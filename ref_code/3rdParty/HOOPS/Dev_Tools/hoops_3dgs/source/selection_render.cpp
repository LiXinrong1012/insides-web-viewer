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
 * $Id: obf_tmp.txt 1.179 2010-10-27 03:56:25 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "patterns.h"
#include "select.h"
#include "tandt.h"
#include "topology.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

GLOBAL_FUNCTION void HD_Selection_Render (
	Net_Rendition const &		nr,
	Geometry const *			geo,
	bool						single) {
#ifndef DISABLE_SELECTION
	_hoops_ACHR					_hoops_SGPPI;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter *	sc = dc->_hoops_APHHP;
	Geometry const *			_hoops_SCRPS = dc->_hoops_RAI;

	_hoops_SGPPI = nr->_hoops_IRR->_hoops_AAICA &
			 (nr->_hoops_RGP |
			  nr->_hoops_IRR->_hoops_PHARP);

	/* _hoops_PAGA: _hoops_GSRPS _hoops_ASGC _hoops_CHR _hoops_RCPRA _hoops_IH _hoops_RSRPS */

	dc->_hoops_CPIGA = false;

	do {
		if (sc->_hoops_GHPPI) {
			dc->_hoops_RAI = null;
			return;
		}

		if (!BIT (geo->_hoops_RRHH, _hoops_HRPGI))
			dc->_hoops_RAI = geo;

		switch (geo->type) {
			case _hoops_SGCP:
			case _hoops_CGCP: {
#ifndef DISABLE_CALLBACKS
				if (nr->_hoops_RSGC->action.draw_3d_geometry != nullroutine) {
					_hoops_HCHGH(nr, _hoops_HGACR);
					_hoops_SHICP (nr, draw_3d_geometry)(&nr, geo);
					_hoops_SCHGH(nr);
				}
				else
#endif
				if (BIT (_hoops_SGPPI, T_FACES))
					HD_Select_Ellipse (nr, (Ellipse alter *)geo, true);
				else if (ANYBIT (_hoops_SGPPI, T_ANY_POLYGON_EDGE))
					HD_Select_Ellipse (nr, (Ellipse alter *)geo, false);
			}	break;

			case _hoops_CHIP: {
#ifndef DISABLE_CALLBACKS
				if (nr->_hoops_RSGC->action.draw_3d_geometry != nullroutine) {
					_hoops_HCHGH(nr, _hoops_HGACR);
					_hoops_SHICP (nr, draw_3d_geometry)(&nr, geo);
					_hoops_SCHGH(nr);
				}
				else
#endif
				if (BIT (_hoops_SGPPI, T_LINES))
					HD_Select_NURBS_Curve (nr, (_hoops_PIRGR alter *)geo);
			}	break;

			case _hoops_RIIP:
			case _hoops_GIIP: {
#ifndef DISABLE_CALLBACKS
				if (nr->_hoops_RSGC->action.draw_3d_geometry != nullroutine) {
					_hoops_HCHGH(nr, _hoops_HGACR);
					_hoops_SHICP (nr, draw_3d_geometry)(&nr, geo);
					_hoops_SCHGH(nr);
				}
				else
#endif
				if (BIT (_hoops_SGPPI, T_LINES))
					HD_Select_Elliptical_Arc (nr, (Elliptical_Arc alter *)geo);
			}	break;

			case _hoops_GRCP:
			case _hoops_RRCP: {
#ifndef DISABLE_CALLBACKS
				if (nr->_hoops_RSGC->action.draw_3d_geometry != nullroutine) {
					_hoops_HCHGH(nr, _hoops_HGACR);
					_hoops_SHICP (nr, draw_3d_geometry)(&nr, geo);
					_hoops_SCHGH(nr);
				}
				else
#endif
				if (BIT (_hoops_SGPPI, T_FACES))
					HD_Select_Ellipse (nr, (Ellipse alter *)geo, true);
				else if (ANYBIT (_hoops_SGPPI, T_ANY_POLYGON_EDGE))
					HD_Select_Ellipse (nr, (Ellipse alter *)geo, false);
			}	break;

			case _hoops_ICIP: {
				Light alter			*light = (Light alter *)geo;

#ifndef DISABLE_CALLBACKS
				if (nr->_hoops_RSGC->action.draw_3d_geometry != nullroutine) {
					_hoops_HCHGH(nr, _hoops_HGACR);
					_hoops_SHICP (nr, draw_3d_geometry)(&nr, geo);
					_hoops_SCHGH(nr);
				}
				else
#endif
				switch (light->_hoops_PRR) {
					case _hoops_S: {
						if (BIT (_hoops_SGPPI, T_ANY_LIGHTS))
							HD_Select_Polyglin (nr, geo, true);
					}	break;

					default: {
					}
				}
			}	break;

			case _hoops_GGCP: {
#ifndef DISABLE_CALLBACKS
				if (nr->_hoops_RSGC->action.draw_3d_geometry != nullroutine) {
					_hoops_HCHGH(nr, _hoops_HGACR);
					_hoops_SHICP (nr, draw_3d_geometry)(&nr, geo);
					_hoops_SCHGH(nr);
				}
				else
#endif
				if (ANYBIT (_hoops_SGPPI, T_VERTICES|T_FACES|T_ANY_GRID_EDGE))
					HD_Select_Grid (nr, (Grid alter *)geo);
			}	break;

			case _hoops_GHPGR: {
				_hoops_RHPGR *		_hoops_AHPGR = (_hoops_RHPGR *)geo;

				if (ANYBIT (_hoops_SGPPI, _hoops_AHPGR->which)) {
					_hoops_PHPGR (HEC_GEOMETRY, HES_MEMORY_PURGED,
							Sprintf_P (null,"Need to select geometry in '%p' -", _hoops_AHPGR->owner), "but memory has been purged from it");
				}
			}	break;

			case _hoops_SIIP:
			case _hoops_PIIP:
			case _hoops_HIIP:
			case _hoops_IIIP: {
#ifndef DISABLE_CALLBACKS
				if (nr->_hoops_RSGC->action.draw_3d_polyline != nullroutine) {
					_hoops_HCHGH(nr,_hoops_RGACR);
					_hoops_SHICP (nr, draw_3d_polyline)(&nr, (Polyline alter *)geo);
					_hoops_SCHGH(nr);
				}
				else if (nr->_hoops_RSGC->action.draw_3d_geometry != nullroutine) {
					_hoops_HCHGH(nr, _hoops_HGACR);
					_hoops_SHICP (nr, draw_3d_geometry)(&nr, geo);
					_hoops_SCHGH(nr);
				}
				else
#endif
				if (BIT (_hoops_SGPPI, T_LINES))
					HD_Select_Polyglin (nr, geo, false);
			}	break;

			case _hoops_PCIP: {
#ifndef DISABLE_CALLBACKS
				if (nr->_hoops_RSGC->action.draw_3d_marker != nullroutine) {
					_hoops_HCHGH(nr, _hoops_GGACR);
					_hoops_SHICP (nr, draw_3d_marker)(&nr, (Marker alter *)geo);
					_hoops_SCHGH(nr);
				}
				else if (nr->_hoops_RSGC->action.draw_3d_geometry != nullroutine) {
					_hoops_HCHGH(nr, _hoops_HGACR);
					_hoops_SHICP (nr, draw_3d_geometry)(&nr, geo);
					_hoops_SCHGH(nr);
				}
				else
#endif
				if (BIT (_hoops_SGPPI, T_MARKERS))
					HD_Select_Marker (nr, (Marker alter *)geo);
			}	break;

			case _hoops_PIRS: {
#ifndef DISABLE_CALLBACKS
				if (nr->_hoops_RSGC->action.draw_3d_marker != null) {
					_hoops_HCHGH(nr, _hoops_GGACR);

					_hoops_GRPGR const *		_hoops_CPAI = (_hoops_GRPGR const *)geo;

					for (int i=0; i<_hoops_CPAI->count; ++i) {
						Marker *	marker;
						int			index = _hoops_CPAI->mapping[i] & ~_hoops_RIRIR;
						ZALLOC (marker, Marker);
						marker->type = _hoops_PCIP;
						marker->_hoops_HIHI = 1;
						marker->owner = _hoops_CPAI->owner;
						marker->key =  HOOPS_WORLD->_hoops_GCHCA.table[index].key;
						marker->_hoops_CSAI = _hoops_CPAI->points[i];
						if (BIT (_hoops_CPAI->mapping[i], _hoops_RIRIR))
							marker->_hoops_RRHH |= _hoops_GGCCA;

						_hoops_SHICP (nr, draw_3d_marker) (&nr, marker);

						_hoops_HPRH (marker);
					}
					geo = _hoops_CPAI;	// _hoops_PHIH _hoops_IH _hoops_CSPC

					_hoops_SCHGH(nr);
				}
				else if (nr->_hoops_RSGC->action.draw_3d_geometry != null) {
					_hoops_HCHGH(nr, _hoops_HGACR);
					_hoops_SHICP (nr, draw_3d_geometry) (&nr, geo);
					_hoops_SCHGH(nr);
				}
				else
#endif
				if (BIT (_hoops_SGPPI, T_MARKERS))
					HD_Select_Multimarker (nr, (_hoops_GRPGR alter *)geo);
			}	break;

			case _hoops_RCIP: {
#ifndef DISABLE_CALLBACKS
				if (nr->_hoops_RSGC->action.draw_3d_polygon != nullroutine) {
					_hoops_HCHGH(nr, _hoops_AGACR);
					_hoops_SHICP (nr, draw_3d_polygon)(&nr, (Polygon alter *)geo);
					_hoops_SCHGH(nr);
				}
				else if (nr->_hoops_RSGC->action.draw_3d_geometry != nullroutine) {
					_hoops_HCHGH(nr, _hoops_HGACR);
					_hoops_SHICP (nr, draw_3d_geometry)(&nr, geo);
					_hoops_SCHGH(nr);
				}
				else
#endif
				if (BIT (_hoops_SGPPI, T_FACES))
					HD_Select_Polyglin (nr, geo, true);
				else if (ANYBIT (_hoops_SGPPI, T_ANY_POLYGON_EDGE))
					HD_Select_Polyglin (nr, geo, false);
			}	break;

			case _hoops_AGCP: {
#ifndef DISABLE_CALLBACKS
				_hoops_HACC *	text = (_hoops_HACC *)geo;

				if (nr->_hoops_RSGC->action.draw_3d_text != nullroutine) {
					_hoops_HCHGH(nr, _hoops_PGACR);
					_hoops_SHICP (nr, draw_3d_text)(&nr, text);
					_hoops_SCHGH(nr);
				}
				else if (nr->_hoops_RSGC->action.draw_3d_geometry != nullroutine) {
					_hoops_HCHGH(nr, _hoops_HGACR);
					_hoops_SHICP (nr, draw_3d_geometry)(&nr, geo);
					_hoops_SCHGH(nr);
				}
				else
#endif
				if (BIT (_hoops_SGPPI, T_TEXT) &&
					(text->count != 0 || text->_hoops_AAPGR != null))
					HD_Select_Text (nr, text);
			}	break;

			case _hoops_HGCP: {
#ifndef DISABLE_CALLBACKS
				if (nr->_hoops_RSGC->action.draw_3d_geometry != nullroutine) {
					_hoops_HCHGH(nr, _hoops_HGACR);
					_hoops_SHICP (nr, draw_3d_geometry)(&nr, geo);
					_hoops_SCHGH(nr);
				}
				else
#endif
				if (BIT (_hoops_SGPPI, T_IMAGES))
					HD_Select_Image (nr, (Image alter *)geo);
			}	break;

			case _hoops_HGPGR: {
			}	break;

			case _hoops_SCIP:
			case _hoops_GSIP: {

				_hoops_CRCP *	_hoops_ARPGR;
				if ((_hoops_ARPGR = geo->owner) != null)
					_hoops_ARPGR->_hoops_RHAGR._hoops_PRPGR(dc->_hoops_RIGC->thread_id);

#ifndef DISABLE_CALLBACKS
				if (nr->_hoops_RSGC->action.draw_3d_geometry != nullroutine) {
					_hoops_HCHGH(nr, _hoops_HGACR);
					_hoops_SHICP (nr, draw_3d_geometry)(&nr, geo);
					_hoops_SCHGH(nr);
				}
				else
#endif
					HD_Select_Polyhedron (nr, (Polyhedron alter *)geo);

				if (_hoops_ARPGR != null)
					_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();

			}	break;

			case _hoops_ASIP: {
#ifndef _hoops_PSPIR
#ifndef DISABLE_CALLBACKS
				if (nr->_hoops_RSGC->action.draw_3d_geometry != nullroutine) {
					_hoops_HCHGH(nr, _hoops_HGACR);
					_hoops_SHICP (nr, draw_3d_geometry)(&nr, geo);
					_hoops_SCHGH(nr);
				}
				else
#endif
					HD_Select_Cylinder (nr, (Cylinder const *)geo);
#endif
			}	break;

			case _hoops_CSIP: {
#ifndef _hoops_PSPIR
#ifndef DISABLE_CALLBACKS
				if (nr->_hoops_RSGC->action.draw_3d_geometry != nullroutine) {
					_hoops_HCHGH(nr, _hoops_HGACR);
					_hoops_SHICP (nr, draw_3d_geometry)(&nr, geo);
					_hoops_SCHGH(nr);
				}
				else
#endif
					HD_Select_PolyCylinder (nr, (PolyCylinder const *)geo);
#endif
			}	break;

			case _hoops_HSIP: {
#ifndef _hoops_RRHIR
#ifndef DISABLE_CALLBACKS
				if (nr->_hoops_RSGC->action.draw_3d_geometry != nullroutine) {
					_hoops_HCHGH(nr, _hoops_HGACR);
					_hoops_SHICP (nr, draw_3d_geometry)(&nr, geo);
					_hoops_SCHGH(nr);
				}
				else
#endif
					HD_Select_Sphere (nr, (Sphere const *)geo);
#endif
			}	break;

			case _hoops_PRCP: {

				_hoops_CRCP *	_hoops_ARPGR;
				if ((_hoops_ARPGR = geo->owner) != null)
					_hoops_ARPGR->_hoops_RHAGR._hoops_PRPGR(dc->_hoops_RIGC->thread_id);
#ifndef DISABLE_CALLBACKS
				if (nr->_hoops_RSGC->action.draw_3d_geometry != nullroutine) {
					_hoops_HCHGH(nr, _hoops_HGACR);
					_hoops_SHICP (nr, draw_3d_geometry)(&nr, geo);
					_hoops_SCHGH(nr);
				}
				else
#endif
					HD_Select_NURBS_Surface (nr, (_hoops_APPGR alter *)geo);


				if (_hoops_ARPGR != null)
					_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
			}	break;

			case _hoops_AHIP: {
				_hoops_PHIP const *	_hoops_RRA = (_hoops_PHIP *)geo;
				_hoops_RISAP				_hoops_HACAH;

				_hoops_HACAH.include = (_hoops_PGRPR *)_hoops_RRA;
				_hoops_HACAH.prev = sc->_hoops_ASCAH;
				sc->_hoops_ASCAH = &_hoops_HACAH;

				sc->_hoops_GSCAH = BIT (_hoops_RRA->_hoops_RRHH, _hoops_PASIR);

				if (_hoops_RRA->condition.count == 0 ||
						 HI_Condition_Passed (nr->_hoops_ASIR->conditions.count,
											  nr->_hoops_ASIR->conditions._hoops_RCHA,
											  &_hoops_RRA->condition)) {
					Net_Rendition		_hoops_ASRPS = nr;

					if (_hoops_RRA->_hoops_IPPGR != null)
						HD_Downwind_Rendition (_hoops_ASRPS, _hoops_RRA->_hoops_IPPGR, _hoops_CAHGP, true);


					if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
						_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0];

						if (_hoops_SRCP->geometry != null)
							HD_Selection_Render (_hoops_ASRPS, _hoops_SRCP->geometry, false);	/* _hoops_SHSC _hoops_HIGR */
					}
					else {
						for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++)
							HD_Selection_Render (_hoops_ASRPS, (Geometry const *)_hoops_RRA->_hoops_IHIP[i], true);
					}
				}


				sc->_hoops_ASCAH = _hoops_HACAH.prev;
			}	break;

			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unknown geometry type in Selection Render");
			}	break;
		}
	} while (!single && (geo = geo->next) != null);

	dc->_hoops_RAI = _hoops_SCRPS;
#endif
}





local bool _hoops_PSRPS (
	Net_Rendition const & 			nr) {
	Display_Context alter *			dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter *		sc = dc->_hoops_APHHP;
	_hoops_HHCR const &		_hoops_IHCR = nr->transform_rendition;
	_hoops_ASHH const *		_hoops_GPHH = _hoops_IHCR->_hoops_HCHH->_hoops_PSHH;
	int								count = _hoops_GPHH->count;
	DC_Point const *				points = _hoops_GPHH->points;
	int								_hoops_IRHAS;

	if (sc->_hoops_CAPAS != 0) {
		_hoops_GPCIH alter * alter *			_hoops_PRHAS;
		int								_hoops_HRHAS;

		_hoops_HRHAS = HI_Create_Polyglin_Wings (count, (Point *)points,
													  true, _hoops_GAPAS,
													  &_hoops_PRHAS);
		_hoops_IRHAS = HI_Wings_Intersect (_hoops_HRHAS, _hoops_PRHAS,
										 sc->_hoops_CAPAS, sc->_hoops_SAPAS);

		HI_Free_Wings (_hoops_HRHAS, _hoops_PRHAS);
	}
	else {
		DC_Point const *				pl = points;
		DC_Point const *				end;
		float							_hoops_AGRSH, _hoops_PGRSH, x1, _hoops_AGSIR,
												_hoops_HSHGA, _hoops_ISHGA,
												xc, yc,
												_hoops_GPHAS, _hoops_RPHAS,
												tc,
												_hoops_SIGGA,
												_hoops_CIGGA,
												_hoops_PHHAS,
												_hoops_HISAP, _hoops_CIPAS;
		bool						_hoops_CARGA = false;
		int								offset = 0;
		bool						_hoops_HHAHR = false;
		float							_hoops_HPCII;


		/* _hoops_HSRPS(!) _hoops_HII _hoops_PRRPS() */
		end = pl + count;
		_hoops_HISAP = sc->_hoops_GICAH;

		_hoops_AGRSH = 0.0f;
		_hoops_PGRSH = 0.0f;
		x1 = pl->x;
		_hoops_AGSIR = pl->y;

		_hoops_RGGA ((++offset, ++pl) == end) {
			if (_hoops_HHAHR) {			/* (_hoops_IRGGS _hoops_RAAP _hoops_IAPR _hoops_HII _hoops_PGHC _hoops_HAPR) */
				x1 = _hoops_AGRSH;
				_hoops_AGSIR = _hoops_PGRSH;
				_hoops_HHAHR = false;
			}

			_hoops_AGRSH = x1;
			_hoops_PGRSH = _hoops_AGSIR;
			x1 = pl->x;
			_hoops_AGSIR = pl->y;

		  _hoops_IRRPS:;

			/* _hoops_RAH _hoops_IRS _hoops_HHCI _hoops_IASC _hoops_AHCRR _hoops_RPGP */

			if (x1 < sc->bounding.left) {
				if (_hoops_AGRSH < sc->bounding.left)
					continue;
			}
			else if (x1 > sc->bounding.right) {
				if (_hoops_AGRSH > sc->bounding.right)
					continue;
			}
			if (_hoops_AGSIR < sc->bounding.bottom) {
				if (_hoops_PGRSH < sc->bounding.bottom)
					continue;
			}
			else if (_hoops_AGSIR > sc->bounding.top) {
				if (_hoops_PGRSH > sc->bounding.top) {
					/* _hoops_PRIA _hoops_ASSA/_hoops_SIPP _hoops_RPGP _hoops_IH _hoops_HSSP _hoops_PIHAS */
					if (_hoops_AGRSH <= sc->_hoops_AICAH.x) {
						if (sc->_hoops_AICAH.x < x1) _hoops_CARGA = !_hoops_CARGA;
					}
					else if (x1 <= sc->_hoops_AICAH.x) {
						if (sc->_hoops_AICAH.x < _hoops_AGRSH) _hoops_CARGA = !_hoops_CARGA;
					}
					continue;
				}
			}

			/* _hoops_ACGR _hoops_RH _hoops_HISGR _hoops_PPSR _hoops_IS _hoops_RH _hoops_HASRH _hoops_GPP _hoops_RH _hoops_PRISA _hoops_III */

			_hoops_HSHGA = x1 - _hoops_AGRSH;
			_hoops_ISHGA = _hoops_AGSIR - _hoops_PGRSH;

			tc = _hoops_HSHGA*_hoops_HSHGA + _hoops_ISHGA*_hoops_ISHGA; /* _hoops_GRAS _hoops_PCHAS */
			if (tc < 0.000001f) {
				/* _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_PPSR, _hoops_HAR _hoops_IRS _hoops_III! */
				xc = _hoops_AGRSH;
				yc = _hoops_PGRSH;
				tc = 0.0f;
			}
			else {
				tc = (_hoops_HSHGA * (sc->_hoops_AICAH.x - _hoops_AGRSH) +
					  _hoops_ISHGA * (sc->_hoops_AICAH.y - _hoops_PGRSH)) / tc;

				if (tc > _hoops_SHRSP) {		/* _hoops_HCHAS _hoops_ICCAR. _hoops_CACH _hoops_ICHAS _hoops_GGR _hoops_RHPP._hoops_GGHR */
					_hoops_HSHGA = -_hoops_HSHGA;
					_hoops_ISHGA = -_hoops_ISHGA;
					_hoops_HPCII = _hoops_AGRSH; _hoops_AGRSH = x1; x1 = _hoops_HPCII;
					_hoops_HPCII = _hoops_PGRSH; _hoops_PGRSH = _hoops_AGSIR; _hoops_AGSIR = _hoops_HPCII;
					_hoops_HHAHR = true;

					tc = (_hoops_HSHGA * (sc->_hoops_AICAH.x - _hoops_AGRSH) +
						  _hoops_ISHGA * (sc->_hoops_AICAH.y - _hoops_PGRSH)) / (_hoops_HSHGA*_hoops_HSHGA + _hoops_ISHGA*_hoops_ISHGA);
				}

				/* _hoops_IRHH _hoops_RCRR _hoops_SR'_hoops_ASAR _hoops_HCHAR _hoops_GIAA _hoops_RH _hoops_III **_hoops_CAGH** ... */
				if (tc <= 0.0f) {
					tc = 0.0f;
					xc = _hoops_AGRSH;
					yc = _hoops_PGRSH;
				}
				else if (tc >= 1.0f) {
					tc = 1.0f;
					xc = x1;
					yc = _hoops_AGSIR;
				}
				else {
					xc = _hoops_AGRSH + _hoops_HSHGA * tc;
					yc = _hoops_PGRSH + _hoops_ISHGA * tc;
				}
			}

			/* _hoops_PRIA _hoops_ASSA/_hoops_SIPP _hoops_RPGP _hoops_IH _hoops_HSSP _hoops_PIHAS */
			if (yc >= sc->_hoops_AICAH.y) {
				if (_hoops_AGRSH <= sc->_hoops_AICAH.x) {
					if (sc->_hoops_AICAH.x < x1) _hoops_CARGA = !_hoops_CARGA;
				}
				else if (x1 <= sc->_hoops_AICAH.x) {
					if (sc->_hoops_AICAH.x < _hoops_AGRSH) _hoops_CARGA = !_hoops_CARGA;
				}
			}

			/* _hoops_CCHAS _hoops_RPGP _hoops_GPP _hoops_RH _hoops_HISGR _hoops_PPSR */
			_hoops_GPHAS = (xc - sc->_hoops_AICAH.x) / sc->_hoops_HICAH.x;
			_hoops_RPHAS = (yc - sc->_hoops_AICAH.y) / sc->_hoops_HICAH.y;
			_hoops_CIPAS = _hoops_GPHAS*_hoops_GPHAS + _hoops_RPHAS*_hoops_RPHAS;

			if (_hoops_CIPAS >= _hoops_HISAP) continue;

			/* _hoops_HSPH _hoops_HISGR _hoops_IS _hoops_RH _hoops_IASC _hoops_AHCRR _hoops_IS _hoops_GHGPR _hoops_ISPR */
			_hoops_SIGGA = 1.0f;
			_hoops_CIGGA = 0.0f;

			if (_hoops_HSHGA > 0.0f) {
				if (_hoops_AGRSH < sc->bounding.left) {
					_hoops_PHHAS = (sc->bounding.left - _hoops_AGRSH) / _hoops_HSHGA;
					if (_hoops_CIGGA < _hoops_PHHAS) _hoops_CIGGA = _hoops_PHHAS;
				}
				if (x1 > sc->bounding.right) {
					_hoops_PHHAS = (sc->bounding.right - _hoops_AGRSH) / _hoops_HSHGA;
					if (_hoops_SIGGA > _hoops_PHHAS) _hoops_SIGGA = _hoops_PHHAS;
				}
			}
			else {
				if (x1 < sc->bounding.left) {
					if (_hoops_HSHGA == 0.0f) continue;
					_hoops_PHHAS = (sc->bounding.left - _hoops_AGRSH) / _hoops_HSHGA;
					if (_hoops_SIGGA > _hoops_PHHAS) _hoops_SIGGA = _hoops_PHHAS;
				}
				if (_hoops_AGRSH > sc->bounding.right) {
					if (_hoops_HSHGA == 0.0f) continue;
					_hoops_PHHAS = (sc->bounding.right - _hoops_AGRSH) / _hoops_HSHGA;
					if (_hoops_CIGGA < _hoops_PHHAS) _hoops_CIGGA = _hoops_PHHAS;
				}
			}

			if (_hoops_ISHGA > 0.0f) {
				if (_hoops_PGRSH < sc->bounding.bottom) {
					_hoops_PHHAS = (sc->bounding.bottom - _hoops_PGRSH) / _hoops_ISHGA;
					if (_hoops_CIGGA < _hoops_PHHAS) _hoops_CIGGA = _hoops_PHHAS;
				}
				if (_hoops_AGSIR > sc->bounding.top) {
					_hoops_PHHAS = (sc->bounding.top - _hoops_PGRSH) / _hoops_ISHGA;
					if (_hoops_SIGGA > _hoops_PHHAS) _hoops_SIGGA = _hoops_PHHAS;
				}
			}
			else {
				if (_hoops_AGSIR < sc->bounding.bottom) {
					if (_hoops_ISHGA == 0.0f) continue;
					_hoops_PHHAS = (sc->bounding.bottom - _hoops_PGRSH) / _hoops_ISHGA;
					if (_hoops_SIGGA > _hoops_PHHAS) _hoops_SIGGA = _hoops_PHHAS;
				}
				if (_hoops_PGRSH > sc->bounding.top) {
					if (_hoops_ISHGA == 0.0f) continue;
					_hoops_PHHAS = (sc->bounding.top - _hoops_PGRSH) / _hoops_ISHGA;
					if (_hoops_CIGGA < _hoops_PHHAS) _hoops_CIGGA = _hoops_PHHAS;
				}
			}

			if (_hoops_CIGGA >= _hoops_SIGGA) continue; /* _hoops_HCR _hoops_PPRGA */

			/* _hoops_CGP _hoops_SCH _hoops_GGHP _hoops_SACH - _hoops_RHSHA _hoops_IPCAH */
			if (tc < _hoops_CIGGA || tc > _hoops_SIGGA) {
				if (tc < _hoops_CIGGA)
					tc = _hoops_CIGGA;
				else
					tc = _hoops_SIGGA;

				xc = _hoops_AGRSH + _hoops_HSHGA * tc;
				yc = _hoops_PGRSH + _hoops_ISHGA * tc;

				_hoops_GPHAS = (xc - sc->_hoops_AICAH.x) / sc->_hoops_HICAH.x;
				_hoops_RPHAS = (yc - sc->_hoops_AICAH.y) / sc->_hoops_HICAH.y;
				_hoops_CIPAS = _hoops_GPHAS*_hoops_GPHAS + _hoops_RPHAS*_hoops_RPHAS;

				if (_hoops_CIPAS >= _hoops_HISAP) continue;
			}

			/* _hoops_SSHAS _hoops_HCCHA */
			return true;
		}

		if (offset == count) {
			if (_hoops_HHAHR) {			/* (_hoops_IRGGS _hoops_RAAP _hoops_IAPR _hoops_HII _hoops_HAPR) */
				x1 = _hoops_AGRSH;
				_hoops_AGSIR = _hoops_PGRSH;
				_hoops_HHAHR = false;
			}

			/* _hoops_ARP _hoops_CGSI _hoops_GH _hoops_GAR _hoops_RPP _hoops_SR _hoops_RIAGR _hoops_RIAGR _hoops_SPR _hoops_RRI _hoops_PPSR */
			pl = points;						/* _hoops_GGHC _hoops_RH _hoops_HAPR _hoops_IS... */
			end = pl + 1;						/* _hoops_HPRAR _hoops_GGSR _hoops_SPS _hoops_GHIR */

			_hoops_AGRSH = x1;
			_hoops_PGRSH = _hoops_AGSIR;
			x1 = pl->x;
			_hoops_AGSIR = pl->y;
			goto _hoops_IRRPS;
		}

		return _hoops_CARGA;	/* _hoops_RPP _hoops_PSP '_hoops_PPPSR _hoops_RHHR' _hoops_GPP _hoops_PCCP _hoops_ISHA _hoops_SR _hoops_RPR _hoops_RPP _hoops_SR _hoops_CHR _hoops_ASSA _hoops_RH _hoops_ISPH */
	}

	return (_hoops_IRHAS > 0);
}






GLOBAL_FUNCTION void HD_Selection_Walk_Tree (
	Net_Rendition const &		inr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		_hoops_APPIP) {
#ifndef DISABLE_SELECTION
	Net_Rendition				nr = inr;
	_hoops_HICS				path = _hoops_APPIP;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter	*	sc = dc->_hoops_APHHP;
	Subsegment const *			_hoops_SSGPR;
	_hoops_PGCIR						_hoops_ISRPS;
	bool						_hoops_CSRPS = false;
	_hoops_ICCAH *	_hoops_CCCAH = null;

	_hoops_ISRPS = sc->bounding;

	top:;

	dc->_hoops_RRCIP = _hoops_SRCP;

	if (sc->_hoops_GHPPI)
		return;

#ifndef DISABLE_CALLBACKS
	if (true || BIT (HOOPS_WORLD->_hoops_HPSPP, _hoops_GHCPP)) {
		if (BIT(dc->flags, _hoops_HHICP)) {
			dc->flags &= ~_hoops_HHICP;

			if (nr->transform_rendition->_hoops_AGAA.left > sc->bounding.right ||
				nr->transform_rendition->_hoops_AGAA.right < sc->bounding.left ||
				nr->transform_rendition->_hoops_AGAA.bottom > sc->bounding.top ||
				nr->transform_rendition->_hoops_AGAA.top < sc->bounding.bottom)
				return;			/* _hoops_ISAP _hoops_HHRPA _hoops_IS _hoops_HPPP */

			if (nr->transform_rendition->_hoops_AGAA.left > sc->bounding.left) {
				sc->bounding.left = (float)nr->transform_rendition->_hoops_AGAA.left;
				_hoops_CSRPS = true;
			}
			if (nr->transform_rendition->_hoops_AGAA.right < sc->bounding.right) {
				sc->bounding.right = (float)nr->transform_rendition->_hoops_AGAA.right;
				_hoops_CSRPS = true;
			}
			if (nr->transform_rendition->_hoops_AGAA.bottom > sc->bounding.bottom) {
				sc->bounding.bottom = (float)nr->transform_rendition->_hoops_AGAA.bottom;
				_hoops_CSRPS = true;
			}
			if (nr->transform_rendition->_hoops_AGAA.top < sc->bounding.top) {
				sc->bounding.top = (float)nr->transform_rendition->_hoops_AGAA.top;
				_hoops_CSRPS = true;
			}
		}
		else {
			_hoops_PSIHP		_hoops_HSIHP = nr->_hoops_RSGC;

			if (_hoops_HSIHP->action.draw_segment_tree != nullroutine ||
				_hoops_HSIHP->action.draw_segment != nullroutine) {

				Segment_Info alter *	si;
				ZALLOC (si, Segment_Info);
				si->segment = _hoops_SRCP;
				si->next = (Segment_Info alter *)dc->_hoops_CHICP; /* _hoops_ICIC _hoops_HIIC */
				dc->_hoops_CHICP = si;
				dc->flags |= _hoops_HHICP;

				_hoops_ARIGH(nr, si);

				if (dc->_hoops_CHICP != si) {
					do {
						Segment_Info alter	*victim;
						if ((victim = (Segment_Info alter *)dc->_hoops_CHICP) == null) {
							HE_ERROR (HEC_CALLBACK, HES_RENDITION_FREED, "Too many Renditions freed during a segment callback.");
							return;
						}
						dc->_hoops_CHICP = victim->next;
						victim->path.release();
						FREE (victim, Segment_Info);
					} _hoops_RGGA (dc->_hoops_CHICP == si);
					HE_ERROR (HEC_CALLBACK, HES_RENDITION_NOT_FREED, "New Renditions during a segment callback were not freed.");
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

	if (BIT (nr->transform_rendition->_hoops_APH, Heur_Culling_VIEW_FRUSTUM) &&
		_hoops_SRCP->bounding != null &&
		!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_PSPCR) &&
		(!BIT (_hoops_SRCP->_hoops_RCGC, T_MARKERS) ||
		 !BIT (nr->_hoops_IRR->_hoops_AAICA &
			   (nr->_hoops_RGP |
				nr->_hoops_IRR->_hoops_PHARP), T_MARKERS) &&
		 !ANYBIT (_hoops_SRCP->_hoops_RCGC, _hoops_APHGP|_hoops_RPHGP))) {
		bool				_hoops_SSRPS;

		_hoops_SSRPS = ANYBIT (_hoops_SRCP->bounding->flags, _hoops_IGCIR|Bounding_TRANSFORM_DEPENDENT) ||
							  BIT (_hoops_SRCP->bounding->flags, _hoops_HGCIR) &&
							  (nr->_hoops_SISI->transform != FT_FULL ||
							   BIT (dc->_hoops_CPGPR, _hoops_RSCCA) ||
							   BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR) || 1);

		if (!_hoops_SSRPS) {
			_hoops_PACIR			_hoops_IPGPS;
			Int_Rectangle				_hoops_CPGPS;
			_hoops_ICP const &	_hoops_CCP = nr->_hoops_GSP;
			float						_hoops_HPGPS = _hoops_CCP->ysize;

			if (BIT (_hoops_CCP->glyph->flags, _hoops_GSIAP))
				_hoops_HPGPS = 1.0f;
			else if (_hoops_HPGPS < 0)
				_hoops_HPGPS = 0.5f * HD_Compute_Generic_Size (nr, _hoops_CCP->_hoops_PHP, _hoops_CCP->_hoops_HHP, 1.0f, false, 0, true);

			_hoops_IPGPS = sc->bounding;
			_hoops_IPGPS._hoops_IACHA(_hoops_HPGPS);

			_hoops_CPGPS = sc->bounding;

			switch (HD_Transform_And_Test_Bounding (nr, &_hoops_SRCP->bounding, &_hoops_IPGPS, &_hoops_CPGPS, 0)) {
			  case Test_DISJOINT:
				return;
				_hoops_HHHI;

			  case _hoops_GAAGI:
			  case _hoops_AAAGI:
			  case _hoops_RAAGI:
				break;
			}
		}
	}

	if (nr->transform_rendition->_hoops_HCHH != null) {
		if (!_hoops_PSRPS (nr))
			return;
	}

	if (nr->_hoops_IRR->_hoops_GRCRP == _hoops_IGCRP) {
		ZALLOC (_hoops_CCCAH, _hoops_ICCAH);
		_hoops_CCCAH->next = sc->_hoops_HCCAH;
		sc->_hoops_HCCAH = _hoops_CCCAH;
		_hoops_CCCAH->segment = _hoops_SRCP;

		/* _hoops_AGRP _hoops_CCH _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_AA _hoops_RGR _hoops_GPP _hoops_GRR _hoops_PSHHP, _hoops_HIH _hoops_GA'_hoops_RA _hoops_IHSH _hoops_PII _hoops_GII _hoops_RII _hoops_CCH */
		nr.Modify()->_hoops_IRR.Modify()->_hoops_GRCRP = _hoops_CGCRP;
	}

	if (_hoops_SRCP->geometry != null) {
		if (nr->_hoops_IRR->_hoops_GRCRP == _hoops_HGCRP) {
			ZALLOC (_hoops_CCCAH, _hoops_ICCAH);
			_hoops_CCCAH->next = sc->_hoops_HCCAH;
			sc->_hoops_HCCAH = _hoops_CCCAH;
			_hoops_CCCAH->segment = _hoops_SRCP;
		}

		HD_Selection_Render (nr, _hoops_SRCP->geometry, false);

		if (_hoops_CCCAH != null) {
			if (_hoops_CCCAH->valid) {
				sc->_hoops_HCCAH = null;	/* _hoops_RRS _hoops_GGAPS _hoops_HII "_hoops_SIIAR" */
				HD_Elaborate_Selection (nr, (Geometry const *)_hoops_CCCAH->segment,
										_hoops_CCCAH->segment->key, _hoops_AIRIR(_hoops_CCCAH->segment),
										-1, -1, -1,
										_hoops_CCCAH->_hoops_RCSAP, _hoops_CCCAH->_hoops_HCSAP, _hoops_CCCAH->_hoops_SCCAH, null);
			}
			sc->_hoops_HCCAH = _hoops_CCCAH->next;
			FREE (_hoops_CCCAH, _hoops_ICCAH);
			_hoops_CCCAH = null;
		}
	}

	if ((_hoops_SSGPR = _hoops_SRCP->_hoops_RGRPR) != null) do {
		if (sc->_hoops_GHPPI)
			break;

		_hoops_HICS		_hoops_HHPIP = path;
		_hoops_PGRPR const *		include = null;

		if (_hoops_SSGPR->type == _hoops_AGRPR) {
			include = (_hoops_PGRPR alter *)_hoops_SSGPR;

			if (include->condition.count == 0 ||
				HI_Condition_Passed (nr->_hoops_ASIR->conditions.count,
									 nr->_hoops_ASIR->conditions._hoops_RCHA,
									 &include->condition)) {
				_hoops_SRCP = include->_hoops_IGRPR;
				_hoops_HHPIP._hoops_IACHA (include, dc);
			}
			else
				_hoops_SRCP = null;
		}
		else
			_hoops_SRCP = (_hoops_CRCP const *)_hoops_SSGPR;

		if (_hoops_SRCP != null && !BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) {
			_hoops_ACHR	_hoops_PGPIR = _hoops_SRCP->_hoops_RCGC & _hoops_RAHGP & _hoops_IRHGP;

			if (BIT (_hoops_PGPIR, T_FACES))
				_hoops_PGPIR |= _hoops_GPA;
			if (!ANYBIT (_hoops_SRCP->_hoops_RCGC, _hoops_APHGP | _hoops_RPHGP)) {
				if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_RPHGP))
					_hoops_PGPIR &= nr->_hoops_IRR->_hoops_AAICA;
				if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_APHGP)) {
					_hoops_ACHR		_hoops_HSIPH = nr->_hoops_RGP;

					if (BIT (_hoops_HSIPH, T_FACES))
						_hoops_HSIPH |= _hoops_GPA;
					if (ANYBIT (_hoops_HSIPH, T_ANY_EDGE))
						_hoops_HSIPH |= T_EDGES;

					_hoops_PGPIR &= _hoops_HSIPH | nr->_hoops_IRR->_hoops_PHARP;
				}
			}

			if (_hoops_PGPIR != false) {
				Net_Rendition		_hoops_PPHIP = nr;

				if (_hoops_SRCP->_hoops_IPPGR != null) {
					_hoops_HHRA const *		_hoops_HPHIP = _hoops_PPHIP->transform_rendition->_hoops_SPH;

					HD_Selection_Downwind (_hoops_PPHIP, _hoops_SRCP->_hoops_IPPGR);

					if ((_hoops_PPHIP->transform_rendition->_hoops_SPH != _hoops_HPHIP ||
							BIT(_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) &&
						(*_hoops_PPHIP->transform_rendition->_hoops_SPH->_hoops_SIPCR < 0.0f ||
						*_hoops_PPHIP->transform_rendition->_hoops_SPH->_hoops_SIPCR == 0.0f && _hoops_GIPHP < 0.0f)) {

						HD_Adjust_WLimit (_hoops_PPHIP, _hoops_SRCP, _hoops_HHPIP);
					}
				}
				if (BIT(_hoops_PPHIP->_hoops_IRR->_hoops_PPH, _hoops_AARAP) &&
					BIT(_hoops_PPHIP->_hoops_RGP, T_CUTTING_PLANES) ||
					_hoops_SRCP->_hoops_PAGSA() > 0 && _hoops_SRCP->geometry != null)
					HD_Find_Local_Cutting_Planes (_hoops_PPHIP, _hoops_SRCP);

				if (!BIT (sc->options, _hoops_IICAH) &&
					(_hoops_PPHIP->transform_rendition->_hoops_AGAA.left > sc->bounding.right+1 ||
					 _hoops_PPHIP->transform_rendition->_hoops_AGAA.right < sc->bounding.left-1 ||
					 _hoops_PPHIP->transform_rendition->_hoops_AGAA.bottom > sc->bounding.top+1 ||
					 _hoops_PPHIP->transform_rendition->_hoops_AGAA.top < sc->bounding.bottom-1)) {}
				else if (include == null) {
					sc->_hoops_GSCAH = BIT (_hoops_SSGPR->_hoops_RRHH,
												_hoops_PASIR);

					if (_hoops_SSGPR->next != null || _hoops_CSRPS || _hoops_CCCAH != null)
						HD_Selection_Walk_Tree (_hoops_PPHIP, _hoops_SRCP, _hoops_HHPIP);
					else {		/* _hoops_RIRP-_hoops_PAGIR */
						path = _hoops_HHPIP;
						nr = _hoops_PPHIP;
						goto top;
					}
				}
				else {	/* _hoops_SCH'_hoops_GRI _hoops_PCCP _hoops_GPAPA */
					_hoops_RISAP				_hoops_HACAH;

					_hoops_HACAH.include = include;
					_hoops_HACAH.prev = sc->_hoops_ASCAH;
					sc->_hoops_ASCAH = &_hoops_HACAH;

					sc->_hoops_GSCAH = BIT (_hoops_SSGPR->_hoops_RRHH,
												_hoops_PASIR);
					HD_Selection_Walk_Tree (_hoops_PPHIP, _hoops_SRCP, _hoops_HHPIP);

					sc->_hoops_ASCAH = _hoops_HACAH.prev;
				}
			}
		}
	} while ((_hoops_SSGPR = _hoops_SSGPR->next) != null);

	if (_hoops_CCCAH != null) {
		if (_hoops_CCCAH->valid) {
			sc->_hoops_HCCAH = null;	/* _hoops_RRS _hoops_GGAPS _hoops_HII "_hoops_SIIAR" */
			HD_Elaborate_Selection (nr, (Geometry const *)_hoops_CCCAH->segment,
									_hoops_CCCAH->segment->key, _hoops_AIRIR(_hoops_CCCAH->segment),
									-1, -1, -1,
									_hoops_CCCAH->_hoops_RCSAP, _hoops_CCCAH->_hoops_HCSAP, _hoops_CCCAH->_hoops_SCCAH, null);
		}
		sc->_hoops_HCCAH = _hoops_CCCAH->next;
		FREE (_hoops_CCCAH, _hoops_ICCAH);
		_hoops_CCCAH = null;
	}

	if (_hoops_CSRPS)
		sc->bounding = _hoops_ISRPS;
#endif
}

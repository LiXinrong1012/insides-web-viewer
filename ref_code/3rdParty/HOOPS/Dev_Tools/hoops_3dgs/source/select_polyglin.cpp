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
 * $Id: obf_tmp.txt 1.92 2010-10-06 19:16:29 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "select.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


/* _hoops_GIGHR: _hoops_APGR _hoops_PPR _hoops_SPPR _hoops_SGS _hoops_CHR 1 _hoops_PPSR _hoops_RGRRR _hoops_CHR _hoops_HAR _hoops_GGSRA ?*/

/* _hoops_GIGHR: _hoops_IPCAS _hoops_RHAP _hoops_HAR _hoops_PPSR _hoops_IS _hoops_RH "_hoops_SCHIA" _hoops_IIGR _hoops_PGCR _hoops_APGR _hoops_ICPAA _hoops_HII
		 _hoops_RH _hoops_PSHR _hoops_GPHA.
 */

/* _hoops_HRS _hoops_IHPR _hoops_RPP _hoops_SR'_hoops_ASAR *_hoops_ASSA* _hoops_RH _hoops_CARA (_hoops_ASSA _hoops_IRS _hoops_HSP) */

GLOBAL_FUNCTION void HD_Select_Polyglin (
	Net_Rendition const &		nr,
	Geometry const *			geometry,
	bool						_hoops_CSHIH) {
#ifndef DISABLE_SELECTION
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter	*	sc = dc->_hoops_APHHP;
	bool						_hoops_PISAA = BIT (nr->transform_rendition->heuristics,
															_hoops_PAIRP);
	int							offset1,
								offset2;
	float						_hoops_RCSAP;
	float						_hoops_HISAP;
	_hoops_GHGGH *			_hoops_IGHGH = dc->_hoops_IGHGH;

	if (_hoops_PISAA) {
		sc->_hoops_HPPAS._hoops_RAI = geometry;
		sc->_hoops_HPPAS._hoops_HHGGH = sc->_hoops_GICAH;
	}
	sc->_hoops_HPPAS._hoops_APPAS = &sc->_hoops_HPPAS._hoops_ACSAP;
	sc->_hoops_HPPAS._hoops_PPPAS = 0;
	sc->_hoops_HPPAS._hoops_RPPAS = nr->_hoops_IRR->_hoops_CCIRP.polyline;
	sc->_hoops_HPPAS._hoops_PHGGH = -1;
	sc->_hoops_HPPAS._hoops_CHGGH = -1;
	sc->_hoops_HPPAS._hoops_CIHIA = false;

	offset1 = offset2 = -1;
	_hoops_HISAP = 0.001f;
	_hoops_RCSAP = nr->transform_rendition->_hoops_PCHH;

	switch (geometry->type) {
		case _hoops_HIIP: {
			_hoops_SHRIR alter *	_hoops_GIRIR = (_hoops_SHRIR alter *)geometry;
			int					count = -_hoops_GIRIR->count / 2;
			Point const *		points = _hoops_GIRIR->points + 2 * count;
			int const *			mapping = _hoops_GIRIR->mapping + count;

			while (count-- > 0) {
				int				index = *--mapping & ~_hoops_RIRIR;
				Key				_hoops_CPCAS = HOOPS_WORLD->_hoops_GCHCA.table[index].key;
				Line			line;

				points -= 2;

				ZERO_STRUCT (&line, Line);
				line.type = _hoops_PIIP;
				line.key = _hoops_CPCAS;
				line.points[0] = points[0];
				line.points[1] = points[1];

				if (_hoops_PISAA) {
					HD_Std_3D_Polyline (nr, (Polyline *)&line);

					if ((offset1 = sc->_hoops_HPPAS._hoops_CHGGH) != -1 || sc->_hoops_HPPAS._hoops_CIHIA) {
						offset2 = offset1 + 1;
						
						if (_hoops_IGHGH != null) {
							if (sc->_hoops_HPPAS._hoops_HHGGH < _hoops_IGHGH->_hoops_HHGGH) {
								_hoops_IGHGH->_hoops_HHGGH		= sc->_hoops_HPPAS._hoops_HHGGH;
								_hoops_IGHGH->_hoops_IHGGH		= sc->_hoops_HPPAS._hoops_IHGGH;
								_hoops_IGHGH->_hoops_CHGGH	= _hoops_IGHGH->_hoops_PHGGH;
							}
						}
						else
							HD_Elaborate_Selection (nr, dc->_hoops_RAI, _hoops_CPCAS, ~(POINTER_SIZED_INT)index,
													offset1, offset2, 0,
													sc->_hoops_HPPAS._hoops_IHGGH, sc->_hoops_HPPAS._hoops_HHGGH,
													T_LINES, sc->_hoops_HPPAS._hoops_ACSAP);
					}
				}
				else if (HD_Select_Point_List (nr, (Geometry *)&line, 2, points,
											   false, false,
											   &offset1, &offset2, &_hoops_HISAP, &_hoops_RCSAP)) {
					if (_hoops_IGHGH != null) {
						if (_hoops_HISAP < _hoops_IGHGH->_hoops_HHGGH) {
							_hoops_IGHGH->_hoops_HHGGH		= _hoops_HISAP;
							_hoops_IGHGH->_hoops_IHGGH		= _hoops_RCSAP;
							_hoops_IGHGH->_hoops_CHGGH	= _hoops_IGHGH->_hoops_PHGGH;
						}
					}
					else
						HD_Elaborate_Selection (nr, dc->_hoops_RAI, _hoops_CPCAS, ~(POINTER_SIZED_INT)index,
												offset1, offset2, 0,
												_hoops_RCSAP, _hoops_HISAP, T_LINES, sc->_hoops_HPPAS._hoops_ACSAP);
				}
				else {
					while (sc->_hoops_HPPAS._hoops_ACSAP != null) {
						_hoops_AISAP *	victim = sc->_hoops_HPPAS._hoops_ACSAP;
						sc->_hoops_HPPAS._hoops_ACSAP = victim->next;
						FREE (victim, _hoops_AISAP);
					}
				}

				sc->_hoops_HPPAS._hoops_ACSAP = null;
				sc->_hoops_HPPAS._hoops_APPAS = &sc->_hoops_HPPAS._hoops_ACSAP;
				sc->_hoops_HPPAS._hoops_PPPAS = 0;
				//_hoops_SAIAS->_hoops_AHSIR._hoops_SPCAS = _hoops_SCII->_hoops_CCGIP->_hoops_GHCAS._hoops_ISII;
				sc->_hoops_HPPAS._hoops_PHGGH = -1;
				sc->_hoops_HPPAS._hoops_CHGGH = -1;
				sc->_hoops_HPPAS._hoops_CIHIA = false;
			}

			sc->_hoops_HPPAS._hoops_ACSAP = null;
		}	break;

		case _hoops_SIIP:
		case _hoops_PIIP:
		case _hoops_IIIP: {
			Polyline alter *	p = (Polyline alter *)geometry;
			Point const *		points;
			int					count;

			if (p->type == _hoops_PIIP) {
				Line const *	line = (Line const *)p;

				points = line->points;
				count = 2;
			}
			else {
				points = p->points;
				count = p->count;
			}

			if (_hoops_PISAA || geometry->type == _hoops_SIIP) {
				if (geometry->type == _hoops_SIIP)
					HD_Std_3D_Infinite_Line(nr, p);
				else
					HD_Std_3D_Polyline (nr, p);

				if ((offset1 = sc->_hoops_HPPAS._hoops_CHGGH) != -1 || sc->_hoops_HPPAS._hoops_CIHIA) {
					offset2 = offset1 + 1;
					
					if (_hoops_IGHGH != null) {
						if (sc->_hoops_HPPAS._hoops_HHGGH < _hoops_IGHGH->_hoops_HHGGH) {
							_hoops_IGHGH->_hoops_HHGGH		= sc->_hoops_HPPAS._hoops_HHGGH;
							_hoops_IGHGH->_hoops_IHGGH		= sc->_hoops_HPPAS._hoops_IHGGH;
							_hoops_IGHGH->_hoops_CHGGH	= _hoops_IGHGH->_hoops_PHGGH;
						}
					}
					else
						HD_Elaborate_Selection (nr, dc->_hoops_RAI,
												dc->_hoops_RAI->key, _hoops_AIRIR(dc->_hoops_RAI),
												offset1, offset2, 0,
												sc->_hoops_HPPAS._hoops_IHGGH, sc->_hoops_HPPAS._hoops_HHGGH,
												T_LINES, sc->_hoops_HPPAS._hoops_ACSAP);
				}
			}
			else if (HD_Select_Point_List (nr, geometry, count, points,
										   false, false,
										   &offset1, &offset2, &_hoops_HISAP, &_hoops_RCSAP)) {
				if (_hoops_IGHGH != null) {
					if (_hoops_HISAP < _hoops_IGHGH->_hoops_HHGGH) {
						_hoops_IGHGH->_hoops_HHGGH		= _hoops_HISAP;
						_hoops_IGHGH->_hoops_IHGGH		= _hoops_RCSAP;
						_hoops_IGHGH->_hoops_CHGGH	= _hoops_IGHGH->_hoops_PHGGH;
					}
				}
				else
					HD_Elaborate_Selection (nr, dc->_hoops_RAI,
											dc->_hoops_RAI->key, _hoops_AIRIR(dc->_hoops_RAI),
											offset1, offset2, 0,
											_hoops_RCSAP, _hoops_HISAP, T_LINES, sc->_hoops_HPPAS._hoops_ACSAP);
			}
			else {
				while (sc->_hoops_HPPAS._hoops_ACSAP != null) {
					_hoops_AISAP *	victim = sc->_hoops_HPPAS._hoops_ACSAP;
					sc->_hoops_HPPAS._hoops_ACSAP = victim->next;
					FREE (victim, _hoops_AISAP);
				}
			}

			sc->_hoops_HPPAS._hoops_ACSAP = null;
		}	break;

		case _hoops_RCIP: {
			Polygon alter	*p = (Polygon alter *)geometry;

#ifdef _hoops_RHCAS
			if (BIT (_hoops_IHCR->flags, _hoops_IGSP)) {
				if (BIT(_hoops_IHCR->heuristics, _hoops_SASA)) {
					if (HD_Find_Geometry_Screen_Plane_C (nr, geometry) < 0.0f)
						return;
				}
				else { /* _hoops_RAAP-_hoops_IGCH */
					if (HD_Find_Geometry_Screen_Plane_C (nr, geometry) >= 0.0f)
						return;
				}
			}
#endif
			if (HD_Select_Point_List (nr, geometry, p->count, p->points,
									  true, _hoops_CSHIH,
									  &offset1, &offset2, &_hoops_HISAP, &_hoops_RCSAP)) {
				if (_hoops_IGHGH != null) {
					if (_hoops_HISAP < _hoops_IGHGH->_hoops_HHGGH) {
						_hoops_IGHGH->_hoops_HHGGH		= _hoops_HISAP;
						_hoops_IGHGH->_hoops_IHGGH		= _hoops_RCSAP;
						_hoops_IGHGH->_hoops_CHGGH	= _hoops_IGHGH->_hoops_PHGGH;
					}
				}
				else if (_hoops_CSHIH && _hoops_HISAP == 0.0f)
					HD_Elaborate_Selection (nr, dc->_hoops_RAI,
											dc->_hoops_RAI->key, _hoops_AIRIR(dc->_hoops_RAI),
											offset1, offset2, 0,
											_hoops_RCSAP, _hoops_HISAP, T_FACES, null);
				else
					HD_Elaborate_Selection (nr, dc->_hoops_RAI,
											dc->_hoops_RAI->key, _hoops_AIRIR(dc->_hoops_RAI),
											offset1, offset2, 0,
											_hoops_RCSAP, _hoops_HISAP, T_ANY_EDGE, null);
			}
		}	break;

		case _hoops_ICIP: {		/* _hoops_CCAC _hoops_RRR _hoops_RGAR */
			_hoops_SHPIR alter	*light = (_hoops_SHPIR alter *)geometry;

			if (HD_Select_Point_List (nr, geometry,
									  light->count,
									  light->points,
									  false, false,
									  &offset1, &offset2, &_hoops_HISAP, &_hoops_RCSAP))
				HD_Elaborate_Selection (nr, dc->_hoops_RAI,
										dc->_hoops_RAI->key, _hoops_AIRIR(dc->_hoops_RAI),
										offset1, offset2, 0,
										_hoops_RCSAP, _hoops_HISAP, T_ANY_LIGHTS, null);
		}	break;


		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				"Polyline/gon selection called with unexpected geometry");
		}	break;
	}

	sc->_hoops_HPPAS._hoops_RAI = null;

	while (sc->_hoops_HPPAS._hoops_ACSAP != null) {
		_hoops_AISAP *	victim = sc->_hoops_HPPAS._hoops_ACSAP;
		sc->_hoops_HPPAS._hoops_ACSAP = victim->next;
		FREE (victim, _hoops_AISAP);
	}
	sc->_hoops_HPPAS._hoops_ACSAP = null;
	sc->_hoops_HPPAS._hoops_APPAS = &dc->_hoops_APHHP->_hoops_HPPAS._hoops_ACSAP;
	sc->_hoops_HPPAS._hoops_PPPAS = 0;
#endif
}

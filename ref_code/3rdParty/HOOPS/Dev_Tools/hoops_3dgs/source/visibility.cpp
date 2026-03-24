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
 * $Id: obf_tmp.txt 1.162 2010-11-18 00:59:02 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "adt.h"

/*
 * _hoops_GIGHR: "_hoops_IHSAA" _hoops_GGR _hoops_RGR _hoops_RGHR _hoops_AGSR "_hoops_ARP _hoops_RH _hoops_RSIR _hoops_PAIP _hoops_IS _hoops_RGR _hoops_PIRA".
 */



local const _hoops_IGRCR _hoops_APCRGR[] = {
	{_hoops_RIHGP,		_hoops_GRRCR ("everything"),	_hoops_RRRCR, 0, true},
	{_hoops_RIHGP,		_hoops_GRRCR ("on"),			_hoops_RRRCR, 0, false},
	{_hoops_RIHGP,		_hoops_GRRCR ("yes"),			_hoops_RRRCR, 0, false},
	{T_SHADOW_RECEIVING,_hoops_GRRCR ("receiving"),		_hoops_RRRCR, 0, true},
	{_hoops_SHHGP,	_hoops_GRRCR ("casting"),		_hoops_RRRCR, 0, true},
	{_hoops_GIHGP, _hoops_GRRCR ("emitting"),		_hoops_RRRCR, 0, true},
	{0,					_hoops_GRRCR ("off"),			_hoops_RRRCR, 0, false},
	{0,					_hoops_GRRCR ("nothing"),		_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_PPCRGR = {
	_hoops_GGAPR (_hoops_APCRGR),			_hoops_APCRGR,
};


local const _hoops_IGRCR _hoops_HPCRGR[] = {
	{T_LINES|T_FACES,	_hoops_GRRCR ("on"),			_hoops_RRRCR, 0, false},
	{T_LINES|T_FACES,	_hoops_GRRCR ("yes"),			_hoops_RRRCR, 0, false},
	{T_LINES|T_FACES,	_hoops_GRRCR ("all"),			_hoops_RRRCR, 0, false},
	{T_LINES,			_hoops_GRRCR ("edge"),			_hoops_RRRCR, 0, true},
	{T_LINES,			_hoops_GRRCR ("edges"),			_hoops_RRRCR, 0, true},
	{T_FACES,			_hoops_GRRCR ("face"),			_hoops_RRRCR, 0, true},
	{T_FACES,			_hoops_GRRCR ("faces"),			_hoops_RRRCR, 0, true},
	{0,					_hoops_GRRCR ("off"),			_hoops_RRRCR, 0, false},
	{0,					_hoops_GRRCR ("no"),			_hoops_RRRCR, 0, false},
	{0,					_hoops_GRRCR ("nothing"),		_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_IPCRGR = {
	_hoops_GGAPR (_hoops_HPCRGR),		_hoops_HPCRGR,
};


local const _hoops_IGRCR _hoops_CPCRGR[] = {
	{T_ANY_EDGE,							_hoops_GRRCR ("everything"),				_hoops_RRRCR, 0, true},
	{T_ANY_EDGE,							_hoops_GRRCR ("on"),						_hoops_RRRCR, 0, false},
	{T_ANY_EDGE,							_hoops_GRRCR ("yes"),						_hoops_RRRCR, 0, false},
	{T_GENERIC_EDGES,						_hoops_GRRCR ("generic"),					_hoops_RRRCR, 0, true},
	{T_GENERIC_EDGES,						_hoops_GRRCR ("generics"),					_hoops_RRRCR, 0, true},
	{T_PERIMETER_EDGES,						_hoops_GRRCR ("perimeter"),					_hoops_RRRCR, 0, true},
	{T_PERIMETER_EDGES,						_hoops_GRRCR ("perimeters"),				_hoops_RRRCR, 0, true},
	{_hoops_CRHGP,						_hoops_GRRCR ("adjacent"),					_hoops_RRRCR, 0, true},
	{T_HARD_EDGES,							_hoops_GRRCR ("hard"),						_hoops_RRRCR, 0, true},
	{T_MESH_QUAD_EDGES,						_hoops_GRRCR ("mesh quad"),					_hoops_RRRCR, 0, true},
	{T_MESH_QUAD_EDGES,						_hoops_GRRCR ("mesh quads"),				_hoops_RRRCR, 0, true},
	{T_INTERIOR_SILHOUETTE_EDGES,			_hoops_GRRCR ("interior silhouette"),		_hoops_RRRCR, 0, true},
	{T_INTERIOR_SILHOUETTE_EDGES,			_hoops_GRRCR ("interior silhouettes"),		_hoops_RRRCR, 0, true},
	{_hoops_GCSI,						_hoops_GRRCR ("nonculled"),					_hoops_RRRCR, 0, true},

	{_hoops_HHSAA|T_PERIMETER_EDGES,			_hoops_GRRCR ("perimeter only"),			_hoops_RRRCR, 0, false},
	{_hoops_HHSAA|T_PERIMETER_EDGES,			_hoops_GRRCR ("perimeters only"),			_hoops_RRRCR, 0, false},
	{_hoops_HHSAA|_hoops_CRHGP,			_hoops_GRRCR ("adjacent only"),				_hoops_RRRCR, 0, false},
	{_hoops_HHSAA|T_HARD_EDGES,				_hoops_GRRCR ("hard only"),					_hoops_RRRCR, 0, false},
	{_hoops_HHSAA|T_MESH_QUAD_EDGES,			_hoops_GRRCR ("mesh quad only"),			_hoops_RRRCR, 0, false},
	{_hoops_HHSAA|T_MESH_QUAD_EDGES,			_hoops_GRRCR ("mesh quads only"),			_hoops_RRRCR, 0, false},
	{_hoops_HHSAA|T_INTERIOR_SILHOUETTE_EDGES, _hoops_GRRCR ("interior silhouette only"),	_hoops_RRRCR, 0, false},
	{_hoops_HHSAA|T_INTERIOR_SILHOUETTE_EDGES, _hoops_GRRCR ("interior silhouettes only"), _hoops_RRRCR, 0, false},
	{_hoops_HHSAA|_hoops_GCSI,			_hoops_GRRCR ("nonculled only"),			_hoops_RRRCR, 0, false},

	{_hoops_HHSAA|0,							_hoops_GRRCR ("off"),						_hoops_RRRCR, 0, false},
	{_hoops_HHSAA|0,							_hoops_GRRCR ("nothing"),					_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_SPCRGR = {
	_hoops_GGAPR (_hoops_CPCRGR),				_hoops_CPCRGR,
};


local const _hoops_IGRCR _hoops_GHCRGR[] = {
	{T_ANY_LIGHTS,				_hoops_GRRCR ("everything"),	_hoops_RRRCR, 0, false},
	{T_ANY_LIGHTS,				_hoops_GRRCR ("on"),			_hoops_RRRCR, 0, false},
	{T_ANY_LIGHTS,				_hoops_GRRCR ("yes"),			_hoops_RRRCR, 0, false},
	{T_LIGHTS_FOR_FACES,		_hoops_GRRCR ("face"),			_hoops_RRRCR, 0, true},
	{T_LIGHTS_FOR_FACES,		_hoops_GRRCR ("faces"),			_hoops_RRRCR, 0, true},
	{T_LIGHTS_FOR_EDGES,		_hoops_GRRCR ("edge"),			_hoops_RRRCR, 0, true},
	{T_LIGHTS_FOR_EDGES,		_hoops_GRRCR ("edges"),			_hoops_RRRCR, 0, true},
	{T_LIGHTS_FOR_MARKERS,		_hoops_GRRCR ("marker"),		_hoops_RRRCR, 0, true},
	{T_LIGHTS_FOR_MARKERS,		_hoops_GRRCR ("markers"),		_hoops_RRRCR, 0, true},
	{T_LIGHTS_FOR_MARKERS,		_hoops_GRRCR ("vertex"),		_hoops_RRRCR, 0, true},
	{T_LIGHTS_FOR_MARKERS,		_hoops_GRRCR ("vertices"),		_hoops_RRRCR, 0, true},
	{_hoops_HHSAA|0,				_hoops_GRRCR ("off"),			_hoops_RRRCR, 0, false},
	{_hoops_HHSAA|0,				_hoops_GRRCR ("nothing"),		_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_RHCRGR = {
	_hoops_GGAPR (_hoops_GHCRGR),			_hoops_GHCRGR,
};


/* (_hoops_HRPAI _hoops_GGR _hoops_AGR _hoops_IIGR _hoops_SISRP) */
local const _hoops_IGRCR _hoops_ISPRS[] = {
	{_hoops_CAHGP,	_hoops_GRRCR("on"),				_hoops_RRRCR, 0, false},
	{_hoops_CAHGP,	_hoops_GRRCR("everything"),		_hoops_RRRCR, 0, true},
	{_hoops_HHSAA|0,				_hoops_GRRCR("off"),			_hoops_RRRCR, 0, false},
	{_hoops_HHSAA|0,				_hoops_GRRCR("nothing"),		_hoops_RRRCR, 0, false},

	{_hoops_AAHGP,			_hoops_GRRCR("geometry"),		_hoops_RRRCR, 0, true},
	{T_FACES,					_hoops_GRRCR("face"),			_hoops_RRRCR, 0, true},
	{T_LINES,					_hoops_GRRCR("line"),			_hoops_RRRCR, 0, true},
	{T_LINES,					_hoops_GRRCR("polyline"),		_hoops_RRRCR, 0, true},
	{T_MARKERS,					_hoops_GRRCR("marker only"),	_hoops_RRRCR, 0, true},
	{T_VERTICES,				_hoops_GRRCR("vertex"),			_hoops_RRRCR, 0, true},
	{T_MARKERS|T_VERTICES,		_hoops_GRRCR("marker"),			_hoops_RRRCR, 0, true},
	{T_CUTTING_PLANES,			_hoops_GRRCR("cutting plane"),	_hoops_RRRCR, 0, true},
	{T_IMAGES,					_hoops_GRRCR("image"),			_hoops_RRRCR, 0, true},
	{T_IMAGES,					_hoops_GRRCR("pixel array"),	_hoops_RRRCR, 0, true},
	{T_FACES|T_ANY_EDGE,		_hoops_GRRCR("polygon"),		_hoops_RRRCR, 0, true},
	{T_TEXT,					_hoops_GRRCR("text"),			_hoops_RRRCR, 0, true},
	{T_STRING_CURSORS,			_hoops_GRRCR("string cursor"),	_hoops_RRRCR, 0, true},
	{T_WINDOWS,					_hoops_GRRCR("window"),			_hoops_RRRCR, 0, true},

	{T_FACES,					_hoops_GRRCR("faces"),			_hoops_RRRCR, 0, true},
	{T_LINES,					_hoops_GRRCR("lines"),			_hoops_RRRCR, 0, true},
	{T_LINES,					_hoops_GRRCR("polylines"),		_hoops_RRRCR, 0, true},
	{T_MARKERS,					_hoops_GRRCR("markers only"),	_hoops_RRRCR, 0, true},
	{T_VERTICES,				_hoops_GRRCR("vertices"),		_hoops_RRRCR, 0, true},
	{T_MARKERS|T_VERTICES,		_hoops_GRRCR("markers"),		_hoops_RRRCR, 0, true},
	{T_CUTTING_PLANES,			_hoops_GRRCR("cutting planes"), _hoops_RRRCR, 0, true},
	{T_IMAGES,					_hoops_GRRCR("images"),			_hoops_RRRCR, 0, true},
	{T_IMAGES,					_hoops_GRRCR("pixel arrays"),	_hoops_RRRCR, 0, true},
	{T_FACES|T_ANY_EDGE,		_hoops_GRRCR("polygons"),		_hoops_RRRCR, 0, true},
	{T_STRING_CURSORS,			_hoops_GRRCR("string cursors"), _hoops_RRRCR, 0, true},
	{T_WINDOWS,					_hoops_GRRCR("windows"),		_hoops_RRRCR, 0, true},

	{T_ANY_LIGHTS,				_hoops_GRRCR("light"),			_hoops_GHAGA, -999, true, &_hoops_RHCRGR},
	{T_ANY_LIGHTS,				_hoops_GRRCR("lighting"),		_hoops_GHAGA, -999, true, &_hoops_RHCRGR},
	{T_ANY_LIGHTS,				_hoops_GRRCR("lights"),			_hoops_GHAGA, -999, true, &_hoops_RHCRGR},

	{T_ANY_EDGE,				_hoops_GRRCR("edge"),			_hoops_GHAGA, -999, true, &_hoops_SPCRGR},
	{T_ANY_EDGE,				_hoops_GRRCR("edges"),			_hoops_GHAGA, -999, true, &_hoops_SPCRGR},

	{T_CUT_GEOMETRY,			_hoops_GRRCR ("cut geometry"),	_hoops_GHAGA, -999, true, &_hoops_IPCRGR},
#define _hoops_SASAA		_hoops_ASPCR	/* _hoops_GII _hoops_IGRH _hoops_HAR _hoops_IGI _hoops_IH _hoops_IRS _hoops_HPHR _hoops_HPRC */
	{_hoops_SASAA,				_hoops_GRRCR("cut edge"),		_hoops_RRRCR, 0, true},
	{_hoops_SASAA,				_hoops_GRRCR("cut edges"),		_hoops_RRRCR, 0, true},

	{T_ANY_SHADOW,				_hoops_GRRCR ("shadow"),		_hoops_GHAGA, -999, true, &_hoops_PPCRGR},
	{T_ANY_SHADOW,				_hoops_GRRCR ("shadows"),		_hoops_GHAGA, -999, true, &_hoops_PPCRGR},
};



local Attribute *_hoops_AHCRGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute *				_hoops_SPACR)
{
	_hoops_RSAIR const *		_hoops_PHCRGR = (_hoops_RSAIR const *)_hoops_CPACR;
	_hoops_RSAIR alter *		_hoops_GCCSC = (_hoops_RSAIR alter *)_hoops_SPACR;

	UNREFERENCED (item);

	ASSERT(_hoops_GCCSC->type == HK_VISIBILITY);

	if (_hoops_PHCRGR != null &&
		_hoops_PHCRGR->mask == _hoops_GCCSC->mask &&
		_hoops_PHCRGR->value == _hoops_GCCSC->value &&
		_hoops_PHCRGR->_hoops_PRIGA.mask == _hoops_GCCSC->_hoops_PRIGA.mask &&
		_hoops_PHCRGR->_hoops_PRIGA.value == _hoops_GCCSC->_hoops_PRIGA.value &&
		_hoops_PHCRGR->_hoops_SPSS.mask == _hoops_GCCSC->_hoops_SPSS.mask &&
		_hoops_PHCRGR->_hoops_SPSS.value == _hoops_GCCSC->_hoops_SPSS.value)
		return null;


	_hoops_ACHR	_hoops_RCGC = 0;

	if (_hoops_PHCRGR != null) {
		_hoops_GCCSC->value |= (_hoops_PHCRGR->value & ~_hoops_GCCSC->mask);
		_hoops_GCCSC->mask |= _hoops_PHCRGR->mask;

		_hoops_GCCSC->_hoops_PRIGA.value |= (_hoops_PHCRGR->_hoops_PRIGA.value & ~_hoops_GCCSC->_hoops_PRIGA.mask);
		_hoops_GCCSC->_hoops_PRIGA.mask |= _hoops_PHCRGR->_hoops_PRIGA.mask;

		_hoops_GCCSC->_hoops_SPSS.value |= (_hoops_PHCRGR->_hoops_SPSS.value & ~_hoops_GCCSC->_hoops_SPSS.mask);
		_hoops_GCCSC->_hoops_SPSS.mask |= _hoops_PHCRGR->_hoops_SPSS.mask;
	}


	if (ANYBIT (_hoops_GCCSC->value, _hoops_AAHGP) ||
		(ANYBIT (_hoops_GCCSC->value, T_CUT_GEOMETRY) &&
		 ANYBIT (_hoops_GCCSC->_hoops_PRIGA.value, T_FACES|T_LINES)))
		_hoops_RCGC |= _hoops_APHGP;

	if (BIT (_hoops_GCCSC->value, T_WINDOWS))
		_hoops_RCGC |= _hoops_HPHGP;

	_hoops_CRCP * _hoops_SRCP = (_hoops_CRCP *)item;
	while (_hoops_SRCP != null && _hoops_SRCP->type != _hoops_IRCP)
		_hoops_SRCP = _hoops_SRCP->owner;

	if (_hoops_SRCP != null && !ALLBITS (_hoops_SRCP->_hoops_RCGC, _hoops_RCGC))
		HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_RCGC);

	return _hoops_GCCSC;
}


local bool _hoops_HHCRGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				target,
	char const *			list,
	_hoops_RSAIR *			_hoops_APHCR)
{
	ASSERT(target != null);

	Option_Value *	option_list;
	Option_Value *	option;

	_hoops_HIACR (_hoops_CPSAA, _hoops_ISPRS);

	if (!HI_Parse_Options (_hoops_RIGC, list, _hoops_CIACR (_hoops_CPSAA), &option_list, _hoops_SIACR))
		return false;

	if ((option = option_list) == null)
		return false;

	int	_hoops_IHCRGR = _hoops_CAHGP;

	if (target->type == _hoops_CIRIR) {
		_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)target;

		switch (_hoops_ASIIR->_hoops_GCRIR) {
			case _hoops_GSRIR:
			case _hoops_ICRIR:
				_hoops_IHCRGR = T_FACES;
			break;

			case _hoops_CCRIR:
				_hoops_IHCRGR = T_ANY_EDGE;
			break;

			case _hoops_SCRIR:
				_hoops_IHCRGR = T_MARKERS|T_VERTICES;
			break;

			default: break;
		}
	}

	do {
		_hoops_ACHR	mask = (_hoops_ACHR)option->type->id;

		if (mask == _hoops_SASAA) {		/* _hoops_GCGH _hoops_RHGS _hoops_PIPPR */
			_hoops_APHCR->mask |= T_CUT_GEOMETRY;
			_hoops_APHCR->value |= T_CUT_GEOMETRY;
			_hoops_APHCR->_hoops_PRIGA.mask |= T_LINES;
			if (option->_hoops_GCACR)
				_hoops_APHCR->_hoops_PRIGA.value &= ~T_LINES;
			else
				_hoops_APHCR->_hoops_PRIGA.value |= T_LINES;
		}
		else if (mask == T_CUT_GEOMETRY) {
			_hoops_APHCR->mask |= mask;
			if (option->_hoops_GCACR) {
				_hoops_APHCR->value &= ~mask;
				_hoops_APHCR->_hoops_PRIGA.mask = T_LINES|T_FACES;
				_hoops_APHCR->_hoops_PRIGA.value = 0;
			}
			else {
				if (option->value.option_list != null) {
					Option_Value *_hoops_AHSAA = option->value.option_list;

					do {
						_hoops_ACHR	_hoops_PHSAA = (_hoops_ACHR)_hoops_AHSAA->type->id;

						if (_hoops_PHSAA == 0) {
							_hoops_APHCR->value &= ~mask;

							_hoops_APHCR->_hoops_PRIGA.mask = 0;
							_hoops_APHCR->_hoops_PRIGA.value = 0;
						}
						else {
							_hoops_APHCR->value |= mask;

							/* _hoops_HIGAA _hoops_RGR _hoops_RGSR */
							_hoops_APHCR->_hoops_PRIGA.mask |= _hoops_PHSAA;
							if (_hoops_AHSAA->_hoops_GCACR)
								_hoops_APHCR->_hoops_PRIGA.value &= ~_hoops_PHSAA;
							else
								_hoops_APHCR->_hoops_PRIGA.value |= _hoops_PHSAA;
						}
					} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
				}
				else {
					_hoops_APHCR->value |= mask;
					_hoops_APHCR->_hoops_PRIGA.mask = T_LINES|T_FACES;
					_hoops_APHCR->_hoops_PRIGA.value = T_LINES|T_FACES;
				}
			}
		}
		else if (mask == T_ANY_SHADOW) {
			_hoops_APHCR->mask |= mask;
			if (option->_hoops_GCACR) {
				_hoops_APHCR->value &= ~mask;
				_hoops_APHCR->_hoops_SPSS.mask = _hoops_RIHGP;
				_hoops_APHCR->_hoops_SPSS.value = 0;
			}
			else {
				_hoops_APHCR->value |= mask;

				if (option->value.option_list != null) {
					Option_Value *_hoops_AHSAA = option->value.option_list;

					do {
						_hoops_ACHR	_hoops_PHSAA = (_hoops_ACHR)_hoops_AHSAA->type->id;

						if (_hoops_PHSAA == 0) {
							_hoops_APHCR->_hoops_SPSS.mask = _hoops_RIHGP;
							_hoops_APHCR->_hoops_SPSS.value = 0;
						}
						else {
							/* _hoops_HIGAA _hoops_RGR _hoops_RGSR */
							_hoops_APHCR->_hoops_SPSS.mask |= _hoops_PHSAA;
							if (_hoops_AHSAA->_hoops_GCACR)
								_hoops_APHCR->_hoops_SPSS.value &= ~_hoops_PHSAA;
							else
								_hoops_APHCR->_hoops_SPSS.value |= _hoops_PHSAA;
						}
					} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
				}
				else {
					_hoops_APHCR->_hoops_SPSS.mask = _hoops_RIHGP;
					_hoops_APHCR->_hoops_SPSS.value = _hoops_RIHGP;
				}
			}
		}
		else if (option->type->_hoops_RCIIR == _hoops_GHAGA &&
				option->value.option_list != null) {
			/* _hoops_ARAS _hoops_RHIR _hoops_IRS _hoops_ARAH-_hoops_HIGR */

			Option_Value *_hoops_AHSAA = option->value.option_list;

			do {
				_hoops_ACHR	_hoops_PHSAA = (_hoops_ACHR)_hoops_AHSAA->type->id;

				if (BIT (_hoops_PHSAA, _hoops_HHSAA)) {
					/* "_hoops_IHSAA" _hoops_AGSR "_hoops_HHSA _hoops_RH _hoops_SHSC _hoops_PAIP _hoops_IS
					 * _hoops_RGR _hoops_PIRA" _hoops_HRII _hoops_HSAR "_hoops_HIGAA _hoops_RGR _hoops_SPR _hoops_IGRH."
					 *
					 * _hoops_IPCP "_hoops_SHSC _hoops_PAIP" _hoops_HRGR _hoops_RH _hoops_CRIPR _hoops_PISH _hoops_HPGR _hoops_RGR _hoops_PSSPR _hoops_PAPA.
					 */
					_hoops_APHCR->mask |= mask;
					_hoops_APHCR->value &= ~mask;
					if (!_hoops_AHSAA->_hoops_GCACR) _hoops_APHCR->value |= (_hoops_PHSAA & ~_hoops_HHSAA);
				}
				else {
					/* _hoops_HIGAA _hoops_RGR _hoops_SPR _hoops_IGRH. */
					_hoops_APHCR->mask |= _hoops_PHSAA;
					if (_hoops_AHSAA->_hoops_GCACR)
						_hoops_APHCR->value &= ~_hoops_PHSAA;
					else
						_hoops_APHCR->value |= _hoops_PHSAA;
				}
			} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
		}
		else if (BIT (mask, _hoops_HHSAA)) {
			/* "_hoops_IHSAA" _hoops_AGSR "_hoops_HHSA _hoops_RH _hoops_SHSC _hoops_PAIP _hoops_IS
			 * _hoops_RGR _hoops_PIRA" _hoops_HRII _hoops_HSAR "_hoops_HIGAA _hoops_RGR _hoops_SPR _hoops_IGRH."
			 *
			 * _hoops_IPCP "_hoops_SHSC _hoops_PAIP" _hoops_HRGR _hoops_CPS, _hoops_HIH _hoops_RGAR _hoops_RIP _hoops_AGAP _hoops_CGSI
			 * _hoops_IRPR _hoops_IH _hoops_ISCP _hoops_SCGR _hoops_IGS _hoops_PAPA
			 */
			_hoops_APHCR->mask = _hoops_IHCRGR;
			_hoops_APHCR->value = 0;
		}
		else {
			/* _hoops_HIGAA _hoops_RGR _hoops_HCSP */

			if (mask == _hoops_CAHGP) {
				/* _hoops_SHIR _hoops_IH _hoops_ISCP _hoops_IGS _hoops_PAPA */
				mask = _hoops_IHCRGR;
			}

			_hoops_APHCR->mask |= mask;
			if (option->_hoops_GCACR)
				_hoops_APHCR->value &= ~mask;
			else {
				_hoops_APHCR->value |= mask;
				if (BIT (mask, T_ANY_SHADOW)) {
					_hoops_APHCR->_hoops_SPSS.mask = _hoops_RIHGP;
					_hoops_APHCR->_hoops_SPSS.value = _hoops_RIHGP;
				}
				if (BIT (mask, T_CUT_GEOMETRY)) {
					_hoops_APHCR->_hoops_PRIGA.mask = T_FACES|T_LINES;
					_hoops_APHCR->_hoops_PRIGA.value = T_FACES|T_LINES;
				}
			}
		}
	} while ((option = option->next) != null);

	HI_Free_Option_List (_hoops_RIGC, option_list);

	return true;
}


local void _hoops_CHCRGR (_hoops_AIGPR * _hoops_RIGC, Polyhedron *_hoops_IPRI, _hoops_PIHGP _hoops_PHSI)
{
	if (_hoops_IPRI->owner &&
		_hoops_IPRI->owner->type == _hoops_IRCP) {

		_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)_hoops_IPRI->owner;

		_hoops_SRCP->_hoops_PHSI |= _hoops_PHSI;

		_hoops_RPAPA * _hoops_APAPA = HOOPS_WORLD->_hoops_PPAPA->Lookup(_hoops_SRCP);

		if (_hoops_APAPA != null) {
			_hoops_APAPA->ResetCursor();
			_hoops_PHIP *	_hoops_RRA;
			while ((_hoops_RRA = _hoops_APAPA->PeekCursor()) != null) {
				HI_Invalidate_Segment_Display_Lists (_hoops_RIGC, _hoops_RRA->owner, -2, null, 0);
				_hoops_RRA->owner->_hoops_PHSI |= _hoops_PHSI;
				_hoops_APAPA->AdvanceCursor();
			}
		}

		_hoops_APAPA = HOOPS_WORLD->_hoops_PPAPA->Lookup(_hoops_IPRI);

		if (_hoops_APAPA != null) {
			_hoops_APAPA->ResetCursor();
			_hoops_PHIP *	_hoops_RRA;
			while ((_hoops_RRA = _hoops_APAPA->PeekCursor()) != null) {
				HI_Invalidate_Segment_Display_Lists (_hoops_RIGC, _hoops_RRA->owner, -2, null, 0);
				_hoops_RRA->owner->_hoops_PHSI |= _hoops_PHSI;
				_hoops_APAPA->AdvanceCursor();
			}
		}
	}

	HI_Invalidate_Display_Lists (_hoops_RIGC, _hoops_IPRI);
}




/* (_hoops_RH _hoops_HSPR _hoops_CIGR _hoops_HCHRC _hoops_HII _hoops_HCHHC) */
#define _hoops_HIHHC(_hoops_RSPGP,_hoops_ICHHC,x)	(BIT (_hoops_ICHHC->_hoops_CPGPR, _hoops_CASIR) ? \
		_hoops_IIHHC (_hoops_RSPGP, _hoops_ICHHC,x) : _hoops_SASIR (_hoops_RSPGP, _hoops_ICHHC, _hoops_RAGGA | (x)))

#define _hoops_IIHHC(_hoops_RSPGP,_hoops_ICHHC,x) _hoops_SASIR (_hoops_RSPGP, _hoops_ICHHC, _hoops_GGARA | (x))

#define _hoops_PASGS(_hoops_RSPGP,_hoops_SRCP,x)	(BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR) ? \
		_hoops_HASGS (_hoops_RSPGP,_hoops_SRCP,x) : \
		_hoops_SASIR (_hoops_RSPGP, _hoops_SRCP, _hoops_AISSR | (x)))

#define _hoops_HASGS(_hoops_RSPGP,_hoops_SRCP,x)	_hoops_SASIR (_hoops_RSPGP, _hoops_SRCP, \
										_hoops_GPSIR | (x))



GLOBAL_FUNCTION bool HI_Set_Visibility(
	_hoops_AIGPR *	_hoops_RIGC,
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_IPRRA				_hoops_GCRIR,
	_hoops_RSAIR *			_hoops_APHCR)
{
	_hoops_ICIIR(_hoops_RIGC);

	ASSERT(_hoops_GCRIR == _hoops_ICRIR || _hoops_GCRIR == _hoops_SCRIR || _hoops_GCRIR == _hoops_CCRIR || _hoops_GCRIR == _hoops_GSRIR);

#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc Attributes");
#else

	_hoops_ACHR value = _hoops_APHCR->value;

	if (_hoops_GCRIR == _hoops_SCRIR) {
		bool		_hoops_CCCIR = false;
		_hoops_PIHGP	_hoops_PHSI = 0;

		if (ANYBIT (_hoops_APHCR->mask, ~(T_MARKERS|T_VERTICES))) {
			HE_WARNING (HEC_VISIBILITY, HES_OPEN_VERTEX_ONLY, "Only 'marker'/'vertex' visibility may be set on an open vertex");
			if (!BIT (_hoops_APHCR->mask, T_MARKERS))
				goto _hoops_PRSPR;
			value &= T_VERTICES;
		}

		Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

		if (_hoops_IPRI->local_vertex_attributes.flags == null)
			HI_Initialize_Vertex_Attributes (_hoops_IPRI, false, 0);

		Local_Vertex_Flags *	flags = _hoops_IPRI->local_vertex_attributes._hoops_CHHPR(offset);

		/* _hoops_APSH _hoops_PII _hoops_SR'_hoops_ASAR _hoops_AHCA _hoops_IS _hoops_ARP _hoops_IRS _hoops_HPRC _hoops_GPP _hoops_SAHR _hoops_SPR _hoops_GPHA, _hoops_HIS
			_hoops_SR'_hoops_GCPP _hoops_PAHH _hoops_RRP _hoops_IRS _hoops_IIRRA->_hoops_SGI _hoops_CRPR */
		if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
			ZALLOC_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
			for (int i = 0; i < _hoops_IPRI->point_count; i++)
				_hoops_IPRI->local_vertex_attributes.flags[i] = _hoops_IPRI->local_vertex_attributes._hoops_SGRHR;
			_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
			flags = _hoops_IPRI->local_vertex_attributes._hoops_CHHPR(offset);
		}

		if (value != 0) { /* _hoops_IAHAR _hoops_SCH _hoops_GPP */
			if (!BIT (*flags, _hoops_PHIAA)) {
				if (BIT (*flags, _hoops_HHIAA)) {
					*flags &= ~_hoops_HHIAA;
					--_hoops_IPRI->local_vertex_attributes._hoops_SIIPR;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HHIAA;
				}
				*flags |= _hoops_PHIAA;
				_hoops_PHSI |= _hoops_HHSI;
				_hoops_CCCIR = true;

				++_hoops_IPRI->local_vertex_attributes._hoops_CPIAA;
				_hoops_IPRI->_hoops_AGRHR &= ~_hoops_PHIAA;

				_hoops_IIHHC (_hoops_RIGC, _hoops_IPRI, _hoops_RPSIR);
			}
		}
		else {
			if (!BIT (*flags, _hoops_HHIAA)) {
				if (BIT (*flags, _hoops_PHIAA)) {
					*flags &= ~_hoops_PHIAA;
					--_hoops_IPRI->local_vertex_attributes._hoops_CPIAA;
					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_PHIAA;
				}
				*flags |= _hoops_HHIAA;
				_hoops_CCCIR = true;

				++_hoops_IPRI->local_vertex_attributes._hoops_SIIPR;
				_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HHIAA;

				_hoops_HIHHC (_hoops_RIGC, _hoops_IPRI, _hoops_RPSIR);
			}
		}

		if (_hoops_SPRI->lvf_uniform(_hoops_IPRI->point_count)) {
			_hoops_SPRI->_hoops_SGRHR = _hoops_SPRI->flags[0];
			FREE_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
			_hoops_IPRI->polyhedron_flags &= ~_hoops_CGRHR;
			_hoops_SPRI->flags = 0;
		}

		if (_hoops_CCCIR)
			_hoops_CHCRGR (_hoops_RIGC, _hoops_IPRI, _hoops_PHSI);

		/* _hoops_RRRPR _hoops_IIGR _hoops_SPIGA _hoops_HHS _hoops_SHH _hoops_IRAP */
		if (_hoops_IPRI->owner) {
			if (value != 0 && !BIT (_hoops_IPRI->owner->_hoops_RCGC, _hoops_APHGP))
				HI_Propagate_Maybes (_hoops_RIGC, _hoops_IPRI->owner, _hoops_APHGP);
		}
	}
	else if (_hoops_GCRIR == _hoops_CCRIR) {
		_hoops_PIHGP	_hoops_PHSI = 0;
		bool		_hoops_CCCIR = false;

		if (_hoops_APHCR->mask != (T_ANY_EDGE)) {
			HE_WARNING (HEC_VISIBILITY, HES_OPEN_EDGE_ONLY, "Only 'edge' visibility may be set on an open edge");
			if (!ANYBIT (_hoops_APHCR->mask, T_ANY_EDGE))
				goto _hoops_PRSPR;
			value &= T_ANY_EDGE;
		}

		if (_hoops_APHCR->mask == T_INTERIOR_SILHOUETTE_EDGES) { /* _hoops_SHCRGR. _hoops_GPP _hoops_HIH _hoops_SPPR _hoops_PSAP */
			HE_ERROR (HEC_VISIBILITY, HES_INVALID_INPUT, "'edge' visibility may only be set 'off' or 'on'");
			goto _hoops_PRSPR;
		}

		if (_hoops_IPRI->_hoops_IHHPR.flags == null)
			HI_Initialize_Edge_Attributes (_hoops_IPRI, false);

		_hoops_GHHPR *	flags = &_hoops_IPRI->_hoops_IHHPR.flags[offset];

		if (value != 0) {
			// _hoops_AGSGR _hoops_HPRC _hoops_PRARH _hoops_GPP
			if (!BIT (*flags, _hoops_APGI)) {
				if (BIT (*flags, _hoops_AHIAA)) {
					*flags &= ~_hoops_AHIAA;
					--_hoops_IPRI->_hoops_IHHPR._hoops_SIIPR;
					_hoops_IPRI->_hoops_RSHPR &= ~_hoops_AHIAA;
				}
				*flags |= _hoops_APGI;
				_hoops_CCCIR = true;
				_hoops_PHSI |= _hoops_HHSI;
				++_hoops_IPRI->_hoops_IHHPR._hoops_CPIAA;
				_hoops_IPRI->_hoops_RSHPR &= ~_hoops_APGI;
				_hoops_IIHHC (_hoops_RIGC, _hoops_IPRI, _hoops_RPSIR);
			}
		}
		else {
			/*
			 * _hoops_AGSGR _hoops_HPRC _hoops_PRARH _hoops_PSAP
			 */
			if (!BIT (*flags, _hoops_AHIAA)) {
				if (BIT (*flags, _hoops_APGI)) {
					*flags &= ~_hoops_APGI;
					--_hoops_IPRI->_hoops_IHHPR._hoops_CPIAA;
					_hoops_IPRI->_hoops_RSHPR &= ~_hoops_APGI;
				}
				*flags |= _hoops_AHIAA;
				_hoops_CCCIR = true;
				++_hoops_IPRI->_hoops_IHHPR._hoops_SIIPR;
				_hoops_IPRI->_hoops_RSHPR &= ~_hoops_AHIAA;
				_hoops_HIHHC (_hoops_RIGC, _hoops_IPRI, _hoops_RPSIR);
			}
		}

		if (_hoops_CCCIR)
			_hoops_CHCRGR (_hoops_RIGC, _hoops_IPRI, _hoops_PHSI);

		/* _hoops_RRRPR _hoops_IIGR _hoops_SPIGA _hoops_HHS _hoops_SHH _hoops_IRAP */
		if (_hoops_IPRI->owner) {
			if (value != 0 && !BIT (_hoops_IPRI->owner->_hoops_RCGC, _hoops_APHGP))
				HI_Propagate_Maybes (_hoops_RIGC, _hoops_IPRI->owner, _hoops_APHGP);
		}
	}
	else if (_hoops_GCRIR == _hoops_GSRIR) {
		_hoops_PIHGP	_hoops_PHSI = 0;
		bool		_hoops_CCCIR = false;
		bool		erase = false;

		if (_hoops_APHCR->mask != T_FACES) {
			HE_WARNING (HEC_VISIBILITY, HES_OPEN_FACE_ONLY, "Only 'face' visibility may be set on an open region");
			if (!BIT (_hoops_APHCR->mask, T_FACES))
				goto _hoops_PRSPR;
			value &= T_FACES;
		}

		int const *	regions = _hoops_IPRI->local_face_attributes.regions;

		if (regions == null && offset != 0)
			goto _hoops_PRSPR; /* _hoops_HCR _hoops_RSSI _hoops_GGR _hoops_SHIR _hoops_ISPH, _hoops_IAGC _hoops_GPGH'_hoops_RA */

		if (*_hoops_IPRI->local_face_attributes._hoops_CHHPR() == 0)
			HI_Initialize_Face_Attributes (_hoops_IPRI, false);

		if (regions != null) {
			/* _hoops_SR _hoops_CHR _hoops_AHCA _hoops_IS _hoops_ARP _hoops_IRS _hoops_HPRC _hoops_GPP _hoops_HAR _hoops_HCR
				_hoops_IIGR _hoops_RH _hoops_RSSI, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IRS _hoops_HSP _hoops_SGI _hoops_CRPR
				_hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_AIAH _hoops_HS _hoops_SPR */
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
				ZALLOC_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
				for (int i = 0; i < _hoops_IPRI->face_count; i++)
					_hoops_IPRI->local_face_attributes.flags[i] = _hoops_IPRI->local_face_attributes._hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
			}
		}

		for (int i=0; i<_hoops_IPRI->face_count; i++) {
			if (regions == null || regions[i] == offset) {
				_hoops_GIIPR *	flags = ((Polyhedron*)_hoops_IPRI)->local_face_attributes._hoops_CHHPR(i);

				if (value != 0) { /* _hoops_IAHAR _hoops_SCH _hoops_GPP */
					if (!BIT (*flags, _hoops_IAGI)) {
						if (BIT (*flags, _hoops_HSIPR)) {
							*flags &= ~_hoops_HSIPR;
							--_hoops_IPRI->local_face_attributes._hoops_SIIPR;

							_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR|_hoops_CIIPR);
						}
						*flags |= _hoops_IAGI;
						*flags |= _hoops_IGAHR;
						++_hoops_IPRI->local_face_attributes._hoops_CPIAA;
						_hoops_PHSI |= _hoops_HHSI;

						/*
						 * _hoops_PAGA: _hoops_GICRGR _hoops_HRGR _hoops_IPIH _hoops_RAICR
						 *	   _hoops_ARPP _hoops_GRHGP _hoops_HRGR _hoops_RAICR, _hoops_HIS _hoops_SCH _hoops_RRP _hoops_HAR _hoops_SHH
						 *	   _hoops_GCGSP _hoops_ARI.
						 */
						_hoops_CCCIR = true;
					}
				}
				else {
					if (!BIT (*flags, _hoops_HSIPR)) {
						if (BIT (*flags, _hoops_IAGI)) {
							*flags &= ~_hoops_IAGI;
							--_hoops_IPRI->local_face_attributes._hoops_CPIAA;
						}
						*flags |= _hoops_HSIPR;
						*flags |= _hoops_IGAHR;
						++_hoops_IPRI->local_face_attributes._hoops_SIIPR;

						_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR|_hoops_CIIPR);

						/*
						 * _hoops_PAGA: _hoops_GICRGR _hoops_HRGR _hoops_IPIH _hoops_RAICR
						 *	   _hoops_ARPP _hoops_GRHGP _hoops_HRGR _hoops_RAICR, _hoops_HIS _hoops_SCH _hoops_RRP _hoops_HAR _hoops_SHH
						 *	   _hoops_GCGSP _hoops_ARI.
						 */
						_hoops_CCCIR = erase = true;
					}
				}
			}
		}

		/* _hoops_RRRPR _hoops_IIGR _hoops_SPIGA _hoops_HHS _hoops_SHH _hoops_IRAP */
		if (_hoops_IPRI->owner) {
			if (value != 0 && !BIT (_hoops_IPRI->owner->_hoops_RCGC, _hoops_APHGP))
				HI_Propagate_Maybes (_hoops_RIGC, _hoops_IPRI->owner, _hoops_APHGP);
		}
		if (_hoops_CCCIR) {
			_hoops_CHCRGR (_hoops_RIGC, _hoops_IPRI, _hoops_PHSI);
			if (_hoops_IPRI->tristrips != null) {
				if (!BIT (HOOPS_WORLD->system_flags, _hoops_CSRRA))
						_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;
				else {
					Tristrip *			ts = _hoops_IPRI->tristrips;
					_hoops_GIIPR		flag;

					flag = erase ? _hoops_HSIPR : _hoops_IAGI;

					do if (ts->face_attributes.region == offset) {
						ts->face_attributes.flags &= ~_hoops_HRAPA;
						ts->face_attributes.flags |= flag;

						ts->_hoops_CPGPR |= _hoops_GPSIR;
					} while ((ts = ts->next) != null);
				}
			}
			if (_hoops_IPRI->local_vertex_attributes._hoops_SIRHR > 0)
				_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
		}

		if (erase)
			_hoops_PASGS (_hoops_RIGC, _hoops_IPRI, _hoops_RPSIR);
		else if (_hoops_CCCIR)
			_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
	}
	else if (_hoops_GCRIR == _hoops_ICRIR) {
		_hoops_PIHGP	_hoops_PHSI = 0;
		bool		_hoops_CCCIR = false;
		bool		erase = false;

		if (_hoops_APHCR->mask != T_FACES) {
			HE_WARNING (HEC_VISIBILITY, HES_OPEN_FACE_ONLY, "Only 'face' visibility may be set on an open face");
			if (!BIT (_hoops_APHCR->mask, T_FACES))
				goto _hoops_PRSPR;
			value &= T_FACES;
		}

		/* _hoops_APSH _hoops_PII _hoops_SR'_hoops_ASAR _hoops_AHCA _hoops_IS _hoops_ARP _hoops_IRS _hoops_HPRC _hoops_GPP _hoops_SAHR _hoops_SPR _hoops_HSP, _hoops_HIS
			_hoops_SR'_hoops_GCPP _hoops_PAHH _hoops_RRP _hoops_IRS _hoops_RHRHR->_hoops_SGI _hoops_CRPR */
		if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
			ZALLOC_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
			for (int i = 0; i < _hoops_IPRI->face_count; i++)
				_hoops_IPRI->local_face_attributes.flags[i] = _hoops_IPRI->local_face_attributes._hoops_SGRHR;
			_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
		}

		if (_hoops_IPRI->local_face_attributes._hoops_CHHPR() == null)
			HI_Initialize_Face_Attributes (_hoops_IPRI, false);

		_hoops_GIIPR *	flags = _hoops_IPRI->local_face_attributes._hoops_CHHPR(offset);

		/*
		 * _hoops_PAGA: _hoops_GICRGR _hoops_HRGR _hoops_IPIH _hoops_RAICR
		 *	   _hoops_ARPP _hoops_GRHGP _hoops_HRGR _hoops_RAICR, _hoops_HIS _hoops_SCH _hoops_RRP _hoops_HAR _hoops_SHH
		 *	   _hoops_GCGSP _hoops_ARI.
		 */
		if (value != 0) { /* _hoops_IAHAR _hoops_SCH _hoops_GPP */
			if (!BIT (*flags, _hoops_IAGI)) {
				if (BIT (*flags, _hoops_HSIPR)) {
					*flags &= ~_hoops_HSIPR;
					--_hoops_IPRI->local_face_attributes._hoops_SIIPR;
					_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
				}
				*flags |= _hoops_IAGI;
				*flags |= _hoops_IGAHR;
				++_hoops_IPRI->local_face_attributes._hoops_CPIAA;
				_hoops_CCCIR = true;
				_hoops_PHSI |= _hoops_HHSI;
			}
		}
		else {
			if (!BIT (*flags, _hoops_HSIPR)) {
				if (BIT (*flags, _hoops_IAGI)) {
					*flags &= ~_hoops_IAGI;
					--_hoops_IPRI->local_face_attributes._hoops_CPIAA;
				}
				*flags |= _hoops_HSIPR;
				*flags |= _hoops_IGAHR;
				++_hoops_IPRI->local_face_attributes._hoops_SIIPR;
				_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
				_hoops_CCCIR = erase = true;
			}
		}

		/* _hoops_RRRPR _hoops_IIGR _hoops_SPIGA _hoops_HHS _hoops_SHH _hoops_IRAP */
		if (_hoops_IPRI->owner) {
			if (value != 0 && !BIT (_hoops_IPRI->owner->_hoops_RCGC, _hoops_APHGP))
				HI_Propagate_Maybes (_hoops_RIGC, _hoops_IPRI->owner, _hoops_APHGP);
		}

		if (_hoops_CCCIR) {
			_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;
			_hoops_CHCRGR (_hoops_RIGC, _hoops_IPRI, _hoops_PHSI);
			if (_hoops_IPRI->local_vertex_attributes._hoops_SIRHR > 0)
				_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
		}

		if (erase)
			_hoops_PASGS (_hoops_RIGC, _hoops_IPRI, _hoops_RPSIR);
		else if (_hoops_CCCIR)
			_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
	}
	else
		ASSERT(0);
_hoops_PRSPR:
#endif
	return false;
}

GLOBAL_FUNCTION bool HI_Set_Visibility (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_RSAIR *			_hoops_RGP)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_VISIBILITY, _hoops_AHCRGR, _hoops_RGP);
}

GLOBAL_FUNCTION bool HI_Unset_Visibility (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_RSAIR *			_hoops_RGP)
{
	/* _hoops_RRGRA */
	UNREFERENCED(_hoops_RIGC);
	UNREFERENCED(item);
	UNREFERENCED(_hoops_RGP);
	return false;
}

HC_INTERFACE void HC_CDECL HC_Set_Visibility (
	char const *			list)
{
	_hoops_PAPPR context("Set_Visibility");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Visibility (%S);\n", list));
	);



	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_AHRPP)) != null) {
		bool			used = false;
		_hoops_RSAIR *	vis;
		ZALLOC (vis, _hoops_RSAIR);
		vis->type = HK_VISIBILITY;

		if (_hoops_HHCRGR (context, target, list, vis)) {
			if (target->type == _hoops_CIRIR) {
				_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)target;
				used = HI_Set_Visibility(context, _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR,
							_hoops_ASIIR->info._hoops_IPRI.offset, _hoops_ASIIR->_hoops_GCRIR, vis);
			}
			else
				used = HI_Set_Visibility(context, target, vis);
		}

		if (!used)
			FREE (vis, _hoops_RSAIR);

		_hoops_IRRPR();
	}
}

GLOBAL_FUNCTION void HI_UnSet_Visibility(
	_hoops_AIGPR *	_hoops_RIGC,
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_IPRRA				_hoops_GCRIR)
{
	_hoops_ICIIR(_hoops_RIGC);

#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc Attributes");
#else

	if (_hoops_GCRIR == _hoops_SCRIR) {
		Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
		Local_Vertex_Flags *		flags = _hoops_SPRI->_hoops_CHHPR(offset);

		if (!BIT (*flags, _hoops_PHIAA|_hoops_HHIAA)) {
			HE_ERROR (HEC_VERTEX, HES_VISIBILITY, "No visibility set on this vertex");
			return;
		}
		if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
			/* _hoops_SR _hoops_HS _hoops_SAHR _hoops_IPPRA _hoops_IRS _hoops_RHPC _hoops_GPP _hoops_IRS _hoops_RSRA _hoops_GPHA.  _hoops_CGP _hoops_RIAGR _hoops_RPII _hoops_GRP _hoops_RH
			_hoops_GHRHR _hoops_RIP, _hoops_SR _hoops_PAH'_hoops_RA _hoops_CPRIR _hoops_PPR _hoops_SR _hoops_HS _hoops_IS _hoops_CCPP _hoops_RH _hoops_IIRRA->_hoops_SGI _hoops_CRPR (_hoops_PPR _hoops_HSPC _hoops_SCH _hoops_IS _hoops_RH _hoops_GHRHR _hoops_RIP)*/
			ZALLOC_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
			for (int i = 0; i < _hoops_IPRI->point_count; i++)
				_hoops_IPRI->local_vertex_attributes.flags[i] = _hoops_IPRI->local_vertex_attributes._hoops_SGRHR;
			_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
			flags = _hoops_SPRI->_hoops_CHHPR(offset);
		}

		if (BIT (*flags, _hoops_PHIAA)) {
			--_hoops_SPRI->_hoops_CPIAA;
			_hoops_IPRI->_hoops_AGRHR &= ~_hoops_PHIAA;
		}
		else {
			--_hoops_SPRI->_hoops_SIIPR;
			_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HHIAA;
		}

		*flags &= ~(_hoops_PHIAA|_hoops_HHIAA);

		if (_hoops_SPRI->lvf_uniform(_hoops_IPRI->point_count)) {
			_hoops_SPRI->_hoops_SGRHR = _hoops_SPRI->flags[0];
			FREE_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
			_hoops_IPRI->polyhedron_flags &= ~_hoops_CGRHR;
			_hoops_SPRI->flags = 0;
		}


		_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_RAGGA|_hoops_RPSIR);
	}
	else if (_hoops_GCRIR == _hoops_CCRIR) {
		_hoops_GHHPR *	flags;

		if ((flags = _hoops_IPRI->_hoops_IHHPR.flags) == null ||
			!BIT (flags[offset], _hoops_APGI|_hoops_AHIAA)) {
			HE_ERROR (HEC_EDGE, HES_VISIBILITY, "No visibility set on this edge");
			return;
		}

		if (BIT (flags[offset], _hoops_APGI)) {
			--_hoops_IPRI->_hoops_IHHPR._hoops_CPIAA;
			_hoops_IPRI->_hoops_RSHPR &= ~_hoops_APGI;
		}
		else {
			--_hoops_IPRI->_hoops_IHHPR._hoops_SIIPR;
			_hoops_IPRI->_hoops_RSHPR &= ~_hoops_AHIAA;
		}

		flags[offset] &= ~(_hoops_APGI|_hoops_AHIAA);

		_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_RAGGA|_hoops_RPSIR);
	}
	else if (_hoops_GCRIR == _hoops_ICRIR) {
		bool	erase = false;

		Local_Face_Attributes *	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;
		_hoops_GIIPR *		flags = _hoops_CPRI->_hoops_CHHPR(offset);

		if (!BIT (*flags, _hoops_IAGI|_hoops_HSIPR)) {
			HE_WARNING(HEC_FACE, HES_VISIBILITY, "No visibility set on this face");
			return;
		}
		if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
			/* _hoops_SR _hoops_HS _hoops_SAHR _hoops_IPPRA _hoops_IRS _hoops_RHPC _hoops_GPP _hoops_IRS _hoops_RSRA _hoops_GPHA.  _hoops_CGP _hoops_RIAGR _hoops_RPII _hoops_GRP _hoops_RH
			_hoops_GHRHR _hoops_RIP, _hoops_SR _hoops_PAH'_hoops_RA _hoops_CPRIR _hoops_PPR _hoops_SR _hoops_HS _hoops_IS _hoops_CCPP _hoops_RH _hoops_IIRRA->_hoops_SGI _hoops_CRPR (_hoops_PPR _hoops_HSPC _hoops_SCH _hoops_IS _hoops_RH _hoops_GHRHR _hoops_RIP)*/
			ZALLOC_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
			for (int i = 0; i < _hoops_IPRI->face_count; i++)
				_hoops_IPRI->local_face_attributes.flags[i] = _hoops_IPRI->local_face_attributes._hoops_SGRHR;
			_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
			flags = _hoops_CPRI->_hoops_CHHPR(offset);
		}

		if (BIT (*flags, _hoops_IAGI)) {
			--_hoops_CPRI->_hoops_CPIAA;
			erase = true;
		}
		else {
			--_hoops_CPRI->_hoops_SIIPR;
		}
		_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);

		*flags &= ~(_hoops_IAGI|_hoops_HSIPR);
		*flags |= _hoops_IGAHR;

		if (_hoops_IPRI->tristrips != null) {
			_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;

			if (erase)
				_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_AISSR|_hoops_CSCCA|_hoops_RPSIR);
			else
				_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
		}
	}
	else if (_hoops_GCRIR == _hoops_GSRIR) {
		Local_Face_Attributes *	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;
		int const *				regions = _hoops_CPRI->regions;
		_hoops_GIIPR *		flags;

		bool	_hoops_SACRH = false;
		bool	erase = false;

		if ((flags = _hoops_CPRI->flags) == null ||
			regions == null && offset != 0) {
			HE_ERROR (HEC_REGION, HES_VISIBILITY, "No visibilities set in this region");
			return;
		}

		for (int i=0; i<_hoops_IPRI->face_count; i++) {
			if (regions == null || regions[i] == offset) {
				if (BIT (flags[i], _hoops_IAGI)) {
					--_hoops_CPRI->_hoops_CPIAA;
					_hoops_SACRH = erase = true;
				}
				else if (BIT (flags[i], _hoops_HSIPR)) {
					--_hoops_CPRI->_hoops_SIIPR;
					_hoops_SACRH = true;
				}

				flags[i] &= ~(_hoops_IAGI|_hoops_HSIPR);
			}
		}

		if (_hoops_SACRH) {
			_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);

			if (_hoops_IPRI->tristrips != null) {
				Tristrip *	ts = _hoops_IPRI->tristrips;

				do if (ts->face_attributes.region == offset) {
					ts->face_attributes.flags &= ~_hoops_HRAPA;
					ts->_hoops_CPGPR |= _hoops_GPSIR;
				} while ((ts = ts->next) != null);
			}

			if (erase)
				_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_AISSR|_hoops_CSCCA|_hoops_RPSIR);
			else
				_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
		}
		else
			HE_ERROR (HEC_REGION, HES_VISIBILITY, "No visibilities set in this region");
	}
	else
		ASSERT(0);
#endif
}


HC_INTERFACE void HC_CDECL HC_UnSet_Visibility (void)
{
	_hoops_PAPPR context("UnSet_Visibility");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Visibility ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_AHRPP)) != null) {
		if (target->type == _hoops_CIRIR) {
			_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)target;
			HI_UnSet_Visibility(context, _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR, _hoops_ASIIR->info._hoops_IPRI.offset, _hoops_ASIIR->_hoops_GCRIR);
		}
		else
			HI_UnSet_Attribute (context, target, HK_VISIBILITY);

		_hoops_IRRPR();
	}

#endif
}


#ifdef DISABLE_SHOW
#	ifdef DISABLE_METAFILE
#		define	_hoops_RICRGR
#	endif
#endif


#ifndef _hoops_RICRGR

#define _hoops_ISIIH(_hoops_ASSGH, _hoops_CSIIH, _hoops_HSSGH, _hoops_ISSGH, _hoops_CSSGH) do {			\
			if (_hoops_CSIIH) {												\
				if (_hoops_HSSGH == null)										\
					_hoops_ISSGH = HI_Sprintf1 (_hoops_ISSGH, _hoops_CSSGH, "%s,", _hoops_ASSGH);		\
				else													\
					_hoops_ISSGH = HI_Copy_Chars ("on,", _hoops_ISSGH);					\
			}															\
			else {														\
				if (_hoops_HSSGH == null)										\
					_hoops_ISSGH = HI_Sprintf1 (_hoops_ISSGH, _hoops_CSSGH, "no %s,", _hoops_ASSGH);	\
				else													\
					_hoops_ISSGH = HI_Copy_Chars ("off,", _hoops_ISSGH);					\
			}															\
		} while (0)

local char *_hoops_AICRGR (
	_hoops_RSAIR			*vis,
	Option_Value const *	option,
	char *					_hoops_ASAPR,
	char const *			_hoops_PSAPR) {
	_hoops_ACHR			mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0U;

	if (!BIT (vis->value, T_CUT_GEOMETRY)) {
		_hoops_ASAPR[0] = 'o'; _hoops_ASAPR[1] = 'f'; _hoops_ASAPR[2] = 'f'; return _hoops_ASAPR + 3;
	}

	if (vis->_hoops_PRIGA.mask == 0) {
		_hoops_ASAPR[0] = 'o'; _hoops_ASAPR[1] = 'n'; return _hoops_ASAPR + 2;
	}

	if ((mask & vis->_hoops_PRIGA.mask) == (T_LINES|T_FACES)) {
		if ((mask & vis->_hoops_PRIGA.value) == 0) {
			_hoops_ASAPR[0] = 'o'; _hoops_ASAPR[1] = 'f'; _hoops_ASAPR[2] = 'f'; return _hoops_ASAPR + 3;
		}
		else if ((mask & vis->_hoops_PRIGA.value) == (T_LINES|T_FACES)) {
			_hoops_ASAPR[0] = 'o'; _hoops_ASAPR[1] = 'n'; return _hoops_ASAPR + 2;
		}
	}

	/* _hoops_IGGA _hoops_RGSR(_hoops_GRI) */

	if (option == null &&
		(_hoops_ACHR)_hoops_RIII (vis->_hoops_PRIGA.mask) != vis->_hoops_PRIGA.mask)
		*_hoops_ASAPR++ = '(';

	if (BIT (mask & vis->_hoops_PRIGA.mask, T_LINES))
		_hoops_ISIIH ("edges", BIT (vis->_hoops_PRIGA.value, T_LINES), option, _hoops_ASAPR, _hoops_PSAPR);
	if (BIT (mask & vis->_hoops_PRIGA.mask, T_FACES))
		_hoops_ISIIH ("faces", BIT (vis->_hoops_PRIGA.value, T_FACES), option, _hoops_ASAPR, _hoops_PSAPR);

	--_hoops_ASAPR;  /* (_hoops_HASIR _hoops_GRCIR _hoops_RRCIR) */

	if (option == null &&
		(_hoops_ACHR)_hoops_RIII (vis->_hoops_PRIGA.mask) != vis->_hoops_PRIGA.mask)
		*_hoops_ASAPR++ = ')';

	return _hoops_ASAPR;
}

local char *_hoops_PICRGR (
	_hoops_RSAIR			*vis,
	Option_Value const *	option,
	char *					_hoops_ASAPR,
	char const *			_hoops_PSAPR) {
	_hoops_ACHR			mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0U;

	if (!BIT (vis->value, T_ANY_SHADOW)) {
		_hoops_ASAPR[0] = 'o'; _hoops_ASAPR[1] = 'f'; _hoops_ASAPR[2] = 'f'; return _hoops_ASAPR + 3;
	}

	if (vis->_hoops_SPSS.mask == 0) {
		_hoops_ASAPR[0] = 'o'; _hoops_ASAPR[1] = 'n'; return _hoops_ASAPR + 2;
	}

#if 0
	if (option == null && vis->_hoops_SPSS.mask == 0) {
		/* _hoops_RPAPR */
		return --_hoops_ASAPR;
	}
#endif

	if (vis->_hoops_SPSS.mask == _hoops_RIHGP) {
		if (vis->_hoops_SPSS.value == 0) {
			_hoops_ASAPR[0] = 'o'; _hoops_ASAPR[1] = 'f'; _hoops_ASAPR[2] = 'f'; return _hoops_ASAPR + 3;
		}
		else if (vis->_hoops_SPSS.value == _hoops_RIHGP) {
			_hoops_ASAPR[0] = 'o'; _hoops_ASAPR[1] = 'n'; return _hoops_ASAPR + 2;
		}
	}

	/* _hoops_IGGA _hoops_RGSR(_hoops_GRI) */

	if (option == null &&
		(_hoops_ACHR)_hoops_RIII (vis->_hoops_SPSS.mask) != vis->_hoops_SPSS.mask)
		*_hoops_ASAPR++ = '(';

	if (BIT (mask & vis->_hoops_SPSS.mask, T_SHADOW_RECEIVING))
		_hoops_ISIIH ("receiving", BIT (vis->_hoops_SPSS.value, T_SHADOW_RECEIVING), option, _hoops_ASAPR, _hoops_PSAPR);
	if (BIT (mask & vis->_hoops_SPSS.mask, _hoops_GIHGP))
		_hoops_ISIIH ("emitting", BIT (vis->_hoops_SPSS.value, _hoops_GIHGP), option, _hoops_ASAPR, _hoops_PSAPR);
	if (BIT (mask & vis->_hoops_SPSS.mask, _hoops_SHHGP))
		_hoops_ISIIH ("casting", BIT (vis->_hoops_SPSS.value, _hoops_SHHGP), option, _hoops_ASAPR, _hoops_PSAPR);

	--_hoops_ASAPR;  /* (_hoops_HASIR _hoops_GRCIR _hoops_RRCIR) */

	if (option == null &&
		(_hoops_ACHR)_hoops_RIII (vis->_hoops_SPSS.mask) != vis->_hoops_SPSS.mask)
		*_hoops_ASAPR++ = ')';

	return _hoops_ASAPR;
}


local char *_hoops_HICRGR (
	_hoops_RSAIR			*vis,
	Option_Value const *	option,
	char *					_hoops_ASAPR,
	char const *			_hoops_PSAPR) {
	_hoops_ACHR			_hoops_IICRGR = vis->mask & T_ANY_LIGHTS;
	_hoops_ACHR			_hoops_CICRGR = vis->value & T_ANY_LIGHTS;
	_hoops_ACHR			mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0U;

	if (option == null && _hoops_IICRGR == 0) {
		/* _hoops_RPAPR */
		return _hoops_ASAPR;
	}

	_hoops_IICRGR &= mask;

	if (_hoops_IICRGR == T_ANY_LIGHTS) switch (_hoops_CICRGR) {
		case 0: {
			_hoops_ASAPR[0] = 'o'; _hoops_ASAPR[1] = 'f'; _hoops_ASAPR[2] = 'f'; return _hoops_ASAPR + 3;
		}		_hoops_HHHI;

		case T_ANY_LIGHTS: {
			_hoops_ASAPR[0] = 'o'; _hoops_ASAPR[1] = 'n'; return _hoops_ASAPR + 2;
		}		_hoops_HHHI;

		/* _hoops_SHIR: _hoops_GRHP _hoops_CPIC */
	}

	/* _hoops_IGGA _hoops_RGSR(_hoops_GRI) */

	if (BIT (_hoops_IICRGR, T_LIGHTS_FOR_FACES))
		_hoops_ISIIH ("faces", BIT (_hoops_CICRGR, T_LIGHTS_FOR_FACES), option, _hoops_ASAPR, _hoops_PSAPR);
	if (BIT (_hoops_IICRGR, T_LIGHTS_FOR_EDGES))
		_hoops_ISIIH ("edges", BIT (_hoops_CICRGR, T_LIGHTS_FOR_EDGES), option, _hoops_ASAPR, _hoops_PSAPR);
	if (BIT (_hoops_IICRGR, T_LIGHTS_FOR_MARKERS))
		_hoops_ISIIH ("markers", BIT (_hoops_CICRGR, T_LIGHTS_FOR_MARKERS), option, _hoops_ASAPR, _hoops_PSAPR);

	--_hoops_ASAPR;  /* (_hoops_HASIR _hoops_GRCIR _hoops_RRCIR) */

	return _hoops_ASAPR;
}


local char *_hoops_SICRGR (
	_hoops_RSAIR *			vis,
	Option_Value const *	option,
	char *					_hoops_ASAPR,
	char const *			_hoops_PSAPR) {
	_hoops_ACHR			_hoops_GCCRGR = vis->mask & T_ANY_EDGE;
	_hoops_ACHR			mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0U;

	_hoops_GCCRGR &= mask;

	if (_hoops_GCCRGR == 0) {
		/* _hoops_RPAPR */
		return _hoops_ASAPR;
	}

	if (ALLBITS (_hoops_GCCRGR, T_ANY_EDGE)) switch (mask & vis->value & T_ANY_EDGE) {
		case 0: {
			_hoops_ASAPR[0] = 'o'; _hoops_ASAPR[1] = 'f'; _hoops_ASAPR[2] = 'f'; return _hoops_ASAPR + 3;
		}	_hoops_HHHI;

		case T_ANY_EDGE: {
			_hoops_ASAPR[0] = 'o'; _hoops_ASAPR[1] = 'n'; return _hoops_ASAPR + 2;
		}	_hoops_HHHI;

		case T_PERIMETER_EDGES: {
			return HI_Copy_Chars ("perimeters only", _hoops_ASAPR);
		}	_hoops_HHHI;

		case _hoops_CRHGP: {
			return HI_Copy_Chars ("adjacent only", _hoops_ASAPR);
		}	_hoops_HHHI;

		case T_MESH_QUAD_EDGES: {
			return HI_Copy_Chars ("mesh quads only", _hoops_ASAPR);
		}	_hoops_HHHI;

		case T_HARD_EDGES:	{
			return HI_Copy_Chars ("hard only", _hoops_ASAPR);
		}	_hoops_HHHI;

		case T_INTERIOR_SILHOUETTE_EDGES:		{
			return HI_Copy_Chars ("interior silhouettes only", _hoops_ASAPR);
		}	_hoops_HHHI;

		case _hoops_GCSI:		{
			return HI_Copy_Chars ("nonculled only", _hoops_ASAPR);
		}	_hoops_HHHI;

		default: {	/* _hoops_HPCAR _hoops_HCR _hoops_PSAP _hoops_HIH _hoops_HHH _hoops_IHPPP _hoops_GPP */
			_hoops_ASAPR = HI_Copy_Chars ("everything=off,", _hoops_ASAPR);

			if (BIT (vis->value, T_GENERIC_EDGES))
				_hoops_ISIIH ("generics", true, option, _hoops_ASAPR, _hoops_PSAPR);
			if (BIT (vis->value, T_PERIMETER_EDGES))
				_hoops_ISIIH ("perimeters", true, option, _hoops_ASAPR, _hoops_PSAPR);
			if (BIT (vis->value, _hoops_CRHGP))
				_hoops_ISIIH ("adjacent", true, option, _hoops_ASAPR, _hoops_PSAPR);
			if (BIT (vis->value, T_MESH_QUAD_EDGES))
				_hoops_ISIIH ("mesh quads", true, option, _hoops_ASAPR, _hoops_PSAPR);
			if (BIT (vis->value, T_HARD_EDGES))
				_hoops_ISIIH ("hard", true, option, _hoops_ASAPR, _hoops_PSAPR);
			if (BIT (vis->value, T_INTERIOR_SILHOUETTE_EDGES))
				_hoops_ISIIH ("interior silhouettes", true, option, _hoops_ASAPR, _hoops_PSAPR);
			if (BIT (vis->value, _hoops_GCSI))
				_hoops_ISIIH ("nonculled", true, option, _hoops_ASAPR, _hoops_PSAPR);

			--_hoops_ASAPR;  /* (_hoops_HASIR _hoops_GRCIR _hoops_RRCIR) */

			return _hoops_ASAPR;
		}	_hoops_HHHI;
	}

	/* _hoops_IGGA _hoops_RGSR(_hoops_GRI) */

	if (BIT (_hoops_GCCRGR, T_GENERIC_EDGES))
		_hoops_ISIIH ("generics", BIT (vis->value, T_GENERIC_EDGES), option, _hoops_ASAPR, _hoops_PSAPR);
	if (BIT (_hoops_GCCRGR, T_PERIMETER_EDGES))
		_hoops_ISIIH ("perimeters", BIT (vis->value, T_PERIMETER_EDGES), option, _hoops_ASAPR, _hoops_PSAPR);
	if (BIT (_hoops_GCCRGR, _hoops_CRHGP))
		_hoops_ISIIH ("adjacent", BIT (vis->value, _hoops_CRHGP), option, _hoops_ASAPR, _hoops_PSAPR);
	if (BIT (_hoops_GCCRGR, T_MESH_QUAD_EDGES))
		_hoops_ISIIH ("mesh quads", BIT (vis->value, T_MESH_QUAD_EDGES), option, _hoops_ASAPR, _hoops_PSAPR);
	if (BIT (_hoops_GCCRGR, T_HARD_EDGES))
		_hoops_ISIIH ("hard", BIT (vis->value, T_HARD_EDGES), option, _hoops_ASAPR, _hoops_PSAPR);
	if (BIT (_hoops_GCCRGR, T_INTERIOR_SILHOUETTE_EDGES))
		_hoops_ISIIH ("interior silhouettes", BIT (vis->value, T_INTERIOR_SILHOUETTE_EDGES), option, _hoops_ASAPR, _hoops_PSAPR);
	if (BIT (_hoops_GCCRGR, _hoops_GCSI))
		_hoops_ISIIH ("nonculled", BIT (vis->value, _hoops_GCSI), option, _hoops_ASAPR, _hoops_PSAPR);

	--_hoops_ASAPR;  /* (_hoops_HASIR _hoops_GRCIR _hoops_RRCIR) */

	return _hoops_ASAPR;
}
#endif

GLOBAL_FUNCTION void HI_Show_Visibility (
	_hoops_RSAIR			*vis,
	char					*spec,
	int						_hoops_CSACR) {
#ifndef _hoops_RICRGR

	if (vis->mask == _hoops_CAHGP &&
		vis->value == _hoops_CAHGP &&
		vis->_hoops_PRIGA.mask == (T_FACES|T_LINES) &&
		vis->_hoops_PRIGA.value == (T_FACES|T_LINES))
		HI_Return_Chars (spec, _hoops_CSACR, "on", 2);
	else if (vis->mask == _hoops_CAHGP && vis->value == 0)
		HI_Return_Chars (spec, _hoops_CSACR, "off", 3);
	else if (vis->mask == _hoops_AAHGP && vis->value == _hoops_AAHGP)
		HI_Return_Chars (spec, _hoops_CSACR, "geometry=on", 11);
	else if (vis->mask == _hoops_AAHGP && vis->value == 0)
		HI_Return_Chars (spec, _hoops_CSACR, "geometry=off", 12);
	else {
		char			buf[600];
		char			*_hoops_ASAPR = buf;
		char const		*_hoops_PSAPR = _hoops_ASAPR + _hoops_GGAPR (buf);

		if (ALLBITS (vis->mask, T_FACES|T_ANY_EDGE) &&
			(ALLBITS (vis->value, T_FACES|T_ANY_EDGE) ||
			 !ANYBIT (vis->value, T_FACES|T_ANY_EDGE))) {
			if (BIT (vis->value, T_FACES)) /* (_hoops_IRS _hoops_CGGHA _hoops_IGRH) */
				_hoops_ASAPR = HI_Copy_Chars ("polygons=on,", _hoops_ASAPR);
			else
				_hoops_ASAPR = HI_Copy_Chars ("polygons=off,", _hoops_ASAPR);
		}
		else {
			if (ANYBIT (vis->mask, T_ANY_EDGE)) {
				bool			_hoops_HISCA = false;

				_hoops_ASAPR = HI_Copy_Chars ("edges=", _hoops_ASAPR);

				if (ALLBITS (vis->mask, T_ANY_EDGE))
					_hoops_HISCA = ANYBIT (vis->value, T_ANY_EDGE) && !ALLBITS (vis->value, T_ANY_EDGE);
				else {
					_hoops_ACHR		_hoops_IGGRH = _hoops_RIII (vis->mask & T_ANY_EDGE);

					_hoops_HISCA = ANYBIT (vis->mask & T_ANY_EDGE, ~_hoops_IGGRH);
				}

				if (_hoops_HISCA) *_hoops_ASAPR++ = '(';
				_hoops_ASAPR = _hoops_SICRGR (vis, null, _hoops_ASAPR, _hoops_PSAPR);
				if (_hoops_HISCA) *_hoops_ASAPR++ = ')';
				*_hoops_ASAPR++ = ',';
			}

			if (BIT (vis->mask, T_FACES)) {
				if (BIT (vis->value, T_FACES))
					_hoops_ASAPR = HI_Copy_Chars ("faces=on,", _hoops_ASAPR);
				else
					_hoops_ASAPR = HI_Copy_Chars ("faces=off,", _hoops_ASAPR);
			}
		}


		if (ALLBITS (vis->mask, T_MARKERS|T_VERTICES) &&
			(ALLBITS (vis->value, T_MARKERS|T_VERTICES) ||
			 !ANYBIT (vis->value, T_MARKERS|T_VERTICES))) {
			if (BIT (vis->value, T_MARKERS)) /* (_hoops_IRS _hoops_CGGHA _hoops_IGRH) */
				_hoops_ASAPR = HI_Copy_Chars ("markers=on,", _hoops_ASAPR);
			else
				_hoops_ASAPR = HI_Copy_Chars ("markers=off,", _hoops_ASAPR);
		}
		else {
			if (BIT (vis->mask, T_MARKERS)) {
				if (BIT (vis->value, T_MARKERS))
					_hoops_ASAPR = HI_Copy_Chars ("markers only=on,", _hoops_ASAPR);
				else
					_hoops_ASAPR = HI_Copy_Chars ("markers only=off,", _hoops_ASAPR);
			}

			if (BIT (vis->mask, T_VERTICES)) {
				if (BIT (vis->value, T_VERTICES))
					_hoops_ASAPR = HI_Copy_Chars ("vertices=on,", _hoops_ASAPR);
				else
					_hoops_ASAPR = HI_Copy_Chars ("vertices=off,", _hoops_ASAPR);
			}
		}


		if (BIT (vis->mask, T_IMAGES)) {
			if (BIT (vis->value, T_IMAGES))
				_hoops_ASAPR = HI_Copy_Chars ("images=on,", _hoops_ASAPR);
			else
				_hoops_ASAPR = HI_Copy_Chars ("images=off,", _hoops_ASAPR);
		}

		if (BIT (vis->mask, T_CUTTING_PLANES)) {
			if (BIT (vis->value, T_CUTTING_PLANES))
				_hoops_ASAPR = HI_Copy_Chars ("cutting planes=on,", _hoops_ASAPR);
			else
				_hoops_ASAPR = HI_Copy_Chars ("cutting planes=off,", _hoops_ASAPR);
		}

		if (BIT (vis->mask, T_LINES)) {
			if (BIT (vis->value, T_LINES))
				_hoops_ASAPR = HI_Copy_Chars ("lines=on,", _hoops_ASAPR);
			else
				_hoops_ASAPR = HI_Copy_Chars ("lines=off,", _hoops_ASAPR);
		}

		if (ANYBIT (vis->mask, T_ANY_LIGHTS)) {
			bool			_hoops_HISCA = false;

			_hoops_ASAPR = HI_Copy_Chars ("lights=", _hoops_ASAPR);

			if (ALLBITS (vis->mask, T_ANY_LIGHTS))
				_hoops_HISCA = ANYBIT (vis->value, T_ANY_LIGHTS) && !ALLBITS (vis->value, T_ANY_LIGHTS);
			else {
				_hoops_ACHR		_hoops_IGGRH = _hoops_RIII (vis->mask & T_ANY_LIGHTS);

				_hoops_HISCA = ANYBIT (vis->mask & T_ANY_LIGHTS, ~_hoops_IGGRH);
			}

			if (_hoops_HISCA) *_hoops_ASAPR++ = '(';
			_hoops_ASAPR = _hoops_HICRGR (vis, null, _hoops_ASAPR, _hoops_PSAPR);
			if (_hoops_HISCA) *_hoops_ASAPR++ = ')';
			*_hoops_ASAPR++ = ',';
		}

		if (BIT (vis->mask, T_TEXT)) {
			if (BIT (vis->value, T_TEXT))
				_hoops_ASAPR = HI_Copy_Chars ("text=on,", _hoops_ASAPR);
			else
				_hoops_ASAPR = HI_Copy_Chars ("text=off,", _hoops_ASAPR);
		}

		if (BIT (vis->mask, T_STRING_CURSORS)) {
			if (BIT (vis->value, T_STRING_CURSORS))
				_hoops_ASAPR = HI_Copy_Chars ("string cursors=on,", _hoops_ASAPR);
			else
				_hoops_ASAPR = HI_Copy_Chars ("string cursors=off,", _hoops_ASAPR);
		}

		if (BIT (vis->mask, T_WINDOWS)) {
			if (BIT (vis->value, T_WINDOWS))
				_hoops_ASAPR = HI_Copy_Chars ("windows=on,", _hoops_ASAPR);
			else
				_hoops_ASAPR = HI_Copy_Chars ("windows=off,", _hoops_ASAPR);
		}

		if (ANYBIT (vis->mask, T_CUT_GEOMETRY)) {
			bool			_hoops_HISCA = false;

			_hoops_ASAPR = HI_Copy_Chars ("cut geometry=", _hoops_ASAPR);

			if (ALLBITS (vis->_hoops_PRIGA.mask, T_LINES|T_FACES))
				_hoops_HISCA = ANYBIT (vis->_hoops_PRIGA.value, T_LINES|T_FACES) &&
							!ALLBITS (vis->_hoops_PRIGA.value, T_LINES|T_FACES);
			else {
				_hoops_ACHR		_hoops_IGGRH = _hoops_RIII (vis->_hoops_PRIGA.mask);

				_hoops_HISCA = ANYBIT (vis->_hoops_PRIGA.mask, ~_hoops_IGGRH);
			}

			_hoops_ASAPR = _hoops_AICRGR (vis, null, _hoops_ASAPR, _hoops_PSAPR);
			*_hoops_ASAPR++ = ',';
		}

		if (ANYBIT (vis->mask, T_ANY_SHADOW)) {
			bool			_hoops_HISCA = false;

			_hoops_ASAPR = HI_Copy_Chars ("shadows=", _hoops_ASAPR);

			if (ALLBITS (vis->_hoops_SPSS.mask, _hoops_RIHGP))
				_hoops_HISCA = ANYBIT (vis->_hoops_SPSS.value, _hoops_RIHGP) &&
							!ALLBITS (vis->_hoops_SPSS.value, _hoops_RIHGP);
			else {
				_hoops_ACHR		_hoops_IGGRH = _hoops_RIII (vis->_hoops_SPSS.mask & _hoops_RIHGP);

				_hoops_HISCA = ANYBIT (vis->_hoops_SPSS.mask & _hoops_RIHGP, ~_hoops_IGGRH);
			}

			if (_hoops_HISCA)
				*_hoops_ASAPR++ = '(';
			_hoops_ASAPR = _hoops_PICRGR (vis, null, _hoops_ASAPR, _hoops_PSAPR);
			if (_hoops_HISCA)
				*_hoops_ASAPR++ = ')';
			*_hoops_ASAPR++ = ',';
		}

		if (_hoops_ASAPR > buf) --_hoops_ASAPR;

		HI_Return_Chars (spec, _hoops_CSACR, buf, (int)(_hoops_ASAPR - buf));
	}
#endif
}


#ifndef DISABLE_SHOW
#define _hoops_SASAA		_hoops_ASPCR	/* _hoops_GII _hoops_IGRH _hoops_HAR _hoops_IGI _hoops_IH _hoops_IRS _hoops_HPHR _hoops_HPRC, _hoops_SPASR _hoops_RGSR _hoops_GGR _hoops_PHPRGR */

local void _hoops_RCCRGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_RSAIR *			vis,
	char const *			_hoops_ACCRGR,
	char *					list,
	int						_hoops_GGCIR)
{
	Option_Value *	option;

	if (!HI_Parse_Options (_hoops_RIGC, _hoops_ACCRGR, _hoops_CIACR (_hoops_CPSAA), &option, _hoops_CGPCR|_hoops_PAPCA))
		return;

	if (option == null)
		return;

	_hoops_ACHR	mask = option->type->id;

	char					buf[1000];
	char *					p = buf;
	char const *			pe = p + _hoops_GGAPR (buf);

	if (mask == T_ANY_EDGE) {
		p = _hoops_SICRGR (vis, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(p - buf));
	}
	else if (mask == T_CUT_GEOMETRY) {
		p = _hoops_AICRGR (vis, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(p - buf));
	}
	else if (mask == T_ANY_SHADOW) {
		p = _hoops_PICRGR (vis, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(p - buf));
	}
	else if (mask == T_ANY_LIGHTS) {
		p = _hoops_HICRGR (vis, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(p - buf));
	}
	else if (mask == _hoops_SASAA) {
		if (!BIT (vis->_hoops_PRIGA.mask, T_LINES))
			HI_Return_Chars (list, _hoops_GGCIR, "", 0);
		else if (BIT (vis->_hoops_PRIGA.value, T_LINES))
			HI_Return_Chars (list, _hoops_GGCIR, "on", 2);
		else
			HI_Return_Chars (list, _hoops_GGCIR, "off", 3);
	}
	else if (_hoops_RIII (mask) != mask) {	/* _hoops_PGGRA _hoops_SGS _hoops_HIAAR _hoops_GRRRA _hoops_AAP */
		if (!ALLBITS (vis->mask, mask)) {
			/* _hoops_HAR _hoops_HCR _hoops_HGRC _hoops_APSAR _hoops_CHR _hoops_ARP */
			HI_Return_Chars (list, _hoops_GGCIR, "", 0);
		}
		else if (ALLBITS (vis->value, mask)) {
			HI_Return_Chars (list, _hoops_GGCIR, "on", 2);
		}
		else if (!ANYBIT (vis->value, mask)) {
			HI_Return_Chars (list, _hoops_GGCIR, "off", 3);
		}
		else {
			/* _hoops_HAR _hoops_HCR _hoops_ARP _hoops_ARP _hoops_RH _hoops_PSHR _hoops_PPRRR */
			HE_ERROR2 (HEC_POLYGON, HES_EDGE_AND_FACE_VIS_MISMATCH,
					   Sprintf_S (null, "Can't show '%s' visibility -", _hoops_ACCRGR),
					   "Components of that setting are different");
		}
	}
	else if (!BIT (vis->mask, mask))
		HI_Return_Chars (list, _hoops_GGCIR, "", 0);
	else if (BIT (vis->value, mask))
		HI_Return_Chars (list, _hoops_GGCIR, "on", 2);
	else
		HI_Return_Chars (list, _hoops_GGCIR, "off", 3);

	HI_Free_Option_List (_hoops_RIGC, option);
}
#endif



HC_INTERFACE void HC_CDECL HC_Show_Visibility (
	char *		list)
{
	_hoops_PAPPR context("Show_Visibility");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Visibility () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_GGAPP)) != null) {
		_hoops_RSAIR *	_hoops_RGP;
		if ((_hoops_RGP = (_hoops_RSAIR *)HI_Find_Attribute (context, target, HK_VISIBILITY)) != null) {
			HI_Show_Visibility (_hoops_RGP, list, -1);
			_hoops_HPRH (_hoops_RGP);
		}
		_hoops_IRRPR();
	}
#endif
}


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Visibility (
	int				count,
	Key const *		keys,
	char *			list)
{
	_hoops_PAPPR context("PShow_Net_Visibility");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Visibility () */\n");
	);

	_hoops_RSAIR *	_hoops_RGP;
	if ((_hoops_RGP = (_hoops_RSAIR *) HI_Find_Attribute_And_Lock(context, _hoops_GGAPP, _hoops_HRPCR, count, keys)) != null) {
		HI_Show_Visibility (_hoops_RGP, list, -1);
		_hoops_HPRH (_hoops_RGP);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(list, -1, "", 0);

#endif
}
#endif



HC_INTERFACE void HC_CDECL HC_Show_One_Visibility (
	char const *		_hoops_PCCRGR,
	char *				list)
{
	_hoops_PAPPR context("Show_One_Visibility");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_Visibility () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_GGAPP)) != null) {
		_hoops_RSAIR *	_hoops_RGP;
		if ((_hoops_RGP = (_hoops_RSAIR *)HI_Find_Attribute (context, target, HK_VISIBILITY)) != null) {
			_hoops_RCCRGR (context, _hoops_RGP, _hoops_PCCRGR, list, -1);
			_hoops_HPRH (_hoops_RGP);
		}
		_hoops_IRRPR();
	}
#endif
}




#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Visibility (
	int					count,
	Key const *			keys,
	char const *		_hoops_PCCRGR,
	char *				list)
{
	_hoops_PAPPR context("PShow_One_Net_Visibility");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_One_Net_Visibility () */\n");
	);

	_hoops_RSAIR *	_hoops_RGP;
	if ((_hoops_RGP = (_hoops_RSAIR *) HI_Find_Attribute_And_Lock(context, _hoops_GGAPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_RCCRGR (context, _hoops_RGP, _hoops_PCCRGR, list, -1);
		_hoops_HPRH (_hoops_RGP);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(list, -1, "", 0);

#endif
}
#endif






















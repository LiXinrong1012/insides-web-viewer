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
 * $Id: obf_tmp.txt 1.63 2010-07-14 23:29:15 covey Exp $
 */


#include "hoops.h"
#include "driver.h"
#include "select.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

/* _hoops_RACRR _hoops_GSSP-_hoops_GC _hoops_RHHR-_hoops_RPGP _hoops_IIGR _hoops_IRS _hoops_RSRA _hoops_PPSR */

GLOBAL_FUNCTION void HD_Select_Dot (
	Net_Rendition const &		nr,
	Geometry const *			thing,
	Key							_hoops_HSICA,
	Key							_hoops_CISAP,
	_hoops_ACHR					type,
	Point const *				_hoops_CSAI) {
#ifndef DISABLE_SELECTION
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter *	sc = dc->_hoops_APHHP;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_RPRA const *			elements = _hoops_IHCR->matrix->data.elements;
	DC_Point					center;
	XY							_hoops_CGSIR;
	float						_hoops_CIPAS;

	switch (_hoops_IHCR->_hoops_HGSC) {
		case _hoops_SIPHP: {
			center.x = _hoops_CSAI->x;
			/* _hoops_HHCI _hoops_ISPR _hoops_IIGR _hoops_RH _hoops_IPCAH _hoops_IGIAR _hoops_SPCR */
			if ((_hoops_CGSIR.x = center.x - sc->_hoops_AICAH.x) < 0.0f) _hoops_CGSIR.x = -_hoops_CGSIR.x;
			if (_hoops_CGSIR.x > sc->_hoops_RICAH.x) return; /* _hoops_GSSR _hoops_AGIR */

			center.y = _hoops_CSAI->y;
		}	break;

		case _hoops_ACPHP: {
			center.x = _hoops_HPRA (elements, *_hoops_CSAI);
			/* _hoops_HHCI _hoops_ISPR _hoops_IIGR _hoops_RH _hoops_IPCAH _hoops_IGIAR _hoops_SPCR */
			if ((_hoops_CGSIR.x = center.x - sc->_hoops_AICAH.x) < 0.0f) _hoops_CGSIR.x = -_hoops_CGSIR.x;
			if (_hoops_CGSIR.x > sc->_hoops_RICAH.x) return; /* _hoops_GSSR _hoops_AGIR */

			center.y = _hoops_IPRA (elements, *_hoops_CSAI);
		}	break;

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Select-dot transform type");
			return;
		}		/* _hoops_IHSA; */
	}

	/* _hoops_HHCI _hoops_ISPR _hoops_HHHGH _hoops_IH _hoops_GHCR */
	if ((_hoops_CGSIR.y = center.y - sc->_hoops_AICAH.y) < 0.0f) _hoops_CGSIR.y = -_hoops_CGSIR.y;
	if (_hoops_CGSIR.y > sc->_hoops_RICAH.y) return;

	/* _hoops_ISPR _hoops_RH _hoops_GHARP (_hoops_RH _hoops_RRI _hoops_CCCI) _hoops_IPCAH */
	_hoops_CGSIR.x /= sc->_hoops_HICAH.x;
	_hoops_CGSIR.y /= sc->_hoops_HICAH.y;
	_hoops_CIPAS = _hoops_CGSIR.x * _hoops_CGSIR.x + _hoops_CGSIR.y * _hoops_CGSIR.y;
	if (_hoops_CIPAS > sc->_hoops_GICAH) return;

	/* _hoops_ISPR _hoops_RH _hoops_CIHH */

	if (sc->_hoops_RAPAS == null)
		if (center.x < sc->bounding.left   ||
			center.x > sc->bounding.right  ||
			center.y < sc->bounding.bottom ||
			center.y > sc->bounding.top) return;


	/* _hoops_ISPR _hoops_AHCR */
	if (_hoops_IHCR->_hoops_HGSC == _hoops_SIPHP)
		center.z = _hoops_CSAI->z;
	else
		center.z = _hoops_CPRA (elements, *_hoops_CSAI);

	if (center.z < sc->bounding.hither || center.z > sc->bounding.yon) return;

	if (BIT (_hoops_IHCR->flags, _hoops_CSP))
		if (!HD_Point_Within_Cutting_Planes (_hoops_IHCR, center.x, center.y, center.z)) return;

	/* _hoops_AA _hoops_SR _hoops_PICP _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_SIGC? */
	if (BIT (sc->options, _hoops_CRPAS)) {
		bool							_hoops_RCAI = false;

		_hoops_IGRS (dc);

		if (sc->_hoops_GPPAS) {
			void *							_hoops_CCHSP;

			_hoops_CCHSP = _hoops_AACGH (nr, true);
			HD_Std_DC_Polydot (nr, 1, &center);
			_hoops_PACGH (nr, _hoops_CCHSP);

			if (_hoops_IACGH (nr, _hoops_CCHSP) == 0)
				_hoops_RCAI = true;
		}
		else {
			_hoops_HCSIR alter *	_hoops_ICSIR = null;

			if (nr->_hoops_SAIR->_hoops_ASSIR != null)
				_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
			if (_hoops_ICSIR == null) {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									"Expected frame buffer not found");
				_hoops_RCAI = true;
				goto _hoops_SIPAS;
			}

			_hoops_ICSIR->input._hoops_PHHSP = 0;

			HD_Std_DC_Polydot (nr, 1, &center);

			if (_hoops_ICSIR->input._hoops_PHHSP == 0)
				_hoops_RCAI = true;
		}

	  _hoops_SIPAS:
		_hoops_SGRS (dc);
		if (_hoops_RCAI)
			return;
	}

#ifndef DISABLE_POLY_SELECTION
	if (sc->_hoops_RAPAS != null) {
		if (BIT (sc->options, _hoops_PRPAS)) {
			if (!HD_Select_Point_By_Polygon (nr, &center)) return;
		}
		else /* _hoops_ISII _hoops_GHSHA */
			if (!HD_Select_Circle_By_Polyline (nr, &center, 0.0f)) return;
	}
#endif


	/*
	 * _hoops_GCPAS _hoops_CCSPR - _hoops_PRIA _hoops_RH _hoops_RCAHR
	 */

	HD_Elaborate_Selection (nr, thing, _hoops_HSICA, _hoops_CISAP, 0, 0, 0, center.z, _hoops_CIPAS, type, null);
#endif
}

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
 * $Id: obf_tmp.txt 1.43 2010-01-13 00:37:06 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

local void _hoops_ARAPS (
	_hoops_RPRA const *				_hoops_APRA,
	_hoops_IAPA const *		_hoops_HRCAR) {

	if (_hoops_HRCAR  != null) do {
		_hoops_GPPA alter *	_hoops_IRCAR;

		if ((_hoops_IRCAR = (_hoops_GPPA alter *)_hoops_HRCAR->_hoops_APPA) != null) do {
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

			if (!HI_Normalize_Plane (&_hoops_IRCAR->_hoops_SPPA))
				HE_WARNING (HEC_CUTTING_PLANE, HES_SINGULAR_PLANE,
							"A cutting plane became singular after transforming");
		} while ((_hoops_IRCAR = _hoops_IRCAR->next) != null);
	} while ((_hoops_HRCAR = _hoops_HRCAR->next) != null);
}

GLOBAL_FUNCTION void HD_Set_DC_Cutting_Planes (
	Net_Rendition const &				nr) {
	_hoops_HHCR const &			_hoops_IHCR = nr->transform_rendition;

	if (_hoops_IHCR->_hoops_RGH == null) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "No DC Cut planes??");
		return; /* _hoops_PAH'_hoops_RA _hoops_AA _hoops_SCH _hoops_HPGR _hoops_HCR */
	}

	_hoops_SSP alter &		_hoops_GGH = (_hoops_SSP alter &)_hoops_IHCR->_hoops_RGH;

	if (_hoops_GGH->_hoops_PGH == 0) return; /* _hoops_RSH _hoops_SSHRR. */

	_hoops_GGH.Modify();


	if (!BIT (_hoops_IHCR->flags, _hoops_IGCC))
		HD_Validate_World_To_Screen (nr);

	_hoops_RPRA const *		_hoops_APRA = _hoops_IHCR->_hoops_CGCC->_hoops_PPRA()->data.elements;

	_hoops_ARAPS (_hoops_APRA, _hoops_GGH->_hoops_ISIGA);
	_hoops_ARAPS (_hoops_APRA, _hoops_GGH->_hoops_PHCA);
	_hoops_ARAPS (_hoops_APRA, _hoops_GGH->_hoops_IRH);
}

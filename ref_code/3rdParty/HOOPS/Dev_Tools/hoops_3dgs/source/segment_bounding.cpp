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
 * $Id: obf_tmp.txt 1.48 2010-10-06 19:16:21 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"


GLOBAL_FUNCTION bool HI_Bounding_Is_Excluded (Attribute const *_hoops_ASGPR) {
	if (_hoops_ASGPR != null) do {
		if (_hoops_ASGPR->type > HK_HEURISTICS)
			break;

		if (_hoops_ASGPR->type == HK_HEURISTICS) {
			_hoops_GHAIR const *		_hoops_GIGC = (_hoops_GHAIR const *)_hoops_ASGPR;

			if (BIT (_hoops_GIGC->mask & _hoops_GIGC->value, _hoops_CCIAA))
				return true;
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	return false;
}


GLOBAL_FUNCTION void HI_Figure_Segment_Bounding (
	_hoops_CRCP const *				_hoops_SRCP,
	Bounding alter &			bounding,
	Bounding alter &			_hoops_HSRIR) {
	Geometry const *			geometry;
	Subsegment const *			_hoops_GIPIA;

	if (_hoops_SRCP->bounding != null && BIT (_hoops_SRCP->bounding->flags, _hoops_CCIIR)) {
		bounding.Merge (_hoops_SRCP->bounding);
		_hoops_HSRIR.Merge (_hoops_SRCP->_hoops_HSRIR);
		return;
	}

	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		_hoops_CRCP const *			_hoops_GGCPH = _hoops_SSIGP (_hoops_GIPIA);
		Bounding				_hoops_CCIIA;
		Bounding				_hoops_GGPAS;
		bool					_hoops_RHAPI = false;

		HI_Figure_Segment_Bounding (_hoops_GGCPH, _hoops_CCIIA, _hoops_GGPAS);
		if (!_hoops_CCIIA._hoops_HICAR()) {
			if (_hoops_GGCPH->_hoops_IPPGR != null) {
				Attribute *		_hoops_PSACR = null;

				HI_Gather_Modelling (_hoops_GGCPH->_hoops_IPPGR, &_hoops_PSACR);
				_hoops_RHAPI = HI_Bounding_Is_Excluded (_hoops_GGCPH->_hoops_IPPGR);

				if (_hoops_PSACR != null) {
					_hoops_CCIIA = _hoops_CCIIA._hoops_SCIS (&((_hoops_ISGI *)_hoops_PSACR)->matrix.elements[0][0]);
					_hoops_HPRH (_hoops_PSACR);
				}
			}
			if (!_hoops_RHAPI)
				bounding.Merge (_hoops_CCIIA);
		}
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);

	Bounding	_hoops_IPRIC;

	if ((geometry = _hoops_SRCP->geometry) != null) do {
		Bounding		_hoops_HSIGA;

		if (HI_Figure_Geometry_Bounding (geometry, _hoops_HSIGA))
			_hoops_IPRIC.Merge (_hoops_HSIGA);
	} while ((geometry = geometry->next) != null);

	_hoops_HSRIR.Merge (_hoops_IPRIC);
	bounding.Merge (_hoops_IPRIC);
}


GLOBAL_FUNCTION void HI_Refresh_Segment_Bounding (
	_hoops_CRCP alter *				_hoops_SRCP) {
	Geometry const *			geometry;
	Subsegment const *			_hoops_GIPIA;

	_hoops_SRCP->bounding = null;

	HOOPS_WORLD->_hoops_PSRGH++;

	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		_hoops_CRCP const *			_hoops_GGCPH = _hoops_SSIGP (_hoops_GIPIA);

		if (!ANYBIT (_hoops_GGCPH->_hoops_PHSI, _hoops_SHSIR|_hoops_HCHGP)) {
			if (_hoops_GGCPH->bounding != null && BIT (_hoops_GGCPH->bounding->flags, _hoops_AAPGP))
				HI_Refresh_Segment_Bounding ((_hoops_CRCP alter *)_hoops_GGCPH);

			if (!_hoops_GGCPH->bounding._hoops_HICAR()) {
				Bounding		_hoops_RGPAS = _hoops_GGCPH->bounding;
				bool			_hoops_RHAPI = false;

				if (_hoops_GGCPH->_hoops_IPPGR != null) {
					Attribute *			_hoops_PSACR = null;

					HI_Gather_Modelling (_hoops_GGCPH->_hoops_IPPGR, &_hoops_PSACR);
					_hoops_RHAPI = HI_Bounding_Is_Excluded (_hoops_GGCPH->_hoops_IPPGR);
					if (_hoops_PSACR != null) {
						_hoops_RGPAS = _hoops_RGPAS._hoops_SCIS (&((_hoops_ISGI *)_hoops_PSACR)->matrix.elements[0][0]);
						_hoops_HPRH (_hoops_PSACR);
					}
				}
				if (!_hoops_RHAPI)
					_hoops_SRCP->bounding.Merge (_hoops_RGPAS);
			}
		}
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);

	if (_hoops_SRCP->_hoops_HSRIR != null && BIT (_hoops_SRCP->_hoops_HSRIR->flags, _hoops_AAPGP)) {
		_hoops_SRCP->_hoops_HSRIR = Bounding::Create();

		if ((geometry = _hoops_SRCP->geometry) != null) do {
			Bounding		_hoops_HSIGA;

			if (HI_Figure_Geometry_Bounding (geometry, _hoops_HSIGA))
				_hoops_SRCP->_hoops_HSRIR.Merge (_hoops_HSIGA);
		} while ((geometry = geometry->next) != null);
	}

	if (_hoops_SRCP->_hoops_SSRIR() != null) {
		_hoops_PGAIR *		_hoops_HGAIR = _hoops_SRCP->_hoops_SSRIR();

		for (int i = 0; i < _hoops_IGAIR; i++) {
			if ((geometry = _hoops_HGAIR->data[i]) != null) do {
				Bounding		_hoops_HSIGA;

				if (HI_Figure_Geometry_Bounding (geometry, _hoops_HSIGA))
					_hoops_SRCP->_hoops_HSRIR.Merge (_hoops_HSIGA);
			} while ((geometry = geometry->next) != null);
		}
	}

	_hoops_SRCP->bounding.Merge (_hoops_SRCP->_hoops_HSRIR);
}

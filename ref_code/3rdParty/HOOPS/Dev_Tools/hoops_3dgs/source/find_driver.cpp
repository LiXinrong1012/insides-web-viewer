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
 * $Id: obf_tmp.txt 1.56 2010-07-09 23:50:15 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "please.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


local _hoops_GGAGR * _hoops_ARCPH (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			name,
	_hoops_CRCP **				_hoops_PRCPH) {
	_hoops_CRCP *				display;
	Attribute *				_hoops_HPHCR;

	if ((*_hoops_PRCPH = display = HI_One_Segment_Search (_hoops_RIGC, name, true)) == null)
		return null;

	if ((_hoops_HPHCR = display->_hoops_IPPGR) != null) {
		do if (_hoops_HPHCR->type == HK_DRIVER)
			break;
		while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
	}

	return (_hoops_GGAGR *)_hoops_HPHCR;
}


GLOBAL_FUNCTION _hoops_GGAGR * HI_Force_Find_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			name) 
{
	_hoops_RSIIR(_hoops_RIGC);
	_hoops_CRCP *	_hoops_SRCP;

	_hoops_GGAGR *	_hoops_GHRI = _hoops_ARCPH (_hoops_RIGC, name, &_hoops_SRCP);

	if (_hoops_SRCP == null) 
		return null;

	if (_hoops_GHRI == null) {
		HE_ERROR (HEC_DRIVER, HES_DRIVER_ATTRIBUTE_ABSENT, Sprintf_P (null, "Segment '%p' does not have a actor attribute", _hoops_SRCP));
	}
	else {
		if (!ANYBIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA|_hoops_SGPIR))
			HI_Initialize_Actor (_hoops_RIGC, _hoops_GHRI);	/* _hoops_SRSCA _hoops_PCSHA _hoops_GASCA */

		if (!BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA)) {
			HE_ERROR (HEC_DRIVER, HES_DEAD_DRIVER, Sprintf_P (null, "The device for '%p' doesn't seem to be alive", _hoops_SRCP));
			_hoops_GHRI = null;
		}
	}

	return _hoops_GHRI;
}


/* _hoops_GAR _hoops_ARRS, _hoops_HIH _hoops_SIHH _hoops_RH _hoops_HRCPH _hoops_HGISR */

GLOBAL_FUNCTION _hoops_GGAGR * HI_Find_Actor (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			name) {
	_hoops_CRCP *				_hoops_SRCP;
	_hoops_GGAGR *					_hoops_GHRI = null;

	_hoops_CSPPR();
	_hoops_GHRI = _hoops_ARCPH (_hoops_RIGC, name, &_hoops_SRCP);

	if (_hoops_SRCP == null) {}
	else if (_hoops_GHRI == null) {
		HE_ERROR (HEC_DRIVER, HES_DRIVER_ATTRIBUTE_ABSENT,
				Sprintf_P (null, "Segment '%p' does not have a driver attribute", _hoops_SRCP));

	}
	else if (!BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA)) {
		HE_ERROR (HEC_DRIVER, HES_DEAD_DRIVER,
				Sprintf_P (null, "The device for '%p' doesn't seem to be alive", _hoops_SRCP));
		_hoops_GHRI = null;
	}

	_hoops_IRRPR();

	return _hoops_GHRI;
}


/* _hoops_CRICR, _hoops_HIH _hoops_RH _hoops_RHPP _hoops_GHCA _hoops_SHH _hoops_GH _hoops_ARRS _hoops_RH _hoops_CHIA _hoops_CAGH */

GLOBAL_FUNCTION _hoops_GGAGR *HI_Find_Owner_Actor (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			segname,
	_hoops_CRCP **				_hoops_PRCPH) 
{
	_hoops_CRCP *				_hoops_SRCP;
	Attribute *				_hoops_HPHCR;
	_hoops_GGAGR *					_hoops_GHRI = null;

	_hoops_CSPPR();

	if (_hoops_PRCPH)
		*_hoops_PRCPH = null;

	if ((_hoops_SRCP = HI_One_Segment_Search (_hoops_RIGC, segname, true)) == null) 
		goto _hoops_PRSPR;

	if (_hoops_PRCPH)
		*_hoops_PRCPH = _hoops_SRCP;

	do {
		if ((_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR) != null) {
			do if (_hoops_HPHCR->type == HK_DRIVER) {
				_hoops_GHRI = (_hoops_GGAGR *)_hoops_HPHCR;

				if (_hoops_GHRI->connected_action != _hoops_GHRI->action)
					goto _hoops_PRSPR;
			} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
		}
		_hoops_SRCP = _hoops_SRCP->owner;
	} while (_hoops_SRCP->type != _hoops_PRAIR);

	_hoops_GHRI = null;

_hoops_PRSPR:

	_hoops_IRRPR();

	/* _hoops_PIRC _hoops_GSGI */
	return _hoops_GHRI;
}

GLOBAL_FUNCTION _hoops_GGAGR * HI_Force_Find_Owner_Actor (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			segname,
	_hoops_CRCP **				_hoops_PRCPH) 
{
	_hoops_GGAGR *					_hoops_GHRI = null;

	_hoops_CSPPR();

	_hoops_GHRI = HI_Find_Owner_Actor (_hoops_RIGC, segname, _hoops_PRCPH);

	if (*_hoops_PRCPH == null) 
		goto _hoops_PRSPR;

	if (_hoops_GHRI == null) {
		HE_ERROR (HEC_DRIVER, HES_NO_ACTIVE_DISPLAY_DRIVER,
				Sprintf_S (null,"Cannot find a display driver at or above '%s'", segname));
	}
	else {
		if (!ANYBIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA|_hoops_SGPIR))
			HI_Initialize_Actor (_hoops_RIGC, _hoops_GHRI);	/* _hoops_SRSCA _hoops_RHPP _hoops_GASCA */

		if (!BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA)) {
			HE_ERROR (HEC_DRIVER, HES_DEAD_DRIVER,
					Sprintf_P (null, "The device for '%p' doesn't seem to be alive", *_hoops_PRCPH));
			_hoops_GHRI = null;
		}
	}

_hoops_PRSPR:

	_hoops_IRRPR();

	return _hoops_GHRI;
}



local _hoops_GGAGR * find_path_driver (
	int						count,
	_hoops_CRCP const **		_hoops_SISAA,
	_hoops_CRCP **				_hoops_PRCPH) {
	_hoops_CRCP const *			_hoops_SRCP = null;
	Attribute *				_hoops_HPHCR;

	if (count <= 0)
		return null;

	if (_hoops_SISAA[count-1]->type != _hoops_IRCP) {
		if (--count == 0) {
			_hoops_SISAA = (_hoops_CRCP const **)&_hoops_SISAA[0]->owner;
			count = 1;
		}
	}

	_hoops_SISAA += count;	/* _hoops_HSPP _hoops_HII _hoops_RII _hoops_RSGR */

	while (count-- > 0) {
		_hoops_SRCP = *--_hoops_SISAA;

		if ((_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR) != null) {
			do if (_hoops_HPHCR->type == HK_DRIVER) {
				_hoops_GGAGR *	driver = (_hoops_GGAGR *)_hoops_HPHCR;

				if (driver->connected_action != driver->action) {
					*_hoops_PRCPH = (_hoops_CRCP *)_hoops_SRCP;
					return driver;
				}
			} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
		}
	}

	/* _hoops_HPPR _hoops_SIACP _hoops_GH _hoops_HII _hoops_IIH */
	_hoops_SRCP = _hoops_SRCP->owner;
	if (_hoops_SRCP->type != _hoops_PRAIR) do {
		if ((_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR) != null) {
			do if (_hoops_HPHCR->type == HK_DRIVER) {
				_hoops_GGAGR *	driver = (_hoops_GGAGR *)_hoops_HPHCR;

				if (driver->connected_action != driver->action) {
					*_hoops_PRCPH = (_hoops_CRCP *)_hoops_SRCP;
					return driver;
				}
			} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
		}

		_hoops_SRCP = _hoops_SRCP->owner;
	} while (_hoops_SRCP->type != _hoops_PRAIR);

	/* _hoops_PIRC _hoops_GSGI */
	return null;
}


GLOBAL_FUNCTION _hoops_GGAGR * HI_Force_Find_Path_Actor (
	_hoops_AIGPR *	_hoops_RIGC,
	int						count,
	_hoops_CRCP const **		_hoops_SISAA,
	_hoops_CRCP **				_hoops_PRCPH) {
	_hoops_GGAGR *					_hoops_GHRI = null;

	_hoops_CSPPR();

	_hoops_GHRI = find_path_driver (count, _hoops_SISAA, _hoops_PRCPH);

	if (_hoops_GHRI == null) {
		HE_ERROR (HEC_DRIVER, HES_NO_ACTIVE_DISPLAY_DRIVER,
				  "Cannot find a display driver in specified path");
	}
	else {
		if (!ANYBIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA|_hoops_SGPIR))
			HI_Initialize_Actor (_hoops_RIGC, _hoops_GHRI);	/* _hoops_SRSCA _hoops_PCSHA _hoops_GASCA */

		if (!BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA)) {
			HE_ERROR (HEC_DRIVER, HES_DEAD_DRIVER,
					Sprintf_P (null, "The device for '%p' doesn't seem to be alive", *_hoops_PRCPH));
			_hoops_GHRI = null;
		}
	}

	_hoops_IRRPR();

	return _hoops_GHRI;
}



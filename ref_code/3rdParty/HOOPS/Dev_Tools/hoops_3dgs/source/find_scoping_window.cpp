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
 * $Id: obf_tmp.txt 1.37 2010-12-09 23:35:54 heppe Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"
#include "hpserror.h"


/*
 * _hoops_ACGR _hoops_IRS _hoops_CAGH'_hoops_GRI _hoops_RPPS _hoops_IGRI, _hoops_PAR, _hoops_RPP _hoops_PHGHH, _hoops_RGCI _hoops_RSPH _hoops_RPPS
 * _hoops_ASSA _hoops_RH _hoops_RHPP _hoops_IGRI.
 *
 * _hoops_HSRR _hoops_GCGC _hoops_IIGR _hoops_RPPS _hoops_CPGGR _hoops_RIP _hoops_HHGHH.
 */

GLOBAL_FUNCTION Window * HI_Find_Scoping_Window (
	_hoops_CRCP const *		_hoops_SRCP) {
	Attribute *			_hoops_HPHCR;

	if ((_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR) != null) {
		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) {
			Window				*_hoops_IHGHH = null;

			/** _hoops_CHGHH _hoops_PCIAA _hoops_RCPS _hoops_ARPP _hoops_SPHGR! **/

			do {
				if (_hoops_HPHCR->type > HK_STYLE) {
					do if (_hoops_HPHCR->type == HK_WINDOW)
						return (Window *)_hoops_HPHCR;
					while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
					break;
				}
#ifndef DISABLE_STYLE_SEGMENT
				else if (_hoops_HPHCR->type == HK_STYLE) {
					Style *		style = (Style *)_hoops_HPHCR;

					if (style->_hoops_IGRPR && 
						BIT (style->_hoops_IGRPR->_hoops_PHSI, _hoops_SHSIR))
						_hoops_IHGHH = HI_Find_Scoping_Window (style->_hoops_IGRPR);
				}
#endif
			} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);

			if (_hoops_IHGHH != null) return _hoops_IHGHH;
		}
		else if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_HIHGP)) {
			do if (_hoops_HPHCR->type == HK_DRIVER)
				return &((_hoops_GGAGR *)_hoops_HPHCR)->_hoops_CSGPR;
			while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
		}
	}

	HE_ERROR2 (HEC_INTERNAL_ERROR, HES_BAD_WINDOW_SCOPE,
			"There was an unexpected Hoops internal error -",
			   "Expected window scope couldn't be found");
	return null;
}

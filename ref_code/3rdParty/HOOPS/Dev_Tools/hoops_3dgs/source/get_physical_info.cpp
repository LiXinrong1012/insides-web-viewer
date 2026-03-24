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
 * $Id: obf_tmp.txt 1.115 2010-06-04 21:37:17 jason Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "database.h"
#include "phedron.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


GLOBAL_FUNCTION void HD_Get_Gamma_Table (
	Display_Context alter	*dc,
	bool					_hoops_GGGIH) {
	Integer32				index;

	index = dc->_hoops_PGCC._hoops_PCHSR - 1;

	if (_hoops_GGGIH) {
		float			scale;

		scale = (float)index /* - 0.01f */;

		do {
			Integer32	_hoops_HHHHP;

			_hoops_HHHHP = (Integer32)(_hoops_SGIHR ((float)(index)/scale) * scale);

			/* _hoops_ARRPA _hoops_ISPR */
			if (_hoops_HHHHP >= dc->_hoops_PGCC._hoops_PCHSR)
				_hoops_HHHHP = dc->_hoops_PGCC._hoops_PCHSR - 1;

#		if _hoops_PHRSP > 256
			dc->_hoops_PGCC._hoops_HHHHP[index] = (short)_hoops_HHHHP;
#		else
			dc->_hoops_PGCC._hoops_HHHHP[index] = (unsigned char)_hoops_HHHHP;
#		endif
		} _hoops_RGGA (--index < 0);
	}
	else {
		do {
#		if _hoops_PHRSP > 256
			dc->_hoops_PGCC._hoops_HHHHP[index] = (short)index;
#		else
			dc->_hoops_PGCC._hoops_HHHHP[index] = (unsigned char)index;
#		endif
		} _hoops_RGGA (--index < 0);
	}
}


GLOBAL_FUNCTION void HD_Get_Physical_Info (
	Display_Context alter		*dc) {

	SET_MEMORY(&dc->_hoops_PGCC, sizeof(dc->_hoops_PGCC), 0);

	dc->_hoops_PGCC._hoops_PIPGH = true;
	dc->_hoops_PGCC._hoops_IHHSR = 1;
	dc->_hoops_PGCC._hoops_CHHSR = _hoops_SHHSR;
	dc->_hoops_PGCC._hoops_PIHSR = _hoops_SIHSR;
	dc->_hoops_PGCC._hoops_PCHSR = 256;
	dc->_hoops_PGCC._hoops_CIPGH.r =
		dc->_hoops_PGCC._hoops_CIPGH.g =
		dc->_hoops_PGCC._hoops_CIPGH.b = 6;

	dc->_hoops_PGCC._hoops_ASHSR = 1;
	dc->_hoops_PGCC._hoops_SCHSR = "$Revision: 1.115 $";
	dc->_hoops_PGCC._hoops_ICHSR = "frame buffer";
	dc->_hoops_PGCC._hoops_RCPGH = "mouse";
	dc->_hoops_PGCC._hoops_ICPGH = 1.0f;
	dc->_hoops_PGCC._hoops_CCPGH = 1.0f;
	dc->_hoops_PGCC._hoops_AHAGH = 1;

	dc->_hoops_PGCC.flags |= _hoops_CAPGH | _hoops_RSHSR | _hoops_PSHSR|
							_hoops_HSHSR |	_hoops_GGISR;

	dc->flags |= _hoops_RAAGH;

	(*dc->_hoops_ACPGR->get_physical_info)(dc);

	if (dc->_hoops_PGCC.driver_type == null) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						   "Driver failed to fill in \"driver type\"");
		dc->_hoops_PGCC.driver_type = "unknown";
	}

	if (dc->_hoops_PGCC._hoops_PRPSR.x < 1 ||
		dc->_hoops_PGCC._hoops_PRPSR.y < 1) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						   "Driver failed to fill in \"number of pixels\"");
		dc->_hoops_PGCC._hoops_PRPSR.x = 1280;
		dc->_hoops_PGCC._hoops_PRPSR.y = 1024;
	}

	if (dc->_hoops_PGCC.size.x <= 0.0f || dc->_hoops_PGCC.size.y <= 0.0f) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						   "Driver failed to fill in \"size\"");
		dc->_hoops_PGCC.size.x = 10.0f * 2.54f;
		dc->_hoops_PGCC.size.y = 8.0f * 2.54f;
	}

	if (dc->_hoops_PGCC._hoops_HGCC == 0 &&
		(BIT(dc->_hoops_PGCC.flags, _hoops_GPPGH) || 
		 BIT(dc->_hoops_PGCC.flags, _hoops_RPPGH)))
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						   "Driver specified hardware gouraud/phong lighting, but no lights!");

	/* _hoops_CSGA _hoops_RII _hoops_SAPIA _hoops_PHPHA _hoops_RGGHR */
	if (dc->_hoops_PGCC._hoops_HHPGH < dc->_hoops_PGCC._hoops_AAPSR)
		dc->_hoops_PGCC._hoops_HHPGH = dc->_hoops_PGCC._hoops_AAPSR;

	dc->_hoops_PGCC.extent.left = (float)dc->_hoops_PGCC._hoops_ARISR.x;
	dc->_hoops_PGCC.extent.bottom = (float)dc->_hoops_PGCC._hoops_ARISR.y;
	dc->_hoops_PGCC.extent.right = dc->_hoops_PGCC._hoops_ARISR.x +
		dc->_hoops_PGCC._hoops_PRPSR.x - 0.001f;
	dc->_hoops_PGCC.extent.top = dc->_hoops_PGCC._hoops_ARISR.y +
		dc->_hoops_PGCC._hoops_PRPSR.y - 0.001f;

	if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
		if (dc->_hoops_PGCC._hoops_AAPSR >= 250)
			dc->_hoops_PGCC._hoops_GCPRP = 125;
		else if (dc->_hoops_PGCC._hoops_AAPSR >= 128)
			dc->_hoops_PGCC._hoops_GCPRP = 64;
		else if (dc->_hoops_PGCC._hoops_AAPSR >= 54)
			dc->_hoops_PGCC._hoops_GCPRP = 27;
		else if (dc->_hoops_PGCC._hoops_AAPSR >= 10)
			dc->_hoops_PGCC._hoops_GCPRP = 8;
		else
			dc->_hoops_PGCC._hoops_GCPRP = 0;
	}

	HD_Get_Gamma_Table (dc, BIT(dc->_hoops_PGCC.flags, _hoops_GGISR) &&
							dc->options._hoops_SRSSP);

	/* _hoops_IRHH _hoops_RCRR _hoops_SSH _hoops_SRHR _hoops_HCH _hoops_HRGR _hoops_GGR _hoops_CCIR _hoops_PPR _hoops_SRSHR _hoops_IRS _hoops_RIRA _hoops_AHPA */
	if (dc->_hoops_PGCC._hoops_HASHP > 0) {
		dc->flags &= ~_hoops_AASHP;
		dc->_hoops_PGCC._hoops_PASHP = (float)((1UL << dc->_hoops_PGCC._hoops_HASHP) - 1);
	}
	else {
		dc->flags |= _hoops_AASHP;
		dc->_hoops_PGCC._hoops_PASHP = (float)_hoops_HSCHA;
	}

	/* _hoops_GGR _hoops_AGIR _hoops_RHAGH _hoops_SAGGR _hoops_PIGS _hoops_ARPP _hoops_RGGIH */
	dc->current.border.left = 0;
	dc->current.border.right = 0;
	dc->current.border.bottom = 0;
	dc->current.border.top = 0;
}

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
 * $Id: obf_tmp.txt 1.59 2010-06-04 21:37:17 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


local void _hoops_GSSHH (
	Display_Context alter *		dc,
	char const *				message) {

	HE_ERROR2 (HEC_DRIVER, HES_INVALID_SUBSCREEN_SPEC,
			Sprintf_S (null, "Invalid subscreen specification - %s",
						  message),
			   "-- Will use (-1, +1, -1, +1) --");

	dc->options._hoops_HCPRP.bottom = dc->options._hoops_HCPRP.left = -1.0f;
	dc->options._hoops_HCPRP.top = dc->options._hoops_HCPRP.right = 1.0f;
}


GLOBAL_FUNCTION void HD_Get_Current_Info (
	Display_Context alter *		dc) {
	float						_hoops_RSSHH;
	int							_hoops_ASSHH[3];
	XY const *					size;
	_hoops_PACIR			_hoops_PHGIP;

	if (dc->options._hoops_SPHSR.x < 0.0f)
		size = &dc->_hoops_PGCC.size;
	else
		size = &dc->options._hoops_SPHSR;


	if (!BIT(dc->_hoops_PGCC.flags, _hoops_HSHSR) &&
		(dc->options._hoops_HCPRP.bottom < -1.0f ||
		 dc->options._hoops_HCPRP.left < -1.0f ||
		 dc->options._hoops_HCPRP.right > 1.0f ||
		 dc->options._hoops_HCPRP.top > 1.0f))
		_hoops_GSSHH (dc, "Values are not between -1 and +1");
	else if (dc->options._hoops_HCPRP.left > dc->options._hoops_HCPRP.right)
		_hoops_GSSHH (dc, "Subscreen 'left' is to the right of 'right'");
	else if (dc->options._hoops_HCPRP.bottom > dc->options._hoops_HCPRP.top)
		_hoops_GSSHH (dc, "Subscreen 'bottom' is above 'top'");


	if (dc->options._hoops_ARPSR && BIT(dc->_hoops_PGCC.flags, _hoops_ISHSR)) {
		/* _hoops_PIIA _hoops_SISR & _hoops_HAPC  _hoops_HII _hoops_CPHSR _hoops_IS _hoops_SCGR */

		dc->current._hoops_HAP.x =
				dc->_hoops_PGCC._hoops_PRPSR.y / size->y;
		dc->current._hoops_HAP.y =
				dc->_hoops_PGCC._hoops_PRPSR.x / size->x;

		dc->current.extent.left =
				(dc->_hoops_PGCC.extent.top - dc->_hoops_PGCC.extent.bottom) *
				(dc->options._hoops_HCPRP.left + 1.0f) / 2.0f +
				dc->_hoops_PGCC.extent.bottom;

		dc->current.extent.right =
				(dc->_hoops_PGCC.extent.top - dc->_hoops_PGCC.extent.bottom) *
				(dc->options._hoops_HCPRP.right + 1.0f) / 2.0f +
				dc->_hoops_PGCC.extent.bottom;

		dc->current.extent.bottom =
				(dc->_hoops_PGCC.extent.right - dc->_hoops_PGCC.extent.left) *
				(dc->options._hoops_HCPRP.bottom + 1.0f) / 2.0f +
				dc->_hoops_PGCC.extent.left;

		dc->current.extent.top =
				(dc->_hoops_PGCC.extent.right - dc->_hoops_PGCC.extent.left) *
				(dc->options._hoops_HCPRP.top + 1.0f) / 2.0f +
				dc->_hoops_PGCC.extent.left;
	}
	else {
		dc->current._hoops_HAP.x =
				dc->_hoops_PGCC._hoops_PRPSR.x / size->x;
		dc->current._hoops_HAP.y =
				dc->_hoops_PGCC._hoops_PRPSR.y / size->y;

		dc->current.extent.left =
				(dc->_hoops_PGCC.extent.right - dc->_hoops_PGCC.extent.left) *
				(dc->options._hoops_HCPRP.left + 1.0f) / 2.0f +
				dc->_hoops_PGCC.extent.left;

		dc->current.extent.right =
				(dc->_hoops_PGCC.extent.right - dc->_hoops_PGCC.extent.left) *
				(dc->options._hoops_HCPRP.right + 1.0f) / 2.0f +
				dc->_hoops_PGCC.extent.left;

		dc->current.extent.bottom =
				(dc->_hoops_PGCC.extent.top - dc->_hoops_PGCC.extent.bottom) *
				(dc->options._hoops_HCPRP.bottom + 1.0f) / 2.0f +
				dc->_hoops_PGCC.extent.bottom;

		dc->current.extent.top =
				(dc->_hoops_PGCC.extent.top - dc->_hoops_PGCC.extent.bottom) *
				(dc->options._hoops_HCPRP.top + 1.0f) / 2.0f +
				dc->_hoops_PGCC.extent.bottom;
	}


	dc->current.extent.left = (float)FLOOR (dc->current.extent.left);
	dc->current.extent.right = FLOOR (dc->current.extent.right) + 0.99f;
	dc->current.extent.bottom = (float)FLOOR (dc->current.extent.bottom);
	dc->current.extent.top = FLOOR (dc->current.extent.top) + 0.99f;

	dc->current._hoops_AGRS = dc->current._hoops_HAP.x /
							   dc->current._hoops_HAP.y;


	if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR)
				dc->current._hoops_AAPSR = (1<<24);
		else
				if (dc->_hoops_PGCC._hoops_PIHSR != _hoops_SIHSR) {
						dc->current._hoops_AAPSR = 0;
						dc->current._hoops_GCPRP = 0;
	} else {
		dc->current._hoops_APASR = dc->_hoops_PGCC._hoops_APASR;

		if (dc->options._hoops_AAPSR < 2) {
#if 0
			HE_WARNING (HEC_COLOR, HES_SMALL_NUMBER_OF_COLORS,
					Sprintf_LD (null,
						"'Number of colors = %D' is not enough for anything",
						dc->options._hoops_AAPSR));
#endif
			dc->current._hoops_AAPSR = dc->_hoops_PGCC._hoops_AAPSR;
		}
		else
			dc->current._hoops_AAPSR = _hoops_AHIA (dc->_hoops_PGCC._hoops_HHPGH,
												dc->options._hoops_AAPSR);

		if (dc->options._hoops_APASR < 0) {
			HE_WARNING (HEC_COLOR, HES_INVALID_FIRST_COLOR,
					Sprintf_LD (null,
							"'First color = %D' is not reasonable",
							dc->options._hoops_AAPSR));
			dc->current._hoops_APASR = dc->_hoops_PGCC._hoops_APASR;
		}
		else
			dc->current._hoops_APASR = _hoops_IAAA (dc->_hoops_PGCC._hoops_APASR,
										   dc->options._hoops_APASR);

		if (dc->current._hoops_APASR + dc->current._hoops_AAPSR >
			dc->_hoops_PGCC._hoops_APASR + dc->_hoops_PGCC._hoops_HHPGH) {
			/*
			 * _hoops_PPIAR _hoops_AHPH _hoops_PSHA.	 _hoops_PSSHH _hoops_IRAA _hoops_RCPPR _hoops_IAPR _hoops_HSSHH.
			 * _hoops_CGP _hoops_GIPR _hoops_HGRC, _hoops_ISSHH _hoops_AGGRA _hoops_IAPR _hoops_RPASR
			 */

			if (BIT (dc->options.values, _hoops_SCARP) &&
				!BIT (dc->options.values, _hoops_ISARP)) {
				dc->current._hoops_AAPSR = (int)
										   (dc->_hoops_PGCC._hoops_APASR +
											dc->_hoops_PGCC._hoops_HHPGH -
											dc->current._hoops_APASR);
			}
			else {
				if (ALLBITS (dc->options.values, _hoops_SCARP |
												_hoops_ISARP)) {
					_hoops_PHPGR (HEC_DRIVER, HES_FIRST_COLOR_IGNORED,
								 "First color setting plus number of colors",
								 "setting exceeds device number of colors");
				}
				dc->current._hoops_APASR = (int)
										   (dc->_hoops_PGCC._hoops_APASR +
											dc->_hoops_PGCC._hoops_HHPGH -
											dc->current._hoops_AAPSR);
			}
		}

		dc->current._hoops_GCPRP = dc->options._hoops_GCPRP;
	}

	_hoops_PHGIP.left = dc->current.extent.left;
	_hoops_PHGIP.right = dc->current.extent.right;
	_hoops_PHGIP.bottom = dc->current.extent.bottom;
	_hoops_PHGIP.top = dc->current.extent.top;

	dc->current.border.left = 0;
	dc->current.border.right = 0;
	dc->current.border.bottom = 0;
	dc->current.border.top = 0;

	(*dc->_hoops_ACPGR->get_current_info)(dc);

	if (dc->options._hoops_HPHRP) {
		/* _hoops_AAPA _hoops_PAPA _hoops_PPGP _hoops_AGRP, _hoops_SSPC _hoops_GII _hoops_RHPP _hoops_IGRSP */
		dc->current.extent.left = _hoops_PHGIP.left + dc->current.border.left;
		dc->current.extent.right = _hoops_PHGIP.right - dc->current.border.right;
		dc->current.extent.bottom = _hoops_PHGIP.bottom + dc->current.border.bottom;
		dc->current.extent.top = _hoops_PHGIP.top - dc->current.border.top;
	}
	else {
		dc->current.extent.left += (float)dc->current.border.left;
		dc->current.extent.right -= (float)dc->current.border.right;
		dc->current.extent.bottom += (float)dc->current.border.bottom;
		dc->current.extent.top -= (float)dc->current.border.top;
	}

	if (dc->options._hoops_RAHHP) dc->current._hoops_AAPSR = 2;

	/* _hoops_CCIH _hoops_GH _hoops_HAH-_hoops_RISA _hoops_SPHGR */
	_hoops_RSSHH = 4.0f*dc->_hoops_PGCC._hoops_IHHSR + 1.0f -
				(dc->current.extent.right - dc->current.extent.left);

	if (_hoops_RSSHH > 0.0f) {
		if (dc->_hoops_PGCC.extent.right - dc->current.extent.right >= _hoops_RSSHH)
			dc->current.extent.right += _hoops_RSSHH;
		else
			dc->current.extent.left += _hoops_RSSHH;
	}

	_hoops_RSSHH = 4.0f*dc->_hoops_PGCC._hoops_IHHSR + 1.0f -
				(dc->current.extent.top - dc->current.extent.bottom);

	if (_hoops_RSSHH > 0.0f) {
		if (dc->_hoops_PGCC.extent.top - dc->current.extent.top >= _hoops_RSSHH)
			dc->current.extent.top += _hoops_RSSHH;
		else
			dc->current.extent.bottom += _hoops_RSSHH;
	}

	/* _hoops_CRHR _hoops_CSSHH _hoops_SHPH _hoops_HII _hoops_GHGA _hoops_PA... */

	if (dc->current._hoops_GCPRP >= 0) {
		int				_hoops_SSSHH = dc->current._hoops_GCPRP;

		HD_Determine_Fixed_Colors (dc, dc->current._hoops_GCPRP,
								   &dc->current._hoops_GCPRP, _hoops_ASSHH);

		if (dc->current._hoops_GCPRP != _hoops_SSSHH) {
			dc->options._hoops_GCPRP = dc->current._hoops_GCPRP;
			dc->options._hoops_IPSSP[0] = _hoops_ASSHH[0];
			dc->options._hoops_IPSSP[1] = _hoops_ASSHH[1];
			dc->options._hoops_IPSSP[2] = _hoops_ASSHH[2];
		}
	}

	dc->current.extent.left = (float)FLOOR (dc->current.extent.left);
	dc->current.extent.right = FLOOR (dc->current.extent.right) + 0.99f;
	dc->current.extent.bottom = (float)FLOOR (dc->current.extent.bottom);
	dc->current.extent.top = FLOOR (dc->current.extent.top) + 0.99f;

	dc->current._hoops_ARISR.x = (int)dc->current.extent.left;
	dc->current._hoops_ARISR.y = (int)dc->current.extent.bottom;
	dc->current._hoops_PRPSR.x = (int)(dc->current.extent.right -
										   dc->current.extent.left) + 1;
	dc->current._hoops_PRPSR.y = (int)(dc->current.extent.top -
										   dc->current.extent.bottom) + 1;
	dc->current.size.x = dc->current._hoops_PRPSR.x /
						 dc->current._hoops_HAP.x;
	dc->current.size.y = dc->current._hoops_PRPSR.y /
						 dc->current._hoops_HAP.y;
}

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
 * $Id: obf_tmp.txt 1.36 2009-11-09 23:59:19 jason Exp $
 */


#include "hoops.h"
#include "driver.h"
#include "hd_proto.h"
#include "database.h"


GLOBAL_FUNCTION void HD_Std_DC_Colorized_Polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors,
	bool						single) {
	Net_Rendition				_hoops_RHICP;
	Display_Context const *		dc = nr->_hoops_SRA;
	int							_hoops_RRC;

	_hoops_ICHC (count, _hoops_RRC, 2);

	if ((ANYBIT (nr->current, _hoops_RSSHP|
											 _hoops_CISHP) &&
		nr->_hoops_ASIR->buffer._hoops_GHAAP == _hoops_PHAAP) ||
		dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) {
		int						_hoops_IIICS;

		_hoops_IIICS = dc->_hoops_PGCC._hoops_PIHSR;

		/* (_hoops_HGPSA _hoops_HIIC) */
		((Display_Context alter *)dc)->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;

		while (count-- > 0) {
			_hoops_RHICP = nr;
			_hoops_RHICP.Modify()->_hoops_AHP.Modify()->color = *colors;

			_hoops_ICGCP (_hoops_RHICP, points);

			points += _hoops_RRC;
			if (!single)
				colors++;
		}

		((Display_Context alter *)dc)->_hoops_PGCC._hoops_PIHSR = _hoops_IIICS;

	}
	else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
		_hoops_GARSR		_hoops_IASGR[4+1];
		int				_hoops_AHHIR[3+1];

		while (count-- > 0) {
			_hoops_RHICP = nr;
			/* _hoops_SGH "_hoops_AAH" _hoops_HAIR */
			(void)HD_Find_Dither_Pattern (nr, colors, _hoops_IASGR, _hoops_AHHIR);
			_hoops_RHICP.Modify()->_hoops_AHP.Modify()->color._hoops_PGGCR = _hoops_IASGR[0];

			_hoops_ICGCP (_hoops_RHICP, points);

			points += _hoops_RRC;
			if (!single)
				colors++;
		}
	}
	else /* _hoops_AIHHP */ {
		RGB			rgb;

		while (count-- > 0) {
			_hoops_RHICP = nr;
			rgb = *colors;
			_hoops_RHICP.Modify()->_hoops_AHP.Modify()->color._hoops_PIHHP =
				(_hoops_HIHHP)(rgb._hoops_CPIR() * ((float)dc->_hoops_PGCC._hoops_PCHSR - 0.01f));

			_hoops_ICGCP (_hoops_RHICP, points);

			points += _hoops_RRC;
			if (!single)
				colors++;
		}
	}
}

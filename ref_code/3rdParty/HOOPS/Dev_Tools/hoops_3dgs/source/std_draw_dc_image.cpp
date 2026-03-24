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
 * $Id: obf_tmp.txt 1.49 2009-11-24 03:37:13 covey Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


GLOBAL_FUNCTION void HD_Std_DC_Image (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							hoffset,
	Image_Format				format,
	int							row_bytes,
	void const * const *		_hoops_HCHIH,
	int							pattern,
	Driver_Color const *		contrast_color,
	Image const *				db_image) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_IPCGA		_hoops_HPCGA;

	/* _hoops_SSCR _hoops_PCPA _hoops_ISCP '_hoops_HPHR' _hoops_ACPH _hoops_HRGR _hoops_CPIC _hoops_IS _hoops_SHH. */

	switch (dc->_hoops_PGCC._hoops_PIHSR) {
		case _hoops_SIHSR: {
			if (dc->_hoops_PGCC._hoops_AAPSR <= 256)
				_hoops_HPCGA = HD_Image_To_Mapped8_Rasters;
			else
				_hoops_HPCGA = HD_Image_To_Mapped16_Rasters;
		}	break;

		case _hoops_HIHSR: {
			if (BIT(dc->_hoops_PGCC.flags , _hoops_IAPGH))
				_hoops_HPCGA = HD_Image_To_Mapped8_Rasters;
			else
				_hoops_HPCGA = HD_Image_To_RGB32_Rasters;
		}	break;

		case _hoops_RIIHP: {
			if (dc->_hoops_PGCC._hoops_AAPSR == 2)
				_hoops_HPCGA = HD_Image_To_Bit_Rasters;
			else
				_hoops_HPCGA = HD_Image_To_Gray8_Rasters;
		}	break;

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "Unknown color system");
			return;
		}
	}

	/*
	 * _hoops_HSRR _hoops_RH _hoops_SSCPR _hoops_IIGR _hoops_HICIP, _hoops_GCGRA _hoops_RGR _hoops_AHSGH "_hoops_IPGPA" _hoops_CRGR
	 * _hoops_RH _hoops_ACPH _hoops_GASR(_hoops_GRI). _hoops_HGI _hoops_CGH _hoops_SHH _hoops_PRCCS _hoops_HCCPR _hoops_IHGSR _hoops_HRGR
	 * _hoops_HRCCS _hoops_IRCCS _hoops_CCA _hoops_CSPH->_hoops_CPHSR._hoops_AHRHH _hoops_PAR ._hoops_ISSHH.
	 */
	{
		_hoops_APARR		_hoops_RRCI = (_hoops_APARR alter &)dc->_hoops_IPCI;

		do if (_hoops_RRCI->_hoops_HPCGA == HD_Std_DC_Image)
			_hoops_RRCI->_hoops_HPCGA = _hoops_HPCGA;
		while ((_hoops_RRCI = _hoops_RRCI->prev) != null);
	}

	/* _hoops_PHHR _hoops_IAISR */
	(*_hoops_HPCGA)(nr, start, end,
					 hoffset, format, row_bytes,
					 _hoops_HCHIH,
					 pattern, contrast_color, db_image);
}

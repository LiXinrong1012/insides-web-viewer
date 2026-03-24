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
 * $Id: obf_tmp.txt 1.64 2009-11-24 03:37:08 covey Exp $
 */


#include "hoops.h"
#include "database.h"
#include "patterns.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"


GLOBAL_FUNCTION int HD_Downwind_Text_Font (
	Net_Rendition alter &		nr,
	_hoops_AGPIR const *			font) {
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	int							_hoops_HCHHP = _hoops_ICHHP;

	/* _hoops_GHHS _hoops_IRS _hoops_CCAH _hoops_PCRIP _hoops_GHCA _hoops_SHH _hoops_IHPH -- _hoops_CACH _hoops_RPP _hoops_SR _hoops_CPSA
	 * _hoops_HS _hoops_IS _hoops_AA _hoops_RGR...
	 */

	if ((!BIT (font->_hoops_HAICA, _hoops_RPPAP) ||
		 (font->_hoops_GHGRP == _hoops_HRCIR->_hoops_GHGRP &&
		  font->size == _hoops_HRCIR->_hoops_PHP)) &&

		(!BIT (font->_hoops_HAICA, _hoops_APPAP) ||
		 (font->_hoops_SSPAP == _hoops_HRCIR->_hoops_SSPAP &&
		  font->_hoops_ACPAP == _hoops_HRCIR->_hoops_ACPAP)) &&

		(!BIT (font->_hoops_HAICA, _hoops_PPPAP) ||
		 font->transform == _hoops_HRCIR->transform) &&

		(!BIT (font->_hoops_HAICA, _hoops_HPPAP) ||
		 (BIT (font->_hoops_HAICA, _hoops_SHPAP) && _hoops_HRCIR->_hoops_CRRIP) ||
		 (!BIT (font->_hoops_HAICA, _hoops_SHPAP) && font->rotation == _hoops_HRCIR->rotation)) &&

		(!BIT (font->_hoops_HAICA, _hoops_IPPAP) ||
		 font->width_scale == _hoops_HRCIR->width_scale) &&

		(!BIT (font->_hoops_HAICA, _hoops_CPPAP) ||
		   (font->_hoops_GGHAP == _hoops_HRCIR->_hoops_GGHAP &&
			font->_hoops_PCPAP == _hoops_HRCIR->_hoops_PCPAP)) &&

		(!BIT (font->_hoops_HAICA, _hoops_SPPAP)||
		 font->_hoops_IPGRP == _hoops_HRCIR->_hoops_IPGRP) &&

		(!BIT (font->_hoops_HAICA, _hoops_GHPAP) ||
		 (font->_hoops_RGHAP == _hoops_HRCIR->_hoops_RGHAP &&
		  font->_hoops_HCPAP == _hoops_HRCIR->_hoops_HCPAP)) &&

		(!BIT (font->_hoops_HAICA, _hoops_IIPAP) ||
		 font->_hoops_SGHAP == _hoops_HRCIR->_hoops_SGHAP) &&

		(!BIT (font->_hoops_HAICA, _hoops_RHPAP) ||
		 font->_hoops_ICPAP == _hoops_HRCIR->_hoops_ICPAP) &&

		(BIT (font->_hoops_HAICA & font->_hoops_CPGRP, _hoops_AHPAP) == _hoops_HRCIR->_hoops_HCRIP) &&
		(BIT (font->_hoops_HAICA & font->_hoops_CPGRP, _hoops_GIPAP) == _hoops_HRCIR->_hoops_ICRIP) &&
		(BIT (font->_hoops_HAICA & font->_hoops_CPGRP, _hoops_RIPAP) == _hoops_HRCIR->_hoops_CCRIP) &&
		(BIT (font->_hoops_HAICA & font->_hoops_CPGRP, _hoops_PHPAP) == _hoops_HRCIR->outline) &&
		(BIT (font->_hoops_HAICA & font->_hoops_CPGRP, _hoops_HHPAP) == _hoops_HRCIR->_hoops_SCRIP) &&
		(BIT (font->_hoops_HAICA & font->_hoops_CPGRP, _hoops_IHPAP) == _hoops_HRCIR->_hoops_GSRIP) &&
		(BIT (font->_hoops_HAICA & font->_hoops_CPGRP, _hoops_CHPAP) == _hoops_HRCIR->_hoops_RSRIP) &&
		(BIT (font->_hoops_HAICA & font->_hoops_CPGRP, _hoops_AIPAP) == _hoops_HRCIR->_hoops_ASRIP) &&
		(BIT (font->_hoops_HAICA & font->_hoops_CPGRP, _hoops_PIPAP) == _hoops_HRCIR->_hoops_PSRIP) &&

		(!BIT (font->_hoops_HAICA, _hoops_HIPAP) ||
		 font->_hoops_ISPAP[0] == _hoops_HRCIR->_hoops_ISPAP[0] &&
		 font->_hoops_ISPAP[1] == _hoops_HRCIR->_hoops_ISPAP[1] &&
		 font->_hoops_CCPAP == _hoops_HRCIR->_hoops_CCPAP &&
		 font->_hoops_AGHAP == _hoops_HRCIR->_hoops_AGHAP) &&

		(!BIT (font->_hoops_HAICA, _hoops_CIPAP) ||
		 font->_hoops_CSPAP[0] == _hoops_HRCIR->_hoops_CSPAP[0] &&
		 font->_hoops_CSPAP[1] == _hoops_HRCIR->_hoops_CSPAP[1] &&
		 font->_hoops_SCPAP == _hoops_HRCIR->_hoops_SCPAP &&
		 font->_hoops_PGHAP == _hoops_HRCIR->_hoops_PGHAP) &&

		(font->_hoops_HGPIR == null ||
		 HI_Font_Names_All_Equal (font->_hoops_HGPIR, _hoops_HRCIR->_hoops_HSRIP->_hoops_HGPIR))) {
		/* _hoops_RPAPR */
	}
	else {
		_hoops_IGCSR alter &		_hoops_IRRIP = nr.Modify()->_hoops_SISI.Modify();

		if (BIT (font->_hoops_HAICA, _hoops_RPPAP)) {
			_hoops_IRRIP->_hoops_GHGRP = font->_hoops_GHGRP;
			_hoops_IRRIP->_hoops_PHP = font->size;
		}

		if (BIT (font->_hoops_HAICA, _hoops_APPAP)) {
			_hoops_IRRIP->_hoops_SSPAP = font->_hoops_SSPAP;
			_hoops_IRRIP->_hoops_ACPAP = font->_hoops_ACPAP;
		}

		if (BIT (font->_hoops_HAICA, _hoops_PPPAP)) {
			_hoops_IRRIP->transform = font->transform;
			
			/* _hoops_AHGGR _hoops_GSH _hoops_CAS _hoops_SR _hoops_PGSA _hoops_HCGR _hoops_GGR _hoops_CCSI _hoops_CAPRR */
			_hoops_HCHHP |= _hoops_IPIHP;	
			if (BIT(nr->flags, _hoops_IPIHP))
				nr->flags &= ~_hoops_IPIHP;
		}

		if (BIT (font->_hoops_HAICA, _hoops_IPPAP))
			_hoops_IRRIP->width_scale = font->width_scale;

		if (BIT (font->_hoops_HAICA, _hoops_RHPAP))
			_hoops_IRRIP->_hoops_ICPAP = font->_hoops_ICPAP;

		if (BIT (font->_hoops_HAICA, _hoops_SPPAP))
			_hoops_IRRIP->_hoops_IPGRP = font->_hoops_IPGRP;

		if (BIT (font->_hoops_HAICA, _hoops_AHPAP))
			_hoops_IRRIP->_hoops_HCRIP = BIT (font->_hoops_CPGRP, _hoops_AHPAP);
		if (BIT (font->_hoops_HAICA, _hoops_GIPAP))
			_hoops_IRRIP->_hoops_ICRIP = BIT (font->_hoops_CPGRP, _hoops_GIPAP);
		if (BIT (font->_hoops_HAICA, _hoops_PHPAP))
			_hoops_IRRIP->outline = BIT (font->_hoops_CPGRP, _hoops_PHPAP);
		if (BIT (font->_hoops_HAICA, _hoops_HHPAP))
			_hoops_IRRIP->_hoops_SCRIP = BIT (font->_hoops_CPGRP, _hoops_HHPAP);
		if (BIT (font->_hoops_HAICA, _hoops_IHPAP))
			_hoops_IRRIP->_hoops_GSRIP = BIT (font->_hoops_CPGRP, _hoops_IHPAP);
		if (BIT (font->_hoops_HAICA, _hoops_RIPAP))
			_hoops_IRRIP->_hoops_CCRIP = BIT (font->_hoops_CPGRP, _hoops_RIPAP);
		if (BIT (font->_hoops_HAICA, _hoops_CHPAP))
			_hoops_IRRIP->_hoops_RSRIP = BIT (font->_hoops_CPGRP, _hoops_CHPAP);
		if (BIT (font->_hoops_HAICA, _hoops_AIPAP))
			_hoops_IRRIP->_hoops_ASRIP = BIT (font->_hoops_CPGRP, _hoops_AIPAP);
		if (BIT (font->_hoops_HAICA, _hoops_PIPAP))
			_hoops_IRRIP->_hoops_PSRIP = BIT (font->_hoops_CPGRP, _hoops_PIPAP);

		if (BIT (font->_hoops_HAICA, _hoops_HIPAP)) {
			if (font->_hoops_ISPAP[0] != -1)
				_hoops_IRRIP->_hoops_ISPAP[0] = font->_hoops_ISPAP[0];
			if (font->_hoops_ISPAP[1] != -1)
				_hoops_IRRIP->_hoops_ISPAP[1] = font->_hoops_ISPAP[1];
			if (font->_hoops_AGHAP != _hoops_SHGRP) {
				_hoops_IRRIP->_hoops_CCPAP = font->_hoops_CCPAP;
				_hoops_IRRIP->_hoops_AGHAP = font->_hoops_AGHAP;
			}
		}

		if (BIT (font->_hoops_HAICA, _hoops_CIPAP)) {
			if (font->_hoops_CSPAP[0] != -1)
				if ((_hoops_IRRIP->_hoops_CSPAP[0] = font->_hoops_CSPAP[0]) == _hoops_GRHRP) {
					if (BIT(nr->_hoops_SRA->_hoops_PGCC.flags, _hoops_ISRIP))
						_hoops_IRRIP->_hoops_CSPAP[0] = _hoops_SGHRP;
					else
						_hoops_IRRIP->_hoops_CSPAP[0] = _hoops_CGHRP;
				}
			if (font->_hoops_CSPAP[1] != -1)
				if ((_hoops_IRRIP->_hoops_CSPAP[1] = font->_hoops_CSPAP[1]) == _hoops_GRHRP) {
					if (BIT(nr->_hoops_SRA->_hoops_PGCC.flags, _hoops_ISRIP))
						_hoops_IRRIP->_hoops_CSPAP[1] = _hoops_SGHRP;
					else
						_hoops_IRRIP->_hoops_CSPAP[1] = _hoops_CGHRP;
				}
			if (font->_hoops_PGHAP != _hoops_SHGRP) {
				_hoops_IRRIP->_hoops_SCPAP = font->_hoops_SCPAP;
				_hoops_IRRIP->_hoops_PGHAP = font->_hoops_PGHAP;
			}
		}

		if (BIT (font->_hoops_HAICA, _hoops_HPPAP)) {
			if (BIT (font->_hoops_HAICA, _hoops_SHPAP)) {
				_hoops_IRRIP->_hoops_CRRIP = true;

				if (_hoops_IRRIP->path.x != 0.0f || _hoops_IRRIP->path.y != 0.0f)
					_hoops_IRRIP->rotation = _hoops_AGGGA (_hoops_IRRIP->path.y, _hoops_IRRIP->path.x);
			}
			else{
				_hoops_IRRIP->_hoops_CRRIP = false;
				_hoops_IRRIP->rotation = font->rotation;
			}
		}

		if (BIT (font->_hoops_HAICA, _hoops_CPPAP)) {
			_hoops_IRRIP->_hoops_GGHAP = font->_hoops_GGHAP;
			_hoops_IRRIP->_hoops_PCPAP = font->_hoops_PCPAP;
		}

		if (BIT (font->_hoops_HAICA, _hoops_GHPAP)) { 
			_hoops_IRRIP->_hoops_RGHAP = font->_hoops_RGHAP;
			_hoops_IRRIP->_hoops_HCPAP = font->_hoops_HCPAP;
		}

		if (BIT (font->_hoops_HAICA, _hoops_IIPAP)) { 
			_hoops_IRRIP->_hoops_SGHAP = font->_hoops_SGHAP;
		}

		if (font->_hoops_HGPIR != null) {
			_hoops_HPRH (_hoops_IRRIP->_hoops_HSRIP);
			_hoops_IRRIP->_hoops_HSRIP = font;
			_hoops_PRRH (font);
		}

		// _hoops_PCHIA _hoops_RHGS _hoops_PCRIP _hoops_RPP _hoops_GII; _hoops_CSRIP _hoops_SSRIP _hoops_IRS _hoops_CCAH _hoops_PCRIP _hoops_CCGR _hoops_GGAIP.
		_hoops_IRRIP->_hoops_SRRIP();
	}

	return _hoops_HCHHP;
}

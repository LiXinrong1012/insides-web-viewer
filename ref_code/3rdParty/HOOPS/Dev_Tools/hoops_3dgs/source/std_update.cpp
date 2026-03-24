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
 * $Id: obf_tmp.txt 1.391 2010-12-06 22:05:39 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "patterns.h"
#include "phedron.h"
#include "hidden.h"
#include "tandt.h"
#include "adt.h"

GLOBAL_FUNCTION void HD_Free_Sprite_List (
	Display_Context alter *			dc,
	_hoops_HSIIP alter * alter *	backlink) {
	_hoops_HSIIP alter				*si, *next;

	if ((si = *backlink) == null)
		return;

	do {
		next = si->next;
		if (si->geometry != null)
			_hoops_HPRH (si->geometry);
		if (si->_hoops_ISIIP != null && _hoops_ISAI (si->_hoops_ISIIP) == 0)
			HI_Free_Tristrip (si->_hoops_ISIIP);
		si->nr.release();
		si->path.release();
		FREE (si, _hoops_HSIIP);
	} while ((si = next) != null);

	*backlink = null;
	if (!dc->_hoops_IHIIP[0])
		dc->_hoops_RIHCP = &dc->_hoops_IHIIP[0];
	if (!dc->_hoops_CHPGR)
		dc->_hoops_IHHCP = &dc->_hoops_CHPGR;
}


GLOBAL_FUNCTION void HD_Free_Overlay_Segments (
	_hoops_SCCIP alter * alter *	_hoops_ASRGR) {
	_hoops_SCCIP alter			*_hoops_GSCIP, *next;

	if ((_hoops_GSCIP = *_hoops_ASRGR) == null)
		return;

	do {
		next = _hoops_GSCIP->next;
		_hoops_HPRH (_hoops_GSCIP->segment);
		FREE (_hoops_GSCIP, _hoops_SCCIP);
	} while ((_hoops_GSCIP = next) != null);

	*_hoops_ASRGR = null;
}

local void _hoops_RISSS (
	Display_Context const *		dc,
	_hoops_SCCIP const *		_hoops_GSCIP,
	Activity					_hoops_CPGPR) {

	do {
		_hoops_CRCP const *			_hoops_SRCP = _hoops_GSCIP->segment;

		if (!BIT (_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR))
			if (ANYBIT (_hoops_SRCP->_hoops_RCGC, _hoops_HAHGP))
				_hoops_SASIR (dc->_hoops_RIGC, _hoops_SRCP, _hoops_CPGPR);
	} while ((_hoops_GSCIP = _hoops_GSCIP->next) != null);
}



local void _hoops_AISSS (
	Net_Rendition alter &		nr) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;

	HD_Free_Colors (dc);

	/* _hoops_RRP _hoops_IS _hoops_CSISS _hoops_HCR _hoops_GSPIP & _hoops_HHSA _hoops_SGCSR _hoops_SPHR -- _hoops_IH _hoops_SPSIR _hoops_PGAP
	** _hoops_PIHA _hoops_GCAPH _hoops_RH _hoops_HRCSR _hoops_CCA _hoops_RH _hoops_RPPS */
	(*dc->_hoops_ACPGR->init_picture) (nr);
	HD_Unload_All_Fonts (dc);
	(*dc->_hoops_ACPGR->finish_picture) (nr, false);

	HI_Clean_Segment_Display_Lists (dc->_hoops_AAHSR, true);

	(*dc->_hoops_ACPGR->free_outer_window) (dc);

	/* (_hoops_CIPSR _hoops_CHR _hoops_ICIC) */
	HD_Free_Sprite_List (dc, &dc->_hoops_IHIIP[0]);
	HD_Free_Sprite_List (dc, &dc->_hoops_IHIIP[1]);
	HD_Free_Sprite_List (dc, &dc->_hoops_CHPGR);
	HD_Free_Sprite_List (dc, &dc->_hoops_CRHGH);
	HD_Free_Overlay_Segments ((_hoops_SCCIP alter * alter *)&dc->_hoops_GCHCP);
	HD_Free_Overlay_Segments ((_hoops_SCCIP alter * alter *)&dc->_hoops_RSCIP);

	dc->flags &= ~_hoops_SAISR;
}


local bool _hoops_PISSS (
	_hoops_CRCP const *		_hoops_SRCP,
	bool				_hoops_RAGCR,
	bool				_hoops_HISSS,
	unsigned Integer32	_hoops_GPPI) {

	do {
		Attribute const	*	_hoops_ASGPR;
		bool				_hoops_IISSS = _hoops_HISSS && !BIT (_hoops_SRCP->_hoops_PHSI, _hoops_HCGPR);

		if (!_hoops_IISSS && (_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR) != null) do {
			if (_hoops_GPPI < _hoops_SRCP->_hoops_PCIGP()) {
				if (ANYBIT (_hoops_ASGPR->_hoops_CPGPR, _hoops_CASIR|_hoops_AHSGA))
					return true;
			}

#ifndef DISABLE_STYLE_SEGMENT
			if (_hoops_ASGPR->type == HK_STYLE) {
				Style *		style = (Style *)_hoops_ASGPR;

				if (style->_hoops_IGRPR && BIT (style->_hoops_IGRPR->_hoops_CPGPR, _hoops_AHGPR) &&
					_hoops_PISSS (style->_hoops_IGRPR, false, false, _hoops_GPPI))
					return true;
			}
#endif
		} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

		if (!_hoops_RAGCR)
			break;

		_hoops_SRCP = _hoops_SRCP->owner;
		_hoops_HISSS = false;
	} while (_hoops_SRCP->type == _hoops_IRCP);

	return false;
}




local void _hoops_IGARH (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP) {
	_hoops_CRCP const *				owner = _hoops_SRCP->owner;

	_hoops_RGGA (owner->type == _hoops_PRAIR) {
		if (owner->type == _hoops_IRCP &&
			owner->_hoops_IPPGR != null) {
			_hoops_IGARH (nr, owner);
			break;
		}
		owner = owner->owner;
#if 0
		if (owner->type == _hoops_PIRIR)
			owner = owner->owner;
#endif
	}

	if (_hoops_SRCP->_hoops_IPPGR != null)
		HD_Downwind_Rendition (nr, _hoops_SRCP->_hoops_IPPGR,
								_hoops_CAHGP, // (_hoops_PHHIP == _hoops_IPPSA->_hoops_SRRPR) ? _hoops_GISIC : _hoops_PHHIP->_hoops_SGHGP,
								true);
}


local void _hoops_SASSS (
	Net_Rendition alter &		nr) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_CRCP const *				_hoops_SRCP = dc->_hoops_AAHSR;

	dc->flags |= _hoops_CPPHP;
	_hoops_IGARH (nr, _hoops_SRCP);
	dc->flags &= ~_hoops_CPPHP;

	/* _hoops_CHASA, _hoops_RPP _hoops_HAHH */
	if (!dc->options._hoops_RASSP)
		dc->options._hoops_AASSP = false;
	if (!dc->options._hoops_AASSP)
		dc->options._hoops_PASSP = false;
	if (dc->_hoops_PGCC._hoops_CHHSR == _hoops_SHHSR)
		dc->options._hoops_SRRRR = false;
	if (dc->options._hoops_HRSSP)
		dc->options.border = true;
}


local Net_Rendition _hoops_CISSS (
	Display_Context alter *		dc)
{
	Net_Rendition				nr;
	_hoops_PRSSP			_hoops_SISSS;
	Integer32					_hoops_GCSSS;
	int							_hoops_RCSSS,
								_hoops_ACSSS;
	XY							_hoops_PCSSS;
	float						_hoops_HCSSS;
	int							_hoops_ASIGS,
								_hoops_PSIGS;

	if (BIT(dc->flags, _hoops_SAISR)) {
		_hoops_RSAI (&dc->options, _hoops_PRSSP, &_hoops_SISSS);
		HI_Copy_Name (&dc->options._hoops_IAPIR, &_hoops_SISSS._hoops_IAPIR);

		_hoops_RCSSS				= dc->current._hoops_APASR;
		_hoops_GCSSS		= dc->current._hoops_AAPSR;
		_hoops_ACSSS			= dc->current._hoops_GCPRP;
		_hoops_PCSSS.x			= dc->current._hoops_HAP.x;
		_hoops_PCSSS.y			= dc->current._hoops_HAP.y;
		_hoops_ASIGS					= dc->_hoops_RHPGA.right - dc->_hoops_RHPGA.left;
		_hoops_PSIGS					= dc->_hoops_RHPGA.top - dc->_hoops_RHPGA.bottom;
	}
	else {
		/* _hoops_GHRAA _hoops_IS _hoops_SPCS _hoops_HSH _hoops_IS _hoops_CRHR _hoops_ICSSS */
		ZERO_STRUCT (&_hoops_SISSS, _hoops_PRSSP);
		_hoops_SISSS._hoops_ARPSR = _hoops_PGHRP;
		_hoops_SISSS._hoops_ACPRP	  = -1.0f;

		_hoops_RCSSS				= 0;
		_hoops_GCSSS		= 0;
		_hoops_ACSSS			= 0;
		_hoops_PCSSS.x			= 0.0f;
		_hoops_PCSSS.y			= 0.0f;
		_hoops_ASIGS					= 0;
		_hoops_PSIGS					= 0;

		dc->current._hoops_AGRS	= -1;
	}

	/* _hoops_HGCR _hoops_CIGGR _hoops_PCIAR _hoops_IIGR _hoops_RH _hoops_SCIA _hoops_HGIIP */
	nr = Net_Rendition::Create(dc);
	_hoops_SASSS (nr);

	/* _hoops_ARP _hoops_HPP _hoops_CCSSS _hoops_PPR _hoops_HPP _hoops_HHGRH */
	_hoops_HCSSS = dc->current._hoops_AGRS;

	HD_Get_Current_Info (dc);


	if (_hoops_HCSSS != dc->current._hoops_AGRS) {
		/* _hoops_RPP _hoops_HPGR _hoops_SRS _hoops_RHAC _hoops_GA'_hoops_RA _hoops_SCSS... */
		nr = Net_Rendition::Create(dc);
		_hoops_SASSS (nr);

		HD_Get_Current_Info (dc);
	}

	if (BIT (dc->flags, _hoops_GPHHP))
		nr->_hoops_RGP |= T_WINDOWS;

	dc->_hoops_SHCIP = nr;

	if ((BIT (nr->_hoops_IRR->_hoops_SRI, _hoops_RRAAP) ||
		 BIT (nr->_hoops_IRR->_hoops_RCRAP, _hoops_ICRAP)) &&
		dc->_hoops_AAHSR->type == _hoops_IRCP &&
		!BIT (dc->_hoops_AAHSR->_hoops_RCGC, _hoops_ASRRA))
		HI_Propagate_Maybes (dc->_hoops_RIGC, (_hoops_CRCP alter *)dc->_hoops_AAHSR, _hoops_ASRRA);

	/* * */
	HD_Calculate_Outer_Window (nr);
	/* * */
	dc->_hoops_RHPGA.left =	  FLOOR (dc->current.extent.left);
	dc->_hoops_RHPGA.right =  FLOOR (dc->current.extent.right);
	dc->_hoops_RHPGA.bottom = FLOOR (dc->current.extent.bottom);
	dc->_hoops_RHPGA.top	= FLOOR (dc->current.extent.top);
	/* * */

	if (BIT (nr->_hoops_RGP, T_WINDOWS)) {
		if (!BIT(dc->flags, _hoops_SAISR) ||
			dc->_hoops_GHSS.current == null &&
			(_hoops_SISSS._hoops_SRRRR	   != dc->options._hoops_SRRRR ||
			 _hoops_SISSS._hoops_RAHHP != dc->options._hoops_RAHHP ||
			 _hoops_SISSS.border				   != dc->options.border ||
			 _hoops_SISSS._hoops_ARPSR != dc->options._hoops_ARPSR ||
			 _hoops_SISSS._hoops_IRSSP		   != dc->options._hoops_IRSSP ||
			 _hoops_SISSS._hoops_CRSSP	   != dc->options._hoops_CRSSP ||
			 _hoops_SISSS._hoops_HRSSP		   != dc->options._hoops_HRSSP ||
			 _hoops_SISSS._hoops_ISPRP		   != dc->options._hoops_ISPRP ||
			 _hoops_SISSS._hoops_RCHSR	   != dc->options._hoops_RCHSR ||
			 _hoops_SISSS._hoops_CSPRP	   != dc->options._hoops_CSPRP ||
			 _hoops_RCSSS				   != dc->current._hoops_APASR ||
			 _hoops_GCSSS			   != dc->current._hoops_AAPSR ||
			 _hoops_ACSSS				   != dc->current._hoops_GCPRP ||
			 _hoops_SISSS._hoops_AGHRP			   != dc->options._hoops_AGHRP ||
			 _hoops_SISSS._hoops_IRARR				   != dc->options._hoops_IRARR ||
			 _hoops_SISSS._hoops_AIPGA	   != dc->options._hoops_AIPGA) ||
			 (!BIT(dc->_hoops_PGCC.flags, _hoops_RHPGH) &&
			  _hoops_SISSS._hoops_GCHSR		   != dc->options._hoops_GCHSR)) {

			if (BIT(dc->flags, _hoops_SAISR)) _hoops_AISSS(nr);

			dc->current._hoops_PAPGH = 0;			/* (_hoops_GHCA _hoops_SHH _hoops_PASGH) */
			dc->current._hoops_HAPGH = 0;		/* (_hoops_GHCA _hoops_SHH _hoops_PASGH) */

			dc->current._hoops_RAPGH = (*dc->_hoops_ACPGR->get_outer_window)(dc);

			/* _hoops_GGR _hoops_AGIR _hoops_SR _hoops_SARS'_hoops_RA _hoops_HGCR _hoops_PCPA _hoops_SR _hoops_SSGRR _hoops_IH */
			HD_Get_Current_Info (dc);
			if (dc->_hoops_RHPGA.left	!= FLOOR (dc->current.extent.left) ||
				dc->_hoops_RHPGA.right	!= FLOOR (dc->current.extent.right) ||
				dc->_hoops_RHPGA.bottom != FLOOR (dc->current.extent.bottom) ||
				dc->_hoops_RHPGA.top	!= FLOOR (dc->current.extent.top)) {
				/* _hoops_RGR _hoops_GPGH'_hoops_RA _hoops_CPPPR _hoops_AGAPR... */

				_hoops_CGRA alter &	_hoops_GCRCS = nr->_hoops_SAIR;

				_hoops_GCRCS->extent.left   = -1.0f;
				_hoops_GCRCS->extent.right  = 1.0f;
				_hoops_GCRCS->extent.bottom = -1.0f;
				_hoops_GCRCS->extent.top	   = 1.0f;

				HD_Calculate_Outer_Window (nr);
				dc->_hoops_RHPGA.left	= FLOOR (dc->current.extent.left);
				dc->_hoops_RHPGA.right	= FLOOR (dc->current.extent.right);
				dc->_hoops_RHPGA.bottom = FLOOR (dc->current.extent.bottom);
				dc->_hoops_RHPGA.top	= FLOOR (dc->current.extent.top);
			}

			dc->_hoops_RCGA.left = dc->_hoops_RHPGA.left;
			dc->_hoops_RCGA.bottom = dc->_hoops_RHPGA.bottom;
			dc->_hoops_RCGA.right = dc->_hoops_RHPGA.right;
			dc->_hoops_RCGA.top = dc->_hoops_RHPGA.top;

			HD_Get_Colors (dc);

			dc->flags |= _hoops_SAISR;

			/* _hoops_IHIR _hoops_AIIAP!... */
			dc->_hoops_CPGPR = _hoops_RCGSA | _hoops_RSCCA;
			dc->_hoops_HSPGH = _hoops_RCGSA;
		}
		/* _hoops_HAR _hoops_IRS _hoops_IHIR _hoops_PIAGR */

		/* _hoops_HRGR _hoops_IIH _hoops_IRS _hoops_CCAH _hoops_CRSAI? */
		else if (!_hoops_RAHSR (dc->options._hoops_IAPIR, _hoops_SISSS._hoops_IAPIR)) {
			(*dc->_hoops_ACPGR->_hoops_ASCSP)(dc);
		}
		/* _hoops_HRGR _hoops_IIH _hoops_IRS _hoops_RPPS _hoops_IHIS/_hoops_PCCS? */
		else if (dc->options._hoops_HPHRP &&
				 (dc->_hoops_RCGA.left != dc->_hoops_RHPGA.left ||
				  dc->_hoops_RCGA.right != dc->_hoops_RHPGA.right ||
				  dc->_hoops_RCGA.bottom != dc->_hoops_RHPGA.bottom ||
				  dc->_hoops_RCGA.top != dc->_hoops_RHPGA.top)) {
			(*dc->_hoops_ACPGR->_hoops_RSCSP)(dc);

			/* _hoops_ASAC _hoops_IH _hoops_SPS _hoops_GHIR */
			dc->_hoops_RCGA.left = dc->_hoops_RHPGA.left;
			dc->_hoops_RCGA.bottom = dc->_hoops_RHPGA.bottom;
			dc->_hoops_RCGA.right = dc->_hoops_RHPGA.right;
			dc->_hoops_RCGA.top = dc->_hoops_RHPGA.top;

			/* _hoops_GGR _hoops_AGIR _hoops_SR _hoops_SARS'_hoops_RA _hoops_HGCR _hoops_PCPA _hoops_SR _hoops_SSGRR _hoops_IH */
			HD_Get_Current_Info (dc);
			if (dc->_hoops_RHPGA.left	!= FLOOR (dc->current.extent.left) ||
				dc->_hoops_RHPGA.right	!= FLOOR (dc->current.extent.right) ||
				dc->_hoops_RHPGA.bottom != FLOOR (dc->current.extent.bottom) ||
				dc->_hoops_RHPGA.top	!= FLOOR (dc->current.extent.top)) {
				/* _hoops_RGR _hoops_GPGH'_hoops_RA _hoops_CPPPR _hoops_AGAPR... */

				_hoops_CGRA alter &	_hoops_GCRCS = nr->_hoops_SAIR;

				_hoops_GCRCS->extent.left   = -1.0f;
				_hoops_GCRCS->extent.right  = 1.0f;
				_hoops_GCRCS->extent.bottom = -1.0f;
				_hoops_GCRCS->extent.top	   = 1.0f;

				HD_Calculate_Outer_Window (nr);
				dc->_hoops_RHPGA.left	= FLOOR (dc->current.extent.left);
				dc->_hoops_RHPGA.right	= FLOOR (dc->current.extent.right);
				dc->_hoops_RHPGA.bottom = FLOOR (dc->current.extent.bottom);
				dc->_hoops_RHPGA.top	= FLOOR (dc->current.extent.top);
			}

			/* _hoops_AIIAP _hoops_CPS! */
			dc->_hoops_CPGPR |= _hoops_RCGSA;
			dc->_hoops_HSPGH = _hoops_RCGSA;
		}
		/* _hoops_RPP _hoops_RH _hoops_GAPGH _hoops_HRGR _hoops_HHACR _hoops_IGIR, _hoops_GHGPR-_hoops_ISPR _hoops_SGS _hoops_CPS'_hoops_GRI
		 * _hoops_CPIC _hoops_IS _hoops_HGCR _hoops_SIGSA (_hoops_SCSSS _hoops_PPR _hoops_GSSSS _hoops_GA'_hoops_RA
		 * _hoops_SSCC _hoops_HHSA _hoops_IGSIP.)
		 */
		else if (_hoops_ASIGS != dc->_hoops_RHPGA.right - dc->_hoops_RHPGA.left ||
				 _hoops_PSIGS != dc->_hoops_RHPGA.top - dc->_hoops_RHPGA.bottom) {
			/* _hoops_AIIAP _hoops_CPS! */
			dc->_hoops_CPGPR |= _hoops_RCGSA;
			dc->_hoops_HSPGH = _hoops_RCGSA;
		}
		/* _hoops_HCAAI _hoops_HCSP _hoops_AGRP? */
		else if (_hoops_PCSSS.x != dc->current._hoops_HAP.x ||
				 _hoops_PCSSS.y != dc->current._hoops_HAP.y) {
			/* _hoops_AIIAP _hoops_CPS! */
			dc->_hoops_CPGPR |= _hoops_RCGSA;
			dc->_hoops_HSPGH = _hoops_RCGSA;
		}
		/* _hoops_AICP _hoops_PICP _hoops_IIGR _hoops_RHPP-_hoops_HCSP-_hoops_RSSSS _hoops_CSSHH _hoops_PCPIP ... */
		else if (_hoops_SISSS._hoops_SIAH != dc->options._hoops_SIAH) {
			/* _hoops_AIIAP _hoops_CPS! */
			dc->_hoops_CPGPR |= _hoops_RCGSA;
			dc->_hoops_HSPGH = _hoops_RCGSA;
		}
		else if (_hoops_SISSS._hoops_RCPRP != dc->options._hoops_RCPRP) {
			/* _hoops_AIIAP _hoops_CPAP */
			dc->_hoops_CPGPR |= _hoops_GGARA;
			dc->_hoops_HSPGH |= _hoops_GGARA;
		}

		/* _hoops_AGRP _hoops_GGR _hoops_GAASP _hoops_SIISR? */
		if (_hoops_SISSS._hoops_SRSSP != dc->options._hoops_SRSSP) {
			/* _hoops_IRHH _hoops_PCCP _hoops_IRPR _hoops_GAASP _hoops_GASR */
			HD_Get_Gamma_Table (dc, BIT(dc->_hoops_PGCC.flags, _hoops_GGISR) &&
									dc->options._hoops_SRSSP);

			HD_Free_Colors (dc);
			HD_Get_Colors (dc);

			/* _hoops_AIIAP _hoops_CPS! */
			dc->_hoops_CPGPR |= _hoops_RCGSA;
			dc->_hoops_HSPGH = _hoops_RCGSA;
		}

		if (dc->options._hoops_ACPRP != _hoops_SISSS._hoops_ACPRP) {
			if (dc->options._hoops_ACPRP == 0.0f)
				dc->_hoops_GRPGH = (int)dc->_hoops_PGCC._hoops_PCHSR;
			else {
				float	_hoops_ASSSS;

				_hoops_ASSSS = 1.0f / dc->options._hoops_ACPRP + 0.5f;
				dc->_hoops_GRPGH = (int)_hoops_AHIA (_hoops_ASSSS,
														(float)dc->_hoops_PGCC._hoops_PCHSR);
				if (dc->_hoops_GRPGH < 2)
					dc->_hoops_GRPGH = 2;
			}

			/* _hoops_AIIAP _hoops_CPS! */
			dc->_hoops_CPGPR |= _hoops_RCGSA;
			dc->_hoops_HSPGH |= _hoops_RCGSA;
		}

		if (nr->transform_rendition->_hoops_RHPHP != _hoops_AHPHP &&
			!BIT(dc->_hoops_PGCC.flags, _hoops_IPPHP)) {
			_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

			_hoops_GGCC->_hoops_RHPHP = _hoops_AHPHP;
			((_hoops_HHRA *)_hoops_GGCC->_hoops_SPH)->_hoops_RRHH &= ~_hoops_GIHCR;
			HD_Downwind_Camera (nr, (Attribute *)_hoops_GGCC->_hoops_SPH);
		}
	}

	dc->_hoops_PSPGH = nr->_hoops_RCSHR;

	_hoops_RGAIR (_hoops_SISSS._hoops_IAPIR);

	return nr;
}


local bool _hoops_PSSSS (_hoops_AIGPR *	_hoops_RIGC) {
	_hoops_HISHA *		event;

	if ((event = _hoops_RIGC->_hoops_PAARH) != null) {
		do if (event->type != _hoops_PHIIR)
			return true;
		while ((event = event->next) != null);
	}

	return false;
}

local bool _hoops_HSSSS (
	Display_Context alter *		dc) {
	UNREFERENCED (dc);

	_hoops_IPR (HEC_INTERNAL_ERROR, HES_RECURSIVE_UPDATE,
					   "Update requested with update in progress!");
	return true; /* (_hoops_IIGGR _hoops_SGS _hoops_SR _hoops_ISSSS _hoops_PCPA _hoops_SCH _hoops_AGSR _hoops_IS "_hoops_PAAP") */
}


#define _hoops_CSSSS(name, format, _hoops_SSSSS) _hoops_GHIA ( \
	_hoops_ASAPR = HI_Sprintf1 (buf, _hoops_PSAPR, (format), (void*)&_hoops_SSSSS); \
	colors[_hoops_GGGGGR] = 0; \
	*_hoops_ASAPR = '\0'; \
	_hoops_IHAGI(_hoops_GCRCC[_hoops_GGGGGR]); \
	_hoops_IHAGI(_hoops_RGGGGR[_hoops_GGGGGR]); \
	HI_Convert_Char_To_KName (name, &_hoops_GCRCC[_hoops_GGGGGR], _hoops_SSAIP); \
	HI_Convert_Char_To_KName (buf, &_hoops_RGGGGR[_hoops_GGGGGR], _hoops_SSAIP); \
	_hoops_GGGGGR++; \
)

#define _hoops_AGGGGR(name, format, _hoops_SSSSS) _hoops_GHIA ( \
	_hoops_CSSSS (name, format, _hoops_RCCA(_hoops_SSSSS)); \
)


#define _hoops_PGGGGR(name, format, _hoops_SSSSS) _hoops_GHIA ( \
	if (dc->_hoops_IGGI->_hoops_SSSSS != 0 || dc->_hoops_CAHGH->_hoops_SSSSS != 0) { \
		if (dc->_hoops_IGGI->_hoops_SSSSS != 0) { \
			_hoops_ASAPR = HI_Sprintf1 (buf, _hoops_PSAPR, (format), (void*)&dc->_hoops_IGGI->_hoops_SSSSS); \
			colors[_hoops_GGGGGR] = 0; \
			dc->_hoops_CAHGH->_hoops_SSSSS = dc->_hoops_IGGI->_hoops_SSSSS; \
		} \
		else { \
			_hoops_ASAPR = HI_Sprintf1 (buf, _hoops_PSAPR, (format), (void*)&dc->_hoops_CAHGH->_hoops_SSSSS); \
			colors[_hoops_GGGGGR] = 1; \
		} \
		*_hoops_ASAPR = '\0'; \
		_hoops_IHAGI(_hoops_GCRCC[_hoops_GGGGGR]); \
		_hoops_IHAGI(_hoops_RGGGGR[_hoops_GGGGGR]); \
		HI_Convert_Char_To_KName (name, &_hoops_GCRCC[_hoops_GGGGGR], _hoops_SSAIP); \
		HI_Convert_Char_To_KName (buf, &_hoops_RGGGGR[_hoops_GGGGGR], _hoops_SSAIP); \
		_hoops_GGGGGR++; \
	} \
)


#define _hoops_HGGGGR 64		// _hoops_IPIH _hoops_AHCA 50 _hoops_HRARH _hoops_CAPP

local void _hoops_IGGGGR (
	Net_Rendition const &		inr) {
	Display_Context const *		dc = inr->_hoops_SRA;
	Net_Rendition				nr[3];
	char						buf[4096], *_hoops_ASAPR, *_hoops_PSAPR;
	KName						_hoops_GCRCC[_hoops_HGGGGR];
	KName						_hoops_RGGGGR[_hoops_HGGGGR];
	float						_hoops_CGGGGR[_hoops_HGGGGR];
	int							colors[_hoops_HGGGGR];
	_hoops_IGPIR					_hoops_RCPPI;
	Point						p;
	int							_hoops_GGGGGR = 0;
	int							i;
	RGB							rgb;
	int							count;

	// _hoops_HPPR _hoops_IS _hoops_CAHA _hoops_PCPA _hoops_SGGGGR _hoops_GRGGGR _hoops_CHR _hoops_HII _hoops_RGR _hoops_PAAP
	dc->_hoops_IGGI->_hoops_ICRGH = HOOPS_WORLD->_hoops_ICRGH - dc->_hoops_IGGI->_hoops_ICRGH;
	dc->_hoops_IGGI->_hoops_CCRGH = HOOPS_WORLD->_hoops_CCRGH - dc->_hoops_IGGI->_hoops_CCRGH;
	dc->_hoops_IGGI->_hoops_SCRGH = HOOPS_WORLD->_hoops_SCRGH - dc->_hoops_IGGI->_hoops_SCRGH;
	dc->_hoops_IGGI->_hoops_GSRGH = HOOPS_WORLD->_hoops_GSRGH - dc->_hoops_IGGI->_hoops_GSRGH;
	dc->_hoops_IGGI->_hoops_PSRGH = HOOPS_WORLD->_hoops_PSRGH - dc->_hoops_IGGI->_hoops_PSRGH;
	dc->_hoops_IGGI->_hoops_HSRGH = HOOPS_WORLD->_hoops_HSRGH - dc->_hoops_IGGI->_hoops_HSRGH;

	dc->_hoops_IGGI->_hoops_PCRGH = HOOPS_WORLD->_hoops_PCRGH - dc->_hoops_IGGI->_hoops_PCRGH;
	dc->_hoops_IGGI->_hoops_HCRGH = HOOPS_WORLD->_hoops_HCRGH - dc->_hoops_IGGI->_hoops_HCRGH;


	nr[0] = inr.Copy();

	if (ANYBIT(nr[0]->_hoops_IRR->_hoops_CHP, _hoops_SHP|_hoops_CRAAP))
		nr[0]->_hoops_IRR.Modify()->_hoops_CHP &= ~(_hoops_SHP|_hoops_CRAAP);
	if (BIT(nr[0]->_hoops_IRR->_hoops_PPH, _hoops_CRI))
		nr[0]->_hoops_IRR.Modify()->_hoops_PPH &= ~_hoops_CRI;

	_hoops_HHCR alter &	_hoops_IHCR = nr[0]->transform_rendition.Modify();
	_hoops_IHCR->heuristics &= ~_hoops_IRI;
	_hoops_IHCR->flags |= _hoops_ISH;
	_hoops_IHCR->flags &= ~_hoops_PASP;
	_hoops_IHCR->_hoops_CHIH = 0.0f;
	_hoops_IHCR->_hoops_AGAA.bottom = nr[0]->_hoops_SAIR->_hoops_PHRA.bottom;
	_hoops_IHCR->_hoops_AGAA.left = nr[0]->_hoops_SAIR->_hoops_PHRA.left;
	_hoops_IHCR->_hoops_AGAA.top = nr[0]->_hoops_SAIR->_hoops_PHRA.top;
	_hoops_IHCR->_hoops_AGAA.right = nr[0]->_hoops_SAIR->_hoops_PHRA.right;

	_hoops_IGCSR alter &		_hoops_HRCIR = nr[0]->_hoops_SISI.Modify();
	_hoops_HRCIR->transform = FT_NONE;
	_hoops_HRCIR->_hoops_GHGRP = GSU_PIXELS;

	if (BIT (HOOPS_WORLD->_hoops_IRARR, _hoops_ARHGI))
		_hoops_HRCIR->_hoops_PHP = 12;
	else
		_hoops_HRCIR->_hoops_PHP = 6;

	_hoops_HRCIR->font = 0;
	_hoops_HRCIR->width_scale = 1.0f;
	_hoops_HRCIR->_hoops_ACPAP = 0.0f;
	_hoops_HRCIR->rotation = 0.0f;

	rgb.blue = 1.0f;
	rgb.green = 1.0f;
	rgb.red = 1.0f;

	_hoops_SCHIP(nr[0], &rgb, true);

	_hoops_RCPPI.specified.length = 0;
	_hoops_RCPPI.specified.text = 0;
	_hoops_RCPPI.next = null;
	_hoops_RCPPI._hoops_SSSGP = GFN_STROKED;

	_hoops_CAAI (HOOPS_WORLD->_hoops_HPHGI);
	do {
		HD_Choose_Font (nr[0], &_hoops_RCPPI, _hoops_SSAIP, true);

		/* _hoops_GHCA _hoops_HAR _hoops_SHH _hoops_SHSS _hoops_IS _hoops_HSRS _hoops_GII _hoops_HRCSR _hoops_GGR _hoops_RGR _hoops_AGIR, _hoops_HIS _hoops_RCRP _hoops_GH */
		if (_hoops_HRCIR->font == null) {
			_hoops_CAAI (HOOPS_WORLD->_hoops_HPHGI);
			return;
		}
	} _hoops_RGGA (HD_Load_Font (dc, _hoops_HRCIR->font));

	nr[2] = nr[1] = nr[0];

	rgb.red = 0.0f;
	rgb.green = 0.0f;
	rgb.blue = 0.0f;

	_hoops_RSHIP(nr[0], &rgb, true);
	_hoops_ICHIP(nr[0], &rgb, true);

	rgb.red = 0.6f;
	rgb.green = 0.6f;
	rgb.blue = 0.6f;

	_hoops_RSHIP(nr[1], &rgb, true);
	_hoops_ICHIP(nr[1], &rgb, true);

	rgb.red = 0.8f;
	rgb.green = 0.0f;
	rgb.blue = 0.0f;

	_hoops_RSHIP(nr[2], &rgb, true);
	_hoops_ICHIP(nr[2], &rgb, true);


	_hoops_PSAPR = buf+4096;

	if (dc->options._hoops_SASSP) {
		_hoops_AGGGGR ("update time:", "%.3F", _hoops_IPRGH);
		_hoops_AGGGGR ("finish time:", "%.3F", _hoops_CPRGH);

		_hoops_PGGGGR ("static time:", "%.3F", _hoops_SPRGH);
		_hoops_PGGGGR ("shadow time:", "%.3F", _hoops_GHRGH);
		_hoops_PGGGGR ("assemble time:", "%.3F", _hoops_RHRGH);
		_hoops_PGGGGR ("region time:", "%.3F", _hoops_PSPGR);
	}

	if (dc->options._hoops_CASSP) {
		_hoops_PGGGGR ("segments:", "%D", _hoops_SISAA);
		_hoops_PGGGGR ("extent culled:", "%D", _hoops_CHRGH);
		_hoops_PGGGGR ("frustum culled:", "%D", _hoops_SHRGH);
		_hoops_PGGGGR ("ph extent culled:", "%D", _hoops_CCHS);
		_hoops_PGGGGR ("ph frustum culled:", "%D", _hoops_PIRGH);
		_hoops_PGGGGR ("ts extent culled:", "%D", _hoops_CSIAR);
		_hoops_PGGGGR ("ts frustum culled:", "%D", _hoops_SSIAR);
		_hoops_PGGGGR ("text extent culled:", "%D", _hoops_IIRGH);
		_hoops_PGGGGR ("text frustum culled:", "%D", _hoops_CIRGH);
		_hoops_PGGGGR ("refs extent culled:", "%D", _hoops_SIRGH);
		_hoops_PGGGGR ("refs frustum culled:", "%D", _hoops_GCRGH);
		_hoops_PGGGGR ("vector culled:", "%D", _hoops_GIRGH);
		_hoops_PGGGGR ("occlusion culled:", "%D", _hoops_RIRGH);
		_hoops_PGGGGR ("dc dots:", "%D", _hoops_CCCA);
		_hoops_PGGGGR ("3d dots:", "%D", _hoops_SCCA);
		_hoops_PGGGGR ("3d vertices:", "%D", _hoops_ICGS);
		_hoops_PGGGGR ("dl 3d vertices:", "%D", _hoops_RPAS);
		_hoops_PGGGGR ("dc lines:", "%D", _hoops_HCCA);
		_hoops_PGGGGR ("3d lines:", "%D", _hoops_ICCA);
		_hoops_PGGGGR ("dl 3d lines:", "%D", _hoops_AHRGH);
		_hoops_PGGGGR ("dc polygons:", "%D", _hoops_PHRGH);
		_hoops_PGGGGR ("3d polygons:", "%D", _hoops_GRCS);
		_hoops_PGGGGR ("dc triangles:", "%D", _hoops_ACCA);
		_hoops_PGGGGR ("3d triangles:", "%D", _hoops_PCCA);
		_hoops_PGGGGR ("dl 3d triangles:", "%D", _hoops_AGCAR);
		_hoops_PGGGGR ("3d text:", "%D", _hoops_HIRGH);
		_hoops_PGGGGR ("refs:", "%D", _hoops_CPGIP);
		_hoops_PGGGGR ("rasters:", "%D", rasters);
		_hoops_PGGGGR ("analytics:", "%D", _hoops_HHRGH);
		_hoops_PGGGGR ("occlusions:", "%D", _hoops_IHRGH);
		_hoops_PGGGGR ("polyhedrons:", "%D", _hoops_AIRGH);
		_hoops_PGGGGR ("tristrips:", "%D", tristrips);
		_hoops_PGGGGR ("dl strips:", "%D", _hoops_GGCAR);
		_hoops_PGGGGR ("ndl strips:", "%D", _hoops_GRHAR);
		_hoops_PGGGGR ("dl deletes:", "%D", _hoops_SGAGR);
		_hoops_PGGGGR ("punted grefs:", "%D", _hoops_HIGC);

		_hoops_PGGGGR ("texture lookup:", "%D", _hoops_RCRGH);
		_hoops_PGGGGR ("texture process:", "%D", _hoops_ACRGH);
		_hoops_PGGGGR ("texture activate:", "%D", _hoops_PCRGH);
		_hoops_PGGGGR ("texture load:", "%D", _hoops_RPRH);
		_hoops_PGGGGR ("texture bind:", "%D", _hoops_GSAC);
		_hoops_PGGGGR ("texture failed:", "%D", _hoops_HCRGH);

		_hoops_PGGGGR ("seg forced defer:", "%D", _hoops_PRHPP);

		_hoops_PGGGGR ("dls extent defer:", "%D", _hoops_GRHPP);
		_hoops_PGGGGR ("ref extent defer:", "%D", _hoops_RRHPP);
		_hoops_PGGGGR ("seg extent defer:", "%D", _hoops_SGHPP);
		_hoops_PGGGGR ("geo extent defer:", "%D", _hoops_ARHPP);

		_hoops_PGGGGR ("deferred geometry:", "%D", _hoops_SASIP);
		_hoops_PGGGGR ("deferred segments:", "%D", _hoops_HASIP);
		_hoops_PGGGGR ("deferred seg_dls:", "%D", _hoops_IASIP);
		_hoops_PGGGGR ("deferred refs:", "%D", _hoops_CASIP);
		_hoops_PGGGGR ("hw flush:", "%D", _hoops_IGCAR);
		_hoops_PGGGGR ("seg bounds:", "%D", _hoops_PSRGH);
		_hoops_PGGGGR ("geo bounds:", "%D", _hoops_HSRGH);


		if (HOOPS_WORLD->display_list_vram_usage > 0 && (HOOPS_WORLD->_hoops_PHARR < _hoops_CSSPP)) {
			long	_hoops_RRGGGR = 1 + (long)(100.0f * HOOPS_WORLD->display_list_vram_usage / HOOPS_WORLD->_hoops_PHARR);
			_hoops_CSSSS ("vram:", "%D %%", _hoops_RRGGGR);
		}
	}

	if (dc->options._hoops_GPSSP) {
		long	allocated;
		long	used;

		HI_Show_Memory_Usage (&allocated, &used);
		if (allocated > (1024*1024)) {
			allocated /= (1024*1024);
			_hoops_CSSSS ("memory total:", "%dM", allocated);
		}
		else {
			allocated /= 1024;
			_hoops_CSSSS ("memory total:", "%dK", allocated);
		}
		if (used > (1024*1024)) {
			used /= (1024*1024);
			_hoops_CSSSS ("memory used:", "%dM", used);
		}
		else {
			used /= 1024;
			_hoops_CSSSS ("memory used:", "%dK", used);
		}

		_hoops_PGGGGR ("memory oversized:", "%D", _hoops_ICRGH);

		_hoops_PGGGGR ("raw free:", "%D", _hoops_CCRGH);

		_hoops_PGGGGR ("memory acquired:", "%D", _hoops_SCRGH);

		_hoops_PGGGGR ("memory allocate:", "%D", _hoops_GSRGH);


		long _hoops_SHPSA = HOOPS_WORLD->_hoops_SHPSA-_hoops_RCCA(_hoops_SHPSA);
		long _hoops_CIPSA = HOOPS_WORLD->_hoops_CIPSA-_hoops_RCCA(_hoops_CIPSA);
		long _hoops_ISRGH = HOOPS_WORLD->_hoops_ISRGH-_hoops_RCCA(_hoops_ISRGH);

		if (_hoops_SHPSA > 0)
			_hoops_CSSSS ("proxies:", "%D", _hoops_SHPSA);

		if (_hoops_CIPSA > 0)
			_hoops_CSSSS ("populated:", "%D", _hoops_CIPSA);

		if (_hoops_ISRGH > 0)
			_hoops_CSSSS ("depopulated:", "%D", _hoops_ISRGH);

		if (HOOPS_WORLD->_hoops_HCPGI != 1.0f)
			_hoops_CSSSS ("populate bias:", "%f", HOOPS_WORLD->_hoops_HCPGI);
	}

	if (dc->options._hoops_CASSP) {
		if (dc->_hoops_HPAGH) {
			_hoops_CSSSS ("stop segment: ", "0x%X", dc->_hoops_HPAGH);
			//_hoops_ARGGGR ("_hoops_PRGGGR: ", "%_hoops_GHGP", _hoops_CSPH->_hoops_PRGGGR);
		}

		if (dc->_hoops_CGAP > 0) {
			_hoops_CSSSS ("update slice:", "%d", dc->_hoops_CGAP);
			if (_hoops_RCCA(_hoops_CSRGH) > 0)
				_hoops_CSSSS ("total tri_3d:", "%D", _hoops_RCCA(_hoops_CSRGH));
			if (_hoops_RCCA(_hoops_SSRGH) > 0)
				_hoops_CSSSS ("total dl_t3d:", "%D", _hoops_RCCA(_hoops_SSRGH));
		}
	}


	if (_hoops_GGGGGR > 0) {
		float			height, width;

		height = _hoops_GGGGGR * (_hoops_HRCIR->_hoops_PHP * 1.5f) + 2;
		if (height > dc->_hoops_IGGI->_hoops_GGAGH)
			((Display_Context alter*)dc)->_hoops_IGGI->_hoops_GGAGH = height;

		for (i=0; i<_hoops_GGGGGR; i++) {
			HD_Measure_Characters (nr[0], _hoops_GCRCC[i].length, _hoops_GCRCC[i]._hoops_IPPPP, _hoops_SSAIP, &width);
			HD_Measure_Characters (nr[0], _hoops_RGGGGR[i].length, _hoops_RGGGGR[i]._hoops_IPPPP, _hoops_SSAIP, &_hoops_CGGGGR[i]);

			width += _hoops_CGGGGR[i];
			width *= 1.2f;

			if (width > dc->_hoops_IGGI->_hoops_RGAGH)
				((Display_Context alter*)dc)->_hoops_IGGI->_hoops_RGAGH = width;
		}
	}


	count = 0;

	while (dc->_hoops_IPCI->prev != null) {
		_hoops_IGRS (dc);
		++count;
	}


	Int_Rectangle const &	_hoops_GPHH = _hoops_IHCR->_hoops_AGAA;

	if (dc->_hoops_IGGI->_hoops_RGAGH > 0.0f && dc->_hoops_IGGI->_hoops_GGAGH > 0.0f) {
		DC_Point		points[4];

		points[0].x = _hoops_GPHH.left;
		points[0].y = _hoops_GPHH.top - (float)dc->_hoops_IGGI->_hoops_GGAGH;
		points[0].z = 0.0f;

		points[1].x = _hoops_GPHH.left;
		points[1].y = _hoops_GPHH.top;
		points[1].z = 0.0f;

		points[2].x = _hoops_GPHH.left + (float)dc->_hoops_IGGI->_hoops_RGAGH;
		points[2].y = _hoops_GPHH.top - (float)dc->_hoops_IGGI->_hoops_GGAGH;
		points[2].z = 0.0f;

		points[3].x = _hoops_GPHH.left + (float)dc->_hoops_IGGI->_hoops_RGAGH;
		points[3].y = _hoops_GPHH.top;
		points[3].z = 0.0f;

		_hoops_GSRGA(nr[0], 4, points);
	}

	p.x = _hoops_GPHH.left + 5.0f;
	p.y = _hoops_GPHH.top - (_hoops_HRCIR->_hoops_PHP * 1.25);
	p.z = 0.0f;

	for (i=0; i<_hoops_GGGGGR; i++) {
		HD_Standard_Draw_Plain_Text(nr[colors[i]], 0, &p, _hoops_GCRCC[i].length, _hoops_GCRCC[i]._hoops_IPPPP, 0);
		_hoops_PRPIR(_hoops_GCRCC[i]);

		Point		v = p;
		v.x = dc->_hoops_IGGI->_hoops_RGAGH - _hoops_CGGGGR[i] - 2;
		HD_Standard_Draw_Plain_Text(nr[colors[i]], 0, &v, _hoops_RGGGGR[i].length, _hoops_RGGGGR[i]._hoops_IPPPP, 0);
		_hoops_PRPIR(_hoops_RGGGGR[i]);

		p.y -= (_hoops_HRCIR->_hoops_PHP * 1.5);
	}

	while (count-- > 0)
		_hoops_SGRS (dc);

	_hoops_APAI (HOOPS_WORLD->_hoops_HPHGI);
}

GLOBAL_FUNCTION void HD_Clean_DC_Breadcrumbs (
	Display_Context alter *		dc) {

	bool _hoops_HRGGGR = BIT(dc->flags, _hoops_IRAGH);

	//_hoops_GII _hoops_RCAPR _hoops_HCGI _hoops_IRGGGR _hoops_HCPH _hoops_CGH _hoops_CRGGGR _hoops_GPP _hoops_RH _hoops_PPAP _hoops_IIGR _hoops_SRGGGR
	//_hoops_HRII _hoops_HSAR _hoops_HPGGR _hoops_PCAAA _hoops_GAR _hoops_APIP
	dc->flags |= _hoops_IRAGH;

	// _hoops_CASI _hoops_GGSR _hoops_HCR _hoops_RH _hoops_CIPH _hoops_SR _hoops_IHGC _hoops_GAPA _hoops_GCAS _hoops_AGRRR _hoops_HGISR
	HD_Free_Sprite_List (dc, &dc->_hoops_IHIIP[0]);
	HD_Free_Sprite_List (dc, &dc->_hoops_IHIIP[1]);
	HD_Free_Sprite_List (dc, &dc->_hoops_CHPGR);


	if (dc->_hoops_GCHCP != null)
		HD_Free_Overlay_Segments ((_hoops_SCCIP alter * alter *)&dc->_hoops_GCHCP);
	if (dc->_hoops_RSCIP != null)
		HD_Free_Overlay_Segments((_hoops_SCCIP alter * alter *)&dc->_hoops_RSCIP);

	while (dc->_hoops_PPSIP != null) {
		_hoops_PGISP *		_hoops_HIGGC = dc->_hoops_PPSIP;

		dc->_hoops_PPSIP = _hoops_HIGGC->next;

		_hoops_HIGGC->nr.release();
		FREE (_hoops_HIGGC, _hoops_PGISP);
	}

	for (int i=0; i<_hoops_CHSSP; i++) {
		while (dc->_hoops_HRHPP[i].list != null) {
			_hoops_HSPPP alter *	_hoops_ISPPP = (_hoops_HSPPP alter *)dc->_hoops_HRHPP[i].list;

			dc->_hoops_HRHPP[i].list = _hoops_ISPPP->next;
			_hoops_ISPPP->_hoops_APHGA.release();
			if (_hoops_ISPPP->_hoops_CPCR != null) {
				_hoops_ISPPP->_hoops_CPCR->_hoops_APHGA.release();
				FREE(_hoops_ISPPP->_hoops_CPCR, _hoops_HSPPP);
			}
			FREE (_hoops_ISPPP, _hoops_HSPPP);
		}
		dc->_hoops_HRHPP[i]._hoops_ASRGR = &dc->_hoops_HRHPP[i].list;
	}

	if (dc->_hoops_AGHPP != null) {
		_hoops_RGHPP alter *	_hoops_SGCCA = null;
		int							_hoops_IGIC;

		while (dc->_hoops_AGHPP->Pop(&_hoops_SGCCA, &_hoops_IGIC)) {
			dc->_hoops_HGHPP->RemoveItem(_hoops_IGIC);

			_hoops_HSPPP alter * _hoops_ISPPP = _hoops_SGCCA->list;

			while (_hoops_ISPPP) {
				_hoops_HSPPP alter * next = _hoops_ISPPP->next;
				_hoops_ISPPP->_hoops_APHGA.release();
				FREE (_hoops_ISPPP, _hoops_HSPPP);
				_hoops_ISPPP = next;
			}

			FREE (_hoops_SGCCA, _hoops_RGHPP);
		}

		ASSERT(dc->_hoops_AGHPP->Count() == 0);
		ASSERT(dc->_hoops_HGHPP->Count() == 0);
	}

	while (dc->_hoops_GPSIP.list) {
		_hoops_HSPPP alter *	_hoops_PASIP = (_hoops_HSPPP alter *)dc->_hoops_GPSIP.list;

		dc->_hoops_GPSIP.list = _hoops_PASIP->next;
		_hoops_PASIP->_hoops_APHGA.release();
		FREE (_hoops_PASIP, _hoops_HSPPP);
	}
	dc->_hoops_GPSIP._hoops_ASRGR = (_hoops_HSPPP alter * alter *)&dc->_hoops_GPSIP.list;

	for (int i=0; i<_hoops_GPPIP; i++) {
		if (dc->_hoops_RPSS[i] != null) {
			HD_Free_Deferred_3D_Geometry (dc->_hoops_RPSS[i]);
			dc->_hoops_RPSS[i] = null;
		}
		if (dc->_hoops_GPSS[i] != null) {
			HD_Free_Deferred_3D_Geometry (dc->_hoops_GPSS[i]);
			dc->_hoops_GPSS[i] = null;
		}

		if (dc->_hoops_HASS[i]) {
			HD_Free_Hidden_List(dc, (_hoops_CASS alter *)dc->_hoops_HASS[i]);
			dc->_hoops_HASS[i] = null;
			dc->_hoops_SASS[i] = 0;
		}

		if (dc->_hoops_SRSIP[i] != null) {
			if (dc->_hoops_SRSIP[i]->_hoops_SIGSH != null)
				HD_Free_Hidden_List (dc, dc->_hoops_SRSIP[i]->_hoops_SIGSH);
			HD_Free_Hidden_Item_Cache (dc);
			FREE (dc->_hoops_SRSIP[i], _hoops_CHAGH);
			dc->_hoops_SRSIP[i] = null;
		}
	}

	if (dc->_hoops_GASIP != null) {
		FREE_ARRAY (dc->_hoops_GASIP->pts, dc->_hoops_GASIP->allocated, DC_Point);
		FREE_ARRAY (dc->_hoops_GASIP->colors, dc->_hoops_GASIP->allocated, RGBAS32);
		FREE (dc->_hoops_GASIP, DC_Polydot_Batch);
		dc->_hoops_GASIP = null;
	}


	dc->_hoops_CPHGH();
	while (dc->_hoops_AHSI != null)
		dc->Pop_Tree();


	while (dc->_hoops_SPA != dc->_hoops_ISAGR) {
		_hoops_AAGSP *	_hoops_GACSS = dc->_hoops_SPA;
		dc->_hoops_SPA = _hoops_GACSS->next;
#ifdef HOOPS_DEBUG_BUILD
		// _hoops_RPP _hoops_AGCR _hoops_CHR _hoops_RHHR _hoops_AICRR _hoops_SARS'_hoops_RA _hoops_ASAC _hoops_PPR _hoops_PHIH _hoops_CIAH
		ASSERT(_hoops_GACSS->_hoops_GRRGH == _hoops_GACSS->modelling_matrix);
		ASSERT(_hoops_GACSS->_hoops_RRRGH == _hoops_GACSS->color);
#endif
		delete _hoops_GACSS;
	}

#ifdef HOOPS_DEBUG_BUILD
	// _hoops_RPP _hoops_AGCR _hoops_CHR _hoops_RHHR _hoops_AICRR _hoops_SARS'_hoops_RA _hoops_ASAC _hoops_PPR _hoops_PHIH _hoops_CIAH
	ASSERT(dc->_hoops_ISAGR->modelling_matrix == null);
	ASSERT(dc->_hoops_ISAGR->color == null);
#endif

	if (dc->_hoops_CGHAR != null) {
		FREE_ARRAY_ALIGNED (dc->_hoops_CGHAR, dc->_hoops_ICACP, int, 16);
		dc->_hoops_CGHAR = null;
		dc->_hoops_ICACP = 0;
	}
	if (dc->_hoops_ACICP) {
		FREE_ARRAY(dc->_hoops_ACICP, dc->_hoops_RCICP, _hoops_CSSHA);
		dc->_hoops_ACICP = null;
		dc->_hoops_RCICP = 0;
	}

	if (!_hoops_HRGGGR)
		dc->flags &= ~_hoops_IRAGH;
}



GLOBAL_FUNCTION bool HD_Minimum_Update (
	Display_Context alter *		dc) {
	_hoops_CRCP const *				_hoops_GAGGGR = dc->_hoops_AAHSR;
	Net_Rendition				nr;

	if (BIT(dc->flags, _hoops_GIRIP))
		return _hoops_HSSSS (dc);

	dc->_hoops_CPGPR = _hoops_GAGGGR->_hoops_CPGPR;

	if (dc->_hoops_PGCC.driver_type == null) {
		HD_Get_Physical_Info (dc);

		/* _hoops_HCHRC _hoops_HII _hoops_RAGGGR _hoops_IH _hoops_AAGGGR... */
		dc->current._hoops_HAP.x = dc->_hoops_PGCC._hoops_PRPSR.x / dc->_hoops_PGCC.size.x;
		dc->current._hoops_HAP.y = dc->_hoops_PGCC._hoops_PRPSR.y / dc->_hoops_PGCC.size.y;
		dc->current._hoops_AGRS = dc->current._hoops_HAP.x / dc->current._hoops_HAP.y;
	}

	/* _hoops_SR'_hoops_ASAR _hoops_GPP _hoops_ISCP _hoops_PPRRR */
	dc->flags |= _hoops_GIRIP;
	dc->flags &= ~_hoops_IRAGH;

	dc->_hoops_RSAGH = false;
	dc->_hoops_ICAGH = false;

	/* _hoops_PAGGGR _hoops_CAIR */
	/* (_hoops_IRHH _hoops_AAP _hoops_HRPAI _hoops_CCCI _hoops_IH _hoops_IHPI _hoops_PAAP) */

	HD_Upwind_Driver_Options (dc);
	HD_Get_Current_Info (dc);

	(*dc->_hoops_ACPGR->init_update)(dc);

	if ((nr = dc->_hoops_SHCIP) == null)
		nr = _hoops_CISSS (dc);

	(*dc->_hoops_ACPGR->finish_update)(dc);

	dc->flags &= ~_hoops_GIRIP;

	return true;
}


local bool _hoops_HAGGGR(Display_Context const *dc)
{
	bool	_hoops_IAGGGR = false;

	if (_hoops_GSGPR()) {
		_hoops_CAAI (HOOPS_WORLD->_hoops_PIPSA);
		_hoops_CRCP *	_hoops_IHPSA;
		while ((_hoops_IHPSA = HOOPS_WORLD->_hoops_HIPSA->RemoveFirst()) != null) {
			_hoops_CRCP alter *		_hoops_RARHP = (_hoops_CRCP alter *)_hoops_IHPSA->owner;
			_hoops_SPAGR				_hoops_GHAGR (_hoops_RARHP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
			_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (_hoops_RARHP, false);

			ASSERT(_hoops_CSC != null);

			_hoops_RHPSA *		_hoops_HSPIR = _hoops_CSC->_hoops_AHPSA();

			ASSERT(_hoops_HSPIR != null);

			_hoops_HSPIR->_hoops_IHPSA = null;
			_hoops_HPRH(_hoops_RARHP);

			if (!BIT(_hoops_IHPSA->_hoops_PHSI, _hoops_ISHGP)) {
				_hoops_ACHR _hoops_ACSAP = 0;

				if (BIT(_hoops_RARHP->_hoops_PHSI, _hoops_GIPSA)) {
					_hoops_IAGGGR = true;
					_hoops_ACSAP = _hoops_GPHGP;
				}

				HI_Propagate_Maybes (dc->_hoops_RIGC, _hoops_RARHP, _hoops_IHPSA->_hoops_RCGC|_hoops_ACSAP);
				HI_Propagate_Activity(dc->_hoops_RIGC, (_hoops_SIHIR*)_hoops_RARHP, _hoops_IHPSA->_hoops_CPGPR);

				if (_hoops_IHPSA->geometry != null) {
					if (_hoops_RARHP->geometry == null) {
						// _hoops_IHIS _hoops_CPAP _hoops_HII _hoops_GARHP
						_hoops_RARHP->geometry = _hoops_IHPSA->geometry;
						Geometry *		_hoops_CAGGGR = _hoops_RARHP->geometry;
						_hoops_CAGGGR->backlink = &_hoops_RARHP->geometry;
						do {
							_hoops_CAGGGR->owner = _hoops_RARHP;
						} while ((_hoops_CAGGGR = _hoops_CAGGGR->next) != null);
						_hoops_IHPSA->geometry = null;

						_hoops_RARHP->_hoops_HSRIR = _hoops_IHPSA->_hoops_HSRIR;
						_hoops_RARHP->_hoops_GACP = _hoops_IHPSA->_hoops_GACP;
						_hoops_IHPSA->_hoops_GACP = null;
					}
					else {
						ASSERT(0);
						//_hoops_HASC _hoops_GGR
					}
				}

#if 0
				if (_hoops_IHPSA->_hoops_IPPGR != null) {
					if (_hoops_RARHP->_hoops_IPPGR == null) {
						ASSERT(0);
						//_hoops_SRAI
					}
					else {
						ASSERT(0);
						//_hoops_HASC _hoops_GGR
					}
				}


				if (_hoops_IHPSA->_hoops_RGRPR != null) {
					// _hoops_SPIC _hoops_PPR _hoops_SCAC _hoops_GARHP _hoops_SGI

					if (_hoops_RARHP->_hoops_RGRPR == null) {
						ASSERT(0);
						//_hoops_SRAI
					}
					else {
						ASSERT(0);
						//_hoops_HASC _hoops_GGR
					}
				}
#endif
			}

			// _hoops_CIH _hoops_GARHP
			_hoops_IHPSA->owner = (_hoops_CRCP alter*)HOOPS_WORLD;
			HI_Delete_Renditions (dc->_hoops_RIGC, _hoops_IHPSA);
			_hoops_HPRH(_hoops_IHPSA);
		}

		_hoops_APAI (HOOPS_WORLD->_hoops_PIPSA);

		_hoops_IRRPR();
	}

	return _hoops_IAGGGR;
}

local void _hoops_SAGGGR(_hoops_CRCP const * _hoops_SRCP, _hoops_IAGGI * _hoops_GPGGGR)
{
	Subsegment *			_hoops_GIPIA;

	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		if (_hoops_GIPIA->type == _hoops_IRCP) {
			_hoops_CRCP const * _hoops_SIIS = (_hoops_CRCP const *)_hoops_GIPIA;

			if (BIT (_hoops_SIIS->_hoops_RCGC, _hoops_GPHGP))
				_hoops_SAGGGR(_hoops_SIIS, _hoops_GPGGGR);
		}
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);

	_hoops_GPGGGR->Push(_hoops_SRCP, _hoops_SRCP->bounding->_hoops_PGCIR());
}

GLOBAL_FUNCTION bool HD_Standard_Update (
	Display_Context alter *		dc,
	Activity					_hoops_SCISP) {
	_hoops_CRCP const *				_hoops_GAGGGR = dc->_hoops_AAHSR;
	Net_Rendition				nr;
	Activity					_hoops_RPGGGR = false,
								_hoops_APGGGR = dc->_hoops_HSPGH;
	bool						_hoops_PPGGGR = false;

	ASSERT(dc->_hoops_RIGC != null);

	if (BIT(dc->flags, _hoops_GIRIP))
		return _hoops_HSSSS (dc);

#ifdef _hoops_GGHSH
	dc->_hoops_CPAGH = null;
#endif

	dc->_hoops_HSPGH = 0;
	dc->_hoops_CPGPR = 0;
	dc->_hoops_PCGPR = 0;

	if (HOOPS_WORLD->_hoops_HIPSA &&
		HOOPS_WORLD->_hoops_HIPSA->Count() > 0) {

		if (_hoops_HAGGGR(dc)) {
			// _hoops_HS _hoops_GCRHA _hoops_GAGAR _hoops_HPGGGR
			dc->_hoops_CPGPR |= _hoops_CHPGP;
			dc->flags |= _hoops_CAAGH;

			if (HOOPS_WORLD->_hoops_SHPSA == HOOPS_WORLD->_hoops_CIPSA) {
				HOOPS_WORLD->_hoops_ICPGI += 16;
				if (HOOPS_WORLD->_hoops_ICPGI > 512)
					HOOPS_WORLD->_hoops_ICPGI = 512;
			}
			else {
				HOOPS_WORLD->_hoops_ICPGI -= 16;
				if (HOOPS_WORLD->_hoops_ICPGI < 16)
					HOOPS_WORLD->_hoops_ICPGI = 16;
			}

			if (dc->_hoops_ISPGH == null) {
				dc->_hoops_ISPGH = POOL_NEW(dc->memory_pool, _hoops_IIPSA)(dc->memory_pool);
				dc->_hoops_CSPGH = POOL_NEW(dc->memory_pool, _hoops_IIPSA)(dc->memory_pool);
			}

			size_t _hoops_IPGGGR = HI_Memory_On_Pool(HOOPS_WORLD->memory_pool);

			if (_hoops_IPGGGR > HOOPS_WORLD->_hoops_PCPGI) {
				float	factor = (float)(_hoops_IPGGGR - HOOPS_WORLD->_hoops_PCPGI)/(float)HOOPS_WORLD->_hoops_PCPGI;

				HOOPS_WORLD->_hoops_HCPGI *= 1.0f - factor;
				if (HOOPS_WORLD->_hoops_HCPGI < 0.001f)
					HOOPS_WORLD->_hoops_HCPGI = 0.001f;
				dc->_hoops_CPGPR |= _hoops_CHPGP;
			}
			else {
				if (BIT(dc->flags, _hoops_CAAGH)) {
					if (HOOPS_WORLD->_hoops_HCPGI != 1.0f) {
						float factor = (float)(HOOPS_WORLD->_hoops_PCPGI - _hoops_IPGGGR)/(float)HOOPS_WORLD->_hoops_PCPGI;
						HOOPS_WORLD->_hoops_HCPGI *= 1.0f + factor;
						if (HOOPS_WORLD->_hoops_HCPGI > 1.0f)
							HOOPS_WORLD->_hoops_HCPGI = 1.0f;

						dc->_hoops_CPGPR |= _hoops_CHPGP;
					}
				}
			}
		}
	}

	// _hoops_GAGAR _hoops_CIPH
	if (dc->_hoops_ISPGH != null) {
		dc->_hoops_ISPGH->Flush();
		dc->_hoops_CSPGH->Flush();
	}

	if (dc->_hoops_RCAGH)
		dc->_hoops_CPGPR |= _hoops_CHPGP;

	if (dc->_hoops_ACAGH)
		_hoops_PPGGGR = true;

	dc->flags &= ~_hoops_CAAGH;
	// _hoops_GAGAR _hoops_CIPH

	if (dc->_hoops_PGCC.driver_type == null) {	/* _hoops_SSAS _hoops_SR _hoops_SGIPR _hoops_AASA _hoops_CPGGGR? */
		HD_Get_Physical_Info (dc);

		/* _hoops_HCHRC _hoops_HII _hoops_RAGGGR _hoops_IH _hoops_AAGGGR... */
		dc->current._hoops_HAP.x = dc->_hoops_PGCC._hoops_PRPSR.x / dc->_hoops_PGCC.size.x;
		dc->current._hoops_HAP.y = dc->_hoops_PGCC._hoops_PRPSR.y / dc->_hoops_PGCC.size.y;
		dc->current._hoops_AGRS = dc->current._hoops_HAP.x / dc->current._hoops_HAP.y;
	}

  top:;

	dc->_hoops_RIGC->_hoops_IIHGH = true;

	dc->_hoops_RIIAP = (dc->options._hoops_SRRRR &&
					dc->_hoops_PGCC._hoops_CHHSR == _hoops_RCPGA) ? ~0 : 0;

	dc->_hoops_CPGPR |= _hoops_GAGGGR->_hoops_CPGPR;

	/* _hoops_RH _hoops_SPS _hoops_HIAAR _hoops_RH _hoops_RPCII - _hoops_CACH _hoops_HRHI _hoops_CPIP */
	dc->_hoops_CPGPR |= _hoops_SCISP;

	/* _hoops_CRRIR _hoops_PPGP _hoops_PAAP _hoops_HII _hoops_CGHI _hoops_GHIR, _hoops_IPSH _hoops_SHISR _hoops_GHGPR-_hoops_GHHPI _hoops_IGGRA. */
	if (dc->_hoops_RIIAP) {
		dc->_hoops_CPGPR |= _hoops_APGGGR;
		dc->_hoops_CPGPR |= _hoops_GAGGGR->_hoops_SPGPR;
	}

	dc->_hoops_CPGPR |= _hoops_RPGGGR;
	_hoops_RPGGGR |= dc->_hoops_CPGPR;


	/* _hoops_IPIHR _hoops_SCH _hoops_RPP _hoops_IIH'_hoops_GRI _hoops_ISAP _hoops_CPSA _hoops_CCAH */
	if (!ANYBIT (dc->_hoops_CPGPR, _hoops_IPPGP|_hoops_CHPGP))
		return true;


	/* _hoops_SR'_hoops_ASAR _hoops_GPP _hoops_ISCP _hoops_PPRRR */

	dc->flags |= _hoops_GIRIP;
	dc->flags &= ~(_hoops_IRAGH | _hoops_RPSRR | _hoops_HHICP);

	if (BIT(dc->flags,_hoops_GPHHP))
		dc->flags |= _hoops_RPSRR;

	dc->_hoops_IRPGH = true;

	dc->_hoops_RSAGH = false;
	dc->_hoops_ICAGH = false;

	dc->_hoops_CHICP = null;

	dc->_hoops_RCAGH = false;
	dc->_hoops_PCAGH = false;
	dc->_hoops_ACAGH = false;

	dc->_hoops_HPAGH = null;
	dc->_hoops_PPAGH = false;

	if (dc->_hoops_RIGC->_hoops_HCPGR == 0)
		dc->_hoops_PGCAR = 0;

	dc->_hoops_IGGI->_hoops_ICRGH = HOOPS_WORLD->_hoops_ICRGH;
	dc->_hoops_IGGI->_hoops_CCRGH = HOOPS_WORLD->_hoops_CCRGH;
	dc->_hoops_IGGI->_hoops_SCRGH = HOOPS_WORLD->_hoops_SCRGH;
	dc->_hoops_IGGI->_hoops_GSRGH = HOOPS_WORLD->_hoops_GSRGH;
	dc->_hoops_IGGI->_hoops_PSRGH = HOOPS_WORLD->_hoops_PSRGH;
	dc->_hoops_IGGI->_hoops_HSRGH = HOOPS_WORLD->_hoops_HSRGH;

	dc->_hoops_IGGI->_hoops_PCRGH = HOOPS_WORLD->_hoops_PCRGH;
	dc->_hoops_IGGI->_hoops_HCRGH = HOOPS_WORLD->_hoops_HCRGH;

	/* _hoops_PAGGGR _hoops_CAIR */
	/* (_hoops_IRHH _hoops_AAP _hoops_HRPAI _hoops_CCCI _hoops_IH _hoops_IHPI _hoops_PAAP) */
	(*dc->_hoops_ACPGR->init_update)(dc);

	/* _hoops_IRHH _hoops_HCR _hoops_RH _hoops_SCIA-_hoops_PAPA _hoops_HGIIP _hoops_CCCI */
	if (dc->_hoops_AAHSR->type != _hoops_IRCP || dc->_hoops_SHCIP == null ||
		_hoops_PISSS (_hoops_GAGGGR, true, true, dc->_hoops_GHRI->_hoops_GPPI)) {
		/* _hoops_PRHSA _hoops_RH _hoops_SCIA _hoops_HGIIP _hoops_RGAR _hoops_RPP _hoops_AIRC _hoops_HS _hoops_HGAS!
		 *
		 * (_hoops_RGR _hoops_SPGGGR _hoops_HHH _hoops_GAHIR - _hoops_CAGH _hoops_PPCCI _hoops_IIGR _hoops_RH _hoops_RHPP _hoops_CAGH,
		 *	_hoops_IH _hoops_SPR _hoops_PCAI.)
		 */

		dc->_hoops_RASIP(_hoops_AASIP);

		dc->_hoops_PCGPR |= _hoops_HSPGP;

		nr = _hoops_CISSS (dc);

		if (!dc->_hoops_CSAGH) {
			_hoops_RSHGH(nr);
			dc->_hoops_CSAGH = true;
		}

		if (_hoops_GGPGR(nr)) {
			(*dc->_hoops_ACPGR->finish_update)(dc);
			if (dc->_hoops_RSAGH) {
				_hoops_APSRR(dc, "interrupt_and_recycle 1","", 0);
				goto top;
			}
			dc->flags &= ~_hoops_GIRIP;
			return true;
		}

		dc->_hoops_RIIAP = (dc->options._hoops_SRRRR &&
					dc->_hoops_PGCC._hoops_CHHSR == _hoops_RCPGA) ? ~0 : 0;

		_hoops_RPGGGR |= dc->_hoops_CPGPR;

		if (ALLBITS (dc->_hoops_CPGPR, _hoops_RCGSA)) {
			/* _hoops_IIS _hoops_RH _hoops_RHPP _hoops_IHSH _hoops_AARI _hoops_GICS _hoops_IRS _hoops_IGRH
			 * (_hoops_GAAP _hoops_IIH _hoops_AAPR _hoops_AHSC _hoops_HSAGA _hoops_SHPH)
			 */
			(*dc->_hoops_ACPGR->finish_update)(dc);
			(*dc->_hoops_ACPGR->init_update)(dc);

			/* _hoops_PPR _hoops_GGR _hoops_AGIR _hoops_RH _hoops_CCAH _hoops_CCCSI() _hoops_HGAS _hoops_CPHP... */
			if (_hoops_GGPGR(nr)) {
				(*dc->_hoops_ACPGR->finish_update)(dc);
				if (dc->_hoops_RSAGH) {
					_hoops_APSRR(dc, "interrupt_and_recycle 2","", 0);
					goto top;
				}
				dc->flags &= ~_hoops_GIRIP;
				return true;
			}
		}

		_hoops_PPGGGR = true;
	}
	else
		nr = dc->_hoops_SHCIP;

	nr->flags &= ~_hoops_HSPSP;


	if (!BIT (nr->_hoops_RGP, T_WINDOWS)) {
		if (BIT(dc->flags, _hoops_SAISR))
			_hoops_AISSS(nr);
	}
	else {
		/* _hoops_IIS _hoops_AAPA _hoops_HARH _hoops_ACPA _hoops_RGR... */
		_hoops_GGAGR alter *		_hoops_GHRI = (_hoops_GGAGR alter *)dc->_hoops_GHRI;

		_hoops_GHRI->_hoops_RIIAP = dc->_hoops_RIIAP;

		if (BIT (_hoops_GAGGGR->_hoops_PHSI, _hoops_HCGPR) ||		// _hoops_PPSPR _hoops_AGRP (_hoops_RII _hoops_HSAR _hoops_HHCI-_hoops_IHCI)
			dc->_hoops_HRHPP[_hoops_SRHPP].list == null) {		// _hoops_PAR _hoops_SR _hoops_SPGA'_hoops_RA _hoops_IRCC _hoops_IS _hoops_SAS _hoops_PCCP _hoops_AGRRR _hoops_PAAP
			_hoops_PPGGGR = true;
			((_hoops_CRCP *)_hoops_GAGGGR)->_hoops_PHSI &= ~_hoops_HCGPR;
		}

		LOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);
		dc->_hoops_GSAGH = false;
		if (dc->options._hoops_GSPRP != _hoops_ICPRP &&
			!BIT (HOOPS_WORLD->system_flags, _hoops_HSCPP) &&
			!_hoops_PSSSS(dc->_hoops_RIGC)) {
			if (HOOPS_WORLD->_hoops_SIHGH > 0 || HI_Enable_Timer_Interrupts()) {
				dc->_hoops_GSAGH = true;
				++HOOPS_WORLD->_hoops_SIHGH;
			}
		}
		UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);

		_hoops_HCSIR alter *	_hoops_ICSIR = dc->_hoops_CISCP;

		if (_hoops_PPGGGR) {
			_hoops_APSRR(dc, "fresh_update","", 0);

			dc->_hoops_CGAP = 0;
			dc->_hoops_RPAGH++;

			if (_hoops_ICSIR) do {
				_hoops_ICSIR->_hoops_SCIIP = false;
			} while ((_hoops_ICSIR = _hoops_ICSIR->next) != null);

			/* _hoops_RPIHR _hoops_HAIR _hoops_GASR _hoops_IRHS _hoops_IGGAR? */
			if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR &&
				!dc->_hoops_SCAGH &&
				BIT (_hoops_GAGGGR->_hoops_RCGC, _hoops_ASRRA)) {
				HD_Free_Colors (dc);
				HD_Get_Colors (dc);
				dc->_hoops_CPGPR = _hoops_RCGSA;
				dc->_hoops_HSPGH = _hoops_RCGSA;
				_hoops_RPGGGR |= dc->_hoops_CPGPR;
			}

			// _hoops_PCSHA _hoops_IRHS _hoops_IS _hoops_HS _hoops_IRS _hoops_PIRA _hoops_RRPAR _hoops_HSAR _hoops_HISI _hoops_AIRC _hoops_SIAS _hoops_HS
			// _hoops_HGAS, _hoops_GAPR _hoops_HGGC _hoops_CRGP _hoops_HSAR _hoops_IPPSA->_hoops_GRHAP, _hoops_CR _hoops_SR _hoops_SIAS _hoops_RHGPA
			((_hoops_GGAGR alter *)dc->_hoops_GHRI)->_hoops_GPPI = HOOPS_WORLD->_hoops_GPPI - 1;

			if (BIT(dc->_hoops_CPGPR, _hoops_APPGP))
				dc->_hoops_GPAGH = HOOPS_WORLD->_hoops_GPPI - 1;

			HD_Preprocess (nr);
			/* _hoops_PSHA _hoops_CHR _hoops_CCCI _hoops_HA; _hoops_ISPR _hoops_SGI */
		}
		else {
			dc->_hoops_CGAP++;
			dc->_hoops_RPAGH = 0;

			_hoops_APSRR(dc, "update_slice++","", 0);

			// _hoops_RRP _hoops_IS _hoops_RARI
			if (BIT (_hoops_GAGGGR->_hoops_PHSI, _hoops_ICGPR)) {
				((_hoops_CRCP *)_hoops_GAGGGR)->_hoops_PHSI &= ~_hoops_ICGPR;
				dc->_hoops_PCAGH = true;
			}
			else if (_hoops_ICSIR) {
				do {
					if (_hoops_ICSIR->_hoops_SCIIP) {
						((_hoops_CRCP *)_hoops_GAGGGR)->_hoops_PHSI &= ~_hoops_ICGPR;
						dc->_hoops_PCAGH = true;
						break;
					}
				} while ((_hoops_ICSIR = _hoops_ICSIR->next) != null);
			}
		}

		(*dc->_hoops_ACPGR->init_picture) (nr);


		/* _hoops_RRP _hoops_IS _hoops_PIHHR _hoops_AGCIP _hoops_RIPS _hoops_SRHR _hoops_GAR _hoops_IAH _hoops_GAR _hoops_SR _hoops_PAH */
		if (!(dc->_hoops_SHPGR == QMoves_XOR &&
			dc->_hoops_PGCC._hoops_CHHSR == _hoops_RCPGA)) {
			int	_hoops_HGRS = 0;

			while (dc->_hoops_IPCI->prev != null) {
				_hoops_HGRS++;
				_hoops_IGRS (dc);
			}

			bool _hoops_GIIIP = BIT(dc->flags, _hoops_RPSRR);
			dc->flags |= _hoops_RPSRR;
			(*dc->_hoops_ACPGR->_hoops_SCPGR) (nr);
			if (!_hoops_GIIIP)
				dc->flags &= ~_hoops_RPSRR;

			while (_hoops_HGRS-- > 0)
				_hoops_SGRS (dc);
		}


		if (!BIT(nr->transform_rendition->heuristics,_hoops_RRIRP)) {
			dc->_hoops_CPGPR |= _hoops_GCPGP; /* _hoops_HHSA _hoops_IRS _hoops_IHIR _hoops_AIIAP */
			dc->_hoops_HSPGH |= _hoops_GCPGP;/*_hoops_SPS _hoops_GHGGGR*/
			_hoops_RPGGGR |= dc->_hoops_CPGPR;
		}

		if (BIT(dc->flags, _hoops_CHIIP) &&
			!BIT(dc->_hoops_PGCC.flags, _hoops_PAGIP))
			dc->_hoops_CPGPR |= _hoops_RAGGA|_hoops_APPGP;

		dc->flags &= ~(_hoops_SHIIP | _hoops_CHIIP);

		/* _hoops_HA _hoops_AIRI _hoops_PPR _hoops_SRGS _hoops_RH _hoops_PCSHA _hoops_CAGH */

		nr.Modify();
		nr->current = 0; /* _hoops_RHGGGR, _hoops_AHGGGR */
		nr->_hoops_RCSHR = dc->_hoops_PSPGH;

		if (_hoops_PPGGGR) {
			_hoops_RCCA(_hoops_CSRGH) = 0;
			_hoops_RCCA(_hoops_SSRGH) = 0;

			if (dc->_hoops_GCHCP != null) {
				/* _hoops_IRHH _hoops_RCRR _hoops_PCHCP _hoops_SGHC _hoops_HGCR _hoops_SIGSA _hoops_RGR _hoops_GHIR _hoops_HAH... */
				_hoops_RISSS(dc, dc->_hoops_GCHCP, _hoops_GGARA);

				/* _hoops_RRP _hoops_IS _hoops_AIIAP _hoops_HGHIP _hoops_RPP _hoops_IAGIP */
				if (BIT(dc->flags, _hoops_CHIIP) &&
					dc->_hoops_RSCIP != null)
					_hoops_RISSS(dc, dc->_hoops_RSCIP,
						_hoops_RIPGP|_hoops_PPPGP);

				_hoops_RPGGGR |= dc->_hoops_CPGPR;
				dc->_hoops_CPGPR |= _hoops_GAGGGR->_hoops_CPGPR; /* _hoops_SAHR _hoops_GGR _hoops_AGIR */
				dc->_hoops_CPGPR |= _hoops_GAGGGR->_hoops_SPGPR&dc->_hoops_RIIAP;
			}

			// _hoops_CASI _hoops_GGSR _hoops_ISCP _hoops_RHGS _hoops_PHGGGR _hoops_PPR _hoops_IRHH _hoops_RCRR _hoops_ISCP _hoops_PIAP _hoops_HRGR _hoops_CASI
			HD_Clean_DC_Breadcrumbs (dc);

			dc->flags &= ~_hoops_HSAGR;
			dc->_hoops_IASS = _hoops_HRAGH;
			dc->_hoops_IPCI->mask = _hoops_RAPI;
			dc->flags |= _hoops_RASS;
			dc->_hoops_RASIP(_hoops_AASIP);
		}
		else {
			_hoops_GPRH(_hoops_ASRGH) = true;

			if (dc->_hoops_AHSI != null && dc->_hoops_AHSI->nr != null)
				(*dc->_hoops_ACPGR->init_picture) (dc->_hoops_AHSI->nr);

			if (dc->_hoops_PCAGH && dc->_hoops_GCHCP != null) {
				/* _hoops_IRHH _hoops_RCRR _hoops_PCHCP _hoops_SGHC _hoops_HGCR _hoops_SIGSA _hoops_RGR _hoops_GHIR _hoops_HAH... */
				_hoops_RISSS(dc, dc->_hoops_GCHCP, _hoops_GGARA);

				if (dc->_hoops_GCHCP != null)
					HD_Free_Overlay_Segments ((_hoops_SCCIP alter * alter *)&dc->_hoops_GCHCP);
			}
		}

		if (dc->_hoops_PCAGH)
			HD_Revisit_Overlay (dc);
		else if (dc->_hoops_HRHPP[_hoops_SRHPP].list == null) {
			// _hoops_PAGA: _hoops_GSSR _hoops_ARAR _hoops_HHS _hoops_SAHR _hoops_CHHSS _hoops_CRGC _hoops_IS _hoops_GSRS _hoops_SPR, _hoops_HIH _hoops_HHH _hoops_ARAR,
			// _hoops_HGPP _hoops_GAR _hoops_RCAR _hoops_RGAP, _hoops_RRP _hoops_RH _hoops_IHH "_hoops_SRS _hoops_HHIS" _hoops_HGSR, _hoops_HIS _hoops_SR _hoops_IIS _hoops_HHGGGR _hoops_RGHH _hoops_PGI
			_hoops_AASS (nr, dc->_hoops_AAHSR, _hoops_HICS());
		}

		HD_Draw_Deferred_Trees (dc);

		if (dc->_hoops_CRIGA != null)
			HD_Process_Cut_Geometry (nr, null, _hoops_HICS(), false, true);

		{
			int	_hoops_HGRS = 0;

			while (dc->_hoops_IPCI->prev != null) {
				_hoops_HGRS++;
				_hoops_IGRS (dc);
			}

			bool _hoops_GIIIP = BIT(dc->flags, _hoops_RPSRR);
			dc->flags |= _hoops_RPSRR;

			/* _hoops_RRP _hoops_IS _hoops_PIHHR _hoops_AGCIP _hoops_RIPS _hoops_SRHR _hoops_GAR _hoops_IAH _hoops_GAR _hoops_SR _hoops_PAH */
			if (dc->_hoops_SHPGR == QMoves_XOR &&
				dc->_hoops_PGCC._hoops_CHHSR == _hoops_RCPGA)
				(*dc->_hoops_ACPGR->_hoops_SCPGR) (nr);

			(*dc->_hoops_ACPGR->draw_overlay_list) (nr);

			if (!_hoops_GIIIP)
				dc->flags &= ~_hoops_RPSRR;

			while (_hoops_HGRS-- > 0)
				_hoops_SGRS (dc);
		}


		if (dc->_hoops_ISPGH != null) {
			size_t _hoops_IPGGGR = HI_Memory_On_Pool(HOOPS_WORLD->memory_pool);

			if (HOOPS_WORLD->_hoops_HCPGI != 1.0f &&
				dc->_hoops_ISPGH->Count() > 0) {

				_hoops_IAGGI * _hoops_GPGGGR = POOL_NEW(dc->memory_pool, _hoops_IAGGI)(dc->memory_pool);

				_hoops_CRCP const * _hoops_SRCP;

				while ((_hoops_SRCP = dc->_hoops_ISPGH->RemoveFirst()) != null)
					_hoops_SAGGGR(_hoops_SRCP, _hoops_GPGGGR);
					//_hoops_IHGGGR->_hoops_PASSC(_hoops_PHHIP, _hoops_PHHIP->_hoops_IASC->_hoops_IGGRR());

				while (_hoops_GPGGGR->Pop(&_hoops_SRCP)) {
					HI_Really_Flush_Geometry (dc->_hoops_RIGC, (_hoops_CRCP alter *)_hoops_SRCP,
						_hoops_CGGPP|_hoops_SGGPP/*|_hoops_CHGGGR*/);

					dc->flags |= _hoops_CAAGH;
					dc->_hoops_ACAGH = true;
					HOOPS_WORLD->_hoops_RAAPH = true;

					_hoops_IPGGGR = HI_Memory_On_Pool(HOOPS_WORLD->memory_pool);

					if (_hoops_IPGGGR < HOOPS_WORLD->_hoops_PCPGI)
						break;
				}

				delete _hoops_GPGGGR;
			}

			if (HOOPS_WORLD->_hoops_HCPGI != 1.0f &&
				dc->_hoops_CSPGH->Count() > 0) {

				_hoops_IAGGI * _hoops_GPGGGR = POOL_NEW(dc->memory_pool, _hoops_IAGGI)(dc->memory_pool);

				_hoops_CRCP const * _hoops_SRCP;

				while ((_hoops_SRCP = dc->_hoops_CSPGH->RemoveFirst()) != null)
					_hoops_SAGGGR(_hoops_SRCP, _hoops_GPGGGR);

				while (_hoops_GPGGGR->Pop(&_hoops_SRCP)) {
					HI_Really_Flush_Geometry (dc->_hoops_RIGC, (_hoops_CRCP alter *)_hoops_SRCP,
						_hoops_CGGPP|_hoops_SGGPP/*|_hoops_CHGGGR*/);

					dc->flags |= _hoops_CAAGH;
					dc->_hoops_ACAGH = true;
					HOOPS_WORLD->_hoops_RAAPH = true;

					_hoops_IPGGGR = HI_Memory_On_Pool(HOOPS_WORLD->memory_pool);

					if (_hoops_IPGGGR < HOOPS_WORLD->_hoops_PCPGI)
						break;
				}

				delete _hoops_GPGGGR;
			}
		}

#if 0
//_hoops_ASIGA
		if (1 || HOOPS_WORLD->display_list_vram_usage > HOOPS_WORLD->_hoops_PHARR*0.5f) {
			_hoops_CAAI (HOOPS_WORLD->_hoops_SAAI);
			_hoops_AGCI alter *		_hoops_AGAGR = HOOPS_WORLD->_hoops_GPAI;
			int										n = 0;

			while (_hoops_AGAGR != null) {
				_hoops_AGCI alter *	_hoops_RRAGR = _hoops_AGAGR->next;

				n++;

				if (_hoops_AGAGR->_hoops_GPPI < HOOPS_WORLD->_hoops_GPPI) {
					HD_Queue_Destroy_List(_hoops_AGAGR, false);
				}

				_hoops_AGAGR = _hoops_RRAGR;
			}
			_hoops_APAI (HOOPS_WORLD->_hoops_SAAI);
		}
#endif

		if (dc->_hoops_GHRI->_hoops_RGAGR)
			(*dc->_hoops_ACPGR->_hoops_SSRGR) (dc);

		/* _hoops_PAAP _hoops_GHIR */
		_hoops_RCCA(_hoops_IPRGH) = (HI_What_Time() - dc->_hoops_RIGC->_hoops_GHPGI) / _hoops_HSPGR;

		if (BIT(dc->flags, _hoops_CHSI)) {
			// "_hoops_CASRR _hoops_RGAR" _hoops_IRHS _hoops_IS _hoops_IHPS _hoops_ARI _hoops_PGGA _hoops_SR _hoops_GA'_hoops_RA _hoops_HHGC _hoops_SCH _hoops_IS _hoops_ASSI
			// _hoops_RH _hoops_AIRI _hoops_IIGR _hoops_RHPP _hoops_GCHA _hoops_GGR _hoops_RSRA _hoops_SRHR _hoops_CCH
			dc->flags |= _hoops_ICPGR;
			if (!dc->options._hoops_SRRRR)
				dc->flags &= ~_hoops_CHSI;
		}

		if (dc->options._hoops_CASSP ||
			dc->options._hoops_SASSP ||
			dc->options._hoops_GPSSP)
			_hoops_IGGGGR(nr);

		_hoops_GSPGR _hoops_SHGGGR = HI_What_Time();

		_hoops_IIIGH (nr, dc->options._hoops_SRRRR && !dc->_hoops_ICAGH);

		/* _hoops_HPIRA _hoops_GHIR */
		_hoops_RCCA(_hoops_CPRGH) = (HI_What_Time() - _hoops_SHGGGR) / _hoops_HSPGR;

#if 0
		if (dc->_hoops_CGAP == 0 &&
			dc->_hoops_RIGC->_hoops_HCPGR != 0 &&
			dc->_hoops_CPAGH != null) {

			_hoops_GSPGR	update = _hoops_RCCA(_hoops_IPRGH) * _hoops_HSPGR;
			_hoops_GSPGR	_hoops_GIGGGR = _hoops_RCCA(_hoops_CPRGH) * _hoops_HSPGR;

			_hoops_GSPGR	total = update + _hoops_GIGGGR;


#define _hoops_RIGGGR 1024*1024

			if (dc->_hoops_PGCAR > 0) {
				if (total > dc->_hoops_RIGC->_hoops_RHPGI * 1.1) {
					dc->_hoops_PGCAR = (int)(dc->_hoops_PGCAR *  0.9);
					if (dc->_hoops_PGCAR < _hoops_RIGGGR * 0.1)
						dc->_hoops_PGCAR = _hoops_RIGGGR * 0.1;
				}
				else if (total < dc->_hoops_RIGC->_hoops_RHPGI * 0.9) {
					dc->_hoops_PGCAR = (int)(dc->_hoops_PGCAR *  1.1);
					if (dc->_hoops_PGCAR > _hoops_RIGGGR * 10)
						dc->_hoops_PGCAR = _hoops_RIGGGR * 10;
				}
			}
			else {
				if (total > dc->_hoops_RIGC->_hoops_RHPGI)
					dc->_hoops_PGCAR = _hoops_RIGGGR;
			}
		}
#endif

		dc->flags &= ~_hoops_CHSI;

		LOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);
		if (dc->_hoops_GSAGH) {
			if (--HOOPS_WORLD->_hoops_SIHGH == 0)
				HI_Disable_Timer_Interrupts();

			dc->_hoops_GSAGH = false;
		}

		UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);
	}

	(*dc->_hoops_ACPGR->finish_update)(dc);

	dc->flags &= ~_hoops_GIRIP;

	if (dc->_hoops_RSAGH) {
		/* _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_ARSSA _hoops_IHCI... */
		_hoops_RPGGGR |= dc->_hoops_CPGPR;
		_hoops_APGGGR |= dc->_hoops_HSPGH;

		_hoops_APSRR(dc, "interrupt_and_recycle 3","", 0);

		/* _hoops_HPPR _hoops_HPPR _hoops_GICS */
		goto top;
	}
	else if (BIT(dc->flags, _hoops_IRAGH)) {
		/* _hoops_RCIPR _hoops_IRHH _hoops_RCRR (_hoops_HIIPA) */
		dc->_hoops_HSPGH = _hoops_APGGGR;
	}
	else
		_hoops_APSRR(dc, "update_complete","", 0);

	return true;
}

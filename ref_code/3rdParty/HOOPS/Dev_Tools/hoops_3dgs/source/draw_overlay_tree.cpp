/*
 * Copyright (c) 1998-2001 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.198 2010-08-13 18:06:50 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "phedron.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


local Geometry const * _hoops_HHHCP (
	Net_Rendition const &		nr,
	Geometry const *			geometry,
	Action_Mask					mask,
	bool						single) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_HSIIP alter *		si;

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_IPIGA))
		return null;
#endif

	ZALLOC (si, _hoops_HSIIP);
	si->nr = nr;
	si->geometry = geometry;
	si->segment = dc->_hoops_RRCIP;
	si->path = dc->path;
	si->mask = mask;
	si->single = single;
	_hoops_PRRH (geometry);

	*dc->_hoops_IHHCP = si;
	dc->_hoops_IHHCP = &si->next;

	dc->_hoops_CHHCP = true;
	if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT)
		dc->_hoops_GSGC |= HD_Geometry_To_Action_Mask (geometry);

	return null;
}


local Geometry const * _hoops_SHHCP (
	Net_Rendition const &		nr,
	Geometry const *			geometry,
	Action_Mask					mask,
	bool						single) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_HSIIP alter *		si;

	UNREFERENCED (mask);
	UNREFERENCED (single);

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_IPIGA))
		return null;
#endif

	if (ANYBIT(dc->flags, _hoops_GIHCP|_hoops_CHSHP))
		return null;

	if (!BIT (nr->current, _hoops_AHIHP) ||
		nr->_hoops_CPP->_hoops_PRH.style == _hoops_GCPI) {

		ZALLOC (si, _hoops_HSIIP);
		si->nr = nr;
		si->geometry = geometry;
		si->segment = dc->_hoops_RRCIP;
		si->path = dc->path;
		si->mask = mask;
		si->single = single;
		_hoops_PRRH (geometry);

		*dc->_hoops_RIHCP = si;
		dc->_hoops_RIHCP = &si->next;

		dc->_hoops_CHHCP = true;
		if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT)
			dc->_hoops_GSGC |= HD_Geometry_To_Action_Mask (geometry);
	}
	else {
		do {
			switch (geometry->type) {
				case _hoops_PRCP:
				case _hoops_GSIP:
				case _hoops_SCIP:
				case _hoops_CSIP:
				case _hoops_ASIP:
				case _hoops_HSIP:
				case _hoops_GGCP:
				case _hoops_RCIP:
					HD_Standard_Render (nr, geometry, mask, true);
					break;

				default:
					ZALLOC (si, _hoops_HSIIP);
					si->nr = nr;
					si->geometry = geometry;
					si->segment = dc->_hoops_RRCIP;
					si->path = dc->path;
					si->mask = mask;
					si->single = true;
					_hoops_PRRH (geometry);

					*dc->_hoops_RIHCP = si;
					dc->_hoops_RIHCP = &si->next;

					dc->_hoops_CHHCP = true;
					if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT)
						dc->_hoops_GSGC |= HD_Geometry_To_Action_Mask (geometry);
			}
		} while (!single && (geometry = geometry->next) != null);
	}

	return null;
}


local void _hoops_AIHCP (
	Net_Rendition const &		nr,
	Tristrip const *			ts) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_HSIIP alter *		si;
	_hoops_HHA const &	matr = nr->_hoops_IHA->_hoops_CHA;

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_IPIGA)) return;
#endif

	if (!BIT (nr->_hoops_SRA->_hoops_IASS, _hoops_HHIIP))
		HE_ERROR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				"mismatch detected in geometry deferral lists for spriting");

	if (!BIT (ts->_hoops_SRHA, DL_SHADOW_TRISTRIP)) {
		if (matr->_hoops_SCA &&
			matr->_hoops_SCA->texture &&
			BIT (matr->_hoops_SCA->texture->flags, _hoops_IAPS)) {
			HD_Std_3D_Tristrip (nr, ts);
			return;
		}
		if (matr->_hoops_IRIR < 1.0f) {
			HD_Std_3D_Tristrip (nr, ts);
			return;
		}
	}

	/* _hoops_RH _hoops_ACSP _hoops_IIGR _hoops_RGR _hoops_API _hoops_CGH _hoops_RGAR _hoops_SHH _hoops_IH _hoops_RCAR _hoops_IIRGR (_hoops_CSIIP _hoops_AACC _hoops_CPAP _hoops_HAH?) */

	ZALLOC (si, _hoops_HSIIP);
	si->nr = nr;

	if (BIT(ts->_hoops_SRHA, DL_TEMPORARY_DATA))
		HD_Isolate_Tristrip_Data (dc, ts);
	si->_hoops_ISIIP = (Tristrip *)ts;
	si->segment = dc->_hoops_RRCIP;
	si->path = dc->path;
	_hoops_CAHS (ts);

	*dc->_hoops_RIHCP = si;
	dc->_hoops_RIHCP = &si->next;
}



struct _hoops_PIHCP : public _hoops_HIHCP {
	_hoops_CRCP const *			segment;
	int						_hoops_IASS;
	int						_hoops_IIHCP;

	_hoops_PIHCP (_hoops_CRCP const * s, int _hoops_CIHCP, int uc)
		: segment (s), _hoops_IASS (_hoops_CIHCP), _hoops_IIHCP (uc) {}

	bool _hoops_SIHCP (Net_Rendition alter & nr, bool _hoops_PPHPP) alter {
		Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;

		if (_hoops_PPHPP)
			return true;

		if (dc->_hoops_CHHCP || dc->_hoops_HASS[dc->_hoops_IASS] != null) {
			_hoops_SCCIP alter *		_hoops_GSCIP;
			/* _hoops_RRP _hoops_IS _hoops_RCPS _hoops_ISSC _hoops_SPS _hoops_GHIR */
			ALLOC (_hoops_GSCIP, _hoops_SCCIP);
			_hoops_GSCIP->segment = (_hoops_CRCP *)segment;
			_hoops_PRRH (segment);
			_hoops_GSCIP->next = (_hoops_SCCIP alter *)dc->_hoops_GCHCP;/*_hoops_ICIC _hoops_HIIC */
			dc->_hoops_GCHCP = _hoops_GSCIP;
		}

		/* _hoops_HCR _hoops_CPHR */

		_hoops_HGSGA (dc,"overlay");
		/* _hoops_HSPR _hoops_HAPR _hoops_CGH _hoops_RGAR _hoops_GRCI _hoops_GGR _hoops_PIHHR */
		while (_hoops_IIHCP--)
			_hoops_SGRS (dc);

		if (_hoops_IASS)
			HD_Alternate_Hidden_Root (dc, _hoops_IASS);

		return true;
	}
};


GLOBAL_FUNCTION void HD_Prepare_Overlay_Tree (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP) {

	nr.Modify();

	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_HHCR			_hoops_IHCR = nr->transform_rendition;
	int							_hoops_IASS = 0;
	int							_hoops_IIHCP = 0;

	if (!BIT(dc->flags, _hoops_RCHCP) && dc->_hoops_SHCI() != _hoops_HRIIP) {
		// _hoops_ICPPA _hoops_RH _hoops_HHIS _hoops_SPIC _hoops_AHSAR _hoops_IH _hoops_GPP _hoops_SPR _hoops_HPPCR _hoops_HIS _hoops_SGS _hoops_SR _hoops_RGAR _hoops_PSCPR _hoops_ARR
		dc->_hoops_AHSI->stage = _hoops_ACHCP;
		return;
	}

	if (BIT (nr->current | nr->_hoops_RCSHR, _hoops_CSGGR) &&
		nr->_hoops_IRR->_hoops_SRI == _hoops_PRAAP) {
		/* _hoops_HHSP _hoops_IAGIP _hoops_RPP _hoops_CCSHP-_hoops_III _hoops_PAR _hoops_SHASA & _hoops_GHARR _hoops_PAH'_hoops_RA _hoops_RGHH _hoops_SCH */
		nr->_hoops_RCSHR &= ~(_hoops_CRSI|_hoops_SRSI);
		return;
	}


	if (BIT (nr->_hoops_RCSHR, _hoops_SRSI))
		dc->flags |= _hoops_CHIIP;

	dc->_hoops_CHHCP = false;

	/* _hoops_PPR _hoops_SSPC _hoops_RCPGP _hoops_RPP _hoops_GHGA _hoops_HHCI _hoops_IHCI */
	nr->_hoops_RCSHR &= ~_hoops_AIPIP;

	nr->current |= _hoops_CRSI;

	if (BIT (nr->_hoops_RCSHR, _hoops_SRSI)) {
		nr->current |= _hoops_SRSI;
		if (!BIT (dc->_hoops_IASS, _hoops_HHIIP))
			_hoops_IASS = _hoops_HHIIP;
	}
	else {
		/* _hoops_PCHCP _hoops_CIPH _hoops_CGH _hoops_SHH _hoops_CHCC _hoops_HPP _hoops_RH _hoops_RHPP, _hoops_HAR _hoops_RH _hoops_ICCGR _hoops_HCHSR _hoops_SRHR */
		if (ANYBIT (nr->current, _hoops_RSSHP|_hoops_CISHP)) {
			HD_Handle_FBI_Pending_Window (nr);
			nr->current &= ~(_hoops_RSSHP|_hoops_CISHP);
			nr->_hoops_RCSHR &= ~(_hoops_RSSHP|_hoops_CISHP);
		}
		if (dc->_hoops_SHPGR == QMoves_XOR) {
			nr->transform_rendition.Modify();
			HD_Set_Z_Buffering_Transform (nr, false, false, 0.0f);
			nr->current &= ~_hoops_CSGGR;
			nr->_hoops_RCSHR &= ~_hoops_CSGGR;
			while (BIT (dc->_hoops_IPCI->mode, _hoops_CSGGR)) {
				_hoops_IGRS (dc);
				_hoops_IIHCP++;
			}
		}
		if (!BIT (dc->_hoops_IASS, _hoops_IHPGR))
			_hoops_IASS = _hoops_IHPGR;
	}
	if (_hoops_IASS)
		HD_Alternate_Hidden_Root (dc, _hoops_IASS);


	/* _hoops_RPP (_hoops_CSPH->_hoops_HCHCP == _hoops_ICHCP) */ {
		if (ANYBIT (nr->_hoops_RCSHR, _hoops_HSGGR|_hoops_ISGGR))
			nr->_hoops_IRR.Modify()->_hoops_CHP &= ~(_hoops_SHP|_hoops_CRAAP);
		nr->_hoops_RCSHR &= ~(_hoops_HSGGR|_hoops_ISGGR);
	}

	/* _hoops_RGR _hoops_HRGR _hoops_PAHH _hoops_CCHCP _hoops_CGPR _hoops_RH _hoops_RPPS & _hoops_CIHH _hoops_HS _hoops_AIAH _hoops_RPII
	 * _hoops_GGSRA - _hoops_HIS _hoops_SR _hoops_PIHA _hoops_RHSHA _hoops_RH _hoops_CIHH _hoops_PPR _hoops_RH _hoops_RSGA...
	 */
	dc->_hoops_CPGPR |= _hoops_RCGSA; /* _hoops_RHGGP _hoops_SCHCP */

	if (!ALLBITS (_hoops_IHCR->flags, _hoops_PRAIP|_hoops_ASPIP)) {
		_hoops_IHCR = nr->transform_rendition.Modify();

		if (!BIT (_hoops_IHCR->flags, _hoops_ASPIP)) {
			HD_Compute_Hard_Clip (nr, null);
			_hoops_IHCR = nr->transform_rendition;
		}
		if (!BIT (_hoops_IHCR->flags, _hoops_PRAIP)) {
			_hoops_HRPA			_hoops_RHSPR;

			HD_Undo_Screen (nr, &_hoops_RHSPR);
			_hoops_IHCR->flags |= _hoops_PRAIP;
			HD_Redo_Screen (nr, &_hoops_RHSPR);
		}
	}

#ifdef HOOPS_DEBUG_BUILD
	if (dc->_hoops_APHHP != null)
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				   "overlay during select");
#endif

	_hoops_HGCGA (dc, "overlay", nr);
	if (BIT (nr->current, _hoops_SRSI)) {
		dc->_hoops_IPCI->_hoops_CHCI						= _hoops_SHHCP;
		/* _hoops_RGCH _hoops_CHR _hoops_CHCC _hoops_GAR _hoops_HHHA _hoops_CCGI */
		dc->_hoops_IPCI->draw_3d_tristrip			= _hoops_AIHCP;
	}
	else {
		dc->_hoops_IPCI->_hoops_CHCI						= _hoops_HHHCP;
	}

	dc->_hoops_AHSI->_hoops_GSHCP (POOL_NEW(dc->memory_pool, _hoops_PIHCP)(_hoops_SRCP, _hoops_IASS, _hoops_IIHCP));
}


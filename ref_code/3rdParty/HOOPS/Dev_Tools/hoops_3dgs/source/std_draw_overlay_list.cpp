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
 * $Id: obf_tmp.txt 1.77 2010-06-11 03:19:43 covey Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


/* _hoops_IPCP _hoops_AGCIP _hoops_HIGR _hoops_HRGR _hoops_IRS _hoops_RSCA _hoops_IGRH _hoops_HAGH _hoops_HII _hoops_RH _hoops_PGSA _hoops_HIGR.  _hoops_PS _hoops_PAH'_hoops_RA 
 * _hoops_HRAR _hoops_GPP _hoops_RH _hoops_ISHI->_hoops_SPS _hoops_CICRR _hoops_PSRSS _hoops_PPSI (_hoops_SSHSR _hoops_PAH _hoops_GGCR _hoops_PAR _hoops_HASIR _hoops_SRGR
 * _hoops_GAPA _hoops_HGISR), _hoops_HIS _hoops_RCSAR _hoops_IGGA _hoops_GPSPR _hoops_IIGR _hoops_CPAP _hoops_IRHS 
 * _hoops_RGCI _hoops_HAII _hoops_HSRSS.  _hoops_HGI _hoops_CGH _hoops_RGAR _hoops_SHH _hoops_IGI _hoops_IH _hoops_RH _hoops_ICHCP _hoops_AGIR */
local void _hoops_ISRSS (
	Display_Context alter *		dc) {
	_hoops_HSIIP const *		si;
	_hoops_HSIIP alter *		_hoops_CIPPI;
	Geometry const *			geometry;
	_hoops_HSIIP alter * alter *_hoops_CSRSS;

	_hoops_CSRSS = &dc->_hoops_CRHGH;
	if ((si = dc->_hoops_CHPGR) != null) do {
		if ((geometry = si->geometry) != null) do {
			ZALLOC (_hoops_CIPPI, _hoops_HSIIP);
			_hoops_CIPPI->nr = si->nr;
			/* _hoops_GASA: _hoops_SR _hoops_RRP _hoops_IS _hoops_IGRC _hoops_IPS _hoops_RH _hoops_CPAP _hoops_RIIA _hoops_IIGR _hoops_SAHR _hoops_PCPCA'_hoops_SSRSS
			 * _hoops_SCH _hoops_PGGA _hoops_RPP _hoops_IIH _hoops_AAPR _hoops_IS _hoops_SHH _hoops_PCCP _hoops_IHCGP _hoops_CAIH _hoops_GAPA _hoops_HA _hoops_PPR
			 * _hoops_RH _hoops_AGCIP, _hoops_SR'_hoops_GHGP _hoops_AGCIP _hoops_RH _hoops_RHPH _hoops_AHAP */
			_hoops_CIPPI->geometry = HI_Copy_Geometry (dc->_hoops_RIGC, geometry);
			_hoops_CIPPI->segment = si->segment;
			_hoops_CIPPI->path = si->path;
			_hoops_CIPPI->single = true;
			_hoops_CIPPI->mask = si->mask;
			*_hoops_CSRSS = _hoops_CIPPI;
			_hoops_CSRSS = &_hoops_CIPPI->next;
		} while ((geometry = geometry->next) != null);
	} while ((si = si->next) != null);
}


local _hoops_PRGIP _hoops_GGASS (_hoops_HSIIP const *si)
{
	_hoops_PRGIP	_hoops_PGCHP = 0;
	do {
		_hoops_PGCHP |= si->nr->_hoops_RSGC->_hoops_PGCHP;
	} while ((si = si->next) != null);
	return _hoops_PGCHP;
}


GLOBAL_FUNCTION void HD_Standard_Draw_Overlay_List (
	Net_Rendition const &		nr) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_HSIIP const *		si;
	_hoops_PRGIP				_hoops_PGCHP = 0;
	_hoops_CRCP const *				_hoops_GRCIP = dc->_hoops_RRCIP;
	_hoops_HICS				_hoops_ARCIP = dc->path;

	dc->_hoops_CPGPR |= _hoops_GGARA;
	if ((si = dc->_hoops_CHPGR) != null) do {
		if (si->nr->_hoops_RSGC->_hoops_PGCHP && !_hoops_PGCHP) {
			_hoops_PRGIP		_hoops_RGASS = dc->_hoops_IPCI->mode;

			_hoops_PGCHP = _hoops_GGASS (si);
			_hoops_HGCGA (dc, "overlay callbacks", si->nr);

			dc->_hoops_IPCI->mode = 0;
			HD_Vanillify_Actions (_hoops_PGCHP, dc->_hoops_IPCI);
			dc->_hoops_IPCI->mode = _hoops_RGASS;
		}
		if (si->geometry) {
			dc->_hoops_RRCIP = si->segment;
			dc->path = si->path;
			_hoops_RPHPP (si->nr, si->geometry, si->mask, si->single);
		}
	} while ((si = si->next) != null);
	dc->_hoops_RRCIP = _hoops_GRCIP;
	dc->path = _hoops_ARCIP;
	if (_hoops_PGCHP)
		_hoops_HGSGA (dc, "overlay callbacks");

	/* _hoops_RPP _hoops_CSPH->_hoops_HCHCP == _hoops_ICHCP, _hoops_CSPH->_hoops_AGASS _hoops_CGH _hoops_PSHRR 
	 * _hoops_SHH _hoops_IRAP, _hoops_CR _hoops_SSIIP _hoops_HRGR _hoops_IHPPP _hoops_PSAP _hoops_GGR _hoops_PGASS.
	 * _hoops_CGP _hoops_SCH _hoops_HRGR _hoops_HGASS _hoops_PAR _hoops_IGASS, _hoops_HGRRA, _hoops_HHCI _hoops_IHCI
	 * _hoops_SGHC _hoops_PAH _hoops_RSRHR _hoops_RRH _hoops_CIPH _hoops_CIAA _hoops_RH _hoops_CCSHP _hoops_HIGR */
	HD_See_Whats_Hidden (nr);

	if (dc->_hoops_GPSS[dc->_hoops_IASS] != null)
		_hoops_SSGGR (dc);

	if (dc->_hoops_RPSS[dc->_hoops_IASS] != null) {
		HD_Draw_Deferred_3D_Geometry (dc->_hoops_RPSS[dc->_hoops_IASS], true);
		HD_Free_Deferred_3D_Geometry (dc->_hoops_RPSS[dc->_hoops_IASS]);
		dc->_hoops_RPSS[dc->_hoops_IASS] = null;
	}

	if (dc->_hoops_SHPGR == QMoves_XOR)
		_hoops_ISRSS (dc);

	HD_Free_Sprite_List (dc, &dc->_hoops_CHPGR);
}


GLOBAL_FUNCTION void HD_Standard_UnDraw_Overlay_List (
	Net_Rendition const &		nr) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_HSIIP const *		si;
	_hoops_CRCP const *				_hoops_GRCIP = dc->_hoops_RRCIP;
	_hoops_HICS				_hoops_ARCIP = dc->path;
	int							_hoops_IPHIP;

	if (!dc->_hoops_CRHGH)
		return;

	if (dc->_hoops_SHPGR != QMoves_XOR)
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_RECURSIVE_UPDATE,
					   "unexpected quick moves type in HD_Standard_UnDraw_Overlay_List");

	_hoops_IPHIP = dc->_hoops_CPGPR;
	dc->_hoops_CPGPR |= _hoops_GGARA;

	HD_Alternate_Hidden_Root (dc, _hoops_IHPGR);
	if ((si = dc->_hoops_CRHGH) != null) do {
		if (si->geometry) {
			dc->_hoops_RRCIP = si->segment;
			dc->path = si->path;
			_hoops_RPHPP (si->nr, si->geometry, si->mask, si->single);
		}
	} while ((si = si->next) != null);
	dc->_hoops_RRCIP = _hoops_GRCIP;
	dc->path = _hoops_ARCIP;

	/* _hoops_RPP _hoops_CSPH->_hoops_HCHCP == _hoops_ICHCP, _hoops_CSPH->_hoops_AGASS _hoops_CGH _hoops_PSHRR 
	 * _hoops_SHH _hoops_IRAP, _hoops_HIS _hoops_GHAP'_hoops_SPHAI _hoops_HAR _hoops_RCRR _hoops_RPP _hoops_RGR _hoops_HRGR _hoops_CPSA _hoops_HAHH */
	HD_See_Whats_Hidden (nr);
	HD_Alternate_Hidden_Root (dc, _hoops_IHPGR);
	HD_Free_Sprite_List (dc, &dc->_hoops_CRHGH);
	dc->_hoops_CPGPR = _hoops_IPHIP;
}


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
 * $Id: obf_tmp.txt 1.134 2010-10-22 22:37:22 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "please.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "task_queue.h"
#include "phedron.h"


GLOBAL_FUNCTION bool HD_Connect_Standard_Driver (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_GGAGR alter *				_hoops_GHRI,
	int							request,
	void						(*_hoops_SRGRH) (_hoops_APARR alter & _hoops_RRCI)) 
{
	UNREFERENCED(_hoops_RIGC);

	if (request == _hoops_GAGRH)
		return true;

	if (request != _hoops_RAGRH) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Connect Standard Driver");
		return false;
	}

	Display_Context *	dc;
	ZALLOC (dc, Display_Context);
	ZALLOC (dc->_hoops_IGGI, _hoops_HPRGH);
	ZALLOC (dc->_hoops_CAHGH, _hoops_HPRGH);

	_hoops_RCCA(_hoops_SHPSA)=HOOPS_WORLD->_hoops_SHPSA;
	_hoops_RCCA(_hoops_CIPSA)=HOOPS_WORLD->_hoops_CIPSA;
	_hoops_RCCA(_hoops_ISRGH)=HOOPS_WORLD->_hoops_ISRGH;

	CREATE_MUTEX (dc->_hoops_RASCA);

	dc->memory_pool = HI_Create_Memory_Pool(MPF_NONE);

	dc->_hoops_SPA = dc->_hoops_ISAGR = POOL_NEW(dc->memory_pool, _hoops_AAGSP)();

	dc->options.border = true;
	dc->options._hoops_HRSSP = true;
	dc->options._hoops_SRSSP = true;
	dc->options._hoops_ARPSR = _hoops_PGHRP;
	dc->options._hoops_RCPRP = 1.0f;
	dc->options._hoops_GSHSR = 1.0f;
	dc->options._hoops_SHSHA = 1.0f;
	dc->options._hoops_GSPRP = _hoops_CCPRP;
	dc->_hoops_PGCC._hoops_CHHSR = _hoops_SHHSR;
	dc->_hoops_PGCC.flags |= _hoops_GGISR;
	dc->_hoops_ARAIP = 4;
	dc->_hoops_SSGC = -1;

	for (int i=0; i<_hoops_CHSSP; i++)
		dc->_hoops_HRHPP[i]._hoops_ASRGR = &dc->_hoops_HRHPP[i].list;

	dc->_hoops_GPSIP._hoops_ASRGR = &dc->_hoops_GPSIP.list;

	dc->flags |= _hoops_RASS;
	dc->_hoops_RIHCP = &dc->_hoops_IHIIP[0];
	dc->_hoops_IHHCP = &dc->_hoops_CHPGR;

	_hoops_GHRI->_hoops_PPRPR = (void alter *)dc;
	dc->_hoops_GHRI = _hoops_GHRI;

	/* _hoops_HGCR _hoops_RH _hoops_RHPP _hoops_PGSI _hoops_PPR _hoops_PSCR _hoops_AACC _hoops_RH _hoops_CIS _hoops_IIGR _hoops_RGR */
	dc->_hoops_ACPGR = _hoops_APARR::Create(dc->memory_pool);
	dc->_hoops_IPCI = dc->_hoops_ACPGR;
	HD_Get_Actions (dc->_hoops_ACPGR, _hoops_SRGRH);
	_hoops_GHRI->connected_action = HD_Standard_Driver;

	return true;
}



local void _hoops_AAGRH (
	Display_Context const *		dc,
	_hoops_AIGPR *		_hoops_RIGC) {

	if (BIT (_hoops_RSPPR(_hoops_RIGC, flags), _hoops_GRSCA) ||
		BIT (_hoops_RIGC->flags, _hoops_RRSCA))
		return;

	/* _hoops_CPSA _hoops_HHSA _hoops_AIIAP _hoops_ARI */
	((_hoops_GGAGR alter *)dc->_hoops_GHRI)->owner->_hoops_ACIGP (HOOPS_WORLD->_hoops_GPPI + 1);

	if (BIT(dc->flags, _hoops_GIRIP)) {
		HD_Interrupt_Update(dc, true, true); /* _hoops_HAGIP _hoops_RH _hoops_SCGR _hoops_PAAP _hoops_IS _hoops_RRS */
		_hoops_APSRR(dc, "reset_update","", 0);
	}
	else if (_hoops_RIGC->_hoops_PAGRH == _hoops_HAGRH) {
		/* _hoops_GGR _hoops_PCCP _hoops_PAAP, _hoops_HIH _hoops_HAR _hoops_RGR _hoops_SAGHR _hoops_AIRI */
		_hoops_RIGC->_hoops_PAGRH = _hoops_IAGRH;
	}
	else {
		/* _hoops_HGCR _hoops_IRS _hoops_CCAH _hoops_PAAP _hoops_AIS */
		HI_Queue_Actor_Update(dc->_hoops_GHRI, false);
	}
}


GLOBAL_FUNCTION void HD_Force_Refresh (
	Display_Context const		*dc) {
	_hoops_CRCP const				*_hoops_SRCP = dc->_hoops_AAHSR;

	/* _hoops_IPCP _hoops_HSPR _hoops_HRGR _hoops_IRS _hoops_AH _hoops_HGIHR _hoops_IH _hoops_CAGRH 599 */
	if (BIT (_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR) ||
		BIT (dc->_hoops_GHRI->_hoops_RRHH, _hoops_HGAGR)) 
		return; /* _hoops_SRCH _hoops_AAPA-_hoops_PAPA _hoops_IRISR _hoops_HCPH! */

	_hoops_AIGPR * _hoops_RIGC = dc->_hoops_RIGC;
	if (!_hoops_RIGC)
		_hoops_IIRIR(_hoops_RIGC);

	/* _hoops_HPGGR _hoops_RH _hoops_AARPR */
	_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_SCCCA);

	_hoops_AAGRH (dc, _hoops_RIGC);
}


GLOBAL_FUNCTION void HD_Force_Partial_Refresh (
	Display_Context const *		dc,
	int							left,
	int							right,
	int							bottom,
	int							top) {
	_hoops_CRCP const *				_hoops_SRCP = dc->_hoops_AAHSR;

	/* _hoops_IPCP _hoops_HSPR _hoops_HRGR _hoops_IRS _hoops_AH _hoops_HGIHR _hoops_IH _hoops_CAGRH 599 */
	if (BIT (_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR) ||
		BIT (dc->_hoops_GHRI->_hoops_RRHH, _hoops_HGAGR)) 
		return; /* _hoops_SRCH _hoops_AAPA-_hoops_PAPA _hoops_IRISR _hoops_HCPH! */

	_hoops_PACIR	scope;
	scope.left = left / (float)dc->current._hoops_PRPSR.x * 2.0f - 1.0f;
	scope.bottom = bottom / (float)dc->current._hoops_PRPSR.y * 2.0f - 1.0f;
	scope.right = ((float)right + 0.999f) / (float)dc->current._hoops_PRPSR.x * 2.0f - 1.0f;
	scope.top = ((float)top + 0.999f) / (float)dc->current._hoops_PRPSR.y * 2.0f - 1.0f;

	/* _hoops_ARRPA _hoops_ISPR */
	scope._hoops_PGPGP(_hoops_SGPGP::_hoops_GRPGP);

	if (scope.left > scope.right || scope.bottom > scope.top) 
		return;

	_hoops_AIGPR * _hoops_RIGC = dc->_hoops_RIGC;
	if (!_hoops_RIGC)
		_hoops_IIRIR(_hoops_RIGC);

	/* _hoops_AA _hoops_SCH */
	HI_Propagate_Scoped_Activity (_hoops_RIGC,(_hoops_SIHIR alter *)_hoops_SRCP,
								  _hoops_SCCCA, &scope);

	_hoops_AAGRH (dc, _hoops_RIGC);
}




GLOBAL_FUNCTION void HD_Resize_Subscreen (
	Display_Context const *		_hoops_SAGRH,
	bool						_hoops_PPIPP,
	int							_hoops_GPGRH,
	int							_hoops_RPGRH,
	int							_hoops_APGRH,
	int							_hoops_PPGRH) {
	_hoops_PACIR			_hoops_HPGRH;
	_hoops_CRCP const *				_hoops_SRCP = _hoops_SAGRH->_hoops_AAHSR;
	Int_XY						_hoops_CIGRR,
								_hoops_CGCGR;
	int							center;
	Display_Context alter *		dc = (Display_Context alter *)_hoops_SAGRH;
	int							_hoops_SGSCA = dc->_hoops_RIGC->flags;

	if (_hoops_GPGRH == dc->_hoops_RCGA.left &&
		_hoops_RPGRH == dc->_hoops_RCGA.right &&
		_hoops_APGRH == dc->_hoops_RCGA.bottom &&
		_hoops_PPGRH == dc->_hoops_RCGA.top) return; /* _hoops_PSP _hoops_RIHRR _hoops_AGRP */

	/* _hoops_IPCP _hoops_HSPR _hoops_HRGR _hoops_IRS _hoops_AH _hoops_HGIHR _hoops_IH _hoops_CAGRH 599 */
	if (BIT (_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR) ||
		BIT (dc->_hoops_GHRI->_hoops_RRHH, _hoops_HGAGR)) 
		return; /* _hoops_SRCH _hoops_AAPA-_hoops_PAPA _hoops_IRISR _hoops_HCPH! */

	if (dc->_hoops_SHCIP)
		HD_Flush_Octree_Queries (dc->_hoops_SHCIP, dc->_hoops_AAHSR);

	if (_hoops_PPIPP) {
		dc->_hoops_RCGA.left = _hoops_GPGRH;
		dc->_hoops_RCGA.right = _hoops_RPGRH;
		dc->_hoops_RCGA.bottom = _hoops_APGRH;
		dc->_hoops_RCGA.top = _hoops_PPGRH;
	}

	_hoops_CGCGR.x = _hoops_RPGRH - _hoops_GPGRH + 1;
	_hoops_CGCGR.y = _hoops_PPGRH - _hoops_APGRH + 1;
	_hoops_CIGRR.x = dc->_hoops_RHPGA.right - dc->_hoops_RHPGA.left + 1;
	_hoops_CIGRR.y = dc->_hoops_RHPGA.top - dc->_hoops_RHPGA.bottom + 1;

	if (!dc->options._hoops_RASSP) {
		/* _hoops_PCHIA _hoops_CPS */

		_hoops_GPGRH = dc->_hoops_RHPGA.left;
		_hoops_RPGRH = dc->_hoops_RHPGA.right;
		_hoops_APGRH = dc->_hoops_RHPGA.bottom;
		_hoops_PPGRH = dc->_hoops_RHPGA.top;
	}
	else if (!dc->options._hoops_AASSP) {
		/* _hoops_PCHIA _hoops_RH _hoops_SAAA */

		if (_hoops_CGCGR.x != _hoops_CIGRR.x) {
			center = (_hoops_RPGRH + _hoops_GPGRH) / 2;
			_hoops_GPGRH = center - _hoops_CIGRR.x / 2;
			_hoops_RPGRH = center + _hoops_CIGRR.x / 2;
			if (_hoops_CIGRR.x % 2 == 0) ++_hoops_GPGRH;
		}

		if (_hoops_CGCGR.y != _hoops_CIGRR.y) {
			center = (_hoops_PPGRH + _hoops_APGRH) / 2;
			_hoops_APGRH = center - _hoops_CIGRR.y / 2;
			_hoops_PPGRH = center + _hoops_CIGRR.y / 2;
			if (_hoops_CIGRR.y % 2 == 0) ++_hoops_APGRH;
		}
	}
	else if (!dc->options._hoops_PASSP &&
			 (_hoops_CGCGR.x != _hoops_CIGRR.x || _hoops_CGCGR.y != _hoops_CIGRR.y)) {
		if (BIT(dc->_hoops_PGCC.flags, _hoops_SAPGH)) 
			{ /* _hoops_IPGRH, _hoops_IHRI! */}
		else {
			float	dx, _hoops_CRRAR;

			/* _hoops_SAAA _hoops_PIHA _hoops_SHH _hoops_GHRHR -- _hoops_IIS _hoops_RH _hoops_RRI _hoops_CPGRH _hoops_SPR _hoops_SPGRH! */

			dx = (float)_hoops_CGCGR.x / (float)_hoops_CIGRR.x;
			if (dx < 1.0f) dx = 1.0f/dx;

			_hoops_CRRAR = (float)_hoops_CGCGR.y / (float)_hoops_CIGRR.y;
			if (_hoops_CRRAR < 1.0f) _hoops_CRRAR = 1.0f/_hoops_CRRAR;

			if (dx < _hoops_CRRAR) {
				/* _hoops_HAPC _hoops_HRGR _hoops_RRI _hoops_CPGRH - _hoops_IRHH _hoops_SISR _hoops_PSSP */

				_hoops_CGCGR.x = (int)(_hoops_CGCGR.y * (_hoops_CIGRR.x / (float)_hoops_CIGRR.y));
				center = (_hoops_RPGRH + _hoops_GPGRH) / 2;
				_hoops_GPGRH = center - _hoops_CGCGR.x / 2;
				_hoops_RPGRH = center + _hoops_CGCGR.x / 2;

				if (_hoops_CGCGR.x % 2 != 0) ++_hoops_RPGRH;
			}
			else {
				/* _hoops_SISR _hoops_HRGR _hoops_RRI _hoops_CPGRH - _hoops_IRHH _hoops_HAPC _hoops_PSSP */

				_hoops_CGCGR.y = (int)(_hoops_CGCGR.x * (_hoops_CIGRR.y / (float)_hoops_CIGRR.x));
				center = (_hoops_PPGRH + _hoops_APGRH) / 2;
				_hoops_APGRH = center - _hoops_CGCGR.y / 2;
				_hoops_PPGRH = center + _hoops_CGCGR.y / 2;
				if (_hoops_CGCGR.y % 2 != 0) ++_hoops_PPGRH;
			}
		}
	}


	/* _hoops_GHGRH *_hoops_GCIS* _hoops_RH _hoops_HGPC, _hoops_RPP _hoops_GII, _hoops_RHGRH _hoops_ISAP _hoops_SHS _hoops_RHAP -
	 * _hoops_ASSS _hoops_IH _hoops_RH _hoops_HGPC.
	 */
	_hoops_GPGRH -= dc->current.border.left;
	_hoops_RPGRH += dc->current.border.right;
	_hoops_APGRH -= dc->current.border.bottom;
	_hoops_PPGRH += dc->current.border.top;

	_hoops_HPGRH.left = 2.0f * (_hoops_GPGRH - dc->_hoops_PGCC.extent.left) /
				   (dc->_hoops_PGCC.extent.right - dc->_hoops_PGCC.extent.left) -
				   1.0f;

	_hoops_HPGRH.right = 2.0f * (_hoops_RPGRH - dc->_hoops_PGCC.extent.left) /
					(dc->_hoops_PGCC.extent.right - dc->_hoops_PGCC.extent.left) -
					1.0f;

	_hoops_HPGRH.bottom = 2.0f * (_hoops_APGRH - dc->_hoops_PGCC.extent.bottom)/
					 (dc->_hoops_PGCC.extent.top - dc->_hoops_PGCC.extent.bottom) -
					 1.0f;

	_hoops_HPGRH.top = 2.0f * (_hoops_PPGRH - dc->_hoops_PGCC.extent.bottom) /
				  (dc->_hoops_PGCC.extent.top - dc->_hoops_PGCC.extent.bottom) -
				  1.0f;

	/* _hoops_RGPA _hoops_IRS _hoops_AHGRH, _hoops_HIS _hoops_SGS _hoops_CGPR _hoops_RH _hoops_PHGRH'_hoops_GRI _hoops_IHPS _hoops_GGR _hoops_HHGRH, _hoops_SR
	 * _hoops_PPPPR'_hoops_RA _hoops_SHH _hoops_IHGRH _hoops_CHGRH _hoops_IRS _hoops_SHSC _hoops_AIR _hoops_ISHP.
	 */
	_hoops_HPGRH.left += 0.1f/dc->_hoops_PGCC._hoops_PRPSR.x;
	_hoops_HPGRH.right += 0.1f/dc->_hoops_PGCC._hoops_PRPSR.x;
	_hoops_HPGRH.bottom += 0.1f/dc->_hoops_PGCC._hoops_PRPSR.y;
	_hoops_HPGRH.top += 0.1f/dc->_hoops_PGCC._hoops_PRPSR.y;


	/* _hoops_ARRPA _hoops_ISPR */
	if (_hoops_HPGRH.left > _hoops_HPGRH.right) 
		_hoops_HPGRH.left = _hoops_HPGRH.right;
	if (_hoops_HPGRH.bottom > _hoops_HPGRH.top) 
		_hoops_HPGRH.bottom = _hoops_HPGRH.top;


	/* _hoops_CGP _hoops_RH _hoops_HCSP _hoops_SSCP _hoops_HGAS, _hoops_ARP _hoops_RH _hoops_CCAH _hoops_PIRA _hoops_SHGRH */
	if (_hoops_GPGRH+dc->current.border.left != dc->_hoops_RCGA.left ||
		_hoops_RPGRH-dc->current.border.right != dc->_hoops_RCGA.right ||
		_hoops_APGRH+dc->current.border.bottom != dc->_hoops_RCGA.bottom ||
		_hoops_PPGRH-dc->current.border.top != dc->_hoops_RCGA.top ||

		Abs (_hoops_HPGRH.left - dc->options._hoops_HCPRP.left) > 0.0001f ||
		Abs (_hoops_HPGRH.right - dc->options._hoops_HCPRP.right) > 0.0001f ||
		Abs (_hoops_HPGRH.bottom - dc->options._hoops_HCPRP.bottom) > 0.0001f ||
		Abs (_hoops_HPGRH.top - dc->options._hoops_HCPRP.top) > 0.0001f) {

		Attribute			*_hoops_HPHCR;

		if ((_hoops_HPHCR = dc->_hoops_AAHSR->_hoops_IPPGR) != null) do {
			if (_hoops_HPHCR->type >= HK_DRIVER_OPTIONS) {
				if (_hoops_HPHCR->type > HK_DRIVER_OPTIONS)
					_hoops_HPHCR = null;	
				break;
			}
		} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);

		{
			_hoops_GAPIR alter * _hoops_GGGRH = (_hoops_GAPIR alter *)_hoops_HPHCR;

			if (_hoops_GGGRH == null) {	// _hoops_GIGRH-_hoops_ISHP _hoops_RIGRH
				Attribute **	_hoops_ASRGR = (Attribute **)&dc->_hoops_AAHSR->_hoops_IPPGR;

				while (*_hoops_ASRGR != null && (*_hoops_ASRGR)->type < HK_DRIVER_OPTIONS)
					_hoops_ASRGR = &(*_hoops_ASRGR)->next;

				ZALLOC (_hoops_GGGRH, _hoops_GAPIR);
				_hoops_GGGRH->type = HK_DRIVER_OPTIONS;
				_hoops_GGGRH->_hoops_HIHI = 1;
				_hoops_GGGRH->owner = (_hoops_CRCP *)dc->_hoops_AAHSR;

				_hoops_GGGRH->backlink = _hoops_ASRGR;
				if ((_hoops_GGGRH->next = *_hoops_ASRGR) != null)
					(*_hoops_ASRGR)->backlink = &_hoops_GGGRH->next;
				*_hoops_ASRGR = _hoops_GGGRH;

				_hoops_GGGRH->_hoops_CPGPR = _hoops_HCHPA;
			}

			_hoops_GGGRH->_hoops_IAICA |= _hoops_RGPRP;
			_hoops_GGGRH->_hoops_HCARP |= _hoops_RGPRP;

			_hoops_GGGRH->_hoops_CPGPR |= _hoops_CAHRA;
			_hoops_GGGRH->_hoops_HPHRP = false;
			_hoops_GGGRH->_hoops_HCPRP.left = _hoops_HPGRH.left;
			_hoops_GGGRH->_hoops_HCPRP.right = _hoops_HPGRH.right;
			_hoops_GGGRH->_hoops_HCPRP.bottom = _hoops_HPGRH.bottom;
			_hoops_GGGRH->_hoops_HCPRP.top = _hoops_HPGRH.top;
		}
	}
	
	/* _hoops_PRGI _hoops_RPP _hoops_RH _hoops_HCSP _hoops_SARS'_hoops_RA _hoops_AGRP (_hoops_SCRPR, _hoops_PSP _hoops_AIGRH), _hoops_IRHH
	 * _hoops_RCRR _hoops_PIGRH _hoops_SAGGR _hoops_IS _hoops_RHCA _hoops_AHCA _hoops_CGSI
	 */
	
	dc->_hoops_GHRI->owner->_hoops_ACIGP (HOOPS_WORLD->_hoops_GPPI + 1);

	dc->_hoops_RIGC->flags &= ~_hoops_RRSCA; 
	_hoops_SASIR (dc->_hoops_RIGC, _hoops_SRCP, _hoops_HGSCA|_hoops_RSCCA|_hoops_CCPGP);
	dc->_hoops_RIGC->flags = _hoops_SGSCA;

	if (BIT(dc->flags, _hoops_GIRIP)) {
		HD_Interrupt_Update(dc, true, true); /* _hoops_HAGIP _hoops_RH _hoops_SCGR _hoops_PAAP, _hoops_RPP _hoops_GII, _hoops_IS _hoops_RRS */
		_hoops_APSRR(dc, "HD_Resize_Subscreen","", 0);
	}
	else 
		HI_Queue_Actor_Update(dc->_hoops_GHRI, false);

}



GLOBAL_FUNCTION void HD_Allow_For_Border (
	Display_Context alter	*dc,
	int							_hoops_HIGRH,
	int							_hoops_IIGRH,
	int							_hoops_CIGRH,
	int							_hoops_SIGRH) {

	/* _hoops_HGI _hoops_HRGR _hoops_PIGS _hoops_RAS _hoops_RH _hoops_CSCS _hoops_SCGR _hoops_SISS _hoops_ARP-_hoops_GH _hoops_IS _hoops_IRHH
	   _hoops_RCRR _hoops_SGS _hoops_IIH'_hoops_GRI _hoops_RAPR _hoops_SHPR _hoops_GC _hoops_IS _hoops_SIHRR _hoops_PCCP _hoops_IHH _hoops_HGPC
	   _hoops_AARI _hoops_RH _hoops_CRIPR _hoops_RPPS.
	*/


	/* _hoops_HGAPR _hoops_GCGRH _hoops_RCGRH _hoops_ISCC _hoops_ACGRH _hoops_PGGA _hoops_SCH _hoops_CRHPR _hoops_SCH _hoops_PCGRH _hoops_IS
	 * _hoops_CISA _hoops_RH _hoops_SHPR _hoops_GGR _hoops_IRS "_hoops_PSP _hoops_GAPGH _hoops_HCGRH" _hoops_ICGRH.
	 */
#	if 0
	/* _hoops_RPP _hoops_HAHH, _hoops_HHSA _hoops_SCH _hoops_IS _hoops_SHH _hoops_IRS _hoops_CCGRH _hoops_AGRP */
	if (!dc->options._hoops_PASSP) {
		float			_hoops_SCGRH,
								_hoops_GSGRH;
		int				tmp;

		/* _hoops_IPHR _hoops_GGR _hoops_CSHCR _hoops_IIGR _hoops_SPCR _hoops_AIR _hoops_PSPA */

		_hoops_SCGRH = _hoops_HIGRH + _hoops_IIGRH;
		_hoops_GSGRH = (_hoops_CIGRH + _hoops_SIGRH) / dc->current._hoops_AGRS;

		if (_hoops_SCGRH > _hoops_GSGRH) {
			tmp = (_hoops_SCGRH - _hoops_GSGRH)*0.5f * dc->current._hoops_AGRS;
			_hoops_CIGRH += tmp;
			_hoops_SIGRH += tmp;
		}
		else if (_hoops_GSGRH > _hoops_SCGRH) {
			tmp = (_hoops_GSGRH - _hoops_SCGRH)*0.5f;
			_hoops_HIGRH += tmp;
			_hoops_IIGRH += tmp;
		}
	}
#	endif

	/* _hoops_PRIA _hoops_RH _hoops_RGGHR, _hoops_PPR _hoops_IIS _hoops_HHGRH _hoops_HIISR _hoops_CCA _hoops_SCH */
	dc->current.border.left = _hoops_HIGRH;
	dc->current.border.right = _hoops_IIGRH;
	dc->current.border.bottom = _hoops_CIGRH;
	dc->current.border.top = _hoops_SIGRH;
}



GLOBAL_FUNCTION Display_Context * HD_Find_DC_From_WID (
	POINTER_SIZED_INT					_hoops_RSGRH) 
{
	_hoops_GGAGR const		*_hoops_GHRI = HOOPS_WORLD->_hoops_CISHA;

	if ((_hoops_GHRI = HOOPS_WORLD->_hoops_CISHA) != null) {

		do if (ALLBITS (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA|_hoops_RCSHA)) {
			Display_Context alter *dc;

			dc = (Display_Context alter *)_hoops_GHRI->_hoops_PPRPR;

			if (dc != null &&
				(dc->current._hoops_RAPGH == _hoops_RSGRH ||
				dc->current._hoops_PAPGH == _hoops_RSGRH))
				return dc;
		}
		_hoops_RGGA ((_hoops_GHRI = _hoops_GHRI->_hoops_CISHA) == null);
	}

	return null;
}

#include "span.h"

GLOBAL_FUNCTION int HD_Find_Dither_Pattern (
	Net_Rendition const &	nr,
	RGBAS32 const *			target,
	_hoops_GARSR alter *		_hoops_ASGRH,
	int alter *				_hoops_AHHIR) 
{
	Display_Context const *	dc = nr->_hoops_SRA;
	_hoops_GARSR alter *		_hoops_PSGRH = _hoops_ASGRH;
	_hoops_GHGCR				result;


	_hoops_SGGCR const *	_hoops_HAP = &dc->_hoops_AGPGH;
	_hoops_SGGCR const *	_hoops_SPGCR = &dc->_hoops_HHGCR;

	/*
	 * _hoops_CGP _hoops_HSGRH, _hoops_SR _hoops_CGH _hoops_SRSHR _hoops_RH _hoops_HISGR _hoops_HAIR, _hoops_PGAP _hoops_HRGR _hoops_RH "_hoops_ISGRH" _hoops_HAIR.
	 * _hoops_HSRR _hoops_CSGRH, _hoops_SR _hoops_IIIAR _hoops_GAPA _hoops_RH _hoops_SSGRH _hoops_PPR _hoops_GGRRH _hoops_IIGR _hoops_RH _hoops_PIRA,
	 * _hoops_PGAP _hoops_RGRRH _hoops_IRS "_hoops_CHGRH" _hoops_HAIR _hoops_HRGR _hoops_IS _hoops_SHH _hoops_IGI _hoops_GAR _hoops_RH _hoops_AIRA.
	 */
	if (BIT (nr->_hoops_IRR->_hoops_SIRAP, Quantization_THRESHOLD)) {
		result.r.number = (target->r * _hoops_HAP->r) << 8;
		result.g.number = (target->g * _hoops_HAP->g) << 8;
		result.b.number = (target->b * _hoops_HAP->b) << 8;

		_hoops_PSGRH[0] = dc->_hoops_RHGCR +
						result.r._hoops_CAGCR._hoops_SAGCR * _hoops_SPGCR->r +
						result.g._hoops_CAGCR._hoops_SAGCR * _hoops_SPGCR->g +
						result.b._hoops_CAGCR._hoops_SAGCR * _hoops_SPGCR->b;

		return 1;
	}


	/*
	 * _hoops_IPCP _hoops_HSPR _hoops_RRGR _hoops_HRGR _hoops_AGRRH _hoops_AAR _hoops_GPP _hoops_RH _hoops_PGRRH _hoops_RIGR
	 * _hoops_IHGS _hoops_IRS _hoops_IISGR _hoops_SIRRR _hoops_IAPR _hoops_HGRRH, _hoops_IGRRH, _hoops_CGRRH.	 _hoops_HHIGR _hoops_SGRRH _hoops_RH
	 * _hoops_SGCCP _hoops_SGS
	 *			_hoops_PGRRH ((_hoops_GRRRH+_hoops_RRRRH), (_hoops_ARRRH+_hoops_PRRRH), (_hoops_HRRRH+_hoops_RRCCP)) + _hoops_GHGP
	 * _hoops_HRGR _hoops_RCGRA _hoops_IS
	 *			_hoops_PGRRH (_hoops_GRRRH, _hoops_ARRRH, _hoops_HRRRH) + _hoops_PGRRH (_hoops_RRRRH, _hoops_PRRRH, _hoops_RRCCP) + _hoops_GHGP
	 * _hoops_CGP _hoops_RGR _hoops_HRGR _hoops_IHPR, _hoops_PSCR _hoops_SR _hoops_PAH _hoops_GIAH _hoops_RH _hoops_HGGAR _hoops_IIGR
	 * _hoops_RH _hoops_HAIR _hoops_PSPI, _hoops_PPR _hoops_GSRS _hoops_RGAR _hoops_IRS _hoops_AIRA _hoops_CIHA _hoops_PPR
	 * _hoops_CPCHR _hoops_IAHP.	 _hoops_HGI _hoops_HACAR _hoops_GPP _hoops_IGRIR _hoops_PPR _hoops_IRRRH.
	 */
	else {
		_hoops_CRRRH			_hoops_GIGCR, _hoops_RIGCR, d3;		/* _hoops_SICIR */
		int						_hoops_AIGCR, _hoops_PIGCR, _hoops_HIGCR;		/* _hoops_IIGCR _hoops_CIGCR */
		int						color;			/* _hoops_GRAHA _hoops_HAIR */

		/*
		 * _hoops_IPCP _hoops_IGHP _hoops_HAIR _hoops_HRGR _hoops_RH _hoops_CHGRH _hoops_HAIR, _hoops_PGAP _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_IAIAR _hoops_ARRS
		 */
		result.r.number = (target->r * (_hoops_HAP->r - 1)) << 8;
		result.g.number = (target->g * (_hoops_HAP->g - 1)) << 8;
		result.b.number = (target->b * (_hoops_HAP->b - 1)) << 8;

		_hoops_PSGRH[0] = dc->_hoops_RHGCR +
						result.r._hoops_CAGCR._hoops_SAGCR * _hoops_SPGCR->r +
						result.g._hoops_CAGCR._hoops_SAGCR * _hoops_SPGCR->g +
						result.b._hoops_CAGCR._hoops_SAGCR * _hoops_SPGCR->b;

#define _hoops_SIGCR(_hoops_ICIPR, _hoops_CCIPR, _hoops_GCGCR) do {										\
		_hoops_GIGCR._hoops_CAGCR._hoops_SAGCR = _hoops_RIGCR._hoops_CAGCR._hoops_SAGCR = d3._hoops_CAGCR._hoops_SAGCR = 0;		\
		_hoops_GIGCR._hoops_CAGCR._hoops_RCGCR = result._hoops_ICIPR._hoops_CAGCR._hoops_RCGCR;					\
		_hoops_RIGCR._hoops_CAGCR._hoops_RCGCR = result._hoops_CCIPR._hoops_CAGCR._hoops_RCGCR;					\
		d3._hoops_CAGCR._hoops_RCGCR = result._hoops_GCGCR._hoops_CAGCR._hoops_RCGCR;					\
		_hoops_AIGCR = _hoops_SPGCR->_hoops_ICIPR;											\
		_hoops_PIGCR = _hoops_SPGCR->_hoops_CCIPR;											\
		_hoops_HIGCR = _hoops_SPGCR->_hoops_GCGCR;} while (0)

		if (result.r._hoops_CAGCR._hoops_RCGCR >= result.g._hoops_CAGCR._hoops_RCGCR) {
			if (result.g._hoops_CAGCR._hoops_RCGCR >= result.b._hoops_CAGCR._hoops_RCGCR)
				_hoops_SIGCR (r, g, b);
			else if (result.r._hoops_CAGCR._hoops_RCGCR >= result.b._hoops_CAGCR._hoops_RCGCR)
				_hoops_SIGCR (r, b, g);
			else
				_hoops_SIGCR (b, r, g);
		}
		else {
			if (result.r._hoops_CAGCR._hoops_RCGCR >= result.b._hoops_CAGCR._hoops_RCGCR)
				_hoops_SIGCR (g, r, b);
			else if (result.g._hoops_CAGCR._hoops_RCGCR >= result.b._hoops_CAGCR._hoops_RCGCR)
				_hoops_SIGCR (g, b, r);
			else
				_hoops_SIGCR (b, g, r);
		}

		/*
		 * _hoops_RHRPA _hoops_GRR _hoops_HHSPR, _hoops_IHIS _hoops_GGR _hoops_RH _hoops_HAGA _hoops_IIGR _hoops_ISHHR _hoops_ASRHA
		 * _hoops_ASC _hoops_SRRRH _hoops_IHSH _hoops_GARRH, _hoops_HIH _hoops_CR _hoops_RARRH _hoops_HRGR _hoops_IRS _hoops_RIIR
		 * _hoops_IIGR 2, _hoops_ICRP _hoops_AARRH _hoops_GRS _hoops_HIHP _hoops_RH _hoops_PHHSR _hoops_CRGR _hoops_IRS _hoops_PARRH.
		 */
		_hoops_GIGCR.number *= _hoops_AHRSP;
		if (_hoops_GIGCR._hoops_CAGCR._hoops_SAGCR == 0) return 1;  /* _hoops_HARRH - _hoops_IARRH + 1 */
		_hoops_AHHIR[0] = _hoops_CPRSP + _hoops_GIGCR._hoops_CAGCR._hoops_SAGCR;
		color = _hoops_PSGRH[0] + _hoops_AIGCR;

		/* _hoops_PPRSP: _hoops_SR _hoops_HS _hoops_HPGR _hoops_CHGC _hoops_PGCR _hoops_HARRH, _hoops_CCA _hoops_SPR _hoops_CARRH _hoops_HSGP */

		_hoops_RIGCR.number *= _hoops_AHRSP;
		if (_hoops_RIGCR._hoops_CAGCR._hoops_SAGCR == 0) {
			_hoops_PSGRH[1] = color;
			return 2; /* _hoops_HARRH - _hoops_IARRH + 2 */
		}
		if (_hoops_GIGCR._hoops_CAGCR._hoops_SAGCR != _hoops_RIGCR._hoops_CAGCR._hoops_SAGCR) {
			_hoops_PSGRH[1] = color;
			++_hoops_PSGRH;
			++_hoops_AHHIR;
			_hoops_AHHIR[0] = _hoops_CPRSP + _hoops_RIGCR._hoops_CAGCR._hoops_SAGCR;
		}
		color += _hoops_PIGCR;

		d3.number *= _hoops_AHRSP;
		if (d3._hoops_CAGCR._hoops_SAGCR == 0) {
			_hoops_PSGRH[1] = color;
			return _hoops_PSGRH - _hoops_ASGRH + 2;
		}
		if (_hoops_RIGCR._hoops_CAGCR._hoops_SAGCR != d3._hoops_CAGCR._hoops_SAGCR) {
			_hoops_PSGRH[1] = color;
			++_hoops_PSGRH;
			++_hoops_AHHIR;
			_hoops_AHHIR[0] = _hoops_CPRSP + d3._hoops_CAGCR._hoops_SAGCR;
		}

		_hoops_PSGRH[1] = color + _hoops_HIGCR;
		return _hoops_PSGRH - _hoops_ASGRH + 2;
	}
}


/* _hoops_RGR _hoops_API _hoops_HRGR _hoops_IPIH _hoops_RGAR _hoops_IGI _hoops_IH _hoops_PHSPR _hoops_AH _hoops_HCCGR,
** _hoops_HGPP _hoops_GAR _hoops_CCGI _hoops_PRHI _hoops_RHIR _hoops_PGHGR
*/
GLOBAL_FUNCTION void HD_Compute_One_World_Plane (
	_hoops_SGCC const &	_hoops_HSGA,
	Vector const *				normal,
	Point const *				point,
	_hoops_ARPA alter *				plane) {

	if (!ANYBIT (_hoops_HSGA->data._hoops_RAGR, _hoops_CICH)) {
		/* _hoops_SCH'_hoops_GRI _hoops_PIHGR */
		plane->a = normal->x;
		plane->b = normal->y;
		plane->c = normal->z;
		plane->d = -(plane->a * point->x +
					 plane->b * point->y +
					 plane->c * point->z);
	}
	else {
		_hoops_RPRA const *		_hoops_CRIPA = _hoops_HSGA->_hoops_PPRA()->data.elements;
		_hoops_ARPA					_hoops_SARRH;

		/* _hoops_SRSGR _hoops_GH _hoops_PCCP _hoops_CARA-_hoops_GC _hoops_IPPA */
		_hoops_SARRH.a = normal->x;
		_hoops_SARRH.b = normal->y;
		_hoops_SARRH.c = normal->z;
		_hoops_SARRH.d = -(_hoops_SARRH.a * point->x +
					  _hoops_SARRH.b * point->y +
					  _hoops_SARRH.c * point->z);

		/* _hoops_HIHP _hoops_SGS _hoops_IPPA */
		/* "_hoops_IRSIR _hoops_HIHP _hoops_GAR _hoops_GPRRH . _hoops_HAICR" - _hoops_RPRRH & _hoops_APRRH */
		/* _hoops_RH _hoops_IAPGR-_hoops_GGSR _hoops_AIRP _hoops_CHR _hoops_HSSPR _hoops_IS _hoops_SHH _hoops_AHHR _hoops_GGR _hoops_IRS _hoops_IRISR 4x3 */

		plane->a = _hoops_CRIPA[0][0] * _hoops_SARRH.a +
				   _hoops_CRIPA[0][1] * _hoops_SARRH.b +
				   _hoops_CRIPA[0][2] * _hoops_SARRH.c /* +
				   _hoops_PPRRH[0][3] * _hoops_HPRRH._hoops_GHGP */;

		plane->b = _hoops_CRIPA[1][0] * _hoops_SARRH.a +
				   _hoops_CRIPA[1][1] * _hoops_SARRH.b +
				   _hoops_CRIPA[1][2] * _hoops_SARRH.c /* +
				   _hoops_PPRRH[1][3] * _hoops_HPRRH._hoops_GHGP */;

		plane->c = _hoops_CRIPA[2][0] * _hoops_SARRH.a +
				   _hoops_CRIPA[2][1] * _hoops_SARRH.b +
				   _hoops_CRIPA[2][2] * _hoops_SARRH.c /* +
				   _hoops_PPRRH[2][3] * _hoops_HPRRH._hoops_GHGP */;

		plane->d = _hoops_CRIPA[3][0] * _hoops_SARRH.a +
				   _hoops_CRIPA[3][1] * _hoops_SARRH.b +
				   _hoops_CRIPA[3][2] * _hoops_SARRH.c +
				   _hoops_CRIPA[3][3] * _hoops_SARRH.d;

		(void)HI_Normalize_Plane (plane);
	}
}



/*
 * _hoops_AHGHR _hoops_AARPR _hoops_RSSA _hoops_PPR _hoops_ASGA, _hoops_GRAS _hoops_GHC _hoops_HPGR _hoops_GRR _hoops_HSP _hoops_GGR _hoops_GSSP
 * _hoops_PCRR (_hoops_SHCAR, _hoops_RAS _hoops_PRGIA).
 *
 * (_hoops_IPRRH _hoops_RH _hoops_AARPR _hoops_RSSA _hoops_GGR _hoops_CPRRH _hoops_IS _hoops_RH _hoops_RSSI _hoops_GCA _hoops_SPRRH
 *	_hoops_RH _hoops_AARPR _hoops_IPPHR.)
 */

GLOBAL_FUNCTION void HD_Compute_World_Face_Planes (
	Net_Rendition const &		nr,
	Polyhedron const *			_hoops_IPRI,
	_hoops_ARPA alter *				planes) {
	int							count = _hoops_IPRI->face_count;
	_hoops_ARPA const *				normals = _hoops_IPRI->local_face_attributes.normals;
	_hoops_SGCC const &	_hoops_HSGA = nr->transform_rendition->_hoops_IPH;

	if (!ANYBIT (_hoops_HSGA->data._hoops_RAGR, _hoops_CICH)) {
		_hoops_AIGA (normals, count, _hoops_ARPA, planes);
	}
	else {
		_hoops_RPRA const *		_hoops_CRIPA = _hoops_HSGA->_hoops_PPRA()->data.elements;

		while (count-- > 0) {
			/* _hoops_HIHP _hoops_GRR _hoops_IPPA */
			/* "_hoops_IRSIR _hoops_HIHP _hoops_GAR _hoops_GPRRH . _hoops_HAICR" - _hoops_RPRRH & _hoops_APRRH */
			/* _hoops_RH _hoops_IAPGR-_hoops_GGSR _hoops_AIRP _hoops_CHR _hoops_HSSPR _hoops_IS _hoops_SHH _hoops_AHHR _hoops_GGR _hoops_IRS _hoops_IRISR 4x3 */

			planes->a = _hoops_CRIPA[0][0] * normals->a +
						_hoops_CRIPA[0][1] * normals->b +
						_hoops_CRIPA[0][2] * normals->c /* +
						_hoops_PPRRH[0][3] * _hoops_ASGA->_hoops_GHGP */;

			planes->b = _hoops_CRIPA[1][0] * normals->a +
						_hoops_CRIPA[1][1] * normals->b +
						_hoops_CRIPA[1][2] * normals->c /* +
						_hoops_PPRRH[1][3] * _hoops_ASGA->_hoops_GHGP */;

			planes->c = _hoops_CRIPA[2][0] * normals->a +
						_hoops_CRIPA[2][1] * normals->b +
						_hoops_CRIPA[2][2] * normals->c /* +
						_hoops_PPRRH[2][3] * _hoops_ASGA->_hoops_GHGP */;

			planes->d = _hoops_CRIPA[3][0] * normals->a +
						_hoops_CRIPA[3][1] * normals->b +
						_hoops_CRIPA[3][2] * normals->c +
						_hoops_CRIPA[3][3] * normals->d;

			(void)HI_Normalize_Plane (planes);

			normals++;
			planes++;
		}
	}
}



/*
 * _hoops_AHGHR _hoops_AARPR _hoops_RSSA _hoops_PPR _hoops_ASGA, _hoops_GRAS _hoops_GHC _hoops_HPGR _hoops_GRR _hoops_ISHA _hoops_GGR _hoops_GSSP
 * _hoops_PCRR (_hoops_SHCAR, _hoops_RAS _hoops_PRGIA).
 *
 * (_hoops_IPRRH _hoops_RH _hoops_AARPR _hoops_RSSA _hoops_GGR _hoops_CPRRH _hoops_IS _hoops_RH _hoops_SPPR _hoops_GCA _hoops_SPRRH
 *	_hoops_RH _hoops_AARPR _hoops_IPPHR.)
 */
GLOBAL_FUNCTION void HD_Compute_World_Edge_Planes (
	Net_Rendition const &		nr,
	Polyedge const *			pe,
	_hoops_ARPA alter *				_hoops_GHRRH) {
	_hoops_SGCC const &	_hoops_HSGA = nr->transform_rendition->_hoops_IPH;
	Point const *				points = pe->points;
	Vector const *				normals = pe->_hoops_RSHA;
	int							_hoops_SHPC, _hoops_HCGS, _hoops_SAHAR, i, j;
	_hoops_ARPA						_hoops_SARRH, *planes;
	_hoops_RPRA const *			_hoops_CRIPA = null;

	if (ANYBIT (_hoops_HSGA->data._hoops_RAGR, _hoops_CICH))
		_hoops_CRIPA = _hoops_HSGA->_hoops_PPRA()->data.elements;

	j = 0;
	_hoops_SHPC = -1;
	for (i=0; i < pe->_hoops_PHHA; i++) {
		_hoops_SAHAR = j + pe->lengths[i];
		j++;
		while (j<_hoops_SAHAR) {
			if (pe->_hoops_AIHA)
				_hoops_HCGS = pe->_hoops_AIHA[j];
			else
				_hoops_HCGS = j;
			if (pe->_hoops_SPII)
				_hoops_SHPC = pe->_hoops_SPII[j];
			else
				_hoops_SHPC++;

			planes = &_hoops_GHRRH[_hoops_SHPC];

			if (!ANYBIT (_hoops_HSGA->data._hoops_RAGR, _hoops_CICH)) {
				planes->a = normals[_hoops_SHPC].x;
				planes->b = normals[_hoops_SHPC].y;
				planes->c = normals[_hoops_SHPC].z;
				planes->d = -(planes->a * points[_hoops_HCGS].x +
							  planes->b * points[_hoops_HCGS].y +
							  planes->c * points[_hoops_HCGS].z);
			}
			else {
				/* _hoops_SRSGR _hoops_GH _hoops_PCCP _hoops_CARA-_hoops_GC _hoops_IPPA */
				_hoops_SARRH.a = normals[_hoops_SHPC].x;
				_hoops_SARRH.b = normals[_hoops_SHPC].y;
				_hoops_SARRH.c = normals[_hoops_SHPC].z;
				_hoops_SARRH.d = -(_hoops_SARRH.a * points[_hoops_HCGS].x +
							  _hoops_SARRH.b * points[_hoops_HCGS].y +
							  _hoops_SARRH.c * points[_hoops_HCGS].z);

				/* _hoops_HIHP _hoops_SGS _hoops_IPPA */
				/* "_hoops_IRSIR _hoops_HIHP _hoops_GAR _hoops_GPRRH . _hoops_HAICR" - _hoops_RPRRH & _hoops_APRRH */

				planes->a = _hoops_CRIPA[0][0] * _hoops_SARRH.a +
							_hoops_CRIPA[0][1] * _hoops_SARRH.b +
							_hoops_CRIPA[0][2] * _hoops_SARRH.c /* +
							_hoops_PPRRH[0][3] * _hoops_HPRRH._hoops_GHGP */;

				planes->b = _hoops_CRIPA[1][0] * _hoops_SARRH.a +
							_hoops_CRIPA[1][1] * _hoops_SARRH.b +
							_hoops_CRIPA[1][2] * _hoops_SARRH.c /* +
							_hoops_PPRRH[1][3] * _hoops_HPRRH._hoops_GHGP */;

				planes->c = _hoops_CRIPA[2][0] * _hoops_SARRH.a +
							_hoops_CRIPA[2][1] * _hoops_SARRH.b +
							_hoops_CRIPA[2][2] * _hoops_SARRH.c /* +
							_hoops_PPRRH[2][3] * _hoops_HPRRH._hoops_GHGP */;

				planes->d = _hoops_CRIPA[3][0] * _hoops_SARRH.a +
							_hoops_CRIPA[3][1] * _hoops_SARRH.b +
							_hoops_CRIPA[3][2] * _hoops_SARRH.c +
							_hoops_CRIPA[3][3] * _hoops_SARRH.d;

				(void)HI_Normalize_Plane (planes);
			}

			j++;
		}
	}
}



/*
 * _hoops_AHGHR _hoops_AARPR _hoops_RSSA _hoops_PPR _hoops_ASGA, _hoops_GRAS _hoops_GHC _hoops_HPGR _hoops_GRR _hoops_PPSR _hoops_GGR _hoops_GSSP
 * _hoops_PCRR (_hoops_SHCAR, _hoops_RAS _hoops_PRGIA).
 */
GLOBAL_FUNCTION void HD_Compute_World_Vertex_Planes (
	Net_Rendition const &		nr,
	int							count,
	Point const *				points,
	Vector const *				normals,
	_hoops_ARPA alter *				planes) {
	_hoops_SGCC const &	_hoops_HSGA = nr->transform_rendition->_hoops_IPH;

	if (!ANYBIT (_hoops_HSGA->data._hoops_RAGR, _hoops_CICH)) {
		/* _hoops_RSH _hoops_AGAPR. */
		_hoops_PCCAR {
			planes->a = normals->x;
			planes->b = normals->y;
			planes->c = normals->z;
			planes->d = -(planes->a * points->x +
						  planes->b * points->y +
						  planes->c * points->z);
			if (--count == 0)
				break;
			++points;
			++normals;
			++planes;
		}
	}
	else {
		_hoops_RPRA const *		_hoops_CRIPA = _hoops_HSGA->_hoops_PPRA()->data.elements;

		_hoops_PCCAR {
			_hoops_ARPA						_hoops_SARRH;

			/* _hoops_SRSGR _hoops_GH _hoops_PCCP _hoops_CARA-_hoops_GC _hoops_IPPA */
			_hoops_SARRH.a = normals->x;
			_hoops_SARRH.b = normals->y;
			_hoops_SARRH.c = normals->z;
			_hoops_SARRH.d = -(_hoops_SARRH.a * points->x +
						  _hoops_SARRH.b * points->y +
						  _hoops_SARRH.c * points->z);

			/* _hoops_HIHP _hoops_SGS _hoops_IPPA */
			/* "_hoops_IRSIR _hoops_HIHP _hoops_GAR _hoops_GPRRH . _hoops_HAICR" - _hoops_RPRRH & _hoops_APRRH */
			/* _hoops_RH _hoops_IAPGR-_hoops_GGSR _hoops_AIRP _hoops_CHR _hoops_HSSPR _hoops_IS _hoops_SHH _hoops_AHHR _hoops_GGR _hoops_IRS _hoops_IRISR 4x3 */

			planes->a = _hoops_CRIPA[0][0] * _hoops_SARRH.a +
						_hoops_CRIPA[0][1] * _hoops_SARRH.b +
						_hoops_CRIPA[0][2] * _hoops_SARRH.c /* +
						_hoops_PPRRH[0][3] * _hoops_HPRRH._hoops_GHGP */;

			planes->b = _hoops_CRIPA[1][0] * _hoops_SARRH.a +
						_hoops_CRIPA[1][1] * _hoops_SARRH.b +
						_hoops_CRIPA[1][2] * _hoops_SARRH.c /* +
						_hoops_PPRRH[1][3] * _hoops_HPRRH._hoops_GHGP */;

			planes->c = _hoops_CRIPA[2][0] * _hoops_SARRH.a +
						_hoops_CRIPA[2][1] * _hoops_SARRH.b +
						_hoops_CRIPA[2][2] * _hoops_SARRH.c /* +
						_hoops_PPRRH[2][3] * _hoops_HPRRH._hoops_GHGP */;

			planes->d = _hoops_CRIPA[3][0] * _hoops_SARRH.a +
						_hoops_CRIPA[3][1] * _hoops_SARRH.b +
						_hoops_CRIPA[3][2] * _hoops_SARRH.c +
						_hoops_CRIPA[3][3] * _hoops_SARRH.d;

			(void)HI_Normalize_Plane (planes);

			if (--count == 0)
				break;

			++points;
			++normals;
			++planes;
		}
	}
}




/* _hoops_RHRRH _hoops_RPP _hoops_RH 2-_hoops_APCAR _hoops_AHCRR _hoops_HRGR _hoops_CCGC _hoops_GIAA _hoops_HCR _hoops_HPPA _hoops_GHC (_hoops_GPP _hoops_GII _hoops_ARP) */
GLOBAL_FUNCTION bool HD_Box_Within_Cutting_Planes (
	_hoops_HHCR const &		_hoops_IHCR,
	float							x,
	float							y,
	float							z,
	int								width,
	int								depth) {
	_hoops_IAPA const *		_hoops_HRCAR = _hoops_IHCR->_hoops_RGH->_hoops_PHCA;
	float							_hoops_AHRRH,
									_hoops_PHRRH;

	/* _hoops_IPHR _hoops_HII _hoops_AIR _hoops_RHCH _hoops_IS _hoops_AIR _hoops_RHCH. _hoops_HHRRH. */
	--width; /* _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_HHHR */
	--depth; /*	   "		   "	  */

	/* _hoops_HSH _hoops_RCPS _hoops_GGR _hoops_CCA _hoops_IRS _hoops_HCH _hoops_HII '_hoops_HAPC'; _hoops_AGRP _hoops_SGS _hoops_IS _hoops_IRS _hoops_APPS... */
	y -= depth;
	_hoops_AHRRH = (float)width;
	_hoops_PHRRH = (float)depth;

	do {
		_hoops_GPPA const *_hoops_IRCAR = _hoops_HRCAR->_hoops_APPA;
		bool						_hoops_IHRRH = false;

		do {
			float					_hoops_CHRRH,
													_hoops_SHRRH,
													_hoops_GIRRH;

			_hoops_CHRRH = -(x*_hoops_IRCAR->_hoops_SPPA.a + y*_hoops_IRCAR->_hoops_SPPA.b +
					 z*_hoops_IRCAR->_hoops_SPPA.c +   _hoops_IRCAR->_hoops_SPPA.d);

			if (0.0f > _hoops_CHRRH ||									/* _hoops_GSSC _hoops_RAAP */
				 (_hoops_SHRRH = _hoops_AHRRH * _hoops_IRCAR->_hoops_SPPA.a) > _hoops_CHRRH ||		/* _hoops_GSSC _hoops_RPHR */
				  (_hoops_GIRRH = _hoops_PHRRH * _hoops_IRCAR->_hoops_SPPA.b) > _hoops_CHRRH ||	/* _hoops_AAPA _hoops_RAAP */
				   _hoops_SHRRH + _hoops_GIRRH > _hoops_CHRRH)							/* _hoops_AAPA _hoops_RPHR */
				_hoops_IHRRH = true;
		} while ((_hoops_IRCAR = _hoops_IRCAR->next) != null);

		if (!_hoops_IHRRH)
			return true;
	} while ((_hoops_HRCAR = _hoops_HRCAR->next) != null);

	return false;
}

/* _hoops_RAHP _hoops_ARRS, _hoops_AHSAR _hoops_RHRRH _hoops_RPP _hoops_RH _hoops_AHCRR _hoops_HRGR _hoops_CCGC _hoops_SIPP _hoops_GII _hoops_HPPA _hoops_IPPA (_hoops_GPP _hoops_HCR _hoops_ARH) */
GLOBAL_FUNCTION bool HD_Box_Outside_Cutting_Planes (
	_hoops_HHCR const &		_hoops_IHCR,
	float							x,
	float							y,
	float							z,
	int								width,
	int								depth) {
	_hoops_IAPA const *		_hoops_HRCAR = _hoops_IHCR->_hoops_RGH->_hoops_PHCA;
	_hoops_GPPA const *	_hoops_IRCAR;
	float							_hoops_AHRRH,
												_hoops_PHRRH;

	/* _hoops_IPHR _hoops_HII _hoops_AIR _hoops_RHCH _hoops_IS _hoops_AIR _hoops_RHCH. _hoops_HHRRH. */
	--width; /* _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_HHHR */
	--depth; /*	   "		   "	  */

	/* _hoops_HSH _hoops_RCPS _hoops_GGR _hoops_CCA _hoops_IRS _hoops_HCH _hoops_HII '_hoops_HAPC'; _hoops_AGRP _hoops_SGS _hoops_IS _hoops_IRS _hoops_APPS... */
	y -= depth;
	_hoops_AHRRH = (float)width;
	_hoops_PHRRH = (float)depth;

	do {
		bool						_hoops_IHRRH = false;

		_hoops_IRCAR = _hoops_HRCAR->_hoops_APPA;
		do {
			float					_hoops_CHRRH,
													_hoops_SHRRH,
													_hoops_GIRRH;

			_hoops_CHRRH = -(x*_hoops_IRCAR->_hoops_SPPA.a + y*_hoops_IRCAR->_hoops_SPPA.b +
					 z*_hoops_IRCAR->_hoops_SPPA.c +   _hoops_IRCAR->_hoops_SPPA.d);

			if (0.0f > _hoops_CHRRH &&									/* _hoops_GSSC _hoops_RAAP */
				 (_hoops_SHRRH = _hoops_AHRRH * _hoops_IRCAR->_hoops_SPPA.a) > _hoops_CHRRH &&		/* _hoops_GSSC _hoops_RPHR */
				  (_hoops_GIRRH = _hoops_PHRRH * _hoops_IRCAR->_hoops_SPPA.b) > _hoops_CHRRH &&	/* _hoops_AAPA _hoops_RAAP */
				   _hoops_SHRRH + _hoops_GIRRH > _hoops_CHRRH)							/* _hoops_AAPA _hoops_RPHR */
				_hoops_IHRRH = true;
		} while ((_hoops_IRCAR = _hoops_IRCAR->next) != null);

		if (!_hoops_IHRRH)
			return false;
	} while ((_hoops_HRCAR = _hoops_HRCAR->next) != null);

	return true;
}




GLOBAL_FUNCTION void HD_Std_Retitle_Outer_Window (
	Display_Context const		*_hoops_RIRRH) {
	Display_Context alter		*dc =
										(Display_Context alter *)_hoops_RIRRH;

	(*dc->_hoops_ACPGR->free_outer_window)(dc);
	HD_Free_Colors (dc);
	dc->current._hoops_PAPGH = 0; /* (_hoops_GHCA _hoops_SHH _hoops_PASGH) */
	dc->current._hoops_RAPGH = (*dc->_hoops_ACPGR->get_outer_window)(dc);
	HD_Get_Colors (dc);
	dc->_hoops_CPGPR = _hoops_RCGSA;
	dc->_hoops_HSPGH = _hoops_RCGSA;
}



GLOBAL_FUNCTION void HD_Standard_Resize_Outer_Window (
	Display_Context const *		_hoops_RIRRH) {
	Display_Context alter *		dc = (Display_Context alter *)_hoops_RIRRH;

	(*dc->_hoops_ACPGR->free_outer_window)(dc);
	HD_Free_Colors (dc);
	dc->current._hoops_PAPGH = 0; /* (_hoops_GHCA _hoops_SHH _hoops_PASGH) */
	dc->current._hoops_RAPGH = (*dc->_hoops_ACPGR->get_outer_window)(dc);
	HD_Get_Colors (dc);
	dc->_hoops_CPGPR = _hoops_RCGSA;
	dc->_hoops_HSPGH = _hoops_RCGSA;
}



GLOBAL_FUNCTION void HD_Calculate_Outer_Window (
	Net_Rendition alter &		nr) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_CGRA alter &	_hoops_SGRA = nr->_hoops_SAIR;
	float						_hoops_RISHP,
								_hoops_AISHP,
								radius,
								_hoops_PISHP,
								_hoops_HISHP;
	float						_hoops_GPGRH,
								_hoops_RPGRH,
								_hoops_PPGRH,
								_hoops_APGRH,
								tmp;

	_hoops_GPGRH   = dc->current.extent.left;
	_hoops_RPGRH  = dc->current.extent.right;
	_hoops_APGRH = dc->current.extent.bottom;
	_hoops_PPGRH	   = dc->current.extent.top;

	_hoops_RISHP = (_hoops_GPGRH + _hoops_RPGRH) * 0.5f;
	_hoops_AISHP = (_hoops_APGRH + _hoops_PPGRH) * 0.5f;

	_hoops_PISHP = 0.5f * (_hoops_RPGRH - _hoops_GPGRH);
	_hoops_HISHP = 0.5f * (_hoops_PPGRH   - _hoops_APGRH);

	/*** _hoops_HGASR _hoops_AGGPA _hoops_AIRRH _hoops_PIRRH _hoops_SGH _hoops_IIGR "_hoops_HGGRR" _hoops_RIGR ***/
	if (_hoops_PISHP < _hoops_HISHP)
		radius = _hoops_PISHP;
	else
		radius = _hoops_HISHP;

	/* _hoops_HIRRH _hoops_IS _hoops_AGRP _hoops_HII _hoops_RRAA _hoops_CRIPR _hoops_SPHGR _hoops_IS _hoops_SHPR-_hoops_SHRAA... */
	if (_hoops_PISHP > _hoops_HISHP) {
		_hoops_SGRA->extent.left *= _hoops_PISHP / _hoops_HISHP;
		_hoops_SGRA->extent.right *= _hoops_PISHP / _hoops_HISHP;
	}
	else {
		_hoops_SGRA->extent.bottom *= _hoops_HISHP / _hoops_PISHP;
		_hoops_SGRA->extent.top *= _hoops_HISHP / _hoops_PISHP;
	}
	/* (_hoops_HSIH _hoops_AHHSR _hoops_RPIHR _hoops_SPHR) */


	if (_hoops_RISHP + _hoops_SGRA->extent.left * radius < _hoops_GPGRH)
		radius = (_hoops_GPGRH - _hoops_RISHP) / _hoops_SGRA->extent.left;

	if (_hoops_RISHP + _hoops_SGRA->extent.right * radius > _hoops_RPGRH)
		radius = (_hoops_RPGRH - _hoops_RISHP) / _hoops_SGRA->extent.right;

	if (_hoops_AISHP + _hoops_SGRA->extent.bottom * radius < _hoops_APGRH)
		radius = (_hoops_APGRH - _hoops_AISHP) / _hoops_SGRA->extent.bottom;

	if (_hoops_AISHP + _hoops_SGRA->extent.top * radius > _hoops_PPGRH)
		radius = (_hoops_PPGRH - _hoops_AISHP) / _hoops_SGRA->extent.top;

	tmp = _hoops_RISHP + _hoops_SGRA->extent.left * radius + 0.001f;
	dc->current.extent.left = (float)(FLOOR (tmp));
	tmp = _hoops_RISHP + _hoops_SGRA->extent.right * radius + 0.001f;
	dc->current.extent.right = (float)(FLOOR (tmp)) + 0.99f;
	tmp = _hoops_AISHP + _hoops_SGRA->extent.bottom * radius + 0.001f;
	dc->current.extent.bottom = (float)(FLOOR (tmp));
	tmp = _hoops_AISHP + _hoops_SGRA->extent.top * radius + 0.001f;
	dc->current.extent.top = (float)(FLOOR (tmp)) + 0.99f;

	dc->current._hoops_PRPSR.x =
		(int)(dc->current.extent.right - dc->current.extent.left + 1.0f);
	dc->current._hoops_PRPSR.y =
		(int)(dc->current.extent.top - dc->current.extent.bottom + 1.0f);
	dc->current.size.x =
		dc->current._hoops_PRPSR.x / dc->current._hoops_HAP.x;
	dc->current.size.y =
		dc->current._hoops_PRPSR.y / dc->current._hoops_HAP.y;

	_hoops_SGRA->extent = dc->current.extent;

	if (!dc->_hoops_PGCC._hoops_PIPGH) {
		dc->current._hoops_ARISR.x = (int)(FLOOR (_hoops_SGRA->extent.left));
		_hoops_SGRA->extent.right  -= _hoops_SGRA->extent.left;
		_hoops_SGRA->extent.left	  =	 0.0f;
		dc->current._hoops_ARISR.y = (int)(FLOOR (_hoops_SGRA->extent.bottom));
		_hoops_SGRA->extent.top	  -= _hoops_SGRA->extent.bottom;
		_hoops_SGRA->extent.bottom =	 0.0f;
	}

	_hoops_SGRA->_hoops_CIIH = _hoops_SGRA->_hoops_PHRA = _hoops_SGRA->extent;		/* _hoops_CPHSR _hoops_ICGRH */

	_hoops_SGRA->_hoops_CSIH = (float)(_hoops_SGRA->_hoops_CIIH.top - _hoops_SGRA->_hoops_CIIH.bottom) /
				 (float)(_hoops_SGRA->_hoops_CIIH.right - _hoops_SGRA->_hoops_CIIH.left) *
				 dc->current._hoops_AGRS;

	_hoops_SGRA->_hoops_SCIH = _hoops_SGRA->_hoops_PHRA;

	_hoops_SGRA->_hoops_HHCAR = _hoops_SGRA->_hoops_SCIH;
	_hoops_SGRA->_hoops_HHCAR._hoops_IACHA(dc->_hoops_ARAIP);
}




/*
 *	 _hoops_HGI _hoops_HRGR _hoops_PIGS _hoops_IS _hoops_ARP _hoops_GH _hoops_RH _hoops_ACIPR _hoops_CIHH _hoops_IIRRH _hoops_CGPR _hoops_IRS _hoops_CCAH
 *	 _hoops_RPPS _hoops_SRIPR. "_hoops_CIRRH" _hoops_HRGR _hoops_GRAA-_hoops_IRAP _hoops_CGPR _hoops_RGAR _hoops_ARIP _hoops_IIGR _hoops_RH _hoops_RPPS
 *	 _hoops_IRHS _hoops_IS _hoops_SHH _hoops_SIGSA.
 *
 *	 _hoops_SIRRH->_hoops_CPGGR _hoops_SSCP "_hoops_GCRRH" _hoops_PPR "_hoops_SCHCP" _hoops_SGI, _hoops_PPR
 *	 _hoops_RH _hoops_SCGR _hoops_HIHP _hoops_IPP _hoops_SSCP "_hoops_RCRRH", _hoops_PPR "_hoops_ACRRH"
 *	 _hoops_SGI, _hoops_PGAP _hoops_CGH _hoops_HCR _hoops_SHH _hoops_PCRRH.
 *
 */

GLOBAL_FUNCTION void HD_Compute_Hard_Clip (
	Net_Rendition alter &		nr,
	_hoops_PACIR const *	_hoops_HCRRH) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_SCASP					_hoops_ICRRH = _hoops_IHCR->flags;
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	Int_Rectangle				_hoops_CCRRH = _hoops_PGPGP(_hoops_SGRA->_hoops_PHRA, _hoops_SGRA->_hoops_SCIH);
	Int_Rectangle				_hoops_SCRRH;

	if (ANYBIT (dc->_hoops_CPGPR, _hoops_AASCA|_hoops_CHPGP) ||
		BIT (_hoops_IHCR->flags, _hoops_ASPIP)) {
		/* _hoops_AA _hoops_RH _hoops_SHSC _hoops_AHAP; _hoops_GA'_hoops_RA _hoops_RHCA */
		_hoops_SCRRH = _hoops_CCRRH;
		_hoops_ICRRH |= _hoops_CGHIP|_hoops_ASPIP;
	}
	else if (_hoops_HCRRH == null) {
		/* _hoops_HRSAR _hoops_CPSRR _hoops_HAR _hoops_IHIR; _hoops_IRGH _hoops_CPSRR _hoops_HAR _hoops_RAGA */

		/* _hoops_PSP _hoops_IRGH; _hoops_SAHR _hoops_HRSAR - _hoops_ARCRA _hoops_HRSAR _hoops_CCA _hoops_IHIR */
		_hoops_SCRRH = _hoops_PGPGP(_hoops_IHCR->_hoops_AGAA, _hoops_CCRRH);

		if (_hoops_SCRRH.left > _hoops_SCRRH.right || _hoops_SCRRH.bottom > _hoops_SCRRH.top)
			_hoops_ICRRH &= ~_hoops_CGHIP; /* _hoops_IPIHR _hoops_SCH! */
		else if (_hoops_SCRRH == _hoops_CCRRH)
			_hoops_ICRRH |= _hoops_ASPIP|_hoops_CGHIP;
	}
	else {
		/* _hoops_GCHRR _hoops_IRGH _hoops_CPSRR _hoops_RAGA */

		float				_hoops_RISHP, _hoops_AISHP,
							_hoops_PISHP, _hoops_HISHP;
		_hoops_PACIR	extent;

		/* _hoops_SICR _hoops_GSRRH _hoops_IS _hoops_SHPR _hoops_PCRR *_hoops_GPCPR* _hoops_RH _hoops_PSHR _hoops_PPRRR
		 * _hoops_GAR _hoops_RSRRH _hoops_RHAP _hoops_SCH.
		 */

		_hoops_PISHP = (_hoops_SGRA->extent.right - _hoops_SGRA->extent.left) * 0.5f;
		_hoops_HISHP = (_hoops_SGRA->extent.top -   _hoops_SGRA->extent.bottom) * 0.5f;
		_hoops_RISHP = (_hoops_SGRA->extent.left +  _hoops_SGRA->extent.right) * 0.5f;
		_hoops_AISHP = (_hoops_SGRA->extent.top +   _hoops_SGRA->extent.bottom) * 0.5f;

		extent.left =	_hoops_RISHP + _hoops_HCRRH->left	 * _hoops_PISHP;
		extent.right =	_hoops_RISHP + _hoops_HCRRH->right	 * _hoops_PISHP;
		extent.bottom = _hoops_AISHP + _hoops_HCRRH->bottom * _hoops_HISHP;
		extent.top =	_hoops_AISHP + _hoops_HCRRH->top	 * _hoops_HISHP;

		_hoops_SCRRH.left =	  FLOOR (extent.left + 0.499f);
		_hoops_SCRRH.bottom = FLOOR (extent.bottom + 0.499f);
		_hoops_SCRRH.right =  FLOOR (extent.right - 0.5f);
		_hoops_SCRRH.top =	  FLOOR (extent.top - 0.5f);

		/* _hoops_ARRPA _hoops_ISPR */
		if (_hoops_SCRRH.left < _hoops_CCRRH.left) 
			_hoops_SCRRH.left = _hoops_CCRRH.left;
		if (_hoops_SCRRH.right > _hoops_CCRRH.right) 
			_hoops_SCRRH.right = _hoops_CCRRH.right;
		if (_hoops_SCRRH.bottom < _hoops_CCRRH.bottom) 
			_hoops_SCRRH.bottom = _hoops_CCRRH.bottom;
		if (_hoops_SCRRH.top > _hoops_CCRRH.top) 
			_hoops_SCRRH.top = _hoops_CCRRH.top;

		_hoops_ICRRH |= _hoops_CGHIP;		/* _hoops_PAH'_hoops_RA _hoops_SHH _hoops_IRAP! */
	}

	_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

	_hoops_GGCC->flags = _hoops_ICRRH;

	_hoops_GGCC->_hoops_AGAA = _hoops_SCRRH;

	_hoops_GGCC->_hoops_RGPSP = _hoops_SCRRH;

	// _hoops_ASRRH _hoops_ISCC _hoops_PSRRH _hoops_HSRRH "_hoops_PRHSA _hoops_SHPR"
}



struct _hoops_ISRRH {
	_hoops_PACIR				extent;
	Int_Rectangle			_hoops_PHRA;
	_hoops_RIARP		_hoops_CSRRH, _hoops_SSRRH;
	_hoops_CRCP const			*_hoops_GGARH;
	Display_Context const	*dc;
};


local void _hoops_RGARH (
	Window const *		window,
	_hoops_ISRRH alter *	_hoops_ISRRH) {
	float				_hoops_RISHP, _hoops_AISHP, _hoops_PISHP, _hoops_HISHP;
	Int_Rectangle		_hoops_AGARH;
	int					weight = 2*_hoops_ISRRH->dc->_hoops_PGCC._hoops_IHHSR;

	/* _hoops_RH _hoops_HSPR _hoops_HRGR _hoops_HCR _hoops_CHGIP _hoops_PPR _hoops_GSAS _hoops_HII _hoops_RSRRH */
	/* _hoops_RPP _hoops_SGS _hoops_SAGGR _hoops_PGARH _hoops_HGAS, _hoops_SGS _hoops_SSCP _hoops_IS _hoops_SHH _hoops_HAH */

	_hoops_AGARH = _hoops_ISRRH->_hoops_PHRA;

	_hoops_PISHP = (_hoops_ISRRH->extent.right - _hoops_ISRRH->extent.left) * 0.5f;
	_hoops_HISHP = (_hoops_ISRRH->extent.top -	 _hoops_ISRRH->extent.bottom) * 0.5f;
	_hoops_RISHP = (_hoops_ISRRH->extent.left +	 _hoops_ISRRH->extent.right) * 0.5f;
	_hoops_AISHP = (_hoops_ISRRH->extent.top +	 _hoops_ISRRH->extent.bottom) * 0.5f;

	_hoops_ISRRH->extent.left =	  _hoops_RISHP + window->_hoops_RCHS.left   * _hoops_PISHP;
	_hoops_ISRRH->extent.right =  _hoops_RISHP + window->_hoops_RCHS.right  * _hoops_PISHP;
	_hoops_ISRRH->extent.bottom = _hoops_AISHP + window->_hoops_RCHS.bottom * _hoops_HISHP;
	_hoops_ISRRH->extent.top =	  _hoops_AISHP + window->_hoops_RCHS.top	   * _hoops_HISHP;

	_hoops_ISRRH->_hoops_PHRA.left =	  FLOOR (_hoops_ISRRH->extent.left + 0.499f);
	_hoops_ISRRH->_hoops_PHRA.bottom = FLOOR (_hoops_ISRRH->extent.bottom + 0.499f);
	_hoops_ISRRH->_hoops_PHRA.right =  FLOOR (_hoops_ISRRH->extent.right - 0.5f);
	_hoops_ISRRH->_hoops_PHRA.top =	  FLOOR (_hoops_ISRRH->extent.top - 0.5f);

	if (BIT(_hoops_ISRRH->_hoops_CSRRH, _hoops_AIARP)) {
		_hoops_ISRRH->_hoops_PHRA._hoops_AGPGP(weight);
	}
	else {
		/* _hoops_CCAH _hoops_RPPS _hoops_HRGR _hoops_HAR _hoops_HGARH */

		if (BIT(_hoops_ISRRH->_hoops_SSRRH, _hoops_AIARP)) {
			if (_hoops_ISRRH->_hoops_PHRA.left < _hoops_AGARH.left &&
				_hoops_ISRRH->_hoops_PHRA.left >= _hoops_AGARH.left - weight)
				_hoops_ISRRH->_hoops_PHRA.left = _hoops_AGARH.left;
			if (_hoops_ISRRH->_hoops_PHRA.right > _hoops_AGARH.right &&
				_hoops_ISRRH->_hoops_PHRA.right <= _hoops_AGARH.right + weight)
				_hoops_ISRRH->_hoops_PHRA.right = _hoops_AGARH.right;
			if (_hoops_ISRRH->_hoops_PHRA.bottom < _hoops_AGARH.bottom &&
				_hoops_ISRRH->_hoops_PHRA.bottom >= _hoops_AGARH.bottom - weight)
				_hoops_ISRRH->_hoops_PHRA.bottom = _hoops_AGARH.bottom;
			if (_hoops_ISRRH->_hoops_PHRA.top > _hoops_AGARH.top &&
				_hoops_ISRRH->_hoops_PHRA.top <= _hoops_AGARH.top + weight)
				_hoops_ISRRH->_hoops_PHRA.top = _hoops_AGARH.top;
		}
	}

	_hoops_ISRRH->_hoops_SSRRH = _hoops_ISRRH->_hoops_CSRRH;
}


local void _hoops_IGARH (
	_hoops_CRCP const	*_hoops_SRCP,
	_hoops_ISRRH alter	*_hoops_ISRRH) {
	Attribute const	*_hoops_HPHCR;
	Window const		*window = null;

	while (_hoops_SRCP->_hoops_IPPGR == null) {
		_hoops_SRCP = (_hoops_CRCP const *)_hoops_SRCP->owner;
		if ((_hoops_CRCP const *)_hoops_SRCP == _hoops_ISRRH->_hoops_GGARH) return;
	}

	if ((_hoops_CRCP const *)_hoops_SRCP->owner != _hoops_ISRRH->_hoops_GGARH)
		_hoops_IGARH ((_hoops_CRCP const *)_hoops_SRCP->owner, _hoops_ISRRH);

	_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR;
	do {
		if (_hoops_HPHCR->type == HK_WINDOW)
			window = (Window const *)_hoops_HPHCR;
		else if (_hoops_HPHCR->type == HK_WINDOW_FRAME)
			_hoops_ISRRH->_hoops_CSRRH = ((_hoops_GSAIR const *)_hoops_HPHCR)->flags;
#ifndef DISABLE_STYLE_SEGMENT
		else if (_hoops_HPHCR->type == HK_STYLE) {
			Style *				style = (Style *)_hoops_HPHCR;

			if (style->_hoops_IGRPR) {
				_hoops_CRCP const *		_hoops_CGARH = _hoops_ISRRH->_hoops_GGARH;

				_hoops_ISRRH->_hoops_GGARH = style->_hoops_IGRPR->owner;
				_hoops_IGARH (style->_hoops_IGRPR, _hoops_ISRRH);
				_hoops_ISRRH->_hoops_GGARH = _hoops_CGARH;
			}
		}
#endif
	}
	_hoops_RGGA ((_hoops_HPHCR = _hoops_HPHCR->next) == null);

	/* _hoops_AASA _hoops_GGSR _hoops_IH _hoops_RGR, _hoops_HIS _hoops_SGS _hoops_HCR _hoops_RGCI _hoops_CCPAR _hoops_GA'_hoops_RA _hoops_HS _hoops_IS _hoops_SHH
	 * _hoops_SGARH'_hoops_GRI _hoops_PHRSA _hoops_SPRS.
	 */
	if (window != null) _hoops_RGARH (window, _hoops_ISRRH);
}


GLOBAL_FUNCTION bool HD_Gather_Window_Extent (
	Display_Context alter *			dc,
	_hoops_RIACA alter *	_hoops_AIACA) {
	_hoops_CRCP const *					_hoops_SRCP = _hoops_AIACA->context;
	Net_Rendition					nr;
	_hoops_CGRA				_hoops_SGRA;
	_hoops_ISRRH						_hoops_ISRRH;
	Int_XY							_hoops_GRARH;

	_hoops_GRARH.x = dc->current._hoops_PRPSR.x;
	_hoops_GRARH.y = dc->current._hoops_PRPSR.y;

	HD_Get_Current_Info (dc);

	if (dc->_hoops_SHCIP == null ||
		_hoops_GRARH.x != dc->current._hoops_PRPSR.x ||
		_hoops_GRARH.y != dc->current._hoops_PRPSR.y) {
		bool	_hoops_RRARH = BIT(dc->flags, _hoops_GIRIP);

		if (dc->_hoops_SHCIP != null) {
			dc->_hoops_SHCIP = null;
			dc->flags &= ~_hoops_GIRIP;
		}

		HD_Minimum_Update (dc);
		if (_hoops_RRARH)
			dc->flags |= _hoops_GIRIP;
		else
			dc->flags &= ~_hoops_GIRIP;

	}

	nr = dc->_hoops_SHCIP;
	_hoops_SGRA = nr->_hoops_SAIR;

	_hoops_AIACA->_hoops_HAP.x = dc->current._hoops_HAP.x;
	_hoops_AIACA->_hoops_HAP.y = dc->current._hoops_HAP.y;
	_hoops_AIACA->_hoops_HIACA.x = dc->current._hoops_PRPSR.x;
	_hoops_AIACA->_hoops_HIACA.y = dc->current._hoops_PRPSR.y;

	_hoops_ISRRH._hoops_PHRA.left = _hoops_SGRA->_hoops_PHRA.left;
	_hoops_ISRRH._hoops_PHRA.right = _hoops_SGRA->_hoops_PHRA.right;
	_hoops_ISRRH._hoops_PHRA.bottom = _hoops_SGRA->_hoops_PHRA.bottom;
	_hoops_ISRRH._hoops_PHRA.top = _hoops_SGRA->_hoops_PHRA.top;

	_hoops_ISRRH.extent.left = _hoops_SGRA->extent.left;
	_hoops_ISRRH.extent.right = _hoops_SGRA->extent.right;
	_hoops_ISRRH.extent.bottom = _hoops_SGRA->extent.bottom;
	_hoops_ISRRH.extent.top = _hoops_SGRA->extent.top;

	_hoops_ISRRH._hoops_CSRRH = _hoops_ISRRH._hoops_SSRRH = _hoops_SGRA->_hoops_ASIHP;

	_hoops_ISRRH.dc = dc;

	if (_hoops_SRCP != null) {
		/* _hoops_RSRA _hoops_CAGH _hoops_RAGA */
		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) {		/* _hoops_ARARH */
			Subsegment const *		_hoops_GIPIA;

			_hoops_RGGA ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) == null) {
				_hoops_RGGA (_hoops_GIPIA->next == null) _hoops_GIPIA = _hoops_GIPIA->next;
				if (_hoops_GIPIA->type != _hoops_IRCP) break;
				_hoops_SRCP = (_hoops_CRCP const *)_hoops_GIPIA;
			}
		}

		if (_hoops_SRCP != dc->_hoops_AAHSR) {
			_hoops_ISRRH._hoops_GGARH = dc->_hoops_AAHSR;

			_hoops_IGARH (_hoops_SRCP, &_hoops_ISRRH);
		}
	}
	else {
		/* _hoops_CRAA _hoops_CHIA */
		_hoops_CRCP const **	path = _hoops_AIACA->path;
		int					count = _hoops_AIACA->_hoops_CISAA;

		/* _hoops_SRS, _hoops_IHIS _hoops_CPCHR _hoops_GGR _hoops_CRAA _hoops_IS _hoops_RHPP */
		_hoops_SRCP = null;
		_hoops_PCCAR {
			if (--count < 0)
				break;

			if (*path == dc->_hoops_AAHSR) {
				_hoops_SRCP = *path++;
				break;
			}

			++path;
		}

		if (_hoops_SRCP == null) {
			/* _hoops_RHPP _hoops_HAR _hoops_PRARH _hoops_HRARH.
			 * _hoops_IRHH _hoops_RCRR _hoops_SRS _hoops_CAGH _hoops_HRGR _hoops_IRARH _hoops_RRGI _hoops_RH _hoops_RHPP */
			path = _hoops_AIACA->path;
			count = _hoops_AIACA->_hoops_CISAA;

			_hoops_SRCP = *path;
			while (_hoops_SRCP != dc->_hoops_AAHSR) {
				if (_hoops_SRCP == null)
					return false;		/* _hoops_PAH'_hoops_RA _hoops_CAHA _hoops_SCH _hoops_GGSR... */

				_hoops_SRCP = _hoops_SRCP->owner;
			}

			/* _hoops_PIHA _hoops_SHH _hoops_RRGI _hoops_RHPP, _hoops_HIS _hoops_SGARH _hoops_IS _hoops_IIH */
			_hoops_SRCP = *path++;
			--count;
			_hoops_ISRRH._hoops_GGARH = dc->_hoops_AAHSR;
			_hoops_IGARH (_hoops_SRCP, &_hoops_ISRRH);
		}

		/* _hoops_HPPP _hoops_GII _hoops_HHRPA _hoops_SGHC */
		while (count-- != 0) {
			_hoops_SRCP = *path++;

			if (_hoops_SRCP->type != _hoops_IRCP)	/* _hoops_CPAP _hoops_HPGR _hoops_RSGR _hoops_IIGR _hoops_HIGR */
				break;

			/* _hoops_CRHR _hoops_SGARH _hoops_HII "_hoops_CRARH" -- _hoops_SR _hoops_SAHR _hoops_HHGC _hoops_IRGH _hoops_AIRC */
			_hoops_ISRRH._hoops_GGARH = _hoops_SRCP->owner;

			_hoops_IGARH (_hoops_SRCP, &_hoops_ISRRH);
		}
	}

	_hoops_AIACA->_hoops_IIACA.left	  = _hoops_ISRRH._hoops_PHRA.left;
	_hoops_AIACA->_hoops_IIACA.right  = _hoops_ISRRH._hoops_PHRA.right;
	_hoops_AIACA->_hoops_IIACA.bottom = _hoops_ISRRH._hoops_PHRA.bottom;
	_hoops_AIACA->_hoops_IIACA.top	  = _hoops_ISRRH._hoops_PHRA.top;

	return true;
}

GLOBAL_FUNCTION void HD_Queue_Pixel_Location_Event (
	Display_Context const *		dc,
	int							status,
	int							_hoops_CHCGR,
	int							_hoops_SHCGR) {
#ifndef DISABLE_EVENTS
	float						x, y;

	/* _hoops_GIAPR: _hoops_RGR *_hoops_CSAP* _hoops_GGR _hoops_CSHCR _hoops_IIGR _hoops_CSPH->_hoops_CPHSR + _hoops_AAP._hoops_GAPGH,
	 * _hoops_HIH _hoops_SGS _hoops_SRARH _hoops_GH _hoops_GPP _hoops_CCA _hoops_RH _hoops_GAARH _hoops_CIPH. _hoops_IAPPR
	 * _hoops_RSAS'_hoops_RA _hoops_SCH _hoops_RAARH _hoops_GGR _hoops_CSHCR _hoops_IIGR _hoops_CSPH->_hoops_SCGR??
	 */

	if (dc->_hoops_PGCC._hoops_PIPGH) {
		_hoops_CHCGR -= (int)dc->current.extent.left;
		_hoops_SHCGR -= (int)dc->current.extent.bottom;
	}

	x = (float)_hoops_CHCGR /
		(float)(dc->current._hoops_PRPSR.x - 1) * 2.0001f - 1.0f;

	y = (float)_hoops_SHCGR /
		(float)(dc->current._hoops_PRPSR.y - 1) * 2.0001f - 1.0f;

	if (x > 1.0f) 
		x = 1.0f;
	else if (x < -1.0f) 
		x = -1.0f;

	if (y > 1.0f) 
		y = 1.0f;
	else if (y < -1.0f) y = -1.0f;


	/* _hoops_ICIC _hoops_HIIC */
	HI_Queue_Location_Event (dc->_hoops_RIGC, (_hoops_GGAGR alter *)dc->_hoops_GHRI, x, y, status,
							 status & 0x00FF ? _hoops_IPSHA : _hoops_SPSHA);
#endif
}


local bool _hoops_AAARH (
	Display_Context const *		dc) {

	_hoops_HISHA const *				event;

#ifdef DISABLE_EVENTS
	return	HOOPS_WORLD->_hoops_PAARH != null;	/* _hoops_RGAR _hoops_IRS _hoops_GRH _hoops_PGRRR _hoops_CGH _hoops_SHH _hoops_SSRR */
#else
	HI_Check_For_Events(dc->_hoops_RIGC, dc->_hoops_GHRI);

	if ((event = dc->_hoops_RIGC->_hoops_PAARH) != null) do switch (event->type) {

		case _hoops_SAIIR: {
			Selection_Event const *		_hoops_GPIIR = (Selection_Event const *)event;
			_hoops_RPIIR const *		si;

			/* _hoops_GA'_hoops_RA _hoops_RPR _hoops_GISAP-_hoops_RIPPR _hoops_SSHGR - _hoops_RGAR _hoops_GH/_hoops_HAARH */

			if ((si = _hoops_GPIIR->_hoops_APIIR) != null) do {
				if (si->_hoops_GCSAP == _hoops_CPSHA || si->_hoops_GCSAP == _hoops_HPSHA)
					return true;
			} while ((si = si->next) != null);
		}	break;

		case _hoops_AAIIR: {
			_hoops_PAIIR const *		_hoops_HAIIR = (_hoops_PAIIR const *)event;
			/* _hoops_GA'_hoops_RA _hoops_RPR _hoops_GISAP-_hoops_RIPPR _hoops_SSHGR - _hoops_RGAR _hoops_GH/_hoops_HAARH */

			if (_hoops_HAIIR->action == _hoops_CPSHA ||
				_hoops_HAIIR->action == _hoops_HPSHA) return true;
		}	break;

		case _hoops_PHIIR: {
			/* _hoops_GA'_hoops_RA _hoops_RPR _hoops_HPGR _hoops_HCR */
		}	break;

		default: {
			/* _hoops_IAARH, _hoops_CAARH, _hoops_RHIPP _hoops_RPR _hoops_SHR */
			return true;
		}		/* _hoops_IHSA; */
	} while ((event = event->next) != null);

	return false;
#endif
}

GLOBAL_FUNCTION void HD_Interrupt_Update (
	Display_Context const	*_hoops_SAARH,
	bool					_hoops_GPARH,
	bool					_hoops_RPARH) {

	Display_Context alter	*dc = (Display_Context alter *)_hoops_SAARH;

	ASSERT(dc->_hoops_APAGH == false);
	ASSERT(!BIT(dc->flags, _hoops_RPSRR));

	// _hoops_CGHI _hoops_APCRR _hoops_PHHIP _hoops_HRGR _hoops_CCAH _hoops_RRS _hoops_PHHIP
	if (!_hoops_RPARH && dc->_hoops_CGAP == 0 &&
		dc->_hoops_HPAGH == null && 
		dc->_hoops_RIGC->_hoops_HCPGR != 0 && 
		!BIT(dc->flags, _hoops_CHSI)) {

		_hoops_GSPGR _hoops_APARH = dc->_hoops_RIGC->_hoops_ACHGH - *HOOPS_WORLD->time_stamp;

		if (dc->_hoops_PPAGH || _hoops_APARH < 0) {
			dc->_hoops_CPAGH = dc->_hoops_GHAGH;
			dc->_hoops_IPAGH = dc->_hoops_SPAGH;
		}
	}
		
	dc->flags |= _hoops_IRAGH; /* _hoops_HSPP _hoops_SRGIR */

	if (dc->options._hoops_HSPRP == _hoops_RSPRP)
		dc->_hoops_ICAGH = _hoops_GPARH; /* _hoops_GA'_hoops_RA _hoops_PGSA _hoops_IASI _hoops_RPISR */
	else 
	if (dc->options._hoops_HSPRP == _hoops_ASPRP)
		dc->_hoops_ICAGH = true;
	else /* _hoops_PPARH */
		dc->_hoops_ICAGH = false;

	dc->_hoops_RSAGH = _hoops_RPARH; /* _hoops_HSPP _hoops_PAAP _hoops_IAPR */

	if (!_hoops_RPARH)
		HI_Update_Interrupted(dc->_hoops_RIGC);
}


GLOBAL_FUNCTION bool HD_Exit_Update (
	Display_Context const *		dc) {

	/* _hoops_GA'_hoops_RA _hoops_RCCS _hoops_RPP _hoops_GGR _hoops_GHSHA */
	if (dc->_hoops_APHHP)
		return false;

	/* _hoops_AIAH _hoops_PPRIP */
	if (BIT(dc->flags, _hoops_IRAGH))
		return BIT(dc->flags, _hoops_IRAGH);

	if (HOOPS_WORLD->_hoops_SIHGH == 0 && 
		dc->_hoops_RIGC->_hoops_HCPGR &&
		HI_What_Time() > dc->_hoops_RIGC->_hoops_ACHGH) {

		HD_Interrupt_Update(dc, false, false);
	}
	else if (!dc->_hoops_RIGC->_hoops_IIHGH) {
		/* _hoops_GA'_hoops_RA _hoops_IHSH _hoops_GAPR */
	}
	else if (dc->options._hoops_GSPRP != _hoops_ICPRP) {

		if (_hoops_AAARH (dc)) {
			_hoops_RCCA(_hoops_RSRGH)++;
			HD_Interrupt_Update(dc, true, false);
		}

		/* _hoops_PAGA: _hoops_HAR _hoops_HPARH(_hoops_RCPP) _hoops_CR _hoops_SR _hoops_RGAR _hoops_HHGC _hoops_IS _hoops_AA _hoops_CARS */
		dc->_hoops_RIGC->_hoops_IIHGH = false;
	}

	return BIT(dc->flags, _hoops_IRAGH);
}



GLOBAL_FUNCTION void HD_Update_Log(Display_Context const *_hoops_SAARH, const char * message, const char* file, int line)
{
#ifdef _hoops_PGAGH
	Display_Context * dc = (Display_Context *)_hoops_SAARH;

	_hoops_HGAGH * log = &dc->_hoops_PPHGH[dc->_hoops_HPHGH++];

	dc->_hoops_HPHGH %= _hoops_APHGH;

	log->message = message;
	log->file = file;
	log->line = line;

	log->time = *HOOPS_WORLD->time_stamp;

	if (dc->_hoops_RIGC->_hoops_HCPGR != 0) {

		log->_hoops_ASPGR = dc->_hoops_RIGC->_hoops_ACHGH;
	}

	if (dc->_hoops_SPA) {

		log->ref = dc->_hoops_SPA->_hoops_CSAGR;
		log->_hoops_IGAGH = dc->_hoops_SPA->index;
		log->_hoops_CGAGH = dc->_hoops_SPA->geometry;
	}
#else
	UNREFERENCED(_hoops_SAARH);
	UNREFERENCED(message);
	UNREFERENCED(file);
	UNREFERENCED(line);
#endif	
}



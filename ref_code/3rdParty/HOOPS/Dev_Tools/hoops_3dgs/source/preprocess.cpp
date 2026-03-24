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
 * $Id: obf_tmp.txt 1.164 2010-08-16 22:20:01 covey Exp $
 */


#include "hoops.h"
#include "database.h"
#include "please.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "phedron.h"

/* _hoops_GIAPR: (_hoops_ASSP'_hoops_RA _hoops_ASAC _hoops_CGHA _hoops_RGSGR) */

/* _hoops_GIAPR: _hoops_RGR _hoops_CGH _hoops_HCR _hoops_SHH _hoops_RHHS _hoops_SGGR _hoops_HPGR _hoops_RH _hoops_CICIP _hoops_ASGAR. _hoops_SACSC! */



GLOBAL_FUNCTION void HD_Get_Colors (
	Display_Context alter		*dc) {

	if (dc->_hoops_PGCC._hoops_PIHSR != _hoops_SIHSR) {
		/* _hoops_GHCA _hoops_RRP _hoops_RHPP _hoops_CARSR _hoops_SPSHH _hoops_HSH _hoops_IH _hoops_GGCSI -> _hoops_HSISI */
		dc->_hoops_AGPGH.r = dc->_hoops_PGCC._hoops_CIPGH.r;
		dc->_hoops_AGPGH.g = dc->_hoops_PGCC._hoops_CIPGH.g;
		dc->_hoops_AGPGH.b = dc->_hoops_PGCC._hoops_CIPGH.b;
		dc->_hoops_RHGCR  = dc->_hoops_PGCC._hoops_SIPGH;
		dc->_hoops_GCPRP = 0;
	}
	else {
		if (dc->current._hoops_GCPRP >= 0 ||
			BIT (dc->_hoops_AAHSR->_hoops_RCGC, _hoops_ASRRA)) {
			HD_Determine_Fixed_Colors (dc, dc->current._hoops_GCPRP,
									   &dc->_hoops_GCPRP,
									   dc->options._hoops_IPSSP);

			dc->_hoops_AGPGH.r = dc->options._hoops_IPSSP[0];
			dc->_hoops_AGPGH.g = dc->options._hoops_IPSSP[1];
			dc->_hoops_AGPGH.b = dc->options._hoops_IPSSP[2];
			dc->_hoops_SCAGH = true;
		}
		else {
			dc->_hoops_GCPRP = 0;
			dc->_hoops_AGPGH.r = 0;
			dc->_hoops_AGPGH.g = 0;
			dc->_hoops_AGPGH.b = 0;
			dc->_hoops_SCAGH = false;
		}

		dc->_hoops_RGPGH = dc->current._hoops_AAPSR - dc->_hoops_GCPRP;
		dc->_hoops_RHGCR = dc->current._hoops_APASR + dc->_hoops_RGPGH;
		dc->_hoops_RIHHP = dc->current._hoops_APASR;
		dc->_hoops_SSAGH = 0; /* _hoops_IS _hoops_HSPP */
		dc->_hoops_GGPGH = dc->current._hoops_APASR;

		dc->_hoops_RRPGH = null;
		dc->_hoops_ARPGH = null;
		dc->_hoops_PRPGH = null;
		dc->_hoops_HRPGH = null;

		{	Driver_Color alter	*_hoops_SPRAR;
			int						tmp;
			RGB alter			*rgb;

			tmp = _hoops_IAAA (dc->_hoops_RIHHP + dc->_hoops_RGPGH,
					   dc->_hoops_GGPGH + dc->_hoops_SSAGH);
			if (tmp == 0) tmp = 1;

			ALLOC_ARRAY (_hoops_SPRAR, tmp, Driver_Color);
			dc->_hoops_CSIR = _hoops_SPRAR;
			do {
				*_hoops_SPRAR++ = _hoops_IAASP;
			} _hoops_RGGA (--tmp == 0);

			tmp = dc->_hoops_PGCC._hoops_AAPSR + dc->_hoops_PGCC._hoops_APASR;
			ALLOC_ARRAY (rgb, tmp, RGB);
			dc->_hoops_CHHIP = rgb;
			do {
				rgb->red = rgb->green = rgb->blue = -1.0f;		++rgb;
			} _hoops_RGGA (--tmp == 0);
		}

		if (dc->_hoops_GCPRP > 0) {
			int				_hoops_GPCSC, _hoops_RPCSC, _hoops_APCSC,
										r;
			int				_hoops_PPCSC[128];
			int				_hoops_HPCSC[128];
			int				_hoops_IPCSC[128];
			float			_hoops_CPCSC[128];
			float			_hoops_SPCSC[128];
			float			_hoops_GHCSC[128];

			_hoops_GPCSC = dc->_hoops_AGPGH.r - 1;
			_hoops_RPCSC = dc->_hoops_AGPGH.g - 1;
			_hoops_APCSC = dc->_hoops_AGPGH.b - 1;

			{	int		i = _hoops_GPCSC;
				float	_hoops_RHCSC = (float)_hoops_GPCSC;
				float	scale;

				scale = (float)dc->_hoops_PGCC._hoops_PCHSR - 0.01f;

				/* _hoops_CAHA _hoops_GAASP _hoops_SIISR _hoops_PPR _hoops_SISS _hoops_HAIR _hoops_RAAA
				 * _hoops_IH _hoops_RGR _hoops_PAPA _hoops_GGR _hoops_RH _hoops_RPIHR _hoops_HAIR _hoops_CSRA
				 */
				do {
					_hoops_CPCSC[i] = (float)i / _hoops_RHCSC;
					if (dc->options._hoops_SRSSP && BIT(dc->_hoops_PGCC.flags, _hoops_GGISR))
						_hoops_CPCSC[i] = _hoops_SGIHR (_hoops_CPCSC[i]);
					_hoops_PPCSC[i] = (int)(_hoops_CPCSC[i] * scale);
					if (_hoops_PPCSC[i] > scale) _hoops_PPCSC[i] = (int)scale;
				} _hoops_RGGA (--i < 0);
			}
			{	int		i = _hoops_RPCSC;
				float	_hoops_AHCSC = (float)_hoops_RPCSC;
				float	scale;

				scale = (float)dc->_hoops_PGCC._hoops_PCHSR - 0.01f;

				/* _hoops_CAHA _hoops_GAASP _hoops_SIISR _hoops_PPR _hoops_SISS _hoops_HAIR _hoops_RAAA
				 * _hoops_IH _hoops_RGR _hoops_PAPA _hoops_GGR _hoops_RH _hoops_RPIHR _hoops_HAIR _hoops_CSRA
				 */
				do {
					_hoops_SPCSC[i] = (float)i / _hoops_AHCSC;
					if (dc->options._hoops_SRSSP && BIT(dc->_hoops_PGCC.flags, _hoops_GGISR))
						_hoops_SPCSC[i] = _hoops_SGIHR (_hoops_SPCSC[i]);
					_hoops_HPCSC[i] = (int)(_hoops_SPCSC[i] * scale);
					if (_hoops_HPCSC[i] > scale) _hoops_HPCSC[i] = (int)scale;
				} _hoops_RGGA (--i < 0);
			}
			{	int		i = _hoops_APCSC;
				float	_hoops_PHCSC = (float)_hoops_APCSC;
				float	scale;

				scale = (float)dc->_hoops_PGCC._hoops_PCHSR - 0.01f;

				/* _hoops_CAHA _hoops_GAASP _hoops_SIISR _hoops_PPR _hoops_SISS _hoops_HAIR _hoops_RAAA
				 * _hoops_IH _hoops_RGR _hoops_PAPA _hoops_GGR _hoops_RH _hoops_RPIHR _hoops_HAIR _hoops_CSRA
				 */
				do {
					_hoops_GHCSC[i] = (float)i / _hoops_PHCSC;
					if (dc->options._hoops_SRSSP && BIT(dc->_hoops_PGCC.flags, _hoops_GGISR))
						_hoops_GHCSC[i] = _hoops_SGIHR (_hoops_GHCSC[i]);
					_hoops_IPCSC[i] = (int)(_hoops_GHCSC[i] * scale);
					if (_hoops_IPCSC[i] > scale) _hoops_IPCSC[i] = (int)scale;
				} _hoops_RGGA (--i < 0);
			}

			r = _hoops_GPCSC;
			do {
				int		g = _hoops_RPCSC;
				do {
					int		b = _hoops_APCSC;
					int		index;

					/* _hoops_GGARP _hoops_HAIR _hoops_ARCR _hoops_IH _hoops_GRR _hoops_RPIHR _hoops_HAIR _hoops_HHSPR */
					do {
						RGB alter		*_hoops_SPRAR;

						index = (r * dc->_hoops_AGPGH.g + g) *
								dc->_hoops_AGPGH.b + b +
								dc->_hoops_RHGCR;

						(*dc->_hoops_ACPGR->_hoops_SCCSR) (dc,
								_hoops_PPCSC[r], _hoops_HPCSC[g], _hoops_IPCSC[b],
								index);

						_hoops_SPRAR = (RGB alter *)&dc->_hoops_CHHIP[index];
						_hoops_SPRAR->red   = _hoops_CPCSC[r];
						_hoops_SPRAR->green = _hoops_SPCSC[g];
						_hoops_SPRAR->blue  = _hoops_GHCSC[b];
					}
					_hoops_RGGA (--b < 0);
				}
				_hoops_RGGA (--g < 0);
			}
			_hoops_RGGA (--r < 0);
		}
	}

	dc->_hoops_HHGCR.r =
		dc->_hoops_AGPGH.g * dc->_hoops_AGPGH.b;
	dc->_hoops_HHGCR.g = dc->_hoops_AGPGH.b;
	dc->_hoops_HHGCR.b = 1;

	dc->_hoops_AHGCR.r = dc->_hoops_AGPGH.r - 1;
	dc->_hoops_AHGCR.g = dc->_hoops_AGPGH.g - 1;
	dc->_hoops_AHGCR.b = dc->_hoops_AGPGH.b - 1;
}


GLOBAL_FUNCTION void HD_Determine_Fixed_Colors (
	Display_Context const	*dc,
	int							start,
	int alter					*fixed,
	int alter					*_hoops_CAGCR) {

	if (dc->options._hoops_IPSSP[0] == 0 &&
		dc->options._hoops_IPSSP[1] == 0 &&
		dc->options._hoops_IPSSP[2] == 0) {
		/* _hoops_CHIA _hoops_GAR _hoops_IRS _hoops_RSRA _hoops_PHI */

		if (start < 0) {
			*fixed = dc->current._hoops_AAPSR/2; /* _hoops_AGSIP! */
			if (*fixed < 8 && dc->current._hoops_AAPSR >= 8)
				*fixed = 8;		/* _hoops_PPSI _hoops_IRS _hoops_SSGRH _hoops_GPP _hoops_SCH */
		}
		else if (start > dc->current._hoops_AAPSR) {
			_hoops_PHPGR (HEC_COLOR, HES_TOO_MANY_FIXED_COLORS,
					"'fixed colors' is greater than 'number of colors' -",
						 "allocating as many fixed colors as possible");
			*fixed = dc->current._hoops_AAPSR;
		}
		else {
			*fixed = start;
		}

		if (*fixed >= 216) {
			*fixed = 216;
			_hoops_CAGCR[0] = _hoops_CAGCR[1] = _hoops_CAGCR[2] = 6;
		}
		else if (*fixed >= 125) {
			*fixed = 125;
			_hoops_CAGCR[0] = _hoops_CAGCR[1] = _hoops_CAGCR[2] = 5;
		}
		else if (*fixed >= 64) {
			*fixed = 64;
			_hoops_CAGCR[0] = _hoops_CAGCR[1] = _hoops_CAGCR[2] = 4;
		}
		else if (*fixed >= 27) {
			*fixed = 27;
			_hoops_CAGCR[0] = _hoops_CAGCR[1] = _hoops_CAGCR[2] = 3;
		}
		else if (*fixed >= 8) {
			*fixed = 8;
			_hoops_CAGCR[0] = _hoops_CAGCR[1] = _hoops_CAGCR[2] = 2;
		}
		else {
			*fixed = 0;
			_hoops_CAGCR[0] = _hoops_CAGCR[1] = _hoops_CAGCR[2] = 0;
		}
	}
	else {
		/* _hoops_CHIA _hoops_GAR _hoops_HRSP _hoops_RGGHR */
		bool		_hoops_SACPA = false;

		_hoops_CAGCR[0] = dc->options._hoops_IPSSP[0];
		_hoops_CAGCR[1] = dc->options._hoops_IPSSP[1];
		_hoops_CAGCR[2] = dc->options._hoops_IPSSP[2];

		if (start < 0) {		/* _hoops_PAH _hoops_RGR _hoops_AGIR _hoops_PRGI _hoops_IHPS? */
			*fixed = dc->current._hoops_AAPSR/2; /* _hoops_AHGC! */
			if (*fixed < 8 && dc->current._hoops_AAPSR >= 8) {
				*fixed = 8;		/* _hoops_PPSI _hoops_IRS _hoops_SSGRH _hoops_GPP _hoops_SCH */
				_hoops_CAGCR[0] = _hoops_CAGCR[1] = _hoops_CAGCR[2] = 2;
				return;
			}
			_hoops_SACPA = true;
		}
		else if (start > dc->current._hoops_AAPSR) {
			_hoops_PHPGR (HEC_COLOR, HES_TOO_MANY_FIXED_COLORS,
					"'fixed colors' is greater than 'number of colors' -",
						 "allocating as many fixed colors as possible");
			*fixed = dc->current._hoops_AAPSR;
			_hoops_SACPA = true;
		}
		else {
			*fixed = start;
			if (_hoops_CAGCR[0] >= 2 && _hoops_CAGCR[1] >= 2 && _hoops_CAGCR[2] >= 2)
				return;			/* _hoops_HCR _hoops_IHRI */
		}

		if (dc->options._hoops_IPSSP[0] < 2 ||
			dc->options._hoops_IPSSP[1] < 2 ||
			dc->options._hoops_IPSSP[2] < 2)
			_hoops_SACPA = true;

		if (_hoops_SACPA) {
			/* _hoops_RGR _hoops_CGH _hoops_HGCR _hoops_AHGSP _hoops_PPR _hoops_HPPR _hoops_IS _hoops_RCPS _hoops_GH _hoops_CCA _hoops_CPHP
			** _hoops_CCA _hoops_RH _hoops_PSHR _hoops_RHAR _hoops_RIRPA _hoops_GAR _hoops_HGRC. _hoops_IH _hoops_HA, _hoops_SGH _hoops_IRS _hoops_ASRH */

			if (*fixed >= 216) {
				*fixed = 216;
				_hoops_CAGCR[0] = _hoops_CAGCR[1] = _hoops_CAGCR[2] = 6;
			}
			else if (*fixed >= 125) {
				*fixed = 125;
				_hoops_CAGCR[0] = _hoops_CAGCR[1] = _hoops_CAGCR[2] = 5;
			}
			else if (*fixed >= 64) {
				*fixed = 64;
				_hoops_CAGCR[0] = _hoops_CAGCR[1] = _hoops_CAGCR[2] = 4;
			}
			else if (*fixed >= 27) {
				*fixed = 27;
				_hoops_CAGCR[0] = _hoops_CAGCR[1] = _hoops_CAGCR[2] = 3;
			}
			else if (*fixed >= 8) {
				*fixed = 8;
				_hoops_CAGCR[0] = _hoops_CAGCR[1] = _hoops_CAGCR[2] = 2;
			}
			else {
				*fixed = 0;
				_hoops_CAGCR[0] = _hoops_CAGCR[1] = _hoops_CAGCR[2] = 0;
			}
		}
	}
}


GLOBAL_FUNCTION void HD_Free_Colors (
	Display_Context alter		*dc) {

	if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
		if (dc->_hoops_RRPGH != null) {
			_hoops_SHHHP const	*sc,
													*next;
			sc = dc->_hoops_RRPGH;
			do {
				next = sc->next;
				FREE (sc, _hoops_SHHHP);
			}
			_hoops_RGGA ((sc = next) == null);
			dc->_hoops_RRPGH = null;
		}

		if (dc->_hoops_ARPGH != null) {
			_hoops_SHHHP const	*sc,
													*next;
			sc = dc->_hoops_ARPGH;
			do {
				next = sc->next;
				FREE (sc, _hoops_SHHHP);
			}
			_hoops_RGGA ((sc = next) == null);
			dc->_hoops_ARPGH = null;
		}

#ifndef DISABLE_COLOR_MAPS
		if (dc->_hoops_PRPGH != null) {
			_hoops_HIIHP const *_hoops_IIIHP,
												*next;
			_hoops_IIIHP = dc->_hoops_PRPGH;
			do {
				next = _hoops_IIIHP->next;
				_hoops_PGRCA(_hoops_IIIHP->_hoops_IGISP)->_hoops_PPRPR = null;
				_hoops_HPRH (_hoops_IIIHP->_hoops_IGISP);
				FREE (_hoops_IIIHP, _hoops_HIIHP);
			}
			_hoops_RGGA ((_hoops_IIIHP = next) == null);
			dc->_hoops_PRPGH = null;
		}

		if (dc->_hoops_HRPGH != null) {
			_hoops_HIIHP const *_hoops_IIIHP,
												*next;
			_hoops_IIIHP = dc->_hoops_HRPGH;
			do {
				next = _hoops_IIIHP->next;
				_hoops_PGRCA(_hoops_IIIHP->_hoops_IGISP)->_hoops_PPRPR = null;
				_hoops_HPRH (_hoops_IIIHP->_hoops_IGISP);
				FREE (_hoops_IIIHP, _hoops_HIIHP);
			}
			_hoops_RGGA ((_hoops_IIIHP = next) == null);
			dc->_hoops_HRPGH = null;
		}
#endif

		{	int						count;

			count = _hoops_IAAA (dc->_hoops_RIHHP + dc->_hoops_RGPGH,
						 dc->_hoops_GGPGH + dc->_hoops_SSAGH);
			if (count == 0) count = 1;

			FREE_ARRAY (dc->_hoops_CSIR, count, Driver_Color);

			count = dc->_hoops_PGCC._hoops_AAPSR + dc->_hoops_PGCC._hoops_APASR;
			FREE_ARRAY (dc->_hoops_CHHIP, count, RGB);
		}
	}
}


local void alter *_hoops_HHCSC (
	Display_Context alter	*dc,
	RGB const				*rgb) {
	_hoops_SHHHP alter	*_hoops_RSGHR,
											**_hoops_ASRGR;
	float						_hoops_PHHHP;
	Driver_Color				_hoops_CPHHP;
	int							tmp;

	_hoops_PHHHP = dc->_hoops_GRPGH - 0.001f;

	_hoops_CPHHP = _hoops_CAHSR::_hoops_SAHSR;
	/* (_hoops_GGR _hoops_GPGR _hoops_CIGCR _hoops_PGGA _hoops_IIGR _hoops_HICA _hoops_IHCSC) */
	tmp = (int)(rgb->red * _hoops_PHHHP);
	_hoops_CPHHP._hoops_HRIR.r = (unsigned char)tmp;
	tmp = (int)(rgb->green * _hoops_PHHHP);
	_hoops_CPHHP._hoops_HRIR.g = (unsigned char)tmp;
	tmp = (int)(rgb->blue * _hoops_PHHHP);
	_hoops_CPHHP._hoops_HRIR.b = (unsigned char)tmp;
	_hoops_CPHHP._hoops_HRIR.a = _hoops_GPGCR;

	if (dc->_hoops_ARPGH != null) {
		_hoops_RSGHR = dc->_hoops_ARPGH;
		do
			if (_hoops_RSGHR->_hoops_HSHCP == _hoops_CPHHP)
				return (void alter *)_hoops_RSGHR;
		_hoops_RGGA ((_hoops_RSGHR = _hoops_RSGHR->next) == null);
	}

	if (dc->_hoops_RRPGH != null) {
		_hoops_ASRGR = &dc->_hoops_RRPGH;
		_hoops_RSGHR = dc->_hoops_RRPGH;
		do {
			if (_hoops_RSGHR->_hoops_HSHCP == _hoops_CPHHP) {
				*_hoops_ASRGR = _hoops_RSGHR->next;
				_hoops_RSGHR->next = dc->_hoops_ARPGH;
				dc->_hoops_ARPGH = _hoops_RSGHR;
				return (void alter *)_hoops_RSGHR;
			}
			_hoops_ASRGR = &_hoops_RSGHR->next;
		} _hoops_RGGA ((_hoops_RSGHR = _hoops_RSGHR->next) == null);
	}

	ALLOC (_hoops_RSGHR, _hoops_SHHHP);
	_hoops_RSGHR->next = dc->_hoops_ARPGH;
	dc->_hoops_ARPGH = _hoops_RSGHR;
	_hoops_RSGHR->_hoops_HSHCP = _hoops_CPHHP;
	_hoops_RSGHR->index = _hoops_GIHHP;
	return (void alter *)_hoops_RSGHR;
}


local void alter *_hoops_CHCSC (
	Display_Context alter	*dc,
	_hoops_ACSGA const			*list) {

	if (!ANYBIT (list->_hoops_GHA, ~(_hoops_IRARA | Color_LIGHTING)))
		return null;	/* _hoops_SAHR _hoops_IRS _hoops_RCA _hoops_HAIR */

	switch (list->type) {
		case _hoops_SHGRA: {
		}	break;

		case _hoops_PPCA: {
			_hoops_APCA const *		normal = (_hoops_APCA const *)list;

			return _hoops_HHCSC (dc, &normal->rgb);
		}	_hoops_HHHI;

		case _hoops_GIGRA: {
			_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;

			if (BIT (_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA, M_DIFFUSE)) {
				/*
				 * _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_HPHR _hoops_HAIR _hoops_SGS _hoops_PAH _hoops_SSPP
				 * _hoops_GHAA _hoops_IS _hoops_CPAP/_hoops_SPHGR
				 */
				return _hoops_HHCSC (dc, &_hoops_ICSGA->_hoops_ISHIR._hoops_CSHR);
			}
		}	break;
	}

	return null;
}


#ifndef DISABLE_COLOR_MAPS
local void alter *_hoops_SHCSC (
	Display_Context alter	*dc,
	_hoops_RHAH const			*_hoops_CSIR,
	bool					_hoops_CGISP) {
	_hoops_HIIHP alter		*_hoops_RSGHR,
											**_hoops_ASRGR;

	if (_hoops_CSIR->length == 0)
		return null;

	if (dc->_hoops_HRPGH != null) {
		_hoops_RSGHR = dc->_hoops_HRPGH;
		do
			if (_hoops_RSGHR->_hoops_IGISP == _hoops_CSIR)
				return (void alter *)_hoops_RSGHR;
		_hoops_RGGA ((_hoops_RSGHR = _hoops_RSGHR->next) == null);
	}

	if (dc->_hoops_PRPGH != null &&
		!ANYBIT (_hoops_CSIR->_hoops_CPGPR, _hoops_AHSGA|_hoops_CASIR)) {
		_hoops_ASRGR = &dc->_hoops_PRPGH;
		_hoops_RSGHR = dc->_hoops_PRPGH;
		do {
			if (_hoops_RSGHR->_hoops_IGISP == _hoops_CSIR) {
				*_hoops_ASRGR = _hoops_RSGHR->next;
				_hoops_RSGHR->next = dc->_hoops_HRPGH;
				dc->_hoops_HRPGH = _hoops_RSGHR;
				return (void alter *)_hoops_RSGHR;
			}
			_hoops_ASRGR = &_hoops_RSGHR->next;
		} _hoops_RGGA ((_hoops_RSGHR = _hoops_RSGHR->next) == null);
	}

	ALLOC (_hoops_RSGHR, _hoops_HIIHP);
	_hoops_RSGHR->next = dc->_hoops_HRPGH;
	dc->_hoops_HRPGH = _hoops_RSGHR;
	_hoops_RSGHR->_hoops_IGISP = _hoops_CSIR; _hoops_PRRH (_hoops_CSIR);
	_hoops_RSGHR->_hoops_SIIHP = _hoops_GIHHP;
	_hoops_RSGHR->length = _hoops_CSIR->length;
	_hoops_RSGHR->_hoops_CGISP = _hoops_CGISP;
	return (void alter *)_hoops_RSGHR;
}
#endif



local _hoops_ACHR _hoops_GICSC (
	Display_Context alter	*dc,
	Attribute const			*_hoops_ASGPR,
	_hoops_ACHR				_hoops_RGP,
	bool					_hoops_RICSC) {

	do switch (_hoops_ASGPR->type) {
		case HK_COLOR: {
			_hoops_ACSGA const *list = ((_hoops_SSGI *)_hoops_ASGPR)->colors;

			do
				((_hoops_ACSGA alter *)list)->_hoops_PPRPR = _hoops_CHCSC (dc, list);
			while ((list = list->next) != null);
		}	break;

		case HK_COLOR_MAP: {
#ifndef DISABLE_COLOR_MAPS
			((_hoops_RHAH alter *)_hoops_ASGPR)->_hoops_PPRPR =
						_hoops_SHCSC (dc, (_hoops_RHAH const *)_hoops_ASGPR,
										  _hoops_RICSC);
#endif
		}	break;

		case HK_STYLE: {
#ifndef DISABLE_STYLE_SEGMENT
			_hoops_CRCP const	*_hoops_SRCP = ((Style *)_hoops_ASGPR)->_hoops_IGRPR;

			if (ANYBIT (_hoops_SRCP->_hoops_RCGC, _hoops_HPRRA |
									 _hoops_PPHGP |
									 _hoops_RPHGP |
									 _hoops_HPHGP |
									 _hoops_APHGP) &&
				_hoops_SRCP->_hoops_IPPGR != null) {

				_hoops_RGP = _hoops_GICSC (dc, _hoops_SRCP->_hoops_IPPGR, _hoops_RGP,
										  _hoops_RICSC ||
										  ANYBIT (_hoops_ASGPR->_hoops_CPGPR, _hoops_CASIR|_hoops_AHSGA));
			}
#endif
		}	break;

		case HK_VISIBILITY: {
			_hoops_RSAIR const *		vis = (_hoops_RSAIR const *)_hoops_ASGPR;

			_hoops_RGP &= ~vis->mask;
			_hoops_RGP |= vis->value;
		}	break;

		default: {
			if (_hoops_ASGPR->type > _hoops_IAAA(HK_COLOR, HK_COLOR_MAP, HK_STYLE, HK_VISIBILITY))
				return _hoops_RGP;
		}	break;
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	return _hoops_RGP;
}



local void _hoops_AICSC (
	Display_Context alter	*dc,
	Subsegment const *		_hoops_SSGPR,
	_hoops_ACHR				_hoops_RGP,
	bool					_hoops_RICSC) {
	_hoops_CRCP const *			_hoops_SRCP;

	top:;

	do {
		if (_hoops_SSGPR->type == _hoops_IRCP) {
			/* _hoops_PIHA _hoops_GGARP _hoops_HAIR _hoops_ACAR _hoops_RPGCA _hoops_GSGI _hoops_SAPGP _hoops_IS _hoops_PICSC _hoops_SHPH _hoops_HGPP
			** _hoops_GAR _hoops_IRS _hoops_HICSC */
			if (BIT (_hoops_SSGPR->_hoops_CPGPR, _hoops_AHSGA))
				_hoops_RICSC = true;
		}
		else {
			/* _hoops_PIHA _hoops_GGARP _hoops_HAIR _hoops_ACAR _hoops_RPGCA _hoops_GSGI _hoops_SAPGP _hoops_IS _hoops_IRS _hoops_CCAH _hoops_GCIS */
			if (BIT (_hoops_SSGPR->_hoops_CPGPR, _hoops_CASIR))
				_hoops_RICSC = true;
		}
		_hoops_SRCP = _hoops_SSIGP (_hoops_SSGPR);

		/* _hoops_IICSC _hoops_HII _hoops_PCSS... */

		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR) &&
			(BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GCHGP) ||
			(!BIT (_hoops_RGP, T_WINDOWS) &&
			 !BIT (_hoops_SRCP->_hoops_RCGC, _hoops_HPHGP)))) {
		}
		else if (1) {
#if				0
				 /*
				  * _hoops_RHRRA
				  *
				  * _hoops_CICSC _hoops_CCA _hoops_RRGSI _hoops_AHCA _hoops_RGR _hoops_SPR - _hoops_SR _hoops_CPSA _hoops_RRP _hoops_IS _hoops_RCPS _hoops_GH
				  * _hoops_CCA _hoops_IRS _hoops_GIH _hoops_RPGP _hoops_HIH _hoops_SCH _hoops_HRGR _hoops_PSP _hoops_IHGP _hoops_RPSHR - _hoops_RGR _hoops_CGH
				  * _hoops_IPHR _hoops_HIH _hoops_SCH _hoops_GRS _hoops_GGHC _hoops_IHHH _hoops_IS _hoops_SHGR _hoops_IRS _hoops_AHCPR _hoops_RRI _hoops_AAGAI _hoops_HSAR
				  * _hoops_SR _hoops_CPSA _hoops_RRP _hoops_IS.
				  * _hoops_RRGSI _hoops_GRS _hoops_RARI _hoops_CGPR _hoops_IRISP _hoops_SSCP _hoops_GHIR
				  */
				   (ANYBIT (_hoops_SRCP->_hoops_RCGC, _hoops_HPRRA |
									   _hoops_RPHGP) &&
				  /* _hoops_AGGC (_hoops_PHHIP->_hoops_SGHGP, _hoops_SICSC) && */
				  (ANYBIT (_hoops_RGP, _hoops_AAHGP) ||
				   BIT (_hoops_SRCP->_hoops_RCGC, _hoops_APHGP))) ||

				 (ANYBIT (_hoops_SRCP->_hoops_RCGC, _hoops_HPRRA |
									   _hoops_PPHGP) &&
				  (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR) ||
				   BIT (_hoops_SRCP->_hoops_RCGC, T_WINDOWS)) &&
				  (BIT (_hoops_RGP, T_WINDOWS) ||
				   BIT (_hoops_SRCP->_hoops_RCGC, _hoops_HPHGP)))) {
#endif

			_hoops_ACHR	_hoops_GCCSC;

			if (BIT (_hoops_SRCP->_hoops_RCGC, _hoops_HPRRA)) {
				if (_hoops_SRCP->_hoops_IPPGR == null)
					_hoops_GCCSC = _hoops_RGP;
				else
					_hoops_GCCSC = _hoops_GICSC (dc, _hoops_SRCP->_hoops_IPPGR, _hoops_RGP, _hoops_RICSC);

				if (_hoops_SRCP->geometry != null) {
					Geometry const * geom = _hoops_SRCP->geometry;

					do if (geom->_hoops_IPPGR != null) {
						_hoops_GICSC (dc, geom->_hoops_IPPGR, _hoops_RGP, _hoops_RICSC);
					} while ((geom = geom->next) != null);
				}

				if (_hoops_SRCP->_hoops_RGRPR != null) {
					if (_hoops_SSGPR->next == null) {
						_hoops_SSGPR = _hoops_SRCP->_hoops_RGRPR;
						_hoops_RGP = _hoops_GCCSC;
						goto top;
					}
					else {
						_hoops_AICSC (dc, _hoops_SRCP->_hoops_RGRPR, _hoops_GCCSC, _hoops_RICSC);
					}
				}
			}
		}
	} while ((_hoops_SSGPR = _hoops_SSGPR->next) != null);
}


local void _hoops_RCCSC (
	_hoops_CRCP const		*_hoops_SRCP,
	Attribute alter		* alter *_hoops_ACCSC,
	_hoops_HHAGP alter *locks,
	Color_Object alter	*color_locks,
	bool alter		   *_hoops_CGISP) {
	Attribute alter		*_hoops_ASGPR;
	_hoops_HHAGP		_hoops_PCCSC = false;
	Color_Object			_hoops_HCCSC = false;

	if ((_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR) != null) {
		/* _hoops_RRP _hoops_IS _hoops_CGIC _hoops_SGHS _hoops_SRS */
		{
			Attribute alter	*_hoops_HPGIP = _hoops_ASGPR;

			do {
				if (_hoops_ASGPR->type > HK_RENDERING_OPTIONS)
					break;

				if (_hoops_ASGPR->type == HK_RENDERING_OPTIONS) {
					_hoops_RHAIR const	*_hoops_AHAIR =
										(_hoops_RHAIR const *)_hoops_ASGPR;

					if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_GSIAA)) {
						if (BIT (_hoops_AHAIR->_hoops_RSIAA, _hoops_GSIAA)) {
							/* _hoops_SSIAA _hoops_GII _hoops_AIRC _hoops_HSGRA _hoops_ARI */
							*locks &= ~_hoops_AHAIR->locks->normal.mask._hoops_IPPGR;

							/* _hoops_PPR _hoops_PCSA _hoops_AGAP _hoops_IS _hoops_ARP _hoops_CGPR _hoops_SR _hoops_HPIRA */
							_hoops_PCCSC = _hoops_AHAIR->locks->normal.value._hoops_IPPGR;

							/* _hoops_PPR _hoops_IH _hoops_PSHA */
							if (BIT (_hoops_AHAIR->locks->normal.mask._hoops_IPPGR, _hoops_GGCAA(HK_COLOR))) {
								*color_locks &= _hoops_AHAIR->locks->normal.mask.color;
								_hoops_HCCSC = _hoops_AHAIR->locks->normal.value.color;
							}
							else
								*color_locks = 0;
						}
						else {
							/* _hoops_SSIAA _hoops_CPS */
							*locks = 0;
							*color_locks = 0;
						}
					}

					break;
				}
			} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

			_hoops_ASGPR = _hoops_HPGIP;
		}


		do switch (_hoops_ASGPR->type) {
			case HK_COLOR: if (!ALLBITS(*color_locks, Color_EVERYTHING)) {
				if (_hoops_ACCSC[(int)HK_COLOR] != null) {
					_hoops_SSGI const * color = (_hoops_SSGI const *)_hoops_ASGPR;
					HI_Merge_Colors ((_hoops_SSGI alter *)_hoops_ACCSC[(int)HK_COLOR], color->colors, null, null);
				}
			}	break;

			case HK_COLOR_MAP: if (!BIT(*locks, _hoops_GGCAA(HK_COLOR_MAP))) {
#ifndef DISABLE_COLOR_MAPS
				_hoops_ACCSC[(int)HK_COLOR_MAP] = _hoops_ASGPR;
#endif
			}	break;


			case HK_SELECTABILITY: if (!BIT(*locks, _hoops_GGCAA(HK_SELECTABILITY))) {
				_hoops_ASAIR const	*	as = (_hoops_ASAIR const *)_hoops_ASGPR;
				_hoops_ASAIR alter	*	s = (_hoops_ASAIR alter *)_hoops_ACCSC[(int)HK_SELECTABILITY];

				if (s != null) {
					s->up &= ~as->mask;
					s->down &= ~as->mask;
					s->_hoops_RHARP &= ~as->mask;
					s->_hoops_AHARP &= ~as->mask;
					s->_hoops_PHARP &= ~as->mask;
					s->mask |= as->mask;
					s->up |= as->up;
					s->down |= as->down;
					s->_hoops_RHARP |= as->_hoops_RHARP;
					s->_hoops_AHARP |= as->_hoops_AHARP;
					s->_hoops_PHARP |= as->_hoops_PHARP;
					s->_hoops_HHARP = s->up|s->down|s->_hoops_RHARP|s->_hoops_AHARP;
				}
			}	break;

			case HK_STYLE: if (!BIT(*locks, _hoops_GGCAA(HK_STYLE))) {
#ifndef DISABLE_STYLE_SEGMENT
				if (ANYBIT (_hoops_ASGPR->_hoops_CPGPR, _hoops_CASIR|_hoops_AHSGA))
					*_hoops_CGISP = true;

				_hoops_RCCSC (((Style *)_hoops_ASGPR)->_hoops_IGRPR, _hoops_ACCSC,
										locks, color_locks, _hoops_CGISP);
#endif
			}	break;

			case HK_VISIBILITY: if (!BIT(*locks, _hoops_GGCAA(HK_VISIBILITY))) {
				_hoops_RSAIR const *	_hoops_ICCSC = (_hoops_RSAIR const *)_hoops_ASGPR;
				_hoops_RSAIR alter *	v = (_hoops_RSAIR alter *)_hoops_ACCSC[(int)HK_VISIBILITY];

				v->value &= ~_hoops_ICCSC->mask;
				v->value |= _hoops_ICCSC->value;
			}	break;

			default: {
				if (_hoops_ASGPR->type > _hoops_IAAA (HK_COLOR, HK_COLOR_MAP, HK_SELECTABILITY, HK_STYLE, HK_VISIBILITY))
					return;
			}	break;
		} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

		/* _hoops_ARP _hoops_HCR _hoops_CISI _hoops_SGHS */
		*locks |= _hoops_PCCSC;
		*color_locks |= _hoops_HCCSC;
	}
}


local void _hoops_CCCSC (
	_hoops_CRCP const *				_hoops_SRCP,
	Attribute alter * alter *	_hoops_ACCSC,
	_hoops_HHAGP alter *		locks,
	Color_Object alter *		color_locks,
	bool alter *				_hoops_CGISP) {
	_hoops_CRCP *					owner = _hoops_SRCP->owner;

	while (owner->type != _hoops_PRAIR) {
		if (owner->type == _hoops_IRCP) {
			_hoops_CCCSC (owner, _hoops_ACCSC, locks, color_locks, _hoops_CGISP);
			break;
		}
		else if (owner->type == _hoops_PIRIR) {
			// _hoops_IPCA _hoops_GH
			owner = owner->owner;
		}
		else
			return;
	}

	_hoops_RCCSC (_hoops_SRCP, _hoops_ACCSC, locks, color_locks, _hoops_CGISP);
}


local void _hoops_SCCSC (
	Display_Context alter	*dc,
	int							index) {
	Driver_Color const		*_hoops_CPHHP = &dc->_hoops_CSIR[index];
	int							r, g, b;
	int							_hoops_GSCSC,
											_hoops_RSCSC;
	float						scale;
	RGB alter				*_hoops_SPRAR;

	/* _hoops_ASH _hoops_SGGR _hoops_IHIR _hoops_HGGPA _hoops_PIRA */
	scale = 1.0f / (dc->_hoops_GRPGH - 1);

	_hoops_SPRAR = (RGB alter *)&dc->_hoops_CHHIP[index];
	_hoops_SPRAR->red	= _hoops_IRGCR(_hoops_CPHHP->_hoops_HRIR.r) * scale;
	_hoops_SPRAR->green	= _hoops_IRGCR(_hoops_CPHHP->_hoops_HRIR.g) * scale;
	_hoops_SPRAR->blue	= _hoops_IRGCR(_hoops_CPHHP->_hoops_HRIR.b) * scale;

	/* _hoops_GAASP _hoops_SIISR... */
	_hoops_GSCSC = dc->_hoops_GRPGH - 1;
	_hoops_RSCSC = dc->_hoops_PGCC._hoops_PCHSR - 1;

	/* (_hoops_RGR _hoops_HRGR _hoops_HCR _hoops_PHPH _hoops_GGSR _hoops_GGR _hoops_SIH _hoops_PPR _hoops_SCSHR _hoops_PGGA _hoops_IIGR _hoops_ASCSC
	 *	_hoops_IHCSC _hoops_GPP _hoops_AGRR _hoops_AARRH.) (_hoops_RH 0xFF'_hoops_GRI _hoops_CHR _hoops_IH _hoops_AARRH
	 *	_hoops_SGS _hoops_GA'_hoops_RA _hoops_PGSPC _hoops_APPC _hoops_GSPR'_hoops_GRI.)
	 */

	r = 0xFF & (int)_hoops_CPHHP->_hoops_HRIR.r;
	r = 0xFF & (int)dc->_hoops_PGCC._hoops_HHHHP[(r * _hoops_RSCSC) / _hoops_GSCSC];

	g = 0xFF & (int)_hoops_CPHHP->_hoops_HRIR.g;
	g = 0xFF & (int)dc->_hoops_PGCC._hoops_HHHHP[(g * _hoops_RSCSC) / _hoops_GSCSC];

	b = 0xFF & (int)_hoops_CPHHP->_hoops_HRIR.b;
	b = 0xFF & (int)dc->_hoops_PGCC._hoops_HHHHP[(b * _hoops_RSCSC) / _hoops_GSCSC];

	(*dc->_hoops_ACPGR->_hoops_SCCSR)(dc, r, g, b, index);
}

#ifndef DISABLE_COLOR_MAPS
local bool _hoops_PSCSC (
	Display_Context alter	*dc) {
	_hoops_HIIHP const		*_hoops_IIIHP;
	Driver_Color alter		*_hoops_CPHHP;
	Driver_Color const		*_hoops_HSCSC;

	_hoops_CPHHP = (Driver_Color alter *)&dc->_hoops_CSIR[dc->_hoops_GGPGH];
	if ((_hoops_IIIHP = dc->_hoops_HRPGH) != null)
	do if (_hoops_IIIHP->_hoops_SIIHP != _hoops_GIHHP) {
		_hoops_GARSR	_hoops_RSASR;

		_hoops_RSASR = _hoops_CPHHP - &dc->_hoops_CSIR[dc->_hoops_GGPGH];

		if (_hoops_RSASR == _hoops_IIIHP->_hoops_SIIHP)
			_hoops_CPHHP += _hoops_IIIHP->length;
		else {
			float						_hoops_PHHHP;
			Named_Material const *_hoops_ISHIR;
			int							count,
													tmp;

			/* _hoops_HHSA _hoops_IRS _hoops_IHIR _hoops_AIIAP... */
			dc->_hoops_CPGPR = _hoops_RCGSA;
			dc->_hoops_HSPGH = _hoops_RCGSA;

			_hoops_PHHHP = dc->_hoops_GRPGH - 0.001f;
			count = 0;
			_hoops_ISHIR = _hoops_IIIHP->_hoops_IGISP->_hoops_HAA;

			do {
				tmp = (int)(_hoops_ISHIR->_hoops_CSHR.red * _hoops_PHHHP);
				_hoops_CPHHP->_hoops_HRIR.r = (unsigned char)tmp;
				tmp = (int)(_hoops_ISHIR->_hoops_CSHR.green * _hoops_PHHHP);
				_hoops_CPHHP->_hoops_HRIR.g = (unsigned char)tmp;
				tmp = (int)(_hoops_ISHIR->_hoops_CSHR.blue * _hoops_PHHHP);
				_hoops_CPHHP->_hoops_HRIR.b = (unsigned char)tmp;
				_hoops_CPHHP->_hoops_HRIR.a = _hoops_GPGCR;
				_hoops_SCCSC (dc, (int)_hoops_IIIHP->_hoops_SIIHP + count);
				++_hoops_ISHIR;
				++_hoops_CPHHP;
			} _hoops_RGGA (++count == _hoops_IIIHP->length);
		}
	} _hoops_RGGA ((_hoops_IIIHP = _hoops_IIIHP->next) == null);

	_hoops_HSCSC = &dc->_hoops_CSIR[dc->_hoops_GGPGH + dc->_hoops_SSAGH];

	if (_hoops_CPHHP == _hoops_HSCSC)
		return false;
	else {
		do
			_hoops_CPHHP[0] = _hoops_IAASP;
		_hoops_RGGA (++_hoops_CPHHP == _hoops_HSCSC);
		return true;
	}
}
#endif


local bool _hoops_ISCSC (
	Display_Context alter	*dc) {
	_hoops_SHHHP alter	*sc;
	Driver_Color alter		*_hoops_CPHHP;
	Driver_Color const		*_hoops_HSCSC;

	_hoops_CPHHP = (Driver_Color alter *)&dc->_hoops_CSIR[dc->_hoops_RIHHP];
	if ((sc = dc->_hoops_ARPGH) != null)
	do if (sc->index != _hoops_GIHHP) {
		_hoops_GARSR	_hoops_RSASR;

		_hoops_RSASR = _hoops_CPHHP - &dc->_hoops_CSIR[dc->_hoops_RIHHP];

		if (_hoops_RSASR == sc->index)
			++_hoops_CPHHP;
		else {
			/* _hoops_HHSA _hoops_IRS _hoops_IHIR _hoops_AIIAP... */
			dc->_hoops_CPGPR = _hoops_RCGSA;
			dc->_hoops_HSPGH = _hoops_RCGSA;

			*_hoops_CPHHP = sc->_hoops_HSHCP;
			sc->index = _hoops_RSASR;
			++_hoops_CPHHP;
		}
	} while ((sc = sc->next) != null);

	_hoops_HSCSC = &dc->_hoops_CSIR[dc->_hoops_RIHHP + dc->_hoops_RGPGH];

	if (_hoops_CPHHP == _hoops_HSCSC)
		return false;
	else {
		do
			_hoops_CPHHP[0] = _hoops_IAASP;
		_hoops_RGGA (++_hoops_CPHHP == _hoops_HSCSC);
		return true;
	}
}


local void _hoops_AARHP (
	Display_Context alter	*dc) {
	int							_hoops_CSCSC = 0,
											_hoops_SSCSC = 0;
	char						buf[MAX_ERRMSG],
											buf2[MAX_ERRMSG];

	{	_hoops_SHHHP const		*sc;

		if ((sc = dc->_hoops_ARPGH) != null) {
			do
				++_hoops_CSCSC;
			_hoops_RGGA ((sc = sc->next) == null);
		}
	}

#ifndef DISABLE_COLOR_MAPS
	{	_hoops_HIIHP const			*_hoops_IIIHP;

		if ((_hoops_IIIHP = dc->_hoops_HRPGH) != null) {
			do
				_hoops_SSCSC += _hoops_IIIHP->length;
			_hoops_RGGA ((_hoops_IIIHP = _hoops_IIIHP->next) == null);
		}
	}
#endif

	Sprintf_DD (buf,
		"You need %d regular, %d 'fixed', and %%d 'color map' colors,",
		_hoops_CSCSC, dc->_hoops_GCPRP);

	_hoops_ARGIP (HEC_COLOR, HES_TOO_MANY_COLORS,
			"You are trying to use too many colors -",
		Sprintf_D (buf2, buf, _hoops_SSCSC),
		Sprintf_D (null,
				"but your net available 'number of colors' is only %d.)",
				dc->_hoops_GCPRP + dc->_hoops_SSAGH + dc->_hoops_RGPGH));

	dc->_hoops_IRPGH = false;
}


local _hoops_GARSR _hoops_GGSSC (
	Display_Context alter	*dc) {

	if ((dc->_hoops_RIHHP > dc->_hoops_GGPGH &&
		 dc->_hoops_CSIR[dc->_hoops_RIHHP - 1] == _hoops_IAASP)
#ifndef DISABLE_COLOR_MAPS
		 || _hoops_PSCSC (dc)
#endif
		) {

		++dc->_hoops_RGPGH;
		--dc->_hoops_RIHHP;
		return (_hoops_GARSR)dc->_hoops_RIHHP;
	}
	else {
		if (dc->_hoops_IRPGH)
			_hoops_AARHP (dc);
		return _hoops_GIHHP;
	}
}


local _hoops_GARSR _hoops_RGSSC (
	Display_Context alter	*dc,
	int							length) {
	Driver_Color alter		*_hoops_CPHHP;
	Driver_Color const		*_hoops_HSCSC;
	Driver_Color alter		*_hoops_HRISA;
	int							_hoops_AGSSC,
											_hoops_PGSSC;

	_hoops_CPHHP = (Driver_Color alter *)&dc->_hoops_CSIR[dc->_hoops_RIHHP];
	_hoops_HSCSC = &dc->_hoops_CSIR[dc->_hoops_RIHHP + dc->_hoops_RGPGH];
	_hoops_HRISA = _hoops_CPHHP;
	while (_hoops_CPHHP < _hoops_HSCSC && *_hoops_CPHHP == _hoops_IAASP) ++_hoops_CPHHP;
	_hoops_AGSSC = _hoops_CPHHP - _hoops_HRISA;

	_hoops_CPHHP = (Driver_Color alter *)&dc->_hoops_CSIR[dc->_hoops_RIHHP - 1];
	_hoops_HSCSC = &dc->_hoops_CSIR[dc->_hoops_GGPGH];
	_hoops_HRISA = _hoops_CPHHP;
	while (_hoops_CPHHP >= _hoops_HSCSC && *_hoops_CPHHP == _hoops_IAASP) --_hoops_CPHHP;
	_hoops_PGSSC = _hoops_HRISA - _hoops_CPHHP;

	if (_hoops_PGSSC + _hoops_AGSSC < length)
		return _hoops_GIHHP;
	else {
		_hoops_GARSR			start;

		start = dc->_hoops_RIHHP - _hoops_PGSSC;
		length -= _hoops_PGSSC;
		dc->_hoops_SSAGH += length;
		dc->_hoops_RGPGH -= length;
		dc->_hoops_RIHHP += length;

		return start;
	}
}


local _hoops_GARSR _hoops_HGSSC (
	Display_Context alter	*dc,
	int							length) {
	_hoops_GARSR				where;

	where = _hoops_RGSSC (dc, length);
	if (where != _hoops_GIHHP)
		return where;

#ifndef DISABLE_COLOR_MAPS
	if (_hoops_PSCSC (dc)) {
		where = _hoops_RGSSC (dc, length);
		if (where != _hoops_GIHHP)
			return where;
	}
#endif

	if (_hoops_ISCSC (dc)) {
		where = _hoops_RGSSC (dc, length);
		if (where != _hoops_GIHHP)
			return where;
	}

	if (dc->_hoops_IRPGH)
		_hoops_AARHP (dc);
	return _hoops_GIHHP;
}


local void _hoops_IGSSC (
	Display_Context alter	*dc) {
	Driver_Color alter		*_hoops_CPHHP;
	_hoops_SHHHP alter	*sc;
	_hoops_HIIHP alter		*_hoops_IIIHP;

	if ((sc = dc->_hoops_RRPGH) != null) {
		_hoops_SHHHP alter		*next;

		_hoops_CPHHP = (Driver_Color alter *)dc->_hoops_CSIR;

		do {
			if (sc->index != _hoops_GIHHP)
				_hoops_CPHHP[sc->index] = _hoops_IAASP;
			next = sc->next;
			FREE (sc, _hoops_SHHHP);
		} _hoops_RGGA ((sc = next) == null);

		dc->_hoops_RRPGH = null;
	}

#ifndef DISABLE_COLOR_MAPS
	if ((_hoops_IIIHP = dc->_hoops_PRPGH) != null) {
		_hoops_HIIHP alter			*next;

		do {
			_hoops_PGRCA(_hoops_IIIHP->_hoops_IGISP)->_hoops_PPRPR = null;
			_hoops_HPRH (_hoops_IIIHP->_hoops_IGISP);

			if (_hoops_IIIHP->_hoops_SIIHP != _hoops_GIHHP) {
				Driver_Color const	*limit;

				_hoops_CPHHP = (Driver_Color alter *)&dc->_hoops_CSIR[_hoops_IIIHP->_hoops_SIIHP];
				limit = _hoops_CPHHP + _hoops_IIIHP->length;

				do
					*_hoops_CPHHP = _hoops_IAASP;
				_hoops_RGGA (++_hoops_CPHHP == limit);
			}
			next = _hoops_IIIHP->next;
			FREE (_hoops_IIIHP, _hoops_HIIHP);
		} _hoops_RGGA ((_hoops_IIIHP = next) == null);

		dc->_hoops_PRPGH = null;
	}
#endif

	/* _hoops_HPPR _hoops_IS _hoops_IPASR _hoops_GSPCR */

	if ((sc = dc->_hoops_ARPGH) != null) {
		Driver_Color alter	*_hoops_CGSSC;

		_hoops_CPHHP = (Driver_Color alter *)dc->_hoops_CSIR;

		/* _hoops_CCPP _hoops_HII _hoops_RH _hoops_CASH _hoops_RSGR _hoops_CPIC _hoops_ISHP */
		_hoops_CGSSC = &_hoops_CPHHP[dc->_hoops_RIHHP];
		_hoops_CPHHP = _hoops_CGSSC + dc->_hoops_RGPGH;

		do if (sc->index == _hoops_GIHHP) {
			_hoops_PCCAR {
				if (_hoops_CPHHP <= _hoops_CGSSC) {
					sc->index = _hoops_GGSSC (dc);
					if (sc->index != _hoops_GIHHP) {
						((Driver_Color alter *)dc->_hoops_CSIR)
							  [sc->index] = sc->_hoops_HSHCP;
						_hoops_SCCSC (dc, (int)sc->index);
					}
					break;
				}

				--_hoops_CPHHP;

				if (*_hoops_CPHHP == _hoops_IAASP) {
					sc->index = _hoops_CPHHP - dc->_hoops_CSIR;
					*_hoops_CPHHP = sc->_hoops_HSHCP;
					_hoops_SCCSC (dc, (int)sc->index);
					break;
				}
			}
		} while ((sc = sc->next) != null);
	}

#ifndef DISABLE_COLOR_MAPS
	if ((_hoops_IIIHP = dc->_hoops_HRPGH) != null) do {
		if (_hoops_IIIHP->_hoops_SIIHP == _hoops_GIHHP) {
			/* _hoops_SSS _hoops_IRS _hoops_AHSC _hoops_RAPR _hoops_IRPCI _hoops_IIGR _hoops_CIH _hoops_PSHA, _hoops_RPP _hoops_SSRR */

			Driver_Color const	*_hoops_SGSSC;

			/* _hoops_GRSSC _hoops_CPIC _hoops_GH */

			_hoops_CPHHP = (Driver_Color alter *)&dc->_hoops_CSIR[dc->_hoops_GGPGH - 1];
			_hoops_SGSSC = _hoops_CPHHP + dc->_hoops_SSAGH - _hoops_IIIHP->length + 2;

			_hoops_PCCAR {
				Driver_Color const	*_hoops_SHGCR,
												*_hoops_RRSSC;

				do if (++_hoops_CPHHP >= _hoops_SGSSC) {
					_hoops_IIIHP->_hoops_SIIHP = _hoops_HGSSC (dc, _hoops_IIIHP->length);
					goto _hoops_PCPPR;
				} while (*_hoops_CPHHP != _hoops_IAASP);

				_hoops_SHGCR = _hoops_CPHHP;
				_hoops_RRSSC = _hoops_CPHHP + _hoops_IIIHP->length;

				do if (++_hoops_CPHHP == _hoops_RRSSC) {
					_hoops_IIIHP->_hoops_SIIHP = _hoops_SHGCR - dc->_hoops_CSIR;
					goto _hoops_PCPPR;
				} while (*_hoops_CPHHP == _hoops_IAASP);
			}
			_hoops_PCPPR:;
		}

		/* _hoops_HA _hoops_GGARP _hoops_IRS _hoops_CCAH _hoops_ARCR, _hoops_PAR _hoops_SGCSR _hoops_PCCP _hoops_RHGS _hoops_SRSS _hoops_SPR */
		if (_hoops_IIIHP->_hoops_SIIHP != _hoops_GIHHP	 &&
			(_hoops_IIIHP->_hoops_CGISP || ANYBIT (_hoops_IIIHP->_hoops_IGISP->_hoops_CPGPR,
										_hoops_AHSGA|_hoops_CASIR))) {
			float						_hoops_PHHHP;
			Named_Material const *_hoops_ISHIR;
			int							count,
															tmp;

			_hoops_PHHHP = dc->_hoops_GRPGH - 0.001f;
			_hoops_CPHHP = (Driver_Color alter *)&dc->_hoops_CSIR[_hoops_IIIHP->_hoops_SIIHP];
			count = 0;
			_hoops_ISHIR = _hoops_IIIHP->_hoops_IGISP->_hoops_HAA;

			do {
				tmp = (int)(_hoops_ISHIR->_hoops_CSHR.red * _hoops_PHHHP);
				_hoops_CPHHP->_hoops_HRIR.r = (unsigned char)tmp;
				tmp = (int)(_hoops_ISHIR->_hoops_CSHR.green * _hoops_PHHHP);
				_hoops_CPHHP->_hoops_HRIR.g = (unsigned char)tmp;
				tmp = (int)(_hoops_ISHIR->_hoops_CSHR.blue * _hoops_PHHHP);
				_hoops_CPHHP->_hoops_HRIR.b = (unsigned char)tmp;
				_hoops_CPHHP->_hoops_HRIR.a = _hoops_GPGCR;
				_hoops_SCCSC (dc, (int)_hoops_IIIHP->_hoops_SIIHP + count);
				++_hoops_ISHIR, ++_hoops_CPHHP, ++count;
			} _hoops_RGGA (count == _hoops_IIIHP->length);

			_hoops_IIIHP->_hoops_CGISP = false;
		}
	} _hoops_RGGA ((_hoops_IIIHP = _hoops_IIIHP->next) == null);
#endif
}


local void _hoops_ARSSC (
	Display_Context alter	*dc,
	_hoops_SSGI const				*color) {
	_hoops_ACSGA const			*list = color->colors;

	dc->_hoops_GHHHP = _hoops_CAHSR::_hoops_SAHSR; /* (_hoops_CASI _hoops_SCH) */
	dc->_hoops_SPHHP = _hoops_CAHSR::_hoops_SAHSR;
	dc->_hoops_HAHHP = false;

	/* _hoops_HPCAR _hoops_RPPS _hoops_HRGR _hoops_APRP... */
	if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
		_hoops_SHHHP const	*_hoops_CRIRH,
								*_hoops_HCGRC;

		dc->_hoops_RRPGH = dc->_hoops_ARPGH;
		dc->_hoops_ARPGH = null;
		dc->_hoops_PRPGH = dc->_hoops_HRPGH;
		dc->_hoops_HRPGH = null;

		_hoops_CRIRH = (_hoops_SHHHP const *)_hoops_HHCSC(dc, &_hoops_GPSR::_hoops_IAHHP);
		_hoops_HCGRC = (_hoops_SHHHP const *)_hoops_HHCSC(dc, &_hoops_GPSR::_hoops_RPSR);

		_hoops_IGSSC (dc);

		dc->_hoops_SPHHP._hoops_PGGCR = _hoops_CRIRH->index;
		dc->_hoops_GHHHP._hoops_PGGCR = _hoops_HCGRC->index;
	}
	else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) {
		unsigned char			_hoops_PRSSC;

		_hoops_PRSSC = (unsigned char)(dc->_hoops_PGCC._hoops_PCHSR - 1);

		dc->_hoops_SPHHP._hoops_HRIR.r = _hoops_PRSSC;
		dc->_hoops_SPHHP._hoops_HRIR.g = _hoops_PRSSC;
		dc->_hoops_SPHHP._hoops_HRIR.b = _hoops_PRSSC;
		dc->_hoops_SPHHP._hoops_HRIR.a = _hoops_GPGCR;
		dc->_hoops_GHHHP._hoops_HRIR.r = 0;
		dc->_hoops_GHHHP._hoops_HRIR.g = 0;
		dc->_hoops_GHHHP._hoops_HRIR.b = 0;
		dc->_hoops_GHHHP._hoops_HRIR.a = _hoops_GPGCR;
	}
	else /* _hoops_AIHHP */ {
		dc->_hoops_SPHHP._hoops_PIHHP =
			dc->_hoops_PGCC._hoops_PCHSR - 1;
		dc->_hoops_GHHHP._hoops_PIHHP = 0;
	}

	while (!BIT (list->_hoops_GHA, Color_WINDOW))
		list = list->next;

	_hoops_APCA const *		normal = (_hoops_APCA const *)list;
	_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;
	if (list->type == _hoops_PPCA && normal->rgb._hoops_CPIR() >= 0.5f ||
		list->type == _hoops_GIGRA && _hoops_ICSGA->_hoops_ISHIR._hoops_CSHR._hoops_CPIR() >= 0.5f) {
		/* _hoops_RPPS _hoops_HRGR _hoops_IGRC _hoops_GARGC - _hoops_HIS _hoops_GGSHR '_hoops_HPRI */
		Swap (dc->_hoops_SPHHP, dc->_hoops_GHHHP);
		dc->_hoops_HAHHP = true;
	}
}


GLOBAL_FUNCTION void HD_Preprocess (
	Net_Rendition alter &		nr) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	Attribute alter *			_hoops_ACCSC[_hoops_CRCCA + 1];
	_hoops_ASAIR				_hoops_HRSSC;
	_hoops_RSAIR					_hoops_IRSSC;
	_hoops_SSGI						_hoops_CRSSC;
	_hoops_GGAGR alter *				_hoops_GHRI;
	_hoops_ACSGA const *			list;
	_hoops_HHAGP				locks = 0;
	Color_Object				color_locks = 0;
	bool						_hoops_CGISP = false;
	_hoops_PIGRA				_hoops_SRSSC;

	_hoops_GHRI = (_hoops_GGAGR alter *)dc->_hoops_GHRI;

	ZERO_ARRAY(_hoops_ACCSC, _hoops_GGAPR(_hoops_ACCSC), Attribute *);

	if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR ||
				dc->options._hoops_RAHHP) {
		_hoops_CRSSC.colors = null;
		_hoops_CRSSC._hoops_GHA = _hoops_CRSSC._hoops_CCCIR = Color_NONE;
		_hoops_CRSSC.owner = (_hoops_CRCP alter *)dc->_hoops_AAHSR;
		_hoops_CRSSC.type = HK_COLOR;
		_hoops_CRSSC.next = null;
		_hoops_ACCSC[(int)HK_COLOR] = (Attribute alter *)&_hoops_CRSSC;
	}
	else
		return;

	_hoops_IRSSC.mask = false;
	_hoops_IRSSC.value = false;
	_hoops_IRSSC.type = HK_VISIBILITY;
	_hoops_IRSSC.next = null;
	_hoops_ACCSC[(int)HK_VISIBILITY] = (Attribute alter *)&_hoops_IRSSC;

	_hoops_CCCSC ((_hoops_CRCP const *)((Subsegment const *)dc->_hoops_AAHSR), _hoops_ACCSC,
								&locks, &color_locks, &_hoops_CGISP);

	if (!BIT (_hoops_IRSSC.value, T_WINDOWS))
		return; /* _hoops_PAHA'_hoops_RA _hoops_IHPS? */

	if (dc->options._hoops_RAHHP) {
		_hoops_ARSSC (dc, (_hoops_SSGI const *)_hoops_ACCSC[(int)HK_COLOR]);
	}
	else /*_hoops_RPP (_hoops_CSPH->_hoops_CPHSR._hoops_AHRHH == _hoops_AIIHP) */ {
		/* _hoops_IHPHR _hoops_HRGR _hoops_ACIPR */
		dc->_hoops_RRPGH = dc->_hoops_ARPGH;
		dc->_hoops_ARPGH = null;
		dc->_hoops_PRPGH = dc->_hoops_HRPGH;
		dc->_hoops_HRPGH = null;

		list = ((_hoops_SSGI const *)_hoops_ACCSC[(int)HK_COLOR])->colors;

		do
			((_hoops_ACSGA alter *)list)->_hoops_PPRPR = _hoops_CHCSC (dc, list);
		while ((list = list->next) != null);

		/* _hoops_GGR _hoops_AGIR _hoops_CIH/_hoops_GASSC _hoops_CSAP _hoops_CPHR, _hoops_SR _hoops_PIHA _hoops_SGCSR _hoops_IS _hoops_CISA _hoops_RASSC */
		if (dc->_hoops_CHHIP != null && dc->_hoops_CHHIP[0].red == -1.0f)
			_hoops_CGISP = true;

#ifndef DISABLE_COLOR_MAPS
		((_hoops_RHAH alter *)_hoops_ACCSC[(int)HK_COLOR_MAP])->_hoops_PPRPR =
				_hoops_SHCSC (dc, (_hoops_RHAH const *)_hoops_ACCSC[(int)HK_COLOR_MAP],
								  _hoops_CGISP);
#endif

		if (dc->_hoops_AAHSR->_hoops_RGRPR != null) {
			if (BIT (dc->_hoops_AAHSR->_hoops_RCGC, _hoops_HPRRA))
				_hoops_AICSC (dc, dc->_hoops_AAHSR->_hoops_RGRPR, _hoops_IRSSC.value, _hoops_CGISP);
		}

		_hoops_IGSSC (dc);

		/* _hoops_HRSIR _hoops_RH _hoops_AASH _hoops_IIGR _hoops_PSHA _hoops_GRP _hoops_CCAH _hoops_PSPI &_hoops_GSGGR.
		** _hoops_PHAA _hoops_RRP _hoops_IS _hoops_AASSC _hoops_GII _hoops_SGHS _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_RH _hoops_PSHA _hoops_HGCR _hoops_PGGGH --
		** _hoops_SGH _hoops_PASSC _hoops_IS _hoops_SHH _hoops_ICIC (_hoops_GHCA _hoops_ACIPR-_hoops_RRGR _hoops_SPHR)
		*/
		_hoops_GRGH	_hoops_RRGH = nr.Modify()->_hoops_IRR.Modify();
		_hoops_RSAI (&_hoops_RRGH->locks, _hoops_PIGRA, &_hoops_SRSSC);
		ZERO_STRUCT (&_hoops_RRGH->locks, _hoops_PIGRA);

#ifndef DISABLE_COLOR_MAPS
		HD_Downwind_Rendition (nr, _hoops_ACCSC[(int)HK_COLOR_MAP], _hoops_CAHGP, false);
#endif
		HD_Downwind_Rendition (nr, _hoops_ACCSC[(int)HK_COLOR], _hoops_CAHGP, false);

		_hoops_RSAI (&_hoops_SRSSC, _hoops_PIGRA, &_hoops_RRGH->locks);

		_hoops_ISHHP	_hoops_CSHHP = nr->_hoops_ASIR.Modify();

		_hoops_CGRA	_hoops_SGRA = nr->_hoops_SAIR.Modify();

		/* _hoops_HGCR _hoops_RH _hoops_HPHR _hoops_RPPS _hoops_HAIR */
		_hoops_SGRA->_hoops_GPIR = _hoops_CSHHP->window.color;
		_hoops_SGRA->_hoops_GRAIP.red	 = _hoops_CSHHP->window._hoops_PGC.red;
		_hoops_SGRA->_hoops_GRAIP.green = _hoops_CSHHP->window._hoops_PGC.green;
		_hoops_SGRA->_hoops_GRAIP.blue	 = _hoops_CSHHP->window._hoops_PGC.blue;
		_hoops_SGRA->contrast_color = _hoops_CSHHP->window._hoops_HGIHP;
		_hoops_SGRA->_hoops_CGIHP.red   = _hoops_CSHHP->window._hoops_CGIHP.red;
		_hoops_SGRA->_hoops_CGIHP.green = _hoops_CSHHP->window._hoops_CGIHP.green;
		_hoops_SGRA->_hoops_CGIHP.blue  = _hoops_CSHHP->window._hoops_CGIHP.blue;
		_hoops_SGRA->_hoops_CGAIP = _hoops_CSHHP->window.pattern;
		_hoops_SGRA->_hoops_SGAIP = false;

		if (_hoops_SGRA->_hoops_SICSR != null)
			_hoops_HPRH (_hoops_SGRA->_hoops_SICSR);

		if ((_hoops_SGRA->_hoops_SICSR = _hoops_CSHHP->window.texture) != null)
			_hoops_PRRH (_hoops_SGRA->_hoops_SICSR);

		/* _hoops_CIH _hoops_RH _hoops_HAIR _hoops_HIGR */
		HI_Free_Colors(((_hoops_SSGI const *)_hoops_ACCSC[(int)HK_COLOR])->colors);
	}
}



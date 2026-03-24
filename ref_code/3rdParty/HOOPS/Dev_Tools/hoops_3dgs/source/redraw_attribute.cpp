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
 * $Id: obf_tmp.txt 1.341 2011-01-18 20:29:37 heppe Exp $
 */

#include "hoops.h"
#include "database.h"
#include "patterns.h"
#include "please.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


#define _hoops_HIHHC(_hoops_RSPGP,_hoops_SRCP,x)	(BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR) ? \
		_hoops_IIHHC (_hoops_RSPGP,_hoops_SRCP,x) : _hoops_SASIR (_hoops_RSPGP,_hoops_SRCP, _hoops_RAGGA | (x)))

#define _hoops_HRSGS(_hoops_RSPGP,_hoops_SRCP,x)		(BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR) ? \
		_hoops_IRSGS (_hoops_RSPGP,_hoops_SRCP,x) : _hoops_SASIR (_hoops_RSPGP,_hoops_SRCP,_hoops_GSCCA | (x)))

#define _hoops_CRSGS(_hoops_RSPGP,_hoops_SRCP,x) (BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR) ? \
		_hoops_SRSGS (_hoops_RSPGP,_hoops_SRCP,x) : _hoops_SASIR (_hoops_RSPGP,_hoops_SRCP, _hoops_HRCCA | \
												_hoops_ICHPA | (x)))

#define _hoops_IRSGS(_hoops_RSPGP,_hoops_SRCP,x) _hoops_SASIR (_hoops_RSPGP,_hoops_SRCP, _hoops_RCGSA | (x))
#define _hoops_GASGS(_hoops_RSPGP,_hoops_SRCP,x) _hoops_SASIR (_hoops_RSPGP,_hoops_SRCP, _hoops_GAGSA | (x))
#define _hoops_RASGS(_hoops_RSPGP,_hoops_SRCP,x)  _hoops_SASIR (_hoops_RSPGP,_hoops_SRCP, _hoops_GCPGP | (x))
#define _hoops_AASGS(_hoops_RSPGP,_hoops_SRCP,x)	  _hoops_SASIR (_hoops_RSPGP,_hoops_SRCP, _hoops_SIPGP | (x))
#define _hoops_IIHHC(_hoops_RSPGP,_hoops_SRCP,x) _hoops_SASIR (_hoops_RSPGP,_hoops_SRCP, _hoops_GGARA | (x))
#define _hoops_SRSGS(_hoops_RSPGP,_hoops_SRCP,x)	_hoops_SASIR (_hoops_RSPGP,_hoops_SRCP, _hoops_HGSCA | (x))

#define _hoops_PASGS(_hoops_RSPGP,_hoops_SRCP,x)	(BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR) ? \
		_hoops_HASGS (_hoops_RSPGP,_hoops_SRCP,x) : \
		_hoops_SASIR (_hoops_RSPGP,_hoops_SRCP, _hoops_AISSR | (x)))

#define _hoops_IASGS(_hoops_RSPGP,_hoops_SRCP,x)	(BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR) ? \
		_hoops_CASGS (_hoops_RSPGP,_hoops_SRCP,x) : \
		_hoops_SASIR (_hoops_RSPGP,_hoops_SRCP, _hoops_ACPGP | (x)))

#define _hoops_SASGS(_hoops_RSPGP,_hoops_SRCP,x)	(BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR) ? \
		_hoops_SRSGS (_hoops_RSPGP,_hoops_SRCP,x) : \
		_hoops_SASIR (_hoops_RSPGP,_hoops_SRCP, _hoops_HRCCA | \
								 _hoops_ICHPA | _hoops_SIGPR | (x)))

#define _hoops_CASGS(_hoops_RSPGP, _hoops_SRCP,x) _hoops_SASIR (_hoops_RSPGP, _hoops_SRCP, \
										_hoops_GCGSA | (x))
#define _hoops_HASGS(_hoops_RSPGP,_hoops_SRCP,x)	_hoops_SASIR (_hoops_RSPGP,_hoops_SRCP, \
										_hoops_GPSIR | (x))

#define _hoops_GPSGS(_hoops_SRCP)		\
		(ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_HIHGP) || \
		 BIT (_hoops_SRCP->_hoops_RCGC, T_WINDOWS))


#ifndef DISABLE_STYLE_SEGMENT
local void _hoops_RPSGS (
	_hoops_AIGPR *	_hoops_RIGC,
	Xref *					_hoops_AHICA,
	Type					type,
	Attribute *				_hoops_PISCA,
	Attribute *				_hoops_SISCA,
	_hoops_PSPGP			_hoops_PCGPR) {

	do {
		/* _hoops_RPP _hoops_IIH _hoops_HRGR _hoops_IRS _hoops_IAHA _hoops_CGRPR _hoops_IS _hoops_IHHH... */
		if (_hoops_AHICA->type == HK_STYLE) {
			Attribute	*_hoops_ASGPR;
			_hoops_CRCP		*_hoops_SRCP = _hoops_AHICA->owner;
			Color_Object _hoops_APSGS = Color_NONE;

			if (_hoops_SRCP->type != _hoops_IRCP) {
				if (_hoops_SRCP->type == HK_RENDERING_OPTIONS && type == HK_COLOR_MAP) {
					_hoops_SRCP=_hoops_SRCP->owner;
					_hoops_HIHHC(_hoops_RIGC, _hoops_SRCP,_hoops_SSCCA);
				}
				continue;
			}

			_hoops_SRCP->_hoops_PCGPR |= _hoops_PCGPR;

			if (_hoops_SISCA != null && _hoops_SISCA->type == HK_COLOR)
				_hoops_APSGS = ((_hoops_SSGI const *)_hoops_SISCA)->_hoops_CCCIR;

			/* _hoops_IHSH _hoops_PPR _hoops_CACH _hoops_RPP _hoops_RH _hoops_PPSGS _hoops_SSCP _hoops_RH _hoops_IGRI _hoops_GACC */
			if ((_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR) != null) do {
				if (_hoops_ASGPR->type >= type) {
					if (_hoops_ASGPR->type > type)
						_hoops_ASGPR = null;
					break;
				}
			} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

			if (_hoops_ASGPR == null) {
				_hoops_AHICA->_hoops_CPGPR |= _hoops_CAHRA;

				HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, type, _hoops_PISCA, _hoops_SISCA);

				_hoops_SRSGS (_hoops_RIGC, _hoops_SRCP, 0);
			}
			else switch (type) {
				case HK_SELECTABILITY:
				case HK_VISIBILITY:
				case HK_TEXT_FONT:
				case HK_RENDERING_OPTIONS:
				case HK_DRIVER_OPTIONS:
				case HK_HEURISTICS: {
					/* _hoops_CAHAR, _hoops_HRII _hoops_HSAR _hoops_CPIC _hoops_CRGR _hoops_AHSIR */

					_hoops_AHICA->_hoops_CPGPR |= _hoops_CAHRA;

					HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, type, _hoops_PISCA, _hoops_SISCA);
#if 0
					HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, type, _hoops_SISCA, _hoops_ASGPR);
					HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, type, _hoops_ASGPR, _hoops_PISCA);
#endif
					_hoops_SRSGS (_hoops_RIGC, _hoops_SRCP, 0);
				}	break;
			}

			if (_hoops_SISCA != null && _hoops_SISCA->type == HK_COLOR)
				((_hoops_SSGI *)_hoops_SISCA)->_hoops_CCCIR = _hoops_APSGS;
		}
	} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);
}
#endif

local bool _hoops_HPSGS (
	_hoops_CRCP				*_hoops_SRCP) {

	do {
		if (BIT (_hoops_SRCP->_hoops_RCGC, _hoops_IPHGP))
			return true;

		if (_hoops_SRCP->_hoops_SGRPR() != null) {
			Xref *_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR();

			do if (_hoops_AHICA->type == _hoops_AGRPR) {
				if (_hoops_HPSGS (_hoops_AHICA->owner))
					return true;
			} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);
		}

		_hoops_SRCP = _hoops_SRCP->owner;
	} while (_hoops_SRCP != HOOPS_WORLD->root);

	return false;
}


local void _hoops_IPSGS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	float					left,
	float					right,
	float					bottom,
	float					top) {

	if (left < right && bottom < top) {
		_hoops_PACIR	scope (left, right, bottom, top);
		_hoops_SRCP->_hoops_CPGPR &= ~_hoops_AHPGP; /* _hoops_HIAP */
		HI_Propagate_Scoped_Activity (_hoops_RIGC, (_hoops_SIHIR *)_hoops_SRCP, _hoops_SCCCA, &scope);
	}
}


local void _hoops_CPSGS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP) {

	if (ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_HIHGP)) {
		Window		*window;
		_hoops_PIHGP	save;

		window = HI_Find_Scoping_Window (_hoops_SRCP);
		save = _hoops_SRCP->_hoops_PHSI;
		_hoops_SRCP->_hoops_PHSI &= ~(_hoops_GCHGP|_hoops_SHSIR);
		_hoops_SRCP->_hoops_CPGPR &= ~_hoops_AHPGP; /* _hoops_HIAP */
		HI_Propagate_Scoped_Activity (_hoops_RIGC, (_hoops_SIHIR *)_hoops_SRCP, _hoops_SCCCA, &window->_hoops_RCHS);
		_hoops_SRCP->_hoops_PHSI = save;
	}
	else if (BIT (_hoops_SRCP->_hoops_RCGC, T_WINDOWS) && _hoops_SRCP->_hoops_RGRPR != null) {
		Subsegment	*_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR;

		do {
			_hoops_SRCP = _hoops_SSIGP (_hoops_GIPIA);

			if (!ANYBIT (_hoops_SRCP->_hoops_PHSI,
						 _hoops_GCHGP|_hoops_SIHGP))
				_hoops_CPSGS (_hoops_RIGC, _hoops_SRCP);
		} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);
	}
}


GLOBAL_FUNCTION void HI_Redraw_Attribute (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	Type					type,
	Attribute *				_hoops_PISCA,
	Attribute *				_hoops_SISCA) {
	_hoops_RCCCA			_hoops_SPSGS = 0;
	Activity				_hoops_GHSGS = 0;
	_hoops_PSPGP			_hoops_PCGPR = _hoops_HSPGP;

	/* _hoops_PIP: _hoops_RHSGS _hoops_GRS _hoops_SHR _hoops_SHH _hoops_CCCI */
	/*		 _hoops_AHSGS _hoops_GHCA _hoops_HAR _hoops_SHH _hoops_CCCI */

	if (_hoops_PISCA != null) {
		_hoops_SPSGS = _hoops_PISCA->_hoops_RRHH;
		_hoops_PISCA->_hoops_RRHH |= _hoops_HGAGR;
	}

	if (_hoops_SRCP->type != _hoops_IRCP) {
		/* _hoops_CPSA _hoops_IRS _hoops_CPAP! */
		_hoops_SRCP = _hoops_SRCP->owner;
		_hoops_GHSGS = _hoops_RAGGA;
	}
	// _hoops_RCRP _hoops_RHPP _hoops_SGHC _hoops_IRS _hoops_GHIR _hoops_HIHGI _hoops_CPIRA _hoops_CGPR _hoops_SCH _hoops_CSAP _hoops_CGHI _hoops_RHIAA.
	if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GISIR))
		_hoops_SRCP->_hoops_ACIGP (HOOPS_WORLD->_hoops_GPPI + 1);

	switch (type) {
		default: {
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Unrecognized attribute for redrawing");
			if (_hoops_PISCA != null) 
				_hoops_PISCA->_hoops_RRHH = _hoops_SPSGS;
			return;
		}		/* _hoops_IHSA; */

		case _hoops_AGAIR: {
			_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, 0);
		}	break;

		case HK_STYLE: {
			if (_hoops_PISCA == null) { /* _hoops_CPRAA _hoops_IAHA */
				Style *		_hoops_RCSCA = (Style *)_hoops_SISCA;

				if (_hoops_RCSCA->condition.count > 0)
					HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_CPHGP);

				if (_hoops_RCSCA->_hoops_IGRPR) {
					Attribute *	_hoops_PHSGS = _hoops_RCSCA->_hoops_IGRPR->_hoops_IPPGR;

					if (_hoops_PHSGS != null) do if (!BIT (_hoops_PHSGS->_hoops_RRHH, _hoops_HGAGR)) {
						HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, _hoops_PHSGS->type, null, _hoops_PHSGS);
					} while ((_hoops_PHSGS = _hoops_PHSGS->next) != null);
				}
			}
			else {					/* _hoops_HGAPA _hoops_IAHA */
				Style *		_hoops_GCSCA = (Style *)_hoops_PISCA;

				if (_hoops_GCSCA->_hoops_IGRPR) {
					Attribute *	_hoops_HHSGS = _hoops_GCSCA->_hoops_IGRPR->_hoops_IPPGR;

					if (_hoops_HHSGS != null) do if (!BIT (_hoops_HHSGS->_hoops_RRHH, _hoops_HGAGR)) {
						HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, _hoops_HHSGS->type, _hoops_HHSGS, null);
					} while ((_hoops_HHSGS = _hoops_HHSGS->next) != null);
				}
			}
		}	break;

		case HK_USER_VALUE:
		case _hoops_GRAIR: {
			if (_hoops_PISCA != null) 
				_hoops_PISCA->_hoops_RRHH = _hoops_SPSGS;
			return;		/* _hoops_RPAPR */
		}		/* _hoops_IHSA; */

		case HK_USER_OPTIONS: {
/*#_hoops_CHS _hoops_IHSGS _hoops_RGR _hoops_CGH _hoops_SHH _hoops_CPHR _hoops_GRP _hoops_RH "_hoops_PAAP _hoops_RGSHA" _hoops_GHARR _hoops_HCSP */
			/* _hoops_SR _hoops_HS _hoops_PSP _hoops_GRIGI _hoops_PCPA _hoops_RH _hoops_SSHSR _hoops_CHR _hoops_GHGA _hoops_CCA _hoops_IPSP _hoops_HCSP _hoops_GGR
			 * _hoops_PAII _hoops_PGHGR _hoops_RRGR */
			_hoops_CRSGS (_hoops_RIGC, _hoops_SRCP, _hoops_GHSGS);
/*#_hoops_SHIIR*/
		}	break;

		case HK_COLOR: {
			_hoops_SSGI		*_hoops_IHPCR = (_hoops_SSGI *)_hoops_SISCA;
			Activity		_hoops_HHCAP = _hoops_SSCCA;

			if (_hoops_IHPCR == null) {
				_hoops_IHPCR = (_hoops_SSGI *)_hoops_PISCA;
				_hoops_IHPCR->_hoops_CCCIR = _hoops_IHPCR->_hoops_GHA;
			}

			if (BIT (_hoops_IHPCR->_hoops_CCCIR, Color_WINDOW) &&
					 _hoops_GPSGS (_hoops_SRCP))
				_hoops_RASGS (_hoops_RIGC, _hoops_SRCP, 0);
			else if (BIT (_hoops_IHPCR->_hoops_CCCIR, Color_WINDOW_CONTRAST) &&
					 _hoops_GPSGS (_hoops_SRCP)  &&
					 !BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_PPPGP)) {
				if (_hoops_HPSGS (_hoops_SRCP))
					_hoops_RASGS (_hoops_RIGC, _hoops_SRCP, 0);
				else
					_hoops_AASGS (_hoops_RIGC, _hoops_SRCP, 0);
			}

			{
				_hoops_SSGI *			_hoops_RPRRA = (_hoops_SSGI *)_hoops_PISCA;
				_hoops_SSGI *			_hoops_APRRA = (_hoops_SSGI *)_hoops_SISCA;
				_hoops_ACSGA *	list;

				bool			_hoops_CHSGS = true;

				if (_hoops_SISCA != null && (list = _hoops_APRRA->colors) != null) do {
					if (list->type == _hoops_GIGRA) {
						_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;

						if ((BIT (_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA, _hoops_IIARA) &&
							 _hoops_ICSGA->_hoops_ISHIR.texture[_hoops_PCA] != null ||
							 BIT (_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA, M_TRANSMISSION) &&
							 (_hoops_ICSGA->_hoops_ISHIR.color[_hoops_PCA].red   != 0.0f ||
							  _hoops_ICSGA->_hoops_ISHIR.color[_hoops_PCA].green != 0.0f ||
							  _hoops_ICSGA->_hoops_ISHIR.color[_hoops_PCA].blue  != 0.0f))) {

							HI_More_Transparencies (_hoops_RIGC, _hoops_SRCP, 1);

							if (_hoops_CHSGS && !BIT (_hoops_SRCP->_hoops_RCGC, _hoops_ASRRA))
								HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_ASRRA);
							_hoops_CHSGS = false;;
							_hoops_HHCAP |= _hoops_CSCCA;
							break;
						}
						else if (_hoops_CHSGS && ANYBIT (_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA, _hoops_PSARA)) {
							/* _hoops_AI _hoops_GACC _hoops_HGAP _hoops_CSGRH */
							if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_ASRRA))
								HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_ASRRA);
							_hoops_CHSGS = false;;
						}
					}
				} while ((list = list->next) != null);

				if (_hoops_PISCA != null && (list = _hoops_RPRRA->colors) != null) do {
					if (list->type == _hoops_GIGRA) {
						_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;

						if ((BIT (_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA, _hoops_IIARA) &&
							 _hoops_ICSGA->_hoops_ISHIR.texture[_hoops_PCA] != null ||
							 BIT (_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA, M_TRANSMISSION) &&
							 (_hoops_ICSGA->_hoops_ISHIR.color[_hoops_PCA].red   != 0.0f ||
							  _hoops_ICSGA->_hoops_ISHIR.color[_hoops_PCA].green != 0.0f ||
							  _hoops_ICSGA->_hoops_ISHIR.color[_hoops_PCA].blue  != 0.0f))) {
							HI_Less_Transparencies (_hoops_RIGC, _hoops_SRCP, 1);
							_hoops_HHCAP |= _hoops_CSCCA;
							break;
						}
					}
				} while ((list = list->next) != null);

			}

			if ((BIT (_hoops_IHPCR->_hoops_CCCIR, Color_LIGHTING)  &&
				 BIT (_hoops_SRCP->_hoops_RCGC, T_ANY_LIGHTS))  ||
				(ANYBIT (_hoops_IHPCR->_hoops_CCCIR, _hoops_IRARA)  &&
				 BIT (_hoops_SRCP->_hoops_RCGC, T_FACES)))
				_hoops_PASGS (_hoops_RIGC, _hoops_SRCP, _hoops_HHCAP);
			else if (ANYBIT (_hoops_IHPCR->_hoops_CCCIR, Color_FACE) &&
					 BIT (_hoops_SRCP->_hoops_RCGC, T_FACES)) {
				if (_hoops_SRCP->_hoops_IGCCA > 0)
					_hoops_PASGS (_hoops_RIGC, _hoops_SRCP, _hoops_HHCAP);
				else
					_hoops_HASGS (_hoops_RIGC, _hoops_SRCP, _hoops_HHCAP);
			}
			else if ((ANYBIT (_hoops_IHPCR->_hoops_CCCIR, Color_FACE|Color_FACE_CONTRAST) &&
					  BIT (_hoops_SRCP->_hoops_RCGC, T_FACES))  ||
					 (BIT (_hoops_IHPCR->_hoops_CCCIR, Color_EDGE) &&
					  ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, T_ANY_EDGE))	 ||
					 (BIT (_hoops_IHPCR->_hoops_CCCIR, Color_LINE) &&
					  BIT (_hoops_SRCP->_hoops_RCGC, T_LINES))  ||
					 (ANYBIT (_hoops_IHPCR->_hoops_CCCIR, Color_MARKER|Color_VERTEX) &&
					  ANYBIT (_hoops_SRCP->_hoops_RCGC, T_MARKERS|T_VERTICES))	 ||
					 (BIT (_hoops_IHPCR->_hoops_CCCIR, Color_TEXT) &&
					  BIT (_hoops_SRCP->_hoops_RCGC, T_TEXT)))
				if (_hoops_SRCP->_hoops_IGCCA > 0)
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_HHCAP);
				else
					_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_HHCAP);
		}	break;


		case HK_WINDOW: {
			int			_hoops_CGR,
						_hoops_RPGGA,
						_hoops_SHSGS,
						_hoops_GISGS;

			if (_hoops_SISCA == null) {
				if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) {/* _hoops_PISSA _hoops_IRS _hoops_RPPS */
					_hoops_SHSGS = _hoops_SRCP->_hoops_IGCCA;
					_hoops_CGR = _hoops_SRCP->_hoops_AAGSA();
					_hoops_RPGGA = _hoops_SRCP->_hoops_PAGSA();
					_hoops_GISGS = _hoops_SRCP->_hoops_SHGSA();

					/* _hoops_AGCR _hoops_RRP _hoops_IS _hoops_SSS _hoops_IRS _hoops_PRP _hoops_RPPS _hoops_PIAP,
					 * _hoops_HIS _hoops_CAHAR _hoops_RH _hoops_RPPS _hoops_CCACR'_hoops_RA _hoops_PPRGA _hoops_SGGR _hoops_GAPR
					 */
					_hoops_PISCA->_hoops_RRHH = _hoops_SPSGS;
					if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GISIR)) {
						if (_hoops_CGR > 0)
							HI_Less_Light (_hoops_RIGC, _hoops_SRCP, _hoops_CGR);
						if (_hoops_RPGGA > 0)
							HI_Less_Cutting_Planes (_hoops_RIGC, _hoops_SRCP, _hoops_RPGGA);
						if (_hoops_GISGS > 0)
							HI_Less_Shadows (_hoops_RIGC, _hoops_SRCP, _hoops_GISGS);
						if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA|_hoops_RIGSA))
							if (_hoops_SHSGS > 0)
								HI_Less_Transparencies (_hoops_RIGC, _hoops_SRCP, _hoops_SHSGS);
					}

					/* *_hoops_HA* _hoops_SCH'_hoops_GRI _hoops_CPSA _hoops_CPIC */
					_hoops_ICIIR(_hoops_RIGC);
					//_hoops_HPPSA (_hoops_IPPSA->_hoops_HHSIR);			// _hoops_SHR _hoops_GIAA _hoops_IRS _hoops_IHSIR?
					bool		_hoops_RISGS = (_hoops_SRCP != HOOPS_WORLD->root) && HI_Fast_Lookup_Available (_hoops_SRCP, true);

					if (_hoops_RISGS)
						HI_Remove_Fast_Lookup_Item (_hoops_SRCP->owner, true, (Subsegment *)_hoops_SRCP);

					_hoops_PISCA->_hoops_RRHH |= _hoops_HGAGR;
					_hoops_SRCP->_hoops_PHSI &= ~_hoops_SHSIR;

					if (_hoops_RISGS)
						HI_Add_Fast_Lookup_Item (_hoops_SRCP->owner, true, (Subsegment *)_hoops_SRCP);
					//_hoops_SPPSA (_hoops_IPPSA->_hoops_HHSIR);

					if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GISIR)) {
						if (_hoops_CGR > 0)
							HI_More_Light (_hoops_RIGC, _hoops_SRCP, _hoops_CGR);
						if (_hoops_RPGGA > 0)
							HI_More_Cutting_Planes (_hoops_RIGC, _hoops_SRCP, _hoops_RPGGA);
						if (_hoops_GISGS > 0)
							HI_More_Shadows (_hoops_RIGC, _hoops_SRCP, _hoops_GISGS);
						if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA|_hoops_RIGSA))
							if (_hoops_SHSGS > 0)
								HI_More_Transparencies (_hoops_RIGC, _hoops_SRCP, _hoops_SHSGS);
					}

					if (_hoops_SRCP->bounding != null)
						HI_Propagate_Bounding (_hoops_RIGC, _hoops_SRCP, _hoops_SRCP->bounding, null);

					if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GCHGP)) {
						if (_hoops_PISCA == null) {
							_hoops_SRCP->_hoops_CPGPR &= ~_hoops_AHPGP; /* _hoops_HIAP */
							_hoops_IASGS (_hoops_RIGC, _hoops_SRCP, 0);
						}
						else {
							if (!BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR)) {
								Window *	_hoops_AISGS = (Window *)_hoops_PISCA;

								_hoops_SRCP->_hoops_CPGPR &= ~_hoops_AHPGP; /* _hoops_HIAP */
								HI_Propagate_Scoped_Activity (_hoops_RIGC, (_hoops_SIHIR *)_hoops_SRCP,
												_hoops_GSCCA|
												(BIT (_hoops_SRCP->_hoops_RCGC, T_FACES) ? _hoops_CSCCA : 0)|
												_hoops_PISSR|
												_hoops_RPSIR|
												_hoops_SSCCA,
												&_hoops_AISGS->_hoops_RCHS);
							}
							if (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, _hoops_HAHGP) &&
								!BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR)) {
								_hoops_SRCP->_hoops_CPGPR &= ~_hoops_AHPGP; /* _hoops_HIAP */
								_hoops_IRSGS (_hoops_RIGC, _hoops_SRCP, 0);
							}
						}
					}
				}
			}
			else if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) {/* _hoops_CPRAA _hoops_IRS _hoops_RPPS */
				if (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, _hoops_HAHGP) &&
					!BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR)) {
					/* _hoops_ARPP _hoops_IAHAR _hoops_GPP _hoops_PISGS! */
					if (BIT (_hoops_SRCP->_hoops_RCGC, T_WINDOWS))
						_hoops_IASGS (_hoops_RIGC, _hoops_SRCP, 0);
					else if (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, T_ANY_DRAWABLE_GEOMETRY))
						_hoops_PASGS (_hoops_RIGC, _hoops_SRCP, 0);

					HI_Propagate_Activity (_hoops_RIGC,
											(_hoops_SIHIR *)_hoops_SRCP,
												(BIT (_hoops_SRCP->_hoops_RCGC, T_FACES) ? _hoops_CSCCA : 0)|
												_hoops_PISSR|
												_hoops_RPSIR|
												_hoops_SSCCA);
				}

				_hoops_SHSGS = _hoops_SRCP->_hoops_IGCCA;
				_hoops_CGR = _hoops_SRCP->_hoops_AAGSA();
				_hoops_RPGGA = _hoops_SRCP->_hoops_PAGSA();
				_hoops_GISGS = _hoops_SRCP->_hoops_SHGSA();

				if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GISIR)) {
					if (_hoops_CGR > 0)
						HI_Less_Light (_hoops_RIGC, _hoops_SRCP, _hoops_CGR);
					if (_hoops_RPGGA > 0)
						HI_Less_Cutting_Planes (_hoops_RIGC, _hoops_SRCP, _hoops_RPGGA);
					if (_hoops_GISGS > 0)
						HI_Less_Shadows (_hoops_RIGC, _hoops_SRCP, _hoops_GISGS);
					if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA|_hoops_RIGSA))
						if (_hoops_SHSGS > 0)
							HI_Less_Transparencies (_hoops_RIGC, _hoops_SRCP, _hoops_SHSGS);
				}

				if (_hoops_SRCP->bounding != null)
					HI_Antiquate_Bounding (_hoops_SRCP, false);


				if (_hoops_SRCP != HOOPS_WORLD->root) {
					_hoops_CRCP *		owner = _hoops_SRCP->owner;
					Subsegment *	_hoops_AIGSA;

					_hoops_ICIIR(_hoops_RIGC);
					//_hoops_HPPSA (_hoops_IPPSA->_hoops_HHSIR);			// _hoops_SHR _hoops_GIAA _hoops_IRS _hoops_IHSIR?
					HI_Create_Fast_Lookup (owner, true);
					HI_Remove_Fast_Lookup_Item (owner, true, (Subsegment *)_hoops_SRCP);

					_hoops_SRCP->_hoops_PHSI |= _hoops_SHSIR;

					HI_Add_Fast_Lookup_Item (owner, true, (Subsegment *)_hoops_SRCP);

					_hoops_AIGSA = HI_Find_Fast_Lookup_Predecessor (owner, true, (Subsegment *)_hoops_SRCP, null);
					//_hoops_SPPSA (_hoops_IPPSA->_hoops_HHSIR);

					_hoops_CIGPR (_hoops_RIGC,_hoops_SRCP);
					if (_hoops_AIGSA != null) {
						if ((_hoops_SRCP->next = _hoops_AIGSA->next) != null)
							_hoops_SRCP->next->backlink = &_hoops_SRCP->next;
						_hoops_SRCP->backlink = &_hoops_AIGSA->next;
						_hoops_AIGSA->next = (Subsegment *)_hoops_SRCP;
					}
					else {
						if ((_hoops_SRCP->next = owner->_hoops_RGRPR) != null)
							_hoops_SRCP->next->backlink = &_hoops_SRCP->next;
						_hoops_SRCP->backlink = &owner->_hoops_RGRPR;
						owner->_hoops_RGRPR = (Subsegment *)_hoops_SRCP;
					}
				}
				//_hoops_PHHIP->_hoops_AIHGP |= _hoops_HISGS;

				if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GISIR)) {
					if (_hoops_CGR > 0)
						HI_More_Light (_hoops_RIGC, _hoops_SRCP, _hoops_CGR);
					if (_hoops_RPGGA > 0)
						HI_More_Cutting_Planes (_hoops_RIGC, _hoops_SRCP, _hoops_RPGGA);
					if (_hoops_GISGS > 0)
						HI_More_Shadows (_hoops_RIGC, _hoops_SRCP, _hoops_GISGS);
					if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA|_hoops_RIGSA))
						if (_hoops_SHSGS > 0)
							HI_More_Transparencies (_hoops_RIGC, _hoops_SRCP, _hoops_SHSGS);
				}

				if (!BIT (_hoops_SRCP->_hoops_RCGC, T_WINDOWS)) {
					HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, T_WINDOWS);
					_hoops_SRCP->_hoops_RCGC &= ~T_WINDOWS;	/* _hoops_HIH _hoops_HAR _hoops_CAIR!! */
				}

				HI_Bring_To_Front (_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP);

				if (_hoops_SRCP->_hoops_SGRPR() != null) {
					Xref			*_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR();

					do if (_hoops_AHICA->type == _hoops_AGRPR)
						HI_Bring_To_Front_By_Key (_hoops_RIGC, _hoops_AIRIR (_hoops_AHICA));
					while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);
				}

				/* _hoops_AIIAP _hoops_RGR _hoops_SHSC _hoops_RPPS */
				_hoops_CASGS (_hoops_RIGC, _hoops_SRCP, 0);
			}
			else {		/* _hoops_HHACR _hoops_IRS _hoops_RPPS */
				if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GCHGP)) {
					if (_hoops_PISCA == null) {
						/* _hoops_IGGRA _hoops_PII _hoops_SR'_hoops_ASAR _hoops_HGAPA _hoops_PPR _hoops_PSCR _hoops_CPRAA _hoops_IRS _hoops_RPPS */
						/* _hoops_SCAC _hoops_RH _hoops_RRRPR _hoops_AGIRH */
						_hoops_SRCP->_hoops_PHSI &= ~_hoops_SHSIR;
						_hoops_SRCP->_hoops_CPGPR &= ~_hoops_AHPGP; /* _hoops_HIAP */
						_hoops_HRSGS (_hoops_RIGC, _hoops_SRCP, 0);

						/* _hoops_SCAC _hoops_IHHH _hoops_AGIRH */
						_hoops_SRCP->_hoops_PHSI |= _hoops_SHSIR;
						_hoops_SRCP->_hoops_CPGPR &= ~_hoops_AHPGP; /* _hoops_HIAP */
						_hoops_IASGS (_hoops_RIGC, _hoops_SRCP, 0);
					}
					else {
						/* _hoops_AHSGS _hoops_HRGR _hoops_HSSPR - _hoops_SCH'_hoops_GRI _hoops_GHIR _hoops_IS _hoops_SHH _hoops_ISPSP */
						Window *		_hoops_AISGS = (Window *)_hoops_PISCA;
						Window *		_hoops_IHPIP = (Window *)_hoops_SISCA;

						if (!BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR)) {
							/* _hoops_AIIAP _hoops_RH _hoops_IISGS _hoops_IIRGR */

							/* _hoops_CAHAR _hoops_SR _hoops_HS _hoops_PSP _hoops_RPPS */
							_hoops_SRCP->_hoops_PHSI &= ~_hoops_SHSIR;

							if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_RCHGP)) {
								/* _hoops_PAH'_hoops_RA _hoops_SHH _hoops_ISPSP -- _hoops_ICCAR _hoops_PRAR... */
								HI_Propagate_Scoped_Activity (_hoops_RIGC, (_hoops_SIHIR *)_hoops_SRCP,
												_hoops_GSCCA,
												&_hoops_AISGS->_hoops_RCHS);
							}
							else {
								/* _hoops_RAAP _hoops_AACAR _hoops_CGGR */
								_hoops_IPSGS (_hoops_RIGC, _hoops_SRCP,
										_hoops_AISGS->_hoops_RCHS.left,
										_hoops_AHIA (_hoops_AISGS->_hoops_RCHS.right,
											 _hoops_IHPIP->_hoops_RCHS.left),
										_hoops_IAAA (_hoops_AISGS->_hoops_RCHS.bottom,
											 _hoops_IHPIP->_hoops_RCHS.bottom),
										_hoops_AISGS->_hoops_RCHS.top);

								/* _hoops_SCIA _hoops_CGGR */
								_hoops_IPSGS (_hoops_RIGC, _hoops_SRCP,
										_hoops_IAAA (_hoops_AISGS->_hoops_RCHS.left,
											 _hoops_IHPIP->_hoops_RCHS.left),
										_hoops_AISGS->_hoops_RCHS.right,
										_hoops_IAAA (_hoops_AISGS->_hoops_RCHS.bottom,
											 _hoops_IHPIP->_hoops_RCHS.top),
										_hoops_AISGS->_hoops_RCHS.top);

								/* _hoops_RPHR _hoops_CGGR */
								_hoops_IPSGS (_hoops_RIGC, _hoops_SRCP,
										_hoops_IAAA (_hoops_AISGS->_hoops_RCHS.left,
											 _hoops_IHPIP->_hoops_RCHS.right),
										_hoops_AISGS->_hoops_RCHS.right,
										_hoops_AISGS->_hoops_RCHS.bottom,
										_hoops_AHIA (_hoops_AISGS->_hoops_RCHS.top,
											 _hoops_IHPIP->_hoops_RCHS.top));

								/* _hoops_PRPC _hoops_CGGR */
								_hoops_IPSGS (_hoops_RIGC, _hoops_SRCP,
										_hoops_AISGS->_hoops_RCHS.left,
										_hoops_AHIA (_hoops_AISGS->_hoops_RCHS.right,
											 _hoops_IHPIP->_hoops_RCHS.right),
										_hoops_AISGS->_hoops_RCHS.bottom,
										_hoops_AHIA (_hoops_AISGS->_hoops_RCHS.top,
											 _hoops_IHPIP->_hoops_RCHS.bottom));
							}

							_hoops_SRCP->_hoops_PHSI |= _hoops_SHSIR;
						}

						/* _hoops_SCAC _hoops_IHHH _hoops_AGIRH */
						_hoops_SRCP->_hoops_CPGPR &= ~_hoops_AHPGP; /* _hoops_HIAP */
						_hoops_IRSGS (_hoops_RIGC, _hoops_SRCP, 0);
					}
				}
			}
		}	break;

		case HK_WINDOW_PATTERN: {
			_hoops_CHCAP *	_hoops_CISGS = (_hoops_CHCAP *)_hoops_SISCA;
			int					_hoops_SHSGS = _hoops_SRCP->_hoops_IGCCA;

			HI_Less_Transparencies (_hoops_RIGC, _hoops_SRCP, _hoops_SHSGS);
			if (_hoops_SISCA == null ||
				(_hoops_CISGS->value != FP_WINDOW_TRANSPARENT &&
					_hoops_CISGS->value != FP_WINDOW_TRANS_NO_ZCLEAR)) {
				_hoops_SRCP->_hoops_PHSI &= ~_hoops_RCHGP;
				if (_hoops_GPSGS (_hoops_SRCP)) _hoops_GASGS (_hoops_RIGC, _hoops_SRCP, 0);
			}
			else {
				_hoops_SRCP->_hoops_PHSI |= _hoops_RCHGP;
				if (_hoops_GPSGS (_hoops_SRCP)) _hoops_HRSGS (_hoops_RIGC, _hoops_SRCP, 0);
			}
			HI_More_Transparencies (_hoops_RIGC, _hoops_SRCP, _hoops_SHSGS);
		}	break;

		case HK_SELECTABILITY: {
			/* _hoops_PAGA: _hoops_HAR "_hoops_SISGS" _hoops_GPP _hoops_AHAR! */
			_hoops_SRSGS (_hoops_RIGC, _hoops_SRCP, 0);		/* _hoops_HGCR _hoops_RH _hoops_CGRHH _hoops_AIRC _hoops_RPHR */
		}	break;

		case HK_VISIBILITY: {
			_hoops_RSAIR *		_hoops_GCSGS = (_hoops_RSAIR *)_hoops_PISCA;
			_hoops_RSAIR *		_hoops_RCSGS = (_hoops_RSAIR *)_hoops_SISCA;

			_hoops_ACHR			_hoops_HSIPH,
								_hoops_ACSGS,
								_hoops_PCSGS;
			bool				erase = false,
								_hoops_HCSGS = false,
								_hoops_ICSGS = false,
								_hoops_CCSGS = false,
								_hoops_SCSGS = false;

			_hoops_SRCP->_hoops_PHSI &= ~(_hoops_GCHGP|_hoops_SIHGP);
			if (_hoops_SISCA != null && BIT (_hoops_RCSGS->mask, T_WINDOWS)) {
				if (BIT (_hoops_RCSGS->value, T_WINDOWS))
					_hoops_SRCP->_hoops_PHSI |= _hoops_SIHGP;
				else
					_hoops_SRCP->_hoops_PHSI |= _hoops_GCHGP;
			}

			/* _hoops_CACH _hoops_PCPA _hoops_GHCA _hoops_HS _hoops_GACHR _hoops_SIGC _hoops_PAR _hoops_GHCA _hoops_HS _hoops_GACHR _hoops_PSIPR */

			if (_hoops_PISCA == null) {
				_hoops_HSIPH = _hoops_RCSGS->value;
				_hoops_ACSGS = _hoops_RCSGS->mask & ~_hoops_RCSGS->value;
			}
			else if (_hoops_SISCA == null) {
				_hoops_HSIPH = _hoops_GCSGS->mask & ~_hoops_GCSGS->value;
				_hoops_ACSGS = _hoops_GCSGS->value;
			}
			else {
				/* _hoops_CSAP _hoops_PSAP _hoops_PPR _hoops_HRGR _hoops_HA _hoops_RHGC */
				_hoops_HSIPH = (_hoops_GCSGS->mask & ~_hoops_GCSGS->value) &
						  ~_hoops_RCSGS->mask;

				/* _hoops_CSAP _hoops_PSAP _hoops_PAR _hoops_RHGC _hoops_PPR _hoops_HRGR _hoops_HA _hoops_GPP */
				_hoops_HSIPH |= _hoops_RCSGS->value & ~_hoops_GCSGS->value;

				/* _hoops_CSAP _hoops_RHGC _hoops_PPR _hoops_HRGR _hoops_HA _hoops_PSAP */
				_hoops_ACSGS = (_hoops_RCSGS->mask & ~_hoops_RCSGS->value) &
							~_hoops_GCSGS->mask;

				/* _hoops_CSAP _hoops_GPP _hoops_PPR _hoops_HRGR _hoops_HA _hoops_RHGC _hoops_PAR _hoops_PSAP */
				_hoops_ACSGS |= _hoops_GCSGS->value & ~_hoops_RCSGS->value;
			}

			if (BIT (_hoops_HSIPH, T_WINDOWS) && _hoops_GPSGS (_hoops_SRCP)) {
				_hoops_SRCP->_hoops_CPGPR &= ~_hoops_AHPGP; /* _hoops_HIAP */
				_hoops_RASGS (_hoops_RIGC, _hoops_SRCP, 0);
			}
			else if (BIT (_hoops_ACSGS, T_WINDOWS) &&
					 _hoops_GPSGS (_hoops_SRCP) &&
					 !BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR)) {
				_hoops_CPSGS (_hoops_RIGC, _hoops_SRCP);

				_hoops_SRSGS (_hoops_RIGC, _hoops_SRCP, 0); /* _hoops_IRHH _hoops_RCRR _hoops_IS _hoops_GSSGS (_hoops_RPP _hoops_RSSGS) */
			}

			_hoops_PCSGS = _hoops_HSIPH | _hoops_ACSGS;

#if 0
			if (BIT (_hoops_PCSGS, T_SHADOW_RECEIVING) &&
				BIT (_hoops_SRCP->_hoops_RCGC, T_FACES))
				_hoops_HCSGS = _hoops_ICSGS = true;

			if (BIT (_hoops_PCSGS, _hoops_SHHGP) &&
				BIT (_hoops_SRCP->_hoops_RCGC, T_FACES))
				_hoops_CCSGS = _hoops_HCSGS = _hoops_ICSGS = true;

			if (BIT (_hoops_PCSGS, _hoops_GIHGP) &&
				BIT (_hoops_SRCP->_hoops_RCGC, T_ANY_LIGHTS))
				_hoops_CCSGS = _hoops_HCSGS = _hoops_ICSGS = true;
#endif

			if (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, _hoops_ACSGS & T_ANY_DRAWABLE_GEOMETRY))
				erase = _hoops_CCSGS = _hoops_ICSGS = true;

			if (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, _hoops_HSIPH & T_ANY_DRAWABLE_GEOMETRY))
				_hoops_ICSGS = true;

			if (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, T_EDGES)) {
				if (ANYBIT (_hoops_ACSGS, T_ANY_EDGE))
					erase = _hoops_CCSGS = _hoops_ICSGS = true;
				else if (ANYBIT (_hoops_HSIPH, T_ANY_EDGE))
					_hoops_ICSGS = true;
			}

			if (BIT (_hoops_SRCP->_hoops_RCGC, _hoops_PCSGS & T_FACES))
				_hoops_HCSGS = _hoops_ICSGS = _hoops_SCSGS = true;

			if (BIT (_hoops_SRCP->_hoops_RCGC, _hoops_PCSGS & T_ANY_LIGHTS))
				_hoops_CCSGS = _hoops_HCSGS = _hoops_ICSGS = true;

			if (BIT (_hoops_PCSGS, T_ANY_LIGHTS) && BIT (_hoops_SRCP->_hoops_RCGC, T_FACES))
				_hoops_HCSGS = _hoops_ICSGS = true;

			if (BIT (_hoops_SRCP->_hoops_RCGC, _hoops_PCSGS & T_CUTTING_PLANES))
				erase = _hoops_HCSGS = _hoops_ICSGS = _hoops_SCSGS = true;

			if (BIT (_hoops_SRCP->_hoops_RCGC, T_FACES) && BIT (_hoops_PCSGS, T_CUT_GEOMETRY))
				erase = _hoops_ICSGS = _hoops_SCSGS = true;

			if (_hoops_SISCA == null && _hoops_GCSGS->_hoops_PRIGA.mask ||
				_hoops_PISCA == null && _hoops_RCSGS->_hoops_PRIGA.mask)
				erase = _hoops_ICSGS = true;
			else if (_hoops_SISCA != null && _hoops_PISCA != null &&
					 (_hoops_RCSGS->_hoops_PRIGA.mask &
					  _hoops_RCSGS->_hoops_PRIGA.value) !=
					 (_hoops_GCSGS->_hoops_PRIGA.mask &
					  _hoops_GCSGS->_hoops_PRIGA.value))
				erase = _hoops_ICSGS = true;

			if (BIT (_hoops_HSIPH, T_TEXT))
				_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_RSCCA);


			if (_hoops_SCSGS)
				_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_SCPGP);


			if (_hoops_CCSGS) {
				/* '_hoops_AHPIP' _hoops_HRGR _hoops_GIASI _hoops_RH _hoops_RGAR _hoops_SPAHR _hoops_SR _hoops_HS _hoops_HPGR _hoops_RH
				 * _hoops_HRGS _hoops_IS _hoops_GGHC _hoops_PCCP _hoops_ASSGS _hoops_SHSC-_hoops_HIRA _hoops_AIIAP...
				 */
				if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) erase = true;
			}

			/* _hoops_AA _hoops_SCH */
			if (_hoops_HCSGS) {
				if (erase)
					_hoops_PASGS (_hoops_RIGC, _hoops_SRCP, _hoops_CCPGP|_hoops_SSCCA);
				else /* _hoops_RPP (_hoops_PSSGS) */ /* (_hoops_CGH _hoops_SHR _hoops_SHH _hoops_IHPR) */
					_hoops_HASGS (_hoops_RIGC, _hoops_SRCP, _hoops_CCPGP|_hoops_SSCCA);
			}
			else {
				if (erase)
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_CCPGP|_hoops_SSCCA);
				else if (_hoops_ICSGS)
					_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_CCPGP|_hoops_SSCCA);
			}
		}	break;

		case HK_COLOR_MAP: {
#ifndef DISABLE_COLOR_MAPS
			_hoops_RHAH *		_hoops_SSPRA = (_hoops_RHAH *)_hoops_PISCA;
			_hoops_RHAH *		_hoops_GGHRA = (_hoops_RHAH *)_hoops_SISCA;

			if (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, _hoops_GAHGP) || _hoops_GPSGS (_hoops_SRCP))
				_hoops_CASGS (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);

			if (_hoops_SISCA != null) {
				Named_Material		*mat = _hoops_GGHRA->_hoops_HAA;
				int						count = _hoops_GGHRA->length;

				while (count--) {
					if (ANYBIT (mat->_hoops_PRGRA, M_TRANSMISSION|_hoops_IIARA)) {
						HI_More_Transparencies (_hoops_RIGC, _hoops_SRCP, 1);
						break;
					}
					++mat;
				}
			}

			if (_hoops_PISCA != null) {
				Named_Material		*mat = _hoops_SSPRA->_hoops_HAA;
				int						count = _hoops_SSPRA->length;

				while (count--) {
					if (ANYBIT (mat->_hoops_PRGRA, M_TRANSMISSION|_hoops_IIARA)) {
						HI_Less_Transparencies (_hoops_RIGC, _hoops_SRCP, 1);
						break;
					}
					++mat;
				}
			}
#endif
		}	break;

		case HK_DRIVER_OPTIONS: {
			_hoops_GAPIR *	_hoops_HSSGS = (_hoops_GAPIR *)_hoops_PISCA;
			_hoops_GAPIR *	_hoops_ISSGS = (_hoops_GAPIR *)_hoops_SISCA;

			/* _hoops_HHSA _hoops_RH _hoops_RHPP _hoops_IS _hoops_IHSH _hoops_HPGR _hoops_SCH */
			_hoops_SRSGS (_hoops_RIGC, _hoops_SRCP, _hoops_CCPGP);

			if (_hoops_HSSGS == null && _hoops_ISSGS->_hoops_ASHRP.mask ||
				_hoops_ISSGS == null && _hoops_HSSGS->_hoops_ASHRP.mask ||
				_hoops_HSSGS != null && _hoops_ISSGS != null &&
				((_hoops_ISSGS->_hoops_ASHRP.mask ^ _hoops_ISSGS->_hoops_ASHRP.mask) ||
				 (_hoops_ISSGS->_hoops_ASHRP.mask & (_hoops_HSSGS->_hoops_ASHRP.value ^ _hoops_ISSGS->_hoops_ASHRP.value)) ||
				 _hoops_ISSGS->_hoops_ASHRP._hoops_GSHRP != _hoops_HSSGS->_hoops_ASHRP._hoops_GSHRP ||
				 _hoops_ISSGS->_hoops_ASHRP._hoops_RSHRP != _hoops_HSSGS->_hoops_ASHRP._hoops_RSHRP ||
				 _hoops_ISSGS->_hoops_ASHRP._hoops_SHGP != _hoops_HSSGS->_hoops_ASHRP._hoops_SHGP ||
				 _hoops_ISSGS->_hoops_AIPGA != _hoops_HSSGS->_hoops_AIPGA))
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_ACPGP);
		}	break;

		case HK_WINDOW_FRAME: {
			_hoops_GSAIR *		_hoops_CSSGS = (_hoops_GSAIR *)_hoops_PISCA;
			_hoops_GSAIR *		_hoops_SSSGS = (_hoops_GSAIR *)_hoops_SISCA;

			if (_hoops_GPSGS (_hoops_SRCP)) {
				if ((_hoops_PISCA == null || BIT(_hoops_CSSGS->flags, _hoops_AIARP)) &&
					(_hoops_SISCA == null || BIT(_hoops_SSSGS->flags, _hoops_GIARP))) {
					/* _hoops_RPP _hoops_SCH _hoops_CSAP _hoops_HGARH _hoops_PAR _hoops_RHGC _hoops_PPR _hoops_SCH _hoops_HRGR _hoops_RRGCI
					 * _hoops_GGGRS _hoops_PAR _hoops_RHGC, _hoops_PSCR _hoops_SR _hoops_RRP _hoops_IS _hoops_AA _hoops_IRS _hoops_GRH
					 * _hoops_RGGRS _hoops_IIGR _hoops_RH _hoops_PCIRA _hoops_PGGA _hoops_RH _hoops_HISAR-_hoops_PAPA _hoops_SPSIR
					 * _hoops_AGGRS _hoops_GGGRS _hoops_SPHGR _hoops_IRS _hoops_IGRH _hoops_IHH (_hoops_SHCAR, _hoops_CGPR _hoops_SSIA'_hoops_ASAR
					 * _hoops_ASSA _hoops_HGARH _hoops_SPHGR.) _hoops_GHRHH.
					 */

					if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) {
						Window				*window;

						window = HI_Find_Scoping_Window(_hoops_SRCP);

						_hoops_SRCP->_hoops_CPGPR &= ~_hoops_AHPGP; /* _hoops_HIAP */
						_hoops_SRCP->_hoops_PHSI &= ~_hoops_SHSIR;		/* _hoops_AGSIP */
						HI_Propagate_Scoped_Activity (_hoops_RIGC, (_hoops_SIHIR *)_hoops_SRCP,
													  _hoops_GSCCA|
													  _hoops_CCPGP,
													  &window->_hoops_RCHS);
						_hoops_SRCP->_hoops_PHSI |= _hoops_SHSIR;
						_hoops_SRCP->_hoops_CPGPR &= ~_hoops_AHPGP; /* _hoops_HIAP */
					}
					else {
						_hoops_HRSGS (_hoops_RIGC, _hoops_SRCP, 0);
					}
				}
				else if (ALLBITS (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR |
												 _hoops_RCHGP)) {
						Window				*window;

						/* _hoops_HHACR _hoops_HCHSR _hoops_GRS _hoops_PGGRS _hoops_CIPH _hoops_ASSA _hoops_RH
						 * _hoops_RRH _hoops_RPPS, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IRS _hoops_IHIR _hoops_AIIAP _hoops_IIGR _hoops_RH
						 * _hoops_PIIRC _hoops_ISPH */

						window = HI_Find_Scoping_Window(_hoops_SRCP);
						HI_Propagate_Scoped_Activity (_hoops_RIGC,(_hoops_SIHIR *)_hoops_SRCP,
													  _hoops_GSCCA|
													  _hoops_CCPGP,
													  &window->_hoops_RCHS);
				}

				_hoops_RASGS (_hoops_RIGC, _hoops_SRCP, 0);
			}
		}	break;

		case HK_HEURISTICS: {
			_hoops_GHAIR *			_hoops_PCIIH = (_hoops_GHAIR *)_hoops_PISCA;
			_hoops_GHAIR *			_hoops_HCIIH = (_hoops_GHAIR *)_hoops_SISCA;
			_hoops_CGSP		_hoops_HGGRS=0, _hoops_IGGRS=0;
			short					_hoops_CGGRS=0, _hoops_SGGRS = 0;
			int						_hoops_SHSGS = _hoops_SRCP->_hoops_IGCCA;


			HI_Clean_Static_Tree(_hoops_RIGC, _hoops_SRCP);

			if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR))
				_hoops_SHSGS = 0;			/* _hoops_RPPS _hoops_GRS _hoops_HGGC _hoops_RIS _hoops_RH _hoops_RPR */

			/* _hoops_CAHP _hoops_HHH _hoops_CPGGR */
			if (_hoops_SISCA == null && _hoops_PISCA != null) {
				_hoops_IGGRS = _hoops_PCIIH->value;
				_hoops_HGGRS = _hoops_PCIIH->mask & ~_hoops_PCIIH->value;
				if (ANYBIT (_hoops_IGGRS, _hoops_HPIRP))
					_hoops_HGGRS &= ~_hoops_HPIRP;
				_hoops_SGGRS = _hoops_PCIIH->_hoops_APH.value;
				_hoops_CGGRS = _hoops_PCIIH->_hoops_APH.mask & ~_hoops_PCIIH->_hoops_APH.value;
			}
			else if (_hoops_PISCA == null && _hoops_SISCA != null) {
				_hoops_HGGRS = _hoops_HCIIH->value;
				_hoops_IGGRS = _hoops_HCIIH->mask & ~_hoops_HCIIH->value;
				/* _hoops_GA'_hoops_RA _hoops_RPR _hoops_GII _hoops_HHCI _hoops_IHIS _hoops_CAPRR _hoops_SR _hoops_CHR _hoops_RGSR _hoops_PSAP _hoops_HA _hoops_RPP _hoops_IAHAR _hoops_GII _hoops_GPP */
				if (ANYBIT (_hoops_HGGRS, _hoops_HPIRP))
					_hoops_IGGRS &= ~_hoops_HPIRP;
				_hoops_CGGRS = _hoops_HCIIH->_hoops_APH.value;
				_hoops_SGGRS = _hoops_HCIIH->_hoops_APH.mask & ~_hoops_HCIIH->_hoops_APH.value;
			}
			else if (_hoops_PISCA != null && _hoops_SISCA != null) {
				/* _hoops_CSAP _hoops_PSAP _hoops_PPR _hoops_HRGR _hoops_HA _hoops_RHGC */
				_hoops_HGGRS = (_hoops_PCIIH->mask & ~_hoops_PCIIH->value) &
							 ~_hoops_HCIIH->mask;
				_hoops_CGGRS = (_hoops_PCIIH->_hoops_APH.mask & ~_hoops_PCIIH->_hoops_APH.value) &
							 ~_hoops_HCIIH->_hoops_APH.mask;

				/* _hoops_CSAP _hoops_PSAP _hoops_PAR _hoops_RHGC _hoops_PPR _hoops_HRGR _hoops_HA _hoops_GPP */
				_hoops_HGGRS |= _hoops_HCIIH->value & ~_hoops_PCIIH->value;
				_hoops_CGGRS |= _hoops_HCIIH->_hoops_APH.value & ~_hoops_PCIIH->_hoops_APH.value;

				/* _hoops_CSAP _hoops_RHGC _hoops_PPR _hoops_HRGR _hoops_HA _hoops_PSAP */
				_hoops_IGGRS = (_hoops_HCIIH->mask & ~_hoops_HCIIH->value) &
							  ~_hoops_PCIIH->mask;
				_hoops_SGGRS = (_hoops_HCIIH->_hoops_APH.mask & ~_hoops_HCIIH->_hoops_APH.value) &
							  ~_hoops_PCIIH->_hoops_APH.mask;

				/* _hoops_GA'_hoops_RA _hoops_RPR _hoops_GII _hoops_HHCI _hoops_IHIS _hoops_CAPRR _hoops_SR _hoops_CHR _hoops_RGSR _hoops_PSAP _hoops_HA _hoops_RPP _hoops_IAHAR _hoops_GII _hoops_GPP */
				if (ANYBIT (_hoops_HGGRS, _hoops_HPIRP))
					_hoops_IGGRS &= ~_hoops_HPIRP;

				/* _hoops_CSAP _hoops_GPP _hoops_PPR _hoops_HRGR _hoops_HA _hoops_RHGC _hoops_PAR _hoops_PSAP */
				_hoops_IGGRS |= _hoops_PCIIH->value & ~_hoops_HCIIH->value;
				_hoops_SGGRS |= _hoops_PCIIH->_hoops_APH.value & ~_hoops_HCIIH->_hoops_APH.value;
			}

			/* _hoops_CCIH _hoops_PCHC _hoops_SGI _hoops_GSSRH _hoops_CGRGS _hoops_CPGGR! */

			_hoops_SRCP->_hoops_PHSI &= ~(_hoops_IIHGP|_hoops_CIHGP);
			if (_hoops_SISCA != null && BIT (_hoops_HCIIH->mask, _hoops_PRIRP)) {
				if (BIT (_hoops_HCIIH->value, _hoops_PRIRP)) {
					if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_GHHGP))
						HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_GHHGP);
					_hoops_SRCP->_hoops_PHSI |= _hoops_IIHGP;
				}
				else
					_hoops_SRCP->_hoops_PHSI |= _hoops_CIHGP;
			}

			if (BIT (_hoops_HGGRS | _hoops_IGGRS, _hoops_CCIAA))
				HI_Antiquate_Bounding (_hoops_SRCP, true);

			/* _hoops_GRH-_hoops_AGIR _hoops_RH _hoops_APHSR _hoops_PCPIP, _hoops_SRS */
			if (BIT (_hoops_HGGRS, _hoops_HPIRP)) {
				if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_AHASA))
					HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_AHASA);

				if (_hoops_SHSGS > 0)
					HI_Less_Transparencies (_hoops_RIGC, _hoops_SRCP, _hoops_SHSGS);

				if (!BIT (_hoops_IGGRS, _hoops_HPIRP)) {
					/* _hoops_IAHAR _hoops_GPP - _hoops_HGCR _hoops_RH _hoops_RHGS _hoops_CIPH _hoops_SGSIP */
					_hoops_SRCP->_hoops_PHSI &= ~(_hoops_GIGSA|_hoops_RIGSA);
					_hoops_SRCP->_hoops_CPGPR &= ~_hoops_AHPGP; /* _hoops_HIAP */
					if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) {
						/* _hoops_IAHAR _hoops_GPP _hoops_APHSR _hoops_RPPS */
						if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GCHGP))
							HI_Propagate_Scoped_Activity (_hoops_RIGC,(_hoops_SIHIR *)_hoops_SRCP,
											_hoops_GSCCA|_hoops_SSCCA,
											&HI_Find_Scoping_Window(_hoops_SRCP)->_hoops_RCHS);
					}
					else {
						/* _hoops_IAHAR _hoops_GPP _hoops_APHSR _hoops_CPAP _hoops_PAR _hoops_HGHIP */
						if (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, T_ANY_DRAWABLE_GEOMETRY)) {
							_hoops_SASGS (_hoops_RIGC, _hoops_SRCP, _hoops_GHSGS |
												 _hoops_RAGGA|
												 _hoops_SCPGP|
												 _hoops_PISSR|
												 _hoops_RPSIR|
												 _hoops_SSCCA);
						}
						else if (BIT (_hoops_SRCP->_hoops_RCGC, T_WINDOWS))
							_hoops_CASGS (_hoops_RIGC, _hoops_SRCP, 0);
					}
				}
				else {	/* _hoops_SIGSP _hoops_IS _hoops_IRS _hoops_HAGH _hoops_HHCI _hoops_IHCI _hoops_CCH */
					Activity		_hoops_ASGGS = _hoops_SRCP->_hoops_CPGPR;

					/* _hoops_AIIAP _hoops_GSSRH _hoops_HGAPA _hoops_SGI _hoops_IS _hoops_SAIPR _hoops_AIIAP _hoops_CPSRR */
					_hoops_SASGS (_hoops_RIGC, _hoops_SRCP, _hoops_GHSGS);
					_hoops_SRCP->_hoops_PHSI &= ~(_hoops_GIGSA|_hoops_RIGSA);

					/* _hoops_HIH _hoops_IRHH _hoops_RCRR _hoops_SR _hoops_AIIAP _hoops_RH _hoops_HIRA _hoops_SIHH _hoops_RH _hoops_CSIIP */
					/* _hoops_CR _hoops_PHHIP _hoops_GHCA _hoops_HS _hoops_RIAGR _hoops_CPGGR, _hoops_SR _hoops_GA'_hoops_RA _hoops_HHGC _hoops_PA _hoops_ARI _hoops_IS _hoops_IHSH _hoops_PII _hoops_SCH _hoops_CSAP
					 * '_hoops_AIAH _hoops_GIR' _hoops_HIS _hoops_SR _hoops_SCAC _hoops_RH _hoops_CPGGR _hoops_PPR _hoops_GACC _hoops_GRGRS
					 * _hoops_PA _hoops_SR _hoops_SIGR _hoops_ARPP
					 */
					_hoops_SRCP->_hoops_CPGPR = 0;
					_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_ASGGS | _hoops_IPPGP|_hoops_IHPGP);
				}

				_hoops_SRCP->_hoops_PHSI |= _hoops_RIGSA;

				if (_hoops_SHSGS > 0)
					HI_More_Transparencies (_hoops_RIGC, _hoops_SRCP, _hoops_SHSGS);

				if (BIT (_hoops_HGGRS, _hoops_IRIRP)) {
					if (!ALLBITS(_hoops_HGGRS, _hoops_HPIRP))
						_hoops_SRCP->_hoops_PHSI |= _hoops_SCHGP;
					HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_ASPCR);
				}
			}
			else if (ANYBIT (_hoops_IGGRS, _hoops_HPIRP)) {
				/* _hoops_IRHH *_hoops_RCRR* _hoops_SR _hoops_HGCR _hoops_AGIRH _hoops_SIGSA */
				if (_hoops_SHSGS > 0)
					HI_Less_Transparencies (_hoops_RIGC, _hoops_SRCP, _hoops_SHSGS);
				_hoops_SRCP->_hoops_PHSI &= ~(_hoops_SCHGP|_hoops_GIGSA|_hoops_RIGSA);
				if (_hoops_SHSGS > 0)
					HI_More_Transparencies (_hoops_RIGC, _hoops_SRCP, _hoops_SHSGS);

				Bounding    bounding = _hoops_SRCP->bounding;
				_hoops_SRCP->bounding = null;
				HI_Propagate_Bounding (_hoops_RIGC, _hoops_SRCP, bounding, null);

				_hoops_SRCP->_hoops_CPGPR &= ~_hoops_AHPGP; /* _hoops_HIAP */

				if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) { /* _hoops_GRH _hoops_AGIR */
					if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GCHGP))
						_hoops_CASGS (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
				}
				else {
					if (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, _hoops_PAHGP)) {
						_hoops_CASGS (_hoops_RIGC, _hoops_SRCP, _hoops_RAGGA|
												 _hoops_SCPGP|
												 _hoops_PISSR|
												 _hoops_RPSIR|
												 _hoops_SSCCA);
					}
				}
			}
			else if (ANYBIT (_hoops_HGGRS, _hoops_IGIRP) &&
					 ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, _hoops_AAHGP))
				_hoops_PASGS (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
			else if (ANYBIT (_hoops_HGGRS, _hoops_CGCS|
										 _hoops_GRIRP) &&
					 BIT (_hoops_SRCP->_hoops_RCGC, T_FACES))
				_hoops_PASGS (_hoops_RIGC, _hoops_SRCP, 0);
			else if (ANYBIT (_hoops_IGGRS, _hoops_RRIRP) &&
					 ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, _hoops_AAHGP)) /* _hoops_HHSA _hoops_IHIR _hoops_AIIAP */
				_hoops_PASGS (_hoops_RIGC, _hoops_SRCP, 0);
			else if (ANYBIT (_hoops_HGGRS, _hoops_PICAR|
										 _hoops_IRI) &&
					 ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, T_ANY_DRAWABLE_GEOMETRY))
				_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, 0);
			else if (ANYBIT (_hoops_HGGRS, _hoops_CGIRP) &&
					 BIT (_hoops_SRCP->_hoops_RCGC, T_FACES))
				_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, 0);
			else if (ANYBIT (_hoops_IGGRS, _hoops_SASA|
										  _hoops_GPSA|
										  _hoops_SGIRP) &&
					 BIT (_hoops_SRCP->_hoops_RCGC, T_FACES))
				_hoops_HASGS (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
			else if (ANYBIT (_hoops_HGGRS, _hoops_SASA|
										 _hoops_GPSA) &&
					 BIT (_hoops_SRCP->_hoops_RCGC, T_FACES))
				_hoops_HASGS (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
			else if (ANYBIT (_hoops_CGGRS | _hoops_SGGRS, Heur_Culling_EXTENT) ||
					 _hoops_SISCA != null && _hoops_PISCA != null &&
					 BIT (_hoops_HCIIH->_hoops_APH.value, Heur_Culling_EXTENT) &&
						_hoops_HCIIH->_hoops_APH._hoops_GRGC !=
						_hoops_PCIIH->_hoops_APH._hoops_GRGC)
				_hoops_PASGS (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
			else if (ANYBIT (_hoops_CGGRS | _hoops_SGGRS, _hoops_RIHS) ||
					 _hoops_SISCA != null && _hoops_PISCA != null &&
					 BIT (_hoops_HCIIH->_hoops_APH.value, _hoops_RIHS) &&
						_hoops_HCIIH->_hoops_APH._hoops_GCHS !=
						_hoops_PCIIH->_hoops_APH._hoops_GCHS)
				_hoops_PASGS (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
			else if (ANYBIT (_hoops_CGGRS | _hoops_SGGRS, _hoops_RHIRP) ||
					 _hoops_SISCA != null && _hoops_PISCA != null &&
					 BIT (_hoops_HCIIH->_hoops_APH.value, _hoops_RHIRP) &&
						 _hoops_HCIIH->_hoops_APH._hoops_PCHS !=
						 _hoops_PCIIH->_hoops_APH._hoops_PCHS)
				 _hoops_PASGS (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
			else if (ANYBIT (_hoops_CGGRS | _hoops_SGGRS, _hoops_HHIRP) ||
					 _hoops_SISCA != null && _hoops_PISCA != null &&
					 BIT (_hoops_HCIIH->_hoops_APH.value, _hoops_HHIRP) &&
						 _hoops_HCIIH->_hoops_APH._hoops_SHHS !=
						 _hoops_PCIIH->_hoops_APH._hoops_SHHS)
				 _hoops_PASGS (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
			else if (ANYBIT (_hoops_HGGRS, _hoops_SICIA|
										 _hoops_SRIRP) ||
					 ANYBIT (_hoops_IGGRS, _hoops_SICIA|
										  _hoops_SRIRP|
										  _hoops_IRI) ||
					 (_hoops_SISCA != null && _hoops_PISCA != null &&
					  (BIT(_hoops_HCIIH->value,_hoops_SICIA) &&
						_hoops_HCIIH->_hoops_GCCIA !=
						_hoops_PCIIH->_hoops_GCCIA ||
					   BIT(_hoops_HCIIH->value,_hoops_SRIRP) &&
						(_hoops_HCIIH->_hoops_CCIRP._hoops_SPHPR !=
						 _hoops_PCIIH->_hoops_CCIRP._hoops_SPHPR ||
						 _hoops_HCIIH->_hoops_CCIRP.polyline !=
						 _hoops_PCIIH->_hoops_CCIRP.polyline))))
				_hoops_SRSGS (_hoops_RIGC, _hoops_SRCP, 0);

			/*	   _hoops_AGGC (_hoops_RRGRS, _hoops_ARGRS|
									   _hoops_PRGRS|
									   _hoops_HRGRS|
									   _hoops_IRGRS|
									   _hoops_CRGRS *//* ?? *//*) ||
				   _hoops_AGGC (_hoops_SRGRS, _hoops_GAGRS|
										_hoops_RAGRS|
										_hoops_AAGRS|
										_hoops_PAGRS|
										_hoops_HAGRS|
										_hoops_CRGRS *//* ?? *//*)
				_hoops_IAGRS! */
		}	break;

		case HK_RENDERING_OPTIONS: {

			_hoops_GHGI				_hoops_CAGRS, _hoops_SAGRS;
			_hoops_GHGI				_hoops_GPGRS, _hoops_RPGRS;
			_hoops_GHGI				_hoops_APGRS, _hoops_PPGRS;
			_hoops_GCRAP		_hoops_HPGRS, _hoops_IPGRS;
			_hoops_PPAAP			_hoops_CPGRS, _hoops_SPGRS;
			_hoops_SHCRP			_hoops_GHGRS, _hoops_RHGRS;

			// _hoops_HSSHH _hoops_IH _hoops_APSAR _hoops_GGR _hoops_RIRCP _hoops_ARAH-_hoops_AGRGI
			_hoops_HHAGP			_hoops_AHGRS = 0, _hoops_PHGRS = 0;
			Color_Object			_hoops_HHGRS = 0, _hoops_IHGRS = 0;
			_hoops_ACHR				_hoops_CHGRS = 0, _hoops_SHGRS = 0;
			_hoops_RRPHA				_hoops_GIGRS = 0, _hoops_RIGRS = 0;
			_hoops_GPCRP		_hoops_AIGRS = 0, _hoops_PIGRS = 0;
			_hoops_HGGAP		_hoops_HIGRS = 0, _hoops_IIGRS = 0;
			_hoops_SAGAP	_hoops_CIGRS = 0, _hoops_SIGRS = 0;

			_hoops_RHAIR *	_hoops_GCGRS = (_hoops_RHAIR *)_hoops_PISCA;
			_hoops_RHAIR *	_hoops_RCGRS = (_hoops_RHAIR *)_hoops_SISCA;

			if (_hoops_RCGRS && BIT (_hoops_RCGRS->_hoops_RSIAA, _hoops_ISGAP) &&
				(_hoops_RCGRS->_hoops_CHP.mask & _hoops_RCGRS->_hoops_CHP.value & ~_hoops_GPSP) != 0) {
				HI_More_Transparencies (_hoops_RIGC, _hoops_SRCP, 1);
				HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_ASRRA);
			}
			if (_hoops_GCGRS && BIT (_hoops_GCGRS->_hoops_RSIAA, _hoops_ISGAP) &&
				(_hoops_GCGRS->_hoops_CHP.mask & _hoops_GCGRS->_hoops_CHP.value & ~_hoops_GPSP) != 0) {
				HI_Less_Transparencies (_hoops_RIGC, _hoops_SRCP, 1);
			}

			/* _hoops_CAHP _hoops_HHH _hoops_CPGGR (_hoops_ACGRS _hoops_PCGRS) */
			if (_hoops_SISCA == null) {
				_hoops_SAGRS = _hoops_GCGRS->_hoops_RSIAA;
				_hoops_CAGRS = _hoops_GCGRS->_hoops_SCIAA & ~_hoops_GCGRS->_hoops_RSIAA;

				_hoops_RPGRS = _hoops_GCGRS->_hoops_RRRAP;
				_hoops_GPGRS = _hoops_GCGRS->_hoops_PSHCA & ~_hoops_GCGRS->_hoops_RRRAP;

				_hoops_PPGRS = _hoops_GCGRS->_hoops_GHRAP;
				_hoops_APGRS = _hoops_GCGRS->_hoops_ISHCA & ~_hoops_GCGRS->_hoops_GHRAP;

				if (_hoops_GCGRS->locks != null) {
					_hoops_PHGRS = _hoops_GCGRS->locks->normal.value._hoops_IPPGR;
					_hoops_AHGRS = _hoops_GCGRS->locks->normal.mask._hoops_IPPGR &
							   ~_hoops_GCGRS->locks->normal.value._hoops_IPPGR;

					_hoops_IHGRS = _hoops_GCGRS->locks->normal.value.color;
					_hoops_HHGRS = _hoops_GCGRS->locks->normal.mask.color &
							   ~_hoops_GCGRS->locks->normal.value.color;

					_hoops_SHGRS = _hoops_GCGRS->locks->normal.value._hoops_RGP;
					_hoops_CHGRS = _hoops_GCGRS->locks->normal.mask._hoops_RGP &
							   ~_hoops_GCGRS->locks->normal.value._hoops_RGP;
				}

				_hoops_IPGRS = _hoops_GCGRS->_hoops_RCRAP;
				_hoops_HPGRS = 0;

				_hoops_SPGRS = _hoops_GCGRS->_hoops_RGICA.value;
				_hoops_CPGRS = _hoops_GCGRS->_hoops_RGICA.mask &
						   ~_hoops_GCGRS->_hoops_RGICA.value;

				if (_hoops_GCGRS->_hoops_AIAIR != null) {
					_hoops_PIGRS = _hoops_GCGRS->_hoops_AIAIR->value;
					_hoops_AIGRS = _hoops_GCGRS->_hoops_AIAIR->mask &
							   ~_hoops_GCGRS->_hoops_AIAIR->value;
				}

				if (_hoops_GCGRS->_hoops_PRSI != null) {
					_hoops_RIGRS = _hoops_GCGRS->_hoops_PRSI->value;
					_hoops_GIGRS = _hoops_GCGRS->_hoops_PRSI->mask &
							   ~_hoops_GCGRS->_hoops_PRSI->value;
				}

				_hoops_RHGRS = _hoops_GCGRS->_hoops_SRI;
				_hoops_GHGRS = 0;

				if (_hoops_GCGRS->_hoops_HHAIR != null) {
					_hoops_IIGRS = _hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.value;
					_hoops_HIGRS = _hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.mask &
							   ~_hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.value;

					_hoops_SIGRS = _hoops_GCGRS->_hoops_HHAIR->_hoops_RHGGR.value;
					_hoops_CIGRS = _hoops_GCGRS->_hoops_HHAIR->_hoops_RHGGR.mask &
							   ~_hoops_GCGRS->_hoops_HHAIR->_hoops_RHGGR.value;
				}

			}
			else if (_hoops_PISCA == null) {
				_hoops_CAGRS = _hoops_RCGRS->_hoops_RSIAA;
				_hoops_SAGRS = _hoops_RCGRS->_hoops_SCIAA & ~_hoops_RCGRS->_hoops_RSIAA;

				_hoops_GPGRS = _hoops_RCGRS->_hoops_RRRAP;
				_hoops_RPGRS = _hoops_RCGRS->_hoops_PSHCA & ~_hoops_RCGRS->_hoops_RRRAP;

				_hoops_APGRS = _hoops_RCGRS->_hoops_GHRAP;
				_hoops_PPGRS = _hoops_RCGRS->_hoops_ISHCA & ~_hoops_RCGRS->_hoops_GHRAP;

				if (_hoops_RCGRS->locks != null) {
					_hoops_AHGRS = _hoops_RCGRS->locks->normal.value._hoops_IPPGR;
					_hoops_PHGRS = _hoops_RCGRS->locks->normal.mask._hoops_IPPGR &
								~_hoops_RCGRS->locks->normal.value._hoops_IPPGR;

					_hoops_HHGRS = _hoops_RCGRS->locks->normal.value.color;
					_hoops_IHGRS = _hoops_RCGRS->locks->normal.mask.color &
								~_hoops_RCGRS->locks->normal.value.color;

					_hoops_CHGRS = _hoops_RCGRS->locks->normal.value._hoops_RGP;
					_hoops_SHGRS = _hoops_RCGRS->locks->normal.mask._hoops_RGP &
								~_hoops_RCGRS->locks->normal.value._hoops_RGP;
				}

				_hoops_IPGRS = 0;
				_hoops_HPGRS = _hoops_RCGRS->_hoops_RCRAP;

				_hoops_CPGRS = _hoops_RCGRS->_hoops_RGICA.value;
				_hoops_SPGRS = _hoops_RCGRS->_hoops_RGICA.mask &
							~_hoops_RCGRS->_hoops_RGICA.value;

				if (_hoops_RCGRS->_hoops_AIAIR != null) {
					_hoops_AIGRS = _hoops_RCGRS->_hoops_AIAIR->value;
					_hoops_PIGRS = _hoops_RCGRS->_hoops_AIAIR->mask &
								~_hoops_RCGRS->_hoops_AIAIR->value;
				}

				if (_hoops_RCGRS->_hoops_PRSI != null) {
					_hoops_GIGRS = _hoops_RCGRS->_hoops_PRSI->value;
					_hoops_RIGRS = _hoops_RCGRS->_hoops_PRSI->mask &
								~_hoops_RCGRS->_hoops_PRSI->value;
				}

				_hoops_RHGRS = 0;
				_hoops_GHGRS = _hoops_RCGRS->_hoops_SRI;

				if (_hoops_RCGRS->_hoops_HHAIR != null) {
					_hoops_HIGRS = _hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.value;
					_hoops_IIGRS = _hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.mask &
								~_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.value;

					_hoops_CIGRS = _hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR.value;
					_hoops_SIGRS = _hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR.mask &
								~_hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR.value;
				}
			}
			else {
				/* _hoops_CSAP _hoops_PSAP _hoops_PPR _hoops_HRGR _hoops_HA _hoops_RHGC */
				_hoops_CAGRS = (_hoops_GCGRS->_hoops_SCIAA & ~_hoops_GCGRS->_hoops_RSIAA) &
							 ~_hoops_RCGRS->_hoops_SCIAA;
				_hoops_GPGRS = (_hoops_GCGRS->_hoops_PSHCA & ~_hoops_GCGRS->_hoops_RRRAP) &
							 ~_hoops_RCGRS->_hoops_PSHCA;
				_hoops_APGRS = (_hoops_GCGRS->_hoops_ISHCA & ~_hoops_GCGRS->_hoops_GHRAP) &
							 ~_hoops_RCGRS->_hoops_ISHCA;

				if (_hoops_GCGRS->locks != null) {

					_hoops_AHGRS = _hoops_GCGRS->locks->normal.mask._hoops_IPPGR &
								~_hoops_GCGRS->locks->normal.value._hoops_IPPGR;
					_hoops_HHGRS = _hoops_GCGRS->locks->normal.mask.color &
								~_hoops_GCGRS->locks->normal.value.color;
					_hoops_CHGRS = _hoops_GCGRS->locks->normal.mask._hoops_RGP &
								~_hoops_GCGRS->locks->normal.value._hoops_RGP;

					if (_hoops_RCGRS->locks != null) {
						_hoops_AHGRS &= ~_hoops_RCGRS->locks->normal.mask._hoops_IPPGR;
						_hoops_HHGRS &= ~_hoops_RCGRS->locks->normal.mask.color;
						_hoops_CHGRS &= ~_hoops_RCGRS->locks->normal.mask._hoops_RGP;
					}
				}

				_hoops_CPGRS = (_hoops_GCGRS->_hoops_RGICA.mask &
							 ~_hoops_GCGRS->_hoops_RGICA.value) &
							 ~_hoops_RCGRS->_hoops_RGICA.mask;

				if (_hoops_GCGRS->_hoops_AIAIR != null) {
					
					_hoops_AIGRS = _hoops_GCGRS->_hoops_AIAIR->mask &
								~_hoops_GCGRS->_hoops_AIAIR->value;
								
					if (_hoops_RCGRS->_hoops_AIAIR != null) 
						_hoops_AIGRS &= ~_hoops_RCGRS->_hoops_AIAIR->mask;
				}

				if (_hoops_GCGRS->_hoops_PRSI != null) {
					_hoops_GIGRS = _hoops_GCGRS->_hoops_PRSI->mask &
								 ~_hoops_GCGRS->_hoops_PRSI->value;
								
					if (_hoops_RCGRS->_hoops_PRSI != null)
						_hoops_GIGRS &= ~_hoops_RCGRS->_hoops_PRSI->mask;
				}

				if (_hoops_GCGRS->_hoops_HHAIR != null) {
					_hoops_HIGRS = _hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.mask &
								 ~_hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.value;
					_hoops_CIGRS = _hoops_GCGRS->_hoops_HHAIR->_hoops_RHGGR.mask &
								 ~_hoops_GCGRS->_hoops_HHAIR->_hoops_RHGGR.value;
					if (_hoops_RCGRS->_hoops_HHAIR != null) {
						_hoops_HIGRS &= ~_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.mask;
						_hoops_CIGRS &= ~_hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR.mask;
					}
				}

				/* _hoops_CSAP _hoops_PSAP _hoops_PAR _hoops_RHGC _hoops_PPR _hoops_HRGR _hoops_HA _hoops_GPP */
				_hoops_CAGRS |= _hoops_RCGRS->_hoops_RSIAA & ~_hoops_GCGRS->_hoops_RSIAA;
				_hoops_GPGRS |= _hoops_RCGRS->_hoops_RRRAP & ~_hoops_GCGRS->_hoops_RRRAP;
				_hoops_APGRS |= _hoops_RCGRS->_hoops_GHRAP & ~_hoops_GCGRS->_hoops_GHRAP;

				if (_hoops_RCGRS->locks != null) {
					_hoops_AHGRS |= _hoops_RCGRS->locks->normal.value._hoops_IPPGR;
					_hoops_HHGRS |= _hoops_RCGRS->locks->normal.value.color;
					_hoops_CHGRS |= _hoops_RCGRS->locks->normal.value._hoops_RGP;
					if (_hoops_GCGRS->locks != null) {
						_hoops_AHGRS &= ~_hoops_GCGRS->locks->normal.value._hoops_IPPGR;
						_hoops_HHGRS &= ~_hoops_GCGRS->locks->normal.value.color;
						_hoops_CHGRS &= ~_hoops_GCGRS->locks->normal.value._hoops_RGP;
					}
				}

				_hoops_CPGRS |= _hoops_RCGRS->_hoops_RGICA.value &
							~_hoops_GCGRS->_hoops_RGICA.value;

				if (_hoops_RCGRS->_hoops_AIAIR != null) {
					_hoops_AIGRS |= _hoops_RCGRS->_hoops_AIAIR->value;
					if (_hoops_GCGRS->_hoops_AIAIR != null)
						_hoops_AIGRS &= ~_hoops_GCGRS->_hoops_AIAIR->value;
				}

				if (_hoops_RCGRS->_hoops_PRSI != null) {
					_hoops_GIGRS |= _hoops_RCGRS->_hoops_PRSI->value;
					if (_hoops_GCGRS->_hoops_PRSI != null)
						_hoops_GIGRS &= ~_hoops_GCGRS->_hoops_PRSI->value;
				}

				if (_hoops_RCGRS->_hoops_HHAIR) {
					_hoops_HIGRS |= _hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.value;
					_hoops_CIGRS |= _hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR.value;
					if (_hoops_GCGRS->_hoops_HHAIR) {
						_hoops_HIGRS &= ~_hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.value;
						_hoops_CIGRS &= ~_hoops_GCGRS->_hoops_HHAIR->_hoops_RHGGR.value;
					}
				}

				/* _hoops_CSAP _hoops_RHGC _hoops_PPR _hoops_HRGR _hoops_HA _hoops_PSAP */
				_hoops_SAGRS = (_hoops_RCGRS->_hoops_SCIAA & ~_hoops_RCGRS->_hoops_RSIAA) & ~_hoops_GCGRS->_hoops_SCIAA;
				_hoops_RPGRS = (_hoops_RCGRS->_hoops_PSHCA & ~_hoops_RCGRS->_hoops_RRRAP) & ~_hoops_GCGRS->_hoops_PSHCA;
				_hoops_PPGRS = (_hoops_RCGRS->_hoops_ISHCA & ~_hoops_RCGRS->_hoops_GHRAP) &
								~_hoops_GCGRS->_hoops_ISHCA;

				if (_hoops_RCGRS->locks != null) {
					_hoops_PHGRS = _hoops_RCGRS->locks->normal.mask._hoops_IPPGR &
								 ~_hoops_RCGRS->locks->normal.value._hoops_IPPGR;
					_hoops_IHGRS = _hoops_RCGRS->locks->normal.mask.color &
								 ~_hoops_RCGRS->locks->normal.value.color;
					_hoops_SHGRS = _hoops_RCGRS->locks->normal.mask._hoops_RGP &
								 ~_hoops_RCGRS->locks->normal.value._hoops_RGP;
					if (_hoops_GCGRS->locks != null) {
						_hoops_PHGRS &= ~_hoops_GCGRS->locks->normal.mask._hoops_IPPGR;
						_hoops_IHGRS &= ~_hoops_GCGRS->locks->normal.mask.color;
						_hoops_SHGRS &= ~_hoops_GCGRS->locks->normal.mask._hoops_RGP;
					}
				}

				_hoops_SPGRS = (_hoops_RCGRS->_hoops_RGICA.mask &
							 ~_hoops_RCGRS->_hoops_RGICA.value) &
							~_hoops_GCGRS->_hoops_RGICA.mask;

				if (_hoops_RCGRS->_hoops_AIAIR != null) {
					_hoops_PIGRS = _hoops_RCGRS->_hoops_AIAIR->mask &
								 ~_hoops_RCGRS->_hoops_AIAIR->value;
					if (_hoops_GCGRS->_hoops_AIAIR != null) 
						_hoops_PIGRS &= ~_hoops_GCGRS->_hoops_AIAIR->mask;
				}

				if (_hoops_RCGRS->_hoops_PRSI != null) {
					_hoops_RIGRS = _hoops_RCGRS->_hoops_PRSI->mask &
								 ~_hoops_RCGRS->_hoops_PRSI->value;
					if (_hoops_GCGRS->_hoops_PRSI != null)
						_hoops_RIGRS &= ~_hoops_GCGRS->_hoops_PRSI->mask;
				}

				if (_hoops_RCGRS->_hoops_HHAIR != null) {
					_hoops_IIGRS = _hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.mask &
								 ~_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.value;
					_hoops_SIGRS = _hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR.mask &
									 ~_hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR.value;
					if (_hoops_GCGRS->_hoops_HHAIR != null) {
						_hoops_IIGRS &= ~_hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.mask;
						_hoops_SIGRS &= ~_hoops_GCGRS->_hoops_HHAIR->_hoops_RHGGR.mask;
					}
				}

				/* _hoops_CSAP _hoops_GPP _hoops_PPR _hoops_HRGR _hoops_HA _hoops_RHGC _hoops_PAR _hoops_PSAP */
				_hoops_SAGRS |= _hoops_GCGRS->_hoops_RSIAA & ~_hoops_RCGRS->_hoops_RSIAA;
				_hoops_RPGRS |= _hoops_GCGRS->_hoops_RRRAP & ~_hoops_RCGRS->_hoops_RRRAP;
				_hoops_PPGRS |= _hoops_GCGRS->_hoops_GHRAP & ~_hoops_RCGRS->_hoops_GHRAP;

				if (_hoops_GCGRS->locks != null) {
					_hoops_PHGRS |= _hoops_GCGRS->locks->normal.value._hoops_IPPGR;
					_hoops_IHGRS |= _hoops_GCGRS->locks->normal.value.color;
					_hoops_SHGRS |= _hoops_GCGRS->locks->normal.value._hoops_RGP;
					if (_hoops_RCGRS->locks != null) {
						_hoops_PHGRS &= ~_hoops_RCGRS->locks->normal.value._hoops_IPPGR;
						_hoops_IHGRS &= ~_hoops_RCGRS->locks->normal.value.color;
						_hoops_SHGRS &= ~_hoops_RCGRS->locks->normal.value._hoops_RGP;
					}
				}

				_hoops_SPGRS |= _hoops_GCGRS->_hoops_RGICA.value &
							 ~_hoops_RCGRS->_hoops_RGICA.value;

				if (_hoops_GCGRS->_hoops_AIAIR != null) {
					_hoops_PIGRS |= _hoops_GCGRS->_hoops_AIAIR->value;
					if (_hoops_RCGRS->_hoops_AIAIR != null)
						_hoops_PIGRS &= ~_hoops_RCGRS->_hoops_AIAIR->value;
				}

				if (_hoops_GCGRS->_hoops_PRSI != null) {
					_hoops_RIGRS |= _hoops_GCGRS->_hoops_PRSI->value;
					if (_hoops_RCGRS->_hoops_PRSI != null)
						_hoops_RIGRS &= ~_hoops_RCGRS->_hoops_PRSI->value;
				}

				if (_hoops_GCGRS->_hoops_HHAIR != null) {
					_hoops_IIGRS |= _hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.value;
					_hoops_SIGRS |= _hoops_GCGRS->_hoops_HHAIR->_hoops_RHGGR.value;
					if (_hoops_RCGRS->_hoops_HHAIR != null) {
						_hoops_IIGRS &= ~_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.value;
						_hoops_SIGRS &= ~_hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR.value;
					}
				}

				_hoops_HPGRS = _hoops_RCGRS->_hoops_RCRAP & ~_hoops_GCGRS->_hoops_RCRAP;
				_hoops_IPGRS = _hoops_GCGRS->_hoops_RCRAP & ~_hoops_RCGRS->_hoops_RCRAP;

				_hoops_GHGRS = _hoops_RCGRS->_hoops_SRI & ~_hoops_GCGRS->_hoops_SRI;
				_hoops_RHGRS = _hoops_GCGRS->_hoops_SRI & ~_hoops_RCGRS->_hoops_SRI;
			}

// _hoops_IGRI _hoops_SGHS _hoops_PGAP _hoops_GHCA _hoops_IGIRR _hoops_SHH _hoops_HGAS _hoops_SIHH _hoops_HCGRS _hoops_PCCP _hoops_ICGRS _hoops_GPRR _hoops_IIGR _hoops_AIIAP
#define	_hoops_CCGRS	(_hoops_GGCAA(HK_SELECTABILITY))
#define _hoops_SCGRS	(_hoops_GGCAA(HK_COLOR) | _hoops_GGCAA(HK_FACE_PATTERN) | \
						 _hoops_GGCAA(HK_WINDOW_PATTERN) | _hoops_GGCAA(HK_WINDOW_FRAME) | \
						 _hoops_CCGRS)

				/* _hoops_RSGA _hoops_PSIAA _hoops_IGGRA _hoops_CRICR _hoops_IS _hoops_SARA _hoops_IH _hoops_CGSI _hoops_PII _hoops_IASC _hoops_HCGC */
			if (_hoops_RCGRS && BIT (_hoops_RCGRS->_hoops_SCIAA & _hoops_RCGRS->_hoops_RSIAA, _hoops_AGICA) &&
					_hoops_RCGRS->_hoops_PGICA != _hoops_GCAAP)
					HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_PSPCR);

			/* _hoops_CCIH _hoops_SGI _hoops_GSSRH _hoops_CGRGS _hoops_CPGGR! */
			if (BIT (_hoops_GHGRS, _hoops_RRAAP) ||
				BIT (_hoops_HPGRS, _hoops_ICRAP))
				HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_ASRRA);

			if (_hoops_RCGRS && BIT (_hoops_RCGRS->_hoops_PSHCA & _hoops_RCGRS->_hoops_RRRAP, _hoops_SARAP) &&
				_hoops_RCGRS->_hoops_SHIH != 0.0f)
				HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_ASPCR);

			if (_hoops_RCGRS && BIT (_hoops_RCGRS->_hoops_PSHCA & _hoops_RCGRS->_hoops_RRRAP, _hoops_HRRAP) &&
				(_hoops_RCGRS->_hoops_HHAAP[0] != 0.0f || _hoops_RCGRS->_hoops_HHAAP[1] != 1.0f))
				HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_ASPCR);

			/* _hoops_RCRP _hoops_ICCGR _hoops_SSH _hoops_SRHR _hoops_IRS _hoops_CGGC _hoops_IS _hoops_CIH _hoops_ACAS */
			if (BIT (_hoops_RHGRS, _hoops_RRAAP))
				_hoops_SRSGS (_hoops_RIGC, _hoops_SRCP, 0);

			if (_hoops_GHGRS != 0 &&
				ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, T_ANY_DRAWABLE_GEOMETRY)) {
				if (ANYBIT (_hoops_GHGRS, _hoops_PRAAP|_hoops_SICI))
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR);
				else if (ANYBIT (_hoops_GHGRS, _hoops_SGAAP|_hoops_RRAAP|_hoops_PRAAP))
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, 0);
				else
					_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, 0);
			}

			if (ANYBIT (_hoops_GHGRS | _hoops_RHGRS, _hoops_PRAAP|_hoops_SICI) &&
				ANYBIT (_hoops_GHGRS | _hoops_RHGRS, ~(_hoops_PRAAP|_hoops_SICI)))
				_hoops_SRSGS (_hoops_RIGC, _hoops_SRCP, _hoops_HISSR);

			if (ANYBIT (_hoops_GPGRS | _hoops_RPGRS, _hoops_CRRAP|_hoops_IPRAP|_hoops_SARAP)) {
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
			}
			else {
				if (_hoops_RCGRS != null && _hoops_GCGRS != null &&
					(BIT (_hoops_RCGRS->_hoops_RRRAP & _hoops_GCGRS->_hoops_RRRAP, _hoops_CRRAP) &&
					 _hoops_RCGRS->_hoops_CHIH != _hoops_GCGRS->_hoops_CHIH ||
					 BIT (_hoops_RCGRS->_hoops_RRRAP & _hoops_GCGRS->_hoops_RRRAP, _hoops_IPRAP) &&
					 _hoops_RCGRS->_hoops_IGAAP != _hoops_GCGRS->_hoops_IGAAP ||
					 BIT (_hoops_RCGRS->_hoops_RRRAP & _hoops_GCGRS->_hoops_RRRAP, _hoops_SARAP) &&
					 _hoops_RCGRS->_hoops_SHIH != _hoops_GCGRS->_hoops_SHIH))
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
			}


			if (ANYBIT (_hoops_GPGRS | _hoops_RPGRS, _hoops_PPRAP)) {
				_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);
			}
			else if (_hoops_RCGRS != null && _hoops_RCGRS->_hoops_HHAIR != null && _hoops_GCGRS != null && _hoops_GCGRS->_hoops_HHAIR != null &&
				(BIT (_hoops_RCGRS->_hoops_RRRAP & _hoops_GCGRS->_hoops_RRRAP, _hoops_PPRAP) &&
					(_hoops_RCGRS->_hoops_HHAIR->_hoops_HRGA.x != _hoops_GCGRS->_hoops_HHAIR->_hoops_HRGA.x ||
					 _hoops_RCGRS->_hoops_HHAIR->_hoops_HRGA.y != _hoops_GCGRS->_hoops_HHAIR->_hoops_HRGA.y ||
					 _hoops_RCGRS->_hoops_HHAIR->_hoops_HRGA.z != _hoops_GCGRS->_hoops_HHAIR->_hoops_HRGA.z)))
					_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);

			if (ANYBIT (_hoops_GPGRS | _hoops_RPGRS, _hoops_CRI))
				_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);

			if (ANYBIT (_hoops_GPGRS | _hoops_RPGRS, _hoops_HRRAP|_hoops_APRAP)) {
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
			}
			else if (_hoops_RCGRS != null && _hoops_GCGRS != null &&
					(BIT (_hoops_RCGRS->_hoops_RRRAP & _hoops_GCGRS->_hoops_RRRAP, _hoops_HRRAP) &&
					 (_hoops_RCGRS->_hoops_HHAAP[0] != _hoops_GCGRS->_hoops_HHAAP[0] ||
					  _hoops_RCGRS->_hoops_HHAAP[1] != _hoops_GCGRS->_hoops_HHAAP[1]) ||
					 BIT (_hoops_RCGRS->_hoops_RRRAP & _hoops_GCGRS->_hoops_RRRAP, _hoops_APRAP) &&
					 (_hoops_RCGRS->_hoops_HCIH.left != _hoops_GCGRS->_hoops_HCIH.left ||
					  _hoops_RCGRS->_hoops_HCIH.right != _hoops_GCGRS->_hoops_HCIH.right ||
					  _hoops_RCGRS->_hoops_HCIH.bottom != _hoops_GCGRS->_hoops_HCIH.bottom ||
					  _hoops_RCGRS->_hoops_HCIH.top != _hoops_GCGRS->_hoops_HCIH.top))) {
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
			}

			if (ANYBIT (_hoops_GPGRS | _hoops_RPGRS, _hoops_GARAP)) {
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
			}
			else if (_hoops_RCGRS != null && _hoops_GCGRS != null &&
					 BIT (_hoops_RCGRS->_hoops_RRRAP & _hoops_GCGRS->_hoops_RRRAP, _hoops_GARAP) &&
					 (_hoops_RCGRS->_hoops_IHAAP[0] != _hoops_GCGRS->_hoops_IHAAP[0] ||
					  _hoops_RCGRS->_hoops_IHAAP[1] != _hoops_GCGRS->_hoops_IHAAP[1])) {
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
			}

			if (ANYBIT (_hoops_GPGRS | _hoops_RPGRS, _hoops_RARAP|_hoops_CPRAP)) {
				_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);
			}
			else if (_hoops_RCGRS != null && _hoops_GCGRS != null &&
					 ANYBIT (_hoops_RCGRS->_hoops_RRRAP & _hoops_GCGRS->_hoops_RRRAP, _hoops_RARAP|_hoops_CPRAP) &&
					 (_hoops_RCGRS->_hoops_CHAAP.red != _hoops_GCGRS->_hoops_CHAAP.red ||
					  _hoops_RCGRS->_hoops_CHAAP.green != _hoops_GCGRS->_hoops_CHAAP.green ||
					  _hoops_RCGRS->_hoops_CHAAP.blue != _hoops_GCGRS->_hoops_CHAAP.blue)) {
					_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);
			}


			if ((_hoops_AIGRS | _hoops_PIGRS) != 0)
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
			else if (_hoops_RCGRS != null && _hoops_RCGRS->_hoops_AIAIR != null && _hoops_GCGRS != null && _hoops_GCGRS->_hoops_AIAIR != null) {
						 
				if (BIT (_hoops_RCGRS->_hoops_AIAIR->value & _hoops_GCGRS->_hoops_AIAIR->value, _hoops_RPCRP) &&
					!_hoops_RAHSR(_hoops_RCGRS->_hoops_AIAIR->_hoops_PIAIR, _hoops_GCGRS->_hoops_AIAIR->_hoops_PIAIR)) {
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
				}
				else if (BIT (_hoops_RCGRS->_hoops_AIAIR->value & _hoops_GCGRS->_hoops_AIAIR->value, _hoops_GHCRP) &&
						 (_hoops_RCGRS->_hoops_AIAIR->weight.value != _hoops_GCGRS->_hoops_AIAIR->weight.value ||
						  _hoops_RCGRS->_hoops_AIAIR->weight._hoops_HHP != _hoops_GCGRS->_hoops_AIAIR->weight._hoops_HHP)) {
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
				}
				else if (BIT (_hoops_RCGRS->_hoops_AIAIR->value & _hoops_GCGRS->_hoops_AIAIR->value, _hoops_SPCRP) &&
						 (_hoops_RCGRS->_hoops_AIAIR->color.red != _hoops_GCGRS->_hoops_AIAIR->color.red ||
						  _hoops_RCGRS->_hoops_AIAIR->color.green != _hoops_GCGRS->_hoops_AIAIR->color.green ||
						  _hoops_RCGRS->_hoops_AIAIR->color.blue != _hoops_GCGRS->_hoops_AIAIR->color.blue)) {
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
				}
				else if (BIT (_hoops_RCGRS->_hoops_AIAIR->value & _hoops_GCGRS->_hoops_AIAIR->value, _hoops_APCRP) &&
						 _hoops_RCGRS->_hoops_AIAIR->_hoops_IHCRP != _hoops_GCGRS->_hoops_AIAIR->_hoops_IHCRP) {
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
				}
			}

			if (ANYBIT (_hoops_AIGRS | _hoops_PIGRS, _hoops_HPCRP))
				_hoops_SRSGS (_hoops_RIGC, _hoops_SRCP, _hoops_HISSR|_hoops_SSCCA);
			else if (ANYBIT (_hoops_AIGRS | _hoops_PIGRS, _hoops_IPCRP))
				_hoops_SRSGS (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);
			else if (_hoops_RCGRS != null && _hoops_RCGRS->_hoops_AIAIR != null && _hoops_GCGRS != null && _hoops_GCGRS->_hoops_AIAIR != null) {

				if (BIT (_hoops_RCGRS->_hoops_AIAIR->value & _hoops_GCGRS->_hoops_AIAIR->value, _hoops_PPCRP) &&
					_hoops_RCGRS->_hoops_AIAIR->_hoops_CHIH != _hoops_GCGRS->_hoops_AIAIR->_hoops_CHIH) {
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
				}
				else if (BIT (_hoops_RCGRS->_hoops_AIAIR->value & _hoops_GCGRS->_hoops_AIAIR->value, _hoops_PHCRP) &&
						 _hoops_RCGRS->_hoops_AIAIR->_hoops_CHCRP != _hoops_GCGRS->_hoops_AIAIR->_hoops_CHCRP) {
						_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
				}
			}

			if (_hoops_RCGRS != null && _hoops_RCGRS->_hoops_AIAIR != null && 
				ANYBIT (_hoops_RCGRS->_hoops_AIAIR->value, _hoops_HPCRP | _hoops_IPCRP | _hoops_RHCRP))
				HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_APHGP);

			if (BIT (_hoops_GPGRS | _hoops_RPGRS, _hoops_HAI))
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);


			if (ANYBIT (_hoops_GIGRS|_hoops_RIGRS, _hoops_HRSI|_hoops_HASRP)) {
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_SCPGP|_hoops_RPSIR|_hoops_SSCCA);
			}
			/* _hoops_CISRP _hoops_HGAS */
			else if (_hoops_RCGRS != null && _hoops_RCGRS->_hoops_PRSI != null && _hoops_GCGRS != null && _hoops_GCGRS->_hoops_PRSI != null) {

				if (BIT (_hoops_RCGRS->_hoops_PRSI->value & _hoops_GCGRS->_hoops_PRSI->value, _hoops_HASRP) &&
					_hoops_RCGRS->_hoops_PRSI->_hoops_IISRP != _hoops_GCGRS->_hoops_PRSI->_hoops_IISRP) {
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_SCPGP|_hoops_RPSIR|_hoops_SSCCA);
				}
				/* _hoops_PISRP _hoops_HGAS  _hoops_PAR  _hoops_AHHSR _hoops_HGAS */
				else if (BIT (_hoops_RCGRS->_hoops_PRSI->value & _hoops_GCGRS->_hoops_PRSI->value, _hoops_IASRP) ||
						 BIT (_hoops_RCGRS->_hoops_PRSI->value & _hoops_GCGRS->_hoops_PRSI->value, _hoops_ISCRP)) {

					/* _hoops_PIP: _hoops_PSP _hoops_CGRPR _hoops_IS _hoops_GCSRP, _hoops_CR _hoops_SGS _hoops_PAHA'_hoops_RA _hoops_GGHC _hoops_IRS _hoops_AIIAP */
					for (int i = 0; i < _hoops_IGAIR; i++) {
						if (_hoops_RCGRS->_hoops_PRSI->_hoops_AISRP[i] != _hoops_GCGRS->_hoops_PRSI->_hoops_AISRP[i] ||
							_hoops_RCGRS->_hoops_PRSI->_hoops_PRPHA[i] != _hoops_GCGRS->_hoops_PRSI->_hoops_PRPHA[i]) {
								_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_SCPGP|_hoops_RPSIR|_hoops_SSCCA);
								break;
						}
					}
				}
			}

			if (_hoops_RCGRS != null && BIT (_hoops_RCGRS->_hoops_SCIAA, _hoops_CSGAP) ||
				_hoops_GCGRS != null && BIT (_hoops_GCGRS->_hoops_SCIAA, _hoops_CSGAP)) {

				//_hoops_IIH _hoops_HRGR _hoops_HHH _hoops_PCHRA _hoops_IIGR _hoops_RCAR _hoops_SIA _hoops_GGR _hoops_ARI _hoops_GSPCA
				if (_hoops_RCGRS == null || _hoops_GCGRS == null || _hoops_RCGRS->_hoops_HHAIR == null || _hoops_GCGRS->_hoops_HHAIR == null) {
					_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_IISSR);
				}
				else if (_hoops_RCGRS->_hoops_HHAIR->_hoops_HRR.mask != _hoops_GCGRS->_hoops_HHAIR->_hoops_HRR.mask ||
						 _hoops_RCGRS->_hoops_HHAIR->_hoops_HRR.value != _hoops_GCGRS->_hoops_HHAIR->_hoops_HRR.value ||
						 _hoops_RCGRS->_hoops_HHAIR->_hoops_HRR._hoops_HAP != _hoops_GCGRS->_hoops_HHAIR->_hoops_HRR._hoops_HAP ||
						 _hoops_RCGRS->_hoops_HHAIR->_hoops_HRR._hoops_CAP != _hoops_GCGRS->_hoops_HHAIR->_hoops_HRR._hoops_CAP)
					_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_IISSR);
			}

			if (_hoops_RCGRS == null && _hoops_GCGRS != null && _hoops_GCGRS->geometry != null && _hoops_GCGRS->geometry->_hoops_APPI.mask ||
				_hoops_GCGRS == null && _hoops_RCGRS != null && _hoops_RCGRS->geometry != null && _hoops_RCGRS->geometry->_hoops_APPI.mask)
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
			else if (_hoops_RCGRS != null && _hoops_RCGRS->geometry != null && _hoops_GCGRS != null && _hoops_GCGRS->geometry != null &&
					(_hoops_RCGRS->geometry->_hoops_APPI.mask != _hoops_GCGRS->geometry->_hoops_APPI.mask ||
					_hoops_RCGRS->geometry->_hoops_APPI.value != _hoops_GCGRS->geometry->_hoops_APPI.value ||
					(BIT (_hoops_RCGRS->geometry->_hoops_APPI.value, _hoops_CHGAP) &&
					_hoops_RCGRS->geometry->_hoops_APPI._hoops_PPPI != _hoops_GCGRS->geometry->_hoops_APPI._hoops_PPPI) ||
					(BIT (_hoops_RCGRS->geometry->_hoops_APPI.value, _hoops_SHGAP) &&
					_hoops_RCGRS->geometry->_hoops_APPI._hoops_HPPI != _hoops_GCGRS->geometry->_hoops_APPI._hoops_HPPI)||
					(BIT (_hoops_RCGRS->geometry->_hoops_APPI.value, _hoops_GIGAP) &&
					_hoops_RCGRS->geometry->_hoops_APPI._hoops_IPPI != _hoops_GCGRS->geometry->_hoops_APPI._hoops_IPPI)||
					(BIT (_hoops_RCGRS->geometry->_hoops_APPI.value, _hoops_RIGAP) &&
					_hoops_RCGRS->geometry->_hoops_APPI._hoops_CPPI != _hoops_GCGRS->geometry->_hoops_APPI._hoops_CPPI)||
					(BIT (_hoops_RCGRS->geometry->_hoops_APPI.value, _hoops_AIGAP) &&
					_hoops_RCGRS->geometry->_hoops_APPI._hoops_SPPI != _hoops_GCGRS->geometry->_hoops_APPI._hoops_SPPI)))
				_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);


			/* _hoops_GSGRS _hoops_HGAS */
			if (_hoops_RCGRS == null && _hoops_GCGRS != null && _hoops_GCGRS->geometry != null && _hoops_GCGRS->geometry->_hoops_GAICA.mask ||
				_hoops_GCGRS == null && _hoops_RCGRS != null && _hoops_RCGRS->geometry != null && _hoops_RCGRS->geometry->_hoops_GAICA.mask)
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
			else if (_hoops_RCGRS != null && _hoops_RCGRS->geometry != null && _hoops_GCGRS != null && _hoops_GCGRS->geometry != null) {

				if (BIT (_hoops_RCGRS->geometry->_hoops_GAICA.mask & _hoops_GCGRS->geometry->_hoops_GAICA.mask, _hoops_ACGAP)) {
					for (int i=0; i<_hoops_IGAIR; ++i) {
						if (_hoops_RCGRS->geometry->_hoops_GAICA.cylinder[i] != _hoops_GCGRS->geometry->_hoops_GAICA.cylinder[i]) {
							_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
							break;
						}
					}
				}
				if (BIT (_hoops_RCGRS->geometry->_hoops_GAICA.mask & _hoops_GCGRS->geometry->_hoops_GAICA.mask, _hoops_PCGAP)) {
					for (int i=0; i<_hoops_IGAIR; ++i) {
						if (_hoops_RCGRS->geometry->_hoops_GAICA.sphere[i] != _hoops_GCGRS->geometry->_hoops_GAICA.sphere[i]) {
							_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
							break;
						}
					}
				}
			}

			if (_hoops_GCGRS == null && _hoops_RCGRS != null && _hoops_RCGRS->geometry != null && BIT (_hoops_RCGRS->geometry->mask, _hoops_RHGAP) ||
				_hoops_RCGRS == null && _hoops_GCGRS != null && _hoops_GCGRS->geometry != null && BIT (_hoops_GCGRS->geometry->mask, _hoops_RHGAP)) {
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_CSCCA|_hoops_RPSIR|_hoops_SSCCA);
			}
			else if (_hoops_GCGRS == null && _hoops_RCGRS != null && _hoops_RCGRS->geometry != null && BIT (_hoops_RCGRS->geometry->mask, _hoops_AHGAP) ||
					 _hoops_RCGRS == null && _hoops_GCGRS != null && _hoops_GCGRS->geometry != null && BIT (_hoops_GCGRS->geometry->mask, _hoops_AHGAP)) {
				_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);
			}

			if (_hoops_RCGRS != null && _hoops_GCGRS != null && (_hoops_RCGRS->_hoops_CSRS != _hoops_GCGRS->_hoops_CSRS))
				_hoops_HIHHC(_hoops_RIGC, _hoops_SRCP, 0);

			if (_hoops_RCGRS != null && _hoops_RCGRS->_hoops_HHAIR != null && _hoops_RCGRS->_hoops_HHAIR->_hoops_PRIGA.mask ||
				_hoops_RCGRS == null && _hoops_GCGRS != null && _hoops_GCGRS->_hoops_HHAIR != null && _hoops_GCGRS->_hoops_HHAIR->_hoops_PRIGA.mask) {
				/* _hoops_PSP _hoops_RSGRS, _hoops_SAHR _hoops_RGRIR _hoops_CPS _hoops_IH _hoops_HA*/
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_HCPGP|_hoops_RPSIR|_hoops_SSCCA);
			}

			if (_hoops_RCGRS != null && _hoops_RCGRS->_hoops_HHAIR != null && _hoops_RCGRS->_hoops_HHAIR->_hoops_IHAIR.mask ||
				_hoops_RCGRS == null && _hoops_GCGRS != null && _hoops_GCGRS->_hoops_HHAIR != null && _hoops_GCGRS->_hoops_HHAIR->_hoops_IHAIR.mask) {
				/* _hoops_PSP _hoops_RSGRS, _hoops_SAHR _hoops_RGRIR _hoops_CPS _hoops_IH _hoops_HA*/
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);
			}

			if (_hoops_RCGRS != null && _hoops_RCGRS->_hoops_SSHCA.mask ||
				_hoops_RCGRS == null && _hoops_GCGRS != null && _hoops_GCGRS->_hoops_SSHCA.mask) {
				/* _hoops_PSP _hoops_RSGRS, _hoops_SAHR _hoops_RGRIR _hoops_CPS _hoops_IH _hoops_HA*/
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);
			}

			{
				bool		_hoops_ASGRS, _hoops_PSGRS;

				_hoops_ASGRS = BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PACAA);
				if (_hoops_GCGRS != null && _hoops_GCGRS->_hoops_HHAIR != null &&
					BIT (_hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_PGGAP)) {
					if (BIT (_hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.value, _hoops_PGGAP) &&
						_hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS._hoops_RGP != _hoops_CRGAP)
						HI_Less_Shadows (_hoops_RIGC, _hoops_SRCP, 1);
					_hoops_SRCP->_hoops_PHSI &= ~_hoops_PACAA;
				}
				if (_hoops_RCGRS != null && _hoops_RCGRS->_hoops_HHAIR != null &&
					BIT (_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_PGGAP)) {
					if (BIT (_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.value, _hoops_PGGAP) &&
						_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS._hoops_RGP != _hoops_CRGAP)
						HI_More_Shadows (_hoops_RIGC, _hoops_SRCP, 1);
					_hoops_SRCP->_hoops_PHSI |= _hoops_PACAA;
				}
				_hoops_PSGRS = BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PACAA);

				if (_hoops_ASGRS != _hoops_PSGRS && !BIT(_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR)) {
					/* _hoops_RCAR _hoops_PPSR _hoops_AGRP _hoops_IRHS _hoops_IS _hoops_PRSCA _hoops_IS _hoops_RRRPR/_hoops_HCSHC */
					_hoops_SRCP->_hoops_PHSI &= ~_hoops_PACAA;
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_GSPGP);
					if (_hoops_PSGRS)
						_hoops_SRCP->_hoops_PHSI |= _hoops_PACAA;
				}
			}

			if (_hoops_HIGRS || _hoops_IIGRS || _hoops_CIGRS || _hoops_SIGRS) {
				/* _hoops_AIIAP */
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);
				/* _hoops_HIH _hoops_RGAR _hoops_IPGGR _hoops_GPP _hoops_HHH _hoops_SHPH */
				if (ANYBIT (_hoops_HIGRS|_hoops_IIGRS, ~(_hoops_PGGAP|_hoops_SGGAP)))
					_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_AICSA|_hoops_SSCCA);
			}
			else if (_hoops_GCGRS != null && _hoops_GCGRS->_hoops_HHAIR != null && _hoops_RCGRS != null && _hoops_RCGRS->_hoops_HHAIR != null) {
				/* _hoops_ISPR _hoops_IH _hoops_IGGA _hoops_SHPH */
				if (BIT (_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.value, _hoops_RRGAP) &&
					_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS._hoops_HAP != _hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS._hoops_HAP ||
					BIT (_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.value, _hoops_ARGAP) &&
					_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS._hoops_IGGGR != _hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS._hoops_IGGGR ||
					BIT (_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.value, _hoops_CGGAP) &&
					(_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.light.x != _hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.light.x ||
					_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.light.y != _hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.light.y ||
					_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.light.z != _hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.light.z) ||
					BIT (_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.value, _hoops_IGGAP) &&
					(_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.plane.a != _hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.plane.a ||
					_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.plane.b != _hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.plane.b ||
					_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.plane.c != _hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.plane.c)) {
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_HISSR|_hoops_SSCCA);
				}
				else if (BIT (_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.value, _hoops_IGGAP) &&
						 _hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.plane.d != _hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.plane.d) {
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_PSCCA|_hoops_SSCCA);
				}
				else if (BIT (_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.value, _hoops_SGGAP) &&
					(_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.color.rgb.red != _hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.color.rgb.red ||
					 _hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.color.rgb.green != _hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.color.rgb.green ||
					 _hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.color.rgb.blue != _hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS.color.rgb.blue)) {
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);
				}
				else if (BIT (_hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS.value, _hoops_GRGAP) &&
						 _hoops_RCGRS->_hoops_HHAIR->_hoops_GHSS._hoops_IRIR != _hoops_GCGRS->_hoops_HHAIR->_hoops_GHSS._hoops_IRIR) {
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);
				}
				else if (BIT (_hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR.value, _hoops_IGGAP) &&
						 (_hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR.plane.a != _hoops_GCGRS->_hoops_HHAIR->_hoops_RHGGR.plane.a ||
						  _hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR.plane.b != _hoops_GCGRS->_hoops_HHAIR->_hoops_RHGGR.plane.b ||
						  _hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR.plane.c != _hoops_GCGRS->_hoops_HHAIR->_hoops_RHGGR.plane.c ||
						  _hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR.plane.d != _hoops_GCGRS->_hoops_HHAIR->_hoops_RHGGR.plane.d)) {
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);
				}
				else if (BIT (_hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR.value, _hoops_RPGAP) &&
						_hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR._hoops_IRIR != _hoops_GCGRS->_hoops_HHAIR->_hoops_RHGGR._hoops_IRIR) {
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP,_hoops_SSCCA);
				}
				else if (BIT (_hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR.value, _hoops_HPGAP) &&
						 _hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR._hoops_IGGGR != _hoops_GCGRS->_hoops_HHAIR->_hoops_RHGGR._hoops_IGGGR) {
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);
				}
				else if (BIT (_hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR.value, _hoops_PPGAP) &&
						(_hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR.hither != _hoops_GCGRS->_hoops_HHAIR->_hoops_RHGGR.hither ||
						  _hoops_RCGRS->_hoops_HHAIR->_hoops_RHGGR.yon != _hoops_GCGRS->_hoops_HHAIR->_hoops_RHGGR.yon)
						) {
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);
				}
			}

			if (ANYBIT (_hoops_GPGRS | _hoops_RPGRS, _hoops_HPH)) {
				if (BIT (_hoops_GPGRS, _hoops_HPH))
					HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_ASRRA);
				_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);
			}
			else if (_hoops_RCGRS != null && _hoops_RCGRS->_hoops_HHAIR != null && _hoops_GCGRS != null && _hoops_GCGRS->_hoops_HHAIR != null &&
					 BIT (_hoops_RCGRS->_hoops_RRRAP & _hoops_GCGRS->_hoops_RRRAP, _hoops_HPH) &&
					 (_hoops_RCGRS->_hoops_HHAIR->_hoops_CRIR.hither != _hoops_GCGRS->_hoops_HHAIR->_hoops_CRIR.hither ||
					  _hoops_RCGRS->_hoops_HHAIR->_hoops_CRIR.yon != _hoops_GCGRS->_hoops_HHAIR->_hoops_CRIR.yon)) {
				_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);
			}

			if (BIT (_hoops_CAGRS | _hoops_SAGRS, _hoops_GSIAA)) {

				HI_Propagate_Maybes_Across_Styles (_hoops_SRCP, _hoops_RHHGP);

				if (ANYBIT (_hoops_AHGRS | _hoops_PHGRS, ~_hoops_SCGRS)) {
					_hoops_PASGS (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR);
					break;				/* _hoops_PAH'_hoops_RA _hoops_AA _hoops_GII _hoops_RRI _hoops_HSAR _hoops_RGR! */
				}
				else if (ANYBIT (_hoops_AHGRS | _hoops_PHGRS, ~_hoops_CCGRS)) {
					if (ANYBIT (_hoops_SRCP->_hoops_RCGC, T_FACES))
						_hoops_HASGS (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR);
					else if (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, T_ANY_DRAWABLE_GEOMETRY))
						_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR);
					else
						_hoops_SRSGS (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);
				}
			}

			if (ANYBIT (_hoops_APGRS | _hoops_PPGRS,
						_hoops_CIRAP |
						  _hoops_AHRAP |
						  _hoops_HHRAP |
						  _hoops_SHRAP |
						  _hoops_IHRAP)) {
				/* _hoops_PAGA: _hoops_SR'_hoops_GHGP _hoops_PII _hoops_IS _hoops_SAHR _hoops_AIIAP, _hoops_HIH _hoops_RH _hoops_SSRR _hoops_SHPH
				 * _hoops_GGR _hoops_HSP-_hoops_HCAS _hoops_IH _hoops_HAIR _hoops_HSGRS _hoops_GH _hoops_AHCR-_hoops_SRHR _hoops_IACAR, _hoops_PPR
				 * _hoops_RH _hoops_SSRR _hoops_CICA _hoops_GGR _hoops_PPR _hoops_GGSR _hoops_IIGR _hoops_HSIAR-_hoops_RCA _hoops_CRHPR
				 * _hoops_RH _hoops_RSRA-_hoops_ASPA _hoops_ISGRS. _hoops_PHGP _hoops_HCR _hoops_IPIH-_hoops_HSSPR
				 * _hoops_GGAR _hoops_PSSGR _hoops_HGAP _hoops_PCCP _hoops_AHPIP. _hoops_RAPHR.
				 */
				_hoops_PASGS (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
				break;					/* _hoops_PAH'_hoops_RA _hoops_AA _hoops_GII _hoops_RRI _hoops_HSAR _hoops_RGR! */
			}

			if (_hoops_CHGRS != false || _hoops_SHGRS != false) {
				if (ANYBIT (_hoops_SRCP->_hoops_RCGC, T_FACES)) {
					_hoops_PASGS (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
					break;						/* _hoops_PAH'_hoops_RA _hoops_AA _hoops_GII _hoops_RRI _hoops_HSAR _hoops_RGR! */
				}
				else if (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, T_ANY_DRAWABLE_GEOMETRY))
					_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
				else
					_hoops_SRSGS (_hoops_RIGC, _hoops_SRCP, 0);
			}

			if (_hoops_HHGRS != false || _hoops_IHGRS != false) {
				if (ANYBIT (_hoops_SRCP->_hoops_RCGC, T_FACES))
					_hoops_HASGS (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
				else if (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, T_ANY_DRAWABLE_GEOMETRY))
					_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
				else
					_hoops_SRSGS (_hoops_RIGC, _hoops_SRCP, 0);
			}

			if (BIT (_hoops_GPGRS | _hoops_RPGRS, _hoops_PARAP))
				_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, 0);

			if (BIT (_hoops_CPGRS | _hoops_SPGRS, _hoops_CPAAP)) {
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, 0);
			}

			if (ANYBIT (_hoops_GPGRS | _hoops_RPGRS, _hoops_HARAP | _hoops_IARAP)) {
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, 0);
			}
			else if (_hoops_RCGRS != null && _hoops_RCGRS->_hoops_HHAIR != null && _hoops_GCGRS != null && _hoops_GCGRS->_hoops_HHAIR != null &&
					 BIT (_hoops_RCGRS->_hoops_RRRAP & _hoops_GCGRS->_hoops_RRRAP, _hoops_IARAP) &&
					 _hoops_RCGRS->_hoops_HHAIR->_hoops_ACSRP != _hoops_GCGRS->_hoops_HHAIR->_hoops_ACSRP) {
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, 0);
			}

			if (BIT (_hoops_CAGRS | _hoops_SAGRS, _hoops_ISGAP) ||
				_hoops_GCGRS != null && _hoops_RCGRS != null && BIT (_hoops_GCGRS->_hoops_RSIAA, _hoops_ISGAP) &&
				_hoops_GCGRS->_hoops_CHP.value != _hoops_RCGRS->_hoops_CHP.value) {
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, 0);
			}

			if (ANYBIT (_hoops_CAGRS | _hoops_SAGRS, _hoops_AGRAP | _hoops_PRICA))
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, 0);
			else if (_hoops_GCGRS != null && _hoops_RCGRS != null) {
				if (BIT (_hoops_GCGRS->_hoops_RSIAA, _hoops_AGRAP)) {
					if (BIT (_hoops_GCGRS->_hoops_IIAIR->value, _hoops_AICRP) &&
						(_hoops_RCGRS->_hoops_IIAIR->_hoops_CCCRP != _hoops_GCGRS->_hoops_IIAIR->_hoops_CCCRP ||
						 _hoops_RCGRS->_hoops_IIAIR->scale != _hoops_GCGRS->_hoops_IIAIR->scale ||
						 _hoops_RCGRS->_hoops_IIAIR->translate != _hoops_GCGRS->_hoops_IIAIR->translate))
						_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_PIPGP);
					else
						_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, 0);
				}
				if (BIT (_hoops_GCGRS->_hoops_RSIAA, _hoops_PRICA)) {
					if (BIT (_hoops_GCGRS->_hoops_IIAIR->value, _hoops_IICRP) &&
						(_hoops_RCGRS->_hoops_IIAIR->_hoops_RSCRP != _hoops_GCGRS->_hoops_IIAIR->_hoops_RSCRP ||
						 _hoops_RCGRS->_hoops_IIAIR->_hoops_CIAIR != _hoops_GCGRS->_hoops_IIAIR->_hoops_CIAIR ||
						 !EQUAL_MEMORY (_hoops_RCGRS->_hoops_IIAIR->_hoops_SIAIR,
										_hoops_RCGRS->_hoops_IIAIR->_hoops_CIAIR * sizeof (float),
									    _hoops_GCGRS->_hoops_IIAIR->_hoops_SIAIR)))
						_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_PIPGP);
					else
						_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, 0);
				}
			}

			/* _hoops_CSGRS _hoops_GPP/_hoops_PSAP _hoops_PAR _hoops_PIRA _hoops_SHPH */
			if (_hoops_HPGRS != 0) {
				if (ANYBIT (_hoops_HPGRS, _hoops_PCRAP|_hoops_HCRAP)	 &&
					(_hoops_GCGRS == null ||
					 !ANYBIT (_hoops_GCGRS->_hoops_RCRAP, _hoops_PCRAP|_hoops_HCRAP)))
					_hoops_HASGS (_hoops_RIGC, _hoops_SRCP, 0);
				else
					_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, 0);
			}
			if (_hoops_IPGRS != 0) {
				_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, 0);
			}

		}	break;

		case HK_DRIVER: {
			int			_hoops_CGR,
						_hoops_RPGGA,
						_hoops_SHSGS,
						_hoops_GISGS;

			_hoops_SHSGS = _hoops_SRCP->_hoops_IGCCA;
			_hoops_CGR = _hoops_SRCP->_hoops_AAGSA();
			_hoops_RPGGA = _hoops_SRCP->_hoops_PAGSA();
			_hoops_GISGS = _hoops_SRCP->_hoops_SHGSA();

			if (_hoops_SISCA == null) {
				if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GISIR)) {/* _hoops_HGGCI _hoops_IRS _hoops_RHPP */
					/* _hoops_IRHP "_hoops_SSGRS" _hoops_IAII _hoops_SR _hoops_PAH'_hoops_RA _hoops_SSS _hoops_IRS _hoops_GGRRS _hoops_RPPS _hoops_CGPR _hoops_SR _hoops_HPPR _hoops_IS _hoops_HASIR _hoops_SS, _hoops_AHI */
					_hoops_PISCA->_hoops_RRHH &= ~_hoops_HGAGR;

					if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) {
						if (_hoops_CGR > 0)
							HI_Less_Light (_hoops_RIGC, _hoops_SRCP, _hoops_CGR);
						if (_hoops_RPGGA > 0)
							HI_Less_Cutting_Planes (_hoops_RIGC, _hoops_SRCP, _hoops_RPGGA);
						if (_hoops_GISGS > 0)
							HI_Less_Shadows (_hoops_RIGC, _hoops_SRCP, _hoops_GISGS);
						if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA|_hoops_RIGSA))
							if (_hoops_SHSGS > 0)
								HI_Less_Transparencies (_hoops_RIGC, _hoops_SRCP, _hoops_SHSGS);
					}

					_hoops_PISCA->_hoops_RRHH |= _hoops_HGAGR;

					_hoops_ICIIR(_hoops_RIGC);
					//_hoops_HPPSA (_hoops_IPPSA->_hoops_HHSIR);			// _hoops_SHR _hoops_GIAA _hoops_IRS _hoops_IHSIR?
					bool		_hoops_RISGS = (_hoops_SRCP != HOOPS_WORLD->root) && HI_Fast_Lookup_Available (_hoops_SRCP->owner, true);

					if (_hoops_RISGS)
						HI_Remove_Fast_Lookup_Item (_hoops_SRCP->owner, true, (Subsegment alter *)_hoops_SRCP);

					_hoops_SRCP->_hoops_PHSI &= ~_hoops_GISIR;

					if (_hoops_RISGS)
						HI_Add_Fast_Lookup_Item (_hoops_SRCP->owner, true, (Subsegment alter *)_hoops_SRCP);
					//_hoops_SPPSA (_hoops_IPPSA->_hoops_HHSIR);

					if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) {
						if (_hoops_CGR > 0)
							HI_More_Light (_hoops_RIGC, _hoops_SRCP, _hoops_CGR);
						if (_hoops_RPGGA > 0)
							HI_More_Cutting_Planes (_hoops_RIGC, _hoops_SRCP, _hoops_RPGGA);
						if (_hoops_GISGS > 0)
							HI_More_Shadows (_hoops_RIGC, _hoops_SRCP, _hoops_GISGS);
						if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA|_hoops_RIGSA))
							if (_hoops_SHSGS > 0)
								HI_More_Transparencies (_hoops_RIGC, _hoops_SRCP, _hoops_SHSGS);
					}
				}
			}
			else {
				if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GISIR)) {/* _hoops_RGSR _hoops_IRS _hoops_CCAH _hoops_RHPP */
					if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) {
						if (_hoops_CGR > 0)
							HI_Less_Light (_hoops_RIGC, _hoops_SRCP, _hoops_CGR);
						if (_hoops_RPGGA > 0)
							HI_Less_Cutting_Planes (_hoops_RIGC, _hoops_SRCP, _hoops_RPGGA);
						if (_hoops_GISGS > 0)
							HI_Less_Shadows (_hoops_RIGC, _hoops_SRCP, _hoops_GISGS);
						if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA|_hoops_RIGSA))
							if (_hoops_SHSGS > 0)
								HI_Less_Transparencies (_hoops_RIGC, _hoops_SRCP, _hoops_SHSGS);
					}

					_hoops_ICIIR(_hoops_RIGC);
					//_hoops_HPPSA (_hoops_IPPSA->_hoops_HHSIR);			// _hoops_SHR _hoops_GIAA _hoops_IRS _hoops_IHSIR?
					bool		_hoops_RISGS = (_hoops_SRCP != HOOPS_WORLD->root) && HI_Fast_Lookup_Available (_hoops_SRCP->owner, true);

					if (_hoops_RISGS)
						HI_Remove_Fast_Lookup_Item (_hoops_SRCP->owner, true, (Subsegment alter *)_hoops_SRCP);

					_hoops_SRCP->_hoops_PHSI |= _hoops_GISIR;

					if (_hoops_RISGS)
						HI_Add_Fast_Lookup_Item (_hoops_SRCP->owner, true, (Subsegment alter *)_hoops_SRCP);
					//_hoops_SPPSA (_hoops_IPPSA->_hoops_HHSIR);

					if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) {
						if (_hoops_CGR > 0)
							HI_More_Light (_hoops_RIGC, _hoops_SRCP, _hoops_CGR);
						if (_hoops_RPGGA > 0)
							HI_More_Cutting_Planes (_hoops_RIGC, _hoops_SRCP, _hoops_RPGGA);
						if (_hoops_GISGS > 0)
							HI_More_Shadows (_hoops_RIGC, _hoops_SRCP, _hoops_GISGS);
						if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA|_hoops_RIGSA))
							if (_hoops_SHSGS > 0)
								HI_More_Transparencies (_hoops_RIGC, _hoops_SRCP, _hoops_SHSGS);
					}

					if (ALLBITS (((_hoops_GGAGR *)_hoops_SISCA)->_hoops_CGPIR, _hoops_RCSHA|_hoops_GCSHA))
						_hoops_SRCP->_hoops_PHSI |= _hoops_HIHGP;
					_hoops_RASGS (_hoops_RIGC, _hoops_SRCP, 0);
				}
			}
		}	break;

		case HK_FACE_PATTERN: {
			if (BIT (_hoops_SRCP->_hoops_RCGC, T_FACES))
				_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA); /* _hoops_RCPGP? */
		}	break;

		case HK_CAMERA: {
			if (_hoops_SISCA != null) {
				_hoops_SRCP->_hoops_PHSI |= _hoops_HCHGP;
				if (_hoops_PISCA == null)
					HI_Antiquate_Bounding (_hoops_SRCP, false);
			}
			else {
				_hoops_SRCP->_hoops_PHSI &= ~_hoops_HCHGP;
				HI_Propagate_Bounding (_hoops_RIGC, _hoops_SRCP, _hoops_SRCP->bounding, null);
			}
			if (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, _hoops_AAHGP))
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
			else /* _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_SAGGR _hoops_RGRRS _hoops_IH _hoops_PPCIA */
				_hoops_SRSGS (_hoops_RIGC, _hoops_SRCP, 0);

			_hoops_PCGPR = _hoops_ISPGP;	//
		}	break;

		case HK_CLIP_REGION: {
			if (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, _hoops_AAHGP))
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_SSCCA);
			else /* _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_SAGGR _hoops_RGRRS _hoops_IH _hoops_PPCIA */
				_hoops_SRSGS (_hoops_RIGC, _hoops_SRCP, 0);
		}	break;

		case HK_HANDEDNESS: {
			if (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, _hoops_AAHGP))
				_hoops_HIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR|_hoops_CSCCA|_hoops_SSCCA);
			else /* _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_SAGGR _hoops_RGRRS _hoops_IH _hoops_PPCIA */
				_hoops_SRSGS (_hoops_RIGC, _hoops_SRCP, 0);
		}	break;

		case HK_EDGE_PATTERN: {
			if (!ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, T_ANY_EDGE)) {}
			else if (_hoops_PISCA == null || _hoops_SISCA == null)
				_hoops_CRSGS (_hoops_RIGC, _hoops_SRCP, _hoops_GHSGS|_hoops_RPSIR|_hoops_SSCCA);
			else
				_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR);
		}	break;

		case _hoops_RPAIR: {
			if (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, T_ANY_EDGE|T_LINES))
				_hoops_CRSGS (_hoops_RIGC, _hoops_SRCP, _hoops_GHSGS|_hoops_RPSIR|_hoops_SSCCA);
		}	break;

		case _hoops_RAAIR: {
			if (BIT (_hoops_SRCP->_hoops_RCGC, T_MARKERS|T_VERTICES))
				_hoops_CRSGS (_hoops_RIGC, _hoops_SRCP, _hoops_GHSGS|_hoops_RPSIR|_hoops_SSCCA);

			if (_hoops_SISCA) {
				_hoops_AAAIR alter *_hoops_SAHCA = (_hoops_AAAIR alter *)_hoops_SISCA;
				int flags = 0;
				int i;

				for (i=0; i<_hoops_SAHCA->count; i++)
					flags |= _hoops_SAHCA->glyphs[i]->flags;

				if (BIT(flags, _hoops_HAGS)) {
					HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_ASRRA);
				}
			}
		}	break;

		case HK_LINE_PATTERN: {
			if (!BIT (_hoops_SRCP->_hoops_RCGC, T_LINES)) {}
			else if (_hoops_PISCA == null || _hoops_SISCA == null)
				_hoops_CRSGS (_hoops_RIGC, _hoops_SRCP, _hoops_GHSGS|_hoops_RPSIR|_hoops_SSCCA);
			else
				_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, _hoops_RPSIR);
		}	break;

		case HK_EDGE_WEIGHT: {
			if (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, T_ANY_EDGE))
				_hoops_CRSGS (_hoops_RIGC, _hoops_SRCP, _hoops_GHSGS|_hoops_RPSIR|_hoops_SSCCA);

			_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_IPPGP);
		}	break;

		case HK_CALLBACK: {
#ifndef DISABLE_CALLBACKS
			_hoops_IHACR const	*_hoops_RCHIR;
			Attribute const		*_hoops_HPHCR;
			Attribute const		*other = _hoops_SISCA;

			/* _hoops_CCGR _hoops_SR _hoops_CACH _hoops_SGS _hoops_SR _hoops_HS _hoops_SPR _hoops_GGR _hoops_RH _hoops_CCAH _hoops_HIGR */
			_hoops_SRCP->_hoops_PHSI &= ~_hoops_ICHGP;

			for (_hoops_HPHCR = _hoops_PISCA;; _hoops_HPHCR = _hoops_SISCA) {
				if (_hoops_HPHCR != null &&
					(_hoops_RCHIR = ((_hoops_GCHIR *)_hoops_HPHCR)->_hoops_ACHIR) != null) do {
					bool		process = true;

					if (!_hoops_RCHIR->_hoops_PIACR) {
						if (other != null) {
							_hoops_IHACR const *	_hoops_AGRRS = ((_hoops_GCHIR *)other)->_hoops_ACHIR;

							if (_hoops_AGRRS != null) do {
								if (_hoops_AGRRS->type == _hoops_RCHIR->type) {
									if (_hoops_AGRRS->_hoops_PIACR == _hoops_RCHIR->_hoops_PIACR &&
										_hoops_RAHSR (_hoops_AGRRS->name->name, _hoops_RCHIR->name->name))
										process = false;
									break;
								}
							} while ((_hoops_AGRRS = _hoops_AGRRS->next) != null);
						}
					}
					else
						process = false;

					if (process) switch (_hoops_RCHIR->type) {
						case _hoops_APACR:
						case _hoops_PPACR:
						case _hoops_CSRCR:
						case _hoops_SSRCR:
						case _hoops_SGACR: 
						case _hoops_HPACR:	{
							/*
							 * _hoops_IRHH _hoops_HHIS _hoops_SPIC _hoops_APRGH _hoops_RHPA _hoops_SGHC _hoops_SGS _hoops_CHH
							 * _hoops_IAII _hoops_SHH _hoops_HPSH.
							 */
							HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_APHGP);
							_hoops_CRSGS (_hoops_RIGC, _hoops_SRCP, _hoops_GHSGS|_hoops_RPSIR|_hoops_SSCCA);
							_hoops_IIHHC (_hoops_RIGC, _hoops_SRCP, 0);
						}	break;

						case _hoops_PAACR:
						case _hoops_GPACR:
						case _hoops_HAACR:
						case _hoops_IAACR:
						case _hoops_CAACR:
						case _hoops_SAACR:
							break;

						default: {
							/* _hoops_IGIPR _hoops_SGS _hoops_IASI-_hoops_AHPIP _hoops_PAH _hoops_SHH _hoops_IIAC _hoops_IS _hoops_IPHR _hoops_GPP _hoops_CAPGR _hoops_ASCA. */
							_hoops_CRSGS (_hoops_RIGC, _hoops_SRCP, _hoops_GHSGS|_hoops_RPSIR);
						} break;
					}

					if (_hoops_HPHCR == _hoops_SISCA) {		// _hoops_RGAR _hoops_CGPR _hoops_CPRAA
						switch (_hoops_RCHIR->type) {

							case _hoops_GPACR: {
								if (_hoops_RCHIR->name->address != nullroutine)
									_hoops_SRCP->_hoops_PHSI |= _hoops_ICHGP;
								else
									_hoops_SRCP->_hoops_PHSI &= ~_hoops_ICHGP;
							}	break;

							//_hoops_AGIR _hoops_PGRRS:
							case _hoops_RRACR:
							case _hoops_ARACR:
							case _hoops_PAACR:
							case _hoops_HAACR:
							case _hoops_IAACR:
							case _hoops_CAACR:
							case _hoops_SAACR: {
								// _hoops_AGCR _hoops_AA _hoops_HAR _hoops_SSPP _hoops_HAHA _hoops_CPAP, _hoops_HIS _hoops_GA'_hoops_RA _hoops_RRP _hoops_RH _hoops_GAAP
							}	break;

							// _hoops_RGR _hoops_PAH _hoops_SGH _hoops_PSPI
							case _hoops_APACR: {
								if (_hoops_RCHIR->name->address != nullroutine)
									_hoops_SRCP->_hoops_PHSI |= _hoops_GIPSA;
								else
									_hoops_SRCP->_hoops_PHSI &= ~_hoops_GIPSA;
							}	_hoops_HHHI;

							default: {
								if (_hoops_RCHIR->name->address != null)
									HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_AHHGP);
							}	break;
						}
					}
				} while ((_hoops_RCHIR = _hoops_RCHIR->next) != null);

				if (_hoops_HPHCR == _hoops_SISCA)
					break;
				other = _hoops_PISCA;
			}
#endif
		}	break;

		case HK_LINE_WEIGHT: {
			if (BIT (_hoops_SRCP->_hoops_RCGC, T_LINES))
				_hoops_CRSGS (_hoops_RIGC, _hoops_SRCP, _hoops_GHSGS|_hoops_RPSIR|_hoops_SSCCA);

			_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_IPPGP);
		}	break;

		case HK_MARKER_SYMBOL: {
			if (BIT (_hoops_SRCP->_hoops_RCGC, T_MARKERS|T_VERTICES))
				_hoops_CRSGS (_hoops_RIGC, _hoops_SRCP, _hoops_GHSGS|_hoops_RPSIR|_hoops_SSCCA);
		}	break;

		case HK_MARKER_SIZE: {
			if (BIT (_hoops_SRCP->_hoops_RCGC, T_MARKERS|T_VERTICES))
				_hoops_CRSGS (_hoops_RIGC, _hoops_SRCP, _hoops_GHSGS|_hoops_RPSIR|_hoops_SSCCA);

			if (_hoops_SISCA != null) {
				_hoops_AHPIR * _hoops_HGRRS = (_hoops_AHPIR *)_hoops_SISCA;

				if (_hoops_HGRRS->data._hoops_HHP == _hoops_SHGRP && _hoops_HGRRS->data.value != 0 ||
					_hoops_HGRRS->data._hoops_HHP == GSU_PIXELS && _hoops_HGRRS->data.value > 1) {

					if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_SAHGP))
						HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_SAHGP);
				}
			}
		}	break;

		case HK_MODELLING_MATRIX: {
			_hoops_ISGI *		_hoops_IGRRS = (_hoops_ISGI *)_hoops_PISCA;
			_hoops_ISGI *		_hoops_AISHC = (_hoops_ISGI *)_hoops_SISCA;
			Activity				_hoops_ACSAP = 0;
			Matrix_Contents			_hoops_CGRRS,	_hoops_SGRRS;

			if (_hoops_SRCP->_hoops_PAGSA() > 0)
				_hoops_ACSAP |= _hoops_HISSR;
			else if (_hoops_PISCA == null) {
				_hoops_SGRRS = _hoops_AISHC->matrix._hoops_RAGR & ~_hoops_RRICR;

				if (_hoops_SGRRS == _hoops_PRICR)
					_hoops_ACSAP |= _hoops_PSCCA;
				else if (_hoops_SGRRS != 0)
					_hoops_ACSAP |= _hoops_HISSR;
			}
			else if (_hoops_SISCA == null) {
				_hoops_CGRRS = _hoops_IGRRS->matrix._hoops_RAGR & ~_hoops_RRICR;

				if (_hoops_CGRRS == _hoops_PRICR)
					_hoops_ACSAP |= _hoops_PSCCA;
				else if (_hoops_CGRRS != 0)
					_hoops_ACSAP |= _hoops_HISSR;
			}
			else {
				_hoops_CGRRS = _hoops_IGRRS->matrix._hoops_RAGR & ~_hoops_RRICR;
				_hoops_SGRRS = _hoops_AISHC->matrix._hoops_RAGR & ~_hoops_RRICR;

				if ((_hoops_CGRRS == _hoops_PRICR || _hoops_CGRRS == 0) &&
					(_hoops_SGRRS == _hoops_PRICR || _hoops_SGRRS == 0))
					_hoops_ACSAP |= _hoops_PSCCA;
				else {
					_hoops_RPRA const *	_hoops_AASPA = (_hoops_RPRA const *)&_hoops_IGRRS->matrix.elements[0];
					_hoops_RPRA const *	_hoops_GASPA = (_hoops_RPRA const *)&_hoops_AISHC->matrix.elements[0];

					if (_hoops_AASPA[0][0] == _hoops_GASPA[0][0] && _hoops_AASPA[0][1] == _hoops_GASPA[0][1] && _hoops_AASPA[0][2] == _hoops_GASPA[0][2] &&
						_hoops_AASPA[1][0] == _hoops_GASPA[1][0] && _hoops_AASPA[1][1] == _hoops_GASPA[1][1] && _hoops_AASPA[1][2] == _hoops_GASPA[1][2] &&
						_hoops_AASPA[2][0] == _hoops_GASPA[2][0] && _hoops_AASPA[2][1] == _hoops_GASPA[2][1] && _hoops_AASPA[2][2] == _hoops_GASPA[2][2])
						_hoops_ACSAP |= _hoops_PSCCA;
					else
						_hoops_ACSAP |= _hoops_HISSR;
				}
			}

			if (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, _hoops_AAHGP))
				_hoops_SASGS (_hoops_RIGC, _hoops_SRCP, _hoops_GHSGS |
									 _hoops_HCPGP |
									 _hoops_ICPGP |
									 _hoops_RPSIR |
									 _hoops_SSCCA |
									 _hoops_IISSR |
									 _hoops_ACSAP);
			if (_hoops_SRCP->bounding != null) {
				HI_Propagate_Bounding (_hoops_RIGC, _hoops_SRCP, _hoops_SRCP->bounding, null);
				HI_Antiquate_Bounding (_hoops_SRCP, false);
			}
			else {
				Bounding	bounding;
				Bounding	_hoops_HSRIR;

				HI_Figure_Segment_Bounding (_hoops_SRCP, bounding, _hoops_HSRIR);
				if (!bounding._hoops_HICAR())
					HI_Propagate_Bounding (_hoops_RIGC, _hoops_SRCP, bounding, null);
			}
		}	break;

		case _hoops_HAAIR: {

			/* _hoops_RGR _hoops_PAH _hoops_HAHA _hoops_PA */
			_hoops_HRSGS (_hoops_RIGC, _hoops_SRCP, _hoops_SCPGP|
				_hoops_ICPGP|
				_hoops_RPSIR|
				_hoops_SSCCA);

		}	break;

		case _hoops_CPPIR: {
			
			if (_hoops_SISCA != null) {
				_hoops_SPPIR const *	_hoops_RCACA = (_hoops_SPPIR const *)_hoops_SISCA;
				//_hoops_CHASI _hoops_RCIC *	_hoops_GRRRS = (_hoops_CHASI _hoops_RCIC *)_hoops_AHSGS;

				if (_hoops_RCACA->_hoops_ACPGR != null)
					HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_CPHGP);
			}

			/* _hoops_RGR _hoops_PAH _hoops_HAHA _hoops_PA */
			_hoops_HRSGS (_hoops_RIGC, _hoops_SRCP, _hoops_SCPGP|
							_hoops_ICPGP|
							_hoops_RPSIR|
							_hoops_SSCCA);
		}	break;

		case _hoops_IPAIR:
		case HK_TEXTURE_MATRIX: {
#ifndef DISABLE_TEXTURING
			if (ANYBIT (_hoops_SRCP->_hoops_RCGC & _hoops_IRHGP, _hoops_AAHGP))
				 _hoops_HASGS (_hoops_RIGC, _hoops_SRCP, _hoops_SSCCA);
#endif
		}	break;

		case HK_TEXT_FONT:
		case HK_TEXT_PATH:
		case HK_TEXT_SPACING:
		case HK_TEXT_ALIGNMENT: {
			if (BIT (_hoops_SRCP->_hoops_RCGC, T_TEXT))
				_hoops_CRSGS (_hoops_RIGC, _hoops_SRCP, _hoops_GHSGS|_hoops_RPSIR|_hoops_SSCCA|_hoops_RSCCA);
		}	break;
	}

	_hoops_SRCP->_hoops_PCGPR |= _hoops_PCGPR;

#ifndef DISABLE_STYLE_SEGMENT
	if (_hoops_SRCP->_hoops_SGRPR() != null)
		_hoops_RPSGS (_hoops_RIGC, _hoops_SRCP->_hoops_SGRPR(), type, _hoops_PISCA, _hoops_SISCA, _hoops_PCGPR);
#endif

	/* _hoops_RRP _hoops_IS _hoops_CSRIP _hoops_HSSGR _hoops_RRRRS _hoops_SGI _hoops_CCGR _hoops_PCIAA _hoops_CHR _hoops_GIR */
	if (_hoops_SISCA != null && _hoops_SISCA->type == HK_COLOR)
		((_hoops_SSGI *)_hoops_SISCA)->_hoops_CCCIR = Color_NONE;

	if (_hoops_PISCA != null)
		_hoops_PISCA->_hoops_RRHH = _hoops_SPSGS;
}

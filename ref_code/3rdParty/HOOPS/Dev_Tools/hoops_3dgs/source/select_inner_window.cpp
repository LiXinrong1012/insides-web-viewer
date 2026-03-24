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
 * $Id: obf_tmp.txt 1.54 2010-06-22 05:26:51 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "please.h"
#include "select.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

#ifndef DISABLE_SELECTION

local void _hoops_AACAS (
	Window_Tree alter	*_hoops_PACAS) {
	Window_Tree alter	*next;
	Window_Tree alter	*_hoops_HACAS;

	do {
		next = _hoops_PACAS->_hoops_ICHSP;
		FREE (_hoops_PACAS, Window_Tree);

		/* _hoops_PSSSR _hoops_IH _hoops_HCIIA _hoops_IIGR _hoops_RH _hoops_SPS _hoops_RPSI */
		if (next != null && (_hoops_HACAS = next->_hoops_CGPAS) != null) do {
			next->_hoops_CGPAS = _hoops_HACAS->_hoops_CGPAS;
			_hoops_AACAS (_hoops_HACAS);
		} _hoops_RGGA ((_hoops_HACAS = next->_hoops_CGPAS) == null);
	}
	_hoops_RGGA ((_hoops_PACAS = next) == null);
}


local void _hoops_IACAS (
	Attribute const *		_hoops_ASGPR,
	Window_Tree alter *		_hoops_PACAS) {
	Attribute const	*		_hoops_SIIAA = _hoops_ASGPR;
	_hoops_PIGRA			_hoops_PCGS, _hoops_CIIAA;

	/* _hoops_HSPP _hoops_CCA _hoops_SGHS _hoops_GCIAA _hoops_HII _hoops_ARRS */
	_hoops_RSAI (&_hoops_PACAS->locks, _hoops_PIGRA, &_hoops_PCGS);
	ZERO_STRUCT (&_hoops_CIIAA, _hoops_PIGRA);

	do {
		if (_hoops_ASGPR->type == HK_RENDERING_OPTIONS) {
			_hoops_RHAIR const	*	_hoops_AHAIR = (_hoops_RHAIR const *)_hoops_ASGPR;

			if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_GSIAA)) {
				_hoops_PIGRA			_hoops_PHGIP;

				/* _hoops_PA _hoops_HSGRA _hoops_HRGR _hoops_HCAGR _hoops_ASIAA _hoops_HCIAA */
				_hoops_RSAI (&_hoops_AHAIR->locks->normal.mask, _hoops_PIGRA, &_hoops_CIIAA);
				// _hoops_HIH _hoops_HAR _hoops_PA _hoops_GRGA _hoops_ARP _hoops_IS _hoops_SSPC
				_hoops_HSIAA (&_hoops_CIIAA, &_hoops_PACAS->_hoops_HHGIP, sizeof (_hoops_PIGRA));

				/* _hoops_HASC _hoops_CCAH _hoops_AAHS _hoops_HRP */
				_hoops_HSIAA (&_hoops_PCGS, &_hoops_CIIAA, sizeof (_hoops_PIGRA));
				/* _hoops_PIASR _hoops_HRGR _hoops_PA _hoops_SR _hoops_HHGC _hoops_IS _hoops_AAHS, _hoops_ACCHA _hoops_GII _hoops_SR _hoops_SPGA'_hoops_RA _hoops_PHRH _hoops_IS _hoops_AGRP */
				_hoops_RSAI (&_hoops_AHAIR->locks->normal.value, _hoops_PIGRA, &_hoops_PHGIP);
				_hoops_HSIAA (&_hoops_PHGIP, &_hoops_PACAS->_hoops_HHGIP, sizeof (_hoops_PIGRA));

				_hoops_ISIAA (&_hoops_PCGS, &_hoops_PHGIP, sizeof (_hoops_PIGRA));

				/* _hoops_PPR _hoops_ARP _hoops_GPP _hoops_IPP */
				if (!EQUAL_MEMORY (&_hoops_PCGS, sizeof (_hoops_PIGRA), &_hoops_PACAS->locks)) {
					_hoops_RSAI (&_hoops_PCGS, _hoops_PIGRA, &_hoops_PACAS->locks);
				}

				/* _hoops_IH _hoops_IRGH _hoops_HCGC _hoops_ARP _hoops_RGR _hoops_IS _hoops_SRCH _hoops_CSIAA '_hoops_PCPAR _hoops_HIH _hoops_HCIAA _hoops_ASIAA' */
				_hoops_HSIAA (&_hoops_PCGS, &_hoops_CIIAA, sizeof (_hoops_PIGRA));
			}
			if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_RGRAP)) {
				// _hoops_AGCR _hoops_SAHR _hoops_RARHR -- _hoops_RPSI _hoops_PAH _hoops_HAR _hoops_HHSP
				_hoops_ISIAA (&_hoops_PACAS->_hoops_HHGIP, &_hoops_AHAIR->locks->_hoops_SACRP.value, sizeof (_hoops_PIGRA));
			}
			break;
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	_hoops_ASGPR = _hoops_SIIAA;


	do {
		switch (_hoops_ASGPR->type) {
			default: {
				/* _hoops_HGI "_hoops_ASRC" _hoops_IIAH _hoops_PGGA _hoops_CACAS._hoops_CIPII _hoops_GHACP _hoops_RH
				 * _hoops_RRHAR _hoops_IGRI _hoops_CPCP!!!!! (_hoops_AHSAR _hoops_IH _hoops_RH _hoops_CIAGR _hoops_CAPP)
				 */
				return;
			}	_hoops_HHHI;


			case _hoops_GRAIR:
			case HK_RENDERING_OPTIONS:
			case HK_COLOR_MAP:
			case HK_COLOR:
			case HK_WINDOW_PATTERN:
			case HK_WINDOW_FRAME: { /* _hoops_HAHH _hoops_HIS "_hoops_SHIR:" _hoops_IISA _hoops_GGSR _hoops_RPHR */
			}	break;

			case HK_STYLE: if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_STYLE))) {
#ifndef DISABLE_STYLE_SEGMENT
				_hoops_CRCP const	*ref = ((Style *)_hoops_ASGPR)->_hoops_IGRPR;

				if (ref->_hoops_IPPGR != null)
					_hoops_IACAS (ref->_hoops_IPPGR, _hoops_PACAS);
#endif
			}	break;

			case HK_SELECTABILITY: if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_SELECTABILITY))) {
				_hoops_ASAIR *			_hoops_AAICA = (_hoops_ASAIR *)_hoops_ASGPR;

				_hoops_PACAS->_hoops_AAICA &= ~_hoops_AAICA->mask;
				_hoops_PACAS->restricted_selectability &= ~_hoops_AAICA->mask;
				_hoops_PACAS->_hoops_PHARP &= ~_hoops_AAICA->mask;

				switch (_hoops_PACAS->_hoops_APHHP->event->_hoops_CHSHA) {
					case _hoops_HPSHA: {
						_hoops_PACAS->_hoops_AAICA |= _hoops_AAICA->down |
											 _hoops_AAICA->_hoops_AHARP;
						_hoops_PACAS->restricted_selectability |= _hoops_AAICA->down;
					}	break;

					case _hoops_IPSHA: {
						_hoops_PACAS->_hoops_AAICA |= _hoops_AAICA->_hoops_AHARP;
						_hoops_PACAS->restricted_selectability |= _hoops_AAICA->_hoops_AHARP;
					}	break;

					case _hoops_CPSHA: {
						_hoops_PACAS->_hoops_AAICA |= _hoops_AAICA->up |
											 _hoops_AAICA->_hoops_RHARP;
						_hoops_PACAS->restricted_selectability |= _hoops_AAICA->up;
					}	break;

					default: /* _hoops_AGIR _hoops_HIRIP: */ {
						_hoops_PACAS->_hoops_AAICA |= _hoops_AAICA->_hoops_RHARP;
						_hoops_PACAS->restricted_selectability |= _hoops_AAICA->_hoops_RHARP;
					}	break;
				}

				_hoops_PACAS->_hoops_PHARP |= _hoops_AAICA->_hoops_PHARP;
			}	break;

			case HK_VISIBILITY: {
				_hoops_RSAIR *			_hoops_RGP = (_hoops_RSAIR *)_hoops_ASGPR;
				_hoops_ACHR				_hoops_CCCIR = (_hoops_PACAS->_hoops_RGP ^ _hoops_RGP->value) &
												  (_hoops_RGP->mask & ~_hoops_PCGS._hoops_RGP);

				_hoops_PACAS->_hoops_RGP ^= _hoops_CCCIR;
			}	break;

			case HK_WINDOW: {
				Window *				window = (Window *)_hoops_ASGPR;
				float					scale,
										translate;

				scale = (_hoops_PACAS->window.right - _hoops_PACAS->window.left) * 0.5f;
				translate = (_hoops_PACAS->window.right + _hoops_PACAS->window.left) * 0.5f;

				_hoops_PACAS->window.left = window->_hoops_RCHS.left * scale + translate;
				_hoops_PACAS->window.right = window->_hoops_RCHS.right * scale + translate;

				scale = (_hoops_PACAS->window.top - _hoops_PACAS->window.bottom) * 0.5f;
				translate = (_hoops_PACAS->window.top + _hoops_PACAS->window.bottom) * 0.5f;

				_hoops_PACAS->window.bottom = window->_hoops_RCHS.bottom * scale + translate;
				_hoops_PACAS->window.top = window->_hoops_RCHS.top * scale + translate;

				if (_hoops_PACAS->_hoops_RRPAS.left < _hoops_PACAS->window.left)
					_hoops_PACAS->_hoops_RRPAS.left = _hoops_PACAS->window.left;
				if (_hoops_PACAS->_hoops_RRPAS.right > _hoops_PACAS->window.right)
					_hoops_PACAS->_hoops_RRPAS.right = _hoops_PACAS->window.right;
				if (_hoops_PACAS->_hoops_RRPAS.bottom < _hoops_PACAS->window.bottom)
					_hoops_PACAS->_hoops_RRPAS.bottom = _hoops_PACAS->window.bottom;
				if (_hoops_PACAS->_hoops_RRPAS.top > _hoops_PACAS->window.top)
					_hoops_PACAS->_hoops_RRPAS.top = _hoops_PACAS->window.top;
			}	break;
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
}


local void _hoops_SACAS (
	Window_Tree alter	*node) {
	Window_Tree alter	*next;
	Window_Tree alter	*_hoops_SCAAR;

	/* _hoops_APRI _hoops_GII _hoops_HCIIA _hoops_IIGR _hoops_RGR _hoops_GIIS _hoops_PPR _hoops_RGCI _hoops_PISIR */
	while ((_hoops_SCAAR = node->_hoops_SCAAR) != null) {
		/* _hoops_CIH _hoops_AGAP _hoops_IARRA _hoops_GGR _hoops_RH _hoops_HIGR (_hoops_PAHA'_hoops_RA _hoops_SHH _hoops_GII) */
		while (_hoops_SCAAR->_hoops_ICHSP != node) {
			next = _hoops_SCAAR->_hoops_ICHSP;
			_hoops_SCAAR->_hoops_ICHSP = next->_hoops_CGPAS;
			_hoops_AACAS (next);
		}
		/* _hoops_CIH _hoops_AGAP _hoops_SPHR _hoops_GGR _hoops_RH _hoops_HIGR */
		while (node->_hoops_CGPAS != null) {
			next = node->_hoops_CGPAS;
			node->_hoops_CGPAS = next->_hoops_CGPAS;
			_hoops_AACAS (next);
		}
		node = _hoops_SCAAR;
	}
}
#endif


GLOBAL_FUNCTION void HD_Select_Inner_Window (
	Subsegment alter *			_hoops_SSGPR,
	Window_Tree alter *			_hoops_SCAAR) {
#ifndef DISABLE_SELECTION
	_hoops_ACCCP alter	*	sc = _hoops_SCAAR->_hoops_APHHP;

	top:;

	do {
		_hoops_CRCP const *			_hoops_SRCP = _hoops_SSIGP (_hoops_SSGPR);

		if (BIT(_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR) || BIT(_hoops_SRCP->_hoops_RCGC, T_WINDOWS)) {
			Window_Tree alter	*_hoops_PACAS;

			ZALLOC (_hoops_PACAS, Window_Tree);
			_hoops_PACAS->_hoops_APHHP = _hoops_SCAAR->_hoops_APHHP;
			_hoops_PACAS->window.left = _hoops_SCAAR->window.left;
			_hoops_PACAS->window.right = _hoops_SCAAR->window.right;
			_hoops_PACAS->window.bottom = _hoops_SCAAR->window.bottom;
			_hoops_PACAS->window.top = _hoops_SCAAR->window.top;
			_hoops_PACAS->_hoops_RRPAS.left = _hoops_SCAAR->_hoops_RRPAS.left;
			_hoops_PACAS->_hoops_RRPAS.right = _hoops_SCAAR->_hoops_RRPAS.right;
			_hoops_PACAS->_hoops_RRPAS.bottom = _hoops_SCAAR->_hoops_RRPAS.bottom;
			_hoops_PACAS->_hoops_RRPAS.top = _hoops_SCAAR->_hoops_RRPAS.top;
			_hoops_PACAS->_hoops_AAICA = _hoops_SCAAR->_hoops_AAICA;
			_hoops_PACAS->restricted_selectability = _hoops_SCAAR->restricted_selectability;
			_hoops_PACAS->_hoops_PHARP = _hoops_SCAAR->_hoops_PHARP;
			_hoops_PACAS->_hoops_RGP = _hoops_SCAAR->_hoops_RGP;
			_hoops_PACAS->locks = _hoops_SCAAR->locks;
			_hoops_PACAS->_hoops_HHGIP = _hoops_SCAAR->_hoops_HHGIP;

			if (_hoops_SRCP->_hoops_IPPGR != null)
				_hoops_IACAS (_hoops_SRCP->_hoops_IPPGR, _hoops_PACAS);

			if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) {
				if (BIT (_hoops_PACAS->_hoops_RGP, T_WINDOWS) &&
					_hoops_PACAS->_hoops_RRPAS.left	  <= sc->xw &&
									   sc->xw <= _hoops_PACAS->_hoops_RRPAS.right &&
					_hoops_PACAS->_hoops_RRPAS.bottom <= sc->yw &&
									   sc->yw <= _hoops_PACAS->_hoops_RRPAS.top) {
					/* _hoops_GGHP _hoops_SPR! */

					if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_RCHGP)) {
						Window_Tree alter	*next;

						/* _hoops_CCPH _hoops_SGGR _hoops_PA _hoops_PGHC */
						while ((next = _hoops_SCAAR->_hoops_ICHSP) != null) {
							_hoops_SCAAR->_hoops_ICHSP = next->_hoops_CGPAS;
							_hoops_AACAS (next);
						}
						_hoops_SACAS (_hoops_SCAAR);
					}

					_hoops_PACAS->_hoops_CGPAS = _hoops_SCAAR->_hoops_ICHSP;
					_hoops_SCAAR->_hoops_ICHSP = _hoops_PACAS;
					_hoops_PACAS->_hoops_SCAAR = _hoops_SCAAR;
					_hoops_PACAS->_hoops_ICHSP = null;
					_hoops_PACAS->_hoops_SRCP = _hoops_SRCP;
					_hoops_PACAS->_hoops_GIPIA = _hoops_SSGPR;

					if (!BIT(_hoops_SRCP->_hoops_RCGC, T_WINDOWS) || _hoops_SRCP->_hoops_RGRPR == null)
						/* _hoops_IRAHR */;
					else if (_hoops_SSGPR->next != null)
						HD_Select_Inner_Window (_hoops_SRCP->_hoops_RGRPR, _hoops_PACAS);
					else {
						_hoops_SSGPR = _hoops_SRCP->_hoops_RGRPR;
						_hoops_SCAAR = _hoops_PACAS;
						goto top;
					}
				}
				else FREE (_hoops_PACAS, Window_Tree);
			}
			else if (_hoops_SRCP->_hoops_RGRPR != null) {
				/* _hoops_GHCA _hoops_SHH _hoops_SPHGR _hoops_ASSA; _hoops_PIHA _hoops_PHHR _hoops_GGR */

				_hoops_PACAS->_hoops_ICHSP = null;
				_hoops_PACAS->_hoops_SRCP = _hoops_SRCP;
				_hoops_PACAS->_hoops_GIPIA = _hoops_SSGPR;
				_hoops_PACAS->_hoops_CGPAS = _hoops_SCAAR->_hoops_ICHSP;
				_hoops_SCAAR->_hoops_ICHSP = _hoops_PACAS;
				_hoops_PACAS->_hoops_SCAAR = _hoops_SCAAR;

				HD_Select_Inner_Window (_hoops_SRCP->_hoops_RGRPR, _hoops_PACAS);

				if (_hoops_PACAS->_hoops_ICHSP == null) { /* _hoops_HHPPA, _hoops_PSP _hoops_GPCAS */
#					ifdef _hoops_CGSPR
						if (_hoops_SCAAR->_hoops_ICHSP != _hoops_PACAS)
							_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									"Bad child assumption");
#					endif
					_hoops_SCAAR->_hoops_ICHSP = _hoops_PACAS->_hoops_CGPAS;
					FREE (_hoops_PACAS, Window_Tree);
				}
			}
			else FREE (_hoops_PACAS, Window_Tree);
		}
	} while ((_hoops_SSGPR = _hoops_SSGPR->next) != null);
#endif
}

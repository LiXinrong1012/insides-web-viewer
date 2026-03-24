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
 * $Id: obf_tmp.txt 1.75 2010-12-06 22:05:40 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "please.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "adt.h"


GLOBAL_FUNCTION void HI_Disentangle (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				thing) {

	/* _hoops_HASIR _hoops_RH _hoops_PIISA _hoops_HII _hoops_RGCI _hoops_SHISR _hoops_AARPR _hoops_GCAHP
	   (_hoops_IIH _hoops_GHCA _hoops_HGGC _hoops_SHH _hoops_RII _hoops_PRCHR _hoops_RCAHP)
	 */

	top:;

	switch (thing->type) {
		case _hoops_IRCP: {
			_hoops_CRCP		*_hoops_SRCP = (_hoops_CRCP *)thing;

			HI_Delete_Renditions (_hoops_RIGC, _hoops_SRCP, null, null, true);

			if (_hoops_SRCP->_hoops_SGRPR() != null) {
				Xref			*x, *xnext;

				x = _hoops_SRCP->_hoops_SGRPR();

				do {
					xnext = x->_hoops_GRRPR;
					HI_Disentangle (_hoops_RIGC, (_hoops_HPAH *)x);
					_hoops_CIGPR (_hoops_RIGC,x);
					_hoops_HPRH (x);
				} while ((x = xnext) != null);
			}
			_hoops_SRCP->_hoops_ISRIR (null);

			_hoops_RPAPA * _hoops_APAPA = HOOPS_WORLD->_hoops_PPAPA->Remove(_hoops_SRCP);

			if (_hoops_APAPA != null) {

				_hoops_PHIP *	_hoops_RRA;
				while ((_hoops_RRA = _hoops_APAPA->RemoveFirst()) != null) {
					HI_Disentangle (_hoops_RIGC, (_hoops_HPAH *)_hoops_RRA);
					_hoops_CIGPR (_hoops_RIGC, _hoops_RRA);
					_hoops_HPRH (_hoops_RRA);
				}

				delete _hoops_APAPA;
			}

			// _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_RGRIR _hoops_HHSIR _hoops_GAR _hoops_SR _hoops_CHR(?) _hoops_GIAA _hoops_IRS _hoops_IHSIR
			if (_hoops_SRCP->_hoops_RHASA() != null)
				HI_Destroy_Fast_Lookups (_hoops_RIGC, _hoops_SRCP);

			if (_hoops_SRCP->_hoops_GACP)
				delete _hoops_SRCP->_hoops_GACP;
			_hoops_SRCP->_hoops_GACP = null;

			if ((thing = (_hoops_HPAH *)_hoops_SRCP->geometry) != null) {
				do
					HI_Disentangle (_hoops_RIGC, thing);
				while ((thing = thing->next) != null);
			}
			if ((thing = (_hoops_HPAH *)_hoops_SRCP->_hoops_IPPGR) != null) {
				do
					HI_Disentangle (_hoops_RIGC, thing);
				while ((thing = thing->next) != null);
			}
			if ((thing = (_hoops_HPAH *)_hoops_SRCP->_hoops_RGRPR) != null) {
				do if (thing->next == null)
						goto top;	/* _hoops_SRCH _hoops_ACAHP _hoops_PAGIR! */
					else
						HI_Disentangle (_hoops_RIGC, thing);
				while ((thing = thing->next) != null);
			}
		}	break;

		case _hoops_AGRPR: {
			_hoops_PGRPR alter *		include = (_hoops_PGRPR *)thing;

			HI_Delete_Renditions (_hoops_RIGC, _hoops_PGRCA(include->_hoops_IGRPR), include);

			if ((*include->_hoops_SHAIR = include->_hoops_GRRPR) != null)
				include->_hoops_GRRPR->_hoops_SHAIR = include->_hoops_SHAIR;
		}	break;

		case HK_DRIVER: {
			_hoops_GGAGR alter *		driver = (_hoops_GGAGR *)thing;

			/* _hoops_HASIR _hoops_HII _hoops_GHARR _hoops_HIGR */
			if ((*driver->_hoops_RAIAP = driver->_hoops_CISHA) != null)
				driver->_hoops_CISHA->_hoops_RAIAP = driver->_hoops_RAIAP;
		}	break;

		case HK_STYLE: {
#ifndef DISABLE_STYLE_SEGMENT
			Style alter *		style = (Style *)thing;

			if (style->_hoops_IGRPR && (*style->_hoops_SHAIR = style->_hoops_GRRPR) != null)
				style->_hoops_GRRPR->_hoops_SHAIR = style->_hoops_SHAIR;
#endif
		}	break;

		case _hoops_AHIP: {
			_hoops_PHIP alter *	_hoops_RRA = (_hoops_PHIP *)thing;
			if (!BIT(_hoops_RRA->_hoops_RRHH, _hoops_IIHIR))
				_hoops_CIHIR(_hoops_RIGC, _hoops_RRA, true);
		}	break;

		case _hoops_CCHIR: {
			_hoops_SCHIR *		_hoops_GSHIR = (_hoops_SCHIR *)thing;
			_hoops_RSHIR	*_hoops_ASHIR;

			/* _hoops_AAAI _hoops_HII _hoops_SCAH _hoops_GASR */

			if ((_hoops_ASHIR = _hoops_GSHIR->_hoops_HSHIR) != null)
				do if ((*_hoops_ASHIR->_hoops_GGSAP = _hoops_ASHIR->_hoops_SSCAP) != null)
					_hoops_ASHIR->_hoops_SSCAP->_hoops_GGSAP = _hoops_ASHIR->_hoops_GGSAP;
				_hoops_RGGA ((_hoops_ASHIR = _hoops_ASHIR->next) == null);

			thing->_hoops_RRHH |= _hoops_HGAGR;
		}	break;

		case _hoops_IIPPR:	{
			thing->_hoops_RRHH |= _hoops_HGAGR;
		}	break;

		case _hoops_PCHIR:	{
			thing->_hoops_RRHH |= _hoops_HGAGR;
		}	break;
	}
}

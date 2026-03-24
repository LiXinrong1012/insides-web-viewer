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
 * $Id: obf_tmp.txt 1.62 2009-11-17 04:44:53 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"


#define _hoops_HGIIS(x) ((1.0f/255.0f) * (float)_hoops_IRGCR(x))


GLOBAL_FUNCTION void HD_Std_3D_Light (
	Net_Rendition const &		inr,
	Light const *				_hoops_IGIIS) {
	_hoops_SHPIR const *			light = (_hoops_SHPIR const *)_hoops_IGIIS;		// _hoops_CCAC _hoops_HRGR _hoops_RH _hoops_RGAR _hoops_GPRR _hoops_SR _hoops_RIPIR _hoops_CRGR
	Net_Rendition				nr = inr;
	Polygon alter *				polygon;
	Display_Context const *		dc = nr->_hoops_SRA;

	// _hoops_IPIH, _hoops_SR _hoops_RGAR _hoops_AIRI _hoops_CCAC _hoops_SS _hoops_GAR _hoops_PA
	if (light->_hoops_PRR != _hoops_S) return;


	// _hoops_RPP _hoops_SS _hoops_CHR _hoops_SIGC, _hoops_SR _hoops_HHGC _hoops_IS _hoops_PGSA _hoops_RGR _hoops_GGR _hoops_RH _hoops_SCGR "_hoops_RRR"
	// _hoops_HAIR, _hoops_SHS _hoops_SR _hoops_PGSA _hoops_SCH _hoops_SAHR _hoops_GAR _hoops_IRS _hoops_HSP

	if (BIT (nr->_hoops_RGP, T_ANY_LIGHTS)) {
		_hoops_PC				_hoops_CGIIS = _hoops_PC::Create(dc);
		_hoops_CIGA alter &		_hoops_CPIHP = nr.Modify()->_hoops_IHA.Modify();

		// _hoops_SR _hoops_GRS _hoops_HGCR _hoops_RH _hoops_HAIR _hoops_GGSP _hoops_HPP _hoops_GHHAI _hoops_IRS _hoops_PGS _hoops_HSP _hoops_CCA
		// _hoops_PCCP _hoops_AASR _hoops_HAIR _hoops_SGS _hoops_SPASR _hoops_RH _hoops_RRR _hoops_HAIR

		if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
			/* _hoops_IIH'_hoops_GRI _hoops_IRS _hoops_PGS _hoops_GGR _hoops_RH _hoops_RPIHR _hoops_GASR */
			_hoops_CPIHP->color._hoops_PGGCR = dc->_hoops_RHGCR + dc->_hoops_GCPRP - 1;
		}
		else {
			_hoops_CPIHP->color._hoops_HRIR.r = 255;
			_hoops_CPIHP->color._hoops_HRIR.g = 255;
			_hoops_CPIHP->color._hoops_HRIR.b = 255;
		}

		/* _hoops_RRP _hoops_IS "_hoops_RRR" _hoops_RGR _hoops_SPR _hoops_GAR 100% _hoops_AASR _hoops_RGAR */
		_hoops_CPIHP->_hoops_AGP = _hoops_CGIIS;
		nr->transform_rendition.Modify()->flags &= ~_hoops_IGSP;

		_hoops_GRGH alter &		_hoops_RRGH = nr->_hoops_IRR.Modify();
		_hoops_RRGH->_hoops_HASR = _hoops_RRGH->_hoops_PCP;
		nr->_hoops_RGP &= ~T_ANY_EDGE;
	}
	else {
		if (!BIT (nr->_hoops_RGP, T_FACES)) {
			/* _hoops_APSH _hoops_PII _hoops_SR _hoops_GA'_hoops_RA _hoops_PGSA _hoops_PA! */
			return;
		}
	}

	ZALLOC (polygon, Polygon);

	polygon->_hoops_HIHI = 1;
	polygon->type = _hoops_RCIP;
	polygon->_hoops_CPGPR = _hoops_PHSSR;
	polygon->count = light->count;
	polygon->allocated = light->count;
	_hoops_APRGA(light->points, polygon->count, Point, polygon->points);

	_hoops_RCAIP (nr, polygon);

	_hoops_HPRH (polygon);
}

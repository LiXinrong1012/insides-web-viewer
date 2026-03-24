/*
 * Copyright (c) 2001 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.31 2010-10-02 07:04:42 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hi_proto.h"
#include "hd_proto.h"
#include "phedron.h"
#include "hpserror.h"


GLOBAL_FUNCTION void HD_Std_3D_NURBS_Surface (
	Net_Rendition const &		inr,
	_hoops_APPGR const *		surface) {
#ifndef _hoops_GSPIR
	Net_Rendition				nr = inr;
	_hoops_SPAGR						_hoops_RIIAA (surface->_hoops_RHAGR, nr->_hoops_SRA->_hoops_RIGC->thread_id);


	if (surface->n_u_vertices == 0 && surface->n_v_vertices == 0)
		return;

	if (surface->_hoops_IPRI == null ||
		surface->_hoops_GRPPA != nr->_hoops_ARA->_hoops_APSHP._hoops_GRPPA)
		HI_Tessellate_NURBS_Surface (nr->_hoops_SRA->_hoops_RIGC, surface, &nr->_hoops_ARA->_hoops_APSHP);


	// _hoops_GIHA _hoops_CHR _hoops_RIPGS _hoops_PSAP _hoops_GGR _hoops_RH _hoops_RRCPR _hoops_SCCI _hoops_IIGR _hoops_IRS _hoops_IRCPH _hoops_ISSGR,
	// _hoops_HIH _hoops_RPP _hoops_RH _hoops_IPP _hoops_SSCP _hoops_CAPR _hoops_PCPAR _hoops_GPP, _hoops_SR _hoops_RRP _hoops_IS _hoops_CHASA _hoops_SGS _hoops_ARI
	if (BIT (nr->_hoops_RGP, T_VERTICES) &&
		BIT (nr->_hoops_IRR->locks._hoops_RGP, T_VERTICES))
		nr.Modify()->_hoops_RGP &= ~T_VERTICES;


	if (nr->_hoops_RSGC->action.draw_3d_polyhedron != nullroutine) {
		_hoops_SHICP (nr, draw_3d_polyhedron)(&nr, surface->_hoops_IPRI);
	}
	else  {
		/* _hoops_ARIIS (_hoops_SCII, _hoops_PRIIS)(_hoops_SCII, _hoops_ISSGR->_hoops_CPHAR); */
		HD_Std_3D_Polyhedron (nr, surface->_hoops_IPRI);
	}
#endif
}


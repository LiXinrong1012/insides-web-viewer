
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
 * $Id: obf_tmp.txt 1.18 2010-03-17 22:42:11 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "tandt.h"
#include "select.h"
#include "topology.h"
#include "patterns.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "phedron.h"

#ifndef DISABLE_SELECTION

GLOBAL_FUNCTION void HD_Select_NURBS_Surface (
	Net_Rendition const &		nr,
	_hoops_APPGR const *		surface) {
#ifndef _hoops_GSPIR
	_hoops_SPAGR						_hoops_RIIAA (surface->_hoops_RHAGR, nr->_hoops_SRA->_hoops_RIGC->thread_id);

	if (surface->_hoops_IPRI == null) {
		HI_Tessellate_NURBS_Surface (nr->_hoops_SRA->_hoops_RIGC, (_hoops_APPGR alter *)surface, &nr->_hoops_ARA->_hoops_APSHP);
	}

	HD_Select_Polyhedron (nr, surface->_hoops_IPRI);
#endif
}
#endif

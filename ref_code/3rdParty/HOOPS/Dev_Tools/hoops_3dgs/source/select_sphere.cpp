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
 * $Id: obf_tmp.txt 1.20 2010-06-18 20:19:58 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "phedron.h"
#include "tandt.h"
#include "select.h"
#include "topology.h"
#include "phdraw.h"
#include "patterns.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "phdraw.h"




GLOBAL_FUNCTION void HD_Select_Sphere (
	Net_Rendition const &	nr,
	Sphere const *			sphere) 
{
#ifndef DISABLE_SELECTION
#ifndef _hoops_RRHIR

	if (BIT (nr->transform_rendition->_hoops_APH, Heur_Culling_VIEW_FRUSTUM)) {

		Display_Context alter	*	dc = (Display_Context alter *)nr->_hoops_SRA;
		_hoops_ACCCP alter	*	sc = dc->_hoops_APHHP;

		Net_Rendition				_hoops_ISGPS = nr.Copy();
		_hoops_CGRA			_hoops_SGRA = _hoops_ISGPS->_hoops_SAIR.Modify();

		_hoops_SGRA->_hoops_HHCAR.left = sc->bounding.left;
		_hoops_SGRA->_hoops_HHCAR.right = sc->bounding.right;
		_hoops_SGRA->_hoops_HHCAR.bottom = sc->bounding.bottom;
		_hoops_SGRA->_hoops_HHCAR.top = sc->bounding.top;

		Test _hoops_ASIS = Test_DISJOINT;

		HD_Transform_And_Test_Simple_Sphere (_hoops_ISGPS, 1, &sphere->data, null, 0.0f, 0.0f, &_hoops_ASIS, null, null);

		if (_hoops_ASIS == Test_DISJOINT)
			return;
	}

	HD_Select_Sphere_Polyhedron (nr, sphere);
	return;

#endif
#endif
}






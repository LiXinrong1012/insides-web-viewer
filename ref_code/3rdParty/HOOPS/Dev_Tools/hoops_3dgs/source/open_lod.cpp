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
 * $Id: obf_tmp.txt 1.24 2010-10-06 19:16:07 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


HC_INTERFACE void HC_CDECL HC_Open_LOD (
	int						offset)
{
	_hoops_PAPPR context("Open_LOD");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_D (null, "HC_Open_LOD (%d);\n", offset));
		HOOPS_WORLD->_hoops_ISPPR += 2;
	);

	_hoops_SIRIR *	_hoops_RGGGC = null;

	if (context->open_list == null) {
		HE_ERROR (HEC_LOD, HES_OPEN_GEOMETRY, "Must 'Open_Geometry' or 'Open_Segment' first");
		return;
	}
	if (context->open_list->_hoops_GCRIR != _hoops_HCRIR &&
		context->open_list->_hoops_GCRIR != _hoops_RCRIR) {
		HE_ERROR (HEC_LOD, HES_INVALID_OPEN, "Most recent 'Open' was not an 'Open_Geometry' or 'Open_Segment'");
		return;
	}

	if (context->open_list->_hoops_GCRIR == _hoops_HCRIR) {
		Geometry *	geometry = (Geometry *)context->open_list->info.geometry._hoops_IGRPR;
		switch (geometry->type) {
			case _hoops_GSIP:
			case _hoops_SCIP: {
				if (offset < 0) {
					HE_ERROR(HEC_LOD, HES_NEGATIVE_OFFSET, "LOD indices must be positive");
					return;
				}
				else if (offset > _hoops_IGAIR) {
					HE_ERROR(HEC_LOD, HES_ZERO_OFFSET, "LOD level out of range");
					return;
				}
			}	break;

			default: {
				HE_ERROR (HEC_LOD, HES_OPEN_SHELL_OR_MESH_ONLY, "Can only 'Open_LOD' within an open Shell or Mesh");
				return;
			}	/* _hoops_IHSA; */
		}
		ZALLOC (_hoops_RGGGC, _hoops_SIRIR);
		_hoops_RGGGC->info._hoops_PRSI._hoops_IGRPR = (_hoops_HPAH *) geometry;
		_hoops_PRRH (geometry);
	}
	else if (context->open_list->_hoops_GCRIR == _hoops_RCRIR) {
		_hoops_CRCP *	segment = (_hoops_CRCP *)context->open_list->info.segment._hoops_IGRPR;
		ZALLOC (_hoops_RGGGC, _hoops_SIRIR);
		_hoops_RGGGC->info._hoops_PRSI._hoops_IGRPR = (_hoops_HPAH *) segment;
		_hoops_PRRH (segment);
	}

	_hoops_RGGGC->type = _hoops_CIRIR;
	_hoops_RGGGC->_hoops_HIHI = 1;
	_hoops_RGGGC->owner = HOOPS_WORLD;
	_hoops_RGGGC->_hoops_GCRIR = _hoops_RSRIR;
	_hoops_RGGGC->info._hoops_PRSI.offset = offset;

	_hoops_IPAPP(context, _hoops_RGGGC);
}


HC_INTERFACE void HC_CDECL HC_Close_LOD (void)
{
	_hoops_PAPPR context("Close_LOD");

	CODE_GENERATION (
		HOOPS_WORLD->_hoops_ISPPR -= 2;
		HI_Dump_Code ("HC_Close_LOD ();\n");
	);

	_hoops_SIRIR *	_hoops_AHSCA = context->open_list;
	if (_hoops_AHSCA == null || _hoops_AHSCA->_hoops_GCRIR != _hoops_RSRIR) {
		HI_Close_Complaint (context, _hoops_RSRIR);
		return;
	}

	/* _hoops_IPCA */
	_hoops_CIGPR (context, _hoops_AHSCA);
	_hoops_HPRH (_hoops_AHSCA);

	/* _hoops_SGS _hoops_CSAP _hoops_CAHPH */

	/* _hoops_IRS _hoops_PGHC _hoops_SSHHC _hoops_III _hoops_SIAS _hoops_HS _hoops_RIPPR, _hoops_HIS _hoops_SAHR _hoops_PCHIA _hoops_SCH */
	_hoops_AHSCA = context->open_list;
	if (_hoops_AHSCA != null && _hoops_AHSCA->_hoops_GCRIR == _hoops_RCRIR && _hoops_AHSCA->info.segment._hoops_ACRIR != null) {
		_hoops_HPRH (_hoops_AHSCA->info.segment._hoops_ACRIR);
		_hoops_AHSCA->info.segment._hoops_ACRIR = null;
	}
}



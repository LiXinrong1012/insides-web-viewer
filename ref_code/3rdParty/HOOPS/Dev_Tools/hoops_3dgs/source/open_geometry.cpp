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
 * $Id: obf_tmp.txt 1.50 2010-10-06 19:16:00 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


HC_INTERFACE void HC_CDECL HC_Open_Geometry (
	Key						key) 
{
	_hoops_PAPPR context("Open_Geometry");

#ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Open_Geometry (LOOKUP (%D));\n", key));
		HOOPS_WORLD->_hoops_ISPPR += 2;
	);

	int	offset;
	_hoops_RPPPR();
	Geometry *	geometry = (Geometry *)_hoops_SISIR (context, key, &offset);

	if (geometry == null ||
		geometry->type < (Type)_hoops_AHRIR ||
		geometry->type > (Type)_hoops_PHRIR ||
		BIT (geometry->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_GEOMETRY, HES_INVALID_KEY, "Provided key does not refer to valid geometry");
		goto Release;
	}

	if (BIT (geometry->_hoops_RRHH, _hoops_CHRIR)) {
		bool		_hoops_HSSAP = (key > _hoops_SHSSR);
		bool		_hoops_GGIHC = _hoops_HSSAP && HI_Has_Local_Key (geometry->owner, key);

		if (_hoops_HSSAP)
			HI_Delete_User_Key (context, (_hoops_HPAH *)geometry, key);

		if (geometry->type == _hoops_HIIP)
			geometry = (Geometry *)HI_Isolate_Line_From_Multiline (context, (_hoops_SHRIR *)geometry, offset);
		else if (geometry->type == _hoops_PIRS)
			geometry = (Geometry *)HI_Isolate_Marker_From_Multimarker (context, (_hoops_GRPGR *)geometry, offset);

		if (_hoops_HSSAP)
			HI_Set_User_Key (context, (_hoops_HPAH *)geometry, 0, key, _hoops_GGIHC);
	}

	_hoops_SIRIR *	_hoops_RGGGC;
	ZALLOC (_hoops_RGGGC, _hoops_SIRIR);
	_hoops_RGGGC->type = _hoops_CIRIR;
	_hoops_RGGGC->_hoops_HIHI = 1;
	_hoops_RGGGC->owner = HOOPS_WORLD;
	_hoops_RGGGC->_hoops_GCRIR = _hoops_HCRIR;

	_hoops_RGGGC->info.geometry._hoops_IGRPR = geometry;
	_hoops_PRRH (geometry);

	_hoops_IPAPP(context, _hoops_RGGGC);

  Release:
	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Close_Geometry (void) 
{
	_hoops_PAPPR context("Close_Geometry");

#ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
#else
	CODE_GENERATION (
		HOOPS_WORLD->_hoops_ISPPR -= 2;
		HI_Dump_Code ("HC_Close_Geometry ();\n");
	);

	_hoops_SIRIR *	_hoops_AHSCA = context->open_list;
	if (_hoops_AHSCA == null || _hoops_AHSCA->_hoops_GCRIR != _hoops_HCRIR) {
		HI_Close_Complaint (context, _hoops_HCRIR);
		return;
	}

	/* _hoops_IPCA */
	_hoops_CIGPR (context,_hoops_AHSCA);
	_hoops_HPRH (_hoops_AHSCA);

	/* _hoops_SGS _hoops_CSAP _hoops_CAHPH */

	/* _hoops_IRS _hoops_PGHC _hoops_SSHHC _hoops_III _hoops_SIAS _hoops_HS _hoops_RIPPR, _hoops_HIS _hoops_SAHR _hoops_PCHIA _hoops_SCH */
	_hoops_AHSCA = context->open_list;
	if (_hoops_AHSCA != null && 
		_hoops_AHSCA->_hoops_GCRIR == _hoops_RCRIR && 
		_hoops_AHSCA->info.segment._hoops_ACRIR != null) {
		_hoops_HPRH (_hoops_AHSCA->info.segment._hoops_ACRIR);
		_hoops_AHSCA->info.segment._hoops_ACRIR = null;
	}
#endif
}

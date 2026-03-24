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
 * $Id: obf_tmp.txt 1.54 2010-10-06 19:16:07 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"



HC_INTERFACE void HC_CDECL HC_Open_Vertex (
	int						offset)
{
	_hoops_PAPPR context("Open_Vertex");

#ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_D (null, "HC_Open_Vertex (%d);\n", offset));
		HOOPS_WORLD->_hoops_ISPPR += 2;
	);

	if (context->open_list == null) {
		HE_ERROR (HEC_VERTEX, HES_OPEN_GEOMETRY, "Must 'Open_Geometry' first");
		return;
	}
	if (context->open_list->_hoops_GCRIR != _hoops_HCRIR) {
		HE_ERROR (HEC_VERTEX, HES_INVALID_OPEN, "Most recent 'Open' was not an 'Open_Geometry'");
		return;
	}

	Polyhedron *	_hoops_IPRI = context->open_list->info._hoops_IPRI._hoops_IGRPR;
	_hoops_SIRIR *		_hoops_RGGGC;

	switch (_hoops_IPRI->type) {
		case _hoops_GSIP:
		case _hoops_SCIP: {
			if (offset >= _hoops_IPRI->point_count || offset < 0) {
				HI_Vertex_Complaint (offset, _hoops_IPRI);
				return;
			}
		}	break;

		case _hoops_CSIP: {
			PolyCylinder const *	_hoops_HSPIR = (PolyCylinder const *)_hoops_IPRI;

			if (offset >= _hoops_HSPIR->point_count || offset < 0) {
				HI_Vertex_Complaint (offset, _hoops_IPRI);
				return;
			}
		}	break;

		default: {
			HE_ERROR (HEC_VERTEX, HES_OPEN_TRISTRIP_ONLY,
					"Can only 'Open_Vertex' within an open Shell, Mesh, or PolyCylinder");
			return;
		}		/* _hoops_IHSA; */
	}

	ZALLOC (_hoops_RGGGC, _hoops_SIRIR);
	_hoops_RGGGC->type = _hoops_CIRIR;
	_hoops_RGGGC->_hoops_HIHI = 1;
	_hoops_RGGGC->owner = HOOPS_WORLD;
	_hoops_RGGGC->_hoops_GCRIR = _hoops_SCRIR;

	/* _hoops_RGR _hoops_IIAH _hoops_IH _hoops_RSRRA _hoops_HAH */
	_hoops_RGGGC->info._hoops_IPRI._hoops_IGRPR = _hoops_IPRI;
	_hoops_PRRH (_hoops_IPRI);
	_hoops_RGGGC->info._hoops_IPRI.offset = offset;

	_hoops_IPAPP(context, _hoops_RGGGC);

#endif
}


HC_INTERFACE void HC_CDECL HC_Close_Vertex (void)
{
	_hoops_PAPPR context("Close_Vertex");

#ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
#else
	CODE_GENERATION (
		HOOPS_WORLD->_hoops_ISPPR -= 2;
		HI_Dump_Code ("HC_Close_Vertex ();\n");
	);

	_hoops_SIRIR *	_hoops_AHSCA = context->open_list;
	if (_hoops_AHSCA == null || _hoops_AHSCA->_hoops_GCRIR != _hoops_SCRIR) {
		HI_Close_Complaint (context, _hoops_SCRIR);
		return;
	}

	/* _hoops_IPCA */
	_hoops_CIGPR (context,_hoops_AHSCA);
	_hoops_HPRH (_hoops_AHSCA);

	/* _hoops_SGS _hoops_CSAP _hoops_CAHPH */

	/* _hoops_IRS _hoops_PGHC _hoops_SSHHC _hoops_III _hoops_SIAS _hoops_HS _hoops_RIPPR, _hoops_HIS _hoops_SAHR _hoops_PCHIA _hoops_SCH */
	_hoops_AHSCA = context->open_list;
	if (_hoops_AHSCA->_hoops_GCRIR == _hoops_RCRIR && _hoops_AHSCA->info.segment._hoops_ACRIR != null) {
		_hoops_HPRH (_hoops_AHSCA->info.segment._hoops_ACRIR);
		_hoops_AHSCA->info.segment._hoops_ACRIR = null;
	}
#endif
}


GLOBAL_FUNCTION void HI_Vertex_Complaint (
	int				offset,
	Polyhedron	*_hoops_IPRI) {
	char			buf[MAX_ERRMSG];

	switch (_hoops_IPRI->type) {
		case _hoops_GSIP: {
			_hoops_AIHPR const *		_hoops_PIHPR = (_hoops_AIHPR const *)_hoops_IPRI;

			HE_ERROR2 (HEC_VERTEX, HES_INVALID_OFFSET,
				Sprintf_DD (null, "A vertex at row %d, column %d", offset / _hoops_PIHPR->columns, offset % _hoops_PIHPR->columns),
				Sprintf_DD (buf, "is not within a %d x %d mesh.", _hoops_PIHPR->rows, _hoops_PIHPR->columns));
		}	break;

		case _hoops_SCIP: {
			if (offset < 0)
				HE_ERROR (HEC_VERTEX, HES_INVALID_OFFSET,
						Sprintf_D (null, "Shell vertex offset of '%d' shouldn't be negative", offset));
			else
				HE_ERROR (HEC_VERTEX, HES_INVALID_OFFSET,
						Sprintf_DD (null,"Can't open vertex at offset '%d' - shell only has %d", offset, _hoops_IPRI->point_count));
		}	break;

		case _hoops_CSIP: {
			PolyCylinder const * _hoops_HSPIR = (PolyCylinder const *)_hoops_IPRI;

			if (offset < 0)
				HE_ERROR (HEC_VERTEX, HES_INVALID_OFFSET,
						Sprintf_D (null,"PolyCylinder vertex offset of '%d' shouldn't be negative", offset));
			else
				HE_ERROR (HEC_VERTEX, HES_INVALID_OFFSET,
						Sprintf_DD (null,"Can't open vertex at offset '%d' - polycylinder only has %d",offset, _hoops_HSPIR->point_count));
		}	break;
	}
}

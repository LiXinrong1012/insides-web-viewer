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
 * $Id: obf_tmp.txt 1.41 2010-07-29 22:00:10 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


HC_INTERFACE void HC_CDECL HC_Flush_By_Key (
	Key			key) 
{	
	_hoops_PAPPR context("Flush_By_Key");

#ifdef DISABLE_DATABASE_EDIT
	_hoops_IRPPR ("Database Edit");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Flush_By_Key (LOOKUP (%D));\n", key));
	);
	
	_hoops_RPPPR();

	_hoops_HPAH *	_hoops_CISIR = (_hoops_HPAH *)_hoops_RCSSR (context, key);

	if (_hoops_CISIR == null) {}
	else if (_hoops_CISIR->type == _hoops_IRCP) {
		if (!BIT(_hoops_CISIR->_hoops_RRHH, _hoops_HGAGR)) {
			HI_Flush_Geometry (context, (_hoops_CRCP *)_hoops_CISIR, null);
			goto Release;
		}
	}
	else if (!BIT (_hoops_CISIR->_hoops_RRHH, _hoops_HGAGR)) {
		switch (_hoops_CISIR->type) {
			case _hoops_SCIP: {
				Shell *		_hoops_SPHPR = (Shell *)_hoops_CISIR;

				if (_hoops_SPHPR->point_count > 0) {
					PUSHNAME(context);
					HC_Edit_Shell_Points (key, 0, _hoops_SPHPR->point_count, 0, null);
					POPNAME(context);
				}
				goto Release;
			}	/* _hoops_IHSA; */

			case _hoops_RCIP: {
				Polygon *	polygon = (Polygon *)_hoops_CISIR;

				if (polygon->count > 0) {
					PUSHNAME(context);
					HC_Edit_Polygon (key, 0, polygon->count, 0, null);
					POPNAME(context);
				}
				goto Release;
			}	/* _hoops_IHSA; */

			case _hoops_IIIP: {
				Polyline *	polyline = (Polyline *)_hoops_CISIR;

				if (polyline->count > 0) {
					PUSHNAME(context);
					HC_Edit_Polyline (key, 0, polyline->count, 0, null);
					POPNAME(context);
				}
				goto Release;
			}	/* _hoops_IHSA; */

			case _hoops_AGCP: {
				_hoops_HACC *	text = (_hoops_HACC *)_hoops_CISIR;
				if (text->count > 0) {
					HI_Edit_Text (context, text, 0, 0, 0, text->count, 0, null);
				}
				goto Release;
			}	/* _hoops_IHSA; */
		}
	}

	HE_ERROR (HEC_INVALID_KEY, HES_INVALID_GEOMETY_OR_SEGMENT,
			"Key does not refer to a valid segment, polyline, polygon, or text");

Release:
	_hoops_IRRPR();
#endif
}

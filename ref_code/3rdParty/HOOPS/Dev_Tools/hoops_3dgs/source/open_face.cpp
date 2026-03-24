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
 * $Id: obf_tmp.txt 1.55 2010-10-06 19:15:59 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


HC_INTERFACE void HC_CDECL HC_Open_Face (
	int					offset)
{
	_hoops_PAPPR context("Open_Face");

#ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_D (null, "HC_Open_Face (%d);\n", offset));
		HOOPS_WORLD->_hoops_ISPPR += 2;
	);

	_hoops_SIRIR *	_hoops_RGGGC;

	if (context->open_list == null) {
		HE_ERROR (HEC_FACE, HES_OPEN_GEOMETRY_FIRST, "Must 'Open_Geometry' first");
		return;
	}
	if (context->open_list->_hoops_GCRIR != _hoops_HCRIR) {
		HE_ERROR (HEC_FACE, HES_INVALID_INPUT, "Most recent 'Open' was not an 'Open_Geometry'");
		return;
	}

	Polyhedron *	_hoops_IPRI = (Polyhedron *)context->open_list->info.geometry._hoops_IGRPR;

	switch (_hoops_IPRI->type) {
		case _hoops_GSIP: {
			_hoops_AIHPR *			_hoops_PIHPR = (_hoops_AIHPR *)_hoops_IPRI;
			int				row,
							column;
			char			buf[MAX_ERRMSG];

			if (BIT (HOOPS_WORLD->system_flags, _hoops_GGSPP)) {
				if (offset >= 0) {
					row = offset / _hoops_PIHPR->columns;
					column = offset - row * _hoops_PIHPR->columns;

					if (row >= _hoops_PIHPR->rows - 1 ||
						column >= _hoops_PIHPR->columns - 1) {
						HE_ERROR2 (HEC_FACE, HES_INVALID_OFFSET,
							Sprintf_DD (null, "A 'positive' face at row %d, column %d",row, column),
							Sprintf_DD (buf, "is not within a %d x %d mesh.", _hoops_PIHPR->rows, _hoops_PIHPR->columns));
						return;
					}

					/* _hoops_GCSS _hoops_GAGHR-_hoops_HPP-_hoops_GAGHR */
					offset = (row*(_hoops_PIHPR->columns - 1) + column)*2;
				}
				else /* _hoops_SHI < 0 */ {
					row = (-offset) / _hoops_PIHPR->columns;
					column = (-offset) - row * _hoops_PIHPR->columns;

					if (row >= _hoops_PIHPR->rows ||
						column >= _hoops_PIHPR->columns ||
						row == 0 || column == 0) {
						HE_ERROR2 (HEC_FACE, HES_INVALID_OFFSET,
							Sprintf_DD (null, "A 'negative' face at row %d, column %d",row, column),
							Sprintf_DD (buf, "is not within a %d x %d mesh.",_hoops_PIHPR->rows, _hoops_PIHPR->columns));
						return;
					}

					/* _hoops_GCSS _hoops_GAGHR-_hoops_HPP-_hoops_GAGHR */
					offset = ((row - 1)*(_hoops_PIHPR->columns - 1) + (column - 1))*2 + 1;
				}
			}
			else {
				if (offset < 0 || offset >= (_hoops_PIHPR->rows-1)*(_hoops_PIHPR->columns-1)*2) {
					HE_ERROR2 (HEC_FACE, HES_INVALID_OFFSET,
						Sprintf_D (null, "A face offset of %d", offset),
						Sprintf_DD (buf, "is not within a %d x %d mesh.",_hoops_PIHPR->rows, _hoops_PIHPR->columns));
					return;
				}
			}
		}	break;

		case _hoops_SCIP: {
			if (offset >= _hoops_IPRI->face_count || offset < 0) {
				HE_ERROR (HEC_FACE, HES_INVALID_OFFSET,
						Sprintf_DD (null,"Can't open face '%d' - shell has only %d faces",offset, _hoops_IPRI->face_count));
				return;
			}
		}	break;

		case _hoops_CSIP: {
			if (offset > 1 || offset < 0) {
				HE_ERROR (HEC_FACE, HES_INVALID_OFFSET,
						Sprintf_D (null,"Can't open face '%d' - may only access start (0) or end (1) face",offset));
				return;
			}
		}	break;

		default: {
			HE_ERROR (HEC_FACE, HES_TRISTRIP_ONLY,"Can only 'Open_Face' within an open Shell, Mesh, or PolyCylinder");
			return;
		}		/* _hoops_IHSA; */
	}

	ZALLOC (_hoops_RGGGC, _hoops_SIRIR);
	_hoops_RGGGC->type = _hoops_CIRIR;
	_hoops_RGGGC->_hoops_HIHI = 1;
	_hoops_RGGGC->owner = HOOPS_WORLD;
	_hoops_RGGGC->_hoops_GCRIR = _hoops_ICRIR;

	/* _hoops_AGCR _hoops_IHRI _hoops_RPP _hoops_RSRRA */
	_hoops_RGGGC->info._hoops_IPRI._hoops_IGRPR = _hoops_IPRI;
	_hoops_PRRH (_hoops_IPRI);
	_hoops_RGGGC->info._hoops_IPRI.offset = offset;

	_hoops_IPAPP(context, _hoops_RGGGC);

#endif
}


HC_INTERFACE void HC_CDECL HC_Close_Face (void)
{
	_hoops_PAPPR context("Close_Face");

#ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
#else
	CODE_GENERATION (
		HOOPS_WORLD->_hoops_ISPPR -= 2;
		HI_Dump_Code ("HC_Close_Face ();\n");
	);

	_hoops_SIRIR *	_hoops_AHSCA = context->open_list;
	if (_hoops_AHSCA == null || _hoops_AHSCA->_hoops_GCRIR != _hoops_ICRIR) {
		HI_Close_Complaint (context, _hoops_ICRIR);
		return;
	}

	/* _hoops_IPCA */
	_hoops_CIGPR (context,_hoops_AHSCA);
	_hoops_HPRH (_hoops_AHSCA);

	/* _hoops_SGS _hoops_CSAP _hoops_CAHPH */

	/* _hoops_IRS _hoops_PGHC _hoops_SSHHC _hoops_III _hoops_SIAS _hoops_HS _hoops_RIPPR, _hoops_HIS _hoops_SAHR _hoops_PCHIA _hoops_SCH */
	_hoops_AHSCA = context->open_list;
	if (_hoops_AHSCA != null && _hoops_AHSCA->_hoops_GCRIR == _hoops_RCRIR && _hoops_AHSCA->info.segment._hoops_ACRIR != null) {
		_hoops_HPRH (_hoops_AHSCA->info.segment._hoops_ACRIR);
		_hoops_AHSCA->info.segment._hoops_ACRIR = null;
	}
#endif
}



HC_INTERFACE void HC_CDECL HC_Open_Region (
	int					offset)
{
	_hoops_PAPPR context("Open_Region");

#ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_D (null, "HC_Open_Region (%d);\n", offset));
		HOOPS_WORLD->_hoops_ISPPR += 2;
	);

	if (context->open_list == null) {
		HE_ERROR (HEC_FACE, HES_OPEN_GEOMETRY_FIRST, "Must 'Open_Geometry' first");
		return;
	}
	if (context->open_list->_hoops_GCRIR != _hoops_HCRIR) {
		HE_ERROR (HEC_FACE, HES_INVALID_INPUT, "Most recent 'Open' was not an 'Open_Geometry'");
		return;
	}

	Polyhedron *	_hoops_IPRI = (Polyhedron *)context->open_list->info.geometry._hoops_IGRPR;

	switch (_hoops_IPRI->type) {
		case _hoops_GSIP: {
		}	break;

		case _hoops_SCIP: {
		}	break;

		default: {
			HE_ERROR (HEC_FACE, HES_TRISTRIP_ONLY, "Can only 'Open_Region' within an open Shell or Mesh");
			return;
		}		/* _hoops_IHSA; */
	}

	_hoops_SIRIR *	_hoops_RGGGC;
	ZALLOC (_hoops_RGGGC, _hoops_SIRIR);
	_hoops_RGGGC->type = _hoops_CIRIR;
	_hoops_RGGGC->_hoops_HIHI = 1;
	_hoops_RGGGC->owner = HOOPS_WORLD;
	_hoops_RGGGC->_hoops_GCRIR = _hoops_GSRIR;

	_hoops_RGGGC->info._hoops_IPRI._hoops_IGRPR = _hoops_IPRI;
	_hoops_PRRH (_hoops_IPRI);
	_hoops_RGGGC->info._hoops_IPRI.offset = offset;

	_hoops_IPAPP(context, _hoops_RGGGC);

#endif
}


HC_INTERFACE void HC_CDECL HC_Close_Region (void)
{
	_hoops_PAPPR context("Close_Region");

#ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
#else
	CODE_GENERATION (
		HOOPS_WORLD->_hoops_ISPPR -= 2;
		HI_Dump_Code ("HC_Close_Region ();\n");
	);

	_hoops_SIRIR *	_hoops_AHSCA = context->open_list;
	if (_hoops_AHSCA == null || _hoops_AHSCA->_hoops_GCRIR != _hoops_GSRIR) {
		HI_Close_Complaint (context, _hoops_GSRIR);
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
#endif
}

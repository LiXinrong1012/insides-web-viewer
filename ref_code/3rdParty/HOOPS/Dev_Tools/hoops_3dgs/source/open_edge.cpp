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
 * $Id: obf_tmp.txt 1.60 2010-10-06 19:16:00 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

#ifndef DISABLE_GEOMETRY_ATTRIBUTES

local int _hoops_ASHHC (
	Polyhedron	*_hoops_IPRI,
	int				_hoops_PSHHC,
	int				_hoops_HSHHC) {

	switch (_hoops_IPRI->type) {
		default: {
			HE_ERROR (HEC_EDGE, HES_OPEN_GEOMETRY,
					"An 'Open_Edge' requires an already-open shell or mesh");
		}	break;

		case _hoops_GSIP: {
			_hoops_AIHPR const *		_hoops_PIHPR = (_hoops_AIHPR const *)_hoops_IPRI;
			int					_hoops_HIHHA, _hoops_AIGCR,
								_hoops_PIAIA, _hoops_PIGCR;
			char				buf1[MAX_ERRMSG],
								buf2[MAX_ERRMSG];

			_hoops_HIHHA = _hoops_PSHHC / _hoops_PIHPR->columns;
			_hoops_AIGCR = _hoops_PSHHC - _hoops_HIHHA * _hoops_PIHPR->columns;

			_hoops_PIAIA = _hoops_HSHHC / _hoops_PIHPR->columns;
			_hoops_PIGCR = _hoops_HSHHC - _hoops_PIAIA * _hoops_PIHPR->columns;

			if (_hoops_HIHHA < _hoops_PIHPR->rows && _hoops_AIGCR < _hoops_PIHPR->columns &&
				_hoops_PIAIA < _hoops_PIHPR->rows && _hoops_PIGCR < _hoops_PIHPR->columns) {
				if (_hoops_HIHHA == _hoops_PIAIA) {					/* _hoops_GGCPR */
					if (_hoops_AIGCR + 1 == _hoops_PIGCR)			/* _hoops_RGCPR _hoops_IS _hoops_RH _hoops_RPHR */
						return 3 * _hoops_PSHHC;
				}
				else if (_hoops_HIHHA + 1 == _hoops_PIAIA) {		/* _hoops_AGCPR */
					if (_hoops_AIGCR == _hoops_PIGCR)
						return 3 * _hoops_PSHHC + 1;	/* _hoops_RGCPR _hoops_AGCPR */
					else if (_hoops_AIGCR - 1 == _hoops_PIGCR)
						return 3 * _hoops_PSHHC + 2;	/* _hoops_GH _hoops_PPR _hoops_IS _hoops_RH _hoops_RAAP */
				}
			}

			HE_ERROR3 (HEC_EDGE, HES_INVALID_OFFSET,

				Sprintf_DD (null, "No direct edge from row offset %d, column %d", _hoops_HIHHA, _hoops_AIGCR),
				Sprintf_DD (buf1, "to row %d, column %d, exists.", _hoops_PIAIA, _hoops_PIGCR),
				Sprintf_DD (buf2, "(The mesh is %d x %d.)",
							_hoops_PIHPR->rows, _hoops_PIHPR->columns));
		}	break;

		case _hoops_SCIP: {
			Shell const *		_hoops_SPHPR = (Shell const *)_hoops_IPRI;
			_hoops_RHHPR	*_hoops_SRCPR;
			_hoops_RHHPR	*_hoops_ISHHC;
			int					_hoops_CSHHC = _hoops_HSHHC;

			if (_hoops_SPHPR->_hoops_GRCPR == null)
				HI_Create_Shell_Edges ((Shell *)_hoops_IPRI, false);

			_hoops_SRCPR	   = _hoops_SPHPR->_hoops_HHHPR[_hoops_PSHHC];
			_hoops_ISHHC = _hoops_SPHPR->_hoops_HHHPR[_hoops_PSHHC + 1];

			_hoops_RGGA (_hoops_SRCPR == _hoops_ISHHC) {
				/* _hoops_RPP _hoops_RGR _hoops_HRGR _hoops_RH _hoops_RPHR _hoops_PASPR */
				if (_hoops_SRCPR->_hoops_GIHPR == _hoops_CSHHC) {
					/*
					 * _hoops_IPCP " - " _hoops_GGR _hoops_RH _hoops_SPS _hoops_CRHRH _hoops_GRS _hoops_PAHH _hoops_PGSAH
					 * _hoops_GPP _hoops_CHPP _hoops_SCHS _hoops_GPP 16-_hoops_IGRH-_hoops_SCSH _hoops_IACAR.
					 */
					return _hoops_SRCPR - _hoops_SPHPR->_hoops_GRCPR;
				}

				++_hoops_SRCPR;
			}

			HE_ERROR (HEC_EDGE, HES_INVALID_OFFSET,
					Sprintf_DD (null,
				"This shell has no edge between vertex %d and %d", _hoops_PSHHC, _hoops_HSHHC));
		}	break;
	}

	return (-1);
}

#endif

HC_INTERFACE void HC_CDECL HC_Open_Edge (
	int						_hoops_PSHHC,
	int						_hoops_HSHHC)
{
	_hoops_PAPPR context("Open_Edge");

#ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_DD (null, "HC_Open_Edge (%d, %d);\n",
								  _hoops_PSHHC, _hoops_HSHHC));
		HOOPS_WORLD->_hoops_ISPPR += 2;
	);

	_hoops_SIRIR *		_hoops_RGGGC;
	int				offset;

	if (context->open_list == null) {
		HE_ERROR (HEC_EDGE, HES_OPEN_GEOMETRY_FIRST, "Must 'Open_Geometry' first");
		return;
	}
	if (context->open_list->_hoops_GCRIR != _hoops_HCRIR) {
		HE_ERROR (HEC_EDGE, HES_INVALID_OPEN, "Most recent 'Open' was not an 'Open_Geometry'");
		return;
	}

	/* _hoops_AGR _hoops_RH _hoops_GIHA */
	if (_hoops_PSHHC > _hoops_HSHHC) {
		int		tmp = _hoops_PSHHC;
		_hoops_PSHHC = _hoops_HSHHC;
		_hoops_HSHHC = tmp;
	}

	Polyhedron *	_hoops_IPRI = (Polyhedron *)context->open_list->info.geometry._hoops_IGRPR;

	if (_hoops_PSHHC >= _hoops_IPRI->point_count || _hoops_PSHHC < 0) {
		HI_Vertex_Complaint (_hoops_PSHHC, _hoops_IPRI);
		return;
	}

	if (_hoops_HSHHC >= _hoops_IPRI->point_count || _hoops_HSHHC < 0) {
		HI_Vertex_Complaint (_hoops_HSHHC, _hoops_IPRI);
		return;
	}

	if ((offset = _hoops_ASHHC (_hoops_IPRI, _hoops_PSHHC, _hoops_HSHHC)) < 0)
		return;

	ZALLOC (_hoops_RGGGC, _hoops_SIRIR);
	_hoops_RGGGC->type = _hoops_CIRIR;
	_hoops_RGGGC->_hoops_HIHI = 1;
	_hoops_RGGGC->owner = HOOPS_WORLD;
	_hoops_RGGGC->_hoops_GCRIR = _hoops_CCRIR;

	_hoops_RGGGC->info._hoops_IPRI._hoops_IGRPR = _hoops_IPRI;
	_hoops_PRRH (_hoops_IPRI);
	_hoops_RGGGC->info._hoops_IPRI.offset = offset;

	_hoops_IPAPP(context, _hoops_RGGGC);

#endif
}


HC_INTERFACE void HC_CDECL HC_Close_Edge (void)
{
	_hoops_PAPPR context("Close_Edge");

#ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
#else
	CODE_GENERATION (
		HOOPS_WORLD->_hoops_ISPPR -= 2;
		HI_Dump_Code ("HC_Close_Edge ();\n");
	);

	_hoops_SIRIR *	_hoops_AHSCA = context->open_list;
	if (_hoops_AHSCA == null || _hoops_AHSCA->_hoops_GCRIR != _hoops_CCRIR) {
		HI_Close_Complaint (context, _hoops_CCRIR);
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


HC_INTERFACE void HC_CDECL HC_MSet_Specific_Edge_Vis (
	Key				key,
	int				count,
	int const *		indices1,
	int const *		indices2,
	char const *	_hoops_IPGCI)
{
	_hoops_PAPPR context("MSet_Specific_Edge_Visibilities");

	unsigned char const *	visibilities = (unsigned char const *)_hoops_IPGCI;

#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#else

	CODE_GENERATION (
		int		count2 = count;
		if (count == 0) {
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Specific_Edge_Visibilities (LOOKUP (%D), 0, 0, 0);\n", key));
		}
		else {
			HI_Dump_Code (Sprintf_D (null, "{char visibilities[%d];\n", count2));
			HI_Dump_Code (Sprintf_D (null, " int indices1[%d];\n", count2));
			HI_Dump_Code (Sprintf_D (null, " int indices2[%d];\n", count2));
			++HOOPS_WORLD->_hoops_ISPPR;
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (Sprintf_DD (null, "visibilities[%d] = %f;\n", count2, visibilities[count2]));
				HI_Dump_Code (Sprintf_DD (null, "indices1[%d] = %f;\n", count2, indices1[count2]));
				HI_Dump_Code (Sprintf_DD (null, "indices2[%d] = %f;\n", count2, indices2[count2]));
			}
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Specific_Edge_Visibilities (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_D (null, "%d, indices1, indices2, visibilities);}\n", count));
			--HOOPS_WORLD->_hoops_ISPPR;
		}
	);


	_hoops_GHHPR *		flags;
	_hoops_RPGHR *	lea;
	int						offset;
	bool					erase = false;

	_hoops_RPPPR();

	Polyhedron *	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (context, key);

	if (_hoops_IPRI == null ||
		(_hoops_IPRI->type != _hoops_SCIP && _hoops_IPRI->type != _hoops_GSIP) ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_COLOR, HES_INVALID_KEY, "Key does not refer to a valid Shell or Mesh");
		goto Release;
	}

	if (count == 0)
		goto Release;  /* _hoops_CPRSH */
	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		goto Release;
	}

	lea = &_hoops_IPRI->_hoops_IHHPR;
	if (lea->flags == null)
		HI_Initialize_Edge_Attributes(_hoops_IPRI, 0);
	flags = lea->flags;

	do {
		unsigned char			_hoops_RGP = *visibilities++;
		int						_hoops_ISPI = *indices1++;
		int						_hoops_CSPI = *indices2++;

		if (_hoops_ISPI > _hoops_CSPI) {
			int		tmp = _hoops_ISPI;
			_hoops_ISPI = _hoops_CSPI;
			_hoops_CSPI = tmp;
		}

		/* _hoops_HHHR _hoops_AIRP _hoops_CHR _hoops_PHHS _hoops_HPSH */
		if (_hoops_ISPI<0 || _hoops_CSPI<0)
			continue;

		if (_hoops_ISPI >= _hoops_IPRI->point_count) {
			HI_Vertex_Complaint (_hoops_ISPI, _hoops_IPRI);
			goto Release;
		}

		if (_hoops_CSPI >= _hoops_IPRI->point_count) {
			HI_Vertex_Complaint (_hoops_CSPI, _hoops_IPRI);
			goto Release;
		}

		if ((offset = _hoops_ASHHC (_hoops_IPRI, _hoops_ISPI, _hoops_CSPI)) < 0)
			continue;

		if (_hoops_RGP) { /* _hoops_IAHAR _hoops_SCH _hoops_GPP */
			if (!BIT (flags[offset], _hoops_APGI)) {
				if (BIT (flags[offset], _hoops_AHIAA)) {
					flags[offset] &= ~_hoops_AHIAA;
					--lea->_hoops_SIIPR;
				}
				flags[offset] |= _hoops_APGI;
				++lea->_hoops_CPIAA;
			}
		}
		else {
			if (!BIT (flags[offset], _hoops_AHIAA)) {
				if (BIT (flags[offset], _hoops_APGI)) {
					flags[offset] &= ~_hoops_APGI;
					--lea->_hoops_CPIAA;
				}
				flags[offset] |= _hoops_AHIAA;
				++lea->_hoops_SIIPR;
				erase = true;
			}
		}
	} _hoops_RGGA (--count == 0);

	if (erase)
		_hoops_SASIR (context, _hoops_IPRI, _hoops_AISSR | _hoops_RPSIR);
	else
		_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR | _hoops_RPSIR);

  Release:
	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_MShow_Specific_Edge_Vis (
	Key				key,
	int				count,
	int const *		indices1,
	int const *		indices2,
	char alter *	_hoops_IPGCI)
{
	_hoops_PAPPR context("MShow_Specific_Edge_Visibilities");

	unsigned char alter *	visibilities = (unsigned char alter *) _hoops_IPGCI;

#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#else

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Specific_Edge_Visibilities () */\n");
	);

	_hoops_GHHPR	*flags;
	_hoops_RPGHR *lea;
	int					_hoops_ISPI, _hoops_CSPI;
	int					offset;
	int					_hoops_HAHC=count;
	int const *			save_indices1 = indices1;
	int const *			save_indices2 = indices2;

	_hoops_CSPPR();

	Polyhedron *	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (context, key);

	if (_hoops_IPRI == null ||
		(_hoops_IPRI->type != _hoops_SCIP && _hoops_IPRI->type != _hoops_GSIP) ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_COLOR, HES_INVALID_KEY, "Key does not refer to a valid Shell or Mesh");
		goto Release;
	}

	if (count == 0)
		goto Release;  /* _hoops_CPRSH */
	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		goto Release;
	}

	lea = &_hoops_IPRI->_hoops_IHHPR;

	if ((flags = lea->flags) == null) {
		HE_ERROR (HEC_NORMAL, HES_NO_LOCAL_SETTING, "No edge visibilities are explicitly set here");
		goto Release;
	}

	do {
		_hoops_ISPI = *indices1++;
		_hoops_CSPI = *indices2++;

		if (_hoops_ISPI > _hoops_CSPI) {
			int		tmp = _hoops_ISPI;
			_hoops_ISPI = _hoops_CSPI;
			_hoops_CSPI = tmp;
		}

		if (_hoops_ISPI<0 || _hoops_CSPI<0) {
			HE_ERROR (HEC_NORMAL, HES_NO_LOCAL_SETTING, "One or more negative vertex values.");
			goto Release;
		}

		if (_hoops_ISPI >= _hoops_IPRI->point_count) {
			HI_Vertex_Complaint (_hoops_ISPI, _hoops_IPRI);
			goto Release;
		}

		if (_hoops_CSPI >= _hoops_IPRI->point_count) {
			HI_Vertex_Complaint (_hoops_CSPI, _hoops_IPRI);
			goto Release;
		}

		if ((offset = _hoops_ASHHC (_hoops_IPRI, _hoops_ISPI, _hoops_CSPI)) < 0) {
			HE_ERROR (HEC_NORMAL, HES_NO_LOCAL_SETTING, "Invalid edge specified.");
			goto Release;
		}

		if (!ANYBIT (flags[offset], _hoops_ICICA)) {
			HE_ERROR (HEC_NORMAL, HES_NO_LOCAL_SETTING,
					  "Not all edge visibilities are explicitly set in the specified range");
			goto Release;
		}
	} _hoops_RGGA (--count == 0);


	indices1=save_indices1;
	indices2=save_indices2;
	count=_hoops_HAHC;

	do {
		_hoops_ISPI = *indices1++;
		_hoops_CSPI = *indices2++;

		if (_hoops_ISPI > _hoops_CSPI) {
			int		tmp = _hoops_ISPI;
			_hoops_ISPI = _hoops_CSPI;
			_hoops_CSPI = tmp;
		}
		offset = _hoops_ASHHC (_hoops_IPRI, _hoops_ISPI, _hoops_CSPI);
		*visibilities++ = BIT (flags[offset], _hoops_APGI);
	} _hoops_RGGA (--count == 0);


  Release:
	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_MUnSet_Specific_Edge_Vis (
	Key				key,
	int				count,
	int const *		indices1,
	int const *		indices2)
{
	_hoops_PAPPR context("MUnSet_Specific_Edge_Visibilities");

#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#else

	CODE_GENERATION (
		int		count2 = count;
		if (count == 0) {
			HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Specific_Edge_Visibilities (LOOKUP (%D), 0, 0, 0);\n", key));
		}
		else {
			HI_Dump_Code (Sprintf_D (null, " int indices1[%d];\n", count2));
			HI_Dump_Code (Sprintf_D (null, " int indices2[%d];\n", count2));
			++HOOPS_WORLD->_hoops_ISPPR;
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (Sprintf_DD (null, "indices1[%d] = %f;\n", count2, indices1[count2]));
				HI_Dump_Code (Sprintf_DD (null, "indices2[%d] = %f;\n", count2, indices2[count2]));
			}
			HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Specific_Edge_Visibilities (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_D (null, "%d, indices1, indices2);}\n", count));
			--HOOPS_WORLD->_hoops_ISPPR;
		}
	);

	_hoops_GHHPR	*flags;
	_hoops_RPGHR *lea;
	int					_hoops_ISPI, _hoops_CSPI;
	int					offset;
	bool				erase = false;
	bool				_hoops_AHPGR = false;
	int					_hoops_HAHC = count;
	int const			*save_indices1 = indices1;
	int const			*save_indices2 = indices2;

	_hoops_RPPPR();

	Polyhedron *	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (context, key);

	if (_hoops_IPRI == null ||
		(_hoops_IPRI->type != _hoops_SCIP && _hoops_IPRI->type != _hoops_GSIP) ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_COLOR, HES_INVALID_KEY, "Key does not refer to a valid Shell or Mesh");
		goto Release;
	}

	if (count == 0)
		goto Release;  /* _hoops_CPRSH */
	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		goto Release;
	}

	lea = &_hoops_IPRI->_hoops_IHHPR;
	if ((flags = lea->flags) == null) {
		/* _hoops_ISAP _hoops_ARP _hoops_RPP _hoops_PSP _hoops_SGI, _hoops_HIS _hoops_SAHR _hoops_PSIIR & _hoops_CASI _hoops_GH */
		HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");
		goto Release;
	}


	do {
		_hoops_ISPI = *indices1++;
		_hoops_CSPI = *indices2++;

		if (_hoops_ISPI > _hoops_CSPI) {
			int		tmp = _hoops_ISPI;
			_hoops_ISPI = _hoops_CSPI;
			_hoops_CSPI = tmp;
		}

		if (_hoops_ISPI<0 || _hoops_CSPI<0) {
			HE_ERROR (HEC_NORMAL, HES_NO_LOCAL_SETTING, "One or more negative vertex values.");
			goto Release;
		}

		if (_hoops_ISPI >= _hoops_IPRI->point_count) {
			HI_Vertex_Complaint (_hoops_ISPI, _hoops_IPRI);
			goto Release;
		}

		if (_hoops_CSPI >= _hoops_IPRI->point_count) {
			HI_Vertex_Complaint (_hoops_CSPI, _hoops_IPRI);
			goto Release;
		}

		if ((offset = _hoops_ASHHC (_hoops_IPRI, _hoops_ISPI, _hoops_CSPI)) < 0) {
			HE_ERROR (HEC_NORMAL, HES_NO_LOCAL_SETTING, "Invalid edge specified.");
			goto Release;
		}
	} _hoops_RGGA (--count == 0);


	indices1=save_indices1;
	indices2=save_indices2;
	count=_hoops_HAHC;

	do {
		_hoops_ISPI = *indices1++;
		_hoops_CSPI = *indices2++;

		if (_hoops_ISPI > _hoops_CSPI) {
			int		tmp = _hoops_ISPI;
			_hoops_ISPI = _hoops_CSPI;
			_hoops_CSPI = tmp;
		}

		offset = _hoops_ASHHC (_hoops_IPRI, _hoops_ISPI, _hoops_CSPI);

		if (BIT (flags[offset], _hoops_AHIAA)) {
			flags[offset] &= ~_hoops_AHIAA;
			--lea->_hoops_SIIPR;
		}
		else if (BIT (flags[offset], _hoops_APGI)) {
			flags[offset] &= ~_hoops_APGI;
			--lea->_hoops_CPIAA;
			erase = true; /* _hoops_CPIC _hoops_HII '_hoops_GPP' _hoops_IS '_hoops_RHGC' _hoops_SIAS _hoops_HA _hoops_CAPGP '_hoops_PSAP' */
		}
		else
			_hoops_AHPGR=true;
	} _hoops_RGGA (--count == 0);

	if (_hoops_AHPGR)
		HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");

	if (_hoops_IPRI->tristrips != null) {
		_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;

		if (erase)
			_hoops_SASIR (context, _hoops_IPRI, _hoops_AISSR|_hoops_CSCCA|_hoops_RPSIR);
		else
			_hoops_SASIR (context, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
	}

  Release:
	_hoops_IRRPR();
#endif
}



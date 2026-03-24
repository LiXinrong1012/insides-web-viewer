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
 * $Id: obf_tmp.txt 1.39 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


local void _hoops_HRARS (
	Polyhedron	*_hoops_IPRI) {
	int				*regions;

	ZALLOC_ARRAY (regions, _hoops_IPRI->face_count +_hoops_SHHIR, int);
	/* _hoops_PRGSI _hoops_ISPH _hoops_CCIR */
	regions[_hoops_IPRI->face_count + _hoops_GISCC] = 0;

	_hoops_IPRI->local_face_attributes.regions = regions;
}

/* _hoops_SIGP: _hoops_HGI _hoops_PAH _hoops_SHH _hoops_RHSI _hoops_SR _hoops_IRARS _hoops_RHHSR _hoops_RH _hoops_HISAR/_hoops_CASH _hoops_CIHA */
local void _hoops_CRARS (
	Polyhedron	*_hoops_IPRI) {
	int				*regions = _hoops_IPRI->local_face_attributes.regions;
	int				count = _hoops_IPRI->face_count;
	int				low, high;

	if (regions == null)
		return;

	low = high = *regions++;
	while (--count > 0) {
		int			region = *regions++;

		if (region < low)
			low = region;
		else if (region > high)
			high = region;
	}
	*regions++ = low;
	*regions++ = high;
	*regions++ = ~0;
}


HC_INTERFACE void HC_CDECL HC_Set_Faces (
	int						first,
	int						count)
{
	_hoops_PAPPR context("Set_Faces");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_DD (null, "HC_Set_Faces (%d, %d);\n", first, count));
	);

	if (context->open_list == null) {
		HE_ERROR (HEC_REGION, HES_OPEN_GEOMETRY_FIRST,"Must 'Open_Region' first");
		return;
	}
	if (context->open_list->_hoops_GCRIR != _hoops_GSRIR) {
		HE_ERROR (HEC_REGION, HES_INVALID_INPUT, "Most recent 'Open' was not an 'Open_Region'");
		return;
	}

	_hoops_CSPPR();

	Polyhedron *	_hoops_IPRI = (Polyhedron *)context->open_list->info._hoops_IPRI._hoops_IGRPR;
	int	region = context->open_list->info._hoops_IPRI.offset;

	if (first < 0 || count < 0) {
		HE_ERROR (HEC_REGION, HES_INVALID_NUMBER, "The first face offset or face count is negative");
	}
	else if (first + count > _hoops_IPRI->face_count) {
		char			buf[MAX_ERRMSG];

		HE_ERROR2 (HEC_REGION, HES_INVALID_OFFSET,
				Sprintf_DD (null,"Can't set as many as %d faces at offset %d -",count, first),
				   Sprintf_D (buf, "the Shell or Mesh only has %d", _hoops_IPRI->face_count));
	}
	else if (_hoops_IPRI->local_face_attributes.regions == null &&
			region == 0) {
		/* _hoops_RSSI _hoops_CHR _hoops_IHPPR _hoops_ISPH 0 _hoops_APIC... */
	}
	else {
		if (_hoops_IPRI->local_face_attributes.regions == null)
			_hoops_HRARS (_hoops_IPRI);

		int alter *	regions = _hoops_IPRI->local_face_attributes.regions;
		regions[_hoops_IPRI->face_count + _hoops_GISCC] = 0;
		regions = _hoops_IPRI->local_face_attributes.regions + first;

		bool	_hoops_RGHIR = false;

		if (*(_hoops_IPRI->local_face_attributes._hoops_CHHPR()) != 0) {
			_hoops_GIIPR *	flags;

			flags = _hoops_IPRI->local_face_attributes._hoops_CHHPR(first);
			while (count-- > 0) {
				if (*regions != region && ANYBIT (*flags, _hoops_PHGPR))
					_hoops_RGHIR = true;
				*regions++ = region;
				if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR))
					flags++;
			}
		}
		else {
			while (count-- > 0)
				*regions++ = region;
		}

		/*_hoops_SRARS (_hoops_CPHAR);*/

		if (_hoops_IPRI->type == _hoops_SCIP &&
			_hoops_IPRI->tristrips != null && _hoops_RGHIR)
			_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;
	}
	_hoops_IRRPR();
}



HC_INTERFACE void HC_CDECL HC_Set_Region (
	int						region)
{
	_hoops_PAPPR context("Set_Region");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_D (null, "HC_Set_Region (%d);\n", region));
	);

	if (context->open_list == null) {
		HE_ERROR (HEC_FACE, HES_OPEN_GEOMETRY_FIRST, "Must 'Open_Face' first");
		return;
	}
	if (context->open_list->_hoops_GCRIR != _hoops_ICRIR) {
		HE_ERROR (HEC_FACE, HES_INVALID_INPUT, "Most recent 'Open' was not an 'Open_Face'");
		return;
	}

	_hoops_RPPPR();
	Polyhedron *	_hoops_IPRI = (Polyhedron *)context->open_list->info._hoops_IPRI._hoops_IGRPR;
	int	offset = context->open_list->info._hoops_IPRI.offset;

	if (_hoops_IPRI->local_face_attributes.regions == null) {
		if (region == 0) {
			_hoops_IRRPR();
			return;				/* _hoops_HSP _hoops_HRGR _hoops_IHPPR _hoops_ISPH 0 _hoops_APIC... */
		}

		_hoops_HRARS (_hoops_IPRI);
	}

	int alter *	regions = _hoops_IPRI->local_face_attributes.regions;
	regions[_hoops_IPRI->face_count + _hoops_GISCC] = 0;
	regions = _hoops_IPRI->local_face_attributes.regions + offset;

	bool	_hoops_RGHIR = false;

	if (*_hoops_IPRI->local_face_attributes._hoops_CHHPR() != 0) {
		_hoops_GIIPR *	flags;

		flags = _hoops_IPRI->local_face_attributes._hoops_CHHPR(offset);
		if (*regions != region && ANYBIT (*flags, _hoops_PHGPR))
			_hoops_RGHIR = true;
	}
	*regions = region;

	/*_hoops_SRARS (_hoops_CPHAR);*/

	if (_hoops_IPRI->type == _hoops_SCIP &&
		_hoops_IPRI->tristrips != null && _hoops_RGHIR)
		_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;

	_hoops_IRRPR();
}



HC_INTERFACE void HC_CDECL HC_MSet_Region_Faces (
	Key					key,
	int					region,
	int					first,
	int					count)
{
	_hoops_PAPPR context("MSet_Region_Faces");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Region_Faces (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_D (null, "%d, ", region));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d);\n", first, count));
	);


	_hoops_RPPPR();

	Polyhedron *	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (context, key);

	if (_hoops_IPRI == null ||
		(_hoops_IPRI->type != _hoops_SCIP && _hoops_IPRI->type != _hoops_GSIP) ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_REGION, HES_INVALID_KEY, "Key does not refer to a valid Shell or Mesh");
	}
	else if (first < 0 || count < 0) {
		HE_ERROR (HEC_REGION, HES_INVALID_NUMBER, "The first face offset or face count is negative");
	}
	else if (first + count > _hoops_IPRI->face_count) {
		char			buf[MAX_ERRMSG];
		HE_ERROR2 (HEC_REGION, HES_INVALID_OFFSET,
				Sprintf_DD (null, "Can't set as many as %d faces at offset %d -", count, first),
				   Sprintf_D (buf, "the Shell or Mesh only has %d", _hoops_IPRI->face_count));
	}
	else if (_hoops_IPRI->local_face_attributes.regions == null &&
		region == 0) {
		/* _hoops_RSSI _hoops_CHR _hoops_IHPPR _hoops_ISPH 0 _hoops_APIC... */
	}
	else {
		if (_hoops_IPRI->local_face_attributes.regions == null)
			_hoops_HRARS (_hoops_IPRI);

		int alter *	regions = _hoops_IPRI->local_face_attributes.regions;
		regions[_hoops_IPRI->face_count + _hoops_GISCC] = 0;
		regions = _hoops_IPRI->local_face_attributes.regions + first;

		bool	_hoops_RGHIR = false;

		if (*_hoops_IPRI->local_face_attributes._hoops_CHHPR() != 0) {
			_hoops_GIIPR *	flags;

			flags = _hoops_IPRI->local_face_attributes._hoops_CHHPR(first);
			while (count-- > 0) {
				if (*regions != region && ANYBIT (*flags, _hoops_PHGPR))
					_hoops_RGHIR = true;
				*regions++ = region;
				if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR))
					flags++;
			}
		}
		else {
			while (count-- > 0)
				*regions++ = region;
		}

		/*_hoops_SRARS (_hoops_CPHAR);*/

		if (_hoops_IPRI->type == _hoops_SCIP &&
			_hoops_IPRI->tristrips != null && _hoops_RGHIR)
			_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;
	}

	_hoops_IRRPR();
}



HC_INTERFACE void HC_CDECL HC_MSet_Face_Regions (
	Key					key,
	int					first,
	int					count,
	int const *			in_regions)
{
	_hoops_PAPPR context("MSet_Face_Regions");

	CODE_GENERATION (
		int		count2 = count;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "int* regions = (int*) malloc(sizeof(int)*%d);\n", count2));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "regions[%d] = %d;\n", count2, in_regions[count2]));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Face_Regions (LOOKUP (%D), ",key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, regions);\n", first, count));
		HI_Dump_Code ("free (regions);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);


	_hoops_RPPPR();

	Polyhedron *	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (context, key);

	if (_hoops_IPRI == null ||
		(_hoops_IPRI->type != _hoops_SCIP && _hoops_IPRI->type != _hoops_GSIP) ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_REGION, HES_INVALID_KEY,"Key does not refer to a valid Shell or Mesh");
	}
	else if (first < 0 || count < 0) {
		HE_ERROR (HEC_REGION, HES_INVALID_NUMBER,"The first face offset or face count is negative");
	}
	else if (first + count > _hoops_IPRI->face_count) {
		char			buf[MAX_ERRMSG];
		HE_ERROR2 (HEC_REGION, HES_INVALID_OFFSET,
				Sprintf_DD (null, "Can't set as many as %d faces at offset %d -", count, first),
				   Sprintf_D (buf, "the Shell or Mesh only has %d", _hoops_IPRI->face_count));
	}
	else {
		bool _hoops_GAARS = false;

		if (_hoops_IPRI->local_face_attributes.regions == null) {
			int				offset;

			for (offset=0; offset<count; offset++) {
				if (in_regions[offset] != 0)
					break;
			}
			if (offset != count)
				_hoops_HRARS (_hoops_IPRI);
			else
				_hoops_GAARS = true;
		}

		if (!_hoops_GAARS) {
			int alter *	regions = _hoops_IPRI->local_face_attributes.regions;
			regions[_hoops_IPRI->face_count + _hoops_GISCC] = 0;
			regions = _hoops_IPRI->local_face_attributes.regions + first;

			bool	_hoops_RGHIR = false;

			if (*(_hoops_IPRI->local_face_attributes._hoops_CHHPR()) != 0) {
				_hoops_GIIPR *	flags;

				flags = _hoops_IPRI->local_face_attributes._hoops_CHHPR(first);
				while (count-- > 0) {
					if (*regions != *in_regions && ANYBIT (*flags, _hoops_PHGPR))
						_hoops_RGHIR = true;
					*regions++ = *in_regions++;
					if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR))
						flags++;
				}
			}
			else {
				while (count-- > 0)
					*regions++ = *in_regions++;
			}

			/*_hoops_SRARS (_hoops_CPHAR);*/

			if (_hoops_IPRI->type == _hoops_SCIP &&
				_hoops_IPRI->tristrips != null && _hoops_RGHIR)
				_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;
		}
	}
	_hoops_IRRPR();
}





HC_INTERFACE void HC_CDECL HC_Show_Faces (
	int alter *		count,
	int alter *		faces)
{
	_hoops_PAPPR context("Show_Faces");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Faces () */\n");
	);

	if (context->open_list == null) {
		HE_ERROR (HEC_REGION, HES_OPEN_GEOMETRY_FIRST, "Must 'Open_Region' first");
		return;
	}
	if (context->open_list->_hoops_GCRIR != _hoops_GSRIR) {
		HE_ERROR (HEC_REGION, HES_INVALID_INPUT, "Most recent 'Open' was not an 'Open_Region'");
		return;
	}

	_hoops_CSPPR();
	Polyhedron *	_hoops_IPRI = (Polyhedron *)context->open_list->info._hoops_IPRI._hoops_IGRPR;
	int region = context->open_list->info._hoops_IPRI.offset;

	int				offset;
	int				_hoops_ASASI=0;

	if (_hoops_IPRI->local_face_attributes.regions == null) {
		/* _hoops_PSP _hoops_HHHA _hoops_PGHH, _hoops_HIS _hoops_RGAR _hoops_SHIR _hoops_ISPH 0 _hoops_SSCP _hoops_GII (_hoops_PPR _hoops_HCR) */
		if (region == 0) {
			_hoops_ASASI = _hoops_IPRI->face_count;
			for (offset=0; offset < _hoops_IPRI->face_count; offset++)
				*faces++ = offset;
		}
	}
	else {
		int const *		regions = _hoops_IPRI->local_face_attributes.regions;

		for (offset=0; offset < _hoops_IPRI->face_count; offset++) {
			if (*regions++ == region) {
				++_hoops_ASASI;
				*faces++ = offset;
			}
		}
	}

	*count = _hoops_ASASI;

	_hoops_IRRPR();

#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Faces_Count (
	int alter *		count)
{
	_hoops_PAPPR context("Show_Faces_Count");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Faces_Count () */\n");
	);

	if (context->open_list == null) {
		HE_ERROR (HEC_REGION, HES_OPEN_GEOMETRY_FIRST, "Must 'Open_Region' first");
		return;
	}
	if (context->open_list->_hoops_GCRIR != _hoops_GSRIR) {
		HE_ERROR (HEC_REGION, HES_INVALID_INPUT, "Most recent 'Open' was not an 'Open_Region'");
		return;
	}

	_hoops_CSPPR();

	Polyhedron *	_hoops_IPRI = (Polyhedron *)context->open_list->info._hoops_IPRI._hoops_IGRPR;
	int	region = context->open_list->info._hoops_IPRI.offset;

	int				_hoops_ASASI=0;

	if (_hoops_IPRI->local_face_attributes.regions == null) {
		/* _hoops_PSP _hoops_HHHA _hoops_PGHH, _hoops_HIS _hoops_RGAR _hoops_SHIR _hoops_ISPH 0 _hoops_SSCP _hoops_GII (_hoops_PPR _hoops_HCR) */
		if (region == 0)
			*count = _hoops_IPRI->face_count;
	}
	else {
		int const *		regions = _hoops_IPRI->local_face_attributes.regions;
		int				offset;

		for (offset=0; offset <  _hoops_IPRI->face_count; offset++) {
			if (*regions++ == region)
				++_hoops_ASASI;
		}
	}

	*count = _hoops_ASASI;

	_hoops_IRRPR();
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Region (
	int alter *		region)
{
	_hoops_PAPPR context("Show_Region");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Region () */\n");
	);

	if (context->open_list == null) {
		HE_ERROR (HEC_FACE, HES_OPEN_GEOMETRY_FIRST, "Must 'Open_Face' first");
		return;
	}
	if (context->open_list->_hoops_GCRIR != _hoops_ICRIR) {
		HE_ERROR (HEC_FACE, HES_INVALID_INPUT,"Most recent 'Open' was not an 'Open_Face'");
		return;
	}

	_hoops_CSPPR();
	Polyhedron *	_hoops_IPRI = (Polyhedron *)context->open_list->info._hoops_IPRI._hoops_IGRPR;
	int	offset = context->open_list->info._hoops_IPRI.offset;

	if (_hoops_IPRI->local_face_attributes.regions == null)
		*region = 0;
	else
		*region = _hoops_IPRI->local_face_attributes.regions[offset];

	_hoops_IRRPR();
#endif
}





HC_INTERFACE void HC_CDECL HC_MShow_Region_Faces (
	Key				key,
	int				region,
	int alter *		count,
	int alter *		faces)
{
	_hoops_PAPPR context("MShow_Region_Faces");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Region_Faces () */\n");
	);

	int				offset;
	int				_hoops_ASASI=0;

	_hoops_CSPPR();

	Polyhedron *	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (context, key);

	if (_hoops_IPRI == null ||
		(_hoops_IPRI->type != _hoops_SCIP && _hoops_IPRI->type != _hoops_GSIP) ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_REGION, HES_INVALID_KEY, "Key does not refer to a valid Shell or Mesh");
	}
	else {
		*count = 0;

		if (_hoops_IPRI->local_face_attributes.regions == null) {
			/* _hoops_PSP _hoops_HHHA _hoops_PGHH, _hoops_HIS _hoops_RGAR _hoops_SHIR _hoops_ISPH 0 _hoops_SSCP _hoops_GII (_hoops_PPR _hoops_HCR) */
			if (region == 0) {
				_hoops_ASASI = _hoops_IPRI->face_count;
				for (offset=0; offset < _hoops_IPRI->face_count; offset++)
					*faces++ = offset;
			}
		}
		else {
			int const *		regions = _hoops_IPRI->local_face_attributes.regions;

			/* _hoops_SIGP: _hoops_HGI _hoops_HRGR _hoops_CPSA, _hoops_CPSA _hoops_HIAC.  _hoops_GCRR _hoops_RGR _hoops_RGGIR(1). */
			/* _hoops_RAIGR _hoops_SCAH _hoops_GHCA _hoops_SHH _hoops_RIRA _hoops_ARI _hoops_CAS _hoops_RH _hoops_SIC _hoops_HRGR _hoops_RH _hoops_ISPH _hoops_PPR _hoops_RH _hoops_PIRA _hoops_HRGR _hoops_RH _hoops_RPR. */
			for (offset=0; offset < _hoops_IPRI->face_count; offset++) {
				if (*regions++ == region) {
					++_hoops_ASASI;
					*faces++ = offset;
				}
			}
		}

		*count=_hoops_ASASI;
	}
	_hoops_IRRPR();

#endif
}

HC_INTERFACE void HC_CDECL HC_MShow_Region_Faces_Count (
	Key				key,
	int				region,
	int alter *		count)
{
	_hoops_PAPPR context("MShow_Region_Faces_Count");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Region_Faces_Count () */\n");
	);

	int	_hoops_ASASI = 0;

	_hoops_CSPPR();
	Polyhedron *	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (context, key);

	if (_hoops_IPRI == null ||
		(_hoops_IPRI->type != _hoops_SCIP && _hoops_IPRI->type != _hoops_GSIP) ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_REGION, HES_INVALID_KEY, "Key does not refer to a valid Shell or Mesh");
	}
	else {
		if (_hoops_IPRI->local_face_attributes.regions == null) {
			/* _hoops_PSP _hoops_HHHA _hoops_PGHH, _hoops_HIS _hoops_RGAR _hoops_SHIR _hoops_ISPH 0 _hoops_SSCP _hoops_GII (_hoops_PPR _hoops_HCR) */
			if (region == 0)
				*count = _hoops_IPRI->face_count;
		}
		else {
			int const *		regions = _hoops_IPRI->local_face_attributes.regions;
			int				offset;

			/* _hoops_SIGP: _hoops_HGI _hoops_HRGR _hoops_CPSA, _hoops_CPSA _hoops_HIAC.  _hoops_GCRR _hoops_RGR _hoops_RGGIR(1). */
			/* _hoops_RAIGR _hoops_SCAH _hoops_GHCA _hoops_SHH _hoops_RIRA _hoops_ARI _hoops_CAS _hoops_RH _hoops_SIC _hoops_HRGR _hoops_RH _hoops_ISPH _hoops_PPR _hoops_RH _hoops_PIRA _hoops_HRGR _hoops_RH _hoops_RPR. */
			for (offset=0; offset < _hoops_IPRI->face_count; offset++) {
				if (*regions++ == region)
					++_hoops_ASASI;
			}
		}

		*count = _hoops_ASASI;
	}
	_hoops_IRRPR();
#endif
}



HC_INTERFACE void HC_CDECL HC_MShow_Face_Regions (
	Key				key,
	int alter *		count,
	int alter *		regions)
{
	_hoops_PAPPR context("MShow_Face_Regions");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Face_Regions () */\n");
	);

	_hoops_CSPPR();
	Polyhedron *	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (context, key);

	if (_hoops_IPRI == null ||
		(_hoops_IPRI->type != _hoops_SCIP && _hoops_IPRI->type != _hoops_GSIP) ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_REGION, HES_INVALID_KEY, "Key does not refer to a valid Shell or Mesh");
	}
	else {
		*count = _hoops_IPRI->face_count;

		if (_hoops_IPRI->local_face_attributes.regions == null)
			ZERO_ARRAY (regions, *count, int);
		else
			_hoops_AIGA (_hoops_IPRI->local_face_attributes.regions, *count, int, regions);
	}
	_hoops_IRRPR();
#endif
}

HC_INTERFACE void HC_CDECL HC_MShow_Face_Regions_Count (
	Key				key,
	int alter *		count)
{
	_hoops_PAPPR context("MShow_Face_Regions_Count");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Face_Regions_Count () */\n");
	);

	_hoops_CSPPR();
	Polyhedron *	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (context, key);

	if (_hoops_IPRI == null ||
		(_hoops_IPRI->type != _hoops_SCIP && _hoops_IPRI->type != _hoops_GSIP) ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_REGION, HES_INVALID_KEY, "Key does not refer to a valid Shell or Mesh");
	}
	else
		*count = _hoops_IPRI->face_count;
	_hoops_IRRPR();
#endif
}

HC_INTERFACE void HC_CDECL HC_MShow_Partial_Face_Regions (
	Key				key,
	int				first,
	int				count,
	int alter *		regions)
{
	_hoops_PAPPR context("MShow_Partial_Face_Regions");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Partial_Face_Regions () */\n");
	);

	_hoops_CSPPR();
	Polyhedron *	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (context, key);

	if (_hoops_IPRI == null ||
		(_hoops_IPRI->type != _hoops_SCIP && _hoops_IPRI->type != _hoops_GSIP) ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_REGION, HES_INVALID_KEY, "Key does not refer to a valid Shell or Mesh");
	}
	else {
		if (first < 0 || count < 0) {
			HE_ERROR (HEC_REGION, HES_INVALID_NUMBER,"The first face offset or face count is negative");
		}
		else {
			if (first + count > _hoops_IPRI->face_count) {
				char			buf[MAX_ERRMSG];

				HE_ERROR2 (HEC_REGION, HES_INVALID_OFFSET,
						Sprintf_DD (null, "Can't show as many as %d faces at offset %d -", count, first),
						   Sprintf_D (buf, "the Shell or Mesh only has %d", _hoops_IPRI->face_count));
				return;
			}

			if (_hoops_IPRI->local_face_attributes.regions == null)
				ZERO_ARRAY (regions, count, int);
			else
				_hoops_AIGA (_hoops_IPRI->local_face_attributes.regions+first, count, int, regions);
		}
	}
	_hoops_IRRPR();
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Region_Range (
	Key				key,
	int alter *		lowest,
	int alter *		highest)
{
	_hoops_PAPPR context("Show_Region_Range");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Region_Range () */\n");
	);

	_hoops_CSPPR();
	Polyhedron *	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (context, key);

	if (_hoops_IPRI == null ||
		(_hoops_IPRI->type != _hoops_SCIP && _hoops_IPRI->type != _hoops_GSIP) ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_REGION, HES_INVALID_KEY, "Key does not refer to a valid Shell or Mesh");
	}
	else {
		if (_hoops_IPRI->local_face_attributes.regions == null)
			*lowest = *highest = 0;
		else {
			int const *		regions = _hoops_IPRI->local_face_attributes.regions;
			int				count = _hoops_IPRI->face_count;

			if (!regions[count + _hoops_GISCC]) {
				_hoops_CRARS(_hoops_IPRI);
			}

			*lowest = regions[count];
			*highest = regions[count+1];
		}
	}
	_hoops_IRRPR();
#endif
}


local bool _hoops_RAARS (
	_hoops_AIGPR *	_hoops_RIGC,
	Polyhedron *			_hoops_IPRI,
	int						region,
	int *					count,
	Point **				points,
	int *					_hoops_GGCIR,
	int **					_hoops_SAGPA)
{
	int const *	regions = _hoops_IPRI->local_face_attributes.regions;

	if (_hoops_IPRI->type == _hoops_SCIP) {
		Shell *		_hoops_SPHPR = (Shell *)_hoops_IPRI;
		int *		_hoops_PSRGA;
		int *		_hoops_AAARS;
		int			length;
		int *		_hoops_SPRAR;
		int			index;
		int			_hoops_ICHGS;
		int			_hoops_PAARS;
		Point *		new_points;
		int *		_hoops_AARGA;

		if (regions == null) {
			/* _hoops_HCR _hoops_GGR _hoops_SHIR _hoops_ISPH */
			if (region != 0) {
				/* _hoops_HIH _hoops_IAGC _hoops_GPGH'_hoops_RA, _hoops_HIS _hoops_ISAP */
				*count = *_hoops_GGCIR = 0;
				*points = null;
				*_hoops_SAGPA = null;
			}
			else {
				/* _hoops_SHSC _hoops_AHAP... */
				*count = _hoops_SPHPR->point_count;
				_hoops_APRGA(_hoops_SPHPR->points, _hoops_SPHPR->point_count, Point, *points);
				*_hoops_GGCIR = _hoops_SPHPR->face_list_length;
				_hoops_APRGA(_hoops_SPHPR->face_list, _hoops_SPHPR->face_list_length, int, *_hoops_SAGPA);
			}

			return true;
		}

		if (_hoops_SPHPR->face_list == null && _hoops_SPHPR->tristrips != null)
			HI_Face_List_From_Tristrips (_hoops_RIGC, _hoops_SPHPR);

		_hoops_PSRGA = _hoops_SPHPR->face_list;
		_hoops_AAARS = _hoops_PSRGA + _hoops_SPHPR->face_list_length;

		ZALLOC_ARRAY (_hoops_SPRAR, _hoops_SPHPR->point_count, int);

		/* _hoops_SRS _hoops_RIH, _hoops_SSS _hoops_IGIR _hoops_IIGR _hoops_SCRPA _hoops_IIGR _hoops_RSSI _hoops_GGR _hoops_ISPH
		 * _hoops_PPR _hoops_RH _hoops_PSHS _hoops_RSSA */
		_hoops_ICHGS = _hoops_PAARS = 0;
		for (index=0; index < _hoops_SPHPR->face_count; index++) {
			if (regions[index] == region) {
				do {
					length = *_hoops_PSRGA++;
					if (length < 0)
						length = -length;
					_hoops_PAARS += length + 1;
					while (length-- > 0) {
						int		which = *_hoops_PSRGA++;

						if (_hoops_SPRAR[which] == 0) {
							_hoops_SPRAR[which] = 1;
							++_hoops_ICHGS;
						}
					}
				} while (_hoops_PSRGA != _hoops_AAARS && *_hoops_PSRGA < 0);
			}
			else {
				do {
					length = *_hoops_PSRGA++;
					if (length < 0)
						length = -length;
					_hoops_PSRGA += length;
				} while (_hoops_PSRGA != _hoops_AAARS && *_hoops_PSRGA < 0);
			}
		}

		if (_hoops_PAARS == 0) {
			*count = *_hoops_GGCIR = 0;
			*points = null;
			*_hoops_SAGPA = null;
		}
		else {
			ALLOC_ARRAY (new_points, _hoops_ICHGS, Point);
			ALLOC_ARRAY (_hoops_AARGA, _hoops_PAARS, int);

			*count = _hoops_ICHGS;
			*points = new_points;
			*_hoops_GGCIR = _hoops_PAARS;
			*_hoops_SAGPA = _hoops_AARGA;

			/* _hoops_IPS _hoops_IGI _hoops_RSSA _hoops_PPR _hoops_AICCI _hoops_SIA */
			_hoops_ICHGS = 0;
			for (index=0; index<_hoops_SPHPR->point_count; index++) {
				if (_hoops_SPRAR[index] != 0) {
					new_points[_hoops_ICHGS].x = _hoops_SPHPR->points[index].x;
					new_points[_hoops_ICHGS].y = _hoops_SPHPR->points[index].y;
					new_points[_hoops_ICHGS].z = _hoops_SPHPR->points[index].z;
					_hoops_SPRAR[index] = _hoops_ICHGS++;
				}
			}

			/* _hoops_IPS _hoops_IGI _hoops_RSSI, _hoops_HGAA _hoops_PSPI */
			_hoops_PAARS = 0;
			_hoops_PSRGA = _hoops_SPHPR->face_list;
			for (index=0; index < _hoops_SPHPR->face_count; index++) {
				if (regions[index] == region) {
					do {
						_hoops_AARGA[_hoops_PAARS++] = length = *_hoops_PSRGA++;
						if (length < 0)
							length = -length;
						while (length-- > 0)
							_hoops_AARGA[_hoops_PAARS++] = _hoops_SPRAR[*_hoops_PSRGA++];
					} while (_hoops_PSRGA != _hoops_AAARS && *_hoops_PSRGA < 0);
				}
				else {
					do {
						length = *_hoops_PSRGA++;
						if (length < 0)
							length = -length;
						_hoops_PSRGA += length;
					} while (_hoops_PSRGA != _hoops_AAARS && *_hoops_PSRGA < 0);
				}
			}
		}

		FREE_ARRAY (_hoops_SPRAR, _hoops_SPHPR->point_count, int);
	}
	else {
		if (regions == null) {
			/* _hoops_HCR _hoops_GGR _hoops_SHIR _hoops_ISPH */
			if (region != 0) {
				/* _hoops_HIH _hoops_IAGC _hoops_GPGH'_hoops_RA, _hoops_HIS _hoops_ISAP */
				*count = *_hoops_GGCIR = 0;
				*points = null;
				*_hoops_SAGPA = null;
				return true;
			}
		}

		HE_WARNING (HEC_REGION, HES_NOT_AVAILABLE, "Not implemented for Mesh regions");
		return false;
	}

	return true;
}


HC_INTERFACE Key HC_Insert_Shell_From_Region (
	Key				key,
	int				region,
	char const *	options)
{
	_hoops_PAPPR context("Insert_Shell_From_Region");


	int				count, _hoops_GGCIR;
	Point *			points;
	int *			_hoops_SAGPA;
	Key				_hoops_CHSSR;
	char const *	_hoops_AHSCA = options;


	_hoops_CSPPR();

	Polyhedron *	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (context, key);

	while (*_hoops_AHSCA == ' ')
		++_hoops_AHSCA;

	if (_hoops_IPRI == null ||
		(_hoops_IPRI->type != _hoops_SCIP && _hoops_IPRI->type != _hoops_GSIP) ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_REGION, HES_INVALID_KEY,"Key does not refer to a valid Shell or Mesh");
		_hoops_CHSSR = _hoops_SHSSR;
	}
	else if (*_hoops_AHSCA) {
		HE_ERROR (HEC_REGION, HES_INVALID_OPTION,"No options currently supported");
		_hoops_CHSSR = _hoops_SHSSR;
	}
	else if (!_hoops_RAARS (context, _hoops_IPRI, region, &count, &points, &_hoops_GGCIR, &_hoops_SAGPA))
		_hoops_CHSSR = _hoops_SHSSR;
	else {
		_hoops_CHSSR = HC_Insert_Shell (count, points, _hoops_GGCIR, _hoops_SAGPA);

		if (count > 0)
			FREE_ARRAY (points, count, Point);
		if (_hoops_GGCIR > 0)
			FREE_ARRAY (_hoops_SAGPA, _hoops_GGCIR, int);
	}
	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Insert_Shell_From_Region (LOOKUP(%D), ", key));
		HI_Dump_Code (Sprintf_D (null, "%d, ", region));
		HI_Dump_Code (Sprintf_S (null, "\"%s\"),", options));
		HI_Dump_Code (Sprintf_LD (null, "%D);}\n", _hoops_CHSSR));
	);

	return _hoops_CHSSR;
}



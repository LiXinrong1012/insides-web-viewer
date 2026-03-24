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
 * $Id: obf_tmp.txt 1.85 2010-10-06 19:16:36 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


local bool _hoops_AISII (
	Polyhedron const *		_hoops_IPRI,
	int						count,
	int const *				indices) {
	int						i;

	for (i=0; i<count; i++) {
		if (indices[i] < 0) {
			HE_ERROR (HEC_MSET_FACE, HES_INVALID_OFFSET,
					   Sprintf_DD (null, "Invalid offset value %d at location %d",
									indices[i], i));
			return false;
		}
		if (_hoops_IPRI->face_count < indices[i]) {
			char			buf[MAX_ERRMSG];

			HE_ERROR2 (HEC_MSET_FACE, HES_INVALID_OFFSET,
					   Sprintf_DD (null, "Invalid offset value %d at location %d", indices[i], i),
					   Sprintf_D (buf, "Shell or mesh only has %d faces", _hoops_IPRI->face_count));
			return false;
		}
	}

	return true;
}

local bool _hoops_PRSII (
	Polyhedron const *		_hoops_IPRI,
	int						count,
	int const *				indices) {
	int						i;

	for (i=0; i<count; i++) {
		if (indices[i] < 0) {
			HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
				Sprintf_DD (null, "Invalid offset value %d at location %d",
				indices[i], i));
			return false;
		}
		if (_hoops_IPRI->point_count < indices[i]) {
			char			buf[MAX_ERRMSG];

			HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
				Sprintf_DD (null, "Invalid offset value %d at location %d", indices[i], i),
				Sprintf_D (buf, "Shell or mesh only has %d points", _hoops_IPRI->point_count));
			return false;
		}
	}

	return true;
}

HC_INTERFACE void HC_CDECL HC_MSet_Vertex_Normals (
	Key						key,
	int						offset,
	int						count,
	Vector const *			normals) 
{
	_hoops_PAPPR context("MSet_Vertex_Normals");

#ifdef _hoops_HCGHR
	_hoops_IRPPR ("Geometry Normals");
#else
	CODE_GENERATION (
		int		count2 = count;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "HC_POINT* normals = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", count2));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "normals[%d].x = %.6ff;  ", count2, normals[count2].x));
			HI_Dump_Code (_hoops_CHCHR (null, "normals[%d].y = %.6ff;  ", count2, normals[count2].y));
			HI_Dump_Code (_hoops_CHCHR (null, "normals[%d].z = %.6ff;\n", count2, normals[count2].z));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Vertex_Normals (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, normals);\n", offset, count));
		HI_Dump_Code ("free (normals);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		return;
	}

	if (count == 0) 
		return;  /* _hoops_CPRSH */

	if (offset < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_OFFSET, "Offset is negative");
		return;
	}

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_HCGPP)) == null)
		return;

	if (_hoops_IPRI->point_count < offset + count) {
		char	buf[MAX_ERRMSG];
		HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
				   Sprintf_D (null, "Shell or mesh only has %d vertices -", _hoops_IPRI->point_count),
				   Sprintf_DD (buf, "can't change %d of them at offset %d", count, offset));
	}
	else {

		if (_hoops_IPRI->local_vertex_attributes.normals == null)
			HI_Initialize_Vertex_Attributes (_hoops_IPRI, LVA_EXPLICIT_NORMAL, 0);

		Vector *				_hoops_AHAHR = &_hoops_IPRI->local_vertex_attributes.normals[offset];
		Local_Vertex_Flags *	flags = _hoops_IPRI->local_vertex_attributes._hoops_CHHPR(offset);

		if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
			if (offset != 0 || count != _hoops_IPRI->point_count) {
				/* _hoops_SR _hoops_CHR _hoops_RGAR _hoops_HCHAR _hoops_HPGR _hoops_IRS _hoops_GIIAR _hoops_IIGR _hoops_RH _hoops_GIHA, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS _hoops_CCPP _hoops_IRS _hoops_IIRRA->_hoops_SGI _hoops_CRPR.*/
				ZALLOC_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
				for (int i = 0; i < _hoops_IPRI->point_count; i++)
					_hoops_IPRI->local_vertex_attributes.flags[i] = _hoops_IPRI->local_vertex_attributes._hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
				flags = _hoops_IPRI->local_vertex_attributes._hoops_CHHPR(offset);
			}
			else {
				/* _hoops_SR _hoops_CHR _hoops_GHGA _hoops_RGR _hoops_IS _hoops_RCSAR _hoops_GPHA, _hoops_PPR _hoops_SSIA _hoops_CHR _hoops_HCR _hoops_GHRHR _hoops_PRGPR _hoops_SGIP, _hoops_HIS _hoops_IIS'_hoops_GRI _hoops_GRHP _hoops_SCH _hoops_SGS _hoops_PPRRR */
			}
		}

		do {
			if (!BIT (*flags, LVA_EXPLICIT_NORMAL)) {
				*flags |= LVA_EXPLICIT_NORMAL;
				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR))
					_hoops_IPRI->local_vertex_attributes.explicit_normal_count += count;
				else
					++_hoops_IPRI->local_vertex_attributes.explicit_normal_count;
			}

			*_hoops_AHAHR = *normals;
			if (_hoops_CSCSH(_hoops_AHAHR->x) || _hoops_CSCSH(_hoops_AHAHR->y) || _hoops_CSCSH(_hoops_AHAHR->z)) {
				_hoops_AHAHR->x = _hoops_AHAHR->y = 0.0f;
				_hoops_AHAHR->z = 1.0f;
				HE_WARNING (HEC_NORMAL, HES_BAD_VALUE, "Normal contains one or more NAN values");
			}
			else if (!HI_Normalize (_hoops_AHAHR))
				HE_WARNING (HEC_NORMAL, HES_ZERO_LENGTH, "Normal vector is of zero or nearly zero length");

			++_hoops_AHAHR;
			++normals;
			if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR))
				++flags;
		} _hoops_RGGA (--count == 0);

		if (BIT (_hoops_IPRI->polyhedron_flags, PHF_VERTEX_NORMALS_VALID)) {
			/* _hoops_GPHA _hoops_ASGA _hoops_AAPR _hoops_PGCPR _hoops_IS _hoops_IHGSR */
			_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR|_hoops_RPSIR);
		}
		else {
			/* _hoops_AGGCI _hoops_IPIH _hoops_PGGCI */
			_hoops_SASIR (context, _hoops_IPRI, _hoops_CAHRA);
		}

		if (_hoops_IPRI->local_vertex_attributes.explicit_normal_count == _hoops_IPRI->point_count)
			_hoops_IPRI->polyhedron_flags |= PHF_VERTEX_NORMALS_VALID;
	}

	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_MUnSet_Vertex_Normals (
	Key								key,
	int								offset,
	int								count) 
{
	_hoops_PAPPR context("MUnSet_Vertex_Normals");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#else

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Vertex_Normals (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d);}\n", offset, count));
	);


	if (offset < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_OFFSET, "Offset is negative");
		return;
	}

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_HCGPP)) == null)
		return;

	bool	_hoops_GCSII = true;

	if (count == -1) {
		count = _hoops_IPRI->point_count - offset;
		_hoops_GCSII = false;
	}

	if (count == 0) {
		; // _hoops_CPRSH
	}
	else if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
	}
	else if (_hoops_IPRI->point_count < offset + count) {
		char	buf[MAX_ERRMSG];
		HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
			Sprintf_D (null, "Shell or mesh only has %d vertices -", _hoops_IPRI->point_count),
			Sprintf_DD (buf, "can't change %d of them at offset %d", count, offset));
	}
	else {
	
		Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

		if (_hoops_SPRI->explicit_normal_count == 0) {
			/* _hoops_ISAP _hoops_ARP _hoops_RPP _hoops_PSP _hoops_SGI, _hoops_HIS _hoops_SAHR _hoops_PSIIR & _hoops_CASI _hoops_GH */
			HE_WARNING (HEC_MUNSET, HES_MISSING, "No normals to UnSet");
		}
		else {

			bool	_hoops_AHPGR = false;

			// _hoops_SR'_hoops_ASAR _hoops_HGGCI _hoops_HCR _hoops_ASGA
			if (offset == 0 && count == _hoops_IPRI->point_count) {
				if (_hoops_SPRI->explicit_normal_count != _hoops_IPRI->point_count)
					_hoops_AHPGR = true;

				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR))
					_hoops_SPRI->_hoops_SGRHR &= ~(LVA_EXPLICIT_NORMAL);
				else {
					Local_Vertex_Flags *	flags = _hoops_SPRI->flags;
					do {
						*flags++ &= ~(LVA_EXPLICIT_NORMAL);
					} _hoops_RGGA (--count == 0);
				}
				_hoops_SPRI->explicit_normal_count = 0;
			}
			// _hoops_IASI _hoops_IPPRA
			else {
				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
					ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
					for (int i = 0; i < _hoops_IPRI->point_count; i++)
						_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
					_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
				}

				Local_Vertex_Flags *	flags = &_hoops_SPRI->flags[offset];
				do {
					if (BIT (*flags, LVA_EXPLICIT_NORMAL)) {
						*flags &= ~LVA_EXPLICIT_NORMAL;
						--_hoops_SPRI->explicit_normal_count;
					}
					else
						_hoops_AHPGR = true;

					++flags;
				} _hoops_RGGA (--count == 0);
			}

			if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR) &&
				_hoops_SPRI->lvf_uniform(_hoops_IPRI->point_count)) {
					_hoops_SPRI->_hoops_SGRHR = _hoops_SPRI->flags[0];
					FREE_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
					_hoops_IPRI->polyhedron_flags &= ~_hoops_CGRHR;
					_hoops_SPRI->flags = null;
			}

			if (_hoops_AHPGR && _hoops_GCSII)
				HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");

			if (_hoops_IPRI->tristrips != null) {
				_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;
				_hoops_SASIR (context, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
			}
		}
	}

	_hoops_IRRPR();
#endif
#endif
}

#define _hoops_IGGCI	0
#define _hoops_CGGCI		1

local int _hoops_SGGCI (
	_hoops_AIGPR *			_hoops_RIGC, 
	Key								key,
	int								offset,
	int								count,
	int const *						specific_vertices,
	unsigned char alter *			existence,
	Vector alter *					normals,
	int *							_hoops_HASII = null) {
	int								_hoops_IASII = 0;
	Local_Vertex_Flags const *		flags;
	Local_Vertex_Attributes const *	_hoops_SPRI;
	Polyhedron const *				_hoops_IPRI;

	_hoops_CSPPR();

	if(_hoops_HASII)
		*_hoops_HASII = 0;
	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (_hoops_RIGC, key);

	if (_hoops_IPRI == null ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_GEOMETRY, HES_INVALID_KEY, "Key does not refer to valid geometry");
		if(_hoops_HASII)
			*_hoops_HASII = 1;
		goto Release;
	}
	else if (_hoops_IPRI->type != _hoops_SCIP && _hoops_IPRI->type != _hoops_GSIP) {
		if (_hoops_IPRI->type == _hoops_ASIP || 
			_hoops_IPRI->type == _hoops_CSIP || 
			_hoops_IPRI->type == _hoops_HSIP || 
			_hoops_IPRI->type == _hoops_PRCP)
			HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_KEY, "MShow_Vertex_Normals not allowed for this primitive type.  Try MShow_Net_Vertex_Normals.");
		else
			HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_KEY, "Key does not refer to a valid shell or mesh");
		if(_hoops_HASII)
			*_hoops_HASII = 1;
		goto Release;
	}

	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		if(_hoops_HASII)
			*_hoops_HASII = 1;
		goto Release;
	}

	if(specific_vertices) 	{
		if (!_hoops_PRSII (_hoops_IPRI, count, specific_vertices))
		{
			if(_hoops_HASII)
				*_hoops_HASII = 1;
			goto Release;
		}
	}
	else {
		if (offset < 0) {
			HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_OFFSET, "Offset is negative");
			if(_hoops_HASII)
				*_hoops_HASII = 1;
			goto Release;
		}

		if (_hoops_IPRI->point_count < offset + count) {
			char			buf[MAX_ERRMSG];

			HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
					   Sprintf_D (null, "Shell or mesh only has %d vertices -", _hoops_IPRI->point_count),
					   Sprintf_DD (buf, "can't show %d of them at offset %d", count, offset));
			if(_hoops_HASII)
				*_hoops_HASII = 1;
			goto Release;
		}
	}

	if (count == 0) 
		goto Release;  /* _hoops_CPRSH */

	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

	if(existence)
		memset(existence, 0, count*sizeof(char));

	if (_hoops_SPRI->normals == null || _hoops_SPRI->explicit_normal_count == 0 ||
		(!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR) &&
		!BIT(_hoops_SPRI->_hoops_SGRHR,LVA_EXPLICIT_NORMAL)))
		goto Release;

	if(specific_vertices){
		for(int i=0; i<count; ++i)
		{
			flags = _hoops_SPRI->_hoops_CHHPR(specific_vertices[i]);
			if(BIT(*flags, LVA_EXPLICIT_NORMAL)) {
				if(normals)
					normals[i] = _hoops_SPRI->normals[specific_vertices[i]];
				if(existence)
					existence[i] = _hoops_CGGCI;
				++_hoops_IASII;
			}
		}
	}
	else {
		for(int i=0; i<count; ++i)
		{
			flags = _hoops_SPRI->_hoops_CHHPR(offset+i);
			if(BIT(*flags, LVA_EXPLICIT_NORMAL)) {
				if(normals)
					normals[i] = _hoops_SPRI->normals[offset+i];
				if(existence)
					existence[i] = _hoops_CGGCI;
				++_hoops_IASII;
			}
		}
	}	

Release:
	_hoops_IRRPR();
	return _hoops_IASII;
}

HC_INTERFACE void HC_CDECL HC_MShow_Vertex_Normals (
	Key							key,
	int							offset,
	int							count,
	Vector alter *				normals) 
{
	_hoops_PAPPR context("MShow_Vertex_Normals");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef _hoops_HCGHR
	_hoops_IRPPR ("Geometry Normals");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Vertex_Normals () */\n");
	);

	int	_hoops_HASII;

	int	_hoops_IASII = _hoops_SGGCI(context, key, offset, count, null, null, normals, &_hoops_HASII);

	//_hoops_RPP _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_RHHS _hoops_PCCP _hoops_RIHH, _hoops_SAHR _hoops_CASI _hoops_GH _hoops_PPR _hoops_PHHR _hoops_RISII
	if(_hoops_HASII)
		return;

	//_hoops_RARIR
	if (_hoops_IASII != count) {
		HE_ERROR (HEC_NORMAL, HES_NO_LOCAL_SETTING,
				  "Not all vertex normals are explicitly set in the specified range");
		return;
	}

#endif
#endif
}

HC_INTERFACE int HC_CDECL HC_MShow_Vertex_Normals_W_Ex (
	Key					key,
	int					offset,
	int					count,
	char alter *		_hoops_GRGCI,
	Vector alter *		normals) 
{
	_hoops_PAPPR context("MShow_Vertex_Normals_With_Existence");

	unsigned char alter *	existence = (unsigned char alter *)_hoops_GRGCI;

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return 0;
#else
#ifdef _hoops_HCGHR
	_hoops_IRPPR ("Geometry Normals");
	return 0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Vertex_Normals_With_Existence () */\n");
	);

	int	_hoops_IASII = _hoops_SGGCI(context, key, offset, count, null, existence, normals);

	return _hoops_IASII;
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_MSet_Specific_Vertex_Normals (
	Key					key,
	int					count,
	int	const *			indices,
	Vector const *		normals) 
{
	_hoops_PAPPR context("MSet_Specific_Vertex_Normals");

#ifdef _hoops_HCGHR
	_hoops_IRPPR ("Geometry Normals");
#else
	CODE_GENERATION (
		int		count2 = count;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "HC_POINT* normals = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", count2));
		HI_Dump_Code (Sprintf_D (null, "int* indices = (int*) malloc(sizeof(int)*%d);\n", count2));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "normals[%d].x = %.6ff;  ",count2, normals[count2].x));
			HI_Dump_Code (_hoops_CHCHR (null, "normals[%d].y = %.6ff;  ",count2, normals[count2].y));
			HI_Dump_Code (_hoops_CHCHR (null, "normals[%d].z = %.6ff;\n",count2, normals[count2].z));
			HI_Dump_Code (Sprintf_DD (null, "indices[%d] = %d;\n",count2, indices[count2]));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Specific_Vertex_Normals (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_D (null, "%d, indices, normals);\n", count));
		HI_Dump_Code ("free (normals);\n");
		HI_Dump_Code ("free (indices);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);


	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		return;
	}

	if (count == 0) 
		return;  /* _hoops_CPRSH */

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_HCGPP)) == null)
		return;

	if (_hoops_IPRI->point_count < count) {
		char	buf[MAX_ERRMSG];
		HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
				   Sprintf_D (null, "Shell or mesh only has %d vertices -", _hoops_IPRI->point_count),
				   Sprintf_D (buf, "can't change %d of them", count));
	}
	else if (_hoops_PRSII (_hoops_IPRI, count, indices)) {

		if (_hoops_IPRI->local_vertex_attributes.normals == null)
			HI_Initialize_Vertex_Attributes (_hoops_IPRI, LVA_EXPLICIT_NORMAL, 0);

		Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

		/* _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_RGSR _hoops_SASI _hoops_PPR _hoops_SR'_hoops_ASAR _hoops_GHRHR, _hoops_HPCAR _hoops_SR _hoops_CHR _hoops_RRGCI _hoops_ARGCI.  _hoops_SCH'_hoops_GRI _hoops_HAH _hoops_ACIPR _hoops_IS _hoops_SHAC _hoops_CGIRA _hoops_IAII _hoops_CCA _hoops_PRGCI _hoops_CR _hoops_SR'_hoops_ASAR _hoops_PSAR _hoops_GCAS _hoops_HRGCI _hoops_IPSP _hoops_PSPI */
		if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
			ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
			for (int i = 0; i < _hoops_IPRI->point_count; i++)
				_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
			_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
		}

		Vector *	_hoops_AHAHR = _hoops_SPRI->normals;

		do {
			int			index = *indices++;

			if (!BIT (*_hoops_SPRI->_hoops_CHHPR(index), LVA_EXPLICIT_NORMAL)) {
				*_hoops_SPRI->_hoops_CHHPR(index) |= LVA_EXPLICIT_NORMAL;
				++_hoops_SPRI->explicit_normal_count;
			}

			_hoops_AHAHR[index] = *normals;

			if (_hoops_CSCSH(_hoops_AHAHR[index].x) || _hoops_CSCSH(_hoops_AHAHR[index].y) || _hoops_CSCSH(_hoops_AHAHR[index].z)) {
				_hoops_AHAHR[index].x = _hoops_AHAHR[index].y = 0.0f;
				_hoops_AHAHR[index].z = 1.0f;
				HE_WARNING (HEC_NORMAL, HES_BAD_VALUE, "Normal contains one or more NAN values");
			}
			else if (!HI_Normalize (&_hoops_AHAHR[index]))
				HE_WARNING (HEC_NORMAL, HES_ZERO_LENGTH, "Normal vector is of zero or nearly zero length");

			++normals;
		} _hoops_RGGA (--count == 0);

		if (BIT (_hoops_IPRI->polyhedron_flags, PHF_VERTEX_NORMALS_VALID)) {
			/* _hoops_GPHA _hoops_ASGA _hoops_AAPR _hoops_PGCPR _hoops_IS _hoops_IHGSR */
			_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR|_hoops_RPSIR);
		}
		else {
			/* _hoops_AGGCI _hoops_IPIH _hoops_PGGCI */
			_hoops_SASIR (context, _hoops_IPRI, _hoops_CAHRA);
		}

		if (_hoops_IPRI->local_vertex_attributes.explicit_normal_count == _hoops_IPRI->point_count)
			_hoops_IPRI->polyhedron_flags |= PHF_VERTEX_NORMALS_VALID;
	}

	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_MUnSet_Specific_Vert_Normals (
	Key				key,
	int				count,
	int	const *		indices) 
{
	_hoops_PAPPR context("MUnSet_Specific_Vertex_Normals");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#else

	CODE_GENERATION (
		int		count2 = count;
		if (count == 0) { 
			HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Specific_Vertex_Normals (LOOKUP (%D),  0, 0);\n", key));
		}
		else {
			HI_Dump_Code ("{\n");
			++HOOPS_WORLD->_hoops_ISPPR;
			HI_Dump_Code (Sprintf_D (null, "int* indices = (int*) malloc(sizeof(int)*%d);\n", count2));
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (Sprintf_DD (null, "indices[%d] = %d;\n", count2, indices[count2]));
			}
			HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Specific_Vertex_Normals (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_D (null, "%d, indices);\n", count));
			HI_Dump_Code ("free (indices);\n");
			--HOOPS_WORLD->_hoops_ISPPR;
			HI_Dump_Code ("}\n");
		}
	);

	if (count == 0)
		return;  /* _hoops_CPRSH */

	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		return;
	}

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_HCGPP)) == null)
		return;

	if (_hoops_IPRI->point_count < count) {
		char	buf[MAX_ERRMSG];
		HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
			Sprintf_D (null, "Shell or mesh only has %d vertices -", _hoops_IPRI->point_count),
			Sprintf_D (buf, "can't change %d of them", count));
	}
	else if (_hoops_PRSII (_hoops_IPRI, count, indices)) {

		Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

		if (_hoops_SPRI->explicit_normal_count == 0) {
			/* _hoops_ISAP _hoops_ARP _hoops_RPP _hoops_PSP _hoops_SGI, _hoops_HIS _hoops_SAHR _hoops_PSIIR & _hoops_CASI _hoops_GH */
			HE_WARNING (HEC_MUNSET, HES_MISSING, "No normals to UnSet");
		}
		else {

			/* _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_HGGCI _hoops_SASI _hoops_PPR _hoops_SR'_hoops_ASAR _hoops_GHRHR, _hoops_HPCAR _hoops_SR _hoops_CHR _hoops_RRGCI _hoops_ARGCI.  _hoops_SCH'_hoops_GRI _hoops_HAH _hoops_ACIPR _hoops_IS _hoops_SHAC _hoops_CGIRA _hoops_IAII _hoops_CCA _hoops_PRGCI _hoops_CR _hoops_SR'_hoops_ASAR _hoops_PSAR _hoops_GCAS _hoops_HRGCI _hoops_IPSP _hoops_PSPI */
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
				for (int i = 0; i < _hoops_IPRI->point_count; i++)
					_hoops_IPRI->local_vertex_attributes.flags[i] = _hoops_IPRI->local_vertex_attributes._hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
			}

			Local_Vertex_Flags *	flags = _hoops_SPRI->_hoops_CHHPR(0);

			bool	_hoops_AHPGR = false;

			do {
				int			index = *indices++;

				if (BIT (flags[index], LVA_EXPLICIT_NORMAL)) {
					flags[index] &= ~LVA_EXPLICIT_NORMAL;
					--_hoops_SPRI->explicit_normal_count;
				}
				else
					_hoops_AHPGR = true;

			} _hoops_RGGA (--count == 0);

#if 0
			/* _hoops_PAHH _hoops_HHGC _hoops_IS _hoops_IHIS _hoops_RGR _hoops_CRGR _hoops_SGGC */
			if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR) &&
				_hoops_SPRI->lvf_uniform(_hoops_IPRI->point_count)) {
					_hoops_SPRI->_hoops_SGRHR = _hoops_SPRI->flags[0];
					FREE_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
					_hoops_IPRI->polyhedron_flags &= ~_hoops_CGRHR;
					_hoops_SPRI->flags = null;
			}
#endif

			if (_hoops_AHPGR)
				HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");

			if (_hoops_IPRI->tristrips != null) {
				_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;
				_hoops_SASIR (context, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
			}
		}
	}

	_hoops_IRRPR();
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_MShow_Specific_Vert_Normals (
	Key						key,
	int						count,
	int const *				indices,
	Vector alter *			normals) 
{
	_hoops_PAPPR context("MShow_Specific_Vertex_Normals");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Specific_Vertex_Normals () */\n");
	);

	int	_hoops_HASII;

	int	_hoops_IASII = _hoops_SGGCI(context, key, 0, count, indices, null, normals, &_hoops_HASII);

	//_hoops_RPP _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_RHHS _hoops_PCCP _hoops_RIHH, _hoops_SAHR _hoops_CASI _hoops_GH _hoops_PPR _hoops_PHHR _hoops_RISII
	if(_hoops_HASII)
		return;

	//_hoops_RARIR
	if (_hoops_IASII != count) {
		HE_ERROR (HEC_NORMAL, HES_NO_LOCAL_SETTING,
				  "Not all vertex normals are explicitly set in the specified range");
		return;
	}
#endif
#endif
}

HC_INTERFACE int HC_CDECL HC_MShow_Spec_Vert_Normals_W_Ex (
	Key					key,
	int					count,
	int const *			indices,
	char alter *		_hoops_GRGCI,
	Vector alter *		_hoops_IICII) 
{
	_hoops_PAPPR context("MShow_Specific_Vertex_Normals_With_Existence");

	unsigned char alter *	existence = (unsigned char alter *)_hoops_GRGCI;

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return 0;
#else
#ifdef _hoops_HCGHR
	_hoops_IRPPR ("Geometry Normals");
	return 0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Specific_Vertex_Normals_With_Existence () */\n");
	);

	int _hoops_IASII = _hoops_SGGCI(context, key, 0, count, indices, existence, _hoops_IICII);

#endif
#endif
	return _hoops_IASII;
}



HC_INTERFACE void HC_CDECL HC_MSet_Face_Normals (
	Key						key,
	int						offset,
	int						count,
	Vector const *			normals) 
{
	_hoops_PAPPR context("MSet_Face_Normals");

#ifdef _hoops_HCGHR
	_hoops_IRPPR ("Geometry Normals");
#else
	CODE_GENERATION (
		int		count2 = count;
		HI_Dump_Code("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "Vector* normals = (Vector*) malloc(sizeof(Vector)*%d);\n", count2));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "normals[%d].x = %.6ff;  ", count2, normals[count2].x));
			HI_Dump_Code (_hoops_CHCHR (null, "normals[%d].y = %.6ff;  ", count2, normals[count2].y));
			HI_Dump_Code (_hoops_CHCHR (null, "normals[%d].z = %.6ff;\n", count2, normals[count2].z));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Face_Normals (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, normals);\n", offset, count));
		HI_Dump_Code ("free (normals);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	if (count < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_COUNT, "Count is negative");
		return;
	}

	if (offset < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_OFFSET, "Offset is negative");
		return;
	}

	if (count == 0) 
		return;  /* _hoops_CPRSH */

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_HCGPP)) == null)
		return;

	if (_hoops_IPRI->face_count < offset + count) {
		char	buf[MAX_ERRMSG];
		HE_ERROR2 (HEC_MSET_FACE, HES_INVALID_OFFSET,
				   Sprintf_D (null, "Shell or mesh only has %d faces -", _hoops_IPRI->face_count),
				   Sprintf_DD (buf, "can't change %d of them at offset %d", count, offset));
	}
	else {

		if (_hoops_IPRI->local_face_attributes.normals == null)
			HI_Initialize_Face_Attributes (_hoops_IPRI, LFA_EXPLICIT_NORMAL);

		_hoops_ARPA *				_hoops_HICSA = &_hoops_IPRI->local_face_attributes.normals[offset];
		_hoops_GIIPR *	flags = _hoops_IPRI->local_face_attributes._hoops_CHHPR(offset);

		if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
			if (offset != 0 || (offset + count) < _hoops_IPRI->face_count) {
				/* _hoops_SR _hoops_CHR _hoops_RGAR _hoops_HCHAR _hoops_HPGR _hoops_IRS _hoops_GIIAR _hoops_IIGR _hoops_RH _hoops_RSSI, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS _hoops_CCPP _hoops_IRS _hoops_RHRHR->_hoops_SGI _hoops_CRPR.*/
				ZALLOC_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
				for (int i = 0; i < _hoops_IPRI->face_count; i++)
					_hoops_IPRI->local_face_attributes.flags[i] = *flags;
				_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
				flags = _hoops_IPRI->local_face_attributes._hoops_CHHPR(offset);

			}
			else {
				/* _hoops_SR _hoops_CHR _hoops_GHGA _hoops_RGR _hoops_IS _hoops_RCSAR _hoops_HSP, _hoops_PPR _hoops_SSIA _hoops_CHR _hoops_HCR _hoops_GHRHR _hoops_PRGPR _hoops_SGIP, _hoops_HIS _hoops_IIS'_hoops_GRI _hoops_GRHP _hoops_SCH _hoops_SGS _hoops_PPRRR */
			}
		}

		do {
			if (!BIT (*flags, LFA_EXPLICIT_NORMAL)) {
				*flags |= LFA_EXPLICIT_NORMAL;
				if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR))
					++_hoops_IPRI->local_face_attributes.explicit_normal_count; 
				else
					_hoops_IPRI->local_face_attributes.explicit_normal_count += count; 
			}
			_hoops_HICSA->a = normals->x;
			_hoops_HICSA->b = normals->y;
			_hoops_HICSA->c = normals->z;

			++_hoops_HICSA;
			++normals;
			if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR))
				++flags;
		} _hoops_RGGA (--count == 0);

		if (BIT (_hoops_IPRI->polyhedron_flags, PHF_FACE_NORMALS_VALID)) {
			/* _hoops_HSP _hoops_ASGA _hoops_AAPR _hoops_PGCPR _hoops_IS _hoops_IHGSR */
			_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR|_hoops_RPSIR);
		}
		else {
			/* _hoops_AGGCI _hoops_IPIH _hoops_PGGCI */
			_hoops_SASIR (context, _hoops_IPRI, _hoops_CAHRA);
		}

		if (_hoops_IPRI->local_face_attributes.explicit_normal_count == _hoops_IPRI->face_count)
			_hoops_IPRI->polyhedron_flags |= PHF_FACE_NORMALS_VALID;
	}

	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_MUnSet_Face_Normals (
	Key								key,
	int								offset,
	int								count) 
{
	_hoops_PAPPR context("MUnSet_Face_Normals");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#else

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Face_Normals (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d);}\n", offset, count));
	);

	if (offset < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_OFFSET, "Offset is negative");
		return;
	}

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_HCGPP)) == null)
		return;

	bool	_hoops_GCSII = true;

	if (count == -1) {
		count = _hoops_IPRI->face_count - offset;
		_hoops_GCSII = false;
	}

	if (count == 0) {
		; // _hoops_CPRSH
	}
	else if (count < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_COUNT, "Count is negative");
	}
	else if (_hoops_IPRI->face_count < offset + count) {
		char	buf[MAX_ERRMSG];
		HE_ERROR2 (HEC_MSET_FACE, HES_INVALID_OFFSET,
			Sprintf_D (null, "Shell or mesh only has %d faces -", _hoops_IPRI->face_count),
			Sprintf_DD (buf, "can't change %d of them at offset %d", count, offset));
	}
	else {

		Local_Face_Attributes *	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;

		if (_hoops_CPRI->explicit_normal_count == 0) {
			/* _hoops_ISAP _hoops_ARP _hoops_RPP _hoops_PSP _hoops_SGI, _hoops_HIS _hoops_SAHR _hoops_PSIIR & _hoops_CASI _hoops_GH */
			HE_WARNING (HEC_MUNSET, HES_MISSING, "No normals to UnSet");
		}
		else {

			bool	_hoops_AHPGR = false;
			
			// _hoops_SR'_hoops_ASAR _hoops_HGGCI _hoops_HCR _hoops_ASGA
			if (offset == 0 && count == _hoops_IPRI->face_count) {
				if (_hoops_CPRI->explicit_normal_count != _hoops_IPRI->face_count)
					_hoops_AHPGR = true;

				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR))
					_hoops_CPRI->_hoops_SGRHR &= ~(LFA_EXPLICIT_NORMAL);
				else {
					_hoops_GIIPR *	flags = _hoops_CPRI->flags;
					do {
						*flags++ &= ~(LFA_EXPLICIT_NORMAL);
					} _hoops_RGGA (--count == 0);
				}
				_hoops_CPRI->explicit_normal_count = 0;
			}
			// _hoops_IASI _hoops_IPPRA
			else {
				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
					ZALLOC_ARRAY(_hoops_CPRI->flags, _hoops_IPRI->face_count, _hoops_GIIPR);
					for (int i = 0; i < _hoops_IPRI->face_count; i++)
						_hoops_CPRI->flags[i] = _hoops_CPRI->_hoops_SGRHR;
					_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
				}

				_hoops_GIIPR *	flags = &_hoops_CPRI->flags[offset];
				do {
					if (BIT (*flags, LFA_EXPLICIT_NORMAL)) {
						*flags &= ~LFA_EXPLICIT_NORMAL;
						--_hoops_CPRI->explicit_normal_count;
					}
					else
						_hoops_AHPGR = true;

					++flags;
				} _hoops_RGGA (--count == 0);
			}

			if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR) &&
				_hoops_CPRI->lff_uniform(_hoops_IPRI->face_count)) {
					_hoops_CPRI->_hoops_SGRHR = _hoops_CPRI->flags[0];
					FREE_ARRAY(_hoops_CPRI->flags, _hoops_IPRI->face_count, _hoops_GIIPR);
					_hoops_IPRI->polyhedron_flags &= ~_hoops_APRHR;
					_hoops_CPRI->flags = null;
			}

			if (_hoops_AHPGR && _hoops_GCSII)
				HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");

			if (_hoops_IPRI->tristrips != null) {
				_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;
				_hoops_SASIR (context, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
			}
		}
	}

	_hoops_IRRPR();
#endif
#endif
}

#define _hoops_IRGCI		0
#define _hoops_CRGCI			1


local int _hoops_SRGCI (
	_hoops_AIGPR *			_hoops_RIGC, 
	Key								key,
	int								offset,
	int								count,
	int const *						_hoops_SISII,
	unsigned char alter *			existence,
	Vector alter *					normals,
	int *							_hoops_HASII = null) 
{
	int								_hoops_IASII = 0;
	_hoops_GIIPR const *		flags;
	Local_Face_Attributes const *	_hoops_CPRI;
	Polyhedron const *				_hoops_IPRI;

	_hoops_CSPPR();

	if(_hoops_HASII)
		*_hoops_HASII = 0;
	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (_hoops_RIGC, key);

	if (_hoops_IPRI == null ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_GEOMETRY, HES_INVALID_KEY, "Key does not refer to valid geometry");
		if(_hoops_HASII)
			*_hoops_HASII = 1;
		goto Release;
	}
	else if (_hoops_IPRI->type != _hoops_SCIP && _hoops_IPRI->type != _hoops_GSIP) {
		if (_hoops_IPRI->type == _hoops_ASIP || 
			_hoops_IPRI->type == _hoops_CSIP || 
			_hoops_IPRI->type == _hoops_HSIP || 
			_hoops_IPRI->type == _hoops_PRCP)
			HE_ERROR (HEC_MSET_FACE, HES_INVALID_KEY, "MShow_Face_Normals not allowed for this primitive.  Try MShow_Net_Face_Normals.");
		else
			HE_ERROR (HEC_MSET_FACE, HES_INVALID_KEY, "Key does not refer to a valid shell or mesh");
		if(_hoops_HASII)
			*_hoops_HASII = 1;
		goto Release;
	}

	if (count < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_COUNT, "Count is negative");
		if(_hoops_HASII)
			*_hoops_HASII = 1;
		goto Release;
	}

	if(_hoops_SISII) 	{
		if (!_hoops_AISII (_hoops_IPRI, count, _hoops_SISII))
		{
			if(_hoops_HASII)
				*_hoops_HASII = 1;
			goto Release;
		}
	}
	else {
		if (offset < 0) {
			HE_ERROR (HEC_MSET_FACE, HES_INVALID_OFFSET, "Offset is negative");
			if(_hoops_HASII)
				*_hoops_HASII = 1;
			goto Release;
		}

		if (_hoops_IPRI->face_count < offset + count) {
			char			buf[MAX_ERRMSG];

			HE_ERROR2 (HEC_MSET_FACE, HES_INVALID_OFFSET,
					   Sprintf_D (null, "Shell or mesh only has %d faces -", _hoops_IPRI->face_count),
					   Sprintf_DD (buf, "can't show %d of them at offset %d", count, offset));
			if(_hoops_HASII)
				*_hoops_HASII = 1;
			goto Release;
		}
	}

	if (count == 0) 
		goto Release;  /* _hoops_CPRSH */

	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;

	if(existence)
		memset(existence, 0, count*sizeof(char));

	if (_hoops_CPRI->normals == null || _hoops_CPRI->explicit_normal_count == 0)
		goto Release;

	if(_hoops_SISII){
		for(int i=0; i<count; ++i)
		{
			flags = _hoops_CPRI->_hoops_CHHPR(_hoops_SISII[i]);
			if(BIT(*flags, LFA_EXPLICIT_NORMAL)) {
				if(normals)
					normals[i] = _hoops_CPRI->normals[_hoops_SISII[i]];
				if(existence)
					existence[i] = _hoops_CRGCI;
				++_hoops_IASII;
			}
		}
	}
	else {
		for(int i=0; i<count; ++i)
		{
			flags = _hoops_CPRI->_hoops_CHHPR(offset+i);
			if(BIT(*flags, LFA_EXPLICIT_NORMAL)) {
				if(normals)
					normals[i] = _hoops_CPRI->normals[offset+i];
				if(existence)
					existence[i] = _hoops_CRGCI;
				++_hoops_IASII;
			}
		}
	}	

  Release:
	_hoops_IRRPR();
	return _hoops_IASII;
}


HC_INTERFACE void HC_CDECL HC_MShow_Face_Normals (
	Key								key,
	int								offset,
	int								count,
	Vector alter *					normals) 
{
	_hoops_PAPPR context("MShow_Face_Normals");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef _hoops_HCGHR
	_hoops_IRPPR ("Geometry Normals");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Face_Normals () */\n");
	);

	int _hoops_HASII;
	int _hoops_IASII = _hoops_SRGCI(context, key, offset, count, null, null, normals, &_hoops_HASII);

	//_hoops_RPP _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_RHHS _hoops_PCCP _hoops_RIHH, _hoops_SAHR _hoops_CASI _hoops_GH _hoops_PPR _hoops_PHHR _hoops_RISII
	if(_hoops_HASII)
		return;

	//_hoops_RARIR
	if (_hoops_IASII != count) {
		HE_ERROR (HEC_NORMAL, HES_NO_LOCAL_SETTING,
				  "Not all face normals are explicitly set in the specified range");
		return;
	}


#endif
#endif
}

HC_INTERFACE int HC_CDECL HC_MShow_Face_Normals_W_Ex (
	Key					key,
	int					offset,
	int					count,
	char alter *		_hoops_GRGCI,
	Vector alter *		normals) 
{
	_hoops_PAPPR context("MShow_Face_Normals_With_Existence");

	unsigned char alter *	existence = (unsigned char alter *)_hoops_GRGCI;

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return 0;
#else
#ifdef _hoops_HCGHR
	_hoops_IRPPR ("Geometry Normals");
	return 0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Face_Normals_With_Existence () */\n");
	);

	int _hoops_IASII = _hoops_SRGCI(context, key, offset, count, null, existence, normals);

	return _hoops_IASII;
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_MSet_Specific_Face_Normals (
	Key						key,
	int						count,
	int const *				indices,
	Vector const *			normals) 
{
	_hoops_PAPPR context("MSet_Specific_Face_Normals");

#ifdef _hoops_HCGHR
	_hoops_IRPPR ("Geometry Normals");
#else
	CODE_GENERATION (
		int		count2 = count;
		HI_Dump_Code("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "Vector* normals = (Vector*) malloc(sizeof(Vector)*%d);\n", count2));
		HI_Dump_Code (Sprintf_D (null, "int* indices = (int*) malloc(sizeof(int)*%d);\n", count2));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "normals[%d].x = %.6ff;  ", count2, normals[count2].x));
			HI_Dump_Code (_hoops_CHCHR (null, "normals[%d].y = %.6ff;  ", count2, normals[count2].y));
			HI_Dump_Code (_hoops_CHCHR (null, "normals[%d].z = %.6ff;\n", count2, normals[count2].z));
			HI_Dump_Code (Sprintf_DD (null, "indices[%d] = %d;\n", count2, indices[count2]));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Specific_Face_Normals (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_D (null, "%d, indices, normals);\n", count));
		HI_Dump_Code ("free (normals);\n");
		HI_Dump_Code ("free (indices);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);


	if (count < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_COUNT, "Count is negative");
		return;
	}

	if (count == 0) 
		return;  /* _hoops_CPRSH */

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_HCGPP)) == null)
		return;

	if (_hoops_IPRI->face_count < count) {
		char	buf[MAX_ERRMSG];
		HE_ERROR2 (HEC_MSET_FACE, HES_INVALID_OFFSET,
				   Sprintf_D (null, "Shell or mesh only has %d faces -", _hoops_IPRI->face_count),
				   Sprintf_D (buf, "can't change %d of them", count));
	}
	else if (_hoops_PRSII (_hoops_IPRI, count, indices)) {

		if (_hoops_IPRI->local_face_attributes.normals == null)
			HI_Initialize_Face_Attributes (_hoops_IPRI, LFA_EXPLICIT_NORMAL);

		Local_Face_Attributes *	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;
		_hoops_ARPA *					_hoops_HICSA = _hoops_CPRI->normals;
		_hoops_GIIPR *		flags = _hoops_CPRI->_hoops_CHHPR(0);

		/* _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_RGSR _hoops_SASI _hoops_PPR _hoops_SR'_hoops_ASAR _hoops_GHRHR, _hoops_HPCAR _hoops_SR _hoops_CHR _hoops_RRGCI _hoops_ARGCI.  _hoops_SCH'_hoops_GRI _hoops_HAH _hoops_ACIPR _hoops_IS _hoops_SHAC _hoops_CGIRA _hoops_IAII _hoops_CCA _hoops_PRGCI _hoops_CR _hoops_SR'_hoops_ASAR _hoops_PSAR _hoops_GCAS _hoops_HRGCI _hoops_IPSP _hoops_PSPI */
		if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
			ZALLOC_ARRAY(_hoops_CPRI->flags, _hoops_IPRI->face_count, _hoops_GIIPR);
			for (int i = 0; i < _hoops_IPRI->face_count; i++)
				_hoops_CPRI->flags[i] = *flags;
			_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
		}

		do {
			int	index = *indices++;

			if (!BIT (*_hoops_CPRI->_hoops_CHHPR(index), LFA_EXPLICIT_NORMAL)) {
				*_hoops_CPRI->_hoops_CHHPR(index) |= LFA_EXPLICIT_NORMAL;
				++_hoops_CPRI->explicit_normal_count; 
			}

			_hoops_HICSA[index].a = normals->x;
			_hoops_HICSA[index].b = normals->y;
			_hoops_HICSA[index].c = normals->z;

			++normals;
		} _hoops_RGGA (--count == 0);

		if (BIT (_hoops_IPRI->polyhedron_flags, PHF_FACE_NORMALS_VALID)) {
			/* _hoops_HSP _hoops_ASGA _hoops_AAPR _hoops_PGCPR _hoops_IS _hoops_IHGSR */
			_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR|_hoops_RPSIR);
		}
		else {
			/* _hoops_AGGCI _hoops_IPIH _hoops_PGGCI */
			_hoops_SASIR (context, _hoops_IPRI, _hoops_CAHRA);
		}

		if (_hoops_IPRI->local_face_attributes.explicit_normal_count == _hoops_IPRI->face_count)
			_hoops_IPRI->polyhedron_flags |= PHF_FACE_NORMALS_VALID;
	}

	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_MUnSet_Specific_Face_Normals (
	Key								key,
	int								count,
	int	const *						indices) 
{
	_hoops_PAPPR context("MUnSet_Specific_Face_Normals");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#else

	CODE_GENERATION (
		int		count2 = count;
		if (count == 0) { 
			HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Specific_Face_Normals (LOOKUP (%D),  0, 0);\n", key));
		}
		else {
			HI_Dump_Code ("{\n");
			++HOOPS_WORLD->_hoops_ISPPR;
			HI_Dump_Code (Sprintf_D (null, "int* indices = (int*) malloc(sizeof(int)*%d);\n", count2));
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (Sprintf_DD (null, "indices[%d] = %d;\n", count2, indices[count2]));
			}
			HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Specific_Face_Normals (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_D (null, "%d, indices);\n", count));
			HI_Dump_Code ("free (indices);\n");
			--HOOPS_WORLD->_hoops_ISPPR;
			HI_Dump_Code ("}\n");
		}
	);


	if (count < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_COUNT, "Count is negative");
		return;
	}

	if (count == 0)
		return;  /* _hoops_CPRSH */

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_HCGPP)) == null)
		return;

	if (_hoops_IPRI->face_count < count) {
		char	buf[MAX_ERRMSG];
		HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
			Sprintf_D (null, "Shell or mesh only has %d faces -", _hoops_IPRI->face_count),
			Sprintf_D (buf, "can't change %d of them", count));
	}
	else if (_hoops_AISII (_hoops_IPRI, count, indices)) {

		Local_Face_Attributes *	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;

		if (_hoops_CPRI->explicit_normal_count == 0) {
			/* _hoops_ISAP _hoops_ARP _hoops_RPP _hoops_PSP _hoops_SGI, _hoops_HIS _hoops_SAHR _hoops_PSIIR & _hoops_CASI _hoops_GH */
			HE_WARNING (HEC_MUNSET, HES_MISSING, "No normals to UnSet");
		}
		else {

			/* _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_HGGCI _hoops_SASI _hoops_PPR _hoops_SR'_hoops_ASAR _hoops_GHRHR, _hoops_HPCAR _hoops_SR _hoops_CHR _hoops_RRGCI _hoops_ARGCI.  _hoops_SCH'_hoops_GRI _hoops_HAH _hoops_ACIPR _hoops_IS _hoops_SHAC _hoops_CGIRA _hoops_IAII _hoops_CCA _hoops_PRGCI _hoops_CR _hoops_SR'_hoops_ASAR _hoops_PSAR _hoops_GCAS _hoops_HRGCI _hoops_IPSP _hoops_PSPI */
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
				ZALLOC_ARRAY(_hoops_CPRI->flags, _hoops_IPRI->face_count, _hoops_GIIPR);
				for (int i = 0; i < _hoops_IPRI->face_count; i++)
					_hoops_CPRI->flags[i] = _hoops_CPRI->_hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
			}

			_hoops_GIIPR *	flags = _hoops_IPRI->local_face_attributes._hoops_CHHPR(0);
			bool				_hoops_AHPGR = false;

			do {
				int			index = *indices++;

				if (BIT (flags[index], LFA_EXPLICIT_NORMAL)) {
					flags[index] &= ~LFA_EXPLICIT_NORMAL;
					--_hoops_CPRI->explicit_normal_count;
				}
				else
					_hoops_AHPGR = true;
			} _hoops_RGGA (--count == 0);

#if 0
			/* _hoops_PAHH _hoops_HHGC _hoops_IS _hoops_IHIS _hoops_RGR _hoops_CRGR _hoops_SGGC */
			if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR) &&
				_hoops_CPRI->lff_uniform(_hoops_IPRI->face_count)) {
					_hoops_CPRI->_hoops_SGRHR = _hoops_CPRI->flags[0];
					FREE_ARRAY(_hoops_CPRI->flags, _hoops_IPRI->face_count, _hoops_GIIPR);
					_hoops_IPRI->polyhedron_flags &= ~_hoops_APRHR;
					_hoops_CPRI->flags = null;
			}
#endif
			if (_hoops_AHPGR)
				HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");

			if (_hoops_IPRI->tristrips != null) {
				_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;
				_hoops_SASIR (context, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
			}
		}
	}

	_hoops_IRRPR();
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_MShow_Specific_Face_Normals (
	Key								key,
	int								count,
	int const *						indices,
	Vector alter *					normals) 
{	
	_hoops_PAPPR context("MShow_Specific_Face_Normals");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Specific_Face_Normals () */\n");
	);

	int	_hoops_HASII;
	int	_hoops_IASII = _hoops_SRGCI(context, key, 0, count, indices, null, normals, &_hoops_HASII);

	//_hoops_RPP _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_RHHS _hoops_PCCP _hoops_RIHH, _hoops_SAHR _hoops_CASI _hoops_GH _hoops_PPR _hoops_PHHR _hoops_RISII
	if(_hoops_HASII)
		return;

	//_hoops_RARIR
	if (_hoops_IASII != count) {
		HE_ERROR (HEC_NORMAL, HES_NO_LOCAL_SETTING, "Not all face normals are explicitly set in the specified range");
		return;
	}

#endif
#endif
}

HC_INTERFACE int HC_CDECL HC_MShow_Spec_Face_Normals_W_Ex (
	Key					key,
	int					count,
	int const *			indices,
	char alter *		_hoops_GRGCI,
	Vector alter *		_hoops_IICII) 
{
	_hoops_PAPPR context("MShow_Specific_Face_Normals_With_Existence");

	unsigned char alter *	existence = (unsigned char alter *)_hoops_GRGCI;

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return 0;
#else
#ifdef _hoops_HCGHR
	_hoops_IRPPR ("Geometry Normals");
	return 0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Specific_Face_Normals_With_Existence () */\n");
	);

	int _hoops_IASII = _hoops_SRGCI(context, key, 0, count, indices, existence, _hoops_IICII);

	return _hoops_IASII;
#endif
#endif
}


/* _hoops_GAGCI _hoops_SRPC _hoops_RAGCI _hoops_AAGCI ( */


/* _hoops_GAGCI _hoops_SRPC _hoops_RAGCI _hoops_PAGCI ( */


HC_INTERFACE void HC_CDECL HC_MShow_Net_Vertex_Normals (
	Key							key,
	int							offset,
	int							count,
	Vector alter *				normals) 
{	
	_hoops_PAPPR context("MShow_Net_Vertex_Normals");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef _hoops_HCGHR
	_hoops_IRPPR ("Geometry Normals");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Net_Vertex_Normals () */\n");
	);

	Vector const *				_hoops_AHAHR;
	Local_Vertex_Flags const *	flags;
	Shell *						victim = null;

	_hoops_CSPPR();

	Polyhedron *	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (context, key);
	if (_hoops_IPRI == null ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_GEOMETRY, HES_INVALID_KEY, "Key does not refer to valid geometry");
		goto Release;
	}
	else if (_hoops_IPRI->type != _hoops_SCIP && _hoops_IPRI->type != _hoops_GSIP) {
		HI_Convert_To_Shell (context, null, (Geometry *)_hoops_IPRI, (Shell **)&_hoops_IPRI, &victim);
		if (_hoops_IPRI->type != _hoops_SCIP) {
			HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_KEY, "Key does not refer to valid shell, mesh, nurbs surface, cylinder, polycylinder or sphere");
			goto Release;
		}
	}

	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		goto Release;
	}

	if (offset < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_OFFSET, "Offset is negative");
		goto Release;
	}

	if (_hoops_IPRI->point_count < offset + count) {
		char			buf[MAX_ERRMSG];

		HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
				   Sprintf_D (null, "Shell or mesh only has %d vertices -", _hoops_IPRI->point_count),
				   Sprintf_DD (buf, "can't show %d of them at offset %d", count, offset));
		goto Release;
	}

	if (count == 0) 
		goto Release;  /* _hoops_CPRSH */

	if (_hoops_IPRI->local_vertex_attributes.normals == null)
		HI_Assemble_Vertex_Normals (_hoops_IPRI);

	flags = _hoops_IPRI->local_vertex_attributes._hoops_CHHPR(offset);

	_hoops_AHAHR = &_hoops_IPRI->local_vertex_attributes.normals[offset];

	do {
		*normals++ = *_hoops_AHAHR++;
	} _hoops_RGGA (--count == 0);

  Release:
	if (victim)
		HI_Au_Revoir ((_hoops_HPAH *)victim);
	_hoops_IRRPR();
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_MShow_Net_Face_Normals (
	Key							key,
	int							offset,
	int							count,
	Vector alter *				_hoops_IICII) 
{
	_hoops_PAPPR context("MShow_Net_Face_Normals");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef _hoops_HCGHR
	_hoops_IRPPR ("Geometry Normals");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Net_Face_Normals () */\n");
	);

	Vector alter *				normals = (Vector alter *)_hoops_IICII;
	_hoops_ARPA const *				_hoops_HICSA;
	_hoops_GIIPR const *	flags;
	Shell *						victim = null;

	_hoops_CSPPR();

	Polyhedron *	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (context, key);
	if (_hoops_IPRI == null ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_GEOMETRY, HES_INVALID_KEY, "Key does not refer to valid geometry");
		goto Release;
	}
	else if (_hoops_IPRI->type != _hoops_SCIP && _hoops_IPRI->type != _hoops_GSIP) {
		HI_Convert_To_Shell (context, null, (Geometry *)_hoops_IPRI, (Shell **)&_hoops_IPRI, &victim);
		if (_hoops_IPRI->type != _hoops_SCIP) {
			HE_ERROR (HEC_MSET_FACE, HES_INVALID_KEY, "Key does not refer to valid shell, mesh, nurbs surface, cylinder, polycylinder or sphere");
			goto Release;
		}
	}

	if (count < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_COUNT, "Count is negative");
		goto Release;
	}

	if (offset < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_OFFSET, "Offset is negative");
		goto Release;
	}

	if (_hoops_IPRI->face_count < offset + count) {
		char			buf[MAX_ERRMSG];

		HE_ERROR2 (HEC_MSET_FACE, HES_INVALID_OFFSET,
				   Sprintf_D (null, "Shell or mesh only has %d faces -", _hoops_IPRI->face_count),
				   Sprintf_DD (buf, "can't show %d of them at offset %d", count, offset));
		goto Release;
	}

	if (count == 0) 
		goto Release;  /* _hoops_CPRSH */

	if (_hoops_IPRI->local_face_attributes.normals == null)
		HI_Assemble_Face_Normals (_hoops_IPRI);

	flags = _hoops_IPRI->local_face_attributes._hoops_CHHPR(offset);

	_hoops_HICSA = &_hoops_IPRI->local_face_attributes.normals[offset];

	do {
		*normals++ = *_hoops_HICSA++;
	} _hoops_RGGA (--count == 0);

  Release:
	if (victim)
		HI_Au_Revoir ((_hoops_HPAH *)victim);
	_hoops_IRRPR();
#endif
#endif
}



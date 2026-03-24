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
* $Id: obf_tmp.txt 1.15 2010-10-06 19:16:36 jason Exp $
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
	int const *				indices) 
{

	for (int i=0; i<count; i++) {
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

HC_INTERFACE void HC_CDECL HC_MSet_Vertex_Visibilities (
	Key				key,
	int				offset,
	int				count,
	char const *	_hoops_IPGCI) 
{
	_hoops_PAPPR context("MSet_Vertex_Visibilities");

	unsigned char const *	visibilities = (unsigned char const *)_hoops_IPGCI;

#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#else

	CODE_GENERATION (
		int		count2 = count;
		if (count == 0) { 
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Vertex_Visibilities (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_D (null, "%d, 0, 0);\n", offset));
		}
		else {
			HI_Dump_Code (Sprintf_D (null, "{char* visibilities = (char*) malloc(sizeof(char)*%d);\n", count2));
			++HOOPS_WORLD->_hoops_ISPPR;
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (Sprintf_DD (null, "visibilities[%d] = %d;\n", count2, (unsigned int)visibilities[count2]));
			}
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Vertex_Visibilities (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_DD (null, "%d, %d, visibilities);\n", offset, count));
			HI_Dump_Code ("free (visibilities);\n");
			--HOOPS_WORLD->_hoops_ISPPR;
			HI_Dump_Code ("}\n");
		}
	);

	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		return;
	}
	if (offset < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_OFFSET, "Offset is negative");
		return;
	}

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_CCGPP)) == null)
		return;

	if (_hoops_IPRI->point_count < offset + count) {
		char	buf[MAX_ERRMSG];
		HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
			Sprintf_D (null, "Shell or mesh only has %d vertices -", _hoops_IPRI->point_count),
			Sprintf_DD (buf, "can't change %d of them at offset %d", count, offset));
	}
	else {
		
		Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

		if (_hoops_SPRI->flags == null)
			HI_Initialize_Vertex_Attributes(_hoops_IPRI, 0, 0);

		bool done = false;

		if (offset == 0 && count == _hoops_IPRI->point_count) {

			bool	_hoops_CPGCI = true;

			for (int i = 0; i < count; i++) {
				if (*visibilities != visibilities[i]) {
					_hoops_CPGCI = false;
					break;	
				}
			}

			/* _hoops_RCSII _hoops_HCR _hoops_RSSI. _hoops_CHR _hoops_SR _hoops_RGSR _hoops_CAPR _hoops_HCR _hoops_IS _hoops_PSHR _hoops_HPRC? */
			if (_hoops_CPGCI && !BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				
				bool	erase = false;

				/* _hoops_PS _hoops_PAH _hoops_SAHR _hoops_SGH _hoops_RH _hoops_GHRHR _hoops_RIP */
				if (visibilities[0]) { /* _hoops_IAHAR _hoops_SCH _hoops_GPP */
					if (!BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_PHIAA)) {
						if (BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_HHIAA)) {
							_hoops_SPRI->_hoops_SGRHR &= ~_hoops_HHIAA;
							_hoops_SPRI->_hoops_SIIPR -= count;
						}
						_hoops_SPRI->_hoops_SGRHR |= _hoops_PHIAA;
						_hoops_SPRI->_hoops_CPIAA += count;
					}
				}
				else {
					if (!BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_HHIAA)) {
						if (BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_PHIAA)) {
							_hoops_SPRI->_hoops_SGRHR &= ~_hoops_PHIAA;
							_hoops_SPRI->_hoops_CPIAA -= count;
						}
						_hoops_SPRI->_hoops_SGRHR |= _hoops_HHIAA;
						_hoops_SPRI->_hoops_SIIPR += count;
						erase = true;
					}
				}

				if (_hoops_IPRI->tristrips != null) {
					_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;

					if (erase)
						_hoops_SASIR (context, _hoops_IPRI, _hoops_AISSR|
						_hoops_CSCCA|
						_hoops_RPSIR);
					else
						_hoops_SASIR (context, _hoops_IPRI, _hoops_IHSSR | _hoops_SIGPR |
						_hoops_RPSIR);
				}
				done = true;
			}
		}

		if (!done) {

			/* _hoops_RCSII _hoops_IRS _hoops_GIIAR _hoops_PAR _hoops_HAR _hoops_HCR _hoops_RH _hoops_PSHR, _hoops_HHSA _hoops_CRPR _hoops_RPP _hoops_SIGR */
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
				for (int i = 0; i < _hoops_IPRI->point_count; i++)
					_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
			}

			Local_Vertex_Flags *	flags = _hoops_SPRI->_hoops_CHHPR(offset);

			bool	erase = false;

			do {
				unsigned char	_hoops_RGP = *visibilities;

				if (_hoops_RGP) { /* _hoops_IAHAR _hoops_SCH _hoops_GPP */
					if (!BIT (*flags, _hoops_PHIAA)) {
						if (BIT (*flags, _hoops_HHIAA)) {
							*flags &= ~_hoops_HHIAA;
							--_hoops_SPRI->_hoops_SIIPR;
						}
						*flags |= _hoops_PHIAA;
						++_hoops_SPRI->_hoops_CPIAA;
					}
				}
				else {
					if (!BIT (*flags, _hoops_HHIAA)) {
						if (BIT (*flags, _hoops_PHIAA)) {
							*flags &= ~_hoops_PHIAA;
							--_hoops_SPRI->_hoops_CPIAA;
						}
						*flags |= _hoops_HHIAA;
						++_hoops_SPRI->_hoops_SIIPR;
						erase = true;
					}
				}

				++flags;
				++visibilities;
			} _hoops_RGGA (--count == 0);

			if (_hoops_IPRI->tristrips != null) {
				_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;

				if (erase)
					_hoops_SASIR (context, _hoops_IPRI, _hoops_AISSR|_hoops_CSCCA|_hoops_RPSIR);
				else
					_hoops_SASIR (context, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
			}
		}
	}

	_hoops_IRRPR();
#endif
}

#define _hoops_SPGCI	0
#define _hoops_GHGCI		1

local int _hoops_RHGCI(
	_hoops_AIGPR *			_hoops_RIGC, 
	Key								key,
	int								offset,
	int								count,
	int const *						specific_vertices,
	unsigned char alter *			existence,
	unsigned char alter *			visibilities,
	int *							_hoops_HASII = null) 
{
	int								_hoops_IASII = 0;
	Local_Vertex_Flags const *		flags;
	Local_Vertex_Attributes const *	_hoops_SPRI;
	Polyhedron const *				_hoops_IPRI;

	_hoops_CSPPR();

	if(_hoops_HASII)
		*_hoops_HASII = 0;
	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (_hoops_RIGC, key);

	if (_hoops_IPRI == null ||
		(_hoops_IPRI->type != _hoops_SCIP && _hoops_IPRI->type != _hoops_GSIP) ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_VISIBILITY, HES_INVALID_KEY, "Key does not refer to a valid Shell or Mesh");
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
				Sprintf_D (null, "Shell or mesh only has %d vertices -", _hoops_IPRI->face_count),
				Sprintf_DD (buf, "can't change %d of them at offset %d", count, offset));
			if(_hoops_HASII)
				*_hoops_HASII = 1;
			goto Release;
		}
	}

	if (count == 0) goto Release;  /* _hoops_CPRSH */

	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

	if(existence)
		memset(existence, 0, count*sizeof(char));

	if ((_hoops_SPRI->flags == null && BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) ||
		(_hoops_SPRI->_hoops_SGRHR == 0 && !BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR))) {
		/* _hoops_ISAP _hoops_ARP _hoops_RPP _hoops_PSP _hoops_SGI, _hoops_HIS _hoops_SAHR _hoops_PSIIR & _hoops_CASI _hoops_GH */
		goto Release;
	}

	if(specific_vertices){
		for(int i=0; i<count; ++i)
		{
			flags = _hoops_SPRI->_hoops_CHHPR(specific_vertices[i]);
			if(BIT(*flags, _hoops_CIICA)) {
				if(visibilities)
					visibilities[i] = BIT (*flags, _hoops_PHIAA);
				if(existence)
					existence[i] = _hoops_GHGCI;
				++_hoops_IASII;
			}
		}
	}
	else {
		for(int i=0; i<count; ++i)
		{
			flags = _hoops_SPRI->_hoops_CHHPR(offset+i);
			if(BIT(*flags, _hoops_CIICA)) {
				if(visibilities)
					visibilities[i] = BIT (*flags, _hoops_PHIAA);
				if(existence)
					existence[i] = _hoops_GHGCI;
				++_hoops_IASII;
			}
		}
	}	

Release:
	_hoops_IRRPR();
	return _hoops_IASII;
}


HC_INTERFACE void HC_CDECL HC_MShow_Vertex_Visibilities (
	Key				key,
	int				offset,
	int				count,
	char alter *	_hoops_IPGCI) 
{
	_hoops_PAPPR context("MShow_Vertex_Visibilities");

	unsigned char alter *	visibilities = (unsigned char alter *)_hoops_IPGCI;

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#	ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#	else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Vertex_Visibilities () */\n");
	);

	int	_hoops_HASII;

	int _hoops_IASII = _hoops_RHGCI(context, key, offset, count, null, null, visibilities, &_hoops_HASII);

	//_hoops_RPP _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_RHHS _hoops_PCCP _hoops_RIHH, _hoops_SAHR _hoops_CASI _hoops_GH _hoops_PPR _hoops_PHHR _hoops_RISII
	if(_hoops_HASII)
		return;

	//_hoops_RARIR
	if (count != _hoops_IASII) {
		HE_ERROR (HEC_VISIBILITY, HES_NO_LOCAL_SETTING, 
			"Not all vertex visibilities are explicitly set in the specified range");
		return;
	}

#	endif
#endif
}


HC_INTERFACE void HC_CDECL HC_MUnSet_Vertex_Visibilities (
	Key								key,
	int								offset,
	int								count) 
{
	_hoops_PAPPR context("MUnSet_Vertex_Visibilities");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#else

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Vertex_Visibilities (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d);}\n", offset, count));
	);

	if (offset < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_OFFSET, "Offset is negative");
		return;
	}

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_CCGPP)) == null)
		return;

	bool	_hoops_AHPGR = false;
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

		if (_hoops_SPRI->_hoops_SIIPR + _hoops_SPRI->_hoops_CPIAA == 0) {
			/* _hoops_ISAP _hoops_ARP _hoops_RPP _hoops_PSP _hoops_SGI, _hoops_HIS _hoops_SAHR _hoops_PSIIR & _hoops_CASI _hoops_GH */
			HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");
		}
		else {

			bool	erase = false;

			if (offset == 0 && count == _hoops_IPRI->point_count) {
				if (_hoops_SPRI->_hoops_SIIPR + _hoops_SPRI->_hoops_CPIAA != _hoops_IPRI->point_count)
					_hoops_AHPGR = true;

				if (_hoops_SPRI->_hoops_CPIAA != 0)
					erase = true;	// _hoops_CPIC _hoops_HII '_hoops_GPP' _hoops_IS '_hoops_RHGC' _hoops_SIAS _hoops_HA _hoops_CAPGP '_hoops_PSAP'

				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR))
					_hoops_SPRI->_hoops_SGRHR &= ~(_hoops_HHIAA|_hoops_PHIAA);
				else {
					Local_Vertex_Flags *	flags = _hoops_SPRI->flags;
					do {
						*flags++ &= ~(_hoops_HHIAA|_hoops_PHIAA);
					} _hoops_RGGA (--count == 0);
				}
				_hoops_SPRI->_hoops_SIIPR = 0;
				_hoops_SPRI->_hoops_CPIAA = 0;
			}
			else {

				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
					ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
					for (int i = 0; i < _hoops_IPRI->point_count; i++)
						_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
					_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
				}

				Local_Vertex_Flags *	flags = &_hoops_SPRI->flags[offset];
				do {
					if (BIT (*flags, _hoops_HHIAA)) {
						*flags &= ~_hoops_HHIAA;
						--_hoops_SPRI->_hoops_SIIPR;
					}
					else if (BIT (*flags, _hoops_PHIAA)) {
						*flags &= ~_hoops_PHIAA;
						--_hoops_SPRI->_hoops_CPIAA;
						erase = true;	// _hoops_CPIC _hoops_HII '_hoops_GPP' _hoops_IS '_hoops_RHGC' _hoops_SIAS _hoops_HA _hoops_CAPGP '_hoops_PSAP'
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
				if (erase)
					_hoops_SASIR (context, _hoops_IPRI, _hoops_AISSR|_hoops_CSCCA|_hoops_RPSIR);
				else
					_hoops_SASIR (context, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
			}
		}
	}

	_hoops_IRRPR();
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_MSet_Specific_Vertex_Vis (
	Key				key,
	int				count,
	int const *		indices,
	char const *	_hoops_IPGCI) 
{
	_hoops_PAPPR context("HC_MSet_Specific_Vertex_Visibilities");

	unsigned char const *	visibilities = (unsigned char const *)_hoops_IPGCI;

#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#else


	CODE_GENERATION (
		int		count2 = count;
		if (count == 0) { 
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Specific_Vertex_Visibilities (LOOKUP (%D), 0, 0, 0);\n", key));
		}
		else {
			HI_Dump_Code (Sprintf_D (null, "{char* visibilities = (char*) malloc(sizeof(char)*%d);\n", count2));
			HI_Dump_Code (Sprintf_D (null, "int* indices = (int*) malloc(sizeof(int)*%d);\n", count2));
			++HOOPS_WORLD->_hoops_ISPPR;
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (Sprintf_DD (null, "visibilities[%d] = %d;\n",count2, (unsigned int)visibilities[count2]));
				HI_Dump_Code (Sprintf_DD (null, "indices[%d] = %d;\n",count2, indices[count2]));
			}
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Specific_Vertex_Visibilities (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_D (null, "%d, indices, visibilities);\n", count));
			HI_Dump_Code ("free (visibilities);\n");
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

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_CCGPP)) == null)
		return;

	if (_hoops_PRSII (_hoops_IPRI, count, indices)) {
		
		Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

		bool	_hoops_CPGCI = true;

		for (int i = 0; i < count; i++) {
			if (*visibilities != visibilities[i]) {
				_hoops_CPGCI = false;
				break;	
			}
		}

		if (count > _hoops_IPRI->point_count) {
			HE_WARNING (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Indices count exceeds vertex count.");
			count = _hoops_IPRI->point_count; // _hoops_SAIPR _hoops_SCH
		}

		bool	_hoops_GSSII = true;

		if (count < _hoops_IPRI->point_count) {
			/* _hoops_PAH'_hoops_RA _hoops_GCAS _hoops_SHH _hoops_RGSR _hoops_HCR _hoops_PSPI */
			_hoops_GSSII = false;
		}
		else {
			/* _hoops_RGR _hoops_RGAR _hoops_HCGC _hoops_RH _hoops_AGIR _hoops_CGPR _hoops_RH _hoops_PSPI _hoops_CHR _hoops_RGPSA,
			_hoops_APHR _hoops_HPGR _hoops_AHHR.  */
			for (int i = 0; i < count; i++) {
				if (i != indices[i]) {
					_hoops_GSSII = false;
					break;
				}
			}
		}

		bool done = false;

		if (_hoops_GSSII) {
			/* _hoops_RCSII _hoops_HCR _hoops_RSSI. _hoops_CHR _hoops_SR _hoops_RGSR _hoops_CAPR _hoops_HCR _hoops_IS _hoops_PSHR _hoops_HPRC? */
			if (_hoops_CPGCI && !BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {

				bool	erase = false;

				/* _hoops_PS _hoops_PAH _hoops_SAHR _hoops_SGH _hoops_RH _hoops_GHRHR _hoops_RIP */
				if (visibilities[0]) { /* _hoops_IAHAR _hoops_SCH _hoops_GPP */
					if (!BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_PHIAA)) {
						if (BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_HHIAA)) {
							_hoops_SPRI->_hoops_SGRHR &= ~_hoops_HHIAA;
							_hoops_SPRI->_hoops_SIIPR -= count;
						}
						_hoops_SPRI->_hoops_SGRHR |= _hoops_PHIAA;
						_hoops_SPRI->_hoops_CPIAA += count;
					}
				}
				else {
					if (!BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_HHIAA)) {
						if (BIT (_hoops_SPRI->_hoops_SGRHR, _hoops_PHIAA)) {
							_hoops_SPRI->_hoops_SGRHR &= ~_hoops_PHIAA;
							_hoops_SPRI->_hoops_CPIAA -= count;
						}
						_hoops_SPRI->_hoops_SGRHR |= _hoops_HHIAA;
						_hoops_SPRI->_hoops_SIIPR += count;
						erase = true;
					}
				}

				if (_hoops_IPRI->tristrips != null) {
					_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;

					if (erase)
						_hoops_SASIR (context, _hoops_IPRI, _hoops_AISSR|_hoops_CSCCA|_hoops_RPSIR);
					else
						_hoops_SASIR (context, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
				}
				done = true;
			}
		}

		if (!done) {
			
			/* _hoops_RGSR _hoops_IRS _hoops_GIIAR _hoops_PAR _hoops_HAR _hoops_HCR _hoops_RH _hoops_PSHR */
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
				for (int i = 0; i < _hoops_IPRI->point_count; i++)
					_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
			}

			bool	erase = false;

			do {
				unsigned char	_hoops_RGP = *visibilities++;
				int	index = *indices++;

				if (_hoops_RGP) { /* _hoops_IAHAR _hoops_SCH _hoops_GPP */
					if (!BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_PHIAA)) {
						if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_HHIAA)) {
							*_hoops_SPRI->_hoops_CHHPR(index) &= ~_hoops_HHIAA;
							--_hoops_SPRI->_hoops_SIIPR;
						}
						*_hoops_SPRI->_hoops_CHHPR(index) |= _hoops_PHIAA;
						++_hoops_SPRI->_hoops_CPIAA;
					}
				}
				else {
					if (!BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_HHIAA)) {
						if (BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_PHIAA)) {
							*_hoops_SPRI->_hoops_CHHPR(index) &= ~_hoops_PHIAA;
							--_hoops_SPRI->_hoops_CPIAA;
						}
						*_hoops_SPRI->_hoops_CHHPR(index) |= _hoops_HHIAA;
						++_hoops_SPRI->_hoops_SIIPR;
						erase = true;
					}
				}
			} _hoops_RGGA (--count == 0);

			if (_hoops_IPRI->tristrips != null) {
				_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;

				if (erase)
					_hoops_SASIR (context, _hoops_IPRI, _hoops_AISSR|_hoops_CSCCA|_hoops_RPSIR);
				else
					_hoops_SASIR (context, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
			}
		}
	}

	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_MShow_Specific_Vertex_Vis (
	Key				key,
	int				count,
	int const *		indices,
	char alter *	_hoops_IPGCI) 
{
	_hoops_PAPPR context("MShow_Specific_Vertex_Visibilities");

	unsigned char alter *	visibilities = (unsigned char alter *)_hoops_IPGCI;

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Specific_Vertex_Visibilities () */\n");
	);

	int	_hoops_HASII;
	int	_hoops_IASII = _hoops_RHGCI(context, key, 0, count, indices, null, visibilities, &_hoops_HASII);

	//_hoops_RPP _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_RHHS _hoops_PCCP _hoops_RIHH, _hoops_SAHR _hoops_CASI _hoops_GH _hoops_PPR _hoops_PHHR _hoops_RISII
	if(_hoops_HASII)
		return;

	//_hoops_RARIR
	if (count != _hoops_IASII) {
		HE_ERROR (HEC_VISIBILITY, HES_NO_LOCAL_SETTING, "Not all vertex visibilities are explicitly set in the specified range");
		return;
	}
#endif
#endif
}


HC_INTERFACE int HC_CDECL HC_MShow_Spec_Vertex_Vis_W_Ex (
	Key				key,
	int				count,
	int const *		indices,
	char alter *	_hoops_GRGCI,
	char alter *	_hoops_IPGCI) 
{
	_hoops_PAPPR context("MShow_Specific_Vertex_Visibilities_With_Existence");

	unsigned char alter *	existence = (unsigned char alter *)_hoops_GRGCI;
	unsigned char alter *	visibilities = (unsigned char alter *)_hoops_IPGCI;

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return 0;
#else
#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
	return 0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Specific_Vertex_Visibilities_With_Existence () */\n");
	);

	int _hoops_IASII = _hoops_RHGCI(context, key, 0, count, indices, existence, visibilities);

	return _hoops_IASII;
#endif
#endif	
}


HC_INTERFACE int HC_CDECL HC_MShow_Vertex_Vis_W_Ex (
	Key				key,
	int				offset,
	int				count,
	char alter *	_hoops_GRGCI,
	char alter *	_hoops_IPGCI) 
{
	_hoops_PAPPR context("MShow_Vertex_Visibilities_With_Existence");

	unsigned char alter *	existence = (unsigned char alter *)_hoops_GRGCI;
	unsigned char alter *	visibilities = (unsigned char alter *)_hoops_IPGCI;

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return 0;
#else
#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
	return 0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Vertex_Visibilities_With_Existence () */\n");
	);

	int _hoops_IASII = _hoops_RHGCI(context, key, offset, count, null, existence, visibilities);

	return _hoops_IASII;
#endif
#endif

}

HC_INTERFACE void HC_CDECL HC_MUnSet_Specific_Vertex_Vis (
	Key							key,
	int							count,
	int const *					indices) 
{
	_hoops_PAPPR context("MUnSet_Specific_Vertex_Visibilities");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#else

	CODE_GENERATION (
		int		count2 = count;
		if (count == 0) { 
			HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Specific_Vertex_Visibilities (LOOKUP (%D),  0, 0);\n", key));
		}
		else {
			HI_Dump_Code (Sprintf_D (null, "{int* indices = (int*) malloc(sizeof(int)*%d);\n", count2));
			++HOOPS_WORLD->_hoops_ISPPR;
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (Sprintf_DD (null, "indices[%d] = %d;\n", count2, indices[count2]));
			}
			HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Specific_Vertex_Visibilities (LOOKUP (%D), ", key));
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

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_CCGPP)) == null)
		return;

	if (_hoops_PRSII (_hoops_IPRI, count, indices)) {

		Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

		// _hoops_SIGP: _hoops_RHAP _hoops_HAR _hoops_RGHH _hoops_GHRHR _hoops_SGI
		if (_hoops_SPRI->_hoops_SIIPR + _hoops_SPRI->_hoops_CPIAA == 0) {
			/* _hoops_ISAP _hoops_ARP _hoops_RPP _hoops_PSP _hoops_SGI, _hoops_HIS _hoops_SAHR _hoops_PSIIR & _hoops_CASI _hoops_GH */
			HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");
		}
		else {

			// _hoops_IHGS _hoops_AHGCI _hoops_ARI, _hoops_HAR _hoops_IRCC _hoops_IS _hoops_CAHA _hoops_GGSR _hoops_RPP _hoops_SSIA _hoops_CHH _hoops_HCR _hoops_SHH _hoops_IPPRA
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
				for (int i = 0; i < _hoops_IPRI->point_count; i++)
					_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
			}

			Local_Vertex_Flags *	flags = _hoops_SPRI->flags;

			bool	erase = false;
			bool	_hoops_AHPGR = false;

			do {
				int			index = *indices++;

				if (BIT (flags[index], _hoops_HHIAA)) {
					flags[index] &= ~_hoops_HHIAA;
					--_hoops_SPRI->_hoops_SIIPR;
				}
				else if (BIT (flags[index], _hoops_PHIAA)) {
					flags[index] &= ~_hoops_PHIAA;
					--_hoops_SPRI->_hoops_CPIAA;
					erase = true; /* _hoops_CPIC _hoops_HII '_hoops_GPP' _hoops_IS '_hoops_RHGC' _hoops_SIAS _hoops_HA _hoops_CAPGP '_hoops_PSAP' */
				}
				else
					_hoops_AHPGR = true;
			} _hoops_RGGA (--count == 0);

			if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR) &&
				_hoops_SPRI->lvf_uniform(_hoops_IPRI->point_count)) {
				_hoops_SPRI->_hoops_SGRHR = _hoops_SPRI->flags[0];
				FREE_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
				_hoops_IPRI->polyhedron_flags &= ~_hoops_CGRHR;
				_hoops_SPRI->flags = null;
			}

			if (_hoops_AHPGR)
				HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");

			if (_hoops_IPRI->tristrips != null) {
				_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;
				if (erase)
					_hoops_SASIR (context, _hoops_IPRI, _hoops_AISSR|_hoops_CSCCA|_hoops_RPSIR);
				else
					_hoops_SASIR (context, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
			}
		}
	}

	_hoops_IRRPR();
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_MSet_Face_Visibilities (
	Key				key,
	int				offset,
	int				count,
	char const *	_hoops_IPGCI) 
{
	_hoops_PAPPR context("MSet_Face_Visibilities");

	unsigned char const *	visibilities = (unsigned char const *)_hoops_IPGCI;

#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#else


	CODE_GENERATION (
		int		count2 = count;
		if (count == 0) { 
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Face_Visibilities (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_D (null, "%d, 0, 0);\n", offset));
		}
		else {
			HI_Dump_Code (Sprintf_D (null, "{unsigned char* visibilities = (unsigned char*) malloc(sizeof(unsigned char)*%d);\n", count2));
			++HOOPS_WORLD->_hoops_ISPPR;
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (Sprintf_DD (null, "visibilities[%d] = %f;\n", count2, visibilities[count2]));
			}
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Face_Visibilities (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_DD (null, "%d, %d, visibilities);\n", offset, count));
			HI_Dump_Code ("free (visibilities);\n");
			--HOOPS_WORLD->_hoops_ISPPR;
			HI_Dump_Code ("}\n");
		}
	);


	if (count < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_COUNT, "Count is negative");
		return;
	}
	if (offset < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_OFFSET, "Offset is negative");
		return;
	}

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_CCGPP)) == null)
		return;

	if (_hoops_IPRI->face_count < offset + count) {
		char	buf[MAX_ERRMSG];
		HE_ERROR2 (HEC_MSET_FACE, HES_INVALID_OFFSET,
				   Sprintf_D (null, "Shell or mesh only has %d faces -", _hoops_IPRI->face_count),
				   Sprintf_DD (buf, "can't change %d of them at offset %d", count, offset));
	}
	else {

		Local_Face_Attributes *	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;

		if (_hoops_CPRI->flags == null || *_hoops_CPRI->_hoops_CHHPR() == 0)
			HI_Initialize_Face_Attributes (_hoops_IPRI, 0);

		bool	_hoops_CPGCI = true;

		for (int i = 0; i < count; i++) {
			if (*visibilities != visibilities[i]) {
				_hoops_CPGCI = false;
				break;	
			}
		}

		bool	erase = false;
		bool	_hoops_PHGCI = false;

		bool	done = false;
		
		if (offset == 0 && count == _hoops_IPRI->face_count) {
			/* _hoops_RCSII _hoops_HCR _hoops_RSSI. _hoops_CHR _hoops_SR _hoops_RGSR _hoops_CAPR _hoops_HCR _hoops_IS _hoops_PSHR _hoops_HPRC? */
			if (_hoops_CPGCI && !BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
				/* _hoops_PS _hoops_PAH _hoops_SAHR _hoops_SGH _hoops_RH _hoops_GHRHR _hoops_RIP */
				if (visibilities[0]) { /* _hoops_IAHAR _hoops_SCH _hoops_GPP */
					if (!BIT (_hoops_CPRI->_hoops_SGRHR, _hoops_IAGI)) {
						if (BIT (_hoops_CPRI->_hoops_SGRHR, _hoops_HSIPR)) {
							_hoops_CPRI->_hoops_SGRHR &= ~_hoops_HSIPR;
							_hoops_CPRI->_hoops_SIIPR -= count;
							_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
						}
						_hoops_CPRI->_hoops_SGRHR |= _hoops_IAGI;
						_hoops_CPRI->_hoops_CPIAA += count;
					}
				}
				else {
					if (!BIT (_hoops_CPRI->_hoops_SGRHR, _hoops_HSIPR)) {
						if (BIT (_hoops_CPRI->_hoops_SGRHR, _hoops_IAGI)) {
							_hoops_CPRI->_hoops_SGRHR &= ~_hoops_IAGI;
							_hoops_CPRI->_hoops_CPIAA -= count;
						}
						_hoops_CPRI->_hoops_SGRHR |= _hoops_HSIPR;
						_hoops_CPRI->_hoops_SIIPR += count;

						_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
						erase = true;
					}
				}
				_hoops_CPRI->_hoops_SGRHR |= _hoops_IGAHR;
				done = true;
			}
			else {
				/* _hoops_RCSII _hoops_HAGH _hoops_HSH _hoops_GPP _hoops_RH _hoops_RSSI. */
				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
					ZALLOC_ARRAY(_hoops_CPRI->flags, _hoops_IPRI->face_count, _hoops_GIIPR);
					for (int i = 0; i < _hoops_IPRI->face_count; i++)
						_hoops_CPRI->flags[i] = _hoops_CPRI->_hoops_SGRHR;
					_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
				}
			}
		}
		else {
			/* _hoops_RCSII _hoops_IRS _hoops_GIIAR _hoops_IIGR _hoops_HCR _hoops_RSSI. */
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
				ZALLOC_ARRAY(_hoops_CPRI->flags, _hoops_IPRI->face_count, _hoops_GIIPR);
				for (int i = 0; i < _hoops_IPRI->face_count; i++)
					_hoops_CPRI->flags[i] = _hoops_CPRI->_hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
			}
		}

		if (!done) {

			_hoops_GIIPR *	flags = _hoops_CPRI->_hoops_CHHPR(offset);

			do {
				unsigned char	_hoops_RGP = *visibilities;
				
				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
					ZALLOC_ARRAY(_hoops_CPRI->flags, _hoops_IPRI->face_count, _hoops_GIIPR);
					for (int i = 0; i < _hoops_IPRI->face_count; i++)
						_hoops_CPRI->flags[i] = _hoops_CPRI->_hoops_SGRHR;
					_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
				}
				/* _hoops_SR _hoops_HS _hoops_IRS _hoops_RHRHR->_hoops_SGI _hoops_CRPR */
				if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
					if (_hoops_RGP) { /* _hoops_IAHAR _hoops_SCH _hoops_GPP */
						if (!BIT (*flags, _hoops_IAGI)) {
							if (BIT (*flags, _hoops_HSIPR)) {
								*flags &= ~_hoops_HSIPR;
								--_hoops_CPRI->_hoops_SIIPR;
								_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
							}
							*flags |= _hoops_IAGI;
							++_hoops_CPRI->_hoops_CPIAA;
						}
					}
					else {
						if (!BIT (*flags, _hoops_HSIPR)) {
							if (BIT (*flags, _hoops_IAGI)) {
								*flags &= ~_hoops_IAGI;
								--_hoops_CPRI->_hoops_CPIAA;
							}
							*flags |= _hoops_HSIPR;
							++_hoops_CPRI->_hoops_SIIPR;

							_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
							erase = true;
						}
					}
					*flags |= _hoops_IGAHR;
					++flags;
				}
				++visibilities;
			} _hoops_RGGA (--count == 0);

		}

		/* _hoops_RRRPR _hoops_IIGR _hoops_SPIGA _hoops_HHS _hoops_SHH _hoops_IRAP */
		if (_hoops_IPRI->owner) {
			if (_hoops_PHGCI && !BIT (_hoops_IPRI->owner->_hoops_RCGC, _hoops_APHGP))
				HI_Propagate_Maybes (context, _hoops_IPRI->owner, _hoops_APHGP);
		}

		_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;

		if (erase)
			_hoops_SASIR (context, _hoops_IPRI, _hoops_AISSR | _hoops_RPSIR);
		else
			_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR | _hoops_RPSIR);

		//_hoops_PAH _hoops_SR _hoops_HGCR _hoops_SCH _hoops_IS _hoops_PGSA _hoops_SAHR _hoops_CIPH _hoops_IAHAR _hoops_GPP?
		//_hoops_HHGCI (_hoops_GGSC, _hoops_CPHAR, _hoops_IHGCI | _hoops_CHGCI |_hoops_SHGCI);
	}

	_hoops_IRRPR();
#endif
}



HC_INTERFACE void HC_CDECL HC_MUnSet_Face_Visibilities (
	Key							key,
	int							offset,
	int							count) 
{
	_hoops_PAPPR context("MUnSet_Face_Visibilities");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#else

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Face_Visibilities (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d);}\n", offset, count));
	);

	if (offset < 0) {
		HE_ERROR (HEC_MSET_FACE, HES_INVALID_OFFSET, "Offset is negative");
		return;
	}

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_CCGPP)) == null)
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

		if ((_hoops_CPRI->flags == null && BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) ||
			(_hoops_CPRI->_hoops_SGRHR == 0 && !BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR))) {
			/* _hoops_ISAP _hoops_ARP _hoops_RPP _hoops_PSP _hoops_SGI, _hoops_HIS _hoops_SAHR _hoops_PSIIR & _hoops_CASI _hoops_GH */
			HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");
		}
		else {

			bool	erase = false;
			bool	_hoops_AHPGR = false;

			_hoops_GIIPR *	flags = _hoops_CPRI->_hoops_CHHPR(offset);

			if (count < _hoops_IPRI->face_count) {

				/* _hoops_RCSII _hoops_IRS _hoops_GIIAR _hoops_IIGR _hoops_HCR _hoops_RSSI. */
				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
					ZALLOC_ARRAY(_hoops_CPRI->flags, _hoops_IPRI->face_count, _hoops_GIIPR);
					for (int i = 0; i < _hoops_IPRI->face_count; i++)
						_hoops_CPRI->flags[i] = _hoops_CPRI->_hoops_SGRHR;
					_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
				}
			
				flags = _hoops_CPRI->_hoops_CHHPR(offset);

				do {
					if (BIT (*flags, _hoops_HSIPR)) {
						*flags &= ~_hoops_HSIPR;
						--_hoops_CPRI->_hoops_SIIPR;
						_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
					}
					else if (BIT (*flags, _hoops_IAGI)) {
						*flags &= ~_hoops_IAGI;
						--_hoops_CPRI->_hoops_CPIAA;
						_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
						erase = true; /* _hoops_CPIC _hoops_HII '_hoops_GPP' _hoops_IS '_hoops_RHGC' _hoops_SIAS _hoops_HA _hoops_CAPGP '_hoops_PSAP' */
					}
					else
						_hoops_AHPGR = true;
					*flags |= _hoops_IGAHR;

					++flags;
				} _hoops_RGGA (--count == 0);
			}
			else if (count == _hoops_IPRI->face_count) {
				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
					//_hoops_AA {
					if (BIT (*_hoops_CPRI->_hoops_CHHPR(offset), _hoops_HSIPR)) {
						*_hoops_CPRI->_hoops_CHHPR(offset) &= ~_hoops_HSIPR;
						_hoops_CPRI->_hoops_SIIPR -= count;
						_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
					}
					else if (BIT (*_hoops_CPRI->_hoops_CHHPR(offset), _hoops_IAGI)) {
						*_hoops_CPRI->_hoops_CHHPR(offset) &= ~_hoops_IAGI;
						_hoops_CPRI->_hoops_CPIAA -= count;
						_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
						erase = true; /* _hoops_CPIC _hoops_HII '_hoops_GPP' _hoops_IS '_hoops_RHGC' _hoops_SIAS _hoops_HA _hoops_CAPGP '_hoops_PSAP' */
					}
					else
						_hoops_AHPGR = true;
					*_hoops_CPRI->_hoops_CHHPR(offset) |= _hoops_IGAHR;

				}
				else{
					/* _hoops_RH _hoops_SHISR _hoops_AGIR */
					flags = _hoops_CPRI->_hoops_CHHPR(offset);

					do {
						if (BIT (*flags, _hoops_HSIPR)) {
							*flags &= ~_hoops_HSIPR;
							--_hoops_CPRI->_hoops_SIIPR;
							_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
						}
						else if (BIT (*flags, _hoops_IAGI)) {
							*flags &= ~_hoops_IAGI;
							--_hoops_CPRI->_hoops_CPIAA;
							_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
							erase = true; /* _hoops_CPIC _hoops_HII '_hoops_GPP' _hoops_IS '_hoops_RHGC' _hoops_SIAS _hoops_HA _hoops_CAPGP '_hoops_PSAP' */
						}
						else
							_hoops_AHPGR = true;
						*flags |= _hoops_IGAHR;

						++flags;
					} _hoops_RGGA (--count == 0);
				}


				/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_ISSC _hoops_IS _hoops_IRS _hoops_PIAP _hoops_CAS _hoops_RH _hoops_SGI _hoops_CHR _hoops_GHRHR, _hoops_SR _hoops_GHCA _hoops_RRP _hoops_IS _hoops_CIH _hoops_RH _hoops_SGI _hoops_CRPR */
				if (/*!_hoops_IRRC (_hoops_CPHAR->_hoops_PHRHR, _hoops_PCSII) &&*/
					BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR) &&
					_hoops_CPRI->lff_uniform(_hoops_IPRI->face_count)) {
					_hoops_CPRI->_hoops_SGRHR = _hoops_CPRI->flags[0];
					FREE_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
					_hoops_IPRI->polyhedron_flags &= ~_hoops_APRHR;
					_hoops_CPRI->flags = 0;
				}


			}

			if (_hoops_AHPGR && _hoops_GCSII)
				HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");

			if (_hoops_IPRI->tristrips != null) {
				_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;

				if (erase)
					_hoops_SASIR (context, _hoops_IPRI, _hoops_AISSR|_hoops_CSCCA|_hoops_RPSIR);
				else
					_hoops_SASIR (context, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
			}
		}
	}

	_hoops_IRRPR();
#endif
#endif
}

#define _hoops_GIGCI		0
#define _hoops_RIGCI			1


local int _hoops_AIGCI (
	_hoops_AIGPR *			_hoops_RIGC,
	Key								key,
	int								offset,
	int								count,
	int const *						_hoops_SISII,
	unsigned char alter *			existence,
	unsigned char alter *			visibilities,
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
		!(_hoops_IPRI->type == _hoops_SCIP || _hoops_IPRI->type == _hoops_GSIP) ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
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
			HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_OFFSET, "Offset is negative");
			if(_hoops_HASII)
				*_hoops_HASII = 1;
			goto Release;
		}

		if (_hoops_IPRI->face_count < offset + count) {
			char			buf[MAX_ERRMSG];

			HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
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

	if (_hoops_CPRI->_hoops_CPIAA == 0 && _hoops_CPRI->_hoops_SIIPR == 0)
		goto Release;

	if(_hoops_SISII){
		for(int i=0; i<count; ++i)
		{
			flags = _hoops_CPRI->_hoops_CHHPR(_hoops_SISII[i]);
			if(BIT(*flags, _hoops_HRAPA)) {
				if(visibilities)
					visibilities[i] = BIT (*flags, _hoops_IAGI);
				if(existence)
					existence[i] = _hoops_RIGCI;
				++_hoops_IASII;
			}
		}
	}
	else {
		for(int i=0; i<count; ++i)
		{
			flags = _hoops_CPRI->_hoops_CHHPR(offset+i);
			if(BIT(*flags, _hoops_HRAPA)) {
				if(visibilities)
					visibilities[i] = BIT (*flags, _hoops_IAGI);
				if(existence)
					existence[i] = _hoops_RIGCI;
				++_hoops_IASII;
			}
		}
	}

  Release:
	_hoops_IRRPR();
	return _hoops_IASII;
}


HC_INTERFACE void HC_CDECL HC_MShow_Face_Visibilities (
	Key				key,
	int				offset,
	int				count,
	char alter *	_hoops_IPGCI) 
{
	_hoops_PAPPR context("MShow_Face_Visibilities");

	unsigned char alter *	visibilities = (unsigned char alter *)_hoops_IPGCI;

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#		ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#		else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Face_Visibilities () */\n");
	);

	int	_hoops_HASII;
	int	_hoops_IASII = _hoops_AIGCI(context, key, offset, count, null, null, visibilities, &_hoops_HASII);

	//_hoops_RPP _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_RHHS _hoops_PCCP _hoops_RIHH, _hoops_SAHR _hoops_CASI _hoops_GH _hoops_PPR _hoops_PHHR _hoops_RISII
	if(_hoops_HASII)
		return;

	//_hoops_RARIR
	if (count != _hoops_IASII) {
		HE_ERROR (HEC_VISIBILITY, HES_NO_LOCAL_SETTING,
			  "Not all face visibilities are explicitly set in the specified range");
		return;
	}
#	endif
#endif
}


HC_INTERFACE int HC_CDECL HC_MShow_Face_Vis_W_Ex (
	Key				key,
	int				offset,
	int				count,
	char alter *	_hoops_GRGCI,
	char alter *	_hoops_IPGCI) 
{
	_hoops_PAPPR context("MShow_Face_Visibilities_With_Existence");

	unsigned char alter *	existence = (unsigned char alter *)_hoops_GRGCI;
	unsigned char alter *	visibilities = (unsigned char alter *)_hoops_IPGCI;

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return 0;
#else
#	ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
	return 0;
#	else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Face_Visibilities_With_Existence () */\n");
	);

	int	_hoops_IASII = _hoops_AIGCI(context, key, offset, count, null, existence, visibilities);

	return _hoops_IASII;
#	endif
#endif
}


HC_INTERFACE void HC_CDECL HC_MSet_Specific_Face_Vis (
	Key				key,
	int				count,
	int const *		indices,
	char const *	_hoops_IPGCI) 
{
	_hoops_PAPPR context("MSet_Specific_Face_Visibilities");

	unsigned char const *	visibilities = (unsigned char const *)_hoops_IPGCI;

#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#else

	CODE_GENERATION (
		int count2 = count;
		if (count == 0) { 
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Specific_Face_Visibilities (LOOKUP (%D), 0, 0, 0);\n", key));
		}
		else {
			HI_Dump_Code (Sprintf_D (null, "{unsigned char* visibilities = (unsigned char*) malloc(sizeof(unsigned char)*%d);\n", count2));
			HI_Dump_Code (Sprintf_D (null, "int* indices = (int*) malloc(sizeof(int)*%d);\n", count2));
			++HOOPS_WORLD->_hoops_ISPPR;
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (Sprintf_DD (null, "visibilities[%d] = %f;\n", count2, visibilities[count2]));
				HI_Dump_Code (Sprintf_DD (null, "indices[%d] = %f;\n", count2, indices[count2]));
			}
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Specific_Face_Visibilities (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_D (null, "%d, indices, visibilities);\n", count));
			HI_Dump_Code ("free (visibilities);\n");
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

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_CCGPP)) == null)
		return;

	if (_hoops_AISII (_hoops_IPRI, count, indices)) {

		Local_Face_Attributes *	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;
		if (_hoops_CPRI->flags == null || *_hoops_CPRI->_hoops_CHHPR() == 0)
			HI_Initialize_Face_Attributes (_hoops_IPRI, 0);

		if (count > _hoops_IPRI->face_count) {
			HE_WARNING (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Indices count exceeds face count.");
			_hoops_IPRI->face_count = count;
		}

		bool	_hoops_GSSII = true;
		
		if (count < _hoops_IPRI->face_count) {
			/* _hoops_PAH'_hoops_RA _hoops_GCAS _hoops_SHH _hoops_RGSR _hoops_HCR _hoops_PSPI */
			_hoops_GSSII = false;
		}
		else {
			for (int i = 0; i < count; i++) {
				if (i != indices[i]) {
					_hoops_GSSII = false;
					break;
				}
			}
		}

		bool	erase = false;
		bool	_hoops_PHGCI = false;
		bool	done = false;

		bool	_hoops_CPGCI = true;

		for (int i = 0; i < count; i++) {
			if (*visibilities != visibilities[i]) {
				_hoops_CPGCI = false;
				break;	
			}
		}

		if (_hoops_GSSII) {

			/* _hoops_RCSII _hoops_HCR _hoops_RSSI. _hoops_CHR _hoops_SR _hoops_RGSR _hoops_CAPR _hoops_HCR _hoops_IS _hoops_PSHR _hoops_HPRC? */
			if (_hoops_CPGCI && !BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {

				/* _hoops_PS _hoops_PAH _hoops_SAHR _hoops_SGH _hoops_RH _hoops_GHRHR _hoops_RIP */
				if (visibilities[0]) { /* _hoops_IAHAR _hoops_SCH _hoops_GPP */
					if (!BIT (_hoops_CPRI->_hoops_SGRHR, _hoops_IAGI)) {
						if (BIT (_hoops_CPRI->_hoops_SGRHR, _hoops_HSIPR)) {
							_hoops_CPRI->_hoops_SGRHR &= ~_hoops_HSIPR;
							_hoops_CPRI->_hoops_SIIPR -= count;
							_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
						}
						_hoops_CPRI->_hoops_SGRHR |= _hoops_IAGI;
						_hoops_CPRI->_hoops_CPIAA += count;
					}
				}
				else {
					if (!BIT (_hoops_CPRI->_hoops_SGRHR, _hoops_HSIPR)) {
						if (BIT (_hoops_CPRI->_hoops_SGRHR, _hoops_IAGI)) {
							_hoops_CPRI->_hoops_SGRHR &= ~_hoops_IAGI;
							_hoops_CPRI->_hoops_CPIAA -= count;
						}
						_hoops_CPRI->_hoops_SGRHR |= _hoops_HSIPR;
						_hoops_CPRI->_hoops_SIIPR += count;

						_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
						erase = true;
					}
				}

				_hoops_CPRI->_hoops_SGRHR |= _hoops_IGAHR;

				done = true;
			}
			else {
				/* _hoops_RCSII _hoops_IRS _hoops_GIIAR _hoops_IIGR _hoops_HCR _hoops_RSSI. */
				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
					ZALLOC_ARRAY(_hoops_CPRI->flags, _hoops_IPRI->face_count, _hoops_GIIPR);
					for (int i = 0; i < _hoops_IPRI->face_count; i++)
						_hoops_CPRI->flags[i] = _hoops_CPRI->_hoops_SGRHR;
					_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
				}
			}

		}

		if (!done) {

			if ((count != _hoops_IPRI->face_count) || !_hoops_CPGCI) {
				/* _hoops_SR _hoops_CHR _hoops_HAR _hoops_RGSR _hoops_IRS _hoops_RIP _hoops_GPP _hoops_RCSAR _hoops_HSP, _hoops_HIS _hoops_RPP _hoops_IRS _hoops_SGI _hoops_CRPR _hoops_SSCP _hoops_HAR _hoops_GAPR
				_hoops_RPII _hoops_PSPP, _hoops_SR _hoops_RRP _hoops_IS _hoops_AA _hoops_SCH _hoops_HA */
				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
					ZALLOC_ARRAY(_hoops_CPRI->flags, _hoops_IPRI->face_count, _hoops_GIIPR);
					for (int i = 0; i < _hoops_IPRI->face_count; i++)
						_hoops_CPRI->flags[i] = _hoops_CPRI->_hoops_SGRHR;
					_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
				}
			}

			do {
				unsigned char		_hoops_RGP = *visibilities++;
				int					index = *indices++;
				_hoops_GIIPR *	_hoops_PSSII = _hoops_CPRI->_hoops_CHHPR(index);

				if (_hoops_RGP) { /* _hoops_IAHAR _hoops_SCH _hoops_GPP */
					if (!BIT (*_hoops_PSSII, _hoops_IAGI)) {
						if (BIT (*_hoops_PSSII, _hoops_HSIPR)) {
							*_hoops_PSSII &= ~_hoops_HSIPR;
							--_hoops_CPRI->_hoops_SIIPR;
							_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
						}
						*_hoops_PSSII |= _hoops_IAGI;
						++_hoops_CPRI->_hoops_CPIAA;
					}
				}
				else {
					if (!BIT (*_hoops_PSSII, _hoops_HSIPR)) {
						if (BIT (*_hoops_PSSII, _hoops_IAGI)) {
							*_hoops_PSSII &= ~_hoops_IAGI;
							--_hoops_CPRI->_hoops_CPIAA;
						}
						*_hoops_PSSII |= _hoops_HSIPR;
						++_hoops_CPRI->_hoops_SIIPR;
						_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
						erase = true;
					}
				}

				*_hoops_PSSII |= _hoops_IGAHR;

			} _hoops_RGGA (--count == 0);
		}

		/* _hoops_RRRPR _hoops_IIGR _hoops_SPIGA _hoops_HHS _hoops_SHH _hoops_IRAP */
		if (_hoops_IPRI->owner) {
			if (_hoops_PHGCI && !BIT (_hoops_IPRI->owner->_hoops_RCGC, _hoops_APHGP))
				HI_Propagate_Maybes (context, _hoops_IPRI->owner, _hoops_APHGP);
		}

		_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;

		if (erase)
			_hoops_SASIR (context, _hoops_IPRI, _hoops_AISSR | _hoops_RPSIR);
		else
			_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR | _hoops_RPSIR);

		//_hoops_PAH _hoops_SR _hoops_HGCR _hoops_SCH _hoops_IS _hoops_PGSA _hoops_SAHR _hoops_CIPH _hoops_IAHAR _hoops_GPP?
		//_hoops_HHGCI (_hoops_GGSC, _hoops_CPHAR, _hoops_IHGCI | _hoops_CHGCI |_hoops_SHGCI);
	}

	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_MUnSet_Specific_Face_Vis (
	Key							key,
	int							count,
	int const *					indices) 
{
	_hoops_PAPPR context("MUnSet_Specific_Face_Visibilities");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#else

	CODE_GENERATION (
		int		count2 = count;
		if (count == 0) { 
			HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Specific_Face_Visibilities (LOOKUP (%D),  0, 0);\n", key));
		}
		else {
			HI_Dump_Code (Sprintf_D (null, "{int* indices = (int*) malloc(sizeof(int)*%d);\n", count2));
			++HOOPS_WORLD->_hoops_ISPPR;
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (Sprintf_DD (null, "indices[%d] = %f;\n", count2, indices[count2]));
			}
			HI_Dump_Code (Sprintf_LD (null, "HC_MUnSet_Specific_Face_Visibilities (LOOKUP (%D), ", key));
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

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_CCGPP)) == null)
		return;

	if (_hoops_AISII (_hoops_IPRI, count, indices)) {

		Local_Face_Attributes *		_hoops_CPRI = &_hoops_IPRI->local_face_attributes;
		
		if (_hoops_CPRI->flags == null) {
			/* _hoops_ISAP _hoops_ARP _hoops_RPP _hoops_PSP _hoops_SGI, _hoops_HIS _hoops_SAHR _hoops_PSIIR & _hoops_CASI _hoops_GH */
			HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");
		}
		else {

			_hoops_CPRI = &_hoops_IPRI->local_face_attributes;
			if (_hoops_CPRI->flags == null && *_hoops_CPRI->_hoops_CHHPR() == 0)
				HI_Initialize_Face_Attributes (_hoops_IPRI, 0);

			//_hoops_PIGCI *	_hoops_SGI = _hoops_RHRHR->_hoops_HIGCI();

			bool	_hoops_GSSII = true;

			for (int i = 0; i < count; i++) {
				if (i != indices[i]) {
					_hoops_GSSII = false;
					break;
				}
			}

			bool	erase = false;
			bool	_hoops_AHPGR = false;
			bool	done = false;

			if (count != _hoops_IPRI->face_count) {
				/* _hoops_SR _hoops_CHR _hoops_HAR _hoops_HGGCI _hoops_IRS _hoops_RIP _hoops_GPP _hoops_RCSAR _hoops_HSP, _hoops_HIS _hoops_RPP _hoops_IRS _hoops_SGI _hoops_CRPR _hoops_SSCP _hoops_HAR _hoops_GAPR
				_hoops_RPII _hoops_PSPP, _hoops_SR _hoops_RRP _hoops_IS _hoops_AA _hoops_SCH _hoops_HA */
				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
					ZALLOC_ARRAY(_hoops_CPRI->flags, _hoops_IPRI->face_count, _hoops_GIIPR);
					for (int i = 0; i < _hoops_IPRI->face_count; i++)
						_hoops_CPRI->flags[i] = _hoops_CPRI->_hoops_SGRHR;
					_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
				}
			}
			else {
				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
					if (_hoops_GSSII) {
						/* _hoops_SR _hoops_IPIH _hoops_HS _hoops_PSP _hoops_SGI _hoops_CRPR, _hoops_HIS _hoops_HCR _hoops_RSSI _hoops_PIHA _hoops_HS _hoops_PSHR _hoops_HPRC.
						_hoops_CPGP _hoops_SR _hoops_CHR _hoops_ISSPR-_hoops_RGSR _hoops_SHAAA _hoops_GPP _hoops_HCR _hoops_RSSI, _hoops_PSCR _hoops_SR _hoops_PAH _hoops_HGGC _hoops_GRHP _hoops_SAHR
						_hoops_RH _hoops_RSRA _hoops_IIGCI */

						if (BIT (_hoops_CPRI->_hoops_SGRHR, _hoops_HSIPR)) {
							_hoops_CPRI->_hoops_SGRHR &= ~_hoops_HSIPR;
							_hoops_CPRI->_hoops_SIIPR -= count;
							_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
						}
						else if (BIT (_hoops_CPRI->_hoops_SGRHR, _hoops_IAGI)) {
							_hoops_CPRI->_hoops_SGRHR &= ~_hoops_IAGI;
							_hoops_CPRI->_hoops_CPIAA -= count;
							_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
							erase = true; /* _hoops_CPIC _hoops_HII '_hoops_GPP' _hoops_IS '_hoops_RHGC' _hoops_SIAS _hoops_HA _hoops_CAPGP '_hoops_PSAP' */
						}
						else
							_hoops_AHPGR = true;

						_hoops_CPRI->_hoops_SGRHR |= _hoops_IGAHR;

						done = true;
					}
					else {
						/* _hoops_SR _hoops_CHR _hoops_HAR _hoops_HGGCI _hoops_IRS _hoops_RIP _hoops_GPP _hoops_RCSAR _hoops_HSP, _hoops_HIS _hoops_RPP _hoops_IRS _hoops_SGI _hoops_CRPR _hoops_SSCP _hoops_HAR _hoops_GAPR
						_hoops_RPII _hoops_PSPP, _hoops_SR _hoops_RRP _hoops_IS _hoops_AA _hoops_SCH _hoops_HA */
						ZALLOC_ARRAY(_hoops_CPRI->flags, _hoops_IPRI->face_count, _hoops_GIIPR);
						for (int i = 0; i < _hoops_IPRI->face_count; i++)
							_hoops_CPRI->flags[i] = _hoops_CPRI->_hoops_SGRHR;
						_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
					}
				}
			}


			do {
				int	index = *indices++;

				if (BIT (*_hoops_CPRI->_hoops_CHHPR(index), _hoops_HSIPR)) {
					*_hoops_CPRI->_hoops_CHHPR(index) &= ~_hoops_HSIPR;
					--_hoops_CPRI->_hoops_SIIPR;
					_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
				}
				else if (BIT (*_hoops_CPRI->_hoops_CHHPR(index), _hoops_IAGI)) {
					*_hoops_CPRI->_hoops_CHHPR(index) &= ~_hoops_IAGI;
					--_hoops_CPRI->_hoops_CPIAA;
					_hoops_IPRI->_hoops_RSHPR &= ~(_hoops_AACPR|_hoops_CCCPR);
					erase = true; /* _hoops_CPIC _hoops_HII '_hoops_GPP' _hoops_IS '_hoops_RHGC' _hoops_SIAS _hoops_HA _hoops_CAPGP '_hoops_PSAP' */
				}
				else
					_hoops_AHPGR = true;

				*_hoops_CPRI->_hoops_CHHPR(index) |= _hoops_IGAHR;
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
		}
	}

	_hoops_IRRPR();
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_MShow_Specific_Face_Vis (
	Key				key,
	int				count,
	int const *		indices,
	char alter *	_hoops_IPGCI) 
{
	_hoops_PAPPR context("MShow_Specific_Face_Visibilities");

	unsigned char alter *	visibilities = (unsigned char alter *)_hoops_IPGCI;

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Specific_Face_Visibilities () */\n");
	);

	int	_hoops_HASII;
	int	_hoops_IASII = _hoops_AIGCI(context, key, 0, count, indices, null, visibilities, &_hoops_HASII);

	//_hoops_RPP _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_RHHS _hoops_PCCP _hoops_RIHH, _hoops_SAHR _hoops_CASI _hoops_GH _hoops_PPR _hoops_PHHR _hoops_RISII
	if(_hoops_HASII)
		return;

	//_hoops_RARIR
	if (count != _hoops_IASII) {
		HE_ERROR (HEC_VISIBILITY, HES_NO_LOCAL_SETTING, "Not all face visibilities are explicitly set in the specified range");
		return;
	}

#endif
#endif
}


HC_INTERFACE int HC_CDECL HC_MShow_Spec_Face_Vis_W_Ex (
	Key				key,
	int				count,
	int const *		indices,
	char alter *	_hoops_GRGCI,
	char alter *	_hoops_IPGCI) 
{
	_hoops_PAPPR context("MShow_Specific_Face_Visibilities_With_Existence");

	unsigned char alter *	existence = (unsigned char alter *)_hoops_GRGCI;
	unsigned char alter *	visibilities = (unsigned char alter *)_hoops_IPGCI;

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return 0;
#else
#ifdef _hoops_IIICA
	_hoops_IRPPR ("Geometry Misc");
	return 0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Specific_Face_Visibilities_With_Existence () */\n");
	);

	int _hoops_IASII = _hoops_AIGCI(context, key, 0, count, indices, existence, visibilities);

	return _hoops_IASII;
#endif
#endif
}




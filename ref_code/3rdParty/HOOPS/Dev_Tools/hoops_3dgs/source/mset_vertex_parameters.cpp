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
 * $Id: obf_tmp.txt 1.62 2010-09-09 21:25:41 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


local bool _hoops_PRSII (
	Polyhedron const *		_hoops_IPRI,
	int						count,
	int const *				indices) {

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

HC_INTERFACE void HC_CDECL HC_MSet_Vertex_Parameters (
	Key							key,
	int							offset,
	int							count,
	int							number_parameters,
	float const *				user_parameters) 
{
	_hoops_PAPPR context("MSet_Vertex_Parameters");

#ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
#else
#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MSet_Vertex_Parameters () */\n");
	);


	if (number_parameters == 0) 
		return;

	if (count == 0) 
		return;  /* _hoops_CPRSH */

	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		return;
	}

	if (offset < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_OFFSET, "Offset is negative");
		return;
	}

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_ICGPP)) == null)
		return;

	if (_hoops_IPRI->point_count < offset + count) {
		char	buf[MAX_ERRMSG];
		HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
				   Sprintf_D (null, "Shell or mesh only has %d vertices -", _hoops_IPRI->point_count),
				   Sprintf_DD (buf, "can't change %d of them at offset %d", count, offset));
	}
	else {

		_hoops_RSSH *					parameters = (_hoops_RSSH *)user_parameters;
		Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

		if (_hoops_SPRI->params == null || _hoops_SPRI->param_width < number_parameters)
			HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_ASAPA, number_parameters);

		if (offset != 0 || count < _hoops_IPRI->point_count) {
			/* _hoops_APSH _hoops_PII _hoops_SR _hoops_GRS _hoops_RRP _hoops_PCCP _hoops_IIRRA->_hoops_SGI _hoops_CRPR _hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_AIAH _hoops_HS _hoops_SCH */
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
				for(int i = 0; i < _hoops_IPRI->point_count; i++)
					_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
			}
		}

		_hoops_RSSH *				_hoops_HAGCI = &_hoops_SPRI->params[offset*_hoops_SPRI->param_width];
		Local_Vertex_Flags *	flags = _hoops_SPRI->_hoops_CHHPR(offset);

		if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
			/* _hoops_RPP _hoops_ISCP _hoops_SGI _hoops_CHR _hoops_GHRHR */
			if (!BIT (*flags, _hoops_ASAPA)) {
				*flags |= _hoops_ASAPA;
				_hoops_SPRI->_hoops_RSAPA += count;
			}

			if (_hoops_SPRI->param_width == number_parameters)
				for (int i=0; i<number_parameters*count; i++)
					_hoops_HAGCI[i] = parameters[i];
			else do { /* _hoops_RPP _hoops_IIRRA->_hoops_IAGCI > _hoops_CAGCI _hoops_PSCR _hoops_CRPSR _hoops_CAPR _hoops_GGSR */
				for (int i=0; i<number_parameters; i++)
					_hoops_HAGCI[i] = parameters[i];

				for (int i=number_parameters; i<_hoops_SPRI->param_width; i++)
					_hoops_HAGCI[i] = 0.0f;

				_hoops_HAGCI+=_hoops_SPRI->param_width;
				parameters+=number_parameters;

				++flags;
			} _hoops_RGGA (--count == 0);
		}
		else do {
			if (!BIT (*flags, _hoops_ASAPA)) {
				*flags |= _hoops_ASAPA;
				++_hoops_SPRI->_hoops_RSAPA;
			}

			for (int i=0; i<number_parameters; i++)
				_hoops_HAGCI[i] = parameters[i];

			for (int i=number_parameters; i<_hoops_SPRI->param_width; i++)
				_hoops_HAGCI[i] = 0.0f;

			_hoops_HAGCI+=_hoops_SPRI->param_width;
			parameters+=number_parameters;

			++flags;
		} _hoops_RGGA (--count == 0);

		/*??? _hoops_HAR _hoops_GGR _hoops_SAGCI */
		if (_hoops_SPRI->_hoops_RSAPA == _hoops_IPRI->point_count &&
			_hoops_IPRI->_hoops_GIGPR != null) {
			Polymarker *pm = _hoops_IPRI->_hoops_GIGPR;
			_hoops_IPRI->_hoops_AGRHR |= _hoops_ASAPA;
			do {
				pm->_hoops_SACI.flags |= _hoops_ASAPA;
			} while ((pm = pm->next) != null);
		}
		
		HI_Invalidate_Display_Lists (context, _hoops_IPRI);
		_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR);
	}

	_hoops_IRRPR();
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_MUnSet_Vertex_Parameters (
	Key							key,
	int							offset,
	int							count) 
{
	_hoops_PAPPR context("MUnSet_Vertex_Parameters");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
#ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
#else
#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MUnSet_Vertex_Parameters () */\n");
	);


	if (offset < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_OFFSET, "Offset is negative");
		return;
	}

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_ICGPP)) == null)
		return;

	bool	_hoops_GCSII = true;

	if (count == -1) {
		count = _hoops_IPRI->point_count - offset;
		_hoops_GCSII = false;
	}

	if (count == 0) 
		;  /* _hoops_CPRSH */
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

		bool	_hoops_AHPGR = false;
		Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

		if (_hoops_SPRI->_hoops_RSAPA == 0) {
			/* _hoops_ISAP _hoops_IS _hoops_IPPRA _hoops_RPP _hoops_PSP _hoops_SGI, _hoops_HIS _hoops_SAHR _hoops_PSIIR & _hoops_CASI _hoops_GH */
			HE_WARNING (HEC_MUNSET, HES_MISSING, "No parameters to UnSet");
		}
		else {

			if (offset != 0 || count < _hoops_IPRI->point_count) {

				if (_hoops_SPRI->_hoops_RSAPA != _hoops_IPRI->point_count)
					_hoops_AHPGR = true;

				/* _hoops_APSH _hoops_PII _hoops_SR _hoops_GRS _hoops_RRP _hoops_PCCP _hoops_IIRRA->_hoops_SGI _hoops_CRPR _hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_AIAH _hoops_HS _hoops_SCH */
				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
					ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
					for(int i = 0; i < _hoops_IPRI->point_count; i++)
						_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
					_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
				}
			}

			Local_Vertex_Flags *	flags = _hoops_SPRI->_hoops_CHHPR(offset);

			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				/* _hoops_RPP _hoops_ISCP _hoops_SGI _hoops_CHR _hoops_GHRHR */
				*flags &= ~_hoops_ASAPA;
				_hoops_SPRI->_hoops_RSAPA = 0;
			}
			else do {
				if (BIT (*flags, _hoops_ASAPA)) {
					*flags &= ~_hoops_ASAPA;
					--_hoops_SPRI->_hoops_RSAPA;
				}
				else
					_hoops_AHPGR = true;
				++flags;
			} _hoops_RGGA (--count == 0);

			/*??? _hoops_HAR _hoops_GGR _hoops_SAGCI */
			if (_hoops_SPRI->_hoops_RSAPA != _hoops_IPRI->point_count &&
				_hoops_IPRI->_hoops_GIGPR != null) {
				Polymarker *pm = _hoops_IPRI->_hoops_GIGPR;
				_hoops_IPRI->_hoops_AGRHR &= ~_hoops_ASAPA;
				do {
					pm->_hoops_SACI.flags &= ~_hoops_ASAPA;
				} while ((pm = pm->next) != null);
			}

			if (_hoops_AHPGR && _hoops_GCSII)
				HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");

			HI_Invalidate_Display_Lists (context, _hoops_IPRI);
			_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR);
		}
	}

	_hoops_IRRPR();
#endif
#endif
#endif
}

#define _hoops_GPGCI	0
#define _hoops_RPGCI		1

local int _hoops_APGCI(
	_hoops_AIGPR *			_hoops_RIGC, 
	Key								key,
	int								offset,
	int								count,
	int const *						specific_vertices,
	unsigned char alter *			existence,
	int alter *						number_parameters,
	float alter *					params,
	int *							_hoops_HASII = null) {
	int								_hoops_IASII = 0;
	_hoops_RSSH *						parameters = (_hoops_RSSH *)params;
	_hoops_RSSH *						_hoops_HAGCI;
	Local_Vertex_Flags const *		flags;
	Local_Vertex_Attributes const *	_hoops_SPRI;
	Polyhedron const *				_hoops_IPRI;
	int								param_width;

	if (parameters == null) {
		goto Release;
	}

	_hoops_CSPPR();

	if(_hoops_HASII)
		*_hoops_HASII = 0;
	_hoops_IPRI = (Polyhedron *)_hoops_RCSSR (_hoops_RIGC, key);

	if (_hoops_IPRI == null ||
		!(_hoops_IPRI->type == _hoops_SCIP || _hoops_IPRI->type == _hoops_GSIP) ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_GEOMETRY, HES_INVALID_KEY, "Key does not refer to a valid shell or mesh");
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

	if (_hoops_IPRI->point_count < count) {
		char			buf[MAX_ERRMSG];

		HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
				   Sprintf_D (null, "Shell or mesh only has %d vertices -", _hoops_IPRI->point_count),
				   Sprintf_D (buf, "can't show %d of them", count));
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

	//_hoops_HSPC _hoops_ASRC _hoops_HSH
	if(existence)
		memset(existence, 0, count*sizeof(char));

	if (_hoops_SPRI->_hoops_RSAPA == 0 || _hoops_SPRI->params == null)
		goto Release;

	param_width = _hoops_SPRI->param_width;

	if (number_parameters != null)
		*number_parameters = param_width;
	
	if(specific_vertices)
	{
		_hoops_HAGCI = _hoops_SPRI->params;
		for(int i=0; i<count; ++i) {
			flags = _hoops_SPRI->_hoops_CHHPR(specific_vertices[i]);
			if(BIT(*flags, _hoops_ASAPA)) {
				if(existence)
					existence[i] = _hoops_RPGCI;
				if(parameters)
					_hoops_AIGA(&_hoops_HAGCI[specific_vertices[i]*param_width], param_width, _hoops_RSSH, &parameters[i*param_width]);
				++_hoops_IASII;
			}
		}
	}
	else
	{
		_hoops_HAGCI = &_hoops_SPRI->params[offset*param_width];
		for(int i=0; i<count; ++i) {
			flags = _hoops_SPRI->_hoops_CHHPR(offset+i);
			if(BIT(*flags, _hoops_ASAPA)) {
				if(existence)
					existence[i] = _hoops_RPGCI;
				if(parameters)
					_hoops_AIGA(&_hoops_HAGCI[i*param_width], param_width, _hoops_RSSH, &parameters[i*param_width]);
				++_hoops_IASII;
			}
		}
	}
	
Release:
	_hoops_IRRPR();
	return _hoops_IASII;
}

HC_INTERFACE void HC_CDECL HC_MShow_Vertex_Parameters (
	Key					key,
	int					offset,
	int					count,
	int	alter *			number_parameters,
	float alter *		user_parameters) 
{
	_hoops_PAPPR context("MShow_Vertex_Parameters");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#	ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
#	else
#		ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#		else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Vertex_Parameters () */\n");
	);

	int	_hoops_HASII;

	int _hoops_IASII = _hoops_APGCI(context, key, offset, count, null, null, number_parameters, user_parameters, &_hoops_HASII);

	//_hoops_RPP _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_RHHS _hoops_PCCP _hoops_RIHH, _hoops_SAHR _hoops_CASI _hoops_GH _hoops_PPR _hoops_PHHR _hoops_RISII
	if(_hoops_HASII)
		return;

	//_hoops_RARIR
	if (count != _hoops_IASII) {
		HE_ERROR (HEC_PARAMETER, HES_NO_LOCAL_SETTING, "Not all requested vertex parameters are explicitly set");
		return;
	}

#		endif
#	endif
#endif
}

/* _hoops_PAGA: 
_hoops_IPCP _hoops_IAGCI _hoops_ACRGI _hoops_HRGR _hoops_IRS _hoops_CRS _hoops_IS _hoops_IRS _hoops_RSRA _hoops_SCSH _hoops_HPGP
_hoops_PPGCI _hoops_HRGR _hoops_IRS _hoops_RPR _hoops_SPCC _hoops_GSPR _hoops_CRPR _hoops_PPR 
_hoops_HPGCI _hoops_HRGR _hoops_IRS (_hoops_RPR*_hoops_IAGCI) _hoops_SPCC _hoops_AIIC _hoops_CRPR */
HC_INTERFACE int HC_CDECL HC_MShow_Vertex_Parameters_W_Ex (
	Key				key,
	int				offset,
	int				count,
	char alter *	_hoops_GRGCI,
	int	alter *		param_width,
	float alter *	user_parameters) 
{
	_hoops_PAPPR context("MShow_Vertex_Parameters_With_Existence");

	unsigned char alter *	existence = (unsigned char alter *) _hoops_GRGCI;

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return 0;
#else
#	ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
	return 0;
#	else
#		ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
	return 0;
#		else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Vertex_Parameters_With_Existence () */\n");
	);

	int	_hoops_IASII = _hoops_APGCI(context, key, offset, count, null, existence, param_width, user_parameters);

	return _hoops_IASII;

#		endif
#	endif
#endif

}

/* _hoops_PAGA: 
_hoops_IPCP _hoops_IAGCI _hoops_ACRGI _hoops_HRGR _hoops_IRS _hoops_CRS _hoops_IS _hoops_IRS _hoops_RSRA _hoops_SCSH _hoops_HPGP
_hoops_PPGCI _hoops_HRGR _hoops_IRS _hoops_RPR _hoops_SPCC _hoops_GSPR _hoops_CRPR _hoops_PPR 
_hoops_HPGCI _hoops_HRGR _hoops_IRS (_hoops_RPR*_hoops_IAGCI) _hoops_SPCC _hoops_AIIC _hoops_CRPR */
HC_INTERFACE int HC_CDECL HC_MShow_Spec_Vertex_Params_W_E (
	Key				key,
	int				count,
	int const *		specific_vertices,
	char alter *	_hoops_GRGCI,
	int	alter *		param_width,
	float alter *	user_parameters) 
{
	_hoops_PAPPR context("MShow_Spec_Vertex_Parameters_With_Existence");

	unsigned char alter *	existence = (unsigned char alter *) _hoops_GRGCI;

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return 0;
#else
#	ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
	return 0;
#	else
#		ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
	return 0;
#		else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Specific_Vertex_Parameters_With_Existence () */\n");
	);

	int _hoops_IASII = _hoops_APGCI(context, key, 0, count, specific_vertices, existence, param_width, user_parameters);
	
	return _hoops_IASII;

#		endif
#	endif
#endif
}


HC_INTERFACE void HC_CDECL HC_MSet_Spec_Vertex_Parameters (
	Key							key,
	int							count,
	int const *					indices,
	int							number_parameters,
	float const *				user_parameters) 
{
	_hoops_PAPPR context("MSet_Specific_Vertex_Parameters");

#ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
#else
#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MSet_Specific_Vertex_Parameters () */\n");
	);

	if (number_parameters == 0) 
		return;
	
	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		return;
	}

	if (count == 0) 
		return;  /* _hoops_CPRSH */

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_ICGPP)) == null)
		return;

	if (_hoops_IPRI->point_count < count) {
		char	buf[MAX_ERRMSG];
		HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
				   Sprintf_D (null, "Shell or mesh only has %d vertices -", _hoops_IPRI->point_count),
				   Sprintf_D (buf, "can't change %d of them", count));
	}
	else if (_hoops_PRSII (_hoops_IPRI, count, indices)) {

		_hoops_RSSH *	parameters = (_hoops_RSSH *)user_parameters;
		Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

		if (_hoops_SPRI->params == null ||
			_hoops_SPRI->param_width < number_parameters)
				HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_ASAPA, number_parameters);

		/* _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_RGSR _hoops_SASI _hoops_PPR _hoops_SR'_hoops_ASAR _hoops_GHRHR, _hoops_HPCAR _hoops_SR _hoops_CHR _hoops_RRGCI _hoops_ARGCI.  _hoops_SCH'_hoops_GRI _hoops_HAH _hoops_ACIPR _hoops_IS _hoops_SHAC _hoops_CGIRA _hoops_IAII _hoops_CCA _hoops_PRGCI _hoops_CR _hoops_SR'_hoops_ASAR _hoops_PSAR _hoops_GCAS _hoops_HRGCI _hoops_IPSP _hoops_PSPI */
		if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
			ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
			for(int i = 0; i < _hoops_IPRI->point_count; i++)
				_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
			_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
		}

		_hoops_RSSH *	_hoops_HAGCI = _hoops_SPRI->params;

		do {
			int	index = *indices++;

			if (!BIT (*_hoops_SPRI->_hoops_CHHPR(index), _hoops_ASAPA)) {
				*_hoops_SPRI->_hoops_CHHPR(index) |= _hoops_ASAPA;
				++_hoops_SPRI->_hoops_RSAPA;
			}

			for (int i = 0; i < number_parameters; i++)
				_hoops_HAGCI[index*_hoops_SPRI->param_width+i] = parameters[i];

			/* _hoops_CRPSR _hoops_SCH _hoops_GGSR _hoops_CCA _hoops_GSHCR _hoops_RPP _hoops_RRP _hoops_SHH */
			for (int i=number_parameters; i<_hoops_SPRI->param_width; i++)
				_hoops_HAGCI[index*_hoops_SPRI->param_width+i] = 0.0f;

			parameters += _hoops_SPRI->param_width;
		} _hoops_RGGA (--count == 0);

		/*??? _hoops_HAR _hoops_GGR _hoops_SAGCI */
		if (_hoops_SPRI->_hoops_RSAPA == _hoops_IPRI->point_count &&
			_hoops_IPRI->_hoops_GIGPR != null) {
			Polymarker *pm = _hoops_IPRI->_hoops_GIGPR;
			_hoops_IPRI->_hoops_AGRHR |= _hoops_ASAPA;
			do {
				pm->_hoops_SACI.flags |= _hoops_ASAPA;
			} while ((pm = pm->next) != null);
		}

		HI_Invalidate_Display_Lists (context, _hoops_IPRI);
		_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR);
	}

	_hoops_IRRPR();
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_MUnSet_Spec_Vert_Parameters (
	Key							key,
	int							count,
	int const *					indices) 
{
	_hoops_PAPPR context("MUnSet_Specific_Vertex_Parameters");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
#ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
#else
#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MUnSet_Specific_Vertex_Parameters () */\n");
	);

	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		return;
	}

	if (count == 0) 
		return;  /* _hoops_CPRSH */

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_ICGPP)) == null)
		return;


	if (_hoops_IPRI->point_count < count) {
		char	buf[MAX_ERRMSG];
		HE_ERROR2 (HEC_MSET_VERTEX, HES_INVALID_OFFSET,
				   Sprintf_D (null, "Shell or mesh only has %d vertices -", _hoops_IPRI->point_count),
				   Sprintf_D (buf, "can't change %d of them", count));
	}
	else {

		Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

		if (_hoops_SPRI->_hoops_RSAPA == 0) {
			/* _hoops_ISAP _hoops_IPPRA _hoops_RPP _hoops_PSP _hoops_SGI, _hoops_HIS _hoops_SAHR _hoops_PSIIR & _hoops_CASI _hoops_GH */
			HE_WARNING (HEC_MUNSET, HES_MISSING, "No parameters to UnSet");
		}
		else if (_hoops_SPRI->params == null) {
			HE_ERROR (HEC_PARAMETER, HES_NO_LOCAL_SETTING, "No vertex parameters are explicitly set here");
		}
		else if (_hoops_PRSII (_hoops_IPRI, count, indices)) {

			/* _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_HGGCI _hoops_SASI _hoops_PPR _hoops_SR'_hoops_ASAR _hoops_GHRHR, _hoops_HPCAR _hoops_SR _hoops_CHR _hoops_RRGCI _hoops_ARGCI.  _hoops_SCH'_hoops_GRI _hoops_HAH _hoops_ACIPR _hoops_IS _hoops_SHAC _hoops_CGIRA _hoops_IAII _hoops_CCA _hoops_PRGCI _hoops_CR _hoops_SR'_hoops_ASAR _hoops_PSAR _hoops_GCAS _hoops_HRGCI _hoops_IPSP _hoops_PSPI */
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				ZALLOC_ARRAY(_hoops_SPRI->flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
				for(int i = 0; i < _hoops_IPRI->point_count; i++)
					_hoops_SPRI->flags[i] = _hoops_SPRI->_hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
			}

			Local_Vertex_Flags *	flags = _hoops_SPRI->_hoops_CHHPR(0);
			bool	_hoops_AHPGR = false;

			do {
				int	index = *indices++;
				if (BIT (flags[index], _hoops_ASAPA)) {
					flags[index] &= ~_hoops_ASAPA;
					--_hoops_SPRI->_hoops_RSAPA;
				}
				else
					_hoops_AHPGR = true;
			} _hoops_RGGA (--count == 0);

			/*??? _hoops_HAR _hoops_GGR _hoops_SAGCI */
			if (_hoops_SPRI->_hoops_RSAPA != _hoops_IPRI->point_count &&
				_hoops_IPRI->_hoops_GIGPR != null) {
				Polymarker *pm = _hoops_IPRI->_hoops_GIGPR;
				_hoops_IPRI->_hoops_AGRHR &= ~_hoops_ASAPA;
				do {
					pm->_hoops_SACI.flags &= ~_hoops_ASAPA;
				} while ((pm = pm->next) != null);
			}

			if (_hoops_AHPGR)
				HE_WARNING (HEC_MUNSET, HES_MISSING, "One or more settings were not present in the range specified");

			HI_Invalidate_Display_Lists (context, _hoops_IPRI);
			_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR);
		}
	}

	_hoops_IRRPR();
#endif
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_MShow_Spec_Vertex_Parameters (
	Key								key,
	int								count,
	int	const *						indices,
	int	alter *						number_parameters,
	float alter *					user_parameters) 
{
	_hoops_PAPPR context("MShow_Specific_Vertex_Parameters");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#	ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
#	else
#		ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#		else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Specific_Vertex_Parameters () */\n");
	);

	int	_hoops_HASII;
	int	_hoops_IASII = _hoops_APGCI(context, key, 0, count, indices, null, number_parameters, user_parameters, &_hoops_HASII);

	//_hoops_RPP _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_RHHS _hoops_PCCP _hoops_RIHH, _hoops_SAHR _hoops_CASI _hoops_GH _hoops_PPR _hoops_PHHR _hoops_RISII
	if(_hoops_HASII)
		return;

	//_hoops_RARIR
	if (count != _hoops_IASII) {
		HE_ERROR (HEC_PARAMETER, HES_NO_LOCAL_SETTING, "Not all requested vertex parameters are explicitly set");
		return;
	}

#		endif
#	endif
#endif
}


HC_INTERFACE void HC_CDECL HC_MShow_Vertex_Parameter_Size (
	Key						key,
	int *					number_parameters) 
{
	_hoops_PAPPR context("MShow_Vertex_Parameter_Size");

#ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
#else
#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_MShow_Vertex_Parameter_Size () */\n");
	);

	_hoops_CSPPR();

	Polyhedron const *	_hoops_IPRI = (Polyhedron const *)_hoops_RCSSR (context, key);

	if (_hoops_IPRI == null ||
		!(_hoops_IPRI->type == _hoops_SCIP || _hoops_IPRI->type == _hoops_GSIP) ||
		BIT (_hoops_IPRI->_hoops_RRHH, _hoops_HGAGR))
		HE_ERROR (HEC_GEOMETRY, HES_INVALID_KEY, "Key does not refer to a valid shell or mesh");
	else
		*number_parameters = _hoops_IPRI->local_vertex_attributes.param_width;

	_hoops_IRRPR();
#endif
#endif
#endif
}





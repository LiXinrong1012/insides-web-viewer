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
 * $Id: obf_tmp.txt 1.46 2010-08-25 01:47:58 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


HC_INTERFACE void HC_CDECL HC_Set_Parameter (
	int				number_parameters,
	float const *	parameters)
{
	_hoops_PAPPR context("Set_Parameter");

#ifdef DISABLE_GEOMETRY_ATTRIBUTES
	_hoops_IRPPR ("Geometry Attributes");
#else
#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Set_Parameter () */\n");
	);

	Local_Vertex_Flags *		flags;
	_hoops_RSSH *					_hoops_HAGCI;
	int							i;

	if (number_parameters == 0) {
		/* _hoops_SRH, _hoops_HIH _hoops_HAR _hoops_CPPPR _hoops_PSIGA! */
		return;
	}

	if (context->open_list == null || context->open_list->_hoops_GCRIR != _hoops_SCRIR) {
	  HE_ERROR (HEC_PARAMETER, HES_OPEN_VERTEX_ONLY, "Can 'set parameter' only on an open vertex");
	  return;
	}

	_hoops_RPPPR();

	Polyhedron *	_hoops_IPRI = context->open_list->info._hoops_IPRI._hoops_IGRPR;
	int	offset = context->open_list->info._hoops_IPRI.offset;
	Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

	if (_hoops_IPRI->local_vertex_attributes.params == null ||
		_hoops_IPRI->local_vertex_attributes.param_width < number_parameters)
			HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_ASAPA, number_parameters);

	_hoops_HAGCI = &_hoops_IPRI->local_vertex_attributes.params
						[offset*_hoops_IPRI->local_vertex_attributes.param_width];

	for (i=0; i<number_parameters; i++) {
		_hoops_HAGCI[i] = parameters[i];
	}

	/* _hoops_APSH _hoops_PII _hoops_SR'_hoops_ASAR _hoops_AHCA _hoops_IS _hoops_ARP _hoops_IRS _hoops_RHPC _hoops_GPP _hoops_SAHR _hoops_SPR _hoops_GPHA, _hoops_HIS
		_hoops_SR'_hoops_GCPP _hoops_PAHH _hoops_RRP _hoops_IRS _hoops_IIRRA->_hoops_SGI _hoops_CRPR */
	if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
		int i = 0;
		ZALLOC_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
		for (i = 0; i < _hoops_IPRI->point_count; i++)
			_hoops_IPRI->local_vertex_attributes.flags[i] = _hoops_IPRI->local_vertex_attributes._hoops_SGRHR;
		_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
	}

	flags = _hoops_IPRI->local_vertex_attributes._hoops_CHHPR(offset);

	if (!BIT (*flags, _hoops_ASAPA)) {
		++_hoops_IPRI->local_vertex_attributes._hoops_RSAPA;
		*flags |= _hoops_ASAPA;
		_hoops_SASIR (context, _hoops_IPRI, _hoops_CAHRA);
	}

	if (_hoops_SPRI->lvf_uniform(_hoops_IPRI->point_count)) {
		_hoops_SPRI->_hoops_SGRHR = _hoops_SPRI->flags[0];
		FREE_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
		_hoops_IPRI->polyhedron_flags &= ~_hoops_CGRHR;
		_hoops_SPRI->flags = 0;
	}

	_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR);

	_hoops_IRRPR();
#endif
#endif
}



HC_INTERFACE void HC_CDECL HC_UnSet_Parameter (void)
{
	_hoops_PAPPR context("UnSet_Parameter");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Parameter ();\n");
	);

	if (context->open_list == null) {
		HE_ERROR (HEC_VERTEX, HES_PARAMETER, "Can only 'unset parameter' on an open vertex");
		return;
	}
	switch (context->open_list->_hoops_GCRIR) {
		default: {
			HE_ERROR (HEC_VERTEX, HES_PARAMETER, "Can only 'unset parameter' on an open vertex");
			return;
		}	_hoops_HHHI;

#ifndef DISABLE_GEOMETRY_ATTRIBUTES
		case _hoops_SCRIR: {
			Polyhedron *				_hoops_IPRI = context->open_list->info._hoops_IPRI._hoops_IGRPR;
			int							offset = context->open_list->info._hoops_IPRI.offset;
			Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
			Local_Vertex_Flags *		flags = _hoops_SPRI->_hoops_CHHPR(offset);

			if (!BIT (*flags, _hoops_ASAPA)) {
				HE_ERROR (HEC_VERTEX, HES_PARAMETER, "No parameter set on this vertex");
				return;
			}

			_hoops_RPPPR();


			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				/* _hoops_SR _hoops_HS _hoops_SAHR _hoops_IPPRA _hoops_IRS _hoops_RHPC _hoops_GPP _hoops_IRS _hoops_RSRA _hoops_GPHA.  _hoops_CGP _hoops_RIAGR _hoops_RPII _hoops_GRP _hoops_RH
				_hoops_GHRHR _hoops_RIP, _hoops_SR _hoops_PAH'_hoops_RA _hoops_CPRIR _hoops_PPR _hoops_SR _hoops_HS _hoops_IS _hoops_CCPP _hoops_RH _hoops_IIRRA->_hoops_SGI _hoops_CRPR (_hoops_PPR _hoops_HSPC _hoops_SCH _hoops_IS _hoops_RH _hoops_GHRHR _hoops_RIP)*/
				ZALLOC_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
				for (int i = 0; i < _hoops_IPRI->point_count; i++)
					_hoops_IPRI->local_vertex_attributes.flags[i] = _hoops_IPRI->local_vertex_attributes._hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
				flags = _hoops_SPRI->_hoops_CHHPR(offset);
			}

			*flags &= ~_hoops_ASAPA;

			if (--_hoops_SPRI->_hoops_RSAPA == 0) {
				FREE_ARRAY (_hoops_SPRI->params, (_hoops_IPRI->point_count +
											_hoops_IPRI->_hoops_GCRHR)*_hoops_SPRI->param_width, _hoops_RSSH);
				_hoops_SPRI->params = null;
				_hoops_SPRI->param_width = 0;
			}
			else {
				_hoops_CRAGI(&_hoops_SPRI->params[offset*_hoops_SPRI->param_width], _hoops_SPRI->param_width);
			}

			if (_hoops_SPRI->lvf_uniform(_hoops_IPRI->point_count)) {
				_hoops_SPRI->_hoops_SGRHR = _hoops_SPRI->flags[0];
				FREE_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
				_hoops_IPRI->polyhedron_flags &= ~_hoops_CGRHR;
				_hoops_SPRI->flags = 0;
			}

			_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR);
			_hoops_IRRPR();
		}	break;
#endif
	}
#endif
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Parameter_Size (
	int *		number_parameters)
{
	_hoops_PAPPR context("Show_Parameter_Size");

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
		HI_Dump_Code ("/* HC_Show_Parameter_Size () */\n");
	);

	if (context->open_list == null || context->open_list->_hoops_GCRIR != _hoops_SCRIR) {
		HE_ERROR (HEC_PARAMETER, HES_OPEN_VERTEX_ONLY, "Can only 'show parameter size' on an open vertex");
		*number_parameters = 0;
		return;
	}

	_hoops_CSPPR();

	Polyhedron *			_hoops_IPRI = context->open_list->info._hoops_IPRI._hoops_IGRPR;
	Local_Vertex_Flags *	flags = _hoops_IPRI->local_vertex_attributes._hoops_CHHPR(context->open_list->info._hoops_IPRI.offset);

	if (!BIT (*flags, _hoops_ASAPA))
		*number_parameters = 0;
	else
		*number_parameters = _hoops_IPRI->local_vertex_attributes.param_width;

	_hoops_IRRPR();
#endif
#endif
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Parameter (
	int *		number_parameters,
	float *		parameters)
{
	_hoops_PAPPR context("Show_Parameter");

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
		HI_Dump_Code ("/* HC_Show_Parameter () */\n");
	);

	_hoops_RSSH			*params;
	Integer32			param_width;
	Polyhedron			*_hoops_IPRI;
	Local_Vertex_Flags	*flags;
	Integer32			offset;

	if (context->open_list == null || context->open_list->_hoops_GCRIR != _hoops_SCRIR) {
		HE_ERROR (HEC_PARAMETER, HES_OPEN_VERTEX_ONLY, "Can only 'show parameter' on an open vertex");
		if (number_parameters)
			*number_parameters = 0;
		return;
	}

	_hoops_CSPPR();

	_hoops_IPRI = context->open_list->info._hoops_IPRI._hoops_IGRPR;
	offset = context->open_list->info._hoops_IPRI.offset;
	params = _hoops_IPRI->local_vertex_attributes.params;
	param_width = _hoops_IPRI->local_vertex_attributes.param_width;
	flags = _hoops_IPRI->local_vertex_attributes._hoops_CHHPR(offset);

	if (!BIT (*flags, _hoops_ASAPA)) {
		HE_ERROR (HEC_PARAMETER, HES_NO_LOCAL_SETTING, "No vertex parameter is explicitly set here");
		if (number_parameters)
			*number_parameters = 0;
	}
	else {
		if (number_parameters)
			*number_parameters = param_width;

		if (parameters)
			_hoops_IRAGI(params, offset, parameters, param_width);
	}

	_hoops_IRRPR();
#endif
#endif
#endif
}


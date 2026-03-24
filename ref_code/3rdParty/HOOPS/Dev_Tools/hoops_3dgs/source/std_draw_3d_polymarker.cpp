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
 * $Id: obf_tmp.txt 1.155 2010-11-24 06:19:43 heppe Exp $
 */

#include "hoops.h"
#include "phdraw.h"
#include "tandt.h"				/* _hoops_IH _hoops_PCACS */
#include "driver.h"
#include "database.h"
#include "phedron.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hc_proto.h"

#ifndef DISABLE_DRAW_3D


#define _hoops_HCACS 4096


#define _hoops_ICACS(nr, mat, point, color, plane, _hoops_ASACP, params, param_width, param_flags, _hoops_GGPCP) do {	\
		if (!ANYBIT (nr->transform_rendition->_hoops_IPH->data._hoops_RAGR, _hoops_CICH))					\
			_hoops_ISACP (nr, nr->_hoops_SCP->_hoops_AGP,														\
								 mat, point, color, plane, _hoops_ASACP, params, param_width, param_flags, _hoops_GGPCP, null);			\
		else																													\
			_hoops_GSACP (nr, mat, point, color, plane, _hoops_ASACP, params, param_width, param_flags, _hoops_GGPCP);		\
	} while (0)


local void _hoops_GSACP (
	Net_Rendition const &		nr,
	_hoops_HHA const &	_hoops_ISHIR,
	Point const *				_hoops_CCACS,
	RGB const *					color,
	_hoops_ARPA const *				plane,
	Vector const *				_hoops_ASACP,
	_hoops_RSSH const *			params,
	Integer32					param_width,
	_hoops_SSIC				param_flags,
	RGBA alter *				total)
{
	Point						_hoops_SCACS;
	_hoops_RPRA const *			elements = nr->transform_rendition->_hoops_IPH->data.elements;

	_hoops_SCACS.x = _hoops_HPRA (elements, *_hoops_CCACS);
	_hoops_SCACS.y = _hoops_IPRA (elements, *_hoops_CCACS);
	_hoops_SCACS.z = _hoops_CPRA (elements, *_hoops_CCACS);

	_hoops_ISACP (nr, nr->_hoops_SCP->_hoops_AGP,
						 _hoops_ISHIR, &_hoops_SCACS, color, plane, _hoops_ASACP,
						 params, param_width, param_flags, total, null);
}
#endif

#if 0
local void _hoops_GSACS (
	Net_Rendition const &nr,
	Polyhedron const *_hoops_IPRI,
	RGB *vcolors)
{
	Local_Vertex_Flags const *	flags;
	RGB const *					_hoops_HCPGS;
	_hoops_ACGHR const *	_hoops_HHACP;
	RGB alter *					vcolors;
	int							remaining;
	_hoops_RHAH const *			_hoops_CSIR;
	RGB							_hoops_RSACS;
	Local_Vertex_Attributes const *_hoops_SPRI;
	bool						_hoops_SIAIS;

	_hoops_ASACS(_hoops_RSACS);

	_hoops_SIAIS = ALLBITS (nr->_hoops_IRR->_hoops_CSA,
								 (_hoops_RHRAP & ~_hoops_AHGI));

	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

	flags = _hoops_SPRI->flags;
	_hoops_HCPGS = _hoops_SPRI->_hoops_PAHIR;
	_hoops_HHACP = _hoops_SPRI->_hoops_HAHIR;
	remaining = _hoops_IPRI->point_count;

	if (_hoops_SPRI->_hoops_PCRRA +
		_hoops_SPRI->_hoops_ICRRA < _hoops_IPRI->point_count)
		_hoops_RSACS = nr->_hoops_SCP->_hoops_CHA->_hoops_CSHR;

	_hoops_CSIR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;

	do {
#ifndef DISABLE_COLOR_MAPS
		if (BIT (*flags, _hoops_SIRRA)) {
			if (_hoops_CSIR->length == 0) {
				HD_Report_Null_Color_Map ("polymarker", _hoops_CSIR);
				_hoops_ASACS (*vcolors);
			}
			else {
				_hoops_ICRCP (_hoops_CSIR, *_hoops_HHACP, *vcolors, _hoops_SIAIS, false);
			}
		}
		else
#endif
		if (BIT (*flags, _hoops_HCRRA))
			*vcolors = *_hoops_HCPGS;
		else					/* _hoops_HPP _hoops_SHIR */
			*vcolors = _hoops_RSACS;

		if (BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI) ||
			nr->_hoops_SRA->options._hoops_SIAH) {
			*vcolors = RGB(vcolors->_hoops_CPIR());
		}

		++flags;
		++_hoops_HCPGS;
		++_hoops_HHACP;
		++vcolors;
	} _hoops_RGGA (--remaining == 0);
}
#endif


GLOBAL_FUNCTION void HD_Std_3D_Polymarker (
	Net_Rendition const &		inr,
	Polymarker const *			pm)
{
#ifndef DISABLE_DRAW_3D
	Net_Rendition				nr = inr;
	int const *					vi = pm->_hoops_AIHA;
	_hoops_RSSH const *			params = null;
	_hoops_RSSH const *			_hoops_PSACS = null;
	int							param_width = 0;
	RGBA alter *				colors = null;
	int							length = pm->length;
	int							point_count = pm->point_count;
	int							offset = -1;
	_hoops_RHAH const *			_hoops_CSIR;
	int							_hoops_APRCP;
	Net_Rendition alter *		_hoops_SPRCP = null;
	DC_Point alter				*_hoops_GHPCP, *_hoops_CGCAR = null;
	float alter					*ws, *_hoops_HSACS = null;
	_hoops_GRCAR alter				*_hoops_ARCAR, *_hoops_ISACS;
	_hoops_ARPA alter					*_hoops_PGPCP = null;
	int							_hoops_CRCAR = -1;
	bool						_hoops_SIAIS;
	_hoops_AHAH const &				_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;
	bool						_hoops_GAHHP = BIT (_hoops_PHAH.options, _hoops_CHRH);

	if (BIT(nr->_hoops_SRA->flags, _hoops_CHSI))
		return;

	//_hoops_RPP(_hoops_SCII->_hoops_CSACS->_hoops_PPCRC != 0.0){
		//_hoops_RSHS = (_hoops_SCSH)((_hoops_AIIC)_hoops_RSHS * _hoops_SCII->_hoops_SRPHC->_hoops_PPCRC);
		//_hoops_SPCC = _hoops_RSHS;
	length = (int)((float)length * nr->_hoops_SCP->_hoops_CSRS);
//	}

	if (point_count == 0) {
		if (vi) {
			int len = pm->length;
			while (len-- > 0) {
				if ((offset = *vi++) > point_count)
					point_count = offset;
			}
			++point_count;	/* _hoops_AGRP _hoops_HII _hoops_AHPA _hoops_CIHA _hoops_IS _hoops_RPR */
		}
		else {
			point_count = length;
		}
		if (!length)
			return;
	}

	if (point_count > _hoops_HCACS) {
		int i = 0;
		int _hoops_HCGS;
		int start, end;
		Polymarker *_hoops_AHPIS;

		start = 0;
		do {
			end = _hoops_HCACS + start;
			if (end > length)
				end = length;
			ZALLOC (_hoops_AHPIS, Polymarker);
			_hoops_ICAI(_hoops_AHPIS);
			_hoops_AHPIS->point_count = end - start;
			_hoops_AHPIS->length = _hoops_AHPIS->point_count;
			_hoops_AHPIS->_hoops_GSCP = pm->_hoops_GSCP;
			_hoops_AHPIS->bounding = pm->bounding;
			_hoops_AHPIS->_hoops_GSHA = pm->_hoops_GSHA;
			_hoops_AHPIS->_hoops_SCAI = pm->_hoops_SCAI;
			ALLOC_ARRAY_ALIGNED (_hoops_AHPIS->points, _hoops_AHPIS->point_count, Point, 16);
#ifndef DISABLE_GEOMETRY_ATTRIBUTES
#  ifndef _hoops_GCGHR
			if (pm->_hoops_PCHA != null)
				ALLOC_ARRAY (_hoops_AHPIS->_hoops_PCHA, _hoops_AHPIS->point_count, RGB);
			if (pm->_hoops_RGIA != null)
				ALLOC_ARRAY (_hoops_AHPIS->_hoops_RGIA, _hoops_AHPIS->point_count, RGBAS32);
			if (pm->_hoops_HCHA != null)
				ALLOC_ARRAY (_hoops_AHPIS->_hoops_HCHA, _hoops_AHPIS->point_count, _hoops_ACGHR);
#  endif
#  ifndef _hoops_HCGHR
			if (pm->_hoops_ICHA != null)
				ALLOC_ARRAY (_hoops_AHPIS->_hoops_ICHA, _hoops_AHPIS->point_count, Vector);
#  endif
#  ifndef DISABLE_TEXTURING
			if (pm->_hoops_CCHA != null)
				ALLOC_ARRAY (_hoops_AHPIS->_hoops_CCHA, _hoops_AHPIS->point_count * pm->_hoops_GSHA, _hoops_RSSH);
#  endif
#endif
			_hoops_AHPIS->_hoops_RAHH = _hoops_RRCGP;  //_hoops_RH _hoops_CCAH _hoops_PAAI _hoops_ARPSP _hoops_CPS _hoops_SCH _hoops_PRCHR

			_hoops_HCGS = start - 1;
			for (i = start; i < end ; i++) {
				if (pm->_hoops_AIHA)
					_hoops_HCGS = pm->_hoops_AIHA[i];
				else
					_hoops_HCGS++;
				_hoops_AHPIS->points[i-start] = pm->points[_hoops_HCGS];
				if (pm->_hoops_ICHA)
					_hoops_AHPIS->_hoops_ICHA[i-start] = pm->_hoops_ICHA[_hoops_HCGS];
				if (pm->_hoops_PCHA)
					_hoops_AHPIS->_hoops_PCHA[i-start] = pm->_hoops_PCHA[_hoops_HCGS];
				if (pm->_hoops_RGIA)
					_hoops_AHPIS->_hoops_RGIA[i-start] = pm->_hoops_RGIA[_hoops_HCGS];
				if (pm->_hoops_HCHA)
					_hoops_AHPIS->_hoops_HCHA[i-start] = pm->_hoops_HCHA[_hoops_HCGS];
			}
			HD_Std_3D_Polymarker (nr, _hoops_AHPIS); //_hoops_GHHA!!
			if (_hoops_ISAI (_hoops_AHPIS) == 0)
				HI_Free_Polymarker (_hoops_AHPIS);
			start = end;
		} while (end < length);
		return;
	}

	ALLOC_ARRAY_ALIGNED_CACHED (_hoops_CGCAR, point_count, DC_Point, 16);
	ALLOC_ARRAY_ALIGNED_CACHED (_hoops_HSACS, point_count, float, 16);
	ZALLOC_ARRAY_CACHED (_hoops_ISACS, point_count, _hoops_GRCAR);

	/* _hoops_RPCRC: _hoops_IRCHS _hoops_RGR _hoops_AIRCP _hoops_HRGR _hoops_RIHGH _hoops_ARSSA _hoops_SSACS
	 _hoops_CCA _hoops_PPSR _hoops_GGPCS _hoops_GGR _hoops_AGRCP*/
	if (BIT(nr->_hoops_CPP->_hoops_PRH._hoops_SRI, _hoops_RRAAP) &&
		nr->_hoops_CPP->_hoops_PRH._hoops_RGGIP) {
	//_hoops_RPP(! _hoops_ARGCS->_hoops_GHCSR->_hoops_CPHSR._hoops_RGPCS){
		_hoops_CRCAR = point_count;
	}
	else {
		_hoops_CRCAR = HD_Acquire_Clip_Points (nr,
			pm->bounding,
			point_count,
			pm->points,
			_hoops_CGCAR,
			_hoops_HSACS,
			_hoops_ISACS);
	}

	if (_hoops_CRCAR == 0) {
		goto _hoops_HPAGR;
	}

	_hoops_GHPCP = _hoops_CGCAR;
	ws = _hoops_HSACS;
	_hoops_ARCAR = _hoops_ISACS;
	_hoops_SIAIS = ALLBITS (nr->_hoops_IRR->_hoops_CSA,
								 _hoops_RHRAP & ~_hoops_AHGI);




#if 1
	if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH &&
		!BIT (pm->_hoops_SRHA, DL_DO_NOT_DEFER) &&
		!BIT (pm->_hoops_SRHA, DL_3D_TRANSPARENCY) &&
		BIT (nr->_hoops_CPP->_hoops_PRH._hoops_SRI, _hoops_HSSS) &&
		nr->_hoops_CPP->_hoops_PRH._hoops_RGGIP &&
		nr->_hoops_CPP->_hoops_PRH.style != _hoops_GCPI) {
		int flags = 0;
		int i, _hoops_AGPCS = 0;

		if (point_count != _hoops_CRCAR) {
			for (i = 0; i < point_count; i++)
				_hoops_AGPCS |= _hoops_ARCAR[i];
		}

		if (!BIT(_hoops_AGPCS, _hoops_IPCAR)) {
			/* _hoops_PSCPR _hoops_RH _hoops_PAAI */
			HD_Hide_3D_Polymarker (nr, pm, flags, _hoops_GHPCP);

			/*_hoops_RPP (_hoops_HSAGA->_hoops_AAGGR > 1)
			_hoops_PGPCS (_hoops_HSAGA);*/	/* _hoops_SHI _hoops_HHHA _hoops_HGPCS _hoops_ARRS */

			goto _hoops_HPAGR;
		}
	}
#endif




#ifndef DISABLE_COLOR_MAPS
	_hoops_CSIR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;
	_hoops_APRCP = _hoops_CSIR->length;

	if (pm->_hoops_HCHA != null) {
		Named_Material const *		_hoops_ISHIR;
		_hoops_ARGRA			_hoops_PRGRA;

#ifndef DISABLE_TEXTURING
		if (nr->_hoops_SCP->_hoops_CHA->_hoops_ARIR) {
			int							i;

			_hoops_ICP alter &	_hoops_CCP = nr.Modify()->_hoops_GSP.Modify();
			_hoops_HHA alter &	mat = _hoops_CCP->_hoops_CHA.Modify();
			nr->_hoops_SCP = _hoops_CCP;

			HI_Free_Diffuse_Channel_List (mat->_hoops_SCA);
			mat->_hoops_SCA = null;
			for (i=0; i<_hoops_GAGRA; i++)
				if (mat->texture[i] != null) {
					_hoops_HPRH (mat->texture[i]);
					mat->texture[i] = null;
				}

			mat->_hoops_ARIR = false;
		}
#endif

		_hoops_ISHIR = _hoops_CSIR->_hoops_HAA;
		_hoops_PRGRA = 0;
		if (_hoops_APRCP > 0) do {
			_hoops_PRGRA |= _hoops_ISHIR->_hoops_PRGRA;
			++_hoops_ISHIR;
		} _hoops_RGGA (--_hoops_APRCP == 0);
		_hoops_APRCP = _hoops_CSIR->length;

#ifndef DISABLE_TEXTURING
		/* _hoops_SGH _hoops_GRPAR _hoops_RGAR _hoops_RPP _hoops_SR _hoops_HGCR _hoops_GII _hoops_AI _hoops_HII _hoops_RH _hoops_ARCR */
		if (pm->_hoops_RPRCP || !ANYBIT (_hoops_PRGRA, _hoops_PSARA))
#endif
			params = null;
	}
	else
#endif
	{
		params = pm->_hoops_CCHA;
		param_width = pm->_hoops_GSHA;

#ifndef DISABLE_TEXTURING
		if (pm->_hoops_RPRCP || !nr->_hoops_SCP->_hoops_CHA->_hoops_ARIR)
#endif
			params = null;
	}

	if (pm->_hoops_ICHA != null || params != null ||
		BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HPH)) {
		_hoops_ICP const &	_hoops_CCP = nr->_hoops_SCP;
		_hoops_ARPA const *				planes = null;
		_hoops_ARPA const *				plane = null;

		if (!colors)
			ALLOC_ARRAY_CACHED (colors, point_count, RGBA);

		if ((planes = _hoops_PGPCP) == null) {
			if (pm->_hoops_ICHA != null) {
				ALLOC_ARRAY_CACHED (_hoops_PGPCP, point_count, _hoops_ARPA);

				HD_Compute_World_Vertex_Planes (nr,
												point_count,
												pm->points,
												pm->_hoops_ICHA,
												_hoops_PGPCP);
			}
			else if (params != null) {
				ZALLOC_ARRAY_CACHED (_hoops_PGPCP, point_count, _hoops_ARPA);
			}

			planes = _hoops_PGPCP;
		}

		if (_hoops_SPRCP != null) {
			float *						findex = pm->_hoops_HCHA;
			_hoops_HHA			use;

			while (length-- > 0) {
				RGBA					tmp;

				if (vi)
					offset = *vi++;
				else
					offset++;

				use = _hoops_SPRCP[(int)(findex[offset] + 0.5f) % _hoops_APRCP]->_hoops_SCP->_hoops_CHA;

				if (planes != null) plane = &planes[offset];

#ifndef DISABLE_TEXTURING
				if (params != null)
					_hoops_ICACS (nr, use, &pm->points[offset], null, plane,	 null,
													 &params[offset*pm->_hoops_GSHA], pm->_hoops_GSHA, 0, &tmp);
				else
#endif
					_hoops_ICACS (nr, use, &pm->points[offset], null, plane, null, null, 0, 0, &tmp);

				if (_hoops_GAHHP)
					colors[offset] = HD_Apply_Color_Effects (tmp, _hoops_PHAH);
				else
					colors[offset] = tmp;
				colors[offset].alpha = 1.0f;
			}
		}
		else {
			_hoops_AHAH 		_hoops_SHAIS;

			while (length-- > 0) {
				RGB const *		_hoops_IASGR = null;
				RGBA			tmp;
				RGB				buf;

				if (vi)
					offset = *vi++;
				else
					offset++;

				if (planes != null)
					plane = &planes[offset];
				if (pm->_hoops_HCHA) {
					_hoops_ICRCP (_hoops_CSIR, pm->_hoops_HCHA[offset], buf, _hoops_SIAIS, _hoops_SHAIS);
					_hoops_IASGR = &buf;
				}
				else if (pm->_hoops_PCHA)
					_hoops_IASGR = &pm->_hoops_PCHA[offset];

#ifndef DISABLE_TEXTURING
				if (params != null) {
					_hoops_PSACS = &params[offset*pm->_hoops_GSHA];
					param_width = pm->_hoops_GSHA;
				}
#endif
				_hoops_ICACS (
								nr,
								_hoops_CCP->_hoops_CHA,
								&pm->points[offset],
								_hoops_IASGR,
								plane,
								null,
								_hoops_PSACS,
								param_width,
								0,
								&tmp);
				if (_hoops_GAHHP)
					colors[offset] = HD_Apply_Color_Effects (tmp, _hoops_PHAH);
				else
					colors[offset] = tmp;
				colors[offset].alpha = 1.0f;
			}
		}
	}
	else if (pm->_hoops_RGIA) {
		if (!colors)
			ALLOC_ARRAY_CACHED (colors, point_count, RGBA);

		while (length-- > 0) {
			if (vi)
				offset = *vi++;
			else
				offset++;

			{
				RGBA		_hoops_IASGR = pm->_hoops_RGIA[offset];

				if (_hoops_GAHHP) {
					RGB		tmp = _hoops_IASGR;
					tmp = HD_Apply_Color_Effects (tmp, _hoops_PHAH);
					colors[offset] = RGBA (tmp, _hoops_IASGR.alpha);
				}
				else
					colors[offset] = _hoops_IASGR;
			}
		}
	}
	else if (pm->_hoops_HCHA || pm->_hoops_PCHA) {
		if (!colors)
			ALLOC_ARRAY_CACHED (colors, point_count, RGBA);

		while (length-- > 0) {
			if (vi)
				offset = *vi++;
			else
				offset++;

			if (pm->_hoops_HCHA)
				_hoops_ICRCP (_hoops_CSIR, pm->_hoops_HCHA[offset], *(RGB *)&colors[offset], _hoops_SIAIS, _hoops_PHAH);
			else {
				RGB const *		_hoops_IASGR =  &pm->_hoops_PCHA[offset];

				if (_hoops_GAHHP)
					colors[offset] = HD_Apply_Color_Effects (*_hoops_IASGR, _hoops_PHAH);
				else
					colors[offset] = *_hoops_IASGR;
			}
			colors[offset].alpha = 1.0f;
		}
	}


	if (nr->_hoops_GSP != nr->_hoops_SCP)
		nr.Modify()->_hoops_GSP = nr->_hoops_SCP;

	if (nr->_hoops_GSP->ysize < 0) {
		_hoops_ICP alter &	_hoops_HCSHP = nr->_hoops_GSP;
		float						size;

		size = HD_Compute_Generic_Size (nr, _hoops_HCSHP->_hoops_PHP, _hoops_HCSHP->_hoops_HHP, 1.0f, false, 0, true);
		_hoops_HCSHP->ysize = size*0.5f;
		_hoops_HCSHP->_hoops_RGRS = size*0.5f*nr->_hoops_SRA->current._hoops_AGRS;
	}

	/* _hoops_PAGA: _hoops_HPPA-_hoops_GHC, _hoops_RPP _hoops_GII, _hoops_AAPR _hoops_RPCSH _hoops_HPP _hoops_GRRAR-_hoops_HSPH-_hoops_RSSA, _hoops_HIH _hoops_RGAR _hoops_SIGH
	 * _hoops_SGS _hoops_RH _hoops_PPSR _hoops_CSAP _hoops_AACC _hoops_SGGR _hoops_GGR _hoops_SPR _hoops_HPPA _hoops_ARP, _hoops_SCH _hoops_GHCA _hoops_SHH _hoops_SIGC _hoops_GGR _hoops_HIASR
	 */
	{
		DC_Point alter *		_hoops_ACGRI = 0;
		RGBAS32 alter *			_hoops_IGPCS = 0;
		DC_Point alter *		_hoops_CGPCS = 0;
		RGBAS32 alter *			_hoops_SGRRS = 0;
		float alter	*			size_fixups = 0, *_hoops_SGPCS=0;
		unsigned char			_hoops_IRIR = _hoops_GPGCR;
		_hoops_HRPA				_hoops_PHSC;
		float					z = 0, _hoops_SRIR = 0;

		ZERO_STRUCT (&_hoops_PHSC, _hoops_HRPA);

		ALLOC_ARRAY_CACHED (_hoops_ACGRI, point_count, DC_Point);
		_hoops_CGPCS = _hoops_ACGRI;

		if (colors) {
			ALLOC_ARRAY_CACHED (_hoops_IGPCS, point_count, RGBAS32);
			_hoops_SGRRS = _hoops_IGPCS;

			if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH)
				_hoops_IRIR = (unsigned char)(255.99f *
					nr->_hoops_GSP->_hoops_CHA->_hoops_IRIR);
		}

		vi = pm->_hoops_AIHA;
		length = pm->length;
		length = (int)((float)pm->length * nr->_hoops_SCP->_hoops_CSRS);
		//_hoops_SPCC = _hoops_RSHS;


		offset = -1;

		if (nr->_hoops_GSP->_hoops_HHP == _hoops_SPSC &&
			nr->transform_rendition->_hoops_SPH->projection == _hoops_GHH) {
			_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
			ALLOC_ARRAY_CACHED (size_fixups, point_count, float);
			_hoops_SGPCS = size_fixups;
			HI_Multiply_Matrices (&_hoops_IHCR->_hoops_IPH->data,
								  &_hoops_IHCR->_hoops_SPH->_hoops_PRPA,
								  &_hoops_PHSC);
			_hoops_SRIR = _hoops_IHCR->_hoops_SPH->_hoops_SRIR;
		}

		while (length-- > 0) {
			if (vi)
				offset = *vi++;
			else
				offset++;

			if ((_hoops_ARCAR[offset] & ~_hoops_RPCAR) == _hoops_HCRCP &&
				(!BIT(_hoops_ARCAR[offset], _hoops_RPCAR) ||
				 HD_Point_Within_Cutting_Planes (nr->transform_rendition,
												 _hoops_GHPCP[offset].x, _hoops_GHPCP[offset].y, _hoops_GHPCP[offset].z))) {
				_hoops_CGPCS->x = _hoops_GHPCP[offset].x;
				_hoops_CGPCS->y = _hoops_GHPCP[offset].y;
				_hoops_CGPCS->z = _hoops_GHPCP[offset].z;
				_hoops_CGPCS++;
				if (size_fixups) {
					z = _hoops_CPRA (_hoops_PHSC.elements, pm->points[offset]);
					z /= _hoops_SRIR;
					*_hoops_SGPCS++ = 1 / (z + 1);
				}
				if (colors) {
					_hoops_SGRRS[0] = RGBAS32 (colors[offset], _hoops_IRIR);
					_hoops_SGRRS++;
				}
			}
		}

		if (_hoops_CGPCS - _hoops_ACGRI > 0) {	/* _hoops_GII _hoops_AIPAA? */
			if (colors)
				_hoops_PGIGH (nr, _hoops_CGPCS-_hoops_ACGRI, _hoops_ACGRI, _hoops_IGPCS, false, null, size_fixups);
			else
				_hoops_AGIGH(nr, _hoops_CGPCS-_hoops_ACGRI, _hoops_ACGRI, null, size_fixups);
		}

		FREE_ARRAY (_hoops_ACGRI, point_count, DC_Point);
		if (_hoops_IGPCS) {
			FREE_ARRAY (_hoops_IGPCS, point_count, RGBAS32);
			_hoops_IGPCS = null;
		}
		if (size_fixups) {
			FREE_ARRAY (size_fixups, point_count, float);
			size_fixups = null;
		}
	}

#ifndef DISABLE_COLOR_MAPS
	if (_hoops_SPRCP != null) {
		Net_Rendition alter *		_hoops_PIRCP = _hoops_SPRCP;

		do {
			(*_hoops_PIRCP).release();
			++_hoops_PIRCP;
		} _hoops_RGGA (--_hoops_APRCP == 0);
		_hoops_APRCP = _hoops_CSIR->length;

		FREE_ARRAY (_hoops_SPRCP, _hoops_APRCP, Net_Rendition);
	}
#endif
#endif
  _hoops_HPAGR:
	if (colors)
		FREE_ARRAY (colors, point_count, RGBA);
	if (_hoops_CGCAR)
		FREE_ARRAY_ALIGNED (_hoops_CGCAR, point_count, DC_Point, 16);
	if (_hoops_HSACS)
		FREE_ARRAY_ALIGNED (_hoops_HSACS, point_count, float, 16);
	if (_hoops_ISACS)
		FREE_ARRAY (_hoops_ISACS, point_count, _hoops_GRCAR);
	if (_hoops_PGPCP)
		FREE_ARRAY (_hoops_PGPCP, point_count, _hoops_ARPA);

}






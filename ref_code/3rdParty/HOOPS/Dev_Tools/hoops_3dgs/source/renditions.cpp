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
 * $Id: obf_tmp.txt 1.263 2010-12-04 01:19:50 covey Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "adt.h"



GLOBAL_FUNCTION _hoops_IAPA alter * HD_Copy_Cutting_Plane_Sets (
	_hoops_IAPA const *				_hoops_AGCPH) {
	_hoops_IAPA alter *				_hoops_CICRS = null;
	_hoops_IAPA alter * alter *		_hoops_SICRS = &_hoops_CICRS;
	_hoops_IAPA alter *				_hoops_GCCRS;
	_hoops_GPPA alter * alter *	_hoops_RCCRS;
	_hoops_GPPA alter *			_hoops_ACCRS;
	_hoops_GPPA const *			_hoops_HGCPH;

	if (_hoops_AGCPH != null) do {
		ALLOC (_hoops_GCCRS, _hoops_IAPA);
		_hoops_GCCRS->_hoops_IPASP = _hoops_AGCPH->_hoops_IPASP;

		_hoops_RCCRS = (_hoops_GPPA alter * alter *)
					&_hoops_GCCRS->_hoops_APPA;

		if ((_hoops_HGCPH = _hoops_AGCPH->_hoops_APPA) != null) do {
			ALLOC (_hoops_ACCRS, _hoops_GPPA);
			_hoops_RSAI (_hoops_HGCPH, _hoops_GPPA, _hoops_ACCRS);

			*_hoops_RCCRS = _hoops_ACCRS;
			_hoops_RCCRS = &_hoops_ACCRS->next;
		} while ((_hoops_HGCPH = _hoops_HGCPH->next) != null);
		*_hoops_RCCRS = null;

		*_hoops_SICRS = _hoops_GCCRS;
		_hoops_SICRS = &_hoops_GCCRS->next;
	} while ((_hoops_AGCPH = _hoops_AGCPH->next) != null);
	*_hoops_SICRS = null;

	return _hoops_CICRS;
}

GLOBAL_FUNCTION _hoops_ASHH alter * HD_Copy_Clip_Regions (
	_hoops_ASHH const *			_hoops_PCCRS) {
	_hoops_ASHH alter *			_hoops_CICRS = null;
	_hoops_ASHH alter * alter *	_hoops_SICRS = &_hoops_CICRS;
	_hoops_ASHH alter *			_hoops_HCCRS;

	if (_hoops_PCCRS != null) do {
		ALLOC (_hoops_HCCRS, _hoops_ASHH);
		_hoops_RSAI (_hoops_PCCRS, _hoops_ASHH, _hoops_HCCRS);
		_hoops_APRGA (_hoops_PCCRS->points, _hoops_PCCRS->count, DC_Point, _hoops_HCCRS->points);
		_hoops_HCCRS->_hoops_GRCPR = null;
		_hoops_HCCRS->_hoops_HSAI = 1;


		*_hoops_SICRS = _hoops_HCCRS;
		_hoops_SICRS = &_hoops_HCCRS->next;
	} while ((_hoops_PCCRS = _hoops_PCCRS->next) != null);
	*_hoops_SICRS = null;

	return _hoops_CICRS;
}







Internal_Net_Rendition::Internal_Net_Rendition(Internal_Net_Rendition const & _hoops_HACIR)
	: _hoops_CPASP (_hoops_HACIR)
	, flags (_hoops_HACIR.flags)
	, current (_hoops_HACIR.current)
	, _hoops_RCSHR (_hoops_HACIR._hoops_RCSHR)
	, _hoops_RGPGR (_hoops_HACIR._hoops_RGPGR)
	, _hoops_RGP (_hoops_HACIR._hoops_RGP)
	, _hoops_PSGI (_hoops_HACIR._hoops_PSGI)
	, _hoops_RSGC (_hoops_HACIR._hoops_RSGC)
	, _hoops_ASIR (_hoops_HACIR._hoops_ASIR)
	, _hoops_ARA (_hoops_HACIR._hoops_ARA)
	, glyph_rendition (_hoops_HACIR.glyph_rendition)
	, _hoops_PIGIP (_hoops_HACIR._hoops_PIGIP)
	, _hoops_GCSHP (_hoops_HACIR._hoops_GCSHP)
	, _hoops_IRR (_hoops_HACIR._hoops_IRR)
	, _hoops_GCCSR (_hoops_HACIR._hoops_GCCSR)
	, transform_rendition (_hoops_HACIR.transform_rendition)
	, _hoops_GCGIP (_hoops_HACIR._hoops_GCGIP)
	, _hoops_CPP (_hoops_HACIR._hoops_CPP)

	, _hoops_RHP (_hoops_HACIR._hoops_RHP)
	, _hoops_IHA (_hoops_HACIR._hoops_IHA)
	, _hoops_AHP (_hoops_HACIR._hoops_AHP)
	, _hoops_GSP (_hoops_HACIR._hoops_GSP)
	, _hoops_SISI (_hoops_HACIR._hoops_SISI)
	, _hoops_SCP (_hoops_HACIR._hoops_SCP)
	, _hoops_SAIR (_hoops_HACIR._hoops_SAIR)

	, _hoops_CAIHP (_hoops_HACIR._hoops_CAIHP)
	, _hoops_HAIHP (_hoops_HACIR._hoops_HAIHP)
	, _hoops_AAIHP (_hoops_HACIR._hoops_AAIHP) {
}


Internal_Color_Map_Rendition::Internal_Color_Map_Rendition (Internal_Color_Map_Rendition const & _hoops_HACIR)
	: _hoops_CPASP (_hoops_HACIR)
	, _hoops_CSIR (_hoops_HACIR._hoops_CSIR)
	, _hoops_RHHHP (_hoops_HACIR._hoops_RHHHP)
	, length (_hoops_HACIR.length) {
	Driver_Color* temp;

	_hoops_CHRSH(_hoops_HACIR._hoops_AHHHP, length, Driver_Color, temp, memory_pool);
	_hoops_AHHHP = temp;
}

Internal_Cutting_Plane_Rendition::Internal_Cutting_Plane_Rendition (Internal_Cutting_Plane_Rendition const & _hoops_HACIR)
	: _hoops_CPASP (_hoops_HACIR)
	, _hoops_PGH (_hoops_HACIR._hoops_PGH)
	, _hoops_CRH (_hoops_HACIR._hoops_CRH)
	, _hoops_AHASP (_hoops_HACIR._hoops_AHASP) {

	_hoops_ISIGA =      HD_Copy_Cutting_Plane_Sets (_hoops_HACIR._hoops_ISIGA);
	_hoops_PHCA = HD_Copy_Cutting_Plane_Sets (_hoops_HACIR._hoops_PHCA);
	_hoops_IRH =   HD_Copy_Cutting_Plane_Sets (_hoops_HACIR._hoops_IRH);
}

_hoops_HHASP::_hoops_HHASP (_hoops_HHASP const & _hoops_HACIR)
	: _hoops_CPASP (_hoops_HACIR)
	, _hoops_ISRGA (_hoops_HACIR._hoops_ISRGA) {

	// _hoops_HPCAR _hoops_RH _hoops_ARH _hoops_GRS _hoops_SHH _hoops_SRSS, _hoops_HIS _hoops_IPS _hoops_RH _hoops_CPCII _hoops_PPR _hoops_HRCI _hoops_GII _hoops_GRCPH _hoops_CIHH
	_hoops_PSHH = HD_Copy_Clip_Regions (_hoops_HACIR._hoops_PSHH);
	_hoops_AHGGA = null;
}


Internal_Display_Rendition::Internal_Display_Rendition (Internal_Display_Rendition const & _hoops_HACIR)
	: _hoops_CPASP (_hoops_HACIR)
	, _hoops_PSIR (_hoops_HACIR._hoops_PSIR)
	, buffer (_hoops_HACIR.buffer)
	, _hoops_GCCI (_hoops_HACIR._hoops_GCCI)
	, window (_hoops_HACIR.window) {

	if (window.texture != null)
		_hoops_PRRH (window.texture);

	if (window._hoops_PGPH != null)
		_hoops_CAHS (window._hoops_PGPH);

	if (_hoops_HACIR.conditions.count > 0) {
		_hoops_HAHSA (_hoops_HACIR.conditions._hoops_RCHA, _hoops_HACIR.conditions.count, unsigned int, conditions._hoops_RCHA, memory_pool);
		conditions.count = _hoops_HACIR.conditions.count;
	}

	if(_hoops_HACIR.conditions._hoops_CPGIP != null) {
		_hoops_SPPIR const * _hoops_GHPIR;
		_hoops_HACIR.conditions._hoops_CPGIP->ResetCursor();
		while((_hoops_GHPIR = _hoops_HACIR.conditions._hoops_CPGIP->PeekCursor()) != null) {
			ASSERT(_hoops_GHPIR->count > 0);
			_hoops_PRRH(_hoops_GHPIR);
			_hoops_HACIR.conditions._hoops_CPGIP->AdvanceCursor();
		}
		conditions._hoops_CPGIP = POOL_NEW(memory_pool, _hoops_SPGIP)(_hoops_HACIR.conditions._hoops_CPGIP);
	}

#if 0
	for (int i=0; i<conditions.count; i++) {
		unsigned int	_hoops_RCHA = conditions._hoops_RCHA[i];
		int				index = i * 32;

		while (_hoops_RCHA != 0) {
			if ((_hoops_RCHA & 1) != 0) {
				_hoops_PRRH (HOOPS_WORLD->_hoops_PCIIR[index]);
			}
			_hoops_RCHA >>= 1;
			++index;
		}
	}
#endif

	conditions._hoops_ACPGR = HI_Copy_Conditional_Actions(_hoops_HACIR.conditions._hoops_ACPGR); 
}

Internal_Face_Rendition::Internal_Face_Rendition (Internal_Face_Rendition const & _hoops_HACIR)
	: _hoops_CPASP (_hoops_HACIR)
	, _hoops_CHA (_hoops_HACIR._hoops_CHA.Copy())
	, _hoops_GIA ()
	, _hoops_AGP (_hoops_HACIR._hoops_AGP)
	, _hoops_PGPH (_hoops_HACIR._hoops_PGPH)
	, color (_hoops_HACIR.color)
	, contrast_color (_hoops_HACIR.contrast_color)
	, _hoops_RGIR (_hoops_HACIR._hoops_RGIR)
	, _hoops_ARIHP (_hoops_HACIR._hoops_ARIHP)
	, _hoops_SCHHP (_hoops_HACIR._hoops_SCHHP)
	, _hoops_GRIHP (_hoops_HACIR._hoops_GRIHP)
	, _hoops_GSHHP (_hoops_HACIR._hoops_GSHHP)
	, _hoops_PRIHP (_hoops_HACIR._hoops_PRIHP)
	, pattern (_hoops_HACIR.pattern) {

	if (_hoops_HACIR._hoops_CHA == _hoops_HACIR._hoops_GIA)
		_hoops_GIA = _hoops_CHA;
	else
		_hoops_GIA = _hoops_HACIR._hoops_GIA.Copy();

	if (_hoops_PGPH != null)
		_hoops_CAHS (_hoops_PGPH);
}

Internal_Geometry_Rendition::Internal_Geometry_Rendition (Internal_Geometry_Rendition const & _hoops_HACIR)
	: _hoops_CPASP (_hoops_HACIR)
	, _hoops_PRSI (_hoops_HACIR._hoops_PRSI)
	, _hoops_APPI (_hoops_HACIR._hoops_APPI)
	, _hoops_APSHP (_hoops_HACIR._hoops_APSHP)
	, _hoops_GAICA (_hoops_HACIR._hoops_GAICA)
	, image (_hoops_HACIR.image)
	, _hoops_IHRH (_hoops_HACIR._hoops_IHRH)
	, geometry_options (_hoops_HACIR.geometry_options)
	, _hoops_GCIPR (_hoops_HACIR._hoops_GCIPR)
	, _hoops_CICP (_hoops_HACIR._hoops_CICP)
	, _hoops_ACP (_hoops_HACIR._hoops_ACP) {

	if (_hoops_ACP._hoops_CIAIR != 0) {
		POOL_ALLOC_ARRAY (_hoops_ACP._hoops_SIAIR, _hoops_ACP._hoops_CIAIR, float, _hoops_SRA->memory_pool);
		_hoops_AIGA (_hoops_HACIR._hoops_ACP._hoops_SIAIR, _hoops_ACP._hoops_CIAIR, float, _hoops_ACP._hoops_SIAIR);
	}

	if (_hoops_ACP._hoops_GCAIR != 0) {
		POOL_ALLOC_ARRAY (_hoops_ACP.colors, _hoops_ACP._hoops_GCAIR, RGB, _hoops_SRA->memory_pool);
		_hoops_AIGA (_hoops_HACIR._hoops_ACP.colors, _hoops_ACP._hoops_GCAIR, RGB, _hoops_ACP.colors);
	}

	if (_hoops_ACP._hoops_RCAIR != 0) {
		POOL_ALLOC_ARRAY (_hoops_ACP._hoops_ACAIR, _hoops_ACP._hoops_RCAIR, _hoops_HCRPR, _hoops_SRA->memory_pool);
		for (int i=0; i<_hoops_ACP._hoops_RCAIR; i++)
			HI_Copy_Name (&_hoops_HACIR._hoops_ACP._hoops_ACAIR[i], &_hoops_ACP._hoops_ACAIR[i]);
		POOL_ALLOC_ARRAY (_hoops_ACP._hoops_PCAIR, _hoops_ACP._hoops_RCAIR, Integer32, _hoops_SRA->memory_pool);
		_hoops_AIGA (_hoops_HACIR._hoops_ACP._hoops_PCAIR, _hoops_ACP._hoops_RCAIR, Integer32, _hoops_ACP._hoops_PCAIR);
	}

	if (_hoops_ACP.weight_count != 0) {
		POOL_ALLOC_ARRAY (_hoops_ACP.weights, _hoops_ACP.weight_count, _hoops_HCAIR, _hoops_SRA->memory_pool);
		_hoops_AIGA (_hoops_HACIR._hoops_ACP.weights, _hoops_ACP.weight_count, _hoops_HCAIR, _hoops_ACP.weights);
	}
}

Internal_Glyph_Rendition::Internal_Glyph_Rendition (Internal_Glyph_Rendition const & _hoops_HACIR)
	: _hoops_CPASP (_hoops_HACIR)
	, count (_hoops_HACIR.count) {

	if (count > 0) {
		POOL_ZALLOC_ARRAY_CACHED(glyphs, count, _hoops_GASC, memory_pool);
		for (int i=0; i<count; i++)
			glyphs[i] = _hoops_HACIR.glyphs[i];

		_hoops_CHRSH(_hoops_HACIR.keys, count, Integer32, keys, memory_pool);
	}
}

_hoops_HIASP::_hoops_HIASP (_hoops_HIASP const & _hoops_HACIR)
	: _hoops_CPASP (_hoops_HACIR)
	, count (_hoops_HACIR.count) {

	if (count > 0) {
		POOL_ZALLOC_ARRAY_CACHED(_hoops_SAAIR, count, _hoops_GPAIR, memory_pool);
		for (int i=0; i<count; i++)
			_hoops_SAAIR[i] = _hoops_HACIR._hoops_SAAIR[i];

		_hoops_CHRSH(_hoops_HACIR.keys, count, Integer32, keys, memory_pool);
	}
}

Internal_Line_Style_Rendition::Internal_Line_Style_Rendition (Internal_Line_Style_Rendition const & _hoops_HACIR)
	: _hoops_CPASP (_hoops_HACIR)
	, _hoops_IHRIP (_hoops_HACIR._hoops_IHRIP)
	, count (_hoops_HACIR.count) {

	if (count > 0) {
		POOL_ZALLOC_ARRAY_CACHED(_hoops_HPAIR, count, Line_Style, memory_pool);
		for (int i=0; i<count; i++)
			_hoops_HPAIR[i] = _hoops_HACIR._hoops_HPAIR[i];

		_hoops_CHRSH(_hoops_HACIR.keys, count, Integer32, keys, memory_pool);
	}
}

Internal_Material_Rendition::Internal_Material_Rendition (Internal_Material_Rendition const & _hoops_HACIR)
	: _hoops_CPASP (_hoops_HACIR)
	, _hoops_CSHR (_hoops_HACIR._hoops_CSHR)
	, _hoops_IRIR (_hoops_HACIR._hoops_IRIR)
	, gloss (_hoops_HACIR.gloss)
	, _hoops_PAGRA (_hoops_HACIR._hoops_PAGRA)
	, _hoops_ARIR (_hoops_HACIR._hoops_ARIR) {

	_hoops_SCA = HI_Copy_Diffuse_Channel_List (_hoops_HACIR._hoops_SCA);
	for (int i=0; i<_hoops_GAGRA; ++i) {
		color[i] = _hoops_HACIR.color[i];

		if ((texture[i] = _hoops_HACIR.texture[i]) != null)
			_hoops_PRRH (texture[i]);
	}
}


Internal_Action_Rendition::Internal_Action_Rendition (Internal_Action_Rendition const & _hoops_HACIR)
	: _hoops_CPASP (_hoops_HACIR)
	, action (_hoops_HACIR.action)
	, _hoops_PGCHP (_hoops_HACIR._hoops_PGCHP)
	, action_mask (_hoops_HACIR.action_mask)
	, _hoops_GGCHP (_hoops_HACIR._hoops_GGCHP) {

	POOL_ALLOC_ARRAY (_hoops_RGCHP, _hoops_GRPCR+1, _hoops_CRCP const *, memory_pool);
	_hoops_AIGA (_hoops_HACIR._hoops_RGCHP, _hoops_GRPCR+1, _hoops_CRCP const *, _hoops_RGCHP);
	POOL_ALLOC_ARRAY (_hoops_AIACR, _hoops_GRPCR+1, void const *, memory_pool);
	_hoops_AIGA (_hoops_HACIR._hoops_AIACR, _hoops_GRPCR+1, void const *, _hoops_AIACR);
}


Internal_Text_Rendition::Internal_Text_Rendition (Internal_Text_Rendition const & _hoops_HACIR)
	: _hoops_CPASP (_hoops_HACIR)
	, font (_hoops_HACIR.font)
	, _hoops_CHA (_hoops_HACIR._hoops_CHA)
	, _hoops_RGIHP (_hoops_HACIR._hoops_RGIHP)
	, _hoops_HSRIP (_hoops_HACIR._hoops_HSRIP)
	, color (_hoops_HACIR.color)
	, contrast_color (_hoops_HACIR.contrast_color)
	, _hoops_SCHHP (_hoops_HACIR._hoops_SCHHP)
	, _hoops_GRIHP (_hoops_HACIR._hoops_GRIHP)
	, _hoops_PRRIP (_hoops_HACIR._hoops_PRRIP)
	, _hoops_HRRIP (_hoops_HACIR._hoops_HRRIP)
	, spacing (_hoops_HACIR.spacing)
	, path (_hoops_HACIR.path)
	, fallback_index (_hoops_HACIR.fallback_index)
	, _hoops_PRPSP (_hoops_HACIR._hoops_PRPSP)
	, _hoops_PHP (_hoops_HACIR._hoops_PHP)
	, _hoops_ACPAP (_hoops_HACIR._hoops_ACPAP)
	, _hoops_PCPAP (_hoops_HACIR._hoops_PCPAP)
	, _hoops_HCPAP (_hoops_HACIR._hoops_HCPAP)
	, rotation (_hoops_HACIR.rotation)
	, width_scale (_hoops_HACIR.width_scale)
	, _hoops_ICPAP (_hoops_HACIR._hoops_ICPAP)
	, _hoops_IPGRP (_hoops_HACIR._hoops_IPGRP)
	, _hoops_CCPAP (_hoops_HACIR._hoops_CCPAP)
	, _hoops_SCPAP (_hoops_HACIR._hoops_SCPAP)
	, _hoops_CRRIP (_hoops_HACIR._hoops_CRRIP)
	, _hoops_HCRIP (_hoops_HACIR._hoops_HCRIP)
	, _hoops_ICRIP (_hoops_HACIR._hoops_ICRIP)
	, outline (_hoops_HACIR.outline)
	, _hoops_SCRIP (_hoops_HACIR._hoops_SCRIP)
	, _hoops_GSRIP (_hoops_HACIR._hoops_GSRIP)
	, _hoops_CCRIP (_hoops_HACIR._hoops_CCRIP)
	, _hoops_RSRIP (_hoops_HACIR._hoops_RSRIP)
	, _hoops_ASRIP (_hoops_HACIR._hoops_ASRIP)
	, _hoops_PSRIP (_hoops_HACIR._hoops_PSRIP)
	, _hoops_CRPSP (_hoops_HACIR._hoops_CRPSP)
	, _hoops_GRCSR (_hoops_HACIR._hoops_GRCSR)
	, transform (_hoops_HACIR.transform)
	, _hoops_SGHAP (_hoops_HACIR._hoops_SGHAP)
	, _hoops_GHGRP (_hoops_HACIR._hoops_GHGRP)
	, _hoops_SSPAP (_hoops_HACIR._hoops_SSPAP)
	, _hoops_GGHAP (_hoops_HACIR._hoops_GGHAP)
	, _hoops_RGHAP (_hoops_HACIR._hoops_RGHAP)
	, _hoops_AGHAP (_hoops_HACIR._hoops_AGHAP)
	, _hoops_PGHAP (_hoops_HACIR._hoops_PGHAP) {

	_hoops_ISPAP[0] = _hoops_HACIR._hoops_ISPAP[0];
	_hoops_ISPAP[1] = _hoops_HACIR._hoops_ISPAP[1];
	_hoops_CSPAP[0] = _hoops_HACIR._hoops_CSPAP[0];
	_hoops_CSPAP[1] = _hoops_HACIR._hoops_CSPAP[1];

	_hoops_PRRH (_hoops_HSRIP);
}


Internal_Texture_Rendition::Internal_Texture_Rendition (Internal_Texture_Rendition const & _hoops_HACIR)
	: _hoops_CPASP (_hoops_HACIR)
	, count (_hoops_HACIR.count) {

	_hoops_CHRSH(_hoops_HACIR.textures, count, _hoops_RCR *, textures, memory_pool);
	_hoops_CHRSH(_hoops_HACIR.keys, count, Integer32, keys, memory_pool);
}

Internal_Transform_Rendition::Internal_Transform_Rendition (Internal_Transform_Rendition const & _hoops_HACIR)
	: _hoops_CPASP (_hoops_HACIR)
	, _hoops_SPH (_hoops_HACIR._hoops_SPH)
	, matrix (_hoops_HACIR.matrix)
	, _hoops_IPH (_hoops_HACIR._hoops_IPH)
	, _hoops_CGCC (_hoops_HACIR._hoops_CGCC)
	, _hoops_GGPSP (_hoops_HACIR._hoops_GGPSP)
	, object_to_projection_matrix (_hoops_HACIR.object_to_projection_matrix)
	, _hoops_RGH (_hoops_HACIR._hoops_RGH)
	, _hoops_HCHH (_hoops_HACIR._hoops_HCHH)
	, _hoops_HGSC (_hoops_HACIR._hoops_HGSC)
	, flags (_hoops_HACIR.flags)
	, _hoops_AGAA (_hoops_HACIR._hoops_AGAA)
	, _hoops_RGPSP (_hoops_HACIR._hoops_RGPSP)
	, _hoops_CHCR (_hoops_HACIR._hoops_CHCR)
	, _hoops_RIPHP (_hoops_HACIR._hoops_RIPHP)
	, _hoops_PCHH (_hoops_HACIR._hoops_PCHH)
	, _hoops_HCIH (_hoops_HACIR._hoops_HCIH)
	, _hoops_CHIH (_hoops_HACIR._hoops_CHIH)
	, _hoops_RASHP (_hoops_HACIR._hoops_RASHP)
	, _hoops_IGAAP (_hoops_HACIR._hoops_IGAAP)
	, _hoops_CASHP (_hoops_HACIR._hoops_CASHP)
	, _hoops_SHIH (_hoops_HACIR._hoops_SHIH)
	, _hoops_SASHP (_hoops_HACIR._hoops_SASHP)
	, _hoops_HIPHP (_hoops_HACIR._hoops_HIPHP)
	, _hoops_IIPHP (_hoops_HACIR._hoops_IIPHP)
	, heuristics (_hoops_HACIR.heuristics)
	, _hoops_APH (_hoops_HACIR._hoops_APH)
	, _hoops_RHPHP (_hoops_HACIR._hoops_RHPHP)
	, _hoops_PGGIP (_hoops_HACIR._hoops_PGGIP)
	, _hoops_ACSRP (_hoops_HACIR._hoops_ACSRP)
	, _hoops_PCSRP (_hoops_HACIR._hoops_PCSRP)
	, _hoops_SSPPP (_hoops_HACIR._hoops_SSPPP) {
	_hoops_GSCH[0] = _hoops_HACIR._hoops_GSCH[0];
	_hoops_GSCH[1] = _hoops_HACIR._hoops_GSCH[1];

	if (_hoops_SPH != null)
		_hoops_PRRH (_hoops_SPH);
}

Internal_User_Rendition::Internal_User_Rendition (Internal_User_Rendition const & _hoops_HACIR)
	: _hoops_CPASP (_hoops_HACIR),
	_hoops_IGGSA(0){

	if(_hoops_HACIR._hoops_IGGSA) {
		_hoops_HPPIR const * _hoops_IPPIR;
		_hoops_CGGSA::UniqueCursor *	uc = _hoops_HACIR._hoops_IGGSA->GetUniqueCursor();
		while((_hoops_IPPIR = uc->Peek()) != null) {
			ASSERT(_hoops_IPPIR->_hoops_IGGSA == null);
			_hoops_PRRH(_hoops_IPPIR);
			uc->Advance();
		}
		delete uc;
		_hoops_IGGSA = POOL_NEW(memory_pool, _hoops_CGGSA)(_hoops_HACIR._hoops_IGGSA);
	}
}


Internal_Window_Rendition::Internal_Window_Rendition (Internal_Window_Rendition const & _hoops_HACIR)
	: _hoops_CPASP (_hoops_HACIR)
	, _hoops_ASSIR (_hoops_HACIR._hoops_ASSIR)
	, _hoops_SICSR (_hoops_HACIR._hoops_SICSR)
	, _hoops_PGPH (_hoops_HACIR._hoops_PGPH)
	, _hoops_CGAIP (_hoops_HACIR._hoops_CGAIP)
	, _hoops_SGAIP (_hoops_HACIR._hoops_SGAIP)
	, _hoops_CSIH (_hoops_HACIR._hoops_CSIH)
	, _hoops_ASIHP (_hoops_HACIR._hoops_ASIHP)
	, shadow_resolution (_hoops_HACIR.shadow_resolution) {

	_hoops_GPIR = _hoops_HACIR._hoops_GPIR;
	contrast_color = _hoops_HACIR.contrast_color;
	_hoops_GRAIP = _hoops_HACIR._hoops_GRAIP;
	_hoops_CGIHP = _hoops_HACIR._hoops_CGIHP;

	extent = _hoops_HACIR.extent;
	_hoops_HHCAR = _hoops_HACIR._hoops_HHCAR;
	_hoops_PHRA = _hoops_HACIR._hoops_PHRA;
	_hoops_CIIH = _hoops_HACIR._hoops_CIIH;
	_hoops_SCIH = _hoops_HACIR._hoops_SCIH;
	_hoops_GAHIP = _hoops_HACIR._hoops_GAHIP;
	_hoops_RRAIP = _hoops_HACIR._hoops_RRAIP;

	if (_hoops_SICSR != null)
		_hoops_PRRH (_hoops_SICSR);
	if (_hoops_PGPH != null)
		_hoops_CAHS (_hoops_PGPH);
}




_hoops_CPASP::_hoops_CPASP (Display_Context const * dc)
	: _hoops_RGCGP (dc->memory_pool)
	, _hoops_SRA (dc)
	, _hoops_CPA (dc->_hoops_GCHHP()) {}
_hoops_CPASP::_hoops_CPASP (_hoops_CPASP const & x)
	: _hoops_RGCGP (x.memory_pool)
	, _hoops_SRA (x._hoops_SRA)
	, _hoops_CPA (x._hoops_SRA->_hoops_GCHHP()) {}

Internal_Action_Table::Internal_Action_Table (Memory_Pool *p)
	: _hoops_RGCGP(p) {}

Internal_Action_Rendition::Internal_Action_Rendition (Display_Context const * dc)
	: _hoops_CPASP (dc) {
	POOL_ZALLOC_ARRAY (_hoops_RGCHP, _hoops_GRPCR+1, _hoops_CRCP const *, memory_pool);
	POOL_ZALLOC_ARRAY (_hoops_AIACR, _hoops_GRPCR+1, void const *, memory_pool);
}

Internal_Color_Map_Rendition::Internal_Color_Map_Rendition (Display_Context const * dc)
	: _hoops_CPASP (dc) {}

Internal_Cutting_Plane_Rendition::Internal_Cutting_Plane_Rendition (Display_Context const * dc)
	: _hoops_CPASP (dc) {}

_hoops_HHASP::_hoops_HHASP (Display_Context const * dc)
	: _hoops_CPASP (dc) {}

Internal_Glyph_Rendition::Internal_Glyph_Rendition (Display_Context const * dc)
	: _hoops_CPASP (dc) {}

_hoops_HIASP::_hoops_HIASP (Display_Context const * dc)
	: _hoops_CPASP (dc) {}

Internal_Misc_Rendition::Internal_Misc_Rendition (Display_Context const * dc)
	: _hoops_CPASP (dc) {}

Internal_Line_Style_Rendition::Internal_Line_Style_Rendition (Display_Context const * dc)
	: _hoops_CPASP (dc) {}

Internal_Texture_Rendition::Internal_Texture_Rendition (Display_Context const * dc)
	: _hoops_CPASP (dc) {}

Internal_User_Rendition::Internal_User_Rendition (Display_Context const * dc)
	: _hoops_CPASP (dc) {}

Internal_Visualization_Rendition::Internal_Visualization_Rendition (Display_Context const * dc)
	: _hoops_CPASP (dc) {}


Internal_Light_Rendition::Internal_Light_Rendition(Display_Context const * dc)
	: _hoops_CPASP (dc)
	, scale (1.0f) {}

Internal_Material_Rendition::Internal_Material_Rendition(Display_Context const * dc)
	: _hoops_CPASP (dc)
	, _hoops_IRIR (1.0f) {}

Internal_Display_Rendition::Internal_Display_Rendition (Display_Context const * dc)
	: _hoops_CPASP (dc)
	, _hoops_PSIR (_hoops_CAHHP::Create(dc)) {}

Internal_Face_Rendition::Internal_Face_Rendition (Display_Context const * dc)
	: _hoops_CPASP (dc)
	, _hoops_CHA (_hoops_HHA::Create(dc))
	, _hoops_GIA (_hoops_CHA) {}

Internal_Line_Rendition::Internal_Line_Rendition (Display_Context const * dc)
	: _hoops_CPASP (dc)
	, _hoops_CHA (_hoops_HHA::Create(dc)) {}

Internal_Geometry_Rendition::Internal_Geometry_Rendition (Display_Context const * dc)
	: _hoops_CPASP (dc) {
	image._hoops_RSCC.red = 1.0f;
	image._hoops_RSCC.green = 1.0f;
	image._hoops_RSCC.blue = 1.0f;
	image._hoops_HRA.red = 1.0f;
	image._hoops_HRA.green = 1.0f;
	image._hoops_HRA.blue = 1.0f;
}

Internal_Marker_Rendition::Internal_Marker_Rendition (Display_Context const * dc)
	: _hoops_CPASP (dc)
	, _hoops_CHA (_hoops_HHA::Create(dc))
	, _hoops_CSRS (1.0f) {
}

Internal_Text_Rendition::Internal_Text_Rendition (Display_Context const * dc)
	: _hoops_CPASP (dc)
	, _hoops_CHA (_hoops_HHA::Create(dc)) {
	_hoops_AGPIR alter *			_hoops_ICCRS;

	POOL_ZALLOC (_hoops_ICCRS, _hoops_AGPIR, memory_pool);
	_hoops_ICCRS->type = HK_TEXT_FONT;
	_hoops_ICCRS->_hoops_HIHI = 1;

	_hoops_HSRIP = _hoops_ICCRS;
}



_hoops_CCASP::_hoops_CCASP (Display_Context const * dc)
	: _hoops_CPASP (dc) {
	HI_Ident_Matrix (&data);
	data._hoops_CPH = 1.0f;
}


Internal_Transform_Rendition::Internal_Transform_Rendition (Display_Context const * dc)
	: _hoops_CPASP (dc)
	, matrix (_hoops_SGCC::Create(dc))
	, _hoops_IPH (matrix)
	, _hoops_CGCC (matrix)
	, object_to_projection_matrix (matrix)
	// _hoops_CCCRS _hoops_HRGR _hoops_RAAP _hoops_IRAP
	, _hoops_HGSC (_hoops_PCPHP)
	, _hoops_AGAA (-1, 1, -1, 1)
	, _hoops_RGPSP (-1, 1, -1, 1)
	, _hoops_HCIH (-1, 1, -1, 1) {
	_hoops_PCHH = dc->_hoops_PGCC._hoops_PASHP;

	_hoops_GSCH[0] = 0.0f;
	_hoops_GSCH[1] = 1.0f;
}

Internal_Window_Rendition::Internal_Window_Rendition (Display_Context const * dc)
	: _hoops_CPASP (dc)
	, extent (-1.0f, 1.0f, -1.0f, 1.0f)
	, _hoops_HHCAR (-1.0f, 1.0f, -1.0f, 1.0f)
	, _hoops_PHRA (-1, 1, -1, 1)
	, _hoops_CIIH (-1, 1, -1, 1)
	, _hoops_SCIH (-1, 1, -1, 1)
	, _hoops_GAHIP (-1, 1, -1, 1)
	, _hoops_RRAIP (0, 0, 0, 0)
	, _hoops_CSIH (1.0f) {}





Internal_Net_Rendition::Internal_Net_Rendition (Display_Context const * dc)
	: _hoops_CPASP (dc)
	, _hoops_RGPGR (~0)
	, _hoops_RSGC (_hoops_PSIHP::Create(dc))
	, _hoops_ASIR (_hoops_ISHHP::Create(dc))
	, _hoops_ARA (_hoops_GRA::Create(dc))
	, glyph_rendition (_hoops_GHRIP::Create (dc))
	, _hoops_PIGIP (_hoops_RIGIP::Create (dc))
	, _hoops_GCSHP (_hoops_PHRIP::Create (dc))
	, _hoops_IRR (_hoops_GRGH::Create(dc))
	, _hoops_GCCSR (_hoops_IPRIP::Create (dc))
	, transform_rendition (_hoops_HHCR::Create(dc))
	, _hoops_GCGIP (_hoops_CIGIP::Create(dc))
	, _hoops_CPP (_hoops_GCIR::Create(dc))

	, _hoops_RHP (Line_Rendition::Create(dc))
	, _hoops_IHA (_hoops_CIGA::Create(dc))
	, _hoops_AHP (_hoops_RHP)
	, _hoops_GSP (_hoops_ICP::Create(dc))
	, _hoops_SISI (_hoops_IGCSR::Create(dc))
	, _hoops_SCP (_hoops_GSP)
	, _hoops_SAIR (_hoops_CGRA::Create(dc))

	, _hoops_CAIHP (_hoops_RHP)
	, _hoops_HAIHP (_hoops_IHA)
	, _hoops_AAIHP (_hoops_IHA) {
}





GLOBAL_FUNCTION void HD_Free_Cutting_Plane_Sets (
	_hoops_IAPA const			*_hoops_HRCAR) {
	_hoops_IAPA const			*_hoops_SCCRS;

	if (_hoops_HRCAR != null) do {
		_hoops_GPPA const		*_hoops_IRCAR;
		_hoops_GPPA const		*_hoops_GSCRS;
		_hoops_SCCRS = _hoops_HRCAR->next;

		if ((_hoops_IRCAR = _hoops_HRCAR->_hoops_APPA) != null) do {
			_hoops_GSCRS = _hoops_IRCAR->next;
			FREE (_hoops_IRCAR, _hoops_GPPA);
		} _hoops_RGGA ((_hoops_IRCAR = _hoops_GSCRS) == null);

		FREE (_hoops_HRCAR, _hoops_IAPA);
	} while ((_hoops_HRCAR = _hoops_SCCRS) != null);
}







Internal_Color_Map_Rendition::~Internal_Color_Map_Rendition () {
	if (_hoops_AHHHP != null && length > 0)
		FREE_ARRAY (_hoops_AHHHP, length, Driver_Color);
	if (_hoops_ACIHP != null && _hoops_HSIR > 0)
		FREE_ARRAY (_hoops_ACIHP, _hoops_HSIR, Driver_Color);
}

Internal_Cutting_Plane_Rendition::~Internal_Cutting_Plane_Rendition () {
	HD_Free_Cutting_Plane_Sets (_hoops_ISIGA);
	HD_Free_Cutting_Plane_Sets (_hoops_PHCA);
	HD_Free_Cutting_Plane_Sets (_hoops_IRH);
}

_hoops_HHASP::~_hoops_HHASP () {
	HD_Free_Convex_Clip_Region (_hoops_PSHH);
	HD_Free_Convex_Clip_Region (_hoops_AHGGA);
}

Internal_Display_Rendition::~Internal_Display_Rendition () {
	if (window.texture != null)
		_hoops_HPRH (window.texture);

	if (window._hoops_PGPH != null) {
		_hoops_SIHHP const		*up = window._hoops_PGPH;

		if (_hoops_ISAI (up) == 0) {
			if (up->pattern != null)
				FREE_ARRAY (up->pattern, up->width * up->height, unsigned char);
			FREE (up, _hoops_SIHHP);
		}
	}

	if (conditions._hoops_CPGIP != null) {
		_hoops_SPPIR const * _hoops_GHPIR;
		while((_hoops_GHPIR = conditions._hoops_CPGIP->RemoveFirst()) != null)
			_hoops_HPRH(_hoops_GHPIR);
		delete conditions._hoops_CPGIP;
	}

	if (conditions._hoops_RCHA != null) {
#if 0
		for (int i=0; i<conditions.count; i++) {
			unsigned int	_hoops_RCHA = conditions._hoops_RCHA[i];
			int				index = i * 32;

			while (_hoops_RCHA != 0) {
				if ((_hoops_RCHA & 1) != 0) {
					_hoops_HPRH (HOOPS_WORLD->_hoops_PCIIR[index]);
				}
				_hoops_RCHA >>= 1;
				++index;
			}
		}
#endif
		FREE_ARRAY (conditions._hoops_RCHA, conditions.count, unsigned int);
	}

	if (conditions._hoops_ACPGR != null)
		HI_Free_Conditional_Actions(conditions._hoops_ACPGR); 
}

Internal_Face_Rendition::~Internal_Face_Rendition () {
	if (_hoops_PGPH != null) {
		_hoops_SIHHP const		*up = _hoops_PGPH;

		if (_hoops_ISAI (up) == 0) {
			if (up->pattern != null)
				FREE_ARRAY (up->pattern, up->width * up->height, unsigned char);

			FREE (up, _hoops_SIHHP);
		}
	}
}

Internal_Geometry_Rendition::~Internal_Geometry_Rendition () {
	if (_hoops_ACP._hoops_CIAIR != 0)
		FREE_ARRAY (_hoops_ACP._hoops_SIAIR, _hoops_ACP._hoops_CIAIR, float);

	if (_hoops_ACP._hoops_GCAIR != 0)
		FREE_ARRAY (_hoops_ACP.colors, _hoops_ACP._hoops_GCAIR, RGB);

	if (_hoops_ACP._hoops_RCAIR != 0) {
		for (int i=0; i<_hoops_ACP._hoops_RCAIR; i++)
			_hoops_RGAIR (_hoops_ACP._hoops_ACAIR[i]);
		FREE_ARRAY (_hoops_ACP._hoops_ACAIR, _hoops_ACP._hoops_RCAIR, _hoops_HCRPR);

		FREE_ARRAY (_hoops_ACP._hoops_PCAIR, _hoops_ACP._hoops_RCAIR, Integer32);
	}

	if (_hoops_ACP.weight_count != 0)
		FREE_ARRAY (_hoops_ACP.weights, _hoops_ACP.weight_count, _hoops_HCAIR);
}

Internal_Glyph_Rendition::~Internal_Glyph_Rendition () {
	if (count) {
		for (int i=0; i<count; i++)
			glyphs[i] = null;
		FREE_ARRAY (glyphs, count, _hoops_GASC);

		if (keys)	// _hoops_PAHA'_hoops_RA _hoops_RRP _hoops_RPGP?
			FREE_ARRAY (keys, count, Integer32);
	}
}

_hoops_HIASP::~_hoops_HIASP () {
	if (count) {
		for (int i=0; i<count; i++)
			_hoops_SAAIR[i] = null;
		FREE_ARRAY (_hoops_SAAIR, count, _hoops_GPAIR);

		if (keys)	// _hoops_PAHA'_hoops_RA _hoops_RRP _hoops_RPGP?
			FREE_ARRAY (keys, count, Integer32);
	}
}

Internal_Light_Rendition::~Internal_Light_Rendition () {
	while (_hoops_CGR != null) {
		_hoops_AS alter *victim = _hoops_CGR;

		_hoops_CGR = victim->next;

		if (victim->count != 0)
			FREE_ARRAY (victim->points, victim->count, Point);
		FREE (victim, _hoops_AS);
	}
}

Internal_Line_Style_Rendition::~Internal_Line_Style_Rendition () {
	if (count) {
		for (int i=0; i<count; ++i)
			_hoops_HPAIR[i] = null;

		FREE_ARRAY (_hoops_HPAIR, count, Line_Style);
		FREE_ARRAY (keys, count, Integer32);
	}
}

Internal_Material_Rendition::~Internal_Material_Rendition () {

	HI_Free_Diffuse_Channel_List (_hoops_SCA);
	for (int i=0; i<_hoops_GAGRA; i++)
		if (texture[i] != null)
			_hoops_HPRH(texture[i]);
}


Internal_Action_Rendition::~Internal_Action_Rendition () {
	FREE_ARRAY (_hoops_RGCHP, _hoops_GRPCR+1, _hoops_CRCP const *);
	FREE_ARRAY (_hoops_AIACR, _hoops_GRPCR+1, void const *);
}


Internal_Net_Rendition::~Internal_Net_Rendition() {
}

Internal_Text_Rendition::~Internal_Text_Rendition () {
	ASSERT(_hoops_HSRIP != null);
	_hoops_HPRH (_hoops_HSRIP);
}


Internal_Texture_Rendition::~Internal_Texture_Rendition () {
	if (count) {
		FREE_ARRAY (textures, count, _hoops_RCR *);
		FREE_ARRAY (keys, count, Integer32);
	}
}

Internal_Transform_Rendition::~Internal_Transform_Rendition () {
	if (_hoops_SPH != null)
		_hoops_HPRH (_hoops_SPH);
}

Internal_User_Rendition::~Internal_User_Rendition () {

	if (_hoops_IGGSA != null) {
		_hoops_HPPIR const * _hoops_IPPIR;
		while((_hoops_IPPIR = _hoops_IGGSA->RemoveFirst()) != null)
			_hoops_HPRH(_hoops_IPPIR);
		delete _hoops_IGGSA;
	}
}

Internal_Window_Rendition::~Internal_Window_Rendition () {
	if (_hoops_SICSR != null)
		_hoops_HPRH (_hoops_SICSR);

	if (_hoops_PGPH != null) {
		_hoops_SIHHP const		*up = _hoops_PGPH;

		if (_hoops_ISAI (up) == 0) {
			if (up->pattern != null)
				FREE_ARRAY (up->pattern, up->width * up->height, unsigned char);

			FREE (up, _hoops_SIHHP);
		}
	}
}



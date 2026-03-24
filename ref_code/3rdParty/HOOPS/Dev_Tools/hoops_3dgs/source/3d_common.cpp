/*
 * Copyright (c) 2009 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.  Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.989.2.1 2011-01-27 00:32:27 heppe Exp $
 */


#include "3d_common.h"

#include <stdio.h>
#include <stdlib.h>
#include "3d_common_tristrip.cpp"
#include "3d_common_post.cpp"

static const char *_hoops_G = "shader_dump";

#undef CONST

// _hoops_R _hoops_A
static int const _hoops_P[] = { _hoops_H, _hoops_I, _hoops_C, _hoops_S };

/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_RR _hoops_AR
*****************************************************************************
*****************************************************************************/
bool H3DData::_hoops_PR ()
{
	// _hoops_HR _hoops_IR, _hoops_CR _hoops_SR _hoops_GA'_hoops_RA _hoops_AA _hoops_PA _hoops_HA.
	bool _hoops_IA = true;

	ALLOC_ARRAY(_hoops_CA, _hoops_SA, char);
	ALLOC_ARRAY(_hoops_GP, _hoops_SA, char);

#ifdef H3D_SHADER_DEBUG
	_hoops_RP = true;
#else
	_hoops_RP = false;
#endif

	// _hoops_AP
	return _hoops_IA;
}


void H3DData::_hoops_PP()
{
	_hoops_HP (_hoops_IP);

	_hoops_CP._hoops_PP();

	// _hoops_SP _hoops_GH _hoops_RH _hoops_AH _hoops_PH _hoops_HH _hoops_IH _hoops_CH
	_hoops_HP(_hoops_SH._hoops_GI);

	// _hoops_SP _hoops_GH _hoops_RI _hoops_AI
	_hoops_HP(_hoops_PI._hoops_HI);
	_hoops_HP(_hoops_II._hoops_HI);

	// _hoops_SP _hoops_GH _hoops_AH _hoops_CI _hoops_SI _hoops_GC
	if (_hoops_CA)
		FREE_ARRAY(_hoops_CA, _hoops_SA, char);
	if (_hoops_GP)
		FREE_ARRAY(_hoops_GP, _hoops_SA, char);
}

/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_RC _hoops_AR
*****************************************************************************
*****************************************************************************/
void H3DShaderID::_hoops_AC (
	Net_Rendition const &		nr,
	_hoops_PC const &		_hoops_HC) {
	int 						_hoops_IC = 0;
	int 						_hoops_CC = 0;
	int 						_hoops_SC = 0;
	int 						_hoops_GS = 0;
	int 						_hoops_RS = 0;
	_hoops_AS const *		light;

	if (!_hoops_HC)
		return;

	// _hoops_PS _hoops_HS _hoops_IS _hoops_CS _hoops_SS _hoops_IS _hoops_RH _hoops_CI _hoops_GGR _hoops_RGR _hoops_AGR
	int _hoops_PGR = 0;
	for (unsigned int i = 0; i < _hoops_HGR(_hoops_P); ++i) {
		// _hoops_IGR
		light = _hoops_HC->_hoops_CGR;
		while (light && _hoops_PGR < 4) {
			// _hoops_SGR _hoops_GRR _hoops_RRR _hoops_ARR
			if (light->_hoops_PRR == _hoops_P[i]) {
				bool _hoops_HRR = false;
				if (light->_hoops_HRR &&
					light->_hoops_HRR->valid &&
					BIT (nr->_hoops_IRR->_hoops_CRR, T_SHADOW_RECEIVING)) {
					// _hoops_SRR _hoops_GAR _hoops_RAR _hoops_AAR (_hoops_PAR _hoops_HAR) _hoops_IAR.
					_hoops_CAR(_hoops_PGR, light->_hoops_HRR->_hoops_SAR);

					// _hoops_GPR/_hoops_RPR _hoops_APR
					_hoops_HRR = true;
					++_hoops_PGR;
				}

				// _hoops_SGR _hoops_SS _hoops_PPR _hoops_HPR
				switch (light->_hoops_PRR) {
					case _hoops_I:
						_hoops_IC++;
						_hoops_RS += _hoops_HRR;
						break;
					case _hoops_C:
						_hoops_CC++;
						break;
					case _hoops_H:
						_hoops_SC++;
						_hoops_GS += _hoops_HRR;
						break;
					default:
						_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
										   "unrecognized light type.");
				}
			}

			// _hoops_CPR _hoops_SPR
			light = light->next;
		}
	}
	_hoops_GHR (_hoops_IC);
	_hoops_RHR (_hoops_CC);
	_hoops_AHR (_hoops_SC);
	if (!_hoops_IC && !_hoops_CC && !_hoops_SC)
		m_data[3] &= ~H3DID_PER_PIXEL_LIGHTING;

	if (_hoops_PGR) {
		_hoops_PHR (_hoops_RS);
		_hoops_HHR (_hoops_GS);

		// _hoops_IHR _hoops_CHR _hoops_SHR _hoops_GIR _hoops_RIR-_hoops_AIR
		m_data[3] |= H3DID_PER_PIXEL_LIGHTING;
	}
}


void H3DShaderID::_hoops_PIR (
		Net_Rendition const & nr,
		_hoops_HIR const *txr, 
		int *_hoops_IIR,
		bool _hoops_CIR)
{
	int _hoops_SIR = *_hoops_IIR;
	int _hoops_GCR;
	_hoops_RCR *_hoops_ACR = txr->texture;			// _hoops_PCR _hoops_HCR _hoops_AI _hoops_IS _hoops_RGR _hoops_SPR
	m_data[5] |= H3DID_SHARED_DIFFUSE_COORDS;

	if (txr->texture->_hoops_ICR[2] > 1)
		m_data[5] |= H3DID_TEXTURE3D;
	if (!_hoops_CCR() &&
		BIT (txr->texture->_hoops_SCR, _hoops_GSR)) {
		m_data[6] |= txr->texture->_hoops_RSR->id;
		m_data[3] |= H3DID_PER_PIXEL_LIGHTING;
		if (BIT (txr->texture->flags, _hoops_ASR))
			m_data[5] |= H3DID_DEFINED_MATERIAL_MULTITEXTURE;
		switch (txr->texture->_hoops_PSR) {
			case HK_PS_REFLECTION_VECTOR:
			case _hoops_HSR:
				m_data[5] |= H3DID_DEFINED_MATERIAL_PS_PHYSICAL_REFLECTION;
				break;
			case HK_PS_WORLD:
				m_data[5] |= H3DID_DEFINED_MATERIAL_PS_WORLD;
				break;
			case HK_PS_OBJECT:
				m_data[5] |= H3DID_DEFINED_MATERIAL_PS_OBJECT;
				break;
			case HK_PS_SURFACE_NORMAL:
				m_data[5] |= H3DID_DEFINED_MATERIAL_PS_SURFACE_NORMAL;
				break;
			case HK_PS_LOCAL_PIXELS:
				m_data[5] |= H3DID_DEFINED_MATERIAL_PS_LOCAL_PIXELS;
				break;
			case HK_PS_OUTER_PIXELS:
				m_data[5] |= H3DID_DEFINED_MATERIAL_PS_OUTER_PIXELS;
				break;
			case HK_PS_LOCAL_WINDOW:
				m_data[5] |= H3DID_DEFINED_MATERIAL_PS_LOCAL_WINDOW;
				break;
			case HK_PS_OUTER_WINDOW:
				m_data[5] |= H3DID_DEFINED_MATERIAL_PS_OUTER_WINDOW;
				break;
			case HK_PS_U:
			case HK_PS_UV:
			case HK_PS_UVW:
			case HK_PS_NATURAL_UV:
			case HK_PS_SPHERE:
			case HK_PS_CYLINDER:
				m_data[5] |= H3DID_DEFINED_MATERIAL_PS_UVW;
				break;
		}
	}

	do {
		if (!_hoops_ISR(nr, txr->texture, _hoops_ACR))
			m_data[5] &= ~H3DID_SHARED_DIFFUSE_COORDS;		

		int _hoops_CSR = 0, _hoops_SSR = 0, _hoops_GGA = 0, _hoops_RGA = 0, _hoops_AGA = 0;
		switch (_hoops_SIR) {
			case 0:
				_hoops_CSR		= H3DID_TEX0_WORLD;
				_hoops_SSR		= H3DID_TEX0_DECAL;
				_hoops_GGA	= H3DID_TEX0_COLOR;
				_hoops_RGA	= H3DID_TEX0_MODULATE;
				_hoops_AGA		= H3DID_TEX0_DROP;
				break;
			case 1:
				_hoops_CSR		= H3DID_TEX1_WORLD;
				_hoops_GGA	= H3DID_TEX1_COLOR;
				_hoops_RGA	= H3DID_TEX1_MODULATE;
				_hoops_AGA		= H3DID_TEX1_DROP;
				break;
			case 2:
				_hoops_CSR		= H3DID_TEX2_WORLD;
				_hoops_GGA	= H3DID_TEX2_COLOR;
				_hoops_RGA	= H3DID_TEX2_MODULATE;
				_hoops_AGA		= H3DID_TEX2_DROP;
				break;
			case 3:
				_hoops_CSR		= H3DID_TEX3_WORLD;
				_hoops_GGA	= H3DID_TEX3_COLOR;
				_hoops_RGA	= H3DID_TEX3_MODULATE;
				_hoops_AGA		= H3DID_TEX3_DROP;
				break;
			case 4:
				_hoops_CSR		= H3DID_TEX4_WORLD;
				_hoops_GGA	= H3DID_TEX4_COLOR;
				_hoops_RGA	= H3DID_TEX4_MODULATE;
				_hoops_AGA		= H3DID_TEX4_DROP;
				break;
			case 5:
				_hoops_CSR		= H3DID_TEX5_WORLD;
				_hoops_GGA	= H3DID_TEX5_COLOR;
				_hoops_RGA	= H3DID_TEX5_MODULATE;
				_hoops_AGA		= H3DID_TEX5_DROP;
				break;
			case 6:
				_hoops_CSR		= H3DID_TEX6_WORLD;
				_hoops_GGA	= H3DID_TEX6_COLOR;
				_hoops_RGA	= H3DID_TEX6_MODULATE;
				_hoops_AGA		= H3DID_TEX6_DROP;
				break;
			case 7:
				_hoops_CSR		= H3DID_TEX7_WORLD;
				_hoops_GGA	= H3DID_TEX7_COLOR;
				_hoops_RGA	= H3DID_TEX7_MODULATE;
				_hoops_AGA		= H3DID_TEX7_DROP;
				break;
		}

		if (_hoops_CIR) 
			_hoops_GCR = 4;
		else
			_hoops_GCR = 2;
		if (txr->texture->_hoops_PSR == HK_PS_WORLD)
			m_data[_hoops_GCR] |= _hoops_CSR;
		if (BIT (txr->texture->_hoops_SCR, _hoops_PGA) || txr->_hoops_HGA > 0)
			m_data[_hoops_GCR] |= _hoops_SSR;
		if (BIT (txr->texture->_hoops_SCR, _hoops_IGA))
			m_data[_hoops_GCR] |= _hoops_RGA;
		if (txr->texture->_hoops_CGA == _hoops_SGA) {
			if (_hoops_CIR)
				_hoops_AGA <<= 8;
			m_data[5] |= _hoops_AGA;
		}

		_hoops_GRA const &	_hoops_RRA = nr->_hoops_ARA;

		if (BIT (txr->flags, _hoops_PRA) ||
			_hoops_RRA->image._hoops_HRA.red != 1.0 ||
			_hoops_RRA->image._hoops_HRA.green != 1.0 ||
			_hoops_RRA->image._hoops_HRA.blue != 1.0)
			m_data[_hoops_GCR] |= _hoops_GGA;

		_hoops_SIR++;
	} while ((txr = txr->next) != null);

	*_hoops_IIR = _hoops_SIR;
}



H3DShaderID *H3DShaderID::_hoops_IRA (
	Net_Rendition const &		nr,
	int							type,
	void const *				thing,
	int							count,
	int 						flags,
	int 						_hoops_CRA) {
	H3DData alter *				h3ddata = H3DD (nr->_hoops_SRA);
	bool						_hoops_GAA = false;
	int							_hoops_RAA = 0;
	int							_hoops_AAA = 0;
	bool						_hoops_PAA = false;

	if (_hoops_CRA) switch(type) {
		case T_FACES:
			if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_IAA], M_DIFFUSE))
				_hoops_CRA &= ~_hoops_CAA;
			break;
		case T_EDGES:
			if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_SAA], M_DIFFUSE))
				_hoops_CRA &= ~_hoops_CAA;
			break;
		case _hoops_GPA:
		case T_LINES:
			if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_RPA], M_DIFFUSE))
				_hoops_CRA &= ~_hoops_CAA;
			break;
		case T_MARKERS:
			if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_APA], M_DIFFUSE))
				_hoops_CRA &= ~_hoops_CAA;
			break;
		case T_VERTICES:
			if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_PPA], M_DIFFUSE))
				_hoops_CRA &= ~_hoops_CAA;
			break;
	}

#if 1
	if (h3ddata->_hoops_HPA._hoops_IPA == nr->_hoops_CPA &&
		h3ddata->_hoops_HPA.flags == flags) {
		if (!_hoops_CRA) {
			switch(type) {
				case T_FACES:
					_hoops_PAA = (nr->_hoops_SRA->_hoops_SPA->color != null &&
									  BIT (nr->_hoops_SRA->_hoops_SPA->color->_hoops_GHA, Color_FRONT) &&
									  !BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_IAA], M_DIFFUSE));
					_hoops_CRA = _hoops_RHA((Tristrip const *) thing, _hoops_PAA);
					break;
				case T_EDGES:
					_hoops_PAA = (nr->_hoops_SRA->_hoops_SPA->color != null &&
									  BIT (nr->_hoops_SRA->_hoops_SPA->color->_hoops_GHA, Color_EDGE) &&
									  !BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_SAA], M_DIFFUSE));
					_hoops_CRA = _hoops_AHA((Polyedge const *) thing, _hoops_PAA);
					break;
				case _hoops_GPA:
				case T_LINES:
					_hoops_PAA = (nr->_hoops_SRA->_hoops_SPA->color != null &&
									  BIT (nr->_hoops_SRA->_hoops_SPA->color->_hoops_GHA, Color_EDGE) &&
									  !BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_RPA], M_DIFFUSE));
					_hoops_CRA = _hoops_AHA((Polyedge const *) thing, _hoops_PAA);
					break;
				case T_VERTICES:
					_hoops_PAA = (nr->_hoops_SRA->_hoops_SPA->color != null &&
									  BIT (nr->_hoops_SRA->_hoops_SPA->color->_hoops_GHA, Color_VERTEX) &&
									  !BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_PPA], M_DIFFUSE));
					_hoops_CRA = _hoops_PHA((Polymarker const *) thing, _hoops_PAA);
					break;
				case T_MARKERS:
					_hoops_PAA = (nr->_hoops_SRA->_hoops_SPA->color != null &&
									  BIT (nr->_hoops_SRA->_hoops_SPA->color->_hoops_GHA, Color_MARKER) &&
									  !BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_APA], M_DIFFUSE));
					_hoops_CRA = _hoops_PHA((Polymarker const *) thing, _hoops_PAA);
					break;
			}
		}
		if (_hoops_CRA == h3ddata->_hoops_HPA._hoops_CRA) {
			return &h3ddata->_hoops_HPA.id;
		}
	}
#endif

	m_data[0] = flags;
	switch (type) {
		case T_FACES: {
			_hoops_HHA const &	matr = nr->_hoops_IHA->_hoops_CHA;
			_hoops_HHA const &	_hoops_SHA = nr->_hoops_IHA->_hoops_GIA;

			if (_hoops_CRA == 0) {
				_hoops_PAA = ((nr->_hoops_SRA->_hoops_SPA->color != null) &&
								  BIT (nr->_hoops_SRA->_hoops_SPA->color->_hoops_GHA, Color_FRONT));
				_hoops_CRA = _hoops_RHA((Tristrip const *) thing, _hoops_PAA);
				if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_IAA], M_DIFFUSE))
					_hoops_CRA &= ~_hoops_CAA;
			}

			m_data[0] |= H3DID_TRIANGLE;

			if (!BIT(flags, H3DID_CREATE_SHADOW_MAP)) {
				if (_hoops_CRA) {
					if (matr->texture[_hoops_RIA]) {
						m_data[3] |= H3DID_ENVIRONMENT_TEXTURE;
						if (matr->texture[_hoops_RIA]->_hoops_PSR == _hoops_HSR)
							m_data[0] |= H3DID_PHYSICAL_REFLECTION;
						if (BIT(matr->texture[_hoops_RIA]->flags,_hoops_AIA))
							m_data[3] |= H3DID_CUBE_ENVIRONMENT_MAP;
					}

					if (BIT(_hoops_CRA, _hoops_PIA)) {
						if (matr->texture[_hoops_HIA]) {
							m_data[2] |= H3DID_SPECULAR_TEXTURE;
						}

						if (matr->texture[_hoops_IIA]) {
							m_data[2] |= H3DID_BUMP_TEXTURE;

							// _hoops_CIA _hoops_SIA _hoops_GCA _hoops_RIR-_hoops_AIR _hoops_RCA
							m_data[3] |= H3DID_PER_PIXEL_LIGHTING;
						}

						if (matr->texture[_hoops_ACA]) {
							m_data[3] |= H3DID_MIRROR_TEXTURE;
						}
						if (matr->texture[_hoops_PCA]) {
							m_data[3] |= H3DID_TRANSMISSION_TEXTURE;
							if (BIT (matr->texture[_hoops_PCA]->_hoops_SCR, _hoops_IGA))
								m_data[3] |= H3DID_TRANSMISSION_TEX_MODULATE;
						}
						if (matr->texture[_hoops_HCA]) {
							m_data[3] |= H3DID_EMISSION_TEXTURE;
							if (BIT (matr->texture[_hoops_HCA]->_hoops_SCR, _hoops_IGA))
								m_data[3] |= H3DID_EMISSION_TEX_MODULATE;
						}
					}
				}

				/* _hoops_ICA _hoops_CCA _hoops_HH _hoops_RPR */
				if (BIT(_hoops_CRA, _hoops_PIA))
				{
					_hoops_HIR *txr = null;

					for (int i = 0; i < 2; i++) {
						if (i == 0) {
							txr = matr->_hoops_SCA;
							if (txr)
								_hoops_PIR (nr, txr, &_hoops_RAA, false);
						}
						else {
							txr = _hoops_SHA->_hoops_SCA;
							if (txr)
								_hoops_PIR (nr, txr, &_hoops_AAA, true);
						}

						if (matr == _hoops_SHA ||
							h3ddata->_hoops_GSA ||
							!ANYBIT(nr->transform_rendition->heuristics, _hoops_RSA))
							break;
					}
				}

				_hoops_ASA (_hoops_RAA);
				_hoops_PSA (_hoops_AAA);

				if (BIT(_hoops_CRA, _hoops_HSA) || BIT(_hoops_CRA, _hoops_ISA)) {
					if (ANYBIT (nr->_hoops_IRR->_hoops_CSA, _hoops_SSA | _hoops_GGP))
						m_data[3] |= H3DID_PER_PIXEL_LIGHTING;
					if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_GGP))
						m_data[3] |= H3DID_GOOCH;
					if (BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES))
						_hoops_AC (nr, nr->_hoops_IHA->_hoops_AGP);
				}
				if (BIT(_hoops_CRA, _hoops_CAA) || BIT(_hoops_CRA, _hoops_PGP))
					m_data[0] |= H3DID_VERTEX_COLORS;
				if (BIT(_hoops_CRA, _hoops_HGP))
					m_data[0] |= H3DID_VERTEX_FINDICES;
				if (BIT(_hoops_CRA, _hoops_IGP))
					m_data[0] |= H3DID_COLOR_INDEX_INTERPOLATED;

			}

			// _hoops_CGP _hoops_SR _hoops_CHR _hoops_SGP _hoops_PAR _hoops_GRP _hoops_HPR, _hoops_SR _hoops_RRP _hoops_IS _hoops_ARP _hoops_PRP _hoops_APR _hoops_HRP.
			if (_hoops_IRP() || _hoops_CRP()) {
				if (!h3ddata->_hoops_SRP && !h3ddata->_hoops_GAP)
					m_data[3] |= H3DID_SHADOW_MAP_RGBA;
			}

			if (_hoops_IRP()) {
				// _hoops_RAP _hoops_AAP
				_hoops_PAP (h3ddata->_hoops_PI._hoops_HAP);
				_hoops_IAP (h3ddata->_hoops_PI._hoops_CAP);

				// _hoops_SAP _hoops_GPP _hoops_RI, _hoops_RPP _hoops_APP _hoops_PPR _hoops_PPP _hoops_HPP _hoops_RH _hoops_IPP.
				if (h3ddata->_hoops_PI._hoops_HI && nr->_hoops_CPP->_hoops_HRR._hoops_HI)
					m_data[2] |= H3DID_SHADOW_MAP_JITTER;
			}
			if (BIT (nr->transform_rendition->flags, _hoops_SPP))
				m_data[3] |= H3DID_PER_PIXEL_LIGHTING;
		} break;
		case _hoops_GPA:
		case T_EDGES:
		case T_LINES: {
			Line_Rendition	_hoops_GHP;
			int weight;

			if (_hoops_CRA == 0) {
				if (type == T_EDGES) {
					_hoops_PAA = (nr->_hoops_SRA->_hoops_SPA->color != null &&
									  BIT (nr->_hoops_SRA->_hoops_SPA->color->_hoops_GHA, Color_EDGE));
					_hoops_CRA = _hoops_AHA((Polyedge const *) thing, _hoops_PAA);
					if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_SAA], M_DIFFUSE))
						_hoops_CRA &= ~_hoops_CAA;
				}
				else if (type == T_LINES) {
					_hoops_PAA = (nr->_hoops_SRA->_hoops_SPA->color != null &&
									  BIT (nr->_hoops_SRA->_hoops_SPA->color->_hoops_GHA, Color_LINE));
					_hoops_CRA = _hoops_AHA((Polyedge const *) thing, _hoops_PAA);
					if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_RPA], M_DIFFUSE))
						_hoops_CRA &= ~_hoops_CAA;
				}
			}

			if (type != T_LINES)
				_hoops_GHP = nr->_hoops_RHP;
			else
				_hoops_GHP = nr->_hoops_AHP;

			_hoops_HHA const &	matr = _hoops_GHP->_hoops_CHA;

			/* _hoops_ICA _hoops_CCA _hoops_HH _hoops_RPR */
			if (BIT(_hoops_CRA, _hoops_PIA)) {
				if (matr->_hoops_SCA) 
					_hoops_PIR (nr, matr->_hoops_SCA, &_hoops_RAA, false);
			}
			_hoops_ASA (_hoops_RAA);

			weight = _hoops_GHP->weight;
			if (weight < 0)
				weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP,1.0f, false, 0, true)+0.5f);

			if (weight > 1) {
				m_data[1] |= H3DID_WIDE_LINE;
				if (h3ddata->_hoops_IHP ||
					BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP) ||
					ANYBIT(_hoops_GHP->style, LJOIN_ROUND|LCAP_ROUND|LCAP_END_ROUND) ||
					type == T_EDGES)
					m_data[1] |= H3DID_ROUND_LINE;

				// _hoops_GA'_hoops_RA _hoops_ARP _hoops_GIP _hoops_RIP _hoops_RPP _hoops_RPR < 0
				if (type == T_LINES && (_hoops_GHP->style & LJOIN_MASK) == LJOIN_MITER && count > 0)
					m_data[1] |= H3DID_MITER;
				thing = null;
			}
			else if (BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)) {
				m_data[1] |= H3DID_WIDE_LINE | H3DID_ANTI_ALIASED_LINE;
				if (h3ddata->glyph.mode)
					m_data[1] &= ~H3DID_ANTI_ALIASED_LINE;
				thing = null;
			}
			else if (h3ddata->_hoops_IHP || h3ddata->_hoops_AIP) {
				m_data[1] |= H3DID_WIDE_LINE;
				thing = null;
			}

			/* _hoops_PIP: _hoops_HIP _hoops_CHR _hoops_IIP _hoops_CIP */
			if (type != T_LINES) {
				if (!_hoops_CRA || BIT(_hoops_CRA, _hoops_HSA) || BIT(_hoops_CRA, _hoops_SIP)) {
					if (!_hoops_CRA || BIT(_hoops_CRA, _hoops_HSA)) {
						if (ANYBIT (nr->_hoops_IRR->_hoops_CSA, _hoops_GCP|_hoops_RCP))
							m_data[3] |= H3DID_PER_PIXEL_LIGHTING;
					}
					if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_RCP))
						m_data[3] |= H3DID_GOOCH;
					if (type == _hoops_GPA) {
						if (nr->_hoops_ARA->_hoops_ACP._hoops_PCP)
							_hoops_AC (nr, _hoops_GHP->_hoops_AGP);
					}
					else {
						if (BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES))
							_hoops_AC (nr, _hoops_GHP->_hoops_AGP);
					}
				}
			}
			if (BIT(_hoops_CRA, _hoops_CAA) || BIT(_hoops_CRA, _hoops_HCP))
				m_data[0] |= H3DID_VERTEX_COLORS;
			if (BIT(_hoops_CRA, _hoops_HGP))
				m_data[0] |= H3DID_VERTEX_FINDICES;

		} break;
		case T_IMAGES: {
			_hoops_ASA (1);
			m_data[2] |= H3DID_TEX0_DECAL;
		} break;
		case T_VERTICES:
		case T_MARKERS: {
			_hoops_ICP	_hoops_CCP;

			m_data[0] |= H3DID_POINT;

			if (type == T_VERTICES)
				_hoops_CCP = nr->_hoops_SCP;
			else
				_hoops_CCP = nr->_hoops_GSP;

			if (_hoops_CRA == 0) {
				if (type == T_VERTICES) {
					_hoops_PAA = ((nr->_hoops_SRA->_hoops_SPA->color != null) &&
									  BIT (nr->_hoops_SRA->_hoops_SPA->color->_hoops_GHA, Color_VERTEX));
					_hoops_CRA = _hoops_PHA((Polymarker const *) thing, _hoops_PAA);
					if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_PPA], M_DIFFUSE))
						_hoops_CRA &= ~_hoops_CAA;
				}
				else {
					ASSERT (type == T_MARKERS);
					_hoops_PAA = ((nr->_hoops_SRA->_hoops_SPA->color != null) &&
									  BIT (nr->_hoops_SRA->_hoops_SPA->color->_hoops_GHA, Color_MARKER));
					_hoops_CRA = _hoops_PHA((Polymarker const *) thing, _hoops_PAA);
					if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_APA], M_DIFFUSE))
						_hoops_CRA &= ~_hoops_CAA;
				}
			}

			if (BIT(_hoops_CRA, _hoops_HSA)) {
				if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_SSA))
					m_data[3] |= H3DID_PER_PIXEL_LIGHTING;
				if (BIT (nr->_hoops_RGP, T_LIGHTS_FOR_MARKERS))
					_hoops_AC (nr, nr->_hoops_IHA->_hoops_AGP);
			}

			_hoops_HHA const &	matr = _hoops_CCP->_hoops_CHA;
			/* _hoops_ICA _hoops_CCA _hoops_HH _hoops_RPR */
			if (matr->_hoops_SCA) {
				_hoops_PIR (nr, matr->_hoops_SCA, &_hoops_RAA, false);
			}
			_hoops_ASA (_hoops_RAA);

			if (BIT(_hoops_CRA, _hoops_CAA))
				m_data[0] |= H3DID_VERTEX_COLORS;
			else if (BIT (_hoops_CRA, _hoops_RSP)) {
				m_data[0] |= H3DID_VERTEX_COLORS;
				m_data[3] |= H3DID_VERTEX_RGBAS;
			}
			else if (BIT(_hoops_CRA, _hoops_HGP))
				m_data[0] |= H3DID_VERTEX_FINDICES;

		} break;
		// _hoops_IH _hoops_ASP
		case 0: {
			m_data[0] |= H3DID_POINT;
			//_hoops_PSP _hoops_HSP _hoops_ISP
		} break;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP))	{
		_hoops_SSP const &		_hoops_GGH = nr->transform_rendition->_hoops_RGH;
		int									_hoops_AGH = _hoops_GGH->_hoops_PGH;

		// _hoops_HGH _hoops_IGH _hoops_PAR _hoops_HAR _hoops_SR _hoops_CGH _hoops_SGH _hoops_RH _hoops_GRH _hoops_RRH _hoops_ARH
		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_AGH = _hoops_GGH->_hoops_CRH;
		}

		// _hoops_SRH?
		if (_hoops_AGH > h3ddata->_hoops_GAH)
		{
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				"DX9 driver shader setup requested more cutting planes than are available. Primitive should have been punted/clipped.");

			// _hoops_RAH _hoops_RH _hoops_AAH _hoops_SR _hoops_PAH - _hoops_HAH _hoops_IAH _hoops_IS _hoops_CAH _hoops_RGR
			_hoops_AGH = h3ddata->_hoops_GAH;
		}

		// _hoops_SAH.
		_hoops_GPH(_hoops_AGH);
	}

	if (!_hoops_GAA) {
		if (ANYBIT (nr->transform_rendition->heuristics, _hoops_RSA)) {
			if (_hoops_RPH() || h3ddata->_hoops_APH)
				m_data[2] |= H3DID_HAS_HANDEDNESS;
		}
	}

	if (!_hoops_CCR() && BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HPH))
		m_data[3] |= H3DID_ATMOSPHERIC_ATTENUATION;

	if (nr->transform_rendition->_hoops_IPH->data._hoops_CPH == 0.0f)
		m_data[3] |= H3DID_NON_UNIFORM_SCALE;

	if (h3ddata->_hoops_SRP)
		m_data[2] |= H3DID_DEPTH_TEXTURE_HARDWARE;

	if (nr->transform_rendition->_hoops_SPH->projection == _hoops_GHH)
		m_data[0] |= H3DID_PERSPECTIVE;

	if (h3ddata->_hoops_RHH.mode) {
		// _hoops_AHH: _hoops_PHH _hoops_HHH _hoops_IHH _hoops_HRP - _hoops_CHH _hoops_SHH _hoops_GIH _hoops_IS _hoops_RIH _hoops_GGR _hoops_AIH _hoops_PIH[0] _hoops_HIH _hoops_IIH
		// _hoops_CHR _hoops_PSP _hoops_CIH _hoops_SIH.
		if (h3ddata->_hoops_RHH._hoops_GCH == H3DFMT_A8R8G8B8)
			m_data[2] |= _hoops_RCH;

		if (h3ddata->_hoops_RHH._hoops_ACH)
			m_data[2] |= H3DID_DEPTH_WRITING_SINGLE_PASS;

		// _hoops_PCH _hoops_ARP _hoops_RH _hoops_HCH _hoops_ICH _hoops_CCH _hoops_RIP, _hoops_CR _hoops_SCH _hoops_GSH _hoops_RSH _hoops_SR _hoops_ASH _hoops_PPR _hoops_PSH _hoops_HCH _hoops_HSH
		m_data[3] |= H3DID_DEPTH_PEELING_MODE;
	}

	if (h3ddata->_hoops_II.mode) {
		if (BIT(nr->transform_rendition->flags, _hoops_ISH))
			// _hoops_CSH _hoops_SSH-_hoops_GGI -> _hoops_PSP _hoops_RGI _hoops_GGR _hoops_HCH _hoops_AGI _hoops_HH _hoops_PGI.
			m_data[0] &= ~H3DID_DEPTH_WRITING;
		else {
			// _hoops_HGI _hoops_IGI _hoops_IS _hoops_SHH _hoops_CGI _hoops_GGR _hoops_AIH _hoops_SGI, _hoops_HIH _hoops_SCH'_hoops_GRI _hoops_RRI _hoops_PRP _hoops_IS _hoops_ARP _hoops_SCH _hoops_GH _hoops_ARR _hoops_ARI.
			m_data[0] |= H3DID_DEPTH_WRITING;
			m_data[2] |= H3DID_DEPTH_WRITING_SINGLE_PASS;

			if (h3ddata->_hoops_II._hoops_PRI)
				m_data[2] |= _hoops_RCH;
		}

		if (h3ddata->_hoops_RHH._hoops_HRI) {
			m_data[0] &= ~H3DID_DEPTH_WRITING;
		}
	}

	if (BIT (nr->transform_rendition->heuristics, _hoops_IRI)) {
		if (BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_CRI))
			m_data[3] |= H3DID_FRAME_BUFFER_EFFECTS;
		if (nr->_hoops_IRR->_hoops_SRI == _hoops_GAI &&
			(nr->_hoops_SRA->_hoops_RAI || h3ddata->_hoops_AAI))
			m_data[3] |= H3DID_PRIORITY_HSRA;
	}

	if (!BIT (HOOPS_WORLD->system_flags, _hoops_PAI))
		m_data[3] |= H3DID_AMBIENT_MATERIAL;
	if (BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI))
		m_data[3] |= H3DID_FORCE_GRAYSCALE;
	if (!_hoops_IAI())
		m_data[3] &= ~H3DID_PER_PIXEL_LIGHTING;

	h3ddata->_hoops_HPA.flags = flags;
	h3ddata->_hoops_HPA._hoops_IPA = nr->_hoops_CPA;
	h3ddata->_hoops_HPA.id = *this;
	h3ddata->_hoops_HPA._hoops_CRA = _hoops_CRA;

	return this;
}


const char *H3DShaderID::_hoops_CAI (
	Net_Rendition const &nr) 
{
	_hoops_RCR *texture = null;

	if (_hoops_SAI())
		texture = nr->_hoops_IHA->_hoops_CHA->_hoops_SCA->texture;
	else if (_hoops_GPI())
		texture = nr->_hoops_SCP->_hoops_CHA->_hoops_SCA->texture;
	else
		texture = nr->_hoops_RHP->_hoops_CHA->_hoops_SCA->texture;

	ASSERT (BIT (texture->_hoops_SCR, _hoops_GSR));
	ASSERT (texture->_hoops_RSR->id == _hoops_RPI());
	return texture->_hoops_RSR->shader_source.text;
}


/* _hoops_HGI _hoops_API _hoops_PPI _hoops_RH _hoops_HH _hoops_HPI _hoops_IPI _hoops_CPI
 * _hoops_IPI - _hoops_SPI, _hoops_GHI, _hoops_RHI, _hoops_AHI.
 * _hoops_PHI - _hoops_HHI, _hoops_IHI, _hoops_CHI, _hoops_AHI.
 * _hoops_SHI - _hoops_GII _hoops_RII _hoops_AII, _hoops_PII _hoops_HII _hoops_III _hoops_CII _hoops_AI.
 */
void H3DShaderID::_hoops_SII(int _hoops_GCI, int number, int *_hoops_RCI, int *_hoops_ACI, int *_hoops_PCI) const
{
	_hoops_HCI _hoops_ICI;

	SET_MEMORY (&_hoops_ICI, sizeof(_hoops_HCI), 0);

	_hoops_ICI._hoops_CCI = (_hoops_SCI()) ? 1 : 0;

	if (_hoops_GSI()) {
		_hoops_ICI._hoops_RSI = 1;
		_hoops_ICI._hoops_ASI = (_hoops_PSI()) ? 1 : 0;
		_hoops_ICI._hoops_HSI = (_hoops_ISI() || _hoops_CSI()) ? 1 : 0;
	}
	if (_hoops_SSI())
		_hoops_ICI._hoops_GGC = 1;

	_hoops_ICI._hoops_RGC = _hoops_AGC();
	_hoops_ICI._hoops_PGC = _hoops_HGC();
	_hoops_ICI._hoops_IGC = _hoops_CGC();
	_hoops_ICI._hoops_SGC = (_hoops_GRC()) ? 1 : 0;
	_hoops_ICI._hoops_RRC = (_hoops_ARC()) ? 1 : 0;
	_hoops_ICI._hoops_PRC = (_hoops_HRC()) ? 1 : 0;
	_hoops_ICI._hoops_IRC = (_hoops_CRC()) ? 1 : 0;
	_hoops_ICI._hoops_SRC = (_hoops_GAC()) ? 1 : 0;
	_hoops_ICI._hoops_RAC = (_hoops_AAC()) ? 1 : 0;
	_hoops_ICI._hoops_PAC = _hoops_IRP();
	_hoops_ICI._hoops_HAC = _hoops_IAC();
	_hoops_ICI._hoops_CAC = (_hoops_SAC()) ? 1 : 0;
	_hoops_ICI._hoops_GPC = (_hoops_RPC() || _hoops_APC()) ? 1 : 0;
	_hoops_ICI._hoops_PPC = (_hoops_HPC() || _hoops_IPC()) ? 1 : 0;
	_hoops_ICI._hoops_CPC = 
		// _hoops_SPC _hoops_GHC _hoops_RRP _hoops_RHC _hoops_AHC
		(_hoops_PHC() || _hoops_RPH()) ? 1 : 0;
	_hoops_ICI.marker = (_hoops_HHC() || _hoops_IHC() || _hoops_CHC() || (_hoops_GPI() && _hoops_SHC())) ? 1 : 0;
	_hoops_ICI._hoops_GIC = _hoops_RIC() ? 1 : 0;
	_hoops_ICI._hoops_AIC = _hoops_PIC() ? 1 : 0;
	_hoops_ICI._hoops_HIC = (_hoops_ARC() || _hoops_SHC()) ? 1 : 0;

	::_hoops_SII(_hoops_GCI, number, &_hoops_ICI, _hoops_RCI, _hoops_ACI, _hoops_PCI);
}


/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_IIC _hoops_AR
*****************************************************************************
*****************************************************************************/
H3DShader::H3DShader(const H3DShaderID& id) :
	// _hoops_SAH _hoops_CIC _hoops_SIC _hoops_PPR _hoops_GCC _hoops_RCC.
	_hoops_ACC(id),
	_hoops_PCC(id),
	_hoops_HCC(false),
	_hoops_ICC(_hoops_CCC),
	_hoops_SCC(_hoops_CCC),
	_hoops_GSC(_hoops_CCC),
	_hoops_RSC(_hoops_CCC)
{
	// _hoops_ASC _hoops_GA'_hoops_RA _hoops_HS _hoops_PSC
	ZERO_STRUCT(&_hoops_HSC, _hoops_ISC);

	SET_MEMORY(_hoops_CSC, _hoops_SSC * sizeof(H3D_Shader_Handle), (char)(POINTER_SIZED_INT)_hoops_GGS);
}

char const *H3DShader::_hoops_RGS (char const *ptr)
{
	//_hoops_AGS _hoops_PGS _hoops_HGS _hoops_PPR _hoops_IGS _hoops_CGS
	//_hoops_PIP _hoops_SGS _hoops_SR _hoops_GRS _hoops_RRP _hoops_IS _hoops_RRS _hoops_ARS _hoops_IGS _hoops_CGS _hoops_ARR
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	return ptr;
}

#define _hoops_PRS(c) (c == '=' || c == '!' || c == '<' || c == '>')

/* _hoops_HRS _hoops_IRS _hoops_CRS _hoops_IS _hoops_RH _hoops_SRS _hoops_GAS _hoops_RAS _hoops_RH _hoops_AAS _hoops_PAS (_hoops_HAS._hoops_IAS. _hoops_CAS
 * _hoops_IS _hoops_SAS _hoops_GPS */
char const *H3DShader::_hoops_RPS (char const *start, char alter *buffer)
{
	char const *ptr = start;
	char alter *_hoops_APS = buffer;

	ptr = _hoops_RGS (ptr);
	_hoops_APS = buffer;
	if (_hoops_PRS(*ptr)) {
		//_hoops_AGS _hoops_RH _hoops_PPS _hoops_HPS
		while (*ptr != ' ' && *ptr != '\t' &&
			*ptr != '\n' && _hoops_PRS(*ptr))
			*_hoops_APS++ = *ptr++;
	}
	else {
		//_hoops_IPS _hoops_CPS _hoops_GH _hoops_IS _hoops_SPS _hoops_PGS _hoops_GC _hoops_PAR _hoops_GRH _hoops_GAS
		while (*ptr != ' ' && *ptr != '\t' &&
			*ptr != '\n' && *ptr != '/' &&
			*ptr != '(' && *ptr != ')' &&
			!_hoops_PRS(*ptr))
			*_hoops_APS++ = *ptr++;
	}

	*_hoops_APS = '\0';
	return ptr;
}


char const *H3DShader::_hoops_GHS (char const *start)
{
	int _hoops_RHS = 0;
	char const *prev, *ptr, *_hoops_AHS;
	char _hoops_PHS[512];

	prev = _hoops_AHS = start;
	while ((_hoops_AHS = strstr (_hoops_AHS, "\n")) != null) {
		_hoops_AHS++;
		prev = _hoops_RGS(prev);
		if (*prev == '#') {
			ptr = prev+1;
			ptr = _hoops_RPS (ptr, _hoops_PHS);
			if (!strncmp (_hoops_PHS, "if", 2)) //_hoops_HHS _hoops_SHH #_hoops_IHS, #_hoops_CHS, _hoops_PAR #_hoops_RPP
				 _hoops_RHS++;
			else if (!strncmp (_hoops_PHS, "el", 2)) { //_hoops_HHS _hoops_SHH #_hoops_SHS _hoops_PAR #_hoops_GIS
				if (_hoops_RHS == 1) {  //_hoops_RIS _hoops_AIS _hoops_CCA _hoops_RH #_hoops_RPP _hoops_PIS _hoops_RGR #_hoops_SHS
					if (_hoops_PHS[2] == 'i')
						return prev; // _hoops_SCH'_hoops_GRI _hoops_IRS #_hoops_GIS, _hoops_HIS _hoops_IIS _hoops_RH _hoops_CIS _hoops_SIS _hoops_GPP _hoops_SCH
					else
						return _hoops_AHS;
				}
				else if (_hoops_RHS == 0)  //_hoops_RIS _hoops_AIS _hoops_CCA _hoops_RGR #_hoops_SHS _hoops_PAR #_hoops_GIS
					_hoops_RHS++;
			}
			else if (!strncmp (_hoops_PHS, "endif", 5))
				 _hoops_RHS--;
		}
		if (_hoops_RHS <= 0)
			break;
		prev = _hoops_AHS;
	}
	return _hoops_AHS;
}

INLINE const char *_hoops_GCS (
	H3D_Driver_Shader_Type _hoops_RCS)
{
	switch (_hoops_RCS) {
		case H3D_Driver_Shader_Type_OGL2:
			return "opengl2";
		case H3D_Driver_Shader_Type_DX9:
			return "dx9";
		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "unrecognized Driver type");
			ASSERT(0);
			return "";
	}
}

bool H3DShader::_hoops_ACS (
		_hoops_PCS *_hoops_HCS,
		char const *ptr)
{
	bool result = false;
	bool _hoops_ICS = false;
	int i, _hoops_CCS;
	char _hoops_PHS[512], _hoops_SCS[512], _hoops_GSS[512];
	POINTER_SIZED_INT _hoops_RSS=0, _hoops_ASS=0;
	_hoops_PCS::status _hoops_PSS;
	const char *_hoops_HSS = _hoops_GCS(_hoops_ISS->_hoops_CSS);

	for (;;) {
		ptr = _hoops_RGS (ptr);
		if (ptr[0] == '|' && ptr[1] == '|')
			return result || _hoops_ACS (_hoops_HCS, ptr+2);
		else if (ptr[0] == '&' && ptr[1] == '&')
			return result && _hoops_ACS (_hoops_HCS, ptr+2);

		if (*ptr == '(') {
			//_hoops_SSS _hoops_RH _hoops_PIS _hoops_GGGR _hoops_RGGR
			_hoops_CCS = 0;
			for (i = 0; i < 4096; i++) {
				if (ptr[i] == '(')
					_hoops_CCS++;
				if (ptr[i] == ')')
					_hoops_CCS--;
				if (!_hoops_CCS)
					break;
			}
			i += 2;
			result = _hoops_ACS (_hoops_HCS, ptr+1);
			if (_hoops_ICS) {
				result = !result;
				_hoops_ICS = false;
			}
			ptr += i;
			ptr = _hoops_RGS (ptr);
			if (ptr[0] == '|' && ptr[1] == '|')
				return result || _hoops_ACS (_hoops_HCS, ptr+2);
			else if (ptr[0] == '&' && ptr[1] == '&')
				return result && _hoops_ACS (_hoops_HCS, ptr+2);
			else
				return result;
		}
		else if (ptr[0] == ')')
			return result;
		else {
			ptr = _hoops_RPS (ptr, _hoops_PHS);
			if (_hoops_PHS[0] >= '0' && _hoops_PHS[0] <= '9')
				_hoops_RSS = atoi(_hoops_PHS);
			else if (_hoops_AGGR(_hoops_PHS, "!")) {
				_hoops_ICS = true;
				continue;
			}
			else if (_hoops_AGGR(_hoops_PHS, "defined")) {
				ptr = _hoops_RGS (ptr);
				if (ptr[0] != '(') {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						Sprintf_SS (null, "(-1) shader parse error in %S driver\n%S", _hoops_HSS, ptr));
				}
				ptr = _hoops_RPS (ptr+1, _hoops_PHS);
				ptr = _hoops_RGS (ptr);
				if (ptr[0] != ')') {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						Sprintf_SS (null, "(0) shader parse error in %S driver\n%S", _hoops_HSS, ptr));
				}
				ptr++;

				_hoops_PSS = _hoops_HCS->LookupItem(_hoops_PHS, &_hoops_RSS);
				if (_hoops_PSS == _hoops_PCS::Success)
					result = true;
				else
					result = false;

				if (_hoops_ICS) {
					result = !result;
					_hoops_ICS = false;
				}

				ptr = _hoops_RGS (ptr);

				if (ptr[0] == '\n')
					return result;
				continue;
			}
			else {
				_hoops_PSS = _hoops_HCS->LookupItem(_hoops_PHS, &_hoops_RSS);
				if (_hoops_PSS != _hoops_PCS::Success) {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						Sprintf_SS (null, "(1) shader parse error in %S driver\n%S", _hoops_HSS, ptr));
				}
			}
			_hoops_ICS = false;
		}

		ptr = _hoops_RPS (ptr, _hoops_SCS);
		ptr = _hoops_RPS (ptr, _hoops_GSS);

		if (_hoops_GSS[0] != '\0') {
			//_hoops_RPP (_hoops_PGGR[0] >= '/' && _hoops_PGGR[0] <= '9')
			//	_hoops_HGGR = _hoops_IGGR(_hoops_PGGR);
			if (_hoops_GSS[0] >= '0' && _hoops_GSS[0] <= '9')
				_hoops_ASS = atoi(_hoops_GSS);
			else {
				_hoops_PSS = _hoops_HCS->LookupItem(_hoops_GSS, &_hoops_ASS);
				if (_hoops_PSS == _hoops_PCS::Success) {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						Sprintf_SS (null, "(2) shader parse error in %S driver\n%S", _hoops_HSS, ptr));
				}
			}
			if (_hoops_AGGR (_hoops_SCS, "=="))
				result  = (_hoops_RSS == _hoops_ASS);
			else if (_hoops_AGGR (_hoops_SCS, "!="))
				result = (_hoops_RSS != _hoops_ASS);
			else if (_hoops_AGGR (_hoops_SCS, "<="))
				result = (_hoops_RSS <= _hoops_ASS);
			else if (_hoops_AGGR (_hoops_SCS, ">="))
				result = (_hoops_RSS >= _hoops_ASS);
			else if (_hoops_AGGR (_hoops_SCS, "<"))
				result = (_hoops_RSS < _hoops_ASS);
			else if (_hoops_AGGR (_hoops_SCS, ">"))
				result = (_hoops_RSS > _hoops_ASS);
			else
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				Sprintf_SS (null, "(3) shader parse error in %S driver\n%S", _hoops_HSS, ptr));
		}
		else
			return (_hoops_RSS != 0);
	}
}

/*
 *  _hoops_CGGR _hoops_SGGR _hoops_GRGR _hoops_RRGR
 *  _hoops_ARGR _hoops_PRGR _hoops_HRGR _hoops_IRGR _hoops_CRGR _hoops_SRGR
 */
bool H3DShader::_hoops_GAGR (
	char alter *	_hoops_RAGR,
	int alter *		_hoops_AAGR)
{
	char const *prev, *ptr, *_hoops_AHS;
	char alter *_hoops_PAGR;
	char _hoops_PHS[512];
	_hoops_PCS *_hoops_HCS = null;
	POINTER_SIZED_INT _hoops_HAGR;
	int length;
	bool status = false;
	bool _hoops_IAGR = true;
	char alter *_hoops_CAGR;
	_hoops_PCS::status _hoops_PSS;

	ALLOC_ARRAY_CACHED (_hoops_CAGR, _hoops_SA, char);

	_hoops_HCS = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_PCS)(HOOPS_WORLD->memory_pool, 1024);
	prev = _hoops_AHS = _hoops_RAGR;
	_hoops_PAGR = _hoops_CAGR;
	while ((_hoops_AHS != null) && ((_hoops_AHS = strstr (_hoops_AHS, "\n")) != null)) {
		_hoops_AHS++;
		ptr = _hoops_RGS(prev);

		/* _hoops_SAGR _hoops_GPGR _hoops_RPGR _hoops_APGR _hoops_CRGR _hoops_SPR */
		if (*ptr == '\n') {
			if (_hoops_IAGR) {
				*_hoops_PAGR++ = '\n';
				_hoops_IAGR = false;
			}
			_hoops_AHS--; //_hoops_PPGR _hoops_IH _hoops_RH _hoops_IHH ++ _hoops_HPGR _hoops_GPP _hoops_RH _hoops_SRS _hoops_IPGR
			do {
				ptr = _hoops_RGS(prev);
				if (*ptr != '\n')
					break;
				_hoops_AHS++;
				prev = _hoops_AHS;
			} while ((_hoops_AHS = strstr (_hoops_AHS, "\n")) != null);
			if (!_hoops_AHS)
				break;
			_hoops_AHS++;
		}

		if (*ptr == '#') {
			ptr++;
			ptr = _hoops_RPS (ptr, _hoops_PHS);
			if (_hoops_AGGR (_hoops_PHS, "define")) {
				_hoops_PHS[0] = '\0';
				ptr = _hoops_RPS (ptr, _hoops_PHS);
				ptr = _hoops_RGS(ptr);
				if (ptr[0] >= '0' && ptr[0] <= '9')
					_hoops_HAGR = atoi (ptr);
				else
					_hoops_HAGR = 1;
				_hoops_HCS->InsertItem(_hoops_PHS, _hoops_HAGR);
			}
			else if (_hoops_AGGR (_hoops_PHS, "ifdef")) {
				ptr = _hoops_RPS (ptr, _hoops_PHS);
				_hoops_PSS = _hoops_HCS->LookupItem(_hoops_PHS, &_hoops_HAGR);
				if (_hoops_PSS != _hoops_PCS::Success)
					_hoops_AHS = _hoops_GHS(prev);
				prev = _hoops_AHS;
				continue;
			}
			else if (_hoops_AGGR (_hoops_PHS, "ifndef")) {
				ptr = _hoops_RPS (ptr, _hoops_PHS);
				_hoops_PSS = _hoops_HCS->LookupItem(_hoops_PHS, &_hoops_HAGR);
				if (_hoops_PSS == _hoops_PCS::Success)
					_hoops_AHS = _hoops_GHS(prev);
				prev = _hoops_AHS;
				continue;
			}
			else if (_hoops_AGGR (_hoops_PHS, "if") ||
				     _hoops_AGGR (_hoops_PHS, "elif")) {
				if (!_hoops_ACS (_hoops_HCS, ptr))
					_hoops_AHS = _hoops_GHS(prev);
				prev = _hoops_AHS;
				continue;
			}
			else if (_hoops_AGGR (_hoops_PHS, "else")) {
				_hoops_AHS = _hoops_GHS(prev);
				prev = _hoops_AHS;
				continue;
			}
			else if (_hoops_AGGR (_hoops_PHS, "endif")) {
				prev = _hoops_AHS;
				continue;
			}
		}
		_hoops_IAGR = true;
		if (_hoops_AHS - prev)
			COPY_MEMORY (prev, _hoops_AHS - prev, _hoops_PAGR);
		_hoops_PAGR += (_hoops_AHS - prev);
		prev = _hoops_AHS;
	}

	*_hoops_PAGR++ = '\0';
	length = _hoops_PAGR - _hoops_CAGR;
	COPY_MEMORY (_hoops_CAGR, length, _hoops_RAGR);
	FREE_ARRAY (_hoops_CAGR, _hoops_SA, char);
	*_hoops_AAGR = length;
	status = true;
	delete _hoops_HCS;
	return (status == _hoops_PCS::Success);
}


#define _hoops_CPGR 10

struct _hoops_SPGR
{
	char name[50];
	char value[50];

	void _hoops_GHGR(const char *iname, const char *ivalue) {
		strcpy(name, iname);
		strcpy(value, ivalue);
	}

	void _hoops_GHGR(const char *iname, const int ivalue) {
		strcpy(name, iname);
		sprintf(value, "%d", ivalue);
	}
};

struct H3D_Macro_Definition
{
	char *start;
	char *end;
	_hoops_SPGR pair[_hoops_CPGR];
};
typedef VList<H3D_Macro_Definition *> H3D_Macro_List;

char alter * H3DShader::_hoops_RHGR (
		char const *filename,
		char const *string,
		char alter *ptr,
		char const *end,
		_hoops_AHGR type)
{
	H3D_Macro_List _hoops_HCS(HOOPS_WORLD->memory_pool);
	H3D_Macro_Definition *_hoops_PHGR;
	char *_hoops_HHGR;
	const char *_hoops_IHGR, *_hoops_CHGR;	// _hoops_IGI _hoops_IS _hoops_SHGR _hoops_GIGR _hoops_RIGR
	char token[512];
	int i = 0;

	ALLOC_ARRAY(_hoops_HHGR, _hoops_SA, char);
	_hoops_AIGR(filename, string, _hoops_HHGR, &_hoops_HHGR[_hoops_SA-1]);

	// _hoops_PIGR _hoops_IRS _hoops_HIGR _hoops_IIGR _hoops_HCR _hoops_CIGR _hoops_SIGR
	if (type == _hoops_GCGR) {
		for (i = 1; i < _hoops_PCC._hoops_HGC(); i++) {
			ALLOC(_hoops_PHGR, H3D_Macro_Definition);
			_hoops_PHGR->start = strstr(_hoops_HHGR, "#define PROCESS_VS_TEXTURE");
			_hoops_PHGR->end = strstr(_hoops_PHGR->start, "#endmacro");
			_hoops_PHGR->pair[0]._hoops_GHGR("facing", "FRONT");
			_hoops_PHGR->pair[1]._hoops_GHGR("unit", i);
			_hoops_PHGR->pair[2]._hoops_GHGR("uv", "uv");
			_hoops_HCS.AddLast(_hoops_PHGR);
		}

		for (i = 1; i < _hoops_PCC._hoops_CGC(); i++) {
			ALLOC(_hoops_PHGR, H3D_Macro_Definition);
			_hoops_PHGR->start = strstr(_hoops_HHGR, "#define PROCESS_VS_TEXTURE");
			_hoops_PHGR->end = strstr(_hoops_PHGR->start, "#endmacro");
			_hoops_PHGR->pair[0]._hoops_GHGR("facing", "BACK");
			_hoops_PHGR->pair[1]._hoops_GHGR("unit", i);
			_hoops_PHGR->pair[2]._hoops_GHGR("uv", "buv");
			_hoops_HCS.AddLast(_hoops_PHGR);
		}
	}
	else {
		for (i = 1; i <  _hoops_PCC._hoops_HGC(); i++) {
			ALLOC(_hoops_PHGR, H3D_Macro_Definition);
			_hoops_PHGR->start = strstr(_hoops_HHGR, "#define PROCESS_PS_TEXTURE");
			_hoops_PHGR->end = strstr(_hoops_PHGR->start, "#endmacro");
			_hoops_PHGR->pair[0]._hoops_GHGR("sampler", "Diffuse");
			_hoops_PHGR->pair[1]._hoops_GHGR("unit", _hoops_PCC._hoops_AGC() ? 0 : i);
			_hoops_PHGR->pair[2]._hoops_GHGR("sampler_unit", i);
			_hoops_PHGR->pair[3]._hoops_GHGR("uv", _hoops_PCC._hoops_SHC() ? "uvst" : "uv");
			_hoops_PHGR->pair[4]._hoops_GHGR("facing_value", 1);
			_hoops_HCS.AddLast(_hoops_PHGR);
		}

		for (i = 1; i < _hoops_PCC._hoops_CGC(); i++) {
			ALLOC(_hoops_PHGR, H3D_Macro_Definition);
			_hoops_PHGR->start = strstr(_hoops_HHGR, "#define PROCESS_PS_TEXTURE");
			_hoops_PHGR->end = strstr(_hoops_PHGR->start, "#endmacro");
			_hoops_PHGR->pair[0]._hoops_GHGR("sampler", "BackDiffuse");
			_hoops_PHGR->pair[1]._hoops_GHGR("unit", i);
			_hoops_PHGR->pair[2]._hoops_GHGR("sampler_unit", i);
			_hoops_PHGR->pair[3]._hoops_GHGR("uv", "buv");
			_hoops_PHGR->pair[4]._hoops_GHGR("facing_value", 0);
			_hoops_HCS.AddLast(_hoops_PHGR);
		}

		for (i = 0; i < 4; i++) {
			ALLOC(_hoops_PHGR, H3D_Macro_Definition);
			_hoops_PHGR->start = strstr(_hoops_HHGR, "#define SHADOWED_DISTANT_LIGHT");
			_hoops_PHGR->end = strstr(_hoops_PHGR->start, "#endmacro");
			_hoops_PHGR->pair[0]._hoops_GHGR("which", i);
			_hoops_HCS.AddLast(_hoops_PHGR);
		}

		for (i = 0; i < 4; i++) {
			ALLOC(_hoops_PHGR, H3D_Macro_Definition);
			_hoops_PHGR->start = strstr(_hoops_HHGR, "#define SHADOWED_SPOT_LIGHT");
			_hoops_PHGR->end = strstr(_hoops_PHGR->start, "#endmacro");
			_hoops_PHGR->pair[0]._hoops_GHGR("which", i);
			_hoops_HCS.AddLast(_hoops_PHGR);
		}
	}

	// _hoops_RCGR _hoops_HCR _hoops_CIGR
	while((_hoops_PHGR = _hoops_HCS.RemoveFirst()) != null) {
		_hoops_IHGR = _hoops_PHGR->start;
		while (true) {
			// _hoops_ACGR _hoops_PCGR _hoops_AHC
			_hoops_CHGR = _hoops_IHGR;
			_hoops_IHGR = strstr(_hoops_IHGR, "##(");

			// _hoops_RCGR _hoops_HCGR _hoops_ICGR _hoops_GH _hoops_CCGR _hoops_SCGR _hoops_PCGR _hoops_GSGR
			if (_hoops_IHGR && _hoops_IHGR < _hoops_PHGR->end) {
				COPY_MEMORY(_hoops_CHGR, _hoops_IHGR - _hoops_CHGR, ptr);
				ptr += (_hoops_IHGR - _hoops_CHGR);
			}
			else {
				//_hoops_RSGR _hoops_IIGR _hoops_RIGR
				COPY_MEMORY(_hoops_CHGR, _hoops_PHGR->end - _hoops_CHGR, ptr);
				ptr += (_hoops_PHGR->end - _hoops_CHGR);
				break;
			}
			
			// _hoops_ASGR _hoops_PSGR
			_hoops_IHGR += 3;										// _hoops_HSGR _hoops_ISGR ##(
			_hoops_IHGR = _hoops_RPS(_hoops_IHGR, token);
			_hoops_IHGR ++;										// _hoops_HSGR _hoops_ISGR _hoops_CSGR )
			for (i = 0; i < _hoops_CPGR; i++) {
				if (_hoops_AGGR(token, _hoops_PHGR->pair[i].name)) {
					sprintf(ptr, "%s", _hoops_PHGR->pair[i].value);
					break;
				}
				ASSERT(i < _hoops_CPGR);
			}
			ptr += _hoops_SSGR(ptr);
			
		}

		*ptr++ = '\n';
		*ptr = '\0';
		FREE(_hoops_PHGR, H3D_Macro_Definition);
		_hoops_HCS.AdvanceCursor();
	}

	if (ptr > end) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
			Sprintf_S (null, "shader scratch space overrun detected in dx9:\n%S", ptr));
	}

	FREE_ARRAY(_hoops_HHGR, _hoops_SA, char);
	return ptr;
}



//
// _hoops_GGRR _hoops_RGRR _hoops_PIH _hoops_GGR _hoops_AGRR _hoops_PGRR _hoops_IIGR _hoops_HGRR _hoops_IGRR.
//

static const float _hoops_CGRR[2] =
{
	0.0f, 0.0f
};
static const float _hoops_SGRR[8] =
{
#ifdef _hoops_GRRR
	0.508986f, 0.00375843f,
	-0.529341f, 0.325585f,
	-0.0711739f, -0.964213f,
	0.860188f, -0.324217f,
#else
     -0.137659f,     0.579446f,
      0.19484f,     -0.627847f,
      0.898229f,     0.296021f,
     -0.95541f,     -0.24762f,
#endif
};
static const float _hoops_RRRR[16] =
{
#ifdef _hoops_GRRR
	-0.399261f, -0.825758f,
	0.446122f, -0.401327f,
	-0.802823f, 0.0323558f,
	-0.166223f, 0.379559f,
	0.277122f, 0.189368f,
	-0.00978094f, -0.129954f,
	0.627247f, 0.663127f,
	-0.598673f, -0.631267f,
#else
	 0.743012f,     0.379432f,
	-0.236977f,    -0.482085f,
	-0.510773f,     0.452725f,
	 0.565749f,    -0.293779f,
	-0.885718f,    -0.233393f,
	-0.0449455f,     0.984452f,
	 0.256112f,    -0.966618f,
	 0.113541f,     0.159266f,
	#endif
};
static const float _hoops_ARRR[24] =
{
#ifdef _hoops_GRRR
	0.829508f, 0.507629f,
	0.326025f, 0.10127f,
	0.105371f, 0.281896f,
	0.475452f, 0.746805f,
	-0.839022f, -0.23169f,
	0.646061f, -0.693608f,
	-0.123454f, -0.355643f,
	-0.657999f, -0.472883f,
	-0.423655f, -0.0614396f,
	-0.274927f, 0.908686f,
	-0.541896f, 0.623274f,
	-0.0086866f, -0.982226f,
#else
	-0.0394162f,      0.38266f,
	  0.582456f,    0.0242637f,
	 -0.589562f,     -0.57246f,
	 -0.814397f,    -0.115057f,
	 -0.689398f,     0.399602f,
	  0.368282f,    -0.859487f,
	 -0.132284f,    -0.343562f,
	  0.549291f,     0.543824f,
	 -0.190733f,     0.876198f,
	 -0.178353f,    -0.911614f,
	  0.822115f,     -0.41905f,
	     0.312f,     0.994681f,
#endif
};
static const float _hoops_PRRR[32] =
{
#ifdef _hoops_GRRR
	0.187381f, 0.492949f,
	0.00689042f, 0.830316f,
	-0.207254f, 0.647487f,
	-0.366166f, -0.282961f,
	-0.80751f, -0.0948964f,
	0.428077f, 0.0191922f,
	0.303393f, -0.726621f,
	-0.109815f, 0.357968f,
	-0.580882f, -0.512129f,
	-0.467321f, -0.387513f,
	0.906418f, 0.175212f,
	0.784523f, -0.18148f,
	0.569622f, 0.266554f,
	0.0927606f, -0.846979f,
	-0.673017f, 0.733764f,
	0.656184f, -0.600289f,
#else
	-0.642157f,    -0.672388f,
	 0.812749f,    -0.341659f,
	 0.530664f,     0.156942f,
	-0.203784f,    -0.116856f,
	-0.667689f,    -0.267132f,
	 0.343684f,    -0.346241f,
	 0.210819f,     0.786453f,
	-0.230371f,    -0.723589f,
	 0.266352f,    -0.858327f,
	-0.490444f,      0.17199f,
	-0.615004f,     0.669584f,
	-0.941863f,    0.0537163f,
	 0.109043f,     0.297582f,
	-0.186288f,     0.643705f,
	 0.767263f,     0.496479f,
	 0.937026f,    0.0497397f,
	#endif
};


char alter *H3DShader::_hoops_HRRR(
	   H3DShaderID &id,
	   char alter *ptr,
	   char const *end,
	   _hoops_IRRR _hoops_CRRR,
	   _hoops_AHGR type)
{
	int _hoops_SRRR = 0;
	int _hoops_GARR = 0;
	int _hoops_RARR = 0;

	static const char *_hoops_AARR[_hoops_PARR] =
	{
		"2", "2X", "3"
	};

	static const char *_hoops_HARR[_hoops_IARR] = 
	{
		"VERTEX", "PIXEL"
	};

	// _hoops_CARR _hoops_CI _hoops_SARR _hoops_SRS
	sprintf (ptr, "#define SHADER_MODEL_%s\n", _hoops_AARR[_hoops_CRRR]);
	ptr += _hoops_SSGR(ptr);

	// _hoops_CARR _hoops_CI _hoops_GPRR
	sprintf (ptr, "#define %s_SHADER\n", _hoops_HARR[type]);
	ptr += _hoops_SSGR(ptr);

	if (type == _hoops_GCGR && !id._hoops_RPH()) {
		sprintf (ptr, "#define LIGHTING\n");
		ptr += _hoops_SSGR(ptr);
	}
	else if (type == _hoops_RPRR && id._hoops_RPH()) {
		sprintf (ptr, "#define LIGHTING\n");
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_AGC()) {
		sprintf (ptr, "#define SHARED_DIFFUSE_COORDS\n");
		ptr += _hoops_SSGR(ptr);
	}

	if (_hoops_HCC) {
		sprintf (ptr, "#define SHADER_MUST_FOG\n");
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_CCR()) {
		sprintf (ptr, "#define DC\n");
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_SAI()) {
		sprintf (ptr, "#define TRIANGLE\n");
		ptr += _hoops_SSGR(ptr);
	}

	sprintf (ptr, "#define DISTANT_LIGHT_COUNT %d\n", id._hoops_APRR());
	ptr += _hoops_SSGR(ptr);
	sprintf (ptr, "#define POINT_LIGHT_COUNT %d\n", id._hoops_PPRR());
	ptr += _hoops_SSGR(ptr);
	sprintf (ptr, "#define SPOT_LIGHT_COUNT %d\n", id._hoops_HPRR());
	ptr += _hoops_SSGR(ptr);

	if (id._hoops_IAI()) {
		sprintf (ptr, "#define HAS_LIGHTING\n");
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_IPRR()) {
		sprintf (ptr, "#define WRITE_LUMINANCE\n");
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_IAI() ||
		id._hoops_GAC()) {
		sprintf (ptr, "#define HAS_VERTEX_NORMALS\n");
		ptr += _hoops_SSGR(ptr);

		sprintf (ptr, "#define NORMAL_FLIP_SIGN %f\n", id._hoops_CPRR());
		ptr += _hoops_SSGR(ptr);

		if (id._hoops_SPRR()) {
			sprintf (ptr, "#define RIGHT_HANDED_MATRIX\n");
			ptr += _hoops_SSGR(ptr);
		}

		if (id._hoops_GHRR()) {
			sprintf (ptr, "#define HAS_HANDEDNESS\n");
			ptr += _hoops_SSGR(ptr);
		}
	}

	if (id._hoops_ARC() || id._hoops_SHC()) {
		id._hoops_SII(_hoops_RHRR, 0, &_hoops_SRRR, &_hoops_GARR, null);

		sprintf (ptr, "#define TANGENT_COORD TEXCOORD%d\n", _hoops_SRRR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define TANGENT_COORD_OUT OUT_TEXCOORD%d\n", _hoops_GARR);
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_AHRR()) {
		sprintf (ptr, "#define HAS_ATMOSPHERIC_ATTENUATION\n");
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_PHRR()) {
		sprintf (ptr, "#define HAS_NON_UNIFORM_SCALE\n");
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_HHRR()) {
		sprintf (ptr, "#define POLY_CYLINDER\n");
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_GSI()) {
		id._hoops_SII(_hoops_IHRR, 0, &_hoops_SRRR, &_hoops_GARR, null);
		sprintf (ptr, "#define WIDE_LINE\n");
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define OFFSET_COORD TEXCOORD%d\n", _hoops_SRRR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define OFFSET_COORD_OUT OUT_TEXCOORD%d\n", _hoops_GARR);
		ptr += _hoops_SSGR(ptr);

		id._hoops_SII(_hoops_CHRR, 0, &_hoops_SRRR, null, null);
		sprintf (ptr, "#define NEXT_COORD TEXCOORD%d\n", _hoops_SRRR);
		ptr += _hoops_SSGR(ptr);

		if (id._hoops_PSI()) {
			id._hoops_SII(_hoops_SHRR, 0, &_hoops_SRRR, null, null);
			sprintf (ptr, "#define MITERED_LINE\n");
			ptr += _hoops_SSGR(ptr);
			sprintf (ptr, "#define PREV_COORD TEXCOORD%d\n", _hoops_SRRR);
			ptr += _hoops_SSGR(ptr);
		}
		if (id._hoops_ISI() || id._hoops_CSI()) {
			if (id._hoops_ISI()) {
				//_hoops_IH _hoops_GIRR _hoops_RIRR/_hoops_AIRR
				sprintf (ptr, "#define ROUND_LINE\n");
				ptr += _hoops_SSGR(ptr);
			}
			if (id._hoops_CSI()) {
				sprintf (ptr, "#define ANTI_ALIASED_LINE\n");
				ptr += _hoops_SSGR(ptr);
			}
			id._hoops_SII(_hoops_PIRR, 0, &_hoops_SRRR, null, &_hoops_RARR);
			sprintf (ptr, "#define ROUND_COORD TEXCOORD%d\n", _hoops_SRRR);
			ptr += _hoops_SSGR(ptr);
			sprintf (ptr, "#define LINE_TOOLS_REGISTER s%d\n", _hoops_RARR);
			ptr += _hoops_SSGR(ptr);
		}
	}
	if (id._hoops_SSI()) {
		id._hoops_SII(_hoops_HIRR, 0, &_hoops_SRRR, &_hoops_GARR, &_hoops_RARR);

		sprintf (ptr, "#define HAS_LINE_PATTERN\n");
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define LINE_PATTERN_COORD TEXCOORD%d\n", _hoops_SRRR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define LINE_PATTERN_COORD_OUT OUT_TEXCOORD%d\n", _hoops_GARR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define LINE_PATTERN_REGISTER s%d\n", _hoops_RARR);
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_HHC()) {
		sprintf (ptr, "#define QUAD_MARKER\n");
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_IIRR()) {
		sprintf (ptr, "#define SPRITE_MARKER\n");
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_CIRR()) {
		sprintf (ptr, "#define WORLD_SPACE_MARKER\n");
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_IHC()) {
		sprintf (ptr, "#define CIRCLE_MARKER\n");
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_CHC()) {
		sprintf (ptr, "#define TEXTURE_MARKER\n");
		ptr += _hoops_SSGR(ptr);

		if (_hoops_ISS->_hoops_CSS == H3D_Driver_Shader_Type_DX9)
			sprintf(ptr, "#define MARKER_HALF_PIXEL_OFFSET float2(0.0, 0.0)\n");
		else
			sprintf(ptr, "#define MARKER_HALF_PIXEL_OFFSET float2(1.0, 0.0)\n");
		ptr += _hoops_SSGR(ptr);
	}
	else {
		if (_hoops_ISS->_hoops_CSS == H3D_Driver_Shader_Type_DX9)
			sprintf(ptr, "#define MARKER_HALF_PIXEL_OFFSET float2(1.0, 0.0)\n");
		else
			sprintf(ptr, "#define MARKER_HALF_PIXEL_OFFSET float2(0.5, 0.5)\n");
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_SIRR()) {
		sprintf (ptr, "#define SNAPPED_MARKER\n");
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_HHC() || id._hoops_IHC() || id._hoops_CHC() || (id._hoops_GPI() && id._hoops_SHC())) {
		// _hoops_GCRR _hoops_RCRR _hoops_SR _hoops_ACRR _hoops_HH _hoops_PCRR
		id._hoops_SII(_hoops_HCRR, 0, &_hoops_SRRR, &_hoops_GARR, &_hoops_RARR);
		
		sprintf (ptr, "#define MARKER_TEXTURE TEXCOORD%d\n", _hoops_SRRR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define MARKER_TEXTURE_OUT OUT_TEXCOORD%d\n", _hoops_GARR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define MARKER_TEXTURE_REGISTER s%d\n", _hoops_RARR);
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_SAC()) {
		if (id._hoops_ICRR()) {
			sprintf (ptr, "#define HAS_TRANSPARENCY_STIPPLE\n");
			ptr += _hoops_SSGR(ptr);
		}

		id._hoops_SII(_hoops_CCRR, 0, &_hoops_SRRR, &_hoops_GARR, &_hoops_RARR);

		sprintf (ptr, "#define HAS_FACE_PATTERN\n");
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define FACE_PATTERN_COORD TEXCOORD%d\n", _hoops_SRRR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define FACE_PATTERN_COORD_OUT OUT_TEXCOORD%d\n", _hoops_GARR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define FACE_PATTERN_REGISTER s%d\n", _hoops_RARR);
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_SHC()) {
		sprintf (ptr, "#define HAS_DEFINED_MATERIAL_SHADER\n");
		ptr += _hoops_SSGR(ptr);
		if (id._hoops_GPI()) {
			sprintf (ptr, "#define MATERIAL_SHADER_MARKER\n");
			ptr += _hoops_SSGR(ptr);
		}
		if (id._hoops_SCRR()) {
			sprintf (ptr, "#define DEFINED_MATERIAL_MULTITEXTURE\n");
			ptr += _hoops_SSGR(ptr);
		}
		switch (id._hoops_GSRR()) {
			case H3DID_DEFINED_MATERIAL_PS_UVW:
				sprintf (ptr, "#define DEFINED_MATERIAL_PS_UVW\n");
				ptr += _hoops_SSGR(ptr);
				break;
			case H3DID_DEFINED_MATERIAL_PS_PHYSICAL_REFLECTION:
				sprintf (ptr, "#define DEFINED_MATERIAL_PS_PHYSICAL_REFLECTION\n");
				ptr += _hoops_SSGR(ptr);
				break;
			case H3DID_DEFINED_MATERIAL_PS_OBJECT:
				sprintf (ptr, "#define DEFINED_MATERIAL_PS_OBJECT\n");
				ptr += _hoops_SSGR(ptr);
				break;
			case H3DID_DEFINED_MATERIAL_PS_SURFACE_NORMAL:
				sprintf (ptr, "#define DEFINED_MATERIAL_PS_SURFACE_NORMAL\n");
				ptr += _hoops_SSGR(ptr);
				break;
			case H3DID_DEFINED_MATERIAL_PS_LOCAL_PIXELS:
				sprintf (ptr, "#define DEFINED_MATERIAL_PS_LOCAL_PIXELS\n");
				ptr += _hoops_SSGR(ptr);
				break;
			case H3DID_DEFINED_MATERIAL_PS_OUTER_PIXELS:
				sprintf (ptr, "#define DEFINED_MATERIAL_PS_OUTER_PIXELS\n");
				ptr += _hoops_SSGR(ptr);
				break;
			case H3DID_DEFINED_MATERIAL_PS_LOCAL_WINDOW:
				sprintf (ptr, "#define DEFINED_MATERIAL_PS_LOCAL_WINDOW\n");
				ptr += _hoops_SSGR(ptr);
				break;
			case H3DID_DEFINED_MATERIAL_PS_OUTER_WINDOW:
				sprintf (ptr, "#define DEFINED_MATERIAL_PS_OUTER_WINDOW\n");
				ptr += _hoops_SSGR(ptr);
				break;
			case H3DID_DEFINED_MATERIAL_PS_WORLD:
				sprintf (ptr, "#define DEFINED_MATERIAL_PS_WORLD\n");
				ptr += _hoops_SSGR(ptr);
				break;
		}
	}

	sprintf (ptr, "#define TEXTURE_COUNT %d\n", id._hoops_HGC());
	ptr += _hoops_SSGR(ptr);
	if (id._hoops_RSRR()) {
		sprintf (ptr, "#define HAS_TEXTURE3D\n");
		ptr += _hoops_SSGR(ptr);
	}

	int _hoops_ASRR = 0;
	for (_hoops_ASRR = 0; _hoops_ASRR < id._hoops_HGC(); _hoops_ASRR++) {
		id._hoops_SII(_hoops_PSRR, _hoops_ASRR, &_hoops_SRRR, &_hoops_GARR, &_hoops_RARR);
		
		sprintf (ptr, "#define DIFFUSE_TEXTURE_COORD%d TEXCOORD%d\n", _hoops_ASRR, _hoops_SRRR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define DIFFUSE_TEXTURE_COORD%d_OUT OUT_TEXCOORD%d\n", _hoops_ASRR, _hoops_GARR);
		ptr += _hoops_SSGR(ptr);

		// _hoops_HSRR _hoops_RH _hoops_SRS _hoops_ISRR _hoops_CSRR (_hoops_SSRR _hoops_GGAR _hoops_HH) _hoops_RGAR
		if (_hoops_ASRR == 0) {
			// _hoops_AGAR _hoops_HH _hoops_ISRR.
			sprintf (ptr, "#define DIFFUSE_TEXTURE_INTERPOLATOR0 TEXCOORD%d\n", _hoops_SRRR);
			ptr += _hoops_SSGR(ptr);
			sprintf (ptr, "#define DIFFUSE_TEXTURE_INTERPOLATOR0_OUT OUT_TEXCOORD%d\n", _hoops_GARR);
			ptr += _hoops_SSGR(ptr);
		}

		if (_hoops_ASRR > 0) {
			sprintf (ptr, "#define TEXTURE%d_WORLD %s\n", _hoops_ASRR, id._hoops_PGAR(_hoops_ASRR) ? "true" : "false");
			ptr += _hoops_SSGR(ptr);

			sprintf (ptr, "#define TEXTURE%d_DECAL %s\n", _hoops_ASRR, id._hoops_HGAR(_hoops_ASRR) ? "true" : "false");
			ptr += _hoops_SSGR(ptr);

			sprintf (ptr, "#define TEXTURE%d_COLOR %s\n", _hoops_ASRR, id._hoops_IGAR(_hoops_ASRR) ? "true" : "false");
			ptr += _hoops_SSGR(ptr);

			sprintf (ptr, "#define TEXTURE%d_MODULATE %s\n", _hoops_ASRR, id._hoops_CGAR(_hoops_ASRR) ? "true" : "false");
			ptr += _hoops_SSGR(ptr);

			sprintf (ptr, "#define TEXTURE%d_DROP %s\n", _hoops_ASRR, id._hoops_SGAR(_hoops_ASRR) ? "true" : "false");
			ptr += _hoops_SSGR(ptr);
		}
		else {
			/* _hoops_GRAR 0 _hoops_HRGR _hoops_GIR _hoops_RRAR, _hoops_PPR _hoops_CCA _hoops_RII _hoops_ARAR _hoops_GAR _hoops_PRAR, _hoops_HIS _hoops_HRAR _hoops_GPP #_hoops_IHS */
			if (id._hoops_PGAR(0)) {
				sprintf (ptr, "#define TEXTURE%d_WORLD\n", _hoops_ASRR);
				ptr += _hoops_SSGR(ptr);
			}
			if (id._hoops_HGAR(0)) {
				sprintf (ptr, "#define TEXTURE%d_DECAL\n", _hoops_ASRR);
				ptr += _hoops_SSGR(ptr);
			}
			if (id._hoops_IGAR(0)) {
				sprintf (ptr, "#define TEXTURE%d_COLOR\n", _hoops_ASRR);
				ptr += _hoops_SSGR(ptr);
			}
			if (id._hoops_CGAR(0)) {
				sprintf (ptr, "#define TEXTURE%d_MODULATE\n", _hoops_ASRR);
				ptr += _hoops_SSGR(ptr);
			}
			if (id._hoops_SGAR(0)) {
				sprintf (ptr, "#define TEXTURE%d_DROP\n", _hoops_ASRR);
				ptr += _hoops_SSGR(ptr);
			}
		}

		sprintf (ptr, "#define DIFFUSE_TEXTURE%d_REGISTER s%d\n", _hoops_ASRR, _hoops_RARR);
		ptr += _hoops_SSGR(ptr);
	}

	sprintf (ptr, "#define BACK_TEXTURE_COUNT %d\n", id._hoops_CGC()); ptr += _hoops_SSGR(ptr);
	for (_hoops_ASRR = 0; _hoops_ASRR < id._hoops_CGC(); _hoops_ASRR++) {
		id._hoops_SII(_hoops_IRAR, _hoops_ASRR, &_hoops_SRRR, &_hoops_GARR, &_hoops_RARR);
		
		sprintf (ptr, "#define BACK_DIFFUSE_TEXTURE_COORD%d TEXCOORD%d\n", _hoops_ASRR, _hoops_SRRR); ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define BACK_DIFFUSE_TEXTURE_COORD%d_OUT OUT_TEXCOORD%d\n", _hoops_ASRR, _hoops_GARR); ptr += _hoops_SSGR(ptr);

		// _hoops_HSRR _hoops_RH _hoops_SRS _hoops_ISRR _hoops_CSRR (_hoops_SSRR _hoops_GGAR _hoops_HH) _hoops_RGAR
		if (_hoops_ASRR == 0) {
			// _hoops_AGAR _hoops_HH _hoops_ISRR.
			sprintf (ptr, "#define BACK_DIFFUSE_TEXTURE_INTERPOLATOR0 TEXCOORD%d\n", _hoops_SRRR); ptr += _hoops_SSGR(ptr);
			sprintf (ptr, "#define BACK_DIFFUSE_TEXTURE_INTERPOLATOR0_OUT OUT_TEXCOORD%d\n", _hoops_GARR); ptr += _hoops_SSGR(ptr);
		}

		if (_hoops_ASRR > 0) {
			sprintf (ptr, "#define BACK_TEXTURE%d_WORLD %s\n", _hoops_ASRR, id._hoops_CRAR(_hoops_ASRR) ? "true" : "false"); ptr += _hoops_SSGR(ptr);
			sprintf (ptr, "#define BACK_TEXTURE%d_DECAL %s\n", _hoops_ASRR, id._hoops_SRAR(_hoops_ASRR) ? "true" : "false"); ptr += _hoops_SSGR(ptr);

			sprintf (ptr, "#define BACK_TEXTURE%d_COLOR %s\n", _hoops_ASRR, id._hoops_GAAR(_hoops_ASRR) ? "true" : "false"); ptr += _hoops_SSGR(ptr);
			sprintf (ptr, "#define BACK_TEXTURE%d_MODULATE %s\n", _hoops_ASRR, id._hoops_RAAR(_hoops_ASRR) ? "true" : "false"); ptr += _hoops_SSGR(ptr);
			sprintf (ptr, "#define BACK_TEXTURE%d_DROP %s\n", _hoops_ASRR, id._hoops_AAAR(_hoops_ASRR) ? "true" : "false");	ptr += _hoops_SSGR(ptr);
		}
		else {
			/* _hoops_GRAR 0 _hoops_HRGR _hoops_GIR _hoops_RRAR, _hoops_PPR _hoops_CCA _hoops_RII _hoops_ARAR _hoops_GAR _hoops_PRAR, _hoops_HIS _hoops_HRAR _hoops_GPP #_hoops_IHS */
			if (id._hoops_CRAR(0)) {
				sprintf (ptr, "#define BACK_TEXTURE%d_WORLD\n", _hoops_ASRR); ptr += _hoops_SSGR(ptr);
			}
			if (id._hoops_SRAR(0)) {
				sprintf (ptr, "#define BACK_TEXTURE%d_DECAL\n", _hoops_ASRR); ptr += _hoops_SSGR(ptr);
			}
			if (id._hoops_GAAR(0)) {
				sprintf (ptr, "#define BACK_TEXTURE%d_COLOR\n", _hoops_ASRR); ptr += _hoops_SSGR(ptr);
			}
			if (id._hoops_RAAR(0)) {
				sprintf (ptr, "#define BACK_TEXTURE%d_MODULATE\n", _hoops_ASRR); ptr += _hoops_SSGR(ptr);
			}
			if (id._hoops_AAAR(0)) {
				sprintf (ptr, "#define BACK_TEXTURE%d_DROP\n", _hoops_ASRR);
				ptr += _hoops_SSGR(ptr);
			}
		}

		sprintf (ptr, "#define BACK_DIFFUSE_TEXTURE%d_REGISTER s%d\n", _hoops_ASRR, _hoops_RARR);
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_PAAR()) {
		sprintf (ptr, "#define HAS_VERTEX_COLORS \n");
		ptr += _hoops_SSGR(ptr);
	}
	if (id._hoops_HAAR()) {
		sprintf (ptr, "#define HAS_VERTEX_RGBAS \n");
		ptr += _hoops_SSGR(ptr);
	}
	if (id._hoops_SCI()) {
		id._hoops_SII(_hoops_IAAR, _hoops_ASRR, &_hoops_SRRR, &_hoops_GARR, &_hoops_RARR);

		sprintf (ptr, "#define HAS_VERTEX_FINDICES \n");
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define FINDEX_COORD TEXCOORD%d\n", _hoops_SRRR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define FINDEX_COORD_OUT OUT_TEXCOORD%d\n", _hoops_GARR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define FINDEX_REGISTER s%d\n", _hoops_RARR);
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_GAC()) {
		id._hoops_SII(_hoops_CAAR, 0, &_hoops_SRRR, &_hoops_GARR, &_hoops_RARR);
		
		sprintf (ptr, "#define ENVIRONMENT_TEXTURE TEXCOORD%d\n", _hoops_SRRR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define ENVIRONMENT_TEXTURE_OUT OUT_TEXCOORD%d\n", _hoops_GARR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define ENVIRONMENT_TEXTURE_REGISTER s%d\n", _hoops_RARR);
		ptr += _hoops_SSGR(ptr);

		if (id._hoops_SAAR()) {
			sprintf (ptr, "#define HAS_PHYSICAL_REFLECTION\n");
			ptr += _hoops_SSGR(ptr);
		}

		if (id._hoops_GPAR()) {
			sprintf (ptr, "#define CUBE_ENVIRONMENT_MAP\n");
			ptr += _hoops_SSGR(ptr);
		}

		if (id._hoops_AAC()) {
			id._hoops_SII(_hoops_RPAR, 0, &_hoops_SRRR, &_hoops_GARR, &_hoops_RARR);
			
			sprintf (ptr, "#define MIRROR_TEXTURE TEXCOORD%d\n", _hoops_SRRR);
			ptr += _hoops_SSGR(ptr);
			sprintf (ptr, "#define MIRROR_TEXTURE_OUT OUT_TEXCOORD%d\n", _hoops_GARR);
			ptr += _hoops_SSGR(ptr);
			sprintf (ptr, "#define MIRROR_TEXTURE_REGISTER s%d\n", _hoops_RARR);
			ptr += _hoops_SSGR(ptr);
		}
	}
	if (id._hoops_ARC()) {
		id._hoops_SII(_hoops_APAR, 0, &_hoops_SRRR, &_hoops_GARR, &_hoops_RARR);
		
		sprintf (ptr, "#define BUMP_TEXTURE TEXCOORD%d\n", _hoops_SRRR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define BUMP_TEXTURE_OUT OUT_TEXCOORD%d\n", _hoops_GARR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define BUMP_TEXTURE_REGISTER s%d\n", _hoops_RARR);
		ptr += _hoops_SSGR(ptr);
	}
	if (id._hoops_GRC()) {
		id._hoops_SII(_hoops_PPAR, 0, &_hoops_SRRR, &_hoops_GARR, &_hoops_RARR);

		sprintf (ptr, "#define SPECULAR_TEXTURE TEXCOORD%d\n", _hoops_SRRR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define SPECULAR_TEXTURE_OUT OUT_TEXCOORD%d\n", _hoops_GARR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define SPECULAR_TEXTURE_REGISTER s%d\n", _hoops_RARR);
		ptr += _hoops_SSGR(ptr);
	}
	if (id._hoops_HRC()) {
		id._hoops_SII(_hoops_HPAR, 0, &_hoops_SRRR, &_hoops_GARR, &_hoops_RARR);

		sprintf (ptr, "#define TRANSMISSION_TEXTURE TEXCOORD%d\n", _hoops_SRRR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define TRANSMISSION_TEXTURE_OUT OUT_TEXCOORD%d\n", _hoops_GARR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define TRANSMISSION_TEXTURE_REGISTER s%d\n", _hoops_RARR);
		ptr += _hoops_SSGR(ptr);

		if (id._hoops_IPAR()) {
			sprintf (ptr, "#define TRANSMISSION_TEXTURE_MODULATE\n");
			ptr += _hoops_SSGR(ptr);
		}
	}
	if (id._hoops_CRC()) {
		id._hoops_SII(_hoops_CPAR, 0, &_hoops_SRRR, &_hoops_GARR, &_hoops_RARR);
		
		sprintf (ptr, "#define EMISSION_TEXTURE TEXCOORD%d\n", _hoops_SRRR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define EMISSION_TEXTURE_OUT OUT_TEXCOORD%d\n", _hoops_GARR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define EMISSION_TEXTURE_REGISTER s%d\n", _hoops_RARR);
		ptr += _hoops_SSGR(ptr);

		if (id._hoops_SPAR()) {
			sprintf (ptr, "#define EMISSION_TEXTURE_MODULATE\n");
			ptr += _hoops_SSGR(ptr);
		}
	}
	if (id._hoops_CRP()) {
		sprintf (ptr, "#define CREATE_SHADOW_MAP\n");
		ptr += _hoops_SSGR(ptr);

		// _hoops_HGI _hoops_CHR _hoops_GHAR _hoops_RHAR _hoops_AHAR _hoops_HSH.
		float const _hoops_PHAR = 0.0075f;
		float const _hoops_HHAR = 0.005f;

		sprintf (ptr, "#define SHADOW_MAP_BIAS %f\n", id._hoops_IHAR() ? _hoops_HHAR : _hoops_PHAR);
		ptr += _hoops_SSGR(ptr);
	}
	if (id._hoops_CHAR()) {
		sprintf (ptr, "#define SHADOW_MAP_RGBA\n");
		ptr += _hoops_SSGR(ptr);
	}

	if (!id._hoops_CRP()) {
		if (id._hoops_RPC() || id._hoops_APC()) {
			// _hoops_SHAR _hoops_HH _hoops_ISRR _hoops_IH _hoops_HCH _hoops_GIAR
			id._hoops_SII(_hoops_RIAR, 0, &_hoops_SRRR, &_hoops_GARR, &_hoops_RARR);

			sprintf (ptr, "#define DEPTH_PEELING_POSITION_COORD TEXCOORD%d\n", _hoops_SRRR);
			ptr += _hoops_SSGR(ptr);
			sprintf (ptr, "#define DEPTH_PEELING_POSITION_COORD_OUT OUT_TEXCOORD%d\n", _hoops_GARR);
			ptr += _hoops_SSGR(ptr);

			if (id._hoops_RPC()) {
				sprintf (ptr, "#define DEPTH_WRITING\n");
				ptr += _hoops_SSGR(ptr);
			}

			if (id._hoops_APC()) {
				sprintf (ptr, "#define DEPTH_PEELING\n");
				ptr += _hoops_SSGR(ptr);
				sprintf (ptr, "#define DEPTH_PEELING_TEXTURE_REGISTER s%d\n", _hoops_RARR);
				ptr += _hoops_SSGR(ptr);
			}

			if(id._hoops_AIAR()) {
				sprintf (ptr, "#define DEPTH_PEELING_MODE\n");
				ptr += _hoops_SSGR(ptr);
			}
		}
	}
	if (id._hoops_PIAR()) {
		sprintf (ptr, "#define DEPTH_TEXTURE_HARDWARE\n");
		ptr += _hoops_SSGR(ptr);
	}
	if (id._hoops_HIAR()) {
		sprintf (ptr, "#define DEPTH_PACKING_RGBA\n");
		ptr += _hoops_SSGR(ptr);
	}
	if (id._hoops_IIAR()) {
		sprintf (ptr, "#define DEPTH_WRITING_SINGLE_PASS\n");
		ptr += _hoops_SSGR(ptr);
	}
	if (id._hoops_CIAR()) {
		sprintf (ptr, "#define FRAME_BUFFER_EFFECTS\n");
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_IHAR()) {
		sprintf (ptr, "#define CAMERA_PERSPECTIVE\n");
		ptr += _hoops_SSGR(ptr);
	}
	if (id._hoops_SIAR()) {
		sprintf (ptr, "#define CREATE_SIMPLE_SHADOW\n");
		ptr += _hoops_SSGR(ptr);
	}
	if (id._hoops_PHC()) {
		sprintf (ptr, "#define CREATE_REFLECTION_PLANE\n");
		ptr += _hoops_SSGR(ptr);

		// _hoops_GCAR _hoops_RCAR _hoops_ACAR _hoops_GGR _hoops_CH
		sprintf (ptr, "#define SHADOW_MAP_COUNT 0\n");
		ptr += _hoops_SSGR(ptr);
	}
	else
	{
		sprintf (ptr, "#define SHADOW_MAP_COUNT %d\n", id._hoops_IRP());
		ptr += _hoops_SSGR(ptr);

		if (id._hoops_IRP()) {

			sprintf (ptr, "#define DISTANT_SHADOW_MAP_COUNT %d\n", id._hoops_PCAR());
			ptr += _hoops_SSGR(ptr);
			sprintf (ptr, "#define SPOT_SHADOW_MAP_COUNT %d\n", id._hoops_HCAR());
			ptr += _hoops_SSGR(ptr);

			sprintf (ptr, "#define SHADOW_MAP_SIZE %f\n", id._hoops_ICAR() * 1.0);
			ptr += _hoops_SSGR(ptr);
			if (id._hoops_IPC()) {
				// _hoops_CCAR _hoops_AAR _hoops_ACAR _hoops_SHR _hoops_SGH _hoops_HCR _hoops_RH _hoops_SCAR.
				sprintf (ptr, "#define SHADOW_MAP_SLICE_COUNT %d\n", _hoops_GSAR::_hoops_RSAR);
				ptr += _hoops_SSGR(ptr);
			}

			// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_PSAR _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_ISAR...
			if (id._hoops_CSAR() > 1)
			{
				const int _hoops_SSAR = id._hoops_CSAR();

				// _hoops_GGPR _hoops_GCA _hoops_RGR _hoops_IH _hoops_AGRR _hoops_RGPR _hoops_AGPR.
				ASSERT(_hoops_SSAR % 4 == 0);

				// _hoops_PGPR _hoops_HGPR _hoops_RH _hoops_PHI _hoops_IIGR _hoops_IGPR _hoops_CGPR _hoops_SCH'_hoops_GRI _hoops_RRI _hoops_HSAR 1. _hoops_SGPR _hoops_RGR _hoops_GGR _hoops_RH _hoops_CI _hoops_IS _hoops_GRPR
				// _hoops_ARAR _hoops_CR _hoops_SR _hoops_PAH'_hoops_RA _hoops_SGH #_hoops_RPP (_hoops_RRPR == 1)
				sprintf (ptr, "#define SHADOW_MAP_SAMPLES %d\n", _hoops_SSAR);
				ptr += _hoops_SSGR(ptr);
				sprintf (ptr, "#define SHADOW_MAP_SAMPLESF %f\n", (float)_hoops_SSAR);
				ptr += _hoops_SSGR(ptr);

				// _hoops_ARPR _hoops_RH _hoops_APR _hoops_PRPR _hoops_HRPR
				sprintf (ptr, "STATIC_ARRAY_BEGIN(pcf_taps, float4, SHADOW_MAP_SAMPLES/2)\n");
				ptr += _hoops_SSGR(ptr);

				// _hoops_ACGR _hoops_RH _hoops_IRPR _hoops_ISAR _hoops_CRPR.
				const float *_hoops_CAP = null;
				switch (_hoops_SSAR) {
					case 1:
						_hoops_CAP = _hoops_CGRR;
						break;
					case 4:
						_hoops_CAP = _hoops_SGRR;
						break;
					case 8:
						_hoops_CAP = _hoops_RRRR;
						break;
					case 12:
						// _hoops_SRPR _hoops_GAPR _hoops_APP - _hoops_HAR _hoops_RAPR _hoops_SIH
						_hoops_CAP = _hoops_ARRR;
						break;
					case 16:
						_hoops_CAP = _hoops_PRRR;
						break;
					default:
						HE_ERROR(HEC_DX9_DRIVER, HEC_DX9_DRIVER,
							"Invalid shadowmap sample count!");
				}

				// _hoops_CGP _hoops_IGPR _hoops_AAPR _hoops_PAPR, _hoops_HAPR _hoops_IAPR _hoops_CAPR _hoops_PPR _hoops_SAPR _hoops_RH _hoops_PIH.
				if (_hoops_CAP) {
					// _hoops_GPPR _hoops_ISAR _hoops_AII _hoops_RPPR _hoops_APPR _hoops_HSAR _hoops_IRS _hoops_PPPR _hoops_IS _hoops_HPPR _hoops_PPR _hoops_IPPR _hoops_CPPR _hoops_SPPR.
					float const s = 1.5f/id._hoops_ICAR();
					for (int i = 0; i < _hoops_SSAR/2; ++i) {
						sprintf (ptr, "    float4(%f, %f, %f, %f)",  s * _hoops_CAP[0], s * _hoops_CAP[1], s * _hoops_CAP[2], s * _hoops_CAP[3]);
						ptr += _hoops_SSGR(ptr);

						if (i < _hoops_SSAR/2 - 1) {
							sprintf (ptr, ",");
							ptr += _hoops_SSGR(ptr);
						}
						sprintf (ptr, "\n");
						ptr += _hoops_SSGR(ptr);

						// _hoops_CPR _hoops_RIS
						_hoops_CAP += 4;
					}
				}
				sprintf (ptr, "STATIC_ARRAY_END;\n");
				ptr += _hoops_SSGR(ptr);
			}

			int _hoops_PGR;
			for (_hoops_PGR = 0; _hoops_PGR < id._hoops_IRP(); _hoops_PGR++) {
				id._hoops_SII(_hoops_GHPR, _hoops_PGR, &_hoops_SRRR, &_hoops_GARR, &_hoops_RARR);

				sprintf (ptr, "#define SHADOW_MAP_COORD%d TEXCOORD%d\n", _hoops_PGR, _hoops_SRRR);
				ptr += _hoops_SSGR(ptr);
				sprintf (ptr, "#define SHADOW_MAP_COORD%d_OUT OUT_TEXCOORD%d\n", _hoops_PGR, _hoops_GARR);
				ptr += _hoops_SSGR(ptr);
				sprintf (ptr, "#define SHADOW_MAP_TEXTURE%d_REGISTER s%d\n", _hoops_PGR, _hoops_RARR);
				ptr += _hoops_SSGR(ptr);

				if (id._hoops_RHPR(_hoops_PGR)) {
					sprintf (ptr, "#define SHADOW_MAP_%d_VIEW_DEPENDENT\n", _hoops_PGR);
					ptr += _hoops_SSGR(ptr);
				}
			}
			_hoops_PGR = 0;
			int _hoops_AHPR;
			for (_hoops_AHPR = 0; _hoops_AHPR < H3D_MAX_SHADOW_MAPS; _hoops_AHPR++) {
				if (_hoops_AHPR < id._hoops_PCAR()) {
					sprintf (ptr, "#define DISTANT_SHADOW_MAP_TEXTURE%d ShadowMapTexture%d\n", _hoops_AHPR, _hoops_PGR);
					ptr += _hoops_SSGR(ptr);
					sprintf (ptr, "#define DISTANT_SHADOW_MAP_UV%d %d\n", _hoops_AHPR, _hoops_PGR);
					ptr += _hoops_SSGR(ptr);
					_hoops_PGR++;
				}
				else {
					sprintf (ptr, "#define DISTANT_SHADOW_MAP_TEXTURE%d ShadowMapTexture0\n", _hoops_AHPR);
					ptr += _hoops_SSGR(ptr);
					sprintf (ptr, "#define DISTANT_SHADOW_MAP_UV%d 0\n", _hoops_AHPR);
					ptr += _hoops_SSGR(ptr);
				}
			}
			int _hoops_PHPR;
			for (_hoops_PHPR = 0; _hoops_PHPR < H3D_MAX_SHADOW_MAPS; _hoops_PHPR++) {
				if (_hoops_PHPR < id._hoops_HCAR()) {
					sprintf (ptr, "#define SPOT_SHADOW_MAP_TEXTURE%d ShadowMapTexture%d\n", _hoops_PHPR, _hoops_PGR);
					ptr += _hoops_SSGR(ptr);
					sprintf (ptr, "#define SPOT_SHADOW_MAP_UV%d %d\n", _hoops_PHPR, _hoops_PGR);
					ptr += _hoops_SSGR(ptr);
					_hoops_PGR++;
				}
				else {
					sprintf (ptr, "#define SPOT_SHADOW_MAP_TEXTURE%d ShadowMapTexture0\n", _hoops_PHPR);
					ptr += _hoops_SSGR(ptr);
					sprintf (ptr, "#define SPOT_SHADOW_MAP_UV%d 0\n", _hoops_PHPR);
					ptr += _hoops_SSGR(ptr);
				}
			}
			if (id._hoops_HPC() || id._hoops_IPC())
			{
				// _hoops_PGPR _hoops_HHPR _hoops_GGR _hoops_IHPR _hoops_RI _hoops_CCH.
				if (id._hoops_HPC()) {
					sprintf(ptr, "#define SHADOW_MAP_JITTER\n");
					ptr += _hoops_SSGR(ptr);
				}

				// _hoops_CHPR _hoops_SHPR-_hoops_GC _hoops_PCRR _hoops_GGR _hoops_GIPR _hoops_RI _hoops_PPR _hoops_RAR-_hoops_AAR _hoops_CCH
				id._hoops_SII(_hoops_RIPR, 0, &_hoops_SRRR, &_hoops_GARR, &_hoops_RARR);

				sprintf(ptr, "#define SHADOW_MAP_JITTER_COORD TEXCOORD%d\n", _hoops_SRRR);
				ptr += _hoops_SSGR(ptr);
				sprintf(ptr, "#define SHADOW_MAP_JITTER_COORD_OUT OUT_TEXCOORD%d\n", _hoops_GARR);
				ptr += _hoops_SSGR(ptr);
				sprintf(ptr, "#define SHADOW_MAP_JITTER_REGISTER s%d\n", _hoops_RARR);
				ptr += _hoops_SSGR(ptr);
			}
		}
	}

	sprintf (ptr, "#define CUTTING_PLANE_COUNT %d\n", id._hoops_IAC());
	ptr += _hoops_SSGR(ptr);
	int _hoops_AIPR = 0;
	for (_hoops_AIPR = 0; _hoops_AIPR < id._hoops_IAC(); _hoops_AIPR++) {
		id._hoops_SII(_hoops_PIPR, _hoops_AIPR, &_hoops_SRRR, &_hoops_GARR, null);
		
		sprintf (ptr, "#define CUTTING_PLANE_COORD%d TEXCOORD%d\n", _hoops_AIPR/4, _hoops_SRRR);
		ptr += _hoops_SSGR(ptr);
		sprintf (ptr, "#define CUTTING_PLANE_COORD%d_OUT OUT_TEXCOORD%d\n", _hoops_AIPR/4, _hoops_GARR);
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_RPH())
	{
		sprintf (ptr, "#define PER_PIXEL_LIGHTING\n");
		ptr += _hoops_SSGR(ptr);
	}

	// _hoops_HIPR _hoops_IIPR _hoops_HH _hoops_ISRR _hoops_IGI _hoops_IH _hoops_RHC _hoops_AHC, _hoops_RPP _hoops_SR _hoops_RRP _hoops_SCH.
	id._hoops_SII(_hoops_CIPR, 0, null, &_hoops_GARR, null);
	if (_hoops_GARR != -1) {
		sprintf(ptr, "#define EYE_POSITION_COORD TEXCOORD\n");
		ptr += _hoops_SSGR(ptr);
		sprintf(ptr, "#define EYE_POSITION_COORD_OUT OUT_TEXCOORD%d\n", _hoops_GARR);
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_RIC())
	{
		sprintf (ptr, "#define GOOCH\n");
		ptr += _hoops_SSGR(ptr);

		// _hoops_SIPR _hoops_IRS _hoops_HH _hoops_CSRR _hoops_IH _hoops_RGR _hoops_HIS _hoops_SR _hoops_PAH _hoops_HGPR _hoops_RH _hoops_GCPR.
		id._hoops_SII(_hoops_RCPR, 0, null, null, &_hoops_RARR);
		sprintf(ptr, "#define GOOCH_TEXTURE_REGISTER s%d\n", _hoops_RARR);
		ptr += _hoops_SSGR(ptr);
	}
	if (id._hoops_PIC())
	{
		sprintf (ptr, "#define PRIORITY_HSRA\n");
		ptr += _hoops_SSGR(ptr);

		id._hoops_SII(_hoops_ACPR, 0, &_hoops_SRRR, null, null);
		sprintf (ptr, "#define PRIORITY_HSRA_COORD TEXCOORD%d\n", _hoops_SRRR);
		ptr += _hoops_SSGR(ptr);
	}
	if (id._hoops_PCPR()) 
	{
		sprintf (ptr, "#define AMBIENT_MATERIAL\n");
		ptr += _hoops_SSGR(ptr);
	}

	if (id._hoops_HCPR())
	{
		sprintf (ptr, "#define FORCE_GRAYSCALE\n");
		ptr += _hoops_SSGR(ptr);
	}

	*ptr++ = '\n';
	*ptr++ = '\n';

	if (ptr > end) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
			Sprintf_S (null, "shader scratch space overrun detected in dx9:\n%S", ptr));
	}
	return ptr;
}


char alter *H3DShader::_hoops_AIGR(
	   const char *filename,
	   const char *_hoops_ICPR,
	   char alter *ptr,
	   char const *end)
{
	FILE *fp;

	if (_hoops_ISS->_hoops_RP) {
		char full_path[4096];
		const char * _hoops_CCPR = null;
		_hoops_CCPR = _hoops_SCPR();

		if(_hoops_CCPR) {
			//_hoops_GSPR *_hoops_RSPR = _hoops_ASPR;
			strcpy(full_path, _hoops_CCPR);
			if (full_path[_hoops_SSGR(full_path)-1] != '\\')
				strcat(full_path, "\\");
			strcat(full_path, filename);
			fp = fopen (full_path, "r");
			if (!fp) {
				strcpy (ptr, _hoops_ICPR);
				ptr += _hoops_SSGR(_hoops_ICPR);

				HE_WARNING (HEC_DRIVER, HEC_DRIVER,
					Sprintf_S(null,
						"Debug shader \"%s\" not found. Debug shaders disabled.",
						full_path));
				_hoops_ISS->_hoops_RP = false;

				return ptr;
			}
			ptr += fread (ptr, 1, end - ptr, fp);
			*ptr = '\0';
			fclose(fp);
			//_hoops_PSPR _hoops_RH _hoops_HSPR _hoops_IS _hoops_ISPR _hoops_IH _hoops_IRS _hoops_CSPR _hoops_SSPR._hoops_GGHR _hoops_RGHR
			//_hoops_AGHR (!_hoops_PGHR (_hoops_HGHR, _hoops_RSPR)); 
		}
		else {
			strcpy (ptr, _hoops_ICPR);
			ptr += _hoops_SSGR(_hoops_ICPR);
		}
	}
	else {
		strcpy (ptr, _hoops_ICPR);
		ptr += _hoops_SSGR(_hoops_ICPR);
	}
	return ptr;
}

char alter *H3DShader::_hoops_IGHR(
		const char *_hoops_CGHR,
		const char *_hoops_SGHR,
		char alter *_hoops_GRHR, 
		int _hoops_RRHR, 
		char const *_hoops_ARHR) 
{
	char *_hoops_PRHR;
	char *buffer;
	int _hoops_HRHR;
	int _hoops_IRHR = _hoops_SSGR(_hoops_CGHR);

	if (_hoops_GRHR + _hoops_IRHR + _hoops_RRHR + 1 > _hoops_ARHR)
		return null; //_hoops_CRHR _hoops_SRHR _hoops_GAHR

	if ((_hoops_PRHR = strstr (_hoops_GRHR, _hoops_SGHR)) == null)
		return null;
	if ((_hoops_PRHR = strstr (_hoops_PRHR, "\n")) == null)
		return null;
	_hoops_PRHR++;

	_hoops_HRHR = 1 + _hoops_GRHR + _hoops_RRHR - _hoops_PRHR;
	ALLOC_ARRAY_CACHED (buffer, _hoops_HRHR, char);
	_hoops_RAHR (_hoops_PRHR, _hoops_HRHR, buffer);
	_hoops_AAHR (_hoops_CGHR, _hoops_PRHR);
	_hoops_PRHR += _hoops_IRHR;
	_hoops_RAHR (buffer, _hoops_HRHR, _hoops_PRHR);
	FREE_ARRAY (buffer, _hoops_HRHR, char);

	return _hoops_GRHR + _hoops_IRHR + _hoops_RRHR;
}


void H3DShader::_hoops_PAHR(
	   H3DShaderID &id,
	   bool _hoops_HAHR,
	   char alter *full_path)
{
	full_path[0] = '\0';

	if (!_hoops_ISS->_hoops_RP)
		return;

	char *ptr;
	char const *_hoops_CCPR;
	int i=0, j=0;
	int _hoops_IAHR;

	_hoops_CCPR = _hoops_SCPR();
	if (!_hoops_CCPR) {
		return;
	}
	strcpy (full_path, _hoops_CCPR);
	strcat (full_path, "\\");
	strcat (full_path, _hoops_G);
	strcat (full_path, "\\");
	strcat (full_path, _hoops_CAHR());
	if (_hoops_HAHR)
		strcat (full_path, "_vs_dump_");
	else
		strcat (full_path, "_ps_dump_");

	//_hoops_RGR _hoops_HAPR _hoops_SAHR _hoops_GPHR _hoops_RH _hoops_RPHR _hoops_APHR _hoops_HAS _hoops_PPR _hoops_PPHR.  _hoops_RH _hoops_HPHR _hoops_IPHR _hoops_HRGR _hoops_CPHR _hoops_SPHR
	for (i = H3DShaderID_SIZE-1; i >= 0; i--) {
		if (id.GetData(i)) {
			//_hoops_GHHR _hoops_RH _hoops_HSPR _hoops_HAPR _hoops_CGPR _hoops_SR _hoops_RHHR _hoops_AHHR _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_PHHR _hoops_HHHR
			for (j = 28; j > 0; j -= 4) {
				if ((id.GetData(i) >> j) & 0xF)
					break;
			}
			break;
		}
	}
	ptr = full_path + _hoops_SSGR (full_path);
	while (i >= 0) {
		while (j >= 0) {
			_hoops_IAHR = (id.GetData(i) >> j) & 0xF;
			switch (_hoops_IAHR) {
				case 0: case 1: case 2: case 3: case 4:
				case 5: case 6: case 7: case 8: case 9:
					*ptr++ = '0' + _hoops_IAHR;
					break;
				case 0xA: case 0xB: case 0xC: case 0xD: case 0xE: case 0xF:
					*ptr++ = 'a' - 0xA + _hoops_IAHR;
					break;
			}
			j -= 4;
		}
		if (i != 0)
			*ptr++ = '_';

		i--;
		j = 28;
	}
	sprintf (ptr, ".%s.txt", _hoops_CAHR());
}

bool H3DShader::_hoops_IHHR (
		char const *filename,
		char const *_hoops_RAGR)
{
	UNREFERENCED(filename);
	UNREFERENCED(_hoops_RAGR);
#ifdef H3D_SHADER_DEBUG
	FILE *fp;

	// _hoops_GCRR _hoops_CHHR
	char *_hoops_SHHR = const_cast<char*>(strrchr(filename, '\\'));
	if (_hoops_SHHR)
	{
		*_hoops_SHHR = '\0';
		CreateDirectoryA(filename, NULL);
		*_hoops_SHHR = '\\';
	}

	fp = fopen (filename, "w");
	if (fp) {
		fwrite (_hoops_RAGR, 1, _hoops_SSGR(_hoops_RAGR), fp);
		fclose(fp);
	}
#endif
	return true;
}


void H3DShader::_hoops_GIHR(_hoops_ISC const *color)
{
	if (_hoops_PCC._hoops_RIHR())
		return;

	if (_hoops_AIHR (color, &_hoops_HSC, sizeof(_hoops_ISC)))
		return;
	RGBAS32 const *rgbas32;
	RGBA _hoops_PIHR;

	rgbas32 = (RGBAS32 const *)color;
	_hoops_PIHR = *rgbas32;
	_hoops_HIHR(H3D_PSConstant_Table, _hoops_IIHR,
		"MaterialColor", "diffuse", &_hoops_PIHR, 4);
	_hoops_HIHR(H3D_VSConstant_Table, _hoops_CIHR,
		"MaterialColor", "diffuse", &_hoops_PIHR, 4);
}

/* _hoops_SIHR _hoops_GIPR _hoops_RH _hoops_SS _hoops_PPR _hoops_GCHR */
void H3DShader::_hoops_RCHR(Net_Rendition const & nr,
							  _hoops_ACHR			type,
							  bool					_hoops_PCHR)
{
	if (_hoops_PCC._hoops_RIHR())
		return;

	H3DData alter *h3ddata = H3DD (nr->_hoops_SRA);
	_hoops_HHA matr;
	_hoops_PC _hoops_HC;
	_hoops_AS const *light;
	RGB _hoops_HCHR, _hoops_ICHR, _hoops_CCHR, _hoops_SCHR;
	bool _hoops_GSHR = false, _hoops_RSHR = false, _hoops_ASHR = false; //"_hoops_PSHR _hoops_HSHR" _hoops_SGI
	bool _hoops_ISHR = false;
	RGBA _hoops_CSHR;
	RGB _hoops_SSHR(0);
	Driver_Color const * color = null;
	int _hoops_RARR;

	_hoops_GGIR(_hoops_PCHR);

	switch (type) {
		case T_FACES:
			if (_hoops_PCHR) {
				matr = nr->_hoops_IHA->_hoops_GIA;
				color = &nr->_hoops_IHA->_hoops_RGIR;
			}
			else {
				matr = nr->_hoops_IHA->_hoops_CHA;
				color = &nr->_hoops_IHA->color;
			}
			_hoops_HC = nr->_hoops_IHA->_hoops_AGP;
			_hoops_ISHR = BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES);
			break;
		case _hoops_GPA:
		case T_EDGES:
			matr = nr->_hoops_RHP->_hoops_CHA;
			_hoops_HC = nr->_hoops_RHP->_hoops_AGP;
			if (type == _hoops_GPA)
				_hoops_ISHR = nr->_hoops_ARA->_hoops_ACP._hoops_PCP;
			else
				_hoops_ISHR = BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES);
			color = &nr->_hoops_RHP->color;
			break;
		case T_LINES:
			matr = nr->_hoops_AHP->_hoops_CHA;
			_hoops_HC = nr->_hoops_AHP->_hoops_AGP;
			_hoops_ISHR = false;
			color = &nr->_hoops_AHP->color;
			break;
		case T_MARKERS:
			matr = nr->_hoops_GSP->_hoops_CHA;
			_hoops_HC = nr->_hoops_GSP->_hoops_AGP;
			_hoops_ISHR = false;
			color = &nr->_hoops_GSP->color;
			break;
		case T_VERTICES:
			matr = nr->_hoops_SCP->_hoops_CHA;
			_hoops_HC = nr->_hoops_SCP->_hoops_AGP;
			_hoops_ISHR = BIT (nr->_hoops_RGP, T_LIGHTS_FOR_MARKERS);
			color = &nr->_hoops_SCP->color;
			break;
		default:
			HE_ERROR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				"Invalid geometry type for EnsureLights.");
	}

	// _hoops_GGR _hoops_RH _hoops_AGIR _hoops_IIGR _hoops_PGIR _hoops_PIH, _hoops_RRP _hoops_IS _hoops_RIH _hoops_GGR _hoops_HGIR _hoops_IGIR
	if (_hoops_PCC._hoops_SCI())
		_hoops_CGIR(H3D_VSConstant_Table, _hoops_SGIR,
			null, "ColormapSize", (float) h3ddata->_hoops_CSC->_hoops_GRIR);

	_hoops_RRIR(h3ddata, nr, _hoops_PCC._hoops_AHRR());

	if (!matr->_hoops_ARIR && !_hoops_PCC._hoops_SCI()) {
		if (!BIT (nr->transform_rendition->flags, _hoops_PRIR) ||
			!_hoops_ISHR) {
			_hoops_ISC _hoops_PIHR;
			if (color)
				_hoops_PIHR = color->_hoops_HRIR;
			else {
				_hoops_PIHR.r = 0;
				_hoops_PIHR.g = 0;
				_hoops_PIHR.b = 0;
			}
			_hoops_PIHR.a = (char) (matr->_hoops_IRIR * 255.0f);
			_hoops_GIHR(&_hoops_PIHR);
			return;
		}
	}

	_hoops_RSHR = (_hoops_HC && _hoops_SCC == _hoops_HC->_hoops_CPA);
	_hoops_GSHR = (_hoops_GSC == matr->_hoops_CPA);
	_hoops_ASHR = (_hoops_RSC == nr->_hoops_IRR->_hoops_CPA);

	if (!_hoops_ASHR) {
		_hoops_RSC = nr->_hoops_IRR->_hoops_CPA;

		if (_hoops_PCC._hoops_AHRR()) {
			float hither, yon;

			if (nr->transform_rendition->_hoops_SPH->projection == _hoops_GHH) {
				hither = nr->_hoops_CPP->_hoops_CRIR.hither;
				yon =  nr->_hoops_CPP->_hoops_CRIR.yon;
			}
			else {
				hither =  nr->_hoops_CPP->_hoops_CRIR.hither - nr->transform_rendition->_hoops_SPH->_hoops_SRIR;
				yon = nr->_hoops_CPP->_hoops_CRIR.yon - nr->transform_rendition->_hoops_SPH->_hoops_SRIR;
			}

			_hoops_CGIR(H3D_VSConstant_Table, _hoops_GAIR,
				"AtmosphericAttenuation", "hither", hither);
			_hoops_CGIR(H3D_VSConstant_Table, _hoops_RAIR,
				"AtmosphericAttenuation", "yon", yon);

			// _hoops_HSRR _hoops_CI _hoops_SARR 3, _hoops_SR _hoops_RRP _hoops_IS _hoops_AAIR _hoops_RH _hoops_PAIR _hoops_HAIR _hoops_CR _hoops_SR _hoops_IAIR _hoops_RH _hoops_PAIR _hoops_CAIR.
			if (_hoops_HCC) {
				float rgb[3] =
				{
					nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.r / 255.0,
					nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.g / 255.0,
					nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.b / 255.0,
				};
				_hoops_HIHR(H3D_PSConstant_Table, _hoops_RPIR,
					null, "AtmosphericAttenuationColor", rgb, 3);
			}
		}
	}


	if (!_hoops_GSHR)
	{
		_hoops_GSC = matr->_hoops_CPA;

		/* _hoops_RAP _hoops_APIR _hoops_PIH */
		_hoops_HIR *_hoops_PGC = matr->_hoops_SCA;
		int i = 0;

		do {
			char handle[1024];

			if (_hoops_PGC) {

				_hoops_GRA const &	_hoops_RRA = nr->_hoops_ARA;
				_hoops_SSHR.red = _hoops_RRA->image._hoops_HRA.red;
				_hoops_SSHR.green = _hoops_RRA->image._hoops_HRA.green;
				_hoops_SSHR.blue = _hoops_RRA->image._hoops_HRA.blue;

				if (BIT (_hoops_PGC->flags, _hoops_PRA)) {
					if (BIT (_hoops_PGC->flags, _hoops_PPIR)) {
						_hoops_SSHR.red *= matr->_hoops_CSHR.red;
						_hoops_SSHR.green *= matr->_hoops_CSHR.green;
						_hoops_SSHR.blue *= matr->_hoops_CSHR.blue;
					}
					else {
						_hoops_SSHR.red *= _hoops_PGC->texture->_hoops_HPIR._hoops_IPIR.red;
						_hoops_SSHR.green *= _hoops_PGC->texture->_hoops_HPIR._hoops_IPIR.green;
						_hoops_SSHR.blue *= _hoops_PGC->texture->_hoops_HPIR._hoops_IPIR.blue;
					}
				}

				if (BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI))
					_hoops_SSHR = RGB (_hoops_SSHR._hoops_CPIR());
			}
			_hoops_CSHR = RGBA (matr->_hoops_CSHR, matr->_hoops_IRIR);

			// _hoops_PGPR _hoops_ARP _hoops_RH _hoops_SPIR._hoops_SPI _hoops_HAIR _hoops_RH _hoops_SRS _hoops_GHIR _hoops_RHIR
			if (i == 0) {
				_hoops_HIHR(H3D_PSConstant_Table, _hoops_IIHR,
					"MaterialColor", "diffuse", &_hoops_CSHR, 4);
				_hoops_HIHR(H3D_VSConstant_Table, _hoops_CIHR,
					"MaterialColor", "diffuse", &_hoops_CSHR, 4);
			}

			if (_hoops_PCC._hoops_HGC() > i) {
				if (_hoops_CSC[_hoops_AHIR + i] == _hoops_GGS)
					sprintf(handle, "ModulationColor%d", i);
				_hoops_HIHR(H3D_PSConstant_Table, _hoops_AHIR + i,
					null, handle, &_hoops_SSHR, 3);
			}

			i++;
			if (_hoops_PGC == null)
				break;
		} while ((_hoops_PGC = _hoops_PGC->next) != null);

		// _hoops_PHIR _hoops_GGR _hoops_APIR _hoops_PIH
		float _hoops_SGC[4];

		// _hoops_CSH _hoops_HHIR (_hoops_IHIR _hoops_CHIR) _hoops_HPP _hoops_SHIR
		_hoops_SGC[0] = 1.0f;
		_hoops_SGC[1] = 1.0f;
		_hoops_SGC[2] = 1.0f;

		// _hoops_GIIR _hoops_RIIR _hoops_GGR _hoops_AIIR
		_hoops_SGC[3] = 4.0f * matr->gloss;

		_hoops_PIIR(H3D_VSConstant_Table, _hoops_HIIR,
			"MaterialColor", "specular", _hoops_SGC, 4);
		_hoops_PIIR(H3D_PSConstant_Table, _hoops_IIIR,
			"MaterialColor", "specular", _hoops_SGC, 4);

		// _hoops_HHH _hoops_AIR _hoops_CI _hoops_A
		if (_hoops_PCC._hoops_GAC()) {
			_hoops_PIIR(H3D_PSConstant_Table, _hoops_CIIR,
				null, "Mirror", &matr->color[_hoops_ACA].red, 3);
		}
	}

	// _hoops_SIIR _hoops_GRH _hoops_RCA _hoops_AGI
	if (_hoops_PCC._hoops_RIC()) {
		_hoops_GCIR _hoops_RCIR = nr->_hoops_CPP;
		float const _hoops_ACIR = 1.0f / (h3ddata->_hoops_CSC->_hoops_GRIR);
		float _hoops_PCIR = _hoops_RCIR->_hoops_GIC._hoops_HCIR[0];
		float _hoops_ICIR = _hoops_RCIR->_hoops_GIC._hoops_HCIR[1];
		if (_hoops_PCIR == 0.0f && _hoops_ICIR == 0.0f) {
			// _hoops_CGP _hoops_RH _hoops_HAIR _hoops_CCIR _hoops_HRGR _hoops_GRGR _hoops_SCH _hoops_GRS _hoops_SCIR [0, 0]. _hoops_GSIR _hoops_IS _hoops_RSIR _hoops_CCIR.
			if(nr->_hoops_ASIR->_hoops_PSIR->_hoops_HSIR > 0)
				_hoops_ICIR = static_cast<float>(nr->_hoops_ASIR->_hoops_PSIR->_hoops_ISIR->length-1);
			else
				_hoops_ICIR = static_cast<float>(nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR->length-1);
		}

		float weights[4] = {
			// _hoops_SSIR-_hoops_GGCR _hoops_RGCR _hoops_HPP _hoops_AGCR _hoops_PGCR _hoops_IS _hoops_HGCR _hoops_IGCR _hoops_HGIR _hoops_ISRR.
			(_hoops_ICIR - _hoops_PCIR) * _hoops_ACIR,
			(_hoops_PCIR + 0.5f) * _hoops_ACIR,
			// _hoops_CGCR _hoops_SPI _hoops_SGCR
			_hoops_RCIR->_hoops_GIC._hoops_GRCR,
			// _hoops_SRPR _hoops_IGI.
			0.0f,
		};
		_hoops_HIHR(H3D_PSConstant_Table, _hoops_RRCR,
			null, "GoochWeights", weights, 4);
	}

	// _hoops_RAP _hoops_RCAR _hoops_ARCR _hoops_PRCR _hoops_A
	if (_hoops_HC && !_hoops_PCC._hoops_CRP()) {
		int _hoops_PGR = 0;
		char handle[1024];

		// _hoops_PS _hoops_HS _hoops_IS _hoops_CS _hoops_SS _hoops_IS _hoops_RH _hoops_CI _hoops_GGR _hoops_RGR _hoops_AGR
		for (int i = 0; i < (int) _hoops_HGR(_hoops_P); ++i)
		{
			light = _hoops_HC->_hoops_CGR;
			while (light) {
				// _hoops_AHH: _hoops_HRCR _hoops_SR _hoops_RGAR _hoops_GGCR _hoops_HPR _hoops_RH _hoops_CI _hoops_HRGR _hoops_IRCR _hoops_IS _hoops_CRCR _hoops_AIH _hoops_RCC::_hoops_SRCR.
				if (light->_hoops_PRR == _hoops_P[i] &&
					light->_hoops_HRR &&
					_hoops_PGR < _hoops_PCC._hoops_IRP()) {

					_hoops_GACR *dl;
					H3D_Display_List *odl;
					bool _hoops_RACR;
					_hoops_GSAR alter *_hoops_HRR = (_hoops_GSAR alter *) light->_hoops_HRR;

					_hoops_RACR = _hoops_AACR(nr, &_hoops_HRR->_hoops_PACR, &dl, &odl, H3D_DL_SHADOW_MAP);

					float _hoops_HACR[16];
					HI_Matmul_44_by_44 (h3ddata->_hoops_IACR, odl->item._hoops_HRR.transform, _hoops_HACR);

					if (_hoops_PCC._hoops_RHPR(_hoops_PGR)) {

						// _hoops_SIIR _hoops_CACR _hoops_A
						Vector _hoops_SACR[_hoops_GSAR::_hoops_RSAR];
						Vector _hoops_GPCR[_hoops_GSAR::_hoops_RSAR];
						int const _hoops_RPCR = _hoops_GSAR::_hoops_RSAR;
						for (int i = 0; i < _hoops_RPCR; ++i) {

							_hoops_GSAR::_hoops_APCR const & _hoops_PPCR = _hoops_HRR->_hoops_HPCR[i];

							// _hoops_GCAR _hoops_IPCR _hoops_SCAR
							if (!_hoops_PPCR._hoops_CPCR) {
								_hoops_SACR[i].z = 0.0f;
								_hoops_GPCR[i].z = -MAX_FLOAT;
							}
							else {
								// _hoops_GSIR _hoops_SPCR _hoops_PPR _hoops_GHCR
								_hoops_RHCR(h3ddata, _hoops_PPCR, i, h3ddata->_hoops_PI._hoops_HAP, _hoops_SACR[i], _hoops_GPCR[i]);

								// _hoops_GSIR _hoops_AHCR _hoops_CRGR _hoops_PHCR _hoops_GC
								_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
								float _hoops_CHCR = _hoops_IHCR->_hoops_CHCR;
								if (_hoops_CHCR < 1.0e-3f)
									_hoops_CHCR = 1.0e-3f;

								float _hoops_SHCR, _hoops_GICR;
								if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH) {
									_hoops_SHCR = _hoops_CHCR * _hoops_IHCR->_hoops_SPH->_hoops_SRIR - _hoops_IHCR->_hoops_SPH->_hoops_SRIR,
									_hoops_GICR = _hoops_IHCR->_hoops_SPH->_hoops_SRIR + (_hoops_IHCR->_hoops_SPH->_hoops_SRIR)*1000.0f - _hoops_IHCR->_hoops_SPH->_hoops_SRIR;

									const float s = _hoops_GICR/(_hoops_GICR - _hoops_SHCR);

									_hoops_SACR[i].z = (_hoops_PPCR._hoops_RICR - _hoops_SHCR) * s;
									_hoops_GPCR[i].z = (_hoops_PPCR._hoops_AICR - _hoops_SHCR) * s;
								} else {
									_hoops_SHCR = -_hoops_IHCR->_hoops_SPH->_hoops_SRIR / _hoops_CHCR;
									_hoops_GICR = +_hoops_IHCR->_hoops_SPH->_hoops_SRIR / _hoops_CHCR;
									_hoops_SACR[i].z = (_hoops_PPCR._hoops_RICR - _hoops_SHCR) / (_hoops_GICR-_hoops_SHCR);
									_hoops_GPCR[i].z = (_hoops_PPCR._hoops_AICR - _hoops_SHCR) / (_hoops_GICR-_hoops_SHCR);
								}
							}
						}

						// _hoops_RAP _hoops_CAPR _hoops_GIPR _hoops_GPP _hoops_RH _hoops_AIR _hoops_CI
						if (_hoops_CSC[_hoops_PICR + _hoops_PGR] == _hoops_GGS)
							sprintf(handle, "SliceScales%d", _hoops_PGR);
						_hoops_HICR(H3D_PSConstant_Table, _hoops_PICR + _hoops_PGR, null, handle, (float *) _hoops_SACR, _hoops_RPCR, 3);
						if (_hoops_CSC[_hoops_IICR + _hoops_PGR] == _hoops_GGS)
							sprintf(handle, "SliceBiases%d", _hoops_PGR);
						_hoops_HICR(H3D_PSConstant_Table, _hoops_IICR + _hoops_PGR, null, handle, (float *) _hoops_GPCR, _hoops_RPCR, 3);
					}
					else {
						// _hoops_CICR _hoops_SICR _hoops_GCCR _hoops_PCRR _hoops_IS _hoops_HH _hoops_PCRR.
						float const offset = 0.5f + 0.5f / h3ddata->_hoops_PI._hoops_HAP;
						float _hoops_RCCR[16] =
						{
							0.5f,	0.0f,   0.0f,   0.0f,
							0.0f,	(h3ddata->_hoops_ACCR * -0.5f),  0.0f,   0.0f,
							0.0f,   0.0f,   1.0f,	0.0f,
							offset, offset, 0.0f,   1.0f
						};

						HI_Matmul_44_by_44 (_hoops_HACR, _hoops_RCCR, _hoops_HACR);
					}

					if (_hoops_CSC[_hoops_PCCR + _hoops_PGR] == _hoops_GGS)
						sprintf(handle, "ShadowMaps[%d]", _hoops_PGR);
					_hoops_HCCR(H3D_VSConstant_Table, _hoops_PCCR + _hoops_PGR,
						handle, "transform", _hoops_HACR, 16);

					// _hoops_ACGR _hoops_RH _hoops_A _hoops_SR _hoops_RRP _hoops_IS _hoops_ARP
					_hoops_PCC._hoops_SII(_hoops_GHPR, _hoops_PGR, null, null, &_hoops_RARR);
					sprintf(handle, "ShadowMapTexture%d", _hoops_PGR);
					_hoops_ICCR(H3D_PSConstant_Table, _hoops_CCCR + _hoops_PGR, null, handle, _hoops_RARR);

					_hoops_SCCR(h3ddata, _hoops_RARR, odl->item._hoops_HRR.id);
					H3DTEXTUREFILTERTYPE filter = _hoops_PCC._hoops_PIAR() ? H3DTEXF_LINEAR : H3DTEXF_POINT;
					h3ddata->_hoops_GSCR->_hoops_RSCR(_hoops_RARR, filter, H3DTEXF_NONE, H3DTADDRESS_CLAMP);

					_hoops_PGR++;
				}
				light = light->next;
			}
		}

		// _hoops_CGP _hoops_SR _hoops_ASCR _hoops_GII _hoops_RCAR _hoops_ACAR _hoops_PSCR _hoops_HSCR _hoops_RI (_hoops_RPP _hoops_PPP)
		if (_hoops_PGR && _hoops_PCC._hoops_HPC())
		{
			// _hoops_ACGR _hoops_RH _hoops_A _hoops_SR _hoops_RRP _hoops_IS _hoops_ARP
			_hoops_PCC._hoops_SII(_hoops_RIPR, 0, null, null, &_hoops_RARR);
			_hoops_ICCR(H3D_PSConstant_Table, _hoops_CCCR + _hoops_PGR,
				null, "ShadowMapJitterSampler", _hoops_RARR);

			_hoops_SCCR(h3ddata, _hoops_RARR, h3ddata->_hoops_PI._hoops_HI);

			// _hoops_ISCR _hoops_RH _hoops_HH _hoops_IAPR _hoops_RH _hoops_CSCR
			h3ddata->_hoops_GSCR->_hoops_RSCR(_hoops_RARR, H3DTEXF_POINT, H3DTEXF_NONE, H3DTADDRESS_WRAP);
		}
	}

	if (!_hoops_HC || _hoops_RSHR && _hoops_GSHR)
		return;

	_hoops_SCC = _hoops_HC->_hoops_CPA;
	_hoops_GSC = matr->_hoops_CPA;

	/* _hoops_SSCR _hoops_GGSR _hoops_APIR _hoops_HAIR; _hoops_RGSR _hoops_SCH _hoops_IS _hoops_PGS _hoops_AGSR _hoops_PSP _hoops_PGSR */
	if (_hoops_PCC._hoops_PAAR() || _hoops_PCC._hoops_SCI() || _hoops_PCC._hoops_HGC() > 0)
		_hoops_HCHR.red = _hoops_HCHR.green = _hoops_HCHR.blue = 1.0f;
	else
		_hoops_HCHR = matr->_hoops_CSHR;

	_hoops_ICHR = matr->color[_hoops_HIA];
	_hoops_CCHR = matr->color[_hoops_HCA];
	_hoops_SCHR = matr->color[_hoops_PCA];

	/* _hoops_HGSR _hoops_GRR _hoops_RRR */
	Point _hoops_IGSR;
	Vector _hoops_CGSR;

	if ((light = _hoops_HC->_hoops_CGR) != null) {
		RGBA _hoops_SGSR;
		RGB _hoops_GRSR;
		float _hoops_RRSR[2];
		Vector _hoops_ARSR;
		int _hoops_PRSR = 0;
		int _hoops_HRSR = 0;
		int _hoops_IRSR = 0;

		/* _hoops_CRSR _hoops_SRSR _hoops_GASR _hoops_CGH _hoops_SR _hoops_ARP _hoops_RH _hoops_SS _hoops_GGR? */
		H3D_Constant_Table table = _hoops_PCC._hoops_RPH() ? H3D_PSConstant_Table : H3D_VSConstant_Table;

		/* _hoops_RASR _hoops_RH _hoops_AASR _hoops_RCA */
		RGB _hoops_PASR = nr->_hoops_IRR->_hoops_HASR;
		RGB _hoops_IASR = nr->_hoops_IRR->_hoops_CASR;
		RGB _hoops_SASR = _hoops_GPSR::_hoops_RPSR;

		do {
			if (light->_hoops_PRR == _hoops_C) {
				int point_count = _hoops_PCC._hoops_PPRR();		//_hoops_HGCR _hoops_APSR # _hoops_IIGR _hoops_PPSR _hoops_SS
				if (point_count == 0)
					continue;

				if (_hoops_CSC[_hoops_HPSR + _hoops_PRSR] == _hoops_GGS)
					sprintf(h3ddata->shader_handle, "PointLights[%d]", _hoops_PRSR);


				// _hoops_CHPR _hoops_GGR _hoops_RH _hoops_IPSR _hoops_CPSR
				HI_Compute_Transformed_Points(1, (Point *)&light->position.x,
												&h3ddata->_hoops_SPSR[0], &_hoops_IGSR);
				_hoops_HIHR(table, _hoops_HPSR + _hoops_PRSR,
					h3ddata->shader_handle, "position", &_hoops_IGSR, 3);

				// _hoops_CHPR _hoops_GGR _hoops_RH _hoops_IPSR _hoops_GHSR
				_hoops_SGSR.red = light->color.red;
				_hoops_SGSR.green = light->color.green;
				_hoops_SGSR.blue = light->color.blue;
				_hoops_SGSR.alpha = _hoops_SGSR._hoops_CPIR();
				_hoops_HIHR(table, _hoops_RHSR + _hoops_PRSR,
					h3ddata->shader_handle, "diffuse", &_hoops_SGSR, 4);

				// _hoops_CHPR _hoops_GGR _hoops_RH _hoops_IPSR _hoops_AHSR
				_hoops_GRSR.red = light->color.red * _hoops_ICHR.red;
				_hoops_GRSR.green = light->color.green * _hoops_ICHR.green;
				_hoops_GRSR.blue = light->color.blue * _hoops_ICHR.blue;
				_hoops_HIHR(table, _hoops_PHSR + _hoops_PRSR,
					h3ddata->shader_handle, "specular", &_hoops_GRSR, 3);

				// _hoops_HHSR _hoops_GGR _hoops_RH _hoops_RIR-_hoops_RRR _hoops_AASR _hoops_IHSR
				_hoops_PASR.red += light->_hoops_HASR.red;
				_hoops_PASR.green += light->_hoops_HASR.green;
				_hoops_PASR.blue += light->_hoops_HASR.blue;
				_hoops_IASR.red += light->_hoops_CASR.red;
				_hoops_IASR.green += light->_hoops_CASR.green;
				_hoops_IASR.blue += light->_hoops_CASR.blue;

				// _hoops_CHSR _hoops_GHI
				_hoops_SASR.red += _hoops_GRSR.red;
				_hoops_SASR.green += _hoops_GRSR.green;
				_hoops_SASR.blue += _hoops_GRSR.blue;

				_hoops_PRSR++;
			}
			else if (light->_hoops_PRR == _hoops_I) {
				int _hoops_SHSR = _hoops_PCC._hoops_HPRR();		//_hoops_HGCR _hoops_APSR # _hoops_IIGR _hoops_GISR _hoops_SS
				if (_hoops_SHSR == 0)
					continue;

				if (_hoops_CSC[_hoops_RISR + _hoops_IRSR] == _hoops_GGS)
					sprintf(h3ddata->shader_handle, "SpotLights[%d]", _hoops_IRSR);


				// _hoops_CHPR _hoops_GGR _hoops_RH _hoops_AISR _hoops_CPSR
				HI_Compute_Transformed_Points(1, (Point *)&light->position.x,
												&h3ddata->_hoops_SPSR[0], &_hoops_IGSR);
				_hoops_HIHR(table, _hoops_RISR + _hoops_IRSR,
					h3ddata->shader_handle, "position", &_hoops_IGSR, 3);

				// _hoops_CHPR _hoops_GGR _hoops_RH _hoops_AISR _hoops_PISR
				HI_Compute_Transformed_Vectors(1, (Vector *)&light->direction.x,
					&h3ddata->_hoops_SPSR[0], &_hoops_CGSR);
				_hoops_HIHR(table, _hoops_HISR + _hoops_IRSR,
					h3ddata->shader_handle, "direction", &_hoops_CGSR, 3);

				// _hoops_IISR _hoops_RH _hoops_AISR _hoops_CISR - _hoops_ARCR (_hoops_SISR - _hoops_HAS)/(_hoops_GCSR - _hoops_HAS) _hoops_CRGR _hoops_SISR * _hoops_IRS + _hoops_RCSR
				float _hoops_ACSR = cos(_hoops_PCSR(light->_hoops_ACSR));
				float _hoops_HCSR = cos(_hoops_PCSR(light->_hoops_HCSR));
				float delta = _hoops_ACSR - _hoops_HCSR;
				if (abs(delta) > 1e-6f) {
					_hoops_RRSR[0] = 1.0f / delta;
					_hoops_RRSR[1] = -_hoops_HCSR * _hoops_RRSR[0];
				}
				else {
					_hoops_RRSR[0] = 1;
					_hoops_RRSR[1] = 0;
				}
				_hoops_HIHR(table, _hoops_ICSR + _hoops_IRSR,
					h3ddata->shader_handle, "angles", _hoops_RRSR, 2);

				// _hoops_CHPR _hoops_GGR _hoops_RH _hoops_AISR _hoops_GHSR
				_hoops_SGSR.red = light->color.red;
				_hoops_SGSR.green = light->color.green;
				_hoops_SGSR.blue = light->color.blue;
				_hoops_SGSR.alpha = _hoops_SGSR._hoops_CPIR();
				_hoops_HIHR(table, _hoops_CCSR + _hoops_IRSR,
					h3ddata->shader_handle, "diffuse", &_hoops_SGSR, 4);

				// _hoops_CHPR _hoops_GGR _hoops_RH _hoops_AISR _hoops_AHSR
				_hoops_GRSR.red = light->color.red * _hoops_ICHR.red;
				_hoops_GRSR.green = light->color.green * _hoops_ICHR.green;
				_hoops_GRSR.blue = light->color.blue * _hoops_ICHR.blue;
				_hoops_HIHR(table, _hoops_SCSR + _hoops_IRSR,
					h3ddata->shader_handle, "specular", &_hoops_GRSR, 3);

				// _hoops_HHSR _hoops_GGR _hoops_RH _hoops_RIR-_hoops_RRR _hoops_AASR _hoops_IHSR
				_hoops_PASR.red += light->_hoops_HASR.red;
				_hoops_PASR.green += light->_hoops_HASR.green;
				_hoops_PASR.blue += light->_hoops_HASR.blue;
				_hoops_IASR.red += light->_hoops_CASR.red;
				_hoops_IASR.green += light->_hoops_CASR.green;
				_hoops_IASR.blue += light->_hoops_CASR.blue;

				// _hoops_CHSR _hoops_GHI
				_hoops_SASR.red += _hoops_GRSR.red;
				_hoops_SASR.green += _hoops_GRSR.green;
				_hoops_SASR.blue += _hoops_GRSR.blue;

				_hoops_IRSR++;
			}
			else { /* _hoops_GSSR _hoops_RSSR _hoops_RRR */
				int _hoops_ASSR = _hoops_PCC._hoops_APRR();		//_hoops_HGCR _hoops_APSR # _hoops_IIGR _hoops_RSSR _hoops_SS
				if (_hoops_ASSR == 0)
					continue;

				if (_hoops_CSC[_hoops_PSSR + _hoops_HRSR] == _hoops_GGS)
					sprintf(h3ddata->shader_handle, "DistantLights[%d]", _hoops_HRSR);

				// _hoops_CHPR _hoops_GGR _hoops_RH _hoops_RSSR _hoops_RRR _hoops_PISR
				HI_Compute_Transformed_Vectors(1, (Vector *)&light->direction.x,
					&h3ddata->_hoops_SPSR[0], &_hoops_CGSR);
				_hoops_HIHR(table, _hoops_PSSR + _hoops_HRSR,
					h3ddata->shader_handle, "direction", &_hoops_CGSR, 3);

				// _hoops_CHPR _hoops_GGR _hoops_RH _hoops_RSSR _hoops_RRR _hoops_GHSR

				_hoops_SGSR.red = light->color.red;
				_hoops_SGSR.green = light->color.green;
				_hoops_SGSR.blue = light->color.blue;
				_hoops_SGSR.alpha = _hoops_SGSR._hoops_CPIR();
				_hoops_HIHR(table, _hoops_HSSR + _hoops_HRSR,
					h3ddata->shader_handle, "diffuse", &_hoops_SGSR, 4);

				// _hoops_CHPR _hoops_GGR _hoops_RH _hoops_RSSR _hoops_RRR _hoops_AHSR
				_hoops_GRSR.red = light->color.red * _hoops_ICHR.red;
				_hoops_GRSR.green = light->color.green * _hoops_ICHR.green;
				_hoops_GRSR.blue = light->color.blue * _hoops_ICHR.blue;
				_hoops_HIHR(table, _hoops_ISSR + _hoops_HRSR,
					h3ddata->shader_handle, "specular", &_hoops_GRSR, 3);

				// _hoops_CHPR _hoops_GGR _hoops_RH _hoops_RSSR _hoops_RRR _hoops_CSSR _hoops_SSSR
				_hoops_ARSR.x = _hoops_CGSR.x;
				_hoops_ARSR.y = _hoops_CGSR.y;
				_hoops_ARSR.z = _hoops_CGSR.z - h3ddata->_hoops_ACCR;
				QUICK_NORMALIZE(_hoops_ARSR);
				_hoops_HIHR(table, _hoops_GGGA + _hoops_HRSR,
					h3ddata->shader_handle, "halfway", &_hoops_ARSR, 3);

				// _hoops_HHSR _hoops_GGR _hoops_RH _hoops_RIR-_hoops_RRR _hoops_AASR _hoops_IHSR
				_hoops_PASR.red += light->_hoops_HASR.red;
				_hoops_PASR.green += light->_hoops_HASR.green;
				_hoops_PASR.blue += light->_hoops_HASR.blue;
				_hoops_IASR.red += light->_hoops_CASR.red;
				_hoops_IASR.green += light->_hoops_CASR.green;
				_hoops_IASR.blue += light->_hoops_CASR.blue;

				// _hoops_CHSR _hoops_GHI
				_hoops_SASR.red += _hoops_GRSR.red;
				_hoops_SASR.green += _hoops_GRSR.green;
				_hoops_SASR.blue += _hoops_GRSR.blue;

				_hoops_HRSR++;
			}
		} _hoops_RGGA ((light = light->next) == null);

		/* _hoops_AGGA _hoops_SR _hoops_PAH _hoops_ARP _hoops_AASR _hoops_RRR _hoops_PGGA _hoops_SR _hoops_HS _hoops_HGGA _hoops_GGR _hoops_SS' _hoops_IGGA _hoops_AASR _hoops_HRP */

		// _hoops_CGGA _hoops_RRR _hoops_HRGR _hoops_SHR _hoops_SGGA _hoops_GGR _hoops_RH _hoops_AIR _hoops_CI, _hoops_HIS _hoops_SR _hoops_RIH _hoops_SGS _hoops_SRSR _hoops_GASR _hoops_GRGA.
		_hoops_HIHR(H3D_PSConstant_Table, _hoops_RRGA,
			null, "AmbientLightUp", &_hoops_PASR, 3);
		_hoops_HIHR(H3D_PSConstant_Table, _hoops_ARGA,
			null, "AmbientLightDown", &_hoops_IASR, 3);

		// _hoops_CHPR _hoops_GGR _hoops_RH _hoops_AASR _hoops_RRR _hoops_PISR
		Vector _hoops_PRGA;
		if (nr->_hoops_IRR->_hoops_HRGA == _hoops_IRGA::_hoops_CRGA)
			// _hoops_SRGA-_hoops_GC _hoops_GH
			_hoops_PRGA = Vector(0.0f, 1.0f, 0.0f);
		else {
			// _hoops_GAGA _hoops_RAGA _hoops_AAGA _hoops_IS _hoops_RHC _hoops_GC.
			HI_Compute_Transformed_Vectors(1, &nr->_hoops_IRR->_hoops_HRGA,
				&h3ddata->_hoops_SPSR[0], &_hoops_PRGA);
			HI_Normalize(&_hoops_PRGA);
		}

		// _hoops_PAGA _hoops_SGS _hoops_AASR _hoops_HAGA _hoops_IAGA _hoops_GGR _hoops_CAGA _hoops_PAR _hoops_SAGA _hoops_GPGA _hoops_GPP _hoops_RCA _hoops_CCH, _hoops_HIS _hoops_SR _hoops_RIH _hoops_GASR _hoops_ARI.
		_hoops_HIHR(table, _hoops_RPGA,
			null, "AmbientLightDir", &_hoops_PRGA, 3);

		// _hoops_CHPR _hoops_APGA _hoops_PPGA.
		_hoops_PIIR(H3D_PSConstant_Table, _hoops_HPGA,
			null, "EmissiveLight", (float *)&_hoops_CCHR, 3);

		if (_hoops_PCC._hoops_HRC()) {
			// _hoops_IPGA _hoops_HH _hoops_PGSR
			_hoops_PIIR(H3D_PSConstant_Table, _hoops_CPGA,
				null, "TransmissionModulateColor", (float *)&_hoops_SCHR, 3);
		}

		// _hoops_CGP _hoops_SR _hoops_SPGA'_hoops_RA _hoops_GHGA _hoops_RIR-_hoops_AIR _hoops_RCA, _hoops_RIH _hoops_IRS _hoops_GHI _hoops_RHGA _hoops_IS _hoops_RH _hoops_AIR _hoops_CI.
		if (!_hoops_PCC._hoops_RPH())
		{
			// _hoops_AHGA _hoops_APSR _hoops_IS _hoops_HGCR _hoops_IRS _hoops_PHGA _hoops_GHI _hoops_HAIR
			float _hoops_HHGA = _hoops_SASR._hoops_CPIR();
			if (_hoops_HHGA > 0) {
				float _hoops_IHGA = 1.0f / _hoops_HHGA;
				_hoops_SASR.red *= _hoops_IHGA;
				_hoops_SASR.green *= _hoops_IHGA;
				_hoops_SASR.blue *= _hoops_IHGA;
			}

			_hoops_HIHR(H3D_PSConstant_Table, _hoops_CHGA,
				null, "SpecularTint", &_hoops_SASR, 3);
		}
	}
}

void H3DShader::_hoops_SHGA(float *matrix)
{
	_hoops_HCCR(H3D_VSConstant_Table, _hoops_GIGA,
		null, "WorldViewProj", matrix, 16);
}

void H3DShader::_hoops_RIGA (Net_Rendition const & nr)
{
	if (_hoops_PCC._hoops_RIHR())
		return;

	H3DData alter *h3ddata = H3DD (nr->_hoops_SRA);

	if (_hoops_ICC == nr->transform_rendition->_hoops_CPA)
		return;
	_hoops_ICC = nr->transform_rendition->_hoops_CPA;
	float mat[16];
	_hoops_AIGA(h3ddata->_hoops_PIGA, 16, float, &mat[0]);
	if (_hoops_PCC._hoops_HIGA())
		mat[14] += h3ddata->_hoops_IIGA;

	if (_hoops_PCC._hoops_SAC()) {
		_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
		Display_Context const *		dc = nr->_hoops_SRA;
		float scale;
		float contrast_color[4];
		contrast_color[0] = _hoops_SIGA->contrast_color._hoops_HRIR.r / 255.0f;
		contrast_color[1] = _hoops_SIGA->contrast_color._hoops_HRIR.g / 255.0f;
		contrast_color[2] = _hoops_SIGA->contrast_color._hoops_HRIR.b / 255.0f;
		contrast_color[3] = _hoops_SIGA->contrast_color._hoops_HRIR.a / 255.0f;

		if (_hoops_PCC._hoops_ICRR())
			scale = 16.0f;
		else
			scale = 32.0f;

		_hoops_CGIR(H3D_VSConstant_Table, _hoops_GCGA, 0, "ScaledWindowWidth",
			(dc->_hoops_RCGA.right - dc->_hoops_RCGA.left+ 1) / scale);
		_hoops_CGIR(H3D_VSConstant_Table, _hoops_ACGA, 0, "ScaledWindowHeight",
			(dc->_hoops_RCGA.top - dc->_hoops_RCGA.bottom + 1) / scale);
		_hoops_HIHR(H3D_PSConstant_Table, _hoops_PCGA,
			0, "FaceContrastColor", (void *) contrast_color, 4);
	}

	if (_hoops_PCC._hoops_GSI()) {
		Display_Context const *dc = nr->_hoops_SRA;

		_hoops_CGIR(H3D_VSConstant_Table, _hoops_GCGA, 0, "WindowWidth",
			(dc->_hoops_RCGA.right - dc->_hoops_RCGA.left+ 1));
		_hoops_CGIR(H3D_VSConstant_Table, _hoops_ACGA, 0, "WindowHeight",
			(dc->_hoops_RCGA.top - dc->_hoops_RCGA.bottom + 1));
	}

	_hoops_HCCR(H3D_VSConstant_Table, _hoops_GIGA,
		null, "WorldViewProj", &mat, 16);

	if (_hoops_PCC._hoops_RPC() && !_hoops_PCC._hoops_APC()) {
		// _hoops_HCGA
		_hoops_CGIR(H3D_PSConstant_Table, _hoops_ICGA, null, "DepthWriteScale", 1.0f);
	}
};



void H3DShader::_hoops_CCGA (H3DData const *	h3ddata)
{
	//_hoops_RIH _hoops_GGR _hoops_IRS _hoops_SCGA _hoops_GSGA _hoops_RSGA (_hoops_IH _hoops_SGH _hoops_CCA _hoops_ASGA)
	float _hoops_PSGA[9];
	float *_hoops_HSGA;
	float const *matrix = h3ddata->_hoops_ISGA;
	int i;

	//_hoops_CSGA _hoops_RH _hoops_SSGA _hoops_GGRA
	_hoops_PSGA[0] = matrix[5] * matrix[10] - matrix[6] * matrix[9];
	_hoops_PSGA[1] = matrix[6] * matrix[8] - matrix[4] * matrix[10];
	_hoops_PSGA[2] = matrix[4] * matrix[9] - matrix[5] * matrix[8];
	_hoops_PSGA[3] = matrix[9] * matrix[2] - matrix[10] * matrix[1];
	_hoops_PSGA[4] = matrix[10] * matrix[0] - matrix[8] * matrix[2];
	_hoops_PSGA[5] = matrix[8] * matrix[1] - matrix[9] * matrix[0];
	_hoops_PSGA[6] = matrix[1] * matrix[6] - matrix[2] * matrix[5];
	_hoops_PSGA[7] = matrix[2] * matrix[4] - matrix[0] * matrix[6];
	_hoops_PSGA[8] = matrix[0] * matrix[5] - matrix[1] * matrix[4];

	_hoops_HSGA = _hoops_PSGA;
	float _hoops_RGRA = (float) sqrt(_hoops_HSGA[0]*_hoops_HSGA[0]+_hoops_HSGA[1]*_hoops_HSGA[1]+_hoops_HSGA[2]*_hoops_HSGA[2]);
	if (_hoops_RGRA > 0)
		for (i = 0; i < 9; i++)
			_hoops_HSGA[i] /= _hoops_RGRA;

	_hoops_HCCR (H3D_VSConstant_Table, _hoops_AGRA,
		null, "NormalizedModelView3x3", _hoops_PSGA, 9);

	if (_hoops_PCC._hoops_HGC() > 0)
		_hoops_HCCR (H3D_VSConstant_Table, _hoops_PGRA,
			null, "Model", h3ddata->_hoops_IACR, 16);

	_hoops_HCCR (H3D_VSConstant_Table, _hoops_HGRA,
		null, "ModelView", h3ddata->_hoops_ISGA, 16);

}

void H3DShader::_hoops_IGRA (Net_Rendition const & nr)
{
	if (_hoops_PCC._hoops_RIHR())
		return;

	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	Display_Context const *		dc = nr->_hoops_SRA;
	H3DData alter *				h3ddata = H3DD (nr->_hoops_SRA);
	int							i = 0;
	float						projection[16];
	int							_hoops_GRRA;

	for (i = 0; i < _hoops_PCC._hoops_HGC(); i++) {
		_hoops_PCC._hoops_SII(_hoops_PSRR, i, null, null, &_hoops_GRRA);
		if (h3ddata->_hoops_RRRA[_hoops_GRRA]) {
			sprintf(h3ddata->shader_handle, "TextureMatrix%d", i);
			_hoops_HCCR (H3D_VSConstant_Table, _hoops_ARRA + i,
				null, h3ddata->shader_handle, &h3ddata->_hoops_PRRA[_hoops_GRRA], 16);

			h3ddata->_hoops_RRRA[_hoops_GRRA] = false;
		}
	}

	for (i = 0; i <  _hoops_PCC._hoops_CGC(); i++) {
		_hoops_PCC._hoops_SII(_hoops_IRAR, i, null, null, &_hoops_GRRA);
		if (h3ddata->_hoops_RRRA[_hoops_GRRA]) {
			sprintf(h3ddata->shader_handle, "TextureMatrix%d", i);
			_hoops_HCCR (H3D_VSConstant_Table, _hoops_ARRA + i,
				null, h3ddata->shader_handle, &h3ddata->_hoops_PRRA[_hoops_GRRA], 16);

			h3ddata->_hoops_RRRA[_hoops_GRRA] = false;
		}
	}

	if (_hoops_PCC._hoops_SCI()) {
		_hoops_PCC._hoops_SII(_hoops_IAAR, 0, null, null, &_hoops_GRRA);
		_hoops_HCCR (H3D_VSConstant_Table, _hoops_HRRA,
			null, "IndexTextureMatrix", &h3ddata->_hoops_PRRA[_hoops_GRRA], 16);
	}

	if (_hoops_PCC._hoops_ARC()) {
		_hoops_PCC._hoops_SII(_hoops_APAR, 0, null, null, &_hoops_GRRA);
		_hoops_HCCR (H3D_VSConstant_Table, _hoops_IRRA,
			null, "BumpTextureMatrix", &h3ddata->_hoops_PRRA[_hoops_GRRA], 16);
	}

	if (_hoops_PCC._hoops_GRC()) {
		_hoops_PCC._hoops_SII(_hoops_PPAR, 0, null, null, &_hoops_GRRA);
		_hoops_HCCR (H3D_VSConstant_Table, _hoops_CRRA,
			null, "SpecularTextureMatrix", &h3ddata->_hoops_PRRA[_hoops_GRRA], 16);
	}

	if (_hoops_PCC._hoops_HRC()) {
		_hoops_PCC._hoops_SII(_hoops_HPAR, 0, null, null, &_hoops_GRRA);
		_hoops_HCCR (H3D_VSConstant_Table, _hoops_SRRA,
			null, "TransmissionTextureMatrix", &h3ddata->_hoops_PRRA[_hoops_GRRA], 16);
	}

	if (_hoops_PCC._hoops_CRC()) {
		_hoops_PCC._hoops_SII(_hoops_CPAR, 0, null, null, &_hoops_GRRA);
		_hoops_HCCR (H3D_VSConstant_Table, _hoops_GARA,
			null, "EmissionTextureMatrix", &h3ddata->_hoops_PRRA[_hoops_GRRA], 16);
	}

	if (_hoops_PCC._hoops_AAC()) {
		_hoops_PCC._hoops_SII(_hoops_RPAR, 0, null, null, &_hoops_GRRA);
		_hoops_HCCR (H3D_VSConstant_Table, _hoops_RARA,
			null, "MirrorTextureMatrix", &h3ddata->_hoops_PRRA[_hoops_GRRA], 16);
	}

	if (_hoops_PCC._hoops_GAC()) {
		_hoops_PCC._hoops_SII(_hoops_CAAR, 0, null, null, &_hoops_GRRA);
		_hoops_HCCR (H3D_VSConstant_Table, _hoops_AARA,
			null, "EnvironmentTextureMatrix", &h3ddata->_hoops_PRRA[_hoops_GRRA], 16);
	}


	if (_hoops_ICC == _hoops_IHCR->_hoops_CPA)
		return;
	_hoops_ICC = _hoops_IHCR->_hoops_CPA;

	_hoops_AIGA(h3ddata->_hoops_PARA, 16, float, projection);
	if (_hoops_PCC._hoops_HIGA())
		projection[14] += h3ddata->_hoops_HARA;
	_hoops_HCCR (H3D_VSConstant_Table, _hoops_IARA,
		null, "Projection", &projection, 16);

	this->_hoops_CCGA (h3ddata);

	//_hoops_RIH _hoops_GGR _hoops_RH _hoops_CARA-_hoops_GC _hoops_SARA _hoops_AHC; _hoops_IGI _hoops_IH _hoops_RHI _hoops_SIA
	if (_hoops_PCC._hoops_GAC())
	{
		Point _hoops_GPRA = _hoops_IHCR->_hoops_SPH->position;
		_hoops_RPRA const  *	_hoops_APRA = _hoops_IHCR->_hoops_IPH->_hoops_PPRA()->data.elements;
		_hoops_GPRA.x = _hoops_HPRA (_hoops_APRA, _hoops_GPRA);
		_hoops_GPRA.y = _hoops_IPRA (_hoops_APRA, _hoops_GPRA);
		_hoops_GPRA.z = _hoops_CPRA (_hoops_APRA, _hoops_GPRA);

		_hoops_HIHR (H3D_VSConstant_Table, _hoops_SPRA,
			null, "CameraPosition", &_hoops_GPRA, 3);
	}

	if (_hoops_PCC._hoops_IAI()) {
		Point _hoops_GPRA = _hoops_IHCR->_hoops_SPH->position;
		Point _hoops_GHRA;

		HI_Compute_Transformed_Points(1, (Point *)&_hoops_GPRA.x,
			&h3ddata->_hoops_SPSR[0], &_hoops_GHRA);

		// _hoops_RAP _hoops_IS _hoops_IRPR _hoops_CI
		_hoops_HIHR (_hoops_PCC._hoops_RPH() ? H3D_PSConstant_Table : H3D_VSConstant_Table, _hoops_RHRA,
			null, "EyeCameraPosition", &_hoops_GHRA, 3);
	}


	if (_hoops_PCC._hoops_SAC() || _hoops_PCC._hoops_AHRA()) {
		float scale;
		float contrast_color[4];
		contrast_color[0] = _hoops_SIGA->contrast_color._hoops_HRIR.r / 255.0f;
		contrast_color[1] = _hoops_SIGA->contrast_color._hoops_HRIR.g / 255.0f;
		contrast_color[2] = _hoops_SIGA->contrast_color._hoops_HRIR.b / 255.0f;
		contrast_color[3] = _hoops_SIGA->contrast_color._hoops_HRIR.a / 255.0f;
		if (_hoops_PCC._hoops_SAC()) {
			if (_hoops_PCC._hoops_ICRR())
				scale = 16.0f;
			else
				scale = 32.0f;
		}
		else
			scale = 1.0f;

		_hoops_CGIR(H3D_VSConstant_Table, _hoops_GCGA, 0, "ScaledWindowWidth",
			(_hoops_SGRA->_hoops_PHRA.right - _hoops_SGRA->_hoops_PHRA.left + 1) / scale);
		_hoops_CGIR(H3D_VSConstant_Table, _hoops_ACGA, 0, "ScaledWindowHeight",
			(_hoops_SGRA->_hoops_PHRA.top - _hoops_SGRA->_hoops_PHRA.bottom + 1) / scale);
		_hoops_HIHR(H3D_PSConstant_Table, _hoops_PCGA,
			0, "FaceContrastColor", contrast_color, 4);
	}

	if (_hoops_PCC._hoops_RPC() && !_hoops_PCC._hoops_APC()) {
		_hoops_HHRA const *_hoops_SPH = _hoops_IHCR->_hoops_SPH;

		// _hoops_GPPR _hoops_IIPR _hoops_AHCR _hoops_HSH _hoops_IS _hoops_IHRA _hoops_CHRA. _hoops_SHRA _hoops_RHC _hoops_GIRA _hoops_HRGR _hoops_IRS _hoops_RIRA _hoops_AIRA _hoops_PIRA _hoops_IH _hoops_RH _hoops_HIRA'_hoops_GRI _hoops_HCH.
		float _hoops_IIRA = 1.0f / (_hoops_CIRA * 2.0f * _hoops_SPH->_hoops_SRIR);
		if (_hoops_SPH->projection != _hoops_GHH) {
			// _hoops_GPPR _hoops_GH _hoops_IS _hoops_CHRA _hoops_HCH _hoops_SRS
			_hoops_IIRA *= h3ddata->_hoops_SIRA - h3ddata->_hoops_GCRA;
		}

		// _hoops_HCGA
		_hoops_CGIR(H3D_PSConstant_Table, _hoops_ICGA, null, "DepthWriteScale", _hoops_IIRA);
	}

	if (_hoops_PCC._hoops_APC() || _hoops_PCC._hoops_HPC()) {
		float _hoops_RCRA, _hoops_ACRA, _hoops_PCRA, _hoops_HCRA;
		Point center, _hoops_ICRA;

		center.x = (float) (dc->_hoops_RCGA.right + dc->_hoops_RCGA.left) / 2;
		center.y = (float) (dc->_hoops_RCGA.top + dc->_hoops_RCGA.bottom) / 2;
		_hoops_ICRA.x = (float) (_hoops_SGRA->_hoops_PHRA.right + _hoops_SGRA->_hoops_PHRA.left) / 2;
		_hoops_ICRA.y = (float) (_hoops_SGRA->_hoops_PHRA.top + _hoops_SGRA->_hoops_PHRA.bottom) / 2;

		float const _hoops_CCRA = (float)(_hoops_SGRA->_hoops_PHRA.right - _hoops_SGRA->_hoops_PHRA.left);
		float const _hoops_SCRA = (float)(_hoops_SGRA->_hoops_PHRA.top - _hoops_SGRA->_hoops_PHRA.bottom);
		_hoops_RCRA = _hoops_CCRA / (dc->_hoops_RCGA.right - dc->_hoops_RCGA.left);
		_hoops_ACRA = _hoops_SCRA / (dc->_hoops_RCGA.top - dc->_hoops_RCGA.bottom);
		_hoops_PCRA = (float)(_hoops_ICRA.x - center.x) / (center.x);
		_hoops_HCRA = (float)(_hoops_ICRA.y - center.y) / (center.y);

		// _hoops_GSRA _hoops_CRGR _hoops_IRS _hoops_RSRA _hoops_SRSR _hoops_GCPR _hoops_PPR _hoops_ASRA
		float _hoops_PSRA[] = {_hoops_RCRA, _hoops_ACRA, _hoops_PCRA, _hoops_HCRA};
		_hoops_PIIR(H3D_PSConstant_Table, _hoops_HSRA, null, "viewport_scale_and_bias", &_hoops_PSRA[0], 4);

		if (_hoops_PCC._hoops_HPC())
		{
			// _hoops_ISRA, _hoops_CSRA _hoops_IH _hoops_RI _hoops_SSRA
			_hoops_PSRA[0] = 0.5f * _hoops_CCRA / _hoops_GGAA;
			_hoops_PSRA[1] = 0.5f * _hoops_SCRA / _hoops_GGAA;
			_hoops_PSRA[2] = 0;
			_hoops_PSRA[3] = 0;
			_hoops_PIIR(H3D_PSConstant_Table, _hoops_RGAA, null, "JitterScaleAndBias", &_hoops_PSRA[0], 4);
		}
	}

	if (_hoops_PCC._hoops_GSI()) {
		_hoops_CGIR(H3D_VSConstant_Table, _hoops_GCGA, 0, "WindowWidth",
			(_hoops_IHCR->_hoops_AGAA.right - _hoops_IHCR->_hoops_AGAA.left + 1));
		_hoops_CGIR(H3D_VSConstant_Table, _hoops_ACGA, 0, "WindowHeight",
			(_hoops_IHCR->_hoops_AGAA.top - _hoops_IHCR->_hoops_AGAA.bottom + 1));
	}
};



//
// _hoops_PGAA: _hoops_PIGR _hoops_HGAA _hoops_HII _hoops_SARA _hoops_GC _hoops_IS _hoops_APR, _hoops_RAGA _hoops_IGAA _hoops_PPR _hoops_CGAA _hoops_IIGR
// _hoops_APR.
//
void _hoops_RHCR(H3DData *h3ddata, const _hoops_GSAR::_hoops_APCR& _hoops_PPCR, int const index, int const size, Vector& scale, Vector& bias) {

	// _hoops_SGAA _hoops_IS _hoops_GRAA-_hoops_RRAA _hoops_ARAA.
	float _hoops_PRAA = _hoops_PPCR.size.x;
	float _hoops_HRAA = _hoops_PPCR.size.y;

	// _hoops_AHH: _hoops_PCH _hoops_IRAA _hoops_RGR _hoops_CRAA - _hoops_PSP _hoops_SRAA _hoops_GAAA _hoops_GGR _hoops_RAAA.
	if (1) {
		// _hoops_GCRR _hoops_IRS _hoops_RRAA _hoops_ARAA. _hoops_HGI _hoops_AAAA _hoops_GIH _hoops_RGRR _hoops_PAAA.
		float const _hoops_HAAA = _hoops_IAAA(_hoops_PPCR.size.x, _hoops_PPCR.size.y);
		_hoops_PRAA = _hoops_HRAA = _hoops_HAAA;
	}

	// _hoops_CAAA _hoops_IGIR _hoops_IS _hoops_SARA _hoops_GC _hoops_SAAA
	scale.x = 2.0f / _hoops_PRAA;
	scale.y = 2.0f / _hoops_HRAA;
	scale.z = 1.0f / _hoops_PPCR.size.z;

	// _hoops_HCGA _hoops_GPAA
	float const _hoops_RPAA = 1.0f + (4.0f * _hoops_APAA) / size;
	scale.x /= _hoops_RPAA;
	scale.y /= _hoops_RPAA;

	// _hoops_GSIR _hoops_IS _hoops_IRS _hoops_PPAA - (_hoops_SISR - _hoops_RCSR)_hoops_GRI -> _hoops_HPAA - _hoops_IPAA -> _hoops_SISR._hoops_GRI + (-_hoops_IPAA)
	bias.x = scale.x * -_hoops_PPCR._hoops_CPAA.x;
	bias.y = scale.y * -_hoops_PPCR._hoops_CPAA.y;
	bias.z = scale.z * -_hoops_PPCR._hoops_CPAA.z;

	// _hoops_SPAA _hoops_GHAA _hoops_RHAA-_hoops_SARA-_hoops_GC _hoops_AHAA _hoops_IS _hoops_HH _hoops_GC. _hoops_PHAA _hoops_CSRA _hoops_HPP _hoops_HHAA _hoops_PPR _hoops_IHAA _hoops_GHCR.
	scale.x *= 0.5f;
	scale.y *= -0.5f * h3ddata->_hoops_ACCR;
	bias.x *= 0.5f;
	bias.y *= -0.5f * h3ddata->_hoops_ACCR;

	// _hoops_SPAA _hoops_CHAA _hoops_IS _hoops_SHAA [0,1]_hoops_SISR[0,1]
	bias.x += 0.5f;
	bias.y += 0.5f;

	// _hoops_AGGA _hoops_ARCR _hoops_IS _hoops_RH _hoops_ARAA _hoops_GIAA _hoops_RH _hoops_HH. _hoops_RIAA _hoops_SCAR _hoops_GGR _hoops_AIAA _hoops_PIAA.
	scale.x *= 0.5f;
	scale.y *= 0.5f;
	bias.x *= 0.5f;
	bias.y *= 0.5f;

	if (index & 1)
		bias.x += 0.5f;
	if (index & 2)
		bias.y += 0.5f;

	// _hoops_HIAA _hoops_CHAA _hoops_HPP _hoops_SPR-_hoops_HHAA _hoops_PPPR _hoops_IS _hoops_ARCR _hoops_AIR _hoops_IIAA _hoops_CIAA _hoops_PPPR _hoops_IIAA
	bias.x += 0.5f / size;
	bias.y += 0.5f / size;
}


void H3DShader::_hoops_SIAA(Net_Rendition const & nr,
							  Line_Rendition const &_hoops_GHP)
{
	if (_hoops_PCC._hoops_RIHR())
		return;

	H3DData alter *h3ddata = H3DD (nr->_hoops_SRA);
	int weight = _hoops_GHP->weight;

	if (_hoops_PCC._hoops_GSI()) {
		if (weight < 0)
			weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP,1.0f, false, 0, true)+0.5f);

		if (weight >= 0 && weight < 1)
			weight = 1;

		if (_hoops_PCC._hoops_CSI())
			weight += 1;

		_hoops_CGIR(H3D_VSConstant_Table, _hoops_GCAA,
			null, "LineWeight", (float)weight);
		ASSERT (weight <= H3D_LARGEST_PRECOMPUTED_CIRCLE);
		_hoops_CGIR(H3D_VSConstant_Table, _hoops_RCAA,
			null, "CircleSubImageStart", (float)h3ddata->_hoops_HSI._hoops_ACAA[weight]);

		if (_hoops_PCC._hoops_PSI()) {
			_hoops_CGIR(H3D_VSConstant_Table, _hoops_PCAA,
				null, "CosJoinCutoffAngle", Abs(COS(_hoops_GHP->_hoops_HCAA)));
		}
	}
	if (_hoops_PCC._hoops_SSI()) {
		float contrast_color[4];
		contrast_color[0] = _hoops_GHP->contrast_color._hoops_HRIR.r;
		contrast_color[1] = _hoops_GHP->contrast_color._hoops_HRIR.g;
		contrast_color[2] = _hoops_GHP->contrast_color._hoops_HRIR.b;
		contrast_color[3] = _hoops_GHP->contrast_color._hoops_HRIR.a;
		_hoops_HIHR(H3D_PSConstant_Table, _hoops_ICAA,
			0, "LineContrastColor", contrast_color, 4);
	}
	UNREFERENCED (nr);
}

void H3DShader::_hoops_CCAA (
	Net_Rendition const &	nr,
	float					size,
	bool					_hoops_SCAA,
	bool					_hoops_GSAA,
	H3DTexture *			glyph)
{
	if (_hoops_PCC._hoops_RIHR())
		return;

	H3DData alter *			h3ddata = H3DD (nr->_hoops_SRA);

	float _hoops_RSAA[2] =
	{
		// _hoops_CAAA _hoops_IGIR _hoops_HII _hoops_AIR _hoops_ASAA _hoops_IS _hoops_GCCR _hoops_GC _hoops_PSAA,
		size * h3ddata->_hoops_HSAA,
		size * h3ddata->_hoops_ISAA,
	};

	if (_hoops_GSAA) {
		_hoops_RSAA[0] /= h3ddata->_hoops_CSC->_hoops_CSAA.Width;
		_hoops_RSAA[1] /= h3ddata->_hoops_CSC->_hoops_CSAA.Height;
	}

	_hoops_PIIR(H3D_VSConstant_Table, _hoops_SSAA, null, "MarkerSize", _hoops_RSAA, 2);

	if (_hoops_SCAA) {

		const float _hoops_GGPA[4] =
		{
			// _hoops_SSIR _hoops_HPP _hoops_AGCR
			0.5f * h3ddata->_hoops_CSC->_hoops_CSAA.Width,
			0.5f * h3ddata->_hoops_CSC->_hoops_CSAA.Height,

			// _hoops_RGPA _hoops_AGCR
			0.5f * h3ddata->_hoops_CSC->_hoops_CSAA.Width,
			0.5f * h3ddata->_hoops_CSC->_hoops_CSAA.Height,
		};

		const float _hoops_AGPA[4] =
		{
			// _hoops_SSIR _hoops_HPP _hoops_AGCR
			2.0f / h3ddata->_hoops_CSC->_hoops_CSAA.Width,
			2.0f / h3ddata->_hoops_CSC->_hoops_CSAA.Height,

			// _hoops_RGPA _hoops_AGCR
			-1.0f,
			-1.0f,
		};

		_hoops_HIHR(H3D_VSConstant_Table, _hoops_PGPA, null, "MarkerSnap", (void *) _hoops_GGPA, 4);
		_hoops_HIHR(H3D_VSConstant_Table, _hoops_HGPA, null, "MarkerUnsnap", (void *) _hoops_AGPA, 4);
	}

	if ( _hoops_PCC._hoops_CHC() ) {
		int _hoops_RARR;
		_hoops_PCC._hoops_SII(_hoops_HCRR, 0, null, null, &_hoops_RARR);

		float _hoops_IGPA = 0;
		if (h3ddata->_hoops_ACCR == -1 && size)
			_hoops_IGPA = 0.5 / size;

		_hoops_CGIR(H3D_PSConstant_Table, _hoops_CGPA,
			null, "MarkerSamplerBias", _hoops_IGPA);

		_hoops_ICCR(H3D_PSConstant_Table, _hoops_SGPA,
			null, "MarkerSampler", _hoops_RARR);

		_hoops_SCCR(h3ddata, _hoops_RARR, glyph);
		_hoops_GRPA(h3ddata, _hoops_RARR, H3DTEXF_POINT, H3DTEXF_NONE, H3DTADDRESS_BORDER);
	}
}


bool _hoops_RRPA(
										Net_Rendition const &  nr,
										_hoops_ARPA const			*in,
										_hoops_ARPA				*_hoops_PAGR)
{
	H3DData *h3ddata				= H3DD(nr->_hoops_SRA);
	_hoops_HHCR const & _hoops_IHCR	= nr->transform_rendition;

	if (_hoops_IHCR->_hoops_SPH->_hoops_PRPA._hoops_APRA == null)
		HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)&_hoops_IHCR->_hoops_SPH->_hoops_PRPA);


	Vector					_hoops_IRPA;
	float					w, scale;
	const _hoops_RPRA		*_hoops_CRPA = _hoops_IHCR->_hoops_SPH->_hoops_PRPA._hoops_APRA->data.elements;

	_hoops_IRPA.x = in->a*_hoops_CRPA[0][0] + in->b*_hoops_CRPA[0][1] + in->c*_hoops_CRPA[0][2] + in->d*_hoops_CRPA[0][3];
	_hoops_IRPA.y = in->a*_hoops_CRPA[1][0] + in->b*_hoops_CRPA[1][1] + in->c*_hoops_CRPA[1][2] + in->d*_hoops_CRPA[1][3];
	_hoops_IRPA.z = in->a*_hoops_CRPA[2][0] + in->b*_hoops_CRPA[2][1] + in->c*_hoops_CRPA[2][2] + in->d*_hoops_CRPA[2][3];
	w	   = in->a*_hoops_CRPA[3][0] + in->b*_hoops_CRPA[3][1] + in->c*_hoops_CRPA[3][2] + in->d*_hoops_CRPA[3][3];

	// _hoops_SRPA _hoops_IH _hoops_RH _hoops_GAAA _hoops_GGR _hoops_SARA _hoops_AHC _hoops_GAPA _hoops_RAPA _hoops_PPR _hoops_AAPA-_hoops_PAPA
	if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH)
		w = w - _hoops_IRPA.z * _hoops_IHCR->_hoops_SPH->_hoops_SRIR;

	scale = (float)HI_Compute_Vector_Length (&_hoops_IRPA);
	if (scale == 0.0f)
		return false;

	scale = 1.0f / scale;

	_hoops_PAGR->a = -_hoops_IRPA.x * scale;
	_hoops_PAGR->b = -_hoops_IRPA.y * scale;
	_hoops_PAGR->c = -_hoops_IRPA.z * scale * h3ddata->_hoops_ACCR;
	_hoops_PAGR->d = -w	   * scale;

	return	true;
}



/*
 * _hoops_PGAA
 */
void H3DShader::_hoops_HAPA (_hoops_IAPA const *_hoops_CAPA)
{
	if (_hoops_PCC._hoops_RIHR())
		return;

	if (_hoops_CAPA) {
		float _hoops_SAPA[4];
		_hoops_GPPA const *_hoops_RPPA = _hoops_CAPA->_hoops_APPA;

		// _hoops_PPPA _hoops_HCR _hoops_RH _hoops_HPPA _hoops_IPPA _hoops_CPPA _hoops_GGR _hoops_RH _hoops_CI
		for (int i = 0; i < _hoops_PCC._hoops_IAC(); ++i)
		{
			if (_hoops_RPPA)
			{
				_hoops_SAPA[0] = -_hoops_RPPA->_hoops_SPPA.a;
				_hoops_SAPA[1] = -_hoops_RPPA->_hoops_SPPA.b;
				_hoops_SAPA[2] = -_hoops_RPPA->_hoops_SPPA.c;
				_hoops_SAPA[3] = -_hoops_RPPA->_hoops_SPPA.d;
				_hoops_RPPA = _hoops_RPPA->next;
			}
			else
			{
				// _hoops_GHPA _hoops_GGSR _hoops_RHPA _hoops_GHC (_hoops_AHPA _hoops_HHS _hoops_SHH _hoops_PHPA _hoops_HSAR _hoops_HHPA _hoops_GHC)
				_hoops_SAPA[0] = 0;
				_hoops_SAPA[1] = 0;
				_hoops_SAPA[2] = 0;
				_hoops_SAPA[3] = 0;
			}

			sprintf(_hoops_ISS->shader_handle, "CuttingPlanes[%d]", i);
			_hoops_PIIR(H3D_VSConstant_Table, _hoops_IHPA + i,
				null, _hoops_ISS->shader_handle, &_hoops_SAPA[0], 4);
		}
	}
}

void H3DShader::_hoops_CHPA(Net_Rendition const & nr, _hoops_IAPA const *_hoops_CAPA)
{
	if (_hoops_PCC._hoops_RIHR())
		return;

	if (_hoops_CAPA) {
		float _hoops_SAPA[4];
		_hoops_GPPA const *_hoops_RPPA = _hoops_CAPA->_hoops_APPA;

		// _hoops_PPPA _hoops_HCR _hoops_RH _hoops_HPPA _hoops_IPPA _hoops_CPPA _hoops_GGR _hoops_RH _hoops_CI
		for (int i = 0; i < _hoops_PCC._hoops_IAC(); ++i)
		{
			if (_hoops_RPPA)
			{
				_hoops_RRPA(nr, &_hoops_RPPA->_hoops_SHPA, (_hoops_ARPA*) _hoops_SAPA);
				_hoops_RPPA = _hoops_RPPA->next;
			}
			else
			{
				// _hoops_GHPA _hoops_GGSR _hoops_RHPA _hoops_GHC (_hoops_AHPA _hoops_HHS _hoops_SHH _hoops_PHPA _hoops_HSAR _hoops_HHPA _hoops_GHC)
				_hoops_SAPA[0] = 0;
				_hoops_SAPA[1] = 0;
				_hoops_SAPA[2] = 0;
				_hoops_SAPA[3] = 0;
			}

			sprintf(_hoops_ISS->shader_handle, "CuttingPlanes[%d]", i);
			_hoops_PIIR(H3D_VSConstant_Table, _hoops_IHPA + i,
				null, _hoops_ISS->shader_handle, (float *) &_hoops_SAPA, 4);
		}
	}
}

void H3DShader::_hoops_GIPA(_hoops_RIPA const & _hoops_AIPA)
{
	if (_hoops_PCC._hoops_RIHR())
		return;

	_hoops_PIIR(H3D_PSConstant_Table, _hoops_PIPA, "ReflectionPlane", "plane", (float *) &_hoops_AIPA.plane, 4);
	_hoops_CGIR(H3D_PSConstant_Table, _hoops_HIPA, "ReflectionPlane", "scale", _hoops_AIPA.scale);
	_hoops_CGIR(H3D_PSConstant_Table, _hoops_IIPA, "ReflectionPlane", "bias", _hoops_AIPA.bias);
}

void H3DShader::_hoops_CIPA (Net_Rendition const &nr)
{
	if (_hoops_PCC._hoops_RIHR())
		return;

	H3DData alter *			h3ddata = H3DD (nr->_hoops_SRA);
	_hoops_HHRA const & _hoops_SPH = *nr->transform_rendition->_hoops_SPH;;

	//
	// _hoops_SIPA _hoops_IS _hoops_SHI _hoops_GCPA _hoops_HPP _hoops_SPR _hoops_HHAA _hoops_AIR _hoops_GGR _hoops_GSSR'_hoops_GRI _hoops_HAGA. _hoops_RCPA _hoops_AA _hoops_RGR _hoops_SR
	// _hoops_RRP _hoops_IS _hoops_ACPA _hoops_PCPA _hoops_IGIR _hoops_SPR _hoops_AIR _hoops_HCPA _hoops_GH _hoops_GGR _hoops_RHC _hoops_GC.
	//

	// _hoops_ICPA _hoops_AIR _hoops_CCPA
	float const _hoops_SCPA = 1.0f/h3ddata->_hoops_CSC->_hoops_CSAA.Width;
	float const _hoops_GSPA = 1.0f/h3ddata->_hoops_CSC->_hoops_CSAA.Height;

	// _hoops_RSPA _hoops_AGIR - _hoops_SAHR _hoops_IPHR _hoops_GGSR _hoops_CSRA _hoops_HII _hoops_CSCR _hoops_ASPA _hoops_IS _hoops_RHC-_hoops_GC _hoops_PSPA
	float const _hoops_HSPA = _hoops_SPH._hoops_ISPA * _hoops_SCPA;
	float const _hoops_CSPA = _hoops_SPH._hoops_SSPA * _hoops_GSPA;
	float const _hoops_GGHA = 0.5f * _hoops_IAAA(_hoops_HSPA, _hoops_CSPA);

	float const _hoops_SACR[4] =
	{
		// _hoops_RSPA
		_hoops_GGHA,
		// _hoops_RGHA. _hoops_AGHA _hoops_RHIR _hoops_HPP _hoops_RHC _hoops_GIRA, _hoops_PGHA _hoops_GGR _hoops_CI.
		_hoops_GGHA / _hoops_SPH._hoops_SRIR,
		// _hoops_HGHA
		0, 0
	};

	_hoops_HIHR(H3D_VSConstant_Table, _hoops_IGHA, null, "PolyCylinderScale", (void *) &_hoops_SACR, sizeof(_hoops_SACR)/sizeof(float));
}


/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_CGHA _hoops_SGHA
*****************************************************************************
*****************************************************************************/



H3D_Vertex_Buffer_Style _hoops_GRHA (
		Polyedge const *pe,
		H3D_Display_List_Bin alter *_hoops_RRHA,
		unsigned int *_hoops_ARHA)
{
	bool _hoops_PRHA;
	unsigned int flags;
	int _hoops_HRHA;

	if (_hoops_RRHA) {
		_hoops_IRHA *pair = _hoops_RRHA->_hoops_CRHA->PeekFirst();
		pe = (Polyedge const *) pair->geo;
		flags = *_hoops_ARHA = _hoops_RRHA->flags;
	}
	else
		flags = *_hoops_ARHA = pe->_hoops_SRHA;

	if (BIT(flags, DL_DO_NOT_RECOMPILE)) {
		H3D_Display_List *odl = (H3D_Display_List *) pe->_hoops_GAHA->list;
		_hoops_HRHA = odl->_hoops_RAHA;
	}
	else
		//_hoops_SR _hoops_GA'_hoops_RA _hoops_RRP _hoops_RH _hoops_AAHA _hoops_ARI, _hoops_CR _hoops_SCH _hoops_PAHA'_hoops_RA _hoops_HAHA _hoops_SRHR _hoops_IAHA
		_hoops_HRHA = _hoops_AHA(pe, false);

	_hoops_PRHA = (BIT(_hoops_HRHA, _hoops_HSA) || BIT(_hoops_HRHA, _hoops_CAA));

	if (BIT(_hoops_HRHA, _hoops_SIP) || BIT(_hoops_HRHA, _hoops_HCP)) {
		if (_hoops_PRHA)
			return H3D_Unshared_Vertices;
		else
			return H3D_Partially_Shared_Vertices;
	}
	else
		return H3D_Shared_Vertices;

} // _hoops_RSGR _hoops_API '_hoops_CAHA _hoops_SAHA _hoops_GPHA _hoops_SRHR _hoops_IAHA'


void _hoops_RPHA (
		Polyedge const *pe,
		H3D_Display_List_Bin alter *_hoops_RRHA,
		H3D_Vertex_Buffer_Style _hoops_APHA,
		int alter *_hoops_PPHA,
		int alter *_hoops_HPHA,
		int alter *_hoops_IPHA)
{
	int i;
	int _hoops_CPHA, point_count, _hoops_SPHA;
	_hoops_IRHA *pair;

	if (_hoops_RRHA) {
		if (_hoops_PPHA)
			*_hoops_PPHA = 0;
		if (_hoops_HPHA)
			*_hoops_HPHA = 0;
		if (_hoops_IPHA)
			*_hoops_IPHA = 0;

		_hoops_RRHA->_hoops_CRHA->ResetCursor();
		for (;;) {
			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			if (!pair)
				break;
			pe = (Polyedge const *) pair->geo;
			// _hoops_GHHA _hoops_GPP _hoops_RHHA _hoops_AHHA
			_hoops_RPHA (pe, null, _hoops_APHA, &_hoops_CPHA, &point_count, &_hoops_SPHA);
			if (_hoops_PPHA)
				*_hoops_PPHA += _hoops_CPHA;
			if (_hoops_HPHA)
				*_hoops_HPHA += point_count;
			if (_hoops_IPHA)
				*_hoops_IPHA += _hoops_SPHA;
			_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
		}
		_hoops_RRHA->_hoops_CRHA->ResetCursor();
	}
	else {
		ASSERT (pe->_hoops_PHHA >= 0);
		if (pe->lengths) {
			/* _hoops_HHHA _hoops_IHHA */
			_hoops_CPHA = 0;
			for (i = 0; i < pe->_hoops_PHHA; i++)
				_hoops_CPHA += 2 * (pe->lengths[i]-1);
		}
		else {
			/* _hoops_CHHA _hoops_IHHA, _hoops_SHHA _hoops_SGS _hoops_HCR _hoops_GIHA _hoops_RIHA _hoops_GGR _hoops_SPR _hoops_CGGR */
			_hoops_CPHA = 2 * (pe->total - 1);
		}
		_hoops_CPHA = Abs(_hoops_CPHA);

		_hoops_SPHA = _hoops_CPHA - pe->_hoops_PHHA;

		if (_hoops_APHA == H3D_Partially_Shared_Vertices)
			point_count = pe->total;
		else if (_hoops_APHA == H3D_Unshared_Vertices)
			point_count = 2 * _hoops_SPHA;
		else {
			ASSERT (_hoops_APHA == H3D_Shared_Vertices);
			if (pe->point_count > 0) {
				point_count = pe->point_count;
			}
			else {
				// _hoops_SR _hoops_HS _hoops_IS _hoops_CAHA _hoops_GGSR _hoops_PPSR _hoops_RPR _hoops_IH _hoops_CAIR
				if (pe->_hoops_AIHA) {
					point_count = 0;
					for (i = 0; i < pe->total; i++)
						if (point_count < pe->_hoops_AIHA[i])
							point_count = pe->_hoops_AIHA[i];
					point_count++;	//_hoops_PIHA _hoops_HIHA _hoops_IH 0 _hoops_IIHA _hoops_CIHA
				}
				else
					point_count = pe->total;
			}
		}
		if (_hoops_PPHA)
			*_hoops_PPHA = _hoops_CPHA;
		if (_hoops_HPHA)
			*_hoops_HPHA = point_count;
		if (_hoops_IPHA)
			*_hoops_IPHA = _hoops_SPHA;
	}

} //_hoops_RSGR _hoops_API '_hoops_SIHA _hoops_SAHA _hoops_GCHA'


int _hoops_AHA(Polyedge const *pe, bool _hoops_PAA)
{
	if (pe == null)
		return 0;

	int _hoops_RCHA = 0;
	if (pe->_hoops_AIHA)
		_hoops_RCHA |= _hoops_ACHA;
	if (pe->_hoops_PCHA)
		_hoops_RCHA |= _hoops_CAA;
	if (pe->_hoops_HCHA)
		_hoops_RCHA |= _hoops_HGP;
	if (pe->_hoops_ICHA)
		_hoops_RCHA |= _hoops_HSA;
	if (pe->_hoops_CCHA)
		_hoops_RCHA |= _hoops_SCHA;
	if (pe->_hoops_GSHA)
		_hoops_RCHA |= _hoops_PIA;
	if (pe->_hoops_RSHA)
		_hoops_RCHA |= _hoops_SIP;
	if (pe->_hoops_ASHA)
		_hoops_RCHA |= _hoops_HCP;
	if (!ANYBIT (_hoops_RCHA, _hoops_HCP|_hoops_CAA)) {
		if (_hoops_PAA) {
			//_hoops_AAHA _hoops_PSHA _hoops_PAH _hoops_SHH _hoops_HSHA _hoops_GAR _hoops_GPHA _hoops_PAR _hoops_ISHA _hoops_PSHA, _hoops_CSHA _hoops_HRGR _hoops_SSHA
			if (BIT (_hoops_RCHA, _hoops_SIP))
				_hoops_RCHA |= _hoops_HCP;
			else
				_hoops_RCHA |= _hoops_CAA;
		}
	}
	if (BIT(pe->_hoops_SRHA, _hoops_GGIA))
		_hoops_RCHA |= _hoops_IGP;

	return _hoops_RCHA;
}


int _hoops_PHA(Polymarker const *pm, bool _hoops_PAA)
{
	if (pm == null)
		return 0;

	int _hoops_RCHA = 0;
	if (pm->_hoops_AIHA)
		_hoops_RCHA |= _hoops_ACHA;
	if (pm->_hoops_PCHA || _hoops_PAA)
		_hoops_RCHA |= _hoops_CAA;
	if (pm->_hoops_RGIA) {
		_hoops_RCHA |= _hoops_RSP;
		//_hoops_AGIA _hoops_IS _hoops_SHH _hoops_PGIA _hoops_HGIA
		ASSERT (!pm->_hoops_PCHA); 
	}
	if (pm->_hoops_HCHA)
		_hoops_RCHA |= _hoops_HGP;
	if (pm->_hoops_ICHA)
		_hoops_RCHA |= _hoops_HSA;
	if (pm->_hoops_CCHA)
		_hoops_RCHA |= _hoops_SCHA;
	if (pm->_hoops_GSHA)
		_hoops_RCHA |= _hoops_PIA;
	if (BIT(pm->_hoops_SRHA, _hoops_GGIA))
		_hoops_RCHA |= _hoops_IGP;

	return _hoops_RCHA;
}


Param_Source _hoops_IGIA (
	_hoops_HHA const &		matr,
	int 							type,
	int 							number) {

	switch (type) {
		case _hoops_PSRR: {
			_hoops_HIR const *_hoops_PGC = matr->_hoops_SCA;
			int i = 0;
			for (i = 0; i < number; i++) {
				ASSERT(_hoops_PGC->next);		/* _hoops_PAHA'_hoops_RA _hoops_HGCR _hoops_ISGR _hoops_RSGR _hoops_IIGR _hoops_SPI _hoops_HIGR */
				_hoops_PGC = _hoops_PGC->next;
			}
			return _hoops_PGC->texture->_hoops_PSR;
		}
		case _hoops_CAAR:
			return matr->texture[_hoops_RIA]->_hoops_PSR;
		case _hoops_PPAR:
			return matr->texture[_hoops_HIA]->_hoops_PSR;
		case _hoops_APAR:
			return matr->texture[_hoops_IIA]->_hoops_PSR;
		default:
			return 0;
	}
}

void _hoops_CGIA(
	Net_Rendition const &		nr,
	_hoops_HHA const &	matr,
	_hoops_HHA const &	_hoops_SHA,
	_hoops_PC const &		_hoops_HC,
	_hoops_HCI *			_hoops_ICI,
	bool *						_hoops_SGIA)
{
	_hoops_AS const *	light = (_hoops_HC) ? _hoops_HC->_hoops_CGR : null;

	_hoops_ICI->_hoops_RGC = true;

	/* _hoops_RPR _hoops_SPI _hoops_AI */
	if (matr->_hoops_SCA) {
		_hoops_HIR *_hoops_GRIA = matr->_hoops_SCA;
		_hoops_RCR *_hoops_ACR = _hoops_GRIA->texture;
		do {
			if (!_hoops_ISR(nr, _hoops_GRIA->texture, _hoops_ACR))
				_hoops_ICI->_hoops_RGC = false;				
			_hoops_ICI->_hoops_PGC++;
		} while ((_hoops_GRIA = _hoops_GRIA->next) != null);
	}

	if (_hoops_SHA &&
		_hoops_SHA != matr &&
		_hoops_SHA->_hoops_SCA) {
		_hoops_HIR *_hoops_GRIA = _hoops_SHA->_hoops_SCA;
		do {
			_hoops_ICI->_hoops_IGC++;
		} while ((_hoops_GRIA = _hoops_GRIA->next) != null);
	}

	/* _hoops_RPR _hoops_RHI _hoops_AI */
	if (matr->texture[_hoops_RIA]) {
		_hoops_ICI->_hoops_SRC++;

		/* _hoops_RRIA _hoops_CH _hoops_RRP _hoops_RHC _hoops_AHC */
		if ( matr->texture[_hoops_RIA]->_hoops_PSR == _hoops_HSR )
			*_hoops_SGIA = true;
	}

	if (matr->texture[_hoops_ACA])
		_hoops_ICI->_hoops_RAC++;

	/* _hoops_RPR _hoops_PH _hoops_ACAR */
	if (matr->texture[_hoops_IIA]) {
		_hoops_ICI->_hoops_RRC++;
		_hoops_ICI->_hoops_HIC = 1;
	}

	/* _hoops_RPR _hoops_ARIA */
	if (matr->_hoops_SCA && BIT(matr->_hoops_SCA->texture->_hoops_SCR, _hoops_GSR))
		_hoops_ICI->_hoops_HIC = 1;

	/* _hoops_RPR _hoops_GHI _hoops_AI */
	if (matr->texture[_hoops_HIA])
		_hoops_ICI->_hoops_SGC++;

	if (matr->texture[_hoops_PCA])
		_hoops_ICI->_hoops_PRC++;

	if (matr->texture[_hoops_HCA])
		_hoops_ICI->_hoops_IRC++;

	if (light) {

		/* _hoops_SGR _hoops_HPR, _hoops_PRIA _hoops_RPP _hoops_GII _hoops_CHR _hoops_RAR-_hoops_AAR */
		bool _hoops_SAR = false;
		while (light) {
			if (light->_hoops_HRR) {
				_hoops_ICI->_hoops_PAC++;
				if (light->_hoops_HRR->_hoops_SAR)
					_hoops_SAR = true;
				if (light->_hoops_PRR == _hoops_C || light->_hoops_PRR == _hoops_I)
					*_hoops_SGIA = true;
			}
			light = light->next;
		}

		if (_hoops_ICI->_hoops_PAC) {
			if (nr->_hoops_CPP->_hoops_HRR._hoops_HI || _hoops_SAR)
				_hoops_ICI->_hoops_PPC++;
		}
	}

}

void _hoops_HRIA (
	H3DData const *					h3ddata,
	Net_Rendition const &			nr,
	int 							type,
	int 							flags,
	int								_hoops_IRIA,
	_hoops_HCI *				_hoops_ICI) {
	_hoops_HHA				matr;
	_hoops_HHA				_hoops_SHA;
	_hoops_PC					_hoops_HC;
	Line_Rendition					_hoops_GHP;
	int								_hoops_CRIA = FP_SOLID;
	bool							_hoops_SRIA = false;
	bool							_hoops_SGIA = false;
	_hoops_SSP const	&_hoops_GGH = nr->transform_rendition->_hoops_RGH;

	ZERO_STRUCT(_hoops_ICI, _hoops_HCI);

	if (type == T_FACES) {
		_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
		_hoops_CRIA = _hoops_SIGA->pattern;

		_hoops_CGIA(nr, _hoops_SIGA->_hoops_CHA, _hoops_SIGA->_hoops_GIA, _hoops_SIGA->_hoops_AGP,
			_hoops_ICI, &_hoops_SGIA);

		if (ANYBIT (nr->_hoops_IRR->_hoops_CSA, _hoops_SSA | _hoops_GGP))
			_hoops_SRIA = true;
	}
	else if (type == T_LINES) {
		_hoops_GHP = nr->_hoops_AHP;
		_hoops_CGIA(nr, _hoops_GHP->_hoops_CHA, null, _hoops_GHP->_hoops_AGP, _hoops_ICI, &_hoops_SGIA);
	}
	else if (type == T_EDGES || type == _hoops_GPA) {
		_hoops_GHP = nr->_hoops_RHP;
		_hoops_CGIA(nr, _hoops_GHP->_hoops_CHA, null, _hoops_GHP->_hoops_AGP, _hoops_ICI, &_hoops_SGIA);

		if (ANYBIT (nr->_hoops_IRR->_hoops_CSA, _hoops_GCP | _hoops_RCP))
			_hoops_SRIA = true;
	}
	else if (type == T_MARKERS || type == T_VERTICES) {
		/* _hoops_GAIA _hoops_SHR _hoops_RAIA _hoops_GPHA _hoops_IPP */
		_hoops_ICP const &	_hoops_CCP = nr->_hoops_SCP;
		_hoops_CGIA(nr, _hoops_CCP->_hoops_CHA, null, _hoops_CCP->_hoops_AGP, _hoops_ICI, &_hoops_SGIA);
	}

	/* _hoops_RPR _hoops_AAIA _hoops_III _hoops_HH _hoops_IPI */
	if (type == T_LINES || type == T_EDGES || type == _hoops_GPA) {
		if (_hoops_GHP->weight > 1 || _hoops_GHP->weight < 0) {
			_hoops_ICI->_hoops_RSI = 1;

			if (type == T_LINES && (_hoops_GHP->style & LJOIN_MASK) == LJOIN_MITER)
				_hoops_ICI->_hoops_ASI = 1;
			if (ANYBIT(_hoops_GHP->style, LCAP_ROUND|LJOIN_ROUND|LCAP_END_ROUND) ||
				type == T_EDGES)
				_hoops_ICI->_hoops_HSI = 1;
		}
		else if (BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)) {
			_hoops_ICI->_hoops_RSI = 1;
			_hoops_ICI->_hoops_HSI = 1;
		}
		else if (h3ddata->_hoops_IHP){
			_hoops_ICI->_hoops_RSI = 1;
		}
	}

	/* _hoops_RPR _hoops_HSP _hoops_PAIA */
	if (_hoops_CRIA != FP_SOLID)
		_hoops_ICI->_hoops_CAC++;

	/* _hoops_RPR _hoops_GGAR _hoops_HH */
	if (BIT(flags, _hoops_GGIA))
		_hoops_ICI->_hoops_CCI++;

	/* _hoops_HAIA _hoops_IAIA _hoops_IIGR _hoops_RCA _hoops_RRP _hoops_RIR-_hoops_AIR _hoops_RHC _hoops_AHC. */
	if (h3ddata->_hoops_SH.mode || _hoops_SRIA)
		++_hoops_ICI->_hoops_CPC;

	/* _hoops_CAIA _hoops_PPR _hoops_SAIA _hoops_GIPR _hoops_RRP _hoops_GPIA _hoops_RPIA _hoops_PCRR */
	if ((type == T_MARKERS) || (_hoops_IRIA & _hoops_APIA))
		++_hoops_ICI->marker;

	/* _hoops_SGR _hoops_CGCR-_hoops_PPIA */
	if ((type == T_FACES && BIT(nr->_hoops_IRR->_hoops_CSA, _hoops_GGP)) ||
		 (type == T_EDGES && BIT(nr->_hoops_IRR->_hoops_CSA, _hoops_RCP)) ||
		 (type == _hoops_GPA && BIT(nr->_hoops_IRR->_hoops_CSA, _hoops_RCP)))
		++_hoops_ICI->_hoops_GIC;

	if (_hoops_GGH) {
		_hoops_ICI->_hoops_GPC = _hoops_GGH->_hoops_PGH;
		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_ICI->_hoops_GPC = _hoops_GGH->_hoops_CRH;
		}
		if (_hoops_ICI->_hoops_GPC > h3ddata->_hoops_GAH)
			_hoops_ICI->_hoops_GPC = h3ddata->_hoops_GAH;
	}

	/* _hoops_SGR _hoops_HCH _hoops_ISRR, _hoops_IGI _hoops_IH _hoops_HCH _hoops_GIAR _hoops_PPR _hoops_HCH _hoops_ICH. */
	if ((h3ddata->_hoops_RHH.flags & H3DID_DEPTH_PEELING) ||
		(h3ddata->_hoops_RHH.flags & H3DID_DEPTH_WRITING) ||
		(h3ddata->_hoops_II.mode && !BIT(nr->transform_rendition->flags, _hoops_ISH)))
		++_hoops_ICI->_hoops_GPC;

	if (nr->_hoops_IRR->_hoops_SRI == _hoops_GAI &&
		BIT (nr->transform_rendition->heuristics, _hoops_IRI))
		++_hoops_ICI->_hoops_AIC;
}


#define _hoops_HPIA(_hoops_IPIA, _hoops_CPIA, _hoops_SPIA) _hoops_GHIA (\
	if (!done) { \
		if (_hoops_GCI == _hoops_IPIA) { \
			if (_hoops_CPIA == 0) \
				*output = -1; \
			else if (_hoops_SPIA) \
				*output = _hoops_RHIA; \
			else \
				*output = _hoops_RHIA + _hoops_AHIA(number, (int)_hoops_CPIA); \
			done = true; \
		} \
		else if (_hoops_GCI == _hoops_PHIA && (_hoops_RHIA + _hoops_CPIA) > number) { \
			*output = _hoops_IPIA; \
			done = true; \
		} \
		if (_hoops_SPIA) \
			_hoops_RHIA += _hoops_AHIA(1, (int)_hoops_CPIA); \
		else \
			_hoops_RHIA += _hoops_CPIA; \
	} \
)

#define _hoops_HHIA(_hoops_IPIA, _hoops_CPIA) _hoops_GHIA (\
	if (!done) { \
		if (_hoops_GCI == _hoops_IPIA) { \
			if (_hoops_CPIA == 0) \
				*output = -1; \
			else \
				*output = _hoops_RHIA + _hoops_AHIA(number, (int)_hoops_CPIA); \
			done = true; \
		} \
		else if (_hoops_GCI == _hoops_PHIA && (_hoops_RHIA + _hoops_CPIA) > number) { \
			*output = _hoops_IPIA; \
			done = true; \
		} \
		_hoops_RHIA += _hoops_CPIA; \
	} \
)

/* - _hoops_HGI _hoops_API _hoops_HRS _hoops_RH _hoops_HH _hoops_HPI _hoops_IHIA _hoops_CCA _hoops_IRS _hoops_CHIA _hoops_HH _hoops_IPI.
 * - _hoops_CGP _hoops_SHIA _hoops_HRGR _hoops_RH _hoops_CHIA _hoops_HH _hoops_IPI, _hoops_RH _hoops_HH _hoops_IPI _hoops_IHIA
 *   _hoops_CCA _hoops_RH _hoops_CHIA _hoops_HH _hoops_HPI _hoops_HRGR _hoops_GIIA _hoops_RIIA (_hoops_AIIA _hoops_IRS _hoops_PIIA _hoops_HIIA).
 *
 *	 _hoops_IIIA:		_hoops_CIIA _hoops_IS _hoops_GPHA _hoops_CI; _hoops_SGH _hoops_CGPR _hoops_SIIA _hoops_GIHA
 *	 _hoops_GCIA:		_hoops_IIPR _hoops_IS _hoops_AIR _hoops_CI; _hoops_RGAR _hoops_IGI _hoops_GGR _hoops_RCIA
 *   _hoops_ACIA:	_hoops_CGPR _hoops_PCIA _hoops_IRS _hoops_HH _hoops_PPR _hoops_RGSR _hoops_HH _hoops_HCIA
 */

void _hoops_SII(int _hoops_GCI, int number, _hoops_HCI *_hoops_ICI, int *_hoops_RCI, int *_hoops_ACI, int *_hoops_PCI)
{
	int *output;
	bool done;

	if ((output = _hoops_RCI) != null) {
		int _hoops_RHIA = *output = 0;
		done = false;

		// _hoops_ICIA _hoops_CCIA _hoops_HPGR _hoops_RH _hoops_SCIA, _hoops_CR _hoops_GSIA _hoops_PPSR-_hoops_RSIA _hoops_ASIA _hoops_SCH _hoops_IIH
		_hoops_HHIA(_hoops_HCRR, _hoops_ICI->marker);

		/* _hoops_PSIA _hoops_APGR */
		{
			_hoops_HHIA(_hoops_CHRR, _hoops_ICI->_hoops_RSI);	// _hoops_GIPR _hoops_HSIA* _hoops_ISPR _hoops_ISIA->_hoops_CSIA _hoops_PGGA _hoops_SSIA _hoops_PGI _hoops_GIPR _hoops_GGCA _hoops_PAR _hoops_GA'_hoops_RA
			_hoops_HHIA(_hoops_IHRR, _hoops_ICI->_hoops_RSI);
			if (_hoops_GCI == _hoops_PIRR && _hoops_ICI->_hoops_RSI > 0) {		//_hoops_HGI _hoops_RGCA _hoops_SHH _hoops_AGCA _hoops_RPHR _hoops_RAS _hoops_RH _hoops_PGCA _hoops_IPI _hoops_ISPR
				*output = _hoops_RHIA - _hoops_ICI->_hoops_RSI;						// _hoops_RPP _hoops_SR _hoops_HS _hoops_AAIA, _hoops_HGCA _hoops_APGR, _hoops_SR _hoops_PAH _hoops_SGH _hoops_AAIA _hoops_III _hoops_PCRR _hoops_GAR _hoops_IGCA _hoops_PCRR
				done = true;
			}
			_hoops_HHIA(_hoops_SHRR, _hoops_ICI->_hoops_ASI);
		}

		_hoops_HHIA(_hoops_IAAR, _hoops_ICI->_hoops_CCI);
		_hoops_HHIA(_hoops_HIRR, _hoops_ICI->_hoops_GGC);
		_hoops_HHIA(_hoops_ACPR, _hoops_ICI->_hoops_AIC);
		_hoops_HPIA(_hoops_PSRR, _hoops_ICI->_hoops_PGC, _hoops_ICI->_hoops_RGC);
		_hoops_HHIA(_hoops_IRAR, _hoops_ICI->_hoops_IGC);
		_hoops_HHIA(_hoops_PPAR, _hoops_ICI->_hoops_SGC);
		_hoops_HHIA(_hoops_APAR, _hoops_ICI->_hoops_RRC);
		_hoops_HHIA(_hoops_RHRR, _hoops_ICI->_hoops_HIC);
		_hoops_HHIA(_hoops_RPAR, _hoops_ICI->_hoops_RAC);
		_hoops_HHIA(_hoops_HPAR, _hoops_ICI->_hoops_PRC);
		_hoops_HHIA(_hoops_CPAR, _hoops_ICI->_hoops_IRC);
		_hoops_HHIA(_hoops_CAAR, _hoops_ICI->_hoops_SRC);
		_hoops_HHIA(_hoops_GHPR, _hoops_ICI->_hoops_PAC);
		_hoops_HHIA(_hoops_CCRR, _hoops_ICI->_hoops_CAC);
		_hoops_HHIA(_hoops_RIPR, _hoops_ICI->_hoops_PPC);
		//_hoops_CGCA(_hoops_SGCA, _hoops_ISIA->_hoops_GRCA);
		//_hoops_CGCA(_hoops_RRCA, _hoops_ISIA->_hoops_IGCR);

		/* _hoops_ARCA _hoops_GHC _hoops_RRP _hoops_GRH _hoops_PRCA, _hoops_PGGA _hoops_AIAA _hoops_HRCA _hoops_RIR _hoops_HH _hoops_HPI */
		if (!done) {
			if (_hoops_GCI == _hoops_PIPR) {
				*output = _hoops_RHIA + (_hoops_AHIA(number, (int) _hoops_ICI->_hoops_HAC))/4;
				done = true;
			}
			_hoops_RHIA += _hoops_ICI->_hoops_HAC;
		}

		//_hoops_IGI _hoops_IH _hoops_GIPR _hoops_HCH _hoops_AI _hoops_PPR _hoops_HCH _hoops_ICH
		_hoops_HHIA(_hoops_RIAR, _hoops_ICI->_hoops_GPC);
	}
	
	if ((output = _hoops_ACI) != null) {
		int _hoops_RHIA = *output = 0;
		done = false;

		// _hoops_ICIA _hoops_CCIA _hoops_HPGR _hoops_RH _hoops_SCIA, _hoops_CR _hoops_GSIA _hoops_PPSR-_hoops_RSIA _hoops_ASIA _hoops_SCH _hoops_IIH
		_hoops_HHIA(_hoops_HCRR, _hoops_ICI->marker);

		/* _hoops_PSIA _hoops_APGR */
		{
			//_hoops_CGCA(_hoops_IRCA, _hoops_ISIA->_hoops_CSIA);	// _hoops_GIPR _hoops_HSIA* _hoops_ISPR _hoops_ISIA->_hoops_CSIA _hoops_PGGA _hoops_SSIA _hoops_PGI _hoops_GIPR _hoops_GGCA _hoops_PAR _hoops_GA'_hoops_RA
			_hoops_HHIA(_hoops_IHRR, _hoops_ICI->_hoops_RSI);
			//_hoops_RPP (_hoops_IPI == _hoops_CRCA && _hoops_ISIA->_hoops_CSIA > 0) {		//_hoops_HGI _hoops_RGCA _hoops_SHH _hoops_AGCA _hoops_RPHR _hoops_RAS _hoops_RH _hoops_PGCA _hoops_IPI _hoops_ISPR
			//	*_hoops_IIPR = _hoops_HPI - _hoops_ISIA->_hoops_CSIA;						// _hoops_RPP _hoops_SR _hoops_HS _hoops_AAIA, _hoops_HGCA _hoops_APGR, _hoops_SR _hoops_PAH _hoops_SGH _hoops_AAIA _hoops_III _hoops_PCRR _hoops_GAR _hoops_IGCA _hoops_PCRR
			//	_hoops_CPHR = _hoops_IHPR;
			//}
			//_hoops_CGCA(_hoops_SRCA, _hoops_ISIA->_hoops_GACA);
		}

		_hoops_HHIA(_hoops_IAAR, _hoops_ICI->_hoops_CCI);
		_hoops_HHIA(_hoops_HIRR, _hoops_ICI->_hoops_GGC);
		_hoops_HHIA(_hoops_ACPR, _hoops_ICI->_hoops_AIC);
		_hoops_HPIA(_hoops_PSRR, _hoops_ICI->_hoops_PGC, _hoops_ICI->_hoops_RGC);
		_hoops_HHIA(_hoops_IRAR, _hoops_ICI->_hoops_IGC);
		_hoops_HHIA(_hoops_PPAR, _hoops_ICI->_hoops_SGC);
		_hoops_HHIA(_hoops_APAR, _hoops_ICI->_hoops_RRC);
		_hoops_HHIA(_hoops_RHRR, _hoops_ICI->_hoops_HIC);
		_hoops_HHIA(_hoops_RPAR, _hoops_ICI->_hoops_RAC);
		_hoops_HHIA(_hoops_HPAR, _hoops_ICI->_hoops_PRC);
		_hoops_HHIA(_hoops_CPAR, _hoops_ICI->_hoops_IRC);
		_hoops_HHIA(_hoops_CAAR, _hoops_ICI->_hoops_SRC);
		_hoops_HHIA(_hoops_GHPR, _hoops_ICI->_hoops_PAC);
		_hoops_HHIA(_hoops_CCRR, _hoops_ICI->_hoops_CAC);
		_hoops_HHIA(_hoops_RIPR, _hoops_ICI->_hoops_PPC);
		_hoops_HHIA(_hoops_CIPR, _hoops_ICI->_hoops_CPC);
		//_hoops_CGCA(_hoops_RRCA, _hoops_ISIA->_hoops_IGCR);

		/* _hoops_ARCA _hoops_GHC _hoops_RRP _hoops_GRH _hoops_PRCA, _hoops_PGGA _hoops_AIAA _hoops_HRCA _hoops_RIR _hoops_HH _hoops_HPI */
		if (!done) {
			if (_hoops_GCI == _hoops_PIPR) {
				*output = _hoops_RHIA + (_hoops_AHIA(number, (int) _hoops_ICI->_hoops_HAC))/4;
				done = true;
			}
			_hoops_RHIA += _hoops_ICI->_hoops_HAC;
		}

		//_hoops_IGI _hoops_IH _hoops_GIPR _hoops_HCH _hoops_AI _hoops_PPR _hoops_HCH _hoops_ICH
		_hoops_HHIA(_hoops_RIAR, _hoops_ICI->_hoops_GPC);
	}
	
	if ((output = _hoops_PCI) != null) {
		int _hoops_RHIA = *output = 0;
		done = false;

		// _hoops_ICIA _hoops_CCIA _hoops_HPGR _hoops_RH _hoops_SCIA, _hoops_CR _hoops_GSIA _hoops_PPSR-_hoops_RSIA _hoops_ASIA _hoops_SCH _hoops_IIH
		_hoops_HHIA(_hoops_HCRR, _hoops_ICI->marker);

		/* _hoops_PSIA _hoops_APGR */
		{
			//_hoops_CGCA(_hoops_IRCA, _hoops_ISIA->_hoops_CSIA);	// _hoops_GIPR _hoops_HSIA* _hoops_ISPR _hoops_ISIA->_hoops_CSIA _hoops_PGGA _hoops_SSIA _hoops_PGI _hoops_GIPR _hoops_GGCA _hoops_PAR _hoops_GA'_hoops_RA
			//_hoops_CGCA(_hoops_RACA, _hoops_ISIA->_hoops_CSIA);
			_hoops_HHIA(_hoops_PIRR, _hoops_ICI->_hoops_HSI);
			//_hoops_CGCA(_hoops_SRCA, _hoops_ISIA->_hoops_GACA);
		}

		_hoops_HHIA(_hoops_IAAR, _hoops_ICI->_hoops_CCI);
		_hoops_HHIA(_hoops_HIRR, _hoops_ICI->_hoops_GGC);
		//_hoops_CGCA(_hoops_AACA, _hoops_ISIA->_hoops_PACA);
		_hoops_HHIA(_hoops_PSRR, _hoops_ICI->_hoops_PGC);
		_hoops_HHIA(_hoops_IRAR, _hoops_ICI->_hoops_IGC);
		_hoops_HHIA(_hoops_PPAR, _hoops_ICI->_hoops_SGC);
		_hoops_HHIA(_hoops_APAR, _hoops_ICI->_hoops_RRC);
		//_hoops_CGCA(_hoops_HACA, _hoops_ISIA->_hoops_IACA);
		_hoops_HHIA(_hoops_RPAR, _hoops_ICI->_hoops_RAC);
		_hoops_HHIA(_hoops_HPAR, _hoops_ICI->_hoops_PRC);
		_hoops_HHIA(_hoops_CPAR, _hoops_ICI->_hoops_IRC);
		_hoops_HHIA(_hoops_CAAR, _hoops_ICI->_hoops_SRC);
		_hoops_HHIA(_hoops_GHPR, _hoops_ICI->_hoops_PAC);
		_hoops_HHIA(_hoops_CCRR, _hoops_ICI->_hoops_CAC);
		_hoops_HHIA(_hoops_RIPR, _hoops_ICI->_hoops_PPC);
		//_hoops_CGCA(_hoops_SGCA, _hoops_ISIA->_hoops_GRCA);
		_hoops_HHIA(_hoops_RCPR, _hoops_ICI->_hoops_GIC);

		//_hoops_IGI _hoops_IH _hoops_GIPR _hoops_HCH _hoops_AI _hoops_PPR _hoops_HCH _hoops_ICH
		_hoops_HHIA(_hoops_RIAR, _hoops_ICI->_hoops_GPC);
	}
}


/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_CACA _hoops_SACA _hoops_GPCA
*****************************************************************************
*****************************************************************************/

local RGB const *_hoops_RPCA (_hoops_APCA const *color, int mask)
{
	do {
		ASSERT (color->type == _hoops_PPCA);
		if (BIT (color->_hoops_GHA, mask))
			return &color->rgb;
	} while ((color = (_hoops_APCA const *)color->next) != null);
	return null;
}

bool _hoops_HPCA(
	Net_Rendition const & nr,
	_hoops_IAPA const *& _hoops_CAPA)
{
	H3DData *h3ddata = H3DNRD(nr);
	// _hoops_HR _hoops_SR _hoops_PAH _hoops_IPCA
	bool _hoops_CPCA = true;
	_hoops_CAPA = null;

	/* _hoops_SPCA _hoops_GHCA _hoops_SHH _hoops_HPPA _hoops_GHC _hoops_IS _hoops_RHCA _hoops_AHCA */
	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		_hoops_SSP const &		_hoops_GGH = nr->transform_rendition->_hoops_RGH;

		/* _hoops_SGPR _hoops_RRH _hoops_GHC _hoops_GGR _hoops_RRH _hoops_CCH */
		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			if (_hoops_GGH->_hoops_CRH > h3ddata->_hoops_GAH)
				_hoops_CPCA = false;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			if (_hoops_GGH->_hoops_PGH > h3ddata->_hoops_GAH)
				_hoops_CPCA = false;
		}
	}

	// _hoops_AP
	return _hoops_CPCA;
}

bool _hoops_HHCA(Tristrip const *ts, H3D_Display_List_Bin *_hoops_RRHA)
{
	if (_hoops_RRHA)
		return false;

	if (ts->_hoops_GAHA &&
		ts->_hoops_GAHA->list)
		return true;

	return false;
}


void _hoops_IHCA (H3DData alter * h3ddata)
{
	if (h3ddata->_hoops_CSC)
		SET_MEMORY (h3ddata->_hoops_CSC, sizeof(H3DCache), 0x5c);
}




/*
 * _hoops_PGAA
 *
 * _hoops_RGPA _hoops_CHCA _hoops_PPR _hoops_RPR _hoops_IS _hoops_IRPR _hoops_SHCA _hoops_GCHA.
 */
void _hoops_GICA (
	H3DData const *h3ddata,
	int count,
	int _hoops_RICA,
	H3DPRIMITIVETYPE Type,
	int _hoops_AICA)
{
	// _hoops_SGR _hoops_RH _hoops_PICA (_hoops_HICA _hoops_GRS _hoops_IICA _hoops_RGR _hoops_CICA _hoops_PPR _hoops_SICA _hoops_SGGR)
	Display_Context *dc = const_cast<Display_Context*>(h3ddata->dc);
	switch (Type)
	{
		case H3DPT_TRIANGLESTRIP :
		case H3DPT_TRIANGLELIST :
			if (_hoops_RICA == _hoops_GCCA)
				_hoops_RCCA(_hoops_ACCA) += (count - _hoops_AICA);
			else
				_hoops_RCCA(_hoops_PCCA) += (count - _hoops_AICA);
			break;

		case H3DPT_LINESTRIP :
		case H3DPT_LINELIST :
			if (_hoops_RICA == _hoops_GCCA)
				_hoops_RCCA(_hoops_HCCA) += count;
			else
				_hoops_RCCA(_hoops_ICCA) += count;
			break;

		case H3DPT_POINTLIST :
			if (_hoops_RICA == _hoops_GCCA)
				_hoops_RCCA(_hoops_CCCA) += count;
			else
				_hoops_RCCA(_hoops_SCCA) += count;
			break;

		case H3DPT_TRIANGLEFAN :
			break;

		default:
			ASSERT(0);
	}
}

/*
 * _hoops_PGAA
 *
 * _hoops_GSCA _hoops_RH _hoops_RSCA _hoops_ASCA _hoops_HAPR _hoops_IH _hoops_HPPA _hoops_GHC _hoops_CCA _hoops_GPHA _hoops_PSCA.
 * _hoops_HSCA _hoops_ISCA _hoops_RH _hoops_PSHR _hoops_CSCA _hoops_APGR _hoops_IIGR _hoops_RRGR _hoops_HCR _hoops_IAPR.
 */
void _hoops_SSCA(
	H3DData alter *h3ddata,
	Net_Rendition const & nr,
	H3DVertexBufferCache *_hoops_GGSA,
	_hoops_IAPA const *_hoops_CAPA,
	int _hoops_RGSA,
	int _hoops_RICA,
	H3DPRIMITIVETYPE Type,
	int _hoops_AICA)
{
	H3DShader *_hoops_RSR = h3ddata->_hoops_CSC->_hoops_AGSA;
	do
	{
		// _hoops_SIIR _hoops_GHC, _hoops_PGSA, _hoops_PPR _hoops_SSS _hoops_SPS _hoops_HPPA _hoops_IPPA _hoops_ARP
		if (_hoops_RICA == _hoops_GCCA) {
			_hoops_RSR->_hoops_HAPA (_hoops_CAPA);
		}
		else {
			_hoops_RSR->_hoops_CHPA (nr, _hoops_CAPA);
		}
		_hoops_GGSA->_hoops_HGSA(h3ddata, Type, _hoops_RGSA);
		if (_hoops_CAPA != null)
			_hoops_CAPA = _hoops_CAPA->next;

		// _hoops_SGR _hoops_CAPR
		_hoops_GICA (h3ddata, _hoops_RGSA, _hoops_RICA, Type, _hoops_AICA);

	} while (_hoops_CAPA != null);

	// _hoops_IGSA _hoops_ASCA
	_hoops_GGSA->_hoops_CGSA();
}

void _hoops_SGSA(
	H3DData alter *h3ddata,
	Net_Rendition const & nr,
	H3DIndexBufferCache *_hoops_GRSA,
	_hoops_IAPA const *_hoops_CAPA,
	int _hoops_RRSA,
	int _hoops_RGSA,
	int _hoops_RICA,
	H3DPRIMITIVETYPE Type,
	int _hoops_AICA,
	bool _hoops_ARSA)
{
	H3DShader *_hoops_RSR = h3ddata->_hoops_CSC->_hoops_AGSA;
	H3DCULL _hoops_PRSA = h3ddata->_hoops_CSC->_hoops_HRSA;
	H3DCULL _hoops_IRSA = H3DCULL_NONE;
	H3DCULL _hoops_CRSA = H3DCULL_NONE;
	int i = 0;


	if (_hoops_ARSA == true) {
		//_hoops_SRSA: _hoops_GASA: _hoops_RGR _hoops_RRGR _hoops_CGH _hoops_SHH _hoops_RASA _hoops_CCA _hoops_IRS _hoops_AASA _hoops_IS _hoops_PASA

		if (!BIT (nr->transform_rendition->matrix->data.flags, _hoops_HASA))
			HI_Validate_Matrix_NEG3X3((_hoops_HRPA alter *)&nr->transform_rendition->matrix->data);

		bool _hoops_IASA = BIT (nr->transform_rendition->matrix->data._hoops_RAGR, _hoops_CASA);

		if ((_hoops_IASA && BIT(nr->transform_rendition->heuristics,_hoops_SASA)) ||
			(!_hoops_IASA &&	BIT(nr->transform_rendition->heuristics,_hoops_GPSA))) {
			_hoops_IRSA = H3DCULL_CCW;
			_hoops_CRSA = H3DCULL_CW;
		}
		else {
			_hoops_IRSA = H3DCULL_CW;
			_hoops_CRSA = H3DCULL_CCW;
		}
	}

	for (i = 0; i < 2; i++) {	//_hoops_PGCR-_hoops_RPSA _hoops_APSA _hoops_HAPR
		bool _hoops_PPSA = false;

		if (_hoops_ARSA) {
			/* _hoops_RH "_hoops_HPSA != _hoops_IPSA" _hoops_ISPR _hoops_HRGR _hoops_CPSA _hoops_RH _hoops_PSHR _hoops_GAR:
			 * (_hoops_IPSA == _hoops_SPSA || _hoops_GHSA == _hoops_IPSA)
			 */
			if (i == 0 && _hoops_CRSA != _hoops_PRSA) {
				_hoops_RHSA(h3ddata,_hoops_IRSA);
				_hoops_AHSA(h3ddata, nr, T_FACES, _hoops_RSR);
			}
			else if (i == 1 && _hoops_IRSA != _hoops_PRSA) {
				_hoops_RHSA(h3ddata,_hoops_CRSA);
				_hoops_PHSA(h3ddata, nr, T_FACES, _hoops_RSR);
			}
			else
				_hoops_PPSA = true;
		}
		else
			i = 2;	//_hoops_HAR _hoops_PGCR-_hoops_RPSA, _hoops_HIS _hoops_HHSA _hoops_IRS _hoops_IHSA _hoops_RAS _hoops_SPR _hoops_IPGR

		if (!_hoops_PPSA) do {
			// _hoops_SIIR _hoops_GHC, _hoops_PGSA, _hoops_PPR _hoops_SSS _hoops_SPS _hoops_HPPA _hoops_IPPA _hoops_ARP
			if (_hoops_RICA == _hoops_GCCA)
				_hoops_RSR->_hoops_HAPA (_hoops_CAPA);
			else
				_hoops_RSR->_hoops_CHPA (nr, _hoops_CAPA);

			_hoops_GRSA->_hoops_CHSA(h3ddata, Type, _hoops_RRSA, _hoops_RGSA);

			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;

			// _hoops_SGR _hoops_CAPR
			_hoops_GICA (h3ddata, _hoops_RGSA, _hoops_RICA, Type, _hoops_AICA);
		} while (_hoops_CAPA != null);
	}
	if (_hoops_ARSA)
		_hoops_RHSA(h3ddata, _hoops_PRSA);

	// _hoops_IGSA _hoops_ASCA
	_hoops_GRSA->_hoops_CGSA();
}


/*
 * _hoops_PGAA
 */
H3DTexture *_hoops_SHSA (H3DData *h3ddata, int w, int h)
{
	// _hoops_GISA _hoops_IRS _hoops_RISA _hoops_SSRA _hoops_HH...
	H3DTexture *texture;
	bool result = h3ddata->_hoops_GSCR->CreateTexture(w, h, 1,
		0, H3DFMT_A8R8G8B8, &texture);

	if (result)
	{
		// _hoops_AISA _hoops_PISA _hoops_HISA _hoops_HIS _hoops_RI _hoops_SHR _hoops_IISA _hoops_GGSR _hoops_RH _hoops_PSHR.
		srand(31415927);

		// _hoops_CHSR _hoops_CISA _hoops_SCH _hoops_GGR
		unsigned char *_hoops_SISA;
		int pitch;
		if (texture->Lock(null, &_hoops_SISA, &pitch))
		{
			for (int y = 0; y < w; ++y)
			{
				unsigned char *row = _hoops_SISA + y * pitch;

				for (int x = 0; x < h; ++x)
				{
					unsigned char *pixel = row + x * 4;

					// _hoops_GCSA _hoops_RCSA
					float theta = 2 * 3.1415927f * rand() / RAND_MAX;

					// _hoops_ACSA, _hoops_PCSA. _hoops_HCSA _hoops_IRS 2x2 _hoops_ICSA _hoops_HPP _hoops_CCSA.
					pixel[1] = 255 * (0.5f * sin(theta) + 0.5f);
					pixel[2] = 255 * (0.5f * cos(theta) + 0.5f);
					pixel[3] = 255 * (0.5f * cos(theta) + 0.5f);
					pixel[0] = 255 * (0.5f * -sin(theta) + 0.5f);
				}
			}

			texture->Unlock();
		}
	}

	return texture;
}

// _hoops_SCSA _hoops_PIH - _hoops_HGRR-_hoops_GSSA _hoops_RSSA _hoops_ASSA _hoops_RH _hoops_HPI _hoops_IGRR.
static const Vector _hoops_PSSA[4] =
{
	Vector(0.800475f, -0.391526f, 0.0f),
	Vector(0.401211f, 0.644555f, 0.0f),
	Vector(-0.591372f, -0.872561f, 0.0f),
	Vector(-0.610313f, 0.619532f, 0.0f),
};

static const Vector _hoops_HSSA[8] =
{
	Vector(-0.0267563f, -0.714192f, 0.0f),
	Vector(0.826619f, 0.0210104f, 0.0f),
	Vector(-0.347736f, 0.827068f, 0.0f),
	Vector(-0.79797f, 0.307575f, 0.0f),
	Vector(0.349483f, 0.899464f, 0.0f),
	Vector(0.0169128f, -0.0749364f, 0.0f),
	Vector(-0.675576f, -0.625112f, 0.0f),
	Vector(0.655024f, -0.640877f, 0.0f),
};

static const Vector _hoops_ISSA[16] =
{
	Vector(0.269998f, -0.146692f, 0.0f),
	Vector(-0.15806f, 0.900334f, 0.0f),
	Vector(0.722349f, -0.141793f, 0.0f),
	Vector(-0.860536f, -0.13521f, 0.0f),
	Vector(0.410752f, 0.298909f, 0.0f),
	Vector(-0.275256f, 0.143427f, 0.0f),
	Vector(0.216773f, -0.716069f, 0.0f),
	Vector(0.478192f, 0.80605f, 0.0f),
	Vector(-0.524234f, -0.711116f, 0.0f),
	Vector(-0.499143f, 0.547045f, 0.0f),
	Vector(-0.932263f, 0.351563f, 0.0f),
	Vector(-0.204112f, -0.401199f, 0.0f),
	Vector(0.854885f, 0.391317f, 0.0f),
	Vector(0.674279f, -0.675606f, 0.0f),
	Vector(-0.172797f, -0.995818f, 0.0f),
	Vector(-0.000825383f, 0.484858f, 0.0f),
};

// _hoops_SCSA _hoops_PIH - _hoops_HGRR-_hoops_GSSA _hoops_RSSA _hoops_ASSA _hoops_RH _hoops_HPI _hoops_IGRR.
static const Vector _hoops_CSSA[32] =
{
	Vector(-0.838396f,    0.20076f, 0.0f),
	Vector(0.602766f,    -0.251304f, 0.0f),
	Vector(0.476738f,     0.653455f, 0.0f),
	Vector(0.126941f,     0.278499f, 0.0f),
	Vector(0.377594f,    -0.099005f, 0.0f),
	Vector(.0707081f,     0.901007f, 0.0f),
	Vector(-0.50523f,    -0.627102f, 0.0f),
	Vector(0.341874f,     0.439791f, 0.0f),
	Vector(-0.01734f,    -0.652809f, 0.0f),
	Vector(0.862931f,    -0.327732f, 0.0f),
	Vector(0.128775f,    -0.235758f, 0.0f),
	Vector(0.400335f,     0.843872f, 0.0f),
	Vector(0.419712f,    -0.717652f, 0.0f),
	Vector(0.176788f,    -0.120496f, 0.0f),
	Vector(0.234248f,     0.914175f, 0.0f),
	Vector(.0834493f,     0.658834f, 0.0f),
	Vector(0.180814f,     -0.87013f, 0.0f),
	Vector(0.947666f,     0.304094f, 0.0f),
	Vector(0.542242f,    0.0286047f, 0.0f),
	Vector(0.214377f,    -0.855337f, 0.0f),
	Vector(0.400281f,     0.192536f, 0.0f),
	Vector(0.927606f,    -0.131792f, 0.0f),
	Vector(0.758801f,    0.0036636f, 0.0f),
	Vector(-0.86557f,    -0.448685f, 0.0f),
	Vector(-0.84745f,     0.545225f, 0.0f),
	Vector(0.722535f,     0.498805f, 0.0f),
	Vector(0.564396f,    -0.409047f, 0.0f),
	Vector(0.143581f,     0.186753f, 0.0f),
	Vector(0.770621f,    -0.609604f, 0.0f),
	Vector(0.281808f,    -0.440396f, 0.0f),
	Vector(0.288139f,    -0.468591f, 0.0f),
	Vector(0.567568f,     0.615368f, 0.0f),
};

/*
* _hoops_PGAA: _hoops_SSSA _hoops_GGGP _hoops_RGGP _hoops_HII _hoops_AGGP _hoops_HGRR _hoops_RSSA.
*/
local void _hoops_PGGP(int const size, const Vector *_hoops_HGGP, float *_hoops_IGGP, float *weights, float &_hoops_CGGP)
{
	// _hoops_GHPA _hoops_SGCR _hoops_SGGP
	_hoops_CGGP = 0;

	for (int i = 0; i < size; ++i) {
		// _hoops_PS _hoops_GRGP _hoops_RH _hoops_HGRR _hoops_SPCR _hoops_PPR _hoops_GHCR _hoops_RSSA _hoops_GGR _hoops_RRGP _hoops_IS _hoops_HGCR _hoops_PGCR _hoops_ARGP _hoops_RIR _hoops_PRGP.
		*_hoops_IGGP++ = _hoops_HGGP[i].x;
		*_hoops_IGGP++ = _hoops_HGGP[i].y;

		// _hoops_HRGP _hoops_RRI _hoops_GGR _hoops_RH _hoops_IRGP, _hoops_CRGP _hoops_HPGR _hoops_RH _hoops_SPPR
		float const r = 1-_hoops_HGGP[i].length();

		// _hoops_SRGP
		float const w = 3*r*r - 2*r*r*r;
		*weights++ = w;

		// _hoops_GAGP _hoops_SGCR _hoops_RAGP _hoops_GGR _hoops_AAGP _hoops_GAR _hoops_PRAR _hoops_IH _hoops_PAGP _hoops_HAGP.
		_hoops_CGGP += w;
	}
}

/*
* _hoops_PGAA: _hoops_HCGA _hoops_AASR _hoops_IAGP _hoops_IS _hoops_RH _hoops_RAGA _hoops_SRHR _hoops_GRP _hoops_RH _hoops_RAGA _hoops_HCH _hoops_HH.
*/
void _hoops_CAGP(H3DData *h3ddata, H3DRenderTarget *target, H3DTexture *depth_texture, bool opaque, bool scaled)
{
	ASSERT(h3ddata->post);
	H3DPost *post = h3ddata->post;

	float radius = 8.0f;
	float _hoops_IIRA = (scaled ? 50.0f : 0.0f) * _hoops_CIRA;
	float _hoops_SAGP = radius;

	//_hoops_GPGP _hoops_ICH _hoops_CCH, _hoops_RH _hoops_AIIR _hoops_RPGP _hoops_HRGR _hoops_APGP _hoops_PPGP _hoops_GPP.
	//_hoops_PS _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_GHGA _hoops_RHAA _hoops_AGI _hoops_HPGP _hoops_ICH
	ASSERT (!h3ddata->_hoops_RHH.mode);
	_hoops_IPGP (h3ddata, false);

	// _hoops_CPGP _hoops_SPGP _hoops_HRGR _hoops_SGGA _hoops_GAR 1/(1+_hoops_GHGP^2), _hoops_SCH _hoops_RHGP _hoops_AHGP _hoops_HPGR 1.0. _hoops_PHGP _hoops_SR _hoops_HHGP _hoops_SCH _hoops_GAPA
	// _hoops_RH _hoops_GSSR _hoops_HCH _hoops_GIRA _hoops_CSRA _hoops_SPGP, _hoops_PPR _hoops_IRS _hoops_IHGP _hoops_IIPR _hoops_CHGP.
	float const _hoops_SHGP = _hoops_CIRA * 25.0f * _hoops_AHIA(1.0f, h3ddata->dc->options._hoops_GIGP);
	float _hoops_RIGP = 8.0f * _hoops_IAAA(1.0f, h3ddata->dc->options._hoops_GIGP);

	H3DPost::_hoops_AGSA const _hoops_RSR = static_cast<H3DPost::_hoops_AGSA>(h3ddata->_hoops_II._hoops_AIGP);

	if (H3DConstantTable *_hoops_AIPA = post->_hoops_PIGP(H3DPost::_hoops_HIGP, _hoops_RSR)) {

		// _hoops_SIIR _hoops_HH.
		const unsigned long _hoops_IIGP = _hoops_AIPA->GetSamplerIndex("Depth");
		if (_hoops_IIGP < _hoops_CIGP) {
			// _hoops_AHH: _hoops_SIGP: _hoops_GCGP _hoops_RCGP _hoops_HRGR _hoops_ACGP _hoops_ARI, _hoops_HIS _hoops_SR _hoops_HHSA _hoops_SCH _hoops_IS _hoops_PCGP _hoops_GGR
			//   _hoops_RH _hoops_CI _hoops_PPR _hoops_GGR _hoops_HCGP
			_hoops_SCCR(h3ddata, _hoops_IIGP, depth_texture);
			_hoops_GRPA(h3ddata, _hoops_IIGP, H3DTEXF_POINT, H3DTEXF_NONE, H3DTADDRESS_CLAMP);
		}

		// _hoops_ICGP _hoops_HPP _hoops_CCGP _hoops_PAPA
		Vector const *_hoops_SCGP = _hoops_ISSA;
		int _hoops_GSGP = 16;

		// _hoops_GPPR _hoops_IIPR _hoops_IS _hoops_IHRA _hoops_CCGP _hoops_PAPA. _hoops_PS _hoops_AA 1, 4, _hoops_PPR 8 _hoops_ARH _hoops_IIGR _hoops_IGPR _hoops_IIHA _hoops_GPP _hoops_PAPA.
		switch (h3ddata->post->_hoops_RSGP(_hoops_RSR)) {
		case H3DPost::_hoops_ASGP :
			// _hoops_PSGP-_hoops_PSAA _hoops_HSGP
			_hoops_SAGP *= 0.5f;
			_hoops_IIRA = 0.0f;

			// _hoops_ISGP _hoops_RGGP
			_hoops_SCGP = _hoops_PSSA;
			_hoops_GSGP = 4;
			break;

		case H3DPost::_hoops_CSGP :
			// _hoops_SSGP _hoops_HSGP
			_hoops_SAGP *= 0.5f;

			// _hoops_ISGP _hoops_RGGP
			_hoops_SCGP = _hoops_HSSA;
			_hoops_GSGP = 8;

			// _hoops_GGRP _hoops_RGRP _hoops_AGRP _hoops_GGR '_hoops_PGRP' _hoops_CCA _hoops_AGRP _hoops_GGR _hoops_PSAA
			_hoops_RIGP *= 3.0f;
			break;

		case H3DPost::_hoops_HGRP :
			// _hoops_ISGP _hoops_RGGP
			_hoops_SCGP = _hoops_ISSA;
			_hoops_GSGP = 16;
			break;

		/* _hoops_SRPR _hoops_GAPR _hoops_IGRP
		_hoops_AGIR _hoops_CGRP::_hoops_SGRP :
			// _hoops_ISGP _hoops_RGGP
			_hoops_RGGP = _hoops_GRRP;
			_hoops_RRRP = 32;
			_hoops_IHSA;
		*/
		default :
			// _hoops_ARRP _hoops_IS _hoops_AA.
			;
		}

		// _hoops_RAP _hoops_PPPR _hoops_IGIR _hoops_HIS _hoops_SR _hoops_PAH _hoops_CSRA _hoops_ISAR _hoops_AII _hoops_PRRP.
		float _hoops_HRRP[2] = {
			radius * h3ddata->_hoops_HSAA / depth_texture->_hoops_IRRP,
			radius * h3ddata->_hoops_ISAA / depth_texture->_hoops_CRRP
		};
		_hoops_AIPA->SetVector("OneOverTexelSize", _hoops_HRRP, 2);

		// _hoops_GISA _hoops_SRRP. _hoops_GARP _hoops_SR _hoops_RRP 32 _hoops_PPR 16-_hoops_RARP _hoops_SRRP.
		float _hoops_IGGP[32*2];
		float weights[32];
		float total;
		_hoops_PGGP(_hoops_GSGP, _hoops_SCGP, _hoops_IGGP, weights, total);
		_hoops_AIPA->SetVectorArray("Taps", _hoops_IGGP, 16);
		_hoops_AIPA->SetVectorArray("Weights", weights, 8);
		total = _hoops_RIGP/total;
		_hoops_AIPA->SetFloat("OutputScale", total);

		// _hoops_RAP _hoops_RII _hoops_A
		_hoops_AIPA->SetFloat("Strength", _hoops_SHGP);
		_hoops_AIPA->SetFloat("MaxRadius", _hoops_SAGP);
		_hoops_AIPA->SetFloat("DepthScale", _hoops_IIRA);

		const unsigned long _hoops_AARP = _hoops_AIPA->GetSamplerIndex("Jitter");
		if (_hoops_AARP < _hoops_CIGP) {
			// _hoops_AHH: _hoops_SIGP: _hoops_GCGP _hoops_RCGP _hoops_HRGR _hoops_ACGP _hoops_ARI, _hoops_HIS _hoops_SR _hoops_HHSA _hoops_SCH _hoops_IS _hoops_PARP _hoops_GGR
			//   _hoops_RH _hoops_CI _hoops_PPR _hoops_GGR _hoops_HCGP
			int const _hoops_HARP = 4;
			if (!h3ddata->_hoops_II._hoops_HI)
				h3ddata->_hoops_II._hoops_HI = _hoops_SHSA(h3ddata, _hoops_HARP, _hoops_HARP);

			if (h3ddata->_hoops_II._hoops_HI) {
				// _hoops_IARP _hoops_RI
				_hoops_SCCR(h3ddata, _hoops_AARP, h3ddata->_hoops_II._hoops_HI);
				_hoops_GRPA(h3ddata, _hoops_AARP, H3DTEXF_POINT, H3DTEXF_NONE, H3DTADDRESS_WRAP);

				// _hoops_IARP _hoops_SAAA _hoops_IH _hoops_CARP
				float const _hoops_SARP[] = {
					static_cast<float>(depth_texture->_hoops_IRRP) / _hoops_HARP,
					static_cast<float>(depth_texture->_hoops_CRRP) / _hoops_HARP,
				};
				_hoops_AIPA->SetVector("JitterScale", _hoops_SARP, 2);
			}
		}

		if (opaque) {
			ENSURE_TRANSPARENCY(h3ddata, false);
			_hoops_GPRP(h3ddata, H3DMASK_RGBA);
		}
		else {
			// _hoops_RPRP _hoops_APRP _hoops_IAPR
			ENSURE_TRANSPARENCY(h3ddata, true);
			_hoops_PPRP(h3ddata, H3DBLEND_ZERO, H3DBLEND_INVSRCALPHA);
			_hoops_GPRP(h3ddata, H3DMASK_RGB);
		}

		post->_hoops_HPRP(target, _hoops_RSR, 0.0f, null, depth_texture);

		// _hoops_IPRP _hoops_CPRP
		_hoops_PPRP(h3ddata, H3DBLEND_SRCALPHA, H3DBLEND_INVSRCALPHA);
	}
}

/*
* _hoops_PGAA. _hoops_GSRA _hoops_IRS _hoops_SPRP _hoops_RGGP _hoops_GHRP _hoops_IH _hoops_HCH _hoops_RHRP. _hoops_AHRP 8*2 _hoops_PHRP _hoops_IH _hoops_ARGP, 8 _hoops_IH _hoops_HHRP
*/
local void _hoops_IHRP(H3DTexture const *depth_texture, bool y, float *_hoops_IGGP, float *weights)
{
	static const Vector _hoops_SCGP[] = {
		Vector (-3.0f, 0.0f, 1.0f/64.0f),
		Vector (-2.0f, 0.0f, 6.0f/64.0f),
		Vector (-1.0f, 0.0f, 15.0f/64.0f),
		Vector (+1.0f, 0.0f, 15.0f/64.0f),
		Vector (+2.0f, 0.0f, 6.0f/64.0f),
		Vector (+3.0f, 0.0f, 1.0f/64.0f),
	};

	float const _hoops_CHRP = 1.0f / depth_texture->_hoops_IRRP;
	float const _hoops_SHRP = 1.0f / depth_texture->_hoops_CRRP;

	for (int i = 0; i < 6; ++i) {
		// _hoops_GSRA _hoops_ARGP _hoops_GIRP
		*_hoops_IGGP++ = y ? 0.0f : _hoops_SCGP[i].x * _hoops_CHRP;
		*_hoops_IGGP++ = y ? _hoops_SCGP[i].x * _hoops_SHRP : 0.0f;

		// _hoops_GSRA _hoops_HHRP _hoops_GIRP
		*weights++ = _hoops_SCGP[i].z;
	}

	// _hoops_GHPA _hoops_RIRP _hoops_AIRP
	for (int i = 6; i < 8; ++i) {
		*_hoops_IGGP++ = 0.0f;
		*_hoops_IGGP++ = 0.0f;
		*weights++ = 0.0f;
	}
}

void _hoops_PIRP(H3DData *h3ddata, H3DTexture *_hoops_HIRP, H3DTexture *_hoops_IIRP)
{
	H3DPost *post = h3ddata->post;

	// _hoops_CIRP...
	if (H3DConstantTable *_hoops_AIPA = post->_hoops_PIGP(H3DPost::_hoops_HIGP, H3DPost::_hoops_SIRP)) {
		const unsigned long _hoops_PCI = _hoops_AIPA->GetSamplerIndex("Sampler");
		if (_hoops_PCI < _hoops_CIGP) {

			// _hoops_GCRP _hoops_IS _hoops_RCRP _hoops_GHAR _hoops_ACRP _hoops_GAPA _hoops_PCRP _hoops_PPR _hoops_HCRP _hoops_IH _hoops_ICRP _hoops_CCRP
			float const _hoops_SCRP = 0.003f;
			_hoops_AIPA->SetFloat("Tolerance", _hoops_CIRA / _hoops_SCRP);

			float _hoops_IGGP[8*2];
			float weights[8];

			// _hoops_GSRP _hoops_RIH
			_hoops_IHRP(_hoops_HIRP, false, _hoops_IGGP, weights);
			_hoops_AIPA->SetVectorArray("Taps", _hoops_IGGP, 4);
			_hoops_AIPA->SetVectorArray("Weights", weights, 2);
			_hoops_SCCR(h3ddata, _hoops_PCI, _hoops_HIRP);
			_hoops_GRPA(h3ddata, _hoops_PCI, H3DTEXF_POINT, H3DTEXF_NONE, H3DTADDRESS_CLAMP);
			post->_hoops_HPRP(_hoops_IIRP, H3DPost::_hoops_SIRP, 0.0f, null, _hoops_HIRP);

			// _hoops_RSRP _hoops_RIH
			_hoops_IHRP(_hoops_IIRP, true, _hoops_IGGP, weights);
			_hoops_AIPA->SetVectorArray("Taps", _hoops_IGGP, 4);
			_hoops_AIPA->SetVectorArray("Weights", weights, 2);
			_hoops_SCCR(h3ddata, _hoops_PCI, _hoops_IIRP);
			post->_hoops_HPRP(_hoops_HIRP, H3DPost::_hoops_SIRP, 0.0f, null, _hoops_HIRP);

			_hoops_ASRP(h3ddata, _hoops_PCI);
		}
	}
}

#define _hoops_PSRP 255.0f
void _hoops_HSRP(float value, float *result)
{
	float shift[4] = {1.0f, _hoops_PSRP, _hoops_PSRP*_hoops_PSRP,  _hoops_PSRP*_hoops_PSRP*_hoops_PSRP};
	float mask[4] = {1.0f/_hoops_PSRP, 1.0f/_hoops_PSRP, 1.0f/_hoops_PSRP, 0.0};

	float _hoops_ISRP[4] = {value * shift[0], value * shift[1], value * shift[2], value * shift[3]};
	_hoops_ISRP[0] = _hoops_ISRP[0] - floor(_hoops_ISRP[0]);
	_hoops_ISRP[1] = _hoops_ISRP[1] - floor(_hoops_ISRP[1]);
	_hoops_ISRP[2] = _hoops_ISRP[2] - floor(_hoops_ISRP[2]);
	_hoops_ISRP[3] = _hoops_ISRP[3] - floor(_hoops_ISRP[3]);

	result[0] = _hoops_ISRP[0] - mask[0] * _hoops_ISRP[1];
	result[1] = _hoops_ISRP[1] - mask[1] * _hoops_ISRP[2];
	result[2] = _hoops_ISRP[2] - mask[2] * _hoops_ISRP[3];
	result[3] = _hoops_ISRP[3] - mask[3] * _hoops_ISRP[3];
}

float _hoops_CSRP(float *packed)
{
	float shift[] = {1.0f, 1.0f/_hoops_PSRP, 1.0f/(_hoops_PSRP*_hoops_PSRP), 1.0f/(_hoops_PSRP*_hoops_PSRP*_hoops_PSRP)};
	float _hoops_SSRP =
		packed[0] * shift[0] +
		packed[1] * shift[1] +
		packed[2] * shift[2] +
		packed[3] * shift[3];
	return _hoops_SSRP;
}

/*
* _hoops_PGAA. _hoops_GGAP _hoops_IS _hoops_ARP _hoops_GH _hoops_HCH _hoops_HH _hoops_RGAP _hoops_IH "_hoops_HCH _hoops_AGI", _hoops_HAS._hoops_IAS. _hoops_AGAP
* _hoops_RHAA _hoops_AGI _hoops_PGAP _hoops_HGAP _hoops_IRS _hoops_HCH _hoops_HH _hoops_IH _hoops_RH _hoops_HIRA _hoops_GAR _hoops_CIIA.
*/
bool _hoops_IGAP(H3DData *h3ddata, int _hoops_CGAP)
{
	bool _hoops_IA = false;
	ASSERT(h3ddata->_hoops_II._hoops_SGAP && h3ddata->_hoops_GRAP > 1 /*&& _hoops_RRAP->_hoops_ARAP*/);
	ASSERT(h3ddata->post);
	//_hoops_AGHR(_hoops_RRAP->_hoops_PRAP._hoops_HRAP == _hoops_IRAP);
	ASSERT(h3ddata->_hoops_CRAP != _hoops_SRAP);
	H3DPost *post = h3ddata->post;

	if (_hoops_CGAP == 0) {
		// _hoops_HRAP _hoops_GAAP _hoops_RAAP _hoops_HII _hoops_AAAP _hoops_PAAP
		if (h3ddata->_hoops_II.depth_texture)
			h3ddata->post->_hoops_HAAP(&h3ddata->_hoops_II.depth_texture);

		// _hoops_GISA _hoops_HCH _hoops_HH.

		// _hoops_GISA _hoops_PIS _hoops_HCH _hoops_HH
		h3ddata->_hoops_II.depth_texture = post->_hoops_IAAP(h3ddata->render_target->_hoops_IRRP, h3ddata->render_target->_hoops_CRRP, H3DFMT_R32F);
		if (h3ddata->_hoops_II.depth_texture) {
			// _hoops_CAAP _hoops_SAAP.
			h3ddata->_hoops_GSCR->_hoops_GPAP(h3ddata->_hoops_II.depth_texture);
			_hoops_RPAP (h3ddata, true);
			_hoops_GPRP (h3ddata, H3DMASK_RGBA);
			_hoops_IPGP (h3ddata, false);

			// _hoops_AHH: _hoops_CAAP _hoops_IS _hoops_PIRA _hoops_GPP _hoops_RH _hoops_APAP _hoops_PPAP _hoops_IIGR 1.0, _hoops_PGAP _hoops_HRGR _hoops_HPAP _hoops_IH _hoops_IPAP _hoops_GGSR _hoops_CPAP _hoops_HII _hoops_HCH _hoops_AGI.
			// _hoops_SPAP, _hoops_GHAP'_hoops_GHGP _hoops_ISPR _hoops_SGS _hoops_RGR _hoops_RHAP _hoops_RH _hoops_RPHR _hoops_AHAP _hoops_CCA _hoops_RH _hoops_PHAP _hoops_HHAP.
			int _hoops_IHAP = 0xfefefefe;
			if (h3ddata->_hoops_II._hoops_PRI) {
				float packed[4];
				_hoops_HSRP(254.0f/255.0f, packed);
				_hoops_IHAP = _hoops_CHAP(h3ddata->_hoops_SHAP, packed[0]*255, packed[1]*255, packed[2]*255, packed[3]*255);
			}
			h3ddata->_hoops_GSCR->Clear(H3DCLEAR_TARGET, _hoops_IHAP, 0, 0);

			// _hoops_IPRP _hoops_HAIR _hoops_SAAP, _hoops_ARP _hoops_HCH _hoops_HH _hoops_GAR _hoops_GIAP _hoops_RIAP
			h3ddata->_hoops_GSCR->_hoops_GPAP(h3ddata->render_target, h3ddata->depth_stencil, h3ddata->_hoops_II.depth_texture);

			// _hoops_AIAP _hoops_HCH _hoops_PIAP _hoops_IS _hoops_SHH _hoops_HIAP _hoops_IS _hoops_HGCR _hoops_RH _hoops_GGI _hoops_IIAP _hoops_HGSR
			_hoops_CIAP(h3ddata, false);

			// _hoops_CSH _hoops_SARA _hoops_HIS _hoops_SR _hoops_PAH _hoops_SSS _hoops_SPR _hoops_SPHR.
			h3ddata->_hoops_II._hoops_SPH = null;

			// _hoops_SAP _hoops_GPP _hoops_HCH _hoops_HH _hoops_RGAP
			h3ddata->_hoops_II.mode = true;
			_hoops_IA = true;
		}
		else
		{
			h3ddata->_hoops_II.mode = false;
			h3ddata->_hoops_II._hoops_SGAP = 0;
		}
	}
	else {
		h3ddata->_hoops_GSCR->_hoops_GPAP(h3ddata->render_target, h3ddata->depth_stencil, h3ddata->_hoops_II.depth_texture);
	}

	return _hoops_IA;
}

/*
* _hoops_PGAA: _hoops_SIAP _hoops_GCAP _hoops_HSH _hoops_IS _hoops_AIIR _hoops_RCAP _hoops_IIGR _hoops_IRS _hoops_RAGA _hoops_SRHR.
*/
void _hoops_ACAP(H3DData *h3ddata, H3DTexture *_hoops_PCAP, H3DTexture *depth, float _hoops_HCAP, float _hoops_ICAP)
{
	ASSERT(h3ddata->post);
	H3DPost& post = *h3ddata->post;

	if ( H3DConstantTable *_hoops_AIPA = post._hoops_PIGP( H3DPost::_hoops_HIGP, H3DPost::_hoops_CCAP ) ) {

		// _hoops_SIIR _hoops_AI.
		if ( const unsigned long _hoops_PCI = _hoops_AIPA->GetSamplerIndex("Depth") < _hoops_CIGP ) {
			// _hoops_AHH: _hoops_SIGP: _hoops_GCGP _hoops_RCGP _hoops_HRGR _hoops_ACGP _hoops_ARI, _hoops_HIS _hoops_SR _hoops_HHSA _hoops_SCH _hoops_IS _hoops_PCGP _hoops_GGR 
			//   _hoops_RH _hoops_CI _hoops_PPR _hoops_GGR _hoops_HCGP 
			_hoops_SCCR(h3ddata, 0, depth);
			_hoops_GRPA(h3ddata, 0, H3DTEXF_POINT, H3DTEXF_NONE, H3DTADDRESS_CLAMP);
		}

		// _hoops_SSSA _hoops_CSRA _hoops_PPR _hoops_CHAA _hoops_IS _hoops_ARCR _hoops_HCH _hoops_CRGR _hoops_GCAP _hoops_SCAP.
		float const _hoops_GSAP[2] = 
		{
			// _hoops_RSAP _hoops_CSRA
			1.0f / (_hoops_ICAP - _hoops_HCAP),
			// _hoops_RSAP _hoops_CHAA
			-_hoops_HCAP / (_hoops_ICAP - _hoops_HCAP),
		};

		_hoops_AIPA->SetVector("ScaleAndBias", _hoops_GSAP, 2 );
		_hoops_AIPA->SetFloat("DepthScale", h3ddata->_hoops_II._hoops_SPH->_hoops_SRIR * 2.0f * _hoops_CIRA);

		post._hoops_HPRP(_hoops_PCAP, H3DPost::_hoops_CCAP, 0.0f, null, depth);
	}
}

/*
* _hoops_PGAA. _hoops_ASAP _hoops_PSAP _hoops_HCH _hoops_HH _hoops_RGAP _hoops_PPR _hoops_GHAA _hoops_RH _hoops_AGI.
*/
void _hoops_HSAP(Net_Rendition const &nr)
{
	H3DData *h3ddata = H3DNRD(nr);

	ASSERT(h3ddata->post);
	H3DPost *post = h3ddata->post;

	// _hoops_CGP _hoops_ISAP _hoops_CSAP _hoops_AIS, _hoops_SR _hoops_HS _hoops_ISAP _hoops_IS _hoops_AA.
	if (!h3ddata->_hoops_II._hoops_SGAP || 
		!h3ddata->_hoops_II.mode ||
		!h3ddata->_hoops_II._hoops_SPH)
		return;

	H3D_TRACE(h3ddata, "Postprocess depth effects");

	// _hoops_SAP _hoops_PSAP _hoops_HCH _hoops_RGAP.
	h3ddata->_hoops_II.mode = false;

	// _hoops_SSAP _hoops_HH
	H3DTexture *depth_texture = h3ddata->_hoops_II.depth_texture;
	h3ddata->_hoops_II.depth_texture = null;

	if ( post->_hoops_GGPP() ) {
		// _hoops_HSRR _hoops_RGPP-_hoops_PHAP _hoops_HCH _hoops_AI, _hoops_AIIR _hoops_RPGP _hoops_PAH _hoops_AGPP _hoops_CCA _hoops_RHAA _hoops_PGPP (_hoops_HGPP _hoops_GAR _hoops_IGPP())
		_hoops_IPGP(h3ddata, false);

		if ( h3ddata->_hoops_II._hoops_SGAP & _hoops_CGPP ) {
			int const _hoops_SGPP = h3ddata->_hoops_CSC->_hoops_GRPP;

			// _hoops_RRPP _hoops_ARPP _hoops_PRPP _hoops_HIS _hoops_PIH _hoops_GRS _hoops_SHH _hoops_HRPP.
			size_t const _hoops_IRPP = h3ddata->_hoops_II._hoops_CRPP->_hoops_SRPP();

			if ( h3ddata->dc->options._hoops_GAPP )
				// _hoops_RAPP _hoops_AAPP _hoops_PAPP _hoops_CCGP _hoops_PAPA _hoops_IS _hoops_AHPA, _hoops_HAPP _hoops_IAPP _hoops_CAPP.
				h3ddata->_hoops_II._hoops_AIGP = H3DPost::_hoops_SAPP;
			else {
				// _hoops_RGR _hoops_GRS _hoops_GPPP _hoops_RH _hoops_RPPP _hoops_CI _hoops_CCGP _hoops_RPP _hoops_SCH _hoops_APPP _hoops_RRI _hoops_HSAR 50_hoops_PPPP _hoops_IS _hoops_HPPP
				if (_hoops_IRPP > 50 && h3ddata->_hoops_II._hoops_AIGP > H3DPost::_hoops_IPPP) {
					--h3ddata->_hoops_II._hoops_AIGP;

					// _hoops_CPPP _hoops_SPS _hoops_SPPP _hoops_GHPP - _hoops_RHPP _hoops_AHPP _hoops_IS _hoops_AA _hoops_RRI _hoops_IPHR _hoops_CGPR _hoops_IRS _hoops_CI _hoops_PHPP
					// _hoops_IH _hoops_RH _hoops_SRS _hoops_GHIR.
					h3ddata->_hoops_II._hoops_CRPP->_hoops_HHPP();
				}
			}

			// _hoops_IHPP _hoops_RGR _hoops_IH _hoops_CHPP _hoops_SHPP _hoops_GGGP
			bool _hoops_GIPP = true;

			// _hoops_GCAR _hoops_RGR _hoops_IH _hoops_RIPP-_hoops_CCGP, _hoops_RIPP _hoops_AIPP.
			bool const _hoops_PIPP = true;
			int _hoops_HIPP = (h3ddata->_hoops_II._hoops_AIGP == H3DPost::_hoops_IPPP) ? 1 : 2;

			//
			// _hoops_IIPP _hoops_CIPP _hoops_SIPP _hoops_SPPP _hoops_PRPP _hoops_PAR _hoops_SR'_hoops_GCPP _hoops_HGCR _hoops_RCPP _hoops_ACPP.
			//

			// _hoops_SGAA _hoops_IS _hoops_GSSR _hoops_IGIR
			int width = depth_texture->_hoops_IRRP;
			int height = depth_texture->_hoops_CRRP;
			
			// _hoops_IIPP _hoops_GSSR _hoops_PCPP
			H3DTexture *_hoops_HCPP = null;
			
			// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_GRP _hoops_ICPP, _hoops_CCPP _hoops_HCH _hoops_HH _hoops_IH _hoops_SCPP.
			if ( _hoops_PIPP && h3ddata->_hoops_IHP ) {
				width /= h3ddata->_hoops_HSAA;
				height /= h3ddata->_hoops_ISAA;
				_hoops_HCPP = post->_hoops_IAAP( width, height, depth_texture->_hoops_GSPP );
			}
			
			// _hoops_IIPP _hoops_PSCA _hoops_IH _hoops_HCRP _hoops_RH _hoops_GHPP.
			H3DTexture *_hoops_RSPP[2] = { null, null };
			if ( _hoops_GIPP ) {
				for ( int i = 0; i < sizeof(_hoops_RSPP)/sizeof(_hoops_RSPP[0]); ++i ) {
					_hoops_RSPP[i] = post->_hoops_IAAP( width, height, H3DFMT_A8R8G8B8 );
				}
			}

			//
			// _hoops_ASPP _hoops_PSPP, _hoops_HSPP _hoops_SPPP.
			//

			h3ddata->_hoops_II._hoops_CRPP->_hoops_GGPP();

			// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_GRP _hoops_ICPP, _hoops_SCPP _hoops_RH _hoops_HCH _hoops_HH
			if ( _hoops_HCPP ) {
				post->Copy(_hoops_HCPP, depth_texture, 0, H3DTEXF_POINT);
				Swap(depth_texture, _hoops_HCPP);
			}

			// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_GRP _hoops_ISPP-_hoops_CCGP _hoops_GGGP, _hoops_SAHR _hoops_GHAA _hoops_RH _hoops_RISA _hoops_CSPP _hoops_SSPP.
			if ( !_hoops_GIPP )
				_hoops_CAGP(h3ddata, h3ddata->render_target, depth_texture, false, false);
			else {
				// _hoops_CGP _hoops_SR _hoops_GGHP _hoops_RH _hoops_RGHP _hoops_PSCA
				if ( _hoops_RSPP[0] && _hoops_RSPP[1] ) {
					_hoops_GPRP(h3ddata, H3DMASK_RGBA);

					// _hoops_AGHP _hoops_PGHP _hoops_GGGP
					_hoops_CAGP(h3ddata, _hoops_RSPP[0], depth_texture, true, true);

					// _hoops_CIRP...
					for ( int i = 0; i < _hoops_HIPP; ++i )
					{
						_hoops_PIRP(h3ddata, _hoops_RSPP[0], _hoops_RSPP[1]);
					}

					// _hoops_HGHP _hoops_CPRP _hoops_IAPR _hoops_IGHP.
					_hoops_GPRP(h3ddata, H3DMASK_RGB);
					ENSURE_TRANSPARENCY(h3ddata, true);
					_hoops_PPRP(h3ddata, H3DBLEND_ZERO, H3DBLEND_INVSRCALPHA);

					// _hoops_CIRP _hoops_CGHP _hoops_SGHP _hoops_GGR _hoops_ICPP _hoops_CCH, _hoops_GRHP _hoops_RRHP _hoops_GGR _hoops_GRAA _hoops_ARHP _hoops_CCH.
					post->Copy( h3ddata->render_target, _hoops_RSPP[0], NULL, h3ddata->_hoops_IHP ? H3DTEXF_LINEAR : H3DTEXF_POINT );

					// _hoops_IPRP _hoops_CPRP
					_hoops_PPRP(h3ddata, H3DBLEND_SRCALPHA, H3DBLEND_INVSRCALPHA);
				}
			}

			// _hoops_ASAP _hoops_SPPP _hoops_PRPP
			h3ddata->_hoops_II._hoops_CRPP->_hoops_PRHP();

			// _hoops_SP _hoops_GH
			for ( int i = 0; i < sizeof(_hoops_RSPP)/sizeof(_hoops_RSPP[0]); ++i )
				post->_hoops_HAAP( &_hoops_RSPP[i] );

			if ( _hoops_HCPP ) {
				// _hoops_IPRP _hoops_GIGR
				Swap(depth_texture, _hoops_HCPP);
				
				// _hoops_HRHP _hoops_RISA _hoops_IRHP
				post->_hoops_HAAP(&_hoops_HCPP);
			}
			_hoops_GPRP(h3ddata, _hoops_SGPP);
		}

		if ( h3ddata->_hoops_II._hoops_SGAP & _hoops_CRHP ) {

			if ( H3DConstantTable *_hoops_AIPA = post->_hoops_PIGP( H3DPost::_hoops_HIGP, H3DPost::_hoops_SRHP ) ) {

				// _hoops_SIIR _hoops_HH.
				if ( unsigned long _hoops_PCI = _hoops_AIPA->GetSamplerIndex("Depth") < _hoops_CIGP ) {
					// _hoops_AHH: _hoops_SIGP: _hoops_GCGP _hoops_RCGP _hoops_HRGR _hoops_ACGP _hoops_ARI, _hoops_HIS _hoops_SR _hoops_HHSA _hoops_SCH _hoops_IS _hoops_PCGP _hoops_GGR 
					//   _hoops_RH _hoops_CI _hoops_PPR _hoops_GGR _hoops_HCGP 
					_hoops_SCCR(h3ddata, 0, depth_texture);
					_hoops_GRPA(h3ddata, 0, H3DTEXF_POINT, H3DTEXF_NONE, H3DTADDRESS_CLAMP);
				}

				// _hoops_RAP _hoops_PPPR _hoops_IGIR _hoops_HIS _hoops_SR _hoops_PAH _hoops_CSRA _hoops_ISAR _hoops_AII _hoops_PRRP.
				float _hoops_HRRP[2] = { 1.0f / depth_texture->_hoops_IRRP, 1.0f / depth_texture->_hoops_CRRP};
				_hoops_AIPA->SetVector("OneOverTexelSize", _hoops_HRRP, 2);

				// _hoops_RAP _hoops_RII _hoops_A
				float scale = 1.0f;

				if (h3ddata->dc->options._hoops_GAHP)
					scale *= h3ddata->dc->options._hoops_GAHP;

 				// _hoops_RAHP _hoops_AAHP _hoops_PAHP, _hoops_HAHP _hoops_HCH _hoops_IAHP _hoops_CHR _hoops_RGHP _hoops_IS _hoops_CAHP _hoops_SAHP,
 				// _hoops_PPR _hoops_GPHP-_hoops_RPHP.
 				float min = 0.02f * scale;
 				float max = 0.08f * scale;
 				float tolerance[2] = 
 				{
 					1.0f / (max - min),
 					-min / (max - min),
 				};
 				_hoops_AIPA->SetVector("ToleranceScaleAndBias", tolerance, 2);

				// _hoops_RAP _hoops_RH '_hoops_APHP' _hoops_CSRA.
				float const _hoops_PPHP = 10.0f;
				_hoops_AIPA->SetFloat("DepthScale", _hoops_PPHP * _hoops_CIRA);

				// _hoops_HGI _hoops_ARP _hoops_IIGR _hoops_ARGP _hoops_HRGR _hoops_AAH _hoops_IH _hoops_PSP _hoops_ARHP, _hoops_SCH _hoops_AAAA '_hoops_RRHP' _hoops_RSRA _hoops_AIR _hoops_SAHP.
				static const float _hoops_IGGP[8] = 
				{
					// _hoops_HPHP _hoops_HSGP
					0, 0, 1, 0, 0, 1, 1, 1
				};

				// _hoops_HGI _hoops_ARP _hoops_IIGR _hoops_ARGP _hoops_PAH _hoops_SHH _hoops_GIH _hoops_IH _hoops_ICPP, _hoops_SCH _hoops_AAAA _hoops_IPHP _hoops_SPPR _hoops_PGAP _hoops_SCPP _hoops_IS 
				// _hoops_CPHP _hoops_SPHP _hoops_RH _hoops_PSHR _hoops_SGCR _hoops_GAR _hoops_RH _hoops_PSP _hoops_ARHP _hoops_SAHP.
				static const float _hoops_GHHP[8] = 
				{
					// _hoops_RHHP _hoops_HSGP
					-1, 0, +1, 0, 0, -1, 0, +1,
				};
				_hoops_AIPA->SetVectorArray("Taps", h3ddata->_hoops_IHP ? _hoops_GHHP : _hoops_IGGP, 4, 2);

				float rgb[3];
				rgb[0] = nr->_hoops_RHP->color._hoops_HRIR.r / 255.0f;
				rgb[1] = nr->_hoops_RHP->color._hoops_HRIR.g / 255.0f;
				rgb[2] = nr->_hoops_RHP->color._hoops_HRIR.b / 255.0f;
				_hoops_AIPA->SetVector("EdgeColor", rgb, 3);

				// _hoops_HGHP _hoops_CPRP _hoops_IAPR _hoops_IGHP.
				ENSURE_TRANSPARENCY(h3ddata, true);
				_hoops_PPRP(h3ddata, H3DBLEND_SRCALPHA, H3DBLEND_INVSRCALPHA);
				post->_hoops_HPRP(h3ddata->render_target, H3DPost::_hoops_SRHP, 0.0f, null, depth_texture);
			}
		}

		if ( h3ddata->_hoops_II._hoops_SGAP & _hoops_AHHP ) {

			if ( H3DConstantTable *_hoops_AIPA = post->_hoops_PIGP( H3DPost::_hoops_HIGP, H3DPost::_hoops_PHHP ) ) {

				// _hoops_SIIR _hoops_HH.
				if ( const unsigned long _hoops_PCI = _hoops_AIPA->GetSamplerIndex("Depth") < _hoops_CIGP ) {
					// _hoops_AHH: _hoops_SIGP: _hoops_GCGP _hoops_RCGP _hoops_HRGR _hoops_ACGP _hoops_ARI, _hoops_HIS _hoops_SR _hoops_HHSA _hoops_SCH _hoops_IS _hoops_PCGP _hoops_GGR 
					//   _hoops_RH _hoops_CI _hoops_PPR _hoops_GGR _hoops_HCGP 
					_hoops_SCCR(h3ddata, 0, depth_texture);
					_hoops_GRPA(h3ddata, 0, H3DTEXF_POINT, H3DTEXF_NONE, H3DTADDRESS_CLAMP);
				}

				// _hoops_RAP _hoops_PPPR _hoops_IGIR _hoops_HIS _hoops_SR _hoops_PAH _hoops_CSRA _hoops_ISAR _hoops_AII _hoops_PRRP.
				float _hoops_HRRP[2] = { 1.0f / depth_texture->_hoops_IRRP, 1.0f / depth_texture->_hoops_CRRP};
				_hoops_AIPA->SetVector("OneOverTexelSize", _hoops_HRRP, 2);

				// _hoops_HGI _hoops_ARP _hoops_IIGR _hoops_ARGP _hoops_AAAA _hoops_HHHP _hoops_SPPR _hoops_CCA _hoops_PSP _hoops_ICPP.
				static const float _hoops_IGGP[8] = 
				{
					// _hoops_RHHP _hoops_HSGP
					-1, 0, +1, 0, 0, -1, 0, +1,
				};

				// _hoops_CHSR _hoops_RGR _hoops_SPR _hoops_AAAA _hoops_RPPR _hoops_IPHP _hoops_SPPR, _hoops_SR _hoops_SGH _hoops_SCH _hoops_IS _hoops_HPPR _hoops_PPR _hoops_IHHP _hoops_RH 
				// _hoops_PSHR _hoops_SGCR _hoops_GGR _hoops_ARHP _hoops_CCH.
				static const float _hoops_GHHP[8] = 
				{
					// _hoops_CHHP _hoops_SHHP _hoops_HSGP
					-2, 0, +2, 0, 0, -2, 0, +2,
				};
				_hoops_AIPA->SetVectorArray("Taps", h3ddata->_hoops_IHP ? _hoops_GHHP : _hoops_IGGP, 4, 2);

				float rgb[3];
				rgb[0] = nr->_hoops_RHP->color._hoops_HRIR.r / 255.0f;
				rgb[1] = nr->_hoops_RHP->color._hoops_HRIR.g / 255.0f;
				rgb[2] = nr->_hoops_RHP->color._hoops_HRIR.b / 255.0f;
				_hoops_AIPA->SetVector("EdgeColor", rgb, 3);

				// _hoops_HGHP _hoops_CPRP _hoops_IAPR _hoops_IGHP.
				ENSURE_TRANSPARENCY(h3ddata, true);
				_hoops_PPRP(h3ddata, H3DBLEND_SRCALPHA, H3DBLEND_INVSRCALPHA);
				post->_hoops_HPRP(h3ddata->render_target, H3DPost::_hoops_PHHP, 0.0f, null, depth_texture);
			}
		}

		if ( (h3ddata->_hoops_II._hoops_SGAP & _hoops_GIHP) && 
			 h3ddata->_hoops_II._hoops_SPH != null ) {

			// _hoops_HCGA _hoops_RH _hoops_PSHR _hoops_PHCR _hoops_IS _hoops_RH _hoops_RIHP _hoops_CCIR _hoops_GAR _hoops_SR _hoops_CHH _hoops_IS _hoops_RH _hoops_SARA-_hoops_GC _hoops_SSH _hoops_HSH.
			float const f = h3ddata->_hoops_SIRA;
			float const n = h3ddata->_hoops_GCRA;
			float s, b;

			if ( h3ddata->_hoops_II._hoops_SPH->projection == _hoops_GHH ) {
				// _hoops_HCGA _hoops_AIHP _hoops_SARA _hoops_GC _hoops_AHCR _hoops_PIHP
				s = f / (f-n);
				b = -n * s;
			}
			else {
				// _hoops_PHAA _hoops_SHI _hoops_HPP _hoops_RHC _hoops_GIRA _hoops_CR _hoops_RH _hoops_SARA _hoops_HIHP _hoops_IIHP _hoops_AHHR _hoops_HPGR _hoops_RH _hoops_SAAP, _hoops_HAR _hoops_RH 
				// _hoops_SARA, _hoops_GGR _hoops_CIHP _hoops_CCH.
				s = 1.0f;
				b = -h3ddata->_hoops_II._hoops_SPH->_hoops_SRIR;

				// _hoops_HCGA _hoops_SIHP _hoops_SARA _hoops_GC _hoops_AHCR _hoops_PIHP, _hoops_HAR _hoops_GCHP _hoops_RH (_hoops_RCHP-_hoops_ACHP) _hoops_CSRA _hoops_GGR _hoops_PCHP.
				s *= 1.0f;
				b += -n * s;
			}

			float const _hoops_HCHP = h3ddata->dc->options._hoops_ICHP * s + b;
			float const _hoops_CCHP = h3ddata->dc->options._hoops_SCHP * s + b;

			// _hoops_AGGA _hoops_SGH _hoops_RH _hoops_HSH
			float const _hoops_GSHP = _hoops_AHIA(_hoops_CCHP, _hoops_HCHP);
			float const _hoops_RSHP = _hoops_IAAA(_hoops_CCHP, _hoops_HCHP);
			float const length = 0.5f * (_hoops_RSHP - _hoops_GSHP);
			float const _hoops_ASHP = _hoops_GSHP - length;
			float const _hoops_PSHP = _hoops_RSHP + length;
			float radius = 6.0f;

			// _hoops_HHSR _hoops_GGR _hoops_SPGP
			float const MAX = 10.0f;
			float const _hoops_SHGP = h3ddata->dc->options._hoops_HSHP;
			if ( _hoops_SHGP < 1 )
				// _hoops_GPPR _hoops_ISHP
				radius *= _hoops_SHGP;
			else 
				// _hoops_GPPR _hoops_GH _hoops_IS 2x _hoops_PSAA _hoops_HPGR _hoops_CSHP _hoops_CIIA _hoops_SPGP
				radius += 1.0f + (_hoops_SHGP - 1.0f) / (MAX - 1.0f);

			// _hoops_SSHP _hoops_IPHR _hoops_AI
			H3DTexture *_hoops_GGIP = post->_hoops_IAAP( depth_texture->_hoops_IRRP, depth_texture->_hoops_CRRP, H3DFMT_A8R8G8B8 );
			H3DTexture *_hoops_RGIP = post->_hoops_IAAP( depth_texture->_hoops_IRRP, depth_texture->_hoops_CRRP, H3DFMT_A8R8G8B8 );
			H3DTexture *_hoops_AGIP = post->_hoops_IAAP( depth_texture->_hoops_IRRP, depth_texture->_hoops_CRRP, H3DFMT_A8R8G8B8 );

			if ( _hoops_GGIP && _hoops_RGIP && _hoops_AGIP ) {

				// _hoops_PGIP _hoops_IS _hoops_HGCR _hoops_IRS _hoops_HIRA _hoops_HH _hoops_SR _hoops_PAH _hoops_IPHR _hoops_CCA.
				_hoops_HGIP(h3ddata, h3ddata->render_target, _hoops_GGIP, H3DTEXF_NONE);

				//
				// _hoops_IGIP _hoops_SPR: _hoops_IISR _hoops_GGR-_hoops_GCAP _hoops_HSH _hoops_CRGR _hoops_AIIR _hoops_RCAP _hoops_IIGR _hoops_HCGP _hoops_CSCR.
				//

				// _hoops_CGIP _hoops_GGR _hoops_RGPP
				int const _hoops_SGPP = h3ddata->_hoops_CSC->_hoops_GRPP;
				ENSURE_TRANSPARENCY(h3ddata, false);

				// _hoops_SIAP _hoops_SGIP _hoops_GCAP _hoops_HSH _hoops_CRGR _hoops_HIRA _hoops_AIIR
				_hoops_GPRP(h3ddata, H3DMASK_A);
				_hoops_ACAP(h3ddata, _hoops_GGIP, depth_texture, _hoops_RSHP, _hoops_PSHP);

				// _hoops_SIAP _hoops_APAP _hoops_GCAP _hoops_HSH _hoops_CRGR _hoops_RISA _hoops_HH _hoops_CCA _hoops_HCR _hoops_GRIP
				_hoops_GPRP(h3ddata, H3DMASK_RGBA);
				_hoops_ACAP(h3ddata, _hoops_RGIP, depth_texture, _hoops_GSHP, _hoops_ASHP);

				// _hoops_SPRP _hoops_RRIP _hoops_CRGR _hoops_SPCR _hoops_PPR _hoops_GHCR - _hoops_RGR _hoops_HRGR _hoops_RH _hoops_SPCR _hoops_ARIP. _hoops_PRIP _hoops_HRIP.
				float const w = 1.0f/256.0f * sqrt(2.0f);
				static Vector const _hoops_IRIP[] = 
				{
					Vector ( -4.0f, 0.0f, 1.0f * w ), 
					Vector ( -3.0f, 0.0f, 8.0f * w ),
					Vector ( -2.0f, 0.0f, 28.0f * w ), 
					Vector ( -1.0f, 0.0f, 56.0f * w ),
					Vector ( +1.0f, 0.0f, 56.0f * w ),
					Vector ( +2.0f, 0.0f, 28.0f * w ),
					Vector ( +3.0f, 0.0f, 8.0f * w ),
					Vector ( +4.0f, 0.0f, 1.0f * w ),
				};

				// _hoops_SPRP _hoops_RRIP _hoops_CRGR _hoops_SPCR _hoops_PPR _hoops_GHCR - _hoops_RGR _hoops_HRGR _hoops_RH _hoops_GHCR _hoops_ARIP. _hoops_PRIP _hoops_HRIP.
				static Vector const _hoops_CRIP[] = 
				{
					Vector ( 0.0f, -4.0f, 1.0f * w ), 
					Vector ( 0.0f, -3.0f, 8.0f * w ), 
					Vector ( 0.0f, -2.0f, 28.0f * w ),
					Vector ( 0.0f, -1.0f, 56.0f * w ), 
					Vector ( 0.0f, +1.0f, 56.0f * w ),
					Vector ( 0.0f, +2.0f, 28.0f * w ),
					Vector ( 0.0f, +3.0f, 8.0f * w ),
					Vector ( 0.0f, +4.0f, 1.0f * w ),
				};

				// _hoops_SRIP _hoops_PPR _hoops_GGCR _hoops_IS _hoops_SGIP _hoops_GCAP
				post->_hoops_GAIP(_hoops_AGIP, _hoops_RGIP, H3DPost::_hoops_RAIP, 7, _hoops_IRIP);
				post->_hoops_GAIP(_hoops_RGIP, _hoops_AGIP, H3DPost::_hoops_RAIP, 7, _hoops_CRIP);

				// _hoops_RAH _hoops_RGR _hoops_GGCR _hoops_GGR _hoops_RH _hoops_AIIR _hoops_RCAP _hoops_RGAR
				_hoops_GPRP(h3ddata, H3DMASK_A);
				ENSURE_TRANSPARENCY(h3ddata, true);
				_hoops_PPRP(h3ddata, H3DBLEND_ONE, H3DBLEND_ONE);
				post->Copy(_hoops_GGIP, _hoops_RGIP, null, H3DTEXF_POINT);

				// _hoops_IPRP _hoops_AAIP
				_hoops_PPRP(h3ddata, H3DBLEND_SRCALPHA, H3DBLEND_INVSRCALPHA);

				//
				// _hoops_IGIP _hoops_PGCR: _hoops_HCGA _hoops_HCH _hoops_IIGR _hoops_PAIP _hoops_HAIP _hoops_IS _hoops_HIRA.
				//

				if ( H3DConstantTable *_hoops_AIPA = post->_hoops_PIGP( H3DPost::_hoops_HIGP, H3DPost::_hoops_IAIP ) ) {

					// _hoops_CAIP'_hoops_RA _hoops_SAIP _hoops_AIIR _hoops_RCAP
					_hoops_GPRP(h3ddata, H3DMASK_RGB);

					// _hoops_SIIR _hoops_AI.
					if ( const unsigned long _hoops_PCI = _hoops_AIPA->GetSamplerIndex("Scene") < _hoops_CIGP ) {
						// _hoops_AHH: _hoops_SIGP: _hoops_GCGP _hoops_RCGP _hoops_HRGR _hoops_ACGP _hoops_ARI, _hoops_HIS _hoops_SR _hoops_HHSA _hoops_SCH _hoops_IS _hoops_PCGP _hoops_GGR 
						//   _hoops_RH _hoops_CI _hoops_PPR _hoops_GGR _hoops_HCGP 
						_hoops_SCCR(h3ddata, 0, _hoops_GGIP);
						_hoops_GRPA(h3ddata, 0, H3DTEXF_POINT, H3DTEXF_NONE, H3DTADDRESS_CLAMP);
					}

					// _hoops_RAP _hoops_PPPR _hoops_IGIR _hoops_HIS _hoops_SR _hoops_PAH _hoops_CSRA _hoops_ISAR _hoops_AII _hoops_PRRP.
					float _hoops_HRRP[2] = { 
						radius * h3ddata->_hoops_HSAA / _hoops_GGIP->_hoops_IRRP, 
						radius * h3ddata->_hoops_ISAA / _hoops_GGIP->_hoops_CRRP
					};
					_hoops_AIPA->SetVector("OneOverTexelSize", _hoops_HRRP, 2);

					// _hoops_HGHP _hoops_CPRP _hoops_IAPR _hoops_IGHP.
					post->_hoops_HPRP(h3ddata->render_target, H3DPost::_hoops_IAIP, 0.0f, null, _hoops_GGIP);
				}

				// _hoops_IPRP _hoops_AAIP
				_hoops_GPRP(h3ddata, _hoops_SGPP);
			}
			
			// _hoops_SP _hoops_GH
			post->_hoops_HAAP(&_hoops_GGIP);
			post->_hoops_HAAP(&_hoops_RGIP);
			post->_hoops_HAAP(&_hoops_AGIP);
		}

		post->_hoops_PRHP();
	}

	// _hoops_GPIP _hoops_HRGR _hoops_PSP _hoops_RPIP _hoops_APIP
	h3ddata->_hoops_II._hoops_SPH = null;

//#_hoops_PPIP _hoops_HPIP
#ifdef _hoops_IPIP
	// _hoops_CPIP _hoops_RH _hoops_HCH _hoops_SRHR _hoops_SR _hoops_SPIP.
	_hoops_GHIP(h3ddata, depth_texture, 0, 200, 200, 200);
#endif

	if ( depth_texture )
		// _hoops_SP _hoops_GH _hoops_PA _hoops_SR _hoops_SPIP.
		post->_hoops_HAAP( &depth_texture );
}


/*
* _hoops_PGAA
*/
bool _hoops_RHIP (
		Action_Mask mask,
		Geometry const *g)
{
	Type type = g->type;

	if (type == _hoops_AHIP) {
		_hoops_PHIP const *		_hoops_RRA = (_hoops_PHIP const *)g;

		for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++)
			if (_hoops_RHIP (mask, (Geometry const *)_hoops_RRA->_hoops_IHIP[i]))
				return true;
		return false;
	}

	switch (type) {
		case _hoops_CHIP:
			return (BIT (mask, _hoops_SHIP));

		case _hoops_GIIP:
		case _hoops_RIIP:
			return (BIT (mask, _hoops_AIIP));

		case _hoops_PIIP:
		case _hoops_HIIP:
		case _hoops_IIIP:
			return (BIT (mask, _hoops_CIIP));

		case _hoops_SIIP:
			return (BIT (mask, _hoops_GCIP));

		case _hoops_RCIP:
			return (BIT (mask, _hoops_ACIP));

		case _hoops_PCIP:
			return (BIT (mask, _hoops_HCIP));

		case _hoops_ICIP:
			return (BIT (mask, _hoops_CCIP));

		case _hoops_SCIP:
		case _hoops_GSIP:
			return (BIT (mask, _hoops_RSIP));

		case _hoops_ASIP:
			return (BIT (mask, _hoops_PSIP));

		case _hoops_HSIP:
			return (BIT (mask, _hoops_ISIP));

		case _hoops_CSIP:
			return (BIT (mask, _hoops_SSIP));

		case _hoops_GGCP:
			return (BIT (mask, _hoops_RGCP));

		case _hoops_AGCP:
			return (BIT (mask, _hoops_PGCP));

		case _hoops_HGCP:
			return (BIT (mask, _hoops_IGCP));

		case _hoops_CGCP:
		case _hoops_SGCP:
		case _hoops_GRCP:
		case _hoops_RRCP:
			return (BIT (mask, _hoops_ARCP));

		case _hoops_PRCP:
			return (BIT (mask, _hoops_HRCP));

		case _hoops_IRCP: {
			Geometry const *geo;
			_hoops_CRCP const *_hoops_SRCP = (_hoops_CRCP *) g;
			int i = 0;

			if (_hoops_SRCP->_hoops_GACP) {
				for (i = 0; i < _hoops_RACP; i++) {
					geo = _hoops_SRCP->_hoops_GACP->_hoops_AACP (i);
					if (geo && _hoops_RHIP(mask, geo))
						return true;
				}
			}
			else {
				geo = _hoops_SRCP->geometry;
				while (geo) {
					if (_hoops_RHIP(mask, geo))
						return true;
					geo = geo->next;
				}
			}
			return false;
		}

		default:
			HE_ERROR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					"unrecognized type in action_mask_matches_gref");
			return false;
	}
}




/*
 * _hoops_PGAA
 */
void _hoops_PACP (
	Net_Rendition const &		nr,
	Polyedge const *			pe,
	Line_Rendition const &		_hoops_GHP,
	H3DVertexBuffer *			_hoops_HACP,
	float						_hoops_IACP,
	int							_hoops_CACP,
	int							_hoops_SACP,
	_hoops_HRPA const *			matrix,
	RGB const *					_hoops_GPCP,
	_hoops_HCI *			_hoops_RPCP) {
	_hoops_HHA const &	matr = nr->_hoops_RHP->_hoops_CHA;
	Line_Style const &			line_style = _hoops_GHP->line_style;
	H3DData *					h3ddata = H3DD(nr->_hoops_SRA);
	float						_hoops_APCP = 0;
	int							i;
	float						u, v, w;
	int 						param_width = pe->_hoops_GSHA;
	H3DVertexFormat				_hoops_PPCP = _hoops_HACP->_hoops_HPCP();

	/*_hoops_IPCP _hoops_CPCP _hoops_PIHA _hoops_SHH _hoops_GAR _hoops_SPCP:
	* _hoops_AHC
	* _hoops_GSSR
	* _hoops_HAIR
	* _hoops_GHCP
	* _hoops_HH
	*/

	ASSERT (_hoops_CACP < pe->point_count);
	ASSERT (_hoops_SACP < pe->_hoops_SPHA || _hoops_SACP == 0 || (pe->_hoops_ASHA == null && pe->_hoops_RSHA == null));

	// _hoops_RHCP _hoops_AHC
	if (matrix == null) {
		_hoops_HACP->_hoops_AHCP(pe->points[_hoops_CACP]);
	}
	else {
		_hoops_APCP = 1.0f / _hoops_PHCP (matrix->elements, pe->points[_hoops_CACP]);
		_hoops_HACP->_hoops_AHCP(_hoops_HPRA(matrix->elements, pe->points[_hoops_CACP]) * _hoops_APCP,
				_hoops_IPRA(matrix->elements, pe->points[_hoops_CACP]) * _hoops_APCP,
				_hoops_CPRA(matrix->elements, pe->points[_hoops_CACP]) * _hoops_APCP);
	}

	// _hoops_RHCP _hoops_ASGA
	if (_hoops_PPCP._hoops_HHCP()) {
		if (matrix == null) {
			if (pe->_hoops_ICHA)
				_hoops_HACP->_hoops_IHCP(pe->_hoops_ICHA[_hoops_CACP]);
			else if (pe->_hoops_RSHA)
				_hoops_HACP->_hoops_IHCP(pe->_hoops_RSHA[_hoops_SACP]);
		}
		else {
			_hoops_ARPA plane;
			Vector vector;

			if (matrix->_hoops_APRA == null)
				HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)matrix);
			_hoops_RPRA const *	_hoops_APRA = matrix->_hoops_APRA->data.elements;

			if (pe->_hoops_ICHA)
				plane = _hoops_ARPA (pe->_hoops_ICHA[_hoops_CACP], pe->points[_hoops_CACP]);
			else
				plane = _hoops_ARPA (pe->_hoops_RSHA[_hoops_SACP], pe->points[_hoops_CACP]);

			vector.x = plane.a*_hoops_APRA[0][0] + plane.b*_hoops_APRA[0][1] + plane.c*_hoops_APRA[0][2] + plane.d*_hoops_APRA[0][3];
			vector.y = plane.a*_hoops_APRA[1][0] + plane.b*_hoops_APRA[1][1] + plane.c*_hoops_APRA[1][2] + plane.d*_hoops_APRA[1][3];
			vector.z = plane.a*_hoops_APRA[2][0] + plane.b*_hoops_APRA[2][1] + plane.c*_hoops_APRA[2][2] + plane.d*_hoops_APRA[2][3];

			if (BIT(matrix->_hoops_RAGR, _hoops_CHCP))
				HI_Normalize(&vector);

			_hoops_HACP->_hoops_IHCP(vector);
		}
	}

	// _hoops_RHCP _hoops_PSHA
	if (_hoops_PPCP._hoops_SHCP()) {
		RGB const *color = null;
		if (pe->_hoops_PCHA)
			color = &pe->_hoops_PCHA[_hoops_CACP];
		else if (pe->_hoops_ASHA)
			color = &pe->_hoops_ASHA[_hoops_SACP];
		else
			color = _hoops_GPCP;

		_hoops_HACP->color(_hoops_GICP(h3ddata->_hoops_SHAP, color->red, color->green, color->blue, 1));
	}

	int _hoops_RICP = 0;
	_hoops_SII(_hoops_IAAR, 0, _hoops_RPCP, &_hoops_RICP, null, null);
	// _hoops_AICP _hoops_PICP _hoops_IIGR _hoops_RH _hoops_GGAR _hoops_HH _hoops_RPP _hoops_SCH _hoops_HICP
	if (pe->_hoops_SRHA & _hoops_GGIA) {
		_hoops_GRA const &		_hoops_RRA = nr->_hoops_ARA;

		_hoops_HACP->_hoops_IICP(pe->_hoops_HCHA[_hoops_CACP] * _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate,
				0,
				0,
				_hoops_RICP);
	}

	if (!BIT(line_style->flags, LSF_SOLID)) {
		POINTER_SIZED_INT _hoops_SICP;

		h3ddata->_hoops_GCCP->LookupItem(line_style->name.text, &_hoops_SICP);

		_hoops_SII(_hoops_HIRR, 0, _hoops_RPCP, &_hoops_RICP, null, null);

		_hoops_HACP->_hoops_IICP(_hoops_IACP / 32.0f / _hoops_GHP->line_style->scale32,
				_hoops_SICP / 32.0f,
				0,
				_hoops_RICP);
	}

	//_hoops_RH _hoops_PIRA _hoops_GGR _hoops_RRAP _hoops_HRGR _hoops_RCCP _hoops_IS _hoops_ACCP _hoops_SHH _hoops_PCCP _hoops_HCCP _hoops_HIIA
	ASSERT (h3ddata->_hoops_AIC == 
			(nr->_hoops_IRR->_hoops_SRI == _hoops_GAI && BIT (nr->transform_rendition->heuristics, _hoops_IRI)));
	if (h3ddata->_hoops_AIC) {
		float _hoops_ICCP;

		if (pe->_hoops_CCCP != null)
			_hoops_ICCP = pe->_hoops_CCCP[_hoops_CACP];
		else
			_hoops_ICCP = _hoops_SCCP(pe->_hoops_GSCP->priority,0);
		_hoops_SII(_hoops_ACPR, 0, _hoops_RPCP, &_hoops_RICP, null, null);
		_hoops_HACP->u(_hoops_ICCP,_hoops_RICP);
	}

	// _hoops_GRAR _hoops_PCRR
	_hoops_HIR *_hoops_PGC = matr->_hoops_SCA;
	for (i = 0; i < _hoops_RPCP->_hoops_PGC; i++) {
		_hoops_SII(_hoops_PSRR, i, _hoops_RPCP, &_hoops_RICP, null, null);

		int _hoops_PSR = 0;
		int offset = 0;
		if (_hoops_PGC) {
			_hoops_PSR = _hoops_PGC->texture->_hoops_PSR;
			offset = _hoops_PGC->texture->_hoops_RSCP;
			if (offset > pe->_hoops_GSHA)
				offset = 0;
			_hoops_PGC = _hoops_PGC->next;
		}

		u = v = w = 0;
		if (_hoops_PSR != HK_PS_WORLD && pe->_hoops_CCHA) {
			if (offset+0 < param_width) u = pe->_hoops_CCHA[_hoops_CACP * param_width + offset + 0];
			if (offset+1 < param_width) v = pe->_hoops_CCHA[_hoops_CACP * param_width + offset + 1];
			if (offset+2 < param_width) w = pe->_hoops_CCHA[_hoops_CACP * param_width + offset + 2];
		}
		_hoops_HACP->_hoops_IICP(u, v, w, _hoops_RICP);

		if (_hoops_RPCP->_hoops_RGC)
			break;
	}
}


void _hoops_ASCP (
	Net_Rendition const &		nr,
	Polymarker const *			pm,
	_hoops_ICP const &	_hoops_CCP,
	H3DVertexBuffer *			_hoops_HACP,
	int							_hoops_CACP,
	_hoops_HCI *			_hoops_RPCP) {
	_hoops_HHA const &	matr = _hoops_CCP->_hoops_CHA;
	H3DData *					h3ddata = H3DD(nr->_hoops_SRA);
	float						u, v, s;
	int 						param_width = pm->_hoops_GSHA;
	H3DVertexFormat				_hoops_PPCP = _hoops_HACP->_hoops_HPCP();
	int							_hoops_RICP;

	_hoops_HACP->_hoops_AHCP(pm->points[_hoops_CACP]);
	if (_hoops_PPCP._hoops_HHCP())
		_hoops_HACP->_hoops_IHCP(pm->_hoops_ICHA[_hoops_CACP]);
	if (_hoops_PPCP._hoops_PSCP()) {
		// _hoops_RHCP _hoops_PSHA
		if (_hoops_PPCP._hoops_SHCP() && (pm->_hoops_PCHA != null))
			_hoops_HACP->color(h3ddata->_hoops_SHAP, pm->_hoops_PCHA[_hoops_CACP].red, pm->_hoops_PCHA[_hoops_CACP].green, pm->_hoops_PCHA[_hoops_CACP].blue, _hoops_CCP->_hoops_CHA->_hoops_IRIR);
		else if (_hoops_PPCP._hoops_SHCP() && (pm->_hoops_RGIA != null))
			_hoops_HACP->color(h3ddata->_hoops_SHAP, pm->_hoops_RGIA[_hoops_CACP]);

		// _hoops_AICP _hoops_PICP _hoops_IIGR _hoops_RH _hoops_GGAR _hoops_HH _hoops_RPP _hoops_SCH _hoops_HICP
		if (pm->_hoops_HCHA) {
			_hoops_GRA const &		_hoops_RRA = nr->_hoops_ARA;
			_hoops_SII(_hoops_IAAR, 0, _hoops_RPCP, &_hoops_RICP, null, null);
			_hoops_HACP->_hoops_IICP(pm->_hoops_HCHA[_hoops_CACP] * _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate,
				0,
				0,
				_hoops_RICP);
		}

		//_hoops_RH _hoops_PIRA _hoops_GGR _hoops_RRAP _hoops_HRGR _hoops_RCCP _hoops_IS _hoops_ACCP _hoops_SHH _hoops_PCCP _hoops_HCCP _hoops_HIIA
		ASSERT (h3ddata->_hoops_AIC == 
			(nr->_hoops_IRR->_hoops_SRI == _hoops_GAI && BIT (nr->transform_rendition->heuristics, _hoops_IRI)));
		if (h3ddata->_hoops_AIC) {
			float _hoops_ICCP;

			if (pm->_hoops_CCCP != null)
				_hoops_ICCP = pm->_hoops_CCCP[_hoops_CACP];
			else
				_hoops_ICCP = _hoops_SCCP(pm->_hoops_GSCP->priority,0);
			_hoops_SII(_hoops_ACPR, 0, _hoops_RPCP, &_hoops_RICP, null, null);
			_hoops_HACP->u(_hoops_ICCP,_hoops_RICP);
		}

		// _hoops_GRAR _hoops_PCRR
		_hoops_HIR *_hoops_PGC = matr->_hoops_SCA;
		int _hoops_ASRR = 0;
		for (_hoops_ASRR = 0; _hoops_ASRR < _hoops_RPCP->_hoops_PGC; _hoops_ASRR++) {
			_hoops_SII(_hoops_PSRR, _hoops_ASRR, _hoops_RPCP, &_hoops_RICP, null, null);

			int _hoops_PSR = 0;
			int offset = 0;
			if (_hoops_PGC) {
				_hoops_PSR = _hoops_PGC->texture->_hoops_PSR;
				offset = _hoops_PGC->texture->_hoops_RSCP;
				if (offset > pm->_hoops_GSHA)
					offset = 0;
				_hoops_PGC = _hoops_PGC->next;
			}

			u = v = s = 0;
			if (_hoops_PSR != HK_PS_WORLD && pm->_hoops_CCHA) {
				if (offset+0 < param_width) u = pm->_hoops_CCHA[_hoops_CACP * param_width + offset + 0];
				if (offset+1 < param_width) v = pm->_hoops_CCHA[_hoops_CACP * param_width + offset + 1];
				if (offset+2 < param_width) s = pm->_hoops_CCHA[_hoops_CACP * param_width + offset + 2];
			}
			_hoops_HACP->_hoops_IICP(u, v, s, _hoops_RICP);

			if (_hoops_RPCP->_hoops_RGC)
				break;
		}
	}
}


/*
* _hoops_PGAA
* _hoops_HSCP _hoops_SGS _hoops_ISCP _hoops_CSCP _hoops_PIAP _hoops_SSCP _hoops_RH _hoops_GGSP _hoops_HRP _hoops_IH
*	_hoops_IRS) _hoops_PGCR _hoops_RPSA _hoops_RCA,
*	_hoops_RCSR) _hoops_RGSP _hoops_HSP
*/
void _hoops_AGSP (
		H3DData alter * h3ddata,
		_hoops_HHCR const & _hoops_IHCR,
		bool _hoops_PGSP)
{
	bool _hoops_HGSP	= BIT (_hoops_IHCR->flags, _hoops_IGSP);
	_hoops_CGSP heuristics = _hoops_IHCR->heuristics;

	if (!BIT (_hoops_IHCR->matrix->data.flags, _hoops_HASA))
		HI_Validate_Matrix_NEG3X3((_hoops_HRPA alter *)&_hoops_IHCR->matrix->data);

	bool _hoops_IASA = BIT (_hoops_IHCR->matrix->data._hoops_RAGR, _hoops_CASA);

 	if (h3ddata->_hoops_SGSP)
		_hoops_IASA = !_hoops_IASA;

	if (_hoops_IASA &&
		ANYBIT(heuristics, _hoops_RSA))
		heuristics ^= _hoops_RSA;

	if (BIT (_hoops_IHCR->flags, _hoops_SPP))
		heuristics ^= _hoops_RSA;

	if (_hoops_PGSP) {
		// _hoops_RGR _hoops_SIHR _hoops_RH 2_hoops_GRSP _hoops_RIH _hoops_IIGR _hoops_IRS 2-_hoops_RPSA _hoops_APSA _hoops_PGSA
		ASSERT (ANYBIT(heuristics, _hoops_RSA));
		heuristics ^= _hoops_RSA;
		_hoops_HGSP = true;
	}

	if (!_hoops_HGSP || !ANYBIT(heuristics, _hoops_RSA))
		_hoops_RHSA (h3ddata, H3DCULL_NONE);
	else if (BIT (heuristics, _hoops_SASA))
		_hoops_RHSA (h3ddata, H3DCULL_CW);
	else
		_hoops_RHSA (h3ddata, H3DCULL_CCW);
}


/*
 * _hoops_PGAA
 *
 * _hoops_RAP _hoops_SIC _hoops_RRSP _hoops_PPR _hoops_GRH _hoops_CI _hoops_AAP.
 * _hoops_ARSP _hoops_RRGR _hoops_PRSP _hoops_GAPA _hoops_RH _hoops_HRSP _hoops_IRSP _hoops_IIGR _hoops_CRSP.
 */
int _hoops_SRSP(H3DData *h3ddata,
							  Net_Rendition const & nr,
							  int type,
							  bool _hoops_GASP,
					          int _hoops_RASP,
							  int flags)
{
	_hoops_HHCR const &_hoops_IHCR = nr->transform_rendition;

	// _hoops_SGAA _hoops_RRSP
	bool _hoops_AASP = BIT(_hoops_IHCR->flags, _hoops_PASP);
	bool _hoops_HASP	= !BIT(_hoops_IHCR->flags, _hoops_ISH);
	bool _hoops_IASP = BIT(_hoops_IHCR->flags, _hoops_CASP);
	int mask = H3DMASK_RGB;
	bool _hoops_SASP = BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP);

	/* _hoops_HCGA _hoops_HCH _hoops_ICH _hoops_SGI _hoops_RPP _hoops_IRPR */
	if (h3ddata->_hoops_RHH.mode)	{
		flags |= h3ddata->_hoops_RHH.flags;

		// _hoops_PCH _hoops_RPSP, _hoops_GGI _hoops_CGPR _hoops_HAR _hoops_GRP _hoops_APSP, _hoops_IIP _hoops_CPRP.
		_hoops_AASP = true;
		_hoops_HASP	= !h3ddata->_hoops_RHH._hoops_PPSP;
		_hoops_GASP	= false;

		// _hoops_AHH: _hoops_HPSP _hoops_IH 11183 - _hoops_PAHA'_hoops_RA _hoops_RH _hoops_IPSP _hoops_ARP _hoops_CPSP->_hoops_SPSP?
		_hoops_IASP = true;

		// _hoops_GHSP _hoops_CPSP _hoops_AIIR _hoops_RPGP _hoops_RGSR _hoops_RHSP _hoops_HCH _hoops_ICH.
		// _hoops_GCAR _hoops_GGR _hoops_AHSP _hoops_CCH _hoops_CGPR _hoops_SR'_hoops_ASAR _hoops_GRP _hoops_RGPP _hoops_CR _hoops_AIIR _hoops_PHSP _hoops_HCH.
		if (!h3ddata->_hoops_RHH._hoops_ACH && h3ddata->_hoops_RHH._hoops_GCH == H3DFMT_A8R8G8B8)
			_hoops_IASP = false;

		mask	= H3DMASK_RGBA;
	}
	else if (h3ddata->_hoops_PI.mode) {
		flags |= H3DID_CREATE_SHADOW_MAP;

		// _hoops_PCH _hoops_RPSP, _hoops_HHSP _hoops_IHSP.
		_hoops_AASP = true;
		_hoops_HASP  = true;
		_hoops_GASP	= false;
		mask	= H3DMASK_RGB;
	}
	else if (h3ddata->_hoops_CHSP.mode) {
		flags |= H3DID_CREATE_SIMPLE_SHADOW;

		// _hoops_CSH _hoops_RRP _hoops_IS _hoops_RPSP, _hoops_HIH _hoops_SHSP _hoops_APIR'_hoops_GRI _hoops_IHSP _hoops_RGSR
		_hoops_AASP = false;
		_hoops_HASP  = false;
		mask	= H3DMASK_RGBA;
	}
	else if (h3ddata->_hoops_SH.mode) {
		flags |= H3DID_CREATE_REFLECTION_PLANE;
		mask = H3DMASK_RGBA;
	}
	else if (h3ddata->glyph.mode) {
		// _hoops_GISP _hoops_GAR _hoops_SSPP _hoops_GAR _hoops_SSRR.
		_hoops_AASP = false;
		_hoops_HASP	= false;
		mask	= H3DMASK_RGBA;
		_hoops_GASP	= false;
		_hoops_IASP = false;
		_hoops_SASP = false;
	}
	else {
		// _hoops_AGAR _hoops_ASCA
		if (type == T_FACES) {
			if (nr->_hoops_IHA->pattern != FP_SOLID) {
				flags |= H3DID_FACE_PATTERN;
				if (_hoops_RASP){
					flags |= H3DID_TRANSPARENCY_STIPPLE;
					_hoops_GASP = false;
				}
			}
			else if (!_hoops_GASP) {
				flags |= H3DID_WRITE_LUMINANCE;
				mask = H3DMASK_RGBA;
			}
		}
		else if (type == T_EDGES || type == T_LINES || type == _hoops_GPA) {
			if (!_hoops_GASP) {
				flags |= H3DID_WRITE_LUMINANCE;
				mask = H3DMASK_RGBA;
			}
		}
	}

	// _hoops_HCGA _hoops_AAIP _hoops_SR'_hoops_RISP _hoops_SAHR _hoops_AISP
	_hoops_PISP (h3ddata, _hoops_AASP);
	ENSURE_DEPTH_MASK (h3ddata, _hoops_HASP);
	_hoops_GPRP (h3ddata, mask);
	ENSURE_TRANSPARENCY (h3ddata, _hoops_GASP);
	_hoops_IPGP(h3ddata, _hoops_IASP);
	_hoops_HISP (h3ddata, _hoops_SASP);
	_hoops_RHSA (h3ddata, H3DCULL_NONE);

	// _hoops_AP
	return flags;
}
#define FALSE 0
#define TRUE 1
/*
 * _hoops_PGAA
 *
 * _hoops_RAP _hoops_SIC _hoops_RRSP _hoops_PPR _hoops_GRH _hoops_CI _hoops_AAP.
 * _hoops_ARSP _hoops_RRGR _hoops_PRSP _hoops_GAPA _hoops_RH _hoops_HRSP _hoops_IRSP _hoops_IIGR _hoops_CRSP.
 */
int _hoops_IISP(H3DData *h3ddata,
								  Net_Rendition const & nr,
								  H3D_Vertex_Buffer_Style _hoops_APHA,
								  int type,
								  bool _hoops_CISP,
						          int _hoops_RASP,
								  int flags)
{
	// _hoops_SISP _hoops_GCSP _hoops_RCSP

	// _hoops_CHSR _hoops_RH _hoops_ACSP. _hoops_PCSP _hoops_PSAP _hoops_HRGR _hoops_RH _hoops_SHIR _hoops_SHCA _hoops_HCSP.
	flags = _hoops_SRSP(h3ddata, nr, type, _hoops_CISP, _hoops_RASP, flags);

	if (type == T_FACES) {
		_hoops_AGSP (h3ddata, nr->transform_rendition, FALSE);
	}

	if (_hoops_APHA != H3D_Partially_Shared_Vertices)
		_hoops_ICSP(h3ddata, H3DSHADE_GOURAUD);
	else {
		_hoops_ICSP(h3ddata, H3DSHADE_FLAT);
		flags |= H3DID_FLAT_SHADING;
	}

	// _hoops_AP
	return flags;
}


int _hoops_CCSP(Net_Rendition const & nr)
{
	H3DData *h3ddata = H3DD(nr->_hoops_SRA);
	int flags = 0;

	if (!BIT (nr->transform_rendition->matrix->data.flags, _hoops_HASA))
		HI_Validate_Matrix_NEG3X3((_hoops_HRPA alter *)&nr->transform_rendition->matrix->data);

	h3ddata->_hoops_IASA = BIT (nr->transform_rendition->matrix->data._hoops_RAGR, _hoops_CASA);

	if (!BIT (nr->transform_rendition->_hoops_IPH->data.flags, _hoops_HASA))
		HI_Validate_Matrix_NEG3X3((_hoops_HRPA alter *)&nr->transform_rendition->_hoops_IPH->data);

	h3ddata->_hoops_SCSP = BIT (nr->transform_rendition->_hoops_IPH->data._hoops_RAGR, _hoops_CASA);

	// _hoops_AHH: _hoops_CGP _hoops_RH _hoops_GSSP _hoops_RSSP _hoops_ASSP'_hoops_RA _hoops_PSSP _hoops_HSSP _hoops_RSSP, _hoops_SR _hoops_RRP _hoops_IS _hoops_ISSP _hoops_RH _hoops_CSSP
	// _hoops_IIGR _hoops_RH _hoops_GSSR _hoops_IHAA
	if (h3ddata->_hoops_IASA) {
		if (BIT (nr->transform_rendition->heuristics, _hoops_GPSA))
			flags |= H3DID_NORMAL_FLIP_NEGATIVE;
	}
	else {
		if (BIT (nr->transform_rendition->heuristics, _hoops_SASA))
			flags |= H3DID_NORMAL_FLIP_NEGATIVE;
	}
	if (h3ddata->_hoops_SCSP)
		flags |= H3DID_RIGHT_HANDED_MATRIX;

	return flags;
}


/**
 * _hoops_PGAA
 *
 * _hoops_HCGA _hoops_CI _hoops_HRP _hoops_IS _hoops_RH _hoops_CHIA _hoops_CI.
 */
void _hoops_SSSP(H3DData *h3ddata,
							  Net_Rendition const & nr,
							  H3DShader *_hoops_RSR)
{
	ASSERT (_hoops_RSR != null);
	_hoops_GGGH (h3ddata, nr, _hoops_RSR);
	_hoops_AHSA (h3ddata, nr, T_FACES, _hoops_RSR);

	// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_RGGH, _hoops_ASRA _hoops_IPPA
	if (h3ddata->_hoops_SH.mode) {
		_hoops_RSR->_hoops_GIPA(h3ddata->_hoops_SH._hoops_AIPA);
	}
}


void _hoops_AGGH (
		H3DData alter *h3ddata,
		_hoops_HRPA const *mat,
		H3DShader alter *_hoops_RSR)
{
	float temp[16];
	ASSERT (h3ddata->_hoops_PGGH[0] == 0);
	_hoops_AIGA (h3ddata->_hoops_ISGA, 16, float, h3ddata->_hoops_PGGH);
	_hoops_AIGA (h3ddata->_hoops_IACR, 16, float, h3ddata->_hoops_HGGH);
	HI_Matmul_44_by_44 (&mat->elements[0][0], h3ddata->_hoops_IACR, temp);
	_hoops_AIGA (temp, 16, float, h3ddata->_hoops_IACR);
	HI_Matmul_44_by_44 (h3ddata->_hoops_IACR, h3ddata->_hoops_SPSR, h3ddata->_hoops_ISGA);
	_hoops_RSR->_hoops_CCGA (h3ddata);
}


void _hoops_IGGH (
		H3DData alter *h3ddata,
		H3DShader alter *_hoops_RSR)
{
	_hoops_AIGA (h3ddata->_hoops_PGGH, 16, float, h3ddata->_hoops_ISGA);
	_hoops_AIGA (h3ddata->_hoops_HGGH, 16, float, h3ddata->_hoops_IACR);
	h3ddata->_hoops_PGGH[0] = 0;
	h3ddata->_hoops_HGGH[0] = 0;
	_hoops_RSR->_hoops_CCGA (h3ddata);
}


bool _hoops_ISR (Net_Rendition const &nr, _hoops_RCR const *_hoops_CGGH, _hoops_RCR const *_hoops_SGGH)
{
	_hoops_GRGH const &_hoops_RRGH = nr->_hoops_IRR;

	if (_hoops_CGGH == _hoops_SGGH)
		return true;

	// _hoops_ARGH _hoops_PRGH _hoops_AII _hoops_PPR _hoops_HRGH
	if (_hoops_CGGH->_hoops_RSCP != _hoops_SGGH->_hoops_RSCP ||
		_hoops_CGGH->_hoops_PSR != _hoops_SGGH->_hoops_PSR)
		return false;

	// _hoops_ARGH _hoops_IRGH _hoops_HH _hoops_HCIA; _hoops_SSIA _hoops_RGAR _hoops_CRGH _hoops_GH _hoops_RPP _hoops_SSIA _hoops_CHR _hoops_HAR _hoops_SRGH
	if (_hoops_CGGH->_hoops_GAGH != _hoops_SGGH->_hoops_GAGH) {
		if (_hoops_CGGH->_hoops_GAGH && _hoops_SGGH->_hoops_GAGH) {
			_hoops_RPRA *_hoops_RAGH = &_hoops_CGGH->_hoops_GAGH->matrix.elements[0];
			_hoops_RPRA *_hoops_AAGH = &_hoops_SGGH->_hoops_GAGH->matrix.elements[0];
			if (_hoops_PAGH(_hoops_RAGH, 4*sizeof(_hoops_RPRA), _hoops_AAGH) != 0)
				return false;	// _hoops_GIPR _hoops_HCIA _hoops_GRAA-_hoops_IRAP, _hoops_HAGH _hoops_IAGH
		}
		else
			return false;		// _hoops_SPR _hoops_RSGA _hoops_IRAP, _hoops_SPR _hoops_RSGA _hoops_GRAA-_hoops_IRAP
	}

	// _hoops_ARGH _hoops_CAGH _hoops_HH _hoops_HCIA; _hoops_RGAR _hoops_SAGH _hoops_RPP _hoops_SCH _hoops_GPGH'_hoops_RA _hoops_SRGH _hoops_IS _hoops_RPGH _hoops_CCA
	if (!_hoops_RRGH->_hoops_APGH->matrix._hoops_PPGH()) {
		bool _hoops_HPGH = BIT(_hoops_CGGH->flags, _hoops_IPGH);
		bool _hoops_CPGH = BIT(_hoops_SGGH->flags, _hoops_IPGH);
		if (_hoops_HPGH != _hoops_CPGH)
			return false;
	}

	return true;
}


const char *_hoops_SCPR()
{
	static char buffer[2048] = {0};
	char *ptr;

	if (buffer[0] != 0)
		return buffer;

	if (getenv("H3D_SHADER_DEBUG")) {
		sprintf (buffer, __FILE__);
		ptr = strrchr (buffer, '\\');
		if (!ptr)
			return null;
		*ptr = '\0';
		return buffer;
	}
	else
		return null;
}



/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_SPGH
*****************************************************************************
*****************************************************************************/

void _hoops_GHGH(H3DData *h3ddata, _hoops_RCR const *txr, unsigned char *_hoops_SISA, int pitch)
{
	H3D_Color_Format _hoops_SHAP = h3ddata->_hoops_SHAP;

	if (txr->_hoops_RHGH->format == _hoops_AHGH) {
		int w =  txr->_hoops_RHGH->width;
		int h = txr->_hoops_RHGH->height;
		if (pitch == 0 || pitch == w) {
			_hoops_AIGA (txr->_hoops_RHGH->_hoops_PHGH, w*h, unsigned char, _hoops_SISA);
		}
		else {
			for (int y = 0; y < h; y++) {
				unsigned char *d_row = _hoops_SISA + pitch * y;
				_hoops_AIGA (txr->_hoops_RHGH->_hoops_PHGH, w, unsigned char, d_row);
			}
		}
	}
	else if (txr->_hoops_RHGH->format == _hoops_HHGH) {
		// _hoops_ISGP _hoops_RGR _hoops_SIPP _hoops_RH _hoops_HAPR _hoops_IS _hoops_CRHR _hoops_IHGH
		if (h3ddata->_hoops_CHGH) {
			if (pitch == 0)
				pitch = 3 * txr->_hoops_RHGH->width;
			for (int y = 0; y < txr->_hoops_RHGH->height; y++) {
				_hoops_SHGH const * _hoops_GIGH = (_hoops_SHGH alter *) txr->_hoops_RHGH->rasters[y];
				_hoops_SHGH *d_row = (_hoops_SHGH *)(_hoops_SISA + pitch * y);
				_hoops_AIGA (_hoops_GIGH, txr->_hoops_RHGH->width, _hoops_SHGH, d_row);
			}
		}
		else if (_hoops_SHAP == H3D_COLOR_ARGB) {
			if (pitch == 0)
				pitch = 4 * txr->_hoops_RHGH->width;
			for (int y = 0; y < txr->_hoops_RHGH->height; y++) {
				_hoops_SHGH const * _hoops_GIGH = (_hoops_SHGH alter *) txr->_hoops_RHGH->rasters[y];
				unsigned char *d_row = _hoops_SISA + pitch * y;
				for (int x = 0; x < txr->_hoops_RHGH->width; x++) {
					// _hoops_RIGH
					*d_row++ = (unsigned char)(_hoops_GIGH[x].b);
					*d_row++ = (unsigned char)(_hoops_GIGH[x].g);
					*d_row++ = (unsigned char)(_hoops_GIGH[x].r);

					if (!h3ddata->_hoops_CHGH)
						*d_row++ = (unsigned char)(255);
				}
			}
		}
		else if (_hoops_SHAP == H3D_COLOR_ABGR) {
			if (pitch == 0)
				pitch = 4 * txr->_hoops_RHGH->width;
			for (int y = 0; y < txr->_hoops_RHGH->height; y++) {
				_hoops_SHGH const * _hoops_GIGH = (_hoops_SHGH alter *) txr->_hoops_RHGH->rasters[y];
				unsigned char *d_row = _hoops_SISA + pitch * y;
				for (int x = 0; x < txr->_hoops_RHGH->width; x++) {
					// _hoops_RIGH
					*d_row++ = (unsigned char)(_hoops_GIGH[x].r);
					*d_row++ = (unsigned char)(_hoops_GIGH[x].g);
					*d_row++ = (unsigned char)(_hoops_GIGH[x].b);

					if (!h3ddata->_hoops_CHGH)
						*d_row++ = (unsigned char)(255);
				}
			}
		}
	}
	else if (txr->_hoops_RHGH->format == Image_RGBA32) {
		// _hoops_ISGP _hoops_RGR _hoops_SIPP _hoops_RH _hoops_HAPR _hoops_IS _hoops_CRHR _hoops_IHGH
		if (_hoops_SHAP == H3D_COLOR_ARGB) {
			if (pitch == 0)
				pitch = 4 * txr->_hoops_RHGH->width;
			for (int y = 0; y < txr->_hoops_RHGH->height; y++) {
				_hoops_AIGH const * _hoops_GIGH = (_hoops_AIGH alter *) txr->_hoops_RHGH->rasters[y];
				unsigned char *d_row = _hoops_SISA + pitch * y;
				for (int x = 0; x < txr->_hoops_RHGH->width; x++) {
					// _hoops_RIGH
					*d_row++ = (unsigned char)(_hoops_GIGH[x].b);
					*d_row++ = (unsigned char)(_hoops_GIGH[x].g);
					*d_row++ = (unsigned char)(_hoops_GIGH[x].r);
					*d_row++ = (unsigned char)(_hoops_GIGH[x].a);
				}
			}
		}
		else if (_hoops_SHAP == H3D_COLOR_ABGR) {
			if (pitch == 0)
				pitch = 4 * txr->_hoops_RHGH->width;
			for (int y = 0; y < txr->_hoops_RHGH->height; y++) {
				_hoops_AIGH const * _hoops_GIGH = (_hoops_AIGH alter *) txr->_hoops_RHGH->rasters[y];
				unsigned char *d_row = _hoops_SISA + pitch * y;
				for (int x = 0; x < txr->_hoops_RHGH->width; x++) {
					// _hoops_RIGH
					*d_row++ = (unsigned char)(_hoops_GIGH[x].r);
					*d_row++ = (unsigned char)(_hoops_GIGH[x].g);
					*d_row++ = (unsigned char)(_hoops_GIGH[x].b);
					*d_row++ = (unsigned char)(_hoops_GIGH[x].a);
				}
			}
		}
	}
	else {
		_hoops_IPR (HEC_TEXTURE, HES_PROCEDURAL_ERROR,
				"Unexpected image texture format.");
	}
}

H3DTexture * _hoops_PIGH (
	H3DData alter *h3ddata,
	Net_Rendition const &  nr,
	_hoops_RCR alter *txr,
	int _hoops_GCI)
{
	(void)(_hoops_GCI);

	_hoops_GACR alter *dl;
	H3D_Display_List alter *odl=0;

	bool _hoops_RACR;
	_hoops_HIGH _hoops_IIGH=0;
	H3DTexture * _hoops_CIGH = null;

	// _hoops_AICP _hoops_AHPA _hoops_HH _hoops_PGRR _hoops_HII _hoops_PCPA _hoops_RH _hoops_RHPP _hoops_SIGH _hoops_SCH _hoops_PAH _hoops_GCGH.
	int const _hoops_RCGH = _hoops_AHIA(h3ddata->_hoops_ACGH._hoops_PCGH, h3ddata->_hoops_ACGH._hoops_HCGH);
	int _hoops_ICGH = 512;
	int _hoops_CCGH = 16;

	// _hoops_PGPR _hoops_RHI-_hoops_SCGH _hoops_GSGH _hoops_AI _hoops_PAH _hoops_SHH _hoops_GSIA _hoops_RSGH. _hoops_CGP _hoops_IRS _hoops_GSGH _hoops_HRGR _hoops_IGI _hoops_IH _hoops_SPI,
	// _hoops_SR _hoops_SAHR _hoops_HH _hoops_CCA _hoops_RH _hoops_SRS _hoops_HSP _hoops_GAR _hoops_ASGH.
	bool const _hoops_PSGH = BIT(txr->flags, _hoops_AIA) && (_hoops_GCI == _hoops_HSGH);
	bool const _hoops_ISGH = BIT(txr->flags, _hoops_CSGH);

	if (txr->image && 
		BIT (txr->image->flags, _hoops_SSGH) &&
		txr->image->format != _hoops_GGRH &&
		txr->image->format != _hoops_RGRH &&
		txr->image->format != _hoops_AGRH) {

		//_hoops_RH _hoops_PGRH _hoops_HGRH _hoops_CHH _hoops_HS _hoops_IS _hoops_SHH _hoops_IRS _hoops_IGRH _hoops_HAGH _hoops_IH _hoops_CGRH-_hoops_RGAR _hoops_SGRH _hoops_AI
		ASSERT (!BIT (txr->image->flags, _hoops_GRRH));  

		//_hoops_SGRH _hoops_RRRH _hoops_PAH _hoops_RGAR _hoops_SHH _hoops_IGI _hoops_GAR-_hoops_HRGR, _hoops_HIS _hoops_RH _hoops_ASGH _hoops_ARRH _hoops_HGRH _hoops_ASSP'_hoops_RA _hoops_GHAA
		_hoops_RACR = _hoops_AACR(nr, &txr->image->_hoops_GAHA, &dl, &odl, H3D_DL_TEXTURE);

		H3DFORMAT format = H3DFMT_DXT1;

		if (!txr->_hoops_RHGH) {
			txr->_hoops_RHGH = txr->image;
			_hoops_PRRH (txr->_hoops_RHGH);
		}

		if (!h3ddata->_hoops_HRRH) {
			HE_ERROR (HEC_TEXTURE, HES_UNSUPPORTED_DEVICE,
					"S3 Texture compression not supported on this hardware.");
			return 0;
		}

		switch (txr->image->format) {
			case _hoops_IRRH: 
				format = H3DFMT_DXT1;
				break;
			case _hoops_CRRH: 
				format = H3DFMT_DXT3;
				break;
			case _hoops_SRRH: 
				format = H3DFMT_DXT5;
				break;

			case _hoops_GGRH:
			case _hoops_RGRH:
			case _hoops_AGRH:
			default:
				_hoops_IPR (HEC_TEXTURE, HES_PROCEDURAL_ERROR,
						"Unexpected compressed texture format.");
				return 0;
		}

		if (_hoops_RACR) {
			int _hoops_GARH = H3DTEXUSAGE_DEFAULT;
			if (txr->_hoops_RARH == _hoops_AARH || txr->_hoops_RARH == _hoops_PARH) {
				// _hoops_AGHP _hoops_HCR _hoops_HARH
				_hoops_GARH |= H3DTEXUSAGE_AUTOGENMIPMAP;
			}

			h3ddata->_hoops_GSCR->CreateTexture(txr->image->width, txr->image->height,
				0, _hoops_GARH, format, &odl->item.texture.id);

			unsigned char *data;
			odl->item.texture.id->Lock(txr->_hoops_RHGH->_hoops_IARH, &data);
			COPY_MEMORY(txr->image->_hoops_PHGH, txr->image->_hoops_IARH, data);
			odl->item.texture.id->Unlock();	

			odl->_hoops_CARH = txr->image->_hoops_IARH;
			HOOPS_WORLD->_hoops_SARH += odl->_hoops_CARH;
			_hoops_GPRH(_hoops_RPRH)++;

			if (txr->_hoops_RARH == _hoops_AARH || txr->_hoops_RARH == _hoops_PARH)
				odl->item.texture.id->_hoops_APRH();
		}
		return odl->item.texture.id;
	}


	if (txr->_hoops_RHGH &&
		_hoops_GCI == _hoops_HSGH &&
		!BIT(txr->_hoops_RHGH->flags, _hoops_PPRH)) {
		_hoops_HPRH(txr->_hoops_RHGH);
		txr->_hoops_RHGH=0;
	}

	if (txr->image && 
		BIT(txr->image->flags, _hoops_GRRH) &&
		txr->_hoops_RHGH != txr->image)
	{
		if (txr->_hoops_RHGH) {
			_hoops_HPRH(txr->_hoops_RHGH);
			txr->_hoops_RHGH=0;
		}

		txr->_hoops_RHGH = txr->image;
		_hoops_PRRH(txr->_hoops_RHGH);
	}

	if (!txr->_hoops_RHGH) {
		/* _hoops_HHS _hoops_SGH _hoops_IPRH _hoops_CPRH */
		if (h3ddata->_hoops_ACGH._hoops_SPRH)
			_hoops_IIGH |= _hoops_GHRH;

		/* _hoops_RGAR _hoops_SGH _hoops_RIS _hoops_RRRH _hoops_PSP _hoops_RHRH _hoops_AHRH _hoops_PHRH */
		_hoops_IIGH |= _hoops_HHRH;

		if (BIT(nr->_hoops_ARA->_hoops_IHRH.options, _hoops_CHRH) &&
			_hoops_GCI != _hoops_SHRH)
			_hoops_IIGH |= _hoops_GIRH;

		if (_hoops_GCI == _hoops_HSGH)
			_hoops_IIGH |= _hoops_PPRH;

		if (BIT(txr->_hoops_SCR, _hoops_IGA) && !BIT(txr->_hoops_SCR, _hoops_PGA))
		    _hoops_IIGH |= _hoops_PPRH;

		if (txr->_hoops_RARH == _hoops_AARH)
			_hoops_IIGH |= _hoops_RIRH;

		if (txr->_hoops_RARH == _hoops_PARH)
			_hoops_IIGH |= _hoops_AIRH;

		if (h3ddata->_hoops_PIRH)
			_hoops_IIGH |= _hoops_GHRH;

		if (ANYBIT(txr->flags, _hoops_HIRH) ||
			txr->_hoops_HPIR._hoops_IIRH != 0.0f ||
			txr->_hoops_HPIR._hoops_CIRH != 1.0f ||
			txr->_hoops_HPIR._hoops_SIRH != 1.0f ||
			txr->_hoops_HPIR._hoops_IPIR.red != 0.0f ||
			txr->_hoops_HPIR._hoops_IPIR.green != 0.0f ||
			txr->_hoops_HPIR._hoops_IPIR.blue != 0.0f)
			_hoops_IIGH |= _hoops_GCRH;

		if (BIT(txr->_hoops_SCR, _hoops_RCRH) ||
		    _hoops_ICGH > _hoops_RCGH) {
			_hoops_ICGH = _hoops_RCGH;
		}

		if (_hoops_GCI == _hoops_ACRH && txr->image->width <= _hoops_ICGH && txr->image->height <= _hoops_ICGH) {
			if (BIT(_hoops_IIGH,_hoops_GHRH) && !BIT(txr->image->flags, _hoops_GHRH) ||
				txr->image->width < _hoops_CCGH ||
				txr->image->height < _hoops_CCGH)
				_hoops_IIGH |= _hoops_PCRH;
		}

		HD_Activate_Texture_Image(nr, txr, _hoops_IIGH, _hoops_CCGH, _hoops_ICGH, _hoops_CCGH, _hoops_ICGH);
	}

	_hoops_RACR = _hoops_AACR(nr, &txr->_hoops_RHGH->_hoops_GAHA, &dl, &odl, H3D_DL_TEXTURE);

	/* _hoops_GISA _hoops_RH _hoops_CSCP _hoops_HH _hoops_CARA */
	if (_hoops_RACR) {
		unsigned int _hoops_GARH = 0;

		// _hoops_SGAA _hoops_IS _hoops_SCIA _hoops_HCRH _hoops_PAPA
		unsigned int _hoops_ICRH = 1;

		if (txr->_hoops_RARH == _hoops_AARH || txr->_hoops_RARH == _hoops_PARH) {
			// _hoops_AGHP _hoops_HCR _hoops_HARH
			_hoops_GARH |= H3DTEXUSAGE_AUTOGENMIPMAP;
			_hoops_ICRH = 0;
		}

		// _hoops_ARGH _hoops_CCRH _hoops_SCRH _hoops_ISCP _hoops_GSRH.
		ASSERT(txr->_hoops_RHGH->width <= _hoops_RCGH && txr->_hoops_RHGH->height <= _hoops_RCGH);

		H3DFORMAT format = _hoops_RSRH (txr->_hoops_RHGH->format);

		// _hoops_GISA _hoops_GGSP _hoops_GPRR _hoops_IIGR _hoops_HH
		if (_hoops_PSGH) {
			ASSERT(txr->_hoops_RHGH->width == txr->_hoops_RHGH->height);  //_hoops_RRAA _hoops_AI _hoops_RGAR _hoops_IH _hoops_ASRH _hoops_ACAR
			H3DCubeTexture *id = null;
			h3ddata->_hoops_GSCR->CreateCubeTexture(
					txr->_hoops_RHGH->width, _hoops_ICRH, _hoops_GARH, &id);
			odl->item.texture.id = id;
		}
		else if (BIT(txr->flags, _hoops_CSGH)) {
			H3DTexture3D *id = null;
			h3ddata->_hoops_GSCR->_hoops_PSRH(
					txr->_hoops_RHGH->width, txr->_hoops_RHGH->height, txr->_hoops_ICR[2],
					_hoops_ICRH, _hoops_GARH, format, &id);
			odl->item.texture.id = id;
		}
		else
			h3ddata->_hoops_GSCR->CreateTexture(
					txr->_hoops_RHGH->width, txr->_hoops_RHGH->height, 
					_hoops_ICRH, _hoops_GARH, format, &odl->item.texture.id);

		if (odl->item.texture.id == null) {
			HE_ERROR(h3ddata->_hoops_HSRH, h3ddata->_hoops_HSRH,
				"Texture creation failed! Out of memory.");
		}
	}
	_hoops_CIGH = odl->item.texture.id;

	/* _hoops_PHIR _hoops_HH _hoops_PIH */
	if (_hoops_RACR && _hoops_CIGH) {

		// _hoops_CISA _hoops_GGR _hoops_RH _hoops_HH _hoops_PIH
		unsigned char* _hoops_SISA;
		int pitch;

		if (_hoops_PSGH) {
			// _hoops_ISRH _hoops_HH - _hoops_CISA _hoops_GRR _hoops_HSP.
			H3DCubeTexture *_hoops_CSRH = static_cast<H3DCubeTexture*>(odl->item.texture.id);
			_hoops_RCR alter * _hoops_SSRH = null;

			// _hoops_GGAH _hoops_HII _hoops_RGAH _hoops_IS _hoops_AGAH _hoops_HSP _hoops_CIHA
			int const face_indices[H3DFACE_COUNT] =
			{
				// _hoops_PGAH, _hoops_HGAH
				3, 2,
				// _hoops_IGAH, _hoops_CGAH
				5, 4,
				// _hoops_SGAH, _hoops_GRAH
				1, 0,
			};

			for (int i = 0; i < H3DFACE_COUNT; ++i) {
				// _hoops_RRAH _hoops_HSP _hoops_ARAH-_hoops_HH
				_hoops_SSRH = txr->_hoops_PRAH[face_indices[i]];
				HD_Activate_Texture_Image(nr, _hoops_SSRH, _hoops_IIGH, _hoops_CCGH, _hoops_ICGH, _hoops_CCGH, _hoops_ICGH);

				// _hoops_HRAH _hoops_PPR _hoops_CISA _hoops_SCH
				if (_hoops_CSRH->Lock(static_cast<H3DFACE>(i), null, &_hoops_SISA, &pitch)) {
					_hoops_GHGH(h3ddata, _hoops_SSRH, _hoops_SISA, pitch);
					_hoops_GPRH(_hoops_RPRH)++;
					_hoops_CSRH->Unlock(static_cast<H3DFACE>(i));
				}

				// _hoops_HRHP
				HD_Clean_Texture_Image_Cache(nr, _hoops_SSRH);
			}
		}
		else if (_hoops_ISGH) {
			H3DTexture3D *_hoops_IRAH = static_cast<H3DTexture3D*>(odl->item.texture.id);
			_hoops_RCR alter * _hoops_CRAH = null;
			unsigned char *ptr;
			int _hoops_SRAH, _hoops_GAAH;

			ASSERT (txr->_hoops_ICR[2] == _hoops_IRAH->_hoops_RAAH());
			if (_hoops_IRAH->Lock(&_hoops_SISA, &_hoops_SRAH, &_hoops_GAAH)) {
				ptr = _hoops_SISA;
				if (_hoops_GAAH == 0)
					_hoops_GAAH = (_hoops_IRAH->Width() * _hoops_IRAH->Height() * _hoops_IRAH->_hoops_AAAH());
				for (int i = 0; i < txr->_hoops_ICR[2] ; ++i) {
					_hoops_CRAH = txr->_hoops_PRAH[i * txr->_hoops_ICR[0] * txr->_hoops_ICR[1]];
					HD_Activate_Texture_Image(nr, _hoops_CRAH, _hoops_IIGH, _hoops_CCGH, _hoops_ICGH, _hoops_CCGH, _hoops_ICGH);
					_hoops_GHGH(h3ddata, _hoops_CRAH, ptr, _hoops_SRAH);
					ptr += _hoops_GAAH;
				}
				_hoops_IRAH->Unlock();
				_hoops_GPRH(_hoops_RPRH)++;
			}
			else
				HE_ERROR (HEC_TEXTURE, HES_PROCEDURAL_ERROR, "error reported during 3d texture lock");

		}
		else {
			bool _hoops_PAAH = false;
			if (BIT (txr->_hoops_RHGH->flags, _hoops_HAAH)) {
				// _hoops_IAAH _hoops_RH _hoops_HH
				_hoops_PAAH = _hoops_CIGH->_hoops_CAAH(txr);
			}

			if (!_hoops_PAAH) {
				_hoops_CIGH->_hoops_SAAH(txr);
			}
		}

		if (txr->_hoops_RARH == _hoops_AARH || txr->_hoops_RARH == _hoops_PARH)
			_hoops_CIGH->_hoops_APRH();

		if (BIT (txr->_hoops_RHGH->flags, _hoops_GPAH)) {
			Image *image = txr->_hoops_RHGH;
			int _hoops_RPAH = (long)image->row_bytes * (long)image->height;

			ASSERT (BIT (image->flags, _hoops_HHRH));
			ASSERT (!BIT (image->flags, _hoops_SSGH));
			FREE_ARRAY (image->_hoops_PHGH, _hoops_RPAH, char);
			if (image->rasters != null) {
				FREE_ARRAY (image->rasters, image->height, void *);
				image->rasters = null;
			}
			image->_hoops_PHGH = null;
			image->flags |= (_hoops_GRRH|_hoops_APAH);
			odl->_hoops_PPAH->owner = (_hoops_HPAH *)txr->_hoops_RHGH;
		}
		HD_Clean_Texture_Image_Cache(nr, txr);
	}

	UNREFERENCED (_hoops_GCI);
	return _hoops_CIGH;
}



/*
 * _hoops_PGAA
 */
local int _hoops_IPAH (int _hoops_CPAH) {
	int _hoops_SPAH;
	for (_hoops_SPAH = 64;	 _hoops_SPAH < _hoops_CPAH;  _hoops_SPAH = _hoops_SPAH << 1) {}
	return _hoops_SPAH;
}


/*
 * _hoops_PGAA
 */
H3DTexture * _hoops_GHAH (H3DData alter * h3ddata, Net_Rendition const &  nr)
{
	_hoops_RHAH const *_hoops_CSIR	= nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;
	_hoops_AHAH const &_hoops_PHAH			= nr->_hoops_ARA->_hoops_IHRH;
	int _hoops_HHAH			= _hoops_CSIR->length;
	int width					= _hoops_IPAH (4 * _hoops_HHAH);

	if((BIT(nr->_hoops_IRR->_hoops_CSA, _hoops_GGP) ||
		BIT(nr->_hoops_IRR->_hoops_CSA, _hoops_RCP)) &&
		nr->_hoops_ASIR->_hoops_PSIR->_hoops_HSIR > 0) {
		_hoops_CSIR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_ISIR;
		_hoops_HHAH = _hoops_CSIR->length;
		width = _hoops_IPAH (4 * _hoops_HHAH);
	}

	// _hoops_CRSR _hoops_IHAH _hoops_CHR _hoops_SR _hoops_GRP? _hoops_CHAH _hoops_PPR _hoops_GSSR _hoops_SHAH _hoops_HS _hoops_GIAH _hoops_RIAH, _hoops_HIS _hoops_SGS _hoops_CGPR _hoops_PCCP
	// _hoops_AIAH-_hoops_PIAH _hoops_HGIR _hoops_HRGR _hoops_ASAR-_hoops_IGI _hoops_GGR _hoops_HHSA-_hoops_HIAH _hoops_CCH _hoops_SCH _hoops_IIAH _hoops_CIAH.
	bool const _hoops_SIAH = BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI);
	H3DTexture_Hash *& _hoops_GCAH = _hoops_SIAH ? h3ddata->_hoops_RCAH : h3ddata->_hoops_ACAH;

	// _hoops_PHAA _hoops_ARPR _hoops_RH _hoops_IHAH _hoops_RPP _hoops_SCH _hoops_ASSP'_hoops_RA _hoops_GGCA _hoops_GAPR.
	if (!_hoops_GCAH) {
		const size_t _hoops_PCAH = 64;
		_hoops_GCAH = POOL_NEW(HOOPS_WORLD->memory_pool, H3DTexture_Hash)(HOOPS_WORLD->memory_pool, _hoops_PCAH);
		ASSERT(_hoops_GCAH);
	}

	// _hoops_HCAH _hoops_RH _hoops_HGIR _hoops_GGR _hoops_RH _hoops_IHAH
	H3DTexture *texture = null;
	if (_hoops_GCAH->LookupItem((long) _hoops_CSIR->_hoops_HAA, &texture) != H3DTexture_Hash::Success) {

		// _hoops_ICAH _hoops_IS _hoops_ARPR _hoops_PPR _hoops_CISA _hoops_GGR _hoops_IRS _hoops_CCAH _hoops_HH.
		unsigned int _hoops_GARH = 0;
		h3ddata->_hoops_GSCR->CreateTexture(width, 2, 1, _hoops_GARH, H3DFMT_A8R8G8B8, &texture);
		ASSERT(texture);

		int i, index, column;

		// _hoops_CISA _hoops_GGR _hoops_RH _hoops_HH _hoops_PIH
		unsigned char* _hoops_SISA;
		int pitch;
		texture->Lock(null, &_hoops_SISA, &pitch);
		{
			for (i = 0; i < 2; i++)
				for (column = 0; column < width; column++) {
					index = column % _hoops_HHAH;
					RGB color;
					
					if (BIT(_hoops_PHAH.options, _hoops_CHRH))
						color = HD_Apply_Color_Effects(_hoops_CSIR->_hoops_HAA[index]._hoops_CSHR, _hoops_PHAH);
					else
						color = _hoops_CSIR->_hoops_HAA[index]._hoops_CSHR;

					if (h3ddata->_hoops_SHAP == H3D_COLOR_ARGB) {
						*_hoops_SISA++ = (unsigned char)(color.blue * 255);
						*_hoops_SISA++ = (unsigned char)(color.green * 255);
						*_hoops_SISA++ = (unsigned char)(color.red * 255);
						*_hoops_SISA++ = (unsigned char)(255);
					}
					else if (h3ddata->_hoops_SHAP == H3D_COLOR_ABGR) {
						*_hoops_SISA++ = (unsigned char)(color.red * 255);
						*_hoops_SISA++ = (unsigned char)(color.green * 255);
						*_hoops_SISA++ = (unsigned char)(color.blue * 255);
						*_hoops_SISA++ = (unsigned char)(255);
					}
				}
		}
		texture->Unlock();

		// _hoops_AGGA _hoops_SCAH _hoops_RH _hoops_HH _hoops_IH _hoops_SPS _hoops_GHIR
		_hoops_GCAH->InsertItem((long) _hoops_CSIR->_hoops_HAA, texture);
	}

	// _hoops_GSAH _hoops_IS _hoops_RSAH _hoops_CCA _hoops_RHPP _hoops_ASAH.
	h3ddata->_hoops_CSC->_hoops_PSAH = texture;
	h3ddata->_hoops_CSC->_hoops_GRIR = width;

	// _hoops_AP
	return texture;
}



/*
 * _hoops_PGAA
 */
int _hoops_HSAH (
	Display_Context alter * dc,
	Line_Style const & style)
{
	H3DData alter *h3ddata = H3DD (dc);
	POINTER_SIZED_INT _hoops_SICP = 0;

	//_hoops_ARPR _hoops_AI _hoops_IH _hoops_RH _hoops_HSP _hoops_PAIA
	if (h3ddata->_hoops_ISAH == null) {
		int _hoops_CSAH = 32;

		h3ddata->_hoops_GSCR->CreateTexture(32, _hoops_CSAH, 1,
			0, H3DFMT_A8R8G8B8, &h3ddata->_hoops_ISAH);

		h3ddata->_hoops_GCCP = POOL_NEW(dc->memory_pool, _hoops_PCS)(dc->memory_pool, _hoops_CSAH*2);
	}


	if (h3ddata->_hoops_GCCP->LookupItem(style->name.text, &_hoops_SICP) == _hoops_SSAH::Failed) {

		_hoops_SICP = h3ddata->_hoops_GGPH;
		h3ddata->_hoops_GCCP->InsertItem(style->name.text, h3ddata->_hoops_GGPH);

		H3DRect _hoops_RGPH;
		_hoops_RGPH.left = 0;
		_hoops_RGPH.right = 32;
		_hoops_RGPH.top = h3ddata->_hoops_GGPH++;
		_hoops_RGPH.bottom = h3ddata->_hoops_GGPH;

		unsigned char *_hoops_SISA;
		int pitch;
		h3ddata->_hoops_ISAH->Lock(&_hoops_RGPH, &_hoops_SISA, &pitch);
		{
			int k;
			for (k = 0; k < 32; k++) {
				*_hoops_SISA++ = (unsigned char)255;
				*_hoops_SISA++ = (unsigned char)255;
				*_hoops_SISA++ = (unsigned char)255;

				if (BIT(style->bits32, 1 << k) == 0)
					*_hoops_SISA++ = (unsigned char) 0;
				else
					*_hoops_SISA++ = (unsigned char) 255;
			}
		}
		h3ddata->_hoops_ISAH->Unlock();
	}

	return _hoops_SICP;
}


/*
 * _hoops_PGAA
 */
void _hoops_AGPH (
	Display_Context alter * dc,
	int _hoops_CRIA,
	int _hoops_PGPH,
	int _hoops_RASP)
{
	H3DData alter *h3ddata = H3DD (dc);
	int _hoops_HGPH, _hoops_IGPH;
	int _hoops_CGPH, _hoops_SGPH;
	const unsigned char *_hoops_GRPH;

	if (_hoops_RASP > 0) {
		//_hoops_RRPH (_hoops_RRAP->_hoops_ARPH[_hoops_PRPH]);
		_hoops_GRPH = (const unsigned char *) _hoops_HRPH[64 -_hoops_RASP];
		_hoops_CGPH = _hoops_SGPH = _hoops_HGPH = _hoops_IGPH = 8;
	}
	else if (_hoops_CRIA == FP_USER_DEFINED) {
		h3ddata->_hoops_IRPH = _hoops_PGPH;
		return;
	}
	else if (_hoops_CRIA < _hoops_CRPH) {
		_hoops_GRPH = (const unsigned char *) dc->_hoops_GRPH[_hoops_CRIA];
		_hoops_CGPH = _hoops_SGPH = 16;
		_hoops_HGPH = 32;
		_hoops_IGPH = 8;
	}
	else
		return;


	if (h3ddata->_hoops_SRPH[_hoops_CRIA] == null) {
		H3DTexture *pattern = null;

		//_hoops_ARPR _hoops_AI _hoops_IH _hoops_RH _hoops_HSP _hoops_PAIA
		h3ddata->_hoops_GSCR->CreateTexture(_hoops_CGPH, _hoops_SGPH, 1, 0, H3DFMT_A8R8G8B8, &pattern);

		unsigned char *_hoops_SISA;
		int pitch;
		pattern->Lock(null, &_hoops_SISA, &pitch);
		{
			int j, k;
			for (j = 0; j < _hoops_HGPH; j++) {
				for (k = 0; k < _hoops_IGPH; k++) {
					*_hoops_SISA++ = (unsigned char)255;
					*_hoops_SISA++ = (unsigned char)255;
					*_hoops_SISA++ = (unsigned char)255;

					if (BIT(_hoops_GRPH[j], (1 << k)))
						*_hoops_SISA++ = (unsigned char) 0;
					else
						*_hoops_SISA++ = (unsigned char) 255;
				}
			}
		}
		pattern->Unlock();

		h3ddata->_hoops_SRPH[_hoops_CRIA] = pattern;
	}
}

/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_GAPH _hoops_RAPH
*****************************************************************************
*****************************************************************************/
/*
 * _hoops_PGAA
 */
void _hoops_AAPH (
	void *					_hoops_PAPH,
	int						_hoops_HAPH,
	Point const *		p1,
	Point const *		p2,
	Point const *		_hoops_IAPH,
	int						s1,
	int						s2,
	int						_hoops_CAPH,
	Intersection const * i1,
	Intersection const * i2,
	Intersection const * _hoops_SAPH)
{
	struct concave_tri *pt = (struct concave_tri *) _hoops_PAPH;
	H3D_Color _hoops_GPPH = _hoops_CHAP(
		pt->h3ddata->_hoops_SHAP,
		pt->color._hoops_HRIR.r,
		pt->color._hoops_HRIR.g,
		pt->color._hoops_HRIR.b,
		pt->color._hoops_HRIR.a);

	if (pt->_hoops_RPPH) {
		if (pt->_hoops_APPH >= pt->_hoops_PPPH) {
			pt->_hoops_PPPH *= 2;
			pt->_hoops_HPPH->_hoops_IPPH(pt->_hoops_PPPH * 3);
		}

		pt->_hoops_HPPH->_hoops_AHCP(p1->x, p1->y + 0.5f, p1->z);
		pt->_hoops_HPPH->color(_hoops_GPPH);
		pt->_hoops_HPPH->_hoops_CPPH();

		pt->_hoops_HPPH->_hoops_AHCP(p2->x, p2->y + 0.5f, p2->z);
		pt->_hoops_HPPH->color(_hoops_GPPH);
		pt->_hoops_HPPH->_hoops_CPPH();

		pt->_hoops_HPPH->_hoops_AHCP(_hoops_IAPH->x, _hoops_IAPH->y + 0.5f, _hoops_IAPH->z);
		pt->_hoops_HPPH->color(_hoops_GPPH);
		pt->_hoops_HPPH->_hoops_CPPH();
	}
	else {
		if (pt->_hoops_APPH >= pt->_hoops_PPPH) {
			pt->_hoops_PPPH *= 2;
			pt->_hoops_SPPH->_hoops_IPPH(pt->_hoops_PPPH * 3);
		}

		pt->_hoops_SPPH->_hoops_AHCP(*p1);
		pt->_hoops_SPPH->_hoops_CPPH();

		pt->_hoops_SPPH->_hoops_AHCP(*p2);
		pt->_hoops_SPPH->_hoops_CPPH();

		pt->_hoops_SPPH->_hoops_AHCP(*_hoops_IAPH);
		pt->_hoops_SPPH->_hoops_CPPH();
	}

	pt->_hoops_APPH++;
	UNREFERENCED(_hoops_HAPH);
	UNREFERENCED(s1);
	UNREFERENCED(s2);
	UNREFERENCED(_hoops_CAPH);
	UNREFERENCED(i1);
	UNREFERENCED(i2);
	UNREFERENCED(_hoops_SAPH);
}

/*
 * _hoops_PGAA
 * _hoops_SIGP: _hoops_AISA _hoops_GHPH _hoops_HRGR _hoops_RHPH _hoops_IH _hoops_AHPH _hoops_ARAR
 * _hoops_PAGA: _hoops_RGR _hoops_CSAP _hoops_PHPH _hoops_CCA _hoops_RH _hoops_GHPH _hoops_SGS _hoops_HHPH _hoops_HRGR _hoops_IHPH _hoops_PPR _hoops_SGS
 * _hoops_SCH _hoops_HRGR _hoops_CHPH _hoops_IS _hoops_AA _hoops_AHPH _hoops_HAIR _hoops_SHPH _hoops_GIPH _hoops_GHGA _hoops_GPGR _hoops_RIPH.	_hoops_HGI
 * _hoops_GHPH _hoops_GHCA _hoops_SHH _hoops_AIPH.  _hoops_PIPH _hoops_HIPH _hoops_IH _hoops_IIPH _hoops_CIPH!
 */
void draw_concave_face (Net_Rendition const &  nr,
				   int count, struct concave_tri const * _hoops_SIPH)
{
	int _hoops_RPPH = _hoops_SIPH->_hoops_RPPH;
	Point alter *_hoops_GCPH;
	int alter *face_list;

	if (count == 0)
		return;

	/*
	 * _hoops_RAH _hoops_RH _hoops_HSP _hoops_HPP _hoops_RCPH _hoops_GGSR _hoops_IH _hoops_IRS _hoops_IHIR-_hoops_CSRA _hoops_HSSP
	 * _hoops_HHPH. _hoops_IPCP _hoops_ACPH _hoops_PCPH _hoops_PSCR _hoops_HCPH _hoops_RH
	 * _hoops_ICPH'_hoops_GRI _hoops_CCPH-_hoops_SCPH _hoops_PCPH.
	 */
	if (_hoops_RPPH)
		_hoops_GCPH = (Point alter *)_hoops_SIPH->points.dc;
	else
		_hoops_GCPH = (Point alter *)_hoops_SIPH->points._hoops_GSPH;

	/* _hoops_GCRR _hoops_IRS _hoops_RSPH _hoops_HSP _hoops_HIGR */
	{
		int alter *_hoops_ASPH;
		int vertex;

		ALLOC_ARRAY (_hoops_ASPH, count + 1, int);
		face_list = _hoops_ASPH;

		*_hoops_ASPH++ = count;
		vertex = 0;
		do
			*_hoops_ASPH++ = vertex;
		_hoops_RGGA (++vertex == count);
	}

	HI_Triangulate_Face_X (_hoops_GCPH, null, face_list,
						 face_list + count + 1, _hoops_SIPH->_hoops_PSPH ,
						 (void alter *) _hoops_SIPH);

	FREE_ARRAY (face_list, count + 1, int);

	UNREFERENCED(nr);
}


/* _hoops_RAGA _hoops_IRS _hoops_HSPH _hoops_ISPH _hoops_PAPR _hoops_GGR _hoops_CSPH, _hoops_PGSA _hoops_SSPH _hoops_SHS */
void _hoops_GGHH (Net_Rendition const & nr,
								  int count, struct concave_tri * _hoops_SIPH)
{
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	DC_Point const *pts = _hoops_SIPH->points.dc;
	/* _hoops_RRP _hoops_IS _hoops_RGHH _hoops_AGHH _hoops_PGHH _hoops_ARI... */
	DC_Point *buffer;
	int *face_list, *end;
	DC_Point _hoops_HGHH[4];
	int i;

	_hoops_HGHH[0].x = _hoops_IHCR->_hoops_AGAA.left - 2;
	_hoops_HGHH[0].y = _hoops_IHCR->_hoops_AGAA.bottom - 2;
	_hoops_HGHH[0].z = 0;
	_hoops_HGHH[1].x = _hoops_IHCR->_hoops_AGAA.left - 2;
	_hoops_HGHH[1].y = _hoops_IHCR->_hoops_AGAA.top + 2;
	_hoops_HGHH[1].z = 0;
	_hoops_HGHH[2].x = _hoops_IHCR->_hoops_AGAA.right + 2;
	_hoops_HGHH[2].y = _hoops_IHCR->_hoops_AGAA.top + 2;
	_hoops_HGHH[2].z = 0;
	_hoops_HGHH[3].x = _hoops_IHCR->_hoops_AGAA.right + 2;
	_hoops_HGHH[3].y = _hoops_IHCR->_hoops_AGAA.bottom - 2;
	_hoops_HGHH[3].z = 0;

	ALLOC_ARRAY (buffer, count + 4, DC_Point);
	_hoops_AIGA (_hoops_HGHH, 4, DC_Point, buffer);
	_hoops_AIGA (pts, count, DC_Point, buffer+4);

	ALLOC_ARRAY (face_list, count + 6, int);
	face_list[0] = 4;
	face_list[1] = 0;
	face_list[2] = 1;
	face_list[3] = 2;
	face_list[4] = 3;
	face_list[5] = -count;
	for (i = 0; i < count; i++) {
		face_list[i+6] = i+4;
	}
	_hoops_SIPH->points.dc = buffer;
	end = face_list + count + 6;
	HI_Triangulate_Face_X ((Point *)buffer, &_hoops_IRGA::_hoops_IGHH, face_list, end, _hoops_SIPH->_hoops_PSPH, (void alter *) _hoops_SIPH);
	FREE_ARRAY (face_list, count + 6, int);
	FREE_ARRAY (buffer, count + 4, DC_Point);
}

/* _hoops_RAGA _hoops_IRS _hoops_HSPH _hoops_ISPH _hoops_PAPR _hoops_GGR _hoops_CSPH, _hoops_PGSA _hoops_RH _hoops_ISPH */
void _hoops_CGHH (Net_Rendition const & nr,
								  int count, struct concave_tri * _hoops_SIPH)
{
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	DC_Point const *pts = _hoops_SIPH->points.dc;
	/* _hoops_RRP _hoops_IS _hoops_RGHH _hoops_AGHH _hoops_PGHH _hoops_ARI... */
	DC_Point *buffer;
	int *face_list, *end;
	DC_Point _hoops_HGHH[4];
	int i;

	_hoops_HGHH[0].x = _hoops_IHCR->_hoops_AGAA.left - 2;
	_hoops_HGHH[0].y = _hoops_IHCR->_hoops_AGAA.bottom - 2;
	_hoops_HGHH[0].z = 0;
	_hoops_HGHH[1].x = _hoops_IHCR->_hoops_AGAA.left - 2;
	_hoops_HGHH[1].y = _hoops_IHCR->_hoops_AGAA.top + 2;
	_hoops_HGHH[1].z = 0;
	_hoops_HGHH[2].x = _hoops_IHCR->_hoops_AGAA.right + 2;
	_hoops_HGHH[2].y = _hoops_IHCR->_hoops_AGAA.top + 2;
	_hoops_HGHH[2].z = 0;
	_hoops_HGHH[3].x = _hoops_IHCR->_hoops_AGAA.right + 2;
	_hoops_HGHH[3].y = _hoops_IHCR->_hoops_AGAA.bottom - 2;
	_hoops_HGHH[3].z = 0;

	ALLOC_ARRAY (buffer, count + 4, DC_Point);
	_hoops_AIGA (pts, count, DC_Point, buffer);

	ALLOC_ARRAY (face_list, count+1, int);
	face_list[0] = count;
	for (i = 0; i < count; i++) {
		face_list[i+1] = i;
	}
	_hoops_SIPH->points.dc = buffer;
	end = face_list + count + 1;
	HI_Triangulate_Face_X ((Point *)buffer, &_hoops_IRGA::_hoops_IGHH, face_list, end, _hoops_SIPH->_hoops_PSPH, (void alter *) _hoops_SIPH);
	FREE_ARRAY (face_list, count + 1, int);
	FREE_ARRAY (buffer, count + 4, DC_Point);
}

/*
 * _hoops_PGAA
 */
void _hoops_SGHH (
		Net_Rendition const & nr,
		Polygon const *polygon)
{
	Display_Context const *dc = nr->_hoops_SRA;
	H3DData alter *h3ddata = H3DD (dc);
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	Tristrip ts;
	struct concave_tri	pt;
	Point const *pts = polygon->points;
	int count = polygon->count;
	_hoops_ARPA plane;

	ZERO_STRUCT (&ts, Tristrip);
	ZERO_STRUCT (&pt, concave_tri);
	pt.h3ddata = h3ddata;
	pt.points._hoops_GSPH = pts;
	pt.color = nr->_hoops_IHA->color;
	pt._hoops_PSPH = _hoops_AAPH;
	pt._hoops_RPPH = false;
	pt._hoops_PPPH = polygon->count;

	H3DVertexFormat _hoops_PPCP(H3DVF_PT);
	pt._hoops_SPPH = NEW(H3DVertexBuffer)();
	pt._hoops_SPPH->_hoops_IRA(null, null, null, &_hoops_PPCP, pt._hoops_PPPH * 3);

	if (nr->_hoops_IHA->_hoops_AGP &&
		BIT (_hoops_IHCR->flags, _hoops_GRHH) &&
		BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES)) {
		if (!BIT (polygon->_hoops_RRHH, _hoops_ARHH))
			HI_Find_Polygon_Plane ((Polygon alter *) polygon);
		plane = polygon->plane;
		if (BIT(_hoops_IHCR->heuristics, _hoops_SASA))
			plane = -plane;
		ts._hoops_PRHH = &plane;
	}

	// _hoops_HRHH _hoops_RH _hoops_HSSP _hoops_PPR _hoops_PGSA
	draw_concave_face (nr, count, (struct concave_tri const *)&pt);

	// _hoops_IRHH _hoops_IRS _hoops_RSPH _hoops_CRHH _hoops_PPR _hoops_PGSA _hoops_AIH _hoops_CRSP
	ts._hoops_SRHA = DL_DO_NOT_DEFER | _hoops_SRHH |_hoops_GAHH | DL_TEMPORARY_DATA;
	ts._hoops_PHHA = pt._hoops_APPH;
	ts.total = ts._hoops_PHHA * 3;
	if (ts._hoops_PRHH) {
		ALLOC_ARRAY (ts.face_indices, ts.total, int);
		ZERO_ARRAY (ts.face_indices, ts.total, int);
	}
	ts.face_count = 1;

	ts.point_count = ts.total;
	ALLOC_ARRAY_CACHED(ts.points, ts.total, Point);
	ALLOC_ARRAY_CACHED(ts.lengths, ts._hoops_PHHA, int);
	ts._hoops_RAHH |= _hoops_AAHH; //_hoops_PAHH _hoops_HAR _hoops_HAHH, _hoops_HIH _hoops_SAHR _hoops_GGR _hoops_AGIR...
	for (int i = 0; i < ts._hoops_PHHA; i++)
		ts.lengths[i] = 3;

	ALLOC_ARRAY_CACHED(ts._hoops_AIHA, ts.total, int);
	for (int i = 0; i < ts.total; i++) {
		ts.points[i] = *((Point*)pt._hoops_SPPH->_hoops_IAHH(i));
		ts._hoops_AIHA[i] = i;
	}

	draw_3d_tristrip(nr, &ts);

	if (ts.face_indices)
		FREE_ARRAY (ts.face_indices, ts.total, int);
	FREE_ARRAY(ts._hoops_AIHA, ts.total, int);
	FREE_ARRAY(ts.points, ts.total, Point);
	FREE_ARRAY(ts.lengths, ts._hoops_PHHA, int);
	delete pt._hoops_SPPH;
}


/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_RAP _hoops_CAHH
*****************************************************************************
*****************************************************************************/
void H3DMatrixPerspectiveLH(float *matrix,
	float w,
	float h,
	float _hoops_SHCR,
	float _hoops_GICR,
	int _hoops_ACCR)
{
	SET_MEMORY(matrix, 16*sizeof(float), 0);
	matrix[0] = 2 * _hoops_SHCR / w;
	matrix[5] = 2 * _hoops_SHCR / h;
	matrix[10] = _hoops_ACCR * _hoops_GICR / (_hoops_GICR - _hoops_SHCR);
	matrix[11] = _hoops_ACCR;
	matrix[14] = (_hoops_SHCR * _hoops_GICR) / (_hoops_SHCR - _hoops_GICR);
}

void H3DMatrixOrthoLH(float *matrix,
	float w,
	float h,
	float _hoops_SHCR,
	float _hoops_GICR,
	int _hoops_ACCR)
{
	SET_MEMORY(matrix, 16*sizeof(float), 0);
	matrix[0] = 2 / w;
	matrix[5] = 2 / h;
	matrix[10] = _hoops_ACCR / (_hoops_GICR - _hoops_SHCR);
	matrix[14] = _hoops_SHCR / (_hoops_SHCR - _hoops_GICR);
	matrix[15] = 1;
}

#if !defined max
#define max(a,b) ((a > b) ? (a) : (b))
#endif
#if !defined min
#define min(a,b) ((a < b) ? (a) : (b))
#endif

void _hoops_SAHH (Net_Rendition const &  nr)
{
	H3DData *h3ddata = H3DD(nr->_hoops_SRA);
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	Int_Rectangle const &		_hoops_GPHH = _hoops_IHCR->_hoops_AGAA;

	if (h3ddata->glyph.mode) {
		// _hoops_SIAP _hoops_IS _hoops_RSIR _hoops_RPHH _hoops_HH
		_hoops_APHH (h3ddata, 0, 1);
		_hoops_PPHH (h3ddata, 0, 0, h3ddata->glyph._hoops_HAP, h3ddata->glyph._hoops_HAP);
		_hoops_HPHH (h3ddata, false);
		_hoops_RRIR(h3ddata, nr, false);

		// _hoops_IPHH _hoops_HII _hoops_ASPA _hoops_IS _hoops_GCCR _hoops_CPHH.
		float *	matrix = h3ddata->_hoops_PIGA;
		float const s = 2.0f / h3ddata->glyph._hoops_HAP;
		matrix[0] = (float) s;
		matrix[1] = (float) 0;
		matrix[2] = (float) 0;
		matrix[3] = (float) 0;

		matrix[4] = (float) 0;
		matrix[5] = (float) s;
		matrix[6] = (float) 0;
		matrix[7] = (float) 0;

		matrix[8] = (float) 0;
		matrix[9] = (float) 0;
		matrix[10] = (float) 1e-10;
		matrix[11] = (float) 0;

		matrix[12] = (float) 0;
		matrix[13] = (float) 0;
		matrix[14] = (float) 0;
		matrix[15] = (float) 1;
		return;
	}

	int width = dc->_hoops_RCGA.right - dc->_hoops_RCGA.left + 1;
	int height = dc->_hoops_RCGA.top - dc->_hoops_RCGA.bottom + 1;
	
	if (width < 1)
		width = 1;
	if (height < 1)
		height = 1;
	float _hoops_SPHH = 0;
	float _hoops_GHHH = 0;

	_hoops_APHH (h3ddata, 0, 1);
	_hoops_PPHH (h3ddata, 0, 0, width, height);
	if (_hoops_GPHH == dc->_hoops_RCGA) {
		_hoops_HPHH (h3ddata, false);
	}
	else {
		_hoops_HPHH (h3ddata, true);

		// _hoops_AHH: _hoops_RHHH _hoops_AHHH _hoops_HII _hoops_PHHH _hoops_CGPR _hoops_AAPA _hoops_PAPA _hoops_HHHH _hoops_IHHH _hoops_CHHH _hoops_HSPH _hoops_PGHH. _hoops_SHHH
		// _hoops_SR _hoops_GIHH _hoops_PCCP _hoops_RIHH _hoops_ARI? (_hoops_AIHH 6812 _hoops_IH _hoops_IRS _hoops_PIHH _hoops_AGIR)
		//
		// _hoops_HIHH _hoops_SAHR _hoops_IIHH _hoops_RH _hoops_CHHH _hoops_CIHH _hoops_ISPH _hoops_SIHH _hoops_GCHH - _hoops_IS _hoops_SARR _hoops_SGS _hoops_PAAA
		// _hoops_SR _hoops_HSPH _hoops_CPS _hoops_GGSR _hoops_HPP _hoops_RCHH _hoops_RH _hoops_ISPH.
		int top = max(_hoops_GPHH.top, _hoops_GPHH.bottom);
		ENSURE_SCISSOR_SET (h3ddata,
			max(_hoops_GPHH.left,0), max(_hoops_GPHH.bottom,0),
			min(_hoops_GPHH.right,width), min(top, h3ddata->yfudge));
	}

	if (h3ddata->_hoops_ACHH != _hoops_IHCR->_hoops_CPA) {
		h3ddata->_hoops_ACHH = _hoops_IHCR->_hoops_CPA;

		float *	matrix = h3ddata->_hoops_PIGA;
		matrix[0] = (float) (2.0 / width);
		matrix[1] = (float) 0;
		matrix[2] = (float) 0;
		matrix[3] = (float) 0;

		matrix[4] = (float) 0;
		matrix[5] = (float) (2.0 / height);
		matrix[6] = (float) 0;
		matrix[7] = (float) 0;

		matrix[8] = (float) 0;
		matrix[9] = (float) 0;
		matrix[10] = (float) (1.0 / _hoops_IHCR->_hoops_PCHH);
		matrix[11] = (float) 0;

		matrix[12] = (float) - 1 + _hoops_SPHH/width;
		matrix[13] = (float) - 1 + _hoops_GHHH/height;
		matrix[14] = (float)  0;
		matrix[15] = (float) 1;

		if (!BIT(_hoops_IHCR->flags, _hoops_PASP)) {
			matrix[10] = (float) 1e-10;
			matrix[14] = (float) 0;
		}

		// _hoops_RAP _hoops_HSPH _hoops_PGHH
		if (_hoops_IHCR->_hoops_HCHH == null)
			_hoops_ICHH (h3ddata, false);
		else {
			H3DShader *_hoops_CCHH = (H3DShader *) h3ddata->_hoops_CSC->_hoops_AGSA;

			_hoops_ICHH (h3ddata, true);

			int _hoops_SCHH = width;
			int _hoops_GSHH = height;
			if (_hoops_SCHH < 1)
				_hoops_SCHH = 1;
			if (_hoops_GSHH < 1)
				_hoops_GSHH = 1;

			if (h3ddata->_hoops_RSHH != _hoops_IHCR->_hoops_HCHH->_hoops_CPA) {
				H3D_TRACE(h3ddata, "clip region");

				_hoops_ASHH const *region = _hoops_IHCR->_hoops_HCHH->_hoops_PSHH;
				Driver_Color			_hoops_HSHH;
				struct					concave_tri pt;
				bool					_hoops_ISHH;
				bool					_hoops_CSHH;
				H3DShader *_hoops_RSR;

				_hoops_PPHH(h3ddata, 0, 0, _hoops_SCHH, _hoops_GSHH);

				int flags = H3DID_VERTEX_COLORS | H3DID_DC;
				_hoops_SSHH (h3ddata, nr, T_FACES, null, flags, &_hoops_RSR);
				_hoops_RSR->_hoops_RIGA(nr);

				H3DCMPFUNC const _hoops_GGIH = h3ddata->_hoops_CSC->_hoops_RGIH;
				unsigned int const _hoops_AGIH = h3ddata->_hoops_CSC->_hoops_PGIH;
				unsigned int const _hoops_HGIH = h3ddata->_hoops_CSC->_hoops_IGIH;
				H3DSTENCILOP const _hoops_CGIH = h3ddata->_hoops_CSC->_hoops_SGIH;
				H3DSTENCILOP const _hoops_GRIH = h3ddata->_hoops_CSC->_hoops_RRIH;
				H3DSTENCILOP const _hoops_ARIH = h3ddata->_hoops_CSC->_hoops_PRIH;
				unsigned int const _hoops_HRIH = h3ddata->_hoops_CSC->_hoops_IRIH;

				_hoops_CRIH(h3ddata, H3DCMP_ALWAYS, 0, _hoops_SRIH, _hoops_SRIH);
				_hoops_GAIH(h3ddata, H3DSTENCILOP_KEEP, H3DSTENCILOP_KEEP, H3DSTENCILOP_REPLACE);

				_hoops_ISHH = h3ddata->_hoops_CSC->_hoops_RAIH;
				_hoops_RPAP (h3ddata, false);
				_hoops_CSHH = h3ddata->_hoops_CSC->_hoops_AAIH;
				ENSURE_DEPTH_MASK (h3ddata, false);

				if (h3ddata->_hoops_RHH._hoops_PPSP) {
					H3DVertexFormat _hoops_PPCP(H3DVF_PT);
					H3DVertexBuffer &_hoops_PAIH = h3ddata->_hoops_CP;
					H3DVertexBufferCache *_hoops_HACP = h3ddata->_hoops_GSCR->_hoops_HAIH();

					_hoops_HACP->CreateVertexBuffer(h3ddata, 4, _hoops_PPCP);
					_hoops_HACP->Lock(4, &_hoops_PAIH);

					float left = nr->_hoops_SAIR->extent.left;
					float bottom = nr->_hoops_SAIR->extent.bottom;
					float right = nr->_hoops_SAIR->extent.right;
					float top = nr->_hoops_SAIR->extent.top;

					_hoops_PAIH._hoops_AHCP(left, bottom, 0);
					_hoops_PAIH._hoops_CPPH();
					_hoops_PAIH._hoops_AHCP(left, top+1, 0);
					_hoops_PAIH._hoops_CPPH();
					_hoops_PAIH._hoops_AHCP(right+1, bottom, 0);
					_hoops_PAIH._hoops_CPPH();
					_hoops_PAIH._hoops_AHCP(right+1, top+1, 0);
					_hoops_PAIH._hoops_CPPH();
					_hoops_HACP->Unlock();

					_hoops_CRIH(h3ddata, H3DCMP_ALWAYS, _hoops_SRIH, _hoops_SRIH, _hoops_SRIH);
					_hoops_GAIH(h3ddata, H3DSTENCILOP_KEEP, H3DSTENCILOP_KEEP, H3DSTENCILOP_REPLACE);

					_hoops_HACP->_hoops_CHSA(h3ddata, H3DPT_TRIANGLESTRIP, 2);

					_hoops_CRIH(h3ddata, H3DCMP_ALWAYS, 0, _hoops_SRIH, _hoops_SRIH);
					_hoops_GAIH(h3ddata, H3DSTENCILOP_KEEP, H3DSTENCILOP_KEEP, H3DSTENCILOP_REPLACE);

					delete _hoops_HACP;
				}
				else
					h3ddata->_hoops_GSCR->Clear(H3DCLEAR_STENCIL, 0, 1.0f, _hoops_SRIH);

				// _hoops_HAIR _hoops_HRGR _hoops_IAIH _hoops_IH _hoops_RGR _hoops_CAIH
				_hoops_HSHH._hoops_HRIR.a = 255;
				_hoops_HSHH._hoops_HRIR.r = 255;
				_hoops_HSHH._hoops_HRIR.g = 255;
				_hoops_HSHH._hoops_HRIR.b = 255;

				_hoops_RHSA (h3ddata, H3DCULL_NONE);

				SET_MEMORY(&pt, sizeof(concave_tri), 0);
				pt.h3ddata = h3ddata;
				pt.color = _hoops_HSHH;
				pt._hoops_PSPH = _hoops_AAPH;
				pt._hoops_RPPH = true;
				pt._hoops_PPPH = 128;

				H3DVertexFormat _hoops_PPCP(H3DVF_PT_CLR);
				pt._hoops_HPPH = NEW(H3DVertexBuffer)();
				pt._hoops_HPPH->_hoops_IRA(null, null, null, &_hoops_PPCP, pt._hoops_PPPH * 3);

				bool					_hoops_SAIH	= false;
				H3DVertexBuffer			&_hoops_PAIH = h3ddata->_hoops_CP;
				H3DVertexBufferCache	*_hoops_GPIH;
				_hoops_RPIH(h3ddata, _hoops_PPCP, _hoops_GPIH);
				if (_hoops_GPIH->_hoops_APIH != _hoops_GPIH->_hoops_PPIH) {
					/* _hoops_HPIH _hoops_API _hoops_HRGR _hoops_IPIH _hoops_GRP _hoops_RGR _hoops_GPHA _hoops_SRHR, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS
					* _hoops_CCPP _hoops_IRS _hoops_AH _hoops_CPIH _hoops_IS _hoops_CRHR _hoops_SPIH
					*/
					_hoops_GPIH = h3ddata->_hoops_GSCR->_hoops_HAIH();
					_hoops_GPIH->CreateVertexBuffer(h3ddata, _hoops_GHIH,											\
						H3DVertexFormat(H3DVF_PT_CLR));
					_hoops_SAIH = true;
				}


				while (region) {
					pt.points.dc = region->points;
					pt._hoops_HPPH->reset();
					pt._hoops_APPH = 0;

					// _hoops_HRHH _hoops_RH _hoops_HSSP _hoops_PPR _hoops_PGSA
					if (BIT (region->flags, _hoops_RHIH))
						_hoops_CGHH (nr, region->count, &pt);
					else
						_hoops_GGHH (nr, region->count, &pt);

					_hoops_GPIH->Lock(pt._hoops_APPH * 3, &_hoops_PAIH);
					pt._hoops_HPPH->reset();
					pt._hoops_HPPH->_hoops_AHIH(&_hoops_PAIH, pt._hoops_APPH * 3);
					_hoops_GPIH->Unlock();
					_hoops_GPIH->_hoops_CHSA(h3ddata, H3DPT_TRIANGLELIST, pt._hoops_APPH);

					h3ddata->_hoops_RSHH = _hoops_IHCR->_hoops_HCHH->_hoops_CPA;
					region = region->next;
				}
				if (_hoops_SAIH)
					delete _hoops_GPIH;
				_hoops_HP(pt._hoops_HPPH);

				// _hoops_PHIH _hoops_RH _hoops_AAIP
				if (h3ddata->_hoops_RHH._hoops_PPSP) {
					_hoops_CRIH(h3ddata, _hoops_GGIH, _hoops_HGIH, _hoops_AGIH, _hoops_HRIH);
					_hoops_GAIH(h3ddata, _hoops_GRIH, _hoops_ARIH, _hoops_CGIH);
				}
				else {
					_hoops_CRIH(h3ddata, H3DCMP_EQUAL, _hoops_SRIH, _hoops_SRIH, _hoops_SRIH);
					_hoops_GAIH(h3ddata, H3DSTENCILOP_KEEP, H3DSTENCILOP_KEEP, H3DSTENCILOP_KEEP);
				}

				_hoops_RPAP (h3ddata, _hoops_ISHH);
				ENSURE_DEPTH_MASK (h3ddata, _hoops_CSHH);
			}
			h3ddata->_hoops_CSC->_hoops_AGSA = _hoops_CCHH;
			_hoops_CCHH->_hoops_HHIH();
		}

		float _hoops_IHIH = 0.0001f * _hoops_IHCR->_hoops_CHCR;
		h3ddata->_hoops_IIGA = _hoops_IHCR->_hoops_CHIH * _hoops_IHIH;
		h3ddata->_hoops_SHIH = _hoops_IHCR->_hoops_SHIH * _hoops_IHIH;
		h3ddata->_hoops_PIGA[14] += h3ddata->_hoops_SHIH;

		_hoops_RRIR(h3ddata, nr, false);
	}
}


void _hoops_GIIH (Net_Rendition const &  nr) {
	H3DData *					h3ddata = H3DD(nr->_hoops_SRA);
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	Int_Rectangle const &		_hoops_GPHH = _hoops_IHCR->_hoops_AGAA;
	bool						_hoops_RIIH = false;
	float						_hoops_AIIH[4][4];
	float						_hoops_PIIH, _hoops_HIIH;
	Int_Rectangle				extent;
	long 						_hoops_IIIH = _hoops_SGRA->_hoops_CIIH.right - _hoops_SGRA->_hoops_CIIH.left;
	long 						_hoops_SIIH = _hoops_SGRA->_hoops_CIIH.top - _hoops_SGRA->_hoops_CIIH.bottom;

	if (h3ddata->_hoops_PI.mode) {
		int const size = h3ddata->_hoops_PI._hoops_HAP;
		if (h3ddata->_hoops_PI._hoops_SAR) {
			// _hoops_GCIH _hoops_CCA _hoops_SCIA _hoops_RAAP _hoops_RCIH.
			extent.left = 0;
			extent.bottom = 0;
			extent.top = size / 2 - 1;
			extent.right = size / 2 - 1;

			// _hoops_ACIH _hoops_IS _hoops_GGSP _hoops_RCIH. _hoops_GARP _hoops_SR _hoops_GCGH _hoops_AIAA _hoops_SCAR _hoops_GAR _hoops_IRS _hoops_GHPP.
			ASSERT(h3ddata->_hoops_PI._hoops_PCIH < _hoops_GSAR::_hoops_RSAR);
			if (h3ddata->_hoops_PI._hoops_PCIH & 1) {
				extent.left += size / 2;
				extent.right += size / 2;
			}
			if (h3ddata->_hoops_PI._hoops_PCIH & 2) {
				extent.bottom += size / 2;
				extent.top += size / 2;
			}
		}
		else {
			extent.left = 0;
			extent.bottom = 0;
			extent.top = size - 1;
			extent.right = size - 1;
		}
	}
	else if (h3ddata->_hoops_CHSP.mode) {
		extent.left = 0;
		extent.bottom = 0;
		extent.top = h3ddata->_hoops_CHSP._hoops_HAP - 1;
		extent.right = h3ddata->_hoops_CHSP._hoops_HAP - 1;
	}
	else {
		extent.left = _hoops_SGRA->_hoops_CIIH.left +
			(int)(0.5f * (_hoops_IHCR->_hoops_HCIH.left + 1.0f) * _hoops_IIIH);
		extent.right = _hoops_SGRA->_hoops_CIIH.left +
			(int)(0.5f * (_hoops_IHCR->_hoops_HCIH.right + 1.0f) * _hoops_IIIH);
		extent.bottom = _hoops_SGRA->_hoops_CIIH.bottom +
			(int)(0.5f * (_hoops_IHCR->_hoops_HCIH.bottom + 1.0f) * _hoops_SIIH);
		extent.top = _hoops_SGRA->_hoops_CIIH.bottom +
			(int)(0.5f * (_hoops_IHCR->_hoops_HCIH.top + 1.0f) * _hoops_SIIH);

		_hoops_IIIH = extent.right - extent.left;
		_hoops_SIIH = extent.top - extent.bottom;

		// _hoops_ISPR _hoops_RPP _hoops_SR _hoops_RRP _hoops_ICIH _hoops_CCIH
		if (extent.right > _hoops_SGRA->_hoops_SCIH.right ||
			extent.left < _hoops_SGRA->_hoops_SCIH.left ||
			extent.top > _hoops_SGRA->_hoops_SCIH.top ||
			extent.bottom < _hoops_SGRA->_hoops_SCIH.bottom)
			_hoops_RIIH = true;
	}

	// _hoops_AHH: _hoops_GSIH _hoops_HCH _hoops_AGI _hoops_SARA _hoops_GAR _hoops_RSIH _hoops_GAR _hoops_SSRR.
	if (h3ddata->_hoops_II.mode && !h3ddata->_hoops_II._hoops_SPH) {
		if (BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_CRI) &&
			 BIT (nr->transform_rendition->heuristics, _hoops_IRI))
			h3ddata->_hoops_II._hoops_SPH = nr->transform_rendition->_hoops_SPH;
	}

	if (h3ddata->_hoops_ASIH != _hoops_IHCR->_hoops_CPA) {
		h3ddata->_hoops_ASIH = _hoops_IHCR->_hoops_CPA;

		// _hoops_RAP _hoops_HSPH _hoops_PGHH
		if (!h3ddata->_hoops_RHH.mode && _hoops_IHCR->_hoops_HCHH == null)
			_hoops_ICHH (h3ddata, false);
		else if (_hoops_IHCR->_hoops_HCHH) {
			_hoops_ICHH (h3ddata, true);
			_hoops_SAHH (nr);
		}

		/* _hoops_PSIH _hoops_RH _hoops_HSIH */
		_hoops_PIIH = _hoops_HIIH = 1.0f;
		float _hoops_ISIH;

		if (h3ddata->_hoops_PI.mode || h3ddata->_hoops_CHSP.mode)
			_hoops_ISIH = 1.0f;
		else
			_hoops_ISIH = _hoops_SGRA->_hoops_CSIH * (_hoops_IHCR->_hoops_HCIH.top - _hoops_IHCR->_hoops_HCIH.bottom) /
									 (_hoops_IHCR->_hoops_HCIH.right - _hoops_IHCR->_hoops_HCIH.left);

		if (_hoops_IHCR->_hoops_SPH->projection != _hoops_SSIH) {
			if (_hoops_ISIH <= _hoops_IHCR->_hoops_SPH->_hoops_CSIH)
				_hoops_PIIH = _hoops_IHCR->_hoops_SPH->_hoops_CSIH / _hoops_ISIH;
			else
				_hoops_HIIH = _hoops_ISIH / _hoops_IHCR->_hoops_SPH->_hoops_CSIH;
		}

		float _hoops_CHCR = _hoops_IHCR->_hoops_CHCR;
		if (_hoops_CHCR < 1.0e-3f)
			_hoops_CHCR = 1.0e-3f;


		if (h3ddata->_hoops_CHSP.mode) {
			_hoops_PIIH = 1.0;
			_hoops_HIIH = h3ddata->_hoops_ACCR;
			_hoops_CHCR = 1.0f;
		}

		// _hoops_AHH: _hoops_RAH _hoops_RGR _hoops_RAS _hoops_RH _hoops_RCAR _hoops_GGCH - _hoops_IHGP _hoops_RGCH _hoops_PAH _hoops_SGH _hoops_GIPR _hoops_AGCH.
		if (BIT (_hoops_IHCR->flags, _hoops_PGCH))
			_hoops_PIIH = -_hoops_PIIH;

		/* ===================== _hoops_HGSR _hoops_HGCH _hoops_RSGA ====================== */
		if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH) {

			float _hoops_SHCR = _hoops_CHCR * _hoops_IHCR->_hoops_SPH->_hoops_SRIR;
			float _hoops_GICR;

			if (h3ddata->_hoops_PI.mode) {
				// _hoops_AIAP _hoops_RPHR-_hoops_IGCH _hoops_RAR
				_hoops_PIIH = _hoops_HIIH = 1.0f;

				// _hoops_HGI _hoops_HRGR _hoops_PCCP _hoops_CGCH _hoops_ASCR
				_hoops_GICR = _hoops_IHCR->_hoops_SPH->_hoops_SRIR;
			} else {
				// _hoops_SGCH '_hoops_SGIP _hoops_CRGR _hoops_RH _hoops_GIRA'
				_hoops_GICR = _hoops_IHCR->_hoops_SPH->_hoops_SRIR + (_hoops_IHCR->_hoops_SPH->_hoops_SRIR)*1000.0f;
			}

			H3DMatrixPerspectiveLH(
				&_hoops_AIIH[0][0],
				(_hoops_IHCR->_hoops_SPH->_hoops_ISPA*_hoops_PIIH)*_hoops_CHCR,
				(_hoops_IHCR->_hoops_SPH->_hoops_SSPA*_hoops_HIIH)*_hoops_CHCR,
				_hoops_SHCR, _hoops_GICR,
				h3ddata->_hoops_ACCR
			);

			h3ddata->_hoops_SIRA = _hoops_GICR;
			h3ddata->_hoops_GCRA = _hoops_SHCR;

			// _hoops_SIGP: _hoops_GRCH
			//_hoops_RRAP->_hoops_IHAH->_hoops_RRCH = 0.0f;
		}
		else {
			/* _hoops_ARCH _hoops_PPR _hoops_CIHP */
			float _hoops_SHCR = -_hoops_IHCR->_hoops_SPH->_hoops_SRIR;
			float _hoops_GICR = _hoops_IHCR->_hoops_SPH->_hoops_SRIR;

			/* _hoops_HSRR _hoops_RCAR _hoops_ACAR, _hoops_SR _hoops_ACPA _hoops_RH _hoops_CHRA _hoops_PRCH _hoops_RH _hoops_HIRA _hoops_HRCH, _hoops_HIS
			   _hoops_GA'_hoops_RA _hoops_IRCH _hoops_SCH _hoops_PAR _hoops_SR _hoops_GRS _hoops_CRCH _hoops_HCH _hoops_RAAA. */
			if (!h3ddata->_hoops_PI.mode) {
				_hoops_SHCR /= _hoops_IHCR->_hoops_CHCR;
				_hoops_GICR /= _hoops_IHCR->_hoops_CHCR;
			}
			else {
				/* _hoops_AIAP _hoops_RPHR-_hoops_IGCH _hoops_RRR _hoops_RHC _hoops_GC _hoops_ARI _hoops_IS _hoops_SRCH _hoops_GACH _hoops_CCA _hoops_SCH _hoops_GGR _hoops_APR _hoops_HGSR. */
				_hoops_PIIH = _hoops_HIIH = 1;
			}

			h3ddata->_hoops_SIRA = _hoops_GICR;
			h3ddata->_hoops_GCRA = _hoops_SHCR;

			H3DMatrixOrthoLH(
				&_hoops_AIIH[0][0],
				_hoops_IHCR->_hoops_SPH->_hoops_ISPA*_hoops_PIIH,
				_hoops_IHCR->_hoops_SPH->_hoops_SSPA*_hoops_HIIH,
				_hoops_SHCR, _hoops_GICR,
				h3ddata->_hoops_ACCR);

//#_hoops_PPIP _hoops_RACH
#ifdef _hoops_AACH
			if (dx9data->_hoops_PI._hoops_SAR) {

				/* _hoops_PACH _hoops_HACH _hoops_PHCR _hoops_PGCR _hoops_IACH _hoops_HIS _hoops_SR _hoops_PAH _hoops_CACH _hoops_SACH-_hoops_GGSR _hoops_CPAP */
				float _hoops_GPCH = 0.5f;
				float _hoops_RPCH = 0.5f;

				/* _hoops_PACH _hoops_GGR _hoops_GPP _hoops_RH _hoops_ARAA */
				D3DXMATRIX _hoops_APCH(
					_hoops_GPCH,						0.0f,				0.0f,	0.0f,
                    0.0f,					_hoops_RPCH,					0.0f,	0.0f,
                    0.0f,					0.0f,				1.0f,	0.0f,
                    0.0f,					0.0f,				0.0f,	1.0f
				);
				D3DXMatrixMultiply(&dx_proj_mat, &dx_proj_mat, &_hoops_APCH);
			}
#endif
		}

		if (_hoops_RIIH) {
			Point _hoops_PPCH = _hoops_HPCH::_hoops_IPCH;
			Point _hoops_CPCH = _hoops_HPCH::_hoops_IPCH;

			_hoops_PPCH.x = ((float) _hoops_IIIH) / (_hoops_SGRA->_hoops_SCIH.right - _hoops_SGRA->_hoops_SCIH.left + 1);
			_hoops_PPCH.y = ((float) _hoops_SIIH) / (_hoops_SGRA->_hoops_SCIH.top - _hoops_SGRA->_hoops_SCIH.bottom + 1);

			/* _hoops_ACGR _hoops_GIRA _hoops_GAPA _hoops_SPCH _hoops_PPR _hoops_GHCH _hoops_HPP _hoops_RH _hoops_GIRA _hoops_HII _hoops_RHCH _hoops_IIGR _hoops_AHCH
			 * _hoops_IS _hoops_ISHA _hoops_IIGR _hoops_AHCH.  _hoops_HGI _hoops_AAAA _hoops_RH _hoops_PHI _hoops_IIGR _hoops_PSPA _hoops_IS _hoops_PHCH.
			 */
			_hoops_CPCH.x = ((extent.right + extent.left) - (_hoops_SGRA->_hoops_SCIH.right + _hoops_SGRA->_hoops_SCIH.left)) / ((float)(_hoops_SGRA->_hoops_SCIH.right - _hoops_SGRA->_hoops_SCIH.left));
			_hoops_CPCH.y = ((extent.top + extent.bottom) - (_hoops_SGRA->_hoops_SCIH.top + _hoops_SGRA->_hoops_SCIH.bottom)) / ((float)(_hoops_SGRA->_hoops_SCIH.top - _hoops_SGRA->_hoops_SCIH.bottom));

			_hoops_AIIH[0][0] *= _hoops_PPCH.x;
			_hoops_AIIH[1][1] *= _hoops_PPCH.y;

			_hoops_AIIH[2][0] = _hoops_AIIH[2][3] * _hoops_CPCH.x;
			_hoops_AIIH[2][1] = _hoops_AIIH[2][3] * _hoops_CPCH.y;

			_hoops_AIIH[3][0] = _hoops_AIIH[3][3] * _hoops_CPCH.x;
			_hoops_AIIH[3][1] = _hoops_AIIH[3][3] * _hoops_CPCH.y;
		}

		if (_hoops_IHCR->_hoops_SPH->_hoops_HHCH != 0.0f || _hoops_IHCR->_hoops_SPH->_hoops_IHCH != 0.0f) {
			float			_hoops_CHCH[4][4];
			float			_hoops_SHCH, _hoops_GICH;

			HI_Ident_44 (&_hoops_CHCH[0][0]);
			if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH)
				_hoops_CHCH[3][2] -= h3ddata->_hoops_ACCR * _hoops_IHCR->_hoops_SPH->_hoops_SRIR;

			_hoops_RICH (_hoops_IHCR->_hoops_SPH->_hoops_HHCH, _hoops_SHCH, _hoops_GICH);
			if (_hoops_GICH != 0.0f) {
				_hoops_CHCH[2][0] += h3ddata->_hoops_ACCR * _hoops_SHCH/_hoops_GICH;
				_hoops_CHCH[3][0] += h3ddata->_hoops_ACCR * _hoops_SHCH/_hoops_GICH * _hoops_CHCH[3][2];
			}

			_hoops_RICH (_hoops_IHCR->_hoops_SPH->_hoops_IHCH, _hoops_SHCH, _hoops_GICH);
			if (_hoops_GICH != 0.0f) {
				_hoops_CHCH[2][1] += h3ddata->_hoops_ACCR * _hoops_SHCH/_hoops_GICH;
				_hoops_CHCH[3][1] += h3ddata->_hoops_ACCR * _hoops_SHCH/_hoops_GICH * _hoops_CHCH[3][2];
			}
			if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH)
				_hoops_CHCH[3][2] += h3ddata->_hoops_ACCR * _hoops_IHCR->_hoops_SPH->_hoops_SRIR;

			HI_Matmul_44_by_44 (&_hoops_CHCH[0][0], &_hoops_AIIH[0][0], h3ddata->_hoops_PARA);
		}
		else
			_hoops_AIGA(&_hoops_AIIH[0][0], 16, float, h3ddata->_hoops_PARA);

		//_hoops_RRAP->_hoops_AICH = _hoops_RCPP;


		/* ===================== _hoops_HGSR _hoops_PICH _hoops_RSGA ====================== */

		HI_Copy_43 (&_hoops_IHCR->_hoops_SPH->_hoops_PRPA.elements[0][0],
					h3ddata->_hoops_SPSR);

		/* _hoops_AA _hoops_RH _hoops_RSSP _hoops_AGRP _hoops_PPR _hoops_RH _hoops_SARA _hoops_HICH (0 _hoops_IS -5) */
		h3ddata->_hoops_SPSR[2] *= h3ddata->_hoops_ACCR;
		h3ddata->_hoops_SPSR[6] *= h3ddata->_hoops_ACCR;
		h3ddata->_hoops_SPSR[10] *= h3ddata->_hoops_ACCR;
		h3ddata->_hoops_SPSR[14] *= h3ddata->_hoops_ACCR;

		if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH)
			h3ddata->_hoops_SPSR[14] += h3ddata->_hoops_ACCR * _hoops_IHCR->_hoops_SPH->_hoops_SRIR;


		h3ddata->_hoops_IICH =
			!ANYBIT (_hoops_IHCR->_hoops_IPH->data._hoops_RAGR,
					 _hoops_CICH);

		if (!h3ddata->_hoops_IICH) {
			HI_Matmul_44_by_44 (&_hoops_IHCR->_hoops_IPH->data.elements[0][0],
				h3ddata->_hoops_SPSR, h3ddata->_hoops_ISGA);

			/*_hoops_RPP (_hoops_CPSP->_hoops_SICH->_hoops_GCCH == _hoops_RCCH (0) &&
			(_hoops_ACCH || _hoops_PCCH)) {
			_hoops_HCCH (_hoops_RRAP->_hoops_GSGA);
			}*/
		}
		else {
			/* _hoops_SGH _hoops_ICCH _hoops_RSGA _hoops_RIIA _hoops_IIGR _hoops_GSGA _hoops_PPR _hoops_SRCH _hoops_CCCH */
			_hoops_AIGA(h3ddata->_hoops_SPSR, 16, float, h3ddata->_hoops_ISGA);
		}

		/* ===================== _hoops_HGSR _hoops_SCCH _hoops_RSGA ====================== */
		HI_Copy_44 (&_hoops_IHCR->_hoops_IPH->data.elements[0][0], h3ddata->_hoops_IACR);

		_hoops_APHH(h3ddata, _hoops_IHCR->_hoops_GSCH[0], _hoops_IHCR->_hoops_GSCH[1]);

		float _hoops_IHIH;
		if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH)
			_hoops_IHIH = 0.0001f * _hoops_IHCR->_hoops_SPH->_hoops_SRIR * _hoops_IHCR->_hoops_CHCR;
		else
			_hoops_IHIH = 0.00004f * _hoops_IHCR->_hoops_CHCR;
		h3ddata->_hoops_HARA = _hoops_IHCR->_hoops_CHIH * _hoops_IHIH;
		h3ddata->_hoops_SHIH = _hoops_IHCR->_hoops_SHIH * _hoops_IHIH;
		h3ddata->_hoops_PARA[14] += h3ddata->_hoops_SHIH;

		if (h3ddata->_hoops_PI.mode) {
			h3ddata->_hoops_HARA = 0;
			h3ddata->_hoops_SHIH = 0;
		}
	}

	if (h3ddata->_hoops_PI.mode || h3ddata->_hoops_CHSP.mode) {
		_hoops_PPHH(h3ddata,
				extent.left, extent.bottom,
				extent.right - extent.left + 1,
				extent.top - extent.bottom + 1);
		_hoops_HPHH(h3ddata, false);
	}
	else {
		if (_hoops_RIIH) {
			int top = _hoops_SGRA->_hoops_SCIH.bottom;
			if (h3ddata->_hoops_RSCH) {
				top = _hoops_AHIA(h3ddata->yfudge, _hoops_SGRA->_hoops_SCIH.top);
				ASSERT(top <= h3ddata->yfudge);

				top = h3ddata->yfudge - top;
			}

			_hoops_PPHH(h3ddata, _hoops_SGRA->_hoops_SCIH.left, _hoops_IAAA(top, 0),
					_hoops_SGRA->_hoops_SCIH.right - _hoops_SGRA->_hoops_SCIH.left + 1,
					_hoops_SGRA->_hoops_SCIH.top - _hoops_SGRA->_hoops_SCIH.bottom + 1);
		}
		else {
			int top = extent.bottom;
			if (h3ddata->_hoops_RSCH) {
				top = _hoops_AHIA(h3ddata->yfudge, extent.top);
				ASSERT(top <= h3ddata->yfudge);

				top = h3ddata->yfudge - top;
			}

			_hoops_PPHH(h3ddata,
					extent.left, top,
					extent.right - extent.left + 1,
					extent.top - extent.bottom + 1);
		}

		if (_hoops_GPHH == dc->_hoops_RCGA) {
			_hoops_HPHH(h3ddata, false);
		}
		else {
			_hoops_HPHH(h3ddata, true);

			// _hoops_AHH: _hoops_RHHH _hoops_AHHH _hoops_HII _hoops_PHHH _hoops_CGPR _hoops_AAPA _hoops_PAPA _hoops_HHHH _hoops_IHHH _hoops_CHHH _hoops_HSPH _hoops_PGHH. _hoops_SHHH
			// _hoops_SR _hoops_GIHH _hoops_PCCP _hoops_RIHH _hoops_ARI? (_hoops_AIHH 6812 _hoops_IH _hoops_IRS _hoops_PIHH _hoops_AGIR)
			//
			// _hoops_HIHH _hoops_SAHR _hoops_IIHH _hoops_RH _hoops_CHHH _hoops_CIHH _hoops_ISPH _hoops_SIHH _hoops_GCHH - _hoops_IS _hoops_SARR _hoops_SGS _hoops_PAAA
			// _hoops_SR _hoops_HSPH _hoops_CPS _hoops_GGSR _hoops_HPP _hoops_RCHH _hoops_RH _hoops_ISPH.
			int top = _hoops_IAAA(_hoops_GPHH.top, _hoops_GPHH.bottom);
			ENSURE_SCISSOR_SET (h3ddata, _hoops_GPHH.left, _hoops_GPHH.bottom, _hoops_GPHH.right, _hoops_AHIA(top, h3ddata->yfudge));
		}
	}
}



/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_ASCH _hoops_PSCH
*****************************************************************************
*****************************************************************************/

/*
* _hoops_PGAA - _hoops_SGH _hoops_HSCH _hoops_HIRA _hoops_IS _hoops_CAHP _hoops_RHAA _hoops_AGI.
*/
void _hoops_ISCH(H3DData *h3ddata, H3DTexture *_hoops_GGIP, H3DRenderTarget *_hoops_CSCH)
{
	// _hoops_HSRR _hoops_SSCH
	H3DPost *post = (H3DPost *)h3ddata->post;
	int const _hoops_GGSH = h3ddata->_hoops_CSC->_hoops_GRPP;
	_hoops_IPGP(h3ddata,false);

	if (post->_hoops_GGPP()) {

		if (h3ddata->dc->options._hoops_RGSH) {

			// _hoops_AGSH _hoops_SR _hoops_GHGA _hoops_IRS _hoops_PGSH?
			bool const _hoops_HGSH = h3ddata->dc->options._hoops_IGSH == _hoops_CGSH;

			// _hoops_SGSH _hoops_IGAA
			int w = _hoops_GGIP->_hoops_IRRP / 4;
			int h = _hoops_GGIP->_hoops_CRRP / 4;

			// _hoops_GRSH _hoops_AHPH _hoops_RRSH _hoops_HARH?
			int const _hoops_ARSH = 8;
			int const _hoops_PRSH = _hoops_AHIA(_hoops_ARSH, h3ddata->dc->options._hoops_HRSH);
			int _hoops_IRSH = 0;

			// _hoops_SSHP _hoops_CRSH _hoops_AI
			H3DTexture *_hoops_ICRH[_hoops_ARSH];
			for (; _hoops_IRSH < _hoops_PRSH; ++_hoops_IRSH) {
				_hoops_ICRH[_hoops_IRSH] = post->_hoops_IAAP(w, h, _hoops_GGIP->_hoops_GSPP);

				// _hoops_CPR _hoops_SPR _hoops_ISHP
				w /= 2;
				h /= 2;

				// _hoops_CGP _hoops_RGR _hoops_SPR _hoops_SRSH, _hoops_PAR _hoops_RH _hoops_SPS _hoops_SPR _hoops_GRS _hoops_SHH _hoops_HAH _hoops_RISA, _hoops_RRS
				if (!_hoops_ICRH[_hoops_IRSH] || (w==0) || (h==0))
					break;
			}

			// _hoops_CGP _hoops_SR _hoops_HS _hoops_PA _hoops_SR _hoops_PAH _hoops_AA...
			if (_hoops_IRSH) {
				//
				// _hoops_PHAA _hoops_SICR _hoops_HIRA _hoops_CRGR _hoops_RRSH _hoops_HCGP
				//

				// _hoops_PCH _hoops_RAIA _hoops_CSRR 0
				_hoops_SCCR(h3ddata, 0, _hoops_GGIP);
				_hoops_GRPA(h3ddata, 0, H3DTEXF_LINEAR, H3DTEXF_NONE, H3DTADDRESS_CLAMP);

				// _hoops_RAH _hoops_RH _hoops_GASH
				post->_hoops_HPRP(_hoops_ICRH[0], H3DPost::_hoops_RASH, 0.0f, null, _hoops_GGIP);

				// _hoops_PPPA _hoops_ISHP _hoops_AASH _hoops_HCRP _hoops_PPR _hoops_PASH
				for (int i = 0; i < _hoops_IRSH; ++i) {
					// _hoops_CPPP _hoops_RH _hoops_SRS _hoops_PAPA, _hoops_HAIP _hoops_RH _hoops_ACSP
					if (i)
						post->_hoops_HASH(_hoops_ICRH[i], 1);

					// _hoops_PGIP _hoops_IS _hoops_SPS _hoops_HH
					if (i + 1 != _hoops_IRSH)
						post->Copy(_hoops_ICRH[i+1], _hoops_ICRH[i], null, H3DTEXF_LINEAR);
				}

				if (_hoops_HGSH) {
					// _hoops_SIPR _hoops_IASH _hoops_IIGR _hoops_CASH _hoops_SASH
					post->_hoops_GPSH(_hoops_ICRH[0]);

					// _hoops_RPSH _hoops_HAIP. _hoops_PCH _hoops_AA _hoops_HRSP _hoops_HHHH - _hoops_APSH _hoops_AAH.
					post->_hoops_PPSH(_hoops_ICRH[0], 3);
				}
				else
					// _hoops_RAH _hoops_RH _hoops_SPRP _hoops_HAIP _hoops_SR _hoops_HPSH, _hoops_IPSH _hoops_IRS _hoops_IGRH _hoops_RRI _hoops_IS _hoops_HPPR _hoops_PPR _hoops_PSSP _hoops_RH _hoops_CPSH _hoops_IIGR _hoops_SPSH _hoops_GGR _hoops_RH _hoops_GHSH.
					post->_hoops_HASH(_hoops_ICRH[0], 2);

				ENSURE_TRANSPARENCY(h3ddata, true);
				_hoops_PPRP(h3ddata, H3DBLEND_ONE, H3DBLEND_ONE);
				// _hoops_CGP _hoops_SR _hoops_HS _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_PAPA, _hoops_GGCR _hoops_RH _hoops_ACSP _hoops_GGR
				if (_hoops_IRSH > 1) {
					float const s = 1.0f / (_hoops_IRSH-1);
					RGBA const _hoops_RHSH(s, s, s, s);

					// _hoops_AGGA _hoops_GGCR _hoops_RH _hoops_HARH _hoops_GIRP
					post->_hoops_AHSH(_hoops_ICRH[0], _hoops_ICRH + 1, _hoops_IRSH-1, &_hoops_RHSH, H3DTEXF_LINEAR);
				}

				// _hoops_PHSH _hoops_SPGP _hoops_HCSP _hoops_GGR (1, _hoops_CSHP] _hoops_IS (1, 2] _hoops_CR _hoops_APPR _hoops_HSH _hoops_HHSH _hoops_SHR _hoops_IHSH _hoops_CHSH.
				float _hoops_SHGP = h3ddata->dc->options._hoops_SHSH / 4;
				float const MAX = 10.0f;
				if (_hoops_SHGP > 1)
					_hoops_SHGP = 1 + (_hoops_SHGP - 1) / (MAX - 1);

				// _hoops_CAAA _hoops_SPGP _hoops_PIRA _hoops_IS _hoops_GISH
				RGBA const _hoops_RHSH(_hoops_SHGP, _hoops_SHGP, _hoops_SHGP, 1);

				// _hoops_CAAA _hoops_RISH _hoops_GGR _hoops_RH _hoops_HIRA _hoops_HH _hoops_IS _hoops_IRS _hoops_AISH _hoops_AIIR _hoops_PISH.
				if (H3DConstantTable *_hoops_AIPA = post->_hoops_PIGP(H3DPost::_hoops_HIGP, H3DPost::_hoops_HISH)) {
					UNREFERENCED(_hoops_AIPA);

					// _hoops_IARP _hoops_HIRA _hoops_HH
					_hoops_SCCR(h3ddata, 0, _hoops_GGIP);
					_hoops_GRPA(h3ddata, 0, H3DTEXF_POINT, H3DTEXF_NONE, H3DTADDRESS_CLAMP);

					// _hoops_IISH _hoops_SCH
					ENSURE_TRANSPARENCY(h3ddata, false);

					// _hoops_CICR _hoops_GGI _hoops_AIIR _hoops_RCAP
					_hoops_GPRP(h3ddata, H3DMASK_A);
					post->_hoops_HPRP(_hoops_CSCH, H3DPost::_hoops_HISH, 0.0f, null, _hoops_GGIP);
				}

				// _hoops_RGPA _hoops_RRSH _hoops_IS _hoops_AISH, _hoops_CISH _hoops_HPP _hoops_SISH _hoops_AIIR
				ENSURE_TRANSPARENCY(h3ddata, true);
				_hoops_PPRP(h3ddata, H3DBLEND_DESTALPHA, H3DBLEND_ONE);
				_hoops_GPRP(h3ddata, H3DMASK_RGB);
				post->Copy(_hoops_CSCH, _hoops_ICRH[0], &_hoops_RHSH, H3DTEXF_LINEAR);

				// _hoops_CHSR _hoops_GCSH _hoops_RCSH _hoops_RH _hoops_CRSH _hoops_AI
				for (int i = 0; i < _hoops_IRSH; ++i)
					post->_hoops_HAAP(&_hoops_ICRH[i]);

				ENSURE_TRANSPARENCY(h3ddata, false);
				_hoops_PPRP(h3ddata, H3DBLEND_SRCALPHA, H3DBLEND_INVSRCALPHA);

				_hoops_GPRP(h3ddata, H3DMASK_A);
				post->_hoops_HPRP(_hoops_CSCH, H3DPost::_hoops_ACSH, 0.0f, null, _hoops_GGIP);
			}
		}

		post->_hoops_PRHP();
	}

	// _hoops_IPRP
	_hoops_GPRP(h3ddata, _hoops_GGSH);
}

/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_PCSH/_hoops_HCSH _hoops_CPIP _hoops_ICSH
*****************************************************************************
*****************************************************************************/
local inline int
_hoops_CCSH (Tristrip const *ts)
{
	int size;

	size = 12 * (ts->point_count < ts->total ? ts->point_count : ts->total);	// 3 _hoops_PHRP _hoops_RIR _hoops_PPSR
	size += 4 * ts->total;	//_hoops_SPR _hoops_SCSH _hoops_RIR _hoops_CIHA
	if (ts->_hoops_ICHA || ts->_hoops_PRHH)
		size += 12 * ts->total;
	if (ts->_hoops_PCHA)
		size += ts->total;
	if (ts->_hoops_GSSH && ts->_hoops_GSSH->_hoops_CCHA)
		size += ts->total * ts->_hoops_GSSH->_hoops_GSHA * sizeof(_hoops_RSSH);
	return size;
}

local inline int
_hoops_ASSH (Polyedge const *pe, bool _hoops_IHP)
{
	int size;

	size = 12 * (pe->point_count < pe->total ? pe->point_count : pe->total);
	if (pe->_hoops_ICHA)
		size += 12 * pe->total;
	if (pe->_hoops_PCHA)
		size += 4 * pe->total;
	if (pe->_hoops_CCHA)
		size += pe->total * pe->_hoops_GSHA * sizeof(_hoops_RSSH);
	if (_hoops_IHP)
		size *= 4;
	return size;
}

local inline int
_hoops_PSSH (Polymarker const *pm)
{
	int size;

	size = 12 * pm->length;
	if (pm->_hoops_ICHA)
		size += 12 * pm->length;
	if (pm->_hoops_PCHA || pm->_hoops_RGIA)
		size += 4 * pm->length;

	return size;
}


local H3D_Display_List_Bin alter *
_hoops_HSSH (
		H3DData alter *h3ddata,
		_hoops_ISSH alter *_hoops_CSSH,
		H3D_Display_List_Bin alter *_hoops_SSSH,
		_hoops_ACHR type,
		_hoops_IRHA *_hoops_GGGI)
{
	H3D_Display_List_Bin alter *_hoops_RRHA;
	_hoops_IRHA *_hoops_RGGI;
	_hoops_AGGI *_hoops_PGGI = null;

	_hoops_CSSH->LookupItem (_hoops_SSSH->_hoops_HGGI, &_hoops_PGGI);
	if (!_hoops_PGGI)
		return null;

	_hoops_PGGI->ResetCursor ();
	while ((_hoops_RRHA = _hoops_PGGI->PeekCursor()) != null) {
		_hoops_PGGI->AdvanceCursor();

		if (_hoops_RRHA->id != _hoops_SSSH->id)
			continue;

		if ((unsigned int)_hoops_RRHA->_hoops_IGGI.point_count + _hoops_SSSH->_hoops_IGGI.point_count >
			_hoops_AHIA ((unsigned int)H3D_Display_List_MAX_SIZE, h3ddata->_hoops_ACGH._hoops_CGGI))
			break;

		//_hoops_RH _hoops_HPHR _hoops_PHI _hoops_IIGR _hoops_PICA _hoops_HRGR _hoops_GPRR _hoops_AAR, _hoops_HIS _hoops_RGR _hoops_HRGR _hoops_SAHR _hoops_IRS _hoops_SGGI _hoops_AAPA _hoops_ASCR
		if ((unsigned int)_hoops_RRHA->_hoops_IGGI.total + _hoops_SSSH->_hoops_IGGI.total >
			_hoops_AHIA ((unsigned int)H3D_Display_List_MAX_SIZE, h3ddata->_hoops_ACGH._hoops_GRGI))
			break;

		_hoops_RGGI = _hoops_RRHA->_hoops_CRHA->PeekFirst();
		switch (type) {
			case T_FACES: {
				// _hoops_GRHP _hoops_HSP _hoops_RPR _hoops_RRGI 64_hoops_ARGI _hoops_PRGI _hoops_GGR _hoops_HRGI _hoops_AGIR _hoops_IRGI _hoops_CAS _hoops_SR _hoops_HS _hoops_CRGI _hoops_SRHR _hoops_IAHA
				// _hoops_CACH _hoops_SRGI()
				if (_hoops_RRHA->_hoops_IGGI.total + _hoops_SSSH->_hoops_IGGI.total + 3 * (_hoops_RRHA->_hoops_IGGI._hoops_PHHA + _hoops_SSSH->_hoops_IGGI._hoops_PHHA) > 0xffff)
					continue;

				Tristrip *_hoops_GAGI, *_hoops_RAGI;
				int _hoops_AAGI;
				_hoops_RAGI = (Tristrip *) _hoops_GGGI->geo;
				if ((_hoops_GGGI->color != null) != (_hoops_RGGI->color != null))
					continue;
				_hoops_GAGI = (Tristrip *) _hoops_RGGI->geo;
				if ((_hoops_GAGI->_hoops_PAGI != null) !=
					(_hoops_RAGI->_hoops_PAGI != null))
					continue;
				if (_hoops_GAGI->face_attributes.flags !=
					_hoops_RAGI->face_attributes.flags)
					continue;
				One_Face_Attributes temp = _hoops_RAGI->face_attributes;
				temp.region = _hoops_GAGI->face_attributes.region;
				_hoops_AAGI = (_hoops_HAGI|LFA_EXPLICIT_COLOR_BY_FINDEX|_hoops_IAGI);
				if (BIT (_hoops_RAGI->_hoops_SRHA, _hoops_CAGI))
					_hoops_AAGI &= ~LFA_EXPLICIT_COLOR_BY_FINDEX;
				if (!_hoops_SAGI (_hoops_GAGI->face_attributes, temp, _hoops_AAGI))
					continue;
			} break;
			case _hoops_GPA:
			case T_EDGES: {
				Polyedge *_hoops_GAGI, *_hoops_RAGI;
				const int _hoops_AAGI = (_hoops_GPGI|_hoops_RPGI|_hoops_APGI);

				_hoops_RAGI = (Polyedge *) _hoops_GGGI->geo;
				if ((_hoops_GGGI->color != null) != (_hoops_RGGI->color != null))
					continue;
				_hoops_GAGI = (Polyedge *) _hoops_RGGI->geo;
				if (_hoops_GAGI->_hoops_PPGI.flags !=
					_hoops_RAGI->_hoops_PPGI.flags)
					continue;
				if (!_hoops_HPGI (
					_hoops_GAGI->_hoops_PPGI,
					_hoops_RAGI->_hoops_PPGI,
					_hoops_AAGI))
					continue;
			} break;
			case T_LINES: {
				if (_hoops_GGGI->color == null) {
					if (_hoops_RGGI->color != null)
						continue;
				}
				else {
					if (_hoops_RGGI->color == null)
						continue;
					if (BIT (_hoops_GGGI->color->_hoops_GHA, Color_LINE) !=
						BIT (_hoops_RGGI->color->_hoops_GHA, Color_LINE))
						continue;
				}

			} break;
		}
		return _hoops_RRHA;
	}
	return null;
}

INLINE void _hoops_IPGI (H3D_Display_List_List*& list);

local bool _hoops_CPGI (
		_hoops_GRGH const &_hoops_RRGH)
{
	bool _hoops_SPGI = BIT (_hoops_RRGH->locks.color, Color_FRONT) &&
					 BIT (_hoops_RRGH->locks._hoops_HAA[_hoops_IAA], M_DIFFUSE);
	if (_hoops_SPGI)
		return false;

	_hoops_GHGI _hoops_RHGI = _hoops_RRGH->_hoops_CSA & ~_hoops_AHGI;
	return ANYBIT (_hoops_RHGI, _hoops_PHGI);
}


local void _hoops_HHGI (
		Net_Rendition const & nr,
		_hoops_GACR alter *dl,
		bool _hoops_IHGI)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	H3DData alter *h3ddata = H3DD (dc);
	H3D_Display_List *_hoops_CHGI = null;
	H3D_Display_List_Bin *_hoops_RRHA;
	_hoops_ISSH *_hoops_CSSH = h3ddata->_hoops_CSSH;
	_hoops_AGGI *_hoops_SHGI;
	bool _hoops_GIGI = false;
	bool _hoops_RIGI = false;
	_hoops_IRHA *pair;
	_hoops_AIGI *list;
	Tristrip *ts;
	bool _hoops_CISP;
	bool _hoops_PIGI = false;
	bool _hoops_HIGI = false;
	bool _hoops_IIGI = h3ddata->_hoops_CIGI->_hoops_SIGI;

	if (dl) {
		_hoops_CHGI = (H3D_Display_List *)dl->list;
		_hoops_IIGI |= BIT (dl->action_mask, _hoops_GCGI);
	}
	else
		_hoops_GIGI = true;

	if (h3ddata->_hoops_CIGI->_hoops_RCGI) {
		list = h3ddata->_hoops_CIGI->_hoops_RCGI;
		list->ResetCursor();
		while((pair = list->PeekCursor()) != null) {
			list->AdvanceCursor();

			ts = (Tristrip *) pair->geo;
			if (BIT (ts->face_attributes.flags, _hoops_IAGI) &&
				_hoops_CHGI && BIT (_hoops_CHGI->item._hoops_ACGI._hoops_PCGI, T_FACES)) {
				_hoops_PIGI = true;
				continue; // _hoops_RH _hoops_HCGI _hoops_AIAH _hoops_ICGI _hoops_RH _hoops_HHHA _hoops_CCGI
			}

			H3D_Display_List_Bin *_hoops_SSSH = POOL_NEW(dc->memory_pool, H3D_Display_List_Bin)(dc->memory_pool);
			_hoops_SSSH->id._hoops_IRA (nr, T_FACES, ts, 0, H3DID_USE_FACE_DISPLACEMENT);
			if (_hoops_GIGI)
				_hoops_SSSH->_hoops_HGGI = pair->nr->_hoops_CPA;
			_hoops_SSSH->_hoops_IGGI.point_count += (ts->point_count < ts->total ? ts->point_count : ts->total);;
			_hoops_SSSH->_hoops_IGGI.total += ts->total;
			_hoops_SSSH->_hoops_IGGI._hoops_PHHA += ts->_hoops_PHHA;
			if (_hoops_IIGI)
				_hoops_RRHA = null;
			else
				_hoops_RRHA = _hoops_HSSH (h3ddata, _hoops_CSSH, _hoops_SSSH, T_FACES, pair);
			if (!_hoops_RRHA) {
				/* _hoops_CSH _hoops_PIS _hoops_SCGI _hoops_GSGI, _hoops_HIS _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_SPR, _hoops_PPR _hoops_GGCR _hoops_IS _hoops_RSGI */
				_hoops_RRHA = _hoops_SSSH;
				_hoops_RRHA->flags = ts->_hoops_SRHA & ~(_hoops_GAHH | DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS);
				_hoops_RRHA->nr = pair->nr;
				if (BIT (ts->_hoops_SRHA, _hoops_GGIA))
					_hoops_RRHA->flags |= (_hoops_GGIA | DL_INDEX_INTERPOLATION);
				if (_hoops_CSSH->LookupItem (_hoops_RRHA->_hoops_HGGI, &_hoops_SHGI) != VHASH_STATUS_SUCCESS) {
					_hoops_SHGI = POOL_NEW(dc->memory_pool, _hoops_AGGI)(dc->memory_pool);
					_hoops_CSSH->InsertItem (_hoops_RRHA->_hoops_HGGI, _hoops_SHGI);
				}
				_hoops_SHGI->AddFirst(_hoops_RRHA);
			}
			else {
				_hoops_RRHA->_hoops_IGGI.point_count += (ts->point_count < ts->total ? ts->point_count : ts->total);;
				_hoops_RRHA->_hoops_IGGI.total += ts->total;
				_hoops_RRHA->_hoops_IGGI._hoops_PHHA += ts->_hoops_PHHA;
				delete _hoops_SSSH;
			}

			/* _hoops_RGPA _hoops_RH _hoops_CRHH _hoops_CRGR _hoops_RH _hoops_SCGI , _hoops_PPR _hoops_ARP _hoops_GII _hoops_ASGI _hoops_PIH */
			_hoops_RRHA->_hoops_CRHA->AddFirst (pair);


		}
		_hoops_CISP = BIT (nr->_hoops_PSGI, T_FACES);

		_hoops_ISSH::PairList *_hoops_HSGI = _hoops_CSSH->GetPairList ();
		_hoops_ISSH::Pair * p;

		while ((p = _hoops_HSGI->RemoveFirst()) != null) {
			_hoops_SHGI = p->Item();
			_hoops_CSSH->RemoveItem (p->Key());
			delete p;
			while ((_hoops_RRHA = _hoops_SHGI->RemoveFirst()) != null) {
				_hoops_ISGI const *_hoops_CSGI = dc->_hoops_SPA->modelling_matrix;
				_hoops_SSGI const *_hoops_GGRI = dc->_hoops_SPA->color;

				_hoops_RRHA->_hoops_CRHA->ResetCursor();
				pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
				ts = (Tristrip *) pair->geo;

				if (!dl ||
					BIT (HOOPS_WORLD->system_flags, _hoops_RGRI) ||
					BIT (dl->_hoops_AGRI, DL_INSUFFICIENT_VRAM) ||
					BIT (dl->action_mask, _hoops_PGRI) ||
					!BIT (_hoops_CHGI->item._hoops_ACGI.flags, H3D_SEGDL_BLESSED_SEGMENT) ||
					_hoops_HGRI(nr, ts->_hoops_SRHA, _hoops_CISP))
					_hoops_GIGI = true;

				/* _hoops_RPP _hoops_HHH _hoops_IGRI _hoops_PAH'_hoops_RA _hoops_SHH _hoops_CGRI _hoops_CRGR _hoops_IRS _hoops_HCGI, _hoops_SGRI _hoops_CRGR _hoops_CPAP _hoops_GRRI */
				if (_hoops_CHGI &&
					BIT (_hoops_CHGI->item._hoops_ACGI.flags, H3D_SEGDL_BLESSED_SEGMENT) &&
					h3ddata->_hoops_CIGI->_hoops_SIGI) {
					_hoops_GIGI = true;
					_hoops_RIGI = true;
				}

				if (!_hoops_GIGI) {
					_hoops_RRRI (nr, null, _hoops_RRHA);
					if (!_hoops_RRHA->odl || _hoops_RRHA->flags == DL_FLAG_INVALID) {
						if (_hoops_RRHA->odl) {
							HD_Queue_Destroy_List (_hoops_RRHA->odl, true);
							_hoops_RRHA->odl = null;
						}
						if (_hoops_RRHA->flags == DL_FLAG_INVALID) {
							_hoops_IRHA *pair = _hoops_RRHA->_hoops_CRHA->PeekFirst();
							ts = (Tristrip *) pair->geo;
							_hoops_RRHA->flags = ts->_hoops_SRHA;
						}
						else if (BIT(_hoops_RRHA->flags, DL_INSUFFICIENT_VRAM)) {
							dl->_hoops_AGRI |= DL_INSUFFICIENT_VRAM;
						}
						_hoops_IPGI(_hoops_CHGI->item._hoops_ACGI._hoops_ARRI);
						_hoops_GIGI = true;
					}
					else if (_hoops_RRHA->odl) {
						if (nr->_hoops_IRR->_hoops_SRI != _hoops_GAI ||
							!BIT (nr->transform_rendition->heuristics, _hoops_IRI))
							dl->_hoops_PRRI &= ~_hoops_HRRI;
						if (!_hoops_CHGI->item._hoops_ACGI._hoops_ARRI)
							_hoops_CHGI->item._hoops_ACGI._hoops_ARRI = POOL_NEW(dc->memory_pool, H3D_Display_List_List)(dc->memory_pool);
						_hoops_CHGI->item._hoops_ACGI._hoops_ARRI->AddFirst (_hoops_RRHA->odl);
						if (BIT (_hoops_RRHA->odl->item.geometry._hoops_IRRI, _hoops_IAGI))
							_hoops_HIGI = true;
					}
				}

				if (_hoops_GIGI) {
					if (!_hoops_IHGI) {
						if (!_hoops_RIGI)
							_hoops_RRHA->flags |= _hoops_SRHH;
						else
							_hoops_RRHA->flags |= DL_SUPPRESS_SEGMENT_DISPLAY_LISTS;
						if (dl && 
							BIT (dl->action_mask, _hoops_PGRI) &&
							pair->nr->_hoops_IHA->_hoops_CPA != nr->_hoops_IHA->_hoops_CPA) {
							_hoops_RRHA->_hoops_CRHA->ResetCursor();
							while ((pair = _hoops_RRHA->_hoops_CRHA->PeekCursor()) != null) {
								_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
								ts = (Tristrip *) pair->geo; 
								if (BIT (ts->_hoops_SRHA, _hoops_GGIA))
									_hoops_CRRI (pair->nr, ts, null);
								else
									_hoops_RRRI (pair->nr, ts, null);
							}
						}
						else {
							ts = (Tristrip *) pair->geo; //_hoops_SRRI _hoops_HPGR _hoops_RH _hoops_SRS _hoops_GARI
							if (BIT (ts->_hoops_SRHA, _hoops_GGIA))
								_hoops_CRRI (nr, null, _hoops_RRHA);
							else
								_hoops_RRRI (nr, null, _hoops_RRHA);

						}
					}
					if (dl) {
						dl->action_mask |= _hoops_PGRI;
						if (nr->_hoops_IHA->_hoops_CHA->_hoops_ARIR ||
							nr->_hoops_IHA->_hoops_GIA->_hoops_ARIR)
							dl->_hoops_AGRI |= DL_TEXTURING;
					}
				}
				dc->_hoops_SPA->modelling_matrix = _hoops_CSGI;
				dc->_hoops_SPA->color = _hoops_GGRI;
				delete _hoops_RRHA;
			}
			/* _hoops_RARI _hoops_RH _hoops_CIPH _hoops_SR _hoops_HPSH _hoops_IAPR _hoops_RH _hoops_SRS _hoops_GHIR _hoops_AARI */
			if (_hoops_CHGI &&
				BIT (_hoops_CHGI->item._hoops_ACGI._hoops_PCGI, T_FACES)) {
				if (_hoops_GIGI) {
					while ((pair = list->PeekCursor()) != null) {
						list->AdvanceCursor();
						ts = (Tristrip *) pair->geo;
						if (BIT (ts->face_attributes.flags, _hoops_IAGI)) {
							unsigned int _hoops_PARI = ts->_hoops_SRHA;
							ts->_hoops_SRHA |= _hoops_SRHH;
							if (!_hoops_IHGI) {
								if (BIT (ts->_hoops_SRHA, _hoops_GGIA))
									_hoops_CRRI (pair->nr, ts, null);
								else
									_hoops_RRRI (pair->nr, ts, null);
							}
							ts->_hoops_SRHA = _hoops_PARI;
						}
					}
				}
				else {
					_hoops_HARI (nr, _hoops_CHGI->item._hoops_ACGI._hoops_ARRI, true, false);
				}
			}
			if (_hoops_HIGI)
				_hoops_CHGI->item._hoops_ACGI._hoops_PCGI |= T_FACES;

			delete _hoops_SHGI;
		}
		ASSERT (_hoops_CSSH->Count() == 0);
		delete _hoops_HSGI;

		/* _hoops_SP _hoops_GH _hoops_IARI _hoops_HIGR */
		ASSERT (list == h3ddata->_hoops_CIGI->_hoops_RCGI);
		while ((pair = list->RemoveFirst()) != null) {
			ts = (Tristrip *)pair->geo;
			ts->_hoops_CARI &= ~_hoops_SARI;

			//_hoops_RPP _hoops_ASGA _hoops_CHR _hoops_GPRI _hoops_PPR _hoops_RPRI _hoops_IS _hoops_APRI (_hoops_HAS._hoops_IAS. _hoops_HAR _hoops_HHHA), _hoops_PSCR _hoops_PPRI '_hoops_HPRI (_hoops_HPGR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_PAAP)
			if (ts->_hoops_GSCP &&
				(ts->_hoops_GSCP->type == _hoops_SCIP || ts->_hoops_GSCP->type == _hoops_GSIP) && 
				!_hoops_GIGI) {
				Polyhedron const *_hoops_IPRI = (Polyhedron const *)ts->_hoops_GSCP;
				Local_Face_Attributes const *_hoops_CPRI = (Local_Face_Attributes const *) &_hoops_IPRI->local_face_attributes;
				Local_Vertex_Attributes const *_hoops_SPRI = (Local_Vertex_Attributes const *) &_hoops_IPRI->local_vertex_attributes;

				if ((_hoops_CPRI->normals != null && _hoops_CPRI->explicit_normal_count == 0) ||
					 (_hoops_SPRI->normals != null && _hoops_SPRI->explicit_normal_count == 0))
					HI_Queue_Flush_Derived_Normals (dc->_hoops_GHRI, (Polyhedron alter *)ts->_hoops_GSCP);
			}
			//_hoops_RHRI _hoops_AHRI, _hoops_PHRI, _hoops_CHR _hoops_SHR _hoops_HHRI _hoops_HPP _hoops_RH _hoops_CRHH, _hoops_HIS _hoops_SCH'_hoops_GRI _hoops_IHRI _hoops_IS _hoops_CHRI _hoops_CAPR _hoops_RPHR _hoops_SGGR _hoops_RPP _hoops_GPRI
			if (BIT (ts->_hoops_SRHA, _hoops_CAGI)) {
				ts->_hoops_SRHA &= ~_hoops_CAGI;
				if (ts->_hoops_PAGI && BIT (ts->_hoops_RAHH, _hoops_SHRI)) {
					FREE_ARRAY (ts->_hoops_PAGI, ts->face_count, RGB);
					ts->_hoops_PAGI = null;
					ts->_hoops_RAHH &= ~_hoops_SHRI;
				}
			}

			delete pair;
		}
		delete h3ddata->_hoops_CIGI->_hoops_RCGI;
		h3ddata->_hoops_CIGI->_hoops_RCGI = null;
	}
	else if (_hoops_CHGI &&
			 _hoops_CHGI->item._hoops_ACGI._hoops_ARRI) {
		bool _hoops_GIRI = false;
		if (BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_EDGES) &&
			_hoops_CPGI (nr->_hoops_IRR))
			_hoops_GIRI = BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_FACES);
		else
			_hoops_GIRI = BIT (nr->_hoops_RGP, T_FACES);
		bool _hoops_RIRI = BIT (_hoops_CHGI->item._hoops_ACGI._hoops_PCGI, T_FACES);
		if (_hoops_GIRI || _hoops_RIRI)
			_hoops_HARI (nr, _hoops_CHGI->item._hoops_ACGI._hoops_ARRI, _hoops_RIRI, _hoops_GIRI);
	}
	UNREFERENCED (_hoops_IHGI);

} /* _hoops_RSGR _hoops_API '_hoops_RSGR _hoops_CRHH _hoops_AIRI _hoops_HIGR' */



local void
_hoops_PIRI (
		Net_Rendition const & nr,
		_hoops_GACR alter *dl,
		bool _hoops_IHGI)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	H3DData alter *h3ddata = H3DD (dc);
	H3D_Display_List *_hoops_CHGI = null;
	H3D_Display_List_Bin *_hoops_RRHA;
	_hoops_ISSH *_hoops_CSSH = h3ddata->_hoops_CSSH;
	_hoops_AGGI *_hoops_HIRI;
	_hoops_IRHA *pair;
	_hoops_AIGI *list;
	bool _hoops_GIGI = false;
	bool _hoops_RIGI = false;
	Polyedge alter *pe;
	int stage = 0;
	_hoops_ACHR _hoops_RGP = nr->_hoops_RGP;
	bool _hoops_PIGI = false;
	bool _hoops_HIGI = false;
	int type;

	if (dl)
		_hoops_CHGI = (H3D_Display_List *)dl->list;
	else
		_hoops_GIGI = true;

	if (h3ddata->_hoops_CIGI->_hoops_IIRI ||
		h3ddata->_hoops_CIGI->_hoops_CIRI||
		h3ddata->_hoops_CIGI->_hoops_SIRI) {
		for (stage = 0; stage < 3; stage++) {
			if (stage == 0) {
				list = h3ddata->_hoops_CIGI->_hoops_SIRI;
				type = _hoops_GPA;
			}
			else if (stage == 1) {
				list = h3ddata->_hoops_CIGI->_hoops_CIRI;
				type = T_EDGES;
			}
			else if (stage == 2) {
				list = h3ddata->_hoops_CIGI->_hoops_IIRI;
				type = T_EDGES;
			}
			else
				break; // _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_SSRR

			if (!list)
				continue;
			list->ResetCursor();
			while ((pair = list->PeekCursor()) != null) {
				list->AdvanceCursor();
				pe = (Polyedge *) pair->geo;
				if (dl) {
					if (list == h3ddata->_hoops_CIGI->_hoops_CIRI)
						dl->_hoops_PRRI |= _hoops_GCRI;
					if (list == h3ddata->_hoops_CIGI->_hoops_SIRI)
						dl->_hoops_PRRI |= _hoops_RCRI;
				}
				if (BIT (pe->_hoops_PPGI.flags, _hoops_APGI) &&
					_hoops_CHGI && BIT (_hoops_CHGI->item._hoops_ACGI._hoops_PCGI, type)) {
					_hoops_PIGI = true;
					continue; // _hoops_RH _hoops_HCGI _hoops_AIAH _hoops_ICGI _hoops_RH _hoops_HHHA _hoops_AHHA
				}

				H3DShaderID id;
				H3D_Display_List_Bin *_hoops_SSSH = POOL_NEW(dc->memory_pool, H3D_Display_List_Bin)(dc->memory_pool);
				int length, point_count;

				_hoops_SSSH->id._hoops_IRA (nr, type, pe, 0, 0);
				if (_hoops_GIGI)
					_hoops_SSSH->_hoops_HGGI = pair->nr->_hoops_CPA;
				_hoops_RRHA = _hoops_HSSH (h3ddata, _hoops_CSSH, _hoops_SSSH, type, pair);
				if (!_hoops_RRHA) {
					/* _hoops_CSH _hoops_PIS _hoops_SCGI _hoops_GSGI, _hoops_HIS _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_SPR, _hoops_PPR _hoops_GGCR _hoops_IS _hoops_RSGI */
					_hoops_RRHA = _hoops_SSSH;
					_hoops_RRHA->nr = nr;
					if (_hoops_CSSH->LookupItem (_hoops_RRHA->_hoops_HGGI, &_hoops_HIRI) != VHASH_STATUS_SUCCESS) {
						_hoops_HIRI = POOL_NEW(dc->memory_pool, _hoops_AGGI)(dc->memory_pool);
						_hoops_CSSH->InsertItem (_hoops_RRHA->_hoops_HGGI, _hoops_HIRI);
					}
					_hoops_HIRI->AddFirst(_hoops_RRHA);
				}
				else
					delete _hoops_SSSH;
				_hoops_RRHA->_hoops_CRHA->AddFirst(pair);

				//_hoops_CAHA _hoops_GGSR _hoops_ACRI'_hoops_GRI _hoops_PPSR _hoops_RPR
				_hoops_RPHA(pe, null, H3D_Shared_Vertices, &length, &point_count, null);
				_hoops_RRHA->_hoops_IGGI.point_count += point_count;
				_hoops_RRHA->_hoops_IGGI.total += length;
			}

			if (_hoops_CHGI &&
				!BIT (_hoops_CHGI->item._hoops_ACGI.flags, H3D_SEGDL_BLESSED_SEGMENT)) {
				_hoops_GIGI = true;
				if (BIT (_hoops_CHGI->item._hoops_ACGI.flags, H3D_SEGDL_BLESSED_GEOMETRY))
					_hoops_RIGI = true;
			}

			_hoops_ISSH::PairList *_hoops_HSGI = _hoops_CSSH->GetPairList ();
			_hoops_ISSH::Pair * p;

			_hoops_HSGI->ResetCursor();
			if (!_hoops_GIGI) {
				POINTER_SIZED_INT _hoops_PCRI = 0;
				while ((p = _hoops_HSGI->PeekCursor()) != null) {
					_hoops_HSGI->AdvanceCursor();
					_hoops_HIRI = p->Item();
					_hoops_HIRI->ResetCursor();
					while ((_hoops_RRHA = _hoops_HIRI->PeekCursor()) != null) {
						_hoops_HIRI->AdvanceCursor();
						if (_hoops_RRHA->_hoops_IGGI.point_count < _hoops_RRHA->_hoops_IGGI.total)
							_hoops_PCRI += 16 * _hoops_RRHA->_hoops_IGGI.point_count;
						else
							_hoops_PCRI += 16 * _hoops_RRHA->_hoops_IGGI.total;
						_hoops_PCRI += 2 * _hoops_RRHA->_hoops_IGGI.total;
					}
				}
				if (h3ddata->_hoops_IHP)
					_hoops_PCRI *= 6;
				if (!_hoops_HCRI (h3ddata, _hoops_PCRI))
					_hoops_GIGI = true;
			}

	    	while ((p = _hoops_HSGI->RemoveFirst()) != null) {
				_hoops_HIRI = p->Item();
				_hoops_CSSH->RemoveItem (p->Key());
				delete p;
				/* _hoops_CHPR _hoops_GRR _hoops_SCGI _hoops_CRGR _hoops_RRAP->_hoops_ICRI._hoops_CCRI(), _hoops_PGAP _hoops_GRS _hoops_SCRI _hoops_HCR _hoops_RH _hoops_RGHP _hoops_GSRI. */
				while ((_hoops_RRHA = _hoops_HIRI->RemoveFirst()) != null) {

					pair = _hoops_RRHA->_hoops_CRHA->PeekFirst();
					pe = (Polyedge *) pair->geo;

					int weight = _hoops_RRHA->nr->_hoops_RHP->weight;
					if (weight < 0)
						weight = (int)(HD_Compute_Generic_Size (nr, nr->_hoops_RHP->_hoops_PHP, nr->_hoops_RHP->_hoops_HHP,1.0f, false, 0, true)+0.5f);

					if (dl) {
						if (list == h3ddata->_hoops_CIGI->_hoops_SIRI) {
							if (BIT (dl->action_mask, _hoops_RSRI) &&
								BIT (_hoops_CHGI->item._hoops_ACGI._hoops_RGP, _hoops_GPA))
								_hoops_GIGI = true;
						}
						else {
							ASSERT (list == h3ddata->_hoops_CIGI->_hoops_IIRI ||
									list == h3ddata->_hoops_CIGI->_hoops_CIRI);
							if (BIT (dl->action_mask, _hoops_ASRI) &&
								ANYBIT (_hoops_CHGI->item._hoops_ACGI._hoops_RGP, _hoops_PSRI))
								_hoops_GIGI = true;
						}

						if (h3ddata->_hoops_CIGI->_hoops_SIGI ||
							_hoops_HSRI (_hoops_RRHA->nr, _hoops_RRHA->nr->_hoops_RHP, false, weight))
							_hoops_GIGI = true;
					}
					else
						_hoops_GIGI = true;


					if (!_hoops_GIGI) {
						if (BIT (pe->_hoops_SRHA, _hoops_GGIA))
							_hoops_ISRI (_hoops_RRHA->nr, null, _hoops_RRHA);
						else
							really_draw_3d_polyedge (_hoops_RRHA->nr, null, _hoops_RRHA->nr->_hoops_RHP, _hoops_RRHA);
						if (_hoops_RRHA->odl == null) {
							_hoops_GIGI = true;
						}
						else {
							//_hoops_SCGI->_hoops_CSRI _hoops_HRGR _hoops_IRS _hoops_SSRI _hoops_GPRR
							if (list == h3ddata->_hoops_CIGI->_hoops_CIRI) {
								if (_hoops_CHGI->item._hoops_ACGI._hoops_GGAI == null)
									_hoops_CHGI->item._hoops_ACGI._hoops_GGAI = POOL_NEW(dc->memory_pool, H3D_Display_List_List)(dc->memory_pool);
								_hoops_CHGI->item._hoops_ACGI._hoops_GGAI->AddFirst(_hoops_RRHA->odl);
							}
							else if (list == h3ddata->_hoops_CIGI->_hoops_SIRI) {
								if (_hoops_CHGI->item._hoops_ACGI._hoops_RGAI == null)
									_hoops_CHGI->item._hoops_ACGI._hoops_RGAI = POOL_NEW(dc->memory_pool, H3D_Display_List_List)(dc->memory_pool);
								_hoops_CHGI->item._hoops_ACGI._hoops_RGAI->AddFirst(_hoops_RRHA->odl);
							}
							else {
								if (_hoops_CHGI->item._hoops_ACGI._hoops_AGAI == null)
									_hoops_CHGI->item._hoops_ACGI._hoops_AGAI = POOL_NEW(dc->memory_pool, H3D_Display_List_List)(dc->memory_pool);
								_hoops_CHGI->item._hoops_ACGI._hoops_AGAI->AddFirst(_hoops_RRHA->odl);
							}
							if (h3ddata->_hoops_IHP)
								dl->_hoops_PRRI |= _hoops_PGAI;
							if (nr->_hoops_IRR->_hoops_SRI != _hoops_GAI ||
								!BIT (nr->transform_rendition->heuristics, _hoops_IRI))
								dl->_hoops_PRRI &= ~_hoops_HRRI;

							if (BIT (_hoops_RRHA->odl->item.geometry._hoops_IRRI, _hoops_APGI))
								_hoops_HIGI = true;
						}
					}
					else
						_hoops_GIGI = true;


					if (_hoops_GIGI) {

						_hoops_ISGI const *_hoops_CSGI = dc->_hoops_SPA->modelling_matrix;
						_hoops_SSGI const *_hoops_GGRI = dc->_hoops_SPA->color;
						dc->_hoops_SPA->modelling_matrix = null;

						/* _hoops_PGSA _hoops_SCGI _hoops_GGR _hoops_HGAI _hoops_CCH */
						_hoops_RRHA->_hoops_CRHA->ResetCursor();
						while ((pair = _hoops_RRHA->_hoops_CRHA->RemoveFirst()) != null) {
							Polyedge alter *pe = (Polyedge *)pair->geo;
							unsigned int _hoops_PARI = pe->_hoops_SRHA;
							if (_hoops_RIGI || !_hoops_CHGI)
								pe->_hoops_SRHA |= DL_SUPPRESS_SEGMENT_DISPLAY_LISTS;
							else
								pe->_hoops_SRHA |= _hoops_SRHH;
							if (!_hoops_IHGI) {
								if (BIT (pe->_hoops_SRHA, _hoops_GGIA))
									_hoops_ISRI (pair->nr, pe, null);
								else
									really_draw_3d_polyedge (pair->nr, pe, pair->nr->_hoops_RHP, null);
							}
							pe->_hoops_SRHA = _hoops_PARI;
							if (dl) {
								if (list == h3ddata->_hoops_CIGI->_hoops_SIRI) {
									dl->action_mask |= _hoops_RSRI;
								}
								else {
									dl->action_mask |= _hoops_IGAI;
									if (list == h3ddata->_hoops_CIGI->_hoops_CIRI)
										dl->action_mask |= _hoops_PGRI;
								}
							}
						}
						dc->_hoops_SPA->modelling_matrix = _hoops_CSGI;
						dc->_hoops_SPA->color = _hoops_GGRI;
					}
					delete _hoops_RRHA;
				}

				/* _hoops_RARI _hoops_RH _hoops_CIPH _hoops_SR _hoops_HPSH _hoops_IAPR _hoops_RH _hoops_SRS _hoops_GHIR _hoops_AARI */
				if (_hoops_CHGI && BIT (_hoops_CHGI->item._hoops_ACGI._hoops_PCGI, type)) {
					if (_hoops_GIGI) {
						while ((pair = list->PeekCursor()) != null) {
							list->AdvanceCursor();
							pe = (Polyedge *) pair->geo;
							if (BIT (pe->_hoops_PPGI.flags, _hoops_APGI)) {
								unsigned int _hoops_PARI = pe->_hoops_SRHA;
								if (_hoops_RIGI)
									pe->_hoops_SRHA |= DL_SUPPRESS_SEGMENT_DISPLAY_LISTS;
								else
									pe->_hoops_SRHA |= _hoops_SRHH;
								if (!_hoops_IHGI) {
									if (BIT (pe->_hoops_SRHA, _hoops_GGIA))
										_hoops_ISRI (pair->nr, pe, null);
									else
										really_draw_3d_polyedge (pair->nr, pe, pair->nr->_hoops_RHP, null);
								}
								pe->_hoops_SRHA = _hoops_PARI;
							}
						}
					}
					else {
						h3ddata->_hoops_AIP = BIT(dl->_hoops_PRRI, _hoops_PGAI);
						_hoops_CGAI (nr, _hoops_CHGI, true, false);
						h3ddata->_hoops_AIP = false;
					}
				}
				if (_hoops_HIGI)
					_hoops_CHGI->item._hoops_ACGI._hoops_PCGI |= type;

				delete _hoops_HIRI;
			}
			ASSERT (_hoops_CSSH->Count() == 0);
			delete _hoops_HSGI;

			/* _hoops_SP _hoops_GH _hoops_IARI _hoops_HIGR */
			while ((pair = list->RemoveFirst()) != null) {
				pe = (Polyedge alter *) pair->geo;
				pe->_hoops_CARI &= ~_hoops_SARI;
				delete pair;
			}
			delete list;
		}
		h3ddata->_hoops_CIGI->_hoops_IIRI = 0;
		h3ddata->_hoops_CIGI->_hoops_CIRI = 0;
		h3ddata->_hoops_CIGI->_hoops_SIRI = null;
	}
	else if (_hoops_CHGI &&
			 (_hoops_CHGI->item._hoops_ACGI._hoops_AGAI||
			 ANYBIT (dl->_hoops_PRRI, _hoops_GCRI|_hoops_RCRI))) {
		bool _hoops_GIRI = (ANYBIT (_hoops_RGP, _hoops_PSRI) ||
							 ANYBIT (dl->_hoops_PRRI, _hoops_GCRI));
		bool _hoops_RIRI = ANYBIT (_hoops_CHGI->item._hoops_ACGI._hoops_PCGI, T_EDGES|_hoops_GPA);

		if (BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_EDGES) &&
			ANYBIT (dl->_hoops_PRRI, _hoops_RCRI))
			_hoops_GIRI = true;

		if (_hoops_GIRI || _hoops_RIRI) {
			h3ddata->_hoops_AIP = BIT(dl->_hoops_PRRI, _hoops_PGAI);
			_hoops_CGAI (nr, _hoops_CHGI, _hoops_RIRI, _hoops_GIRI);
			h3ddata->_hoops_AIP = false;
		}
	}
}


local bool
_hoops_SGAI (Net_Rendition const & nr,
					_hoops_ICP const & _hoops_CCP,
					Polymarker const * pm)
{
	if (ANYBIT (_hoops_CCP->glyph->flags, _hoops_GRAI))
		return true;

	UNREFERENCED (nr);
	UNREFERENCED (pm);
	return false;
}


//_hoops_HRS _hoops_IHPR _hoops_RPP _hoops_SR _hoops_RRAI _hoops_IRS _hoops_ARAI _hoops_IS _hoops_RH _hoops_HIGR
local bool
_hoops_PRAI (
		Net_Rendition const &nr,
		_hoops_ACHR _hoops_HRAI,
		Polymarker alter *_hoops_IRAI,
		int count,
		bool _hoops_IHGI,
		bool _hoops_GIGI,
		H3D_Display_List *_hoops_CHGI)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	bool added = false;

	if (_hoops_GIGI && _hoops_IHGI)
		return false;


	_hoops_IRAI->length = _hoops_IRAI->point_count = count;
	if (_hoops_GIGI ||
		!_hoops_HCRI(h3ddata, 0))
		_hoops_IRAI->_hoops_SRHA |= _hoops_SRHH;

	if (_hoops_HRAI == T_MARKERS &&
		nr->_hoops_GSP->_hoops_CPA != nr->_hoops_SCP->_hoops_CPA) {
		Net_Rendition _hoops_CRAI = nr;
		_hoops_CRAI.Modify()->_hoops_SCP = _hoops_CRAI->_hoops_GSP;
		draw_3d_polymarker (_hoops_CRAI, _hoops_IRAI);
	}
	else
		draw_3d_polymarker (nr, _hoops_IRAI);
	
	if (_hoops_IRAI->_hoops_GAHA && 
		!BIT(_hoops_IRAI->_hoops_GAHA->_hoops_AGRI, DL_INSUFFICIENT_VRAM) && 
		_hoops_IRAI->_hoops_GAHA->list) {
		//_hoops_SRAI _hoops_SCH!
		H3D_Display_List *odl = (H3D_Display_List *)_hoops_IRAI->_hoops_GAHA->list;

		if (_hoops_HRAI == T_MARKERS) {
			if (_hoops_CHGI->item._hoops_ACGI._hoops_GAAI == null)
				_hoops_CHGI->item._hoops_ACGI._hoops_GAAI = POOL_NEW(dc->memory_pool, H3D_Display_List_List)(dc->memory_pool);
			_hoops_CHGI->item._hoops_ACGI._hoops_GAAI->AddLast (odl);
		}
		else {
			if (_hoops_CHGI->item._hoops_ACGI._hoops_RAAI == null)
				_hoops_CHGI->item._hoops_ACGI._hoops_RAAI = POOL_NEW(dc->memory_pool, H3D_Display_List_List)(dc->memory_pool);
			_hoops_CHGI->item._hoops_ACGI._hoops_RAAI->AddLast (odl);
		}
		//_hoops_AAAI _hoops_HII _hoops_RH _hoops_PAAI (_hoops_PGAP _hoops_HRGR _hoops_HAAI _hoops_IS _hoops_PHHR _hoops_SGGR)
		odl->_hoops_PPAH = null;
		_hoops_IRAI->_hoops_GAHA->list = null;
		//_hoops_AAAI _hoops_HII _hoops_RH _hoops_IAAI _hoops_HIGR (_hoops_CR _hoops_SCH _hoops_HRGR _hoops_HHRI _hoops_HPP _hoops_RH _hoops_HCGI)
		_hoops_CAAI (HOOPS_WORLD->_hoops_SAAI);
		ASSERT (HOOPS_WORLD->_hoops_GPAI == odl); //_hoops_SR _hoops_SAHR _hoops_SPIP _hoops_SCH, _hoops_HIS _hoops_SCH _hoops_CGH _hoops_SHH _hoops_RH _hoops_ICRP _hoops_RPAI
		HOOPS_WORLD->_hoops_GPAI = HOOPS_WORLD->_hoops_GPAI->next;
		HOOPS_WORLD->_hoops_GPAI->prev = &(HOOPS_WORLD->_hoops_GPAI);
		odl->next = null;
		odl->prev = null;
		ASSERT (!HOOPS_WORLD->_hoops_GPAI || HOOPS_WORLD->_hoops_GPAI != HOOPS_WORLD->_hoops_GPAI->next);
		_hoops_APAI (HOOPS_WORLD->_hoops_SAAI);

		added = true;
	}
	return added;
}


#define _hoops_PPAI(_hoops_GGGI,_hoops_RGGI) (\
	( \
		((_hoops_GGGI->color==null) && (_hoops_RGGI->color==null)) || \
		(_hoops_GGGI->color && _hoops_RGGI->color && (_hoops_GGGI->color->_hoops_GHA == _hoops_RGGI->color->_hoops_GHA)) \
	) \
)
#define _hoops_HPAI(_hoops_GGGI,_hoops_RGGI) (\
	( \
		((_hoops_GGGI->color==null) && (_hoops_RGGI->color==null)) || \
		(_hoops_GGGI->color && _hoops_RGGI->color && (_hoops_GGGI->color->_hoops_GHA == _hoops_RGGI->color->_hoops_GHA)) \
	) \
)
#define _hoops_IPAI(_hoops_GGGI,_hoops_RGGI) (\
	(_hoops_GGGI->_hoops_CPAI == _hoops_RGGI->_hoops_CPAI) && \
	( \
		((_hoops_GGGI->color==null) && (_hoops_RGGI->color==null)) || \
		(_hoops_GGGI->color && _hoops_RGGI->color && (_hoops_GGGI->color->_hoops_GHA == _hoops_RGGI->color->_hoops_GHA)) \
	) \
)
#define _hoops_SPAI 64

#define _hoops_GHAI 4096

local void
_hoops_RHAI (
		Net_Rendition const &nr,
		_hoops_GACR alter *dl,
		bool _hoops_IHGI)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	H3DData *h3ddata = H3DD(dc);
	bool _hoops_AHAI = true;
	H3D_Display_List *_hoops_CHGI = (H3D_Display_List *)dl->list;

	ASSERT (h3ddata->_hoops_PHAI <= _hoops_GHAI);
	if (h3ddata->_hoops_CIGI->_hoops_HHAI ||
		h3ddata->_hoops_CIGI->_hoops_IHAI) {
		_hoops_AIGI *list = null;
		Color_Object _hoops_RAIH = 0;
		_hoops_ACHR _hoops_HRAI = 0;
		_hoops_IRHA *pair;
		_hoops_IRHA *_hoops_CHAI[_hoops_SPAI];
		_hoops_IRHA **_hoops_SHAI = _hoops_CHAI;
		int _hoops_GIAI = _hoops_SPAI;
		int _hoops_RIAI = 0, _hoops_AIAI = 0;
		int pass;
		int i;
		Point _hoops_PIAI[_hoops_GHAI];
		RGB _hoops_HIAI[_hoops_GHAI];
		float _hoops_IIAI[_hoops_GHAI];
		float *_hoops_CIAI = null;
		int param_width = 0;
		int stage = 0;
		H3D_Display_List *odl;
		bool _hoops_GIGI = false;
		H3D_Display_List_List *_hoops_SIAI = null;
		bool _hoops_GCAI = false;
		Polymarker alter *_hoops_IRAI = null;


		_hoops_AHAI = false;
		if (dl)
			_hoops_CHGI = (H3D_Display_List *)dl->list;
		for (stage = 0; stage < 2; stage++) {
			int count = 0;
			int total = 0;
			int _hoops_RCAI = 0;
			bool _hoops_ACAI = false;
			if (stage == 0) {
				list = h3ddata->_hoops_CIGI->_hoops_IHAI;
				_hoops_GIGI = _hoops_SGAI (nr, nr->_hoops_GSP, null);
				_hoops_HRAI = T_MARKERS;
				_hoops_RAIH = Color_MARKER;
				if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_APA], M_DIFFUSE))
					_hoops_ACAI = true;
				if (_hoops_CHGI && (_hoops_SIAI = _hoops_CHGI->item._hoops_ACGI._hoops_GAAI) != null) {
					_hoops_AHAI = true;
					_hoops_SIAI->ResetCursor();
					while ((odl = _hoops_SIAI->PeekCursor()) != null) {
						_hoops_RCAI += odl->item.geometry._hoops_IGGI.total;
						_hoops_SIAI->AdvanceCursor();
					}					
				}
			}
			else if (stage == 1) {
				list = h3ddata->_hoops_CIGI->_hoops_HHAI;
				_hoops_GIGI = _hoops_SGAI (nr, nr->_hoops_SCP, null);
				_hoops_HRAI = T_VERTICES;
				_hoops_RAIH = Color_VERTEX;
				if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_PPA], M_DIFFUSE))
					_hoops_ACAI = true;
				if (_hoops_CHGI && (_hoops_SIAI = _hoops_CHGI->item._hoops_ACGI._hoops_RAAI) != null) {
					_hoops_AHAI = true;
					_hoops_SIAI->ResetCursor();
					while ((odl = _hoops_SIAI->PeekCursor()) != null) {
						_hoops_RCAI += odl->item.geometry._hoops_IGGI.total;
						_hoops_SIAI->AdvanceCursor();
					}					
				}
			}
			else
				break; // _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_SSRR

			if (!list)
				continue;
			if (!_hoops_CHGI)
				_hoops_GIGI = true;

			_hoops_SHAI[0] = list->PeekFirst();
			_hoops_RIAI = 1;
			for(pass = 0; pass < _hoops_RIAI; pass++) {
				total = 0;
				count = 0;

				list->ResetCursor();
				while ((pair = list->PeekCursor()) != null) {
					list->AdvanceCursor();
					if (!_hoops_PPAI (pair, _hoops_SHAI[pass])) {
						if (pass == 0) {
							//_hoops_CAHA _hoops_GGSR _hoops_RPP _hoops_SR _hoops_RRP _hoops_IS _hoops_GGCR _hoops_IRS _hoops_CCAH _hoops_PCAI
							if (!_hoops_PPAI (pair, _hoops_SHAI[_hoops_AIAI])) {
								for (i = 0; i < _hoops_RIAI; i++) {
									if (_hoops_PPAI (pair, _hoops_SHAI[i])) {
										_hoops_AIAI = i;
										break;
									}
								}
								if (i == _hoops_RIAI) {
									if (_hoops_RIAI == _hoops_GIAI) {
										_hoops_IRHA **victim = _hoops_SHAI;
										_hoops_GIAI *= 2;
										ZALLOC_ARRAY (_hoops_SHAI, _hoops_GIAI, _hoops_IRHA *);
										_hoops_AIGA (victim, _hoops_RIAI, _hoops_IRHA *, _hoops_SHAI);
										if (victim != _hoops_CHAI)
											FREE_ARRAY (victim, _hoops_RIAI, _hoops_IRHA *);
									}
									_hoops_SHAI[_hoops_RIAI] = pair;
									_hoops_RIAI++;
								}
							}
						}
						continue;
					}
					if (pair->type == _hoops_IRHA::_hoops_HCAI) {
						Polymarker const *pm = (Polymarker const *)pair->geo;
						Point const *p;
						int vi;

						for (int i = _hoops_RCAI; i < pm->length ; i++) {
							if (_hoops_IRAI == null) {
								ZALLOC (_hoops_IRAI, Polymarker);
								_hoops_ICAI (_hoops_IRAI);
								_hoops_IRAI->points = _hoops_PIAI;
								if (pm->_hoops_HCHA)
									_hoops_IRAI->_hoops_HCHA = _hoops_IIAI;
								else {
									if (!_hoops_ACAI && _hoops_CCAI (_hoops_SHAI[pass]->color, _hoops_RAIH) != null)
										_hoops_IRAI->_hoops_PCHA = _hoops_HIAI;
									else if (pm->_hoops_PCHA)
										_hoops_IRAI->_hoops_PCHA = _hoops_HIAI;
								}
								if (pm->_hoops_GSHA > param_width) {
									if (_hoops_CIAI != null)
										FREE_ARRAY(_hoops_CIAI, _hoops_GHAI * param_width, float);
									ALLOC_ARRAY(_hoops_CIAI, _hoops_GHAI * pm->_hoops_GSHA, float);
									param_width = pm->_hoops_GSHA;
								}
								_hoops_IRAI->_hoops_GSHA = pm->_hoops_GSHA;
								_hoops_IRAI->_hoops_SCAI = pm->_hoops_SCAI;
								if (pm->_hoops_CCHA)
									_hoops_IRAI->_hoops_CCHA = _hoops_CIAI;
								_hoops_IRAI->_hoops_SRHA |= DL_TEMPORARY_DATA;
								_hoops_IRAI->_hoops_SRHA |= pm->_hoops_SRHA;
								_hoops_IRAI->_hoops_CARI |= pm->_hoops_CARI;
								_hoops_IRAI->_hoops_GSAI |= pm->_hoops_GSAI;
								if (BIT (pm->_hoops_SRHA, _hoops_GGIA))
									_hoops_GCAI = true;
							}
							if (pm->_hoops_AIHA) 
								vi = pm->_hoops_AIHA[i];
							else
								vi = i;
							p = &pm->points[vi];
							if (pair->_hoops_CPAI) {
								float _hoops_APCP = 1.0f / _hoops_PHCP (pair->_hoops_CPAI->matrix.elements, *p);
								_hoops_IRAI->points[count].x = _hoops_HPRA (pair->_hoops_CPAI->matrix.elements, *p) * _hoops_APCP;
								_hoops_IRAI->points[count].y = _hoops_IPRA (pair->_hoops_CPAI->matrix.elements, *p) * _hoops_APCP;
								_hoops_IRAI->points[count].z = _hoops_CPRA (pair->_hoops_CPAI->matrix.elements, *p) * _hoops_APCP;
							}
							else
								_hoops_RSAI (p, Point, &_hoops_IRAI->points[count]);
							if (_hoops_IRAI->_hoops_PCHA) { /* _hoops_ASAI _hoops_PSAI->_hoops_HAIR, _hoops_GAR _hoops_RH _hoops_RGSR _hoops_GHCA _hoops_HAR _hoops_GHAA _hoops_IS _hoops_SAIA */
								if (pm->_hoops_PCHA) {
									_hoops_RSAI (&pm->_hoops_PCHA[vi], RGB, &_hoops_IRAI->_hoops_PCHA[count]);
								}
								else {
								    RGB const *_hoops_GPCP = _hoops_CCAI (pair->color, _hoops_RAIH);
								    _hoops_RSAI (_hoops_GPCP, RGB, &_hoops_IRAI->_hoops_PCHA[count]);
							    }
							}
							if (_hoops_CIAI) {
								_hoops_AIGA (&pm->_hoops_CCHA[vi*pm->_hoops_GSHA], pm->_hoops_GSHA, float, &_hoops_CIAI[count*pm->_hoops_GSHA]);
							}
							else if (_hoops_IRAI->_hoops_HCHA)
								_hoops_IRAI->_hoops_HCHA[count] = pm->_hoops_HCHA[vi];
							count++;
							if (count == h3ddata->_hoops_PHAI) {
								if (!_hoops_PRAI (nr, 
										_hoops_HRAI, 
										_hoops_IRAI,
										count, 
										_hoops_IHGI, 
										_hoops_GIGI,
										_hoops_CHGI)) {
									_hoops_GIGI = true;
								}
								else {
									_hoops_AHAI = true;
									total += count;
								}
								if (_hoops_IRAI->_hoops_HSAI > 1) {
									_hoops_ISAI (_hoops_IRAI);
									_hoops_IRAI = null;
								}
								count = 0;
							}
						}
						if (_hoops_RCAI >= pm->length)
							_hoops_RCAI -= pm->length;
						else
							_hoops_RCAI = 0;
					}
					else {
						Marker const *m = (Marker const *)pair->geo;
						for (;;) {
							if (_hoops_RCAI == 0) {
								if (_hoops_IRAI == null) {
									ZALLOC (_hoops_IRAI, Polymarker);
									_hoops_ICAI (_hoops_IRAI);
									_hoops_IRAI->_hoops_SRHA |= DL_TEMPORARY_DATA;
									_hoops_IRAI->_hoops_CARI = 0;
									_hoops_IRAI->_hoops_GSAI = 0;
									_hoops_IRAI->points = _hoops_PIAI;
									if (!_hoops_ACAI && _hoops_CCAI (_hoops_SHAI[pass]->color, _hoops_RAIH) != null)
										_hoops_IRAI->_hoops_PCHA = _hoops_HIAI;
								}
								if (pair->_hoops_CPAI) {
									float _hoops_APCP = 1.0f / _hoops_PHCP (pair->_hoops_CPAI->matrix.elements, m->_hoops_CSAI);
									_hoops_IRAI->points[count].x = _hoops_HPRA (pair->_hoops_CPAI->matrix.elements, m->_hoops_CSAI) * _hoops_APCP;
									_hoops_IRAI->points[count].y = _hoops_IPRA (pair->_hoops_CPAI->matrix.elements, m->_hoops_CSAI) * _hoops_APCP;
									_hoops_IRAI->points[count].z = _hoops_CPRA (pair->_hoops_CPAI->matrix.elements, m->_hoops_CSAI) * _hoops_APCP;
								}
								else
									_hoops_RSAI (&m->_hoops_CSAI, Point, &_hoops_IRAI->points[count]);
								if (_hoops_IRAI->_hoops_PCHA) {
									RGB const *_hoops_GPCP = _hoops_CCAI (pair->color, _hoops_RAIH);
									_hoops_RSAI (_hoops_GPCP, RGB, &_hoops_IRAI->_hoops_PCHA[count]);
								}
								count++;
								if (count == h3ddata->_hoops_PHAI) {
									//_hoops_CHRI _hoops_IRS _hoops_SSAI
									if (!_hoops_PRAI (nr, 
											_hoops_HRAI, 
											_hoops_IRAI,
											count, 
											_hoops_IHGI, 
											_hoops_GIGI,
											_hoops_CHGI)) {
										_hoops_GIGI = true;
									}
									else {
										_hoops_AHAI = true;
										total += count;
									}
									if (_hoops_IRAI->_hoops_HSAI > 1) {
										_hoops_ISAI (_hoops_IRAI);
										_hoops_IRAI = null;
									}
									count = 0;
								}
							}
							else
								--_hoops_RCAI;

							if (pair->single)
								break;
							m = (Marker const *)m->next;
							if (!m)
								break;
						}
					}
				}
				if (count) {
					if (count + total < H3D_Display_List_MINIMUM)
						_hoops_GIGI = true;

					//_hoops_CHRI _hoops_RH _hoops_GGPI
					if (!_hoops_PRAI (nr, 
							_hoops_HRAI, 
							_hoops_IRAI,
							count, 
							_hoops_IHGI, 
							_hoops_GIGI,
							_hoops_CHGI)) {
						_hoops_GIGI = true;
					}
					else {
						_hoops_AHAI = true;
						total += count;
					}
				}
				if (_hoops_IRAI && 
					_hoops_ISAI (_hoops_IRAI) == 0) {
					HI_Free_Polymarker (_hoops_IRAI);
					_hoops_IRAI = null;
				}

				if (_hoops_GIGI) {
					if (stage == 0)
						dl->action_mask |= _hoops_HCIP;
					else
						dl->action_mask |= _hoops_RGPI;
				}
			}

			/* _hoops_SP _hoops_GH _hoops_IARI _hoops_HIGR _hoops_PPR _hoops_AGPI _hoops_PGPI/_hoops_HGPI _hoops_IGPI */
			while ((pair = list->RemoveFirst()) != null)
				delete pair;
			delete list;
		}
		h3ddata->_hoops_CIGI->_hoops_IHAI = null;
		h3ddata->_hoops_CIGI->_hoops_HHAI = null;
		if (_hoops_CIAI)
			FREE_ARRAY(_hoops_CIAI, _hoops_GHAI * param_width, float);
		if (_hoops_SHAI != _hoops_CHAI) {
			FREE_ARRAY (_hoops_SHAI, _hoops_GIAI, _hoops_IRHA *);
			_hoops_SHAI = null;
		}
	}
	if (_hoops_IHGI)
		_hoops_AHAI = false;

	if (_hoops_CHGI && _hoops_AHAI) {
		if (_hoops_CHGI->item._hoops_ACGI._hoops_GAAI &&
			BIT (nr->_hoops_RGP, T_MARKERS)) {
			_hoops_CGPI (nr, T_MARKERS, _hoops_CHGI->item._hoops_ACGI._hoops_GAAI);
		}
		if (_hoops_CHGI->item._hoops_ACGI._hoops_RAAI &&
			BIT (nr->_hoops_RGP, T_VERTICES)) {
			_hoops_CGPI (nr, T_VERTICES, _hoops_CHGI->item._hoops_ACGI._hoops_RAAI);
		}
	}
}


local void
_hoops_SGPI (
		Net_Rendition const & nr,
		_hoops_GACR alter *dl,
		bool _hoops_IHGI)
{
	UNREFERENCED(_hoops_IHGI);
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	H3DData *h3ddata = H3DD(dc);
	H3D_Display_List *_hoops_CHGI = null;
	H3D_Display_List_Bin *_hoops_RRHA, *_hoops_GRPI;
	_hoops_ISSH *_hoops_CSSH = h3ddata->_hoops_CSSH;
	_hoops_AGGI *_hoops_RRPI;
	_hoops_IRHA *pair;
	H3DShaderID id;
	_hoops_AIGI *list;
	bool _hoops_GIGI = false;
	bool _hoops_ARPI = false;
	bool _hoops_PRPI = false;

	if (dl)
		_hoops_CHGI = (H3D_Display_List *)dl->list;
	else
		_hoops_GIGI = true;
	if (h3ddata->_hoops_CIGI->_hoops_HRPI) {
		if (!dl ||
			BIT (dl->action_mask, _hoops_IRPI) ||
			!BIT (_hoops_CHGI->item._hoops_ACGI.flags, H3D_SEGDL_BLESSED_SEGMENT))
			_hoops_GIGI = true;

		list = h3ddata->_hoops_CIGI->_hoops_HRPI;
		id._hoops_IRA (nr, T_LINES, null, 0, 0);
		while ((pair = list->RemoveFirst()) != null) {
			H3DShaderID id;
			H3D_Display_List_Bin *_hoops_SSSH = POOL_NEW(dc->memory_pool, H3D_Display_List_Bin)(dc->memory_pool);

			_hoops_SSSH->id._hoops_IRA (nr, T_LINES, null, 0, 0);
			_hoops_RRHA = _hoops_HSSH (h3ddata, _hoops_CSSH, _hoops_SSSH, T_LINES, pair);
			if (!_hoops_RRHA) {
				/* _hoops_CSH _hoops_PIS _hoops_SCGI _hoops_GSGI, _hoops_HIS _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_SPR, _hoops_PPR _hoops_GGCR _hoops_IS _hoops_RSGI */
				_hoops_RRHA = _hoops_SSSH;
				_hoops_RRHA->nr = nr;
				if (_hoops_CSSH->LookupItem (_hoops_RRHA->_hoops_HGGI, &_hoops_RRPI) != VHASH_STATUS_SUCCESS) {
					_hoops_RRPI = POOL_NEW(dc->memory_pool, _hoops_AGGI)(dc->memory_pool);
					_hoops_CSSH->InsertItem (_hoops_RRHA->_hoops_HGGI, _hoops_RRPI);
				}
				_hoops_RRPI->AddFirst(_hoops_RRHA);
			}
			else
				delete _hoops_SSSH;
			_hoops_RRHA->_hoops_CRHA->AddFirst(pair);
		}
		ASSERT (list->Count() == 0);
		delete h3ddata->_hoops_CIGI->_hoops_HRPI;
		h3ddata->_hoops_CIGI->_hoops_HRPI = list = null;

		_hoops_ISSH::PairList *_hoops_HSGI = _hoops_CSSH->GetPairList ();
		_hoops_ISSH::Pair * p;

		while ((p = _hoops_HSGI->RemoveFirst()) != null) {
			_hoops_RRPI = p->Item();
			_hoops_CSSH->RemoveItem (p->Key());
			delete p;
			while ((_hoops_RRHA = _hoops_RRPI->RemoveFirst()) != null) {
				H3D_Display_List *_hoops_CRPI = null;

				int weight = _hoops_RRHA->nr->_hoops_AHP->weight;
				if (weight < 0)
					weight = (int)(HD_Compute_Generic_Size (nr, _hoops_RRHA->nr->_hoops_AHP->_hoops_PHP, _hoops_RRHA->nr->_hoops_AHP->_hoops_HHP,1.0f, false, 0, true)+0.5f);

				if (weight > H3D_LARGEST_PRECOMPUTED_CIRCLE ||
					BIT(_hoops_RRHA->nr->_hoops_AHP->flags, _hoops_SRPI) ||
					_hoops_GAPI (_hoops_RRHA->nr->_hoops_AHP->line_style)) {
					while ((pair = _hoops_RRHA->_hoops_CRHA->RemoveFirst()) != null) {
						if (!_hoops_IHGI)
							segment_render (pair->nr, (Geometry *)pair->geo, _hoops_RAPI, pair->single);
						delete pair;
					}
					if (dl)
						dl->action_mask |= _hoops_IRPI;
				}
				else {
					//_hoops_GGR _hoops_RH _hoops_AAPI _hoops_AGIR, _hoops_SCH _hoops_CSAP _hoops_GARI, _hoops_SAHA, _hoops_PPR _hoops_PAPI.  _hoops_HAPI _hoops_SR _hoops_SAHR _hoops_HS _hoops_SAHA
					H3D_Display_List_Bin_List *_hoops_IAPI = POOL_NEW(dc->memory_pool, H3D_Display_List_Bin_List)(dc->memory_pool);

					if (_hoops_CHGI &&
						_hoops_CHGI->item._hoops_ACGI._hoops_CAPI) {
						_hoops_CRPI = _hoops_CHGI->item._hoops_ACGI._hoops_CAPI->PeekFirst();
					}
					_hoops_SAPI (_hoops_RRHA->nr, _hoops_RRHA, _hoops_IAPI, &_hoops_ARPI, &_hoops_PRPI, &_hoops_GIGI);

					if (!_hoops_GIGI &&
						_hoops_IAPI->Count() &&
						_hoops_HCRI(h3ddata, 0) &&
						!h3ddata->_hoops_CIGI->_hoops_SIGI &&
						!BIT (dl->action_mask, _hoops_CIIP)) {
						if (!_hoops_CRPI) {
							ZALLOC (_hoops_CRPI, H3D_Display_List);
							_hoops_CRPI->type = H3D_DL_SEGMENT_POLYLINE;
							_hoops_CRPI->time_stamp = HOOPS_WORLD->_hoops_GPPI;
							_hoops_CRPI->item._hoops_RPPI._hoops_ARPI = _hoops_ARPI;
							if (_hoops_ARPI) {
								_hoops_CRPI->item._hoops_RPPI._hoops_SAR = nr->_hoops_ARA->_hoops_APPI._hoops_SAR;
								_hoops_CRPI->item._hoops_RPPI._hoops_PPPI = nr->_hoops_ARA->_hoops_APPI._hoops_PPPI;
								_hoops_CRPI->item._hoops_RPPI._hoops_HPPI = nr->_hoops_ARA->_hoops_APPI._hoops_HPPI;
								_hoops_CRPI->item._hoops_RPPI._hoops_IPPI = nr->_hoops_ARA->_hoops_APPI._hoops_IPPI;
								_hoops_CRPI->item._hoops_RPPI._hoops_CPPI = nr->_hoops_ARA->_hoops_APPI._hoops_CPPI;
								_hoops_CRPI->item._hoops_RPPI._hoops_SPPI = nr->_hoops_ARA->_hoops_APPI._hoops_SPPI;
							}
						}
						_hoops_IAPI->ResetCursor();
						while ((_hoops_GRPI = _hoops_IAPI->PeekCursor()) != null) {
							_hoops_IAPI->AdvanceCursor();
							really_draw_3d_polyedge (_hoops_GRPI->nr, null, _hoops_GRPI->nr->_hoops_AHP, _hoops_GRPI);
							if (_hoops_GRPI->odl) {
								if (h3ddata->_hoops_IHP)
									dl->_hoops_PRRI |= _hoops_PGAI;
								if (nr->_hoops_IRR->_hoops_SRI != _hoops_GAI ||
									!BIT (nr->transform_rendition->heuristics, _hoops_IRI))
									dl->_hoops_PRRI &= ~_hoops_HRRI;
								if (!_hoops_CRPI->item._hoops_RPPI._hoops_GHPI)
									_hoops_CRPI->item._hoops_RPPI._hoops_GHPI = POOL_NEW(dc->memory_pool, H3D_Display_List_List)(dc->memory_pool);
								_hoops_CRPI->item._hoops_RPPI._hoops_GHPI->AddFirst (_hoops_GRPI->odl);
								_hoops_GRPI->odl = null;
							}
							else
								dl->action_mask |= _hoops_IRPI;
						}
						if (_hoops_CHGI->item._hoops_ACGI._hoops_CAPI == null)
							_hoops_CHGI->item._hoops_ACGI._hoops_CAPI = POOL_NEW(dc->memory_pool, H3D_Display_List_List)(dc->memory_pool);
						_hoops_CHGI->item._hoops_ACGI._hoops_CAPI->AddFirst(_hoops_CRPI);
						_hoops_CRPI = null;
					}
					else
						_hoops_GIGI = true;

					if (_hoops_GIGI) {
						_hoops_ISGI const *_hoops_CSGI = dc->_hoops_SPA->modelling_matrix;
						_hoops_SSGI const *_hoops_GGRI = dc->_hoops_SPA->color;
						/* _hoops_PGSA _hoops_RHPI _hoops_GGR _hoops_HGAI _hoops_CCH */
						dc->_hoops_SPA->modelling_matrix = null;
						dc->_hoops_SPA->color = null;
						if (!_hoops_IHGI) {
							_hoops_IAPI->ResetCursor();
							while ((_hoops_GRPI = _hoops_IAPI->PeekCursor()) != null) {
								_hoops_IAPI->AdvanceCursor();
								_hoops_GRPI->flags |= _hoops_SRHH;
								really_draw_3d_polyedge (_hoops_GRPI->nr, null, _hoops_GRPI->nr->_hoops_AHP, _hoops_GRPI);
								ASSERT (_hoops_GRPI->odl == null);
							}
						}
						if (dl)
							dl->action_mask |= _hoops_IRPI;
						dc->_hoops_SPA->modelling_matrix = _hoops_CSGI;
						dc->_hoops_SPA->color = _hoops_GGRI;
					}

					if (_hoops_PRPI) {
						Geometry const *g;

						_hoops_RRHA->_hoops_CRHA->ResetCursor();
						while ((pair = _hoops_RRHA->_hoops_CRHA->PeekCursor()) != null) {
							_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
							g = (Geometry const *)pair->geo;
							if (g->type == _hoops_RCIP)
								continue;
							h3ddata->_hoops_AHPI = !pair->single;
							dc->_hoops_RAI = g;
							_hoops_PHPI (pair->nr, g, _hoops_RAPI, pair->single);
							h3ddata->_hoops_AHPI = false;
						}
						if (dl)
							dl->action_mask |= _hoops_SHIP|_hoops_AIIP;
					}

					while ((_hoops_GRPI = _hoops_IAPI->RemoveFirst()) != null) {
						while ((pair = _hoops_GRPI->_hoops_CRHA->RemoveFirst()) != null) {
							ASSERT (((Polyedge *) pair->geo)->_hoops_GAHA == null);
							delete pair;
						}
						_hoops_GRPI->odl = null;
						delete _hoops_GRPI;
					}
					delete _hoops_IAPI;
				}
				while ((pair = _hoops_RRHA->_hoops_CRHA->RemoveFirst()) != null) {
					delete pair;
				}
				_hoops_RRHA->odl = null;
				delete _hoops_RRHA;
			}
			delete _hoops_RRPI;
		}
		delete _hoops_HSGI;
		ASSERT (_hoops_CSSH->Count() == 0);
	}
	else if (_hoops_CHGI &&
			_hoops_CHGI->item._hoops_ACGI._hoops_CAPI &&
			BIT (nr->_hoops_RGP, T_LINES) &&
			!h3ddata->_hoops_PI.mode) {
		h3ddata->_hoops_AIP = BIT(dl->_hoops_PRRI, _hoops_PGAI);
		_hoops_HHPI (nr, _hoops_CHGI->item._hoops_ACGI._hoops_CAPI);
		h3ddata->_hoops_AIP = false;
	}
}

/*
 * _hoops_PGAA - _hoops_IHPI _hoops_IRS _hoops_CRHH _hoops_GHRP _hoops_IH _hoops_RSPH _hoops_CHPI.
 */
local void
_hoops_SHPI (Net_Rendition const & nr, Tristrip *ts, bool _hoops_GIPI)
{

	ts->face_count = ts->point_count >> 2; // _hoops_PPSR _hoops_RPR _hoops_RIPI _hoops_HPP 4
	ALLOC_ARRAY_ALIGNED (ts->points, ts->point_count, Point, 16);
	ALLOC_ARRAY (ts->lengths, ts->_hoops_PHHA, int);
	ALLOC_ARRAY (ts->_hoops_AIHA, ts->total, int);
	ZALLOC_ARRAY (ts->face_indices, ts->total, int);
	ts->_hoops_RAHH |= _hoops_AAHH | _hoops_AIPI;
	if (_hoops_GIPI) {
		ALLOC_ARRAY (ts->_hoops_PCHA, ts->point_count, RGB);
		ts->_hoops_RAHH |= _hoops_PIPI;
	}
	if (nr->_hoops_IRR->_hoops_SRI == _hoops_GAI &&
		BIT (nr->transform_rendition->heuristics, _hoops_IRI)) {
		ALLOC_ARRAY_CACHED (ts->_hoops_CCCP, ts->point_count, float);
		ts->_hoops_RAHH |= _hoops_HIPI;
	}

	// _hoops_IIPI _hoops_CIPI
	ts->point_count = 0;
	ts->total = 0;
	ASSERT(ts->_hoops_PHHA == 1) ;
	ts->lengths[0] = 0;

	ts->_hoops_CARI |= _hoops_APIA;

	_hoops_HHA const & matr = nr->_hoops_IHA->_hoops_CHA;
	_hoops_HHA const & _hoops_SIPI = nr->_hoops_IHA->_hoops_GIA;

	if (matr->_hoops_IRIR < 1.0f ||
		_hoops_SIPI->_hoops_IRIR < 1.0f) {
		if (nr->_hoops_CPP->_hoops_PRH.style != _hoops_GCPI)
			ts->_hoops_SRHA |= DL_HAS_TRANSPARENCY;
	}
	if (nr->_hoops_IHA->pattern != FP_SOLID)
		ts->_hoops_SRHA |= DL_PATTERN;
	if (BIT (nr->transform_rendition->flags, _hoops_GRHH) &&
		BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES)) {
		ts->_hoops_SRHA |= DL_LIGHTING;
		ALLOC_ARRAY_ALIGNED (ts->_hoops_PRHH, ts->face_count, _hoops_ARPA, 16);
		ts->_hoops_RAHH |= _hoops_RCPI;
	}
	ts->_hoops_GSAI = nr->_hoops_IRR->_hoops_CSA & Rendo_TRISTRIP_MASK;
}


/*
 * _hoops_PGAA - _hoops_GGCR _hoops_ACPI _hoops_PCPI _hoops_CPAP _hoops_IH _hoops_PCCP _hoops_HCPI _hoops_IS _hoops_RH _hoops_CRHH
 */
local void
_hoops_ICPI(
		Tristrip *ts,
		int _hoops_CCPI,
		int _hoops_SCPI,
		_hoops_GSPI const *e,
		_hoops_HRPA const *matrix,
		RGB const *_hoops_GPCP,
		bool _hoops_RSPI,
		bool _hoops_ASPI)
{
	// _hoops_RHCP _hoops_PSPI _hoops_IH _hoops_PCPI
	int ii;
	int const _hoops_HSPI = ts->point_count;
	int const _hoops_ISPI = _hoops_HSPI + 1;
	int const _hoops_CSPI = _hoops_HSPI + 2;
	int const _hoops_SSPI = _hoops_HSPI + 3;

	// _hoops_AGHP _hoops_GPHA _hoops_PIH
	if (matrix) {
		Point buffer[4];
		float _hoops_APCP;
		Point *_hoops_PCAP;

		buffer[0] =  e->center + e->_hoops_GGHI + e->_hoops_RGHI;
		buffer[1] =  e->center + e->_hoops_GGHI - e->_hoops_RGHI;
		buffer[2] =  e->center - e->_hoops_GGHI + e->_hoops_RGHI;
		buffer[3] =  e->center - e->_hoops_GGHI - e->_hoops_RGHI;

		_hoops_PCAP = &ts->points[_hoops_HSPI];
		ASSERT (_hoops_SSPI - _hoops_HSPI == 3);
		for (ii = 0; ii < 4; ii++) {
			_hoops_APCP = 1.0f / _hoops_PHCP (matrix->elements, buffer[ii]);
			_hoops_PCAP->x = _hoops_HPRA(matrix->elements, buffer[ii]) * _hoops_APCP;
			_hoops_PCAP->y = _hoops_IPRA(matrix->elements, buffer[ii]) * _hoops_APCP;
			_hoops_PCAP->z = _hoops_CPRA(matrix->elements, buffer[ii]) * _hoops_APCP;
			_hoops_PCAP++;
		}

	}
	else {
		ts->points[_hoops_HSPI] = e->center + e->_hoops_GGHI + e->_hoops_RGHI;
		ts->points[_hoops_ISPI] = e->center + e->_hoops_GGHI - e->_hoops_RGHI;
		ts->points[_hoops_CSPI] = e->center - e->_hoops_GGHI + e->_hoops_RGHI;
		ts->points[_hoops_SSPI] = e->center - e->_hoops_GGHI - e->_hoops_RGHI;
	}

	if (_hoops_GPCP) {
		ts->_hoops_PCHA[_hoops_HSPI] = *_hoops_GPCP;
		ts->_hoops_PCHA[_hoops_ISPI] = *_hoops_GPCP;
		ts->_hoops_PCHA[_hoops_CSPI] = *_hoops_GPCP;
		ts->_hoops_PCHA[_hoops_SSPI] = *_hoops_GPCP;
	}

	if (ts->_hoops_CCCP) {
		ts->_hoops_CCCP[ts->point_count] = _hoops_SCCP(e->priority,1);
		for (ii = 1; ii < 4; ii++)
			ts->_hoops_CCCP[ts->point_count + ii] = ts->_hoops_CCCP[ts->point_count];
	}

	// _hoops_AGHP _hoops_PSPI _hoops_IH 2-_hoops_SCPH _hoops_CGGR _hoops_IS _hoops_SHAA _hoops_PCPI.
	int *indices = ts->_hoops_AIHA + ts->total;

	// _hoops_AGHI _hoops_HIPH
	if (_hoops_ASPI) {
		indices[0] = _hoops_HSPI;
		indices[1] = _hoops_ISPI;
		indices[2] = _hoops_CSPI;
		indices[3] = _hoops_SSPI;
	}
	else {
		indices[0] = _hoops_HSPI;
		indices[1] = _hoops_CSPI;
		indices[2] = _hoops_ISPI;
		indices[3] = _hoops_SSPI;
	}

	int _hoops_PGHI = 4;

	if (_hoops_RSPI)
	{
		// _hoops_PHAA _hoops_HGHI _hoops_SCPH
		indices[4] = _hoops_SSPI;

		// _hoops_PHAA _hoops_GPHA _hoops_IIGR _hoops_SPS _hoops_PCPI _hoops_GRS _hoops_SHH... _hoops_IGHI _hoops_CGHI _hoops_RARP _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_GAHR.
		int const _hoops_SGHI = _hoops_AHIA(_hoops_HSPI + 4, _hoops_SCPI - 1);

		// _hoops_GRHI _hoops_HGHI _hoops_SCPH
		indices[5] = _hoops_SGHI;

		// _hoops_SGR _hoops_CAPR
		_hoops_PGHI += 2;
	}

	// _hoops_RRHI _hoops_ASGA _hoops_ARHI _hoops_HSP _hoops_SR _hoops_PRHI.
	if (ts->_hoops_PRHH)
		ts->_hoops_PRHH[_hoops_CCPI] = e->plane;
	for (int i = 0; i < _hoops_PGHI; ++i)
		ts->face_indices[ts->total + i] = _hoops_CCPI;

	// _hoops_HRHI _hoops_RAGP
	ts->point_count += 4;
	ts->total += _hoops_PGHI;

	// _hoops_PGPR _hoops_HS _hoops_SPR _hoops_CGGR, _hoops_SAHR _hoops_IRHI _hoops_SCH.
	ASSERT(ts->_hoops_PHHA == 1);
	ts->lengths[0] += _hoops_PGHI;
}



local void _hoops_CRHI (
		int shift,
		int count,
		int *_hoops_SRHI)
{
	int i;
	int *_hoops_GAHI;

	_hoops_GAHI = _hoops_SRHI;
	for (i = 1; i < count - 1; i++) {
		*_hoops_GAHI++ = 0 + shift;
		*_hoops_GAHI++ = i + shift;
		*_hoops_GAHI++ = i + shift + 1;
	}
}


local void _hoops_RAHI (
		int shift,
		int count,
		int *_hoops_SRHI)
{
	int i;
	int *_hoops_GAHI;

	_hoops_GAHI = _hoops_SRHI;
	*_hoops_GAHI++ = 0 + shift;
	for (i = 1; i*2 <= count; i++) {
		*_hoops_GAHI++ = i + shift;
		if (i*2 == count)
			break;
		*_hoops_GAHI++ = (count - i) + shift;
	}
}


struct _hoops_AAHI {
	Point *_hoops_PAHI; //_hoops_IH _hoops_HAHI-_hoops_IAHI
	int *indices;
	int _hoops_CAHI;
	int _hoops_SAHI;
	int _hoops_GPHI;
};

local void _hoops_RPHI (
		void *_hoops_PAPH,
		Integer32 _hoops_HAPH,
		Point const * p1, Point const * p2, Point const * _hoops_IAPH,
		Integer32 _hoops_ISPI, Integer32 _hoops_CSPI, Integer32 _hoops_SSPI,
		Intersection const * i1, Intersection const * i2, Intersection const * _hoops_SAPH)
{
	_hoops_AAHI *_hoops_APHI = (_hoops_AAHI *)_hoops_PAPH;
	int _hoops_PPHI = 0;

	if (_hoops_ISPI < 0 && -_hoops_ISPI > _hoops_PPHI)
		_hoops_PPHI = -_hoops_ISPI;
	if (_hoops_CSPI < 0 && -_hoops_CSPI > _hoops_PPHI)
		_hoops_PPHI = -_hoops_CSPI;
	if (_hoops_SSPI < 0 && -_hoops_SSPI > _hoops_PPHI)
		_hoops_PPHI = -_hoops_SSPI;

	if (_hoops_PPHI > _hoops_APHI->_hoops_CAHI) {
		Point *_hoops_HPHI;
		ZALLOC_ARRAY (_hoops_HPHI, _hoops_PPHI, Point);
		if (_hoops_APHI->_hoops_CAHI > 0) {
			_hoops_AIGA (_hoops_APHI->_hoops_PAHI, _hoops_APHI->_hoops_CAHI, Point, _hoops_HPHI);
			FREE_ARRAY (_hoops_APHI->_hoops_PAHI, _hoops_APHI->_hoops_CAHI, Point);
		}
		_hoops_APHI->_hoops_PAHI = _hoops_HPHI;
		_hoops_APHI->_hoops_CAHI = _hoops_PPHI;
	}
	if (_hoops_APHI->_hoops_GPHI + 3 > _hoops_APHI->_hoops_SAHI) {
		int *_hoops_IPHI;
		ZALLOC_ARRAY (_hoops_IPHI, _hoops_APHI->_hoops_SAHI + 12, int);
		if (_hoops_APHI->_hoops_SAHI > 0) {
			if (_hoops_APHI->_hoops_GPHI)
				_hoops_AIGA (_hoops_APHI->indices, _hoops_APHI->_hoops_GPHI, int, _hoops_IPHI);
			FREE_ARRAY (_hoops_APHI->indices, _hoops_APHI->_hoops_SAHI, int);
		}
		_hoops_APHI->indices = _hoops_IPHI;
		_hoops_APHI->_hoops_SAHI += 12;
	}

	if (_hoops_ISPI < 0)
		_hoops_APHI->_hoops_PAHI[-_hoops_ISPI - 1] = *p1; 
	_hoops_APHI->indices[_hoops_APHI->_hoops_GPHI] = _hoops_ISPI;
	_hoops_APHI->_hoops_GPHI++;
	if (_hoops_CSPI < 0)
		_hoops_APHI->_hoops_PAHI[-_hoops_CSPI - 1] = *p2; 
	_hoops_APHI->indices[_hoops_APHI->_hoops_GPHI] = _hoops_CSPI;
	_hoops_APHI->_hoops_GPHI++;
	if (_hoops_SSPI < 0)
		_hoops_APHI->_hoops_PAHI[-_hoops_SSPI - 1] = *_hoops_IAPH; 
	_hoops_APHI->indices[_hoops_APHI->_hoops_GPHI] = _hoops_SSPI;
	_hoops_APHI->_hoops_GPHI++;
	UNREFERENCED (i1);
	UNREFERENCED (i2);
	UNREFERENCED (_hoops_SAPH);
	UNREFERENCED (_hoops_HAPH);
}


local void
_hoops_CPHI (
		Polygon const *p,
		_hoops_AAHI *_hoops_APHI)
{
	int i;
	int *face_list;

	ALLOC_ARRAY (face_list, p->count + 1, int);
	face_list[0] = p->count;
	for (i = 0; i < p->count; i++)
		face_list[i+1] = i;
	HI_Triangulate_Face_X (p->points, (Vector *)&p->plane, face_list,
						 face_list + p->count + 1, _hoops_RPHI,
						 (void alter *) _hoops_APHI);
	FREE_ARRAY (face_list, p->count + 1, int);
}


local void
_hoops_SPHI (
		Polygon const *p,
		_hoops_AAHI const *_hoops_APHI,
		int shift,
		int *_hoops_SRHI)
{
	int i;
	int *_hoops_GAHI = _hoops_SRHI;

	for (i = 0; i < _hoops_APHI->_hoops_GPHI; i++) {
		if (_hoops_APHI->indices[i] < 0)
			*_hoops_GAHI++ = -_hoops_APHI->indices[i] - 1 + shift + p->count;
		else
			*_hoops_GAHI++ = _hoops_APHI->indices[i] + shift;
	}
}


local _hoops_GHHI alter *
_hoops_RHHI (_hoops_GHHI const *a, _hoops_HRPA const *mat)
{
	_hoops_GHHI alter *_hoops_AHHI = null;
	switch (a->type) {
		case _hoops_RIIP:
		case _hoops_GIIP:
		case _hoops_GRCP:
		case _hoops_RRCP: {
			Circular_Arc alter *_hoops_PAGR;
			ZALLOC (_hoops_PAGR, Circular_Arc);
			_hoops_AHHI = (_hoops_GHHI alter *)_hoops_PAGR;
			_hoops_PAGR->type = a->type;
			_hoops_PAGR->arc_start = a->arc_start;
			_hoops_PAGR->_hoops_PHHI = a->_hoops_PHHI;
		} _hoops_HHHI;

		case _hoops_SGCP:
		case _hoops_CGCP: {
			Ellipse *_hoops_PAGR;
			Vector _hoops_IHHI, _hoops_CHHI;
			Point pt;

			if (_hoops_AHHI == null) {
				ZALLOC (_hoops_PAGR, Ellipse);
				_hoops_PAGR->type = _hoops_CGCP;
			}
			else
				_hoops_PAGR = (Ellipse *)_hoops_AHHI;

			if (BIT (a->_hoops_RRHH, _hoops_SHHI)) {
				Vector _hoops_GIHI;
				_hoops_ARPA _hoops_RIHI;
				_hoops_AIHI const *	c;
				c = (_hoops_AIHI const *)a;		/* _hoops_IHRI _hoops_IH _hoops_PIHI _hoops_HAH */

				pt.x = c->center.x;
				pt.y = c->center.x;
				pt.z = 0;
				_hoops_PAGR->center.x = _hoops_HPRA (mat->elements, pt);
				_hoops_PAGR->center.y = _hoops_IPRA (mat->elements, pt);
				_hoops_PAGR->center.z = _hoops_CPRA (mat->elements, pt);

				pt.x += c->radius;
				_hoops_PAGR->_hoops_GGHI.x = _hoops_HPRA (mat->elements, pt) - _hoops_PAGR->center.x;
				_hoops_PAGR->_hoops_GGHI.y = _hoops_IPRA (mat->elements, pt) - _hoops_PAGR->center.y;
				_hoops_PAGR->_hoops_GGHI.z = _hoops_CPRA (mat->elements, pt) - _hoops_PAGR->center.y;

				pt.x = c->center.x;
				pt.y += c->radius;
				_hoops_PAGR->_hoops_RGHI.x = _hoops_HPRA (mat->elements, pt) - _hoops_PAGR->center.x;
				_hoops_PAGR->_hoops_RGHI.y = _hoops_IPRA (mat->elements, pt) - _hoops_PAGR->center.y;
				_hoops_PAGR->_hoops_RGHI.z = _hoops_CPRA (mat->elements, pt) - _hoops_PAGR->center.y;

				_hoops_RIHI.a = _hoops_RIHI.b = _hoops_RIHI.d = 0;
				_hoops_RIHI.c = -1;
				HI_Compute_Transformed_Planes (1, &_hoops_RIHI, mat, &_hoops_PAGR->plane);
			}
			else {
				_hoops_GSPI const *e;
				e = (_hoops_GSPI *)a;
				_hoops_PAGR->center.x = _hoops_HPRA (mat->elements, e->center);
				_hoops_PAGR->center.y = _hoops_IPRA (mat->elements, e->center);
				_hoops_PAGR->center.z = _hoops_CPRA (mat->elements, e->center);
				HI_Compute_Transformed_Vectors (1, &e->_hoops_GGHI, (float *)&mat->elements[0], &_hoops_PAGR->_hoops_GGHI);
				HI_Compute_Transformed_Vectors (1, &e->_hoops_RGHI, (float *)&mat->elements[0], &_hoops_PAGR->_hoops_RGHI);
				HI_Compute_Transformed_Planes (1, &e->plane, mat, &_hoops_PAGR->plane);
			}
			_hoops_AHHI = (_hoops_GHHI alter *)_hoops_PAGR;
		} break;

		default: {
			HE_ERROR (HEC_ELLIPSE, HES_PROCEDURAL_ERROR,
					"Unexpected case in compute transformed arc");
		} break;

	}
	_hoops_AHHI->key = -1;
	_hoops_AHHI->_hoops_HIHI = 1;
	return _hoops_AHHI;
}


local void
_hoops_IIHI (
		Net_Rendition const & nr,
		Action_Mask mask,
		H3D_Display_List_Bin alter *_hoops_RRHA,
		H3D_Display_List_Bin_List alter *_hoops_CIHI,
		H3D_Display_List_Bin_List alter *_hoops_IAPI,
		H3D_Display_List_Bin_List alter *_hoops_SIHI,
		bool *_hoops_GCHI,
		bool *_hoops_RCHI)
{
	Display_Context const * dc = nr->_hoops_SRA;
	_hoops_GRGH const &	_hoops_ACHI = nr->_hoops_IRR;
	_hoops_IRHA *pair;
	_hoops_IRHA *_hoops_CHAI[_hoops_SPAI];
	_hoops_IRHA **_hoops_SHAI = _hoops_CHAI;
	int _hoops_GIAI = _hoops_SPAI;
	int _hoops_RIAI;
	int _hoops_AIAI = 0;
	int pass;
	Tristrip *ts = null;
	Polyedge *pe = null;
	Tristrip *_hoops_PCHI = null;
	Type type;
	Geometry const *g;
	int i, ii, _hoops_CCPI;
	int *_hoops_HCHI;
	_hoops_AAHI *_hoops_APHI;
	VList<_hoops_AAHI *> _hoops_ICHI(dc->memory_pool);
	_hoops_CCHI *_hoops_SCHI = null;
	struct _hoops_GSHI alter *_hoops_RSHI;
	int _hoops_ASHI = 0;
	bool _hoops_SAR = nr->_hoops_ARA->_hoops_APPI._hoops_SAR;
	bool _hoops_PSHI = false;
	_hoops_HRPA const *matrix;
	RGB const *_hoops_GPCP;
	_hoops_ACHR _hoops_HSHI;

	if (BIT (nr->transform_rendition->flags, _hoops_GRHH))
		_hoops_ASHI = nr->_hoops_RGP & (T_LIGHTS_FOR_FACES|T_LIGHTS_FOR_EDGES);

	*_hoops_GCHI = false;
	_hoops_SHAI[0] = _hoops_RRHA->_hoops_CRHA->PeekFirst();
	_hoops_RIAI = 1;

	_hoops_HSHI = nr->_hoops_RGP;
	if (!BIT (mask, _hoops_GCGI))
		_hoops_HSHI &= ~T_FACES;
	if (!BIT (mask, _hoops_ASRI))
		_hoops_HSHI &= ~T_ANY_POLYGON_EDGE;
	if (!ANYBIT (_hoops_HSHI, T_FACES|T_ANY_POLYGON_EDGE))
		return;

	for(pass = 0; pass < _hoops_RIAI; pass++) {
		if (ANYBIT(_hoops_HSHI, T_ANY_POLYGON_EDGE)) {
			ZALLOC (pe, Polyedge);
			_hoops_ICAI (pe);
		}
		if (BIT(_hoops_HSHI, T_FACES)) {
			ZALLOC (ts, Tristrip);
			_hoops_ICAI (ts);
			if (!pe) {
				ZALLOC (_hoops_PCHI, Tristrip);
				_hoops_ICAI (_hoops_PCHI);
			}
		}
		_hoops_RRHA->_hoops_CRHA->ResetCursor();
		for (;;) { // _hoops_IH _hoops_GRR _hoops_PSAI
			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			if (!pair)
				break;
			_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
			if (!_hoops_IPAI (pair, _hoops_SHAI[pass])) {
				if (pass == 0) {
					//_hoops_CAHA _hoops_GGSR _hoops_RPP _hoops_SR _hoops_RRP _hoops_IS _hoops_GGCR _hoops_IRS _hoops_CCAH _hoops_PCAI
					if (!_hoops_IPAI (pair, _hoops_SHAI[_hoops_AIAI])) {
						for (i = 0; i < _hoops_RIAI; i++) {
							if (_hoops_IPAI (pair, _hoops_SHAI[i])) {
								_hoops_AIAI = i;
								break;
							}
						}
						if (i == _hoops_RIAI) {
							if (_hoops_RIAI == _hoops_GIAI) {
								_hoops_IRHA **victim = _hoops_SHAI;
								_hoops_GIAI *= 2;
								ZALLOC_ARRAY (_hoops_SHAI, _hoops_GIAI, _hoops_IRHA *);
								_hoops_AIGA (victim, _hoops_RIAI, _hoops_IRHA *, _hoops_SHAI);
								if (victim != _hoops_CHAI)
									FREE_ARRAY (victim, _hoops_RIAI, _hoops_IRHA *);
							}
							_hoops_SHAI[_hoops_RIAI] = pair;
							_hoops_RIAI++;
						}
					}
				}
				continue;
			}
			g = (Geometry const *)pair->geo;
			for (;;) { // _hoops_IH _hoops_GRR _hoops_ISHI
				type = g->type;
				switch (type) {
					case _hoops_RCIP: {
						Polygon const *p = (Polygon const *)g;
						if (ts) {
							if (!BIT (p->_hoops_RRHH, _hoops_ARHH))
								HI_Find_Polygon_Plane ((Polygon alter *) p);
							POOL_ZALLOC (_hoops_APHI, _hoops_AAHI, dc->memory_pool);
							_hoops_CPHI (p, _hoops_APHI);
							if (_hoops_APHI->_hoops_GPHI != 0) {
								ts->point_count += p->count + _hoops_APHI->_hoops_CAHI;
								ts->total += _hoops_APHI->_hoops_GPHI;
								ts->_hoops_PHHA += _hoops_APHI->_hoops_GPHI / 3;
								_hoops_ICHI.AddLast (_hoops_APHI);
							}
							else {
								FREE (_hoops_APHI, _hoops_AAHI);
								_hoops_ICHI.AddLast (null);
							}
						}
						if (pe) {
							pe->point_count += p->count;
							pe->total += p->count + 1;
							pe->_hoops_PHHA++;
						}
					} break;

					case _hoops_GRCP:
					case _hoops_RRCP:
					case _hoops_SGCP:
					case _hoops_CGCP: {
						*_hoops_GCHI = true;

						if (_hoops_PSHI)
							_hoops_CSHI (g, type);

						// _hoops_AGSH _hoops_SR _hoops_ASCA _hoops_RSPH _hoops_CHPI?
						if ((type == _hoops_SGCP || type == _hoops_CGCP) && _hoops_PCHI) {
							// _hoops_PHIR _hoops_GGR _hoops_SPR _hoops_PCPI _hoops_RIR _hoops_HCPI. _hoops_SSHI _hoops_CI _hoops_GRS _hoops_GGII _hoops_SCH _hoops_IH _hoops_IHHH.
							// _hoops_RIAA _hoops_GIHA
							_hoops_PCHI->point_count += 4;

							// _hoops_RGII _hoops_PSPI - _hoops_AIAA _hoops_IH _hoops_RH _hoops_PCPI, _hoops_PGCR _hoops_IH _hoops_RH _hoops_AGII _hoops_IS _hoops_RH _hoops_SPS _hoops_PCPI
							_hoops_PCHI->total += 6;

							// _hoops_PGII _hoops_PHAP _hoops_CRGR _hoops_SPR _hoops_CGGR
							_hoops_PCHI->_hoops_PHHA = 1;
						}
						else if (!_hoops_SAR) {
							_hoops_GHHI const *a = (_hoops_GHHI const *)g;
							float start, end;
							int _hoops_HGII;

							if (!_hoops_SCHI)
								_hoops_SCHI = POOL_NEW(dc->memory_pool, _hoops_CCHI)(dc->memory_pool);
							POOL_ALLOC (_hoops_RSHI, struct _hoops_GSHI, dc->memory_pool);
							_hoops_RSHI->g = g;
							_hoops_RSHI->type = a->type;
							_hoops_RSHI->_hoops_IGII = _hoops_CCAI (pair->color, Color_EDGE);
							_hoops_RSHI->_hoops_CGII = _hoops_CCAI (pair->color, Color_FRONT);

							if (pair->_hoops_CPAI)
								a = _hoops_RHHI (a, &pair->_hoops_CPAI->matrix);
							_hoops_HGII = HD_Determine_Elliptical_Res (nr, a);
							if (BIT (a->_hoops_RRHH, _hoops_SHHI)) {
								Circular_Arc_Lite const *arc;

								arc = (Circular_Arc_Lite const *)a;
								start = arc->arc_start;
								end = arc->_hoops_PHHI;
							}
							else {
								Elliptical_Arc const *arc;

								arc = (Elliptical_Arc const *)a;
								start = arc->arc_start;
								end = arc->_hoops_PHHI;
								if (end < start)
									end += 1.0f;
							}
							_hoops_RSHI->_hoops_SGII = 10 + _hoops_HGII;
							POOL_ALLOC_ARRAY_CACHED (_hoops_RSHI->points, _hoops_RSHI->_hoops_SGII, Point, dc->memory_pool);
							_hoops_RSHI->count = HD_Generate_Elliptical_Points (nr, a, _hoops_HGII, _hoops_RSHI->points);
							ASSERT (_hoops_RSHI->count <= _hoops_RSHI->_hoops_SGII);
							if (_hoops_RSHI->count >= 2) {
								_hoops_SCHI->AddLast(_hoops_RSHI);
								if (ts) {
									ts->point_count += _hoops_RSHI->count;
									//_hoops_GRII _hoops_RRII _hoops_CHR _hoops_ARII _hoops_AGHH, _hoops_HIS _hoops_SSIA _hoops_HS
									//_hoops_IS _hoops_SHH _hoops_HSHA _hoops_GAR _hoops_IRS _hoops_PRII, _hoops_HRII _hoops_HSAR _hoops_GAR _hoops_IRS _hoops_IRII
									if (a->type == _hoops_RRCP)
										ts->total += 3 * (_hoops_RSHI->count - 2);
									else
										ts->total += _hoops_RSHI->count;
									ts->_hoops_PHHA++;
								}
								if (pe) {
									pe->point_count += _hoops_RSHI->count;
									pe->total += _hoops_RSHI->count + 1;
									pe->_hoops_PHHA++;
								}
								if (_hoops_ASHI)
									_hoops_RSHI->plane = a->plane;
							}
							else {
								FREE_ARRAY (_hoops_RSHI->points, _hoops_RSHI->_hoops_SGII, Point);
								FREE (_hoops_RSHI, struct _hoops_GSHI);
								_hoops_RSHI = null;
							}
							if (pair->_hoops_CPAI) {
								ASSERT (a != (_hoops_GHHI const *)g);
								_hoops_HPRH (a);
								a = null;
							}
						}
						else {
							_hoops_PSHI = true;
							_hoops_CSHI (g, type);
						}
					} break;
				}
				if (!g)
					break;
				if (pair->single)
					break;
				g = g->next;
				if (!g || g->type != type)
					break;
			}
		}
		*_hoops_RCHI = _hoops_PSHI;
		if (ts && ts->point_count == 0) {
			if (_hoops_ISAI (ts) == 0)
				HI_Free_Tristrip (ts);
			ts = null;
		}
		if (pe && pe->point_count == 0) {
			if (_hoops_ISAI (pe) == 0)
				HI_Free_Polyedge (pe);
			pe = null;
		}
		if (_hoops_PCHI && _hoops_PCHI->point_count == 0) {
			if (_hoops_ISAI (_hoops_PCHI) == 0)
				HI_Free_Tristrip (_hoops_PCHI);
			_hoops_PCHI = null;
		}
		if (!ts && !pe && !_hoops_PCHI)
			return;

		if (ts) {
			H3D_Display_List_Bin *		_hoops_CRII = null;
			_hoops_HHA const &	matr = nr->_hoops_IHA->_hoops_CHA;
			_hoops_HHA const &	_hoops_SIPI = nr->_hoops_IHA->_hoops_GIA;

			POOL_ALLOC_ARRAY_CACHED (ts->_hoops_AIHA, ts->total, int, dc->memory_pool);
			POOL_ZALLOC_ARRAY_CACHED (ts->face_indices, ts->total, int, dc->memory_pool);
			POOL_ALLOC_ARRAY_CACHED (ts->lengths, ts->_hoops_PHHA, int, dc->memory_pool);
			ts->_hoops_RAHH |= _hoops_AAHH;

			POOL_ALLOC_ARRAY_ALIGNED_CACHED (ts->points, ts->point_count, Point, 16, dc->memory_pool);
			ts->_hoops_RAHH |= _hoops_AIPI;

			if (_hoops_CCAI (_hoops_SHAI[pass]->color, Color_FRONT) != null) {
				POOL_ALLOC_ARRAY_CACHED (ts->_hoops_PCHA, ts->point_count, RGB, dc->memory_pool);
				ts->_hoops_RAHH |= _hoops_PIPI;
			}
			if (nr->_hoops_IRR->_hoops_SRI == _hoops_GAI &&
				BIT (nr->transform_rendition->heuristics, _hoops_IRI)) {
				ALLOC_ARRAY_CACHED (ts->_hoops_CCCP, ts->point_count, float);
				ts->_hoops_RAHH |= _hoops_HIPI;
			}
			ts->face_count = ts->_hoops_PHHA;
			if (BIT (_hoops_ASHI, T_LIGHTS_FOR_FACES)) {
				POOL_ALLOC_ARRAY_ALIGNED (ts->_hoops_PRHH, ts->face_count, _hoops_ARPA, 16, dc->memory_pool);
				ts->_hoops_RAHH |= _hoops_RCPI;
			}

			ts->point_count = 0;
			ts->total = 0;
			ts->_hoops_PHHA = 0;

			_hoops_RRHA->_hoops_CRHA->ResetCursor();
			_hoops_CCPI = 0;
			_hoops_HCHI = ts->face_indices;
			for (;;) {
				pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
				if (!pair)
					break;
				_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
				if (!_hoops_IPAI (pair, _hoops_SHAI[pass]))
					continue;
				g = (Geometry const *)pair->geo;
				if (pair->_hoops_CPAI)
					matrix = &pair->_hoops_CPAI->matrix;
				else
					matrix = null;
				_hoops_GPCP = _hoops_CCAI (pair->color, Color_FRONT);
				if (g->type == _hoops_RCIP) {
					for (;;) {
						Polygon const *p = (Polygon const *)g;
						if (matrix) {
							int ii;
							float _hoops_APCP;
							Point *_hoops_PCAP = ts->points + ts->point_count;
							for (ii = 0; ii < p->count; ii++) {
								_hoops_APCP = 1.0f / _hoops_PHCP (matrix->elements, p->points[ii]);
								_hoops_PCAP->x = _hoops_HPRA(matrix->elements, p->points[ii]) * _hoops_APCP;
								_hoops_PCAP->y = _hoops_IPRA(matrix->elements, p->points[ii]) * _hoops_APCP;
								_hoops_PCAP->z = _hoops_CPRA(matrix->elements, p->points[ii]) * _hoops_APCP;
								_hoops_PCAP++;
							}
						}
						else
							_hoops_AIGA (p->points, p->count, Point, &ts->points[ts->point_count]);
						if (_hoops_GPCP) {
							for (ii = 0; ii < p->count; ii++)
								ts->_hoops_PCHA[ts->point_count + ii] = *_hoops_GPCP;
						}
						if (ts->_hoops_CCCP) {
							ts->_hoops_CCCP[ts->point_count] = _hoops_SCCP(g->priority,1);
							for (ii = 1; ii < p->count; ii++)
								ts->_hoops_CCCP[ts->point_count + ii] = ts->_hoops_CCCP[ts->point_count];
 						}
						_hoops_APHI = _hoops_ICHI.RemoveFirst ();
						if (_hoops_APHI) {
							_hoops_SPHI (p, _hoops_APHI, ts->point_count, &ts->_hoops_AIHA[ts->total]);
							if (_hoops_APHI->_hoops_CAHI) {
								if (matrix) {
									float _hoops_APCP;
									Point *_hoops_PCAP = &ts->points[ts->point_count] + p->count;
									for (ii = 0; ii < _hoops_APHI->_hoops_CAHI; ii++) {
										_hoops_APCP = 1.0f / _hoops_PHCP (matrix->elements, _hoops_APHI->_hoops_PAHI[ii]);
										_hoops_PCAP->x = _hoops_HPRA(matrix->elements, _hoops_APHI->_hoops_PAHI[ii]) * _hoops_APCP;
										_hoops_PCAP->y = _hoops_IPRA(matrix->elements, _hoops_APHI->_hoops_PAHI[ii]) * _hoops_APCP;
										_hoops_PCAP->z = _hoops_CPRA(matrix->elements, _hoops_APHI->_hoops_PAHI[ii]) * _hoops_APCP;
										_hoops_PCAP++;
									}
								}
								else
									_hoops_AIGA (_hoops_APHI->_hoops_PAHI, _hoops_APHI->_hoops_CAHI, Point, &ts->points[ts->point_count] + p->count);
							}
							ts->point_count += p->count + _hoops_APHI->_hoops_CAHI;
							for (i = 0; i < _hoops_APHI->_hoops_GPHI / 3; i++)
								ts->lengths[ts->_hoops_PHHA + i] = 3;
							ts->_hoops_PHHA += _hoops_APHI->_hoops_GPHI / 3;
							ts->total += _hoops_APHI->_hoops_GPHI;
							FREE_ARRAY (_hoops_APHI->indices, _hoops_APHI->_hoops_SAHI, int);
							if (_hoops_APHI->_hoops_PAHI)
								FREE_ARRAY (_hoops_APHI->_hoops_PAHI, _hoops_APHI->_hoops_CAHI, Point);
							FREE (_hoops_APHI, _hoops_AAHI);
						}
						while (_hoops_HCHI < ts->face_indices + ts->total)
							*_hoops_HCHI++ = _hoops_CCPI;
						if (ts->_hoops_PRHH) {
							if (BIT(nr->transform_rendition->heuristics, _hoops_SASA))
								ts->_hoops_PRHH[_hoops_CCPI] = -p->plane;
							else
								ts->_hoops_PRHH[_hoops_CCPI] = p->plane;
						}
						_hoops_CCPI++;
						if (pair->single)
							break;
						g = g->next;
						if (!g || g->type != _hoops_RCIP)
							break;
					}
				}
			}
			/* _hoops_CHPI, _hoops_SRII, _hoops_GAII _hoops_PPR _hoops_RRII _hoops_AAPR _hoops_RAII _hoops_PPR _hoops_AAII _hoops_CIAA _hoops_PAII _hoops_HAII _hoops_HIGR */
			if (_hoops_SCHI && !_hoops_PSHI) {
				_hoops_SCHI->ResetCursor();
				while ((_hoops_RSHI = _hoops_SCHI->PeekCursor()) != null) {
					_hoops_AIGA (_hoops_RSHI->points, _hoops_RSHI->count, Point, &ts->points[ts->point_count]);
					if (_hoops_RSHI->type == _hoops_RRCP) {
						_hoops_CRHI (ts->point_count, _hoops_RSHI->count, &ts->_hoops_AIHA[ts->total]);
						ts->lengths[ts->_hoops_PHHA] = 3 * (_hoops_RSHI->count - 2);
						ts->total += ts->lengths[ts->_hoops_PHHA];
					}
					else {
						_hoops_RAHI (ts->point_count, _hoops_RSHI->count, &ts->_hoops_AIHA[ts->total]);
						ts->total += _hoops_RSHI->count;
						ts->lengths[ts->_hoops_PHHA] = _hoops_RSHI->count;
					}
					if (ts->_hoops_PRHH) {
						if (BIT(nr->transform_rendition->heuristics, _hoops_SASA))
							ts->_hoops_PRHH[_hoops_CCPI] = -_hoops_RSHI->plane;
						else
							ts->_hoops_PRHH[_hoops_CCPI] = _hoops_RSHI->plane;
					}
					if (_hoops_RSHI->_hoops_CGII) {
						ASSERT (ts->_hoops_PCHA != null);  //_hoops_IAII _hoops_RGR _hoops_PAHA'_hoops_RA _hoops_HS _hoops_CGI _hoops_CAII
						for (ii = 0; ii < _hoops_RSHI->count; ii++)
							ts->_hoops_PCHA[ts->point_count + ii] = *_hoops_RSHI->_hoops_CGII;
					}
					if (ts->_hoops_CCCP) {
						g = _hoops_RSHI->g;
						ts->_hoops_CCCP[ts->point_count] = _hoops_SCCP(g->priority,1);
						for (ii = 1; ii < _hoops_RSHI->count; ii++)
							ts->_hoops_CCCP[ts->point_count + ii] = ts->_hoops_CCCP[ts->point_count];
					}
					ts->point_count += _hoops_RSHI->count;
					_hoops_CCPI++;
					ts->_hoops_PHHA++;
					_hoops_SCHI->AdvanceCursor();
				}
			}

			pair = POOL_NEW(dc->memory_pool, _hoops_IRHA)(_hoops_RRHA->nr, ts, null, null);
			_hoops_ISAI (ts); //_hoops_SAII _hoops_HHHH _hoops_IS _hoops_RH _hoops_GPII
			ASSERT (ts->_hoops_HSAI != 0); //_hoops_PAH'_hoops_RA _hoops_SHH 0.  _hoops_CGH _hoops_HS _hoops_RPII _hoops_APII _hoops_GGR _hoops_RH _hoops_GPII _hoops_PPII

			if (matr->_hoops_IRIR < 1.0f || _hoops_SIPI->_hoops_IRIR < 1.0f) {
				if (nr->_hoops_CPP->_hoops_PRH.style != _hoops_GCPI)
					ts->_hoops_SRHA |= DL_HAS_TRANSPARENCY;
			}
			if (nr->_hoops_IHA->pattern != FP_SOLID)
				ts->_hoops_SRHA |= DL_PATTERN;
			if (BIT (nr->transform_rendition->flags, _hoops_GRHH) &&
				BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES))
				ts->_hoops_SRHA |= DL_LIGHTING;
			ts->_hoops_CARI |= _hoops_HPII;
			ts->_hoops_GSAI = _hoops_ACHI->_hoops_CSA & Rendo_TRISTRIP_MASK;

			_hoops_CRII = POOL_NEW(dc->memory_pool, H3D_Display_List_Bin)(dc->memory_pool);
			_hoops_CRII->_hoops_CRHA->AddFirst(pair);
			_hoops_CRII->nr = _hoops_RRHA->nr;
			_hoops_CRII->_hoops_IGGI.point_count = ts->point_count;
			_hoops_CRII->_hoops_IGGI._hoops_PHHA = ts->_hoops_PHHA;
			_hoops_CRII->_hoops_IGGI.total = ts->total;
			_hoops_CIHI->AddFirst (_hoops_CRII);
		}
		if (pe) {
			H3D_Display_List_Bin *_hoops_GRPI = null;
			_hoops_HHA const &	matr = nr->_hoops_RHP->_hoops_CHA;

			pe->lengths_allocated = pe->_hoops_PHHA;
			pe->_hoops_IPII = pe->_hoops_CPII = pe->total;
			POOL_ALLOC_ARRAY_CACHED (pe->lengths, pe->lengths_allocated, int, dc->memory_pool);
			POOL_ALLOC_ARRAY_CACHED (pe->_hoops_AIHA, pe->_hoops_IPII, int, dc->memory_pool);
			POOL_ALLOC_ARRAY_CACHED (pe->_hoops_SPII, pe->_hoops_CPII, int, dc->memory_pool);
			pe->_hoops_RAHH |= _hoops_AAHH;

			POOL_ALLOC_ARRAY_CACHED (pe->points, pe->point_count, Point, dc->memory_pool);
			pe->_hoops_RAHH |= _hoops_AIPI;

			if (_hoops_CCAI (_hoops_SHAI[pass]->color, Color_EDGE) != null) {
				POOL_ALLOC_ARRAY_CACHED (pe->_hoops_PCHA, pe->point_count, RGB, dc->memory_pool);
				pe->_hoops_RAHH |= _hoops_PIPI;
			}
			if (nr->_hoops_IRR->_hoops_SRI == _hoops_GAI &&
				BIT (nr->transform_rendition->heuristics, _hoops_IRI)) {
				ALLOC_ARRAY_CACHED (pe->_hoops_CCCP, pe->point_count, float);
				pe->_hoops_RAHH |= _hoops_HIPI;
			}
			if (BIT (_hoops_ASHI, T_LIGHTS_FOR_EDGES)) {
				POOL_ALLOC_ARRAY_CACHED (pe->_hoops_RSHA, pe->_hoops_PHHA, Vector, dc->memory_pool);
				pe->_hoops_RAHH |= _hoops_GHII;
			}

			pe->point_count = 0;
			pe->total = 0;
			pe->_hoops_PHHA = 0;

			_hoops_RRHA->_hoops_CRHA->ResetCursor();
			for (;;) {
				pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
				if (!pair)
					break;
				_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
				if (!_hoops_IPAI (pair, _hoops_SHAI[pass]))
					continue;
				g = (Geometry const *)pair->geo;
				if (g->type == _hoops_RCIP) {
					for (;;) {
						Polygon const *p = (Polygon const *)g;
						if (pair->_hoops_CPAI)
							matrix = &pair->_hoops_CPAI->matrix;
						else
							matrix = null;
						_hoops_GPCP = _hoops_CCAI (pair->color, Color_EDGE);
						if (matrix) {
							int ii;
							float _hoops_APCP;
							Point *_hoops_PCAP = pe->points + pe->point_count;
							for (ii = 0; ii < p->count; ii++) {
								_hoops_APCP = 1.0f / _hoops_PHCP (matrix->elements, p->points[ii]);
								_hoops_PCAP->x = _hoops_HPRA(matrix->elements, p->points[ii]) * _hoops_APCP;
								_hoops_PCAP->y = _hoops_IPRA(matrix->elements, p->points[ii]) * _hoops_APCP;
								_hoops_PCAP->z = _hoops_CPRA(matrix->elements, p->points[ii]) * _hoops_APCP;
								_hoops_PCAP++;
							}
						}
						else
							_hoops_AIGA (p->points, p->count, Point, &pe->points[pe->point_count]);
						if (_hoops_GPCP) {
							for (ii = 0; ii < p->count; ii++)
								pe->_hoops_PCHA[pe->point_count + ii] = *_hoops_GPCP;
						}
						if (pe->_hoops_CCCP) {
							pe->_hoops_CCCP[pe->point_count] = _hoops_SCCP(g->priority,0);
							for (ii = 1; ii < p->count; ii++)
								pe->_hoops_CCCP[pe->point_count + ii] = pe->_hoops_CCCP[pe->point_count];
						}
						for (i = 0; i < p->count; i++) {
							pe->_hoops_SPII[pe->total + i] = pe->_hoops_PHHA;
							pe->_hoops_AIHA[pe->total + i] = pe->point_count + i;
						}
						pe->_hoops_SPII[pe->total + i] = pe->_hoops_PHHA;
						pe->_hoops_AIHA[pe->total + i] = pe->point_count; //_hoops_GGGR _hoops_RH _hoops_HAPR
						if (pe->_hoops_RSHA)
							pe->_hoops_RSHA[pe->_hoops_PHHA] = p->plane;
						pe->lengths[pe->_hoops_PHHA] = p->count + 1;
						pe->point_count += p->count;
						pe->total += p->count + 1;
						pe->_hoops_PHHA++;
						if (pair->single)
							break;
						g = g->next;
						if (!g || g->type != _hoops_RCIP)
							break;
					}
				}
			}
			/* _hoops_CHPI, _hoops_SRII, _hoops_GAII _hoops_PPR _hoops_RRII _hoops_AAPR _hoops_RAII _hoops_PPR _hoops_AAII _hoops_CIAA _hoops_PAII _hoops_HAII _hoops_HIGR */
			if (_hoops_SCHI && !_hoops_PSHI) {
				_hoops_SCHI->ResetCursor();
				while ((_hoops_RSHI = _hoops_SCHI->PeekCursor()) != null) {
					_hoops_AIGA (_hoops_RSHI->points, _hoops_RSHI->count, Point, &pe->points[pe->point_count]);
					for (i = 0; i < _hoops_RSHI->count; i++) {
						pe->_hoops_SPII[pe->total + i] = pe->_hoops_PHHA;
						pe->_hoops_AIHA[pe->total + i] = pe->point_count + i;
					}
					pe->_hoops_SPII[pe->total + i] = pe->_hoops_PHHA;
					pe->_hoops_AIHA[pe->total + i] = pe->point_count; //_hoops_GGGR _hoops_RH _hoops_HAPR
					pe->lengths[pe->_hoops_PHHA] = _hoops_RSHI->count + 1;
					if (_hoops_RSHI->_hoops_IGII) {
						ASSERT (pe->_hoops_PCHA != null);  //_hoops_IAII _hoops_RGR _hoops_PAHA'_hoops_RA _hoops_HS _hoops_CGI _hoops_CAII
						for (ii = 0; ii < _hoops_RSHI->count; ii++)
							pe->_hoops_PCHA[pe->point_count + ii] = *_hoops_RSHI->_hoops_IGII;
					}
					if (pe->_hoops_CCCP) {
						g = _hoops_RSHI->g;
						pe->_hoops_CCCP[pe->point_count] = _hoops_SCCP(g->priority,0);
						for (ii = 1; ii < _hoops_RSHI->count; ii++)
							pe->_hoops_CCCP[pe->point_count + ii] = pe->_hoops_CCCP[pe->point_count];
					}
					pe->point_count += _hoops_RSHI->count;
					pe->total += _hoops_RSHI->count + 1;
					pe->_hoops_PHHA++;
					_hoops_SCHI->AdvanceCursor();
				}
			}

			pair = POOL_NEW(dc->memory_pool, _hoops_IRHA)(_hoops_RRHA->nr, pe, null, null);
			_hoops_ISAI (pe); //_hoops_SAII _hoops_HHHH _hoops_IS _hoops_RH _hoops_GPII
			ASSERT (pe->_hoops_HSAI != 0); //_hoops_PAH'_hoops_RA _hoops_SHH 0.  _hoops_CGH _hoops_HS _hoops_RPII _hoops_APII _hoops_GGR _hoops_RH _hoops_GPII _hoops_PPII

			pe->_hoops_SPHA = pe->_hoops_PHHA;
			if (matr->_hoops_IRIR < 1.0f &&
				nr->_hoops_CPP->_hoops_PRH.style != _hoops_GCPI)
				pe->_hoops_SRHA |= DL_HAS_TRANSPARENCY;
			if (BIT (nr->transform_rendition->flags, _hoops_GRHH) &&
				BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES))
				pe->_hoops_SRHA |= DL_LIGHTING;
			if (!BIT(nr->_hoops_RHP->line_style->flags,LSF_SOLID))
				pe->_hoops_SRHA |= DL_PATTERN;
			pe->_hoops_CARI |= _hoops_HPII;
			pe->_hoops_GSAI = _hoops_ACHI->_hoops_CSA & _hoops_RHII;

			_hoops_GRPI = POOL_NEW(dc->memory_pool, H3D_Display_List_Bin)(dc->memory_pool);
			_hoops_GRPI->_hoops_CRHA->AddFirst(pair);
			_hoops_GRPI->nr = _hoops_RRHA->nr;
			_hoops_GRPI->_hoops_IGGI.point_count = pe->point_count;
			_hoops_GRPI->_hoops_IGGI._hoops_PHHA = pe->_hoops_PHHA;
			_hoops_GRPI->_hoops_IGGI.total = pe->total;
			_hoops_IAPI->AddFirst (_hoops_GRPI);
		}
		if (_hoops_PCHI && !_hoops_PSHI) {
			H3D_Display_List_Bin *_hoops_AHII = null;
			int const _hoops_SCPI = _hoops_PCHI->point_count;
			bool _hoops_GIPI = (_hoops_CCAI (_hoops_SHAI[pass]->color, Color_FRONT) != null);

			_hoops_SHPI(nr, _hoops_PCHI, _hoops_GIPI);

			_hoops_RRHA->_hoops_CRHA->ResetCursor();
			_hoops_CCPI = 0;
			for (;;) {
				pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
				_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
				if (!pair)
					break;
				if (!_hoops_IPAI (pair, _hoops_SHAI[pass]))
					continue;
				g = (Geometry const *)pair->geo;
				type = g->type;
				if (type != _hoops_SGCP &&
					type != _hoops_CGCP)
					continue;
				if (pair->_hoops_CPAI)
					matrix = &pair->_hoops_CPAI->matrix;
				else
					matrix = null;
				_hoops_GPCP = _hoops_CCAI (pair->color, Color_FRONT);
				bool _hoops_ASPI = BIT(nr->transform_rendition->heuristics, _hoops_SASA);
				for (;;) {
					_hoops_GSPI const *e = (_hoops_GSPI const *)g;
					_hoops_ICPI (_hoops_PCHI, _hoops_CCPI++, _hoops_SCPI, e, matrix, _hoops_GPCP, true, _hoops_ASPI);
					if (pair->single)
						break;
					g = g->next;
					if (!g || g->type != type)
						break;
				}
			}

			pair = POOL_NEW(dc->memory_pool, _hoops_IRHA)(_hoops_RRHA->nr, _hoops_PCHI, null, null);
			_hoops_ISAI (_hoops_PCHI); //_hoops_SAII _hoops_HHHH _hoops_IS _hoops_RH _hoops_GPII
			ASSERT (_hoops_PCHI->_hoops_HSAI != 0); //_hoops_PAH'_hoops_RA _hoops_SHH 0.  _hoops_CGH _hoops_HS _hoops_RPII _hoops_APII _hoops_GGR _hoops_RH _hoops_GPII _hoops_PPII

			_hoops_AHII = POOL_NEW(dc->memory_pool, H3D_Display_List_Bin)(dc->memory_pool);
			_hoops_AHII->_hoops_CRHA->AddFirst(pair);
			_hoops_AHII->nr = _hoops_RRHA->nr;
			_hoops_AHII->_hoops_IGGI.point_count = _hoops_PCHI->point_count;
			_hoops_AHII->_hoops_IGGI._hoops_PHHA = _hoops_PCHI->_hoops_PHHA;
			_hoops_AHII->_hoops_IGGI.total = _hoops_PCHI->total;
			_hoops_SIHI->AddFirst (_hoops_AHII);
		}

		if (_hoops_SCHI) {
			while ((_hoops_RSHI = _hoops_SCHI->RemoveFirst()) != null) {
				FREE_ARRAY (_hoops_RSHI->points, _hoops_RSHI->_hoops_SGII, Point);
				FREE (_hoops_RSHI, struct _hoops_GSHI);
			}
		}
	}
	if (_hoops_SCHI)
		delete _hoops_SCHI;
	if (_hoops_SHAI != _hoops_CHAI)
		FREE_ARRAY (_hoops_SHAI, _hoops_GIAI, _hoops_IRHA *);
}


local bool
_hoops_PHII (
		Net_Rendition const &nr)
{
	bool _hoops_HHII = false, _hoops_IHII = false;

	if (BIT (nr->_hoops_RGP, T_FACES)) {
		_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
		_hoops_HHII = (
			_hoops_SIGA->_hoops_CHA &&
			_hoops_SIGA->_hoops_CHA->_hoops_IRIR < 1.0f);
		if (_hoops_SIGA->pattern == FP_USER_DEFINED) {
			//_hoops_CHII _hoops_PPR _hoops_SHII _hoops_HII _hoops_GIII
			if (_hoops_SIGA->_hoops_PGPH == null ||
				!_hoops_SIGA->_hoops_PGPH->stipple &&
				(_hoops_SIGA->_hoops_PGPH->height > 32 || 
				 _hoops_SIGA->_hoops_PGPH->width > 32 ||
				 _hoops_RIII(_hoops_SIGA->_hoops_PGPH->width) != _hoops_SIGA->_hoops_PGPH->width ||
				 _hoops_RIII(_hoops_SIGA->_hoops_PGPH->height) != _hoops_SIGA->_hoops_PGPH->height))
				return true;
		}
	}
	if (BIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE)) {
		_hoops_IHII = (
			nr->_hoops_RHP->_hoops_CHA &&
			nr->_hoops_RHP->_hoops_CHA->_hoops_IRIR < 1.0f);
		if (_hoops_GAPI (nr->_hoops_RHP->line_style))
			return true;
		if (nr->_hoops_RHP->weight > 1 &&
			BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP))
			return true;
	}

	if (_hoops_HHII || _hoops_IHII) {
		if (nr->_hoops_CPP->_hoops_PRH.style != _hoops_AIII &&
			nr->_hoops_CPP->_hoops_PRH.style != _hoops_GCPI &&
			nr->_hoops_CPP->_hoops_PRH._hoops_SRI != _hoops_PIII)
			return true;
	}

	return false;
}


local void
_hoops_HIII (
		Net_Rendition const & nr,
		_hoops_GACR alter *dl,
		bool _hoops_IHGI)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	H3DData *h3ddata = H3DD(dc);
	H3D_Display_List *_hoops_CHGI = null;

	if (dl)
		_hoops_CHGI = (H3D_Display_List *)dl->list;

	if (h3ddata->_hoops_CIGI->_hoops_IIII) {
		_hoops_IRHA *pair;
		float weight;
		_hoops_AIGI *list;
		bool _hoops_GIGI = false;

		list = h3ddata->_hoops_CIGI->_hoops_IIII;

		weight = nr->_hoops_RHP->weight;
		if (weight < 0)
			weight = (int)(HD_Compute_Generic_Size (nr, nr->_hoops_RHP->_hoops_PHP, nr->_hoops_RHP->_hoops_HHP,1.0f, false, 0, true)+0.5f);

		if (_hoops_PHII (h3ddata->_hoops_CIGI->nr)) {
			if (!_hoops_IHGI) {
				Geometry const *g;
				list->ResetCursor();
				while ((pair = list->PeekCursor()) != null) {
					list->AdvanceCursor();
					g = (Geometry const *)pair->geo;
					h3ddata->_hoops_AHPI = !pair->single;
					dc->_hoops_RAI = g;
					if (g->type == _hoops_RCIP)
						draw_3d_polygon (pair->nr, (Polygon const *)g);
					else
						_hoops_CIII (pair->nr, (Ellipse const *)g);
					h3ddata->_hoops_AHPI = false;

				}
			}
			if (dl)
				dl->action_mask |= _hoops_SIII;
		}
		else {
			H3D_Display_List_Bin *_hoops_RRHA;
			H3D_Display_List *_hoops_CRPI = null;
			Tristrip alter *ts;
			Polyedge alter *pe;
			H3D_Display_List_Bin_List *_hoops_CIHI = POOL_NEW(dc->memory_pool, H3D_Display_List_Bin_List)(dc->memory_pool);
			H3D_Display_List_Bin_List *_hoops_IAPI = POOL_NEW(dc->memory_pool, H3D_Display_List_Bin_List)(dc->memory_pool);
			H3D_Display_List_Bin_List *_hoops_SIHI = POOL_NEW(dc->memory_pool, H3D_Display_List_Bin_List)(dc->memory_pool);
			H3D_Display_List_Bin *_hoops_CRII = null;
			H3D_Display_List_Bin *_hoops_GRPI = null;
			H3D_Display_List_Bin *_hoops_AHII = null;
			bool _hoops_GCII = false;
			bool _hoops_PSHI = false;
			Action_Mask mask = _hoops_RAPI;


			if (!dl ||
				BIT (dl->action_mask, _hoops_ACIP) ||
				!BIT (_hoops_CHGI->item._hoops_ACGI.flags, H3D_SEGDL_BLESSED_SEGMENT))
				_hoops_GIGI = true;

			_hoops_RRHA = POOL_NEW(dc->memory_pool, H3D_Display_List_Bin)(dc->memory_pool);
			_hoops_RRHA->nr = h3ddata->_hoops_CIGI->nr;
			delete _hoops_RRHA->_hoops_CRHA;
			_hoops_RRHA->_hoops_CRHA = list;
			if (_hoops_CHGI &&
				_hoops_CHGI->item._hoops_ACGI._hoops_RCII) {
				_hoops_CRPI = _hoops_CHGI->item._hoops_ACGI._hoops_RCII->PeekFirst();
				if (_hoops_CRPI) {
					if (_hoops_CRPI->item._hoops_ACII._hoops_PCII != null ||
						_hoops_CRPI->item._hoops_ACII._hoops_HCII != null) {
						mask &= ~_hoops_GCGI;
						if (!_hoops_IHGI &&
							BIT (nr->_hoops_RGP, T_FACES))
							_hoops_ICII (nr, _hoops_CHGI->item._hoops_ACGI._hoops_RCII, T_FACES);
					}
					if (_hoops_CRPI->item._hoops_ACII._hoops_GHPI != null) {
						mask &= ~_hoops_ASRI;
						if (!_hoops_IHGI &&
							BIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE)) {
							h3ddata->_hoops_AIP = BIT(dl->_hoops_PRRI, _hoops_PGAI);
							_hoops_ICII (nr, _hoops_CHGI->item._hoops_ACGI._hoops_RCII, T_ANY_POLYGON_EDGE);
							h3ddata->_hoops_AIP = false;
						}
					}
				}
			}
			_hoops_IIHI (_hoops_RRHA->nr, mask, _hoops_RRHA, _hoops_CIHI, _hoops_IAPI, _hoops_SIHI, &_hoops_GCII, &_hoops_PSHI);

			if (!_hoops_GIGI &&
				_hoops_HCRI(h3ddata, 0) ||
				!h3ddata->_hoops_CIGI->_hoops_SIGI &&
				!BIT (dl->action_mask, _hoops_ACIP)) {
				if (!_hoops_CRPI) {
					ZALLOC (_hoops_CRPI, H3D_Display_List);
					_hoops_CRPI->type = H3D_DL_SEGMENT_POLYGON;
					_hoops_CRPI->time_stamp = HOOPS_WORLD->_hoops_GPPI;
					_hoops_CRPI->item._hoops_ACII._hoops_GCII = _hoops_GCII;
					if (_hoops_GCII) {
						_hoops_CRPI->item._hoops_ACII._hoops_SAR = nr->_hoops_ARA->_hoops_APPI._hoops_SAR;
						_hoops_CRPI->item._hoops_ACII._hoops_PPPI = nr->_hoops_ARA->_hoops_APPI._hoops_PPPI;
						_hoops_CRPI->item._hoops_ACII._hoops_HPPI = nr->_hoops_ARA->_hoops_APPI._hoops_HPPI;
						_hoops_CRPI->item._hoops_ACII._hoops_IPPI = nr->_hoops_ARA->_hoops_APPI._hoops_IPPI;
						_hoops_CRPI->item._hoops_ACII._hoops_CPPI = nr->_hoops_ARA->_hoops_APPI._hoops_CPPI;
						_hoops_CRPI->item._hoops_ACII._hoops_SPPI = nr->_hoops_ARA->_hoops_APPI._hoops_SPPI;
					}
				}
				_hoops_CIHI->ResetCursor();
				while ((_hoops_CRII = _hoops_CIHI->PeekCursor()) != null) {
					_hoops_CIHI->AdvanceCursor();
					if (_hoops_CRII->_hoops_CRHA->Count()) {
						_hoops_RRRI (_hoops_CRII->nr, null, _hoops_CRII);
						if (!_hoops_CRPI->item._hoops_ACII._hoops_PCII)
							_hoops_CRPI->item._hoops_ACII._hoops_PCII = POOL_NEW(dc->memory_pool, H3D_Display_List_List)(dc->memory_pool);
						_hoops_CRPI->item._hoops_ACII._hoops_PCII->AddFirst (_hoops_CRII->odl);
						_hoops_CRII->odl = null;
					}
				}
				_hoops_IAPI->ResetCursor();
				while ((_hoops_GRPI = _hoops_IAPI->PeekCursor()) != null) {
					_hoops_IAPI->AdvanceCursor();
					if (_hoops_GRPI->_hoops_CRHA->Count()) {
						really_draw_3d_polyedge (_hoops_GRPI->nr, null, _hoops_GRPI->nr->_hoops_RHP, _hoops_GRPI);
						if (!_hoops_CRPI->item._hoops_ACII._hoops_GHPI)
							_hoops_CRPI->item._hoops_ACII._hoops_GHPI = POOL_NEW(dc->memory_pool, H3D_Display_List_List)(dc->memory_pool);
						_hoops_CRPI->item._hoops_ACII._hoops_GHPI->AddFirst (_hoops_GRPI->odl);
						if (h3ddata->_hoops_IHP)
							dl->_hoops_PRRI |= _hoops_PGAI;
						_hoops_GRPI->odl = null;
					}
				}
				_hoops_SIHI->ResetCursor();
				while ((_hoops_AHII = _hoops_SIHI->PeekCursor()) != null) {
					_hoops_SIHI->AdvanceCursor();
					if (_hoops_AHII->_hoops_CRHA->Count()) {
						_hoops_RRRI (_hoops_AHII->nr, null, _hoops_AHII);
						if (!_hoops_CRPI->item._hoops_ACII._hoops_HCII)
							_hoops_CRPI->item._hoops_ACII._hoops_HCII = POOL_NEW(dc->memory_pool, H3D_Display_List_List)(dc->memory_pool);
						_hoops_CRPI->item._hoops_ACII._hoops_HCII->AddFirst (_hoops_AHII->odl);
						_hoops_AHII->odl = null;
					}
				}

				if (_hoops_CRPI->item._hoops_ACII._hoops_PCII ||
					_hoops_CRPI->item._hoops_ACII._hoops_GHPI ||
					_hoops_CRPI->item._hoops_ACII._hoops_HCII) {
					if (nr->_hoops_IRR->_hoops_SRI != _hoops_GAI ||
						!BIT (nr->transform_rendition->heuristics, _hoops_IRI))
						dl->_hoops_PRRI &= ~_hoops_HRRI;
					if (!_hoops_CHGI->item._hoops_ACGI._hoops_RCII)
						_hoops_CHGI->item._hoops_ACGI._hoops_RCII = POOL_NEW(dc->memory_pool, H3D_Display_List_List)(dc->memory_pool);
					if (_hoops_CRPI != _hoops_CHGI->item._hoops_ACGI._hoops_RCII->PeekFirst())
						_hoops_CHGI->item._hoops_ACGI._hoops_RCII->AddFirst(_hoops_CRPI);
				}
				else
					FREE (_hoops_CRPI, H3D_Display_List);
				_hoops_CRPI = null;
			}
			else
				_hoops_GIGI = true;

			if (_hoops_GIGI) {
				_hoops_ISGI const *_hoops_CSGI = dc->_hoops_SPA->modelling_matrix;
				_hoops_SSGI const *_hoops_GGRI = dc->_hoops_SPA->color;
				/* _hoops_PGSA _hoops_CCII _hoops_GGR _hoops_HGAI _hoops_CCH */
				dc->_hoops_SPA->modelling_matrix = null;
				dc->_hoops_SPA->color = null;
				if (!_hoops_IHGI) {
					_hoops_CIHI->ResetCursor();
					while ((_hoops_CRII = _hoops_CIHI->PeekCursor()) != null) {
						_hoops_CIHI->AdvanceCursor();
						_hoops_CRII->_hoops_CRHA->ResetCursor();
						while ((pair = _hoops_CRII->_hoops_CRHA->PeekCursor()) != null) {
							ts = (Tristrip *)pair->geo;
							ts->_hoops_SRHA |= _hoops_SRHH;
							_hoops_RRRI (_hoops_CRII->nr, ts, null);
							_hoops_CRII->_hoops_CRHA->AdvanceCursor();
						}
					}
					_hoops_IAPI->ResetCursor();
					while ((_hoops_GRPI = _hoops_IAPI->PeekCursor()) != null) {
						_hoops_IAPI->AdvanceCursor();
						_hoops_GRPI->_hoops_CRHA->ResetCursor();
						while ((pair = _hoops_GRPI->_hoops_CRHA->PeekCursor()) != null) {
							pe = (Polyedge *)pair->geo;
							pe->_hoops_SRHA |= _hoops_SRHH;
							really_draw_3d_polyedge (_hoops_GRPI->nr, pe, _hoops_GRPI->nr->_hoops_RHP, null);
							_hoops_GRPI->_hoops_CRHA->AdvanceCursor();
						}
					}
					_hoops_SIHI->ResetCursor();
					while ((_hoops_AHII = _hoops_SIHI->PeekCursor()) != null) {
						_hoops_SIHI->AdvanceCursor();
						_hoops_AHII->_hoops_CRHA->ResetCursor();
						while ((pair = _hoops_AHII->_hoops_CRHA->PeekCursor()) != null) {
							ts = (Tristrip *)pair->geo;
							ts->_hoops_SRHA |= _hoops_SRHH;
							_hoops_RRRI (_hoops_AHII->nr, ts, null);
							_hoops_AHII->_hoops_CRHA->AdvanceCursor();
						}
					}
				}
				if (dl)
					dl->action_mask |= _hoops_ACIP;
				dc->_hoops_SPA->modelling_matrix = _hoops_CSGI;
				dc->_hoops_SPA->color = _hoops_GGRI;
			}

			if (_hoops_PSHI) {
				Geometry const *g;

				_hoops_RRHA->_hoops_CRHA->ResetCursor();
				while ((pair = _hoops_RRHA->_hoops_CRHA->PeekCursor()) != null) {
					_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
					g = (Geometry const *)pair->geo;
					if (g->type == _hoops_RCIP)
						continue;
					h3ddata->_hoops_AHPI = !pair->single;
					dc->_hoops_RAI = g;
					_hoops_CIII (pair->nr, (Ellipse const *)g);
					h3ddata->_hoops_AHPI = false;
				}
				if (dl)
					dl->action_mask |= _hoops_ARCP;
			}

			_hoops_CIHI->ResetCursor();
			while ((_hoops_CRII = _hoops_CIHI->PeekCursor()) != null) {
				_hoops_CIHI->AdvanceCursor();
				while ((pair = _hoops_CRII->_hoops_CRHA->RemoveFirst()) != null) {
					delete pair;
				}
				_hoops_CRII->odl = null;
				delete _hoops_CRII;
			}
			delete _hoops_CIHI;

			_hoops_IAPI->ResetCursor();
			while ((_hoops_GRPI = _hoops_IAPI->PeekCursor()) != null) {
				_hoops_IAPI->AdvanceCursor();
				while ((pair = _hoops_GRPI->_hoops_CRHA->RemoveFirst()) != null) {
					delete pair;
				}
				_hoops_GRPI->odl = null;
				delete _hoops_GRPI;
			}
			delete _hoops_IAPI;

			_hoops_SIHI->ResetCursor();
			while ((_hoops_AHII = _hoops_SIHI->PeekCursor()) != null) {
				_hoops_SIHI->AdvanceCursor();
				while ((pair = _hoops_AHII->_hoops_CRHA->RemoveFirst()) != null) {
					delete pair;
				}
				_hoops_AHII->odl = null;
				delete _hoops_AHII;
			}
			delete _hoops_SIHI;
			ASSERT (_hoops_RRHA->_hoops_CRHA == h3ddata->_hoops_CIGI->_hoops_IIII);
			_hoops_RRHA->_hoops_CRHA = null;
			delete _hoops_RRHA;
			_hoops_RRHA = null;
		}

		/* _hoops_SP _hoops_GH _hoops_IARI _hoops_HIGR _hoops_PPR _hoops_AGPI _hoops_PGPI/_hoops_SCII _hoops_IGPI */
		while ((pair = list->RemoveFirst()) != null) {
			delete pair;
		}
		delete h3ddata->_hoops_CIGI->_hoops_IIII;
		h3ddata->_hoops_CIGI->_hoops_IIII = 0;
	}
	else {
		_hoops_ACHR _hoops_RGP = nr->_hoops_RGP;

		if (_hoops_CHGI &&
			_hoops_CHGI->item._hoops_ACGI._hoops_RCII &&
			ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE)) {
			h3ddata->_hoops_AIP = BIT(dl->_hoops_PRRI, _hoops_PGAI);
			_hoops_ICII (nr, _hoops_CHGI->item._hoops_ACGI._hoops_RCII, _hoops_RGP);
			h3ddata->_hoops_AIP = false;
		}
	}
}


local int
_hoops_GSII (Geometry const *_hoops_RSII, bool single)
{
	Geometry const *g = _hoops_RSII;
	int _hoops_ASII = 0;
	int _hoops_PSII = 0;
	int type;

	while (g) {
		type = g->type;
		switch (type) {
			case _hoops_PIIP: {
				do {
					_hoops_ASII += 2;
					_hoops_PSII++;
					g = g->next;
					if (single)
						break;
				} while (g && g->type == type);
			} break;

			case _hoops_HIIP: {
				type = _hoops_IIIP;		// _hoops_HSII _hoops_SAHR _hoops_GAR _hoops_ISII
			} _hoops_HHHI;

			case _hoops_IIIP: {
				Polyline const *ptr;
				do {
					ptr = (Polyline const *)g;
					_hoops_ASII += Abs(ptr->count);
					_hoops_PSII++;
					g = g->next;
					if (single)
						break;
				} while (g && g->type == type);
			} break;

			case _hoops_GIIP:
			case _hoops_RIIP:
			case _hoops_CHIP:{
				do {
					_hoops_ASII += 256;
					_hoops_PSII++;
					g = g->next;
					if (single)
						break;
				} while (g && g->type == type);
			} break;

			default:
				_hoops_CSHI (g, type);
		}
		if (single)
			break;
	}
	return 12 * _hoops_ASII + 12 * _hoops_PSII;
}


void _hoops_CSII (
		Net_Rendition const & nr,
		H3D_Display_List alter *odl)
{
	Display_Context const * dc = nr->_hoops_SRA;
	H3DData *h3ddata = H3DD(nr->_hoops_SRA);
	Tristrip *_hoops_SSII;

	POOL_ZALLOC (_hoops_SSII, Tristrip, dc->memory_pool);
	POOL_ZALLOC (_hoops_SSII->_hoops_GAHA, _hoops_GACR, dc->memory_pool);

	_hoops_ICAI(_hoops_SSII);
	_hoops_SSII->_hoops_GAHA->_hoops_GGCI = -1;

	/* _hoops_RAP _hoops_GH _hoops_RH _hoops_CRHH _hoops_PPR _hoops_RGCI _hoops_AIRI _hoops_HIGR */
	_hoops_SSII->_hoops_GAHA->list = (_hoops_AGCI*)odl;
	odl->_hoops_PPAH = _hoops_SSII->_hoops_GAHA;
	_hoops_SSII->_hoops_GAHA->_hoops_GHRI = nr->_hoops_SRA->_hoops_GHRI;
	_hoops_SSII->_hoops_GAHA->_hoops_PRRI = odl->item.geometry._hoops_CARI;
	_hoops_SSII->_hoops_GSAI = odl->item.geometry._hoops_GSAI;
	//_hoops_PGCI->_hoops_HGCI = _hoops_CSRI->_hoops_IGCI._hoops_CPAP._hoops_CGCI;
	_hoops_SSII->_hoops_SRHA = odl->item.geometry._hoops_SRHA;
	_hoops_SSII->_hoops_CARI = odl->item.geometry._hoops_CARI;
	_hoops_SSII->face_attributes.flags = odl->item.geometry._hoops_IRRI;
	_hoops_SSII->_hoops_SRHA |= DL_DO_NOT_RECOMPILE;
	_hoops_SSII->total = odl->item.geometry._hoops_IGGI.total;
	_hoops_SSII->_hoops_PHHA = odl->item.geometry._hoops_IGGI._hoops_PHHA;
	_hoops_SSII->point_count = odl->item.geometry._hoops_IGGI.point_count;


	ASSERT(_hoops_SSII->_hoops_GAHA->list);	//_hoops_SR _hoops_SGCI'_hoops_RA _hoops_SHH _hoops_ARI _hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_CPHP _hoops_IS _hoops_GRCI
	/* _hoops_CHPR _hoops_IS "_hoops_PGSA 3d _hoops_CRHH" */
	if (BIT (odl->item.geometry._hoops_SRHA, _hoops_GGIA))
		h3ddata->_hoops_RRCI->_hoops_ARCI (nr, _hoops_SSII);
	else
		h3ddata->_hoops_RRCI->draw_3d_tristrip(nr, _hoops_SSII);
	ASSERT(_hoops_SSII->_hoops_GAHA->list);	//_hoops_SCH _hoops_HRGR _hoops_CHHH _hoops_IH _hoops_PRCI _hoops_IS _hoops_HRCI _hoops_IRCI

	/* _hoops_CRCI */
	FREE(_hoops_SSII->_hoops_GAHA, _hoops_GACR);
	FREE(_hoops_SSII, Tristrip);
	odl->_hoops_PPAH = null;
}

void _hoops_SRCI (
		Net_Rendition const &nr,
		H3D_Display_List alter *odl,
		Line_Rendition const &_hoops_GHP)
{
	Display_Context const * dc = nr->_hoops_SRA;

	Polyedge *_hoops_GACI;
	POOL_ZALLOC (_hoops_GACI, Polyedge, dc->memory_pool);
	POOL_ZALLOC (_hoops_GACI->_hoops_GAHA, _hoops_GACR, dc->memory_pool);

	_hoops_ICAI(_hoops_GACI);
	_hoops_GACI->_hoops_GAHA->_hoops_GGCI = -1;

	/* _hoops_RAP _hoops_GH _hoops_RH _hoops_ACRI _hoops_PPR _hoops_RGCI _hoops_AIRI _hoops_HIGR */
	_hoops_GACI->_hoops_GAHA->list = (_hoops_AGCI*)odl;
	_hoops_GACI->_hoops_GAHA->list->_hoops_PPAH = _hoops_GACI->_hoops_GAHA;
	_hoops_GACI->_hoops_GAHA->_hoops_GHRI = nr->_hoops_SRA->_hoops_GHRI;
	_hoops_GACI->_hoops_GAHA->_hoops_PRRI = odl->item.geometry._hoops_CARI;
	_hoops_GACI->_hoops_GSAI = odl->item.geometry._hoops_GSAI;
	_hoops_GACI->_hoops_SRHA = odl->item.geometry._hoops_SRHA;
	_hoops_GACI->_hoops_CARI = odl->item.geometry._hoops_CARI;
	_hoops_GACI->_hoops_PPGI.flags = odl->item.geometry._hoops_IRRI;
	_hoops_GACI->_hoops_SRHA |= DL_DO_NOT_RECOMPILE;
	_hoops_GACI->total = odl->item.geometry._hoops_IGGI.total;
	_hoops_GACI->point_count = odl->item.geometry._hoops_IGGI.point_count;
	_hoops_GACI->_hoops_PHHA = odl->item.geometry._hoops_IGGI._hoops_PHHA;

	ASSERT(_hoops_GACI->_hoops_GAHA->list);	//_hoops_PAHA'_hoops_RA _hoops_HGCR _hoops_ARI _hoops_CCA _hoops_ISAP _hoops_IS _hoops_RIH _hoops_GGR
	really_draw_3d_polyedge (nr, _hoops_GACI, _hoops_GHP, null);
	ASSERT(_hoops_GACI->_hoops_GAHA->list);	//_hoops_SCH _hoops_HRGR _hoops_CHHH _hoops_IH _hoops_PRCI _hoops_IS _hoops_HRCI _hoops_IRCI

	/* _hoops_CRCI */
	FREE (_hoops_GACI->_hoops_GAHA, _hoops_GACR);
	FREE (_hoops_GACI, Polyedge);
	odl->_hoops_PPAH = null;
}


#define _hoops_RACI 10
void _hoops_HARI (
		Net_Rendition const & nr,
		H3D_Display_List_List alter *_hoops_AACI,
		bool _hoops_PACI,
		bool _hoops_HACI)
{
	H3D_Display_List *odl;
	bool draw;
	int count = _hoops_RACI;

	_hoops_AACI->ResetCursor();
	while ((odl = _hoops_AACI->PeekCursor()) != null) {
		if (BIT (odl->item.geometry._hoops_IRRI, _hoops_IAGI))
			draw = _hoops_PACI;
		else
			draw = _hoops_HACI;
		if (draw)
			_hoops_CSII (nr, odl);
		_hoops_AACI->AdvanceCursor();
		if (--count == 0) {
			Display_Context const * dc = nr->_hoops_SRA;
			if (_hoops_IACI(dc))
				break;
			count = _hoops_RACI;
		}
	}
}


void _hoops_CGAI (
		Net_Rendition const & nr,
		H3D_Display_List alter *_hoops_CHGI,
		bool _hoops_PACI,
		bool _hoops_HACI)
{
	H3D_Display_List_List alter *_hoops_AACI = null;
	H3D_Display_List *odl;
	bool draw;
	int i;

	for (i = 0; i < 3; i++) {
		if (i == 0)
			_hoops_AACI = _hoops_CHGI->item._hoops_ACGI._hoops_RGAI;
		else if (i == 1)
			_hoops_AACI = _hoops_CHGI->item._hoops_ACGI._hoops_GGAI;
		else if (i == 2)
			_hoops_AACI = _hoops_CHGI->item._hoops_ACGI._hoops_AGAI;
		if (!_hoops_AACI)
			continue;
		_hoops_AACI->ResetCursor();
		while ((odl = _hoops_AACI->PeekCursor()) != null) {
			if (BIT (odl->item.geometry._hoops_IRRI, _hoops_APGI))
				draw = _hoops_PACI;
			else
				draw = _hoops_HACI;
			if (draw)
				_hoops_SRCI (nr, odl, nr->_hoops_RHP);
			_hoops_AACI->AdvanceCursor();
		}
	}
}


void _hoops_CGPI (
		Net_Rendition const & inr,
		_hoops_ACHR type,
		H3D_Display_List_List alter *_hoops_AACI)
{
	H3DData *h3ddata = H3DD(inr->_hoops_SRA);
	H3D_Display_List *odl;

	Net_Rendition nr = inr;
	if (type != T_VERTICES) {
		nr->_hoops_SCP = nr->_hoops_GSP;
	}

	/* _hoops_CACI _hoops_RHIR _hoops_RH _hoops_CCGI _hoops_HIGR _hoops_PPR _hoops_PGSA _hoops_HCR _hoops_IIGR _hoops_CAPR! */
	_hoops_AACI->ResetCursor();
	while ((odl = _hoops_AACI->PeekCursor()) != null) {
		/* _hoops_GCRR _hoops_IRS _hoops_RSPH _hoops_CRHH */
		Polymarker *_hoops_IRAI;

		ZALLOC (_hoops_IRAI, Polymarker);
		ZALLOC (_hoops_IRAI->_hoops_GAHA, _hoops_GACR);

		_hoops_ICAI (_hoops_IRAI);

		/* _hoops_RAP _hoops_GH _hoops_RH _hoops_CRHH _hoops_PPR _hoops_RGCI _hoops_AIRI _hoops_HIGR */
		_hoops_IRAI->_hoops_GAHA->list = (_hoops_AGCI*)odl;
		odl->_hoops_PPAH = _hoops_IRAI->_hoops_GAHA;
		_hoops_IRAI->_hoops_GAHA->_hoops_GHRI = nr->_hoops_SRA->_hoops_GHRI;
		_hoops_IRAI->_hoops_GAHA->_hoops_AGRI = odl->item.geometry._hoops_SRHA;
		_hoops_IRAI->_hoops_GAHA->_hoops_PRRI = odl->item.geometry._hoops_CARI;
		_hoops_IRAI->_hoops_GAHA->_hoops_GGCI = -1;

		_hoops_IRAI->_hoops_GSAI = odl->item.geometry._hoops_GSAI;
		_hoops_IRAI->_hoops_SRHA = odl->item.geometry._hoops_SRHA;
		_hoops_IRAI->_hoops_CARI = odl->item.geometry._hoops_CARI;
		_hoops_IRAI->_hoops_SACI.flags = odl->item.geometry._hoops_IRRI;
		_hoops_IRAI->_hoops_SRHA |= DL_DO_NOT_RECOMPILE;
		_hoops_IRAI->point_count = odl->item.geometry._hoops_IGGI.point_count;
		_hoops_IRAI->length = _hoops_IRAI->point_count;

		/* _hoops_CHPR _hoops_IS "_hoops_PGSA 3d _hoops_PAAI" */
		ASSERT (_hoops_IRAI->_hoops_GAHA->list);	//_hoops_SR _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_ARI
		_hoops_GPCI (nr, _hoops_IRAI, nr->_hoops_SCP, null);
		ASSERT (_hoops_IRAI->_hoops_GAHA->list);	//_hoops_SCH _hoops_HRGR _hoops_CHHH _hoops_IH _hoops_PRCI _hoops_IS _hoops_HRCI _hoops_IRCI

		/* _hoops_CRCI */
		FREE (_hoops_IRAI->_hoops_GAHA, _hoops_GACR);
		FREE (_hoops_IRAI, Polymarker);
		odl->_hoops_PPAH = null;
		_hoops_AACI->AdvanceCursor();
		if (ANYBIT (odl->item.geometry._hoops_SRHA, DL_COLORS_BY_FINDEX|_hoops_GGIA|DL_VCOLORED_TRISTRIP)) {
			h3ddata->_hoops_RPCI = _hoops_CCC;
		}
	}
}

void _hoops_ICII (
		Net_Rendition const & nr,
		H3D_Display_List_List alter *_hoops_AACI,
		_hoops_ACHR _hoops_RGP)
{
	H3D_Display_List *odl;
	H3D_Display_List *_hoops_APCI;
	H3D_Display_List_List *list;

	if (BIT (_hoops_RGP, T_FACES)) {
		_hoops_AACI->ResetCursor();
		while ((odl = _hoops_AACI->PeekCursor()) != null) {
			ASSERT (odl->type == H3D_DL_SEGMENT_POLYGON);
			if (odl->item._hoops_ACII._hoops_PCII) {
				list = odl->item._hoops_ACII._hoops_PCII;
				list->ResetCursor();
				while ((_hoops_APCI = list->PeekCursor()) != null) {
					list->AdvanceCursor();
					_hoops_CSII (nr, _hoops_APCI);
				}
			}
			if (odl->item._hoops_ACII._hoops_HCII) {
				list = odl->item._hoops_ACII._hoops_HCII;
				list->ResetCursor();
				while ((_hoops_APCI = list->PeekCursor()) != null) {
					list->AdvanceCursor();
					_hoops_CSII (nr, _hoops_APCI);
				}
			}
			_hoops_AACI->AdvanceCursor();
		}
	}
	if (BIT (_hoops_RGP, T_ANY_POLYGON_EDGE)) {
		_hoops_AACI->ResetCursor();
		while ((odl = _hoops_AACI->PeekCursor()) != null) {
			ASSERT (odl->type == H3D_DL_SEGMENT_POLYGON);
			if (odl->item._hoops_ACII._hoops_GHPI) {
				list = odl->item._hoops_ACII._hoops_GHPI;
				list->ResetCursor();
				while ((_hoops_APCI = list->PeekCursor()) != null) {
					list->AdvanceCursor();
					_hoops_SRCI (nr, _hoops_APCI, nr->_hoops_RHP);
				}
			}
			_hoops_AACI->AdvanceCursor();
		}
	}
}


void _hoops_HHPI (
		Net_Rendition const & nr,
		H3D_Display_List_List alter *_hoops_AACI)
{
	H3D_Display_List *odl;
	H3D_Display_List *_hoops_APCI;
	H3D_Display_List_List *list;

	_hoops_AACI->ResetCursor();
	while ((odl = _hoops_AACI->PeekCursor()) != null) {
		ASSERT (odl->type == H3D_DL_SEGMENT_POLYLINE);
		if (odl->item._hoops_RPPI._hoops_GHPI) {
			list = odl->item._hoops_RPPI._hoops_GHPI;
			list->ResetCursor();
			while ((_hoops_APCI = list->PeekCursor()) != null) {
				list->AdvanceCursor();
				_hoops_SRCI (nr, _hoops_APCI, nr->_hoops_AHP);
			}
		}
		_hoops_AACI->AdvanceCursor();
	}
}


void _hoops_PPCI (
		Net_Rendition const & nr,
		_hoops_GACR *dl)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	H3DData *h3ddata = H3DD(nr->_hoops_SRA);
	H3D_Display_List *_hoops_CHGI = (H3D_Display_List *) dl->list;
	_hoops_ACHR _hoops_RGP = nr->_hoops_RGP;
	_hoops_ACHR _hoops_HPCI = dc->_hoops_IPCI->mask;
	bool _hoops_RIRI, _hoops_GIRI;

	h3ddata->_hoops_AAI = _hoops_CHGI;

	_hoops_RIRI = BIT (_hoops_CHGI->item._hoops_ACGI.flags, H3D_SEGDL_HAS_EXPLICIT_VISIBLE);

	if (_hoops_CHGI->type != H3D_DL_SEGMENT_TREE) {
		/* _hoops_IH _hoops_HA, _hoops_RGR _hoops_API _hoops_PAH _hoops_RGAR _hoops_RGHH _hoops_CAGH _hoops_PAPA _hoops_AIRI _hoops_CPCI */
		_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
			"Unknown display list type in dx9_driver::execute_display_list");
		return;
	}

	if (BIT (_hoops_RGP, T_FACES)) {
		if (BIT (dl->_hoops_PRRI, _hoops_GCRI)) {
			_hoops_RGP |= T_EDGES;
			dc->_hoops_IPCI->mask |= (_hoops_ASRI|_hoops_GHCI);
		}
		if (BIT (dl->_hoops_PRRI, _hoops_RCRI)) {
			_hoops_RGP |= _hoops_GPA;
			dc->_hoops_IPCI->mask |= (_hoops_RSRI);
		}
	}
	if (BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_EDGES)) {
		_hoops_RGP |= _hoops_GPA;
		if (_hoops_CPGI (nr->_hoops_IRR)) {
			_hoops_RGP &= ~(T_FACES);
			_hoops_RGP |= nr->_hoops_ARA->_hoops_CICP._hoops_RGP & (T_FACES);
		}
	}

	//_hoops_RH _hoops_HSPR _hoops_RIS _hoops_RHCI _hoops_HHH _hoops_AHCI _hoops_PHCI _hoops_CCA _hoops_HHCI _hoops_IHCI [#10623]
	if (dc->_hoops_IPCI->_hoops_CHCI != segment_render &&
		dc->_hoops_IPCI->_hoops_CHCI != HD_Standard_Render) {
		(*dc->_hoops_IPCI->_hoops_CHCI) (nr, (Geometry *)dl, dc->_hoops_IPCI->mask, true);
		return;
	}

	if (_hoops_CHGI->item._hoops_ACGI._hoops_ARRI) {
		_hoops_GIRI = BIT (_hoops_RGP, T_FACES);
		if (_hoops_GIRI || _hoops_RIRI) {
			_hoops_HARI (nr,
				_hoops_CHGI->item._hoops_ACGI._hoops_ARRI,
				_hoops_RIRI, _hoops_GIRI);
		}
	}

	if (ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE)) {
		if (_hoops_CHGI->item._hoops_ACGI._hoops_RCII) {
			h3ddata->_hoops_AIP = BIT(dl->_hoops_PRRI, _hoops_PGAI);
			_hoops_ICII (nr, _hoops_CHGI->item._hoops_ACGI._hoops_RCII, _hoops_RGP);
			h3ddata->_hoops_AIP = false;
		}
	}

	if (dc->_hoops_SHCI() != _hoops_GICI &&
		dc->_hoops_SHCI() != _hoops_RICI &&
		!h3ddata->_hoops_PI.mode) {

		h3ddata->_hoops_AIP = BIT(dl->_hoops_PRRI, _hoops_PGAI);
		if (_hoops_CHGI->item._hoops_ACGI._hoops_AGAI ||
			_hoops_CHGI->item._hoops_ACGI._hoops_GGAI ||
			_hoops_CHGI->item._hoops_ACGI._hoops_RGAI) {
			_hoops_GIRI =
				ANYBIT (_hoops_RGP, _hoops_PSRI) ||
				BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_EDGES);
			if (_hoops_GIRI || _hoops_RIRI) {
				_hoops_CGAI (nr, _hoops_CHGI, _hoops_RIRI, _hoops_GIRI);
			}
		}

		if (BIT (_hoops_RGP, T_LINES) &&
			_hoops_CHGI->item._hoops_ACGI._hoops_CAPI && !h3ddata->_hoops_PI.mode) {
			_hoops_HHPI (nr, _hoops_CHGI->item._hoops_ACGI._hoops_CAPI);
		}

		if (BIT (_hoops_RGP, T_VERTICES) &&
			_hoops_CHGI->item._hoops_ACGI._hoops_RAAI && !h3ddata->_hoops_PI.mode) {
			_hoops_CGPI (nr, T_VERTICES, _hoops_CHGI->item._hoops_ACGI._hoops_RAAI);
		}

		if (BIT (_hoops_RGP, T_MARKERS) &&
			_hoops_CHGI->item._hoops_ACGI._hoops_GAAI && !h3ddata->_hoops_PI.mode) {
			_hoops_CGPI (nr, T_MARKERS, _hoops_CHGI->item._hoops_ACGI._hoops_GAAI);
		}
		h3ddata->_hoops_AIP = false;
	}
	dc->_hoops_IPCI->mask = _hoops_HPCI;

	h3ddata->_hoops_AAI = null;
} //_hoops_RSGR _hoops_API '_hoops_GRCI _hoops_AIRI _hoops_HIGR'


void _hoops_AICI(
		Net_Rendition const  &nr,
		_hoops_GACR **_hoops_PICI,
		unsigned Integer32 *mask,
		unsigned Integer32 *_hoops_HICI)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	H3DData *h3ddata = H3DD (dc);
	_hoops_GACR *dl;
	H3D_Display_List *_hoops_CHGI;
	bool _hoops_RACR;
	int _hoops_HSHI;
	int _hoops_IICI = 0, _hoops_CICI = 0;

	_hoops_HSHI = nr->_hoops_RGP;
	if (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_EDGES){
		_hoops_HSHI |= _hoops_GPA;
		if (_hoops_CPGI (nr->_hoops_IRR)) {
			_hoops_HSHI &= ~(T_FACES);
			_hoops_HSHI |= nr->_hoops_ARA->_hoops_CICP._hoops_RGP & (T_FACES);
		}
	}
	if (ANYBIT (_hoops_HSHI, _hoops_GPA|T_EDGES|T_LINES)) {
		if (nr->_hoops_IRR->_hoops_SRI == _hoops_SICI &&
			BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_RCCI)) {
			Line_Style const &	_hoops_ACCI = nr->_hoops_ASIR->_hoops_GCCI.line_style;

			/* _hoops_PCCI _hoops_HII _hoops_HCCI _hoops_GGR _hoops_ICCI._hoops_GGHR */
			if (!BIT(_hoops_ACCI->flags, LSF_SOLID))
			{
				if (!BIT(_hoops_ACCI->flags, LSF_BITS16) || /* _hoops_PSP _hoops_CCCI 16-_hoops_IGRH _hoops_SCCI */
					BIT(nr->_hoops_AHP->flags, _hoops_SRPI) ||
					ANYBIT(_hoops_ACCI->flags, LSF_COMPLEX_ANYBITS))
					*mask = (_hoops_IGAI|_hoops_IRPI);
			}
		}
	}

	_hoops_RACR = _hoops_AACR(nr, &(*_hoops_PICI), &dl, &_hoops_CHGI, H3D_DL_SEGMENT_TREE);
	if (_hoops_RACR && (h3ddata->_hoops_PI.mode || h3ddata->_hoops_CHSP.mode))
		return;
	if (!_hoops_RACR) {
		if (!_hoops_GSCI (nr, dl, _hoops_CHGI, null, &_hoops_IICI, &_hoops_CICI))
			*mask = _hoops_RSCI;
	}
	if (_hoops_HICI) {
		*_hoops_HICI = 0;
		if (BIT (_hoops_IICI, T_FACES))
			*_hoops_HICI |= _hoops_PGRI|_hoops_ACIP;
		if (ANYBIT (_hoops_IICI, _hoops_PSRI))
			*_hoops_HICI |= _hoops_IGAI;
		if (ANYBIT (_hoops_IICI, T_ANY_POLYGON_EDGE))
			*_hoops_HICI |= _hoops_ACIP;
		if (BIT (_hoops_IICI, T_LINES))
			*_hoops_HICI |= _hoops_IRPI;
		if (ANYBIT (_hoops_IICI, T_MARKERS|T_VERTICES))
			*_hoops_HICI |= _hoops_HCIP|_hoops_RGPI;
	}

	if (_hoops_RACR)
		*mask = _hoops_RSCI;
}


void _hoops_ASCI(
		H3DData *h3ddata)
{
	_hoops_IRHA *pair;
	int i;
	_hoops_AIGI *_hoops_PSCI[8];

	if (h3ddata->_hoops_CIGI->_hoops_RCGI) {
		_hoops_PSCI[0] = h3ddata->_hoops_CIGI->_hoops_RCGI;
		while ((pair = _hoops_PSCI[0]->RemoveFirst()) != null) {
			Tristrip alter *ts = (Tristrip alter *)pair->geo;
			ts->_hoops_CARI &= ~_hoops_SARI;
			delete pair;
		}
		delete _hoops_PSCI[0];
		h3ddata->_hoops_CIGI->_hoops_RCGI = null;
	}

	_hoops_PSCI[0] = h3ddata->_hoops_CIGI->_hoops_IIRI;
	h3ddata->_hoops_CIGI->_hoops_IIRI = null;
	_hoops_PSCI[1] = h3ddata->_hoops_CIGI->_hoops_CIRI;
	h3ddata->_hoops_CIGI->_hoops_CIRI = null;
	_hoops_PSCI[2] = h3ddata->_hoops_CIGI->_hoops_SIRI;
	h3ddata->_hoops_CIGI->_hoops_SIRI = null;
	for (i = 0; i < 3; i++) {
		if (_hoops_PSCI[i]) {
			while ((pair = _hoops_PSCI[i]->RemoveFirst()) != null) {
				Polyedge alter *pe = (Polyedge alter *)pair->geo;
				pe->_hoops_CARI &= ~_hoops_SARI;
				delete pair;
			}
			delete _hoops_PSCI[i];
		}
	}

	_hoops_PSCI[0] = h3ddata->_hoops_CIGI->_hoops_HRPI;
	h3ddata->_hoops_CIGI->_hoops_HRPI = null;
	_hoops_PSCI[1] = h3ddata->_hoops_CIGI->_hoops_IIII;
	h3ddata->_hoops_CIGI->_hoops_IIII = null;
	for (i = 0; i < 2; i++) {
		if (_hoops_PSCI[i]) {
			while ((pair = _hoops_PSCI[i]->RemoveFirst()) != null) {
				delete pair;
			}
			delete _hoops_PSCI[i];
		}
	}

	/* _hoops_HSCI _hoops_RH _hoops_IARI */
	h3ddata->_hoops_CIGI->nr.release();
	FREE (h3ddata->_hoops_CIGI, H3D_Collector);
	h3ddata->_hoops_CIGI = null;
	h3ddata->_hoops_ISCI = 0;
}


local Action_Mask
_hoops_CSCI (_hoops_GACR const *dl)
{
	H3D_Display_List const *odl = (H3D_Display_List const *)dl->list;
	Action_Mask mask;

	mask = dl->action_mask;
	if (odl->item._hoops_ACGI._hoops_ARRI)
		mask |= _hoops_PGRI;
	if (odl->item._hoops_ACGI._hoops_AGAI)
		mask |= _hoops_IGAI;
	if (odl->item._hoops_ACGI._hoops_GGAI)
		mask |= _hoops_PSIP;
	if (odl->item._hoops_ACGI._hoops_RGAI)
		mask |= (_hoops_SSCI | _hoops_IGAI);
	if (odl->item._hoops_ACGI._hoops_CAPI)
		mask |= _hoops_IRPI;
	if (odl->item._hoops_ACGI._hoops_RCII)
		mask |= _hoops_SIII;
	if (odl->item._hoops_ACGI._hoops_RAAI)
		mask |= _hoops_RGPI;
	if (odl->item._hoops_ACGI._hoops_GAAI)
		mask |= _hoops_HCIP;
	return mask;
}


bool _hoops_GGSI(
		Net_Rendition const &		nr,
		_hoops_GACR **				_hoops_PICI,
		unsigned Integer32 *		mask,
		bool						_hoops_IHGI)
{
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	H3DData *					h3ddata = H3DD (dc);
	Action_Mask					_hoops_RGSI = 0;
	//_hoops_AGSI _hoops_PGSI _hoops_CHR _hoops_HAR _hoops_ARP _hoops_GGR _hoops_RH _hoops_HGSI _hoops_ACPH _hoops_PISH _hoops_HIH _hoops_IGSI _hoops_HPGR _hoops_RH _hoops_PRCA _hoops_PSCH _hoops_HIS _hoops_SGS 
	// _hoops_CGSI _hoops_PII _hoops_SGSI _hoops_HGCR _hoops_IRS _hoops_GRSI _hoops_HPGR _hoops_CAPR.
	Action_Mask					_hoops_RRSI = 0; 
	int							_hoops_IICI = 0, _hoops_CICI = 0, _hoops_HSHI;
	_hoops_GACR *				dl;
	H3D_Display_List *			_hoops_CHGI;
	bool 						_hoops_RACR;
	bool 						_hoops_ARSI;

	if (BIT(nr->_hoops_ARA->_hoops_PRSI.options, _hoops_HRSI) ||
		BIT(dc->flags, _hoops_IRSI)) {
		*mask = _hoops_RAPI;
		return false;
	}
	if (ANYBIT (nr->current, _hoops_CRSI | _hoops_SRSI) &&
		(dc->_hoops_IPCI->_hoops_CHCI != segment_render)) {
		*mask = _hoops_RAPI;
		return false;
	}

	_hoops_HSHI = nr->_hoops_RGP;
	if (!BIT(nr->transform_rendition->flags,_hoops_GRHH))
		_hoops_HSHI &= ~(T_LIGHTS_FOR_FACES | T_LIGHTS_FOR_EDGES | T_LIGHTS_FOR_MARKERS);
	if (BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_EDGES)) {
		_hoops_HSHI |= _hoops_GPA;
		if (_hoops_CPGI (_hoops_RRGH)) {
			_hoops_HSHI &= ~(T_FACES);
			_hoops_HSHI |= nr->_hoops_ARA->_hoops_CICP._hoops_RGP & (T_FACES);
		}
	}

	if (_hoops_RRGH->_hoops_GAHA == Display_List_SEGMENT) {
		_hoops_RACR = _hoops_AACR(nr, &(*_hoops_PICI), &dl, &_hoops_CHGI, H3D_DL_SEGMENT_TREE);
		if (h3ddata->_hoops_CIGI)
			_hoops_ASCI (h3ddata);
		if (!_hoops_RACR &&
			!h3ddata->_hoops_PI.mode &&
			!h3ddata->_hoops_CHSP.mode) {
			if (!_hoops_GSCI (nr, dl, _hoops_CHGI, &_hoops_HSHI, &_hoops_IICI, &_hoops_CICI)) {
				if (_hoops_CHGI->item._hoops_ACGI._hoops_ARRI ||
					_hoops_CHGI->item._hoops_ACGI._hoops_AGAI ||
					_hoops_CHGI->item._hoops_ACGI._hoops_GGAI ||
					_hoops_CHGI->item._hoops_ACGI._hoops_RGAI ||
					_hoops_CHGI->item._hoops_ACGI._hoops_RAAI ||
					_hoops_CHGI->item._hoops_ACGI._hoops_GAAI ||
					_hoops_CHGI->item._hoops_ACGI._hoops_CAPI ||
					_hoops_CHGI->item._hoops_ACGI._hoops_RCII) {
					if (dl->_hoops_GASI) {
						//_hoops_HCGI'_hoops_GRI _hoops_HRCI _hoops_PAII _hoops_RASI, _hoops_HIH _hoops_HAR _hoops_GPHP _hoops_RPHP
						if (!BIT (dl->_hoops_PRRI, _hoops_AASI)) {
							*dl->_hoops_GASI->backlink = dl->_hoops_GASI->next;
							_hoops_HPRH (dl->_hoops_GASI); //_hoops_GRS _hoops_PASI _hoops_AASA _hoops_RHIR _hoops_IS _hoops_HASI
						}
					}
					*dl->backlink = dl->next;
					_hoops_HPRH (dl); //_hoops_GRS _hoops_PASI _hoops_AASA _hoops_RHIR _hoops_IS _hoops_HASI
					_hoops_RACR = _hoops_AACR(nr, &(*_hoops_PICI), &dl, &_hoops_CHGI, H3D_DL_SEGMENT_TREE);
					ASSERT (_hoops_RACR);
				}
				else {
					_hoops_CHGI->item._hoops_ACGI._hoops_RGP = 0;
					_hoops_RACR = true;
				}
			}
			else {
				/* _hoops_IASI _hoops_CASI _hoops_GH _hoops_IIGR _hoops_AIRI _hoops_HIGR _hoops_GPGA _hoops_GPP _hoops_PGAP _hoops_SASI _hoops_SIH (_hoops_RPP _hoops_GII) _hoops_AGRP */
				H3D_Display_List *_hoops_GPSI;
				H3D_Display_List_List *list;

				if (dl->_hoops_GASI &&
					!BIT (dl->_hoops_PRRI, _hoops_AASI)) {
					/* _hoops_SR _hoops_HS _hoops_IRS _hoops_HCH _hoops_ICH _hoops_AIRI _hoops_HIGR _hoops_SGS _hoops_HRGR _hoops_IRS _hoops_RPSI _hoops_IIGR _hoops_RGR _hoops_HCGI,
					 * _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RPP _hoops_SCH _hoops_APSI _hoops_IHHH _hoops_IS _hoops_PPSI _hoops_PA _hoops_GPP _hoops_RH
					 * _hoops_SGSI _hoops_HIGR _hoops_IH _hoops_SCH _hoops_IS _hoops_HPSI _hoops_CCA */
					int _hoops_IPSI = 0, _hoops_CPSI = 0;
					if (!_hoops_GSCI (nr, dl->_hoops_GASI,
							(H3D_Display_List *)dl->_hoops_GASI->list, null, &_hoops_IPSI, &_hoops_CPSI)) {
						if (dl->_hoops_GASI->_hoops_GSAI == DL_FLAG_INVALID) {
							ASSERT (0); //_hoops_HRGR _hoops_RGR _hoops_CRAA _hoops_PRGI _hoops_SSRR _hoops_GII _hoops_RRI?

							*dl->backlink = dl->next;
							_hoops_HPRH (dl); //_hoops_GRS _hoops_PASI _hoops_AASA _hoops_RHIR _hoops_IS _hoops_HASI
							_hoops_RACR = _hoops_AACR (nr, &(*_hoops_PICI), &dl, &_hoops_CHGI, H3D_DL_SEGMENT_TREE);
							ASSERT (_hoops_RACR);
						}
						else
							dl->action_mask |= dl->_hoops_GASI->action_mask;
					}
					_hoops_IICI |= _hoops_IPSI;
					_hoops_CICI |= _hoops_CPSI;
				}

				if (BIT (_hoops_CHGI->item._hoops_ACGI.flags, H3D_SEGDL_HAS_EXPLICIT_VISIBLE))
					_hoops_HSHI |= (T_EDGES|T_FACES|T_VERTICES);

				if (!BIT (_hoops_HSHI, T_FACES))
					_hoops_IICI &= ~T_LIGHTS_FOR_FACES;
				if (!ANYBIT (_hoops_HSHI, _hoops_PSRI)) 
					_hoops_IICI &= ~T_LIGHTS_FOR_EDGES;
				if (!BIT (_hoops_HSHI, T_VERTICES))
					_hoops_IICI &= ~T_LIGHTS_FOR_MARKERS;

				if (BIT (_hoops_HSHI, T_FACES) &&
					ANYBIT (_hoops_IICI, T_FACES|T_LIGHTS_FOR_FACES)) {
					list = _hoops_CHGI->item._hoops_ACGI._hoops_ARRI;
					if (list) {
						list->ResetCursor ();
						while((_hoops_GPSI = list->PeekCursor()) != null) {
							if (!BIT (_hoops_GPSI->item.geometry._hoops_IRRI, _hoops_IAGI)) {
								list->RemoveAtCursor();
								_hoops_SPSI ((_hoops_AGCI *)_hoops_GPSI);
							}
							else
								list->AdvanceCursor();
						}
					}
					dl->action_mask |= _hoops_PGRI;
					_hoops_CHGI->item._hoops_ACGI._hoops_RGP &= ~(T_FACES|T_LIGHTS_FOR_FACES);
				}
				/* _hoops_IH _hoops_SPPR, _hoops_RPP _hoops_GHSI (_hoops_HIH _hoops_HAR _hoops_HCR) _hoops_RHSI _hoops_PAR _hoops_PA _hoops_RRAI */
				if (ANYBIT (_hoops_HSHI, _hoops_PSRI) &&
					(ANYBIT (_hoops_CICI, _hoops_PSRI) ||
					 ANYBIT (_hoops_IICI, _hoops_PSRI|T_LIGHTS_FOR_EDGES))) {
					list = _hoops_CHGI->item._hoops_ACGI._hoops_AGAI;
					if (list) {
						list->ResetCursor ();
						while((_hoops_GPSI = list->PeekCursor()) != null) {
							if (!BIT (_hoops_GPSI->item.geometry._hoops_IRRI, _hoops_APGI)) {
								list->RemoveAtCursor();
								_hoops_SPSI ((_hoops_AGCI *)_hoops_GPSI);
							}
							else
								list->AdvanceCursor();
						}
					}
					list = _hoops_CHGI->item._hoops_ACGI._hoops_GGAI;
					if (list) {
						list->ResetCursor ();
						while((_hoops_GPSI = list->PeekCursor()) != null) {
							if (!BIT (_hoops_GPSI->item.geometry._hoops_IRRI, _hoops_APGI)) {
								list->RemoveAtCursor();
								_hoops_SPSI ((_hoops_AGCI *)_hoops_GPSI);
							}
							else
								list->AdvanceCursor();
						}
					}
					dl->action_mask |= _hoops_IGAI;
					_hoops_CHGI->item._hoops_ACGI._hoops_RGP &= ~(_hoops_PSRI|T_LIGHTS_FOR_EDGES);
				}
				if (BIT (_hoops_HSHI, _hoops_GPA) &&
					BIT (_hoops_IICI, _hoops_GPA)) {
					list = _hoops_CHGI->item._hoops_ACGI._hoops_RGAI;
					if (list) {
						while ((_hoops_GPSI = list->RemoveFirst()) != null)
							_hoops_SPSI ((_hoops_AGCI *)_hoops_GPSI);
					}
					dl->action_mask |= _hoops_RSRI;
					_hoops_CHGI->item._hoops_ACGI._hoops_RGP &= ~(_hoops_GPA);
				}
				if (BIT (_hoops_HSHI, T_LINES) &&
					ANYBIT (_hoops_IICI, T_LINES)) {
					list = _hoops_CHGI->item._hoops_ACGI._hoops_CAPI;
					if (list) {
						while((_hoops_GPSI = list->RemoveFirst()) != null)
							_hoops_SPSI ((_hoops_AGCI *)_hoops_GPSI);
					}
					dl->action_mask |= _hoops_IRPI;
					_hoops_CHGI->item._hoops_ACGI._hoops_RGP &= ~(T_LINES);
				}
				if (BIT (_hoops_HSHI, T_VERTICES) &&
					ANYBIT (_hoops_IICI, T_VERTICES|T_LIGHTS_FOR_MARKERS)) {
					list = _hoops_CHGI->item._hoops_ACGI._hoops_RAAI;
					if (list) {
						while ((_hoops_GPSI = list->RemoveFirst()) != null)
							HD_Queue_Destroy_List (_hoops_GPSI, true);
					}
					dl->action_mask |= _hoops_RGPI;
					_hoops_CHGI->item._hoops_ACGI._hoops_RGP &= ~(T_VERTICES|T_LIGHTS_FOR_MARKERS);
				}
				if (BIT (_hoops_HSHI, T_MARKERS) &&
					ANYBIT (_hoops_IICI, T_MARKERS)) {
					list = _hoops_CHGI->item._hoops_ACGI._hoops_GAAI;
					if (list) {
						while ((_hoops_GPSI = list->RemoveFirst()) != null)
							HD_Queue_Destroy_List (_hoops_GPSI, true);
					}
					dl->action_mask |= _hoops_HCIP;
					_hoops_CHGI->item._hoops_ACGI._hoops_RGP &= ~(T_MARKERS);
				}
			}
		}
		if (_hoops_RACR) {
			_hoops_RGSI = _hoops_RAPI;
			_hoops_CHGI->item._hoops_ACGI.flags = 0;
			if (dc->_hoops_AHSI != null && BIT (dc->_hoops_AHSI->segment->_hoops_PHSI, _hoops_HHSI))
				_hoops_CHGI->item._hoops_ACGI.flags |= H3D_SEGDL_HAS_EXPLICIT_VISIBLE;
		}
		if (BIT (_hoops_CHGI->item._hoops_ACGI.flags, H3D_SEGDL_HAS_EXPLICIT_VISIBLE))
			_hoops_HSHI |= (T_EDGES|T_FACES|T_VERTICES);

		if (BIT (dl->_hoops_PRRI, _hoops_IHSI)) {
			dl->_hoops_PRRI &= ~_hoops_IHSI;
			_hoops_RGSI = _hoops_RAPI;
		}

		if (BIT(dc->flags, _hoops_CHSI)) {
			_hoops_RGSI &= (_hoops_RSCI|_hoops_SHSI);
			dl->_hoops_PRRI |= _hoops_IHSI;
		}
		_hoops_RGSI |= dl->action_mask;
		_hoops_RRSI = 0;

		if (dl->_hoops_GASI &&
			!BIT (dl->_hoops_PRRI, _hoops_AASI) &&
			nr->_hoops_CPP->_hoops_PRH._hoops_SRI != _hoops_PIII) {
			/* _hoops_ISCP _hoops_RPSI _hoops_HRGR _hoops_GISI _hoops_HGCR _hoops_RISI, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS _hoops_AISI _hoops_PISI _hoops_CPAP _hoops_ISHP
			 * _hoops_HISI _hoops_IHSP _hoops_IISI _hoops_HRGR _hoops_CISI */
			_hoops_RGSI |= _hoops_CSCI (dl->_hoops_GASI);
		}

		if (!h3ddata->_hoops_PI.mode &&
			!h3ddata->_hoops_CHSP.mode)
			dl->_hoops_GSAI = 0;

		if (BIT (_hoops_HSHI, T_FACES)) {
			if (BIT (dl->_hoops_PRRI, _hoops_GCRI))
				_hoops_HSHI |= T_EDGES;
		}
		if (!BIT(nr->transform_rendition->flags, _hoops_GRHH))
			_hoops_HSHI &= ~(T_LIGHTS_FOR_FACES | T_LIGHTS_FOR_EDGES | T_LIGHTS_FOR_MARKERS);
		if (!BIT (_hoops_HSHI, T_FACES)) {
			_hoops_HSHI &= ~T_LIGHTS_FOR_FACES;
			_hoops_RGSI &= ~_hoops_PGRI;
			if (!ANYBIT (_hoops_HSHI, T_ANY_POLYGON_EDGE))
				_hoops_RGSI &= ~_hoops_ACIP;
		}
		else if (BIT (_hoops_IICI, T_FACES))
			_hoops_RGSI |= _hoops_PGRI;
		if (ANYBIT (_hoops_IICI, T_ANY_POLYGON_EDGE|T_FACES))
			_hoops_RGSI |= _hoops_ACIP;
		if (!ANYBIT (_hoops_HSHI, _hoops_PSRI)) {
			_hoops_HSHI &= ~T_LIGHTS_FOR_EDGES;
			_hoops_RGSI &= ~(_hoops_ASRI|_hoops_GHCI);
		}
		else if (ANYBIT (_hoops_IICI, _hoops_PSRI))
			_hoops_RGSI |= _hoops_ASRI|_hoops_GHCI;
		if (!BIT (_hoops_HSHI, T_LINES)) {
			if (!BIT (_hoops_HSHI, T_TEXT) ||
				nr->_hoops_SISI->transform != FT_FULL)
				_hoops_RGSI &= ~_hoops_IRPI;
		}
		else if (BIT (_hoops_IICI, T_LINES))
			_hoops_RGSI |= _hoops_IRPI;
		if (!BIT (_hoops_HSHI, T_VERTICES)) {
			_hoops_HSHI &= ~T_LIGHTS_FOR_MARKERS;
			_hoops_RGSI &= ~_hoops_RGPI;
		}
		else if (BIT (_hoops_IICI, T_VERTICES))
			_hoops_RGSI |= _hoops_RGPI;
		if (!BIT (_hoops_HSHI, T_MARKERS)) {
			_hoops_RGSI &= ~_hoops_HCIP;
		}
		else if (BIT (_hoops_IICI, T_MARKERS))
			_hoops_RGSI |= _hoops_HCIP;

		_hoops_ARSI = (
					ANYBIT (nr->_hoops_RGP, T_INTERIOR_SILHOUETTE_EDGES | _hoops_GCSI) &&
					!BIT (nr->_hoops_RGP, T_GENERIC_EDGES));
		if (_hoops_ARSI) {
			_hoops_RGSI |= _hoops_RCSI|_hoops_ACSI;
		}
		else {
			_hoops_RGSI &= ~(_hoops_RCSI|_hoops_ACSI);
			if (!ANYBIT (_hoops_RGSI, _hoops_PCSI) &&
				!ALLBITS (_hoops_RRGH->_hoops_CSA, _hoops_HCSI))
				_hoops_RGSI &= ~(_hoops_SHSI);
		}
		if (!BIT (_hoops_RGSI, _hoops_CIIP) &&
			!nr->_hoops_ARA->_hoops_APPI._hoops_SAR &&
			BIT (nr->_hoops_AHP->line_style->flags, LSF_SOLID)) {
			_hoops_RGSI &= ~(_hoops_AIIP|_hoops_SHIP);
		}

		if (_hoops_CHGI->item._hoops_ACGI._hoops_ARRI &&
			_hoops_CHGI->item._hoops_ACGI._hoops_ARRI->Count() &&
			ANYBIT (_hoops_RGSI, _hoops_PGRI)) {
			if (!ANYBIT (_hoops_IICI, _hoops_PGRI))
				_hoops_RRSI |= _hoops_PGRI;
		}
		if (_hoops_CHGI->item._hoops_ACGI._hoops_CAPI &&
			_hoops_CHGI->item._hoops_ACGI._hoops_CAPI->Count() &&
			BIT (_hoops_RGSI, _hoops_CIIP)) {
			/* _hoops_RHHR _hoops_CCA _hoops_ICSI _hoops_CCSI _hoops_SCSI _hoops_CCA _hoops_HCH _hoops_GSSI _hoops_HSCH _hoops_RSSI. */
			if (nr->_hoops_ARA->_hoops_APPI._hoops_SAR)
				_hoops_RRSI |= _hoops_CIIP;
			else
				_hoops_RRSI |= _hoops_IRPI;
		}
		if (_hoops_CHGI->item._hoops_ACGI._hoops_RGAI &&
			_hoops_CHGI->item._hoops_ACGI._hoops_RGAI->Count()) {
			_hoops_RRSI |= _hoops_RSRI;
		}
		//_hoops_GA'_hoops_RA _hoops_ASSI _hoops_SAIA _hoops_PPR _hoops_PSSI, _hoops_CR _hoops_SSIA _hoops_RRP _hoops_IS _hoops_GCGH _hoops_IASI _hoops_HSSI
		//_hoops_RPP (_hoops_HCGI->_hoops_IGCI._hoops_ISSI._hoops_CSSI &&
		//	_hoops_HCGI->_hoops_IGCI._hoops_ISSI._hoops_CSSI->_hoops_SGR()) {
		//	_hoops_ASSI |= _hoops_SSSI;
		//}
		//_hoops_RPP (_hoops_HCGI->_hoops_IGCI._hoops_ISSI._hoops_GGGC &&
		//	_hoops_HCGI->_hoops_IGCI._hoops_ISSI._hoops_GGGC->_hoops_SGR()) {
		//	_hoops_ASSI |= _hoops_RGGC;
		//}
		if (_hoops_CHGI->item._hoops_ACGI._hoops_AGAI &&
			_hoops_CHGI->item._hoops_ACGI._hoops_AGAI->Count() &&
			ANYBIT (_hoops_RGSI, _hoops_ASRI|_hoops_GHCI)) {
			if (!BIT (_hoops_IICI, _hoops_PSRI))
				_hoops_RRSI |= (_hoops_ASRI|_hoops_GHCI);
		}

		if (_hoops_CHGI->item._hoops_ACGI._hoops_RCII &&
			_hoops_CHGI->item._hoops_ACGI._hoops_RCII->Count()) {
			if (!ANYBIT (_hoops_RGSI, _hoops_ASRI|_hoops_GCGI)) {
				_hoops_RRSI |= _hoops_ACIP;
				if (!nr->_hoops_ARA->_hoops_APPI._hoops_SAR)
					_hoops_RRSI |= _hoops_ARCP;
			}
		}

		if (!_hoops_RGSI && !_hoops_IHGI) {
			_hoops_PPCI (nr, dl);
		}
		ASSERT (!_hoops_CHGI->item._hoops_ACGI._hoops_ARRI || !_hoops_CHGI->item._hoops_ACGI._hoops_ARRI->Count() || ANYBIT (_hoops_IICI, T_FACES) || !ANYBIT (_hoops_RGSI&~_hoops_RRSI, _hoops_PGRI));
		ASSERT (!_hoops_CHGI->item._hoops_ACGI._hoops_AGAI || !_hoops_CHGI->item._hoops_ACGI._hoops_AGAI->Count() || ANYBIT (_hoops_IICI, _hoops_PSRI) || !ANYBIT (_hoops_RGSI&~_hoops_RRSI, _hoops_ASRI|_hoops_GHCI));
		ASSERT (!_hoops_CHGI->item._hoops_ACGI._hoops_CAPI || !_hoops_CHGI->item._hoops_ACGI._hoops_CAPI->Count() || !ANYBIT (_hoops_RGSI&~_hoops_RRSI, _hoops_CIIP));
		//_hoops_SAIA _hoops_PPR _hoops_PSSI _hoops_RRP _hoops_IS _hoops_GCGH _hoops_IASI _hoops_HSSI
		//_hoops_AGHR (!_hoops_HCGI->_hoops_IGCI._hoops_ISSI._hoops_CSSI || !_hoops_HCGI->_hoops_IGCI._hoops_ISSI._hoops_CSSI->_hoops_SGR() || !_hoops_AGGC (_hoops_PGGC&~_hoops_ASSI, _hoops_SSSI));
		//_hoops_AGHR (!_hoops_HCGI->_hoops_IGCI._hoops_ISSI._hoops_GGGC || !_hoops_HCGI->_hoops_IGCI._hoops_ISSI._hoops_GGGC->_hoops_SGR() || !_hoops_AGGC (_hoops_PGGC&~_hoops_ASSI, _hoops_RGGC));
	}
	else {
		//_hoops_SR'_hoops_ASAR _hoops_ASCA _hoops_GGR _hoops_HGAI _hoops_CCH, _hoops_HIH _hoops_HGGC _hoops_IGGC _hoops_CPAP
		//_hoops_HIS _hoops_SGS _hoops_SR _hoops_HS _hoops_IRS _hoops_CGGC _hoops_IS _hoops_SGGC _hoops_SCH
		_hoops_RGSI = _hoops_RAPI;
	}

	if (_hoops_RGSI) {
		ASSERT(nr->_hoops_IRR->_hoops_GRGC >= 0);

		/* _hoops_RAP _hoops_GH _hoops_RH _hoops_IARI _hoops_RRGC, _hoops_PPR _hoops_AISI _hoops_SCH _hoops_GPP */
		H3D_Collector *_hoops_ARGC;

		ZALLOC (_hoops_ARGC, H3D_Collector);
		_hoops_ARGC->next = h3ddata->_hoops_CIGI;
		_hoops_ARGC->nr = nr;
		_hoops_ARGC->mask = _hoops_RGSI;
		_hoops_ARGC->_hoops_RRSI = _hoops_RRSI;
		_hoops_ARGC->_hoops_PRGC = _hoops_RGSI;
		_hoops_ARGC->_hoops_IHGI = _hoops_IHGI;
		h3ddata->_hoops_CIGI = _hoops_ARGC;
		_hoops_RGSI |= (_hoops_HRGC | _hoops_IRGC);
		h3ddata->_hoops_ISCI++;
		if (ALLBITS (nr->_hoops_IRR->_hoops_CSA, _hoops_HCSI))
			_hoops_ARGC->_hoops_SIGI = true;  /* _hoops_CRGC _hoops_SRGC _hoops_GAGC */
	}
	*mask = _hoops_RGSI;
	return true;
}



/* _hoops_RAGC _hoops_RH _hoops_HAHH _hoops_AAGC _hoops_IPI _hoops_PAGC _hoops_GPP _hoops_IRS _hoops_AIRI _hoops_HIGR
 * _hoops_IH _hoops_RH _hoops_AHAR _hoops_IIGR _hoops_HAGC _hoops_IRS _hoops_HSSI _hoops_IAGC */
void _hoops_CAGC (
	Net_Rendition const & nr,
	H3D_Display_List *_hoops_CHGI)
{
	Display_Context const *dc = nr->_hoops_SRA;
	H3DData *h3ddata = H3DD(dc);
	int delta = 0, _hoops_SAGC = 0;
	int _hoops_GPGC = 0, _hoops_RPGC = 0;
	int _hoops_APGC = 0;
	_hoops_AIGI *list;
	_hoops_IRHA *pair;

	if (h3ddata->_hoops_CIGI->_hoops_RCGI) {
		list = h3ddata->_hoops_CIGI->_hoops_RCGI;
		list->ResetCursor();
		while ((pair = list->PeekCursor()) != null) {
			Tristrip const *ts = (Tristrip const *) pair->geo;
			delta = _hoops_CCSH (ts);
			_hoops_APGC += (ts->point_count < ts->total ? ts->point_count : ts->total);
			_hoops_GPGC += delta;
			list->AdvanceCursor();
		}
		_hoops_SAGC += list->Count();
	}
	if (h3ddata->_hoops_CIGI->_hoops_IIRI) {
		list = h3ddata->_hoops_CIGI->_hoops_IIRI;
		list->ResetCursor();
		while ((pair = list->PeekCursor()) != null) {
			Polyedge const *pe = (Polyedge const *) pair->geo;
			delta = _hoops_ASSH(pe, h3ddata->_hoops_IHP);
			_hoops_APGC += (pe->point_count < pe->total ? pe->point_count : pe->total);
			_hoops_GPGC += delta;
			list->AdvanceCursor();
		}
		_hoops_SAGC += list->Count();
		/* _hoops_HAR _hoops_PPGC _hoops_GGSP, _hoops_HIH _hoops_HPGC _hoops_RH _hoops_IPGC'_hoops_GRI _hoops_CPGC _hoops_CHH _hoops_IAII _hoops_SHH
		 * _hoops_RRI _hoops_SPGC _hoops_HSAR _hoops_SCH _hoops_HRGR _hoops_GHGC */
		if (h3ddata->_hoops_CIGI->_hoops_RCGI)
			_hoops_RPGC *= 2;
	}
	if (h3ddata->_hoops_CIGI->_hoops_HHAI) {
		list = h3ddata->_hoops_CIGI->_hoops_HHAI;
		list->ResetCursor();
		while ((pair = list->PeekCursor()) != null) {
			Polymarker *pm = (Polymarker *)pair->geo;
			delta = _hoops_PSSH (pm);
			_hoops_GPGC += delta;
			list->AdvanceCursor();
		}
		_hoops_SAGC += list->Count();
	}
	if (h3ddata->_hoops_CIGI->_hoops_CIRI) {
		list = h3ddata->_hoops_CIGI->_hoops_CIRI;
		list->ResetCursor();
		while ((pair = list->PeekCursor()) != null) {
			Polyedge const *pe = (Polyedge const *) pair->geo;
			delta = _hoops_ASSH(pe, h3ddata->_hoops_IHP);
			_hoops_APGC += pe->point_count;
			_hoops_GPGC += delta;
			list->AdvanceCursor();
		}
		_hoops_SAGC += list->Count();
	}
	if (h3ddata->_hoops_CIGI->_hoops_SIRI) {
		list = h3ddata->_hoops_CIGI->_hoops_SIRI;
		list->ResetCursor();
		while ((pair = list->PeekCursor()) != null) {
			Polyedge const *pe = (Polyedge const *) pair->geo;
			delta = _hoops_ASSH(pe, h3ddata->_hoops_IHP);
			_hoops_APGC += pe->point_count;
			_hoops_GPGC += delta;
			list->AdvanceCursor();
		}
		_hoops_SAGC += list->Count();
	}
	if (h3ddata->_hoops_CIGI->_hoops_HRPI) {
		list = h3ddata->_hoops_CIGI->_hoops_HRPI;
		list->ResetCursor();
		while ((pair = list->PeekCursor()) != null) {
			Polyline *p = (Polyline *)pair->geo;

			delta = _hoops_GSII ((Geometry *)pair->geo, pair->single);
			if (p->type == _hoops_IIIP || p->type == _hoops_HIIP || p->type == _hoops_PIIP) {
				do {
					if (p->type == _hoops_PIIP)
						_hoops_APGC += 2;
					else
						_hoops_APGC += Abs (p->count);
					p = (Polyline *)p->next;
				} while (_hoops_APGC < H3D_Display_List_MINIMUM &&
						 p != null &&
						 (p->type == _hoops_IIIP || p->type == _hoops_HIIP || p->type == _hoops_PIIP));
			}
			else
				_hoops_APGC += H3D_Display_List_MINIMUM;
			_hoops_GPGC += delta;
			list->AdvanceCursor();
		}
		_hoops_SAGC += list->Count();
	}
	if (h3ddata->_hoops_CIGI->_hoops_IIII) {
		list = h3ddata->_hoops_CIGI->_hoops_IIII;
		list->ResetCursor();
		while ((pair = list->PeekCursor()) != null) {
			Polygon *p = (Polygon *)pair->geo;
			if (p->type == _hoops_RCIP) {
				_hoops_APGC += p->count;
				delta = 24 * p->count + 24;
			}
			else {
				_hoops_APGC += 100;
				delta = 24 * 100;
			}
			_hoops_GPGC += delta;
			_hoops_RPGC += delta;
			_hoops_SAGC++;
			list->AdvanceCursor();
		}
	}
	if (h3ddata->_hoops_CIGI->_hoops_IHAI) {
		list = h3ddata->_hoops_CIGI->_hoops_IHAI;
		list->ResetCursor();
		while ((pair = list->PeekCursor()) != null) {
			if (pair->type == _hoops_IRHA::_hoops_HCAI) {
				Polymarker *pm = (Polymarker *)pair->geo;
				delta = _hoops_PSSH (pm);
				_hoops_GPGC += delta;
			}
			else {
				if (!pair->single) {
					//_hoops_RHGC _hoops_IGIR, _hoops_HIS _hoops_SAHR _hoops_AHGC
					_hoops_APGC += 100;
					delta = 24 * 100;
				}
				else {
					_hoops_APGC ++;
					delta = 24;
				}
			}
			_hoops_GPGC += delta;
			_hoops_RPGC += delta;
			_hoops_SAGC++;
			list->AdvanceCursor();
		}
	}
	if (!_hoops_GPGC ||
		_hoops_APGC <= H3D_Display_List_MINIMUM)
		return;

	/* _hoops_PHGC _hoops_RIPI _hoops_HPP _hoops_AIPP (_hoops_SR _hoops_HHGC _hoops_IS _hoops_IHGC _hoops_RH _hoops_CHGC _hoops_SHGC _hoops_IPIH _hoops_CISI _hoops_AIRI _hoops_HIGR) */
	float _hoops_GIGC = (float)_hoops_GPGC / _hoops_SAGC;  
	if (HI_Push_Display_List (dc->_hoops_RIGC, _hoops_CHGI->_hoops_PPAH, _hoops_GIGC, _hoops_GPGC))
		_hoops_CHGI->item._hoops_ACGI.flags |= H3D_SEGDL_BLESSED_SEGMENT;
}


void _hoops_AIGC(
	Net_Rendition const & nr,
	_hoops_GACR **_hoops_PICI,
	bool _hoops_IHGI)
{
	Display_Context const *dc = nr->_hoops_SRA;
	H3DData *h3ddata = H3DD(dc);
	_hoops_GACR *dl = null;
	H3D_Display_List *_hoops_CHGI;
	Integer32 _hoops_PIGC = 0;

	if (h3ddata->_hoops_CIGI) {
		bool _hoops_RACR;

		if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT) {
			_hoops_ACHR _hoops_RGP = nr->_hoops_RGP;

			if (h3ddata->_hoops_CIGI->_hoops_SIGI)
				_hoops_GPRH(_hoops_HIGC)++;
			_hoops_RACR = _hoops_AACR(nr, &(*_hoops_PICI), &dl, &_hoops_CHGI, H3D_DL_SEGMENT_TREE);
			h3ddata->_hoops_AAI = _hoops_CHGI;
			if (!_hoops_IACI(dc) &&
				!BIT(dl->_hoops_AGRI, DL_INSUFFICIENT_VRAM)) 
			{
				if (!BIT(nr->transform_rendition->flags,_hoops_GRHH))
					_hoops_RGP &= ~(T_LIGHTS_FOR_FACES | T_LIGHTS_FOR_EDGES | T_LIGHTS_FOR_MARKERS);
				if (!BIT (_hoops_RGP, T_FACES))
					_hoops_RGP &= ~T_LIGHTS_FOR_FACES;
				if (!BIT (_hoops_RGP, _hoops_PSRI))
					_hoops_RGP &= ~T_LIGHTS_FOR_EDGES;
				if (!BIT (_hoops_RGP, T_VERTICES))
					_hoops_RGP &= ~T_LIGHTS_FOR_MARKERS;
				if (BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_EDGES)) {
					_hoops_RGP |= _hoops_GPA;
					if (_hoops_CPGI (nr->_hoops_IRR)) {
						_hoops_RGP &= ~(T_FACES);
						_hoops_RGP |= nr->_hoops_ARA->_hoops_CICP._hoops_RGP & (T_FACES);
					}
				}

				_hoops_CHGI->item._hoops_ACGI._hoops_RGP |= _hoops_RGP;
				if (BIT(dc->flags, _hoops_IIGC)) {
					//_hoops_RPP _hoops_CPAP _hoops_HRGR _hoops_CIGC, _hoops_HSII _hoops_SCH _hoops_GAR _hoops_RPP _hoops_SCH _hoops_AAPR _hoops_HAR _hoops_SIGC _hoops_IH _hoops_RH
					//_hoops_GCGC _hoops_IIGR _hoops_IRS _hoops_HCH _hoops_ICH _hoops_AIRI _hoops_HIGR _hoops_HCGI
					_hoops_ACHR _hoops_RCGC = dc->_hoops_AHSI->segment->_hoops_RCGC;
					if (BIT (_hoops_RCGC, T_FACES) &&
						!BIT (nr->_hoops_PSGI, T_FACES))
						_hoops_RGP &= ~T_FACES;
					if (BIT (_hoops_RCGC, T_LINES) &&
						!BIT (nr->_hoops_PSGI, T_LINES))
						_hoops_RGP &= ~T_LINES;
					if (BIT (_hoops_RCGC, T_EDGES) &&
						!BIT (nr->_hoops_PSGI, T_EDGES))
						_hoops_RGP &= ~T_EDGES;
					//_hoops_SRSA _hoops_GASA _hoops_PIP: _hoops_PA _hoops_IS _hoops_AA _hoops_ARI _hoops_IH _hoops_ACGC?
					if (BIT (_hoops_RCGC, T_VERTICES) &&
						!BIT (nr->_hoops_PSGI, T_VERTICES))
						_hoops_RGP &= ~T_VERTICES;
					if (BIT (_hoops_RCGC, T_MARKERS) &&
						!BIT (nr->_hoops_PSGI, T_MARKERS))
						_hoops_RGP &= ~T_MARKERS;
					if (BIT (_hoops_RCGC, T_TEXT) &&
						!BIT (nr->_hoops_PSGI, T_TEXT))
						_hoops_RGP &= ~T_TEXT;

				    //_hoops_RH _hoops_HSPR _hoops_PCGC _hoops_PSSP _hoops_HCGC _hoops_GGR _hoops_ICGC _hoops_SGS 
				    //_hoops_ASSI _hoops_CPAP _hoops_SGS _hoops_HRGR _hoops_CCGC _hoops_RRH
				    if (BIT (_hoops_RGP, T_FACES) && 
					    nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR == 0 && 
					    !nr->_hoops_IHA->_hoops_CHA->_hoops_ARIR)
					    _hoops_RGP &= ~T_FACES;
				    if (BIT (_hoops_RGP, T_EDGES) && 
					    nr->_hoops_RHP->_hoops_CHA->_hoops_IRIR == 0 && 
					    !nr->_hoops_RHP->_hoops_CHA->_hoops_ARIR)
					    _hoops_RGP &= ~T_EDGES;
				    if (BIT (_hoops_RGP, T_VERTICES) && 
					    nr->_hoops_SCP->_hoops_CHA->_hoops_IRIR == 0 && 
					    !nr->_hoops_SCP->_hoops_CHA->_hoops_ARIR)
					    _hoops_RGP &= ~T_VERTICES;
				}
				if (BIT (_hoops_RGP, T_FACES)) {
					dl->action_mask &= ~_hoops_PGRI;
					if (h3ddata->_hoops_CIGI->_hoops_CIRI)
						_hoops_RGP |= T_EDGES;
					if (h3ddata->_hoops_CIGI->_hoops_SIRI)
						_hoops_RGP |= _hoops_GPA;
				}
				if (ANYBIT (_hoops_RGP, _hoops_PSRI))
					dl->action_mask &= ~_hoops_IGAI;
				if (BIT (_hoops_RGP, _hoops_GPA))
					dl->action_mask &= ~_hoops_RSRI;
				if (ANYBIT (_hoops_RGP, T_VERTICES))
					dl->action_mask &= ~_hoops_RGPI;
				if (ANYBIT (_hoops_RGP, T_MARKERS))
					dl->action_mask &= ~_hoops_HCIP;
				if (BIT (_hoops_RGP, T_LINES))
					dl->action_mask &= ~_hoops_IRPI;
				if (ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE))
					dl->action_mask &= ~(_hoops_ACIP|_hoops_ARCP);
			}
			if (h3ddata->_hoops_CIGI->_hoops_SIGI) {
				if (ANYBIT (h3ddata->_hoops_CIGI->_hoops_PRGC, _hoops_PGRI))
					dl->action_mask |= _hoops_PGRI;
				if (ANYBIT (h3ddata->_hoops_CIGI->_hoops_PRGC, _hoops_ASRI|_hoops_GHCI))
					dl->action_mask |= _hoops_IGAI;
				if (BIT (h3ddata->_hoops_CIGI->_hoops_PRGC, _hoops_RSRI))
					dl->action_mask |= _hoops_RSRI;
				if (BIT (h3ddata->_hoops_CIGI->_hoops_PRGC, _hoops_RGPI))
					dl->action_mask |= _hoops_RGPI;
				if (BIT (h3ddata->_hoops_CIGI->_hoops_PRGC, _hoops_HCIP))
					dl->action_mask |= _hoops_HCIP;
				if (ANYBIT (h3ddata->_hoops_CIGI->_hoops_PRGC, _hoops_IRPI))
					dl->action_mask |= _hoops_IRPI;
				if (BIT (h3ddata->_hoops_CIGI->_hoops_PRGC, _hoops_ACIP))
					dl->action_mask |= _hoops_ACIP;
			}
			dl->action_mask |= (h3ddata->_hoops_CIGI->_hoops_PRGC ^ h3ddata->_hoops_CIGI->mask);
			dl->action_mask |= dc->_hoops_SCGC;
			dl->action_mask |= dc->_hoops_GSGC;
			if (BIT (dc->_hoops_GSGC, _hoops_SHSI))
				dl->action_mask |= _hoops_PCSI;
			dl->action_mask |= nr->_hoops_RSGC->action_mask;  /* _hoops_ASGC _hoops_ASSI _hoops_AIRI _hoops_CPCI */
			if (!_hoops_IACI(dc) &&
				!h3ddata->_hoops_CIGI->_hoops_SIGI)
				dl->action_mask &= ~h3ddata->_hoops_CIGI->_hoops_RRSI;
			if (nr->_hoops_IRR->_hoops_SRI == _hoops_GAI &&
				BIT (nr->transform_rendition->heuristics, _hoops_IRI))
				dl->_hoops_PRRI |= _hoops_HRRI;

			/* _hoops_GCPR _hoops_PSGC _hoops_IH _hoops_HSSI (_hoops_IS _hoops_SHH _hoops_RHRI _hoops_HPGR _hoops_GHIR _hoops_IIGR _hoops_HSGC */
			if (!BIT (_hoops_CHGI->item._hoops_ACGI.flags, H3D_SEGDL_BLESSED_SEGMENT)) {
				bool _hoops_ISGC = BIT(dc->flags, _hoops_IIGC);
				if (_hoops_ISGC)
					_hoops_CHGI->item._hoops_ACGI.flags |= H3D_SEGDL_BLESSED_SEGMENT; //_hoops_CSGC _hoops_ICH _hoops_GRRI'_hoops_GRI
				else
					_hoops_CAGC (nr, _hoops_CHGI);
			}

			ASSERT (dc->_hoops_SSGC == -1 || dl->action_mask != 0);
		}
		_hoops_PIGC = h3ddata->_hoops_ISCI - 1;
		h3ddata->_hoops_ISCI = 0;

		if (h3ddata->_hoops_CSSH == null)
			h3ddata->_hoops_CSSH = POOL_NEW(dc->memory_pool, _hoops_ISSH)(dc->memory_pool); //_hoops_GGRC _hoops_SCII _hoops_HSHR -> _hoops_RGRC
		_hoops_HHGI (nr, dl, _hoops_IHGI);
		_hoops_PIRI (nr, dl, _hoops_IHGI);
		_hoops_RHAI (nr, dl, _hoops_IHGI); /* _hoops_AGRC _hoops_GIHA _hoops_PPR _hoops_SAIA */
		_hoops_HIII (nr, dl, _hoops_IHGI);  /* _hoops_GSCA _hoops_HSSP _hoops_RSSI _hoops_PPR _hoops_HSSP _hoops_SPPR */

		// _hoops_PGRC _hoops_IRHH _hoops_HCGI'_hoops_GRI _hoops_PRGI _hoops_RPP _hoops_RH _hoops_HGRC _hoops_CCH _hoops_CSAP _hoops_IGRC _hoops_CGRC
		if (h3ddata->_hoops_CIGI->_hoops_HRPI &&
			nr->_hoops_IRR->_hoops_GAHA == Display_List_GEOMETRY) {
			_hoops_RACR = _hoops_AACR(nr, &(*_hoops_PICI), &dl, &_hoops_CHGI, H3D_DL_SEGMENT_TREE);
			if (!_hoops_IACI(dc)) {
				if (BIT (nr->_hoops_RGP, T_LINES))
					dl->action_mask &= ~_hoops_IRPI;
			}
			if (h3ddata->_hoops_CIGI->_hoops_SIGI) {
				if (ANYBIT (h3ddata->_hoops_CIGI->_hoops_PRGC, _hoops_IRPI))
					dl->action_mask |= _hoops_IRPI;
			}
			int _hoops_SGRC = 0;
			_hoops_SGRC |= (h3ddata->_hoops_CIGI->_hoops_PRGC ^ h3ddata->_hoops_CIGI->mask);
			_hoops_SGRC |= dc->_hoops_SCGC & ~(_hoops_RSCI);
			_hoops_SGRC |= dc->_hoops_GSGC;
			_hoops_SGRC |= nr->_hoops_RSGC->action_mask;  /* _hoops_ASGC _hoops_ASSI _hoops_AIRI _hoops_CPCI */
			dl->action_mask |= (_hoops_SGRC & _hoops_IRPI);
		}
		_hoops_SGPI (nr, dl, _hoops_IHGI); /* _hoops_AGRC _hoops_APGR, _hoops_GRRC _hoops_PPR _hoops_RRRC */

		/* _hoops_ARRC _hoops_RH _hoops_IARI _hoops_RRGC */
		H3D_Collector *_hoops_PRRC = h3ddata->_hoops_CIGI->next;
		h3ddata->_hoops_CIGI->nr.release();
		FREE (h3ddata->_hoops_CIGI, H3D_Collector);
		h3ddata->_hoops_CIGI = _hoops_PRRC;
		h3ddata->_hoops_ISCI = _hoops_PIGC;

		//_hoops_HAR _hoops_RCRR _hoops_RPP _hoops_RGR _hoops_CGH _hoops_SHH _hoops_PPP _hoops_PAR _hoops_HAR...
		//_hoops_AGHR (!_hoops_HCGI->_hoops_IGCI._hoops_ISSI._hoops_HRRC || !_hoops_HCGI->_hoops_IGCI._hoops_ISSI._hoops_HRRC->_hoops_SGR() || !_hoops_IRRC (_hoops_GRRI->_hoops_CRRC, _hoops_SRRC));
	}

	h3ddata->_hoops_AAI = null;
} //_hoops_RSGR _hoops_API '_hoops_RSGR _hoops_AIRI _hoops_CPCI'



local bool
_hoops_GARC (
	Net_Rendition const &		nr,
	_hoops_GACR const *		dl,
	H3D_Display_List const *	odl)
{
	bool _hoops_RARC, _hoops_AARC;

	if (!odl->item._hoops_RPPI._hoops_ARPI)
		return true;
	if (dl && dl->_hoops_GSAI == (_hoops_GHGI) DL_FLAG_INVALID)
		return false;

	_hoops_AARC = (nr->_hoops_IRR->_hoops_SRI == _hoops_GAI &&
		BIT (nr->transform_rendition->heuristics, _hoops_IRI));
	_hoops_RARC = BIT (dl->_hoops_PRRI, _hoops_HRRI);
	if (_hoops_RARC != _hoops_AARC)
		return false;

	_hoops_PARC const *_hoops_HARC = &(nr->_hoops_ARA->_hoops_APPI);
	if (odl->item._hoops_RPPI._hoops_SAR != _hoops_HARC->_hoops_SAR)
		return false;
	if (!odl->item._hoops_RPPI._hoops_SAR) {
		if (odl->item._hoops_RPPI._hoops_PPPI != _hoops_HARC->_hoops_PPPI)
			return false;
		if (odl->item._hoops_RPPI._hoops_HPPI != _hoops_HARC->_hoops_HPPI)
			return false;
		if (odl->item._hoops_RPPI._hoops_IPPI != _hoops_HARC->_hoops_IPPI)
			return false;
		if (odl->item._hoops_RPPI._hoops_CPPI != _hoops_HARC->_hoops_CPPI)
			return false;
		if (odl->item._hoops_RPPI._hoops_SPPI != _hoops_HARC->_hoops_SPPI)
			return false;
	}
	return true;
}


local bool
_hoops_IARC (
	Net_Rendition const &		nr,
	_hoops_GACR const *		dl,
	H3D_Display_List const *	odl)
{
	_hoops_ACHR _hoops_CARC = nr->_hoops_RGP;
	H3D_Display_List_List *list;
	H3D_Display_List *_hoops_APCI;
	bool _hoops_RARC, _hoops_AARC;
	bool _hoops_SARC, _hoops_GPRC;

	if (dl && dl->_hoops_GSAI == (_hoops_GHGI) DL_FLAG_INVALID)
		return false;

	_hoops_AARC = (nr->_hoops_IRR->_hoops_SRI == _hoops_GAI &&
		BIT (nr->transform_rendition->heuristics, _hoops_IRI));
	_hoops_RARC = BIT (dl->_hoops_PRRI, _hoops_HRRI);
	if (_hoops_RARC != _hoops_AARC)
		return false;

	if (BIT (_hoops_CARC, T_FACES)) {
		if (odl->item._hoops_ACII._hoops_PCII) {
			list = odl->item._hoops_ACII._hoops_PCII;
			list->ResetCursor();
			while ((_hoops_APCI = list->PeekCursor()) != null) {
				list->AdvanceCursor();
				if (!_hoops_RPRC (nr, null, dl, _hoops_APCI))
					return false;
				_hoops_SARC = BIT (_hoops_APCI->item.geometry._hoops_SRHA, DL_LIGHTING);
				_hoops_GPRC = BIT (nr->transform_rendition->flags, _hoops_GRHH) &&
					BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES);
				if (_hoops_SARC != _hoops_GPRC)
					return false;
			}
		}
		if (odl->item._hoops_ACII._hoops_HCII) {
			list = odl->item._hoops_ACII._hoops_HCII;
			list->ResetCursor();
			while ((_hoops_APCI = list->PeekCursor()) != null) {
				list->AdvanceCursor();
				if (!_hoops_RPRC (nr, null, dl, _hoops_APCI))
					return false;
			}
		}
	}
	if (BIT (_hoops_CARC, T_ANY_POLYGON_EDGE)) {
		if (odl->item._hoops_ACII._hoops_GHPI) {
			list = odl->item._hoops_ACII._hoops_GHPI;
			if (list->Count() > 0) {
				int weight;
				if ((weight = nr->_hoops_RHP->weight) < 0)
					weight = (int)(HD_Compute_Generic_Size (nr, nr->_hoops_RHP->_hoops_PHP, nr->_hoops_RHP->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
				if (_hoops_GAPI (nr->_hoops_RHP->line_style) ||
					weight > H3D_LARGEST_PRECOMPUTED_CIRCLE)
					return false;
			}
			list->ResetCursor();
			while ((_hoops_APCI = list->PeekCursor()) != null) {
				list->AdvanceCursor();
				if (!_hoops_APRC (nr, null, dl, _hoops_APCI))
					return false;
			}
		}
	}

	if (!odl->item._hoops_ACII._hoops_GCII)
		return true;

	if (!odl->item._hoops_ACII._hoops_GHPI &&
		!odl->item._hoops_ACII._hoops_PCII)
		return true;

	_hoops_PARC const *_hoops_HARC = &(nr->_hoops_ARA->_hoops_APPI);
	if (odl->item._hoops_ACII._hoops_SAR != _hoops_HARC->_hoops_SAR)
		return false;
	if (!odl->item._hoops_ACII._hoops_SAR) {
		if (odl->item._hoops_ACII._hoops_PPPI != _hoops_HARC->_hoops_PPPI)
			return false;
		if (odl->item._hoops_ACII._hoops_HPPI != _hoops_HARC->_hoops_HPPI)
			return false;
		if (odl->item._hoops_ACII._hoops_IPPI != _hoops_HARC->_hoops_IPPI)
			return false;
		if (odl->item._hoops_ACII._hoops_CPPI != _hoops_HARC->_hoops_CPPI)
			return false;
		if (odl->item._hoops_ACII._hoops_SPPI != _hoops_HARC->_hoops_SPPI)
			return false;
	}

	return true;
}


/*
 * _hoops_PGAA
 */
local bool
_hoops_GSCI (
		Net_Rendition const & nr,
		_hoops_GACR const *dl,
		H3D_Display_List const *_hoops_CHGI,
		_hoops_ACHR alter *_hoops_HSHI,
		_hoops_ACHR alter *_hoops_IICI,
		_hoops_ACHR alter *_hoops_CICI)
{
	H3DData *h3ddata = H3DD(nr->_hoops_SRA);
	H3D_Display_List_List *vlist = null;
	_hoops_ACHR _hoops_CARC, _hoops_PPRC;
	H3D_Display_List *odl;

	if (dl->_hoops_GSAI == (unsigned int) DL_FLAG_INVALID)
		return false;

	_hoops_CARC = nr->_hoops_RGP;
	if (!BIT(nr->transform_rendition->flags,_hoops_GRHH))
	    _hoops_CARC &= ~(T_LIGHTS_FOR_FACES | T_LIGHTS_FOR_EDGES | T_LIGHTS_FOR_MARKERS);
	if (BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_EDGES)) {
		_hoops_CARC |= _hoops_GPA;
		if (_hoops_CPGI (nr->_hoops_IRR)) {
			// _hoops_RPP _hoops_ACGC _hoops_CHR _hoops_PPP, _hoops_HSP _hoops_HPRC _hoops_HRGR _hoops_IPRC _hoops_HPP _hoops_CPRC _hoops_AAP
			_hoops_CARC &= ~(T_FACES);
			_hoops_CARC |= nr->_hoops_ARA->_hoops_CICP._hoops_RGP & (T_FACES);
		}
	}
	if (_hoops_HSHI)
		*_hoops_HSHI = _hoops_CARC;

	_hoops_PPRC = _hoops_CHGI->item._hoops_ACGI._hoops_RGP;
	*_hoops_IICI = _hoops_CARC & ~_hoops_PPRC;
	*_hoops_CICI = _hoops_PPRC & ~_hoops_CARC;

	if (ALLBITS (nr->_hoops_IRR->_hoops_CSA, _hoops_HCSI))
		return false;

	if (BIT (_hoops_CARC, T_FACES)) {
		vlist = _hoops_CHGI->item._hoops_ACGI._hoops_ARRI;
		if (vlist && vlist->Count()) {
			odl = vlist->PeekFirst();
			if (_hoops_HGRI (nr, odl->item.geometry._hoops_SRHA, BIT (nr->_hoops_PSGI, T_FACES)))
				return false;
		}
		if (vlist) {
			vlist->ResetCursor();
			while ((odl = vlist->PeekCursor()) != null) {
				if (!_hoops_RPRC (nr, null, dl, odl))
					return false;
				vlist->AdvanceCursor();
			}
		}
	}

	if (BIT (_hoops_CARC, T_LINES)) {
		vlist = _hoops_CHGI->item._hoops_ACGI._hoops_CAPI;
		if (vlist) {
			vlist->ResetCursor();
			if (vlist->Count()) {
				if (h3ddata->_hoops_IHP &&
					!BIT(dl->_hoops_PRRI, _hoops_PGAI))
					return false;
				float weight = nr->_hoops_AHP->weight;
				if (weight < 0)
					weight = (int)(HD_Compute_Generic_Size (nr, nr->_hoops_AHP->_hoops_PHP, nr->_hoops_AHP->_hoops_HHP,1.0f, false, 0, true)+0.5f);
				if (_hoops_HSRI (nr, nr->_hoops_AHP, true, weight))
					return false;
			}

			while ((odl = vlist->PeekCursor()) != null) {
				if (!_hoops_GARC (nr, dl, odl))
					return false;
				vlist->AdvanceCursor();
			}
		}
	}

	if (ANYBIT (_hoops_CARC, T_ANY_EDGE)) {
		int i;
		for (i = 0; i < 2; i++) {
			if (i == 0)
				vlist = _hoops_CHGI->item._hoops_ACGI._hoops_GGAI;
			else if (i == 1)
				vlist = _hoops_CHGI->item._hoops_ACGI._hoops_AGAI;
			if (vlist && vlist->Count()) {
				if (vlist == _hoops_CHGI->item._hoops_ACGI._hoops_AGAI &&
					BIT (nr->transform_rendition->flags, _hoops_GRHH) &&
					BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES)) {
					if (BIT (_hoops_CHGI->item._hoops_ACGI._hoops_RGP, T_EDGES) &&
						!BIT (_hoops_CHGI->item._hoops_ACGI._hoops_RGP, T_LIGHTS_FOR_EDGES))
						return false;
				}

				float weight = nr->_hoops_RHP->weight;
				if (weight < 0)
					weight = (int)(HD_Compute_Generic_Size (nr, nr->_hoops_RHP->_hoops_PHP, nr->_hoops_RHP->_hoops_HHP,1.0f, false, 0, true)+0.5f);
				if (_hoops_HSRI (nr, nr->_hoops_RHP, true, weight))
					return false;

				vlist->ResetCursor();
				if (vlist->Count() && h3ddata->_hoops_IHP &&
					!BIT(dl->_hoops_PRRI, _hoops_PGAI))
					return false;
				while ((odl = vlist->PeekCursor()) != null) {
					if (!_hoops_APRC (nr, null, dl, odl))
						return false;
					vlist->AdvanceCursor();
				}
			}
		}
	}

	if (BIT (_hoops_CARC, _hoops_GPA)) {
		vlist = _hoops_CHGI->item._hoops_ACGI._hoops_RGAI;
		if (vlist) {
			vlist->ResetCursor();
			if (vlist->Count() && h3ddata->_hoops_IHP &&
				!BIT(dl->_hoops_PRRI, _hoops_PGAI))
				return false;
			while ((odl = vlist->PeekCursor()) != null) {
				if (!_hoops_APRC (nr, null, dl, odl))
					return false;
				vlist->AdvanceCursor();
			}
		}
	}

	if (BIT (_hoops_CARC, T_VERTICES)) {
		vlist = _hoops_CHGI->item._hoops_ACGI._hoops_RAAI;
		if (vlist) {
			if ((odl = vlist->PeekFirst()) != null) {
				if (!_hoops_SPRC (nr, T_VERTICES, dl, odl))
					return false;
			}
		}
	}

	if (BIT (_hoops_CARC, T_MARKERS)) {
		vlist = _hoops_CHGI->item._hoops_ACGI._hoops_GAAI;
		if (vlist) {
			if ((odl = vlist->PeekFirst()) != null) {
				if (!_hoops_SPRC (nr, T_MARKERS, dl, odl))
					return false;
			}
		}
	}

	if (ANYBIT (_hoops_CARC, T_FACES|T_ANY_POLYGON_EDGE)) {
		vlist = _hoops_CHGI->item._hoops_ACGI._hoops_RCII;
		if (vlist) {
			vlist->ResetCursor();

			if (ANYBIT(_hoops_CARC, T_ANY_POLYGON_EDGE) &&
				vlist->Count() &&
				h3ddata->_hoops_IHP &&
				!BIT(dl->_hoops_PRRI, _hoops_PGAI))
				return false;

			while ((odl = vlist->PeekCursor()) != null) {
				if (!_hoops_IARC (nr, dl, odl))
					return false;
				vlist->AdvanceCursor();
			}
		}
	}

	return true;
}


/*
 * _hoops_PGAA
 */
bool _hoops_RPRC (
		Net_Rendition const &		nr,
		Tristrip const *			ts,
		_hoops_GACR const *		dl,
		H3D_Display_List const *	odl)
{
	H3DData const *				h3ddata = H3DD (nr->_hoops_SRA);
	_hoops_HHA const &	matr = nr->_hoops_IHA->_hoops_CHA;
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	bool 						_hoops_GHRC, _hoops_RHRC, findices;
	bool 						_hoops_AHRC, _hoops_PHRC, _hoops_HHRC;
	bool						_hoops_RARC, _hoops_AARC;
	bool 						_hoops_SPGI, _hoops_IHRC;
	unsigned int				_hoops_RHGI;
	int 						_hoops_CHRC, _hoops_PSR;
	int 						_hoops_SRHA = 0;
	int 						_hoops_CARI = 0;

	if (odl->type != H3D_DL_GEOMETRY) {
		_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
			"Unexpected display list type in check_tristrip_display_list_valid");
		return false;
	}
	if (!h3ddata->_hoops_CSC->_hoops_RAIH)
		return true;

	_hoops_AARC = (nr->_hoops_IRR->_hoops_SRI == _hoops_GAI &&
		BIT (nr->transform_rendition->heuristics, _hoops_IRI));
	_hoops_RARC = BIT (dl->_hoops_PRRI, _hoops_HRRI);
	if (_hoops_RARC != _hoops_AARC)
		return false;

	if (dl && dl->_hoops_GSAI == (unsigned int) DL_FLAG_INVALID)
		return false;
	bool _hoops_SHRC = BIT (odl->item.geometry._hoops_SRHA, DL_HAS_TRANSPARENCY) &&
					!nr->_hoops_IRR->_hoops_GIRC;
	bool _hoops_RIRC = (
					nr->_hoops_CPP->_hoops_PRH.style != _hoops_GCPI &&
					BIT (nr->_hoops_PSGI, T_FACES)
	);
	if (_hoops_RIRC != _hoops_SHRC)
		return false;

	if (ANYBIT (odl->item.geometry._hoops_CARI, _hoops_HPII|_hoops_APIA))
		return true;  //_hoops_AAPI _hoops_HS _hoops_PSP _hoops_IRGH _hoops_GPHA _hoops_AIRC, _hoops_HIS _hoops_PIRC _hoops_IIGR _hoops_RH _hoops_RII _hoops_PCGC _hoops_GHAA

	if (BIT (odl->item.geometry._hoops_SRHA, _hoops_CAGI)) {
		if (odl->time_stamp <
			nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR->time_stamp)
			return false;
	}

	_hoops_RHGI = _hoops_RRGH->_hoops_CSA & ~_hoops_AHGI;
	_hoops_SPGI = BIT (_hoops_RRGH->locks.color, Color_FRONT) &&
		 BIT (_hoops_RRGH->locks._hoops_HAA[_hoops_IAA], M_DIFFUSE);
	_hoops_RHRC = (!_hoops_SPGI && BIT (_hoops_RHGI, _hoops_PHGI));
	_hoops_PHRC =(!_hoops_SPGI && BIT (_hoops_RHGI, _hoops_HIRC));
	_hoops_GHRC = BIT (odl->item.geometry._hoops_SRHA, DL_INDEX_INTERPOLATION);
	_hoops_AHRC = BIT (odl->item.geometry._hoops_SRHA, DL_COLOR_INTERPOLATION);
	findices = BIT (odl->item.geometry._hoops_SRHA, DL_COLORS_BY_FINDEX);
	_hoops_HHRC = BIT (odl->item.geometry._hoops_SRHA, DL_VCOLORED_TRISTRIP);

	if (findices && (_hoops_GHRC != _hoops_RHRC))
		return false;
	if (_hoops_HHRC) {
		_hoops_PHRC =(!_hoops_SPGI && BIT (_hoops_RHGI, _hoops_HIRC));
		_hoops_AHRC = BIT (odl->item.geometry._hoops_SRHA, DL_COLOR_INTERPOLATION);
		if (_hoops_AHRC != _hoops_PHRC)
			return false;
		_hoops_IHRC = BIT (odl->item.geometry._hoops_SRHA, _hoops_IIRC);
		if (_hoops_SPGI != _hoops_IHRC)
			return false;
	}

	if (ts) {
		int _hoops_CIRC, _hoops_SIRC, _hoops_GCRC;
		int added, _hoops_RCRC;
		_hoops_CIRC = _hoops_ACRC & ~(
			DL_COLOR_INTERPOLATION |
			DL_INDEX_INTERPOLATION |
			_hoops_SRHH);
		_hoops_SIRC = DL_TEXTURING;
		_hoops_GCRC = (
			_hoops_PCRC |
			_hoops_HCRC |
			_hoops_ICRC);

		// _hoops_ISPR _hoops_CCRC
		added = odl->item.geometry._hoops_SRHA & ~ts->_hoops_SRHA;
		_hoops_RCRC = ts->_hoops_SRHA & ~odl->item.geometry._hoops_SRHA;
		if ((_hoops_RCRC & _hoops_CIRC) != 0)
			return false;
		if ((added & _hoops_CIRC & ~_hoops_SIRC) != 0)
			return false;

		// _hoops_ISPR _hoops_SCRC
		added = odl->item.geometry._hoops_CARI & ~ts->_hoops_CARI;
		_hoops_RCRC = ts->_hoops_CARI & ~odl->item.geometry._hoops_CARI;
		if ((_hoops_RCRC & _hoops_GCRC) != 0)
			return false;
		if ((added & _hoops_GCRC) != 0)
			return false;

		if (odl->item.geometry._hoops_GSAI != ts->_hoops_GSAI)
			return false;
	}
	else {
		unsigned int _hoops_GSAI = _hoops_RRGH->_hoops_CSA & Rendo_TRISTRIP_MASK;
		if (BIT (nr->_hoops_IRR->_hoops_CSA,
				 (_hoops_GSRC & ~_hoops_AHGI)) &&
			(nr->_hoops_IHA->_hoops_CHA->_hoops_ARIR ||
			 nr->_hoops_IHA->_hoops_GIA->_hoops_ARIR)) {
			if (!BIT (odl->item.geometry._hoops_SRHA, DL_TEXTURING))
				return false;
		}
		if (ANYBIT ((odl->item.geometry._hoops_GSAI ^ _hoops_GSAI), Rendo_TRISTRIP_MASK))
			return false;
		//_hoops_RPP (_hoops_CSRI->_hoops_IGCI._hoops_CPAP._hoops_RSRC != _hoops_RSRC)
		//	_hoops_ASRC _hoops_RCPP;
	}

	/* _hoops_ARGH _hoops_AI */
	_hoops_HCI _hoops_RPCP;
	if (ts) {
		_hoops_SRHA = ts->_hoops_SRHA;
		_hoops_CARI = ts->_hoops_CARI;
	}
	_hoops_HRIA(h3ddata, nr, T_FACES,  _hoops_SRHA, _hoops_CARI, &_hoops_RPCP);

	//_hoops_AGCR _hoops_APGR _hoops_CGH _hoops_SHH _hoops_CPHR _hoops_GGR _hoops_IRS _hoops_HAPR _hoops_IS _hoops_PSRC _hoops_IAPR _hoops_HCR _hoops_RH _hoops_AI
	_hoops_SII(_hoops_PHIA, 0, &_hoops_RPCP, null, null, &_hoops_CHRC);
	_hoops_PSR = _hoops_IGIA(matr, _hoops_CHRC, 0);
	if (_hoops_PSR &&
		odl->item.geometry._hoops_HSRC != _hoops_PSR)
		return false;

	return true;
}


/*
 * _hoops_PGAA
 */
bool _hoops_APRC (
		Net_Rendition const &		nr,
		Polyedge const *			pe,
		_hoops_GACR const *		dl,
		H3D_Display_List const *	odl)
{
	H3DData const *				h3ddata = H3DD (nr->_hoops_SRA);
	_hoops_HHA const &	matr = nr->_hoops_RHP->_hoops_CHA;
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	bool 						_hoops_GHRC, _hoops_RHRC, findices;
	bool 						_hoops_AHRC, _hoops_PHRC, _hoops_HHRC;
	bool						_hoops_RARC, _hoops_AARC;
	bool 						_hoops_SPGI;
	unsigned int				_hoops_RHGI;
	int 						_hoops_CHRC;
	int 						_hoops_SRHA = 0;
	int 						_hoops_CARI = 0;

	if (odl->type != H3D_DL_GEOMETRY) {
		_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
			"Unexpected display list type in check_polyedge_display_list_valid");
		return false;
	}
	if (!h3ddata->_hoops_CSC->_hoops_RAIH)
		return true;

	_hoops_AARC = (nr->_hoops_IRR->_hoops_SRI == _hoops_GAI &&
		BIT (nr->transform_rendition->heuristics, _hoops_IRI));
	_hoops_RARC = BIT (dl->_hoops_PRRI, _hoops_HRRI);
	if (_hoops_RARC != _hoops_AARC)
		return false;

	if (dl && dl->_hoops_GSAI == (unsigned int) DL_FLAG_INVALID)
		return false;

	bool _hoops_ISRC = (BIT (nr->_hoops_PSGI, T_EDGES) &&
			nr->_hoops_CPP->_hoops_PRH.style != _hoops_GCPI);
	bool _hoops_RIRC = BIT (odl->item.geometry._hoops_SRHA, DL_HAS_TRANSPARENCY);
	if (_hoops_ISRC != _hoops_RIRC)
		return false;

	if (_hoops_GAPI (nr->_hoops_RHP->line_style) ||
		!BIT(nr->_hoops_RHP->line_style->flags, LSF_SOLID))
		return false;

	if (BIT (odl->item.geometry._hoops_CARI, _hoops_HPII))
		return true;  //_hoops_AAPI _hoops_HS _hoops_PSP _hoops_IRGH _hoops_GPHA _hoops_AIRC, _hoops_HIS _hoops_PIRC _hoops_IIGR _hoops_RH _hoops_RII _hoops_PCGC _hoops_GHAA

	if (BIT (odl->item.geometry._hoops_SRHA, _hoops_CAGI)) {
		if (odl->time_stamp <
			nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR->time_stamp)
			return false;
	}

	_hoops_RHGI = _hoops_RRGH->_hoops_CSA & ~_hoops_AHGI;
	_hoops_SPGI = BIT (_hoops_RRGH->locks.color, Color_FRONT) &&
		 BIT (_hoops_RRGH->locks._hoops_HAA[_hoops_IAA], M_DIFFUSE);
	_hoops_RHRC = (!_hoops_SPGI && BIT (_hoops_RHGI, _hoops_CSRC));
	_hoops_GHRC = BIT (odl->item.geometry._hoops_SRHA, DL_INDEX_INTERPOLATION);
	findices = BIT (odl->item.geometry._hoops_SRHA, DL_COLORS_BY_FINDEX);
	_hoops_HHRC = BIT (odl->item.geometry._hoops_SRHA, DL_VCOLORED_TRISTRIP);

	if (findices && (_hoops_GHRC != _hoops_RHRC))
		return false;
	if (!BIT (odl->item.geometry._hoops_CARI, _hoops_RCRI)) {
		_hoops_PHRC =(!_hoops_SPGI && BIT (_hoops_RHGI, _hoops_SSRC));
		_hoops_AHRC = BIT (odl->item.geometry._hoops_SRHA, DL_COLOR_INTERPOLATION);
		if (_hoops_HHRC && (_hoops_AHRC != _hoops_PHRC))
			return false;
	}

	if (pe) {
		int _hoops_CIRC, _hoops_SIRC, _hoops_GCRC;
		int added, _hoops_RCRC;
		_hoops_CIRC = _hoops_ACRC & ~(
			DL_COLOR_INTERPOLATION |
			DL_INDEX_INTERPOLATION |
			_hoops_SRHH);
		_hoops_SIRC = DL_TEXTURING;
		_hoops_GCRC = (
			_hoops_HCRC |
			_hoops_ICRC);  /* _hoops_PSP _hoops_GGAC _hoops_ARI*/

		// _hoops_ISPR _hoops_CCRC
		added = odl->item.geometry._hoops_SRHA & ~pe->_hoops_SRHA;
		_hoops_RCRC = pe->_hoops_SRHA & ~odl->item.geometry._hoops_SRHA;
		if ((_hoops_RCRC & _hoops_CIRC) != 0)
			return false;
		if ((added & _hoops_CIRC & ~_hoops_SIRC) != 0)
			return false;

		// _hoops_ISPR _hoops_SCRC
		added = odl->item.geometry._hoops_CARI & ~pe->_hoops_CARI;
		_hoops_RCRC = pe->_hoops_CARI & ~odl->item.geometry._hoops_CARI;
		if ((_hoops_RCRC & _hoops_GCRC) != 0)
			return false;
		if ((added & _hoops_GCRC) != 0)
			return false;

		if ((odl->item.geometry._hoops_GSAI & _hoops_RHII) !=
			(pe->_hoops_GSAI & _hoops_RHII))
			return false;
	}
	else {
		if (BIT (nr->_hoops_IRR->_hoops_CSA,
				 (_hoops_RGAC & ~_hoops_AHGI)) &&
			(nr->_hoops_RHP->_hoops_CHA->_hoops_ARIR)) {
			if (!BIT (odl->item.geometry._hoops_SRHA, DL_TEXTURING))
				return false;
		}
		if (!BIT (odl->item.geometry._hoops_CARI, _hoops_RCRI)) {
			if ((odl->item.geometry._hoops_GSAI & _hoops_RHII) !=
				(_hoops_RRGH->_hoops_CSA & _hoops_RHII))
				return false;
		}
	}

	/* _hoops_ARGH _hoops_AI */
	_hoops_HCI _hoops_RPCP;
	if (pe) {
		_hoops_SRHA = pe->_hoops_SRHA;
		_hoops_CARI = pe->_hoops_CARI;
	}
	_hoops_HRIA(h3ddata, nr, T_EDGES, _hoops_SRHA, _hoops_CARI, &_hoops_RPCP);

	//_hoops_AGCR _hoops_APGR _hoops_CGH _hoops_SHH _hoops_CPHR _hoops_GGR _hoops_IRS _hoops_HAPR _hoops_IS _hoops_PSRC _hoops_IAPR _hoops_HCR _hoops_RH _hoops_AI
	_hoops_SII(_hoops_PHIA, 0, &_hoops_RPCP, null, null, &_hoops_CHRC);
	if (odl->item.geometry._hoops_HSRC != _hoops_IGIA(matr, _hoops_CHRC, 0))
		return false;

	return true;
}


bool _hoops_SPRC (
		Net_Rendition const &		nr,
		_hoops_ACHR					_hoops_HRAI,
		_hoops_GACR const *		dl,
		H3D_Display_List const *	odl)
{
	H3DData alter *h3ddata = H3DD (nr->_hoops_SRA);
	_hoops_ICP const &_hoops_CCP = (_hoops_HRAI == T_VERTICES ? nr->_hoops_SCP : nr->_hoops_GSP);
	Integer32 _hoops_AGAC = _hoops_CCP->glyph->key;
	Integer32 _hoops_PGAC = (Integer32) odl->item.geometry._hoops_HGAC;
	bool _hoops_IGAC, _hoops_CGAC;
	bool _hoops_SGAC, _hoops_GRAC;
		
	if (_hoops_AGAC != _hoops_PGAC)
		return false;

	int const _hoops_RRAC = _hoops_ARAC (h3ddata, nr, _hoops_CCP, null, odl, null);

	_hoops_GRAC = BIT (_hoops_RRAC, _hoops_PRAC);
	_hoops_SGAC = BIT (odl->item.geometry._hoops_CARI, DL2_MARKER_POINT_SPRITE);
	if (_hoops_GRAC != _hoops_SGAC)
		return false;

	_hoops_CGAC = BIT (_hoops_RRAC, _hoops_HRAC);
	_hoops_IGAC = BIT (odl->item.geometry._hoops_CARI, DL2_MARKER_CIRCLE);
	if (_hoops_CGAC != _hoops_IGAC)
		return false;

	UNREFERENCED (dl);
	return true;
}


/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_IRAC
*****************************************************************************
*****************************************************************************/



/*****************************************************************************
						_hoops_CRAC
*****************************************************************************/
/*
* _hoops_SRAC
*/
void draw_dc_rgb32_rasters (Net_Rendition const &  nr,
					   DC_Point const * start,
					   DC_Point const * end,
					   int row_bytes, RGBAS32 const * _hoops_GAAC)
{
	H3DData alter *h3ddata = H3DD (nr->_hoops_SRA);
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	int _hoops_RAAC = (int)start->y;
	int width = (int)end->x - (int)start->x + 1;
	int height = (int)start->y - (int)end->y + 1;
	unsigned int size = width*height;
	int dx;
	float _hoops_AAAC;
	DC_Point _hoops_PAAC;
	RGBAS32 const *_hoops_HAAC;
	RGBAS32 const *_hoops_IAAC;
	int _hoops_CAAC = 0;
	_hoops_IAPA const		*_hoops_CAPA = null;
	int flags = H3DID_DC | H3DID_VERTEX_COLORS;
	H3DShader *_hoops_RSR;

	H3D_TRACE(h3ddata, "draw_dc_rgb32_rasters");

	if (0 == row_bytes)
		row_bytes = width * sizeof (RGBAS32);

	dx = (int)end->x - (int)start->x;

	H3DVertexBuffer &_hoops_PAIH = h3ddata->_hoops_CP;
	H3DVertexFormat _hoops_PPCP(H3DVF_PT_CLR);
	H3DVertexBufferCache *_hoops_SAAC;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		_hoops_SSP const &		_hoops_GGH = nr->transform_rendition->_hoops_RGH;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
		}
	}

	// _hoops_SR _hoops_HS _hoops_PGCR _hoops_GPAC _hoops_ARI. _hoops_HSRR _hoops_RPAC _hoops_APAC _hoops_PGAP _hoops_PAH _hoops_PGSA _hoops_PPAC _hoops_PICA,
	// _hoops_SR _hoops_SGH _hoops_RRGR _hoops_CRAA _hoops_PGAP _hoops_SSCP _hoops_IHH _hoops_HPAC _hoops_IPAC. _hoops_GHAP _hoops_GA'_hoops_RA _hoops_HHGC _hoops_SGS _hoops_RRGR _hoops_IS
	// _hoops_HAHA _hoops_CPAC _hoops_PPR _hoops_SPAC _hoops_APAC. _hoops_GHAC _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_RH '_hoops_SHS' _hoops_HPAC _hoops_ARI _hoops_RPP
	// _hoops_RHAC _hoops_CHR _hoops_GPS _hoops_RGR _hoops_AHAC 5 _hoops_PHAC _hoops_SPHR- _hoops_HHAC _hoops_IHAC (3-_hoops_CHAC-04)
	if (size < h3ddata->_hoops_ACGH._hoops_GRGI) {
		// _hoops_AA _hoops_HAR _hoops_SHAC _hoops_GRP _hoops_GPHA _hoops_SRHR _hoops_IHAH _hoops_RPP _hoops_HAH _hoops_CHPP
		if (size < _hoops_GHIH) {
			_hoops_RPIH(h3ddata, H3DVertexFormat(H3DVF_PT_CLR), _hoops_SAAC);
		}
		else {
			_hoops_SAAC = h3ddata->_hoops_GSCR->_hoops_HAIH();
			_hoops_SAAC->CreateVertexBuffer(h3ddata, size, H3DVertexFormat(H3DVF_PT_CLR));
		}
		_hoops_SAAC->Lock(size, &_hoops_PAIH);
		if (dx == 0) {
			while (_hoops_RAAC >= (int)end->y) {
				_hoops_PAIH._hoops_RRCI(_hoops_CAAC)._hoops_AHCP(start->x + 0.5f, _hoops_RAAC + 0.5f, start->z);
				_hoops_PAIH._hoops_RRCI(_hoops_CAAC).color(h3ddata->_hoops_SHAP, *_hoops_GAAC);
				_hoops_CAAC++;

				_hoops_GAAC = (RGBAS32 *) ((unsigned char *) _hoops_GAAC + row_bytes);
				_hoops_RAAC--;
			}
		}
		else {
			_hoops_AAAC = (end->z - start->z) / (float)dx;

			while (_hoops_RAAC >= (int)end->y) {
				_hoops_IAAC = _hoops_GAAC;
				_hoops_HAAC = _hoops_IAAC + dx;
				_hoops_PAAC.x = start->x + 0.5f;
				_hoops_PAAC.y = _hoops_RAAC + 0.5f;
				_hoops_PAAC.z = start->z;

				do {
					_hoops_PAIH._hoops_RRCI(_hoops_CAAC)._hoops_AHCP(_hoops_PAAC);
					_hoops_PAIH._hoops_RRCI(_hoops_CAAC).color(h3ddata->_hoops_SHAP, *_hoops_IAAC);
					_hoops_CAAC++;
					_hoops_PAAC.z += _hoops_AAAC;
					_hoops_PAAC.x++;
				} _hoops_RGGA (_hoops_IAAC++ == _hoops_HAAC);

				_hoops_GAAC = (RGBAS32 *) ((unsigned char *) _hoops_GAAC + row_bytes);
				_hoops_RAAC--;
			}
		}

		_hoops_SAAC->Unlock();

		_hoops_PISP (h3ddata, BIT(_hoops_IHCR->flags, _hoops_PASP));
		ENSURE_DEPTH_MASK (h3ddata, (BIT(_hoops_IHCR->flags, _hoops_PASP) && !BIT(nr->transform_rendition->flags, _hoops_ISH)));
		ENSURE_TRANSPARENCY (h3ddata, !h3ddata->_hoops_RHH.mode &&
			nr->_hoops_CPP->_hoops_PRH._hoops_HRH);
		_hoops_GPRP (h3ddata, (h3ddata->_hoops_SH.mode || h3ddata->_hoops_RHH.mode) ? H3DMASK_RGBA : H3DMASK_RGB);
		_hoops_SSHH (h3ddata, nr, 0, null, flags, &_hoops_RSR);
		_hoops_GIAC (h3ddata, nr, _hoops_RSR);
		do {
			if (_hoops_CAAC) {
				_hoops_GPRH(rasters) += _hoops_CAAC;
				_hoops_SAAC->_hoops_CHSA(h3ddata, H3DPT_POINTLIST, _hoops_CAAC);
			}
			else
				_hoops_SAAC->_hoops_RIAC();

			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);
	}
	else {
		// _hoops_AIAC _hoops_RH _hoops_RPR _hoops_IH _hoops_HAR _hoops_PIAC _hoops_RH _hoops_IGIR - _hoops_HIAC _hoops_CRAA
		size = h3ddata->_hoops_ACGH._hoops_GRGI;
		int rasters = size / width;

		_hoops_SAAC = h3ddata->_hoops_GSCR->_hoops_HAIH();
		_hoops_SAAC->CreateVertexBuffer(h3ddata, size, H3DVertexFormat(H3DVF_PT_CLR));

		_hoops_PISP (h3ddata, BIT(_hoops_IHCR->flags, _hoops_PASP));
		ENSURE_DEPTH_MASK (h3ddata, (BIT(_hoops_IHCR->flags, _hoops_PASP) && !BIT(nr->transform_rendition->flags, _hoops_ISH)));
		ENSURE_TRANSPARENCY (h3ddata, !h3ddata->_hoops_RHH.mode &&
			nr->_hoops_CPP->_hoops_PRH._hoops_HRH);
		_hoops_GPRP (h3ddata, (h3ddata->_hoops_SH.mode || h3ddata->_hoops_RHH.mode) ? H3DMASK_RGBA : H3DMASK_RGB);
		_hoops_SSHH (h3ddata, nr, 0, null, flags, &_hoops_RSR);
		_hoops_GIAC (h3ddata, nr, _hoops_RSR);

		do {
			_hoops_SAAC->Lock(size, &_hoops_PAIH);
			if (dx == 0) {
				while (_hoops_RAAC >= (int)end->y) {
					_hoops_PAIH._hoops_RRCI(_hoops_CAAC)._hoops_AHCP(start->x + 0.5f, _hoops_RAAC + 0.5f, start->z);
					_hoops_PAIH._hoops_RRCI(_hoops_CAAC).color(h3ddata->_hoops_SHAP, *_hoops_GAAC);
					_hoops_CAAC++;

					_hoops_GAAC = (RGBAS32 *) ((unsigned char *) _hoops_GAAC + row_bytes);
					_hoops_RAAC--;
				}
			}
			else {
				_hoops_AAAC = (end->z - start->z) / (float)dx;

				while (1) {
					_hoops_IAAC = _hoops_GAAC;
					_hoops_HAAC = _hoops_IAAC + dx;
					_hoops_PAAC.x = start->x + 0.5f;
					_hoops_PAAC.y = _hoops_RAAC + 0.5f;
					_hoops_PAAC.z = start->z;

					do {
						_hoops_PAIH._hoops_RRCI(_hoops_CAAC)._hoops_AHCP(_hoops_PAAC);
						_hoops_PAIH._hoops_RRCI(_hoops_CAAC).color(h3ddata->_hoops_SHAP, *_hoops_IAAC);
						_hoops_CAAC++;
						_hoops_PAAC.z += _hoops_AAAC;
						_hoops_PAAC.x++;
					} _hoops_RGGA (_hoops_IAAC++ == _hoops_HAAC);

					if (_hoops_RAAC < (int)end->y)
						break;
					else if (_hoops_CAAC == rasters*width) {
						_hoops_SAAC->Unlock();
						_hoops_GPRH(rasters) += _hoops_CAAC;
						_hoops_SAAC->_hoops_CHSA(h3ddata, H3DPT_POINTLIST, _hoops_CAAC);
						_hoops_SAAC->Lock(size, &_hoops_PAIH);
						_hoops_CAAC=0;
					}

					_hoops_GAAC = (RGBAS32 *) ((unsigned char *) _hoops_GAAC + row_bytes);
					_hoops_RAAC--;
				}

			}

			_hoops_SAAC->Unlock();
			if (_hoops_CAAC) {
				_hoops_GPRH(rasters) += _hoops_CAAC;
				_hoops_SAAC->_hoops_CHSA(h3ddata, H3DPT_POINTLIST, _hoops_CAAC);
			}
			else
				_hoops_SAAC->_hoops_RIAC();

			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);
	}


	// _hoops_HSCI _hoops_RH _hoops_GPHA _hoops_SRHR _hoops_IHAH _hoops_RPP _hoops_RGR _hoops_CSAP _hoops_IRGH _hoops_SPR _hoops_SR _hoops_IIAC
	if (size >= _hoops_GHIH)
		delete _hoops_SAAC;


}


/*****************************************************************************
						_hoops_CIAC
*****************************************************************************/
/*
 * _hoops_SRAC
 */
void draw_dc_rectangle (
		Net_Rendition const & nr,
		int left,
		int right,
		int bottom,
		int top)
{
	H3DData alter *h3ddata = H3DD (nr->_hoops_SRA);
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	H3DVertexBufferCache *_hoops_HACP = 0;
	Int_Rectangle const &_hoops_GPHH = _hoops_IHCR->_hoops_AGAA;
	int flags = H3DID_DC;

	H3DShader *_hoops_RSR;

	//_hoops_PRPP _hoops_SIAC _hoops_ACPP _hoops_HIS _hoops_SGS _hoops_GCAC _hoops_HCPH _hoops_CHR _hoops_RCAC _hoops_IS _hoops_SSS
	H3D_TRACE(h3ddata, "draw_dc_rectangle");

	if (_hoops_SIGA->pattern == FP_USER_DEFINED) {
	    HD_Std_DC_Rectangle (nr, left, right, bottom, top);
	    return;
	}

	/*_hoops_ACAC _hoops_PCAC _hoops_HPPA _hoops_IPPA _hoops_HIHP _hoops_CGPR _hoops_HIHP _hoops_SHPH*/
	h3ddata->_hoops_HCAC = _hoops_CCC;
	h3ddata->_hoops_ICAC = _hoops_CCC;

	//_hoops_CCAC _hoops_SCAC
	H3DVertexFormat _hoops_PPCP(H3DVF_PT);
	H3DVertexBuffer &_hoops_PAIH = h3ddata->_hoops_CP;

	_hoops_RPIH (h3ddata, _hoops_PPCP, _hoops_HACP);
	_hoops_HACP->Lock(4, &_hoops_PAIH);
	_hoops_PAIH._hoops_AHCP(left, bottom, 0);
	_hoops_PAIH._hoops_CPPH();
	_hoops_PAIH._hoops_AHCP(left, top+1, 0);
	_hoops_PAIH._hoops_CPPH();
	_hoops_PAIH._hoops_AHCP(right+1, bottom, 0);
	_hoops_PAIH._hoops_CPPH();
	_hoops_PAIH._hoops_AHCP(right+1, top+1, 0);
	_hoops_PAIH._hoops_CPPH();
	_hoops_HACP->Unlock();

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		_hoops_AGPH((Display_Context alter *) nr->_hoops_SRA, nr->_hoops_IHA->pattern, 0);
		h3ddata->_hoops_GSCR->_hoops_GSAC(nr, 0, _hoops_RSAC, h3ddata->_hoops_SRPH[nr->_hoops_IHA->pattern], 0);

		flags |= H3DID_FACE_PATTERN;
	}

	flags |= H3DID_WRITE_LUMINANCE;
	_hoops_AGSP (h3ddata, nr->transform_rendition, false);
	_hoops_SSHH (h3ddata, nr, T_FACES, null, flags, &_hoops_RSR);
	_hoops_GPRP (h3ddata, H3DMASK_RGBA);
	_hoops_GIAC (h3ddata, nr, _hoops_RSR);
	_hoops_AHSA (h3ddata, nr, T_FACES, _hoops_RSR);
	_hoops_HPHH (h3ddata, true);
	ENSURE_SCISSOR_SET (h3ddata, _hoops_GPHH.left, _hoops_GPHH.bottom, _hoops_GPHH.right, _hoops_GPHH.top);
	_hoops_APHH(h3ddata, 1, 1);
	_hoops_PISP (h3ddata, false);
	ENSURE_DEPTH_MASK (h3ddata, false);
	_hoops_HISP (h3ddata, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
	// _hoops_PS _hoops_RRP _hoops_IS _hoops_HHSA _hoops_IHSP _hoops_PSAP, _hoops_HIS _hoops_ASAC _hoops_RH _hoops_RGSR _hoops_HIS _hoops_SR _hoops_PAH _hoops_PHIH _hoops_SCH _hoops_SPHR
	bool _hoops_PSAC = h3ddata->_hoops_CSC->_hoops_HSAC;
	ENSURE_TRANSPARENCY(h3ddata, false);
	_hoops_RHSA (h3ddata, H3DCULL_NONE);
	_hoops_IPGP(h3ddata, false);

	_hoops_HACP->_hoops_CHSA(h3ddata, H3DPT_TRIANGLESTRIP, 2);


	ENSURE_TRANSPARENCY(h3ddata, _hoops_PSAC);
}


/*****************************************************************************
						_hoops_ISAC
*****************************************************************************/
#include "circle_data.h"
local unsigned char *_hoops_CSAC (
		int first,
		int _hoops_SSAC,
		unsigned char const *_hoops_GGPC,
		int _hoops_RGPC)
{
	int count = _hoops_SSAC - first + 1;
	int i, j, k, _hoops_HGII;
	unsigned char *data;
	unsigned char const *ptr = _hoops_GGPC;
	int x = 0, y = 1;

	ALLOC_ARRAY (data, 4*_hoops_RGPC*_hoops_RGPC, unsigned char);
	SET_MEMORY (data, 4*_hoops_RGPC*_hoops_RGPC, 0x00);
	for (k = 0; k < count; k++) {
		_hoops_HGII = first + k;
		x++;
		if (_hoops_HGII > 1) {
			for (i = 0; i < _hoops_HGII; i++) {
				for (j = 0; j < _hoops_HGII; j++) {
					data [3 + 4*(((y+i)*_hoops_RGPC)+(x+j))] = *ptr++;
				}
			}
		}
		else {
			/* _hoops_RAAA == 1 _hoops_HRGR _hoops_GIR _hoops_GAR _hoops_IRS _hoops_GRH _hoops_AGIR, _hoops_SAHR _hoops_IRS _hoops_RSRA
			 * _hoops_AGPC-_hoops_PGPC _hoops_PPPR (_hoops_CCA _hoops_IRS _hoops_HGPC _hoops_CAPP) */
			data [3 + 4*((y*_hoops_RGPC)+x)] = 0xff;
		}
		/* _hoops_GGI _hoops_RH _hoops_AIIR _hoops_IGPC _hoops_IIGR _hoops_HCR _hoops_RH _hoops_CGPC _hoops_GGR _hoops_IRS 1-_hoops_PPPR _hoops_HGPC
		 * _hoops_AARI _hoops_RH _hoops_SGPC.  _hoops_IPCP _hoops_AIAA _hoops_GRPC _hoops_HGCR _hoops_PHPH _hoops_RRPC, _hoops_HIH
		 * _hoops_SGS _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_IRS _hoops_ARPC */
		for (i = -1; i < _hoops_HGII+1; i++) {
			data [3 + 4*(((y+i)*_hoops_RGPC)+(x-1))] = 0;   //_hoops_RAAP
			data [3 + 4*(((y+i)*_hoops_RGPC)+(x+_hoops_HGII))] = 0; //_hoops_RPHR
			data [3 + 4*(((y-1)*_hoops_RGPC)+(x+i))] = 0;   //_hoops_PRPC
			data [3 + 4*(((y+_hoops_HGII)*_hoops_RGPC)+(x+i))] = 0; //_hoops_SCIA
		}
		x += _hoops_HGII + 1;
	}
	return data;
}

local void _hoops_HRPC(H3DData alter *h3ddata)
{
	int _hoops_IRPC = H3D_LARGEST_PRECOMPUTED_CIRCLE;
	int _hoops_HGII = H3D_LINE_TOOLS_SIZE;
	int i, x, y;

	h3ddata->_hoops_GSCR->CreateTexture(_hoops_HGII, _hoops_HGII, 1, H3DTEXUSAGE_DEFAULT, H3DFMT_A8R8G8B8, &h3ddata->_hoops_HSI.texture);
	h3ddata->_hoops_HSI.data_size = _hoops_HGII * _hoops_HGII;
	h3ddata->_hoops_HSI.data = _hoops_CSAC (1, _hoops_IRPC, _hoops_CRPC, _hoops_HGII);
	x = 0;
	h3ddata->_hoops_HSI._hoops_ACAA[0] = 0;
	for (i = 1; i <= _hoops_IRPC; i++) {
		h3ddata->_hoops_HSI._hoops_ACAA[i] = (float)x / H3D_LINE_TOOLS_SIZE;
		x += i+2;
	}

	unsigned char* _hoops_SISA;
	h3ddata->_hoops_HSI.texture->Lock(null, &_hoops_SISA);
	for (y = 0; y < _hoops_HGII; y++) {
		for (x = 0; x < _hoops_HGII; x++) {
			*_hoops_SISA++ = h3ddata->_hoops_HSI.data[(y*_hoops_HGII+x)*4+0];
			*_hoops_SISA++ = h3ddata->_hoops_HSI.data[(y*_hoops_HGII+x)*4+1];
			*_hoops_SISA++ = h3ddata->_hoops_HSI.data[(y*_hoops_HGII+x)*4+2];
			*_hoops_SISA++ = h3ddata->_hoops_HSI.data[(y*_hoops_HGII+x)*4+3];
		}
	}
	h3ddata->_hoops_HSI.texture->Unlock();
	h3ddata->_hoops_HSI.valid = true;
}

/* _hoops_SRPR _hoops_IPIH _hoops_SIGR.

_hoops_IRGH _hoops_SRPC _hoops_GAPC(_hoops_RR _hoops_RAPC *_hoops_RRAP)
{
	_hoops_SCSH _hoops_AAPC = _hoops_PAPC;
	_hoops_SCSH _hoops_SISR, _hoops_HAPC;

	_hoops_RRAP->_hoops_ICRI->_hoops_IAPC(_hoops_AAPC, _hoops_AAPC, 0, _hoops_CAPC, _hoops_SAPC, &_hoops_RRAP->_hoops_GPPC._hoops_RPPC);
	_hoops_IH (_hoops_SCSH _hoops_HAS = 0; _hoops_HAS < 8; ++_hoops_HAS)
	{
		_hoops_APPC _hoops_GSPR* _hoops_PPPC;
		_hoops_RPP (_hoops_RRAP->_hoops_GPPC._hoops_RPPC->_hoops_HRAH(_hoops_IRAP, _hoops_HAS, (_hoops_SRPC**)&_hoops_PPPC)) {
			_hoops_IH (_hoops_HAPC = 0; _hoops_HAPC < _hoops_AAPC; _hoops_HAPC++) {
				_hoops_IH (_hoops_SISR = 0; _hoops_SISR < _hoops_AAPC; _hoops_SISR++) {
					_hoops_APPC _hoops_GSPR _hoops_HPPC = (_hoops_SISR*_hoops_SISR + _hoops_HAPC*_hoops_HAPC) < (_hoops_AAPC*_hoops_AAPC) ? 255u : 0;
					*_hoops_PPPC++ = _hoops_HPPC;
					*_hoops_PPPC++ = _hoops_HPPC;
					*_hoops_PPPC++ = _hoops_HPPC;
					*_hoops_PPPC++ = _hoops_HPPC;
				}
			}
			_hoops_RRAP->_hoops_GPPC._hoops_RPPC->_hoops_IPPC();
		}
		_hoops_AAPC = _hoops_AAPC >> 1;
	}
	_hoops_RRAP->_hoops_GPPC._hoops_APIP = _hoops_IHPR;
}

*/


// _hoops_AGCR _hoops_CPPC _hoops_PIHA _hoops_PSSP _hoops_PCPA _hoops_HRGR _hoops_GGR _hoops_SPPC._hoops_GHPC
#define H3D_ROUND	1
#define H3D_SQUARE	2
#define H3D_MITER	3

#define H3DCAP_ISDC					0x01
#define H3DCAP_NO_MITER_NEXT		0x02
#define H3DCAP_NO_MITER_PREV		0x04

/* _hoops_HGI _hoops_AGSR _hoops_SGS _hoops_RH *_hoops_RSSA _hoops_RHPC _hoops_GGR _hoops_AHPC _hoops_HRGR _hoops_PHPC _hoops_IS _hoops_RH _hoops_SCGR _hoops_PPSR
 * _hoops_HHPC, _hoops_SCH'_hoops_GRI _hoops_PHPC _hoops_IS _hoops_RH _hoops_RSGI _hoops_IIGR _hoops_RH _hoops_RSSA _hoops_CRPR
 */
#define H3DCAP_USE_CURRENT_POINT	0x08
#define H3DCAP_FIRST_POINT			0x10
#define H3DCAP_LAST_POINT			0x20

void _hoops_IHPC (
		Net_Rendition const & nr,
		Line_Rendition const & _hoops_GHP,
		Polyedge const *pe,
		Point const *points,
		H3DVertexBuffer *_hoops_PAIH,
		H3DIndexBuffer *_hoops_CHPC,
		_hoops_HCI *_hoops_RPCP,
		_hoops_HRPA const *matrix,
		RGB const *_hoops_GPCP,
		int *index,
		int i,
		int start,
		int end,
		int _hoops_SHPC,
		bool _hoops_GIPC,
		unsigned int _hoops_RIPC)
{
	Display_Context const *dc = nr->_hoops_SRA;
	H3DData alter *h3ddata = H3DD (dc);
	int _hoops_AIPC = 0, _hoops_PIPC = 0, _hoops_HIPC = 0, _hoops_IIPC = 0;
	float _hoops_ICCP = 0;
	int _hoops_CIPC = 0;
	int _hoops_HSPI, _hoops_ISPI, _hoops_CSPI;
	bool _hoops_SIPC = (!BIT(_hoops_RIPC, H3DCAP_ISDC) && _hoops_GHP == nr->_hoops_RHP);
	int weight = _hoops_GHP->weight;
	if (weight < 0)
		weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP,1.0f, false, 0, true)+0.5f);

	if (weight <= 2)
		return;

	_hoops_SII(_hoops_CHRR, 0, _hoops_RPCP, &_hoops_AIPC, null, null);
	_hoops_SII(_hoops_SHRR, 0, _hoops_RPCP, &_hoops_PIPC, null, null);
	_hoops_SII(_hoops_IHRR, 0, _hoops_RPCP, &_hoops_HIPC, null, null);
	if (h3ddata->_hoops_AIC) {
		_hoops_SII(_hoops_ACPR, 0, _hoops_RPCP, &_hoops_IIPC, null, null);
		if (pe->_hoops_CCCP)
			_hoops_ICCP = pe->_hoops_CCCP[0];
		else if (pe->_hoops_GSCP)
			_hoops_ICCP = pe->_hoops_GSCP->priority;
		else
			_hoops_ICCP = dc->_hoops_RAI->priority;
	}

	if (BIT(_hoops_RIPC, H3DCAP_USE_CURRENT_POINT)) {
		_hoops_HSPI = -1;
		_hoops_ISPI = 0;
		_hoops_CSPI = 1;

		if (BIT(_hoops_RIPC, H3DCAP_FIRST_POINT))
			_hoops_HSPI = 0;
		if (BIT(_hoops_RIPC, H3DCAP_LAST_POINT))
			_hoops_CSPI = 0;
	}
	else {
		_hoops_HSPI = (i == start) ? end-2 : i-1;			// _hoops_GCPC _hoops_PPSR
		_hoops_ISPI = i;										// _hoops_SCGR _hoops_PPSR
		_hoops_CSPI = (i == end-1) ? start+1 : i+1;			// _hoops_SPS _hoops_PPSR

		if (pe && pe->_hoops_AIHA) {
			/* _hoops_HHHA _hoops_PSPI */
			_hoops_HSPI = pe->_hoops_AIHA[_hoops_HSPI];
			_hoops_ISPI = pe->_hoops_AIHA[_hoops_ISPI];
			_hoops_CSPI = pe->_hoops_AIHA[_hoops_CSPI];
		}
	}

	Point _hoops_RCPC, point1, point2;
	if (matrix) {
		_hoops_RCPC.x = _hoops_HPRA(matrix->elements, points[_hoops_HSPI]);
		_hoops_RCPC.y = _hoops_IPRA(matrix->elements, points[_hoops_HSPI]);
		_hoops_RCPC.z = _hoops_CPRA(matrix->elements, points[_hoops_HSPI]);
		point1.x = _hoops_HPRA(matrix->elements, points[_hoops_ISPI]);
		point1.y = _hoops_IPRA(matrix->elements, points[_hoops_ISPI]);
		point1.z = _hoops_CPRA(matrix->elements, points[_hoops_ISPI]);
		point2.x = _hoops_HPRA(matrix->elements, points[_hoops_CSPI]);
		point2.y = _hoops_IPRA(matrix->elements, points[_hoops_CSPI]);
		point2.z = _hoops_CPRA(matrix->elements, points[_hoops_CSPI]);
	}
	else {
		_hoops_RCPC = points[_hoops_HSPI];
		point1 = points[_hoops_ISPI];
		point2 = points[_hoops_CSPI];
	}

	// _hoops_RGPA _hoops_ACPC/_hoops_PCPC _hoops_RPP _hoops_IRPR
	if (!_hoops_GIPC && !_hoops_SIPC) {
		if (i == start)
			_hoops_CIPC = (_hoops_GHP->style & LCAP_START_MASK);
		else if (i == end - 1) {
			_hoops_CIPC = (_hoops_GHP->style & LCAP_END_MASK);
			if (_hoops_CIPC == LCAP_END_BUTT)
				return;

			if (!_hoops_CIPC)
				_hoops_CIPC = (_hoops_GHP->style & LCAP_START_MASK);

			if (_hoops_CIPC == LCAP_BUTT)
				return;

			// _hoops_ISPR _hoops_CGHI _hoops_PPSR _hoops_HCPC 1_hoops_ICPC _hoops_PPSR _hoops_IS _hoops_CACH _hoops_RPP _hoops_SSIA'_hoops_ASAR _hoops_RH _hoops_PSHR
			// _hoops_RPP _hoops_SSIA _hoops_CHR, _hoops_HSII _hoops_GAR _hoops_IRS _hoops_PCPC
			if (!_hoops_CIPC && _hoops_GIPC)
				_hoops_CIPC = (_hoops_GHP->style & LJOIN_MASK);
		}
		else
			_hoops_CIPC = (_hoops_GHP->style & LJOIN_MASK);
	}
	else
		_hoops_CIPC = (_hoops_GHP->style & LJOIN_MASK);


	// _hoops_CCPC
	// _hoops_HSRR _hoops_HHH _hoops_SCPC, _hoops_RPP _hoops_SR'_hoops_RISP _hoops_PPP _hoops_RH _hoops_GSPC _hoops_PPR _hoops_GA'_hoops_RA _hoops_RSPC _hoops_SCH, _hoops_HIPH _hoops_HGCR _hoops_ASPC.
	// _hoops_PSPC, _hoops_SR _hoops_HSPC _hoops_SCH _hoops_IS _hoops_HHH _hoops_ISPC _hoops_PIH _hoops_IS _hoops_CRHR _hoops_SGS.
	if (_hoops_PIPC > 0)
		_hoops_PAIH->_hoops_IICP(point1.x+123,point1.y-123,point1.z, _hoops_PIPC);

	// _hoops_PGPR _hoops_GIP _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_GGR _hoops_RH _hoops_IRGP _hoops_IIGR _hoops_RH _hoops_III _hoops_PAR _hoops_CSPC
	// _hoops_HIPR, _hoops_SSPC _hoops_GIP _hoops_RPP _hoops_GII _hoops_IIGR _hoops_RH _hoops_RSSA _hoops_CHR _hoops_RH _hoops_PSHR (_hoops_PAH _hoops_GGHC _hoops_RGHC _hoops_APGR)
	if (!_hoops_SIPC &&
		(_hoops_ISPI != start || _hoops_GIPC) &&
		(_hoops_ISPI != end-1 || _hoops_GIPC) &&
		_hoops_CIPC == LJOIN_MITER &&
		_hoops_RCPC != point1 && point1 != point2) {


		// _hoops_CIPH _hoops_RH _hoops_PIH
		_hoops_PAIH->_hoops_AHCP(point1.x, point1.y, point1.z);

		// _hoops_GGCR _hoops_GHCP _hoops_PIRA
		if (h3ddata->_hoops_AIC) {
			if (pe->_hoops_CCCP) {
				//_hoops_RPP _hoops_GPRI, _hoops_HCR _hoops_GPHA _hoops_AGHC _hoops_GIAA _hoops_IRS _hoops_CGGR _hoops_CGH _hoops_SHH _hoops_RH _hoops_PSHR
				ASSERT (pe->_hoops_CCCP[_hoops_HSPI] == pe->_hoops_CCCP[_hoops_ISPI]); 
				_hoops_PAIH->u(pe->_hoops_CCCP[_hoops_HSPI], _hoops_IIPC);
			}
			else
				_hoops_PAIH->u(_hoops_ICCP, _hoops_IIPC);
		}

		// _hoops_GGCR _hoops_SPS _hoops_PPSR
		if (i == end - 1 && !_hoops_GIPC) {
			//_hoops_IIH _hoops_HRGR _hoops_PSP _hoops_SPS _hoops_PPSR -- _hoops_ARPR _hoops_IRS _hoops_RSPH _hoops_SPR
			_hoops_PAIH->_hoops_IICP(2*point1.x - _hoops_RCPC.x,
					  2*point1.y - _hoops_RCPC.y,
					  2*point1.z - _hoops_RCPC.z,
					  _hoops_AIPC);
		}
		else
			_hoops_PAIH->_hoops_IICP(point2.x, point2.y, point2.z, _hoops_AIPC);

		// _hoops_GGCR _hoops_PGHC _hoops_PPSR
		if (i == 0 && !_hoops_GIPC) {
			//_hoops_IIH _hoops_HRGR _hoops_PSP _hoops_PGHC _hoops_PPSR -- _hoops_ARPR _hoops_IRS _hoops_RSPH _hoops_SPR
			_hoops_PAIH->_hoops_IICP(2*point1.x - point2.x,
					  2*point1.y - point2.y,
					  2*point1.z - point2.z,
					  _hoops_PIPC);
		}
		else
			_hoops_PAIH->_hoops_IICP(_hoops_RCPC.x, _hoops_RCPC.y, _hoops_RCPC.z, _hoops_PIPC);

		_hoops_PAIH->t(H3D_MITER, _hoops_HIPC);
		_hoops_PAIH->_hoops_RRCI(0)._hoops_IICP(+1,+1,+1, _hoops_HIPC);
		_hoops_PAIH->_hoops_CPPH();


		// _hoops_HA _hoops_SR _hoops_HS _hoops_RH _hoops_PGCR _hoops_RSSA _hoops_GGR _hoops_HGHC, _hoops_SAHR _hoops_RRP _hoops_IS _hoops_ARP _hoops_GH _hoops_IGHC
		if (!BIT(_hoops_RIPC, H3DCAP_NO_MITER_PREV) && i > start) {
			(*_hoops_CHPC)[0] = *index;
			(*_hoops_CHPC)[1] = *index - 2;
			(*_hoops_CHPC)[2] = *index - 1;
			(*_hoops_CHPC) += 3;
		}
		if (!BIT(_hoops_RIPC, H3DCAP_NO_MITER_NEXT) && i < end - 1) {
			(*_hoops_CHPC)[0] = *index;
			(*_hoops_CHPC)[1] = *index + 1;
			(*_hoops_CHPC)[2] = *index + 2;
			(*_hoops_CHPC) += 3;
		}

		*index += 1;
	}
	if (!_hoops_SIPC && _hoops_CIPC == LJOIN_BEVEL) {
		if (i == end - 1) {
			//_hoops_SR _hoops_RRP _hoops_IS _hoops_PCPC _hoops_RH _hoops_SRS _hoops_PPSR _hoops_CCA _hoops_RH _hoops_CGHI _hoops_SPR
			(*_hoops_CHPC)[0] = *index - 2;
			(*_hoops_CHPC)[1] = *index - 1;
			(*_hoops_CHPC)[2] = 0;
			(*_hoops_CHPC)[3] = *index - 1;
			(*_hoops_CHPC)[4] = 0;
			(*_hoops_CHPC)[5] = 1;
			(*_hoops_CHPC) += 6;
		}
		else if (i > 0) {
			// _hoops_CISA _hoops_GGR _hoops_CGHC _hoops_GAPA _hoops_PGCR _hoops_III _hoops_SGHC
			(*_hoops_CHPC)[0] = *index - 2;
			(*_hoops_CHPC)[1] = *index - 1;
			(*_hoops_CHPC)[2] = *index + 0;
			(*_hoops_CHPC)[3] = *index - 1;
			(*_hoops_CHPC)[4] = *index + 1;
			(*_hoops_CHPC)[5] = *index + 0;
			(*_hoops_CHPC) += 6;
		}
	}
	else if (_hoops_SIPC || _hoops_CIPC != 0)
	{
		if (BIT(_hoops_RIPC, H3DCAP_ISDC)) {
			_hoops_PAIH->_hoops_AHCP(point1);

			//_hoops_GRHC _hoops_RH _hoops_PCPC _hoops_RRHC _hoops_RH _hoops_SPS _hoops_PPSR (_hoops_PAR _hoops_GCPC _hoops_PPSR, _hoops_GPGA)
			if (i < end - 1)
				_hoops_PAIH->_hoops_IICP(point2.x, point2.y, point2.z, _hoops_AIPC);
			else
				_hoops_PAIH->_hoops_IICP(_hoops_RCPC.x, _hoops_RCPC.y, _hoops_RCPC.z, _hoops_AIPC);
		}
		else {
			_hoops_PACP(nr, pe, _hoops_GHP, _hoops_PAIH, 0, _hoops_ISPI, _hoops_SHPC, matrix, _hoops_GPCP, _hoops_RPCP);

			if (i < end - 1)
				_hoops_PAIH->_hoops_IICP(point2.x, point2.y, point2.z, _hoops_AIPC);
			else
				_hoops_PAIH->_hoops_IICP(_hoops_RCPC.x, _hoops_RCPC.y, _hoops_RCPC.z, _hoops_AIPC);
		}
		_hoops_PAIH->t(H3D_SQUARE, _hoops_HIPC);
		if (!_hoops_SIPC && ANYBIT(_hoops_CIPC, LCAP_TRIANGLE|LCAP_END_TRIANGLE)) {
			_hoops_PAIH->_hoops_RRCI(0)._hoops_ARHC(0,-1, _hoops_HIPC);
			_hoops_PAIH->_hoops_CPPH();

			if (i == start) {
				(*_hoops_CHPC)[0] = *index;
				(*_hoops_CHPC)[1] = *index + 1;
				(*_hoops_CHPC)[2] = *index + 2;
			}
			else {
				(*_hoops_CHPC)[0] = *index;
				(*_hoops_CHPC)[1] = *index - 1;
				(*_hoops_CHPC)[2] = *index - 2;
			}
			(*_hoops_CHPC) += 3;
			*index += 1;
		}
		else {
			if (_hoops_SIPC || ANYBIT(_hoops_CIPC, LJOIN_ROUND|LCAP_ROUND|LCAP_END_ROUND)) {
				_hoops_PAIH->s(0.05f + 2/weight, _hoops_HIPC);		//_hoops_IRHH _hoops_RH _hoops_PRHC _hoops_RPPR _hoops_HRHC
				_hoops_PAIH->t(H3D_ROUND, _hoops_HIPC);	//_hoops_IRHC _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_GIRR _hoops_PCPC (_hoops_APRI _hoops_ASPA _hoops_RPP _hoops_AIIR < 0.5)
			}

			_hoops_PAIH->_hoops_RRCI(0)._hoops_AHIH(1);
			_hoops_PAIH->_hoops_RRCI(0)._hoops_AHIH(2);
			_hoops_PAIH->_hoops_RRCI(0)._hoops_AHIH(3);
			_hoops_PAIH->_hoops_RRCI(0)._hoops_ARHC(+1,-1, _hoops_HIPC);
			_hoops_PAIH->_hoops_RRCI(1)._hoops_ARHC(-1,-1, _hoops_HIPC);
			_hoops_PAIH->_hoops_RRCI(2)._hoops_ARHC(+1,+1, _hoops_HIPC);
			_hoops_PAIH->_hoops_RRCI(3)._hoops_ARHC(-1,+1, _hoops_HIPC);

			_hoops_PAIH->_hoops_CPPH(4);

			(*_hoops_CHPC)[0] = *index;
			(*_hoops_CHPC)[1] = *index + 1;
			(*_hoops_CHPC)[2] = *index + 2;
			(*_hoops_CHPC)[3] = *index + 1;
			(*_hoops_CHPC)[4] = *index + 3;
			(*_hoops_CHPC)[5] = *index + 2;
			(*_hoops_CHPC) += 6;
			*index += 4;
		}
	}
}


/*
* _hoops_SRAC
*/
void draw_dc_gouraud_polyline (
		Net_Rendition const &  nr,
		int _hoops_CRHC,
		DC_Point const *_hoops_SRHC,
		RGBAS32 const *_hoops_GAHC)
{
	Display_Context const *dc = nr->_hoops_SRA;
	H3DData alter *h3ddata = H3DD (dc);
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	H3DShader *_hoops_RSR;
	H3DVertexBufferCache *_hoops_HACP;
	H3DVertexBuffer &_hoops_PAIH = h3ddata->_hoops_CP;
	H3DIndexBufferCache *_hoops_RAHC;
	H3DIndexBuffer _hoops_CHPC, _hoops_AAHC;
	short *_hoops_PAHC;
	_hoops_IAPA const *_hoops_CAPA = null;
	int _hoops_RRC, _hoops_HAHC, i;
	DC_Point const *points = _hoops_SRHC;
	int count = _hoops_CRHC;
	int flags = H3DID_DC;
	bool _hoops_IAHC = false;
	bool _hoops_GIPC = false;		//_hoops_IGH _hoops_PAR _hoops_HAR _hoops_ISII _hoops_HRGR _hoops_IRS _hoops_CAHC _hoops_HAPR
	H3DVertexFormat _hoops_PPCP;
	int _hoops_RRSA, _hoops_RGSA;
	_hoops_HCI _hoops_RPCP;
	float _hoops_ICCP = 0;
	int _hoops_PIPC, _hoops_AIPC, _hoops_HIPC, _hoops_SAHC, _hoops_IIPC;

	if (BIT(_hoops_HC->flags, _hoops_SRPI) ||
		ANYBIT(_hoops_HC->line_style->flags, LSF_COMPLEX_ANYBITS) ||
		!BIT(_hoops_HC->line_style->flags, LSF_SOLID) ||
		_hoops_HC->weight > H3D_LARGEST_PRECOMPUTED_CIRCLE) {
		_hoops_IAHC = true;
	}

	if (_hoops_IAHC) {
		if (_hoops_GAHC)
			HD_Std_DC_Gouraud_Polyline (nr, count, points, _hoops_GAHC);
		else
			HD_Std_DC_Polyline (nr, count, points);
		return;
	}

	if (!_hoops_HPCA(nr, _hoops_CAPA)) {
		HD_Clip_DC_Polyline (nr, _hoops_CRHC, _hoops_SRHC, 0,0,0,0,0,0, _hoops_GPHC);
		return;
	}


	H3D_TRACE(h3ddata, "draw_dc_polyline");

	h3ddata->_hoops_AIC = (
		nr->_hoops_IRR->_hoops_SRI == _hoops_GAI &&
		BIT (nr->transform_rendition->heuristics, _hoops_IRI));

	if (h3ddata->_hoops_AIC)
		_hoops_ICCP = _hoops_SCCP (dc->_hoops_RAI->priority, 0);

	if (_hoops_GAHC) {
		flags |= H3DID_VERTEX_COLORS;
		_hoops_PPCP._hoops_RPHC();
	}

	if (h3ddata->_hoops_II.mode)
		_hoops_PPCP._hoops_APHC();

	SET_MEMORY(&_hoops_RPCP, sizeof(_hoops_HCI), 0);
	_hoops_HRIA(h3ddata, nr, T_LINES, 0, 0, &_hoops_RPCP);
	_hoops_SII(_hoops_SHRR, 0, &_hoops_RPCP, &_hoops_PIPC, null, null);
	_hoops_SII(_hoops_CHRR, 0, &_hoops_RPCP, &_hoops_AIPC, null, null);
	_hoops_SII(_hoops_IHRR, 0, &_hoops_RPCP, &_hoops_HIPC, null, null);
	_hoops_SII(_hoops_ACPR, 0, &_hoops_RPCP, &_hoops_IIPC, null, null);

	bool const _hoops_PPHC = (BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP) ||
		(_hoops_HC->weight > 1 && ANYBIT(_hoops_HC->style, LJOIN_ROUND|LCAP_ROUND|LCAP_END_ROUND)));

	flags = _hoops_SRSP(h3ddata, nr, T_LINES, _hoops_PPHC || nr->_hoops_CPP->_hoops_PRH._hoops_HRH, 0, flags);

	// _hoops_CHPR _hoops_GGR _hoops_RPR, _hoops_HIS _hoops_SR _hoops_PAH _hoops_SRCH _hoops_GHGA _hoops_HPHC _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_IPHC _hoops_SGHC (_hoops_HHHR _hoops_RPR)
	if (_hoops_HC->weight > 1 ||
		h3ddata->_hoops_IHP ||
		BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP))
		_hoops_CPHC(h3ddata, nr, T_LINES, null, count, flags, &_hoops_RSR);
	else
		_hoops_SSHH (h3ddata, nr, T_LINES, null, flags, &_hoops_RSR);

	if (_hoops_PPHC) {
		_hoops_SII(_hoops_IHRR, 0, &_hoops_RPCP, null, null, &_hoops_SAHC);
		if (!h3ddata->_hoops_HSI.valid)
			_hoops_HRPC (h3ddata);

		_hoops_RSR->_hoops_GGIR();
		h3ddata->_hoops_GSCR->_hoops_GSAC (nr, null, _hoops_SPHC, h3ddata->_hoops_HSI.texture, _hoops_SAHC);
	}
	_hoops_GHHC (h3ddata, nr, _hoops_HC, _hoops_RSR);
	_hoops_GIAC (h3ddata, nr, _hoops_RSR);
	_hoops_RSR->_hoops_GIHR (&_hoops_HC->color._hoops_HRIR);
	h3ddata->_hoops_RPCI = nr->_hoops_CPA;

	if (_hoops_HC->weight > 1 ||
		h3ddata->_hoops_IHP) {
		if (count > 0) {
			bool _hoops_RHHC = false;
			int _hoops_AHHC;
			int _hoops_PHHC = 4;
			int _hoops_HHHC = 0;
			int _hoops_IHHC = 6;
			int _hoops_CHHC = 0;

			if (EQUAL_MEMORY(&_hoops_SRHC[0], sizeof(DC_Point), &_hoops_SRHC[_hoops_CRHC - 1]))
				_hoops_GIPC = true;

			// _hoops_PGII _hoops_AAIA _hoops_APGR _hoops_HS _hoops_HPGR _hoops_CHGC:
			// 1. _hoops_AHC (_hoops_SHHC)
			// 2. _hoops_GIHC (_hoops_RIHC)
			// 3. _hoops_GIHC (_hoops_SHI)
			_hoops_PPCP._hoops_AIHC();
			_hoops_PPCP._hoops_APHC();
			_hoops_PPCP._hoops_APHC();

			if (_hoops_HC->weight > 1) {
				if (ANYBIT(_hoops_HC->style, LCAP_MASK)) {
					_hoops_HHHC += 8;
					_hoops_CHHC += 12;
				}
				if (ANYBIT(_hoops_HC->style, LJOIN_ROUND | LJOIN_BEVEL)) {
					_hoops_PHHC += 4;
					_hoops_IHHC += 6;
				}
				if ((_hoops_HC->style & LJOIN_MASK) == LJOIN_MITER) {
					_hoops_PHHC += 1;
					_hoops_IHHC += 6;
					_hoops_CHHC += 2;
				}
				// _hoops_PIHC _hoops_APGR _hoops_RRP _hoops_PCCP _hoops_IHH _hoops_GIHC _hoops_IH _hoops_RH "_hoops_PGHC" _hoops_PPSR
				if ((_hoops_HC->style & LJOIN_MASK) == LJOIN_MITER) {
					_hoops_RHHC = true;
					_hoops_PPCP._hoops_APHC();
					_hoops_PPCP._hoops_HIHC(_hoops_PIPC, 3);

					// _hoops_HSRR _hoops_GIRR _hoops_RIRR/_hoops_AIRR, _hoops_SR _hoops_RGAR _hoops_RRP _hoops_PCCP _hoops_IHH _hoops_HH _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_IIHC _hoops_APGR
					// _hoops_CIHC _hoops_IIHC _hoops_APGR, _hoops_RH _hoops_AII _hoops_SCIR _hoops_HCR _hoops_RH _hoops_SIHC _hoops_SIGR
					if (ANYBIT(_hoops_HC->style, LJOIN_ROUND | LCAP_ROUND | LCAP_END_ROUND))
						_hoops_PPCP._hoops_APHC();
				}
			}

			_hoops_PPCP._hoops_HIHC(_hoops_HIPC, 4);
			_hoops_PPCP._hoops_HIHC(_hoops_AIPC, 3);

			_hoops_GCHC (h3ddata, _hoops_PPCP);
			_hoops_RHSA (h3ddata, H3DCULL_NONE);
			_hoops_RPIH (h3ddata, _hoops_PPCP, _hoops_HACP);
			_hoops_RCHC	(h3ddata, _hoops_HACP);
			_hoops_RAHC = h3ddata->_hoops_ACHC;
			_hoops_HAHC = count;

			if (_hoops_RHHC) {
				int j = 0;
				int end;
				int start;

				while (count) {
					int index = 0;

					// _hoops_SR _hoops_PAH _hoops_RGAR _hoops_PGSA _hoops_IRS _hoops_PCHC _hoops_HCHC _hoops_HPGR _hoops_ARR
					_hoops_AHHC= _hoops_AHIA(_hoops_GHIH/_hoops_IHHC - _hoops_CHHC, count);

					start = j;
					end = j + _hoops_AHHC;


					_hoops_HACP->Lock(_hoops_AHHC*_hoops_PHHC + _hoops_HHHC, &_hoops_PAIH);
					_hoops_RAHC->Lock(_hoops_AHHC*_hoops_IHHC + _hoops_CHHC, &_hoops_PAHC);
					_hoops_CHPC._hoops_IRA(H3DFMT_INDEX16, _hoops_PAHC);
					_hoops_AAHC = _hoops_CHPC;

					for (i = 0; i < _hoops_AHHC - 1; i++) {

						int _hoops_ISPI = j;
						int _hoops_CSPI = j+1;

						if (i == 0) {
							_hoops_IHPC(nr, _hoops_HC, null, points, &_hoops_PAIH, &_hoops_CHPC, &_hoops_RPCP, null, null,
									&index, j, start, end, 0, _hoops_GIPC, H3DCAP_ISDC);
						}

						_hoops_PAIH._hoops_AHCP(points[_hoops_ISPI]);
						if (h3ddata->_hoops_AIC)
							_hoops_PAIH.u(_hoops_ICCP, _hoops_IIPC);
						//_hoops_RGPA _hoops_HSPP _hoops_IIGR _hoops_SPS _hoops_III
						_hoops_PAIH._hoops_IICP(points[_hoops_CSPI].x,
							points[_hoops_CSPI].y,
							points[_hoops_CSPI].z,
							_hoops_AIPC);
						_hoops_PAIH._hoops_IICP(points[_hoops_CSPI].x,
							points[_hoops_CSPI].y,
							points[_hoops_CSPI].z,
							_hoops_PIPC);
						_hoops_PAIH.t(H3D_MITER, _hoops_HIPC);
						if (_hoops_GAHC)
							_hoops_PAIH.color(h3ddata->_hoops_SHAP, _hoops_GAHC[_hoops_ISPI]);

						_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
						_hoops_PAIH._hoops_RRCI(0)._hoops_IICP(-1,0,0, _hoops_HIPC);
						_hoops_PAIH._hoops_RRCI(1)._hoops_IICP(+1,0,0, _hoops_HIPC);
						_hoops_PAIH._hoops_CPPH(2);

						_hoops_PAIH._hoops_AHCP(points[_hoops_CSPI]);
						if (h3ddata->_hoops_AIC)
							_hoops_PAIH.u(_hoops_ICCP, _hoops_IIPC);
						_hoops_PAIH._hoops_IICP(2*points[_hoops_CSPI].x - points[_hoops_ISPI].x,
								2*points[_hoops_CSPI].y - points[_hoops_ISPI].y,
								2*points[_hoops_CSPI].z - points[_hoops_ISPI].z,
								_hoops_AIPC);
						_hoops_PAIH._hoops_IICP(2*points[_hoops_CSPI].x - points[_hoops_ISPI].x,
								2*points[_hoops_CSPI].y - points[_hoops_ISPI].y,
								2*points[_hoops_CSPI].z - points[_hoops_ISPI].z,
								_hoops_PIPC);
						_hoops_PAIH.t(H3D_MITER, _hoops_HIPC);
						if (_hoops_GAHC)
							_hoops_PAIH.color(h3ddata->_hoops_SHAP, _hoops_GAHC[_hoops_CSPI]);

						_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
						_hoops_PAIH._hoops_RRCI(0)._hoops_IICP(-1,0,0, _hoops_HIPC);
						_hoops_PAIH._hoops_RRCI(1)._hoops_IICP(+1,0,0, _hoops_HIPC);
						_hoops_PAIH._hoops_CPPH(2);

						_hoops_CHPC = index;			++_hoops_CHPC;
						_hoops_CHPC = index + 1;		++_hoops_CHPC;
						_hoops_CHPC = index + 2;		++_hoops_CHPC;
						_hoops_CHPC = index + 1;		++_hoops_CHPC;
						_hoops_CHPC = index + 3;		++_hoops_CHPC;
						_hoops_CHPC = index + 2;		++_hoops_CHPC;
						index += 4;

						_hoops_IHPC(nr, _hoops_HC, null, points, &_hoops_PAIH, &_hoops_CHPC, &_hoops_RPCP, null, null,
								&index, j+1, start, end, 0, _hoops_GIPC, H3DCAP_ISDC);

						j++;
					}

					_hoops_RAHC->Unlock();
					_hoops_HACP->Unlock();
					_hoops_RRSA = _hoops_PAIH.length();
					_hoops_RGSA = (_hoops_CHPC - _hoops_AAHC) / 3;
					_hoops_SGSA (h3ddata, nr, _hoops_RAHC, _hoops_CAPA,
						_hoops_RRSA, _hoops_RGSA, _hoops_GCCA, H3DPT_TRIANGLELIST);
					count -= _hoops_AHHC;
				}
			}
			else {
				while (count) {
					int index = 0;
					_hoops_AHHC= _hoops_AHIA(_hoops_GHIH/_hoops_IHHC - _hoops_CHHC, count);

					_hoops_HACP->Lock(_hoops_AHHC*_hoops_PHHC + _hoops_HHHC, &_hoops_PAIH);
					_hoops_RAHC->Lock(_hoops_AHHC*_hoops_IHHC + _hoops_CHHC, &_hoops_PAHC);
					_hoops_CHPC._hoops_IRA(H3DFMT_INDEX16, _hoops_PAHC);
					{
						_hoops_AAHC = _hoops_CHPC;

						for (int i = 0; i < _hoops_AHHC; i++) {
							if (i > 0) {
								_hoops_PAIH._hoops_AHCP(points[0]);
								if (h3ddata->_hoops_AIC)
									_hoops_PAIH.u(_hoops_ICCP, _hoops_IIPC);
								// _hoops_RGPA _hoops_RSGR _hoops_IIGR _hoops_PGHC _hoops_III
								_hoops_PAIH._hoops_IICP(2*points->x - points[-1].x,
									2*points->y - points[-1].y,
									2*points->z - points[-1].z,
									_hoops_AIPC);
								if (_hoops_GAHC)
									_hoops_PAIH.color(h3ddata->_hoops_SHAP, *_hoops_GAHC++);

								_hoops_PAIH.t(H3D_SQUARE, _hoops_HIPC);
								_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
								_hoops_PAIH._hoops_RRCI(0)._hoops_IICP(-1,0,0, _hoops_HIPC);
								_hoops_PAIH._hoops_RRCI(1)._hoops_IICP(+1,0,0, _hoops_HIPC);
								_hoops_PAIH._hoops_CPPH(2);

								_hoops_CHPC = index;			++_hoops_CHPC;
								_hoops_CHPC = index + 1;		++_hoops_CHPC;
								_hoops_CHPC = index + 2;		++_hoops_CHPC;
								_hoops_CHPC = index + 1;		++_hoops_CHPC;
								_hoops_CHPC = index + 3;		++_hoops_CHPC;
								_hoops_CHPC = index + 2;		++_hoops_CHPC;
								index += 4;
							}

							int _hoops_RIPC = H3DCAP_ISDC | H3DCAP_USE_CURRENT_POINT;
							if (i == 0)
								_hoops_RIPC |= H3DCAP_FIRST_POINT;
							else if (i == _hoops_AHHC-1)
								_hoops_RIPC |= H3DCAP_LAST_POINT;

							_hoops_IHPC(nr, _hoops_HC, null, points, &_hoops_PAIH, &_hoops_CHPC, &_hoops_RPCP, null, null,
								&index, i, 0, _hoops_AHHC, 0, _hoops_GIPC, _hoops_RIPC);

							if (i < _hoops_AHHC - 1) {
								// _hoops_RGPA _hoops_HSPP _hoops_IIGR _hoops_SPS _hoops_III
								_hoops_PAIH._hoops_AHCP(points[0]);
								if (h3ddata->_hoops_AIC)
									_hoops_PAIH.u(_hoops_ICCP, _hoops_IIPC);
								_hoops_PAIH._hoops_IICP(points[1].x,
									points[1].y,
									points[1].z,
									_hoops_AIPC);
								if (_hoops_GAHC)
									_hoops_PAIH.color(h3ddata->_hoops_SHAP, *_hoops_GAHC++);
								_hoops_PAIH.t(H3D_SQUARE, _hoops_HIPC);
								_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
								_hoops_PAIH._hoops_RRCI(0)._hoops_IICP(-1,0,0, _hoops_HIPC);
								_hoops_PAIH._hoops_RRCI(1)._hoops_IICP(+1,0,0, _hoops_HIPC);
								_hoops_PAIH._hoops_CPPH(2);
							}
							points++;
						}
					}
					_hoops_RAHC->Unlock();
					_hoops_HACP->Unlock();


					_hoops_RRSA = _hoops_PAIH.length();
					_hoops_RGSA = (_hoops_CHPC - _hoops_AAHC) / 3;
					_hoops_SGSA (h3ddata, nr, _hoops_RAHC, _hoops_CAPA,
						_hoops_RRSA, _hoops_RGSA, _hoops_GCCA, H3DPT_TRIANGLELIST);
					count -= _hoops_AHHC;
				}
			}
		}
		else /* _hoops_RPR < 0 -- _hoops_IPHC _hoops_III _hoops_SGHC */ {
			_hoops_ICHC (count, _hoops_RRC, 2);

			_hoops_PPCP._hoops_AIHC();
			_hoops_PPCP._hoops_APHC();
			_hoops_PPCP._hoops_APHC();
			_hoops_PPCP._hoops_HIHC(_hoops_HIPC, 4);
			_hoops_PPCP._hoops_HIHC(_hoops_AIPC, 3);
			_hoops_GCHC (h3ddata, _hoops_PPCP);

			h3ddata->_hoops_GSCR->_hoops_CCHC(H3DCULL_NONE);

			_hoops_RPIH (h3ddata, _hoops_PPCP, _hoops_HACP);
			_hoops_RCHC (h3ddata, _hoops_HACP);

			H3DIndexBufferCache *_hoops_RAHC = h3ddata->_hoops_ACHC;
			while (count) {
				int _hoops_AHHC, _hoops_IHHC;
				int _hoops_SCHC = 0;

				_hoops_IHHC = 6;
				if (ANYBIT(_hoops_HC->style, LCAP_START_MASK) && (_hoops_HC->style & LCAP_START_MASK) != LCAP_BUTT)
					_hoops_IHHC += 6;

				// _hoops_CGP _hoops_IIH _hoops_HRGR _hoops_PSP _hoops_RSGR _hoops_ACPC _hoops_IAHA, _hoops_SGH _hoops_RH _hoops_HSPP _hoops_ACPC _hoops_IAHA
				if (ANYBIT(_hoops_HC->style, LCAP_END_MASK) && (_hoops_HC->style & LCAP_END_MASK) != LCAP_END_BUTT)
					_hoops_IHHC += 6;
				else if (ANYBIT(_hoops_HC->style, LCAP_START_MASK) && (_hoops_HC->style & LCAP_START_MASK) != LCAP_BUTT)
					_hoops_IHHC += 6;

				_hoops_AHHC= _hoops_AHIA(_hoops_GHIH/_hoops_IHHC, count);
				//_hoops_GSHC:	 _hoops_SPS _hoops_PPSR
				//_hoops_RSHC: _hoops_PGHC _hoops_PPSR _hoops_PAR 2*_hoops_SCGR-_hoops_SPS, _hoops_GPGA _hoops_GPP _hoops_GPHA'_hoops_GRI _hoops_ASHC
				//_hoops_PSHC._hoops_HSHC: _hoops_ISHC _hoops_PPR/_hoops_PAR _hoops_CSHC _hoops_ISP
				//_hoops_PSHC._hoops_SSH:  _hoops_SSHC _hoops_HSPP _hoops_PAR _hoops_RSGR _hoops_IIGR _hoops_III _hoops_CAGH
				_hoops_HACP->Lock(_hoops_AHHC*_hoops_IHHC, &_hoops_PAIH);
				_hoops_RAHC->Lock(_hoops_AHHC*_hoops_IHHC, &_hoops_PAHC);
				_hoops_CHPC._hoops_IRA(H3DFMT_INDEX16, _hoops_PAHC);
				for (i = 0; i < _hoops_AHHC; i++) {
					// _hoops_RGPA _hoops_GIRR _hoops_ACPC _hoops_RPP _hoops_IRPR
					_hoops_IHPC(nr, _hoops_HC, null, points, &_hoops_PAIH, &_hoops_CHPC, &_hoops_RPCP, null, null,
							&_hoops_SCHC, 0, 0, 2, 0, false, H3DCAP_ISDC | H3DCAP_FIRST_POINT | H3DCAP_USE_CURRENT_POINT);

					// _hoops_RGPA _hoops_HSPP _hoops_IIGR _hoops_III _hoops_CAGH
					_hoops_PAIH._hoops_AHCP(points[0]);
					if (h3ddata->_hoops_AIC)
						_hoops_PAIH.u(_hoops_ICCP, _hoops_IIPC);
					_hoops_PAIH._hoops_IICP(points[1].x, points[1].y, points[1].z, _hoops_AIPC);
					if (_hoops_GAHC) {
						_hoops_PAIH.color(h3ddata->_hoops_SHAP, _hoops_GAHC[0]);
						++_hoops_GAHC;
					}

					_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
					_hoops_PAIH._hoops_RRCI(0)._hoops_IICP(-1,0,0, _hoops_HIPC);
					_hoops_PAIH._hoops_RRCI(1)._hoops_IICP(+1,0,0, _hoops_HIPC);
					_hoops_PAIH._hoops_CPPH(2);
					points++;

					// _hoops_RGPA _hoops_RSGR _hoops_IIGR _hoops_III _hoops_CAGH
					_hoops_PAIH._hoops_AHCP(points[0]);
					if (h3ddata->_hoops_AIC)
						_hoops_PAIH.u(_hoops_ICCP, _hoops_IIPC);
					_hoops_PAIH._hoops_IICP(2*points->x - points[-1].x,
							2*points->y - points[-1].y,
							2*points->z - points[-1].z,
							_hoops_AIPC);
					if (_hoops_GAHC) {
						_hoops_PAIH.color(h3ddata->_hoops_SHAP, _hoops_GAHC[0]);
						++_hoops_GAHC;
					}

					_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
					_hoops_PAIH._hoops_RRCI(0)._hoops_IICP(-1,0,0, _hoops_HIPC);
					_hoops_PAIH._hoops_RRCI(1)._hoops_IICP(+1,0,0, _hoops_HIPC);
					_hoops_PAIH._hoops_CPPH(2);

					_hoops_CHPC[0] = _hoops_SCHC + 0;
					_hoops_CHPC[1] = _hoops_SCHC + 1;
					_hoops_CHPC[2] = _hoops_SCHC + 2;
					_hoops_CHPC[3] = _hoops_SCHC + 1;
					_hoops_CHPC[4] = _hoops_SCHC + 2;
					_hoops_CHPC[5] = _hoops_SCHC + 3;
					_hoops_CHPC += 6;
					_hoops_SCHC += 4;

					_hoops_IHPC(nr, _hoops_HC, null, points, &_hoops_PAIH, &_hoops_CHPC, &_hoops_RPCP, null, null,
							&_hoops_SCHC, 0, -1, 1, 0, false, H3DCAP_ISDC | H3DCAP_LAST_POINT | H3DCAP_USE_CURRENT_POINT);
					points++;
				}


				_hoops_HACP->Unlock();
				_hoops_RAHC->Unlock();
				_hoops_RRSA = _hoops_PAIH.length();
				_hoops_RGSA = _hoops_CHPC.length() / 3;
				_hoops_SGSA(h3ddata, nr, _hoops_RAHC, _hoops_CAPA, _hoops_RRSA, _hoops_RGSA, _hoops_GCCA, H3DPT_TRIANGLELIST);
				count -= _hoops_AHHC;
			}
		}
	}
	else /* _hoops_GGIC _hoops_APGR -- _hoops_PSP _hoops_RRP _hoops_IS _hoops_RGIC _hoops_AHCA _hoops_RIRR _hoops_PPR _hoops_AIRR */ {
		if (BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)) {
			if (count > 0)
			{
				_hoops_PPCP._hoops_AIHC();
				_hoops_PPCP._hoops_APHC();
				_hoops_PPCP._hoops_APHC();
				_hoops_PPCP._hoops_HIHC(_hoops_HIPC, 4);
				_hoops_PPCP._hoops_HIHC(_hoops_AIPC, 3);
				_hoops_GCHC (h3ddata, _hoops_PPCP);

				h3ddata->_hoops_GSCR->_hoops_CCHC(H3DCULL_NONE);

				_hoops_RPIH (h3ddata, _hoops_PPCP, _hoops_HACP);
				while (count) {
					int _hoops_AHHC, _hoops_PHHC = 4;
					_hoops_AHHC= _hoops_AHIA(_hoops_GHIH/_hoops_PHHC, count);

					_hoops_HACP->Lock(_hoops_AHHC*_hoops_PHHC+1, &_hoops_PAIH);
					for (int i = 0; i < _hoops_AHHC; i++) {
						if (i > 0)
						{
							// _hoops_RGPA _hoops_RSGR _hoops_IIGR _hoops_PGHC _hoops_III
							_hoops_PAIH._hoops_AHCP(points[0]);
							if (h3ddata->_hoops_AIC)
								_hoops_PAIH.u(_hoops_ICCP, _hoops_IIPC);
							_hoops_PAIH._hoops_IICP(2*points->x - points[-1].x,
									2*points->y - points[-1].y,
									2*points->z - points[-1].z,
									_hoops_AIPC);
							if (_hoops_GAHC)
								_hoops_PAIH.color(h3ddata->_hoops_SHAP, *_hoops_GAHC++);
							_hoops_PAIH.t(H3D_ROUND, _hoops_HIPC);
							_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
							_hoops_PAIH._hoops_RRCI(0)._hoops_IICP(-1,0,0, _hoops_HIPC);
							_hoops_PAIH._hoops_RRCI(1)._hoops_IICP(+1,0,0, _hoops_HIPC);
							_hoops_PAIH._hoops_CPPH(2);
						}

						if (i < _hoops_AHHC - 1)
						{
							// _hoops_RGPA _hoops_HSPP _hoops_IIGR _hoops_SPS _hoops_III
							_hoops_PAIH._hoops_AHCP(points[0]);
							if (h3ddata->_hoops_AIC)
								_hoops_PAIH.u(_hoops_ICCP, _hoops_IIPC);
							_hoops_PAIH._hoops_IICP(points[1].x, points[1].y, points[1].z, _hoops_AIPC);
							if (_hoops_GAHC)
								_hoops_PAIH.color(h3ddata->_hoops_SHAP, *_hoops_GAHC++);
							_hoops_PAIH.t(H3D_ROUND, _hoops_HIPC);
							_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
							_hoops_PAIH._hoops_RRCI(0)._hoops_IICP(-1,0,0, _hoops_HIPC);
							_hoops_PAIH._hoops_RRCI(1)._hoops_IICP(+1,0,0, _hoops_HIPC);
							_hoops_PAIH._hoops_CPPH(2);
						}
						points++;
					}

					_hoops_HACP->Unlock();
					_hoops_RGSA = _hoops_PAIH.length() - 2;
					_hoops_SSCA (h3ddata, nr, _hoops_HACP, _hoops_CAPA, _hoops_RGSA, _hoops_GCCA, H3DPT_TRIANGLESTRIP);
					count -= _hoops_AHHC;
				}
			}else /* _hoops_RPR < 0 */{
				_hoops_ICHC (count, _hoops_RRC, 2);

				_hoops_PPCP._hoops_AIHC();
				_hoops_PPCP._hoops_APHC();
				_hoops_PPCP._hoops_APHC();
				_hoops_PPCP._hoops_HIHC(_hoops_HIPC, 4);
				_hoops_PPCP._hoops_HIHC(_hoops_AIPC, 3);
				_hoops_GCHC (h3ddata, _hoops_PPCP);

				h3ddata->_hoops_GSCR->_hoops_CCHC(H3DCULL_NONE);

				_hoops_RPIH (h3ddata, _hoops_PPCP, _hoops_HACP);
				_hoops_RCHC (h3ddata, _hoops_HACP);

				H3DIndexBufferCache *_hoops_RAHC = h3ddata->_hoops_ACHC;
				while (count) {
					int _hoops_AHHC, _hoops_IHHC;
					short *_hoops_PAHC, *_hoops_AGIC, _hoops_SCHC = 0;

					_hoops_IHHC = 6;
					_hoops_AHHC= _hoops_AHIA(_hoops_GHIH/_hoops_IHHC, count);
					//_hoops_GSHC:	 _hoops_SPS _hoops_PPSR
					//_hoops_RSHC: _hoops_PGHC _hoops_PPSR _hoops_PAR 2*_hoops_SCGR-_hoops_SPS, _hoops_GPGA _hoops_GPP _hoops_GPHA'_hoops_GRI _hoops_ASHC
					//_hoops_PSHC._hoops_HSHC: _hoops_ISHC _hoops_PPR/_hoops_PAR _hoops_CSHC _hoops_ISP
					//_hoops_PSHC._hoops_SSH:  _hoops_SSHC _hoops_HSPP _hoops_PAR _hoops_RSGR _hoops_IIGR _hoops_III _hoops_CAGH
					_hoops_HACP->Lock(_hoops_AHHC*_hoops_IHHC, &_hoops_PAIH);
					_hoops_RAHC->Lock(_hoops_AHHC*_hoops_IHHC, &_hoops_PAHC);

					_hoops_AGIC = _hoops_PAHC;
					for (i = 0; i < _hoops_AHHC; i++) {
						// _hoops_RGPA _hoops_HSPP _hoops_IIGR _hoops_III _hoops_CAGH
						_hoops_PAIH._hoops_AHCP(points[0]);
						if (h3ddata->_hoops_AIC)
							_hoops_PAIH.u(_hoops_ICCP, _hoops_IIPC);
						_hoops_PAIH._hoops_IICP(points[1].x, points[1].y, points[1].z, _hoops_AIPC);
						if (_hoops_GAHC)
							_hoops_PAIH.color(h3ddata->_hoops_SHAP, *_hoops_GAHC++);
						_hoops_PAIH.t(H3D_ROUND, _hoops_HIPC);
						_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
						_hoops_PAIH._hoops_RRCI(0)._hoops_IICP(-1,0,0, _hoops_HIPC);
						_hoops_PAIH._hoops_RRCI(1)._hoops_IICP(+1,0,0, _hoops_HIPC);
						_hoops_PAIH._hoops_CPPH(2);
						points++;

						// _hoops_RGPA _hoops_RSGR _hoops_IIGR _hoops_III _hoops_CAGH
						_hoops_PAIH._hoops_AHCP(points[0]);
						if (h3ddata->_hoops_AIC)
							_hoops_PAIH.u(_hoops_ICCP, _hoops_IIPC);
						_hoops_PAIH._hoops_IICP(2*points->x - points[-1].x, 
								2*points->y - points[-1].y,
								2*points->z - points[-1].z,
								_hoops_AIPC);
						if (_hoops_GAHC)
							_hoops_PAIH.color(h3ddata->_hoops_SHAP, *_hoops_GAHC++);
						_hoops_PAIH.t(H3D_ROUND, _hoops_HIPC);
						_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
						_hoops_PAIH._hoops_RRCI(0)._hoops_IICP(-1,0,0, _hoops_HIPC);
						_hoops_PAIH._hoops_RRCI(1)._hoops_IICP(+1,0,0, _hoops_HIPC);
						_hoops_PAIH._hoops_CPPH(2);

						*_hoops_PAHC++ = _hoops_SCHC + 0;
						*_hoops_PAHC++ = _hoops_SCHC + 1;
						*_hoops_PAHC++ = _hoops_SCHC + 2;
						*_hoops_PAHC++ = _hoops_SCHC + 1;
						*_hoops_PAHC++ = _hoops_SCHC + 2;
						*_hoops_PAHC++ = _hoops_SCHC + 3;
						_hoops_SCHC += 4;
						points++;
					}
					_hoops_HACP->Unlock();
					_hoops_RAHC->Unlock();

					_hoops_RRSA = _hoops_PAIH.length();
					_hoops_RGSA = (_hoops_PAHC - _hoops_AGIC) / 3;
					_hoops_SGSA(h3ddata, nr, _hoops_RAHC, _hoops_CAPA, _hoops_RRSA, _hoops_RGSA, _hoops_GCCA, H3DPT_TRIANGLELIST);
					count -= _hoops_AHHC;
				}
			}
		}
		else /* _hoops_GGIC _hoops_GRAA-_hoops_PGIC _hoops_APGR */ {
			H3DVertexBufferCache *_hoops_HACP;
			int _hoops_HGIC = 0;
			int i, j, _hoops_IGIC;
			_hoops_ISC const *_hoops_PIHR = &nr->_hoops_AHP->color._hoops_HRIR;

			_hoops_SSHH (h3ddata, nr, T_LINES, null, flags, &_hoops_RSR);
			_hoops_GIAC (h3ddata, nr, _hoops_RSR);

			_hoops_RSR->_hoops_GIHR (_hoops_PIHR);

			_hoops_PPCP._hoops_AIHC();
			if (h3ddata->_hoops_AIC) {
				_hoops_PPCP._hoops_APHC();
				_hoops_PPCP._hoops_HIHC(0, 1);
			}
			_hoops_RPIH (h3ddata, _hoops_PPCP, _hoops_HACP);
			_hoops_GCHC (h3ddata, _hoops_PPCP);

			_hoops_ICHC (count, _hoops_RRC, 2);
			//_hoops_CGIC _hoops_PHI _hoops_IIGR _hoops_III _hoops_SGHC _hoops_IS _hoops_SGIC _hoops_GGR _hoops_SPR _hoops_PHHR
			_hoops_IGIC = (int)_hoops_HACP->_hoops_GRIC/2;

			while (count) {
				i = j = 0;
				if (count < _hoops_IGIC)
					_hoops_IGIC = count;
				_hoops_HGIC = 0;
				_hoops_HACP->Lock(_hoops_IGIC*2, &_hoops_PAIH);

				for (j = 0; j < _hoops_IGIC; j++) {
					for (i = 0; i < 2; i++) {

						// _hoops_SR _hoops_GA'_hoops_RA _hoops_HHGC _hoops_IS _hoops_SHI _hoops_RRIC _hoops_HCGR
						float _hoops_ARIC;
						float _hoops_PRIC;
						if (h3ddata->_hoops_ACCR == -1) {
							_hoops_ARIC = 0.5f;
							_hoops_PRIC = 0.5f;
							if (nr->_hoops_SRA->_hoops_HRIC || h3ddata->glyph.mode) {
								_hoops_ARIC = 0.0;
								_hoops_PRIC = 0.0;
							}
						}
						else {
							_hoops_ARIC = 0.0f;
							_hoops_PRIC = 0.5f;
							if (nr->_hoops_SRA->_hoops_HRIC) {
								_hoops_ARIC = 0.0;
								_hoops_PRIC = 0.0;
							}
							if (h3ddata->glyph.mode) {
								_hoops_ARIC = 0.5;
								_hoops_PRIC = 0.0;
							}
						}
						_hoops_PAIH._hoops_AHCP(points[i].x + _hoops_ARIC,
								points[i].y + _hoops_PRIC,
								points[i].z);
						if (h3ddata->_hoops_AIC)
							_hoops_PAIH.u(_hoops_ICCP, _hoops_IIPC);
						if (_hoops_GAHC)
							_hoops_PAIH.color(h3ddata->_hoops_SHAP, _hoops_GAHC[i]);

						_hoops_PAIH._hoops_CPPH();
					}
					points += _hoops_RRC;
					if (_hoops_GAHC)
						_hoops_GAHC += _hoops_RRC;
				}
				_hoops_HACP->Unlock();
				_hoops_SSCA (h3ddata, nr, _hoops_HACP, _hoops_CAPA, _hoops_IGIC, _hoops_GCCA, H3DPT_LINELIST);
				count -= _hoops_IGIC;
			}
		}//_hoops_RSGR _hoops_SHS _hoops_GGIC _hoops_APGR
	}
	h3ddata->_hoops_AIC = false;

} //_hoops_RSGR '_hoops_PGSA _hoops_CSPH _hoops_IRIC _hoops_ISII'


void draw_dc_polyline (
		Net_Rendition const &  nr,
		int _hoops_CRHC,
		DC_Point const *_hoops_SRHC)
{
	draw_dc_gouraud_polyline (nr, _hoops_CRHC, _hoops_SRHC, null);
} //_hoops_RSGR '_hoops_PGSA _hoops_CSPH _hoops_ISII'


/*****************************************************************************
						_hoops_CRIC
*****************************************************************************/
void _hoops_SRIC (
		Net_Rendition const &  nr,
		int count,
		DC_Point const * points,
		RGBAS32 const * colors,
		const int _hoops_GAIC)
{
	H3DData alter *h3ddata = H3DD (nr->_hoops_SRA);
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	H3DShader *_hoops_RSR;
	H3DVertexBufferCache *_hoops_HACP;
	H3DVertexBuffer &_hoops_PAIH = h3ddata->_hoops_CP;
	int _hoops_RRC;
	int flags = H3DID_DC|H3DID_USE_FACE_DISPLACEMENT;
	int _hoops_HGIC = 0;
	int i, j, _hoops_IGIC;
	bool _hoops_RASP = false;
	_hoops_IAPA const *_hoops_CAPA = null;

	// _hoops_SHHH _hoops_RGAR _hoops_HS _hoops_SPR _hoops_IIGR _hoops_AGCR _hoops_CHIA
	ASSERT(_hoops_GAIC == _hoops_RAIC || _hoops_GAIC == _hoops_AAIC || _hoops_GAIC == _hoops_PAIC);

	/* _hoops_SPCA _hoops_GHCA _hoops_SHH _hoops_HPPA _hoops_GHC _hoops_IS _hoops_RHCA _hoops_AHCA */
	if (!_hoops_HPCA(nr, _hoops_CAPA)) {
		/* _hoops_HAIC'_hoops_RA _hoops_AA _hoops_HGRC _hoops_GHC - _hoops_CAH */
		HD_Clip_DC_Polytriangle(nr, count, points, colors, null, null, null, 0, 0, _hoops_GAIC|_hoops_GPHC);
		return;
	}

	if (_hoops_SIGA->pattern == FP_USER_DEFINED) {
	    HD_Span_DC_Polytriangle (nr, count, points);
	    return;
	}

	H3D_TRACE(h3ddata, "draw_dc_polytriangle_helper");

	/* _hoops_PHAA _hoops_AHAP _hoops_IS _hoops_IAIC _hoops_HRGR _hoops_HSP _hoops_HSGP */
	if (nr->_hoops_CPP->_hoops_PRH.style == _hoops_GCPI &&
		_hoops_SIGA->_hoops_CHA->_hoops_IRIR < 1.0f &&
		_hoops_SIGA->_hoops_PGPH)
		_hoops_RASP = (_hoops_SIGA->_hoops_PGPH->stipple != 0);
	if (_hoops_RASP ||
		nr->_hoops_IHA->pattern != FP_SOLID && nr->_hoops_IHA->pattern != FP_USER_DEFINED) {
		_hoops_AGPH((Display_Context alter *) nr->_hoops_SRA, nr->_hoops_IHA->pattern, 0, _hoops_RASP);
		h3ddata->_hoops_GSCR->_hoops_GSAC(nr, 0, _hoops_RSAC, h3ddata->_hoops_SRPH[nr->_hoops_IHA->pattern], 0);
	}

	// _hoops_CAIC-_hoops_SCPH _hoops_PPR _hoops_RIR-_hoops_GPHA _hoops_HAIR _hoops_GIPR _hoops_PPSI _hoops_RH _hoops_PSHA _hoops_CRGR _hoops_RH _hoops_SAIC.
	if (_hoops_GAIC != _hoops_RAIC) {
		flags |= H3DID_VERTEX_COLORS;
	}

	flags = _hoops_SRSP(h3ddata, nr, T_FACES, nr->_hoops_CPP->_hoops_PRH._hoops_HRH, _hoops_RASP, flags);

	// _hoops_AHH: _hoops_SRPR _hoops_HAHH _hoops_IS _hoops_HHPR _hoops_GPIC _hoops_RPIC, _hoops_SR _hoops_CISA _hoops_GGR _hoops_HCR _hoops_RH _hoops_PSHA _hoops_APIC. _hoops_PPIC _hoops_GRS _hoops_RGHH _hoops_CPS.
	_hoops_ICSP(h3ddata, H3DSHADE_GOURAUD);
	_hoops_SSHH (h3ddata, nr, T_FACES, null, flags, &_hoops_RSR);
	_hoops_GIAC (h3ddata, nr, _hoops_RSR);

	h3ddata->_hoops_RPCI = nr->_hoops_CPA;

	if (_hoops_GAIC == _hoops_RAIC) {
		// _hoops_GGPR _hoops_HPIC _hoops_HAIR, _hoops_GIHA _hoops_RSPC _hoops_AHC _hoops_RGAR
		H3DVertexFormat _hoops_PPCP(H3DVF_PT);
		_hoops_ISC _hoops_PIHR;
		_hoops_PIHR.r = colors[0].r;
		_hoops_PIHR.g = colors[0].g;
		_hoops_PIHR.b = colors[0].b;
		_hoops_PIHR.a = colors[0].a;
		_hoops_RSR->_hoops_GIHR (&_hoops_PIHR);
		_hoops_RPIH (h3ddata, _hoops_PPCP, _hoops_HACP);
		_hoops_GCHC (h3ddata, _hoops_PPCP);
	}
	else {
		// _hoops_IPIC _hoops_RSPC _hoops_HAIR _hoops_PPR _hoops_AHC
		H3DVertexFormat _hoops_PPCP(H3DVF_PT_CLR);
		_hoops_RPIH (h3ddata, _hoops_PPCP, _hoops_HACP);
		_hoops_GCHC (h3ddata, _hoops_PPCP);
	}

	// _hoops_GRSH _hoops_CHR _hoops_SR _hoops_CPIC _hoops_IS _hoops_SPIC _hoops_RSSA?
	_hoops_ICHC (count, _hoops_RRC, 3);

	// _hoops_GRSH _hoops_CHR _hoops_SR _hoops_CPIC _hoops_IS _hoops_SPIC _hoops_PSHA?
	int _hoops_GHIC = 0;
	int _hoops_RHIC = 0;
	if ((_hoops_GAIC == _hoops_PAIC))
		_hoops_RHIC = 1;
	else if (_hoops_GAIC == _hoops_AAIC) {
		_hoops_GHIC = 1;

		if (_hoops_RRC == 1)
			_hoops_RHIC = -2;  //_hoops_HAS._hoops_IAS. _hoops_AHIC _hoops_HPP 2 _hoops_RAS _hoops_GRR _hoops_SCPH
	}

	//_hoops_CGIC _hoops_PHI _hoops_IIGR _hoops_HIPH _hoops_IS _hoops_SGIC _hoops_GGR _hoops_SPR _hoops_PHHR
	_hoops_IGIC = (int)_hoops_HACP->_hoops_GRIC/3;
	while (count) {
		if (count < _hoops_IGIC)
			_hoops_IGIC = count;
		_hoops_HGIC = 0;
		_hoops_HACP->Lock(_hoops_IGIC*3, &_hoops_PAIH);

		// _hoops_PHIC _hoops_SIPP _hoops_RH _hoops_HAPR _hoops_IS _hoops_SRCH _hoops_HHIC _hoops_ASSA - _hoops_IHIC _hoops_CHIC = _hoops_SPAC.
		if (_hoops_GAIC == _hoops_RAIC) {
			// _hoops_IISH _hoops_AGGP _hoops_RSSA
			for (j = 0; j < _hoops_IGIC; j++) {
				for (i = 0; i < 3; i++) {
					_hoops_PAIH._hoops_AHCP(points[i].x, points[i].y + 0.5f, points[i].z);
					_hoops_PAIH._hoops_CPPH();
				}
				points += _hoops_RRC;
			}
		}
		else
		{
			// _hoops_IISH _hoops_SHIC _hoops_RSSA
			for (j = 0; j < _hoops_IGIC; j++) {

				for (i = 0; i < 3; i++) {
					_hoops_PAIH._hoops_AHCP(points[i].x, points[i].y + 0.5f, points[i].z);

					// _hoops_GIIC-_hoops_RIIC _hoops_HAIR _hoops_CRGR _hoops_AIIC _hoops_SRHR
					//_hoops_PIIC _hoops_RH _hoops_HSPR _hoops_HIIC _hoops_CSAP _hoops_IIIC _hoops_RH _hoops_SIH _hoops_GGR _hoops_PCHC _hoops_PCGC
					//  _hoops_CIIC[_hoops_SIIC++] = *_hoops_GCIC<_hoops_RCIC _hoops_AIIC*>(&_hoops_HAIR);
					_hoops_PAIH.color(h3ddata->_hoops_SHAP, *colors);
					_hoops_PAIH._hoops_CPPH();

					// _hoops_ACIC _hoops_SHH _hoops_SPR _hoops_PAR _hoops_AHHR _hoops_GPGA _hoops_GPP _hoops_CCH - _hoops_RGR _hoops_PCIC _hoops_IHGH.
					colors += _hoops_GHIC;
				}

				// _hoops_SRPA _hoops_HAIR _hoops_CRS _hoops_AHC _hoops_RPP _hoops_GGR _hoops_CCGI _hoops_CCH
				colors += _hoops_RHIC;

				// _hoops_CPR _hoops_SCPH
				points += _hoops_RRC;
			}
		}
		_hoops_HACP->Unlock();

		// _hoops_AHH: _hoops_HCIC _hoops_SCH _hoops_ICIC _hoops_IS _hoops_AA _hoops_RH _hoops_HPPA _hoops_IPPA _hoops_IPGR _hoops_ASSA _hoops_RH _hoops_SSAI _hoops_IPGR?
		_hoops_SSCA (h3ddata, nr, _hoops_HACP, _hoops_CAPA, _hoops_IGIC, _hoops_GCCA, H3DPT_TRIANGLELIST);
		count -= _hoops_IGIC;
	}
}

/*
 * _hoops_SRAC
 */
void draw_dc_colorized_polytriangle (
		Net_Rendition const &  nr,
		int count,
		DC_Point const * points,
		RGBAS32 const * colors,
		bool single)
{
	_hoops_SRIC(nr, count, points, colors, single ? _hoops_RAIC : _hoops_PAIC);
}


/*
 * _hoops_SRAC
 */
void draw_dc_polytriangle (
		Net_Rendition const &  nr,
		int count,
		DC_Point const * points)
{
	RGBAS32 const *rgbas32 = (RGBAS32 const *)&nr->_hoops_IHA->color._hoops_HRIR;

	_hoops_SRIC(nr, count, points, rgbas32, _hoops_RAIC);
}


/*
 * _hoops_SRAC
 */
void HC_CDECL draw_dc_gouraud_polytriangle (
		Net_Rendition const & nr,
		int								count,
		DC_Point const				*points,
		RGBAS32 const				*colors)
{
	_hoops_SRIC(nr, count, points, colors, _hoops_AAIC);
}

local void
_hoops_CCIC(
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	_hoops_RSSH const *			params,
	Integer32					param_width,
	bool *						result)
{
	H3DData alter *				h3ddata = H3DD (nr->_hoops_SRA);
	_hoops_RCR alter *				txr = null;
	_hoops_HHA const &	matr = nr->_hoops_IHA->_hoops_CHA;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	H3DShader *					_hoops_RSR;
	H3DVertexBufferCache *		_hoops_HACP;
	H3DVertexBuffer				  _hoops_PAIH;
	Driver_Color alter				color;
	H3DTexture *					id;
	_hoops_IAPA const *		_hoops_CAPA = null;
	const int						_hoops_SCIC [6]	= {0, 1, 2, 3, 4, 5};
	const int						_hoops_GSIC [6]	= {0, 1, 2, 2, 1, 3};
	const int *						indices;
	int								i;
	int								_hoops_RSIC;
	int								_hoops_ASIC = 6;
	_hoops_RSSH 						_hoops_PSIC[18];
	float							u, v;
	float							_hoops_HSIC=0.0, _hoops_ISIC=0.0;
	unsigned int					flags=H3DID_DC;

	*result=false;

	if(matr->_hoops_SCA==null || matr->_hoops_SCA->next != null)
		return;

	if(!BIT(matr->_hoops_SCA->texture->_hoops_SCR, _hoops_RCRH))
		return;

	if(count==4)
		indices = _hoops_GSIC;
	else if(count == -6)
		indices = _hoops_SCIC;
	else if(count == -3) {
		indices = _hoops_SCIC;
		_hoops_ASIC = 3;
	}
	else
		return;

	if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_GSRC) &&
		(!matr->_hoops_SCA->texture->image ||
		 matr->_hoops_SCA->texture->image->width > (int) h3ddata->_hoops_ACGH._hoops_PCGH||
		 matr->_hoops_SCA->texture->image->height > (int) h3ddata->_hoops_ACGH._hoops_HCGH)) {
		return;
	}

	for(i=0; i<_hoops_ASIC-1; ++i)
	{
		if(points[indices[i]].z != points[indices[i+1]].z)
			return;
	}

	if (BIT (_hoops_IHCR->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = _hoops_IHCR->_hoops_RGH;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			if (_hoops_GGH->_hoops_CRH > H3D_MAX_CUTTING_PLANES)
				return;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			if (_hoops_GGH->_hoops_PGH > h3ddata->_hoops_GAH)
				return;
		}
	}

	_hoops_CSIC(h3ddata, nr, T_FACES, null, flags, _hoops_PIA, &_hoops_RSR);
	_hoops_ICSP(h3ddata, H3DSHADE_FLAT);
	_hoops_GIAC(h3ddata, nr, _hoops_RSR);
	_hoops_HISP(h3ddata, false);
	ENSURE_DEPTH_MASK (h3ddata, (BIT(_hoops_IHCR->flags, _hoops_PASP) && !BIT(nr->transform_rendition->flags, _hoops_ISH)));
	ENSURE_TRANSPARENCY (h3ddata, nr->_hoops_CPP->_hoops_PRH._hoops_HRH);
	_hoops_RHSA(h3ddata, H3DCULL_NONE);
	_hoops_IPGP (h3ddata, true);

	H3DVertexFormat _hoops_PPCP(H3DVF_PT_TEX);
	_hoops_RPIH (h3ddata, _hoops_PPCP, _hoops_HACP);
	_hoops_GCHC (h3ddata, _hoops_PPCP);

	_hoops_GRA const &	_hoops_RRA = nr->_hoops_ARA;
	color._hoops_HRIR.a = (char) (matr->_hoops_IRIR*255);
	if(BIT(matr->_hoops_SCA->flags, _hoops_PRA)
		|| BIT(matr->_hoops_SCA->flags, _hoops_PPIR)) {

			color._hoops_HRIR.r = (char) (_hoops_RRA->image._hoops_HRA.red*matr->_hoops_CSHR.red*255);
			color._hoops_HRIR.g = (char) (_hoops_RRA->image._hoops_HRA.green*matr->_hoops_CSHR.green*255);
			color._hoops_HRIR.b = (char) (_hoops_RRA->image._hoops_HRA.blue*matr->_hoops_CSHR.blue*255);
	}
	else  {
		color._hoops_HRIR.r = (char) (_hoops_RRA->image._hoops_HRA.red*255);
		color._hoops_HRIR.g = (char) (_hoops_RRA->image._hoops_HRA.green*255);
		color._hoops_HRIR.b = (char) (_hoops_RRA->image._hoops_HRA.blue*255);
	}
	_hoops_RSR->_hoops_RCHR(nr, T_FACES, false);

	txr = matr->_hoops_SCA->texture;
	_hoops_PRRH(txr);
	id = _hoops_PIGH (h3ddata, nr, txr, _hoops_ACRH);
	h3ddata->_hoops_GSCR->_hoops_GSAC (nr, txr, _hoops_ACRH, id, 0);
	if(!BIT(txr->_hoops_RHGH->flags, _hoops_PCRH)) {
		u=1.0f;
		v=1.0f;
	}
	else {
		u = (float)matr->_hoops_SCA->texture->image->width/(float)txr->_hoops_RHGH->width;
		v = (float)matr->_hoops_SCA->texture->image->height/(float)txr->_hoops_RHGH->height;
	}
	if (h3ddata->_hoops_CSS == H3D_Driver_Shader_Type_DX9) {
		_hoops_HSIC = 0.5/txr->_hoops_RHGH->width;
		_hoops_ISIC = 0.5/txr->_hoops_RHGH->height;
	}
	_hoops_RSIC = (count>0 ? count : -count);

	for(i=0; i<_hoops_RSIC; ++i) {
		_hoops_PSIC[i*param_width] = params[i*param_width] * u + _hoops_HSIC;
		_hoops_PSIC[i*param_width +1] = 1-params[i*param_width +1] * v + _hoops_ISIC;
	}

	_hoops_GPRH(_hoops_ACCA) += 2;
	_hoops_HACP->Lock(_hoops_ASIC, &_hoops_PAIH);
		for(i=0; i<_hoops_ASIC; ++i)
		{
			_hoops_PAIH._hoops_AHCP(points[indices[i]].x + 0.5, points[indices[i]].y + 0.5, points[indices[i]].z);
			_hoops_PAIH._hoops_IICP(_hoops_PSIC[indices[i]*param_width], _hoops_PSIC[indices[i]*param_width+1], 0);
			_hoops_PAIH._hoops_CPPH();
		}
	_hoops_HACP->Unlock();

	do {
		_hoops_HACP->_hoops_CHSA(h3ddata, H3DPT_TRIANGLELIST, _hoops_ASIC/3);

		if (_hoops_CAPA != null)
			_hoops_CAPA = _hoops_CAPA->next;
	} while (_hoops_CAPA != null);

	h3ddata->_hoops_RPCI = _hoops_CCC;
	_hoops_HPRH(txr);

	*result=true;
}

/*
 * _hoops_SRAC
 */
void draw_dc_textured_polytriangle (
	Net_Rendition const &  nr,
	int count,
	DC_Point const * points,
	RGBA const * color,
	_hoops_ARPA const * planes,
	_hoops_RSSH const * params,
	Integer32 param_width,
	_hoops_SSIC param_flags)
{
	Display_Context const *dc = nr->_hoops_SRA;
	H3DData alter *h3ddata = H3DD(dc);
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	Net_Rendition	_hoops_CRAI;
	_hoops_HHCR _hoops_GGCC;
 	Tristrip alter ts;
	float _hoops_APCP;
	Point alter *_hoops_RGCC;
	Vector alter	*normals;
	int *lengths;
	int *_hoops_AGCC;
	int _hoops_RRC, used, i;
	bool _hoops_IA;

	H3D_TRACE(h3ddata, "draw_dc_textured_polytriangle");

	_hoops_CCIC(nr, count, points, params, param_width, &_hoops_IA);
	if(_hoops_IA)
		return;

	if (_hoops_SIGA->_hoops_AGP != null &&
		_hoops_SIGA->_hoops_AGP->count > dc->_hoops_PGCC._hoops_HGCC) {
		HD_Std_DC_Textured_Polytris (nr, count, points, color, planes, params, param_width, param_flags);
		return;
	}
	if (!BIT (nr->transform_rendition->flags, _hoops_IGCC))
		HD_Validate_World_To_Screen (nr);
	_hoops_RPRA const * _hoops_APRA = nr->transform_rendition->_hoops_CGCC->_hoops_PPRA()->data.elements;

	_hoops_CRAI = nr;
	_hoops_GGCC = _hoops_CRAI.Modify()->transform_rendition.Modify();
	_hoops_GGCC->flags &= ~_hoops_IGSP;
	_hoops_GGCC->heuristics &= ~_hoops_RSA;

	if (_hoops_GGCC->_hoops_IPH->data._hoops_RAGR != 0) {
		_hoops_GGCC->_hoops_IPH = _hoops_SGCC::Create (dc);
	    HD_Redo_Screen (_hoops_CRAI, &((_hoops_HHRA alter *)_hoops_GGCC->_hoops_SPH)->_hoops_GRCC);
	}

	_hoops_ICHC (count, _hoops_RRC, 3);

	ALLOC_ARRAY_CACHED (_hoops_RGCC, count*3, Point);
	ALLOC_ARRAY_CACHED (normals, count*3, Vector);
	ALLOC_ARRAY_CACHED (_hoops_AGCC, count*3, int);
	ALLOC_ARRAY_CACHED (lengths, count, int);

	ZERO_STRUCT (&ts, Tristrip);
	ts._hoops_PHHA = count;
	ts.total = count * 3;
	ts.point_count = count * 3;
	ts.face_count = count;
	ZALLOC(ts._hoops_GSSH, _hoops_RRCC);
	_hoops_ICAI (ts._hoops_GSSH);
	ts._hoops_GSSH->_hoops_GSHA = param_width;
	ts._hoops_GSSH->_hoops_SCAI = (param_flags & ~_hoops_ARCC);
	ts._hoops_SRHA = DL_DO_NOT_DEFER | _hoops_SRHH | _hoops_GAHH | DL_TEMPORARY_DATA;
	ts._hoops_GSSH->_hoops_CCHA = (_hoops_RSSH alter *)params;
	if (planes)
		ts._hoops_ICHA = normals;
	ts._hoops_AIHA = _hoops_AGCC;
	ts.points = _hoops_RGCC;
	ts.lengths = lengths;

	int length = count+2;

	if (_hoops_RRC == 3) {
		ts.lengths = lengths;
		ts._hoops_PHHA = count;
		ts.total = count * 3;
		ts.point_count = count * 3;
		used = 0;
		for (i = 0; i < count; i++) {
			lengths[i] = 3;
			_hoops_AGCC[used] = used;
			_hoops_AGCC[used+1] = used+1;
			_hoops_AGCC[used+2] = used+2;

			_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_APRA, points[used + 0]);
			_hoops_RGCC[used].x = _hoops_HPRA (_hoops_APRA, points[used + 0]) * _hoops_APCP;
			_hoops_RGCC[used].y = _hoops_IPRA (_hoops_APRA, points[used + 0]) * _hoops_APCP;
			_hoops_RGCC[used].z = _hoops_CPRA (_hoops_APRA, points[used + 0]) * _hoops_APCP;

			_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_APRA, points[used + 1]);
			_hoops_RGCC[used + 1].x = _hoops_HPRA (_hoops_APRA, points[used + 1]) * _hoops_APCP;
			_hoops_RGCC[used + 1].y = _hoops_IPRA (_hoops_APRA, points[used + 1]) * _hoops_APCP;
			_hoops_RGCC[used + 1].z = _hoops_CPRA (_hoops_APRA, points[used + 1]) * _hoops_APCP;

			_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_APRA, points[used + 2]);
			_hoops_RGCC[used + 2].x = _hoops_HPRA (_hoops_APRA, points[used + 2]) * _hoops_APCP;
			_hoops_RGCC[used + 2].y = _hoops_IPRA (_hoops_APRA, points[used + 2]) * _hoops_APCP;
			_hoops_RGCC[used + 2].z = _hoops_CPRA (_hoops_APRA, points[used + 2]) * _hoops_APCP;

			if (planes) {
				normals[used + 0] = planes[used + 0];
				normals[used + 1] = planes[used + 1];
				normals[used + 2] = planes[used + 2];
			}
			used += 3;
		}
	}
	else {
		ts._hoops_PHHA = 1;
		ts.total = length;
		ts.point_count = length;
		ts.lengths = &length;
		for (i = 0; i < length; i++) {
			_hoops_AGCC[i] = i;

			_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_APRA, points[i]);
			_hoops_RGCC[i].x = _hoops_HPRA (_hoops_APRA, points[i]) * _hoops_APCP;
			_hoops_RGCC[i].y = _hoops_IPRA (_hoops_APRA, points[i]) * _hoops_APCP;
			_hoops_RGCC[i].z = _hoops_CPRA (_hoops_APRA, points[i]) * _hoops_APCP;

			if (planes)
				normals[i + 0] = planes[i];
		}
	}

	h3ddata->_hoops_GSA = true;
	draw_3d_tristrip (_hoops_CRAI, &ts);
	h3ddata->_hoops_GSA = false;

	FREE_ARRAY (_hoops_RGCC, count*3, Point);
	FREE_ARRAY (normals, count*3, Vector);
	FREE_ARRAY (_hoops_AGCC, count*3, int);
	FREE_ARRAY (lengths, count, int);

	if (_hoops_ISAI (ts._hoops_GSSH) == 0)
		HI_Free_Texture_Parameters (ts._hoops_GSSH);

	/* _hoops_RH _hoops_PRCC _hoops_RIP _hoops_HRGR _hoops_AGIA _hoops_IS _hoops_CRHR _hoops_HRCC _hoops_HII _hoops_IRCC _hoops_IS
	   _hoops_CRCC _hoops_GPP _hoops_IS _hoops_RGR _hoops_CRHH */
	if (ts._hoops_HSAI != 0)
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "invalid ref count in draw_dc_textured_polytriangle");
}




/*****************************************************************************
						_hoops_SRCC
*****************************************************************************/
/*
 * _hoops_SRAC
 * _hoops_GACC _hoops_SIHR _hoops_RACC
 */
void draw_dc_colorized_polydot (
		Net_Rendition const &  nr,
		int count,
		DC_Point const * points,
		RGBAS32 const * colors,
		bool single)
{
	H3DData alter *h3ddata = H3DD (nr->_hoops_SRA);
	H3DShader *_hoops_RSR;
	H3DVertexBuffer &_hoops_PAIH = h3ddata->_hoops_CP;
	H3DVertexBufferCache *_hoops_HACP;
	int _hoops_RRC;
	int flags = H3DID_DC|H3DID_USE_FACE_DISPLACEMENT;
	int _hoops_HGIC = 0;
	int i, j, _hoops_IGIC;
	_hoops_IAPA const *_hoops_CAPA = null;

	if (!_hoops_HPCA(nr, _hoops_CAPA)) {
		// _hoops_HAIC'_hoops_RA _hoops_AACC _hoops_AGCR _hoops_RSSA - _hoops_HS _hoops_IS _hoops_CAH
		HD_Clip_DC_Polydot (nr, count, points, colors, _hoops_GPHC|(single?_hoops_RAIC:_hoops_PAIC));
		return;
	}

	H3D_TRACE(h3ddata, "draw_dc_colorized_polydot");

	if (!single)
		flags |= H3DID_VERTEX_COLORS;

	if (h3ddata->_hoops_IHP)
		flags |= H3DID_SPRITE_MARKER;

	_hoops_SRSP(h3ddata, nr, T_VERTICES, nr->_hoops_CPP->_hoops_PRH._hoops_HRH, 0, 0);
	_hoops_SSHH (h3ddata, nr, 0, null, flags, &_hoops_RSR);
	_hoops_GIAC (h3ddata, nr, _hoops_RSR);
	ENSURE_TRANSPARENCY (h3ddata, !h3ddata->_hoops_RHH.mode &&
		nr->_hoops_CPP->_hoops_PRH._hoops_HRH);

	if (h3ddata->_hoops_IHP) {
		float size = (float) h3ddata->_hoops_ISAA;
		_hoops_PACC (h3ddata, true, size, size);
		_hoops_RSR->_hoops_CCAA(nr, size, false, false, null);
	}
	else
		_hoops_PACC (h3ddata, false, 1.0f, 1.0f);


	h3ddata->_hoops_RPCI = nr->_hoops_CPA;

	if (single) {
		H3DVertexFormat _hoops_PPCP(H3DVF_PT);
		_hoops_ISC _hoops_PIHR;
		_hoops_PIHR.r = colors[0].r;
		_hoops_PIHR.g = colors[0].g;
		_hoops_PIHR.b = colors[0].b;
		_hoops_PIHR.a = colors[0].a;
		_hoops_RSR->_hoops_GIHR (&_hoops_PIHR);
		_hoops_RPIH (h3ddata, _hoops_PPCP, _hoops_HACP);
		_hoops_GCHC (h3ddata, _hoops_PPCP);
	}
	else {
		H3DVertexFormat _hoops_PPCP(H3DVF_PT_CLR);
		_hoops_RPIH (h3ddata, _hoops_PPCP, _hoops_HACP);
		_hoops_GCHC (h3ddata, _hoops_PPCP);
		_hoops_ICSP(h3ddata, H3DSHADE_FLAT);
	}
	_hoops_ICHC (count, _hoops_RRC, 1);

	//_hoops_CGIC _hoops_PHI _hoops_IIGR _hoops_HIPH _hoops_IS _hoops_SGIC _hoops_GGR _hoops_SPR _hoops_PHHR
	_hoops_IGIC = (int)_hoops_HACP->_hoops_GRIC;
	while (count) {
		i = j = 0;
		if (count < _hoops_IGIC)
			_hoops_IGIC = count;
		_hoops_HGIC=0;
		_hoops_HACP->Lock(_hoops_IGIC, &_hoops_PAIH);
		for (j = 0; j < _hoops_IGIC; j++) {
			_hoops_PAIH._hoops_AHCP(points[i].x + 0.5f, points[i].y + 0.5f, points[i].z);
			if (BIT (flags, H3DID_VERTEX_COLORS)) {
				_hoops_PAIH.color(h3ddata->_hoops_SHAP, colors[i]);
			}

			_hoops_PAIH._hoops_CPPH();
			points += _hoops_RRC;
			if (BIT (flags, H3DID_VERTEX_COLORS))
				colors += _hoops_RRC;
		}
		_hoops_HACP->Unlock();
		_hoops_SSCA (h3ddata, nr, _hoops_HACP, _hoops_CAPA, _hoops_IGIC, _hoops_GCCA, H3DPT_POINTLIST);
		count -= _hoops_IGIC;
	}
}


/*
 * _hoops_SRAC
 */
void draw_dc_polydot (
		Net_Rendition const &  nr,
		int count,
		DC_Point const * points)
{
	RGBAS32 const *rgbas32 = (RGBAS32 const *)&nr->_hoops_AHP->color._hoops_HRIR;
	draw_dc_colorized_polydot (nr, count, points, rgbas32, true);
}


/*****************************************************************************
						_hoops_AGRR _hoops_PGSA _hoops_PGSI
*****************************************************************************/
void draw_3d_text (
		Net_Rendition const &  nr,
		_hoops_HACC const *text)
{
	H3DData alter *h3ddata = H3DD (nr->_hoops_SRA);

	H3D_TRACE(h3ddata, "draw_3d_text");
	if (h3ddata->_hoops_CIGI)
		h3ddata->_hoops_CIGI->mask &= ~_hoops_PGCP;
	HD_Std_3D_Text (nr, text);

}

void draw_3d_grid (
		Net_Rendition const &  nr,
		Grid const *grid)
{
	H3DData alter *h3ddata = H3DD (nr->_hoops_SRA);

	H3D_TRACE(h3ddata, "draw_3d_grid");
	if (h3ddata->_hoops_CIGI)
		h3ddata->_hoops_CIGI->mask &= ~_hoops_RGCP;
	HD_Std_3D_Grid (nr, grid);

}

/*
 *
 * _hoops_SRAC
 *
 */
void draw_3d_image(
		Net_Rendition const &  nr,
		Image const *image)
{
	H3DData alter *h3ddata = H3DD (nr->_hoops_SRA);
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	H3DShader *_hoops_RSR;
	H3DVertexBufferCache *_hoops_HACP = 0;
	H3DVertexBuffer &_hoops_PAIH = h3ddata->_hoops_CP;
	int flags = H3DID_DC;
	Point alter points[4];
	float _hoops_IACC, _hoops_CACC, _hoops_SACC, _hoops_GPCC, u, v;
	int width, height;
	_hoops_RCR alter *txr=0;
	H3DTexture *id;
	_hoops_IAPA const *_hoops_CAPA = null;
	bool	_hoops_IAHC = false;

	//_hoops_RPP ((_hoops_CSCR->_hoops_RPCC == _hoops_APCC || _hoops_CSCR->_hoops_RPCC == _hoops_PPCC) &&
	//	_hoops_CSCR->_hoops_HPCC >= _hoops_IPCC->_hoops_CPCC->_hoops_SPCC) {
	//	_hoops_GHCC (_hoops_RHCC, _hoops_AHCC, _hoops_PHCC (_hoops_IRAP,
	//		"_hoops_HHCC _hoops_CSCR _hoops_AHPA _hoops_IIGR %_hoops_GHGP _hoops_GHCA _hoops_IHCC _hoops_HAIR _hoops_ARCR _hoops_AHPA _hoops_IIGR %_hoops_GHGP - _hoops_HAR _hoops_CHCC",
	//		(_hoops_SCSH)_hoops_CSCR->_hoops_HPCC, (_hoops_SCSH)_hoops_IPCC->_hoops_CPCC->_hoops_SPCC - 1));
	//	_hoops_ASRC;
	//}

	if (!HD_Calc_Image_Position_And_Size(nr, image, &width, &height, &_hoops_IACC, &_hoops_CACC, &_hoops_SACC))
		return;

	if (BIT(image->flags, _hoops_SHCC) ||
		BIT(image->flags, _hoops_GICC)) {
		_hoops_IAHC = true;
	}
	else if (nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR != 1.0f) {
		_hoops_IAHC = true;
	}

	//_hoops_RPP (_hoops_IRRC (_hoops_SCII->_hoops_RICC->_hoops_SGI, _hoops_AICC)) {
	//	_hoops_PICC _hoops_RCIC &	_hoops_HICC = _hoops_SCII->_hoops_RICC->_hoops_IICC;
	//	_hoops_CICC							_hoops_CAH = _hoops_RCPP;

	//	_hoops_RPP (_hoops_SCII->_hoops_SICC->_hoops_IHSP._hoops_GCCC) {
	//		_hoops_RPP (_hoops_HICC->_hoops_RCCC == _hoops_IRAP)
	//			_hoops_ACCC (_hoops_HICC);
	//		_hoops_PCCC = _hoops_HICC->_hoops_RCCC;
	//		_hoops_RPP (_hoops_HICC->_hoops_HCCC > _hoops_RRAP->_hoops_ICCC)
	//			_hoops_CAH = _hoops_IHPR;
	//	}
	//	_hoops_SHS {
	//		_hoops_PCCC = _hoops_HICC->_hoops_CCCC;
	//		_hoops_RPP (_hoops_HICC->_hoops_SCCC > _hoops_RRAP->_hoops_ICCC)
	//			_hoops_CAH = _hoops_IHPR;
	//	}
	//}

	if (h3ddata->_hoops_CIGI)
		h3ddata->_hoops_CIGI->mask &= ~_hoops_IGCP;

	if (_hoops_IAHC) {
		HD_Std_3D_Image(nr, image);
		return;
	}

	//_hoops_PRPP _hoops_SIAC _hoops_ACPP _hoops_HIS _hoops_SGS _hoops_GCAC _hoops_HCPH _hoops_CHR _hoops_RCAC _hoops_IS _hoops_SSS
	H3D_TRACE(h3ddata, "draw_3d_image");

	bool _hoops_GSCC = (
				nr->_hoops_ARA->image._hoops_RSCC.red != 1.0f ||
				nr->_hoops_ARA->image._hoops_RSCC.green != 1.0f ||
				nr->_hoops_ARA->image._hoops_RSCC.blue != 1.0f);
	if (_hoops_GSCC)
		flags |= H3DID_TINTED_IMAGE;

	txr = HI_Clone_Texture(0);
	txr->_hoops_SCR |= _hoops_RCRH;
	txr->_hoops_CGA = _hoops_ASCC;
	if (width < image->width>>1 || height < image->height>>1)
	txr->_hoops_RARH = _hoops_AARH;
	if (width == image->width && height == image->height)
		txr->_hoops_PSCC = _hoops_HSCC;


	txr->image = (Image alter*)image;
	_hoops_PRRH(txr->image);

	_hoops_SSHH (h3ddata, nr, T_IMAGES, null, flags, &_hoops_RSR);
	_hoops_GPRP (h3ddata, (h3ddata->_hoops_SH.mode || h3ddata->_hoops_RHH.mode) ? H3DMASK_RGBA : H3DMASK_RGB);
	_hoops_RHSA (h3ddata, H3DCULL_NONE);
	_hoops_GIAC (h3ddata, nr, _hoops_RSR);
	_hoops_PISP (h3ddata, BIT(_hoops_IHCR->flags, _hoops_PASP));
	ENSURE_DEPTH_MASK (h3ddata, !BIT(nr->transform_rendition->flags, _hoops_ISH));
	_hoops_HISP (h3ddata, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
	ENSURE_TRANSPARENCY (h3ddata, !h3ddata->_hoops_RHH.mode &&
		nr->_hoops_CPP->_hoops_PRH._hoops_HRH);

	Driver_Color color;
	color._hoops_HRIR.a = 255;
	if (_hoops_GSCC) {
		color._hoops_HRIR.r = (char) (nr->_hoops_ARA->image._hoops_RSCC.red*255);
		color._hoops_HRIR.b = (char) (nr->_hoops_ARA->image._hoops_RSCC.blue*255);
		color._hoops_HRIR.g = (char) (nr->_hoops_ARA->image._hoops_RSCC.green*255);
	}
	else {
		color._hoops_HRIR.r = 255;
		color._hoops_HRIR.b = 255;
		color._hoops_HRIR.g = 255;
	}
	_hoops_RSR->_hoops_GIHR(&color._hoops_HRIR);

	if (BIT (image->flags, _hoops_GRRH)) {
		/* _hoops_IPCP _hoops_AIRI _hoops_HIGR **_hoops_ISCC** _hoops_RH _hoops_IAAI _hoops_IPS _hoops_IIGR _hoops_RH _hoops_CSCR _hoops_PIH.
		   _hoops_HGPP _hoops_RRRH _hoops_CHR _hoops_CSCC _hoops_IS _hoops_IRS _hoops_SASI _hoops_RHPP, _hoops_HIH _hoops_SCH _hoops_HRGR _hoops_HAR _hoops_SSCC
		   _hoops_RH _hoops_GGSC _hoops_SR'_hoops_ASAR _hoops_IPIH _hoops_ASCA _hoops_CCA (_hoops_GGR _hoops_RGSC, _hoops_SCH _hoops_PAHH _hoops_GPGH'_hoops_RA).
		   _hoops_PSPC, _hoops_RH _hoops_ASGH _hoops_PGRH _hoops_HGRH _hoops_ASSP'_hoops_RA _hoops_GHAA _hoops_ARI. */
		_hoops_GACR alter *dl;
		H3D_Display_List alter *odl = 0;

		dl = image->_hoops_GAHA;
		if (dl)
			odl = (H3D_Display_List alter *) dl->list;
		if (!odl) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				   "GPU copy of image unexpectedly lost by dx9 or opengl driver.");
			return;
		}
		id = odl->item.texture.id;
		h3ddata->_hoops_GSCR->_hoops_GSAC (nr, null, _hoops_ACRH, id, 0);
		u = v = 1;
	}
	else {
		id = _hoops_PIGH (h3ddata, nr, txr, _hoops_ACRH);
		h3ddata->_hoops_GSCR->_hoops_GSAC (nr, txr, _hoops_ACRH, id, 0);
		if(!BIT(txr->_hoops_RHGH->flags, _hoops_PCRH)) {
			u=1.0f + 0.5/(float)(txr->_hoops_RHGH->width);
			v=1.0f - 0.5/(float)(txr->_hoops_RHGH->height);;
		}
		else {
			if(BIT(txr->_hoops_RHGH->flags, _hoops_AGSC)){
				u = (float)image->width/(float)(txr->_hoops_RHGH->width -2);
				v = (float)image->height/(float)(txr->_hoops_RHGH->height -2);
			}
			else {
				u = (float)(image->width + 0.5)/(float)(txr->_hoops_RHGH->width);
				v = (float)(image->height - 0.5)/(float)(txr->_hoops_RHGH->height);
			}
		}
	}

	if (_hoops_PGSC (_hoops_IHCR->_hoops_HGSC))
		_hoops_GPCC = _hoops_IGSC (_hoops_SACC, _hoops_IHCR);
	else
		_hoops_GPCC = 0.0f;

	float _hoops_CGSC = ((_hoops_IACC - (width * 0.5f)));
	float _hoops_SGSC = ((_hoops_CACC - (height * 0.5f)));
	_hoops_CGSC = (int) _hoops_CGSC;
	_hoops_SGSC = (int) _hoops_SGSC;

	points[0].x = _hoops_CGSC;
	points[0].y = _hoops_SGSC;
	points[0].z = _hoops_GPCC;

	points[1].x = _hoops_CGSC;
	points[1].y = _hoops_SGSC + height;
	points[1].z = _hoops_GPCC;

	points[2].x = _hoops_CGSC + width;
	points[2].y = _hoops_SGSC + height;
	points[2].z = _hoops_GPCC;

	points[3].x = _hoops_CGSC + width;
	points[3].y = _hoops_SGSC;
	points[3].z = _hoops_GPCC;


	H3DVertexFormat _hoops_PPCP(H3DVF_PT_TEX);
	_hoops_RPIH(h3ddata, _hoops_PPCP, _hoops_HACP);
	_hoops_HACP->Lock(6, &_hoops_PAIH);
	_hoops_PAIH._hoops_AHCP(points[0]);
	_hoops_PAIH._hoops_IICP(0, 1, 0);
	_hoops_PAIH._hoops_CPPH();
	_hoops_PAIH._hoops_AHCP(points[1]);
	_hoops_PAIH._hoops_IICP(0, 1 - v, 0);
	_hoops_PAIH._hoops_CPPH();
	_hoops_PAIH._hoops_AHCP(points[2]);
	_hoops_PAIH._hoops_IICP(u, 1 - v, 0);
	_hoops_PAIH._hoops_CPPH();
	_hoops_PAIH._hoops_AHCP(points[2]);
	_hoops_PAIH._hoops_IICP(u, 1 - v, 0);
	_hoops_PAIH._hoops_CPPH();
	_hoops_PAIH._hoops_AHCP(points[3]);
	_hoops_PAIH._hoops_IICP(u, 1, 0);
	_hoops_PAIH._hoops_CPPH();
	_hoops_PAIH._hoops_AHCP(points[0]);
	_hoops_PAIH._hoops_IICP(0, 1, 0);
	_hoops_PAIH._hoops_CPPH();
	_hoops_HACP->Unlock();

	_hoops_RSR->_hoops_GGIR();

	do {
		//_hoops_RPP (_hoops_PCCC != _hoops_IRAP) {
		//	_hoops_GRSC (_hoops_RRAP);
		//	_hoops_RRSC (_hoops_RRAP, _hoops_SCII, _hoops_PCCC->_hoops_ARSC);
		//	_hoops_PRSC (_hoops_RRAP);
		//}

		_hoops_HACP->_hoops_CHSA(h3ddata, H3DPT_TRIANGLELIST, 2);

		if (_hoops_CAPA != null)
			_hoops_CAPA = _hoops_CAPA->next;
	} while (_hoops_CAPA != null);
	h3ddata->_hoops_GSCR->SetTexture(0, 0);
	_hoops_HPRH(txr);

}


/*****************************************************************************
						_hoops_HRSC
*****************************************************************************/

/*
 * _hoops_PGAA: _hoops_HGH _hoops_APP _hoops_RPHH _hoops_RCC _hoops_HII _hoops_GPIA'_hoops_GRI _hoops_RPHH _hoops_GSGR.
 * _hoops_IRSC _hoops_ICCI._hoops_CRSC
 */
local H3DGlyph _hoops_SRSC (_hoops_GASC const & g)
{
	char const *t;

	if (g->name.length == 1) {
		if (g->name.text[0] == '.') {
			return H3D_GLYPH_DOT;
		}
		else if (g->name.text[0] == '@') {
			return H3D_GLYPH_FILLED_CIRCLE;
		}
		else if (g->name.text[0] == 'x' || g->name.text[0] == 'X') {
			return H3D_GLYPH_X_MARK;
		}
		else if (g->name.text[0] == '+') {
			return H3D_GLYPH_PLUS_MARK;
		}
	}
	else if (g->name.length == 3) {
		t = g->name.text;
		if (t[0] == '(' && t[1] == '*' && t[2] == ')') {
			return H3D_GLYPH_FILLED_CIRCLE;
		}
		else if (t[0] == '[' && t[1] == '*' && t[2] == ']') {
			return H3D_GLYPH_FILLED_SQUARE;
		}
	}
	return H3D_GLYPH_UNSUPPORTED;
}


/*
 * _hoops_PGAA: _hoops_HGH _hoops_IRS _hoops_SGGI _hoops_RASC _hoops_IIGR _hoops_RH _hoops_AASC _hoops_RHC-_hoops_GC _hoops_AHCR-_hoops_PIRA _hoops_IH _hoops_RH
 * _hoops_RSIR _hoops_PAAI.
 * _hoops_IRSC _hoops_ICCI._hoops_CRSC
 */
// _hoops_PASC _hoops_HASC _hoops_IS _hoops_IASC 
local float _hoops_CASC (_hoops_SASC const & cuboid, _hoops_HRPA const & matrix)
{
	Point	p[8];
	cuboid._hoops_GPSC(&p[0]);

	float	_hoops_RPSC = MAX_FLOAT;

	for (int i = 0; i < 8; i++) {
		float z = _hoops_CPRA (matrix.elements, p[i]);
		if (z < _hoops_RPSC)
			_hoops_RPSC = z;
	}

	return _hoops_RPSC;
}

local bool _hoops_APSC(
		Net_Rendition const & nr,
		_hoops_ICP const &_hoops_CCP,
		Polymarker const *pm,
		H3D_Display_List const *odl,
		float *size, 
		int *flags)
{
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	H3DData *h3ddata = H3DD(nr->_hoops_SRA);
	bool const _hoops_PPSC	= (h3ddata->dc->options._hoops_HPSC);
	
	// _hoops_HR _hoops_HAR _hoops_GRP _hoops_PPSR _hoops_IPSC
	bool _hoops_CPSC = false;

	// _hoops_HCIC _hoops_RGR _hoops_IRS _hoops_GSSP-_hoops_GC _hoops_GPIA?
	if ((_hoops_CCP->_hoops_HHP & _hoops_SPSC) && (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH)) {
		// _hoops_GHSC _hoops_IGIR.
		*flags |= _hoops_RHSC;

		if (pm && !_hoops_PPSC) {
			// _hoops_GRSH _hoops_AHSC _hoops_PAH _hoops_RH _hoops_SAIA _hoops_HGCR?
			_hoops_HRPA _hoops_PHSC;
			HI_Multiply_Matrices (&_hoops_IHCR->_hoops_IPH->data, &_hoops_IHCR->_hoops_SPH->_hoops_PRPA, &_hoops_PHSC);
			float const _hoops_HHSC = ((*size/h3ddata->_hoops_IHSC)-1)*_hoops_IHCR->_hoops_SPH->_hoops_SRIR;

			float	_hoops_RPSC = -1.0f;
			if (pm->bounding != null)
				_hoops_RPSC = _hoops_CASC(pm->bounding->cuboid, _hoops_PHSC);
			if (_hoops_RPSC > _hoops_HHSC)
				_hoops_CPSC = true;
		}
		else
			_hoops_CPSC = true;
	}
	else
	{
		// _hoops_PSGP _hoops_IGIR _hoops_GPIA. _hoops_CHSC _hoops_GH _hoops_IS _hoops_IRS _hoops_SHSC _hoops_AIR _hoops_IGIR.
		*size = ceil(*size);

		// _hoops_GISC _hoops_RISA _hoops_SAIA _hoops_IS _hoops_RSSA.
		if (*size <= 1) {
			*size = 0;
			*flags = _hoops_RISC;
		}
		else if (*size <= h3ddata->_hoops_IHSC || h3ddata->dc->options._hoops_HPSC)
			// _hoops_AISC _hoops_RAPR _hoops_IS _hoops_PGSA _hoops_GAR _hoops_PPSR _hoops_IPSC.
			_hoops_CPSC = true;

		// _hoops_CHSC _hoops_GH _hoops_IS _hoops_PISC _hoops_IGIR, _hoops_IAII _hoops_SSIA _hoops_PGSA _hoops_CCA _hoops_HISC _hoops_SPPR.
		*size += ((int)*size + 1) & 1;
	}

	// _hoops_CGP _hoops_SR _hoops_HS _hoops_HPPA _hoops_GHC, *_hoops_PPR* _hoops_SR'_hoops_ASAR?? _hoops_GRP _hoops_SRII _hoops_PAR _hoops_AI, _hoops_SR _hoops_PAH'_hoops_RA _hoops_SGH _hoops_PPSR _hoops_IPSC.
	if (BIT (_hoops_IHCR->flags, _hoops_CSP) && (*flags & (_hoops_HRAC|_hoops_IISC)))
		_hoops_CPSC = false;

	bool _hoops_CISC = false;
	if (pm)
		_hoops_CISC = (pm->_hoops_HCHA || BIT(pm->_hoops_SRHA,DL_INDEX_INTERPOLATION));
	else
		_hoops_CISC = BIT(odl->item.geometry._hoops_SRHA,DL_INDEX_INTERPOLATION);

	// _hoops_CAIP'_hoops_RA _hoops_HHGC _hoops_IS _hoops_AA _hoops_PPSR _hoops_IPSC _hoops_IH _hoops_III _hoops_IIHA _hoops_SAIA
	if (ANYBIT(*flags, _hoops_SISC))
		_hoops_CPSC = false;

	if ((_hoops_CCP->_hoops_CHA->_hoops_ARIR || _hoops_CISC) 
		&& (h3ddata->_hoops_GCSC || !_hoops_PPSC))
		_hoops_CPSC = false;

	// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_GRP _hoops_HCH _hoops_ICH, _hoops_PPSR _hoops_IPSC _hoops_GA'_hoops_RA _hoops_IPHR.
	// _hoops_AHH: _hoops_ACGR _hoops_GGSR _hoops_RCSC!
	if (h3ddata->_hoops_RHH.mode)
		_hoops_CPSC = false;

	if (_hoops_CPSC) {
		// _hoops_GISP _hoops_GAR _hoops_PPSR _hoops_IPSC _hoops_HII _hoops_IRS _hoops_PPSR _hoops_ACSC.
		*flags &= ~(_hoops_PCSC | _hoops_HCSC | _hoops_ICSC);
		*flags &= ~(_hoops_CCSC | _hoops_SCSC | _hoops_SISC);
		*flags |= _hoops_RISC | _hoops_PRAC;

		// _hoops_AHH: _hoops_HGI _hoops_HRGR _hoops_AIIA _hoops_IRS _hoops_GSSC _hoops_CCGP, _hoops_RPPR _hoops_SPAC _hoops_CCH.
		if (_hoops_PPSC) {
			*flags |= _hoops_RSSC;
			*flags &= ~_hoops_ASSC;
		}
	}

	return _hoops_CPSC;
}

/*
 * _hoops_PGAA: _hoops_HGH _hoops_IGIR _hoops_IH _hoops_GPIA, _hoops_CICA _hoops_GPP _hoops_PSSC _hoops_RPP _hoops_SSRR, _hoops_PPR _hoops_HSSC _hoops_ISSC _hoops_IS
 * _hoops_RRI _hoops_IRPR _hoops_RPHH _hoops_CSSC _hoops_RRGI _hoops_PCHC _hoops_SSSC.
 */
local int _hoops_ARAC(
	H3DData const *h3ddata,
	Net_Rendition const & nr,
	_hoops_ICP const &_hoops_CCP,
	Polymarker const *pm,
	H3D_Display_List const *odl,
	float *_hoops_GGGS)
{
	int flags;
	float _hoops_RGGS;
	float *size = &_hoops_RGGS;
	if (_hoops_GGGS)
		size = _hoops_GGGS;

	// _hoops_AGGS _hoops_GPPC (_hoops_PGSA _hoops_PGGS _hoops_HGGS/_hoops_PGGS _hoops_III) _hoops_PAH'_hoops_RA _hoops_SHH _hoops_GIR _hoops_HPP _hoops_RH _hoops_RHPP _hoops_HPGR _hoops_HCR
	if ( _hoops_CCP->glyph->flags & _hoops_IGGS )
		return _hoops_CGGS;

	// _hoops_AIHH _hoops_RPP _hoops_RPHH _hoops_HRGR _hoops_APP
	H3DGlyph glyph;

	// _hoops_GRSH _hoops_AHSC _hoops_CHR _hoops_RH _hoops_SAIA? (_hoops_SGGS _hoops_HII _hoops_ICCI._hoops_CRSC:(14699)
	if (_hoops_CCP->ysize < 0)
		*size = 0.707f * HD_Compute_Generic_Size (nr, _hoops_CCP->_hoops_PHP, _hoops_CCP->_hoops_HHP, 1.0f, false, 0, true);
	else
		*size = 1.414f * _hoops_CCP->ysize;

	if (*size == 0)
		glyph = H3D_GLYPH_DOT;
	else if (*size < 1 && !(BIT (_hoops_CCP->_hoops_HHP,_hoops_SPSC) && (nr->transform_rendition->_hoops_SPH->projection == _hoops_GHH)))
		glyph = H3D_GLYPH_DOT;
	else
		glyph = _hoops_SRSC(_hoops_CCP->glyph);

	switch (glyph)
	{
		case H3D_GLYPH_DOT :
			flags = _hoops_RISC;
			break;

		case H3D_GLYPH_FILLED_SQUARE :
			flags = _hoops_PCSC | _hoops_HCSC | _hoops_ICSC | _hoops_ASSC;
			break;

		case H3D_GLYPH_FILLED_CIRCLE :
			if (!h3ddata->dc->options._hoops_HPSC)
				return _hoops_CGGS;

			flags = _hoops_PCSC | _hoops_HCSC | _hoops_ICSC | _hoops_HRAC | _hoops_ASSC;
			break;

		case H3D_GLYPH_X_MARK :
			flags = _hoops_CCSC | _hoops_SISC | _hoops_ICSC | _hoops_ASSC;
			break;

		case H3D_GLYPH_PLUS_MARK:
			flags = _hoops_SCSC | _hoops_SISC | _hoops_ICSC | _hoops_ASSC;
			break;

		case H3D_GLYPH_UNSUPPORTED:
#define _hoops_GRGS
#ifdef _hoops_GRGS
			// _hoops_SHCA/_hoops_RRGS _hoops_AHPP _hoops_IS _hoops_SHH _hoops_ARGS _hoops_PRGS _hoops_HPGR _hoops_RH _hoops_HRGS - _hoops_CPS _hoops_HRGR _hoops_IRGS, _hoops_PAH'_hoops_RA _hoops_CRGS _hoops_RPP _hoops_SAIA _hoops_IPHR _hoops_PAR _hoops_HAR.
			if ( h3ddata->_hoops_CRAP == _hoops_SRAP )
				return _hoops_CGGS;

			// _hoops_HAIC'_hoops_RA _hoops_SRGS _hoops_AIIR _hoops_CRGR _hoops_GPIA _hoops_HH
			if ( !BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP) &&
				BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP))
				return _hoops_CGGS;

			// _hoops_HAIC'_hoops_RA _hoops_SGH _hoops_GAGS _hoops_GPPC _hoops_HPGR _hoops_HAGH _hoops_PGRR.
			if ( _hoops_CCP->_hoops_HHP & _hoops_SPSC )
				return _hoops_CGGS;

			// _hoops_HAIC'_hoops_RA _hoops_RGHH _hoops_RH _hoops_RAGS _hoops_GAPA _hoops_RPHH _hoops_HH _hoops_PPR _hoops_GPHA/_hoops_APIR _hoops_AAGS
			if (ANYBIT (_hoops_CCP->glyph->flags, _hoops_PAGS|_hoops_HAGS))
				return _hoops_CGGS;

			// _hoops_HHPC _hoops_IAGS _hoops_IRS _hoops_HH _hoops_PPR _hoops_SGH _hoops_SCH.
			flags = _hoops_PCSC | _hoops_HCSC | _hoops_ICSC | _hoops_ASSC | _hoops_IISC;

			// _hoops_RGPA _hoops_CAGS _hoops_IH _hoops_SHI _hoops_GPPC
			// _hoops_AHH: _hoops_SIGP: _hoops_SAGS _hoops_RGHH _hoops_RGR _hoops_HPGR _hoops_SRGS _hoops_GHIR _hoops_HIH _hoops_SCH _hoops_AGSR _hoops_GPGS _hoops_RRI _hoops_RRGR, _hoops_RGR _hoops_HRGR _hoops_RPGS _hoops_HIH _hoops_APGS 
			// _hoops_HH _hoops_PPGS _hoops_PPR _hoops_CISA _hoops_HPGS.
			{ 
				float _hoops_IPGS = 2.0f * _hoops_IAAA( Abs(GLYPH_HOTSPOT_X(_hoops_CCP->glyph)), Abs(GLYPH_HOTSPOT_Y(_hoops_CCP->glyph)) ) / GLYPH_RADIUS(_hoops_CCP->glyph);
				*size *= (1.0f + _hoops_IPGS);
			}

			// _hoops_CPGS _hoops_IRCH *_hoops_IGIR: 2 _hoops_IH _hoops_SPGS, 2 _hoops_RRI _hoops_IH _hoops_GHGS _hoops_IS _hoops_PSSP _hoops_RHGS _hoops_SAIA (_hoops_PGAP _hoops_HCR _hoops_AHGS _hoops_IS _hoops_SHH _hoops_SHI _hoops_HPP _hoops_IRS _hoops_AIR?)
			*size += 4.0f;

			// _hoops_CGP _hoops_HACH *_hoops_IGIR _hoops_HRGR _hoops_CHPP, _hoops_GAGS _hoops_SAIA _hoops_CHR _hoops_IRS _hoops_AHCI _hoops_PHGS-_hoops_PSAP
			if ( *size > 64.0f )
				return _hoops_CGGS;

			// _hoops_AAHA _hoops_PSHA _hoops_GGHC _hoops_HHGS, _hoops_PPR _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA _hoops_RPP _hoops_SR _hoops_CHR _hoops_IPIH _hoops_IHGS _hoops_IGI _hoops_IS _hoops_PGSA _hoops_IRS _hoops_GPIA _hoops_PAR _hoops_IRS _hoops_PAAI.  _hoops_CACH 6471_hoops_CHGS
			if (_hoops_CCAI (nr->_hoops_SRA->_hoops_SPA->color, Color_VERTEX|Color_MARKER))
				return _hoops_CGGS;

			// _hoops_HHPC _hoops_HPPR _hoops_AI
			break;
#else
			return _hoops_CGGS;
#endif

		default :
			return _hoops_CGGS;
	}

	if (flags == _hoops_RISC) {
		// _hoops_SHGS _hoops_PGSA _hoops_GIGS _hoops_GAR _hoops_SSIA _hoops_CHR _hoops_HPGR *_hoops_IGIR _hoops_AHHR.
		*size = 0;
	}
	else
	{
		// _hoops_CGP _hoops_SR _hoops_HS _hoops_SRII _hoops_PAR _hoops_IPSH, _hoops_CSRA *_hoops_IGIR _hoops_GH
		if (ANYBIT(flags, (_hoops_HRAC | _hoops_SCSC | _hoops_IISC)))
			*size *= 1.414f;

		// _hoops_HGH _hoops_IGH _hoops_GRP _hoops_PPSR _hoops_IPSC _hoops_PAR _hoops_HAR, _hoops_PPR _hoops_HGSR
		_hoops_APSC(nr, _hoops_CCP, pm, odl, size, &flags);
	}

	// _hoops_AP
	return flags;
}


/*
 * _hoops_RIGS _hoops_IRS _hoops_PAAI _hoops_GGR _hoops_HGAI _hoops_CCH. _hoops_AIGS _hoops_IS _hoops_SHH _hoops_PIGS _hoops_HPP _hoops_HIGS, _hoops_CR _hoops_RGR _hoops_IIGS _hoops_RH
 * _hoops_CIGS _hoops_CAH _hoops_HCGC _hoops_PPR _hoops_ARH _hoops_GH _hoops_RPIC/_hoops_SRGS _hoops_PIAP. _hoops_SIGS _hoops_SHH _hoops_IGI _hoops_GCGS.
 */
local void _hoops_RCGS (
		Net_Rendition const &		nr,
		Polymarker const *			pm,
		_hoops_ICP const &	_hoops_CCP,
		H3DShader *					_hoops_RSR,
		H3DVertexFormat				_hoops_PPCP,
		const int					_hoops_RRAC,
		_hoops_IAPA const * const	_hoops_ACGS,
		int							start,
		int							end,
		_hoops_HCI *			_hoops_RPCP)
{
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	H3DData alter *				h3ddata = H3DD(dc);
	H3DVertexBufferCache *		_hoops_HACP = null;
	H3DIndexBufferCache *		_hoops_RAHC = null;
	H3DVertexBuffer				&_hoops_PAIH = h3ddata->_hoops_CP;
	short *						_hoops_CHPC = null;
	int 						_hoops_IGIC = 0;
	int 						i = 0, j = 0;
	bool						_hoops_PCGS = false;
	int							_hoops_HCGS = start - 1;

	_hoops_RPIH(h3ddata, _hoops_PPCP, _hoops_HACP);
	_hoops_RCHC(h3ddata, _hoops_HACP);
	_hoops_RAHC = h3ddata->_hoops_ACHC;

	if (ANYBIT(_hoops_RRAC,_hoops_HCSC | _hoops_SISC) == 0) {
		// _hoops_PHIR _hoops_SRHR _hoops_CCA _hoops_RSSA.
		_hoops_IGIC = _hoops_AHIA((int)_hoops_HACP->_hoops_GRIC, end - start);

		for (i = start; i < end; i++) {
			if (_hoops_PCGS && j == _hoops_IGIC) {
				_hoops_HACP->Unlock();
				_hoops_PCGS = false;

				// _hoops_GISP _hoops_CCA _hoops_HPPA _hoops_GHC, _hoops_RPP _hoops_GII.
				_hoops_IAPA const *_hoops_CAPA = _hoops_ACGS;
				do {
					if (_hoops_CAPA) {
						_hoops_RSR->_hoops_CHPA(nr, _hoops_CAPA);
						_hoops_CAPA = _hoops_CAPA->next;
					}
					_hoops_GPRH (_hoops_ICGS) += j;
					_hoops_HACP->_hoops_HGSA(h3ddata, H3DPT_POINTLIST, j);

				} while (_hoops_CAPA);
				_hoops_HACP->_hoops_CGSA();
				j = 0;
			}
			if (!_hoops_PCGS) {
				_hoops_HACP->Lock(_hoops_IGIC, &_hoops_PAIH);
				_hoops_PCGS = true;
			}

			if (pm->_hoops_AIHA)
				_hoops_HCGS = pm->_hoops_AIHA[i];
			else
				_hoops_HCGS++;

			_hoops_ASCP(nr, pm, _hoops_CCP, &_hoops_PAIH, _hoops_HCGS, _hoops_RPCP);
			_hoops_PAIH._hoops_CPPH();
			j++;
		}

		if (_hoops_PCGS) {
			_hoops_HACP->Unlock();
			_hoops_PCGS = false;

			// _hoops_GISP _hoops_CCA _hoops_HPPA _hoops_GHC, _hoops_RPP _hoops_GII.
			_hoops_IAPA const *_hoops_CAPA = _hoops_ACGS;
			do {
				if (_hoops_CAPA) {
					_hoops_RSR->_hoops_CHPA(nr, _hoops_CAPA);
					_hoops_CAPA = _hoops_CAPA->next;
				}
				_hoops_GPRH (_hoops_ICGS) += j;
				_hoops_HACP->_hoops_HGSA(h3ddata, H3DPT_POINTLIST, j);

			} while (_hoops_CAPA);
			_hoops_HACP->_hoops_CGSA();
		}
	}
	else {
		// _hoops_SR _hoops_RRP 6 _hoops_PSPI _hoops_RIR _hoops_GPIA, _hoops_PPR _hoops_SR _hoops_HS _hoops_IRS _hoops_AHPA _hoops_IIGR 16384 _hoops_PSPI
		int _hoops_CCGS = 6;
		H3DPRIMITIVETYPE _hoops_SCGS = H3DPT_TRIANGLELIST;

		if (ANYBIT(_hoops_RRAC, _hoops_SISC)) {
			_hoops_CCGS = 4;
			_hoops_SCGS = H3DPT_LINELIST;
		}

		_hoops_IGIC = _hoops_AHIA((int)_hoops_HACP->_hoops_GRIC / _hoops_CCGS, (end - start) * _hoops_CCGS);

		// _hoops_HGI _hoops_GSGS _hoops_PIH _hoops_HRGR _hoops_RSGS. _hoops_IPCP _hoops_CGHI _hoops_PGCR _hoops_ASGS _hoops_CHR _hoops_HGSR _hoops_RIR _hoops_PPSR.
		int _hoops_HIPC;
		_hoops_SII(_hoops_HCRR, 0, _hoops_RPCP, &_hoops_HIPC, null, null);

		for (i = start; i < end; i++) {
			if (_hoops_PCGS && j == _hoops_IGIC) {
				_hoops_HACP->Unlock();
				_hoops_RAHC->Unlock();
				_hoops_PCGS = false;

				// _hoops_GISP _hoops_CCA _hoops_HPPA _hoops_GHC
				_hoops_IAPA const *_hoops_CAPA = _hoops_ACGS;
				do {
					if (_hoops_CAPA) {
						_hoops_RSR->_hoops_CHPA(nr, _hoops_CAPA);
						_hoops_CAPA = _hoops_CAPA->next;
					}
					_hoops_GPRH (_hoops_ICGS) += j;

					_hoops_RAHC->_hoops_CHSA(h3ddata, _hoops_SCGS, j * 4, j * 2);
					_hoops_RAHC->_hoops_CGSA();

				} while(_hoops_CAPA);
				j = 0;
			}
			if (!_hoops_PCGS) {
				_hoops_HACP->Lock(_hoops_IGIC*4, &_hoops_PAIH);
				_hoops_RAHC->Lock(_hoops_IGIC*_hoops_CCGS, &_hoops_CHPC);		// 6 _hoops_PSPI _hoops_IS 4 _hoops_GIHA, _hoops_PAR _hoops_SSAI * 1.5
				_hoops_PCGS = true;
			}

			if (pm->_hoops_AIHA)
				_hoops_HCGS = pm->_hoops_AIHA[i];
			else
				_hoops_HCGS++;

			_hoops_ASCP(nr, pm, _hoops_CCP, &_hoops_PAIH, _hoops_HCGS, _hoops_RPCP);

			// _hoops_PSGS _hoops_SRS _hoops_ARIP _hoops_IIGR _hoops_GPHA _hoops_AIAA _hoops_IACH.
			_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
			_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(2);
			_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(3);

			if (BIT(_hoops_RRAC, _hoops_PCSC)) {
				// _hoops_RAP _hoops_HSGS _hoops_SHI _hoops_GGR _hoops_GRR _hoops_IPS.
				_hoops_PAIH._hoops_RRCI(0)._hoops_ARHC(-1.0f, -1.0f, _hoops_HIPC);
				_hoops_PAIH._hoops_RRCI(1)._hoops_ARHC(+1.0f, -1.0f, _hoops_HIPC);
				_hoops_PAIH._hoops_RRCI(2)._hoops_ARHC(-1.0f, +1.0f, _hoops_HIPC);
				_hoops_PAIH._hoops_RRCI(3)._hoops_ARHC(+1.0f, +1.0f, _hoops_HIPC);

				_hoops_PAIH._hoops_CPPH(4);

				_hoops_CHPC[0] = j * 4 + 0;
				_hoops_CHPC[1] = j * 4 + 1;
				_hoops_CHPC[2] = j * 4 + 2;
				_hoops_CHPC[3] = j * 4 + 1;
				_hoops_CHPC[4] = j * 4 + 3;
				_hoops_CHPC[5] = j * 4 + 2;
				_hoops_CHPC += 6;
			}
			else if (BIT(_hoops_RRAC, _hoops_SISC)) {
				if (BIT(_hoops_RRAC, _hoops_CCSC)) {
					// _hoops_RAP _hoops_HSGS _hoops_SHI _hoops_GGR _hoops_GRR _hoops_IPS.
					_hoops_PAIH._hoops_RRCI(0)._hoops_ARHC(-0.99f, -0.99f, _hoops_HIPC);
					_hoops_PAIH._hoops_RRCI(1)._hoops_ARHC(+0.99f, +0.99f, _hoops_HIPC);
					_hoops_PAIH._hoops_RRCI(2)._hoops_ARHC(+0.99f, -0.99f, _hoops_HIPC);
					_hoops_PAIH._hoops_RRCI(3)._hoops_ARHC(-0.99f, +0.99f, _hoops_HIPC);
					_hoops_PAIH._hoops_CPPH(4);
				}
				else if (BIT(_hoops_RRAC, _hoops_SCSC)) {
					// _hoops_RAP _hoops_HSGS _hoops_SHI _hoops_GGR _hoops_GRR _hoops_IPS.
					_hoops_PAIH._hoops_RRCI(0)._hoops_ARHC(0.0f, -1.0f, _hoops_HIPC);
					_hoops_PAIH._hoops_RRCI(1)._hoops_ARHC(0.0f, +1.0f, _hoops_HIPC);
					_hoops_PAIH._hoops_RRCI(2)._hoops_ARHC(-1.0f, 0.0f, _hoops_HIPC);
					_hoops_PAIH._hoops_RRCI(3)._hoops_ARHC(+1.0f, 0.0f, _hoops_HIPC);
					_hoops_PAIH._hoops_CPPH(4);
				}

				_hoops_CHPC[0] = j * 4 + 0;
				_hoops_CHPC[1] = j * 4 + 1;
				_hoops_CHPC[2] = j * 4 + 2;
				_hoops_CHPC[3] = j * 4 + 3;
				_hoops_CHPC += 4;
			}
			j++;
		}

		if (_hoops_PCGS) {
			_hoops_HACP->Unlock();
			_hoops_RAHC->Unlock();
			_hoops_PCGS = false;

			_hoops_IAPA const *_hoops_CAPA = _hoops_ACGS;
			do {
				if (_hoops_CAPA) {
					_hoops_RSR->_hoops_CHPA(nr, _hoops_CAPA);
					_hoops_CAPA = _hoops_CAPA->next;
				}
				_hoops_GPRH (_hoops_ICGS) += j;

				_hoops_RAHC->_hoops_CHSA(h3ddata, _hoops_SCGS, j * 4, j * 2);
			} while(_hoops_CAPA);
			_hoops_RAHC->_hoops_CGSA();
		}
	}
}

local void _hoops_ISGS (
	Net_Rendition const & nr)
{
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;
	H3DData alter *				h3ddata = H3DD(dc);
	
	H3D_TRACE(h3ddata, "draw_one_glyph");

	// _hoops_CSGS _hoops_GPIA _hoops_IPP _hoops_CCA _hoops_GPHA _hoops_IPP _hoops_IH _hoops_RPHH _hoops_ASCA
	Net_Rendition _hoops_SSGS = nr;
	_hoops_SSGS.Modify();
	_hoops_SSGS->_hoops_GSP = _hoops_SSGS->_hoops_SCP;

	// _hoops_SSSA _hoops_IGIR _hoops_RPP _hoops_RGHP
	if (_hoops_SSGS->_hoops_GSP->ysize < 0) {
		_hoops_ICP alter &	_hoops_GGRS = _hoops_SSGS->_hoops_GSP.Modify();
		float size = HD_Compute_Generic_Size (nr, _hoops_GGRS->_hoops_PHP, _hoops_GGRS->_hoops_HHP, 1.0f, false, 0, true);
		_hoops_GGRS->ysize = size*0.5f;
		_hoops_GGRS->_hoops_RGRS = size*0.5f*nr->_hoops_SRA->current._hoops_AGRS;
	}

	// _hoops_GCAR _hoops_HPPA _hoops_GHC.
	_hoops_SSGS->transform_rendition.Modify()->flags &= ~_hoops_CSP;

	// _hoops_PGRS _hoops_PGSI _hoops_ISSC _hoops_IS _hoops_RHPP _hoops_HIS _hoops_SCH _hoops_PAH _hoops_CACH _hoops_HCR _hoops_RPHH _hoops_PICA.
	int _hoops_HGRS = 0;
	while (!_hoops_AGGR(dc->_hoops_IPCI->id, "driver")) {
		_hoops_HGRS++;
		_hoops_IGRS (dc);
	}

	// _hoops_GISP _hoops_SPR _hoops_IPS _hoops_HPGR _hoops_RH _hoops_CGRS
	HD_Std_DC_Polymarker(_hoops_SSGS, 1, &_hoops_HPCH::_hoops_IPCH, null, null);

	// _hoops_IPRP _hoops_PGSI
	while (_hoops_HGRS-- > 0)
		_hoops_SGRS (dc);
}



void draw_3d_marker (
		Net_Rendition const & nr,
		Marker const * m)
{
	Display_Context alter *	dc = (Display_Context alter *) nr->_hoops_SRA;
	H3DData alter *			h3ddata = H3DD (dc);
	bool					single = !h3ddata->_hoops_AHPI;

	if (h3ddata->_hoops_ISCI)	{
		if (!h3ddata->_hoops_CIGI->_hoops_IHAI)
			h3ddata->_hoops_CIGI->_hoops_IHAI = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);

		_hoops_IRHA *pair = POOL_NEW(dc->memory_pool, _hoops_IRHA)(nr, m, dc->_hoops_SPA->modelling_matrix, dc->_hoops_SPA->color, single);	

		h3ddata->_hoops_CIGI->_hoops_IHAI->AddFirst(pair);
		return;
	}

	do {
		HD_Std_3D_Marker(nr, (Marker const *)m);
		m = (Marker const *)m->next;
		if (single)
			break;
	} while (m && m->type == _hoops_PCIP);
}


/*
 * _hoops_GRRS _hoops_IGH _hoops_PAR _hoops_HAR _hoops_IS _hoops_CAH _hoops_RH _hoops_GPIA, _hoops_ARH _hoops_GH _hoops_RPIC/_hoops_SRGS _hoops_PIAP, _hoops_PPR _hoops_PSCR _hoops_RRRS _hoops_RH
 * _hoops_PAAI _hoops_RPP _hoops_SCH _hoops_HRGR _hoops_GPP _hoops_RH _hoops_AIRI _hoops_HIGR _hoops_CRAA. _hoops_HSRR _hoops_RH _hoops_HGAI _hoops_CCH _hoops_CRAA, _hoops_RH _hoops_ARRS _hoops_API
 * _hoops_HRGR _hoops_PIGS _hoops_IS _hoops_SCRI _hoops_RH _hoops_ASCA _hoops_RIIA.
 */
void _hoops_GPCI (
	Net_Rendition const &		nr,
	Polymarker const *			pm,
	_hoops_ICP const &	_hoops_CCP,
	H3D_Display_List_Bin *		_hoops_RRHA)
{
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;
	_hoops_HHA const &	matr = _hoops_CCP->_hoops_CHA;
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	Polymarker alter *			_hoops_PRRS = (Polymarker alter *) pm;
	H3DData alter *				h3ddata = H3DD(dc);
	H3DIndexedBufferObject *	_hoops_HRRS = null;
	H3DVertexFormat 			_hoops_PPCP;
	H3DVertexBuffer 			&_hoops_PAIH = h3ddata->_hoops_CP;
	H3DIndexBuffer				_hoops_RAHC;
	H3DShader *					_hoops_RSR;
	_hoops_GACR *				dl = null;
	H3D_Display_List *			odl = null;
	bool 						_hoops_IRRS = false;
	bool 						_hoops_IAHC = false;
	bool 						_hoops_CRRS = false;
	int 						i, j;
	int 						_hoops_SRRS = 0;
	int 						_hoops_HCGS = -1;
	int 						_hoops_SRHA = 0;
	int 						_hoops_CARI = 0;
	float						size = 0;
	int							_hoops_CCGS = 1;
	int							_hoops_GARS = 1;
	_hoops_IAPA const *	_hoops_CAPA = null;
	float						_hoops_IRIR = nr->_hoops_GSP->_hoops_CHA->_hoops_IRIR;
	bool						_hoops_CISP = (_hoops_IRIR < 1.0f) || pm->_hoops_RGIA;
	H3DTexture *				glyph = null;
	Type						type;
	
	UNREFERENCED(_hoops_RRHA);

	H3D_TRACE(h3ddata, "draw_3d_polymarker");

	if (_hoops_CCP == nr->_hoops_GSP)
		type = T_MARKERS;
	else
		type = T_VERTICES;

	if (pm->_hoops_HCHA) {
		Polymarker alter *_hoops_RARS = (Polymarker alter *)pm;
		_hoops_RARS->_hoops_SRHA |= _hoops_GGIA;
	}
	
	// _hoops_ICGP _hoops_GPIA _hoops_IGIR _hoops_PPR _hoops_IPHR _hoops_GGSR _hoops_RSH _hoops_IS _hoops_PGSA _hoops_SCH.
	int const _hoops_RRAC = _hoops_ARAC(h3ddata, nr, _hoops_CCP, pm, null, &size);

	// _hoops_AARS _hoops_GII _hoops_GPPC _hoops_SR _hoops_PAH'_hoops_RA _hoops_SRGS.
	if (_hoops_RRAC == _hoops_CGGS)
		_hoops_IAHC = true;

	// _hoops_AARS _hoops_RPP _hoops_SR _hoops_PAH'_hoops_RA _hoops_SGH _hoops_RH _hoops_HPPA _hoops_GHC
	if (!_hoops_HPCA(nr, _hoops_CAPA))
		_hoops_IAHC = true;

	if (_hoops_RRAC & _hoops_IISC) {

		// _hoops_GRSH _hoops_AHSC 
		unsigned int _hoops_PARS = static_cast<unsigned int>(size);

		// _hoops_ACGR _hoops_HARS _hoops_IIGR _hoops_HIGR
		_hoops_IARS* list = h3ddata->glyph_textures;

		// _hoops_SGCH _hoops_IH _hoops_CARS
		while ( list ) {
			if ( list->size == _hoops_PARS && list->glyph_key == _hoops_CCP->glyph->key )
				break;
			list = list->next;
		}

		// _hoops_CGP _hoops_SR _hoops_SARS'_hoops_RA _hoops_HGCR _hoops_SPR, _hoops_GA'_hoops_RA _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_RPHH _hoops_IH _hoops_IRS _hoops_RSRA _hoops_PAAI (_hoops_GPRS _hoops_IS _hoops_RPRS _hoops_APRS _hoops_PHRI)
		if ( !list && pm->length > 1 ) {
			// _hoops_ICAH _hoops_IS _hoops_ARPR _hoops_PPR _hoops_CISA _hoops_GGR _hoops_IRS _hoops_CCAH _hoops_HH.
			h3ddata->_hoops_GSCR->CreateTexture(_hoops_PARS * h3ddata->_hoops_HSAA, 
												_hoops_PARS * h3ddata->_hoops_ISAA, 
												1, H3DTEXUSAGE_RENDERTARGET, H3DFMT_A8R8G8B8, &glyph);
			if ( glyph ) {
				// _hoops_GISA _hoops_PPR _hoops_CISA _hoops_GGR _hoops_CCAH _hoops_HIGR _hoops_RARP
				ZALLOC(list, _hoops_IARS);
				list->size = _hoops_PARS;
				list->glyph_key = _hoops_CCP->glyph->key;
				list->texture = glyph;

				// _hoops_RGPA _hoops_IS _hoops_HIGR
				list->next = h3ddata->glyph_textures;
				h3ddata->glyph_textures = list;

				// _hoops_GISP _hoops_IS _hoops_SCH
				_hoops_PPRS _hoops_HPRS;
				h3ddata->_hoops_GSCR->_hoops_IPRS(&_hoops_HPRS);
				h3ddata->_hoops_GSCR->_hoops_GPAP(glyph);

				// _hoops_CPRS _hoops_ASGH _hoops_ICPP _hoops_SPRS-_hoops_GHRS (_hoops_PGAP _hoops_GRS _hoops_SHH _hoops_GRGR _hoops_GGR _hoops_RHRS) _hoops_PPR _hoops_HHPR
				if ( h3ddata->_hoops_CRAP == _hoops_AHRS )
					h3ddata->_hoops_IHP = true;

				// _hoops_PHRS _hoops_ICIH _hoops_IH _hoops_ICPP
				_hoops_HHRS(h3ddata, 0, 0, _hoops_PARS, _hoops_PARS);

				// _hoops_CAAP
				h3ddata->_hoops_GSCR->Clear(H3DCLEAR_TARGET, 0, 0, 0, true);

				// _hoops_IHRS _hoops_SPR _hoops_RPHH _hoops_PPR _hoops_GASH _hoops_SCH.
				h3ddata->glyph.mode = TRUE;
				h3ddata->glyph._hoops_HAP = _hoops_PARS;
				_hoops_ISGS(nr);
				h3ddata->glyph.mode = FALSE;

				// _hoops_HGI _hoops_GRS _hoops_GACC _hoops_PHIH _hoops_GSSR _hoops_ICPP _hoops_PAAA
				h3ddata->_hoops_GSCR->_hoops_CHRS(&_hoops_HPRS);

				// _hoops_SHRS: _hoops_CPIP _hoops_ICRP _hoops_RPAI _hoops_RPHH 
				// _hoops_RRAP->_hoops_ICRI->_hoops_GIRS(_hoops_RRAP, _hoops_RPHH, 10, 40, 10 + 4 * _hoops_RIRS, 10 + 4 * _hoops_RIRS);
			}
		}

		// _hoops_CGP _hoops_HPGR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_HCR _hoops_SGS _hoops_SR _hoops_HS _hoops_PCCP _hoops_RARP, _hoops_SGH _hoops_SCH
		if ( list )
			// _hoops_SGPR _hoops_APRS _hoops_RPHH
			glyph = list->texture;
		else
			// _hoops_AIRS - _hoops_PSP _hoops_HCSP _hoops_HIH _hoops_IS _hoops_CAH
			_hoops_IAHC = true;
	}

	if (_hoops_IAHC) {
		if (h3ddata->_hoops_CIGI) {
			if (dc->_hoops_RAI && dc->_hoops_RAI->type == _hoops_PIRS)
				h3ddata->_hoops_CIGI->mask &= ~_hoops_HCIP;
			else
				h3ddata->_hoops_CIGI->mask &= ~_hoops_RGPI;
		}
		HD_Std_3D_Polymarker(nr, pm);
		return;
	}

	
	if (h3ddata->_hoops_ISCI > 0) {
		bool _hoops_HIRS = false;

		if (BIT (pm->_hoops_SRHA, DL_DO_NOT_DEFER))
			_hoops_HIRS = true;

		if (!_hoops_HIRS) {
			_hoops_IRHA *pair;
			_hoops_AIGI *list = null;
			bool _hoops_IIRS = false;

			if (dc->_hoops_RAI && 
				dc->_hoops_RAI->type == _hoops_PIRS) 
			{
				_hoops_IIRS = (dc->_hoops_SPA->color && BIT (dc->_hoops_SPA->color->_hoops_GHA, Color_MARKER));
				if (BIT (h3ddata->_hoops_CIGI->_hoops_RRSI, _hoops_HCIP))
					return;  //_hoops_CIRS _hoops_SIRS _hoops_IS _hoops_CRHR _hoops_GCRS _hoops_RCRS _hoops_CPAP
				if (!h3ddata->_hoops_CIGI->_hoops_IHAI)
					h3ddata->_hoops_CIGI->_hoops_IHAI = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);
				list = h3ddata->_hoops_CIGI->_hoops_IHAI;			
			}
			else {
				_hoops_IIRS = (dc->_hoops_SPA->color && BIT (dc->_hoops_SPA->color->_hoops_GHA, Color_VERTEX));
				if (BIT (h3ddata->_hoops_CIGI->_hoops_RRSI, _hoops_RGPI))
					return;  //_hoops_CIRS _hoops_SIRS _hoops_IS _hoops_CRHR _hoops_GCRS _hoops_RCRS _hoops_CPAP
				if (!h3ddata->_hoops_CIGI->_hoops_HHAI)
					h3ddata->_hoops_CIGI->_hoops_HHAI = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);
				list = h3ddata->_hoops_CIGI->_hoops_HHAI;			
			}
			if (BIT(pm->_hoops_SRHA, DL_TEMPORARY_DATA))
				HD_Isolate_Polymarker_Data (dc, pm);

			Polymarker alter *_hoops_RARS = (Polymarker alter *) pm;
			_hoops_RARS->_hoops_CARI |= _hoops_SARI;

			pair = POOL_NEW(dc->memory_pool, _hoops_IRHA)(nr, pm, dc->_hoops_SPA->modelling_matrix, dc->_hoops_SPA->color);

			list->AddFirst(pair);
			return;
		}
		h3ddata->_hoops_CIGI->mask &= ~_hoops_RGPI;
	}
	
	_hoops_SRHA = pm->_hoops_SRHA;
	_hoops_CARI = pm->_hoops_CARI;

	/* _hoops_RAP _hoops_GH _hoops_RH _hoops_AI */
	int _hoops_RARR = 0;
	int _hoops_SIR = 0;
	_hoops_HCI _hoops_RPCP;
	_hoops_HRIA(h3ddata, nr, type, _hoops_SRHA, _hoops_CARI, &_hoops_RPCP);
	if (ANYBIT(_hoops_RRAC, _hoops_HRAC|_hoops_IISC|_hoops_PCSC|_hoops_ICSC))
		_hoops_RPCP.marker = 1;

	// _hoops_IARP _hoops_HAIR _hoops_CIHA _hoops_HH _hoops_RPP _hoops_HAHH.
	if (pm->_hoops_HCHA || BIT(pm->_hoops_SRHA, _hoops_GGIA)) {
		int _hoops_RARR;
		_hoops_SII(_hoops_IAAR, 0, &_hoops_RPCP, null, null, &_hoops_RARR);
		H3DTexture *_hoops_ACRS = _hoops_GHAH(h3ddata, nr);
		h3ddata->_hoops_GSCR->_hoops_GSAC(nr, null, _hoops_PCRS, _hoops_ACRS, _hoops_RARR);
	}

	/* _hoops_HCRS _hoops_RHIR _hoops_RH _hoops_ACSP _hoops_IIGR _hoops_RH _hoops_AI */
	if (matr->_hoops_ARIR)
	{
		H3DTexture *id = null;
		_hoops_RCR *txr = null;

		if (matr->_hoops_SCA) {
			_hoops_HIR *_hoops_GRIA = matr->_hoops_SCA;
			do {
				txr = _hoops_GRIA->texture;
				_hoops_SII(_hoops_PSRR, _hoops_SIR++, &_hoops_RPCP, null, null, &_hoops_RARR);
				if (!BIT (txr->_hoops_SCR, _hoops_GSR))
					id = _hoops_PIGH(h3ddata, nr, txr, 0);
				h3ddata->_hoops_GSCR->_hoops_GSAC(nr, txr, 0, id, _hoops_RARR);
			} while ((_hoops_GRIA = _hoops_GRIA->next) != null);
		}
	}

	// _hoops_RAP _hoops_GH _hoops_ICRS
	if (BIT(_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
		odl = (H3D_Display_List *) pm->_hoops_GAHA->list;
		_hoops_PPCP = odl->_hoops_PPCP;
	}
	else {
		int _hoops_GRRA = 0;

		_hoops_PPCP._hoops_AIHC();
		if (pm->_hoops_PCHA)
			_hoops_PPCP._hoops_RPHC();
		if (pm->_hoops_RGIA)
			_hoops_PPCP._hoops_RPHC();
		if (pm->_hoops_ICHA)
			_hoops_PPCP._hoops_CCRS();
		if (pm->_hoops_HCHA) {
			_hoops_SII(_hoops_IAAR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
			_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
			_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 1);
		}

		if (matr->_hoops_ARIR && pm->_hoops_CCHA && pm->_hoops_GSHA > 0) {
			_hoops_HIR *_hoops_PGC = matr->_hoops_SCA;
			for (int _hoops_ASRR = 0; _hoops_ASRR < _hoops_SIR; _hoops_ASRR++) {
				_hoops_SII(_hoops_PSRR, _hoops_ASRR, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				switch(_hoops_PGC->texture->_hoops_PSR) {
					case HK_PS_U:
						_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
						break;

					case HK_PS_UNSPECIFIED:
					case HK_PS_UV:
					case HK_PS_OBJECT:
					case HK_PS_WORLD:
					case HK_PS_SURFACE_NORMAL:
					case HK_PS_REFLECTION_VECTOR:
					case HK_PS_NATURAL_UV:
					case HK_PS_LOCAL_PIXELS:
					case HK_PS_OUTER_PIXELS:
					case HK_PS_LOCAL_WINDOW:
					case HK_PS_OUTER_WINDOW:
					case HK_PS_TRANSMISSION_VECTOR:
					case HK_PS_SPHERE:
					case HK_PS_CYLINDER:
					case _hoops_HSR:
						_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
						break;

					case HK_PS_UVW:
						_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
						break;
					default: HE_ERROR (HEC_DX9_DRIVER, HES_PROCEDURAL_ERROR,
						"Invalid vertex param width");
				}
				_hoops_PGC = _hoops_PGC->next;
			}

			if (matr->texture[_hoops_IIA]) {
				_hoops_SII(_hoops_APAR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
			}

			if (matr->texture[_hoops_HIA]) {
				_hoops_SII(_hoops_PPAR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
			}
			if (matr->texture[_hoops_ACA]) {
				_hoops_SII(_hoops_RPAR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
			}
			if (matr->texture[_hoops_PCA]) {
				_hoops_SII(_hoops_HPAR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
			}
			if (matr->texture[_hoops_HCA]) {
				_hoops_SII(_hoops_CPAR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
			}
		}

		if (_hoops_RRAC & _hoops_ICSC) {
			_hoops_SII(_hoops_HCRR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
			// _hoops_ICAH _hoops_IHH _hoops_HH _hoops_PCRR _hoops_RIR-_hoops_PPSR _hoops_IS _hoops_GSRS _hoops_RH _hoops_RPIA _hoops_AII.
			_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
			_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 2);
		}
	}

	_hoops_CRRS = (
		nr->_hoops_IRR->_hoops_GAHA &&
		!BIT (pm->_hoops_SRHA, DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS));

	// _hoops_RAP _hoops_CI _hoops_SGI _hoops_IIHA _hoops_GPP _hoops_RH _hoops_GCAC _hoops_CRAA _hoops_SR _hoops_RSRS.
	if (_hoops_RRAC & _hoops_ICSC)
		_hoops_SRRS |= H3DID_QUAD_MARKER;
	if (_hoops_RRAC & _hoops_PRAC)
		_hoops_SRRS |= H3DID_SPRITE_MARKER;
	if (_hoops_RRAC & _hoops_HRAC)
		_hoops_SRRS |= H3DID_CIRCLE_MARKER;
	if (_hoops_RRAC & _hoops_IISC)
		_hoops_SRRS |= H3DID_TEXTURE_MARKER;
	if (_hoops_RRAC & _hoops_RHSC)
		_hoops_SRRS |= H3DID_WORLD_SPACE_MARKER;
	if (_hoops_RRAC & _hoops_ASSC)
		_hoops_SRRS |= H3DID_SNAPPED_MARKER;

	_hoops_CISP &= nr->_hoops_CPP->_hoops_PRH._hoops_HRH;
	_hoops_SRRS = _hoops_IISP(h3ddata, nr, H3D_Unshared_Vertices, type, _hoops_CISP, 0, _hoops_SRRS);
	if (_hoops_RRHA || BIT(_hoops_SRHA, DL_DO_NOT_RECOMPILE))
		_hoops_CSIC (h3ddata, nr, type, null, _hoops_SRRS, odl->_hoops_RAHA, &_hoops_RSR);
	else
		_hoops_SSHH (h3ddata, nr, type, pm, _hoops_SRRS, &_hoops_RSR);
	_hoops_GGGH (h3ddata, nr, _hoops_RSR);
	_hoops_AHSA (h3ddata, nr, type, _hoops_RSR);
	_hoops_RHSA (h3ddata, H3DCULL_NONE);

	// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_GGR _hoops_GSSP _hoops_GC _hoops_PPR _hoops_GRP _hoops_GRPC, _hoops_SR _hoops_RRP _hoops_IS _hoops_CSRA _hoops_GH _hoops_RH _hoops_IGIR.
	if (_hoops_RRAC & _hoops_RHSC)
		size *= _hoops_IHCR->_hoops_SPH->_hoops_SRIR;

	// _hoops_SIIR _hoops_CI
	_hoops_RSR->_hoops_CCAA (nr, size, (_hoops_RRAC & _hoops_ASSC) != 0, (_hoops_RRAC & _hoops_ICSC) != 0, glyph);

	// _hoops_SIIR _hoops_IPSC
	if (_hoops_RRAC & _hoops_PRAC) {

		// _hoops_HAIC'_hoops_RA _hoops_ASRS _hoops_GRPC _hoops_PPR _hoops_PPSR _hoops_IPSC
		ASSERT((_hoops_RRAC & _hoops_ICSC) == 0);

		// _hoops_PS _hoops_GHCA _hoops_RRP _hoops_CARP _hoops_PCRR _hoops_IH _hoops_RH _hoops_GRPC _hoops_IIGR _hoops_RH _hoops_PPSR.
		bool _hoops_PSRS = 
				ANYBIT (_hoops_RRAC, _hoops_HRAC|_hoops_IISC) ||
				_hoops_RSR->ID()._hoops_SHC();
		float _hoops_ICGH = h3ddata->_hoops_IHSC;

		if (_hoops_RRAC & _hoops_RSSC)
			_hoops_ICGH = _hoops_AHIA(_hoops_ICGH, 64.0f);
		_hoops_PACC(h3ddata, _hoops_PSRS, 1.0f, _hoops_ICGH);
	}

	if (_hoops_CRRS) {
		_hoops_IRRS = _hoops_AACR(nr, &_hoops_PRRS->_hoops_GAHA, &dl, &odl, H3D_DL_GEOMETRY);
		if (_hoops_IRRS) {
			if (!_hoops_HCRI(h3ddata, 0)) {
				_hoops_CRRS = false;
				dl->_hoops_AGRI |= DL_INSUFFICIENT_VRAM;
			}
		}
		else if (BIT (dl->_hoops_AGRI,DL_INSUFFICIENT_VRAM))
			_hoops_CRRS = false;
	}

	// _hoops_AGGA _hoops_HSRS _hoops_ISRS _hoops_PAR _hoops_GRAA-_hoops_ISRS _hoops_CRAA.
	if (!_hoops_CRRS) {
		int start = 0;
		int end = (int)(((float)pm->length)*nr->_hoops_SCP->_hoops_CSRS);

		if (!BIT(dc->flags, _hoops_CHSI))
			_hoops_RCGS(nr, pm, _hoops_CCP, _hoops_RSR, _hoops_PPCP, _hoops_RRAC, _hoops_CAPA, start, end, &_hoops_RPCP);

		// _hoops_RAH *_hoops_HAR* _hoops_ASRC - _hoops_IAII _hoops_SR _hoops_HS _hoops_IS _hoops_SSRS _hoops_GGAS _hoops_RRGR, _hoops_PGAP _hoops_HRGR _hoops_CPIC _hoops_IS _hoops_HGCR _hoops_GGSR _hoops_IIGR _hoops_RGAS _hoops_HPGR _hoops_HHH _hoops_PPSR.
	}
	else {
		/* _hoops_AGAS _hoops_RH _hoops_AIRI _hoops_HIGR _hoops_RPP _hoops_GII _hoops_GCAC _hoops_SGI _hoops_PAR _hoops_RH _hoops_PGAS _hoops_HS _hoops_HGAS */
		if (!_hoops_IRRS &&
			(dl->_hoops_GSAI == DL_FLAG_INVALID ||
			pm->_hoops_GSAI != odl->item.geometry._hoops_GSAI ||
			!_hoops_SPRC(nr, _hoops_RRAC, dl, odl) ||
			_hoops_PPCP != odl->_hoops_PPCP))
		{
			HD_Queue_Destroy_List (odl, true);
			if (BIT(_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
				return;
			}
			_hoops_IRRS = _hoops_AACR(nr, &_hoops_PRRS->_hoops_GAHA, &dl, &odl, H3D_DL_GEOMETRY);
		}

		if (ANYBIT(_hoops_RRAC, _hoops_HCSC | _hoops_SISC))
			_hoops_GARS = 4;

		if (_hoops_IRRS) {
			// _hoops_IGAS _hoops_PSCA

			// _hoops_RGPA _hoops_RH _hoops_CCAH _hoops_CGAS _hoops_SRHR _hoops_IS _hoops_RH _hoops_AIRI _hoops_HIGR
			ASSERT(odl->item.geometry.id == 0);
			odl->item.geometry.id = POOL_NEW(dc->memory_pool, H3DIndexedBufferObject_List)(dc->memory_pool);
			odl->item.geometry._hoops_SGAS = H3D_OBJ_IndexBuffer;
			odl->item.geometry._hoops_GSAI = dl->_hoops_GSAI = pm->_hoops_GSAI;
			odl->item.geometry._hoops_SRHA = pm->_hoops_SRHA;
			odl->item.geometry._hoops_CARI = pm->_hoops_CARI;
			if (BIT (_hoops_RRAC, _hoops_PRAC))
				odl->item.geometry._hoops_CARI |= DL2_MARKER_POINT_SPRITE;
			if (BIT (_hoops_RRAC, _hoops_HRAC))
				odl->item.geometry._hoops_CARI |= DL2_MARKER_CIRCLE;
			odl->item.geometry._hoops_IRRI = pm->_hoops_SACI.flags;
			odl->item.geometry._hoops_HGAC = _hoops_CCP->glyph->key;
			odl->_hoops_PPCP = _hoops_PPCP;
			odl->_hoops_RAHA = _hoops_PHA(pm, false);
			odl->item.geometry._hoops_IGGI.total = 0;  //_hoops_GRAS _hoops_RH _hoops_RRAS _hoops_GAR _hoops_SR _hoops_PHHR _hoops_GGR _hoops_AGIR _hoops_SR _hoops_ARAS _hoops_GGSR _hoops_IIGR _hoops_AAGC
			odl->item.geometry._hoops_IGGI.point_count = pm->point_count;

			if (ANYBIT(_hoops_RRAC, _hoops_HCSC | _hoops_SISC) == 0) {
				i = 0;
				while (i < pm->length){
					int end;

					end = i + h3ddata->_hoops_PHAI;
					if (end > pm->length)
						end = pm->length;

					_hoops_HRRS = h3ddata->_hoops_GSCR->_hoops_PRAS();

					//_hoops_HRAS (&_hoops_ARAI, _hoops_SCII, _hoops_IRAS, _hoops_CRAS,_hoops_HSPP,_hoops_RSGR);
					_hoops_HRRS->CreateVertexBuffer(h3ddata, end - i, _hoops_PPCP);

					_hoops_HRRS->LockVertexBuffer(0,0,&_hoops_PAIH,0);
					while (i < end) {
						if (pm->_hoops_AIHA)
							_hoops_HCGS = pm->_hoops_AIHA[i];
						else
							_hoops_HCGS++;

						_hoops_ASCP(nr, pm, _hoops_CCP, &_hoops_PAIH, _hoops_HCGS, &_hoops_RPCP);
						_hoops_PAIH._hoops_CPPH();
						++i;
					}
					_hoops_HRRS->UnlockVertexBuffer();

					odl->item.geometry.id->AddLast(_hoops_HRRS);
					odl->item.geometry._hoops_IGGI.total += _hoops_HRRS->_hoops_SRAS();
					if (_hoops_RRHA == null &&
						!_hoops_HCRI(h3ddata, 0))
						break;
				}
			}
			else {
				_hoops_CCGS = 6;
				H3DPRIMITIVETYPE _hoops_SCGS = H3DPT_TRIANGLELIST;
				if (ANYBIT(_hoops_RRAC, _hoops_SISC)) {
					_hoops_CCGS = 4;
					_hoops_SCGS = H3DPT_LINELIST;
				}

				// _hoops_GISA _hoops_SRHR _hoops_IIGR _hoops_GAAS.
				// _hoops_HGI _hoops_GSGS _hoops_PIH _hoops_HRGR _hoops_RSGS. _hoops_IPCP _hoops_CGHI _hoops_PGCR _hoops_ASGS _hoops_CHR _hoops_HGSR _hoops_RIR _hoops_PPSR.
				int _hoops_HIPC;
				_hoops_SII(_hoops_HCRR, 0, &_hoops_RPCP, &_hoops_HIPC, null, null);

				int _hoops_RAAS = pm->point_count;		// _hoops_SAIA _hoops_RIR _hoops_SSAI
				bool _hoops_AAAS = false;
				bool _hoops_PCGS = false;

				ASSERT (!_hoops_HRRS);

				if ((unsigned int) pm->point_count * 4 > h3ddata->_hoops_ACGH._hoops_CGGI ||
					(unsigned int) pm->point_count * 2 > h3ddata->_hoops_ACGH._hoops_GRGI)
				{
					_hoops_AAAS = true;
					_hoops_RAAS = _hoops_AHIA(h3ddata->_hoops_ACGH._hoops_GRGI / 2, h3ddata->_hoops_ACGH._hoops_CGGI / 4);
				}

				j = 0;
				for (i = 0; i < pm->length; i++) {
					if (_hoops_PCGS && _hoops_AAAS &&
						(j >= _hoops_RAAS * _hoops_CCGS || _hoops_PAIH.length() >= _hoops_RAAS * 4))
					{
						_hoops_HRRS->UnlockIndexBuffer();
						_hoops_HRRS->UnlockVertexBuffer();
						odl->item.geometry.id->AddLast(_hoops_HRRS);
						odl->item.geometry._hoops_IGGI.total += _hoops_HRRS->_hoops_SRAS();
						_hoops_PCGS = false;
						j = 0;
						if (_hoops_RRHA == null &&
							!_hoops_HCRI(h3ddata, 0))
							break;
					}
					if (!_hoops_PCGS) {
						_hoops_HRRS = h3ddata->_hoops_GSCR->_hoops_PRAS();

						// _hoops_PAAS _hoops_SGP _hoops_AHSC _hoops_SAIA, _hoops_RIR _hoops_GPHA _hoops_SR _hoops_RRP 4 _hoops_RSSA _hoops_PPR 6 _hoops_PSPI (2 _hoops_HIPH)
						_hoops_HRRS->CreateVertexBuffer(h3ddata, _hoops_RAAS * 4, _hoops_PPCP);
						_hoops_HRRS->CreateIndexBuffer(h3ddata, _hoops_SCGS, _hoops_RAAS * _hoops_CCGS, _hoops_RAAS * 2);

						_hoops_HRRS->LockVertexBuffer(0,0,&_hoops_PAIH,0);
						_hoops_HRRS->LockIndexBuffer(0,0,&_hoops_RAHC,0);
						_hoops_PCGS = true;
					}

					if (pm->_hoops_AIHA)
						_hoops_HCGS = pm->_hoops_AIHA[i];
					else
						_hoops_HCGS++;

					_hoops_ASCP(nr, pm, _hoops_CCP, &_hoops_PAIH, _hoops_HCGS, &_hoops_RPCP);
					
					// _hoops_PSGS _hoops_SRS _hoops_ARIP _hoops_IIGR _hoops_GPHA _hoops_AIAA _hoops_IACH.
					_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
					_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(2);
					_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(3);

					if (BIT(_hoops_RRAC, _hoops_HCSC)) {
						// _hoops_RAP _hoops_HSGS _hoops_SHI _hoops_GGR _hoops_GRR _hoops_IPS.
						_hoops_PAIH._hoops_RRCI(0)._hoops_ARHC(-1.0f, -1.0f, _hoops_HIPC);
						_hoops_PAIH._hoops_RRCI(1)._hoops_ARHC(+1.0f, -1.0f, _hoops_HIPC);
						_hoops_PAIH._hoops_RRCI(2)._hoops_ARHC(-1.0f, +1.0f, _hoops_HIPC);
						_hoops_PAIH._hoops_RRCI(3)._hoops_ARHC(+1.0f, +1.0f, _hoops_HIPC);

						_hoops_PAIH._hoops_CPPH(4);

						_hoops_RAHC[0] = j * 4 + 0;
						_hoops_RAHC[1] = j * 4 + 1;
						_hoops_RAHC[2] = j * 4 + 2;
						_hoops_RAHC[3] = j * 4 + 1;
						_hoops_RAHC[4] = j * 4 + 3;
						_hoops_RAHC[5] = j * 4 + 2;
						_hoops_RAHC += 6;
					}
					else if (BIT(_hoops_RRAC, _hoops_SISC)) {
						if (BIT(_hoops_RRAC, _hoops_CCSC)) {
							// _hoops_RAP _hoops_HSGS _hoops_SHI _hoops_GGR _hoops_GRR _hoops_IPS.
							_hoops_PAIH._hoops_RRCI(0)._hoops_ARHC(-0.99f, -0.99f, _hoops_HIPC);
							_hoops_PAIH._hoops_RRCI(1)._hoops_ARHC(+0.99f, +0.99f, _hoops_HIPC);
							_hoops_PAIH._hoops_RRCI(2)._hoops_ARHC(-0.99f, +0.99f, _hoops_HIPC);
							_hoops_PAIH._hoops_RRCI(3)._hoops_ARHC(+0.99f, -0.99f, _hoops_HIPC);
							_hoops_PAIH._hoops_CPPH(4);
						}
						else if (BIT(_hoops_RRAC, _hoops_SCSC)) {
							// _hoops_RAP _hoops_HSGS _hoops_SHI _hoops_GGR _hoops_GRR _hoops_IPS.
							_hoops_PAIH._hoops_RRCI(0)._hoops_ARHC(0.0f, -1.0f, _hoops_HIPC);
							_hoops_PAIH._hoops_RRCI(1)._hoops_ARHC(0.0f, +1.0f, _hoops_HIPC);
							_hoops_PAIH._hoops_RRCI(2)._hoops_ARHC(-1.0f, 0.0f, _hoops_HIPC);
							_hoops_PAIH._hoops_RRCI(3)._hoops_ARHC(+1.0f, 0.0f, _hoops_HIPC);
							_hoops_PAIH._hoops_CPPH(4);
						}

						_hoops_RAHC[0] = j * 4 + 0;
						_hoops_RAHC[1] = j * 4 + 1;
						_hoops_RAHC[2] = j * 4 + 2;
						_hoops_RAHC[3] = j * 4 + 3;
						_hoops_RAHC += 4;
					}
					j++;
				}

				if (_hoops_PCGS) {
					_hoops_HRRS->UnlockIndexBuffer();
					_hoops_HRRS->UnlockVertexBuffer();
					odl->item.geometry.id->AddLast(_hoops_HRRS);
					odl->item.geometry._hoops_IGGI.total += _hoops_HRRS->_hoops_SRAS();
					_hoops_PCGS = false;
				}
			}
		}
		else
		{
			odl->item.geometry.id->ResetCursor();
			_hoops_HRRS = odl->item.geometry.id->PeekCursor();
		}

		// _hoops_GISP _hoops_CCA _hoops_HPPA _hoops_GHC, _hoops_RPP _hoops_GII...
		if (!BIT(dc->flags, _hoops_CHSI)) {
			do {
				if (_hoops_CAPA) {
					_hoops_RSR->_hoops_CHPA(nr, _hoops_CAPA);
					_hoops_CAPA = _hoops_CAPA->next;
				}

				odl->item.geometry.id->ResetCursor();
				int _hoops_HAAS = (int)(nr->_hoops_SCP->_hoops_CSRS*(float)pm->length);
				int _hoops_IAAS = _hoops_HAAS / h3ddata->_hoops_PHAI;
				int _hoops_CAAS = 0;

				while(odl->item.geometry.id->PeekCursor() != 0 && _hoops_IAAS-- >= 0) {
					H3DIndexedBufferObject *_hoops_SAAS = odl->item.geometry.id->PeekCursor();
					if(_hoops_IAAS < 0) {
						_hoops_SAAS->_hoops_GPAS(h3ddata, nr->_hoops_SCP->_hoops_CSRS);
						_hoops_CAAS = _hoops_HAAS;
					}
					else {
						_hoops_SAAS->_hoops_GPAS(h3ddata, 1.0f);
						_hoops_CAAS += _hoops_SAAS->_hoops_SRAS() / _hoops_GARS;
					}

					odl->item.geometry.id->AdvanceCursor();
				}
				_hoops_GPRH (_hoops_RPAS) += _hoops_CAAS;

				if (_hoops_RRHA == null &&
					_hoops_CAAS < _hoops_HAAS) {
					ASSERT (!BIT (pm->_hoops_SRHA, DL_DO_NOT_RECOMPILE));
					_hoops_RCGS(nr, pm, _hoops_CCP, _hoops_RSR, _hoops_PPCP, _hoops_RRAC, _hoops_CAPA, _hoops_CAAS, _hoops_HAAS, &_hoops_RPCP);
				}
			} while (_hoops_CAPA);
		}
	}

	// _hoops_IGSA _hoops_ASCA _hoops_ISRS _hoops_PPR _hoops_GRAA-_hoops_ISRS _hoops_GPAC. _hoops_SP _hoops_GH.
	if (_hoops_RRAC & _hoops_PRAC)
		_hoops_PACC(h3ddata, false, 1, 1);
}


void draw_3d_polymarker (
	Net_Rendition const &	nr,
	Polymarker const *		pm) {
	_hoops_GPCI (nr, pm, nr->_hoops_SCP, null);
}


/*****************************************************************************
						_hoops_APAS
*****************************************************************************/

void _hoops_PPAS (
		Net_Rendition const &  nr,
		Polyedge const *pe)
{
	H3DData alter *h3ddata = H3DD (nr->_hoops_SRA);
	Polyedge alter *_hoops_HPAS = (Polyedge alter *) pe;
	Line_Rendition const &_hoops_GHP = nr->_hoops_RHP;
	int weight = _hoops_GHP->weight;

	H3D_TRACE(h3ddata, "draw_indexed_polyedge");

	if (weight < 0)
		weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
	if (_hoops_GAPI (_hoops_GHP->line_style) ||
		BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)) {
		if (h3ddata->_hoops_CIGI)
			h3ddata->_hoops_CIGI->mask &= ~_hoops_GHCI;
		HD_Draw_Indexicated_3D_Polyedge (nr, pe);
		return;
	}

	_hoops_HPAS->_hoops_SRHA |= (_hoops_GGIA | DL_INDEX_INTERPOLATION);

	really_draw_3d_polyedge (nr, _hoops_HPAS, nr->_hoops_RHP, null);


}


/*****************************************************************************
						_hoops_IPAS
*****************************************************************************/
/*
 * _hoops_PGAA
 * _hoops_PGSA _hoops_IRS _hoops_ACRI _hoops_GGR _hoops_HGAI _hoops_CCH _hoops_GRP _hoops_RH _hoops_GPHA _hoops_SRHR _hoops_RIAH.
 */
void _hoops_CPAS (
		Net_Rendition const &		nr,
		Polyedge const *			pe,
		H3D_Display_List_Bin *		_hoops_RRHA,
		Line_Rendition const &		_hoops_GHP,
		H3D_Vertex_Buffer_Style		_hoops_APHA,
		H3DVertexFormat				_hoops_PPCP)
{
	Display_Context const *		dc = nr->_hoops_SRA;
	H3DData alter *				h3ddata = H3DD (dc);
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	H3DVertexBufferCache *		_hoops_HACP = null;
	H3DVertexBuffer				&_hoops_PAIH = h3ddata->_hoops_CP;
	H3DIndexBuffer				_hoops_CHPC, _hoops_AAHC;
	int 						type = 0;
	int							_hoops_SPAS = 0;
	int 						i, j, k;
	int 						_hoops_HSPI, _hoops_ISPI, _hoops_CSPI, _hoops_SSPI, ei;
	int 						_hoops_GHAS = 0, _hoops_RHAS, _hoops_AHAS;
	short 						*_hoops_PHAS = null;
	int 						point_count = 0;
	int 						len, start, end, _hoops_IGIC;
	int 						_hoops_RRC = 1;
	float 						_hoops_IACP;
	Point 						_hoops_HHAS, _hoops_IHAS;
	short *						_hoops_CHAS = null, *_hoops_PAHC = null;
	H3DShader *					_hoops_RSR;
	int 						flags = 0;
	int 						_hoops_HGIC = 0;
	bool						_hoops_PCGS;
	_hoops_IAPA const *	_hoops_CAPA = null;
	bool						_hoops_IAHC = false;
	_hoops_HRPA const *			_hoops_SHAS = null;
	RGB const *					_hoops_GPCP = null;
	bool						_hoops_GIAS;
	bool						_hoops_SIPC = (_hoops_GHP == nr->_hoops_RHP);
	int							weight = _hoops_GHP->weight;
	_hoops_IRHA *				pair = null;
	int							_hoops_PIPC, _hoops_AIPC, _hoops_HIPC;


	_hoops_ISGI const *_hoops_CSGI = dc->_hoops_SPA->modelling_matrix;
	_hoops_SSGI const *_hoops_GGRI = dc->_hoops_SPA->color;

	if (ANYBIT(_hoops_GHP->line_style->flags, LSF_COMPLEX_ANYBITS)) {
		_hoops_IAHC = true;
	}

	if (!_hoops_HPCA(nr, _hoops_CAPA)) {
		_hoops_IAHC = true;
	}

	if (_hoops_IAHC) {
		HD_Std_3D_Polyedge (nr, pe);
		return;
	}

	if (!BIT(_hoops_GHP->line_style->flags, LSF_SOLID)) {
		flags |= H3DID_LINE_PATTERN;
	}

	if (_hoops_RRHA) {
		_hoops_RRHA->_hoops_CRHA->ResetCursor();
		pair = _hoops_RRHA->_hoops_CRHA->PeekFirst();
		pe = (Polyedge const *) pair->geo;
	}

	if (_hoops_GHP == nr->_hoops_RHP) {
		if (BIT (pe->_hoops_CARI, _hoops_RCRI))
			type = _hoops_GPA;
		else
			type = T_EDGES;
		_hoops_SPAS = Color_EDGE;
	}
	else {
		type = T_LINES;
		_hoops_SPAS = Color_LINE;
	}

	if (_hoops_RRHA) {
		_hoops_GPCP = _hoops_CCAI (pair->color, _hoops_SPAS);
		if (pair->_hoops_CPAI)
			_hoops_SHAS = &pair->_hoops_CPAI->matrix;
		else
			_hoops_SHAS = null;
		if (_hoops_GPCP)
			dc->_hoops_SPA->color = pair->color;
	}
	else {
		_hoops_GPCP = _hoops_CCAI (dc->_hoops_SPA->color, _hoops_SPAS);
	}

	if (_hoops_GPCP)
		_hoops_PPCP._hoops_RPHC();

	/* _hoops_PSIH _hoops_PPSR _hoops_RPR */
	for(;;) {
		if (pe->point_count > 0)
			point_count += pe->point_count;
		else {
			if (pe->_hoops_SPII) {
				int _hoops_RIAS = 0;
				for (i = 0; i < pe->total; i++)
					if (_hoops_RIAS < pe->_hoops_SPII[i])
						_hoops_RIAS = pe->_hoops_SPII[i];
				_hoops_RIAS++;	//_hoops_PIHA _hoops_HIHA _hoops_IH 0 _hoops_IIHA _hoops_CIHA
				point_count += _hoops_RIAS;
			}
			else
				point_count += pe->total;
		}

		if (_hoops_RRHA) {
			_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			if (!pair)
				break;
			pe = (Polyedge const *) pair->geo;
		}
		else
			break;
	}
	if (_hoops_RRHA) {
		_hoops_RRHA->_hoops_CRHA->ResetCursor();
		pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
		pe = (Polyedge const *) pair->geo;
	}

	_hoops_RPIH(h3ddata, _hoops_PPCP, _hoops_HACP);

	_hoops_PHAS = _hoops_AIAS(h3ddata, point_count);

	_hoops_RCHC(h3ddata, _hoops_HACP);

	bool const _hoops_PPHC = BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP) ||
		(weight > 1 && (_hoops_SIPC || ANYBIT(_hoops_GHP->style, LJOIN_ROUND|LCAP_ROUND|LCAP_END_ROUND)));

	bool const _hoops_PRH = _hoops_PPHC || nr->_hoops_CPP->_hoops_PRH._hoops_HRH;
	flags = _hoops_IISP (h3ddata, nr, _hoops_APHA, type, _hoops_PRH, 0, flags);

	flags |= _hoops_CCSP(nr);
	_hoops_CPHC (h3ddata, nr, type, pe, pe->total, flags, &_hoops_RSR);
	_hoops_GGGH (h3ddata, nr, _hoops_RSR);
	_hoops_AHSA (h3ddata, nr, type, _hoops_RSR);

	_hoops_HCI _hoops_RPCP;
	_hoops_HRIA(h3ddata, nr, type, pe->_hoops_SRHA, pe->_hoops_CARI, &_hoops_RPCP);

	if (!BIT(_hoops_GHP->line_style->flags, LSF_SOLID))
		_hoops_RPCP._hoops_GGC++;

	if (weight < 0)
		weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP,1.0f, false, 0, true)+0.5f);

	int _hoops_SAHC;
	_hoops_SII(_hoops_SHRR, 0, &_hoops_RPCP, &_hoops_PIPC, null, null);
	_hoops_SII(_hoops_CHRR, 0, &_hoops_RPCP, &_hoops_AIPC, null, null);
	_hoops_SII(_hoops_IHRR, 0, &_hoops_RPCP, &_hoops_HIPC, null, &_hoops_SAHC);
	if (_hoops_PPHC) {
		if (!h3ddata->_hoops_HSI.valid)
			_hoops_HRPC (h3ddata);
		h3ddata->_hoops_GSCR->_hoops_GSAC (nr, null, _hoops_SPHC, h3ddata->_hoops_HSI.texture, _hoops_SAHC);
	}

	_hoops_RSR->_hoops_SIAA (nr, _hoops_GHP);

	if (weight > 1 ||
		h3ddata->_hoops_IHP ||
		BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP))
	{
		bool _hoops_PIAS = false;

		for (;;) {
			bool _hoops_GIPC = false;
			bool _hoops_RHHC = false;

			int _hoops_PHHC = 4;
			int _hoops_HHHC = 0;
			int _hoops_IHHC = 6;
			int _hoops_CHHC = 0;

			int _hoops_HIAS = _hoops_IHHC;
			int _hoops_RRSA;
			int _hoops_RGSA;

			int _hoops_IIAS = _hoops_HACP->_hoops_GRIC;

			if (_hoops_SHAS) {
				_hoops_AGGH(h3ddata, _hoops_SHAS, _hoops_RSR);
				_hoops_PIAS = true;
				_hoops_SHAS = null;
			}

			if (!_hoops_SIPC) {
				_hoops_RHSA(h3ddata, H3DCULL_NONE);
				if ((_hoops_GHP->style & LJOIN_MASK) == LJOIN_MITER &&
					weight > 1)
					_hoops_RHHC = true;
			}

			if (pe->points[0] == pe->points[pe->point_count - 1])
				_hoops_GIPC = true;

			if (_hoops_SIPC || ANYBIT(_hoops_GHP->style, LCAP_MASK)) {
				// _hoops_SR _hoops_HHS _hoops_ARII _hoops_HS _hoops_GH _hoops_IS _hoops_RGR _hoops_GSGS, _hoops_RPP _hoops_SR _hoops_HS _hoops_IPHC _hoops_III _hoops_SGHC
				_hoops_PHHC += 8;
				_hoops_IHHC += 12;
				_hoops_HIAS += 12;
			}
			if (_hoops_SIPC || ANYBIT(_hoops_GHP->style, LJOIN_ROUND | LJOIN_BEVEL)) {
				_hoops_PHHC += 4;
				_hoops_IHHC += 6;
				_hoops_HIAS += 6;
			}
			if (!_hoops_SIPC && (_hoops_GHP->style & LJOIN_MASK) == LJOIN_MITER) {
				_hoops_PHHC += 1;
				_hoops_IHHC += 6;
				_hoops_HHHC += 2 * pe->_hoops_PHHA;
				_hoops_HIAS += 6;
			}

			// _hoops_SSAI _hoops_HRGR _hoops_RH _hoops_CIAS _hoops_PHI _hoops_IIGR _hoops_PSPI _hoops_SR _hoops_SIAS _hoops_GCAS _hoops_CIPH _hoops_GGR _hoops_SPR _hoops_RCAS:
			// 6 _hoops_IH _hoops_RH _hoops_AAIA _hoops_III _hoops_ACAS
			// 6 _hoops_IH _hoops_IRS _hoops_CAGH _hoops_PCPC	(_hoops_HRGI _hoops_AGIR)
			// 12 _hoops_IH _hoops_PGCR _hoops_PCAS (_hoops_HRGI _hoops_AGIR)
			_hoops_IGIC = (int)_hoops_HACP->_hoops_GRIC/_hoops_HIAS;
			_hoops_IGIC = _hoops_AHIA (_hoops_IGIC, pe->total);

			i = j = k = 0;
			_hoops_PCGS = false;
			_hoops_GIAS = (pe->_hoops_ASHA || pe->_hoops_RSHA || !_hoops_PHAS);


			ei = -1;
			while (i < pe->_hoops_PHHA)
			{
				if (pe->lengths)
					len = pe->lengths[i];
				else
					len = pe->total;

				if (len < 0) {
					_hoops_ICHC (len, _hoops_RRC, 2);

					start = j;
					end = j+len;

					_hoops_IACP = 0;

					_hoops_ISPI = j;

					while (j < end) {
						_hoops_CSPI = _hoops_ISPI+1;

						if (pe->_hoops_AIHA) {
							/* _hoops_HHHA _hoops_PSPI */
							_hoops_ISPI = pe->_hoops_AIHA[_hoops_ISPI];
							_hoops_CSPI = pe->_hoops_AIHA[_hoops_CSPI];
						}

						if (pe->_hoops_SPII)
							ei = pe->_hoops_SPII[j+1];
						else
							ei++;
						if (!_hoops_PCGS) {
							_hoops_HACP->Lock(_hoops_AHIA(_hoops_IGIC*_hoops_PHHC + _hoops_HHHC, _hoops_IIAS), &_hoops_PAIH);
							h3ddata->_hoops_ACHC->Lock(_hoops_IGIC*_hoops_IHHC + _hoops_CHHC, &_hoops_PAHC);
							_hoops_CHPC._hoops_IRA(H3DFMT_INDEX16, _hoops_PAHC);
							_hoops_AAHC = _hoops_CHPC;
							_hoops_PCGS = true;
							_hoops_HGIC = 0;
							_hoops_GHAS = 0;
						}

						_hoops_IHPC(nr, _hoops_GHP, pe, pe->points, &_hoops_PAIH, &_hoops_CHPC, &_hoops_RPCP, _hoops_SHAS, _hoops_GPCP,
							&_hoops_GHAS, _hoops_ISPI, _hoops_ISPI, _hoops_ISPI+2, ei, false, 0);

						_hoops_PACP (nr, pe, _hoops_GHP, &_hoops_PAIH, _hoops_IACP, _hoops_ISPI, ei, _hoops_SHAS, _hoops_GPCP, &_hoops_RPCP);
						//_hoops_RGPA _hoops_HSPP _hoops_IIGR _hoops_SPS _hoops_III
						_hoops_PAIH._hoops_IICP(pe->points[_hoops_CSPI].x,
							pe->points[_hoops_CSPI].y,
							pe->points[_hoops_CSPI].z,
							_hoops_AIPC);
						_hoops_PAIH.t(H3D_SQUARE, _hoops_HIPC);

						if (_hoops_RHHC) {
							_hoops_PAIH._hoops_IICP(pe->points[_hoops_CSPI].x,
								pe->points[_hoops_CSPI].y,
								pe->points[_hoops_CSPI].z,
								_hoops_PIPC);
						}


						_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
						_hoops_PAIH._hoops_RRCI(0)._hoops_IICP(-1,0,0, _hoops_HIPC);
						_hoops_PAIH._hoops_RRCI(1)._hoops_IICP(+1,0,0, _hoops_HIPC);
						_hoops_PAIH._hoops_CPPH(2);


						if (BIT(flags, H3DID_LINE_PATTERN)) {
							_hoops_HHAS.x = _hoops_HPRA(_hoops_IHCR->matrix->data.elements, pe->points[_hoops_ISPI]);
							_hoops_HHAS.y = _hoops_IPRA(_hoops_IHCR->matrix->data.elements, pe->points[_hoops_ISPI]);
							_hoops_IHAS.x = _hoops_HPRA(_hoops_IHCR->matrix->data.elements, pe->points[_hoops_CSPI]);
							_hoops_IHAS.y = _hoops_IPRA(_hoops_IHCR->matrix->data.elements, pe->points[_hoops_CSPI]);
							_hoops_IACP += sqrt((_hoops_IHAS.x-_hoops_HHAS.x) * (_hoops_IHAS.x-_hoops_HHAS.x) + (_hoops_IHAS.y-_hoops_HHAS.y) * (_hoops_IHAS.y-_hoops_HHAS.y));
						}

						_hoops_PACP (nr, pe, _hoops_GHP, &_hoops_PAIH, _hoops_IACP, _hoops_CSPI, ei, _hoops_SHAS, _hoops_GPCP, &_hoops_RPCP);
						//_hoops_RGPA _hoops_GCPC _hoops_PPSR
						_hoops_PAIH._hoops_IICP(2*pe->points[_hoops_CSPI].x - pe->points[_hoops_ISPI].x,
							2*pe->points[_hoops_CSPI].y - pe->points[_hoops_ISPI].y,
							2*pe->points[_hoops_CSPI].z - pe->points[_hoops_ISPI].z,
							_hoops_AIPC);
						_hoops_PAIH.t(H3D_SQUARE, _hoops_HIPC);

						if (_hoops_RHHC) {
							_hoops_PAIH._hoops_IICP(2*pe->points[_hoops_CSPI].x - pe->points[_hoops_ISPI].x,
								2*pe->points[_hoops_CSPI].y - pe->points[_hoops_ISPI].y,
								2*pe->points[_hoops_CSPI].z - pe->points[_hoops_ISPI].z,
								_hoops_PIPC);
						}


						_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
						_hoops_PAIH._hoops_RRCI(0)._hoops_IICP(-1,0,0, _hoops_HIPC);
						_hoops_PAIH._hoops_RRCI(1)._hoops_IICP(+1,0,0, _hoops_HIPC);
						_hoops_PAIH._hoops_CPPH(2);

						_hoops_CHPC = _hoops_GHAS;			++_hoops_CHPC;
						_hoops_CHPC = _hoops_GHAS + 1;		++_hoops_CHPC;
						_hoops_CHPC = _hoops_GHAS + 2;		++_hoops_CHPC;
						_hoops_CHPC = _hoops_GHAS + 1;		++_hoops_CHPC;
						_hoops_CHPC = _hoops_GHAS + 3;		++_hoops_CHPC;
						_hoops_CHPC = _hoops_GHAS + 2;		++_hoops_CHPC;
						_hoops_GHAS += 4;

						_hoops_IHPC(nr, _hoops_GHP, pe, pe->points, &_hoops_PAIH, &_hoops_CHPC, &_hoops_RPCP, _hoops_SHAS, _hoops_GPCP,
							&_hoops_GHAS, _hoops_CSPI, _hoops_ISPI, _hoops_ISPI+2, ei, false, 0);

						j++;
						k++;

						_hoops_ISPI += _hoops_RRC;

						if (k >= _hoops_IGIC) {
							_hoops_HACP->Unlock();
							h3ddata->_hoops_ACHC->Unlock();
							_hoops_PCGS = false;

							_hoops_RRSA = _hoops_PAIH.length();
							_hoops_RGSA = (_hoops_CHPC - _hoops_AAHC) / 3;

							if (j < end - 1 && _hoops_RHHC) {
								/* _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_HCAS _hoops_RH _hoops_ISII _hoops_GH _hoops_PPR _hoops_SR _hoops_HS _hoops_IIHC _hoops_AIRR,
								* _hoops_APRI _hoops_RH _hoops_CGHI _hoops_SCPH, _hoops_GAR _hoops_SCH'_hoops_GRI _hoops_ICAS _hoops_CCAS _hoops_GIHA
								*/
								_hoops_RGSA -= 1;
							}

							_hoops_SGSA(h3ddata, nr, h3ddata->_hoops_ACHC, _hoops_CAPA,
								_hoops_RRSA, _hoops_RGSA, _hoops_SCAS, H3DPT_TRIANGLELIST);
							k = 0;
						}
					}
					i++;
					j = _hoops_ISPI;
				}
				else {
					start = j;
					end = j+len;

					_hoops_IACP = 0;

					while (j < end-1) {

						_hoops_HSPI = (j == start) ? end-2 : j-1;
						_hoops_ISPI = j;
						_hoops_CSPI = j+1;
						_hoops_SSPI = (j == end-2) ? start+1 : j+2;

						if (pe->_hoops_AIHA) {
							/* _hoops_HHHA _hoops_PSPI */
							_hoops_HSPI = pe->_hoops_AIHA[_hoops_HSPI];
							_hoops_ISPI = pe->_hoops_AIHA[_hoops_ISPI];
							_hoops_CSPI = pe->_hoops_AIHA[_hoops_CSPI];
							_hoops_SSPI = pe->_hoops_AIHA[_hoops_SSPI];
						}

						if (pe->_hoops_SPII)
							ei = pe->_hoops_SPII[j+1];
						else
							ei++;
						if (!_hoops_PCGS) {
							_hoops_HACP->Lock(_hoops_AHIA(_hoops_IGIC*_hoops_PHHC + _hoops_HHHC, _hoops_IIAS), &_hoops_PAIH);
							h3ddata->_hoops_ACHC->Lock(_hoops_IGIC*_hoops_IHHC + _hoops_CHHC, &_hoops_PAHC);
							_hoops_CHPC._hoops_IRA(H3DFMT_INDEX16, _hoops_PAHC);
							_hoops_AAHC = _hoops_CHPC;
							_hoops_PCGS = true;
							_hoops_HGIC = 0;
							_hoops_GHAS = 0;
						}

						if (j == start) {
							_hoops_IHPC(nr, _hoops_GHP, pe, pe->points, &_hoops_PAIH, &_hoops_CHPC, &_hoops_RPCP, _hoops_SHAS, _hoops_GPCP,
								&_hoops_GHAS, j, start, end, ei, _hoops_GIPC, 0);
						}
						else if (j < end - 1 && _hoops_GHAS == 0) {
							/* _hoops_RPP _hoops_SR _hoops_GSAS _hoops_RH _hoops_ISII _hoops_GH _hoops_PPR _hoops_SR _hoops_HS _hoops_IIHC _hoops_AIRR,
							* _hoops_SR _hoops_RRP _hoops_IS _hoops_ASAR-_hoops_GGCR _hoops_RH _hoops_PCPC _hoops_GAR _hoops_SCH _hoops_RSAS'_hoops_RA _hoops_ASAS _hoops_CGHI _hoops_GHIR
							*/
							_hoops_IHPC(nr, _hoops_GHP, pe, pe->points, &_hoops_PAIH, &_hoops_CHPC, &_hoops_RPCP, _hoops_SHAS, _hoops_GPCP,
								&_hoops_GHAS, j, start, end, ei, _hoops_GIPC, H3DCAP_NO_MITER_PREV);
						}

						_hoops_PACP (nr, pe, _hoops_GHP, &_hoops_PAIH, _hoops_IACP, _hoops_ISPI, ei, _hoops_SHAS, _hoops_GPCP, &_hoops_RPCP);
						//_hoops_RGPA _hoops_HSPP _hoops_IIGR _hoops_SPS _hoops_III
						_hoops_PAIH._hoops_IICP(pe->points[_hoops_CSPI].x,
							pe->points[_hoops_CSPI].y,
							pe->points[_hoops_CSPI].z,
							_hoops_AIPC);
						_hoops_PAIH.t(H3D_SQUARE, _hoops_HIPC);

						if (_hoops_RHHC) {
							_hoops_PAIH._hoops_IICP(pe->points[_hoops_CSPI].x,
								pe->points[_hoops_CSPI].y,
								pe->points[_hoops_CSPI].z,
								_hoops_PIPC);
						}


						_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
						_hoops_PAIH._hoops_RRCI(0)._hoops_IICP(-1,0,0, _hoops_HIPC);
						_hoops_PAIH._hoops_RRCI(1)._hoops_IICP(+1,0,0, _hoops_HIPC);
						_hoops_PAIH._hoops_CPPH(2);


						if (BIT(flags, H3DID_LINE_PATTERN)) {
							_hoops_HHAS.x = _hoops_HPRA(_hoops_IHCR->matrix->data.elements, pe->points[_hoops_ISPI]);
							_hoops_HHAS.y = _hoops_IPRA(_hoops_IHCR->matrix->data.elements, pe->points[_hoops_ISPI]);
							_hoops_IHAS.x = _hoops_HPRA(_hoops_IHCR->matrix->data.elements, pe->points[_hoops_CSPI]);
							_hoops_IHAS.y = _hoops_IPRA(_hoops_IHCR->matrix->data.elements, pe->points[_hoops_CSPI]);
							_hoops_IACP += sqrt((_hoops_IHAS.x-_hoops_HHAS.x) * (_hoops_IHAS.x-_hoops_HHAS.x) + (_hoops_IHAS.y-_hoops_HHAS.y) * (_hoops_IHAS.y-_hoops_HHAS.y));
						}

						_hoops_PACP (nr, pe, _hoops_GHP, &_hoops_PAIH, _hoops_IACP, _hoops_CSPI, ei, _hoops_SHAS, _hoops_GPCP, &_hoops_RPCP);

						//_hoops_RGPA _hoops_GCPC _hoops_PPSR
						_hoops_PAIH._hoops_IICP(2*pe->points[_hoops_CSPI].x - pe->points[_hoops_ISPI].x,
							2*pe->points[_hoops_CSPI].y - pe->points[_hoops_ISPI].y,
							2*pe->points[_hoops_CSPI].z - pe->points[_hoops_ISPI].z,
							_hoops_AIPC);
						_hoops_PAIH.t(H3D_SQUARE, _hoops_HIPC);

						if (_hoops_RHHC) {
							_hoops_PAIH._hoops_IICP(2*pe->points[_hoops_CSPI].x - pe->points[_hoops_ISPI].x,
								2*pe->points[_hoops_CSPI].y - pe->points[_hoops_ISPI].y,
								2*pe->points[_hoops_CSPI].z - pe->points[_hoops_ISPI].z,
								_hoops_PIPC);
						}


						_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
						_hoops_PAIH._hoops_RRCI(0)._hoops_IICP(-1,0,0, _hoops_HIPC);
						_hoops_PAIH._hoops_RRCI(1)._hoops_IICP(+1,0,0, _hoops_HIPC);
						_hoops_PAIH._hoops_CPPH(2);

						_hoops_CHPC = _hoops_GHAS;			++_hoops_CHPC;
						_hoops_CHPC = _hoops_GHAS + 1;		++_hoops_CHPC;
						_hoops_CHPC = _hoops_GHAS + 2;		++_hoops_CHPC;
						_hoops_CHPC = _hoops_GHAS + 1;		++_hoops_CHPC;
						_hoops_CHPC = _hoops_GHAS + 3;		++_hoops_CHPC;
						_hoops_CHPC = _hoops_GHAS + 2;		++_hoops_CHPC;
						_hoops_GHAS += 4;

						_hoops_IHPC(nr, _hoops_GHP, pe, pe->points, &_hoops_PAIH, &_hoops_CHPC, &_hoops_RPCP, _hoops_SHAS, _hoops_GPCP,
							&_hoops_GHAS, j+1, start, end, ei, _hoops_GIPC, 0);

						j++;
						k++;

						if (k >= _hoops_IGIC) {
							_hoops_HACP->Unlock();
							h3ddata->_hoops_ACHC->Unlock();
							_hoops_PCGS = false;

							_hoops_RRSA = _hoops_PAIH.length();
							_hoops_RGSA = (_hoops_CHPC - _hoops_AAHC) / 3;

							if (j < end - 1 && _hoops_RHHC) {
								/* _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_HCAS _hoops_RH _hoops_ISII _hoops_GH _hoops_PPR _hoops_SR _hoops_HS _hoops_IIHC _hoops_AIRR,
								* _hoops_APRI _hoops_RH _hoops_CGHI _hoops_SCPH, _hoops_GAR _hoops_SCH'_hoops_GRI _hoops_ICAS _hoops_CCAS _hoops_GIHA
								*/
								_hoops_RGSA -= 1;
							}

							_hoops_SGSA(h3ddata, nr, h3ddata->_hoops_ACHC, _hoops_CAPA,
								_hoops_RRSA, _hoops_RGSA, _hoops_SCAS, H3DPT_TRIANGLELIST);
							k = 0;
						}
					}
					i++;
					j++;
				}
			}
			/* _hoops_CPHR _hoops_PSAS.  _hoops_CHRI _hoops_GII _hoops_GGPI */
			if (k) {
				_hoops_HACP->Unlock();
				h3ddata->_hoops_ACHC->Unlock();

				_hoops_RRSA = _hoops_PAIH.length();
				_hoops_RGSA = (_hoops_CHPC - _hoops_AAHC) / 3;

				_hoops_SGSA(h3ddata, nr, h3ddata->_hoops_ACHC, _hoops_CAPA,
					_hoops_RRSA, _hoops_RGSA, _hoops_SCAS, H3DPT_TRIANGLELIST);
			}

			if (_hoops_PIAS) {
				_hoops_IGGH(h3ddata, _hoops_RSR);
				_hoops_PIAS = false;
			}

			if (_hoops_RRHA) {
				_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
				pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
				if (!pair)
					break;
				pe = (Polyedge const *) pair->geo;
				_hoops_GPCP = _hoops_CCAI (pair->color, _hoops_SPAS);
				if (pair->_hoops_CPAI)
					_hoops_SHAS = &pair->_hoops_CPAI->matrix;
				else
					_hoops_SHAS = null;
			}
			else
				break;
		}
	}
	else {
		bool _hoops_HSAS = false;
		bool _hoops_PIAS = false;

		_hoops_IGIC = (int)_hoops_HACP->_hoops_GRIC/2;
		int _hoops_ISAS = 0;
		if (_hoops_RRHA) {
			_hoops_RRHA->_hoops_CRHA->ResetCursor();
			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			while (pair) {
				Polyedge const *pe = (Polyedge const *) pair->geo;
				_hoops_ISAS += pe->total - pe->_hoops_PHHA;
				_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
				pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			}
			_hoops_RRHA->_hoops_CRHA->ResetCursor();
		}
		else
			_hoops_ISAS = pe->total - pe->_hoops_PHHA;
		_hoops_IGIC = _hoops_AHIA(_hoops_ISAS, _hoops_IGIC);


		if (_hoops_SHAS) {
			if (pe->point_count > H3D_Hardware_Transform_Cutoff) {
				_hoops_AGGH(h3ddata, _hoops_SHAS, _hoops_RSR);
				_hoops_PIAS = true;
				_hoops_SHAS = null;
			}
			else {
				if (_hoops_PPCP._hoops_HHCP() && _hoops_SHAS->_hoops_APRA == null)
					HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)_hoops_SHAS);
			}
		}

		_hoops_PCGS = false;
		_hoops_GIAS = (pe->_hoops_ASHA || pe->_hoops_RSHA || !_hoops_PHAS);

		k = 0;
		ei = -1;
		for (;;) {
			i = j = 0;

			while (i < pe->_hoops_PHHA)
			{
				if (pe->lengths)
					len = pe->lengths[i];
				else
					len = pe->total;

				if (len < 0)
					_hoops_ICHC (len, _hoops_RRC, 2);

				end = j+len*_hoops_RRC;

				_hoops_IACP = 0;

				while (j < end-1) {
					if (pe->_hoops_AIHA) {
						/* _hoops_HHHA _hoops_PSPI */
						_hoops_ISPI = pe->_hoops_AIHA[j];
						_hoops_CSPI = pe->_hoops_AIHA[j+1];
					}
					else {
						/* _hoops_CHHA _hoops_PSPI */
						_hoops_ISPI = j;
						_hoops_CSPI = j+1;
					}
					if (pe->_hoops_SPII)
						ei = pe->_hoops_SPII[j+1];
					else
						ei++;
					j+=_hoops_RRC;
					if (!_hoops_PCGS) {
						if (_hoops_PHAS)
							SET_MEMORY(_hoops_PHAS, point_count*sizeof(short), -1);

						_hoops_HACP->Lock(_hoops_IGIC*2, &_hoops_PAIH);
						h3ddata->_hoops_ACHC->Lock(_hoops_IGIC*2, &_hoops_CHAS);
						_hoops_PAHC = _hoops_CHAS;
						_hoops_PCGS = true;
						_hoops_HGIC = 0;
						_hoops_GHAS = 0;
					}

					if (_hoops_PHAS) {
						_hoops_RHAS = _hoops_PHAS[_hoops_ISPI];
						_hoops_AHAS = _hoops_PHAS[_hoops_CSPI];
					}
					else {
						_hoops_RHAS = _hoops_AHAS = -1;
					}

					if (_hoops_RHAS < 0) {
						//_hoops_PSP _hoops_SCGH _hoops_PPSR _hoops_GSGI
						_hoops_RHAS = _hoops_GHAS++;
						if (!_hoops_GIAS)
							_hoops_PHAS[_hoops_ISPI] = _hoops_RHAS;
						_hoops_PACP (nr, pe, _hoops_GHP, &_hoops_PAIH, _hoops_IACP, _hoops_ISPI, ei, _hoops_SHAS, _hoops_GPCP, &_hoops_RPCP);
						_hoops_PAIH._hoops_CPPH();
					}

					if (BIT(flags, H3DID_LINE_PATTERN)) {
						_hoops_HHAS.x = _hoops_HPRA(_hoops_IHCR->matrix->data.elements, pe->points[_hoops_ISPI]);
						_hoops_HHAS.y = _hoops_IPRA(_hoops_IHCR->matrix->data.elements, pe->points[_hoops_ISPI]);
						_hoops_IHAS.x = _hoops_HPRA(_hoops_IHCR->matrix->data.elements, pe->points[_hoops_CSPI]);
						_hoops_IHAS.y = _hoops_IPRA(_hoops_IHCR->matrix->data.elements, pe->points[_hoops_CSPI]);
						_hoops_IACP += sqrt((_hoops_IHAS.x-_hoops_HHAS.x) * (_hoops_IHAS.x-_hoops_HHAS.x) + (_hoops_IHAS.y-_hoops_HHAS.y) * (_hoops_IHAS.y-_hoops_HHAS.y));
						_hoops_AHAS = -1;		//_hoops_HHSA _hoops_CSAS _hoops_IIGR _hoops_RIHC...
					}

					if (_hoops_AHAS < 0) {
						//_hoops_PSP _hoops_SCGH _hoops_PPSR _hoops_GSGI
						_hoops_AHAS = _hoops_GHAS++;
						if (!_hoops_GIAS)
							_hoops_PHAS[_hoops_CSPI] = _hoops_AHAS;
						_hoops_PACP (nr, pe, _hoops_GHP, &_hoops_PAIH, _hoops_IACP, _hoops_CSPI, ei, _hoops_SHAS, _hoops_GPCP, &_hoops_RPCP);
						_hoops_PAIH._hoops_CPPH();
					}

					*_hoops_PAHC++ = _hoops_RHAS;
					*_hoops_PAHC++ = _hoops_AHAS;

					k++;
					if (k == _hoops_IGIC) {
						_hoops_HACP->Unlock();
						h3ddata->_hoops_ACHC->Unlock();
						_hoops_PCGS = false;
						_hoops_SGSA(h3ddata, nr, h3ddata->_hoops_ACHC, _hoops_CAPA, _hoops_PAIH.length(), k, _hoops_SCAS, H3DPT_LINELIST);
						k = 0;
					}
				}
				i++;
				j+= (2-_hoops_RRC);
			}

			if (_hoops_RRHA) {
				_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
				pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
				if (!pair)
					break;
				pe = (Polyedge const *) pair->geo;
				_hoops_GPCP = _hoops_CCAI (pair->color, _hoops_SPAS);
				if (pair->_hoops_CPAI)
					_hoops_SHAS = &pair->_hoops_CPAI->matrix;
				else
					_hoops_SHAS = null;

				if (_hoops_PCGS && (_hoops_PIAS || (_hoops_SHAS != null && pe->point_count > H3D_Hardware_Transform_Cutoff))) {
					_hoops_HACP->Unlock();
					h3ddata->_hoops_ACHC->Unlock();
					_hoops_SGSA(h3ddata, nr, h3ddata->_hoops_ACHC, _hoops_CAPA, _hoops_IGIC*2, k, _hoops_SCAS, H3DPT_LINELIST);
					_hoops_PCGS = false;
					_hoops_HSAS = false;
				}
				if (_hoops_PIAS) {
					_hoops_IGGH(h3ddata, _hoops_RSR);
					_hoops_PIAS = false;
				}
				if (_hoops_SHAS) {
					if (pe->point_count > H3D_Hardware_Transform_Cutoff) {
						_hoops_AGGH(h3ddata, _hoops_SHAS, _hoops_RSR);
						_hoops_PIAS = true;
						_hoops_SHAS = null;
					}
					else {
						if (_hoops_PPCP._hoops_HHCP() && _hoops_SHAS->_hoops_APRA == null)
							HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)_hoops_SHAS);
					}
				}
				if (_hoops_PHAS)
					SET_MEMORY(_hoops_PHAS, pe->point_count*sizeof(short), -1);
			}
			else
				break;
		}
		/* _hoops_CPHR _hoops_PSAS.  _hoops_SSAS _hoops_SCH _hoops_HCR _hoops_HGCR _hoops_GGPS, _hoops_PAR _hoops_HRGR _hoops_IIH _hoops_CPHP _hoops_RAAP _hoops_IAPR? */
		if (k) {
			_hoops_HACP->Unlock();
			h3ddata->_hoops_ACHC->Unlock();
			_hoops_SGSA(h3ddata, nr, h3ddata->_hoops_ACHC, _hoops_CAPA, _hoops_PAIH.length(), k, _hoops_SCAS, H3DPT_LINELIST);
		}
		if (_hoops_PIAS)
			_hoops_IGGH(h3ddata, _hoops_RSR);
	}

	dc->_hoops_SPA->modelling_matrix = _hoops_CSGI;
	dc->_hoops_SPA->color = _hoops_GGRI;

} // _hoops_RSGR _hoops_API '_hoops_CPSA _hoops_PGSA 3d _hoops_ACRI _hoops_RGPS'



bool _hoops_HSRI (
		Net_Rendition const &nr,
		Line_Rendition const &_hoops_GHP,
		bool _hoops_AGPS,
		float weight)
{
	if (ANYBIT(_hoops_GHP->line_style->flags, LSF_COMPLEX_ANYBITS)) {
		return true;
	}
	
	if (_hoops_GHP->style & LPAT_MASK) {
		return true;
	}

	if (weight > H3D_LARGEST_PRECOMPUTED_CIRCLE)
		return true;

	//_hoops_SR _hoops_PGPS _hoops_HHGC _hoops_IS _hoops_GCGH _hoops_GAGS _hoops_SPPR, _hoops_HIH _hoops_SSIA _hoops_SPGA'_hoops_RA
	//_hoops_HGPS _hoops_GAPR
	if (_hoops_GHP->_hoops_CPA == nr->_hoops_RHP->_hoops_CPA && //_hoops_APGR _hoops_PAH'_hoops_RA _hoops_SHH _hoops_GAGS
		_hoops_GHP->_hoops_CHA &&
		_hoops_AGPS &&
		_hoops_GHP->_hoops_CHA->_hoops_IRIR < 1.0f && 
		nr->_hoops_CPP->_hoops_PRH._hoops_SRI != _hoops_PIII) {
		return true;
	}
	return false;
}


local bool _hoops_IGPS(H3DIndexedBufferObject *_hoops_CGPS, H3D_Display_List *odl, H3D_Display_List_Bin *_hoops_RRHA)
{
	if (!_hoops_CGPS->_hoops_SGPS()) {
		delete _hoops_CGPS;
		if (odl->item.geometry.id != 0) {
			while ((_hoops_CGPS = odl->item.geometry.id->RemoveFirst ()) != null)
				delete _hoops_CGPS;
			FREE (odl->item.geometry.id, H3DIndexedBufferObject_List);
			odl->item.geometry.id = null;
		}
		if (_hoops_RRHA) {
			_hoops_RRHA->odl = null;
			_hoops_RRHA->flags |= DL_INSUFFICIENT_VRAM;
		}
		return false;
	}
	return true;
}

/*
 * _hoops_PGAA
 * _hoops_GRPS _hoops_RRPS _hoops_IS _hoops_RH _hoops_HSPR _hoops_ARPS:
 *
 *  _hoops_CAH _hoops_ISPR
 *  _hoops_PRPS _hoops_GAPA _hoops_GCSP/_hoops_HRPS/_hoops_GHSI _hoops_GCSP
 *  _hoops_SIHA _hoops_GCHA
 *  _hoops_ARP _hoops_IRPS
 *  _hoops_PGGC
 *  _hoops_ARP _hoops_GH _hoops_PGAS
 *  _hoops_ARP _hoops_GH _hoops_PAIA
 *  _hoops_AASA _hoops_IS _hoops_RGPS _hoops_RPP _hoops_IRPR
 *  _hoops_RPP (_hoops_CRPS) {
 * 	  _hoops_ARPR _hoops_GPHA/_hoops_CIHA _hoops_PSCA
 * 	  _hoops_IH (;;) {
 * 		_hoops_RPP (_hoops_SCGI) {
 * 		  _hoops_SRPS _hoops_SAHA
 * 		  _hoops_IHSA _hoops_RPP _hoops_IRAP
 * 		}
 * 		_hoops_CIPH _hoops_GHSI _hoops_GCSP
 * 		_hoops_SHS _hoops_CIPH _hoops_HRPS
 * 		_hoops_SHS _hoops_CIPH _hoops_GCSP
 * 	  }
 *  }
 *  _hoops_GAPS _hoops_CIGR _hoops_IS _hoops_ARP _hoops_GH _hoops_PIAP
 *  _hoops_AA {
 * 	  _hoops_RAPS->_hoops_GISP ()
 *  } _hoops_HPGP _hoops_PCCC
 */
void really_draw_3d_polyedge (
		Net_Rendition const &		nr,
		Polyedge const *			pe,
		Line_Rendition const &		_hoops_GHP,
		H3D_Display_List_Bin *		_hoops_RRHA)
{
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;
	H3DData alter *				h3ddata = H3DD (dc);
	_hoops_HHA			matr = _hoops_GHP->_hoops_CHA;
	H3DShader *					_hoops_RSR;
	int							i, j = 0, len, start, end, _hoops_RRC = 1;
	H3DIndexedBufferObject *	_hoops_CGPS = null;
	_hoops_IAPA const *	_hoops_CAPA = null;
	int 						_hoops_SRRS = 0;
	int 						type = 0;
	H3DVertexBuffer 			&_hoops_PAIH = h3ddata->_hoops_CP;
	H3DVertexFormat 			_hoops_PPCP;
	_hoops_GACR alter *		dl = null;
	H3D_Display_List alter *	odl = null;
	bool						_hoops_IRRS;
	unsigned int				_hoops_SRHA = 0;
	unsigned int				_hoops_CARI = 0;
	bool						_hoops_IAHC = false;
	Polyedge alter *			_hoops_HPAS = (Polyedge alter *) pe;
	_hoops_IRHA *				pair = null;
	_hoops_HRPA const *			matrix = null;
	RGB const *					_hoops_GPCP = _hoops_CCAI (dc->_hoops_SPA->color, Color_EDGE);
	int							point_count, _hoops_SPHA, _hoops_CPHA;
	H3D_Vertex_Buffer_Style		_hoops_APHA;
	bool						_hoops_CRRS = true;
	int							_hoops_GRRA, _hoops_RARR;
	bool						_hoops_RHHC = false;
	int							_hoops_PIPC = -1;		// _hoops_IH _hoops_AAIA _hoops_APGR
	int							_hoops_AIPC = -1;		// _hoops_IH _hoops_AAIA _hoops_APGR
	int							_hoops_HIPC = -1;		// _hoops_IH _hoops_AAIA _hoops_APGR
	bool						_hoops_SIPC = (_hoops_GHP == nr->_hoops_RHP);
	bool						_hoops_AAPS = false;
	int	*						_hoops_PAPS = null;
	int							weight;
	bool						_hoops_CISP;
	int							_hoops_HAPS = 1;

	if (pe && pe->_hoops_PHHA == 0 && !BIT (pe->_hoops_SRHA, DL_DO_NOT_RECOMPILE))
		return;

	if (_hoops_GHP == nr->_hoops_RHP) {
		if (!pe) {
			pair = _hoops_RRHA->_hoops_CRHA->PeekFirst();
			pe = (Polyedge *) pair->geo;
		}
		if (BIT (pe->_hoops_CARI, _hoops_RCRI))
			type = _hoops_GPA;
		else
			type = T_EDGES;
	}
	else {
		type = T_LINES;
	}

	_hoops_CISP = matr && (matr->_hoops_IRIR < 1.0f ||
		(matr->_hoops_SCA &&
		BIT (matr->_hoops_SCA->texture->flags, _hoops_IAPS) &&
		!BIT (matr->_hoops_SCA->texture->_hoops_SCR, _hoops_PGA)));

	weight = _hoops_GHP->weight;
	if (weight < 0)
		weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP,1.0f, false, 0, true)+0.5f);

	if (pe && !h3ddata->_hoops_GSA) {

		if (_hoops_RRHA)
			_hoops_SRHA = _hoops_RRHA->flags;
		else {
			_hoops_SRHA = pe->_hoops_SRHA;
			_hoops_CARI = pe->_hoops_CARI;
		}

		bool _hoops_AGPS =
			_hoops_CISP &&
			!ANYBIT (_hoops_SRHA, DL_DO_NOT_DEFER|DL_3D_TRANSPARENCY);
		_hoops_IAHC = _hoops_HSRI (nr, _hoops_GHP, _hoops_AGPS, weight);

		if (!_hoops_HPCA(nr, _hoops_CAPA))
			_hoops_IAHC = true;

		/* [11826] - _hoops_IPHR _hoops_AARI _hoops_PGGS _hoops_CAPS _hoops_SAPS _hoops_PPSR _hoops_GPPS _hoops_CGPR _hoops_RPPS _hoops_IGAA < _hoops_APPS */
		if (pe->_hoops_GSCP != null && 
			pe->_hoops_GSCP->type == _hoops_GGCP &&
			nr->transform_rendition->_hoops_SPH->projection == _hoops_GHH &&
			BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP))
		{
			Grid const *grid = (Grid const *) pe->_hoops_GSCP;
			if (grid->count1 == 0 || grid->count2 == 0)
				_hoops_IAHC = true;
		}

		if (_hoops_IAHC) {
			if (h3ddata->_hoops_CIGI)
				h3ddata->_hoops_CIGI->mask &= ~_hoops_IGAI;

			if (BIT(pe->_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
				/* _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_AIRI _hoops_HIGR _hoops_RGAR, _hoops_SIHH _hoops_RH _hoops_PPPS _hoops_SIHC _hoops_GGR _hoops_AGR _hoops_IS _hoops_CAH */
				Polyedge alter *_hoops_HPAS = (Polyedge alter *) pe;
				_hoops_GACR alter *dl;
				H3D_Display_List alter *odl=0;
				bool _hoops_RACR = false;

				_hoops_RACR = _hoops_AACR(nr, &_hoops_HPAS->_hoops_GAHA, &dl, &odl, H3D_DL_GEOMETRY);
				HD_Queue_Destroy_List (odl, true);
			}
			else {
				Net_Rendition _hoops_CRAI = nr;
				if (_hoops_CRAI->_hoops_RHP->_hoops_CPA != _hoops_GHP->_hoops_CPA)
					_hoops_CRAI.Modify()->_hoops_RHP = _hoops_GHP;

				if (BIT (_hoops_SRHA, _hoops_GGIA))
					HD_Draw_Indexicated_3D_Polyedge (_hoops_CRAI, pe);
				else
					HD_Std_3D_Polyedge (_hoops_CRAI, pe);
			}
			return;
		}
	}

	H3D_TRACE(h3ddata, "draw_3d_polyedge");

	_hoops_APHA = _hoops_GRHA (pe, _hoops_RRHA, &_hoops_SRHA);
	_hoops_RPHA (pe, _hoops_RRHA, _hoops_APHA, &_hoops_CPHA, &point_count, &_hoops_SPHA);
	_hoops_CRRS = (
		nr->_hoops_IRR->_hoops_GAHA &&
		BIT(_hoops_GHP->line_style->flags, LSF_SOLID) &&
		Abs(_hoops_CPHA) > 1);

	/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_IGGC _hoops_IH _hoops_CAGH _hoops_PAPA _hoops_AIRI _hoops_CPCI */
	if (h3ddata->_hoops_ISCI && type != T_LINES)
	{
		bool _hoops_HIRS = false;
		Action_Mask _hoops_HPPS = ((type == _hoops_GPA) ? _hoops_RSRI : _hoops_ASRI);

		if (ANYBIT (h3ddata->_hoops_CIGI->_hoops_RRSI, _hoops_HPPS))
			return;  //_hoops_CIRS _hoops_SIRS _hoops_IS _hoops_CRHR _hoops_GCRS _hoops_RCRS _hoops_CPAP

		if (BIT (pe->_hoops_SRHA, DL_SUPPRESS_SEGMENT_DISPLAY_LISTS))
			_hoops_HIRS = true;  //_hoops_HHHA _hoops_IPPS
		else if (!h3ddata->_hoops_CSC->_hoops_RAIH && _hoops_CISP)
			_hoops_HIRS = true;  //_hoops_AGSI _hoops_IHSP
		else if (h3ddata->_hoops_CHSP.mode || h3ddata->_hoops_PI.mode)
			_hoops_HIRS = true;  //_hoops_RGCH _hoops_PAH _hoops_SGH _hoops_HIH _hoops_HAR _hoops_CAHP _hoops_HCGI'_hoops_GRI
		//_hoops_SHS _hoops_RPP (_hoops_SAHA->_hoops_CPPS && _hoops_IRRC (_hoops_SAHA->_hoops_HGCI, _hoops_SPPS))
		//	_hoops_GHPS = _hoops_IHPR;  //_hoops_AGCR _hoops_GPHA _hoops_RHPS _hoops_CHR _hoops_AHPS _hoops_IS _hoops_AGRP _hoops_SIHH _hoops_PHPS
		else if (nr->_hoops_IRR->_hoops_GAHA == Display_List_GEOMETRY &&
			!BIT (_hoops_SRHA, DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS))
			_hoops_HIRS = true;  //_hoops_HHPS _hoops_CPAP _hoops_AIRI _hoops_CPCI
		else if (!BIT(_hoops_GHP->line_style->flags, LSF_SOLID))
			_hoops_HIRS = true;

		if (!_hoops_HIRS) {
			// _hoops_RH _hoops_PGGC _hoops_CPAP _hoops_AGIR _hoops_CGH _hoops_RGAR _hoops_IHPS _hoops_CCA _hoops_HPHR _hoops_SAHA'_hoops_GRI, _hoops_HAR _hoops_SCGI'_hoops_GRI
			ASSERT (pe);
			ASSERT (!_hoops_RRHA);
			Polyedge alter *_hoops_CHPS = (Polyedge alter *) pe;
			_hoops_IRHA *pair;
			_hoops_AIGI *list = null;

			if (pe->_hoops_AIHA == null)
				return;

			//_hoops_SR _hoops_CGH _hoops_RGAR _hoops_HGCR _hoops_ARI _hoops_CCA _hoops_HPHR _hoops_AHHA, _hoops_HAR _hoops_SHPS _hoops_PGRC
			ASSERT (_hoops_GHP == nr->_hoops_RHP);

			if (!pe->_hoops_ASHA &&
				!pe->_hoops_PCHA &&
				!_hoops_GPCP &&
				nr->_hoops_RHP->_hoops_CPA != h3ddata->_hoops_CIGI->nr->_hoops_RHP->_hoops_CPA)
				h3ddata->_hoops_CIGI->_hoops_SIGI = true;

			if (dc->_hoops_RAI &&
				(dc->_hoops_RAI->type == _hoops_CSIP ||
				 dc->_hoops_RAI->type == _hoops_ASIP)) {
				if (!h3ddata->_hoops_CIGI->_hoops_CIRI)
					h3ddata->_hoops_CIGI->_hoops_CIRI = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);
				list = h3ddata->_hoops_CIGI->_hoops_CIRI;
			}
			else {
				if (BIT (pe->_hoops_CARI, _hoops_RCRI)) {
					if (!h3ddata->_hoops_CIGI->_hoops_SIRI)
						h3ddata->_hoops_CIGI->_hoops_SIRI = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);
					list = h3ddata->_hoops_CIGI->_hoops_SIRI;
				}
				else {
					if (!h3ddata->_hoops_CIGI->_hoops_IIRI)
						h3ddata->_hoops_CIGI->_hoops_IIRI = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);
					list = h3ddata->_hoops_CIGI->_hoops_IIRI;
				}
			}

			if (BIT(pe->_hoops_SRHA, DL_TEMPORARY_DATA))
				HD_Isolate_Polyedge_Data (dc, pe);

			_hoops_CHPS->_hoops_CARI |= _hoops_SARI;
			pair = POOL_NEW(dc->memory_pool, _hoops_IRHA)(nr, pe, 
				dc->_hoops_SPA->modelling_matrix, dc->_hoops_SPA->color);
			
			list->AddFirst(pair);
			return;
		}
		matrix = null;
		h3ddata->_hoops_CIGI->mask &= ~_hoops_HPPS;
		if (h3ddata->_hoops_CIGI->_hoops_IHGI)
			return;
	}

	_hoops_HCI _hoops_RPCP;
	_hoops_HRIA(h3ddata, nr, type, _hoops_SRHA, _hoops_CARI, &_hoops_RPCP);

	/* _hoops_RAP _hoops_GH _hoops_RH _hoops_AI _hoops_PPR _hoops_III _hoops_PAIA */
	if (!BIT(_hoops_GHP->line_style->flags, LSF_SOLID)) {
		_hoops_RPCP._hoops_GGC++;
		_hoops_SII(_hoops_HIRR, 0, &_hoops_RPCP, null, null, &_hoops_RARR);
		_hoops_HSAH((Display_Context *)nr->_hoops_SRA, _hoops_GHP->line_style);
		h3ddata->_hoops_GSCR->_hoops_GSAC(nr, 0, _hoops_GIPS, h3ddata->_hoops_ISAH, _hoops_RARR);
		_hoops_SRRS |= H3DID_LINE_PATTERN;
	}

	/* _hoops_RAP _hoops_GH _hoops_CIHA _hoops_HH */
	if (BIT(_hoops_SRHA, _hoops_GGIA)) {
		 _hoops_SII(_hoops_IAAR, 0, &_hoops_RPCP, null, null, &_hoops_RARR);
		H3DTexture *_hoops_ACRS = _hoops_GHAH(h3ddata, nr);
		h3ddata->_hoops_GSCR->_hoops_GSAC(nr, null, _hoops_PCRS, _hoops_ACRS, _hoops_RARR);
	}

	/* _hoops_RAP _hoops_GH _hoops_III _hoops_CII _hoops_IH _hoops_AAIA _hoops_APGR */
	int _hoops_SAHC;
	_hoops_SII(_hoops_SHRR, 0, &_hoops_RPCP, &_hoops_PIPC, null, null);
	_hoops_SII(_hoops_CHRR, 0, &_hoops_RPCP, &_hoops_AIPC, null, null);
	_hoops_SII(_hoops_IHRR, 0, &_hoops_RPCP, &_hoops_HIPC, null, &_hoops_SAHC);
	if (BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP) ||
		(weight > 1 && ANYBIT(_hoops_GHP->style, LJOIN_ROUND|LCAP_ROUND|LCAP_END_ROUND))) {
		ENSURE_TRANSPARENCY (h3ddata, true);
		if (!h3ddata->_hoops_HSI.valid)
			_hoops_HRPC (h3ddata);
		h3ddata->_hoops_GSCR->_hoops_GSAC (nr, null, _hoops_SPHC, h3ddata->_hoops_HSI.texture, _hoops_SAHC);
	}
	else
		ENSURE_TRANSPARENCY (h3ddata, !h3ddata->_hoops_RHH.mode &&
				nr->_hoops_CPP->_hoops_PRH._hoops_HRH);

	/* _hoops_HCRS _hoops_RHIR _hoops_RH _hoops_ACSP _hoops_IIGR _hoops_RH _hoops_AI */
	int _hoops_SIR = 0;
	if (matr->_hoops_ARIR)
	{
		H3DTexture *id = null;
		_hoops_RCR *txr = null;

		if (matr->_hoops_SCA) {
			_hoops_HIR *_hoops_GRIA = matr->_hoops_SCA;
			do {
				txr = _hoops_GRIA->texture;
				_hoops_SII(_hoops_PSRR, _hoops_SIR++, &_hoops_RPCP, null, null, &_hoops_RARR);
				id = _hoops_PIGH(h3ddata, nr, txr, 0);
				h3ddata->_hoops_GSCR->_hoops_GSAC(nr, txr, 0, id, _hoops_RARR);
			} while ((_hoops_GRIA = _hoops_GRIA->next) != null);
		}
		if ((txr = matr->texture[_hoops_RIA]) != null) {
			_hoops_SII(_hoops_CAAR, 0, &_hoops_RPCP, null, null, &_hoops_RARR);
			id = _hoops_PIGH(h3ddata, nr, txr, _hoops_HSGH);
			h3ddata->_hoops_GSCR->_hoops_GSAC(nr, txr, _hoops_HSGH, id, _hoops_RARR);
		}
		if ((txr = matr->texture[_hoops_ACA]) != null) {
			_hoops_SII(_hoops_RPAR, 0, &_hoops_RPCP, null, null, &_hoops_RARR);
			id = _hoops_PIGH(h3ddata, nr, txr, 0);
			h3ddata->_hoops_GSCR->_hoops_GSAC(nr, txr, 0, id, _hoops_RARR);
		}
		if ((txr = matr->texture[_hoops_IIA]) != null) {
			_hoops_SII(_hoops_APAR, 0, &_hoops_RPCP, null, null, &_hoops_RARR);
			id = _hoops_PIGH(h3ddata, nr, txr, 0);
			h3ddata->_hoops_GSCR->_hoops_GSAC(nr, txr, 0, id, _hoops_RARR);
		}
		if ((txr = matr->texture[_hoops_HIA]) != null) {
			_hoops_SII(_hoops_PPAR, 0, &_hoops_RPCP, null, null, &_hoops_RARR);
			id = _hoops_PIGH(h3ddata, nr, txr, 0);
			h3ddata->_hoops_GSCR->_hoops_GSAC(nr, txr, 0, id, _hoops_RARR);
		}
		if ((txr = matr->texture[_hoops_PCA]) != null) {
			_hoops_SII(_hoops_HPAR, 0, &_hoops_RPCP, null, null, &_hoops_RARR);
			id = _hoops_PIGH(h3ddata, nr, txr, 0);
			h3ddata->_hoops_GSCR->_hoops_GSAC(nr, txr, 0, id, _hoops_RARR);
		}
		if ((txr = matr->texture[_hoops_HCA]) != null) {
			_hoops_SII(_hoops_CPAR, 0, &_hoops_RPCP, null, null, &_hoops_RARR);
			id = _hoops_PIGH(h3ddata, nr, txr, 0);
			h3ddata->_hoops_GSCR->_hoops_GSAC(nr, txr, 0, id, _hoops_RARR);
		}
	}

	_hoops_RHSA (h3ddata, H3DCULL_NONE);

	if (BIT(_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
		odl = (H3D_Display_List *) pe->_hoops_GAHA->list;
		_hoops_PPCP = odl->_hoops_PPCP;
	}
	else {
		if (_hoops_RRHA) {
			//_hoops_SRPS _hoops_SPR _hoops_ACRI _hoops_PSAP _hoops_RH _hoops_RIPS _hoops_IS _hoops_CAHA _hoops_GGSR _hoops_PCPA _hoops_PGAS _hoops_IS _hoops_SGH
			pair = _hoops_RRHA->_hoops_CRHA->PeekFirst();
			pe = (Polyedge const *) pair->geo;
			_hoops_GPCP = _hoops_CCAI (pair->color, Color_EDGE);
		}
		/* _hoops_ARP _hoops_GH _hoops_RH _hoops_AIPS _hoops_SGI */
		_hoops_PPCP._hoops_AIHC();
		if (pe->_hoops_ICHA || pe->_hoops_RSHA)
			_hoops_PPCP._hoops_CCRS();
		if (pe->_hoops_PCHA || pe->_hoops_ASHA || _hoops_GPCP)
			_hoops_PPCP._hoops_RPHC();

		if (BIT(_hoops_SRRS, H3DID_LINE_PATTERN)) {
			_hoops_SII(_hoops_HIRR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
			_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
			_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
		}
		if (BIT(_hoops_SRHA, _hoops_GGIA)) {
			_hoops_SII(_hoops_IAAR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
			_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
			_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
		}

		if (nr->_hoops_IRR->_hoops_SRI == _hoops_GAI &&
			BIT (nr->transform_rendition->heuristics, _hoops_IRI)) {
			_hoops_SII(_hoops_ACPR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
			_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
			_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 1);
		}

		if (h3ddata->_hoops_IHP ||
			weight > 1 || BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)) {
			_hoops_PPCP._hoops_SCRS(_hoops_HIPC);
			_hoops_PPCP._hoops_SCRS(_hoops_AIPC);

			if (!_hoops_SIPC) {
				// _hoops_PIHC _hoops_APGR _hoops_RRP _hoops_PCCP _hoops_IHH _hoops_GIHC _hoops_IH _hoops_RH "_hoops_PGHC" _hoops_PPSR
				if ((_hoops_GHP->style & LJOIN_MASK) == LJOIN_MITER) {
					if (weight > 1) {
						_hoops_RHHC = true;
						_hoops_PPCP._hoops_SCRS(_hoops_PIPC);
						_hoops_PPCP._hoops_HIHC(_hoops_PIPC, 3);
					}

					// _hoops_HSRR _hoops_GIRR _hoops_RIRR/_hoops_AIRR, _hoops_SR _hoops_RGAR _hoops_RRP _hoops_PCCP _hoops_IHH _hoops_HH _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_IIHC _hoops_APGR
					// _hoops_CIHC _hoops_IIHC _hoops_APGR, _hoops_RH _hoops_AII _hoops_SCIR _hoops_HCR _hoops_RH _hoops_SIHC _hoops_SIGR
					if (ANYBIT(_hoops_GHP->style, LJOIN_ROUND | LCAP_ROUND | LCAP_END_ROUND))
						_hoops_PPCP._hoops_APHC();
				}
			}
			_hoops_PPCP._hoops_HIHC(_hoops_HIPC, 4);
			_hoops_PPCP._hoops_HIHC(_hoops_AIPC, 3);
		}

		int _hoops_ASRR = 0;
		if (matr->_hoops_ARIR && pe->_hoops_GSHA > 0) {
			_hoops_HIR *_hoops_PGC = matr->_hoops_SCA;
			for (_hoops_ASRR = 0; _hoops_ASRR < _hoops_SIR; _hoops_ASRR++) {
				_hoops_SII(_hoops_PSRR, _hoops_ASRR, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
				_hoops_PGC = _hoops_PGC->next;
			}

			if (matr->texture[_hoops_IIA]) {
				_hoops_SII(_hoops_APAR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
			}
			if (matr->texture[_hoops_HIA]) {
				_hoops_SII(_hoops_PPAR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
			}
			if (matr->texture[_hoops_ACA]) {
				_hoops_SII(_hoops_RPAR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
			}
			if (matr->texture[_hoops_PCA]) {
				_hoops_SII(_hoops_HPAR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
			}
			if (matr->texture[_hoops_HCA]) {
				_hoops_SII(_hoops_CPAR, 0, &_hoops_RPCP, &_hoops_GRRA, null, null);
				_hoops_PPCP._hoops_SCRS(_hoops_GRRA);
				_hoops_PPCP._hoops_HIHC(_hoops_GRRA, 3);
			}
		}
	}
	_hoops_GCHC (h3ddata, _hoops_PPCP);
	
	h3ddata->_hoops_AIC = (
		nr->_hoops_IRR->_hoops_SRI == _hoops_GAI && 
		BIT (nr->transform_rendition->heuristics, _hoops_IRI));

	if (pe && BIT (pe->_hoops_SRHA, DL_DO_NOT_RECOMPILE))
		//_hoops_RPP _hoops_RH _hoops_SAHA _hoops_HRGR _hoops_SAHR _hoops_IRS _hoops_PIPS, _hoops_SR _hoops_HS _hoops_PSP _hoops_PIH _hoops_PPR _hoops_SR _hoops_RGCA _hoops_SGH _hoops_AIRI _hoops_CPCI
		_hoops_CRRS = true;
	else if (nr->_hoops_IRR->_hoops_GAHA == Display_List_GEOMETRY) {
		//_hoops_CCA _hoops_HCGI, _hoops_AASC _hoops_HRGR _hoops_HIPS _hoops_HPGR _hoops_IIPS, _hoops_HAR _hoops_ARI
		_hoops_CRRS = (!BIT(pe->_hoops_SRHA, DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS) && 
							 pe->point_count >= H3D_Display_List_MINIMUM);
	}
	else if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT) {
		if (_hoops_RRHA)
			_hoops_CRRS = !BIT(_hoops_RRHA->flags, DL_SUPPRESS_SEGMENT_DISPLAY_LISTS);
		else
			_hoops_CRRS = !BIT(pe->_hoops_SRHA, DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS);
	}
	else
		_hoops_CRRS = false;

	if (!_hoops_CRRS) {
  _hoops_CIPS:
		if (h3ddata->_hoops_CIGI) {
			if (!BIT (_hoops_SRHA, DL_SUPPRESS_SEGMENT_DISPLAY_LISTS))
				h3ddata->_hoops_CIGI->mask &= ~_hoops_ASRI;
			if (h3ddata->_hoops_CIGI->_hoops_IHGI)
				return;
		}

		_hoops_ISGI const *_hoops_CSGI = dc->_hoops_SPA->modelling_matrix;
		_hoops_SSGI const *_hoops_GGRI = dc->_hoops_SPA->color;
		if (_hoops_RRHA) {
			H3DVertexFormat _hoops_SIPS = _hoops_PPCP;

			_hoops_RRHA->_hoops_CRHA->ResetCursor();
			_hoops_CPAS (nr, pe, _hoops_RRHA, _hoops_GHP, _hoops_APHA, _hoops_SIPS);
		}
		else {
			dc->_hoops_SPA->modelling_matrix = null;
			_hoops_CPAS (nr, pe, null, _hoops_GHP, _hoops_APHA, _hoops_PPCP);
		}
		dc->_hoops_SPA->modelling_matrix = _hoops_CSGI;
		dc->_hoops_SPA->color = _hoops_GGRI;
		if (_hoops_PAPS) {
			FREE_ARRAY(_hoops_PAPS, _hoops_HAPS, int);
			_hoops_PAPS = null;
		}
		return;
	}

	if (_hoops_RRHA) {
		ZALLOC(_hoops_RRHA->odl, H3D_Display_List);
		odl = _hoops_RRHA->odl;
		odl->type = H3D_DL_GEOMETRY;
		odl->time_stamp = HOOPS_WORLD->_hoops_GPPI;
		_hoops_HAPS = _hoops_RRHA->_hoops_CRHA->Count();
		_hoops_IRRS = true;
	}
	else {

		bool _hoops_GCPS = true;

		_hoops_IRRS = _hoops_AACR(nr, &_hoops_HPAS->_hoops_GAHA, &dl, &odl, H3D_DL_GEOMETRY);

		if (type != T_LINES &&
			pe->_hoops_GSCP != null && /* _hoops_RSPH _hoops_AHHA _hoops_SGS _hoops_RCPS _hoops_IS _hoops_IHHH _hoops_ACPS */
			!_hoops_APRC(nr, pe, dl, odl))
			_hoops_GCPS = false;

		/* _hoops_AGAS _hoops_RH _hoops_AIRI _hoops_HIGR _hoops_RPP _hoops_GII _hoops_GCAC _hoops_SGI _hoops_PAR _hoops_RH _hoops_PGAS _hoops_HS _hoops_HGAS */
		if (!_hoops_IRRS &&
			(dl->_hoops_GSAI == (_hoops_GHGI) DL_FLAG_INVALID ||
			_hoops_PPCP != odl->_hoops_PPCP ||
			!_hoops_GCPS))
		{
			HD_Queue_Destroy_List (odl, true);
			if (BIT(_hoops_SRHA, DL_DO_NOT_RECOMPILE))
				return;

			_hoops_IRRS = _hoops_AACR(nr, &_hoops_HPAS->_hoops_GAHA, &dl, &odl, H3D_DL_GEOMETRY);
		}
	}

	if (_hoops_IRRS) {
		bool _hoops_AAAS = false;
		unsigned int _hoops_PCPS = h3ddata->_hoops_ACGH._hoops_CGGI;
		unsigned int _hoops_HCPS = h3ddata->_hoops_ACGH._hoops_GRGI * 3;
		float *_hoops_ICPS = null;
		short *_hoops_CCPS = null;
		int _hoops_SCPS = 0;
		int _hoops_GSPS = 0;
		bool _hoops_PCGS = false;
		H3DIndexBuffer _hoops_CHPC;
		H3D_Bounding_Tree *_hoops_RSPS = null;

		if (h3ddata->_hoops_IHP ||
			weight > 1 ||
			BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)) {
			Point _hoops_ASPS, _hoops_PSPS;
			Point _hoops_HSPS, _hoops_ISPS;
			bool _hoops_GIPC = false;
			int _hoops_HHHC = 0, _hoops_CHHC = 0;
			int _hoops_PHHC = 4, _hoops_IHHC = 6;
			int _hoops_CSPS = 0;
			int start, end;
			int ei;
			int index = 0;

			_hoops_CSPS = Abs(_hoops_CPHA) / 2;

			if (weight > 1) {
				if (_hoops_SIPC || ANYBIT(_hoops_GHP->style, LJOIN_ROUND | LJOIN_BEVEL)) {
					_hoops_PHHC += 4;
					_hoops_IHHC += 6;
				}
				if (!_hoops_SIPC && (_hoops_GHP->style & LJOIN_MASK) == LJOIN_MITER) {
					_hoops_PHHC += 1;
					_hoops_IHHC += 6;
				}
				// _hoops_PS _hoops_RRP _hoops_IS _hoops_RPR _hoops_GH _hoops_IHH _hoops_GIHA/_hoops_PSPI _hoops_SSPS
				for (;;) {
					if (_hoops_RRHA) {
						pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
						if (!pair)
							break;
						_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
						pe = (Polyedge const *) pair->geo;
					}
					if (pe->total > 0) {
						if (_hoops_SIPC || ANYBIT(_hoops_GHP->style, LCAP_MASK)) {
							_hoops_HHHC += 8 * pe->_hoops_PHHA;
							_hoops_CHHC += 12 * pe->_hoops_PHHA;
						}
						if (!_hoops_SIPC && (_hoops_GHP->style & LJOIN_MASK) == LJOIN_MITER) {
							_hoops_HHHC += 2 * pe->_hoops_PHHA;
						}

						// _hoops_RCPA _hoops_HIHA _hoops_IH _hoops_GGHS _hoops_RGHS, _hoops_GGCR _hoops_HHH _hoops_IHH _hoops_PSPI/_hoops_GIHA _hoops_IH _hoops_GRR _hoops_ACRI
						if (_hoops_SIPC || ANYBIT(_hoops_GHP->style, LJOIN_ROUND | LJOIN_BEVEL)) {
							_hoops_HHHC += (4 * pe->_hoops_PHHA);
							_hoops_CHHC += (6 * pe->_hoops_PHHA);
						}
						if (!_hoops_SIPC && (_hoops_GHP->style & LJOIN_MASK) == LJOIN_MITER) {
							_hoops_HHHC += (1 * pe->_hoops_PHHA);
							_hoops_CHHC += (6 * pe->_hoops_PHHA);
						}
					}
					else {
						if (_hoops_SIPC || ANYBIT(_hoops_GHP->style, LCAP_MASK)) {
							_hoops_HHHC += 8 * _hoops_CSPS;
							_hoops_CHHC += 12 * _hoops_CSPS;
						}
					}

					if (!_hoops_RRHA)
						break;
				}
			}

			// _hoops_SSCR _hoops_GGSR _hoops_SRHR _hoops_PGRR _hoops_PPR _hoops_AGHS
			unsigned int _hoops_RRSA = (_hoops_CSPS+1) * _hoops_PHHC + _hoops_HHHC;
			unsigned int _hoops_PGHS = (_hoops_CSPS * _hoops_IHHC + _hoops_CHHC) / 3;


			_hoops_PCPS = h3ddata->_hoops_ACGH._hoops_CGGI;
			if (h3ddata->_hoops_IHP)
				_hoops_PCPS /= 6;
			if (_hoops_RRSA > _hoops_PCPS)
				_hoops_AAAS = true;

			_hoops_HCPS = h3ddata->_hoops_ACGH._hoops_GRGI;
			if (_hoops_PGHS * 3 > _hoops_HCPS)
				_hoops_AAAS = true;

			H3DFORMAT format = (_hoops_PCPS <= 0xffff && _hoops_HCPS / 3 <= 0xffff)? H3DFMT_INDEX16 : H3DFMT_INDEX32;
			int stride = (format == H3DFMT_INDEX16) ? 1 : 2;

			_hoops_SCPS = _hoops_PCPS * _hoops_PPCP._hoops_HGHS(false);
			POOL_ALLOC_ARRAY_CACHED (_hoops_ICPS, _hoops_SCPS, float, dc->memory_pool);

			_hoops_GSPS = _hoops_HCPS * stride;
			POOL_ALLOC_ARRAY_CACHED (_hoops_CCPS, _hoops_GSPS, short, dc->memory_pool);


			// _hoops_PCSH _hoops_SIIA
			if (_hoops_RRHA)
				_hoops_RRHA->_hoops_CRHA->ResetCursor();

			for (;;) {
				if (_hoops_RRHA) {
					pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
					if (!pair)
						break;
					_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
					pe = (Polyedge const *) pair->geo;
					if (pair->_hoops_CPAI)
						matrix = &pair->_hoops_CPAI->matrix;
					else
						matrix = null;
					_hoops_GPCP = _hoops_CCAI (pair->color, Color_EDGE);

					// _hoops_IGHS _hoops_CAGH _hoops_PAPA _hoops_CGHS, _hoops_HIS _hoops_HRCI _hoops_GII _hoops_CPAP _hoops_CGHS
					if (pe->_hoops_GAHA && pe->_hoops_GAHA->list)
						HD_Queue_Destroy_List (pe->_hoops_GAHA->list, true);

					odl->item.geometry._hoops_IGGI.point_count += pe->point_count;
					odl->item.geometry._hoops_IGGI._hoops_PHHA += pe->_hoops_PHHA;
					odl->item.geometry._hoops_IGGI.total += pe->total;
				}

				i = 0;
				j = 0;
				ei = -1;
				while (i < pe->_hoops_PHHA)
				{
					if (pe->lengths)
						len = pe->lengths[i];
					else
						len = pe->total;

					if (len < 0) {
						_hoops_ICHC (len, _hoops_RRC, 2);

						int _hoops_ISPI, _hoops_CSPI;

						start = j;
						end = j+len;

						_hoops_ISPI = j;

						while (j < end) {
							/* _hoops_GSCA _hoops_SRHR _hoops_SGHS */
							if (_hoops_PCGS && _hoops_AAAS &&
								(_hoops_PAIH.length() > (int) _hoops_PCPS - _hoops_PHHC - 4 ||
								_hoops_CHPC.length() > (int) _hoops_HCPS - _hoops_IHHC - 6))
							{
								H3DVertexBuffer _hoops_GRHS;
								H3DIndexBuffer _hoops_RRHS;

								_hoops_CGPS = h3ddata->_hoops_GSCR->_hoops_PRAS();
								_hoops_CGPS->CreateVertexBuffer(h3ddata, _hoops_PAIH.length(), _hoops_PPCP);
								_hoops_CGPS->CreateIndexBuffer(h3ddata, H3DPT_TRIANGLELIST, _hoops_CHPC.length(), _hoops_CHPC.length() / 3);

								if (!_hoops_IGPS(_hoops_CGPS, odl, _hoops_RRHA))
									goto _hoops_CIPS;

								_hoops_CGPS->LockVertexBuffer(0, 0, &_hoops_GRHS, 0);
								_hoops_CGPS->LockIndexBuffer(0, 0, &_hoops_RRHS, 0);

								COPY_MEMORY(_hoops_ICPS, _hoops_PAIH.length() * _hoops_PPCP._hoops_HGHS(), _hoops_GRHS._hoops_ARHS());
								COPY_MEMORY(_hoops_CCPS, _hoops_CHPC.length() * stride * sizeof(short), _hoops_RRHS._hoops_ARHS());

								_hoops_CGPS->UnlockVertexBuffer();
								_hoops_CGPS->UnlockIndexBuffer();

								if (odl->item.geometry.id == 0)
									odl->item.geometry.id = POOL_NEW(dc->memory_pool, H3DIndexedBufferObject_List)(dc->memory_pool);
								odl->item.geometry.id->AddFirst(_hoops_CGPS);

								_hoops_PCGS = false;
							}
							if (!_hoops_PCGS) {
								_hoops_PAIH._hoops_IRA(_hoops_ICPS, &_hoops_PPCP);
								_hoops_CHPC._hoops_IRA(format, _hoops_CCPS);

								_hoops_PCGS = true;
							}

							_hoops_CSPI = _hoops_ISPI+1;

							if (pe->_hoops_AIHA) {
								/* _hoops_HHHA _hoops_PSPI */
								_hoops_ISPI = pe->_hoops_AIHA[_hoops_ISPI];
								_hoops_CSPI = pe->_hoops_AIHA[_hoops_CSPI];
							}

							if (pe->_hoops_SPII)
								ei = pe->_hoops_SPII[j+1];
							else
								ei++;

							_hoops_IHPC(nr, _hoops_GHP, pe, pe->points, &_hoops_PAIH, &_hoops_CHPC, &_hoops_RPCP, matrix, _hoops_GPCP,
								&index, _hoops_ISPI, _hoops_ISPI, _hoops_ISPI+2, ei, false, 0);

							_hoops_PACP (nr, pe, _hoops_GHP, &_hoops_PAIH, 0, _hoops_ISPI, ei, matrix, _hoops_GPCP, &_hoops_RPCP);
							//_hoops_RGPA _hoops_HSPP _hoops_IIGR _hoops_SPS _hoops_III
							_hoops_PSPS = pe->points[_hoops_CSPI];
							if (matrix) {
								float _hoops_APCP = 1.0f / _hoops_PHCP (matrix->elements, _hoops_PSPS);
								_hoops_ASPS.x = _hoops_HPRA(matrix->elements, _hoops_PSPS) * _hoops_APCP;
								_hoops_ASPS.y = _hoops_IPRA(matrix->elements, _hoops_PSPS) * _hoops_APCP;
								_hoops_ASPS.z = _hoops_CPRA(matrix->elements, _hoops_PSPS) * _hoops_APCP;
							}
							else
								_hoops_ASPS = _hoops_PSPS;

							_hoops_PAIH._hoops_IICP(_hoops_ASPS.x, _hoops_ASPS.y, _hoops_ASPS.z, _hoops_AIPC);
							_hoops_PAIH.t(H3D_SQUARE, _hoops_HIPC);

							if (_hoops_RHHC) {
								_hoops_PAIH._hoops_IICP(_hoops_ASPS.x, _hoops_ASPS.y, _hoops_ASPS.z, _hoops_PIPC);
							}


							_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
							_hoops_PAIH._hoops_RRCI(0)._hoops_IICP(-1,0,0, _hoops_HIPC);
							_hoops_PAIH._hoops_RRCI(1)._hoops_IICP(+1,0,0, _hoops_HIPC);
							_hoops_PAIH._hoops_CPPH(2);

							_hoops_PACP (nr, pe, _hoops_GHP, &_hoops_PAIH, 0, _hoops_CSPI, ei, matrix, _hoops_GPCP, &_hoops_RPCP);
							//_hoops_RGPA _hoops_GCPC _hoops_PPSR
							_hoops_ISPS.x = 2*pe->points[_hoops_CSPI].x - pe->points[_hoops_ISPI].x;
							_hoops_ISPS.y = 2*pe->points[_hoops_CSPI].y - pe->points[_hoops_ISPI].y;
							_hoops_ISPS.z = 2*pe->points[_hoops_CSPI].z - pe->points[_hoops_ISPI].z;
							if (matrix) {
								float _hoops_APCP = 1.0f / _hoops_PHCP (matrix->elements, _hoops_ISPS);
								_hoops_HSPS.x = _hoops_HPRA(matrix->elements, _hoops_ISPS) * _hoops_APCP;
								_hoops_HSPS.y = _hoops_IPRA(matrix->elements, _hoops_ISPS) * _hoops_APCP;
								_hoops_HSPS.z = _hoops_CPRA(matrix->elements, _hoops_ISPS) * _hoops_APCP;
							}
							else
								_hoops_HSPS = _hoops_ISPS;

							_hoops_PAIH._hoops_IICP(_hoops_HSPS.x, _hoops_HSPS.y, _hoops_HSPS.z, _hoops_AIPC);
							_hoops_PAIH.t(H3D_SQUARE, _hoops_HIPC);

							if (_hoops_RHHC) {
								_hoops_PAIH._hoops_IICP(_hoops_HSPS.x, _hoops_HSPS.y, _hoops_HSPS.z, _hoops_PIPC);
							}


							_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
							_hoops_PAIH._hoops_RRCI(0)._hoops_IICP(-1,0,0, _hoops_HIPC);
							_hoops_PAIH._hoops_RRCI(1)._hoops_IICP(+1,0,0, _hoops_HIPC);
							_hoops_PAIH._hoops_CPPH(2);

							_hoops_CHPC[0] = index;
							_hoops_CHPC[1] = index + 1;
							_hoops_CHPC[2] = index + 2;
							_hoops_CHPC[3] = index + 1;
							_hoops_CHPC[4] = index + 3;
							_hoops_CHPC[5] = index + 2;
							_hoops_CHPC += 6;
							index += 4;

							_hoops_IHPC(nr, _hoops_GHP, pe, pe->points, &_hoops_PAIH, &_hoops_CHPC, &_hoops_RPCP, matrix, _hoops_GPCP,
								&index, _hoops_CSPI, _hoops_ISPI, _hoops_ISPI+2, ei, false, 0);

							j++;
							_hoops_ISPI += _hoops_RRC;
						}
						i++;
						j = _hoops_ISPI;
					}
					else {
						start = j;
						end = j+len;


						if (pe->_hoops_AIHA) {
							if (pe->points[pe->_hoops_AIHA[j]] == pe->points[pe->_hoops_AIHA[end - 1]])
								_hoops_GIPC = true;
						}
						else {
							if (pe->points[0] == pe->points[pe->point_count - 1])
								_hoops_GIPC = true;
						}


						while (j < end-1) {
							/* _hoops_GSCA _hoops_SRHR _hoops_SGHS */
							if (_hoops_PCGS && _hoops_AAAS &&
								(_hoops_PAIH.length() > (int) _hoops_PCPS - _hoops_PHHC - 4 ||
								_hoops_CHPC.length() > (int) _hoops_HCPS - _hoops_IHHC - 6))
							{
								H3DVertexBuffer _hoops_GRHS;
								H3DIndexBuffer _hoops_RRHS;

								_hoops_CGPS = h3ddata->_hoops_GSCR->_hoops_PRAS();
								_hoops_CGPS->CreateVertexBuffer(h3ddata, _hoops_PAIH.length(), _hoops_PPCP);
								_hoops_CGPS->CreateIndexBuffer(h3ddata, H3DPT_TRIANGLELIST, _hoops_CHPC.length(), _hoops_CHPC.length() / 3);

								if (!_hoops_IGPS(_hoops_CGPS, odl, _hoops_RRHA))
									goto _hoops_CIPS;

								_hoops_CGPS->LockVertexBuffer(0, 0, &_hoops_GRHS, 0);
								_hoops_CGPS->LockIndexBuffer(0, 0, &_hoops_RRHS, 0);

								COPY_MEMORY(_hoops_ICPS, _hoops_PAIH.length() * _hoops_PPCP._hoops_HGHS(), _hoops_GRHS._hoops_ARHS());
								COPY_MEMORY(_hoops_CCPS, _hoops_CHPC.length() * stride * sizeof(short), _hoops_RRHS._hoops_ARHS());

								_hoops_CGPS->UnlockVertexBuffer();
								_hoops_CGPS->UnlockIndexBuffer();

								if (odl->item.geometry.id == 0)
									odl->item.geometry.id = POOL_NEW(dc->memory_pool, H3DIndexedBufferObject_List)(dc->memory_pool);
								odl->item.geometry.id->AddFirst(_hoops_CGPS);

								_hoops_PCGS = false;
							}
							if (!_hoops_PCGS) {
								_hoops_PAIH._hoops_IRA(_hoops_ICPS, &_hoops_PPCP);
								_hoops_CHPC._hoops_IRA(format, _hoops_CCPS);

								_hoops_PCGS = true;
								index = 0;
							}

							int _hoops_ISPI = j;
							int _hoops_CSPI = j+1;

							if (pe->_hoops_AIHA) {
								/* _hoops_HHHA _hoops_PSPI */
								_hoops_ISPI = pe->_hoops_AIHA[_hoops_ISPI];
								_hoops_CSPI = pe->_hoops_AIHA[_hoops_CSPI];
							}

							if (pe->_hoops_SPII)
								ei = pe->_hoops_SPII[j+1];
							else
								ei++;

							if (j == start) {
								_hoops_IHPC(nr, _hoops_GHP, pe, pe->points, &_hoops_PAIH, &_hoops_CHPC, &_hoops_RPCP, matrix, _hoops_GPCP,
									&index, j, start, end, ei, _hoops_GIPC, false);
							}

							_hoops_PACP (nr, pe, _hoops_GHP, &_hoops_PAIH, 0, _hoops_ISPI, ei, matrix, _hoops_GPCP, &_hoops_RPCP);
							//_hoops_RGPA _hoops_HSPP _hoops_IIGR _hoops_SPS _hoops_III
							_hoops_PSPS = pe->points[_hoops_CSPI];
							if (matrix) {
								float _hoops_APCP = 1.0f / _hoops_PHCP (matrix->elements, _hoops_PSPS);
								_hoops_ASPS.x = _hoops_HPRA(matrix->elements, _hoops_PSPS) * _hoops_APCP;
								_hoops_ASPS.y = _hoops_IPRA(matrix->elements, _hoops_PSPS) * _hoops_APCP;
								_hoops_ASPS.z = _hoops_CPRA(matrix->elements, _hoops_PSPS) * _hoops_APCP;
							}
							else
								_hoops_ASPS = _hoops_PSPS;

							_hoops_PAIH._hoops_IICP(_hoops_ASPS.x, _hoops_ASPS.y, _hoops_ASPS.z, _hoops_AIPC);
							_hoops_PAIH.t(H3D_SQUARE, _hoops_HIPC);

							if (_hoops_RHHC) {
								_hoops_PAIH._hoops_IICP(_hoops_ASPS.x, _hoops_ASPS.y, _hoops_ASPS.z, _hoops_PIPC);
								_hoops_PAIH.t(H3D_MITER, _hoops_HIPC);
							}

							_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
							_hoops_PAIH._hoops_RRCI(0)._hoops_IICP(-1,0,0, _hoops_HIPC);
							_hoops_PAIH._hoops_RRCI(1)._hoops_IICP(+1,0,0, _hoops_HIPC);
							_hoops_PAIH._hoops_CPPH(2);

							_hoops_PACP (nr, pe, _hoops_GHP, &_hoops_PAIH, 0, _hoops_CSPI, ei, matrix, _hoops_GPCP, &_hoops_RPCP);

							//_hoops_RGPA _hoops_GCPC _hoops_PPSR
							_hoops_ISPS.x = 2*pe->points[_hoops_CSPI].x - pe->points[_hoops_ISPI].x;
							_hoops_ISPS.y = 2*pe->points[_hoops_CSPI].y - pe->points[_hoops_ISPI].y;
							_hoops_ISPS.z = 2*pe->points[_hoops_CSPI].z - pe->points[_hoops_ISPI].z;
							if (matrix) {
								float _hoops_APCP = 1.0f / _hoops_PHCP (matrix->elements, _hoops_ISPS);
								_hoops_HSPS.x = _hoops_HPRA(matrix->elements, _hoops_ISPS) * _hoops_APCP;
								_hoops_HSPS.y = _hoops_IPRA(matrix->elements, _hoops_ISPS) * _hoops_APCP;
								_hoops_HSPS.z = _hoops_CPRA(matrix->elements, _hoops_ISPS) * _hoops_APCP;
							}
							else
								_hoops_HSPS = _hoops_ISPS;

							_hoops_PAIH._hoops_IICP(_hoops_HSPS.x, _hoops_HSPS.y, _hoops_HSPS.z, _hoops_AIPC);
							_hoops_PAIH.t(H3D_SQUARE, _hoops_HIPC);

							if (_hoops_RHHC) {
								_hoops_PAIH._hoops_IICP(_hoops_HSPS.x, _hoops_HSPS.y, _hoops_HSPS.z, _hoops_PIPC);
								_hoops_PAIH.t(H3D_MITER, _hoops_HIPC);
							}

							_hoops_PAIH._hoops_RRCI(0)._hoops_AHIH(1);
							_hoops_PAIH._hoops_RRCI(0)._hoops_IICP(-1,0,0, _hoops_HIPC);
							_hoops_PAIH._hoops_RRCI(1)._hoops_IICP(+1,0,0, _hoops_HIPC);
							_hoops_PAIH._hoops_CPPH(2);

							_hoops_CHPC[0] = index;
							_hoops_CHPC[1] = index + 1;
							_hoops_CHPC[2] = index + 2;
							_hoops_CHPC[3] = index + 1;
							_hoops_CHPC[4] = index + 3;
							_hoops_CHPC[5] = index + 2;
							_hoops_CHPC += 6;
							index += 4;

							_hoops_IHPC(nr, _hoops_GHP, pe, pe->points, &_hoops_PAIH, &_hoops_CHPC, &_hoops_RPCP, matrix, _hoops_GPCP,
								&index, j+1, start, end, ei, _hoops_GIPC, false);

							j++;
						}
					}
					i++;
					j++;
				}

				if (!_hoops_RRHA)
					break;
			}

			if (_hoops_PCGS)
			{
				H3DVertexBuffer _hoops_GRHS;
				H3DIndexBuffer _hoops_RRHS;


				_hoops_CGPS = h3ddata->_hoops_GSCR->_hoops_PRAS();
				_hoops_CGPS->CreateVertexBuffer(h3ddata, _hoops_PAIH.length(), _hoops_PPCP);
				_hoops_CGPS->CreateIndexBuffer(h3ddata, H3DPT_TRIANGLELIST, _hoops_CHPC.length(), _hoops_CHPC.length() / 3);

				if (!_hoops_IGPS(_hoops_CGPS, odl, _hoops_RRHA))
					goto _hoops_CIPS;

				_hoops_CGPS->LockVertexBuffer(0, 0, &_hoops_GRHS, 0);
				_hoops_CGPS->LockIndexBuffer(0, 0, &_hoops_RRHS, 0);

				COPY_MEMORY(_hoops_ICPS, _hoops_PAIH.length() * _hoops_PPCP._hoops_HGHS(), _hoops_GRHS._hoops_ARHS());
				COPY_MEMORY(_hoops_CCPS, _hoops_CHPC.length() * stride * sizeof(short), _hoops_RRHS._hoops_ARHS());

				_hoops_CGPS->UnlockVertexBuffer();
				_hoops_CGPS->UnlockIndexBuffer();

				if (odl->item.geometry.id == 0)
					odl->item.geometry.id = POOL_NEW(dc->memory_pool, H3DIndexedBufferObject_List)(dc->memory_pool);
				odl->item.geometry.id->AddFirst(_hoops_CGPS);

				_hoops_PCGS = false;
			}


			odl->_hoops_RAHA = _hoops_AHA(pe, (_hoops_GPCP!=null));

			odl->item.geometry._hoops_SGAS = H3D_OBJ_IndexBuffer;
			odl->item.geometry._hoops_GSAI = pe->_hoops_GSAI;
			if (dl)
				dl->_hoops_GSAI = pe->_hoops_GSAI;
			odl->item.geometry._hoops_SRHA = pe->_hoops_SRHA;
			odl->item.geometry._hoops_CARI = pe->_hoops_CARI;
			int _hoops_CHRC;
			_hoops_SII(_hoops_PHIA, 0, &_hoops_RPCP, null, null, &_hoops_CHRC);
			odl->item.geometry._hoops_HSRC = _hoops_IGIA(matr, _hoops_CHRC, 0);
			if (h3ddata->_hoops_AIC)
				odl->item.geometry._hoops_CARI |= _hoops_HRRI;
			odl->item.geometry._hoops_IRRI = pe->_hoops_PPGI.flags;
			odl->_hoops_PPCP = _hoops_PPCP;
		}
		else {

			i = j = 0;
			int _hoops_ISIC = 0;
			int _hoops_GHAS = 0;
			int _hoops_PRHS, _hoops_HRHS = 0;

			_hoops_PCPS = point_count;
			_hoops_HCPS = _hoops_CPHA;

			if (_hoops_PCPS > h3ddata->_hoops_ACGH._hoops_CGGI ||
				_hoops_HCPS > h3ddata->_hoops_ACGH._hoops_GRGI * 2)
			{
				// _hoops_HGI _hoops_IRHS _hoops_IS _hoops_CRHS _hoops_IIHA _hoops_GPP _hoops_RH _hoops_SRHR _hoops_IAHA...
				_hoops_PCPS = h3ddata->_hoops_ACGH._hoops_CGGI;
				_hoops_HCPS = h3ddata->_hoops_ACGH._hoops_GRGI * 2;
				_hoops_AAAS = true;
			}


			_hoops_SCPS = _hoops_PCPS * _hoops_PPCP._hoops_HGHS(false);
			POOL_ALLOC_ARRAY_CACHED (_hoops_ICPS, _hoops_SCPS, float, dc->memory_pool);

			_hoops_GSPS = _hoops_HCPS;
			POOL_ALLOC_ARRAY_CACHED (_hoops_CCPS, _hoops_GSPS, short, dc->memory_pool);

			_hoops_PAIH._hoops_IRA(_hoops_ICPS, &_hoops_PPCP);
			_hoops_CHPC._hoops_IRA(H3DFMT_INDEX16, _hoops_CCPS);

			if (_hoops_RRHA) {
				_hoops_RSPS = _hoops_SRHS (dc->memory_pool, null, _hoops_RRHA, _hoops_AAPS);
				if (_hoops_RRHA->_hoops_CRHA->Count() > 1) {
					ALLOC_ARRAY(_hoops_PAPS, _hoops_RRHA->_hoops_CRHA->Count(), int);
				}
				_hoops_RRHA->_hoops_CRHA->ResetCursor();
				pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
				pe = (Polyedge const *) pair->geo;
				if (pair->_hoops_CPAI)
					matrix = &pair->_hoops_CPAI->matrix;
				else
					matrix = null;
				_hoops_GPCP = _hoops_CCAI (pair->color, Color_EDGE);
			}
			else
				_hoops_RSPS = _hoops_SRHS (dc->memory_pool, (_hoops_GAHS *)pe, null, _hoops_AAPS);


			/* _hoops_PHIR _hoops_RH _hoops_GPHA _hoops_PPR _hoops_CIHA _hoops_PSCA */
			if (_hoops_APHA == H3D_Partially_Shared_Vertices) {

				// _hoops_PSRC _hoops_RHIR _hoops_AHHA _hoops_GIAA _hoops_RH _hoops_SCGI
				for (_hoops_PRHS = 0; ; _hoops_PRHS++) {

					int _hoops_ISPI, ei;
					//_hoops_CIPH _hoops_RH _hoops_GPHA _hoops_PPR _hoops_CIHA _hoops_SRHR _hoops_GIAA _hoops_RH _hoops_PSHR _hoops_HAPR
					j = 0;
					ei = -1;
					_hoops_GHAS = 0;

					if (_hoops_PAPS)
						_hoops_PAPS[_hoops_PRHS] = _hoops_CHPC.length();

					for (i = 0; i < pe->_hoops_PHHA; i++) {
						if (pe->lengths)
							len = pe->lengths[i];
						else
							len = pe->total;
						ASSERT (len > 0); //_hoops_RPP _hoops_III _hoops_SGHC, _hoops_SR _hoops_CGH _hoops_SHH _hoops_GGR _hoops_RAHS _hoops_AGIR
						start = j;
						end = j + len;
						while (j < end) {

							// _hoops_ISPR "_hoops_IHSA _hoops_AAHS" _hoops_HPAC
							if (_hoops_PCGS && _hoops_AAAS &&
								((unsigned int)_hoops_PAIH.length() >= _hoops_PCPS ||
								(unsigned int)_hoops_CHPC.length() >= _hoops_HCPS))
							{
								_hoops_CGPS = h3ddata->_hoops_GSCR->_hoops_PRAS();
								_hoops_CGPS->CreateVertexBuffer(h3ddata, _hoops_PAIH.length(), _hoops_PPCP);
								_hoops_CGPS->CreateIndexBuffer(h3ddata, H3DPT_LINELIST, _hoops_CHPC.length(), _hoops_CHPC.length() / 2);

								if (!_hoops_IGPS(_hoops_CGPS, odl, _hoops_RRHA))
									goto _hoops_CIPS;

								_hoops_CGPS->_hoops_PAHS(_hoops_ICPS, _hoops_PAIH.length() * _hoops_PPCP._hoops_HGHS());
								_hoops_CGPS->_hoops_HAHS(_hoops_CCPS, _hoops_CHPC.length() * sizeof(short));

								if (odl->item.geometry.id == 0)
									odl->item.geometry.id = POOL_NEW(dc->memory_pool, H3DIndexedBufferObject_List)(dc->memory_pool);
								odl->item.geometry.id->AddFirst(_hoops_CGPS);

								if (_hoops_RSPS) {
									_hoops_CGPS->_hoops_IAHS = _hoops_RSPS;
									_hoops_CAHS (_hoops_RSPS);
								}
								_hoops_CGPS->_hoops_SAHS			= _hoops_PRHS - _hoops_HRHS + 1;
								_hoops_CGPS->_hoops_GPHS			= _hoops_HRHS;
								if (_hoops_HAPS > 1) {
									ALLOC_ARRAY(_hoops_CGPS->_hoops_RPHS, _hoops_CGPS->_hoops_SAHS, int);
									_hoops_AIGA(_hoops_PAPS, _hoops_CGPS->_hoops_SAHS, int, _hoops_CGPS->_hoops_RPHS);
								}
								else
									_hoops_CGPS->_hoops_RPHS = null;

								_hoops_PCGS = false;
							}
							if (!_hoops_PCGS) {
								_hoops_PAIH._hoops_IRA(_hoops_ICPS, &_hoops_PPCP);
								_hoops_CHPC._hoops_IRA(H3DFMT_INDEX16, _hoops_CCPS);

								// _hoops_RPP _hoops_SR _hoops_AAPR _hoops_GGR _hoops_RH _hoops_IRGP _hoops_IIGR _hoops_IRS _hoops_CGGR _hoops_CGPR _hoops_SR _hoops_HHGP, _hoops_PSCR
								// _hoops_SR _hoops_RRP _hoops_IS _hoops_APHS _hoops_RH _hoops_PGHC _hoops_GPHA
								if (j > start && j < end) {
									j--;
									ei--;
								}

								_hoops_GHAS = 0;
								_hoops_ISIC = 0;
								_hoops_HRHS = _hoops_PRHS;

								_hoops_PCGS = true;
							}


							if (pe->_hoops_AIHA)
								_hoops_ISPI = pe->_hoops_AIHA[j];
							else
								_hoops_ISPI = j;
							j++;
							if (pe->_hoops_SPII) {
								if (j < end)
									ei = pe->_hoops_SPII[j];
							}
							else if(ei+1 < pe->_hoops_SPHA)
								ei++;

							_hoops_PACP (nr, pe, _hoops_GHP, &_hoops_PAIH, 0, _hoops_ISPI, ei, matrix, _hoops_GPCP, &_hoops_RPCP);
							_hoops_PAIH._hoops_CPPH();
							if (_hoops_GHAS > 0 && start+1 < j && j <= end) {
								_hoops_CHPC[0] = _hoops_ISIC + _hoops_GHAS - 1;
								++_hoops_CHPC;
								_hoops_CHPC[0] = _hoops_ISIC + _hoops_GHAS;
								++_hoops_CHPC;
							}
							_hoops_GHAS++;
						}
						ei--;
					}
					_hoops_ISIC += _hoops_GHAS;

					if (_hoops_RRHA) {
						_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
						pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
						if (!pair)
							break;
						pe = (Polyedge const *) pair->geo;
						if (pair->_hoops_CPAI)
							matrix = &pair->_hoops_CPAI->matrix;
						else
							matrix = null;
						_hoops_GPCP = _hoops_CCAI (pair->color, Color_EDGE);
						ei = -1;

						// _hoops_IGHS _hoops_CAGH _hoops_PAPA _hoops_CGHS, _hoops_HIS _hoops_HRCI _hoops_GII _hoops_CPAP _hoops_CGHS
						if (pe->_hoops_GAHA && pe->_hoops_GAHA->list)
							HD_Queue_Destroy_List (pe->_hoops_GAHA->list, true);

						odl->item.geometry._hoops_IGGI.point_count += pe->point_count;
						odl->item.geometry._hoops_IGGI._hoops_PHHA += pe->_hoops_PHHA;
						odl->item.geometry._hoops_IGGI.total += pe->total;
					}
					else
						break;
				}

				if (_hoops_PCGS)
				{
					_hoops_CGPS = h3ddata->_hoops_GSCR->_hoops_PRAS();
					_hoops_CGPS->CreateVertexBuffer(h3ddata, _hoops_PAIH.length(), _hoops_PPCP);
					_hoops_CGPS->CreateIndexBuffer(h3ddata, H3DPT_LINELIST, _hoops_CHPC.length(), _hoops_CHPC.length() / 2);

					if (!_hoops_IGPS(_hoops_CGPS, odl, _hoops_RRHA))
						goto _hoops_CIPS;

					_hoops_CGPS->_hoops_PAHS(_hoops_ICPS, _hoops_PAIH.length() * _hoops_PPCP._hoops_HGHS());
					_hoops_CGPS->_hoops_HAHS(_hoops_CCPS, _hoops_CHPC.length() * sizeof(short));

					// _hoops_ARP _hoops_GH _hoops_PPHS'_hoops_GRI _hoops_IASC _hoops_HPHS
					if (_hoops_RSPS) {
						_hoops_CGPS->_hoops_IAHS = _hoops_RSPS;
						_hoops_CAHS (_hoops_RSPS);
					}
					_hoops_CGPS->_hoops_SAHS			= _hoops_PRHS - _hoops_HRHS + 1;
					_hoops_CGPS->_hoops_GPHS			= _hoops_HRHS;
					if (_hoops_HAPS > 1) {
						ALLOC_ARRAY(_hoops_CGPS->_hoops_RPHS, _hoops_CGPS->_hoops_SAHS, int);
						_hoops_AIGA(_hoops_PAPS, _hoops_CGPS->_hoops_SAHS, int, _hoops_CGPS->_hoops_RPHS);
					}
					else
						_hoops_CGPS->_hoops_RPHS = null;

					if (odl->item.geometry.id == 0)
						odl->item.geometry.id = POOL_NEW(dc->memory_pool, H3DIndexedBufferObject_List)(dc->memory_pool);
					odl->item.geometry.id->AddFirst(_hoops_CGPS);
					_hoops_PCGS = false;
				}

			}
			else if (_hoops_APHA == H3D_Unshared_Vertices) {
				int _hoops_ISPI, _hoops_CSPI, ei;

				// _hoops_PSRC _hoops_RHIR _hoops_AHHA _hoops_GIAA _hoops_RH _hoops_SCGI
				for (_hoops_PRHS = 0; ; _hoops_PRHS++) {
					j = 0;
					ei = -1;
					_hoops_GHAS = 0;

					if (_hoops_PAPS)
						_hoops_PAPS[_hoops_PRHS] = _hoops_CHPC.length();

					for (i = 0; i < pe->_hoops_PHHA; i++) {
						if (pe->lengths)
							len = pe->lengths[i];
						else
							len = pe->total;
						ASSERT (len > 0); //_hoops_RPP _hoops_III _hoops_SGHC, _hoops_SR _hoops_CGH _hoops_SHH _hoops_GGR _hoops_RAHS _hoops_AGIR
						end = j + len;
						while (j < end-1) {
							// _hoops_ISPR "_hoops_IHSA _hoops_AAHS" _hoops_HPAC
							if (_hoops_PCGS && _hoops_AAAS &&
								((unsigned int) _hoops_PAIH.length() >= _hoops_PCPS - 2 ||
								(unsigned int) _hoops_CHPC.length() >= _hoops_HCPS - 2))
							{
								_hoops_CGPS = h3ddata->_hoops_GSCR->_hoops_PRAS();
								_hoops_CGPS->CreateVertexBuffer(h3ddata, _hoops_PAIH.length(), _hoops_PPCP);
								_hoops_CGPS->CreateIndexBuffer(h3ddata, H3DPT_LINELIST, _hoops_CHPC.length(), _hoops_CHPC.length() / 2);

								if (!_hoops_IGPS(_hoops_CGPS, odl, _hoops_RRHA))
									goto _hoops_CIPS;

								_hoops_CGPS->_hoops_PAHS(_hoops_ICPS, _hoops_PAIH.length() * _hoops_PPCP._hoops_HGHS());
								_hoops_CGPS->_hoops_HAHS(_hoops_CCPS, _hoops_CHPC.length() * sizeof(short));

								if (_hoops_RSPS) {
									_hoops_CGPS->_hoops_IAHS = _hoops_RSPS;
									_hoops_CAHS (_hoops_RSPS);
								}
								_hoops_CGPS->_hoops_SAHS			= _hoops_PRHS - _hoops_HRHS + 1;
								_hoops_CGPS->_hoops_GPHS			= _hoops_HRHS;
								if (_hoops_HAPS > 1) {
									ALLOC_ARRAY(_hoops_CGPS->_hoops_RPHS, _hoops_CGPS->_hoops_SAHS, int);
									_hoops_AIGA(_hoops_PAPS, _hoops_CGPS->_hoops_SAHS, int, _hoops_CGPS->_hoops_RPHS);
								}
								else
									_hoops_CGPS->_hoops_RPHS = null;

								if (odl->item.geometry.id == 0)
									odl->item.geometry.id = POOL_NEW(dc->memory_pool, H3DIndexedBufferObject_List)(dc->memory_pool);
								odl->item.geometry.id->AddFirst(_hoops_CGPS);
								_hoops_PCGS = false;
							}
							if (!_hoops_PCGS) {
								_hoops_PAIH._hoops_IRA(_hoops_ICPS, &_hoops_PPCP);
								_hoops_CHPC._hoops_IRA(H3DFMT_INDEX16, _hoops_CCPS);

								_hoops_GHAS = 0;
								_hoops_ISIC = 0;
								_hoops_HRHS = _hoops_PRHS;

								_hoops_PCGS = true;
							}

							if (pe->_hoops_AIHA) {
								_hoops_ISPI = pe->_hoops_AIHA[j];
								_hoops_CSPI = pe->_hoops_AIHA[j+1];
							}
							else {
								_hoops_ISPI = j;
								_hoops_CSPI = j+1;
							}
							j++;
							if (pe->_hoops_SPII)
								ei = pe->_hoops_SPII[j];
							else
								ei++;

							_hoops_PACP (nr, pe, _hoops_GHP, &_hoops_PAIH, 0, _hoops_ISPI, ei, matrix, _hoops_GPCP, &_hoops_RPCP);
							_hoops_PAIH._hoops_CPPH();
							_hoops_CHPC = _hoops_ISIC + _hoops_GHAS; ++_hoops_CHPC;
							_hoops_GHAS++;

							_hoops_PACP (nr, pe, _hoops_GHP, &_hoops_PAIH, 0, _hoops_CSPI, ei, matrix, _hoops_GPCP, &_hoops_RPCP);
							_hoops_PAIH._hoops_CPPH();
							_hoops_CHPC = _hoops_ISIC + _hoops_GHAS; ++_hoops_CHPC;
							_hoops_GHAS++;
						}
						j++;
					}
					_hoops_ISIC += _hoops_GHAS;

					if (_hoops_RRHA) {
						_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
						pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
						if (!pair)
							break;
						pe = (Polyedge const *) pair->geo;
						if (pair->_hoops_CPAI)
							matrix = &pair->_hoops_CPAI->matrix;
						else
							matrix = null;
						_hoops_GPCP = _hoops_CCAI (pair->color, Color_EDGE);

						// _hoops_IGHS _hoops_CAGH _hoops_PAPA _hoops_CGHS, _hoops_HIS _hoops_HRCI _hoops_GII _hoops_CPAP _hoops_CGHS
						if (pe->_hoops_GAHA && pe->_hoops_GAHA->list)
							HD_Queue_Destroy_List (pe->_hoops_GAHA->list, true);

						odl->item.geometry._hoops_IGGI.point_count += pe->point_count;
						odl->item.geometry._hoops_IGGI._hoops_PHHA += pe->_hoops_PHHA;
						odl->item.geometry._hoops_IGGI.total += pe->total;
					}
					else
						break;
				}

				if (_hoops_PCGS)
				{
					_hoops_CGPS = h3ddata->_hoops_GSCR->_hoops_PRAS();
					_hoops_CGPS->CreateVertexBuffer(h3ddata, _hoops_PAIH.length(), _hoops_PPCP);
					_hoops_CGPS->CreateIndexBuffer(h3ddata, H3DPT_LINELIST, _hoops_CHPC.length(), _hoops_CHPC.length() / 2);

					if (!_hoops_IGPS(_hoops_CGPS, odl, _hoops_RRHA))
						goto _hoops_CIPS;

					_hoops_CGPS->_hoops_PAHS(_hoops_ICPS, _hoops_PAIH.length() * _hoops_PPCP._hoops_HGHS());
					_hoops_CGPS->_hoops_HAHS(_hoops_CCPS, _hoops_CHPC.length() * sizeof(short));

					// _hoops_ARP _hoops_GH _hoops_PPHS'_hoops_GRI _hoops_IASC _hoops_HPHS
					if (_hoops_RSPS) {
						_hoops_CGPS->_hoops_IAHS = _hoops_RSPS;
						_hoops_CAHS (_hoops_RSPS);
					}
					_hoops_CGPS->_hoops_SAHS			= _hoops_PRHS - _hoops_HRHS + 1;
					_hoops_CGPS->_hoops_GPHS			= _hoops_HRHS;
					if (_hoops_HAPS > 1) {
						ALLOC_ARRAY(_hoops_CGPS->_hoops_RPHS, _hoops_CGPS->_hoops_SAHS, int);
						_hoops_AIGA(_hoops_PAPS, _hoops_CGPS->_hoops_SAHS, int, _hoops_CGPS->_hoops_RPHS);
					}
					else
						_hoops_CGPS->_hoops_RPHS = null;

					if (odl->item.geometry.id == 0)
						odl->item.geometry.id = POOL_NEW(dc->memory_pool, H3DIndexedBufferObject_List)(dc->memory_pool);
					odl->item.geometry.id->AddFirst(_hoops_CGPS);
					_hoops_PCGS = false;
				}
			}
			else {
				int _hoops_ISPI, _hoops_CSPI;
				int _hoops_RHAS = -1, _hoops_AHAS = -1;
				short *_hoops_PHAS;

				ASSERT (_hoops_APHA == H3D_Shared_Vertices);

				// _hoops_PSRC _hoops_RHIR _hoops_AHHA _hoops_GIAA _hoops_RH _hoops_SCGI
				for (_hoops_PRHS = 0; ; _hoops_PRHS++) {
					j = 0;

					_hoops_PHAS = _hoops_AIAS(h3ddata, pe->point_count);
					if (_hoops_PHAS)
						SET_MEMORY(_hoops_PHAS, pe->point_count*sizeof(short), -1);

					if (_hoops_PAPS)
						_hoops_PAPS[_hoops_PRHS] = _hoops_CHPC.length();

					for (i = 0; i < pe->_hoops_PHHA; i++)
					{
						if (pe->lengths)
							len = pe->lengths[i];
						else
							len = pe->point_count;
						if (len < 0)
							_hoops_ICHC (len, _hoops_RRC, 2);

						start = j;
						end = j+len*_hoops_RRC;

						while (j < end - 1) {
							// _hoops_ISPR "_hoops_IHSA _hoops_AAHS" _hoops_HPAC
							if (_hoops_PCGS && _hoops_AAAS &&
								((unsigned int) _hoops_PAIH.length() >= _hoops_PCPS - 2 ||
								(unsigned int) _hoops_CHPC.length() >= _hoops_HCPS - 2))
							{
								_hoops_CGPS = h3ddata->_hoops_GSCR->_hoops_PRAS();
								_hoops_CGPS->CreateVertexBuffer(h3ddata, _hoops_PAIH.length(), _hoops_PPCP);
								_hoops_CGPS->CreateIndexBuffer(h3ddata, H3DPT_LINELIST, _hoops_CHPC.length(), _hoops_CHPC.length() / 2);

								if (!_hoops_IGPS(_hoops_CGPS, odl, _hoops_RRHA))
									goto _hoops_CIPS;

								_hoops_CGPS->_hoops_PAHS(_hoops_ICPS, _hoops_PAIH.length() * _hoops_PPCP._hoops_HGHS());
								_hoops_CGPS->_hoops_HAHS(_hoops_CCPS, _hoops_CHPC.length() * sizeof(short));

								if (_hoops_RSPS) {
									_hoops_CGPS->_hoops_IAHS = _hoops_RSPS;
									_hoops_CAHS (_hoops_RSPS);
								}
								_hoops_CGPS->_hoops_SAHS			= _hoops_PRHS - _hoops_HRHS + 1;
								_hoops_CGPS->_hoops_GPHS			= _hoops_HRHS;
								if (_hoops_HAPS > 1) {
									ALLOC_ARRAY(_hoops_CGPS->_hoops_RPHS, _hoops_CGPS->_hoops_SAHS, int);
									_hoops_AIGA(_hoops_PAPS, _hoops_CGPS->_hoops_SAHS, int, _hoops_CGPS->_hoops_RPHS);
								}
								else
									_hoops_CGPS->_hoops_RPHS = null;

								if (odl->item.geometry.id == 0)
									odl->item.geometry.id = POOL_NEW(dc->memory_pool, H3DIndexedBufferObject_List)(dc->memory_pool);
								odl->item.geometry.id->AddFirst(_hoops_CGPS);
								_hoops_PCGS = false;
							}
							if (!_hoops_PCGS) {
								_hoops_PAIH._hoops_IRA(_hoops_ICPS, &_hoops_PPCP);
								_hoops_CHPC._hoops_IRA(H3DFMT_INDEX16, _hoops_CCPS);

								SET_MEMORY(_hoops_PHAS, pe->point_count*sizeof(short), -1);

								// _hoops_RPP _hoops_SR _hoops_AAPR _hoops_GGR _hoops_RH _hoops_IRGP _hoops_IIGR _hoops_IRS _hoops_CGGR _hoops_CGPR _hoops_SR _hoops_HHGP, _hoops_PSCR
								// _hoops_SR _hoops_RRP _hoops_IS _hoops_APHS _hoops_RH _hoops_PGHC _hoops_GPHA
								if (j > start && j < end) {
									j--;
								}

								_hoops_GHAS = 0;
								_hoops_HRHS = _hoops_PRHS;

								_hoops_PCGS = true;
							}


							if (pe->_hoops_AIHA) {
								_hoops_ISPI = pe->_hoops_AIHA[j];
								_hoops_CSPI = pe->_hoops_AIHA[j+1];
							}
							else {
								_hoops_ISPI = j;
								_hoops_CSPI = j+1;
							}
							j+=_hoops_RRC;

							_hoops_RHAS = _hoops_PHAS[_hoops_ISPI];
							if (_hoops_RHAS < 0) {
								_hoops_RHAS = _hoops_PHAS[_hoops_ISPI] = _hoops_GHAS++;
								_hoops_PACP (nr, pe, _hoops_GHP, &_hoops_PAIH, 0, _hoops_ISPI, 0, matrix, _hoops_GPCP, &_hoops_RPCP);
								_hoops_PAIH._hoops_CPPH();
							}
							_hoops_AHAS = _hoops_PHAS[_hoops_CSPI];
							if (_hoops_AHAS < 0) {
								_hoops_AHAS = _hoops_PHAS[_hoops_CSPI] = _hoops_GHAS++;
								_hoops_PACP (nr, pe, _hoops_GHP, &_hoops_PAIH, 0, _hoops_CSPI, 0, matrix, _hoops_GPCP, &_hoops_RPCP);
								_hoops_PAIH._hoops_CPPH();
							}


							// _hoops_CIPH _hoops_CIHA _hoops_PPR _hoops_GPHA _hoops_PSCA
							_hoops_CHPC = _hoops_RHAS; ++_hoops_CHPC;
							_hoops_CHPC = _hoops_AHAS; ++_hoops_CHPC;
						}


						j+= (2-_hoops_RRC);
					}

					if (_hoops_RRHA) {
						_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
						pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
						if (!pair)
							break;
						pe = (Polyedge const *) pair->geo;
						if (pair->_hoops_CPAI)
							matrix = &pair->_hoops_CPAI->matrix;
						else
							matrix = null;
						_hoops_GPCP = _hoops_CCAI (pair->color, Color_EDGE);

						// _hoops_IGHS _hoops_CAGH _hoops_PAPA _hoops_CGHS, _hoops_HIS _hoops_HRCI _hoops_GII _hoops_CPAP _hoops_CGHS
						if (pe->_hoops_GAHA && pe->_hoops_GAHA->list)
							HD_Queue_Destroy_List (pe->_hoops_GAHA->list, true);

						odl->item.geometry._hoops_IGGI.point_count += pe->point_count;
						odl->item.geometry._hoops_IGGI._hoops_PHHA += pe->_hoops_PHHA;
						odl->item.geometry._hoops_IGGI.total += pe->total;
					}
					else
						break;
				}

				if (_hoops_PCGS)
				{
					_hoops_CGPS = h3ddata->_hoops_GSCR->_hoops_PRAS();
					_hoops_CGPS->CreateVertexBuffer(h3ddata, _hoops_PAIH.length(), _hoops_PPCP);
					_hoops_CGPS->CreateIndexBuffer(h3ddata, H3DPT_LINELIST, _hoops_CHPC.length(), _hoops_CHPC.length() / 2);

					if (!_hoops_IGPS(_hoops_CGPS, odl, _hoops_RRHA))
						goto _hoops_CIPS;

					_hoops_CGPS->_hoops_PAHS(_hoops_ICPS, _hoops_PAIH.length() * _hoops_PPCP._hoops_HGHS());
					_hoops_CGPS->_hoops_HAHS(_hoops_CCPS, _hoops_CHPC.length() * sizeof(short));

					// _hoops_ARP _hoops_GH _hoops_PPHS'_hoops_GRI _hoops_IASC _hoops_HPHS
					if (_hoops_RSPS) {
						_hoops_CGPS->_hoops_IAHS = _hoops_RSPS;
						_hoops_CAHS (_hoops_RSPS);
					}
					_hoops_CGPS->_hoops_SAHS			= _hoops_PRHS - _hoops_HRHS + 1;
					_hoops_CGPS->_hoops_GPHS			= _hoops_HRHS;
					if (_hoops_HAPS > 1) {
						ALLOC_ARRAY(_hoops_CGPS->_hoops_RPHS, _hoops_CGPS->_hoops_SAHS, int);
						_hoops_AIGA(_hoops_PAPS, _hoops_CGPS->_hoops_SAHS, int, _hoops_CGPS->_hoops_RPHS);
					}
					else
						_hoops_CGPS->_hoops_RPHS = null;

					if (odl->item.geometry.id == 0)
						odl->item.geometry.id = POOL_NEW(dc->memory_pool, H3DIndexedBufferObject_List)(dc->memory_pool);
					odl->item.geometry.id->AddFirst(_hoops_CGPS);
					_hoops_PCGS = false;
				}
			}
		}

		if (_hoops_ICPS)
			FREE_ARRAY (_hoops_ICPS, _hoops_SCPS, float);
		if (_hoops_CCPS)
			FREE_ARRAY (_hoops_CCPS, _hoops_GSPS, short);

		odl->_hoops_RAHA = _hoops_AHA(pe, (_hoops_GPCP!=null));

		odl->item.geometry._hoops_SGAS = H3D_OBJ_IndexBuffer;
		odl->item.geometry._hoops_GSAI = pe->_hoops_GSAI;
		if (dl)
			dl->_hoops_GSAI = pe->_hoops_GSAI;
		odl->item.geometry._hoops_SRHA = pe->_hoops_SRHA;
		if (matr->_hoops_ARIR && 
			BIT (nr->_hoops_IRR->_hoops_CSA, (_hoops_RGAC & ~_hoops_AHGI))) {
			int _hoops_CHRC;
			odl->item.geometry._hoops_SRHA |= DL_TEXTURING;
			_hoops_SII(_hoops_PHIA, 0, &_hoops_RPCP, null, null, &_hoops_CHRC);
			odl->item.geometry._hoops_HSRC = _hoops_IGIA(matr, _hoops_CHRC, 0);
		}
		odl->item.geometry._hoops_CARI = pe->_hoops_CARI;
		if (h3ddata->_hoops_AIC)
			odl->item.geometry._hoops_CARI |= _hoops_HRRI;
		odl->item.geometry._hoops_IRRI = pe->_hoops_PPGI.flags;
		odl->item.geometry._hoops_IGGI.point_count = pe->point_count;
		odl->item.geometry._hoops_IGGI.total = pe->total;
		odl->item.geometry._hoops_IGGI._hoops_PHHA = pe->_hoops_PHHA;
		odl->_hoops_PPCP = _hoops_PPCP;

		// _hoops_GISP _hoops_CGHI _hoops_AIR _hoops_IIGR _hoops_GRR _hoops_CGGR _hoops_RPP _hoops_RGHP
		if (BIT(pe->_hoops_CARI, _hoops_IPHS)) {
			// _hoops_ARPR _hoops_GPHA _hoops_SRHR
			_hoops_CGPS = h3ddata->_hoops_GSCR->_hoops_PRAS();
			if (_hoops_CGPS && 
				_hoops_CGPS->CreateVertexBuffer(h3ddata,pe->_hoops_PHHA,_hoops_PPCP) &&
				_hoops_CGPS->CreateIndexBuffer(h3ddata,H3DPT_POINTLIST,pe->_hoops_PHHA,pe->_hoops_PHHA)) 
			{
				_hoops_CGPS->LockIndexBuffer(0, 0, &_hoops_CHPC, 0);
				_hoops_CGPS->LockVertexBuffer(0, 0, &_hoops_PAIH, 0);
				{
					int ei = -1;
					int index = -1;
					for (i = 0; i < pe->_hoops_PHHA; i++) {
						index += pe->lengths[i];
						if (pe->_hoops_SPII)
							ei = pe->_hoops_SPII[j];
						else
							ei++;

						_hoops_PACP(nr, pe, _hoops_GHP, &_hoops_PAIH, 0, pe->_hoops_AIHA[index], ei, matrix, _hoops_GPCP, &_hoops_RPCP);
						_hoops_CHPC[i] = i;
						_hoops_PAIH._hoops_CPPH();
					}
				}
				_hoops_CGPS->UnlockVertexBuffer();
				_hoops_CGPS->UnlockIndexBuffer();

				odl->item.geometry.id->AddFirst(_hoops_CGPS);
			}
			else {
				//_hoops_RPP _hoops_SR _hoops_RGAR _hoops_CPHS _hoops_RH _hoops_HACH _hoops_AIR _hoops_PGGA _hoops_IIGR _hoops_SPHS _hoops_GHHS _hoops_RHHS _hoops_HII _hoops_AHHS, 
				//_hoops_SAHR _hoops_PHHS _hoops_SSPC _hoops_SCH
				delete _hoops_CGPS;
			}
		}
	}
	else
	{
		odl->item.geometry.id->ResetCursor();
		_hoops_CGPS = odl->item.geometry.id->PeekCursor();
	}

	if (_hoops_PAPS)
		FREE_ARRAY(_hoops_PAPS, _hoops_HAPS, int);

	if (h3ddata->_hoops_CIGI &&
		h3ddata->_hoops_CIGI->_hoops_IHGI)
		return;

	bool _hoops_GASP =
		nr->_hoops_CPP->_hoops_PRH._hoops_HRH ||
		BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP);
	_hoops_SRRS = _hoops_IISP(h3ddata, nr, _hoops_APHA, type, _hoops_GASP, 0, _hoops_SRRS);
	_hoops_SRRS |= _hoops_CCSP(nr);

	if (_hoops_RRHA || BIT(_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
		_hoops_HHHS (h3ddata, nr, type, pe, _hoops_CPHA, _hoops_SRRS, odl->_hoops_RAHA, &_hoops_RSR);
	}
	else
		_hoops_CPHC (h3ddata, nr, type, pe, _hoops_CPHA, _hoops_SRRS, &_hoops_RSR);

	_hoops_GGGH (h3ddata, nr, _hoops_RSR);
	_hoops_AHSA (h3ddata, nr, type, _hoops_RSR);
	_hoops_RSR->_hoops_SIAA (nr, _hoops_GHP);

	odl->item.geometry.id->ResetCursor();
	_hoops_CGPS = odl->item.geometry.id->PeekCursor();
	
	bool _hoops_IHHS =
		!BIT (nr->transform_rendition->flags, _hoops_CHHS) &&
			BIT (nr->_hoops_IRR->_hoops_SHHS, _hoops_GIHS) &&
			(ANYBIT (nr->transform_rendition->_hoops_APH, Heur_Culling_EXTENT|_hoops_RIHS) ||
				(BIT (nr->transform_rendition->_hoops_APH, Heur_Culling_VIEW_FRUSTUM) &&
					!BIT (nr->transform_rendition->flags, _hoops_AIHS)));

	do {
		Test *	cull_results = null;
		int	_hoops_PIHS = 0;

		if (_hoops_CGPS->_hoops_IAHS && _hoops_IHHS) {
			H3D_Bounding_Tree *tree = _hoops_CGPS->_hoops_IAHS;

			if (tree->count > h3ddata->_hoops_HIHS) {
				if (h3ddata->_hoops_IIHS)
					FREE_ARRAY (h3ddata->_hoops_IIHS, h3ddata->_hoops_HIHS, Test);
				ALLOC_ARRAY (h3ddata->_hoops_IIHS, tree->count, Test);
				h3ddata->_hoops_HIHS = tree->count;
			}

			cull_results = h3ddata->_hoops_IIHS;

			float _hoops_CIHS;
			int	_hoops_SIHS = 0;
			
			if (BIT (nr->transform_rendition->_hoops_APH, _hoops_RIHS))
				_hoops_SIHS = nr->_hoops_IRR->_hoops_GCHS;
			if (BIT (nr->transform_rendition->_hoops_APH, Heur_Culling_EXTENT))
				_hoops_SIHS = _hoops_IAAA(nr->_hoops_IRR->_hoops_GRGC, _hoops_SIHS);
			
			_hoops_PIHS = HD_Transform_And_Test_Simple_Sphere (nr, 
							tree->count, tree->_hoops_RCHS, tree->_hoops_ACHS, 
							0, _hoops_SIHS, cull_results, null, &_hoops_CIHS);

			if (_hoops_CIHS > 0.0f &&
				nr->_hoops_IRR->_hoops_PCHS == Heur_MAX_EXTENT_MODE_DEFER) { 

				int _hoops_HCHS = (int) (_hoops_CIHS * (float)_hoops_ICHS / (float)_hoops_SIHS);

				if (_hoops_HCHS > dc->_hoops_SSGC)
					dc->_hoops_SSGC = _hoops_HCHS;
			}

			_hoops_GPRH (_hoops_CCHS) += tree->count - _hoops_PIHS;
		}
		else
			_hoops_PIHS = _hoops_CGPS->_hoops_SAHS;

		do {
			_hoops_RSR->_hoops_CHPA (nr, _hoops_CAPA);

			if (_hoops_PIHS == _hoops_CGPS->_hoops_SAHS)
				_hoops_CGPS->_hoops_CHSA(h3ddata);
			else
				_hoops_CGPS->_hoops_CHSA(h3ddata, cull_results);
			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);

		odl->item.geometry.id->AdvanceCursor();
	} while ((_hoops_CGPS = odl->item.geometry.id->PeekCursor()) != null);

	h3ddata->_hoops_AIC = false;

} //_hoops_RSGR _hoops_API '_hoops_CPSA _hoops_PGSA 3d _hoops_ACRI'



/*
 * _hoops_SRAC
 */
void draw_3d_polyedge (
		Net_Rendition const &  nr,
		Polyedge const *pe)
{
	H3DData alter *h3ddata = H3DD (nr->_hoops_SRA);
	Line_Rendition const &_hoops_GHP = nr->_hoops_RHP;
	int weight = _hoops_GHP->weight;

	/* _hoops_GISP _hoops_SPPR _hoops_HIS _hoops_SGS _hoops_GGIC _hoops_SCHS _hoops_PAH _hoops_HIIC _hoops_RGCH. */
	//_hoops_RPP (_hoops_RRAP->_hoops_GSHS._hoops_CCH == _hoops_IHPR)
		//_hoops_ASRC;

	if (weight < 0)
		weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
	if (_hoops_GAPI (_hoops_GHP->line_style) ||
		weight > H3D_LARGEST_PRECOMPUTED_CIRCLE){
		if (h3ddata->_hoops_CIGI)
			h3ddata->_hoops_CIGI->mask &= ~_hoops_ASRI;
		HD_Std_3D_Polyedge (nr, pe);
		return;
	}

	if (!BIT(pe->_hoops_SRHA, DL_DO_NOT_RECOMPILE) && pe->point_count == 0) {
		int				_hoops_PHHA = pe->_hoops_PHHA;
		int const *		lengths = pe->lengths;
		int const *		_hoops_AIHA = pe->_hoops_AIHA;
		int				index;
		int				point_count = 0;
		/* _hoops_PS _hoops_GHCA _hoops_HS _hoops_PCCP _hoops_AIPH _hoops_RSHS _hoops_PPR/_hoops_PAR _hoops_ASHS, _hoops_SPIC _hoops_HIGR _hoops_IS _hoops_CGIC _hoops_RH
		** _hoops_CIAS _hoops_PSHS _hoops_HSH _hoops_IH _hoops_AGCR. */

		while (_hoops_PHHA-- > 0) {
			int			length = *lengths++;

			if (length < 0)
				length = -length;

			if (_hoops_AIHA) {
				while (length-- > 0) {
					if ((index = *_hoops_AIHA++) > point_count)
						point_count = index;
				}
			}
			else {
				point_count = pe->total;
			}
		}

		if (pe->point_count == 0)
			((Polyedge alter *)pe)->point_count = ++point_count;
	}
	really_draw_3d_polyedge (nr, pe, _hoops_GHP, null);

}


local bool
_hoops_HSHS (
		Net_Rendition const &nr,
		Geometry const *g,
		bool single)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	H3DData alter *h3ddata = H3DD (dc);

	if (BIT (h3ddata->_hoops_CIGI->_hoops_RRSI, _hoops_CIIP))
		return true;  //_hoops_ISII _hoops_HRGR _hoops_AIAH _hoops_GPP _hoops_RH _hoops_AIRI _hoops_HIGR.

	_hoops_IRHA *pair = POOL_NEW(dc->memory_pool, _hoops_IRHA)(nr, g, dc->_hoops_SPA->modelling_matrix, dc->_hoops_SPA->color, single);

	if (!h3ddata->_hoops_CIGI->_hoops_HRPI)
		h3ddata->_hoops_CIGI->_hoops_HRPI = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);

	h3ddata->_hoops_CIGI->_hoops_HRPI->AddFirst(pair);
	return true;
}


/*
 * _hoops_SRAC
 */
void draw_3d_polyline (
		Net_Rendition const &  nr,
		Polyline const *p)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	H3DData alter *h3ddata = H3DD (nr->_hoops_SRA);
	Polyedge alter *pe;
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	bool _hoops_IAHC = false;
	_hoops_IAPA const *_hoops_CAPA = null;
	int weight = _hoops_HC->weight;

	if (h3ddata->_hoops_ISCI) {
		if (dc->_hoops_RAI) {
			Type type = dc->_hoops_RAI->type;
			switch (type) {
				case _hoops_IIIP:
				case _hoops_HIIP:
				case _hoops_PIIP:
				case _hoops_GIIP:
				case _hoops_RIIP:
				case _hoops_CHIP: {
					_hoops_HSHS (nr, (Geometry const *)p, !h3ddata->_hoops_AHPI);
					return;
				}
				case _hoops_GGCP:
				default:
					//_hoops_AA _hoops_ISAP
					break;
			}
		}
		else {
			_hoops_HSHS (nr, (Geometry const *)p, !h3ddata->_hoops_AHPI);
			return;
		}
		h3ddata->_hoops_CIGI->mask &= ~_hoops_IRPI;
	}

	if (weight < 0)
		weight = (int)(HD_Compute_Generic_Size (nr, _hoops_HC->_hoops_PHP, _hoops_HC->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
	if (weight > 1 ||
		BIT(_hoops_HC->flags, _hoops_SRPI) ||
		_hoops_GAPI (_hoops_HC->line_style) ||
		p->type != _hoops_PIIP && p->count < 0) {
		_hoops_IAHC = true;
	}

	// _hoops_AHH: _hoops_PS _hoops_HS _hoops_IS _hoops_CAH _hoops_RGR _hoops_HPGR _hoops_RH _hoops_SCIA _hoops_PAPA _hoops_RPP _hoops_SCH _hoops_ISHS, _hoops_CR _hoops_RH _hoops_CSHS _hoops_SPIP _hoops_CAPP
	// _hoops_GPGH'_hoops_RA _hoops_SSHS _hoops_RAPR _hoops_IH _hoops_RH _hoops_RHPP'_hoops_GRI _hoops_ACRI _hoops_ACPH _hoops_IS _hoops_CAH _hoops_SCH _hoops_ISSC _hoops_IS _hoops_GGIS.
	if (!_hoops_HPCA(nr, _hoops_CAPA)) {
		_hoops_IAHC = true;
	}

	if (_hoops_IAHC) {
		HD_Std_3D_Polyline (nr, p);
		return;
	}

	if (p->type != _hoops_PIIP && p->count < 2)
		return;

	H3D_TRACE(h3ddata, "draw_3d_polyline");
	ZALLOC (pe, Polyedge);
	_hoops_ICAI (pe);
	if (p->type == _hoops_PIIP) {
		Line const *	l = (Line const *)p;
		pe->point_count = 2;
		pe->points = (Point *)l->points;
	}
	else {
		pe->point_count = p->count;
		pe->points = p->points;
	}
	pe->total = pe->point_count;
	pe->_hoops_PHHA = 1;
	pe->_hoops_GSCP = (Geometry *)p;
	/* _hoops_PGRC _hoops_PAH _hoops_RGAR _hoops_PHHR _hoops_CRGR _hoops_AIRI _hoops_CPCI _hoops_AIH _hoops_RGIS.  _hoops_CGP 
	   _hoops_SR'_hoops_ASAR _hoops_ARI, _hoops_SCH _hoops_SIAS _hoops_SHH _hoops_PGGA _hoops_SR'_hoops_ASAR _hoops_ASCA _hoops_IRS _hoops_RAR-_hoops_AAR _hoops_AGIS 
	   _hoops_PAR _hoops_PGIS */
	pe->_hoops_SRHA = _hoops_SRHH;
	really_draw_3d_polyedge (nr, pe, nr->_hoops_AHP, null);
	if (_hoops_ISAI (pe) == 0)
		HI_Free_Polyedge(pe);

}


/*****************************************************************************
						_hoops_HGIS
						_hoops_APAS
*****************************************************************************/

void _hoops_ISRI (
		Net_Rendition const &  nr,
		Polyedge const * pe,
		H3D_Display_List_Bin * _hoops_RRHA)
{
	H3DData alter *h3ddata = H3DD (nr->_hoops_SRA);
	Polyedge alter *_hoops_HPAS = (Polyedge alter *) pe;

	//_hoops_PRPP _hoops_SIAC _hoops_ACPP _hoops_HIS _hoops_SGS _hoops_GCAC _hoops_HCPH _hoops_CHR _hoops_RCAC _hoops_IS _hoops_SSS
	H3D_TRACE(h3ddata, "draw_indexed_polyedge");

	if (_hoops_RRHA)
		_hoops_RRHA->flags |= (_hoops_GGIA | DL_INDEX_INTERPOLATION);
	else
		_hoops_HPAS->_hoops_SRHA |= (_hoops_GGIA | DL_INDEX_INTERPOLATION);
	really_draw_3d_polyedge(nr, _hoops_HPAS, nr->_hoops_RHP, _hoops_RRHA);


}


//#_hoops_PPIP _hoops_IGIS
#ifdef _hoops_CGIS

//_hoops_SGIS
#define _hoops_GRIS 10
#define	_hoops_RRIS	0.15f
#define _hoops_ARIS 32

#define _hoops_PRIS		0x1
#define _hoops_HRIS		0x2
#define _hoops_IRIS		0x4

typedef VList<int, CMO_Pooled> _hoops_CRIS;
struct _hoops_SRIS {
	_hoops_SRIS *	_hoops_GAIS;
	_hoops_SRIS *	_hoops_RAIS;
	_hoops_SRIS *	_hoops_AAIS;
	_hoops_CRIS *			_hoops_PAIS;
	int					_hoops_HAIS;
};


local int _hoops_IAIS (
		Memory_Pool *mempool,
		_hoops_CAIS const *_hoops_RCHS,
		_hoops_SRIS *p,
		int level,
		int _hoops_SAIS)
{
	Point _hoops_GPIS;
	float radius;
	int index;
	int i;
	int count =  p->_hoops_PAIS->Count();
	float _hoops_RPIS, high, low, _hoops_APIS;
	float _hoops_PPIS = 0.0f;
	int _hoops_HPIS = 0;

	if (count < _hoops_GRIS ||
		ANYBIT (_hoops_SAIS, _hoops_PRIS|_hoops_HRIS|_hoops_IRIS) ||
		level > _hoops_ARIS)
		return count;

	//_hoops_GRAS _hoops_IPIS
	_hoops_SASC cuboid;
	p->_hoops_PAIS->ResetCursor(); 
	for (i = 0 ; i < count ; i++) {
		index = p->_hoops_PAIS->PeekCursor();
		p->_hoops_PAIS->AdvanceCursor();
		cuboid.Merge (_hoops_RCHS[index]);
	}

	//_hoops_CAHA _hoops_CPIS _hoops_SPIS
	if (!BIT (_hoops_SAIS, _hoops_PRIS)) {
		_hoops_RPIS = cuboid.max.x - cuboid.min.x;
		p->_hoops_HAIS = _hoops_PRIS;
		_hoops_PPIS = _hoops_RPIS;
	}
	if (!BIT (_hoops_SAIS, _hoops_HRIS)) {
		_hoops_RPIS = cuboid.max.y - cuboid.min.y;
		_hoops_PPIS = _hoops_RPIS;
		p->_hoops_HAIS = _hoops_HRIS;
	}
	if (!BIT (_hoops_SAIS, _hoops_IRIS)) {
		_hoops_RPIS = cuboid.max.z - cuboid.min.z;
		_hoops_PPIS = _hoops_RPIS;
		p->_hoops_HAIS = _hoops_IRIS;
	}
	if (_hoops_PPIS <= 0.0f)
		return count;

	switch (p->_hoops_HAIS) {
		default:
			ASSERT(0); //_hoops_PAHA'_hoops_RA _hoops_SHH _hoops_SSRR
		case _hoops_PRIS: {
			_hoops_RPIS = cuboid.max.x - cuboid.min.x;
			_hoops_APIS = (cuboid.max.x + cuboid.min.x) * 0.5f;
		} break;
		case _hoops_HRIS: {
			_hoops_RPIS = cuboid.max.y - cuboid.min.y;
			_hoops_APIS = (cuboid.max.y + cuboid.min.y) * 0.5f;
		} break;
		case _hoops_IRIS: {
			_hoops_RPIS = cuboid.max.z - cuboid.min.z;
			_hoops_APIS = (cuboid.max.z + cuboid.min.z) * 0.5f;
		} break;
	}
	high = _hoops_APIS + _hoops_RRIS * _hoops_RPIS;
	low  = _hoops_APIS - _hoops_RRIS * _hoops_RPIS;

	//_hoops_GHIS _hoops_CRGR _hoops_RHIS, _hoops_AHIS, _hoops_PHIS
	if (p->_hoops_GAIS == null) {
		ZALLOC (p->_hoops_GAIS, _hoops_SRIS);
		p->_hoops_GAIS->_hoops_PAIS = POOL_NEW(mempool, _hoops_CRIS)();
	}
	if (p->_hoops_RAIS == null) {
		ZALLOC (p->_hoops_RAIS, _hoops_SRIS);
		p->_hoops_RAIS->_hoops_PAIS = POOL_NEW(mempool, _hoops_CRIS)();
	}
	if (p->_hoops_AAIS == null) {
		ZALLOC (p->_hoops_AAIS, _hoops_SRIS);
		p->_hoops_AAIS->_hoops_PAIS = POOL_NEW(mempool, _hoops_CRIS)();
	}
	for (i = 0 ; i < count ; i++) {
		index = p->_hoops_PAIS->RemoveFirst();
		_hoops_GPIS = _hoops_RCHS[index].center;
		radius = _hoops_RCHS[index].radius;
		if (radius == -1.0f)
			p->_hoops_PAIS->AddLast (index); //_hoops_PPSI _hoops_SCH _hoops_ISSC _hoops_HPGR _hoops_RH _hoops_RSGR
		else switch (p->_hoops_HAIS) {
			case _hoops_PRIS: {
				if (_hoops_GPIS.x > _hoops_APIS) {
					if (_hoops_GPIS.x - radius > low)
						p->_hoops_GAIS->_hoops_PAIS->AddLast (index);
					else
						p->_hoops_AAIS->_hoops_PAIS->AddLast (index);
				}
				else {
					if (_hoops_GPIS.x + radius < high)
						p->_hoops_RAIS->_hoops_PAIS->AddLast (index);
					else
						p->_hoops_AAIS->_hoops_PAIS->AddLast (index);
				}
			} break;
			case _hoops_HRIS: {
				if (_hoops_GPIS.y > _hoops_APIS) {
					if (_hoops_GPIS.y - radius > low)
						p->_hoops_GAIS->_hoops_PAIS->AddLast (index);
					else
						p->_hoops_AAIS->_hoops_PAIS->AddLast (index);
				}
				else {
					if (_hoops_GPIS.y + radius < high)
						p->_hoops_RAIS->_hoops_PAIS->AddLast (index);
					else
						p->_hoops_AAIS->_hoops_PAIS->AddLast (index);
				}
			} break;
			case _hoops_IRIS: {
				if (_hoops_GPIS.z > _hoops_APIS) {
					if (_hoops_GPIS.z - radius > low)
						p->_hoops_GAIS->_hoops_PAIS->AddLast (index);
					else
						p->_hoops_AAIS->_hoops_PAIS->AddLast (index);
				}
				else {
					if (_hoops_GPIS.z + radius < high)
						p->_hoops_RAIS->_hoops_PAIS->AddLast (index);
					else
						p->_hoops_AAIS->_hoops_PAIS->AddLast (index);
				}
			} break;
		}
	}
	//_hoops_CCPH _hoops_RH _hoops_HHIS _hoops_RPP _hoops_SIGR
	if (p->_hoops_GAIS->_hoops_PAIS->Count() <= _hoops_GRIS) {
		count = p->_hoops_GAIS->_hoops_PAIS->Count();
		//_hoops_IHIS _hoops_RH _hoops_SRGR _hoops_IS _hoops_RH _hoops_PHIS _hoops_HIGR
		for (i = 0 ; i < count ; i++) {
			index = p->_hoops_GAIS->_hoops_PAIS->RemoveFirst();
			p->_hoops_AAIS->_hoops_PAIS->AddLast (index);
		}
		delete p->_hoops_GAIS->_hoops_PAIS;
		FREE (p->_hoops_GAIS, _hoops_SRIS);
		p->_hoops_GAIS = null;
	}
	else
		_hoops_HPIS += _hoops_IAIS (mempool, _hoops_RCHS, p->_hoops_GAIS, level+1, _hoops_SAIS);
	if (p->_hoops_RAIS->_hoops_PAIS->Count() <= _hoops_GRIS) {
		count = p->_hoops_RAIS->_hoops_PAIS->Count();
		for (i = 0 ; i < count ; i++) {
			index = p->_hoops_RAIS->_hoops_PAIS->RemoveFirst();
			p->_hoops_AAIS->_hoops_PAIS->AddLast (index);
		}
		delete p->_hoops_RAIS->_hoops_PAIS;
		FREE (p->_hoops_RAIS, _hoops_SRIS);
		p->_hoops_RAIS = null;
	}
	else
		_hoops_HPIS += _hoops_IAIS (mempool, _hoops_RCHS, p->_hoops_RAIS, level+1, _hoops_SAIS);
	//_hoops_RPP _hoops_IIH _hoops_AAPR _hoops_CHIS _hoops_PRCH _hoops_SGS _hoops_GGHP _hoops_SHIS _hoops_IS _hoops_IRS _hoops_GSSC _hoops_PAPA, _hoops_GRHP _hoops_RGR _hoops_GIIS _hoops_GAR _hoops_IRS _hoops_GRAA-_hoops_RIIS
	if (_hoops_HPIS != 0)
		_hoops_HPIS++;
	_hoops_HPIS += _hoops_IAIS (mempool, _hoops_RCHS, p->_hoops_AAIS, level+1, _hoops_SAIS | p->_hoops_HAIS);
	_hoops_HPIS += p->_hoops_PAIS->Count();

	//_hoops_ASRC _hoops_RH _hoops_PHI _hoops_IIGR _hoops_AIIS _hoops_HPGR _hoops_RGR _hoops_PAPA _hoops_PPR _hoops_CAPP _hoops_SGS _hoops_GRS _hoops_SHH _hoops_PPSI _hoops_GGR _hoops_RH _hoops_HACH _hoops_HRPR
	return _hoops_HPIS;
}


local int _hoops_PIIS (
		_hoops_CAIS const *_hoops_RCHS,
		_hoops_SRIS *p,
		int offset,
		_hoops_CAIS alter *_hoops_HIIS,
		int alter *_hoops_ACHS,
		_hoops_CAIS alter *_hoops_IIIS,
		int alter *_hoops_HGA,
		int alter *_hoops_CIIS)
{
	_hoops_CAIS _hoops_SIIS;
	int count = 0;
	int index;
	int i;

	if (p->_hoops_GAIS != null)
		count += _hoops_PIIS (_hoops_RCHS, p->_hoops_GAIS, offset+count+1, _hoops_HIIS, _hoops_ACHS, &_hoops_SIIS, _hoops_HGA, _hoops_CIIS);
	if (p->_hoops_RAIS != null)
		count += _hoops_PIIS (_hoops_RCHS, p->_hoops_RAIS, offset+count+1, _hoops_HIIS, _hoops_ACHS, &_hoops_SIIS, _hoops_HGA, _hoops_CIIS);
	//_hoops_GCIS _hoops_HAHI _hoops_GAR _hoops_GRAA-_hoops_RIIS _hoops_GIIS _hoops_RPP (_hoops_HIH _hoops_RGAR _hoops_RPP) _hoops_CPHP _hoops_HRGR _hoops_RCIS _hoops_CRGR _hoops_RHIS _hoops_PPR/_hoops_PAR _hoops_AHIS _hoops_CHIC
	if (count != 0)
		count++;
	if (p->_hoops_AAIS != null)
		count += _hoops_PIIS (_hoops_RCHS, p->_hoops_AAIS, offset+count, _hoops_HIIS, _hoops_ACHS, &_hoops_SIIS, _hoops_HGA, _hoops_CIIS);

	int length = p->_hoops_PAIS->Count();
	for (i = 0 ; i < length ; i++) {
		index = p->_hoops_PAIS->RemoveFirst();
		_hoops_SIIS.Merge (_hoops_RCHS[index]);
		_hoops_HGA[index] = *_hoops_CIIS;
		(*_hoops_CIIS)++;
		_hoops_HIIS[offset+count] = _hoops_RCHS[index];
		count++;
	}

	if (p->_hoops_GAIS || p->_hoops_RAIS) {
		_hoops_HIIS[offset] = _hoops_SIIS;
		_hoops_ACHS[offset] = count;
	}
	if (_hoops_IIIS)
		_hoops_IIIS->Merge (_hoops_SIIS);

	delete p->_hoops_PAIS;
	FREE (p, _hoops_SRIS);
	return count;
}


local H3D_Bounding_Tree *_hoops_ACIS (
		Memory_Pool *mempool,
		H3D_Display_List_Bin alter *_hoops_RRHA,
		_hoops_CAIS const *_hoops_RCHS)
{
	int count = _hoops_RRHA->_hoops_CRHA->Count();
	int *_hoops_HGA;
	_hoops_IRHA **_hoops_PCIS;
	_hoops_IRHA *pair;
	H3D_Bounding_Tree *tree = null;

	_hoops_SRIS *	p;
	ZALLOC (p, _hoops_SRIS);
	p->_hoops_PAIS = POOL_NEW(mempool, _hoops_CRIS)();
	for (int i = 0 ; i < count ; i++)
		p->_hoops_PAIS->AddLast (i);
	ZALLOC (tree, H3D_Bounding_Tree);
	tree->count = _hoops_IAIS (mempool, _hoops_RCHS, p, 0, 0);
	ZALLOC_ARRAY (tree->_hoops_RCHS, tree->count, _hoops_CAIS);
	ZALLOC_ARRAY (tree->_hoops_ACHS, tree->count, int);
	ALLOC_ARRAY (_hoops_HGA, count, int);
	SET_MEMORY (_hoops_HGA, count * sizeof(int), -1);
	int _hoops_HCIS = 0;
	_hoops_PIIS (_hoops_RCHS, p, 0, tree->_hoops_RCHS, tree->_hoops_ACHS, null, _hoops_HGA, &_hoops_HCIS);

	ZALLOC_ARRAY (_hoops_PCIS, count, _hoops_IRHA *);
	_hoops_RRHA->_hoops_CRHA->ResetCursor();
	for (int i = 0; i < count; i++) {
		pair = _hoops_RRHA->_hoops_CRHA->RemoveFirst();
		ASSERT (pair != null);
		_hoops_PCIS[_hoops_HGA[i]] = pair;
	}
	for (int i = 0; i < count; i++)
		_hoops_RRHA->_hoops_CRHA->AddLast(_hoops_PCIS[i]);
	FREE_ARRAY (_hoops_PCIS, count, _hoops_IRHA *);
	FREE_ARRAY (_hoops_HGA, count, int);

	return tree;
}
#endif


local H3D_Bounding_Tree *_hoops_SRHS(
		Memory_Pool *memory_pool,
		_hoops_GAHS const *_hoops_ICIS,
		H3D_Display_List_Bin alter *_hoops_RRHA,
		bool _hoops_CCIS)
{
	_hoops_IRHA *pair = null;
	H3D_Bounding_Tree *tree;

	ZALLOC (tree, H3D_Bounding_Tree);
	if (_hoops_RRHA) {
		tree->count = _hoops_RRHA->_hoops_CRHA->Count();
		_hoops_RRHA->_hoops_CRHA->ResetCursor();
	}
	else {
		tree->count = 1;
	}

	ZALLOC_ARRAY (tree->_hoops_RCHS, tree->count, _hoops_CAIS);
	for (int i = 0; i < tree->count ; i++) {
		if (_hoops_RRHA) {
			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
			ASSERT (pair != null);
			_hoops_ICIS = (_hoops_GAHS const *)pair->geo;
		}

		if (_hoops_ICIS->bounding != null) {
			if (_hoops_CCIS && pair->_hoops_CPAI)
				tree->_hoops_RCHS[i] = _hoops_ICIS->bounding->cuboid._hoops_SCIS(pair->_hoops_CPAI->matrix);
			else 
				tree->_hoops_RCHS[i] = _hoops_ICIS->bounding->sphere;
		}
		else
			tree->_hoops_RCHS[i].radius = -1.0f;
	}

#ifdef _hoops_CGIS
	if (_hoops_RRHA && tree->count > _hoops_GRIS) {
		H3D_Bounding_Tree *_hoops_GSIS = _hoops_ACIS (memory_pool, _hoops_RRHA, tree->_hoops_RCHS);
		FREE_ARRAY (tree->_hoops_RCHS, tree->count, _hoops_CAIS);
		FREE (tree, H3D_Bounding_Tree);
		return _hoops_GSIS;
	}
#else
	UNREFERENCED (memory_pool);
#endif
	return tree;
}

/*
 * _hoops_PGAA
 */
local bool _hoops_RSIS (
		Net_Rendition const &nr,
		_hoops_GAHS const *_hoops_ICIS)
{
	if (_hoops_ICIS->bounding == null)
		return true;

	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;

	Test _hoops_ASIS;
	float _hoops_CIHS;
	int	_hoops_SIHS = 0;

	if (BIT (nr->transform_rendition->_hoops_APH, _hoops_RIHS))
		_hoops_SIHS = nr->_hoops_IRR->_hoops_GCHS;
	if (BIT (nr->transform_rendition->_hoops_APH, Heur_Culling_EXTENT))
		_hoops_SIHS = _hoops_IAAA(nr->_hoops_IRR->_hoops_GRGC, _hoops_SIHS);

	int _hoops_PIHS = HD_Transform_And_Test_Simple_Sphere (nr, 1, &_hoops_ICIS->bounding->sphere, null, 
							0, _hoops_SIHS, &_hoops_ASIS, null, &_hoops_CIHS);

	if (_hoops_CIHS > 0.0f &&
		nr->_hoops_IRR->_hoops_PCHS == Heur_MAX_EXTENT_MODE_DEFER) { 

		int _hoops_HCHS = (int) (_hoops_CIHS * (float)_hoops_ICHS / (float)_hoops_SIHS);

		if (_hoops_HCHS > dc->_hoops_SSGC)
			((Display_Context alter *)dc)->_hoops_SSGC = _hoops_HCHS;
	}

	if (!_hoops_PIHS)
		_hoops_GPRH (_hoops_CCHS)++;

	return _hoops_PIHS != 0;
}


/*****************************************************************************
						_hoops_PSIS
*****************************************************************************/

local bool
_hoops_HSIS (
		Net_Rendition const &nr,
		Polygon const *p,
		bool single)
{
	Display_Context const *dc = nr->_hoops_SRA;
	H3DData alter *h3ddata = H3DD (dc);
	Type type = p->type;
	Action_Mask mask;
	_hoops_IRHA *pair;

	UNREFERENCED(type);

	ASSERT (type == _hoops_RCIP);
	mask = _hoops_ACIP;

	if (h3ddata->_hoops_CIGI->_hoops_SIGI)
		return false;

	if (dc->_hoops_RAI &&
		dc->_hoops_RAI->type != _hoops_RCIP)
		return false;


	/* _hoops_AAPI _hoops_PAH'_hoops_RA _hoops_HS _hoops_IRGH _hoops_ISHA _hoops_PAR _hoops_CPAP _hoops_AIRC, _hoops_HIS _hoops_IIH'_hoops_GRI _hoops_PSP
	   _hoops_RRP _hoops_IS _hoops_ISPR _hoops_IH _hoops_IAHP _hoops_GGR _hoops_RH _hoops_ISIS
	_hoops_RPP (_hoops_SCII->_hoops_CSIS->_hoops_HSHR != _hoops_RRAP->_hoops_SSIS->_hoops_SCII->_hoops_CSIS->_hoops_HSHR)
		_hoops_ASRC _hoops_RCPP;
	_hoops_RPP (_hoops_SCII->_hoops_GGCS->_hoops_HSHR != _hoops_RRAP->_hoops_SSIS->_hoops_SCII->_hoops_GGCS->_hoops_HSHR)
		_hoops_ASRC _hoops_RCPP;
	*/

	if (!h3ddata->_hoops_CIGI->_hoops_IIII)
		h3ddata->_hoops_CIGI->_hoops_IIII = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);

	pair = POOL_NEW(dc->memory_pool, _hoops_IRHA)(nr, p, dc->_hoops_SPA->modelling_matrix, dc->_hoops_SPA->color, single);
	h3ddata->_hoops_CIGI->_hoops_IIII->AddFirst(pair);
	return true;
}



/* _hoops_SIHR _hoops_CHPI, _hoops_SRII, _hoops_GAII _hoops_PPR _hoops_RRII */
void draw_3d_ellipse (
		Net_Rendition const &nr,
		Ellipse const *		 ellipse)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	H3DData alter *h3ddata = H3DD (dc);
	Type type = ellipse->type;
	_hoops_IRHA *pair;

	if (h3ddata->_hoops_ISCI) {
		if (!h3ddata->_hoops_CIGI->_hoops_IIII)
			h3ddata->_hoops_CIGI->_hoops_IIII = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);

		pair = POOL_NEW(dc->memory_pool, _hoops_IRHA)(nr, ellipse, dc->_hoops_SPA->modelling_matrix, dc->_hoops_SPA->color, !h3ddata->_hoops_AHPI);
		h3ddata->_hoops_CIGI->_hoops_IIII->AddFirst(pair);
		return;
	}

	for (;;) {
		switch (type) {
			case _hoops_CGCP:
			case _hoops_SGCP:
				HD_Std_3D_Ellipse (nr, ellipse);
				break;
			case _hoops_GRCP:
			case _hoops_RRCP:
				HD_Std_3D_Elliptical_Arc (nr, (Elliptical_Arc const *) ellipse);
				break;
		}
		if (!h3ddata->_hoops_AHPI)
			break;
		ellipse = (Ellipse const *)ellipse->next;
		if (ellipse == null || ellipse->type != type)
			break;
	}
}



void draw_3d_polygon (
		Net_Rendition const &		inr,
		Polygon const *				polygon)
{
	Net_Rendition				nr = inr;
	Display_Context const *		dc = nr->_hoops_SRA;
	H3DData alter *				h3ddata = H3DD (dc);
	int							i, ii, j, length;
#define _hoops_RGCS 128
	int 						_hoops_AGCS[_hoops_RGCS];
	int 						_hoops_PGCS[_hoops_RGCS];
	int 						_hoops_HGCS[_hoops_RGCS];
	float 						_hoops_IGCS[_hoops_RGCS];
	int *						indices = _hoops_AGCS;
	int *						face_indices = _hoops_PGCS;
	int *						_hoops_SPII = _hoops_HGCS;
	float *						_hoops_CCCP = _hoops_IGCS;
	_hoops_ARPA *						normals = null;
	int *						_hoops_GAHI;
	bool						_hoops_IAHC = false;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	Polygon const *				p;
	Point alter *				pts;
	int							shift;

	if (polygon->count < 2)
		return;

	_hoops_IAHC = _hoops_PHII (nr);

	if (h3ddata->_hoops_ISCI) {
		if (!_hoops_IAHC && _hoops_HSIS (nr, polygon, !h3ddata->_hoops_AHPI))
			return;
		if (dc->_hoops_RAI && dc->_hoops_RAI->type != _hoops_RCIP) {
			if (dc->_hoops_RAI->type == _hoops_GGCP)
				h3ddata->_hoops_CIGI->mask &= ~_hoops_RGCP;
			else
				h3ddata->_hoops_CIGI->mask &= ~_hoops_ARCP;
		}
		h3ddata->_hoops_CIGI->mask &= ~_hoops_ACIP;
	}

	if (_hoops_IAHC) {
		p = polygon;
		for (;;) {
			HD_Std_3D_Polygon (nr, p);
			if (!h3ddata->_hoops_AHPI)
				break;
			p = (Polygon const *)p->next;
			if (p == null || p->type != _hoops_RCIP)
				break;
		}
		return;
	}

	if (polygon->count >= 3) {
		if (BIT (nr->_hoops_RGP, T_FACES)) {
			_hoops_CIGA	_hoops_SIGA = nr->_hoops_IHA;
			Tristrip ts;
			bool _hoops_HHII;

			_hoops_HHII = (
				nr->_hoops_IHA->_hoops_CHA &&
				nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR < 1.0f);

			if (BIT (_hoops_IHCR->heuristics, _hoops_CGCS)) {
				/* _hoops_AGHH */
				p = polygon;
				for (;;) {
					_hoops_SGHH (nr, p);
					if (!h3ddata->_hoops_AHPI)
						break;
					p = (Polygon const *)p->next;
					if (p == null || p->type != _hoops_RCIP)
						break;
				}
			}
			else {
				/* _hoops_SGCS */
				ZERO_STRUCT (&ts,Tristrip);
				ts._hoops_GSCP = (Geometry *)polygon;
				ts._hoops_SRHA = DL_DO_NOT_DEFER | _hoops_SRHH | _hoops_GAHH | DL_TEMPORARY_DATA;
				p = polygon;
				for (;;) {
					_hoops_RCCA(_hoops_GRCS)++;
					ts._hoops_PHHA++;
					ts.point_count += p->count;
					ts.total += p->count;
					if (!h3ddata->_hoops_AHPI)
						break;
					p = (Polygon const *)p->next;
					if (p == null || p->type != _hoops_RCIP)
						break;
				}

				if (ts.point_count + 1 > _hoops_RGCS) {
					ALLOC_ARRAY_CACHED (indices, ts.point_count, int);
					ALLOC_ARRAY_CACHED (face_indices, ts.point_count, int);
				}
				else {
				}
				if (ts._hoops_PHHA > 1) {
					ALLOC_ARRAY (ts.points, ts.point_count, Point);
					ALLOC_ARRAY (ts.lengths, ts._hoops_PHHA, int);
					ts._hoops_RAHH |= _hoops_AAHH;
					p = polygon;
					pts = ts.points;
					for (;;) {
						_hoops_AIGA (p->points, p->count, Point, pts);
						pts += p->count;
						if (!h3ddata->_hoops_AHPI)
							break;
						p = (Polygon const *)p->next;
						if (p == null || p->type != _hoops_RCIP)
							break;
					}

				}
				else {
					ts.points = polygon->points;
					length = polygon->count;
					ts.lengths = &length;
				}
				ts._hoops_AIHA = indices;
				ts.face_count = ts._hoops_PHHA;

				if (nr->_hoops_IRR->_hoops_SRI == _hoops_GAI &&
					BIT (nr->transform_rendition->heuristics, _hoops_IRI)) {

					if (ts.point_count + 1 > _hoops_RGCS)
						ALLOC_ARRAY_CACHED (_hoops_CCCP, ts.point_count, float);

					ts._hoops_CCCP = _hoops_CCCP;
					float *priorities = _hoops_CCCP;
					p = polygon;
					for (;;) {
						float _hoops_HAGR = _hoops_SCCP(p->priority,1);  //1 == _hoops_HSP _hoops_ISP
						for (ii = 0; ii < p->count; ii++) {
							priorities[ii] = _hoops_HAGR;
						}
						priorities += p->count;
						if (!h3ddata->_hoops_AHPI)
							break;
						p = (Polygon const *)p->next;
						if (p == null || p->type != _hoops_RCIP)
							break;
					}
				}

				if (_hoops_SIGA->_hoops_AGP &&
					BIT (_hoops_IHCR->flags, _hoops_GRHH) &&
					BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES)) {
					p = polygon;
					j = 0;
					ALLOC_ARRAY (normals, ts._hoops_PHHA, _hoops_ARPA);
					ts._hoops_PRHH = normals;
					ts.face_indices = face_indices;
					for (;;) {
						if (!BIT (p->_hoops_RRHH, _hoops_ARHH))
							HI_Find_Polygon_Plane ((Polygon alter *) p);
						for (i = 0; i < p->count; i++)
							face_indices[i] = j;
						face_indices += p->count;
						if (BIT(_hoops_IHCR->heuristics, _hoops_SASA)) {
							normals[j].a = -p->plane.a;
							normals[j].b = -p->plane.b;
							normals[j].c = -p->plane.c;
							normals[j].d = -p->plane.d;
						}
						else {
							normals[j].a = p->plane.a;
							normals[j].b = p->plane.b;
							normals[j].c = p->plane.c;
							normals[j].d = p->plane.d;
						}
						if (!h3ddata->_hoops_AHPI)
							break;
						j++;
						p = (Polygon const *)p->next;
						if (p == null || p->type != _hoops_RCIP)
							break;
					}
					face_indices = ts.face_indices; //_hoops_AHIC _hoops_ISSC _hoops_IS _hoops_HSPP
				}

				p = polygon;
				shift = 0;
				j = 0;
				_hoops_GAHI = indices;
				for (;;) {
					ts.lengths[j] = p->count;
					//_hoops_IRHH _hoops_IRS _hoops_IRII
					*_hoops_GAHI++ = 0 + shift;
					length = p->count;
					for (i = 1; i*2 <= length; i++) {
						*_hoops_GAHI++ = i + shift;
						if (i*2 == length)
							break;
						*_hoops_GAHI++ = (length - i) + shift;
					}
					if (!h3ddata->_hoops_AHPI)
						break;
					j++;
					shift += length;
					p = (Polygon const *)p->next;
					if (p == null || p->type != _hoops_RCIP)
						break;
				}
				draw_3d_tristrip (nr, &ts);

				//_hoops_GGAS
				if (indices != _hoops_AGCS) {
					FREE_ARRAY (indices, ts.total, int);
					ts._hoops_AIHA = null;
					indices = _hoops_AGCS;
				}
				if (face_indices != _hoops_PGCS) {
					FREE_ARRAY (face_indices, ts.total, int);
					ts.face_indices = null;
					face_indices = _hoops_PGCS;
				}
				if (_hoops_CCCP != _hoops_IGCS) {
					FREE_ARRAY (_hoops_CCCP, ts.total, float);
					_hoops_CCCP = _hoops_IGCS;
				}
				if (normals != null) {
					FREE_ARRAY (normals, ts._hoops_PHHA, _hoops_ARPA);
					ts._hoops_PRHH = null;
					normals = null;
				}
				if (ts._hoops_PHHA > 1) {
					ASSERT (ts.points != polygon->points);
					FREE_ARRAY (ts.points, ts.point_count, Point);
					ts.points = null;
					ASSERT (ts.lengths != &length);
					FREE_ARRAY (ts.lengths, ts._hoops_PHHA, int);
					ts.lengths = null;
				}
			}
		}
	}

	if (ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE)) {
		Polyedge pe;
		Line_Rendition const &_hoops_GHP = nr->_hoops_RHP;
		int _hoops_RRCS;

		ZERO_STRUCT (&pe, Polyedge);
		pe._hoops_GSCP = (Geometry *)polygon;
		pe._hoops_SRHA = DL_DO_NOT_DEFER | _hoops_SRHH | _hoops_GAHH | DL_TEMPORARY_DATA;
		p = polygon;
		for (;;) {
			_hoops_RCCA(_hoops_GRCS)++;
			pe._hoops_PHHA++;
			pe.point_count += p->count;
			pe.total += p->count + 1;
			if (!h3ddata->_hoops_AHPI)
				break;
			p = (Polygon const *)p->next;
			if (p == null || p->type != _hoops_RCIP)
				break;
		}
		if (pe.total > _hoops_RGCS) {
			ALLOC_ARRAY_CACHED (indices, pe.total, int);
			ALLOC_ARRAY_CACHED (_hoops_SPII, pe.total, int);
		}
		if (pe._hoops_PHHA > 1) {
			ALLOC_ARRAY_CACHED (pe.points, pe.point_count, Point);
			ALLOC_ARRAY_CACHED (pe.lengths, pe._hoops_PHHA, int);
			pe._hoops_RAHH |= _hoops_AAHH;
			p = polygon;
			pts = pe.points;
			for (;;) {
				_hoops_AIGA (p->points, p->count, Point, pts);
				pts += p->count;
				if (!h3ddata->_hoops_AHPI)
					break;
				p = (Polygon const *)p->next;
				if (p == null || p->type != _hoops_RCIP)
					break;
			}
		}
		else {
			pe.points = polygon->points;
			pe.lengths = &_hoops_RRCS;
		}
		if (nr->_hoops_IRR->_hoops_SRI == _hoops_GAI &&
			BIT (nr->transform_rendition->heuristics, _hoops_IRI)) {

			if (pe.point_count + 1 > _hoops_RGCS)
				ALLOC_ARRAY_CACHED (_hoops_CCCP, pe.point_count, float);
			pe._hoops_CCCP = _hoops_CCCP;
			float *priorities = _hoops_CCCP;
			p = polygon;
			for (;;) {
				float _hoops_HAGR = _hoops_SCCP(p->priority,0); //0 == _hoops_PSP _hoops_HSP _hoops_ISP
				for (ii = 0; ii < p->count; ii++) {
					priorities[ii] = _hoops_HAGR;
				}
				priorities += p->count;
				if (!h3ddata->_hoops_AHPI)
					break;
				p = (Polygon const *)p->next;
				if (p == null || p->type != _hoops_RCIP)
					break;
			}
		}


		pe._hoops_AIHA = indices;
		pe._hoops_SPHA = pe._hoops_PHHA;  //_hoops_HAR _hoops_CPSA, _hoops_HIH _hoops_CGH _hoops_SHH _hoops_IRS _hoops_ARCS _hoops_PRCS

		if (_hoops_GHP->_hoops_AGP &&
			BIT (_hoops_IHCR->flags, _hoops_GRHH) &&
			BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES)) {
			p = polygon;
			j = 0;
			ALLOC_ARRAY (pe._hoops_RSHA, pe._hoops_PHHA, Vector);
			pe._hoops_SPII = _hoops_SPII;
			for (;;) {
				if (!BIT (p->_hoops_RRHH, _hoops_ARHH))
					HI_Find_Polygon_Plane ((Polygon alter *) p);
				for (i = 0; i < p->count+1; i++)
					_hoops_SPII[i] = j;
				_hoops_SPII += p->count + 1;
				if (BIT(_hoops_IHCR->heuristics, _hoops_SASA)) {
					pe._hoops_RSHA[j].x = -p->plane.a;
					pe._hoops_RSHA[j].y = -p->plane.b;
					pe._hoops_RSHA[j].z = -p->plane.c;
				}
				else {
					pe._hoops_RSHA[j].x = p->plane.a;
					pe._hoops_RSHA[j].y = p->plane.b;
					pe._hoops_RSHA[j].z = p->plane.c;
				}
				if (!h3ddata->_hoops_AHPI)
					break;
				j++;
				p = (Polygon const *)p->next;
				if (p == null || p->type != _hoops_RCIP)
					break;
			}
			_hoops_SPII = pe._hoops_SPII; //_hoops_AHIC _hoops_ISSC _hoops_IS _hoops_HSPP
		}

		p = polygon;
		shift = 0;
		j = 0;
		int k = 0;
		_hoops_GAHI = indices;
		for (;;) {
			pe.lengths[j] = p->count + 1;
			//_hoops_IRHH _hoops_IRS _hoops_HAPR
			length = p->count;
			for (i = 0; i < length; i++) {
				*_hoops_GAHI++ = i + shift;
			}
			*_hoops_GAHI++ = shift;

			if (!h3ddata->_hoops_AHPI)
				break;
			j++;
			k++;
			shift += length;
			p = (Polygon const *)p->next;
			if (p == null || p->type != _hoops_RCIP)
				break;
		}
		draw_3d_polyedge (nr, &pe);

		if (indices != _hoops_AGCS) {
			FREE_ARRAY (indices, pe.total, int);
			indices = _hoops_AGCS;
			pe._hoops_AIHA = null;
		}
		if (_hoops_SPII != _hoops_HGCS) {
			FREE_ARRAY (_hoops_SPII, pe.total, int);
			_hoops_SPII = _hoops_HGCS;
			pe._hoops_SPII = null;
		}
		if (pe._hoops_RSHA != null) {
			FREE_ARRAY (pe._hoops_RSHA, pe._hoops_PHHA, Vector);
			normals = null;
			pe._hoops_RSHA = null;
		}
		if (pe._hoops_PHHA > 1) {
			ASSERT (pe.points != polygon->points);
			FREE_ARRAY (pe.points, pe.point_count, Point);
			pe.points = null;
			ASSERT (pe.lengths != &length);
			FREE_ARRAY (pe.lengths, pe._hoops_PHHA, int);
			pe.lengths = null;
		}
		if (_hoops_CCCP != _hoops_IGCS)
			FREE_ARRAY (_hoops_CCCP, pe.point_count, float);
	}
} // _hoops_RSGR _hoops_API '_hoops_PGSA 3d _hoops_HSSP'



/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_HRCS _hoops_IRCS
*****************************************************************************
*****************************************************************************/

/*****************************************************************************
						_hoops_CRCS: _hoops_SRCS _hoops_GACS
*****************************************************************************/
/*
 * _hoops_PGAA
 */
local H3D_Display_List *_hoops_RACS (
	Net_Rendition const &		nr,
	_hoops_GSAR *				_hoops_HRR)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	H3DData *h3ddata = H3DD (dc);

	H3D_TRACE(h3ddata, "create_shadow_map_resources");

	// _hoops_ICGP _hoops_AGHS
	H3DFORMAT _hoops_AACS;
	unsigned long _hoops_PACS;

	if (h3ddata->_hoops_SRP)
	{
		_hoops_AACS = H3DFMT_D24S8;
		_hoops_PACS = H3DTEXUSAGE_DEPTHSTENCIL;
	}
	else if (h3ddata->_hoops_GAP)
	{
		_hoops_AACS = H3DFMT_R32F;
		_hoops_PACS = H3DTEXUSAGE_RENDERTARGET;
	}
	else
	{
		// _hoops_HACS _hoops_RPCC.
		_hoops_AACS = H3DFMT_A8R8G8B8;
		_hoops_PACS = H3DTEXUSAGE_RENDERTARGET;
	}

	// _hoops_GCIH _hoops_CCA _hoops_HGRC _hoops_RAAA
	int _hoops_IACS = nr->_hoops_CPP->_hoops_HRR._hoops_HAP;

	if (_hoops_IACS > 2048 && HOOPS_WORLD->vram_size < 0x10000000)	//256 _hoops_CACS
		_hoops_IACS = 2048;

	// _hoops_IPHH _hoops_RAAA _hoops_CRGR _hoops_APP _hoops_HSH
	if (_hoops_IACS <= 512)
		_hoops_IACS = 512;
	else if (_hoops_IACS <= 1024)
		_hoops_IACS = 1024;
	else if (_hoops_IACS <= 2048)
		_hoops_IACS = 2048;
	else if (_hoops_IACS <= 4096)
		_hoops_IACS = 4096;
	/* _hoops_HSRR _hoops_SACS _hoops_SGH.
	_hoops_SHS _hoops_RPP (_hoops_GPCS <= 8192)
		_hoops_GPCS = 8192;
	*/

	// _hoops_RPCS _hoops_ISSC _hoops_APCS _hoops_RPP _hoops_SR _hoops_HS _hoops_AIAH _hoops_CPHR _hoops_HIS.
	if (h3ddata->_hoops_PI._hoops_PPCS &&
		_hoops_IACS > h3ddata->_hoops_PI._hoops_PPCS)
		_hoops_IACS = h3ddata->_hoops_PI._hoops_PPCS;

	// _hoops_HR _hoops_HPCS
	_hoops_GACR *dl;
	H3D_Display_List *odl = null;
	bool _hoops_RACR = _hoops_AACR(nr, &_hoops_HRR->_hoops_PACR, &dl, &odl, H3D_DL_SHADOW_MAP);

	// _hoops_IPCS _hoops_AIRI _hoops_HIGR _hoops_RPP _hoops_IGIR _hoops_SHPH.
	if (!_hoops_RACR &&
		(odl->item._hoops_HRR._hoops_HAP != _hoops_IACS)) {
		HD_Queue_Destroy_List (odl, true);
		_hoops_RACR = _hoops_AACR(nr, &_hoops_HRR->_hoops_PACR, &dl, &odl, H3D_DL_SHADOW_MAP);
	}

	// _hoops_CPCS _hoops_SPCS _hoops_PSCA _hoops_RPP _hoops_IGIR _hoops_SHPH.
	if (h3ddata->_hoops_PI._hoops_HAP != _hoops_IACS) {
		_hoops_HP (h3ddata->_hoops_PI.depth_buffer);
		_hoops_HP (h3ddata->_hoops_PI.dummy_buffer);
		h3ddata->_hoops_PI._hoops_HAP = 0;
	}

	// _hoops_HR _hoops_IR
	bool result = true;

	// _hoops_GGAP _hoops_GHCS _hoops_IIGR _hoops_PA _hoops_SR _hoops_GA'_hoops_RA _hoops_AIAH _hoops_HS. _hoops_HAIC _hoops_RGAR _hoops_IPCA _hoops_CCA _hoops_IRS _hoops_IHIR _hoops_ARP.
	do {
		// _hoops_PHAA _hoops_ARPR _hoops_RH _hoops_APR _hoops_RPP _hoops_RGHP
		if (!odl->item._hoops_HRR.id) {
			result = h3ddata->_hoops_GSCR->CreateTexture(_hoops_IACS, _hoops_IACS, 1,
				_hoops_PACS, _hoops_AACS, &odl->item._hoops_HRR.id);
		}

		// _hoops_SPAA _hoops_RH _hoops_HCH/_hoops_SPCS _hoops_SRHR _hoops_GAR _hoops_RGHP. _hoops_PGPR _hoops_SPR _hoops_SIGR _hoops_IH _hoops_HCR _hoops_HPR.
		if (result) {
			if (h3ddata->_hoops_SRP && !h3ddata->_hoops_PI.dummy_buffer) {
				// _hoops_GISA _hoops_GCSP _hoops_SPCS _hoops_SRHR
				result = h3ddata->_hoops_GSCR->CreateRenderTarget(_hoops_IACS, _hoops_IACS, H3DTEXUSAGE_RENDERTARGET,
					H3DFMT_A8R8G8B8, 0, &h3ddata->_hoops_PI.dummy_buffer);
			}
			if (!h3ddata->_hoops_SRP && !h3ddata->_hoops_PI.depth_buffer) {
				// _hoops_GISA _hoops_GCSP _hoops_HCH _hoops_SRHR
				result = h3ddata->_hoops_GSCR->CreateRenderTarget(_hoops_IACS, _hoops_IACS, H3DTEXUSAGE_DEPTHSTENCIL,
					H3DFMT_D24S8, 0, &h3ddata->_hoops_PI.depth_buffer);
			}
		}

		// _hoops_RHCS _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_SR _hoops_PAH _hoops_HSCR _hoops_RH _hoops_AHCS _hoops_PRRP
		if (result) {
			if (h3ddata->_hoops_SRP) {
				result = h3ddata->_hoops_GSCR->_hoops_PHCS(
					h3ddata->_hoops_PI.dummy_buffer, odl->item._hoops_HRR.id);
			}
			else {
				result = h3ddata->_hoops_GSCR->_hoops_PHCS(
					odl->item._hoops_HRR.id, h3ddata->_hoops_PI.depth_buffer);
			}
		}

		if (!result) {

			// _hoops_SP _hoops_CPS _hoops_GH
			_hoops_HP(odl->item._hoops_HRR.id);
			_hoops_HP(h3ddata->_hoops_PI.dummy_buffer);
			_hoops_HP(h3ddata->_hoops_PI.depth_buffer);
			h3ddata->_hoops_PI._hoops_HAP = 0;

			// _hoops_HHCS _hoops_HRHC _hoops_IGIR
			_hoops_IACS /= 2;

			// _hoops_GSIH _hoops_SGS _hoops_SR _hoops_IHCS _hoops_ISSC _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_HPPR _hoops_RH _hoops_CHCS _hoops_SHCS _hoops_GICS.
			h3ddata->_hoops_PI._hoops_PPCS = _hoops_IACS;
		}

	} while (!result && _hoops_IACS >= 512);

	// _hoops_GSIH _hoops_PSPP _hoops_PGRR
	odl->item._hoops_HRR._hoops_HAP = _hoops_IACS;
	h3ddata->_hoops_PI._hoops_HAP = _hoops_IACS;

	// _hoops_AP. _hoops_RICS _hoops_ISSC _hoops_AIRI _hoops_HIGR _hoops_RPP _hoops_SCH _hoops_AICS.
	return result ? odl : null;
}

/**
 _hoops_SRAC: _hoops_GISA _hoops_RCAR _hoops_ACAR.
 */
void HC_CDECL _hoops_PICS (
	Net_Rendition const &		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path) {
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;
	Net_Rendition &				_hoops_IICS = const_cast<Net_Rendition&>(nr);
	H3DData *					h3ddata = H3DD (dc);
	bool						_hoops_CICS = h3ddata->_hoops_CSC->_hoops_RAIH;
	_hoops_GSAR alter *			_hoops_HRR = nr->_hoops_SRA->_hoops_HRR.current;
	float						bias, _hoops_SICS;

	// (_hoops_GCCS)_hoops_ARPR _hoops_ACAR _hoops_PPR _hoops_SPCS _hoops_PSCA _hoops_RPP _hoops_HAHH.
	H3D_Display_List *odl = _hoops_RACS(nr, _hoops_HRR);

	// _hoops_HAIC'_hoops_RA _hoops_SAS _hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_RGR
	if (!odl)
		return;

	H3D_TRACE(h3ddata, "shadow map draw tree");

	// _hoops_IRSC _hoops_ARI _hoops_GPP, _hoops_SRCH _hoops_RCCS-_hoops_ACCS _hoops_PCCS _hoops_AHI.
	H3D_LONG_OPERATION(dc);

	// _hoops_GISA _hoops_RI _hoops_RPP _hoops_SR _hoops_RRP _hoops_SCH. _hoops_GPRS _hoops_IS _hoops_PHIS, _hoops_SR _hoops_PAH _hoops_HGGC _hoops_SGH _hoops_HPR _hoops_SIHH _hoops_RI.
	if (nr->_hoops_CPP->_hoops_HRR._hoops_HI && !h3ddata->_hoops_PI._hoops_HI)
		h3ddata->_hoops_PI._hoops_HI = _hoops_SHSA(h3ddata, _hoops_GGAA, _hoops_GGAA);

	// _hoops_AHH: _hoops_HCCS: _hoops_CHPR _hoops_SSH-_hoops_CCIR _hoops_ISSC _hoops_IS _hoops_AAPA _hoops_PAPA
	if (h3ddata->_hoops_II._hoops_ICCS > h3ddata->_hoops_II._hoops_CCCS) {
		_hoops_HRR->_hoops_SCCS = h3ddata->_hoops_II._hoops_CCCS;
		_hoops_HRR->_hoops_GSCS = h3ddata->_hoops_II._hoops_ICCS;
	}
	else {
		_hoops_HRR->_hoops_SCCS = 0;
		_hoops_HRR->_hoops_GSCS = 0;
	}

	for (int i = 0; i < _hoops_CIGP; i++) {
		_hoops_ASRP(h3ddata, i);
	}

	// _hoops_RSCS _hoops_APRS _hoops_ASCS
	_hoops_PPRS _hoops_HPRS;
	h3ddata->_hoops_GSCR->_hoops_IPRS(&_hoops_HPRS);

	// _hoops_GCIH _hoops_PSCS _hoops_APR
	h3ddata->_hoops_PI.mode = true;
	h3ddata->_hoops_PI._hoops_CAP = nr->_hoops_CPP->_hoops_HRR._hoops_CAP;
	h3ddata->_hoops_PI._hoops_SAR = false;
	h3ddata->_hoops_PI._hoops_HSCS = odl;
	odl->_hoops_ISCS = _hoops_HRR;

	// _hoops_SIAP _hoops_CSCS _hoops_RCAR _hoops_SARA _hoops_HIHP
	_hoops_GIIH (nr);
	HI_Matmul_44_by_44 (h3ddata->_hoops_SPSR, h3ddata->_hoops_PARA,
			odl->item._hoops_HRR.transform);

	// _hoops_GCRR _hoops_ARCR _hoops_SCGR
	if (h3ddata->_hoops_SRP) {
		ASSERT(h3ddata->_hoops_PI.dummy_buffer);
		ASSERT(!h3ddata->_hoops_PI.depth_buffer);

		h3ddata->_hoops_GSCR->_hoops_GPAP(h3ddata->_hoops_PI.dummy_buffer, odl->item._hoops_HRR.id);
		_hoops_RPAP(h3ddata, false);

		// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_GRP _hoops_HCH _hoops_HH _hoops_CCH, _hoops_ARP _hoops_RH _hoops_SSCS
		//_hoops_CHAA = 0.0075f;
		bias = 0.0001f;
		_hoops_SICS = 4.0f;
		h3ddata->_hoops_GSCR->_hoops_GGSS(bias, _hoops_SICS);
	}
	else {
		ASSERT(!h3ddata->_hoops_PI.dummy_buffer);
		ASSERT(h3ddata->_hoops_PI.depth_buffer);

		h3ddata->_hoops_GSCR->_hoops_GPAP(odl->item._hoops_HRR.id, h3ddata->_hoops_PI.depth_buffer);
		_hoops_RPAP(h3ddata, true);
	}

	ENSURE_DEPTH_MASK(h3ddata, true);
	_hoops_RGSS(h3ddata, 0xff);
	_hoops_GPRP(h3ddata, H3DMASK_RGBA);
	HD_Alternate_Hidden_Root (dc, _hoops_AGSS);

	h3ddata->_hoops_GSCR->Clear(H3DCLEAR_TARGET | H3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);

	// _hoops_SAP _hoops_GPP _hoops_RAR _hoops_PGSS.
	h3ddata->_hoops_PI._hoops_SAR = _hoops_HRR->_hoops_SAR;
	if (h3ddata->_hoops_PI._hoops_SAR) {

		// _hoops_RSCS _hoops_GIGR _hoops_SARA
		_hoops_HHRA const *_hoops_HGSS = nr->transform_rendition->_hoops_SPH;
		_hoops_PRRH(_hoops_HGSS);

		// _hoops_HSRR _hoops_GRR _hoops_ARAA,
		for (int i = 0; i < _hoops_GSAR::_hoops_RSAR; ++i) {
			_hoops_GSAR::_hoops_APCR const & _hoops_PPCR = dc->_hoops_HRR.current->_hoops_HPCR[i];

			// _hoops_CPPP _hoops_IPCR _hoops_SCAR
			if (!_hoops_PPCR._hoops_CPCR)
				continue;

			h3ddata->_hoops_PI._hoops_PCIH = i;

			dc->flags |= _hoops_IGSS;

			//
			// _hoops_PACH _hoops_SARA _hoops_GGR _hoops_GPP _hoops_ARAA.
			//

			// _hoops_SGAA _hoops_IS _hoops_GRAA-_hoops_RRAA _hoops_ARAA.
			float _hoops_PRAA = _hoops_PPCR.size.x;
			float _hoops_HRAA = _hoops_PPCR.size.y;

			// _hoops_AHH: _hoops_HGI _hoops_HRGR _hoops_SHR _hoops_RH _hoops_AAH _hoops_HCSP
			if (1) {
				// _hoops_GCRR _hoops_IRS _hoops_RRAA _hoops_ARAA. _hoops_HGI _hoops_AAAA _hoops_GIH _hoops_RGRR _hoops_PAAA.
				float const _hoops_HAAA = _hoops_IAAA(_hoops_PPCR.size.x, _hoops_PPCR.size.y);
				_hoops_PRAA = _hoops_HRAA = _hoops_HAAA;
			}

			/* _hoops_HCGA _hoops_AIAA-_hoops_PPPR _hoops_HGPC. _hoops_CGSS _hoops_CR _hoops_SR _hoops_HS 2x2 _hoops_RRRH, _hoops_HIS _hoops_AIAA _hoops_GPAA _hoops_GGR _hoops_SPCR _hoops_PPR _hoops_GHCR. */
			float const _hoops_RPAA = 1.0f + (4.0f * _hoops_APAA) / h3ddata->_hoops_PI._hoops_HAP;
			float _hoops_GPCH = 0.5f * (_hoops_PRAA * _hoops_RPAA);
			float _hoops_RPCH = 0.5f * (_hoops_HRAA * _hoops_RPAA);

			/* _hoops_GISA _hoops_SSRS _hoops_SARA _hoops_IH _hoops_RH _hoops_RCAR _hoops_ARAA */

			/* _hoops_SGSS 0 _hoops_GRS _hoops_SHH _hoops_GRSS _hoops_HPP _hoops_RRSS */
			_hoops_HHRA *	_hoops_SPH; 
			ZALLOC(_hoops_SPH, _hoops_HHRA);
			HI_Default_Camera (_hoops_SPH, _hoops_HGSS); 

			/* _hoops_PHIR _hoops_GGR _hoops_CCAH _hoops_PAIP */
			_hoops_SPH->_hoops_ISPA = _hoops_HGSS->_hoops_ISPA * _hoops_GPCH;
			_hoops_SPH->_hoops_SSPA = _hoops_HGSS->_hoops_SSPA * _hoops_RPCH;
			_hoops_SPH->_hoops_ARSS = _hoops_SPH->_hoops_ISPA / _hoops_SPH->_hoops_SRIR;
			_hoops_SPH->_hoops_PRSS = _hoops_SPH->_hoops_SSPA / _hoops_SPH->_hoops_SRIR;
			_hoops_SPH->_hoops_CSIH = 1.0f;

			/* _hoops_HRSS _hoops_SARA'_hoops_GRI _hoops_IRSS _hoops_IS _hoops_ARAA'_hoops_GRI _hoops_CGAA. */
			Vector delta = _hoops_SPH->_hoops_CRSS * _hoops_PPCR._hoops_CPAA.x * _hoops_HGSS->_hoops_ISPA/2 +
						   _hoops_SPH->up_vector * _hoops_PPCR._hoops_CPAA.y * _hoops_HGSS->_hoops_SSPA/2;
			_hoops_SPH->position += delta;
			_hoops_SPH->target += delta;

			/* _hoops_HCGA _hoops_SRSS _hoops_SARA _hoops_IS _hoops_SCII */
			HD_Downwind_Camera (_hoops_IICS, (Attribute *)_hoops_SPH);

			_hoops_IICS->transform_rendition.Renew();

			bool _hoops_GASS = BIT(dc->flags, _hoops_RASS);
			dc->flags &= ~_hoops_RASS;

			_hoops_AASS (_hoops_IICS, _hoops_SRCP, path);

			if (_hoops_GASS)
				dc->flags |= _hoops_RASS;
		}

		// _hoops_CSH _hoops_RPIP _hoops_SIGR
		_hoops_HPRH(_hoops_HGSS);
	}
	else {
		// _hoops_GISP _hoops_PASS
		_hoops_AASS (nr, _hoops_SRCP, path);
	}

	// _hoops_IGSA _hoops_PSCS _hoops_RCAR _hoops_ACAR
	h3ddata->_hoops_PI.mode = false;
	h3ddata->_hoops_PI._hoops_PCIH = 0;
	h3ddata->_hoops_PI._hoops_SAR = false;
	h3ddata->_hoops_PI._hoops_HSCS = null;

	if (dc->_hoops_HASS[dc->_hoops_IASS]) {
		HD_Free_Hidden_List(dc, (_hoops_CASS alter *)dc->_hoops_HASS[dc->_hoops_IASS]);
		dc->_hoops_HASS[dc->_hoops_IASS] = null;
		dc->_hoops_SASS[dc->_hoops_IASS] = 0;
	}
	if (dc->_hoops_GPSS[dc->_hoops_IASS]) {
		HD_Free_Deferred_3D_Geometry (dc->_hoops_GPSS[dc->_hoops_IASS]);
		dc->_hoops_GPSS[dc->_hoops_IASS] = null;
	}
	ASSERT(dc->_hoops_RPSS[dc->_hoops_IASS] == null);
	HD_Alternate_Hidden_Root (dc, _hoops_AGSS);

	// _hoops_IPRP _hoops_RHGS _hoops_ASCS
	h3ddata->_hoops_GSCR->_hoops_CHRS(&_hoops_HPRS);

	// _hoops_IPRP _hoops_RRSP.
	h3ddata->_hoops_GSCR->_hoops_GGSS(0, 0);
	_hoops_RPAP (h3ddata, _hoops_CICS);

	_hoops_APSS (h3ddata);
	for (int i = 0; i < _hoops_CIGP; i++)
		_hoops_ASRP(h3ddata, i);
}



/*****************************************************************************
						_hoops_CRCS: _hoops_PPSS _hoops_SRCS
*****************************************************************************/
/**
 _hoops_SRAC: _hoops_GISP _hoops_HPSS _hoops_RCAR _hoops_PICA _hoops_PPR _hoops_GASH _hoops_IS _hoops_IRS _hoops_SRGS _hoops_SAAP _hoops_HH.
 */
void HC_CDECL _hoops_IPSS (
	Net_Rendition const &		inr,
	_hoops_CRCP const *				start,
	_hoops_HICS const &		path) {
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;
	_hoops_CPSS alter *		_hoops_SPSS = dc->_hoops_GHSS.current;
	H3DData *					h3ddata = H3DD (dc);
	_hoops_GACR alter *		dl;
	H3D_Display_List alter *	odl=0;
	bool						_hoops_RACR;
	H3DTexture *				texture = null;
	int							_hoops_RHSS = h3ddata->yfudge;
	H3DBLEND 					_hoops_AHSS = h3ddata->_hoops_CSC->_hoops_PHSS;
	H3DBLEND 					_hoops_HHSS = h3ddata->_hoops_CSC->_hoops_IHSS;

	if (h3ddata->_hoops_PI.mode ||
		BIT(dc->flags, _hoops_CHSI)) {
		_hoops_SPSS->_hoops_CHSS = 0;
		return;
	}

	H3D_TRACE(h3ddata, "simple_shadow_draw_tree");

	//
	// _hoops_ACGR _hoops_PAR _hoops_ARPR _hoops_RCAR _hoops_HH
	//

	// _hoops_AHH: _hoops_SHHH _hoops_SHH _hoops_SHSS _hoops_IS _hoops_HGCR _hoops_RGR _hoops_HII _hoops_RH _hoops_GISS, _hoops_HIH _hoops_PSCR _hoops_CPS _hoops_IISA _hoops_GGSR _hoops_RISS...
	unsigned long const _hoops_HAP = 1024;

	// _hoops_AISS _hoops_RGR _hoops_RCAR _hoops_HS _hoops_IRS _hoops_HH _hoops_AIAH?
	if (_hoops_SPSS->texture)
	{
		// _hoops_SHHH _hoops_SHH _hoops_PISS _hoops_PPR _hoops_HISS _hoops_IS _hoops_IRS _hoops_RAPA _hoops_HH _hoops_AIAH (_hoops_CACH _hoops_CAPP)
		ASSERT(_hoops_SPSS->texture->_hoops_RHGH);
		_hoops_RACR = _hoops_AACR(nr, &_hoops_SPSS->texture->_hoops_RHGH->_hoops_GAHA, &dl, &odl, H3D_DL_TEXTURE);

		// _hoops_IISS _hoops_HS _hoops_CISS _hoops_AIRI _hoops_HIGR _hoops_GGR _hoops_SISS _hoops_HIAP...
		if (odl->item.texture.id)
		{
			// _hoops_SSAP _hoops_HH
			ASSERT(odl->item.texture.id);

			// _hoops_HCIC _hoops_RH _hoops_GCSS _hoops_HH _hoops_RH _hoops_RPHR _hoops_IGIR?
			if (odl->item.texture.id->_hoops_IRRP != (int) _hoops_HAP || odl->item.texture.id->_hoops_CRRP != (int) _hoops_HAP)
				// _hoops_CSH: _hoops_CPCS _hoops_PPR _hoops_RCSS _hoops_HII _hoops_AIRI _hoops_HIGR
				_hoops_HP(odl->item.texture.id);

			// _hoops_SGPR _hoops_RGR, _hoops_PAR _hoops_IRAP _hoops_RPP _hoops_SR _hoops_SAHR _hoops_ACSS _hoops_SCH.
			texture = odl->item.texture.id;
		}
	}

	// _hoops_CGP _hoops_SR _hoops_HGGC _hoops_GA'_hoops_RA _hoops_HS _hoops_IRS _hoops_HH
	if (!texture)
	{
		// _hoops_GISA _hoops_IRS _hoops_CCAH _hoops_HH
		h3ddata->_hoops_GSCR->CreateTexture(_hoops_HAP, _hoops_HAP, 1,
			H3DTEXUSAGE_RENDERTARGET, H3DFMT_A8R8G8B8, (H3DTexture **)&texture);
	}

	// _hoops_CGP _hoops_RAS _hoops_HCR _hoops_SGS, _hoops_SR _hoops_GCSH _hoops_HS _hoops_IRS _hoops_HH...
	if (texture)
	{
		//
		// _hoops_PCSS _hoops_RCAR _hoops_HH
		//

		// _hoops_IRSC _hoops_ARI _hoops_GPP, _hoops_SRCH _hoops_RCCS-_hoops_ACCS _hoops_PCCS _hoops_AHI.
		H3D_LONG_OPERATION(dc);

		// _hoops_RSCS _hoops_HCSS _hoops_PPR _hoops_ICIH
		_hoops_PPRS _hoops_HPRS;
		h3ddata->_hoops_GSCR->_hoops_IPRS(&_hoops_HPRS);

		// _hoops_ICSS _hoops_RCAR _hoops_HH _hoops_RPP _hoops_SCH _hoops_HRGR _hoops_ARP, _hoops_PAR _hoops_SR _hoops_PAH'_hoops_RA _hoops_SRGS _hoops_IS _hoops_SCH!
		_hoops_APSS (h3ddata);
		_hoops_ASRP(h3ddata, 0);

		// _hoops_PCSS _hoops_GISH (_hoops_APRP _hoops_GPP _hoops_PGS) _hoops_RGAR _hoops_IH _hoops_RCAR
		h3ddata->_hoops_GSCR->_hoops_GPAP(texture);

		// _hoops_GCRR _hoops_RCRR _hoops_SR _hoops_PAH _hoops_IGRC _hoops_SCAC _hoops_RH _hoops_SAAP
		_hoops_RPAP(h3ddata, TRUE);
		_hoops_GPRP(h3ddata, H3DMASK_RGBA);

		// _hoops_CCSS _hoops_IS _hoops_RRH _hoops_AIIR _hoops_AGSR _hoops_SR _hoops_RRP _hoops_IS _hoops_HHSP _hoops_AIIR _hoops_IH _hoops_RH _hoops_SCAC _hoops_IS _hoops_SCSS.
		ENSURE_TRANSPARENCY(h3ddata, FALSE);
		_hoops_ICHH(h3ddata, FALSE);

		// _hoops_ICAH _hoops_IS _hoops_SCAC _hoops_CR _hoops_IHGP _hoops_RCAR _hoops_RRGR _hoops_GSSS _hoops_IRS _hoops_PGS _hoops_RRH _hoops_IGHP
		h3ddata->_hoops_GSCR->Clear(H3DCLEAR_TARGET, 0x00ffffff, 0, 0);

		// _hoops_RSSS _hoops_RCAR _hoops_CCH
		h3ddata->_hoops_CHSP._hoops_HAP = _hoops_HAP;
		h3ddata->_hoops_CHSP.mode = TRUE;

		// _hoops_CAIP'_hoops_RA _hoops_ASSS _hoops_RHPP _hoops_IS _hoops_CAH _hoops_RRH _hoops_CPAP _hoops_RHSP _hoops_RCAR _hoops_SRGS - _hoops_SR _hoops_RRP _hoops_SCH.
		bool _hoops_PSSS = h3ddata->_hoops_GSA;
		h3ddata->_hoops_GSA = TRUE;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_SRI == _hoops_PIII)
			nr.Modify()->_hoops_CPP.Modify()->_hoops_PRH._hoops_SRI = _hoops_HSSS;

		_hoops_PPRP(h3ddata, H3DBLEND_ONE, H3DBLEND_INVSRCALPHA);

		h3ddata->yfudge = _hoops_HAP - 1;
		bool _hoops_GASS = BIT(dc->flags, _hoops_RASS);
		dc->flags &= ~_hoops_RASS;
		{
			// _hoops_ISSS _hoops_IS _hoops_CSSS _hoops_IS _hoops_PPIP _hoops_PPR _hoops_PGSA _hoops_RH _hoops_RCAR - _hoops_RGR _hoops_GRS _hoops_ASAR-_hoops_SSSS _hoops_RH _hoops_RHPP _hoops_GGGGR.
			H3D_TRACE(h3ddata, "Create shadow");
			_hoops_AASS(nr, start, path);
		}
		if (_hoops_GASS)
			dc->flags |= _hoops_RASS;

		h3ddata->yfudge = _hoops_RHSS;
		_hoops_PPRP(h3ddata, _hoops_AHSS, _hoops_HHSS);

		// _hoops_IPRP _hoops_CGSI _hoops_SR _hoops_RGGGR _hoops_CCA
		h3ddata->_hoops_GSA = _hoops_PSSS;

		// _hoops_AGGGR _hoops_RCAR _hoops_CCH
		h3ddata->_hoops_CHSP.mode = FALSE;

		// _hoops_IPRP _hoops_SRGS _hoops_SAAP
		h3ddata->_hoops_GSCR->_hoops_CHRS(&_hoops_HPRS);

		_hoops_PPRP(h3ddata, H3DBLEND_SRCALPHA, H3DBLEND_INVSRCALPHA);

		//
		// _hoops_PGGGR _hoops_HAIP _hoops_RH _hoops_RCAR
		//

		int const _hoops_HGGGR = nr->_hoops_CPP->_hoops_GHSS._hoops_IGGGR;
		if (_hoops_HGGGR > 0)
		{
			// _hoops_SRIP _hoops_GGSR _hoops_RH _hoops_RCAR
			if (h3ddata->post->_hoops_GGPP()) {

				h3ddata->post->_hoops_CGGGR(texture, _hoops_HGGGR);

				// _hoops_SP _hoops_GH
				h3ddata->post->_hoops_PRHP();
			}
		}

		//
		// _hoops_IARP _hoops_RAPA _hoops_HH _hoops_IS _hoops_AGAH _hoops_HH
		//

		// _hoops_CGP _hoops_IRS _hoops_RCAR _hoops_CSAP _hoops_SPIP...
		if (_hoops_SPSS->image) {
			// _hoops_SGGGR _hoops_RH _hoops_GRGGR _hoops_PPR _hoops_RRGGR _hoops_CSRA _hoops_GRS _hoops_HHSA _hoops_CSSS _hoops_IS _hoops_ARGGR _hoops_HH _hoops_PCRR _hoops_HIS _hoops_SGS _hoops_RH
			// _hoops_IRGP _hoops_PRGGR _hoops_IIGR _hoops_ISCP _hoops_HH _hoops_HRGR _hoops_SGGA _hoops_IS _hoops_RH _hoops_RCAR _hoops_HSSP _hoops_GAR _hoops_PHRI _hoops_SR'_hoops_GHGP _hoops_CPHR _hoops_RH _hoops_SHSC
			// _hoops_AHAP _hoops_HPGR _hoops_RH _hoops_RPHR _hoops_RAAA.
			_hoops_SPSS->_hoops_CHRP *= (float)_hoops_SPSS->image->width / _hoops_HAP;
			_hoops_SPSS->_hoops_SHRP *= (float)_hoops_SPSS->image->height / _hoops_HAP;

			// _hoops_GISA _hoops_HH _hoops_GPP _hoops_HRGGR
			if (_hoops_SPSS->texture == null)
				// _hoops_GISA _hoops_AGAH _hoops_HH _hoops_PPR _hoops_HSCR _hoops_RAPA _hoops_HH _hoops_IS _hoops_SCH.
				_hoops_SPSS->texture = HI_Define_Shadow_Texture(dc->_hoops_RIGC, _hoops_SPSS->image);

			// _hoops_RRAH _hoops_SCH
			if (_hoops_SPSS->texture->_hoops_RHGH == null)
			{
				// _hoops_IRGGR _hoops_GPP _hoops_ARIP _hoops_IIGR _hoops_CRGGR()
				int _hoops_ICGH = 4096;
				int _hoops_CCGH = 16;
				HD_Activate_Texture_Image(nr, _hoops_SPSS->texture, 0, _hoops_CCGH, _hoops_ICGH, _hoops_CCGH, _hoops_ICGH);
			}

			// _hoops_CHSR _hoops_SRGGR _hoops_RH _hoops_AIRI _hoops_HIGR
			_hoops_RACR = _hoops_AACR(nr, &_hoops_SPSS->texture->_hoops_RHGH->_hoops_GAHA, &dl, &odl, H3D_DL_TEXTURE);

			// _hoops_GAGGR _hoops_SCH _hoops_HGAS?
			if (odl->item.texture.id != texture)
			{
				// _hoops_RAGGR _hoops_RAPA _hoops_HH, _hoops_GA'_hoops_RA _hoops_AGRP _hoops_AAGGR _hoops_CR _hoops_SCH _hoops_AIAH _hoops_SSCP _hoops_SPR _hoops_PAGGR.
				_hoops_HP(odl->item.texture.id);
				odl->item.texture.id = texture;

				// _hoops_ICAH _hoops_IS _hoops_HAGGR _hoops_RGR _hoops_HH _hoops_GPP _hoops_SISS _hoops_HIAP.
				odl->item.texture._hoops_IAGGR = true;

				// _hoops_CHSR _hoops_CAGGR _hoops_RH _hoops_RCAR _hoops_HIS _hoops_SCH _hoops_SAGGR _hoops_GPGGR _hoops_GICS
				odl->_hoops_ISCS = _hoops_SPSS;
			}

			// _hoops_RPGGR _hoops_IH _hoops_SGH
			_hoops_SPSS->valid = true;
			_hoops_SPSS->_hoops_CHSS = true;
			_hoops_SPSS->_hoops_APGGR = true;
		}
		else
		{
			// _hoops_ARRP _hoops_IS _hoops_HSCR _hoops_IS. _hoops_PPGGR _hoops_RH _hoops_HH
			_hoops_HP(texture);

			if (odl) {
				odl->item.texture.id = null;
				HD_Queue_Destroy_List (odl, true);
			}

			// _hoops_HPGGR _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_HPPR _hoops_IS _hoops_IPGGR _hoops_SIHH _hoops_SASI _hoops_CPGGR
			_hoops_SPSS->_hoops_CHSS = true;
		}
	}
}


/*****************************************************************************
						_hoops_CRCS: _hoops_SPC _hoops_SPGGR
*****************************************************************************/

void HC_CDECL _hoops_GHGGR (
	Net_Rendition const &			nr,
	_hoops_CRCP const *					start,
	_hoops_HICS const &			path,
	float							_hoops_IRIR,
	float							radius) {
	UNREFERENCED(radius);
	Display_Context alter *			dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_GCIR const &	visual = nr->_hoops_CPP;
	_hoops_ARPA const *					plane = &visual->_hoops_RHGGR.plane;
	H3DData *						h3ddata = H3DD (dc);
	H3DPost *						post = h3ddata->post;

	H3D_TRACE(h3ddata, "reflection_plane_draw_tree");

	// _hoops_SIAP _hoops_SCIA-_hoops_PAPA _hoops_AHGGR
	_hoops_GIIH (nr);
	float _hoops_PHGGR[16];
	HI_Matmul_44_by_44 (h3ddata->_hoops_SPSR, h3ddata->_hoops_PARA, _hoops_PHGGR);

//#_hoops_PPIP _hoops_HHGGR
#ifdef _hoops_IHGGR
	//
	// _hoops_CHGGR: _hoops_GISA _hoops_IRS _hoops_PH _hoops_ARCR
	//
	if (!h3ddata->_hoops_SH._hoops_GI)
	{
		h3ddata->pDevice->CreateTexture(128, 128, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &h3ddata->_hoops_SH._hoops_GI, null);
		if (h3ddata->_hoops_SH._hoops_GI)
		{
			D3DLOCKED_RECT _hoops_HC;
			if (SUCCEEDED(h3ddata->_hoops_SH._hoops_GI->LockRect(0, &_hoops_HC, null, 0)))
			{
				unsigned char *_hoops_SHGGR = static_cast<unsigned char *>(_hoops_HC.pBits);
				for (int y = 0; y < 128; ++y)
				{
					unsigned char *row = _hoops_SHGGR + _hoops_HC.Pitch * y;

					// _hoops_RSRP _hoops_HH _hoops_GIGGR
					float v = y / 128.0f;

					// _hoops_RSRP _hoops_IHSR _hoops_IIGR _hoops_RIGGR _hoops_GSSR
					float ny = 0.5f * sin(v * 2.0f * 3.1415927f);

					for (int x = 0; x < 128; ++x)
					{
						// _hoops_GSRP _hoops_HH _hoops_GIGGR
						float u = x / 128.0f;

						// _hoops_GSRP _hoops_IHSR _hoops_IIGR _hoops_RIGGR _hoops_GSSR
						float nx = 0.5f * cos(u * 2.0f * 3.1415927f);

						// _hoops_AIGGR (_hoops_GGSR) _hoops_IHSR _hoops_IIGR _hoops_RIGGR _hoops_GSSR
						ASSERT(nx*nx + ny*ny <= 1);
						float nz = sqrt(1-nx*nx-ny*ny);

						unsigned char *pixel = row + 4*x;

						// _hoops_GPGP _hoops_AGR _hoops_PIGGR
						pixel[0] = (unsigned char)(255.0f * (nz * 0.5f + 0.5f));
						pixel[1] = (unsigned char)(255.0f * (ny * 0.5f + 0.5f));
						pixel[2] = (unsigned char)(255.0f * (nx * 0.5f + 0.5f));
						pixel[3] = (unsigned char)255;
					}
				}

				h3ddata->_hoops_SH._hoops_GI->UnlockRect(0);
			}
		}
	}
	// _hoops_HIGGR _hoops_CHGGR
#endif

	// _hoops_GISA/_hoops_IIGGR _hoops_IRS _hoops_RHAA _hoops_HH _hoops_PPR _hoops_CIGGR _hoops_HCH _hoops_SRHR _hoops_IIGR _hoops_RH _hoops_RPHR _hoops_IGIR _hoops_PPR _hoops_RPCC.
	H3DTexture *_hoops_SIGGR = post->_hoops_IAAP(h3ddata->render_target->_hoops_IRRP, h3ddata->render_target->_hoops_CRRP, H3DFMT_A8R8G8B8);
	H3DRenderTarget *_hoops_GCGGR = post->_hoops_RCGGR(h3ddata->render_target->_hoops_IRRP, h3ddata->render_target->_hoops_CRRP, H3DFMT_D24S8, false);

	if (_hoops_SIGGR && _hoops_GCGGR)
	{
		// _hoops_IRSC _hoops_ARI _hoops_GPP, _hoops_SRCH _hoops_RCCS-_hoops_ACCS _hoops_PCCS _hoops_AHI.
		H3D_LONG_OPERATION(dc);

		// _hoops_SIAP _hoops_IS _hoops_RGR _hoops_ACGGR
		_hoops_PPRS _hoops_HPRS;
		h3ddata->_hoops_GSCR->_hoops_IPRS(&_hoops_HPRS);
		h3ddata->_hoops_GSCR->_hoops_GPAP(_hoops_SIGGR, _hoops_GCGGR);

		// _hoops_GCRR _hoops_RCRR _hoops_SCAC _hoops_PCGGR
		_hoops_RPAP(h3ddata, TRUE);
		_hoops_GPRP(h3ddata, H3DMASK_RGBA);
		ENSURE_DEPTH_MASK(h3ddata, TRUE);
		_hoops_RGSS(h3ddata, 0xff);

		// _hoops_CCSS _hoops_IS _hoops_RRH _hoops_AIIR _hoops_AGSR _hoops_SR _hoops_RRP _hoops_IS _hoops_HHSP _hoops_AIIR _hoops_IH _hoops_RH _hoops_SCAC _hoops_IS _hoops_SCSS.
		ENSURE_TRANSPARENCY(h3ddata, FALSE);

		// _hoops_AGGA _hoops_SCAC _hoops_AAGS _hoops_PPR _hoops_RH _hoops_CCAH _hoops_HCH/_hoops_APSP _hoops_SRHR
		h3ddata->_hoops_GSCR->Clear(H3DCLEAR_TARGET|H3DCLEAR_ZBUFFER|H3DCLEAR_STENCIL, 0x00000000, 1.0f, 0, true);

		// _hoops_PHIR _hoops_GGR _hoops_IPPA
		_hoops_RRPA(nr, plane, &h3ddata->_hoops_SH._hoops_AIPA.plane);

		// _hoops_SGAA _hoops_IS _hoops_PSP _hoops_HCGGR
		h3ddata->_hoops_SH._hoops_AIPA.scale = 0.0f;
		h3ddata->_hoops_SH._hoops_AIPA.bias = 0.0f;
		if (visual->_hoops_RHGGR._hoops_SIRH) {
			// _hoops_CAAA _hoops_GHC _hoops_CRGR _hoops_CSRA _hoops_PPR _hoops_CHAA _hoops_HIS _hoops_RH _hoops_CI _hoops_RRP _hoops_RGAR _hoops_SGH _hoops_IRS _hoops_ICGGR _hoops_CCGGR.
			const float h = visual->_hoops_RHGGR.hither;
			const float y = visual->_hoops_RHGGR.yon;
			const float d = y - h;
			if (d > 1e-6f)
			{
				// _hoops_IPHH
				//
				// _hoops_IRS = (_hoops_SSH - _hoops_GGHR) / (_hoops_HAPC - _hoops_GGHR)
				//
				// _hoops_CRGR
				//
				// _hoops_IRS = _hoops_SCGGR + _hoops_GSGGR
				h3ddata->_hoops_SH._hoops_AIPA.scale = 1.0f / d;
				h3ddata->_hoops_SH._hoops_AIPA.bias = -h / d;
			}
		}

		// _hoops_SGPR _hoops_RSGGR _hoops_AIIR
		_hoops_PPRP(h3ddata, H3DBLEND_ONE, H3DBLEND_INVSRCALPHA);

		// _hoops_ASGGR _hoops_IS _hoops_GASH _hoops_PISI _hoops_CPAP
		HD_Alternate_Hidden_Root (dc, _hoops_PSGGR);

		// _hoops_GISP _hoops_RH _hoops_CHIR
		h3ddata->_hoops_SH.mode = true;
		_hoops_AASS (nr, start, path);

		// _hoops_HPPP _hoops_GII _hoops_PISI (_hoops_IAS._hoops_ISHI. _hoops_RRH) _hoops_CPAP _hoops_CRGR _hoops_RH _hoops_CHIR
		int		count = 0;
		while (BIT (dc->_hoops_IPCI->mode, _hoops_HSGGR|_hoops_ISGGR|_hoops_CSGGR)) {
			_hoops_IGRS (dc);
			++count;
		}

		if (dc->_hoops_HASS[dc->_hoops_IASS] != null)
			HD_See_Whats_Hidden (nr);
		if (dc->_hoops_GPSS[dc->_hoops_IASS] != null)
			_hoops_SSGGR (dc);
		if (dc->_hoops_RPSS[dc->_hoops_IASS] != null) {
			HD_Draw_Deferred_3D_Geometry (dc->_hoops_RPSS[dc->_hoops_IASS], true);
			HD_Free_Deferred_3D_Geometry (dc->_hoops_RPSS[dc->_hoops_IASS]);
			dc->_hoops_RPSS[dc->_hoops_IASS] = null;
		}

		while (count-- > 0)
			_hoops_SGRS (dc);

		h3ddata->_hoops_SH.mode = false;

		//_hoops_PHIH _hoops_GGRGR-_hoops_APRS _hoops_PISI _hoops_CPAP _hoops_CRGR _hoops_RGCI _hoops_RHGS _hoops_GISR
		HD_Alternate_Hidden_Root (dc, _hoops_PSGGR);

		// _hoops_IPRP _hoops_ACGGR
		h3ddata->_hoops_GSCR->_hoops_CHRS(&_hoops_HPRS, false);

		// _hoops_AGGA _hoops_HPPP _hoops_RGRGR _hoops_CHIR, _hoops_PPR _hoops_GHAA _hoops_SCH.
		if (post->_hoops_GGPP())
		{
			// _hoops_SGAA _hoops_IS _hoops_ASCA _hoops_GGR 2D
			float const *transform = NULL;

			// _hoops_AGSH _hoops_SR _hoops_HCRP _hoops_RH _hoops_CHIR?
			if (visual->_hoops_RHGGR._hoops_IGGGR > 0) {
				post->_hoops_HASH(_hoops_SIGGR, visual->_hoops_RHGGR._hoops_IGGGR);
			}

			// _hoops_IPRP _hoops_HGSI _hoops_HCH _hoops_SRHR _hoops_IH _hoops_AGRGR
			h3ddata->_hoops_GSCR->_hoops_GPAP(
				(H3DRenderTarget *) _hoops_HPRS._hoops_PGRGR[0],
				h3ddata->depth_stencil,
				(H3DRenderTarget *) _hoops_HPRS._hoops_PGRGR[1],
				(H3DRenderTarget *) _hoops_HPRS._hoops_PGRGR[2],
				(H3DRenderTarget *) _hoops_HPRS._hoops_PGRGR[3]);


			if (H3DConstantTable *_hoops_AIPA = post->_hoops_PIGP(transform ? H3DPost::_hoops_HGRGR : H3DPost::_hoops_HIGP, H3DPost::_hoops_IGRGR))
			{
#ifdef _hoops_IHGGR

				//
				// _hoops_AHH: _hoops_HGI _hoops_CGRGR _hoops_IRHS _hoops_IS _hoops_SHH _hoops_SGRGR _hoops_IS _hoops_ASAR-_hoops_HHPR _hoops_GRRGR. _hoops_RRRGR _hoops_HSAR _hoops_ASCA 3D _hoops_CPAP, _hoops_SR _hoops_RRP
				// _hoops_IS _hoops_PGSA _hoops_RH _hoops_ASGH 2D _hoops_ARRGR _hoops_PPR _hoops_ISSC-_hoops_PRRGR _hoops_CIAA _hoops_RH _hoops_IPPA _hoops_GGR _hoops_RH _hoops_CI _hoops_IS _hoops_HRRGR _hoops_RH _hoops_IRRGR
				// _hoops_PCRR.
				//

				//
				// _hoops_GAGA _hoops_HII _hoops_IPPA _hoops_GC _hoops_IS _hoops_GSSP _hoops_GC
				//

				// _hoops_SPGGR _hoops_IRSS _hoops_GGR _hoops_CRRGR
				D3DXVECTOR3 i, j, k;
				k.x = plane->a;
				k.y = plane->b;
				k.z = plane->c;

				D3DXVECTOR3 const _hoops_SRRGR(1,0,0);
				D3DXVECTOR3 const _hoops_GARGR(0,1,0);
				D3DXVECTOR3 const _hoops_RARGR(0,0,1);

				// _hoops_ACGR _hoops_IRS _hoops_GHRP _hoops_AARGR _hoops_IS _hoops_CRRGR
				D3DXVec3Cross(&i, &_hoops_SRRGR, &k);
				if (D3DXVec3LengthSq(&i) < 0.0001f)
				{
					D3DXVec3Cross(&i, &_hoops_GARGR, &k);
					if (D3DXVec3LengthSq(&i) < 0.0001f)
					{
						D3DXVec3Cross(&i, &_hoops_RARGR, &k);
						ASSERT(D3DXVec3LengthSq(&i) > 0.0001f);
					}
				}

				// _hoops_PARGR _hoops_RH _hoops_HARGR
				D3DXVec3Cross(&j, &k, &i);

				// _hoops_IISR _hoops_RSGA _hoops_PGAP _hoops_ACAR (_hoops_SISR,_hoops_HAPC) _hoops_IS (_hoops_IARGR._hoops_HAS, _hoops_HPPC._hoops_PPHR)
				D3DXMATRIX m;
				m._11 = i.x; m._12 = i.y; m._13 = i.z; m._14 = 0;
				m._21 = j.x; m._22 = j.y; m._23 = j.z; m._24 = 0;
				m._31 = k.x; m._32 = k.y; m._33 = k.z; m._34 = 0;
				m._41 = plane->a * -plane->d;
				m._42 = plane->b * -plane->d;
				m._43 = plane->c * -plane->d;
				m._44 = 1;

				// _hoops_SSIR _hoops_RGR _hoops_CRGR _hoops_RH _hoops_CARGR _hoops_HIHP
				D3DXMatrixMultiply((D3DXMATRIX*)_hoops_PHGGR, &m, (D3DXMATRIX*)_hoops_PHGGR);

				// _hoops_GPPR _hoops_IPPA _hoops_GH
				float const scale = 500.0f * radius;
				D3DXMatrixScaling(&m, scale, scale, scale);
				D3DXMatrixMultiply((D3DXMATRIX*)_hoops_PHGGR, &m, (D3DXMATRIX*)_hoops_PHGGR);

				// _hoops_SGPR _hoops_RGR _hoops_HIHP
				transform = _hoops_PHGGR;

				// _hoops_SARGR: _hoops_SGPR _hoops_GPRGR _hoops_PH _hoops_ARCR, _hoops_SPHR _hoops_HGCR _hoops_HII _hoops_RPRGR _hoops_RRGR.
				_hoops_AIPA->SetFloat(h3ddata->pDevice, "BumpSize", 1.0f / 500.0f);
				_hoops_AIPA->SetFloat(h3ddata->pDevice, "BumpStrength", 4.0f / desc.Width);
				const unsigned long _hoops_APRGR = _hoops_AIPA->GetSamplerIndex("NormalMapSampler");
				_hoops_SCCR(h3ddata, _hoops_APRGR, h3ddata->_hoops_SH._hoops_GI);
				_hoops_GRPA(h3ddata, _hoops_PCI, D3DTEXF_LINEAR, D3DTEXF_LINEAR, D3DTADDRESS_WRAP);

#endif // _hoops_HHGGR

				// _hoops_IARP _hoops_PPRGR
				_hoops_AIPA->SetFloat("Opacity", _hoops_IRIR);

				// _hoops_IARP _hoops_AI
				const unsigned long _hoops_PCI = _hoops_AIPA->GetSamplerIndex("ReflectionSampler");
				_hoops_SCCR(h3ddata, _hoops_PCI, _hoops_SIGGR);

				// _hoops_SIIR _hoops_IH _hoops_RSGGR _hoops_AIIR
				ENSURE_TRANSPARENCY(h3ddata, TRUE);
				_hoops_PPRP(h3ddata, H3DBLEND_ONE, H3DBLEND_INVSRCALPHA);
				_hoops_PISP(h3ddata, TRUE);
				_hoops_GPRP(h3ddata, H3DMASK_RGB);

				// _hoops_GISP _hoops_CCA _hoops_CI
				post->_hoops_HPRP(h3ddata->render_target, H3DPost::_hoops_IGRGR, h3ddata->_hoops_CSC->_hoops_GSCH[1], transform, _hoops_SIGGR);

				// _hoops_SP _hoops_GH _hoops_AI
				_hoops_ASRP(h3ddata, _hoops_PCI);
#ifdef _hoops_IHGGR
				_hoops_ASRP(h3ddata, _hoops_APRGR);
#endif // _hoops_HHGGR
			}

			post->_hoops_PRHP();
		}

		// _hoops_GGAS
		h3ddata->_hoops_GSCR->_hoops_CHRS(&_hoops_HPRS);
	}

	// _hoops_IPRP _hoops_HPRGR _hoops_CPRP
	_hoops_PPRP(h3ddata, H3DBLEND_SRCALPHA, H3DBLEND_INVSRCALPHA);

	// _hoops_AP _hoops_CCA _hoops_CRSH _hoops_PSCA - _hoops_ASRC _hoops_IS _hoops_IHAH
	post->_hoops_HAAP(&_hoops_SIGGR);
	post->_hoops_IPRGR(&_hoops_GCGGR);
}


/*****************************************************************************
*****************************************************************************
			_hoops_GR: _hoops_CPRGR
*****************************************************************************
*****************************************************************************/
#define _hoops_SPRGR(pe,_hoops_GHRGR) (pe->point_count > _hoops_GHRGR)


Polyedge alter *_hoops_RHRGR (
		Net_Rendition const & nr,
		Geometry const *_hoops_RSII,
		bool alter *_hoops_AHRGR,
		bool single,
		RGB const *_hoops_GPCP, 
		bool _hoops_PHRGR)
{
	Display_Context const *dc = nr->_hoops_SRA;
	bool _hoops_SAR = false;
	Geometry const *g;
	Type type;
	_hoops_HHRGR *_hoops_IHRGR = null;
	struct _hoops_CHRGR alter *_hoops_RSHI;
	Polyedge alter *pe, *_hoops_SHRGR, **backlink;
	int _hoops_GIRGR = 0;
	bool _hoops_ARPI = false;
	int i, ii;
	int _hoops_GHRGR;

	if (_hoops_PHRGR)
		_hoops_GHRGR = H3D_Display_List_MAX_SIZE - 200;
	else
		_hoops_GHRGR = 0x7fffffff;


	pe = null;
	_hoops_SHRGR = null;
	backlink = &_hoops_SHRGR;

	/* _hoops_SPIC _hoops_RH _hoops_HIGR _hoops_ARR _hoops_IS _hoops_GRAS _hoops_GHCS _hoops_PGRR */
	g = _hoops_RSII;
	while (g) {
		if (!pe) {
			ZALLOC (pe, Polyedge);
			_hoops_ICAI (pe);
			if (BIT (nr->_hoops_PSGI, T_LINES))
				pe->_hoops_SRHA |= DL_HAS_TRANSPARENCY;
			*backlink = pe;
			if (_hoops_SHRGR == null)
				_hoops_SHRGR = pe;
		}
		type = g->type;
		switch (type) {
			case _hoops_PIIP: {
				ASSERT (!_hoops_IHRGR); //_hoops_RRRC _hoops_PPR _hoops_GRRC _hoops_HS _hoops_IS _hoops_SHH _hoops_CGHI
				do {
					pe->point_count += 2;
					pe->total += 2;
					pe->_hoops_PHHA++;
					g = g->next;
					if (single)
						break;
					if (_hoops_SPRGR(pe, _hoops_GHRGR)) {
						backlink = &pe->next;
						pe = null;
						break;
					}
				} while (g && g->type == type);
			} break;

			case _hoops_HIIP: {
				type = _hoops_IIIP;		// _hoops_HSII _hoops_SAHR _hoops_GAR _hoops_ISII
			} _hoops_HHHI;

			case _hoops_IIIP: {
				Polyline const *ptr;

				ASSERT (!_hoops_IHRGR);
				do {
					ptr = (Polyline const *)g;
					if (ptr->count > 0) {
						pe->point_count += ptr->count;
						pe->total += ptr->count;
						pe->_hoops_PHHA++;
					}
					else if (ptr->count < 0) {
						ASSERT (-ptr->count % 2 == 0);  //_hoops_PIHA _hoops_SHH _hoops_PRGI
						pe->point_count += -ptr->count;
						pe->total += -ptr->count;
						pe->_hoops_PHHA += -ptr->count / 2;
					}
					g = g->next;
					if (single)
						break;
					if (_hoops_SPRGR(pe, _hoops_GHRGR)) {
						backlink = &pe->next;
						pe = null;
						break;
					}
				} while (g && g->type == type);
			} break;

			case _hoops_CHIP:
			case _hoops_GIIP: 
			case _hoops_RIIP:
				_hoops_ARPI = true;
			default:
				_hoops_CSHI (g, type);
		}
		if (single)
			break;
	}

	// _hoops_HA _hoops_HPIH _hoops_GHCS _hoops_RIH _hoops_IS _hoops_RGHH _hoops_GRRC _hoops_PPR _hoops_RRRC
	if (_hoops_ARPI && !_hoops_SAR) {
		g = _hoops_RSII;
		while (g) {
			if (!pe) {
				ZALLOC (pe, Polyedge);
				_hoops_ICAI (pe);
				if (_hoops_RIRGR (nr->_hoops_AHP->_hoops_CHA))
					pe->_hoops_SRHA |= DL_HAS_TRANSPARENCY;
				*backlink = pe;
				if (_hoops_SHRGR == null)
					_hoops_SHRGR = pe;
			}
			type = g->type;
			switch (type) {

				case _hoops_CHIP: {
					_hoops_ARPI = true;
					if (!_hoops_SAR) {
						Polyline alter _hoops_AIRGR;
						_hoops_PIRGR const *ptr;

						if (!_hoops_IHRGR)
							_hoops_IHRGR = POOL_NEW(dc->memory_pool, _hoops_HHRGR)(dc->memory_pool);
						do {
							ptr = (_hoops_PIRGR const *)g;
							if (ptr->control_point_count) {
								ZERO_STRUCT (&_hoops_AIRGR, Polyline);
								HI_Generate_NURBS_Polyline (ptr, 
									&nr->_hoops_ARA->_hoops_APPI, 
									&nr->transform_rendition->matrix->data, 
									&_hoops_AIRGR, 0);
								ALLOC (_hoops_RSHI, struct _hoops_CHRGR);
								_hoops_RSHI->_hoops_SGII = _hoops_AIRGR.allocated;
								_hoops_RSHI->count = _hoops_AIRGR.count;
								_hoops_RSHI->points = _hoops_AIRGR.points;
								_hoops_RSHI->g = g;
								//_hoops_IRAP _hoops_CPAP _hoops_HIRGR _hoops_HHGS _hoops_IH _hoops_GHCP _hoops_IISI
								ASSERT (g != null); 
								_hoops_IHRGR->AddLast(_hoops_RSHI);
								pe->point_count += _hoops_RSHI->count;
								pe->total += _hoops_RSHI->count;
								pe->_hoops_PHHA++;
							}
							g = g->next;
							if (single)
								break;
							if (_hoops_SPRGR(pe, _hoops_GHRGR)) {
								backlink = &pe->next;
								pe = null;
								break;
							}
						} while (g && g->type == type);
					}
					else
						_hoops_CSHI (g, type);
				} break;

				case _hoops_GIIP: 
				case _hoops_RIIP: {
					_hoops_ARPI = true;
					if (!_hoops_SAR) {
						_hoops_GHHI const *ptr;
						float start, end;
						int _hoops_HGII;

						if (!_hoops_IHRGR)
							_hoops_IHRGR = POOL_NEW(dc->memory_pool, _hoops_HHRGR)(dc->memory_pool);
						do {
							ptr = (_hoops_GHHI const *)g;
							ALLOC (_hoops_RSHI, struct _hoops_CHRGR);
							_hoops_HGII = HD_Determine_Elliptical_Res (nr, ptr);
							if (BIT (ptr->_hoops_RRHH, _hoops_SHHI)) {
								Circular_Arc_Lite const *arc;

								arc = (Circular_Arc_Lite const *)ptr;
								start = arc->arc_start;
								end = arc->_hoops_PHHI;
							}
							else {
								Elliptical_Arc const *arc;

								arc = (Elliptical_Arc const *)ptr;
								start = arc->arc_start;
								end = arc->_hoops_PHHI;
								if (end < start)
									end += 1.0f;
							}
							_hoops_RSHI->_hoops_SGII = 10 + (int)((float)_hoops_HGII * Abs (end - start) + 0.5f);
							ALLOC_ARRAY (_hoops_RSHI->points, _hoops_RSHI->_hoops_SGII, Point);
							_hoops_RSHI->count = HD_Generate_Elliptical_Points (nr, ptr, _hoops_HGII, _hoops_RSHI->points);
							_hoops_RSHI->g = g;
							ASSERT (g != null);
							ASSERT (_hoops_RSHI->count <= _hoops_RSHI->_hoops_SGII);
							if (_hoops_RSHI->count >= 2) {
								_hoops_IHRGR->AddLast(_hoops_RSHI);
								pe->point_count += _hoops_RSHI->count;
								pe->total += _hoops_RSHI->count;
								pe->_hoops_PHHA++;
							}
							else {
								FREE_ARRAY (_hoops_RSHI->points, _hoops_RSHI->_hoops_SGII, Point);
								FREE (_hoops_RSHI, struct _hoops_CHRGR);
								_hoops_RSHI = null;
							}
							g = g->next;
							if (single)
								break;
							if (_hoops_SPRGR(pe, _hoops_GHRGR)) {
								backlink = &pe->next;
								pe = null;
								break;
							}
						} while (g && g->type == type);
					}
					else
						_hoops_CSHI (g, type);
				} break;

				default:
					_hoops_CSHI (g, type);
			}
			if (single)
				break;
		}
	}

	if (!pe || pe->point_count == 0) {
		if (pe && _hoops_ISAI (pe) == 0)
			HI_Free_Polyedge(pe);
		if (_hoops_AHRGR)
			*_hoops_AHRGR = _hoops_ARPI;
		if (*backlink == _hoops_SHRGR)
			return null;
		*backlink = null;
	}

	pe = _hoops_SHRGR;
	while (pe) {
		ALLOC_ARRAY (pe->lengths, pe->_hoops_PHHA, int);
		pe->lengths_allocated = pe->_hoops_PHHA;
		pe->_hoops_RAHH |= _hoops_AAHH;

		ALLOC_ARRAY_ALIGNED (pe->points, pe->point_count, Point, 16);
		pe->_hoops_RAHH |= _hoops_AIPI;

		if (_hoops_GPCP) {
			ALLOC_ARRAY_CACHED (pe->_hoops_PCHA, pe->point_count, RGB);
			pe->_hoops_RAHH |= _hoops_PIPI;
		}
		if (nr->_hoops_IRR->_hoops_SRI == _hoops_GAI &&
			BIT (nr->transform_rendition->heuristics, _hoops_IRI)) {
			ALLOC_ARRAY_CACHED (pe->_hoops_CCCP, pe->point_count, float);
			pe->_hoops_RAHH |= _hoops_HIPI;
		}
		pe = pe->next;
	}

	pe = _hoops_SHRGR;
	_hoops_GIRGR = pe->point_count;
	/* _hoops_HIAP _hoops_AGCR _hoops_HSH _hoops_HIS _hoops_SGS _hoops_SR _hoops_PAH _hoops_RPRS _hoops_IIRGR _hoops_PPR _hoops_CIRGR _hoops_GAR 
	 * _hoops_CRPR _hoops_PSPI.  _hoops_SSIA _hoops_CGH _hoops_RCPS _hoops_GGSR _hoops_IS _hoops_RH _hoops_PSHR _hoops_AHAP _hoops_GAR _hoops_ARPP */
	pe->_hoops_PHHA = pe->point_count = 0;
	g = _hoops_RSII;
	/* _hoops_SPIC _hoops_RH _hoops_HIGR _hoops_GICS _hoops_IS _hoops_IPS _hoops_CRGR _hoops_RH _hoops_RSSA _hoops_PPR _hoops_IIRGR _hoops_SIRGR */
	while (g) {
		type = g->type;
		switch (type) {
			case _hoops_PIIP: {
				do {
					Line const *		ptr = (Line const *)g;

					pe->lengths[pe->_hoops_PHHA] = 2;
					_hoops_AIGA (ptr->points, 2, Point, &pe->points[pe->point_count]);
					if (pe->_hoops_CCCP) {
						pe->_hoops_CCCP[pe->point_count] = 
							pe->_hoops_CCCP[pe->point_count+1] = _hoops_SCCP(g->priority,0);
 					}
					if (_hoops_GPCP) {
						for (ii = 0; ii < 2; ii++)
							pe->_hoops_PCHA[pe->point_count + ii] = *_hoops_GPCP;
					}
					pe->point_count += 2;
					pe->_hoops_PHHA++;

					g = g->next;
					if (single)
						break;
					if (_hoops_SPRGR(pe, _hoops_GHRGR)) {
						ASSERT (pe->point_count == _hoops_GIRGR);
						pe = pe->next;
						if (!pe)
							break;
						_hoops_GIRGR = pe->point_count;
						pe->_hoops_PHHA = pe->point_count = 0;
					}
				} while (g && g->type == type);
			} break;

			case _hoops_HIIP: {
				type = _hoops_IIIP;		// _hoops_HSII _hoops_SAHR _hoops_GAR _hoops_ISII
			} _hoops_HHHI;

			case _hoops_IIIP: {
				do {
					Polyline const *	ptr = (Polyline const *)g;

					if (ptr->count > 0) {
						pe->lengths[pe->_hoops_PHHA] = ptr->count;
						_hoops_AIGA (ptr->points, ptr->count, Point, &pe->points[pe->point_count]);
						if (pe->_hoops_CCCP) {
							pe->_hoops_CCCP[pe->point_count] = _hoops_SCCP(g->priority,0);
							for (ii = 1; ii < ptr->count; ii++)
								pe->_hoops_CCCP[pe->point_count + ii] = pe->_hoops_CCCP[pe->point_count];
 						}
						if (_hoops_GPCP) {
							for (ii = 0; ii < ptr->count; ii++)
								pe->_hoops_PCHA[pe->point_count + ii] = *_hoops_GPCP;
						}
						pe->point_count += ptr->count;
						pe->_hoops_PHHA++;
					}
					if (ptr->count < 0) {
						_hoops_AIGA (ptr->points, -ptr->count, Point, &pe->points[pe->point_count]);
						if (_hoops_GPCP) {
							for (ii = 0; ii < -ptr->count; ii++)
								pe->_hoops_PCHA[pe->point_count + ii] = *_hoops_GPCP;
						}
						if (pe->_hoops_CCCP) {
							pe->_hoops_CCCP[pe->point_count] = _hoops_SCCP(g->priority,0);
							for (ii = 1; ii < -ptr->count; ii++)
								pe->_hoops_CCCP[pe->point_count + ii] = pe->_hoops_CCCP[pe->point_count];
 						}
						pe->point_count += -ptr->count;
						for (i = 0; i < -ptr->count; i += 2) {
							pe->lengths[pe->_hoops_PHHA] = 2;
							pe->_hoops_PHHA++;
						}
					}

					g = g->next;
					if (single)
						break;
					if (_hoops_SPRGR(pe, _hoops_GHRGR)) {
						ASSERT (pe->point_count == _hoops_GIRGR);
						pe = pe->next;
						if (!pe)
							break;
						_hoops_GIRGR = pe->point_count;
						pe->_hoops_PHHA = pe->point_count = 0;
					}
				} while (g && g->type == type);
			} break;

			default:
				_hoops_CSHI (g, type);
		};
		if (single)
			break;
	}
	/* _hoops_RRRC _hoops_PPR _hoops_GRRC _hoops_AAPR _hoops_RAII _hoops_PPR _hoops_AAII _hoops_CIAA _hoops_PAII _hoops_HAII _hoops_HIGR */
	if (_hoops_IHRGR) {
		struct _hoops_CHRGR alter *_hoops_RSHI;
		while ((_hoops_RSHI = _hoops_IHRGR->RemoveFirst()) != null) {
			_hoops_AIGA (_hoops_RSHI->points, _hoops_RSHI->count, Point, &pe->points[pe->point_count]);
			if (_hoops_GPCP) {
				for (ii = 0; ii < _hoops_RSHI->count; ii++)
					pe->_hoops_PCHA[pe->point_count + ii] = *_hoops_GPCP;
			}
			if (pe->_hoops_CCCP) {
				g = _hoops_RSHI->g;
				pe->_hoops_CCCP[pe->point_count] = _hoops_SCCP(g->priority,0);
				for (ii = 1; ii < _hoops_RSHI->count; ii++)
					pe->_hoops_CCCP[pe->point_count + ii] = pe->_hoops_CCCP[pe->point_count];
			}
			pe->lengths[pe->_hoops_PHHA] = _hoops_RSHI->count;
			pe->point_count += _hoops_RSHI->count;
			pe->_hoops_PHHA++;
			FREE_ARRAY (_hoops_RSHI->points, _hoops_RSHI->_hoops_SGII, Point);
			FREE (_hoops_RSHI, struct _hoops_CHRGR);
			if (_hoops_SPRGR(pe, _hoops_GHRGR)) {
				ASSERT (pe->point_count == _hoops_GIRGR);
				pe = pe->next;
				if (!pe)
					break;
				_hoops_GIRGR = pe->point_count;
				pe->_hoops_PHHA = pe->point_count = 0;
			}
		}
		delete _hoops_IHRGR;
	}
	ASSERT (!pe || pe->point_count == _hoops_GIRGR);
	if (_hoops_AHRGR)
		*_hoops_AHRGR = _hoops_ARPI;

	return _hoops_SHRGR;
} //_hoops_RSGR _hoops_API '_hoops_APGR _hoops_IS _hoops_ACRI'


local void
_hoops_SAPI (
		Net_Rendition const &  nr,
		H3D_Display_List_Bin alter *_hoops_RRHA,
		H3D_Display_List_Bin_List alter *_hoops_IAPI,
		bool *_hoops_AHRGR,
		bool *_hoops_GCRGR,
		bool *_hoops_GIGI)
{
	Display_Context const * dc = nr->_hoops_SRA;
	Polyedge *pe = null;
	_hoops_AIGI *_hoops_RCRGR = null;
	//_hoops_SCSH _hoops_SPCC, _hoops_RSHS;
	_hoops_IRHA *pair = null;
	Geometry const *g = null;
	bool _hoops_ARPI = false;
	bool _hoops_SAR = nr->_hoops_ARA->_hoops_APPI._hoops_SAR;
	bool _hoops_ACRGR;
	_hoops_IRHA *_hoops_CHAI[_hoops_SPAI];
	_hoops_IRHA **_hoops_SHAI = _hoops_CHAI;
	int _hoops_GIAI = _hoops_SPAI;
	int _hoops_RIAI;
	int i;
	int pass;
	int _hoops_AIAI = 0;
	H3D_Display_List_Bin *_hoops_GRPI = null;
	RGB const *_hoops_PCRGR;
	int _hoops_HCRGR = 0, total = 0;

	if (_hoops_AHRGR != null)
		*_hoops_AHRGR = false;
	_hoops_SHAI[0] = _hoops_RRHA->_hoops_CRHA->PeekFirst();
	_hoops_RIAI = 1;

	for(pass = 0; pass < _hoops_RIAI; pass++) {
		_hoops_RRHA->_hoops_CRHA->ResetCursor();
		for (;;) { // _hoops_IH _hoops_GRR _hoops_PSAI
			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			if (!pair)
				break;
			_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
			if (!_hoops_HPAI (pair, _hoops_SHAI[pass])) {
				if (pass == 0) {
					//_hoops_CAHA _hoops_GGSR _hoops_RPP _hoops_SR _hoops_RRP _hoops_IS _hoops_GGCR _hoops_IRS _hoops_CCAH _hoops_PCAI
					if (!_hoops_HPAI (pair, _hoops_SHAI[_hoops_AIAI])) {
						for (i = 0; i < _hoops_RIAI; i++) {
							if (_hoops_HPAI (pair, _hoops_SHAI[i])) {
								_hoops_AIAI = i;
								break;
							}
						}
						if (i == _hoops_RIAI) {
							if (_hoops_RIAI == _hoops_GIAI) {
								_hoops_IRHA **victim = _hoops_SHAI;
								_hoops_GIAI *= 2;
								ZALLOC_ARRAY (_hoops_SHAI, _hoops_GIAI, _hoops_IRHA *);
								_hoops_AIGA (victim, _hoops_RIAI, _hoops_IRHA *, _hoops_SHAI);
								if (victim != _hoops_CHAI)
									FREE_ARRAY (victim, _hoops_RIAI, _hoops_IRHA *);
							}
							_hoops_SHAI[_hoops_RIAI] = pair;
							_hoops_RIAI++;
						}
					}
				}
				continue;
			}
			g = (Geometry const *)pair->geo;
			_hoops_PCRGR = _hoops_CCAI (pair->color, Color_LINE);
			if (!_hoops_SAR ||
				g->type == _hoops_IIIP ||
				g->type == _hoops_HIIP ||
				g->type == _hoops_PIIP) {
				pe = _hoops_RHRGR (nr, (Geometry *)pair->geo, &_hoops_ACRGR, pair->single, _hoops_PCRGR, true);
				_hoops_ARPI |= _hoops_ACRGR;
				while (pe) {
					_hoops_IRHA *_hoops_ICRGR = POOL_NEW(dc->memory_pool, _hoops_IRHA)(pair->nr, pe, pair->_hoops_CPAI, pair->color, pair->single);
					if (!_hoops_RCRGR) {
						_hoops_RCRGR = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);
						_hoops_GRPI = POOL_NEW(dc->memory_pool, H3D_Display_List_Bin)(dc->memory_pool);
						delete _hoops_GRPI->_hoops_CRHA;
						_hoops_GRPI->_hoops_CRHA = _hoops_RCRGR;
						_hoops_GRPI->nr = _hoops_RRHA->nr;
						_hoops_IAPI->AddFirst (_hoops_GRPI);
					}
					_hoops_RCRGR->AddFirst(_hoops_ICRGR);
					_hoops_GRPI->_hoops_IGGI.point_count += pe->point_count;
					_hoops_GRPI->_hoops_IGGI.total += pe->total;
					_hoops_GRPI->_hoops_IGGI._hoops_PHHA += pe->_hoops_PHHA;
					_hoops_ISAI (pe); //_hoops_SAII _hoops_SSCP _hoops_CGI _hoops_IS _hoops_RH _hoops_GPII
					if (pe->next) {
						//_hoops_RH _hoops_ACRI _hoops_CSAP _hoops_HAH _hoops_AHSC _hoops_IH _hoops_SPR _hoops_AIRI _hoops_HIGR, _hoops_HIS _hoops_CCRGR
						//_hoops_SCRGR _hoops_IHHH _hoops_IRS _hoops_HIGR _hoops_SGS _hoops_SR _hoops_RRP _hoops_IS _hoops_HHGP _hoops_GH _hoops_PPR _hoops_GSRGR _hoops_RSRGR.
						Polyedge *next = pe->next;
						pe->next = null;
						pe = next;
						ASSERT (pair->single == false);
						_hoops_ICRGR->single = false;
					}
					else
						break;
				}
			}
			else {
				_hoops_ARPI = true;
			}
		}
		_hoops_RCRGR = null;
		if (_hoops_GRPI) {
			_hoops_HCRGR += _hoops_GRPI->_hoops_IGGI.point_count;
			total += _hoops_GRPI->_hoops_IGGI.total;
		}
	}

	if (_hoops_AHRGR)
		*_hoops_AHRGR = _hoops_ARPI;
	if (_hoops_SAR && _hoops_ARPI &&
		_hoops_GCRGR != null)
		*_hoops_GCRGR = true;
	if (total < H3D_Display_List_MINIMUM ||
		_hoops_HCRGR < H3D_Display_List_MINIMUM)
		*_hoops_GIGI = true;
	if (_hoops_SHAI != _hoops_CHAI)
		FREE_ARRAY (_hoops_SHAI, _hoops_GIAI, _hoops_IRHA *);
}


bool _hoops_AACR (
		Net_Rendition const & nr,
		_hoops_GACR alter **_hoops_ASRGR,
		_hoops_GACR alter **dl,
		H3D_Display_List alter **odl,
		unsigned int type)
{
	//_hoops_PSRGR _hoops_RAPC *_hoops_HSRGR = _hoops_ISRGR ();
	bool _hoops_RACR = HI_Get_Display_List(nr->_hoops_SRA->_hoops_GHRI, _hoops_ASRGR, dl);

	if ((*dl)->list == null) {

		ZALLOC(*odl, H3D_Display_List);
		(*dl)->list = (_hoops_AGCI*)*odl;
		(*dl)->_hoops_GGCI = -1;
		(*odl)->_hoops_GPPI = HOOPS_WORLD->_hoops_GPPI;
		(*odl)->type = type;
		(*odl)->time_stamp = HOOPS_WORLD->_hoops_GPPI;
		(*odl)->_hoops_PPAH = *dl;
		(*odl)->_hoops_GHRI = nr->_hoops_SRA->_hoops_GHRI;

		_hoops_CAAI (HOOPS_WORLD->_hoops_SAAI);
		(*odl)->next = HOOPS_WORLD->_hoops_GPAI;
		(*odl)->prev = &(HOOPS_WORLD->_hoops_GPAI);
		if (HOOPS_WORLD->_hoops_GPAI != null)
			HOOPS_WORLD->_hoops_GPAI->prev = &(*odl)->next;
		HOOPS_WORLD->_hoops_GPAI = *odl;
		_hoops_APAI (HOOPS_WORLD->_hoops_SAAI);
		
		_hoops_RACR = true;

		if (type == H3D_DL_SEGMENT_TREE) {
			(*dl)->action_mask = _hoops_RSCI;
			if (BIT (nr->_hoops_SRA->flags, _hoops_IIGC))
				(*dl)->_hoops_PRRI |= _hoops_AASI;
		}

	}

	*odl = (H3D_Display_List*) (*dl)->list;

#if 0
	if (*odl) {
		OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
		(*odl)->dc = nr->_hoops_SRA;
	}
#endif

	return _hoops_RACR;
}




void _hoops_SSRGR(Display_Context const *dc)
{
	H3DData *h3ddata = H3DD(dc);
	_hoops_GGAGR alter * _hoops_GHRI = (_hoops_GGAGR alter *)dc->_hoops_GHRI;

	_hoops_CAAI (HOOPS_WORLD->_hoops_SAAI);
	_hoops_AGCI * _hoops_RGAGR = _hoops_GHRI->_hoops_RGAGR;
	_hoops_GHRI->_hoops_RGAGR = null;
	_hoops_APAI (HOOPS_WORLD->_hoops_SAAI);

	if (_hoops_RGAGR != null) {

		_hoops_AGCI * _hoops_AGAGR = _hoops_RGAGR;

		while (_hoops_AGAGR != null) {
			bool _hoops_IAGGR = false;

			H3D_Display_List alter * odl = (H3D_Display_List alter *)_hoops_AGAGR;

			if (odl->type == H3D_DL_SHADOW_MAP)
				_hoops_IAGGR = true;

			if (odl->type == H3D_DL_TEXTURE && odl->_hoops_PPAH) {
				if (odl->item.texture._hoops_IAGGR)
					_hoops_IAGGR = true;
				/* _hoops_RPP _hoops_RH _hoops_CSRI _hoops_HRGR _hoops_IRS _hoops_CGRH _hoops_HH, _hoops_SRPS _hoops_RH _hoops_PIH _hoops_ARPP _hoops_PGAGR _hoops_SCH _hoops_SGGR */
				Image alter *image = (Image alter *)odl->_hoops_PPAH->owner;
				if (image &&
					BIT (image->flags, _hoops_GRRH) && 
					!BIT (image->_hoops_RRHH, _hoops_HGAGR) &&
					!h3ddata->_hoops_IGAGR) {
					if (dc->_hoops_IPCI->_hoops_CGAGR != null) {
						dc->_hoops_IPCI->_hoops_CGAGR (dc, odl);
						image->flags &= ~(_hoops_GRRH);
					}
				}
			}

			if (odl->type == H3D_DL_SEGMENT_TREE) {
				if (odl->item._hoops_ACGI._hoops_ARRI)
					_hoops_RCCA(_hoops_SGAGR) += odl->item._hoops_ACGI._hoops_ARRI->Count();
				if (odl->item._hoops_ACGI._hoops_AGAI)
					_hoops_RCCA(_hoops_SGAGR) += odl->item._hoops_ACGI._hoops_AGAI->Count();
				if (odl->item._hoops_ACGI._hoops_GGAI)
					_hoops_RCCA(_hoops_SGAGR) += odl->item._hoops_ACGI._hoops_GGAI->Count();
				if (odl->item._hoops_ACGI._hoops_RGAI)
					_hoops_RCCA(_hoops_SGAGR) += odl->item._hoops_ACGI._hoops_RGAI->Count();
				if (odl->item._hoops_ACGI._hoops_CAPI)
					_hoops_RCCA(_hoops_SGAGR) += odl->item._hoops_ACGI._hoops_CAPI->Count();
				if (odl->item._hoops_ACGI._hoops_RCII)
					_hoops_RCCA(_hoops_SGAGR) += odl->item._hoops_ACGI._hoops_RCII->Count();
				if (odl->item._hoops_ACGI._hoops_GAAI)
					_hoops_RCCA(_hoops_SGAGR) += odl->item._hoops_ACGI._hoops_GAAI->Count();
			}
			else
				_hoops_RCCA(_hoops_SGAGR)++;

#ifndef H3D_DL_DELETE_TASK
			if (1) {
#else
			if (_hoops_IAGGR || dc->_hoops_GRAGR) {
#endif
				_hoops_AGCI *_hoops_ASRGR = _hoops_RGAGR;

				if (_hoops_ASRGR == _hoops_AGAGR) {
					_hoops_RGAGR = _hoops_ASRGR->next;
				}
				else {
					while (_hoops_ASRGR && _hoops_ASRGR->next != _hoops_AGAGR)
						_hoops_ASRGR = _hoops_ASRGR->next;

					if (_hoops_ASRGR && _hoops_ASRGR->next)
						_hoops_ASRGR->next = _hoops_ASRGR->next->next;
				}

				_hoops_AGCI * _hoops_RRAGR = _hoops_AGAGR->next;
				_hoops_SPSI (_hoops_AGAGR);
				_hoops_AGAGR = _hoops_RRAGR;
			}
			else {
				ASSERT (_hoops_AGAGR != _hoops_AGAGR->next);
				_hoops_AGAGR = _hoops_AGAGR->next;
			}
		}

#ifdef H3D_DL_DELETE_TASK
		if (_hoops_RGAGR)
			NEW(H3D_DL_Delete_Task)(dc, _hoops_RGAGR);

#endif
	}

}

bool _hoops_ARAGR(H3DData alter *h3ddata, int _hoops_SHGGR)
{
	UNREFERENCED(h3ddata);
	bool result = false;

	size_t _hoops_PRAGR = HOOPS_WORLD->display_list_vram_usage - _hoops_SHGGR;

	if (HOOPS_WORLD->display_list_vram_usage < (size_t) _hoops_SHGGR)
		_hoops_PRAGR = 0;

	((Display_Context alter *) h3ddata->dc)->_hoops_GRAGR = true;
#define _hoops_HRAGR 1
	while (HOOPS_WORLD->display_list_vram_usage > _hoops_PRAGR) {

		_hoops_CAAI (HOOPS_WORLD->_hoops_SAAI);
		_hoops_AGCI alter *		_hoops_AGAGR = HOOPS_WORLD->_hoops_GPAI;
		int										n = 0;

		while (_hoops_AGAGR != null) {
			_hoops_AGCI alter *	_hoops_RRAGR = _hoops_AGAGR->next;

			H3D_Display_List alter * odl = (H3D_Display_List alter *)_hoops_AGAGR;

			if (h3ddata->_hoops_AAI != odl &&
				odl->type != H3D_DL_SHADOW_MAP && odl->type != H3D_DL_TEXTURE &&
				!BIT(odl->_hoops_PPAH->_hoops_PRRI, _hoops_AASI)) {
				n++;

				HD_Queue_Destroy_List(_hoops_AGAGR, false);

				if (n == _hoops_HRAGR)
					break;
			}

			_hoops_AGAGR = _hoops_RRAGR;
		}
		_hoops_APAI (HOOPS_WORLD->_hoops_SAAI);

		if (n > 0) {
			_hoops_SSRGR(h3ddata->dc);
			result = true;
		}
		else
			break;
	}
	((Display_Context alter *) h3ddata->dc)->_hoops_GRAGR = false;
	return result;
}

INLINE void
_hoops_IPGI (H3D_Display_List_List*& list)
{
	if (list) {
		H3D_Display_List *_hoops_IRAGR;
		while ((_hoops_IRAGR = list->RemoveFirst()) != null) {
			_hoops_SPSI(_hoops_IRAGR);
		}
		delete list;
		list= null;
	}
}

void
_hoops_SPSI (_hoops_AGCI *_hoops_AGAGR)
{
	H3D_Display_List alter * odl = (H3D_Display_List *) _hoops_AGAGR;

	switch (odl->type) {
		case H3D_DL_TEXTURE: {
			if (odl->item.texture.id && odl->item.texture.id != _hoops_CRAGR)
				_hoops_HP(odl->item.texture.id);

			if (odl->item.texture._hoops_SRAGR) {
				/*_hoops_IH (_hoops_HAS=0; _hoops_HAS<_hoops_GAAGR; _hoops_HAS++)
					_hoops_RPP (_hoops_CSRI->_hoops_IGCI._hoops_HH._hoops_RAAGR[_hoops_HAS] &&
						_hoops_CSRI->_hoops_IGCI._hoops_HH._hoops_RAAGR[_hoops_HAS]->_hoops_PPGGR();

				_hoops_AAAGR(_hoops_CSRI->_hoops_IGCI._hoops_HH._hoops_RAAGR, _hoops_GAAGR, _hoops_PAAGR);*/
			}
		} break;

		case H3D_DL_GEOMETRY: {
			if (odl->item.geometry.id && odl->item.geometry.id != _hoops_HAAGR) {

				H3DIndexedBufferObject_List* _hoops_IAAGR = odl->item.geometry.id;
				H3DIndexedBufferObject * dx9_obj;
				while ((dx9_obj = _hoops_IAAGR->RemoveFirst()) != null)
				{
					if (odl->item.geometry._hoops_SGAS == H3D_OBJ_IndexBuffer)
						delete dx9_obj;
					else if (odl->item.geometry._hoops_SGAS == H3D_OBJ_VertexBuffer)
						delete (H3DVertexBufferCache *) dx9_obj;
					else if (odl->item.geometry._hoops_SGAS == H3D_OBJ_Mesh) {
						delete dx9_obj;
					}
				}
				delete _hoops_IAAGR;
				odl->item.geometry.id = null;
				odl->item.geometry._hoops_SGAS = H3D_OBJ_INVALID;
			}
		} break;

		case H3D_DL_SEGMENT_POLYLINE: {
			_hoops_IPGI (odl->item._hoops_RPPI._hoops_GHPI);
		} break;

		case H3D_DL_SEGMENT_POLYGON: {
			_hoops_IPGI (odl->item._hoops_ACII._hoops_PCII);
			_hoops_IPGI (odl->item._hoops_ACII._hoops_GHPI);
			_hoops_IPGI (odl->item._hoops_ACII._hoops_HCII);
		} break;

		case H3D_DL_SEGMENT_TREE: {
			_hoops_IPGI (odl->item._hoops_ACGI._hoops_ARRI);
			_hoops_IPGI (odl->item._hoops_ACGI._hoops_AGAI);
			_hoops_IPGI (odl->item._hoops_ACGI._hoops_GGAI);
			_hoops_IPGI (odl->item._hoops_ACGI._hoops_RGAI);
			_hoops_IPGI (odl->item._hoops_ACGI._hoops_GAAI);
			_hoops_IPGI (odl->item._hoops_ACGI._hoops_RAAI);
			_hoops_IPGI (odl->item._hoops_ACGI._hoops_CAPI);
			_hoops_IPGI (odl->item._hoops_ACGI._hoops_RCII);
			odl->item._hoops_ACGI._hoops_RGP = 0;
			odl->item._hoops_ACGI.flags = 0;
		} break;

		case H3D_DL_SHADOW_MAP: {
			_hoops_HP (odl->item._hoops_HRR.id);
		} break;

		default:
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				"Unrecognized type in DX9 destroy_list()");
			break;
	}
	FREE(odl, H3D_Display_List);
}

/*
* _hoops_SRAC
*/
void _hoops_CAAGR (Net_Rendition const &  nr,
				int left, int right, int bottom, int top)
{
	H3DData alter *h3ddata = H3DNRD (nr);
	H3DVertexBufferCache *_hoops_HACP = 0;
	H3DVertexBuffer &_hoops_PAIH = h3ddata->_hoops_CP;

	_hoops_HPHH (h3ddata, false);

	//_hoops_PRPP _hoops_SIAC _hoops_ACPP _hoops_HIS _hoops_SGS _hoops_GCAC _hoops_HCPH _hoops_CHR _hoops_RCAC _hoops_IS _hoops_SSS
	H3D_TRACE(h3ddata, "clear_z_buffer");

	/*_hoops_ACAC _hoops_PCAC _hoops_HPPA _hoops_IPPA _hoops_HIHP _hoops_CGPR _hoops_HIHP _hoops_SHPH*/
	h3ddata->_hoops_HCAC = _hoops_CCC;
	h3ddata->_hoops_ICAC = _hoops_CCC;

	if (left == nr->_hoops_SRA->_hoops_RCGA.left &&
		right == nr->_hoops_SRA->_hoops_RCGA.right &&
		top == nr->_hoops_SRA->_hoops_RCGA.top &&
		bottom == nr->_hoops_SRA->_hoops_RCGA.bottom) {
		ENSURE_DEPTH_MASK (h3ddata, true);
		//_hoops_IHIR _hoops_SHPR _hoops_SCAC
		h3ddata->_hoops_GSCR->Clear(H3DCLEAR_ZBUFFER, 0x000000ff, 1.0f, 0L);
	}
	else {
		//_hoops_CCAC _hoops_SCAC
		H3DVertexFormat _hoops_PPCP(H3DVF_PT);
		_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
		float _hoops_SAAGR[2] = {h3ddata->_hoops_CSC->_hoops_GSCH[0], h3ddata->_hoops_CSC->_hoops_GSCH[1]};

		int flags = H3DID_DC;
		H3DShader *_hoops_RSR;

		_hoops_SSHH (h3ddata, nr, T_FACES, null, flags, &_hoops_RSR);
		_hoops_GIAC (h3ddata, nr, _hoops_RSR);
		_hoops_RPAP (h3ddata, false);
		_hoops_APHH(h3ddata, 1, 1);
		_hoops_PISP (h3ddata, false);
		ENSURE_DEPTH_MASK (h3ddata, true);
		_hoops_RHSA (h3ddata, H3DCULL_NONE);

		_hoops_RPIH (h3ddata, _hoops_PPCP, _hoops_HACP);
		_hoops_HACP->Lock(4, &_hoops_PAIH);
		_hoops_PAIH._hoops_AHCP(left, bottom, _hoops_IHCR->_hoops_PCHH);
		_hoops_PAIH._hoops_CPPH();
		_hoops_PAIH._hoops_AHCP(left, top + 1, _hoops_IHCR->_hoops_PCHH);
		_hoops_PAIH._hoops_CPPH();
		_hoops_PAIH._hoops_AHCP(right + 1, bottom, _hoops_IHCR->_hoops_PCHH);
		_hoops_PAIH._hoops_CPPH();
		_hoops_PAIH._hoops_AHCP(right + 1, top + 1, _hoops_IHCR->_hoops_PCHH);
		_hoops_PAIH._hoops_CPPH();
		_hoops_HACP->Unlock();
		_hoops_HACP->_hoops_CHSA(h3ddata, H3DPT_TRIANGLESTRIP, 2);
		_hoops_RPAP (h3ddata, true);

		_hoops_APHH(h3ddata, _hoops_SAAGR[0], _hoops_SAAGR[1]);
	}

}


/*
 * _hoops_PGAA
 */
void _hoops_PHPI (
		Net_Rendition const &  nr,
		Geometry const * _hoops_RSII,
		Action_Mask mask,
		bool single)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	H3DData alter *h3ddata = H3DD (dc);
	Polyedge alter *pe;
	_hoops_GACR alter *dl;
	H3D_Display_List alter *odl=0;
	bool _hoops_RACR;
	_hoops_CRCP alter *owner = null;
	bool _hoops_SAR = nr->_hoops_ARA->_hoops_APPI._hoops_SAR;
	bool _hoops_CISP, _hoops_IAHC;
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	int weight;
	Geometry const *g;
	Type type;
	_hoops_GPAGR	_hoops_RPAGR;
	_hoops_HICS		path;

	H3D_TRACE(h3ddata, "render_3d_lines");

	weight = _hoops_HC->weight;
	if (weight < 0)
		weight = (int)(HD_Compute_Generic_Size (nr, _hoops_HC->_hoops_PHP, _hoops_HC->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
	_hoops_IAHC = (weight > H3D_LARGEST_PRECOMPUTED_CIRCLE ||
			BIT(_hoops_HC->flags, _hoops_SRPI) || _hoops_GAPI (_hoops_HC->line_style) ||
			(h3ddata->_hoops_ISCI > 0 && !BIT(_hoops_HC->line_style->flags, LSF_SOLID)) ||
			(weight > 1 && !BIT(_hoops_HC->line_style->flags, LSF_SOLID)));

	_hoops_CISP = (_hoops_HC->_hoops_CHA &&
					  _hoops_HC->_hoops_CHA->_hoops_IRIR < 1.0f);
	if (_hoops_CISP &&
	 	nr->_hoops_CPP->_hoops_PRH._hoops_SRI != _hoops_PIII) {
		_hoops_IAHC = true;
	}

	if (single &&
		(_hoops_RSII->type == _hoops_IIIP || 
		_hoops_RSII->type == _hoops_HIIP ||
		_hoops_RSII->type == _hoops_PIIP)) {
			_hoops_SAR = false;
	}

	/* _hoops_RAR _hoops_AAR _hoops_CPAP _hoops_PAH'_hoops_RA _hoops_SHH _hoops_ARIP _hoops_IIGR _hoops_AIRI _hoops_CPCI */
	if (_hoops_SAR || _hoops_IAHC) {
		bool _hoops_APAGR = true;

		g = _hoops_RSII;
		while (g) {
			type = g->type;
			switch (type) {
				case _hoops_RIIP:
				case _hoops_GIIP: {
					if (h3ddata->_hoops_CIGI)
						h3ddata->_hoops_CIGI->mask &= ~_hoops_AIIP;
					do {
						dc->_hoops_RAI = g;
						_hoops_PPAGR (nr, (Elliptical_Arc const *) g);
						g = g->next;
						if (single)
							goto _hoops_HPAGR;
					} while (g && g->type == type);
				} break;

				case _hoops_CHIP: {
					if (h3ddata->_hoops_CIGI)
						h3ddata->_hoops_CIGI->mask &= ~_hoops_SHIP;
					do {
						dc->_hoops_RAI = g;
						_hoops_IPAGR (nr, (_hoops_PIRGR alter *) g);
						g = g->next;
						if (single)
							goto _hoops_HPAGR;
					} while (g && g->type == type);
				} break;

				case _hoops_IIIP:
				case _hoops_HIIP:
				case _hoops_PIIP: {
					if (_hoops_IAHC) {
						if (h3ddata->_hoops_CIGI)
							h3ddata->_hoops_CIGI->mask &= ~_hoops_IRPI;
						do {
							dc->_hoops_RAI = g;
							HD_Std_3D_Polyline (nr, (Polyline const *)g);
							g = g->next;
							if (single)
								goto _hoops_HPAGR;
						} while (g && g->type == type);
					}
					else {
						_hoops_APAGR = false;
						_hoops_CSHI (g, g->type);
					}
				} break;

				default:
					_hoops_CSHI (g, g->type);
			}
		}
		if (_hoops_APAGR)
			goto _hoops_HPAGR;
	}

	if (!BIT (mask, _hoops_CIIP))
		goto _hoops_HPAGR;

	if (h3ddata->_hoops_ISCI > 0) {
		if (_hoops_HSHS (nr, (Geometry const *)_hoops_RSII, single))
			goto _hoops_HPAGR;
	}

	if (single) {
		dc->_hoops_RAI = _hoops_RSII;
		switch (_hoops_RSII->type) {
			case _hoops_RIIP:
			case _hoops_GIIP: {
				if (BIT (mask, _hoops_AIIP))
					_hoops_PPAGR (nr, (Elliptical_Arc const *) _hoops_RSII);
			} break;

			case _hoops_CHIP: {
				if (BIT (mask, _hoops_SHIP))
					_hoops_IPAGR (nr, (_hoops_PIRGR const *) _hoops_RSII);
			} break;

			case _hoops_IIIP:
			case _hoops_HIIP:
			case _hoops_PIIP: {
				if (BIT (mask, _hoops_CIIP))
					_hoops_CPAGR (nr, (Polyline const *) _hoops_RSII);
			} break;
		}
		goto _hoops_HPAGR;
	}

	if (h3ddata->_hoops_CIGI == null) {
		pe = _hoops_RHRGR (nr, _hoops_RSII, null, single, null, false);
		if (pe) {
			pe->_hoops_SRHA |= _hoops_SRHH;
			really_draw_3d_polyedge (nr, pe, nr->_hoops_AHP, null);
			if (_hoops_ISAI (pe) == 0)
				HI_Free_Polyedge(pe);
		}
		goto _hoops_HPAGR;
	}

	/* _hoops_SSS _hoops_RH _hoops_AIRI _hoops_HIGR _hoops_IHIA _hoops_CCA _hoops_RGR _hoops_RHPP, _hoops_PPR _hoops_HRCI _hoops_SCH _hoops_RPP _hoops_HAHH */
	owner = (_hoops_CRCP alter *)_hoops_RSII->owner;
	ASSERT(owner != null);

	if (dc->_hoops_AHSI != null)
		path = dc->_hoops_AHSI->path;

	{
		_hoops_SPAGR				_hoops_GHAGR (owner->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
		_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (owner, path);

		if ((_hoops_RPAGR = _hoops_CSC->_hoops_PHAGR()) == null) {
			_hoops_RPAGR = _hoops_GPAGR::Create(dc->memory_pool);
			_hoops_CSC->_hoops_HHAGR (_hoops_RPAGR);
		}
	}


	_hoops_RACR = _hoops_AACR(nr, &_hoops_RPAGR->_hoops_IHAGR, &dl, &odl, H3D_DL_SEGMENT_POLYLINE);
#define	_hoops_CHAGR			(_hoops_GHGI)0xFFFFFFFF
#define _hoops_SHAGR	(_hoops_GHGI)0x00000001
	if (_hoops_RACR) {
		dl->_hoops_GSAI = _hoops_CHAGR;
	}
	else {
		/* _hoops_ISPR _hoops_IH _hoops_SHPH _hoops_GGR _hoops_AGIS _hoops_GIAGR _hoops_RPP _hoops_SR _hoops_RIAGR _hoops_GRRC _hoops_CGHI _hoops_GHIR _hoops_AARI */
		if (BIT (dl->_hoops_GSAI, _hoops_SHAGR)) {
			/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_CPIC *_hoops_IS* _hoops_RAR _hoops_AIAGR, _hoops_SR'_hoops_GCPP _hoops_HHGC _hoops_IS _hoops_PIAGR _hoops_RGR _hoops_ISRS _hoops_SIHH _hoops_GRRC */
			if (nr->_hoops_ARA->_hoops_APPI._hoops_SAR) {
				dl->_hoops_GSAI = _hoops_CHAGR;
			}
			/* _hoops_RPP _hoops_GII _hoops_AGIS _hoops_GIAGR _hoops_HGAS, _hoops_HRCI _hoops_ISRS */
			if (odl->item._hoops_RPPI._hoops_PPPI != nr->_hoops_ARA->_hoops_APPI._hoops_PPPI ||
				odl->item._hoops_RPPI._hoops_HPPI != nr->_hoops_ARA->_hoops_APPI._hoops_HPPI ||
				odl->item._hoops_RPPI._hoops_IPPI != nr->_hoops_ARA->_hoops_APPI._hoops_IPPI ||
				odl->item._hoops_RPPI._hoops_CPPI != nr->_hoops_ARA->_hoops_APPI._hoops_CPPI ||
				odl->item._hoops_RPPI._hoops_SPPI != nr->_hoops_ARA->_hoops_APPI._hoops_SPPI) {
				dl->_hoops_GSAI = _hoops_CHAGR;
			}
		}
		else {
			/* _hoops_PSP _hoops_GRRC _hoops_ARPP, _hoops_RPP _hoops_SR _hoops_CHR _hoops_GRP/_hoops_CPIC _hoops_IS _hoops_RAR-_hoops_HIAGR,
			   _hoops_HRCI/_hoops_PIAGR _hoops_ISRS _hoops_RPP _hoops_SR _hoops_IPIH _hoops_HS _hoops_GII _hoops_GRRC _hoops_GGR _hoops_RH _hoops_CAGH */
			if (!nr->_hoops_ARA->_hoops_APPI._hoops_SAR) {
				if (owner != null &&
					owner->type == _hoops_IRCP &&
					(owner->_hoops_GACP->_hoops_AACP (_hoops_IIAGR(_hoops_CHIP)) != null ||
					 owner->_hoops_GACP->_hoops_AACP (_hoops_IIAGR(_hoops_RIIP)) != null ||
					 owner->_hoops_GACP->_hoops_AACP (_hoops_IIAGR(_hoops_GIIP)) != null)) {
					dl->_hoops_GSAI = _hoops_CHAGR;
				}
			}
		}
	}
	if (dl->_hoops_GSAI == _hoops_CHAGR) {
		if (!_hoops_RACR) {
			HD_Queue_Destroy_List (odl, true);
			_hoops_RACR = _hoops_AACR(nr, &_hoops_RPAGR->_hoops_IHAGR, &dl, &odl, H3D_DL_SEGMENT_POLYLINE);
		}
		dl->_hoops_GSAI = 0;
		odl->item._hoops_RPPI._hoops_PPPI = nr->_hoops_ARA->_hoops_APPI._hoops_PPPI;
		odl->item._hoops_RPPI._hoops_HPPI = nr->_hoops_ARA->_hoops_APPI._hoops_HPPI;
		odl->item._hoops_RPPI._hoops_IPPI = nr->_hoops_ARA->_hoops_APPI._hoops_IPPI;
		odl->item._hoops_RPPI._hoops_CPPI = nr->_hoops_ARA->_hoops_APPI._hoops_CPPI;
		odl->item._hoops_RPPI._hoops_SPPI = nr->_hoops_ARA->_hoops_APPI._hoops_SPPI;
	}

	if (_hoops_RACR) {
		H3D_Display_List_Bin *_hoops_GRPI;
		_hoops_IRHA *pair;
		pe = _hoops_RHRGR (nr, _hoops_RSII, null, single, null, false);
		//_hoops_RH _hoops_SPS _hoops_CIAGR _hoops_APGR _hoops_AACC _hoops_PPR _hoops_SIAGR _hoops_HII _hoops_GCAGR
		_hoops_GRPI = POOL_NEW(dc->memory_pool, H3D_Display_List_Bin)(dc->memory_pool);
		pair = POOL_NEW(dc->memory_pool, _hoops_IRHA)(nr, pe, null, null);
		_hoops_ISAI (pe); //_hoops_SAII _hoops_HHHH _hoops_IS _hoops_RH _hoops_GPII
		_hoops_GRPI->_hoops_CRHA->AddFirst (pair);
		_hoops_GRPI->nr = nr;
		_hoops_GRPI->_hoops_IGGI.point_count = pe->point_count;
		_hoops_GRPI->_hoops_IGGI._hoops_PHHA = pe->_hoops_PHHA;
		_hoops_GRPI->_hoops_IGGI.total = pe->total;
		//_hoops_HII _hoops_ARI _hoops_GPP, _hoops_RRGR _hoops_RCAGR _hoops_HII _hoops_IIPS
		really_draw_3d_polyedge (nr, null, nr->_hoops_AHP, _hoops_GRPI);
		ASSERT (odl->item._hoops_RPPI._hoops_GHPI == null);
		odl->item._hoops_RPPI._hoops_GHPI = POOL_NEW(dc->memory_pool, H3D_Display_List_List)(dc->memory_pool);
		odl->item._hoops_RPPI._hoops_GHPI->AddFirst (_hoops_GRPI->odl);
		_hoops_GRPI->odl = null;
		while ((pair = _hoops_GRPI->_hoops_CRHA->RemoveFirst()) != null) {
			delete pair;
		}
		delete _hoops_GRPI;

		dl->_hoops_AGRI = pe->_hoops_SRHA;
		if (!_hoops_SAR)
			dl->_hoops_GSAI = pe->_hoops_GSAI | _hoops_SHAGR;
		else
			dl->_hoops_GSAI = pe->_hoops_GSAI;

	}
	else {
		H3D_Display_List_List *list;
		H3D_Display_List *_hoops_APCI;

		if (odl->item._hoops_RPPI._hoops_GHPI) {
			list = odl->item._hoops_RPPI._hoops_GHPI;
			list->ResetCursor();
			while ((_hoops_APCI = list->PeekCursor()) != null) {
				list->AdvanceCursor();
				_hoops_SRCI (nr, _hoops_APCI, nr->_hoops_AHP);
			}
		}
	}

_hoops_HPAGR:
	;

} // _hoops_RSGR _hoops_API '_hoops_SRGS 3d _hoops_APGR'

/*
 * _hoops_PGAA - _hoops_IRHH _hoops_RCRR _hoops_GRAA-_hoops_AIRI-_hoops_HIGR _hoops_CHPI _hoops_PGSA _hoops_GAR _hoops_RSPH _hoops_CHPI _hoops_HIS _hoops_GII _hoops_PGCR
 * _hoops_PSHR _hoops_HPRC/_hoops_PSHR _hoops_IGIR/_hoops_PSHR _hoops_ACAGR _hoops_CHPI _hoops_PHHR _hoops_ISHP _hoops_RH _hoops_PSHR _hoops_CRAA.
 */
local
void _hoops_CIII (Net_Rendition const & nr, Ellipse const *ellipse)
{
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	H3DData *					h3ddata = H3DD(dc);
	int const					_hoops_RGP = nr->_hoops_RGP;
	int							type = ellipse->type;

	// _hoops_CGP _hoops_SR _hoops_HS _hoops_GII _hoops_SPPR, _hoops_SGH _hoops_RH _hoops_GSSR _hoops_CRAA. _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_IGGC _hoops_AIRI _hoops_CPCI, _hoops_PCAGR.
	if (h3ddata->_hoops_ISCI ||
		type == _hoops_GRCP ||
		type == _hoops_RRCP ||
		BIT(_hoops_RGP, T_ANY_POLYGON_EDGE))

		// _hoops_GISP _hoops_HCAGR
		draw_3d_ellipse (nr, ellipse);

	else {
		// _hoops_PIGR _hoops_IRS _hoops_CRHH _hoops_IIGR _hoops_GAAS _hoops_IS _hoops_SCIR _hoops_RH _hoops_HCPI
		Tristrip alter *_hoops_PCHI;
		Geometry const *g;
		int count = 0;
		int _hoops_CCPI = 0;

		ZALLOC (_hoops_PCHI, Tristrip);
		_hoops_ICAI (_hoops_PCHI);

		g = ellipse;
		for (;;) {
			count++;
			if (!h3ddata->_hoops_AHPI)
				break;
			g = g->next;
			if (!g || g->type != type)
				break;
		}
		// _hoops_ICAGR _hoops_CGGR _hoops_CCA _hoops_SPR _hoops_HCPI
		_hoops_PCHI->point_count = count * 4;
		_hoops_PCHI->total = count * 6;
		_hoops_PCHI->face_count = count;
		_hoops_PCHI->_hoops_PHHA = 1;

		// _hoops_CCAGR/_hoops_CCPP _hoops_SIRGR
		_hoops_SHPI(nr, _hoops_PCHI, false);
		g = ellipse;
		bool _hoops_ASPI = BIT(nr->transform_rendition->heuristics, _hoops_SASA);
		for (;;) {
			_hoops_ICPI(_hoops_PCHI, _hoops_CCPI++, count*4, (Ellipse const *)g, null, null, true, _hoops_ASPI);
			if (!h3ddata->_hoops_AHPI)
				break;
			g = g->next;
			if (!g || g->type != type)
				break;
		}

		// _hoops_GISP _hoops_SCH
		_hoops_PCHI->_hoops_SRHA |= _hoops_SRHH;
		draw_3d_tristrip(nr, _hoops_PCHI);

		// _hoops_SCAGR _hoops_IIGR _hoops_SCH
		if (_hoops_ISAI(_hoops_PCHI) == 0)
			HI_Free_Tristrip(_hoops_PCHI);
	}
}

/*
* _hoops_SRAC
*/
Geometry const * segment_render (
		Net_Rendition const &		_hoops_GSAGR,
		Geometry const *			_hoops_RSII,
		Action_Mask					mask,
		bool						_hoops_RSAGR)
{
	Display_Context alter *		dc = (Display_Context alter *)_hoops_GSAGR->_hoops_SRA;
	H3DData *					h3ddata = H3DD(dc);
	_hoops_ACHR					_hoops_RGP;
	Geometry const *			g = _hoops_RSII;
	bool 						_hoops_ASAGR = false;
	bool						_hoops_PSAGR = true;

	if (BIT(dc->flags, _hoops_CHSI) &&
		!BIT(dc->flags, _hoops_HSAGR))
		return null;

	_hoops_RGP = _hoops_GSAGR->_hoops_RGP;

	if (g->owner == null || _hoops_RSAGR) {
		return HD_Standard_Render(_hoops_GSAGR, g, mask, _hoops_RSAGR);
	}

	do {
		Net_Rendition				nr = _hoops_GSAGR;
		bool						single = _hoops_RSAGR;

		if (dc->_hoops_SPA != dc->_hoops_ISAGR) {
			if ((g = dc->_hoops_SPA->geometry) == null){
				g = dc->_hoops_SPA->_hoops_CSAGR;	// _hoops_IHIS _hoops_GPP _hoops_IS _hoops_GGAS
				_hoops_PSAGR = true;
			}

			nr = dc->_hoops_SPA->nr;
			single = dc->_hoops_SPA->single;
		}

		while (g) {
			_hoops_SSAGR(g);

			if (_hoops_PSAGR && _hoops_GGPGR(nr))
				return g;

			dc->_hoops_RAI = g;

			if (!BIT (nr->_hoops_RGPGR, _hoops_AGPGR(g->type))) {
				if (single)
					goto done;
				_hoops_PGPGR (g, g->type);
			}
			else switch (g->type) {
				case _hoops_CHIP: {
					if (!_hoops_ASAGR &&
						BIT (_hoops_RGP, T_LINES) &&
						BIT (mask, _hoops_SHIP)) {
						_hoops_PHPI (nr, g, mask, single); // _hoops_RGHH _hoops_RH _hoops_APGR, _hoops_RRRC, _hoops_PGRC _hoops_PPR _hoops_GRRC
					}
					_hoops_ASAGR = true;
					if (single)
						goto done;
					_hoops_CSHI (g, g->type);
				} break;

				case _hoops_GIIP:
				case _hoops_RIIP: {
					Type type = g->type;
					if (!_hoops_ASAGR &&
						BIT (_hoops_RGP, T_LINES) &&
						BIT (mask, _hoops_AIIP)) {
						_hoops_PHPI (nr, g, mask, single); // _hoops_RGHH _hoops_RH _hoops_APGR, _hoops_RRRC, _hoops_PGRC _hoops_PPR _hoops_GRRC
					}
					_hoops_ASAGR = true;
					if (single)
						goto done;
					_hoops_CSHI (g, type);
				} break;

				case _hoops_PIIP:
				case _hoops_HIIP:
				case _hoops_IIIP: {
					Type type = g->type;
					if (!_hoops_ASAGR &&
						BIT (_hoops_RGP, T_LINES) &&
						BIT (mask, _hoops_CIIP)) {
						_hoops_PHPI (nr, g, mask, single); // _hoops_RGHH _hoops_RH _hoops_APGR, _hoops_RRRC, _hoops_PGRC _hoops_PPR _hoops_GRRC
					}
					_hoops_ASAGR = true;
					if (single)
						goto done;
					_hoops_CSHI (g, type);
				} break;

				case _hoops_HGPGR: {
					/* _hoops_ISAP _hoops_IS _hoops_AA _hoops_ARI.  _hoops_HPPA _hoops_GHC _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_HGCR _hoops_CHCC */
					_hoops_CSHI (g, g->type);
				} break;

				case _hoops_SIIP: {
					if (h3ddata->_hoops_CIGI)
						h3ddata->_hoops_CIGI->mask &= ~_hoops_GCIP;
					if (BIT (mask, _hoops_GCIP) && BIT (_hoops_RGP, T_LINES)) {
						do {
							dc->_hoops_RAI = g;
							_hoops_IGPGR (nr, (Polyline const *) g);
							g = g->next;
							if (single)
								goto done;
						} while (g && g->type == _hoops_SIIP);
					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_SIIP);
				} break;

				case _hoops_RCIP: {
					if (ANYBIT (_hoops_RGP, T_ANY_POLYGON_EDGE | T_FACES) &&
						BIT (mask, _hoops_ACIP)) {
						if (h3ddata->_hoops_CIGI) {
							if (_hoops_HSIS (nr, (Polygon const *)g, single))
								_hoops_CSHI (g, g->type);
							h3ddata->_hoops_CIGI->mask &= ~_hoops_ACIP;
						}
						h3ddata->_hoops_AHPI = !single;
						dc->_hoops_RAI = g;
						_hoops_SGPGR (nr, (Polygon const *)g);
						h3ddata->_hoops_AHPI = false;
					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_RCIP);
				}

				case _hoops_GRCP:
				case _hoops_RRCP:
				case _hoops_CGCP:
				case _hoops_SGCP: {
					Type type = g->type;
					if (ANYBIT (_hoops_RGP, T_FACES | T_ANY_POLYGON_EDGE) &&
						BIT (mask, _hoops_ARCP)) {
						if (h3ddata->_hoops_CIGI)
							h3ddata->_hoops_CIGI->mask &= ~_hoops_ARCP;
						h3ddata->_hoops_AHPI = !single;
						dc->_hoops_RAI = g;
						_hoops_CIII (nr, (Ellipse const *)g);
						h3ddata->_hoops_AHPI = false;
					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, type);
				} break;

				case _hoops_PCIP:
					if (BIT (mask, _hoops_HCIP) && BIT (_hoops_RGP, T_MARKERS)) {
						h3ddata->_hoops_AHPI = !single;
						dc->_hoops_RAI = g;
						draw_3d_marker (nr, (Marker const *)g);
						h3ddata->_hoops_AHPI = false;
					}
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_PCIP);
				break;

				case _hoops_PIRS: {
					if (BIT (mask, _hoops_HCIP) && BIT (_hoops_RGP, T_MARKERS)) {
						do {
							HD_Std_3D_Multimarker(nr, (_hoops_GRPGR const *)g);
							g = g->next;
							if (single)
								goto done;
						} while (g && g->type == _hoops_PIRS);
					}	 /* _hoops_RSGR _hoops_SIGC */
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_PIRS);
				} break;

				case _hoops_ICIP: {
					if (BIT (mask, _hoops_CCIP) && BIT (_hoops_RGP, T_ANY_LIGHTS)) {
						do {
							dc->_hoops_RAI = g;
							_hoops_RRPGR (nr, (Light const *) g);
							g = g->next;
							if (single)
								goto done;
						} while (g && g->type == _hoops_ICIP);
					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_ICIP);
				} break;

				case _hoops_SCIP:
				case _hoops_GSIP: {
					Type type = g->type;
					if (h3ddata->_hoops_CIGI) {
						h3ddata->_hoops_CIGI->mask &= ~_hoops_RSIP;
						if (!BIT (_hoops_RGP, T_GENERIC_EDGES)) {
							if (BIT (_hoops_RGP, T_INTERIOR_SILHOUETTE_EDGES))
								h3ddata->_hoops_CIGI->mask &= ~_hoops_RCSI;
							if (BIT (_hoops_RGP, _hoops_GCSI))
								h3ddata->_hoops_CIGI->mask &= ~_hoops_ACSI;
						}
					}
					if (BIT (mask, _hoops_RSIP|_hoops_PCSI)) {

						_hoops_CRCP *	_hoops_ARPGR;
						if ((_hoops_ARPGR = g->owner) != null)
							_hoops_ARPGR->_hoops_RHAGR._hoops_PRPGR(dc->_hoops_RIGC->thread_id);

						do {
							dc->_hoops_RAI = g;
							_hoops_HRPGR (nr, (Polyhedron const *)g);
							if (_hoops_IACI(dc)) {
								if (_hoops_ARPGR != null)
									_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
								return g;
							}

							g = g->next;
							if (single) {
								if (_hoops_ARPGR != null)
									_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
								goto done;
							}
						} while (g && g->type == type);

						if (_hoops_ARPGR != null)
							_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();

					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, type);
				} break;

				case _hoops_ASIP: {
					if (h3ddata->_hoops_CIGI)
						h3ddata->_hoops_CIGI->mask &= ~_hoops_PSIP;
					if (ANYBIT (_hoops_RGP, T_FACES | T_ANY_SHELL_EDGE) &&
						BIT (mask, _hoops_PSIP|_hoops_PCSI)) {

						do {
							dc->_hoops_RAI = g;
							_hoops_CRPGR (nr, (Cylinder const *) g);
							g = g->next;
							if (single)
								goto done;
						} while (g && g->type == _hoops_ASIP);
					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_ASIP);
				} break;

				case _hoops_HSIP: {
					if (h3ddata->_hoops_CIGI)
						h3ddata->_hoops_CIGI->mask &= ~_hoops_ISIP;
					if (ANYBIT (_hoops_RGP, T_FACES | T_ANY_SHELL_EDGE) &&
						BIT (mask, _hoops_ISIP|_hoops_PCSI)) {

						do {
							dc->_hoops_RAI = g;
							_hoops_SRPGR (nr, (Sphere const *) g);
							g = g->next;
							if (single)
								goto done;
						} while (g && g->type == _hoops_HSIP);
					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_HSIP);
				} break;


				case _hoops_CSIP: {
					if (h3ddata->_hoops_CIGI)
						h3ddata->_hoops_CIGI->mask &= ~_hoops_SSIP;
					if (ANYBIT (_hoops_RGP, T_FACES | T_ANY_SHELL_EDGE) &&
						BIT (mask, _hoops_SSIP|_hoops_PCSI)) {

						do {
							dc->_hoops_RAI = g;
							_hoops_GAPGR (nr, (PolyCylinder const *) g);
							g = g->next;
							if (single)
								goto done;
						} while (g && g->type == _hoops_CSIP);
					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_CSIP);
				} break;

				case _hoops_GGCP: {
					if (h3ddata->_hoops_CIGI)
						h3ddata->_hoops_CIGI->mask &= ~_hoops_RGCP;
					if (ANYBIT (_hoops_RGP, T_FACES | T_ANY_GRID_EDGE | T_MARKERS) &&
						BIT (mask, _hoops_RGCP|_hoops_PCSI) &&
						!h3ddata->_hoops_PI.mode) {

						do {
							dc->_hoops_RAI = g;
							_hoops_RAPGR (nr, (Grid const *) g);
							g = g->next;
							if (single)
								goto done;
						} while (g && g->type == _hoops_GGCP);
					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_GGCP);
				} break;

				case _hoops_AGCP: {
					if (h3ddata->_hoops_CIGI)
						h3ddata->_hoops_CIGI->mask &= ~_hoops_PGCP;
					if (BIT (_hoops_RGP, T_TEXT) &&
						BIT (mask, _hoops_PGCP)) {
						do {
							_hoops_HACC const *		text = (_hoops_HACC const *)g;
							dc->_hoops_RAI = g;
							if (text->count != 0 || text->_hoops_AAPGR != null)
								_hoops_PAPGR (nr, text);
							g = g->next;
							if (single)
								goto done;
						} while (g && g->type == _hoops_AGCP);
					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_AGCP);
				} break;

				case _hoops_HGCP: {
					if (h3ddata->_hoops_CIGI)
						h3ddata->_hoops_CIGI->mask &= ~_hoops_IGCP;
					if (BIT (_hoops_RGP, T_IMAGES) &&
						BIT (mask, _hoops_IGCP)) {
						do {
							dc->_hoops_RAI = g;
							_hoops_HAPGR (nr, (Image const *) g);
							g = g->next;
							if (single)
								goto done;
						} while (g && g->type == _hoops_HGCP);
					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_HGCP);
				} break;

				case _hoops_PRCP: {
					if (h3ddata->_hoops_CIGI)
						h3ddata->_hoops_CIGI->mask &= ~_hoops_HRCP;
					if (ANYBIT (_hoops_RGP, T_FACES|T_ANY_SHELL_EDGE) &&
						BIT (mask, _hoops_HRCP|_hoops_PCSI)) {

						_hoops_CRCP *	_hoops_ARPGR;
						if ((_hoops_ARPGR = g->owner) != null)
							_hoops_ARPGR->_hoops_RHAGR._hoops_PRPGR(dc->_hoops_RIGC->thread_id);

						do {
							dc->_hoops_RAI = g;
							/* _hoops_HSPR _hoops_III _hoops_IAPGR _hoops_GGSR _hoops_CCGR _hoops_SR _hoops_HS _hoops_PCCP _hoops_RGPS _hoops_CAPGR _hoops_HGPS
							 * _hoops_SAPGR (_hoops_SCII, (_hoops_GPPGR _hoops_RAPC *)_hoops_ISHI); */
							_hoops_RPPGR (nr, (_hoops_APPGR alter *) g);
							g = g->next;
							if (single) {
								if (_hoops_ARPGR != null)
									_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
								goto done;
							}
						} while (g && g->type == _hoops_PRCP);

						if (_hoops_ARPGR != null)
							_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_PRCP);
				} break;

				case _hoops_AHIP: {
					_hoops_PHIP const *	_hoops_RRA = (_hoops_PHIP const *)g;
					Geometry const *				_hoops_PPPGR = _hoops_RRA->next;

					if (dc->_hoops_SPA->_hoops_CSAGR != _hoops_RRA) {
						if (_hoops_RRA->condition.count == 0 ||
							HI_Condition_Passed (nr->_hoops_ASIR->conditions.count,
												 nr->_hoops_ASIR->conditions._hoops_RCHA,
												 &_hoops_RRA->condition)) {
							bool _hoops_SIGI = false;

							if (h3ddata->_hoops_CIGI) {
								Attribute const *_hoops_HPPGR;
								if ((_hoops_HPPGR = _hoops_RRA->_hoops_IPPGR) != null) {
									h3ddata->_hoops_CIGI->_hoops_CPPGR = true;
									do {
										switch (_hoops_HPPGR->type) {
											case HK_MODELLING_MATRIX:
											case HK_USER_OPTIONS:
											case HK_USER_VALUE:
												break;
											case HK_COLOR: {
												_hoops_SSGI const *color = (_hoops_SSGI const *)_hoops_HPPGR;
												if (!HI_Color_Is_Simple (color, null))
													_hoops_SIGI = true;
											} break;
											default:
												_hoops_SIGI = true;
										}
									} while (!_hoops_SIGI && (_hoops_HPPGR = _hoops_HPPGR->next) != null);
								}
								if (_hoops_SIGI)
									h3ddata->_hoops_CIGI->_hoops_SIGI = _hoops_SIGI;
							}

							if (nr->_hoops_IRR->_hoops_GAHA != Display_List_SEGMENT ||
								(HD_Geometry_To_Action_Mask (g) & mask)) {
								if ((g = HD_Process_Geometry_Reference (nr, _hoops_RRA)) != null)
									goto _hoops_SPPGR;
							}
							nr = _hoops_GSAGR;
							single = _hoops_RSAGR;
							_hoops_ASAGR = false;
							_hoops_PSAGR = false;
						}
					}
					else {
						if (nr->_hoops_IRR->_hoops_GAHA != Display_List_SEGMENT ||
							(HD_Geometry_To_Action_Mask (g) & mask)) {
							if ((g = HD_Process_Geometry_Reference (nr, _hoops_RRA)) != null)
								goto _hoops_SPPGR;
						}
						nr = _hoops_GSAGR;
						single = _hoops_RSAGR;
						_hoops_ASAGR = false;
					}

					if (single || (g = _hoops_PPPGR) == null)
						goto done;

				} break;

				/*
				 * _hoops_CPHP'_hoops_GRI _hoops_RHPH, _hoops_CSH _hoops_CGHA
				 */
				case _hoops_GHPGR: {
					_hoops_RHPGR const *	_hoops_AHPGR = (_hoops_RHPGR const *)g;
					_hoops_CRCP const *				owner = _hoops_AHPGR->owner;

					if (ANYBIT (_hoops_RGP, _hoops_AHPGR->which))
						_hoops_PHPGR (HEC_GL_DRIVER, HES_MEMORY_PURGED,
						Sprintf_P (null, "Need to redraw all or some of '%p' -", owner),
						"but memory has been purged from it");
					g = g->next;
				} break;

				default:
					_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
						Sprintf_D (null, "Unknown type '%d' in render", g->type));
					goto done;
					_hoops_HHHI;
			}
		}
done:
		dc->_hoops_RAI = null;

		if (dc->_hoops_SPA != dc->_hoops_ISAGR)
			dc->_hoops_SPA->geometry = null;

  _hoops_SPPGR:;
	} while (dc->_hoops_SPA != dc->_hoops_ISAGR);

	return g;
}



void draw_overlay_list (Net_Rendition const & nr)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	H3DData alter *h3ddata = H3DD (dc);
	bool _hoops_HHPGR = false;

	H3D_TRACE(h3ddata, "draw_overlay_list");

	HD_Alternate_Hidden_Root (dc, _hoops_IHPGR);
	if (!dc->_hoops_CHPGR &&
		!dc->_hoops_HASS[dc->_hoops_IASS] &&
		!dc->_hoops_GPSS[dc->_hoops_IASS] &&
		!dc->_hoops_RPSS[dc->_hoops_IASS])
		goto _hoops_HPAGR;

	switch (dc->_hoops_SHPGR)
	{
		case QMoves_Accumulation: {
			Int_Rectangle area;
			area.bottom = nr->_hoops_SAIR->extent.bottom;
			area.top = nr->_hoops_SAIR->extent.top;
			area.left = nr->_hoops_SAIR->extent.left;
			area.right = nr->_hoops_SAIR->extent.right;

			if (!h3ddata->_hoops_GIPGR) {
				ASSERT(!h3ddata->_hoops_RIPGR);
				h3ddata->_hoops_GSCR->create_region(nr, &area,
					&h3ddata->_hoops_GIPGR, &h3ddata->_hoops_AIPGR);
			}

			if (h3ddata->_hoops_RIPGR)
				h3ddata->_hoops_GSCR->_hoops_PIPGR(nr, &area,
					h3ddata->_hoops_GIPGR, h3ddata->_hoops_AIPGR);

			h3ddata->_hoops_GSCR->_hoops_HIPGR(nr, &area,
				h3ddata->_hoops_GIPGR, h3ddata->_hoops_AIPGR);

			// _hoops_CGP _hoops_SR _hoops_HS _hoops_IIPGR, _hoops_CIPGR _hoops_RH _hoops_CSCR _hoops_ARI, _hoops_HIS _hoops_SGS _hoops_HCH _hoops_HPHS _hoops_HRGR
			// _hoops_HHPA _hoops_PPR _hoops_SR _hoops_SIPGR'_hoops_RA _hoops_GCPGR _hoops_RH _hoops_RCPGR _hoops_ISPH.
			if (!_hoops_IACI(dc) && dc->_hoops_ACPGR->_hoops_PCPGR) {
				(*dc->_hoops_ACPGR->_hoops_PCPGR) (nr);
				_hoops_HHPGR = true;
			}

			_hoops_CAAGR(nr, area.left, area.right, area.bottom, area.top);

			HD_Standard_Draw_Overlay_List (nr);

			if (dc->_hoops_RIGC->_hoops_HCPGR != 1)
				dc->flags |= _hoops_ICPGR;

			h3ddata->_hoops_RIPGR = true;
		} break;

		case QMoves_Spriting: {
			/* _hoops_AA _hoops_ISAP.  _hoops_SCH'_hoops_GRI _hoops_GIR _hoops_GGR _hoops_CCPGR */
		} break;
	}

_hoops_HPAGR:
	HD_Alternate_Hidden_Root (dc, _hoops_IHPGR);

	// _hoops_CGP _hoops_SR _hoops_SARS'_hoops_RA _hoops_AIAH _hoops_CIPGR _hoops_RH _hoops_CSCR, _hoops_HA _hoops_HRGR _hoops_RH _hoops_GHIR _hoops_IS _hoops_AA _hoops_SCH.
	if (!_hoops_IACI(dc) && dc->_hoops_ACPGR->_hoops_PCPGR && !_hoops_HHPGR) {
		(*dc->_hoops_ACPGR->_hoops_PCPGR) (nr);
	}
}

void _hoops_SCPGR (Net_Rendition const & nr)
{
	Display_Context const *dc = nr->_hoops_SRA;
	H3DData alter *h3ddata = H3DD (dc);

	H3D_TRACE(h3ddata, "undraw_overlay_list");

	if (!h3ddata->_hoops_RIPGR)
		return;

	switch (dc->_hoops_SHPGR)
	{
		case QMoves_Accumulation: {
			Int_Rectangle area;
			area.bottom = nr->_hoops_SAIR->extent.bottom;
			area.top = nr->_hoops_SAIR->extent.top;
			area.left = nr->_hoops_SAIR->extent.left;
			area.right = nr->_hoops_SAIR->extent.right;

			h3ddata->_hoops_GSCR->_hoops_PIPGR(nr, &area,
				h3ddata->_hoops_GIPGR, h3ddata->_hoops_AIPGR);

			h3ddata->_hoops_RIPGR = false;
		} break;

		case QMoves_Spriting: {
			/* _hoops_AA _hoops_ISAP.  _hoops_SCH'_hoops_GRI _hoops_GIR _hoops_GGR _hoops_CCPGR */
		} break;
	}
}



void create_region (Net_Rendition const &  nr,
			Int_Rectangle const * area, void **image, void **z)
{
	H3DData *h3ddata = H3DNRD(nr);
	_hoops_GSPGR	_hoops_RSPGR, _hoops_ASPGR;
	_hoops_RSPGR = HI_What_Time();
	h3ddata->_hoops_GSCR->create_region(nr, area, image, z);
	_hoops_ASPGR = HI_What_Time();
	_hoops_GPRH(_hoops_PSPGR) += (_hoops_ASPGR - _hoops_RSPGR) / _hoops_HSPGR;
}

void _hoops_HIPGR (Net_Rendition const &  nr,
		Int_Rectangle const * area, void alter * image, void alter * z)
{
	H3DData *h3ddata = H3DNRD(nr);
	_hoops_GSPGR	_hoops_RSPGR, _hoops_ASPGR;
	_hoops_RSPGR = HI_What_Time();
	h3ddata->_hoops_GSCR->_hoops_HIPGR(nr, area, image, z);
	_hoops_ASPGR = HI_What_Time();
	_hoops_GPRH(_hoops_PSPGR) += (_hoops_ASPGR - _hoops_RSPGR) / _hoops_HSPGR;
}

void _hoops_PIPGR (Net_Rendition const &  nr,
		Int_Rectangle const * area, void alter * image, void alter * z)
{
	H3DData *h3ddata = H3DNRD(nr);
	_hoops_GSPGR	_hoops_RSPGR, _hoops_ASPGR;
	_hoops_RSPGR = HI_What_Time();
	h3ddata->_hoops_GSCR->_hoops_PIPGR(nr, area, image, z);
	_hoops_ASPGR = HI_What_Time();
	_hoops_GPRH(_hoops_PSPGR) += (_hoops_ASPGR - _hoops_RSPGR) / _hoops_HSPGR;
}

void _hoops_ISPGR (Net_Rendition const &  nr,
		void alter * image, void alter * z)
{
	H3DData *h3ddata = H3DNRD(nr);
	_hoops_GSPGR	_hoops_RSPGR, _hoops_ASPGR;
	_hoops_RSPGR = HI_What_Time();
	h3ddata->_hoops_GSCR->_hoops_ISPGR((Display_Context alter *)nr->_hoops_SRA, image, z);
	_hoops_ASPGR = HI_What_Time();
	_hoops_GPRH(_hoops_PSPGR) += (_hoops_ASPGR - _hoops_RSPGR) / _hoops_HSPGR;
}


void _hoops_CSPGR (
	Display_Context alter *		dc) {
	H3DData *					h3ddata = H3DD(dc);

	h3ddata->_hoops_SSPGR = h3ddata->_hoops_CIGI;
	h3ddata->_hoops_GGHGR = h3ddata->_hoops_ISCI;
	h3ddata->_hoops_RGHGR = dc->_hoops_IPCI->mask;

	h3ddata->_hoops_CIGI = null;
	h3ddata->_hoops_ISCI = 0;
	dc->_hoops_IPCI->mask = _hoops_RAPI;
}
void _hoops_AGHGR (
	Display_Context alter *		dc) {
	H3DData *					h3ddata = H3DD(dc);

	h3ddata->_hoops_CIGI = h3ddata->_hoops_SSPGR;
	h3ddata->_hoops_ISCI = h3ddata->_hoops_GGHGR;
	dc->_hoops_IPCI->mask = h3ddata->_hoops_RGHGR;
}


/*****************************************************************************
*****************************************************************************
								_hoops_PGHGR _hoops_HGHGR
*****************************************************************************
*****************************************************************************/
#include "hic_calls.h"

void * _hoops_IGHGR(
	Net_Rendition const &	nr,
	long					request,
	void alter				*pointer,
	POINTER_SIZED_INT		_hoops_ISPI,
	POINTER_SIZED_INT		_hoops_CSPI,
	POINTER_SIZED_INT		_hoops_SSPI,
	POINTER_SIZED_INT		_hoops_SGHI,
	float					f1,
	float					f2,
	float					_hoops_CGHGR,
	float					_hoops_SGHGR)
{
	H3DData alter *h3ddata = H3DD (nr->_hoops_SRA);

	UNREFERENCED(pointer);
	UNREFERENCED(_hoops_ISPI);
	UNREFERENCED(_hoops_CSPI);
	UNREFERENCED(_hoops_SSPI);
	UNREFERENCED(_hoops_SGHI);
	UNREFERENCED(f1);
	UNREFERENCED(f2);
	UNREFERENCED(_hoops_CGHGR);
	UNREFERENCED(_hoops_SGHGR);

	switch (request) {
		case _hoops_GRHGR: {
			return (void*)(POINTER_SIZED_INT)h3ddata->render_target->_hoops_IRRP;
		}_hoops_HHHI;

		case _hoops_RRHGR: {
			return (void*)(POINTER_SIZED_INT)h3ddata->render_target->_hoops_CRRP;
		}_hoops_HHHI;

		case _hoops_ARHGR: {
			// _hoops_GPHA _hoops_PAR _hoops_AIR _hoops_CI?
			_hoops_AHGR type = (_hoops_AHGR) _hoops_ISPI;
			return h3ddata->_hoops_GSCR->_hoops_PRHGR(type, (char *) pointer);
		} break;

		case _hoops_HRHGR: {
			h3ddata->_hoops_GSCR->_hoops_IRHGR((POINTER_SIZED_INT) pointer);
		} break;

		case _hoops_CRHGR: {
			_hoops_AHGR type = (_hoops_AHGR) _hoops_ISPI;
			return (void *) h3ddata->_hoops_GSCR->_hoops_SRHGR(type, (POINTER_SIZED_INT) pointer);
		} break;

		case _hoops_GAHGR: {
			_hoops_AHGR type		= (_hoops_AHGR) _hoops_ISPI;
			char const *name	= (char const *) pointer;
			int count			= _hoops_CSPI;
			int *data			= (int *) _hoops_SSPI;
			h3ddata->_hoops_GSCR->_hoops_RAHGR(type, name, count, data);
		} break;

		case _hoops_AAHGR: {
			_hoops_AHGR type		= (_hoops_AHGR) _hoops_ISPI;
			char const *name	= (char const *) pointer;
			int count			= _hoops_CSPI;
			float *data			= (float *) _hoops_SSPI;
			h3ddata->_hoops_GSCR->_hoops_PAHGR(type, name, count, data);
		} break;

		case _hoops_HAHGR: {
			_hoops_AHGR type		= (_hoops_AHGR) _hoops_ISPI;
			char const *name	= (char const *) pointer;
			int width			= _hoops_CSPI;
			int count			= _hoops_SSPI;
			float *data			= (float *) _hoops_SGHI;
			h3ddata->_hoops_GSCR->_hoops_IAHGR(type, name, width, count, data);
		} break;

		case _hoops_CAHGR: {
			_hoops_AHGR type		= (_hoops_AHGR) _hoops_ISPI;
			char const *name	= (char const *) pointer;
			int count			= _hoops_CSPI;
			float *data			= (float *) _hoops_SSPI;
			h3ddata->_hoops_GSCR->_hoops_SAHGR(type, name, count, data);
		} break;

		case _hoops_GPHGR: {
			float *matrix		= (float *) pointer;
			h3ddata->_hoops_GSCR->_hoops_RPHGR(nr, matrix);
		} break;

		case _hoops_APHGR:
		case _hoops_PPHGR: {
			float *matrix		= (float *) pointer;
			h3ddata->_hoops_GSCR->_hoops_HPHGR(nr, matrix);
		} break;

		case _hoops_IPHGR: {
			return (void*)h3ddata->_hoops_GSCR->_hoops_CPHGR();
		} break;

		default:break;
	}

	return 0;
}

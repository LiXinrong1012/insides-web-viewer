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
 * $Id: obf_tmp.txt 1.48 2010-12-06 22:05:39 jason Exp $
 */
#ifndef _3D_COMMON_SHADER_H
#define _3D_COMMON_SHADER_H

/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_RC _hoops_ISHGR
*****************************************************************************
*****************************************************************************/
// _hoops_CRSR _hoops_CI _hoops_HARAR _hoops_AA _hoops_SR _hoops_SGH?
enum _hoops_IRRR 
{ 
	_hoops_IARAR, 
	_hoops_CARAR, 
	_hoops_SARAR,
	_hoops_PARR
};

enum _hoops_AHGR
{
	_hoops_GCGR,
	_hoops_RPRR,
	_hoops_IARR
};


//_hoops_GCSS _hoops_GPP _hoops_PIH[0]
#define H3DID_DC						0x00000001
#define H3DID_TRIANGLE					0x00000002
#define H3DID_POINT						0x00000004		
#define H3DID_LINE						0x00000008
#define H3DID_GOURAUD					0x00000010
#define H3DID_COLOR_INTERPOLATED		0x00000020
#define H3DID_COLOR_INDEX_INTERPOLATED  0x00000040
#define H3DID_VERTEX_COLORS				0x00000080
#define H3DID_VERTEX_FINDICES			0x00000100
#define H3DID_SPRITE_MARKER				0x00000200
#define H3DID_PHYSICAL_REFLECTION		0x00000400
#define H3DID_DEPTH_PEELING				0x00000800
#define H3DID_DEPTH_WRITING				0x00001000
#define H3DID_QUAD_MARKER				0x00002000
#define H3DID_USE_FACE_DISPLACEMENT		0x00004000
#define H3DID_TINTED_IMAGE				0x00008000
#define H3DID_FLAT_SHADING				0x00010000
#define H3DID_TEXTURE_MARKER			0x00020000
#define H3DID_WRITE_LUMINANCE			0x00040000
#define H3DID_CREATE_SHADOW_MAP			0x00080000
#define H3DID_FACE_PATTERN				0x00100000
#define H3DID_LINE_PATTERN				0x00200000
#define H3DID_TRANSPARENCY_STIPPLE		0x00400000
#define H3DID_PERSPECTIVE				0x00800000
#define H3DID_SNAPPED_MARKER			0x01000000
#define H3DID_CREATE_SIMPLE_SHADOW		0x02000000
#define H3DID_CREATE_REFLECTION_PLANE	0x04000000
#define H3DID_CIRCLE_MARKER				0x08000000
#define H3DID_WORLD_SPACE_MARKER    	0x10000000
#define H3DID_RIGHT_HANDED_MATRIX		0x20000000
#define H3DID_NORMAL_FLIP_NEGATIVE		0x40000000
#define H3DID_POLY_CYLINDER				0X80000000

//_hoops_GCSS _hoops_GPP _hoops_PIH[1]
#define H3DID_WIDE_LINE					0x00000001
#define H3DID_ROUND_LINE				0x00000002
#define H3DID_MITER						0x00000004
#define H3DID_ANTI_ALIASED_LINE			0x00000008
#define H3DID_SHADOW_MAP_SAMPLES		0x00000030 // 2 _hoops_SIH - 0..3
#define H3DID_SHADOW_MAP_SAMPLES_SHIFT  4
#define H3DID_DISTANT_SHADOW_MAP_MASK	0x000001C0 // 3 _hoops_SIH - 0..7
#define H3DID_DISTANT_SHADOW_MAP_SHIFT  6
#define H3DID_SPOT_SHADOW_MAP_MASK		0x00000E00 // 3 _hoops_SIH - 0..7
#define H3DID_SPOT_SHADOW_MAP_SHIFT     9
#define H3DID_CUTTING_PLANE_MASK		0x0000F000
#define H3DID_TEXTURE_MASK				0x000F0000
#define H3DID_SPOT_LIGHT_MASK			0x00F00000
#define H3DID_POINT_LIGHT_MASK			0x0F000000
#define H3DID_DISTANT_LIGHT_MASK		0xF0000000

//_hoops_GCSS _hoops_GPP _hoops_PIH[2] (_hoops_RPP _hoops_SGS _hoops_SHPH, _hoops_PAAP _hoops_SIGR _hoops_GGR _hoops_RC::_hoops_CCAGR)
#define H3DID_TEX0_DECAL				0x00000001
#define H3DID_TEX0_WORLD				0x00000002
#define H3DID_TEX0_COLOR				0x00000004
#define H3DID_TEX0_MODULATE				0x00000008
#define H3DID_TEX1_WORLD				0x00000010
#define H3DID_TEX1_COLOR				0x00000020
#define H3DID_TEX1_MODULATE				0x00000040
#define H3DID_TEX2_WORLD				0x00000080
#define H3DID_TEX2_COLOR				0x00000100
#define H3DID_TEX2_MODULATE				0x00000200
#define H3DID_TEX3_WORLD				0x00000400
#define H3DID_TEX3_COLOR				0x00000800
#define H3DID_TEX3_MODULATE				0x00001000
#define H3DID_TEX4_WORLD				0x00002000
#define H3DID_TEX4_COLOR				0x00004000
#define H3DID_TEX4_MODULATE				0x00008000
#define H3DID_TEX5_WORLD				0x00010000
#define H3DID_TEX5_COLOR				0x00020000
#define H3DID_TEX5_MODULATE				0x00040000
#define H3DID_TEX6_WORLD				0x00080000
#define H3DID_TEX6_COLOR				0x00100000
#define H3DID_TEX6_MODULATE				0x00200000
#define H3DID_TEX7_WORLD				0x00400000
#define H3DID_TEX7_COLOR				0x00800000
#define H3DID_TEX7_MODULATE				0x01000000
#define H3DID_HAS_HANDEDNESS			0x02000000
#define _hoops_RCH				0x04000000
#define H3DID_DEPTH_WRITING_SINGLE_PASS 0x08000000
#define H3DID_DEPTH_TEXTURE_HARDWARE	0x10000000
#define H3DID_SPECULAR_TEXTURE			0x20000000
#define H3DID_BUMP_TEXTURE				0x40000000
#define H3DID_SHADOW_MAP_JITTER			0x80000000

// _hoops_GPRAR _hoops_GPP _hoops_PIH[3] (_hoops_RPP _hoops_SGS _hoops_SHPH, _hoops_PAAP _hoops_SIGR _hoops_GGR _hoops_RC::_hoops_CCAGR)
#define H3DID_GOOCH						0x00000001
#define H3DID_PER_PIXEL_LIGHTING		0x00000002
#define H3DID_ENVIRONMENT_TEXTURE		0x00000004
#define H3DID_NON_UNIFORM_SCALE			0x00000008
#define H3DID_SHADOW_MAP_RES_SHIFT				 4
#define H3DID_SHADOW_MAP_RES_MASK		0x00000070
#define H3DID_SHADOW_MAP_VIEW_SHIFT				 7
#define H3DID_SHADOW_MAP_VIEW_MASK		0x00000780
#define H3DID_SHADOW_MAP_RGBA			0x00000800
#define H3DID_AMBIENT_MATERIAL			0x00001000
#define H3DID_FORCE_GRAYSCALE			0x00002000
#define H3DID_CUBE_ENVIRONMENT_MAP		0x00004000
#define H3DID_VERTEX_RGBAS				0x00008000
#define H3DID_FRAME_BUFFER_EFFECTS		0x00010000
#define H3DID_MIRROR_TEXTURE			0x00020000
#define H3DID_TRANSMISSION_TEXTURE		0x00040000
#define H3DID_TRANSMISSION_TEX_MODULATE	0x00080000
#define H3DID_EMISSION_TEXTURE			0x00100000
#define H3DID_EMISSION_TEX_MODULATE		0x00200000
#define H3DID_DEPTH_PEELING_MODE		0x00800000
#define H3DID_PRIORITY_HSRA				0x01000000
#define H3DID_ATMOSPHERIC_ATTENUATION	0x02000000

//_hoops_GCSS _hoops_GPP _hoops_PIH[4] (_hoops_RPP _hoops_SGS _hoops_SHPH, _hoops_PAAP _hoops_SIGR _hoops_GGR _hoops_RC::_hoops_CCAGR)
#define H3DID_BACK_TEX0_DECAL			H3DID_TEX0_DECAL	
#define H3DID_BACK_TEX0_WORLD			H3DID_TEX0_WORLD	
#define H3DID_BACK_TEX0_COLOR			H3DID_TEX0_COLOR	
#define H3DID_BACK_TEX0_MODULATE		H3DID_TEX0_MODULATE	
#define H3DID_BACK_TEX1_WORLD			H3DID_TEX1_WORLD	
#define H3DID_BACK_TEX1_COLOR			H3DID_TEX1_COLOR	
#define H3DID_BACK_TEX1_MODULATE		H3DID_TEX1_MODULATE	
#define H3DID_BACK_TEX2_WORLD			H3DID_TEX2_WORLD	
#define H3DID_BACK_TEX2_COLOR			H3DID_TEX2_COLOR	
#define H3DID_BACK_TEX2_MODULATE		H3DID_TEX2_MODULATE	
#define H3DID_BACK_TEX3_WORLD			H3DID_TEX3_WORLD	
#define H3DID_BACK_TEX3_COLOR			H3DID_TEX3_COLOR	
#define H3DID_BACK_TEX3_MODULATE		H3DID_TEX3_MODULATE	
#define H3DID_BACK_TEX4_WORLD			H3DID_TEX4_WORLD	
#define H3DID_BACK_TEX4_COLOR			H3DID_TEX4_COLOR	
#define H3DID_BACK_TEX4_MODULATE		H3DID_TEX4_MODULATE	
#define H3DID_BACK_TEX5_WORLD			H3DID_TEX5_WORLD	
#define H3DID_BACK_TEX5_COLOR			H3DID_TEX5_COLOR	
#define H3DID_BACK_TEX5_MODULATE		H3DID_TEX5_MODULATE	
#define H3DID_BACK_TEX6_WORLD			H3DID_TEX6_WORLD	
#define H3DID_BACK_TEX6_COLOR			H3DID_TEX6_COLOR	
#define H3DID_BACK_TEX6_MODULATE		H3DID_TEX6_MODULATE	
#define H3DID_BACK_TEX7_WORLD			H3DID_TEX7_WORLD	
#define H3DID_BACK_TEX7_COLOR			H3DID_TEX7_COLOR	
#define H3DID_BACK_TEX7_MODULATE		H3DID_TEX7_MODULATE	
#define H3DID_BACK_TEXTURE_MASK			0xF0000000

// _hoops_GCSS _hoops_GPP _hoops_PIH[5] (_hoops_RPP _hoops_SGS _hoops_SHPH, _hoops_PAAP _hoops_SIGR _hoops_GGR _hoops_RC::_hoops_CCAGR)
#define H3DID_USER_SHADER				0x00000001    //_hoops_GHAP._hoops_RPRAR. _hoops_IAHA _hoops_APRAR _hoops_PCGR
#define H3DID_TEXTURE3D					0x00000002    //3d _hoops_AI
#define H3DID_SHARED_DIFFUSE_COORDS		0x00000004
//#_hoops_PPIP _hoops_PPRAR						0x00000008
#define H3DID_TEX0_DROP					0x00000010	  //_hoops_IH '_hoops_HPRAR' _hoops_SSRA _hoops_IAHA, _hoops_RH _hoops_CHHA _hoops_RRH _hoops_HGPC
#define H3DID_TEX1_DROP					0x00000020
#define H3DID_TEX2_DROP					0x00000040
#define H3DID_TEX3_DROP					0x00000080
#define H3DID_TEX4_DROP					0x00000100
#define H3DID_TEX5_DROP					0x00000200
#define H3DID_TEX6_DROP					0x00000400
#define H3DID_TEX7_DROP					0x00000800
#define H3DID_BACK_TEX0_DROP			H3DID_TEX0_DROP << 8
#define H3DID_BACK_TEX1_DROP			H3DID_TEX1_DROP << 8
#define H3DID_BACK_TEX2_DROP			H3DID_TEX2_DROP << 8
#define H3DID_BACK_TEX3_DROP			H3DID_TEX3_DROP << 8
#define H3DID_BACK_TEX4_DROP			H3DID_TEX4_DROP << 8
#define H3DID_BACK_TEX5_DROP			H3DID_TEX5_DROP << 8
#define H3DID_BACK_TEX6_DROP			H3DID_TEX6_DROP << 8
#define H3DID_BACK_TEX7_DROP			H3DID_TEX7_DROP << 8
#define H3DID_DEFINED_MATERIAL_PS_MASK  0x00f00000
#define	H3DID_DEFINED_MATERIAL_PS_UVW					0x00100000
#define	H3DID_DEFINED_MATERIAL_PS_WORLD					0x00200000
#define	H3DID_DEFINED_MATERIAL_PS_OBJECT				0x00300000
#define H3DID_DEFINED_MATERIAL_PS_SURFACE_NORMAL		0x00400000
#define	H3DID_DEFINED_MATERIAL_PS_LOCAL_PIXELS			0x00500000
#define H3DID_DEFINED_MATERIAL_PS_OUTER_PIXELS			0x00600000
#define	H3DID_DEFINED_MATERIAL_PS_LOCAL_WINDOW			0x00700000
#define H3DID_DEFINED_MATERIAL_PS_OUTER_WINDOW			0x00800000
#define H3DID_DEFINED_MATERIAL_PS_PHYSICAL_REFLECTION	0x00900000
#define H3DID_DEFINED_MATERIAL_MULTITEXTURE				0x01000000


// _hoops_PIH[6] _hoops_HRGR _hoops_CCGC _hoops_HPAP _hoops_IH _hoops_IPSP _hoops_AIRRR _hoops_CHIA _hoops_HPP _hoops_IPRAR
#define H3DID_DEFINED_MATERIAL_SHADER_MASK	0xFFFFFFFF


class H3DShaderID : public CMO
{
private:
#define H3DShaderID_SIZE 7
	unsigned int m_data[H3DShaderID_SIZE];

	void _hoops_AC (
			Net_Rendition const & nr,
			_hoops_PC const & _hoops_HC);
	void _hoops_PAP(int _hoops_HGII)	{ 
		int _hoops_HAP = 0;
		switch (_hoops_HGII) {
			/* _hoops_HSRR _hoops_SACS _hoops_SGH 
			_hoops_AGIR 8192: _hoops_RAAA++; */
			case 4096: _hoops_HAP++;
			case 2048: _hoops_HAP++;
			case 1024: _hoops_HAP++;
			case 512: 
				m_data[3] &= ~H3DID_SHADOW_MAP_RES_MASK;
				m_data[3] |= (_hoops_HAP << H3DID_SHADOW_MAP_RES_SHIFT) & H3DID_SHADOW_MAP_RES_MASK;
				break;
			case 0:  
				//_hoops_RPP _hoops_SR _hoops_HGCR _hoops_ARI, _hoops_SR _hoops_PAHH _hoops_AAPR _hoops_IIP _hoops_GRP _hoops_RCAR _hoops_ACAR
				break;
			default:
				HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
					"Invalid shadow map resolution! Must be 512, 1024, 2048, or 4096.");
				break;			
		}
	};
	void _hoops_IAP(int _hoops_CAP)	{
		int _hoops_CPRAR = 0;
		if (_hoops_CAP >= 4) _hoops_CPRAR++;
		if (_hoops_CAP >= 8) _hoops_CPRAR++;
		if (_hoops_CAP >= 16) _hoops_CPRAR++;
		_hoops_CPRAR <<= H3DID_SHADOW_MAP_SAMPLES_SHIFT;
		
		m_data[1] |= _hoops_CPRAR;
	};
	void _hoops_HHR(int count){ ASSERT(count <= 7); m_data[1] &= ~H3DID_DISTANT_SHADOW_MAP_MASK; m_data[1] |= (count << H3DID_DISTANT_SHADOW_MAP_SHIFT); };
	void _hoops_PHR(int count)	{ ASSERT(count <= 7); m_data[1] &= ~H3DID_SPOT_SHADOW_MAP_MASK; m_data[1] |= (count << H3DID_SPOT_SHADOW_MAP_SHIFT); };
	void _hoops_GPH(int count)	{ ASSERT(count <= 15); m_data[1] &= ~H3DID_CUTTING_PLANE_MASK;	m_data[1] |= (count << 12); };
	void _hoops_ASA(int count)			{ m_data[1] &= ~H3DID_TEXTURE_MASK;		m_data[1] |= (count << 16); };
	void _hoops_GHR(int count)		{ m_data[1] &= ~H3DID_SPOT_LIGHT_MASK;		m_data[1] |= (count << 20); };
	void _hoops_RHR(int count)		{ m_data[1] &= ~H3DID_POINT_LIGHT_MASK;	m_data[1] |= (count << 24); };
	void _hoops_AHR(int count)	{ m_data[1] &= ~H3DID_DISTANT_LIGHT_MASK;	m_data[1] |= (count << 28); };

	void _hoops_PSA(int count)		{ m_data[4] &= ~H3DID_TEXTURE_MASK;		m_data[4] |= (count << 28); };

	void _hoops_CAR(int _hoops_SPRAR, bool _hoops_AGHRR)
	{ 
		ASSERT( _hoops_SPRAR < 4 );
		int const shift = H3DID_SHADOW_MAP_VIEW_SHIFT + _hoops_SPRAR;
		if ( _hoops_AGHRR )
			m_data[3] |= (1 << shift);
		else
			m_data[3] &= ~(1 << shift);
	}
	void _hoops_PIR(
		Net_Rendition const & nr,
		_hoops_HIR const *txr, 
		int *_hoops_SIR, 
		bool _hoops_CIR);

public:
	H3DShaderID () { ZERO_ARRAY (m_data, H3DShaderID_SIZE, int); };
	~H3DShaderID() {};

	POINTER_SIZED_INT _hoops_GHRAR() const {return m_data[0]^m_data[1]^m_data[2]^m_data[3];};

	H3DShaderID *_hoops_IRA (
		Net_Rendition const & nr,
		int type,
		void const *thing, // _hoops_CRHH, _hoops_ACRI _hoops_PAR _hoops_PAAI
		int count,
		int flags,
		int _hoops_RHRAR = 0);

	const char *_hoops_CAI(
		Net_Rendition const & nr);

	void _hoops_AHRAR () {
		m_data[0] = H3DID_DC;
		_hoops_ASA(1);
	};

	void _hoops_PHRAR (int flags, int index = 0) {
		ASSERT(index < H3DShaderID_SIZE);
		m_data[index] |= flags;
	};
	void _hoops_PASRR (POINTER_SIZED_INT _hoops_HHRAR, POINTER_SIZED_INT ps) {
		m_data[0] = (int) _hoops_HHRAR;
		m_data[1] = (int) ps;
		m_data[2] = (int) _hoops_HHRAR >> 16 >> 16;
		m_data[3] = (int) ps >> 16 >> 16;
		m_data[5] = H3DID_USER_SHADER;
	};
	void _hoops_IHRAR (POINTER_SIZED_INT *_hoops_HHRAR, POINTER_SIZED_INT *ps) {
		if (_hoops_HHRAR)
			*_hoops_HHRAR = (m_data[0] + (m_data[2] << 16 << 16));
		if (ps)
			*ps = (m_data[1] + (m_data[3] << 16 << 16));
	}

	int GetData (int index) {
		return m_data[index];
	};

	bool operator == (const H3DShaderID &id) const {
		return  _hoops_AIHR(id.m_data, m_data, sizeof(m_data)); 
	};
	bool operator != (const H3DShaderID &id) const {
		return  !_hoops_AIHR(id.m_data, m_data, sizeof(m_data)); 
	};
	H3DShaderID& operator = (const H3DShaderID &id) {
		COPY_MEMORY (id.m_data, sizeof(m_data), m_data);
		return *this;
	};
	bool _hoops_CCR()		const { return BIT(m_data[0], H3DID_DC); };
	bool _hoops_SAI() const { return BIT(m_data[0], H3DID_TRIANGLE); };
	bool _hoops_GPI()	const { return BIT(m_data[0], H3DID_POINT); };
	bool _hoops_PSI()	const { return BIT(m_data[1], H3DID_MITER); };
	bool _hoops_ISI()	const { return BIT(m_data[1], H3DID_ROUND_LINE); }; //_hoops_GIRR _hoops_CHRAR _hoops_PAR _hoops_GIRR _hoops_SHRAR
	bool _hoops_CSI() const {return BIT(m_data[1], H3DID_ANTI_ALIASED_LINE); }; //_hoops_ARHP _hoops_APGR
	bool _hoops_PAAR() const { return BIT(m_data[0], H3DID_VERTEX_COLORS); };
	bool _hoops_HAAR() const { return BIT(m_data[3], H3DID_VERTEX_RGBAS); };
	bool _hoops_SCI() const { return BIT(m_data[0], H3DID_VERTEX_FINDICES); };
	bool _hoops_RPC()	const { return BIT(m_data[0], H3DID_DEPTH_WRITING); };
	bool _hoops_APC()	const { return BIT(m_data[0], H3DID_DEPTH_PEELING); };
	bool _hoops_PIAR()	const { return BIT(m_data[2], H3DID_DEPTH_TEXTURE_HARDWARE); };
	bool _hoops_HHC()	const { return BIT(m_data[0], H3DID_QUAD_MARKER); };
	bool _hoops_IIRR()	const { return BIT(m_data[0], H3DID_SPRITE_MARKER); };
	bool _hoops_CIRR()	const { return BIT(m_data[0], H3DID_WORLD_SPACE_MARKER); };
	bool _hoops_CRP()	const { return BIT(m_data[0], H3DID_CREATE_SHADOW_MAP); };
	bool _hoops_HIGA() const { return BIT(m_data[0], H3DID_USE_FACE_DISPLACEMENT); };
	bool _hoops_GIRAR() const { return BIT(m_data[0], H3DID_FLAT_SHADING); };
	bool _hoops_SAC() const { return BIT(m_data[0], H3DID_FACE_PATTERN); };
	bool _hoops_SSI() const { return BIT(m_data[0], H3DID_LINE_PATTERN); };
	bool _hoops_GSI() const { return BIT(m_data[1], H3DID_WIDE_LINE); };
	bool _hoops_ICRR() const {return BIT(m_data[0], H3DID_TRANSPARENCY_STIPPLE); };
	bool _hoops_IHAR() const { return BIT(m_data[0], H3DID_PERSPECTIVE); };
	bool _hoops_SIAR() const { return BIT(m_data[0], H3DID_CREATE_SIMPLE_SHADOW); }
	bool _hoops_PHC() const { return BIT(m_data[0], H3DID_CREATE_REFLECTION_PLANE); }
	bool _hoops_HPC() const { return BIT(m_data[2], H3DID_SHADOW_MAP_JITTER); }
	bool _hoops_CHAR()	const { return BIT(m_data[3], H3DID_SHADOW_MAP_RGBA); };
	bool _hoops_RPH() const { return BIT(m_data[3], H3DID_PER_PIXEL_LIGHTING); }
	bool _hoops_CHC() const { return BIT(m_data[0], H3DID_TEXTURE_MARKER); }
	bool _hoops_IHC() const { return BIT(m_data[0], H3DID_CIRCLE_MARKER); }
	bool _hoops_SIRR() const { return BIT(m_data[0], H3DID_SNAPPED_MARKER); }
	bool _hoops_RIC() const { return BIT(m_data[3], H3DID_GOOCH); }
	bool _hoops_PIC() const { return BIT(m_data[3], H3DID_PRIORITY_HSRA); }
	bool _hoops_PCPR() const { return BIT(m_data[3], H3DID_AMBIENT_MATERIAL); }
	bool _hoops_SHC() const { return ANYBIT(m_data[6], H3DID_DEFINED_MATERIAL_SHADER_MASK); }
	bool _hoops_RSRR() const { return BIT(m_data[5], H3DID_TEXTURE3D); }
	bool _hoops_AGC() const { return BIT(m_data[5], H3DID_SHARED_DIFFUSE_COORDS); }
	bool _hoops_AHRA() const { return ANYBIT(m_data[5], H3DID_DEFINED_MATERIAL_PS_LOCAL_PIXELS|H3DID_DEFINED_MATERIAL_PS_OUTER_PIXELS ); }
	bool _hoops_SCRR() const { return ANYBIT(m_data[5], H3DID_DEFINED_MATERIAL_MULTITEXTURE); }
	int _hoops_GSRR() const { return m_data[5] & H3DID_DEFINED_MATERIAL_PS_MASK; }
	int _hoops_RPI() const { return m_data[6]; }
	bool _hoops_HCPR() const { return BIT(m_data[3], H3DID_FORCE_GRAYSCALE); }
	bool _hoops_HHRR() const	{ return BIT(m_data[0], H3DID_POLY_CYLINDER); }
	bool _hoops_GPAR() const { return BIT(m_data[3], H3DID_CUBE_ENVIRONMENT_MAP); }
	bool _hoops_CIAR() const { return BIT(m_data[3], H3DID_FRAME_BUFFER_EFFECTS); }
	bool _hoops_RIHR() const { return BIT(m_data[5], H3DID_USER_SHADER); }
	bool _hoops_AIAR() const { return BIT(m_data[3], H3DID_DEPTH_PEELING_MODE); }
	int	_hoops_ICAR()const { return (512 << ((m_data[3] & H3DID_SHADOW_MAP_RES_MASK) >> H3DID_SHADOW_MAP_RES_SHIFT)); };
	int	_hoops_CSAR()	const { 
		int _hoops_CAP = ((m_data[1] & H3DID_SHADOW_MAP_SAMPLES) >> H3DID_SHADOW_MAP_SAMPLES_SHIFT);
		switch (_hoops_CAP) {
			case 0: return 1;
			case 1: return 4;
			case 2: return 8;
			case 3: return 16;
			default: return 1;
		}
	};
	int	_hoops_PCAR()	const { return (m_data[1] >> H3DID_DISTANT_SHADOW_MAP_SHIFT) & 0x07; }
	int	_hoops_HCAR()		const { return (m_data[1] >> H3DID_SPOT_SHADOW_MAP_SHIFT) & 0x07; }
	int	_hoops_IRP()			const { return _hoops_PCAR() + _hoops_HCAR(); }
	int	_hoops_IAC()		const { return (m_data[1] >> 12) & 0xF; }
	int	_hoops_HGC()			const { return (m_data[1] >> 16) & 0xF; }
	int	_hoops_HPRR()			const { return (m_data[1] >> 20) & 0xF; }
	int	_hoops_PPRR()		const { return (m_data[1] >> 24) & 0xF; }
	int	_hoops_APRR()		const { return (m_data[1] >> 28) & 0xF; }

	int _hoops_CGC()		const { return (m_data[4] >> 28) & 0XF; }

	bool _hoops_IAI() const		  { return _hoops_HPRR() || _hoops_PPRR() || _hoops_APRR(); }

	bool _hoops_HGAR(int _hoops_ASRR) const { if (_hoops_ASRR == 0) return BIT(m_data[2], H3DID_TEX0_DECAL); return false;};
	bool _hoops_CGAR(int _hoops_ASRR) const { 
		switch (_hoops_ASRR) {
			case 0:	return (
						BIT(m_data[2], H3DID_TEX0_MODULATE) || 
						BIT(m_data[0], H3DID_TINTED_IMAGE)); 
			case 1:	return BIT(m_data[2], H3DID_TEX1_MODULATE); 
			case 2:	return BIT(m_data[2], H3DID_TEX2_MODULATE); 
			case 3:	return BIT(m_data[2], H3DID_TEX3_MODULATE);
			case 4:	return BIT(m_data[2], H3DID_TEX4_MODULATE);
			case 5:	return BIT(m_data[2], H3DID_TEX5_MODULATE);
			case 6:	return BIT(m_data[2], H3DID_TEX6_MODULATE);
			case 7:	return BIT(m_data[2], H3DID_TEX7_MODULATE);
			default: return false;
		}
	};
	bool _hoops_IGAR(int _hoops_ASRR) const { 
		switch (_hoops_ASRR) {
			case 0: return BIT(m_data[2], H3DID_TEX0_COLOR); 
			case 1: return BIT(m_data[2], H3DID_TEX1_COLOR); 
			case 2: return BIT(m_data[2], H3DID_TEX2_COLOR); 
			case 3: return BIT(m_data[2], H3DID_TEX3_COLOR); 
			case 4: return BIT(m_data[2], H3DID_TEX4_COLOR); 
			case 5: return BIT(m_data[2], H3DID_TEX5_COLOR); 
			case 6: return BIT(m_data[2], H3DID_TEX6_COLOR); 
			case 7: return BIT(m_data[2], H3DID_TEX7_COLOR); 
			default: return false;
		}
	};
	bool _hoops_PGAR(int _hoops_ASRR) const { 
		switch (_hoops_ASRR) {
			case 0: return BIT(m_data[2], H3DID_TEX0_WORLD); 
			case 1: return BIT(m_data[2], H3DID_TEX1_WORLD); 
			case 2: return BIT(m_data[2], H3DID_TEX2_WORLD); 
			case 3: return BIT(m_data[2], H3DID_TEX3_WORLD); 
			case 4: return BIT(m_data[2], H3DID_TEX4_WORLD); 
			case 5: return BIT(m_data[2], H3DID_TEX5_WORLD); 
			case 6: return BIT(m_data[2], H3DID_TEX6_WORLD); 
			case 7: return BIT(m_data[2], H3DID_TEX7_WORLD); 
			default: return false;
		}
	};
	bool _hoops_SGAR(int _hoops_ASRR) const { 
		switch (_hoops_ASRR) {
			case 0: return BIT(m_data[5], H3DID_TEX0_DROP); 
			case 1: return BIT(m_data[5], H3DID_TEX1_DROP); 
			case 2: return BIT(m_data[5], H3DID_TEX2_DROP); 
			case 3: return BIT(m_data[5], H3DID_TEX3_DROP); 
			case 4: return BIT(m_data[5], H3DID_TEX4_DROP); 
			case 5: return BIT(m_data[5], H3DID_TEX5_DROP); 
			case 6: return BIT(m_data[5], H3DID_TEX6_DROP); 
			case 7: return BIT(m_data[5], H3DID_TEX7_DROP); 
			default: return false;
		}
	};


	bool _hoops_SRAR(int _hoops_ASRR) const { if (_hoops_ASRR == 0) return BIT(m_data[4], H3DID_BACK_TEX0_DECAL); return false;};
	bool _hoops_RAAR(int _hoops_ASRR) const { 
		switch (_hoops_ASRR) {
			case 0:	return (
						BIT(m_data[4], H3DID_BACK_TEX0_MODULATE) || 
						BIT(m_data[0], H3DID_TINTED_IMAGE)); 
			case 1:	return BIT(m_data[4], H3DID_BACK_TEX1_MODULATE); 
			case 2:	return BIT(m_data[4], H3DID_BACK_TEX2_MODULATE); 
			case 3:	return BIT(m_data[4], H3DID_BACK_TEX3_MODULATE);
			case 4:	return BIT(m_data[4], H3DID_BACK_TEX4_MODULATE);
			case 5:	return BIT(m_data[4], H3DID_BACK_TEX5_MODULATE);
			case 6:	return BIT(m_data[4], H3DID_BACK_TEX6_MODULATE);
			case 7:	return BIT(m_data[4], H3DID_BACK_TEX7_MODULATE);
			default: return false;
		}
	};
	bool _hoops_GAAR(int _hoops_ASRR) const { 
		switch (_hoops_ASRR) {
			case 0: return BIT(m_data[4], H3DID_BACK_TEX0_COLOR); 
			case 1: return BIT(m_data[4], H3DID_BACK_TEX1_COLOR); 
			case 2: return BIT(m_data[4], H3DID_BACK_TEX2_COLOR); 
			case 3: return BIT(m_data[4], H3DID_BACK_TEX3_COLOR); 
			case 4: return BIT(m_data[4], H3DID_BACK_TEX4_COLOR); 
			case 5: return BIT(m_data[4], H3DID_BACK_TEX5_COLOR); 
			case 6: return BIT(m_data[4], H3DID_BACK_TEX6_COLOR); 
			case 7: return BIT(m_data[4], H3DID_BACK_TEX7_COLOR); 
			default: return false;
		}
	};
	bool _hoops_CRAR(int _hoops_ASRR) const { 
		switch (_hoops_ASRR) {
			case 0: return BIT(m_data[4], H3DID_BACK_TEX0_WORLD); 
			case 1: return BIT(m_data[4], H3DID_BACK_TEX1_WORLD); 
			case 2: return BIT(m_data[4], H3DID_BACK_TEX2_WORLD); 
			case 3: return BIT(m_data[4], H3DID_BACK_TEX3_WORLD); 
			case 4: return BIT(m_data[4], H3DID_BACK_TEX4_WORLD); 
			case 5: return BIT(m_data[4], H3DID_BACK_TEX5_WORLD); 
			case 6: return BIT(m_data[4], H3DID_BACK_TEX6_WORLD); 
			case 7: return BIT(m_data[4], H3DID_BACK_TEX7_WORLD); 
			default: return false;
		}
	};
	bool _hoops_AAAR(int _hoops_ASRR) const { 
		switch (_hoops_ASRR) {
			case 0: return BIT(m_data[5], H3DID_BACK_TEX0_DROP); 
			case 1: return BIT(m_data[5], H3DID_BACK_TEX1_DROP); 
			case 2: return BIT(m_data[5], H3DID_BACK_TEX2_DROP); 
			case 3: return BIT(m_data[5], H3DID_BACK_TEX3_DROP); 
			case 4: return BIT(m_data[5], H3DID_BACK_TEX4_DROP); 
			case 5: return BIT(m_data[5], H3DID_BACK_TEX5_DROP); 
			case 6: return BIT(m_data[5], H3DID_BACK_TEX6_DROP); 
			case 7: return BIT(m_data[5], H3DID_BACK_TEX7_DROP); 
			default: return false;
		}
	};

	bool _hoops_SAAR() const { return BIT(m_data[0], H3DID_PHYSICAL_REFLECTION); };
	bool _hoops_GAC() const { return BIT(m_data[3], H3DID_ENVIRONMENT_TEXTURE); };
	bool _hoops_ARC() const { return BIT(m_data[2], H3DID_BUMP_TEXTURE); };
	bool _hoops_GRC() const { return BIT(m_data[2], H3DID_SPECULAR_TEXTURE); };
	bool _hoops_AAC() const { return BIT(m_data[3], H3DID_MIRROR_TEXTURE); };
	bool _hoops_HRC() const { return BIT(m_data[3], H3DID_TRANSMISSION_TEXTURE); };
	bool _hoops_IPAR() const { return BIT(m_data[3], H3DID_TRANSMISSION_TEX_MODULATE); };
	bool _hoops_CRC() const { return BIT(m_data[3], H3DID_EMISSION_TEXTURE); };
	bool _hoops_SPAR() const { return BIT(m_data[3], H3DID_EMISSION_TEX_MODULATE); };

	bool _hoops_GHRR() const { return BIT(m_data[2], H3DID_HAS_HANDEDNESS); };
	bool _hoops_HIAR() const { return BIT(m_data[2], _hoops_RCH); }
	bool _hoops_IIAR() const { return BIT(m_data[2], H3DID_DEPTH_WRITING_SINGLE_PASS); }
	float	   _hoops_CPRR() const { return BIT(m_data[0], H3DID_NORMAL_FLIP_NEGATIVE) ? -1 : +1; }
	int		   _hoops_SPRR() const { return BIT(m_data[0], H3DID_RIGHT_HANDED_MATRIX); }
	bool _hoops_AHRR() const { return BIT(m_data[3], H3DID_ATMOSPHERIC_ATTENUATION); };
	bool _hoops_PHRR()	const {return BIT(m_data[3], H3DID_NON_UNIFORM_SCALE); };
	bool _hoops_IPRR() const { return BIT(m_data[0], H3DID_WRITE_LUMINANCE); }

	// _hoops_HCIC _hoops_RGR _hoops_SASI _hoops_RCAR _hoops_ARCR _hoops_RAR _hoops_AAR?
	bool _hoops_RHPR(int _hoops_SPRAR) const
	{
		ASSERT( _hoops_SPRAR < 4 );
		int const shift = H3DID_SHADOW_MAP_VIEW_SHIFT + _hoops_SPRAR;
		return BIT(m_data[3], (1 << shift));
	}

	// _hoops_AGSH _hoops_GII _hoops_RCAR _hoops_ACAR _hoops_RAR _hoops_AAR?
	bool _hoops_IPC() const
	{
		return (m_data[3] & H3DID_SHADOW_MAP_VIEW_MASK) != 0;
	}

	void _hoops_SII(int _hoops_GCI, int number, int *_hoops_RCI, int *_hoops_ACI, int *_hoops_PCI) const;


	// _hoops_HGH _hoops_PGAP _hoops_SARR _hoops_RGR _hoops_CI _hoops_CHH _hoops_IPHR _hoops_AAH _hoops_CCA
	_hoops_IRRR _hoops_RIRAR()
	{
		if (_hoops_RPH())
			// _hoops_ICAH _hoops_AIRAR _hoops_IH _hoops_HSP _hoops_GCPR
			return _hoops_SARAR;

		if (_hoops_ARC())
			// _hoops_ICAH _hoops_AIRAR _hoops_IH _hoops_PIRAR.
			return _hoops_SARAR;

		if (_hoops_IRP() > 0)
			// _hoops_HIRAR _hoops_SIA _hoops_HRGR _hoops_IHPH, _hoops_SR _hoops_IIRAR _hoops_CIRAR 3 _hoops_ARI _hoops_HAH
			return _hoops_SARAR;

		if (_hoops_RIHR() || _hoops_SHC())
			// _hoops_RASRR _hoops_AIRRR _hoops_PAH _hoops_SHH _hoops_SIRAR
			return _hoops_SARAR;

		// _hoops_GCRAR _hoops_HRGR _hoops_RCRAR
		return _hoops_IARAR;
	}
	// _hoops_ACRAR _hoops_APIR _hoops_CI _hoops_HRP _hoops_IH _hoops_RGR _hoops_CI. _hoops_HCGAR _hoops_RCPP _hoops_CGPR _hoops_RGR _hoops_RSAS'_hoops_RA _hoops_SSRR
	bool _hoops_PCRAR()
	{
		bool _hoops_IA = true;

		if ( _hoops_SHC() )
		{
			m_data[6] = 0;
			m_data[5] &= ~(H3DID_DEFINED_MATERIAL_PS_LOCAL_PIXELS|H3DID_DEFINED_MATERIAL_PS_OUTER_PIXELS);
			m_data[5] &= ~H3DID_DEFINED_MATERIAL_MULTITEXTURE;
			m_data[5] &= ~H3DID_DEFINED_MATERIAL_PS_MASK;
		}
		else
			_hoops_IA = false;

		return _hoops_IA;
	}

	// _hoops_HCRAR _hoops_CCGP _hoops_HRP _hoops_IIGR _hoops_RGR _hoops_CI. _hoops_HCGAR _hoops_RCPP _hoops_CGPR _hoops_PSP _hoops_ICRAR _hoops_CSAP _hoops_SSRR.
	bool _hoops_CCRAR()
	{
		bool _hoops_IA = true;

		// _hoops_GGRR _hoops_IGPR _hoops_CHR _hoops_IHPH - _hoops_HSPP _hoops_ARI.
		int _hoops_CAP = ((m_data[1] & H3DID_SHADOW_MAP_SAMPLES) >> 6);
		if (_hoops_CAP > 0)
		{
			// _hoops_HCRAR _hoops_HPP _hoops_SPR _hoops_PAPA
			--_hoops_CAP;
			m_data[1] &= ~H3DID_SHADOW_MAP_SAMPLES;
			_hoops_IAP(_hoops_CAP * 4);
		}
		else if (_hoops_HPC())
		{
			// _hoops_SCRAR _hoops_GSRAR _hoops_HRGR _hoops_IHPH, _hoops_HHSP _hoops_SGS _hoops_SPS
			m_data[2] &= ~H3DID_SHADOW_MAP_JITTER;
		}
		else if (_hoops_HCAR() > 0)
		{
			// _hoops_IHR _hoops_CHR _hoops_IHPH
			_hoops_PHR(_hoops_HCAR() - 1);
		}
		else if (_hoops_PCAR() > 0)
		{
			// _hoops_IHR _hoops_CHR _hoops_IHPH
			_hoops_HHR(_hoops_PCAR() - 1);
		}
		else if (_hoops_RPH())
		{
			// _hoops_IHR _hoops_HGAP _hoops_RIR _hoops_AIR _hoops_RCA, _hoops_HIS _hoops_SR _hoops_PAH'_hoops_RA _hoops_HPRAR _hoops_SGS _hoops_CCGR _hoops_RAS
			// _hoops_SR'_hoops_RISP _hoops_RSRAR _hoops_CAPR.
			m_data[3] &= ~H3DID_PER_PIXEL_LIGHTING;
		}
		/* _hoops_SAPRR _hoops_ASRAR _hoops_IS _hoops_PSRAR _hoops_CCGP _hoops_CHH _hoops_PHHR _hoops_ARI, _hoops_GGR _hoops_HSRAR _hoops_AGR _hoops_IIGR _hoops_ISRAR/
		   _hoops_AHGP _hoops_AGR _hoops_IIGR _hoops_CSRAR...
		_hoops_SHS
		{
		}
		*/
		else
		{
			// _hoops_ARRP _hoops_SHS _hoops_IS _hoops_AA
			_hoops_IA = false;
		}

		return _hoops_IA;
	}

	friend class H3DShaderHASH;
	friend class H3DShader;
};


/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_IIC _hoops_ISHGR
*****************************************************************************
*****************************************************************************/
#define _hoops_SA 131072

#ifdef DX9_DRIVER
typedef void * H3D_Shader_Handle;
#else
typedef int H3D_Shader_Handle;
#endif

#define _hoops_GGS		(H3D_Shader_Handle)(-1)
#define _hoops_SSRAR		(H3D_Shader_Handle)(-2)

enum H3D_Shader_Constant_Type {
	H3D_Float,
	H3D_Integer,
	H3D_Matrix,
	H3D_Vector
};

enum H3D_Constant_Table {
	H3D_VSConstant_Table,
	H3D_PSConstant_Table,
};

void _hoops_RHCR( H3DData *h3ddata, const _hoops_GSAR::_hoops_APCR& _hoops_PPCR, int const index, int const size, Vector& scale, Vector& bias );

enum H3D_Shader_Handle_Type {
	_hoops_PGRA,
	_hoops_HGRA,
	_hoops_IARA,
	_hoops_AGRA,

	_hoops_IIIR,
	_hoops_HIIR,
	_hoops_SGIR,
	_hoops_CIIR,
	_hoops_SPRA,
	_hoops_RHRA,
	_hoops_RRCR,

	_hoops_RRGA,
	_hoops_ARGA,
	_hoops_RPGA,
	_hoops_HPGA,
	_hoops_CPGA,
	_hoops_CHGA,

	_hoops_GGAAR/*[8]*/,
	_hoops_RGAAR/*[8]*/						= _hoops_GGAAR + 8,
	_hoops_AGAAR									= _hoops_RGAAR + 8,
	_hoops_PGAAR,
	_hoops_HGAAR,
	_hoops_IGAAR,
	_hoops_CGAAR,
	_hoops_SGAAR,
	_hoops_GRAAR,
	_hoops_RRAAR,

	_hoops_ARAAR,
	_hoops_PRAAR,
	_hoops_ICGA,

	_hoops_CCCR/*[4]*/,
	_hoops_PCCR/*[_hoops_HRAAR]*/			= _hoops_CCCR + 4,

	_hoops_PICR/*[_hoops_HRAAR]*/	= _hoops_PCCR + H3D_MAX_SHADOW_MAPS,
	_hoops_IICR/*[_hoops_HRAAR]*/	= _hoops_PICR + H3D_MAX_SHADOW_MAPS,

	_hoops_AHIR/*[_hoops_IRAAR]*/			= _hoops_IICR + H3D_MAX_SHADOW_MAPS,

	_hoops_GAIR					= _hoops_AHIR + H3D_MAX_TEXTURES,
	_hoops_RAIR,
	_hoops_RPIR,

	_hoops_PIPA,
	_hoops_HIPA,
	_hoops_IIPA,

	_hoops_IGHA,

	_hoops_SSAA,
	_hoops_PGPA,
	_hoops_HGPA,
	_hoops_SGPA,
	_hoops_CGPA,

	_hoops_GIGA,
	_hoops_CRAAR,
	_hoops_GCAA,
	_hoops_RCAA,
	_hoops_PCAA,

	_hoops_HSRA,
	_hoops_RGAA,
	_hoops_GCGA,
	_hoops_ACGA,
	_hoops_PCGA,
	_hoops_ICAA,
	_hoops_SRAAR,
	_hoops_GAAAR,
	_hoops_HRRA,
	_hoops_ARRA/*[_hoops_IRAAR]*/,
	_hoops_IRRA			= _hoops_ARRA + H3D_MAX_TEXTURES,
	_hoops_CRRA,
	_hoops_SRRA,
	_hoops_GARA,
	_hoops_RARA,
	_hoops_AARA,
	_hoops_IIHR,
	_hoops_CIHR,
	_hoops_IHPA/*[_hoops_RAAAR]*/,

	_hoops_AAAAR						= _hoops_IHPA + H3D_MAX_CUTTING_PLANES,		// _hoops_PAAAR _hoops_HAAAR _hoops_IAAAR _hoops_CAAAR'_hoops_SAAAR _hoops_GPAAR _hoops_RPAAR _hoops_APAAR _hoops_PPAAR

	_hoops_PSSR,
	_hoops_HSSR		= _hoops_PSSR + 15,
	_hoops_ISSR		= _hoops_HSSR + 15,
	_hoops_GGGA		= _hoops_ISSR + 15,
	_hoops_HPSR			= _hoops_GGGA + 15,
	_hoops_RHSR			= _hoops_HPSR + 15,
	_hoops_PHSR			= _hoops_RHSR + 15,
	_hoops_RISR			= _hoops_PHSR + 15,
	_hoops_HISR			= _hoops_RISR + 15,
	_hoops_ICSR			= _hoops_HISR + 15,
	_hoops_CCSR			= _hoops_ICSR + 15,
	_hoops_SCSR			= _hoops_CCSR + 15,
	_hoops_HPAAR					= _hoops_SCSR + 15,	//_hoops_IGI _hoops_IS _hoops_RCRP _hoops_IPAAR 15 _hoops_CPAAR

	_hoops_SSC,
};


class H3DShader : public CMO
{
protected:
	H3D_Shader_Handle _hoops_CSC[_hoops_SSC];

protected:
	const H3DShaderID _hoops_ACC;	// _hoops_HGI _hoops_RCC _hoops_CSAP _hoops_IGI _hoops_IS _hoops_ARPR _hoops_RH _hoops_CI, _hoops_PPR _hoops_IIP _hoops_SHPH. _hoops_HHIGR _hoops_HRGR _hoops_IGI _hoops_IH _hoops_SPAAR _hoops_RH _hoops_CI.
	H3DShaderID _hoops_PCC;			// _hoops_HGI _hoops_RCC _hoops_HRGR _hoops_IGI _hoops_HPGR _hoops_GHAAR _hoops_IS _hoops_RHAAR _hoops_RH _hoops_CI. _hoops_HHIGR _hoops_GHCA _hoops_SHH _hoops_HAGH _hoops_HII _hoops_RH _hoops_SIC _hoops_RPP _hoops_RH _hoops_CI _hoops_CSAP _hoops_AHAAR _hoops_GGR _hoops_PHAAR.
	bool _hoops_HCC;		// _hoops_HHAAR _hoops_PAR _hoops_HAR _hoops_RGR _hoops_CI _hoops_RRP _hoops_IS _hoops_IHAAR _hoops_RGHH _hoops_PAIR
	H3DData *_hoops_ISS;

	INLINE char const *_hoops_RGS (char const *ptr);
	INLINE char const *_hoops_RPS (char const *start, char alter *buffer);
	INLINE char const *_hoops_GHS (char const *start);
	bool _hoops_ACS (_hoops_PCS *_hoops_HCS, char const *ptr);

	// _hoops_ISIRR _hoops_SPCS _hoops_IPS-_hoops_CHAAR _hoops_SIRRR _hoops_CR _hoops_HICA _hoops_PAH'_hoops_RA.
	void operator=(const H3DShader& other)
	{
		(void)other;
		ASSERT(0);
	}

	// _hoops_HRS "_hoops_SHAAR", "_hoops_GHPC", _hoops_AHI. _hoops_GPGA _hoops_GPP _hoops_RHPP
	virtual char const * _hoops_CAHR(){return null;};

protected:
	bool _hoops_GAGR (char alter *_hoops_RAGR, int alter *_hoops_AAGR);
	char alter *_hoops_HRRR (H3DShaderID &id, char alter *ptr, char const *end, _hoops_IRRR _hoops_CRRR, _hoops_AHGR type);
	char alter *_hoops_RHGR (const char *filename, const char *string, char alter *_hoops_RAGR, char const *end, _hoops_AHGR type);
	char alter *_hoops_AIGR (const char *filename, const char *string, char alter *ptr, char const *end);
	char alter *_hoops_IGHR (const char *_hoops_CGHR, const char *_hoops_SGHR, char alter *_hoops_GRHR, int _hoops_RRHR, char const *_hoops_ARHR);
	void _hoops_PAHR (H3DShaderID &id, bool _hoops_HAHR, char alter *_hoops_GIAAR);
	bool _hoops_IHHR (char const *filename, char const *_hoops_RAGR);

public:
	int _hoops_ICC;
	int _hoops_SCC;
	int _hoops_GSC;
	int _hoops_RSC;
	_hoops_ISC _hoops_HSC;

	H3DShader (const H3DShaderID& id);
	virtual ~H3DShader () {};

	virtual bool Create(H3DData *h3ddata, const char *_hoops_IASRR = null) = 0;
	virtual bool _hoops_HHIH() = 0;

	void _hoops_SHGA (float *matrix);
	void _hoops_CCGA (H3DData const *h3ddata);
	void _hoops_IGRA (Net_Rendition const & nr);
	void _hoops_RIGA (Net_Rendition const & nr);
	void _hoops_GIHR (_hoops_ISC const *color);
	void _hoops_RCHR (Net_Rendition const & nr, _hoops_ACHR type, bool _hoops_PCHR);
	void _hoops_SIAA (Net_Rendition const & nr, Line_Rendition const & _hoops_GHP);
	void _hoops_CCAA (Net_Rendition const &nr, float size, bool _hoops_SCAA, bool _hoops_GSAA, H3DTexture *glyph);
	void _hoops_CHPA (Net_Rendition const &nr, _hoops_IAPA const *_hoops_RIAAR);
	void _hoops_HAPA (_hoops_IAPA const *_hoops_RIAAR);
	void _hoops_GIPA (_hoops_RIPA const & _hoops_AIPA);
	void _hoops_CIPA (Net_Rendition const &nr);
	virtual void _hoops_RAPRR(H3DTexture *texture, H3DData *h3ddata) = 0;
	virtual void _hoops_GGIR (bool _hoops_AIAAR = false) = 0;

	// _hoops_GGPR'_hoops_GRI _hoops_SIC _hoops_HRGR _hoops_IGI _hoops_IS _hoops_PIAAR _hoops_SCH.
	INLINE const H3DShaderID Key() const { return _hoops_ACC; }

	// _hoops_GGPR'_hoops_GRI _hoops_RCC _hoops_HIAAR _hoops_RSH _hoops_RH _hoops_CI _hoops_HRGR _hoops_IRCR. _hoops_CAIP'_hoops_RA _hoops_SGH _hoops_RGR _hoops_IH _hoops_SPAAR _hoops_RH _hoops_CI
	// _hoops_GAR _hoops_SCH _hoops_PAH _hoops_AGRP!
	INLINE const H3DShaderID ID() const { return _hoops_PCC; }


protected:
	// _hoops_RGHH: _hoops_PIAH _hoops_RGHH _hoops_IS _hoops_IRS _hoops_CI _hoops_SRSR
	// _hoops_PIH: _hoops_SRHR _hoops_IIAAR _hoops_RH _hoops_HSH
	// _hoops_CIAAR: _hoops_PHI _hoops_IIGR _hoops_HSH _hoops_GGR _hoops_PIH (_hoops_IS _hoops_ARP _hoops_SIRGR)
	// _hoops_SIAAR: _hoops_GCAAR _hoops_GPRR _hoops_IIGR _hoops_PIH (_hoops_RSGA, _hoops_AIIC, _hoops_AHI)
	virtual void _hoops_RCAAR(H3D_Constant_Table table, int type, int data) = 0;
	virtual void _hoops_ACAAR(H3D_Constant_Table table, int type, float data) = 0;
	virtual void _hoops_PCAAR(H3D_Constant_Table table, int type, void const *data, int _hoops_HCAAR, int _hoops_GPIGR = 1) = 0;
	virtual void _hoops_ICAAR(H3D_Constant_Table table, int type, float *data, int width) = 0;
	virtual void _hoops_CCAAR(H3D_Constant_Table table, int type, float *data, int _hoops_SIIRR, int width) = 0;
	virtual H3D_Shader_Handle GetConstantByName(H3D_Constant_Table table, char const * _hoops_SCAAR, char const * _hoops_GSAAR) = 0;
};



#define _hoops_RSAAR(_hoops_ASAAR, _hoops_PSAAR, _hoops_SCAAR, _hoops_GSAAR) _hoops_GHIA (\
	if (_hoops_CSC[_hoops_PSAAR] == _hoops_GGS) \
		_hoops_CSC[_hoops_PSAAR] = GetConstantByName(_hoops_ASAAR, _hoops_SCAAR, _hoops_GSAAR); \
);

#define _hoops_HSAAR(_hoops_ASAAR, _hoops_PSAAR, _hoops_SCAAR, _hoops_GSAAR, value, size, type) _hoops_GHIA (\
	_hoops_RSAAR(_hoops_ASAAR, _hoops_PSAAR, _hoops_SCAAR, _hoops_GSAAR); \
	if (_hoops_CSC[_hoops_PSAAR] != _hoops_SSRAR) \
		_hoops_PCAAR(_hoops_ASAAR, _hoops_PSAAR, value, type, size); \
);

#define _hoops_CGIR(_hoops_ASAAR, _hoops_PSAAR, _hoops_SCAAR, _hoops_GSAAR, value) _hoops_GHIA (\
	_hoops_RSAAR(_hoops_ASAAR, _hoops_PSAAR, _hoops_SCAAR, _hoops_GSAAR); \
	if (_hoops_CSC[_hoops_PSAAR] != _hoops_SSRAR) \
		_hoops_ACAAR(_hoops_ASAAR, _hoops_PSAAR, value); \
);

#define _hoops_HIHR(_hoops_ASAAR, _hoops_PSAAR, _hoops_SCAAR, _hoops_GSAAR, value, size) \
	_hoops_HSAAR(_hoops_ASAAR, _hoops_PSAAR, _hoops_SCAAR, _hoops_GSAAR, value, size, H3D_Float);

#define _hoops_ICCR(_hoops_ASAAR, _hoops_PSAAR, _hoops_SCAAR, _hoops_GSAAR, value) _hoops_GHIA (\
	_hoops_RSAAR(_hoops_ASAAR, _hoops_PSAAR, _hoops_SCAAR, _hoops_GSAAR); \
	if (_hoops_CSC[_hoops_PSAAR] != _hoops_SSRAR) \
		_hoops_RCAAR(_hoops_ASAAR, _hoops_PSAAR, value); \
);

#define _hoops_ISAAR(_hoops_ASAAR, _hoops_PSAAR, _hoops_SCAAR, _hoops_GSAAR, value, size) \
	_hoops_HSAAR(_hoops_ASAAR, _hoops_PSAAR, _hoops_SCAAR, _hoops_GSAAR, value, size, H3D_Integer);

#define _hoops_HCCR(_hoops_ASAAR, _hoops_PSAAR, _hoops_SCAAR, _hoops_GSAAR, value, _hoops_CSAAR) \
	_hoops_HSAAR(_hoops_ASAAR, _hoops_PSAAR, _hoops_SCAAR, _hoops_GSAAR, value, _hoops_CSAAR, H3D_Matrix);

// _hoops_RSGA _hoops_SIRGR _hoops_CHR _hoops_HAR _hoops_APP _hoops_HPGR _hoops_RGR _hoops_GHIR
#define _hoops_SSAAR(_hoops_ASAAR, _hoops_PSAAR, _hoops_SCAAR, _hoops_GSAAR, value, _hoops_CSAAR, size) _hoops_GHIA( \
	ASSERT(0); \
	_hoops_HSAAR(_hoops_ASAAR, _hoops_PSAAR, _hoops_SCAAR, _hoops_GSAAR, value, _hoops_CSAAR, H3D_Matrix); \
)

#define _hoops_PIIR(_hoops_ASAAR, _hoops_PSAAR, _hoops_SCAAR, _hoops_GSAAR, value, width) _hoops_GHIA (\
	_hoops_RSAAR(_hoops_ASAAR, _hoops_PSAAR, _hoops_SCAAR, _hoops_GSAAR); \
	if (_hoops_CSC[_hoops_PSAAR] != _hoops_SSRAR) \
		_hoops_CCAAR(_hoops_ASAAR, _hoops_PSAAR, value, 1, width); \
);

#define _hoops_HICR(_hoops_ASAAR, _hoops_PSAAR, _hoops_SCAAR, _hoops_GSAAR, value, size, width) _hoops_GHIA (\
	_hoops_RSAAR(_hoops_ASAAR, _hoops_PSAAR, _hoops_SCAAR, _hoops_GSAAR); \
	if (_hoops_CSC[_hoops_PSAAR] != _hoops_SSRAR) \
		_hoops_CCAAR(_hoops_ASAAR, _hoops_PSAAR, value, size, width); \
);



/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_GGPAR _hoops_ISHGR
*****************************************************************************
*****************************************************************************/
local void _hoops_RGPAR(H3DShader *_hoops_RSR, POINTER_SIZED_INT _hoops_HCIS, void const * const _hoops_AGPAR)
{
	_hoops_HP(_hoops_RSR);
	UNREFERENCED(_hoops_HCIS);
	UNREFERENCED(_hoops_AGPAR);
}

typedef VHash<POINTER_SIZED_INT, H3DShader *> ID_2_Shader_Hash;

class H3DShaderHASH : public CMO
{

private:
	ID_2_Shader_Hash *_hoops_PGPAR;
	H3DData *_hoops_ISS;
public:
	H3DShaderHASH (H3DData *h3ddata, int _hoops_HGPAR=1024) {
		_hoops_ISS = h3ddata;
		_hoops_PGPAR = POOL_NEW(HOOPS_WORLD->memory_pool, ID_2_Shader_Hash)(HOOPS_WORLD->memory_pool, _hoops_HGPAR);
	}
	~H3DShaderHASH () {
		_hoops_PGPAR->MapFunction(_hoops_RGPAR, _hoops_ISS);
		delete _hoops_PGPAR;
		_hoops_PGPAR = null;
	}

	void Insert (const H3DShaderID &id, H3DShader *_hoops_RSR) {
		_hoops_PGPAR->InsertItem(id._hoops_GHRAR(), _hoops_RSR);
	}
	H3DShader *Lookup (const H3DShaderID &id) {
		H3DShader *_hoops_RSR;
		int status, n;

		for (n = 0; ; n++) {
			status = _hoops_PGPAR->LookupNthItem(id._hoops_GHRAR(), n, &_hoops_RSR);
			if (status != ID_2_Shader_Hash::Success)
				return null;
			if (_hoops_RSR->Key() == id)
				return _hoops_RSR;
		}
	}

};


#endif //3D_hoops_IGPAR

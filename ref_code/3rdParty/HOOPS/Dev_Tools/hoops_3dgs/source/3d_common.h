/*
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.  Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.384 2011-01-13 22:30:14 boni Exp $
 */

#ifndef H3DCOMMON_H
#define H3DCOMMON_H

#include "windows_wrapper.h"	// _hoops_CGRI <_hoops_SPHGR._hoops_GGHR>, _hoops_PIHA _hoops_RCPS _hoops_SRS :(

#include "hoops.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "adt.h"
#include "database.h"
#include "driver.h"
#include "hpserror.h"
#include "patterns.h"
#include "phdraw.h"
#include "phedron.h"
#include "please.h"
#include "searchh.h"
#include "tandt.h"
#include "hversion.h"

#ifndef NUTCRACKER
#ifdef WINDOWS_SYSTEM
#include "msw.h"
#endif
#endif

/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_GHHGR _hoops_A
*****************************************************************************
*****************************************************************************/
#define	H3D_Bless_Constant					4096
#define H3D_Display_List_MINIMUM			32
#define H3D_Display_List_PREFERRED_SIZE		5000			//_hoops_CIRGR
#define H3D_Display_List_MAX_SIZE			0xffff			//_hoops_CIRGR & _hoops_CHCA _hoops_RPR
#define H3D_Hardware_Transform_Cutoff		256

// _hoops_RHHGR _hoops_IIGR _hoops_RH _hoops_SSRA _hoops_RI _hoops_HH _hoops_GGR _hoops_SPCR _hoops_PPR _hoops_GHCR. _hoops_SSGP _hoops_AGSR _hoops_SPAC (_hoops_RRI _hoops_CGGC _hoops_SGS _hoops_RH
// _hoops_CGPC _hoops_GRS _hoops_SHH _hoops_GGR _hoops_RH _hoops_IHAH) _hoops_HIH _hoops_RH _hoops_SSRA _hoops_HRGR _hoops_RRI _hoops_SIGC.
#define _hoops_GGAA 64
#define _hoops_APAA 8

// _hoops_AHHGR _hoops_IH _hoops_HCH _hoops_AGI _hoops_AHCR-_hoops_CCIR. _hoops_GSAH _hoops_IS _hoops_SAGR _hoops_RH _hoops_CCIR _hoops_CRGR [0, 1]
#define _hoops_CIRA 1000.0f

/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_GHHGR _hoops_CIGR _hoops_PPR _hoops_PHHGR
*****************************************************************************
*****************************************************************************/
#ifdef _DEBUG
#define H3D_SHADER_DEBUG
#endif


#ifndef _hoops_AIHR
#  define _hoops_AIHR(a,b,_hoops_HHHGR) !memcmp(a,b,_hoops_HHHGR)
#endif

#define _hoops_HGR(array) (sizeof(array)/sizeof((array)[0]))

//#_hoops_PPIP _hoops_IHHGR
#ifndef _hoops_CHHGR

local void _hoops_SHHGR()
{
	HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR, "Function needs implementation");
}

#define _hoops_GIHGR _hoops_SHHGR()
#endif


#define H3DD(dc) ((H3DData alter *)((dc)->_hoops_RIHGR))
#define H3DNRD(nr) (H3DD((nr)->_hoops_SRA))


#define _hoops_HP(p)			{ if (p) { delete (p);	   (p)=null; } }
#define H_SAFE_RELEASE(p)			{ if (p) { (p)->Release(); (p)=null; } }


#define _hoops_GAPI(line_style)\
	(!BIT(line_style->flags, LSF_SOLID) && \
	 (\
		/* _hoops_PSP _hoops_CCCI 16-_hoops_IGRH _hoops_SCCI */ \
		!ANYBIT(line_style->flags, LSF_BITS16|LSF_BITS32) || \
		ANYBIT(line_style->flags, LSF_COMPLEX_ANYBITS)\
	)\
)

/*
 * _hoops_GCRR _hoops_SCH _hoops_HHHA _hoops_CGPR _hoops_SR'_hoops_ASAR _hoops_GRP _hoops_SHCA _hoops_PAR 3D _hoops_CCH - _hoops_IRS _hoops_AIHGR _hoops_HRGR _hoops_PIHGR _hoops_IS _hoops_HIHGR _hoops_SIHH _hoops_GGSC.
 */
enum _hoops_IIHGR
{
	_hoops_GCCA, // _hoops_SHCA _hoops_PICA
	_hoops_SCAS, // 3D _hoops_PICA
};

/*
 * _hoops_CIHGR _hoops_GPIA _hoops_GPPC
 */
enum H3DGlyph
{
	H3D_GLYPH_DOT,
	H3D_GLYPH_FILLED_CIRCLE,
	H3D_GLYPH_FILLED_SQUARE,
	H3D_GLYPH_X_MARK,
	H3D_GLYPH_PLUS_MARK,

	// _hoops_GRSH _hoops_AHPH _hoops_GPPC _hoops_CHR _hoops_APP.
	H3D_GLYPH_UNSUPPORTED,

	// _hoops_HSRR _hoops_SIHGR _hoops_GPPC _hoops_SR _hoops_PAH'_hoops_RA _hoops_SRGS
	H3D_GLYPH_COUNT = H3D_GLYPH_UNSUPPORTED
};

#define _hoops_HSGH					1
#define _hoops_GCHGR		2
#define _hoops_PCRS		3
#define _hoops_ACRH						4
#define _hoops_RSAC					5
#define _hoops_GIPS					6
#define _hoops_SPHC					7
#define _hoops_SHRH							8
#define _hoops_RCHGR						9

typedef struct H3DRect_s {
	long left;
	long top;
	long right;
	long bottom;
} H3DRect;

enum H3D_Color_Format
{
	H3D_COLOR_RGBA,
	H3D_COLOR_ARGB,
	H3D_COLOR_ABGR,
};

typedef enum H3D_Driver_Shader_Type_e {
	H3D_Driver_Shader_Type_DX9,
	H3D_Driver_Shader_Type_OGL2,
} H3D_Driver_Shader_Type;


typedef unsigned int H3D_Color;
#define H3D_PACK_BYTES(a,b,c,d) ((H3D_Color)((((a)&0xff)<<24)|(((b)&0xff)<<16)|(((c)&0xff)<<8)|((d)&0xff)))
local H3D_Color _hoops_CHAP(H3D_Color_Format format, char r, char g, char b, char a)
{
	H3D_Color color;
	switch (format)
	{
	case H3D_COLOR_ARGB:
		color = H3D_PACK_BYTES(a,r,g,b);
		break;
	case H3D_COLOR_ABGR:
		color = H3D_PACK_BYTES(a,b,g,r);
		break;
	case H3D_COLOR_RGBA:
	default:
		color = H3D_PACK_BYTES(r,g,b,a);
		break;
	}
	return color;
}
local H3D_Color _hoops_GICP(H3D_Color_Format format, float r, float g, float b, float a)
{
	return _hoops_CHAP(format, (char)(r*255), (char)(g*255), (char)(b*255), (char)(a*255));
}


#define H3D_OBJ_INVALID			0
#define H3D_OBJ_IndexBuffer		1			/* _hoops_CIHA _hoops_ACHGR _hoops_CARA (_hoops_PCHGR)*/
#define H3D_OBJ_VertexBuffer	2			/* _hoops_GPHA _hoops_SRHR (_hoops_HCHGR) */
#define H3D_OBJ_Mesh		3			/* _hoops_CIHA _hoops_ACHGR _hoops_CARA (_hoops_ICHGR _hoops_RAIA _hoops_RGR _hoops_CCHGR _hoops_HAH)*/


/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_SCHGR _hoops_GSHGR _hoops_RSHGR
*****************************************************************************
*****************************************************************************/
#ifdef DX9_DRIVER
#include "d3dutil.h"
#define H3D_SURFACE_ID				LPDIRECT3DSURFACE9
#define H3D_TEXTURE_ID				LPDIRECT3DTEXTURE9
#else

#define H3D_SURFACE_ID				H3DRenderTarget *
#define H3D_TEXTURE_ID				H3DRenderTarget *
#endif


/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_ASHGR _hoops_PSHGR
*****************************************************************************
*****************************************************************************/

class H3D_Display_List_Bin;
class H3DActions;
class H3DCubeTexture;
class H3DTexture3D;
class H3DTexture;
struct H3DData;
class H3DIndexBufferCache;
class H3DIndexedBufferObject;
class H3DPost;
class H3DRenderTarget;
class H3DShaderID;
class H3DShader;
class H3DShaderHASH;
class H3DVertexBuffer;
class H3DVertexBufferCache;



/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_HSHGR _hoops_ISHGR

_hoops_HGI _hoops_CSHGR _hoops_IACH _hoops_CGRH _hoops_PGSA _hoops_SSHGR.  _hoops_AIGS _hoops_IS _hoops_SHH _hoops_GGIGR _hoops_RIR _hoops_RHPP.
*****************************************************************************
*****************************************************************************/
class H3DGPUTimer
{
public:
	H3DGPUTimer(H3DData* data) :
		_hoops_ISS(data),
		_hoops_RGIGR(_hoops_AGIGR),
		_hoops_PGIGR(true),
		_hoops_HGIGR(0),
		_hoops_IGIGR(0)
	{
	}

	// _hoops_SP _hoops_GH
	virtual ~H3DGPUTimer() {}

	// _hoops_RAP _hoops_RH _hoops_HSGR _hoops_RIP _hoops_IS _hoops_SSPC _hoops_RH _hoops_SPS _hoops_GHIR
	void _hoops_HHPP()
	{
		_hoops_PGIGR = true;
	}

	// _hoops_RRPP _hoops_GHIR _hoops_HII _hoops_CGHI _hoops_PRPP. _hoops_CGIGR _hoops_AASA *_hoops_SAHR _hoops_ARPP* _hoops_RH _hoops_PRPP _hoops_IS _hoops_SRCH _hoops_SGIGR _hoops_GRIGR.
	virtual size_t _hoops_SRPP() = 0;

	// _hoops_PCSH _hoops_IRS _hoops_SPPP _hoops_PRPP
	virtual void _hoops_GGPP() = 0;
	virtual void _hoops_PRHP() = 0;

protected:
	H3DData* _hoops_ISS;

	enum _hoops_RRIGR
	{
		_hoops_AGIGR,
		_hoops_ARIGR,
		_hoops_PRIGR,
		_hoops_HRIGR
	};

	_hoops_RRIGR _hoops_RGIGR;

	// _hoops_RAP _hoops_IS _hoops_HSGR _hoops_SRS _hoops_GHIR _hoops_IRIGR, _hoops_PGAP _hoops_AHPP _hoops_IS _hoops_AIPP _hoops_RRI _hoops_HSAR _hoops_SCH _hoops_CGH.
	bool _hoops_PGIGR;

	// _hoops_CRIGR _hoops_CCH _hoops_IACH
	_hoops_GSPGR _hoops_HGIGR;
	_hoops_GSPGR _hoops_IGIGR;
};


/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_SRIGR _hoops_ISHGR

_hoops_HGI _hoops_CSHGR _hoops_HRGR _hoops_IRS _hoops_PIPS _hoops_AARI _hoops_IRS _hoops_GPHA _hoops_RPCC _hoops_GAIGR.  _hoops_AIGS _hoops_IS _hoops_SHH
_hoops_GGIGR _hoops_RIR _hoops_RHPP.
*****************************************************************************
*****************************************************************************/

#define H3DVF								unsigned int

#define H3DVF_POSITION						0x0001
#define H3DVF_NORMAL						0x0002
#define H3DVF_DIFFUSE						0x0004
#define H3DVF_TEXCOUNT_1					0x0010
#define H3DVF_TEXCOUNT_2					0x0020
#define H3DVF_TEXCOUNT_3					0x0030
#define H3DVF_TEXCOUNT_4					0x0040
#define H3DVF_TEXCOUNT_5					0x0050
#define H3DVF_TEXCOUNT_6					0x0060
#define H3DVF_TEXCOUNT_7					0x0070
#define H3DVF_TEXCOUNT_8					0x0080
#define H3DVF_TEXCOUNT_MASK					0x00f0
#define H3DVF_TEXCOUNT_SHIFT				4
#define H3DVF_TEXCOUNT_LOOKUP(_hoops_PPCP)			((_hoops_PPCP & H3DVF_TEXCOUNT_MASK) >> H3DVF_TEXCOUNT_SHIFT)

#define H3DVF_TEXCOORD_SIZE(i, size)		((size-1) << (i * 2 + 16))
#define H3DVF_TEXCOORD_SIZE_LOOKUP(_hoops_PPCP, i)	(((_hoops_PPCP >> (i * 2 + 16)) & (0x3)) + 1)




/* _hoops_RAIGR _hoops_CIAGR _hoops_AAIGR _hoops_PAIGR */
#define H3DVF_PT			(H3DVF_POSITION)
#define H3DVF_PT_CLR		(H3DVF_POSITION | H3DVF_DIFFUSE)
#define H3DVF_PT_TEX		(H3DVF_POSITION | H3DVF_TEXCOUNT_1 | H3DVF_TEXCOORD_SIZE(0,3))
#define H3DVF_PT_NML_TEX	(H3DVF_PT_TEX | H3DVF_NORMAL)
#define H3DVF_PT_NML_TEX2	(H3DVF_PT_NML_TEX | H3DVF_TEXCOUNT_2 | H3DVF_TEXCOORD_SIZE(1,3))


class H3DVertexFormat : public CMO
{
protected:
	H3DVF _hoops_HAIGR;
	unsigned int m_size;



	void _hoops_IAIGR(int bit, bool state) {
		if (state)
			_hoops_HAIGR |= bit;
		else
			_hoops_HAIGR &= ~bit;
	};
public:
	H3DVertexFormat(H3DVF _hoops_CAIGR)
	{
		reset();
		_hoops_SAIGR(_hoops_CAIGR);
	};

	H3DVertexFormat() { reset(); };
	~H3DVertexFormat(){};

	void reset()
	{
		_hoops_HAIGR = 0;
		m_size = 0;
	}

	void _hoops_SAIGR(H3DVF _hoops_CAIGR)
	{
		_hoops_HAIGR |= _hoops_CAIGR;
	};

	void _hoops_AIHC(bool state = true) {_hoops_IAIGR(H3DVF_POSITION, state);};
	void _hoops_CCRS(bool state = true) {_hoops_IAIGR(H3DVF_NORMAL, state);};
	void _hoops_RPHC(bool state = true) {_hoops_IAIGR(H3DVF_DIFFUSE, state);};
	void _hoops_SCRS(int _hoops_GPIGR) {
		int _hoops_RPIGR = _hoops_APIGR();
		if (_hoops_GPIGR+1 > _hoops_RPIGR) {
			_hoops_PPIGR(_hoops_GPIGR+1);
		}
	};
	void _hoops_APHC() {_hoops_HAIGR += H3DVF_TEXCOUNT_1;};
	void _hoops_PPIGR(int _hoops_GPIGR) {
		_hoops_HAIGR &= ~H3DVF_TEXCOUNT_MASK;			// _hoops_SCAC _hoops_GGSR _hoops_APRS _hoops_SIH
		_hoops_HAIGR |= (H3DVF_TEXCOUNT_1 * _hoops_GPIGR);		// _hoops_GGCR _hoops_GGR _hoops_RH _hoops_HGRC _hoops_HPIGR
	};
	void _hoops_HIHC(int _hoops_GPIGR, int size) {_hoops_HAIGR |= H3DVF_TEXCOORD_SIZE(_hoops_GPIGR, size);};

	H3DVF _hoops_HPCP() {return _hoops_HAIGR;};
	bool _hoops_IPIGR() {return BIT(_hoops_HAIGR, H3DVF_POSITION);};
	bool _hoops_HHCP() {return BIT(_hoops_HAIGR, H3DVF_NORMAL);};
	bool _hoops_SHCP() {return BIT(_hoops_HAIGR, H3DVF_DIFFUSE);};
	bool _hoops_PSCP() {return ANYBIT (_hoops_HAIGR, ~(H3DVF_POSITION|H3DVF_NORMAL));};
	int _hoops_APIGR() {return H3DVF_TEXCOUNT_LOOKUP(_hoops_HAIGR);};
	int _hoops_CPIGR(int _hoops_GPIGR) {return H3DVF_TEXCOORD_SIZE_LOOKUP(_hoops_HAIGR, _hoops_GPIGR);};

	int _hoops_HGHS(bool _hoops_SPIGR = true, bool _hoops_GHIGR = true)
	{
		int _hoops_RHIGR = 1;

		if (_hoops_SPIGR)
			_hoops_RHIGR = sizeof(float);

		m_size = 0;

		if (_hoops_GHIGR) {
			if (_hoops_IPIGR())				m_size += 3;
			if (_hoops_HHCP())				m_size += 3;
		}
		if (_hoops_SHCP())				m_size += 1;

		for ( int i = 0; i < _hoops_APIGR(); ++i )
			m_size += _hoops_CPIGR(i);

		return m_size * _hoops_RHIGR;
	};

	bool operator == (H3DVertexFormat &right) { return _hoops_HAIGR == right._hoops_HAIGR; };
	bool operator != (H3DVertexFormat &right) { return _hoops_HAIGR != right._hoops_HAIGR; };
};


/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_AHIGR _hoops_ISHGR

_hoops_HGI _hoops_CSHGR _hoops_HRGR _hoops_IRS _hoops_PIPS _hoops_AARI _hoops_IRS _hoops_PHIGR _hoops_AIIC _hoops_GPHA _hoops_SRHR.  _hoops_HHIGR _hoops_IHIGR _hoops_IRS
_hoops_GPHA _hoops_AHC, _hoops_ASGA, _hoops_AHI. _hoops_IS _hoops_SHH _hoops_ARP _hoops_GGR _hoops_IRS _hoops_RRI _hoops_CHIGR _hoops_SHIGR.
*****************************************************************************
*****************************************************************************/
class H3DVertexBuffer : public CMO
{
private:
	float *_hoops_GIIGR;
	float *_hoops_RIIGR;

	float *_hoops_AIIGR;
	float *_hoops_PIIGR;

	float *_hoops_HIIGR;
	float *_hoops_IIIGR;

	int *_hoops_CIIGR;

	H3DVertexFormat _hoops_PPCP;
	int vstride;		// _hoops_GPHA _hoops_SIIGR
	int _hoops_GCIGR;		// _hoops_IGRI _hoops_SIIGR

	int _hoops_RCIGR;
	int _hoops_ACIGR;
	int _hoops_PCIGR;
	int _hoops_HCIGR;

	int _hoops_ICIGR;
	int _hoops_CCIGR;
	int _hoops_SCIGR;

	bool _hoops_GSIGR;
	int _hoops_RSIGR;

	bool _hoops_GHIGR;

	// _hoops_IRS _hoops_IPS _hoops_IIGR _hoops_IRS "_hoops_HPHR" _hoops_AHIGR, _hoops_GIIA _hoops_HPP _hoops_HPGR()
	bool _hoops_ASIGR;
	H3DVertexBuffer *_hoops_PSIGR;

public:
	H3DVertexBuffer(float *_hoops_HSIGR, float *_hoops_ISIGR, float *_hoops_CSIGR, H3DVertexFormat _hoops_SSIGR, int _hoops_GGCGR = 0)
	{
		_hoops_RGCGR();
		_hoops_IRA(_hoops_HSIGR, _hoops_ISIGR, _hoops_CSIGR, &_hoops_SSIGR, _hoops_GGCGR);
	}
	H3DVertexBuffer(float *_hoops_HSIGR, H3DVertexFormat _hoops_SSIGR, int _hoops_GGCGR = 0)
	{
		_hoops_RGCGR();
		_hoops_IRA(_hoops_HSIGR, &_hoops_SSIGR, _hoops_GGCGR);
	}
	H3DVertexBuffer()
	{
		_hoops_RGCGR();
	};

	~H3DVertexBuffer()
	{
		_hoops_PP();
	};
	void _hoops_PP()
	{
		if (!_hoops_ASIGR) {
			if (_hoops_GSIGR) {
				FREE_ARRAY (_hoops_RIIGR, _hoops_RCIGR, float);
				if (_hoops_PIIGR)
					FREE_ARRAY (_hoops_PIIGR, _hoops_ACIGR, float);
				if (_hoops_IIIGR)
					FREE_ARRAY (_hoops_IIIGR, _hoops_PCIGR, float);
			}

			if (_hoops_CIIGR) {
				FREE_ARRAY (_hoops_CIIGR, _hoops_HCIGR, int);
				_hoops_CIIGR = null;
				_hoops_HCIGR = 0;
			}
		}
	};

	H3DVertexBuffer(const H3DVertexBuffer &_hoops_PAIH)
	{
		COPY_MEMORY(&_hoops_PAIH, sizeof(H3DVertexBuffer), this);

		if (_hoops_PAIH._hoops_HCIGR) {
			_hoops_HCIGR = _hoops_PAIH._hoops_HCIGR;
			ALLOC_ARRAY (_hoops_CIIGR, _hoops_HCIGR, int);
			COPY_MEMORY (_hoops_PAIH._hoops_CIIGR, _hoops_HCIGR * sizeof(int), _hoops_CIIGR);
		}

		if (_hoops_GSIGR) {
			_hoops_RCIGR = vstride * _hoops_RSIGR;
			ALLOC_ARRAY (_hoops_RIIGR, _hoops_RCIGR, float);
			COPY_MEMORY (_hoops_PAIH._hoops_RIIGR, vstride * _hoops_RSIGR * sizeof(float), _hoops_RIIGR);
			_hoops_GIIGR = _hoops_RIIGR;
		}
	}

	INLINE void _hoops_RGCGR() {
		_hoops_GIIGR = null;
		_hoops_RIIGR = null;
		_hoops_AIIGR = null;
		_hoops_PIIGR = null;
		_hoops_HIIGR = null;
		_hoops_IIIGR = null;
		_hoops_CIIGR = null;
		H3DVertexFormat _hoops_PPCP = 0;
		vstride = 0;
		_hoops_GCIGR = 0;
		_hoops_RCIGR = 0;
		_hoops_ACIGR = 0;
		_hoops_PCIGR = 0;
		_hoops_HCIGR = 0;
		_hoops_ICIGR = 0;
		_hoops_CCIGR = 0;
		_hoops_SCIGR = 0;
		_hoops_GSIGR = 0;
		_hoops_RSIGR = 0;
		_hoops_ASIGR = false;
		_hoops_PSIGR = null;
	}

	void _hoops_IRA(float *_hoops_HSIGR, H3DVertexFormat *_hoops_SSIGR, int _hoops_GGCGR = 0) {
		_hoops_GHIGR = true;

		// _hoops_HRCR _hoops_SR _hoops_GA'_hoops_RA _hoops_AGCGR _hoops_PGCGR _hoops_PAR _hoops_SRHR _hoops_PPGS.
		ASSERT(_hoops_RIIGR == null || !_hoops_GSIGR);

		if (_hoops_GGCGR > 0)
			_hoops_GSIGR = true;
		else
			_hoops_GSIGR = false;

		vstride = 0;
		_hoops_GCIGR = 0;
		_hoops_PPCP = *_hoops_SSIGR;

		// _hoops_IHAH _hoops_RH _hoops_AII _hoops_IS _hoops_RH _hoops_AGRR _hoops_IGPC
		_hoops_ICIGR = _hoops_CCIGR = _hoops_SCIGR = -1;

		// _hoops_CSGA _hoops_SIIGR
		if (_hoops_PPCP._hoops_IPIGR()) {
			_hoops_ICIGR = vstride;
			vstride += 3;
		}
		if (_hoops_PPCP._hoops_HHCP()) {
			_hoops_CCIGR = vstride;
			vstride += 3;
		}
		if (_hoops_PPCP._hoops_SHCP()) {
			_hoops_SCIGR = vstride;
			vstride += 1;
		}
		if (_hoops_PPCP._hoops_APIGR() > 0) {
			if (_hoops_PPCP._hoops_APIGR() > _hoops_HCIGR) {
				if (_hoops_CIIGR)
					FREE_ARRAY (_hoops_CIIGR, _hoops_HCIGR, int);
				_hoops_HCIGR = _hoops_PPCP._hoops_APIGR();
				ALLOC_ARRAY (_hoops_CIIGR, _hoops_HCIGR, int);
			}

			for ( int i = 0; i < _hoops_PPCP._hoops_APIGR(); ++i ) {
				_hoops_CIIGR[i] = vstride;
				vstride += _hoops_PPCP._hoops_CPIGR(i);
			}
		}

		/* _hoops_GCRR _hoops_RCRR _hoops_RH _hoops_SIIGR _hoops_SR _hoops_CSGA _hoops_ARI _hoops_HRGR _hoops_RH _hoops_PSHR _hoops_GAR _hoops_RH _hoops_SPR _hoops_SR _hoops_CSGA _hoops_HII _hoops_RH _hoops_ICRS */
		ASSERT(vstride == _hoops_PPCP._hoops_HGHS(false));

		_hoops_RSIGR = _hoops_GGCGR;
		if (_hoops_GSIGR) {
			_hoops_RCIGR = vstride * _hoops_RSIGR;
			ALLOC_ARRAY (_hoops_GIIGR, _hoops_RCIGR, float);
		}
		else {
			_hoops_GIIGR = _hoops_HSIGR;
			_hoops_AIIGR = _hoops_HSIGR;
			_hoops_HIIGR = _hoops_HSIGR;
		}

		_hoops_RIIGR = _hoops_GIIGR;
		_hoops_PIIGR = _hoops_GIIGR;
		_hoops_IIIGR = _hoops_GIIGR;
	}

	void _hoops_IRA(float *_hoops_HSIGR, float *_hoops_ISIGR, float *_hoops_CSIGR, H3DVertexFormat *_hoops_SSIGR, int _hoops_GGCGR = 0) {
		_hoops_GHIGR = false;

		// _hoops_HRCR _hoops_SR _hoops_GA'_hoops_RA _hoops_AGCGR _hoops_PGCGR _hoops_PAR _hoops_SRHR _hoops_PPGS.
		ASSERT(_hoops_RIIGR == null || !_hoops_GSIGR);

		if (_hoops_GGCGR > 0)
			_hoops_GSIGR = true;
		else
			_hoops_GSIGR = false;

		vstride = 3;
		_hoops_GCIGR = 0;
		_hoops_PPCP = *_hoops_SSIGR;

		// _hoops_IHAH _hoops_RH _hoops_AII _hoops_IS _hoops_RH _hoops_AGRR _hoops_IGPC
		_hoops_ICIGR = _hoops_CCIGR = _hoops_SCIGR = -1;

		// _hoops_CSGA _hoops_SIIGR
		if (_hoops_PPCP._hoops_IPIGR())
			_hoops_ICIGR = 0;
		if (_hoops_PPCP._hoops_HHCP())
			_hoops_CCIGR = 0;
		if (_hoops_PPCP._hoops_SHCP()) {
			_hoops_SCIGR = _hoops_GCIGR;
			_hoops_GCIGR += 1;
		}
		if (_hoops_PPCP._hoops_APIGR() > 0) {
			if (_hoops_PPCP._hoops_APIGR() > _hoops_HCIGR) {
				if (_hoops_CIIGR)
					FREE_ARRAY (_hoops_CIIGR, _hoops_HCIGR, int);
				_hoops_HCIGR = _hoops_PPCP._hoops_APIGR();
				ALLOC_ARRAY (_hoops_CIIGR, _hoops_HCIGR, int);
			}

			for ( int i = 0; i < _hoops_PPCP._hoops_APIGR(); ++i ) {
				_hoops_CIIGR[i] = _hoops_GCIGR;
				_hoops_GCIGR += _hoops_PPCP._hoops_CPIGR(i);
			}
		}

		_hoops_RSIGR = _hoops_GGCGR;
		if (_hoops_GSIGR) {
			_hoops_RCIGR = vstride * _hoops_RSIGR;
			ALLOC_ARRAY (_hoops_GIIGR, _hoops_RCIGR, float);
			if (_hoops_PPCP._hoops_HHCP()) {
				_hoops_ACIGR = vstride * _hoops_RSIGR;
				ALLOC_ARRAY (_hoops_AIIGR, _hoops_ACIGR, float);
			}
			if (_hoops_PPCP._hoops_PSCP()) {
				_hoops_PCIGR = _hoops_GCIGR * _hoops_RSIGR;
				ALLOC_ARRAY (_hoops_HIIGR, _hoops_PCIGR, float);
			}
		}
		else {
			_hoops_GIIGR = _hoops_HSIGR;
			_hoops_AIIGR = _hoops_ISIGR;
			_hoops_HIIGR = _hoops_CSIGR;
		}

		_hoops_RIIGR = _hoops_GIIGR;
		_hoops_PIIGR = _hoops_AIIGR;
		_hoops_IIIGR = _hoops_HIIGR;
	}

	INLINE void _hoops_HGCGR(H3DVertexBuffer *_hoops_IGCGR) {
		_hoops_PSIGR = _hoops_IGCGR;
	}

	// _hoops_SGSS _hoops_PSCH
	INLINE void reset() {
		_hoops_GIIGR = _hoops_RIIGR;
		_hoops_AIIGR = _hoops_PIIGR;
		_hoops_HIIGR = _hoops_IIIGR;
	};
	INLINE void _hoops_IPPH(int _hoops_CGCGR) {

		int _hoops_SGCGR = _hoops_GIIGR - _hoops_RIIGR;
		int _hoops_GRCGR = _hoops_HIIGR - _hoops_IIIGR;

		float *_hoops_RRCGR = _hoops_RIIGR;
		float *_hoops_ARCGR = _hoops_PIIGR;
		float *_hoops_PRCGR = _hoops_IIIGR;
		int	_hoops_HRCGR = _hoops_RCIGR;
		int	_hoops_IRCGR = _hoops_PCIGR;
		bool _hoops_CRCGR = _hoops_GSIGR;

		if (_hoops_GHIGR)
			_hoops_RCIGR = vstride * _hoops_CGCGR;
		else {
			_hoops_RCIGR = vstride * _hoops_CGCGR;
			_hoops_PCIGR = _hoops_GCIGR * _hoops_CGCGR;
		}

		ALLOC_ARRAY (_hoops_RIIGR, _hoops_RCIGR, float);
		COPY_MEMORY(_hoops_RRCGR, vstride * _hoops_AHIA(_hoops_RSIGR, _hoops_CGCGR) * sizeof(float), _hoops_RIIGR);
		if (_hoops_PIIGR) {
			ALLOC_ARRAY (_hoops_PIIGR, _hoops_RCIGR, float);
			COPY_MEMORY(_hoops_ARCGR, vstride * _hoops_AHIA(_hoops_RSIGR, _hoops_CGCGR) * sizeof(float), _hoops_PIIGR);
		}
		if (_hoops_IIIGR) {
			ALLOC_ARRAY (_hoops_IIIGR, _hoops_PCIGR, float);
			COPY_MEMORY(_hoops_PRCGR, _hoops_GCIGR * _hoops_AHIA(_hoops_RSIGR, _hoops_CGCGR) * sizeof(float), _hoops_IIIGR);
		}
		_hoops_GSIGR = true;

		if (_hoops_CRCGR) {
			FREE_ARRAY (_hoops_RRCGR, _hoops_HRCGR, float);
			if (_hoops_ARCGR)
				FREE_ARRAY (_hoops_ARCGR, _hoops_HRCGR, float);
			if (_hoops_PRCGR)
				FREE_ARRAY (_hoops_PRCGR, _hoops_IRCGR, float);
		}

		_hoops_RSIGR = _hoops_CGCGR;
		_hoops_GIIGR = _hoops_RIIGR + _hoops_SGCGR;
		if (_hoops_PIIGR)
			_hoops_AIIGR = _hoops_PIIGR + _hoops_SGCGR;
		if (_hoops_IIIGR)
			_hoops_HIIGR = _hoops_IIIGR + _hoops_GRCGR;
	}

	INLINE void _hoops_AHIH(int _hoops_SRCGR, int _hoops_GACGR = 1) {
		if (_hoops_GHIGR) {
			COPY_MEMORY(_hoops_GIIGR, _hoops_GACGR*vstride*sizeof(float), _hoops_GIIGR+_hoops_SRCGR*vstride);
		}
		else {
			COPY_MEMORY(_hoops_GIIGR, _hoops_GACGR*vstride*sizeof(float), _hoops_GIIGR+_hoops_SRCGR*vstride);
			if (_hoops_AIIGR)
				COPY_MEMORY(_hoops_AIIGR, _hoops_GACGR*vstride*sizeof(float), _hoops_AIIGR+_hoops_SRCGR*vstride);
			if (_hoops_HIIGR)
				COPY_MEMORY(_hoops_HIIGR, _hoops_GACGR*_hoops_GCIGR*sizeof(float), _hoops_HIIGR+_hoops_SRCGR*_hoops_GCIGR);
		}
	}

	INLINE void _hoops_AHIH(H3DVertexBuffer *_hoops_PCAP, int _hoops_GACGR = 1) {
		if (_hoops_GHIGR) {
			COPY_MEMORY(_hoops_GIIGR, _hoops_GACGR*vstride*sizeof(float), _hoops_PCAP->_hoops_GIIGR);
		}
		else {
			COPY_MEMORY(_hoops_GIIGR, _hoops_GACGR*vstride*sizeof(float), _hoops_PCAP->_hoops_GIIGR);
			if (_hoops_AIIGR)
				COPY_MEMORY(_hoops_AIIGR, _hoops_GACGR*vstride*sizeof(float), _hoops_PCAP->_hoops_AIIGR);
			if (_hoops_HIIGR)
				COPY_MEMORY(_hoops_HIIGR, _hoops_GACGR*_hoops_GCIGR*sizeof(float), _hoops_PCAP->_hoops_HIIGR);
		}
	}


	INLINE int _hoops_RACGR() {return _hoops_RSIGR;};

	// _hoops_RH _hoops_AACGR() _hoops_PSCH _hoops_CHR _hoops_RGAR _hoops_RPRI _hoops_CCA _hoops_PCCP _hoops_PACGR _hoops_PAR _hoops_AHC _hoops_RGAR _hoops_CPIH
	INLINE float * _hoops_HACGR() {
		ASSERT(_hoops_GHIGR || (!_hoops_AIIGR && !_hoops_HIIGR));
		return _hoops_GIIGR;
	};
	INLINE float * _hoops_ARHS() {
		ASSERT(_hoops_GHIGR || (!_hoops_AIIGR && !_hoops_HIIGR));
		return _hoops_RIIGR;
	};
	INLINE float * _hoops_IAHH(int index) {
		ASSERT(_hoops_GHIGR || (!_hoops_AIIGR && !_hoops_HIIGR));
		return _hoops_RIIGR + index * vstride;
	};
	INLINE int _hoops_IACGR() {return (_hoops_GIIGR - _hoops_RIIGR) / vstride;};
	INLINE H3DVertexFormat & _hoops_HPCP() {return _hoops_PPCP;};
	INLINE int _hoops_CACGR() {return vstride;};
	INLINE int _hoops_SACGR() {return _hoops_ICIGR;};
	INLINE int _hoops_GPCGR() {return _hoops_CCIGR;};
	INLINE int _hoops_RPCGR() {return _hoops_SCIGR;};
	INLINE int _hoops_APCGR() {return (_hoops_CIIGR) ? _hoops_CIIGR[0] : -1;};

	// _hoops_HGCR() _hoops_PSCH
	INLINE float _hoops_PPCGR() {return _hoops_GIIGR[_hoops_ICIGR+0];}
	INLINE float _hoops_HPCGR() {return _hoops_GIIGR[_hoops_ICIGR+1];}
	INLINE float _hoops_IPCGR() {return _hoops_GIIGR[_hoops_ICIGR+2];}

	INLINE float _hoops_CPCGR() {return _hoops_AIIGR[_hoops_CCIGR+0];}
	INLINE float _hoops_SPCGR() {return _hoops_AIIGR[_hoops_CCIGR+1];}
	INLINE float _hoops_GHCGR() {return _hoops_AIIGR[_hoops_CCIGR+2];}

	INLINE float _hoops_RHCGR(int _hoops_AHCGR = 0) {
		if (_hoops_AHCGR < _hoops_PPCP._hoops_APIGR())
			return _hoops_HIIGR[_hoops_CIIGR[_hoops_AHCGR]+0];
		return -1;
	}
	INLINE float _hoops_PHCGR(int _hoops_AHCGR = 0) {
		if (_hoops_AHCGR < _hoops_PPCP._hoops_APIGR())
			return _hoops_HIIGR[_hoops_CIIGR[_hoops_AHCGR]+1];
		return -1;
	}
	INLINE float _hoops_HHCGR(int _hoops_AHCGR = 0) {
		if (_hoops_AHCGR < _hoops_PPCP._hoops_APIGR())
			return _hoops_HIIGR[_hoops_CIIGR[_hoops_AHCGR]+2];
		return -1;
	}
	INLINE float _hoops_IHCGR(int _hoops_AHCGR = 0) {
		if (_hoops_AHCGR < _hoops_PPCP._hoops_APIGR())
			return _hoops_HIIGR[_hoops_CIIGR[_hoops_AHCGR]+3];
		return -1;
	}

	// _hoops_ARP() _hoops_PSCH
	INLINE void _hoops_AHCP(Point const & p) {
		if (_hoops_ICIGR >= 0) {
			_hoops_GIIGR[_hoops_ICIGR+0] = p.x;
			_hoops_GIIGR[_hoops_ICIGR+1] = p.y;
			_hoops_GIIGR[_hoops_ICIGR+2] = p.z;
		}
	}
	INLINE void _hoops_AHCP(float _hoops_CHCGR, float _hoops_SHCGR, float _hoops_GICGR) {
		if (_hoops_ICIGR >= 0) {
			_hoops_GIIGR[_hoops_ICIGR+0] = _hoops_CHCGR;
			_hoops_GIIGR[_hoops_ICIGR+1] = _hoops_SHCGR;
			_hoops_GIIGR[_hoops_ICIGR+2] = _hoops_GICGR;
		}
	}
	INLINE void x(float _hoops_CHCGR) {if (_hoops_ICIGR >= 0) _hoops_GIIGR[_hoops_ICIGR+0] = _hoops_CHCGR;}
	INLINE void y(float _hoops_SHCGR) {if (_hoops_ICIGR >= 0) _hoops_GIIGR[_hoops_ICIGR+1] = _hoops_SHCGR;}
	INLINE void z(float _hoops_GICGR) {if (_hoops_ICIGR >= 0) _hoops_GIIGR[_hoops_ICIGR+2] = _hoops_GICGR;}

	INLINE void _hoops_IHCP(Vector const & v) {
		if (_hoops_CCIGR >= 0) {
			_hoops_AIIGR[_hoops_CCIGR+0] = v.x;
			_hoops_AIIGR[_hoops_CCIGR+1] = v.y;
			_hoops_AIIGR[_hoops_CCIGR+2] = v.z;
		}
	};
	INLINE void _hoops_IHCP(float _hoops_RICGR, float _hoops_AICGR, float _hoops_PICGR) {
		if (_hoops_CCIGR >= 0) {
			_hoops_AIIGR[_hoops_CCIGR+0] = _hoops_RICGR;
			_hoops_AIIGR[_hoops_CCIGR+1] = _hoops_AICGR;
			_hoops_AIIGR[_hoops_CCIGR+2] = _hoops_PICGR;
		}
	}
	INLINE void nx(float _hoops_RICGR) {if (_hoops_CCIGR >= 0) _hoops_AIIGR[_hoops_CCIGR+0] = _hoops_RICGR;}
	INLINE void ny(float _hoops_AICGR) {if (_hoops_CCIGR >= 0) _hoops_AIIGR[_hoops_CCIGR+1] = _hoops_AICGR;}
	INLINE void nz(float _hoops_PICGR) {if (_hoops_CCIGR >= 0) _hoops_AIIGR[_hoops_CCIGR+2] = _hoops_PICGR;}

	INLINE void color(H3D_Color const _hoops_HICGR) {COPY_MEMORY(&_hoops_HICGR, sizeof(H3D_Color), &_hoops_HIIGR[_hoops_SCIGR]);}
	INLINE void color(char a, char b, char c, char d) {color(H3D_PACK_BYTES(a, b, c, d));}
	INLINE void color(H3D_Color_Format format, char a, char b, char c, char d)	{color(_hoops_CHAP(format,a,b,c,d));}
	INLINE void color(H3D_Color_Format format, float a, float b, float c, float d)	{color(_hoops_GICP(format,a,b,c,d));}
	INLINE void color(H3D_Color_Format format, const RGBAS32 _hoops_PIHR) {
		color(_hoops_CHAP(format,_hoops_PIHR.r, _hoops_PIHR.g, _hoops_PIHR.b, _hoops_PIHR.a));
	}

	INLINE void _hoops_IICGR(_hoops_ARPA const *_hoops_IICGR, int _hoops_AHCGR = 0) {u(_hoops_IICGR->a,_hoops_AHCGR); v(_hoops_IICGR->b,_hoops_AHCGR); s(_hoops_IICGR->c,_hoops_AHCGR); t(_hoops_IICGR->d,_hoops_AHCGR);}
	INLINE void _hoops_IICGR(float _hoops_CICGR, float _hoops_SICGR, float is, float it, int _hoops_AHCGR = 0) {u(_hoops_CICGR,_hoops_AHCGR); v(_hoops_SICGR,_hoops_AHCGR); s(is,_hoops_AHCGR); t(it,_hoops_AHCGR);}
	INLINE void _hoops_IICP(float _hoops_CICGR, float _hoops_SICGR, float is, int _hoops_AHCGR = 0) {u(_hoops_CICGR,_hoops_AHCGR); v(_hoops_SICGR,_hoops_AHCGR); s(is,_hoops_AHCGR);}
	INLINE void _hoops_ARHC(float _hoops_CICGR, float _hoops_SICGR, int _hoops_AHCGR = 0) {u(_hoops_CICGR,_hoops_AHCGR); v(_hoops_SICGR,_hoops_AHCGR); }
	INLINE void u(float _hoops_CICGR, int _hoops_AHCGR = 0) {
		if (_hoops_AHCGR < _hoops_PPCP._hoops_APIGR() && _hoops_CIIGR[_hoops_AHCGR] >= 0 && _hoops_PPCP._hoops_CPIGR(_hoops_AHCGR) > 0)
			_hoops_HIIGR[_hoops_CIIGR[_hoops_AHCGR]+0] = _hoops_CICGR;
	}
	INLINE void v(float _hoops_SICGR, int _hoops_AHCGR = 0) {
		if (_hoops_AHCGR < _hoops_PPCP._hoops_APIGR() && _hoops_CIIGR[_hoops_AHCGR] >= 0 && _hoops_PPCP._hoops_CPIGR(_hoops_AHCGR) > 1)
			_hoops_HIIGR[_hoops_CIIGR[_hoops_AHCGR]+1] = _hoops_SICGR;
	}
	INLINE void s(float is, int _hoops_AHCGR = 0) {
		if (_hoops_AHCGR < _hoops_PPCP._hoops_APIGR() && _hoops_CIIGR[_hoops_AHCGR] >= 0 && _hoops_PPCP._hoops_CPIGR(_hoops_AHCGR) > 2)
			_hoops_HIIGR[_hoops_CIIGR[_hoops_AHCGR]+2] = is;
	}
	INLINE void t(float it, int _hoops_AHCGR = 0) {
		if (_hoops_AHCGR < _hoops_PPCP._hoops_APIGR() && _hoops_CIIGR[_hoops_AHCGR] >= 0 && _hoops_PPCP._hoops_CPIGR(_hoops_AHCGR) > 3)
			_hoops_HIIGR[_hoops_CIIGR[_hoops_AHCGR]+3] = it;
	}

	INLINE H3DVertexBuffer & _hoops_RRCI(int const index) {
		if (_hoops_PSIGR->_hoops_RIIGR != _hoops_RIIGR ||
			_hoops_PSIGR->_hoops_PPCP != _hoops_PPCP)
		{
			*_hoops_PSIGR = *this;
			_hoops_PSIGR->_hoops_ASIGR = true;
		}

		if (_hoops_GHIGR) {
			_hoops_PSIGR->_hoops_RIIGR = _hoops_PSIGR->_hoops_GIIGR = _hoops_GIIGR + index*vstride;
			_hoops_PSIGR->_hoops_PIIGR = _hoops_PSIGR->_hoops_AIIGR = _hoops_GIIGR + index*vstride;
			_hoops_PSIGR->_hoops_IIIGR = _hoops_PSIGR->_hoops_HIIGR = _hoops_GIIGR + index*vstride;
		}
		else {
			_hoops_PSIGR->_hoops_RIIGR = _hoops_PSIGR->_hoops_GIIGR = _hoops_GIIGR + index*vstride;
			if (_hoops_AIIGR)
				_hoops_PSIGR->_hoops_PIIGR = _hoops_PSIGR->_hoops_AIIGR = _hoops_AIIGR + index*vstride;
			if (_hoops_HIIGR)
				_hoops_PSIGR->_hoops_IIIGR = _hoops_PSIGR->_hoops_HIIGR = _hoops_HIIGR + index*_hoops_GCIGR;
		}
		return *_hoops_PSIGR;
	}
	INLINE H3DVertexBuffer const & _hoops_CPPH(int const _hoops_GCCGR = 1) {
		//_hoops_AGHR(_hoops_RGR != &_hoops_RCCGR->_hoops_ACCGR);	//_hoops_ACCGR _hoops_PIHA _hoops_HAR _hoops_SHH _hoops_APII!!
		if (_hoops_GHIGR) {
			int _hoops_PCCGR = _hoops_GCCGR * vstride;
			_hoops_GIIGR += _hoops_PCCGR;
			_hoops_AIIGR += _hoops_PCCGR;
			_hoops_HIIGR += _hoops_PCCGR;
		}
		else {
			_hoops_GIIGR += _hoops_GCCGR * vstride;
			if (_hoops_AIIGR)
				_hoops_AIIGR += _hoops_GCCGR * vstride;
			if (_hoops_HIIGR)
				_hoops_HIIGR += _hoops_GCCGR * _hoops_GCIGR;
		}
		return *this;
	}

	INLINE int const length() const
	{
		return (_hoops_GIIGR - _hoops_RIIGR) / vstride;
	}
};


/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_SCHGR _hoops_HCCGR
*****************************************************************************
*****************************************************************************/
#define H3D_SOFTWARE_XFORM_BIN_SIZE			256				//_hoops_AHPA _hoops_IGIR _hoops_IS _hoops_ASSS _hoops_IH _hoops_SCGI _hoops_PGHGR _hoops_ICCGR _hoops_CCCGR

enum H3D_Segdl_Flags {
	H3D_SEGDL_BLESSED_GEOMETRY		= 0x0001,
	H3D_SEGDL_BLESSED_SEGMENT		= 0x0002,
	H3D_SEGDL_SINGLE_INSTANCED		= 0x0004,
	H3D_SEGDL_HAS_EXPLICIT_VISIBLE  = 0x0008
};


enum H3D_Display_List_Type {
	H3D_DL_NONE = 0,
	H3D_DL_TEXTURE = 1,
	H3D_DL_SHADOW_MAP = 2,
	H3D_DL_GEOMETRY = 3,
	H3D_DL_SEGMENT_POLYLINE = 4,
	H3D_DL_SEGMENT_POLYGON = 5,
	H3D_DL_SEGMENT_TREE = 6,
};

class H3D_Display_List;
typedef VList<H3D_Display_List *> H3D_Display_List_List;
typedef VList<H3DIndexedBufferObject *> H3DIndexedBufferObject_List;
typedef VList<H3D_Display_List_Bin *> _hoops_AGGI;
typedef VHash<int, _hoops_AGGI *> _hoops_ISSH;


bool _hoops_AACR(Net_Rendition const & nr,
							  _hoops_GACR alter **_hoops_ASRGR,
							  _hoops_GACR alter **dl,
							  H3D_Display_List alter **odl,
							  unsigned int type);

class H3D_Display_List : public _hoops_AGCI {
public:

	unsigned int type;
	int _hoops_CARH;		/* _hoops_SCCGR _hoops_HCHC _hoops_IIGR _hoops_PPGS _hoops_RGR _hoops_CARA _hoops_GSCGR */

	int							_hoops_RAHA;
	H3DVertexFormat				_hoops_PPCP;

	union {
		struct {
			H3DTexture			*id;
			H3DTexture			*_hoops_SRAGR;
			bool				_hoops_IAGGR;
		}	texture;
		struct {
			H3DIndexedBufferObject_List *	id;
			int					_hoops_SGAS;
			unsigned int		_hoops_GSAI;
			unsigned int		_hoops_SRHA;
			unsigned int		_hoops_CARI;
			unsigned int		_hoops_IRRI;
			Param_Source		_hoops_HSRC;
			POINTER_SIZED_INT	_hoops_HGAC;
			struct {
				int total;
				int _hoops_PHHA;
				int point_count;
			}	_hoops_IGGI;
		}	geometry;
		struct {
			H3DTexture			*id;
			int					_hoops_HAP;
			float				transform[16];
		}	_hoops_HRR;
		struct {
			H3D_Display_List_List *_hoops_GHPI; // _hoops_RSCGR _hoops_ASCGR _hoops_CGHS
			bool				_hoops_ARPI, _hoops_SAR;
			int					_hoops_PPPI, _hoops_HPPI;
			float				_hoops_IPPI, _hoops_CPPI, _hoops_SPPI;
			struct {
				int total;
				int _hoops_PHHA;
				int point_count;
			}	_hoops_IGGI;
		}   _hoops_RPPI;
		struct {
			H3D_Display_List_List *_hoops_PCII; // _hoops_PSCGR _hoops_HSCGR _hoops_CGHS
			H3D_Display_List_List *_hoops_GHPI; // _hoops_RSCGR _hoops_ASCGR _hoops_CGHS
			H3D_Display_List_List *_hoops_HCII; // _hoops_ISCGR _hoops_CSCGR _hoops_CGHS
			bool				_hoops_GCII, _hoops_SAR;
			int					_hoops_PPPI, _hoops_HPPI;
			float				_hoops_IPPI, _hoops_CPPI, _hoops_SPPI;
		}   _hoops_ACII;
		struct {
			H3D_Display_List_List *_hoops_ARRI;
			H3D_Display_List_List *_hoops_AGAI;
			H3D_Display_List_List *_hoops_GGAI;	// _hoops_AHHA
			H3D_Display_List_List *_hoops_RGAI;			// _hoops_AHHA
			H3D_Display_List_List *_hoops_GAAI;
			H3D_Display_List_List *_hoops_RAAI;
			H3D_Display_List_List *_hoops_CAPI;
			H3D_Display_List_List *_hoops_RCII;

			_hoops_ACHR			_hoops_RGP;
			_hoops_ACHR			_hoops_PCGI;  //_hoops_IAGH _hoops_SGS _hoops_SSCGR _hoops_GGR _hoops_HPP _hoops_GGSGR _hoops_IIGR _hoops_IRGH _hoops_RGSGR
			_hoops_GHGI			_hoops_CSA;
			unsigned int		flags;
		}	_hoops_ACGI;
	} 	item;
};

enum H3D_Vertex_Buffer_Style
{
	H3D_Invalid = 0,
	H3D_Shared_Vertices = 1,			// _hoops_GIHA _hoops_GCSP _hoops_GAPA _hoops_IIRGR
	H3D_Partially_Shared_Vertices = 2,	// _hoops_GIHA _hoops_GCSP _hoops_GIAA, _hoops_HIH _hoops_HAR _hoops_GAPA, _hoops_IIRGR.  _hoops_IAS._hoops_ISHI. _hoops_GPIC _hoops_RCA, _hoops_HIH _hoops_SR'_hoops_ASAR _hoops_SHSS _hoops_IS _hoops_AGSGR _hoops_PSAP _hoops_GGAR
	H3D_Unshared_Vertices = 3			// _hoops_GIHA _hoops_HAR _hoops_GCSP.  _hoops_HAHH _hoops_CGPR _hoops_IIH _hoops_CHR _hoops_PGSGR _hoops_HGSGR _hoops_IH _hoops_IGSGR _hoops_SARR, _hoops_IAS._hoops_ISHI. _hoops_GPIC-_hoops_CIP _hoops_HIH _hoops_GAGS
};



/* _hoops_RAIGR _hoops_CPAP / _hoops_RSGA _hoops_PSAI */
class _hoops_IRHA : public CMO_Pooled {

public:

	enum Type {
		_hoops_CGSGR = 0,
		_hoops_SGSGR,
		_hoops_GRSGR,
		_hoops_HCAI,
		_hoops_RRSGR,
	};

	_hoops_IRHA(
		Net_Rendition const &inr, 
		Tristrip const *its, 
		_hoops_ISGI const * _hoops_ARSGR, 
		_hoops_SSGI const * _hoops_PRSGR, 
		bool _hoops_HRSGR=false):nr(inr) 
	{
		ASSERT (its != null);
		geo = (void*)its;
		type = _hoops_SGSGR;
		_hoops_CAHS(its);

		if (its->_hoops_GSCP != null)
			priority = its->_hoops_GSCP->priority;
		else
			//_hoops_RH _hoops_HSPR _hoops_III _hoops_HRGR _hoops_IRSGR _hoops_CGPR _hoops_SR _hoops_HS _hoops_GPGR _hoops_PICA
			//_hoops_CRSGR _hoops_IS _hoops_SRSGR _hoops_SPR _hoops_CRHH (_hoops_IAS._hoops_ISHI. _hoops_GASGR).  _hoops_IPCP 
			//_hoops_GPII'_hoops_GRI _hoops_GHCP _hoops_CGH _hoops_IIP _hoops_RSGR _hoops_GH _hoops_GHHS _hoops_IGI
			priority = 0; 

		if ((_hoops_CPAI = _hoops_ARSGR) != null)
			_hoops_PRRH (_hoops_CPAI);

		if ((color = _hoops_PRSGR) != null)
			_hoops_PRRH (color);

		single = _hoops_HRSGR;
	};

	_hoops_IRHA(
		Net_Rendition const &inr, 
		Polyedge const *_hoops_RASGR, 
		_hoops_ISGI const * _hoops_ARSGR, 
		_hoops_SSGI const * _hoops_PRSGR, 
		bool _hoops_HRSGR=false):nr(inr) 
	{
		ASSERT (_hoops_RASGR != null);
		geo = (void*)_hoops_RASGR;
		type = _hoops_GRSGR;
		_hoops_CAHS(_hoops_RASGR);
		if (_hoops_RASGR->_hoops_GSCP != null)
			priority = _hoops_RASGR->_hoops_GSCP->priority;
		else
			priority = 0;  //_hoops_CACH _hoops_AHAC _hoops_GGR _hoops_AASGR-_hoops_IIHA _hoops_GPII _hoops_PPII _hoops_ARRS

		if ((_hoops_CPAI = _hoops_ARSGR) != null)
			_hoops_PRRH (_hoops_CPAI);

		if ((color = _hoops_PRSGR) != null)
			_hoops_PRRH (color);

		single = _hoops_HRSGR;
	};

	_hoops_IRHA(
		Net_Rendition const &inr, 
		Polymarker const *_hoops_PASGR, 
		_hoops_ISGI const * _hoops_ARSGR, 
		_hoops_SSGI const * _hoops_PRSGR, 
		bool _hoops_HRSGR=false):nr(inr) 
	{
		ASSERT (_hoops_PASGR != null);
		geo = (void*)_hoops_PASGR;
		type = _hoops_HCAI;
		_hoops_CAHS(_hoops_PASGR);
		if (_hoops_PASGR->_hoops_GSCP != null)
			priority = _hoops_PASGR->_hoops_GSCP->priority;
		else
			priority = 0;  //_hoops_CACH _hoops_AHAC _hoops_GGR _hoops_AASGR-_hoops_IIHA _hoops_GPII _hoops_PPII _hoops_ARRS

		if ((_hoops_CPAI = _hoops_ARSGR) != null)
			_hoops_PRRH (_hoops_CPAI);

		if ((color = _hoops_PRSGR) != null)
			_hoops_PRRH (color);

		single = _hoops_HRSGR;
	};

	_hoops_IRHA(Net_Rendition const &inr, 
		Geometry const * _hoops_HASGR, 
		_hoops_ISGI const * _hoops_ARSGR, 
		_hoops_SSGI const * _hoops_PRSGR, 
		bool _hoops_HRSGR=false):nr(inr) 
	{
		ASSERT (_hoops_HASGR != null);
		geo = (void*)_hoops_HASGR;
		type = _hoops_RRSGR;
		_hoops_PRRH (_hoops_HASGR);
		priority = _hoops_HASGR->priority;

		if ((_hoops_CPAI = _hoops_ARSGR) != null)
			_hoops_PRRH (_hoops_CPAI);

		if ((color = _hoops_PRSGR) != null)
			_hoops_PRRH (color);

		single = _hoops_HRSGR;
	};

	~_hoops_IRHA() {
		if (type == _hoops_SGSGR) {
			if (_hoops_ISAI ((Tristrip *)geo) == 0)
				HI_Free_Tristrip ((Tristrip *)geo);
		}
		else if (type == _hoops_GRSGR) {
			if (_hoops_ISAI ((Polyedge *)geo) == 0)
				HI_Free_Polyedge ((Polyedge *)geo);
		}
		else if (type == _hoops_HCAI) {
			if (_hoops_ISAI ((Polymarker *)geo) == 0)
				HI_Free_Polymarker ((Polymarker *)geo);
		}
		else if (type == _hoops_RRSGR)
			_hoops_HPRH ((Geometry*)geo);

		if (_hoops_CPAI)
			_hoops_HPRH (_hoops_CPAI);

		if (color)
			_hoops_HPRH (color);
	};

	Type						type;
	void *						geo;
	_hoops_ISGI const *	_hoops_CPAI;
	_hoops_SSGI const *				color;
	float						priority;
	Net_Rendition				nr;
	bool						single;
};



typedef VList<_hoops_IRHA *> _hoops_AIGI;

local RGB const *_hoops_RPCA (_hoops_APCA const *color, int mask);
#define _hoops_CCAI(_hoops_IASGR,bit) (_hoops_IASGR==null?null:(BIT(_hoops_IASGR->_hoops_GHA,bit)?_hoops_RPCA((_hoops_APCA const *)_hoops_IASGR->colors,bit):null))

#define _hoops_CASGR 0.5f
#define _hoops_SCCP(priority,displacement) (0.5f + 1e-6f*(((displacement)?_hoops_CASGR:0) - (float)(priority)))

struct H3D_Collector
{
	H3D_Collector *next;
	Net_Rendition		nr;
	_hoops_AIGI *_hoops_RCGI;
	_hoops_AIGI *_hoops_IIRI;
	_hoops_AIGI *_hoops_CIRI;
	_hoops_AIGI *_hoops_SIRI;
	_hoops_AIGI *_hoops_HRPI;			//_hoops_APGR, _hoops_GRRC _hoops_PPR _hoops_RRRC
	_hoops_AIGI *_hoops_IIII;			//_hoops_AAPI, _hoops_SRII, _hoops_CHPI
	_hoops_AIGI *_hoops_HHAI;
	_hoops_AIGI *_hoops_IHAI;
	Action_Mask mask, _hoops_RRSI, _hoops_PRGC;  /* _hoops_SASGR _hoops_SIH, _hoops_CAS 1==_hoops_GIR, 0==_hoops_HAR _hoops_GIR */
	bool _hoops_SIGI;
	bool _hoops_CPPGR;
	bool _hoops_IHGI;
};


/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_RR _hoops_ISHGR
*****************************************************************************
*****************************************************************************/
#define _hoops_CIGP					7				//_hoops_GPSGR _hoops_HH _hoops_HPI _hoops_IS _hoops_SGH
#define H3D_MAX_TEXTURES					8
#define H3D_MAX_SHADOW_MAPS					4
#define H3D_MAX_CUTTING_PLANES				15


typedef int _hoops_RPSGR;
#define _hoops_APSGR		((_hoops_RPSGR)0)
#define _hoops_PPSGR		((_hoops_RPSGR)1)
#define _hoops_HPSGR	((_hoops_RPSGR)2)
#define DCT_IMAGE			((_hoops_RPSGR)3)
#define _hoops_IPSGR	((_hoops_RPSGR)4)
#define _hoops_CPSGR		((_hoops_RPSGR)5)

/* _hoops_PGII _hoops_RH _hoops_HAGH _hoops_SPSGR _hoops_SGS _hoops_PAH _hoops_PHHR _hoops_CRGR _hoops_GHSGR _hoops_PSCH */
typedef enum _hoops_RHSGR {
    H3DBLEND_ZERO               = 1,
    H3DBLEND_ONE                = 2,
    H3DBLEND_SRCCOLOR           = 3,
    H3DBLEND_INVSRCCOLOR        = 4,
    H3DBLEND_SRCALPHA           = 5,
    H3DBLEND_INVSRCALPHA        = 6,
    H3DBLEND_DESTALPHA          = 7,
    H3DBLEND_INVDESTALPHA       = 8,
    H3DBLEND_DESTCOLOR          = 9,
    H3DBLEND_INVDESTCOLOR       = 10,
    H3DBLEND_SRCALPHASAT        = 11,
    H3DBLEND_BOTHSRCALPHA       = 12,
    H3DBLEND_BOTHINVSRCALPHA    = 13,
    H3DBLEND_BLENDFACTOR        = 14, /* _hoops_PGPR _hoops_APP _hoops_RPP _hoops_AHSGR _hoops_HRGR _hoops_GPP */
    H3DBLEND_INVBLENDFACTOR     = 15, /* _hoops_PGPR _hoops_APP _hoops_RPP _hoops_AHSGR _hoops_HRGR _hoops_GPP */
    H3DBLEND_FORCE_DWORD        = 0x7fffffff, /* _hoops_HHSA 32-_hoops_IGRH _hoops_IGIR _hoops_PHSGR */
} H3DBLEND;

typedef enum _hoops_HHSGR {
	H3DCLEAR_TARGET				= 1,
	H3DCLEAR_ZBUFFER			= 2,
	H3DCLEAR_STENCIL			= 3,
} H3DCLEAR;

typedef enum _hoops_IHSGR {
    H3DCMP_NEVER                = 1,
    H3DCMP_LESS                 = 2,
    H3DCMP_EQUAL                = 3,
    H3DCMP_LESSEQUAL            = 4,
    H3DCMP_GREATER              = 5,
    H3DCMP_NOTEQUAL             = 6,
    H3DCMP_GREATEREQUAL         = 7,
    H3DCMP_ALWAYS               = 8,
    H3DCMP_FORCE_DWORD          = 0x7fffffff, /* _hoops_HHSA 32-_hoops_IGRH _hoops_IGIR _hoops_PHSGR */
} H3DCMPFUNC;

typedef enum _hoops_CHSGR {
    H3DCULL_NONE                = 1,
    H3DCULL_CW                  = 2,
    H3DCULL_CCW                 = 3,
    H3DCULL_FORCE_DWORD         = 0x7fffffff, /* _hoops_HHSA 32-_hoops_IGRH _hoops_IGIR _hoops_PHSGR */
} H3DCULL;

typedef enum _hoops_SHSGR {
    H3DPT_POINTLIST             = 1,
    H3DPT_LINELIST              = 2,
    H3DPT_LINESTRIP             = 3,
    H3DPT_TRIANGLELIST          = 4,
    H3DPT_TRIANGLESTRIP         = 5,
    H3DPT_TRIANGLEFAN           = 6,
    H3DPT_FORCE_DWORD           = 0x7fffffff, /* _hoops_HHSA 32-_hoops_IGRH _hoops_IGIR _hoops_PHSGR */
} H3DPRIMITIVETYPE;

typedef enum _hoops_GISGR {
    H3DSHADE_FLAT               = 1,
    H3DSHADE_GOURAUD            = 2,
    H3DSHADE_PHONG              = 3,
    H3DSHADE_FORCE_DWORD        = 0x7fffffff, /* _hoops_HHSA 32-_hoops_IGRH _hoops_IGIR _hoops_PHSGR */
} H3DSHADEMODE;

typedef enum _hoops_RISGR {
    H3DSTENCILOP_KEEP           = 1,
    H3DSTENCILOP_ZERO           = 2,
    H3DSTENCILOP_REPLACE        = 3,
    H3DSTENCILOP_INCRSAT        = 4,
    H3DSTENCILOP_DECRSAT        = 5,
    H3DSTENCILOP_INVERT         = 6,
    H3DSTENCILOP_INCR           = 7,
    H3DSTENCILOP_DECR           = 8,
    H3DSTENCILOP_FORCE_DWORD    = 0x7fffffff, /* _hoops_HHSA 32-_hoops_IGRH _hoops_IGIR _hoops_PHSGR */
} H3DSTENCILOP;

typedef enum _hoops_AISGR {
    H3DTADDRESS_WRAP            = 1,
    H3DTADDRESS_MIRROR          = 2,
    H3DTADDRESS_CLAMP           = 3,
    H3DTADDRESS_BORDER          = 4,
    H3DTADDRESS_MIRRORONCE      = 5,
    H3DTADDRESS_FORCE_DWORD     = 0x7fffffff, /* _hoops_HHSA 32-_hoops_IGRH _hoops_IGIR _hoops_PHSGR */
} H3DTEXTUREADDRESS;

typedef enum _hoops_PISGR
{
    H3DTEXF_NONE				= 0,    // _hoops_RHRP _hoops_GRGR (_hoops_APIP _hoops_IH _hoops_HCRH _hoops_RGRR _hoops_RGAR)
    H3DTEXF_POINT				= 1,    // _hoops_HISGR
    H3DTEXF_LINEAR				= 2,    // _hoops_IISGR _hoops_GGAR
    H3DTEXF_ANISOTROPIC			= 3,    // _hoops_CISGR
    H3DTEXF_PYRAMIDALQUAD		= 6,    // 4-_hoops_ISAR _hoops_SISGR
    H3DTEXF_GAUSSIANQUAD		= 7,    // 4-_hoops_ISAR _hoops_GCSGR
    H3DTEXF_FORCE_DWORD			= 0x7fffffff,   // _hoops_HHSA 32-_hoops_IGRH _hoops_IGIR _hoops_PHSGR
} H3DTEXTUREFILTERTYPE;

typedef enum _hoops_RCSGR
{
    H3DFMT_UNKNOWN              =  0,

    H3DFMT_R8G8B8               = 20,
    H3DFMT_A8R8G8B8             = 21,
    H3DFMT_X8R8G8B8             = 22,
    H3DFMT_R5G6B5               = 23,
    H3DFMT_X1R5G5B5             = 24,
    H3DFMT_A1R5G5B5             = 25,
    H3DFMT_A4R4G4B4             = 26,
    H3DFMT_R3G3B2               = 27,
    H3DFMT_A8                   = 28,
    H3DFMT_A8R3G3B2             = 29,
    H3DFMT_X4R4G4B4             = 30,
    H3DFMT_A2B10G10R10          = 31,
    H3DFMT_A8B8G8R8             = 32,
    H3DFMT_X8B8G8R8             = 33,
    H3DFMT_G16R16               = 34,
    H3DFMT_A2R10G10B10          = 35,
    H3DFMT_A16B16G16R16         = 36,

    H3DFMT_A8P8                 = 40,
    H3DFMT_P8                   = 41,
    H3DFMT_L8                   = 50,
    H3DFMT_A8L8                 = 51,
    H3DFMT_A4L4                 = 52,

    H3DFMT_V8U8                 = 60,
    H3DFMT_L6V5U5               = 61,
    H3DFMT_X8L8V8U8             = 62,
    H3DFMT_Q8W8V8U8             = 63,
    H3DFMT_V16U16               = 64,
    H3DFMT_A2W10V10U10          = 67,

#ifndef _hoops_ACSGR
#define _hoops_ACSGR(_hoops_PCSGR, _hoops_HCSGR, _hoops_ICSGR, _hoops_CCSGR)                              \
		((unsigned long)(unsigned char)(_hoops_PCSGR) | ((unsigned long)(unsigned char)(_hoops_HCSGR) << 8) |       \
		((unsigned long)(unsigned char)(_hoops_ICSGR) << 16) | ((unsigned long)(unsigned char)(_hoops_CCSGR) << 24 ))
#endif /* _hoops_PAPR(_hoops_SCSGR) */
    H3DFMT_DXT1                 = _hoops_ACSGR('D', 'X', 'T', '1'),
    H3DFMT_DXT2                 = _hoops_ACSGR('D', 'X', 'T', '2'),
    H3DFMT_DXT3                 = _hoops_ACSGR('D', 'X', 'T', '3'),
    H3DFMT_DXT4                 = _hoops_ACSGR('D', 'X', 'T', '4'),
    H3DFMT_DXT5                 = _hoops_ACSGR('D', 'X', 'T', '5'),

    H3DFMT_D16_LOCKABLE         = 70,
    H3DFMT_D32                  = 71,
    H3DFMT_D15S1                = 73,
    H3DFMT_D24S8                = 75,
    H3DFMT_D24X8                = 77,
    H3DFMT_D24X4S4              = 79,
    H3DFMT_D16                  = 80,

    H3DFMT_D32F_LOCKABLE        = 82,
    H3DFMT_D24FS8               = 83,
    H3DFMT_L16                  = 81,

    H3DFMT_VERTEXDATA           =100,
    H3DFMT_INDEX16              =101,
    H3DFMT_INDEX32              =102,

    H3DFMT_Q16W16V16U16         =110,

    // _hoops_GSSGR _hoops_AGHS (16-_hoops_SIH _hoops_RIR _hoops_RCAP)
    H3DFMT_R16F                 = 111,
    H3DFMT_G16R16F              = 112,
    H3DFMT_A16B16G16R16F        = 113,

    // _hoops_RSSGR _hoops_ASSGR _hoops_AGHS (32-_hoops_SIH _hoops_RIR _hoops_RCAP)
    H3DFMT_R32F                 = 114,
    H3DFMT_G32R32F              = 115,
    H3DFMT_A32B32G32R32F        = 116,

    H3DFMT_CxV8U8               = 117,
    H3DFMT_FORCE_DWORD          =0x7fffffff
} H3DFORMAT;


//_hoops_PHCH _hoops_HII _hoops_AAPA _hoops_PAPA _hoops_CSPP _hoops_IIGR _hoops_CSCR _hoops_RPCC _hoops_PHSGR _hoops_IS _hoops_RH _hoops_CSCP _hoops_CSPP
local inline H3DFORMAT _hoops_RSRH(Image_Format fmt)
{
	switch (fmt) {
		case _hoops_AHGH: 
			return H3DFMT_L8;
		case _hoops_HHGH: 
			return H3DFMT_R8G8B8;
		default:
			return H3DFMT_A8R8G8B8;
	}
}


enum H3DFACE
{
   H3DFACE_POSITIVE_X 			= 0,
   H3DFACE_NEGATIVE_X 			= 1,
   H3DFACE_POSITIVE_Y 			= 2,
   H3DFACE_NEGATIVE_Y 			= 3,
   H3DFACE_POSITIVE_Z 			= 4,
   H3DFACE_NEGATIVE_Z 			= 5,

   H3DFACE_COUNT				= 6,
};

#define	H3DTEXUSAGE_DEFAULT			0x0000
#define	H3DTEXUSAGE_RENDERTARGET	0x0001
#define	H3DTEXUSAGE_DEPTHSTENCIL	0x0002
#define	H3DTEXUSAGE_AUTOGENMIPMAP	0x0004




/*
 * _hoops_PSSGR _hoops_IH _hoops_HSSGR
 */
#define H3DCLEAR_TARGET				0x0001  /* _hoops_CAAP _hoops_SAAP _hoops_ISSGR */
#define H3DCLEAR_ZBUFFER			0x0002  /* _hoops_CAAP _hoops_SAAP _hoops_SSH _hoops_SRHR */
#define H3DCLEAR_STENCIL			0x0004  /* _hoops_CAAP _hoops_APSP _hoops_GHC */

/*
 * _hoops_CSSGR _hoops_PISH _hoops_SIH
 */
enum
{
	// _hoops_ICAGR _hoops_IGRH _hoops_RIR _hoops_RCAP
	H3DMASK_R = (1<<0),
	H3DMASK_G = (1<<1),
	H3DMASK_B = (1<<2),
	H3DMASK_A = (1<<3),

	// _hoops_SSSGR _hoops_GGGRR
	H3DMASK_RGB = H3DMASK_R|H3DMASK_G|H3DMASK_B,
	H3DMASK_RGBA = H3DMASK_RGB|H3DMASK_A,
};


struct H3DViewport {
	unsigned long       X;
    unsigned long       Y;				/* _hoops_RGGRR _hoops_AGGRR _hoops_RAAP */
    unsigned long       Width;
    unsigned long       Height;			/* _hoops_RGGRR _hoops_PGGRR */
    float				MinZ;			/* _hoops_HGGRR/_hoops_AHPA _hoops_IIGR _hoops_HSPH _hoops_IGGRR */
    float				MaxZ;
};


typedef VHash<H3DVF, H3DVertexBufferCache *> H3DVF_2_H3DVertexBufferCache_Hash;

class H3DTexture;
typedef VHash<POINTER_SIZED_INT, H3DTexture *> H3DTexture_Hash;

struct _hoops_IARS
{
	unsigned Integer32 size;
	Integer32 glyph_key;
	H3DTexture *texture;
	_hoops_IARS *next;
};

class H3DGPUTimer;

enum _hoops_CGGRR
{
	_hoops_SGGRR,
	_hoops_GRGRR,
	_hoops_SRAP,
	_hoops_AHRS,
};

struct _hoops_RIPA
{
	_hoops_ARPA				plane;
	float					scale;
	float					bias;
};

#include "3d_common_shader.h"

/* _hoops_RCAR _hoops_IIGR _hoops_SISS _hoops_PIAP */
struct H3DCache
{
	H3DViewport _hoops_CSAA;
	void *_hoops_RRGRR;
	float _hoops_GSCH[2];
	bool _hoops_ARGRR;
	bool _hoops_PRGRR;
	bool _hoops_HRGRR;
	H3DCMPFUNC _hoops_RGIH;
	unsigned long _hoops_IGIH;
	unsigned long _hoops_PGIH;
	unsigned long _hoops_IRIH;
	H3DSTENCILOP _hoops_RRIH;
	H3DSTENCILOP _hoops_PRIH;
	H3DSTENCILOP _hoops_SGIH;
	bool _hoops_IRGRR;
	bool _hoops_HSAC;
	H3DBLEND _hoops_PHSS;
	H3DBLEND _hoops_IHSS;
	bool _hoops_RAIH;
	int _hoops_GRPP;
	bool _hoops_AAIH;
	bool _hoops_CRGRR;
	H3DRect _hoops_SRGRR;
	H3DCULL _hoops_HRSA;
	H3DShader *_hoops_AGSA;
	bool antialias;

	bool _hoops_GAGRR;

	int _hoops_RAGRR[_hoops_CIGP];
	int _hoops_AAGRR[_hoops_CIGP];
	int _hoops_PAGRR[_hoops_CIGP];
	int _hoops_HAGRR[_hoops_CIGP];
	int _hoops_IAGRR[_hoops_CIGP];
	int _hoops_CAGRR[_hoops_CIGP];
	H3DTexture *texture[_hoops_CIGP];

	int _hoops_GRIR;

	H3DSHADEMODE _hoops_SAGRR;
	H3DTexture *_hoops_PSAH;
	H3DTexture *_hoops_GPGRR[_hoops_CIGP];
	
	H3DVertexFormat	_hoops_PPCP;
};

struct H3DData {

	H3DRenderTarget			*render_target;			// _hoops_RPGRR _hoops_SRGS _hoops_HCSS
	H3DRenderTarget			*depth_stencil;

	// _hoops_APGRR _hoops_RAS _hoops_PPGRR _hoops_PRCR.
	bool _hoops_PR();

	// _hoops_APGRR _hoops_ARPP _hoops_PPGRR _hoops_HPGRR.
	void _hoops_PP();

	// _hoops_IGI _hoops_HPP _hoops_AIRI _hoops_HIGR _hoops_GGAS _hoops_IPGRR
	volatile int			H3D_DL_Delete_Task_count;
	_hoops_CPGRR					H3D_DL_Delete_Task_mutex;
	volatile bool			_hoops_SPGRR;

	bool				_hoops_GHGRR;	// _hoops_SISS _hoops_CARA _hoops_PIAP
	bool				_hoops_RHGRR;// _hoops_SISS _hoops_CARA _hoops_PIAP
	bool				_hoops_AHGRR;		// _hoops_PIAP _hoops_PSGR _hoops_IS _hoops_SRCH _hoops_GPGR _hoops_PHGRR _hoops_HCPH _hoops_ARPP _hoops_PCCP _hoops_HHGRR
	bool				_hoops_IGAGR;

	Image *_hoops_IHGRR;							// _hoops_APIP _hoops_CHGRR _hoops_SR'_hoops_ASAR _hoops_PCCP _hoops_CSCR _hoops_RHPP

	void * _hoops_GIPGR;
	void * _hoops_AIPGR;
	bool _hoops_RIPGR;

#ifndef NUTCRACKER
#ifdef WINDOWS_SYSTEM
	HWND hWND;
	HDC hDC;
	HDC _hoops_SHGRR;
	WNDPROC _hoops_GIGRR;
	HPALETTE _hoops_RIGRR, _hoops_AIGRR;
#endif
#endif
	_hoops_RPSGR _hoops_PIGRR;

	/*
	* _hoops_PGGRR
	*/
	H3DRect _hoops_HIGRR;
	H3DRect _hoops_IIGRR;
	Int_XY _hoops_CIGRR;
	Int_XY _hoops_SIGRR;
	Int_XY _hoops_GCGRR;

	int _hoops_RCGRR;
	int _hoops_ACGRR;
	int _hoops_PCGRR;
	int _hoops_HCGRR;

	bool _hoops_RSCH;
	int yfudge;
	float _hoops_ICGRR;
	int _hoops_CCGRR;
	int _hoops_SCGRR;
	int mouse_y;

	bool _hoops_GSGRR;
	bool _hoops_RSGRR;
	bool _hoops_ASGRR;

	int	_hoops_HSAA;		// _hoops_ICPP _hoops_CCPA, _hoops_GHAA _hoops_IS _hoops_ICIH.
	int	_hoops_ISAA;
	bool _hoops_IHP;			// _hoops_HCIC _hoops_PCCP _hoops_ICPP _hoops_PSGRR _hoops_ARP _hoops_IPIH?
	bool _hoops_AIP;

	_hoops_CGGRR _hoops_CRAP;			// _hoops_RPGRR _hoops_HSGRR _hoops_CCH.
	int _hoops_ISGRR;		// _hoops_GRSH _hoops_AHPH _hoops_IGPR (_hoops_RPP _hoops_ARHP _hoops_HRGR _hoops_PPP)
	int _hoops_CSGRR; // _hoops_GRSH _hoops_AHPH _hoops_IGPR _hoops_AAPR _hoops_SSGRR _hoops_IH?

	// _hoops_RAP _hoops_IS _hoops_CRHR _hoops_RH _hoops_RHPP _hoops_GGRRR _hoops_CGPR _hoops_IRS _hoops_RGRRR _hoops_CAIH _hoops_HRGR _hoops_AGRRR _hoops_HPP _hoops_RH _hoops_PCCS _hoops_PGRRR.
	int	_hoops_HGRRR;

	// _hoops_RAP _hoops_HPP _hoops_RH _hoops_RHPP _hoops_IS _hoops_IRHC _hoops_IRS _hoops_PCCS _hoops_PGRRR _hoops_CSAP _hoops_IGRRR _hoops_RHSP _hoops_IRS _hoops_RGRRR _hoops_CAIH (_hoops_CACH _hoops_ARRS).
	bool _hoops_CGRRR;

	int _hoops_PHAI;

	H3DCache *_hoops_CSC;

	struct {
		int _hoops_IPA;
		int _hoops_CRA;
		int flags;
		H3DShaderID id;
	} _hoops_HPA;

	_hoops_SGRRR *_hoops_GRRRR;

#define	_hoops_RRRRR		 0x01
#define	_hoops_ARRRR		 0x02
#define	_hoops_PRRRR	 0x04
	int _hoops_HRRRR;
	bool _hoops_IRRRR;
	bool pending_resize;

	char *_hoops_CRRRR;
	bool _hoops_SRRRR;
	Display_Context const *dc;

#define _hoops_CCC				(_hoops_GARRR) -1
#define _hoops_RARRR(_hoops_AARRR)					(-(_hoops_AARRR))
#define _hoops_PARRR(_hoops_AARRR)					(_hoops_AARRR)
	_hoops_GARRR _hoops_HCAC;
	_hoops_GARRR _hoops_ACHH;
	_hoops_GARRR _hoops_ASIH;
	int			   _hoops_HARRR;
	_hoops_GARRR _hoops_RPCI;
	_hoops_GARRR _hoops_IARRR;
	_hoops_GARRR _hoops_CARRR;
	_hoops_GARRR _hoops_ICAC;
	_hoops_GARRR _hoops_SARRR;
	_hoops_GARRR _hoops_GPRRR;
	_hoops_GARRR _hoops_RSHH;

	/*
	* _hoops_HRCS _hoops_IRCS _hoops_RPRRR
	*/
#define _hoops_APRRR 16
	struct {
		bool					_hoops_HRI;
		bool					mode;
		bool					_hoops_PPSP; /* _hoops_HRGR _hoops_SRGS _hoops_IS _hoops_APSP _hoops_RRGI _hoops_PPRRR */
		int						flags;
		H3DTexture				*_hoops_HPRRR;
		int						w, h;
		H3DFORMAT				_hoops_GCH;
		bool					_hoops_ACH;
		H3DTexture				*_hoops_IPRRR[_hoops_APRRR];
		H3DTexture				*_hoops_CPRRR[_hoops_APRRR];
		H3D_SURFACE_ID			msaa_target;
	} _hoops_RHH;

	struct {
		bool _hoops_PRI;
		bool mode;
		int	 _hoops_SGAP;

		// _hoops_HSRR _hoops_HCH _hoops_SPRRR _hoops_RGAR.
		H3DTexture *depth_measure_pattern;
		H3D_SURFACE_ID depth_measure_target;

		// _hoops_HSRR _hoops_GGGP
		H3DTexture *_hoops_HI;
		int _hoops_AIGP;
		H3DGPUTimer *_hoops_CRPP;

		// _hoops_HSRR _hoops_HCR _hoops_AGI.
		H3DTexture *depth_texture;

		// _hoops_HSRR _hoops_HCH _hoops_IIGR _hoops_PAIP, _hoops_SR _hoops_RRP _hoops_IS _hoops_PGHA _hoops_RH _hoops_HPHR-_hoops_GSSP _hoops_HHAP _hoops_HIS _hoops_SR _hoops_RRP _hoops_RH _hoops_SARA
		_hoops_HHRA const *_hoops_SPH;

		float _hoops_CCCS, _hoops_ICCS;
	} _hoops_II;

	// _hoops_GHRRR _hoops_RRRH
	struct
	{
		H3DTexture *_hoops_RHRRR;
		H3DTexture *_hoops_AHRRR;

		float _hoops_PHRRR[16];

	} _hoops_HHRRR;

	struct {
		bool					mode;
		bool					_hoops_SAR;
		Integer32				_hoops_PCIH;
		Integer32				_hoops_HAP;
		Integer32				_hoops_PPCS;
		Integer32				_hoops_CAP;

		H3DRenderTarget			*depth_buffer;		// _hoops_HCH _hoops_SRHR _hoops_IH _hoops_RH _hoops_RCAR _hoops_ARCR
		H3DRenderTarget			*dummy_buffer;		// _hoops_HAIR _hoops_SRHR (_hoops_HAR _hoops_IGI)

		H3D_Display_List		*_hoops_HSCS;
		H3DTexture				*_hoops_HI;		// _hoops_CAIC-_hoops_AIR _hoops_RI _hoops_GGR _hoops_HHH _hoops_SRSGR.
	} _hoops_PI;

	struct {
		bool					mode;
		Integer32			_hoops_HAP;

	} _hoops_CHSP;

	struct {
		bool					mode;
		Integer32				_hoops_HAP;

	} glyph;

	struct {
		bool					mode;
		Integer32			_hoops_HAP;
		H3DTexture				*_hoops_GI;
		_hoops_RIPA _hoops_AIPA;

	} _hoops_SH;

	/*
	* _hoops_IHRRR _hoops_PPR _hoops_III _hoops_PAIA
	*/
#define _hoops_CRPH		(FP_WINDOW_TRANSPARENT + 1)
    H3DTexture			*_hoops_SRPH[128];
	int					_hoops_IRPH;

	H3DTexture			*_hoops_ISAH;
	_hoops_PCS		*_hoops_GCCP;
	int					_hoops_GGPH;

#define H3D_LARGEST_PRECOMPUTED_CIRCLE  20
#define H3D_LINE_TOOLS_SIZE				256
	struct {
		bool					valid;
		int						data_size;
		unsigned char			*data;
		H3DTexture				*texture;
		float					_hoops_ACAA[H3D_LARGEST_PRECOMPUTED_CIRCLE+1];
	} _hoops_HSI;

	struct {
		bool					valid;
		H3DTexture				*_hoops_CHRRR;
	} glyphs;

	// _hoops_AGCR _hoops_HCIA _hoops_IHAH _hoops_SHRRR _hoops_ACPP, _hoops_HIH _hoops_HS _hoops_PSP _hoops_GIRRR _hoops_GPP _hoops_GCAC
	// _hoops_CCGR _hoops_SSIA _hoops_CHR _hoops_RIRRR _hoops_CRGR _hoops_RH _hoops_AIRRR' _hoops_SRSR _hoops_PIRRR
	float _hoops_PIGA[16];
	float _hoops_IACR[16];
	float _hoops_ISGA[16];
	float _hoops_PARA[16];
	float _hoops_SPSR[16];
	bool _hoops_RRRA[H3D_MAX_TEXTURES];
	float _hoops_PRRA[H3D_MAX_TEXTURES][16];
	float _hoops_SHIH;
	float _hoops_IIGA;
	float _hoops_HARA;
	bool _hoops_IICH;
	float _hoops_PGGH[16];
	float _hoops_HGGH[16];
	float _hoops_GCRA;
	float _hoops_SIRA;

	H3DShaderHASH				*_hoops_IP;
	H3DVF_2_H3DVertexBufferCache_Hash *	_hoops_HIRRR;
	H3DTexture_Hash *			_hoops_ACAH;
	H3DTexture_Hash *			_hoops_RCAH;
	_hoops_IARS *				glyph_textures;
	H3DIndexBufferCache			*_hoops_ACHC;
	H3DVertexBuffer				_hoops_CP;				//_hoops_IH _hoops_IIRRR _hoops_SGH
	H3DVertexBuffer				_hoops_CIRRR;		//_hoops_IH _hoops_SGH _hoops_CCA _hoops_RH _hoops_SIRRR[]

	char						*_hoops_CA;
	char						*_hoops_GP;

#define _hoops_GCRRR(h3ddata) _hoops_GHIA( \
	if (h3ddata->_hoops_ICPS) \
		FREE_ARRAY(h3ddata->_hoops_ICPS, h3ddata->_hoops_SCPS, float); \
	h3ddata->_hoops_SCPS = 0; \
	h3ddata->_hoops_ICPS = null; \
) \

#define _hoops_RCRRR(h3ddata) _hoops_GHIA( \
	if (h3ddata->_hoops_CCPS) \
		FREE_ARRAY(h3ddata->_hoops_CCPS, h3ddata->_hoops_GSPS, short); \
	h3ddata->_hoops_GSPS = 0; \
	h3ddata->_hoops_CCPS = null; \
) \

#define _hoops_ACRRR(h3ddata, _hoops_PCRRR, size) _hoops_GHIA( \
	 if (size > h3ddata->_hoops_SCPS) { \
		if (h3ddata->_hoops_ICPS) \
			FREE_ARRAY(h3ddata->_hoops_ICPS, h3ddata->_hoops_SCPS, float); \
		h3ddata->_hoops_SCPS = size; \
		ALLOC_ARRAY_CACHED(h3ddata->_hoops_ICPS, h3ddata->_hoops_SCPS, float); \
	} \
	_hoops_PCRRR = h3ddata->_hoops_ICPS; \
)

#define _hoops_HCRRR(h3ddata, _hoops_ICRRR, size) _hoops_GHIA( \
	if (size > h3ddata->_hoops_GSPS) { \
		if (h3ddata->_hoops_CCPS) \
			FREE_ARRAY(h3ddata->_hoops_CCPS, h3ddata->_hoops_GSPS, short); \
		h3ddata->_hoops_GSPS = size; \
		ALLOC_ARRAY_CACHED(h3ddata->_hoops_CCPS, h3ddata->_hoops_GSPS, short); \
	} \
	_hoops_ICRRR = h3ddata->_hoops_CCPS; \
)

	float						*_hoops_ICPS;
	int							_hoops_SCPS;

	short						*_hoops_CCPS;
	int							_hoops_GSPS;

	float						_hoops_CCRRR[_hoops_SSC][16];
	bool						_hoops_SCRRR[_hoops_SSC];

	H3D_Display_List			*_hoops_AAI;

	/*
	* _hoops_GSRRR-_hoops_PAPA _hoops_AIRI _hoops_CPCI
	*/
	Integer32					_hoops_ISCI;
	Integer32					_hoops_GGHGR;
	H3D_Collector *				_hoops_CIGI;
	H3D_Collector *				_hoops_SSPGR;
	unsigned Integer32			_hoops_RGHGR;
	bool						_hoops_SGSP;
	int							_hoops_RSRRR;
	_hoops_ISSH	*					_hoops_CSSH;

	bool						_hoops_ASRRR;
	bool						_hoops_GSA;

	bool						_hoops_IASA;
	bool						_hoops_SCSP;

	short						*_hoops_PSRRR;
	int							_hoops_HSRRR;

	int							*_hoops_ISRRR;
	int							_hoops_CSRRR;

#define _hoops_SSRRR(h3ddata, size) _hoops_GHIA(\
	if (h3ddata->_hoops_GGARR == null || h3ddata->_hoops_RGARR < size) { \
		if (h3ddata->_hoops_GGARR) {\
			FREE_ARRAY(h3ddata->_hoops_GGARR, h3ddata->_hoops_RGARR, _hoops_ARPA); \
			FREE_ARRAY(h3ddata->_hoops_AGARR, h3ddata->_hoops_RGARR, Vector); \
		}\
		h3ddata->_hoops_RGARR = size; \
		ALLOC_ARRAY(h3ddata->_hoops_GGARR, h3ddata->_hoops_RGARR, _hoops_ARPA); \
		ALLOC_ARRAY(h3ddata->_hoops_AGARR, h3ddata->_hoops_RGARR, Vector); \
	} \
)
	Vector						*_hoops_AGARR;
	_hoops_ARPA						*_hoops_GGARR;
	int							_hoops_RGARR;

	int							_hoops_HIHS;
	Test *						_hoops_IIHS;

	char						shader_handle[4096];			//_hoops_SI _hoops_GC _hoops_IH _hoops_CI _hoops_SIHR

	bool						_hoops_APH;
	bool						_hoops_AHPI;
	bool						_hoops_AIC;
	bool						_hoops_PGARR;

	int							_hoops_GAH;
	bool						_hoops_HGARR;
	int							_hoops_IGARR;
	unsigned long				_hoops_CGARR;

	bool						_hoops_SGARR;

	bool						_hoops_GRARR;
	int							_hoops_RRARR;		//_hoops_IGI _hoops_IH _hoops_GPIC _hoops_IGSGR _hoops_SARR / _hoops_PSP _hoops_GGAR (_hoops_AHHS _hoops_RAIA _hoops_SRS _hoops_GPHA _hoops_IIGR _hoops_IRS _hoops_SCPH, _hoops_ICCI _hoops_RAIA _hoops_CGHI)

	bool 						_hoops_SRP;		//_hoops_GSIA _hoops_RCAR _hoops_ACAR
	bool 						_hoops_GAP;		//32-_hoops_IGRH _hoops_SAPS _hoops_PPSR _hoops_AI
	int		 					_hoops_GRAP;				//_hoops_GPGR _hoops_SRGS _hoops_SAAP _hoops_RPR
	float						_hoops_IHSC;	// _hoops_GRSH _hoops_AHSC _hoops_PAH _hoops_RH _hoops_GSIA _hoops_PGSA _hoops_PPSR _hoops_IPSC?
	_hoops_ARARR *				_hoops_PRARR;			//_hoops_HRARR _hoops_CIPH
	int							_hoops_IRARR;
	bool						_hoops_RP;

	// _hoops_IPSP _hoops_AIRRR
	POINTER_SIZED_INT			_hoops_CRARR;
	POINTER_SIZED_INT			_hoops_SRARR;
	POINTER_SIZED_INT			_hoops_GAARR;
	POINTER_SIZED_INT			_hoops_RAARR;

	// _hoops_SAH _hoops_HHH _hoops_PHIGR _hoops_AAARR _hoops_ARI
	struct {
		unsigned int			_hoops_CGGI;
		unsigned int			_hoops_GRGI;
		unsigned int			_hoops_PCGH;
		unsigned int			_hoops_HCGH;
		_hoops_IRRR				_hoops_PAARR;
		bool					_hoops_SPRH;				// _hoops_IHPR _hoops_RPP _hoops_HH _hoops_HAARR _hoops_PIHA _hoops_SHH _hoops_IAARR _hoops_IIGR 2
	} _hoops_ACGH;

	bool						_hoops_HRRH;
	bool						_hoops_CAARR;
	bool						_hoops_SAARR;
	bool						_hoops_CHGH;
	bool						_hoops_GPARR;

	bool						_hoops_PIRH;
	bool						_hoops_RPARR;
	bool						_hoops_GCSC;

	int							_hoops_HSRH;
	H3D_Color_Format			_hoops_SHAP;
	H3D_Driver_Shader_Type		_hoops_CSS;
	int							_hoops_ACCR;

	H3DActions					*_hoops_GSCR;
	_hoops_APARR				_hoops_RRCI;

	H3DPost						*post;

}; //_hoops_RSGR _hoops_PPARR _hoops_RR

/*
 * _hoops_HPARR _hoops_IPARR _hoops_CPARR _hoops_SPARR
 */
#ifdef DX9_DRIVER
//_hoops_AHPA _hoops_IH _hoops_AAGC _hoops_IPSH _hoops_GHARR _hoops_PPGS _hoops_ARPP _hoops_SR _hoops_RRS _hoops_HHPS _hoops_AIRI _hoops_CPCI
#  define _hoops_RHARR ((size_t)1000*1000*1000)

#  ifdef _WIN64
#    define _hoops_HCRI(h3ddata, _hoops_AHARR) \
	  (HOOPS_WORLD->display_list_vram_usage + HOOPS_WORLD->_hoops_SARH + (size_t)(_hoops_AHARR) < HOOPS_WORLD->_hoops_PHARR)
#  else
#    define _hoops_HCRI(h3ddata, _hoops_AHARR) \
	  (HOOPS_WORLD->display_list_vram_usage + HOOPS_WORLD->_hoops_SARH + (size_t)(_hoops_AHARR) < HOOPS_WORLD->_hoops_PHARR && \
	   HOOPS_WORLD->display_list_vram_usage + HI_Memory_On_Pool(HOOPS_WORLD->memory_pool) < _hoops_RHARR)
#  endif

#else

#  define _hoops_HCRI(h3ddata, _hoops_HHARR) \
	(HOOPS_WORLD->display_list_vram_usage + HOOPS_WORLD->_hoops_SARH + (size_t)(_hoops_HHARR) < HOOPS_WORLD->_hoops_PHARR)

#endif


void _hoops_IHARR( Display_Context alter *dc );

class _hoops_CHARR
{
public:
	_hoops_CHARR( Display_Context alter *dc ) : _hoops_SHARR(dc)
	{
		H3DData *h3ddata = H3DD(dc);

		// _hoops_RSSS _hoops_GIARR _hoops_PCCS _hoops_GGSC
		++h3ddata->_hoops_HGRRR;
	}

	~_hoops_CHARR()
	{
		H3DData *h3ddata = H3DD(_hoops_SHARR);

		// _hoops_RCPA _hoops_RIARR _hoops_SR _hoops_PIHA _hoops_SRS _hoops_HS _hoops_AIARR!
		ASSERT(h3ddata->_hoops_HGRRR > 0);

		// _hoops_PIARR _hoops_GGSR?
		if ( --h3ddata->_hoops_HGRRR == 0 )
		{
			// _hoops_CGP _hoops_SR _hoops_IGRRR _hoops_IRS _hoops_PCCS, _hoops_RGHH _hoops_SCH _hoops_HA
			if ( h3ddata->pending_resize )
			{
				_hoops_IHARR(_hoops_SHARR);
				h3ddata->pending_resize = false;
			}
		}
	}

private:
	Display_Context alter *_hoops_SHARR;
};

#define H3D_LONG_OPERATION(dc) _hoops_CHARR _hoops_HIARR(dc)





// _hoops_HPARR _hoops_IPARR _hoops_IIARR _hoops_CIARR
bool _hoops_ARAGR(H3DData alter *h3ddata, int _hoops_SHGGR);

void _hoops_SPSI(_hoops_AGCI *_hoops_AGAGR);

void _hoops_SSRGR(Display_Context const *dc);

void _hoops_ASCI(H3DData alter *h3ddata);

void _hoops_SIARR(H3DData alter *h3ddata);

#include "task_queue.h"
class H3D_DL_Delete_Task : public _hoops_GCARR {

public:

	H3D_DL_Delete_Task(Display_Context const * dc, _hoops_AGCI * _hoops_RGAGR) {

		h3ddata = H3DD (dc);
		_hoops_CAAI (h3ddata->H3D_DL_Delete_Task_mutex);
		h3ddata->H3D_DL_Delete_Task_count++;
		_hoops_APAI (h3ddata->H3D_DL_Delete_Task_mutex);

		_hoops_RCARR = _hoops_RGAGR;

		if (dc->_hoops_GHRI->_hoops_ACARR)
			dc->_hoops_GHRI->_hoops_ACARR->_hoops_PCARR(this);
		else
			_hoops_HCARR (false);
	};

	virtual ~H3D_DL_Delete_Task() {

		_hoops_CAAI (h3ddata->H3D_DL_Delete_Task_mutex);
		h3ddata->H3D_DL_Delete_Task_count--;
		if (h3ddata->_hoops_SPGRR &&
			h3ddata->H3D_DL_Delete_Task_count == 0) {
			_hoops_SIARR(h3ddata);
		}
		else
			_hoops_APAI (h3ddata->H3D_DL_Delete_Task_mutex);

	};

	virtual _hoops_ICARR Type() {return _hoops_CCARR;}

	virtual void _hoops_HCARR(bool _hoops_SCARR) {

		UNREFERENCED(_hoops_SCARR);

		_hoops_AGCI * _hoops_AGAGR=null;

		while ((_hoops_AGAGR = _hoops_RCARR) != null) {
			_hoops_RCARR = _hoops_AGAGR->next;
			_hoops_SPSI (_hoops_AGAGR);
		}

		delete this;
	};

private:
	_hoops_AGCI * _hoops_RCARR;

	H3DData alter *h3ddata;

};


#define H3D_DL_DELETE_TASK

#ifndef DX9_DRIVER
#undef H3D_DL_DELETE_TASK
#endif


/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_GSARR _hoops_ISHGR

_hoops_HGI _hoops_CSHGR _hoops_HRGR _hoops_IRS _hoops_PIPS _hoops_AARI _hoops_IRS _hoops_RHPP _hoops_SASI _hoops_HH _hoops_RCC.
*****************************************************************************
*****************************************************************************/
#define _hoops_RSARR						(-1)
#define _hoops_CRAGR					(H3DTexture*)(-1)
#define _hoops_HAAGR				(void*)(-1)

#define _hoops_ASARR(h3ddata) _hoops_GHIA(\
	{ \
		int _hoops_PSARR; \
		for (_hoops_PSARR = 0; _hoops_PSARR < _hoops_CIGP; ++_hoops_PSARR) { \
			(h3ddata)->_hoops_CSC->_hoops_RAGRR[_hoops_PSARR] = _hoops_RSARR; \
			(h3ddata)->_hoops_CSC->_hoops_AAGRR[_hoops_PSARR] = _hoops_RSARR; \
			(h3ddata)->_hoops_CSC->_hoops_PAGRR[_hoops_PSARR] = _hoops_RSARR; \
			(h3ddata)->_hoops_CSC->_hoops_HAGRR[_hoops_PSARR] = _hoops_RSARR; \
			(h3ddata)->_hoops_CSC->_hoops_IAGRR[_hoops_PSARR] = _hoops_RSARR; \
		} \
	} \
)

class H3DRenderTarget : public CMO
{
public:
	H3DData *_hoops_ISS;
	int _hoops_IRRP;
	int _hoops_CRRP;
	int _hoops_HSARR;
	H3DFORMAT _hoops_GSPP;

public:
	H3DRenderTarget(H3DData *h3ddata,
		unsigned int width,
		unsigned int height,
		unsigned int _hoops_GCI,
		H3DFORMAT format,
		unsigned int _hoops_ISARR)
	{
		UNREFERENCED(_hoops_GCI);
		_hoops_ISS = h3ddata;
		_hoops_IRRP = width;
		_hoops_CRRP = height;
		_hoops_GSPP = format;
		_hoops_HSARR = _hoops_ISARR;
	};
	virtual ~H3DRenderTarget(){};

	virtual bool _hoops_CSARR() {return false;}
	int Width() const { return _hoops_IRRP; }
	int Height() const { return _hoops_CRRP; }
};

void _hoops_GHGH(H3DData *h3ddata, _hoops_RCR const *txr, unsigned char *_hoops_SISA, int pitch);
class H3DTexture : public H3DRenderTarget
{
public:
	int _hoops_SSARR;
	H3DTEXTUREFILTERTYPE _hoops_GGPRR;
	H3DTEXTUREFILTERTYPE _hoops_RGPRR;
	H3DTEXTUREFILTERTYPE _hoops_AGPRR;
	H3DTEXTUREADDRESS _hoops_PGPRR;
	H3DTEXTUREADDRESS _hoops_HGPRR;

	H3DTexture **_hoops_IGPRR;

public:
	H3DTexture(H3DData *h3ddata,
		unsigned int width,
		unsigned int height,
		unsigned int _hoops_ICRH,
		unsigned int _hoops_GCI,
		H3DFORMAT format) :
		H3DRenderTarget(h3ddata, width, height, _hoops_GCI, format, 0)
	{
		_hoops_IGPRR = null;
		UNREFERENCED(_hoops_ICRH);
	};
	virtual ~H3DTexture()
	{
		if (_hoops_IGPRR)
			*_hoops_IGPRR = null;
		_hoops_IGPRR = null;
	};
	virtual bool Lock(int _hoops_SHGGR, unsigned char ** data){
		UNREFERENCED(_hoops_SHGGR);
		UNREFERENCED(data);
		return false;
	};
	virtual bool Lock(H3DRect *_hoops_CGPRR, unsigned char ** data, int *pitch = null) = 0;
	virtual void Unlock() = 0;
	virtual void _hoops_APRH() = 0;
	virtual bool _hoops_CSARR() {return true;}
	virtual bool _hoops_SGPRR() {return false;}
	virtual bool _hoops_GRPRR() {return false;}
	int _hoops_AAAH() const {return _hoops_SSARR;}

	virtual bool _hoops_CAAH(_hoops_RCR *txr) {
		UNREFERENCED(txr);
		return false;
	}
	virtual bool _hoops_SAAH(_hoops_RCR *txr) {
		UNREFERENCED(txr);
		return false;
	}
};


class H3DCubeTexture : public H3DTexture
{
public:
	H3DCubeTexture(H3DData *h3ddata,
		unsigned int size,
		unsigned int _hoops_ICRH,
		unsigned int _hoops_GCI,
		H3DFORMAT format) :
		H3DTexture(h3ddata, size, size, _hoops_ICRH, _hoops_GCI, format)
	{
	};
	virtual ~H3DCubeTexture(){};
	virtual bool Lock(H3DFACE face, H3DRect *_hoops_CGPRR, unsigned char ** data, int *pitch = null) = 0;
	virtual void Unlock(H3DFACE face) = 0;
	virtual bool _hoops_SGPRR() {return true;}
	virtual bool _hoops_GRPRR() {return false;}

	// _hoops_RRPRR _hoops_GSSR _hoops_SGHS _hoops_IS _hoops_SRS _hoops_HSP (_hoops_PAR _hoops_SR _hoops_HHS _hoops_SSPC _hoops_CAPR?)
	virtual bool Lock(H3DRect *_hoops_CGPRR, unsigned char **data, int *pitch = null)
		{
		return Lock(H3DFACE_POSITIVE_X, _hoops_CGPRR, data, pitch);
	}
	virtual void Unlock()
	{
		Unlock(H3DFACE_POSITIVE_X);
	}
};


class H3DTexture3D : public H3DTexture
{
protected:
	unsigned int m_depth;

public:
	H3DTexture3D(H3DData *h3ddata,
		unsigned int w,
		unsigned int h,
		unsigned int depth,
		unsigned int _hoops_ICRH,
		unsigned int _hoops_GCI,
		H3DFORMAT format) :
		H3DTexture(h3ddata, w, h, _hoops_ICRH, _hoops_GCI, format)
	{
		m_depth = depth;
	};
	virtual ~H3DTexture3D(){};
	virtual bool Lock(unsigned char **data, int *_hoops_SRAH, int *_hoops_GAAH) = 0;
	virtual void Unlock() = 0;
	virtual bool _hoops_SGPRR() {return false;}
	virtual bool _hoops_GRPRR() {return true;}
	int _hoops_RAAH() const {return m_depth;}

	//_hoops_SR _hoops_CGH _hoops_IIP _hoops_SHH _hoops_ARPRR _hoops_IS _hoops_AAHS _hoops_IRS _hoops_PRPRR _hoops_IIGR _hoops_IRS 3d _hoops_HH
	virtual bool Lock(H3DRect *_hoops_CGPRR, unsigned char **data, int *pitch = null) {
		UNREFERENCED (_hoops_CGPRR);
		UNREFERENCED (data);
		UNREFERENCED (pitch);
		ASSERT (0);
		return false;
	}

};


/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_HRPRR _hoops_CIGR
*****************************************************************************
*****************************************************************************/
#define _hoops_GHIH	16384

#define _hoops_RPIH(h3ddata, _hoops_PPCP, _hoops_IRPRR) _hoops_GHIA( \
	if (!h3ddata->_hoops_HIRRR)					\
		h3ddata->_hoops_HIRRR = POOL_NEW(HOOPS_WORLD->memory_pool, H3DVF_2_H3DVertexBufferCache_Hash)(HOOPS_WORLD->memory_pool);	\
	H3DVertexBufferCache *_hoops_CRPRR; \
	if (h3ddata->_hoops_HIRRR->LookupItem(_hoops_PPCP._hoops_HPCP(), &_hoops_CRPRR) != VHASH_STATUS_SUCCESS) {	\
		_hoops_CRPRR = h3ddata->_hoops_GSCR->_hoops_HAIH(); \
		_hoops_CRPRR->CreateVertexBuffer(h3ddata, _hoops_GHIH, _hoops_PPCP); \
		h3ddata->_hoops_HIRRR->InsertItem(_hoops_PPCP._hoops_HPCP(), _hoops_CRPRR); \
	} \
	_hoops_IRPRR = _hoops_CRPRR; \
)


#define _hoops_RCHC(h3ddata, _hoops_HACP) _hoops_GHIA(\
	if (h3ddata->_hoops_ACHC == null) { \
		h3ddata->_hoops_ACHC = h3ddata->_hoops_GSCR->_hoops_SRPRR(); \
		h3ddata->_hoops_ACHC->CreateIndexBuffer(h3ddata); \
	} \
	h3ddata->_hoops_ACHC->_hoops_GAPRR(_hoops_HACP); \
)

#define _hoops_PHSA(h3ddata,nr,type,_hoops_RSR) _hoops_RSR->_hoops_RCHR(nr, type, true)

#define _hoops_AHSA(h3ddata,nr,type,_hoops_RSR) _hoops_RSR->_hoops_RCHR(nr, type, false)

#define _hoops_GHHC(dx9data,nr,_hoops_GHP,_hoops_RSR) _hoops_RSR->_hoops_SIAA(nr,_hoops_GHP)

#define _hoops_GIAC(h3ddata,nr,_hoops_RSR) _hoops_GHIA( \
	if (h3ddata->_hoops_HCAC != nr->transform_rendition->_hoops_CPA || \
		h3ddata->_hoops_HARRR == 0) { \
			_hoops_SAHH (nr); \
			h3ddata->_hoops_HCAC = nr->transform_rendition->_hoops_CPA; \
			h3ddata->_hoops_HARRR = 1; \
	} \
	_hoops_RSR->_hoops_RIGA(nr); \
	if (h3ddata->_hoops_RHH.mode) { \
		_hoops_RSR->_hoops_RAPRR (h3ddata->_hoops_RHH._hoops_HPRRR, h3ddata); \
	} \
)

/*
 * _hoops_AAPRR
 * _hoops_PAPRR _hoops_HAPRR _hoops_HCIA.  _hoops_HAIA _hoops_PIAP _hoops_IAGA _hoops_GPP _hoops_RH _hoops_SISS (_hoops_IAS._hoops_ISHI.
 * _hoops_IAPRR _hoops_CAPRR, _hoops_ICIH).  _hoops_SAPRR _hoops_PIAP _hoops_IAGA _hoops_GGR _hoops_RH _hoops_AIRRR' _hoops_SRSR _hoops_PIRRR
 */
#define _hoops_GGGH(h3ddata,nr,_hoops_RSR) _hoops_GHIA(\
	if (h3ddata->_hoops_HCAC != nr->transform_rendition->_hoops_CPA || \
		h3ddata->_hoops_HARRR == 1) { \
		_hoops_GIIH (nr); \
		h3ddata->_hoops_HCAC = nr->transform_rendition->_hoops_CPA; \
		h3ddata->_hoops_HARRR = 0; \
	} \
	_hoops_RSR->_hoops_IGRA(nr); \
	if (h3ddata->_hoops_RHH.mode) { \
		_hoops_RSR->_hoops_RAPRR (h3ddata->_hoops_RHH._hoops_HPRRR, h3ddata); \
	} \
)



/*
 * _hoops_GPPRR
 */
#define _hoops_RPPRR(h3ddata) _hoops_GHIA(\
	ZERO_STRUCT (&h3ddata->_hoops_CSC->_hoops_CSAA, H3DViewport); \
	h3ddata->_hoops_HCAC = _hoops_CCC; \
)
#define _hoops_HHRS(h3ddata, left, top, width, height) _hoops_GHIA(\
	H3DViewport *_hoops_APPRR = &h3ddata->_hoops_CSC->_hoops_CSAA; \
	ASSERT((int)(left) >= 0 && (int)(top) >= 0); \
	_hoops_APPRR->X = (left); \
	_hoops_APPRR->Y = (top); \
	_hoops_APPRR->Width = (width);	 \
	_hoops_APPRR->Height = (height); 	\
	_hoops_APPRR->MinZ = h3ddata->_hoops_CSC->_hoops_GSCH[0]; \
	_hoops_APPRR->MaxZ = h3ddata->_hoops_CSC->_hoops_GSCH[1]; \
	h3ddata->_hoops_GSCR->SetViewport(_hoops_APPRR); \
)
#define _hoops_PPHH(h3ddata, left, top, width, height) _hoops_GHIA(\
	if ((unsigned int)left != h3ddata->_hoops_CSC->_hoops_CSAA.X || (unsigned int)top != h3ddata->_hoops_CSC->_hoops_CSAA.Y || \
		(unsigned int)width != h3ddata->_hoops_CSC->_hoops_CSAA.Width || (unsigned int)height != h3ddata->_hoops_CSC->_hoops_CSAA.Height || \
		h3ddata->_hoops_CSC->_hoops_GSCH[0] != h3ddata->_hoops_CSC->_hoops_CSAA.MinZ || \
		h3ddata->_hoops_CSC->_hoops_GSCH[1] != h3ddata->_hoops_CSC->_hoops_CSAA.MaxZ \
		) {	\
		_hoops_HHRS(h3ddata, (left), (top), (width), (height)); \
	} \
)



#define _hoops_PPPRR(h3ddata,_hoops_HPPRR) h3ddata->_hoops_GSCR->_hoops_IPPRR(_hoops_HPPRR);
#define _hoops_GCHC(h3ddata,_hoops_HPPRR)  _hoops_GHIA( \
	if (h3ddata->_hoops_CSC->_hoops_PPCP != _hoops_HPPRR) \
		_hoops_PPPRR(h3ddata,_hoops_HPPRR); \
)


#define _hoops_CPPRR(h3ddata, _hoops_HAGR) (h3ddata)->_hoops_GSCR->_hoops_SPPRR(_hoops_HAGR);
#define _hoops_IPGP(h3ddata, _hoops_HAGR) _hoops_GHIA(\
	if ((h3ddata)->_hoops_CSC->_hoops_HRGRR != (_hoops_HAGR)) { \
		_hoops_CPPRR(h3ddata, (_hoops_HAGR)); \
	} \
)

#define _hoops_GHPRR(h3ddata,mode) h3ddata->_hoops_GSCR->_hoops_RHPRR(mode);
#define _hoops_HISP(h3ddata,mode) _hoops_GHIA( \
	if (h3ddata->_hoops_CSC->antialias != mode) \
		_hoops_GHPRR(h3ddata, mode); \
)

#define _hoops_AHPRR(h3ddata,mode) (h3ddata)->_hoops_GSCR->_hoops_PHPRR(mode);
#define _hoops_RPAP(h3ddata,mode) _hoops_GHIA( \
	if ((h3ddata)->_hoops_CSC->_hoops_RAIH != mode) \
		_hoops_AHPRR(h3ddata,mode); \
)

#define _hoops_HHPRR(h3ddata,mask) (h3ddata)->_hoops_GSCR->_hoops_IHPRR((mask));
#define _hoops_GPRP(h3ddata,mask) _hoops_GHIA( \
	if ((h3ddata)->_hoops_CSC->_hoops_GRPP != (mask)) \
		_hoops_HHPRR(h3ddata,(mask)); \
)

#define FORCE_CULLING(h3ddata,mode) h3ddata->_hoops_GSCR->_hoops_CCHC(mode);
#define _hoops_RHSA(h3ddata,mode) _hoops_GHIA( \
	if (h3ddata->_hoops_CSC->_hoops_HRSA != mode) \
		FORCE_CULLING(h3ddata, mode); \
)


#define _hoops_CIAP(h3ddata,mode) (h3ddata)->_hoops_GSCR->_hoops_CHPRR(mode);
#define ENSURE_DEPTH_MASK(h3ddata,mode) _hoops_GHIA( \
	if ((h3ddata)->_hoops_CSC->_hoops_AAIH != mode) \
		_hoops_CIAP((h3ddata), mode); \
)

#define _hoops_SHPRR(h3ddata,_hoops_RICR,_hoops_AICR) h3ddata->_hoops_GSCR->_hoops_GIPRR(_hoops_RICR,_hoops_AICR);
#define _hoops_APHH(h3ddata,_hoops_RICR,_hoops_AICR) _hoops_GHIA(\
	if ((_hoops_RICR != h3ddata->_hoops_CSC->_hoops_GSCH[0]) || (_hoops_AICR != h3ddata->_hoops_CSC->_hoops_GSCH[1])) { \
		_hoops_SHPRR(h3ddata, _hoops_RICR, _hoops_AICR); \
	} \
)

/*
 * _hoops_RIPRR _hoops_AIPRR
 */
#define _hoops_PIPRR(h3ddata, nr, mode) h3ddata->_hoops_GSCR->_hoops_HIPRR(nr, mode);
#define _hoops_RRIR(h3ddata, nr, mode) _hoops_GHIA(\
	if (h3ddata->_hoops_CSC->_hoops_GAGRR != mode) {\
		_hoops_PIPRR(h3ddata, nr, mode); \
	} \
)

#define _hoops_IIPRR(h3ddata,mode) (h3ddata)->_hoops_GSCR->_hoops_CIPRR(mode);
#define _hoops_ICSP(h3ddata,mode) _hoops_GHIA( \
	if ((h3ddata)->_hoops_CSC->_hoops_SAGRR != mode) \
		_hoops_IIPRR(h3ddata, mode); \
)


#define _hoops_SIPRR(h3ddata,mode) (h3ddata)->_hoops_GSCR->_hoops_GCPRR(mode);
#define _hoops_HPHH(h3ddata,mode) _hoops_GHIA(\
	if ((h3ddata)->_hoops_CSC->_hoops_IRGRR != mode) \
		_hoops_SIPRR(h3ddata,mode); \
)


#define _hoops_RCPRR(h3ddata) _hoops_GHIA(\
	h3ddata->_hoops_CSC->_hoops_SRGRR.left		= _hoops_RSARR; \
	h3ddata->_hoops_CSC->_hoops_SRGRR.top			= _hoops_RSARR; \
	h3ddata->_hoops_CSC->_hoops_SRGRR.right		= _hoops_RSARR; \
	h3ddata->_hoops_CSC->_hoops_SRGRR.bottom		= _hoops_RSARR; \
)

#define _hoops_ACPRR(h3ddata,_hoops_PCPRR,_hoops_HCPRR,_hoops_ICPRR,_hoops_CCPRR) (h3ddata)->_hoops_GSCR->_hoops_SCPRR(_hoops_PCPRR,_hoops_HCPRR,_hoops_ICPRR,_hoops_CCPRR);
#define ENSURE_SCISSOR_SET(h3ddata,_hoops_PCPRR,_hoops_HCPRR,_hoops_ICPRR,_hoops_CCPRR) _hoops_GHIA(\
	if ((_hoops_PCPRR != h3ddata->_hoops_CSC->_hoops_SRGRR.left) || \
		(_hoops_HCPRR != h3ddata->_hoops_CSC->_hoops_SRGRR.bottom) || \
		(_hoops_ICPRR != h3ddata->_hoops_CSC->_hoops_SRGRR.right) || \
		(_hoops_CCPRR != h3ddata->_hoops_CSC->_hoops_SRGRR.top)) { \
			h3ddata->_hoops_CSC->_hoops_SRGRR.left = _hoops_PCPRR; \
			h3ddata->_hoops_CSC->_hoops_SRGRR.bottom = _hoops_HCPRR; \
			h3ddata->_hoops_CSC->_hoops_SRGRR.right = _hoops_ICPRR; \
			h3ddata->_hoops_CSC->_hoops_SRGRR.top = _hoops_CCPRR; \
			_hoops_ACPRR(h3ddata,_hoops_PCPRR,_hoops_HCPRR,_hoops_ICPRR,_hoops_CCPRR); \
	} \
)

#define _hoops_GSPRR(h3ddata, mode) (h3ddata)->_hoops_GSCR->_hoops_RSPRR(mode);
#define _hoops_ICHH(h3ddata, mode) _hoops_GHIA(\
	if ((h3ddata)->_hoops_CSC->_hoops_PRGRR != mode) { \
		_hoops_GSPRR(h3ddata, mode); \
	} \
)

#define _hoops_ASPRR(h3ddata,_hoops_RHIA,texture) (h3ddata)->_hoops_GSCR->_hoops_PSPRR(_hoops_RHIA,texture);
#define _hoops_SCCR(h3ddata,_hoops_RHIA,_hoops_HSPRR) _hoops_GHIA( \
	if ((h3ddata)->_hoops_CSC->texture[_hoops_RHIA] != _hoops_HSPRR) \
		_hoops_ASPRR((h3ddata), _hoops_RHIA, _hoops_HSPRR); \
)
#define _hoops_ASRP(h3ddata, _hoops_RHIA) _hoops_GHIA(\
	_hoops_SCCR(h3ddata, _hoops_RHIA, null); \
)

#define _hoops_ISPRR(h3ddata,mode) (h3ddata)->_hoops_GSCR->_hoops_CSPRR(mode);
#define ENSURE_TRANSPARENCY(h3ddata,mode) _hoops_GHIA( \
	if ((h3ddata)->_hoops_CSC->_hoops_HSAC != mode) \
		_hoops_ISPRR(h3ddata,mode); \
)

#define _hoops_SSPRR(h3ddata,mode) (h3ddata)->_hoops_GSCR->_hoops_GGHRR(mode);
#define _hoops_PISP(h3ddata,mode) _hoops_GHIA( \
	if ((h3ddata)->_hoops_CSC->_hoops_ARGRR != mode) \
		_hoops_SSPRR(h3ddata, mode); \
)

#define _hoops_RGHRR(h3ddata, _hoops_AGHRR, _hoops_CCGH, _hoops_ICGH) (h3ddata)->_hoops_GSCR->_hoops_PGHRR((_hoops_AGHRR), (_hoops_CCGH), (_hoops_ICGH));
#define _hoops_PACC(h3ddata, _hoops_AGHRR, _hoops_CCGH, _hoops_ICGH) _hoops_GHIA( \
	_hoops_RGHRR(h3ddata, _hoops_AGHRR, _hoops_CCGH, _hoops_ICGH); \
)

#define _hoops_APSS(h3ddata) _hoops_GHIA(\
	{ \
		int _hoops_PSARR; \
		for (_hoops_PSARR = 0; _hoops_PSARR < _hoops_CIGP; ++_hoops_PSARR) { \
			(h3ddata)->_hoops_CSC->_hoops_RAGRR[_hoops_PSARR] = _hoops_RSARR; \
			(h3ddata)->_hoops_CSC->_hoops_AAGRR[_hoops_PSARR] = _hoops_RSARR; \
			(h3ddata)->_hoops_CSC->_hoops_PAGRR[_hoops_PSARR] = _hoops_RSARR; \
			(h3ddata)->_hoops_CSC->_hoops_HAGRR[_hoops_PSARR] = _hoops_RSARR; \
			(h3ddata)->_hoops_CSC->_hoops_IAGRR[_hoops_PSARR] = _hoops_RSARR; \
		} \
	} \
)



/*
 * _hoops_HGHRR
 */
#define _hoops_SRIH (0x0080)
#define _hoops_IGHRR(h3ddata, _hoops_HAGR) h3ddata->_hoops_GSCR->_hoops_CGHRR(_hoops_HAGR);
#define _hoops_RGSS(h3ddata, _hoops_HAGR) _hoops_GHIA(\
	if (h3ddata->_hoops_CSC->_hoops_PGIH != _hoops_HAGR) { \
		_hoops_IGHRR(h3ddata, _hoops_HAGR);	\
	} \
)

#define _hoops_SGHRR(h3ddata, _hoops_HAGR) h3ddata->_hoops_GSCR->_hoops_GRHRR(_hoops_HAGR);
#define _hoops_RRHRR(h3ddata, _hoops_HAGR) _hoops_GHIA(\
	if (h3ddata->_hoops_CSC->_hoops_IRIH != _hoops_HAGR) { \
		_hoops_SGHRR(h3ddata, _hoops_HAGR);	\
	} \
)

#define _hoops_ARHRR(h3ddata, _hoops_HAGR) h3ddata->_hoops_GSCR->_hoops_PRHRR(_hoops_HAGR);
#define _hoops_HRHRR(h3ddata, _hoops_HAGR) _hoops_GHIA(\
	if (h3ddata->_hoops_CSC->_hoops_IGIH != _hoops_HAGR) { \
		_hoops_ARHRR(h3ddata, _hoops_HAGR);	\
	} \
)

#define _hoops_IRHRR(h3ddata, _hoops_HAGR) h3ddata->_hoops_GSCR->_hoops_CRHRR(_hoops_HAGR);
#define _hoops_SRHRR(h3ddata, _hoops_HAGR) _hoops_GHIA(\
	if (h3ddata->_hoops_CSC->_hoops_RGIH != _hoops_HAGR) { \
		_hoops_IRHRR(h3ddata, _hoops_HAGR);	\
	} \
)


#define _hoops_GAHRR(h3ddata, _hoops_AAIS, _hoops_RAHRR, pass) h3ddata->_hoops_GSCR->_hoops_AAHRR(_hoops_AAIS, _hoops_RAHRR, pass);
#define _hoops_PAHRR(h3ddata, _hoops_AAIS, _hoops_RAHRR, pass) _hoops_GHIA(\
	if (h3ddata->_hoops_CSC->_hoops_RRIH != _hoops_AAIS ||		\
		h3ddata->_hoops_CSC->_hoops_PRIH != _hoops_RAHRR ||	\
		h3ddata->_hoops_CSC->_hoops_SGIH != pass) { \
		_hoops_GAHRR(h3ddata, _hoops_AAIS, _hoops_RAHRR, pass);	\
	} \
)

#define _hoops_CRIH(h3ddata, cmp, ref, mask, _hoops_HAHRR) h3ddata->_hoops_GSCR->_hoops_IAHRR(cmp, ref, mask, _hoops_HAHRR);
/*
#_hoops_PPIP _hoops_CAHRR(_hoops_RRAP, _hoops_SAHRR, _hoops_PAGGR, _hoops_PISH, _hoops_GPHRR) _hoops_RPHRR(\
	_hoops_APHRR(_hoops_RRAP, _hoops_SAHRR); \
	_hoops_PPHRR(_hoops_RRAP, _hoops_PAGGR); \
	_hoops_HPHRR(_hoops_RRAP, _hoops_PISH); \
	_hoops_IPHRR(_hoops_RRAP, _hoops_GPHRR); \
)
*/

#define _hoops_GAIH(h3ddata, _hoops_AAIS, _hoops_RAHRR, pass) _hoops_PAHRR(h3ddata, _hoops_AAIS, _hoops_RAHRR, pass)


/*
 * _hoops_CPHRR
 */
#define _hoops_SPHRR(h3ddata, src, _hoops_PCAP) (h3ddata)->_hoops_GSCR->_hoops_GHHRR(src, _hoops_PCAP);
#define _hoops_PPRP(h3ddata, src, _hoops_PCAP) _hoops_GHIA(\
	if ((h3ddata)->_hoops_CSC->_hoops_PHSS != src || (h3ddata)->_hoops_CSC->_hoops_IHSS != _hoops_PCAP) \
		_hoops_SPHRR(h3ddata, src, _hoops_PCAP); \
)

/*
 * _hoops_GRAR _hoops_RHHRR _hoops_AHHRR
 */
#define _hoops_GRPA(h3ddata, _hoops_RHIA, filter, _hoops_PHHRR, _hoops_HHHRR) (h3ddata)->_hoops_GSCR->_hoops_RSCR(_hoops_RHIA, filter, _hoops_PHHRR, _hoops_HHHRR)

/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_IHHRR _hoops_ISHGR
*****************************************************************************
*****************************************************************************/
struct H3D_Bounding_Tree {
	_hoops_CAIS *	_hoops_RCHS;		//_hoops_PCCP _hoops_CRPR _hoops_IIGR _hoops_IHGP _hoops_CHHRR _hoops_IASC _hoops_SHHRR
	int	*			_hoops_ACHS;  //_hoops_HSRR _hoops_GRR _hoops_GIIS, _hoops_RH _hoops_PHI _hoops_IIGR _hoops_RASI _hoops_GIHRR _hoops_RRGI _hoops_SCH.  _hoops_PGPR _hoops_RIIS _hoops_AIIS (_hoops_HAS._hoops_IAS. _hoops_AIRP _hoops_CCA _hoops_IRS 0) _hoops_HS _hoops_RIHRR _hoops_CPAP
	int				count;		//_hoops_RH _hoops_APSR _hoops_PHI _hoops_IIGR _hoops_HHIS _hoops_AIIS.  _hoops_GHCA _hoops_SHH _hoops_HAGH _hoops_HII _hoops_AIHRR _hoops_SPCC _hoops_PGGA _hoops_IIGR _hoops_GRAA-_hoops_RIIS _hoops_AIIS
	int				_hoops_HSAI;
};


/* _hoops_CPIP _hoops_HIGR "_hoops_SCGI _hoops_PIHRR" */
class H3D_Display_List_Bin : public CMO_Pooled
{
public:

	H3D_Display_List_Bin(Memory_Pool * memory_pool) :
	  flags(0),
	  _hoops_CRHA(null),
	  nr(null),
	  odl(0),
	  _hoops_HGGI(0)
	{
		_hoops_IGGI.total = 0,
		_hoops_IGGI._hoops_PHHA = 0,
		_hoops_IGGI.point_count = 0,

		//_hoops_HIHRR(_hoops_RGR, _hoops_IIHRR);
		//_hoops_HIHRR(&_hoops_SCII, _hoops_CIHRR);
		_hoops_CRHA = POOL_NEW(memory_pool, _hoops_AIGI)(memory_pool);
	};
	~H3D_Display_List_Bin() {
		nr = null;
		delete _hoops_CRHA;
	};

	struct {
		int total;
		int _hoops_PHHA;
		int point_count;
	}	_hoops_IGGI;

	/* _hoops_SGPR _hoops_AGCR _hoops_GAR _hoops_RHAC _hoops_CACH _hoops_SIHRR... */
	H3DShaderID			id;
	int					flags;		//_hoops_GII _hoops_GRH _hoops_SGI
	_hoops_AIGI *	_hoops_CRHA;	//_hoops_HIGR _hoops_IIGR _hoops_CPAP _hoops_RSGA _hoops_RRGP (_hoops_GPII)
	Net_Rendition		nr;			//_hoops_RH _hoops_CPAP _hoops_GGR _hoops_IRS _hoops_SCGI _hoops_CGH _hoops_HCR _hoops_HS _hoops_RH _hoops_PSHR _hoops_GCHRR _hoops_IPP
	H3D_Display_List *	odl;		//_hoops_IIPR; _hoops_RH _hoops_ARGR _hoops_AIRI _hoops_HIGR
	int					_hoops_HGGI;	//_hoops_SIC _hoops_IS _hoops_SHH _hoops_IGI _hoops_IH _hoops_CIGS _hoops_RCHRR _hoops_IIGR _hoops_ACHRR
	H3D_Bounding_Tree * _hoops_RSPS;
};

typedef VList<H3D_Display_List_Bin *> H3D_Display_List_Bin_List;



/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_PCHRR _hoops_ISHGR

_hoops_HGI _hoops_CSHGR _hoops_HRGR _hoops_IRS _hoops_PIPS _hoops_AARI _hoops_IRS _hoops_PHIGR _hoops_CIHA _hoops_SRHR.  _hoops_HHIGR _hoops_HCHRR
_hoops_SIHR _hoops_GIPR _hoops_ICHRR _hoops_PPR _hoops_SCSH _hoops_IIHA _hoops_CGAS _hoops_PSCA.
*****************************************************************************
*****************************************************************************/
class H3DIndexBuffer: public CMO
{
public:
	H3DIndexBuffer():_hoops_CCHRR(null), _hoops_SCHRR(null), _hoops_GSHRR(1){}

	H3DIndexBuffer(int const stride, void * const _hoops_RAHC):
	_hoops_CCHRR((short*)_hoops_RAHC), _hoops_SCHRR((short*)_hoops_RAHC), _hoops_GSHRR(stride)
	{
	}


	H3DIndexBuffer(H3DFORMAT const format, void * const _hoops_RAHC)
	{
		_hoops_IRA(format, _hoops_RAHC);
	}

	~H3DIndexBuffer(){}

	void _hoops_IRA(H3DFORMAT const format, void * const _hoops_RAHC)
	{
		_hoops_CCHRR = _hoops_SCHRR = (short *) _hoops_RAHC;

		if (format == H3DFMT_INDEX16)
			_hoops_GSHRR = 1;
		else if (format == H3DFMT_INDEX32)
			_hoops_GSHRR = 2;
		else
			HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
				"Index buffer format must be H3DFMT_INDEX16 or H3DFMT_INDEX32.");
	}

	void _hoops_IRA(int const stride, void * const _hoops_RAHC)
	{
		_hoops_CCHRR = _hoops_SCHRR = (short *) _hoops_RAHC;
		_hoops_GSHRR = stride;
	}

	void _hoops_RSHRR(H3DIndexBuffer const source, int const _hoops_ASHRR)
	{
		int i = 0;
		short *_hoops_PCAP = _hoops_CCHRR;
		short *src = source._hoops_CCHRR;

		if (source._hoops_GSHRR == _hoops_GSHRR)
			COPY_MEMORY(src, _hoops_ASHRR * _hoops_GSHRR * sizeof(short), _hoops_PCAP);
		else if (source._hoops_GSHRR == 2 && _hoops_GSHRR == 1) {
			/* _hoops_HGI _hoops_AGIR _hoops_HRGR _hoops_PSHRR _hoops_IRSGR _hoops_CGPR _hoops_SR _hoops_IPS _hoops_HII _hoops_IRS 32b_hoops_SCH _hoops_HSHRR _hoops_IS _hoops_IRS 16b_hoops_SCH _hoops_ISHRR.
			 * _hoops_HGI _hoops_SIAS _hoops_IHPS _hoops_PGGA _hoops_CSHRR _hoops_HS _hoops_IRS _hoops_SSHRR _hoops_GGIRR _hoops_SGS _hoops_SCH _hoops_PAH'_hoops_RA _hoops_HS _hoops_RRI _hoops_HSAR
			 * 2^16 _hoops_PSPI _hoops_CGPR _hoops_SCH'_hoops_GRI _hoops_RGIRR _hoops_GAR 16b_hoops_SCH, _hoops_AGIRR 16b_hoops_SCH _hoops_PGIRR _hoops_PAH.  _hoops_GPGP _hoops_RGR _hoops_AGIR,
			 * _hoops_HCR _hoops_IIGR _hoops_RH _hoops_HSHRR'_hoops_GRI _hoops_PSPI _hoops_CHH _hoops_SHH 16b_hoops_RGCI _hoops_PAR _hoops_CRGP (_hoops_SR _hoops_HGIRR'_hoops_RA _hoops_HS _hoops_IRS 16b_hoops_SCH _hoops_PPHS _hoops_IAII),
			 * _hoops_HIS _hoops_SR _hoops_PAH _hoops_IGIRR _hoops_IPS _hoops_RH _hoops_RSSA _hoops_IAPR.
			 */

			for (i = 0; i < _hoops_ASHRR; i++) {
				*_hoops_PCAP = *((int *) src);
				_hoops_PCAP += _hoops_GSHRR;
				src += source._hoops_GSHRR;
			}
		}
		else {
			for (i = 0; i < _hoops_ASHRR; i++) {
				*((int *) _hoops_PCAP) = *src;
				_hoops_PCAP += _hoops_GSHRR;
				src += source._hoops_GSHRR;
			}
		}
	}

	// _hoops_CGIRR
	int const operator*() const {
		if (_hoops_GSHRR == 2)
			return *((int *)_hoops_CCHRR);
		else
			return *_hoops_CCHRR;
	}

	bool const operator==(H3DIndexBuffer const &right) const {
		return (this->_hoops_CCHRR == right._hoops_CCHRR);
	}
	bool const operator!=(H3DIndexBuffer const &right) const {
		return (this->_hoops_CCHRR != right._hoops_CCHRR);
	}

	H3DIndexBuffer const & operator=(int const number) {
		if (_hoops_GSHRR == 2)
			*((int *) _hoops_CCHRR) = number;
		else
			*_hoops_CCHRR = number;
		return *this;
	}
	H3DIndexBuffer const & operator++() {
		_hoops_CCHRR += _hoops_GSHRR;
		return *this;
	}
	H3DIndexBuffer const & operator--() {
		_hoops_CCHRR -= _hoops_GSHRR;
		return *this;
	}
	H3DIndexBuffer const & operator+=(int const _hoops_GCCGR) {
		_hoops_CCHRR += _hoops_GCCGR * _hoops_GSHRR;
		return *this;
	}
	H3DIndexBuffer const & operator-=(int const _hoops_GCCGR) {
		_hoops_CCHRR -= _hoops_GCCGR * _hoops_GSHRR;
		return *this;
	}
	H3DIndexBuffer const operator+(int const _hoops_GCCGR) const {
		H3DIndexBuffer _hoops_SGIRR;
		_hoops_SGIRR._hoops_CCHRR = _hoops_CCHRR + _hoops_GCCGR * _hoops_GSHRR;
		_hoops_SGIRR._hoops_GSHRR = _hoops_GSHRR;
		return _hoops_SGIRR;
	}
	H3DIndexBuffer operator-(int const _hoops_GCCGR) const {
		return *this + (-_hoops_GCCGR);
	}
	H3DIndexBuffer operator[](int const index) {
		return H3DIndexBuffer(_hoops_GSHRR, (void*)(_hoops_CCHRR + index*_hoops_GSHRR));
	}

	int const operator-(H3DIndexBuffer const &right) const {
		return _hoops_GSHRR ? (this->_hoops_CCHRR - right._hoops_CCHRR) / _hoops_GSHRR : 0;
	}

	short *_hoops_HACGR() {
		return _hoops_CCHRR;
	}

	short *_hoops_ARHS() {
		return _hoops_SCHRR;
	}

	int const length() const {
		return (_hoops_CCHRR - _hoops_SCHRR) / _hoops_GSHRR;
	}

private:
	short *_hoops_CCHRR, *_hoops_SCHRR;
	short _hoops_GSHRR;
};


/*****************************************************************************
*****************************************************************************
							_hoops_GR: _hoops_GRIRR
*****************************************************************************
*****************************************************************************/
#define _hoops_RRIRR(_hoops_ARIRR) (!BIT(_hoops_ARIRR,Test_EXTENT) && (_hoops_ARIRR != Test_DISJOINT))

// _hoops_PRIRR _hoops_HRIRR _hoops_GRR _hoops_GPHA (_hoops_PAR _hoops_CIHA) _hoops_IS _hoops_SHH _hoops_HSHA _hoops_GAR _hoops_HSGS (_hoops_PSP _hoops_IRIRR)
#define _hoops_CRIRR(_hoops_SRIRR, _hoops_CACP, _hoops_GAIRR) _hoops_GHIA (\
	if (_hoops_GAIRR) \
		_hoops_SRIRR = -1; \
	else \
		_hoops_SRIRR = _hoops_PHAS[_hoops_CACP]; \
	if (_hoops_SRIRR < 0) { \
		_hoops_SRIRR = _hoops_PHAS[_hoops_CACP] = _hoops_GHAS++; \
	} \
)


class H3DIndexedBufferObject : public CMO
{
public:
	unsigned int									_hoops_RAIRR;
	unsigned int									_hoops_GSHRR;
	H3DVertexFormat									_hoops_AAIRR;
	H3DFORMAT										_hoops_GSPP;

	H3D_Bounding_Tree *								_hoops_IAHS;
	int *											_hoops_RPHS;
	int												_hoops_GPHS;	//_hoops_RH _hoops_SRS _hoops_PAIRR'_hoops_GRI _hoops_CIHA _hoops_GGR _hoops_RH _hoops_PPHS
	int												_hoops_SAHS;

	bool											_hoops_HAIRR;

	H3DIndexedBufferObject()
	{
		_hoops_RAIRR = 0;
		_hoops_RPHS = null;
		_hoops_IAHS = null;
		_hoops_SAHS = 0;
		_hoops_HAIRR = true;
	}
	virtual ~H3DIndexedBufferObject()
	{
		if (_hoops_RPHS)
			FREE_ARRAY(_hoops_RPHS, _hoops_SAHS, int);
		if (_hoops_IAHS &&
			_hoops_ISAI (_hoops_IAHS) == 0) {
			FREE_ARRAY (_hoops_IAHS->_hoops_RCHS, _hoops_IAHS->count, _hoops_CAIS);
			FREE (_hoops_IAHS, H3D_Bounding_Tree);
		}
	}

	//_hoops_PIGS _hoops_ARR _hoops_RIR _hoops_IAIRR
	virtual bool CreateVertexBuffer (H3DData *h3ddata,
								unsigned int point_count,
								H3DVertexFormat VF) = 0;

	//_hoops_PIGS _hoops_GARI->_hoops_IIRGR _hoops_IACH _hoops_RIR _hoops_IAIRR
	virtual bool CreateIndexBuffer (H3DData *h3ddata,
								H3DPRIMITIVETYPE type,
								unsigned int length,
								unsigned int count) = 0;

	virtual bool _hoops_CAIRR (H3DData *h3ddata,
								unsigned int point_count,
								unsigned int face_count,
								H3DVertexFormat VF)
	{
		if (CreateVertexBuffer(h3ddata, point_count, VF) &&
			CreateIndexBuffer(h3ddata, H3DPT_TRIANGLELIST, face_count * 3 * sizeof(int), face_count))
			return true;
		return false;
	};

	virtual bool LockIndexBuffer(unsigned int _hoops_SAIRR, unsigned int _hoops_GPIRR, H3DIndexBuffer *_hoops_RAHC, unsigned int Flags) = 0;
	virtual bool LockVertexBuffer(unsigned int _hoops_SAIRR, unsigned int _hoops_GPIRR, H3DVertexBuffer *_hoops_PAIH, unsigned int Flags) = 0;
	virtual void UnlockIndexBuffer() = 0;
	virtual void UnlockVertexBuffer() = 0;
	virtual void _hoops_CHSA(H3DData *h3ddata, Test *cull_results = null) = 0;
	virtual void _hoops_GPAS(H3DData *h3ddata, float _hoops_RPIRR = 1.0f) = 0;

	int _hoops_SRAS () const { return _hoops_RAIRR; }

	void _hoops_PAHS(float *vertices, int size)
	{
		H3DVertexBuffer _hoops_PAIH;
		LockVertexBuffer(0, 0, &_hoops_PAIH, 0);
		COPY_MEMORY(vertices, size, _hoops_PAIH._hoops_ARHS());
		UnlockVertexBuffer();
	}

	void _hoops_HAHS(short *indices, int size)
	{
		H3DIndexBuffer _hoops_CHPC;
		LockIndexBuffer(0, 0, &_hoops_CHPC, 0);
		COPY_MEMORY(indices, size, _hoops_CHPC._hoops_ARHS());
		UnlockIndexBuffer();
	}

	bool _hoops_SGPS() const {return _hoops_HAIRR; }
};



class H3DVertexBufferCache : public CMO
{
public:
	H3DVertexBufferCache(){}
	virtual ~H3DVertexBufferCache(){}

	virtual bool CreateVertexBuffer(H3DData *h3ddata, unsigned int _hoops_APIRR, H3DVertexFormat VF) = 0;
	virtual bool Reset() = 0;

	virtual bool _hoops_RIAC() = 0;
	virtual bool _hoops_PPIRR(_hoops_HRPA const *matrix = null, int length = 0) = 0;
	virtual bool Lock(unsigned int count, H3DVertexBuffer *_hoops_PAIH) = 0;
	virtual bool Unlock(_hoops_HRPA const *matrix = null) = 0;
	virtual bool _hoops_CHSA(H3DData *h3ddata , H3DPRIMITIVETYPE _hoops_HPIRR, unsigned int _hoops_IPIRR) = 0;
	virtual bool _hoops_HGSA(H3DData *h3ddata , H3DPRIMITIVETYPE _hoops_HPIRR, unsigned int _hoops_IPIRR) = 0;
	virtual void _hoops_CGSA() = 0;

	H3DVertexFormat			_hoops_AAIRR;
	unsigned int			_hoops_CPIRR;
	unsigned int			_hoops_SPIRR;
	unsigned int			_hoops_GRIC;
	unsigned int			_hoops_APIH;
	unsigned int			_hoops_PPIH;
	unsigned int			_hoops_GHIRR;
	unsigned int			_hoops_RHIRR;

	unsigned int			_hoops_AHIRR;
	unsigned int			_hoops_PHIRR;
	float					*_hoops_HHIRR;
	float					*_hoops_IHIRR;
	float					*_hoops_CHIRR;
	float					*_hoops_SHIRR;
	float					*_hoops_GIIRR;
	float					*_hoops_RIIRR;
};


class H3DIndexBufferCache : public CMO
{
public:
	H3DIndexBufferCache(){};
	virtual ~H3DIndexBufferCache(){};

	virtual bool CreateIndexBuffer(H3DData *h3ddata) = 0;
	virtual bool Lock(short count, short **_hoops_AIIRR) = 0;
	virtual bool Unlock() = 0;
	virtual bool _hoops_CHSA(H3DData *h3ddata, H3DPRIMITIVETYPE _hoops_HPIRR,
		unsigned int _hoops_PIIRR,
		unsigned int _hoops_IPIRR) = 0;

	virtual void _hoops_CGSA() = 0;
	virtual void _hoops_GAPRR (H3DVertexBufferCache *_hoops_IRPRR) = 0;
};


/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_HIIRR _hoops_CSHGR
*****************************************************************************
*****************************************************************************/
class H3DConstantTable
{
protected:
	H3DData *_hoops_ISS;

public:
	H3DConstantTable(H3DData *h3ddata)
	{
		_hoops_ISS = h3ddata;
	};
	virtual ~H3DConstantTable() {};

	virtual void SetFloat(const char *name, const float value)
	{
		_hoops_GIHGR;
		UNREFERENCED(name);
		UNREFERENCED(value);
	}
	virtual void SetFloatArray(const char *handle, const float *values, int count)
	{
		_hoops_GIHGR;
		UNREFERENCED(handle);
		UNREFERENCED(values);
		UNREFERENCED(count);
	};
	virtual void SetMatrix(const char *name, const float *matrix)
	{
		_hoops_GIHGR;
		UNREFERENCED(name);
		UNREFERENCED(matrix);
	}
	virtual void SetVector(const char *name, const float *vector, const int _hoops_IIIRR = 4)
	{
		_hoops_GIHGR;
		UNREFERENCED(name);
		UNREFERENCED(vector);
		UNREFERENCED(_hoops_IIIRR);
	};
	virtual void SetVectorArray(const char *name, const float *_hoops_CIIRR, const float _hoops_SIIRR, const int _hoops_IIIRR = 4)
	{
		_hoops_GIHGR;
		UNREFERENCED(name);
		UNREFERENCED(_hoops_CIIRR);
		UNREFERENCED(_hoops_IIIRR);
		UNREFERENCED(_hoops_SIIRR);
	};
	virtual unsigned long GetSamplerIndex(const char *name)
	{
		_hoops_GIHGR;
		UNREFERENCED(name);
		return 0;
	};
};


/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_CGRP _hoops_CSHGR
*****************************************************************************
*****************************************************************************/
#define _hoops_GCIRR			0x0000
#define _hoops_RCIRR			0x0001
#define _hoops_ACIRR			0x0002
#define _hoops_PCIRR			0x0004
#define _hoops_HCIRR			0x0008
#define _hoops_ICIRR		0x0010		//_hoops_RAIA _hoops_GIAP _hoops_GIHC _hoops_CIIA
#define _hoops_CCIRR	0x0020
#define _hoops_SCIRR	0x0040
#define _hoops_GSIRR	0x0080

// _hoops_GGPR _hoops_RSIRR/_hoops_ASIRR _hoops_PSAI
struct _hoops_PSIRR
{
	char const *filename;
	char const *string;
	int flags;				//_hoops_HSIRR _hoops_SGI _hoops_IS _hoops_IRHC #_hoops_CPPC _hoops_IS _hoops_PPSI _hoops_GGR _hoops_AIRRR
};

// _hoops_ISIRR _hoops_IRS _hoops_CI _hoops_RSIRR
#define _hoops_CSIRR(name,flags) { #name, name, flags }





// _hoops_SSIRR _hoops_HCH _hoops_AGI.
enum
{
	_hoops_CGPP		= (1<<0),
	_hoops_CRHP			= (1<<1),
	_hoops_AHHP	= (1<<2),
	_hoops_GGCRR			= (1<<3),
	_hoops_RGCRR				= (1<<4),
	_hoops_GIHP				= (1<<5),
	_hoops_AGCRR				= (1<<6),
};

class H3DPost {
public:
	H3DPost() :
		_hoops_PGCRR(null),
		_hoops_ISS(null),
		_hoops_HGCRR(null),
		_hoops_IGCRR(null),
		_hoops_CGCRR(null)

	{
		memset( _hoops_SGCRR, 0, sizeof(_hoops_SGCRR) );
	}
	virtual ~H3DPost() {}

	virtual bool _hoops_GGPP() {
		_hoops_GIHGR;
		return false;
	};
	virtual void _hoops_PRHP() {
		_hoops_GIHGR;
	};

	// _hoops_CRSR _hoops_RHAA _hoops_AIRRR _hoops_CHR _hoops_HHPA?
	enum _hoops_GRCRR
	{
		_hoops_HIGP,
		_hoops_HGRGR,
		_hoops_RRCRR,
	};

	enum _hoops_AGSA
	{
		// _hoops_GHHGR-_hoops_AHAR
		_hoops_ARCRR,
		_hoops_PRCRR,
		_hoops_HRCRR,
		_hoops_IRCRR,
		_hoops_CRCRR,
		_hoops_SRCRR,
		_hoops_GACRR,

		// _hoops_RACRR-_hoops_AHAR
		_hoops_IGRGR,
		_hoops_IPPP,
		_hoops_AACRR,
		_hoops_SAPP,
		_hoops_SIRP,
		_hoops_SRHP,
		_hoops_PHHP,
		_hoops_PACRR,
		_hoops_RASH,
		_hoops_HACRR,
		_hoops_IAIP,
		_hoops_CCAP,
		_hoops_RAIP,
		_hoops_HISH,
		_hoops_ACSH,

		_hoops_IACRR,
	};

	virtual H3DConstantTable *_hoops_PIGP( _hoops_GRCRR const _hoops_CACRR, _hoops_AGSA const which )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_CACRR);
		UNREFERENCED(which);
		return null;
	}

	enum _hoops_SACRR
	{
		_hoops_ASGP,
		_hoops_CSGP,
		_hoops_HGRP,

		_hoops_GPCRR,
	};

	virtual _hoops_SACRR _hoops_RSGP( _hoops_AGSA const which )
	{
		_hoops_GIHGR;
		UNREFERENCED(which);
		return _hoops_ASGP;
	}

	void _hoops_RPCRR();

	// _hoops_SIPR _hoops_IRS _hoops_AH _hoops_SRGS-_hoops_SAAP _hoops_HH _hoops_SRHR _hoops_HII _hoops_RH _hoops_IHAH
	H3DTexture *_hoops_IAAP(const unsigned long width, const unsigned long height, const H3DFORMAT format);

	// _hoops_SIPR _hoops_IRS _hoops_AH _hoops_SRGS-_hoops_SAAP _hoops_SRHR _hoops_HII _hoops_RH _hoops_IHAH
	H3DRenderTarget *_hoops_RCGGR(const unsigned long width, const unsigned long height, const H3DFORMAT format, bool _hoops_ISARR);

	// _hoops_GPR _hoops_SGS _hoops_RPRGR _hoops_SSCP _hoops_APCRR _hoops_CCA _hoops_IRS _hoops_AH _hoops_SRHR
	void _hoops_HAAP(H3DTexture **texture);

	// _hoops_GPR _hoops_SGS _hoops_RPRGR _hoops_SSCP _hoops_APCRR _hoops_CCA _hoops_IRS _hoops_AH _hoops_SRHR
	void _hoops_IPRGR(H3DRenderTarget ** surface);

	virtual void Copy(H3DRenderTarget *_hoops_PCAP, H3DTexture *src, RGBA const * _hoops_SSHR = null, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT)
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_PCAP);
		UNREFERENCED(src);
		UNREFERENCED(_hoops_SSHR);
		UNREFERENCED(filter);
	}

	virtual void Copy(H3DTexture *_hoops_PCAP, H3DTexture *src, RGBA const * _hoops_SSHR = null, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT)
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_PCAP);
		UNREFERENCED(src);
		UNREFERENCED(_hoops_SSHR);
		UNREFERENCED(filter);
	}

	virtual void _hoops_PPCRR(H3DTexture *_hoops_PCAP, H3DTexture *src, int _hoops_HPCRR, Vector const *_hoops_IGGP, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT)
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_PCAP);
		UNREFERENCED(src);
		UNREFERENCED(_hoops_HPCRR);
		UNREFERENCED(_hoops_IGGP);
		UNREFERENCED(filter);
	}

	virtual void _hoops_PPCRR(H3DRenderTarget *_hoops_PCAP, H3DTexture *src, int _hoops_HPCRR, Vector const *_hoops_IGGP, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT)
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_PCAP);
		UNREFERENCED(src);
		UNREFERENCED(_hoops_HPCRR);
		UNREFERENCED(_hoops_IGGP);
		UNREFERENCED(filter);
	}

	virtual void _hoops_IPCRR( H3DTexture * _hoops_PCAP, H3DTexture * src, H3DTexture *depth, int _hoops_HPCRR, Vector const *_hoops_IGGP, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_PCAP);
		UNREFERENCED(src);
		UNREFERENCED(_hoops_HPCRR);
		UNREFERENCED(_hoops_IGGP);
		UNREFERENCED(filter);
		UNREFERENCED(depth);
	}

	virtual void _hoops_GAIP( H3DTexture * _hoops_PCAP, H3DTexture * src, _hoops_AGSA which, int _hoops_HPCRR, Vector const *_hoops_IGGP, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_PCAP);
		UNREFERENCED(src);
		UNREFERENCED(_hoops_HPCRR);
		UNREFERENCED(_hoops_IGGP);
		UNREFERENCED(filter);
		UNREFERENCED(which);
	}

	// _hoops_RGPA _hoops_RH _hoops_CHIA _hoops_AI _hoops_GIRP _hoops_GPP _hoops_RH _hoops_SAAP
	virtual void _hoops_AHSH( H3DRenderTarget * _hoops_PCAP, H3DTexture **_hoops_CPCRR, int _hoops_SPCRR, RGBA const *_hoops_SSHR = null, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_PCAP);
		UNREFERENCED(_hoops_CPCRR);
		UNREFERENCED(_hoops_SPCRR);
		UNREFERENCED(_hoops_SSHR);
		UNREFERENCED(filter);
	}

	// _hoops_CIRP _hoops_RH _hoops_CHIA _hoops_HH _hoops_IS _hoops_RH _hoops_SAAP
	virtual void _hoops_AHSH( H3DTexture * _hoops_PCAP, H3DTexture **_hoops_CPCRR, int _hoops_SPCRR, RGBA const *_hoops_SSHR = null, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_PCAP);
		UNREFERENCED(_hoops_CPCRR);
		UNREFERENCED(_hoops_SPCRR);
		UNREFERENCED(_hoops_SSHR);
		UNREFERENCED(filter);
	}


	//
	// _hoops_GHCRR
	//

	// _hoops_SRIP _hoops_IRS _hoops_HH _hoops_GRP _hoops_IRS 7x7 _hoops_SPRP _hoops_RGGP
	void _hoops_HASH( H3DTexture *texture, int _hoops_RHCRR = 1 );

	// _hoops_SRIP _hoops_IRS _hoops_HH _hoops_GRP _hoops_IRS 7x7 _hoops_AHCRR _hoops_RGGP
	void _hoops_PHCRR( H3DTexture *texture, int _hoops_RHCRR = 1 );

	// _hoops_SRIP _hoops_IRS _hoops_HH _hoops_GRP _hoops_IRS 3x3 _hoops_SPRP _hoops_RGGP
	void _hoops_GPSH( H3DTexture *texture, int _hoops_RHCRR = 1 );

	// _hoops_SRIP _hoops_IRS _hoops_HH _hoops_GRP _hoops_IRS 3x3 _hoops_AHCRR _hoops_RGGP
	void _hoops_CGGGR( H3DTexture *texture, int _hoops_RHCRR = 1 );

	// _hoops_SRIP _hoops_IRS _hoops_HH _hoops_GRP _hoops_IRS _hoops_PGSH-_hoops_HHCRR _hoops_RGGP
	void _hoops_PPSH( H3DTexture *texture, int _hoops_RHCRR = 1 );


	virtual void _hoops_HPRP( H3DRenderTarget *_hoops_PCAP, _hoops_AGSA const which, float depth = 0.0f, float const *matrix = null, H3DTexture *_hoops_IHCRR = null) {
		_hoops_GIHGR;
		UNREFERENCED(_hoops_PCAP);
		UNREFERENCED(which);
		UNREFERENCED(depth);
		UNREFERENCED(matrix);
		UNREFERENCED(_hoops_IHCRR);
	};

	virtual H3DConstantTable * _hoops_CHCRR(_hoops_AGSA which, float depth = 0.0f, float const *matrix = null, H3DTexture *_hoops_IHCRR = null) {
		_hoops_GIHGR;
		UNREFERENCED(which);
		UNREFERENCED(depth);
		UNREFERENCED(matrix);
		UNREFERENCED(_hoops_IHCRR);
		return false;
	};

	// _hoops_RAPH
	void _hoops_SHCRR( H3DTexture* src );			// _hoops_HCGA _hoops_PPPR _hoops_SHI _hoops_IS _hoops_A _hoops_IIHA _hoops_GPP _hoops_RAGA _hoops_HH

	virtual void _hoops_GICRR() {
		_hoops_GIHGR;
		return;
	};

protected:
	struct _hoops_RICRR
	{
		bool _hoops_CPCR;										// _hoops_HCIC _hoops_AICRR _hoops_GRP _hoops_RGR _hoops_SRHR?
		H3DTexture		*texture;							// _hoops_IPCP _hoops_PSGRR _hoops_HH
		H3DRenderTarget *surface;							// _hoops_IPCP _hoops_ISSGR (_hoops_IH _hoops_HCH _hoops_PSCA)
		_hoops_RICRR *next;										// _hoops_CPR _hoops_SRHR _hoops_GGR _hoops_RH _hoops_AASH
	};
	_hoops_RICRR *_hoops_PGCRR;											// _hoops_ICSH _hoops_IIGR _hoops_AH _hoops_PSCA _hoops_SR'_hoops_RISP _hoops_PSPP

	H3DData *_hoops_ISS;
	H3DVertexFormat _hoops_AAIRR;
	H3DIndexedBufferObject *_hoops_HGCRR;

	H3DConstantTable *_hoops_IGCRR;
	H3DConstantTable *_hoops_CGCRR;
	H3DConstantTable *_hoops_SGCRR[_hoops_RRCRR][_hoops_IACRR];		// _hoops_PICRR _hoops_PIRRR _hoops_IH _hoops_PCIA _hoops_RH _hoops_AIR _hoops_AIRRR.
};


/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_HAIA _hoops_HICRR _hoops_PSCH
*****************************************************************************
*****************************************************************************/
void H3DMatrixPerspectiveLH(float *matrix,
	float w,
	float h,
	float _hoops_SHCR,
	float _hoops_GICR,
	int _hoops_ACCR);

void H3DMatrixOrthoLH(float *matrix,
	float w,
	float h,
	float _hoops_SHCR,
	float _hoops_GICR,
	int _hoops_ACCR);

/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_IICRR _hoops_ISHGR

_hoops_HGI _hoops_CSHGR _hoops_ICGI _hoops_CICRR _hoops_IS _hoops_RHPP _hoops_SASI _hoops_HICRR _hoops_PSCH.
*****************************************************************************
*****************************************************************************/
struct _hoops_PPRS
{
	enum { _hoops_SICRR = 4 };
	H3DRenderTarget *_hoops_PGRGR[_hoops_SICRR];
	H3DRenderTarget *depth_stencil;
};

class H3DActions : public CMO
{
protected:
	H3DData *_hoops_ISS;

public:
	H3DActions(){};
	H3DActions(H3DData *h3ddata) {_hoops_ISS = h3ddata;};


public:

// _hoops_AHH: _hoops_GCCRR _hoops_SPR _hoops_HIGR _hoops_IIGR _hoops_PGSI _hoops_PPR _hoops_CICA _hoops_GAPA _hoops_CAPRR _hoops_ARI
#ifdef _hoops_CHHGR
#define H3DACTION(_hoops_RCCRR) virtual _hoops_RCCRR = 0
#else
#define H3DACTION(_hoops_RCCRR) virtual _hoops_RCCRR
#endif

	H3DACTION( void _hoops_GHIP(H3DData				*h3ddata,
											H3DTexture			*texture,
											int					x,
											int					y,
											int					width,
											int					height,
											float				_hoops_ACCRR = 0,
											float				_hoops_ISPI = 0,
											float				_hoops_PCCRR = 1,
											float				_hoops_CSPI = 1))
	{
		_hoops_GIHGR;
		UNREFERENCED(h3ddata);
		UNREFERENCED(texture);
		UNREFERENCED(x);
		UNREFERENCED(y);
		UNREFERENCED(width);
		UNREFERENCED(height);
		UNREFERENCED(_hoops_ACCRR);
		UNREFERENCED(_hoops_ISPI);
		UNREFERENCED(_hoops_PCCRR);
		UNREFERENCED(_hoops_CSPI);
	}

	H3DACTION( H3DVertexBufferCache* _hoops_HAIH() ) {_hoops_GIHGR; return null;};
	H3DACTION( H3DIndexBufferCache* _hoops_SRPRR() ) {_hoops_GIHGR; return null;};
	H3DACTION( H3DIndexedBufferObject* _hoops_PRAS() ) {_hoops_GIHGR; return null;};
	H3DACTION( H3DIndexedBufferObject* _hoops_CAIRR() )
	{
		return _hoops_PRAS();
	}

	H3DACTION( H3DPost* _hoops_HCCRR() ) {_hoops_GIHGR; return null;};

	H3DACTION( bool CreateTexture(
		unsigned int width,
		unsigned int height,
		unsigned int _hoops_ICRH,
		unsigned int _hoops_GCI,
		H3DFORMAT format,
		H3DTexture **id) )
	{
		_hoops_GIHGR;
		UNREFERENCED(width);
		UNREFERENCED(height);
		UNREFERENCED(_hoops_ICRH);
		UNREFERENCED(_hoops_GCI);
		UNREFERENCED(format);
		UNREFERENCED(id);
		return false;
	};

	H3DACTION( bool CreateCubeTexture(
		unsigned int size,
		unsigned int _hoops_ICRH,
		unsigned int _hoops_GCI,
		H3DCubeTexture **id) )
	{
		_hoops_GIHGR;
		UNREFERENCED(size);
		UNREFERENCED(_hoops_ICRH);
		UNREFERENCED(_hoops_GCI);
		UNREFERENCED(id);
		return false;
	};

	H3DACTION( bool _hoops_PSRH(
		unsigned int w,
		unsigned int h,
		unsigned int depth,
		unsigned int _hoops_ICRH,
		unsigned int _hoops_GCI,
		H3DFORMAT format,
		H3DTexture3D **id) )
	{
		_hoops_GIHGR;
		UNREFERENCED(w);
		UNREFERENCED(h);
		UNREFERENCED(depth);
		UNREFERENCED(_hoops_ICRH);
		UNREFERENCED(_hoops_GCI);
		UNREFERENCED(format);
		UNREFERENCED(id);
		return false;
	};

	H3DACTION( bool CreateRenderTarget(
		unsigned int width,
		unsigned int height,
		unsigned int _hoops_GCI,
		H3DFORMAT _hoops_GCH,
		unsigned int _hoops_ISARR,
		H3DRenderTarget **id))
	{
		_hoops_GIHGR;
		UNREFERENCED(width);
		UNREFERENCED(height);
		UNREFERENCED(_hoops_GCI);
		UNREFERENCED(_hoops_GCH);
		UNREFERENCED(_hoops_ISARR);
		UNREFERENCED(id);
		return false;
	};

	H3DACTION( void SetTexture(int _hoops_RHIA, H3DTexture *id) )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_RHIA);
		UNREFERENCED(id);
	}

	H3DACTION( void SetViewport(H3DViewport const *_hoops_APPRR) )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_APPRR);
	}

	H3DACTION( H3DShader* _hoops_ICCRR(H3DShaderID id) )
	{
		_hoops_GIHGR;
		UNREFERENCED(id);
		return null;
	}

	H3DACTION( void Clear(int flags, int color, float _hoops_CCCRR, int _hoops_SCCRR, bool _hoops_GSCRR = false) )
	{
		_hoops_GIHGR;
		UNREFERENCED(flags);
		UNREFERENCED(color);
		UNREFERENCED(_hoops_CCCRR);
		UNREFERENCED(_hoops_SCCRR);

		// _hoops_RGR _hoops_RSCRR _hoops_HRGR _hoops_IGI _hoops_IS _hoops_HHSA _hoops_RGAR _hoops_IRS _hoops_AASA _hoops_IS _hoops_SCAC _hoops_API, _hoops_SIHH _hoops_RH _hoops_ACPI _hoops_RRGR _hoops_AARI _hoops_IH _hoops_HCH _hoops_AGI
		UNREFERENCED(_hoops_GSCRR);
	}

	H3DACTION( void _hoops_ASCRR(wchar_t const *string) )
	{
		_hoops_GIHGR;
		UNREFERENCED(string);
	}
	H3DACTION( void _hoops_PSCRR(wchar_t const *string) )
	{
		_hoops_GIHGR;
		UNREFERENCED(string);
	}

	H3DACTION( bool _hoops_HSCRR(size_t _hoops_HHARR) )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_HHARR);
		return false;
	}

	H3DACTION( bool _hoops_GSAC(Net_Rendition const & nr, _hoops_RCR *txr, int _hoops_GCI, H3DTexture *id, int _hoops_GRRA) )
	{
		_hoops_GIHGR;
		UNREFERENCED(nr);
		UNREFERENCED(txr);
		UNREFERENCED(_hoops_GCI);
		UNREFERENCED(id);
		UNREFERENCED(_hoops_GRRA);
		return false;
	}

	H3DACTION( void create_region (Net_Rendition const &  nr,
			Int_Rectangle const * area, void **image, void **z) )
	{
		_hoops_GIHGR;
		UNREFERENCED(nr);
		UNREFERENCED(area);
		UNREFERENCED(image);
		UNREFERENCED(z);
	}

	H3DACTION( void _hoops_HIPGR (Net_Rendition const &  nr,
			Int_Rectangle const * area, void alter * image, void alter * z) )
	{
		_hoops_GIHGR;
		UNREFERENCED(nr);
		UNREFERENCED(area);
		UNREFERENCED(image);
		UNREFERENCED(z);
	}

	H3DACTION( void _hoops_PIPGR (Net_Rendition const &  nr,
			Int_Rectangle const * area, void alter * image, void alter * z) )
	{
		_hoops_GIHGR;
		UNREFERENCED(nr);
		UNREFERENCED(area);
		UNREFERENCED(image);
		UNREFERENCED(z);
	}

	H3DACTION( void _hoops_ISPGR (Display_Context alter * dc,
			void alter * image, void alter * z) )
	{
		_hoops_GIHGR;
		UNREFERENCED(dc);
		UNREFERENCED(image);
		UNREFERENCED(z);
	}

	H3DACTION( void _hoops_CSPGR (Display_Context alter * dc) )
	{
		_hoops_GIHGR;
		UNREFERENCED(dc);
	}

	H3DACTION( void _hoops_AGHGR (Display_Context alter * dc) )
	{
		_hoops_GIHGR;
		UNREFERENCED(dc);
	}

	H3DACTION( void _hoops_IPRS( _hoops_PPRS *_hoops_HPRS ) )	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_HPRS);
	}
	H3DACTION( void _hoops_CHRS( _hoops_PPRS *_hoops_HPRS,  bool release = true) )	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_HPRS);
		UNREFERENCED(release);
	}
	H3DACTION( void _hoops_GPAP (
		H3DRenderTarget		*_hoops_ISCRR,
		H3DRenderTarget		*_hoops_AASP = null,
		H3DRenderTarget		*_hoops_CSCRR = null,
		H3DRenderTarget		*_hoops_SSCRR = null,
		H3DRenderTarget		*_hoops_GGSRR = null)) {
		_hoops_GIHGR;
		UNREFERENCED(_hoops_ISCRR);
		UNREFERENCED(_hoops_AASP);
		UNREFERENCED(_hoops_CSCRR);
		UNREFERENCED(_hoops_SSCRR);
		UNREFERENCED(_hoops_GGSRR);
	}

	H3DACTION( bool _hoops_PHCS(
		H3DRenderTarget		*_hoops_ISCRR,
		H3DRenderTarget		*_hoops_AASP = null,
		H3DRenderTarget		*_hoops_CSCRR = null,
		H3DRenderTarget		*_hoops_SSCRR = null,
		H3DRenderTarget		*_hoops_GGSRR = null)) {
		_hoops_GIHGR;
		UNREFERENCED(_hoops_ISCRR);
		UNREFERENCED(_hoops_AASP);
		UNREFERENCED(_hoops_CSCRR);
		UNREFERENCED(_hoops_SSCRR);
		UNREFERENCED(_hoops_GGSRR);
		return false;
	};

	H3DACTION( void _hoops_GGSS (float _hoops_RGSRR, float _hoops_SICS) ) {
		_hoops_GIHGR;
		UNREFERENCED(_hoops_RGSRR);
		UNREFERENCED(_hoops_SICS);
	}

	H3DACTION( void _hoops_SPPRR (bool mode) )
	{
		_hoops_GIHGR;
		UNREFERENCED(mode);
	}
	H3DACTION( void _hoops_RHPRR (bool mode) )
	{
		_hoops_GIHGR;
		UNREFERENCED(mode);
	}
	H3DACTION( void _hoops_GHHRR (H3DBLEND src, H3DBLEND _hoops_PCAP) )
	{
		_hoops_GIHGR;
		UNREFERENCED(src);
		UNREFERENCED(_hoops_PCAP);
	}
	H3DACTION( void _hoops_PHPRR (bool mode) )
	{
		_hoops_GIHGR;
		UNREFERENCED(mode);
	}
	H3DACTION( void _hoops_IHPRR (int mask) )
	{
		_hoops_GIHGR;
		UNREFERENCED(mask);
	}
	H3DACTION( void _hoops_CCHC (H3DCULL mode) )
	{
		_hoops_GIHGR;
		UNREFERENCED(mode);
	}
	H3DACTION( void _hoops_CHPRR (bool mode) )
	{
		_hoops_GIHGR;
		UNREFERENCED(mode);
	}
	H3DACTION( void _hoops_GIPRR (float _hoops_RICR, float _hoops_AICR) )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_RICR);
		UNREFERENCED(_hoops_AICR);
	}
	H3DACTION( void _hoops_HIPRR (Net_Rendition const & nr, bool mode) )
	{
		_hoops_GIHGR;
		UNREFERENCED(nr);
		UNREFERENCED(mode);
	}
	H3DACTION( void _hoops_RSCR (
		int _hoops_GRRA,
		H3DTEXTUREFILTERTYPE filter,
		H3DTEXTUREFILTERTYPE _hoops_PHHRR,
		H3DTEXTUREADDRESS _hoops_HHHRR) )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_GRRA);
		UNREFERENCED(filter);
		UNREFERENCED(_hoops_PHHRR);
		UNREFERENCED(_hoops_HHHRR);
	}
	H3DACTION( void _hoops_GCPRR (bool mode) )
	{
		_hoops_GIHGR;
		UNREFERENCED(mode);
	}
	H3DACTION( void _hoops_SCPRR(int _hoops_PCPRR, int _hoops_HCPRR, int _hoops_ICPRR, int _hoops_CCPRR) )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_PCPRR);
		UNREFERENCED(_hoops_HCPRR);
		UNREFERENCED(_hoops_ICPRR);
		UNREFERENCED(_hoops_CCPRR);
	}
	H3DACTION( void _hoops_CIPRR (H3DSHADEMODE mode) )
	{
		_hoops_GIHGR;
		UNREFERENCED(mode);
	}
	H3DACTION( void _hoops_RSPRR (bool mode) )
	{
		_hoops_GIHGR;
		UNREFERENCED(mode);
	}
	H3DACTION( void _hoops_PSPRR (int _hoops_RHIA, H3DTexture *texture) )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_RHIA);
		UNREFERENCED(texture);
	}
	H3DACTION( void _hoops_AGSRR (int _hoops_RHIA, H3DTexture *texture) )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_RHIA);
		UNREFERENCED(texture);
	}
	H3DACTION( void _hoops_CRHRR(H3DCMPFUNC cmp) )
	{
		_hoops_GIHGR;
		UNREFERENCED(cmp);
	}
	H3DACTION( void _hoops_CGHRR(int _hoops_HAGR) )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_HAGR);
	}
	H3DACTION( void _hoops_PRHRR(int _hoops_HAGR) )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_HAGR);
	}
	H3DACTION( void _hoops_GRHRR(int _hoops_HAGR) )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_HAGR);
	}
	H3DACTION( void _hoops_AAHRR(H3DSTENCILOP _hoops_AAIS, H3DSTENCILOP _hoops_RAHRR, H3DSTENCILOP pass) )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_AAIS);
		UNREFERENCED(_hoops_RAHRR);
		UNREFERENCED(pass);
	}
	H3DACTION( void _hoops_IAHRR(H3DCMPFUNC cmp, unsigned long ref, unsigned long mask, unsigned long _hoops_HAHRR) )
	{
		_hoops_GIHGR;
		UNREFERENCED(cmp);
		UNREFERENCED(ref);
		UNREFERENCED(mask);
		UNREFERENCED(_hoops_HAHRR);
	}
	H3DACTION( void _hoops_CSPRR (bool mode) )
	{
		_hoops_GIHGR;
		UNREFERENCED(mode);
	}
	H3DACTION( void _hoops_IPPRR (H3DVertexFormat _hoops_PPCP) )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_PPCP);
	}
	H3DACTION( void _hoops_GGHRR (bool mode) )
	{
		_hoops_GIHGR;
		UNREFERENCED(mode);
	}
	H3DACTION( void _hoops_PGHRR (bool _hoops_AGHRR, float _hoops_CCGH, float _hoops_ICGH) )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_AGHRR);
		UNREFERENCED(_hoops_CCGH);
		UNREFERENCED(_hoops_ICGH);
	}


	// _hoops_PGHGR _hoops_PGSRR
	H3DACTION( void * _hoops_PRHGR(_hoops_AHGR type, const char *source) )
	{
		_hoops_GIHGR;
		UNREFERENCED(type);
		UNREFERENCED(source);
		return null;
	}

	H3DACTION( void _hoops_IRHGR(POINTER_SIZED_INT _hoops_RSR) )
	{
		_hoops_GIHGR;
		UNREFERENCED(_hoops_RSR);
	}

	H3DACTION( bool _hoops_SRHGR(_hoops_AHGR type, POINTER_SIZED_INT _hoops_RSR) )
	{
		_hoops_GIHGR;
		UNREFERENCED(type);
		UNREFERENCED(_hoops_RSR);
		return false;
	}

	H3DACTION( void _hoops_RAHGR(_hoops_AHGR type, char const * name, int count, int *data) )
	{
		_hoops_GIHGR;
		UNREFERENCED(type);
		UNREFERENCED(name);
		UNREFERENCED(count);
		UNREFERENCED(data);
	}

	H3DACTION( void _hoops_PAHGR(_hoops_AHGR type, char const * name, int count, float *data) )
	{
		_hoops_GIHGR;
		UNREFERENCED(type);
		UNREFERENCED(name);
		UNREFERENCED(count);
		UNREFERENCED(data);
	}

	H3DACTION( void _hoops_IAHGR(_hoops_AHGR type, char const * name, int width, int count, float *data) )
	{
		_hoops_GIHGR;
		UNREFERENCED(type);
		UNREFERENCED(name);
		UNREFERENCED(width);
		UNREFERENCED(count);
		UNREFERENCED(data);
	}

	H3DACTION( void _hoops_SAHGR(_hoops_AHGR type, char const * name, int count, float *data) )
	{
		_hoops_GIHGR;
		UNREFERENCED(type);
		UNREFERENCED(name);
		UNREFERENCED(count);
		UNREFERENCED(data);
	}

	H3DACTION( void _hoops_RPHGR(Net_Rendition const &nr, float *matrix) )
	{
		_hoops_HHCR const &_hoops_IHCR = nr->transform_rendition;
		float _hoops_HGSRR[16];

		HI_Copy_43 (&_hoops_IHCR->_hoops_SPH->_hoops_PRPA.elements[0][0],
					_hoops_HGSRR);

		/* _hoops_AA _hoops_RH _hoops_RSSP _hoops_AGRP _hoops_PPR _hoops_RH _hoops_SARA _hoops_HICH (0 _hoops_IS -5) */
		_hoops_HGSRR[2] *= _hoops_ISS->_hoops_ACCR;
		_hoops_HGSRR[6] *= _hoops_ISS->_hoops_ACCR;
		_hoops_HGSRR[10] *= _hoops_ISS->_hoops_ACCR;
		_hoops_HGSRR[14] *= _hoops_ISS->_hoops_ACCR;

		if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH)
			_hoops_HGSRR[14] += _hoops_ISS->_hoops_ACCR * _hoops_IHCR->_hoops_SPH->_hoops_SRIR;


		_hoops_ISS->_hoops_IICH =
			!ANYBIT (_hoops_IHCR->_hoops_IPH->data._hoops_RAGR,
					 _hoops_CICH);

		if (!_hoops_ISS->_hoops_IICH) {
			HI_Matmul_44_by_44 (&_hoops_IHCR->_hoops_IPH->data.elements[0][0],
				_hoops_HGSRR, matrix);

			/*_hoops_RPP (_hoops_CPSP->_hoops_SICH->_hoops_GCCH == _hoops_RCCH (0) &&
			(_hoops_ACCH || _hoops_PCCH)) {
			_hoops_HCCH (_hoops_RCCGR->_hoops_GSGA);
			}*/
		}
		else {
			/* _hoops_SGH _hoops_ICCH _hoops_RSGA _hoops_RIIA _hoops_IIGR _hoops_GSGA _hoops_PPR _hoops_SRCH _hoops_CCCH */
			_hoops_AIGA(_hoops_HGSRR, 16, float, matrix);
		}
	}

	H3DACTION( void _hoops_HPHGR(Net_Rendition const &nr, float *matrix) )
	{
		_hoops_HHCR const &_hoops_IHCR = nr->transform_rendition;
		_hoops_CGRA const &_hoops_SGRA = nr->_hoops_SAIR;
		if (!matrix)
			return;

		float _hoops_PIIH, _hoops_HIIH;
		float _hoops_ISIH;

		_hoops_PIIH = _hoops_HIIH = 1.0f;
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

		if (BIT (_hoops_IHCR->flags, _hoops_PGCH))
			_hoops_PIIH = -_hoops_PIIH;

		if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH) {
			float _hoops_SHCR = _hoops_CHCR * _hoops_IHCR->_hoops_SPH->_hoops_SRIR;
			float _hoops_GICR;

			// _hoops_SGCH '_hoops_SGIP _hoops_CRGR _hoops_RH _hoops_GIRA'
			_hoops_GICR = _hoops_IHCR->_hoops_SPH->_hoops_SRIR + (_hoops_IHCR->_hoops_SPH->_hoops_SRIR)*1000.0f;

			H3DMatrixPerspectiveLH(
				matrix,
				(_hoops_IHCR->_hoops_SPH->_hoops_ISPA*_hoops_PIIH)*_hoops_CHCR,
				(_hoops_IHCR->_hoops_SPH->_hoops_SSPA*_hoops_HIIH)*_hoops_CHCR,
				_hoops_SHCR, _hoops_GICR,
				_hoops_ISS->_hoops_ACCR
			);

			_hoops_ISS->_hoops_SIRA = _hoops_GICR;
			_hoops_ISS->_hoops_GCRA = _hoops_SHCR;
		}
		else {
			/* _hoops_ARCH _hoops_PPR _hoops_CIHP */
			float _hoops_SHCR = -_hoops_IHCR->_hoops_SPH->_hoops_SRIR;
			float _hoops_GICR = _hoops_IHCR->_hoops_SPH->_hoops_SRIR;

			/* _hoops_HSRR _hoops_RCAR _hoops_ACAR, _hoops_SR _hoops_ACPA _hoops_RH _hoops_CHRA _hoops_PRCH _hoops_RH _hoops_HIRA _hoops_HRCH, _hoops_HIS
			   _hoops_GA'_hoops_RA _hoops_IRCH _hoops_SCH _hoops_PAR _hoops_SR _hoops_GRS _hoops_CRCH _hoops_HCH _hoops_RAAA. */
			if ( !_hoops_ISS->_hoops_PI.mode ) {
				_hoops_SHCR /= _hoops_IHCR->_hoops_CHCR;
				_hoops_GICR /= _hoops_IHCR->_hoops_CHCR;
			}
			else {
				/* _hoops_AIAP _hoops_RPHR-_hoops_IGCH _hoops_RRR _hoops_RHC _hoops_GC _hoops_ARI _hoops_IS _hoops_SRCH _hoops_GACH _hoops_CCA _hoops_SCH _hoops_GGR _hoops_APR _hoops_HGSR. */
				_hoops_PIIH = _hoops_HIIH = 1;
			}

			_hoops_ISS->_hoops_SIRA = _hoops_GICR;
			_hoops_ISS->_hoops_GCRA = _hoops_SHCR;

			H3DMatrixOrthoLH(
				matrix,
				_hoops_IHCR->_hoops_SPH->_hoops_ISPA*_hoops_PIIH,
				_hoops_IHCR->_hoops_SPH->_hoops_SSPA*_hoops_HIIH,
				_hoops_SHCR, _hoops_GICR,
				_hoops_ISS->_hoops_ACCR);
		}
	}

	H3DACTION( void * _hoops_CPHGR() )
	{
		_hoops_GIHGR;
		return null;
	}

#undef H3DACTION

	void _hoops_IGSRR(H3DData *h3ddata)
	{
		while (h3ddata->glyph_textures) {
			// _hoops_CGSRR
			_hoops_IARS *remove = h3ddata->glyph_textures;
			h3ddata->glyph_textures = h3ddata->glyph_textures->next;

			// _hoops_SP _hoops_GH
			_hoops_HP(remove->texture);
			FREE(remove, _hoops_IARS);
		}
	}

	void _hoops_SGSRR(Display_Context alter * dc)
	{
		H3DData *h3ddata = H3DD(dc);
		int i = 0;

		/* _hoops_AIAP _hoops_ASAR-_hoops_ARP-_hoops_GH _hoops_IIGR _hoops_HSGRR _hoops_CCH */
		h3ddata->_hoops_CRAP = _hoops_SGGRR;
		h3ddata->_hoops_ISGRR = -1;
		h3ddata->_hoops_CSGRR = -1;

		// _hoops_SP _hoops_GH _hoops_GRSRR
		if (h3ddata->_hoops_HIRRR) {
			h3ddata->_hoops_HIRRR->DeleteItems();
			_hoops_HP(h3ddata->_hoops_HIRRR);
		}

		if (h3ddata->_hoops_ACAH) {
			h3ddata->_hoops_ACAH->DeleteItems();
			_hoops_HP(h3ddata->_hoops_ACAH);
		}

		_hoops_IGSRR(h3ddata);

		_hoops_HP(h3ddata->_hoops_IP);

		if (h3ddata->_hoops_RCAH) {
			h3ddata->_hoops_RCAH->DeleteItems();
			_hoops_HP(h3ddata->_hoops_RCAH);
		}

		if (h3ddata->_hoops_GIPGR) {
			h3ddata->_hoops_GSCR->_hoops_ISPGR(dc, h3ddata->_hoops_GIPGR, h3ddata->_hoops_AIPGR);
			h3ddata->_hoops_GIPGR = null;
			h3ddata->_hoops_AIPGR = null;
		}

		_hoops_HP(h3ddata->_hoops_CSSH);
		_hoops_HP(h3ddata->_hoops_ACHC);

		if (h3ddata->_hoops_PSRRR)
			FREE_ARRAY(h3ddata->_hoops_PSRRR, h3ddata->_hoops_HSRRR, short);
		h3ddata->_hoops_PSRRR = null;
		h3ddata->_hoops_HSRRR = 0;

		if (h3ddata->_hoops_CSRRR)
			FREE_ARRAY(h3ddata->_hoops_ISRRR, h3ddata->_hoops_CSRRR, int);
		h3ddata->_hoops_ISRRR = null;
		h3ddata->_hoops_CSRRR = 0;

		if (h3ddata->_hoops_GGARR) {
			FREE_ARRAY(h3ddata->_hoops_GGARR, h3ddata->_hoops_RGARR, _hoops_ARPA);
			FREE_ARRAY(h3ddata->_hoops_AGARR, h3ddata->_hoops_RGARR, Vector);
		}
		h3ddata->_hoops_GGARR = null;
		h3ddata->_hoops_AGARR = null;
		h3ddata->_hoops_RGARR = 0;

		if (h3ddata->_hoops_IIHS) 
			FREE_ARRAY (h3ddata->_hoops_IIHS, h3ddata->_hoops_HIHS, Test);
		h3ddata->_hoops_IIHS = null;
		h3ddata->_hoops_HIHS = 0;

		_hoops_HP(h3ddata->_hoops_HSI.texture);
		h3ddata->_hoops_HSI.valid = false;

		_hoops_HP(h3ddata->glyphs._hoops_CHRRR);
		h3ddata->glyphs.valid = false;

		if (h3ddata->_hoops_HSI.data) {
			FREE_ARRAY(h3ddata->_hoops_HSI.data, 4*h3ddata->_hoops_HSI.data_size, unsigned char);
			h3ddata->_hoops_HSI.data = null;
			h3ddata->_hoops_HSI.data_size = 0;
		}

		for (i = 0; i < 128; i++)
			_hoops_HP(h3ddata->_hoops_SRPH[i]);
		_hoops_HP(h3ddata->_hoops_ISAH);
		if (h3ddata->_hoops_GCCP)
			delete h3ddata->_hoops_GCCP;
		h3ddata->_hoops_GCCP = null;
		h3ddata->_hoops_GGPH = 0;

		_hoops_HP(h3ddata->_hoops_PI.depth_buffer);
		_hoops_HP(h3ddata->_hoops_PI.dummy_buffer);
		_hoops_HP(h3ddata->_hoops_PI._hoops_HI);
		h3ddata->_hoops_PI._hoops_HAP = 0;

		_hoops_HP(h3ddata->_hoops_II.depth_measure_target);
		_hoops_HP(h3ddata->_hoops_II.depth_measure_pattern);

		/* _hoops_SP _hoops_GH _hoops_GII _hoops_RRSRR _hoops_SR _hoops_PSPP */
		for (i = 0 ; i < _hoops_APRRR ; i++) {
			_hoops_HP(h3ddata->_hoops_RHH._hoops_IPRRR[i]);
			_hoops_HP(h3ddata->_hoops_RHH._hoops_CPRRR[i]);
		}
	}

};



/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_ARSRR

*****************************************************************************
*****************************************************************************/

static inline void _hoops_PRSRR (
		H3DData *h3ddata,
		Net_Rendition const &nr,
		int geom_type,
		void const *geom,
		int count,
		unsigned Integer32 flags,
		unsigned Integer32 _hoops_RCHA,
		H3DShader **_hoops_HRSRR)  
{
	H3DShader *_hoops_RSR = null; 
	H3DShaderID id; 
	H3DShaderID *_hoops_IRSRR; /* _hoops_SIGR _hoops_IH _hoops_CI _hoops_CRSRR _hoops_SRSRR */ 
	h3ddata->_hoops_CRARR = h3ddata->_hoops_GAARR; 
	h3ddata->_hoops_SRARR = h3ddata->_hoops_RAARR; 
	h3ddata->_hoops_GAARR = 0; 
	h3ddata->_hoops_RAARR = 0; 
	_hoops_GASRR(nr, h3ddata->_hoops_CSS, geom_type, _hoops_RCHA, (void *)geom); 
	if (!h3ddata->_hoops_IP) 
		h3ddata->_hoops_IP = NEW(H3DShaderHASH)(h3ddata); 
	if (h3ddata->_hoops_GAARR && h3ddata->_hoops_RAARR) { 
		/* _hoops_RASRR _hoops_CI */ 
		H3DShaderID _hoops_AASRR; 
		_hoops_AASRR._hoops_PASRR(h3ddata->_hoops_GAARR, h3ddata->_hoops_RAARR); 
		_hoops_RSR = h3ddata->_hoops_IP->Lookup (_hoops_AASRR); 
	} 
	if (!_hoops_RSR) { 
		/* _hoops_HASRR _hoops_CI */ 
		_hoops_IRSRR = id._hoops_IRA (nr, geom_type, geom, count, flags, _hoops_RCHA); 
		_hoops_RSR = h3ddata->_hoops_IP->Lookup (*_hoops_IRSRR);  
		if (!_hoops_RSR) { 
			const char *_hoops_IASRR = null;
			_hoops_RSR = h3ddata->_hoops_GSCR->_hoops_ICCRR(*_hoops_IRSRR);
			if (id._hoops_SHC()) {
				_hoops_IASRR = id._hoops_CAI (nr);
			}
			if (!_hoops_RSR->Create(h3ddata, _hoops_IASRR)) {
				/* _hoops_CI _hoops_CASRR _hoops_RIHH.  _hoops_SASRR _hoops_GPSRR _hoops_AIAH _hoops_RHHS */ 
				delete _hoops_RSR; 
				Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
				dc->flags &= ~_hoops_RPSRR;
				HD_Interrupt_Update (dc, true, false); 
				_hoops_APSRR(nr->_hoops_SRA, "shader compile error","", 0); 
				*_hoops_HRSRR = null;
				return; 
			} 
			h3ddata->_hoops_IP->Insert (*_hoops_IRSRR, _hoops_RSR);  
		} 
	} 
	if (h3ddata->_hoops_CSC->_hoops_AGSA != _hoops_RSR) {
		_hoops_RSR->_hoops_HHIH(); 
		h3ddata->_hoops_CSC->_hoops_AGSA = _hoops_RSR; 
		SET_MEMORY(h3ddata->_hoops_RRRA, H3D_MAX_TEXTURES * sizeof(bool), true); 
	} 
	*(_hoops_HRSRR) = h3ddata->_hoops_CSC->_hoops_AGSA; 
}


#define _hoops_HHHS(h3ddata,nr,geom_type,geom,count,flags,_hoops_RCHA,_hoops_HRSRR) _hoops_GHIA( \
	_hoops_PRSRR(h3ddata,nr,geom_type,geom,count,flags,_hoops_RCHA,_hoops_HRSRR); \
	if (*_hoops_HRSRR == null) \
		return;	\
)

#define _hoops_CSIC(h3ddata,nr,geom_type,geom,flags,_hoops_RCHA,_hoops_HRSRR) _hoops_GHIA( \
	_hoops_PRSRR(h3ddata,nr,geom_type,geom,0,flags,_hoops_RCHA,_hoops_HRSRR); \
	if (*_hoops_HRSRR == null) \
		return;	\
)

#define _hoops_CPHC(h3ddata,nr,geom_type,geom,count,flags,_hoops_HRSRR) _hoops_GHIA( \
	_hoops_PRSRR(h3ddata,nr,geom_type,geom,count,flags,0,_hoops_HRSRR); \
	if (*_hoops_HRSRR == null) \
		return;	\
)

#define _hoops_SSHH(h3ddata,nr,geom_type,geom,flags,_hoops_HRSRR) _hoops_GHIA( \
	_hoops_CSIC(h3ddata,nr,geom_type,geom,flags,0,	_hoops_HRSRR); \
	if (*_hoops_HRSRR == null) \
		return;	\
)


/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_PPSRR _hoops_HPSRR _hoops_GCGH

*****************************************************************************
*****************************************************************************/

#ifdef _DEBUG

// _hoops_SACA: _hoops_IPSRR _hoops_GPP _hoops_CPSRR _hoops_RARP _hoops_PPR _hoops_RIARR. _hoops_SGPR _hoops_RH _hoops_SPSRR _hoops_RIGR _hoops_CAPP.
class _hoops_GHSRR
{
public:
	_hoops_GHSRR( H3DData *h3ddata, wchar_t const *_hoops_RHSRR ) : _hoops_ISS(h3ddata), _hoops_AHSRR(_hoops_RHSRR)
	{
		if ( _hoops_ISS && _hoops_ISS->_hoops_GSCR )
			_hoops_ISS->_hoops_GSCR->_hoops_ASCRR(_hoops_RHSRR);
	}

	~_hoops_GHSRR()
	{
		if ( _hoops_ISS && _hoops_ISS->_hoops_GSCR )
			_hoops_ISS->_hoops_GSCR->_hoops_PSCRR(_hoops_AHSRR);
	}

private:

	H3DData *_hoops_ISS;
	const wchar_t *_hoops_AHSRR;
};


#define H3D_TRACE(h3ddata, string) _hoops_GHSRR _hoops_PHSRR##__LINE__((h3ddata), (L##string));
#else
#define H3D_TRACE(h3ddata, string) UNREFERENCED(h3ddata)
#endif

/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_HHSRR
*****************************************************************************
*****************************************************************************/

struct concave_tri
{
	H3DData alter *h3ddata;
	bool _hoops_RPPH;
	union {
		DC_Point const *dc;
		Point const *_hoops_GSPH;
	} points;
	union {
		H3DVertexBuffer *_hoops_HPPH;				//_hoops_IHSRR*	_hoops_CHSRR;
		H3DVertexBuffer *_hoops_SPPH;			//_hoops_SHSRR*		_hoops_GISRR;
	};
	float normal[3];
	Driver_Color color;
	int _hoops_APPH;
	int _hoops_PPPH;
	void (*_hoops_PSPH) (void alter * info,
						   Integer32 _hoops_HAPH,
						   Point const * p1,
						   Point const * p2,
						   Point const * _hoops_IAPH,
						   Integer32 _hoops_ISPI,
						   Integer32 _hoops_CSPI,
						   Integer32 _hoops_SSPI,
						   Intersection const * i1,
						   Intersection const * i2,
						   Intersection const * _hoops_SAPH);
};

/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_CGHA _hoops_SGHA
*****************************************************************************
*****************************************************************************/

//_hoops_CPAP _hoops_ASIRR _hoops_SIH
#define	_hoops_ACHA			0x00000001
#define	_hoops_RISRR			0x00000002
#define	_hoops_CAA			0x00000004
#define	_hoops_RSP			0x00000008
#define	_hoops_HGP			0x00000010
#define	_hoops_HSA			0x00000020
#define	_hoops_SCHA			0x00000040
#define	_hoops_PIA		0x00000080
#define	_hoops_PGP				0x00000100
#define	_hoops_ISA			0x00000200
#define	_hoops_IGP		0x00000400
#define	_hoops_SIP			0x00000800
#define	_hoops_HCP				0x00001000


/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_GRAR _hoops_AISRR _hoops_PISRR
*****************************************************************************
*****************************************************************************/
#define _hoops_HISRR						-1		//_hoops_IGI _hoops_RGAR _hoops_IS _hoops_SHI _hoops_RH _hoops_IPI _hoops_IISRR
#define _hoops_CISRR						0
#define _hoops_PSRR				1
#define _hoops_PPAR				2
#define _hoops_CAAR			3
#define _hoops_GHPR			4
#define _hoops_PIPR				5
#define _hoops_CCRR					6
#define _hoops_RIAR		7
#define _hoops_IAAR				8
#define _hoops_RIPR			9
#define _hoops_CIPR		10
#define _hoops_APAR					11
#define _hoops_RHRR				12
#define _hoops_HCRR						13
#define _hoops_RCPR						14
#define _hoops_HIRR					15		//_hoops_IH _hoops_III _hoops_PAIA
#define _hoops_CHRR			16
#define _hoops_IHRR				17
#define _hoops_SHRR					18
#define _hoops_PIRR					19		//_hoops_IH _hoops_GIRR _hoops_PAR _hoops_ARHP _hoops_APGR
#define _hoops_ACPR				20

#define _hoops_IRAR			21
#define _hoops_RPAR				22
#define _hoops_HPAR			23
#define _hoops_CPAR				24

#define _hoops_PHIA			0xffff

typedef struct _hoops_SISRR {
	char _hoops_CCI;
	char _hoops_GGC;
	char _hoops_ASI;
	char _hoops_RSI;
	char _hoops_HSI;
	char _hoops_PGC;
	bool _hoops_RGC;
	char _hoops_IGC;
	char _hoops_SGC;
	char _hoops_RRC;
	char _hoops_RAC;
	char _hoops_PRC;
	char _hoops_IRC;
	char _hoops_SRC;
	char _hoops_PAC;
	char _hoops_HAC;
	char _hoops_CAC;
	char _hoops_GPC;
	char _hoops_PPC;
	char _hoops_CPC;
	char marker;
	char _hoops_GIC;
	char _hoops_AIC;
	char _hoops_HIC;
} _hoops_HCI;


/* _hoops_RGR _hoops_GASR _hoops_CGH _hoops_SHH _hoops_SAHR 520 _hoops_GCSRR, _hoops_HIS _hoops_SCH _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_GSGS _hoops_IIGR _hoops_IRS _hoops_IGIR _hoops_RCSRR */
static const unsigned char _hoops_HRPH[65][8] = {
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	{0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	{0x0, 0x80, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0},
	{0x0, 0x80, 0x0, 0x0, 0x0, 0x88, 0x0, 0x0},
	{0x0, 0x88, 0x0, 0x0, 0x0, 0x88, 0x0, 0x0},
	{0x0, 0x88, 0x0, 0x20, 0x0, 0x88, 0x0, 0x0},
	{0x0, 0x88, 0x0, 0x20, 0x0, 0x88, 0x0, 0x2},
	{0x0, 0x88, 0x0, 0x20, 0x0, 0x88, 0x0, 0x22},
	{0x0, 0x88, 0x0, 0x22, 0x0, 0x88, 0x0, 0x22},
	{0x0, 0x88, 0x0, 0xa2, 0x0, 0x88, 0x0, 0x22},
	{0x0, 0x88, 0x0, 0xa2, 0x0, 0x88, 0x0, 0x2a},
	{0x0, 0x88, 0x0, 0xa2, 0x0, 0x88, 0x0, 0xaa},
	{0x0, 0x88, 0x0, 0xaa, 0x0, 0x88, 0x0, 0xaa},
	{0x0, 0xa8, 0x0, 0xaa, 0x0, 0x88, 0x0, 0xaa},
	{0x0, 0xa8, 0x0, 0xaa, 0x0, 0x8a, 0x0, 0xaa},
	{0x0, 0xa8, 0x0, 0xaa, 0x0, 0xaa, 0x0, 0xaa},
	{0x0, 0xaa, 0x0, 0xaa, 0x0, 0xaa, 0x0, 0xaa},
	{0x40, 0xaa, 0x0, 0xaa, 0x0, 0xaa, 0x0, 0xaa},
	{0x40, 0xaa, 0x0, 0xaa, 0x4, 0xaa, 0x0, 0xaa},
	{0x40, 0xaa, 0x0, 0xaa, 0x44, 0xaa, 0x0, 0xaa},
	{0x44, 0xaa, 0x0, 0xaa, 0x44, 0xaa, 0x0, 0xaa},
	{0x44, 0xaa, 0x10, 0xaa, 0x44, 0xaa, 0x0, 0xaa},
	{0x44, 0xaa, 0x10, 0xaa, 0x44, 0xaa, 0x1, 0xaa},
	{0x44, 0xaa, 0x10, 0xaa, 0x44, 0xaa, 0x11, 0xaa},
	{0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0xaa},
	{0x44, 0xaa, 0x51, 0xaa, 0x44, 0xaa, 0x11, 0xaa},
	{0x44, 0xaa, 0x51, 0xaa, 0x44, 0xaa, 0x15, 0xaa},
	{0x44, 0xaa, 0x51, 0xaa, 0x44, 0xaa, 0x55, 0xaa},
	{0x44, 0xaa, 0x55, 0xaa, 0x44, 0xaa, 0x55, 0xaa},
	{0x54, 0xaa, 0x55, 0xaa, 0x44, 0xaa, 0x55, 0xaa},
	{0x54, 0xaa, 0x55, 0xaa, 0x45, 0xaa, 0x55, 0xaa},
	{0x54, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa},
	{0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa},
	{0xd5, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa},
	{0xd5, 0xaa, 0x55, 0xaa, 0x5d, 0xaa, 0x55, 0xaa},
	{0xd5, 0xaa, 0x55, 0xaa, 0xdd, 0xaa, 0x55, 0xaa},
	{0xdd, 0xaa, 0x55, 0xaa, 0xdd, 0xaa, 0x55, 0xaa},
	{0xdd, 0xaa, 0x75, 0xaa, 0xdd, 0xaa, 0x55, 0xaa},
	{0xdd, 0xaa, 0x75, 0xaa, 0xdd, 0xaa, 0x57, 0xaa},
	{0xdd, 0xaa, 0x75, 0xaa, 0xdd, 0xaa, 0x77, 0xaa},
	{0xdd, 0xaa, 0x77, 0xaa, 0xdd, 0xaa, 0x77, 0xaa},
	{0xdd, 0xaa, 0xf7, 0xaa, 0xdd, 0xaa, 0x77, 0xaa},
	{0xdd, 0xaa, 0xf7, 0xaa, 0xdd, 0xaa, 0x7f, 0xaa},
	{0xdd, 0xaa, 0xf7, 0xaa, 0xdd, 0xaa, 0xff, 0xaa},
	{0xdd, 0xaa, 0xff, 0xaa, 0xdd, 0xaa, 0xff, 0xaa},
	{0xfd, 0xaa, 0xff, 0xaa, 0xdd, 0xaa, 0xff, 0xaa},
	{0xfd, 0xaa, 0xff, 0xaa, 0xdf, 0xaa, 0xff, 0xaa},
	{0xfd, 0xaa, 0xff, 0xaa, 0xff, 0xaa, 0xff, 0xaa},
	{0xff, 0xaa, 0xff, 0xaa, 0xff, 0xaa, 0xff, 0xaa},
	{0xff, 0xea, 0xff, 0xaa, 0xff, 0xaa, 0xff, 0xaa},
	{0xff, 0xea, 0xff, 0xaa, 0xff, 0xae, 0xff, 0xaa},
	{0xff, 0xea, 0xff, 0xaa, 0xff, 0xee, 0xff, 0xaa},
	{0xff, 0xee, 0xff, 0xaa, 0xff, 0xee, 0xff, 0xaa},
	{0xff, 0xee, 0xff, 0xba, 0xff, 0xee, 0xff, 0xaa},
	{0xff, 0xee, 0xff, 0xba, 0xff, 0xee, 0xff, 0xab},
	{0xff, 0xee, 0xff, 0xba, 0xff, 0xee, 0xff, 0xbb},
	{0xff, 0xee, 0xff, 0xbb, 0xff, 0xee, 0xff, 0xbb},
	{0xff, 0xee, 0xff, 0xfb, 0xff, 0xee, 0xff, 0xbb},
	{0xff, 0xee, 0xff, 0xfb, 0xff, 0xee, 0xff, 0xbf},
	{0xff, 0xee, 0xff, 0xfb, 0xff, 0xee, 0xff, 0xff},
	{0xff, 0xee, 0xff, 0xff, 0xff, 0xee, 0xff, 0xff},
	{0xff, 0xfe, 0xff, 0xff, 0xff, 0xee, 0xff, 0xff},
	{0xff, 0xfe, 0xff, 0xff, 0xff, 0xef, 0xff, 0xff},
	{0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
	{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}
};


/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_CACA _hoops_SACA _hoops_GPCA
*****************************************************************************
*****************************************************************************/

bool _hoops_RRPA(Net_Rendition const &nr, _hoops_ARPA const *in, _hoops_ARPA	*_hoops_PAGR);

/**
 * _hoops_PGAA
 *
 * _hoops_ICGP _hoops_GAPA _hoops_CIGC _hoops_PPR _hoops_RRH _hoops_HPPA _hoops_GHC, _hoops_ISPR _hoops_ACSRR _hoops_RHPP _hoops_PCSRR, _hoops_PPR _hoops_PRPS
 * _hoops_IGH _hoops_PAR _hoops_HAR _hoops_RGR _hoops_CHCA _hoops_CGH _hoops_SHH _hoops_HCSRR.
 *
 * _hoops_CGP _hoops_RH _hoops_API _hoops_HRS _hoops_RCPP, _hoops_CAH _hoops_RH _hoops_CHCA (_hoops_PSHRR _hoops_SPR _hoops_IIGR _hoops_RH _hoops_ICSRR _hoops_PSCH).
 * _hoops_CGP _hoops_RH _hoops_API _hoops_HRS _hoops_IHPR, _hoops_SGH _hoops_RH _hoops_PCCC _hoops_GGR _hoops_RH _hoops_CCSRR _hoops_RHPC - _hoops_RGR _hoops_HHS _hoops_SHH _hoops_IRAP _hoops_RPP
 * _hoops_IIH _hoops_CHR _hoops_PSP _hoops_GHC _hoops_IS _hoops_SGH.
 */
bool _hoops_HPCA(
		Net_Rendition const & nr,
		_hoops_IAPA const *& _hoops_CAPA);


bool _hoops_HHCA(Tristrip const *ts, H3D_Display_List_Bin *_hoops_RRHA);

void _hoops_IHCA (H3DData alter * h3ddata);


/*
 * _hoops_PGAA
 * _hoops_RGPA _hoops_CHCA _hoops_PPR _hoops_RPR _hoops_IS _hoops_IRPR _hoops_SHCA _hoops_GCHA.
 */
void _hoops_GICA (
		H3DData const *h3ddata,
		int count,
		int _hoops_RICA,
		H3DPRIMITIVETYPE Type,
		int _hoops_AICA);

/*
 * _hoops_PGAA
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
		int _hoops_AICA = 0);

/* _hoops_GSCA _hoops_RH _hoops_RSCA _hoops_ASCA _hoops_HAPR _hoops_IH _hoops_HPPA _hoops_GHC _hoops_CCA _hoops_CIHA _hoops_PSCA.
 * _hoops_HSCA _hoops_ISCA _hoops_RH _hoops_PSHR _hoops_CSCA _hoops_APGR _hoops_IIGR _hoops_RRGR _hoops_HCR _hoops_IAPR.
 */
void _hoops_SGSA(
		H3DData alter *dx9data,
		Net_Rendition const & nr,
		H3DIndexBufferCache *_hoops_GRSA,
		_hoops_IAPA const *_hoops_CAPA,
		int _hoops_RRSA,
		int _hoops_RGSA,
		int _hoops_RICA,
		H3DPRIMITIVETYPE Type,
		int _hoops_AICA = 0,
		bool _hoops_ARSA = false);

H3DTexture *_hoops_SHSA (H3DData *h3ddata, int w, int h);

void _hoops_CAGP(H3DData *h3ddata, H3DRenderTarget *target, H3DTexture *depth_texture, bool opaque, bool scaled);
void _hoops_PIRP(H3DData *h3ddata, H3DTexture *_hoops_HIRP, H3DTexture *_hoops_IIRP);
bool _hoops_IGAP( H3DData *h3ddata, int _hoops_CGAP );
void _hoops_HSAP(Net_Rendition const &nr);

void _hoops_HGIP (
	   H3DData					*h3ddata,
	   H3DRenderTarget			*_hoops_SCSRR,
	   H3DRenderTarget			*_hoops_GSSRR,
	   H3DTEXTUREFILTERTYPE		filter = H3DTEXF_NONE,
	   bool						_hoops_RSSRR = false,
	   bool						_hoops_ASSRR = false);

bool _hoops_RHIP(
		Action_Mask mask,
		Geometry const *_hoops_RRA);

void _hoops_PACP (
		Net_Rendition const & nr,
		Polyedge const *pe,
		Line_Rendition const &_hoops_GHP,
		H3DVertexBuffer *_hoops_HACP,
		float _hoops_IACP,
		int _hoops_CACP,
		int _hoops_SACP,
		_hoops_HRPA const *matrix,
		RGB const *_hoops_GPCP,
		_hoops_HCI *_hoops_RPCP);

/* _hoops_HSCP _hoops_SGS _hoops_ISCP _hoops_RAPA _hoops_PIAP _hoops_SSCP _hoops_RH _hoops_GGSP _hoops_HRP _hoops_IH
 *	_hoops_IRS) _hoops_PGCR _hoops_RPSA _hoops_RCA,
 *	_hoops_RCSR) _hoops_RGSP _hoops_HSP
 */
void _hoops_AGSP (
		H3DData alter * h3ddata,
		_hoops_HHCR const & _hoops_IHCR,
		bool _hoops_PGSP);

/* _hoops_RAP _hoops_SIC _hoops_RRSP _hoops_PPR _hoops_GRH _hoops_CI _hoops_AAP. */
int _hoops_SRSP(
		H3DData *h3ddata,
		Net_Rendition const & nr,
		int type,
		bool _hoops_GASP,
		int _hoops_RASP,
		int flags);

/* _hoops_RAP _hoops_SIC _hoops_RRSP _hoops_PPR _hoops_GRH _hoops_CI _hoops_AAP. */
int _hoops_IISP(
		H3DData *h3ddata,
		Net_Rendition const & nr,
		H3D_Vertex_Buffer_Style _hoops_APHA,
		int type,
		bool _hoops_CISP,
		int _hoops_RASP,
		int flags);

int _hoops_CCSP(
		 Net_Rendition const & nr);

/* _hoops_HCGA _hoops_CI _hoops_HRP _hoops_IS _hoops_RH _hoops_CHIA _hoops_CI.*/
void _hoops_SSSP(
		H3DData *h3ddata,
		Net_Rendition const & nr,
		H3DShader *_hoops_RSR);

void _hoops_AGGH (
		H3DData alter *h3ddata,
		_hoops_HRPA const *mat,
		H3DShader alter *_hoops_RSR);

void _hoops_IGGH (
		H3DData alter *h3ddata,
		H3DShader alter *_hoops_RSR);


/* _hoops_PSSRR _hoops_AI _hoops_IS _hoops_CACH _hoops_RPP _hoops_SSIA _hoops_PAH _hoops_HSSRR _hoops_PCRR */
bool _hoops_ISR (Net_Rendition const &nr, _hoops_RCR const *_hoops_CGGH, _hoops_RCR const *_hoops_SGGH);

const char *_hoops_SCPR();


/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_SPGH
*****************************************************************************
*****************************************************************************/
H3DTexture * _hoops_PIGH (
		H3DData alter *h3ddata,
		Net_Rendition const &  nr,
		_hoops_RCR alter *txr,
		int _hoops_GCI);

H3DTexture * _hoops_GHAH (
		H3DData alter * dx9data,
		Net_Rendition const &  nr);

int _hoops_HSAH (
		Display_Context alter * dc,
		Line_Style const & style);

void _hoops_AGPH (
	Display_Context alter * dc,
	int _hoops_CRIA,
	int _hoops_PGPH,
	int _hoops_RASP = 0);


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
	Intersection const * _hoops_SAPH);


/* _hoops_SIGP: _hoops_AISA _hoops_GHPH _hoops_HRGR _hoops_RHPH _hoops_IH _hoops_AHPH _hoops_ARAR
 * _hoops_PAGA: _hoops_RGR _hoops_CSAP _hoops_PHPH _hoops_CCA _hoops_RH _hoops_GHPH _hoops_SGS _hoops_HHPH _hoops_HRGR _hoops_IHPH _hoops_PPR _hoops_SGS
 * _hoops_SCH _hoops_HRGR _hoops_CHPH _hoops_IS _hoops_AA _hoops_AHPH _hoops_HAIR _hoops_SHPH _hoops_GIPH _hoops_GHGA _hoops_GPGR _hoops_RIPH.	_hoops_HGI
 * _hoops_GHPH _hoops_GHCA _hoops_SHH _hoops_AIPH.  _hoops_PIPH _hoops_HIPH _hoops_IH _hoops_IIPH _hoops_CIPH!
 */
void draw_concave_face (Net_Rendition const &  nr,
				   int count, struct concave_tri const * _hoops_SIPH);

/* _hoops_RAGA _hoops_IRS _hoops_HSPH _hoops_ISPH _hoops_PAPR _hoops_GGR _hoops_CSPH, _hoops_PGSA _hoops_SSPH _hoops_SHS */
void _hoops_GGHH (Net_Rendition const & nr,
								  int count, struct concave_tri * _hoops_SIPH);

void _hoops_SGHH (
		Net_Rendition const & nr,
		Polygon const *polygon);


/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_RAP _hoops_CAHH
*****************************************************************************
*****************************************************************************/
void _hoops_SAHH (Net_Rendition const &  nr);

void _hoops_GIIH (Net_Rendition const &  nr);

/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_ASCH _hoops_PSCH
*****************************************************************************
*****************************************************************************/
void _hoops_ISCH( H3DData *h3ddata, H3DTexture *_hoops_GGIP, H3DRenderTarget *_hoops_CSCH );

/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_CPIP _hoops_ISSRR
*****************************************************************************
*****************************************************************************/
void _hoops_PPCI (
		Net_Rendition const & nr,
		_hoops_GACR *dl);

void _hoops_AICI(
		Net_Rendition const & nr,
		_hoops_GACR **_hoops_PICI,
		unsigned Integer32 *mask,
		unsigned Integer32 *_hoops_IICI);

bool _hoops_GGSI(
		Net_Rendition const & nr,
		_hoops_GACR **_hoops_PICI,
		unsigned Integer32 *mask,
		bool _hoops_IHGI);

void _hoops_AIGC(
		Net_Rendition const & nr,
		_hoops_GACR **_hoops_PICI,
		bool _hoops_IHGI);

local bool
_hoops_GSCI (
		Net_Rendition const & nr,
		_hoops_GACR const *dl,
		H3D_Display_List const *_hoops_CHGI,
		_hoops_ACHR alter *_hoops_HSHI,
		_hoops_ACHR alter *_hoops_IICI,
		_hoops_ACHR alter *_hoops_CICI);

bool _hoops_RPRC (
		Net_Rendition const & nr,
		Tristrip const *ts,
		_hoops_GACR const *dl,
		H3D_Display_List const *odl);

bool _hoops_APRC (
		Net_Rendition const & nr,
		Polyedge const *pe,
		_hoops_GACR const *dl,
		H3D_Display_List const *odl);

bool _hoops_SPRC (
		Net_Rendition const & nr,
		_hoops_ACHR _hoops_HRAI,
		_hoops_GACR const *dl,
		H3D_Display_List const *odl);

void _hoops_CSII (
		Net_Rendition const & nr,
		H3D_Display_List alter *odl);

void _hoops_SRCI (
		Net_Rendition const & nr,
		H3D_Display_List alter *odl,
		Line_Rendition const &_hoops_GHP);

void _hoops_HARI (
		Net_Rendition const & nr,
		H3D_Display_List_List alter *_hoops_AACI,
		bool _hoops_PACI,
		bool _hoops_HACI);

void _hoops_CGAI (
		Net_Rendition const & nr,
		H3D_Display_List alter *_hoops_CHGI,
		bool _hoops_PACI,
		bool _hoops_HACI);

void _hoops_CGPI (
		Net_Rendition const & nr,
		_hoops_ACHR type,
		H3D_Display_List_List alter *_hoops_AACI);

void _hoops_ICII (
		Net_Rendition const & nr,
		H3D_Display_List_List alter *_hoops_AACI,
		_hoops_ACHR _hoops_RGP);

void _hoops_HHPI (
		Net_Rendition const & nr,
		H3D_Display_List_List alter *_hoops_AACI);


/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_IRAC
*****************************************************************************
*****************************************************************************/
void draw_dc_rgb32_rasters (Net_Rendition const &  nr,
	   DC_Point const * start,
	   DC_Point const * end,
	   int row_bytes, RGBAS32 const * _hoops_GAAC);

void draw_dc_rectangle (
		Net_Rendition const & nr,
		int left,
		int right,
		int bottom,
		int top);

void draw_dc_gouraud_polyline (
		Net_Rendition const &  nr,
		int _hoops_CRHC,
		DC_Point const *_hoops_SRHC,
		RGBAS32 const *_hoops_GAHC);
void draw_dc_polyline (
		Net_Rendition const &  nr,
		int _hoops_CRHC,
		DC_Point const *_hoops_SRHC);

void _hoops_SRIC (
		Net_Rendition const &  nr,
		int count,
		DC_Point const * points,
		RGBAS32 const * colors,
		const int _hoops_GAIC);
void draw_dc_colorized_polytriangle (
		Net_Rendition const &  nr,
		int count,
		DC_Point const * points,
		RGBAS32 const * colors,
		bool single);
void draw_dc_polytriangle (
		Net_Rendition const &  nr,
		int count,
		DC_Point const * points);
void draw_dc_gouraud_polytriangle (
		Net_Rendition const & nr,
		int	count,
		DC_Point const *points,
		RGBAS32 const *colors);
void draw_dc_textured_polytriangle (
		Net_Rendition const &  nr,
		int count,
		DC_Point const * points,
		RGBA const * color,
		_hoops_ARPA const * planes,
		_hoops_RSSH const * params,
		Integer32 param_width,
		_hoops_SSIC param_flags);

void draw_dc_colorized_polydot (
		Net_Rendition const &  nr,
		int count,
		DC_Point const * points,
		RGBAS32 const * colors,
		bool single);
void draw_dc_polydot (
		Net_Rendition const &  nr,
		int count,
		DC_Point const * points);


void _hoops_PPAS (
		Net_Rendition const &  nr,
		Polyedge const *pe);

void draw_3d_marker (
		Net_Rendition const &  nr,
		Marker const *m);

void draw_3d_polymarker (
		Net_Rendition const &  nr,
		Polymarker const *pm);

void _hoops_GPCI (
		Net_Rendition const &  nr,
		Polymarker const *pm,
		_hoops_ICP const & _hoops_CCP,
		H3D_Display_List_Bin *_hoops_RRHA);

void draw_3d_text (
		Net_Rendition const &  nr,
		_hoops_HACC const *text);

void draw_3d_grid (
		Net_Rendition const &  nr,
		Grid const *grid);

void draw_3d_image(
		Net_Rendition const &  nr,
		Image const *image);

void _hoops_CPAS (
		Net_Rendition const &  nr,
		Polyedge const *pe,
		H3D_Display_List_Bin *_hoops_RRHA,
		Line_Rendition const &_hoops_GHP,
		H3D_Vertex_Buffer_Style _hoops_APHA,
		H3DVertexFormat _hoops_PPCP);

bool _hoops_HSRI (
		Net_Rendition const &nr,
		Line_Rendition const &_hoops_GHP,
		bool _hoops_AGPS,
		float weight);

void really_draw_3d_polyedge (
		Net_Rendition const &  nr,
		Polyedge const *pe,
		Line_Rendition const &_hoops_GHP,
		H3D_Display_List_Bin *_hoops_RRHA);

void draw_3d_polyedge (
		Net_Rendition const &  nr,
		Polyedge const *pe);

void draw_3d_polyline (
		Net_Rendition const &  nr,
		Polyline const *p);

bool _hoops_HGRI(
		Net_Rendition const & nr,
		unsigned Integer32 _hoops_SRHA,
		bool _hoops_CISP);

void _hoops_CRRI (
		Net_Rendition const &  nr,
		Tristrip const * ts,
		H3D_Display_List_Bin * _hoops_RRHA);

void _hoops_ARCI (
		Net_Rendition const &  nr,
		Tristrip const * ts);

void _hoops_ISRI (
		Net_Rendition const &  nr,
		Polyedge const * pe,
		H3D_Display_List_Bin * _hoops_RRHA);

void _hoops_PPAS(
		Net_Rendition const &  nr,
		Polyedge const * pe);

void _hoops_CSSRR(
		Net_Rendition const & nr,
		Tristrip const *ts,
		H3D_Display_List_Bin *_hoops_RRHA,
		_hoops_IAPA const *_hoops_CAPA,
		H3DVertexFormat _hoops_PPCP,
		H3D_Vertex_Buffer_Style _hoops_APHA,
		_hoops_HCI *_hoops_RPCP,
		int _hoops_RASP = 0);

void _hoops_SSSRR(
		Net_Rendition const & nr,
		Tristrip const *ts,
		H3D_Display_List_Bin *_hoops_RRHA,
		_hoops_IAPA const *_hoops_CAPA,
		H3DVertexFormat _hoops_PPCP,
		H3D_Vertex_Buffer_Style _hoops_APHA,
		_hoops_HCI *_hoops_RPCP,
		int _hoops_RASP = 0);

void _hoops_RRRI (
		Net_Rendition const &  nr,
		Tristrip const * ts,
		H3D_Display_List_Bin * _hoops_RRHA);

void draw_3d_tristrip (
		Net_Rendition const &  nr,
		Tristrip const * ts);

void draw_3d_polygon (
		Net_Rendition const & inr,
		Polygon const *polygon);

void draw_3d_ellipse (
		Net_Rendition const & nr,
		Ellipse const *e);

local void _hoops_CIII (
		Net_Rendition const & nr,
		Ellipse const *e);

void _hoops_PICS (
		Net_Rendition const & nr,
		_hoops_CRCP const * start,
		_hoops_HICS const & path) ;

void _hoops_IPSS (
		Net_Rendition const & inr,
		_hoops_CRCP const * start,
		_hoops_HICS const & path) ;

void _hoops_GHGGR (
		Net_Rendition const & nr,
		_hoops_CRCP const * start,
		_hoops_HICS const & path,
		float _hoops_IRIR,
		float radius);

/*****************************************************************************
*****************************************************************************
						_hoops_GR: _hoops_CPRGR
*****************************************************************************
*****************************************************************************/

//_hoops_GGGAR _hoops_ARI _hoops_HRGR _hoops_IRS _hoops_RSCA _hoops_RGGAR _hoops_HIS _hoops_SGS _hoops_SR _hoops_PAH _hoops_AGGAR _hoops_GIRP
// _hoops_PGGAR _hoops_HGGAR _hoops_ACPP.  _hoops_HHPC _hoops_SR'_hoops_GHGP _hoops_HS _hoops_IS
// _hoops_AASA _hoops_SCH _hoops_ARR _hoops_ARPP _hoops_IGGAR _hoops_PPR _hoops_GICS _hoops_IS _hoops_CAHP _hoops_RH _hoops_RSSA -- _hoops_PPR
// _hoops_SCH _hoops_PAH _hoops_HGCR _hoops_IS _hoops_SHH _hoops_CGGAR _hoops_IIGR _hoops_IHPH.
struct _hoops_CHRGR {
	Geometry const *g;
	Point *points;
	int _hoops_SGII; //_hoops_AAPA _hoops_ASCR _hoops_IH _hoops_GHCS
	int count;  //_hoops_RIHRR _hoops_RPR
	Type type;
	RGB const *_hoops_IGII;
};
struct _hoops_GSHI : public _hoops_CHRGR {
	_hoops_ARPA plane;
	RGB const *_hoops_CGII;
};

typedef VList<_hoops_CHRGR *> _hoops_HHRGR;
typedef VList<_hoops_GSHI *> _hoops_CCHI;


Polyedge alter *_hoops_RHRGR (
		Net_Rendition const & nr,
		Geometry const *_hoops_RSII,
		bool alter *_hoops_ARPI,
		bool single,
		RGB const *_hoops_PCRGR,
		bool _hoops_PHRGR);

/* _hoops_SPCP _hoops_GAR _hoops_SGGAR _hoops_GAR _hoops_SSRR _hoops_RH _hoops_PGPP _hoops_CPHR _hoops_GGR _hoops_GASGR */
local void _hoops_SAPI (
		Net_Rendition const &  nr,
		H3D_Display_List_Bin alter *_hoops_RRHA,
		H3D_Display_List_Bin_List alter *_hoops_IAPI,
		bool *_hoops_AHRGR,
		bool *_hoops_GCRGR,
		bool *_hoops_GRGAR);


/* _hoops_GCRR _hoops_IRS _hoops_RSPH _hoops_ACRI, _hoops_AISI _hoops_IRS _hoops_RAGA _hoops_CSRI _hoops_CRGR _hoops_SCH, _hoops_PPR _hoops_ASRC
 * _hoops_PCCP _hoops_CSRI _hoops_IIGR _hoops_GPRR _hoops_RRGAR _hoops_IS _hoops_ARGAR _hoops_SCH _hoops_GIRP _hoops_CCA
 * _hoops_HPHS _hoops_IS _hoops_CGIC _hoops_IGH _hoops_PAR _hoops_HAR _hoops_SCH _hoops_HRGR _hoops_HGGC _hoops_APIP */
H3D_Display_List *_hoops_PRGAR (
		Net_Rendition const & nr,
		H3D_Display_List alter *odl,
		bool _hoops_ARPI,
		H3D_Display_List_Bin const *_hoops_RRHA);

void _hoops_CAAGR (
		Net_Rendition const &  nr,
		int left,
		int right,
		int bottom,
		int top);

void _hoops_PHPI (
		Net_Rendition const &  nr,
		Geometry const * _hoops_RSII,
		Action_Mask mask,
		bool single);

Geometry const * segment_render (
		Net_Rendition const &  nr,
		Geometry const * _hoops_RSII,
		Action_Mask mask,
		bool single);

void draw_overlay_list (Net_Rendition const & nr);

void _hoops_SCPGR (Net_Rendition const & nr);

void create_region (Net_Rendition const &  nr,
			Int_Rectangle const * area, void **image, void **z);

void _hoops_HIPGR (Net_Rendition const &  nr,
		Int_Rectangle const * area, void alter * image, void alter * z);

void _hoops_PIPGR (Net_Rendition const &  nr,
		Int_Rectangle const * area, void alter * image, void alter * z);

void _hoops_ISPGR (Net_Rendition const &  nr,
		void alter * image, void alter * z);

void _hoops_CSPGR (Display_Context alter * dc);
void _hoops_AGHGR (Display_Context alter * dc);

local H3D_Bounding_Tree *_hoops_SRHS(
		Memory_Pool *memory_pool, 
		_hoops_GAHS const *_hoops_ICIS,
		H3D_Display_List_Bin alter *_hoops_RRHA,
		bool _hoops_CCIS);

local bool _hoops_RSIS (
		Net_Rendition const &nr,
		_hoops_GAHS const *_hoops_ICIS);

int _hoops_RHA(Tristrip const *ts, bool _hoops_PAA);
int _hoops_AHA(Polyedge const *pe, bool _hoops_PAA);
int _hoops_PHA(Polymarker const *pm, bool _hoops_PAA);

H3D_Vertex_Buffer_Style _hoops_HRGAR (
	Tristrip const *ts,
	_hoops_CIGA const &_hoops_SIGA,
	H3D_Display_List_Bin alter *_hoops_RRHA,
	unsigned int *_hoops_ARHA);

int _hoops_IRGAR(Tristrip const *ts);

void _hoops_CRGAR(
	Net_Rendition const & nr,
	Tristrip const *ts,
	H3D_Display_List_Bin alter *_hoops_RRHA,
	H3D_Vertex_Buffer_Style _hoops_APHA,
	unsigned int alter *_hoops_SCPI,
	int alter *face_count);

H3D_Vertex_Buffer_Style _hoops_GRHA (
	Polyedge const *pe,
	H3D_Display_List_Bin alter *_hoops_RRHA,
	unsigned int *_hoops_ARHA);


/* _hoops_SSCR _hoops_GGSR _hoops_RH _hoops_APSR _hoops_SPCC, _hoops_PPSR _hoops_RPR _hoops_PPR _hoops_ISHA _hoops_RPR */
void _hoops_RPHA (
	Polyedge const *pe,
	H3D_Display_List_Bin alter *_hoops_RRHA,
	H3D_Vertex_Buffer_Style _hoops_APHA,
	int alter *_hoops_PPHA,
	int alter *_hoops_HPHA,
	int alter *_hoops_IPHA);

int _hoops_SRGAR(H3DData *h3ddata, H3D_Display_List_Bin *_hoops_RRHA);

Param_Source _hoops_IGIA(
		_hoops_HHA const &matr,
		int type,
		int number);

void _hoops_HRIA (
		H3DData const *			h3ddata,
		Net_Rendition const &	nr,
		int 					type,
		int 					flags,
		int 					_hoops_IRIA,
		_hoops_HCI *		_hoops_ICI);

/* _hoops_RCPA _hoops_SGH _hoops_RGR _hoops_API, _hoops_RHAC *_hoops_PIHA* _hoops_GAGAR _hoops_RH _hoops_RAGAR _hoops_PPARR _hoops_CCA
 * _hoops_HH _hoops_ISIA.  _hoops_SPAA _hoops_RIH _hoops_SCH _hoops_GGR, _hoops_PPR _hoops_RH _hoops_API _hoops_GRS _hoops_CSGA _hoops_PGAP
 * _hoops_AAGAR _hoops_CGH _hoops_SHH _hoops_IGI _hoops_IH _hoops_RH _hoops_CHIA _hoops_HH.
 *
 * _hoops_PAGAR, _hoops_RGR _hoops_API _hoops_HRS _hoops_RH _hoops_HH _hoops_HPI _hoops_IHIA _hoops_CCA _hoops_IRS _hoops_RAGA _hoops_HH _hoops_GPRR;
 * _hoops_IH _hoops_HAGAR, _hoops_IAGAR _hoops_SIAS _hoops_ASRC _hoops_HPI 0, _hoops_CAGAR _hoops_RSHC.  _hoops_SAGAR, _hoops_CGPR
 * _hoops_SHIA _hoops_HRGR _hoops_GPGAR, _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_PIIA _hoops_HIIA; _hoops_IH _hoops_IRS _hoops_RAGA _hoops_AAGAR, _hoops_SCH _hoops_HRS
 * _hoops_RH _hoops_IHIA _hoops_GPRR (_hoops_HGPP _hoops_GAR _hoops_IAGAR).
 */
void _hoops_SII(int _hoops_GCI, int number, _hoops_HCI *_hoops_ICI, int *_hoops_RCI, int *_hoops_ACI, int *_hoops_PCI);


/* _hoops_RPGAR _hoops_IS _hoops_CCPP _hoops_RRAP->_hoops_APGAR _hoops_IS _hoops_RH _hoops_HGRC _hoops_IGIR, _hoops_PPR _hoops_HRS _hoops_SCH _hoops_RPP _hoops_PPGAR */
static inline short *_hoops_AIAS(H3DData alter *h3ddata, int _hoops_HHARR)
{
	if (h3ddata->_hoops_PSRRR == null || h3ddata->_hoops_HSRRR < _hoops_HHARR) { 
		short *_hoops_PHAS;
		int size = _hoops_HHARR * 1.5;

		TRY_ALLOC_ARRAY(_hoops_PHAS, size, short); 
		if (!_hoops_PHAS) {
			size = _hoops_HHARR;
			TRY_ALLOC_ARRAY(_hoops_PHAS, size, short); 
			if (!_hoops_PHAS)
				return null;
		}
		if (h3ddata->_hoops_PSRRR)
			FREE_ARRAY(h3ddata->_hoops_PSRRR, h3ddata->_hoops_HSRRR, short);
		h3ddata->_hoops_HSRRR = size;
		h3ddata->_hoops_PSRRR = _hoops_PHAS;
	} 
	return h3ddata->_hoops_PSRRR;
}

/* _hoops_RPGAR _hoops_IS _hoops_CCPP _hoops_RRAP->_hoops_HPGAR _hoops_IS _hoops_RH _hoops_HGRC _hoops_IGIR, _hoops_PPR _hoops_HRS _hoops_SCH _hoops_RPP _hoops_PPGAR */
static inline int *_hoops_IPGAR(H3DData alter *h3ddata, int _hoops_HHARR)
{
	if (h3ddata->_hoops_ISRRR == null || h3ddata->_hoops_CSRRR < _hoops_HHARR) { 
		int *_hoops_PHAS;
		int size = _hoops_HHARR * 1.5;

		TRY_ALLOC_ARRAY(_hoops_PHAS, size, int); 
		if (!_hoops_PHAS) {
			size = _hoops_HHARR;
			TRY_ALLOC_ARRAY(_hoops_PHAS, size, int); 
			if (!_hoops_PHAS)
				return null;
		}
		if (h3ddata->_hoops_ISRRR)
			FREE_ARRAY(h3ddata->_hoops_ISRRR, h3ddata->_hoops_CSRRR, int);
		h3ddata->_hoops_CSRRR = size;
		h3ddata->_hoops_ISRRR = _hoops_PHAS;
	} 
	return h3ddata->_hoops_ISRRR;
}


enum _hoops_CPGAR
{
	// _hoops_SPGAR _hoops_ACSC _hoops_CGH _hoops_SCIR _hoops_GAAS (_hoops_SHIR _hoops_RSSA)
	_hoops_HCSC		= (1<<1),
	_hoops_SISC		= (1<<2),

	// _hoops_RHCP _hoops_CI _hoops_CGH _hoops_GHGAR _hoops_RH _hoops_GPIA _hoops_GRPC (_hoops_SHIR _hoops_CGAA)
	_hoops_ICSC	= (1<<3),

	// _hoops_GRSH _hoops_IS _hoops_PGSA _hoops_RH _hoops_GPIA - _hoops_SPR _hoops_HRGR _hoops_SHR _hoops_ARP.
	_hoops_RISC			= (1<<4),
	_hoops_PCSC			= (1<<5),
	_hoops_CCSC				= (1<<6),
	_hoops_SCSC			= (1<<7),

	// _hoops_RACRR _hoops_SGI
	_hoops_PRAC		= (1<<8),
	_hoops_HRAC				= (1<<9),
	_hoops_RHSC			= (1<<10),
	_hoops_RSSC			= (1<<11),
	_hoops_ASSC				= (1<<12),
	_hoops_IISC				= (1<<13),

	// _hoops_RHGAR _hoops_RGR _hoops_GPIA _hoops_ISSC _hoops_IS _hoops_AAPA _hoops_PAPA
	_hoops_CGGS					= 0,
};


local int _hoops_ARAC(
	H3DData const *h3ddata,
	Net_Rendition const &nr,
	_hoops_ICP const &_hoops_CCP,
	Polymarker const *pm,
	H3D_Display_List const *odl,
	float *size);


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
	float					_hoops_SGHGR);


#endif // _hoops_AHGAR



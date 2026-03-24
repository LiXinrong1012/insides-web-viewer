/*
* Copyright (c) 2007 by Tech Soft 3D, LLC.
* The information contained herein is confidential and proprietary to
* Tech Soft 3D, LLC., and considered a trade secret as defined under
* civil and criminal statutes.	Tech Soft 3D shall pursue its civil
* and criminal remedies in the event of unauthorized use or misappropriation
* of its trade secrets.	 Use of this information by anyone other than
* authorized employees of Tech Soft 3D, LLC. is granted only under a
* written non-disclosure agreement, expressly prescribing the scope and
* manner of such use.
*
 * $Id: obf_tmp.txt 1.390 2011-01-13 22:30:14 boni Exp $
*/


#ifndef _hoops_CAAAH
#define _hoops_CAAAH

#include "windows_wrapper.h"	// _hoops_CGRI <_hoops_SPHGR._hoops_GGHR>, _hoops_PIHA _hoops_RCPS _hoops_SRS :(


#include <stdio.h>
#include <stdlib.h>

#include "adt.h"
#include "database.h"
#include "driver.h"
#include "hpserror.h"
#include "patterns.h"
#include "phedron.h"
#include "please.h"
#include "searchh.h"
#include "tandt.h"
#include "hversion.h"
#include "d3dutil.h"

/*_hoops_CPCHR _hoops_IGCPR*/
class _hoops_RGRGP;
class _hoops_HHRGP;
class _hoops_SAAAH;
class _hoops_GPAAH;
class _hoops_RGHRH;
class _hoops_RIARH;
class H3DShaderID;
class _hoops_GSCRH;
class _hoops_HIARH;

#include <Pbt.h>
#include "msw.h"

#pragma warning(disable : 4710)

#define _hoops_RPAAH 5000
#define _hoops_CHSRH 0x7FFFFFFF //8192 _hoops_RHGS _hoops_PHI
#define _hoops_SHSRH 4092

#define HDX9_OUT_OF_MEMORY(_hoops_IIRHP) (_hoops_IIRHP == E_OUTOFMEMORY || ((_hoops_IIRHP&0xffff) == ERROR_NOT_ENOUGH_MEMORY))

// _hoops_APAAH _hoops_PAR _hoops_GSIRH, 
#define HDX9_MANAGED_POOL
#ifdef HDX9_MANAGED_POOL
#	define _hoops_PPAAH					D3DPOOL_MANAGED
#else
#	define _hoops_PPAAH					D3DPOOL_DEFAULT
#endif


struct DX9ImageRegion 
{
	LPDIRECT3DSURFACE9 surface;	// _hoops_RCPGR _hoops_GISH _hoops_ISSGR
	DX9ImageRegion* next;		// _hoops_CRS _hoops_IS _hoops_SPS _hoops_ISPH - _hoops_RGHP _hoops_RHSP _hoops_IIPI _hoops_IIGR _hoops_SISS
};

struct DX9DepthRegion 
{
	LPDIRECT3DSURFACE9 surface;	// _hoops_RCPGR _hoops_HCH _hoops_ISSGR
	LPDIRECT3DSURFACE9 texture;	// _hoops_RCPGR _hoops_HPAAH _hoops_ISSGR
	DX9DepthRegion* next;		// _hoops_CRS _hoops_IS _hoops_SPS _hoops_ISPH - _hoops_RGHP _hoops_RHSP _hoops_IIPI _hoops_IIGR _hoops_SISS
};


D3DPRIMITIVETYPE d3dprimitive(H3DPRIMITIVETYPE type)
{
	switch (type) {
		case H3DPT_POINTLIST:		return D3DPT_POINTLIST;
		case H3DPT_LINELIST:		return D3DPT_LINELIST;
		case H3DPT_LINESTRIP:    	return D3DPT_LINESTRIP;
		case H3DPT_TRIANGLELIST: 	return D3DPT_TRIANGLELIST;
		case H3DPT_TRIANGLESTRIP:	return D3DPT_TRIANGLESTRIP;
		case H3DPT_TRIANGLEFAN:  	return D3DPT_TRIANGLEFAN;
		case H3DPT_FORCE_DWORD:  	return D3DPT_FORCE_DWORD; 
		default:
			HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
				"Internal error: Unhandled primitive type mapping.");
			return D3DPT_POINTLIST;
	}
}

D3DBLEND d3dblend(H3DBLEND type)
{
	switch (type) {
		case H3DBLEND_ZERO:				return D3DBLEND_ZERO;
		case H3DBLEND_ONE:				return D3DBLEND_ONE;
		case H3DBLEND_SRCCOLOR:         return D3DBLEND_SRCCOLOR;
		case H3DBLEND_INVSRCCOLOR:      return D3DBLEND_INVSRCCOLOR;
		case H3DBLEND_SRCALPHA:         return D3DBLEND_SRCALPHA;
		case H3DBLEND_INVSRCALPHA:      return D3DBLEND_INVSRCALPHA;
		case H3DBLEND_DESTALPHA:        return D3DBLEND_DESTALPHA;
		case H3DBLEND_INVDESTALPHA:     return D3DBLEND_INVDESTALPHA;
		case H3DBLEND_DESTCOLOR:        return D3DBLEND_DESTCOLOR;
		case H3DBLEND_INVDESTCOLOR:     return D3DBLEND_INVDESTCOLOR;
		case H3DBLEND_SRCALPHASAT:      return D3DBLEND_SRCALPHASAT;
		case H3DBLEND_BOTHSRCALPHA:     return D3DBLEND_BOTHSRCALPHA;
		case H3DBLEND_BOTHINVSRCALPHA:  return D3DBLEND_BOTHINVSRCALPHA;
		case H3DBLEND_BLENDFACTOR:      return D3DBLEND_BLENDFACTOR;
		case H3DBLEND_INVBLENDFACTOR:   return D3DBLEND_INVBLENDFACTOR;
		/* _hoops_IPAAH _hoops_RGAR -- */
#if !defined(H3D_DISABLE_9EX)
		//_hoops_AGIR _hoops_CPAAH:        _hoops_ASRC _hoops_SPAAH;
		//_hoops_AGIR _hoops_GHAAH:     _hoops_ASRC _hoops_RHAAH;
#endif // !_hoops_AHAAH
		/* -- _hoops_IPAAH _hoops_RGAR */
		case H3DBLEND_FORCE_DWORD:      return D3DBLEND_FORCE_DWORD;
		default:
			HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
				"Internal error: Unhandled blend type mapping.");
			return D3DBLEND_ZERO;
	}
}



DWORD d3dclear(int flags)
{
	DWORD _hoops_PHAAH = 0;
	if (BIT(flags, H3DCLEAR_TARGET))
		_hoops_PHAAH |= D3DCLEAR_TARGET;
	if (BIT(flags, H3DCLEAR_ZBUFFER))
		_hoops_PHAAH |= D3DCLEAR_ZBUFFER;
	if (BIT(flags, H3DCLEAR_STENCIL))
		_hoops_PHAAH |= D3DCLEAR_STENCIL;
	return _hoops_PHAAH;
}

D3DSHADEMODE d3dshademode(H3DSHADEMODE type)
{
	switch (type) {
		case H3DSHADE_FLAT:			return D3DSHADE_FLAT;
		case H3DSHADE_GOURAUD:		return D3DSHADE_GOURAUD;
		case H3DSHADE_PHONG:		return D3DSHADE_PHONG;
		case H3DSHADE_FORCE_DWORD:	return D3DSHADE_FORCE_DWORD;
		default:
			HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
				"Internal error: Unhandled shade mode mapping.");
			return D3DSHADE_FLAT;
	}
}

D3DTEXTUREADDRESS d3dtextureaddress(H3DTEXTUREADDRESS type)
{
	switch (type) {
		case H3DTADDRESS_WRAP:			return D3DTADDRESS_WRAP;
		case H3DTADDRESS_MIRROR:		return D3DTADDRESS_MIRROR;
		case H3DTADDRESS_CLAMP:			return D3DTADDRESS_CLAMP;
		case H3DTADDRESS_BORDER:		return D3DTADDRESS_BORDER;
		case H3DTADDRESS_MIRRORONCE:	return D3DTADDRESS_MIRRORONCE;
		default:
			HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
				"Internal error: Unhandled shade mode mapping.");
			return D3DTADDRESS_WRAP;
	}
}

D3DTEXTUREFILTERTYPE d3dtexturefilter(H3DTEXTUREFILTERTYPE type)
{
	switch (type) {
		case H3DTEXF_NONE:				return D3DTEXF_NONE;
		case H3DTEXF_POINT:				return D3DTEXF_POINT;
		case H3DTEXF_LINEAR:			return D3DTEXF_LINEAR;
		case H3DTEXF_ANISOTROPIC:		return D3DTEXF_ANISOTROPIC;
		case H3DTEXF_PYRAMIDALQUAD:		return D3DTEXF_PYRAMIDALQUAD;
		case H3DTEXF_GAUSSIANQUAD:		return D3DTEXF_GAUSSIANQUAD;
		default:
			HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
				"Internal error: Unhandled shade mode mapping.");
			return D3DTEXF_NONE;
	}
}

D3DCULL d3dcull(H3DCULL type)
{
	switch (type) {
		case H3DCULL_NONE:			return D3DCULL_NONE;
		case H3DCULL_CW:			return D3DCULL_CW;
		case H3DCULL_CCW:			return D3DCULL_CCW;
		case H3DCULL_FORCE_DWORD:	return D3DCULL_FORCE_DWORD;
		default:
			HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
				"Internal error: Unhandled cull mode mapping.");
			return D3DCULL_NONE;
	}
}

D3DFORMAT d3dformat(H3DFORMAT type)
{
	switch (type) {
		case H3DFMT_D24S8:			return D3DFMT_D24S8;
		case H3DFMT_A8R8G8B8:		return D3DFMT_A8R8G8B8;
		case H3DFMT_R32F:			return D3DFMT_R32F;
		case H3DFMT_INDEX16:		return D3DFMT_INDEX16;
		case H3DFMT_INDEX32:		return D3DFMT_INDEX32;
		default:
			HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
				"Internal error: Unhandled format mapping.");
			return D3DFMT_INDEX32;
	}
}

D3DVIEWPORT9 d3dviewport(H3DViewport const *_hoops_APPRR)
{
	D3DVIEWPORT9 _hoops_PAPH;
	_hoops_PAPH.X = _hoops_APPRR->X;
	_hoops_PAPH.Y = _hoops_APPRR->Y;
	_hoops_PAPH.Width = _hoops_APPRR->Width;
	_hoops_PAPH.Height = _hoops_APPRR->Height;
	_hoops_PAPH.MinZ = _hoops_APPRR->MinZ;
	_hoops_PAPH.MaxZ = _hoops_APPRR->MaxZ;
	return _hoops_PAPH;
}

H3DViewport _hoops_HHAAH(D3DVIEWPORT9 const *_hoops_PAPH)
{
	H3DViewport _hoops_APPRR;
	_hoops_APPRR.X = _hoops_PAPH->X;
	_hoops_APPRR.Y = _hoops_PAPH->Y;
	_hoops_APPRR.Width = _hoops_PAPH->Width;
	_hoops_APPRR.Height = _hoops_PAPH->Height;
	_hoops_APPRR.MinZ = _hoops_PAPH->MinZ;
	_hoops_APPRR.MaxZ = _hoops_PAPH->MaxZ;
	return _hoops_APPRR;
}
/*****************************************************************************
*****************************************************************************
					_hoops_SRIGR _hoops_HICRR _hoops_PSCH
*****************************************************************************
*****************************************************************************/

H3DVertexFormat _hoops_IHAAH(DWORD _hoops_CHAAH) 
{
	H3DVertexFormat _hoops_PPCP;
	int i = 0;

	if (BIT(_hoops_CHAAH, D3DFVF_XYZ))		_hoops_PPCP._hoops_AIHC();
	if (BIT(_hoops_CHAAH, D3DFVF_NORMAL))	_hoops_PPCP._hoops_CCRS();
	if (BIT(_hoops_CHAAH, D3DFVF_DIFFUSE))	_hoops_PPCP._hoops_RPHC();
	_hoops_PPCP._hoops_PPIGR((_hoops_CHAAH & D3DFVF_TEXCOUNT_MASK) >> D3DFVF_TEXCOUNT_SHIFT);

	for(i = 0; i < _hoops_PPCP._hoops_APIGR(); i++) {
		int _hoops_SHAAH = _hoops_CHAAH & D3DFVF_TEXCOORDSIZE1(i);

		if (D3DFVF_TEXCOORDSIZE1(i) == _hoops_SHAAH)		_hoops_PPCP._hoops_HIHC(i,1);
		else if (D3DFVF_TEXCOORDSIZE2(i) == _hoops_SHAAH)	_hoops_PPCP._hoops_HIHC(i,2);
		else if (D3DFVF_TEXCOORDSIZE3(i) == _hoops_SHAAH)	_hoops_PPCP._hoops_HIHC(i,3);
		else if (D3DFVF_TEXCOORDSIZE4(i) == _hoops_SHAAH)	_hoops_PPCP._hoops_HIHC(i,4);
	}
	return _hoops_PPCP;
}

local DWORD _hoops_GIAAH(H3DVertexFormat _hoops_PPCP)
{
	int i = 0;
	DWORD _hoops_CHAAH = 0;

	if (_hoops_PPCP._hoops_IPIGR())		_hoops_CHAAH |= D3DFVF_XYZ;
	if (_hoops_PPCP._hoops_HHCP())		_hoops_CHAAH |= D3DFVF_NORMAL;
	if (_hoops_PPCP._hoops_SHCP())		_hoops_CHAAH |= D3DFVF_DIFFUSE;

	for(i = 0; i < _hoops_PPCP._hoops_APIGR(); i++) {
		_hoops_CHAAH += D3DFVF_TEX1;

		if (_hoops_PPCP._hoops_CPIGR(i) == 1)		_hoops_CHAAH |= D3DFVF_TEXCOORDSIZE1(i);
		else if (_hoops_PPCP._hoops_CPIGR(i) == 2)	_hoops_CHAAH |= D3DFVF_TEXCOORDSIZE2(i);
		else if (_hoops_PPCP._hoops_CPIGR(i) == 3)	_hoops_CHAAH |= D3DFVF_TEXCOORDSIZE3(i);
		else if (_hoops_PPCP._hoops_CPIGR(i) == 4)	_hoops_CHAAH |= D3DFVF_TEXCOORDSIZE4(i);
		
	}

	return _hoops_CHAAH;
}


struct DX9Data;
void _hoops_GPAP(DX9Data& dx9data, IDirect3DSurface9 *_hoops_ISCRR, IDirect3DSurface9 *_hoops_AASP = null, IDirect3DSurface9 *_hoops_CSCRR = null, IDirect3DSurface9 *_hoops_SSCRR = null, IDirect3DSurface9 *_hoops_GGSRR = null );

struct DX9Data : H3DData
{
	DX9Data					*next;
	DX9Data					**backlink;

	_hoops_RGRGP			*_hoops_HISRH;			// _hoops_HHPA _hoops_RAPA _hoops_HRP: _hoops_HRGGP, _hoops_AGSHA, _hoops_CAPRR, _hoops_AHI
	_hoops_HHRGP			*_hoops_IISRH;				// _hoops_SCGR _hoops_RAPA _hoops_HRP: _hoops_APGGP, _hoops_SISS, _hoops_CCH, _hoops_AGHS, _hoops_AHI
	D3DPRESENT_PARAMETERS	_hoops_HCARH;	// _hoops_RIAAH _hoops_GRPAR _hoops_IH _hoops_RH _hoops_SISS _hoops_IS _hoops_SHH _hoops_SPIP 
	LPDIRECT3DDEVICE9		pDevice;				// _hoops_IPCP _hoops_RAPA _hoops_GCAC _hoops_SISS
	LPDIRECT3DSWAPCHAIN9	_hoops_IGCRH;				// _hoops_IPCP _hoops_GGSHR _hoops_AASH

	// _hoops_AIAAH _hoops_RPR _hoops_IH _hoops_PIAAH/_hoops_HSGC
	int						_hoops_HIAAH;

	//_hoops_IAGIP
	DX9ImageRegion *_hoops_PSARH;		
	DX9DepthRegion *_hoops_HSARH;			

	//_hoops_AH _hoops_HCH _hoops_ICH _hoops_ASAC/_hoops_PHIH
	void *_hoops_ICIRH;
	void *_hoops_CCIRH;

	//_hoops_IHAH _hoops_RH _hoops_SCGR _hoops_GPHA/_hoops_CIHA _hoops_SRHR
	LPDIRECT3DVERTEXBUFFER9 *_hoops_SISSA;
	LPDIRECT3DINDEXBUFFER9	*_hoops_GCSSA;

	//_hoops_IHAH _hoops_RH _hoops_SCGR _hoops_AHCS
	struct {
		IDirect3DSurface9		*_hoops_SIARH;
		IDirect3DSurface9		*_hoops_GCARH;
		IDirect3DSurface9		*_hoops_RCARH;
		IDirect3DSurface9		*_hoops_ACARH;
		IDirect3DSurface9		*ds;	// _hoops_IIAAH
	} _hoops_CIARH;

	D3DCAPS9				_hoops_HPHRH;			//_hoops_AGRAH _hoops_IH _hoops_RH _hoops_SISS
	D3DFORMAT				_hoops_IIGAH;
	bool					_hoops_PASRH;

	D3DVERTEXELEMENT9		_hoops_CIAAH[15];		// _hoops_SI _hoops_GC _hoops_IH _hoops_SGP _hoops_GPHA _hoops_IGCPR

	HRESULT _hoops_IIRHP;
};

#define DX9D(dc) ((DX9Data alter *)((dc)->_hoops_RIHGR))
#define DX9NRD(nr) (DX9D((nr)->_hoops_SRA))



#ifndef DX9DATA_ONLY


#define _hoops_SIAAH				0x00000001
#define _hoops_GGRAH					0x00000002
#define _hoops_GCAAH							0x00000004
#define _hoops_RCAAH							0x00000008
#define _hoops_ACAAH							0x00000010
#define _hoops_PCAAH							0x00000020
#define _hoops_GCCRH					0x00000040
#define _hoops_HCAAH							0x00000080
#define _hoops_ICAAH							0x00000100
#define _hoops_CCAAH							0x00000200
#define _hoops_SCAAH							0x00000400
#define _hoops_GSAAH							0x00000800
#define _hoops_RSAAH							0x00001000
#define _hoops_ASAAH							0x00002000
#define _hoops_PSAAH				0x00004000
#define _hoops_HSAAH							0x00008000
#define _hoops_ISAAH							0x00010000
#define _hoops_CSAAH							0x00020000
#define _hoops_SSAAH							0x00040000
#define _hoops_GGPAH							0x00080000
#define _hoops_GCSRH				0x00100000
#define _hoops_RGPAH							0x00200000
#define _hoops_AGPAH							0x00400000
#define _hoops_PGPAH							0x00800000
#define _hoops_ARRAH					0x01000000
#define _hoops_HGPAH							0x02000000
#define _hoops_IGPAH							0x04000000
#define _hoops_CGPAH							0x08000000
#define _hoops_SGPAH							0x10000000
#define _hoops_GRPAH							0x20000000
#define _hoops_RRPAH							0x40000000
#define _hoops_ARPAH							0x80000000

/* _hoops_HRARR _hoops_SCPGH */
#define XBIT_NONE							0L
#define XBIT_NO_INDEXED_PRIMITIVES			1L
#define XBIT_BAD_MSAA_SPRITING				2L
#define XBIT_BAD_DEPTH_PEELING				3L
#define XBIT_POINT_SPRITES_BASH_ALL			4L


#define D3DXMatrix_2_floats(d3d_mat_in, _hoops_PRPAH)		\
	_hoops_PRPAH[0][0] = d3d_mat_in._11;					\
	_hoops_PRPAH[0][1] = d3d_mat_in._12;					\
	_hoops_PRPAH[0][2] = d3d_mat_in._13;					\
	_hoops_PRPAH[0][3] = d3d_mat_in._14;					\
	\
	_hoops_PRPAH[1][0] = d3d_mat_in._21;					\
	_hoops_PRPAH[1][1] = d3d_mat_in._22;					\
	_hoops_PRPAH[1][2] = d3d_mat_in._23;					\
	_hoops_PRPAH[1][3] = d3d_mat_in._24;					\
	\
	_hoops_PRPAH[2][0] = d3d_mat_in._31;					\
	_hoops_PRPAH[2][1] = d3d_mat_in._32;					\
	_hoops_PRPAH[2][2] = d3d_mat_in._33;					\
	_hoops_PRPAH[2][3] = d3d_mat_in._34;					\
	\
	_hoops_PRPAH[3][0] = d3d_mat_in._41;					\
	_hoops_PRPAH[3][1] = d3d_mat_in._42;					\
	_hoops_PRPAH[3][2] = d3d_mat_in._43;					\
	_hoops_PRPAH[3][3] = d3d_mat_in._44;			


/*
 * _hoops_HRPAH _hoops_IRPAH
 */
#define _hoops_CRPAH(dx9data, _hoops_RHIA, mode) _hoops_GHIA(\
	(dx9data)->_hoops_CSC->_hoops_RAGRR[_hoops_RHIA] = mode; \
	(dx9data)->pDevice->SetSamplerState(_hoops_RHIA, D3DSAMP_ADDRESSU, mode); \
)

#define ENSURE_TEXTURE_WRAP_S(dx9data, _hoops_RHIA, mode) _hoops_GHIA(\
	if ((dx9data)->_hoops_CSC->_hoops_RAGRR[_hoops_RHIA] != mode) \
		_hoops_CRPAH((dx9data), _hoops_RHIA, mode); \
)

#define _hoops_SRPAH(dx9data, _hoops_RHIA, mode) _hoops_GHIA(\
	(dx9data)->_hoops_CSC->_hoops_AAGRR[_hoops_RHIA] = mode; \
	(dx9data)->pDevice->SetSamplerState(_hoops_RHIA, D3DSAMP_ADDRESSV, mode); \
)

#define _hoops_SAIRH(dx9data, _hoops_RHIA, mode) _hoops_GHIA(\
	if ((dx9data)->_hoops_CSC->_hoops_AAGRR[_hoops_RHIA] != mode) \
		_hoops_SRPAH((dx9data), _hoops_RHIA, mode); \
)

#define _hoops_GAPAH(dx9data, _hoops_RHIA, mode) _hoops_GHIA(\
	(dx9data)->_hoops_CSC->_hoops_HAGRR[_hoops_RHIA] = mode; \
	(dx9data)->pDevice->SetSamplerState(_hoops_RHIA, D3DSAMP_MINFILTER, mode); \
)

#define _hoops_GPIRH(dx9data, _hoops_RHIA, mode) _hoops_GHIA(\
	if ((dx9data)->_hoops_CSC->_hoops_HAGRR[_hoops_RHIA] != mode) \
		_hoops_GAPAH((dx9data), _hoops_RHIA, mode); \
)

#define _hoops_RAPAH(dx9data, _hoops_RHIA, mode) _hoops_GHIA(\
	(dx9data)->_hoops_CSC->_hoops_PAGRR[_hoops_RHIA] = mode; \
	(dx9data)->pDevice->SetSamplerState(_hoops_RHIA, D3DSAMP_MAGFILTER, mode); \
)

#define _hoops_RPIRH(dx9data, _hoops_RHIA, mode) _hoops_GHIA(\
	if ((dx9data)->_hoops_CSC->_hoops_PAGRR[_hoops_RHIA] != mode) \
		_hoops_RAPAH((dx9data), _hoops_RHIA, mode); \
)

#define _hoops_AAPAH(dx9data, _hoops_RHIA, mode) _hoops_GHIA(\
	(dx9data)->_hoops_CSC->_hoops_IAGRR[_hoops_RHIA] = mode; \
	(dx9data)->pDevice->SetSamplerState(_hoops_RHIA, D3DSAMP_MIPFILTER, mode); \
)

#define _hoops_APIRH(dx9data, _hoops_RHIA, mode) _hoops_GHIA(\
	if ((dx9data)->_hoops_CSC->_hoops_IAGRR[_hoops_RHIA] != mode) \
		_hoops_AAPAH((dx9data), _hoops_RHIA, mode); \
)

#define _hoops_APSS(dx9data) _hoops_GHIA(\
	{ \
		int _hoops_PSARR; \
		for (_hoops_PSARR = 0; _hoops_PSARR < _hoops_CIGP; ++_hoops_PSARR) { \
			(dx9data)->_hoops_CSC->_hoops_RAGRR[_hoops_PSARR] = _hoops_RSARR; \
			(dx9data)->_hoops_CSC->_hoops_AAGRR[_hoops_PSARR] = _hoops_RSARR; \
			(dx9data)->_hoops_CSC->_hoops_PAGRR[_hoops_PSARR] = _hoops_RSARR; \
			(dx9data)->_hoops_CSC->_hoops_HAGRR[_hoops_PSARR] = _hoops_RSARR; \
			(dx9data)->_hoops_CSC->_hoops_IAGRR[_hoops_PSARR] = _hoops_RSARR; \
		} \
	} \
)

// _hoops_PAPAH _hoops_HCGP
#define _hoops_HAPAH(dx9data,_hoops_IAPAH,_hoops_HACP,stride) _hoops_GHIA(\
	if (_hoops_HACP != dx9data->_hoops_SISSA[_hoops_IAPAH]) { \
		dx9data->pDevice->SetStreamSource (_hoops_IAPAH, _hoops_HACP, 0, stride); \
		dx9data->_hoops_SISSA[_hoops_IAPAH] = _hoops_HACP; \
	} \
)




/*****************************************************************************
*****************************************************************************
						_hoops_AHHH _hoops_IPSRH _hoops_CAPAH
*****************************************************************************
*****************************************************************************/
HRESULT _hoops_CSIRH (Display_Context alter * dc);
HRESULT _hoops_ACIRH(Display_Context alter * dc);
local void invalidate_cache (D3D_System_Data *d3d_sd)
{
	if (d3d_sd->_hoops_CSC)
		SET_MEMORY (d3d_sd->_hoops_CSC, sizeof(H3DCache), 0x5c);
}


class DX9CreateDeviceTask : public _hoops_GCARR 
{
public:
	DX9CreateDeviceTask(
		D3D_System_Data *d3d_sd,
		UINT _hoops_SAPAH,
		D3DDEVTYPE _hoops_GPPAH,
		HWND _hoops_RPPAH,
		DWORD _hoops_APPAH) :
			d3d_sd(d3d_sd),
			_hoops_SAPAH(_hoops_SAPAH),
			_hoops_GPPAH(_hoops_GPPAH),
			_hoops_RPPAH(_hoops_RPPAH),
			_hoops_APPAH(_hoops_APPAH)
	{
		((_hoops_SRIAP *) d3d_sd->_hoops_RISSA)->_hoops_PCARR(this);
	}
	virtual ~DX9CreateDeviceTask() {;};

	virtual void _hoops_HCARR(bool _hoops_SCARR)
	{
		UNREFERENCED(_hoops_SCARR);
		D3DPRESENT_PARAMETERS _hoops_PPPAH;
		ZeroMemory( &_hoops_PPPAH, sizeof(_hoops_PPPAH) );

		_hoops_PPPAH.Windowed = true;
		_hoops_PPPAH.SwapEffect = D3DSWAPEFFECT_COPY;
		_hoops_PPPAH.BackBufferFormat = D3DFMT_A8R8G8B8;
		_hoops_PPPAH.BackBufferWidth = 1;
		_hoops_PPPAH.BackBufferHeight = 1;

		d3d_sd->_hoops_SHSSA->CreateDevice(
				_hoops_SAPAH, 
				_hoops_GPPAH,
				_hoops_RPPAH, 
				_hoops_APPAH, 
				&_hoops_PPPAH,
				&d3d_sd->pDevice);

		HM_RELEASE_SEMAPHORE(d3d_sd->_hoops_HISSA, 1);
	}

	virtual _hoops_ICARR Type() {return _hoops_HPPAH;};

private:
	D3D_System_Data *d3d_sd;
	UINT _hoops_SAPAH;
	D3DDEVTYPE _hoops_GPPAH;
	HWND _hoops_RPPAH;
	DWORD _hoops_APPAH;
};

class DX9DeleteDeviceTask : public _hoops_GCARR 
{
public:

	DX9DeleteDeviceTask(D3D_System_Data *d3d_sd) : d3d_sd(d3d_sd)
	{
		((_hoops_SRIAP *) d3d_sd->_hoops_RISSA)->_hoops_PCARR(this);
	};
	virtual ~DX9DeleteDeviceTask() {;};

	virtual void _hoops_HCARR(bool _hoops_SCARR)
	{
		UNREFERENCED(_hoops_SCARR);
		H_SAFE_RELEASE(d3d_sd->pDevice);

		HM_RELEASE_SEMAPHORE(d3d_sd->_hoops_HISSA, 1);
	};

	virtual _hoops_ICARR Type() {return _hoops_IPPAH;};

private:

	D3D_System_Data *d3d_sd;
};


class DX9ResetDeviceTask : public _hoops_GCARR 
{
public:
	DX9ResetDeviceTask(D3D_System_Data *d3d_sd): d3d_sd(d3d_sd)
	{
		((_hoops_SRIAP *) d3d_sd->_hoops_RISSA)->_hoops_PCARR(this);
	}
	virtual ~DX9ResetDeviceTask() {;};

	virtual void _hoops_HCARR(bool _hoops_SCARR)
	{
		UNREFERENCED(_hoops_SCARR);
		DX9Data *dx9data;
		HRESULT _hoops_IIRHP;

		D3DPRESENT_PARAMETERS _hoops_PPPAH;
		ZeroMemory( &_hoops_PPPAH, sizeof(_hoops_PPPAH) );

		_hoops_PPPAH.Windowed = true;
		_hoops_PPPAH.SwapEffect = D3DSWAPEFFECT_COPY;
		_hoops_PPPAH.BackBufferFormat = D3DFMT_A8R8G8B8;
		_hoops_PPPAH.BackBufferWidth = 1;
		_hoops_PPPAH.BackBufferHeight = 1;

		invalidate_cache(d3d_sd);

		// _hoops_PPGGR _hoops_HCR _hoops_CPPAH _hoops_AGSAR
		dx9data = d3d_sd->dx9data_list;
		while (dx9data) {
			if (dx9data->_hoops_RHGRR) {
				dx9data->_hoops_RHGRR = false;
				_hoops_ACIRH((Display_Context alter*)dx9data->dc);
				H_SAFE_RELEASE(dx9data->_hoops_IGCRH);
			}
			dx9data = dx9data->next;
		}
		

		while (FAILED(_hoops_IIRHP = d3d_sd->pDevice->Reset(&_hoops_PPPAH))) {
			if (_hoops_IIRHP == D3DERR_DEVICELOST) {
				while ((_hoops_IIRHP = d3d_sd->pDevice->TestCooperativeLevel()) == D3DERR_DEVICELOST)
					;	//_hoops_AA _hoops_ISAP
				if (_hoops_IIRHP == D3DERR_DRIVERINTERNALERROR) {
					ASSERT(0);
				}
			}
			else {
				ASSERT(0);
			}
		}

		// _hoops_GHRAA _hoops_RH _hoops_HIGGP'_hoops_GRI _hoops_SISS-_hoops_AAR _hoops_AGSAR
		dx9data = d3d_sd->dx9data_list;
		while (dx9data) {
			_hoops_IIRHP = _hoops_CSIRH((Display_Context alter*)dx9data->dc);
			if (FAILED(_hoops_IIRHP)) {
				_hoops_ACIRH((Display_Context alter*)dx9data->dc);
			}
			dx9data->_hoops_RHGRR = true;
			dx9data = dx9data->next;
		}

		HM_RELEASE_SEMAPHORE(d3d_sd->_hoops_HISSA, 1);
	}

	virtual _hoops_ICARR Type() {return _hoops_HPPAH;};

private:
	D3D_System_Data *d3d_sd;
};



/*****************************************************************************
*****************************************************************************
							_hoops_RHCP/_hoops_SPPAH _hoops_GRIRR
*****************************************************************************
*****************************************************************************/

//_hoops_PAHGA _hoops_IRS _hoops_GHPAH _hoops_IIGR _hoops_PCCP _hoops_AASGR _hoops_PAR _hoops_CSHS
struct hdx9_indexed_primitive : CMO_Pooled
{
	H3DPRIMITIVETYPE type; //_hoops_IAS._hoops_ISHI. _hoops_RHPAH _hoops_PAR _hoops_AHPAH
	unsigned int size;
	unsigned int count;
	IDirect3DIndexBuffer9 *idx_buff;
};


class _hoops_PHPAH : public H3DIndexedBufferObject
{
public:
	ID3DXMesh								*m_d3dxmesh;

	_hoops_PHPAH() 
	{
		HOOPS_WORLD->display_list_vram_usage += _hoops_RPAAH;
		HOOPS_WORLD->_hoops_HHPAH++;
	}
	~_hoops_PHPAH()
	{
		HOOPS_WORLD->display_list_vram_usage -= _hoops_RPAAH;
		HOOPS_WORLD->_hoops_HHPAH--;
		H_SAFE_RELEASE(m_d3dxmesh);
	}

	//_hoops_PIGS _hoops_ARR _hoops_RIR _hoops_AASGR
	bool _hoops_CAIRR (H3DData *h3ddata,
						UINT point_count, 
						UINT face_count,
						H3DVertexFormat VF)
	{
		DX9Data *dx9data = (DX9Data *) h3ddata;
		HRESULT _hoops_IIRHP;

		_hoops_RAIRR	= point_count;
		_hoops_GSHRR		= VF._hoops_HGHS();
		_hoops_AAIRR			= VF;

		do {
			 _hoops_IIRHP = D3DXCreateMeshFVF(
								face_count,
								point_count,
								D3DXMESH_32BIT | D3DXMESH_SYSTEMMEM,
								_hoops_GIAAH(VF),
								dx9data->pDevice,
								&m_d3dxmesh);
		} while (_hoops_IIRHP == D3DERR_NOTAVAILABLE);
		return SUCCEEDED(_hoops_IIRHP);
	}


	bool LockIndexBuffer(UINT _hoops_SAIRR, UINT _hoops_GPIRR, H3DIndexBuffer *_hoops_RAHC, UINT Flags)
	{
		UNREFERENCED(_hoops_SAIRR);
		UNREFERENCED(_hoops_GPIRR);
		void *p;

		_hoops_GSPP = H3DFMT_INDEX32;

		HRESULT _hoops_IIRHP = m_d3dxmesh->LockIndexBuffer(Flags, (void**)&p);
		ASSERT (p != null);
		_hoops_RAHC->_hoops_IRA(_hoops_GSPP, p);
		return SUCCEEDED(_hoops_IIRHP);
	}

	bool LockVertexBuffer(UINT _hoops_SAIRR, UINT _hoops_GPIRR, H3DVertexBuffer *_hoops_PAIH, UINT Flags)
	{
		UNREFERENCED(_hoops_SAIRR);
		UNREFERENCED(_hoops_GPIRR);
		float *data;
		HRESULT _hoops_IIRHP = m_d3dxmesh->LockVertexBuffer(Flags, (void**)&data);
		ASSERT (data != null);
		_hoops_PAIH->_hoops_IRA(data, &_hoops_AAIRR);
		return SUCCEEDED(_hoops_IIRHP);
	}

	void UnlockIndexBuffer()
	{
		m_d3dxmesh->UnlockIndexBuffer();
	}

	void UnlockVertexBuffer()
	{
		m_d3dxmesh->UnlockVertexBuffer();
	}

	bool CreateVertexBuffer (H3DData *h3ddata,
								UINT point_count, 
								H3DVertexFormat VF)
	{
		UNREFERENCED(h3ddata);
		UNREFERENCED(point_count);
		UNREFERENCED(VF);
		return false;
	};
	bool CreateIndexBuffer (H3DData *h3ddata,
								H3DPRIMITIVETYPE type, 
								UINT size,
								UINT count)
	{
		UNREFERENCED(h3ddata);
		UNREFERENCED(type);
		UNREFERENCED(size);
		UNREFERENCED(count);
		return false;
	};
	void _hoops_CHSA(H3DData *h3ddata, Test *cull_results = null)
	{
		UNREFERENCED(h3ddata);
		UNREFERENCED(cull_results);
	}
	void _hoops_GPAS(H3DData *h3ddata, float _hoops_RPIRR = 1.0)
	{
		UNREFERENCED(h3ddata);
		UNREFERENCED(_hoops_RPIRR);
	}
};



void _hoops_SGPAR(H3DData *h3ddata);

// _hoops_RGR _hoops_HRGR _hoops_RH _hoops_SRHR _hoops_CARA _hoops_PIH _hoops_HRPR _hoops_PGAP _hoops_RIAH _hoops_RH _hoops_GPHA _hoops_PPR _hoops_CIHA _hoops_PSCA
// _hoops_IHPAH _hoops_PCCP _hoops_RSIR _hoops_AASGR _hoops_PAR _hoops_CSHS
class _hoops_CHPAH : public H3DIndexedBufferObject
{
public:
	IDirect3DVertexBuffer9					*m_vtx_buff;
	hdx9_indexed_primitive					*_hoops_SHPAH;

	_hoops_CHPAH() 
	{
		HOOPS_WORLD->display_list_vram_usage += _hoops_RPAAH;
		HOOPS_WORLD->_hoops_HHPAH++;
		_hoops_SHPAH = null;
	}
	~_hoops_CHPAH()
	{
		H_SAFE_RELEASE(m_vtx_buff);
		HOOPS_WORLD->display_list_vram_usage -= _hoops_RPAAH;
		HOOPS_WORLD->_hoops_HHPAH--;
		HOOPS_WORLD->display_list_vram_usage -= (_hoops_GSHRR * _hoops_RAIRR);

		if (_hoops_SHPAH) {
			HOOPS_WORLD->display_list_vram_usage -= _hoops_SHPAH->size;
			H_SAFE_RELEASE(_hoops_SHPAH->idx_buff);
			_hoops_HP(_hoops_SHPAH);
		}
	}

	//_hoops_PIGS _hoops_ARR _hoops_RIR _hoops_IAIRR
	bool CreateVertexBuffer (H3DData *h3ddata,
								UINT point_count, 
								H3DVertexFormat VF)
	{
		DX9Data *dx9data = (DX9Data *) h3ddata;
		_hoops_RAIRR	= point_count;
		_hoops_GSHRR		= VF._hoops_HGHS();
		_hoops_AAIRR			= VF;		//_hoops_RH _hoops_GIPAH _hoops_GPHA _hoops_RPCC
		HRESULT _hoops_IIRHP;
		ASSERT (point_count > 0);
		do {
			_hoops_IIRHP = dx9data->pDevice->CreateVertexBuffer(
													point_count*_hoops_GSHRR, 
													D3DUSAGE_WRITEONLY,  
													_hoops_GIAAH(VF), 
													_hoops_PPAAH,
													&m_vtx_buff, 
													NULL);
		} while (_hoops_IIRHP == D3DERR_NOTAVAILABLE);

		if (_hoops_IIRHP == E_OUTOFMEMORY)
			HOOPS_WORLD->_hoops_PHARR = HOOPS_WORLD->display_list_vram_usage + (_hoops_GSHRR * _hoops_RAIRR) - 1;
		else
			HOOPS_WORLD->display_list_vram_usage += (_hoops_GSHRR * _hoops_RAIRR);
		
		_hoops_HAIRR &= SUCCEEDED(_hoops_IIRHP);
		return _hoops_HAIRR;
	}

	//_hoops_PIGS _hoops_GARI->_hoops_IIRGR _hoops_IACH _hoops_RIR _hoops_IAIRR
	bool CreateIndexBuffer (H3DData *h3ddata,
							   H3DPRIMITIVETYPE type, 
							   UINT length,
							   UINT count)
	{
		// _hoops_CSH _hoops_PPSR _hoops_SGP _hoops_PCCP _hoops_CIHA _hoops_SRHR _hoops_RPP _hoops_RH _hoops_GPHA _hoops_SRHR _hoops_AIAH _hoops_SRSH
		if (!_hoops_SGPS())
			return false;

		DX9Data *dx9data = (DX9Data *) h3ddata;
		IDirect3DIndexBuffer9* pIndexBuffer;
		D3DCAPS9 _hoops_ACGH;
		dx9data->pDevice->GetDeviceCaps(&_hoops_ACGH);

		if (_hoops_RAIRR > _hoops_ACGH.MaxVertexIndex)
			HE_ERROR(HEC_DX9_DRIVER, HEC_DX9_DRIVER,
			"Internal error: point count exceeds maximum vertex index.");

		if (_hoops_RAIRR <= 0x0000ffff && count <= 0x0000ffff)
			_hoops_GSPP = H3DFMT_INDEX16;
		else
			_hoops_GSPP = H3DFMT_INDEX32;


		hdx9_indexed_primitive * _hoops_CSHPP = POOL_NEW(dx9data->dc->memory_pool, hdx9_indexed_primitive)();
		_hoops_CSHPP->type = type;
		_hoops_CSHPP->size = length * ((_hoops_GSPP == H3DFMT_INDEX16) ? sizeof(short) : sizeof(int));
		_hoops_CSHPP->count = count;
		_hoops_SHPAH = _hoops_CSHPP;

		HRESULT _hoops_IIRHP;
		do {
			_hoops_IIRHP = dx9data->pDevice->CreateIndexBuffer(
													_hoops_CSHPP->size, 
													D3DUSAGE_WRITEONLY,  
													d3dformat(_hoops_GSPP), 
													_hoops_PPAAH,
													&pIndexBuffer, 
													NULL);
		} while (_hoops_IIRHP == D3DERR_NOTAVAILABLE);
		_hoops_CSHPP->idx_buff = pIndexBuffer;

		if (_hoops_IIRHP == E_OUTOFMEMORY) {
			_hoops_CAAI (HOOPS_WORLD->_hoops_PIPSA);
			HOOPS_WORLD->_hoops_PHARR = HOOPS_WORLD->display_list_vram_usage + (_hoops_CSHPP->size) - 1;
			_hoops_APAI (HOOPS_WORLD->_hoops_PIPSA);
		}
		else
			HOOPS_WORLD->display_list_vram_usage += (_hoops_CSHPP->size);

		_hoops_HAIRR &= SUCCEEDED(_hoops_IIRHP);
		return _hoops_HAIRR;
	}

	bool LockIndexBuffer(UINT _hoops_SAIRR, UINT _hoops_GPIRR, H3DIndexBuffer *_hoops_RAHC, UINT Flags)
	{
		void *p;
		HRESULT _hoops_IIRHP = _hoops_SHPAH->idx_buff->Lock(_hoops_SAIRR, _hoops_GPIRR, &p, Flags);
		ASSERT (p != null);
		_hoops_RAHC->_hoops_IRA(_hoops_GSPP, p);
		return SUCCEEDED(_hoops_IIRHP);
	}

	bool LockVertexBuffer(UINT _hoops_SAIRR, UINT _hoops_GPIRR, H3DVertexBuffer *_hoops_PAIH, UINT Flags)
	{
		float *data = null;
		HRESULT _hoops_IIRHP = m_vtx_buff->Lock(_hoops_SAIRR, _hoops_GPIRR, (void **) &data, Flags);
		ASSERT (data != null);
		_hoops_PAIH->_hoops_IRA(data, &_hoops_AAIRR);
		return SUCCEEDED(_hoops_IIRHP);
	}

	void UnlockIndexBuffer()
	{
		if (_hoops_SHPAH)
			_hoops_SHPAH->idx_buff->Unlock();
	}

	void UnlockVertexBuffer()
	{
		m_vtx_buff->Unlock();
	}

	void _hoops_CHSA(H3DData *h3ddata, Test *cull_results = null)
	{
		DX9Data *dx9data = (DX9Data *) h3ddata;
		Display_Context *dc = (Display_Context *)dx9data->dc;
		_hoops_GCHC(dx9data, _hoops_AAIRR);
		_hoops_HAPAH(dx9data, 0, m_vtx_buff, _hoops_GSHRR);

		if (_hoops_SHPAH)
			dx9data->pDevice->SetIndices(_hoops_SHPAH->idx_buff);

		if (cull_results == null || _hoops_SHPAH == null) {
			if (_hoops_SHPAH) {
				switch (_hoops_SHPAH->type) {
					case H3DPT_TRIANGLELIST:
					case H3DPT_TRIANGLESTRIP:
						_hoops_RCCA(_hoops_AGCAR) += _hoops_SHPAH->count;
						if (dc->_hoops_PGCAR > 0 &&
							_hoops_RCCA(_hoops_AGCAR) > _hoops_RCCA(_hoops_HGCAR)+dc->_hoops_PGCAR) {
							_hoops_RCCA(_hoops_HGCAR) = _hoops_RCCA(_hoops_AGCAR);
							_hoops_RCCA(_hoops_IGCAR)++;
							_hoops_SGPAR(h3ddata);
						}
						break;
					case H3DPT_LINELIST:
					case H3DPT_LINESTRIP:
						_hoops_RCCA(_hoops_AHRGH) += _hoops_SHPAH->count;
						break;
					default:
						ASSERT(0);
						break;
				}

				dx9data->pDevice->DrawIndexedPrimitive (
									d3dprimitive(_hoops_SHPAH->type), 
									0, 
									0, 
									_hoops_RAIRR, 
									0, 
									_hoops_SHPAH->count);
			}
			else {
				dx9data->pDevice->DrawPrimitive (
									D3DPT_POINTLIST,
									0,
									_hoops_RAIRR);
			}
		}
		else {
			int prev = 0;
			int len = 0;
			int i = 0;  //0.._hoops_RIPAH->_hoops_RPR
			int k = 0;  //0.._hoops_AIPAH
			int _hoops_PGHS = 0;

			for (;;) {
				if (_hoops_RPHS) {
					if (_hoops_IAHS && 
						_hoops_IAHS->_hoops_ACHS) {
						while (k < _hoops_SAHS) {
							while (_hoops_IAHS->_hoops_ACHS[i] > 0)
								i++;

							if (_hoops_RRIRR(cull_results[i + _hoops_GPHS])) {
								len = _hoops_RPHS[k] - prev;				
								k++;
								i++;
							}
							else
								break;
						}
					}
					else {
						while (k < _hoops_SAHS && 
							_hoops_RRIRR(cull_results[k + _hoops_GPHS])) {
								len = _hoops_RPHS[k] - prev;				
								k++;
						}
					}

					// _hoops_PIPAH _hoops_SR _hoops_SRSH _hoops_GPP _hoops_IRS _hoops_IAPRR _hoops_RPGP, _hoops_PAR _hoops_SR _hoops_PPHRH _hoops_APCRR. _hoops_GPGP _hoops_GIPR _hoops_ARAR, _hoops_SR
					// _hoops_RRP _hoops_IS _hoops_CAHA _hoops_GGSR _hoops_PCPA _hoops_SPCC _hoops_IIGR _hoops_RH _hoops_CGHI _hoops_PAIRR _hoops_IS _hoops_SHH _hoops_CHCC, _hoops_PPR _hoops_GGCR _hoops_IS _hoops_RH
					// _hoops_APSR _hoops_SPCC.
					if (k == _hoops_SAHS) {
						// _hoops_CR _hoops_SR _hoops_RGAR _hoops_ASH _hoops_RH _hoops_SRS _hoops_CIHA _hoops_IIGR _hoops_GRR _hoops_PAIRR, _hoops_SR _hoops_RRP _hoops_IS _hoops_CSGA
						// _hoops_RH _hoops_SPCC _hoops_IIGR _hoops_RH _hoops_CGHI _hoops_SPR (_hoops_GAR _hoops_SCH'_hoops_GRI _hoops_HAR _hoops_HIPAH _hoops_GCSS _hoops_GGR _hoops_RH _hoops_AII _hoops_CRPR)
						if (_hoops_GSPP == H3DFMT_INDEX32)
							len += ((_hoops_SHPAH->size >> 2) - _hoops_RPHS[k-1]); //_hoops_GHCH _hoops_HPP 4
						else
							len += ((_hoops_SHPAH->size >> 1) - _hoops_RPHS[k-1]); //_hoops_GHCH _hoops_HPP 2

					}
					else
						len = _hoops_RPHS[k] - prev;
				}
				else if (_hoops_RRIRR(cull_results[_hoops_GPHS])) {
					if (_hoops_GSPP == H3DFMT_INDEX32)
						len = (_hoops_SHPAH->size >> 2); //_hoops_GHCH _hoops_HPP 4
					else
						len = (_hoops_SHPAH->size >> 1); //_hoops_GHCH _hoops_HPP 2
				}

				if (len > 0) {
					switch (_hoops_SHPAH->type) {
						case H3DPT_TRIANGLELIST:
							_hoops_PGHS = len / 3;
							_hoops_RCCA(_hoops_AGCAR) += _hoops_PGHS;
							if (dc->_hoops_PGCAR > 0 &&
								_hoops_RCCA(_hoops_AGCAR) > _hoops_RCCA(_hoops_HGCAR)+dc->_hoops_PGCAR) {
								_hoops_RCCA(_hoops_HGCAR) = _hoops_RCCA(_hoops_AGCAR);
								_hoops_RCCA(_hoops_IGCAR)++;
								_hoops_SGPAR(h3ddata);
							}
							break;
						case H3DPT_TRIANGLESTRIP:
							_hoops_PGHS = len - 2;
							_hoops_RCCA(_hoops_AGCAR) += _hoops_PGHS;
							if (dc->_hoops_PGCAR > 0 &&
								_hoops_RCCA(_hoops_AGCAR) > _hoops_RCCA(_hoops_HGCAR)+dc->_hoops_PGCAR) {
								_hoops_RCCA(_hoops_HGCAR) = _hoops_RCCA(_hoops_AGCAR);
								_hoops_RCCA(_hoops_IGCAR)++;
								_hoops_SGPAR(h3ddata);
							}
							break;
						case H3DPT_LINELIST:
							_hoops_PGHS = len / 2;
							_hoops_RCCA(_hoops_AHRGH) += _hoops_PGHS;
							break;
						case H3DPT_LINESTRIP:
							_hoops_PGHS = len - 1;
							_hoops_RCCA(_hoops_AHRGH) += _hoops_PGHS;
							break;
						default:
							ASSERT(0);
							break;
					}
					dx9data->pDevice->DrawIndexedPrimitive (
									d3dprimitive(_hoops_SHPAH->type), 
									0, 
									0, 
									_hoops_RAIRR, 
									prev, 
									_hoops_PGHS);
				}
				if (_hoops_RPHS == null)
					break;

				if (_hoops_IAHS && 
					_hoops_IAHS->_hoops_ACHS) {
					while (k < _hoops_SAHS) {
						while (_hoops_IAHS->_hoops_ACHS[i] > 0)
							i++;

						if (!_hoops_RRIRR(cull_results[i + _hoops_GPHS])) {
							prev = _hoops_RPHS[k];
							k++;
							i++;
						}
						else
							break;
					}
				}
				else {
					while (k < _hoops_SAHS && 
						!_hoops_RRIRR(cull_results[k + _hoops_GPHS])) {
							prev = _hoops_RPHS[k];
							k++;
					}
				}
				if (k == _hoops_SAHS)
					break;
			}
		}
	}

	void _hoops_GPAS( H3DData *h3ddata, float _hoops_RPIRR = 1.0f)
	{
		DX9Data *dx9data = (DX9Data *) h3ddata;
		_hoops_GCHC(dx9data, _hoops_AAIRR);
		_hoops_HAPAH(dx9data, 0, m_vtx_buff, _hoops_GSHRR);

		if (_hoops_SHPAH) {
			dx9data->pDevice->SetIndices(_hoops_SHPAH->idx_buff);
			dx9data->pDevice->DrawIndexedPrimitive (
								d3dprimitive(_hoops_SHPAH->type), 
								0, 
								0, 
								_hoops_RAIRR, 
								0, 
								_hoops_SHPAH->count * _hoops_RPIRR);
		}
		else {
			dx9data->pDevice->DrawPrimitive (
								D3DPT_POINTLIST,
								0,
								_hoops_RAIRR * _hoops_RPIRR);
		}
	}
};


// _hoops_RGR _hoops_HRGR _hoops_RH _hoops_HRSAR _hoops_GPHA _hoops_SRHR _hoops_IHAH, _hoops_IHGS _hoops_IGI _hoops_IH _hoops_RAR _hoops_AAR _hoops_CPAP
LPDIRECT3DVERTEXDECLARATION9 _hoops_IIPAH(DX9Data *dx9data, H3DVertexFormat VF, bool _hoops_GHIGR)
{
	LPDIRECT3DVERTEXDECLARATION9 result;

	int ei = 0;
	int _hoops_CIPAH = 0;
	int offset = 0;
	if (VF._hoops_IPIGR()) {
		dx9data->_hoops_CIAAH[ei].Stream = _hoops_CIPAH;
		dx9data->_hoops_CIAAH[ei].Offset = offset;
		dx9data->_hoops_CIAAH[ei].Type = D3DDECLTYPE_FLOAT3;
		dx9data->_hoops_CIAAH[ei].Method = D3DDECLMETHOD_DEFAULT;
		dx9data->_hoops_CIAAH[ei].Usage = D3DDECLUSAGE_POSITION;
		dx9data->_hoops_CIAAH[ei].UsageIndex = 0;
		ei++;
		if (!_hoops_GHIGR)
			_hoops_CIPAH++;
		else
			offset+=3;
	}
	if (VF._hoops_HHCP()) {
		dx9data->_hoops_CIAAH[ei].Stream = _hoops_CIPAH;
		dx9data->_hoops_CIAAH[ei].Offset = offset;
		dx9data->_hoops_CIAAH[ei].Type = D3DDECLTYPE_FLOAT3;
		dx9data->_hoops_CIAAH[ei].Method = D3DDECLMETHOD_DEFAULT;
		dx9data->_hoops_CIAAH[ei].Usage = D3DDECLUSAGE_NORMAL;
		dx9data->_hoops_CIAAH[ei].UsageIndex = 0;
		ei++;
		if (!_hoops_GHIGR)
			_hoops_CIPAH++;
		else
			offset+=3;
	}
	if (VF._hoops_SHCP()) {
		dx9data->_hoops_CIAAH[ei].Stream = _hoops_CIPAH;
		dx9data->_hoops_CIAAH[ei].Offset = offset;
		dx9data->_hoops_CIAAH[ei].Type = D3DDECLTYPE_D3DCOLOR;
		dx9data->_hoops_CIAAH[ei].Method = D3DDECLMETHOD_DEFAULT;
		dx9data->_hoops_CIAAH[ei].Usage = D3DDECLUSAGE_COLOR;
		dx9data->_hoops_CIAAH[ei].UsageIndex = 0;
		offset += 1;
		ei++;
	}
	for (int i = 0; i < VF._hoops_APIGR(); i++) {
		int type = D3DDECLTYPE_FLOAT1;
		switch(VF._hoops_CPIGR(i)) {
			case 2: type = D3DDECLTYPE_FLOAT2; break;
			case 3: type = D3DDECLTYPE_FLOAT3; break;
			case 4: type = D3DDECLTYPE_FLOAT4; break;
		}
		dx9data->_hoops_CIAAH[ei].Stream = _hoops_CIPAH;
		dx9data->_hoops_CIAAH[ei].Offset = offset*4;
		dx9data->_hoops_CIAAH[ei].Type = type;
		dx9data->_hoops_CIAAH[ei].Method = D3DDECLMETHOD_DEFAULT;
		dx9data->_hoops_CIAAH[ei].Usage = D3DDECLUSAGE_TEXCOORD;
		dx9data->_hoops_CIAAH[ei].UsageIndex = i;
		offset += VF._hoops_CPIGR(i);
		ei++;
	}
	//_hoops_SIPAH()
	dx9data->_hoops_CIAAH[ei].Stream = 0xFF;
	dx9data->_hoops_CIAAH[ei].Offset = 0;
	dx9data->_hoops_CIAAH[ei].Type = D3DDECLTYPE_UNUSED;
	dx9data->_hoops_CIAAH[ei].Method = 0;
	dx9data->_hoops_CIAAH[ei].Usage = 0;
	dx9data->_hoops_CIAAH[ei].UsageIndex = 0;

	dx9data->pDevice->CreateVertexDeclaration(dx9data->_hoops_CIAAH, &result);
	return result;
}

#if 0
class _hoops_SAAAH : public H3DVertexBufferCache
{
public:
	_hoops_SAAAH()
	{
		HOOPS_WORLD->display_list_vram_usage += _hoops_RPAAH;
		HOOPS_WORLD->_hoops_HHPAH++;
		m_pVertexBuffer = 0;
		_hoops_GRIC	= 0;
		_hoops_PPIH = 0;
		_hoops_APIH = 0;
	}

	~_hoops_SAAAH()
	{
		HOOPS_WORLD->display_list_vram_usage -= _hoops_RPAAH;
		HOOPS_WORLD->_hoops_HHPAH--;
		H_SAFE_RELEASE(m_pVertexBuffer);
		HOOPS_WORLD->display_list_vram_usage -= (_hoops_GRIC * _hoops_CPIRR);
	}

	bool CreateVertexBuffer(H3DData *h3ddata, UINT _hoops_APIRR, 
		H3DVertexFormat VF)
	{
		H_SAFE_RELEASE(m_pVertexBuffer);
		DX9Data *dx9data = (DX9Data *) h3ddata;

		_hoops_GRIC	= _hoops_APIRR;
		_hoops_CPIRR = VF._hoops_HGHS();
		_hoops_AAIRR			= VF;
		HRESULT _hoops_IIRHP = dx9data->pDevice->CreateVertexBuffer(_hoops_GRIC*_hoops_CPIRR, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,  
												_hoops_GIAAH(VF), D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL);

		HOOPS_WORLD->display_list_vram_usage += (_hoops_GRIC * _hoops_CPIRR);
		return !FAILED(_hoops_IIRHP);
	}

	bool Reset()
	{
		H_SAFE_RELEASE(m_pVertexBuffer);
		HOOPS_WORLD->display_list_vram_usage -= (_hoops_GRIC * _hoops_CPIRR);

		_hoops_GRIC	= 0;
		_hoops_PPIH = 0;
		_hoops_APIH = 0;
		return true;
	}

	bool _hoops_RIAC()
	{
		_hoops_PPIH = 0;
		_hoops_APIH = 0;
		void * _hoops_PIAHP;
		m_pVertexBuffer->Lock((UINT)_hoops_PPIH, 0, &_hoops_PIAHP, D3DLOCK_DISCARD);
		m_pVertexBuffer->Unlock();
		return true;
	}

	bool Lock(UINT count, H3DVertexBuffer *_hoops_PAIH)
	{
		float *_hoops_GIIGR = null;

		// _hoops_HGH _hoops_RH _hoops_IGIR _hoops_IIGR _hoops_PIH _hoops_IS _hoops_SHH _hoops_RIPPR _hoops_CRGR _hoops_RH _hoops_GPHA _hoops_SRHR.
		UINT data_size = count * _hoops_CPIRR;

		// _hoops_CSH _hoops_IIIAA _hoops_GRS _hoops_SHH _hoops_IGI _hoops_RPP _hoops_RH _hoops_GIHA _hoops_PAH _hoops_SIHRR _hoops_CRGR 
		//		 _hoops_RH _hoops_GC _hoops_HHRPA _hoops_GGR _hoops_RH _hoops_GPHA _hoops_SRHR.
		DWORD _hoops_GCPAH = D3DLOCK_NOOVERWRITE;

		// _hoops_ARGH _hoops_IS _hoops_CACH _hoops_RPP _hoops_RH _hoops_RSIR _hoops_GPHA _hoops_SRHR _hoops_SSCP _hoops_RPII _hoops_IGI _hoops_GH _hoops_GAPR.
		if (_hoops_PPIH > (_hoops_GRIC*_hoops_CPIRR - data_size))
		{
			// _hoops_CSH _hoops_GC _hoops_IGICR. _hoops_GCIH _hoops_IAPR _hoops_HII _hoops_RH _hoops_RSGI 
			//		 _hoops_IIGR _hoops_RH _hoops_GPHA _hoops_SRHR.
			_hoops_GCPAH = D3DLOCK_DISCARD;
			_hoops_APIH = 0;
			_hoops_PPIH = 0;
		}

		// _hoops_HRAH _hoops_RH _hoops_GPHA _hoops_SRHR.
		HRESULT _hoops_IIRHP;
		if (FAILED(_hoops_IIRHP = m_pVertexBuffer->Lock((UINT)_hoops_PPIH, data_size, 
			(void **) &_hoops_GIIGR, _hoops_GCPAH)))
			return false;
		ASSERT (_hoops_GIIGR != null);
		_hoops_PAIH->_hoops_IRA(_hoops_GIIGR, &_hoops_AAIRR);

		// _hoops_RCPAH _hoops_IS _hoops_RH _hoops_SPS _hoops_AHC _hoops_GGR _hoops_RH _hoops_GPHA _hoops_SRHR.
		_hoops_PPIH += data_size;

		return true;
	}

	bool Unlock(VOID)
	{
		return !FAILED(m_pVertexBuffer->Unlock());
	}

	bool _hoops_CHSA(H3DData *h3ddata , H3DPRIMITIVETYPE _hoops_HPIRR, UINT _hoops_IPIRR)
	{
		// _hoops_PCSS _hoops_RH _hoops_PICA.
		bool result = _hoops_HGSA(h3ddata, _hoops_HPIRR, _hoops_IPIRR);
		_hoops_CGSA();
		return result;
	}

	bool _hoops_HGSA(H3DData *h3ddata , H3DPRIMITIVETYPE _hoops_HPIRR, UINT _hoops_IPIRR)
	{
		// _hoops_PCSS _hoops_RH _hoops_PICA.
		DX9Data *dx9data = (DX9Data *) h3ddata;
		_hoops_GCHC(dx9data, _hoops_AAIRR);
		_hoops_HAPAH(dx9data, m_pVertexBuffer, _hoops_CPIRR);
		HRESULT _hoops_IIRHP = dx9data->pDevice->DrawPrimitive(d3dprimitive(_hoops_HPIRR), _hoops_APIH/_hoops_CPIRR, _hoops_IPIRR);
		return !FAILED(_hoops_IIRHP);
	}

	void _hoops_CGSA()
	{
		_hoops_APIH = _hoops_PPIH;
	}

	IDirect3DVertexBuffer9  *m_pVertexBuffer;
};
#endif

class _hoops_SAAAH : public H3DVertexBufferCache
{
public:
	_hoops_SAAAH()
	{
		HOOPS_WORLD->display_list_vram_usage += _hoops_RPAAH;
		HOOPS_WORLD->_hoops_HHPAH++;
		m_pVertexBuffer = null;
		_hoops_ACPAH = null;
		_hoops_PCPAH = null;
		_hoops_GRIC	= 0;
		_hoops_PPIH = 0;
		_hoops_APIH = 0;
		_hoops_RHIRR = 0;
		_hoops_GHIRR = 0;
	}

	~_hoops_SAAAH()
	{
		HOOPS_WORLD->display_list_vram_usage -= _hoops_RPAAH;
		HOOPS_WORLD->_hoops_HHPAH--;
		H_SAFE_RELEASE(m_pVertexBuffer);
		H_SAFE_RELEASE(_hoops_ACPAH);
		H_SAFE_RELEASE(_hoops_PCPAH);
		H_SAFE_RELEASE(_hoops_HCPAH);
		if (_hoops_HHIRR)
			FREE_ARRAY_ALIGNED(_hoops_HHIRR, _hoops_GRIC*_hoops_CPIRR/4, float, 16);
		if (_hoops_IHIRR)
			FREE_ARRAY_ALIGNED(_hoops_IHIRR, _hoops_GRIC*_hoops_CPIRR/4, float, 16);
		HOOPS_WORLD->display_list_vram_usage -= (_hoops_GRIC * _hoops_CPIRR);
	}

	bool CreateVertexBuffer(H3DData *h3ddata, UINT _hoops_APIRR, 
		H3DVertexFormat VF)
	{
		H_SAFE_RELEASE(m_pVertexBuffer);
		DX9Data *dx9data = (DX9Data *) h3ddata;

		_hoops_GRIC		= _hoops_APIRR;
		_hoops_AAIRR				= VF;
		_hoops_HCPAH				= _hoops_IIPAH(dx9data, _hoops_AAIRR, false);
		_hoops_CPIRR		= 12;
		_hoops_SPIRR	= VF._hoops_HGHS(true, false);

		if (_hoops_AAIRR._hoops_IPIGR()) {
			dx9data->pDevice->CreateVertexBuffer(_hoops_GRIC*_hoops_CPIRR, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,  
												0, D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL);
			ALLOC_ARRAY_ALIGNED(_hoops_HHIRR, _hoops_GRIC*_hoops_CPIRR/4, float, 16);
		}
		if (_hoops_AAIRR._hoops_HHCP()) {
			dx9data->pDevice->CreateVertexBuffer(_hoops_GRIC*_hoops_CPIRR, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,  
												0, D3DPOOL_DEFAULT, &_hoops_ACPAH, NULL);
			ALLOC_ARRAY_ALIGNED(_hoops_IHIRR, _hoops_GRIC*_hoops_CPIRR/4, float, 16);
		}
		if (_hoops_AAIRR._hoops_PSCP()) {
			dx9data->pDevice->CreateVertexBuffer(_hoops_GRIC*_hoops_SPIRR, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,  
												0, D3DPOOL_DEFAULT, &_hoops_PCPAH, NULL);
		}

		HOOPS_WORLD->display_list_vram_usage += (_hoops_GRIC * (_hoops_CPIRR+_hoops_SPIRR));
		return true;
	}

	bool Reset()
	{
		H_SAFE_RELEASE(m_pVertexBuffer);
		H_SAFE_RELEASE(_hoops_ACPAH);
		H_SAFE_RELEASE(_hoops_PCPAH);
		HOOPS_WORLD->display_list_vram_usage -= (_hoops_GRIC * (_hoops_CPIRR+_hoops_SPIRR));

		_hoops_GRIC	= 0;
		_hoops_PPIH = 0;
		_hoops_APIH = 0;
		_hoops_RHIRR = 0;
		_hoops_GHIRR = 0;
		_hoops_PHIRR = 0;
		return true;
	}

	bool _hoops_RIAC()
	{
		_hoops_PHIRR = 0;
		_hoops_PPIH = 0;
		_hoops_APIH = 0;
		_hoops_RHIRR= 0;
		_hoops_GHIRR = 0;
		void * _hoops_PIAHP;
		m_pVertexBuffer->Lock((UINT)_hoops_PPIH, 0, &_hoops_PIAHP, D3DLOCK_DISCARD);
		m_pVertexBuffer->Unlock();
		if (_hoops_ACPAH) {
			_hoops_ACPAH->Lock((UINT)_hoops_PPIH, 0, &_hoops_PIAHP, D3DLOCK_DISCARD);
			_hoops_ACPAH->Unlock();
		}
		if (_hoops_PCPAH) {
			_hoops_PCPAH->Lock((UINT)_hoops_RHIRR, 0, &_hoops_PIAHP, D3DLOCK_DISCARD);
			_hoops_PCPAH->Unlock();
		}
		return true;
	}

	bool _hoops_PPIRR(_hoops_HRPA const *matrix = null, int length = -1)
	{
		bool result = true;
		int _hoops_ICPAH = (length >= 0) ? length : _hoops_AHIRR/_hoops_CPIRR;
		_hoops_ICPAH -= _hoops_PHIRR;
		if (_hoops_ICPAH <= 0)
			return true;
		ASSERT (_hoops_ICPAH > 0);

		int offset = _hoops_PHIRR*3;
		if (matrix)
			HI_Compute_Transformed_Points(_hoops_ICPAH, (Point*)(_hoops_HHIRR+offset), &matrix->elements[0][0], (Point*)(_hoops_SHIRR+offset));
		else
			COPY_MEMORY(_hoops_HHIRR+offset, _hoops_ICPAH*_hoops_CPIRR, _hoops_SHIRR+offset);
		
		if (_hoops_AAIRR._hoops_HHCP()) {
			if (matrix)
				HI_Compute_Transformed_Vectors(_hoops_ICPAH, (Vector*)(_hoops_IHIRR+offset), &matrix->_hoops_APRA->data.elements[0][0], (Vector*)(_hoops_GIIRR+offset));
			else
				COPY_MEMORY(_hoops_IHIRR+offset, _hoops_ICPAH*_hoops_CPIRR, _hoops_GIIRR+offset);
		}

		_hoops_PHIRR += _hoops_ICPAH;
		return result;
	}

	bool Lock(UINT count, H3DVertexBuffer *_hoops_PAIH)
	{
		_hoops_PHIRR = 0;

		// _hoops_HGH _hoops_RH _hoops_IGIR _hoops_IIGR _hoops_PIH _hoops_IS _hoops_SHH _hoops_RIPPR _hoops_CRGR _hoops_RH _hoops_GPHA _hoops_SRHR.
		UINT data_size = count * _hoops_CPIRR;
		UINT _hoops_CCPAH = count * _hoops_SPIRR;

		// _hoops_CSH _hoops_IIIAA _hoops_GRS _hoops_SHH _hoops_IGI _hoops_RPP _hoops_RH _hoops_GIHA _hoops_PAH _hoops_SIHRR _hoops_CRGR 
		//		 _hoops_RH _hoops_GC _hoops_HHRPA _hoops_GGR _hoops_RH _hoops_GPHA _hoops_SRHR.
		DWORD _hoops_GCPAH = D3DLOCK_NOOVERWRITE;

		// _hoops_ARGH _hoops_IS _hoops_CACH _hoops_RPP _hoops_RH _hoops_RSIR _hoops_GPHA _hoops_SRHR _hoops_SSCP _hoops_RPII _hoops_IGI _hoops_GH _hoops_GAPR.
		if (_hoops_PPIH > (_hoops_GRIC*_hoops_CPIRR - data_size))
		{
			// _hoops_CSH _hoops_GC _hoops_IGICR. _hoops_GCIH _hoops_IAPR _hoops_HII _hoops_RH _hoops_RSGI 
			//		 _hoops_IIGR _hoops_RH _hoops_GPHA _hoops_SRHR.
			_hoops_GCPAH = D3DLOCK_DISCARD;
			_hoops_APIH = 0;
			_hoops_PPIH = 0;

			_hoops_GHIRR = 0;
			_hoops_RHIRR = 0;
		}

		// _hoops_HRAH _hoops_RH _hoops_GPHA _hoops_SRHR.
		HRESULT _hoops_IIRHP;
		if (FAILED(_hoops_IIRHP = m_pVertexBuffer->Lock((UINT)_hoops_PPIH, data_size, 
			(void **) &_hoops_SHIRR, _hoops_GCPAH)))
			return false;
		if (_hoops_ACPAH) {
			if (FAILED(_hoops_IIRHP = _hoops_ACPAH->Lock((UINT)_hoops_PPIH, data_size, 
				(void **) &_hoops_GIIRR, _hoops_GCPAH)))
				return false;
		}
		if (_hoops_PCPAH) {
			if (FAILED(_hoops_IIRHP = _hoops_PCPAH->Lock((UINT)_hoops_RHIRR, _hoops_CCPAH, 
				(void **) &_hoops_RIIRR, _hoops_GCPAH)))
				return false;
		}
		
		_hoops_AHIRR = data_size;
			
		ASSERT (_hoops_SHIRR != null);
		_hoops_PAIH->_hoops_IRA(_hoops_HHIRR,_hoops_IHIRR,_hoops_RIIRR, &_hoops_AAIRR);

		// _hoops_RCPAH _hoops_IS _hoops_RH _hoops_SPS _hoops_AHC _hoops_GGR _hoops_RH _hoops_GPHA _hoops_SRHR.
		_hoops_PPIH += data_size;
		_hoops_RHIRR += _hoops_CCPAH;

		// _hoops_ACGR _hoops_SPS _hoops_PPCAR 12-_hoops_RAPSR _hoops_PPR 16-_hoops_RAPSR _hoops_AHSGP (_hoops_CHGC _hoops_PPCAR _hoops_GPGR _hoops_IIGR 12 _hoops_PPR 16 > _hoops_SCPAH)
		if (_hoops_PPIH % 16 || _hoops_PPIH % 12) {
			int start = _hoops_PPIH;
			int _hoops_GSPAH = 0;

			// _hoops_RSPAH _hoops_IS _hoops_SPS 16 _hoops_RAPSR _hoops_AHSGP
			_hoops_PPIH += (16 - (_hoops_PPIH % 16));

			// _hoops_ACGR _hoops_SPS 16 _hoops_RAPSR _hoops_AHSGP _hoops_SGS'_hoops_GRI _hoops_GACC 12 _hoops_RAPSR _hoops_RGCGA
			while (_hoops_PPIH % 12)
				_hoops_PPIH += 16;

			_hoops_GSPAH = (_hoops_PPIH - start) / 12;
			_hoops_RHIRR += _hoops_GSPAH * _hoops_SPIRR;
		}

		return true;
	}

	bool Unlock(_hoops_HRPA const *matrix = null)
	{
		bool result = true;

		_hoops_PPIRR(matrix);
		m_pVertexBuffer->Unlock();
		
		if (_hoops_ACPAH)
			_hoops_ACPAH->Unlock();

		if (_hoops_PCPAH)
			result &= SUCCEEDED(_hoops_PCPAH->Unlock());
		return result;
	}

	int _hoops_ASPAH()
	{
		return  _hoops_APIH/_hoops_CPIRR;
	}

	void _hoops_PSPAH(H3DData *h3ddata)
	{
		DX9Data *dx9data = (DX9Data *) h3ddata;
		dx9data->pDevice->SetVertexDeclaration(_hoops_HCPAH);
		dx9data->_hoops_CSC->_hoops_PPCP = H3DVertexFormat();
	}
	void _hoops_HSPAH(H3DData *h3ddata)
	{
		DX9Data *dx9data = (DX9Data *) h3ddata;
		int _hoops_CIPAH = 0;
		if (_hoops_AAIRR._hoops_IPIGR()) {
			_hoops_HAPAH(dx9data, _hoops_CIPAH, m_pVertexBuffer, _hoops_CPIRR);
			_hoops_CIPAH++;
		}
		if (_hoops_AAIRR._hoops_HHCP()) {
			_hoops_HAPAH(dx9data, _hoops_CIPAH, _hoops_ACPAH, _hoops_CPIRR);
			_hoops_CIPAH++;
		}
		if (_hoops_AAIRR._hoops_PSCP()) {
			_hoops_HAPAH(dx9data, _hoops_CIPAH, _hoops_PCPAH, _hoops_SPIRR);
			_hoops_CIPAH++;
		}
	}

	bool _hoops_CHSA(H3DData *h3ddata , H3DPRIMITIVETYPE _hoops_HPIRR, UINT _hoops_IPIRR)
	{
		// _hoops_PCSS _hoops_RH _hoops_PICA.
		bool result = _hoops_HGSA(h3ddata, _hoops_HPIRR, _hoops_IPIRR);
		_hoops_CGSA();
		return result;
	}

	bool _hoops_HGSA(H3DData *h3ddata , H3DPRIMITIVETYPE _hoops_HPIRR, UINT _hoops_IPIRR)
	{
		// _hoops_PCSS _hoops_RH _hoops_PICA.
		DX9Data *dx9data = (DX9Data *) h3ddata;
		_hoops_HSPAH(dx9data);
		_hoops_PSPAH(dx9data);
		HRESULT _hoops_IIRHP = dx9data->pDevice->DrawPrimitive(d3dprimitive(_hoops_HPIRR), _hoops_ASPAH(), _hoops_IPIRR);
		return !FAILED(_hoops_IIRHP);
	}

	void _hoops_CGSA()
	{
		_hoops_APIH = _hoops_PPIH;
		_hoops_GHIRR = _hoops_RHIRR;
	}

	IDirect3DVertexBuffer9  *m_pVertexBuffer;
	IDirect3DVertexBuffer9  *_hoops_ACPAH;
	IDirect3DVertexBuffer9  *_hoops_PCPAH;

	IDirect3DVertexDeclaration9 *_hoops_HCPAH;
};


// _hoops_PCCP _hoops_CIHA _hoops_SRHR, _hoops_IGI _hoops_GGR _hoops_ISPAH _hoops_CCA _hoops_IRS _hoops_CSPAH _hoops_CSHGR. _hoops_HAIC _hoops_SGH _hoops_GII _hoops_CSPAH
class _hoops_GPAAH : public H3DIndexBufferCache
{
public:
	_hoops_GPAAH()
	{
		HOOPS_WORLD->display_list_vram_usage += _hoops_RPAAH;
		HOOPS_WORLD->_hoops_HHPAH++;
		_hoops_SSPAH = 0;
		_hoops_GGHAH = 0;
		_hoops_RGHAH = 0;
	}

	~_hoops_GPAAH()
	{
		HOOPS_WORLD->display_list_vram_usage -= _hoops_RPAAH;
		HOOPS_WORLD->_hoops_HHPAH--;
		HOOPS_WORLD->display_list_vram_usage -= (_hoops_GHIH * sizeof(short));
		H_SAFE_RELEASE(_hoops_SSPAH);
	}

	bool CreateIndexBuffer(H3DData *h3ddata)
	{
		HRESULT _hoops_IIRHP = S_OK;
		DX9Data *dx9data = (DX9Data *) h3ddata;
		LPDIRECT3DDEVICE9 pDevice = dx9data->pDevice;

		ASSERT(_hoops_GHIH < 0x0000ffff);	//_hoops_CIHA _hoops_SRHR _hoops_IHAH _hoops_RHAP _hoops_HAR _hoops_GCGH 32 _hoops_IGRH _hoops_PSPI
		if (_hoops_SSPAH == NULL)
			_hoops_IIRHP = pDevice->CreateIndexBuffer (
				_hoops_GHIH * sizeof(short), 
				D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, 
				D3DFMT_INDEX16,
				D3DPOOL_DEFAULT,
				&_hoops_SSPAH,
				NULL);

		HOOPS_WORLD->display_list_vram_usage += (_hoops_GHIH * sizeof(short));
		return SUCCEEDED(_hoops_IIRHP);
	}

	bool Lock(short count, short **_hoops_AIIRR)
	{
		HRESULT _hoops_IIRHP;
		int _hoops_AGHAH = count * sizeof(short);
		if (_hoops_GGHAH > (_hoops_GHIH * sizeof(short) - _hoops_AGHAH)) {
			_hoops_RGHAH = _hoops_GGHAH = 0;
			_hoops_IIRHP = _hoops_SSPAH->Lock(0, _hoops_AGHAH, (void **) _hoops_AIIRR, D3DLOCK_DISCARD);
		}
		else {
			_hoops_IIRHP = _hoops_SSPAH->Lock(_hoops_GGHAH, _hoops_AGHAH, (void **) _hoops_AIIRR, D3DLOCK_NOOVERWRITE);
		}
		ASSERT (_hoops_AIIRR != null);
		_hoops_GGHAH += _hoops_AGHAH;

		return SUCCEEDED(_hoops_IIRHP);
	}

	bool Unlock(VOID)
	{
		return SUCCEEDED(_hoops_SSPAH->Unlock());
	}

	bool _hoops_CHSA(H3DData *h3ddata , H3DPRIMITIVETYPE _hoops_HPIRR, 
		UINT _hoops_PIIRR,
		UINT _hoops_IPIRR)
	{
		DX9Data *dx9data = (DX9Data *) h3ddata;
		// _hoops_PCSS _hoops_RH _hoops_PICA.
		_hoops_PGHAH->_hoops_HSPAH(dx9data);
		_hoops_PGHAH->_hoops_PSPAH(dx9data);
		dx9data->pDevice->SetIndices (_hoops_SSPAH);
		HRESULT _hoops_IIRHP = dx9data->pDevice->DrawIndexedPrimitive (
			d3dprimitive(_hoops_HPIRR), 
			_hoops_PGHAH->_hoops_ASPAH(), 
			0, 
			_hoops_PIIRR, 
			_hoops_RGHAH/sizeof(short), 
			_hoops_IPIRR);
		return SUCCEEDED(_hoops_IIRHP);
	}

	void _hoops_CGSA()
	{
		_hoops_RGHAH = _hoops_GGHAH;
		_hoops_PGHAH->_hoops_CGSA();
	}

	void _hoops_GAPRR (H3DVertexBufferCache *_hoops_IRPRR)
	{
		_hoops_PGHAH = (_hoops_SAAAH *) _hoops_IRPRR;
	}

	IDirect3DIndexBuffer9	*_hoops_SSPAH;
	_hoops_SAAAH	*_hoops_PGHAH;
	UINT					_hoops_RGHAH;
	UINT					_hoops_GGHAH;
};


/*****************************************************************************
*****************************************************************************
						_hoops_GGHRH _hoops_ISHGR
*****************************************************************************
*****************************************************************************/
class _hoops_RGHRH : public H3DShader
{
protected:
	char const * _hoops_CAHR(){return "hlsl";};

public:
	IDirect3DDevice9 *m_pDevice;
	IDirect3DVertexShader9 *_hoops_AGHRH;
	IDirect3DPixelShader9 *_hoops_PGHRH;
	ID3DXConstantTable *m_pVSConstantTable;
	ID3DXConstantTable *m_pPSConstantTable;
	
	_hoops_RGHRH (const H3DShaderID& id);
	~_hoops_RGHRH ();

	bool Create (H3DData *h3ddata, const char *_hoops_IASRR = null);
	bool _hoops_HHIH (void);

	void _hoops_RAPRR (H3DTexture *texture, H3DData *h3ddata);
	void _hoops_GGIR(bool _hoops_AIAAR = false);

	void _hoops_RCAAR(H3D_Constant_Table table, int _hoops_HGHAH, int data)
	{
		if (_hoops_ISS->_hoops_SCRRR[_hoops_HGHAH] && EQUAL_MEMORY(_hoops_ISS->_hoops_CCRRR[_hoops_HGHAH], sizeof(int), &data))
			return;
		COPY_MEMORY(&data, sizeof(int), _hoops_ISS->_hoops_CCRRR[_hoops_HGHAH]);
		_hoops_ISS->_hoops_SCRRR[_hoops_HGHAH] = true;

		ID3DXConstantTable *dxtable = (table == H3D_PSConstant_Table) ? m_pPSConstantTable : m_pVSConstantTable;
		D3DXHANDLE dxhandle = (D3DXHANDLE) _hoops_CSC[_hoops_HGHAH];
		dxtable->SetInt(m_pDevice, dxhandle, data);
	}

	void _hoops_ACAAR(H3D_Constant_Table table, int _hoops_HGHAH, float data)
	{
		if (_hoops_ISS->_hoops_SCRRR[_hoops_HGHAH] && data == _hoops_ISS->_hoops_CCRRR[_hoops_HGHAH][0])
			return;
		_hoops_ISS->_hoops_CCRRR[_hoops_HGHAH][0] = data;
		_hoops_ISS->_hoops_SCRRR[_hoops_HGHAH] = true;

		ID3DXConstantTable *dxtable = (table == H3D_PSConstant_Table) ? m_pPSConstantTable : m_pVSConstantTable;
		D3DXHANDLE dxhandle = (D3DXHANDLE) _hoops_CSC[_hoops_HGHAH];
		dxtable->SetFloat(m_pDevice, dxhandle, data);
	}

	void _hoops_PCAAR(H3D_Constant_Table table, int _hoops_HGHAH, void const *data, int _hoops_HCAAR, int _hoops_GPIGR = 1)
	{
		int _hoops_IGHAH = _hoops_GPIGR;

		if (_hoops_HCAAR == H3D_Vector)
			_hoops_IGHAH = _hoops_GPIGR * 4;

		if (_hoops_IGHAH <= 16) {
			if (_hoops_ISS->_hoops_SCRRR[_hoops_HGHAH] && EQUAL_MEMORY(_hoops_ISS->_hoops_CCRRR[_hoops_HGHAH], _hoops_IGHAH * sizeof(float), (float *) data))
				return;
			COPY_MEMORY(data, _hoops_IGHAH * sizeof(float), _hoops_ISS->_hoops_CCRRR[_hoops_HGHAH]);
			_hoops_ISS->_hoops_SCRRR[_hoops_HGHAH] = true;
		}

		ID3DXConstantTable *dxtable = (table == H3D_PSConstant_Table) ? m_pPSConstantTable : m_pVSConstantTable;
		D3DXHANDLE dxhandle = (D3DXHANDLE) _hoops_CSC[_hoops_HGHAH];
		switch (_hoops_HCAAR) {
			case H3D_Integer:
				dxtable->SetIntArray(m_pDevice, dxhandle, (const INT *) data, _hoops_GPIGR);
				break;
			case H3D_Float:
				dxtable->SetFloatArray(m_pDevice, dxhandle, (const FLOAT *) data, _hoops_GPIGR);
				break;
			case H3D_Vector:
				if (_hoops_GPIGR == 1)
					dxtable->SetVector(m_pDevice, dxhandle, (const D3DXVECTOR4 *) data);
				else
					dxtable->SetVectorArray(m_pDevice, dxhandle, (const D3DXVECTOR4 *) data, _hoops_GPIGR);
				break;
			case H3D_Matrix:
				if (_hoops_GPIGR == 16)
					dxtable->SetMatrix(m_pDevice, dxhandle, (const D3DXMATRIX *) data);
				else
					dxtable->SetFloatArray(m_pDevice, dxhandle, (const FLOAT *) data, _hoops_GPIGR);

				// _hoops_CGHAH->_hoops_SGHAH(_hoops_GRHAH, _hoops_RRHAH, (_hoops_RCIC _hoops_ARHAH *) _hoops_PIH, _hoops_CIAAR);	//_hoops_HAR _hoops_GIR _hoops_GAPR
				break;
			default:
				ASSERT(0);
				break;
		}
	}

	void _hoops_ICAAR(H3D_Constant_Table table, int _hoops_HGHAH, float *data, int width) {
		_hoops_CCAAR(table, _hoops_HGHAH, data, 1, width);
	}
	void _hoops_CCAAR(H3D_Constant_Table table, int _hoops_HGHAH, float *data, int _hoops_SIIRR, int width) {
		_hoops_PCAAR(table, _hoops_HGHAH, data, H3D_Float, _hoops_SIIRR * width);
	}

	H3D_Shader_Handle GetConstantByName(H3D_Constant_Table table, char const * _hoops_SCAAR, char const * _hoops_GSAAR)
	{
		H3D_Shader_Handle handle = _hoops_SSRAR;
		if (table == H3D_PSConstant_Table)
			handle = (H3D_Shader_Handle) m_pPSConstantTable->GetConstantByName(_hoops_SCAAR, _hoops_GSAAR);
		else
			handle = (H3D_Shader_Handle) m_pVSConstantTable->GetConstantByName(_hoops_SCAAR, _hoops_GSAAR);

		if (handle == null)
			handle = _hoops_SSRAR;

		return handle;
	}
};



local void _hoops_PRHAH(Display_Context alter * dc);
local void _hoops_HRHAH(Display_Context alter * dc);




/*****************************************************************************
*****************************************************************************
							_hoops_IRHAH _hoops_ISHGR
*****************************************************************************
*****************************************************************************/
class _hoops_HIARH : public H3DRenderTarget
{
private:
	LPDIRECT3DSURFACE9	_hoops_PCC;

public:
	HRESULT _hoops_IIRHP;

public:

	_hoops_HIARH(H3DData *h3ddata, IDirect3DSurface9 *surface) : 
		H3DRenderTarget(h3ddata, 0, 0, 0, H3DFMT_A8B8G8R8, 0)
	{
		D3DSURFACE_DESC desc;
		surface->GetDesc(&desc);

		_hoops_IRRP = desc.Width;
		_hoops_CRRP = desc.Height;
		//_hoops_CRHAH = _hoops_SRHAH._hoops_GAHAH;
		_hoops_HSARR = desc.MultiSampleQuality;
		_hoops_PCC = surface;
	}

	_hoops_HIARH(H3DData *h3ddata, 
		unsigned int width, 
		unsigned int height,
		unsigned int _hoops_GCI,		// _hoops_RAHAH
		H3DFORMAT format,
		int _hoops_ISARR = 0,
		bool _hoops_AAHAH = false) :
		H3DRenderTarget(h3ddata, width, height, _hoops_GCI, format, _hoops_ISARR)
	{
		DX9Data *dx9data = (DX9Data *) h3ddata;
		bool _hoops_IA = true;

		if (_hoops_GCI == H3DTEXUSAGE_RENDERTARGET) {
			_hoops_IA = _hoops_IA && SUCCEEDED( _hoops_IIRHP = dx9data->pDevice->CreateRenderTarget( 
				width, height, d3dformat(format), 
				(D3DMULTISAMPLE_TYPE) _hoops_ISARR, 0, FALSE, &_hoops_PCC, null ) );
		}
		else if (_hoops_GCI == H3DTEXUSAGE_DEPTHSTENCIL) {
			_hoops_IA = _hoops_IA && SUCCEEDED( _hoops_IIRHP = dx9data->pDevice->CreateDepthStencilSurface( 
				width, height, d3dformat(format), 
				(D3DMULTISAMPLE_TYPE) _hoops_ISARR, 0, _hoops_AAHAH, &_hoops_PCC, null ) );
		}
		else
			ASSERT(0);
	}

	~_hoops_HIARH()
	{
		H_SAFE_RELEASE(_hoops_PCC);
	}

	H3D_SURFACE_ID _hoops_IIARH() {return _hoops_PCC;}
};


class _hoops_RIARH : public H3DTexture
{
private:
	LPDIRECT3DTEXTURE9 _hoops_PCC;
	D3DLOCKED_RECT _hoops_PAHAH;

public:
	HRESULT _hoops_IIRHP;

public:
	_hoops_RIARH(H3DData *h3ddata, 
		unsigned int width, 
		unsigned int height,
		unsigned int _hoops_ICRH,
		unsigned int _hoops_GCI,
		H3DFORMAT format) :
		H3DTexture(h3ddata, width, height, _hoops_ICRH, _hoops_GCI, format)
	{
		DX9Data *dx9data = (DX9Data *) h3ddata;
		_hoops_ISS = h3ddata;
		D3DFORMAT d3dformat = D3DFMT_A8R8G8B8;
		D3DPOOL pool = D3DPOOL_DEFAULT;
		unsigned int _hoops_HAHAH = 0;
		_hoops_SSARR = 4;

		if (BIT(_hoops_GCI, H3DTEXUSAGE_RENDERTARGET)) 
			_hoops_HAHAH = D3DUSAGE_RENDERTARGET;
		else if (BIT(_hoops_GCI, H3DTEXUSAGE_DEPTHSTENCIL))
			_hoops_HAHAH = D3DUSAGE_DEPTHSTENCIL;
		else
			pool = D3DPOOL_MANAGED;

		if (BIT(_hoops_GCI, H3DTEXUSAGE_AUTOGENMIPMAP))
			_hoops_HAHAH |= D3DUSAGE_AUTOGENMIPMAP;
		else
			// _hoops_CGP _hoops_SR _hoops_SPGA'_hoops_RA _hoops_PSCS _hoops_HCRH _hoops_HARH, _hoops_GA'_hoops_RA _hoops_ARPR _hoops_CAPR, _hoops_CR _hoops_RH _hoops_RHPP
			// _hoops_ASSP'_hoops_RA _hoops_CISA _hoops_GGR _hoops_PA _hoops_PRGAH _hoops_RH _hoops_SCIA _hoops_PAPA.
			_hoops_ICRH = 1;
		
		switch (format)
		{
			case H3DFMT_L8:
				d3dformat = D3DFMT_L8;
				_hoops_SSARR = 1;
				break;
			case H3DFMT_R8G8B8:
				if (dx9data->_hoops_CHGH) {
					d3dformat = D3DFMT_R8G8B8;
					_hoops_SSARR = 3;
					break;
				}
			case H3DFMT_A8R8G8B8:
				d3dformat = D3DFMT_A8R8G8B8;
				break;
			case H3DFMT_R32F:
				d3dformat = dx9data->_hoops_GAP ? D3DFMT_R32F : D3DFMT_A8R8G8B8;
				break;
			case H3DFMT_D24S8:
			case H3DFMT_D24X8:
				d3dformat = dx9data->_hoops_IIGAH;
				break;

			case H3DFMT_DXT1:
				d3dformat = D3DFMT_DXT1;
				_hoops_SSARR = -1;
				break;
			case H3DFMT_DXT3:
				d3dformat = D3DFMT_DXT3;
				_hoops_SSARR = -1;
				break;
			case H3DFMT_DXT5:
				d3dformat = D3DFMT_DXT5;
				_hoops_SSARR = -1;
				break;

			default:
				HE_ERROR(HEC_DX9_DRIVER, HEC_DX9_DRIVER, 
					"Internal error: unhandled DX9 texture format!");
		}

		_hoops_IIRHP = dx9data->pDevice->CreateTexture(width, height, _hoops_ICRH, _hoops_HAHAH,
			d3dformat, pool, &_hoops_PCC, NULL);
	}

	~_hoops_RIARH()
	{
		H_SAFE_RELEASE(_hoops_PCC);
	};

	bool Lock(int _hoops_SHGGR, unsigned char ** data)
	{
		UNREFERENCED(_hoops_SHGGR);
		HRESULT _hoops_IIRHP;
		_hoops_IIRHP = _hoops_PCC->LockRect(0, &_hoops_PAHAH, null, 0);
		*data = (unsigned char *) _hoops_PAHAH.pBits;
		return SUCCEEDED(_hoops_IIRHP);
	}

	bool Lock(H3DRect *_hoops_CGPRR, unsigned char ** data, int * pitch = null)
	{
		HRESULT _hoops_IIRHP;
		RECT rect;
		if (_hoops_CGPRR)
		{
			rect.top = _hoops_CGPRR->top;
			rect.bottom = _hoops_CGPRR->bottom;
			rect.right = _hoops_CGPRR->right;
			rect.left = _hoops_CGPRR->left;
			_hoops_IIRHP = _hoops_PCC->LockRect(0, &_hoops_PAHAH, &rect, 0);
		}
		else
			_hoops_IIRHP = _hoops_PCC->LockRect(0, &_hoops_PAHAH, null, 0);
		*data = (unsigned char *) _hoops_PAHAH.pBits;
		if (pitch)
			*pitch = _hoops_PAHAH.Pitch;
		return SUCCEEDED(_hoops_IIRHP);
	}

	void Unlock()
	{
		_hoops_PCC->UnlockRect(0);
		ZERO_STRUCT(&_hoops_PAHAH, D3DLOCKED_RECT);
	}

	void _hoops_APRH()
	{
		_hoops_PCC->GenerateMipSubLevels();
	}

	bool _hoops_CAAH(_hoops_RCR *txr) {
		LPDIRECT3DSURFACE9 surface;
		unsigned char *_hoops_IAHAH = (unsigned char *)txr->_hoops_RHGH->_hoops_PHGH;
		int _hoops_CAHAH = 0;

		_hoops_PCC->GetSurfaceLevel(0, &surface);

		RECT _hoops_SAHAH;
		_hoops_SAHAH.top = 0;
		_hoops_SAHAH.left = 0;
		_hoops_SAHAH.bottom = txr->_hoops_RHGH->height;
		_hoops_SAHAH.right = txr->_hoops_RHGH->width;

		D3DFORMAT format = D3DFMT_A8B8G8R8;
		if (txr->_hoops_RHGH->format == _hoops_HHGH) {
			format = D3DFMT_R8G8B8;

			// _hoops_CPGP _hoops_RAPA _hoops_ASSP'_hoops_RA _hoops_HS _hoops_IRS _hoops_GPHAH _hoops_RPCC, _hoops_SR _hoops_PIHA _hoops_GGSHR _hoops_RH _hoops_IGPC _hoops_IHAAR
			_hoops_CAHAH = txr->_hoops_RHGH->width*txr->_hoops_RHGH->height*txr->_hoops_RHGH->_hoops_GCPIR;
			ALLOC_ARRAY(_hoops_IAHAH, _hoops_CAHAH, unsigned char);

			for (int i = 0; i < txr->_hoops_RHGH->width*txr->_hoops_RHGH->height; i++) {
				_hoops_IAHAH[i*3+0] = ((unsigned char*) txr->_hoops_RHGH->_hoops_PHGH)[i*3+2];
				_hoops_IAHAH[i*3+1] = ((unsigned char*) txr->_hoops_RHGH->_hoops_PHGH)[i*3+1];
				_hoops_IAHAH[i*3+2] = ((unsigned char*) txr->_hoops_RHGH->_hoops_PHGH)[i*3+0];
			}
		}
		if (txr->_hoops_RHGH->format == _hoops_AHGH) {
			format = D3DFMT_L8;
		}
		HRESULT _hoops_IIRHP = D3DXLoadSurfaceFromMemory(surface, null, null,
			_hoops_IAHAH, format, txr->_hoops_RHGH->row_bytes, null, &_hoops_SAHAH,
			D3DX_DEFAULT, 0x00000000);

		if (_hoops_CAHAH) {
			ASSERT(_hoops_IAHAH != txr->_hoops_RHGH->_hoops_PHGH);
			FREE_ARRAY(_hoops_IAHAH, _hoops_CAHAH, unsigned char);
		}

		H_SAFE_RELEASE(surface);
		return SUCCEEDED(_hoops_IIRHP);;
	}

	bool _hoops_SAAH(_hoops_RCR *txr)
	{
		HRESULT _hoops_IIRHP;
		unsigned char *data;
		int pitch;

		if (SUCCEEDED(_hoops_IIRHP = Lock(null, &data, &pitch))) {
			_hoops_GHGH(_hoops_ISS, txr, data, pitch);
			Unlock();
		}
		return SUCCEEDED(_hoops_IIRHP);;
	}


	/* _hoops_IRHAH _hoops_SASI _hoops_PISRR */
	/********************************/
	HRESULT GetSurfaceLevel(unsigned int level, LPDIRECT3DSURFACE9 *surface)
	{
		return _hoops_PCC->GetSurfaceLevel(level, surface);
	}

	LPDIRECT3DSURFACE9 GetSurfaceLevel(unsigned int level)
	{
		IDirect3DSurface9 *surface;
		_hoops_PCC->GetSurfaceLevel(level, &surface);
		return surface;
	}

	HRESULT GetLevelDesc(unsigned int level, D3DSURFACE_DESC *desc)
	{
		return _hoops_PCC->GetLevelDesc(level, desc);
	}

	LPDIRECT3DTEXTURE9 _hoops_AIARH()
	{
		return _hoops_PCC;
	}
};


class _hoops_HPIRH : public H3DCubeTexture
{
private:
	LPDIRECT3DCUBETEXTURE9 _hoops_PCC;

public:
	HRESULT _hoops_IIRHP;

public:
	_hoops_HPIRH(H3DData *h3ddata, 
		unsigned int size, 
		unsigned int _hoops_ICRH,
		unsigned int _hoops_GCI) :
		H3DCubeTexture(h3ddata, size, _hoops_ICRH, _hoops_GCI, H3DFMT_A8R8G8B8)
	{
		DX9Data *dx9data = (DX9Data *) h3ddata;
		_hoops_ISS = h3ddata;
		D3DFORMAT format = D3DFMT_A8R8G8B8;
		D3DPOOL pool = D3DPOOL_DEFAULT;
		unsigned int _hoops_HAHAH = 0;

		if (BIT(_hoops_GCI, H3DTEXUSAGE_RENDERTARGET)) 
			_hoops_HAHAH = D3DUSAGE_RENDERTARGET;
		else
			pool = D3DPOOL_MANAGED;

		if (BIT(_hoops_GCI, H3DTEXUSAGE_AUTOGENMIPMAP))
			_hoops_HAHAH |= D3DUSAGE_AUTOGENMIPMAP;
		else
			// _hoops_CGP _hoops_SR _hoops_SPGA'_hoops_RA _hoops_PSCS _hoops_HCRH _hoops_HARH, _hoops_GA'_hoops_RA _hoops_ARPR _hoops_CAPR, _hoops_CR _hoops_RH _hoops_RHPP
			// _hoops_ASSP'_hoops_RA _hoops_CISA _hoops_GGR _hoops_PA _hoops_PRGAH _hoops_RH _hoops_SCIA _hoops_PAPA.
			_hoops_ICRH = 1;
		
		_hoops_IIRHP = dx9data->pDevice->CreateCubeTexture(size, _hoops_ICRH, _hoops_HAHAH,
			format, pool, &_hoops_PCC, NULL);
	}

	~_hoops_HPIRH()
	{
		H_SAFE_RELEASE(_hoops_PCC);
	};

	enum _hoops_RPHAH
	{
		_hoops_APHAH,
		_hoops_PPHAH,
		_hoops_HPHAH,
		_hoops_IPHAH,
		_hoops_CPHAH,
		_hoops_SPHAH,
	};

	bool Lock(H3DFACE face, H3DRect *_hoops_CGPRR, unsigned char ** data, int * pitch = null)
	{
		HRESULT _hoops_IIRHP;
		RECT rect;
		D3DLOCKED_RECT _hoops_HC;
		if (_hoops_CGPRR)
		{
			rect.top = _hoops_CGPRR->top;
			rect.bottom = _hoops_CGPRR->bottom;
			rect.right = _hoops_CGPRR->right;
			rect.left = _hoops_CGPRR->left;
			_hoops_IIRHP = _hoops_PCC->LockRect(static_cast<D3DCUBEMAP_FACES>(face), 0, &_hoops_HC, &rect, 0);
		}
		else
			_hoops_IIRHP = _hoops_PCC->LockRect(static_cast<D3DCUBEMAP_FACES>(face), 0, &_hoops_HC, null, 0);
		*data = (unsigned char *)_hoops_HC.pBits;
		if (pitch)
			*pitch = _hoops_HC.Pitch;
		return SUCCEEDED(_hoops_IIRHP);
	}

	void Unlock(H3DFACE face)
	{
		_hoops_PCC->UnlockRect(static_cast<D3DCUBEMAP_FACES>(face), 0);
	}

	void _hoops_APRH()
	{
		_hoops_PCC->GenerateMipSubLevels();
	}

	LPDIRECT3DCUBETEXTURE9 _hoops_AIARH()
	{
		return _hoops_PCC;
	}
};



class _hoops_IPIRH : public H3DTexture3D
{
private:
	LPDIRECT3DVOLUMETEXTURE9 _hoops_PCC;

public:
	HRESULT _hoops_IIRHP;

public:
	_hoops_IPIRH(H3DData *h3ddata, 
		unsigned int w, 
		unsigned int h,
		unsigned int depth,
		unsigned int _hoops_ICRH,
		unsigned int _hoops_GCI,
		H3DFORMAT format) :
		H3DTexture3D(h3ddata, w, h, depth, _hoops_ICRH, _hoops_GCI, format)
	{
		DX9Data *dx9data = (DX9Data *) h3ddata;
		_hoops_ISS = h3ddata;
		D3DFORMAT d3dformat = D3DFMT_UNKNOWN;
		D3DPOOL pool = D3DPOOL_DEFAULT;
		unsigned int _hoops_HAHAH = 0;

		if (BIT(_hoops_GCI, H3DTEXUSAGE_RENDERTARGET)) 
			_hoops_HAHAH = D3DUSAGE_RENDERTARGET;
		else
			pool = D3DPOOL_MANAGED;

		switch (format)
		{
			case H3DFMT_L8:
				d3dformat = D3DFMT_L8;
				break;
			case H3DFMT_R8G8B8:
				if (dx9data->_hoops_CHGH) {
					d3dformat = D3DFMT_R8G8B8;
					break;
				}
			case H3DFMT_A8R8G8B8:
				d3dformat = D3DFMT_A8R8G8B8;
				break;

			case H3DFMT_R32F:
			case H3DFMT_D24S8:
			case H3DFMT_D24X8:
			case H3DFMT_DXT1:
			case H3DFMT_DXT3:
			case H3DFMT_DXT5:
			default:
				HE_ERROR(HEC_DX9_DRIVER, HEC_DX9_DRIVER, 
					"Internal error: unhandled DX9 texture format in HDX9Texture3D!");
				return;
		}

		if (BIT(_hoops_GCI, H3DTEXUSAGE_AUTOGENMIPMAP))
			_hoops_HAHAH |= D3DUSAGE_AUTOGENMIPMAP;
		else
			// _hoops_CGP _hoops_SR _hoops_SPGA'_hoops_RA _hoops_PSCS _hoops_HCRH _hoops_HARH, _hoops_GA'_hoops_RA _hoops_ARPR _hoops_CAPR, _hoops_CR _hoops_RH _hoops_RHPP
			// _hoops_ASSP'_hoops_RA _hoops_CISA _hoops_GGR _hoops_PA _hoops_PRGAH _hoops_RH _hoops_SCIA _hoops_PAPA.
			_hoops_ICRH = 1;

		_hoops_IIRHP = D3DXCreateVolumeTexture (dx9data->pDevice, 
			w, h, depth, 
			_hoops_ICRH, _hoops_HAHAH, d3dformat, pool, &_hoops_PCC);

		//_hoops_SGH _hoops_GHHAH _hoops_GAR _hoops_ARRS _hoops_RIIA _hoops_IIGR _hoops_RH _hoops_HSPR _hoops_GGR _hoops_AGR _hoops_IS _hoops_HGCR _hoops_HHH _hoops_CIH _hoops_RIHH _hoops_IPAC
		//_hoops_RHHAH = _hoops_CRCRH->_hoops_GHSRH->_hoops_AHHAH (
		//	_hoops_SSCHA, _hoops_GGHR, _hoops_HCH, _hoops_HARH, _hoops_PHHAH,
		//	_hoops_RPCC, _hoops_ICGAR, &_hoops_HHHAH, _hoops_IHHAH);
	}

	~_hoops_IPIRH()
	{
		H_SAFE_RELEASE(_hoops_PCC);
	};

	bool Lock(unsigned char ** data, int *_hoops_SRAH, int *_hoops_GAAH)
	{
		HRESULT _hoops_IIRHP;
		D3DLOCKED_BOX _hoops_CHHAH;

		_hoops_IIRHP = _hoops_PCC->LockBox(0, &_hoops_CHHAH, null, 0);
		*_hoops_SRAH = _hoops_CHHAH.RowPitch;
		*_hoops_GAAH = _hoops_CHHAH.SlicePitch;
		*data = (unsigned char *)_hoops_CHHAH.pBits;
		return SUCCEEDED(_hoops_IIRHP);
	}

	void Unlock()
	{
		_hoops_PCC->UnlockBox(0);
	}

	void _hoops_APRH()
	{
		_hoops_PCC->GenerateMipSubLevels();
	}

	LPDIRECT3DVOLUMETEXTURE9 _hoops_AIARH()
	{
		return _hoops_PCC;
	}
};



/*****************************************************************************
*****************************************************************************
						_hoops_SHHAH _hoops_ISHGR
*****************************************************************************
*****************************************************************************/
class _hoops_ICARH : public H3DActions
{
private:
	DX9Data *_hoops_CCARH;

// _hoops_SAP _hoops_GPP _hoops_SSPGP _hoops_IIPR
// #_hoops_PPIP _hoops_GIHAH

	void _hoops_RIHAH(wchar_t const *event, wchar_t const *_hoops_RHSRR) {
#ifdef DX9_TRACE_TO_DEBUGGER
		DWORD const thread = GetCurrentThreadId();

		int const _hoops_RSIGR = 256;
		wchar_t buffer[_hoops_RSIGR];
		_hoops_AIHAH( buffer, _hoops_RSIGR-1, L"[Thread %d] %s: %s\n", thread, event, _hoops_RHSRR );
		buffer[_hoops_RSIGR-1] = '\0';

		_hoops_PIHAH( buffer );
#else
		UNREFERENCED(event);
		UNREFERENCED(_hoops_RHSRR);
#endif
	}

public:
	_hoops_ICARH(){};
	_hoops_ICARH(DX9Data *dx9data) : 
		H3DActions(dx9data),
		_hoops_CCARH(dx9data) {};
	~_hoops_ICARH(){};

	void _hoops_ASCRR(wchar_t const *_hoops_RHSRR) {
		D3DPERF_BeginEvent(0, _hoops_RHSRR);
		_hoops_RIHAH( L"Enter", _hoops_RHSRR );
	};
	void _hoops_PSCRR(wchar_t const *_hoops_RHSRR) {
		_hoops_RIHAH( L"Exit", _hoops_RHSRR );
		D3DPERF_EndEvent();
	};

#define _hoops_RHARR ((size_t)1000*1000*1000) 
	bool _hoops_HSCRR(size_t _hoops_HHARR)
	{
		bool result = (HOOPS_WORLD->display_list_vram_usage + HOOPS_WORLD->_hoops_SARH + (size_t)(_hoops_HHARR) < HOOPS_WORLD->_hoops_PHARR);

#ifndef _WIN64
		result = result && (HOOPS_WORLD->display_list_vram_usage + HI_Memory_On_Pool(HOOPS_WORLD->memory_pool) < _hoops_RHARR);	   
#endif

		return result;
	}

	H3DVertexBufferCache *_hoops_HAIH() {return NEW(_hoops_SAAAH)();}
	H3DIndexBufferCache *_hoops_SRPRR() {return NEW(_hoops_GPAAH)();}
	H3DIndexedBufferObject* _hoops_PRAS() {return NEW(_hoops_CHPAH)();}
	H3DIndexedBufferObject* _hoops_CAIRR()  {return NEW(_hoops_PHPAH)();}

	void Clear(int flags, int color, float _hoops_CCCRR, int _hoops_SCCRR, bool _hoops_GSCRR)
	{
		_hoops_GPRP(_hoops_CCARH, H3DMASK_RGBA);

		if (_hoops_GSCRR) {
			_hoops_CCARH->pDevice->Clear(0, NULL, d3dclear(flags), color, _hoops_CCCRR, _hoops_SCCRR);
			return;
		}

		// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_GRP _hoops_HCH _hoops_AGI, _hoops_GA'_hoops_RA _hoops_SCAC _hoops_RH _hoops_HCH _hoops_HH _hoops_IS _hoops_RH _hoops_GISH _hoops_PIRA.
		_hoops_PPRS _hoops_HPRS = { { NULL, NULL, NULL, NULL }, NULL };
		if ( _hoops_CCARH->_hoops_II.mode && !_hoops_CCARH->_hoops_PI.mode ) {
			_hoops_IPRS(&_hoops_HPRS);
			_hoops_GPAP(_hoops_HPRS._hoops_PGRGR[0], _hoops_HPRS.depth_stencil);
		}

		// _hoops_CAAP _hoops_RH _hoops_HAIR _hoops_SAAP _hoops_PPR _hoops_AHCR/_hoops_APSP _hoops_HCAGR _hoops_AIH _hoops_RAPA.
		DWORD _hoops_HIHAH = d3dclear(flags);
		_hoops_CCARH->pDevice->Clear(0, NULL, _hoops_HIHAH, color, _hoops_CCCRR, _hoops_SCCRR);

		// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_GRP _hoops_HCH _hoops_AGI, _hoops_SR _hoops_RRP _hoops_IS _hoops_PPSI _hoops_ISSC _hoops_RH _hoops_RHGS _hoops_HCSS.
		if ( _hoops_CCARH->_hoops_II.mode && !_hoops_CCARH->_hoops_PI.mode ) {
			// _hoops_CGP _hoops_RH _hoops_HCH _hoops_SRHR _hoops_CSAP _hoops_GCGSP, _hoops_SCAC _hoops_RH _hoops_HCH _hoops_HH _hoops_IS _hoops_IRS _hoops_PIS _hoops_HAIR _hoops_PIRA.
			if ( _hoops_HIHAH & D3DCLEAR_ZBUFFER ) {
				// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HSSGR _hoops_IS _hoops_RH _hoops_SGIP _hoops_IPPA, _hoops_IRHH _hoops_RCRR _hoops_SR _hoops_GA'_hoops_RA _hoops_RHHR _hoops_SCH.
				if( _hoops_CCCRR == 1.0f )
					_hoops_CCCRR = 254.0f/255.0f;

				_hoops_GPAP(_hoops_HPRS._hoops_PGRGR[1]);
				_hoops_CCARH->pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_COLORVALUE(_hoops_CCCRR, _hoops_CCCRR, _hoops_CCCRR, _hoops_CCCRR), 0, 0);
			}

			// _hoops_IPRP _hoops_GIGR _hoops_HCSS.
			_hoops_CCARH->_hoops_GSCR->_hoops_CHRS(&_hoops_HPRS);
		}
	}

	void SetViewport(H3DViewport const *_hoops_APPRR)
	{
		D3DVIEWPORT9 _hoops_PAPH = d3dviewport(_hoops_APPRR);
		if ( _hoops_CCARH->_hoops_IHP ) {
			_hoops_PAPH.X *= _hoops_CCARH->_hoops_HSAA;
			_hoops_PAPH.Y *= _hoops_CCARH->_hoops_ISAA;
			_hoops_PAPH.Width *= _hoops_CCARH->_hoops_HSAA;
			_hoops_PAPH.Height *= _hoops_CCARH->_hoops_ISAA;
		}
		_hoops_CCARH->pDevice->SetViewport(&_hoops_PAPH);
	}

	void _hoops_GGSS (float _hoops_RGSRR, float _hoops_SICS) {
		_hoops_CCARH->pDevice->SetRenderState (D3DRS_DEPTHBIAS, *(DWORD const *)&_hoops_RGSRR);
		_hoops_CCARH->pDevice->SetRenderState (D3DRS_SLOPESCALEDEPTHBIAS, *(DWORD const *)&_hoops_SICS);
	}

	/************************/
	/* _hoops_ISIRR/_hoops_IARP _hoops_SPGH */
	/************************/
	void _hoops_AGPH (Display_Context alter * dc, int _hoops_CRIA, int _hoops_PGPH = 0, int _hoops_RASP = 0);
	bool _hoops_GSAC(const Net_Rendition & nr, _hoops_RCR *txr, int _hoops_GCI, H3DTexture *id, int _hoops_GRRA);


	/********************/
	/* _hoops_GRAR _hoops_IIHAH */
	/********************/
	bool CreateTexture(unsigned int width, unsigned int height, unsigned int _hoops_ICRH, unsigned int _hoops_GCI, H3DFORMAT format, H3DTexture **id);
	bool CreateCubeTexture(unsigned int size, unsigned int _hoops_ICRH, unsigned int _hoops_GCI, H3DCubeTexture **id);
	bool _hoops_PSRH(unsigned int width, unsigned int height, unsigned int depth, unsigned int _hoops_ICRH, unsigned int _hoops_GCI, H3DFORMAT format, H3DTexture3D **id);
	bool CreateRenderTarget(unsigned int width, unsigned int height, unsigned int _hoops_GCI, H3DFORMAT _hoops_GCH, unsigned int _hoops_ISARR, H3DRenderTarget **id);
	void SetTexture(int _hoops_RHIA, H3DTexture *id)
	{
		_hoops_SCCR(_hoops_CCARH, _hoops_RHIA, id);
	}


	/*******************/
	/* _hoops_GGPR _hoops_IIHAH */
	/*******************/
	H3DShader *_hoops_ICCRR(H3DShaderID id) 
	{
		return NEW(_hoops_RGHRH)(id);
	};



	/******************/
	/* _hoops_CIHAH _hoops_PGSI */
	/******************/
	void create_region (Net_Rendition const &  nr,
			Int_Rectangle const * area, void **image, void **z);

	void _hoops_HIPGR (Net_Rendition const &  nr,
			Int_Rectangle const * area, void alter * image, void alter * z);

	void _hoops_PIPGR (Net_Rendition const &  nr,
			Int_Rectangle const * area, void alter * image, void alter * z);

	void _hoops_ISPGR (Display_Context alter * dc,
			void alter * image, void alter * z);


	/********************/
	/* _hoops_SIHAH */
	/********************/
	void _hoops_IPRS (_hoops_PPRS *_hoops_HPRS);
	void _hoops_CHRS (_hoops_PPRS *_hoops_HPRS, bool release = true);

	void _hoops_GPAP (H3DRenderTarget *_hoops_ISCRR, H3DRenderTarget *_hoops_AASP = null, H3DRenderTarget *_hoops_CSCRR = null, H3DRenderTarget *_hoops_SSCRR = null, H3DRenderTarget *_hoops_GGSRR = null );

	bool _hoops_PHCS (H3DRenderTarget *_hoops_ISCRR, H3DRenderTarget *_hoops_AASP = null, H3DRenderTarget *_hoops_CSCRR = null, H3DRenderTarget *_hoops_SSCRR = null, H3DRenderTarget *_hoops_GGSRR = null ) {
		UNREFERENCED(_hoops_ISCRR);
		UNREFERENCED(_hoops_AASP);
		UNREFERENCED(_hoops_CSCRR);
		UNREFERENCED(_hoops_SSCRR);
		UNREFERENCED(_hoops_GGSRR);
		return true;
	};
	/************************/
	/* _hoops_IPSRH _hoops_PIAP "_hoops_HHSA" */
	/************************/

	void _hoops_RHPRR(bool mode)
	{
		_hoops_CCARH->_hoops_CSC->antialias = mode;
		_hoops_CCARH->pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, mode);
	}

	void _hoops_GHHRR(H3DBLEND src, H3DBLEND _hoops_PCAP)
	{
		_hoops_CCARH->_hoops_CSC->_hoops_PHSS = src;
		_hoops_CCARH->pDevice->SetRenderState(D3DRS_SRCBLEND, d3dblend(src));
		_hoops_CCARH->_hoops_CSC->_hoops_IHSS = _hoops_PCAP;
		_hoops_CCARH->pDevice->SetRenderState(D3DRS_DESTBLEND, d3dblend(_hoops_PCAP));
	}

	void _hoops_PHPRR(bool mode)
	{
		_hoops_CCARH->pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, mode ? _hoops_CCARH->_hoops_CSC->_hoops_GRPP : 0);
		_hoops_CCARH->_hoops_CSC->_hoops_RAIH = mode;
	}

	void _hoops_IHPRR(int mask)
	{
		_hoops_CCARH->pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, _hoops_CCARH->_hoops_CSC->_hoops_RAIH ? mask : 0);
		_hoops_CCARH->_hoops_CSC->_hoops_GRPP = mask;
	}

	void _hoops_CCHC(H3DCULL mode)
	{
		if (mode == H3DCULL_NONE)
			_hoops_CCARH->_hoops_APH = false;
		else
			_hoops_CCARH->_hoops_APH = true;
		_hoops_CCARH->_hoops_CSC->_hoops_HRSA = mode;
		_hoops_CCARH->pDevice->SetRenderState(D3DRS_CULLMODE, d3dcull(mode));
	}

	void _hoops_CHPRR(bool mode)
	{
		_hoops_CCARH->_hoops_CSC->_hoops_AAIH = mode;
		if (mode)
			_hoops_CCARH->pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
		else
			_hoops_CCARH->pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE);

		if (_hoops_CCARH->_hoops_II.mode && 
			BIT (_hoops_CCARH->_hoops_HPHRH.PrimitiveMiscCaps, D3DPMISCCAPS_INDEPENDENTWRITEMASKS))
			_hoops_CCARH->pDevice->SetRenderState(D3DRS_COLORWRITEENABLE1, mode ? 0xf : 0);
	}

	void _hoops_GIPRR(float _hoops_RICR, float _hoops_AICR)
	{
		H3DViewport _hoops_PAPH = _hoops_CCARH->_hoops_CSC->_hoops_CSAA;
		_hoops_PAPH.MinZ = _hoops_CCARH->_hoops_CSC->_hoops_GSCH[0] = _hoops_RICR;
		_hoops_PAPH.MaxZ = _hoops_CCARH->_hoops_CSC->_hoops_GSCH[1] = _hoops_AICR;
		SetViewport(&_hoops_PAPH);
	}

	void _hoops_HIPRR (Net_Rendition const & nr, bool mode)
	{
		if (mode) {
			_hoops_CCARH->_hoops_CSC->_hoops_GAGRR = true;
			_hoops_CCARH->pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
			if (nr->_hoops_CPP->_hoops_CPA != _hoops_CCARH->_hoops_SARRR) {
				/*_hoops_AIIC _hoops_GCHAH[4];*/
				_hoops_CCARH->_hoops_SARRR = nr->_hoops_IRR->_hoops_CPA;
				/* _hoops_AA _hoops_HAR _hoops_AA _hoops_AIR _hoops_PAIR _hoops_IISRR */
				_hoops_CCARH->pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_NONE);
				_hoops_CCARH->pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
				_hoops_CCARH->pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_XRGB(nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.r, nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.g, nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.r));
			} \
		}
		else {
			_hoops_CCARH->_hoops_CSC->_hoops_GAGRR = false;
			_hoops_CCARH->pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
		}
	}

	void _hoops_RSCR (
		int _hoops_GRRA, 
		H3DTEXTUREFILTERTYPE filter, 
		H3DTEXTUREFILTERTYPE _hoops_PHHRR, 
		H3DTEXTUREADDRESS _hoops_HHHRR)
	{
		_hoops_GPIRH(_hoops_CCARH, _hoops_GRRA, d3dtexturefilter(filter));
		_hoops_RPIRH(_hoops_CCARH, _hoops_GRRA, d3dtexturefilter(filter));
		_hoops_APIRH(_hoops_CCARH, _hoops_GRRA, d3dtexturefilter(_hoops_PHHRR));
		ENSURE_TEXTURE_WRAP_S(_hoops_CCARH, _hoops_GRRA, d3dtextureaddress(_hoops_HHHRR));
		_hoops_SAIRH(_hoops_CCARH, _hoops_GRRA, d3dtextureaddress(_hoops_HHHRR));
	}

	void _hoops_GCPRR(bool mode)
	{
		if (_hoops_CCARH->_hoops_HGARR) {
			_hoops_RCPRR(_hoops_CCARH);
			_hoops_CCARH->_hoops_CSC->_hoops_IRGRR = mode;
			if (mode)
				_hoops_CCARH->pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
			else
				_hoops_CCARH->pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
		}
	}

	void _hoops_SCPRR(int _hoops_PCPRR, int _hoops_HCPRR, int _hoops_ICPRR, int _hoops_CCPRR)
	{
		RECT _hoops_RCHAH;
		_hoops_RCHAH.left = _hoops_PCPRR;
		_hoops_RCHAH.top = _hoops_CCARH->yfudge - _hoops_CCPRR;
		_hoops_RCHAH.right = _hoops_ICPRR + 1;
		_hoops_RCHAH.bottom = _hoops_CCARH->yfudge - _hoops_HCPRR + 1;

		if ( _hoops_CCARH->_hoops_IHP ) { \
			_hoops_RCHAH.left *= _hoops_CCARH->_hoops_HSAA;
			_hoops_RCHAH.right *= _hoops_CCARH->_hoops_HSAA;
			_hoops_RCHAH.top *= _hoops_CCARH->_hoops_ISAA;
			_hoops_RCHAH.bottom *= _hoops_CCARH->_hoops_ISAA;
		}

		_hoops_CCARH->pDevice->SetScissorRect(&_hoops_RCHAH);
	}

	void _hoops_CIPRR(H3DSHADEMODE mode)
	{
		_hoops_CCARH->_hoops_CSC->_hoops_SAGRR = mode;
		_hoops_CCARH->pDevice->SetRenderState(D3DRS_SHADEMODE, d3dshademode(mode));
	}

	void _hoops_SPPRR(bool mode)
	{
		if (mode){
			_hoops_CCARH->pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000001);
			_hoops_CCARH->pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE); 
			_hoops_CCARH->pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
		}
		else
			_hoops_CCARH->pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		_hoops_CCARH->_hoops_CSC->_hoops_HRGRR = mode;

	}

	void _hoops_RSPRR(bool mode)
	{
		if (mode)
			_hoops_CCARH->pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		else
			_hoops_CCARH->pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
		_hoops_CCARH->_hoops_CSC->_hoops_PRGRR = mode;

	}

	void _hoops_CRHRR(H3DCMPFUNC cmp)
	{
		_hoops_CCARH->_hoops_CSC->_hoops_RGIH = cmp;
		_hoops_CCARH->pDevice->SetRenderState(D3DRS_STENCILFUNC, cmp);
	}

	void _hoops_CGHRR(int _hoops_HAGR)
	{
		_hoops_CCARH->_hoops_CSC->_hoops_PGIH = _hoops_HAGR;
		_hoops_CCARH->pDevice->SetRenderState(D3DRS_STENCILMASK, _hoops_HAGR);
	}

	void _hoops_PRHRR(int _hoops_HAGR)
	{
		_hoops_CCARH->_hoops_CSC->_hoops_IGIH = _hoops_HAGR;
		_hoops_CCARH->pDevice->SetRenderState(D3DRS_STENCILREF, _hoops_HAGR);
	}

	void _hoops_GRHRR(int _hoops_HAGR)
	{
		_hoops_CCARH->_hoops_CSC->_hoops_IRIH = _hoops_HAGR;
		_hoops_CCARH->pDevice->SetRenderState(D3DRS_STENCILWRITEMASK, _hoops_HAGR);
	}

	void _hoops_AAHRR(H3DSTENCILOP _hoops_AAIS, H3DSTENCILOP _hoops_RAHRR, H3DSTENCILOP pass)
	{
		_hoops_CCARH->_hoops_CSC->_hoops_RRIH = _hoops_AAIS;
		_hoops_CCARH->_hoops_CSC->_hoops_PRIH = _hoops_RAHRR;
		_hoops_CCARH->_hoops_CSC->_hoops_SGIH = pass;
		_hoops_CCARH->pDevice->SetRenderState(D3DRS_STENCILFAIL, _hoops_AAIS);
		_hoops_CCARH->pDevice->SetRenderState(D3DRS_STENCILZFAIL, _hoops_RAHRR);
		_hoops_CCARH->pDevice->SetRenderState(D3DRS_STENCILPASS, pass);
	}

	void _hoops_IAHRR(H3DCMPFUNC cmp, unsigned long ref, unsigned long mask, unsigned long _hoops_HAHRR)
	{
		if (cmp != _hoops_CCARH->_hoops_CSC->_hoops_RGIH)
			_hoops_CRHRR(cmp);
		if (ref != _hoops_CCARH->_hoops_CSC->_hoops_IGIH)
			_hoops_PRHRR(ref);
		if (mask != _hoops_CCARH->_hoops_CSC->_hoops_PGIH)
			_hoops_CGHRR(mask);
		if (_hoops_HAHRR != _hoops_CCARH->_hoops_CSC->_hoops_IRIH)
			_hoops_GRHRR(_hoops_HAHRR);
	}

	void _hoops_PSPRR (int _hoops_RHIA, H3DTexture *texture)
	{
		ASSERT(_hoops_RHIA < H3D_MAX_TEXTURES);
		_hoops_CCARH->_hoops_CSC->texture[_hoops_RHIA] = texture;
		
		if ( texture ) {
			texture->_hoops_IGPRR = &_hoops_CCARH->_hoops_CSC->texture[_hoops_RHIA];

			// _hoops_AHH: _hoops_ACHAH _hoops_PCHAH _hoops_RGHP _hoops_IH 2D _hoops_PPR _hoops_ASRH _hoops_AI.
			if ( texture->_hoops_SGPRR() ) {
				_hoops_HPIRH *dx9_texture = static_cast<_hoops_HPIRH*>(texture);
				_hoops_CCARH->pDevice->SetTexture(_hoops_RHIA, dx9_texture->_hoops_AIARH());
			}
			else if ( texture->_hoops_GRPRR() ) {
				_hoops_IPIRH *dx9_texture = static_cast<_hoops_IPIRH*>(texture);
				_hoops_CCARH->pDevice->SetTexture(_hoops_RHIA, dx9_texture->_hoops_AIARH());
			}
			else {
				_hoops_RIARH *dx9_texture = static_cast<_hoops_RIARH*>(texture);
				_hoops_CCARH->pDevice->SetTexture(_hoops_RHIA, dx9_texture->_hoops_AIARH());
			}
		}
		else
			_hoops_CCARH->pDevice->SetTexture(_hoops_RHIA, null);
		_hoops_CCARH->dc->_hoops_IGGI->_hoops_GSAC++;
	}
	void _hoops_AGSRR (int _hoops_RHIA, H3DTexture *texture)
	{
		if (_hoops_CCARH->_hoops_CSC->texture[_hoops_RHIA] != texture)
			_hoops_ASPRR(_hoops_CCARH, _hoops_RHIA, texture);
	}

	void _hoops_CSPRR(bool mode)
	{
		_hoops_CCARH->_hoops_CSC->_hoops_HSAC = mode;
		_hoops_CCARH->pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, mode);
	}

	void _hoops_IPPRR(H3DVertexFormat _hoops_PPCP)
	{
		_hoops_CCARH->_hoops_CSC->_hoops_PPCP = _hoops_PPCP;
		_hoops_CCARH->pDevice->SetFVF(_hoops_GIAAH(_hoops_PPCP));
	}

	void _hoops_GGHRR(bool mode)
	{
		if (!mode)
			_hoops_CCARH->pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		else {
			if (_hoops_CCARH->_hoops_CSC->_hoops_CRGRR)
				_hoops_CCARH->pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_GREATER);
			else
				_hoops_CCARH->pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		}
		_hoops_CCARH->_hoops_CSC->_hoops_ARGRR = mode;
	}

	void _hoops_PGHRR(bool _hoops_AGHRR, float _hoops_CCGH, float _hoops_ICGH)
	{
		_hoops_CCARH->pDevice->SetRenderState( D3DRS_POINTSPRITEENABLE, _hoops_AGHRR );
		_hoops_CCARH->pDevice->SetRenderState( D3DRS_POINTSIZE_MIN, *reinterpret_cast<const DWORD*>(&_hoops_CCGH) );
		_hoops_CCARH->pDevice->SetRenderState( D3DRS_POINTSIZE_MAX, *reinterpret_cast<const DWORD*>(&_hoops_ICGH) );
	}

	void _hoops_GHIP(H3DData				*h3ddata,
											H3DTexture			*texture,
											int					x, 
											int					y, 
											int					width, 
											int					height,
											float				_hoops_ACCRR = 0,
											float				_hoops_ISPI = 0,
											float				_hoops_PCCRR = 1,
											float				_hoops_CSPI = 1);

	void * _hoops_CPHGR()
	{
		return ((_hoops_HIARH*)_hoops_CCARH->render_target)->_hoops_IIARH();
	}

	void * _hoops_PRHGR(_hoops_AHGR type, const char *source) 
	{
		DX9Data *dx9data = (DX9Data*) _hoops_ISS;
		int length = (int)strlen(source);
		const char *_hoops_CCHRH = (type == _hoops_GCGR) ? 
			D3DXGetVertexShaderProfile(dx9data->pDevice) : D3DXGetPixelShaderProfile(dx9data->pDevice);
		const char *_hoops_HCHAH = (type == _hoops_GCGR) ?
			"vs_main" : "ps_main";
		DWORD _hoops_SRRS = 0;
		ID3DXBuffer *_hoops_RSR = null;
		ID3DXBuffer *_hoops_PHHRH = null;

		HRESULT _hoops_IIRHP = D3DXCompileShader(
					source,				
					(UINT)(length+1),
					null,
					null,
					_hoops_HCHAH,
					_hoops_CCHRH,
					_hoops_SRRS,
					&_hoops_RSR, 
					&_hoops_PHHRH, // _hoops_RIHH _hoops_SSHRH 
					null);

		if (FAILED(_hoops_IIRHP)) {
			const char *error = (const char *)_hoops_PHHRH->GetBufferPointer();
			HE_ERROR(DX9_DRIVER, DX9_DRIVER, error);
		}

		UNREFERENCED(_hoops_IIRHP);
		return _hoops_RSR;
	}

	void _hoops_IRHGR(POINTER_SIZED_INT _hoops_RSR) 
	{
		ID3DXBuffer *_hoops_ICHAH = (ID3DXBuffer *) _hoops_RSR;
		H_SAFE_RELEASE(_hoops_ICHAH);
	}

	bool _hoops_SRHGR(_hoops_AHGR type, POINTER_SIZED_INT _hoops_RSR)
	{
		bool _hoops_CCHAH = false;
		if (type == _hoops_GCGR)
			_hoops_ISS->_hoops_GAARR = _hoops_RSR;
		else
			_hoops_ISS->_hoops_RAARR = _hoops_RSR;

		// _hoops_CGP _hoops_SR'_hoops_RISP _hoops_GGHP _hoops_GIPR _hoops_AIRRR _hoops_ARP, _hoops_PSCR _hoops_SGHHR _hoops_IS _hoops_ARPR _hoops_PCCP _hoops_IIC
		if (_hoops_ISS->_hoops_GAARR && _hoops_ISS->_hoops_RAARR &&
			(_hoops_ISS->_hoops_GAARR != _hoops_ISS->_hoops_CRARR ||
			_hoops_ISS->_hoops_RAARR != _hoops_ISS->_hoops_SRARR))
		{
			H3DShaderID id;
			id._hoops_PASRR(_hoops_ISS->_hoops_GAARR, _hoops_ISS->_hoops_RAARR);

			H3DShader *_hoops_SCHAH = _hoops_ISS->_hoops_IP->Lookup (id);
			if (!_hoops_SCHAH) {
				_hoops_SCHAH = _hoops_ISS->_hoops_GSCR->_hoops_ICCRR(id);
				if (_hoops_SCHAH->Create(_hoops_ISS))
					_hoops_ISS->_hoops_IP->Insert (id, _hoops_SCHAH);
				else
					delete _hoops_SCHAH;
			}
			_hoops_CCHAH = true;
		}
		return _hoops_CCHAH;
	}

	ID3DXConstantTable *_hoops_GSHAH(_hoops_AHGR type)
	{
		ID3DXConstantTable *table;
		ID3DXBuffer *_hoops_RSR = (type == _hoops_GCGR) ? (ID3DXBuffer *)_hoops_ISS->_hoops_GAARR : (ID3DXBuffer *)_hoops_ISS->_hoops_RAARR;

		if (!_hoops_RSR) {
			HE_ERROR(HEC_DX9_DRIVER, HEC_DX9_DRIVER,
				"User shader error: Cannot set uniform when user shader is not set!");
			return null;
		}

		D3DXGetShaderConstantTable((DWORD*)_hoops_RSR->GetBufferPointer(), &table);
		return table;
	}
	
	void _hoops_RAHGR(_hoops_AHGR type, char const * name, int count, int *data)
	{
		HRESULT _hoops_IIRHP;
		DX9Data *dx9data = (DX9Data *) _hoops_ISS;
		ID3DXConstantTable *table = _hoops_GSHAH(type);
		if (!table)
			return;

		D3DXHANDLE _hoops_RSHAH = table->GetConstantByName(null, name);
		_hoops_IIRHP = table->SetIntArray(dx9data->pDevice, _hoops_RSHAH, data, count);
	}

	void _hoops_PAHGR(_hoops_AHGR type, char const * name, int count, float *data)
	{
		HRESULT _hoops_IIRHP;
		DX9Data *dx9data = (DX9Data *) _hoops_ISS;
		ID3DXConstantTable *table = _hoops_GSHAH(type);
		if (!table)
			return;

		D3DXHANDLE _hoops_RSHAH = table->GetConstantByName(null, name);
		_hoops_IIRHP = table->SetFloatArray(dx9data->pDevice, _hoops_RSHAH, data, count);
	}

	void _hoops_IAHGR(_hoops_AHGR type, char const * name, int width, int count, float *data)
	{
		HRESULT _hoops_IIRHP;
		DX9Data *dx9data = (DX9Data *) _hoops_ISS;
		ID3DXConstantTable *table = _hoops_GSHAH(type);
		if (!table)
			return;

		D3DXHANDLE _hoops_RSHAH = table->GetConstantByName(null, name);
		_hoops_IIRHP = table->SetFloatArray(dx9data->pDevice, _hoops_RSHAH, data, width * count);
	}

	void _hoops_SAHGR(_hoops_AHGR type, char const * name, int count, float *data)
	{
		HRESULT _hoops_IIRHP;
		DX9Data *dx9data = (DX9Data *) _hoops_ISS;
		ID3DXConstantTable *table = _hoops_GSHAH(type);
		if (!table)
			return;

		D3DXHANDLE _hoops_RSHAH = table->GetConstantByName(null, name);
		_hoops_IIRHP = table->SetMatrixArray(dx9data->pDevice, _hoops_RSHAH, (D3DXMATRIX *) data, count);
	}
}; // _hoops_SHHAH


#endif // _hoops_ASHAH

#pragma warning(default : 4710)

#endif // _hoops_PSHAH



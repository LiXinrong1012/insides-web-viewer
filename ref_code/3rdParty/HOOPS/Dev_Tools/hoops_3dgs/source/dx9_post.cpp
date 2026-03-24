/*
* Copyright (c) 2006 by Tech Soft 3D, LLC.
* The information contained herein is confidential and proprietary to
* Tech Soft 3D, LLC., and considered a trade secret as defined under
* civil and criminal statutes.	Tech Soft 3D shall pursue its civil
* and criminal remedies in the event of unauthorized use or misappropriation
* of its trade secrets.	 Use of this information by anyone other than
* authorized employees of Tech Soft 3D, LLC. is granted only under a
* written non-disclosure agreement, expressly prescribing the scope and
* manner of such use.
*
* $Id: obf_tmp.txt 1.69 2010-08-13 18:06:50 jason Exp $
*/

#include "hoops.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "adt.h"

#include "dx9_driver.h"
#include "dx9_post.h"

// _hoops_HSHAH /////////////////////////////////////////////////////////////////////

// _hoops_GGPR _hoops_PIH
local _hoops_PSIRR const _hoops_ISHAH = _hoops_CSIRR(dx9_post_vertex, 0);
local _hoops_PSIRR const _hoops_CSHAH = _hoops_CSIRR(dx9_post_vertex_3d, 0);
local _hoops_PSIRR const _hoops_SSHAH[H3DPost::_hoops_IACRR] = 
{
	_hoops_CSIRR(_hoops_GGIAH, 0),
	_hoops_CSIRR(_hoops_RGIAH, _hoops_RCIRR),
	_hoops_CSIRR(_hoops_RGIAH, _hoops_ACIRR),
	_hoops_CSIRR(_hoops_RGIAH, _hoops_PCIRR),
	_hoops_CSIRR(_hoops_RGIAH, _hoops_HCIRR),
	_hoops_CSIRR(_hoops_AGIAH, _hoops_ACIRR),
	_hoops_CSIRR(_hoops_PGIAH, _hoops_ACIRR),
	_hoops_CSIRR(_hoops_HGIAH, _hoops_ICIRR),
	_hoops_CSIRR(_hoops_IGIAH, 0),
	_hoops_CSIRR(_hoops_IGIAH, _hoops_SCIRR),
	_hoops_CSIRR(_hoops_IGIAH, _hoops_GSIRR),
	_hoops_CSIRR(_hoops_CGIAH, 0),
	_hoops_CSIRR(_hoops_SGIAH, 0),
	_hoops_CSIRR(_hoops_GRIAH, 0),
	_hoops_CSIRR(_hoops_RRIAH, 0),
	_hoops_CSIRR(_hoops_ARIAH, 0),
	_hoops_CSIRR(_hoops_PRIAH, _hoops_CCIRR),
	_hoops_CSIRR(_hoops_HRIAH, _hoops_GSIRR),
	_hoops_CSIRR(_hoops_IRIAH, 0),
	_hoops_CSIRR(_hoops_CRIAH, _hoops_ACIRR),
	_hoops_CSIRR(_hoops_SRIAH, 0),
	_hoops_CSIRR(_hoops_GAIAH, 0),
};

#ifdef H3D_SHADER_DEBUG

local char const *_hoops_RAIAH( _hoops_PSIRR& name, size_t& _hoops_AAIAH )
{
	// _hoops_HSRR _hoops_GGAS _hoops_SPHR
	char *_hoops_PAIAH = NULL;
	_hoops_AAIAH = 0;

	// _hoops_RAH _hoops_SR _hoops_HS _hoops_IRS _hoops_ACAGR _hoops_IS _hoops_GGARP _hoops_HII
	if ( char const * _hoops_CCPR = _hoops_SCPR() )
	{
		// _hoops_RAH _hoops_SR _hoops_RRP _hoops_IS _hoops_GGCR _hoops_IRS _hoops_HAIAH?
		bool const _hoops_IAIAH = _hoops_CCPR[_hoops_SSGR(_hoops_CCPR) - 1] != '\\';

		// _hoops_IISR _hoops_APRAR _hoops_CAIAH
		const size_t _hoops_PGACP = _MAX_PATH;
		char full_path[_hoops_PGACP+1]; // _hoops_SAIAH _hoops_IH _hoops_ISHRH
		_snprintf(full_path, _hoops_PGACP, "%s%s%s.hlsl", _hoops_CCPR, _hoops_IAIAH ? "\\" : "", name.filename);

		// _hoops_CGP _hoops_GPIAH _hoops_PAH'_hoops_RA _hoops_SIHRR _hoops_RH _hoops_GSGR, _hoops_PSP _hoops_ISHRH _hoops_HRGR _hoops_RPIAH, _hoops_HIS _hoops_SR _hoops_PIHA _hoops_AA _hoops_SGS _hoops_ARI. _hoops_PS _hoops_RAAP _hoops_SPR _hoops_GC _hoops_IH _hoops_RGR.
		full_path[_hoops_PGACP] = '\0';
		if (FILE *fp = fopen(full_path, "rb"))
		{
			// _hoops_GRSH _hoops_AHSC _hoops_HRGR _hoops_RH _hoops_RGHR?
			fseek(fp, 0, SEEK_END);
			_hoops_AAIAH = ftell(fp) + 1;
			fseek(fp, 0, SEEK_SET);

			ALLOC_ARRAY(_hoops_PAIAH, _hoops_AAIAH, char);
			if (_hoops_PAIAH)
				fread(_hoops_PAIAH, 1, _hoops_AAIAH - 1, fp);
			fclose(fp);

			// _hoops_RAGHR
			_hoops_PAIAH[_hoops_AAIAH-1] = '\0';

			// _hoops_ASGR _hoops_GSGR _hoops_CCA _hoops_PGGGH _hoops_PIH _hoops_IH _hoops_HSSI
			name.string = _hoops_PAIAH;
		}
		else
		{
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				Sprintf_S (null, "Postprocess shader %s not found", full_path));
		}
	}

	return _hoops_PAIAH;
}

#endif // _hoops_PAHRH

//
// _hoops_APHRH _hoops_CI _hoops_HCGP _hoops_IS _hoops_APIAH.
//
local ID3DXBuffer *_hoops_PPIAH(DX9Data& dx9data, _hoops_PSIRR name, char const * _hoops_CCHRH, D3DXMACRO const *_hoops_HPIAH, bool _hoops_IPIAH, H3DPost::_hoops_SACRR _hoops_CPIAH, ID3DXConstantTable **_hoops_AIPA = NULL)
{
	char _hoops_SPIAH[_hoops_SA];
	_hoops_SPIAH[0] = 0;

	_hoops_PSIRR _hoops_GGHPR = _hoops_CSIRR(dx9_post_header, 0);

#ifdef H3D_SHADER_DEBUG
	// _hoops_HSRR _hoops_GGAS _hoops_SPHR
	size_t _hoops_AAIAH = 0;
	char const *_hoops_PAIAH = _hoops_RAIAH(name, _hoops_AAIAH);

	size_t _hoops_GHIAH = 0;
	char const *_hoops_RHIAH = _hoops_RAIAH(_hoops_GGHPR, _hoops_GHIAH);
#endif 

	// _hoops_HSRR _hoops_RH _hoops_GHPP
	ID3DXBuffer *_hoops_RSR = NULL;

	if (name.string)
	{
		// _hoops_HPSSA _hoops_AHIAH
		strcat(_hoops_SPIAH, "//=============================\n");
		strcat(_hoops_SPIAH, "//  Begin shader preprocessors \n");
		strcat(_hoops_SPIAH, "//=============================\n");
		if (BIT(name.flags, _hoops_RCIRR))
			strcat(_hoops_SPIAH, "#define NUM_TAPS 4\n");
		if (BIT(name.flags, _hoops_ACIRR))
			strcat(_hoops_SPIAH, "#define NUM_TAPS 8\n");
		if (BIT(name.flags, _hoops_PCIRR))
			strcat(_hoops_SPIAH, "#define NUM_TAPS 12\n");
		if (BIT(name.flags, _hoops_HCIRR))
			strcat(_hoops_SPIAH, "#define NUM_TAPS 16\n");
		if (BIT(name.flags, _hoops_ICIRR))
			strcat(_hoops_SPIAH, "#define TEXCOORD_INPUT_2\n");
		if (BIT(name.flags, _hoops_CCIRR))
			strcat(_hoops_SPIAH, "#define DEPTH_OUTPUT\n");
		if (!dx9data._hoops_GAP)
			strcat(_hoops_SPIAH, "#define DEPTH_PACKING_RGBA\n");

		char buffer[64];
		sprintf(buffer, "#define QUALITY %d\n", _hoops_CPIAH);
		strcat(_hoops_SPIAH, buffer);

		strcat(_hoops_SPIAH, "//=============================\n");
		strcat(_hoops_SPIAH, "//   End shader preprocessors  \n");
		strcat(_hoops_SPIAH, "//=============================\n");

		// _hoops_RGPA _hoops_PHIAH-_hoops_SASI _hoops_RGSPR
		strcat(_hoops_SPIAH, _hoops_GGHPR.string);

		// _hoops_CHSR _hoops_CI _hoops_ACAS.
		strcat(_hoops_SPIAH, name.string);
		if (_hoops_IPIAH)
			strcat(_hoops_SPIAH, dx9_post_pixel);

		// _hoops_APHRH _hoops_CI _hoops_PPR _hoops_AIRI _hoops_GII _hoops_CASRR _hoops_SPHS
		ID3DXBuffer *errors = NULL;
		HRESULT _hoops_IIRHP = D3DXCompileShader(_hoops_SPIAH, _hoops_SSGR(_hoops_SPIAH), _hoops_HPIAH, NULL, "main", _hoops_CCHRH, D3DXSHADER_OPTIMIZATION_LEVEL2, &_hoops_RSR, &errors, _hoops_AIPA);

		// _hoops_HGIRH _hoops_PHHS _hoops_RPP _hoops_SR _hoops_SIPGR'_hoops_RA _hoops_GCSPR _hoops_HHIAH-_hoops_PRPC _hoops_CCGP
		if (FAILED(_hoops_IIRHP) && _hoops_CPIAH == H3DPost::_hoops_ASGP) {
			char const *ptr = errors ? (char const *)errors->GetBufferPointer() : "Unknown error";
#ifdef _DEBUG
			OutputDebugString("D3DX reports shader compilation errors:\n");
			OutputDebugString(ptr);
#endif

			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, 
				Sprintf_S (null, "Postprocess shader compilation error:\n%S", ptr));
		}
		H_SAFE_RELEASE(errors);
	}

#ifdef H3D_SHADER_DEBUG
	// _hoops_PPGGR _hoops_CI _hoops_GSGR _hoops_SR _hoops_PGGGH _hoops_HII _hoops_IHIAH.
	if (_hoops_PAIAH)
		FREE_ARRAY(_hoops_PAIAH, _hoops_AAIAH, char);

	if (_hoops_RHIAH)
		FREE_ARRAY(_hoops_RHIAH, _hoops_GHIAH, char);
#endif // _hoops_CHIAH

	return _hoops_RSR;
}


// _hoops_SHIAH ///////////////////////////////////////////////////////////////////

//
// _hoops_AHRAA. _hoops_IARP _hoops_IS _hoops_SISS _hoops_PPR _hoops_GGARP _hoops_AIRRR.
//
_hoops_GSCRH::_hoops_GSCRH(DX9Data& data) : 
	_hoops_CCARH(data),
	_hoops_GIIAH(*data.pDevice),
	_hoops_RIIAH(NULL),
	_hoops_AIIAH(NULL),
	_hoops_PIIAH(NULL),
	_hoops_GSPP(NULL)
{
	ASSERT(data.pDevice);

	HRESULT _hoops_IIRHP;

	_hoops_PGCRR = null;
	_hoops_ISS = &data;

	memset(_hoops_HIIAH, 0, sizeof(_hoops_HIIAH));

	// _hoops_IIIAH _hoops_AGAPR _hoops_CCA _hoops_CIIAH
	_hoops_GIIAH.AddRef();

	// _hoops_SSHAR/_hoops_CASRR/_hoops_ARPR _hoops_AIRRR
	_hoops_SIIAH();

	// _hoops_GISA _hoops_CPAP
	DWORD const stride = sizeof(Vector);
	DWORD const size = stride * 3;
	_hoops_IIRHP = _hoops_GIIAH.CreateVertexBuffer(size, D3DUSAGE_WRITEONLY, D3DFVF_XYZ, D3DPOOL_MANAGED, &_hoops_PIIAH, NULL);
	if (SUCCEEDED(_hoops_IIRHP))
	{
		// _hoops_GISA _hoops_SHPR-_hoops_GCIAH _hoops_SCPH
		Vector *data = NULL;
		_hoops_IIRHP = _hoops_PIIAH->Lock(0, size, (LPVOID*)&data, 0);
		if (SUCCEEDED(_hoops_IIRHP))
		{	
			// _hoops_AGGRR _hoops_RAAP
			data[0].x = -1.0f;
			data[0].y = 1.0f;
			data[0].z = 0.0f;

			// _hoops_RCIAH
			data[1].x = 3.0f;
			data[1].y = 1.0f;
			data[1].z = 0.0f;

			// _hoops_PGRCR
			data[2].x = -1.0f;
			data[2].y = -3.0f;
			data[2].z = 0.0f;

			_hoops_PIIAH->Unlock();
		}
	}

	// _hoops_GISA _hoops_GPHA _hoops_CAPHR
	D3DVERTEXELEMENT9 const format[] = 
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		D3DDECL_END()
	};

	_hoops_IIRHP = _hoops_GIIAH.CreateVertexDeclaration(format, &_hoops_GSPP);
}

//
// _hoops_ACIAH. _hoops_PPGGR _hoops_CPS.
//
_hoops_GSCRH::~_hoops_GSCRH()
{
	// _hoops_PPGGR _hoops_RH _hoops_CGRPR _hoops_SR _hoops_PCIAH _hoops_GPP _hoops_PSPRH
	_hoops_GIIAH.Release();

	H_SAFE_RELEASE(_hoops_PIIAH);
	H_SAFE_RELEASE(_hoops_GSPP);

	// _hoops_PPGGR _hoops_AIRRR
	_hoops_HCIAH();

	// _hoops_PPGGR _hoops_PSCA
	_hoops_RPCRR();
}

//
// _hoops_PCSH _hoops_ASCA _hoops_RHAA _hoops_AGI
//
bool _hoops_GSCRH::_hoops_GGPP()
{
	// _hoops_RAP _hoops_CPAP
	HRESULT _hoops_IIRHP = _hoops_GIIAH.SetStreamSource(0, _hoops_PIIAH, 0, sizeof(Vector));
	_hoops_CCARH._hoops_SISSA[0] = _hoops_PIIAH;

	if (SUCCEEDED(_hoops_IIRHP))
	{
		_hoops_IIRHP = _hoops_GIIAH.SetVertexDeclaration(_hoops_GSPP);
		if (SUCCEEDED(_hoops_IIRHP))
		{
			// _hoops_RSCS _hoops_SCGR _hoops_ASCS
			_hoops_CCARH._hoops_GSCR->_hoops_IPRS(&_hoops_ICIAH);

			// _hoops_ICSS _hoops_HCH-_hoops_APSP _hoops_ISSGR
			_hoops_GIIAH.SetDepthStencilSurface(NULL);

			// _hoops_GCAR _hoops_IAPRR
			_hoops_RHSA((&_hoops_CCARH), H3DCULL_NONE);

			// _hoops_CHSR _hoops_CCIAH
			ENSURE_TRANSPARENCY(&_hoops_CCARH, FALSE);
			_hoops_RPAP(&_hoops_CCARH, TRUE);
			_hoops_GPRP(&_hoops_CCARH, H3DMASK_RGBA);
			return true;
		}
	}

	return false;
}

//
// _hoops_SP _hoops_GH _hoops_RAS _hoops_ASCA _hoops_RHAA _hoops_AGI
//
void _hoops_GSCRH::_hoops_PRHP()
{
	// _hoops_ICSS _hoops_ISCP _hoops_AIRRR
	_hoops_GIIAH.SetVertexShader(NULL);
	_hoops_GIIAH.SetPixelShader(NULL);

	// _hoops_IPRP _hoops_ASCS
	_hoops_CCARH._hoops_GSCR->_hoops_CHRS(&_hoops_ICIAH);

	//
	// _hoops_GCRR _hoops_RCRR _hoops_RH _hoops_IHAH _hoops_HRGR _hoops_IAR _hoops_CAGGR, _hoops_PAR _hoops_GH _hoops_IS _hoops_ICGIP.
	//

	// _hoops_SCIAH _hoops_RPIC _hoops_PPR _hoops_HIHP _hoops_PIAP _hoops_HCAGR.
	_hoops_CCARH._hoops_GSCR->_hoops_IPPRR(H3DVertexFormat(_hoops_CCARH._hoops_CSC->_hoops_PPCP));
	_hoops_CCARH._hoops_CSC->_hoops_AGSA = NULL;
	_hoops_CCARH._hoops_HCAC = _hoops_CCC;

	// _hoops_ICSS _hoops_GII _hoops_PPR _hoops_HCR _hoops_AI
	for (int t = 0; t < _hoops_CIGP; ++t) {
		_hoops_ASRP(&_hoops_CCARH, t);
	}

	// _hoops_CHSR _hoops_HRP
	_hoops_APSS((&_hoops_CCARH));

	// _hoops_IPRP _hoops_PIAP
	_hoops_GPRP(&_hoops_CCARH, H3DMASK_RGB);
}

//
// _hoops_IGPP _hoops_IRS _hoops_HH _hoops_IS _hoops_RH _hoops_SCGR _hoops_SRGS _hoops_SAAP
//
void _hoops_GSCRH::Copy(H3DRenderTarget * _hoops_PCAP, H3DTexture * src, RGBA const *_hoops_SSHR, H3DTEXTUREFILTERTYPE _hoops_GSIAH)
{	
	D3DTEXTUREFILTERTYPE filter = d3dtexturefilter(_hoops_GSIAH);

	_hoops_ISS->_hoops_GSCR->_hoops_GPAP(_hoops_PCAP);

	if (H3DConstantTable *_hoops_AIPA = _hoops_PIGP(_hoops_HIGP, _hoops_ARCRR))
	{
		// _hoops_IARP _hoops_HAIR
		if (!_hoops_SSHR)
			_hoops_SSHR = &_hoops_IGISA::_hoops_IAHHP;
		_hoops_AIPA->SetVector("ModulationColor", (const float *) _hoops_SSHR);

		// _hoops_IARP _hoops_HH _hoops_IS _hoops_GGSP _hoops_HPPCR
		const DWORD _hoops_PCI = _hoops_AIPA->GetSamplerIndex("Sampler");
		_hoops_SCCR(&_hoops_CCARH, _hoops_PCI, src);
		ENSURE_TEXTURE_WRAP_S(&_hoops_CCARH, _hoops_PCI, D3DTADDRESS_CLAMP);
		_hoops_SAIRH(&_hoops_CCARH, _hoops_PCI, D3DTADDRESS_CLAMP);

		// _hoops_HCGA _hoops_RGRR _hoops_HRP
		_hoops_GPIRH(&_hoops_CCARH, _hoops_PCI, filter);
		_hoops_RPIRH(&_hoops_CCARH, _hoops_PCI, filter);

		// _hoops_HCGA _hoops_IPS _hoops_CI
		_hoops_HPRP(_hoops_PCAP, _hoops_ARCRR, 0, NULL, src);

		// ..._hoops_PPR _hoops_RSIAH _hoops_HH _hoops_HIS _hoops_SR _hoops_PAH _hoops_SRGS _hoops_IS _hoops_SCH _hoops_SPHR.
		_hoops_ASRP(&_hoops_CCARH, _hoops_PCI);
	}
}

//
// _hoops_HCGA _hoops_IRS _hoops_CI _hoops_IS _hoops_RH _hoops_RAGA _hoops_SRGS _hoops_SAAP
//
void _hoops_GSCRH::_hoops_HPRP(IDirect3DSurface9& _hoops_PCAP, _hoops_AGSA which, float depth, D3DXMATRIX const *matrix, H3DTexture *_hoops_IHCRR)
{	
	_hoops_GPAP(_hoops_CCARH, &_hoops_PCAP);
	if (_hoops_CHCRR(which, depth, matrix, _hoops_IHCRR))
	{
		// _hoops_GISP...
		_hoops_GIIAH.DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	}
}

//
// _hoops_CIRP _hoops_IRS _hoops_HH _hoops_IS _hoops_RH _hoops_SCGR _hoops_SRGS _hoops_SAAP
//
void _hoops_GSCRH::_hoops_PPCRR(IDirect3DSurface9 &_hoops_PCAP, H3DTexture * src, int _hoops_HPCRR, Vector const *_hoops_IGGP, D3DTEXTUREFILTERTYPE filter)
{
	_hoops_GPAP(_hoops_CCARH, &_hoops_PCAP);
	
	// _hoops_IPHH (_hoops_PPR _hoops_GCAS _hoops_ACASA) _hoops_IPSP _hoops_RGGP _hoops_CRGR _hoops_IRS _hoops_APP _hoops_CI _hoops_IGIR.
	int _hoops_GSGP;
	if (_hoops_HPCRR <= 4)
		_hoops_GSGP = 4;
	else if (_hoops_HPCRR <= 8)
		_hoops_GSGP = 8;
	else if (_hoops_HPCRR <= 12)
		_hoops_GSGP = 12;
	else
		_hoops_GSGP = 16;

	// _hoops_RRAH _hoops_GGSP _hoops_CI
	_hoops_AGSA which = (_hoops_AGSA)(_hoops_PRCRR + _hoops_GSGP / 4 - 1);

	if (H3DConstantTable *_hoops_AIPA = _hoops_PIGP(_hoops_HIGP, which))
	{
		// _hoops_GRSH _hoops_AHSC _hoops_HRGR _hoops_RH _hoops_HCGP _hoops_HH?
		float const _hoops_CHRP = 1.0f / src->_hoops_IRRP;
		float const _hoops_SHRP = 1.0f / src->_hoops_CRRP;

		// _hoops_PHIR _hoops_GGR _hoops_IPSP _hoops_ARGP
		D3DXVECTOR4 _hoops_SCGP[16];
		for (int i = 0; i < _hoops_HPCRR; ++i)
		{
			// _hoops_GPPR _hoops_IS _hoops_ASIAH _hoops_PSIAH
			_hoops_SCGP[i] = D3DXVECTOR4(_hoops_IGGP[i].x * _hoops_CHRP, _hoops_IGGP[i].y * _hoops_SHRP, 0, _hoops_IGGP[i].z);
		}

		// _hoops_GHPA _hoops_RII _hoops_ARGP
		memset(_hoops_SCGP + _hoops_HPCRR, 0, (_hoops_GSGP - _hoops_HPCRR) * sizeof(D3DXVECTOR4));

		// _hoops_CHSR _hoops_GCSH _hoops_GHAA _hoops_SCH
		_hoops_AIPA->SetVectorArray("Kernel", (const float *) _hoops_SCGP, _hoops_GSGP);

		// _hoops_IARP _hoops_HH _hoops_IS _hoops_GGSP _hoops_HPPCR
		const DWORD _hoops_PCI = _hoops_AIPA->GetSamplerIndex("Sampler");
		_hoops_SCCR(&_hoops_CCARH, _hoops_PCI, src);
		ENSURE_TEXTURE_WRAP_S(&_hoops_CCARH, _hoops_PCI, D3DTADDRESS_CLAMP);
		_hoops_SAIRH(&_hoops_CCARH, _hoops_PCI, D3DTADDRESS_CLAMP);

		// _hoops_HCGA _hoops_RGRR _hoops_HRP
		_hoops_GPIRH((&_hoops_CCARH), _hoops_PCI, filter);
		_hoops_RPIRH((&_hoops_CCARH), _hoops_PCI, filter);

		// _hoops_GISP...
		_hoops_HPRP(_hoops_PCAP, which, 0, NULL, src);

		// ..._hoops_PPR _hoops_RSIAH _hoops_HH _hoops_HIS _hoops_SR _hoops_PAH _hoops_SRGS _hoops_IS _hoops_SCH _hoops_SPHR.
		_hoops_ASRP(&_hoops_CCARH, _hoops_PCI);
	}
}

//
// _hoops_HSIAH _hoops_RGRR _hoops_IIGR _hoops_IRS _hoops_HH _hoops_IS _hoops_RH _hoops_SCGR _hoops_SRGS _hoops_SAAP
//
void _hoops_GSCRH::_hoops_GAIP(IDirect3DSurface9 &_hoops_PCAP, H3DTexture * src, _hoops_AGSA which, int _hoops_HPCRR, Vector const *_hoops_IGGP, D3DTEXTUREFILTERTYPE filter)
{
	_hoops_GPAP(_hoops_CCARH, &_hoops_PCAP);
	
	// _hoops_IPHH (_hoops_PPR _hoops_GCAS _hoops_ACASA) _hoops_IPSP _hoops_RGGP _hoops_CRGR _hoops_IRS _hoops_APP _hoops_CI _hoops_IGIR.
	int _hoops_GSGP = 8;

	if (H3DConstantTable *_hoops_AIPA = _hoops_PIGP(_hoops_HIGP, which))
	{
		// _hoops_GRSH _hoops_AHSC _hoops_HRGR _hoops_RH _hoops_HCGP _hoops_HH?
		float const _hoops_CHRP = 1.0f / src->_hoops_IRRP;
		float const _hoops_SHRP = 1.0f / src->_hoops_CRRP;

		// _hoops_PHIR _hoops_GGR _hoops_IPSP _hoops_ARGP
		D3DXVECTOR4 _hoops_SCGP[16];
		for (int i = 0; i < _hoops_HPCRR; ++i)
		{
			// _hoops_GPPR _hoops_IS _hoops_ASIAH _hoops_PSIAH
			_hoops_SCGP[i] = D3DXVECTOR4(_hoops_IGGP[i].x * _hoops_CHRP, _hoops_IGGP[i].y * _hoops_SHRP, 0, _hoops_IGGP[i].z);
		}

		// _hoops_GHPA _hoops_RII _hoops_ARGP
		memset(_hoops_SCGP + _hoops_HPCRR, 0, (_hoops_GSGP - _hoops_HPCRR) * sizeof(D3DXVECTOR4));

		// _hoops_CHSR _hoops_GCSH _hoops_GHAA _hoops_SCH
		_hoops_AIPA->SetVectorArray("Kernel", (const float *) _hoops_SCGP, _hoops_GSGP);

		// _hoops_IARP _hoops_HH _hoops_IS _hoops_GGSP _hoops_HPPCR
		const DWORD _hoops_PCI = _hoops_AIPA->GetSamplerIndex("Sampler");
		_hoops_SCCR(&_hoops_CCARH, _hoops_PCI, src);
		ENSURE_TEXTURE_WRAP_S(&_hoops_CCARH, _hoops_PCI, D3DTADDRESS_CLAMP);
		_hoops_SAIRH(&_hoops_CCARH, _hoops_PCI, D3DTADDRESS_CLAMP);

		// _hoops_HCGA _hoops_RGRR _hoops_HRP
		_hoops_GPIRH((&_hoops_CCARH), _hoops_PCI, filter);
		_hoops_RPIRH((&_hoops_CCARH), _hoops_PCI, filter);

		// _hoops_GISP...
		_hoops_HPRP(_hoops_PCAP, which, 0, NULL, src);

		// ..._hoops_PPR _hoops_RSIAH _hoops_HH _hoops_HIS _hoops_SR _hoops_PAH _hoops_SRGS _hoops_IS _hoops_SCH _hoops_SPHR.
		_hoops_ASRP(&_hoops_CCARH, _hoops_PCI);
	}
}

//
// _hoops_RGHSP-_hoops_ISIAH _hoops_RGRR _hoops_IIGR _hoops_IRS _hoops_HH _hoops_IS _hoops_RH _hoops_SCGR _hoops_SRGS _hoops_SAAP
//
void _hoops_GSCRH::_hoops_IPCRR(IDirect3DSurface9 &_hoops_PCAP, H3DTexture * src, H3DTexture *depth, int _hoops_HPCRR, Vector const *_hoops_IGGP, D3DTEXTUREFILTERTYPE filter)
{
	// _hoops_IARP _hoops_HCH _hoops_CSIAH
	_hoops_SCCR(&_hoops_CCARH, 1, depth);
	_hoops_GRPA(&_hoops_CCARH, 1, H3DTEXF_POINT, H3DTEXF_NONE, H3DTADDRESS_CLAMP);

	// _hoops_SGPR _hoops_GPRGR _hoops_RGRR
	_hoops_GAIP(_hoops_PCAP, src, _hoops_GACRR, _hoops_HPCRR, _hoops_IGGP, filter);

	// ..._hoops_PPR _hoops_RSIAH _hoops_HCH _hoops_HH _hoops_HIS _hoops_SR _hoops_PAH _hoops_SRGS _hoops_IS _hoops_SCH _hoops_SPHR.
	_hoops_ASRP(&_hoops_CCARH, 1);
}

//
// _hoops_RGPA _hoops_AI _hoops_GIRP.
//
void _hoops_GSCRH::_hoops_AHSH(IDirect3DSurface9 &_hoops_PCAP, H3DTexture ** _hoops_CPCRR, int _hoops_SPCRR, RGBA const *_hoops_RHSH, D3DTEXTUREFILTERTYPE filter)
{
	_hoops_GPAP(_hoops_CCARH, &_hoops_PCAP);

	// _hoops_IPHH (_hoops_PPR _hoops_GCAS _hoops_ACASA) _hoops_IPSP _hoops_RGGP _hoops_CRGR _hoops_IRS _hoops_APP _hoops_CI _hoops_IGIR.
	int _hoops_GSGP = 8;
	_hoops_AGSA which = _hoops_SRCRR;

	// _hoops_RRAH _hoops_GGSP _hoops_CI
	if (H3DConstantTable *_hoops_AIPA = _hoops_PIGP(_hoops_HIGP, which))
	{
		// _hoops_PHIR _hoops_GGR _hoops_IPSP _hoops_ARGP
		D3DXVECTOR4 _hoops_SCGP[8];
		RGBA const color = _hoops_RHSH ? *_hoops_RHSH : RGBA(1,1,1,1);
		for (int i = 0; i < _hoops_SPCRR; ++i)
		{
			// _hoops_SSIAH _hoops_RGR _hoops_SPR
			_hoops_SCGP[i] = D3DXVECTOR4(color.red, color.green, color.blue, color.alpha);
		}

		// _hoops_GHPA _hoops_RII _hoops_ARGP
		memset(_hoops_SCGP + _hoops_SPCRR, 0, (_hoops_GSGP - _hoops_SPCRR) * sizeof(D3DXVECTOR4));

		// _hoops_CHSR _hoops_GCSH _hoops_GHAA _hoops_SCH
		_hoops_AIPA->SetVectorArray("Kernel", (const float *) _hoops_SCGP, _hoops_GSGP);

		// _hoops_IARP _hoops_AI _hoops_IS _hoops_GGSP _hoops_GGCAH
		for ( int i = 0; i < _hoops_SPCRR; ++i ) {
			_hoops_SCCR(&_hoops_CCARH, i, _hoops_CPCRR[i]);
			ENSURE_TEXTURE_WRAP_S(&_hoops_CCARH, i, D3DTADDRESS_CLAMP);
			_hoops_SAIRH(&_hoops_CCARH, i, D3DTADDRESS_CLAMP);

			// _hoops_HCGA _hoops_RGRR _hoops_HRP
			_hoops_GPIRH((&_hoops_CCARH), i, filter);
			_hoops_RPIRH((&_hoops_CCARH), i, filter);
		}

		// _hoops_IARP _hoops_SRS _hoops_HH _hoops_IS _hoops_HHRPA _hoops_GGCAH (_hoops_GRS _hoops_SHH _hoops_IAGGA)
		for ( int i = _hoops_SPCRR; i < _hoops_GSGP; ++i ) {
			_hoops_SCCR(&_hoops_CCARH, i, _hoops_CPCRR[0]);
		}

		// _hoops_GISP...
		_hoops_HPRP(_hoops_PCAP, which, 0, NULL, _hoops_CPCRR[0]);

		// ..._hoops_PPR _hoops_RSIAH _hoops_AI _hoops_HIS _hoops_SR _hoops_PAH _hoops_SRGS _hoops_IS _hoops_CAPR _hoops_SPHR.
		for ( int i = 0; i < _hoops_GSGP; ++i )
			_hoops_ASRP(&_hoops_CCARH, i);
	}
}

//
// _hoops_SIPR _hoops_IRS _hoops_AIGAR _hoops_HCH-_hoops_APSP _hoops_ISSGR
//
H3DRenderTarget *_hoops_GSCRH::_hoops_RCGGR(DWORD width, DWORD height, H3DFORMAT format, bool _hoops_ISARR)
{
	// _hoops_HIGAR _hoops_IIGAR _hoops_GPRR _hoops_CGH _hoops_SR _hoops_IHSH _hoops_IH
	int const _hoops_CIGAR = _hoops_ISARR ? _hoops_CCARH._hoops_ISGRR : 0; 

	// _hoops_PPPA _hoops_PSCA
	for (_hoops_RICRR *buffer = _hoops_PGCRR; buffer != NULL; buffer = buffer->next)
	{
		if (!buffer->_hoops_CPCR && buffer->surface)
		{
			// _hoops_HCIC _hoops_RGR _hoops_SRHR _hoops_GHRP?
			if (buffer->surface->_hoops_IRRP == (int) width && 
				buffer->surface->_hoops_CRRP == (int) height && 
				buffer->surface->_hoops_GSPP == format && buffer->surface->_hoops_HSARR == _hoops_CIGAR)
			{
				buffer->_hoops_CPCR = true;
				return buffer->surface;
			}
		}
	}

	// _hoops_HHPC _hoops_SR _hoops_RRP _hoops_IS _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_SRHR
	H3DRenderTarget *surface = null;
	if ( format == D3DFMT_D24S8 )
		surface = NEW(_hoops_HIARH)(_hoops_ISS, width, height, H3DTEXUSAGE_DEPTHSTENCIL, H3DFMT_D24S8, _hoops_CIGAR, true); 
	else
		surface = NEW(_hoops_HIARH)(_hoops_ISS, width, height, H3DTEXUSAGE_RENDERTARGET, H3DFMT_A8R8G8B8, _hoops_CIGAR); 
	if (surface)
	{
		// _hoops_PHIR _hoops_GGR _hoops_HIGR _hoops_RARP
		_hoops_RICRR *_hoops_PIGAR = new _hoops_RICRR;
		_hoops_PIGAR->_hoops_CPCR = true;
		_hoops_PIGAR->texture = NULL;
		_hoops_PIGAR->surface = surface;

		// _hoops_CHSR _hoops_AGGAR _hoops_IS _hoops_HIGR
		_hoops_PIGAR->next = _hoops_PGCRR;
		_hoops_PGCRR = _hoops_PIGAR;
	}

	return surface;
}


// _hoops_IAIGH _hoops_RGCAH ///////////////////////////////////////////////////////////

//
// _hoops_GCRR _hoops_IRS _hoops_CI _hoops_CISI _hoops_PPR _hoops_ASRC _hoops_RGCI _hoops_SRSR _hoops_GASR _hoops_IH _hoops_RCRAH _hoops_RPP _hoops_SCH _hoops_AICS.
//
H3DConstantTable *_hoops_GSCRH::_hoops_CHCRR(_hoops_AGSA which, float depth, D3DXMATRIX const *matrix, H3DTexture *_hoops_IHCRR)
{
	ASSERT(which >= 0 && which < _hoops_IACRR);

	if (matrix)
	{
		// 3D _hoops_CCH
		if (_hoops_CGCRR)
		{
			_hoops_CGCRR->SetFloat("ConstantDepth", depth);
			_hoops_CGCRR->SetMatrix("ModelToProjection", (const float *) matrix);
		}
		if (_hoops_AIIAH)
		{
			_hoops_GIIAH.SetVertexShader(_hoops_AIIAH);
		}
	}
	else
	{
		// 2D _hoops_CCH
		if (_hoops_IGCRR)
		{
			// _hoops_PS _hoops_PAH _hoops_SGH _hoops_HAGH _hoops_HCH _hoops_HSH _hoops_IS _hoops_HPSSA _hoops_RRRH _hoops_CRGR 3D _hoops_CCRP
			_hoops_IGCRR->SetFloat("ConstantDepth", depth);
			_hoops_SHCRR( _hoops_IHCRR );
		}
		if (_hoops_RIIAH)
		{
			_hoops_GIIAH.SetVertexShader(_hoops_RIIAH);
		}
	}

	// _hoops_HR _hoops_HPCS
	H3DConstantTable *result = NULL;

	// _hoops_APHRH _hoops_AIR _hoops_CI _hoops_RPP _hoops_HAHH
	if (!_hoops_HIIAH[which])
		CreatePixelShader(which);

	// _hoops_CGP _hoops_SR _hoops_HS _hoops_CPS _hoops_SR _hoops_RRP
	if (_hoops_HIIAH[which] && _hoops_SGCRR[0][which])
	{
		// _hoops_RRAH _hoops_CI _hoops_PPR _hoops_ASRC _hoops_GASR _hoops_CHGRR. _hoops_SCH _hoops_AICS.
		HRESULT _hoops_IIRHP = _hoops_GIIAH.SetPixelShader(_hoops_HIIAH[which]);
		if (SUCCEEDED(_hoops_IIRHP))
			result = _hoops_SGCRR[0][which];
	}

	return result;
}

// _hoops_RAPH ////////////////////////////////////////////////////////////////////////
//
// _hoops_SSHAR/_hoops_ARPR/_hoops_CASRR _hoops_HCR _hoops_AIRRR.
//
void _hoops_GSCRH::_hoops_SIIAH()
{
	HRESULT _hoops_IIRHP;

	// _hoops_CRSR _hoops_RPIC _hoops_SARR _hoops_IS _hoops_SGH? _hoops_PS _hoops_GCGH 2 _hoops_PPR 3 _hoops_HPGR _hoops_RH _hoops_HRGS.
	bool const _hoops_AGCAH = _hoops_CCARH._hoops_HPHRH.PixelShaderVersion >= D3DPS_VERSION(3,0);
	char const *_hoops_PGCAH = _hoops_AGCAH ? "vs_3_0" : "vs_2_0";

	// _hoops_ISIRR _hoops_CI _hoops_SARR
	D3DXMACRO const _hoops_HPIAH[] = 
	{
		{ _hoops_AGCAH ? "SHADER_MODEL_3" : "SHADER_MODEL_2", "" },
		{ NULL, NULL },
	};

	// _hoops_GISA _hoops_GPHA _hoops_AIRRR (_hoops_GCSP _hoops_HPP _hoops_HCR)
	ID3DXConstantTable *d3d_constant_table;

	if (ID3DXBuffer *buffer = _hoops_PPIAH(_hoops_CCARH, _hoops_ISHAH, _hoops_PGCAH, _hoops_HPIAH, false, _hoops_ASGP, &d3d_constant_table)) {
		_hoops_IIRHP = _hoops_GIIAH.CreateVertexShader((DWORD*)buffer->GetBufferPointer(), &_hoops_RIIAH);
		_hoops_IGCRR = new _hoops_HGCAH(_hoops_ISS, d3d_constant_table);
		H_SAFE_RELEASE(buffer);
	}

	if (ID3DXBuffer *buffer = _hoops_PPIAH(_hoops_CCARH, _hoops_CSHAH, _hoops_PGCAH, _hoops_HPIAH, false, _hoops_ASGP, &d3d_constant_table)) {
		_hoops_IIRHP = _hoops_GIIAH.CreateVertexShader((DWORD*)buffer->GetBufferPointer(), &_hoops_AIIAH);
		_hoops_CGCRR = new _hoops_HGCAH(_hoops_ISS, d3d_constant_table);
		H_SAFE_RELEASE(buffer);
	}
}

void _hoops_GSCRH::CreatePixelShader(_hoops_AGSA which)
{
	ASSERT(_hoops_HIIAH[which] == null);

	// _hoops_CRSR _hoops_RPIC _hoops_SARR _hoops_IS _hoops_SGH? _hoops_PS _hoops_GCGH 2 _hoops_PPR 3 _hoops_HPGR _hoops_RH _hoops_HRGS.
	bool const _hoops_AGCAH = _hoops_CCARH._hoops_HPHRH.PixelShaderVersion >= D3DPS_VERSION(3,0);
	char const *_hoops_IGCAH = _hoops_AGCAH ? "ps_3_0" : "ps_2_0";

	// _hoops_ISIRR _hoops_CI _hoops_SARR
	D3DXMACRO const _hoops_HPIAH[] = 
	{
		{ _hoops_AGCAH ? "SHADER_MODEL_3" : "SHADER_MODEL_2", "" },
		{ NULL, NULL },
	};

	// _hoops_GISA _hoops_GPHA _hoops_AIRRR (_hoops_GCSP _hoops_HPP _hoops_HCR)
	ID3DXConstantTable *d3d_constant_table;

	// _hoops_RAP _hoops_SHIR
	_hoops_CGCAH[which] = _hoops_ASGP;

	// _hoops_HCIC _hoops_RGR _hoops_IRS _hoops_PSGR _hoops_CCGP _hoops_CI? _hoops_CGP _hoops_HAR, _hoops_HSPP _hoops_HPGR _hoops_HISAR _hoops_SGCAH.
	_hoops_PSIRR const &name = _hoops_SSHAH[which];
	int _hoops_GRCAH = _hoops_ASGP;
	if ( BIT(name.flags, _hoops_SCIRR) )
		_hoops_GRCAH = _hoops_CSGP;
	if ( BIT(name.flags, _hoops_GSIRR) )
		_hoops_GRCAH = _hoops_HGRP;

	// _hoops_HSRR _hoops_GRR _hoops_HHPA _hoops_CCGP _hoops_PAPA
	for ( int _hoops_CPIAH = _hoops_GRCAH; _hoops_CPIAH >= _hoops_ASGP; --_hoops_CPIAH ) {
		if (ID3DXBuffer *buffer = _hoops_PPIAH(_hoops_CCARH, name, _hoops_IGCAH, _hoops_HPIAH, true, static_cast<_hoops_SACRR>(_hoops_CPIAH), &d3d_constant_table)) {
			HRESULT _hoops_IIRHP = _hoops_GIIAH.CreatePixelShader((DWORD*)buffer->GetBufferPointer(), &_hoops_HIIAH[which]);
			_hoops_SGCRR[0][which] = new _hoops_HGCAH(_hoops_ISS, d3d_constant_table);
			H_SAFE_RELEASE(buffer);

			if (_hoops_IIRHP == S_OK) {
				// _hoops_SCPRH _hoops_GPP _hoops_SRS _hoops_PPGAR _hoops_CCGP _hoops_PAPA _hoops_PPR _hoops_PRIA _hoops_SCH
				_hoops_CGCAH[which] = static_cast<_hoops_SACRR>(_hoops_CPIAH);
				break;
			}
		}
	}
}

//
// _hoops_SCAGR _hoops_IIGR _hoops_HCR _hoops_AIRRR.
//
void _hoops_GSCRH::_hoops_HCIAH()
{
	H_SAFE_RELEASE(_hoops_RIIAH);
	H_SAFE_RELEASE(_hoops_AIIAH);
	_hoops_HP(_hoops_IGCRR);
	_hoops_HP(_hoops_CGCRR);
	for (int i = 0; i < _hoops_IACRR; ++i) {
		H_SAFE_RELEASE(_hoops_HIIAH[i]);
		_hoops_HP(_hoops_SGCRR[0][i]);
	}
}

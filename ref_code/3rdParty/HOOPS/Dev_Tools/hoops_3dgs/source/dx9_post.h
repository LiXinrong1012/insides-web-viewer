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
 * $Id: obf_tmp.txt 1.37 2010-05-18 22:59:05 heppe Exp $
*/


#ifndef _hoops_RRCAH
#define _hoops_RRCAH

/*_hoops_CPCHR _hoops_IGCPR*/
class _hoops_GSCRH;
struct DX9Data;
struct IDirect3DDevice9;
struct IDirect3DVertexBuffer9;
struct IDirect3DVertexShader9;
struct IDirect3DPixelShader9;
struct ID3DXConstantTable;

class _hoops_HGCAH : public H3DConstantTable
{
private:
	ID3DXConstantTable *_hoops_ARCAH;

public:
	_hoops_HGCAH(H3DData *h3ddata, void *table):
		H3DConstantTable(h3ddata),
		_hoops_ARCAH((ID3DXConstantTable *) table) {};
	~_hoops_HGCAH() 
	{
		H_SAFE_RELEASE(_hoops_ARCAH);
	};

	void SetFloat(const char *name, const float value)
	{
		_hoops_ARCAH->SetFloat(((DX9Data *)_hoops_ISS)->pDevice, name, value);
	}
	void SetFloatArray(const char *name, const float *values, int count)	
	{
		_hoops_ARCAH->SetFloatArray(((DX9Data *)_hoops_ISS)->pDevice, name, (const float *) values, count);
	}
	void SetMatrix(const char *name, const float *matrix)
	{
		_hoops_ARCAH->SetMatrix(((DX9Data *)_hoops_ISS)->pDevice, name, (const D3DXMATRIX *) matrix);
	}
	void SetVector(const char *name, const float *vector, const int _hoops_IIIRR = 4) 
	{
		if (_hoops_IIIRR == 4)
			_hoops_ARCAH->SetVector(((DX9Data *)_hoops_ISS)->pDevice, name, (const D3DXVECTOR4 *) vector);
		else
			_hoops_ARCAH->SetFloatArray(((DX9Data *)_hoops_ISS)->pDevice, name, vector, _hoops_IIIRR);
	};
	void SetVectorArray(const char *name, const float *_hoops_CIIRR, const float _hoops_SIIRR, const int _hoops_IIIRR = 4) 
	{
		if (_hoops_IIIRR == 4)
			_hoops_ARCAH->SetVectorArray(((DX9Data *)_hoops_ISS)->pDevice, name, (const D3DXVECTOR4 *) _hoops_CIIRR, _hoops_SIIRR);
		else
			_hoops_ARCAH->SetFloatArray(((DX9Data *)_hoops_ISS)->pDevice, name, _hoops_CIIRR, _hoops_SIIRR * _hoops_IIIRR);
	};
	unsigned long GetSamplerIndex(const char *name) 
	{
		return _hoops_ARCAH->GetSamplerIndex(name);
	};
};

class _hoops_GSCRH : public H3DPost
{
public:

	_hoops_GSCRH( DX9Data& data );
	~_hoops_GSCRH();

	bool _hoops_GGPP();					// _hoops_GCIH _hoops_IRS _hoops_RHAA _hoops_PRCAH
	void _hoops_PRHP();	// _hoops_ASAP _hoops_IRS _hoops_RHAA _hoops_PRCAH

	//
	// _hoops_GRIRH _hoops_PICA
	//

	// _hoops_IGPP _hoops_RH _hoops_CHIA _hoops_HH _hoops_IS _hoops_RH _hoops_SAAP
	void Copy( H3DRenderTarget * _hoops_PCAP, H3DTexture *src, RGBA const * _hoops_SSHR = NULL, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT );

	// _hoops_IGPP _hoops_RH _hoops_CHIA _hoops_HH _hoops_IS _hoops_RH _hoops_SAAP
	void Copy( H3DTexture *_hoops_PCAP, H3DTexture *src, RGBA const * _hoops_SSHR = NULL, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT )
	{
		Copy( (H3DRenderTarget *)_hoops_PCAP, src, _hoops_SSHR, filter );
	}

	// _hoops_CIRP _hoops_RH _hoops_CHIA _hoops_HH _hoops_IS _hoops_RH _hoops_SAAP.
	void _hoops_PPCRR( IDirect3DSurface9& _hoops_PCAP, H3DTexture * src, int _hoops_HPCRR, Vector const *_hoops_IGGP, D3DTEXTUREFILTERTYPE filter = D3DTEXF_POINT );

	// _hoops_CIRP _hoops_RH _hoops_CHIA _hoops_HH _hoops_IS _hoops_RH _hoops_SAAP
	void _hoops_PPCRR( H3DTexture * _hoops_PCAP, H3DTexture * src, int _hoops_HPCRR, Vector const *_hoops_IGGP, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT )
	{
		IDirect3DSurface9 *_hoops_HRCAH;
		((_hoops_RIARH *) _hoops_PCAP)->GetSurfaceLevel(0, &_hoops_HRCAH);
		if (_hoops_HRCAH)
			_hoops_PPCRR( *_hoops_HRCAH, src, _hoops_HPCRR, _hoops_IGGP, d3dtexturefilter(filter));

		H_SAFE_RELEASE(_hoops_HRCAH);
	}

	// _hoops_CIRP _hoops_RH _hoops_CHIA _hoops_HH _hoops_IS _hoops_RH _hoops_SAAP
	void _hoops_IPCRR( IDirect3DSurface9& _hoops_PCAP, H3DTexture * src, H3DTexture *depth, int _hoops_HPCRR, Vector const *_hoops_IGGP, D3DTEXTUREFILTERTYPE filter = D3DTEXF_POINT );

	// _hoops_CIRP _hoops_RH _hoops_CHIA _hoops_HH _hoops_IS _hoops_RH _hoops_SAAP (_hoops_HCH _hoops_IRCAH)
	void _hoops_IPCRR( H3DTexture * _hoops_PCAP, H3DTexture * src, H3DTexture *depth, int _hoops_HPCRR, Vector const *_hoops_IGGP, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT )
	{
		IDirect3DSurface9 *_hoops_HRCAH;
		((_hoops_RIARH *) _hoops_PCAP)->GetSurfaceLevel(0, &_hoops_HRCAH);
		if (_hoops_HRCAH)
			_hoops_IPCRR( *_hoops_HRCAH, src, depth, _hoops_HPCRR, _hoops_IGGP, d3dtexturefilter(filter));

		H_SAFE_RELEASE(_hoops_HRCAH);
	}

	// _hoops_CIRP _hoops_RH _hoops_CHIA _hoops_HH _hoops_IS _hoops_RH _hoops_SAAP (_hoops_GPRGR _hoops_CI)
	void _hoops_GAIP( IDirect3DSurface9& _hoops_PCAP, H3DTexture * src, _hoops_AGSA which, int _hoops_HPCRR, Vector const *_hoops_IGGP, D3DTEXTUREFILTERTYPE filter = D3DTEXF_POINT );

	// _hoops_CIRP _hoops_RH _hoops_CHIA _hoops_HH _hoops_IS _hoops_RH _hoops_SAAP (_hoops_GPRGR _hoops_CI)
	void _hoops_GAIP( H3DTexture * _hoops_PCAP, H3DTexture * src, _hoops_AGSA which, int _hoops_HPCRR, Vector const *_hoops_IGGP, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT )
	{
		IDirect3DSurface9 *_hoops_HRCAH;
		((_hoops_RIARH *) _hoops_PCAP)->GetSurfaceLevel(0, &_hoops_HRCAH);
		if (_hoops_HRCAH)
			_hoops_GAIP( *_hoops_HRCAH, src, which, _hoops_HPCRR, _hoops_IGGP, d3dtexturefilter(filter));

		H_SAFE_RELEASE(_hoops_HRCAH);
	}

	// _hoops_RGPA _hoops_RH _hoops_CHIA _hoops_AI _hoops_GIRP _hoops_GPP _hoops_RH _hoops_SAAP
	void _hoops_AHSH( IDirect3DSurface9& _hoops_PCAP, H3DTexture **_hoops_CPCRR, int _hoops_SPCRR, RGBA const *_hoops_SSHR = NULL, D3DTEXTUREFILTERTYPE filter = D3DTEXF_POINT );

	// _hoops_CIRP _hoops_RH _hoops_CHIA _hoops_HH _hoops_IS _hoops_RH _hoops_SAAP
	void _hoops_AHSH( H3DTexture * _hoops_PCAP, H3DTexture **_hoops_CPCRR, int _hoops_SPCRR, RGBA const *_hoops_SSHR = NULL, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT )
	{
		IDirect3DSurface9 *_hoops_HRCAH;
		((_hoops_RIARH *) _hoops_PCAP)->GetSurfaceLevel(0, &_hoops_HRCAH);
		if (_hoops_HRCAH)
			_hoops_AHSH( *_hoops_HRCAH, _hoops_CPCRR, _hoops_SPCRR, _hoops_SSHR, d3dtexturefilter(filter));

		H_SAFE_RELEASE(_hoops_HRCAH);
	}

	// _hoops_CRCAH _hoops_IRS _hoops_CI _hoops_GGR _hoops_AGR _hoops_IS _hoops_RHAAR _hoops_SCH
	INLINE H3DConstantTable *_hoops_PIGP( _hoops_GRCRR const _hoops_CACRR, _hoops_AGSA const which )	
	{ 
		UNREFERENCED(_hoops_CACRR); 
		if (!_hoops_HIIAH[which]) 
			CreatePixelShader(which);
		return _hoops_SGCRR[0][which]; 
	}

	// _hoops_CRCAH _hoops_IRS _hoops_CI'_hoops_GRI _hoops_CCGP _hoops_PAPA
	INLINE _hoops_SACRR _hoops_RSGP( _hoops_AGSA const which )	{ return _hoops_CGCAH[which]; }

	// _hoops_RRAH _hoops_IRS _hoops_CI _hoops_GGR _hoops_AGR _hoops_IS _hoops_SRGS _hoops_IHAAR
	H3DConstantTable *_hoops_CHCRR( _hoops_AGSA which, float depth = 0.0f, D3DXMATRIX const *matrix = NULL, H3DTexture *_hoops_IHCRR = NULL );

	// _hoops_HCGA _hoops_RH _hoops_CHIA _hoops_CI _hoops_IS _hoops_RH _hoops_SAAP
	void _hoops_HPRP( IDirect3DSurface9& _hoops_PCAP, _hoops_AGSA const which, float depth = 0.0f, D3DXMATRIX const *matrix = NULL, H3DTexture *_hoops_IHCRR = NULL  );

	// _hoops_HCGA _hoops_RH _hoops_CHIA _hoops_CI _hoops_IS _hoops_RH _hoops_SAAP
	void _hoops_HPRP( H3DRenderTarget *_hoops_PCAP, _hoops_AGSA const which, float depth = 0.0f, float const *matrix = NULL, H3DTexture *_hoops_IHCRR = NULL  )
	{
		if (_hoops_PCAP) {
			if ( _hoops_PCAP->_hoops_CSARR()) {
				H3DTexture *texture = static_cast<H3DTexture*>(_hoops_PCAP);
				if ( !texture->_hoops_SGPRR() ) {
					IDirect3DSurface9 *surface = null;
					static_cast<_hoops_RIARH*>(texture)->GetSurfaceLevel(0, &surface);
					_hoops_HPRP( *surface, which, depth, reinterpret_cast<D3DXMATRIX const *>(matrix), _hoops_IHCRR );
					H_SAFE_RELEASE(surface);
				}
			}
			else {
				_hoops_HPRP( *static_cast<_hoops_HIARH*>(_hoops_PCAP)->_hoops_IIARH(), which, depth, reinterpret_cast<D3DXMATRIX const *>(matrix), _hoops_IHCRR );
			}
		}
	}

	// _hoops_SIPR _hoops_IRS _hoops_AH _hoops_SRGS-_hoops_SAAP _hoops_HH _hoops_SRHR _hoops_HII _hoops_RH _hoops_IHAH
	H3DRenderTarget *_hoops_RCGGR( const DWORD width, const DWORD height, const H3DFORMAT format, bool _hoops_ISARR );

	// _hoops_SRCAH _hoops_AIRRR _hoops_HII _hoops_IHIAH
	void _hoops_GICRR()
	{
		_hoops_HCIAH();
		_hoops_SIIAH();
	}


private:

	// _hoops_AGGAH _hoops_GACAH
	_hoops_GSCRH& operator=( const _hoops_GSCRH& other )			{ UNREFERENCED(other); ASSERT(0); return *this; }

	DX9Data& _hoops_CCARH;										// _hoops_AHHH _hoops_RHPP _hoops_PIAP
	IDirect3DDevice9 &_hoops_GIIAH;								// _hoops_RAPA _hoops_SISS
	IDirect3DVertexBuffer9 *_hoops_PIIAH;						// _hoops_IPIC _hoops_IH _hoops_SPR _hoops_SCPH
	IDirect3DVertexDeclaration9 *_hoops_GSPP;					// _hoops_GAHAH _hoops_RACAH _hoops_IH _hoops_AGCR _hoops_GIHA
	IDirect3DVertexShader9 *_hoops_RIIAH;				// _hoops_ICPA _hoops_GPHA _hoops_CI
	IDirect3DVertexShader9 *_hoops_AIIAH;				// _hoops_ICPA _hoops_GPHA _hoops_CI _hoops_IH 3D
	IDirect3DPixelShader9 *_hoops_HIIAH[_hoops_IACRR];	// _hoops_ACHAH _hoops_AIR _hoops_AIRRR
	_hoops_SACRR _hoops_CGCAH[_hoops_IACRR];					// _hoops_AACAH _hoops_PAPA _hoops_GGR _hoops_SGH _hoops_IH _hoops_GRR _hoops_CI.

	_hoops_PPRS _hoops_ICIAH;

	// _hoops_RAPH
	void _hoops_SIIAH();								// _hoops_GISA/_hoops_CASRR _hoops_GPHA _hoops_AIRRR
	void CreatePixelShader(_hoops_AGSA which);					// _hoops_GISA/_hoops_CASRR _hoops_AIR _hoops_CI
	void _hoops_HCIAH();									// _hoops_CPCS _hoops_HCR _hoops_AIRRR
};

#endif // _hoops_PACAH



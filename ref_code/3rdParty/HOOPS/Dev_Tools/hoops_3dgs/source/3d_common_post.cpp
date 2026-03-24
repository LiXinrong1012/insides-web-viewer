/*
* Copyright (c) 2009 by Tech Soft 3D, LLC.
* The information contained herein is confidential and proprietary to
* Tech Soft 3D, LLC., and considered a trade secret as defined under
* civil and criminal statutes.	Tech Soft 3D shall pursue its civil
* and criminal remedies in the event of unauthorized use or misappropriation
* of its trade secrets.	 Use of this information by anyone other than
* authorized employees of Tech Soft 3D, LLC. is granted only under a
* written non-disclosure agreement, expressly prescribing the scope and
* manner of such use.
*
* $Id: obf_tmp.txt 1.14 2010-09-22 02:29:38 trask Exp $
*/

//
// _hoops_PHGAR-_hoops_HHGAR _hoops_RGRR _hoops_HICRR
// 
local void _hoops_IHGAR(H3DTexture *_hoops_HIRP, H3DPost *post, int _hoops_RHCRR, int _hoops_CHGAR, Vector const *_hoops_IRIP, int _hoops_SHGAR, Vector const *_hoops_CRIP)
{
	// _hoops_ACGR/_hoops_ARPR _hoops_IRS _hoops_GIGAR _hoops_IH _hoops_RIGAR-_hoops_HHGAR
	if (H3DTexture *_hoops_IIRP = post->_hoops_IAAP(_hoops_HIRP->_hoops_IRRP, _hoops_HIRP->_hoops_CRRP, _hoops_HIRP->_hoops_GSPP))
	{
		for (int i = 0; i < _hoops_RHCRR; ++i)
		{
			post->_hoops_PPCRR(_hoops_IIRP, _hoops_HIRP, _hoops_CHGAR, _hoops_IRIP);
			post->_hoops_PPCRR(_hoops_HIRP, _hoops_IIRP, _hoops_SHGAR, _hoops_CRIP);
		}

		// _hoops_PPGGR _hoops_IRHP _hoops_SRHR
		post->_hoops_HAAP(&_hoops_IIRP);
	}
}


//
// _hoops_SIPR _hoops_IRS _hoops_AIGAR _hoops_SRHR
//
H3DTexture *H3DPost::_hoops_IAAP(unsigned long width, unsigned long height, H3DFORMAT format)
{
	// _hoops_PPPA _hoops_PSCA
	for (_hoops_RICRR *buffer = _hoops_PGCRR; buffer != NULL; buffer = buffer->next)
	{
		if (!buffer->_hoops_CPCR && buffer->texture)
		{
			if (buffer->texture->_hoops_IRRP == (int) width && 
				buffer->texture->_hoops_CRRP == (int) height && 
				buffer->texture->_hoops_GSPP == format)
			{
				buffer->_hoops_CPCR = true;
				return buffer->texture;
			}
		}
	}

	// _hoops_HHPC _hoops_SR _hoops_RRP _hoops_IS _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_SRHR
	H3DTexture *texture = null;
	_hoops_ISS->_hoops_GSCR->CreateTexture(width, height, 1, H3DTEXUSAGE_RENDERTARGET, format, &texture);
	if (texture)
	{
		// _hoops_PHIR _hoops_GGR _hoops_HIGR _hoops_RARP
		_hoops_RICRR *_hoops_PIGAR = new _hoops_RICRR;
		_hoops_PIGAR->_hoops_CPCR = true;
		_hoops_PIGAR->texture = texture;
		_hoops_PIGAR->surface = NULL;

		// _hoops_CHSR _hoops_AGGAR _hoops_IS _hoops_HIGR
		_hoops_PIGAR->next = _hoops_PGCRR;
		_hoops_PGCRR = _hoops_PIGAR;
	}

	return texture;
}

//
// _hoops_SIPR _hoops_IRS _hoops_AIGAR _hoops_HCH-_hoops_APSP _hoops_ISSGR
//
H3DRenderTarget *H3DPost::_hoops_RCGGR(const unsigned long width , const unsigned long height, H3DFORMAT format, bool _hoops_ISARR)
{
	// _hoops_HIGAR _hoops_IIGAR _hoops_GPRR _hoops_CGH _hoops_SR _hoops_IHSH _hoops_IH
	int const _hoops_CIGAR = _hoops_ISARR ? _hoops_ISS->_hoops_ISGRR : 0; 

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
	if ( format == H3DFMT_D24S8 )
		_hoops_ISS->_hoops_GSCR->CreateRenderTarget(width, height, H3DTEXUSAGE_DEPTHSTENCIL, H3DFMT_D24S8, _hoops_CIGAR, &surface);
		//_hoops_ISSGR = _hoops_CCAH _hoops_SIGAR(_hoops_RCCGR, _hoops_IGAA, _hoops_APPS, _hoops_GCGAR, _hoops_RCGAR, _hoops_ACGAR, _hoops_IHPR); 
	else
		_hoops_ISS->_hoops_GSCR->CreateRenderTarget(width, height, H3DTEXUSAGE_RENDERTARGET, H3DFMT_A8R8G8B8, _hoops_CIGAR, &surface);
		//_hoops_ISSGR = _hoops_CCAH _hoops_SIGAR(_hoops_RCCGR, _hoops_IGAA, _hoops_APPS, _hoops_PCGAR, _hoops_SAPC, _hoops_ACGAR); 
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

//
// _hoops_HCGAR _hoops_IRS _hoops_AIGAR _hoops_SRHR _hoops_IS _hoops_RH _hoops_ICGAR _hoops_RAS _hoops_SR'_hoops_RISP _hoops_APCRR _hoops_CCA _hoops_SCH.
//
void H3DPost::_hoops_HAAP(H3DTexture ** texture)
{
	// _hoops_PPPA _hoops_PSCA
	for (_hoops_RICRR *buffer = _hoops_PGCRR; buffer != NULL; buffer = buffer->next)
	{
		if (buffer->texture == *texture)
		{
			buffer->_hoops_CPCR = false;
		}
	}

	*texture = null;
}


//
// _hoops_HSRR _hoops_CCGAR _hoops_PPPR _hoops_AII
//
void H3DPost::_hoops_SHCRR(H3DTexture *src)
{
	if (_hoops_IGCRR)
	{
		float offset[2];

		if ( src ) {
			// _hoops_PS _hoops_RRP _hoops_IS _hoops_SHI _hoops_HPP _hoops_HHAA-_hoops_IRS-_hoops_AIR _hoops_IS _hoops_SSPP _hoops_ARCR _hoops_CGPC _hoops_IS _hoops_ASPA.
			offset[0] = +0.5f / src->_hoops_IRRP;
			offset[1] = -0.5f / src->_hoops_CRRP;
		}
		else {
			offset[0] = offset[1] = 0;
		}

		// _hoops_HCGA _hoops_RGR
		_hoops_IGCRR->SetVector("TexelOffset", offset, 2);
	}
}








//
// _hoops_HCGAR _hoops_IRS _hoops_AIGAR _hoops_SRHR _hoops_IS _hoops_RH _hoops_ICGAR _hoops_RAS _hoops_SR'_hoops_RISP _hoops_APCRR _hoops_CCA _hoops_SCH.
//
void H3DPost::_hoops_IPRGR(H3DRenderTarget ** surface)
{
	// _hoops_PPPA _hoops_PSCA
	for (_hoops_RICRR *buffer = _hoops_PGCRR; buffer != NULL; buffer = buffer->next)
	{
		if (buffer->surface == *surface)
		{
			buffer->_hoops_CPCR = false;
		}
	}

	*surface = null;
}

// _hoops_SCGAR _hoops_GCAC (_hoops_GSGAR _hoops_PISRR) ///////////////////////////////////

//
// _hoops_HCGA _hoops_SPRP _hoops_HAIP _hoops_IS _hoops_IRS _hoops_HH
//
void H3DPost::_hoops_HASH(H3DTexture * texture, int _hoops_RHCRR)
{
	// _hoops_AHH: _hoops_RSGAR _hoops_ASGAR: _hoops_SGPR _hoops_PSGAR _hoops_RHRP _hoops_PPR _hoops_SHI _hoops_ISAR _hoops_ARGP _hoops_IS _hoops_HGCR _hoops_PGCR _hoops_HSGAR
	// _hoops_IH _hoops_RH _hoops_ISGAR _hoops_IIGR _hoops_SPR.

	// _hoops_CSGAR:
	// 1  =  1
	// 1  1  =  2
	// 1  2  1  =  4
	// 1  3  3  1  =  8
	// 1  4  6  4  1  = 16
	// 1  5 10 10  5  1  = 32
	// 1  6 15 20 15  6  1  = 64
	// 1  7 21 35 35 21  7  1 = 128
	// _hoops_AHI.

	// _hoops_SPRP _hoops_RRIP _hoops_CRGR _hoops_SPCR _hoops_PPR _hoops_GHCR - _hoops_RGR _hoops_HRGR _hoops_RH _hoops_SPCR _hoops_ARIP 
	static Vector const _hoops_IRIP[] = 
	{
		Vector ( -3.0f, 0.0f, 1.0f/64.0f ), 
		Vector ( -2.0f, 0.0f, 6.0f/64.0f ),
		Vector ( -1.0f, 0.0f, 15.0f/64.0f ), 
		Vector (  0.0f, 0.0f, 20.0f/64.0f ),
		Vector ( +1.0f, 0.0f, 15.0f/64.0f ),
		Vector ( +2.0f, 0.0f, 6.0f/64.0f ),
		Vector ( +3.0f, 0.0f, 1.0f/64.0f ),
	};

	// _hoops_SPRP _hoops_RRIP _hoops_CRGR _hoops_SPCR _hoops_PPR _hoops_GHCR - _hoops_RGR _hoops_HRGR _hoops_RH _hoops_GHCR _hoops_ARIP 
	static Vector const _hoops_CRIP[] = 
	{
		Vector ( 0.0f, -3.0f, 1.0f/64.0f ), 
		Vector ( 0.0f, -2.0f, 6.0f/64.0f ),
		Vector ( 0.0f, -1.0f, 15.0f/64.0f ), 
		Vector ( 0.0f,  0.0f, 20.0f/64.0f ),
		Vector ( 0.0f, +1.0f, 15.0f/64.0f ),
		Vector ( 0.0f, +2.0f, 6.0f/64.0f ),
		Vector ( 0.0f, +3.0f, 1.0f/64.0f ),
	};

	// _hoops_SGPR _hoops_HICRR
	_hoops_IHGAR(texture, this, _hoops_RHCRR, sizeof(_hoops_IRIP)/sizeof(Vector), _hoops_IRIP,
												  sizeof(_hoops_CRIP)/sizeof(Vector), _hoops_CRIP);
}

//
// _hoops_HCGA _hoops_PGSH-_hoops_HHCRR _hoops_HAIP _hoops_IS _hoops_IRS _hoops_HH
//
void H3DPost::_hoops_PPSH(H3DTexture * texture, int _hoops_RHCRR)
{
	//
	// _hoops_SIIR
	//

	// _hoops_RPSH _hoops_SSGAR - _hoops_AIAA-_hoops_PPRRR _hoops_GGRAR
	int const _hoops_RGRAR = 6;
	float const r = 1.0f;
	float _hoops_AGRAR[_hoops_RGRAR];
	float dxs[_hoops_RGRAR];
	Vector _hoops_IGGP[4];

	// _hoops_AGHP _hoops_PGSH _hoops_PPSR _hoops_PGRAR, _hoops_HGRAR _hoops_RPPR
	float const offset = float(HK_Pi) / 180.0f * 25.0f;
	for ( int i = 0; i < _hoops_RGRAR; ++i ) {
		float const theta = offset + i * 2.0f * float(HK_Pi) / _hoops_RGRAR;
		dxs[i] = r * cos((float)theta);
		_hoops_AGRAR[i] = r * sin((float)theta);
	}

	// _hoops_GRSH _hoops_IGRAR _hoops_RH _hoops_IIPR _hoops_HRGR
	float const w = 0.5f/_hoops_RGRAR;

	// _hoops_HSRR _hoops_CGRAR _hoops_RH _hoops_IIPR
	RGBA const _hoops_SGRAR(w, w, w, w);

	// _hoops_GRSH _hoops_ICSI _hoops_RH _hoops_PGSH _hoops_RSSA _hoops_HSSC _hoops_PSAP (_hoops_HRHC = _hoops_SPAC)
	float const a = 0.85f;

	// _hoops_PHAA _hoops_GRRAR _hoops_AH _hoops_CIPP.
	H3DTexture *input = _hoops_IAAP(texture->_hoops_IRRP, texture->_hoops_CRRP, texture->_hoops_GSPP);
	H3DTexture *_hoops_HIRP = _hoops_IAAP(texture->_hoops_IRRP, texture->_hoops_CRRP, texture->_hoops_GSPP);
	H3DTexture *_hoops_IIRP = _hoops_IAAP(texture->_hoops_IRRP, texture->_hoops_CRRP, texture->_hoops_GSPP);

	// _hoops_RRRAR _hoops_GGSR _hoops_RPP _hoops_SCH _hoops_SRSH.
	if ( !input || !_hoops_HIRP || !_hoops_IIRP )
		goto release;

	// _hoops_IGPP _hoops_HCGP _hoops_HH, _hoops_ARRAR _hoops_HII _hoops_RRSH _hoops_IS _hoops_PGSH (_hoops_AIH _hoops_AIIR _hoops_RCAP) _hoops_GAR _hoops_SR _hoops_PHHR.
	ENSURE_TRANSPARENCY(_hoops_ISS, true);
	_hoops_PPRP(_hoops_ISS, H3DBLEND_SRCALPHA, H3DBLEND_ZERO);
	Copy(input, texture);

	// _hoops_PRRAR _hoops_CIGC, _hoops_RGR _hoops_HRGR _hoops_SAHR _hoops_RGSR _hoops_RH _hoops_CPRP _hoops_GH _hoops_IH _hoops_RH _hoops_HAPR.
	_hoops_PPRP(_hoops_ISS, H3DBLEND_ONE, H3DBLEND_ONE);

	//
	// _hoops_GISA _hoops_PGSH _hoops_GAR _hoops_IGGA _hoops_RSSA
	//

	// _hoops_HSRR _hoops_RH _hoops_HAPR

	// _hoops_GCRR _hoops_HRRAR _hoops_RSGR _hoops_GPP _hoops_PCCP _hoops_PISC _hoops_PHI _hoops_HIS _hoops_SR _hoops_IPS _hoops_GGSR _hoops_CIAH.
	_hoops_RHCRR = (_hoops_RHCRR & ~1) + 1;

	// _hoops_HSRR _hoops_GRR _hoops_HAGA
	for ( int d = 0; d < _hoops_RGRAR; ++d ) {

		// _hoops_IRRAR _hoops_IRS _hoops_PPSR _hoops_HRGR _hoops_HCR _hoops_CIGC
		ENSURE_TRANSPARENCY(_hoops_ISS, false);
		
		// _hoops_SGCH _hoops_GH _hoops_RSSA
		float const dx = dxs[d];
		float const _hoops_CRRAR = _hoops_AGRAR[d];

		// _hoops_HSRR _hoops_GRR _hoops_IPGR
		for ( int p = 0; p < _hoops_RHCRR; ++p ) {
			
			// _hoops_GPPR _hoops_IIGR _hoops_RGR _hoops_IPGR
			float const b = pow(4.0f, static_cast<float>(p));

			// _hoops_RIAA _hoops_ARGP, _hoops_SAAA _hoops_GGSR _hoops_HPP _hoops_AIAA _hoops_GRR _hoops_GHIR
			for ( int s = 0; s < 4; ++s )
			{
				// _hoops_GRSH _hoops_SGIP _hoops_GGSR _hoops_HRGR _hoops_RH _hoops_SRRAR?
				float const u = b * s;
	        
				_hoops_IGGP[s] = Vector(dx * u, _hoops_CRRAR * u, pow(a, u));
			}

			// _hoops_RRPP _hoops_HII _hoops_GARAR _hoops_HH _hoops_GPP _hoops_RH _hoops_SRS _hoops_RIH
			H3DTexture *source;
			if ( p == 0 )
				source = input;
			else
				source = (p & 1) ? _hoops_HIRP : _hoops_IIRP;

			// _hoops_RARAR _hoops_HII _hoops_RIGAR _hoops_IS _hoops_HHGAR
			H3DTexture *_hoops_PCAP = (p & 1) ? _hoops_IIRP : _hoops_HIRP;

			// _hoops_GISP
			_hoops_PPCRR(_hoops_PCAP, source, 4, _hoops_IGGP, H3DTEXF_LINEAR);
		}

		// _hoops_PHAA _hoops_SPR _hoops_HRGR _hoops_CIGC, _hoops_HSPR _hoops_RSSA _hoops_GGCR
		ENSURE_TRANSPARENCY(_hoops_ISS, d > 0);

		// _hoops_RGPA _hoops_CRGR _hoops_IIPR
		Copy(texture, _hoops_HIRP, &_hoops_SGRAR);
	}

release:

	//
	// _hoops_SP _hoops_GH
	//

	// _hoops_PPGGR _hoops_HRGR _hoops_IRAP-_hoops_ICIC
	_hoops_HAAP( &input );
	_hoops_HAAP( &_hoops_HIRP );
	_hoops_HAAP( &_hoops_IIRP );
}

//
// _hoops_HCGA _hoops_AHCRR _hoops_HAIP _hoops_IS _hoops_IRS _hoops_HH
//
void H3DPost::_hoops_PHCRR(H3DTexture * texture, int _hoops_RHCRR)
{
	// _hoops_HPHP _hoops_RRIP _hoops_CRGR _hoops_SPCR _hoops_PPR _hoops_GHCR - _hoops_RGR _hoops_HRGR _hoops_RH _hoops_SPCR _hoops_ARIP 
	Vector const _hoops_IRIP[] = 
	{
		Vector ( -3.0f, 0.0f, 1.0f/7.0f ), 
		Vector ( -2.0f, 0.0f, 1.0f/7.0f ),
		Vector ( -1.0f, 0.0f, 1.0f/7.0f ), 
		Vector (  0.0f, 0.0f, 1.0f/7.0f ),
		Vector ( +1.0f, 0.0f, 1.0f/7.0f ),
		Vector ( +2.0f, 0.0f, 1.0f/7.0f ),
		Vector ( +3.0f, 0.0f, 1.0f/7.0f ),
	};

	// _hoops_HPHP _hoops_RRIP _hoops_CRGR _hoops_SPCR _hoops_PPR _hoops_GHCR - _hoops_RGR _hoops_HRGR _hoops_RH _hoops_GHCR _hoops_ARIP 
	Vector const _hoops_CRIP[] = 
	{
		Vector ( 0.0f, -3.0f, 1.0f/7.0f ), 
		Vector ( 0.0f, -2.0f, 1.0f/7.0f ),
		Vector ( 0.0f, -1.0f, 1.0f/7.0f ), 
		Vector ( 0.0f,  0.0f, 1.0f/7.0f ),
		Vector ( 0.0f, +1.0f, 1.0f/7.0f ),
		Vector ( 0.0f, +2.0f, 1.0f/7.0f ),
		Vector ( 0.0f, +3.0f, 1.0f/7.0f ),
	};

	// _hoops_SGPR _hoops_HICRR
	_hoops_IHGAR(texture, this, _hoops_RHCRR, sizeof(_hoops_IRIP)/sizeof(Vector), _hoops_IRIP,
												  sizeof(_hoops_CRIP)/sizeof(Vector), _hoops_CRIP);
}

//
// _hoops_HCGA _hoops_SPRP _hoops_HAIP _hoops_IS _hoops_IRS _hoops_HH
//
void H3DPost::_hoops_GPSH(H3DTexture * texture, int _hoops_RHCRR)
{
	// _hoops_AHH: _hoops_RSGAR _hoops_ASGAR: _hoops_SGPR _hoops_PSGAR _hoops_RHRP _hoops_PPR _hoops_SHI _hoops_ISAR _hoops_ARGP _hoops_IS _hoops_HGCR _hoops_PGCR _hoops_HSGAR
	// _hoops_IH _hoops_RH _hoops_ISGAR _hoops_IIGR _hoops_SPR.

	// _hoops_CSGAR:
	// 1  =  1
	// 1  1  =  2
	// 1  2  1  =  4
	// 1  3  3  1  =  8
	// _hoops_AHI.

	// _hoops_SPRP _hoops_RRIP _hoops_CRGR _hoops_SPCR _hoops_PPR _hoops_GHCR - _hoops_RGR _hoops_HRGR _hoops_RH _hoops_SPCR _hoops_ARIP 
	static Vector const _hoops_IRIP[] = 
	{
		Vector ( -1.0f, 0.0f, 1.0f/4.0f ), 
		Vector (  0.0f, 0.0f, 2.0f/4.0f ),
		Vector ( +1.0f, 0.0f, 1.0f/4.0f ),
	};

	// _hoops_SPRP _hoops_RRIP _hoops_CRGR _hoops_SPCR _hoops_PPR _hoops_GHCR - _hoops_RGR _hoops_HRGR _hoops_RH _hoops_GHCR _hoops_ARIP 
	static Vector const _hoops_CRIP[] = 
	{
		Vector ( 0.0f, -1.0f, 1.0f/4.0f ), 
		Vector ( 0.0f, -0.0f, 2.0f/4.0f ),
		Vector ( 0.0f, +1.0f, 1.0f/4.0f ),
	};

	// _hoops_SGPR _hoops_HICRR
	_hoops_IHGAR(texture, this, _hoops_RHCRR, sizeof(_hoops_IRIP)/sizeof(Vector), _hoops_IRIP,
												  sizeof(_hoops_CRIP)/sizeof(Vector), _hoops_CRIP);
}

//
// _hoops_HCGA _hoops_AHCRR _hoops_HAIP _hoops_IS _hoops_IRS _hoops_HH
//
void H3DPost::_hoops_CGGGR(H3DTexture * texture, int _hoops_RHCRR)
{
	// _hoops_HPHP _hoops_RRIP _hoops_CRGR _hoops_SPCR _hoops_PPR _hoops_GHCR - _hoops_RGR _hoops_HRGR _hoops_RH _hoops_SPCR _hoops_ARIP 
	Vector const _hoops_IRIP[] = 
	{
		Vector ( -1.0f, 0.0f, 1.0f/3.0f ), 
		Vector (  0.0f, 0.0f, 1.0f/3.0f ),
		Vector ( +1.0f, 0.0f, 1.0f/3.0f ),
	};

	// _hoops_HPHP _hoops_RRIP _hoops_CRGR _hoops_SPCR _hoops_PPR _hoops_GHCR - _hoops_RGR _hoops_HRGR _hoops_RH _hoops_GHCR _hoops_ARIP 
	Vector const _hoops_CRIP[] = 
	{
		Vector ( 0.0f, -1.0f, 1.0f/3.0f ), 
		Vector ( 0.0f,  0.0f, 1.0f/3.0f ),
		Vector ( 0.0f, +1.0f, 1.0f/3.0f ),
	};

	// _hoops_SGPR _hoops_HICRR
	_hoops_IHGAR(texture, this, _hoops_RHCRR, sizeof(_hoops_IRIP)/sizeof(Vector), _hoops_IRIP,
												  sizeof(_hoops_CRIP)/sizeof(Vector), _hoops_CRIP);
}


//
// _hoops_PPGGR _hoops_SHIR _hoops_ICGAR _hoops_AARAR/_hoops_AI
//
void H3DPost::_hoops_RPCRR()
{
	while (_hoops_PGCRR)
	{
		_hoops_RICRR *next = _hoops_PGCRR->next;
		
		// _hoops_SP _hoops_GH
		ASSERT( !_hoops_PGCRR->_hoops_CPCR );
		_hoops_HP(_hoops_PGCRR->texture);
		_hoops_HP(_hoops_PGCRR->surface);
		_hoops_HP(_hoops_PGCRR);

		// _hoops_PARAR _hoops_IS _hoops_SPS _hoops_SRHR
		_hoops_PGCRR = next;
	}
}


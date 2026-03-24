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
* $Id: obf_tmp.txt 1.1016.2.1 2011-01-27 00:08:55 heppe Exp $
*/

#ifndef DX9_DRIVER

#include "hoops.h"
#include "hd_proto.h"

/*
* _hoops_APICR _hoops_PPICR
*/
extern "C"  bool HC_CDECL HD_DX9_Driver (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_GGAGR alter *			_hoops_GHRI, 
	int						request, 
	void *					request_info) 
{
	UNREFERENCED(request_info);
	return HD_No_Driver (_hoops_RIGC, _hoops_GHRI, request, "dx9");
}

#else

#ifdef _DEBUG
#define _hoops_IPARH
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include "windows_wrapper.h"	// _hoops_CGRI <_hoops_SPHGR._hoops_GGHR>, _hoops_PIHA _hoops_RCPS _hoops_SRS :(

#include "hoops.h"
#include "driver.h"
#include "please.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "adt.h"

#include "3d_common.h"

#undef CONST

//#_hoops_PPIP _hoops_CPARH

#define _hoops_SPARH
#ifdef _hoops_SPARH
typedef VStringHash<FILETIME *> _hoops_GHARH;
	_hoops_GHARH *_hoops_RHARH = null;
#endif

//_hoops_GASA: _hoops_SPS _hoops_PGCR _hoops_APGR _hoops_IH _hoops_GSPHR _hoops_RGAR
//#_hoops_AHARH _hoops_PHARH
//#_hoops_PPIP _hoops_PHARH

#define _hoops_HHARH										//_hoops_IHARH _hoops_HSPH _hoops_PGHH

#include "dx9_driver.h"
#include "h3d_hlsl.h"
#include "phdraw.h"

#pragma warning(disable: 4310)	// _hoops_HIIC _hoops_AHHPP _hoops_SRSR _hoops_PIRA

/*****************************************************************************
*****************************************************************************
							_hoops_CHARH _hoops_SACA
*****************************************************************************
*****************************************************************************/
/*
 * _hoops_PGAA
 * _hoops_CAAA _hoops_IRS _hoops_HH _hoops_IS _hoops_IRS _hoops_ISSGR _hoops_HCPRA, _hoops_SCSHA _hoops_RH _hoops_ISSGR _hoops_HRGR _hoops_SHPHP _hoops_GPP _hoops_HPGRR.
 */
class _hoops_SHARH
{
public:
	_hoops_SHARH( IDirect3DTexture9 *texture, DWORD level = 0 ) : _hoops_GIARH(null)
	{
		if ( texture )
			texture->GetSurfaceLevel( level, &_hoops_GIARH );
	}

	_hoops_SHARH( H3DTexture *texture, DWORD level = 0 ) : _hoops_GIARH(null)
	{
		ASSERT( !texture || !texture->_hoops_SGPRR() );
		_hoops_RIARH *dx9 = static_cast<_hoops_RIARH*>(texture);
		if ( dx9 && dx9->_hoops_AIARH() )
			dx9->_hoops_AIARH()->GetSurfaceLevel( level, &_hoops_GIARH );
	}

	~_hoops_SHARH()
	{
		H_SAFE_RELEASE(_hoops_GIARH);
	}

	INLINE operator IDirect3DSurface9* () const
	{
		return _hoops_GIARH;
	}

	INLINE operator IDirect3DSurface9* ()
	{
		return _hoops_GIARH;
	}

private:
	IDirect3DSurface9 *_hoops_GIARH;
};

INLINE IDirect3DSurface9 *_hoops_PIARH( IDirect3DSurface9 *target )
{
	return target;
}

INLINE IDirect3DSurface9 *_hoops_PIARH( H3DRenderTarget *target )
{
	return (target && !target->_hoops_CSARR()) ? static_cast<_hoops_HIARH*>(target)->_hoops_IIARH() : null;
}


/*
 * _hoops_PGAA: _hoops_RAP _hoops_RH _hoops_APRAR _hoops_RIAP _hoops_PIAP.
 */
void _hoops_GPAP (DX9Data& dx9data, IDirect3DSurface9 *_hoops_ISCRR, IDirect3DSurface9 *_hoops_AASP, IDirect3DSurface9 *_hoops_CSCRR, IDirect3DSurface9 *_hoops_SSCRR, IDirect3DSurface9 *_hoops_GGSRR )
{
	// _hoops_IHGCP _hoops_SCGR _hoops_AHCS
	dx9data._hoops_CIARH._hoops_SIARH = _hoops_ISCRR;
	dx9data._hoops_CIARH._hoops_GCARH = _hoops_CSCRR;
	dx9data._hoops_CIARH._hoops_RCARH = _hoops_SSCRR;
	dx9data._hoops_CIARH._hoops_ACARH = _hoops_GGSRR;
	dx9data._hoops_CIARH.ds = _hoops_AASP;

	// _hoops_ASC _hoops_CHR _hoops_SHR _hoops_APP.
	dx9data.pDevice->SetRenderTarget(0, _hoops_ISCRR);
	dx9data.pDevice->SetDepthStencilSurface(_hoops_AASP);

	// _hoops_SAPRR _hoops_HCSS _hoops_RGAR _hoops_APP _hoops_RPP _hoops_IIH _hoops_CHR _hoops_RAPR _hoops_RIAP _hoops_CPPA
	if ( dx9data._hoops_GRAP > 1 )
		dx9data.pDevice->SetRenderTarget(1, _hoops_CSCRR);
	else { 
		ASSERT(_hoops_CSCRR == null);
	}

	if ( dx9data._hoops_GRAP > 2 )
		dx9data.pDevice->SetRenderTarget(2, _hoops_SSCRR);
	else { 
		ASSERT(_hoops_SSCRR == null);
	}

	if ( dx9data._hoops_GRAP > 3 )
		dx9data.pDevice->SetRenderTarget(3, _hoops_GGSRR);
	else { 
		ASSERT(_hoops_GGSRR == null);
	}

	// _hoops_RAP _hoops_PCARH _hoops_RIP _hoops_IIHA _hoops_GPP _hoops_CISI _hoops_SAAP.
	dx9data._hoops_IHP = false;
	if ( dx9data._hoops_CRAP == _hoops_AHRS ) {
		// _hoops_GRSH _hoops_AHSC _hoops_HRGR _hoops_RH _hoops_CCAH _hoops_SAAP, _hoops_HCPC. _hoops_RH _hoops_ASGH _hoops_SPR.
		D3DSURFACE_DESC desc;
		_hoops_ISCRR->GetDesc( &desc );
		if ( desc.Width == dx9data._hoops_HCARH.BackBufferWidth * dx9data._hoops_HSAA &&
			 desc.Height == dx9data._hoops_HCARH.BackBufferHeight * dx9data._hoops_ISAA ) {
			 // _hoops_HR _hoops_RGR _hoops_HRGR _hoops_PCCP _hoops_ICPP _hoops_SAAP _hoops_PPR _hoops_AGSGR _hoops_GPP.
			 dx9data._hoops_IHP = true;
		}
	}

	// _hoops_HRHI _hoops_ISCP _hoops_PRIA _hoops_IIGR _hoops_RH _hoops_ICIH _hoops_IS _hoops_PSSP _hoops_RH _hoops_CCAH _hoops_SPR.
	D3DVIEWPORT9 _hoops_PAPH;
	dx9data.pDevice->GetViewport(&_hoops_PAPH);

	if ( dx9data._hoops_IHP ) {
		// _hoops_CAAA _hoops_ICIH _hoops_ISSC _hoops_IS _hoops_RSRA-_hoops_ISAR _hoops_RPRGR _hoops_PCRR.
		_hoops_PAPH.X /= dx9data._hoops_HSAA;
		_hoops_PAPH.Width /= dx9data._hoops_HSAA;
		_hoops_PAPH.Y /= dx9data._hoops_ISAA;
		_hoops_PAPH.Height /= dx9data._hoops_ISAA;
	}

	dx9data._hoops_CSC->_hoops_CSAA.X = _hoops_PAPH.X;
	dx9data._hoops_CSC->_hoops_CSAA.Y = _hoops_PAPH.Y;
	dx9data._hoops_CSC->_hoops_CSAA.Width = _hoops_PAPH.Width;
	dx9data._hoops_CSC->_hoops_CSAA.Height = _hoops_PAPH.Height;
	dx9data._hoops_CSC->_hoops_CSAA.MinZ = _hoops_PAPH.MinZ;
	dx9data._hoops_CSC->_hoops_CSAA.MaxZ = _hoops_PAPH.MaxZ;
}

/*
 * _hoops_PGAA: _hoops_RAP _hoops_RH _hoops_APRAR _hoops_RIAP _hoops_PIAP.
 */
void _hoops_ICARH::_hoops_GPAP (H3DRenderTarget *_hoops_ISCRR, H3DRenderTarget *_hoops_AASP, H3DRenderTarget *_hoops_CSCRR, H3DRenderTarget *_hoops_SSCRR, H3DRenderTarget *_hoops_GGSRR )
{
	::_hoops_GPAP (
		*_hoops_CCARH,
		_hoops_ISCRR->_hoops_CSARR()			? _hoops_SHARH((_hoops_RIARH *)_hoops_ISCRR) : _hoops_PIARH(_hoops_ISCRR),
		_hoops_AASP && _hoops_AASP->_hoops_CSARR() ? _hoops_SHARH((_hoops_RIARH *)_hoops_AASP) : _hoops_PIARH(_hoops_AASP),
		_hoops_CSCRR && _hoops_CSCRR->_hoops_CSARR() ? _hoops_SHARH((_hoops_RIARH *)_hoops_CSCRR) : _hoops_PIARH(_hoops_CSCRR),
		_hoops_SSCRR && _hoops_SSCRR->_hoops_CSARR() ? _hoops_SHARH((_hoops_RIARH *)_hoops_SSCRR) : _hoops_PIARH(_hoops_SSCRR),
		_hoops_GGSRR && _hoops_GGSRR->_hoops_CSARR() ? _hoops_SHARH((_hoops_RIARH *)_hoops_GGSRR) : _hoops_PIARH(_hoops_GGSRR)
	);
}

/*
 * _hoops_PGAA
 */
void _hoops_ICARH::_hoops_IPRS( _hoops_PPRS *_hoops_HPRS )
{
	IDirect3DSurface9 *surface = null;
	IDirect3DSurface9 *_hoops_SCARH = null;

	// _hoops_GRSH _hoops_AHPH _hoops_AA _hoops_SR _hoops_HIISR _hoops_CCA?
	const int _hoops_GSARH = min(_hoops_HPRS->_hoops_SICRR, _hoops_CCARH->_hoops_GRAP);

	// _hoops_RSCS _hoops_HPHR _hoops_HCSS
	for ( int i = 0; i < _hoops_GSARH; ++i )
		if ( !SUCCEEDED(_hoops_CCARH->pDevice->GetRenderTarget( i, (IDirect3DSurface9 **) &surface )) ) 
			_hoops_HPRS->_hoops_PGRGR[i] = null;
		else
			_hoops_HPRS->_hoops_PGRGR[i] = NEW(_hoops_HIARH)(_hoops_CCARH, surface);

	// _hoops_GHPA _hoops_HHRPA _hoops_AIRP.
	for ( int i = _hoops_GSARH; i < _hoops_HPRS->_hoops_SICRR; ++i )
		_hoops_HPRS->_hoops_PGRGR[i] = null;

	// _hoops_RSCS _hoops_HCH _hoops_SRHR
	_hoops_CCARH->pDevice->GetDepthStencilSurface( (IDirect3DSurface9 **) &_hoops_SCARH );
	if (_hoops_SCARH)
		_hoops_HPRS->depth_stencil = NEW(_hoops_HIARH)(_hoops_CCARH, _hoops_SCARH);
	else
		_hoops_HPRS->depth_stencil = null;
}

void _hoops_RSARH( _hoops_PPRS& _hoops_HPRS )
{
	// _hoops_PPGGR _hoops_HCR _hoops_ISCP _hoops_PRCHR.
	_hoops_HP(_hoops_HPRS.depth_stencil);

	for ( int i = 0; i < _hoops_HPRS._hoops_SICRR; ++i ) {
		_hoops_HP(_hoops_HPRS._hoops_PGRGR[i]);
	}
}

void _hoops_ICARH::_hoops_CHRS( _hoops_PPRS *_hoops_HPRS, bool release )
{
	// _hoops_IPRP _hoops_CPS
	ASSERT( _hoops_HPRS->_hoops_SICRR == 4 );
	_hoops_GPAP(
		_hoops_HPRS->_hoops_PGRGR[0], 
		_hoops_HPRS->depth_stencil, 
		_hoops_HPRS->_hoops_PGRGR[1], 
		_hoops_HPRS->_hoops_PGRGR[2], 
		_hoops_HPRS->_hoops_PGRGR[3]);

	if ( release )
		_hoops_RSARH( *_hoops_HPRS );
}

/**
* _hoops_PGAA: _hoops_RSCS _hoops_ASARH _hoops_HPGRR _hoops_RRGR.
*/
local void _hoops_RSARH( DX9Data& dx9data )
{
	// _hoops_HHPC, _hoops_RCSH _hoops_SCGR _hoops_AHCS
	_hoops_HP(dx9data.render_target);
	_hoops_HP(dx9data.depth_stencil);

	// _hoops_PPGGR _hoops_ISPH _hoops_AARAR _hoops_HIH _hoops_GRHP _hoops_CRCC _hoops_IIGR _hoops_ISPH _hoops_AGSAR _hoops_HIS _hoops_SR _hoops_PAH _hoops_PSASA _hoops_CAPR.
	for (DX9ImageRegion *region = dx9data._hoops_PSARH; region; region = region->next) {
		H_SAFE_RELEASE(region->surface);
	}
	for (DX9DepthRegion *region = dx9data._hoops_HSARH; region; region = region->next) {
		H_SAFE_RELEASE(region->surface);
		H_SAFE_RELEASE(region->texture);
	}
}

/*
* _hoops_PGAA: _hoops_RSCS _hoops_ASARH _hoops_PRCR _hoops_RRGR.
*/
local bool _hoops_ISARH( DX9Data& dx9data, DWORD width, DWORD height, D3DMULTISAMPLE_TYPE _hoops_ISARR )
{
	H3D_TRACE(&dx9data, "create_targets");

	// _hoops_HR _hoops_IR
	bool _hoops_IA = true;

	// _hoops_SIGS _hoops_ARPR _hoops_AHCS _hoops_APPR _hoops_HSAR _hoops_CIAS _hoops_APP _hoops_HH _hoops_IGIR
	if (width > dx9data._hoops_ACGH._hoops_PCGH ||
		height > dx9data._hoops_ACGH._hoops_HCGH)
		_hoops_IA = false;

	// _hoops_HSRR _hoops_PGISR
	H3DFORMAT const _hoops_CSARH = H3DFMT_A8R8G8B8;
	H3DFORMAT const _hoops_SSARH = H3DFMT_D24S8;
	HRESULT _hoops_IIRHP;

	// _hoops_HHCS _hoops_PPR _hoops_ARPR _hoops_CPS _hoops_HPGP _hoops_SR _hoops_SAS _hoops_IS _hoops_SCSS.
	dx9data.render_target = NEW(_hoops_HIARH)(&dx9data, width, height, H3DTEXUSAGE_RENDERTARGET,
		_hoops_CSARH, _hoops_ISARR, false);

	dx9data.depth_stencil = NEW(_hoops_HIARH)(&dx9data, width, height, H3DTEXUSAGE_DEPTHSTENCIL,
		_hoops_SSARH, _hoops_ISARR, false);

	// _hoops_GGPRH _hoops_ISPH _hoops_AARAR
	for (DX9ImageRegion *region = dx9data._hoops_PSARH; region; region = region->next) {
		_hoops_IA = _hoops_IA && SUCCEEDED( _hoops_IIRHP = dx9data.pDevice->CreateRenderTarget( 
			width, height, d3dformat(_hoops_CSARH), 
			_hoops_ISARR, 0, FALSE, &region->surface, null ) );
	}

	for (DX9DepthRegion *region = dx9data._hoops_HSARH; region; region = region->next) {
		_hoops_IA = _hoops_IA && SUCCEEDED( _hoops_IIRHP = dx9data.pDevice->CreateDepthStencilSurface( 
			width, height, d3dformat(_hoops_SSARH), 
			_hoops_ISARR, 0, FALSE, &region->surface, null ) );

		// _hoops_CAIP'_hoops_RA _hoops_PSASA _hoops_HCH _hoops_HH _hoops_ISSGR - _hoops_SRIPR _hoops_GPP _hoops_HRGGR
	}

	// _hoops_CGP _hoops_PA _hoops_SRSH, _hoops_CASI _hoops_GH
	if ( !_hoops_IA )
		_hoops_RSARH(dx9data);

	UNREFERENCED (_hoops_IIRHP);
	// _hoops_AP
	return _hoops_IA;
}

/*
* _hoops_PGAA: _hoops_PISPR _hoops_AHHH _hoops_RHPP _hoops_CRGR _hoops_RH _hoops_RAGA _hoops_HSGRR _hoops_CCH.
*/
local bool _hoops_RGPRH( DX9Data& dx9data, _hoops_CGGRR mode, int _hoops_AGPRH )
{
	H3D_TRACE(&dx9data, "set_antialias_mode");
	ASSERT(mode != _hoops_SGGRR);

	// _hoops_GSCA _hoops_AHCI _hoops_ISAR _hoops_PSGC.
	if ( _hoops_AGPRH < 0 )
		// _hoops_SGAA _hoops_HRGR _hoops_AIAA _hoops_IGPR.
		_hoops_AGPRH = 4;
	else if ( _hoops_AGPRH <= 1 )
		// _hoops_GHPA _hoops_PPR _hoops_SPR _hoops_PHGA _hoops_SPR _hoops_ISAR, _hoops_HAS._hoops_IAS. _hoops_PSP _hoops_ARHP.
		_hoops_AGPRH = 0;
	
	if ( HOOPS_WORLD->vram_size <= 0x08000000 )
		// _hoops_CGP _hoops_RH _hoops_PGPRH _hoops_SSCP 128_hoops_HGPRH _hoops_PAR _hoops_CRGP, _hoops_HHSP _hoops_IGPRH-_hoops_CGPRH
		_hoops_AGPRH = 0;

	// _hoops_GSCA _hoops_AHCI _hoops_CCH _hoops_PSGC.
	if ( _hoops_AGPRH == 0 )
		mode = _hoops_GRGRR;

	// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HSGRR, _hoops_SGPRH _hoops_PCPA _hoops_GSIA _hoops_GCGH _hoops_SR _hoops_HS.
	DWORD _hoops_GRPRH = _hoops_AGPRH;
	if ( mode != _hoops_GRGRR ) {

		_hoops_RRPRH alter *_hoops_IRSRA = _hoops_ARPRH ();
		D3D_System_Data alter *d3d_sd = (D3D_System_Data*) _hoops_IRSRA->d3d_shared_data;

		while ( FAILED( d3d_sd->_hoops_SHSSA->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT, 
			D3DDEVTYPE_HAL, D3DFMT_A8R8G8B8, TRUE, static_cast<D3DMULTISAMPLE_TYPE>(_hoops_GRPRH), null ) ) ) {
			--_hoops_GRPRH;
			if ( _hoops_GRPRH <= 1 )
				break;
		}

		// _hoops_CGP _hoops_SR _hoops_HGRC _hoops_GSIA _hoops_RRGS _hoops_PPR _hoops_SR _hoops_PAH'_hoops_RA _hoops_HS _hoops_SCH, _hoops_IIPGA _hoops_IS _hoops_ICPP
		if ( _hoops_GRPRH <= 1 && mode == _hoops_SRAP ) {
			mode = _hoops_AHRS;
		}
	}

	// _hoops_CGP _hoops_SR _hoops_CHR _hoops_AIAH _hoops_GGR _hoops_RGR _hoops_CCH _hoops_CCA _hoops_RGR _hoops_ISAR _hoops_RPR.., _hoops_ISAP _hoops_IS _hoops_AA.
	if ( mode == dx9data._hoops_CRAP && _hoops_AGPRH == dx9data._hoops_CSGRR )
		return true;

	// _hoops_GCIH _hoops_HPIAA _hoops_SR _hoops_PAH _hoops_SGH _hoops_RH _hoops_PSHR _hoops_PHI _hoops_IIGR _hoops_IGPR _hoops_GAR _hoops_AAPR _hoops_HGRC.
	int _hoops_CAP = _hoops_AGPRH;

	// _hoops_HHPC _hoops_SR'_hoops_GCPP _hoops_PSASA _hoops_HCSS
	_hoops_RSARH(dx9data);

	// _hoops_CPCS _hoops_GPPC _hoops_CR _hoops_SSIA _hoops_RRP _hoops_PRPRH _hoops_IH _hoops_RH _hoops_CCAH _hoops_ARHP _hoops_CCH
	dx9data._hoops_GSCR->_hoops_IGSRR(&dx9data);

	// _hoops_HR _hoops_HPCS
	bool _hoops_IA = false;

	// _hoops_HSRR _hoops_SSCH
	DWORD const _hoops_HRPRH = dx9data._hoops_HCARH.BackBufferWidth;
	DWORD const _hoops_IRPRH = dx9data._hoops_HCARH.BackBufferHeight;

	// _hoops_HGI _hoops_HRGR _hoops_RH _hoops_ICRP _hoops_IHPH _hoops_CCH. _hoops_CGIP _hoops_HPIPR.
	if ( mode == _hoops_AHRS ) {
		// _hoops_CAAA _hoops_CRPRH _hoops_CRGR _hoops_PCCP _hoops_ICPP _hoops_CAPS. _hoops_SRPRH 2x2 _hoops_PPR 2x1. 2x1 _hoops_HRGR _hoops_HHSH _hoops_HAR _hoops_GHGC _hoops_SCH _hoops_GGR _hoops_CCGP _hoops_CSHCR.
		int width_scale = 2;
		int _hoops_IISHP = 2;
		if ( _hoops_CAP < 4 )
			_hoops_IISHP = 1;
		ASSERT(width_scale * _hoops_IISHP <= _hoops_CAP);

		// _hoops_AGGA _hoops_HPPR _hoops_PPR _hoops_ARPR _hoops_HCR _hoops_RH _hoops_HCSS _hoops_IH _hoops_GRR _hoops_IGIR.
		while ( !_hoops_IA && mode == _hoops_AHRS ) {
			_hoops_IA = _hoops_ISARH(dx9data, _hoops_HRPRH * width_scale, _hoops_IRPRH * _hoops_IISHP, D3DMULTISAMPLE_NONE);
			if ( !_hoops_IA ) {
				// _hoops_HCRAR _hoops_SRS _hoops_IGAA, _hoops_PSCR _hoops_APPS.
				if ( width_scale > _hoops_IISHP )
					--width_scale;
				else 
					--_hoops_IISHP;

				// _hoops_CGP _hoops_SR _hoops_HGCR _hoops_IS 1x1, _hoops_SR _hoops_SPGA'_hoops_RA _hoops_CPIC _hoops_IS _hoops_HGCR _hoops_GII _hoops_GAPRH.
				if ( width_scale == 1 && _hoops_IISHP == 1 ) {
					HE_WARNING (HEC_DX9_DRIVER, HEC_DX9_DRIVER,
						"Could not create rendertargets for supersample antialiasing.");
					mode = _hoops_GRGRR;
				}
			}
		}

		// _hoops_GSIH _hoops_RH _hoops_PPGAR _hoops_IGAA/_hoops_APPS _hoops_CSRA
		if ( _hoops_IA ) {
			_hoops_CAP = width_scale * _hoops_IISHP;
			dx9data._hoops_HSAA = width_scale;
			dx9data._hoops_ISAA = _hoops_IISHP;
		}
	}

	// _hoops_HHCS _hoops_RRGS _hoops_RPP _hoops_HGRC.
	if ( mode == _hoops_SRAP ) {

		// _hoops_HGI _hoops_HRGR _hoops_PCPA _hoops_SR _hoops_PAH _hoops_GCGH, _hoops_AISP _hoops_ARRS.
		_hoops_CAP = _hoops_GRPRH;

		// _hoops_RAPRH _hoops_SR _hoops_SSS _hoops_IRS _hoops_GHRP _hoops_ISAR _hoops_RPR?
		if ( _hoops_CAP <= 1 ) {
			HE_WARNING (HEC_DX9_DRIVER, HEC_DX9_DRIVER,
				"Could not find hardware support for multisample antialiasing.");
			mode = _hoops_GRGRR;
		}
		else {
			// _hoops_HHCS _hoops_PPR _hoops_SGH _hoops_RH _hoops_CCH.
			_hoops_IA = _hoops_ISARH(dx9data, _hoops_HRPRH, _hoops_IRPRH, static_cast<D3DMULTISAMPLE_TYPE>(_hoops_CAP));

			if ( !_hoops_IA ) {
				HE_WARNING (HEC_DX9_DRIVER, HEC_DX9_DRIVER,
					"Could not create rendertargets for multisample antialiasing.");
				mode = _hoops_GRGRR;
			}
		}

		// _hoops_CSH _hoops_ICPP
		dx9data._hoops_HSAA = 1;
		dx9data._hoops_ISAA = 1;
	}

	// _hoops_HHCS _hoops_PSP _hoops_ARHP _hoops_RPP _hoops_HGRC.
	if ( mode == _hoops_GRGRR ) {
		_hoops_CAP = 0;
		_hoops_IA = _hoops_ISARH(dx9data, _hoops_HRPRH, _hoops_IRPRH, D3DMULTISAMPLE_NONE);

		if ( !_hoops_IA ) {
			HE_ERROR (HEC_DX9_DRIVER, HEC_DX9_DRIVER,
				"Could not create driver rendertargets.");
		}

		// _hoops_CSH _hoops_ICPP
		dx9data._hoops_HSAA = 1;
		dx9data._hoops_ISAA = 1;
	}

	if ( _hoops_IA ) {

		//
		// _hoops_SIPR _hoops_CPS _hoops_HRPP.
		// 

		// _hoops_RAP _hoops_RGR _hoops_SRS _hoops_HIS _hoops_SAAP _hoops_HGISR _hoops_CACH _hoops_SCH. _hoops_SAH _hoops_HGRC _hoops_IGPR _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_HGCR _hoops_AAPRH
		// _hoops_RCSAR _hoops_PAAP _hoops_PAPRH _hoops_SR _hoops_PAH'_hoops_RA _hoops_GCGH _hoops_RH _hoops_CCH _hoops_RH _hoops_RPRGR _hoops_SSGRR _hoops_IH.
		dx9data._hoops_CRAP = mode;
		dx9data._hoops_ISGRR = _hoops_CAP;
		dx9data._hoops_CSGRR = _hoops_AGPRH;

		// _hoops_HRHI _hoops_HRPRA.
		Display_Context alter *_hoops_HAPRH = (Display_Context alter *)dx9data.dc;
		_hoops_HAPRH->_hoops_PGCC.flags |= _hoops_PAGIP;
		_hoops_HAPRH->_hoops_PGCC.flags &= ~_hoops_GIHSR;

		// _hoops_SPAA _hoops_ARP _hoops_AHCS _hoops_PPR _hoops_ICIH _hoops_IS _hoops_RSIR _hoops_CSCR.
		dx9data._hoops_GSCR->_hoops_GPAP(dx9data.render_target, dx9data.depth_stencil);
		_hoops_HHRS((&dx9data), 0, 0, _hoops_HRPRH, _hoops_IRPRH);
	}

	// _hoops_AP
	return _hoops_IA;
}

/*
* _hoops_PGAA. _hoops_IAPRH() _hoops_RCGRA _hoops_IS _hoops_CAPRH _hoops_PAAP

*/

void _hoops_SGPAR(H3DData* data)
{

	DX9Data& dx9data = *((DX9Data*)data);


	// _hoops_SAPRH _hoops_SPAHR (_hoops_RAPA _hoops_GPPRH) _hoops_IH _hoops_AHHH _hoops_HRGR _hoops_IS _hoops_ARPR _hoops_PPR _hoops_RPPRH _hoops_IRS _hoops_RACGH.
	IDirect3DQuery9 *_hoops_APPRH = null;
	if ( SUCCEEDED(dx9data.pDevice->CreateQuery( D3DQUERYTYPE_EVENT, &_hoops_APPRH )) )
	{
		// _hoops_PPPRH _hoops_RH _hoops_PGRRR _hoops_GGR _hoops_RH _hoops_IRGAA _hoops_SRHR.
		_hoops_APPRH->Issue(D3DISSUE_END);

		// _hoops_HPPRH _hoops_RH _hoops_IRGAA _hoops_SRHR _hoops_PPR _hoops_IPPRH _hoops_CCGR _hoops_RH _hoops_CGRH _hoops_HRGR _hoops_CPPRH.
		while ( _hoops_APPRH->GetData( null, 0, D3DGETDATA_FLUSH ) == S_FALSE ) {
			// _hoops_SPPRH.
		}

		// _hoops_PAGA _hoops_SGS _hoops_SCH _hoops_HRGR _hoops_SAPIA _hoops_IS _hoops_ISPR _hoops_IH _hoops_GHPRH _hoops_HAR _hoops_RHPRH, _hoops_GAR _hoops_IIH _hoops_CHR _hoops_PGCR _hoops_SSRR
		// _hoops_RSGR _hoops_SSSC:
		// _hoops_RHPRH - _hoops_RACGH _hoops_CSAP _hoops_AHPRH
		// _hoops_PHPRH - _hoops_SISS _hoops_CSAP _hoops_CISS _hoops_RHSP _hoops_RPPRH.
		// _hoops_GPGP _hoops_RH _hoops_HHPRH _hoops_AGIR _hoops_SR _hoops_PAH _hoops_SAHR _hoops_SSPC _hoops_RH _hoops_HPCS _hoops_PPR _hoops_HIAP _hoops_RH _hoops_SISS _hoops_RHIR
		// _hoops_GSSR _hoops_GRIP.

		// _hoops_PPGGR _hoops_RH _hoops_RACGH
		H_SAFE_RELEASE(_hoops_APPRH);
	}
	else
	{
		// _hoops_HGI _hoops_HRGR _hoops_RH _hoops_RHGS _hoops_RRGR, _hoops_HIH _hoops_SCH _hoops_IHPRH _hoops_RAPA _hoops_SPHS, _hoops_HIS _hoops_SR _hoops_RGAR _hoops_SGH _hoops_SCH _hoops_GAR _hoops_IRS _hoops_IIPGA
		// _hoops_RPP _hoops_SR _hoops_PAH'_hoops_RA _hoops_ARPR _hoops_RH _hoops_RACGH _hoops_CARA.
		D3DLOCKED_RECT _hoops_HC;
		int _hoops_CHPRH = 0;
		IDirect3DSurface9 *_hoops_SHPRH;
		dx9data.pDevice->GetBackBuffer (0, _hoops_CHPRH, 
			D3DBACKBUFFER_TYPE_MONO, &_hoops_SHPRH);
		for (;;) {
			HRESULT _hoops_IIRHP = _hoops_SHPRH->LockRect (&_hoops_HC, 0, D3DLOCK_DONOTWAIT);
			if (SUCCEEDED (_hoops_IIRHP))
				break;
			else if (_hoops_IIRHP != D3DERR_WASSTILLDRAWING) {
				HE_ERROR (HEC_DX9_DRIVER, HEC_DX9_DRIVER, "Could not synch dx9 update.");
				break;
			}
		} 
		_hoops_SHPRH->UnlockRect ();
		H_SAFE_RELEASE (_hoops_SHPRH);
	}
}

/*****************************************************************************
*****************************************************************************
							_hoops_GIPRH _hoops_SACA
*****************************************************************************
*****************************************************************************/

class _hoops_RIPRH : public H3DGPUTimer
{
public:
	_hoops_RIPRH(H3DData* data) :
		H3DGPUTimer(data),
		_hoops_AIPRH(null),
		_hoops_PIPRH(null),
		_hoops_HIPRH(null)
	{
		DX9Data *dx9data = (DX9Data *)_hoops_ISS;
		// _hoops_GISA _hoops_IIPRH _hoops_IH _hoops_SPPP _hoops_PRPP, _hoops_PPR _hoops_CIPRH.
		dx9data->pDevice->CreateQuery( D3DQUERYTYPE_TIMESTAMP, &_hoops_AIPRH );
		dx9data->pDevice->CreateQuery( D3DQUERYTYPE_TIMESTAMP, &_hoops_PIPRH );
		dx9data->pDevice->CreateQuery( D3DQUERYTYPE_TIMESTAMPFREQ, &_hoops_HIPRH );

		// _hoops_CGP _hoops_SR _hoops_GGHP _hoops_CAPR _hoops_HCR, _hoops_SR _hoops_PAH _hoops_SGH _hoops_GSIA _hoops_SIPRH
		if ( _hoops_AIPRH && _hoops_PIPRH && _hoops_HIPRH )
			_hoops_RGIGR = _hoops_ARIGR;
	}

	// _hoops_SP _hoops_GH
	~_hoops_RIPRH()
	{
		H_SAFE_RELEASE(_hoops_AIPRH);
		H_SAFE_RELEASE(_hoops_PIPRH);
		H_SAFE_RELEASE(_hoops_HIPRH);
	}

	// _hoops_RRPP _hoops_GHIR _hoops_HII _hoops_CGHI _hoops_PRPP. _hoops_CGIGR _hoops_AASA *_hoops_SAHR _hoops_ARPP* _hoops_RH _hoops_PRPP _hoops_IS _hoops_SRCH _hoops_SGIGR _hoops_GRIGR.
	size_t _hoops_SRPP()
	{
		size_t _hoops_IRPP = 0;

		if ( _hoops_RGIGR == _hoops_AGIGR )
			_hoops_IRPP = static_cast<size_t>(_hoops_IGIGR - _hoops_HGIGR);
		else {
			ASSERT( _hoops_RGIGR == _hoops_HRIGR || _hoops_RGIGR == _hoops_ARIGR );

			if ( _hoops_RGIGR == _hoops_HRIGR ) {
				// _hoops_GCPRH _hoops_HCR _hoops_IIPRH _hoops_IH _hoops_PIH.
				UINT64 start, end, _hoops_RCPRH;
				if ( _hoops_HIPRH->GetData( &_hoops_RCPRH, sizeof(_hoops_RCPRH), 0 ) == S_OK &&
					 _hoops_AIPRH->GetData( &start, sizeof(start), 0 ) == S_OK &&
					 _hoops_PIPRH->GetData( &end, sizeof(end), 0 ) == S_OK ) {

					// _hoops_PS _hoops_GGHP _hoops_CAPR _hoops_HCR. _hoops_SSSA _hoops_RIAPR _hoops_ACPRH _hoops_PPR _hoops_PCPRH _hoops_SPS _hoops_PRPP.
					_hoops_IRPP = static_cast<size_t>((end-start)/(_hoops_RCPRH/1000));
					
					_hoops_RGIGR = _hoops_ARIGR;
				}
			}
		}

		// _hoops_CPPP _hoops_SRS _hoops_RRAIA _hoops_IRIGR _hoops_CR _hoops_SCH'_hoops_GRI _hoops_SHR _hoops_RHPH
		if ( _hoops_IRPP > 0 && _hoops_PGIGR ) {
			_hoops_IRPP = 0;
			_hoops_PGIGR = false;
		}
	
		return _hoops_IRPP;
	}

	// _hoops_PCSH _hoops_IRS _hoops_SPPP _hoops_PRPP
	void _hoops_GGPP()
	{
		DX9Data *dx9data = (DX9Data *)_hoops_ISS;
		if ( _hoops_RGIGR == _hoops_AGIGR ) {
			// _hoops_ACIPA _hoops_CGRH
			_hoops_SGPAR( dx9data ); 

			// _hoops_GCIH _hoops_SPPP
			_hoops_HGIGR = HI_What_Time();
		}
		else {
			// _hoops_HCPRH _hoops_CRAA. _hoops_ICPRH _hoops_CCAH _hoops_IIPRH _hoops_IH _hoops_HSPP _hoops_IIGR _hoops_PRPP _hoops_RPP _hoops_SSIA _hoops_SPGA'_hoops_RA _hoops_GGR-_hoops_CCPRH.
			if ( _hoops_RGIGR == _hoops_ARIGR ) {
				_hoops_HIPRH->Issue( D3DISSUE_END );
				_hoops_AIPRH->Issue( D3DISSUE_END );

				_hoops_RGIGR = _hoops_PRIGR;
			}
		}
	}

	void _hoops_PRHP()
	{
		DX9Data *dx9data = (DX9Data *)_hoops_ISS;
		if ( _hoops_RGIGR == _hoops_AGIGR ) {
			// _hoops_ACIPA _hoops_CGRH
			_hoops_SGPAR( dx9data ); 

			// _hoops_SCPRH _hoops_SPPP
			_hoops_IGIGR = HI_What_Time();
		}
		else {
			// _hoops_HCPRH _hoops_CRAA. _hoops_ICPRH _hoops_CCAH _hoops_RACGH _hoops_IH _hoops_RSGR _hoops_IIGR _hoops_PRPP _hoops_RPP _hoops_SR _hoops_AIS _hoops_SPR.
			if ( _hoops_RGIGR == _hoops_PRIGR ) {
				_hoops_PIPRH->Issue( D3DISSUE_END );

				_hoops_RGIGR = _hoops_HRIGR;
			}
		}
	}

private:
	// _hoops_HCPRH _hoops_IIPRH
	IDirect3DQuery9 *_hoops_AIPRH;
	IDirect3DQuery9 *_hoops_PIPRH;
	IDirect3DQuery9 *_hoops_HIPRH;
};


// _hoops_AHH: _hoops_CAIP'_hoops_RA _hoops_ARPR _hoops_CCAH _hoops_HCHIA _hoops_PSPA _hoops_IS _hoops_SRCH _hoops_RIPHR _hoops_GSPRH.
#include "dx9_post.h"
#include "dx9_post.cpp"

static XBits	_hoops_RSPRH[] = {
	{"BAD_MSAA_SPRITING",		XBIT_BAD_MSAA_SPRITING},
	{"BAD_DEPTH_PEELING",		XBIT_BAD_DEPTH_PEELING},
	{"POINT_SPRITES_BASH_ALL",	XBIT_POINT_SPRITES_BASH_ALL},
	{"",						0},
};

/*
 * _hoops_PGAA
 * _hoops_ASPRH _hoops_GPP _hoops_PSPRH/_hoops_HPGRR.
 */
class BlockTimer
{
public:

	BlockTimer(const char * _hoops_RHSRR) : _hoops_AHSRR(_hoops_RHSRR)
	{
		_hoops_HSPRH = HI_What_Time() * (1.0 / _hoops_HSPGR);
	}

	~BlockTimer()
	{
		double _hoops_ASPGR = HI_What_Time() * (1.0 / _hoops_HSPGR);

		char buffer[512];
		_snprintf(buffer, 511, "Block \"%s\" took %d ms\n", _hoops_AHSRR, static_cast<int>(1000 * (_hoops_ASPGR - _hoops_HSPRH)));
		buffer[511] = '\0';

		::OutputDebugStringA(buffer);
	}

private:
	const char *_hoops_AHSRR;
	double _hoops_HSPRH;
};


local void _hoops_ISPRH (const Display_Context *dc);

local void _hoops_RSCSR (_hoops_APARR & _hoops_RRCI);

local void _hoops_CSPRH(Display_Context const * dc)
{
	DX9Data alter *dx9data = DX9D (dc);
	dx9data->pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	dx9data->pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	dx9data->pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	dx9data->pDevice->SetRenderState(D3DRS_ALPHAREF, MAKEWORD(1,1));
	_hoops_ISPRH (dc);
}


/*****************************************************************************
*****************************************************************************
							_hoops_SSPRH _hoops_PISRR
*****************************************************************************
*****************************************************************************/

/*****************************************************************************
*****************************************************************************
							_hoops_GGHRH _hoops_PISRR
*****************************************************************************
*****************************************************************************/


_hoops_RGHRH::_hoops_RGHRH(const H3DShaderID& id) : 
	H3DShader(id),
	m_pDevice(null),
	_hoops_AGHRH(null),
	_hoops_PGHRH(null),
	m_pVSConstantTable(null),
	m_pPSConstantTable(null)
{
}
_hoops_RGHRH::~_hoops_RGHRH()
{
    H_SAFE_RELEASE(m_pVSConstantTable);
    H_SAFE_RELEASE(m_pPSConstantTable);
    H_SAFE_RELEASE(_hoops_AGHRH);
    H_SAFE_RELEASE(_hoops_PGHRH);
}

local void _hoops_HGHRH(const char *_hoops_IGHCP, const char *_hoops_HHCAP = null)
{
	_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, Sprintf_SS(null, "DX9 driver shader construction error: %s failed (%s)", _hoops_IGHCP, (_hoops_HHCAP ? _hoops_HHCAP : "") ) );
}

local void _hoops_IGHRH(ID3DXBuffer *buffer, const char *type)
{
	const char *ptr = buffer ? (const char *)buffer->GetBufferPointer() : "Unknown";

	// _hoops_SRIGP _hoops_IIGR _hoops_CIPP _hoops_SPHS _hoops_CHR _hoops_CCSHP _hoops_PGGA _hoops_SR _hoops_PAH _hoops_RCRPA _hoops_HSSI.
	// _hoops_IAS._hoops_ISHI.
	// _hoops_CGHRH: _hoops_HAR _hoops_RAPR _hoops_SGHRH _hoops_CCGGR _hoops_CPPA
	// _hoops_GRHRH: _hoops_HAR _hoops_RAPR _hoops_CCGGR _hoops_CPPA
	// _hoops_RRHRH: _hoops_GGPR _hoops_RAIA _hoops_HH _hoops_ARHRH _hoops_PGPP _hoops_GGR _hoops_IRS _hoops_PRHRH _hoops_AASH _hoops_SGS _hoops_HRGR _hoops_HAH _hoops_SIRAR _hoops_IH _hoops_RH _hoops_SAAP _hoops_CI _hoops_SARR (_hoops_HRHRH) _hoops_IS _hoops_RGHH.
	// _hoops_IRHRH: _hoops_SIGS _hoops_ARCR _hoops_CRHRH _hoops_IS _hoops_AIR _hoops_CI _hoops_CCGGR _hoops_ARP.
	if (!strstr(ptr, "X5608") && !strstr(ptr, "X5609") && !strstr(ptr, "X5426") && !strstr(ptr, "X4532") )
	{
#ifdef _DEBUG
		// _hoops_SRHRH _hoops_CHR _hoops_GGR _hoops_GAHRH _hoops_RPCC _hoops_IH _hoops_RAHRH _hoops_AAHRH - _hoops_HSPAA _hoops_IS _hoops_HISRA _hoops_GGSR
		OutputDebugString("D3DX reports shader compilation errors:\n");
		OutputDebugStringA(ptr);
#endif // _hoops_PAHRH

		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, 
			Sprintf_SS (null, "%s shader compilation error reported by dx9:\n%S", type, ptr));
	}
}

struct _hoops_HAHRH
{
	unsigned int major, minor;
	char const *_hoops_HHRAR;
	char const *ps;
};

// _hoops_CIHGR _hoops_CI _hoops_IAHRH _hoops_CGAS _hoops_HPP _hoops_SARR.
_hoops_HAHRH const _hoops_CAHRH[_hoops_PARR] = 
{
	// _hoops_AHH: _hoops_RCPA _hoops_RPGP _hoops_HAGH _hoops_CI _hoops_SARR _hoops_GCGH, _hoops_AGRP _hoops_RH _hoops_ARSSA _hoops_CSPP _hoops_RGGHR
	// _hoops_IIGR _hoops_RH _hoops_AIRRR _hoops_RHAC _hoops_GA'_hoops_RA _hoops_HHGC _hoops_IS _hoops_GCGH _hoops_IS _hoops_CPHP _hoops_CHPP.
	// _hoops_IAS._hoops_ISHI. { 9,0, "_hoops_SAHRH", "_hoops_GPHRH" } _hoops_GRS _hoops_RPGP _hoops_RPHRH _hoops_PPR _hoops_CAPP.
	{ 2,0, "vs_2_0", "ps_2_0" },
	{ 2,0, "vs_2_0", "ps_2_a" },
	{ 3,0, "vs_3_0", "ps_3_0" },
};

//
// _hoops_APHRH _hoops_PPR _hoops_ARPR _hoops_CI. _hoops_PAGA _hoops_SGS _hoops_SR _hoops_PAH'_hoops_RA _hoops_CIPAA _hoops_RH _hoops_CGI-_hoops_GGR _hoops_RCC, _hoops_PGAP _hoops_HRGR _hoops_IGI _hoops_IS _hoops_CIHA
// _hoops_RH _hoops_CI. _hoops_PS _hoops_AA _hoops_CIPAA _hoops_RH _hoops_CI _hoops_RCC _hoops_RIRIA _hoops_GGR _hoops_HHH _hoops_ARAR (_hoops_CGPR _hoops_RH _hoops_CI _hoops_CCGP _hoops_IRHS _hoops_IS
// _hoops_SHH _hoops_AHAAR _hoops_GGR _hoops_AGR _hoops_IS _hoops_CASRR _hoops_SCH _hoops_PPHRH.)
//
bool _hoops_RGHRH::Create(H3DData *h3ddata, const char *_hoops_IASRR) 
{
	DX9Data *dx9data = (DX9Data *) h3ddata;
	_hoops_ISS = h3ddata;

	IDirect3DDevice9 *pDevice = dx9data->pDevice;
	D3DCAPS9 *_hoops_ACGH = &dx9data->_hoops_HPHRH;
	HRESULT _hoops_IIRHP = 0;
    ID3DXBuffer *_hoops_IPHRH = null;
    ID3DXBuffer *_hoops_CPHRH = null;
	IDirect3DVertexShader9 *_hoops_SPHRH = null;
	IDirect3DPixelShader9 *_hoops_GHHRH = null;
	ID3DXConstantTable *_hoops_RHHRH = null;
	ID3DXConstantTable *_hoops_AHHRH = null;
	ID3DXBuffer *_hoops_PHHRH = null;
	ID3DXBuffer *_hoops_HHHRH = null;
	ID3DXBuffer *_hoops_IHHRH = null;
	bool status = false;
	char *_hoops_GP, *_hoops_CA, *ptr, *_hoops_CHHRH, *_hoops_SHHRH;
	char _hoops_GIAAR[4096];
	DWORD _hoops_SRRS = 0;
	int _hoops_GIHRH, _hoops_RIHRH;

	// _hoops_ARGH _hoops_RPP _hoops_SR _hoops_HS _hoops_IRS _hoops_IPSP _hoops_CI
	if (_hoops_PCC._hoops_RIHR()) {
		_hoops_PCC._hoops_IHRAR((POINTER_SIZED_INT *) &_hoops_IPHRH, (POINTER_SIZED_INT  *) &_hoops_CPHRH);

		_hoops_IIRHP = dx9data->pDevice->CreateVertexShader(
			(DWORD*)_hoops_IPHRH->GetBufferPointer(), &_hoops_SPHRH);
		_hoops_IIRHP = dx9data->pDevice->CreatePixelShader(
			(DWORD*)_hoops_CPHRH->GetBufferPointer(), &_hoops_GHHRH);

		if (SUCCEEDED(_hoops_IIRHP)) {
			// _hoops_SAH _hoops_CPS
			_hoops_AGHRH = _hoops_SPHRH;
			_hoops_PGHRH = _hoops_GHHRH;
			m_pDevice = pDevice;
			status = true;
			return true;
		}
		else {
			H_SAFE_RELEASE(_hoops_SPHRH);
			H_SAFE_RELEASE(_hoops_GHHRH);
			return false;
		}
	}


	_hoops_GP = h3ddata->_hoops_GP;
	_hoops_CA = h3ddata->_hoops_CA;
	_hoops_CHHRH = &_hoops_GP[_hoops_SA-1];
	_hoops_SHHRH = &_hoops_CA[_hoops_SA-1];

#ifdef H3D_SHADER_DEBUG
	_hoops_SRRS |= D3DXSHADER_DEBUG;
#endif
	/* _hoops_RRPS _hoops_IS: _hoops_IHHRA://_hoops_AIHRH._hoops_PIHRH._hoops_HIHRH/_hoops_IIHRH-_hoops_IHHH/_hoops_GIRPR/_hoops_CIHRH._hoops_SIHRH
	 * _hoops_SR _hoops_PAH _hoops_GACC _hoops_SGH (_hoops_GCHRH |= _hoops_RCHRH) _hoops_ARR 
	 * _hoops_SR _hoops_PHHR _hoops_IS _hoops_ACHRH */

	//_hoops_GCHRH |= _hoops_PCHRH;

	// _hoops_HCHRH _hoops_HAPR - _hoops_SGHHR _hoops_IS _hoops_IIPGA _hoops_CGPR _hoops_HSSI _hoops_ISHS
	while (_hoops_CPHRH == null || _hoops_IPHRH == null)
	{
		// _hoops_SGAA _hoops_IS _hoops_HHPS _hoops_GGR _hoops_ISPP _hoops_PIGGP _hoops_SARR.
		int start = 0;
		int end = _hoops_PARR;
		int _hoops_IGHCP = 1;

		if ( _hoops_PCC._hoops_RIRAR() == _hoops_SARAR ) {
			// _hoops_CGP _hoops_RH _hoops_CI _hoops_IRHS _hoops_CASH-_hoops_RSGR _hoops_ICHRH, _hoops_CASRR _hoops_GPSGR _hoops_HARAR _hoops_SRS.
			start = _hoops_PARR-1;
			end = -1;
			_hoops_IGHCP = -1;
		}

		for (int _hoops_CRRR = start; _hoops_CRRR != end ; _hoops_CRRR += _hoops_IGHCP )
		{
			const _hoops_HAHRH& _hoops_CCHRH = _hoops_CAHRH[_hoops_CRRR];

			// _hoops_HCIC _hoops_RH _hoops_HAPIA _hoops_APP?
			bool _hoops_SCHRH = _hoops_ACGH->VertexShaderVersion >= D3DVS_VERSION(_hoops_CCHRH.major,_hoops_CCHRH.minor) &&
							 _hoops_ACGH->PixelShaderVersion >= D3DPS_VERSION(_hoops_CCHRH.major,_hoops_CCHRH.minor);

			// _hoops_CGP _hoops_RH _hoops_CI _hoops_SARR _hoops_HRGR 2X, _hoops_SR _hoops_RRP _hoops_IS _hoops_ISPR _hoops_HHH _hoops_SIC _hoops_RIRR _hoops_SIH _hoops_IH _hoops_RH _hoops_GSHRH _hoops_RIRR _hoops_SR _hoops_RRP.
			if ( (_hoops_CRRR == _hoops_CARAR) && !(_hoops_ACGH->PS20Caps.Caps & D3DPS20CAPS_GRADIENTINSTRUCTIONS) )
				 _hoops_SCHRH = false;

			if ( _hoops_SCHRH ) {
				/* 
				 * _hoops_IISR _hoops_GPHA _hoops_CI _hoops_HCGP _hoops_RRGR
				 */
				if (_hoops_CCHRH.major == 3)
					_hoops_HCC = true;
				else
					_hoops_HCC = false;

				ptr = _hoops_CA;
				_hoops_PAHR (_hoops_PCC, true, _hoops_GIAAR);
				if (_hoops_GIAAR && _hoops_GIAAR[0] != '\0') {
					sprintf (ptr, "#line 1 \"%s\"\n", _hoops_GIAAR);
					ptr += _hoops_SSGR(ptr);
				}
				if ((ptr = _hoops_AIGR ("dx9_header.hlsl", dx9_header, ptr, _hoops_SHHRH)) == null) {
					_hoops_HGHRH( "append", "dx9_header.hlsl" );
					goto release;
				}
				if ((ptr = _hoops_HRRR (_hoops_PCC, ptr, _hoops_SHHRH, static_cast<_hoops_IRRR>(_hoops_CRRR), _hoops_GCGR)) == null) {
					_hoops_HGHRH( "preamble" );
					goto release;
				}
				if ((ptr = _hoops_RHGR ("h3d_macros.hlsl", _hoops_RSHRH, ptr, _hoops_SHHRH, _hoops_GCGR)) == null) {
					_hoops_HGHRH( "macros" );
					goto release;
				}
				if ((ptr = _hoops_AIGR ("h3d_material.hlsl", _hoops_ASHRH, ptr, _hoops_SHHRH)) == null) {
					_hoops_HGHRH( "append", "h3d_material.hlsl" );
					goto release;
				}
				if ((ptr = _hoops_AIGR ("h3d_common.hlsl", _hoops_PSHRH, ptr, _hoops_SHHRH)) == null) {
					_hoops_HGHRH( "append", "h3d_common.hlsl" );
					goto release;
				}
				if ((ptr = _hoops_AIGR ("h3d_vertex.hlsl", _hoops_HSHRH, ptr, _hoops_SHHRH)) == null) {
					_hoops_HGHRH( "append", "h3d_vertex.hlsl" );
					goto release;
				}
				if ((ptr = _hoops_AIGR ("dx9_common.hlsl", dx9_common, ptr, _hoops_SHHRH)) == null) {
					_hoops_HGHRH( "append", "dx9_common.hlsl" );
					goto release;
				}
				if ((ptr = _hoops_AIGR ("dx9_vertex.hlsl", dx9_vertex, ptr, _hoops_SHHRH)) == null) {
					_hoops_HGHRH( "append", "dx9_vertex.hlsl" );
					goto release;
				}
				_hoops_GIHRH = ptr - _hoops_CA;
				if (!_hoops_GAGR (_hoops_CA, &_hoops_GIHRH)) {
					_hoops_HGHRH( "dead-strip" );
					goto release;
				}
				if (_hoops_GIAAR[0] != '\0') {
					_hoops_IHHR (_hoops_GIAAR, _hoops_CA);
				}

				// _hoops_ARGH _hoops_SPCC - _hoops_SPR _hoops_CRRPR _hoops_ISHRH, _hoops_RH _hoops_RII _hoops_ASSP'_hoops_RA.
				ASSERT(_hoops_GIHRH == 1 + _hoops_SSGR(_hoops_CA));

				/* 
				 * _hoops_IISR _hoops_AIR _hoops_CI _hoops_HCGP _hoops_RRGR
				 */
				ptr = _hoops_GP;
				_hoops_PAHR (_hoops_PCC, false, _hoops_GIAAR);
				if (_hoops_GIAAR && _hoops_GIAAR[0] != '\0') {
					sprintf (ptr, "#line 1 \"%s\"\n", _hoops_GIAAR);
					ptr += _hoops_SSGR(ptr);
				}
				if ((ptr = _hoops_AIGR ("dx9_header.hlsl", dx9_header, ptr, _hoops_CHHRH)) == null) {
					_hoops_HGHRH( "append", "dx9_header.hlsl" );
					goto release;
				}
				if ((ptr = _hoops_HRRR (_hoops_PCC, ptr, _hoops_CHHRH, static_cast<_hoops_IRRR>(_hoops_CRRR), _hoops_RPRR)) == null) {
					_hoops_HGHRH( "preamble" );
					goto release;
				}
				if ((ptr = _hoops_RHGR ("h3d_macros.hlsl", _hoops_RSHRH, ptr, _hoops_CHHRH, _hoops_RPRR)) == null) {
					_hoops_HGHRH( "macros" );
					goto release;
				}
				if ((ptr = _hoops_AIGR ("h3d_material.hlsl", _hoops_ASHRH, ptr, _hoops_CHHRH)) == null) {
					_hoops_HGHRH( "append", "h3d_material.hlsl" );
					goto release;
				}
				if (_hoops_IASRR != null) {
					const int length = _hoops_SSGR(_hoops_IASRR) + 2;
					if ( length > (_hoops_CHHRH - ptr) ) {
						_hoops_HGHRH( "material shader" );
						goto release;
					}
					sprintf(ptr, "\n%s\n", _hoops_IASRR);
					ptr += length;
				}
				if ((ptr = _hoops_AIGR ("h3d_common.hlsl", _hoops_PSHRH, ptr, _hoops_CHHRH)) == null) {
					_hoops_HGHRH( "append", "h3d_common.hlsl" );
					goto release;
				}
				if ((ptr = _hoops_AIGR ("h3d_pixel.hlsl", _hoops_CSHRH, ptr, _hoops_CHHRH)) == null) {
					_hoops_HGHRH( "append", "h3d_pixel.hlsl" );
					goto release;
				}
				if ((ptr = _hoops_AIGR ("dx9_common.hlsl", dx9_common, ptr, _hoops_CHHRH)) == null) {
					_hoops_HGHRH( "append", "dx9_common.hlsl" );
					goto release;
				}
				if ((ptr = _hoops_AIGR ("dx9_pixel.hlsl", dx9_pixel, ptr, _hoops_CHHRH)) == null) {
					_hoops_HGHRH( "append", "dx9_pixel.hlsl" );
					goto release;
				}
				_hoops_RIHRH = ptr - _hoops_GP;
				if (!_hoops_GAGR (_hoops_GP, &_hoops_RIHRH)) {
					_hoops_HGHRH( "dead-strip" );
					goto release;
				}
				if (_hoops_GIAAR[0] != '\0') {
					_hoops_IHHR (_hoops_GIAAR, _hoops_GP);
				}

				// _hoops_ARGH _hoops_SPCC - _hoops_SPR _hoops_CRRPR _hoops_ISHRH, _hoops_RH _hoops_RII _hoops_ASSP'_hoops_RA.
				ASSERT(_hoops_RIHRH == 1 + _hoops_SSGR(_hoops_GP));

				/*
				 * _hoops_APHRH _hoops_AIRRR
				 */

				do {
					// _hoops_RHCP _hoops_CI
					_hoops_IIRHP = D3DXCompileShader(
						_hoops_CA,				
						(UINT)(_hoops_GIHRH), 
						null,
						null,
						"main",
						_hoops_CCHRH._hoops_HHRAR,				
						_hoops_SRRS,
						&_hoops_IPHRH, 
						&_hoops_PHHRH, // _hoops_RIHH _hoops_SSHRH 
						&_hoops_RHHRH);

					if (!SUCCEEDED (_hoops_IIRHP)) {
						if (HDX9_OUT_OF_MEMORY(_hoops_IIRHP)) {
							if(!_hoops_ARAGR(h3ddata, 10000000)) {
								HE_ERROR (HEC_DX9_DRIVER, HES_OUT_OF_MEMORY,
									"Not enough memory to compile vertex shader."); 
								goto release;
							}
						}
						else
							_hoops_IGHRH(_hoops_PHHRH, "Vertex");
						H_SAFE_RELEASE(_hoops_IPHRH);
						H_SAFE_RELEASE(_hoops_PHHRH);
						H_SAFE_RELEASE(_hoops_RHHRH); 
						continue;
					}
					

					// _hoops_SSHI _hoops_CI
					_hoops_IIRHP = D3DXCompileShader(
						_hoops_GP,				
						(UINT)(_hoops_RIHRH), 
						null,
						null,
						"main",
						_hoops_CCHRH.ps,				
						_hoops_SRRS,
						&_hoops_CPHRH, 
						&_hoops_HHHRH, // _hoops_RIHH _hoops_SSHRH 
						&_hoops_AHHRH);

					if (!SUCCEEDED (_hoops_IIRHP)) {
						if (HDX9_OUT_OF_MEMORY(_hoops_IIRHP)) {
							if(!_hoops_ARAGR(h3ddata, 10000000)) {
								HE_ERROR (HEC_DX9_DRIVER, HES_OUT_OF_MEMORY,
									"Not enough memory to compile pixel shader."); 
								goto release;
							}
						}
						else if (_hoops_IASRR) {
							// _hoops_SAH _hoops_GGHS _hoops_APIR _hoops_CI _hoops_RIHH _hoops_IH _hoops_SPHR
							_hoops_IGHRH(_hoops_HHHRH, "Pixel");
							H_SAFE_RELEASE(_hoops_IHHRH);
							_hoops_IHHRH = _hoops_HHHRH;
						}
						else {
							// _hoops_CICR _hoops_RHRRH _hoops_RH _hoops_RIHH
							_hoops_IGHRH(_hoops_HHHRH, "Pixel");
							H_SAFE_RELEASE(_hoops_HHHRH);
						}
						H_SAFE_RELEASE(_hoops_CPHRH);
						H_SAFE_RELEASE(_hoops_AHHRH);
						continue;
					}

					// _hoops_CGP _hoops_GIPR _hoops_GGIRH _hoops_SCSS, _hoops_SR'_hoops_ASAR _hoops_CPHR
					if (_hoops_CPHRH && _hoops_IPHRH)
						goto done;

				} while (HDX9_OUT_OF_MEMORY(_hoops_IIRHP));
			}
		}

		//
		// _hoops_RGIRH _hoops_SR _hoops_RRP _hoops_IS _hoops_PSRAR _hoops_CCGP _hoops_PPR _hoops_HPPR _hoops_GICS
		//

		if (!_hoops_PCC._hoops_CCRAR())
		{
			// _hoops_CSH _hoops_RRI _hoops_ASRAR _hoops_IS _hoops_PSRAR _hoops_CCGP.
			if (_hoops_PCC._hoops_SHC()) {
				// _hoops_IIPI _hoops_CCGP
				_hoops_PCC = _hoops_ACC;

				// _hoops_SCPRH _hoops_GRP _hoops_APIR _hoops_CI _hoops_AGIRH.
				_hoops_PCC._hoops_PCRAR();
				_hoops_IASRR = null;

				// _hoops_PGIRH _hoops_APIR _hoops_CI _hoops_RIHH
				if ( _hoops_IHHRH ) {
					_hoops_IGHRH(_hoops_IHHRH, "Material");
					H_SAFE_RELEASE(_hoops_IHHRH);
				}
			}
			else {
				// _hoops_CSH _hoops_RRI _hoops_ASRAR _hoops_IS _hoops_HSSC _hoops_ISSC. _hoops_HGIRH.
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "DX9 driver could not compile shader - too complex" );
				break;
			}
		}
	}

done: 

	// _hoops_RAPRH _hoops_HSSI _hoops_SCSS?
	if (_hoops_CPHRH && _hoops_IPHRH)
	{
		_hoops_IIRHP = pDevice->CreateVertexShader(
			(DWORD*)_hoops_IPHRH->GetBufferPointer(), &_hoops_SPHRH);
		_hoops_IIRHP = pDevice->CreatePixelShader(
			(DWORD*)_hoops_CPHRH->GetBufferPointer(), &_hoops_GHHRH);
	}

release:

	// _hoops_RAPRH _hoops_RH _hoops_RHPP _hoops_IGIRH _hoops_IS _hoops_ARPR _hoops_RH _hoops_CI?
	if (_hoops_GHHRH && _hoops_SPHRH)
	{
		// _hoops_SAH _hoops_CPS
		m_pVSConstantTable = _hoops_RHHRH;
		m_pPSConstantTable = _hoops_AHHRH;
		_hoops_AGHRH = _hoops_SPHRH;
		_hoops_PGHRH = _hoops_GHHRH;
		m_pDevice = pDevice;
		status = true;
	}
	else
	{
		// _hoops_PPGGR _hoops_CPS
        H_SAFE_RELEASE(_hoops_RHHRH); 
        H_SAFE_RELEASE(_hoops_AHHRH); 
        H_SAFE_RELEASE(_hoops_SPHRH);    
        H_SAFE_RELEASE(_hoops_GHHRH); 
    }

	// _hoops_PPGGR _hoops_AH _hoops_PIH
    H_SAFE_RELEASE(_hoops_IPHRH);  
    H_SAFE_RELEASE(_hoops_CPHRH);  
	H_SAFE_RELEASE(_hoops_PHHRH);
	H_SAFE_RELEASE(_hoops_HHHRH);
	H_SAFE_RELEASE(_hoops_IHHRH);
	return status;
}


void _hoops_RGHRH::_hoops_RAPRR(H3DTexture *texture, H3DData *h3ddata)
{
	if (_hoops_PCC._hoops_RIHR())
		return;

	_hoops_RIARH *_hoops_CGIRH = (_hoops_RIARH *) texture;
	DX9Data *dx9data = (DX9Data *) h3ddata;
	// _hoops_ACGR _hoops_RH _hoops_A _hoops_SR _hoops_RRP _hoops_IS _hoops_ARP
	D3DXHANDLE t = m_pPSConstantTable->GetConstantByName(null, "DepthPeelingTexture");
	D3DXHANDLE b = m_pPSConstantTable->GetConstantByName(null, "DepthPeelingScaleAndBias");
	if (t && b)
	{
		// _hoops_IARP _hoops_IS _hoops_SISS
		const DWORD _hoops_PCI = m_pPSConstantTable->GetSamplerIndex(t);
		_hoops_SCCR(dx9data, _hoops_PCI, _hoops_CGIRH);

		// _hoops_HGI _hoops_PAH _hoops_SHH _hoops_IGI _hoops_IS _hoops_ARP/_hoops_IPPRA _hoops_RH _hoops_HH. _hoops_PGPR _hoops_GGCR _hoops_PIAP _hoops_RPP _hoops_IRS _hoops_HH _hoops_CSAP _hoops_ARSAR.
		if (_hoops_CGIRH)
		{
			_hoops_GRPA(dx9data, _hoops_PCI, H3DTEXF_POINT, H3DTEXF_NONE, H3DTADDRESS_CLAMP);

			// _hoops_GRSH _hoops_AHSC _hoops_HRGR _hoops_SCH?
			D3DSURFACE_DESC _hoops_IRSRA;
			_hoops_CGIRH->GetLevelDesc(0, &_hoops_IRSRA);

			// _hoops_HCGA _hoops_PPPR _hoops_SHI _hoops_IS _hoops_CI.
			D3DXVECTOR4 _hoops_GSAP(
				0.5f, 
				-0.5f, 
				0.5f + 0.5f / _hoops_IRSRA.Width, 
				0.5f + 0.5f / _hoops_IRSRA.Height
			);
			m_pPSConstantTable->SetVector(m_pDevice, b, &_hoops_GSAP);
		}
	}
}

void _hoops_RGHRH::_hoops_GGIR(bool _hoops_AIAAR)
{
	if (_hoops_PCC._hoops_RIHR())
		return;

	if (_hoops_PCC._hoops_HGC() || _hoops_PCC._hoops_CGC() ||
		_hoops_PCC._hoops_ISI() || _hoops_PCC._hoops_CSI())
	{
		D3DXHANDLE _hoops_SGIRH = m_pPSConstantTable->GetConstantByName(null, "FrontDiffuseTextureEnable");
		m_pPSConstantTable->SetInt(m_pDevice, _hoops_SGIRH, _hoops_AIAAR ? 0 : 1);
	}
}

bool _hoops_RGHRH::_hoops_HHIH() 
{
	HRESULT _hoops_IIRHP;
	_hoops_IIRHP = m_pDevice->SetVertexShader(_hoops_AGHRH);
	if (FAILED(_hoops_IIRHP))
		return false;
	_hoops_IIRHP = m_pDevice->SetPixelShader(_hoops_PGHRH);
	if (FAILED(_hoops_IIRHP))
		return false;

	_hoops_ICC = _hoops_SCC = _hoops_GSC = _hoops_RSC = 0;

	SET_MEMORY(_hoops_ISS->_hoops_SCRRR, sizeof(_hoops_ISS->_hoops_SCRRR), false);
	return true;
}


/*****************************************************************************
*****************************************************************************
							_hoops_SACA _hoops_GRIRH
*****************************************************************************
*****************************************************************************/

#if 0
/*
 * _hoops_PGAA
 */
local void set_target(
	IDirect3DDevice9	*device,
	int					index,
	IDirect3DTexture9	*texture)
{
	HRESULT _hoops_IIRHP;

	// _hoops_GAIAR _hoops_ISSGR _hoops_HII _hoops_HH
	IDirect3DSurface9 *surface = null;
	_hoops_IIRHP = texture->GetSurfaceLevel(0, &surface);
	if (SUCCEEDED(_hoops_IIRHP))
	{
		// _hoops_HCGA
		_hoops_IIRHP = device->SetRenderTarget(index, surface);
		
		// _hoops_CSH _hoops_RPIP _hoops_RRP _hoops_RH _hoops_CGRPR
		surface->Release();
	}
}

local void set_target(
	IDirect3DDevice9	*device,
	int					index,
	H3DTexture			*texture)
{
	set_target (device, index, ((_hoops_RRIRH *)texture)->_hoops_AIARH());
}


/*
 * _hoops_PGAA
 */
local void _hoops_ARIRH(
	IDirect3DDevice9	*device,
	H3DTexture			*texture)
{
	HRESULT _hoops_IIRHP;
	_hoops_RRIRH *_hoops_CGIRH = (_hoops_RRIRH *) texture;

	// _hoops_GAIAR _hoops_ISSGR _hoops_HII _hoops_HH
	IDirect3DSurface9 *surface = null;
	_hoops_IIRHP = _hoops_CGIRH->GetSurfaceLevel(0, &surface);
	if (SUCCEEDED(_hoops_IIRHP))
	{
		// _hoops_HCGA
		_hoops_IIRHP = device->SetDepthStencilSurface(surface);
		
		// _hoops_CSH _hoops_RPIP _hoops_RRP _hoops_RH _hoops_CGRPR
		surface->Release();
	}
}
#endif

/*
 * _hoops_PGAA
 */
local void _hoops_HGIP(
	IDirect3DDevice9	*device,
	IDirect3DSurface9	*src,
	IDirect3DTexture9	*_hoops_PCAP)
{
	HRESULT _hoops_IIRHP;

	// _hoops_GAIAR _hoops_ISSGR _hoops_HII _hoops_HH
	IDirect3DSurface9 *surface = null;
	_hoops_IIRHP = _hoops_PCAP->GetSurfaceLevel(0, &surface);
	if (SUCCEEDED(_hoops_IIRHP))
	{
		_hoops_IIRHP = device->StretchRect(src, null, surface, null, D3DTEXF_NONE);

		// _hoops_CSH _hoops_RPIP _hoops_RRP _hoops_RH _hoops_CGRPR
		surface->Release();
	}
}

/*
 * _hoops_PGAA
 */
local void _hoops_HGIP(
	IDirect3DDevice9	*device,
	IDirect3DTexture9	*src,
	IDirect3DSurface9	*_hoops_PCAP)
{
	HRESULT _hoops_IIRHP;

	// _hoops_GAIAR _hoops_ISSGR _hoops_HII _hoops_HH
	IDirect3DSurface9 *surface = null;
	_hoops_IIRHP = src->GetSurfaceLevel(0, &surface);
	if (SUCCEEDED(_hoops_IIRHP))
	{
		_hoops_IIRHP = device->StretchRect(surface, null, _hoops_PCAP, null, D3DTEXF_NONE);

		// _hoops_CSH _hoops_RPIP _hoops_RRP _hoops_RH _hoops_CGRPR
		surface->Release();
	}
}

/*
 * _hoops_PGAA
 */
local void _hoops_HGIP(
	IDirect3DDevice9	*device,
	IDirect3DSurface9	*src,
	H3DTexture			*_hoops_PCAP)
{
	_hoops_RIARH *_hoops_CGIRH = (_hoops_RIARH *) _hoops_PCAP;

	_hoops_HGIP(device, src, _hoops_CGIRH->_hoops_AIARH());
}

/*
 * _hoops_PGAA
 */
local void _hoops_HGIP(
	IDirect3DDevice9	*device,
	H3DTexture			*src,
	IDirect3DSurface9	*_hoops_PCAP)
{
	_hoops_RIARH *_hoops_CGIRH = (_hoops_RIARH *) src;

	_hoops_HGIP(device, _hoops_CGIRH->_hoops_AIARH(), _hoops_PCAP);
}


void _hoops_HGIP (
	   H3DData					*h3ddata,
	   H3DRenderTarget			*_hoops_SCSRR,
	   H3DRenderTarget			*_hoops_GSSRR,
	   H3DTEXTUREFILTERTYPE		filter,
	   bool						_hoops_RSSRR,
	   bool						_hoops_ASSRR)
{
	UNREFERENCED(_hoops_RSSRR);
	UNREFERENCED(_hoops_ASSRR);

	DX9Data *dx9data = (DX9Data *) h3ddata;
	bool _hoops_PRIRH = false;
	bool _hoops_HRIRH = false;

	// _hoops_GAIAR _hoops_ISSGR _hoops_HII _hoops_HH
	IDirect3DSurface9 *src = null;
	IDirect3DSurface9 *_hoops_HRGSP = null;
	if (_hoops_SCSRR->_hoops_CSARR()) {
		src = ((_hoops_RIARH *)_hoops_SCSRR)->GetSurfaceLevel(0);
		_hoops_PRIRH = true;
	}
	else {
		src = ((_hoops_HIARH *)_hoops_SCSRR)->_hoops_IIARH();
	}
	
	if (_hoops_GSSRR->_hoops_CSARR()) {
		_hoops_HRGSP = ((_hoops_RIARH *)_hoops_GSSRR)->GetSurfaceLevel(0);
		_hoops_HRIRH = true;
	}
	else {
		_hoops_HRGSP = ((_hoops_HIARH *)_hoops_GSSRR)->_hoops_IIARH();
	}

	
	dx9data->pDevice->StretchRect(src, null, _hoops_HRGSP, null, d3dtexturefilter(filter));

	// _hoops_CSH _hoops_RPIP _hoops_RRP _hoops_RH _hoops_CGRPR
	if (_hoops_PRIRH)
		src->Release();
	if (_hoops_HRIRH)
		_hoops_HRGSP->Release();
}


local void _hoops_IRIRH(DX9Data *dx9data)
{
	dx9data->_hoops_GSCR->_hoops_ASCRR(L"set_alpha");

	_hoops_HPHH (dx9data, false);
	_hoops_GPRP(dx9data, H3DMASK_A);

	//_hoops_ACAC _hoops_PCAC _hoops_HPPA _hoops_IPPA _hoops_HIHP _hoops_CGPR _hoops_HIHP _hoops_SHPH
	dx9data->_hoops_HCAC = _hoops_CCC;
	dx9data->_hoops_ICAC = _hoops_CCC;

	//_hoops_CCAC _hoops_SCAC
	H3DVertexFormat _hoops_PPCP(H3DVF_PT);
	H3DVertexBuffer _hoops_PAIH;
	H3DVertexBufferCache *_hoops_HACP;
	H3DShaderID id;
	H3DShader *_hoops_RSR;

	// _hoops_RASR
	
	//_hoops_ARSRR
	id._hoops_PHRAR(H3DID_DC, 0);
	_hoops_RSR = dx9data->_hoops_IP->Lookup (id); 
	if (!_hoops_RSR) {
		_hoops_RSR = NEW(_hoops_RGHRH)(id);
		if (!_hoops_RSR->Create(dx9data)) {
			return;
		}
		dx9data->_hoops_IP->Insert (id, _hoops_RSR); 
	}
	if (dx9data->_hoops_CSC->_hoops_AGSA != _hoops_RSR) {
		_hoops_RSR->_hoops_HHIH();
		dx9data->_hoops_CSC->_hoops_AGSA = _hoops_RSR;
	}

	// _hoops_GRSH _hoops_AHSC _hoops_HRGR _hoops_RH _hoops_ICIH?
	H3DViewport _hoops_PAPH = dx9data->_hoops_CSC->_hoops_CSAA;

	// _hoops_SIIR _hoops_HIHP _hoops_HII _hoops_ASPA
	D3DXMATRIX m;
	D3DXMatrixOrthoOffCenterRH(&m, _hoops_PAPH.X, _hoops_PAPH.X + _hoops_PAPH.Width, _hoops_PAPH.Y, _hoops_PAPH.Y + _hoops_PAPH.Height, _hoops_PAPH.MinZ, _hoops_PAPH.MaxZ);
	_hoops_RSR->_hoops_SHGA((float *) &m);

	_hoops_ISC const _hoops_CRIRH = { 255, 255, 255, 255 };
	_hoops_RSR->_hoops_GIHR(&_hoops_CRIRH);

	_hoops_PISP (dx9data, FALSE);
	_hoops_RPAP (dx9data, TRUE);
	_hoops_RHSA (dx9data, H3DCULL_NONE);
	ENSURE_DEPTH_MASK (dx9data, FALSE);
	_hoops_RPIH(dx9data, _hoops_PPCP, _hoops_HACP);
	
	// _hoops_PHIR _hoops_GGR _hoops_RSSA
	int width = dx9data->render_target->_hoops_IRRP;
	int height = dx9data->render_target->_hoops_CRRP;
	_hoops_HACP->Lock(4, &_hoops_PAIH);
	_hoops_PAIH._hoops_AHCP(0,0,0);
	_hoops_PAIH._hoops_CPPH();
	_hoops_PAIH._hoops_AHCP(width,0,0);
	_hoops_PAIH._hoops_CPPH();
	_hoops_PAIH._hoops_AHCP(0,height,0);
	_hoops_PAIH._hoops_CPPH();
	_hoops_PAIH._hoops_AHCP(width,height,0);
	_hoops_PAIH._hoops_CPPH();
	_hoops_HACP->Unlock();


	// _hoops_GISP _hoops_RH _hoops_ARRGR
	_hoops_HACP->_hoops_CHSA(dx9data, H3DPT_TRIANGLESTRIP, 2);

	// _hoops_SP _hoops_GH
	ENSURE_DEPTH_MASK (dx9data, TRUE);
	_hoops_GPRP(dx9data, H3DMASK_RGBA);
}

/*
 * _hoops_PGAA
 */
void _hoops_ICARH::_hoops_GHIP(

	H3DData				*h3ddata,
	H3DTexture			*texture,
	int					x, 
	int					y, 
	int					width, 
	int					height,
	float				_hoops_ACCRR,
	float				_hoops_ISPI,
	float				_hoops_PCCRR,
	float				_hoops_CSPI)
{
	DX9Data *dx9data = (DX9Data *) h3ddata;
	dx9data->_hoops_GSCR->_hoops_ASCRR(L"draw_textured_rectangle");

	_hoops_HPHH (dx9data, false);

	//_hoops_ACAC _hoops_PCAC _hoops_HPPA _hoops_IPPA _hoops_HIHP _hoops_CGPR _hoops_HIHP _hoops_SHPH
	dx9data->_hoops_HCAC = _hoops_CCC;
	dx9data->_hoops_ICAC = _hoops_CCC;

	//_hoops_CCAC _hoops_SCAC
	H3DVertexFormat _hoops_PPCP(H3DVF_PT_TEX);
	H3DVertexBuffer _hoops_PAIH;
	H3DVertexBufferCache *_hoops_HACP;
	H3DShaderID id;
	H3DShader *_hoops_RSR;

	// _hoops_RASR
	
	//_hoops_ARSRR
	id._hoops_AHRAR();
	_hoops_RSR = dx9data->_hoops_IP->Lookup (id); 
	if (!_hoops_RSR) {
		_hoops_RSR = NEW(_hoops_RGHRH)(id);
		if (!_hoops_RSR->Create(dx9data)) {
			return;
		}
		dx9data->_hoops_IP->Insert (id, _hoops_RSR); 
	}
	if (dx9data->_hoops_CSC->_hoops_AGSA != _hoops_RSR) {
		_hoops_RSR->_hoops_HHIH();
		dx9data->_hoops_CSC->_hoops_AGSA = _hoops_RSR;
	}
	_hoops_RSR->_hoops_GGIR();

	//_hoops_SRIRH
	// _hoops_GRSH _hoops_AHSC _hoops_HRGR _hoops_RH _hoops_ICIH?
	H3DViewport _hoops_PAPH = dx9data->_hoops_CSC->_hoops_CSAA;

	// _hoops_SIIR _hoops_HIHP _hoops_HII _hoops_ASPA
	D3DXMATRIX m;
	D3DXMatrixOrthoOffCenterRH(&m, _hoops_PAPH.X, _hoops_PAPH.X + _hoops_PAPH.Width, _hoops_PAPH.Y, _hoops_PAPH.Y + _hoops_PAPH.Height, _hoops_PAPH.MinZ, _hoops_PAPH.MaxZ);
	_hoops_RSR->_hoops_SHGA((float *) &m);

	_hoops_ISC const _hoops_CRIRH = { 255, 255, 255, 255 };
	_hoops_RSR->_hoops_GIHR(&_hoops_CRIRH);

	_hoops_PISP (dx9data, FALSE);
	_hoops_RPAP (dx9data, TRUE);
	_hoops_RHSA (dx9data, H3DCULL_NONE);
	ENSURE_DEPTH_MASK (dx9data, FALSE);
	_hoops_RPIH(dx9data, _hoops_PPCP, _hoops_HACP);
	
	// _hoops_PHIR _hoops_GGR _hoops_RSSA
	_hoops_HACP->Lock(4, &_hoops_PAIH);
	_hoops_PAIH._hoops_AHCP(x,y,0);
	_hoops_PAIH._hoops_IICP(_hoops_ACCRR,_hoops_CSPI,0);
	_hoops_PAIH._hoops_CPPH();
	_hoops_PAIH._hoops_AHCP(x+width,y,0);
	_hoops_PAIH._hoops_IICP(_hoops_PCCRR,_hoops_CSPI,0);
	_hoops_PAIH._hoops_CPPH();
	_hoops_PAIH._hoops_AHCP(x,y+height,0);
	_hoops_PAIH._hoops_IICP(_hoops_ACCRR,_hoops_ISPI,0);
	_hoops_PAIH._hoops_CPPH();
	_hoops_PAIH._hoops_AHCP(x+width,y+height,0);
	_hoops_PAIH._hoops_IICP(_hoops_PCCRR,_hoops_ISPI,0);
	_hoops_PAIH._hoops_CPPH();
	_hoops_HACP->Unlock();


	// _hoops_SIIR _hoops_PPSR _hoops_RHRP
	_hoops_SCCR(dx9data, 0, texture);
	_hoops_GRPA(dx9data, 0, H3DTEXF_POINT, H3DTEXF_NONE, H3DTADDRESS_CLAMP);

	// _hoops_GISP _hoops_RH _hoops_ARRGR
	_hoops_HACP->_hoops_CHSA(dx9data, H3DPT_TRIANGLESTRIP, 2);

	// _hoops_ICSS _hoops_HH - _hoops_SAPIA _hoops_PAR _hoops_SR _hoops_PAH'_hoops_RA _hoops_SRGS _hoops_IS _hoops_SCH _hoops_SPS _hoops_GHIR
	_hoops_ASRP(dx9data, 0);

	// _hoops_SP _hoops_GH
	ENSURE_DEPTH_MASK (dx9data, TRUE);
}


/*****************************************************************************
*****************************************************************************
							_hoops_SHCA _hoops_GRIRH
*****************************************************************************
*****************************************************************************/

#define _hoops_GAIRH(u,v,w) D3DCOLOR_COLORVALUE(((float)(u)+1)/2,((float)(v)+1)/2,((float)(w)+1)/2,0)


/*****************************************************************************
*****************************************************************************
							3D _hoops_GRIRH
*****************************************************************************
*****************************************************************************/
static const float _hoops_RAIRH[] = { 1,0,0,0,  0,1,0,0,  0,0,1,0,  0,0,0,1 };
static const float _hoops_AAIRH[] =  { 0,0,1,0,  0,1,0,0,  1,0,0,0,  0,0,0,1 };
static const float _hoops_PAIRH[] =  { 1,0,0,0,  0,-1,0,0,  0,0,1,0,  0,1,0,1 };
static const float _hoops_HAIRH[] = { -1,0,0,0,  0,1,0,0,  0,0,1,0,  0,0,0,1 };

bool _hoops_ICARH::_hoops_GSAC (
	Net_Rendition const & nr,
	_hoops_RCR alter *txr,
	int _hoops_GCI,
	H3DTexture *id,
	int _hoops_GRRA)
{
	DX9Data *dx9data = _hoops_CCARH;
	if (_hoops_GRRA >= H3D_MAX_TEXTURES)
		return false;

	/* _hoops_PHAA, _hoops_HSCR _hoops_RH _hoops_HH */
	_hoops_SCCR(dx9data, _hoops_GRRA, id);

	/* _hoops_CGP _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_IRAP _hoops_PCIA, _hoops_GA'_hoops_RA _hoops_SHAC _hoops_IS _hoops_ARP _hoops_AAIP (_hoops_PHRI _hoops_AIRRR _hoops_HGGC _hoops_RRP _hoops_HH _hoops_HCIA) */
	if ( id == null && (!txr || !BIT(txr->_hoops_SCR, _hoops_GSR)))
		return true;

	/*
	* _hoops_PHAA _hoops_RH _hoops_HRSAR _hoops_HH _hoops_RSGA _hoops_IPIH _hoops_ARP (_hoops_RPP _hoops_GII).
	* _hoops_HAPI _hoops_SR _hoops_ARP _hoops_GH _hoops_PCCP _hoops_SRGH _hoops_RSGA _hoops_PPR _hoops_GACC _hoops_IHAA _hoops_RH _hoops_HH.
	*/
	D3DXMATRIX dx_identity(_hoops_RAIRH);
	D3DXMATRIX dx_tfm(_hoops_PAIRH);
	D3DXMATRIX dx_t3dfm(_hoops_AAIRH);
	D3DXMATRIX dx_efm(_hoops_HAIRH);
	D3DXMATRIX *dx_tm = null;

	if (txr) {
		if (BIT(txr->_hoops_SCR, _hoops_GSR))
			dx_tm = &dx_identity;
		else if (BIT(txr->flags, _hoops_CSGH))
			dx_tm = &dx_t3dfm;
		else if (_hoops_GCI == _hoops_HSGH)
			dx_tm = &dx_efm;
		else
			dx_tm = &dx_tfm;
		_hoops_GAAIR alter *tm = (_hoops_GAAIR alter *) nr->_hoops_IRR->_hoops_APGH;
		if (txr->_hoops_GAGH != null) {
			/* _hoops_PS _hoops_HS _hoops_IRS _hoops_PIAH _hoops_HH-_hoops_IIHA _hoops_RSGA */
			D3DXMATRIX _hoops_IAIRH (&txr->_hoops_GAGH->matrix._hoops_APRA->data.elements[0][0]);
			D3DXMatrixMultiply (dx_tm, &_hoops_IAIRH, dx_tm);
		}
		if (!BIT(txr->flags, _hoops_IPGH) &&
			ANYBIT (tm->matrix._hoops_RAGR, _hoops_CICH)) {
			/* _hoops_PS _hoops_HS _hoops_RGAR _hoops_IRS _hoops_CAGH-_hoops_IIHA _hoops_RSGA */
			if (tm->matrix._hoops_APRA == null)
				HI_Validate_Matrix_Adjoint ((_hoops_HRPA *)&tm->matrix);

			D3DXMATRIX _hoops_CAIRH (&tm->matrix._hoops_APRA->data.elements[0][0]);
			D3DXMatrixMultiply (dx_tm, &_hoops_CAIRH, dx_tm);
		}
		if (!EQUAL_MEMORY(dx_tm, 16*sizeof(float), dx9data->_hoops_PRRA[_hoops_GRRA])) {
			dx9data->_hoops_RRRA[_hoops_GRRA] = true;
			COPY_MEMORY(dx_tm, 16*sizeof(float), dx9data->_hoops_PRRA[_hoops_GRRA]);
		}
	}
	else {
		ASSERT (_hoops_GCI != _hoops_HSGH);
		dx_tm = &dx_tfm;
		if (!EQUAL_MEMORY(dx_tm, 16*sizeof(float), dx9data->_hoops_PRRA[_hoops_GRRA])) {
			dx9data->_hoops_RRRA[_hoops_GRRA] = true;
			COPY_MEMORY(dx_tm, 16*sizeof(float), dx9data->_hoops_PRRA[_hoops_GRRA]);
		}
	}


	/* _hoops_CGP _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_IRAP _hoops_PCIA, _hoops_GA'_hoops_RA _hoops_SHAC _hoops_IS _hoops_ARP _hoops_AAIP */
	if ( id == null )
		return true;

	/* _hoops_AGGA, _hoops_ARP _hoops_GH _hoops_RH _hoops_HH _hoops_RHRP (_hoops_RPP _hoops_GII) */
	if (_hoops_GCI == _hoops_HSGH) {
		ENSURE_TEXTURE_WRAP_S (dx9data, _hoops_GRRA, D3DTADDRESS_WRAP);
		_hoops_SAIRH (dx9data, _hoops_GRRA, D3DTADDRESS_WRAP);
		_hoops_GPIRH (dx9data, _hoops_GRRA, D3DTEXF_LINEAR);
		_hoops_RPIRH (dx9data, _hoops_GRRA, D3DTEXF_LINEAR);
	}
	else if (_hoops_GCI == _hoops_GCHGR) {
		if (!BIT (nr->_hoops_IRR->_hoops_CSA,_hoops_HIRC)) {
			_hoops_GPIRH (dx9data, _hoops_GRRA, D3DTEXF_POINT);
			_hoops_RPIRH (dx9data, _hoops_GRRA, D3DTEXF_POINT);
		}
		else {
			_hoops_GPIRH (dx9data, _hoops_GRRA, D3DTEXF_LINEAR);
			_hoops_RPIRH (dx9data, _hoops_GRRA, D3DTEXF_LINEAR);
		}
		// _hoops_CSSGR _hoops_ACAR _hoops_RRP _hoops_IS _hoops_ARGAR _hoops_CGPR _hoops_RH _hoops_PSPI _hoops_PHHR _hoops_GGSR _hoops_IIGR _hoops_PRCH.
		ENSURE_TEXTURE_WRAP_S (dx9data, _hoops_GRRA, D3DTADDRESS_WRAP);
	}
	else if (_hoops_GCI == _hoops_PCRS) {
		if (!BIT (nr->_hoops_IRR->_hoops_CSA,_hoops_SSRC)) {
			_hoops_GPIRH (dx9data, _hoops_GRRA, D3DTEXF_POINT);
			_hoops_RPIRH (dx9data, _hoops_GRRA, D3DTEXF_POINT);
		}
		else {
			_hoops_GPIRH (dx9data, _hoops_GRRA, D3DTEXF_LINEAR);
			_hoops_RPIRH (dx9data, _hoops_GRRA, D3DTEXF_LINEAR);
		}
		// _hoops_CSSGR _hoops_ACAR _hoops_RRP _hoops_IS _hoops_ARGAR _hoops_CGPR _hoops_RH _hoops_PSPI _hoops_PHHR _hoops_GGSR _hoops_IIGR _hoops_PRCH.
		ENSURE_TEXTURE_WRAP_S (dx9data, _hoops_GRRA, D3DTADDRESS_WRAP);
	}
	else if (_hoops_GCI == _hoops_RSAC || _hoops_GCI == _hoops_GIPS) {
		ENSURE_TEXTURE_WRAP_S (dx9data, _hoops_GRRA, D3DTADDRESS_WRAP);
		_hoops_SAIRH (dx9data, _hoops_GRRA, D3DTADDRESS_WRAP);
		_hoops_GPIRH (dx9data, _hoops_GRRA, D3DTEXF_POINT);
		_hoops_RPIRH (dx9data, _hoops_GRRA, D3DTEXF_POINT);
	}
	else if (_hoops_GCI == _hoops_SPHC) {
		ENSURE_TEXTURE_WRAP_S (dx9data, _hoops_GRRA, D3DTADDRESS_WRAP);
		_hoops_SAIRH (dx9data, _hoops_GRRA, D3DTADDRESS_WRAP);
		_hoops_GPIRH (dx9data, _hoops_GRRA, D3DTEXF_LINEAR);
		_hoops_RPIRH (dx9data, _hoops_GRRA, D3DTEXF_LINEAR);
	}
	else if (_hoops_GCI == _hoops_RCHGR) {
		ENSURE_TEXTURE_WRAP_S (dx9data, _hoops_GRRA, D3DTADDRESS_MIRROR);
		_hoops_SAIRH (dx9data, _hoops_GRRA, D3DTADDRESS_MIRROR);
		_hoops_GPIRH (dx9data, _hoops_GRRA, D3DTEXF_POINT);
		_hoops_RPIRH (dx9data, _hoops_GRRA, D3DTEXF_POINT);
		_hoops_APIRH (dx9data, _hoops_GRRA, D3DTEXF_POINT);
	}
	else if (txr) {
		switch (txr->_hoops_CGA) {
			case _hoops_ASGRP:
				ENSURE_TEXTURE_WRAP_S (dx9data, _hoops_GRRA, D3DTADDRESS_WRAP);
				_hoops_SAIRH (dx9data, _hoops_GRRA, D3DTADDRESS_WRAP);
				break;
			case _hoops_ASCC:
				ENSURE_TEXTURE_WRAP_S (dx9data, _hoops_GRRA, D3DTADDRESS_CLAMP);
				_hoops_SAIRH (dx9data, _hoops_GRRA, D3DTADDRESS_CLAMP);
				break;
			case _hoops_PSGRP:
				ENSURE_TEXTURE_WRAP_S (dx9data, _hoops_GRRA, D3DTADDRESS_MIRROR);
				_hoops_SAIRH (dx9data, _hoops_GRRA, D3DTADDRESS_MIRROR);
				break;
		}

		/*_hoops_RRPS _hoops_IS _hoops_PAGGR _hoops_PPIRH _hoops_HSHIA 4-94 _hoops_SR _hoops_CGH _hoops_IIP _hoops_PPSI _hoops_PGGA _hoops_IIGR _hoops_PIGGH*/
		if (txr->_hoops_PSCC == _hoops_HSCC) {
			_hoops_RPIRH (dx9data, _hoops_GRRA, D3DTEXF_POINT);
			_hoops_GPIRH (dx9data, _hoops_GRRA, D3DTEXF_POINT);
		}
		else {
			_hoops_RPIRH (dx9data, _hoops_GRRA, D3DTEXF_LINEAR);
			_hoops_GPIRH (dx9data, _hoops_GRRA, D3DTEXF_LINEAR);
		}
		if (txr->_hoops_RARH == _hoops_AARH) {
			_hoops_APIRH (dx9data, _hoops_GRRA, D3DTEXF_POINT);
		}
		else if (txr->_hoops_RARH == _hoops_PARH) {
			_hoops_GPIRH (dx9data, _hoops_GRRA, D3DTEXF_ANISOTROPIC);
			_hoops_APIRH (dx9data, _hoops_GRRA, D3DTEXF_LINEAR);
		}
		else {
			_hoops_APIRH (dx9data, _hoops_GRRA, D3DTEXF_NONE);
		}
	}

	return true;
}


bool _hoops_ICARH::CreateTexture(
	unsigned int width, 
	unsigned int height, 
	unsigned int _hoops_ICRH,
	unsigned int _hoops_GCI,
	H3DFORMAT format,
	H3DTexture **id)
{
	_hoops_RIARH *_hoops_CGIRH;
	_hoops_CGIRH = NEW(_hoops_RIARH)(_hoops_CCARH, width, height, _hoops_ICRH, _hoops_GCI, format);
	if (FAILED(_hoops_CGIRH->_hoops_IIRHP))
	{
		delete _hoops_CGIRH;
		return false;
	}
	*id = (H3DTexture *)_hoops_CGIRH;
	return true;
}


bool _hoops_ICARH::CreateCubeTexture(
	unsigned int size, 
	unsigned int _hoops_ICRH,
	unsigned int _hoops_GCI,
	H3DCubeTexture **id)
{
	_hoops_HPIRH *_hoops_CGIRH;
	_hoops_CGIRH = NEW(_hoops_HPIRH)(_hoops_CCARH, size, _hoops_ICRH, _hoops_GCI);
	if (FAILED(_hoops_CGIRH->_hoops_IIRHP))
	{
		delete _hoops_CGIRH;
		return false;
	}
	*id = _hoops_CGIRH;
	return true;
}


bool _hoops_ICARH::_hoops_PSRH(
	unsigned int w, 
	unsigned int h, 
	unsigned int depth, 
	unsigned int _hoops_ICRH,
	unsigned int _hoops_GCI,
	H3DFORMAT format, 
	H3DTexture3D **id)
{
	_hoops_IPIRH *_hoops_CGIRH;
	_hoops_CGIRH = NEW(_hoops_IPIRH)(_hoops_CCARH, w, h, depth, _hoops_ICRH, _hoops_GCI, format);
	if (FAILED(_hoops_CGIRH->_hoops_IIRHP))
	{
		delete _hoops_CGIRH;
		return false;
	}
	*id = _hoops_CGIRH;
	return true;
}


bool _hoops_ICARH::CreateRenderTarget(
	unsigned int width, 
	unsigned int height, 
	unsigned int _hoops_GCI,
	H3DFORMAT _hoops_GCH,
	unsigned int _hoops_ISARR,
	H3DRenderTarget **id)
{
	_hoops_HIARH *_hoops_CGIRH;
	_hoops_CGIRH = NEW(_hoops_HIARH)(_hoops_CCARH, width, height, _hoops_GCI, _hoops_GCH, _hoops_ISARR);
	if (FAILED(_hoops_CGIRH->_hoops_IIRHP))
	{
		delete _hoops_CGIRH;
		return false;
	}
	*id = _hoops_CGIRH;
	return true;
}



/*****************************************************************************
*****************************************************************************
							_hoops_CPIRH _hoops_SPIRH
*****************************************************************************
*****************************************************************************/

/*
* _hoops_PGAA
*/
local void check_events (DX9Data alter * dx9data)
{
	MSG _hoops_SSACR;

	dx9data->_hoops_IRRRR = false;

	while (PeekMessage (&_hoops_SSACR, dx9data->hWND, 0, 0, PM_NOREMOVE) &&
		GetMessage (&_hoops_SSACR, dx9data->hWND, 0, 0)) {
		TranslateMessage (&_hoops_SSACR);
		DispatchMessage (&_hoops_SSACR);
	}
}


/*
* _hoops_PGAA
*/
local void consume_key (
		DX9Data alter * dx9data,
		UINT word_parameter,
		LONG _hoops_GHIRH)
{
	int			key;
	BYTE		_hoops_RHIRH[256];
	int			status = 0;

	/* _hoops_ASC _hoops_CPPC _hoops_CHR _hoops_AHIRH _hoops_GPP _hoops_RH _hoops_PHIRH _hoops_CPPC */

#define B_SHIFT			0x00000100
#define B_CONTROL		0x00000200
#define B_NUM_LOCK		0x00000400
#define B_ALT			0x00000800

	/* _hoops_ASC _hoops_CHR _hoops_HSGS _hoops_IS _hoops_RH _hoops_AAGIP _hoops_PPR _hoops_ACGP _hoops_HHIRH */

#define B_CAPS_LOCK				0x00001000
#define B_SCROLL_LOCK			0x00002000
#define B_LEFT_SHIFT			0x00004000
#define B_RIGB_SHIFT			0x00008000
#define B_RIGB_CONTROL			0x00010000
#define B_LEFT_CONTROL			0x00020000
#define B_RIGB_ALT				0x00040000
#define B_LEFT_ALT				0x00080000


	GetKeyboardState (_hoops_RHIRH);

	if ((_hoops_RHIRH[VK_SHIFT] & 0x80) != 0)
		status |= B_SHIFT;
	if ((_hoops_RHIRH[VK_CONTROL] & 0x80) != 0)
		status |= B_CONTROL;
	if ((_hoops_RHIRH[VK_NUMLOCK] & 0x01) != 0)
		status |= B_NUM_LOCK;
	if ((_hoops_RHIRH[VK_MENU] & 0x80) != 0)
		status |= B_ALT;
	if ((_hoops_RHIRH[VK_CAPITAL] & 0x01) != 0)
		status |= B_CAPS_LOCK;
	if ((_hoops_RHIRH[VK_SCROLL] & 0x01) != 0)
		status |= B_SCROLL_LOCK;
	if ((_hoops_RHIRH[VK_LSHIFT] & 0x80) != 0)
		status |= B_LEFT_SHIFT;
	if ((_hoops_RHIRH[VK_RSHIFT] & 0x80) != 0)
		status |= B_RIGB_SHIFT;
	if ((_hoops_RHIRH[VK_LCONTROL] & 0x80) != 0)
		status |= B_LEFT_CONTROL;
	if ((_hoops_RHIRH[VK_RCONTROL] & 0x80) != 0)
		status |= B_RIGB_CONTROL;
	if ((_hoops_RHIRH[VK_LMENU] & 0x80) != 0)
		status |= B_LEFT_ALT;
	if ((_hoops_RHIRH[VK_RMENU] & 0x80) != 0)
		status |= B_RIGB_ALT;

	/* _hoops_SCH'_hoops_GRI _hoops_PCCP _hoops_ICIGP _hoops_SIC _hoops_IIGR _hoops_HHH _hoops_CGGAR */
	switch (word_parameter) {
		case VK_NUMPAD0:
		case VK_NUMPAD1:
		case VK_NUMPAD2:
		case VK_NUMPAD3:
		case VK_NUMPAD4:
		case VK_NUMPAD5:
		case VK_NUMPAD6:
		case VK_NUMPAD7:
		case VK_NUMPAD8:
		case VK_NUMPAD9: {
			if (status & B_NUM_LOCK)
				key = '0' + word_parameter - VK_NUMPAD0;
			else
				key = FIRST_KEYPAD_KEY + word_parameter - VK_NUMPAD0;
		}	break;

		case VK_INSERT: {
			key = FIRST_KEYPAD_KEY + 0;
		}	break;

		case VK_END: {
			key = FIRST_KEYPAD_KEY + 1;
		}	break;

		case VK_HOME: {
			key = FIRST_KEYPAD_KEY + 7;
		}	break;

		case VK_PRIOR: {
			key = FIRST_KEYPAD_KEY + 9;
		}   break;

		case VK_NEXT: {
			key = FIRST_KEYPAD_KEY + 3;
		}	break;

		case VK_F1:
		case VK_F2:
		case VK_F3:
		case VK_F4:
		case VK_F5:
		case VK_F6:
		case VK_F7:
		case VK_F8:
		case VK_F9:
		case VK_F10:
		case VK_F11:
		case VK_F12:
		case VK_F13:
		case VK_F14:
		case VK_F15:
		case VK_F16: {
			key = FIRST_FUNCTION_KEY + word_parameter - VK_F1 + 1;
		}	break;

		case VK_TAB: {
			key = 9;
		}	break;

		case VK_RETURN: {
			key = 13;
		}	break;

		case VK_ESCAPE: {
			key = 27;
		}	break;

		case VK_SPACE: {
			key = 32;
		}   break;

		case VK_DELETE: {
			key = RUBOUT_KEY;
		}	break;

		case VK_UP: {
			key = UP_ARROW_KEY;
		}	break;

		case VK_DOWN: {
			key = DOWN_ARROW_KEY;
		}	break;

		case VK_LEFT: {
			key = LEFT_ARROW_KEY;
		}	  break;

		case VK_RIGHT: {
			key = RIGHT_ARROW_KEY;
		}   break;

		default: {
			UINT	_hoops_IHIRH;
			WORD	_hoops_CHIRH;
			char	_hoops_SHIRH[256];

			_hoops_IHIRH = (WORD) LOBYTE (HIWORD (_hoops_GHIRH));
			GetKeyboardState ((LPBYTE)_hoops_SHIRH);

			if (ToAsciiEx (word_parameter, _hoops_IHIRH, (PBYTE)_hoops_SHIRH,
				(LPWORD)&_hoops_CHIRH, (UINT)0,GetKeyboardLayout(0)) == 1)
				key = (unsigned int) (0xFFL & _hoops_CHIRH);
			else
				key = 0;
		}	_hoops_HHHI;
	}

	if (key != 0)
		HI_Queue_Keyboard_Event ((_hoops_GGAGR alter *)dx9data->dc->_hoops_GHRI, key, status);
}




/*
* _hoops_PGAA
*/
local void
consume_mouse (DX9Data alter * dx9data,
			   UINT event, UINT wParam, LONG lParam)
{

	switch (event) {
		case WM_RBUTTONDOWN:	dx9data->_hoops_HRRRR |= _hoops_ARRRR;		break;
		case WM_MBUTTONDOWN:	dx9data->_hoops_HRRRR |= _hoops_PRRRR;		break;
		case WM_LBUTTONDOWN:	dx9data->_hoops_HRRRR |= _hoops_RRRRR;		break;

		case WM_RBUTTONUP:		dx9data->_hoops_HRRRR &= ~_hoops_ARRRR;		break;
		case WM_MBUTTONUP:		dx9data->_hoops_HRRRR &= ~_hoops_PRRRR;	break;
		case WM_LBUTTONUP:		dx9data->_hoops_HRRRR &= ~_hoops_RRRRR;		break;
	}

	dx9data->_hoops_SCGRR = LOWORD (lParam);
	dx9data->mouse_y = dx9data->yfudge - HIWORD (lParam);

	HD_Queue_Pixel_Location_Event (dx9data->dc, dx9data->_hoops_HRRRR,
		dx9data->_hoops_SCGRR, dx9data->mouse_y);
	dx9data->_hoops_IRRRR = true;

	UNREFERENCED(wParam);
}


/*
* _hoops_SRAC
*/
local bool
_hoops_HSCSP (Display_Context const * dc,
				  int alter * button,
				  int alter * x, int alter * y)
{
	DX9Data alter *dx9data = DX9D (dc);

	if (dx9data != null) {
		check_events (dx9data);
		/* _hoops_HGI _hoops_SPS _hoops_III _hoops_HRGR _hoops_GIIRH _hoops_HAHH _hoops_IS _hoops_SGHIP _hoops_RH _hoops_CRS */
		dx9data = DX9D (dc);
		/*
		* _hoops_HGI _hoops_API _hoops_PIHA _hoops_SHR _hoops_RHRRH _hoops_IRS _hoops_GISAP "_hoops_PIAP",
		* _hoops_HIS _hoops_RPP _hoops_RIIRH _hoops_SSAS _hoops_HAR _hoops_RHRRH _hoops_PCCP _hoops_CPGGR _hoops_AIH
		* _hoops_AIIRH, _hoops_SR _hoops_PIHA _hoops_RHRRH _hoops_SPR _hoops_ARI.
		* _hoops_PS _hoops_GRS _hoops_SAHR _hoops_ASAR-_hoops_RHRRH _hoops_RH _hoops_CGHI _hoops_GISAP _hoops_PIAP _hoops_SGS
		* _hoops_SR _hoops_HARRA.
		*/
		if (dx9data == null || dx9data->_hoops_IRRRR)
			return false;
		else {
			*button = dx9data->_hoops_HRRRR;
			*x = dx9data->_hoops_SCGRR;
			*y = dx9data->mouse_y;
			return true;
		}
	}

	return false;
}


/*
* _hoops_SRAC
*/
local bool
_hoops_ISCSP (Display_Context const * dc,
				  int alter * button, int alter * status)
{
	DX9Data alter *dx9data = DX9D (dc);

	if (dx9data != null) {
		check_events (dx9data);
		/* _hoops_HGI _hoops_SPS _hoops_III _hoops_HRGR _hoops_GIIRH _hoops_HAHH _hoops_IS _hoops_SGHIP _hoops_RH _hoops_CRS */
		dx9data = DX9D (dc);

		/*
		* _hoops_RIIRH _hoops_GRS _hoops_SHR _hoops_HS _hoops_PIIRH _hoops_GII _hoops_HIIRH
		* _hoops_IS _hoops_IRISR _hoops_AIH _hoops_IIIRH.  _hoops_CPGP _hoops_IRISR _hoops_ASSP'_hoops_RA
		* _hoops_RRP _hoops_IS _hoops_ACPA _hoops_RH "_hoops_PIAP" _hoops_IIGR _hoops_RH _hoops_CIIRH, _hoops_RGR _hoops_API
		* _hoops_PAH _hoops_IGIRR _hoops_ASRC _hoops_RCPP.
		*/
	}

	UNREFERENCED(status);
	UNREFERENCED(button);

	return false;
}

/*****************************************************************************
*****************************************************************************
						_hoops_HGGSP _hoops_SIIRH'_hoops_GRI (_hoops_PPR _hoops_HICRR _hoops_SICAR)
*****************************************************************************
*****************************************************************************/

//_hoops_GCIRH
local void free_outer_window (Display_Context const * dc);
local void stop_device (Display_Context alter * dc);
local void invalidate_cache (D3D_System_Data *d3d_sd);

#ifdef HDX9_MANAGED_POOL
local bool _hoops_RCIRH(_hoops_AGCI alter *_hoops_AGAGR, void *_hoops_HHCAP)
{
	H3D_Display_List *ptr = (H3D_Display_List *)_hoops_AGAGR;

	if (ptr->type == H3D_DL_SHADOW_MAP ||
		(ptr->type == H3D_DL_TEXTURE && ptr->item.texture._hoops_IAGGR))
		return true;
	
	UNREFERENCED (_hoops_HHCAP);
	return false;
}
#endif

HRESULT _hoops_ACIRH(Display_Context alter * dc)
{
	DX9Data alter *dx9data = DX9D (dc);
	H3D_TRACE(dx9data, "invalidate_device_objects");

	// _hoops_HHSA _hoops_IAGIP _hoops_PPR _hoops_HHCI _hoops_IHCI _hoops_PSCA _hoops_IS _hoops_SHH _hoops_PCIRH
	dc->flags |= _hoops_SHIIP;

	H_SAFE_RELEASE(dx9data->_hoops_RHH.msaa_target);

	// _hoops_PPGGR _hoops_HCIRH
	_hoops_HP(dx9data->_hoops_II._hoops_CRPP);

	// _hoops_SCAGR _hoops_IIGR _hoops_ISCP _hoops_GRH _hoops_CSCR _hoops_PGHH
	if ( dx9data->_hoops_GSCR )
		dx9data->_hoops_GSCR->_hoops_ISPGR(const_cast<Display_Context alter*>(dx9data->dc), dx9data->_hoops_ICIRH, dx9data->_hoops_CCIRH);
	dx9data->_hoops_ICIRH = null;
	dx9data->_hoops_CCIRH = null;

	// _hoops_PPGGR _hoops_AHCS _hoops_PPR _hoops_CSCR _hoops_PGHH.
	_hoops_RSARH(*dx9data);
	dx9data->_hoops_PSARH = null;
	dx9data->_hoops_HSARH = null;

	// _hoops_AHHH _hoops_RHAA _hoops_GRS _hoops_CASI _hoops_AGCR _hoops_GH, _hoops_SR _hoops_SAHR _hoops_RRP _hoops_IS _hoops_AHHR _hoops_RH _hoops_CICRR
	dx9data->_hoops_HHRRR._hoops_AHRRR = NULL;
	dx9data->_hoops_HHRRR._hoops_RHRRR = NULL;

	dx9data->_hoops_GSCR->_hoops_SGSRR(dc);
	_hoops_HP(dx9data->_hoops_GSCR);

	// _hoops_SP _hoops_GH _hoops_AIRI _hoops_CPCI _hoops_SGS _hoops_CHR _hoops_PSPP _hoops_GPP _hoops_RH _hoops_SHIR _hoops_ICGAR

#ifdef HDX9_MANAGED_POOL
	HD_Purge_Display_Lists(dc->_hoops_GHRI, _hoops_RCIRH, null); 
#else
	HD_Purge_Display_Lists(dc->_hoops_GHRI, null, null); 
#endif

	((Display_Context alter *) dx9data->dc)->_hoops_GRAGR = true;
	_hoops_SSRGR(dc);
	((Display_Context alter *) dx9data->dc)->_hoops_GRAGR = false;

	// _hoops_PPGGR _hoops_RH _hoops_RHAA _hoops_SCIRH'_hoops_GRI _hoops_GSIRH _hoops_SHCS
	if (dx9data->post) {
		if (dx9data->_hoops_II.depth_texture )
			dx9data->post->_hoops_HAAP( &dx9data->_hoops_II.depth_texture );
		dx9data->post->_hoops_RPCRR();
	}

	return S_OK;
}

//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_RSIRH()
// _hoops_RHSSA: _hoops_ASIRH _hoops_CCA _hoops_PSIRH()
//		 _hoops_IPCP _hoops_SISS _hoops_HICP, _hoops_HIH _hoops_GHCA _hoops_HS _hoops_SAHR _hoops_RPII _hoops_IIPI().	 _hoops_ASPP _hoops_GGR
//		 _hoops_GSIRH _hoops_PPR _hoops_GII _hoops_RII _hoops_SISS _hoops_PIAP _hoops_SGS _hoops_HSIRH _hoops_RHSP
//		 _hoops_GCAC _hoops_CGH _hoops_SHH _hoops_ARP _hoops_ARI.	_hoops_PCSS _hoops_AAIP, _hoops_HCIA, _hoops_AI,
//		 _hoops_AHI., _hoops_SGS _hoops_GA'_hoops_RA _hoops_AGRP _hoops_RHSP _hoops_GCAC _hoops_PAH _hoops_SHH _hoops_ARP _hoops_ARR _hoops_ARI _hoops_IS
//		 _hoops_SRCH _hoops_CPCIP _hoops_PIAP _hoops_RGSR _hoops_RHSP _hoops_PCSS() _hoops_PAR _hoops_ISIRH().
//-----------------------------------------------------------------------------
HRESULT _hoops_CSIRH (Display_Context alter * dc)
{
	// _hoops_SIIR _hoops_CPS _hoops_ISSC
	_hoops_CSPRH(dc);
	return S_OK;
}


HRESULT _hoops_SSIRH (Display_Context alter * dc)
{
	DX9Data alter *dx9data = DX9D (dc);
	H3D_TRACE(dx9data, "reset_3d_environment");

	// _hoops_IIPI _hoops_RH _hoops_SISS
	D3D_System_Data *d3d_sd = (D3D_System_Data *) _hoops_ARPRH()->d3d_shared_data;
	NEW(DX9ResetDeviceTask)(d3d_sd);
	HM_WAIT_SEMAPHORE(d3d_sd->_hoops_HISSA);

	return S_OK;
}

/*
 * _hoops_PGAA
 */
void _hoops_IHARR(Display_Context alter * dc)
{
	DX9Data alter *dx9data = DX9D (dc);
	H3D_TRACE(dx9data, "handle_size_change");

	// _hoops_CGP _hoops_SR _hoops_PAH'_hoops_RA _hoops_RGHH _hoops_IRS _hoops_PCCS _hoops_RPHR _hoops_HA, _hoops_ARP _hoops_RH _hoops_RIP _hoops_PPR _hoops_SAS
	if ( dx9data->_hoops_HGRRR ) {
		dx9data->_hoops_CGRRR = true;
		return;
	}

	// _hoops_HRHI _hoops_RPPS _hoops_HRPRA
	//_hoops_GGCRH(_hoops_RGCRH, &_hoops_AGCRH);
	RECT _hoops_PGCRH;
	CopyRect(&_hoops_PGCRH, (RECT *) &dx9data->_hoops_IIGRR);
	GetClientRect (dx9data->hWND, (RECT *) &dx9data->_hoops_IIGRR);

	if (_hoops_PGCRH.right - _hoops_PGCRH.left !=
		dx9data->_hoops_IIGRR.right - dx9data->_hoops_IIGRR.left ||
		_hoops_PGCRH.bottom - _hoops_PGCRH.top !=
		dx9data->_hoops_IIGRR.bottom - dx9data->_hoops_IIGRR.top) {
		// _hoops_RAIGR _hoops_CCAH _hoops_RPPS _hoops_IGIR _hoops_GRS _hoops_HGAP _hoops_IRS _hoops_CCAH _hoops_AISH
		// _hoops_IGIR, _hoops_HIS _hoops_RH 3D _hoops_HCCGR _hoops_PIHA _hoops_SHH _hoops_HGAS _hoops_HGCRH.

		dx9data->_hoops_HCARH.BackBufferWidth  = dx9data->_hoops_IIGRR.right - dx9data->_hoops_IIGRR.left;
		dx9data->_hoops_HCARH.BackBufferHeight = dx9data->_hoops_IIGRR.bottom - dx9data->_hoops_IIGRR.top;

		if (dx9data->_hoops_HCARH.BackBufferWidth == 0)
			dx9data->_hoops_HCARH.BackBufferWidth = 1;
		if (dx9data->_hoops_HCARH.BackBufferHeight == 0)
			dx9data->_hoops_HCARH.BackBufferHeight = 1;

		if (dx9data->pDevice != null) {
			H_SAFE_RELEASE(dx9data->_hoops_IGCRH);
			dx9data->pDevice->CreateAdditionalSwapChain(&dx9data->_hoops_HCARH, &dx9data->_hoops_IGCRH);
			dx9data->_hoops_CRAP = _hoops_SGGRR;		// _hoops_HHSA _hoops_CGCRH _hoops_IS _hoops_PSASA _hoops_ASCS
		}
	}
	return;
}

/*
 * _hoops_PGAA
 */
local void
_hoops_SGCRH (DX9Data alter *dx9data,
			 HWND _hoops_GRCRH,
			 bool _hoops_RRCRH,
			 bool _hoops_ARCRH)
{
	PAINTSTRUCT ps;
	HDC hDC;
	RECT _hoops_PRCRH;

	UNREFERENCED (_hoops_ARCRH);

	/* _hoops_PCR _hoops_CCA _hoops_PSHR _hoops_API _hoops_GGR _hoops_HRCRH _hoops_SCHGR */

	if (dx9data->pending_resize) {
		dx9data->pending_resize = false;
		if (!IsIconic (_hoops_GRCRH)
			&& (_hoops_RRCRH || IsWindowVisible (_hoops_GRCRH))) {
			//_hoops_IRCRH (_hoops_CRCRH->_hoops_SRCRH, (_hoops_GACRH *) &_hoops_CRCRH->_hoops_RACRH);
			HD_Force_Refresh (dx9data->dc);
		}
	}

	hDC = BeginPaint (dx9data->hWND, (LPPAINTSTRUCT) & ps);
	InvalidateRect (dx9data->hWND, (LPRECT) &ps.rcPaint, 0);
	EndPaint (dx9data->hWND, &ps);

	CopyRect (&_hoops_PRCRH, &ps.rcPaint);
	if (ps.rcPaint.bottom + ps.rcPaint.top + ps.rcPaint.right +
		ps.rcPaint.left != 0) {
		RECT rect;
		GetClientRect(dx9data->hWND, &rect);
		HD_Force_Partial_Refresh (dx9data->dc,
			ps.rcPaint.left,
			ps.rcPaint.right - 1,
			rect.bottom - ps.rcPaint.bottom,
			rect.bottom - ps.rcPaint.top);
	}
}



/* _hoops_GRAA-_hoops_SGH _hoops_RPPS _hoops_RCC _hoops_RPPS _hoops_AACRH */
local LRESULT APIENTRY
_hoops_PACRH (HWND _hoops_GRCRH,
				 UINT message,
				 WPARAM wParam,
				 LPARAM lParam)
{
	Display_Context alter *dc;

	if ((dc = HD_Find_DC_From_WID ((POINTER_SIZED_INT) _hoops_GRCRH)) != null) {
		DX9Data alter *dx9data;

		dx9data = DX9D (dc);

		switch (message) {
			case WM_CLOSE: {
			/*
			* _hoops_HPIRA _hoops_RPISR _hoops_GRS _hoops_ISPR _hoops_RGR _hoops_RIP _hoops_PPR
			* _hoops_PCHIA _hoops_RHPP - _hoops_ISCCP _hoops_SCH _hoops_ARI _hoops_CHH _hoops_HS _hoops_RPII _hoops_HACRH _hoops_IACRH
				*/
				char event_string[255];

				
				if (dc->options._hoops_GASSP && !dc->options._hoops_IRSSP) {

					HI_Queue_Special_Event (dc->_hoops_RIGC, "DX9:DeleteWindow",
						HI_Build_Special_Event_String(event_string, "DX9", dc->_hoops_AAHSR,
						(POINTER_SIZED_INT) dx9data->hWND, -1));
				}

				HI_Queue_Actor_Shutdown(dc->_hoops_GHRI, false);

			}	break;

			case WM_KEYDOWN: {
				consume_key (dx9data, wParam, lParam);
			}	break;

			case WM_MOUSEMOVE:
			case WM_RBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_LBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_MBUTTONUP:
			case WM_LBUTTONUP: {
				consume_mouse (dx9data, message, wParam, lParam);
			}	break;

			case WM_ERASEBKGND: {
				return true;
			}	_hoops_HHHI;

			case WM_WINDOWPOSCHANGING:
			{
				LPWINDOWPOS _hoops_CACRH;
				char _hoops_SACRH = false;

				_hoops_CACRH = (LPWINDOWPOS) lParam;
				if (IsIconic (_hoops_GRCRH) || IsZoomed (_hoops_GRCRH))
					break;

				if (dc->options._hoops_RASSP) {
					if (_hoops_CACRH->cx > 0 &&
						dx9data->_hoops_CIGRR.x == _hoops_CACRH->cx &&
						dx9data->_hoops_CIGRR.y == _hoops_CACRH->cy) {
						/*
						* _hoops_ICIA _hoops_IHGC _hoops_IIGR _hoops_GPCRH _hoops_CGAPR _hoops_IH _hoops_SSRR _hoops_SGH
						* _hoops_HPP _hoops_GAPGH-_hoops_GGRRR
						*/
						dx9data->_hoops_SIGRR.x = _hoops_CACRH->x;
						dx9data->_hoops_SIGRR.y = _hoops_CACRH->y;
						_hoops_SACRH = true;
					}
				}
				else {
					if (dx9data->_hoops_CIGRR.x == _hoops_CACRH->cx &&
						dx9data->_hoops_CIGRR.y == _hoops_CACRH->cy) {
						/* _hoops_RPCRH */
						_hoops_CACRH->flags |= (SWP_NOMOVE | SWP_NOREPOSITION);
						_hoops_SACRH = true;
					}
				}

				if (!dc->options._hoops_PASSP &&
					_hoops_CACRH->cx > 0 &&
					(dx9data->_hoops_CIGRR.x != _hoops_CACRH->cx ||
					 dx9data->_hoops_CIGRR.y != _hoops_CACRH->cy)) {
					/*
					 * _hoops_PS _hoops_HS _hoops_IS _hoops_APCRH _hoops_RGR _hoops_RPPS _hoops_IS _hoops_RH _hoops_PSHR
					 * _hoops_AHHSR _hoops_SCH _hoops_RIAGR _hoops_CGPR _hoops_SR _hoops_SPIP _hoops_SCH
					 */
					float			cx, cy;
					int				_hoops_PPCRH, _hoops_HPCRH, _hoops_IPCRH, _hoops_CPCRH;
					bool		_hoops_IRACA;

					_hoops_IPCRH = _hoops_CACRH->x;
					_hoops_CPCRH = _hoops_CACRH->y;
					_hoops_HPCRH = _hoops_CACRH->cx;
					_hoops_PPCRH = _hoops_CACRH->cy;

					_hoops_IRACA = false;

					_hoops_SACRH = true;
 
					cx = _hoops_HPCRH - dx9data->_hoops_CIGRR.x;
					cy = _hoops_PPCRH - dx9data->_hoops_CIGRR.y;

					if (Abs(cx) > Abs(cy)) {
						if (Abs(cy) == 0.0f) {
							_hoops_PPCRH = (int)((float) _hoops_HPCRH * (float)dx9data->_hoops_GCGRR.y /
															(float)dx9data->_hoops_GCGRR.x);

							if (_hoops_CPCRH != dx9data->_hoops_SIGRR.y)
								_hoops_CPCRH += _hoops_CACRH->cy - _hoops_PPCRH;

						}
						else{
							_hoops_HPCRH = (int)((float) _hoops_PPCRH * (float)dx9data->_hoops_GCGRR.x /
															(float)dx9data->_hoops_GCGRR.y);

							if (_hoops_IPCRH != dx9data->_hoops_SIGRR.x)
								_hoops_IPCRH += _hoops_CACRH->cx - _hoops_HPCRH;
						}
					}
					else {
						if (Abs(cx) == 0.0f) {
							_hoops_HPCRH = (int)((float) _hoops_PPCRH * (float)dx9data->_hoops_GCGRR.x /
															(float)dx9data->_hoops_GCGRR.y);

							if (_hoops_IPCRH != dx9data->_hoops_SIGRR.x)
								_hoops_IPCRH += _hoops_CACRH->cx - _hoops_HPCRH;
						}
						else{
							_hoops_PPCRH = (int)((float) _hoops_HPCRH * (float)dx9data->_hoops_GCGRR.y /
															(float)dx9data->_hoops_GCGRR.x);

							if (_hoops_CPCRH != dx9data->_hoops_SIGRR.y)
								_hoops_CPCRH += _hoops_CACRH->cy - _hoops_PPCRH;
						}
					}
					dx9data->_hoops_CIGRR.x = _hoops_HPCRH;
					dx9data->_hoops_CIGRR.y = _hoops_PPCRH;

					if (!_hoops_IRACA) {
					   _hoops_CACRH->x = _hoops_IPCRH;
					   _hoops_CACRH->y = _hoops_CPCRH;
					   _hoops_CACRH->cx = _hoops_HPCRH;
					   _hoops_CACRH->cy = _hoops_PPCRH;
					   _hoops_SACRH = true;
					}
				}
				if (!_hoops_SACRH)
					return 0;
			}	break;

			case WM_SIZE: {
				if (SIZE_MINIMIZED == wParam) {
					dx9data->_hoops_RSGRR = true;
					dx9data->_hoops_ASGRR = false;
				}
				else if (SIZE_MAXIMIZED == wParam) {
					dx9data->_hoops_RSGRR = false;
					dx9data->_hoops_ASGRR = true;
					_hoops_IHARR(dc);
				}
				else if (SIZE_RESTORED == wParam) {
					if (dx9data->_hoops_ASGRR) {
						dx9data->_hoops_ASGRR = false;
						_hoops_IHARR(dc);
					}
					else if (dx9data->_hoops_RSGRR) {
						dx9data->_hoops_RSGRR = false;
						_hoops_IHARR(dc);
					}
					else {
						// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_RSIPR _hoops_SPCRH _hoops_GHCRH _hoops_RHCRH, _hoops_RH _hoops_RPPS _hoops_IGIR
						// _hoops_HRGR _hoops_HHACR _hoops_HPP _hoops_RH _hoops_IPSP _hoops_AHCRH _hoops_RH _hoops_RPPS _hoops_SPPR.  _hoops_GPGP _hoops_RGR
						// _hoops_AGIR, _hoops_SR _hoops_GA'_hoops_RA _hoops_HIAP _hoops_RH _hoops_SISS _hoops_GAPR -- _hoops_SR _hoops_IPPRH _hoops_CCGR _hoops_RH
						// _hoops_IPSP _hoops_RHGP _hoops_AHCRH, _hoops_PPR _hoops_IRS _hoops_PHCRH _hoops_GPSRR _hoops_IISA.
					}
				}
			}	break;

			case WM_EXITSIZEMOVE: {
				//_hoops_HHCRH(_hoops_CSPH);
			}	break;

			case WM_PALETTECHANGED: {
				if (dx9data->_hoops_RIGRR) {
				/*	_hoops_CGP _hoops_RGR _hoops_CCRPR _hoops_SSAS _hoops_HAR _hoops_AGRP _hoops_RH _hoops_IHCRH, _hoops_HAIHR
					_hoops_PPR _hoops_CHCRH _hoops_RGR _hoops_CCRPR'_hoops_GRI _hoops_IHCRH	*/
					if (wParam != (WPARAM) _hoops_GRCRH) {
						/* _hoops_ISGP _hoops_PPR _hoops_CHCRH _hoops_ISCP _hoops_IHCRH */
						dx9data->_hoops_AIGRR = SelectPalette (dx9data->hDC, dx9data->_hoops_RIGRR, false);
						RealizePalette (dx9data->hDC);

						/*
						* _hoops_PAAS _hoops_RIGRP _hoops_RH _hoops_PSHA _hoops_IH _hoops_PCCP _hoops_IPCR _hoops_RPPS,
						* _hoops_SHCRH _hoops_PAH _hoops_SHH _hoops_PIGS _hoops_PGGA _hoops_SCH _hoops_HRGR _hoops_SPAC _hoops_HSAR
						* _hoops_IGSIP _hoops_RH _hoops_RPRGR _hoops_CCAC (_hoops_PRGI _hoops_PHRI _hoops_RH _hoops_ACPP _hoops_CHR
						* _hoops_HAR _hoops_GAR _hoops_RIRA)
						*/
						UpdateColors (dx9data->hDC);

						/* _hoops_SP _hoops_GH */
						if (dx9data->_hoops_AIGRR)
							SelectPalette (dx9data->hDC, dx9data->_hoops_AIGRR, false);
					}
				}
			}	break;

			case WM_QUERYNEWPALETTE: {
				if (dx9data->_hoops_RIGRR) {
					/* _hoops_ISGP _hoops_PPR _hoops_CHCRH _hoops_RH _hoops_IHCRH */
					dx9data->_hoops_AIGRR = SelectPalette (dx9data->hDC, dx9data->_hoops_RIGRR, FALSE);
					RealizePalette (dx9data->hDC);

					/* _hoops_HRHIP _hoops_RH _hoops_RPRGR _hoops_CCAC */
					InvalidateRect (_hoops_GRCRH, null, true);
					UpdateWindow (_hoops_GRCRH);

					if (dx9data->_hoops_AIGRR)
						SelectPalette (dx9data->hDC, dx9data->_hoops_AIGRR, false);

					return true;
				}

				return FALSE;
			}	_hoops_HHHI;

			case WM_POWERBROADCAST: {
				if (wParam == PBT_APMQUERYSUSPEND)
					return TRUE;

				if (wParam == PBT_APMRESUMESUSPEND) {
					if (dx9data->pDevice != null)
						_hoops_SSIRH (dc);
					HD_Force_Refresh (dc);
				}
			}	break;

			case WM_PAINT: {
				if (!dx9data->pending_resize)
					_hoops_SGCRH (dx9data, _hoops_GRCRH, true, false);
			}	break;
		}
	}
	return DefWindowProc (_hoops_GRCRH, message, wParam, lParam);

} //_hoops_RSGR '_hoops_RPPS _hoops_AACRH _hoops_AHHS'


/*
* _hoops_PGAA
* _hoops_GICRH _hoops_HGGSP _hoops_SIIRH: _hoops_RICRH _hoops_IRS _hoops_CIAGR _hoops_PGCPR _hoops_SSHRH
*/
local LRESULT APIENTRY _hoops_AICRH (HWND _hoops_GRCRH,
											 UINT message,
											 WPARAM wParam,
											 LPARAM lParam)
{
	Display_Context *	dc;

	if ((dc = HD_Find_DC_From_WID ((POINTER_SIZED_INT) _hoops_GRCRH)) != null) {
		DX9Data alter *dx9data;

		dx9data = DX9D (dc);

		switch (message) {
			case WM_ERASEBKGND: {
				/* _hoops_ASSI _hoops_SPHGR _hoops_IGHP _hoops_SCAC, _hoops_AGAH _hoops_GRS _hoops_RGHH _hoops_SCH */
				return 1L;
			}	_hoops_HHHI;

			case WM_SIZE: {
				dx9data->pending_resize = true;
			}	break;

			case WM_POWERBROADCAST: {
				if (wParam == PBT_APMQUERYSUSPEND)
					return TRUE;

				if (wParam == PBT_APMRESUMESUSPEND) {
					if (dx9data->pDevice != null)
						_hoops_SSIRH (dc);
					HD_Force_Refresh (dc);
				}
			}	break;

			case WM_PAINT: {
				_hoops_SGCRH (dx9data, _hoops_GRCRH, false, true);
			}	break;

			case WM_PALETTECHANGED: {
				if (dx9data->_hoops_RIGRR) {
					/*
					* _hoops_CGP _hoops_RGR _hoops_CCRPR _hoops_SSAS _hoops_HAR _hoops_AGRP _hoops_RH _hoops_IHCRH, _hoops_HAIHR
					* _hoops_PPR _hoops_CHCRH _hoops_RGR _hoops_CCRPR'_hoops_GRI _hoops_IHCRH
					*/
					if (wParam != (WPARAM) _hoops_GRCRH) {
						/* _hoops_ISGP _hoops_PPR _hoops_CHCRH _hoops_ISCP _hoops_IHCRH */
						dx9data->_hoops_AIGRR = SelectPalette (dx9data->hDC,
															dx9data->_hoops_RIGRR, false);
						RealizePalette (dx9data->hDC);

						UpdateColors (dx9data->hDC);

						/* _hoops_SP _hoops_GH */
						if (dx9data->_hoops_AIGRR)
							SelectPalette (dx9data->hDC, dx9data->_hoops_AIGRR, false);
					}
				}
			}	break;

			case WM_QUERYNEWPALETTE: {
				if (dx9data->_hoops_RIGRR) {
					dx9data->_hoops_AIGRR =
						SelectPalette (dx9data->hDC, dx9data->_hoops_RIGRR,
						FALSE);
					RealizePalette (dx9data->hDC);

					/* _hoops_HRHIP _hoops_RH _hoops_RPRGR _hoops_CCAC */

					InvalidateRect (_hoops_GRCRH, null, true);
					UpdateWindow (_hoops_GRCRH);

					if (dx9data->_hoops_AIGRR)
						SelectPalette (dx9data->hDC, dx9data->_hoops_AIGRR,
						false);

					return 1L;
				}
			}	break;
		}

		return CallWindowProc (dx9data->_hoops_GIGRR,
								_hoops_GRCRH, message, wParam, lParam);
	}
	return DefWindowProc (_hoops_GRCRH, message, wParam, lParam);

} //_hoops_RSGR '_hoops_PICRH _hoops_RPPS _hoops_AACRH'



/*
* _hoops_PGAA
* _hoops_HICRH _hoops_HGGSP _hoops_SIIRH: _hoops_RICRH _hoops_PCCS _hoops_SSHRH
*/
local LRESULT APIENTRY _hoops_IICRH (HWND _hoops_GRCRH,
											 UINT message,
											 WPARAM wParam,
											 LPARAM lParam)
{
	Display_Context *	dc;

	if ((dc = HD_Find_DC_From_WID ((POINTER_SIZED_INT) _hoops_GRCRH)) != null) {
		DX9Data alter *dx9data;

		dx9data = DX9D (dc);

		switch (message) {
			case WM_SIZE: {
				if (dc->_hoops_SHCIP != null)
					HD_Flush_Octree_Queries (dc->_hoops_SHCIP, dc->_hoops_AAHSR);
				dc->flags |= _hoops_ICPGR;
			}	break;

			case WM_DESTROY: {
#ifdef _WIN64
				SetWindowLongPtr (dx9data->hWND, GWLP_WNDPROC,
								(POINTER_SIZED_INT) dx9data->_hoops_GIGRR);
#else
				SetWindowLong (dx9data->hWND, GWL_WNDPROC,
								(POINTER_SIZED_INT) dx9data->_hoops_GIGRR);
#endif
			}	break;

			case WM_PAINT: {
				//_hoops_CICRH(_hoops_CRCRH, _hoops_RGCRH, _hoops_IHPR, _hoops_RCPP);
				break;
			}
		}


		return CallWindowProc (dx9data->_hoops_GIGRR,
								 _hoops_GRCRH, message, wParam, lParam);
	}
	return DefWindowProc (_hoops_GRCRH, message, wParam, lParam);

} //_hoops_RSGR '_hoops_PCCS _hoops_RPPS _hoops_AACRH'


/*****************************************************************************
*****************************************************************************
						_hoops_CCAGR/_hoops_ASAP _hoops_HRHI _hoops_PPR
						_hoops_CCAGR/_hoops_ASAP _hoops_SICRH
*****************************************************************************
*****************************************************************************/

local POINTER_SIZED_INT get_outer_window (Display_Context const * _hoops_SAGRH);

/*
* _hoops_SRAC
*/
local void init_update (Display_Context const * dc)
{
	DX9Data alter *dx9data = DX9D (dc);
	H3D_TRACE(dx9data, "init_update");

	RECT rect;

	if (!BIT(dc->flags, _hoops_SAISR))
		return;

	if (dx9data->_hoops_PIGRR == _hoops_PPSGR) {
		if (!dc->options._hoops_CRSSP &&
			!BIT (dc->options._hoops_IRARR, _hoops_GCCRH))
			check_events (dx9data);
		/* _hoops_HGI _hoops_SPS _hoops_III _hoops_HRGR _hoops_GIIRH _hoops_HAHH _hoops_IS _hoops_SGHIP _hoops_RH _hoops_CRS */
		dx9data = DX9D (dc);
		if (!dx9data) 
			return;
	}

	if (!IsWindow (dx9data->hWND))
		return;

	if (IsIconic(dx9data->hWND)) {
		HD_Interrupt_Update(dc, false, false);
		_hoops_APSRR(dc, "IsIconic(dx9data->hWND)","", 0);
		return;
	}	
	if (dx9data->_hoops_ASRRR) {
		get_outer_window(dc);
	}

	if (dx9data->hWND != null) {
		if (IsZoomed (dx9data->hWND))
			((Display_Context alter *) dc)->options._hoops_PASSP = true;

		GetClientRect (dx9data->hWND, &rect);

		if (!EqualRect (&rect, (RECT *) &dx9data->_hoops_HIGRR)) {
			CopyRect ((RECT *) &dx9data->_hoops_HIGRR, &rect);
			_hoops_IHARR(const_cast<Display_Context*>(dc));

			dx9data->yfudge = rect.bottom - 1;

			HD_Resize_Subscreen (dc, true,
									0, rect.right - 1,
									0, rect.bottom - 1);
		}

		if ((dx9data->pDevice->TestCooperativeLevel () != S_OK) ||
			BIT (dc->_hoops_GHRI->_hoops_CGPIR, _hoops_IRSCA)) {
			((_hoops_GGAGR alter *)dc->_hoops_GHRI)->_hoops_CGPIR &= ~_hoops_IRSCA;

			if (dx9data->pDevice != null)
				_hoops_SSIRH ((Display_Context alter *)dc);
		}
	}
}


/*
* _hoops_SRAC
*/
local void finish_update (Display_Context const * dc)
{
	DX9Data alter *dx9data = DX9D (dc);
	H3D_TRACE(dx9data, "finish_update");


	if (!BIT(dc->flags, _hoops_SAISR))
		return;

	if (dx9data->_hoops_PIGRR == _hoops_PPSGR)
		if (!dc->options._hoops_CRSSP &&
			!BIT (dc->options._hoops_IRARR, _hoops_GCCRH))
			check_events (dx9data);
}


/*
* _hoops_PGAA. _hoops_PHIC _hoops_PGAP _hoops_HCH _hoops_AGI _hoops_IS _hoops_AA.
*/
local void _hoops_RCCRH( DX9Data& dx9data )
{
	// _hoops_HR _hoops_PSP _hoops_AGI _hoops_CCGR _hoops_SR'_hoops_RISP _hoops_GIPCR _hoops_SR _hoops_PAH _hoops_AA _hoops_CAPR.
	dx9data._hoops_II._hoops_SGAP = 0;

	// _hoops_ACCRH _hoops_HCH-_hoops_AAR _hoops_AGI
	int _hoops_HHAIR = 0;
	if ( dx9data.dc->options._hoops_PPSSP )
		_hoops_HHAIR |= _hoops_CGPP;
	if ( dx9data.dc->options._hoops_RPSSP )
		_hoops_HHAIR |= _hoops_CRHP;
	if ( dx9data.dc->options._hoops_APSSP )
		_hoops_HHAIR |= _hoops_AHHP;
	if ( false )
		_hoops_HHAIR |= _hoops_GGCRR;
	if ( dx9data.dc->options._hoops_HPSSP )
		_hoops_HHAIR |= _hoops_GIHP;
	if ( dx9data._hoops_IHGRR && dx9data._hoops_IHGRR->format == _hoops_PCCRH )
		_hoops_HHAIR |= _hoops_AGCRR;
	
	// _hoops_PHAA _hoops_GHIR _hoops_RHIR, _hoops_SRPS _hoops_RH _hoops_HCCRH _hoops_HRGH
	bool _hoops_ICCRH = false;
	if ( _hoops_ICCRH && !dx9data._hoops_HHRRR._hoops_RHRRR )
		_hoops_HHAIR |= _hoops_RGCRR;

	// _hoops_ASC _hoops_CHR _hoops_HAR _hoops_APIP _hoops_CCGR _hoops_RAS _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_HIRA.
	dx9data._hoops_II._hoops_CCCS = 0.0f;
	dx9data._hoops_II._hoops_ICCS = 0.0f;

	// _hoops_CGP _hoops_AGI _hoops_CHR _hoops_HGRC _hoops_PPR _hoops_APP
	if ( _hoops_HHAIR && 
		 dx9data._hoops_GRAP > 1 && 
		 BIT (dx9data._hoops_HPHRH.PrimitiveMiscCaps, D3DPMISCCAPS_INDEPENDENTWRITEMASKS) ) {
		dx9data._hoops_II._hoops_SGAP = _hoops_HHAIR;

		if ( !dx9data._hoops_GAP )
			dx9data._hoops_II._hoops_PRI = true;
	}
}


/**
 * _hoops_PGAA - _hoops_GHAA _hoops_CCCRH _hoops_RAR _hoops_IIGR _hoops_IARRA _hoops_HIRA _hoops_IS _hoops_RGR _hoops_HIRA.
 */
void _hoops_SCCRH( DX9Data& dx9data)
{
	ASSERT( dx9data.post );
	_hoops_GSCRH &post = *(_hoops_GSCRH *)dx9data.post;

	if ( post._hoops_GGPP() ) {
 
		if ( H3DConstantTable *_hoops_AIPA = post._hoops_PIGP( H3DPost::_hoops_HGRGR, H3DPost::_hoops_HACRR ) ) {

			// _hoops_SIIR _hoops_AI.
			if ( DWORD _hoops_PCI = _hoops_AIPA->GetSamplerIndex("Depth") < _hoops_CIGP ) {
				// _hoops_AHH: _hoops_SIGP: _hoops_GCGP _hoops_RCGP _hoops_HRGR _hoops_ACGP _hoops_ARI, _hoops_HIS _hoops_SR _hoops_HHSA _hoops_SCH _hoops_IS _hoops_PCGP _hoops_GGR 
				//   _hoops_RH _hoops_CI _hoops_PPR _hoops_GGR _hoops_HCGP 
				_hoops_SCCR(&dx9data, 0, dx9data._hoops_HHRRR._hoops_RHRRR);
				_hoops_GRPA(&dx9data, 0, H3DTEXF_LINEAR, H3DTEXF_LINEAR, H3DTADDRESS_CLAMP);
			}
			if ( DWORD _hoops_PCI = _hoops_AIPA->GetSamplerIndex("Scene") < _hoops_CIGP ) {
				// _hoops_AHH: _hoops_SIGP: _hoops_GCGP _hoops_RCGP _hoops_HRGR _hoops_ACGP _hoops_ARI, _hoops_HIS _hoops_SR _hoops_HHSA _hoops_SCH _hoops_IS _hoops_PCGP _hoops_GGR 
				//   _hoops_RH _hoops_CI _hoops_PPR _hoops_GGR _hoops_HCGP 
				_hoops_SCCR(&dx9data, 1, dx9data._hoops_HHRRR._hoops_AHRRR);
				_hoops_GRPA(&dx9data, 1, H3DTEXF_LINEAR, H3DTEXF_LINEAR, H3DTADDRESS_CLAMP);
			}

			/// _hoops_HPSP: _hoops_SIPR _hoops_SCGR _hoops_HIHP
			float transform[16];
			memcpy( transform, dx9data._hoops_SPSR, sizeof(transform) );

			// _hoops_ACGR _hoops_ISGSP _hoops_HII _hoops_RCPGR _hoops_HIHP _hoops_IS _hoops_RGR _hoops_SPR.
			float _hoops_RSCRH[16];
			HI_Compute_Matrix_Inverse (dx9data._hoops_HHRRR._hoops_PHRRR, _hoops_RSCRH);
			float delta[16];
			HI_Matmul_44_by_44 (_hoops_RSCRH, transform, delta);

			// _hoops_HCGA _hoops_RHC _hoops_AAGA _hoops_HII _hoops_RCPGR _hoops_HIHP
			_hoops_AIPA->SetFloatArray("EyeDir", &delta[8], 3);

			// _hoops_IISH _hoops_RH _hoops_CSCR
			ENSURE_TRANSPARENCY(&dx9data, false);
			_hoops_PISP(&dx9data, false);
			ENSURE_DEPTH_MASK(&dx9data, true);
			post._hoops_HPRP(dx9data.render_target, H3DPost::_hoops_HACRR, 0.0f, delta );
		
		}

		post._hoops_PRHP();
	}
}

/*
* _hoops_SRAC
*/
local void init_picture (Net_Rendition const &  nr)
{
	DX9Data alter *dx9data = DX9NRD (nr);
	H3D_TRACE(dx9data, "init_picture");

	Display_Context const *dc = nr->_hoops_SRA;
	if (dx9data->_hoops_ASRRR)
		return;

	if (!dx9data->_hoops_IGCRH)
		dx9data->pDevice->CreateAdditionalSwapChain(&dx9data->_hoops_HCARH, &dx9data->_hoops_IGCRH);

	// _hoops_AIAP _hoops_CGRH _hoops_IS _hoops_ASCRH _hoops_IRGAA _hoops_SRHR _hoops_PPR _hoops_PHHR _hoops_CPPRH.
	if (dc->_hoops_RIGC->_hoops_HCPGR == 0)
		_hoops_SGPAR(dx9data);

	dx9data->_hoops_CSC->_hoops_CRGRR = BIT(nr->transform_rendition->flags , _hoops_PIHIP);
	_hoops_SSPRR (dx9data, BIT(nr->transform_rendition->flags, _hoops_PASP));
	ENSURE_DEPTH_MASK (dx9data, !BIT(nr->transform_rendition->flags, _hoops_ISH));
	
	dx9data->_hoops_HCAC = 
		dx9data->_hoops_ASIH = 
			dx9data->_hoops_ACHH = _hoops_CCC;
	dx9data->_hoops_CSC->_hoops_GSCH[0] = 0.00015712534142563f; //_hoops_HRCI

	_hoops_RPAP (dx9data, !nr->_hoops_IRR->_hoops_GIRC);
	_hoops_GPRP (dx9data, H3DMASK_RGB);
	//_hoops_RCGHA(_hoops_CRCRH->_hoops_PSCRH, _hoops_GGHSP(_hoops_CRCRH->_hoops_PSCRH), 0);

	if (!BIT(dc->flags, _hoops_GPHHP)) {
		if (dx9data->_hoops_PIGRR == DCT_IMAGE) {
			Image alter				*image;

			image = (Image alter *)_hoops_RCSSR (dc->_hoops_RIGC, dc->options._hoops_GCHSR);
			if (image != dx9data->_hoops_IHGRR) {
				/* _hoops_SIGP: _hoops_ISPR _hoops_IH _hoops_CSCR _hoops_IGIR _hoops_AGRP */
				if (image == null) {
					HE_ERROR (HEC_DX9_DRIVER, HES_INVALID_KEY,
							"An invalid key was passed to the DX9 driver with USE_WINDOW_IS_IMAGE set."); 
					return;
				}
				_hoops_HPRH (dx9data->_hoops_IHGRR);
				dx9data->_hoops_IHGRR = image;
				_hoops_PRRH (dx9data->_hoops_IHGRR);
			}
		}
	}

	// _hoops_PHAA _hoops_GHIR?
	if ( !dx9data->_hoops_AHGRR )
	{
		// _hoops_PHAA _hoops_HSRS _hoops_HCH _hoops_AGI, _hoops_RPP _hoops_GII.
		_hoops_RCCRH(*dx9data);

		// _hoops_HSCRH _hoops_ARHP _hoops_CCH _hoops_IIHA _hoops_GPP _hoops_IPSP'_hoops_GRI _hoops_IAGC _hoops_PPR _hoops_ISCP _hoops_ISCRH.
		_hoops_CGGRR _hoops_CSCRH = _hoops_GRGRR;
		int _hoops_AGPRH = 0;
		if ( dx9data->dc->options._hoops_RIPGA ) {
			_hoops_AGPRH = dx9data->dc->options._hoops_AIPGA;
			_hoops_CSCRH = dx9data->_hoops_II._hoops_SGAP ? _hoops_AHRS : _hoops_SRAP;
			if (XBIT_TEST(dx9data->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_MSAA_SPRITING))
				_hoops_CSCRH = _hoops_AHRS;
		}

		// _hoops_AHH: _hoops_SSCRH _hoops_CHR _hoops_HA _hoops_PSPP _hoops_GGR _hoops_CGCRH. _hoops_HHIGR _hoops_PIHA _hoops_SHH _hoops_PIGS _hoops_GGR _hoops_GGSRH
		_hoops_RGPRH(*dx9data, _hoops_CSCRH, _hoops_AGPRH );

		// _hoops_CPGP _hoops_SR'_hoops_ASAR _hoops_GRP _hoops_GGSHR _hoops_RGSRH, _hoops_SR _hoops_PIHA _hoops_GHSGR _hoops_RH _hoops_AGSRH _hoops_AHCS _hoops_CHR _hoops_ARP _hoops_RCSAR _hoops_GHIR
		_hoops_GPAP(*dx9data, 
			dx9data->_hoops_CIARH._hoops_SIARH, 
			dx9data->_hoops_CIARH.ds, 
			dx9data->_hoops_CIARH._hoops_GCARH, 
			dx9data->_hoops_CIARH._hoops_RCARH, 
			dx9data->_hoops_CIARH._hoops_ACARH);

		// _hoops_SIIR _hoops_IH _hoops_HCH-_hoops_AAR _hoops_AGI
		if (dx9data->_hoops_II._hoops_SGAP)
			_hoops_IGAP(dx9data, dc->_hoops_CGAP);

		// _hoops_PHAA _hoops_GHIR _hoops_RARP.
		dx9data->pDevice->BeginScene();
		dx9data->_hoops_AHGRR = true;
	}
	else {
		// _hoops_PGSRH _hoops_PAAP - _hoops_PHIH _hoops_PGHC _hoops_CIGC _hoops_CSCR _hoops_RPP _hoops_SR _hoops_HS _hoops_SPR
		_hoops_PIPGR(nr, null, dx9data->_hoops_CCIRH, dx9data->_hoops_ICIRH);
	}

#if defined(_hoops_SPARH)
	if (dx9data->_hoops_RP) {
		HANDLE _hoops_HGSRH;
		WIN32_FIND_DATA _hoops_IGSRH;
		char _hoops_CGSRH[2048];

		if (!_hoops_RHARH)
			_hoops_RHARH = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_GHARH)(HOOPS_WORLD->memory_pool);

		_hoops_CGSRH[0] = '\0';
		if (_hoops_SCPR())
			sprintf(_hoops_CGSRH, "%s\\*.hlsl", _hoops_SCPR());
		_hoops_HGSRH = FindFirstFile(_hoops_CGSRH, &_hoops_IGSRH);

		if (_hoops_HGSRH != INVALID_HANDLE_VALUE) {	
			bool _hoops_GHIAA = false;
			do {
				FILETIME *_hoops_SGSRH = 0;
				FILETIME *_hoops_GRSRH = 0;
				int status = _hoops_RHARH->LookupItem(_hoops_IGSRH.cFileName, &_hoops_SGSRH);
				if (status != VHASH_STATUS_SUCCESS)
				{
					_hoops_GRSRH = new FILETIME();
					COPY_MEMORY(&_hoops_IGSRH.ftLastWriteTime, sizeof(FILETIME), _hoops_GRSRH);
					_hoops_RHARH->InsertItem(_hoops_IGSRH.cFileName, _hoops_GRSRH);
				}
				else if (_hoops_IGSRH.ftLastWriteTime.dwHighDateTime > _hoops_SGSRH->dwHighDateTime ||
					(_hoops_IGSRH.ftLastWriteTime.dwHighDateTime == _hoops_SGSRH->dwHighDateTime &&
					_hoops_IGSRH.ftLastWriteTime.dwLowDateTime > _hoops_SGSRH->dwLowDateTime))
				{
					_hoops_GHIAA = true;
					COPY_MEMORY(&_hoops_IGSRH.ftLastWriteTime, sizeof(FILETIME), _hoops_SGSRH);
				}

			} while (FindNextFile(_hoops_HGSRH, &_hoops_IGSRH));
			FindClose(_hoops_HGSRH);

			if (_hoops_GHIAA)
			{
				// _hoops_GGPRH _hoops_AIRRR
				delete dx9data->_hoops_IP;
				dx9data->_hoops_IP = NEW(H3DShaderHASH)(dx9data);

				// _hoops_GGPRH _hoops_RHAA _hoops_AIRRR
				dx9data->post->_hoops_GICRR();
			}
		}	
	}
#endif
}


local bool snapshot(Net_Rendition const &  nr, int width, int height, unsigned char * data); //_hoops_CPCHR

/* _hoops_RGR _hoops_API _hoops_SAGGR _hoops_RH _hoops_CSCR _hoops_CRGR _hoops_RH _hoops_IIPR _hoops_SRHR, _hoops_PPR _hoops_RRSRH _hoops_SCH
 * _hoops_GAR _hoops_SCH _hoops_IAGA. */
local void *_hoops_ARSRH (
		_hoops_SHGH const *input, 
		int w, 
		int h, 
		int _hoops_HAPIR, 
		void alter *_hoops_PRSRH)
{
	int i;

	if (_hoops_HAPIR == Image_RGBA32) {
		_hoops_AIGH *output=(_hoops_AIGH alter *)_hoops_PRSRH;
		for (i = 0 ; i < h ; i++) {
			_hoops_AIGH *ptr = output + w*i;
			_hoops_AIGH *end = ptr + w;
			while (ptr < end) {
				ptr->r = input->r;
				ptr->g = input->g;
				ptr->b = input->b;
				ptr->a = 255;
				ptr++;
				input++;
			}
		}

		return output + w*h;
	}
	else 
	if (_hoops_HAPIR == _hoops_CSGSP) {
		RGBAS32 *output = (RGBAS32 alter *)_hoops_PRSRH;
		for (i = 0 ; i < h ; i++) {
			RGBAS32 *ptr = output + w*i;
			RGBAS32 *end = ptr + w;
			while (ptr < end) {
				ptr->r = input->r;
				ptr->g = input->g;
				ptr->b = input->b;
				ptr->a = 255;
				ptr++;
				input++;
			}
		}
		return output + w*h;
	}
	else 
	if (_hoops_HAPIR == _hoops_HRSRH) {
		_hoops_IRSRH *output = (_hoops_IRSRH alter *)_hoops_PRSRH;
		for (i = 0 ; i < h ; i++) {
			_hoops_IRSRH *ptr = output + w*i;
			_hoops_IRSRH *end = ptr + w;
			while (ptr < end) {
				ptr->r = input->r;
				ptr->g = input->g;
				ptr->b = input->b;
				ptr->a = 255;
				ptr++;
				input++;
			}
		}
		return output + w*h;
	}
	else 
	if (_hoops_HAPIR == _hoops_HHGH) {
		_hoops_SHGH *output = (_hoops_SHGH alter *)_hoops_PRSRH;
		for (i = 0 ; i < h ; i++) {
			_hoops_SHGH *ptr = output + w*i;
			_hoops_SHGH *end = ptr + w;
			while (ptr < end) {
				ptr->r = input->r;
				ptr->g = input->g;
				ptr->b = input->b;
				ptr++;
				input++;
			}
		}
		return output + w*h;
	}
	else if (_hoops_HAPIR == _hoops_GGRH || 
			 _hoops_HAPIR == _hoops_RGRH || 
			 _hoops_HAPIR == _hoops_AGRH || 
			 _hoops_HAPIR == _hoops_IRRH || 
			 _hoops_HAPIR == _hoops_CRRH || 
			 _hoops_HAPIR == _hoops_SRRH) {
		HE_ERROR (HEC_DX9_DRIVER, HES_BAD_VALUE,
			"compressed output image format not allowed in DX9 driver."); 
		return null;
	}
	else if (_hoops_HAPIR == _hoops_AHGH) {
		HE_ERROR (HEC_DX9_DRIVER, HES_BAD_VALUE,
			"gray scale output image format not allowed in DX9 driver."); 
		return null;
	}
	else {
		HE_ERROR (HEC_DX9_DRIVER, HES_BAD_VALUE,
			"unexpected output image format in DX9 driver."); 
		return null;
	}
}

/*
* _hoops_SRAC
*/
local void _hoops_PCPGR (Net_Rendition const &nr)
{
	DX9Data alter *dx9data = DX9NRD (nr);

	H3D_TRACE(dx9data, "postprocess_picture");

	ENSURE_TRANSPARENCY(dx9data, false);
	_hoops_APHH(dx9data, 0.0f, 1.0f);

	//
	// _hoops_GHRRR _hoops_SRS.
	//

	// _hoops_CGP _hoops_SR _hoops_HS _hoops_HCCRH _hoops_IS _hoops_SGH, _hoops_SGH _hoops_SCH
	if ( dx9data->_hoops_HHRRR._hoops_RHRRR && dx9data->_hoops_HHRRR._hoops_AHRRR ) {
		_hoops_SCCRH( *dx9data);
	}

	//
	// _hoops_SPAA _hoops_HCH _hoops_AGI
	//

	// _hoops_ASAP _hoops_HCH _hoops_AGI
	_hoops_HSAP(nr);

	//
	// _hoops_SPAA _hoops_RII _hoops_AGI
	//

	bool _hoops_CRSRH = false;

	if ( dx9data->dc->options._hoops_RGSH )
		_hoops_CRSRH = true;

	// _hoops_AHH: _hoops_RGHSP _hoops_SRSRH _hoops_GCA _hoops_RGR
	if ( dx9data->_hoops_II._hoops_SGAP & _hoops_RGCRR )
		_hoops_CRSRH = true;

	// _hoops_CGIP _hoops_GGSR _hoops_CAS _hoops_IS _hoops_CCGSP _hoops_IS
	if ( _hoops_CRSRH ) {

		_hoops_GPRP(dx9data, H3DMASK_RGBA);

		// _hoops_SIAP _hoops_HIRA _hoops_GAR _hoops_HCGP _hoops_IH _hoops_RHAA _hoops_AGI
		if ( H3DTexture *_hoops_GASRH = dx9data->post->_hoops_IAAP( 
			dx9data->_hoops_HCARH.BackBufferWidth, dx9data->_hoops_HCARH.BackBufferHeight, dx9data->render_target->_hoops_GSPP) )
		{
			dx9data->pDevice->EndScene();

			// _hoops_HSRR _hoops_ICPP, _hoops_RGRR _hoops_RH _hoops_CCGSP. _hoops_HSRR _hoops_RRGS, _hoops_AAIR _hoops_PIRC _hoops_IS _hoops_HGCR _hoops_GSIA _hoops_PRRHP.
			D3DTEXTUREFILTERTYPE filter = (dx9data->_hoops_CRAP == _hoops_AHRS) ? 
				D3DTEXF_LINEAR : D3DTEXF_NONE;

			// _hoops_RASRH _hoops_HII _hoops_HIRA (_hoops_GCAS _hoops_RRGS _hoops_PAR _hoops_ICPP) _hoops_IS _hoops_HH
			IDirect3DSurface9 *target = null;
			if ( SUCCEEDED( ((_hoops_RIARH *) _hoops_GASRH)->GetSurfaceLevel(0, &target)) ) {
				dx9data->pDevice->StretchRect( _hoops_PIARH(dx9data->render_target), null, target, null, filter);
				H_SAFE_RELEASE(target);
			}

			dx9data->pDevice->BeginScene();

			// _hoops_IGPP _hoops_RH _hoops_HIRA _hoops_HH _hoops_IPSH _hoops_AGI _hoops_IS _hoops_RH _hoops_SRGS _hoops_SAAP
			_hoops_ISCH( dx9data, _hoops_GASRH, dx9data->render_target );

			// _hoops_AASRH _hoops_HH _hoops_IH _hoops_HCCRH
			if ( dx9data->_hoops_II._hoops_SGAP & _hoops_RGCRR ) {
				dx9data->_hoops_HHRRR._hoops_AHRRR = _hoops_GASRH;
				_hoops_GASRH = NULL;
			}

			if ( _hoops_GASRH )
				// _hoops_PPGGR _hoops_HH
				dx9data->post->_hoops_HAAP( &_hoops_GASRH );
		}
	}
}


/*
* _hoops_SRAC
*/
local void finish_picture (Net_Rendition const &  nr,
						   bool swap_buffers)
{
	Display_Context const *dc = nr->_hoops_SRA;
	DX9Data alter *dx9data = DX9NRD (nr);

	H3D_TRACE(dx9data, "finish_picture");

	IDirect3DSurface9 *_hoops_CSCH = null;
	HRESULT _hoops_IIRHP;

	// _hoops_RAPRH _hoops_SR _hoops_HSPP _hoops_AIAH?
	if ( dx9data->_hoops_AHGRR )
	{
		ENSURE_TRANSPARENCY(dx9data, false);
		_hoops_APHH(dx9data, 0.0f, 1.0f);

		if (dx9data->_hoops_PASRH) {
			int x = 0;
			int size = 200;

			// _hoops_PPPA _hoops_AIRI _hoops_CPCI
			_hoops_CAAI (HOOPS_WORLD->_hoops_SAAI);
			for ( _hoops_AGCI *dl = HOOPS_WORLD->_hoops_GPAI; dl; dl = dl->next ) { 
				H3D_Display_List *_hoops_PICI = (H3D_Display_List *) dl;
				if ( _hoops_PICI->type == H3D_DL_SHADOW_MAP ) {
					// _hoops_GISP _hoops_PPR _hoops_GCHGA _hoops_HASRH.
					dx9data->_hoops_GSCR->_hoops_GHIP(dx9data, _hoops_PICI->item._hoops_HRR.id, x, 0, size, size);
					x += size;
				}
			}
			_hoops_APAI (HOOPS_WORLD->_hoops_SAAI);
		}

		// _hoops_ASAP _hoops_HIRA.
		dx9data->pDevice->EndScene();
		dx9data->_hoops_AHGRR = false;
	}

	// _hoops_IGPP _hoops_HIRA _hoops_IS _hoops_AISH
	if (dx9data->_hoops_PIGRR != DCT_IMAGE) {
		_hoops_IIRHP = dx9data->_hoops_IGCRH->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &_hoops_CSCH);
		if ( _hoops_CSCH ) {

			// _hoops_RASRH _hoops_RH _hoops_HSCH _hoops_HIRA _hoops_CIAA _hoops_RH _hoops_AISH
			// _hoops_HSRR _hoops_ICPP, _hoops_RGRR _hoops_RH _hoops_CCGSP. _hoops_HSRR _hoops_RRGS, _hoops_AAIR _hoops_PIRC _hoops_IS _hoops_HGCR _hoops_GSIA _hoops_PRRHP.
			D3DTEXTUREFILTERTYPE filter = (dx9data->_hoops_CRAP == _hoops_AHRS) ? 
				D3DTEXF_LINEAR : D3DTEXF_NONE;
			dx9data->pDevice->StretchRect (_hoops_PIARH(dx9data->render_target), null, _hoops_CSCH, null, filter);

			// _hoops_PPGGR _hoops_SAAP, _hoops_PSP _hoops_RPIP _hoops_SIGR
			H_SAFE_RELEASE(_hoops_CSCH);
		}
	}

	_hoops_GCRRR(dx9data);
	_hoops_RCRRR(dx9data);

	// _hoops_AGGA _hoops_HGSR _hoops_IH _hoops_SPS _hoops_HCHSR
	dx9data->_hoops_GSCR->_hoops_GPAP(dx9data->render_target, dx9data->depth_stencil);

	if (dx9data->_hoops_PIGRR == DCT_IMAGE) {
		if (!BIT (dc->flags, _hoops_SAISR))	// _hoops_PAHH _hoops_IASRH _hoops_ISHP _hoops_RH _hoops_RHPP
			return;
	
		if (!BIT(dx9data->_hoops_IHGRR->flags, _hoops_GRRH))
			HI_Clear_Image_Cache(dx9data->_hoops_IHGRR);
		else {
			if (dx9data->_hoops_IHGRR->_hoops_PHGH) {
				FREE_ARRAY(dx9data->_hoops_IHGRR->_hoops_PHGH, dx9data->_hoops_IHGRR->width * dx9data->_hoops_IHGRR->height * dx9data->_hoops_IHGRR->_hoops_GCPIR, char);
				dx9data->_hoops_IHGRR->_hoops_PHGH = null;
			}
		}

		if (BIT(dc->flags, _hoops_SAISR))
			HI_Set_Delayed_Activity (dx9data->_hoops_IHGRR->owner, _hoops_IHSSR,
									 dx9data->_hoops_IHGRR, _hoops_HHSSR);
	}

	//_hoops_RPP (/*!_hoops_CASRH(_hoops_CSPH) &&*/ _hoops_IRRC(_hoops_CSPH->_hoops_SGI, _hoops_SASRH)) 
	{
		if (dx9data->_hoops_PIGRR == DCT_IMAGE) {
			_hoops_SHGH alter *ptr;
			int w, h;
			w = dx9data->_hoops_IHGRR->width;
			h = dx9data->_hoops_IHGRR->height;
			if (BIT (dc->options.flags, _hoops_CIPRP)) {
				_hoops_GACR alter *dl;
				H3D_Display_List alter *odl=0;
				bool _hoops_RACR;
				H3DFORMAT fmt;

				dx9data->_hoops_IHGRR->flags |= _hoops_GRRH;
				_hoops_RACR = _hoops_AACR(nr, &dx9data->_hoops_IHGRR->_hoops_GAHA, &dl, &odl, H3D_DL_TEXTURE);
				fmt = _hoops_RSRH(dx9data->_hoops_IHGRR->format);
				if (_hoops_RACR) {
					odl->item.texture.id = NEW(_hoops_RIARH)(
						dx9data, 
						w, h, 0,  
						H3DTEXUSAGE_RENDERTARGET,
						fmt);
					odl->_hoops_PPAH->owner = (_hoops_HPAH *)dx9data->_hoops_IHGRR;
				}

				if (odl->item.texture.id->_hoops_SSARR == 4) {
					dx9data->pDevice->BeginScene();
					_hoops_IRIRH(dx9data);
					dx9data->pDevice->EndScene();
				}
				_hoops_HGIP (dx9data->pDevice, ((_hoops_HIARH*)dx9data->render_target)->_hoops_IIARH(), odl->item.texture.id);
			}
			else {
				if (dx9data->_hoops_IHGRR->format == _hoops_PCCRH) {
					// _hoops_HGI _hoops_HRGR _hoops_IPIH _hoops_GIR _hoops_GGR _hoops_GPSRH
				}
				else {
					if (dx9data->_hoops_IHGRR->format == _hoops_HHGH)
						ptr = (_hoops_SHGH alter *)dx9data->_hoops_IHGRR->_hoops_PHGH;
					else
						POOL_ALLOC_ARRAY_CACHED (ptr, w*h, _hoops_SHGH, dc->memory_pool);

					snapshot (nr, w, h, (unsigned char alter *)ptr);
					if (ptr != dx9data->_hoops_IHGRR->_hoops_PHGH) {
						_hoops_ARSRH (ptr, w, h, 
								dx9data->_hoops_IHGRR->format, 
								(void alter *)dx9data->_hoops_IHGRR->_hoops_PHGH);
						FREE_ARRAY (ptr, w*h, _hoops_SHGH);
					}
				}
			}
		}
		else if (!BIT(dc->flags, _hoops_CHSI)) {
			_hoops_IIRHP = dx9data->_hoops_IGCRH->Present(null, null, null, null, 0);
			
			/* _hoops_CGP _hoops_RH _hoops_SISS _hoops_HRGR _hoops_CISS, _hoops_SGHHR _hoops_IS _hoops_RPSRH _hoops_SCH */
			if (_hoops_IIRHP == D3DERR_DEVICELOST) {
				if (FAILED(_hoops_IIRHP = dx9data->pDevice->TestCooperativeLevel())) {
					if (_hoops_IIRHP == D3DERR_DEVICELOST)
						return;

					if (_hoops_IIRHP == D3DERR_DEVICENOTRESET) {
						_hoops_SSIRH((Display_Context alter *)nr->_hoops_SRA);
						HD_Force_Refresh (nr->_hoops_SRA);
						return;
					}
				}
			}

			// _hoops_AIAP _hoops_CGRH _hoops_IS _hoops_ASCRH _hoops_IRGAA _hoops_SRHR _hoops_PPR _hoops_PHHR _hoops_CPPRH.
			if (dc->_hoops_RIGC->_hoops_HCPGR != 0)
				_hoops_SGPAR(dx9data);
		}
	}
	if (dx9data->hWND &&
		!dc->options._hoops_CRSSP &&
		!BIT (nr->_hoops_SRA->options._hoops_IRARR, _hoops_GCCRH))
		ValidateRect (dx9data->hWND, (RECT *) &dx9data->_hoops_IIGRR);
	SetRectEmpty ((RECT *) &dx9data->_hoops_IIGRR);
	UNREFERENCED(swap_buffers);

#ifdef _hoops_APSRH
	delete dx9data->_hoops_IP;
	dx9data->_hoops_IP = new H3DShaderHASH (dx9data);
#endif
}

/*****************************************************************************
*****************************************************************************
_hoops_PPSRH
*****************************************************************************
*****************************************************************************/

/*
 * _hoops_SRAC
 */
local bool measure_char(
	Net_Rendition const & nr,
	Font_Instance const *instance,
	Karacter _hoops_IPCSR,
	float alter *_hoops_GGGS,
	bool alter *_hoops_CPCSR,
	void ** _hoops_HPSRH) {

	return HI_W32_measure_char_stenciled(nr, instance, _hoops_IPCSR, _hoops_GGGS, _hoops_CPCSR, _hoops_HPSRH);
}

/*
 * _hoops_SRAC
 */
local _hoops_RAARP * _hoops_RGSSP (	
	Net_Rendition const & nr,
	Font_Instance const	*instance,
	unsigned short			_hoops_IPCSR,
	int						bitmap_height,
	int						bolding_level,
	float					xrslant,
	float					xrrotation,
	float					xrwidth_scale,
	bool				antialias) {

	UNREFERENCED(nr);

	return HI_W32_make_font_stencil (instance, _hoops_IPCSR, 
									bitmap_height, bolding_level,
									xrslant,xrrotation,xrwidth_scale,
									antialias); 
}


/*
 * _hoops_SRAC
 */
local void
unload_font (
	Display_Context const * dc,
	Font_Instance alter	*instance) {

	HI_W32_unload_font_stenciled(dc, instance);
}


/*
 * _hoops_SRAC
 */
local void *
load_font(
	Display_Context const * dc,
	char const * name,
	Font_Instance alter * instance) {

	DX9Data alter *dx9data = DX9D (dc);
	_hoops_RRPRH alter *_hoops_IRSRA = _hoops_ARPRH ();

	return HI_W32_load_font_stenciled(dc, name, instance, dx9data->hDC, &dx9data->_hoops_GRRRR, &_hoops_IRSRA->font_list);
}


/*
 * _hoops_SRAC
 */
local bool _hoops_CSCSP(
	Net_Rendition const		&nr,
	_hoops_IGPIR const			*_hoops_RRCSP,
	_hoops_IGPIR alter			*_hoops_ARCSP) {

	return HI_W32_name_font(nr, _hoops_RRCSP, _hoops_ARCSP);
}


/*
 * _hoops_SRAC
 */
local void find_all_fonts (
	Display_Context alter *dc) {

	DX9Data alter *dx9data = DX9D (dc);
	_hoops_RRPRH alter *_hoops_IRSRA = _hoops_ARPRH ();

	HI_W32_find_all_fonts (dc, &dx9data->_hoops_GRRRR, &_hoops_IRSRA->font_list);
}


/*
 *	** _hoops_SRAC **
 */
local bool _hoops_AACSR (
	Display_Context alter	*dc,
	char const					 *_hoops_PACSR) {

	DX9Data alter *dx9data = DX9D (dc);
	_hoops_RRPRH alter *_hoops_IRSRA = _hoops_ARPRH ();

	return HI_W32_find_one_font (dc, _hoops_PACSR, dx9data->hDC, &dx9data->_hoops_GRRRR, &_hoops_IRSRA->font_list);
}

/*
 * _hoops_SRAC
 */
local void _hoops_CACSR (
	Display_Context alter *dc) {

	DX9Data alter *dx9data = DX9D (dc);
	_hoops_RRPRH alter *_hoops_IRSRA = _hoops_ARPRH ();

	HI_W32_find_basic_fonts (dc, dx9data->hDC, &dx9data->_hoops_GRRRR, &_hoops_IRSRA->font_list);
}


/*****************************************************************************
*****************************************************************************
						_hoops_GCIH/_hoops_SCPRH _hoops_IPSRH
*****************************************************************************
*****************************************************************************/


/*
 * _hoops_PGAA
 */
local void
_hoops_CPSRH (Display_Context const * dc) 
{
	DX9Data alter *dx9data = DX9D (dc);

	if (dx9data->_hoops_RIGRR) {
		SelectPalette (dx9data->hDC, dx9data->_hoops_AIGRR, FALSE);
		DeleteObject (dx9data->_hoops_RIGRR);
	}
	ReleaseDC (dx9data->hWND, dx9data->hDC);
	dx9data->hDC = null;
}


/*
 * _hoops_PGAA
 * _hoops_RGR _hoops_API _hoops_HRGR _hoops_IRS _hoops_RSCA _hoops_HAGH _hoops_HII _hoops_RH _hoops_SPSRH _hoops_RHPP _hoops_GGR _hoops_SGS
 * _hoops_SCH _hoops_HRGR _hoops_PIGS _hoops_RAS _hoops_CRCRH->_hoops_GHSRH _hoops_SSCP _hoops_RPII _hoops_SPIP.
 */
local void _hoops_ISPRH (Display_Context const * dc)
{
	DX9Data alter *dx9data = DX9D (dc);
	Display_Context alter * _hoops_RHSRH = (Display_Context alter *) dc;
	D3D_System_Data *d3d_sd = (D3D_System_Data *) _hoops_ARPRH()->d3d_shared_data;
	
	D3DPERF_BeginEvent(0, L"init_dx9data");

	dx9data->dc = dc;
	dx9data->_hoops_HARRR = _hoops_RSARR;

	dx9data->_hoops_AHGRR = false;

	dx9data->_hoops_CSC = (H3DCache*) d3d_sd->_hoops_CSC;
	dx9data->_hoops_SISSA = &d3d_sd->_hoops_SISSA[0];
	dx9data->_hoops_GCSSA = &d3d_sd->_hoops_GCSSA;

	dx9data->_hoops_CSC->_hoops_RRGRR = 0;
	dx9data->_hoops_CSC->_hoops_GSCH[0] = 0;
	dx9data->_hoops_CSC->_hoops_GSCH[1] = 1;

	dx9data->_hoops_SRRRR = dc->options._hoops_SRRRR;
	dx9data->_hoops_RHGRR = true;

	dx9data->_hoops_RHH.mode = false;
	dx9data->_hoops_RHH.flags = 0;
	dx9data->_hoops_RHH._hoops_HPRRR = null;

	dx9data->_hoops_II._hoops_CRPP = new _hoops_RIPRH(dx9data);

	dx9data->_hoops_GIPGR = null;
	dx9data->_hoops_AIPGR = null;
	dx9data->_hoops_RIPGR = false;

	dx9data->_hoops_ICIRH = null;
	dx9data->_hoops_CCIRH = null;

	// _hoops_AHH: _hoops_SAGS _hoops_GCGH _hoops_SPR _hoops_RRI, _hoops_HIH _hoops_SR _hoops_PAH _hoops_RGAR _hoops_HCAAA 15 _hoops_GGR _hoops_RH _hoops_RCC.
	dx9data->_hoops_GAH = H3D_MAX_CUTTING_PLANES;

	dx9data->pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	/* _hoops_SAH _hoops_HHH _hoops_API _hoops_CICRR _hoops_HIS _hoops_SGS 3d_hoops_AHSRH _hoops_PAH _hoops_ACAPA _hoops_CAPR */
	_hoops_RSCSR (dx9data->_hoops_RRCI);
	dx9data->_hoops_GSCR = NEW(_hoops_ICARH)(dx9data);
	dx9data->_hoops_SHAP = H3D_COLOR_ARGB;
	dx9data->_hoops_CSS = H3D_Driver_Shader_Type_DX9;
	dx9data->_hoops_ACCR = 1;
	dx9data->_hoops_RSCH = true;					// _hoops_RRP _hoops_IS _hoops_AA _hoops_PHSRH _hoops_IISRR
	dx9data->_hoops_HSRH = HEC_DX9_DRIVER;
	dx9data->_hoops_RRARR = 0;

	dx9data->_hoops_CP._hoops_HGCGR(&dx9data->_hoops_CIRRR);

	FORCE_CULLING (dx9data, H3DCULL_NONE);
	_hoops_ISPRR (dx9data, false);
	_hoops_SPHRR (dx9data, H3DBLEND_SRCALPHA, H3DBLEND_INVSRCALPHA);
	_hoops_GSPRR (dx9data, false);
	_hoops_GAHRR (dx9data, H3DSTENCILOP_KEEP, H3DSTENCILOP_KEEP, H3DSTENCILOP_KEEP);
	_hoops_IRHRR (dx9data, H3DCMP_ALWAYS);
	_hoops_SGHRR (dx9data, 0x00ff);
	_hoops_IGHRR (dx9data, 0x00ff);
	_hoops_ARHRR (dx9data, 0x00ff);
	_hoops_AHPRR (dx9data, true);
	_hoops_HHPRR (dx9data, H3DMASK_RGBA);
	_hoops_CIAP (dx9data, true);
	_hoops_SSPRR (dx9data, true);
	_hoops_GHPRR (dx9data, false);

	// _hoops_RAP _hoops_HCR _hoops_HH _hoops_PSPA _hoops_IS _hoops_AHPA _hoops_HHSRH _hoops_ARR, _hoops_PSCR _hoops_SR _hoops_PAH _hoops_SRCH _hoops_SCH _hoops_SPHR. _hoops_IPCP _hoops_HHSRH
	// _hoops_RGSR _hoops_GRS _hoops_RGAR _hoops_SHH _hoops_IGI _hoops_CGPR _hoops_RH _hoops_CGGPR _hoops_PAR _hoops_IHSRH _hoops_RGRR _hoops_HRGR _hoops_CISGR.
	D3DCAPS9 _hoops_ACGH;
	dx9data->pDevice->GetDeviceCaps(&_hoops_ACGH);
	for (int i = 0; i < _hoops_CIGP; ++i)
	{
		dx9data->pDevice->SetSamplerState(i, D3DSAMP_MAXANISOTROPY, _hoops_ACGH.MaxAnisotropy);
	}

	_hoops_RHSRH->_hoops_PGCC._hoops_ACPGH = dx9data->_hoops_GAH;
	_hoops_RHSRH->flags |= _hoops_IIPIP;
	dx9data->_hoops_RSRRR = _hoops_CHSRH;
	dx9data->_hoops_PHAI = _hoops_SHSRH;

	dx9data->_hoops_GCSC = XBIT_TEST(dx9data->_hoops_PRARR->_hoops_HHIPP, XBIT_POINT_SPRITES_BASH_ALL);

	if ( !dx9data->_hoops_PR() )
		HE_WARNING (HEC_DX9_DRIVER, HEC_DX9_DRIVER,
				"Failed to initialise dx9data." );

	dx9data->pDevice->SetRenderState (D3DRS_ZENABLE, TRUE);
	HD_Get_Bit_Patterns (_hoops_RHSRH, true);

	D3DPERF_EndEvent();
}


/*
* _hoops_PGAA
* _hoops_APSHR _hoops_GC _hoops_PSPP _hoops_IH _hoops_IRS _hoops_GISRH _hoops_CRS _hoops_ISGRA _hoops_CCPSA
*/
local void _hoops_RISRH(D3D_System_Data alter *d3d_sd)
{
	delete ((_hoops_SRIAP*)d3d_sd->_hoops_RISSA);
	HM_DESTRUCT_SEMAPHORE(d3d_sd->_hoops_HISSA);
	FREE(d3d_sd->_hoops_CSC, H3DCache);
	FREE(d3d_sd, D3D_System_Data);
}


/*
* _hoops_SRAC
*/
local bool start_device (Display_Context alter * dc)
{
#ifdef _DEBUG
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	DX9Data *dx9data = DX9D(dc);

	H3D_TRACE(dx9data, "start_device");

	_hoops_RRPRH alter *_hoops_IRSRA = _hoops_ARPRH ();
	D3D_System_Data alter *d3d_sd = (D3D_System_Data*) _hoops_IRSRA->d3d_shared_data;
	HRESULT _hoops_IIRHP;

	if (!d3d_sd) {
		ALLOC (d3d_sd, D3D_System_Data);
		ZERO_STRUCT (d3d_sd, D3D_System_Data);
		_hoops_IRSRA->d3d_shared_data = d3d_sd;
		d3d_sd->_hoops_RISSA = NEW(_hoops_SRIAP)(1, false);
		HM_CONSTRUCT_SEMAPHORE (d3d_sd->_hoops_HISSA, 1, 0);
		ALLOC(d3d_sd->_hoops_CSC, H3DCache);
		invalidate_cache(d3d_sd);

		d3d_sd->_hoops_SHSSA = Direct3DCreate9(D3D_SDK_VERSION);
		if (d3d_sd->_hoops_SHSSA == null) {
			HE_ERROR (HEC_DX9_DRIVER, HEC_DX9_DRIVER,
				"Could not initialize DX9. You may"
				"want to check that the latest version of"
				"DirectX is correctly installed on your"
				"system.  Also make sure that this program"
				"was compiled with header files that match"
				"the installed DirectX DLLs.");
			return false;
		}
	}
	d3d_sd->ref_count++;

	ZALLOC (dx9data, DX9Data);
	if((dx9data->next = d3d_sd->dx9data_list) != null)
		dx9data->next->backlink = &dx9data->next; 
	d3d_sd->dx9data_list = dx9data;
	dx9data->backlink = &d3d_sd->dx9data_list;

	dx9data->_hoops_SPGRR = false;
	dx9data->H3D_DL_Delete_Task_count = 0;
	dx9data->H3D_DL_Delete_Task_mutex = HI_Create_Mutex();

	/*_hoops_GIPR _hoops_ARP _hoops_HIS _hoops_AISRH _hoops_HRGR _hoops_IGI _hoops_IH _hoops_PISRH _hoops_RIGR*/
	dc->data = (void alter *) dx9data;
	dc->_hoops_RIHGR = (void alter *) dx9data;

	dx9data->_hoops_RRCI = _hoops_APARR::Create(dc->memory_pool);
	dx9data->_hoops_HISRH			= new _hoops_RGRGP();
	dx9data->_hoops_IISRH				= new _hoops_HHRGP();
	dx9data->_hoops_IP				= NEW(H3DShaderHASH)(dx9data);

	dx9data->dc = dc;

	// _hoops_GPIPR _hoops_IRS _hoops_HIGR _hoops_IIGR _hoops_HHSSA _hoops_HRGGP, _hoops_CAPRR _hoops_PPR _hoops_AGSHA. _hoops_IPCP
	// _hoops_CISRH() _hoops_CAPGR _hoops_HRGR _hoops_IGI _hoops_IS _hoops_RHAHA _hoops_SGS _hoops_RGAR _hoops_AGSHA _hoops_SGS
	// _hoops_SISRH _hoops_RH _hoops_HIGGP'_hoops_GRI _hoops_HGSGR _hoops_CHR _hoops_GHSAR.
	dx9data->_hoops_HISRH->_hoops_HPRGP(d3d_sd->_hoops_SHSSA);
	dx9data->_hoops_HISRH->_hoops_CRRGP = _hoops_CPRGP;
	if (FAILED(_hoops_IIRHP = dx9data->_hoops_HISRH->_hoops_IPRGP())) {
		H_SAFE_RELEASE(d3d_sd->_hoops_SHSSA);
		HE_ERROR (HEC_DX9_DRIVER, HEC_DX9_DRIVER,
			"Could not find suitable Direct3D device.");
		return false;
	}

	if (!dc->options._hoops_GCHSR) {
		dx9data->_hoops_PIGRR = _hoops_PPSGR;
		dx9data->_hoops_SHGRR = GetDC (GetDesktopWindow ());
	}
	else if (dc->options._hoops_RGHRP == _hoops_GGHRP || BIT (dc->options._hoops_IRARR, _hoops_GCSRH)) {
		Image alter				*image;

		dx9data->_hoops_PIGRR = DCT_IMAGE;
		dx9data->_hoops_SHGRR = GetDC (GetDesktopWindow ());

		dc->_hoops_PGCC.flags |= _hoops_RHPGH;

		image = (Image alter *)_hoops_RCSSR (dc->_hoops_RIGC, dc->options._hoops_GCHSR);
		if (image == null) {
			HE_ERROR (HEC_DX9_DRIVER, HES_INVALID_KEY,
					"An invalid key was passed to the dx9 driver with USE_WINDOW_IS_IMAGE set."); 
			return false;
		}
		if (image->_hoops_PHGH == 0 ||
			!(image->format == Image_RGBA32 || 
			 image->format == _hoops_HRSRH || 
			 image->format == _hoops_CSGSP || 
			 image->format == _hoops_HHGH || 
			 image->format == _hoops_PCCRH)) {
			HE_ERROR (HEC_DX9_DRIVER, HES_INVALID_KEY,
					"dx9 output image unsupported format."); 
			return false;
		}
		dx9data->_hoops_IHGRR = image;
		_hoops_PRRH (dx9data->_hoops_IHGRR);
	}
	else {
		dx9data->_hoops_PIGRR = _hoops_HPSGR;
		dx9data->hWND = (HWND) dc->options._hoops_GCHSR;
		dx9data->hDC = GetDC (dx9data->hWND);
		dx9data->_hoops_SHGRR = dx9data->hDC;

#ifdef _WIN64
		_hoops_RCSRH (_hoops_ACSRH) =
			(HINSTANCE) GetWindowLongPtr (dx9data->hWND, GWLP_HINSTANCE);
#else
		_hoops_RCSRH (_hoops_ACSRH) =
			(HINSTANCE) GetWindowLong (dx9data->hWND, GWL_HINSTANCE);
#endif

		/* _hoops_GRPHA _hoops_RH _hoops_CSPH _hoops_HIS _hoops_SGS _hoops_PCSRH _hoops_GRS _hoops_IPHR */
		((Display_Context alter *) dc)->current._hoops_RAPGH = (POINTER_SIZED_INT) dx9data->hWND;
		dx9data->_hoops_SHGRR = GetDC (GetDesktopWindow ());
		if (!dc->options._hoops_CRSSP &&
			!BIT (dc->options._hoops_IRARR, _hoops_GCCRH)) {

#ifdef _WIN64
			dx9data->_hoops_GIGRR =
				(WNDPROC) SetWindowLongPtr (dx9data->hWND, GWLP_WNDPROC,
										(POINTER_SIZED_INT) _hoops_AICRH);
#else
			dx9data->_hoops_GIGRR =
				(WNDPROC) SetWindowLong (dx9data->hWND, GWL_WNDPROC,
											(POINTER_SIZED_INT) _hoops_AICRH);
#endif
		}
		else {

#ifndef _hoops_SHRIP
    #ifdef _WIN64
			    dx9data->_hoops_GIGRR =
				    (WNDPROC) SetWindowLongPtr (dx9data->hWND, GWLP_WNDPROC,
											    (POINTER_SIZED_INT) _hoops_IICRH);
    #else
			    dx9data->_hoops_GIGRR =
				    (WNDPROC) SetWindowLong (dx9data->hWND, GWL_WNDPROC,
											    (POINTER_SIZED_INT) _hoops_IICRH);
    #endif
#endif
#ifdef _hoops_SHRIP
        dx9data->_hoops_GIGRR = 0;
#endif

		}
	}

	/* _hoops_PAIA - _hoops_RCSC _hoops_RHAP _hoops_AAPA _hoops_PAPA _hoops_HHGC _hoops_RH _hoops_RHPP _hoops_IS _hoops_AA _hoops_RGR? _hoops_GHAP _hoops_GA'_hoops_RA _hoops_ACPA*/
	HD_Get_Bit_Patterns (dc, true);

	((_hoops_GGAGR *) dc->_hoops_GHRI)->_hoops_CAIAP = _hoops_ARIAP;
	return true;

} //_hoops_RSGR '_hoops_HSPP _hoops_SISS'



void _hoops_SIARR(H3DData alter *h3ddata) {
	_hoops_RRPRH alter *_hoops_IRSRA = _hoops_ARPRH ();
	D3D_System_Data alter *d3d_sd = (D3D_System_Data*) _hoops_IRSRA->d3d_shared_data;
	DX9Data alter * dx9data = (DX9Data alter *)h3ddata;

	// _hoops_HCSRH _hoops_ICSRH _hoops_RGCA _hoops_CCSRH _hoops_HGAPR _hoops_SCSRH _hoops_GSSRH _hoops_RSSRH
	_hoops_APAI (dx9data->H3D_DL_Delete_Task_mutex);

	H_SAFE_RELEASE(dx9data->_hoops_IGCRH);
	if (d3d_sd->ref_count <= 1) {
		NEW(DX9DeleteDeviceTask)(d3d_sd);
		HM_WAIT_SEMAPHORE(d3d_sd->_hoops_HISSA);
	}

	HI_Destroy_Mutex(dx9data->H3D_DL_Delete_Task_mutex);

	if((*dx9data->backlink = dx9data->next) != null)
		dx9data->next->backlink = dx9data->backlink;
	FREE (dx9data, DX9Data);

	d3d_sd->ref_count--;
	if (d3d_sd->ref_count < 1) {
		H_SAFE_RELEASE(d3d_sd->_hoops_SHSSA);
		_hoops_RISRH(d3d_sd);
		_hoops_IRSRA->d3d_shared_data = null;
	}
}

/*
* _hoops_SRAC
*/
local void stop_device (Display_Context alter * dc)
{
	DX9Data alter *dx9data = DX9D (dc);

	/* _hoops_RCSH _hoops_GII _hoops_ASSRH _hoops_SHCA'_hoops_GRI _hoops_SR _hoops_SPIP */
	switch (dx9data->_hoops_PIGRR) {

		case _hoops_PPSGR:
		case DCT_IMAGE:
			dx9data->_hoops_PIGRR = _hoops_APSGR;
			ReleaseDC (GetDesktopWindow (), dx9data->_hoops_SHGRR);
			if (dx9data->_hoops_IHGRR) {
				_hoops_HPRH (dx9data->_hoops_IHGRR);
			}
			break;

		case _hoops_HPSGR:
			/* _hoops_IPPRA _hoops_RPPS _hoops_PSSRH _hoops_RPP _hoops_RGCI _hoops_ARP */

            if (dx9data->_hoops_GIGRR)
            {
                #ifdef _WIN64
			                SetWindowLongPtr (dx9data->hWND, GWLP_WNDPROC,
				                (POINTER_SIZED_INT) dx9data->_hoops_GIGRR);
                #else
			                SetWindowLong (dx9data->hWND, GWL_WNDPROC,
				                (POINTER_SIZED_INT) dx9data->_hoops_GIGRR);
                #endif
            }
 			dx9data->_hoops_GIGRR = null;
			ReleaseDC (GetDesktopWindow (), dx9data->_hoops_SHGRR);
			_hoops_CPSRH (dc);
			break;
	}

	/*_hoops_RGR _hoops_CRRHP _hoops_RH _hoops_IRGH _hoops_HRCSR _hoops_HIGR*/
	_hoops_SGRRR * _hoops_HSSRH = dx9data->_hoops_GRRRR;
	_hoops_SGRRR * _hoops_ISSRH;

	while (_hoops_HSSRH) {

		_hoops_ISSRH = _hoops_HSSRH->next;

		FREE_ARRAY (_hoops_HSSRH->name, _hoops_SSGR(_hoops_HSSRH->name) + 1, char);

		if (_hoops_HSSRH->specific)
			FREE_ARRAY (_hoops_HSSRH->specific, _hoops_SSGR(_hoops_HSSRH->specific) + 1, char);

		FREE (_hoops_HSSRH, _hoops_SGRRR);

		_hoops_HSSRH = _hoops_ISSRH;
	}

	dx9data->_hoops_GRRRR = 0;

	// _hoops_AHH: _hoops_HHIGR'_hoops_GRI _hoops_SSRR _hoops_IH _hoops_RH _hoops_SISS _hoops_IS _hoops_SHH _hoops_CSSRH _hoops_ARPP _hoops_SSSRH, _hoops_GGR _hoops_PGAP _hoops_AGIR
	// _hoops_RGR _hoops_SHPP _hoops_GGGAH (_hoops_RGGAH, _hoops_ASSP'_hoops_RA _hoops_AGCGR _hoops_PPGS). _hoops_AGGAH _hoops_SGS _hoops_HPP _hoops_PGGAH _hoops_ARI.
	if ( dx9data->post && dx9data->_hoops_II.depth_texture )
		dx9data->post->_hoops_HAAP( &dx9data->_hoops_II.depth_texture );

	_hoops_ACIRH (dc);

	_hoops_HP (dx9data->post);
	_hoops_HP (dx9data->_hoops_HISRH);
	_hoops_HP (dx9data->_hoops_IISRH);
	_hoops_HP (dx9data->_hoops_IP);

	dx9data->_hoops_RRCI = null;

	if (dx9data->_hoops_PRARR)
		HI_Free_Driver_Config(dx9data->_hoops_PRARR);

	/*_hoops_GIPR _hoops_ARP _hoops_HIS _hoops_AISRH _hoops_HRGR _hoops_IGI _hoops_IH _hoops_PISRH _hoops_RIGR*/
	dc->data = null;
	dc->_hoops_RIHGR = null;

	_hoops_CAAI (dx9data->H3D_DL_Delete_Task_mutex);
	if (dx9data->H3D_DL_Delete_Task_count > 0) {
		dx9data->_hoops_SPGRR = true;
		_hoops_APAI (dx9data->H3D_DL_Delete_Task_mutex);
	}
	else
		_hoops_SIARR((H3DData alter *)dx9data);

} //_hoops_RSGR '_hoops_RRS _hoops_SISS'


/*****************************************************************************
*****************************************************************************
						_hoops_RRIA _hoops_RPGGP _hoops_SICAR
*****************************************************************************
*****************************************************************************/

/*
* _hoops_PGAA
*/
local void _hoops_HGGAH (Display_Context alter * dc)
{
	DX9Data alter *dx9data = DX9D (dc);
	RECT _hoops_PCRSP;
	RECT _hoops_IGGAH;
	POINT _hoops_CGGAH;
	HWND _hoops_SGGAH;

	/*
	* _hoops_PS _hoops_RRP _hoops_IS _hoops_GRAS _hoops_RH _hoops_RPPS _hoops_PHGSP _hoops_PPR _hoops_GPAA - _hoops_SR _hoops_HS _hoops_IS
	* _hoops_RGIC _hoops_AHCA _hoops_PPGC _hoops_IRS _hoops_CIAGR _hoops_CCPAR - _hoops_HIS _hoops_IS _hoops_IRHH _hoops_SCH _hoops_RCAC _hoops_SR
	* _hoops_CHR _hoops_CPIC _hoops_IS _hoops_HGCR _hoops_RH _hoops_RPPS _hoops_GRGAH (_hoops_CRRPR _hoops_HCR _hoops_RGSHA _hoops_HIAHR
	* _hoops_PPR _hoops_GPAA) _hoops_PPR _hoops_RH _hoops_RPRGR _hoops_CCAC (_hoops_SAHR _hoops_RH _hoops_HAICP _hoops_CCAC _hoops_IIGR _hoops_RH
	* _hoops_SHPR) - _hoops_SR _hoops_GRS _hoops_GACC _hoops_SGHHR _hoops_IS _hoops_HGCR _hoops_RH _hoops_RRGAH _hoops_HCGR _hoops_SPCC _hoops_PPR
	* _hoops_RH _hoops_ARGAH _hoops_PRGAH _hoops_HPHS
	* _hoops_IRSC _hoops_AGCR _hoops_HRGAH _hoops_HSH _hoops_GHAP _hoops_CGH _hoops_SHH _hoops_SHSS _hoops_IS _hoops_CAHA _hoops_CPS _hoops_GGSR
	*/

	_hoops_SGGAH = dx9data->hWND;

	if (_hoops_SGGAH == null) {
		/* _hoops_AGAH _hoops_IPAC _hoops_GGSR _hoops_RH _hoops_GHARR _hoops_ARPP _hoops_SGP _hoops_RPPS */
		_hoops_SGGAH = GetDesktopWindow ();
	}

	GetWindowRect (_hoops_SGGAH, &_hoops_PCRSP);
	GetClientRect (_hoops_SGGAH, &_hoops_IGGAH);

	_hoops_CGGAH.x = _hoops_IGGAH.left;
	_hoops_CGGAH.y = _hoops_IGGAH.bottom;
	ClientToScreen (_hoops_SGGAH, &_hoops_CGGAH);
	_hoops_IGGAH.left = _hoops_CGGAH.x;
	_hoops_IGGAH.bottom = _hoops_CGGAH.y;

	_hoops_CGGAH.x = _hoops_IGGAH.right;
	_hoops_CGGAH.y = _hoops_IGGAH.top;
	ClientToScreen (_hoops_SGGAH, &_hoops_CGGAH);
	_hoops_IGGAH.right = _hoops_CGGAH.x;
	_hoops_IGGAH.top = _hoops_CGGAH.y;

	/*
	* _hoops_IPCP _hoops_IRGAH _hoops_PAH _hoops_HS _hoops_ARGAH _hoops_CRGAH, _hoops_IRS _hoops_SRGAH, _hoops_IRS _hoops_IRGAH, _hoops_PPR _hoops_SPR _hoops_IIGR
	* _hoops_HRSP _hoops_CSSC _hoops_IIGR _hoops_GPAA
	*/

	dx9data->_hoops_HCGRR =
		dx9data->_hoops_RCGRR = dx9data->_hoops_ACGRR =
		dx9data->_hoops_PCGRR = 0;

	if (dx9data->hWND == null) {
	/* _hoops_AGAH _hoops_GRS _hoops_SHH _hoops_GRP _hoops_RGR _hoops_HPHS _hoops_IS _hoops_ARPR _hoops_RH _hoops_SHIR
		_hoops_RPPS _hoops_HIS _hoops_SR _hoops_PIHA _hoops_PSIIR _hoops_SCH _hoops_IS _hoops_ASSS _hoops_IH _hoops_RH _hoops_HPRGR _hoops_GPAA */
		/* _hoops_GAGAH _hoops_RAGAH _hoops_PPR _hoops_GPAA */
		if (dc->options._hoops_AASSP) {
			dx9data->_hoops_ACGRR =
				dx9data->_hoops_PCGRR = GetSystemMetrics (SM_CXFRAME);
			dx9data->_hoops_RCGRR = GetSystemMetrics (SM_CYFRAME);
		}
		else {
			dx9data->_hoops_ACGRR =
				dx9data->_hoops_PCGRR = GetSystemMetrics (SM_CXBORDER);
			dx9data->_hoops_RCGRR = GetSystemMetrics (SM_CYBORDER);
		}
		dx9data->_hoops_HCGRR = dx9data->_hoops_RCGRR +
			GetSystemMetrics (SM_CYCAPTION) - 1;
	}
	else {
		/* _hoops_PSIH _hoops_GPAA _hoops_IIGR _hoops_APRS _hoops_RPPS */
		dx9data->_hoops_ACGRR = _hoops_PCRSP.right - _hoops_IGGAH.right;
		dx9data->_hoops_PCGRR = _hoops_IGGAH.left - _hoops_PCRSP.left;
		dx9data->_hoops_HCGRR = _hoops_IGGAH.top - _hoops_PCRSP.top;
		dx9data->_hoops_RCGRR = _hoops_PCRSP.bottom - _hoops_IGGAH.bottom;
	}


	dc->current.extent.left = (float) _hoops_PCRSP.left;
	dc->current.extent.right = (float) _hoops_PCRSP.right - 1;
	dc->current.extent.bottom = (float) (dx9data->_hoops_CCGRR - (_hoops_PCRSP.bottom - 1));
	dc->current.extent.top = (float) (dx9data->_hoops_CCGRR - _hoops_PCRSP.top);
}


/*
 * _hoops_SRAC
 */
local void get_physical_info (Display_Context alter * dc)
{
	DX9Data alter *dx9data = DX9D (dc);
	HDC hDC;

	if (dx9data->hDC == 0)
		hDC = dx9data->_hoops_SHGRR;
	else
		hDC = dx9data->hDC;

	dc->_hoops_PGCC.flags |= _hoops_PPPGH;

	/* _hoops_PS _hoops_AA _hoops_HAR _hoops_AA _hoops_IPPSR _hoops_PCRR */
	dc->_hoops_PGCC._hoops_PIPGH = false;

	if (dx9data->_hoops_PIGRR== DCT_IMAGE) {
		dc->_hoops_PGCC._hoops_PRPSR.x = dx9data->_hoops_IHGRR->width;
		dc->_hoops_PGCC._hoops_PRPSR.y = dx9data->_hoops_IHGRR->height;
		dc->_hoops_PGCC.size.x = dc->_hoops_PGCC._hoops_PRPSR.x * (2.54f /72.0f);
		dc->_hoops_PGCC.size.y = dc->_hoops_PGCC._hoops_PRPSR.y * (2.54f /72.0f);
	}
	else {
		dc->_hoops_PGCC._hoops_PRPSR.x = GetDeviceCaps (hDC, HORZRES);
		dc->_hoops_PGCC._hoops_PRPSR.y = GetDeviceCaps (hDC, VERTRES);
		
		dc->_hoops_PGCC.size.x = GetDeviceCaps (hDC, HORZSIZE) / 10.0f;

		if (dc->_hoops_PGCC.size.x == 0.0f) dc->_hoops_PGCC.size.x = 30.0f;
		
		/* _hoops_HR _hoops_IGAA _hoops_GGSP _hoops_PPR _hoops_AIR _hoops_CHR _hoops_RRAA */
		dc->_hoops_PGCC.size.y = (float) dc->_hoops_PGCC._hoops_PRPSR.y /
			(float) dc->_hoops_PGCC._hoops_PRPSR.x * dc->_hoops_PGCC.size.x;
 
		dx9data->yfudge = dx9data->_hoops_CCGRR = dc->_hoops_PGCC._hoops_PRPSR.y - 1;	

		_hoops_HGGAH (dc);
	}

	/* _hoops_PPSI _hoops_GGR _hoops_GHAR _hoops_RGGHR _hoops_ARI..._hoops_SAHR _hoops_GGR _hoops_AGIR _hoops_RH _hoops_RPGP _hoops_RPPS _hoops_ISHS */
	dc->_hoops_PGCC._hoops_PCHSR = 256;
	dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;
	dc->_hoops_PGCC.driver_type = "Direct3D";
  	dc->_hoops_PGCC._hoops_SCHSR = "$Revision: 1.1016.2.1 $";
 	dc->_hoops_PGCC._hoops_ICHSR = "frame buffer";
 	dc->_hoops_PGCC._hoops_RCPGH = "mouse";

	/* _hoops_IHH _hoops_AAARR _hoops_ARP _hoops_IS _hoops_RCPP _hoops_CCGR _hoops_SR _hoops_CACH _hoops_IRS _hoops_APIP _hoops_GGSC */
	dc->_hoops_PGCC.flags &= ~_hoops_SGICP;
	dc->_hoops_PGCC.flags &= ~_hoops_GPPGH;

	dc->_hoops_PGCC.flags &= ~_hoops_GGISR;

	//_hoops_CSPH->_hoops_CPHSR._hoops_AAGAH = _hoops_PAGAH;
	dc->_hoops_PGCC._hoops_CHHSR = _hoops_ACPGA;

	/* _hoops_IHH _hoops_AAARR */
	dc->_hoops_PGCC.flags |= _hoops_SGICP;
	dc->_hoops_PGCC.flags |= _hoops_GPPGH;

	dc->_hoops_PGCC._hoops_HGCC = 15;
	dc->_hoops_PGCC._hoops_ACPGH = 15; 

	dc->_hoops_PGCC.flags &= ~_hoops_GIHSR;
	dc->_hoops_PGCC._hoops_IIPGH[0] = QMoves_Accumulation;
	dc->_hoops_PGCC._hoops_IIPGH[1] = QMoves_Spriting;
	dc->_hoops_PGCC.flags |= _hoops_PAGIP;

	if (GetSystemMetrics (SM_MOUSEPRESENT) != 0)
		dc->_hoops_PGCC.flags |= _hoops_RSHSR;
	else
		dc->_hoops_PGCC.flags &= ~_hoops_RSHSR;

	dc->_hoops_PGCC._hoops_ASHSR = GetSystemMetrics (SM_CMOUSEBUTTONS);

	dc->_hoops_PGCC._hoops_HASHP = dx9data->_hoops_IGARR = 24; //_hoops_SRSA _hoops_ACIPR _hoops_RRGR
	dc->_hoops_PGCC._hoops_PASHP = dx9data->_hoops_CGARR = (1UL << dx9data->_hoops_IGARR) - 1;
	if (dc->_hoops_PGCC._hoops_HASHP > 0) 
		dc->flags &= ~_hoops_AASHP;
	else 
		dc->flags |= _hoops_AASHP;
	dx9data->_hoops_ICGRR = (float)(1.0/dx9data->_hoops_CGARR);
	dc->_hoops_PGCC.flags |= _hoops_SPPGH;
	dc->_hoops_PGCC.flags |= _hoops_CPPGH;
	dc->_hoops_PGCC.flags |= _hoops_PHPGH; //_hoops_IHPPP _hoops_PSAP _hoops_SPHR _hoops_RPP _hoops_CGRPR _hoops_HAGAH
	dc->_hoops_PGCC.flags |= _hoops_PSSHP;
	dc->_hoops_PGCC.flags |= _hoops_ASSHP;
	dc->_hoops_PGCC.flags |= _hoops_GHPGH;
	dc->_hoops_PGCC.flags |= _hoops_ISSHP;
	//_hoops_CSPH->_hoops_SGI |= _hoops_IAGAH;

	

	dx9data->_hoops_HGARR = true;
	dc->_hoops_PGCC._hoops_AHAGH = _hoops_APRRR;

	if (dc->options._hoops_RGHRP == _hoops_GGHRP || BIT (dc->options._hoops_IRARR, _hoops_GCSRH))
		dc->_hoops_PGCC.flags |= _hoops_RHPGH;

} //_hoops_RSGR '_hoops_HGCR _hoops_CPHSR _hoops_SIHC'


/*
 * _hoops_SRAC
 */
local void get_current_info (Display_Context alter * dc)
{
	DX9Data alter *dx9data = DX9D (dc);
	HDC hDC;

	if (dx9data->hDC == 0)
		hDC = dx9data->_hoops_SHGRR;
	else
		hDC = dx9data->hDC;

	if (dc->options._hoops_GCHSR != 0) {
		dc->options._hoops_RASSP = true;
		dc->options._hoops_AASSP = true;
		dc->options._hoops_PASSP = true;
		dc->options._hoops_HPHRP = false;
	}
	dc->current._hoops_AAPSR = 1L << 24;
	dc->current._hoops_APASR = 0;

	_hoops_HGGAH (dc);

	if (dc->options.border) {
		HD_Allow_For_Border (dc, dx9data->_hoops_ACGRR,
			dx9data->_hoops_PCGRR, dx9data->_hoops_RCGRR,
			dx9data->_hoops_HCGRR);
	}
}


/*
 * _hoops_PGAA
 */
bool _hoops_CAGAH(
		Display_Context alter * dc, 
		bool _hoops_SAGAH, 
		bool _hoops_GPGAH)
{
	DX9Data alter *dx9data = DX9D (dc);
	_hoops_RRPRH alter *_hoops_IRSRA = _hoops_ARPRH ();
	D3D_System_Data alter *d3d_sd = (D3D_System_Data*) _hoops_IRSRA->d3d_shared_data;

	H3D_TRACE(dx9data, "find best windowed mode");

	// _hoops_SIPR _hoops_AIRI _hoops_CCH _hoops_IIGR _hoops_PRRPA _hoops_APGGP (_hoops_PGAP _hoops_HRGR _hoops_SHHA _hoops_IS _hoops_SHH _hoops_CAS _hoops_RH _hoops_RPPS
	// _hoops_GRS _hoops_RPGAH)
	D3DDISPLAYMODE _hoops_APGAH;
	d3d_sd->_hoops_SHSSA->GetAdapterDisplayMode(0, &_hoops_APGAH);

	D3DAdapterInfo* pBestAdapterInfo = null;
	D3DDeviceInfo* _hoops_PPGAH = null;
	D3DDeviceCombo* _hoops_HPGAH = null;

	for (;;) {
		for (UINT _hoops_CHRHP = 0; _hoops_CHRHP < dx9data->_hoops_HISRH->_hoops_PRRGP->Count(); _hoops_CHRHP++) {
			D3DAdapterInfo* _hoops_PGRGP = (D3DAdapterInfo*)dx9data->_hoops_HISRH->_hoops_PRRGP->_hoops_GRGGP(_hoops_CHRHP);
			for (UINT _hoops_HHRHP = 0; _hoops_HHRHP < _hoops_PGRGP->_hoops_SPGGP->Count(); _hoops_HHRHP++) {
				D3DDeviceInfo* _hoops_CGRGP = (D3DDeviceInfo*)_hoops_PGRGP->_hoops_SPGGP->_hoops_GRGGP(_hoops_HHRHP);
				if (_hoops_SAGAH && _hoops_CGRGP->_hoops_PHGGP != D3DDEVTYPE_HAL)
					continue;
				if (_hoops_GPGAH && _hoops_CGRGP->_hoops_PHGGP != D3DDEVTYPE_REF)
					continue;
				for (UINT _hoops_IHRHP = 0; _hoops_IHRHP < _hoops_CGRGP->_hoops_HHGGP->Count(); _hoops_IHRHP++) {
					D3DDeviceCombo* _hoops_GRRGP = (D3DDeviceCombo*)_hoops_CGRGP->_hoops_HHGGP->_hoops_GRGGP(_hoops_IHRHP);
					bool _hoops_IPGAH = (_hoops_GRRGP->BackBufferFormat == _hoops_GRRGP->_hoops_IIGGP);
					if (!_hoops_GRRGP->_hoops_CIGGP)
						continue;
					if (_hoops_GRRGP->_hoops_IIGGP != _hoops_APGAH.Format)
						continue;
					// _hoops_CGP _hoops_SR _hoops_SIPGR'_hoops_RA _hoops_GSGI _hoops_IRS _hoops_PIGGP _hoops_CGAHP _hoops_GAPR, _hoops_PAR _hoops_RPP _hoops_RGR _hoops_ARP
					// _hoops_HRGR _hoops_GIH (_hoops_PGGA _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_CPGAH, _hoops_PPR/_hoops_PAR _hoops_PGGA _hoops_AGHS _hoops_PSSP _hoops_GIH),
					// _hoops_ASAC _hoops_SCH
					if (_hoops_HPGAH == null ||
						_hoops_HPGAH->_hoops_PHGGP != D3DDEVTYPE_HAL && _hoops_GRRGP->_hoops_PHGGP == D3DDEVTYPE_HAL ||
						_hoops_GRRGP->_hoops_PHGGP == D3DDEVTYPE_HAL && _hoops_IPGAH) {
							pBestAdapterInfo = _hoops_PGRGP;
							_hoops_PPGAH = _hoops_CGRGP;
							_hoops_HPGAH = _hoops_GRRGP;
							if (_hoops_GRRGP->_hoops_PHGGP == D3DDEVTYPE_HAL && _hoops_IPGAH) {
								if (_hoops_PPGAH->Caps.PixelShaderVersion < D3DPS_VERSION(2,0)) {
									HE_ERROR(HEC_DX9_DRIVER, HEC_DX9_DRIVER,
										"DX9 driver requires shader model 2.0 or above. Disabling hardware acceleration.");
									_hoops_HPGAH = null;
									break;
								}
								// _hoops_HGI _hoops_AISIR _hoops_SISS _hoops_SPACA _hoops_APSH _hoops_SPGAH -- _hoops_IRAA _hoops_SCH
								goto _hoops_GHGAH;
							}
							// _hoops_HHPC _hoops_GRHP _hoops_HCHAR _hoops_IH _hoops_IRS _hoops_GIH _hoops_AISIR _hoops_SISS _hoops_SPACA
					}
				}
			}
		}

		if (_hoops_GPGAH)
			break;
		_hoops_GPGAH = true;
	}
_hoops_GHGAH:
	if (_hoops_HPGAH == null)
		return false;

	dx9data->_hoops_IISRH->_hoops_IHRGP = pBestAdapterInfo;
	dx9data->_hoops_IISRH->_hoops_CHRGP = _hoops_PPGAH;
	dx9data->_hoops_IISRH->_hoops_SHRGP = _hoops_HPGAH;
	dx9data->_hoops_IISRH->_hoops_CIGGP = true;
	dx9data->_hoops_IISRH->_hoops_GIRGP = _hoops_APGAH;
	//_hoops_RHGAH	  _hoops_CRCRH->_hoops_HRP->_hoops_AHGAH = _hoops_PHGAH._hoops_RPHR - _hoops_PHGAH._hoops_RAAP;
	//	  _hoops_CRCRH->_hoops_HRP->_hoops_HHGAH = _hoops_PHGAH._hoops_PRPC - _hoops_PHGAH._hoops_SCIA;
	if (dx9data->_hoops_HISRH->_hoops_IARGP)
		dx9data->_hoops_IISRH->_hoops_AIRGP = *(D3DFORMAT*)_hoops_HPGAH->_hoops_SIGGP->_hoops_GRGGP(0);
	dx9data->_hoops_IISRH->_hoops_PIRGP = *(D3DMULTISAMPLE_TYPE*)_hoops_HPGAH->_hoops_RCGGP->_hoops_GRGGP(0);
	dx9data->_hoops_IISRH->_hoops_HIRGP = 0;
	if (_hoops_PPGAH->Caps.VertexShaderVersion < D3DVS_VERSION(2,0))
		dx9data->_hoops_IISRH->_hoops_IIRGP = _hoops_HAGGP;
	else
		dx9data->_hoops_IISRH->_hoops_IIRGP = *(_hoops_PAGGP*)_hoops_HPGAH->_hoops_SCGGP->_hoops_GRGGP(0);
	dx9data->_hoops_IISRH->_hoops_CIRGP = *(UINT*)_hoops_HPGAH->_hoops_RSGGP->_hoops_GRGGP(0);
	return true;
}



static const char * d3d_software_string = "DX9_Software";
static const char * d3d_hardware_string = "DX9_Hardware";

/*
 * _hoops_PGAA
 */
local bool _hoops_IHGAH (D3D_System_Data *d3d_sd, D3DFORMAT format)
{
	return SUCCEEDED(d3d_sd->_hoops_SHSSA->CheckDeviceFormat( D3DADAPTER_DEFAULT,
								  D3DDEVTYPE_HAL,
								  D3DFMT_X8R8G8B8,
								  0,
								  D3DRTYPE_TEXTURE,
								  format));
}

/*
 * _hoops_PGAA
 */
local void identify_renderer (Display_Context alter * dc)
{
	DX9Data alter *dx9data = DX9D (dc);
	_hoops_RRPRH alter *_hoops_IRSRA = _hoops_ARPRH ();
	D3D_System_Data alter *d3d_sd = (D3D_System_Data*) _hoops_IRSRA->d3d_shared_data;

	D3DPERF_BeginEvent(0, L"identify_renderer");

	HRESULT _hoops_IIRHP;

	D3DDeviceInfo* _hoops_CGRGP = dx9data->_hoops_IISRH->_hoops_RSRGP();

	dx9data->_hoops_HCARH.Windowed				= true;
	dx9data->_hoops_HCARH.BackBufferCount		= 1;
	dx9data->_hoops_HCARH.MultiSampleType		= dx9data->_hoops_IISRH->_hoops_SSRGP();
	dx9data->_hoops_HCARH.MultiSampleQuality		= dx9data->_hoops_IISRH->_hoops_RGAGP();
	dx9data->_hoops_HCARH.SwapEffect				= D3DSWAPEFFECT_COPY;
	dx9data->_hoops_HCARH.hDeviceWindow			= dx9data->hWND;

	if (dx9data->_hoops_HISRH->_hoops_IARGP) {
		dx9data->_hoops_HCARH.Flags				= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	}
	else {
		dx9data->_hoops_HCARH.Flags				= 0;
	}

	dx9data->_hoops_HCARH.BackBufferWidth  = dx9data->_hoops_IIGRR.right - dx9data->_hoops_IIGRR.left;
	dx9data->_hoops_HCARH.BackBufferHeight = dx9data->_hoops_IIGRR.bottom - dx9data->_hoops_IIGRR.top;
	dx9data->_hoops_HCARH.BackBufferFormat = D3DFMT_A8R8G8B8; //_hoops_CRCRH->_hoops_HRP->_hoops_CHGAH()->_hoops_SHGAH;
	dx9data->_hoops_HCARH.FullScreen_RefreshRateInHz = 0;
	dx9data->_hoops_HCARH.PresentationInterval = dx9data->_hoops_IISRH->_hoops_IGAGP();

	if (_hoops_CGRGP->Caps.PrimitiveMiscCaps & D3DPMISCCAPS_NULLREFERENCE) {
		// _hoops_GIGAH _hoops_IPSP _hoops_AHCA _hoops_IRAP _hoops_PAGGR _hoops_SISS _hoops_SGS _hoops_PAH'_hoops_RA _hoops_SRGS _hoops_PA
		HE_ERROR (HEC_DX9_DRIVER, HEC_DX9_DRIVER,
			"D3DAPPERR_NULLREFDEVICE: DX9 Driver error");
		HD_Kill_Driver (dc);
		return;
	}

	DWORD _hoops_RIGAH;
	if (dx9data->_hoops_IISRH->_hoops_PGAGP() == _hoops_HAGGP)
		_hoops_RIGAH = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	else if (dx9data->_hoops_IISRH->_hoops_PGAGP() == _hoops_IAGGP)
		_hoops_RIGAH = D3DCREATE_MIXED_VERTEXPROCESSING;
	else if (dx9data->_hoops_IISRH->_hoops_PGAGP() == _hoops_CAGGP)
		_hoops_RIGAH = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else if (dx9data->_hoops_IISRH->_hoops_PGAGP() == _hoops_SAGGP)
		_hoops_RIGAH = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE;
	else
		_hoops_RIGAH = 0; // _hoops_SIGP: _hoops_RSRHR _hoops_GSASR
	_hoops_RIGAH |= D3DCREATE_FPU_PRESERVE;
#ifdef H3D_DL_DELETE_TASK
	_hoops_RIGAH |= D3DCREATE_MULTITHREADED;
#endif

	// _hoops_SGCH _hoops_IH _hoops_RH _hoops_AGRR _hoops_HCH _hoops_HH _hoops_AGHS _hoops_SR _hoops_HHS _hoops_SGH
	D3DFORMAT const _hoops_AIGAH[] = 
	{
		D3DFMT_D24X8,
		D3DFMT_D24S8,
	};

	// _hoops_SGCH _hoops_IH _hoops_RH _hoops_SRS _hoops_PIS _hoops_RPCC.
	for ( int i = 0; i < sizeof(_hoops_AIGAH)/sizeof(D3DFORMAT) && !dx9data->_hoops_SRP; ++i )
	{
		// _hoops_ARGH _hoops_IH _hoops_PIGAH _hoops_HH _hoops_GCGH
		dx9data->_hoops_SRP = SUCCEEDED(d3d_sd->_hoops_SHSSA->CheckDeviceFormat(
			// _hoops_HAPPR
			dx9data->_hoops_IISRH->_hoops_PPGGP(), _hoops_CGRGP->_hoops_PHGGP, D3DFMT_X8R8G8B8, 
			// _hoops_HIGAH
			D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_TEXTURE, _hoops_AIGAH[i]));

		// _hoops_CGP _hoops_SCH _hoops_AICS, _hoops_PCSA _hoops_SCH.
		if ( dx9data->_hoops_SRP )
			dx9data->_hoops_IIGAH = _hoops_AIGAH[i];
	}

	// _hoops_ARGH _hoops_IH _hoops_CIGAH _hoops_SRGS-_hoops_IS-_hoops_HH _hoops_GCGH
	dx9data->_hoops_GAP = SUCCEEDED(d3d_sd->_hoops_SHSSA->CheckDeviceFormat(
		// _hoops_HAPPR
		dx9data->_hoops_IISRH->_hoops_PPGGP(), _hoops_CGRGP->_hoops_PHGGP, D3DFMT_X8R8G8B8, 
		// _hoops_HIGAH
		D3DUSAGE_RENDERTARGET, D3DRTYPE_TEXTURE, D3DFMT_R32F));

	dx9data->_hoops_HRRH = _hoops_IHGAH(d3d_sd, D3DFMT_DXT1);
	dx9data->_hoops_CAARR = _hoops_IHGAH(d3d_sd, D3DFMT_DXT3);
	dx9data->_hoops_SAARR = _hoops_IHGAH(d3d_sd, D3DFMT_DXT5);
	dx9data->_hoops_CHGH = _hoops_IHGAH(d3d_sd, D3DFMT_R8G8B8);
	dx9data->_hoops_GPARR = _hoops_IHGAH(d3d_sd, D3DFMT_L8);


	// _hoops_AHH: _hoops_GPRHP _hoops_GRGR _hoops_CCGR _hoops_SR _hoops_PAH _hoops_CPSSR _hoops_RH _hoops_CGHI _hoops_CIAGR _hoops_AHRPA. (_hoops_SIGAH _hoops_APRP _hoops_RGCH _hoops_CGPR _hoops_HHACR _hoops_CIRAR _hoops_IGIR _hoops_GPP _hoops_GCGAH, _hoops_RAPA _hoops_RGGAH _hoops_GPP _hoops_RCGAH).
	dx9data->_hoops_SRP = false;

	// _hoops_AHH: _hoops_HSRR _hoops_ACGAH _hoops_RGPP _hoops_PHAP _hoops_HCH _hoops_IIPGA _hoops_GPAC
	// _hoops_CRCRH->_hoops_ARAP = _hoops_RCPP;

	// _hoops_GRSH _hoops_AHPH _hoops_PCGAH (_hoops_GPGR _hoops_SRGS _hoops_HCSS) _hoops_APP?
	dx9data->_hoops_GRAP = _hoops_CGRGP->Caps.NumSimultaneousRTs;

	// _hoops_GRSH _hoops_CHPP _hoops_PAH _hoops_PPSR _hoops_IPSC _hoops_SHH?
	dx9data->_hoops_IHSC = (_hoops_CGRGP->Caps.MaxPointSize > 1) ? _hoops_CGRGP->Caps.MaxPointSize : 0;

	// _hoops_AHH: _hoops_HCGAH _hoops_IH _hoops_ICGAH _hoops_IIGR _hoops_AHAAR _hoops_RIRR - _hoops_PCPI _hoops_GPIA _hoops_IIPGA _hoops_CRAA.
	//_hoops_CRCRH->_hoops_CCGAH = 0;

	// _hoops_AHH: _hoops_HCGAH _hoops_IH _hoops_ICGAH _hoops_IIGR _hoops_AHAAR _hoops_RIRR - _hoops_SCGAH _hoops_PGCR-_hoops_RIH _hoops_HCH _hoops_ICH.
	//_hoops_CRCRH->_hoops_GSGAH = 1;

	// _hoops_PS _hoops_PAH _hoops_SHR _hoops_RCAR _hoops_ARCR _hoops_CR _hoops_SR _hoops_GCGH _hoops_RGPP _hoops_ACAR
	dc->flags |= _hoops_SRAGH;

	// _hoops_RSGAH _hoops_HRGR _hoops_IRS _hoops_GGPR _hoops_ASGAH 3 _hoops_IRGHA
	dx9data->_hoops_SGARR = _hoops_CGRGP->Caps.VertexShaderVersion >= D3DVS_VERSION(3,0);

	// _hoops_HCGAH _hoops_IH _hoops_HISRA _hoops_PPR _hoops_ICGAH _hoops_IIGR _hoops_GSIA _hoops_RHPP _hoops_PAAA
	//_hoops_PSGAH = _hoops_HSGAH;
	//_hoops_ISGAH->_hoops_CSGAH = _hoops_SSGAH;

	//_hoops_RPP _hoops_RH _hoops_RPPS _hoops_CCAC _hoops_HRGR 0, _hoops_AHHS _hoops_HGPHP.
	RECT Rect;
	GetWindowRect(dx9data->hWND, &Rect);
	if (Rect.left==Rect.right || Rect.top==Rect.bottom) {
		if (Rect.left!=Rect.right)
			MoveWindow(dx9data->hWND, Rect.left, Rect.top, Rect.right-Rect.left, 1, 0);
		else if (Rect.top!=Rect.bottom)
			MoveWindow(dx9data->hWND, Rect.left, Rect.top, 1, Rect.bottom-Rect.top, 0);
		else
			MoveWindow(dx9data->hWND, Rect.left, Rect.top, 1, 1, 0);
	}

	if (!d3d_sd->pDevice) {
		if (!BIT(dx9data->dc->options._hoops_IRARR, _hoops_GGRAH)) {
			// _hoops_GISA _hoops_RH _hoops_SISS
			NEW(DX9CreateDeviceTask)(d3d_sd, 
				dx9data->_hoops_IISRH->_hoops_PPGGP(), 
				_hoops_CGRGP->_hoops_PHGGP,
				dx9data->hWND, 
				_hoops_RIGAH);
		}
		else {
			// _hoops_GISA _hoops_IRS _hoops_RGRAH-_hoops_PPP _hoops_SISS (_hoops_IH _hoops_SIAC)
			NEW(DX9CreateDeviceTask)(d3d_sd, 
				d3d_sd->_hoops_SHSSA->GetAdapterCount()-1, 
				D3DDEVTYPE_REF,
				dx9data->hWND, 
				_hoops_RIGAH);
		}

		HM_WAIT_SEMAPHORE(d3d_sd->_hoops_HISSA);
	}

	dx9data->pDevice = d3d_sd->pDevice;
	_hoops_IIRHP = dx9data->pDevice->CreateAdditionalSwapChain(&dx9data->_hoops_HCARH, &dx9data->_hoops_IGCRH);

	_hoops_RGAIR(dc->_hoops_PGCC._hoops_GSPGH);
	_hoops_RGAIR(dc->_hoops_PGCC._hoops_RSPGH);
	HI_Copy_Chars_To_Name("DEFAULT", &dc->_hoops_PGCC._hoops_GSPGH);
	HI_Copy_Chars_To_Name("*", &dc->_hoops_PGCC._hoops_RSPGH);
	dc->_hoops_PGCC._hoops_PRARR = dx9data->_hoops_PRARR = HI_Lookup_Driver_Config(dc->_hoops_RIGC, "dx9", "DEFAULT", "*", true, _hoops_RSPRH);

	if (SUCCEEDED(_hoops_IIRHP)) {
		// _hoops_CRSRR _hoops_RH _hoops_PGPRH
		D3DAdapterInfo* _hoops_PGRGP = dx9data->_hoops_IISRH->_hoops_GSRGP();
		char const *test = (char const *) _hoops_PGRGP->_hoops_HPGGP.Description;

		if (test) {
			HI_Free_Driver_Config(dx9data->_hoops_PRARR);
			_hoops_RGAIR(dc->_hoops_PGCC._hoops_GSPGH);
			_hoops_RGAIR(dc->_hoops_PGCC._hoops_RSPGH);
			HI_Copy_Chars_To_Name(test, &dc->_hoops_PGCC._hoops_GSPGH);
			HI_Copy_Chars_To_Name("*", &dc->_hoops_PGCC._hoops_RSPGH);
			dc->_hoops_PGCC._hoops_PRARR = dx9data->_hoops_PRARR = HI_Lookup_Driver_Config(dc->_hoops_RIGC, "dx9", test, "*", true, _hoops_RSPRH);
		}

		// _hoops_SAH _hoops_SISS _hoops_AGRAH
		dx9data->pDevice->GetDeviceCaps(&dx9data->_hoops_HPHRH);
		dx9data->_hoops_ACGH._hoops_CGGI = dx9data->_hoops_HPHRH.MaxVertexIndex;
		dx9data->_hoops_ACGH._hoops_GRGI = dx9data->_hoops_HPHRH.MaxPrimitiveCount;

		dx9data->_hoops_ACGH._hoops_PCGH = dx9data->_hoops_HPHRH.MaxTextureWidth;
		dx9data->_hoops_ACGH._hoops_HCGH = dx9data->_hoops_HPHRH.MaxTextureHeight;
		dx9data->_hoops_ACGH._hoops_SPRH = BIT(dx9data->_hoops_HPHRH.TextureCaps, D3DPTEXTURECAPS_POW2);
		dc->_hoops_PGCC._hoops_PCPGH = _hoops_AHIA(dx9data->_hoops_ACGH._hoops_PCGH, dx9data->_hoops_ACGH._hoops_HCGH);


		// _hoops_SAIPR _hoops_GPP _hoops_HAGIR _hoops_SGS _hoops_RISA _hoops_HRGR _hoops_GIH
		if (dx9data->_hoops_ACGH._hoops_CGGI > 0x7FFF)
			dx9data->_hoops_ACGH._hoops_CGGI = 0x7FFF;
		if (dx9data->_hoops_ACGH._hoops_GRGI > 0xFFFF)
			dx9data->_hoops_ACGH._hoops_GRGI = 0xFFFF;

		if (dx9data->_hoops_HPHRH.PixelShaderVersion <= D3DPS_VERSION(2, 0))
			dx9data->_hoops_ACGH._hoops_PAARR = _hoops_IARAR;
		else if (dx9data->_hoops_HPHRH.PixelShaderVersion < D3DPS_VERSION(3, 0))
			dx9data->_hoops_ACGH._hoops_PAARR = _hoops_CARAR;
		else if (dx9data->_hoops_HPHRH.PixelShaderVersion < D3DPS_VERSION(4, 0))
			dx9data->_hoops_ACGH._hoops_PAARR = _hoops_SARAR;
		else
			ASSERT(0);
	}
	else {
		// _hoops_CGP _hoops_SGS _hoops_SRSH, _hoops_HSSC _hoops_ISSC _hoops_IS _hoops_RH _hoops_CGRPR _hoops_HAGAH
		if (_hoops_CGRGP->_hoops_PHGGP == D3DDEVTYPE_HAL) {
			HE_ERROR(HEC_DX9_DRIVER, HES_CANNOT_OPEN_DEVICE, "Failed to create a hardware accelerated Direct3D Device."
				"Attempting to switch to the reference rasterizer,"
				"a software device that implements the entire"
				"Direct3D feature set, but runs very slowly.");
			_hoops_CAGAH(dc, false, true);
			identify_renderer(dc);
		}
		else {
			HE_ERROR(HEC_DX9_DRIVER, HES_CANNOT_OPEN_DISPLAY, "Failed to create a Direct3D Device. Direct3d API CreateDevice failed.\n");
			HD_Kill_Driver (dc);
			return;
		}
		dx9data->_hoops_ACGH._hoops_PAARR = _hoops_SARAR;
	}
	if (dx9data->_hoops_ACGH._hoops_PAARR < _hoops_SARAR)
		dc->_hoops_PGCC._hoops_HCPGH = 1;
	else
		dc->_hoops_PGCC._hoops_HCPGH = 4;


	if (_hoops_CGRGP->_hoops_PHGGP == D3DDEVTYPE_HAL) {
		dc->_hoops_PGCC.driver_type = d3d_hardware_string;
		dx9data->_hoops_GSGRR = false;
	}
	else {
		dc->_hoops_PGCC.driver_type = d3d_software_string;
		dx9data->_hoops_GSGRR = true;
	}

	// _hoops_GISA _hoops_PGRAH
#ifdef _hoops_SHRIP
	_hoops_HP (dx9data->post);
#endif
	if (dx9data->post == null)
		dx9data->post = new _hoops_GSCRH(*dx9data);

	// _hoops_RAP _hoops_SHIR _hoops_GGGP _hoops_CCH
	dx9data->_hoops_II._hoops_AIGP = H3DPost::_hoops_SAPP;
	dx9data->_hoops_CRAP = _hoops_SGGRR;		// _hoops_HHSA _hoops_CGCRH _hoops_IS _hoops_PSASA _hoops_ASCS

	D3DPERF_EndEvent();

	return;

} //_hoops_RSGR '_hoops_PIAAR _hoops_PPGRR'


/*
 * _hoops_SRAC
 */
local POINTER_SIZED_INT get_outer_window (Display_Context const * _hoops_SAGRH)
{
	_hoops_RRPRH *_hoops_IRSRA = _hoops_ARPRH ();
	POINTER_SIZED_INT retval = 0L;
	int temp;
	WNDCLASS window_class;
	Display_Context alter * dc = (Display_Context alter *) _hoops_SAGRH;
	DX9Data alter *dx9data = DX9D (dc);

	//_hoops_PRPP _hoops_SIAC _hoops_ACPP _hoops_HIS _hoops_SGS _hoops_GCAC _hoops_HCPH _hoops_CHR _hoops_RCAC _hoops_IS _hoops_SSS
	H3D_TRACE(dx9data, "get_outer_window");

	/*_hoops_SHR _hoops_IRHH _hoops_IRS _hoops_CSHGR _hoops_IH _hoops_SGH _hoops_GGR _hoops_CRSRR _hoops_PPGRR*/
	if (!_hoops_IRSRA->d3d_hoops_class) {
		window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_GLOBALCLASS;
		window_class.lpfnWndProc = _hoops_PACRH;
		window_class.cbClsExtra = 0;
		window_class.cbWndExtra = 0;
		window_class.hInstance = _hoops_RCSRH (_hoops_ACSRH);
		if (dx9data->_hoops_PIGRR == _hoops_PPSGR)
			window_class.hIcon = LoadIcon (_hoops_RCSRH (_hoops_HGRAH), "HoopsIcon");
		else
			window_class.hIcon = 0;
		window_class.hCursor = LoadCursor (null, IDC_ARROW);
		window_class.hbrBackground = (HBRUSH__ *) GetStockObject (WHITE_BRUSH);
		window_class.lpszMenuName = null;
		window_class.lpszClassName = "HoopsWClassD3D";

		temp = RegisterClass (&window_class);

		if (temp == 0) {
			HE_ERROR (HEC_DX9_DRIVER, HES_CANNOT_CREATE_WINDOW, "Unable to Register our class");
			HD_Kill_Driver (dc);
		}
		_hoops_IRSRA->d3d_hoops_class = true;
	}

	switch (dx9data->_hoops_PIGRR) {

		case _hoops_HPSGR: {
		}	break;

		case DCT_IMAGE: 
		case _hoops_PPSGR: {
			DWORD window_style;
			char _hoops_IAPIR[4096];
			HMONITOR		_hoops_IGRAH;
			MONITORINFO		_hoops_CGRAH = { sizeof(_hoops_CGRAH) };
			const	POINT			_hoops_SGRAH = { 0, 0 };


			/* _hoops_GAGAH _hoops_RAGAH _hoops_PPR _hoops_GPAA */
			if (dc->options._hoops_AASSP) {
				dx9data->_hoops_ACGRR =
					dx9data->_hoops_PCGRR = GetSystemMetrics (SM_CXFRAME);
				dx9data->_hoops_RCGRR = GetSystemMetrics (SM_CYFRAME);
			}
			else {
				dx9data->_hoops_ACGRR =
					dx9data->_hoops_PCGRR = GetSystemMetrics (SM_CXBORDER);
				dx9data->_hoops_RCGRR = GetSystemMetrics (SM_CYBORDER);
			}
			dx9data->_hoops_HCGRR = dx9data->_hoops_RCGRR +
				GetSystemMetrics (SM_CYCAPTION) - 1;

			/* _hoops_CAHA _hoops_GGSR _hoops_RH _hoops_RPPS _hoops_IAHA */
			window_style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW;

			if (!dc->options._hoops_AASSP) {
				window_style &= ~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_MINIMIZE | WS_THICKFRAME);
			}

			HI_Copy_Name_To_Chars (&dc->options._hoops_IAPIR, _hoops_IAPIR);
			_hoops_IAPIR[79] = '\0';

			dx9data->_hoops_SIGRR.x = dc->_hoops_RHPGA.left
				- dx9data->_hoops_PCGRR;
			dx9data->_hoops_SIGRR.y = dx9data->_hoops_CCGRR -
				dc->_hoops_RHPGA.top - dx9data->_hoops_HCGRR;
			dx9data->_hoops_GCGRR.x = dx9data->_hoops_CIGRR.x = dc->_hoops_RHPGA.right -
				dc->_hoops_RHPGA.left +
				dx9data->_hoops_ACGRR + dx9data->_hoops_PCGRR;
			dx9data->_hoops_GCGRR.y = dx9data->_hoops_CIGRR.y = dc->_hoops_RHPGA.top -
				dc->_hoops_RHPGA.bottom +
				dx9data->_hoops_HCGRR + dx9data->_hoops_RCGRR;


			if (dx9data->_hoops_PIGRR != DCT_IMAGE) {
				if (BIT(dc->options.flags, _hoops_GIPRP)) {
					_hoops_IGRAH = MonitorFromPoint(_hoops_SGRAH, MONITOR_DEFAULTTOPRIMARY);
					GetMonitorInfo(_hoops_IGRAH, &_hoops_CGRAH);
					dx9data->hWND = 
						CreateWindow ("HoopsWClassD3D", _hoops_IAPIR, WS_POPUP | WS_VISIBLE,
											_hoops_CGRAH.rcMonitor.left,
											_hoops_CGRAH.rcMonitor.top,
											_hoops_CGRAH.rcMonitor.right - _hoops_CGRAH.rcMonitor.left,
											_hoops_CGRAH.rcMonitor.bottom - _hoops_CGRAH.rcMonitor.top,
											null, null, _hoops_RCSRH (_hoops_ACSRH), (LPSTR)dc);
				} else{
					dx9data->hWND =
						CreateWindow ("HoopsWClassD3D", _hoops_IAPIR, window_style,
							dc->_hoops_RHPGA.left - dx9data->_hoops_PCGRR,
							dx9data->_hoops_CCGRR -
							dc->_hoops_RHPGA.top - dx9data->_hoops_HCGRR,
							dc->_hoops_RHPGA.right -
							dc->_hoops_RHPGA.left +
							dx9data->_hoops_ACGRR + dx9data->_hoops_PCGRR,
							dc->_hoops_RHPGA.top -
							dc->_hoops_RHPGA.bottom +
							dx9data->_hoops_HCGRR + dx9data->_hoops_RCGRR,
							null, null, _hoops_RCSRH (_hoops_ACSRH), (LPSTR) dc);
				}
			}
			else {
				int w, h;
				w = dx9data->_hoops_IHGRR->width;
				h = dx9data->_hoops_IHGRR->height;
				dx9data->hWND =
					CreateWindow ("HoopsWClassD3D", _hoops_IAPIR, WS_POPUP,
						0, 0, w, h, 
						null, null, _hoops_RCSRH (_hoops_ACSRH), (LPSTR) dc);
#ifdef _WIN64
				dx9data->_hoops_GIGRR =
					(WNDPROC) SetWindowLongPtr (dx9data->hWND, GWLP_WNDPROC, 0);
#else
				dx9data->_hoops_GIGRR =
					(WNDPROC) SetWindowLong (dx9data->hWND, GWL_WNDPROC, 0);
#endif

			}

			if (dx9data->hWND == null) {
				HE_ERROR (HEC_DX9_DRIVER, HES_CANNOT_CREATE_WINDOW,
					"Unable to Create a Window");
				HD_Kill_Driver (dc);
			}
			if (dx9data->_hoops_PIGRR != DCT_IMAGE) {
				ShowWindow (dx9data->hWND, SW_SHOWNORMAL);
				UpdateWindow (dx9data->hWND);
			}

			if (dc->options._hoops_HRSSP) {
				HMENU _hoops_GRRAH;

				_hoops_GRRAH = GetSystemMenu (dx9data->hWND, FALSE);
			}
			GetClientRect (dx9data->hWND, (RECT *) &dx9data->_hoops_IIGRR); 
		}
		break;

	}

	retval = (POINTER_SIZED_INT) dx9data->hWND;
	dx9data->hDC = GetDC (dx9data->hWND);

	if ((dx9data->_hoops_ASRRR = (IsIconic(dx9data->hWND) != 0)) == false && !dc->options._hoops_IASSP) {
		bool _hoops_RRRAH = (dc->options._hoops_IRARR & _hoops_ARRAH) ? true : false;

		_hoops_CAGAH(dc, false, _hoops_RRRAH);
		identify_renderer (dc);
		if (dx9data->_hoops_GSGRR)
			dc->_hoops_PGCC.flags &= ~_hoops_PHPGH;
		if (BIT (dc->_hoops_GHRI->_hoops_CGPIR, _hoops_SGPIR))
			return 0;
		_hoops_ISPRH (dc);
	}
	return retval;

} //_hoops_RSGR '_hoops_HGCR _hoops_CRIPR _hoops_RPPS'


/*
* _hoops_SRAC
*/
local void free_outer_window (Display_Context const * dc)
{
	DX9Data alter *dx9data = DX9D (dc);
	dx9data->_hoops_IGAGR = true;

	if (dx9data->_hoops_CIGI)
		_hoops_ASCI (dx9data);

	// _hoops_SP _hoops_GH _hoops_AIRI _hoops_CPCI
	HD_Purge_Display_Lists(dc->_hoops_GHRI, null, null); 

	if (dc->_hoops_GHRI->_hoops_RGAGR)
		_hoops_SSRGR((Display_Context alter *)dc);

	if (dx9data->_hoops_PIGRR == _hoops_PPSGR ||
		dx9data->_hoops_PIGRR == DCT_IMAGE) {
		_hoops_CPSRH (dc);
		DestroyWindow (dx9data->hWND);
		dx9data->hWND = null;
	}

#ifdef _hoops_SPARH
	if (_hoops_RHARH)
	{
		_hoops_RHARH->DeleteItems();
		delete _hoops_RHARH;
		_hoops_RHARH = null;
	}
#endif

	dx9data->_hoops_PP();
}


/*
 * _hoops_SRAC
 */
local void _hoops_ASCSP (
	Display_Context const	*dc) 
{
	DX9Data alter *dx9data = DX9D (dc);

	SetWindowText (dx9data->hWND, dc->options._hoops_IAPIR.text);
}

/*
* _hoops_SRAC
*/
local void
_hoops_RSCSP (Display_Context const * dc)
{
	DX9Data alter *dx9data = DX9D (dc);

	dx9data->_hoops_HCAC = _hoops_CCC;
	dx9data->_hoops_RPCI = _hoops_CCC;
	dx9data->_hoops_IARRR = _hoops_CCC;
	dx9data->_hoops_ICAC = _hoops_CCC;

	if ((dx9data->_hoops_PIGRR == _hoops_PPSGR ||
		dx9data->_hoops_PIGRR == _hoops_HPSGR) &&
		IsWindow (dx9data->hWND) &&
		(IsIconic (dx9data->hWND) || IsZoomed (dx9data->hWND))) {
		/* _hoops_CGP _hoops_RH _hoops_RPPS _hoops_HRGR _hoops_PRRAH _hoops_SR _hoops_SSPC _hoops_HCR _hoops_PCCS _hoops_SSHRH */
		return;
	}

	dx9data->_hoops_SIGRR.x = dc->_hoops_RHPGA.left - dx9data->_hoops_PCGRR;
	dx9data->_hoops_SIGRR.y = dx9data->_hoops_CCGRR -
		dc->_hoops_RHPGA.top - dx9data->_hoops_HCGRR;
	dx9data->_hoops_CIGRR.x = dc->_hoops_RHPGA.right -
		dc->_hoops_RHPGA.left + dx9data->_hoops_ACGRR + dx9data->_hoops_PCGRR;
	dx9data->_hoops_CIGRR.y = dc->_hoops_RHPGA.top -
		dc->_hoops_RHPGA.bottom + dx9data->_hoops_HCGRR +
		dx9data->_hoops_RCGRR;

	MoveWindow (dx9data->hWND,
		dc->_hoops_RHPGA.left - dx9data->_hoops_PCGRR,
		dx9data->_hoops_CCGRR -
		dc->_hoops_RHPGA.top - dx9data->_hoops_HCGRR,
		dc->_hoops_RHPGA.right - dc->_hoops_RHPGA.left +
		dx9data->_hoops_ACGRR + dx9data->_hoops_PCGRR,
		dc->_hoops_RHPGA.top - dc->_hoops_RHPGA.bottom +
		dx9data->_hoops_HCGRR + dx9data->_hoops_RCGRR, true);
}



/*****************************************************************************
*****************************************************************************
							_hoops_HRRAH
*****************************************************************************
*****************************************************************************/

/*
 * _hoops_SRAC
 * _hoops_RPP _hoops_GHGPR _hoops_RHGPR, _hoops_RGR _hoops_PIHA _hoops_SHH _hoops_PIGS _hoops_ARPP _hoops_RH _hoops_GGSHR _hoops_PSCA
 */
local bool
snapshot(
	Net_Rendition const &  nr,
	int width,
	int height,
	unsigned char * data)
{
	//_hoops_IRRAH _hoops_CIAPR("_hoops_CRRAH");

	DX9Data alter *dx9data = DX9D (nr->_hoops_SRA);
	Int_Rectangle const * area = &nr->_hoops_SAIR->_hoops_SCIH;
	int w,h;
	LPDIRECT3DSURFACE9 pCurrentSurface, pSavedSurface;
	D3DPRESENT_PARAMETERS pp = dx9data->_hoops_HCARH;
	bool result = false;

	w = area->right - area->left + 1;
	h = area->top - area->bottom + 1;

	if (w*h > width*height)
		return result;
	
	// _hoops_HGCR _hoops_RH _hoops_ASPA _hoops_HII _hoops_SCGR _hoops_SRGS _hoops_SAAP _hoops_IS _hoops_HPIH _hoops_SRRAH _hoops_SRGS _hoops_ISSGR
	dx9data->_hoops_IGCRH->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pCurrentSurface);
	dx9data->pDevice->StretchRect (_hoops_PIARH(dx9data->render_target), null, pCurrentSurface, null, D3DTEXF_NONE);

	// _hoops_ARPR _hoops_IRS _hoops_SRRAH _hoops_ISSGR _hoops_CCA _hoops_RH _hoops_PSHR _hoops_HAARR
	D3DSURFACE_DESC desc;
	pCurrentSurface->GetDesc(&desc);
	dx9data->pDevice->CreateOffscreenPlainSurface(
		desc.Width, desc.Height, pp.BackBufferFormat, D3DPOOL_SYSTEMMEM, &pSavedSurface, null);

	if (!pCurrentSurface || !pSavedSurface)
		goto release;

	dx9data->pDevice->GetRenderTargetData(pCurrentSurface, pSavedSurface);

	
	D3DLOCKED_RECT d3dlr;
	pSavedSurface->LockRect(&d3dlr, null, D3DLOCK_READONLY);


	int y;
	int yoffset = dx9data->yfudge - height + 1;
	for (y = 0; y < height; y++) {
		unsigned char *d_row = (unsigned char *) &data[(y*width*3)];
		CHAR* pSrc = (CHAR*)d3dlr.pBits + (y + yoffset)*d3dlr.Pitch;
		for (int x = 0; x < width; x++) {
			unsigned char b=*pSrc++;
			unsigned char g=*pSrc++;
			unsigned char r=*pSrc++;

			*d_row++ = r;
			*d_row++ = g;
			*d_row++ = b;

			pSrc++;
		}
	}
	pSavedSurface->UnlockRect();

	result = true;

release:
	H_SAFE_RELEASE (pCurrentSurface);
	H_SAFE_RELEASE (pSavedSurface);

	return result;
}

/*
 * _hoops_SRAC
 */
local void _hoops_CGAGR (Display_Context const *dc, void *list)
{
	DX9Data *dx9data = DX9D(dc);
	H3D_Display_List alter * odl = (H3D_Display_List alter*)list;
	Image *image = (Image *)odl->_hoops_PPAH->owner;
	int w = image->width;
	int h = image->height;
	_hoops_RIARH *dx9tex2d = (_hoops_RIARH *)odl->item.texture.id;
	LPDIRECT3DSURFACE9 pCurrentSurface, pSavedSurface, _hoops_GARAH;
	D3DPRESENT_PARAMETERS pp = dx9data->_hoops_HCARH;
	D3DSURFACE_DESC desc;

	if (image->_hoops_PHGH == null)
		ALLOC_ARRAY (image->_hoops_PHGH, image->row_bytes*h, unsigned char);
	
	dx9tex2d->GetSurfaceLevel(0, &_hoops_GARAH);

	_hoops_GARAH->GetDesc(&desc);
	if (desc.Pool == D3DPOOL_MANAGED) {
		pCurrentSurface = null;
		pSavedSurface = _hoops_GARAH;
		_hoops_GARAH = null;
	}
	else {
		// _hoops_HGCR _hoops_RH _hoops_ASPA _hoops_HII _hoops_SCGR _hoops_SRGS _hoops_SAAP _hoops_IS _hoops_HPIH _hoops_SRRAH _hoops_SRGS _hoops_ISSGR
		dx9data->_hoops_IGCRH->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pCurrentSurface);
		dx9data->pDevice->StretchRect (_hoops_GARAH, null, pCurrentSurface, null, D3DTEXF_NONE);

		// _hoops_ARPR _hoops_IRS _hoops_SRRAH _hoops_ISSGR _hoops_CCA _hoops_RH _hoops_PSHR _hoops_HAARR
		pCurrentSurface->GetDesc(&desc);
		dx9data->pDevice->CreateOffscreenPlainSurface(
			desc.Width, desc.Height, pp.BackBufferFormat, D3DPOOL_SYSTEMMEM, &pSavedSurface, null);

		if (!pCurrentSurface || !pSavedSurface) {
			HE_ERROR (0, 0, "Cannot create readable surface");
			goto release;
		}

		dx9data->pDevice->GetRenderTargetData(pCurrentSurface, pSavedSurface);
	}
	D3DLOCKED_RECT d3dlr;
	pSavedSurface->LockRect(&d3dlr, null, D3DLOCK_READONLY);

	int y;

	if (image->format == _hoops_AHGH) {
		for (y = 0; y < h; y++) {
			unsigned char *d_row = (unsigned char *) &((unsigned char *) image->_hoops_PHGH)[(y*w)];
			CHAR* pSrc = (CHAR*)d3dlr.pBits + y*d3dlr.Pitch;
			for (int x = 0; x < w; x++) {
				*d_row++ = *pSrc++;
			}
		}
	} 
	else if (image->format == _hoops_HHGH) {
		for (y = 0; y < h; y++) {
			unsigned char *d_row = (unsigned char *) &((unsigned char *) image->_hoops_PHGH)[(y*w*3)];
			CHAR* pSrc = (CHAR*)d3dlr.pBits + y*d3dlr.Pitch;
			for (int x = 0; x < w; x++) {
				unsigned char b=*pSrc++;
				unsigned char g=*pSrc++;
				unsigned char r=*pSrc++;

				*d_row++ = r;
				*d_row++ = g;
				*d_row++ = b;

				pSrc++;
			}
		}
	} 
	else if (image->format == Image_RGBA32) {
		for (y = 0; y < h; y++) {
			unsigned char *d_row = (unsigned char *) &((unsigned char *) image->_hoops_PHGH)[(y*w*4)];
			CHAR* pSrc = (CHAR*)d3dlr.pBits + y*d3dlr.Pitch;
			for (int x = 0; x < w; x++) {
				unsigned char a=*pSrc++;
				unsigned char b=*pSrc++;
				unsigned char g=*pSrc++;
				unsigned char r=*pSrc++;

				*d_row++ = r;
				*d_row++ = g;
				*d_row++ = b;
				*d_row++ = a;
			}
		}
	}
	else if (image->format == _hoops_AGGSP) {
		for (y = 0; y < h; y++) {
			float *d_row = (float *) &((float *) image->_hoops_PHGH)[(y*w)];
			float* pSrc = (float*)d3dlr.pBits + y*d3dlr.Pitch;
			for (int x = 0; x < w; x++) {
				*d_row++ = *pSrc++;
			}
		}
	}
	else {
		HE_ERROR (0, 0, "unrecognized image format in show_image_data()");
		return;
	}

	pSavedSurface->UnlockRect();

	if (image->rasters == null) {
		ALLOC_ARRAY (image->rasters, image->height, void const *);
		void **_hoops_RARAH = (void **)image->rasters;
		for (int i = 0 ; i < image->height ; i++) {
			_hoops_RARAH[i] = &((unsigned char *)image->_hoops_PHGH)[image->row_bytes*i];
		}
	}
	image->flags &= ~(_hoops_GRRH|_hoops_APAH);

release:
	H_SAFE_RELEASE (pCurrentSurface);
	H_SAFE_RELEASE (pSavedSurface);
	H_SAFE_RELEASE (_hoops_GARAH);

	return;
}

void _hoops_AARAH (
		DX9Data alter *dx9data, 
		DX9ImageRegion *_hoops_PARAH, 
		DX9DepthRegion *_hoops_GCIIP)
{
	int const width = dx9data->render_target->_hoops_IRRP;
	int const height = dx9data->render_target->_hoops_CRRP;

	if (_hoops_PARAH) {
		// _hoops_GISA _hoops_PSGRR _hoops_IS _hoops_ASAC _hoops_RH _hoops_HIRA
		dx9data->pDevice->CreateRenderTarget(width, height, d3dformat(dx9data->render_target->_hoops_GSPP),
			(D3DMULTISAMPLE_TYPE) dx9data->render_target->_hoops_HSARR, 0,
			FALSE, &_hoops_PARAH->surface, null);

		if (_hoops_PARAH->surface) {
			_hoops_PARAH->next = dx9data->_hoops_PSARH;
			dx9data->_hoops_PSARH = _hoops_PARAH;
		}
	}

	if (_hoops_GCIIP) {
		// _hoops_SIPR _hoops_HIRA _hoops_HCH _hoops_APSP _hoops_ISSGR _hoops_HRPRA.
		ASSERT( width == dx9data->depth_stencil->_hoops_IRRP && height == dx9data->depth_stencil->_hoops_CRRP);

		// _hoops_GISA _hoops_PSGRR _hoops_IS _hoops_ASAC _hoops_RH _hoops_HCH/_hoops_APSP _hoops_ISSGR
		dx9data->pDevice->CreateDepthStencilSurface(width, height, d3dformat(dx9data->depth_stencil->_hoops_GSPP),
			(D3DMULTISAMPLE_TYPE) dx9data->depth_stencil->_hoops_HSARR, 0,
			FALSE, &_hoops_GCIIP->surface, null);

		// _hoops_HR _hoops_PSP _hoops_HCH _hoops_HH
		_hoops_GCIIP->texture = null;

		if (_hoops_GCIIP->surface) {
			_hoops_GCIIP->next = dx9data->_hoops_HSARH;
			dx9data->_hoops_HSARH = _hoops_GCIIP;
		}
	}
}


/*
* _hoops_SRAC
* _hoops_HARAH
* _hoops_HSSIA _hoops_PPGS _hoops_IH _hoops_SRGIA _hoops_HHH _hoops_CSCR _hoops_PIH.
* _hoops_HRS _hoops_AARAR _hoops_GGR _hoops_RH _hoops_SRSGR _hoops_IIGR _hoops_CSCR _hoops_PPR _hoops_IARAH
* _hoops_HRS _hoops_IRAP _hoops_IH _hoops_CARAH _hoops_RPP _hoops_SSH-_hoops_RHGPR _hoops_HRGR _hoops_IHPPP _hoops_PSAP
* _hoops_HGI _hoops_API _hoops_HRGR _hoops_SIGR 3d _hoops_IAGIP
* _hoops_GIGHR: _hoops_SPCA _hoops_HRGR _hoops_SCGR _hoops_SARAH _hoops_CCA _hoops_RAPA (_hoops_GPRAH.0b) _hoops_SGS _hoops_SCH _hoops_PAH _hoops_ASAI _hoops_AA _hoops_IASI _hoops_RPRAH
*		 _hoops_RH _hoops_RGHSP-_hoops_APRAH _hoops_AARAR - _hoops_HHAC _hoops_IHAC (18-_hoops_PPRAH-03)
*/
void _hoops_ICARH::create_region (Net_Rendition const &  nr,
			   Int_Rectangle const * area, void **image, void **z)
{
	UNREFERENCED(area);

	DX9Data alter *dx9data = DX9D (nr->_hoops_SRA);
	DX9ImageRegion *_hoops_PARAH = null;
	DX9DepthRegion *_hoops_GCIIP = null;

	H3D_TRACE(dx9data, "create_region");

	if (image) {
		ZALLOC(_hoops_PARAH, DX9ImageRegion);
		*image = _hoops_PARAH;
	}

	if (z) {
		ZALLOC(_hoops_GCIIP, DX9DepthRegion);
		*z = _hoops_GCIIP;
	}

	_hoops_AARAH (dx9data, _hoops_PARAH, _hoops_GCIIP);

	if (_hoops_PARAH && !_hoops_PARAH->surface) {
		// _hoops_CGP _hoops_SR _hoops_HGCR _hoops_ARI, _hoops_ISSGR _hoops_GHCS _hoops_SRSH (_hoops_GGSR _hoops_IIGR _hoops_PPGS)
		FREE(_hoops_PARAH, DX9ImageRegion);
		*image = null;
	}
	if (_hoops_GCIIP && !_hoops_GCIIP->surface) {
		FREE(_hoops_GCIIP, DX9DepthRegion);
		*z = null;
	}

}/* _hoops_RSGR _hoops_API _hoops_HARAH */


 /*
 * _hoops_SRAC
 * _hoops_CCPIP
 * _hoops_HPRAH _hoops_IRS _hoops_IPRAH _hoops_PRGGR _hoops_IIGR _hoops_CSCR _hoops_HII _hoops_SCGR _hoops_SRGS _hoops_SAAP _hoops_IS
 * _hoops_HPIH _hoops_CPRAH _hoops_SRGS _hoops_ISSGR. _hoops_RPICR _hoops_IH _hoops_HCH _hoops_PSCA - _hoops_HIH _hoops_SR _hoops_PAH'_hoops_RA
 * _hoops_AA _hoops_IASI _hoops_IPS _hoops_GPP _hoops_HCH-_hoops_APSP _hoops_AARAR _hoops_GGR _hoops_RAPA _hoops_GPRAH.0b
*/
void _hoops_ICARH::_hoops_HIPGR (Net_Rendition const &  nr,
			 Int_Rectangle const * area, void alter * image,
			 void alter * z)
{
	UNREFERENCED(area);

	DX9Data alter *dx9data = DX9D (nr->_hoops_SRA);
	DX9ImageRegion *_hoops_PARAH = (DX9ImageRegion*) image;
	DX9DepthRegion *_hoops_GCIIP = (DX9DepthRegion*) z;

	if ((_hoops_PARAH && !_hoops_PARAH->surface) ||
		(_hoops_GCIIP && !_hoops_GCIIP->surface)) {
		_hoops_AARAH (dx9data, _hoops_PARAH, _hoops_GCIIP);
	}

	H3D_TRACE(dx9data, "save_region");

	// _hoops_SIPR _hoops_HIRA _hoops_ACGGR _hoops_HAARR
	int const width = dx9data->render_target->_hoops_IRRP / dx9data->_hoops_HSAA;
	int const height = dx9data->render_target->_hoops_CRRP / dx9data->_hoops_ISAA;

	_hoops_PPHH(dx9data, 0, 0, width, height);
	int const _hoops_GGSH = dx9data->_hoops_CSC->_hoops_GRPP;
	_hoops_GPRP(dx9data, H3DMASK_RGBA);

	// _hoops_RPRAH _hoops_HRGR _hoops_HAR _hoops_PHRH _hoops_GAPA _hoops_PHGRR _hoops_PPR _hoops_HHGRR _hoops_HCPH
	dx9data->pDevice->EndScene();

	if (_hoops_PARAH && _hoops_PARAH->surface) // _hoops_GIGHR: _hoops_AARAR _hoops_HGCR _hoops_SHPHP _hoops_RHSP _hoops_PCCS
		dx9data->pDevice->StretchRect(_hoops_PIARH(dx9data->render_target), null, _hoops_PARAH->surface, null, D3DTEXF_NONE);
	if (_hoops_GCIIP) {
		if (_hoops_GCIIP->surface)
			dx9data->pDevice->StretchRect(_hoops_PIARH(dx9data->depth_stencil), null, _hoops_GCIIP->surface, null, D3DTEXF_NONE);

		if (dx9data->_hoops_II.depth_texture) {
			
			// _hoops_GISA _hoops_GPP _hoops_HRGGR
			if ( !_hoops_GCIIP->texture ) {
				// _hoops_HIGAR _hoops_RPCC _hoops_GRS _hoops_RH _hoops_HCH _hoops_HH _hoops_SHH _hoops_GRP?
				D3DFORMAT format = dx9data->_hoops_GAP ? D3DFMT_R32F : D3DFMT_A8R8G8B8;

				// _hoops_GISA _hoops_PSGRR _hoops_IS _hoops_ASAC _hoops_RH _hoops_HCH _hoops_HH _hoops_ISSGR
				dx9data->pDevice->CreateRenderTarget(dx9data->_hoops_II.depth_texture->_hoops_IRRP, 
					dx9data->_hoops_II.depth_texture->_hoops_CRRP, format,
					(D3DMULTISAMPLE_TYPE) dx9data->_hoops_II.depth_texture->_hoops_HSARR, 0,
					FALSE, &_hoops_GCIIP->texture, null);
			}

			if ( _hoops_GCIIP->texture )
				_hoops_HGIP(dx9data->pDevice, dx9data->_hoops_II.depth_texture, _hoops_GCIIP->texture );
		}
	}
	
	dx9data->pDevice->BeginScene();

	_hoops_GPRP(dx9data, _hoops_GGSH);

}/* _hoops_RSGR _hoops_API _hoops_CCPIP */


 /*
 * _hoops_SRAC
 * _hoops_SPRAH
 * _hoops_HPRAH _hoops_ISSC _hoops_RH _hoops_IPRAH _hoops_PRGGR _hoops_IIGR _hoops_CSCR _hoops_HII _hoops_RH _hoops_CPRAH _hoops_SRGS _hoops_SAAP _hoops_IS
 * _hoops_HPIH _hoops_SCGR _hoops_SRGS _hoops_ISSGR. _hoops_RPICR _hoops_IH _hoops_HCH _hoops_PSCA - _hoops_HIH _hoops_SR _hoops_PAH'_hoops_RA
 * _hoops_AA _hoops_IASI _hoops_IPS _hoops_GPP _hoops_HCH-_hoops_APSP _hoops_AARAR _hoops_GGR _hoops_RAPA _hoops_GPRAH.0b
*/
void _hoops_ICARH::_hoops_PIPGR (Net_Rendition const &  nr,
				Int_Rectangle const * area, void alter * image,
				void alter * z)
{
	UNREFERENCED(area);

	DX9Data alter *dx9data = DX9D (nr->_hoops_SRA);
	DX9ImageRegion *_hoops_PARAH = (DX9ImageRegion *) image;
	DX9DepthRegion *_hoops_GCIIP = (DX9DepthRegion *) z;

	H3D_TRACE(dx9data, "restore_region");

	// _hoops_SIPR _hoops_HIRA _hoops_ACGGR _hoops_HAARR
	int const width = dx9data->render_target->_hoops_IRRP / dx9data->_hoops_HSAA;
	int const height = dx9data->render_target->_hoops_CRRP / dx9data->_hoops_ISAA;

	_hoops_APHH(dx9data, 0, 1);
	_hoops_PPHH(dx9data, 0, 0, width, height);
	int const _hoops_GGSH = dx9data->_hoops_CSC->_hoops_GRPP;
	_hoops_GPRP(dx9data, H3DMASK_RGBA);

	// _hoops_RPRAH _hoops_HRGR _hoops_HAR _hoops_PHRH _hoops_GAPA _hoops_PHGRR _hoops_PPR _hoops_HHGRR _hoops_HCPH
	dx9data->pDevice->EndScene();

	if (_hoops_PARAH && _hoops_PARAH->surface) // _hoops_GIGHR: _hoops_AARAR _hoops_HGCR _hoops_SHPHP _hoops_RHSP _hoops_PCCS
		dx9data->pDevice->StretchRect(_hoops_PARAH->surface, null, _hoops_PIARH(dx9data->render_target), null, D3DTEXF_NONE);
	if (_hoops_GCIIP && _hoops_GCIIP->surface)
		dx9data->pDevice->StretchRect(_hoops_GCIIP->surface, null, _hoops_PIARH(dx9data->depth_stencil), null, D3DTEXF_NONE);
	if (_hoops_GCIIP && _hoops_GCIIP->texture && dx9data->_hoops_II.depth_texture)
		_hoops_HGIP(dx9data->pDevice, _hoops_GCIIP->texture, dx9data->_hoops_II.depth_texture);

	dx9data->pDevice->BeginScene();

	_hoops_GPRP(dx9data, _hoops_GGSH);

}/* _hoops_RSGR _hoops_API _hoops_SPRAH */

/**
 * _hoops_SACA. _hoops_RHHH _hoops_HHH _hoops_RRGR _hoops_PRSP.
 */
template <typename _hoops_PGHHA>
void _hoops_GHRAH( _hoops_PGHHA *& head, _hoops_PGHHA *region )
{
	_hoops_PGHHA * _hoops_RHRAH = 0;
	_hoops_PGHHA * _hoops_AHRAH = head;
	while (_hoops_AHRAH) {
		if (_hoops_AHRAH == region) {
			if (_hoops_RHRAH)
				_hoops_RHRAH->next = _hoops_AHRAH->next;
			else
				head = _hoops_AHRAH->next;
			break;
		}
		_hoops_RHRAH = _hoops_AHRAH;
		_hoops_AHRAH = _hoops_AHRAH->next;
	}
}

/*
 * _hoops_SRAC
 * _hoops_PHRAH
 * _hoops_RCSH _hoops_RH _hoops_AARAR. _hoops_HIPR _hoops_HASIR _hoops_CAPR _hoops_HII _hoops_RH _hoops_RHPP _hoops_PIH
*/
void _hoops_ICARH::_hoops_ISPGR (Display_Context alter * dc,
				void alter * image, void alter * z)
{
	DX9Data alter *dx9data = DX9D (dc);
	DX9ImageRegion *_hoops_PARAH = (DX9ImageRegion *) image;
	DX9DepthRegion *_hoops_GCIIP = (DX9DepthRegion *) z;

	H3D_TRACE(dx9data, "destroy_region");

	// _hoops_HASIR _hoops_HII _hoops_ISCP _hoops_CCHHR _hoops_CPCI
	_hoops_GHRAH( dx9data->_hoops_PSARH, _hoops_PARAH );
	_hoops_GHRAH( dx9data->_hoops_HSARH, _hoops_GCIIP );

	if (_hoops_PARAH != null) {
		H_SAFE_RELEASE(_hoops_PARAH->surface);
		FREE(_hoops_PARAH, DX9ImageRegion);
	}

	if (_hoops_GCIIP != null) {
		H_SAFE_RELEASE(_hoops_GCIIP->surface);
		H_SAFE_RELEASE(_hoops_GCIIP->texture);
		FREE(_hoops_GCIIP, DX9DepthRegion);
	}

}/* _hoops_RSGR _hoops_API _hoops_PHRAH */




/*****************************************************************************
 *****************************************************************************
					 _hoops_HHRAH
 *****************************************************************************
*****************************************************************************/

/*
* _hoops_IHRAH - _hoops_IAGP _hoops_RACGH
*/
local void * _hoops_GRSSP (
				Net_Rendition const & nr,
				bool				disable_write)
{
	DX9Data alter *			dx9data = DX9D (nr->_hoops_SRA);
	LPDIRECT3DQUERY9		_hoops_APPRH = 0;

	if (disable_write) {
		_hoops_RPAP(dx9data, FALSE);
		ENSURE_DEPTH_MASK(dx9data, FALSE);
	}

	dx9data->pDevice->CreateQuery(D3DQUERYTYPE_OCCLUSION, &_hoops_APPRH);

	if (_hoops_APPRH)
		_hoops_APPRH->Issue(D3DISSUE_BEGIN);

	return (void *)_hoops_APPRH;
}

local void _hoops_RRSSP (
		Net_Rendition const & nr,
		void *					_hoops_HACGH)
{
	DX9Data alter *		dx9data = DX9D (nr->_hoops_SRA);
	LPDIRECT3DQUERY9	_hoops_APPRH	= (LPDIRECT3DQUERY9)_hoops_HACGH;

	if (_hoops_APPRH)
		_hoops_APPRH->Issue(D3DISSUE_END);

	_hoops_RPAP(dx9data, TRUE);
	ENSURE_DEPTH_MASK(dx9data, TRUE);
}

local int _hoops_CRGIP (
							   Net_Rendition const & nr,
							   void *					_hoops_HACGH)
{
	LPDIRECT3DQUERY9	_hoops_APPRH			= (LPDIRECT3DQUERY9)_hoops_HACGH;
	DWORD				_hoops_CHRAH	= D3DGETDATA_FLUSH;
	int					value			= 0xffff;

	if (_hoops_APPRH) {
		DWORD results;

		while (_hoops_APPRH->GetData(&results, sizeof(DWORD), _hoops_CHRAH) == S_FALSE);
		value = results;
 		_hoops_APPRH->Release();
	}

	UNREFERENCED(nr);

	return value;
}

local void _hoops_ARSSP (
							   Net_Rendition const & nr,
							   void *					_hoops_HACGH)
{
#if 1
	LPDIRECT3DQUERY9	_hoops_APPRH			= (LPDIRECT3DQUERY9)_hoops_HACGH;

	if (_hoops_APPRH)
		_hoops_APPRH->Release();
#else
	UNREFERENCED(_hoops_HACGH);
#endif

	UNREFERENCED(nr);
}


/*****************************************************************************
*****************************************************************************
							_hoops_SHRAH
*****************************************************************************
*****************************************************************************/

/*
 * _hoops_SRAC _hoops_GIRAH
 */
local void _hoops_RHH (
		Display_Context alter *	dc)
{
	HRESULT						_hoops_IIRHP;
	DX9Data alter *				dx9data = DX9D (dc);
	int							_hoops_RIRAH = dc->_hoops_AHAGH;
	int							_hoops_AIRAH;
	_hoops_PGCIP alter *		list;
	int							i;
	int							_hoops_PIRAH = 0;
	int							_hoops_IAAIP, _hoops_CAAIP;
	int							width, height;
	Int_Rectangle const *	extent;
	bool						_hoops_IA = true;
	bool						result = true;
	H3DTexture					**_hoops_IPRRR = dx9data->_hoops_RHH._hoops_IPRRR;
	H3DTexture					**_hoops_CPRRR = dx9data->_hoops_RHH._hoops_CPRRR;
	float						_hoops_ACCRR, _hoops_PCCRR, _hoops_ISPI, _hoops_CSPI;

	// _hoops_HIRAH _hoops_AAP
	const bool					_hoops_ISARR = dx9data->_hoops_CRAP == _hoops_SRAP;
	H3DFORMAT					_hoops_GCH = H3DFMT_R32F;
	bool						_hoops_ACH = true;

// _hoops_AHH: _hoops_ISIRR _hoops_IH _hoops_HISRA _hoops_AIRI
// #_hoops_PPIP _hoops_IIRAH

	if (dc->_hoops_PPSIP != null)
		HD_Process_Deferred_Octrees (dc);

#ifdef _hoops_CIRAH
	// _hoops_GISA/_hoops_ASAC _hoops_CSCR _hoops_ARPP _hoops_ICH
	if ( _hoops_PGCIP alter * _hoops_SIRAH = dc->_hoops_GPSS[dc->_hoops_IASS] ) {
		if ( !dx9data->_hoops_ICIRH || !dx9data->_hoops_CCIRH )
			create_region(_hoops_SIRAH->nr, null, &dx9data->_hoops_ICIRH, &dx9data->_hoops_CCIRH);
		_hoops_HIPGR(_hoops_SIRAH->nr, null, dx9data->_hoops_ICIRH, dx9data->_hoops_CCIRH);
	}
#endif

	//
	// _hoops_GCRAH-_hoops_GGSR _hoops_IH _hoops_RSRA-_hoops_ASAH _hoops_ICH, _hoops_PGAP _hoops_PAH _hoops_SHH _hoops_GIR _hoops_GGGGR.
	//
	if (XBIT_TEST(dx9data->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_DEPTH_PEELING)) {
		dc->_hoops_PGCC._hoops_AHAGH = 1; 
		_hoops_RIRAH = 1;
	}

	if (_hoops_RIRAH == 1) {
		H3D_TRACE(dx9data, "layer 1 depth peeling");
		dx9data->_hoops_RHH._hoops_HRI = true;
		HD_Std_Depth_Peeling (dc);
		dx9data->_hoops_RHH._hoops_HRI = false;
		return;
	}

	//
	// _hoops_GCRAH-_hoops_GGSR _hoops_IH _hoops_RHPA _hoops_HCH _hoops_ICH _hoops_HIGR
	//

	if ((list = dc->_hoops_GPSS[dc->_hoops_IASS]) == null)
		return;
	dc->_hoops_GPSS[dc->_hoops_IASS] = null;
	if (BIT(dc->flags, _hoops_CHSI)) {
		HD_Free_Deferred_3D_Geometry (list);
		return;
	}

	//
	// _hoops_ACCRH _hoops_HCH _hoops_ICH _hoops_IS _hoops_IHRA _hoops_GSIA/_hoops_RCRAH.
	//

	if (_hoops_ISARR) {
		// _hoops_GPGP _hoops_IIGAR _hoops_HSGRR _hoops_CCH, _hoops_SR _hoops_PIHA _hoops_SGH _hoops_PGCR _hoops_RIH _hoops_RGPP.
		_hoops_GCH = H3DFMT_A8R8G8B8;
		_hoops_ACH = false;
	}
	else
	{
		// _hoops_CGP _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_CIGAH _hoops_GCGH, _hoops_HSSC _hoops_ISSC.
		if (!dx9data->_hoops_GAP) 
			_hoops_GCH = H3DFMT_A8R8G8B8;

		// _hoops_CGP _hoops_SR _hoops_PAH _hoops_AA _hoops_RIAP, _hoops_SR _hoops_GA'_hoops_RA _hoops_RRP _hoops_PGCR _hoops_RIH. _hoops_HHPC _hoops_SR _hoops_AA.
		if (dx9data->_hoops_GRAP < 2)
			_hoops_ACH = false;
	}

	if (_hoops_RIRAH > _hoops_APRRR)
		_hoops_RIRAH = _hoops_APRRR;

	//
	// _hoops_HGH _hoops_PGRR _hoops_PPR _hoops_ARPR _hoops_CIPP.
	//

	// _hoops_ACRAH _hoops_ASCA _hoops_HPGR _hoops_ICIH _hoops_IGIR
	int const _hoops_PCRAH = dx9data->_hoops_HCARH.BackBufferWidth;
	int const _hoops_HCRAH = dx9data->_hoops_HCARH.BackBufferHeight;

	// _hoops_GRSH _hoops_AHPH _hoops_AHCR _hoops_AI _hoops_AA _hoops_SR _hoops_RRP?
	int _hoops_ICRAH = _hoops_ISARR ? 1 : 2;

	{
		H3D_TRACE(dx9data, "depth_peeling allocation");

		// _hoops_IIPP _hoops_PSCA _hoops_HPGR _hoops_SRGS _hoops_SAAP _hoops_IGIR.
		int const _hoops_CCRAH = dx9data->render_target->_hoops_IRRP;
		int const _hoops_SCRAH = dx9data->render_target->_hoops_CRRP;

#ifdef _hoops_GSRAH
		_hoops_ICRAH = _hoops_RIRAH;
#endif // _hoops_IIRAH

		// _hoops_RSRAH _hoops_RH _hoops_SRHR _hoops_PGRR _hoops_HGAS?
		if (dx9data->_hoops_RHH.w != _hoops_CCRAH ||
			dx9data->_hoops_RHH.h != _hoops_SCRAH ||
			dx9data->_hoops_RHH._hoops_GCH != _hoops_GCH) {
			// _hoops_HRHP _hoops_PIAH _hoops_AI
			for (i = 0 ; i < _hoops_APRRR ; i++) {
				_hoops_HP (_hoops_IPRRR[i]);
				_hoops_HP (_hoops_CPRRR[i]);
			}
			// _hoops_CHSR _hoops_PIAH _hoops_SAAP
			H_SAFE_RELEASE (dx9data->_hoops_RHH.msaa_target);
			dx9data->_hoops_RHH.w = _hoops_CCRAH;
			dx9data->_hoops_RHH.h = _hoops_SCRAH;
			dx9data->_hoops_RHH._hoops_GCH = _hoops_GCH;
		}

		// _hoops_IIPP _hoops_AHCR _hoops_AI
		for (i = 0 ; i < _hoops_ICRAH; i++) {
			if (!_hoops_IPRRR[i]) {
				_hoops_IA = dx9data->_hoops_GSCR->CreateTexture(_hoops_CCRAH, _hoops_SCRAH, 1,
					H3DTEXUSAGE_RENDERTARGET, _hoops_GCH, &_hoops_IPRRR[i]);
			}
		}

		// _hoops_IIPP _hoops_RGPP _hoops_AI
		for (i = 0 ; i < _hoops_RIRAH ; i++) {
			if (!_hoops_CPRRR[i]) {
				result = dx9data->_hoops_GSCR->CreateTexture(_hoops_CCRAH, _hoops_SCRAH, 1,
					H3DTEXUSAGE_RENDERTARGET, H3DFMT_A8R8G8B8, &_hoops_CPRRR[i]);
				if (!result) {
					if (i > 0)
						_hoops_RIRAH = i;
					else
						_hoops_IA = false;
				}
			}
		}

		// _hoops_CGP _hoops_HAHH, _hoops_ARPR _hoops_RRGS _hoops_SAAP - _hoops_SRGS _hoops_IS _hoops_RRGS _hoops_SAAP _hoops_PPR _hoops_IPS/_hoops_SCPP _hoops_IS _hoops_HH
		if (_hoops_ISARR) {
			if (!dx9data->_hoops_RHH.msaa_target) {
				_hoops_IIRHP = dx9data->pDevice->CreateRenderTarget(_hoops_CCRAH, _hoops_SCRAH, D3DFMT_A8R8G8B8,
						(D3DMULTISAMPLE_TYPE) dx9data->_hoops_ISGRR, 0, FALSE, &dx9data->_hoops_RHH.msaa_target, null);
				if (!SUCCEEDED(_hoops_IIRHP)) {
					_hoops_IA = false;
				}
			}
		}
	}

	// _hoops_RAPRH _hoops_SCH _hoops_IPHR?
	if (!_hoops_IA)
	{
		//
		// _hoops_CSH: _hoops_SP _hoops_GH, _hoops_PSCR _hoops_HSSC _hoops_ISSC _hoops_IS _hoops_RSRA-_hoops_ASAH. _hoops_CSH _hoops_PPSR _hoops_GGR _hoops_ASRAH _hoops_RH _hoops_AARAR
		// _hoops_SR _hoops_PSRAH _hoops_IS _hoops_CCPP _hoops_CR _hoops_SR _hoops_PIHA _hoops_AIAH _hoops_SHH _hoops_HISAR _hoops_GPP _hoops_PPGS _hoops_PPR _hoops_SR _hoops_PAH'_hoops_RA _hoops_SGH _hoops_CAPR.
		//

		// _hoops_HRHP _hoops_PIAH _hoops_AI
		for (i = 0 ; i < _hoops_APRRR ; i++) {
			_hoops_HP(_hoops_IPRRR[i]);
			_hoops_HP(_hoops_CPRRR[i]);
		}
		
		// _hoops_CHSR _hoops_PIAH _hoops_SAAP
		H_SAFE_RELEASE (dx9data->_hoops_RHH.msaa_target);

		// _hoops_HSRAH
		H3D_TRACE(dx9data, "layer 1 depth peeling");
		HD_Std_Depth_Peeling (dc);
		return;
	}

	//
	// _hoops_ICPA _hoops_HGSR
	//

	//_hoops_PRPP _hoops_SIAC _hoops_ACPP _hoops_HIS _hoops_SGS _hoops_GCAC _hoops_HCPH _hoops_CHR _hoops_RCAC _hoops_IS _hoops_SSS
	H3D_TRACE(dx9data, "depth_peeling");

	// _hoops_IRSC _hoops_ARI _hoops_GPP, _hoops_SRCH _hoops_RCCS-_hoops_ACCS _hoops_PCCS _hoops_AHI.
	H3D_LONG_OPERATION(dc);

	// _hoops_CSH _hoops_RRI _hoops_RSIH-_hoops_ISRAH _hoops_SSRR, _hoops_HIS _hoops_SR _hoops_PAH _hoops_ASCRH _hoops_RH _hoops_CSRAH _hoops_HIGR.
	dc->_hoops_GPSS[dc->_hoops_IASS] = null;

	/* _hoops_PCSA _hoops_SRGS _hoops_HCSS*/
	_hoops_PPRS _hoops_HPRS;
	dx9data->_hoops_GSCR->_hoops_IPRS(&_hoops_HPRS);

	/* _hoops_CHSR _hoops_ICIH */
	H3DViewport _hoops_SSRAH = dx9data->_hoops_CSC->_hoops_CSAA;
	/*_hoops_GGAAH._hoops_SPCR = _hoops_CSPH->_hoops_RGAAH._hoops_RAAP;
	_hoops_GGAAH._hoops_GHCR = _hoops_CSPH->_hoops_RGAAH._hoops_PRPC;
	_hoops_GGAAH._hoops_AGAAH = _hoops_CSPH->_hoops_RGAAH._hoops_RPHR - _hoops_CSPH->_hoops_RGAAH._hoops_RAAP + 1;
	_hoops_GGAAH._hoops_PGAAH = _hoops_CSPH->_hoops_RGAAH._hoops_SCIA - _hoops_CSPH->_hoops_RGAAH._hoops_PRPC + 1;*/

	// _hoops_PS _hoops_CHR _hoops_HA _hoops_GGR _hoops_ICH _hoops_CCH.
	dx9data->_hoops_RHH.mode = true;
	dx9data->_hoops_RHH.flags = 0;
	dx9data->_hoops_RHH._hoops_ACH = _hoops_ACH;

	_hoops_CPPRR(dx9data, true);

	dc->flags |= _hoops_ICPGR;

	// _hoops_GRSH _hoops_AHSC _hoops_HRGR _hoops_RH _hoops_CISI _hoops_ISPH?
	extent = &list->nr->_hoops_SAIR->_hoops_PHRA;
	_hoops_IAAIP = extent->left;
	_hoops_CAAIP = extent->bottom;
	width = extent->right - extent->left + 1;
	height = extent->top - extent->bottom + 1;

	if (dc->_hoops_PHAGH < 0)
		_hoops_AIRAH = -(int)dc->_hoops_PHAGH;
	else
		_hoops_AIRAH = (int)(dc->_hoops_PHAGH * width * height / 100.0f);

	//
	// _hoops_RAH _hoops_CIGS _hoops_APSP _hoops_SRHR _hoops_HGSR.
	//

	// _hoops_CRSR _hoops_SRHR _hoops_IS _hoops_SGH? _hoops_HGAAH _hoops_IS _hoops_SGH _hoops_SCGR _hoops_SRHR _hoops_HRII _hoops_HSAR _hoops_HPRGR _hoops_SPR, _hoops_HIS _hoops_SGS _hoops_RPP _hoops_SR'_hoops_ASAR 
	// _hoops_IHGS _hoops_PIGS _hoops_HPP _hoops_IRS _hoops_CHIR, _hoops_SR _hoops_HGCR _hoops_RH _hoops_RPHR _hoops_HHAP. _hoops_HSHCR _hoops_GGR _hoops_RRGS _hoops_CCH _hoops_SGS _hoops_PPPPR'_hoops_RA _hoops_IPHR _hoops_CCGR
	// _hoops_CH _hoops_CHR _hoops_GACC _hoops_RRGS - _hoops_HAR _hoops_GAPR _hoops_HGPS.
	IDirect3DSurface9 *dummy_buffer = _hoops_ISARR ? _hoops_PIARH(dx9data->render_target) : _hoops_PIARH(_hoops_HPRS._hoops_PGRGR[0]);
	IDirect3DSurface9 *depth_stencil = _hoops_ISARR ? _hoops_PIARH(dx9data->depth_stencil) : _hoops_PIARH(_hoops_HPRS.depth_stencil);

	/* _hoops_RAP _hoops_HGSI _hoops_ACGGR _hoops_PPR _hoops_HCH _hoops_SRHR. */
	_hoops_GPAP(*dx9data, dummy_buffer, depth_stencil);

	{
		H3D_TRACE(dx9data, "dp render to stencil");
		dx9data->_hoops_RHH._hoops_PPSP = true;
		/* _hoops_PGSA _hoops_CRGR _hoops_RH _hoops_APSP _hoops_SRHR _hoops_IS _hoops_RPR _hoops_RH _hoops_PHI _hoops_IIGR _hoops_IACH _hoops_GRR _hoops_AIR
		   _hoops_HRGR _hoops_RHIAA _hoops_HPP _hoops_CPHP _hoops_RRH. */
		_hoops_RPAP (dx9data, FALSE);
		ENSURE_TRANSPARENCY (dx9data, FALSE);
		_hoops_ICHH(dx9data, TRUE);
		_hoops_RRHRR(dx9data, 0x007F); 
		_hoops_PAHRR(
			dx9data,
			H3DSTENCILOP_KEEP, /* _hoops_AA _hoops_ISAP _hoops_RPP _hoops_APSP _hoops_RPGP _hoops_ISHS */
			H3DSTENCILOP_KEEP, /* _hoops_AA _hoops_ISAP _hoops_RPP _hoops_HCH _hoops_RPGP _hoops_ISHS */
			H3DSTENCILOP_INCR  /* _hoops_GPISR _hoops_APSP _hoops_SRHR _hoops_RPP _hoops_HCH _hoops_RPGP _hoops_PCGGR */
		);
		/* _hoops_RGAR _hoops_GPISR _hoops_APSP _hoops_CGPR _hoops_ASSA _hoops_IRS _hoops_HSPH _hoops_ISPH */
		_hoops_SRHRR(dx9data, H3DCMP_EQUAL); 
		_hoops_HRHRR(dx9data, _hoops_SRIH);
		_hoops_RGSS(dx9data, _hoops_SRIH);
		
		/* _hoops_CAAA _hoops_HCH _hoops_IS _hoops_IRS _hoops_APSP _hoops_RPR _hoops_IIGR _hoops_RRH _hoops_RSSI _hoops_HPGR _hoops_GRR _hoops_AIR. */

		/* _hoops_PPSI 1'_hoops_GRI _hoops_CRGR _hoops_RH _hoops_AAPA _hoops_IGRH (_hoops_GHCA _hoops_SHH _hoops_GCGSP _hoops_SPHR _hoops_HPP _hoops_HSPH _hoops_PGHH),
		   _hoops_PPR 0'_hoops_GRI _hoops_CRGR _hoops_RH _hoops_GSSC _hoops_SIH */
		_hoops_IIRHP = dx9data->pDevice->Clear(0, null, D3DCLEAR_STENCIL, 0, 1.0f, _hoops_SRIH);

		dx9data->_hoops_RSHH = _hoops_CCC;

		// _hoops_GISP _hoops_IS _hoops_APSP _hoops_RGAR
		HD_Draw_Deferred_3D_Geometry (list, true);
		dx9data->_hoops_RHH._hoops_PPSP = false;
		_hoops_SSRAH = dx9data->_hoops_CSC->_hoops_CSAA;
	}

	//
	// _hoops_RGHSP _hoops_ICH _hoops_HAPR. _hoops_AGHP _hoops_IGAAH.
	//

	// _hoops_IPRP _hoops_APSP 
	_hoops_PAHRR(dx9data, H3DSTENCILOP_KEEP, H3DSTENCILOP_KEEP, H3DSTENCILOP_KEEP);

	// _hoops_IPRP _hoops_HAIR _hoops_PPR _hoops_HCH _hoops_CIGCP
	_hoops_RPAP (dx9data, TRUE);
	_hoops_GPRP(dx9data, H3DMASK_RGBA);
	ENSURE_DEPTH_MASK (dx9data, TRUE);
	_hoops_PISP (dx9data, TRUE);

	/* _hoops_HPPP _hoops_IGAAH */
	for (i=0; i<_hoops_RIRAH; i++) {
		void *			_hoops_CGAAH = null;
		int				result = 0;

		// _hoops_CRSR _hoops_AHCR _hoops_HH _hoops_RGR _hoops_GHIR?
		int				z = i % _hoops_ICRAH;

		// _hoops_IPCP _hoops_CGHI _hoops_ASAH _hoops_HRGR _hoops_HA _hoops_RGR _hoops_SPR.
		_hoops_PIRAH = i;

		/* _hoops_ASSS _hoops_GRR _hoops_AIR _hoops_IS _hoops_SHH _hoops_RHIAA _hoops_RGAR _hoops_GAR _hoops_AHPH _hoops_IACH _hoops_GAR _hoops_SR _hoops_SGAAH */
		_hoops_SRHRR(dx9data, H3DCMP_LESS);
		_hoops_HRHRR(dx9data, (DWORD)(i | 0x80));
		_hoops_RGSS(dx9data, 0x00FF);

		if (_hoops_AIRAH > 0)
			_hoops_CGAAH = _hoops_AACGH (list->nr, false);

		if (_hoops_ACH) {

			H3D_TRACE(dx9data, "dp single pass");
			//
			// _hoops_GRAAH _hoops_RIH _hoops_GRP _hoops_RIAP.
			//

			// _hoops_CAAP _hoops_AHCR _hoops_IS _hoops_RSSR.
			_hoops_GPAP(*dx9data, _hoops_SHARH(_hoops_IPRRR[z]), depth_stencil);
			dx9data->pDevice->Clear(0, null, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff), 1.0f, 0);

			// _hoops_CAAP _hoops_GISH _hoops_IS _hoops_CIGC
			_hoops_GPAP(*dx9data, _hoops_SHARH(_hoops_CPRRR[i]));
			dx9data->pDevice->Clear(0, null, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0x00, 0x00, 0x00, 0x00), 0, 0);

			// _hoops_RAP _hoops_AHCR _hoops_ISSC _hoops_GPP _hoops_ACGGR 1
			_hoops_GPAP(*dx9data, _hoops_SHARH(_hoops_CPRRR[i]), depth_stencil, _hoops_SHARH(_hoops_IPRRR[z]));

			_hoops_PPHH(dx9data, _hoops_SSRAH.X, _hoops_SSRAH.Y, _hoops_SSRAH.Width, _hoops_SSRAH.Height);

			// _hoops_PGII _hoops_IGAAH _hoops_GGI _hoops_HCH
			dx9data->_hoops_RHH.flags = H3DID_DEPTH_WRITING;

			// _hoops_PGPR _hoops_IGAAH _hoops_RAS _hoops_RH _hoops_SRS _hoops_SGH _hoops_RH _hoops_HCH _hoops_IS _hoops_RRAAH
			if ( i ) 
				dx9data->_hoops_RHH.flags |= H3DID_DEPTH_PEELING;

			// _hoops_GISP _hoops_RH _hoops_RRH _hoops_CPAP
			dx9data->_hoops_RPCI = _hoops_CCC;
			HD_Draw_Deferred_3D_Geometry (list, false);
		}
		else {

			H3D_TRACE(dx9data, "dp two pass");

			{
				H3D_TRACE( dx9data, "dp colour" );

				//
				// _hoops_CHPR 1: _hoops_PCSS _hoops_GISH
				// 

				// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_GRP _hoops_RRGS
				if (_hoops_ISARR) {
					// _hoops_GCRR _hoops_RRGS _hoops_SAAP _hoops_SCGR
					_hoops_GPAP(*dx9data, dx9data->_hoops_RHH.msaa_target, depth_stencil);
				}
				else {
					// _hoops_GCRR _hoops_GISH _hoops_SAAP _hoops_SCGR
					_hoops_GPAP(*dx9data, _hoops_SHARH(_hoops_CPRRR[i]), depth_stencil);
				}

		 		// _hoops_CICR _hoops_GGI _hoops_GISH _hoops_RH _hoops_SRS _hoops_GHIR, _hoops_RRAAH _hoops_GPP _hoops_SPHR _hoops_IGAAH
				dx9data->_hoops_RHH.flags = i ? H3DID_DEPTH_PEELING : 0;

				// _hoops_CAAP _hoops_IS _hoops_RRH/_hoops_RSSR
				dx9data->pDevice->Clear(0, null, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

				_hoops_PPHH(dx9data, _hoops_SSRAH.X, _hoops_SSRAH.Y, _hoops_SSRAH.Width, _hoops_SSRAH.Height);

				// _hoops_GISP _hoops_RH _hoops_RRH _hoops_CPAP
				dx9data->_hoops_RPCI = _hoops_CCC;
				HD_Draw_Deferred_3D_Geometry (list, false);

				if (_hoops_ISARR) {
					// _hoops_PGIP _hoops_PPR _hoops_ASAC _hoops_GISH
					_hoops_HGIP(dx9data->pDevice, dx9data->_hoops_RHH.msaa_target, _hoops_CPRRR[i]);
				}

			}

			{
				H3D_TRACE( dx9data, "dp depth" );

				//
				// _hoops_CHPR 2: _hoops_PCSS _hoops_HCH
				//

				if (_hoops_ISARR) {
					// _hoops_GCRR _hoops_RRGS _hoops_SAAP _hoops_SCGR
					_hoops_GPAP(*dx9data, dx9data->_hoops_RHH.msaa_target, depth_stencil);
				}
				else {
					// _hoops_GCRR _hoops_AHCR _hoops_HH _hoops_SCGR
					_hoops_GPAP(*dx9data, _hoops_SHARH(_hoops_IPRRR[z]), depth_stencil);
				}

		 		_hoops_PPHH(dx9data, _hoops_SSRAH.X, _hoops_SSRAH.Y, _hoops_SSRAH.Width, _hoops_SSRAH.Height);

				// _hoops_IISH _hoops_HCH, _hoops_RRAAH _hoops_GAR _hoops_PRAR _hoops_RPP _hoops_ARP _hoops_ARRS
				dx9data->_hoops_RHH.flags |= H3DID_DEPTH_WRITING;

				// _hoops_CAAP _hoops_IS _hoops_RSSR. _hoops_CAIP'_hoops_RA _hoops_RRP _hoops_IS _hoops_ASAR-_hoops_SCAC _hoops_SSH _hoops_SRHR _hoops_CR _hoops_CRGP-_hoops_SASPR _hoops_HCH _hoops_RPGP _hoops_GRS _hoops_IPHR _hoops_IH _hoops_IHHH.
				dx9data->pDevice->Clear(0, null, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00), 1.0f, 0);

				// _hoops_GISP _hoops_RH _hoops_RRH _hoops_CPAP
				dx9data->_hoops_RPCI = _hoops_CCC;
				HD_Draw_Deferred_3D_Geometry (list, false);

				if (_hoops_ISARR) {
					// _hoops_PGIP _hoops_PPR _hoops_ASAC _hoops_AHCR
					_hoops_HGIP(dx9data->pDevice, dx9data->_hoops_RHH.msaa_target, _hoops_IPRRR[z]);
				}
			}
		}

		// _hoops_ASAP _hoops_IAGP _hoops_RACGH _hoops_PPR _hoops_GAAP _hoops_RSIH-_hoops_GGSR.
		if (_hoops_CGAAH) {
			_hoops_PACGH (list->nr, _hoops_CGAAH);
			result = _hoops_IACGH (list->nr, _hoops_CGAAH);
			_hoops_CACGH (list->nr, _hoops_CGAAH);
		}
		if (result < _hoops_AIRAH)
			break;

		// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_ARAAH, _hoops_SGH _hoops_RGR _hoops_AHCR _hoops_HH _hoops_SPS _hoops_GHIR.
		dx9data->_hoops_RHH._hoops_HPRRR = _hoops_IPRRR[z];
	}

	// _hoops_CSH _hoops_RPIP _hoops_ICH
	dx9data->_hoops_RHH.mode = false;
	dx9data->_hoops_RHH.flags = 0;
	dx9data->_hoops_RHH._hoops_HPRRR = null;

	{
		//
		// _hoops_PRAAH _hoops_RH _hoops_IGAAH _hoops_CRGR _hoops_PCCP _hoops_CSCR.
		//

		H3D_TRACE( dx9data, "dp draw layers" );

		// _hoops_IPRP _hoops_AISH _hoops_PPR _hoops_HCH _hoops_APSP _hoops_ISSGR.
		dx9data->_hoops_GSCR->_hoops_CHRS(&_hoops_HPRS);

		/* _hoops_CPRP _hoops_CCAH _hoops_RRRH _hoops_IAPR _hoops_GIGR _hoops_IS _hoops_HGCR _hoops_RH _hoops_GHPP */
		_hoops_PPRP (dx9data, H3DBLEND_SRCALPHA, H3DBLEND_INVSRCALPHA);
		ENSURE_TRANSPARENCY (dx9data, true);  
		_hoops_ICHH (dx9data, false);

		// _hoops_SSSA _hoops_CARP _hoops_PCRR _hoops_IH _hoops_HH
		_hoops_ACCRR = (_hoops_IAAIP + 0.5f) / (float)_hoops_PCRAH;
		_hoops_PCCRR = (_hoops_IAAIP + (width-1) + 0.5f) / (float)_hoops_PCRAH;

		_hoops_ISPI = (_hoops_HCRAH - _hoops_CAAIP - (height-1) + 0.5f) / (float)_hoops_HCRAH;
		_hoops_CSPI = (_hoops_HCRAH - _hoops_CAAIP + 0.5f) / (float)_hoops_HCRAH;

		// _hoops_GISP _hoops_HCR _hoops_IGAAH _hoops_GGR _hoops_PIIA _hoops_AGR.
		_hoops_GPRP (dx9data, (dx9data->_hoops_SH.mode ? H3DMASK_RGBA : H3DMASK_RGB));
		for (i=_hoops_PIRAH; i>=0; i--) {
			dx9data->_hoops_GSCR->_hoops_GHIP(dx9data, _hoops_CPRRR[i], _hoops_IAAIP, _hoops_CAAIP, (width-1), (height-1), _hoops_ACCRR, _hoops_ISPI, _hoops_PCCRR, _hoops_CSPI);
		}

		// _hoops_IPRP _hoops_CPRP _hoops_CCH
		ENSURE_TRANSPARENCY (dx9data, false);  
	}

#ifdef _hoops_GSRAH

	{
		H3D_TRACE( dx9data, "dp debug layers" );

		//
		// _hoops_PPSRR _hoops_GISS _hoops_RRGR
		//

		// _hoops_HRAAH _hoops_IGAAH _hoops_GGSR _hoops_ARHI _hoops_RH _hoops_CRRPA
		const int _hoops_IRAAH = (extent->right - extent->left)/(_hoops_RIRAH*2);

		for (i=_hoops_PIRAH; i>=0; i--) {
			dx9data->_hoops_GSCR->_hoops_GHIP(dx9data, _hoops_CPRRR[i], _hoops_IAAIP + i * _hoops_IRAAH, _hoops_CAAIP, _hoops_IRAAH, _hoops_IRAAH);
		}

		for (i=0; i < _hoops_ICRAH; ++i) {
			dx9data->_hoops_GSCR->_hoops_GHIP(dx9data, _hoops_IPRRR[i], _hoops_IAAIP + i * _hoops_IRAAH, _hoops_CAAIP + _hoops_IRAAH, _hoops_IRAAH, _hoops_IRAAH);
		}
	}

#endif // _hoops_IIRAH

	for (i = 0 ; i < 8 ; i++) {
		_hoops_ASRP(dx9data, i);
	}

	/* _hoops_HCR _hoops_CPHR _hoops_CCA _hoops_RGR _hoops_HIGR _hoops_IIGR _hoops_RRH _hoops_IGCGA */
	HD_Free_Deferred_3D_Geometry (list);

} //_hoops_RSGR _hoops_API '_hoops_HCH _hoops_ICH'




/*****************************************************************************
*****************************************************************************
						_hoops_CRAAH _hoops_PPR _hoops_SRAAH
*****************************************************************************
*****************************************************************************/


/*
* _hoops_SRAC
* _hoops_IPCP _hoops_GRGPR _hoops_IIGR _hoops_RGR _hoops_PCPH _hoops_HRGR _hoops_GIIA _hoops_HPP _hoops_GAAAH.
* _hoops_HGI _hoops_PCPH _hoops_RAAAH _hoops_RH _hoops_CIACP _hoops_IIGR _hoops_RH _hoops_RII _hoops_SRAC _hoops_SICAR.
*/
local void _hoops_RSCSR (_hoops_APARR alter & _hoops_RRCI)
{

	/* _hoops_SISS _hoops_GASCA _hoops_CIPH */
	_hoops_RRCI->start_device = start_device;
	_hoops_RRCI->stop_device = stop_device;
	_hoops_RRCI->get_physical_info = get_physical_info;
	_hoops_RRCI->get_current_info = get_current_info;
	_hoops_RRCI->get_outer_window = get_outer_window;
	_hoops_RRCI->free_outer_window = free_outer_window;
	_hoops_RRCI->_hoops_ASCSP = _hoops_ASCSP;
	_hoops_RRCI->_hoops_RSCSP = _hoops_RSCSP;

	_hoops_RRCI->init_update = init_update;
	_hoops_RRCI->finish_update = finish_update;
	_hoops_RRCI->init_picture = init_picture;
	_hoops_RRCI->_hoops_PCPGR = _hoops_PCPGR;
	_hoops_RRCI->finish_picture = finish_picture;

	_hoops_RRCI->_hoops_CAAGR = _hoops_CAAGR;
	_hoops_RRCI->_hoops_CHCI = segment_render;

	/* _hoops_CIIA _hoops_SICAR */
	_hoops_RRCI->_hoops_HSCSP = _hoops_HSCSP;
	_hoops_RRCI->_hoops_ISCSP = _hoops_ISCSP;

	_hoops_RRCI->draw_overlay_list = draw_overlay_list;
	_hoops_RRCI->_hoops_SCPGR = _hoops_SCPGR;

	/* _hoops_PGSA _hoops_SICAR */
	_hoops_RRCI->draw_dc_rgb32_rasters = draw_dc_rgb32_rasters;
	_hoops_RRCI->draw_dc_rectangle = draw_dc_rectangle;
	_hoops_RRCI->draw_dc_polyline = draw_dc_polyline;
	_hoops_RRCI->draw_dc_gouraud_polyline = draw_dc_gouraud_polyline;
	_hoops_RRCI->draw_dc_colorized_polytriangle = draw_dc_colorized_polytriangle;
	_hoops_RRCI->draw_dc_polytriangle = draw_dc_polytriangle;
	_hoops_RRCI->draw_dc_gouraud_polytriangle = draw_dc_gouraud_polytriangle;
	_hoops_RRCI->draw_dc_textured_polytriangle = draw_dc_textured_polytriangle;
	_hoops_RRCI->draw_dc_polydot = draw_dc_polydot;
	_hoops_RRCI->draw_dc_colorized_polydot = draw_dc_colorized_polydot;

	_hoops_RRCI->draw_3d_tristrip = draw_3d_tristrip;
	_hoops_RRCI->draw_3d_polygon = draw_3d_polygon;
	_hoops_RRCI->draw_3d_polyedge = draw_3d_polyedge;
	_hoops_RRCI->draw_3d_polyline = draw_3d_polyline;
	_hoops_RRCI->_hoops_ARCI = _hoops_ARCI;
	_hoops_RRCI->_hoops_PPAS = _hoops_PPAS;
	_hoops_RRCI->draw_3d_polymarker = draw_3d_polymarker;
	_hoops_RRCI->draw_3d_marker = draw_3d_marker; 
	_hoops_RRCI->draw_3d_grid = draw_3d_grid;
	_hoops_RRCI->draw_3d_text = draw_3d_text;
	_hoops_RRCI->draw_3d_image = draw_3d_image;
	
	//_hoops_HPGR->_hoops_AAAAH = _hoops_AAAAH; 
	//_hoops_HPGR->_hoops_PAAAH = _hoops_PAAAH;

	_hoops_RRCI->_hoops_AICI = _hoops_AICI;
	_hoops_RRCI->_hoops_GGSI = _hoops_GGSI;
	_hoops_RRCI->_hoops_AIGC = _hoops_AIGC;
	_hoops_RRCI->_hoops_PPCI = _hoops_PPCI;

	_hoops_RRCI->_hoops_SSRGR = _hoops_SSRGR;

	/*_hoops_HRCSR _hoops_PRCA */
	_hoops_RRCI->measure_char = measure_char;
	_hoops_RRCI->_hoops_AACSR = _hoops_AACSR;
	_hoops_RRCI->_hoops_CACSR = _hoops_CACSR;
	_hoops_RRCI->find_all_fonts = find_all_fonts;
	_hoops_RRCI->load_font = load_font;
	_hoops_RRCI->unload_font = unload_font;
	_hoops_RRCI->_hoops_CSCSP = _hoops_CSCSP;
	_hoops_RRCI->_hoops_RGSSP = _hoops_RGSSP;

	/* _hoops_ISPH _hoops_SICAR */
	_hoops_RRCI->_hoops_CGAGR = _hoops_CGAGR;
	_hoops_RRCI->snapshot = snapshot;	// _hoops_RGHP _hoops_IH _hoops_HAAAH _hoops_SHPR _hoops_HSRPR
	_hoops_RRCI->create_region = create_region;
	_hoops_RRCI->_hoops_HIPGR = _hoops_HIPGR;
	_hoops_RRCI->_hoops_PIPGR = _hoops_PIPGR;
	_hoops_RRCI->_hoops_ISPGR = _hoops_ISPGR;
	_hoops_RRCI->_hoops_CSPGR = _hoops_CSPGR;
	_hoops_RRCI->_hoops_AGHGR = _hoops_AGHGR;

	/* _hoops_IAGP _hoops_RACGH _hoops_SICAR */
	_hoops_RRCI->_hoops_GRSSP = _hoops_GRSSP;
	_hoops_RRCI->_hoops_RRSSP = _hoops_RRSSP;
	_hoops_RRCI->_hoops_CRGIP = _hoops_CRGIP;
	_hoops_RRCI->_hoops_ARSSP = _hoops_ARSSP;

	_hoops_RRCI->_hoops_RHH = _hoops_RHH;
	_hoops_RRCI->_hoops_PICS = _hoops_PICS;
	_hoops_RRCI->_hoops_IPSS = _hoops_IPSS;
	_hoops_RRCI->_hoops_GHGGR = _hoops_GHGGR;

	_hoops_RRCI->_hoops_IGHGR = _hoops_IGHGR;
}/* _hoops_RSGR _hoops_API _hoops_SRAAH */


/*
* _hoops_IAAAH _hoops_PPICR
*/
extern "C"  bool HC_CDECL HD_DX9_Driver (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (request_info);
	return HD_Connect_Standard_Driver (_hoops_RIGC, _hoops_GHRI, request, _hoops_RSCSR);
}

/*
* _hoops_ASCSR _hoops_RARP _hoops_PPSR (_hoops_IGI _hoops_GPP _hoops_PSCSR)
*/
_hoops_HSCSR (_hoops_RSCSR)

#endif  /* _hoops_PHARH */


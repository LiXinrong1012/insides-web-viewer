/*
 * Copyright (c) 2006 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.19 2010-09-22 02:29:38 trask Exp $
 */


#if defined(DX9_DRIVER)

//-----------------------------------------------------------------------------
// _hoops_SPSSA: _hoops_GHSSA._hoops_CRSC
//
// _hoops_RHSSA: _hoops_HPRHP _hoops_CIGR _hoops_PPR _hoops_PSCH _hoops_IH _hoops_GRP _hoops_IPRHP _hoops_AGSAR
//-----------------------------------------------------------------------------
#define _hoops_CPRHP
#include "windows_wrapper.h"	// _hoops_CGRI <_hoops_SPHGR._hoops_GGHR>, _hoops_PIHA _hoops_RCPS _hoops_SRS :(
#include <WindowsX.h>
#include "d3dutil.h"
#include "hoops.h"


//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_ACSSA()
// _hoops_RHSSA: _hoops_PCSSA _hoops_IRS _hoops_HCSSA _hoops_HRPR, _hoops_RGSR _hoops_RH _hoops_SPI _hoops_PPR _hoops_AASR
//		 _hoops_PSHA. _hoops_HHIGR _hoops_RHAP _hoops_HAR _hoops_ARP _hoops_APGA _hoops_PAR _hoops_GHI _hoops_PSHA.
//-----------------------------------------------------------------------------
VOID D3DUtil_InitMaterial(D3DMATERIAL9& _hoops_ICSSA, FLOAT r, FLOAT g, FLOAT b,
						   FLOAT a)
{
	ZeroMemory(&_hoops_ICSSA, sizeof(D3DMATERIAL9));
	_hoops_ICSSA.Diffuse.r = _hoops_ICSSA.Ambient.r = r;
	_hoops_ICSSA.Diffuse.g = _hoops_ICSSA.Ambient.g = g;
	_hoops_ICSSA.Diffuse.b = _hoops_ICSSA.Ambient.b = b;
	_hoops_ICSSA.Diffuse.a = _hoops_ICSSA.Ambient.a = a;
}




//-----------------------------------------------------------------------------
// _hoops_SPSSA: _hoops_ARGGP._hoops_CRSC
//
// _hoops_RHSSA: _hoops_PRGGP _hoops_RAPA _hoops_HRGGP, _hoops_AGSHA, _hoops_CAPRR, _hoops_AHI.
//-----------------------------------------------------------------------------
#define _hoops_CPRHP


//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_SPRHP
// _hoops_RHSSA: _hoops_GCAAA _hoops_RH _hoops_PHI _hoops_IIGR _hoops_HAIR _hoops_RCAP _hoops_SIH _hoops_GGR _hoops_RH _hoops_CHIA _hoops_GHRHP
//-----------------------------------------------------------------------------
UINT _hoops_IRGGP(D3DFORMAT fmt)
{
	switch (fmt)
	{
		case D3DFMT_R8G8B8:
			return 8;
		case D3DFMT_A8R8G8B8:
			return 8;
		case D3DFMT_X8R8G8B8:
			return 8;
		case D3DFMT_R5G6B5:
			return 5;
		case D3DFMT_X1R5G5B5:
			return 5;
		case D3DFMT_A1R5G5B5:
			return 5;
		case D3DFMT_A4R4G4B4:
			return 4;
		case D3DFMT_R3G3B2:
			return 2;
		case D3DFMT_A8R3G3B2:
			return 2;
		case D3DFMT_X4R4G4B4:
			return 4;
		case D3DFMT_A2B10G10R10:
			return 10;
		case D3DFMT_A2R10G10B10:
			return 10;
		default:
			return 0;
	}
}




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_RHRHP
// _hoops_RHSSA: _hoops_GCAAA _hoops_RH _hoops_PHI _hoops_IIGR _hoops_AIIR _hoops_RCAP _hoops_SIH _hoops_GGR _hoops_RH _hoops_CHIA _hoops_GHRHP
//-----------------------------------------------------------------------------
UINT _hoops_CRGGP(D3DFORMAT fmt)
{
	switch (fmt)
	{
		case D3DFMT_R8G8B8:
			return 0;
		case D3DFMT_A8R8G8B8:
			return 8;
		case D3DFMT_X8R8G8B8:
			return 0;
		case D3DFMT_R5G6B5:
			return 0;
		case D3DFMT_X1R5G5B5:
			return 0;
		case D3DFMT_A1R5G5B5:
			return 1;
		case D3DFMT_A4R4G4B4:
			return 4;
		case D3DFMT_R3G3B2:
			return 0;
		case D3DFMT_A8R3G3B2:
			return 8;
		case D3DFMT_X4R4G4B4:
			return 0;
		case D3DFMT_A2B10G10R10:
			return 2;
		case D3DFMT_A2R10G10B10:
			return 2;
		default:
			return 0;
	}
}




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_AHRHP
// _hoops_RHSSA: _hoops_GCAAA _hoops_RH _hoops_PHI _hoops_IIGR _hoops_HCH _hoops_SIH _hoops_GGR _hoops_RH _hoops_CHIA _hoops_GHRHP
//-----------------------------------------------------------------------------
UINT _hoops_SRGGP(D3DFORMAT fmt)
{
	switch (fmt)
	{
		case D3DFMT_D16:
			return 16;
		case D3DFMT_D15S1:
			return 15;
		case D3DFMT_D24X8:
			return 24;
		case D3DFMT_D24S8:
			return 24;
		case D3DFMT_D24X4S4:
			return 24;
		case D3DFMT_D32:
			return 32;
		default:
			return 0;
	}
}




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_PHRHP
// _hoops_RHSSA: _hoops_GCAAA _hoops_RH _hoops_PHI _hoops_IIGR _hoops_APSP _hoops_SIH _hoops_GGR _hoops_RH _hoops_CHIA _hoops_GHRHP
//-----------------------------------------------------------------------------
UINT _hoops_GAGGP(D3DFORMAT fmt)
{
	switch (fmt)
	{
		case D3DFMT_D16:
			return 0;
		case D3DFMT_D15S1:
			return 1;
		case D3DFMT_D24X8:
			return 0;
		case D3DFMT_D24S8:
			return 8;
		case D3DFMT_D24X4S4:
			return 4;
		case D3DFMT_D32:
			return 0;
		default:
			return 0;
	}
}




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_GPGGP _hoops_CCPSA
// _hoops_RHSSA: 
//-----------------------------------------------------------------------------
D3DAdapterInfo::~D3DAdapterInfo(void)
{
	if (_hoops_IPGGP != NULL)
		delete _hoops_IPGGP;
	if (_hoops_SPGGP != NULL)
	{
		for (UINT _hoops_HHRHP = 0; _hoops_HHRHP < _hoops_SPGGP->Count(); _hoops_HHRHP++)
			delete (D3DDeviceInfo*)_hoops_SPGGP->_hoops_GRGGP(_hoops_HHRHP);
		delete _hoops_SPGGP;
	}
}




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_GHGGP _hoops_CCPSA
// _hoops_RHSSA: 
//-----------------------------------------------------------------------------
D3DDeviceInfo::~D3DDeviceInfo(void)
{
	if (_hoops_HHGGP != NULL)
	{
		for (UINT _hoops_IHRHP = 0; _hoops_IHRHP < _hoops_HHGGP->Count(); _hoops_IHRHP++)
			delete (D3DDeviceCombo*)_hoops_HHGGP->_hoops_GRGGP(_hoops_IHRHP);
		delete _hoops_HHGGP;
	}
}


//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_IHGGP _hoops_CCPSA
// _hoops_RHSSA: 
//-----------------------------------------------------------------------------
D3DDeviceCombo::~D3DDeviceCombo(void)
{
	if (_hoops_SIGGP != NULL)
		delete _hoops_SIGGP;
	if (_hoops_RCGGP != NULL)
		delete _hoops_RCGGP;
	if (_hoops_PCGGP != NULL)
		delete _hoops_PCGGP;
	if (_hoops_ICGGP != NULL)
		delete _hoops_ICGGP;
	if (_hoops_SCGGP != NULL)
		delete _hoops_SCGGP;
	if (_hoops_RSGGP != NULL)
		delete _hoops_RSGGP;
}



//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_GGRGP _hoops_PPII
// _hoops_RHSSA: 
//-----------------------------------------------------------------------------
_hoops_RGRGP::_hoops_RGRGP()
{
	_hoops_PRRGP = NULL;
	_hoops_PPRGP = NULL;
	_hoops_SRRGP = 640;
	_hoops_GARGP = 480;
	_hoops_RARGP = 5;
	_hoops_AARGP = 0;
	_hoops_PARGP = 15;
	_hoops_HARGP = 0;
	_hoops_IARGP = true;
	_hoops_CARGP = false;
	_hoops_RPRGP = false;
	_hoops_APRGP = false;
	_hoops_CRRGP = NULL;
}




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_GGRGP _hoops_CCPSA
// _hoops_RHSSA: 
//-----------------------------------------------------------------------------
_hoops_RGRGP::~_hoops_RGRGP()
{
	if (_hoops_PRRGP != NULL)
	{
		for (UINT _hoops_CHRHP = 0; _hoops_CHRHP < _hoops_PRRGP->Count(); _hoops_CHRHP++)
			delete (D3DAdapterInfo*)_hoops_PRRGP->_hoops_GRGGP(_hoops_CHRHP);
		delete _hoops_PRRGP;
	}
	_hoops_HP(_hoops_PPRGP);
}




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_SHRHP
// _hoops_RHSSA: _hoops_GSAH _hoops_IS _hoops_GHIS _hoops_CPGGP
//-----------------------------------------------------------------------------
static int __cdecl _hoops_GIRHP(const void* _hoops_RIRHP, const void* _hoops_AIRHP)
{
	D3DDISPLAYMODE* _hoops_PIRHP = (D3DDISPLAYMODE*)_hoops_RIRHP;
	D3DDISPLAYMODE* _hoops_HIRHP = (D3DDISPLAYMODE*)_hoops_AIRHP;

	if (_hoops_PIRHP->Width > _hoops_HIRHP->Width)
		return 1;
	if (_hoops_PIRHP->Width < _hoops_HIRHP->Width)
		return -1;
	if (_hoops_PIRHP->Height > _hoops_HIRHP->Height)
		return 1;
	if (_hoops_PIRHP->Height < _hoops_HIRHP->Height)
		return -1;
	if (_hoops_PIRHP->Format > _hoops_HIRHP->Format)
		return 1;
	if (_hoops_PIRHP->Format < _hoops_HIRHP->Format)
		return -1;
	if (_hoops_PIRHP->RefreshRate > _hoops_HIRHP->RefreshRate)
		return 1;
	if (_hoops_PIRHP->RefreshRate < _hoops_HIRHP->RefreshRate)
		return -1;
	return 0;
}




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_IRRGP
// _hoops_RHSSA: _hoops_PRGGP _hoops_HHPA _hoops_RAPA _hoops_HRGGP, _hoops_AGSHA, _hoops_CAPRR, _hoops_AHI.
//-----------------------------------------------------------------------------
HRESULT _hoops_RGRGP::_hoops_IPRGP()
{
	HRESULT _hoops_IIRHP = S_OK;
	_hoops_SSSSA _hoops_CIRHP(_hoops_ISSSA, sizeof(D3DFORMAT));

	D3DPERF_BeginEvent(0, L"enumerate");

	if (m_pD3D == NULL) {
		_hoops_IIRHP = E_FAIL;
		goto done;
	}

	_hoops_PRRGP = new _hoops_SSSSA(AL_REFERENCE);
	if (_hoops_PRRGP == NULL) {
		_hoops_IIRHP = E_OUTOFMEMORY;
		goto done;
	}

	_hoops_PPRGP = new _hoops_SSSSA(_hoops_ISSSA, sizeof(D3DFORMAT));
	if (_hoops_PPRGP == NULL) {
		_hoops_IIRHP = E_OUTOFMEMORY;
		goto done;
	}
	D3DFORMAT fmt;
	if (FAILED(_hoops_IIRHP = _hoops_PPRGP->_hoops_AHSH(&(fmt = D3DFMT_X8R8G8B8))))
		goto done;
	if (FAILED(_hoops_IIRHP = _hoops_PPRGP->_hoops_AHSH(&(fmt = D3DFMT_X1R5G5B5))))
		goto done;
	if (FAILED(_hoops_IIRHP = _hoops_PPRGP->_hoops_AHSH(&(fmt = D3DFMT_R5G6B5))))
		goto done;
	if (FAILED(_hoops_IIRHP = _hoops_PPRGP->_hoops_AHSH(&(fmt = D3DFMT_A2R10G10B10))))
		goto done;

	D3DAdapterInfo* _hoops_PGRGP = NULL;
	UINT _hoops_SIRHP = m_pD3D->GetAdapterCount();

	for (UINT adapterOrdinal = 0; adapterOrdinal < _hoops_SIRHP; adapterOrdinal++)
	{
		_hoops_PGRGP = new D3DAdapterInfo;
		if (_hoops_PGRGP == NULL) {
			_hoops_IIRHP = E_OUTOFMEMORY;
			goto done;
		}
		_hoops_PGRGP->_hoops_IPGGP = new _hoops_SSSSA(_hoops_ISSSA, sizeof(D3DDISPLAYMODE)); 
		_hoops_PGRGP->_hoops_SPGGP = new _hoops_SSSSA(AL_REFERENCE);
		if (_hoops_PGRGP->_hoops_IPGGP == NULL ||
			_hoops_PGRGP->_hoops_SPGGP == NULL)
		{
			delete _hoops_PGRGP;
			_hoops_IIRHP = E_OUTOFMEMORY;
			goto done;
		}
		_hoops_PGRGP->_hoops_PPGGP = adapterOrdinal;
		m_pD3D->GetAdapterIdentifier(adapterOrdinal, 0, &_hoops_PGRGP->_hoops_HPGGP);

		// _hoops_SIPR _hoops_HIGR _hoops_IIGR _hoops_HCR _hoops_AIRI _hoops_CAPRR _hoops_GPP _hoops_RGR _hoops_APGGP.  
		// _hoops_HIPR _hoops_RIPHR _hoops_IRS _hoops_AH _hoops_HIGR _hoops_IIGR _hoops_HCR _hoops_AIRI _hoops_APGGP _hoops_AGHS.
		_hoops_CIRHP.Clear();
		for (UINT iaaf = 0; iaaf < _hoops_PPRGP->Count(); iaaf++)
		{
			D3DFORMAT _hoops_GCRHP = *(D3DFORMAT*)_hoops_PPRGP->_hoops_GRGGP(iaaf);
			UINT _hoops_RCRHP = m_pD3D->GetAdapterModeCount(adapterOrdinal, _hoops_GCRHP);
			for (UINT mode = 0; mode < _hoops_RCRHP; mode++)
			{
				D3DDISPLAYMODE displayMode;
				m_pD3D->EnumAdapterModes(adapterOrdinal, _hoops_GCRHP, mode, &displayMode);
				if (displayMode.Width < _hoops_SRRGP ||
					displayMode.Height < _hoops_GARGP ||
					_hoops_IRGGP(displayMode.Format) < _hoops_RARGP)
				{
					continue;
				}
				_hoops_PGRGP->_hoops_IPGGP->_hoops_AHSH(&displayMode);
				if (!_hoops_CIRHP._hoops_HPCIR(&displayMode.Format))
					_hoops_CIRHP._hoops_AHSH(&displayMode.Format);
			}
		}

		// _hoops_ASHPR _hoops_ACRHP _hoops_HIGR
		qsort(_hoops_PGRGP->_hoops_IPGGP->_hoops_GRGGP(0), 
			_hoops_PGRGP->_hoops_IPGGP->Count(), sizeof(D3DDISPLAYMODE),
			_hoops_GIRHP);

		// _hoops_SIPR _hoops_SIHC _hoops_IH _hoops_GRR _hoops_SISS _hoops_GPP _hoops_RGR _hoops_APGGP
		if (FAILED(_hoops_IIRHP = _hoops_AGRGP(_hoops_PGRGP, &_hoops_CIRHP)))
		{
			delete _hoops_PGRGP;
			goto done;
		}

		// _hoops_CGP _hoops_HPGR _hoops_CHGC _hoops_SPR _hoops_SISS _hoops_GPP _hoops_RGR _hoops_APGGP _hoops_HRGR _hoops_HHPA _hoops_PPR _hoops_PIGGP
		// _hoops_CCA _hoops_RH _hoops_HIGGP, _hoops_GGCR _hoops_RH _hoops_PCRHP _hoops_IS _hoops_RH _hoops_HIGR
		if (_hoops_PGRGP->_hoops_SPGGP->Count() == 0)
			delete _hoops_PGRGP;
		else
			_hoops_PRRGP->_hoops_AHSH(_hoops_PGRGP);
	}

done:
	D3DPERF_EndEvent();

	return _hoops_IIRHP;
}




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_HCRHP
// _hoops_RHSSA: _hoops_PRGGP _hoops_RAPA _hoops_AGSHA _hoops_IH _hoops_IRS _hoops_SAGHR _hoops_APGGP.
//-----------------------------------------------------------------------------
HRESULT _hoops_RGRGP::_hoops_AGRGP(D3DAdapterInfo* _hoops_PGRGP, 
										   _hoops_SSSSA* _hoops_HGRGP)
{
	const D3DDEVTYPE _hoops_ICRHP[] = { D3DDEVTYPE_HAL, D3DDEVTYPE_SW, D3DDEVTYPE_REF };
	const UINT _hoops_CCRHP = sizeof(_hoops_ICRHP) / sizeof(_hoops_ICRHP[0]);
	HRESULT _hoops_IIRHP;

	D3DDeviceInfo* _hoops_CGRGP = NULL;
	for (UINT _hoops_SCRHP = 0; _hoops_SCRHP < _hoops_CCRHP; _hoops_SCRHP++)
	{
		_hoops_CGRGP = new D3DDeviceInfo;
		if (_hoops_CGRGP == NULL)
			return E_OUTOFMEMORY;
		_hoops_CGRGP->_hoops_HHGGP = new _hoops_SSSSA(AL_REFERENCE); 
		if (_hoops_CGRGP->_hoops_HHGGP == NULL)
		{
			delete _hoops_CGRGP;
			return E_OUTOFMEMORY;
		}
		_hoops_CGRGP->_hoops_PPGGP = _hoops_PGRGP->_hoops_PPGGP;
		_hoops_CGRGP->_hoops_PHGGP = _hoops_ICRHP[_hoops_SCRHP];
		if (FAILED(m_pD3D->GetDeviceCaps(_hoops_PGRGP->_hoops_PPGGP, 
			_hoops_CGRGP->_hoops_PHGGP, &_hoops_CGRGP->Caps)))
		{
			delete _hoops_CGRGP;
			continue;
		}

		// _hoops_SIPR _hoops_SIHC _hoops_IH _hoops_GRR _hoops_GSRHP _hoops_GPP _hoops_RGR _hoops_SISS
		if (FAILED(_hoops_IIRHP = _hoops_IGRGP(_hoops_CGRGP, _hoops_HGRGP)))
		{
			delete _hoops_CGRGP;
			return _hoops_IIRHP;
		}

		// _hoops_CGP _hoops_HPGR _hoops_CHGC _hoops_SPR _hoops_GSRHP _hoops_IH _hoops_RGR _hoops_SISS _hoops_HRGR _hoops_GSGI, 
		// _hoops_GGCR _hoops_RH _hoops_RSRHP _hoops_IS _hoops_RH _hoops_HIGR
		if (_hoops_CGRGP->_hoops_HHGGP->Count() == 0)
		{
			delete _hoops_CGRGP;
			continue;
		}
		_hoops_PGRGP->_hoops_SPGGP->_hoops_AHSH(_hoops_CGRGP);
	}
	return S_OK;
}




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_ASRHP
// _hoops_RHSSA: _hoops_PRGGP _hoops_PSRHP _hoops_IH _hoops_IRS _hoops_SAGHR _hoops_SISS.
//-----------------------------------------------------------------------------
HRESULT _hoops_RGRGP::_hoops_IGRGP(D3DDeviceInfo* _hoops_CGRGP, 
											   _hoops_SSSSA* _hoops_HGRGP)
{
	const D3DFORMAT _hoops_HSRHP[] = 
		{	D3DFMT_A8R8G8B8, D3DFMT_X8R8G8B8, D3DFMT_A2R10G10B10, 
			D3DFMT_R5G6B5, D3DFMT_A1R5G5B5, D3DFMT_X1R5G5B5 };
	const UINT _hoops_ISRHP = sizeof(_hoops_HSRHP) / sizeof(_hoops_HSRHP[0]);
	bool _hoops_CSRHP[] = { false, true };

	// _hoops_AIHH _hoops_PGAP _hoops_APGGP _hoops_AGHS _hoops_CHR _hoops_APP _hoops_HPP _hoops_RGR _hoops_SISS
	D3DFORMAT _hoops_CSGGP;
	for (UINT _hoops_SSRHP = 0; _hoops_SSRHP < _hoops_HGRGP->Count(); _hoops_SSRHP++)
	{
		_hoops_CSGGP = *(D3DFORMAT*)_hoops_HGRGP->_hoops_GRGGP(_hoops_SSRHP);
		D3DFORMAT _hoops_SSGGP;
		for (UINT _hoops_GGAHP = 0; _hoops_GGAHP < _hoops_ISRHP; _hoops_GGAHP++)
		{
			_hoops_SSGGP = _hoops_HSRHP[_hoops_GGAHP];
			if (_hoops_CRGGP(_hoops_SSGGP) < _hoops_AARGP)
				continue;
			bool _hoops_RGAHP;
			for (UINT _hoops_AGAHP = 0; _hoops_AGAHP < 2; _hoops_AGAHP++)
			{
				_hoops_RGAHP = _hoops_CSRHP[_hoops_AGAHP];
				if (!_hoops_RGAHP && _hoops_RPRGP)
					continue;
				if (_hoops_RGAHP && _hoops_APRGP)
					continue;
				if (FAILED(m_pD3D->CheckDeviceType(_hoops_CGRGP->_hoops_PPGGP, _hoops_CGRGP->_hoops_PHGGP, 
					_hoops_CSGGP, _hoops_SSGGP, _hoops_RGAHP)))
				{
					continue;
				}
				// _hoops_RHRPA _hoops_RGR _hoops_PPSR, _hoops_SR _hoops_HS _hoops_PCCP _hoops_APGGP/_hoops_SISS/_hoops_PGAHP/_hoops_HGAHP/_hoops_IGAHP
				// _hoops_CGAHP _hoops_SGS _hoops_HRGR _hoops_APP _hoops_HPP _hoops_RH _hoops_GHARR.	 _hoops_PS _hoops_HGGC _hoops_RRP _hoops_IS _hoops_RHAHA _hoops_SGS _hoops_SCH'_hoops_GRI 
				// _hoops_PIGGP _hoops_CCA _hoops_RH _hoops_HIGGP, _hoops_PPR _hoops_SSS _hoops_SPR _hoops_PAR _hoops_RRI _hoops_GHRP _hoops_HCH/_hoops_APSP _hoops_SRHR _hoops_RPCC,
				// _hoops_IIGAR _hoops_GPRR, _hoops_GPHA _hoops_PHSPR _hoops_GPRR, _hoops_PPR _hoops_GPRI _hoops_SGAHP.
				D3DDeviceCombo* _hoops_GRRGP = NULL;
				_hoops_GRRGP = new D3DDeviceCombo;
				if (_hoops_GRRGP == NULL)
					return E_OUTOFMEMORY;
				_hoops_GRRGP->_hoops_SIGGP = new _hoops_SSSSA(_hoops_ISSSA, sizeof(D3DFORMAT));
				_hoops_GRRGP->_hoops_RCGGP = new _hoops_SSSSA(_hoops_ISSSA, sizeof(D3DMULTISAMPLE_TYPE));
				_hoops_GRRGP->_hoops_PCGGP = new _hoops_SSSSA(_hoops_ISSSA, sizeof(DWORD));
				_hoops_GRRGP->_hoops_ICGGP = new _hoops_SSSSA(_hoops_ISSSA, sizeof(D3DDSMSConflict));
				_hoops_GRRGP->_hoops_SCGGP = new _hoops_SSSSA(_hoops_ISSSA, sizeof(_hoops_PAGGP));
				_hoops_GRRGP->_hoops_RSGGP = new _hoops_SSSSA(_hoops_ISSSA, sizeof(UINT));
				if (_hoops_GRRGP->_hoops_SIGGP == NULL ||
					_hoops_GRRGP->_hoops_RCGGP == NULL || 
					_hoops_GRRGP->_hoops_PCGGP == NULL || 
					_hoops_GRRGP->_hoops_ICGGP == NULL || 
					_hoops_GRRGP->_hoops_SCGGP == NULL ||
					_hoops_GRRGP->_hoops_RSGGP == NULL)
				{
					delete _hoops_GRRGP;
					return E_OUTOFMEMORY;
				}
				_hoops_GRRGP->_hoops_PPGGP = _hoops_CGRGP->_hoops_PPGGP;
				_hoops_GRRGP->_hoops_PHGGP = _hoops_CGRGP->_hoops_PHGGP;
				_hoops_GRRGP->_hoops_IIGGP = _hoops_CSGGP;
				_hoops_GRRGP->BackBufferFormat = _hoops_SSGGP;
				_hoops_GRRGP->_hoops_CIGGP = _hoops_RGAHP;
				if (_hoops_IARGP)
				{
					_hoops_SGRGP(_hoops_GRRGP);
					if (_hoops_GRRGP->_hoops_SIGGP->Count() == 0)
					{
						delete _hoops_GRRGP;
						continue;
					}
				}
				BuildMultiSampleTypeList(_hoops_GRRGP);
				if (_hoops_GRRGP->_hoops_RCGGP->Count() == 0)
				{
					delete _hoops_GRRGP;
					continue;
				}
				BuildDSMSConflictList(_hoops_GRRGP);
				_hoops_RRRGP(_hoops_CGRGP, _hoops_GRRGP);
				if (_hoops_GRRGP->_hoops_SCGGP->Count() == 0)
				{
					delete _hoops_GRRGP;
					continue;
				}
				_hoops_ARRGP(_hoops_CGRGP, _hoops_GRRGP);

				_hoops_CGRGP->_hoops_HHGGP->_hoops_AHSH(_hoops_GRRGP);
			}
		}
	}

	return S_OK;
}




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_GRAHP
// _hoops_RHSSA: _hoops_RRAHP _hoops_HCR _hoops_HCH/_hoops_APSP _hoops_AGHS _hoops_SGS _hoops_CHR _hoops_PIGGP _hoops_CCA _hoops_RH _hoops_SISS 
//		 _hoops_PPR _hoops_HIGGP _hoops_IS _hoops_RH _hoops_RAGA _hoops_IHGGP.
//-----------------------------------------------------------------------------
void _hoops_RGRGP::_hoops_SGRGP(D3DDeviceCombo* _hoops_GRRGP)
{
	const D3DFORMAT _hoops_ARAHP[] = 
	{
		D3DFMT_D32,
		D3DFMT_D24S8,
		D3DFMT_D24X8,
		D3DFMT_D24X4S4,
		D3DFMT_D16,
		D3DFMT_D15S1,
	};
	const UINT _hoops_PRAHP = sizeof(_hoops_ARAHP) / 
											  sizeof(_hoops_ARAHP[0]);

	D3DFORMAT _hoops_HRAHP;
	for (UINT _hoops_IRAHP = 0; _hoops_IRAHP < _hoops_PRAHP; _hoops_IRAHP++)
	{
		_hoops_HRAHP = _hoops_ARAHP[_hoops_IRAHP];
		if (_hoops_SRGGP(_hoops_HRAHP) < _hoops_PARGP)
			continue;
		if (_hoops_GAGGP(_hoops_HRAHP) < _hoops_HARGP)
			continue;
		if (SUCCEEDED(m_pD3D->CheckDeviceFormat(_hoops_GRRGP->_hoops_PPGGP, 
			_hoops_GRRGP->_hoops_PHGGP, _hoops_GRRGP->_hoops_IIGGP, 
			D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, _hoops_HRAHP)))
		{
			if (SUCCEEDED(m_pD3D->CheckDepthStencilMatch(_hoops_GRRGP->_hoops_PPGGP, 
				_hoops_GRRGP->_hoops_PHGGP, _hoops_GRRGP->_hoops_IIGGP, 
				_hoops_GRRGP->BackBufferFormat, _hoops_HRAHP)))
			{
				_hoops_GRRGP->_hoops_SIGGP->_hoops_AHSH(&_hoops_HRAHP);
			}
		}
	}
}




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_CRAHP
// _hoops_RHSSA: _hoops_RRAHP _hoops_HCR _hoops_IIGAR _hoops_CSSC _hoops_SGS _hoops_CHR _hoops_PIGGP _hoops_CCA _hoops_RH _hoops_SISS _hoops_PPR _hoops_HIGGP _hoops_IS
//		 _hoops_RH _hoops_RAGA _hoops_IHGGP.
//-----------------------------------------------------------------------------
void _hoops_RGRGP::BuildMultiSampleTypeList(D3DDeviceCombo* _hoops_GRRGP)
{
	const D3DMULTISAMPLE_TYPE _hoops_SRAHP[] = { 
		D3DMULTISAMPLE_NONE,
		D3DMULTISAMPLE_NONMASKABLE,
		D3DMULTISAMPLE_2_SAMPLES,
		D3DMULTISAMPLE_3_SAMPLES,
		D3DMULTISAMPLE_4_SAMPLES,
		D3DMULTISAMPLE_5_SAMPLES,
		D3DMULTISAMPLE_6_SAMPLES,
		D3DMULTISAMPLE_7_SAMPLES,
		D3DMULTISAMPLE_8_SAMPLES,
		D3DMULTISAMPLE_9_SAMPLES,
		D3DMULTISAMPLE_10_SAMPLES,
		D3DMULTISAMPLE_11_SAMPLES,
		D3DMULTISAMPLE_12_SAMPLES,
		D3DMULTISAMPLE_13_SAMPLES,
		D3DMULTISAMPLE_14_SAMPLES,
		D3DMULTISAMPLE_15_SAMPLES,
		D3DMULTISAMPLE_16_SAMPLES,
	};
	const UINT _hoops_GAAHP = sizeof(_hoops_SRAHP) / sizeof(_hoops_SRAHP[0]);

	D3DMULTISAMPLE_TYPE _hoops_RAAHP;
	DWORD _hoops_AAAHP;
	for (UINT _hoops_PAAHP = 0; _hoops_PAAHP < _hoops_GAAHP; _hoops_PAAHP++)
	{
		_hoops_RAAHP = _hoops_SRAHP[_hoops_PAAHP];
		if (SUCCEEDED(m_pD3D->CheckDeviceMultiSampleType(_hoops_GRRGP->_hoops_PPGGP, _hoops_GRRGP->_hoops_PHGGP, 
			_hoops_GRRGP->BackBufferFormat, _hoops_GRRGP->_hoops_CIGGP, _hoops_RAAHP, &_hoops_AAAHP)))
		{
			_hoops_GRRGP->_hoops_RCGGP->_hoops_AHSH(&_hoops_RAAHP);
			_hoops_GRRGP->_hoops_PCGGP->_hoops_AHSH(&_hoops_AAAHP);
		}
	}
}




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_HAAHP
// _hoops_RHSSA: _hoops_ACGR _hoops_GII _hoops_SPIH _hoops_GAPA _hoops_RH _hoops_HHPA _hoops_HCH/_hoops_APSP _hoops_AGHS _hoops_PPR
//		 _hoops_IIGAR _hoops_CSSC.
//-----------------------------------------------------------------------------
void _hoops_RGRGP::BuildDSMSConflictList(D3DDeviceCombo* _hoops_GRRGP)
{
	D3DDSMSConflict _hoops_IAAHP;

	for (UINT _hoops_GPICA = 0; _hoops_GPICA < _hoops_GRRGP->_hoops_SIGGP->Count(); _hoops_GPICA++)
	{
		D3DFORMAT _hoops_CAAHP = *(D3DFORMAT*)_hoops_GRRGP->_hoops_SIGGP->_hoops_GRGGP(_hoops_GPICA);
		for (UINT _hoops_SAAHP = 0; _hoops_SAAHP < _hoops_GRRGP->_hoops_RCGGP->Count(); _hoops_SAAHP++)
		{
			D3DMULTISAMPLE_TYPE _hoops_RAAHP = *(D3DMULTISAMPLE_TYPE*)_hoops_GRRGP->_hoops_RCGGP->_hoops_GRGGP(_hoops_SAAHP);
			if (FAILED(m_pD3D->CheckDeviceMultiSampleType(_hoops_GRRGP->_hoops_PPGGP, _hoops_GRRGP->_hoops_PHGGP,
				_hoops_CAAHP, _hoops_GRRGP->_hoops_CIGGP, _hoops_RAAHP, NULL)))
			{
				_hoops_IAAHP._hoops_GIGGP = _hoops_CAAHP;
				_hoops_IAAHP._hoops_RIGGP = _hoops_RAAHP;
				_hoops_GRRGP->_hoops_ICGGP->_hoops_AHSH(&_hoops_IAAHP);
			}
		}
	}
}




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_GPAHP
// _hoops_RHSSA: _hoops_RRAHP _hoops_HCR _hoops_GPHA _hoops_PHSPR _hoops_CSSC _hoops_SGS _hoops_CHR _hoops_PIGGP _hoops_CCA _hoops_RH _hoops_SISS 
//		 _hoops_PPR _hoops_HIGGP _hoops_IS _hoops_RH _hoops_RAGA _hoops_IHGGP.
//-----------------------------------------------------------------------------
void _hoops_RGRGP::_hoops_RRRGP(D3DDeviceInfo* _hoops_CGRGP, 
													 D3DDeviceCombo* _hoops_GRRGP)
{
	_hoops_PAGGP _hoops_RPAHP;
	if ((_hoops_CGRGP->Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) != 0)
	{
		if ((_hoops_CGRGP->Caps.DevCaps & D3DDEVCAPS_PUREDEVICE) != 0)
		{
			if (_hoops_CRRGP == NULL ||
				_hoops_CRRGP(&_hoops_CGRGP->Caps, _hoops_SAGGP, 
				_hoops_GRRGP->_hoops_IIGGP, _hoops_GRRGP->BackBufferFormat))
			{
				_hoops_RPAHP = _hoops_SAGGP;
				_hoops_GRRGP->_hoops_SCGGP->_hoops_AHSH(&_hoops_RPAHP);
			}
		}
		if (_hoops_CRRGP == NULL ||
			_hoops_CRRGP(&_hoops_CGRGP->Caps, _hoops_CAGGP, 
			_hoops_GRRGP->_hoops_IIGGP, _hoops_GRRGP->BackBufferFormat))
		{
			_hoops_RPAHP = _hoops_CAGGP;
			_hoops_GRRGP->_hoops_SCGGP->_hoops_AHSH(&_hoops_RPAHP);
		}
		if (_hoops_CARGP && (_hoops_CRRGP == NULL ||
			_hoops_CRRGP(&_hoops_CGRGP->Caps, _hoops_IAGGP, 
			_hoops_GRRGP->_hoops_IIGGP, _hoops_GRRGP->BackBufferFormat)))
		{
			_hoops_RPAHP = _hoops_IAGGP;
			_hoops_GRRGP->_hoops_SCGGP->_hoops_AHSH(&_hoops_RPAHP);
		}
	}
	if (_hoops_CRRGP == NULL ||
		_hoops_CRRGP(&_hoops_CGRGP->Caps, _hoops_HAGGP, 
		_hoops_GRRGP->_hoops_IIGGP, _hoops_GRRGP->BackBufferFormat))
	{
		_hoops_RPAHP = _hoops_HAGGP;
		_hoops_GRRGP->_hoops_SCGGP->_hoops_AHSH(&_hoops_RPAHP);
	}
}




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_APAHP
// _hoops_RHSSA: _hoops_RRAHP _hoops_HCR _hoops_GPRI _hoops_PPAHP _hoops_SGS _hoops_CHR _hoops_PIGGP _hoops_CCA _hoops_RH _hoops_SISS _hoops_PPR _hoops_HIGGP 
//		 _hoops_IS _hoops_RH _hoops_RAGA _hoops_IHGGP.
//-----------------------------------------------------------------------------
void _hoops_RGRGP::_hoops_ARRGP(D3DDeviceInfo* _hoops_CGRGP, 
												D3DDeviceCombo* _hoops_GRRGP)
{
	const UINT _hoops_HPAHP[] = { 
		D3DPRESENT_INTERVAL_IMMEDIATE,
		D3DPRESENT_INTERVAL_DEFAULT,
		D3DPRESENT_INTERVAL_ONE,
		D3DPRESENT_INTERVAL_TWO,
		D3DPRESENT_INTERVAL_THREE,
		D3DPRESENT_INTERVAL_FOUR,
	};
	const UINT _hoops_IPAHP = sizeof(_hoops_HPAHP) / sizeof(_hoops_HPAHP[0]);

	UINT _hoops_CHPC;
	for (UINT _hoops_CPAHP = 0; _hoops_CPAHP < _hoops_IPAHP; _hoops_CPAHP++)
	{
		_hoops_CHPC = _hoops_HPAHP[_hoops_CPAHP];
		if (_hoops_GRRGP->_hoops_CIGGP)
		{
			if (_hoops_CHPC == D3DPRESENT_INTERVAL_TWO ||
				_hoops_CHPC == D3DPRESENT_INTERVAL_THREE ||
				_hoops_CHPC == D3DPRESENT_INTERVAL_FOUR)
			{
				// _hoops_ASC _hoops_PPAHP _hoops_CHR _hoops_HAR _hoops_APP _hoops_GGR _hoops_AISIR _hoops_CCH.
				continue;
			}
		}
		// _hoops_PAGA _hoops_SGS _hoops_SPAHP _hoops_HRGR _hoops_AHHR, _hoops_HIS _hoops_RHAC
		// _hoops_PAH'_hoops_RA _hoops_AA _hoops_IRS _hoops_RIRR _hoops_ISPR _hoops_IH _hoops_SCH -- _hoops_SCH _hoops_HRGR _hoops_SHR _hoops_HHPA.
		if (_hoops_CHPC == D3DPRESENT_INTERVAL_DEFAULT ||
			(_hoops_CGRGP->Caps.PresentationIntervals & _hoops_CHPC))
		{
			_hoops_GRRGP->_hoops_RSGGP->_hoops_AHSH(&_hoops_CHPC);
		}
	}
}

//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_GHAHP()
// _hoops_RHSSA: _hoops_RHAHP _hoops_API _hoops_IGI _hoops_HPP _hoops_ARGGP
//-----------------------------------------------------------------------------
bool _hoops_CPRGP(D3DCAPS9* _hoops_HSGGP, _hoops_PAGGP _hoops_ISGGP,
							D3DFORMAT _hoops_CSGGP, D3DFORMAT _hoops_SSGGP)
{
	DWORD _hoops_AHAHP;

	if (_hoops_ISGGP == _hoops_HAGGP)
		_hoops_AHAHP = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	else if (_hoops_ISGGP == _hoops_IAGGP)
		_hoops_AHAHP = D3DCREATE_MIXED_VERTEXPROCESSING;
	else if (_hoops_ISGGP == _hoops_CAGGP)
		_hoops_AHAHP = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else if (_hoops_ISGGP == _hoops_SAGGP)
		_hoops_AHAHP = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE;
	else
		_hoops_AHAHP = 0; // _hoops_SIGP: _hoops_RSRHR _hoops_GSASR

	// _hoops_RPCS _hoops_IS _hoops_CRIGR/_hoops_PHAHP, _hoops_RPP _hoops_SR....

	// ..._hoops_AA _hoops_HAR _hoops_HS _hoops_HHAHP _hoops_RPGP _hoops_IHAHP
	if (!(_hoops_HSGGP->RasterCaps & D3DPRASTERCAPS_SCISSORTEST))
		return false;

	UNREFERENCED (_hoops_CSGGP);
	UNREFERENCED (_hoops_SSGGP);

	return true;
}

//-----------------------------------------------------------------------------
// _hoops_SPSSA: _hoops_SPRGP._hoops_CRSC
//
// _hoops_RHSSA: _hoops_GHRGP _hoops_CSHGR _hoops_PPR _hoops_AGRP-_hoops_HRP _hoops_RHRGP _hoops_CSHGR _hoops_IH _hoops_RH _hoops_HHSSA 
//		 _hoops_IGPR _hoops_AHRGP _hoops_GIRPR.
//-----------------------------------------------------------------------------
#define _hoops_CPRHP

//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_PSSSA _hoops_PPII
// _hoops_RHSSA: 
//-----------------------------------------------------------------------------
_hoops_SSSSA::_hoops_SSSSA(_hoops_HSSSA Type, UINT _hoops_IGGGP)
{
	if (Type == AL_REFERENCE)
		_hoops_IGGGP = sizeof(void*);
	_hoops_GGGGP = Type;
	_hoops_RGGGP = NULL;
	_hoops_AGGGP = _hoops_IGGGP;
	_hoops_PGGGP = 0;
	_hoops_HGGGP = 0;
}



//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_PSSSA _hoops_CCPSA
// _hoops_RHSSA: 
//-----------------------------------------------------------------------------
_hoops_SSSSA::~_hoops_SSSSA(void)
{
	if (_hoops_RGGGP != NULL)
		delete[] _hoops_RGGGP;
}




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_PSSSA::_hoops_RGPA
// _hoops_RHSSA: _hoops_RRAHP _hoops_CHAHP _hoops_IS _hoops_RH _hoops_HIGR.
//-----------------------------------------------------------------------------
HRESULT _hoops_SSSSA::_hoops_AHSH(void* _hoops_CGGGP)
{
	if (_hoops_AGGGP == 0)
		return E_FAIL;
	if (_hoops_RGGGP == NULL || _hoops_PGGGP + 1 > _hoops_HGGGP)
	{
		void* _hoops_SHAHP;
		UINT _hoops_GIAHP;
		if (_hoops_HGGGP == 0)
			_hoops_GIAHP = 16;
		else
			_hoops_GIAHP = _hoops_HGGGP * 2;
		_hoops_SHAHP = new BYTE[_hoops_GIAHP * _hoops_AGGGP];
		if (_hoops_SHAHP == NULL)
			return E_OUTOFMEMORY;
		if (_hoops_RGGGP != NULL)
		{
			CopyMemory(_hoops_SHAHP, _hoops_RGGGP, _hoops_PGGGP * _hoops_AGGGP);
			delete[] _hoops_RGGGP;
		}
		_hoops_RGGGP = _hoops_SHAHP;
		_hoops_HGGGP = _hoops_GIAHP;
	}

	if (_hoops_GGGGP == _hoops_ISSSA)
		CopyMemory((BYTE*)_hoops_RGGGP + (_hoops_PGGGP * _hoops_AGGGP), _hoops_CGGGP, _hoops_AGGGP);
	else
		*(((void**)_hoops_RGGGP) + _hoops_PGGGP) = _hoops_CGGGP;
	_hoops_PGGGP++;

	return S_OK;
}




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_PSSSA::_hoops_ACRAR
// _hoops_RHSSA: _hoops_ACRAR _hoops_RH _hoops_IGCI _hoops_HPGR _hoops_RIAHP _hoops_GGR _hoops_RH _hoops_HIGR, _hoops_PPR _hoops_GHRHA _hoops_RH _hoops_CRPR. 
//-----------------------------------------------------------------------------
void _hoops_SSSSA::Remove(UINT _hoops_SGGGP)
{
	// _hoops_AIAHP _hoops_RPR
	_hoops_PGGGP--;

	// _hoops_ACGR _hoops_RH _hoops_RARP _hoops_GRGPR
	BYTE* _hoops_PIAHP = (BYTE*)_hoops_RGGGP + (_hoops_SGGGP * _hoops_AGGGP);

	// _hoops_HIAHP _hoops_RH _hoops_CRPR
	MoveMemory(_hoops_PIAHP, _hoops_PIAHP + _hoops_AGGGP, (_hoops_PGGGP - _hoops_SGGGP) * _hoops_AGGGP);
}




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_PSSSA::_hoops_IIAHP
// _hoops_RHSSA: _hoops_GCAAA _hoops_IRS _hoops_CRS _hoops_IS _hoops_RH _hoops_RIAHP'_hoops_CRISR _hoops_RARP _hoops_GGR _hoops_RH _hoops_HIGR.
//-----------------------------------------------------------------------------
void* _hoops_SSSSA::_hoops_GRGGP(UINT _hoops_SGGGP)
{
	if (_hoops_GGGGP == _hoops_ISSSA)
		return (BYTE*)_hoops_RGGGP + (_hoops_SGGGP * _hoops_AGGGP);
	else
		return *(((void**)_hoops_RGGGP) + _hoops_SGGGP);
}




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_PSSSA::_hoops_CIAHP
// _hoops_RHSSA: _hoops_GCAAA _hoops_IGH _hoops_RH _hoops_HIGR _hoops_ICGI _hoops_PCCP _hoops_RARP _hoops_HSHPR _hoops_IS _hoops_RH 
//		 _hoops_CHIA _hoops_RARP _hoops_PIH.
//-----------------------------------------------------------------------------
bool _hoops_SSSSA::_hoops_HPCIR(void* _hoops_RRGGP)
{
	for (UINT _hoops_SIAHP = 0; _hoops_SIAHP < _hoops_PGGGP; _hoops_SIAHP++)
	{
		if (_hoops_GGGGP == _hoops_ISSSA)
		{
			if (memcmp(_hoops_GRGGP(_hoops_SIAHP), _hoops_RRGGP, _hoops_AGGGP) == 0)
				return true;
		}
		else
		{
			if (_hoops_GRGGP(_hoops_SIAHP) == _hoops_RRGGP)
				return true;
		}
	}
	return false;
}


#endif






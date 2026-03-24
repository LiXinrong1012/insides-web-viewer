/*
 * Copyright (c) 1998-2001 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.20 2010-09-22 02:29:38 trask Exp $
 */

//-----------------------------------------------------------------------------
// _hoops_SPSSA: _hoops_GHSSA._hoops_GGHR
//
// _hoops_RHSSA: _hoops_SACA _hoops_PSCH _hoops_PPR _hoops_AHSSA _hoops_PHSSA _hoops_IH _hoops_HHSSA _hoops_IHSSA.
//-----------------------------------------------------------------------------
#ifndef _hoops_CHSSA
#define _hoops_CHSSA
#ifdef _DEBUG
#ifndef D3D_DEBUG_INFO
#define D3D_DEBUG_INFO
#endif
#endif 
#include <D3D9.h>
#include <D3DX9Math.h>

struct DX9Data;

typedef struct d3d_system_data 
{
	int						ref_count;				// _hoops_CGRPR _hoops_RPR
	LPDIRECT3D9				_hoops_SHSSA;					// _hoops_RH _hoops_HGSI _hoops_RAPA _hoops_CARA
	LPDIRECT3DDEVICE9		pDevice;				// _hoops_RH _hoops_HGSI _hoops_RAPA _hoops_SISS
	DX9Data					*dx9data_list;			// _hoops_IRS _hoops_HIGR _hoops_IIGR _hoops_HCR _hoops_GISSA
	void					*_hoops_RISSA;		// _hoops_AISSA _hoops_GSSHR _hoops_IH _hoops_SGP/_hoops_PISSA _hoops_SISS
	void					*_hoops_HISSA; // _hoops_IISSA _hoops_IH _hoops_RH _hoops_SISS _hoops_AISSA
	void					*_hoops_CSC;					// _hoops_GCSP _hoops_CISSA

	LPDIRECT3DVERTEXBUFFER9 _hoops_SISSA[15];			// _hoops_IHAH _hoops_RH _hoops_SCGR _hoops_GPHA/_hoops_CIHA _hoops_SRHR
	LPDIRECT3DINDEXBUFFER9	_hoops_GCSSA;
} D3D_System_Data;


//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_ACSSA()
// _hoops_RHSSA: _hoops_PCSSA _hoops_IRS _hoops_HCSSA _hoops_HRPR, _hoops_RGSR _hoops_RH _hoops_SPI _hoops_PPR _hoops_AASR
//				 _hoops_PSHA. _hoops_HHIGR _hoops_RHAP _hoops_HAR _hoops_ARP _hoops_APGA _hoops_PAR _hoops_GHI _hoops_PSHA.
//-----------------------------------------------------------------------------
VOID D3DUtil_InitMaterial(
	D3DMATERIAL9& _hoops_ICSSA, 
	FLOAT r=0.0f, 
	FLOAT g=0.0f,
	FLOAT b=0.0f, 
	FLOAT a=1.0f);


//-----------------------------------------------------------------------------
// _hoops_SPSSA: _hoops_CCSSA._hoops_GGHR
//
// _hoops_RHSSA: _hoops_SACA _hoops_PSCH _hoops_PPR _hoops_AHSSA _hoops_PHSSA _hoops_IH _hoops_SCSSA _hoops_IHSSA.
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// _hoops_GSSSA _hoops_HICRR _hoops_PSCH
//-----------------------------------------------------------------------------
#define _hoops_HP(p)			 { if (p) { delete (p);	   (p)=null; } }
#define H_SAFE_RELEASE(p)			 { if (p) { (p)->Release(); (p)=null; } }




//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_RSSSA
// _hoops_RHSSA: _hoops_ASSSA _hoops_RSH _hoops_PIH _hoops_CGH _hoops_SHH _hoops_GCSS _hoops_GGR _hoops_IRS _hoops_PSSSA
//-----------------------------------------------------------------------------
enum _hoops_HSSSA
{
		_hoops_ISSSA,				// _hoops_RARP _hoops_PIH _hoops_HRGR _hoops_RIRRR _hoops_CRGR _hoops_RH _hoops_HIGR
		AL_REFERENCE,	// _hoops_RARP _hoops_CICRR _hoops_CHR _hoops_RIRRR _hoops_CRGR _hoops_RH _hoops_HIGR
};


//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_PSSSA
// _hoops_RHSSA: _hoops_RAIGR _hoops_CSSSA _hoops_CRPR
//-----------------------------------------------------------------------------
class _hoops_SSSSA
{
protected:
		_hoops_HSSSA _hoops_GGGGP;
		void* _hoops_RGGGP;
		UINT _hoops_AGGGP;
		UINT _hoops_PGGGP;
		UINT _hoops_HGGGP;

public:
		_hoops_SSSSA(_hoops_HSSSA Type, UINT _hoops_IGGGP = 0);
		~_hoops_SSSSA(void);
		HRESULT _hoops_AHSH(void* _hoops_CGGGP);
		void Remove(UINT _hoops_SGGGP);
		void* _hoops_GRGGP(UINT _hoops_SGGGP);
		UINT Count(void) { return _hoops_PGGGP; }
		bool _hoops_HPCIR(void* _hoops_RRGGP);
		void Clear(void) { _hoops_PGGGP = 0; }
};


//-----------------------------------------------------------------------------
// _hoops_SPSSA: _hoops_ARGGP._hoops_GGHR
//
// _hoops_RHSSA: _hoops_PRGGP _hoops_RAPA _hoops_HRGGP, _hoops_AGSHA, _hoops_CAPRR, _hoops_AHI.
//-----------------------------------------------------------------------------

extern UINT _hoops_IRGGP(D3DFORMAT fmt);
extern UINT _hoops_CRGGP(D3DFORMAT fmt);
extern UINT _hoops_SRGGP(D3DFORMAT fmt);
extern UINT _hoops_GAGGP(D3DFORMAT fmt);

//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_PHSGR _hoops_RAGGP
// _hoops_RHSSA: _hoops_AAGGP _hoops_IIGR _hoops_HCR _hoops_SSRR _hoops_RAPA _hoops_GPHA _hoops_PHSPR _hoops_CSSC.
//-----------------------------------------------------------------------------
enum _hoops_PAGGP
{
		_hoops_HAGGP,
		_hoops_IAGGP,
		_hoops_CAGGP,
		_hoops_SAGGP
};


//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_PPARR _hoops_GPGGP
// _hoops_RHSSA: _hoops_RPGGP _hoops_AHCA _hoops_IRS _hoops_AIRI _hoops_APGGP.
//-----------------------------------------------------------------------------
struct D3DAdapterInfo
{
		int _hoops_PPGGP;
		D3DADAPTER_IDENTIFIER9 _hoops_HPGGP;
		_hoops_SSSSA* _hoops_IPGGP; // _hoops_ICSH _hoops_IIGR _hoops_CPGGP
		_hoops_SSSSA* _hoops_SPGGP; // _hoops_ICSH _hoops_IIGR _hoops_GHGGP _hoops_CICRR
		~D3DAdapterInfo(void);
};


//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_PPARR _hoops_GHGGP
// _hoops_RHSSA: _hoops_RPGGP _hoops_AHCA _hoops_IRS _hoops_RAPA _hoops_SISS, _hoops_RHGGP _hoops_IRS _hoops_HIGR _hoops_IIGR _hoops_AHGGP (_hoops_CACH _hoops_CAPP) 
//				 _hoops_SGS _hoops_IPHR _hoops_CCA _hoops_RH _hoops_SISS.
//-----------------------------------------------------------------------------
struct D3DDeviceInfo
{
		int _hoops_PPGGP;
		D3DDEVTYPE _hoops_PHGGP;
		D3DCAPS9 Caps;
		_hoops_SSSSA* _hoops_HHGGP; // _hoops_ICSH _hoops_IIGR _hoops_IHGGP _hoops_CICRR
		~D3DDeviceInfo(void);
};


//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_PPARR _hoops_CHGGP
// _hoops_RHSSA: _hoops_RAIGR _hoops_HCH/_hoops_APSP _hoops_SRHR _hoops_RPCC _hoops_SGS _hoops_HRGR _hoops_SHGGP _hoops_CCA _hoops_IRS
//				 _hoops_IIGAR _hoops_GPRR.
//-----------------------------------------------------------------------------
struct D3DDSMSConflict
{
		D3DFORMAT _hoops_GIGGP;
		D3DMULTISAMPLE_TYPE _hoops_RIGGP;
};


//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_PPARR _hoops_IHGGP
// _hoops_RHSSA: _hoops_RAIGR _hoops_AARRA _hoops_IIGR _hoops_APGGP _hoops_RPCC, _hoops_ISSC _hoops_SRHR _hoops_RPCC, _hoops_PPR _hoops_AISIR/_hoops_AIGGP 
//				 _hoops_SGS _hoops_HRGR _hoops_PIGGP _hoops_CCA _hoops_IRS _hoops_SAGHR _hoops_RAPA _hoops_SISS (_hoops_PPR _hoops_RH _hoops_HIGGP).
//-----------------------------------------------------------------------------
struct D3DDeviceCombo
{
		int _hoops_PPGGP;
		D3DDEVTYPE _hoops_PHGGP;
		D3DFORMAT _hoops_IIGGP;
		D3DFORMAT BackBufferFormat;
		bool _hoops_CIGGP;
		_hoops_SSSSA* _hoops_SIGGP; // _hoops_ICSH _hoops_IIGR _hoops_GCGGP
		_hoops_SSSSA* _hoops_RCGGP; // _hoops_ICSH _hoops_IIGR _hoops_ACGGP
		_hoops_SSSSA* _hoops_PCGGP; // _hoops_ICSH _hoops_IIGR _hoops_HCGGP (_hoops_PHI _hoops_IIGR _hoops_CCGP 
																				 // _hoops_HARH _hoops_IH _hoops_GRR _hoops_IIGAR _hoops_GPRR)
		_hoops_SSSSA* _hoops_ICGGP; // _hoops_ICSH _hoops_IIGR _hoops_CCGGP
		_hoops_SSSSA* _hoops_SCGGP; // _hoops_ICSH _hoops_IIGR _hoops_GSGGP
		_hoops_SSSSA* _hoops_RSGGP; // _hoops_ICSH _hoops_IIGR _hoops_ASGGP

		~D3DDeviceCombo(void);
};


typedef bool(* _hoops_PSGGP)(D3DCAPS9* _hoops_HSGGP, _hoops_PAGGP _hoops_ISGGP, 
																				   D3DFORMAT _hoops_CSGGP, D3DFORMAT _hoops_SSGGP);



//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_CSHGR _hoops_GGRGP
// _hoops_RHSSA: _hoops_PRGGP _hoops_HHPA _hoops_RAPA _hoops_HRGGP, _hoops_AGSHA, _hoops_CAPRR, _hoops_AHI.
//-----------------------------------------------------------------------------
class _hoops_RGRGP
{
private:
		IDirect3D9* m_pD3D;

private:
		HRESULT _hoops_AGRGP(D3DAdapterInfo* _hoops_PGRGP, _hoops_SSSSA* _hoops_HGRGP);
		HRESULT _hoops_IGRGP(D3DDeviceInfo* _hoops_CGRGP, _hoops_SSSSA* _hoops_HGRGP);
		void _hoops_SGRGP(D3DDeviceCombo* _hoops_GRRGP);
		void BuildMultiSampleTypeList(D3DDeviceCombo* _hoops_GRRGP);
		void BuildDSMSConflictList(D3DDeviceCombo* _hoops_GRRGP);
		void _hoops_RRRGP(D3DDeviceInfo* _hoops_CGRGP, D3DDeviceCombo* _hoops_GRRGP);
		void _hoops_ARRGP(D3DDeviceInfo* _hoops_CGRGP, D3DDeviceCombo* _hoops_GRRGP);

public:
		_hoops_SSSSA* _hoops_PRRGP;
		// _hoops_IPCP _hoops_HSPR _hoops_CCPAR _hoops_PAH _hoops_SHH _hoops_IGI _hoops_IS _hoops_SAIPR _hoops_PCPA _hoops_CAPRR, _hoops_AGHS, 
		// _hoops_AHI. _hoops_CHR _hoops_HRRGP.	 _hoops_RAP _hoops_CAPR _hoops_IS _hoops_RH _hoops_HSH _hoops_RHAC _hoops_HHGC _hoops_ARPP _hoops_RCPH
		// _hoops_IRRGP().
		_hoops_PSGGP _hoops_CRRGP;
		UINT _hoops_SRRGP;
		UINT _hoops_GARGP;
		UINT _hoops_RARGP; // _hoops_CGGPR _hoops_HAIR _hoops_SIH _hoops_RIR _hoops_RCAP _hoops_GGR _hoops_APGGP _hoops_RPCC
		UINT _hoops_AARGP; // _hoops_CGGPR _hoops_AIIR _hoops_SIH _hoops_RIR _hoops_AIR _hoops_GGR _hoops_ISSC _hoops_SRHR _hoops_RPCC
		UINT _hoops_PARGP;
		UINT _hoops_HARGP;
		bool _hoops_IARGP;
		bool _hoops_CARGP; // _hoops_IGH _hoops_HIGGP _hoops_PAH _hoops_IRAA _hoops_SARGP _hoops_IIGR _hoops_CCPHR _hoops_GPRGP _hoops_CCH
		bool _hoops_RPRGP;
		bool _hoops_APRGP;
		_hoops_SSSSA* _hoops_PPRGP; // _hoops_HIGR _hoops_IIGR _hoops_GCGGP

		_hoops_RGRGP();
		~_hoops_RGRGP();
		void _hoops_HPRGP(IDirect3D9* _hoops_SHSSA) { m_pD3D = _hoops_SHSSA; }
		HRESULT _hoops_IPRGP();
};

extern bool _hoops_CPRGP(
	D3DCAPS9* _hoops_HSGGP, 
	_hoops_PAGGP _hoops_ISGGP,
	D3DFORMAT _hoops_CSGGP, 
	D3DFORMAT _hoops_SSGGP);

//-----------------------------------------------------------------------------
// _hoops_SPSSA: _hoops_SPRGP._hoops_GGHR
//
// _hoops_RHSSA: _hoops_GHRGP _hoops_CSHGR _hoops_PPR _hoops_AGRP-_hoops_HRP _hoops_RHRGP _hoops_CSHGR _hoops_IH _hoops_RH _hoops_HHSSA 
//				 _hoops_IGPR _hoops_AHRGP _hoops_GIRPR.
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// _hoops_RCSSA: _hoops_CSHGR _hoops_PHRGP
// _hoops_RHSSA: _hoops_RPGRR _hoops_RAPA _hoops_HRP: _hoops_APGGP, _hoops_SISS, _hoops_CCH, _hoops_AGHS, _hoops_AHI.
//-----------------------------------------------------------------------------
class _hoops_HHRGP 
{
public:
		bool _hoops_CIGGP;

		D3DAdapterInfo* _hoops_IHRGP;
		D3DDeviceInfo* _hoops_CHRGP;
		D3DDeviceCombo* _hoops_SHRGP;

		D3DDISPLAYMODE _hoops_GIRGP; // _hoops_HAR _hoops_RIRGP _hoops_HPP _hoops_RH _hoops_IPSP
		D3DFORMAT _hoops_AIRGP;
		D3DMULTISAMPLE_TYPE _hoops_PIRGP;
		DWORD _hoops_HIRGP;
		_hoops_PAGGP _hoops_IIRGP;
		UINT _hoops_CIRGP;
		int Windowed_Width;
		int Windowed_Height;

		D3DAdapterInfo* _hoops_SIRGP;
		D3DDeviceInfo* _hoops_GCRGP;
		D3DDeviceCombo* _hoops_RCRGP;

		D3DDISPLAYMODE _hoops_ACRGP; // _hoops_RIRGP _hoops_HPP _hoops_RH _hoops_IPSP
		D3DFORMAT _hoops_PCRGP;
		D3DMULTISAMPLE_TYPE _hoops_HCRGP;
		DWORD _hoops_ICRGP;
		_hoops_PAGGP _hoops_CCRGP;
		UINT _hoops_SCRGP;

		D3DAdapterInfo* _hoops_GSRGP() { return _hoops_CIGGP ? _hoops_IHRGP : _hoops_SIRGP; }
		D3DDeviceInfo* _hoops_RSRGP() { return _hoops_CIGGP ? _hoops_CHRGP : _hoops_GCRGP; }
		D3DDeviceCombo* _hoops_ASRGP() { return _hoops_CIGGP ? _hoops_SHRGP : _hoops_RCRGP; }

		int _hoops_PPGGP() { return _hoops_ASRGP()->_hoops_PPGGP; }
		D3DDEVTYPE _hoops_PHGGP() { return _hoops_ASRGP()->_hoops_PHGGP; }
		D3DFORMAT BackBufferFormat() { return _hoops_ASRGP()->BackBufferFormat; }

		D3DDISPLAYMODE _hoops_PSRGP() { return _hoops_CIGGP ? _hoops_GIRGP : _hoops_ACRGP; }
		void _hoops_HSRGP(D3DDISPLAYMODE value) { if (_hoops_CIGGP) _hoops_GIRGP = value; else _hoops_ACRGP = value; }

		D3DFORMAT _hoops_ISRGP() { return _hoops_CIGGP ? _hoops_AIRGP : _hoops_PCRGP; }
		void _hoops_CSRGP(D3DFORMAT value) { if (_hoops_CIGGP) _hoops_AIRGP = value; else _hoops_PCRGP = value; }

		D3DMULTISAMPLE_TYPE _hoops_SSRGP() { return _hoops_CIGGP ? _hoops_PIRGP : _hoops_HCRGP; }
		void _hoops_GGAGP(D3DMULTISAMPLE_TYPE value) { if (_hoops_CIGGP) _hoops_PIRGP = value; else _hoops_HCRGP = value; }

		DWORD _hoops_RGAGP() { return _hoops_CIGGP ? _hoops_HIRGP : _hoops_ICRGP; }
		void _hoops_AGAGP(DWORD value) { if (_hoops_CIGGP) _hoops_HIRGP = value; else _hoops_ICRGP = value; }

		_hoops_PAGGP _hoops_PGAGP() { return _hoops_CIGGP ? _hoops_IIRGP : _hoops_CCRGP; }
		void _hoops_HGAGP(_hoops_PAGGP value) { if (_hoops_CIGGP) _hoops_IIRGP = value; else _hoops_CCRGP = value; }

		UINT _hoops_IGAGP() { return _hoops_CIGGP ? _hoops_CIRGP : _hoops_SCRGP; }
		void _hoops_CGAGP(UINT value) { if (_hoops_CIGGP) _hoops_CIRGP = value; else _hoops_SCRGP = value; }
};



#endif // _hoops_SGAGP

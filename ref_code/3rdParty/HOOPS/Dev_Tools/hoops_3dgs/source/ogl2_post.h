/*
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.26 2009-10-28 23:48:36 warren Exp $
 */

#ifndef _hoops_AGPPC
#define _hoops_AGPPC


#include "3d_common.h"

/*_hoops_CPCHR _hoops_IGCPR*/
class _hoops_RRCAC;
struct HOGLData;


class _hoops_RIAPC : public H3DConstantTable
{
private:
	GLint _hoops_AIAPC;

#define _hoops_PIAPC 10
	H3D_Shader_Handle _hoops_HIAPC[_hoops_PIAPC];	//_hoops_PGPPC _hoops_IGIR _hoops_IH _hoops_HA

public:
	_hoops_RIAPC(H3DData *h3ddata, GLint table): 
		H3DConstantTable(h3ddata),
		_hoops_AIAPC((GLint)table)
	{
		SET_MEMORY(&_hoops_HIAPC[0], sizeof(_hoops_HIAPC), _hoops_GGS);
	};
	~_hoops_RIAPC() {};

	void SetFloat(const char *name, const float value);
	void SetFloatArray(const char *name, const float *values, int count);
	void SetMatrix(const char *name, const float *matrix);
	void SetVector(const char *name, const float *vector, const int _hoops_IIIRR = 4);
	void SetVectorArray(const char *name, const float *_hoops_CIIRR, const float _hoops_SIIRR, const int _hoops_IIIRR = 4);
	unsigned long GetSamplerIndex(const char *name);
};


class _hoops_RRCAC : public H3DPost
{
public:

	_hoops_RRCAC( H3DData *data );
	~_hoops_RRCAC();

	bool _hoops_GGPP();					// _hoops_GCIH _hoops_IRS _hoops_RHAA _hoops_PRCAH
	void _hoops_PRHP();						// _hoops_ASAP _hoops_IRS _hoops_RHAA _hoops_PRCAH

	void Copy(H3DRenderTarget *_hoops_PCAP, H3DTexture * src, RGBA const *_hoops_SSHR, H3DTEXTUREFILTERTYPE filter);

	void Copy(H3DTexture *_hoops_PCAP, H3DTexture * src, RGBA const *_hoops_SSHR, H3DTEXTUREFILTERTYPE filter) {
		Copy((H3DRenderTarget *) _hoops_PCAP, src, _hoops_SSHR, filter);
	}

	void _hoops_PPCRR(H3DRenderTarget *_hoops_PCAP, H3DTexture *src, int _hoops_HPCRR, Vector const *_hoops_IGGP, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT);

	void _hoops_PPCRR(H3DTexture *_hoops_PCAP, H3DTexture *src, int _hoops_HPCRR, Vector const *_hoops_IGGP, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT) {
		_hoops_PPCRR((H3DRenderTarget *) _hoops_PCAP, src, _hoops_HPCRR, _hoops_IGGP, filter);
	}


	void _hoops_GAIP(H3DRenderTarget *_hoops_PCAP, H3DTexture *src, _hoops_AGSA which,int _hoops_HPCRR, Vector const *_hoops_IGGP, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT);

	void _hoops_GAIP(H3DTexture *_hoops_PCAP, H3DTexture *src, _hoops_AGSA which,int _hoops_HPCRR, Vector const *_hoops_IGGP, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT) {
		_hoops_GAIP((H3DRenderTarget *) _hoops_PCAP, src, which, _hoops_HPCRR, _hoops_IGGP, filter);
	}

	void _hoops_AHSH( H3DRenderTarget * _hoops_PCAP, H3DTexture **_hoops_CPCRR, int _hoops_SPCRR, RGBA const *_hoops_SSHR = NULL, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT );

	void _hoops_AHSH( H3DTexture * _hoops_PCAP, H3DTexture **_hoops_CPCRR, int _hoops_SPCRR, RGBA const *_hoops_SSHR = NULL, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT )
	{
		_hoops_AHSH((H3DRenderTarget *) _hoops_PCAP, _hoops_CPCRR, _hoops_SPCRR, _hoops_SSHR, filter);
	}

	void _hoops_IPCRR(H3DRenderTarget * _hoops_PCAP, H3DTexture * src, H3DTexture *depth, int _hoops_HPCRR, Vector const *_hoops_IGGP, H3DTEXTUREFILTERTYPE filter);

	void _hoops_IPCRR( H3DTexture * _hoops_PCAP, H3DTexture * src, H3DTexture *depth, int _hoops_HPCRR, Vector const *_hoops_IGGP, H3DTEXTUREFILTERTYPE filter = H3DTEXF_POINT )
	{
		_hoops_IPCRR((H3DRenderTarget *) _hoops_PCAP, src, depth, _hoops_HPCRR, _hoops_IGGP, filter);
	}

	// _hoops_HCGA _hoops_RH _hoops_CHIA _hoops_CI _hoops_IS _hoops_RH _hoops_SAAP
	void _hoops_HPRP( H3DRenderTarget *_hoops_PCAP, _hoops_AGSA const which, float depth = 0.0f, float const *matrix = null, H3DTexture *_hoops_IHCRR = null  )
	{
		_hoops_ISS->_hoops_GSCR->_hoops_GPAP(_hoops_PCAP);
		if (_hoops_CHCRR(which, depth, matrix, _hoops_IHCRR))
		{
			// _hoops_GISP...
			_hoops_HGCRR->_hoops_CHSA(_hoops_ISS);
		}
	}

	H3DConstantTable * _hoops_CHCRR(_hoops_AGSA which, float depth = 0.0f, float const *matrix = null, H3DTexture *_hoops_IHCRR = null);

	H3DConstantTable* _hoops_PIGP( _hoops_GRCRR const _hoops_CACRR, _hoops_AGSA const which );

	// _hoops_CRCAH _hoops_IRS _hoops_CI'_hoops_GRI _hoops_CCGP _hoops_PAPA
	inline _hoops_SACRR _hoops_RSGP( _hoops_AGSA const which )	{ return _hoops_CGCAH[which]; }

	bool _hoops_SSAPC(_hoops_GRCRR const _hoops_HHRAR, _hoops_AGSA const ps, bool _hoops_GGPPC);

	// _hoops_SRCAH _hoops_AIRRR _hoops_HII _hoops_IHIAH
	void _hoops_GICRR()
	{
		_hoops_HCIAH();
		_hoops_SCAPC();
	}

private:
	_hoops_PPRS _hoops_ICIAH;

	GLint _hoops_CCAPC[H3DPost::_hoops_RRCRR][H3DPost::_hoops_IACRR];		// _hoops_GGPR _hoops_HAACI (_hoops_SPR _hoops_IH _hoops_GRR _hoops_HCPC/_hoops_HGPPC _hoops_SPACA)
	GLint _hoops_RIIAH;								// _hoops_ICPA _hoops_GPHA _hoops_CI
	GLint _hoops_AIIAH;								// _hoops_ICPA _hoops_GPHA _hoops_CI _hoops_IH 3D
	GLint _hoops_HIIAH[H3DPost::_hoops_IACRR];			// _hoops_ACHAH _hoops_AIR _hoops_AIRRR
	_hoops_SACRR _hoops_CGCAH[_hoops_IACRR];					// _hoops_AACAH _hoops_PAPA _hoops_GGR _hoops_SGH _hoops_IH _hoops_GRR _hoops_CI.

	// _hoops_RAPH
	void _hoops_SCAPC();									// _hoops_GISA/_hoops_CASRR _hoops_HCR _hoops_AIRRR
	void _hoops_HCIAH();									// _hoops_CPCS _hoops_HCR _hoops_AIRRR
};

#endif // _hoops_IGPPC

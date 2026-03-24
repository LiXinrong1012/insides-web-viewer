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
 * $Id: obf_tmp.txt 1.58 2010-10-13 00:08:41 warren Exp $
 */

#include "hoops.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "adt.h"

#include "ogl2.h"
#include "ogl2_post.h"



// _hoops_GIAPC ///////////////////////////////////////////////////////////////////
void _hoops_RIAPC::SetFloat(const char *name, const float value) 
{
	HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
	GLint handle = glGetUniformLocation (_hoops_AIAPC, name);
	if (handle == -1)
		return;
	glUniform1f(handle, value);
};
void _hoops_RIAPC::SetFloatArray(const char *name, const float *values, const int count)
{
	HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
	GLint handle = glGetUniformLocation (_hoops_AIAPC, name);
	if (handle == -1)
		return;
	glUniform1fv(handle, count, values);
}
void _hoops_RIAPC::SetMatrix(const char *name, const float *matrix) 
{
	HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
	GLint handle = glGetUniformLocation (_hoops_AIAPC, name);
	if (handle == -1)
		return;
	glUniformMatrix4fv(handle, 1, false, matrix);
};
void _hoops_RIAPC::SetVector(const char *name, const float *vector, const int _hoops_IIIRR) 
{
	SetVectorArray(name, vector, 1, _hoops_IIIRR);
};
void _hoops_RIAPC::SetVectorArray(const char *name, const float *_hoops_CIIRR, const float _hoops_SIIRR, const int _hoops_IIIRR) 
{
	HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
	GLint handle = glGetUniformLocation (_hoops_AIAPC, name);
	if (handle == -1)
		return;

	switch(_hoops_IIIRR) {
		case 4:
			glUniform4fv(handle, _hoops_SIIRR, (const GLfloat *) _hoops_CIIRR);
			break;
		case 3:
			glUniform3fv(handle, _hoops_SIIRR, (const GLfloat *) _hoops_CIIRR);
			break;
		case 2:
			glUniform2fv(handle, _hoops_SIIRR, (const GLfloat *) _hoops_CIIRR);
			break;
		case 1:
			glUniform1fv(handle, _hoops_SIIRR, (const GLfloat *) _hoops_CIIRR);
			break;
	}
};
unsigned long _hoops_RIAPC::GetSamplerIndex(const char *name) 
{
	HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
	unsigned long result = 0;
	GLint handle = glGetUniformLocation (_hoops_AIAPC, name);

	// _hoops_RPP _hoops_SR'_hoops_RISP _hoops_IIP _hoops_ARP _hoops_RH _hoops_RCGP, _hoops_AA _hoops_HIS _hoops_HA
	if (handle) {
		for (result = 0; result < _hoops_PIAPC; result++) {
			if (_hoops_HIAPC[result] == _hoops_GGS) {
				glUniform1i(handle, result);
				_hoops_HIAPC[result] = handle;
				break;
			}
			else if (_hoops_HIAPC[result] == handle) {
				break;
			}
		}
	}

	//_hoops_IIAPC( _hoops_CIAPC, _hoops_RGHH, (_hoops_SIAPC *) &_hoops_GHPP);		//_hoops_IH _hoops_SSRR _hoops_RIHH _hoops_IPAC?
	ASSERT(result <= _hoops_PIAPC);
	return result;
};


// _hoops_GGPR _hoops_PIH
local _hoops_PSIRR const _hoops_ISHAH = _hoops_CSIRR(_hoops_CHGIH, 0);
local _hoops_PSIRR const _hoops_CSHAH = _hoops_CSIRR(_hoops_SHGIH, 0);
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


local GLint _hoops_PPIAH(H3DData *h3ddata, _hoops_PSIRR name, H3DPost::_hoops_SACRR _hoops_CPIAH, GLenum type)
{
	HOGLData *_hoops_CSRGR = (HOGLData *) h3ddata;
	UNREFERENCED(_hoops_CSRGR);

	GLint _hoops_GCAPC = 0;
	char *_hoops_PAIAH = null;
	int _hoops_AAIAH = 0;
	char _hoops_SPIAH[_hoops_SA];

	UNREFERENCED(_hoops_PAIAH);
	UNREFERENCED(_hoops_AAIAH);

#ifdef H3D_SHADER_DEBUG
	if ( char const * _hoops_CCPR = _hoops_SCPR() )
	{
		// _hoops_RAH _hoops_SR _hoops_RRP _hoops_IS _hoops_GGCR _hoops_IRS _hoops_HAIAH?
		bool const _hoops_IAIAH = _hoops_CCPR[_hoops_SSGR(_hoops_CCPR) - 1] != '\\';

		// _hoops_IISR _hoops_APRAR _hoops_CAIAH
		char full_path[1024]; // _hoops_SAIAH _hoops_IH _hoops_ISHRH
		sprintf(full_path, "%s%s%s.hlsl", _hoops_CCPR, _hoops_IAIAH ? "\\" : "", name.filename);

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
#endif // _hoops_PAHRH

	if (name.string) {
		_hoops_GCAPC = glCreateShader(type);

		sprintf(_hoops_SPIAH, "%s", _hoops_HHGIH);
		//_hoops_RCAPC(_hoops_ACAPC, "#_hoops_PPIP _hoops_PCAPC\_hoops_ACHP");

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

		char buffer[64];
		sprintf(buffer, "#define QUALITY %d\n", _hoops_CPIAH);
		strcat(_hoops_SPIAH, buffer);

		strcat(_hoops_SPIAH, "//=============================\n");
		strcat(_hoops_SPIAH, "//   End shader preprocessors  \n");
		strcat(_hoops_SPIAH, "//=============================\n");

		strcat(_hoops_SPIAH, name.string);

		if (type == GL_FRAGMENT_SHADER)
			strcat(_hoops_SPIAH, _hoops_IHGIH);
		int len = _hoops_SSGR(_hoops_SPIAH);

		const char *shader_source = &_hoops_SPIAH[0];
		glShaderSource(_hoops_GCAPC, 1, &shader_source, &len);
		glCompileShader(_hoops_GCAPC);

		int status = 0;
		glGetShaderiv(_hoops_GCAPC, GL_COMPILE_STATUS, &status);

		if (status != GL_TRUE)
		{
			// _hoops_HGIRH _hoops_PHHS _hoops_RPP _hoops_IRS _hoops_IIPGA _hoops_HRGR _hoops_HHPA
			if (_hoops_CPIAH == H3DPost::_hoops_ASGP) 
			{
				char log[4096];
				int len;
				glGetShaderInfoLog(_hoops_GCAPC, sizeof(log), &len, log);

				if (len > 0) {
					char _hoops_CIIAC[4096];
					//_hoops_PRHHP (_hoops_HRHHP, _hoops_IRHHP, 
						//_hoops_HISGA (_hoops_IRAP, "_hoops_HCAPC _hoops_CI _hoops_HSSI _hoops_RIHH:\_hoops_ACHP%_hoops_IISGA", &_hoops_ISIAC[0]));

					sprintf(_hoops_CIIAC, "%s:\n %s\n", name.filename, log);

#ifdef WINDOWS_SYSTEM
					OutputDebugString(_hoops_CIIAC);
#endif
				}
			}

			// _hoops_SP _hoops_GH _hoops_SRSH _hoops_CI
			glDeleteShader(_hoops_GCAPC);
			_hoops_GCAPC = 0;
		}
	}

#ifdef _DEBUG
	// _hoops_PPGGR _hoops_CI _hoops_GSGR _hoops_SR _hoops_PGGGH _hoops_HII _hoops_IHIAH.
	if (_hoops_PAIAH)
		FREE_ARRAY(_hoops_PAIAH, _hoops_AAIAH, char);
#endif // _hoops_PAHRH

	return _hoops_GCAPC;
}



// _hoops_ICAPC ///////////////////////////////////////////////////////////////////

//
// _hoops_AHRAA. _hoops_IARP _hoops_IS _hoops_SISS _hoops_PPR _hoops_GGARP _hoops_AIRRR.
//
_hoops_RRCAC::_hoops_RRCAC(H3DData *data)
{
	HOGLData *_hoops_CSRGR = (HOGLData *) data;
	UNREFERENCED(_hoops_CSRGR);

	_hoops_ISS = data;
	_hoops_PGCRR = null;

	memset(_hoops_HIIAH, 0, sizeof(_hoops_HIIAH));
	memset(_hoops_CCAPC, 0, sizeof(_hoops_CCAPC));
	memset(_hoops_SGCRR, 0, sizeof(_hoops_SGCRR));

	_hoops_SCAPC();

	// _hoops_GISA _hoops_HGSI _hoops_AIPS
	_hoops_AAIRR._hoops_SAIGR(H3DVF_PT);

	// _hoops_GISA _hoops_CPAP
	H3DVertexBuffer &_hoops_PAIH = _hoops_ISS->_hoops_CP;
	H3DIndexBuffer _hoops_RAHC;
	H3DIndexedBufferObject *_hoops_HACP;
	_hoops_HACP = _hoops_ISS->_hoops_GSCR->_hoops_PRAS();

	// _hoops_GISA _hoops_SHPR-_hoops_GCIAH _hoops_SCPH
	_hoops_HACP->CreateVertexBuffer(_hoops_ISS, 3, _hoops_AAIRR);
	_hoops_HACP->CreateIndexBuffer(_hoops_ISS, H3DPT_TRIANGLELIST, 3, 1);

	_hoops_HACP->LockVertexBuffer(0, 0, &_hoops_PAIH, 0);
	_hoops_HACP->LockIndexBuffer(0, 0, &_hoops_RAHC, 0);
	{
		// _hoops_AGGRR _hoops_RAAP
		_hoops_PAIH._hoops_AHCP(-1.0f, 1.0f, 0.0f);
		_hoops_PAIH._hoops_CPPH();

		// _hoops_RCIAH
		_hoops_PAIH._hoops_AHCP(3.0f, 1.0f, 0.0f);
		_hoops_PAIH._hoops_CPPH();
		
		// _hoops_PGRCR
		_hoops_PAIH._hoops_AHCP(-1.0f, -3.0f, 0.0f);
		_hoops_PAIH._hoops_CPPH();

		_hoops_RAHC[0] = 0;
		_hoops_RAHC[1] = 1;
		_hoops_RAHC[2] = 2;
	}
	_hoops_HACP->UnlockIndexBuffer();
	_hoops_HACP->UnlockVertexBuffer();

	_hoops_HGCRR = _hoops_HACP;
}

//
// _hoops_ACIAH. _hoops_PPGGR _hoops_CPS.
//
_hoops_RRCAC::~_hoops_RRCAC()
{
	HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
	int i = 0;
	UNREFERENCED(_hoops_CSRGR);

	for (i = 0; i < H3DPost::_hoops_IACRR; ++i) {
		if (_hoops_CCAPC[0][i])
			glDeleteProgram(_hoops_CCAPC[0][i]);
		if (_hoops_CCAPC[1][i])
			glDeleteProgram(_hoops_CCAPC[1][i]);
	}

	glDeleteShader(_hoops_RIIAH);
	glDeleteShader(_hoops_AIIAH);
		
	// _hoops_SHPPR _hoops_AIR _hoops_AIRRR
	for (i = 0; i < H3DPost::_hoops_IACRR; ++i) {
		glDeleteShader(_hoops_HIIAH[i]);
	}

	for (i = 0; i < _hoops_IACRR; ++i) {
		_hoops_HP(_hoops_SGCRR[0][i]);
	}

	_hoops_HP(_hoops_HGCRR);

	// _hoops_PPGGR _hoops_PSCA
	_hoops_RPCRR();
}

//
// _hoops_PPGGR _hoops_SHIR _hoops_ICGAR _hoops_AARAR/_hoops_AI
//


bool _hoops_RRCAC::_hoops_GGPP()
{
	//_hoops_CPRPI(_hoops_SPRPI, 0);

	// _hoops_RSCS _hoops_SCGR _hoops_ASCS
	_hoops_ISS->_hoops_GSCR->_hoops_IPRS(&_hoops_ICIAH);


	// _hoops_ICSS _hoops_HCH-_hoops_APSP _hoops_ISSGR
	//_hoops_GSAPC._hoops_RSAPC(_hoops_IRAP);

	// _hoops_GCAR _hoops_IAPRR
	_hoops_RHSA(_hoops_ISS, H3DCULL_NONE);

	// _hoops_CHSR _hoops_CCIAH
	ENSURE_TRANSPARENCY(_hoops_ISS, false);
	_hoops_RPAP(_hoops_ISS, true);
	return true;
}

void _hoops_RRCAC::_hoops_PRHP()
{
	HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
	// _hoops_ICSS _hoops_ISCP _hoops_AIRRR
	glUseProgram(0);

	// _hoops_IPRP _hoops_ASCS
	_hoops_CSRGR->_hoops_GSCR->_hoops_CHRS(&_hoops_ICIAH);

	//
	// _hoops_GCRR _hoops_RCRR _hoops_RH _hoops_IHAH _hoops_HRGR _hoops_IAR _hoops_CAGGR, _hoops_PAR _hoops_GH _hoops_IS _hoops_ICGIP.
	//

	// _hoops_SCIAH _hoops_RPIC _hoops_PPR _hoops_HIHP _hoops_PIAP _hoops_HCAGR.
	_hoops_CSRGR->_hoops_GSCR->_hoops_IPPRR(H3DVertexFormat(_hoops_CSRGR->_hoops_CSC->_hoops_PPCP));
	_hoops_CSRGR->_hoops_CSC->_hoops_AGSA = null;
	_hoops_CSRGR->_hoops_HCAC = _hoops_CCC;

	// _hoops_ICSS _hoops_GII _hoops_PPR _hoops_HCR _hoops_AI
	for (int t = 0; t < _hoops_CIGP; ++t) {
		_hoops_ASRP(_hoops_CSRGR, t);
	}

	// _hoops_CHSR _hoops_HRP
	_hoops_APSS(_hoops_CSRGR);
}

//
// _hoops_IGPP _hoops_IRS _hoops_HH _hoops_IS _hoops_RH _hoops_SCGR _hoops_SRGS _hoops_SAAP
//
void _hoops_RRCAC::Copy(H3DRenderTarget *_hoops_PCAP, H3DTexture * src, RGBA const *_hoops_SSHR, H3DTEXTUREFILTERTYPE filter)
{	
	_hoops_ISS->_hoops_GSCR->_hoops_GPAP(_hoops_PCAP);

	if (H3DConstantTable *_hoops_AIPA = _hoops_PIGP(_hoops_HIGP, _hoops_ARCRR))
	{
		// _hoops_IARP _hoops_HAIR
		if (!_hoops_SSHR)
			_hoops_SSHR = &_hoops_IGISA::_hoops_IAHHP;
		_hoops_AIPA->SetVector("ModulationColor", (const float *) _hoops_SSHR);

		// _hoops_IARP _hoops_HH _hoops_IS _hoops_GGSP _hoops_HPPCR
		const unsigned long _hoops_PCI = _hoops_AIPA->GetSamplerIndex("Sampler");
		_hoops_SCCR(_hoops_ISS, _hoops_PCI, src);
		ENSURE_TEXTURE_WRAP_S(_hoops_ISS, _hoops_PCI, H3DTADDRESS_CLAMP);
		_hoops_SAIRH(_hoops_ISS, _hoops_PCI, H3DTADDRESS_CLAMP);

		// _hoops_HCGA _hoops_RGRR _hoops_HRP
		_hoops_GAPAH(_hoops_ISS, _hoops_PCI, filter);
		_hoops_RAPAH(_hoops_ISS, _hoops_PCI, filter);

		// _hoops_HCGA _hoops_IPS _hoops_CI
		_hoops_HPRP(_hoops_PCAP, _hoops_ARCRR, 0, NULL, src);

		// ..._hoops_PPR _hoops_RSIAH _hoops_HH _hoops_HIS _hoops_SR _hoops_PAH _hoops_SRGS _hoops_IS _hoops_SCH _hoops_SPHR.
		_hoops_ASRP(_hoops_ISS, _hoops_PCI);
	}
}

//
// _hoops_CIRP _hoops_IRS _hoops_HH _hoops_IS _hoops_RH _hoops_SCGR _hoops_SRGS _hoops_SAAP
//
void _hoops_RRCAC::_hoops_PPCRR(H3DRenderTarget *_hoops_PCAP, H3DTexture *src, int _hoops_HPCRR, Vector const *_hoops_IGGP, H3DTEXTUREFILTERTYPE filter)
{
	HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
	_hoops_CSRGR->_hoops_GSCR->_hoops_GPAP(_hoops_PCAP);
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
		float _hoops_SCGP[16][4];
		SET_MEMORY(&_hoops_SCGP[0][0], 16 * 4 * sizeof(float), 0);

		for (int i = 0; i < _hoops_HPCRR; ++i)
		{
			// _hoops_GPPR _hoops_IS _hoops_ASIAH _hoops_PSIAH
			//_hoops_RGGP[_hoops_HAS] = _hoops_ASAPC(_hoops_ARGP[_hoops_HAS]._hoops_SISR * _hoops_PSAPC, _hoops_ARGP[_hoops_HAS]._hoops_HAPC * _hoops_HSAPC, 0, _hoops_ARGP[_hoops_HAS]._hoops_SSH);
			_hoops_SCGP[i][0] = _hoops_IGGP[i].x * _hoops_CHRP;
			_hoops_SCGP[i][1] = _hoops_IGGP[i].y * _hoops_SHRP;
			_hoops_SCGP[i][2] = 0;
			_hoops_SCGP[i][3] = _hoops_IGGP[i].z;
		}

		// _hoops_CHSR _hoops_GCSH _hoops_GHAA _hoops_SCH
		_hoops_AIPA->SetVectorArray("Kernel", (const float *) _hoops_SCGP, _hoops_GSGP);

		// _hoops_IARP _hoops_HH _hoops_IS _hoops_GGSP _hoops_HPPCR
		const unsigned long _hoops_PCI = _hoops_AIPA->GetSamplerIndex("Sampler");
		_hoops_SCCR(_hoops_CSRGR, _hoops_PCI, src);
		ENSURE_TEXTURE_WRAP_S(_hoops_CSRGR, _hoops_PCI, H3DTADDRESS_CLAMP);
		_hoops_SAIRH(_hoops_CSRGR, _hoops_PCI, H3DTADDRESS_CLAMP);

		// _hoops_HCGA _hoops_RGRR _hoops_HRP
		_hoops_GAPAH(_hoops_CSRGR, _hoops_PCI, filter);
		_hoops_RAPAH(_hoops_CSRGR, _hoops_PCI, filter);

		// _hoops_GISP...
		_hoops_HPRP(_hoops_PCAP, which);

		// ..._hoops_PPR _hoops_RSIAH _hoops_HH _hoops_HIS _hoops_SR _hoops_PAH _hoops_SRGS _hoops_IS _hoops_SCH _hoops_SPHR.
		_hoops_ASRP(_hoops_CSRGR, _hoops_PCI);
	}
}

void _hoops_RRCAC::_hoops_GAIP(H3DRenderTarget *_hoops_PCAP, H3DTexture *src, _hoops_AGSA which,int _hoops_HPCRR, Vector const *_hoops_IGGP, H3DTEXTUREFILTERTYPE filter)
{
	HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
	_hoops_CSRGR->_hoops_GSCR->_hoops_GPAP(_hoops_PCAP);
	
	// _hoops_IPHH (_hoops_PPR _hoops_GCAS _hoops_ACASA) _hoops_IPSP _hoops_RGGP _hoops_CRGR _hoops_IRS _hoops_APP _hoops_CI _hoops_IGIR.
	int _hoops_GSGP = 8;

	if (H3DConstantTable *_hoops_AIPA = _hoops_PIGP(_hoops_HIGP, which))
	{
		// _hoops_GRSH _hoops_AHSC _hoops_HRGR _hoops_RH _hoops_HCGP _hoops_HH?
		float const _hoops_CHRP = 1.0f / src->_hoops_IRRP;
		float const _hoops_SHRP = 1.0f / src->_hoops_CRRP;

		// _hoops_PHIR _hoops_GGR _hoops_IPSP _hoops_ARGP
		RGBA _hoops_SCGP[16];
		for (int i = 0; i < _hoops_HPCRR; ++i)
		{
			// _hoops_GPPR _hoops_IS _hoops_ASIAH _hoops_PSIAH
			_hoops_SCGP[i] = RGBA(_hoops_IGGP[i].x * _hoops_CHRP, _hoops_IGGP[i].y * _hoops_SHRP, 0, _hoops_IGGP[i].z);
		}

		// _hoops_GHPA _hoops_RII _hoops_ARGP
		memset(_hoops_SCGP + _hoops_HPCRR, 0, (_hoops_GSGP - _hoops_HPCRR) * sizeof(RGBA));

		// _hoops_CHSR _hoops_GCSH _hoops_GHAA _hoops_SCH
		_hoops_AIPA->SetVectorArray("Kernel", (const float *) _hoops_SCGP, _hoops_GSGP);

		// _hoops_IARP _hoops_HH _hoops_IS _hoops_GGSP _hoops_HPPCR
		const unsigned long _hoops_PCI = _hoops_AIPA->GetSamplerIndex("Sampler");
		_hoops_SCCR(_hoops_CSRGR, _hoops_PCI, src);
		ENSURE_TEXTURE_WRAP_S(_hoops_CSRGR, _hoops_PCI, H3DTADDRESS_CLAMP);
		_hoops_SAIRH(_hoops_CSRGR, _hoops_PCI, H3DTADDRESS_CLAMP);

		// _hoops_HCGA _hoops_RGRR _hoops_HRP
		_hoops_GPIRH((_hoops_CSRGR), _hoops_PCI, filter);
		_hoops_RPIRH((_hoops_CSRGR), _hoops_PCI, filter);

		// _hoops_GISP...
		_hoops_HPRP(_hoops_PCAP, which, 0, NULL, src);

		// ..._hoops_PPR _hoops_RSIAH _hoops_HH _hoops_HIS _hoops_SR _hoops_PAH _hoops_SRGS _hoops_IS _hoops_SCH _hoops_SPHR.
		_hoops_ASRP(_hoops_CSRGR, _hoops_PCI);
	}
}



//
// _hoops_RGHSP-_hoops_ISIAH _hoops_RGRR _hoops_IIGR _hoops_IRS _hoops_HH _hoops_IS _hoops_RH _hoops_SCGR _hoops_SRGS _hoops_SAAP
//
void _hoops_RRCAC::_hoops_IPCRR(H3DRenderTarget * _hoops_PCAP, H3DTexture * src, H3DTexture *depth, int _hoops_HPCRR, Vector const *_hoops_IGGP, H3DTEXTUREFILTERTYPE filter)
{
	HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;

	// _hoops_IARP _hoops_HCH _hoops_CSIAH
	_hoops_SCCR(_hoops_CSRGR, 1, depth);
	_hoops_GRPA(_hoops_CSRGR, 1, H3DTEXF_POINT, H3DTEXF_NONE, H3DTADDRESS_CLAMP);

	// _hoops_SGPR _hoops_GPRGR _hoops_RGRR
	_hoops_GAIP(_hoops_PCAP, src, _hoops_GACRR, _hoops_HPCRR, _hoops_IGGP, filter);

	// ..._hoops_PPR _hoops_RSIAH _hoops_HCH _hoops_HH _hoops_HIS _hoops_SR _hoops_PAH _hoops_SRGS _hoops_IS _hoops_SCH _hoops_SPHR.
	_hoops_ASRP(_hoops_CSRGR, 1);
}

//
// _hoops_CIRP _hoops_IRS _hoops_HH _hoops_IS _hoops_RH _hoops_SCGR _hoops_SRGS _hoops_SAAP
//
void _hoops_RRCAC::_hoops_AHSH(H3DRenderTarget *_hoops_PCAP, H3DTexture ** _hoops_CPCRR, int _hoops_SPCRR, RGBA const *_hoops_RHSH, H3DTEXTUREFILTERTYPE filter)
{
	HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
	_hoops_CSRGR->_hoops_GSCR->_hoops_GPAP(_hoops_PCAP);

	// _hoops_IPHH (_hoops_PPR _hoops_GCAS _hoops_ACASA) _hoops_IPSP _hoops_RGGP _hoops_CRGR _hoops_IRS _hoops_APP _hoops_CI _hoops_IGIR.
	int _hoops_GSGP = 8;

	// _hoops_RRAH _hoops_GGSP _hoops_CI
	_hoops_AGSA which = _hoops_SRCRR;//(_hoops_GGPR)(_hoops_ISAPC + _hoops_RRRP / 4 - 1);
	if (H3DConstantTable *_hoops_AIPA = _hoops_PIGP(_hoops_HIGP, which))
	{
		// _hoops_PHIR _hoops_GGR _hoops_IPSP _hoops_ARGP
		RGBA _hoops_SCGP[8];
		SET_MEMORY(_hoops_SCGP, sizeof(_hoops_SCGP), 0);
		RGBA const color = _hoops_RHSH ? *_hoops_RHSH : RGBA(1,1,1,1);
		for (int i = 0; i < _hoops_SPCRR; ++i)
		{
			// _hoops_SSIAH _hoops_RGR _hoops_SPR
			_hoops_SCGP[i] = color;
		}

		// _hoops_GHPA _hoops_RII _hoops_ARGP
		memset(_hoops_SCGP + _hoops_SPCRR, 0, (_hoops_GSGP - _hoops_SPCRR) * sizeof(RGBA));

		// _hoops_CHSR _hoops_GCSH _hoops_GHAA _hoops_SCH
		_hoops_AIPA->SetVectorArray("Kernel", (const float *) _hoops_SCGP, _hoops_GSGP);

		// _hoops_IARP _hoops_AI _hoops_IS _hoops_GGSP _hoops_GGCAH
		char _hoops_CSAPC[16];
		for ( int i = 0; i < _hoops_SPCRR; ++i ) {
			sprintf(_hoops_CSAPC, "Sampler%d", i);
			unsigned long _hoops_PCI = _hoops_AIPA->GetSamplerIndex(_hoops_CSAPC);

			_hoops_SCCR(_hoops_CSRGR, _hoops_PCI, _hoops_CPCRR[i]);
			ENSURE_TEXTURE_WRAP_S(_hoops_CSRGR, _hoops_PCI, H3DTADDRESS_CLAMP);
			_hoops_SAIRH(_hoops_CSRGR, _hoops_PCI, H3DTADDRESS_CLAMP);

			// _hoops_HCGA _hoops_RGRR _hoops_HRP
			_hoops_GAPAH((_hoops_CSRGR), _hoops_PCI, filter);
			_hoops_RAPAH((_hoops_CSRGR), _hoops_PCI, filter);
		}

		// _hoops_IARP _hoops_SRS _hoops_HH _hoops_IS _hoops_HHRPA _hoops_GGCAH (_hoops_GRS _hoops_SHH _hoops_IAGGA)
		for ( int i = _hoops_SPCRR; i < _hoops_GSGP; ++i ) {
			_hoops_SCCR(_hoops_CSRGR, i, _hoops_CPCRR[0]);
		}

		// _hoops_GISP...
		_hoops_HPRP(_hoops_PCAP, which, 0, NULL, _hoops_CPCRR[0]);

		// ..._hoops_PPR _hoops_RSIAH _hoops_AI _hoops_HIS _hoops_SR _hoops_PAH _hoops_SRGS _hoops_IS _hoops_CAPR _hoops_SPHR.
		for ( int i = 0; i < _hoops_GSGP; ++i )
			_hoops_ASRP(_hoops_CSRGR, i);
	}
}


H3DConstantTable * _hoops_RRCAC::_hoops_CHCRR(_hoops_AGSA which, float depth, float const *matrix, H3DTexture *_hoops_IHCRR)
{
	ASSERT(which >= 0 && which < _hoops_IACRR);

	HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
	UNREFERENCED(_hoops_CSRGR);

	H3DConstantTable *_hoops_AIPA;
	_hoops_GRCRR _hoops_CACRR = matrix ? _hoops_HGRGR : _hoops_HIGP;

	_hoops_AIPA = _hoops_PIGP(_hoops_CACRR, which);

	if (matrix)
	{
		// 3D _hoops_CCH
		if (_hoops_AIPA)
		{
			_hoops_AIPA->SetFloat("ConstantDepth", depth);
			_hoops_AIPA->SetMatrix("ModelToProjection", (const float *) matrix);
		}
	}
	else
	{
		// 2D _hoops_CCH
		if (_hoops_AIPA)
		{
			// _hoops_PS _hoops_PAH _hoops_SGH _hoops_HAGH _hoops_HCH _hoops_HSH _hoops_IS _hoops_HPSSA _hoops_RRRH _hoops_CRGR 3D _hoops_CCRP
			_hoops_AIPA->SetFloat("ConstantDepth", depth);
			_hoops_SHCRR( _hoops_IHCRR );
		}
	}

	// _hoops_HR _hoops_HPCS
	H3DConstantTable *result = null;

	// _hoops_CGP _hoops_SR _hoops_HS _hoops_CPS _hoops_SR _hoops_RRP
	if (_hoops_HIIAH[which] && _hoops_SGCRR[_hoops_CACRR][which])
	{
		// _hoops_RRAH _hoops_CI _hoops_PPR _hoops_ASRC _hoops_GASR _hoops_CHGRR. _hoops_SCH _hoops_AICS.
		glUseProgram(_hoops_CCAPC[_hoops_CACRR][which]);
		int error = glGetError();
		if (error != GL_NO_ERROR) {
			return result;
		}
		result = _hoops_SGCRR[_hoops_CACRR][which];
	}

	return result;
}


H3DConstantTable* _hoops_RRCAC::_hoops_PIGP( _hoops_GRCRR const _hoops_CACRR, _hoops_AGSA const which ) 
{
	HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;

	if (_hoops_CCAPC[_hoops_CACRR][which] == 0 || _hoops_SGCRR[_hoops_CACRR][which] == null) {
		_hoops_SSAPC(_hoops_CACRR, which, false);
	}

	H3DConstantTable *result = _hoops_SGCRR[_hoops_CACRR][which];

	// _hoops_GCRR _hoops_RH _hoops_SRSR _hoops_GASR _hoops_SCGR
	_hoops_IGCRR = result;
	_hoops_CGCRR = result;

	glUseProgram(_hoops_CCAPC[_hoops_CACRR][which]);

	return result; 
}


bool _hoops_RRCAC::_hoops_SSAPC(_hoops_GRCRR const _hoops_HHRAR, _hoops_AGSA const ps, bool _hoops_GGPPC) 
{
	if (_hoops_CCAPC[_hoops_HHRAR][ps] == 0) {
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		GLint program = glCreateProgram();

		_hoops_CCAPC[_hoops_HHRAR][ps] = program;
		_hoops_SGCRR[_hoops_HHRAR][ps] = new _hoops_RIAPC(_hoops_ISS,  program);


		glAttachShader(program, _hoops_HHRAR == _hoops_HIGP ? _hoops_RIIAH : _hoops_AIIAH);
		glAttachShader(program, _hoops_HIIAH[ps]);
		glLinkProgram(program);

		int status = GL_TRUE;
		int len = 0;
		char log[4096];
		glGetProgramInfoLog(program, sizeof(log), &len, log);

		glGetProgramiv(program, GL_LINK_STATUS, &status);

		if (status != GL_TRUE) {
			glDeleteProgram(program);
			_hoops_CCAPC[_hoops_HHRAR][ps] = 0;

			if (!_hoops_GGPPC) {
				HE_ERROR(HEC_OPENGL_DRIVER, HEC_OPENGL_DRIVER,
					"Error linking post-processing shader program.");
				return false;
			}
		}
	}
	return true;
}


void _hoops_RRCAC::_hoops_SCAPC()
{
	HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
	UNREFERENCED(_hoops_CSRGR);

	// _hoops_GISA _hoops_GPHA _hoops_AIRRR (_hoops_GCSP _hoops_HPP _hoops_HCR)
	_hoops_RIIAH = _hoops_PPIAH(_hoops_ISS, _hoops_ISHAH, _hoops_ASGP, GL_VERTEX_SHADER);
	_hoops_AIIAH = _hoops_PPIAH(_hoops_ISS, _hoops_CSHAH, _hoops_ASGP, GL_VERTEX_SHADER);
	
	// _hoops_GISA _hoops_AIR _hoops_AIRRR
	for (int i = 0; i < _hoops_IACRR; ++i) {

		// _hoops_RAP _hoops_SHIR
		_hoops_CGCAH[i] = _hoops_ASGP;

		// _hoops_HCIC _hoops_RGR _hoops_IRS _hoops_PSGR _hoops_CCGP _hoops_CI? _hoops_CGP _hoops_HAR, _hoops_HSPP _hoops_HPGR _hoops_HISAR _hoops_SGCAH.
		_hoops_PSIRR const &name = _hoops_SSHAH[i];
		int _hoops_GRCAH = _hoops_ASGP;
		if ( BIT(name.flags, _hoops_SCIRR) )
			_hoops_GRCAH = _hoops_CSGP;
		if ( BIT(name.flags, _hoops_GSIRR) )
			_hoops_GRCAH = _hoops_HGRP;

		// _hoops_HSRR _hoops_GRR _hoops_HHPA _hoops_CCGP _hoops_PAPA
		for ( int _hoops_CPIAH = _hoops_GRCAH; _hoops_CPIAH >= _hoops_ASGP; --_hoops_CPIAH ) {
			bool _hoops_RGPPC = false;
			_hoops_HIIAH[i] = _hoops_PPIAH(_hoops_CSRGR, name, static_cast<_hoops_SACRR>(_hoops_CPIAH), GL_FRAGMENT_SHADER);

			if ( BIT(name.flags, _hoops_ICIRR))
				continue;

			if ( _hoops_HIIAH[i] )
				_hoops_RGPPC = _hoops_SSAPC(_hoops_HIGP, (const _hoops_AGSA) i, (_hoops_CPIAH == _hoops_ASGP));

			if (_hoops_RGPPC) {
				// _hoops_SCPRH _hoops_GPP _hoops_SRS _hoops_PPGAR _hoops_CCGP _hoops_PAPA _hoops_PPR _hoops_PRIA _hoops_SCH
				_hoops_CGCAH[i] = static_cast<_hoops_SACRR>(_hoops_CPIAH);
				break;
			}
		}
	}

}

void _hoops_RRCAC::_hoops_HCIAH()
{
	HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
	UNREFERENCED(_hoops_CSRGR);

	glUseProgram(0);
	glDeleteShader(_hoops_RIIAH);
	glDeleteShader(_hoops_AIIAH);

	_hoops_IGCRR = null;
	_hoops_CGCRR = null;
	for (int i = 0; i < _hoops_IACRR; ++i) {
		glDeleteShader(_hoops_HIIAH[i]);
		_hoops_HP(_hoops_SGCRR[0][i]);
		_hoops_HP(_hoops_SGCRR[1][i]);

		if (_hoops_CCAPC[0][i])
			glDeleteProgram(_hoops_CCAPC[0][i]);
		if (_hoops_CCAPC[1][i])
			glDeleteProgram(_hoops_CCAPC[1][i]);
	}

	memset(_hoops_CCAPC, 0, sizeof(_hoops_CCAPC));
}

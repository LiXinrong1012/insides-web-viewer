/*
 * Copyright (c) 2008 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.279 2010-12-09 21:51:28 heppe Exp $
 *
 */

#if defined(GLX_DRIVER) || defined(WGL_DRIVER) || defined(AGL_DRIVER) || defined(COCOA_OGL_DRIVER)

#include "ogl_tristrip.cpp"  /* _hoops_RH _hoops_RHGS _hoops_SICAR _hoops_RGHH _hoops_HHH _hoops_IIGR _hoops_RH _hoops_IIGSH _hoops_RPIA _hoops_ARAR */


#define _hoops_RIGHC
#ifdef _hoops_RIGHC


#define _hoops_AIGHC								unsigned int

#define _hoops_PIGHC						0x0001
#define _hoops_HIGHC						0x0002
#define _hoops_IIGHC						0x0004
#define _hoops_CIGHC						0x0008
#define _hoops_SIGHC					0x0010
#define _hoops_GCGHC					0x0020
#define _hoops_RCGHC					0x0030
#define _hoops_ACGHC					0x0040
#define _hoops_PCGHC					0x0050
#define _hoops_HCGHC					0x0060
#define _hoops_ICGHC					0x0070
#define _hoops_CCGHC					0x0080
#define _hoops_SCGHC				0x00f0
#define _hoops_GSGHC				4
#define _hoops_RSGHC(_hoops_PPCP)			((_hoops_PPCP & _hoops_SCGHC) >> _hoops_GSGHC)

#define _hoops_ASGHC(i, size)		((size-1) << (i * 2 + 16))
#define _hoops_PSGHC(_hoops_PPCP, i)	(((_hoops_PPCP >> (i * 2 + 16)) & (0x3)) + 1)




/* _hoops_RAIGR _hoops_CIAGR _hoops_AAIGR _hoops_PAIGR */
#define _hoops_HSGHC			(_hoops_PIGHC)
#define _hoops_ISGHC		(_hoops_PIGHC | _hoops_IIGHC)
#define _hoops_CSGHC		(_hoops_PIGHC | _hoops_SIGHC | _hoops_ASGHC(0,3))
#define _hoops_SSGHC	(_hoops_CSGHC | _hoops_HIGHC)
#define _hoops_GGRHC	(_hoops_SSGHC | _hoops_GCGHC | _hoops_ASGHC(1,3))


class _hoops_RSPRC
{
protected:
	_hoops_AIGHC _hoops_HAIGR;

	_hoops_AIGHC _hoops_RGRHC;
	unsigned int m_size;



	void _hoops_IAIGR(int bit, bool state) {
		if (state)
			_hoops_HAIGR |= bit;
		else
			_hoops_HAIGR &= ~bit;
	};
public:
	_hoops_RSPRC(_hoops_AIGHC _hoops_CAIGR)
	{
		reset();
		_hoops_SAIGR(_hoops_CAIGR);
	};

	_hoops_RSPRC() { reset(); };
	~_hoops_RSPRC(){};

	void reset()
	{
		ZERO_STRUCT(this, _hoops_RSPRC);
	}

	void _hoops_SAIGR(_hoops_AIGHC _hoops_CAIGR)
	{
		_hoops_HAIGR |= _hoops_CAIGR;
	};

	void _hoops_AIHC(bool state = true) {_hoops_IAIGR(_hoops_PIGHC, state);};
	void _hoops_CCRS(bool state = true) {_hoops_IAIGR(_hoops_HIGHC, state);};
	void _hoops_RPHC(bool state = true) {_hoops_IAIGR(_hoops_IIGHC, state);};
	void _hoops_APHC() {_hoops_HAIGR += _hoops_SIGHC;};
	void _hoops_PPIGR(int _hoops_GPIGR) {_hoops_HAIGR |= (_hoops_SIGHC * _hoops_GPIGR);};
	void _hoops_HIHC(int _hoops_GPIGR, int size) {_hoops_HAIGR |= _hoops_ASGHC(_hoops_GPIGR, size);};

	_hoops_AIGHC _hoops_HPCP() {return _hoops_HAIGR;};
	bool _hoops_IPIGR() {return BIT(_hoops_HAIGR, _hoops_PIGHC);};
	bool _hoops_HHCP() {return BIT(_hoops_HAIGR, _hoops_HIGHC);};
	bool _hoops_SHCP() {return BIT(_hoops_HAIGR, _hoops_IIGHC);};
	bool _hoops_AGRHC() {return BIT(_hoops_HAIGR, _hoops_CIGHC);};
	int _hoops_APIGR() {return _hoops_RSGHC(_hoops_HAIGR);};
	int _hoops_CPIGR(int _hoops_GPIGR) {return _hoops_PSGHC(_hoops_HAIGR, _hoops_GPIGR);};

	int _hoops_HGHS()
	{
		int i = 0;
		if (_hoops_RGRHC == _hoops_HAIGR)
			return m_size;

		m_size = 0;
		_hoops_RGRHC = _hoops_HAIGR;

		if (_hoops_IPIGR())				m_size += 3;
		if (_hoops_HHCP())				m_size += 3;
		if (_hoops_SHCP())				m_size += 1;

		for (i = 0; i < _hoops_APIGR(); i++)
			m_size += _hoops_CPIGR(i);

		return m_size;
	};

	void _hoops_PGRHC (OGLData *_hoops_CSRGR, void *_hoops_HGRHC, bool _hoops_ACAI = false) {
		int stride = _hoops_HGHS() * sizeof(float);
		int offset = 3;
		int i = 0;
		const char *_hoops_SHGCR = (const char *)_hoops_HGRHC;

		ASSERT (_hoops_IPIGR()); //_hoops_SR _hoops_CGH _hoops_SHR _hoops_HS _hoops_PGRAR
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer (3, GL_FLOAT, stride, _hoops_SHGCR);
		if (_hoops_HHCP()) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer (GL_FLOAT, stride, _hoops_SHGCR + offset*sizeof(float));
			offset += 3;
		}
		if (_hoops_SHCP()) {
			if (!_hoops_ACAI) {
				glEnableClientState(GL_COLOR_ARRAY);
				glColorPointer (4, GL_UNSIGNED_BYTE, stride, _hoops_SHGCR + offset*sizeof(float));
			}
			offset++;
		}
		for (i = 0; i < _hoops_APIGR(); i++) {
			int width = this->_hoops_CPIGR(i);

			ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,i,true);
			glTexCoordPointer(width, GL_FLOAT, stride, _hoops_SHGCR + offset * sizeof(float));
			offset += width;
		}
		_hoops_IHRRC(_hoops_CSRGR,0);
		UNREFERENCED (_hoops_CSRGR);
	}
	void _hoops_IGRHC (OGLData *_hoops_CSRGR) {
		int i = 0;

		glDisableClientState(GL_VERTEX_ARRAY);
		glVertexPointer (3, GL_FLOAT, 12, 0);
		if (_hoops_HHCP()) {
			glDisableClientState(GL_NORMAL_ARRAY);
			glNormalPointer (GL_FLOAT, 12, null );
		}
		if (_hoops_SHCP()) {
			glDisableClientState(GL_COLOR_ARRAY);
			glColorPointer (3, GL_UNSIGNED_BYTE, 12, null);
		}
		for (i = 0; i < _hoops_APIGR(); i++) {
			ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,i,false);
		}
		_hoops_IHRRC(_hoops_CSRGR,0);
		_hoops_CSRGR->_hoops_CSC._hoops_IGPAC = false;
		_hoops_CSRGR->_hoops_CSC._hoops_CGPAC = false;
		_hoops_CSRGR->_hoops_CSC._hoops_HGPAC = false;
	}

	bool operator == (_hoops_RSPRC &right) { return _hoops_HAIGR == right._hoops_HAIGR; };
	bool operator != (_hoops_RSPRC &right) { return _hoops_HAIGR != right._hoops_HAIGR; };
};



enum _hoops_CGRHC
{
	_hoops_SGRHC,
	_hoops_GRRHC,
	_hoops_RRRHC,
};
typedef unsigned int _hoops_ARRHC;
#define _hoops_PRRHC(a,b,c,d) ((_hoops_ARRHC)((((a)&0xff)<<24)|(((b)&0xff)<<16)|(((c)&0xff)<<8)|((d)&0xff)))
local _hoops_ARRHC _hoops_CHAP(_hoops_CGRHC format, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	_hoops_ARRHC color;
	switch (format)
	{
	case _hoops_GRRHC:
		color = _hoops_PRRHC(a,r,g,b);
		break;
	case _hoops_RRRHC:
		color = _hoops_PRRHC(a,b,g,r);
		break;
	case _hoops_SGRHC:
	default:
		color = _hoops_PRRHC(r,g,b,a);
		break;
	}
	return color;
}
local _hoops_ARRHC _hoops_GICP(_hoops_CGRHC format, float r, float g, float b, float a)
{
	return _hoops_CHAP(format, (unsigned char)(r*255), (unsigned char)(g*255), (unsigned char)(b*255), (unsigned char)(a*255));
}



class HOGLVertexBuffer
{
private:
	int stride;
	_hoops_RSPRC _hoops_PPCP;
	float *_hoops_GIIGR;
	float *_hoops_RIIGR;

	int _hoops_ICIGR;
	int _hoops_CCIGR;
	int _hoops_SCIGR;
	int *_hoops_HRRHC;

	bool _hoops_GSIGR;
	int _hoops_RSIGR;

public:
	HOGLVertexBuffer(float *_hoops_HSIGR, _hoops_RSPRC _hoops_SSIGR, int _hoops_GGCGR = 0)
	{
		_hoops_IRA(_hoops_HSIGR, _hoops_SSIGR, _hoops_GGCGR);
	}
	HOGLVertexBuffer()
	{
		ZERO_STRUCT (this, HOGLVertexBuffer);
	};
	~HOGLVertexBuffer()
	{
		if (_hoops_GSIGR) {
			if (_hoops_RIIGR)
				delete [] _hoops_RIIGR;
			_hoops_RIIGR = null;
		}

		if (_hoops_HRRHC)
			delete [] _hoops_HRRHC;
	};

	void _hoops_IRA(float *_hoops_HSIGR, _hoops_RSPRC _hoops_SSIGR, int _hoops_GGCGR = 0) {
		if (_hoops_GGCGR > 0)
			_hoops_GSIGR = true;
		else
			_hoops_GSIGR = false;

		stride = 0;
		_hoops_PPCP = _hoops_SSIGR;

		// _hoops_IHAH _hoops_RH _hoops_AII _hoops_IS _hoops_RH _hoops_AGRR _hoops_IGPC
		_hoops_ICIGR = _hoops_CCIGR = _hoops_SCIGR = -1;
		if (_hoops_HRRHC) {
			delete [] _hoops_HRRHC;
			_hoops_HRRHC = null;
		}

		// _hoops_CSGA _hoops_SIIGR
		if (_hoops_PPCP._hoops_IPIGR()) {
			_hoops_ICIGR = stride;
			stride += 3;
		}
		if (_hoops_PPCP._hoops_HHCP()) {
			_hoops_CCIGR = stride;
			stride += 3;
		}
		if (_hoops_PPCP._hoops_SHCP()) {
			_hoops_SCIGR = stride;
			stride += 1;
		}
		if (_hoops_PPCP._hoops_APIGR() > 0) {
			_hoops_HRRHC = new int[_hoops_PPCP._hoops_APIGR()];

			for ( int i = 0; i < _hoops_PPCP._hoops_APIGR(); ++i ) {
				_hoops_HRRHC[i] = stride;
				stride += _hoops_PPCP._hoops_CPIGR(i);
			}
		}

		/* _hoops_GCRR _hoops_RCRR _hoops_RH _hoops_SIIGR _hoops_SR _hoops_CSGA _hoops_ARI _hoops_HRGR _hoops_RH _hoops_PSHR _hoops_GAR _hoops_RH _hoops_SPR _hoops_SR _hoops_CSGA _hoops_HII _hoops_RH _hoops_ICRS */
		ASSERT(stride == _hoops_PPCP._hoops_HGHS());

		_hoops_RSIGR = _hoops_GGCGR;
		if (_hoops_GSIGR)
			_hoops_GIIGR = new float[stride * _hoops_RSIGR];
		else
			_hoops_GIIGR = _hoops_HSIGR;

		_hoops_RIIGR = _hoops_GIIGR;
	}
	// _hoops_SGSS _hoops_PSCH
	void reset() {_hoops_GIIGR = _hoops_RIIGR;};
	void _hoops_IPPH(int _hoops_CGCGR) {
		int _hoops_SGCGR = _hoops_GIIGR - _hoops_RIIGR;
		float *_hoops_RRCGR = _hoops_RIIGR;

		_hoops_RIIGR = new float[stride * _hoops_CGCGR];
		_hoops_AIGA(_hoops_RRCGR, stride * _hoops_AHIA(_hoops_RSIGR, _hoops_CGCGR), float, _hoops_RIIGR);

		_hoops_RSIGR = _hoops_CGCGR;
		_hoops_GIIGR = _hoops_RIIGR + _hoops_SGCGR;
	}

	int _hoops_IRRHC() { return ((_hoops_GIIGR - _hoops_RIIGR) / stride); };
	int _hoops_RACGR() {return _hoops_RSIGR;};
	float * _hoops_HACGR() {return _hoops_GIIGR;};
	float * _hoops_ARHS() {return _hoops_RIIGR;};
	float * _hoops_IAHH(int index) {return _hoops_RIIGR + index * stride;};
	_hoops_RSPRC _hoops_HPCP() {return _hoops_PPCP;};
	int _hoops_CACGR() {return stride;};
	int _hoops_SACGR() {return _hoops_ICIGR;};
	int _hoops_GPCGR() {return _hoops_CCIGR;};
	int _hoops_RPCGR() {return _hoops_SCIGR;};
	int _hoops_APCGR() {return (_hoops_HRRHC) ? _hoops_HRRHC[0] : -1;};

	// _hoops_HGCR() _hoops_PSCH
	float _hoops_PPCGR() {return _hoops_GIIGR[_hoops_ICIGR+0];}
	float _hoops_HPCGR() {return _hoops_GIIGR[_hoops_ICIGR+1];}
	float _hoops_IPCGR() {return _hoops_GIIGR[_hoops_ICIGR+2];}

	float _hoops_CPCGR() {return _hoops_GIIGR[_hoops_CCIGR+0];}
	float _hoops_SPCGR() {return _hoops_GIIGR[_hoops_CCIGR+1];}
	float _hoops_GHCGR() {return _hoops_GIIGR[_hoops_CCIGR+2];}

	float _hoops_RHCGR(int _hoops_AHCGR = 0) {
		if (_hoops_AHCGR < _hoops_PPCP._hoops_APIGR()) return _hoops_GIIGR[_hoops_HRRHC[_hoops_AHCGR]+0];
		return -1;
	}
	float _hoops_PHCGR(int _hoops_AHCGR = 0) {
		if (_hoops_AHCGR < _hoops_PPCP._hoops_APIGR()) return _hoops_GIIGR[_hoops_HRRHC[_hoops_AHCGR]+1];
		return -1;
	}
	float _hoops_CRRHC(int _hoops_AHCGR = 0) {
		if (_hoops_AHCGR < _hoops_PPCP._hoops_APIGR()) return _hoops_GIIGR[_hoops_HRRHC[_hoops_AHCGR]+2];
		return -1;
	}

	// _hoops_ARP() _hoops_PSCH
	void _hoops_AHCP(float _hoops_CHCGR, float _hoops_SHCGR, float _hoops_GICGR) {x(_hoops_CHCGR); y(_hoops_SHCGR); z(_hoops_GICGR);}
	void _hoops_AHCP(Point *p) {x(p->x); y(p->y); z(p->z);}
	void x(float _hoops_CHCGR) {if (_hoops_ICIGR >= 0) _hoops_GIIGR[_hoops_ICIGR+0] = _hoops_CHCGR;}
	void y(float _hoops_SHCGR) {if (_hoops_ICIGR >= 0) _hoops_GIIGR[_hoops_ICIGR+1] = _hoops_SHCGR;}
	void z(float _hoops_GICGR) {if (_hoops_ICIGR >= 0) _hoops_GIIGR[_hoops_ICIGR+2] = _hoops_GICGR;}

	void _hoops_IHCP(float _hoops_RICGR, float _hoops_AICGR, float _hoops_PICGR) {nx(_hoops_RICGR); ny(_hoops_AICGR); nz(_hoops_PICGR);}
	void _hoops_IHCP(Vector *v) {nx(v->x); ny(v->y); nz(v->z);}
	void nx(float _hoops_RICGR) {if (_hoops_CCIGR >= 0) _hoops_GIIGR[_hoops_CCIGR+0] = _hoops_RICGR;}
	void ny(float _hoops_AICGR) {if (_hoops_CCIGR >= 0) _hoops_GIIGR[_hoops_CCIGR+1] = _hoops_AICGR;}
	void nz(float _hoops_PICGR) {if (_hoops_CCIGR >= 0) _hoops_GIIGR[_hoops_CCIGR+2] = _hoops_PICGR;}

	void color(_hoops_ARRHC const _hoops_HICGR) {_hoops_RSAI(&_hoops_HICGR, _hoops_ARRHC, &_hoops_GIIGR[_hoops_SCIGR]);}
	void color(char a, char b, char c, char d) {color(_hoops_PRRHC(a, b, c, d));}
	void color(_hoops_CGRHC format, char a, char b, char c, char d)	{color(_hoops_CHAP(format,a,b,c,d));}
	void color(_hoops_CGRHC format, float a, float b, float c, float d)	{color(_hoops_GICP(format,a,b,c,d));}
	void color(_hoops_CGRHC format, RGB *_hoops_IASGR, float alpha)	{color(_hoops_GICP(format,_hoops_IASGR->red,_hoops_IASGR->green,_hoops_IASGR->blue,alpha));}
	void color(_hoops_CGRHC format, const RGBAS32 _hoops_PIHR) {
		color(_hoops_CHAP(format,_hoops_PIHR.r, _hoops_PIHR.g, _hoops_PIHR.b, _hoops_PIHR.a));
	}

	void uvw(float _hoops_CICGR, float _hoops_SICGR, float _hoops_PIIPA, int _hoops_AHCGR = 0) {u(_hoops_CICGR,_hoops_AHCGR); v(_hoops_SICGR,_hoops_AHCGR); w(_hoops_PIIPA,_hoops_AHCGR);}
	void u(float _hoops_CICGR, int _hoops_AHCGR = 0) {
		if (_hoops_HRRHC[_hoops_AHCGR] >= 0 && _hoops_PPCP._hoops_CPIGR(_hoops_AHCGR) > 0 && _hoops_AHCGR < _hoops_PPCP._hoops_APIGR())
			_hoops_GIIGR[_hoops_HRRHC[_hoops_AHCGR]+0] = _hoops_CICGR;
	}
	void v(float _hoops_SICGR, int _hoops_AHCGR = 0) {
		if (_hoops_HRRHC[_hoops_AHCGR] >= 0 && _hoops_PPCP._hoops_CPIGR(_hoops_AHCGR) > 1 && _hoops_AHCGR < _hoops_PPCP._hoops_APIGR())
			_hoops_GIIGR[_hoops_HRRHC[_hoops_AHCGR]+1] = _hoops_SICGR;
	}
	void w(float _hoops_PIIPA, int _hoops_AHCGR = 0) {
		if (_hoops_HRRHC[_hoops_AHCGR] >= 0 && _hoops_PPCP._hoops_CPIGR(_hoops_AHCGR) > 2 && _hoops_AHCGR < _hoops_PPCP._hoops_APIGR())
			_hoops_GIIGR[_hoops_HRRHC[_hoops_AHCGR]+2] = _hoops_PIIPA;
	}

	// _hoops_SRRHC
	HOGLVertexBuffer operator[](int const index) {
		return HOGLVertexBuffer(_hoops_GIIGR + index*stride, _hoops_PPCP);
	}
	HOGLVertexBuffer const & operator+=(int const _hoops_GCCGR) {
		_hoops_GIIGR += _hoops_GCCGR * stride;
		return *this;
	}
	HOGLVertexBuffer const & operator++() {
		_hoops_GIIGR += stride;
		return *this;
	}
	HOGLVertexBuffer const & next() {
		_hoops_GIIGR += stride;
		return *this;
	}
	HOGLVertexBuffer operator+(int const _hoops_GCCGR) const {
		return HOGLVertexBuffer(_hoops_GIIGR + _hoops_GCCGR*stride, _hoops_PPCP);
	}
	HOGLVertexBuffer operator-(int const _hoops_GCCGR) const {
		return HOGLVertexBuffer(_hoops_GIIGR + _hoops_GCCGR*stride, _hoops_PPCP);
	}
};

class _hoops_GARHC
{
public:
	_hoops_GARHC():_hoops_CCHRR(0), _hoops_GSHRR(0){}

	_hoops_GARHC(int const stride, void * const _hoops_RAHC):
	_hoops_CCHRR((unsigned short*)_hoops_RAHC), _hoops_GSHRR(stride)
	{
	}

	~_hoops_GARHC(){}

	void _hoops_IRA(int const stride, void * const _hoops_RAHC)
	{
		_hoops_CCHRR = (unsigned short *) _hoops_RAHC;
		_hoops_GSHRR = stride;
	}

	void _hoops_RSHRR(_hoops_GARHC const source, int const _hoops_ASHRR)
	{
		int i = 0;
		unsigned short *_hoops_PCAP = _hoops_CCHRR;
		unsigned short *src = source._hoops_CCHRR;

		if (source._hoops_GSHRR == _hoops_GSHRR)
			_hoops_AIGA(src, _hoops_ASHRR * _hoops_GSHRR, short, _hoops_PCAP);
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

	bool const operator==(_hoops_GARHC const &right) const {
		return (this->_hoops_CCHRR == right._hoops_CCHRR);
	}
	bool const operator!=(_hoops_GARHC const &right) const {
		return (this->_hoops_CCHRR != right._hoops_CCHRR);
	}

	_hoops_GARHC const & operator=(int const number) {
		if (_hoops_GSHRR == 2)
			*((int *) _hoops_CCHRR) = number;
		else
			*_hoops_CCHRR = number;
		return *this;
	}
	_hoops_GARHC const & operator++() {
		_hoops_CCHRR += _hoops_GSHRR;
		return *this;
	}
	_hoops_GARHC const & operator--() {
		_hoops_CCHRR -= _hoops_GSHRR;
		return *this;
	}
	_hoops_GARHC const & operator+=(int const _hoops_GCCGR) {
		_hoops_CCHRR += _hoops_GCCGR * _hoops_GSHRR;
		return *this;
	}
	_hoops_GARHC const & operator-=(int const _hoops_GCCGR) {
		_hoops_CCHRR -= _hoops_GCCGR * _hoops_GSHRR;
		return *this;
	}
	_hoops_GARHC const operator+(int const _hoops_GCCGR) const {
		_hoops_GARHC _hoops_SGIRR;
		_hoops_SGIRR._hoops_CCHRR = _hoops_CCHRR + _hoops_GCCGR * _hoops_GSHRR;
		_hoops_SGIRR._hoops_GSHRR = _hoops_GSHRR;
		return _hoops_SGIRR;
	}
	_hoops_GARHC operator-(int const _hoops_GCCGR) const {
		return *this + (-_hoops_GCCGR);
	}
	_hoops_GARHC operator[](int const index) {
		return _hoops_GARHC(_hoops_GSHRR, (void*)(_hoops_CCHRR + index*_hoops_GSHRR));
	}

	int const operator-(_hoops_GARHC const &right) const {
		return (this->_hoops_CCHRR - right._hoops_CCHRR) / _hoops_GSHRR;
	}

public:
	unsigned short *_hoops_CCHRR;
	unsigned short _hoops_GSHRR;
};


typedef enum _hoops_RARHC
{
	HOGL_Invalid = 0,
	_hoops_AARHC = 1,			// _hoops_GIHA _hoops_GCSP _hoops_GAPA _hoops_IIRGR
	_hoops_PARHC = 2,	// _hoops_GIHA _hoops_GCSP _hoops_GIAA, _hoops_HIH _hoops_HAR _hoops_GAPA, _hoops_IIRGR.  _hoops_IAS._hoops_ISHI. _hoops_GPIC _hoops_RCA, _hoops_HIH _hoops_SR'_hoops_ASAR _hoops_SHSS _hoops_IS _hoops_AGSGR _hoops_PSAP _hoops_GGAR
	_hoops_HARHC = 3,			// _hoops_GIHA _hoops_HAR _hoops_GCSP.  _hoops_HAHH _hoops_CGPR _hoops_IIH _hoops_CHR _hoops_PGSGR _hoops_HGSGR _hoops_IH _hoops_IGSGR _hoops_SARR, _hoops_IAS._hoops_ISHI. _hoops_GPIC-_hoops_CIP _hoops_HIH _hoops_GAGS
	HOGL_Unknown_Smooth = 4				// _hoops_RHGC _hoops_IGH _hoops_IARHC _hoops_PAR _hoops_CARHC.
} _hoops_SARHC;


local _hoops_SARHC _hoops_GPRHC (
	Tristrip const *ts,
	_hoops_CIGA const &_hoops_SIGA,
	OGL_Display_List_Bin alter *_hoops_RRHA)
{
	bool _hoops_PRHA;
	unsigned int flags;

	if (_hoops_RRHA) {
		_hoops_RRHA->_hoops_CRHA->ResetCursor();
		_hoops_IPSGC *pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
		ts = (Tristrip const *) pair->geo;
		flags = _hoops_RRHA->_hoops_AGRI;
	}
	else
		flags = ts->_hoops_SRHA;

	_hoops_PRHA = (
		(ts->_hoops_ICHA) ||
		(ts->_hoops_PCHA) ||
		ANYBIT(flags, _hoops_GGIA|DL_FORCE_SMOOTH_SHADE_MODEL) ||
		_hoops_SIGA->_hoops_CHA->_hoops_ARIR);

	// _hoops_ISRS _hoops_AIAH _hoops_HICP, _hoops_HIS _hoops_RGAR _hoops_RRP _hoops_IS _hoops_CAHA _hoops_GGSR _hoops_RPP _hoops_SR _hoops_RRP _hoops_GPHA _hoops_GGAR
	if (BIT(flags, DL_DO_NOT_RECOMPILE)) {
		if (_hoops_PRHA)
			return HOGL_Unknown_Smooth;
		else
			return _hoops_PARHC;
	}

	// _hoops_SSCR _hoops_GGSR _hoops_PGAP _hoops_CRHH _hoops_CRAA _hoops_IS _hoops_IRAA, _hoops_PPR _hoops_HGCR _hoops_IPPAR _hoops_CIRGR/_hoops_CPPAR
	if (ts->_hoops_PRHH || ts->_hoops_PAGI) {
		if (_hoops_PRHA)
			return _hoops_HARHC;
		else
			return _hoops_PARHC;
	}
	else
		return _hoops_AARHC;
}


struct _hoops_RPRHC {
	int _hoops_HSARC;
	int *_hoops_APRHC;
	_hoops_GARHC _hoops_PPRHC;
	_hoops_GARHC _hoops_HPRHC;
};


#define _hoops_IPRHC(point_count,_hoops_AGPRC) _hoops_GHIA( \
	_hoops_AGPRC = 2; \
	if(point_count < 0xffff) \
		_hoops_AGPRC = 1; \
)


#define _hoops_CPRHC 16
#define _hoops_SPRHC 4

class IntFifo {

protected:
	Memory_Pool * memory_pool;
	int _hoops_RAIRR;
	int m_data[_hoops_CPRHC];
	unsigned int *_hoops_GHRHC;
	int _hoops_RHRHC;
	int _hoops_AHRHC;
	int _hoops_PHRHC;

	//_hoops_HRS _hoops_RCPP _hoops_RPP _hoops_SCH _hoops_CSAP _hoops_AIAH _hoops_ARP
	bool _hoops_HHRHC (int _hoops_HAGR) {
		int bit = _hoops_HAGR%32;
		int offset = _hoops_HAGR/32;
		if (BIT(_hoops_GHRHC[offset], bit))
			return false;
		_hoops_GHRHC[offset] |= bit;
		return true;
	}
	void _hoops_IHRHC (int _hoops_HAGR) {
		int bit = _hoops_HAGR%32;
		int offset = _hoops_HAGR/32;
		_hoops_GHRHC[offset] &= ~bit;
	}


public:
	IntFifo(Memory_Pool * _hoops_CHRHC) : memory_pool(_hoops_CHRHC) {
		ZERO_ARRAY (m_data, _hoops_CPRHC, int);
		_hoops_GHRHC = 0;
	}
	~IntFifo() {
		if (_hoops_GHRHC)
			FREE_ARRAY (_hoops_GHRHC, _hoops_RHRHC, unsigned int);
	}
	bool IsResident (int _hoops_HAGR) {
		int bit = _hoops_HAGR%32;
		int offset = _hoops_HAGR/32;
		return BIT(_hoops_GHRHC[offset], bit);
	}

	void _hoops_IRA (int point_count) {
		_hoops_RAIRR = point_count;
		_hoops_RHRHC = 1 + _hoops_RAIRR/32;
		POOL_ZALLOC_ARRAY_CACHED (_hoops_GHRHC, _hoops_RHRHC, unsigned int, memory_pool);
		_hoops_PHRHC = false;
		_hoops_AHRHC = 0;
	}
	int Peek (int i) {
		return m_data[(_hoops_AHRHC + i) % _hoops_CPRHC];
	}
	void Push (int _hoops_HAGR) {
		if (_hoops_HHRHC (_hoops_HAGR)) {
			if (_hoops_PHRHC)
				_hoops_IHRHC (m_data[_hoops_AHRHC]);
			_hoops_AHRHC++;
			if (_hoops_AHRHC == _hoops_CPRHC) {
				_hoops_AHRHC = 0;
				_hoops_PHRHC = true;
			}
			m_data[_hoops_AHRHC] = _hoops_HAGR;
		}
	}
};


class OptimizerScratch : public CMO_Pooled
{
  protected:
	int *_hoops_SHRHC;			//_hoops_GIRHC
	int _hoops_RIRHC;	//_hoops_GIRHC
	int **_hoops_AIRHC;					//_hoops_GIRHC
	int _hoops_PIRHC;			//_hoops_GIRHC
	unsigned char *_hoops_AHCCP;		//_hoops_GIRHC
	int _hoops_HIRHC;		//_hoops_GIRHC

	unsigned short *vertex_indices_long;	//_hoops_IIRHC
	int _hoops_CIRHC;		//_hoops_IIRHC
	unsigned short *_hoops_SIRHC;	//_hoops_IIRHC
	int _hoops_GCRHC;		//_hoops_IIRHC
	Point *points;							//_hoops_IIRHC
	int _hoops_CAHI;					//_hoops_IIRHC
	Vector *normals;						//_hoops_IIRHC
	int _hoops_RCRHC;					//_hoops_IIRHC
	RGB *colors;							//_hoops_IIRHC
	int _hoops_ACRHC;					//_hoops_IIRHC
	_hoops_RSSH * parameters[48];				//_hoops_IIRHC
	int _hoops_PCRHC[48];			//_hoops_IIRHC
	float *data;							//_hoops_IIRHC
	int _hoops_HCRHC;						//_hoops_IIRHC
	int *_hoops_PHAS;							//_hoops_IIRHC
	int _hoops_ICRHC;					//_hoops_IIRHC
	int *_hoops_CCRHC;					//_hoops_IIRHC
	int _hoops_SCRHC;			//_hoops_IIRHC

	int *_hoops_CPGCP;					//_hoops_GSRHC
	int _hoops_RSRHC;		//_hoops_GSRHC

  public:

	Memory_Pool * memory_pool;

	int *GetTriangleStarts (int _hoops_ASRHC) {
		if (_hoops_ASRHC > _hoops_RIRHC) {
			if (_hoops_SHRHC)
				FREE_ARRAY (_hoops_SHRHC, _hoops_RIRHC, int);
			POOL_ALLOC_ARRAY_CACHED (_hoops_SHRHC, _hoops_ASRHC, int, memory_pool);
			_hoops_RIRHC = _hoops_ASRHC;
		}
		ZERO_ARRAY (_hoops_SHRHC, _hoops_ASRHC, int);
		return _hoops_SHRHC;
	}

	int **GetVptrs (int _hoops_ASRHC) {
		if (_hoops_ASRHC > _hoops_PIRHC) {
			if (_hoops_AIRHC)
				FREE_ARRAY (_hoops_AIRHC, _hoops_PIRHC, int *);
			POOL_ALLOC_ARRAY_CACHED (_hoops_AIRHC, _hoops_ASRHC, int *, memory_pool);
			_hoops_PIRHC = _hoops_ASRHC;
		}
		ZERO_ARRAY (_hoops_AIRHC, _hoops_ASRHC, int *);
		return _hoops_AIRHC;
	}

	unsigned char *GetHistogram (int _hoops_ASRHC) {
		if (_hoops_ASRHC > _hoops_HIRHC) {
			if (_hoops_AHCCP)
				FREE_ARRAY (_hoops_AHCCP, _hoops_HIRHC, unsigned char);
			POOL_ALLOC_ARRAY_CACHED (_hoops_AHCCP, _hoops_ASRHC, unsigned char, memory_pool);
			_hoops_HIRHC = _hoops_ASRHC;
		}
		ZERO_ARRAY (_hoops_AHCCP, _hoops_ASRHC, unsigned char);
		return _hoops_AHCCP;
	}

	unsigned short *GetVertexIndicesLong (int _hoops_ASRHC) {
		if (_hoops_ASRHC > _hoops_CIRHC) {
			if (vertex_indices_long)
				FREE_ARRAY (vertex_indices_long, _hoops_CIRHC, unsigned short);
			POOL_ALLOC_ARRAY_CACHED (vertex_indices_long, _hoops_ASRHC, unsigned short, memory_pool);
			_hoops_CIRHC = _hoops_ASRHC;
		}
		ZERO_ARRAY (vertex_indices_long, _hoops_ASRHC, unsigned short);
		return vertex_indices_long;
	}

	unsigned short *GetVertexIndicesShort (int _hoops_ASRHC) {
		if (_hoops_ASRHC > _hoops_GCRHC) {
			if (_hoops_SIRHC)
				FREE_ARRAY (_hoops_SIRHC, _hoops_GCRHC, unsigned short);
			POOL_ALLOC_ARRAY_CACHED (_hoops_SIRHC, _hoops_ASRHC, unsigned short, memory_pool);
			_hoops_GCRHC = _hoops_ASRHC;
		}
		ZERO_ARRAY (_hoops_SIRHC, _hoops_ASRHC, unsigned short);
		return _hoops_SIRHC;
	}

	Point *GetPoints (int _hoops_ASRHC) {
		if (_hoops_ASRHC > _hoops_CAHI) {
			if (points)
				FREE_ARRAY (points, _hoops_CAHI, Point);
			POOL_ALLOC_ARRAY_CACHED (points, _hoops_ASRHC, Point, memory_pool);
			_hoops_CAHI = _hoops_ASRHC;
		}
		ZERO_ARRAY (points, _hoops_ASRHC, Point);
		return points;
	}

	Vector *GetNormals (int _hoops_ASRHC) {
		if (_hoops_ASRHC > _hoops_RCRHC) {
			if (normals)
				FREE_ARRAY (normals, _hoops_RCRHC, Vector);
			POOL_ALLOC_ARRAY_CACHED (normals, _hoops_ASRHC, Vector, memory_pool);
			_hoops_RCRHC = _hoops_ASRHC;
		}
		ZERO_ARRAY (normals, _hoops_ASRHC, Vector);
		return normals;
	}

	RGB *GetColors (int _hoops_ASRHC) {
		if (_hoops_ASRHC > _hoops_ACRHC) {
			if (colors)
				FREE_ARRAY (colors, _hoops_ACRHC, RGB);
			POOL_ALLOC_ARRAY_CACHED (colors, _hoops_ASRHC, RGB, memory_pool);
			_hoops_ACRHC = _hoops_ASRHC;
		}
		ZERO_ARRAY (colors, _hoops_ASRHC, RGB);
		return colors;
	}


	_hoops_RSSH *GetParameters (int _hoops_ASRHC, int _hoops_RHGPC = 0) {
		if (_hoops_ASRHC > _hoops_PCRHC[_hoops_RHGPC]) {
			if (parameters[_hoops_RHGPC])
				FREE_ARRAY (parameters[_hoops_RHGPC], _hoops_PCRHC[_hoops_RHGPC], _hoops_RSSH);
			POOL_ALLOC_ARRAY_CACHED (parameters[_hoops_RHGPC], _hoops_ASRHC, _hoops_RSSH, memory_pool);
			_hoops_PCRHC[_hoops_RHGPC] = _hoops_ASRHC;
		}
		ZERO_ARRAY (parameters[_hoops_RHGPC], _hoops_ASRHC, _hoops_RSSH);
		return parameters[_hoops_RHGPC];
	}

	_hoops_RSSH *_hoops_PSRHC (int _hoops_RHGPC = 0) {
		return parameters[_hoops_RHGPC];
	}


	float *GetData (int _hoops_ASRHC) {
		if (_hoops_ASRHC > _hoops_HCRHC) {
			if (data)
				FREE_ARRAY (data, _hoops_HCRHC, float);
			POOL_TRY_ALLOC_ARRAY_CACHED (data, _hoops_ASRHC, float, memory_pool);
			if (!data) {
				_hoops_HCRHC = 0;
				return null;
			}
			_hoops_HCRHC = _hoops_ASRHC;
		}
		ZERO_ARRAY (data, _hoops_ASRHC, float);
		return data;
	}

	int *_hoops_HSRHC (int _hoops_ASRHC) {
		if (_hoops_ASRHC > _hoops_ICRHC) {
			if (_hoops_PHAS)
				FREE_ARRAY (_hoops_PHAS, _hoops_ICRHC, int);
			POOL_ALLOC_ARRAY_CACHED (_hoops_PHAS, _hoops_ASRHC, int, memory_pool);
			_hoops_ICRHC = _hoops_ASRHC;
		}
		ZERO_ARRAY (_hoops_PHAS, _hoops_ASRHC, int);
		return _hoops_PHAS;
	}

	int *_hoops_ISRHC (int _hoops_ASRHC) {
		if (_hoops_ASRHC > _hoops_SCRHC) {
			if (_hoops_CCRHC)
				FREE_ARRAY (_hoops_CCRHC, _hoops_SCRHC, int);
			POOL_ALLOC_ARRAY_CACHED (_hoops_CCRHC, _hoops_ASRHC, int, memory_pool);
			_hoops_SCRHC = _hoops_ASRHC;
		}
		ZERO_ARRAY (_hoops_CCRHC, _hoops_ASRHC, int);
		return _hoops_CCRHC;
	}

	int *GetTriangles (int _hoops_ASRHC) {
		if (_hoops_ASRHC > _hoops_RSRHC) {
			if (_hoops_CPGCP)
				FREE_ARRAY (_hoops_CPGCP, _hoops_RSRHC, int);
			POOL_ALLOC_ARRAY_CACHED (_hoops_CPGCP, _hoops_ASRHC, int, memory_pool);
			_hoops_RSRHC = _hoops_ASRHC;
		}
		ZERO_ARRAY (_hoops_CPGCP, _hoops_ASRHC, int);
		return _hoops_CPGCP;
	}

	OptimizerScratch (Memory_Pool * _hoops_CHRHC) {
		memory_pool = _hoops_CHRHC;
		_hoops_SHRHC = 0;
		_hoops_RIRHC = 0;
		_hoops_PIRHC = 0;
		_hoops_AIRHC = 0;
		_hoops_AHCCP = 0;
		_hoops_HIRHC = 0;
		vertex_indices_long = 0;
		_hoops_CIRHC = 0;
		_hoops_SIRHC = 0;
		_hoops_GCRHC = 0;
		points = 0;
		_hoops_CAHI = 0;
		normals = 0;
		_hoops_RCRHC = 0;
		colors = 0;
		_hoops_ACRHC = 0;
		ZERO_ARRAY(parameters, 48, _hoops_RSSH);
		ZERO_ARRAY(_hoops_PCRHC, 48, int);
		data = 0;
		_hoops_HCRHC = 0;
		_hoops_PHAS = 0;
		_hoops_ICRHC = 0;
		_hoops_CCRHC = 0;
		_hoops_SCRHC = 0;
		_hoops_CPGCP = 0;
		_hoops_RSRHC = 0;
	}
	~OptimizerScratch () {
		if (_hoops_SHRHC)
			FREE_ARRAY (_hoops_SHRHC, _hoops_RIRHC, int);
		if (_hoops_AIRHC)
			FREE_ARRAY (_hoops_AIRHC, _hoops_PIRHC, int *);
		if (_hoops_AHCCP)
			FREE_ARRAY (_hoops_AHCCP, _hoops_HIRHC, unsigned char);
		if (vertex_indices_long)
			FREE_ARRAY (vertex_indices_long, _hoops_CIRHC, unsigned short);
		if (_hoops_SIRHC)
			FREE_ARRAY (_hoops_SIRHC, _hoops_GCRHC, unsigned short);
		if (points)
			FREE_ARRAY (points, _hoops_CAHI, Point);
		if (normals)
			FREE_ARRAY (normals, _hoops_RCRHC, Vector);
		if (colors)
			FREE_ARRAY (colors, _hoops_ACRHC, RGB);
		for(int i = 0; i < 48; i++){
			if (parameters[i]){
				FREE_ARRAY (parameters[i], _hoops_PCRHC[i], _hoops_RSSH);
				parameters[i] = 0;
				_hoops_PCRHC[i] = 0;
			}
		}
		if (data)
			FREE_ARRAY (data, _hoops_HCRHC, float);
		if (_hoops_PHAS)
			FREE_ARRAY (_hoops_PHAS, _hoops_ICRHC, int);
		if (_hoops_CCRHC)
			FREE_ARRAY (_hoops_CCRHC, _hoops_SCRHC, int);
		if (_hoops_CPGCP)
			FREE_ARRAY (_hoops_CPGCP, _hoops_RSRHC, int);
	}
};



local bool optimize_triangle_list (
		Tristrip const *ts,
		int _hoops_CIIPP,
		int alter *outcount,
		int alter *output,
		OptimizerScratch *scratch)
{
	int a, b, i, j, k;
	int *_hoops_SHRHC, starts_allocated;
	unsigned char *_hoops_AHCCP;
	int **_hoops_AIRHC; //_hoops_PCCP _hoops_CRPR _hoops_IIGR _hoops_AII _hoops_CRGR _hoops_RH _hoops_SCPH _hoops_RRGPR _hoops_CRPR
	bool _hoops_CIPAR;
	int _hoops_HAGR, v;
	int _hoops_APPH;
	int tri;
	IntFifo _hoops_GCAHA(scratch->memory_pool);
	int finalized;
	int _hoops_SSAC;
	int _hoops_ACCAA;
	int _hoops_HSPI, _hoops_ISPI, _hoops_CSPI;
	bool status = true;

	if (ts->total < _hoops_CPRHC)
		return false;

	_hoops_APPH = ts->total - 2*ts->_hoops_PHHA;
	starts_allocated = 3*_hoops_APPH;
	_hoops_SHRHC = scratch->GetTriangleStarts (starts_allocated);
	_hoops_AIRHC = scratch->GetVptrs (ts->point_count);
	_hoops_AHCCP = scratch->GetHistogram (ts->point_count);

	k = 0;
	for (i = 0 ; i < ts->_hoops_PHHA ; i++) {
		if (ts->lengths[i] < _hoops_CIIPP) {
			_hoops_HSPI = ts->_hoops_AIHA[k];
			_hoops_ISPI = ts->_hoops_AIHA[k+1];
			for (j = 0 ; j < ts->lengths[i]-2 ; j++) {
				_hoops_CSPI = ts->_hoops_AIHA[k+2];
				if (_hoops_HSPI != _hoops_ISPI && _hoops_ISPI != _hoops_CSPI && _hoops_HSPI != _hoops_CSPI) {
					if (_hoops_AHCCP[_hoops_HSPI] == 0xFF)
						status = false;
					if (_hoops_AHCCP[_hoops_ISPI] == 0xFF)
						status = false;
					if (_hoops_AHCCP[_hoops_CSPI] == 0xFF)
						status = false;
					_hoops_AHCCP[_hoops_HSPI]++;
					_hoops_AHCCP[_hoops_ISPI]++;
					_hoops_AHCCP[_hoops_CSPI]++;
				}
				k++;
				_hoops_HSPI = _hoops_ISPI;
				_hoops_ISPI = _hoops_CSPI;
			}
			k += 2;
		}
		else
			k += ts->lengths[i];
	}
	if (!status)
		goto _hoops_HPAGR;
	_hoops_AIRHC[0] = _hoops_SHRHC;
	for (i = 1 ; i < ts->point_count ; i++ )
		_hoops_AIRHC[i] = _hoops_AIRHC[i-1] + _hoops_AHCCP[i-1];
	ASSERT (_hoops_AIRHC[ts->point_count-1] <= _hoops_SHRHC + starts_allocated);
	_hoops_SSAC = ts->point_count-1;
	_hoops_APPH = (_hoops_AIRHC[_hoops_SSAC] + _hoops_AHCCP[_hoops_SSAC] - _hoops_SHRHC) / 3;
	k = 0;
	for (i = 0 ; i < ts->_hoops_PHHA ; i++) {
		if (ts->lengths[i] < _hoops_CIIPP) {
			_hoops_CIPAR = false;
			_hoops_HSPI = ts->_hoops_AIHA[k];
			_hoops_ISPI = ts->_hoops_AIHA[k+1];
			for (j = 0 ; j < ts->lengths[i]-2 ; j++) {
				_hoops_CSPI = ts->_hoops_AIHA[k+2];
				if (_hoops_HSPI != _hoops_ISPI && _hoops_ISPI != _hoops_CSPI && _hoops_HSPI != _hoops_CSPI) {
					if (_hoops_CIPAR)
						_hoops_HAGR = ~k;
					else
						_hoops_HAGR = k;
					*_hoops_AIRHC[_hoops_HSPI]++ = _hoops_HAGR;
					*_hoops_AIRHC[_hoops_ISPI]++ = _hoops_HAGR;
					*_hoops_AIRHC[_hoops_CSPI]++ = _hoops_HAGR;
				}
				_hoops_CIPAR = !_hoops_CIPAR;
				k++;
				_hoops_HSPI = _hoops_ISPI;
				_hoops_ISPI = _hoops_CSPI;
			}
			k += 2;
		}
		else
			k += ts->lengths[i];
	}
	_hoops_AIRHC[0] = _hoops_SHRHC;
	for (i = 1 ; i < ts->point_count ; i++ )
		_hoops_AIRHC[i] = _hoops_AIRHC[i-1] + _hoops_AHCCP[i-1];

	_hoops_GCAHA._hoops_IRA (ts->point_count);
	_hoops_GCAHA.Push (ts->_hoops_AIHA[0]);
	k = 0;
	finalized = 0;
	for (;;) {
		_hoops_ACCAA = _hoops_IICIA;
		for (j = _hoops_CPRHC-1 ; j >= 0 ; j--) {
			v = _hoops_GCAHA.Peek(j);
			if (_hoops_AHCCP [v] == 0) {
				continue;
			}
			else if (_hoops_AHCCP [v] == 1) {
				_hoops_ACCAA = v;
				break;
			}
			else if (_hoops_ACCAA == _hoops_IICIA ||
					 _hoops_AHCCP [v] < _hoops_AHCCP[_hoops_ACCAA])
				_hoops_ACCAA = v;
			if (j < _hoops_CPRHC - _hoops_SPRHC &&
				_hoops_ACCAA != _hoops_IICIA)
				break;
		}
		// _hoops_ISAP _hoops_IHAH-_hoops_CSRHC _hoops_GSGI.  _hoops_SSS _hoops_IRS _hoops_CCAH _hoops_GPHA _hoops_IS _hoops_HISA _hoops_CCA
		if (_hoops_ACCAA == _hoops_IICIA) {
			while (finalized < ts->point_count) {
				if (_hoops_AHCCP[finalized] > 0) {
					_hoops_GCAHA.Push (finalized);
					_hoops_ACCAA = finalized;
					break;
				}
				finalized++;
			}
		}
		if (_hoops_ACCAA == _hoops_IICIA)
			break;

		while (_hoops_AHCCP[_hoops_ACCAA]) {
			//_hoops_SAHR _hoops_SRPS _hoops_RH _hoops_SRS _hoops_SCPH _hoops_HII _hoops_GPHA "_hoops_AAH"'_hoops_GRI _hoops_HIGR
			tri = *_hoops_AIRHC[_hoops_ACCAA];
			output[k] = tri;
			if (tri < 0)
				tri = ~tri;
			//_hoops_SR'_hoops_RISP _hoops_GSCSR _hoops_RH _hoops_SCPH _hoops_CRGR _hoops_RH _hoops_IIPR, _hoops_HA _hoops_SR _hoops_RRP _hoops_IS _hoops_HASIR _hoops_SCH
			//_hoops_HII _hoops_RGCI _hoops_IHSR _hoops_GIHA' _hoops_SCPH _hoops_HIGR.
			for (a = 0 ; a < 3 ; a++) {
				v = ts->_hoops_AIHA[tri + a];
				_hoops_SSAC = _hoops_AHCCP[v] - 1;
				ASSERT (_hoops_AHCCP[v] > 0);
				_hoops_AHCCP[v]--;
				if (v == _hoops_ACCAA) {
					_hoops_AIRHC[v][0] = _hoops_AIRHC[v][_hoops_SSAC];
				}
				else {
					_hoops_GCAHA.Push(v);
					b = 0;
					for (;;) {
						if (_hoops_AIRHC[v][b] == output[k]) {
							_hoops_AIRHC[v][b] = _hoops_AIRHC[v][_hoops_SSAC];
							break;
						}
						ASSERT (b <= _hoops_AHCCP[v]);
						b++;
					}
				}
			}
			k++;
		}
	}
	*outcount = k;
	ASSERT (k == _hoops_APPH);
_hoops_HPAGR:
	return status;

} // _hoops_RSGR _hoops_API '_hoops_SGGC _hoops_SCPH _hoops_HIGR'


#define _hoops_SSRHC(index, _hoops_PHAS, _hoops_GGAHC) \
	(_hoops_PHAS[index] < 0 ? (_hoops_CCRHC[_hoops_GGAHC] = index, _hoops_PHAS[index] = _hoops_GGAHC++) : _hoops_PHAS[index])

/*
 * _hoops_PGAA
 */
local void stuff_tristrip_index_buffers (
		Tristrip const *ts,
		bool _hoops_HAHRC,
		int _hoops_RGAHC,
		int _hoops_CIIPP,
		bool _hoops_AGAHC,
		_hoops_RPRHC *pack,
		int alter *_hoops_CCRHC,
		int alter *_hoops_CAPHA,
		OptimizerScratch *scratch)
{
	int i, j;
	int const *src;
	int _hoops_PGAHC = 0;
	int _hoops_GGAHC = 0;
	int _hoops_HGAHC[3];
	bool _hoops_IGAHC = true;
	bool _hoops_CIPAR = false, _hoops_CGAHC = false;
	bool _hoops_SGAHC = true;
	bool _hoops_GRAHC = false;
	int *_hoops_PHAS;

	_hoops_PHAS = scratch->_hoops_HSRHC (ts->point_count);
	SET_MEMORY (_hoops_PHAS, ts->point_count * sizeof(int), -1);

	/* _hoops_ICHRR _hoops_IIRGR */
	if (_hoops_CIIPP >= 4) {
		if (_hoops_SGAHC) {
			int *_hoops_CPGCP;
			//_hoops_PCCP _hoops_AAPA _hoops_ASCR, _hoops_GAR _hoops_AIHAR _hoops_GRS _hoops_RSGR _hoops_GH _hoops_GHHS _hoops_IPHAR
			int _hoops_APPH = ts->total - 2*ts->_hoops_PHHA;
			int _hoops_RRAHC, _hoops_HAGR;

			_hoops_CPGCP = scratch->GetTriangles (_hoops_APPH);  //_hoops_SRSPC (_hoops_HIPH, _hoops_ARAHC, _hoops_SCSH);
			if (optimize_triangle_list (ts, _hoops_CIIPP, &_hoops_RRAHC, _hoops_CPGCP, scratch)) {
				_hoops_GRAHC = true;
				for (i = 0 ; i < _hoops_RRAHC ; i++) {
					_hoops_HAGR = _hoops_CPGCP[i];
					if (_hoops_HAGR < 0) {
						_hoops_CIPAR = !_hoops_HAHRC;
						_hoops_HAGR = ~_hoops_HAGR;
					}
					else
						_hoops_CIPAR = _hoops_HAHRC;
					src = ts->_hoops_AIHA + _hoops_HAGR;
					ASSERT (src[0] >= 0 && src[1] >= 0 && src[2] >= 0);
					ASSERT (src[0] < ts->point_count && src[1] < ts->point_count && src[2] < ts->point_count);
					_hoops_HGAHC[0] = _hoops_SSRHC (src[0], _hoops_PHAS, _hoops_GGAHC);
					_hoops_HGAHC[1] = _hoops_SSRHC (src[1], _hoops_PHAS, _hoops_GGAHC);
					_hoops_HGAHC[2] = _hoops_SSRHC (src[2], _hoops_PHAS, _hoops_GGAHC);
					pack->_hoops_HPRHC[0] = _hoops_HGAHC[0] + _hoops_RGAHC;
					if (_hoops_CIPAR) {
						pack->_hoops_HPRHC[1] = _hoops_HGAHC[2] + _hoops_RGAHC;
						pack->_hoops_HPRHC[2] = _hoops_HGAHC[1] + _hoops_RGAHC;
					}
					else {
						pack->_hoops_HPRHC[1] = _hoops_HGAHC[1] + _hoops_RGAHC;
						pack->_hoops_HPRHC[2] = _hoops_HGAHC[2] + _hoops_RGAHC;
					}
					pack->_hoops_HPRHC += 3;
				}
			}
		}
		if (!_hoops_GRAHC) {
			src = ts->_hoops_AIHA;
			for (i = 0 ; i < ts->_hoops_PHHA ; i++) {
				if (ts->lengths[i] < _hoops_CIIPP) {
					_hoops_CIPAR = _hoops_HAHRC;
					for (j = 0 ; j < ts->lengths[i]-2 ; j++) {
						_hoops_HGAHC[0] = _hoops_SSRHC (src[0], _hoops_PHAS, _hoops_GGAHC);
						_hoops_HGAHC[1] = _hoops_SSRHC (src[1], _hoops_PHAS, _hoops_GGAHC);
						_hoops_HGAHC[2] = _hoops_SSRHC (src[2], _hoops_PHAS, _hoops_GGAHC);
						pack->_hoops_HPRHC[0] = _hoops_HGAHC[0] + _hoops_RGAHC;
						if (_hoops_CIPAR) {
							pack->_hoops_HPRHC[1] = _hoops_HGAHC[2] + _hoops_RGAHC;
							pack->_hoops_HPRHC[2] = _hoops_HGAHC[1] + _hoops_RGAHC;
						}
						else {
							pack->_hoops_HPRHC[1] = _hoops_HGAHC[1] + _hoops_RGAHC;
							pack->_hoops_HPRHC[2] = _hoops_HGAHC[2] + _hoops_RGAHC;
						}
						pack->_hoops_HPRHC += 3;
						src++;
						_hoops_CIPAR = !_hoops_CIPAR;
					}
					src += 2;
				}
			}
		}
	}

	/* _hoops_RGRRR _hoops_IIRGR */
	src = ts->_hoops_AIHA;
	for (i = 0 ; i < ts->_hoops_PHHA ; i++) {
		if (ts->lengths[i] >= _hoops_CIIPP) {
			_hoops_PGAHC += ts->lengths[i];
			_hoops_HGAHC[0] = _hoops_SSRHC (src[0], _hoops_PHAS, _hoops_GGAHC);
			if (_hoops_AGAHC) {
				/* _hoops_SPGCA _hoops_CCA _hoops_RH _hoops_PGHC _hoops_CRHH */
				if (!_hoops_IGAHC) {
					int temp = *pack->_hoops_PPRHC[-1];
					pack->_hoops_PPRHC[0] = temp;
					pack->_hoops_PPRHC[1] = _hoops_HGAHC[0] + _hoops_RGAHC;
					pack->_hoops_PPRHC += 2;
					_hoops_PGAHC += 2;
				}
				else
					_hoops_IGAHC = false;

				if (_hoops_HAHRC)
					_hoops_CGAHC = !_hoops_CGAHC;
				if (_hoops_CGAHC) {
					/* _hoops_PIIA _hoops_RH _hoops_CGRIR _hoops_RSSP _hoops_HPP _hoops_ISCA _hoops_RH _hoops_SRS _hoops_GPHA */
					pack->_hoops_PPRHC[0] = _hoops_HGAHC[0] + _hoops_RGAHC;
					++pack->_hoops_PPRHC;
					_hoops_PGAHC++;
					_hoops_CGAHC = false;
				}
				if (ts->lengths[i] & 0x1)
					_hoops_CGAHC = true;
			}

			for (j = 0 ; j < ts->lengths[i] ; j++) {
				_hoops_HGAHC[0] = _hoops_SSRHC (src[0], _hoops_PHAS, _hoops_GGAHC);
				pack->_hoops_PPRHC[0] = _hoops_HGAHC[0] + _hoops_RGAHC;
				++pack->_hoops_PPRHC;
				src++;
			}

			if (!_hoops_AGAHC) {
				pack->_hoops_APRHC[0] = ts->lengths[i];
				pack->_hoops_APRHC++;
				pack->_hoops_HSARC++;
			}
		}
		else
			src += ts->lengths[i];
	}
	if (_hoops_AGAHC && _hoops_PGAHC) {
		pack->_hoops_APRHC[0] = _hoops_PGAHC;
		pack->_hoops_APRHC++;
		pack->_hoops_HSARC++;
	}
	*_hoops_CAPHA = _hoops_GGAHC;
}






local void _hoops_PRAHC (
		Net_Rendition const &		nr,
		Tristrip const *			ts,
		HOGLVertexBuffer *			_hoops_HACP,
		int							_hoops_CACP,
		_hoops_HRPA const *			matrix,
		RGB const *					_hoops_GPCP,
		int							_hoops_CRPAR)
{
	_hoops_HHA const &	matr = nr->_hoops_IHA->_hoops_CHA;
	float						_hoops_APCP;
	int 						_hoops_PSR = 0, offset = 0, param_width = ts->_hoops_GSSH ? ts->_hoops_GSSH->_hoops_GSHA : 0;
	int 						_hoops_HRAHC = 0;
	float						u, v, w;
	_hoops_RSPRC				_hoops_PPCP = _hoops_HACP->_hoops_HPCP();
	/*_hoops_IPCP _hoops_CPCP _hoops_GHCP _hoops_PIHA _hoops_SHH _hoops_GAR _hoops_SPCP:
	* _hoops_AHC
	* _hoops_GSSR
	* _hoops_HAIR
	* _hoops_HH
	*/

	// _hoops_RHCP _hoops_AHC
	if (matrix == null)
		_hoops_HACP->_hoops_AHCP(ts->points[_hoops_CACP].x, ts->points[_hoops_CACP].y, ts->points[_hoops_CACP].z);
	else {
		_hoops_APCP = 1.0f / _hoops_PHCP (matrix->elements, ts->points[_hoops_CACP]);
		_hoops_HACP->_hoops_AHCP(_hoops_HPRA(matrix->elements, ts->points[_hoops_CACP]) * _hoops_APCP,
				_hoops_IPRA(matrix->elements, ts->points[_hoops_CACP]) * _hoops_APCP,
				_hoops_CPRA(matrix->elements, ts->points[_hoops_CACP]) * _hoops_APCP);
	}

	// _hoops_RHCP _hoops_ASGA
	if (_hoops_PPCP._hoops_HHCP()) {
		if (matrix == null) {
			if (ts->_hoops_ICHA)
				_hoops_HACP->_hoops_IHCP(ts->_hoops_ICHA[_hoops_CACP].x, ts->_hoops_ICHA[_hoops_CACP].y, ts->_hoops_ICHA[_hoops_CACP].z);
			else if (ts->_hoops_PRHH)
				_hoops_HACP->_hoops_IHCP(ts->_hoops_PRHH[_hoops_CRPAR].a, ts->_hoops_PRHH[_hoops_CRPAR].b, ts->_hoops_PRHH[_hoops_CRPAR].c);
		}
		else {
			_hoops_ARPA plane;
			Vector vector;

			if (matrix->_hoops_APRA == null)
				HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)matrix);

			if (ts->_hoops_ICHA) {
				plane.a = ts->_hoops_ICHA[_hoops_CACP].x;
				plane.b = ts->_hoops_ICHA[_hoops_CACP].y;
				plane.c = ts->_hoops_ICHA[_hoops_CACP].z;
				plane.d = ts->_hoops_ICHA[_hoops_CACP].x * ts->points[_hoops_CACP].x +
					ts->_hoops_ICHA[_hoops_CACP].y * ts->points[_hoops_CACP].y +
					ts->_hoops_ICHA[_hoops_CACP].z * ts->points[_hoops_CACP].z;
			}
			else {
				plane.a = ts->_hoops_PRHH[_hoops_CRPAR].a;
				plane.b = ts->_hoops_PRHH[_hoops_CRPAR].b;
				plane.c = ts->_hoops_PRHH[_hoops_CRPAR].c;
				plane.d = ts->_hoops_PRHH[_hoops_CRPAR].d;
			}

			_hoops_RPRA const *	_hoops_APRA = matrix->_hoops_APRA->data.elements;

			vector.x = plane.a*_hoops_APRA[0][0] + plane.b*_hoops_APRA[0][1] + plane.c*_hoops_APRA[0][2] + plane.d*_hoops_APRA[0][3];
			vector.y = plane.a*_hoops_APRA[1][0] + plane.b*_hoops_APRA[1][1] + plane.c*_hoops_APRA[1][2] + plane.d*_hoops_APRA[1][3];
			vector.z = plane.a*_hoops_APRA[2][0] + plane.b*_hoops_APRA[2][1] + plane.c*_hoops_APRA[2][2] + plane.d*_hoops_APRA[2][3];
			if (BIT(matrix->_hoops_RAGR, _hoops_CHCP))
				HI_Normalize(&vector);

			_hoops_HACP->_hoops_IHCP(vector.x, vector.y, vector.z);
		}
	}

	// _hoops_RHCP _hoops_PSHA
	if (_hoops_PPCP._hoops_SHCP()) {
		const RGB *color = null;
		if (ts->_hoops_PCHA)
			color = &ts->_hoops_PCHA[_hoops_CACP];
		else if (ts->_hoops_PAGI)
			color = &ts->_hoops_PAGI[_hoops_CRPAR];
		else
			color = _hoops_GPCP;

		_hoops_HACP->color(_hoops_GICP(_hoops_RRRHC,color->red, color->green, color->blue, 1));
	}

	// _hoops_AICP _hoops_PICP _hoops_IIGR _hoops_RH _hoops_GGAR _hoops_HH _hoops_RPP _hoops_SCH _hoops_HICP
	if (ts->_hoops_SRHA & _hoops_GGIA) {
		_hoops_HACP->uvw(ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * ts->_hoops_GSSH->_hoops_GSHA],
				ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * ts->_hoops_GSSH->_hoops_GSHA+1],
				0,
				_hoops_HRAHC++);
	}

	// _hoops_GRAR _hoops_PCRR
	if (matr->_hoops_ARIR && param_width > 0) {
		_hoops_HIR *_hoops_PGC = matr->_hoops_SCA;
		_hoops_RRCC *	_hoops_HAPAR = ts->_hoops_GSSH;

		while (_hoops_PGC) {
			_hoops_PSR = _hoops_PGC->texture->_hoops_PSR;
			offset = _hoops_PGC->texture->_hoops_RSCP;
			if (_hoops_HAPAR)
					param_width = _hoops_HAPAR->_hoops_GSHA;

			if (offset > param_width)
				offset = 0;

			u = v = w = 0;
			if (_hoops_PSR != HK_PS_WORLD) {
				if (offset+0 < param_width) u = _hoops_HAPAR->_hoops_CCHA[_hoops_CACP * param_width + offset + 0];
				if (offset+1 < param_width) v = _hoops_HAPAR->_hoops_CCHA[_hoops_CACP * param_width + offset + 1];
				if (offset+2 < param_width) w = _hoops_HAPAR->_hoops_CCHA[_hoops_CACP * param_width + offset + 2];
			}

			_hoops_HACP->uvw(u, v, w, _hoops_HRAHC++);
			_hoops_PGC = _hoops_PGC->next;

			if (_hoops_HAPAR && _hoops_HAPAR->next)
					_hoops_HAPAR = _hoops_HAPAR->next;
		}

		/* _hoops_RGAR _hoops_SPI _hoops_AI _hoops_PICP _hoops_AHCA _hoops_IAPAR _hoops_PPR _hoops_SHI */
		_hoops_PSR = 0;
		offset = 0;

		if (matr->texture[_hoops_HIA]) {
			u = v = w = 0;
			if (param_width > 0) u = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + 0];
			if (param_width > 1) v = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + 1];
			if (param_width > 2) w = ts->_hoops_GSSH->_hoops_CCHA[_hoops_CACP * param_width + 2];

			_hoops_HACP->uvw(u, v, w, _hoops_HRAHC++);
		}
	}
}


//_hoops_HSPR _hoops_RIS _hoops_HRGR _hoops_GRGR _hoops_PGGA _hoops_SR _hoops_HS _hoops_HAR _hoops_GAPR _hoops_GCRHA _hoops_GSIA _hoops_IH _hoops_PGAP
//_hoops_RGR _hoops_PHPP _hoops_IS _hoops_SHH _hoops_RH _hoops_AAH _hoops_SPAHR
#if 0

/*
 * _hoops_PGAA
 */
local int _hoops_IRAHC (
		OGL_Vertex_Buffer_Object alter *_hoops_SAAS,
		Net_Rendition const & nr,
		Tristrip const *ts,
		OGL_Display_List_Bin alter *_hoops_RRHA)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	int _hoops_CARH = 0;
	bool _hoops_CCIS = false;
	_hoops_RSPRC _hoops_PPCP;
	int i, j, k;
	int _hoops_HSPI = 0, _hoops_ISPI, _hoops_CSPI;
	int total = 0;
	bool _hoops_CIPAR;
	_hoops_IRHA *pair;
	bool _hoops_CRAHC = true;
	bool _hoops_IGAHC = true;
	bool _hoops_CGAHC = false;

	if (_hoops_RRHA) {
		HI_VList_Reset_Cursor (_hoops_RRHA->_hoops_CRHA);
		pair = (_hoops_IRHA *) HI_VList_Peek_Cursor (_hoops_RRHA->_hoops_CRHA);
		if (pair->mat)
			_hoops_CCIS = true;
		if (!pair)
			return 0;
		ts = (Tristrip *)pair->geo;
	}
	_hoops_IGAHC = true;
	_hoops_CGAHC = false;
	for (;;) {
		if (_hoops_CRAHC) {
			//_hoops_CCGI _hoops_RIHA _hoops_CCA _hoops_ARHAR _hoops_HIPH
			_hoops_CARH += _hoops_RRHRC (ts);
			_hoops_SAAS->count++;
			for (i = 0 ; i < ts->_hoops_PHHA ; i++) {
				total += ts->lengths[i];
				// _hoops_HIHA _hoops_IH _hoops_RH _hoops_ARHAR _hoops_SCPH _hoops_PSPI
				if (!_hoops_IGAHC) {
					total += 2;
					if (_hoops_CGAHC)
						total++;
				}
				else
					_hoops_IGAHC = false;
				if (ts->lengths[i] & 0x1)
					_hoops_CGAHC = true;
				else
					_hoops_CGAHC = false;
			}
		}
		else {
			//_hoops_SCPH _hoops_CPCI
			_hoops_CARH += _hoops_RRHRC (ts);
			_hoops_SAAS->count++;
			for (i = 0 ; i < ts->_hoops_PHHA ; i++) {
				total += 3 * (ts->lengths[i] - 2);
			}
		}
		if (!_hoops_RRHA)
			break;
		HI_VList_Advance_Cursor (_hoops_RRHA->_hoops_CRHA);
		pair = (_hoops_IRHA *) HI_VList_Peek_Cursor (_hoops_RRHA->_hoops_CRHA);
		if (!pair)
			break;
		if (pair->mat)
			_hoops_CCIS = true;
		ts = (Tristrip const *) pair->geo;
	}

	// _hoops_RAP _hoops_GH _hoops_SRAHC
	_hoops_PPCP._hoops_AIHC();
	if (ts->_hoops_ICHA)
		_hoops_PPCP._hoops_CCRS();
	if (ts->_hoops_PCHA)
		_hoops_PPCP._hoops_RPHC();

	if (!_hoops_SAAS->_hoops_IGPRC)
		_hoops_CSRGR->_hoops_CHPGC(1, &_hoops_SAAS->_hoops_IGPRC);

	/* _hoops_CIPH _hoops_GPHA _hoops_PIH */
	_hoops_CSRGR->_hoops_PSPGI(GL_ARRAY_BUFFER_ARB, _hoops_SAAS->_hoops_IGPRC);
	_hoops_CSRGR->_hoops_HSPGI(GL_ARRAY_BUFFER_ARB, total*_hoops_PPCP._hoops_HGHS()*sizeof(float), NULL, GL_STATIC_DRAW_ARB);

	float* data = (float *)_hoops_CSRGR->_hoops_AIPGC(GL_ARRAY_BUFFER_ARB, GL_WRITE_ONLY_ARB);
	ASSERT (data != null);
	HOGLVertexBuffer _hoops_PAIH(data, _hoops_PPCP);
	if (_hoops_RRHA) {
		HI_VList_Reset_Cursor (_hoops_RRHA->_hoops_CRHA);
		pair = (_hoops_IRHA *) HI_VList_Peek_Cursor (_hoops_RRHA->_hoops_CRHA);
		ts = (Tristrip *)pair->geo;
	}

	_hoops_IGAHC = true;
	_hoops_CGAHC = false;
	for (;;) {
		k = 0;
		if (_hoops_CRAHC) {
			for (i = 0; i < ts->_hoops_PHHA ; i++) {
				if (!_hoops_IGAHC) {
					//_hoops_SPGCA _hoops_IS _hoops_RH _hoops_PGHC _hoops_CGGR.
					// _hoops_RGRCR _hoops_HRGR _hoops_RAAP _hoops_IAPR _hoops_HII _hoops_RH _hoops_PGHC _hoops_CGGR
					_hoops_AIGA (_hoops_PAIH[-1]._hoops_HACGR(), _hoops_PAIH._hoops_CACGR(), float, _hoops_PAIH[0]._hoops_HACGR());
					_hoops_PAIH++;
					if (_hoops_CGAHC) {
						_hoops_AIGA (_hoops_PAIH[-1]._hoops_HACGR(), _hoops_PAIH._hoops_CACGR(), float, _hoops_PAIH[0]._hoops_HACGR());
						_hoops_PAIH++;
					}

					_hoops_HSPI = ts->_hoops_AIHA[k];
					_hoops_PAIH._hoops_AHCP(ts->points[_hoops_HSPI].x, ts->points[_hoops_HSPI].y, ts->points[_hoops_HSPI].z);
					if (ts->_hoops_ICHA)
						_hoops_PAIH._hoops_IHCP(ts->_hoops_ICHA[_hoops_HSPI].x, ts->_hoops_ICHA[_hoops_HSPI].y, ts->_hoops_ICHA[_hoops_HSPI].z);
					_hoops_PAIH++;
				}
				else
					_hoops_IGAHC = false;

				if (ts->lengths[i] & 0x1)
					_hoops_CGAHC = true;
				else
					_hoops_CGAHC = false;

				for (j = 0 ; j < ts->lengths[i] ; j++) {
					_hoops_HSPI = ts->_hoops_AIHA[k];
					_hoops_PAIH._hoops_AHCP(ts->points[_hoops_HSPI].x, ts->points[_hoops_HSPI].y, ts->points[_hoops_HSPI].z);
					if (ts->_hoops_ICHA)
						_hoops_PAIH._hoops_IHCP(ts->_hoops_ICHA[_hoops_HSPI].x, ts->_hoops_ICHA[_hoops_HSPI].y, ts->_hoops_ICHA[_hoops_HSPI].z);
					_hoops_PAIH++;
					k++;
				}
			}
		}
		else {
			k = 0;
			for (i = 0; i < ts->_hoops_PHHA ; i++) {
				_hoops_CIPAR = false;
				for (j = 0 ; j < ts->lengths[i] - 2 ; j++) {
					_hoops_HSPI = ts->_hoops_AIHA[k];
					if (_hoops_CIPAR) {
						_hoops_ISPI = ts->_hoops_AIHA[k+2];
						_hoops_CSPI = ts->_hoops_AIHA[k+1];
					}
					else {
						_hoops_ISPI = ts->_hoops_AIHA[k+1];
						_hoops_CSPI = ts->_hoops_AIHA[k+2];
					}
					_hoops_PAIH._hoops_AHCP(ts->points[_hoops_HSPI].x, ts->points[_hoops_HSPI].y, ts->points[_hoops_HSPI].z);
					if (ts->_hoops_ICHA)
						_hoops_PAIH._hoops_IHCP(ts->_hoops_ICHA[_hoops_HSPI].x, ts->_hoops_ICHA[_hoops_HSPI].y, ts->_hoops_ICHA[_hoops_HSPI].z);
					_hoops_PAIH++;
					_hoops_PAIH._hoops_AHCP(ts->points[_hoops_ISPI].x, ts->points[_hoops_ISPI].y, ts->points[_hoops_ISPI].z);
					if (ts->_hoops_ICHA)
						_hoops_PAIH._hoops_IHCP(ts->_hoops_ICHA[_hoops_ISPI].x, ts->_hoops_ICHA[_hoops_ISPI].y, ts->_hoops_ICHA[_hoops_ISPI].z);
					_hoops_PAIH++;
					_hoops_PAIH._hoops_AHCP(ts->points[_hoops_CSPI].x, ts->points[_hoops_CSPI].y, ts->points[_hoops_CSPI].z);
					if (ts->_hoops_ICHA)
						_hoops_PAIH._hoops_IHCP(ts->_hoops_ICHA[_hoops_CSPI].x, ts->_hoops_ICHA[_hoops_CSPI].y, ts->_hoops_ICHA[_hoops_CSPI].z);
					_hoops_PAIH++;
					k++;
					_hoops_CIPAR = !_hoops_CIPAR;
				}
				k += 2;
			}
		}

		if (!_hoops_RRHA)
			break;
		HI_VList_Advance_Cursor (_hoops_RRHA->_hoops_CRHA);
		pair = (_hoops_IRHA *) HI_VList_Peek_Cursor (_hoops_RRHA->_hoops_CRHA);
		if (!pair)
			break;
		ts = (Tristrip const *) pair->geo;
	}

	_hoops_CSRGR->_hoops_PIPGC(GL_ARRAY_BUFFER_ARB);
	_hoops_CSRGR->_hoops_PSPGI (GL_ARRAY_BUFFER_ARB, null);

	_hoops_SAAS->_hoops_CPPSP = _hoops_PAIH._hoops_SACGR() * sizeof(float);
	_hoops_SAAS->_hoops_HPRAC = _hoops_PAIH._hoops_GPCGR() * sizeof(float);
	_hoops_SAAS->colors_offset = _hoops_PAIH._hoops_RPCGR() * sizeof(float);
	_hoops_SAAS->_hoops_GPSAC = _hoops_PAIH._hoops_APCGR() * sizeof(float);
	_hoops_SAAS->stride = _hoops_PAIH._hoops_CACGR() * sizeof(float);

	if (_hoops_CRAHC) {
		_hoops_SAAS->flags |= OGL_VBO_STRIP_ARRAYS;
		_hoops_SAAS->_hoops_RGPRC = total;
	}
	else {
		_hoops_SAAS->flags |= OGL_VBO_ARRAYS;
		_hoops_SAAS->_hoops_HGPRC = total;
	}

	return _hoops_CARH;

} //_hoops_RSGR _hoops_API '_hoops_CRHH _hoops_CASRR _hoops_GAAHC _hoops_ARAI'
#endif



#ifdef _hoops_RAAHC
local void _hoops_AAAHC (
		OGL_Display_List_Bin alter *_hoops_RRHA,
		OGL_Vertex_Buffer_Object alter *_hoops_SAAS)
{
	int i, count;
	float *radii;
	int *_hoops_HGA;
	_hoops_IPSGC **_hoops_PCIS;
	_hoops_IPSGC *pair;
	_hoops_SCCIR const *_hoops_PGASH = _hoops_SAAS->_hoops_PGASH;
	_hoops_SCCIR *_hoops_PAAHC;

	count = _hoops_RRHA->_hoops_CRHA->Count();
	ALLOC_ARRAY_CACHED (radii, count, float);
	ALLOC_ARRAY_CACHED (_hoops_HGA, count, int);
	ALLOC_ARRAY_CACHED (_hoops_PCIS, count, _hoops_IPSGC *);
	ZALLOC_ARRAY (_hoops_PAAHC, count, _hoops_SCCIR);
	for (i = 0 ; i < count ; i++) {
		if (_hoops_PGASH[i]) {
			radii[i] = _hoops_PGASH[i]->radius();
		}
		else
			radii[i] = 0;
		_hoops_HGA[i] = i;
	}
	HI_Sort_Array (count, radii, (void **)_hoops_HGA, sizeof(int), false);

	_hoops_RRHA->_hoops_CRHA->ResetCursor();
	for (i = 0 ; i < count ; i++) {
		pair = _hoops_RRHA->_hoops_CRHA->RemoveFirst();
		ASSERT (pair);
		_hoops_PCIS[_hoops_HGA[i]] = pair;
		_hoops_PAAHC[_hoops_HGA[i]] = _hoops_PGASH[i];
	}
	for (i = 0 ; i < count ; i++)
		_hoops_RRHA->_hoops_CRHA->AddLast(_hoops_PCIS[i]);

	for (i=0 ; i < count ; i++)
		_hoops_SAAS->_hoops_PGASH[i].release();

	FREE_ARRAY (_hoops_SAAS->_hoops_PGASH, count, _hoops_SCCIR);

	_hoops_SAAS->_hoops_PGASH = _hoops_PAAHC;

	FREE_ARRAY (radii, count, float);
	FREE_ARRAY (_hoops_HGA, count, int);
	FREE_ARRAY (_hoops_PCIS, count, _hoops_IPSGC *);
}
#endif


local void _hoops_HAAHC (
	   Tristrip const *ts,
	   OGL_Display_List_Bin alter *_hoops_RRHA,
	   OGL_Vertex_Buffer_Object alter *_hoops_SAAS,
	   bool _hoops_CCIS)
{
	_hoops_CAIS *	_hoops_PGASH;
	ZALLOC_ARRAY_CACHED (_hoops_PGASH, _hoops_SAAS->count, _hoops_CAIS);
	_hoops_SAAS->_hoops_SSARC = _hoops_PGASH;

	if (_hoops_RRHA)
		_hoops_RRHA->_hoops_CRHA->ResetCursor();

	for (int i = 0; ; i++) {

		_hoops_IPSGC *pair = null;

		if (_hoops_RRHA) {

			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();

			if (!pair)
				break;

			ts = (Tristrip const *)pair->geo;
		}

		if (ts->bounding != null) {

			if (_hoops_CCIS && pair->_hoops_CPAI)
				_hoops_PGASH[i] = ts->bounding->cuboid._hoops_SCIS(pair->_hoops_CPAI->matrix);
			else 
				_hoops_PGASH[i] = ts->bounding->sphere;
		}
		else
			_hoops_PGASH[i].radius = -1.0f;

		if (!_hoops_RRHA)
			break;

		_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
	}

}

struct _hoops_IAAHC {
	int *_hoops_CCRHC;
	int length;
};
typedef VList<_hoops_IAAHC *> _hoops_CAAHC;

/*
 * _hoops_PGAA
 */
local int _hoops_SAAHC (
	OGL_Vertex_Buffer_Object alter **_hoops_GPAHC,
	Net_Rendition const & nr,
	Tristrip const *ts,
	OGL_Display_List_Bin alter *_hoops_RRHA)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	_hoops_GRA const &_hoops_RRA = nr->_hoops_ARA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	OGL_Vertex_Buffer_Object alter *_hoops_SAAS;
	int _hoops_RGAHC = 0;
	int param_width = 0;
	int _hoops_HGPRC = 0;
	_hoops_IPSGC *pair;
	Point *points = null;
	Vector *normals = null;
	_hoops_RSSH *params = null;
	RGB *colors = null;
	unsigned short *vertex_indices_long = null, *_hoops_SIRHC = null;
	_hoops_RPRHC pack;
	int *_hoops_CCRHC, _hoops_CAPHA;
	int _hoops_CARH = 0;
	int _hoops_CIIPP = 0x7fffffff /*_hoops_HGPGA->_hoops_ASHGC->_hoops_GRGHC*/;
	int i, j;
	int _hoops_HCGS;
	bool _hoops_AAPS = false;
	bool _hoops_HAHRC = false;
	_hoops_RSPRC _hoops_PPCP;
	_hoops_SARHC _hoops_APHA = _hoops_GPRHC(ts, nr->_hoops_IHA, _hoops_RRHA);
	HOGLVertexBuffer _hoops_PAIH;
	bool _hoops_AGAHC = true;
	float *data = null;
	_hoops_HRPA const *matrix = null;
	RGB const *_hoops_GPCP = null;
	Bounding _hoops_RPAHC;
	GLenum error;
	OptimizerScratch *scratch = null;
	bool status = true;

	ASSERT (!ts || !BIT (ts->_hoops_SRHA, DL_DO_NOT_RECOMPILE));
	ASSERT (_hoops_APHA == _hoops_PARHC ||
			_hoops_APHA == _hoops_AARHC);

	error = glGetError (); //_hoops_SCAC _hoops_SPHS
	if (!_hoops_CSRGR->_hoops_PISGC)
		_hoops_CSRGR->_hoops_PISGC = POOL_NEW(dc->memory_pool, OptimizerScratch)(dc->memory_pool);
	scratch = _hoops_CSRGR->_hoops_PISGC;

	if (_hoops_RRHA) {
		pair = _hoops_RRHA->_hoops_CRHA->PeekFirst();
		if (!pair)
			return 0;
		ts = (Tristrip *)pair->geo;
		if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_APA], M_DIFFUSE))
			_hoops_GPCP = null;
		else
			_hoops_GPCP = _hoops_CCAI (pair->color, Color_FACE);
		if (pair->_hoops_CPAI) {
			matrix = &pair->_hoops_CPAI->matrix;
			_hoops_HAHRC = BIT (matrix->_hoops_RAGR, _hoops_CASA);
		}
		else {
			matrix = null;
			_hoops_HAHRC = false;
		}
	}

	ZALLOC (_hoops_SAAS, OGL_Vertex_Buffer_Object);

	_hoops_RPAHC = ts->bounding;
	if (!_hoops_SAAS->_hoops_IGPRC)
		_hoops_CSRGR->_hoops_CHPGC(1, &_hoops_SAAS->_hoops_IGPRC);

	// _hoops_RAP _hoops_GH _hoops_SRAHC
	_hoops_PPCP._hoops_AIHC();
	if (ts->_hoops_ICHA || ts->_hoops_PRHH)
		_hoops_PPCP._hoops_CCRS();
	if (ts->_hoops_PCHA || ts->_hoops_PAGI || _hoops_GPCP)
		_hoops_PPCP._hoops_RPHC();
	if (BIT(ts->_hoops_SRHA, _hoops_GGIA)) {
		_hoops_PPCP._hoops_PPIGR(1);
		_hoops_PPCP._hoops_HIHC(0, 2);
		param_width = 2;
		_hoops_SAAS->_hoops_ASARC = _hoops_PPCP._hoops_APIGR();
		ALLOC_ARRAY (_hoops_SAAS->_hoops_RSARC, _hoops_SAAS->_hoops_ASARC + 1, int);	// _hoops_ASH _hoops_AII + _hoops_CGHI _hoops_SHI (_hoops_HIS _hoops_SR _hoops_PAH _hoops_CSGA _hoops_PRGH _hoops_IGAA _hoops_IIGR _hoops_GRR _hoops_HH)
	}
	else if (ts->_hoops_GSSH && ts->_hoops_GSSH->_hoops_CCHA && ts->_hoops_GSSH->_hoops_GSHA > 0) {
		int _hoops_APAHC = 0;
		int _hoops_PPAHC = 0;

		_hoops_RRCC* _hoops_CGGHC = ts->_hoops_GSSH;
		while(_hoops_CGGHC){
			_hoops_PPAHC += _hoops_CGGHC->_hoops_GSHA;
			_hoops_CGGHC = _hoops_CGGHC->next;
		}

		_hoops_CGGHC = ts->_hoops_GSSH;
		param_width = _hoops_CGGHC->_hoops_GSHA;
		
		// _hoops_HGI _hoops_HRGR _hoops_IRS _hoops_IGRH _hoops_IIGR _hoops_IRS _hoops_RSAIP _hoops_IH _hoops_CGPR _hoops_SR _hoops_HS _hoops_RRI _hoops_RHPS _hoops_HSAR _hoops_SR _hoops_ACPA _hoops_PCPA _hoops_IS _hoops_AA _hoops_CCA.
		// _hoops_PS _hoops_IPASR _hoops_CAPR _hoops_IS _hoops_AI _hoops_PHGCA.
		while (_hoops_PPAHC) {
			if (_hoops_APAHC == 0) {
				int _hoops_HPAHC = 2;
				_hoops_HHA const matr = nr->_hoops_IHA->_hoops_CHA;

				if (matr->_hoops_SCA != null) {
					int _hoops_PSR = matr->_hoops_SCA->texture->_hoops_PSR;

					if (_hoops_PSR == HK_PS_U)
						_hoops_HPAHC = 1;
					else if (_hoops_PSR == HK_PS_UVW)
						_hoops_HPAHC = 3;
				}
				else {
					if (_hoops_PPAHC == 1 || _hoops_PPAHC == 3)
						_hoops_HPAHC = _hoops_PPAHC;
				}
				_hoops_PPCP._hoops_HIHC(_hoops_APAHC++, _hoops_HPAHC);
				_hoops_PPAHC -= _hoops_HPAHC;
			}
			else {
				_hoops_PPCP._hoops_HIHC(_hoops_APAHC++, _hoops_AHIA(_hoops_PPAHC, 3));
				_hoops_PPAHC -= _hoops_AHIA(_hoops_PPAHC, 3);
			}

			_hoops_PPCP._hoops_APHC();
			if(_hoops_CGGHC)
				_hoops_CGGHC = _hoops_CGGHC->next;
		}
		_hoops_SAAS->_hoops_ASARC = _hoops_PPCP._hoops_APIGR();
		ALLOC_ARRAY (_hoops_SAAS->_hoops_RSARC, _hoops_SAAS->_hoops_ASARC + 1, int);	// _hoops_ASH _hoops_AII + _hoops_CGHI _hoops_SHI (_hoops_HIS _hoops_SR _hoops_PAH _hoops_CSGA _hoops_PRGH _hoops_IGAA _hoops_IIGR _hoops_GRR _hoops_HH)
	}

	if (_hoops_RRHA) {
		_hoops_RRHA->_hoops_CRHA->ResetCursor();
		_hoops_RRHA->_hoops_AGRI = ts->_hoops_SRHA;
		if (_hoops_APHA != _hoops_PARHC)
			_hoops_RRHA->_hoops_AGRI |= DL_FORCE_SMOOTH_SHADE_MODEL;
	}
	if (_hoops_APHA == _hoops_AARHC) {
		for (;;) {
			bool _hoops_IGAHC = true;
			bool _hoops_CGAHC = false;
			_hoops_CARH += _hoops_RRHRC (ts);
			_hoops_SAAS->count++;
			_hoops_SAAS->point_count += ts->point_count;
			for (i = 0 ; i < ts->_hoops_PHHA ; i++) {
				if (ts->lengths[i] < _hoops_CIIPP) {
					_hoops_HGPRC += 3 * (ts->lengths[i] - 2);
				}
				else {
					_hoops_SAAS->_hoops_HSARC++;
					_hoops_SAAS->_hoops_RGPRC += ts->lengths[i];
					if (_hoops_AGAHC) {
						// _hoops_HIHA _hoops_IH _hoops_RH _hoops_ARHAR _hoops_SCPH _hoops_PSPI
						if (_hoops_HAHRC)
							_hoops_CGAHC = !_hoops_CGAHC;
						if (_hoops_CGAHC) {
							_hoops_SAAS->_hoops_RGPRC++;
							_hoops_CGAHC = false;
						}
						if (!_hoops_IGAHC)
							_hoops_SAAS->_hoops_RGPRC += 2;
						else
							_hoops_IGAHC = false;
						if (ts->lengths[i] & 0x1)
							_hoops_CGAHC = true;
					}
				}
			}
			if (matrix && ts && _hoops_RPAHC)
				_hoops_AAPS = true;

			if (!_hoops_RRHA)
				break;
			_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			if (!pair)
				break;
			ts = (Tristrip const *) pair->geo;
			_hoops_RPAHC = ts->bounding;
			if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_IAA], M_DIFFUSE))
				_hoops_GPCP = null;
			else
				_hoops_GPCP = _hoops_CCAI (pair->color, Color_FACE);
			if (pair->_hoops_CPAI) {
				matrix = &pair->_hoops_CPAI->matrix;
				_hoops_HAHRC = BIT (matrix->_hoops_RAGR, _hoops_CASA);
			}
			else {
				matrix = null;
				_hoops_HAHRC = false;
			}
		}

		_hoops_IPRHC(_hoops_SAAS->point_count, _hoops_SAAS->_hoops_AGPRC);

		if (_hoops_SAAS->_hoops_HSARC)
			ALLOC_ARRAY (_hoops_SAAS->_hoops_PSARC, _hoops_SAAS->_hoops_HSARC, int);
		if (_hoops_SAAS->_hoops_RGPRC)
			vertex_indices_long = scratch->GetVertexIndicesLong (_hoops_SAAS->_hoops_RGPRC*_hoops_SAAS->_hoops_AGPRC); //_hoops_SRSPC (_hoops_IPAHC, _hoops_ARAI->_hoops_CPAHC * _hoops_ARAI->_hoops_SPAHC, _hoops_APPC _hoops_ICHRR);
		if (_hoops_HGPRC)
			_hoops_SIRHC = scratch->GetVertexIndicesShort (_hoops_HGPRC*_hoops_SAAS->_hoops_AGPRC); //_hoops_SRSPC (_hoops_GHAHC, _hoops_RHAHC * _hoops_ARAI->_hoops_SPAHC, _hoops_APPC _hoops_ICHRR);

		ZERO_STRUCT (&pack, _hoops_RPRHC);
		pack._hoops_APRHC = _hoops_SAAS->_hoops_PSARC;
		pack._hoops_PPRHC._hoops_IRA(_hoops_SAAS->_hoops_AGPRC, vertex_indices_long);
		pack._hoops_HPRHC._hoops_IRA(_hoops_SAAS->_hoops_AGPRC, _hoops_SIRHC);
		if (_hoops_RRHA) {
			int _hoops_AHAHC = 0;
			_hoops_IAAHC *r;

			_hoops_CAAHC	_hoops_PHAHC(dc->memory_pool);

			_hoops_HAAHC (null, _hoops_RRHA, _hoops_SAAS, _hoops_AAPS);
#ifdef _hoops_RAAHC
			if (_hoops_SAAS->count > 1)
				_hoops_AAAHC (_hoops_RRHA, _hoops_SAAS);
#endif

			_hoops_RRHA->_hoops_CRHA->ResetCursor();
			_hoops_RGAHC = 0;
			ALLOC_ARRAY (_hoops_SAAS->_hoops_ISARC, _hoops_SAAS->count, int);
			ALLOC_ARRAY (_hoops_SAAS->_hoops_CSARC, _hoops_SAAS->count, int);
			for (i = 0 ; ; i++) {
				pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
				if (!pair)
					break;
				_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
				ts = (Tristrip const *) pair->geo;
				_hoops_RPAHC = ts->bounding;
				if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_IAA], M_DIFFUSE))
					_hoops_GPCP = null;
				else
					_hoops_GPCP = _hoops_CCAI (pair->color, Color_FACE);
				if (pair->_hoops_CPAI) {
					matrix = &pair->_hoops_CPAI->matrix;
					_hoops_HAHRC = BIT (matrix->_hoops_RAGR, _hoops_CASA);
				}
				else {
					matrix = null;
					_hoops_HAHRC = false;
				}

				_hoops_CCRHC = scratch->_hoops_ISRHC(ts->total);
				stuff_tristrip_index_buffers (ts, _hoops_HAHRC, _hoops_RGAHC, _hoops_CIIPP, _hoops_AGAHC, &pack, _hoops_CCRHC, &_hoops_CAPHA, _hoops_CSRGR->_hoops_PISGC);

				_hoops_SAAS->_hoops_ISARC[i] = (pack._hoops_PPRHC._hoops_CCHRR - vertex_indices_long) / pack._hoops_PPRHC._hoops_GSHRR;
				_hoops_SAAS->_hoops_CSARC[i] = (pack._hoops_HPRHC._hoops_CCHRR - _hoops_SIRHC) / pack._hoops_HPRHC._hoops_GSHRR;

				POOL_ZALLOC (r, _hoops_IAAHC, dc->memory_pool);
				if (_hoops_CAPHA > 0) {
					POOL_ZALLOC_ARRAY_CACHED (r->_hoops_CCRHC, _hoops_CAPHA, int, dc->memory_pool);
					_hoops_AIGA (_hoops_CCRHC, _hoops_CAPHA, int, r->_hoops_CCRHC);
					_hoops_AHAHC += _hoops_CAPHA;
				}
				r->length = _hoops_CAPHA;
				_hoops_RGAHC += _hoops_CAPHA;
				_hoops_PHAHC.AddLast (r);
			}

			points = scratch->GetPoints (_hoops_AHAHC); //_hoops_SRSPC (_hoops_RSSA, _hoops_HHAHC, _hoops_RACIR);
			if (_hoops_PPCP._hoops_HHCP())
				normals = scratch->GetNormals (_hoops_AHAHC); //_hoops_SRSPC (_hoops_ASGA, _hoops_HHAHC, _hoops_CASGI);
			if (_hoops_PPCP._hoops_SHCP())
				colors = scratch->GetColors (_hoops_AHAHC); //_hoops_SRSPC (_hoops_PSHA, _hoops_HHAHC, _hoops_HGGPA);
			if (_hoops_PPCP._hoops_APIGR() > 0){
				_hoops_RRCC* _hoops_CGGHC = ts->_hoops_GSSH;
				int _hoops_RHGPC = 0;
				while(_hoops_CGGHC){
					if (!BIT(ts->_hoops_SRHA, _hoops_GGIA))
						param_width = _hoops_CGGHC->_hoops_GSHA;
					params = scratch->GetParameters (_hoops_AHAHC * param_width, _hoops_RHGPC); //_hoops_SRSPC (_hoops_RHPS, _hoops_HHAHC * _hoops_IAGCI, _hoops_IHAHC);
					_hoops_CGGHC = _hoops_CGGHC->next;
					_hoops_RHGPC++;
				}
				params = scratch->_hoops_PSRHC(0);
			}

			_hoops_RRHA->_hoops_CRHA->ResetCursor();
			_hoops_RGAHC = 0;
			for (i = 0 ; ; i++) {
				pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
				if (!pair)
					break;
				_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
				ts = (Tristrip const *) pair->geo;
				r = _hoops_PHAHC.RemoveFirst();
				if (r->length == 0)
					continue;
				_hoops_CCRHC = r->_hoops_CCRHC;
				_hoops_CAPHA = r->length;
				_hoops_RPAHC = ts->bounding;
				if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_IAA], M_DIFFUSE))
					_hoops_GPCP = null;
				else
					_hoops_GPCP = _hoops_CCAI (pair->color, Color_FACE);
				if (pair->_hoops_CPAI) {
					matrix = &pair->_hoops_CPAI->matrix;
					_hoops_HAHRC = BIT (matrix->_hoops_RAGR, _hoops_CASA);
				}
				else {
					matrix = null;
					_hoops_HAHRC = false;
				}

				if (matrix) {
					if (normals && matrix->_hoops_APRA == null)
						HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)matrix);

					if (_hoops_CAPHA) {
						for (j = 0 ; j < _hoops_CAPHA ; j++) {
							_hoops_HCGS = _hoops_CCRHC[j];
							ASSERT (_hoops_HCGS < ts->point_count);
							_hoops_SGCRC (matrix, ts->points[_hoops_HCGS], points[j+_hoops_RGAHC]);
							if (normals)
								_hoops_GRCRC (matrix, ts->_hoops_ICHA[_hoops_HCGS], ts->points[_hoops_HCGS], normals[j+_hoops_RGAHC]);
						}
					}
					else {
						for (j = 0 ; j < ts->point_count ; j++) {
							_hoops_SGCRC (matrix, ts->points[j], points[j+_hoops_RGAHC]);
							if (normals)
								_hoops_GRCRC (matrix, ts->_hoops_ICHA[j], ts->points[j], normals[j+_hoops_RGAHC]);
						}
					}
				}
				else {
					if (_hoops_CAPHA) {
						for (j = 0 ; j < _hoops_CAPHA ; j++) {
							_hoops_HCGS = _hoops_CCRHC[j];
							ASSERT (_hoops_HCGS < ts->point_count);
							points[j+_hoops_RGAHC] = ts->points[_hoops_HCGS];
							if (normals)
								normals[j+_hoops_RGAHC] = ts->_hoops_ICHA[_hoops_HCGS];
						}
					}
					else {
						_hoops_AIGA (ts->points, ts->point_count, Point, points + _hoops_RGAHC);
						if (normals)
							_hoops_AIGA (ts->_hoops_ICHA, ts->point_count, Vector, normals + _hoops_RGAHC);
					}
				}
				if (_hoops_CAPHA) {
					for (j = 0 ; j < _hoops_CAPHA ; j++) {
						_hoops_HCGS = _hoops_CCRHC[j];
						if (params) {
							if (BIT (ts->_hoops_SRHA, _hoops_GGIA)) {
								_hoops_RSSH *_hoops_APHCP = &params[(j + _hoops_RGAHC)* param_width];
								_hoops_APHCP[0] = ts->_hoops_HCHA[_hoops_HCGS]
												* _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate;
								_hoops_APHCP[1] = 0;
							}
							else {
								_hoops_AIGA (&ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS * param_width], 
										param_width, _hoops_RSSH, 
										&params[(j + _hoops_RGAHC)* param_width]);
							}
						}
						if (colors) {
							if (ts->_hoops_PCHA)
								colors[j + _hoops_RGAHC] = ts->_hoops_PCHA[_hoops_HCGS];
							else
								colors[j + _hoops_RGAHC] = *_hoops_GPCP;
						}
					}
				}
				else {
					if (params) {
						if (BIT (ts->_hoops_SRHA, _hoops_GGIA)) {
							int ii;
							for (ii = 0; ii < ts->point_count; ii++) {
								params[ii*2] = ts->_hoops_HCHA[ii]
												* _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate;
								params[ii*2 + 1] = 0;
							}
						}
						else
							_hoops_AIGA (ts->_hoops_GSSH->_hoops_CCHA, ts->point_count*param_width, _hoops_RSSH, params + _hoops_RGAHC*param_width);
					}
					if (colors) {
						if (ts->_hoops_PCHA) {
							_hoops_AIGA (ts->_hoops_PCHA, ts->point_count, RGB, colors + _hoops_RGAHC);
						}
						else {
							RGB *_hoops_PCAP = colors + _hoops_RGAHC;
							int ii;
							for (ii = 0 ; ii < ts->point_count ; ii++) {
								_hoops_RSAI (_hoops_GPCP, RGB, _hoops_PCAP);
								_hoops_PCAP++;
							}
						}
					}
				}
				if (_hoops_CAPHA)
					_hoops_RGAHC += _hoops_CAPHA;
				else
					_hoops_RGAHC += ts->point_count;
				FREE_ARRAY (r->_hoops_CCRHC, r->length, int);
				FREE (r, _hoops_IAAHC);	
			}
		}
		else {
			_hoops_CCRHC = scratch->_hoops_ISRHC (ts->total);
			stuff_tristrip_index_buffers (ts, false, 0, _hoops_CIIPP, _hoops_AGAHC, &pack, _hoops_CCRHC, &_hoops_CAPHA,  scratch);

			if (_hoops_CAPHA > 0) {
				int ii;

				points = scratch->GetPoints (_hoops_CAPHA);
				if (_hoops_PPCP._hoops_HHCP())
					normals = scratch->GetNormals (_hoops_CAPHA);
				if (_hoops_PPCP._hoops_SHCP())
					colors = scratch->GetColors (_hoops_CAPHA);

				if (_hoops_PPCP._hoops_APIGR() > 0){
					_hoops_RRCC* _hoops_CGGHC = ts->_hoops_GSSH;
					int _hoops_RHGPC = 0;
					while(_hoops_CGGHC){
						if (!BIT(ts->_hoops_SRHA, _hoops_GGIA))
							param_width = _hoops_CGGHC->_hoops_GSHA;
						params = scratch->GetParameters (_hoops_CAPHA * param_width, _hoops_RHGPC); //_hoops_SRSPC (_hoops_RHPS, _hoops_HHAHC * _hoops_IAGCI, _hoops_IHAHC);
						_hoops_CGGHC = _hoops_CGGHC->next;
						_hoops_RHGPC++;
					}
					params = scratch->_hoops_PSRHC(0);
				}

				for (ii = 0 ; ii < _hoops_CAPHA ; ii++) {
					_hoops_HCGS = _hoops_CCRHC[ii];
					ASSERT (_hoops_HCGS < ts->point_count);
					points[ii] = ts->points[_hoops_HCGS];
					if (normals)
						normals[ii] = ts->_hoops_ICHA[_hoops_HCGS];
					if (colors)
						colors[ii] = ts->_hoops_PCHA[_hoops_HCGS];
					if (params) {
						if (BIT (ts->_hoops_SRHA, _hoops_GGIA)) {
							params[ii*2] = ts->_hoops_HCHA[_hoops_HCGS]
											* _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate;
							params[ii*2 + 1] = 0;
						}
						else {
							_hoops_RRCC* _hoops_CGGHC = ts->_hoops_GSSH;
							int _hoops_RHGPC = 0;
							
							while(_hoops_CGGHC){
								params = scratch->_hoops_PSRHC(_hoops_RHGPC);
								param_width = _hoops_CGGHC->_hoops_GSHA;
								_hoops_AIGA (&_hoops_CGGHC->_hoops_CCHA[_hoops_HCGS * param_width], 
											param_width, _hoops_RSSH, 
											&params[ii * param_width]);
								_hoops_RHGPC++;
								_hoops_CGGHC = _hoops_CGGHC->next;
							}
						}
					}
				}
				_hoops_RGAHC += _hoops_CAPHA;
			}
			else {
				points = ts->points;
				normals = ts->_hoops_ICHA;
				if (BIT (ts->_hoops_SRHA, _hoops_GGIA)) {
					int ii;
					for (ii = 0 ; ii < ts->point_count ; ii++) {
						params[ii*2] = ts->_hoops_HCHA[ii]
										* _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate;
						params[ii*2 + 1] = 0;
					}
				}
				else
					params = ts->_hoops_GSSH->_hoops_CCHA;
				colors = ts->_hoops_PCHA;
				_hoops_RGAHC += ts->point_count;
			}
		}
		ASSERT (pack._hoops_PPRHC._hoops_CCHRR == vertex_indices_long + _hoops_SAAS->_hoops_RGPRC * pack._hoops_PPRHC._hoops_GSHRR);
		//_hoops_PAH _hoops_SHH _hoops_CRGP _hoops_HSAR _hoops_APSR _hoops_RPP _hoops_SGGC _hoops_SCPH _hoops_HIGR _hoops_GPHR _hoops_PPR _hoops_GSIPA _hoops_HHH _hoops_AIHAR
		ASSERT ((pack._hoops_HPRHC._hoops_CCHRR - _hoops_SIRHC)/ pack._hoops_PPRHC._hoops_GSHRR <= _hoops_HGPRC);
		_hoops_SAAS->_hoops_HGPRC = (pack._hoops_HPRHC._hoops_CCHRR - _hoops_SIRHC) / pack._hoops_PPRHC._hoops_GSHRR;

		/* _hoops_CIPH _hoops_CIHA _hoops_PIH */
		if (!XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_ELEMENT_BUFFER)) {
			if (_hoops_SAAS->_hoops_RGPRC) {
				if (!_hoops_SAAS->_hoops_RRPRC)
					_hoops_CSRGR->_hoops_CHPGC(1, &_hoops_SAAS->_hoops_RRPRC);
				_hoops_CSRGR->_hoops_PSPGI(GL_ELEMENT_BUFFER_ARB, _hoops_SAAS->_hoops_RRPRC );
				_hoops_CSRGR->_hoops_HSPGI(GL_ELEMENT_BUFFER_ARB,
					_hoops_SAAS->_hoops_RGPRC*_hoops_SAAS->_hoops_AGPRC*sizeof(short), vertex_indices_long, GL_STATIC_DRAW_ARB);
			}
			if (_hoops_SAAS->_hoops_HGPRC) {
				if (!_hoops_SAAS->_hoops_ARPRC)
					_hoops_CSRGR->_hoops_CHPGC(1, &_hoops_SAAS->_hoops_ARPRC);
				_hoops_CSRGR->_hoops_PSPGI(GL_ELEMENT_BUFFER_ARB, _hoops_SAAS->_hoops_ARPRC );
				_hoops_CSRGR->_hoops_HSPGI(GL_ELEMENT_BUFFER_ARB,
					_hoops_SAAS->_hoops_HGPRC*_hoops_SAAS->_hoops_AGPRC*sizeof(short), _hoops_SIRHC, GL_STATIC_DRAW_ARB);
			}
			_hoops_CSRGR->_hoops_PSPGI(GL_ELEMENT_BUFFER_ARB, 0);
		}

		_hoops_SAAS->point_count = _hoops_RGAHC;

		/* _hoops_CIPH _hoops_GPHA _hoops_PIH */
		data = scratch->GetData (_hoops_SAAS->point_count*_hoops_PPCP._hoops_HGHS());  //_hoops_SRSPC (_hoops_PIH, _hoops_ARAI->_hoops_RSHS*_hoops_ICRS._hoops_CHAHC(), _hoops_AIIC);
		if (!data) {
			status = false;
			goto _hoops_HPAGR;
		}

		_hoops_CSRGR->_hoops_PSPGI(GL_ARRAY_BUFFER_ARB, _hoops_SAAS->_hoops_IGPRC);
		_hoops_PAIH._hoops_IRA(data, _hoops_PPCP);

		float _hoops_IRIR = nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR;
		for (i = 0; i < _hoops_SAAS->point_count; i++) {
			_hoops_PAIH._hoops_AHCP(points[i].x, points[i].y, points[i].z);
			if (normals)
				_hoops_PAIH._hoops_IHCP(normals[i].x, normals[i].y, normals[i].z);
			if (colors)
				_hoops_PAIH.color(_hoops_RRRHC, colors[i].red, colors[i].green, colors[i].blue, _hoops_IRIR);


			_hoops_RRCC* _hoops_CGGHC = ts->_hoops_GSSH;
			int _hoops_RHGPC = 0;
			int _hoops_AHCGR = 0;
			int _hoops_RSCP = 0;
			
			if( (params = scratch->_hoops_PSRHC(_hoops_RHGPC)) != null && _hoops_SAAS->_hoops_RSARC)
				_hoops_SAAS->_hoops_RSARC[0] = _hoops_PAIH._hoops_APCGR();

			while(_hoops_CGGHC){
				if (BIT(ts->_hoops_SRHA, _hoops_GGIA))
					param_width = 2;
				else	
					param_width = _hoops_CGGHC->_hoops_GSHA;

				params = scratch->_hoops_PSRHC(_hoops_RHGPC);
				if (params && param_width) {
					int _hoops_SHAHC = i*param_width;

					if (param_width >= 1)
						_hoops_PAIH.u(params[_hoops_SHAHC ], _hoops_AHCGR);
					if (param_width >= 2)
						_hoops_PAIH.v(params[_hoops_SHAHC + 1], _hoops_AHCGR);
					if (param_width >= 3)
						_hoops_PAIH.w(params[_hoops_SHAHC + 2], _hoops_AHCGR);

					_hoops_RSCP += _hoops_PPCP._hoops_CPIGR(_hoops_AHCGR);
					_hoops_AHCGR++;
					ASSERT (_hoops_AHCGR <= _hoops_SAAS->_hoops_ASARC);
					_hoops_SAAS->_hoops_RSARC[_hoops_AHCGR] = _hoops_SAAS->_hoops_RSARC[0] + _hoops_RSCP;
				}
				_hoops_CGGHC = _hoops_CGGHC->next;
				_hoops_RHGPC++;
			}
			++_hoops_PAIH;
		}
		_hoops_CSRGR->_hoops_HSPGI (GL_ARRAY_BUFFER_ARB, _hoops_SAAS->point_count*_hoops_PPCP._hoops_HGHS()*sizeof(float), data, GL_STATIC_DRAW_ARB);
		_hoops_CSRGR->_hoops_PSPGI (GL_ARRAY_BUFFER_ARB, 0);
		data = null;
	}
	else if (_hoops_APHA == _hoops_PARHC) {
		int _hoops_ISPAR = 0;

		_hoops_SAAS->_hoops_RGPRC = 0;
		_hoops_SAAS->point_count = 0;
		_hoops_SAAS->count = 1;
		_hoops_SAAS->_hoops_HSARC = 1;

		/* _hoops_PHAA, _hoops_CAHA _hoops_GGSR _hoops_APSR _hoops_PPSR _hoops_PPR _hoops_HSP _hoops_ISIA */
		if (_hoops_RRHA) {
			_hoops_SAAS->count = _hoops_RRHA->_hoops_CRHA->Count();
			_hoops_RRHA->_hoops_CRHA->ResetCursor();
			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			ts = (Tristrip const *) pair->geo;
			if (pair->_hoops_CPAI)
				matrix = &pair->_hoops_CPAI->matrix;
			else
				matrix = null;
			//_hoops_HSPR _hoops_III _hoops_GRGR _hoops_PGGA _hoops_PSHA _hoops_GA'_hoops_RA _hoops_HAHA _hoops_ISIA...
			//_hoops_IHHAR = _hoops_GIAHC (_hoops_PSAI->_hoops_HAIR, _hoops_RIAHC);
		}

		for (;;) {
			_hoops_RPAHC = ts->bounding;
			_hoops_SAAS->point_count += ts->total;
			_hoops_CARH += _hoops_RRHRC (ts);
			if (matrix && BIT(matrix->_hoops_RAGR, _hoops_CASA))
				_hoops_ISPAR = 0x1;
			else
				_hoops_ISPAR = 0;
			for (i = 0; i < ts->_hoops_PHHA ; i++) {
				if (_hoops_SAAS->_hoops_RGPRC != 0) {
					_hoops_SAAS->_hoops_RGPRC++;
					if ((_hoops_SAAS->_hoops_RGPRC & 0x1) != _hoops_ISPAR)
						_hoops_SAAS->_hoops_RGPRC++;
				}
				_hoops_SAAS->_hoops_RGPRC += ts->lengths[i] + 1;
			}
			if ((_hoops_SAAS->_hoops_RGPRC & 0x1) != 0)
				_hoops_SAAS->_hoops_RGPRC++;
			if (matrix && ts && _hoops_RPAHC)
				_hoops_AAPS = true;

			if (_hoops_RRHA) {
				_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
				pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
				if (!pair)
					break;
				ts = (Tristrip const *) pair->geo;
				if (pair->_hoops_CPAI)
					matrix = &pair->_hoops_CPAI->matrix;
				else
					matrix = null;
				//_hoops_IHHAR = _hoops_GIAHC (_hoops_PSAI->_hoops_HAIR, _hoops_RIAHC);
			}
			else
				break;
		}


		if (_hoops_RRHA) {
			//_hoops_AIAHC _hoops_SSCP _hoops_IS _hoops_SHH _hoops_PISI _hoops_CCGR _hoops_RAS _hoops_RH _hoops_SRS
			//_hoops_IHIR _hoops_ARAS _hoops_RHIR _hoops_RH _hoops_HIGR _hoops_HIS _hoops_SGS _hoops_RH _hoops_HSAGA _hoops_IIGR _hoops_PIAHC
			//_hoops_HRGR _hoops_GGSP
			_hoops_HAAHC (null, _hoops_RRHA, _hoops_SAAS, _hoops_AAPS);
#ifdef _hoops_RAAHC
			if (_hoops_SAAS->count > 1)
				_hoops_AAAHC (_hoops_RRHA, _hoops_SAAS);
#endif
			_hoops_RRHA->_hoops_CRHA->ResetCursor();
			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			ts = (Tristrip const *) pair->geo;
			if (pair->_hoops_CPAI)
				matrix = &pair->_hoops_CPAI->matrix;
			else
				matrix = null;
			if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_IAA], M_DIFFUSE))
				_hoops_GPCP = null;
			else
				_hoops_GPCP = _hoops_CCAI (pair->color, Color_FACE);
		}
		else {
			ASSERT (_hoops_SAAS->count == 1);
			_hoops_HAAHC (ts, null, _hoops_SAAS, _hoops_AAPS);
		}

		_hoops_IPRHC (_hoops_SAAS->_hoops_RGPRC, _hoops_SAAS->_hoops_AGPRC);
		ASSERT (_hoops_SAAS->_hoops_HSARC != 0);
		ALLOC_ARRAY (_hoops_SAAS->_hoops_PSARC, _hoops_SAAS->_hoops_HSARC, int);
		vertex_indices_long = scratch->GetVertexIndicesLong (_hoops_SAAS->_hoops_RGPRC*_hoops_SAAS->_hoops_AGPRC); //_hoops_SRSPC (_hoops_IPAHC, _hoops_ARAI->_hoops_CPAHC*_hoops_ARAI->_hoops_SPAHC, _hoops_APPC _hoops_ICHRR);
		_hoops_SAAS->_hoops_PSARC[0] = _hoops_SAAS->_hoops_RGPRC;
		data = scratch->GetData (_hoops_SAAS->point_count * _hoops_PPCP._hoops_HGHS());
		ALLOC_ARRAY (_hoops_SAAS->_hoops_ISARC, _hoops_SAAS->count, int);

		_hoops_PAIH._hoops_IRA(data, _hoops_PPCP);
		_hoops_GARHC _hoops_SGIRR(_hoops_SAAS->_hoops_AGPRC, vertex_indices_long);
		_hoops_GARHC _hoops_IHPAR;
		{
			int _hoops_HIAHC = 0;
			int _hoops_ICIAR = 0;
			_hoops_IHPAR = _hoops_SGIRR;

			for (;;) {
				int j;
				int _hoops_CACP;
				int _hoops_CRPAR = 0;
				int len = 0;
				int _hoops_SCHC = 0;
				int _hoops_CCIAR = 0;
				int *_hoops_SGHAR = ts->face_indices;

				if (matrix && BIT(matrix->_hoops_RAGR, _hoops_CASA))
					_hoops_ISPAR = 0x1;
				else
					_hoops_ISPAR = 0;

				for (i = 0; i < ts->_hoops_PHHA; i++) {
					len = ts->lengths[i];

					// _hoops_GIHAR _hoops_HIPH
					if (_hoops_IHPAR != _hoops_SGIRR) {
						_hoops_IHPAR = _hoops_ICIAR;
						++_hoops_IHPAR;
						_hoops_CCIAR = (_hoops_IHPAR._hoops_CCHRR - vertex_indices_long) / _hoops_SAAS->_hoops_AGPRC;
						if ((_hoops_CCIAR & 0x1) != _hoops_ISPAR) {
							_hoops_IHPAR = _hoops_ICIAR;
							++_hoops_IHPAR;
						}
					}

					if (i == 0) {
						_hoops_CCIAR = (_hoops_IHPAR._hoops_CCHRR - vertex_indices_long) / _hoops_SAAS->_hoops_AGPRC;
						_hoops_SAAS->_hoops_ISARC[_hoops_HIAHC++] = _hoops_CCIAR;
					}

					// _hoops_SCIAR _hoops_IRS _hoops_CGGR, _hoops_IPS _hoops_GRR _hoops_GPHA _hoops_PPR _hoops_CIHA _hoops_IAPR
					for (j = 0 ; j < len ; j++) {
						if (_hoops_SGHAR)
							_hoops_CRPAR = *_hoops_SGHAR++;
						else if (j > 2)
							_hoops_CRPAR++;

						_hoops_CACP = ts->_hoops_AIHA[j + _hoops_SCHC];
						_hoops_PRAHC(nr, ts, &_hoops_PAIH, _hoops_CACP, matrix, _hoops_GPCP, _hoops_CRPAR);
						++_hoops_PAIH;

						_hoops_IHPAR = j + _hoops_ICIAR;
						++_hoops_IHPAR;
					}
					_hoops_CRPAR++;

					// _hoops_GIHAR _hoops_HIPH _hoops_GGR _hoops_ISSC
					_hoops_IHPAR = j+_hoops_ICIAR-1;
					++_hoops_IHPAR;
					_hoops_ICIAR += len;
					_hoops_SCHC += len;
				}
				_hoops_CCIAR = (_hoops_IHPAR._hoops_CCHRR - vertex_indices_long) / _hoops_SAAS->_hoops_AGPRC;
				if ((_hoops_CCIAR & 0x1) != 0) {
					_hoops_IHPAR = *(_hoops_IHPAR-1);
					++_hoops_IHPAR;
					_hoops_CCIAR++;
				}

				if (_hoops_RRHA) {
					_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
					pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
					if (!pair)
						break;
					ts = (Tristrip const *) pair->geo;
					if (pair->_hoops_CPAI)
						matrix = &pair->_hoops_CPAI->matrix;
					else
						matrix = null;
					if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_IAA], M_DIFFUSE))
						_hoops_GPCP = null;
					else
						_hoops_GPCP = _hoops_CCAI (pair->color, Color_FACE);

					// _hoops_IGHS _hoops_CAGH _hoops_PAPA _hoops_CGHS, _hoops_HIS _hoops_HRCI _hoops_GII _hoops_CPAP _hoops_CGHS
					if (ts->_hoops_GAHA && ts->_hoops_GAHA->list)
						HD_Queue_Destroy_List (ts->_hoops_GAHA->list, true);

				}
				else
					break;
			}
		}
		ASSERT (_hoops_IHPAR._hoops_CCHRR - vertex_indices_long == _hoops_SAAS->_hoops_RGPRC * _hoops_SAAS->_hoops_AGPRC);
		ASSERT (_hoops_SAAS->point_count == _hoops_PAIH._hoops_IRRHC());

		/* _hoops_RIH _hoops_RH _hoops_GPHA _hoops_PIH */
		_hoops_CSRGR->_hoops_PSPGI(GL_ARRAY_BUFFER_ARB, _hoops_SAAS->_hoops_IGPRC);
		_hoops_CSRGR->_hoops_HSPGI(GL_ARRAY_BUFFER_ARB,
			_hoops_SAAS->point_count * _hoops_PPCP._hoops_HGHS() * sizeof(float), data, GL_STATIC_DRAW_ARB);
		_hoops_CSRGR->_hoops_PSPGI(GL_ARRAY_BUFFER_ARB, 0);

		/* _hoops_RIH _hoops_RH _hoops_PSPI */
		if (!XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_ELEMENT_BUFFER)) {
			if (!_hoops_SAAS->_hoops_RRPRC)
				_hoops_CSRGR->_hoops_CHPGC(1, &_hoops_SAAS->_hoops_RRPRC);
			_hoops_CSRGR->_hoops_PSPGI(GL_ELEMENT_BUFFER_ARB, _hoops_SAAS->_hoops_RRPRC );
			_hoops_CSRGR->_hoops_HSPGI(GL_ELEMENT_BUFFER_ARB,
				_hoops_SAAS->_hoops_RGPRC * _hoops_SAAS->_hoops_AGPRC * sizeof(short), vertex_indices_long, GL_STATIC_DRAW_ARB);
			_hoops_CSRGR->_hoops_PSPGI(GL_ELEMENT_BUFFER_ARB, 0);
		}
		data = null;
	}
	else {
		ASSERT (0);
	}

	_hoops_SAAS->_hoops_CPPSP = _hoops_PAIH._hoops_SACGR() * sizeof(float);
	_hoops_SAAS->_hoops_HPRAC = _hoops_PAIH._hoops_GPCGR() * sizeof(float);
	_hoops_SAAS->colors_offset = _hoops_PAIH._hoops_RPCGR() * sizeof(float);
	if (BIT(ts->_hoops_SRHA, _hoops_GGIA))
		_hoops_SAAS->param_width = 2;
	else
		_hoops_SAAS->param_width = ts->_hoops_GSSH ? ts->_hoops_GSSH->_hoops_GSHA : 0;
	_hoops_SAAS->stride = _hoops_PAIH._hoops_CACGR() * sizeof(float);

	error = glGetError ();
	if (error) {
		ASSERT (error == GL_OUT_OF_MEMORY);
	}
  _hoops_HPAGR:

	if (error || !status) {
		_hoops_GSARC (_hoops_SAAS);
		*_hoops_GPAHC = null;
		_hoops_CARH = 0;
	}
	else
		*_hoops_GPAHC = _hoops_SAAS;
	return _hoops_CARH;
}


#define _hoops_RRIRR(_hoops_ARIRR) (!BIT(_hoops_ARIRR,Test_EXTENT) && (_hoops_ARIRR != Test_DISJOINT))
#ifdef glDrawRangeElements
#undef glDrawRangeElements
#endif

#if 0
#define glDrawRangeElements(_hoops_IIAHC,_hoops_CIAHC,_hoops_SIAHC,_hoops_GCAHC,_type,_hoops_RCAHC) _hoops_GHIA (\
	if (_hoops_CSRGR->glDrawRangeElementsEXT) \
		_hoops_CSRGR->glDrawRangeElementsEXT (_hoops_IIAHC, _hoops_CIAHC, _hoops_SIAHC, _hoops_GCAHC, _type, _hoops_RCAHC); \
	else \
		glDrawElements (_hoops_IIAHC, _hoops_GCAHC, _type, _hoops_RCAHC); \
)
#else
#define glDrawRangeElements(_hoops_IIAHC,_hoops_CIAHC,_hoops_SIAHC,_hoops_GCAHC,_type,_hoops_RCAHC) _hoops_GHIA (\
	glDrawElements (_hoops_IIAHC, _hoops_GCAHC, _type, _hoops_RCAHC); \
)
#endif


//_hoops_PIHA _hoops_SHH _hoops_GPGR _hoops_IIGR 3
#define _hoops_ACAHC 4095


/*
 * _hoops_PGAA
 */
local void _hoops_PCAHC (
		OGL_Vertex_Buffer_Object alter *_hoops_SAAS,
		Net_Rendition const & nr,
		OGL_Render_Control *rc)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	Test *cull_results = null;
	int _hoops_PIHS = 0;
	int start, end, _hoops_IGIC;
	int i, j, k, prev, len;
	GLenum _hoops_HCAHC;
	int _hoops_AHCGR = 0;

	bool _hoops_IHHS =
		!BIT (nr->transform_rendition->flags, _hoops_CHHS) &&
			BIT (nr->_hoops_IRR->_hoops_SHHS, _hoops_GIHS) &&
			(ANYBIT (nr->transform_rendition->_hoops_APH, Heur_Culling_EXTENT|_hoops_RIHS) ||
				(BIT (nr->transform_rendition->_hoops_APH, Heur_Culling_VIEW_FRUSTUM) &&
					!BIT (nr->transform_rendition->flags, _hoops_AIHS)));

	if (_hoops_SAAS->_hoops_SSARC && _hoops_IHHS) {

		if (_hoops_SAAS->count > _hoops_CSRGR->_hoops_HIHS) {
			if (_hoops_CSRGR->_hoops_IIHS)
				FREE_ARRAY (_hoops_CSRGR->_hoops_IIHS, _hoops_CSRGR->_hoops_HIHS, Test);
			ALLOC_ARRAY (_hoops_CSRGR->_hoops_IIHS, _hoops_SAAS->count, Test);
			_hoops_CSRGR->_hoops_HIHS = _hoops_SAAS->count;
		}

		cull_results = _hoops_CSRGR->_hoops_IIHS;

		float _hoops_CIHS;
		
		int	_hoops_SIHS = 0;

		if (BIT (nr->transform_rendition->_hoops_APH, _hoops_RIHS))
			_hoops_SIHS = nr->_hoops_IRR->_hoops_GCHS;
		if (BIT (nr->transform_rendition->_hoops_APH, Heur_Culling_EXTENT))
			_hoops_SIHS = _hoops_IAAA(nr->_hoops_IRR->_hoops_GRGC, _hoops_SIHS);

		_hoops_PIHS = HD_Transform_And_Test_Simple_Sphere (nr, 
						_hoops_SAAS->count, _hoops_SAAS->_hoops_SSARC, null, 
						0, _hoops_SIHS, cull_results, null, &_hoops_CIHS);

		if (_hoops_CIHS > 0.0f &&
			nr->_hoops_IRR->_hoops_PCHS == Heur_MAX_EXTENT_MODE_DEFER) { 

			int _hoops_HCHS = (int) (_hoops_CIHS * (float)_hoops_ICHS / (float)_hoops_SIHS);

			if (_hoops_HCHS > dc->_hoops_SSGC)
				dc->_hoops_SSGC = _hoops_HCHS;
		}

		if (_hoops_PIHS == 0) {
			if (cull_results && BIT(cull_results[0],Test_EXTENT))
				_hoops_GPRH (_hoops_CSIAR) += _hoops_SAAS->count;
			else
				_hoops_GPRH (_hoops_SSIAR) += _hoops_SAAS->count;
			goto _hoops_HPAGR;
		}
		else if (_hoops_PIHS < _hoops_SAAS->count && cull_results) {
			for (i = 0 ; i < _hoops_SAAS->count ; i++) {
				if (BIT (cull_results[i],Test_EXTENT))
					_hoops_GPRH (_hoops_CSIAR)++;
				else if (cull_results[i] == Test_DISJOINT)
					_hoops_GPRH (_hoops_SSIAR)++;
			}
		}
	}
	else
		_hoops_PIHS = _hoops_SAAS->count;

	if (_hoops_SAAS->_hoops_AGPRC == 1)
		_hoops_HCAHC = GL_UNSIGNED_SHORT;
	else
		_hoops_HCAHC = GL_UNSIGNED_INT;

	_hoops_CSRGR->_hoops_PSPGI (GL_ARRAY_BUFFER_ARB, _hoops_SAAS->_hoops_IGPRC);
	if (_hoops_SAAS->_hoops_HPRAC > 0) {
		_hoops_HGCRC(_hoops_CSRGR);
		glNormalPointer (GL_FLOAT, _hoops_SAAS->stride, (char *) 0 + _hoops_SAAS->_hoops_HPRAC);
	}



		for (_hoops_AHCGR = 0; _hoops_AHCGR < OGL_MAX_TEXTURE_UNITS ; _hoops_AHCGR++) {
			ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,_hoops_AHCGR,false);
		}
		ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,0,true);
		if (BIT(rc->_hoops_GCI[rc->pass], _hoops_RIGRC))
			glTexCoordPointer (2, GL_FLOAT, _hoops_SAAS->stride, (char *) 0 + (_hoops_SAAS->_hoops_RSARC[rc->pass] * sizeof(float))  );
		else
			glTexCoordPointer (2, GL_FLOAT, _hoops_SAAS->stride, (char *) 0 + ( (_hoops_SAAS->_hoops_RSARC) ? (_hoops_SAAS->_hoops_RSARC[rc->pass- (rc->pass ? 1 : 0) ] * sizeof(float)) : 0 )  );


	_hoops_IHRRC(_hoops_CSRGR,0);

	if (_hoops_SAAS->colors_offset > 0) {
		ENSURE_COLOR_ARRAY_ON(_hoops_CSRGR);
		glColorPointer (4, GL_UNSIGNED_BYTE, _hoops_SAAS->stride, (char *) 0 + _hoops_SAAS->colors_offset);
	}

	_hoops_CPPRC (_hoops_CSRGR);
	glVertexPointer (3, GL_FLOAT, _hoops_SAAS->stride, (char *) 0);

	i = j = k = 0;
	start = len = prev = 0;

	if (_hoops_SAAS->_hoops_RRPRC) {
		if (!XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_ELEMENT_BUFFER))
			_hoops_CSRGR->_hoops_PSPGI (GL_ELEMENT_BUFFER_ARB, _hoops_SAAS->_hoops_RRPRC);
		ASSERT (_hoops_SAAS->_hoops_HSARC == 1);  //_hoops_HSPR _hoops_HAPR _hoops_IGIPR _hoops_CPS _hoops_RIHA _hoops_CCA _hoops_AIHAR
		while (k < _hoops_SAAS->count) {
			if (cull_results &&
				_hoops_SAAS->_hoops_ISARC) {
				start = end = prev;
				while (k < _hoops_SAAS->count &&
					!_hoops_RRIRR (cull_results[k])) {
					start = _hoops_SAAS->_hoops_ISARC[k];
					k++;
				}
				while (k < _hoops_SAAS->count &&
					_hoops_RRIRR (cull_results[k])) {
					if (k < _hoops_SAAS->count - 1)
						end = _hoops_SAAS->_hoops_ISARC[k+1];
					else
						end = _hoops_SAAS->_hoops_RGPRC;
					k++;
				}
				prev = end;
			}
			else {
				start = 0;
				end = _hoops_SAAS->_hoops_RGPRC;
				k = _hoops_SAAS->count;
			}
			if (end > start) {
				if (!XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_ELEMENT_BUFFER))
					glDrawRangeElements (
						GL_TRIANGLE_STRIP, 0, _hoops_SAAS->point_count, end - start,
						_hoops_HCAHC, I2V(start*_hoops_SAAS->_hoops_AGPRC*sizeof(short)));
				else
					glDrawRangeElements (
						GL_TRIANGLE_STRIP, 0, _hoops_SAAS->point_count, end - start,
						_hoops_HCAHC, _hoops_SAAS->_hoops_GGPRC + (start*_hoops_SAAS->_hoops_AGPRC));
				_hoops_GPRH(_hoops_AGCAR) += end - start - 2;

				if (dc->_hoops_PGCAR > 0 &&
					_hoops_GPRH(_hoops_AGCAR) > _hoops_GPRH(_hoops_HGCAR)+dc->_hoops_PGCAR) {
					_hoops_GPRH(_hoops_HGCAR) = _hoops_GPRH(_hoops_AGCAR);
					_hoops_GPRH(_hoops_IGCAR)++;
					//_hoops_IAGHC();
					glFinish();
				}
			}
		}
	}

	if (!XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_ELEMENT_BUFFER))
		_hoops_CSRGR->_hoops_PSPGI (GL_ELEMENT_BUFFER_ARB, _hoops_SAAS->_hoops_ARPRC);
	prev = 0;
	len = 0;
	k = 0;
	for (;;) {
		if (cull_results && _hoops_SAAS->_hoops_CSARC) {
			while (k < _hoops_SAAS->count &&
				_hoops_RRIRR (cull_results[k])) {
				len = _hoops_SAAS->_hoops_CSARC[k] - prev;
				k++;
			}
		}
		else {
			len = _hoops_SAAS->_hoops_HGPRC;
			k = _hoops_SAAS->count;
		}
		if (len > 0) {
			start = prev;
			end = prev + len;

			while (start < end) {
				if (end - start > _hoops_ACAHC)
					_hoops_IGIC = _hoops_ACAHC;
				else
					_hoops_IGIC = end - start;

				if (!XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_ELEMENT_BUFFER))
					glDrawRangeElements (
						GL_TRIANGLES, 0, _hoops_SAAS->point_count, _hoops_IGIC,
						_hoops_HCAHC, I2V(start*_hoops_SAAS->_hoops_AGPRC*sizeof(short)));
				else
					glDrawRangeElements (
						GL_TRIANGLES, 0, _hoops_SAAS->point_count, _hoops_IGIC,
						_hoops_HCAHC, _hoops_SAAS->_hoops_PGPRC + start*_hoops_SAAS->_hoops_AGPRC);
				start += _hoops_IGIC;
			}

			_hoops_GPRH(_hoops_AGCAR) += len/3;
			if (dc->_hoops_PGCAR > 0 &&
				_hoops_GPRH(_hoops_AGCAR) > _hoops_GPRH(_hoops_HGCAR)+dc->_hoops_PGCAR) {
				_hoops_GPRH(_hoops_HGCAR) = _hoops_GPRH(_hoops_AGCAR);
				_hoops_GPRH(_hoops_IGCAR)++;
				//_hoops_IAGHC();
				glFinish();
			}
		}
		while (k < _hoops_SAAS->count &&
			!_hoops_RRIRR (cull_results[k])) {
			prev = _hoops_SAAS->_hoops_CSARC[k];
			k++;
		}
		if (k == _hoops_SAAS->count)
			break;
	}
	_hoops_GPRH(_hoops_GGCAR)++;

_hoops_HPAGR:
	_hoops_AHPRC(_hoops_CSRGR);
	_hoops_IGCRC(_hoops_CSRGR);
	_hoops_RHPRC(_hoops_CSRGR);
	for (i = 0 ; i < OGL_MAX_TEXTURE_UNITS ; i++) {
		ENSURE_TEXTURE_COORD_ARRAY (_hoops_CSRGR, i, false);
	}
	_hoops_IHRRC (_hoops_CSRGR, 0);
	_hoops_CSRGR->_hoops_PSPGI (GL_ARRAY_BUFFER_ARB, 0);
	if (!XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_ELEMENT_BUFFER))
		_hoops_CSRGR->_hoops_PSPGI (GL_ELEMENT_BUFFER_ARB, 0);
}


/*
 * _hoops_PGAA
 */
local void _hoops_ICAHC (
		Net_Rendition const & nr,
		OGL_Render_Control const *rc,
		Tristrip const *ts)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	int i, j;
	int _hoops_AHCGR = 0;
	float *_hoops_CCAHC = null;

	if (ts->_hoops_ICHA) {
		_hoops_HGCRC(_hoops_CSRGR);
		glNormalPointer (GL_FLOAT, 0, ts->_hoops_ICHA);
	}
	else
		_hoops_IGCRC(_hoops_CSRGR);

	if (rc->params[rc->pass]) {
		_hoops_HHA const matr = nr->_hoops_IHA->_hoops_CHA;
		int _hoops_PPAHC = rc->param_width[rc->pass];
		int _hoops_GPSAC = 0;		// _hoops_RH _hoops_SHI _hoops_IIGR _hoops_GRR _hoops_GSHRH _hoops_RHPC
		int _hoops_SCAHC = 0;		// _hoops_RH _hoops_SHI _hoops_RGIRR _hoops_GGR _hoops_RH _hoops_HH _hoops_IPPHR
		_hoops_HIR *_hoops_GRIA = matr->_hoops_SCA;

		while (_hoops_PPAHC) {
			int _hoops_HPAHC = 3;
			if (_hoops_CSRGR->_hoops_SPGRC && (_hoops_PPAHC > 3))
				_hoops_HPAHC = 2;
			int width;

			if (_hoops_GRIA) {
				int _hoops_PSR = _hoops_GRIA->texture->_hoops_PSR;
				_hoops_SCAHC = _hoops_GRIA->texture->_hoops_RSCP;
				if (_hoops_PSR == HK_PS_U)
					_hoops_HPAHC = 1;
				else if (_hoops_PSR == HK_PS_UVW ||
					_hoops_GRIA->texture->_hoops_ICR[2] > 1)
					_hoops_HPAHC = 3;
				else
					_hoops_HPAHC = 2;

				_hoops_GRIA = _hoops_GRIA->next;
			}

			width = _hoops_AHIA (_hoops_HPAHC, _hoops_PPAHC);
			ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,_hoops_AHCGR,true);
			glTexCoordPointer (width, GL_FLOAT, rc->param_width[rc->pass]*sizeof(float), rc->params[rc->pass] + _hoops_GPSAC + _hoops_SCAHC);

			_hoops_PPAHC -= width;
			_hoops_GPSAC += width;
			_hoops_AHCGR++;
		}
	}
	else if (rc->_hoops_GCI[rc->pass] == _hoops_RIGRC){
		ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,_hoops_AHCGR,true);
		if (nr->_hoops_ARA->_hoops_CICP.scale != 1.0f || nr->_hoops_ARA->_hoops_CICP.scale != 0.0f) {
			ALLOC_ARRAY_CACHED (_hoops_CCAHC, ts->point_count, float);
			if (ts->point_count < ts->total && ts->point_count > 0) {
				for (i = 0 ; i < ts->point_count ; i++)
					_hoops_CCAHC[i] = ts->_hoops_HCHA[i]  * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate;
			}
			else {
				for (i = 0 ; i < ts->total ; i++) {
					int vi = ts->_hoops_AIHA[i];
					_hoops_CCAHC[vi] = ts->_hoops_HCHA[vi]  * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate;
				}
			}
			glTexCoordPointer (1, GL_FLOAT, sizeof(float), _hoops_CCAHC);
		}
		else 
			glTexCoordPointer (1, GL_FLOAT, sizeof(float), ts->_hoops_HCHA);
		_hoops_AHCGR++;
	}

	// _hoops_PIHA _hoops_HHSP _hoops_GIGGR _hoops_CRPR _hoops_IH _hoops_RII _hoops_PSPA, _hoops_IAII _hoops_SRCIA _hoops_GRS _hoops_HPPR _hoops_IS _hoops_IRIGR _hoops_SCH _hoops_PPR _hoops_GHCA _hoops_SCCHH
	while (_hoops_AHCGR < OGL_MAX_TEXTURE_UNITS) {
		ENSURE_TEXTURE_COORD_ARRAY (_hoops_CSRGR, _hoops_AHCGR, false);
		_hoops_AHCGR++;
	}
	_hoops_IHRRC(_hoops_CSRGR,0);

	if (ts->_hoops_PCHA) {
		ENSURE_COLOR_ARRAY_ON(_hoops_CSRGR);
		glColorPointer (3, GL_FLOAT, 0, ts->_hoops_PCHA);
	}
	else
		_hoops_RHPRC(_hoops_CSRGR);

	_hoops_CPPRC(_hoops_CSRGR);
	glVertexPointer (3, GL_FLOAT, 0, ts->points);

	j = 0;
	for (i = 0 ; i < ts->_hoops_PHHA ; i++) {
		glDrawRangeElements (
				GL_TRIANGLE_STRIP, 0, ts->point_count, ts->lengths[i],
				GL_UNSIGNED_INT, &ts->_hoops_AIHA[j]);
		j += ts->lengths[i];
	}
	_hoops_AHPRC(_hoops_CSRGR);
	_hoops_IGCRC(_hoops_CSRGR);
	for (i = 0 ; i < OGL_MAX_TEXTURE_UNITS; i++) {
		ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,i,false);
	}
	_hoops_IHRRC(_hoops_CSRGR,0);
	_hoops_RHPRC(_hoops_CSRGR);
	if (_hoops_CCAHC)
		FREE_ARRAY (_hoops_CCAHC, ts->point_count, float);

} /* _hoops_RSGR _hoops_API '_hoops_CRHH _hoops_CRPR _hoops_PGSA' */


local void _hoops_CSPAR (
		Tristrip const *ts,
		int _hoops_SSPAR,
		int start,
		int end,
		int alter *_hoops_GGHAR,
		int alter *_hoops_RGHAR,
		int *_hoops_AGHAR)
{
	int _hoops_PGHAR, j, k;
	int _hoops_HGHAR;
	int const *face_indices = ts->face_indices;

	ASSERT (_hoops_AGHAR);

	_hoops_PGHAR = j = start;
	j += 2;
	_hoops_HGHAR = _hoops_SSPAR + (end - j - 1);

	if (face_indices)
		while (j<end && !_hoops_AGHAR[face_indices[j]])
			j++;
	else {
		while (j<end && !_hoops_AGHAR[_hoops_SSPAR]) {
			j++;
			_hoops_SSPAR++;
		}
	}
	if (j < end) {
		/* _hoops_AHIC _hoops_HGPP _hoops_SGS _hoops_SR _hoops_IGHAR _hoops_RH _hoops_APRAR _hoops_SCGR _hoops_SCPH _hoops_PPR _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_PCCP _hoops_PRGI _hoops_PHI _hoops_IIGR _hoops_HIPH */
		if ((j-_hoops_PGHAR) & 0x1) {
			_hoops_SSPAR--;
			j -= 3;
		}
		else
			j -= 2;
		if (face_indices) {
			while (!_hoops_AGHAR[face_indices[end-1]])
				end--;
		}
		else {
			k = 0;
			while (!_hoops_AGHAR[_hoops_HGHAR-k])
				k++;
			end -= k;
		}
	}
	*_hoops_GGHAR = j;
	*_hoops_RGHAR = end;
}


local void _hoops_GSAHC (
		Net_Rendition const & nr,
		OGL_Render_Control const *rc,
		Tristrip const *ts)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	int i, j, k, fi, _hoops_SAHAR, _hoops_RPHAR, _hoops_GPHAR;
	int _hoops_PGCRC;
	int _hoops_HCGS, _hoops_SSPAR;
	int _hoops_RRIRC = 0;
	int _hoops_CIIPP = _hoops_CSRGR->_hoops_PRARR->_hoops_CIIPP;
	bool _hoops_PRHA;
	bool _hoops_CRSPH;
	float _hoops_IRIR = nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR;

	_hoops_CRSPH = BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI);

	_hoops_PRHA =
		(rc->txr[rc->pass] ||
		 rc->param_width[rc->pass] ||
		 ts->_hoops_PCHA ||
		 ts->_hoops_ICHA ||
		 BIT (ts->_hoops_SRHA, DL_FORCE_SMOOTH_SHADE_MODEL));

	if (!ANYBIT (nr->transform_rendition->heuristics, _hoops_RSA)) {
		_hoops_RRIRC = _hoops_PRIRC;
		_hoops_HRIRC(_hoops_CSRGR, nr);
	}
	else if (BIT(rc->flags[rc->pass], _hoops_RGCGC)) {
		OGL_SET_HANDEDNESS (_hoops_CSRGR, nr->transform_rendition, rc->flags[rc->pass]);
		if (BIT(rc->flags[rc->pass],_hoops_AGCGC))
			_hoops_RRIRC = _hoops_IIHAC;
	}

	if (_hoops_PRHA && (ts->_hoops_PRHH || ts->_hoops_PAGI)) {
		_hoops_CIIPP = 0x7fffffff;
		_hoops_PGCRC = ts->total;
	}
	else {
		j = 0;
		_hoops_SSPAR = 0;
		_hoops_PGCRC = 0;

		for (i = 0; i < ts->_hoops_PHHA; i++) {
			if (!ts->lengths) {
				_hoops_PGCRC++;
				j += 3;
			}
			else if (ts->lengths[i] < _hoops_CIIPP) {
				_hoops_PGCRC += ts->lengths[i] - 2;
				j += ts->lengths[i];
			}
			else {
				_hoops_SAHAR = j + ts->lengths[i];
				_hoops_GPHAR = j;
				if (dc->_hoops_CGHAR)
					_hoops_CSPAR (ts, _hoops_SSPAR, j, _hoops_SAHAR, &j, &_hoops_RPHAR,dc->_hoops_CGHAR);
				else
					_hoops_RPHAR = _hoops_SAHAR;

				k = j - _hoops_GPHAR - 2;
				if (_hoops_RPHAR > j) {
					glBegin (GL_TRIANGLE_STRIP);
					while (j<_hoops_RPHAR) {
						_hoops_HCGS = ts->_hoops_AIHA[j];
						if (_hoops_CSRGR->_hoops_SPGRC) {
							(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*ts->_hoops_GSSH->_hoops_GSHA]);
							(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*ts->_hoops_GSSH->_hoops_GSHA+2]);
						}
						else if (rc->params[rc->pass]) {
							if (rc->param_width[rc->pass] == 2)
								glTexCoord2fv (&(rc->params[rc->pass])[_hoops_HCGS*rc->param_width[rc->pass] ]);
							else
								glTexCoord3fv (&(rc->params[rc->pass])[_hoops_HCGS*rc->param_width[rc->pass] ]);
						}
						else if (rc->_hoops_GCI[rc->pass] == _hoops_RIGRC) {
							glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
						}
						else if (ts->_hoops_PCHA)
							FORCE_COLOR_4F (ts->_hoops_PCHA[_hoops_HCGS].red,
                                            ts->_hoops_PCHA[_hoops_HCGS].green,
                                            ts->_hoops_PCHA[_hoops_HCGS].blue,
                                            _hoops_IRIR,
                                            _hoops_CRSPH);
						if (ts->_hoops_ICHA)
							_hoops_RRCRC (_hoops_RRIRC, ts->_hoops_ICHA[_hoops_HCGS], ts->points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
						if ((j - _hoops_GPHAR) >= 2) {
							if (ts->face_indices) {
								fi = ts->face_indices[j];
							}
							else {
								fi = _hoops_SSPAR + k;
							}
							if (ts->_hoops_PRHH)
								_hoops_CIHAC (_hoops_RRIRC, ts->_hoops_PRHH[fi], _hoops_CSRGR->_hoops_SRIRC);
							if (ts->_hoops_PAGI)
								FORCE_COLOR_4F (ts->_hoops_PAGI[fi].red,
                                               ts->_hoops_PAGI[fi].green,
                                               ts->_hoops_PAGI[fi].blue,
                                               _hoops_IRIR,
                                               _hoops_CRSPH);
						}
						glVertex3fv (&ts->points[_hoops_HCGS].x);
						j++;
						k++;
					}
					glEnd ();
				}
				j = _hoops_SAHAR;
			}
			if (ts->lengths)
				_hoops_SSPAR = _hoops_SSPAR + ts->lengths[i] - 2;
			else
				_hoops_SSPAR++;
		}
	}
	if (_hoops_PGCRC) {
		j = 0;
		_hoops_SSPAR = -1;
		_hoops_HCGS = -1;
		glBegin (GL_TRIANGLES);
		for (i = 0; i < ts->_hoops_PHHA; i++) {
			if (!ts->lengths || ts->lengths[i] < _hoops_CIIPP) {
				if (ts->lengths)
					_hoops_SAHAR = j + ts->lengths[i];
				else
					_hoops_SAHAR = j + 3;
				j += 2;
				while (j<_hoops_SAHAR) {
					if (ts->face_indices)
						_hoops_SSPAR = ts->face_indices[j];
					else
						_hoops_SSPAR++;
					if (!dc->_hoops_CGHAR || dc->_hoops_CGHAR[_hoops_SSPAR]) {
						if (ts->_hoops_AIHA)
							_hoops_HCGS = ts->_hoops_AIHA[j-2];
						else
							_hoops_HCGS++;
						if (ts->_hoops_PAGI) {
							FORCE_COLOR_4F (ts->_hoops_PAGI[_hoops_SSPAR].red,
                                            ts->_hoops_PAGI[_hoops_SSPAR].green,
                                            ts->_hoops_PAGI[_hoops_SSPAR].blue,
                                            _hoops_IRIR,
                                            _hoops_CRSPH);
						}
						if (_hoops_CSRGR->_hoops_SPGRC) {
							(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*ts->_hoops_GSSH->_hoops_GSHA]);
							(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*ts->_hoops_GSSH->_hoops_GSHA+2]);
						}
						else if (rc->params[rc->pass]) {
							if (rc->param_width[rc->pass] == 2)
								glTexCoord2fv (&(rc->params[rc->pass])[_hoops_HCGS*rc->param_width[rc->pass]]);
							else
								glTexCoord3fv (&(rc->params[rc->pass])[_hoops_HCGS*rc->param_width[rc->pass]]);
						}
						else if (rc->_hoops_GCI[rc->pass] == _hoops_RIGRC) {
							glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
						}
						else if (ts->_hoops_PCHA)
							FORCE_COLOR_4F (ts->_hoops_PCHA[_hoops_HCGS].red,
                                            ts->_hoops_PCHA[_hoops_HCGS].green,
                                            ts->_hoops_PCHA[_hoops_HCGS].blue,
                                            _hoops_IRIR,
                                            _hoops_CRSPH);
						if (ts->_hoops_ICHA)
							_hoops_RRCRC (_hoops_RRIRC, ts->_hoops_ICHA[_hoops_HCGS], ts->points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
						else if (ts->_hoops_PRHH)
							_hoops_CIHAC (_hoops_RRIRC, ts->_hoops_PRHH[_hoops_SSPAR], _hoops_CSRGR->_hoops_SRIRC);
						glVertex3fv (&ts->points[_hoops_HCGS].x);

						if (ts->_hoops_AIHA)
							_hoops_HCGS = ts->_hoops_AIHA[j-1];
						else
							_hoops_HCGS++;
						if (_hoops_CSRGR->_hoops_SPGRC) {
							(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*ts->_hoops_GSSH->_hoops_GSHA]);
							(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*ts->_hoops_GSSH->_hoops_GSHA+2]);
						}
						else if (rc->params[rc->pass]) {
							glTexCoord2fv (&(rc->params[rc->pass])[_hoops_HCGS*rc->param_width[rc->pass]]);
						}
						else if (rc->_hoops_GCI[rc->pass] == _hoops_RIGRC) {
							glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
						}
						else if (ts->_hoops_PCHA)
							FORCE_COLOR_4F (ts->_hoops_PCHA[_hoops_HCGS].red,
                                            ts->_hoops_PCHA[_hoops_HCGS].green,
                                            ts->_hoops_PCHA[_hoops_HCGS].blue,
                                            _hoops_IRIR,
                                            _hoops_CRSPH);
						if (ts->_hoops_ICHA)
							_hoops_RRCRC (_hoops_RRIRC, ts->_hoops_ICHA[_hoops_HCGS], ts->points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
						/* _hoops_PSP _hoops_RSAHC */
						glVertex3fv (&ts->points[_hoops_HCGS].x);

						if (ts->_hoops_AIHA)
							_hoops_HCGS = ts->_hoops_AIHA[j];
						else
							_hoops_HCGS++;
						if (_hoops_CSRGR->_hoops_SPGRC) {
							(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*ts->_hoops_GSSH->_hoops_GSHA]);
							(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*ts->_hoops_GSSH->_hoops_GSHA+2]);
						}
						else if (rc->params[rc->pass]) {
							glTexCoord2fv (&(rc->params[rc->pass])[_hoops_HCGS*rc->param_width[rc->pass] ]);
						}
						else if (rc->_hoops_GCI[rc->pass] == _hoops_RIGRC) {
							glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
						}
						else if (ts->_hoops_PCHA)
							FORCE_COLOR_4F (ts->_hoops_PCHA[_hoops_HCGS].red,
                                            ts->_hoops_PCHA[_hoops_HCGS].green,
                                            ts->_hoops_PCHA[_hoops_HCGS].blue,
                                            _hoops_IRIR,
                                            _hoops_CRSPH);
						if (ts->_hoops_ICHA)
							_hoops_RRCRC (_hoops_RRIRC, ts->_hoops_ICHA[_hoops_HCGS], ts->points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
						/* _hoops_PSP _hoops_RSAHC */
						glVertex3fv (&ts->points[_hoops_HCGS].x);
					}
					j++;

					if (j == _hoops_SAHAR)
						break;

					if (ts->face_indices)
						_hoops_SSPAR = ts->face_indices[j];
					else
						_hoops_SSPAR++;
					if (!dc->_hoops_CGHAR || dc->_hoops_CGHAR[_hoops_SSPAR]) {
						_hoops_HCGS = ts->_hoops_AIHA[j];
						if (ts->_hoops_PAGI)
							FORCE_COLOR_4F (ts->_hoops_PAGI[_hoops_SSPAR].red,
                                            ts->_hoops_PAGI[_hoops_SSPAR].green,
                                            ts->_hoops_PAGI[_hoops_SSPAR].blue,
                                            _hoops_IRIR,
                                            _hoops_CRSPH);
						if (_hoops_CSRGR->_hoops_SPGRC) {
							(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*ts->_hoops_GSSH->_hoops_GSHA]);
							(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*ts->_hoops_GSSH->_hoops_GSHA+2]);
						}
						else if (rc->params[rc->pass]) {
							glTexCoord2fv (&(rc->params[rc->pass])[_hoops_HCGS*rc->param_width[rc->pass]]);
						}
						else if (rc->_hoops_GCI[rc->pass] == _hoops_RIGRC) {
							glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
						}
						else if (ts->_hoops_PCHA)
							FORCE_COLOR_4F (ts->_hoops_PCHA[_hoops_HCGS].red,
                                            ts->_hoops_PCHA[_hoops_HCGS].green,
                                            ts->_hoops_PCHA[_hoops_HCGS].blue,
                                            _hoops_IRIR,
                                            _hoops_CRSPH);
						if (ts->_hoops_ICHA)
							_hoops_RRCRC (_hoops_RRIRC, ts->_hoops_ICHA[_hoops_HCGS], ts->points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
						else if (ts->_hoops_PRHH)
							_hoops_CIHAC (_hoops_RRIRC, ts->_hoops_PRHH[_hoops_SSPAR], _hoops_CSRGR->_hoops_SRIRC);
						glVertex3fv (&ts->points[_hoops_HCGS].x);

						_hoops_HCGS = ts->_hoops_AIHA[j-1];
						if (_hoops_CSRGR->_hoops_SPGRC) {
							(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*ts->_hoops_GSSH->_hoops_GSHA]);
							(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*ts->_hoops_GSSH->_hoops_GSHA+2]);
						}
						else if (rc->params[rc->pass]) {
							glTexCoord2fv (&(rc->params[rc->pass])[_hoops_HCGS*rc->param_width[rc->pass]]);
						}
						else if (rc->_hoops_GCI[rc->pass] == _hoops_RIGRC) {
							glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
						}
						else if (ts->_hoops_PCHA)
							FORCE_COLOR_4F (ts->_hoops_PCHA[_hoops_HCGS].red,
                                            ts->_hoops_PCHA[_hoops_HCGS].green,
                                            ts->_hoops_PCHA[_hoops_HCGS].blue,
                                            _hoops_IRIR,
                                            _hoops_CRSPH);
						if (ts->_hoops_ICHA)
							_hoops_RRCRC (_hoops_RRIRC, ts->_hoops_ICHA[_hoops_HCGS], ts->points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
						/* _hoops_PSP _hoops_RSAHC */
						glVertex3fv (&ts->points[_hoops_HCGS].x);

						_hoops_HCGS = ts->_hoops_AIHA[j-2];
						if (_hoops_CSRGR->_hoops_SPGRC) {
							(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*ts->_hoops_GSSH->_hoops_GSHA]);
							(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*ts->_hoops_GSSH->_hoops_GSHA+2]);
						}
						else if (rc->params[rc->pass]) {
							glTexCoord2fv (&(rc->params[rc->pass])[_hoops_HCGS*rc->param_width[rc->pass]]);
						}
						else if (rc->_hoops_GCI[rc->pass] == _hoops_RIGRC) {
							glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
						}
						else if (ts->_hoops_PCHA)
							FORCE_COLOR_4F (ts->_hoops_PCHA[_hoops_HCGS].red,
                                            ts->_hoops_PCHA[_hoops_HCGS].green,
                                            ts->_hoops_PCHA[_hoops_HCGS].blue,
                                            _hoops_IRIR,
                                            _hoops_CRSPH);
						if (ts->_hoops_ICHA)
							_hoops_RRCRC (_hoops_RRIRC, ts->_hoops_ICHA[_hoops_HCGS], ts->points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
						/* _hoops_PSP _hoops_RSAHC */
						glVertex3fv (&ts->points[_hoops_HCGS].x);
					}
					j++;
				}
				j = _hoops_SAHAR;
			}
			else {
				j += ts->lengths[i];
				_hoops_SSPAR += ts->lengths[i] - 2;
			}
		}
		glEnd ();
	}

} /* _hoops_RSGR _hoops_API '_hoops_CRHH _hoops_ASAHC _hoops_PGSA' */


/*
 * _hoops_PGAA
 */
local _hoops_IAPA const *
_hoops_PSAHC (
		Net_Rendition const & nr)
{
	_hoops_SSP const &	_hoops_GGH = nr->transform_rendition->_hoops_RGH;
	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			return _hoops_GGH->_hoops_IRH;
		}
		else
			return _hoops_GGH->_hoops_PHCA;
	}
	return null;
}


#define _hoops_HSAHC(nr, _hoops_ISAHC) \
		(nr->_hoops_IHA->pattern == FP_SOLID ? \
			false : \
			define_face_stipple(nr,_hoops_ISAHC))


/*
 * _hoops_PGAA
 */
local bool
define_face_stipple (
		Net_Rendition const & nr,
		int _hoops_ISAHC)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	unsigned int stipple[32];
	int _hoops_RASP = 0;
	bool _hoops_GPIAR = false;
	int i, j;

	if (_hoops_SIGA->pattern == FP_USER_DEFINED) {
		if (_hoops_SIGA->_hoops_PGPH != null && _hoops_SIGA->_hoops_PGPH->stipple)
			_hoops_RASP = _hoops_SIGA->_hoops_PGPH->stipple;
		else
			_hoops_GPIAR = true;
	}

	if (_hoops_ISAHC == 0) {
		if (_hoops_RASP) {
			int _hoops_PHPSR;
			const unsigned char *pattern;

			_hoops_PHPSR = (int)(64 - _hoops_RASP);
			pattern = _hoops_HRPH[_hoops_PHPSR];
			/* _hoops_IRCH _hoops_HSGP _hoops_HII 8x8 _hoops_IS 8x32 */
			for (i = 0; i < 8; i++) {
				stipple[i] = pattern[i];
				stipple[i] |= stipple[i] << 8;
				stipple[i] |= stipple[i] << 16;
			}
			/* _hoops_IRCH _hoops_HSGP _hoops_HII 8x32 _hoops_IS 32x32 */
			_hoops_AIGA (stipple,  8, unsigned int, stipple+8);
			_hoops_AIGA (stipple, 16, unsigned int, stipple+16);
			glEnable (GL_POLYGON_STIPPLE);
			glPolygonStipple ((GLubyte const *)stipple);
		}
		else if (_hoops_GPIAR) {
			for (i = 0; i < _hoops_SIGA->_hoops_PGPH->height; i++) {
				int	index = _hoops_SIGA->_hoops_PGPH->height-1 - i;

				stipple[index] = 0;
				for (j = 0; j < _hoops_SIGA->_hoops_PGPH->width; j++) {
					if (_hoops_SIGA->_hoops_PGPH->pattern[i*_hoops_SIGA->_hoops_PGPH->width + j] == 0)
						stipple[index] |= 1 << (_hoops_SIGA->_hoops_PGPH->width-1 - j);
				}
				while (j<32) {
					stipple[index] |= stipple[index]<<j;
					j <<= 1;
				}
			}
			while (i<32) {
				_hoops_AIGA (stipple, i, unsigned int, stipple+i);
				i <<= 1;
			}
			glEnable (GL_POLYGON_STIPPLE);
			glPolygonStipple ((GLubyte const *)stipple);
		}
	}
	else if (_hoops_ISAHC == 1) {
		if (_hoops_RASP ||
			(_hoops_GPIAR && _hoops_SIGA->_hoops_PGPH->_hoops_ACHHP == UPAT_NO_CONTRAST)) {
			glDisable (GL_POLYGON_STIPPLE);
			return false;
		}

		/* _hoops_HHSP _hoops_SS _hoops_PPR _hoops_SGH _hoops_RH _hoops_HSP _hoops_CGARA _hoops_HAIR */
		_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
		_hoops_ICGRC(_hoops_CSRGR);
		_hoops_SCIGC (_hoops_CSRGR);
		FORCE_COLOR (_hoops_CSRGR, &_hoops_SIGA->contrast_color, false);
		if (_hoops_GPIAR) {
			for (i = 0; i < 32; i++) {
				stipple[i] ^= ~0UL;
			}
			/* _hoops_AIAH _hoops_PPP */
			glPolygonStipple ((GLubyte const *)stipple);
		}
		else {
			glEnable (GL_POLYGON_STIPPLE);
			ENSURE_FACE_PATTERN (_hoops_CSRGR, _hoops_SIGA->pattern);
		}
	}
	else {
		glDisable (GL_POLYGON_STIPPLE);
		return false;
	}
	return true;

}  //_hoops_RSGR _hoops_API '_hoops_PPIP _hoops_HSP _hoops_GIPRC'


local bool
_hoops_APARC (
		OGLData alter *_hoops_CSRGR,
		_hoops_PC const & _hoops_HC)
{
	_hoops_AS const * light;

	if (!_hoops_HC ||
		_hoops_CSRGR->_hoops_RIRGC)
		return false;
	if ((light = _hoops_HC->_hoops_CGR) != null)
	{
		if (light->_hoops_PRR == _hoops_I)
			return true;
	} ((light = light->next) != null);
	return false;
}


/*
 * _hoops_PGAA
 */
local bool _hoops_RSIS (
		Net_Rendition const &nr,
		_hoops_GAHS const *_hoops_ICIS)
{
	if (_hoops_ICIS->bounding._hoops_HICAR())
		return true;

	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;

	int	_hoops_SIHS = 0;

	if (BIT (nr->transform_rendition->_hoops_APH, _hoops_RIHS))
		_hoops_SIHS = nr->_hoops_IRR->_hoops_GCHS;
	if (BIT (nr->transform_rendition->_hoops_APH, Heur_Culling_EXTENT))
		_hoops_SIHS = _hoops_IAAA(nr->_hoops_IRR->_hoops_GRGC, _hoops_SIHS);

	Test	_hoops_ASIS;
	float	_hoops_CIHS;

	int _hoops_PIHS = HD_Transform_And_Test_Simple_Sphere (nr, 1, &_hoops_ICIS->bounding->sphere, null, 
							0, _hoops_SIHS, &_hoops_ASIS, null, &_hoops_CIHS);

	if (_hoops_CIHS > 0.0f &&
		nr->_hoops_IRR->_hoops_PCHS == Heur_MAX_EXTENT_MODE_DEFER) { 

		int _hoops_HCHS = (int) (_hoops_CIHS * (float)_hoops_ICHS / (float)_hoops_SIHS);

		if (_hoops_HCHS > dc->_hoops_SSGC)
			((Display_Context alter *)dc)->_hoops_SSGC = _hoops_HCHS;
	}

	if (!_hoops_PIHS)
		_hoops_GPRH (_hoops_CCHS)++;

	return _hoops_PIHS != 0;
}

/*
 * _hoops_PGAA
 */
local void
_hoops_RRRI (
		Net_Rendition const &		nr,
		Tristrip const *			ts,
		OGL_Display_List_Bin *		_hoops_RRHA)
{
	nr._hoops_SSAGR();
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;
	OGLData alter *				_hoops_CSRGR = OGLD (dc);
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_IHCR._hoops_SSAGR();
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	_hoops_SIGA._hoops_SSAGR();
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	_hoops_RRGH._hoops_SSAGR();
	_hoops_HHA const &	matr = _hoops_SIGA->_hoops_CHA;
	OGL_Render_Control *		rc = &_hoops_CSRGR->_hoops_CSC._hoops_PAPAC;
	_hoops_HRPA const *			matrix = null;
	RGB const *					_hoops_GPCP = null;
	int							_hoops_RASP = 0;// _hoops_CSAHC = 0;
	bool						_hoops_CRRS;
	int							_hoops_RRIRC = 0;
	OGL_Vertex_Buffer_Object *	_hoops_SAAS = null;
	_hoops_IPSGC *				pair;
	_hoops_SARHC	_hoops_APHA = _hoops_GPRHC(ts, _hoops_SIGA, _hoops_RRHA);
	_hoops_IAPA const *	_hoops_CAPA = null;
	int							_hoops_ISAHC = 0;
	bool 						_hoops_CISP;
	bool						_hoops_IAHC = false;


	_hoops_RAPRC("draw_3d_tristrip", true);

	_hoops_CISP = BIT (nr->_hoops_PSGI, T_FACES);

	if (!_hoops_RRHA) {
		if (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC) {
			_hoops_IAHC = _hoops_HGRI (nr, ts->_hoops_SRHA, _hoops_CISP);

			if (!_hoops_IAHC && BIT(ts->_hoops_SRHA, _hoops_GGIA))
				_hoops_IAHC = !OGL_DEFINE_INTERPOLATION_TEXTURE (_hoops_CSRGR, nr);

			if (_hoops_IAHC) {
				if (BIT(ts->_hoops_SRHA, DL_DO_NOT_RECOMPILE))
					_hoops_SCARC (nr, ts);
				else
					HD_Std_3D_Tristrip (nr, ts);
				return;
			}
		}
	}
	else {
		pair = _hoops_RRHA->_hoops_CRHA->PeekFirst();
		ts = (Tristrip *)pair->geo;
		if (BIT(ts->_hoops_SRHA, _hoops_GGIA))
			_hoops_IAHC = !OGL_DEFINE_INTERPOLATION_TEXTURE (_hoops_CSRGR, nr);
		ASSERT (!_hoops_IAHC); //_hoops_CGH _hoops_HS _hoops_RPII _hoops_RAICR _hoops_ARPP _hoops_SR _hoops_GGHP _hoops_ARI
	}

	/* _hoops_PSCPR _hoops_IS _hoops_RH _hoops_RHGS _hoops_RSAHH _hoops_GAR _hoops_IRS _hoops_RPPR _hoops_GCASI _hoops_CRAA _hoops_SGS _hoops_SIHR _hoops_HCR
	 * _hoops_IIGR _hoops_RH _hoops_AGRR _hoops_GHCII _hoops_RPIA _hoops_ARAR */
	if (!_hoops_CSRGR->_hoops_IHPGC) {
		_hoops_GIGHC (nr, ts, _hoops_RRHA);
		return;
	}
	if (BIT (ts->_hoops_SRHA, _hoops_GGIA) &&
		matr->_hoops_ARIR) {
		_hoops_GIGHC (nr, ts, _hoops_RRHA);
		return;
	}
	if (_hoops_APARC (_hoops_CSRGR, _hoops_SIGA->_hoops_AGP)) {
		_hoops_GIGHC (nr, ts, _hoops_RRHA);
		return;
	}
	if (ts->_hoops_ICHA &&
		matr->texture[_hoops_RIA]) {
		_hoops_GIGHC (nr, ts, _hoops_RRHA);
		return;
	}

	if (ts->total > 2000000) {
		_hoops_GIGHC (nr, ts, _hoops_RRHA);
		return;
	}

	if (ts->_hoops_GSSH && ts->_hoops_GSSH->_hoops_CCHA) {
		int _hoops_ASARC = 0;
		if (ts->_hoops_GSSH->_hoops_GSHA > 3) {
			/* _hoops_RPR _hoops_SPI _hoops_AI */
			if (matr->_hoops_SCA) {
				_hoops_HIR *_hoops_GRIA = matr->_hoops_SCA;
				do {
					_hoops_ASARC++;
				} while ((_hoops_GRIA = _hoops_GRIA->next) != null);
			}

			if (matr->texture[_hoops_HIA])
				_hoops_ASARC++;
		}
		if (matr->texture[_hoops_IIA] ||
			_hoops_ASARC > 1 || 
			(ts->_hoops_GSSH->_hoops_GSHA > 3 && ts->_hoops_GSSH->_hoops_GSHA != 5) ||
			BIT (ts->_hoops_GSSH->_hoops_SCAI, _hoops_HPPAR)) {
			_hoops_GIGHC (nr, ts, _hoops_RRHA);
			return;
		}
	}

	if (_hoops_APHA == _hoops_HARHC) {
		_hoops_GIGHC (nr, ts, _hoops_RRHA);
		return;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_GRHH) &&
		BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES)) {
		if (BIT (HOOPS_WORLD->system_flags, _hoops_RGRI) ||
		   !ANYBIT (_hoops_IHCR->heuristics, _hoops_RSA)) {
			_hoops_RRIRC = _hoops_PRIRC;
			_hoops_HRIRC(_hoops_CSRGR, nr);
		}
	}

	/* _hoops_HHIGR _hoops_HRGR _hoops_HAR _hoops_ICIC _hoops_IS _hoops_CAH _hoops_GRHCP _hoops_RGR _hoops_PPSR */
	if (_hoops_CSRGR->_hoops_ISCI > 0)
	{
		bool _hoops_HIRS = false;

		if (BIT(ts->_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
			_hoops_SCARC (nr, ts);
			return;
		}

		if (ANYBIT (_hoops_CSRGR->_hoops_CIGI->_hoops_RRSI, _hoops_PGRI))
			return;

		if (!_hoops_CSRGR->_hoops_CSC._hoops_RAIH && _hoops_CISP)
			_hoops_HIRS = true;

		if (!BIT (ts->_hoops_SRHA, DL_SUPPRESS_SEGMENT_DISPLAY_LISTS) &&
			!_hoops_HIRS) {

			bool _hoops_IIRS = (dc->_hoops_SPA->color &&
				ANYBIT (dc->_hoops_SPA->color->_hoops_GHA, Color_FACE));

			if (ts->_hoops_AIHA == null)
				return;

			if (!ts->_hoops_PCHA &&
				!ts->_hoops_PAGI &&
				!_hoops_IIRS &&
				nr->_hoops_IHA->_hoops_CPA != _hoops_CSRGR->_hoops_CIGI->nr->_hoops_IHA->_hoops_CPA)
				_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_PGRI;

			if (!_hoops_CSRGR->_hoops_CIGI->_hoops_RCGI)
				_hoops_CSRGR->_hoops_CIGI->_hoops_RCGI = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);

			if (BIT(ts->_hoops_SRHA, DL_TEMPORARY_DATA)) {
				HD_Isolate_Tristrip_Data (dc, ts);
			}

			Tristrip alter *_hoops_IPIAR = (Tristrip alter *)ts;
			_hoops_IPIAR->_hoops_CARI |= _hoops_SARI;
			ASSERT(ts->_hoops_GSCP != null);

			_hoops_IPSGC *pair = POOL_NEW(dc->memory_pool, _hoops_IPSGC)(nr, ts, dc->_hoops_SPA->modelling_matrix, dc->_hoops_SPA->color);

			_hoops_CSRGR->_hoops_CIGI->_hoops_RCGI->AddFirst(pair);
			return;
		}
		_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_PGRI;
		if (_hoops_CSRGR->_hoops_CIGI->_hoops_IHGI)
			return;

		bool _hoops_IHHS =
			!BIT (_hoops_IHCR->flags, _hoops_CHHS) &&
				BIT (_hoops_RRGH->_hoops_SHHS, _hoops_GIHS) &&
				(ANYBIT (_hoops_IHCR->_hoops_APH, Heur_Culling_EXTENT|_hoops_RIHS) ||
					(BIT (_hoops_IHCR->_hoops_APH, Heur_Culling_VIEW_FRUSTUM) &&
						!BIT (_hoops_IHCR->flags, _hoops_AIHS)));

		if (_hoops_IHHS && !_hoops_RSIS (nr, (_hoops_GAHS *)ts))
			return;
	}

	if (BIT (ts->_hoops_SRHA, DL_DO_NOT_RECOMPILE))
		_hoops_CRRS = true;
	else if (_hoops_RRGH->_hoops_GAHA == Display_List_GEOMETRY)
		_hoops_CRRS = !BIT(ts->_hoops_SRHA, DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS);
	else if (_hoops_RRGH->_hoops_GAHA == Display_List_SEGMENT) {
		if (_hoops_RRHA)
			_hoops_CRRS = !BIT(ts->_hoops_SRHA, DL_SUPPRESS_SEGMENT_DISPLAY_LISTS);
		else
			_hoops_CRRS = !BIT(ts->_hoops_SRHA, DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS);
	}
	else
		_hoops_CRRS = false;
	if (!_hoops_CSRGR->_hoops_RRSGC ||
		_hoops_RRIRC == _hoops_PRIRC)
		_hoops_CRRS = false;

	if (_hoops_CRRS) {
		_hoops_GACR alter *dl = null;
		OGL_Display_List alter *odl = null;
		bool _hoops_RACR = false;

		if (_hoops_RRHA) {
			ZALLOC (odl, OGL_Display_List);
			AGLM(odl->_hoops_CSRGR = OGLD(dc));
			_hoops_RRHA->odl = odl;
			odl->_hoops_GHRI = dc->_hoops_GHRI;
			odl->time_stamp = HOOPS_WORLD->_hoops_GPPI;
			odl->type = OGL_DL_GEOMETRY_VBO;
			if (ts->_hoops_GSCP)
				odl->_hoops_HHCAP = (void*)ts->_hoops_GSCP->key;
			_hoops_RACR = true;
		}
		else {
			bool _hoops_GCPS, _hoops_SRGHC;
			Tristrip alter *_hoops_RPIAR = (Tristrip alter *) ts;

			_hoops_RACR = _hoops_AACR(nr, &_hoops_RPIAR->_hoops_GAHA, &dl, &odl, OGL_DL_GEOMETRY_VBO);
			_hoops_SRGHC = (odl->item.geometry.id == _hoops_RSARR);
			if (!_hoops_RACR) {
				_hoops_GCPS = _hoops_RPRC (nr, ts, dl, odl);
				if (!_hoops_GCPS) {
					HD_Queue_Destroy_List (odl, true);
					if (BIT (ts->_hoops_SRHA, DL_DO_NOT_RECOMPILE))
						return;  //_hoops_CIS _hoops_HRGR _hoops_HGSAR _hoops_IH _hoops_SSAHC _hoops_PIH.
					_hoops_RACR = _hoops_AACR(nr, &_hoops_RPIAR->_hoops_GAHA, &dl, &odl, OGL_DL_GEOMETRY_VBO);
				}
			}
		}
		if (dl)
			dl->_hoops_GSAI = ts->_hoops_GSAI;

		if (odl->item.geometry.id == _hoops_RSARR) {
			// _hoops_GGSR _hoops_IIGR _hoops_AAGC
			_hoops_SAAS = null;
		}
		else if (_hoops_RACR) {
			odl->item.geometry._hoops_GSAI = ts->_hoops_GSAI;
			odl->item.geometry.param_flags[0] = ts->_hoops_GSSH ? ts->_hoops_GSSH->_hoops_SCAI : 0;
			odl->item.geometry._hoops_SRHA = ts->_hoops_SRHA;
			odl->item.geometry._hoops_CARI = ts->_hoops_CARI;
			odl->item.geometry._hoops_IRRI = ts->face_attributes.flags;

			if (BIT(ts->_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
				ASSERT (!_hoops_RRHA);
				_hoops_SCARC (nr, ts);
				return;
			}

			int _hoops_GCI = _hoops_RRHRC (ts);
			if (HOOPS_WORLD->display_list_vram_usage + _hoops_GCI > HOOPS_WORLD->_hoops_PHARR) {
				if (dl && odl) {
					dl->_hoops_AGRI |= DL_INSUFFICIENT_VRAM;
					odl->item.geometry.id = _hoops_RSARR; /* _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_GRHP _hoops_IRCC */
					odl->_hoops_CARH = 0;
				}
			}
			else {
				//_hoops_CSRI->_hoops_GGPHC = _hoops_RGPHC (_hoops_ARAI, _hoops_SCII, _hoops_GARI, _hoops_SCGI);
				odl->_hoops_CARH = _hoops_SAAHC (&_hoops_SAAS, nr, ts, _hoops_RRHA);
				odl->item.geometry.id = V2I(_hoops_SAAS);
				if (_hoops_RRHA) {
					if (!_hoops_SAAS)
					{
						_hoops_RRHA->_hoops_AGRI = DL_FLAG_INVALID;
						return;
					}
					odl->item.geometry._hoops_SRHA = _hoops_RRHA->_hoops_AGRI;
				}
				else
					odl->item.geometry._hoops_SRHA = ts->_hoops_SRHA;
				HOOPS_WORLD->display_list_vram_usage += odl->_hoops_CARH;
			}
		}
		else if (odl->type == OGL_DL_GEOMETRY) {
			_hoops_GIGHC (nr, ts, _hoops_RRHA);
			return;
		}
		else if (odl->type == OGL_DL_GEOMETRY_VBO) {
			odl->_hoops_GPPI = HOOPS_WORLD->_hoops_GPPI;
			_hoops_SAAS = (OGL_Vertex_Buffer_Object *) I2V(odl->item.geometry.id);
		}
		else
			_hoops_SAAS = null;
	}

	ZERO_STRUCT(rc, OGL_Render_Control);
	_hoops_SAARC (nr, rc, ts);

	_hoops_GGGH(_hoops_CSRGR, nr);
	/* _hoops_IRAA _hoops_PICP _hoops_IIGR _hoops_IRS _hoops_HRGHC _hoops_IIGR _hoops_IRGHC _hoops_GGR _hoops_PGAP _hoops_RH _hoops_HSAGA _hoops_IIGR _hoops_CRGHC
	 * _hoops_PAH _hoops_SHH _hoops_GCGP */
	if (_hoops_CSRGR->_hoops_GGCGC) {
		if (!matrix)
			_hoops_SAHRC (_hoops_CSRGR, _hoops_IHCR, false);
	}
	else {
		if (BIT (ts->_hoops_SRHA, DL_NEGATIVE_3X3))
			_hoops_SAHRC (_hoops_CSRGR, _hoops_IHCR, true);
	}
	_hoops_HISP(_hoops_CSRGR, BIT(_hoops_RRGH->_hoops_CHP, _hoops_GPSP));
	_hoops_PIIGC(_hoops_CSRGR, nr);
	ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
	ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH && !_hoops_RASP);
	_hoops_IPGP(_hoops_CSRGR, BIT(nr->transform_rendition->flags, _hoops_CASP));
	if (_hoops_APHA == _hoops_PARHC)
		ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);
	else
		ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_SMOOTH);

	if (_hoops_CSRGR->_hoops_CIGI &&
		_hoops_CSRGR->_hoops_CIGI->_hoops_IHGI) {
		if (_hoops_RRHA && !_hoops_SAAS)
			_hoops_RRHA->_hoops_AGRI = DL_FLAG_INVALID;
		return;
	}
	if (_hoops_RRHA && _hoops_SAAS)
		return;  //_hoops_RH _hoops_ACSP _hoops_GRS _hoops_SHH _hoops_GIR _hoops_HPP _hoops_GRCI _hoops_SIHH _hoops_IRS _hoops_SCGI.

	if (_hoops_SAAS) {
		/* _hoops_AGPHC _hoops_PGPHC */
		_hoops_HSAHC (nr, _hoops_ISAHC);
		do {													//_hoops_IH _hoops_GRR _hoops_GIPRC _hoops_RIH
			rc->pass = 0;
			do {												//_hoops_IH _hoops_GRR _hoops_RIH
				_hoops_CAPA = _hoops_PSAHC (nr);
				if (!_hoops_ISAHC)
					pre_pass(nr, rc, ts);
				do {											//_hoops_IH _hoops_GRR _hoops_AACC _hoops_ARP
					if (_hoops_CAPA)
						_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
					_hoops_PCAHC (_hoops_SAAS, nr, rc);
					if (_hoops_CAPA != null)
						_hoops_CAPA = _hoops_CAPA->next;
				} while (_hoops_CAPA != null);
				if (_hoops_ISAHC)
					break;
			} while (_hoops_GPRRC(nr, ts->_hoops_GSSH ? ts->_hoops_GSSH->_hoops_GSHA : 0, ts->_hoops_GSSH ? ts->_hoops_GSSH->_hoops_SCAI : 0, rc));
			_hoops_ISAHC++;
		} while (_hoops_HSAHC (nr, _hoops_ISAHC));
	}
	else {
		/* _hoops_HGPHC _hoops_PGPHC */
		ASSERT (!BIT(ts->_hoops_SRHA, DL_DO_NOT_RECOMPILE));
		bool _hoops_CCIRC = true;
		if (ts->_hoops_ICHA) {
			if (BIT (HOOPS_WORLD->system_flags, _hoops_RGRI) ||
			   !ANYBIT (_hoops_IHCR->heuristics, _hoops_RSA))
				_hoops_CCIRC = false;
		}
		else if (ts->_hoops_PRHH || ts->_hoops_PAGI)
			_hoops_CCIRC = false;
		if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_NONDL_VERTEX_ARRAYS))
			_hoops_CCIRC = false;

		bool _hoops_IHHS =
			!BIT (_hoops_IHCR->flags, _hoops_CHHS) &&
				BIT (_hoops_RRGH->_hoops_SHHS, _hoops_GIHS) &&
				(ANYBIT (_hoops_IHCR->_hoops_APH, Heur_Culling_EXTENT|_hoops_RIHS) ||
					(BIT (_hoops_IHCR->_hoops_APH, Heur_Culling_VIEW_FRUSTUM) &&
						!BIT (_hoops_IHCR->flags, _hoops_AIHS)));

		_hoops_HSAHC (nr, _hoops_ISAHC);
		do {
			if (_hoops_RRHA) {
				_hoops_RRHA->_hoops_CRHA->ResetCursor();
				pair = _hoops_RRHA->_hoops_CRHA->PeekFirst();
				ts = (Tristrip *) pair->geo;
			}
			for (;;) {											//_hoops_IH _hoops_GRR _hoops_GARI
				if (!_hoops_IHHS || _hoops_RSIS (nr, (_hoops_GAHS const *)ts)) {
					rc->pass = 0;
					do {											//_hoops_IH _hoops_GRR _hoops_RIH
						_hoops_CAPA = _hoops_PSAHC (nr);
						if (!_hoops_ISAHC)
							if (!pre_pass(nr, rc, ts))
								continue;

						do {										//_hoops_IH _hoops_GRR _hoops_AACC _hoops_ARP
							if (_hoops_CAPA)
								_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
							if (_hoops_CCIRC)
								_hoops_ICAHC (nr, rc, ts);
							else
								_hoops_GSAHC (nr, rc, ts);
							if (_hoops_CAPA != null)
								_hoops_CAPA = _hoops_CAPA->next;

						} while (_hoops_CAPA != null);

						_hoops_GPRH(_hoops_GRHAR)++;
						_hoops_GPRH(_hoops_PCCA) += ts->total - 2*ts->_hoops_PHHA;

						if (_hoops_ISAHC)
							break;

					} while (_hoops_GPRRC(nr, ts->_hoops_GSSH ? ts->_hoops_GSSH->_hoops_GSHA : 0, ts->_hoops_GSSH ? ts->_hoops_GSSH->_hoops_SCAI : 0, rc));
				}
				if (!_hoops_RRHA)
					break;
				_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
				pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
				if (!pair)
					break;
				ts = (Tristrip *) pair->geo;
			}
			_hoops_ISAHC++;

		} while (_hoops_HSAHC (nr, _hoops_ISAHC));
	}
	if (_hoops_CSRGR->_hoops_CSC._hoops_PRPAC[0]) {
		_hoops_SRGRC(_hoops_CSRGR,0);
		_hoops_AARRC (_hoops_CSRGR,0);
		_hoops_ICGRC(_hoops_CSRGR);
		_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
	}
	else if (ts->_hoops_PCHA || ts->_hoops_PAGI || _hoops_GPCP) {
		_hoops_ICGRC(_hoops_CSRGR);
		_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
	}

} /* _hoops_RSGR _hoops_API '_hoops_CPSA _hoops_PGSA 3d _hoops_CRHH' */






local void
_hoops_AIHRC (
	OGL_Polymarker_Vertex_Buffer_Object alter **_hoops_IGPHC,
	Net_Rendition const & nr,
	Polymarker const *pm,
	bool _hoops_RIHRC,
	int start,
	int end)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	OGL_Polymarker_Vertex_Buffer_Object alter *_hoops_SAAS;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	OptimizerScratch *scratch;
	HOGLVertexBuffer _hoops_PAIH;
	_hoops_RSPRC _hoops_PPCP;
	int stride;					//# _hoops_IIGR _hoops_PHRP, _hoops_HAR _hoops_GCSRR, _hoops_RIR _hoops_GPHA
	GLenum error;
	float *data = null;
	int i;
	Point *_hoops_APHCP = null;
	Vector *_hoops_CGPHC = null;
	RGB *_hoops_SGPHC = null;
	RGBAS32* _hoops_GRPHC = null;
	float *_hoops_RRPHC = null;
	float _hoops_IRIR = 0;

	if (!_hoops_CSRGR->_hoops_IHPGC ||
		HOOPS_WORLD->display_list_vram_usage > HOOPS_WORLD->_hoops_PHARR) {
		*_hoops_IGPHC = null;
		return;
	}

	ZALLOC (_hoops_SAAS, OGL_Polymarker_Vertex_Buffer_Object);

	if (!_hoops_CSRGR->_hoops_PISGC)
		_hoops_CSRGR->_hoops_PISGC = POOL_NEW(dc->memory_pool, OptimizerScratch)(dc->memory_pool);
	scratch = _hoops_CSRGR->_hoops_PISGC;

	error = glGetError (); //_hoops_SCAC _hoops_SPHS

	// _hoops_RAP _hoops_GH _hoops_SRAHC
	_hoops_PPCP._hoops_AIHC();
	_hoops_APHCP = pm->points + start;
	if (pm->_hoops_ICHA) {
		_hoops_PPCP._hoops_CCRS();
		_hoops_CGPHC = pm->_hoops_ICHA + start;
	}
	if (pm->_hoops_PCHA) {
		_hoops_PPCP._hoops_RPHC();
		_hoops_SGPHC = pm->_hoops_PCHA + start;
		_hoops_IRIR = nr->_hoops_SCP->_hoops_CHA->_hoops_IRIR;
	}
	if (pm->_hoops_RGIA) {
		_hoops_PPCP._hoops_RPHC();
		_hoops_GRPHC = pm->_hoops_RGIA + start;
		_hoops_IRIR = nr->_hoops_SCP->_hoops_CHA->_hoops_IRIR;
	}
	if (BIT(pm->_hoops_SRHA, _hoops_GGIA) || pm->_hoops_HCHA) {
		_hoops_PPCP._hoops_PPIGR(1);
		_hoops_PPCP._hoops_HIHC(0, 1);
		_hoops_RRPHC = pm->_hoops_HCHA + start;
	}
	//_hoops_SHS _hoops_RPP (_hoops_IRAS->_hoops_ARPHC > 0) {
	//	_hoops_SCSH _hoops_PRPHC = 0;
	//	_hoops_SCSH _hoops_HRPHC = _hoops_IRAS->_hoops_ARPHC;

	//	// _hoops_HGI _hoops_HRGR _hoops_IRS _hoops_IGRH _hoops_IIGR _hoops_IRS _hoops_RSAIP _hoops_IH _hoops_CGPR _hoops_SR _hoops_HS _hoops_RRI _hoops_RHPS _hoops_HSAR _hoops_SR _hoops_ACPA _hoops_PCPA _hoops_IS _hoops_AA _hoops_CCA.
	//	// _hoops_PS _hoops_IPASR _hoops_CAPR _hoops_IS _hoops_AI _hoops_PHGCA.
	//	_hoops_HPGP (_hoops_HRPHC) {
	//		_hoops_RPP (_hoops_PRPHC == 0) {
	//			_hoops_SCSH _hoops_IRPHC = 2;
	//			_hoops_CRPHC _hoops_RCIC _hoops_CHCGH = _hoops_SCII->_hoops_SRPHC->_hoops_ASHAR;
	//
	//			_hoops_RPP (_hoops_CHCGH->_hoops_HSHAR) {
	//				_hoops_SCSH _hoops_IAPAR = _hoops_CHCGH->_hoops_GAPHC->_hoops_HH->_hoops_IAPAR;
	//
	//				_hoops_RPP (_hoops_IAPAR == _hoops_RAPHC)
	//					_hoops_IRPHC = 1;
	//				_hoops_SHS _hoops_RPP (_hoops_IAPAR == _hoops_AAPHC)
	//					_hoops_IRPHC = 3;
	//			}
	//			_hoops_SHS {
	//				_hoops_RPP (_hoops_HRPHC == 1 || _hoops_HRPHC == 3)
	//					_hoops_IRPHC = _hoops_HRPHC;
	//			}
	//			_hoops_ICRS._hoops_PAPHC(_hoops_PRPHC++, _hoops_IRPHC);
	//			_hoops_HRPHC -= _hoops_IRPHC;
	//		}
	//		_hoops_SHS {
	//			_hoops_ICRS._hoops_PAPHC(_hoops_PRPHC++, _hoops_HGGRR(_hoops_HRPHC, 3));
	//			_hoops_HRPHC -= _hoops_HGGRR(_hoops_HRPHC, 3);
	//		}

	//		_hoops_ICRS._hoops_HAPHC();
	//	}
	//}

	_hoops_SAAS->_hoops_PPCP = _hoops_PPCP._hoops_HPCP(); //_hoops_IAPHC _hoops_SCH _hoops_SGGR _hoops_IH _hoops_RH _hoops_GRCI _hoops_SPHR
	_hoops_SAAS->point_count = end - start;

	/* _hoops_CIPH _hoops_GPHA _hoops_PIH */
	stride = _hoops_PPCP._hoops_HGHS();
	data = scratch->GetData (_hoops_SAAS->point_count*stride);
	_hoops_PAIH._hoops_IRA(data, _hoops_PPCP);

	//_hoops_RPP (_hoops_IRAS->_hoops_CPPS) {
	//	_hoops_ARAI->_hoops_CAPHC = _hoops_ICRS._hoops_SAPHC();
	//	_hoops_SRSPC (_hoops_ARAI->_hoops_GPPHC, _hoops_ARAI->_hoops_CAPHC + 1, _hoops_SCSH);	// _hoops_ASH _hoops_AII + _hoops_CGHI _hoops_SHI (_hoops_HIS _hoops_SR _hoops_PAH _hoops_CSGA _hoops_PRGH _hoops_IGAA _hoops_IIGR _hoops_GRR _hoops_HH)
	//}

	int _hoops_HCGS = start - 1;
	for (i = start; i < end ; i++) {
		if (pm->_hoops_AIHA)
			_hoops_HCGS = pm->_hoops_AIHA[i];
		else
			_hoops_HCGS++;
		_hoops_PAIH._hoops_AHCP(&pm->points[_hoops_HCGS]);
		if (pm->_hoops_ICHA) {
			_hoops_PAIH._hoops_IHCP(&pm->_hoops_ICHA[_hoops_HCGS]);
		}
		if (pm->_hoops_PCHA) {
			_hoops_SGPHC = &pm->_hoops_PCHA[_hoops_HCGS];
			if (_hoops_RIHRC) {
				float _hoops_HHGA = _hoops_SGPHC->_hoops_CPIR();
				_hoops_PAIH.color(_hoops_RRRHC, _hoops_HHGA, _hoops_HHGA, _hoops_HHGA, _hoops_IRIR);
			}
			else
				_hoops_PAIH.color(_hoops_RRRHC, _hoops_SGPHC, _hoops_IRIR);
		}
		if (pm->_hoops_RGIA){
			_hoops_GRPHC = &pm->_hoops_RGIA[_hoops_HCGS];
			if(_hoops_RIHRC){
				float _hoops_HHGA = _hoops_IRASP (_hoops_GRPHC->r, _hoops_GRPHC->g, _hoops_GRPHC->b);
				_hoops_PAIH.color(_hoops_RRRHC, _hoops_HHGA, _hoops_HHGA, _hoops_HHGA, _hoops_GRPHC->a);
			}
			else
				_hoops_PAIH.color(_hoops_RRRHC, *_hoops_GRPHC);
		}
		if (pm->_hoops_HCHA){
			_hoops_RRPHC = &pm->_hoops_HCHA[_hoops_HCGS];
			_hoops_PAIH.u(*_hoops_RRPHC);
		}
		++_hoops_PAIH;
	}
	_hoops_CSRGR->_hoops_CHPGC (1, &_hoops_SAAS->_hoops_HRPRC);
	_hoops_CSRGR->_hoops_PSPGI (GL_ARRAY_BUFFER_ARB, _hoops_SAAS->_hoops_HRPRC);
	_hoops_CSRGR->_hoops_HSPGI (GL_ARRAY_BUFFER_ARB, _hoops_SAAS->point_count*stride*sizeof(float), data, GL_STATIC_DRAW_ARB);
	_hoops_CSRGR->_hoops_PSPGI (GL_ARRAY_BUFFER_ARB, 0);

	error = glGetError ();
	if (error) {
		ASSERT (error == GL_OUT_OF_MEMORY);
		_hoops_PRPRC (_hoops_SAAS);
		*_hoops_IGPHC = null;
	}
	else {
		_hoops_SAAS->_hoops_GPGC = ((end - start) * stride * sizeof(float));
		HOOPS_WORLD->display_list_vram_usage += _hoops_SAAS->_hoops_GPGC;
		*_hoops_IGPHC = _hoops_SAAS;
	}
}


local void
_hoops_HHCRC (
		Net_Rendition const & nr,
		OGL_Polymarker_Vertex_Buffer_Object alter *_hoops_SAAS,
		float _hoops_RPIRR)
{
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_RSPRC _hoops_PPCP = _hoops_SAAS->_hoops_PPCP;
	int count;
	bool _hoops_ACAI;

	_hoops_GPRH (_hoops_RPAS) += (int)( ((float)_hoops_SAAS->point_count)*_hoops_RPIRR);

	count = _hoops_SAAS->point_count * _hoops_RPIRR;

	//_hoops_IRHH _hoops_HCR _hoops_AHSAC _hoops_RPPHC _hoops_CSCHR _hoops_IS _hoops_ARAI->_hoops_APPHC
	_hoops_CSRGR->_hoops_PSPGI (GL_ARRAY_BUFFER_ARB, _hoops_SAAS->_hoops_HRPRC);
	_hoops_ACAI = (BIT (nr->_hoops_IRR->locks.color, Color_VERTEX));
	_hoops_PPCP._hoops_PGRHC (_hoops_CSRGR, null, _hoops_ACAI);
	glDrawArrays (GL_POINTS, 0, count);
	_hoops_PPCP._hoops_IGRHC (_hoops_CSRGR);
	_hoops_CSRGR->_hoops_PSPGI (GL_ARRAY_BUFFER_ARB, 0);
}


#else

local void
_hoops_RRRI (
		Net_Rendition const &  nr,
		Tristrip const *ts,
		OGL_Display_List_Bin *_hoops_RRHA)
{
	if (_hoops_RRHA)
		_hoops_GIGHC (nr, ts, _hoops_RRHA);
	else
		old_draw_3d_tristrip (nr, ts);
}

local void
_hoops_AIHRC (
		OGL_Polymarker_Vertex_Buffer_Object alter **_hoops_IGPHC,
		Net_Rendition const & nr,
		Polymarker *pm,
		bool _hoops_RIHRC,
		int start,
		int end)
{
	*_hoops_IGPHC = null;
	UNREFERENCED (nr);
	UNREFERENCED (pm);
	UNREFERENCED (_hoops_RIHRC);
	UNREFERENCED (start);
	UNREFERENCED (end);
}


#endif

/*
 * _hoops_SRAC
 */
local void
draw_3d_tristrip (Net_Rendition const &  nr,
				  Tristrip const * ts)
{
	_hoops_RRRI (nr, ts, null);
} /* _hoops_RSGR _hoops_API '_hoops_PGSA 3d _hoops_CRHH' */


#endif



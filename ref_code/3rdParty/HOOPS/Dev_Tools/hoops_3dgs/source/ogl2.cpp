/*
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.  Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.263 2011-01-11 08:38:24 heppe Exp $
 */

#ifndef HOOPS_DEFINED
# include "hoops.h"
#endif

#include "ogl2.h"
#include "h3d_hlsl.h"

#include "hc_proto.h"
#include "hi_proto.h"
#include "phdraw.h"

#include "ogl2_post.h"
#include "ogl2_post.cpp"



static XBits	_hoops_RSPRH[] = {
	{"NONE",							XBIT_NONE},											
	{"DOUBLE_BUFFER_SWAP_ONLY",			XBIT_DOUBLE_BUFFER_SWAP_ONLY},									
	{"FORCE_DEFAULT_SOFTWARE",			XBIT_FORCE_DEFAULT_SOFTWARE},			
	{"BAD_OVERLAY",						XBIT_BAD_OVERLAY},					
	{"BAD_STENCIL",						XBIT_BAD_STENCIL},										
	{"BAD_DISPLAY_LIST",				XBIT_BAD_DISPLAY_LIST},                       
	{"LIES_ABOUT_SWAP",					XBIT_LIES_ABOUT_SWAP},										
	{"BAD_SINGLE_BUFFERING",            XBIT_BAD_SINGLE_BUFFERING},
	{"BAD_ACCUMULATION_BUFFER",         XBIT_BAD_ACCUMULATION_BUFFER},
	{"BAD_MSAA_SPRITING",				XBIT_BAD_MSAA_SPRITING},
	{"BAD_DEPTH_PEELING",				XBIT_BAD_DEPTH_PEELING},
	{"BAD_NON_POWER_OF_2_TEXTURES",		XBIT_BAD_NON_POWER_OF_2_TEXTURES},
	{"TEXTURE_SIZE_OFF_BY_ONE",			XBIT_TEXTURE_SIZE_OFF_BY_ONE},
	{"BAD_GLSL4_SAMPLER_CUBE",			XBIT_BAD_GLSL4_SAMPLER_CUBE},
	{"BAD_FLAT_SHADE_MODEL",			XBIT_BAD_FLAT_SHADE_MODEL},
	{"",0}
};

static const char * _hoops_CCGGC = "OpenGL2_Software";
static const char * _hoops_SCGGC = "OpenGL2_Hardware";



/*
* _hoops_PGAA. _hoops_IAPRH() _hoops_RCGRA _hoops_IS _hoops_CAPRH _hoops_PAAP

*/
void _hoops_SGPAR(H3DData* data)
{
	UNREFERENCED(data);
	glFinish();
}

/*****************************************************************************
*****************************************************************************
							_hoops_GIPRH _hoops_SACA
*****************************************************************************
*****************************************************************************/

class _hoops_CSHAC : public H3DGPUTimer
{
public:
	_hoops_CSHAC(H3DData* data) : 
		H3DGPUTimer(data),
		_hoops_SSHAC(0)
	{
	}

	// _hoops_SP _hoops_GH
	~_hoops_CSHAC()
	{
		HOGLData *_hoops_CSRGR = (HOGLData *)_hoops_ISS;
		if (_hoops_SSHAC)
			glDeleteQueries(1, &_hoops_SSHAC);
	}

	// _hoops_RRPP _hoops_GHIR _hoops_HII _hoops_CGHI _hoops_PRPP. _hoops_CGIGR _hoops_AASA *_hoops_SAHR _hoops_ARPP* _hoops_RH _hoops_PRPP _hoops_IS _hoops_SRCH _hoops_SGIGR _hoops_GRIGR.
	size_t _hoops_SRPP()
	{
		HOGLData *_hoops_CSRGR = (HOGLData *)_hoops_ISS;
		size_t _hoops_IRPP = 0;

		if ( _hoops_RGIGR == _hoops_AGIGR )
			_hoops_IRPP = static_cast<size_t>(_hoops_IGIGR - _hoops_HGIGR);
		else {
			ASSERT( _hoops_RGIGR == _hoops_HRIGR || _hoops_RGIGR == _hoops_ARIGR );

			if ( _hoops_RGIGR == _hoops_HRIGR ) {
				GLuint value = 0;
				while (1) {	 
					glGetQueryObjectuiv (_hoops_SSHAC, GL_QUERY_RESULT_AVAILABLE_ARB, &value);
					if (value)
						break;
				}
				if (value)
					glGetQueryObjectuiv (_hoops_SSHAC, GL_QUERY_RESULT_ARB, &value);
				else
					value = ~0U;

				_hoops_RGIGR = _hoops_ARIGR;
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
		HOGLData *_hoops_CSRGR = (HOGLData *)_hoops_ISS;

		// _hoops_GISA _hoops_IIPRH _hoops_IH _hoops_SPPP _hoops_PRPP, _hoops_PPR _hoops_CIPRH.
		if (GLEW_EXT_timer_query && !_hoops_SSHAC) {
			glGenQueries (1, &_hoops_SSHAC);

			// _hoops_CGP _hoops_SR _hoops_GGHP _hoops_CAPR _hoops_HCR, _hoops_SR _hoops_PAH _hoops_SGH _hoops_GSIA _hoops_SIPRH
			if ( _hoops_SSHAC )
				_hoops_RGIGR = _hoops_ARIGR;
			else
				_hoops_SSHAC = ~0U;
		}


		if ( _hoops_RGIGR == _hoops_AGIGR ) {
			// _hoops_ACIPA _hoops_CGRH
			glFinish();

			// _hoops_GCIH _hoops_SPPP
			_hoops_HGIGR = HI_What_Time();
		}
		else {
			// _hoops_HCPRH _hoops_CRAA. _hoops_ICPRH _hoops_CCAH _hoops_IIPRH _hoops_IH _hoops_HSPP _hoops_IIGR _hoops_PRPP _hoops_RPP _hoops_SSIA _hoops_SPGA'_hoops_RA _hoops_GGR-_hoops_CCPRH.
			if ( _hoops_RGIGR == _hoops_ARIGR ) {
				glBeginQuery(GL_TIME_ELAPSED_EXT, _hoops_SSHAC);

				_hoops_RGIGR = _hoops_PRIGR;
			}
		}
	}

	void _hoops_PRHP()
	{
		HOGLData *_hoops_CSRGR = (HOGLData *)_hoops_ISS;
		if ( _hoops_RGIGR == _hoops_AGIGR ) {
			// _hoops_ACIPA _hoops_CGRH
			glFinish();

			// _hoops_SCPRH _hoops_SPPP
			_hoops_IGIGR = HI_What_Time();
		}
		else {
			// _hoops_HCPRH _hoops_CRAA. _hoops_ICPRH _hoops_CCAH _hoops_RACGH _hoops_IH _hoops_RSGR _hoops_IIGR _hoops_PRPP _hoops_RPP _hoops_SR _hoops_AIS _hoops_SPR.
			if ( _hoops_RGIGR == _hoops_PRIGR ) {
				glEndQuery(GL_TIME_ELAPSED_EXT);

				_hoops_RGIGR = _hoops_HRIGR;
			}
		}
	}

private:
	// _hoops_HCPRH _hoops_IIPRH
	GLuint _hoops_SSHAC;
};


/* _hoops_ASHGR _hoops_PSHGR */
local void _hoops_RSCSR (_hoops_APARR & _hoops_RRCI);
local int _hoops_RGSRC (HOGLData *_hoops_CSRGR);

#ifdef OSX_SYSTEM	
static void _hoops_GGIAC(H3DData *h3ddata, H3DRenderTarget *_hoops_SCSRR, H3DRenderTarget *_hoops_GSSRR)
{	
	HOGLData *_hoops_CSRGR = (HOGLData *) h3ddata;	
	_hoops_RGIAC *src = (_hoops_RGIAC *) _hoops_SCSRR;
	_hoops_RGIAC *_hoops_PCAP = (_hoops_RGIAC *) _hoops_GSSRR;		
	UNREFERENCED(_hoops_PCAP);
	
#if 0	
	
	if (!_hoops_CSRGR->_hoops_AGIAC)
		_hoops_CSRGR->_hoops_AGIAC = new HOGLFrameBufferObject(_hoops_CSRGR);
	if (!_hoops_CSRGR->_hoops_PGIAC)
		_hoops_CSRGR->_hoops_PGIAC = new HOGLFrameBufferObject(_hoops_CSRGR);
	
	GLint _hoops_HGIAC = GL_COLOR_ATTACHMENT0_EXT;
	
	_hoops_CSRGR->_hoops_AGIAC->_hoops_IGIAC(_hoops_HGIAC, src);
	
	if (_hoops_GSSRR) {
		ASSERT(src->_hoops_GSPP == _hoops_PCAP->_hoops_GSPP);
		_hoops_CSRGR->_hoops_PGIAC->_hoops_IGIAC(_hoops_HGIAC, _hoops_PCAP);
		glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, _hoops_CSRGR->_hoops_PGIAC->_hoops_CGIAC);
	}
	else
		glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, 0);
	
	glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, _hoops_CSRGR->_hoops_AGIAC->_hoops_CGIAC);	
	
#else	
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);	
	
#endif
	
	GLuint *buffer = &_hoops_CSRGR->_hoops_SGIAC;
	
	glGenTextures(1,buffer);		
	glBindTexture(GL_TEXTURE_2D, *buffer);
	
	int _hoops_GRIAC = src->_hoops_IRRP;
	int _hoops_RRIAC = src->_hoops_CRRP;	
	
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,_hoops_GRIAC,_hoops_RRIAC,0,GL_RGBA,GL_UNSIGNED_BYTE,0);	
	glCopyTexSubImage2D(GL_TEXTURE_2D,0,0,0,0,0,_hoops_GRIAC,_hoops_RRIAC);
	
	//	_hoops_ARIAC( _hoops_RPPGC, 3, _hoops_PRIAC, _hoops_HRIAC, _hoops_IRIAC, _hoops_CRIAC, _hoops_ASPA );	
	
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	
	glUseProgram(0);
	
	for ( int i = 0 ; i < 8 ; i++ )
	{
		glActiveTexture(GL_TEXTURE0+i);
		glDisable(GL_TEXTURE_2D);		
	}	
	
	glActiveTexture(GL_TEXTURE0);	
	glEnable(GL_TEXTURE_2D);		
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
	
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);	

	glPolygonMode(GL_FRONT, GL_FILL);	
	
	glMatrixMode (GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity ();
	
	glMatrixMode (GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity ();
	
	glMatrixMode (GL_TEXTURE);
	glPushMatrix ();
	glLoadIdentity ();	
	
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);	glVertex2f(-1, -1);
	glTexCoord2f(0, 1);	glVertex2f(-1, 1);
	glTexCoord2f(1, 1);	glVertex2f(1, 1);
	glTexCoord2f(1, 0);	glVertex2f(1, -1);
	glEnd();
	
	glFlush();	
	
	glMatrixMode (GL_TEXTURE);
	glPopMatrix ();
	
	glMatrixMode (GL_MODELVIEW);
	glPopMatrix ();
	
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();		
}
#endif


void _hoops_SRIAC(
	   H3DData					*h3ddata,
	   H3DRenderTarget			*_hoops_SCSRR,
	   H3DRenderTarget			*_hoops_GSSRR,
	   H3DTEXTUREFILTERTYPE		filter = H3DTEXF_NONE)
{
	HOGLData *_hoops_CSRGR = (HOGLData *) h3ddata;
	_hoops_RGIAC *src = (_hoops_RGIAC *) _hoops_SCSRR;
	_hoops_RGIAC *_hoops_PCAP = (_hoops_RGIAC *) _hoops_GSSRR;
	float *data = null;
	int _hoops_GRIAC = src->_hoops_IRRP;
	int _hoops_RRIAC = src->_hoops_CRRP;
	int _hoops_GAIAC = (_hoops_PCAP) ? _hoops_PCAP->_hoops_IRRP : _hoops_CSRGR->window_width;
	int _hoops_RAIAC = (_hoops_PCAP) ? _hoops_PCAP->_hoops_CRRP : _hoops_CSRGR->window_height;

	UNREFERENCED(_hoops_GAIAC);
	UNREFERENCED(_hoops_RAIAC);

	if (!_hoops_CSRGR->_hoops_AGIAC)
		_hoops_CSRGR->_hoops_AGIAC = new HOGLFrameBufferObject(_hoops_CSRGR);
	if (!_hoops_CSRGR->_hoops_PGIAC)
		_hoops_CSRGR->_hoops_PGIAC = new HOGLFrameBufferObject(_hoops_CSRGR);

	GLint _hoops_HGIAC = GL_COLOR_ATTACHMENT0_EXT;
	GLint format = GL_RGB;
	GLint internalformat = GL_RGB8;
	GLuint *buffer = &_hoops_CSRGR->_hoops_SGIAC;
	GLenum type = GL_UNSIGNED_BYTE;
	GLuint _hoops_AAIAC = 0;
	if (src->_hoops_GSPP == H3DFMT_D24S8) {
		_hoops_HGIAC = GL_DEPTH_ATTACHMENT_EXT;
		format = GL_DEPTH_COMPONENT;
		if (_hoops_CSRGR->_hoops_IGARR == 16)
		    internalformat = GL_DEPTH_COMPONENT16_ARB;
	    else
		    internalformat = GL_DEPTH_COMPONENT24_ARB;
		buffer = &_hoops_CSRGR->_hoops_PAIAC;
		type = GL_FLOAT;

		if (!_hoops_CSRGR->_hoops_SISGC)
			_hoops_RGSRC (_hoops_CSRGR);
		_hoops_AAIAC = _hoops_CSRGR->_hoops_SISGC;

		_hoops_RPAP (_hoops_CSRGR, false);
		ENSURE_DEPTH_MASK (_hoops_CSRGR, true);		
	}
	else {
		_hoops_RPAP (_hoops_CSRGR, true);
		ENSURE_DEPTH_MASK (_hoops_CSRGR, false);
	}
	_hoops_PISP (_hoops_CSRGR, false);


	// _hoops_IGIP 1: _hoops_IGPP _hoops_ASPA _hoops_HII _hoops_GGPGC _hoops_IS _hoops_HH
	// ================================================
	_hoops_CSRGR->_hoops_AGIAC->_hoops_IGIAC(_hoops_HGIAC, src);
	// _hoops_RPP _hoops_CCCH _hoops_HAIR, _hoops_HASIR _hoops_HCH _hoops_AI _hoops_PGGA _hoops_SSIA _hoops_GHCA _hoops_SHH _hoops_CSPR (_hoops_RHPH _hoops_HAARR, _hoops_AHI)
	if (src->_hoops_GSPP != H3DFMT_D24S8)	
		_hoops_CSRGR->_hoops_AGIAC->_hoops_IGIAC(GL_DEPTH_ATTACHMENT_EXT, 0);
	_hoops_CSRGR->_hoops_AGIAC->_hoops_HAIAC();

	glEnable(GL_TEXTURE_RECTANGLE_ARB);

	// _hoops_CGP _hoops_SR _hoops_HS _hoops_PCCP _hoops_APRS _hoops_IRHP _hoops_HH, _hoops_IRHH _hoops_RCRR _hoops_SCH'_hoops_GRI _hoops_RH _hoops_RPHR _hoops_IGIR
	if (*buffer) {
		int _hoops_IAIAC, _hoops_CAIAC;
		glGetTexLevelParameteriv(GL_TEXTURE_RECTANGLE_ARB, 0, GL_TEXTURE_WIDTH, &_hoops_IAIAC);
		glGetTexLevelParameteriv(GL_TEXTURE_RECTANGLE_ARB, 0, GL_TEXTURE_HEIGHT, &_hoops_CAIAC);
		if (_hoops_GRIAC != _hoops_IAIAC || _hoops_RRIAC != _hoops_CAIAC) {
			glDeleteTextures(1, buffer);
			*buffer = 0;
		}
	}
	if (!(*buffer)) {
		glGenTextures(1, buffer);
		glBindTexture(GL_TEXTURE_RECTANGLE_ARB, *buffer);
		_hoops_CSRGR->dc->_hoops_IGGI->_hoops_GSAC++;
		_hoops_CSRGR->dc->_hoops_IGGI->_hoops_RPRH++;
		glTexImage2D (GL_TEXTURE_RECTANGLE_ARB, 0, internalformat, _hoops_GRIAC, _hoops_RRIAC, 0,
			format, type, data);
		glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, filter);
		glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, *buffer);
	glCopyTexSubImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, 0, 0, 0, 0, _hoops_GRIAC, _hoops_RRIAC);


	// _hoops_IGIP 2: _hoops_GISP _hoops_GAGS _hoops_PCPI _hoops_CIAA _hoops_PASPR _hoops_GGPGC
	// ========================================================
	// _hoops_RHRP _hoops_SIGR, _hoops_HIS _hoops_IPS _hoops_ASPA _hoops_IS _hoops_HH _hoops_PPR _hoops_SRGS _hoops_IS _hoops_SHPR _hoops_IH _hoops_RGRR
	float _hoops_SAIAC = 2.0 * ((float)_hoops_GAIAC / _hoops_GRIAC);
	float _hoops_GPIAC = 2.0 * ((float)_hoops_RAIAC / _hoops_RRIAC);
	
	if (_hoops_PCAP) {
		_hoops_CSRGR->_hoops_PGIAC->_hoops_IGIAC(_hoops_HGIAC, _hoops_PCAP);
		if (src->_hoops_GSPP != H3DFMT_D24S8)	
			_hoops_CSRGR->_hoops_PGIAC->_hoops_IGIAC(GL_DEPTH_ATTACHMENT_EXT, 0);
		_hoops_CSRGR->_hoops_PGIAC->_hoops_HAIAC();
	}
	else
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	// _hoops_SGH _hoops_RPIHR-_hoops_API _hoops_SGIGR (_hoops_PAR _hoops_HCH _hoops_CCGSP _hoops_CI, _hoops_GAR _hoops_HAHH)
	glUseProgram(_hoops_AAIAC);

	if (_hoops_AAIAC) {
		int handle = glGetUniformLocation (_hoops_AAIAC, "depth_sampler");
		glUniform1i(handle, 0);
	}

	// _hoops_PGSA _hoops_RH _hoops_HH _hoops_CIAA _hoops_RH _hoops_RII _hoops_GGPGC
	glMatrixMode (GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity ();

	glMatrixMode (GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity ();

	glMatrixMode (GL_TEXTURE);
	glPushMatrix ();
	glLoadIdentity ();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);			glVertex2f(-1,			-1);
	glTexCoord2f(0, _hoops_RRIAC);		glVertex2f(-1,			-1+_hoops_GPIAC);
	glTexCoord2f(_hoops_GRIAC, _hoops_RRIAC);	glVertex2f(-1+_hoops_SAIAC,	-1+_hoops_GPIAC);
	glTexCoord2f(_hoops_GRIAC, 0);		glVertex2f(-1+_hoops_SAIAC,	-1);
	glEnd();

	glPopMatrix ();
	glMatrixMode (GL_MODELVIEW);
	glPopMatrix ();
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();

	glDisable(GL_TEXTURE_RECTANGLE_ARB);
	if (src->_hoops_GSPP == H3DFMT_D24S8)
		_hoops_RPAP (_hoops_CSRGR, true);

	if (_hoops_CSRGR->_hoops_CSC->_hoops_AGSA)
		_hoops_CSRGR->_hoops_CSC->_hoops_AGSA->_hoops_HHIH();

	_hoops_CSRGR->fbo->_hoops_HAIAC();
}

void _hoops_HGIP (
	   H3DData					*h3ddata,
	   H3DRenderTarget			*_hoops_SCSRR,
	   H3DRenderTarget			*_hoops_GSSRR,
	   H3DTEXTUREFILTERTYPE		filter,
	   bool						_hoops_RSSRR,
	   bool						_hoops_ASSRR)
{
	
#ifdef OSX_SYSTEM	
	_hoops_GGIAC(h3ddata,_hoops_SCSRR,_hoops_GSSRR);
	return;	
#endif
	
	HOGLData *_hoops_CSRGR = (HOGLData *) h3ddata;
	if (!glBlitFramebufferEXT) {
		_hoops_SRIAC(h3ddata, _hoops_SCSRR, _hoops_GSSRR);
		return;
	}

	H3DViewport _hoops_RPIAC = _hoops_CSRGR->_hoops_CSC->_hoops_CSAA;
	_hoops_CSRGR->fbo->_hoops_APIAC();

	_hoops_RGIAC *src = (_hoops_RGIAC *) _hoops_SCSRR;
	_hoops_RGIAC *_hoops_PCAP = (_hoops_RGIAC *) _hoops_GSSRR;
	int _hoops_GRIAC = src->_hoops_IRRP;
	int _hoops_RRIAC = src->_hoops_CRRP;
	int _hoops_GAIAC = _hoops_CSRGR->window_width;
	int _hoops_RAIAC = _hoops_CSRGR->window_height;

	// _hoops_PHAA _hoops_PPIAC _hoops_PRSAR _hoops_IS _hoops_GGPGC _hoops_GPRR
	GLint _hoops_HGIAC = GL_COLOR_ATTACHMENT0_EXT;
	GLint _hoops_HPIAC = GL_COLOR_BUFFER_BIT;
	if (src->_hoops_GSPP == H3DFMT_D24S8) {
		_hoops_HGIAC = GL_DEPTH_STENCIL_EXT;
		_hoops_HPIAC = GL_DEPTH_BUFFER_BIT;
	}

	_hoops_CSRGR->fbo->_hoops_IGIAC(_hoops_HGIAC, src);

	// _hoops_RAP _hoops_GH _hoops_PGSA _hoops_IPIAC
	if (_hoops_GSSRR) {
		//_hoops_AGHR(_hoops_CPIAC->_hoops_CRHAH == _hoops_SISH->_hoops_CRHAH);	// _hoops_SR _hoops_CGH _hoops_IRHH _hoops_RCRR _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_IRCC _hoops_IS _hoops_CCGSP _hoops_HAIR <-> _hoops_HCH
		_hoops_GAIAC = _hoops_PCAP->_hoops_IRRP;
		_hoops_RAIAC = _hoops_PCAP->_hoops_CRRP;

		if (!_hoops_CSRGR->_hoops_AGIAC)
			_hoops_CSRGR->_hoops_AGIAC = new HOGLFrameBufferObject(_hoops_CSRGR);
		_hoops_CSRGR->_hoops_AGIAC->_hoops_IGIAC(_hoops_HGIAC, _hoops_PCAP);
		glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, _hoops_CSRGR->_hoops_AGIAC->_hoops_CGIAC);
		glDrawBuffer(_hoops_HGIAC);
	}
	else {
		glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, 0);
	}

	// _hoops_RAP _hoops_GH _hoops_IRIGR _hoops_IPIAC
	glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, _hoops_CSRGR->fbo->_hoops_CGIAC);
	glReadBuffer(_hoops_HGIAC);

	// _hoops_RASRH _hoops_HII _hoops_IRIGR _hoops_IPIAC -> _hoops_PGSA _hoops_IPIAC
	if (_hoops_ASSRR) {
		glBlitFramebufferEXT(
			0, _hoops_RRIAC, _hoops_GRIAC, 0,
			0, 0, _hoops_GAIAC, _hoops_RAIAC,
			_hoops_HPIAC, _hoops_SPIAC(filter));
	}
	else {
		glBlitFramebufferEXT(
			0, 0, _hoops_GRIAC, _hoops_RRIAC,
			0, 0, _hoops_GAIAC, _hoops_RAIAC,
			_hoops_HPIAC, _hoops_SPIAC(filter));
	}

	if (_hoops_RSSRR) {
		GLboolean _hoops_GHIAC[4];
		glGetBooleanv(GL_COLOR_WRITEMASK, _hoops_GHIAC);
		glColorMask(false,false,false,true);
		glClear(GL_COLOR_BUFFER_BIT);
		glColorMask(_hoops_GHIAC[0],_hoops_GHIAC[1],_hoops_GHIAC[2],_hoops_GHIAC[3]);
	}

	// _hoops_SP _hoops_GH _hoops_HCH _hoops_SRHR _hoops_AAIP (_hoops_PAH _hoops_GGHC _hoops_HCH _hoops_ICH _hoops_IS _hoops_RRS _hoops_RIGRP _hoops_PIRAI _hoops_HCSS _hoops_IH _hoops_HHH _hoops_SCPC)
	if (src->_hoops_GSPP == H3DFMT_D24S8) {
		if (_hoops_CSRGR->_hoops_AGIAC)
			_hoops_CSRGR->_hoops_AGIAC->_hoops_IGIAC(_hoops_HGIAC, 0);
	}

	bool result = false;
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _hoops_CSRGR->fbo->_hoops_CGIAC);
	_hoops_CSRGR->fbo->_hoops_RHIAC();
	result = _hoops_CSRGR->fbo->_hoops_HAIAC();

	if (result)
		_hoops_HHRS(_hoops_CSRGR, _hoops_RPIAC.X, _hoops_RPIAC.Y, _hoops_RPIAC.Width, _hoops_RPIAC.Height);
}



/*
 * _hoops_PGAA: _hoops_RAP _hoops_RH _hoops_APRAR _hoops_RIAP _hoops_PIAP.
 */
void _hoops_AHIAC::_hoops_GPAP (
		H3DRenderTarget		*_hoops_ISCRR, 
		H3DRenderTarget		*_hoops_AASP,
		H3DRenderTarget		*_hoops_CSCRR, 
		H3DRenderTarget		*_hoops_SSCRR, 
		H3DRenderTarget		*_hoops_GGSRR)
{
	HOGLData *_hoops_CSRGR = _hoops_PHIAC;

	if (_hoops_CSRGR->fbo == 0)
		_hoops_CSRGR->fbo = new HOGLFrameBufferObject(_hoops_CSRGR);

	if (_hoops_ISCRR || _hoops_AASP) {
		_hoops_CSRGR->fbo->_hoops_IGIAC(GL_COLOR_ATTACHMENT0_EXT, _hoops_ISCRR);

		//_hoops_RPP (_hoops_RPSP)
		_hoops_CSRGR->fbo->_hoops_IGIAC(GL_DEPTH_STENCIL_EXT, _hoops_AASP);

		if ( _hoops_CSRGR->_hoops_GRAP > 1 )
			_hoops_CSRGR->fbo->_hoops_IGIAC(GL_COLOR_ATTACHMENT1_EXT, _hoops_CSCRR);
		else {
			ASSERT(_hoops_CSCRR == 0);
		}

		if ( _hoops_CSRGR->_hoops_GRAP > 2 )
			_hoops_CSRGR->fbo->_hoops_IGIAC(GL_COLOR_ATTACHMENT2_EXT, _hoops_SSCRR);
		else {
			ASSERT(_hoops_SSCRR == 0);
		}

		if ( _hoops_CSRGR->_hoops_GRAP > 3 )
			_hoops_CSRGR->fbo->_hoops_IGIAC(GL_COLOR_ATTACHMENT3_EXT, _hoops_GGSRR);
		else {
			ASSERT(_hoops_GGSRR == 0);
		}

		_hoops_CSRGR->fbo->_hoops_HAIAC();

		// _hoops_RAP _hoops_PCARH _hoops_RIP _hoops_IIHA _hoops_GPP _hoops_CISI _hoops_SAAP.
		_hoops_CSRGR->_hoops_IHP = false;
		if ( _hoops_CSRGR->_hoops_CRAP == _hoops_AHRS ) {
			// _hoops_GRSH _hoops_AHSC _hoops_HRGR _hoops_RH _hoops_CCAH _hoops_SAAP, _hoops_HCPC. _hoops_RH _hoops_ASGH _hoops_SPR.
			if ( _hoops_CSRGR->fbo->_hoops_HHIAC[0]->_hoops_IRRP == _hoops_CSRGR->window_width * _hoops_CSRGR->_hoops_HSAA &&
				 _hoops_CSRGR->fbo->_hoops_HHIAC[0]->_hoops_CRRP == _hoops_CSRGR->window_height * _hoops_CSRGR->_hoops_ISAA ) {
				 // _hoops_HR _hoops_RGR _hoops_HRGR _hoops_PCCP _hoops_ICPP _hoops_SAAP _hoops_PPR _hoops_AGSGR _hoops_GPP.
				 _hoops_CSRGR->_hoops_IHP = true;
			}
		}

	}
	else
		_hoops_IHIAC(_hoops_CSRGR, 0);

	// _hoops_HRHI _hoops_ISCP _hoops_PRIA _hoops_IIGR _hoops_RH _hoops_ICIH _hoops_IS _hoops_PSSP _hoops_RH _hoops_CCAH _hoops_SPR.
	int _hoops_CSAA[4];
	float _hoops_HHAAP[2];
	glGetIntegerv(GL_VIEWPORT, _hoops_CSAA);
	glGetFloatv(GL_DEPTH_RANGE, _hoops_HHAAP);

	if ( _hoops_CSRGR->_hoops_IHP ) {
		// _hoops_CAAA _hoops_ICIH _hoops_ISSC _hoops_IS _hoops_RSRA-_hoops_ISAR _hoops_RPRGR _hoops_PCRR.
		_hoops_CSAA[0] /= _hoops_CSRGR->_hoops_HSAA;
		_hoops_CSAA[1] /= _hoops_CSRGR->_hoops_ISAA;
		_hoops_CSAA[2] /= _hoops_CSRGR->_hoops_HSAA;
		_hoops_CSAA[3] /= _hoops_CSRGR->_hoops_ISAA;
	}

	_hoops_CSRGR->_hoops_CSC->_hoops_CSAA.X = _hoops_CSAA[0];
	_hoops_CSRGR->_hoops_CSC->_hoops_CSAA.Y = _hoops_CSAA[1];
	_hoops_CSRGR->_hoops_CSC->_hoops_CSAA.Width = _hoops_CSAA[2];
	_hoops_CSRGR->_hoops_CSC->_hoops_CSAA.Height = _hoops_CSAA[3];
	_hoops_CSRGR->_hoops_CSC->_hoops_CSAA.MinZ = _hoops_HHAAP[0];
	_hoops_CSRGR->_hoops_CSC->_hoops_CSAA.MaxZ = _hoops_HHAAP[1];
}

bool _hoops_AHIAC::_hoops_PHCS (H3DRenderTarget *_hoops_ISCRR, H3DRenderTarget *_hoops_AASP, H3DRenderTarget *_hoops_CSCRR, H3DRenderTarget *_hoops_SSCRR, H3DRenderTarget *_hoops_GGSRR ) {
	bool result;
	_hoops_PPRS _hoops_PGRGR;
	_hoops_IPRS(&_hoops_PGRGR);
	
	_hoops_PHIAC->fbo->_hoops_IGIAC(GL_COLOR_ATTACHMENT0_EXT, _hoops_ISCRR);
	_hoops_PHIAC->fbo->_hoops_IGIAC(GL_DEPTH_STENCIL_EXT, _hoops_AASP);
	if ( _hoops_PHIAC->_hoops_GRAP > 1 )
		_hoops_PHIAC->fbo->_hoops_IGIAC(GL_COLOR_ATTACHMENT1_EXT, _hoops_CSCRR);
	if ( _hoops_PHIAC->_hoops_GRAP > 2 )
		_hoops_PHIAC->fbo->_hoops_IGIAC(GL_COLOR_ATTACHMENT2_EXT, _hoops_SSCRR);
	if ( _hoops_PHIAC->_hoops_GRAP > 3 )
		_hoops_PHIAC->fbo->_hoops_IGIAC(GL_COLOR_ATTACHMENT3_EXT, _hoops_GGSRR);
	result = _hoops_PHIAC->fbo->_hoops_HAIAC(false);

	_hoops_CHRS(&_hoops_PGRGR);
	return result;
};

/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_GIRS
*****************************************************************************
*****************************************************************************/

/*
 * _hoops_PGAA
 */
void _hoops_AHIAC::_hoops_GHIP(
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
	HOGLData *_hoops_CSRGR = (HOGLData *) h3ddata;
	_hoops_HPHH (h3ddata, false);

	//_hoops_ACAC _hoops_PCAC _hoops_HPPA _hoops_IPPA _hoops_HIHP _hoops_CGPR _hoops_HIHP _hoops_SHPH
	h3ddata->_hoops_HCAC = _hoops_CCC;
	h3ddata->_hoops_ICAC = _hoops_CCC;

	//_hoops_CCAC _hoops_SCAC
	H3DVertexFormat _hoops_PPCP(H3DVF_PT_TEX);
	H3DVertexBuffer & _hoops_PAIH = h3ddata->_hoops_CP;
	H3DVertexBufferCache *_hoops_HACP;
	H3DShaderID id;
	H3DShader *_hoops_RSR;

	// _hoops_RASR
	
	//_hoops_ARSRR
	id._hoops_AHRAR();
	_hoops_RSR = h3ddata->_hoops_IP->Lookup (id); 
	if (!_hoops_RSR) {
		_hoops_RSR = h3ddata->_hoops_GSCR->_hoops_ICCRR(id);
		if (!_hoops_RSR->Create(h3ddata)) {
			return;
		}
		h3ddata->_hoops_IP->Insert (id, _hoops_RSR); 
	}
	if (h3ddata->_hoops_CSC->_hoops_AGSA != _hoops_RSR) {
		_hoops_RSR->_hoops_HHIH();
		h3ddata->_hoops_CSC->_hoops_AGSA = _hoops_RSR;
	}
	_hoops_RSR->_hoops_GGIR();

	//_hoops_SRIRH
	// _hoops_GRSH _hoops_AHSC _hoops_HRGR _hoops_RH _hoops_ICIH?
	//_hoops_SCSH _hoops_ICIH[4];
	float _hoops_HHAAP[2];

	//_hoops_CHIAC(_hoops_SHIAC, _hoops_ICIH);
	glGetFloatv(GL_DEPTH_RANGE, _hoops_HHAAP);

	//_hoops_SCSH _hoops_GIIAC = _hoops_ICIH[2];
	//_hoops_SCSH _hoops_RIIAC = _hoops_ICIH[3];
	int window_width = _hoops_CSRGR->window_width;
	int window_height = _hoops_CSRGR->window_height;
	float _hoops_CGSAA = _hoops_HHAAP[1];

	_hoops_PPHH(h3ddata, 0, 0, window_width, window_height);

	// _hoops_SIIR _hoops_HIHP _hoops_HII _hoops_ASPA
	float matrix[16];
	matrix[0] = (GLfloat) (2.0 / window_width);
	matrix[1] = (GLfloat) 0;
	matrix[2] = (GLfloat) 0;
	matrix[3] = (GLfloat) 0;
	matrix[4] = (GLfloat) 0;
	matrix[5] = (GLfloat) (2.0 / window_height);
	matrix[6] = (GLfloat) 0;
	matrix[7] = (GLfloat) 0;
	matrix[8] = (GLfloat) 0;
	matrix[9] = (GLfloat) 0;
	matrix[10] = (GLfloat) (1.0 / _hoops_CGSAA);
	matrix[11] = (GLfloat) 0;
	matrix[12] = (GLfloat) - 1;
	matrix[13] = (GLfloat) - 1;
	matrix[14] = (GLfloat) 0;
	matrix[15] = (GLfloat) 1;
	_hoops_RSR->_hoops_SHGA((float *) &matrix[0]);


	_hoops_ISC const _hoops_CRIRH = { 255, 255, 255, 255 };
	_hoops_RSR->_hoops_GIHR(&_hoops_CRIRH);

	_hoops_PISP (h3ddata, false);
	_hoops_RPAP (h3ddata, true);
	_hoops_RHSA (h3ddata, H3DCULL_NONE);
	ENSURE_DEPTH_MASK (h3ddata, false);
	_hoops_RPIH(h3ddata, _hoops_PPCP, _hoops_HACP);
	
	// _hoops_PHIR _hoops_GGR _hoops_RSSA
	if (_hoops_HACP->Lock(4, &_hoops_PAIH)) {
		_hoops_PAIH._hoops_AHCP(x,y,0);
		_hoops_PAIH._hoops_IICP(_hoops_ACCRR,_hoops_ISPI,0);
		_hoops_PAIH._hoops_CPPH();
		_hoops_PAIH._hoops_AHCP(x+width,y,0);
		_hoops_PAIH._hoops_IICP(_hoops_PCCRR,_hoops_ISPI,0);
		_hoops_PAIH._hoops_CPPH();
		_hoops_PAIH._hoops_AHCP(x,y+height,0);
		_hoops_PAIH._hoops_IICP(_hoops_ACCRR,_hoops_CSPI,0);
		_hoops_PAIH._hoops_CPPH();
		_hoops_PAIH._hoops_AHCP(x+width,y+height,0);
		_hoops_PAIH._hoops_IICP(_hoops_PCCRR,_hoops_CSPI,0);
		_hoops_PAIH._hoops_CPPH();
		_hoops_HACP->Unlock();
	}


	// _hoops_SIIR _hoops_PPSR _hoops_RHRP
	_hoops_SCCR(_hoops_CSRGR, 0, texture);
	_hoops_GPIRH(h3ddata, 0, H3DTEXF_POINT);
	_hoops_RPIRH(h3ddata, 0, H3DTEXF_POINT);
	ENSURE_TEXTURE_WRAP_S(h3ddata, 0, H3DTADDRESS_CLAMP);
	_hoops_SAIRH(h3ddata, 0, H3DTADDRESS_CLAMP);


	// _hoops_GISP _hoops_RH _hoops_ARRGR
	_hoops_HACP->_hoops_CHSA(h3ddata, H3DPT_TRIANGLESTRIP, 2);

	// _hoops_ICSS _hoops_HH - _hoops_SAPIA _hoops_PAR _hoops_SR _hoops_PAH'_hoops_RA _hoops_SRGS _hoops_IS _hoops_SCH _hoops_SPS _hoops_GHIR
	_hoops_ASRP(_hoops_CSRGR, 0);

	// _hoops_SP _hoops_GH
	ENSURE_DEPTH_MASK (h3ddata, true);
}

/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_AIIAC _hoops_PISRR
*****************************************************************************
*****************************************************************************/
_hoops_PIIAC::_hoops_PIIAC(const H3DShaderID& id) : 
	H3DShader(id)
{
	// _hoops_ASC _hoops_GA'_hoops_RA _hoops_HS _hoops_PSC
	ZERO_STRUCT(&_hoops_HSC, _hoops_ISC);

	_hoops_HCC = true;
}
_hoops_PIIAC::~_hoops_PIIAC()
{
	HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
	UNREFERENCED(_hoops_CSRGR);

	glDetachShader(_hoops_HIIAC, _hoops_AGHRH);
	glDetachShader(_hoops_HIIAC, _hoops_PGHRH);
	glDeleteShader(_hoops_AGHRH);
	glDeleteShader(_hoops_PGHRH);

	glDeleteProgram(_hoops_HIIAC);
}


local void _hoops_IIIAC(const char *error, const char *filename = null)
{
	UNREFERENCED(filename);

	if (_hoops_SSGR(error) == 0)
		return;

#ifdef _DEBUG
	// _hoops_SRHRH _hoops_CHR _hoops_GGR _hoops_GAHRH _hoops_RPCC _hoops_IH _hoops_RAHRH _hoops_AAHRH - _hoops_HSPAA _hoops_IS _hoops_HISRA _hoops_GGSR
	char _hoops_CIIAC[4096];
	if (filename) {
		sprintf(_hoops_CIIAC, "OpenGL2 reports errors in\n %s: \n", filename);
		OutputDebugString(_hoops_CIIAC);
	}
	else
		OutputDebugString("OpenGL2 reports errors: \n");
	OutputDebugStringA(error);
#endif // _hoops_PAHRH

	_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, 
		Sprintf_S (null, "error reported by opengl:\n%S", error));
}

bool _hoops_PIIAC::Create(H3DData *h3ddata, const char *_hoops_IASRR)
{
	HOGLData *_hoops_CSRGR = (HOGLData *) h3ddata;
	_hoops_ISS = h3ddata;
	UNREFERENCED(_hoops_CSRGR);

	int len;
	char log[4096];
	char _hoops_GIAAR[4096];
	int status = 0;
	char *_hoops_CA, *_hoops_GP, *ptr, *_hoops_CHHRH, *_hoops_SHHRH;
	GLuint _hoops_GHHRH = 0, _hoops_SPHRH = 0, _hoops_SIIAC = 0;
	int _hoops_GIHRH, _hoops_RIHRH;
	bool _hoops_GCIAC = false, _hoops_RCIAC = false, _hoops_ACIAC = false;

	UNREFERENCED(ptr);
	UNREFERENCED(_hoops_GIAAR);
	UNREFERENCED(_hoops_GIHRH);
	UNREFERENCED(_hoops_RIHRH);


	// _hoops_ARGH _hoops_RPP _hoops_SR _hoops_HS _hoops_IRS _hoops_IPSP _hoops_CI
	if (_hoops_PCC._hoops_RIHR()) {
		_hoops_PCC._hoops_IHRAR((POINTER_SIZED_INT *) &_hoops_SPHRH, (POINTER_SIZED_INT  *) &_hoops_GHHRH);

		if (_hoops_SPHRH && _hoops_GHHRH) {
			_hoops_SIIAC = glCreateProgram();
			glAttachShader(_hoops_SIIAC, _hoops_SPHRH);
			glAttachShader(_hoops_SIIAC, _hoops_GHHRH);
			glLinkProgram(_hoops_SIIAC);

			//_hoops_SPPPR _hoops_AGGAR _hoops_IR?
			glGetProgramiv(_hoops_SIIAC, GL_LINK_STATUS, &status);
			_hoops_ACIAC = (status == GL_TRUE) ? true : false;
		}

		if (_hoops_ACIAC) {
			// _hoops_SAH _hoops_CPS
			glUseProgram(_hoops_SIIAC);
			h3ddata->_hoops_CSC->_hoops_AGSA = this;

			_hoops_AGHRH = _hoops_SPHRH;
			_hoops_PGHRH = _hoops_GHHRH;
			_hoops_HIIAC = _hoops_SIIAC;
			_hoops_PCIAC();
			status = true;
			return true;
		}
		else {
			glDeleteProgram(_hoops_SIIAC);
			return false;
		}
	}

	_hoops_GP = h3ddata->_hoops_GP;
	_hoops_CA = h3ddata->_hoops_CA;
	_hoops_CHHRH = &_hoops_GP[_hoops_SA-1];
	_hoops_SHHRH = &_hoops_CA[_hoops_SA-1];

	const char *_hoops_HCIAC = _hoops_CA;
	const char *_hoops_ICIAC = _hoops_GP;

	_hoops_SPHRH = glCreateShader(GL_VERTEX_SHADER);
	_hoops_GHHRH = glCreateShader(GL_FRAGMENT_SHADER);

	//_hoops_CARR _hoops_CCPGC _hoops_CSPP
	int _hoops_CCIAC = _hoops_CSRGR->glsl_version;
	char glsl_version[40];
	if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_GLSL4_SAMPLER_CUBE) &&
		(_hoops_PCC._hoops_GPAR() || _hoops_PCC._hoops_RSRR()) && 
		_hoops_CCIAC == 140) {
			_hoops_CCIAC = 130;
	}
	sprintf(glsl_version, "#version %d\n#define GLSL_%d\n\n", _hoops_CCIAC, _hoops_CCIAC);

	// _hoops_HCHRH _hoops_HAPR - _hoops_SGHHR _hoops_IS _hoops_IIPGA _hoops_CGPR _hoops_HSSI _hoops_ISHS
	while (_hoops_GCIAC == false || _hoops_RCIAC == false || _hoops_ACIAC == false)
	{
		/* 
		 * _hoops_IISR _hoops_GPHA _hoops_CI _hoops_HCGP _hoops_RRGR
		 */
		ptr = _hoops_CA;
		_hoops_PAHR (_hoops_PCC, true, _hoops_GIAAR);
		
		if ((ptr = _hoops_SCIAC ("ogl2_header.hlsl", _hoops_AHGIH, ptr, _hoops_SHHRH, glsl_version, _hoops_GCGR)) == null)
			goto release;
		if ((ptr = _hoops_HRRR (_hoops_PCC, ptr, _hoops_SHHRH, _hoops_PCC._hoops_RIRAR(), _hoops_GCGR)) == null)
			goto release;
		if ((ptr = _hoops_RHGR ("h3d_macros.hlsl", _hoops_RSHRH, ptr, _hoops_SHHRH, _hoops_GCGR)) == null)
			goto release;
		if ((ptr = _hoops_AIGR ("h3d_material.hlsl", _hoops_ASHRH, ptr, _hoops_SHHRH)) == null)
			goto release;
		if ((ptr = _hoops_AIGR ("h3d_common.hlsl", _hoops_PSHRH, ptr, _hoops_SHHRH)) == null)
			goto release;
		if ((ptr = _hoops_AIGR ("h3d_vertex.hlsl", _hoops_HSHRH, ptr, _hoops_SHHRH)) == null)
			goto release;
		if ((ptr = _hoops_AIGR ("ogl2_common.hlsl", _hoops_RHGIH, ptr, _hoops_SHHRH)) == null)
			goto release;
		if ((ptr = _hoops_AIGR ("ogl2_vertex.hlsl", _hoops_GIGIH, ptr, _hoops_SHHRH)) == null)
			goto release;
		_hoops_GIHRH = ptr - _hoops_CA;
		if (!_hoops_GAGR (_hoops_CA, &_hoops_GIHRH))
			goto release;
		if (_hoops_GIAAR[0] != '\0') {
			_hoops_IHHR (_hoops_GIAAR, _hoops_CA);
		}

		/* 
		 * _hoops_IISR _hoops_AIR _hoops_CI _hoops_HCGP _hoops_RRGR
		 */
		ptr = _hoops_GP;
		_hoops_PAHR (_hoops_PCC, false, _hoops_GIAAR);
		
		if ((ptr = _hoops_SCIAC ("ogl2_header.hlsl", _hoops_AHGIH, ptr, _hoops_CHHRH, glsl_version, _hoops_RPRR)) == null)
			goto release;
		if ((ptr = _hoops_HRRR (_hoops_PCC, ptr, _hoops_CHHRH, _hoops_PCC._hoops_RIRAR(), _hoops_RPRR)) == null)
			goto release;
		if ((ptr = _hoops_RHGR ("h3d_macros.hlsl", _hoops_RSHRH, ptr, _hoops_CHHRH, _hoops_RPRR)) == null)
			goto release;
		if ((ptr = _hoops_AIGR ("h3d_material.hlsl", _hoops_ASHRH, ptr, _hoops_CHHRH)) == null)
			goto release;
		if (_hoops_IASRR != null) {
			const int length = _hoops_SSGR(_hoops_IASRR) + 2;
			if ( length > (_hoops_CHHRH - ptr) )
				goto release;
			sprintf(ptr, "\n%s\n", _hoops_IASRR);
			ptr += length;
		}
		if ((ptr = _hoops_AIGR ("h3d_common.hlsl", _hoops_PSHRH, ptr, _hoops_CHHRH)) == null)
			goto release;
		if ((ptr = _hoops_AIGR ("h3d_pixel.hlsl", _hoops_CSHRH, ptr, _hoops_CHHRH)) == null)
			goto release;
		if ((ptr = _hoops_AIGR ("ogl2_common.hlsl", _hoops_RHGIH, ptr, _hoops_CHHRH)) == null)
			goto release;
		if ((ptr = _hoops_AIGR ("ogl2_pixel.hlsl", _hoops_PHGIH, ptr, _hoops_CHHRH)) == null)
			goto release;
		_hoops_RIHRH = ptr - _hoops_GP;
		if (!_hoops_GAGR (_hoops_GP, &_hoops_RIHRH))
			goto release;
		if (_hoops_GIAAR[0] != '\0') {
			_hoops_IHHR (_hoops_GIAAR, _hoops_GP);
		}

		glShaderSource(_hoops_SPHRH, 1, &_hoops_HCIAC, null);
		glShaderSource(_hoops_GHHRH, 1, &_hoops_ICIAC, null);

		glCompileShader(_hoops_SPHRH);
		glCompileShader(_hoops_GHHRH);

		glGetShaderiv(_hoops_SPHRH, GL_COMPILE_STATUS, &status);
		_hoops_GCIAC = (status == GL_TRUE) ? true : false;

		glGetShaderiv(_hoops_GHHRH, GL_COMPILE_STATUS, &status);
		_hoops_RCIAC = (status == GL_TRUE) ? true : false;

#ifdef _DEBUG
//#_hoops_PPIP _hoops_GSIAC
#endif

		//_hoops_CI _hoops_HSSI _hoops_IR?
#ifndef _hoops_RSIAC
		if (!_hoops_GCIAC) 
#endif
		{
			//_hoops_ASIAC(_hoops_PSIAC, _hoops_HSIAC, &_hoops_GHIIA);		//_hoops_HGCR _hoops_RH _hoops_SPCC _hoops_IIGR _hoops_RH _hoops_SIHC _hoops_ISIAC; 4096 _hoops_HRGR _hoops_ICGSI _hoops_RAPR
			glGetShaderInfoLog(_hoops_SPHRH, sizeof(log), &len, log);
			char *_hoops_CSIAC = strstr(_hoops_GIAAR, "ps_dump");
			if (_hoops_CSIAC)
				*_hoops_CSIAC = 'v';

#ifdef _hoops_RSIAC
			if (strstr(log, "WARNING") || strstr(log, "ERROR"))
#endif
				_hoops_IIIAC(log, _hoops_GIAAR);
		}

#ifndef _hoops_RSIAC
		if (!_hoops_RCIAC)
#endif
		{
			char *_hoops_CSIAC = strstr(_hoops_GIAAR, "vs_dump");
			if (_hoops_CSIAC)
				*_hoops_CSIAC = 'p';
			glGetShaderInfoLog(_hoops_GHHRH, sizeof(log), &len, log);

#ifdef _hoops_RSIAC
			if (strstr(log, "WARNING") || strstr(log, "ERROR"))
#endif
				_hoops_IIIAC(log, _hoops_GIAAR);
		}

		if (_hoops_GCIAC && _hoops_RCIAC) {
			_hoops_SIIAC = glCreateProgram();
			glAttachShader(_hoops_SIIAC, _hoops_SPHRH);
			glAttachShader(_hoops_SIIAC, _hoops_GHHRH);

			if (glBindFragDataLocationEXT) {
				glBindFragDataLocationEXT(_hoops_SIIAC, 0, "final_color");
				glBindFragDataLocationEXT(_hoops_SIIAC, 1, "final_depth");
			}
			else
				ASSERT(_hoops_CSRGR->glsl_version == 120);

			glLinkProgram(_hoops_SIIAC);

			//_hoops_SPPPR _hoops_AGGAR _hoops_IR?
			glGetProgramiv(_hoops_SIIAC, GL_LINK_STATUS, &status);
			_hoops_ACIAC = (status == GL_TRUE) ? true : false;

#ifndef _hoops_RSIAC
			if (!_hoops_ACIAC) 
#endif 
			{
				glGetProgramInfoLog(_hoops_SIIAC, sizeof(log), &len, log);

#ifdef _hoops_RSIAC
				if (strstr(log, "WARNING") || strstr(log, "ERROR"))
#endif
					_hoops_IIIAC(log);
			}		
		}

		// _hoops_CGP _hoops_GIPR _hoops_GGIRH _hoops_SCSS, _hoops_SR'_hoops_ASAR _hoops_CPHR
		if (_hoops_GCIAC && _hoops_RCIAC && _hoops_ACIAC)
		{
			break;
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
			}
			else {
				// _hoops_HGIRH.
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "OpenGL2 driver could not compile shader - too complex" );
				break;
			}
		}

	}


release:

	// _hoops_RAPRH _hoops_RH _hoops_RHPP _hoops_IGIRH _hoops_IS _hoops_ARPR _hoops_RH _hoops_CI?
	if (_hoops_GHHRH && _hoops_SPHRH)
	{
		// _hoops_SAH _hoops_CPS
		_hoops_HIIAC = _hoops_SIIAC;
		_hoops_AGHRH = _hoops_SPHRH;
		_hoops_PGHRH = _hoops_GHHRH;
		status = true;
	}
	else
	{
		// _hoops_PPGGR _hoops_CPS
		if (_hoops_SIIAC) {
			glDetachShader(_hoops_SIIAC, _hoops_SPHRH);
			glDetachShader(_hoops_SIIAC, _hoops_GHHRH);
			glDeleteProgram(_hoops_SIIAC);
		}

		if (_hoops_SPHRH)
			glDeleteShader(_hoops_SPHRH);
        if (_hoops_GHHRH)
			glDeleteShader(_hoops_GHHRH);
	
    }

	// _hoops_SAH _hoops_IGRI _hoops_AHPHA
	_hoops_PCIAC();

	return (status == GL_TRUE);
};

char alter *_hoops_PIIAC::_hoops_SCIAC (
		const char *filename,
		const char *_hoops_ICPR,
		char alter *ptr,
		char const *end,
		const char *glsl_version,
		_hoops_AHGR type)
{
	strcpy (ptr, glsl_version); 
	ptr += _hoops_SSGR(ptr);

	if (type == _hoops_RPRR) {
		strcat (ptr, "#define OPENGL_PIXEL_SHADER\n\n");
		ptr += _hoops_SSGR(ptr);
	}

	if (_hoops_PCC._hoops_GIRAR()) {
		strcat (ptr, "#define FLAT_SHADING \n");
		ptr += _hoops_SSGR (ptr);
	}

	ptr = _hoops_AIGR (filename, _hoops_ICPR, ptr, end);
	return ptr;
}

bool _hoops_PIIAC::_hoops_HHIH()
{
	HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
	UNREFERENCED(_hoops_CSRGR);

	glUseProgram(_hoops_HIIAC);
	_hoops_ICC = _hoops_SCC = _hoops_GSC = _hoops_RSC = 0;

	SET_MEMORY(_hoops_ISS->_hoops_SCRRR, sizeof(_hoops_ISS->_hoops_SCRRR), false);
	return true;
};


// _hoops_SSIAC _hoops_GGCAC
void _hoops_PIIAC::_hoops_GGIR (bool _hoops_AIAAR)
{
	if (_hoops_PCC._hoops_RIHR())
		return;

	HOGLData *_hoops_CSRGR = (HOGLData *)_hoops_ISS;
	int _hoops_RARR = 0;
	int _hoops_ASRR = 0;
	int _hoops_RGCAC = _hoops_PCC._hoops_HGC();
	int _hoops_AGCAC = _hoops_PCC._hoops_CGC();
	int _hoops_PGCAC = _hoops_PCC._hoops_IRP();

	if (_hoops_PCC._hoops_HGC() || _hoops_PCC._hoops_CGC() ||
		_hoops_PCC._hoops_ISI() || _hoops_PCC._hoops_CSI()) {
		int handle = (H3D_Shader_Handle) glGetUniformLocation (_hoops_HIIAC, "FrontDiffuseTextureEnable");
		glUniform1i(handle, _hoops_AIAAR ? 0 : 1);
	}

	if (_hoops_PCC._hoops_GSI()) {
		if (_hoops_PCC._hoops_ISI() || _hoops_PCC._hoops_CSI()) {
			_hoops_PCC._hoops_SII(_hoops_PIRR, 0, null, null, &_hoops_RARR);
			_hoops_ICCR(H3D_PSConstant_Table, _hoops_SGAAR, null, "LineToolsSampler", _hoops_RARR);
		}
	}

	if (_hoops_PCC._hoops_SCI()) {
		_hoops_PCC._hoops_SII(_hoops_IAAR, 0, null, null, &_hoops_RARR);
		if (_hoops_RARR != -1) {
			_hoops_ICCR(H3D_PSConstant_Table, _hoops_GRAAR, null, "IndexSampler", _hoops_RARR);
		}
	}

	if (_hoops_PCC._hoops_SSI()) {
		_hoops_PCC._hoops_SII(_hoops_HIRR, 0, null, null, &_hoops_RARR);
		if (_hoops_RARR != -1) {
			_hoops_ICCR(H3D_PSConstant_Table, _hoops_CGAAR, null, "LinePatternSampler", _hoops_RARR);
		}
	}

	for (_hoops_ASRR = 0; _hoops_ASRR < _hoops_PGCAC; _hoops_ASRR++) {
		_hoops_PCC._hoops_SII(_hoops_GHPR, _hoops_ASRR, null, null, &_hoops_RARR);
		if (_hoops_RARR != -1) {
			sprintf(_hoops_ISS->shader_handle, "ShadowMapTexture%d", _hoops_ASRR);
			_hoops_ICCR(H3D_PSConstant_Table, _hoops_CCCR + _hoops_ASRR, null, _hoops_ISS->shader_handle, _hoops_RARR);
		}
	}

	for (_hoops_ASRR = 0; _hoops_ASRR < _hoops_RGCAC; _hoops_ASRR++) {
		_hoops_PCC._hoops_SII(_hoops_PSRR, _hoops_ASRR, null, null, &_hoops_RARR);
		if (_hoops_RARR != -1) {
			sprintf(_hoops_ISS->shader_handle, "DiffuseSampler%d", _hoops_ASRR);
			_hoops_ICCR(H3D_PSConstant_Table, _hoops_GGAAR + _hoops_ASRR, null, _hoops_ISS->shader_handle, _hoops_RARR);
		}
	}

	for (_hoops_ASRR = 0; _hoops_ASRR < _hoops_AGCAC; _hoops_ASRR++) {
		_hoops_PCC._hoops_SII(_hoops_IRAR, _hoops_ASRR, null, null, &_hoops_RARR);
		if (_hoops_RARR != -1) {
			sprintf(_hoops_ISS->shader_handle, "BackDiffuseSampler%d", _hoops_ASRR);
			_hoops_ICCR(H3D_PSConstant_Table, _hoops_RGAAR + _hoops_ASRR, null, _hoops_ISS->shader_handle, _hoops_RARR);
		}
	}

	if (_hoops_PCC._hoops_GAC()) {
		_hoops_PCC._hoops_SII(_hoops_CAAR, 0, null, null, &_hoops_RARR);
		if (_hoops_RARR != -1) {
			_hoops_ICCR(H3D_PSConstant_Table, _hoops_HGAAR, null, "EnvironmentSampler", _hoops_RARR);
		}
	}

	if (_hoops_PCC._hoops_ARC()) {
		_hoops_PCC._hoops_SII(_hoops_APAR, 0, null, null, &_hoops_RARR);
		if (_hoops_RARR != -1) {
			_hoops_ICCR(H3D_PSConstant_Table, _hoops_AGAAR, null, "BumpSampler", _hoops_RARR);
		}
	}
	if (_hoops_PCC._hoops_GRC()) {
		_hoops_PCC._hoops_SII(_hoops_PPAR, 0, null, null, &_hoops_RARR);
		if (_hoops_RARR != -1) {
			_hoops_ICCR(H3D_PSConstant_Table, _hoops_PGAAR, null, "SpecularSampler", _hoops_RARR);
		}
	}
	if (_hoops_PCC._hoops_SAC()) {
		_hoops_PCC._hoops_SII(_hoops_CCRR, 0, null, null, &_hoops_RARR);
		if (_hoops_RARR != -1) {
			_hoops_ICCR(H3D_PSConstant_Table, _hoops_IGAAR, null, "FacePatternSampler", _hoops_RARR);
		}
	}
	if (_hoops_PCC._hoops_RIC()) {
		_hoops_PCC._hoops_SII(_hoops_RCPR, 0, null, null, &_hoops_RARR);
		if (_hoops_RARR != -1) {
			_hoops_ICCR(H3D_PSConstant_Table, _hoops_RRAAR, null, "GoochSampler", _hoops_RARR);
		}
	}
}


void _hoops_PIIAC::_hoops_RAPRR(H3DTexture *texture, H3DData *h3ddata)
{
	if (_hoops_PCC._hoops_RIHR())
		return;

	_hoops_HGCAC *_hoops_CGIRH = (_hoops_HGCAC *) texture;
	HOGLData *_hoops_CSRGR = (HOGLData *) h3ddata;

	int _hoops_RARR;
	_hoops_PCC._hoops_SII(_hoops_RIAR, 0, null, null, &_hoops_RARR);
	H3D_Shader_Handle b = (H3D_Shader_Handle) glGetUniformLocation (_hoops_HIIAC, "DepthPeelingScaleAndBias");

	if (_hoops_RARR >= 0 && b != _hoops_SSRAR) {
		// _hoops_IARP _hoops_IS _hoops_SISS
		_hoops_SCCR(_hoops_CSRGR, _hoops_RARR, _hoops_CGIRH);
		_hoops_ICCR(H3D_PSConstant_Table, _hoops_ARAAR, null, "DepthPeelingTexture", _hoops_RARR);

		// _hoops_HGI _hoops_PAH _hoops_SHH _hoops_IGI _hoops_IS _hoops_ARP/_hoops_IPPRA _hoops_RH _hoops_HH. _hoops_PGPR _hoops_GGCR _hoops_PIAP _hoops_RPP _hoops_IRS _hoops_HH _hoops_CSAP _hoops_ARSAR.
		if (_hoops_CGIRH)
		{
			_hoops_SCCR(_hoops_CSRGR, _hoops_RARR, texture);
			_hoops_GPIRH(h3ddata, _hoops_RARR, H3DTEXF_POINT);
			_hoops_RPIRH(h3ddata, _hoops_RARR, H3DTEXF_POINT);
			ENSURE_TEXTURE_WRAP_S(h3ddata, _hoops_RARR, H3DTADDRESS_CLAMP);
			_hoops_SAIRH(h3ddata, _hoops_RARR, H3DTADDRESS_CLAMP);


			// _hoops_HCGA _hoops_PPPR _hoops_SHI _hoops_IS _hoops_CI.
			float _hoops_GSAP[] = {
				0.5f, 
				0.5f, 
				0.5f,
				0.5f
			};
			glUniform4f ((GLint) b, 
				_hoops_GSAP[0],
				_hoops_GSAP[1],
				_hoops_GSAP[2],
				_hoops_GSAP[3]);
		}
	}
};





/*
 * _hoops_PGAA
 */
local void
invalidate_cache (HOGLData alter * _hoops_CSRGR) {
	_hoops_IHCA(_hoops_CSRGR);
	if (_hoops_CSRGR->_hoops_CSC)
		_hoops_CSRGR->_hoops_CSC->_hoops_AGSA = null;
}


/*
 *	_hoops_PGAA
 */
void _hoops_CHCGC (Display_Context alter * dc) {
	HOGLData alter *_hoops_CSRGR = OGLD (dc);

	_hoops_CSRGR->dc = dc;
	_hoops_CSRGR->_hoops_HARRR = _hoops_RSARR;

	if (!_hoops_CSRGR->_hoops_CSC)
		ALLOC(_hoops_CSRGR->_hoops_CSC, H3DCache);

	invalidate_cache (_hoops_CSRGR);

	if (_hoops_CSRGR->_hoops_PRARR)
		HI_Free_Driver_Config(_hoops_CSRGR->_hoops_PRARR);

	_hoops_RGAIR(dc->_hoops_PGCC._hoops_GSPGH);
	_hoops_RGAIR(dc->_hoops_PGCC._hoops_RSPGH);
	HI_Copy_Chars_To_Name("DEFAULT", &dc->_hoops_PGCC._hoops_GSPGH);
	HI_Copy_Chars_To_Name("*", &dc->_hoops_PGCC._hoops_RSPGH);
	dc->_hoops_PGCC._hoops_PRARR = _hoops_CSRGR->_hoops_PRARR = HI_Lookup_Driver_Config(dc->_hoops_RIGC, "opengl2", "DEFAULT", "*", true, _hoops_RSPRH);


	glEnable(GL_DEPTH_TEST);

	_hoops_CSRGR->_hoops_RRARR = 2;

	_hoops_CSRGR->_hoops_RHH.mode = false;
	_hoops_CSRGR->_hoops_RHH.flags = 0;
	_hoops_CSRGR->_hoops_RHH._hoops_HPRRR = null;

	_hoops_CSRGR->_hoops_II._hoops_PRI = true;

	_hoops_CSRGR->_hoops_GIPGR = null;
	_hoops_CSRGR->_hoops_AIPGR = null;
	_hoops_CSRGR->_hoops_RIPGR = false;

	_hoops_CSRGR->_hoops_CP._hoops_HGCGR(&_hoops_CSRGR->_hoops_CIRRR);

	_hoops_CSRGR->_hoops_II._hoops_CRPP = new _hoops_CSHAC(_hoops_CSRGR);
	_hoops_CSRGR->_hoops_RSRRR = _hoops_IICIA;
	_hoops_CSRGR->_hoops_PHAI = _hoops_IGCAC;

	if ( !_hoops_CSRGR->_hoops_PR() )
		HE_WARNING (HEC_OPENGL_DRIVER, HEC_OPENGL_DRIVER,
				"Failed to initialise ogldata." );

	HD_Get_Bit_Patterns (dc, true);
}


/*
 * _hoops_PGAA
 * _hoops_HIS _hoops_SGS _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_IS _hoops_RICGC _hoops_AICGC' _hoops_CIGS _hoops_SHIR _hoops_HSH,
 * _hoops_PPSI _hoops_ISCP _hoops_HAII _hoops_HSSPR _hoops_HSH _hoops_CRGR _hoops_HCR _hoops_ICCI _hoops_PIAP
 */
local void
_hoops_PICGC (Display_Context alter * dc) {
	HOGLData alter *_hoops_CSRGR = OGLD (dc);

	/* _hoops_SAH _hoops_HHH _hoops_API _hoops_CICRR _hoops_HIS _hoops_SGS 3d_hoops_AHSRH _hoops_PAH _hoops_ACAPA _hoops_CAPR */
	_hoops_RSCSR (_hoops_CSRGR->_hoops_RRCI);
	_hoops_CSRGR->_hoops_GSCR = NEW(_hoops_AHIAC)(_hoops_CSRGR);
	_hoops_CSRGR->_hoops_SHAP = H3D_COLOR_ABGR;
	_hoops_CSRGR->_hoops_CSS = H3D_Driver_Shader_Type_OGL2;
	_hoops_CSRGR->_hoops_ACCR = -1;
	_hoops_CSRGR->_hoops_RSCH = false;
	_hoops_CSRGR->_hoops_HSRH = HEC_OPENGL_DRIVER;

	if (_hoops_CSRGR->post == null)
		_hoops_CSRGR->post = _hoops_CSRGR->_hoops_GSCR->_hoops_HCCRR();

	_hoops_CSRGR->_hoops_HRRH = (GLEW_EXT_texture_compression_s3tc == 1);
	_hoops_CSRGR->_hoops_CAARR = (GLEW_EXT_texture_compression_s3tc == 1);
	_hoops_CSRGR->_hoops_SAARR = (GLEW_EXT_texture_compression_s3tc == 1);
	_hoops_CSRGR->_hoops_CHGH = true;
	_hoops_CSRGR->_hoops_GPARR = true;
	_hoops_CSRGR->_hoops_GAP = false;
	_hoops_CSRGR->_hoops_II._hoops_AIGP = H3DPost::_hoops_SAPP; // _hoops_RAP _hoops_SHIR _hoops_GGGP _hoops_CCH

	_hoops_IAHGC ((Display_Context alter *) dc);

	_hoops_CSRGR->_hoops_PIRH = XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_NON_POWER_OF_2_TEXTURES);
	_hoops_CSRGR->_hoops_RPARR = XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_FLAT_SHADE_MODEL);

	const char *glsl_version = (const char*) glGetString(GL_SHADING_LANGUAGE_VERSION);
	if (strstr(glsl_version, "1.2"))
		_hoops_CSRGR->glsl_version = 120;
	else if (strstr(glsl_version, "1.3"))
		_hoops_CSRGR->glsl_version = 130;
	else
		_hoops_CSRGR->glsl_version = 140;

	/* _hoops_PAIA */
	//_hoops_SIGP: _hoops_CGCAC ((_hoops_GAGSI _hoops_RAPC *) _hoops_CSPH);

	glClearColor (1.0f, 1.0f, 1.0f, 1.0f);
	glClearStencil (0);
	/*_hoops_SIGP: _hoops_HGPGA->_hoops_IHAH->_hoops_SGCAC._hoops_AIPGH._hoops_PCCIR = 255;
	_hoops_HGPGA->_hoops_IHAH->_hoops_SGCAC._hoops_AIPGH._hoops_ISHI = 255;
	_hoops_HGPGA->_hoops_IHAH->_hoops_SGCAC._hoops_AIPGH._hoops_RCSR = 255;
	_hoops_HGPGA->_hoops_IHAH->_hoops_SGCAC._hoops_AIPGH._hoops_IRS = 255;*/
	glClearDepth (1.0f);
	
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

	FORCE_CULLING(_hoops_CSRGR, H3DCULL_NONE);

	/*_hoops_HCIC _hoops_RGR _hoops_SSRR _hoops_SGIPR? _hoops_HICGC (_hoops_IICGC);*/

	_hoops_SIPRR (_hoops_CSRGR, false);


	FORCE_CULLING (_hoops_CSRGR, H3DCULL_NONE);
	_hoops_ISPRR (_hoops_CSRGR, false);
	_hoops_SPHRR (_hoops_CSRGR, H3DBLEND_SRCALPHA, H3DBLEND_INVSRCALPHA);
	_hoops_GSPRR (_hoops_CSRGR, false);
	_hoops_GAHRR (_hoops_CSRGR, H3DSTENCILOP_KEEP, H3DSTENCILOP_KEEP, H3DSTENCILOP_KEEP);
	_hoops_IRHRR (_hoops_CSRGR, H3DCMP_ALWAYS);
	_hoops_SGHRR (_hoops_CSRGR, 0x00ff);
	_hoops_IGHRR (_hoops_CSRGR, 0x00ff);
	_hoops_ARHRR (_hoops_CSRGR, 0x00ff);
	_hoops_AHPRR (_hoops_CSRGR, true);
	_hoops_HHPRR (_hoops_CSRGR, H3DMASK_RGBA);
	_hoops_CIAP (_hoops_CSRGR, true);
	_hoops_SSPRR (_hoops_CSRGR, true);
	_hoops_GHPRR (_hoops_CSRGR, false);

	glPixelStorei (GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	((_hoops_GGAGR *) dc->_hoops_GHRI)->_hoops_CAIAP = _hoops_PRIAP;
} 


/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_GRCAC _hoops_AR
*****************************************************************************
*****************************************************************************/
H3DPost* _hoops_AHIAC::_hoops_HCCRR()
{
	return new _hoops_RRCAC(_hoops_ISS);
};


static const float _hoops_PARRC[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
static const float _hoops_PAIRH[4][4] = {{1,0,0,0},{0,-1,0,0},{0,0,1,0},{0,1,0,1}};
static const float _hoops_AAIRH[4][4] = {{0,0,1,0},{1,0,0,0},{0,1,0,0},{0,0,0,1}};
static const float _hoops_HAIRH[4][4] = {{-1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};

bool _hoops_AHIAC::_hoops_GSAC (Net_Rendition const & nr, _hoops_RCR *txr, int _hoops_GCI, H3DTexture *id, int _hoops_GRRA)
{
	HOGLData *_hoops_CSRGR = _hoops_PHIAC;
	if (_hoops_GRRA >= H3D_MAX_TEXTURES)
		return false;

	/* _hoops_PHAA, _hoops_HSCR _hoops_RH _hoops_HH */
	_hoops_SCCR(_hoops_CSRGR, _hoops_GRRA, id);

	_hoops_APSS(_hoops_CSRGR);

	/* _hoops_CGP _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_IRAP _hoops_PCIA, _hoops_GA'_hoops_RA _hoops_SHAC _hoops_IS _hoops_ARP _hoops_AAIP (_hoops_PHRI _hoops_AIRRR _hoops_HGGC _hoops_RRP _hoops_HH _hoops_HCIA) */
	if ( id == null && (!txr || !BIT(txr->_hoops_SCR, _hoops_GSR)))
		return true;

	float _hoops_APGH[16];
	float dx_tm[16];
	float *result = &dx_tm[0];
	_hoops_GAAIR alter *tm = (_hoops_GAAIR alter *) nr->_hoops_IRR->_hoops_APGH;

	if (txr) {
		if (BIT(txr->_hoops_SCR, _hoops_GSR))
			_hoops_AIGA(_hoops_PARRC, 16, float, dx_tm);
		else if (BIT(txr->flags, _hoops_CSGH))
			_hoops_AIGA(_hoops_AAIRH, 16, float, dx_tm);
		else if (_hoops_GCI == _hoops_HSGH)
			_hoops_AIGA(_hoops_HAIRH, 16, float, dx_tm);
		else
			_hoops_AIGA(_hoops_PAIRH, 16, float, dx_tm);
		if (txr->_hoops_GAGH != null) {
			/* _hoops_PS _hoops_HS _hoops_IRS _hoops_PIAH _hoops_HH-_hoops_IIHA _hoops_RSGA */
			HI_Matmul_44_by_44(
				&txr->_hoops_GAGH->matrix._hoops_APRA->data.elements[0][0],
				&_hoops_PAIRH[0][0],
				dx_tm);
		}
		if (!BIT(txr->flags, _hoops_IPGH) &&
			ANYBIT (tm->matrix._hoops_RAGR, _hoops_CICH)) {
			/* _hoops_PS _hoops_HS _hoops_RGAR _hoops_IRS _hoops_CAGH-_hoops_IIHA _hoops_RSGA */
			if (tm->matrix._hoops_APRA == null)
				HI_Validate_Matrix_Adjoint ((_hoops_HRPA *)&tm->matrix);

			HI_Matmul_44_by_44(
				&tm->matrix._hoops_APRA->data.elements[0][0],
				dx_tm,
				_hoops_APGH);

			result = &_hoops_APGH[0];
		}
		if (!EQUAL_MEMORY(result, 16*sizeof(float), _hoops_CSRGR->_hoops_PRRA[_hoops_GRRA])) {
			_hoops_CSRGR->_hoops_RRRA[_hoops_GRRA] = true;
			_hoops_AIGA(result, 16, float, _hoops_CSRGR->_hoops_PRRA[_hoops_GRRA]);
		}
	}
	else {
		ASSERT (_hoops_GCI != _hoops_HSGH);
		_hoops_AIGA(_hoops_PAIRH, 16, float, dx_tm);
		if (!EQUAL_MEMORY(result, 16*sizeof(float), _hoops_CSRGR->_hoops_PRRA[_hoops_GRRA])) {
			_hoops_CSRGR->_hoops_RRRA[_hoops_GRRA] = true;
			_hoops_AIGA(result, 16, float, _hoops_CSRGR->_hoops_PRRA[_hoops_GRRA]);
		}
	}

	/* _hoops_CGP _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_IRAP _hoops_PCIA, _hoops_GA'_hoops_RA _hoops_SHAC _hoops_IS _hoops_ARP _hoops_AAIP */
	if ( id == null )
		return true;

	/* _hoops_AGGA, _hoops_ARP _hoops_GH _hoops_RH _hoops_HH _hoops_RHRP (_hoops_RPP _hoops_GII) */
	if (_hoops_GCI == _hoops_HSGH) {
		if (id->_hoops_SGPRR()) {
			glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, _hoops_ARCAC(H3DTADDRESS_WRAP));
			glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, _hoops_ARCAC(H3DTADDRESS_WRAP));
			glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, _hoops_SPIAC(H3DTEXF_LINEAR));
			glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, _hoops_SPIAC(H3DTEXF_LINEAR));
		}
		else {
			ENSURE_TEXTURE_WRAP_S (_hoops_CSRGR, _hoops_GRRA, H3DTADDRESS_WRAP);
			_hoops_SAIRH (_hoops_CSRGR, _hoops_GRRA, H3DTADDRESS_WRAP);
			_hoops_GPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_LINEAR);
			_hoops_RPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_LINEAR);
		}
	}
	else if (_hoops_GCI == _hoops_GCHGR) {
		if (!BIT (nr->_hoops_IRR->_hoops_CSA,_hoops_HIRC)) {
			_hoops_GPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_POINT);
			_hoops_RPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_POINT);
		}
		else {
			_hoops_GPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_LINEAR);
			_hoops_RPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_LINEAR);
		}
	}
	else if (_hoops_GCI == _hoops_PCRS) {
		if (!BIT (nr->_hoops_IRR->_hoops_CSA,_hoops_SSRC)) {
			_hoops_GPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_POINT);
			_hoops_RPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_POINT);
		}
		else {
			_hoops_GPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_LINEAR);
			_hoops_RPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_LINEAR);
		}
	}
	else if (_hoops_GCI == _hoops_RSAC || _hoops_GCI == _hoops_GIPS) {
		ENSURE_TEXTURE_WRAP_S (_hoops_CSRGR, _hoops_GRRA, H3DTADDRESS_WRAP);
		_hoops_SAIRH (_hoops_CSRGR, _hoops_GRRA, H3DTADDRESS_WRAP);
		_hoops_GPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_POINT);
		_hoops_RPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_POINT);
	}
	else if (_hoops_GCI == _hoops_SPHC) {
		ENSURE_TEXTURE_WRAP_S (_hoops_CSRGR, _hoops_GRRA, H3DTADDRESS_WRAP);
		_hoops_SAIRH (_hoops_CSRGR, _hoops_GRRA, H3DTADDRESS_WRAP);
		_hoops_GPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_LINEAR);
		_hoops_RPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_LINEAR);
	}
	else if (_hoops_GCI == _hoops_RCHGR) {
		ENSURE_TEXTURE_WRAP_S (_hoops_CSRGR, _hoops_GRRA, H3DTADDRESS_MIRROR);
		_hoops_SAIRH (_hoops_CSRGR, _hoops_GRRA, H3DTADDRESS_MIRROR);
		_hoops_RPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_POINT);
		_hoops_GPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_POINT);
		_hoops_APIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_POINT);
	}
	else if (txr) {
		switch (txr->_hoops_CGA) {
			case _hoops_ASGRP:
				ENSURE_TEXTURE_WRAP_S (_hoops_CSRGR, _hoops_GRRA, H3DTADDRESS_WRAP);
				_hoops_SAIRH (_hoops_CSRGR, _hoops_GRRA, H3DTADDRESS_WRAP);
				break;
			case _hoops_ASCC:
				ENSURE_TEXTURE_WRAP_S (_hoops_CSRGR, _hoops_GRRA, H3DTADDRESS_CLAMP);
				_hoops_SAIRH (_hoops_CSRGR, _hoops_GRRA, H3DTADDRESS_CLAMP);
				break;
			case _hoops_PSGRP:
				ENSURE_TEXTURE_WRAP_S (_hoops_CSRGR, _hoops_GRRA, H3DTADDRESS_MIRROR);
				_hoops_SAIRH (_hoops_CSRGR, _hoops_GRRA, H3DTADDRESS_MIRROR);
				break;
		}

		if (txr->_hoops_RARH == _hoops_PARH)
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, _hoops_CSRGR->_hoops_GSSGC);
		
		/*_hoops_RRPS _hoops_IS _hoops_PAGGR _hoops_PPIRH _hoops_HSHIA 4-94 _hoops_SR _hoops_CGH _hoops_IIP _hoops_CAH _hoops_PGGA _hoops_IIGR _hoops_PIGGH*/
		if (txr->_hoops_PSCC == _hoops_HSCC) {
			_hoops_RPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_POINT);
			_hoops_GPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_POINT);
		}
		else {
			_hoops_RPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_LINEAR);
			_hoops_GPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_LINEAR);
		}
		if (txr->_hoops_RARH == _hoops_AARH) {
			_hoops_APIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_POINT);
		}
		else if (txr->_hoops_RARH == _hoops_PARH) {
			_hoops_GPIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_LINEAR);
			_hoops_APIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_LINEAR);
		}
		else {
			_hoops_APIRH (_hoops_CSRGR, _hoops_GRRA, H3DTEXF_NONE);
		}
	}

	return true;
}


void _hoops_IPRRC(H3DData *h3ddata, int _hoops_RHIA)
{
	HOGLData *_hoops_CSRGR = (HOGLData*) h3ddata;
	_hoops_CSRGR->_hoops_PRCAC._hoops_HRCAC = (int)_hoops_RHIA;
	glActiveTexture(GL_TEXTURE0 + _hoops_RHIA);
}



/*****************************************************************************
 *****************************************************************************
							_hoops_HRRAH
 _hoops_AGCR _hoops_PSCH _hoops_CHR _hoops_SIGR _hoops_IH 3d _hoops_IAGIP _hoops_PPR 2d _hoops_GACC...
 *****************************************************************************
 *****************************************************************************/
/*
 * _hoops_SRAC
 * _hoops_RPP _hoops_GHGPR _hoops_RHGPR, _hoops_RGR _hoops_PIHA _hoops_SHH _hoops_PIGS _hoops_ARPP _hoops_RH _hoops_GGSHR _hoops_PSCA
 */
local bool
snapshot(
	Net_Rendition const & nr,
	int width,
	int height,
	unsigned char * data) {

	HOGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA); 
	Int_Rectangle const * area = &nr->_hoops_SAIR->_hoops_SCIH; 
	GLint w,h;
	int x,y,index;
	unsigned char * _hoops_IGHSI;

#ifdef GLX_DRIVER
	bool _hoops_GSCRC = false;
	if (!glXGetCurrentContext()) {
		if (glXMakeCurrent (_hoops_CSRGR->display, _hoops_CSRGR->window, _hoops_CSRGR->context) == GL_FALSE) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								   "glXMakeCurrent failed for snapshot.");
			return false;
		}
		_hoops_GSCRC = true;
	}
#endif
#ifdef WGL_DRIVER
	bool _hoops_GSCRC = false;
	if (!wglGetCurrentContext()) {
		if (wglMakeCurrent (_hoops_CSRGR->hDC, _hoops_CSRGR->hGLRC) == GL_FALSE) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								   "wglMakeCurrent failed for snapshot.");
			return false;
		}
		_hoops_GSCRC = true;
	}
#endif

	w = area->right - area->left + 1;
	h = area->top - area->bottom + 1;

	if (w*h > width*height) return false;
		   
	/* _hoops_SRGC _hoops_CPAP _hoops_IS _hoops_HCHSR _hoops_PSCA _hoops_ARPP _hoops_GPS */ 
	glFlush ();

	ALLOC_ARRAY(_hoops_IGHSI, w*h*3, unsigned char);
	 
	if (_hoops_CSRGR->_hoops_SRRRR)
		glReadBuffer(GL_BACK);
	else
		glReadBuffer(GL_FRONT);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ROW_LENGTH, 0);
	glReadPixels (0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, (void *)_hoops_IGHSI);

	for (y=h-1;y>=0;y--) {
		for (x=0;x<w;x++) {
			index=(y*w+x)*3; 
			*data++ = (unsigned char)_hoops_IGHSI[index+0];
			*data++ = (unsigned char)_hoops_IGHSI[index+1];
			*data++ = (unsigned char)_hoops_IGHSI[index+2];
		}
	}

	FREE_ARRAY(_hoops_IGHSI, w*h*3, unsigned char);

#ifdef GLX_DRIVER
	if (_hoops_GSCRC)
		glXMakeCurrent(_hoops_CSRGR->display, 0, 0);
#endif
#ifdef WGL_DRIVER
	if (_hoops_GSCRC)
		wglMakeCurrent (0, 0);
#endif

	return true;
}



/*
 * _hoops_SRAC
 */
local void
_hoops_CGAGR (Display_Context const *dc, void *list)
{
	H3D_Display_List alter * odl = (H3D_Display_List alter*)list;
	HOGLData alter *_hoops_CSRGR = OGLD (dc);
	Image *image = (Image *)odl->_hoops_PPAH->owner;
	int w = image->width;
	int h = image->height;
	_hoops_HGCAC *_hoops_IRCAC = (_hoops_HGCAC *)odl->item.texture.id;
	GLint _hoops_CRCAC = 0;
	GLenum format = GL_RGBA;
	int _hoops_GCPIR = 4;

	switch (image->format) {
		case _hoops_AHGH:
			format = GL_LUMINANCE;
			_hoops_GCPIR = 1;
			break;
		case _hoops_HHGH:
			format = GL_RGB;
			_hoops_GCPIR = 3;
			break;
		case Image_RGBA32:
			format = GL_RGBA;
			_hoops_GCPIR = 4;
			break;
		default: 
			ASSERT(0);
	}
	if (image->_hoops_PHGH == null)
		ALLOC_ARRAY (image->_hoops_PHGH, w*h*_hoops_GCPIR, unsigned char);
	_hoops_IHRRC (_hoops_CSRGR, 0);
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &_hoops_CRCAC);
	_hoops_IRCAC->_hoops_SRCAC (0);
	glGetTexImage (GL_TEXTURE_2D, 0, format, GL_UNSIGNED_BYTE, (void *)image->_hoops_PHGH);

	if (image->rasters == null) {
		ALLOC_ARRAY (image->rasters, image->height, void const *);
		void **_hoops_RARAH = (void **)image->rasters;
		for (int i = 0 ; i < image->height ; i++) {
			_hoops_RARAH[i] = &((unsigned char *)image->_hoops_PHGH)[image->row_bytes*i];
		}
	}
	image->flags &= ~(_hoops_GRRH|_hoops_APAH);

	glBindTexture(GL_TEXTURE_2D, _hoops_CRCAC);
}



local int _hoops_RSCRC (HOGLData *_hoops_CSRGR) 
{
	GLint _hoops_ASCRC = 0;
	GLuint _hoops_SISGC, _hoops_GCSGC;

	/* _hoops_PSHR _hoops_GAR _hoops_ARRS, _hoops_HIH _hoops_CCA _hoops_RH _hoops_HPRGR _hoops_ISCRC _hoops_RIIA _hoops_IIGR _hoops_RH _hoops_SPR
       _hoops_CHIA _hoops_GAR _hoops_ARIP _hoops_IIGR _hoops_CSCRC */
	const char *_hoops_PSCRC = 
		"uniform sampler2D depth_sampler; \n"
		"void main() { \n"
		"	vec4 tmp = texture2D(depth_sampler, gl_TexCoord[0].xy); \n"
		"	gl_FragDepth = tmp.r; \n"
		"} \n";

	  /* _hoops_ARP _hoops_GH _hoops_RH _hoops_RRAA-_hoops_IIHA _hoops_CI */
	_hoops_SISGC = glCreateProgram();
	_hoops_GCSGC = glCreateShader (GL_FRAGMENT_SHADER_ARB);
	glShaderSource(_hoops_GCSGC, 1, &_hoops_PSCRC, null);
	glCompileShader(_hoops_GCSGC);
	glGetShaderiv (_hoops_GCSGC, GL_COMPILE_STATUS, &_hoops_ASCRC);
	_hoops_CSRGR->_hoops_SSCRC = _hoops_SISGC;
	_hoops_CSRGR->_hoops_GGSRC = _hoops_GCSGC;
	return _hoops_ASCRC;
}


local int _hoops_RGSRC (HOGLData *_hoops_CSRGR) 
{
	GLuint _hoops_SISGC, _hoops_GCSGC;
	GLint _hoops_ASCRC = 0;
	char buffer[4096];
	GLsizei length;

	/* _hoops_IRS _hoops_CPPPR _hoops_IHGP _hoops_SPPPR _hoops_SGS _hoops_PGSRC _hoops_RH _hoops_HCH _hoops_PIRA _hoops_HII _hoops_IRS _hoops_HH _hoops_IS _hoops_RH 
	   _hoops_IIPR _hoops_HCH (_hoops_PGAP _hoops_CHH _hoops_HCAGR _hoops_SHH _hoops_RAGA _hoops_RH _hoops_HCH _hoops_PIRA _hoops_IIGR _hoops_RH _hoops_HSSP) */
	const char *_hoops_AGSRC = 
		"#extension GL_ARB_texture_rectangle : enable\n"
		"uniform sampler2DRect depth_sampler; \n"
		"void main() { \n"
		"	vec4 tmp = texture2DRect(depth_sampler, gl_TexCoord[0].xy); \n"
		"	gl_FragDepth = tmp.r; \n"
		"} \n";

	_hoops_SISGC = glCreateProgram();
	_hoops_GCSGC = glCreateShader (GL_FRAGMENT_SHADER_ARB);
	glEnable (GL_TEXTURE_RECTANGLE_ARB);
	glShaderSource(_hoops_GCSGC, 1, &_hoops_AGSRC, null);
	glCompileShader(_hoops_GCSGC);
	glDisable (GL_TEXTURE_RECTANGLE_ARB);
	glGetShaderiv (_hoops_GCSGC, GL_COMPILE_STATUS, &_hoops_ASCRC);

	/* _hoops_HHH _hoops_RSIH _hoops_IRSP _hoops_IIGR _hoops_CCPGC _hoops_SARS'_hoops_RA _hoops_GCGH _hoops_IGSRC, _hoops_HIS _hoops_SR _hoops_HS _hoops_IS 
	   _hoops_HSSC _hoops_ISSC _hoops_IS _hoops_RH _hoops_RSAHH _hoops_SGS _hoops_CSAP _hoops_IIHA _hoops_GPP _hoops_RRAA _hoops_AI */
	if (!_hoops_ASCRC) {
		  /* _hoops_CASI _hoops_GH _hoops_RH _hoops_IIPSI-_hoops_IIHA _hoops_CI */
		glDetachShader (_hoops_CSRGR->_hoops_SISGC, _hoops_CSRGR->_hoops_GCSGC);
		glDeleteShader (_hoops_CSRGR->_hoops_GCSGC);
		glDeleteProgram (_hoops_CSRGR->_hoops_SISGC);

		  /* _hoops_ARP _hoops_GH _hoops_RH _hoops_RRAA-_hoops_IIHA _hoops_CI */
		_hoops_ASCRC = _hoops_RSCRC (_hoops_CSRGR);
		_hoops_SISGC = _hoops_CSRGR->_hoops_SSCRC;
		_hoops_GCSGC = _hoops_CSRGR->_hoops_GGSRC; 
	}

	glAttachShader (_hoops_SISGC, _hoops_GCSGC);
	glLinkProgram (_hoops_SISGC);
	if (!_hoops_ASCRC) {
		glGetShaderInfoLog (_hoops_GCSGC, sizeof(buffer), &length, buffer);
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, 
			Sprintf_S (null, "shader compilation error reported by opengl:\n%S", buffer));
	}
	_hoops_CSRGR->_hoops_SISGC = _hoops_SISGC;
	_hoops_CSRGR->_hoops_GCSGC = _hoops_GCSGC;
	return 0;
}


#if 1
/* 
 * _hoops_SRAC
 * _hoops_HSSIA _hoops_PPGS _hoops_IH _hoops_SRGIA _hoops_HHH _hoops_CSCR _hoops_PIH.
 * _hoops_HRS _hoops_PSCA _hoops_GGR _hoops_RH _hoops_SRSGR _hoops_IIGR _hoops_CSCR _hoops_PPR _hoops_PPR/_hoops_PAR _hoops_IARAH
 * _hoops_HRS _hoops_IRAP _hoops_IH _hoops_CARAH _hoops_RPP _hoops_SSH-_hoops_RHGPR _hoops_HRGR _hoops_IHPPP _hoops_PSAP
 */
void _hoops_AHIAC::create_region (
	Net_Rendition const & nr,
	Int_Rectangle const * area, 
	void **image, 
	void **z) 
{
	UNREFERENCED(area);

	HOGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA); 
	_hoops_SICRC *_hoops_PARAH = null;
	_hoops_SICRC *_hoops_GCIIP = null;

	_hoops_RAPRC("create_region", true);

	// _hoops_SIPR _hoops_HIRA _hoops_ACGGR _hoops_HAARR
	int const width = _hoops_CSRGR->render_target->_hoops_IRRP;
	int const height = _hoops_CSRGR->render_target->_hoops_CRRP;

	// _hoops_CCPP _hoops_PPGS _hoops_PPR _hoops_GGCR _hoops_IS _hoops_AGGAR _hoops_HIGR
	if (image) {
		ALLOC(_hoops_PARAH, _hoops_SICRC);
		*image = _hoops_PARAH;

		// _hoops_GISA _hoops_PSGRR _hoops_IS _hoops_ASAC _hoops_RH _hoops_HIRA
		_hoops_PARAH->surface = NEW(_hoops_RGIAC)(_hoops_CSRGR, width, height, 
			H3DTEXUSAGE_RENDERTARGET, _hoops_CSRGR->render_target->_hoops_GSPP, _hoops_CSRGR->render_target->_hoops_HSARR);
	}

	// _hoops_PSHR _hoops_IH _hoops_RH _hoops_SSH
	if (z) {
		ALLOC(_hoops_GCIIP, _hoops_SICRC);
		*z = _hoops_GCIIP;

		// _hoops_SIPR _hoops_HIRA _hoops_HCH _hoops_APSP _hoops_ISSGR _hoops_HRPRA.
		ASSERT( width == _hoops_CSRGR->depth_stencil->_hoops_IRRP && height == _hoops_CSRGR->depth_stencil->_hoops_CRRP );

		// _hoops_GISA _hoops_PSGRR _hoops_IS _hoops_ASAC _hoops_RH _hoops_HCH/_hoops_APSP _hoops_ISSGR
		// _hoops_GISA _hoops_PSGRR _hoops_IS _hoops_ASAC _hoops_RH _hoops_HIRA
		_hoops_GCIIP->surface = NEW(_hoops_RGIAC)(_hoops_CSRGR, width, height, 
			H3DTEXUSAGE_DEPTHSTENCIL, _hoops_CSRGR->depth_stencil->_hoops_GSPP, _hoops_CSRGR->depth_stencil->_hoops_HSARR);

		// _hoops_HR _hoops_PSP _hoops_HCH _hoops_HH
		_hoops_GCIIP->texture = null;
	}

}/* _hoops_RSGR _hoops_API _hoops_HARAH */


/* 
 * _hoops_SRAC
 * _hoops_PHRAH
 */
void _hoops_AHIAC::_hoops_ISPGR (Display_Context alter *dc,
				void alter * image, void alter * z) 
{
	UNREFERENCED(dc);

	_hoops_SICRC *_hoops_PARAH = (_hoops_SICRC *) image;
	_hoops_SICRC *_hoops_GCIIP = (_hoops_SICRC *) z;

	_hoops_RAPRC("destroy_region", true);

	if (_hoops_PARAH) {
		_hoops_HP(_hoops_PARAH->surface);
	}
	if (_hoops_GCIIP) {
	    _hoops_HP(_hoops_GCIIP->surface);
		_hoops_HP(_hoops_GCIIP->texture);
	}

	if (_hoops_PARAH == _hoops_GCIIP) {
		FREE(_hoops_PARAH, _hoops_SICRC);
	}
	else {
		if (_hoops_GCIIP) {
			FREE(_hoops_GCIIP, _hoops_SICRC);
		}
		if (_hoops_PARAH) {
			FREE(_hoops_PARAH, _hoops_SICRC);
		}
	}	
}/* _hoops_RSGR _hoops_API _hoops_PHRAH */


/* 
 * _hoops_SRAC
 */
void _hoops_AHIAC::_hoops_HIPGR (Net_Rendition const & nr,
			 Int_Rectangle const * area, 
			 void alter * image,
			 void alter * z) 
{
	UNREFERENCED(area);

	HOGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_SICRC *_hoops_PARAH = (_hoops_SICRC *) image;
	_hoops_SICRC *_hoops_GCIIP = (_hoops_SICRC *) z;

	_hoops_RAPRC("save_region", true);
	if (_hoops_PARAH && _hoops_PARAH->surface) // _hoops_GIGHR: _hoops_AARAR _hoops_HGCR _hoops_SHPHP _hoops_RHSP _hoops_PCCS
		_hoops_HGIP(_hoops_CSRGR, _hoops_CSRGR->render_target, _hoops_PARAH->surface, H3DTEXF_NONE);

	if (_hoops_GCIIP) {
		if (_hoops_GCIIP->surface)
			_hoops_HGIP(_hoops_CSRGR, _hoops_CSRGR->depth_stencil, _hoops_GCIIP->surface, H3DTEXF_NONE);

		if (_hoops_CSRGR->_hoops_II.depth_texture) {
			// _hoops_GISA _hoops_GPP _hoops_HRGGR
			if ( !_hoops_GCIIP->texture ) {
				// _hoops_GISA _hoops_PSGRR _hoops_IS _hoops_ASAC _hoops_RH _hoops_HCH _hoops_HH _hoops_ISSGR
				_hoops_GCIIP->texture = NEW(_hoops_RGIAC)(_hoops_CSRGR, 
					_hoops_CSRGR->_hoops_II.depth_texture->_hoops_IRRP,
					_hoops_CSRGR->_hoops_II.depth_texture->_hoops_CRRP,
					H3DTEXUSAGE_RENDERTARGET,
					_hoops_CSRGR->_hoops_II.depth_texture->_hoops_GSPP,
					_hoops_CSRGR->_hoops_II.depth_texture->_hoops_HSARR);
			}

			if ( _hoops_GCIIP->texture )
				_hoops_HGIP(_hoops_CSRGR, _hoops_CSRGR->_hoops_II.depth_texture, _hoops_GCIIP->texture );

		}
	}

}/* _hoops_RSGR _hoops_API _hoops_CCPIP */


/* 
 * _hoops_SRAC
 */
void _hoops_AHIAC::_hoops_PIPGR (Net_Rendition const & nr,
				Int_Rectangle const * area, 
				void alter * image,
				void alter * z) 
{
	UNREFERENCED(area);

	HOGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_SICRC *_hoops_PARAH = (_hoops_SICRC *) image;
	_hoops_SICRC *_hoops_GCIIP = (_hoops_SICRC *) z;

	_hoops_RAPRC("restore_region", true);

	// _hoops_SIPR _hoops_HIRA _hoops_ACGGR _hoops_HAARR
	int const width = _hoops_CSRGR->render_target->_hoops_IRRP / _hoops_CSRGR->_hoops_HSAA;
	int const height = _hoops_CSRGR->render_target->_hoops_CRRP / _hoops_CSRGR->_hoops_ISAA;

	_hoops_APHH(_hoops_CSRGR, 0, 1);
	_hoops_PPHH(_hoops_CSRGR, 0, 0, width, height);
	int const _hoops_GGSH = _hoops_CSRGR->_hoops_CSC->_hoops_GRPP;
	_hoops_GPRP(_hoops_CSRGR, H3DMASK_RGBA);

	if (_hoops_PARAH && _hoops_PARAH->surface) // _hoops_GIGHR: _hoops_AARAR _hoops_HGCR _hoops_SHPHP _hoops_RHSP _hoops_PCCS
		_hoops_HGIP(_hoops_CSRGR, _hoops_PARAH->surface, _hoops_CSRGR->render_target, H3DTEXF_NONE);
	if (_hoops_GCIIP && _hoops_GCIIP->surface)
		_hoops_HGIP(_hoops_CSRGR, _hoops_GCIIP->surface, _hoops_CSRGR->depth_stencil, H3DTEXF_NONE);
	if (_hoops_GCIIP && _hoops_GCIIP->texture && _hoops_CSRGR->_hoops_II.depth_texture)
		_hoops_HGIP(_hoops_CSRGR, _hoops_GCIIP->texture, _hoops_CSRGR->_hoops_II.depth_texture);

	_hoops_GPRP(_hoops_CSRGR, _hoops_GGSH);

}/* _hoops_RSGR _hoops_API _hoops_SPRAH */
#endif





/*****************************************************************************
 *****************************************************************************
							_hoops_GACAC _hoops_HIGAH
 *****************************************************************************
 *****************************************************************************/
/*
 * _hoops_IHRAH - _hoops_IAGP _hoops_RACGH
 */

local void * _hoops_GRSSP (
	Net_Rendition const &nr,
	bool				disable_write) {
	HOGLData alter *		_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	GLuint					id;

	ENSURE_TRANSPARENCY(_hoops_CSRGR, false);

	if (disable_write) {
		_hoops_RPAP(_hoops_CSRGR, false);
		ENSURE_DEPTH_MASK(_hoops_CSRGR, false);
	}

	glGenQueries (1, &id);
	glBeginQuery (GL_SAMPLES_PASSED_ARB, id);

	return (void *)(POINTER_SIZED_INT)id;
}

local void _hoops_RRSSP (
	Net_Rendition const &nr,
	void *					_hoops_HACGH) {
	HOGLData alter *		_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	UNREFERENCED(_hoops_HACGH);

	glEndQueryARB (GL_SAMPLES_PASSED_ARB);

	_hoops_RPAP(_hoops_CSRGR, true);
	ENSURE_DEPTH_MASK(_hoops_CSRGR, true);

	_hoops_CSRGR->_hoops_CCRGC = true;
}

local int _hoops_CRGIP (
	Net_Rendition const &nr,
	void *					_hoops_HACGH) {
	HOGLData alter *		_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	GLuint					id = (GLuint)(POINTER_SIZED_INT)_hoops_HACGH;
	GLuint					value=0;

	if (_hoops_CSRGR->_hoops_CCRGC) {
		glFlush();
		_hoops_CSRGR->_hoops_CCRGC = false;
	}

	_hoops_GPRH(_hoops_IHRGH)++;

	while (1) {	 
		glGetQueryObjectuiv (id, GL_QUERY_RESULT_AVAILABLE_ARB, &value);
		if (value)
			break;
	}
	if (value)
		glGetQueryObjectuiv (id, GL_QUERY_RESULT_ARB, &value);
	else
		value = ~0U;

	glDeleteQueriesARB (1, &id);

	return value;
}

local void _hoops_ARSSP (
	Net_Rendition const &nr,
	void *					_hoops_HACGH) {
	HOGLData alter *		_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	UNREFERENCED(_hoops_CSRGR);

	GLuint					id = (GLuint)(POINTER_SIZED_INT)_hoops_HACGH;

	glDeleteQueries (1, &id);
}


/*****************************************************************************
 *****************************************************************************
							_hoops_RACAC
 *****************************************************************************
 *****************************************************************************/
/*
 * _hoops_PGAA
 */

void _hoops_AHIAC::_hoops_IPRS( _hoops_PPRS *_hoops_HPRS )
{
	HOGLData *_hoops_CSRGR = _hoops_PHIAC;

	// _hoops_GRSH _hoops_AHPH _hoops_AA _hoops_SR _hoops_HIISR _hoops_CCA?
	const int _hoops_GSARH = _hoops_AHIA((int) _hoops_HPRS->_hoops_SICRR, _hoops_CSRGR->_hoops_GRAP);

	// _hoops_RSCS _hoops_HPHR _hoops_HCSS
	for ( int i = 0; i < _hoops_GSARH; ++i )
		_hoops_HPRS->_hoops_PGRGR[i] = (_hoops_CSRGR->fbo) ? _hoops_CSRGR->fbo->_hoops_HHIAC[i] : null;

	// _hoops_GHPA _hoops_HHRPA _hoops_AIRP.
	for ( int i = _hoops_GSARH; i < _hoops_HPRS->_hoops_SICRR; ++i )
		_hoops_HPRS->_hoops_PGRGR[i] = null;

	// _hoops_RSCS _hoops_HCH _hoops_SRHR
	_hoops_HPRS->depth_stencil = (_hoops_CSRGR->fbo) ? _hoops_CSRGR->fbo->m_depth : null;
	
	// _hoops_RSCS _hoops_HCSS _hoops_PPR _hoops_ICIH
	//_hoops_AACAC(_hoops_PACAC);
}

void _hoops_AHIAC::_hoops_CHRS( _hoops_PPRS *_hoops_HPRS, bool release )
{
	HOGLData *_hoops_CSRGR = _hoops_PHIAC;
	UNREFERENCED(_hoops_CSRGR);
	UNREFERENCED(_hoops_HPRS);
	UNREFERENCED(release);

	// _hoops_IPRP _hoops_CPS
	//_hoops_HACAC();

	ASSERT( _hoops_HPRS->_hoops_SICRR == 4 );
	//_hoops_HGPGA->_hoops_ICRI->_hoops_RHRS(_hoops_RCPGR->_hoops_HCSS[0], _hoops_RCPGR->_hoops_IACAC, _hoops_RCPGR->_hoops_HCSS[1], _hoops_RCPGR->_hoops_HCSS[2], _hoops_RCPGR->_hoops_HCSS[3] );
	_hoops_CSRGR->_hoops_GSCR->_hoops_GPAP((H3DRenderTarget*) _hoops_HPRS->_hoops_PGRGR[0], 
		(H3DRenderTarget*) _hoops_HPRS->depth_stencil, 
		(H3DRenderTarget*) _hoops_HPRS->_hoops_PGRGR[1], 
		(H3DRenderTarget*) _hoops_HPRS->_hoops_PGRGR[2], 
		(H3DRenderTarget*) _hoops_HPRS->_hoops_PGRGR[3] );

#if 0
	// _hoops_PPGGR _hoops_HCR _hoops_ISCP _hoops_PRCHR.
	H_SAFE_RELEASE(_hoops_HPRS.depth_stencil);
	for ( int i = 0; i < _hoops_HPRS._hoops_SICRR; ++i )
		H_SAFE_RELEASE(_hoops_HPRS._hoops_PGRGR[i]);
#endif
}


bool _hoops_ISARH( HOGLData *_hoops_CSRGR , int width, int height, unsigned int _hoops_ISARR)
{
	_hoops_CSRGR->render_target = NEW(_hoops_RGIAC)(_hoops_CSRGR, 
		width, height, H3DTEXUSAGE_RENDERTARGET, H3DFMT_A8R8G8B8, _hoops_ISARR);

	_hoops_CSRGR->depth_stencil = NEW(_hoops_RGIAC)(_hoops_CSRGR, 
		width, height, H3DTEXUSAGE_DEPTHSTENCIL, H3DFMT_D24S8, _hoops_ISARR);

#if 0
	_hoops_CSRGR->_hoops_CACAC = NEW(_hoops_RGIAC)(_hoops_CSRGR, 
		width, height, H3DTEXUSAGE_RENDERTARGET, H3DFMT_A8R8G8B8, _hoops_ISARR);
#endif

	return true;
}

void _hoops_RSARH( HOGLData *_hoops_CSRGR )
{
	// _hoops_HHPC, _hoops_RCSH _hoops_SCGR _hoops_AHCS
	_hoops_CSRGR->_hoops_GSCR->_hoops_GPAP(null);
	_hoops_HP(_hoops_CSRGR->render_target);
	_hoops_HP(_hoops_CSRGR->depth_stencil);
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
	HOGLData alter *				_hoops_CSRGR = OGLD (dc);
	int							_hoops_RIRAH = dc->_hoops_AHAGH;
	int							_hoops_AIRAH;
	_hoops_PGCIP alter *			list;
	int							i;
	int							_hoops_PIRAH = 0;
	int							_hoops_IAAIP, _hoops_CAAIP;
	int							width, height;
	Int_Rectangle const *		extent;
	bool						_hoops_IA = true;
	bool						result = true;
	H3DTexture					**_hoops_IPRRR = _hoops_CSRGR->_hoops_RHH._hoops_IPRRR;
	H3DTexture					**_hoops_CPRRR = _hoops_CSRGR->_hoops_RHH._hoops_CPRRR;
	float						_hoops_ACCRR, _hoops_PCCRR, _hoops_ISPI, _hoops_CSPI;

	// _hoops_HIRAH _hoops_AAP
	// _hoops_AHH:						_hoops_SPAP, _hoops_RGR _hoops_IGI _hoops_IS _hoops_SRSHR _hoops_GH _hoops_HHH _hoops_PPRAR _hoops_PIH _hoops_HII _hoops_HGPGA.
	const bool					_hoops_ISARR = _hoops_CSRGR->_hoops_CRAP == _hoops_SRAP;
	H3DFORMAT					_hoops_GCH = H3DFMT_R32F;
	bool						_hoops_ACH = true;

// _hoops_AHH: _hoops_ISIRR _hoops_IH _hoops_HISRA _hoops_AIRI
//#_hoops_PPIP _hoops_IIRAH

	if (dc->_hoops_PPSIP != null)
		HD_Process_Deferred_Octrees (dc);

#ifdef _hoops_CIRAH
	// _hoops_GISA/_hoops_ASAC _hoops_CSCR _hoops_ARPP _hoops_ICH
	if ( _hoops_PGCIP alter * _hoops_SIRAH = dc->_hoops_GPSS[dc->_hoops_IASS] ) {
		if ( !_hoops_CSRGR->_hoops_ICIRH || !_hoops_CSRGR->_hoops_CCIRH )
			create_region(_hoops_SIRAH->nr, null, &_hoops_CSRGR->_hoops_ICIRH, &_hoops_CSRGR->_hoops_CCIRH);
		_hoops_HIPGR(_hoops_SIRAH->nr, null, _hoops_CSRGR->_hoops_ICIRH, _hoops_CSRGR->_hoops_CCIRH);
	}
#endif
	

	//
	// _hoops_GCRAH-_hoops_GGSR _hoops_IH _hoops_RSRA-_hoops_ASAH _hoops_ICH, _hoops_PGAP _hoops_PAH _hoops_SHH _hoops_GIR _hoops_GGGGR.
	//

	if (/*_hoops_HGSRC ||*/ (_hoops_RIRAH == 1)) {
		_hoops_CSRGR->_hoops_GSCR->_hoops_ASCRR(L"layer 1 depth peeling");
		_hoops_CSRGR->_hoops_RHH._hoops_HRI = true;
		HD_Std_Depth_Peeling (dc);
		_hoops_CSRGR->_hoops_RHH._hoops_HRI = false;
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
		if (!_hoops_CSRGR->_hoops_GAP) 
			_hoops_GCH = H3DFMT_A8R8G8B8;

		// _hoops_CGP _hoops_SR _hoops_PAH _hoops_AA _hoops_RIAP, _hoops_SR _hoops_GA'_hoops_RA _hoops_RRP _hoops_PGCR _hoops_RIH. _hoops_HHPC _hoops_SR _hoops_AA.
		if (_hoops_CSRGR->_hoops_GRAP < 2)
			_hoops_ACH = false;
	}

	if (_hoops_RIRAH > _hoops_APRRR)
		_hoops_RIRAH = _hoops_APRRR;

	//
	// _hoops_HGH _hoops_PGRR _hoops_PPR _hoops_ARPR _hoops_CIPP.
	//

	// _hoops_ACRAH _hoops_ASCA _hoops_HPGR _hoops_ICIH _hoops_IGIR
	int const _hoops_PCRAH = _hoops_CSRGR->window_width;
	int const _hoops_HCRAH = _hoops_CSRGR->window_height;

	// _hoops_GRSH _hoops_AHPH _hoops_AHCR _hoops_AI _hoops_AA _hoops_SR _hoops_RRP?
	int _hoops_ICRAH = _hoops_ISARR ? 1 : 2;

	{
		_hoops_CSRGR->_hoops_GSCR->_hoops_ASCRR(L"depth_peeling allocation");

		// _hoops_IIPP _hoops_PSCA _hoops_HPGR _hoops_SHPR _hoops_IGIR.
		int _hoops_CCRAH = _hoops_CSRGR->render_target->_hoops_IRRP;
		int _hoops_SCRAH = _hoops_CSRGR->render_target->_hoops_CRRP;

#ifdef _hoops_GSRAH
		_hoops_ICRAH = _hoops_RIRAH;
#endif // _hoops_IIRAH

		// _hoops_RSRAH _hoops_RH _hoops_SRHR _hoops_PGRR _hoops_HGAS?
		if (_hoops_CSRGR->_hoops_RHH.w != _hoops_CCRAH ||
			_hoops_CSRGR->_hoops_RHH.h != _hoops_SCRAH ||
			_hoops_CSRGR->_hoops_RHH._hoops_GCH != _hoops_GCH) {
			// _hoops_HRHP _hoops_PIAH _hoops_AI
			for (i = 0 ; i < _hoops_APRRR ; i++) {
				_hoops_HP (_hoops_IPRRR[i]);
				_hoops_HP (_hoops_CPRRR[i]);
			}
			// _hoops_CHSR _hoops_PIAH _hoops_SAAP
			_hoops_HP(_hoops_CSRGR->_hoops_RHH.msaa_target);
			_hoops_CSRGR->_hoops_RHH.w = _hoops_CCRAH;
			_hoops_CSRGR->_hoops_RHH.h = _hoops_SCRAH;
			_hoops_CSRGR->_hoops_RHH._hoops_GCH = _hoops_GCH;
		}

		// _hoops_IIPP _hoops_AHCR _hoops_AI
		for (i = 0 ; i < _hoops_ICRAH; i++) {
			if (!_hoops_IPRRR[i]) {
				_hoops_IA = _hoops_CSRGR->_hoops_GSCR->CreateTexture(_hoops_CCRAH, _hoops_SCRAH, 1,
					H3DTEXUSAGE_RENDERTARGET, _hoops_GCH, &_hoops_IPRRR[i]);
			}
		}

		// _hoops_IIPP _hoops_RGPP _hoops_AI
		for (i = 0 ; i < _hoops_RIRAH ; i++) {
			if (!_hoops_CPRRR[i]) {
				result = _hoops_CSRGR->_hoops_GSCR->CreateTexture(_hoops_CCRAH, _hoops_SCRAH, 1,
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
			if (!_hoops_CSRGR->_hoops_RHH.msaa_target) {
				_hoops_CSRGR->_hoops_RHH.msaa_target = NEW(_hoops_RGIAC)(_hoops_CSRGR, _hoops_CCRAH, _hoops_SCRAH, H3DTEXUSAGE_RENDERTARGET, H3DFMT_A8R8G8B8, _hoops_CSRGR->_hoops_ISGRR);
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
		_hoops_HP (_hoops_CSRGR->_hoops_RHH.msaa_target);

		// _hoops_HSRAH
		_hoops_CSRGR->_hoops_GSCR->_hoops_ASCRR(L"layer 1 depth peeling");
		HD_Std_Depth_Peeling (dc);
		return;
	}

	//
	// _hoops_ICPA _hoops_HGSR
	//

	//_hoops_PRPP _hoops_SIAC _hoops_ACPP _hoops_HIS _hoops_SGS _hoops_GCAC _hoops_HCPH _hoops_CHR _hoops_RCAC _hoops_IS _hoops_SSS
	_hoops_CSRGR->_hoops_GSCR->_hoops_ASCRR(L"depth_peeling");

	// _hoops_IRSC _hoops_ARI _hoops_GPP, _hoops_SRCH _hoops_RCCS-_hoops_ACCS _hoops_PCCS _hoops_AHI.
	H3D_LONG_OPERATION(dc);

	// _hoops_CSH _hoops_RRI _hoops_RSIH-_hoops_ISRAH _hoops_SSRR, _hoops_HIS _hoops_SR _hoops_PAH _hoops_ASCRH _hoops_RH _hoops_CSRAH _hoops_HIGR.
	dc->_hoops_GPSS[dc->_hoops_IASS] = null;

	/* _hoops_PCSA _hoops_SRGS _hoops_HCSS*/
	_hoops_PPRS _hoops_HPRS;
	_hoops_CSRGR->_hoops_GSCR->_hoops_IPRS(&_hoops_HPRS);

	/* _hoops_CHSR _hoops_ICIH */
	H3DViewport _hoops_SSRAH;
	GLint _hoops_SACAC[4];
	glGetIntegerv(GL_VIEWPORT, &_hoops_SACAC[0]);
	_hoops_SSRAH.X = _hoops_SACAC[0];
	_hoops_SSRAH.Y = _hoops_SACAC[1];
	_hoops_SSRAH.Width = _hoops_SACAC[2];
	_hoops_SSRAH.Height = _hoops_SACAC[3];

	// _hoops_PS _hoops_CHR _hoops_HA _hoops_GGR _hoops_ICH _hoops_CCH.
	_hoops_CSRGR->_hoops_RHH.mode = true;
	_hoops_CSRGR->_hoops_RHH.flags = 0;
	_hoops_CSRGR->_hoops_RHH._hoops_ACH = _hoops_ACH;

	_hoops_CPPRR(_hoops_CSRGR, true);

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
	H3DRenderTarget *dummy_buffer = _hoops_ISARR ? _hoops_CSRGR->render_target : (H3DRenderTarget *)_hoops_HPRS._hoops_PGRGR[0];
	H3DRenderTarget *depth_stencil = _hoops_ISARR ? _hoops_CSRGR->depth_stencil : (H3DRenderTarget *)_hoops_HPRS.depth_stencil;


	/* _hoops_RAP _hoops_HGSI _hoops_ACGGR _hoops_PPR _hoops_HCH _hoops_SRHR. */
	_hoops_CSRGR->_hoops_GSCR->_hoops_GPAP(dummy_buffer, depth_stencil);
 	
	_hoops_CSRGR->_hoops_GSCR->_hoops_ASCRR(L"dp render to stencil");
	{
		_hoops_RRHRR(_hoops_CSRGR, 0x00FF); 
		_hoops_CSRGR->_hoops_GSCR->Clear(H3DCLEAR_STENCIL, 0, 1.0f, _hoops_SRIH);
	
		_hoops_CSRGR->_hoops_RHH._hoops_PPSP = true;
		/* _hoops_PGSA _hoops_CRGR _hoops_RH _hoops_APSP _hoops_SRHR _hoops_IS _hoops_RPR _hoops_RH _hoops_PHI _hoops_IIGR _hoops_IACH _hoops_GRR _hoops_AIR
		   _hoops_HRGR _hoops_RHIAA _hoops_HPP _hoops_CPHP _hoops_RRH. */
		_hoops_RPAP (_hoops_CSRGR, false);
		ENSURE_TRANSPARENCY (_hoops_CSRGR, false);
		_hoops_ICHH(_hoops_CSRGR, true);
		_hoops_RRHRR(_hoops_CSRGR, 0x007F); 
		_hoops_PAHRR(
			_hoops_CSRGR,
			H3DSTENCILOP_KEEP, /* _hoops_AA _hoops_ISAP _hoops_RPP _hoops_APSP _hoops_RPGP _hoops_ISHS (_hoops_PGGAC _hoops_CCA _hoops_APSP _hoops_RPGP _hoops_PSAP) */
			H3DSTENCILOP_KEEP, /* _hoops_AA _hoops_ISAP _hoops_RPP _hoops_HCH _hoops_RPGP _hoops_ISHS */
			H3DSTENCILOP_INCR  /* _hoops_GPISR _hoops_APSP _hoops_SRHR _hoops_RPP _hoops_HCH _hoops_RPGP _hoops_PCGGR */
		);
		/* _hoops_RGAR _hoops_GPISR _hoops_APSP _hoops_CGPR _hoops_ASSA _hoops_IRS _hoops_HSPH _hoops_ISPH */
		_hoops_SRHRR(_hoops_CSRGR, H3DCMP_EQUAL); 
		_hoops_HRHRR(_hoops_CSRGR, _hoops_SRIH);
		_hoops_RGSS(_hoops_CSRGR, _hoops_SRIH);

		
		/* _hoops_CAAA _hoops_HCH _hoops_IS _hoops_IRS _hoops_APSP _hoops_RPR _hoops_IIGR _hoops_RRH _hoops_RSSI _hoops_HPGR _hoops_GRR _hoops_AIR. */

		/* _hoops_PPSI 1'_hoops_GRI _hoops_CRGR _hoops_RH _hoops_AAPA _hoops_IGRH (_hoops_GHCA _hoops_SHH _hoops_GCGSP _hoops_SPHR _hoops_HPP _hoops_HSPH _hoops_PGHH),
		   _hoops_PPR 0'_hoops_GRI _hoops_CRGR _hoops_RH _hoops_GSSC _hoops_SIH */
		//_hoops_HGPGA->_hoops_ICRI->_hoops_CAAP(_hoops_GPCAC, 0, 1.0f, _hoops_RPCAC);

		_hoops_CSRGR->_hoops_RSHH = _hoops_CCC;

		// _hoops_GISP _hoops_IS _hoops_APSP _hoops_RGAR
		HD_Draw_Deferred_3D_Geometry (list, true);
		_hoops_CSRGR->_hoops_RHH._hoops_PPSP = false;
		_hoops_SSRAH = _hoops_CSRGR->_hoops_CSC->_hoops_CSAA;
	}
	

	//
	// _hoops_RGHSP _hoops_ICH _hoops_HAPR. _hoops_AGHP _hoops_IGAAH.
	//

	// _hoops_IPRP _hoops_APSP 
	_hoops_PAHRR(_hoops_CSRGR, H3DSTENCILOP_KEEP, H3DSTENCILOP_KEEP, H3DSTENCILOP_KEEP);

	// _hoops_IPRP _hoops_HAIR _hoops_PPR _hoops_HCH _hoops_CIGCP
	_hoops_RPAP (_hoops_CSRGR, true);
	_hoops_GPRP (_hoops_CSRGR, H3DMASK_RGBA);
	ENSURE_DEPTH_MASK (_hoops_CSRGR, true);
	_hoops_PISP (_hoops_CSRGR, true);

	/* _hoops_HPPP _hoops_IGAAH */
	for (i=0; i<_hoops_RIRAH; i++) {
		void *			_hoops_CGAAH = null;
		int				result = 0;

		// _hoops_CRSR _hoops_AHCR _hoops_HH _hoops_RGR _hoops_GHIR?
		int				z = i % _hoops_ICRAH;

		// _hoops_IPCP _hoops_CGHI _hoops_ASAH _hoops_HRGR _hoops_HA _hoops_RGR _hoops_SPR.
		_hoops_PIRAH = i;

		/* _hoops_ASSS _hoops_GRR _hoops_AIR _hoops_IS _hoops_SHH _hoops_RHIAA _hoops_RGAR _hoops_GAR _hoops_AHPH _hoops_IACH _hoops_GAR _hoops_SR _hoops_SGAAH */
		_hoops_SRHRR(_hoops_CSRGR, H3DCMP_LESS);
		_hoops_HRHRR(_hoops_CSRGR, (unsigned int)(i | 0x80));
		_hoops_RGSS(_hoops_CSRGR, 0x00FF);

		if (_hoops_AIRAH > 0)
			_hoops_CGAAH = _hoops_AACGH (list->nr, false);

		if (_hoops_ACH) {

			//
			// _hoops_GRAAH _hoops_RIH _hoops_GRP _hoops_RIAP.
			//

			// _hoops_CAAP _hoops_AHCR _hoops_IS _hoops_RSSR.
			_hoops_CSRGR->_hoops_GSCR->_hoops_GPAP(_hoops_IPRRR[z], depth_stencil);
			_hoops_CSRGR->_hoops_GSCR->Clear(H3DCLEAR_TARGET | H3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);

			// _hoops_CAAP _hoops_GISH _hoops_IS _hoops_CIGC
			_hoops_CSRGR->_hoops_GSCR->_hoops_GPAP(_hoops_CPRRR[i]);
			_hoops_CSRGR->_hoops_GSCR->Clear(H3DCLEAR_TARGET, 0x00000000, 0, 0);

			// _hoops_RAP _hoops_AHCR _hoops_ISSC _hoops_GPP _hoops_ACGGR 1
			_hoops_CSRGR->_hoops_GSCR->_hoops_GPAP(_hoops_CPRRR[i], depth_stencil, _hoops_IPRRR[i]);
			
		 	_hoops_PPHH(_hoops_CSRGR, _hoops_SSRAH.X, _hoops_SSRAH.Y, _hoops_SSRAH.Width, _hoops_SSRAH.Height);

			// _hoops_PGII _hoops_IGAAH _hoops_GGI _hoops_HCH
			_hoops_CSRGR->_hoops_RHH.flags = H3DID_DEPTH_WRITING;

			// _hoops_PGPR _hoops_IGAAH _hoops_RAS _hoops_RH _hoops_SRS _hoops_SGH _hoops_RH _hoops_HCH _hoops_IS _hoops_RRAAH
			if (i)
				_hoops_CSRGR->_hoops_RHH.flags |= H3DID_DEPTH_PEELING;

			// _hoops_GISP _hoops_RH _hoops_RRH _hoops_CPAP
			_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
			HD_Draw_Deferred_3D_Geometry (list, false);
		}
		else {

			H3D_TRACE(_hoops_CSRGR, "dp two pass");

			{
				H3D_TRACE( _hoops_CSRGR, "dp colour" );

				//
				// _hoops_CHPR 1: _hoops_PCSS _hoops_GISH
				// 

				// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_GRP _hoops_RRGS
				if (_hoops_ISARR) {
					// _hoops_GCRR _hoops_RRGS _hoops_SAAP _hoops_SCGR
					_hoops_CSRGR->_hoops_GSCR->_hoops_GPAP(_hoops_CSRGR->_hoops_RHH.msaa_target, depth_stencil);
				}
				else {
					// _hoops_GCRR _hoops_GISH _hoops_SAAP _hoops_SCGR
					_hoops_CSRGR->_hoops_GSCR->_hoops_GPAP(_hoops_CPRRR[i], depth_stencil);
				}

		 		// _hoops_CICR _hoops_GGI _hoops_GISH _hoops_RH _hoops_SRS _hoops_GHIR, _hoops_RRAAH _hoops_GPP _hoops_SPHR _hoops_IGAAH
				_hoops_CSRGR->_hoops_RHH.flags = i ? H3DID_DEPTH_PEELING : 0;

				// _hoops_CAAP _hoops_IS _hoops_RRH/_hoops_RSSR
				_hoops_CSRGR->_hoops_GSCR->Clear(H3DCLEAR_TARGET | H3DCLEAR_ZBUFFER, 0, 1.0f, 0);

				_hoops_PPHH(_hoops_CSRGR, _hoops_SSRAH.X, _hoops_SSRAH.Y, _hoops_SSRAH.Width, _hoops_SSRAH.Height);

				// _hoops_GISP _hoops_RH _hoops_RRH _hoops_CPAP
				_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
				HD_Draw_Deferred_3D_Geometry (list, false);

				if (_hoops_ISARR) {
					// _hoops_PGIP _hoops_PPR _hoops_ASAC _hoops_GISH
					_hoops_HGIP(_hoops_CSRGR, _hoops_CSRGR->_hoops_RHH.msaa_target, _hoops_CPRRR[i]);
				}

			}

			{
				H3D_TRACE( _hoops_CSRGR, "dp depth" );

				//
				// _hoops_CHPR 2: _hoops_PCSS _hoops_HCH
				//

				if (_hoops_ISARR) {
					// _hoops_GCRR _hoops_RRGS _hoops_SAAP _hoops_SCGR
					_hoops_CSRGR->_hoops_GSCR->_hoops_GPAP(_hoops_CSRGR->_hoops_RHH.msaa_target, depth_stencil);
				}
				else {
					// _hoops_GCRR _hoops_AHCR _hoops_HH _hoops_SCGR
					_hoops_CSRGR->_hoops_GSCR->_hoops_GPAP(_hoops_IPRRR[z], depth_stencil);
				}

		 		_hoops_PPHH(_hoops_CSRGR, _hoops_SSRAH.X, _hoops_SSRAH.Y, _hoops_SSRAH.Width, _hoops_SSRAH.Height);

				// _hoops_IISH _hoops_HCH, _hoops_RRAAH _hoops_GAR _hoops_PRAR _hoops_RPP _hoops_ARP _hoops_ARRS
				_hoops_CSRGR->_hoops_RHH.flags |= H3DID_DEPTH_WRITING;

				// _hoops_CAAP _hoops_IS _hoops_RSSR. _hoops_CAIP'_hoops_RA _hoops_RRP _hoops_IS _hoops_ASAR-_hoops_SCAC _hoops_SSH _hoops_SRHR _hoops_CR _hoops_CRGP-_hoops_SASPR _hoops_HCH _hoops_RPGP _hoops_GRS _hoops_IPHR _hoops_IH _hoops_IHHH.
				_hoops_CSRGR->_hoops_GSCR->Clear(H3DCLEAR_TARGET, 0xff000000, 1.0f, 0);

				// _hoops_GISP _hoops_RH _hoops_RRH _hoops_CPAP
				_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
				HD_Draw_Deferred_3D_Geometry (list, false);

				if (_hoops_ISARR) {
					// _hoops_PGIP _hoops_PPR _hoops_ASAC _hoops_AHCR
					_hoops_HGIP(_hoops_CSRGR, _hoops_CSRGR->_hoops_RHH.msaa_target, _hoops_IPRRR[z]);
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
		_hoops_CSRGR->_hoops_RHH._hoops_HPRRR = _hoops_IPRRR[z];
	}

	// _hoops_CSH _hoops_RPIP _hoops_ICH
	_hoops_CSRGR->_hoops_RHH.mode = false;
	_hoops_CSRGR->_hoops_RHH.flags = 0;
	_hoops_CSRGR->_hoops_RHH._hoops_HPRRR = null;

	{
		//
		// _hoops_PRAAH _hoops_RH _hoops_IGAAH _hoops_CRGR _hoops_PCCP _hoops_CSCR.
		//

		H3D_TRACE( _hoops_CSRGR, "dp draw layers" );

		// _hoops_IPRP _hoops_AISH _hoops_PPR _hoops_HCH _hoops_APSP _hoops_ISSGR.
		_hoops_CSRGR->_hoops_GSCR->_hoops_CHRS(&_hoops_HPRS);

		/* _hoops_CPRP _hoops_CCAH _hoops_RRRH _hoops_IAPR _hoops_GIGR _hoops_IS _hoops_HGCR _hoops_RH _hoops_GHPP */
		_hoops_PPRP (_hoops_CSRGR, H3DBLEND_SRCALPHA, H3DBLEND_INVSRCALPHA);
		ENSURE_TRANSPARENCY (_hoops_CSRGR, true);  
		_hoops_ICHH (_hoops_CSRGR, false);

		// _hoops_SSSA _hoops_CARP _hoops_PCRR _hoops_IH _hoops_HH
		_hoops_ACCRR = (_hoops_IAAIP) / (float)_hoops_PCRAH;
		_hoops_PCCRR = (_hoops_IAAIP + (width-1)) / (float)_hoops_PCRAH;

		_hoops_ISPI = (_hoops_CAAIP) / (float) _hoops_HCRAH;
		_hoops_CSPI = (_hoops_CAAIP + height) / (float) _hoops_HCRAH;

		// _hoops_GISP _hoops_HCR _hoops_IGAAH _hoops_GGR _hoops_PIIA _hoops_AGR.
		_hoops_GPRP (_hoops_CSRGR, (_hoops_CSRGR->_hoops_SH.mode ? H3DMASK_RGBA : H3DMASK_RGB));
		for (i=_hoops_PIRAH; i>=0; i--) {
			_hoops_CSRGR->_hoops_GSCR->_hoops_GHIP(_hoops_CSRGR, _hoops_CPRRR[i], _hoops_IAAIP, _hoops_CAAIP, (width-1), (height-1), _hoops_ACCRR, _hoops_ISPI, _hoops_PCCRR, _hoops_CSPI);
		}

		// _hoops_IPRP _hoops_CPRP _hoops_CCH
		ENSURE_TRANSPARENCY (_hoops_CSRGR, false);  
	}

#ifdef _hoops_GSRAH

	{
		H3D_TRACE( _hoops_CSRGR, "dp debug layers" );

		//
		// _hoops_PPSRR _hoops_GISS _hoops_RRGR
		//

		// _hoops_HRAAH _hoops_IGAAH _hoops_GGSR _hoops_ARHI _hoops_RH _hoops_CRRPA
		const int _hoops_IRAAH = (extent->right - extent->left)/(_hoops_RIRAH*2);

		for (i=_hoops_PIRAH; i>=0; i--) {
			_hoops_CSRGR->_hoops_GSCR->_hoops_GHIP(_hoops_CSRGR, _hoops_CPRRR[i], _hoops_IAAIP + i * _hoops_IRAAH, _hoops_CAAIP, _hoops_IRAAH, _hoops_IRAAH);
		}

		for (i=0; i < _hoops_ICRAH; ++i) {
			_hoops_CSRGR->_hoops_GSCR->_hoops_GHIP(_hoops_CSRGR, _hoops_IPRRR[i], _hoops_IAAIP + i * _hoops_IRAAH, _hoops_CAAIP + _hoops_IRAAH, _hoops_IRAAH, _hoops_IRAAH);
		}
	}

#endif // _hoops_IIRAH

	for (i = 0 ; i < _hoops_CIGP ; i++) {
		_hoops_ASRP(_hoops_CSRGR, i);
	}
	/* _hoops_HCR _hoops_CPHR _hoops_CCA _hoops_RGR _hoops_HIGR _hoops_IIGR _hoops_RRH _hoops_IGCGA */
	HD_Free_Deferred_3D_Geometry (list);

} //_hoops_RSGR _hoops_API '_hoops_HCH _hoops_ICH'


/*
 * _hoops_PGAA
 */
void _hoops_IAHGC (Display_Context alter * dc) 
{
	HOGLData alter *_hoops_CSRGR = OGLD (dc);

#if 0	
	GLint _hoops_RCHA[3];
	glGetIntegerv (GL_RED_BITS, _hoops_RCHA);
	glGetIntegerv (GL_BLUE_BITS, _hoops_RCHA + 1);
	glGetIntegerv (GL_GREEN_BITS, _hoops_RCHA + 2);
	_hoops_CSRGR->_hoops_SAHGC = _hoops_RCHA[0] + _hoops_RCHA[1] + _hoops_RCHA[2];
#endif
	dc->_hoops_PGCC._hoops_HHPGH =
		dc->_hoops_PGCC._hoops_AAPSR = 1L << 24;
	dc->_hoops_PGCC._hoops_APASR = 0;

	dc->flags |= _hoops_IIPIP;

	/* _hoops_GPHGC _hoops_AAPI, "_hoops_RPHGC" */
	glGetIntegerv (GL_STENCIL_BITS, &_hoops_CSRGR->_hoops_APHGC);
	_hoops_CSRGR->_hoops_PPHGC = _hoops_CSRGR->_hoops_APHGC > 0;

	_hoops_CSRGR->_hoops_GAGRR = false;

	glGetIntegerv (GL_DEPTH_BITS, &_hoops_CSRGR->_hoops_IGARR);

	if (_hoops_CSRGR->_hoops_IGARR > 24)
		_hoops_CSRGR->_hoops_IGARR = 24;

#ifdef NUTCRACKER
	_hoops_CSRGR->_hoops_CGARR = ((__int64)1UL << _hoops_CSRGR->_hoops_IGARR) - 1;
#else
	_hoops_CSRGR->_hoops_CGARR = (0x1 << _hoops_CSRGR->_hoops_IGARR) - 1;
#endif

	dc->flags |= _hoops_RAAGH;
	dc->_hoops_PGCC._hoops_HASHP = _hoops_CSRGR->_hoops_IGARR;
	dc->_hoops_PGCC._hoops_PASHP = (float) (_hoops_CSRGR->_hoops_CGARR);
	if (dc->_hoops_PGCC._hoops_HASHP > 0) 
		dc->flags &= ~_hoops_AASHP;
	else 
		dc->flags |= _hoops_AASHP;

	dc->_hoops_PGCC._hoops_HGCC = 15;
	glGetIntegerv (GL_MAX_CLIP_PLANES, &_hoops_CSRGR->_hoops_GAH);
	/*_hoops_HGPGA->_hoops_ICCC = 0;*/
	dc->_hoops_PGCC._hoops_ACPGH = _hoops_CSRGR->_hoops_GAH;

	// _hoops_SAH _hoops_SISS _hoops_AGRAH
	_hoops_CSRGR->_hoops_ACGH._hoops_CGGI = 0x00007fff;
	_hoops_CSRGR->_hoops_ACGH._hoops_GRGI = 0x0000ffff;
	glGetIntegerv (GL_MAX_TEXTURE_SIZE, (GLint *) &_hoops_CSRGR->_hoops_ACGH._hoops_PCGH);
	glGetIntegerv (GL_MAX_TEXTURE_SIZE, (GLint *) &_hoops_CSRGR->_hoops_ACGH._hoops_HCGH);
	dc->_hoops_PGCC._hoops_PCPGH = _hoops_AHIA(_hoops_CSRGR->_hoops_ACGH._hoops_PCGH, _hoops_CSRGR->_hoops_ACGH._hoops_HCGH);

	if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_TEXTURE_SIZE_OFF_BY_ONE)) {
		_hoops_CSRGR->_hoops_ACGH._hoops_PCGH--;
		_hoops_CSRGR->_hoops_ACGH._hoops_HCGH--;
	}

	glGetIntegerv (GL_MAX_COLOR_ATTACHMENTS_EXT, &_hoops_CSRGR->_hoops_GRAP);

	GLint _hoops_GICRC[2];
	glGetIntegerv (GL_POINT_SIZE_RANGE, _hoops_GICRC);
	_hoops_CSRGR->_hoops_IHSC = _hoops_GICRC[1];

	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &_hoops_CSRGR->_hoops_GSSGC);

	glGetIntegerv(GL_MAX_SAMPLES_EXT, &_hoops_CSRGR->_hoops_APCAC);

	{
		/* _hoops_IPHGC _hoops_CPHGC _hoops_HRS _hoops_RH _hoops_CGGPR _hoops_PPR _hoops_AHPA _hoops_SPHGC
		 * _hoops_APP _hoops_HPP _hoops_CGPR _hoops_GHHGC _hoops_HRGR _hoops_PPP.  _hoops_GHAP _hoops_SIPGR'_hoops_RA _hoops_GCRHA
		 * _hoops_GII _hoops_GPPRH _hoops_RHHGC _hoops_SGS _hoops_IIH _hoops_HRGR _hoops_IRS _hoops_AHPA _hoops_CGPR _hoops_GHHGC
		 * _hoops_HRGR _hoops_GRGR. */
		float _hoops_CAHGC[2] = {1, 2};
		glGetFloatv(GL_LINE_WIDTH_RANGE, _hoops_CAHGC);
		_hoops_CSRGR->_hoops_AHHGC = (int) _hoops_CAHGC[1];
	}

	if (_hoops_CSRGR->_hoops_PHHGC)
		dc->_hoops_PGCC.flags |= _hoops_CPPGH;
	else
		dc->_hoops_PGCC.flags &= ~_hoops_CPPGH;

	dc->_hoops_PGCC.flags |= _hoops_SPPGH;
	dc->_hoops_PGCC.flags |= _hoops_PHPGH;
	dc->_hoops_PGCC.flags |= _hoops_RPPGH;
	dc->_hoops_PGCC.flags |= _hoops_PSSHP;
	dc->_hoops_PGCC.flags |= _hoops_ASSHP;
	dc->_hoops_PGCC.flags |= _hoops_ISSHP;
	dc->flags |= _hoops_SRAGH;

	dc->_hoops_PGCC._hoops_AHAGH = _hoops_APRRR;

#ifdef GLX_DRIVER
	dc->_hoops_PGCC._hoops_CHHSR = _hoops_RCPGA;
#if 0
	{
		GLboolean _hoops_SASSR=GL_TRUE;
		glGetBooleanv (GL_DOUBLEBUFFER, &_hoops_SASSR);

		if (_hoops_SASSR)
			dc->_hoops_PGCC._hoops_CHHSR = _hoops_RCPGA;
		else
			dc->_hoops_PGCC._hoops_CHHSR = _hoops_SHHSR;
	}
#endif
#endif

}

void _hoops_ACIRH(Display_Context alter * dc) {
	HOGLData *_hoops_CSRGR = OGLD(dc);

	// _hoops_HRCI _hoops_RH _hoops_AAIP _hoops_IHAH
	invalidate_cache(_hoops_CSRGR);

	_hoops_HP(_hoops_CSRGR->_hoops_RHH.msaa_target);

	// _hoops_PPGGR _hoops_HCIRH
	_hoops_HP(_hoops_CSRGR->_hoops_II._hoops_CRPP);

	_hoops_CSRGR->_hoops_GSCR->_hoops_SGSRR(dc);
	_hoops_HP(_hoops_CSRGR->_hoops_GSCR);
	_hoops_HP(_hoops_CSRGR->render_target);
	_hoops_HP(_hoops_CSRGR->depth_stencil);
	_hoops_HP(_hoops_CSRGR->fbo);
	_hoops_HP(_hoops_CSRGR->_hoops_AGIAC);
	_hoops_HP(_hoops_CSRGR->_hoops_PGIAC);
	_hoops_HP(_hoops_CSRGR->_hoops_PPCAC);
}

void _hoops_SPSGC(Display_Context const * dc) 
{
	HOGLData alter *_hoops_CSRGR = OGLD (dc);
	//_hoops_HPCAC *_hoops_CSRI = _hoops_IRAP;
	//_hoops_SCSH _hoops_HAS;
	
	// _hoops_SP _hoops_GH _hoops_AIRI _hoops_CPCI
	HD_Purge_Display_Lists(dc->_hoops_GHRI, null, null); 

	if (dc->_hoops_GHRI->_hoops_RGAGR)
		_hoops_SSRGR(dc);

	if (_hoops_CSRGR->_hoops_SISGC) {
		glDetachShader (_hoops_CSRGR->_hoops_SISGC, _hoops_CSRGR->_hoops_GCSGC);
		glDeleteShader (_hoops_CSRGR->_hoops_GCSGC);
		glDeleteProgram (_hoops_CSRGR->_hoops_SISGC);
		_hoops_CSRGR->_hoops_SISGC = 0;
		_hoops_CSRGR->_hoops_GCSGC = 0;
	}

	// _hoops_AHH: _hoops_HHIGR'_hoops_GRI _hoops_SSRR _hoops_IH _hoops_RH _hoops_SISS _hoops_IS _hoops_SHH _hoops_CSSRH _hoops_ARPP _hoops_SSSRH, _hoops_GGR _hoops_PGAP _hoops_AGIR
	// _hoops_RGR _hoops_SHPP _hoops_GGGAH (_hoops_RGGAH, _hoops_ASSP'_hoops_RA _hoops_AGCGR _hoops_PPGS). _hoops_AGGAH _hoops_SGS _hoops_HPP _hoops_PGGAH _hoops_ARI.
	if ( _hoops_CSRGR->post && _hoops_CSRGR->_hoops_II.depth_texture )
		_hoops_CSRGR->post->_hoops_HAAP( &_hoops_CSRGR->_hoops_II.depth_texture );

	_hoops_HP(_hoops_CSRGR->post);
	_hoops_HP(_hoops_CSRGR->_hoops_IPCAC);
	FREE(_hoops_CSRGR->_hoops_CSC, H3DCache);
	_hoops_CSRGR->_hoops_CSC = null;

#ifdef _hoops_SPARH
	if (_hoops_RHARH)
	{
		_hoops_RHARH->DeleteItems();
		delete _hoops_RHARH;
		_hoops_RHARH = null;
	}
#endif
}


local bool _hoops_RGPRH( HOGLData *_hoops_CSRGR, _hoops_CGGRR mode, int _hoops_AGPRH )
{
	ASSERT(mode != _hoops_SGGRR);

	// _hoops_GSCA _hoops_AHCI _hoops_ISAR _hoops_PSGC.
	if ( _hoops_AGPRH < 0 )
		// _hoops_SGAA _hoops_HRGR _hoops_AIAA _hoops_IGPR.
		_hoops_AGPRH = 4;
	else if ( _hoops_AGPRH <= 1 )
		// _hoops_GHPA _hoops_PPR _hoops_SPR _hoops_PHGA _hoops_SPR _hoops_ISAR, _hoops_HAS._hoops_IAS. _hoops_PSP _hoops_ARHP.
		_hoops_AGPRH = 0;

	// _hoops_GSCA _hoops_AHCI _hoops_CCH _hoops_PSGC.
	if ( _hoops_AGPRH == 0 )
		mode = _hoops_GRGRR;

	// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HSGRR, _hoops_SGPRH _hoops_PCPA _hoops_GSIA _hoops_GCGH _hoops_SR _hoops_HS.
	const unsigned long _hoops_GRPRH = _hoops_AGPRH;
	if ( mode != _hoops_GRGRR ) {

		// _hoops_CGP _hoops_SR _hoops_HGRC _hoops_GSIA _hoops_RRGS _hoops_PPR _hoops_SR _hoops_PAH'_hoops_RA _hoops_HS _hoops_SCH, _hoops_IIPGA _hoops_IS _hoops_ICPP
		if ( _hoops_CSRGR->_hoops_APCAC <= 1 && mode == _hoops_SRAP ) {
			mode = _hoops_AHRS;
		}
	}

	// _hoops_CGP _hoops_SR _hoops_CHR _hoops_AIAH _hoops_GGR _hoops_RGR _hoops_CCH _hoops_CCA _hoops_RGR _hoops_ISAR _hoops_RPR.., _hoops_ISAP _hoops_IS _hoops_AA.
	if ( mode == _hoops_CSRGR->_hoops_CRAP && _hoops_AGPRH == _hoops_CSRGR->_hoops_CSGRR )
		return true;

	// _hoops_GCIH _hoops_HPIAA _hoops_SR _hoops_PAH _hoops_SGH _hoops_RH _hoops_PSHR _hoops_PHI _hoops_IIGR _hoops_IGPR _hoops_GAR _hoops_AAPR _hoops_HGRC.
	int _hoops_CAP = _hoops_AGPRH;

	// _hoops_HHPC _hoops_SR'_hoops_GCPP _hoops_PSASA _hoops_HCSS
	_hoops_RSARH(_hoops_CSRGR);

	// _hoops_CPCS _hoops_GPPC _hoops_CR _hoops_SSIA _hoops_RRP _hoops_PRPRH _hoops_IH _hoops_RH _hoops_CCAH _hoops_ARHP _hoops_CCH
	_hoops_CSRGR->_hoops_GSCR->_hoops_IGSRR(_hoops_CSRGR);

	// _hoops_HR _hoops_HPCS
	bool _hoops_IA = false;

	// _hoops_HSRR _hoops_SSCH
	unsigned int const _hoops_HRPRH = _hoops_CSRGR->window_width;
	unsigned int const _hoops_IRPRH = _hoops_CSRGR->window_height;
	
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
			_hoops_IA = _hoops_ISARH(_hoops_CSRGR, _hoops_HRPRH * width_scale, _hoops_IRPRH * _hoops_IISHP, 0);
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
			_hoops_CSRGR->_hoops_HSAA = width_scale;
			_hoops_CSRGR->_hoops_ISAA = _hoops_IISHP;
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
			_hoops_IA = _hoops_ISARH(_hoops_CSRGR, _hoops_HRPRH, _hoops_IRPRH, _hoops_CAP);

			if ( !_hoops_IA ) {
				HE_WARNING (HEC_DX9_DRIVER, HEC_DX9_DRIVER,
					"Could not create rendertargets for multisample antialiasing.");
				mode = _hoops_GRGRR;
			}
		}

		// _hoops_CSH _hoops_ICPP
		_hoops_CSRGR->_hoops_HSAA = 1;
		_hoops_CSRGR->_hoops_ISAA = 1;
	}

	// _hoops_HHCS _hoops_PSP _hoops_ARHP _hoops_RPP _hoops_HGRC.
	if ( mode == _hoops_GRGRR ) {
		_hoops_CAP = 0;
		_hoops_IA = _hoops_ISARH(_hoops_CSRGR, _hoops_HRPRH, _hoops_IRPRH, 0);

		if ( !_hoops_IA ) {
			HE_ERROR (HEC_DX9_DRIVER, HEC_DX9_DRIVER,
				"Could not create driver rendertargets.");
		}

		// _hoops_CSH _hoops_ICPP
		_hoops_CSRGR->_hoops_HSAA = 1;
		_hoops_CSRGR->_hoops_ISAA = 1;
	}

	if ( _hoops_IA ) {

		//
		// _hoops_SIPR _hoops_CPS _hoops_HRPP.
		// 

		// _hoops_RAP _hoops_RGR _hoops_SRS _hoops_HIS _hoops_SAAP _hoops_HGISR _hoops_CACH _hoops_SCH. _hoops_SAH _hoops_HGRC _hoops_IGPR _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_HGCR _hoops_AAPRH
		// _hoops_RCSAR _hoops_PAAP _hoops_PAPRH _hoops_SR _hoops_PAH'_hoops_RA _hoops_GCGH _hoops_RH _hoops_CCH _hoops_RH _hoops_RPRGR _hoops_SSGRR _hoops_IH.
		_hoops_CSRGR->_hoops_CRAP = mode;
		_hoops_CSRGR->_hoops_ISGRR = _hoops_CAP;
		_hoops_CSRGR->_hoops_CSGRR = _hoops_AGPRH;

		// _hoops_HRHI _hoops_HRPRA.
		Display_Context alter *_hoops_HAPRH = (Display_Context alter *)_hoops_CSRGR->dc;
		_hoops_HAPRH->_hoops_PGCC.flags |= _hoops_PAGIP;
		_hoops_HAPRH->_hoops_PGCC.flags &= ~_hoops_GIHSR;

		// _hoops_SPAA _hoops_ARP _hoops_AHCS _hoops_PPR _hoops_ICIH _hoops_IS _hoops_RSIR _hoops_CSCR.
		_hoops_CSRGR->_hoops_GSCR->_hoops_GPAP(_hoops_CSRGR->render_target, _hoops_CSRGR->depth_stencil);
		_hoops_HHRS(_hoops_CSRGR, 0, 0, _hoops_HRPRH, _hoops_IRPRH);
	}

	// _hoops_AP
	return _hoops_IA;
}



/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_RHAA _hoops_PHSPR
*****************************************************************************
*****************************************************************************/
/*
* _hoops_PGAA. _hoops_PHIC _hoops_PGAP _hoops_HCH _hoops_AGI _hoops_IS _hoops_AA.
*/
void _hoops_RCCRH( HOGLData *_hoops_CSRGR )
{
	// _hoops_HR _hoops_PSP _hoops_AGI _hoops_CCGR _hoops_SR'_hoops_RISP _hoops_GIPCR _hoops_SR _hoops_PAH _hoops_AA _hoops_CAPR.
	_hoops_CSRGR->_hoops_II._hoops_SGAP = 0;

	// _hoops_ACCRH _hoops_HCH-_hoops_AAR _hoops_AGI
	int _hoops_HHAIR = 0;
	if ( _hoops_CSRGR->dc->options._hoops_PPSSP )
		_hoops_HHAIR |= _hoops_CGPP;
	if ( _hoops_CSRGR->dc->options._hoops_RPSSP )
		_hoops_HHAIR |= _hoops_CRHP;
	if ( _hoops_CSRGR->dc->options._hoops_APSSP )
		_hoops_HHAIR |= _hoops_AHHP;
	if ( false )
		_hoops_HHAIR |= _hoops_GGCRR;
	if ( _hoops_CSRGR->dc->options._hoops_HPSSP )
		_hoops_HHAIR |= _hoops_GIHP;
	if ( _hoops_CSRGR->_hoops_IHGRR && _hoops_CSRGR->_hoops_IHGRR->format == _hoops_PCCRH )
		_hoops_HHAIR |= _hoops_AGCRR;

	// _hoops_ASC _hoops_CHR _hoops_HAR _hoops_APIP _hoops_CCGR _hoops_RAS _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_HIRA.
	_hoops_CSRGR->_hoops_II._hoops_CCCS = 0.0f;
	_hoops_CSRGR->_hoops_II._hoops_ICCS = 0.0f;

	// _hoops_CGP _hoops_AGI _hoops_CHR _hoops_HGRC _hoops_PPR _hoops_APP
	//_hoops_RPP ( _hoops_AGI && _hoops_HGPGA->_hoops_GSGAH > 1 && _hoops_HGPGA->_hoops_ARAP ) {
	if ( _hoops_HHAIR && _hoops_CSRGR->_hoops_GRAP > 1 ) {
		_hoops_CSRGR->_hoops_II._hoops_SGAP = _hoops_HHAIR;
	}
}


/*
* _hoops_SRAC
*/
void _hoops_PCPGR (Net_Rendition const &nr)
{
	HOGLData alter *_hoops_CSRGR = OGLNRD (nr);

	H3D_TRACE(_hoops_CSRGR, "postprocess_picture");

	ENSURE_TRANSPARENCY(_hoops_CSRGR, false);
	_hoops_APHH(_hoops_CSRGR, 0.0f, 1.0f);

	//
	// _hoops_GHRRR _hoops_SRS.
	//

	// _hoops_CGP _hoops_SR _hoops_HS _hoops_HCCRH _hoops_IS _hoops_SGH, _hoops_SGH _hoops_SCH
	if ( _hoops_CSRGR->_hoops_HHRRR._hoops_RHRRR && _hoops_CSRGR->_hoops_HHRRR._hoops_AHRRR ) {
		//_hoops_SIGP: _hoops_CPCAC( *_hoops_HGPGA);
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

	if ( _hoops_CSRGR->dc->options._hoops_RGSH )
		_hoops_CRSRH = true;

	// _hoops_AHH: _hoops_RGHSP _hoops_SRSRH _hoops_GCA _hoops_RGR
	if ( _hoops_CSRGR->_hoops_II._hoops_SGAP & _hoops_RGCRR )
		_hoops_CRSRH = true;

	// _hoops_CGIP _hoops_GGSR _hoops_CAS _hoops_IS _hoops_CCGSP _hoops_IS
	if ( _hoops_CRSRH ) {

		_hoops_GPRP(_hoops_CSRGR, H3DMASK_RGBA);

		// _hoops_SIAP _hoops_HIRA _hoops_GAR _hoops_HCGP _hoops_IH _hoops_RHAA _hoops_AGI
		if ( H3DTexture *_hoops_GASRH = _hoops_CSRGR->post->_hoops_IAAP( 
			_hoops_CSRGR->render_target->_hoops_IRRP, _hoops_CSRGR->render_target->_hoops_CRRP, _hoops_CSRGR->render_target->_hoops_GSPP) )
		{

			// _hoops_HSRR _hoops_ICPP, _hoops_RGRR _hoops_RH _hoops_CCGSP. _hoops_HSRR _hoops_RRGS, _hoops_AAIR _hoops_PIRC _hoops_IS _hoops_HGCR _hoops_GSIA _hoops_PRRHP.
			H3DTEXTUREFILTERTYPE filter = (_hoops_CSRGR->_hoops_CRAP == _hoops_AHRS) ? 
				H3DTEXF_LINEAR : H3DTEXF_NONE;

			// _hoops_RASRH _hoops_HII _hoops_HIRA (_hoops_GCAS _hoops_RRGS _hoops_PAR _hoops_ICPP) _hoops_IS _hoops_HH
			_hoops_HGIP(_hoops_CSRGR, _hoops_CSRGR->render_target, _hoops_GASRH, filter);

			// _hoops_IGPP _hoops_RH _hoops_HIRA _hoops_HH _hoops_IPSH _hoops_AGI _hoops_IS _hoops_RH _hoops_SRGS _hoops_SAAP
			_hoops_ISCH( _hoops_CSRGR, _hoops_GASRH, _hoops_CSRGR->render_target );

			// _hoops_AASRH _hoops_HH _hoops_IH _hoops_HCCRH
			if ( _hoops_CSRGR->_hoops_II._hoops_SGAP & _hoops_RGCRR ) {
				_hoops_CSRGR->_hoops_HHRRR._hoops_AHRRR = _hoops_GASRH;
				_hoops_GASRH = NULL;
			}

			if ( _hoops_GASRH )
				// _hoops_PPGGR _hoops_HH
				_hoops_CSRGR->post->_hoops_HAAP( &_hoops_GASRH );
		}
	}
}



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
			"compressed output image format not allowed in OpenGL2 driver."); 
		return null;
	}
	else if (_hoops_HAPIR == _hoops_AHGH) {
		HE_ERROR (HEC_DX9_DRIVER, HES_BAD_VALUE,
			"gray scale output image format not allowed in OpenGL2 driver."); 
		return null;
	}
	else {
		HE_ERROR (HEC_OPENGL_DRIVER, HES_BAD_VALUE,
			"unexpected output image format in OpenGL2 driver."); 
		return null;
	}
}


/*****************************************************************************
*****************************************************************************
							_hoops_SPCAC
*****************************************************************************
*****************************************************************************/
/*
 * _hoops_SRAC
 * _hoops_IPCP _hoops_GRGPR _hoops_IIGR _hoops_RGR _hoops_PCPH _hoops_HRGR _hoops_GIIA _hoops_HPP _hoops_GAAAH.
 * _hoops_HGI _hoops_PCPH _hoops_RAAAH _hoops_RH _hoops_CIACP _hoops_IIGR _hoops_RH _hoops_RII _hoops_SRAC _hoops_SICAR.
 */
void _hoops_GHCAC (_hoops_APARR alter & _hoops_RRCI) {
	/* _hoops_ASC _hoops_CHR _hoops_SIGR _hoops_IS _hoops_CHASA _hoops_GPAAC _hoops_PGSI */
	_hoops_RRCI->draw_dc_colorized_face						= HD_Std_DC_Colorized_Face;
	_hoops_RRCI->draw_dc_colorized_polytriangle				= HD_Std_DC_Colorized_Polytris;
	_hoops_RRCI->draw_dc_ellipse								= HD_Std_DC_Ellipse;
	_hoops_RRCI->_hoops_SCISR						= HD_Std_DC_Outline_Ellipse;
	_hoops_RRCI->draw_dc_polyline							= HD_Std_DC_Polyline;
	_hoops_RRCI->draw_dc_face								= HD_Std_DC_Face;
	_hoops_RRCI->draw_dc_polytriangle						= HD_Std_DC_Polytriangle;
	_hoops_RRCI->_hoops_RPCGA								= HD_Std_DC_Polygon;
	_hoops_RRCI->draw_dc_rectangle							= HD_Std_DC_Rectangle;
	_hoops_RRCI->draw_dc_polydot								= HD_Std_DC_Polydot;

	/* _hoops_SISS _hoops_GASCA _hoops_CIPH */
	_hoops_RRCI->start_device = start_device;
	_hoops_RRCI->stop_device = stop_device;
	_hoops_RRCI->get_physical_info = get_physical_info;
	_hoops_RRCI->get_outer_window = get_outer_window;
	_hoops_RRCI->free_outer_window = free_outer_window;
	_hoops_RRCI->_hoops_ASCSP = _hoops_ASCSP;
	_hoops_RRCI->_hoops_RSCSP = _hoops_RSCSP;
	_hoops_RRCI->get_current_info = get_current_info;

	_hoops_RRCI->finish_update = finish_update;
	_hoops_RRCI->init_update = init_update;
	_hoops_RRCI->finish_picture = finish_picture;
	_hoops_RRCI->init_picture = init_picture;
	_hoops_RRCI->_hoops_PCPGR = _hoops_PCPGR;

	_hoops_RRCI->draw_overlay_list = draw_overlay_list;
	_hoops_RRCI->_hoops_SCPGR = _hoops_SCPGR;


	/* _hoops_RHCAC _hoops_SICAR */
	_hoops_RRCI->draw_dc_rgb32_rasters = draw_dc_rgb32_rasters;
	_hoops_RRCI->draw_dc_rectangle = draw_dc_rectangle;
	_hoops_RRCI->draw_dc_polydot = draw_dc_polydot;
	_hoops_RRCI->draw_dc_colorized_polydot = draw_dc_colorized_polydot;
	_hoops_RRCI->draw_dc_polyline = draw_dc_polyline;
	_hoops_RRCI->draw_dc_gouraud_polyline = draw_dc_gouraud_polyline;
	_hoops_RRCI->draw_dc_polytriangle = draw_dc_polytriangle;
	_hoops_RRCI->draw_dc_gouraud_polytriangle = draw_dc_gouraud_polytriangle;
	_hoops_RRCI->draw_dc_colorized_polytriangle = draw_dc_colorized_polytriangle;
//#_hoops_CHS _hoops_AHCAC
	_hoops_RRCI->draw_dc_textured_polytriangle = draw_dc_textured_polytriangle;
//#_hoops_SHIIR

	/* _hoops_CIIA _hoops_SICAR */
	_hoops_RRCI->_hoops_HSCSP = _hoops_HSCSP;
	_hoops_RRCI->_hoops_ISCSP = _hoops_ISCSP;

	/* _hoops_AHCR _hoops_SRHR _hoops_PCPH */
	_hoops_RRCI->_hoops_CAAGR = _hoops_CAAGR;

	/* _hoops_PGSA 3D _hoops_SICAR */
	_hoops_RRCI->_hoops_CHCI = segment_render;

	_hoops_RRCI->draw_3d_polygon = draw_3d_polygon; 
	_hoops_RRCI->draw_3d_polyline = draw_3d_polyline; 
	_hoops_RRCI->draw_3d_tristrip = draw_3d_tristrip; 
	_hoops_RRCI->draw_3d_polyedge = draw_3d_polyedge; 
	_hoops_RRCI->draw_3d_polymarker = draw_3d_polymarker; 
	_hoops_RRCI->draw_3d_marker = draw_3d_marker; 
	_hoops_RRCI->_hoops_ARCI = _hoops_ARCI; 
	_hoops_RRCI->_hoops_PPAS = _hoops_PPAS; 
	_hoops_RRCI->draw_3d_grid = draw_3d_grid; 
	_hoops_RRCI->draw_3d_image = draw_3d_image; 

//	/* _hoops_AGCR _hoops_CGH _hoops_IIP _hoops_SHH _hoops_PIGS..._hoops_SR _hoops_PHCAC _hoops_RH _hoops_HHCAC _hoops_HSRPR _hoops_RPP _hoops_SSIA _hoops_AA... */
//	_hoops_HPGR->_hoops_IHCAC = _hoops_IRAP;
//	_hoops_HPGR->_hoops_CHCAC = _hoops_IRAP;
//	_hoops_HPGR->_hoops_SHCAC = _hoops_IRAP;
//

	/* _hoops_AIRI _hoops_CPCI */
	_hoops_RRCI->_hoops_AICI = _hoops_AICI;
	_hoops_RRCI->_hoops_GGSI = _hoops_GGSI;
	_hoops_RRCI->_hoops_AIGC = _hoops_AIGC;
	_hoops_RRCI->_hoops_PPCI = _hoops_PPCI;

	_hoops_RRCI->_hoops_SSRGR = _hoops_SSRGR;
//
//	/* _hoops_IAGIP _hoops_SICAR */
	_hoops_RRCI->create_region = create_region;
	_hoops_RRCI->_hoops_HIPGR = _hoops_HIPGR;
	_hoops_RRCI->_hoops_PIPGR = _hoops_PIPGR;
	_hoops_RRCI->_hoops_ISPGR = _hoops_ISPGR;
	_hoops_RRCI->_hoops_CSPGR = _hoops_CSPGR;
	_hoops_RRCI->_hoops_AGHGR = _hoops_AGHGR;
//
	_hoops_RRCI->snapshot = snapshot;
	_hoops_RRCI->_hoops_CGAGR = _hoops_CGAGR;

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

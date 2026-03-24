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
 * $Id: obf_tmp.txt 1.154 2010-12-17 21:51:23 warren Exp $
 */


#ifndef WIN32_OPENGL2_DRIVER

#include "hoops.h"
#include "hd_proto.h"

/*
 * _hoops_APICR _hoops_PPICR
 */
extern "C" bool HC_CDECL HD_Win32_OpenGL2_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR alter *			_hoops_GHRI, 
	int						request, 
	void *					request_info) 
{
	UNREFERENCED(request_info);
	return HD_No_Driver (_hoops_RIGC, _hoops_GHRI, request, "opengl2");
}

#else

#ifdef _DEBUG
#define _hoops_IPARH
#include <stdlib.h>
#include <crtdbg.h>
#endif


#include "windows_wrapper.h"	// _hoops_CGRI <_hoops_SPHGR._hoops_GGHR>, _hoops_PIHA _hoops_RCPS _hoops_SRS :(

#include "hoops.h"
#include "hd_proto.h"
#include "adt.h"


#define _hoops_SPARH
#ifdef _hoops_SPARH
typedef VStringHash<FILETIME *> _hoops_GHARH;
	_hoops_GHARH *_hoops_RHARH = null;
#endif

#define WGL2_DRIVER
#define DECLARE_OGL_PROTOTYPES
#include "ogl2.cpp"

#include "glew/include/GL/wglew.h"

#undef CONST

/* _hoops_ASHGR _hoops_PSHGR */
void check_events (HOGLData alter * _hoops_CSRGR);


local unsigned char _hoops_CGPPC[8] = {
	0, 0111 >> 1, 0222 >> 1, 0333 >> 1, 0444 >> 1, 0555 >> 1, 0666 >> 1, 0377
};

local unsigned char _hoops_SGPPC[4] = {
	0, 0x55, 0xaa, 0xff
};

local unsigned char _hoops_GRPPC[2] = {
	0, 255
};


/*
 * _hoops_PGAA
 */
local unsigned char
_hoops_RRPPC (int i, UINT _hoops_ARPPC, UINT shift) {
	unsigned char _hoops_HAGR;

	_hoops_HAGR = (unsigned char) (i >> shift);
	switch (_hoops_ARPPC) {
		case 1:
		_hoops_HAGR &= 0x1;
		return _hoops_GRPPC[_hoops_HAGR];

		case 2:
		_hoops_HAGR &= 0x3;
		return _hoops_SGPPC[_hoops_HAGR];

		case 3:
		_hoops_HAGR &= 0x7;
		return _hoops_CGPPC[_hoops_HAGR];

		default:
		return (unsigned char) 0;
	}
}

/*
 * _hoops_PGAA
 */
local void
_hoops_PRPPC (HOGLData alter * _hoops_CSRGR) {
	PIXELFORMATDESCRIPTOR pfd;
	LOGPALETTE *pPal;
	int n, i;
	static int _hoops_HRPPC[13] = {
		0, 3, 24, 27, 64, 67, 88, 173, 181, 236, 247, 164, 91
	};
	static PALETTEENTRY _hoops_IRPPC[20] = {
		{0, 0, 0, 0},
		{0x80, 0, 0, 0},
		{0, 0x80, 0, 0},
		{0x80, 0x80, 0, 0},
		{0, 0, 0x80, 0},
		{0x80, 0, 0x80, 0},
		{0, 0x80, 0x80, 0},
		{0xC0, 0xC0, 0xC0, 0},

		{192, 220, 192, 0},
		{166, 202, 240, 0},
		{255, 251, 240, 0},
		{160, 160, 164, 0},

		{0x80, 0x80, 0x80, 0},
		{0xFF, 0, 0, 0},
		{0, 0xFF, 0, 0},
		{0xFF, 0xFF, 0, 0},
		{0, 0, 0xFF, 0},
		{0xFF, 0, 0xFF, 0},
		{0, 0xFF, 0xFF, 0},
		{0xFF, 0xFF, 0xFF, 0}
	};

	n = GetPixelFormat (_hoops_CSRGR->hDC);
	DescribePixelFormat (_hoops_CSRGR->hDC, n, sizeof (PIXELFORMATDESCRIPTOR),
						 &pfd);

	if (pfd.dwFlags & PFD_NEED_PALETTE) {
		n = 1 << pfd.cColorBits;
		pPal =
			(PLOGPALETTE) LocalAlloc (LMEM_FIXED,
									  sizeof (LOGPALETTE) +
									  n * sizeof (PALETTEENTRY));
		pPal->palVersion = 0x300;
		pPal->palNumEntries = n;
		for (i = 0; i < n; i++) {
			pPal->palPalEntry[i].peRed =
				_hoops_RRPPC (i, pfd.cRedBits, pfd.cRedShift);
			pPal->palPalEntry[i].peGreen =
				_hoops_RRPPC (i, pfd.cGreenBits, pfd.cGreenShift);
			pPal->palPalEntry[i].peBlue =
				_hoops_RRPPC (i, pfd.cBlueBits, pfd.cBlueShift);
			pPal->palPalEntry[i].peFlags = 0;
		}

		/* _hoops_CCIH _hoops_GH _hoops_RH _hoops_IHCRH _hoops_IS _hoops_GCIS _hoops_RH _hoops_SHIR _hoops_HRRPI _hoops_IHCRH */
		if ((pfd.cColorBits == 8) &&
			(pfd.cRedBits == 3) && (pfd.cRedShift == 0) &&
			(pfd.cGreenBits == 3) && (pfd.cGreenShift == 3) &&
			(pfd.cBlueBits == 2) && (pfd.cBlueShift == 6)) {
			for (i = 1; i <= 12; i++)
				pPal->palPalEntry[_hoops_HRPPC[i]] = _hoops_IRPPC[i];
		}

		_hoops_CSRGR->_hoops_RIGRR = CreatePalette (pPal);
		LocalFree (pPal);

		_hoops_CSRGR->_hoops_AIGRR =
			SelectPalette (_hoops_CSRGR->hDC, _hoops_CSRGR->_hoops_RIGRR, FALSE);
		n = RealizePalette (_hoops_CSRGR->hDC);
	}
}



local bool
wgl_arb_pixel_format (Display_Context alter * dc)
{
	HOGLData alter *_hoops_CSRGR = OGLD (dc);
	int attribs[32], results[32];
	/*_hoops_AIIC _hoops_CRPPC[] = {0, 0};*/
	int _hoops_SRPPC = 0, _hoops_GAPPC;
	int i, j, _hoops_RAPPC;
	bool pass, status = false;
	bool _hoops_AAPPC, _hoops_PAPPC;
	bool want_hardware, _hoops_HAPPC = false;
	bool _hoops_IAPPC;
	int _hoops_CAPPC;
	bool _hoops_SAPPC, _hoops_GPPPC;
	bool *_hoops_RRSI = null;
	int _hoops_RPPPC = 0;
	float _hoops_IISAP, _hoops_APPPC, _hoops_PPPPC;
	/* _hoops_IPCP _hoops_GHARR'_hoops_GRI _hoops_SCRII _hoops_IHSR _hoops_RAIA _hoops_RGR _hoops_HRPR _hoops_IS _hoops_PRIA _hoops_RH _hoops_SICHR _hoops_AIR _hoops_RPCC _hoops_IGRSP. 
	 * _hoops_IPCP _hoops_HRPR _hoops_SSCP _hoops_PSP _hoops_RII _hoops_GIRRR _hoops_CRSIR _hoops_RH _hoops_GRRII _hoops_IIGR _hoops_RH _hoops_HPPPC _hoops_API. _hoops_GHPA _hoops_ICRP _hoops_CPS 
	 * _hoops_GGSR _hoops_PGGA _hoops_SR _hoops_CHR _hoops_HAR _hoops_GRP _hoops_RH _hoops_RHGS _hoops_IPPPC _hoops_SRSGR */
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof (PIXELFORMATDESCRIPTOR), /* _hoops_IGIR _hoops_IIGR _hoops_RGR _hoops_CPPPC */
		1,						/* _hoops_CSPP _hoops_PHI */
		0,
		0,						/* _hoops_RGPP _hoops_GPRR */
		0,						/* 24-_hoops_IGRH _hoops_HAIR _hoops_HCH */
		0, 0, 0, 0, 0, 0,		/* _hoops_HAIR _hoops_SIH _hoops_IAIH */
		0,						/* _hoops_PSP _hoops_AIIR _hoops_SRHR */
		0,						/* _hoops_PARRH _hoops_IGRH _hoops_IAIH */
		0,						/* _hoops_PSP _hoops_AAHRP _hoops_SRHR */
		0, 0, 0, 0,				/* _hoops_SPPPC _hoops_SIH _hoops_IAIH */
		0,						/* _hoops_SSH-_hoops_SRHR _hoops_SIH */
		0,						/* _hoops_HHGC _hoops_APSP _hoops_SRHR */
		0,						/* _hoops_PSP _hoops_GHPPC _hoops_SRHR */
		0,						/* _hoops_HGSI _hoops_ASAH */
		0,						/* _hoops_HPAP */
		0, 0, 0					/* _hoops_ASAH _hoops_IIAP _hoops_IAIH */
	};

	/* _hoops_SIPR _hoops_RH _hoops_PHI _hoops_IIGR _hoops_AIR _hoops_RPCC _hoops_HHPA */
	attribs[0] = WGL_NUMBER_PIXEL_FORMATS_ARB;
	if (!wglGetPixelFormatAttribivARB) {
		status = false;
		goto _hoops_HPAGR;
	}

	if (wglGetPixelFormatAttribivARB(_hoops_CSRGR->hDC,1,0,1,attribs,results) == GL_FALSE) {
		status = false;
		goto _hoops_HPAGR;
	}
	_hoops_SRPPC = results[0];
	if (_hoops_SRPPC > 0)
		ZALLOC_ARRAY(_hoops_RRSI, _hoops_SRPPC, bool);
	/* _hoops_HGSGR, _hoops_GGR _hoops_AGR _hoops_IIGR _hoops_GHCP
		_hoops_GCGH _hoops_SRCIA
		_hoops_GSIA _hoops_AHPGH
		_hoops_GHGPR _hoops_SRHR
		_hoops_HCH _hoops_SIH > 0
		_hoops_AIR _hoops_GPRR _hoops_PIRAI
		_hoops_IHSP _hoops_APP
		_hoops_GRCH (_hoops_CHGRR _hoops_HGRC)
		_hoops_IGPRH _hoops_CGPRH (_hoops_CHGRR _hoops_HGRC)
		_hoops_APSP _hoops_SIH > 0 (_hoops_CHGRR _hoops_HGRC)
		_hoops_IPS _hoops_GGSHR _hoops_SRHR 
		_hoops_PSP _hoops_AAHRP _hoops_SRHR (_hoops_RPP _hoops_SSRR)
		_hoops_PGSA _hoops_IS _hoops_RPPS (_hoops_ASPSI?)
	*/
	i = 0;
	attribs[i++] = WGL_SUPPORT_OPENGL_ARB;
	attribs[i++] = WGL_ACCELERATION_ARB;
	attribs[i++] = WGL_DOUBLE_BUFFER_ARB;
	attribs[i++] = WGL_DEPTH_BITS_ARB;
	attribs[i++] = WGL_ALPHA_BITS_ARB;
	attribs[i++] = WGL_ACCUM_BITS_ARB;
	attribs[i++] = WGL_PIXEL_TYPE_ARB;
	attribs[i++] = WGL_COLOR_BITS_ARB;
	attribs[i++] = WGL_STEREO_ARB;
	attribs[i++] = WGL_STENCIL_BITS_ARB;
	if (WGLEW_ARB_multisample)
		attribs[i++] = WGL_SAMPLES_ARB;
	attribs[i++] = WGL_SWAP_METHOD_ARB;
	attribs[i++] = WGL_DRAW_TO_WINDOW_ARB;
	_hoops_GAPPC = i;

	do {
		status = true;
		_hoops_RAPPC = -1;
		_hoops_PPPPC = -1;
		for (i = 1; i < _hoops_SRPPC; i++) {
			if (_hoops_RRSI[i])
				continue;

			/* _hoops_HPIAR _hoops_RH _hoops_AIR _hoops_RPCC _hoops_AIRC */
			if (wglGetPixelFormatAttribivARB(_hoops_CSRGR->hDC, i, 0, _hoops_GAPPC, attribs, results) == GL_FALSE) {
				status = false;
				goto _hoops_HPAGR;
			}
			pass = true;
			_hoops_IISAP = 0;
			for (j = 0; j < _hoops_GAPPC && pass; j++) {
				switch (attribs[j]) {
					case WGL_DOUBLE_BUFFER_ARB:
					case WGL_SUPPORT_OPENGL_ARB:
					case WGL_DRAW_TO_WINDOW_ARB:
					case WGL_DRAW_TO_PBUFFER_ARB: /* _hoops_RGAR _hoops_CISI _hoops_RPP _hoops_CGSRC _hoops_RHPPC */
					case WGL_ALPHA_BITS_ARB:
						if (results[j] == 0)
							pass = false;
						break;
					case WGL_DEPTH_BITS_ARB:
						if (results[j] == 0)
							pass = false;
						else
							_hoops_IISAP += results[j]/32.0f;
						break;
					case WGL_ACCUM_BITS_ARB:
						if (results[j] == 0)
							pass = false;
						break;
					case WGL_STEREO_ARB:
						_hoops_SAPPC = (dc->options._hoops_AHIIP != 0);
						_hoops_GPPPC = (results[j] != 0);
						if (_hoops_GPPPC != _hoops_SAPPC)
							pass = false;
						break;
					case WGL_SAMPLE_BUFFERS_ARB:
					case WGL_SAMPLES_ARB:
						//_hoops_AHPPC = (_hoops_CSPH->_hoops_AAP._hoops_PHPPC != 0);
						_hoops_IAPPC = false;
						if (dc->options._hoops_AIPGA < 0)
							_hoops_CAPPC = 2;  /* _hoops_AAPA _hoops_PAPA _hoops_HHPPC _hoops_RHPP'_hoops_GRI _hoops_SHIR */
						else
							_hoops_CAPPC = dc->options._hoops_AIPGA;
						if (!_hoops_IAPPC == !results[j]) { /* (!_hoops_IRS == !_hoops_RCSR) _hoops_IH _hoops_SICHR _hoops_CRGIR */
							_hoops_IISAP += (float)results[j] / 1024.0f;
							pass = true;
						}
						else {
							_hoops_IISAP -= (float)results[j] / 1024.0f;
							pass = false;
						}
						if (results[j] == _hoops_CAPPC)
							_hoops_IISAP += 0.25f; /* _hoops_IHH _hoops_IHPPC _hoops_IH _hoops_PCCP _hoops_CGCH _hoops_PSSP */
						break;
					case WGL_PIXEL_TYPE_ARB:
						if (results[j] != WGL_TYPE_RGBA_ARB)
							pass = false;
						break;
					case WGL_ACCELERATION_ARB:
						//_hoops_CHPPC = !(_hoops_CSPH->_hoops_AAP._hoops_HISRA & _hoops_SHPPC);
						want_hardware = true;
						_hoops_HAPPC = (results[j] == WGL_FULL_ACCELERATION_ARB);
						if (want_hardware != _hoops_HAPPC)
							pass = false;
						break;
					case WGL_COLOR_BITS_ARB:
						if (results[j] < 16)
							pass = false;
						break;
					case WGL_SWAP_METHOD_ARB:
						if (results[j] != WGL_SWAP_COPY_ARB)
							pass = false;
						break;
					/* _hoops_GPGA _hoops_GPP _hoops_RH _hoops_AIAAC, _hoops_SR _hoops_GHCA _hoops_PAR _hoops_GHCA _hoops_HAR _hoops_HHGC _hoops_IS _hoops_HGCR _hoops_IRS _hoops_APSP _hoops_SRHR */
					case WGL_STENCIL_BITS_ARB:
						_hoops_AAPPC = dc->options._hoops_PIPGA &&
							!XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_STENCIL);
						_hoops_PAPPC = (results[j] != 0);
						if (_hoops_AAPPC != _hoops_PAPPC)
							pass = false;
						break;
					default:
						HE_ERROR (HEC_OPENGL_DRIVER, HES_PROCEDURAL_ERROR,
								  "internal error: mismatch between pixel attributes requested and processed");
						break;
				}
			}
			/* _hoops_RH "_hoops_GIPPC" _hoops_HRGR _hoops_RH _hoops_PHI _hoops_IIGR _hoops_HRRAR _hoops_SR _hoops_PPHRH _hoops_ASAS _hoops_SIHH _hoops_HPCS, _hoops_IPSH
				_hoops_IRS _hoops_RISA _hoops_PIRA _hoops_IS _hoops_IHSA _hoops_RIPPC _hoops_GRP _hoops_AIRC _hoops_IH _hoops_PGAP _hoops_SR _hoops_HS _hoops_IRS "_hoops_HCHAC" _hoops_CIHCA. */
			_hoops_APPPC = (float) j + _hoops_IISAP;
			if (_hoops_APPPC > _hoops_PPPPC) {
				_hoops_RAPPC = i;
				_hoops_PPPPC = _hoops_APPPC;
			}
		}
		if (_hoops_RAPPC < 0) {
			status = false;
			goto _hoops_HPAGR;
		}
		status = SetPixelFormat (_hoops_CSRGR->hDC, _hoops_RAPPC, &pfd) != FALSE;
		/* _hoops_PAHA'_hoops_RA _hoops_IHPS, _hoops_HIH _hoops_SCH _hoops_RHAP.  _hoops_HAIA _hoops_PAGRC _hoops_IIGR _hoops_SRCIA _hoops_AIPPC _hoops_AIR _hoops_AGHS _hoops_SGS
		 * _hoops_CHR _hoops_HAR _hoops_PIPPC _hoops_HPGR _hoops_RH _hoops_GHIR _hoops_IIGR _hoops_RAP */
		if (!status)
			_hoops_RRSI[_hoops_RAPPC] = true;
	} while (!status);

	/* _hoops_HA _hoops_CISA _hoops_GGR _hoops_HGPGA _hoops_PPR _hoops_CSPH->_hoops_CPHSR _hoops_CCA _hoops_HPHS _hoops_AHCA _hoops_RH _hoops_SASI _hoops_AIR _hoops_RPCC _hoops_SGS _hoops_SR _hoops_RSRS */
	status = wglGetPixelFormatAttribivARB(_hoops_CSRGR->hDC, _hoops_RAPPC, 0, _hoops_GAPPC, attribs, results) != FALSE;
	if (!status)
		goto _hoops_HPAGR;
	for (j = 0; j < _hoops_GAPPC; j++) {
		switch (attribs[j]) {
			case WGL_DOUBLE_BUFFER_ARB:
				_hoops_CSRGR->_hoops_SRRRR = results[j] != 0;
				break;
			case WGL_STEREO_ARB:
				if (results[j] != 0)
					dc->_hoops_PGCC.flags |= _hoops_IPPHP;
				else
					dc->_hoops_PGCC.flags &= ~_hoops_IPPHP;
				break;
			case WGL_SAMPLES_ARB:
				//_hoops_HGPGA->_hoops_HIPPC = (_hoops_ACPP[_hoops_PPHR] != 0);
				//_hoops_HGPGA->_hoops_IIPPC = _hoops_ACPP[_hoops_PPHR];
				_hoops_CSRGR->_hoops_PHHGC = (WGLEW_ARB_multisample != 0);
				_hoops_CSRGR->_hoops_APCAC = -1;
				break;
			case WGL_DEPTH_BITS_ARB:
				_hoops_CSRGR->_hoops_IGARR = results[j];
				break;
			case WGL_COLOR_BITS_ARB:
				if (results[j] < 24)
					_hoops_CSRGR->_hoops_CRHGC = true;
				break;
			case WGL_SWAP_METHOD_ARB:
				if (results[j] == WGL_SWAP_COPY_ARB ||
					XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_LIES_ABOUT_SWAP))
					dc->_hoops_PGCC._hoops_CHHSR = _hoops_ACPGA;
				else
					dc->_hoops_PGCC._hoops_CHHSR = _hoops_RCPGA;
				break;
			case WGL_STENCIL_BITS_ARB:
				if (results[j])
					_hoops_CSRGR->_hoops_PPHGC = true;
				_hoops_RPPPC = results[j];
				break;
			case WGL_ACCUM_BITS_ARB:
				if (!XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_ACCUMULATION_BUFFER))
					_hoops_CSRGR->accumulation_bits = results[j];
				break;
			case WGL_ACCELERATION_ARB:
				_hoops_HAPPC = (results[j] == WGL_FULL_ACCELERATION_ARB);
				break;
			case WGL_SAMPLE_BUFFERS_ARB:
			case WGL_ALPHA_BITS_ARB:
			case WGL_SUPPORT_OPENGL_ARB:
			case WGL_DRAW_TO_WINDOW_ARB:
			case WGL_PIXEL_TYPE_ARB:
			default:
				break;
		}
	}

  _hoops_HPAGR:
	if (_hoops_RRSI != null) {
		FREE_ARRAY(_hoops_RRSI, _hoops_SRPPC, bool);
	}
	return status;
} /* _hoops_RSGR _hoops_API _hoops_CIPPC */




#ifdef _hoops_IIIPA
#define _hoops_SIPPC(dwOldMode) \
	__asm fnstcw WORD PTR dwOldMode \
	__asm mov eax, dwOldMode \
	__asm or eax, 0x3f \
	__asm mov WORD PTR dwOldMode+2, ax \
	__asm fldcw WORD PTR dwOldMode+2

#define _hoops_GCPPC(dwOldMode) \
	__asm fnclex \
	__asm fldcw WORD PTR dwOldMode
#else
#define _hoops_SIPPC(dwOldMode)
#define _hoops_GCPPC(dwOldMode)
#endif


local void 
_hoops_RCPPC (char alter *_hoops_ACPPC)
{
	char const *_hoops_PCPPC;

	_hoops_AAHR ("*", _hoops_ACPPC);

	_hoops_PCPPC = (char const *) glGetString (GL_VENDOR);
	if (!_hoops_PCPPC)
		return;
#if 0
	HKEY _hoops_HCPPC;
	long status;
	DWORD _hoops_ICPPC;

	if (_hoops_CISGH (_hoops_PCPPC, "ATI") ||
		_hoops_CISGH (_hoops_PCPPC, "AMD")) {
		status = RegOpenKeyEx (HKEY_LOCAL_MACHINE, 
					"SOFTWARE\\ATI Technologies\\CBT", 
					0L,	KEY_QUERY_VALUE, &_hoops_HCPPC);
		if (status != ERROR_SUCCESS)
			return;
		_hoops_ICPPC = 4096;
		RegQueryValueEx (_hoops_HCPPC, "ReleaseVersion", null, null,
					(LPBYTE)_hoops_ACPPC, &_hoops_ICPPC);
		if (status != ERROR_SUCCESS)
			_hoops_AAHR ("*", _hoops_ACPPC);
		RegCloseKey (_hoops_HCPPC);
	}
	else if (_hoops_CISGH (_hoops_PCPPC, "NVIDIA")) {
		/* _hoops_SIGP */
	}
#endif
}




#define PFD_ATTRIBUTE_SCORE1 0x01
#define PFD_ATTRIBUTE_SCORE2 0x02
#define PFD_ATTRIBUTE_SCORE3 0x04
#define PFD_ATTRIBUTE_SCORE4 0x08
#define PFD_ATTRIBUTE_SCORE5 0x10
#define PFD_ATTRIBUTE_SCORE6 0x20
#define PFD_ATTRIBUTE_SCORE7 0x40
/*
 * _hoops_PGAA
 */
local void
choose_pixel_format (Display_Context alter * dc)
{
	HOGLData alter *_hoops_CSRGR = OGLD (dc);
	int pixelFormat;
	int _hoops_CCPPC;
	int _hoops_SCPPC, _hoops_GSPPC;
	int _hoops_RSPPC, _hoops_ASPPC;
	/*_hoops_SCSH _hoops_PSPPC = _hoops_IRRC (_hoops_CSPH->_hoops_AAP._hoops_HISRA, _hoops_HSPPC) ? 1 : 32;*/
	int nzb = BIT (dc->options._hoops_IRARR, _hoops_CPGAC) ? 1 : 16;
	int _hoops_HAPPC=0, want_hardware;

	int _hoops_AAPPC = dc->options._hoops_PIPGA &&
		!XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_STENCIL);

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof (PIXELFORMATDESCRIPTOR), /* _hoops_IGIR _hoops_IIGR _hoops_RGR _hoops_CPPPC */
		1,						/* _hoops_CSPP _hoops_PHI */
		PFD_DRAW_TO_WINDOW |	/* _hoops_GCGH _hoops_RPPS */
			PFD_SUPPORT_OPENGL |		/* _hoops_GCGH _hoops_HIHH */
			PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,			/* _hoops_RGPP _hoops_GPRR */
		24,						/* 24-_hoops_IGRH _hoops_HAIR _hoops_HCH *//* _hoops_ISPPC _hoops_IGI '24' */
		0, 0, 0, 0, 0, 0,		/* _hoops_HAIR _hoops_SIH _hoops_IAIH */
		0,						/* _hoops_PSP _hoops_AIIR _hoops_SRHR */
		0,						/* _hoops_PARRH _hoops_IGRH _hoops_IAIH */
		0,						/* _hoops_PSP _hoops_AAHRP _hoops_SRHR */
		0, 0, 0, 0,				/* _hoops_SPPPC _hoops_SIH _hoops_IAIH */
		32,						/* _hoops_CSPPC _hoops_SSH-_hoops_SRHR *//* _hoops_ISPPC _hoops_IGI '24' */
		1,						/* _hoops_HHGC _hoops_APSP _hoops_SRHR */
		0,						/* _hoops_PSP _hoops_GHPPC _hoops_SRHR */
		PFD_MAIN_PLANE,			/* _hoops_HGSI _hoops_ASAH */
		0,						/* _hoops_HPAP */
		0, 0, 0					/* _hoops_ASAH _hoops_IIAP _hoops_IAIH */
	};

	pfd.cDepthBits=nzb; 
	pfd.cStencilBits=_hoops_AAPPC;

	if (dc->options._hoops_AHIIP)
		pfd.dwFlags |= PFD_STEREO;


	if (!XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_DOUBLE_BUFFER_SWAP_ONLY))
		pfd.dwFlags |= PFD_SWAP_COPY;

	/* _hoops_HGAPR _hoops_RAIGC, _hoops_SSPPC _hoops_GGHIP _hoops_RCSPR _hoops_HPPPC _hoops_GGHPC, _hoops_GRGSI _hoops_RGHPC _hoops_GGHIP _hoops_AGHPC _hoops_CARRI _hoops_PGHPC */
	/*
	 * _hoops_HHCS _hoops_IS _hoops_PSSP _hoops_HGHPC _hoops_IGRH _hoops_HCH, _hoops_HIH _hoops_RRP _hoops_IGHPC _hoops_HPGR _hoops_CHGC
	 */
	pfd.cColorBits = GetDeviceCaps (_hoops_CSRGR->hDC, BITSPIXEL);
	if (pfd.cColorBits < 16)
		pfd.cColorBits = 16;

	/*
	 * _hoops_HGH _hoops_RH _hoops_PHI _hoops_IIGR _hoops_AIR _hoops_AGHS _hoops_HHPA.	 _hoops_CGP _hoops_CRSIR _hoops_RARP,
	 * &_hoops_CPPPC _hoops_HRGR _hoops_IRAP, _hoops_RH _hoops_API _hoops_CIGCP _hoops_PSP _hoops_PIH _hoops_IS _hoops_RH _hoops_HRPR.	_hoops_HGI
	 * _hoops_HRGR _hoops_PSIGA _hoops_CGPR _hoops_RHAC _hoops_RGAR _hoops_HHGC _hoops_IS _hoops_CGHPC _hoops_RH _hoops_CIAS _hoops_AIR _hoops_RPCC
	 * _hoops_CIHA _hoops_IIGR _hoops_IRS _hoops_SISS _hoops_GGSC.
	 */
	_hoops_ASPPC = 0;
	_hoops_ASPPC = DescribePixelFormat (_hoops_CSRGR->hDC, 0,
										   sizeof (PIXELFORMATDESCRIPTOR),
										   null);

	/*
	 * _hoops_RAP _hoops_RH _hoops_AIR _hoops_RPCC _hoops_IS _hoops_RH _hoops_SHIR _hoops_AIR _hoops_RPCC
	 */
	pixelFormat = 1;
	_hoops_SCPPC = -PFD_ATTRIBUTE_SCORE6;

	/*
	 * _hoops_SGHPC _hoops_RHIR _hoops_RH _hoops_AIR _hoops_AGHS _hoops_HII 1 _hoops_IS _hoops_GRHPC _hoops_IS _hoops_SSS
	 * _hoops_RH _hoops_AAH _hoops_PSSP _hoops_CCA _hoops_RH _hoops_RGHP _hoops_PPR _hoops_PIASR _hoops_AIRC.
	 *
	 * _hoops_RRHPC _hoops_RHAC _hoops_SSS _hoops_RH _hoops_CIHA _hoops_IH _hoops_RH _hoops_AIR _hoops_RPCC _hoops_CCA _hoops_RH _hoops_RGHP
	 * _hoops_PPR _hoops_PIASR _hoops_AIRC, _hoops_SGS _hoops_CIHA _hoops_GHCA _hoops_SHH _hoops_IGI _hoops_HPP _hoops_RH _hoops_RCHAR
	 * _hoops_AHSHA _hoops_IS _hoops_ARP _hoops_RH _hoops_AIR _hoops_RPCC.	 _hoops_GPGP _hoops_RII _hoops_ARCCP, _hoops_RHAC _hoops_CGH
	 * _hoops_RGAR _hoops_HS _hoops_IS _hoops_SHGR _hoops_RH _hoops_HIGR _hoops_IIGR _hoops_AIR _hoops_AGHS _hoops_ARR _hoops_IH _hoops_GII
	 * _hoops_RAGA _hoops_SISS _hoops_GGSC.
	 */
	for (_hoops_GSPPC = 1;
		 _hoops_GSPPC <= _hoops_ASPPC; _hoops_GSPPC++) {

		/*
		 * _hoops_GHPA _hoops_GGSR _hoops_RH _hoops_ARHPC _hoops_GRR _hoops_GHIR
		 */
		_hoops_RSPPC = 0;

		/*
		 * _hoops_GAIAR _hoops_CICAR _hoops_HPHS _hoops_AHCA _hoops_RH _hoops_SISS _hoops_PRHPC _hoops_AIR
		 * _hoops_RPCC _hoops_IHIA _hoops_CCA _hoops_HRHPC
		 */
		if (!DescribePixelFormat (_hoops_CSRGR->hDC, (short) _hoops_GSPPC,
								  sizeof (PIXELFORMATDESCRIPTOR), &pfd)) {
			HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_SET_ATTRIBUTE,
					  "First DescribePixelFormat Failed");
			HD_Kill_Driver (dc);
			return;
		}

		/*
		 * _hoops_ACGR _hoops_RH _hoops_AIR _hoops_RPCC _hoops_SGS _hoops_SSCP _hoops_RH _hoops_RGHP _hoops_AIRC
		 */
		if (pfd.dwFlags & PFD_DRAW_TO_WINDOW &&
			pfd.dwFlags & PFD_SUPPORT_OPENGL &&
			pfd.dwFlags & PFD_DOUBLEBUFFER &&
			pfd.iPixelType == PFD_TYPE_RGBA &&
			pfd.cDepthBits > 15 /* && _hoops_CPPPC._hoops_IRHPC >= 15 */) {

			/*
			 * _hoops_ACGR _hoops_RH _hoops_AIR _hoops_RPCC _hoops_SGS _hoops_SSCP _hoops_RH _hoops_AAH _hoops_PSSP _hoops_IS _hoops_RH
			 * _hoops_PIASR _hoops_AIRC
			 */
			if (pfd.cStencilBits > 0) {
				_hoops_RSPPC += PFD_ATTRIBUTE_SCORE1;
			}

				/*_hoops_SR _hoops_HA _hoops_HHGC _hoops_AIIR _hoops_GGRGR 555 _hoops_SR _hoops_CRHPC _hoops_PACIA _hoops_ACSRR _hoops_SCH*/
			if (pfd.cAlphaBits > 0)
				_hoops_RSPPC += PFD_ATTRIBUTE_SCORE2;

			/*
			 * _hoops_PS _hoops_GA'_hoops_RA _hoops_HHGC _hoops_APHSR _hoops_PAR _hoops_SRHPC _hoops_GHC _hoops_RPP _hoops_SR _hoops_PAH
			 * _hoops_SRCH _hoops_CAPR, _hoops_PGGA _hoops_SSIA _hoops_IRAA _hoops_GH _hoops_PPGS _hoops_PPR _hoops_SSIA _hoops_GHCA
			 * _hoops_RAGS _hoops_CCA _hoops_AIIR.
			 */
			if (pfd.bReserved == 0)
				_hoops_RSPPC += PFD_ATTRIBUTE_SCORE3;

			if (pfd.iLayerType == PFD_MAIN_PLANE)
				_hoops_RSPPC += PFD_ATTRIBUTE_SCORE4;

			if (pfd.dwFlags & PFD_SWAP_COPY) {
				if (!XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_DOUBLE_BUFFER_SWAP_ONLY))
					_hoops_RSPPC += PFD_ATTRIBUTE_SCORE5;
			}

			//_hoops_CHPPC = !(_hoops_CSPH->_hoops_AAP._hoops_HISRA & _hoops_SHPPC);
			want_hardware = true;

			if (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP && 
					XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_FORCE_DEFAULT_SOFTWARE)) {

					want_hardware = 0;
			}

			_hoops_HAPPC = !(pfd.dwFlags & PFD_GENERIC_FORMAT) && !(pfd.dwFlags & PFD_GENERIC_ACCELERATED);
			if (want_hardware == _hoops_HAPPC)
				_hoops_RSPPC += PFD_ATTRIBUTE_SCORE6;

			if (dc->options._hoops_AHIIP && (pfd.dwFlags & PFD_STEREO))
				_hoops_RSPPC += PFD_ATTRIBUTE_SCORE7;

			/*
			 * _hoops_RAP _hoops_RH _hoops_AAH _hoops_AIR _hoops_RPCC _hoops_IIHA _hoops_GPP _hoops_RH _hoops_GIPPC
			 */
			if (_hoops_RSPPC > _hoops_SCPPC) {
				pixelFormat = _hoops_GSPPC;
				_hoops_SCPPC = _hoops_RSPPC;
			}
		}
	}

	/*
	 * _hoops_AGGA _hoops_SGS _hoops_SR _hoops_HS _hoops_GSGI _hoops_RH _hoops_AIR _hoops_RPCC _hoops_SGS _hoops_AAH _hoops_SPASR _hoops_RH
	 * _hoops_PIASR _hoops_AIRC, _hoops_SR _hoops_RRP _hoops_IS _hoops_GAHPC _hoops_SGS _hoops_AIR _hoops_RPCC _hoops_GICS
	 * _hoops_PGGA _hoops_SCH _hoops_GHCA _hoops_HAR _hoops_HS _hoops_RPII _hoops_RH _hoops_CGHI _hoops_AIR _hoops_RPCC _hoops_GGR _hoops_RH _hoops_HIGR.
	 */
	if (!DescribePixelFormat (_hoops_CSRGR->hDC, (short) pixelFormat,
							  sizeof (PIXELFORMATDESCRIPTOR), &pfd)) {
		HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_SET_ATTRIBUTE,
				  "DescribePixelFormat Failed");
		HD_Kill_Driver (dc);
		return;
	}


	if (pfd.dwFlags & PFD_SWAP_COPY)
		dc->_hoops_PGCC._hoops_CHHSR = _hoops_ACPGA;
	else
		dc->_hoops_PGCC._hoops_CHHSR = _hoops_RCPGA;

	if (XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_DOUBLE_BUFFER_SWAP_ONLY))
		dc->_hoops_PGCC._hoops_CHHSR = _hoops_RCPGA;

	if (pfd.dwFlags & PFD_STEREO)
		dc->_hoops_PGCC.flags |= _hoops_IPPHP;

	if (pfd.cColorBits < 24)
		_hoops_CSRGR->_hoops_CRHGC = true;

	/*
	 * _hoops_RAP _hoops_RH _hoops_AIR _hoops_RPCC _hoops_IIGR _hoops_RH _hoops_CHIA _hoops_SISS _hoops_GGSC _hoops_IS _hoops_RH _hoops_RPCC.
	 */
	_hoops_CCPPC = SetPixelFormat (_hoops_CSRGR->hDC, pixelFormat, &pfd);
	_hoops_CSRGR->accumulation_bits = 0;

	if (!_hoops_CCPPC) {
		HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_SET_ATTRIBUTE,
				  "Unable to Set Pixel Format");
		HD_Kill_Driver (dc);
		return;
	}
}

/*
 * _hoops_PGAA
 */
local void
identify_renderer (Display_Context alter * dc) {
	HOGLData alter *_hoops_CSRGR = OGLD (dc);
	char const *test;
	char version[4096];
	HGLRC temp;
	HWND hWND;
	HDC hDC;
	HDC _hoops_RAHPC;

	hWND = CreateWindow ("HoopsWClassOGL2", "htest", 
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		1,1,1,1,
		null, null, _hoops_RCSRH (_hoops_ACSRH), null);

	if (hWND == null) {
		HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_CREATE_WINDOW,
				  "Unable to Create Renderer Test Window");
		HD_Kill_Driver (dc);
		return;
	}

	hDC = GetDC (hWND);

	if (hDC == null) {
		HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_CREATE_WINDOW,
				  "Unable to Create Renderer Test DC");
		HD_Kill_Driver (dc);
		return;
	}

	/*_hoops_AAHPC _hoops_CCPC*/
	_hoops_RAHPC = _hoops_CSRGR->hDC;
	_hoops_CSRGR->hDC = hDC;

	/* _hoops_ARPR _hoops_IRS _hoops_SPCS _hoops_RPPS _hoops_IH _hoops_HHCPR */
	if (BIT(dc->options._hoops_IRARR, _hoops_ARRAH)) {
		HE_WARNING (HEC_OPENGL_DRIVER, HES_NOT_AVAILABLE,
			"Software Opengl2 not available. Using hardware acceleration.");
	}
	choose_pixel_format(dc);
	temp = wglCreateContext (_hoops_CSRGR->hDC);

	if (temp) {
		HDC	  _hoops_APAAC;
		HGLRC _hoops_PPAAC;
#ifdef _M_IX86
		int _hoops_PAHPC;
#endif
		_hoops_APAAC = wglGetCurrentDC();
		_hoops_PPAAC = wglGetCurrentContext();

		/* _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_HGASI _hoops_IH _hoops_IRS _hoops_SCCHH _hoops_GPP _hoops_RCGAH _hoops_CGPR _hoops_RSIPH _hoops_HS _hoops_RPII _hoops_PPP*/

		_hoops_SIPPC(_hoops_PAHPC);
		wglMakeCurrent (_hoops_CSRGR->hDC, temp);
		_hoops_GCPPC(_hoops_PAHPC);

		_hoops_CSRGR->glewcontext = new GLEWContext(); 
		_hoops_CSRGR->wglewcontext = new WGLEWContext();
		glewInit();
		wglewInit();

		test = (char const *) glGetString (GL_RENDERER);

		if (test) {
			if (_hoops_CSRGR->_hoops_PRARR)
				HI_Free_Driver_Config(_hoops_CSRGR->_hoops_PRARR);
			_hoops_RCPPC (version);
			_hoops_RGAIR(dc->_hoops_PGCC._hoops_GSPGH);
			_hoops_RGAIR(dc->_hoops_PGCC._hoops_RSPGH);
			HI_Copy_Chars_To_Name(test, &dc->_hoops_PGCC._hoops_GSPGH);
			HI_Copy_Chars_To_Name(version, &dc->_hoops_PGCC._hoops_RSPGH);
			dc->_hoops_PGCC._hoops_PRARR = _hoops_CSRGR->_hoops_PRARR = HI_Lookup_Driver_Config(dc->_hoops_RIGC, "opengl2", test, version, true, _hoops_RSPRH);   
		}
		wglMakeCurrent (_hoops_APAAC, _hoops_PPAAC);
		wglDeleteContext (temp);
	}

	/*_hoops_HAHPC _hoops_AAHPC _hoops_CCPC*/
	ReleaseDC (hWND, _hoops_CSRGR->hDC);
	_hoops_CSRGR->hDC = _hoops_RAHPC;

	DestroyWindow(hWND);

	if (!temp || 
		XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_FORCE_DEFAULT_SOFTWARE)) {

		if (_hoops_CSRGR->_hoops_PRARR)
			HI_Free_Driver_Config(_hoops_CSRGR->_hoops_PRARR);
		_hoops_RGAIR(dc->_hoops_PGCC._hoops_GSPGH);
		_hoops_RGAIR(dc->_hoops_PGCC._hoops_RSPGH);
		HI_Copy_Chars_To_Name("GDI Generic", &dc->_hoops_PGCC._hoops_GSPGH);
		HI_Copy_Chars_To_Name("*", &dc->_hoops_PGCC._hoops_RSPGH);
		dc->_hoops_PGCC._hoops_PRARR = _hoops_CSRGR->_hoops_PRARR = HI_Lookup_Driver_Config(dc->_hoops_RIGC, "opengl2", "GDI Generic", "*", true, _hoops_RSPRH);
	}

	if (!BIT(_hoops_CSRGR->_hoops_PRARR->flags, _hoops_IIIPP)) {
		dc->_hoops_PGCC.driver_type = _hoops_SCGGC;
		_hoops_CSRGR->_hoops_GSGRR = false;
	}
	else {
		dc->_hoops_PGCC.driver_type = _hoops_CCGGC;
		_hoops_CSRGR->_hoops_GSGRR = true;
	}
}



local void
unset_ogl (Display_Context const * dc) {
	HOGLData alter *_hoops_CSRGR = OGLD (dc);
	_hoops_RRPRH *_hoops_IRSRA = _hoops_ARPRH();

	_hoops_CAAI (HOOPS_WORLD->_hoops_APHGI);

	wglMakeCurrent(NULL,NULL);

#if 0
	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_HPSGR) {
		/*_hoops_IAHPC (_hoops_HGPGA->_hoops_SRCRH, 0, 0, 1, 1, _hoops_RCPP);*/
	}
#endif
	if (!_hoops_CSRGR->_hoops_GSGRR && 
		_hoops_IRSRA->_hoops_PRACI != null) {

		HOGLData const *_hoops_CAHPC;

		_hoops_IRSRA->_hoops_PRACI->ResetCursor();
		while ((_hoops_CAHPC = _hoops_IRSRA->_hoops_PRACI->PeekCursor()) != null) {
		   if (_hoops_CAHPC == _hoops_CSRGR) {
			  _hoops_IRSRA->_hoops_PRACI->RemoveAtCursor();
			  break;
		   }
		   _hoops_IRSRA->_hoops_PRACI->AdvanceCursor();
		}
		if (_hoops_IRSRA->_hoops_PRACI->Count() == 0) {
			delete _hoops_IRSRA->_hoops_PRACI;
			_hoops_IRSRA->_hoops_PRACI = null;
		}
	}


	/*_hoops_GGAS _hoops_SAHPC _hoops_CIPH*/
	if (_hoops_CSRGR->_hoops_HIISI) {
		SelectObject(_hoops_CSRGR->_hoops_HIISI, _hoops_CSRGR->old_hBitmap);
		DeleteObject(_hoops_CSRGR->hBitmap);
		DeleteObject(_hoops_CSRGR->_hoops_HIISI);
		_hoops_CSRGR->_hoops_HIISI = null;
		_hoops_CSRGR->hBitmap = null;
		_hoops_CSRGR->old_hBitmap = null;
	}

	if (_hoops_CSRGR->_hoops_RIGRR) {
		SelectPalette (_hoops_CSRGR->hDC, _hoops_CSRGR->_hoops_AIGRR, FALSE);
		DeleteObject (_hoops_CSRGR->_hoops_RIGRR);
	}

	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR) {
		wglDeleteContext (_hoops_CSRGR->hGLRC);
		//_hoops_SIGP:_hoops_HGPGA->_hoops_GPHPC (_hoops_HGPGA->_hoops_CGSRC, _hoops_HGPGA->_hoops_SASRC);
		//_hoops_SIGP:_hoops_HGPGA->_hoops_RPHPC (_hoops_HGPGA->_hoops_CGSRC);
	}
	else {
		ReleaseDC (_hoops_CSRGR->hWND, _hoops_CSRGR->hDC);
		wglDeleteContext (_hoops_CSRGR->hGLRC);
	}

	/* _hoops_SIGP _hoops_RGR _hoops_IHSHH
	_hoops_RPP (_hoops_HGPGA->_hoops_APHPC)
		_hoops_PPHPC (_hoops_HGPGA->_hoops_APHPC);
		*/

	_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);

	_hoops_CSRGR->hDC = null;
	_hoops_CSRGR->hGLRC = null;
	_hoops_CSRGR->overlayGLRC = null;
}


/*
 * _hoops_SRAC
 */
void finish_picture (Net_Rendition const &  nr,
				bool swap_buffers) 
{
	Display_Context const *dc = nr->_hoops_SRA;
	HOGLData alter *_hoops_CSRGR = OGLNRD (nr);

	if ( _hoops_CSRGR->_hoops_AHGRR )
	{

//#_hoops_PPIP _hoops_PGRPC
#ifdef _hoops_HGRPC
		int x = 0;
		int size = 200;

		_hoops_CAAI (HOOPS_WORLD->_hoops_SAAI);
		// _hoops_PPPA _hoops_AIRI _hoops_CPCI
		for ( _hoops_AGCI *dl = HOOPS_WORLD->_hoops_GPAI; dl; dl = dl->next ) { 
			H3D_Display_List *_hoops_PICI = (H3D_Display_List *) dl;
			if ( _hoops_PICI->type == H3D_DL_SHADOW_MAP ) {
				// _hoops_GISP _hoops_PPR _hoops_GCHGA _hoops_HASRH.
				_hoops_GHIP(_hoops_CSRGR, _hoops_PICI->item._hoops_HRR.id, x, 0, size, size);
				x += size;
			}
		}
		_hoops_APAI (HOOPS_WORLD->_hoops_SAAI);

#endif // _hoops_PGRPC

		_hoops_CSRGR->_hoops_AHGRR = false;
	}

	glFlush();
	if (dc->_hoops_RIGC->_hoops_HCPGR != 0)
		glFinish();

	if (_hoops_CSRGR->render_target) {
		// _hoops_HSRR _hoops_ICPP, _hoops_RGRR _hoops_RH _hoops_CCGSP. _hoops_HSRR _hoops_RRGS, _hoops_AAIR _hoops_PIRC _hoops_IS _hoops_HGCR _hoops_GSIA _hoops_PRRHP.
		H3DTEXTUREFILTERTYPE filter = (_hoops_CSRGR->_hoops_CRAP == _hoops_AHRS) ? 
			H3DTEXF_LINEAR : H3DTEXF_POINT; 

		// _hoops_AHH: _hoops_HIHH _hoops_IGRPC _hoops_HHAHP _hoops_RPGP _hoops_CGPR _hoops_SGSAC, _hoops_HIS _hoops_GHSGR _hoops_SGS _hoops_RGR _hoops_HRGR _hoops_GRGR.
		_hoops_HPHH(_hoops_CSRGR, false);

		if (_hoops_CSRGR->_hoops_PIGRR != DCT_IMAGE)
			_hoops_HGIP(_hoops_CSRGR, _hoops_CSRGR->render_target, 0, filter);
	}

	if (_hoops_CSRGR->_hoops_PIGRR == DCT_IMAGE) {
		if (!BIT (dc->flags, _hoops_SAISR))	// _hoops_PAHH _hoops_IASRH _hoops_ISHP _hoops_RH _hoops_RHPP
			return;

		if (!BIT(_hoops_CSRGR->_hoops_IHGRR->flags, _hoops_GRRH))
			HI_Clear_Image_Cache(_hoops_CSRGR->_hoops_IHGRR);
		else {
			if (_hoops_CSRGR->_hoops_IHGRR->_hoops_PHGH) {
				FREE_ARRAY(_hoops_CSRGR->_hoops_IHGRR->_hoops_PHGH, _hoops_CSRGR->_hoops_IHGRR->width * _hoops_CSRGR->_hoops_IHGRR->height * _hoops_CSRGR->_hoops_IHGRR->_hoops_GCPIR, char);
				_hoops_CSRGR->_hoops_IHGRR->_hoops_PHGH = null;
			}
		}

		if (BIT(dc->flags, _hoops_SAISR))
			HI_Set_Delayed_Activity (_hoops_CSRGR->_hoops_IHGRR->owner, _hoops_IHSSR,
									 _hoops_CSRGR->_hoops_IHGRR, _hoops_HHSSR);
	}

	if (/*!_hoops_CASRH(_hoops_CSPH) &&*/ BIT(dc->flags, _hoops_SAISR)) {
		if (_hoops_CSRGR->_hoops_PIGRR == DCT_IMAGE) {
			_hoops_SHGH alter *ptr;
			int w, h;
			w = _hoops_CSRGR->_hoops_IHGRR->width;
			h = _hoops_CSRGR->_hoops_IHGRR->height;
			if (BIT (dc->options.flags, _hoops_CIPRP)) {
				_hoops_GACR alter *dl;
				H3D_Display_List alter *odl=0;
				bool _hoops_RACR;
				H3DFORMAT fmt;

				_hoops_CSRGR->_hoops_IHGRR->flags |= _hoops_GRRH;
				_hoops_RACR = _hoops_AACR(nr, &_hoops_CSRGR->_hoops_IHGRR->_hoops_GAHA, &dl, &odl, H3D_DL_TEXTURE);
				fmt = _hoops_RSRH(_hoops_CSRGR->_hoops_IHGRR->format);
				if (_hoops_RACR) {
					odl->item.texture.id = NEW(_hoops_HGCAC)(
						_hoops_CSRGR, 
						w, h, 0,  
						H3DTEXUSAGE_RENDERTARGET,
						fmt);
					odl->_hoops_PPAH->owner = (_hoops_HPAH *)_hoops_CSRGR->_hoops_IHGRR;
				}
				bool _hoops_RSSRR = (fmt == H3DFMT_A8R8G8B8);
				_hoops_HGIP (_hoops_CSRGR, _hoops_CSRGR->render_target, odl->item.texture.id, H3DTEXF_POINT, _hoops_RSSRR, true);
			}
			else {
				if (_hoops_CSRGR->_hoops_IHGRR->format == _hoops_PCCRH) {
					// _hoops_HGI _hoops_HRGR _hoops_IPIH _hoops_GIR _hoops_GGR _hoops_GPSRH
				}
				else {
					if (_hoops_CSRGR->_hoops_IHGRR->format == _hoops_HHGH)
						ptr = (_hoops_SHGH alter *)_hoops_CSRGR->_hoops_IHGRR->_hoops_PHGH;
					else
						ALLOC_ARRAY (ptr, w*h, _hoops_SHGH);
					snapshot (nr, w, h, (unsigned char alter *)ptr);
					if (ptr != _hoops_CSRGR->_hoops_IHGRR->_hoops_PHGH) {
						_hoops_ARSRH (ptr, w, h, 
								_hoops_CSRGR->_hoops_IHGRR->format, 
								(void alter *)_hoops_CSRGR->_hoops_IHGRR->_hoops_PHGH);
						FREE_ARRAY (ptr, w*h, _hoops_SHGH);
					}
				}
			}
		}
		else if (!BIT(dc->flags, _hoops_CHSI)){
			UNREFERENCED(swap_buffers);
			SwapBuffers (_hoops_CSRGR->hDC);
		}
	}

	_hoops_GCRRR(_hoops_CSRGR);
	_hoops_RCRRR(_hoops_CSRGR);

	if (_hoops_CSRGR->hWND &&
		!dc->options._hoops_CRSSP &&
		!BIT (nr->_hoops_SRA->options._hoops_IRARR, _hoops_GCCRH))
			ValidateRect (_hoops_CSRGR->hWND, (const RECT *) &_hoops_CSRGR->_hoops_IIGRR);

	SetRectEmpty ((RECT *) &_hoops_CSRGR->_hoops_IIGRR);
}


/*
 * _hoops_SRAC
 */
void init_picture (Net_Rendition const &  nr)
{
	Display_Context const *dc = nr->_hoops_SRA;
	HOGLData alter *_hoops_CSRGR = OGLD (dc);

	// _hoops_AIAP _hoops_CGRH _hoops_IS _hoops_ASCRH _hoops_IRGAA _hoops_SRHR _hoops_PPR _hoops_PHHR _hoops_CPPRH.
	if (dc->_hoops_RIGC->_hoops_HCPGR == 0)
		_hoops_SGPAR(_hoops_CSRGR);

	_hoops_CSRGR->_hoops_CSC->_hoops_CRGRR = BIT(nr->transform_rendition->flags , _hoops_PIHIP);
	_hoops_SSPRR (_hoops_CSRGR, BIT(nr->transform_rendition->flags, _hoops_PASP));

	if (!BIT(dc->flags, _hoops_GPHHP)) {
		if (_hoops_CSRGR->_hoops_PIGRR == DCT_IMAGE) {
			Image alter				*image;

			image = (Image alter *)_hoops_RCSSR (nr->_hoops_SRA->_hoops_RIGC, dc->options._hoops_GCHSR);
			if (image != _hoops_CSRGR->_hoops_IHGRR) {
				/* _hoops_SIGP: _hoops_ISPR _hoops_IH _hoops_CSCR _hoops_IGIR _hoops_AGRP */
				if (image == null) {
					HE_ERROR (HEC_OPENGL_DRIVER, HES_INVALID_KEY,
							"An invalid key was passed to the OpenGL2 driver with USE_WINDOW_IS_IMAGE set."); 
					return;
				}
				_hoops_HPRH (_hoops_CSRGR->_hoops_IHGRR);
				_hoops_CSRGR->_hoops_IHGRR = image;
				_hoops_PRRH (_hoops_CSRGR->_hoops_IHGRR);
				MoveWindow(_hoops_CSRGR->hWND, 0,0, image->width, image->height, false);
			}
		}
	}

	if (!_hoops_CSRGR->_hoops_AHGRR) {
		// _hoops_PHAA _hoops_HSRS _hoops_HCH _hoops_AGI, _hoops_RPP _hoops_GII.
		_hoops_RCCRH(_hoops_CSRGR);

		// _hoops_HSCRH _hoops_ARHP _hoops_CCH _hoops_IIHA _hoops_GPP _hoops_IPSP'_hoops_GRI _hoops_IAGC _hoops_PPR _hoops_ISCP _hoops_ISCRH.
		_hoops_CGGRR _hoops_CSCRH = _hoops_GRGRR;
		int _hoops_AGPRH = 0;
		if ( _hoops_CSRGR->dc->options._hoops_RIPGA ) {
			_hoops_AGPRH = _hoops_CSRGR->dc->options._hoops_AIPGA;
			_hoops_CSCRH = _hoops_CSRGR->_hoops_II._hoops_SGAP ? _hoops_AHRS : _hoops_SRAP;
			if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_MSAA_SPRITING))
				_hoops_CSCRH = _hoops_AHRS;
		}

		// _hoops_AHH: _hoops_SSCRH _hoops_CHR _hoops_HA _hoops_PSPP _hoops_GGR _hoops_CGCRH. _hoops_HHIGR _hoops_PIHA _hoops_SHH _hoops_PIGS _hoops_GGR _hoops_GGSRH
		_hoops_RGPRH(_hoops_CSRGR, _hoops_CSCRH, _hoops_AGPRH );


		// _hoops_SIIR _hoops_IH _hoops_HCH-_hoops_AAR _hoops_AGI
		if (_hoops_CSRGR->_hoops_II._hoops_SGAP)
			_hoops_IGAP(_hoops_CSRGR, dc->_hoops_CGAP);

		_hoops_CSRGR->_hoops_AHGRR = true;
	}

	_hoops_RPAP (_hoops_CSRGR, !nr->_hoops_IRR->_hoops_GIRC);
	_hoops_GPRP (_hoops_CSRGR, H3DMASK_RGB);

#if defined(_hoops_SPARH)
	if (_hoops_CSRGR->_hoops_RP) {
		HANDLE _hoops_HGSRH;
		WIN32_FIND_DATA _hoops_IGSRH;
		char _hoops_CGSRH[2048];

		if (!_hoops_RHARH)
			_hoops_RHARH = POOL_NEW(dc->memory_pool, _hoops_GHARH)(dc->memory_pool);

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
				delete _hoops_CSRGR->_hoops_IP;
				_hoops_CSRGR->_hoops_IP = NEW(H3DShaderHASH)(_hoops_CSRGR);

				// _hoops_GGPRH _hoops_RHAA _hoops_AIRRR
				_hoops_CSRGR->post->_hoops_GICRR();
			}
		}
	}
#endif
}


/*
 * _hoops_SRAC
 */
void finish_update (Display_Context const * dc) {
	HOGLData alter *_hoops_CSRGR = OGLD (dc);
  
	if (!BIT(dc->flags, _hoops_SAISR))
		return;

#if 0
	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_PPSGR)
		if (!dc->options._hoops_CRSSP &&
			!BIT (dc->options._hoops_IRARR, _hoops_GCCRH))
			check_events (_hoops_CSRGR);
#endif

	wglMakeCurrent(0,0);
	if (_hoops_CSRGR->_hoops_APAAC && _hoops_CSRGR->_hoops_PPAAC)
		wglMakeCurrent(_hoops_CSRGR->_hoops_APAAC, _hoops_CSRGR->_hoops_PPAAC);
	_hoops_CSRGR->_hoops_APAAC = 0;
	_hoops_CSRGR->_hoops_PPAAC = 0;
}



/*
 * _hoops_PGAA
 */
void _hoops_IHARR(Display_Context alter * dc)
{
	Display_Context alter *_hoops_RHSRH = (Display_Context alter *) dc;
	HOGLData alter *_hoops_CSRGR = OGLD (_hoops_RHSRH);
	// _hoops_HRHI _hoops_RPPS _hoops_HRPRA
	//_hoops_GGCRH(_hoops_RGCRH, &_hoops_AGCRH);
	RECT _hoops_PGCRH;
	CopyRect(&_hoops_PGCRH, (RECT *) &_hoops_CSRGR->_hoops_IIGRR);
	GetClientRect (_hoops_CSRGR->hWND, (RECT *) &_hoops_CSRGR->_hoops_IIGRR);

	if (_hoops_PGCRH.right - _hoops_PGCRH.left !=
		_hoops_CSRGR->_hoops_IIGRR.right - _hoops_CSRGR->_hoops_IIGRR.left ||
		_hoops_PGCRH.bottom - _hoops_PGCRH.top !=
		_hoops_CSRGR->_hoops_IIGRR.bottom - _hoops_CSRGR->_hoops_IIGRR.top) {
		// _hoops_RAIGR _hoops_CCAH _hoops_RPPS _hoops_IGIR _hoops_GRS _hoops_HGAP _hoops_IRS _hoops_CCAH _hoops_AISH
		// _hoops_IGIR, _hoops_HIS _hoops_RH 3D _hoops_HCCGR _hoops_PIHA _hoops_SHH _hoops_HGAS _hoops_HGCRH.

		_hoops_CSRGR->window_width = _hoops_CSRGR->_hoops_IIGRR.right - _hoops_CSRGR->_hoops_IIGRR.left;
		_hoops_CSRGR->window_height = _hoops_CSRGR->_hoops_IIGRR.bottom - _hoops_CSRGR->_hoops_IIGRR.top;

		if (_hoops_CSRGR->window_width == 0)
			_hoops_CSRGR->window_width = 1;
		if (_hoops_CSRGR->window_height == 0)
			_hoops_CSRGR->window_height = 1;

		//_hoops_HPHPC(_hoops_CSPH);

		_hoops_CSRGR->_hoops_GSCR->_hoops_GPAP(null);
		_hoops_HP(_hoops_CSRGR->render_target);
		_hoops_HP(_hoops_CSRGR->depth_stencil);
		_hoops_HP(_hoops_CSRGR->_hoops_CACAC);
		
		_hoops_CSRGR->_hoops_CRAP = _hoops_SGGRR;
		//_hoops_HGPGA->_hoops_IPHPC = _hoops_CCAH _hoops_CPHPC(_hoops_HGPGA, _hoops_HGPGA->_hoops_GIIAC, _hoops_HGPGA->_hoops_RIIAC, 
			//_hoops_PCGAR, _hoops_SAPC, _hoops_HGPGA->_hoops_SPHPC);

		//_hoops_HGPGA->_hoops_IACAC = _hoops_CCAH _hoops_CPHPC(_hoops_HGPGA, _hoops_HGPGA->_hoops_GIIAC, _hoops_HGPGA->_hoops_RIIAC, 
			//_hoops_GCGAR, _hoops_RCGAR, _hoops_HGPGA->_hoops_SPHPC);

#if 0
		_hoops_CSRGR->_hoops_CACAC = new _hoops_RGIAC(_hoops_CSRGR, _hoops_CSRGR->window_width, _hoops_CSRGR->window_height, 
			H3DTEXUSAGE_RENDERTARGET, H3DFMT_A8R8G8B8, _hoops_CSRGR->_hoops_ISGRR);
#endif

		// _hoops_RAP _hoops_ICIH _hoops_IS _hoops_RSIR _hoops_CSCR (_hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_CACH _hoops_PCCP _hoops_AIPH _hoops_ICIH _hoops_GGR _hoops_RH _hoops_IHAH _hoops_RHSP _hoops_ASCA)
		//_hoops_GHHPC(_hoops_HGPGA, 0, 0, _hoops_HGPGA->_hoops_GIIAC, _hoops_HGPGA->_hoops_RIIAC);

		//_hoops_HGPGA->_hoops_ICRI->_hoops_RHRS(_hoops_HGPGA->_hoops_IPHPC, _hoops_HGPGA->_hoops_IACAC);
	}
	return;
}

/*
 * _hoops_SRAC
 */
void init_update (Display_Context const * dc) {
	HOGLData alter *_hoops_CSRGR = OGLD (dc);
	RECT rect;
    HWND hWND;
	bool _hoops_RHHPC = false;

	if (!BIT(dc->flags, _hoops_SAISR))
		return;
	
	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_PPSGR) {
		if (!dc->options._hoops_CRSSP &&
			!BIT (dc->options._hoops_IRARR, _hoops_GCCRH))
			check_events (_hoops_CSRGR);
		/* _hoops_HGI _hoops_SPS _hoops_III _hoops_HRGR _hoops_GIIRH _hoops_HAHH _hoops_IS _hoops_SGHIP _hoops_RH _hoops_CRS */
		_hoops_CSRGR = OGLD (dc);

		if (!_hoops_CSRGR) return;
	}

	if (!IsWindow (_hoops_CSRGR->hWND))
		return;

	_hoops_CSRGR->_hoops_APAAC = wglGetCurrentDC();
	_hoops_CSRGR->_hoops_PPAAC = wglGetCurrentContext();

	if (_hoops_CSRGR->hWND != null) {
		if (_hoops_CSRGR->_hoops_PIGRR != DCT_IMAGE && _hoops_CSRGR->_hoops_PIGRR != _hoops_IPSGR) {
			if (IsZoomed (_hoops_CSRGR->hWND))
				((Display_Context alter *) dc)->options._hoops_PASSP = true;

				GetClientRect (_hoops_CSRGR->hWND, &rect);
				CopyRect ((RECT *) &_hoops_CSRGR->_hoops_HIGRR, &rect);

				if ((rect.right-rect.left != _hoops_CSRGR->window_width) || 
						(rect.bottom-rect.top != _hoops_CSRGR->window_height)) {

				_hoops_RHHPC = true;

				_hoops_CSRGR->window_width = rect.right-rect.left;
				_hoops_CSRGR->window_height = rect.bottom-rect.top;

				_hoops_CSRGR->yfudge = rect.bottom - 1;
				hWND=_hoops_CSRGR->hWND;
				HD_Resize_Subscreen (dc, true,
									 0, rect.right - 1, 
									 0, rect.bottom - 1);

				if (!IsWindow (hWND))
					return;				
			}/*!_hoops_SASPR*/
		}
		else {
			/*_hoops_CSCR _hoops_PAR _hoops_AHHPC*/
			int *_hoops_SIGHP = (int*)dc->options._hoops_CSPRP;

#define _hoops_PHHPC 0
#define _hoops_HHHPC 1
#define _hoops_IHHPC 2
#define _hoops_CHHPC 3
			if (_hoops_SIGHP && 
				(_hoops_CSRGR->window_width != _hoops_SIGHP[_hoops_IHHPC] || _hoops_CSRGR->window_height != _hoops_SIGHP[_hoops_CHHPC])) {
				HD_Resize_Subscreen (dc, true,
									 0, _hoops_SIGHP[_hoops_IHHPC]-1, 
									 0, _hoops_SIGHP[_hoops_CHHPC]-1);
				_hoops_CSRGR->window_width = _hoops_SIGHP[_hoops_IHHPC];
				_hoops_CSRGR->window_height = _hoops_SIGHP[_hoops_CHHPC];
			}
			else {
				GetClientRect (_hoops_CSRGR->hWND, &rect);	
				_hoops_CSRGR->window_width = rect.right-rect.left;
				_hoops_CSRGR->window_height = rect.bottom-rect.top;
			}
		}

		if (_hoops_CSRGR->_hoops_APSRC) {
			/* _hoops_ACAHP _hoops_SHHPC _hoops_RH _hoops_AHGSR _hoops_GPP _hoops_HPCS _hoops_IH _hoops_RH _hoops_HSPR _hoops_PGGA _hoops_GIHPC _hoops_HRGR _hoops_RIHPC _hoops_IHHH _hoops_HHGS
			 * _hoops_RHSP _hoops_AIHPC */
			if (!wglMakeCurrent (_hoops_CSRGR->_hoops_HIISI, _hoops_CSRGR->hGLRC)) {
				/* _hoops_PSRHR (_hoops_PIHPC, _hoops_HIHPC,
						  "_hoops_IIHPC _hoops_IS _hoops_CIHPC _hoops_GPP _hoops_HIHH _hoops_PPGS _hoops_GGSC _hoops_RHSP _hoops_CCCSI"); */
				HD_Kill_Driver (dc);
				return;
			}
		}
		else {
			if (!wglMakeCurrent (_hoops_CSRGR->hDC, _hoops_CSRGR->hGLRC)) {
				/* _hoops_PSRHR (_hoops_PIHPC, _hoops_HIHPC,
						  "_hoops_IIHPC _hoops_IS _hoops_CIHPC _hoops_GPP _hoops_HIHH _hoops_GGSC _hoops_RHSP _hoops_CCCSI"); */
				HD_Kill_Driver (dc);
				return;
			}

			if (_hoops_RHHPC)
				_hoops_IHARR((Display_Context alter *) dc);
		}
	}/*_hoops_RGCRH*/
} /* _hoops_RSGR _hoops_API _hoops_CCCSI */



/*****************************************************************************
 *****************************************************************************
								_hoops_PPSRH
 *****************************************************************************
 *****************************************************************************/


/*
 * _hoops_SRAC
 */
local  bool _hoops_GGSSP (
	Net_Rendition const &	nr,
	Font_Instance const *	specific) {

	UNREFERENCED(specific);
	UNREFERENCED(nr);

	return true;
}

/*
 * _hoops_SRAC
 */
local bool measure_char (
	Net_Rendition const &	nr,
	Font_Instance const *	instance,
	Karacter _hoops_IPCSR,
	float alter *_hoops_GGGS,
	bool alter *_hoops_CPCSR,
	void ** _hoops_HPSRH) {

	return HI_W32_measure_char_stenciled (nr, instance, _hoops_IPCSR, _hoops_GGGS, _hoops_CPCSR, _hoops_HPSRH);
}

/*
 * _hoops_SRAC
 */
local _hoops_RAARP * _hoops_RGSSP (
	Net_Rendition const &	nr,
	Font_Instance const	*	instance,
	unsigned short			_hoops_IPCSR,
	int						bitmap_height,
	int						bolding_level,
	float					xrslant,
	float					xrrotation,
	float					xrwidth_scale,
	bool					antialias) {

	UNREFERENCED(nr);

	return HI_W32_make_font_stencil (instance, _hoops_IPCSR, 
									bitmap_height, bolding_level,
									xrslant,xrrotation,xrwidth_scale,
									antialias); 
}



/*
 * _hoops_SRAC
 */
local void unload_font (
	Display_Context const *	dc, 
	Font_Instance alter *	instance) {

	HI_W32_unload_font_stenciled (dc, instance);
}


/*
 * _hoops_SRAC
 */
local void * load_font (
	Display_Context const * dc,
	char const * name,
	Font_Instance alter * instance) {

	HOGLData alter *_hoops_CSRGR = OGLD (dc);
	_hoops_RRPRH alter *_hoops_IRSRA = _hoops_ARPRH ();

	return HI_W32_load_font_stenciled(dc, name, instance, _hoops_CSRGR->hDC, &_hoops_CSRGR->_hoops_GRRRR, &_hoops_IRSRA->font_list);	 
}


/*
 * _hoops_SRAC
 */
local bool _hoops_CSCSP (
	Net_Rendition const &	nr,
	_hoops_IGPIR const *		_hoops_RRCSP,
	_hoops_IGPIR alter *		_hoops_ARCSP) {
	
	return HI_W32_name_font(nr, _hoops_RRCSP, _hoops_ARCSP);
}


/*
 * _hoops_SRAC
 */
local void find_all_fonts (
	Display_Context alter *	dc) {
	HOGLData alter *			_hoops_CSRGR = OGLD (dc);
	_hoops_RRPRH alter *		_hoops_IRSRA = _hoops_ARPRH ();

	HI_W32_find_all_fonts (dc, &_hoops_CSRGR->_hoops_GRRRR, &_hoops_IRSRA->font_list);
}


/*
 *	** _hoops_SRAC **
 */
local bool _hoops_AACSR (
	Display_Context alter *	dc,
	char const *			_hoops_PACSR) {
	HOGLData alter *			_hoops_CSRGR = OGLD (dc);
	_hoops_RRPRH alter *		_hoops_IRSRA = _hoops_ARPRH ();

	return HI_W32_find_one_font (dc, _hoops_PACSR, _hoops_CSRGR->hDC, &_hoops_CSRGR->_hoops_GRRRR, &_hoops_IRSRA->font_list);
}

/*
 * _hoops_SRAC
 */
local void _hoops_CACSR (
	Display_Context alter *	dc) {
	HOGLData alter *			_hoops_CSRGR = OGLD (dc);
	_hoops_RRPRH alter *		_hoops_IRSRA = _hoops_ARPRH ();

	HI_W32_find_basic_fonts (dc, _hoops_CSRGR->hDC, &_hoops_CSRGR->_hoops_GRRRR, &_hoops_IRSRA->font_list);
}


/*****************************************************************************
 *****************************************************************************
								_hoops_CPIRH _hoops_SPIRH
 *****************************************************************************
 *****************************************************************************/

/*
 * _hoops_PGAA
 */
void check_events (HOGLData alter * _hoops_CSRGR) {
	MSG _hoops_SSACR;

	_hoops_CSRGR->_hoops_IRRRR = false;

	while (PeekMessage (&_hoops_SSACR, _hoops_CSRGR->hWND, 0, 0, PM_NOREMOVE) &&
		   GetMessage (&_hoops_SSACR, _hoops_CSRGR->hWND, 0, 0)) {
		TranslateMessage (&_hoops_SSACR);
		DispatchMessage (&_hoops_SSACR);
	}
}


/*
 * _hoops_PGAA
 */
local void consume_key (
	HOGLData alter * _hoops_CSRGR,
	UINT word_parameter,
	LONG _hoops_GHIRH) {

	int					key;
	BYTE		_hoops_RHIRH[256];
	int					status = 0;

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
			key = INSERT_KEY;
		}	break;

		case VK_END: {
			key = END_KEY;
		}	break;

		case VK_HOME: {
			key = HOME_KEY;
		}	break;

		case VK_PRIOR: {
			key = PAGE_UP_KEY;
		}	break;

		case VK_NEXT: {
			key = PAGE_DOWN_KEY;
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
		}	break;

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
		}	break;

		case VK_RIGHT: {
			key = RIGHT_ARROW_KEY;
		}	break;

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
		} _hoops_HHHI;
	}

	if (key != 0)
			HI_Queue_Keyboard_Event ((_hoops_GGAGR alter *)_hoops_CSRGR->dc->_hoops_GHRI, key, status);
}




/*
 * _hoops_PGAA
 */
local void
consume_mouse (HOGLData alter * _hoops_CSRGR,
			   UINT event, UINT wParam, LONG lParam) {
	UNREFERENCED(wParam);

	switch (event) {
		case WM_RBUTTONDOWN: {
			_hoops_CSRGR->_hoops_HRRRR |= _hoops_ARRRR;
		}	break;
		case WM_MBUTTONDOWN: {
			_hoops_CSRGR->_hoops_HRRRR |= _hoops_PRRRR;
		}	break;
		case WM_LBUTTONDOWN: {
			_hoops_CSRGR->_hoops_HRRRR |= _hoops_RRRRR;
		}	break;

		case WM_RBUTTONUP: {
			_hoops_CSRGR->_hoops_HRRRR &= ~_hoops_ARRRR;
		}	break;
		case WM_MBUTTONUP: {
			_hoops_CSRGR->_hoops_HRRRR &= ~_hoops_PRRRR;
		}	break;
		case WM_LBUTTONUP: {
			_hoops_CSRGR->_hoops_HRRRR &= ~_hoops_RRRRR;
		}	break;
	}

	_hoops_CSRGR->_hoops_SCGRR = LOWORD (lParam);
	_hoops_CSRGR->mouse_y = _hoops_CSRGR->yfudge - HIWORD (lParam);

	HD_Queue_Pixel_Location_Event (_hoops_CSRGR->dc, _hoops_CSRGR->_hoops_HRRRR,
								   _hoops_CSRGR->_hoops_SCGRR, _hoops_CSRGR->mouse_y);
	_hoops_CSRGR->_hoops_IRRRR = true;
}


/*
 * _hoops_SRAC
 */
bool _hoops_HSCSP (Display_Context const * dc,
				  int alter * button,
				  int alter * x, int alter * y) {
	HOGLData alter *_hoops_CSRGR = OGLD (dc);

	if (_hoops_CSRGR != null) {
		check_events (_hoops_CSRGR);
		/* _hoops_HGI _hoops_SPS _hoops_III _hoops_HRGR _hoops_GIIRH _hoops_HAHH _hoops_IS _hoops_SGHIP _hoops_RH _hoops_CRS */
		_hoops_CSRGR = OGLD (dc);
		/*
		 * _hoops_HGI _hoops_API _hoops_PIHA _hoops_SHR _hoops_RHRRH _hoops_IRS _hoops_GISAP "_hoops_PIAP",
		 * _hoops_HIS _hoops_RPP _hoops_RIIRH _hoops_SSAS _hoops_HAR _hoops_RHRRH _hoops_PCCP _hoops_CPGGR _hoops_AIH
		 * _hoops_AIIRH, _hoops_SR _hoops_PIHA _hoops_RHRRH _hoops_SPR _hoops_ARI.
		 * _hoops_PS _hoops_GRS _hoops_SAHR _hoops_ASAR-_hoops_RHRRH _hoops_RH _hoops_CGHI _hoops_GISAP _hoops_PIAP _hoops_SGS
		 * _hoops_SR _hoops_HARRA.
		 */
		if (_hoops_CSRGR == null || _hoops_CSRGR->_hoops_IRRRR)
			return false;
		else {
			*button = _hoops_CSRGR->_hoops_HRRRR;
			*x = _hoops_CSRGR->_hoops_SCGRR;
			*y = _hoops_CSRGR->mouse_y;
			return true;
		}
	}

	return false;
}


/*
 * _hoops_SRAC
 */
bool _hoops_ISCSP (Display_Context const * dc,
				  int alter * button, int alter * status) {
	HOGLData alter *_hoops_CSRGR = OGLD (dc);

	UNREFERENCED(status);
	UNREFERENCED(button);

	if (_hoops_CSRGR != null) {
		check_events (_hoops_CSRGR);
		/* _hoops_HGI _hoops_SPS _hoops_III _hoops_HRGR _hoops_GIIRH _hoops_HAHH _hoops_IS _hoops_SGHIP _hoops_RH _hoops_CRS */
		_hoops_CSRGR = OGLD (dc);

		/*
		 * _hoops_RIIRH _hoops_GRS _hoops_SHR _hoops_HS _hoops_PIIRH _hoops_GII _hoops_HIIRH
		 * _hoops_IS _hoops_IRISR _hoops_AIH _hoops_IIIRH.  _hoops_CPGP _hoops_IRISR _hoops_ASSP'_hoops_RA
		 * _hoops_RRP _hoops_IS _hoops_ACPA _hoops_RH "_hoops_PIAP" _hoops_IIGR _hoops_RH _hoops_CIIRH, _hoops_RGR _hoops_API
		 * _hoops_PAH _hoops_IGIRR _hoops_ASRC _hoops_RCPP.
		 */
	}
	return false;
}



/*****************************************************************************
 *****************************************************************************
								_hoops_HGGSP _hoops_PARPI
 *****************************************************************************
 *****************************************************************************/

/*
 * _hoops_PGAA
 */
local void
_hoops_HGGAH (Display_Context alter * dc) {
	HOGLData alter *_hoops_CSRGR = OGLD (dc);
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

	_hoops_SGGAH = _hoops_CSRGR->hWND;

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

	_hoops_CSRGR->_hoops_HCGRR =
		_hoops_CSRGR->_hoops_RCGRR = _hoops_CSRGR->_hoops_ACGRR =
		_hoops_CSRGR->_hoops_PCGRR = 0;

	if (_hoops_CSRGR->_hoops_PIGRR == DCT_IMAGE ||
		_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR) {
		dc->current.extent.left = (float) 0;
		dc->current.extent.right = (float) dc->_hoops_PGCC._hoops_PRPSR.x - 1;
		dc->current.extent.bottom = (float) 0;
		dc->current.extent.top = (float) dc->_hoops_PGCC._hoops_PRPSR.y - 1;
	}
	else {
		if (_hoops_CSRGR->hWND == null) {
			/* _hoops_AGAH _hoops_GRS _hoops_SHH _hoops_GRP _hoops_RGR _hoops_HPHS _hoops_IS _hoops_ARPR _hoops_RH _hoops_SHIR
			   _hoops_RPPS _hoops_HIS _hoops_SR _hoops_PIHA _hoops_PSIIR _hoops_SCH _hoops_IS _hoops_ASSS _hoops_IH _hoops_RH _hoops_HPRGR _hoops_GPAA */
			/* _hoops_GAGAH _hoops_RAGAH _hoops_PPR _hoops_GPAA */
			if (dc->options._hoops_AASSP) {
				_hoops_CSRGR->_hoops_ACGRR =
					_hoops_CSRGR->_hoops_PCGRR = GetSystemMetrics (SM_CXFRAME);
				_hoops_CSRGR->_hoops_RCGRR = GetSystemMetrics (SM_CYFRAME);
			}
			else {
				_hoops_CSRGR->_hoops_ACGRR =
					_hoops_CSRGR->_hoops_PCGRR = GetSystemMetrics (SM_CXBORDER);
				_hoops_CSRGR->_hoops_RCGRR = GetSystemMetrics (SM_CYBORDER);
			}
			_hoops_CSRGR->_hoops_HCGRR = _hoops_CSRGR->_hoops_RCGRR +
				GetSystemMetrics (SM_CYCAPTION) - 1;
		}
		else {
			/* _hoops_PSIH _hoops_GPAA _hoops_IIGR _hoops_APRS _hoops_RPPS */
			_hoops_CSRGR->_hoops_ACGRR = _hoops_PCRSP.right - _hoops_IGGAH.right;
			_hoops_CSRGR->_hoops_PCGRR = _hoops_IGGAH.left - _hoops_PCRSP.left;
			_hoops_CSRGR->_hoops_HCGRR = _hoops_IGGAH.top - _hoops_PCRSP.top;
			_hoops_CSRGR->_hoops_RCGRR = _hoops_PCRSP.bottom - _hoops_IGGAH.bottom;
		}

		dc->current.extent.left = (float) _hoops_PCRSP.left;
		dc->current.extent.right = (float) _hoops_PCRSP.right - 1;
		dc->current.extent.bottom = (float) (_hoops_CSRGR->_hoops_CCGRR - (_hoops_PCRSP.bottom - 1));
		dc->current.extent.top = (float) (_hoops_CSRGR->_hoops_CCGRR - _hoops_PCRSP.top);
	}
}

/*****************************************************************************
 *****************************************************************************
				_hoops_RRIA _hoops_RPGGP _hoops_SICAR
 *****************************************************************************
 *****************************************************************************/


/*
 * _hoops_SRAC
 */
void get_current_info (Display_Context alter * dc) 
{
	HOGLData alter *_hoops_CSRGR = OGLD (dc);
	HDC hDC;
	int *_hoops_SIGHP;

	if (_hoops_CSRGR->hDC == 0)
		hDC = _hoops_CSRGR->_hoops_SHGRR;
	else
		hDC = _hoops_CSRGR->hDC;


	if (dc->options._hoops_GCHSR != 0) {
		dc->options._hoops_RASSP = true;
		dc->options._hoops_AASSP = true;
		dc->options._hoops_PASSP = true;
		dc->options._hoops_HPHRP = false;
	}
#if 0	 
	GLint _hoops_RCHA[3] = { 0, 0, 0 };
	if (_hoops_CSRGR->hGLRC) {
		glGetIntegerv (GL_RED_BITS, _hoops_RCHA);
		glGetIntegerv (GL_BLUE_BITS, _hoops_RCHA + 1);
		glGetIntegerv (GL_GREEN_BITS, _hoops_RCHA + 2);
		_hoops_CSRGR->_hoops_SAHGC = _hoops_RCHA[0] + _hoops_RCHA[1] + _hoops_RCHA[2];
	}
#endif
	/* _hoops_HIHH _hoops_SHR _hoops_APPP 8 _hoops_SIH _hoops_RIR _hoops_AIHSR */
	dc->current._hoops_AAPSR = 1L << 24;
	dc->current._hoops_APASR = 0;

	_hoops_HGGAH (dc);

	_hoops_SIGHP = (int*)dc->options._hoops_CSPRP;
	if (_hoops_SIGHP) {
		dc->current.extent.left = (float) 0;
		dc->current.extent.right = (float) _hoops_SIGHP[_hoops_IHHPC];
		dc->current.extent.bottom = (float) 0;
		dc->current.extent.top = (float) _hoops_SIGHP[_hoops_CHHPC];
	}

	if (dc->options.border) {
		HD_Allow_For_Border (dc, _hoops_CSRGR->_hoops_ACGRR,
							 _hoops_CSRGR->_hoops_PCGRR, _hoops_CSRGR->_hoops_RCGRR,
							 _hoops_CSRGR->_hoops_HCGRR);
	}
}


/*
 * _hoops_SRAC
 */
void get_physical_info (Display_Context alter * dc) {
	HOGLData alter *_hoops_CSRGR = OGLD (dc);
	HDC hDC;

	if (_hoops_CSRGR->hDC == 0)
		hDC = _hoops_CSRGR->_hoops_SHGRR;
	else
		hDC = _hoops_CSRGR->hDC;	  

	/* _hoops_PS _hoops_AA _hoops_HAR _hoops_AA _hoops_IPPSR _hoops_PCRR */
	dc->_hoops_PGCC._hoops_PIPGH = false;
	dc->_hoops_PGCC.flags |= _hoops_PPPGH;

	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR ||
		_hoops_CSRGR->_hoops_PIGRR == DCT_IMAGE) {
		dc->_hoops_PGCC._hoops_PRPSR.x = _hoops_CSRGR->_hoops_IHGRR->width;
		dc->_hoops_PGCC._hoops_PRPSR.y = _hoops_CSRGR->_hoops_IHGRR->height;
		dc->_hoops_PGCC.size.x = dc->_hoops_PGCC._hoops_PRPSR.x * (2.54f / 72.0f);
		dc->_hoops_PGCC.size.y = dc->_hoops_PGCC._hoops_PRPSR.y * (2.54f / 72.0f);
	}
	else {
		dc->_hoops_PGCC._hoops_PRPSR.x = GetDeviceCaps (hDC, HORZRES);
		dc->_hoops_PGCC._hoops_PRPSR.y = GetDeviceCaps (hDC, VERTRES);
		
		dc->_hoops_PGCC.size.x = GetDeviceCaps (hDC, HORZSIZE) / 10.0f;

		if (dc->_hoops_PGCC.size.x == 0.0f) dc->_hoops_PGCC.size.x = 30.0f;
		
		/* _hoops_HR _hoops_IGAA _hoops_GGSP _hoops_PPR _hoops_AIR _hoops_CHR _hoops_RRAA */
		dc->_hoops_PGCC.size.y = (float) dc->_hoops_PGCC._hoops_PRPSR.y /
			(float) dc->_hoops_PGCC._hoops_PRPSR.x * dc->_hoops_PGCC.size.x;
 
		_hoops_CSRGR->yfudge = _hoops_CSRGR->_hoops_CCGRR = dc->_hoops_PGCC._hoops_PRPSR.y - 1;

		_hoops_HGGAH (dc);
	}

	if (dc->options._hoops_SPHSR.x != -1) {
		dc->_hoops_PGCC.size.x = dc->options._hoops_SPHSR.x;
		dc->_hoops_PGCC.size.y = dc->options._hoops_SPHSR.y;
	}

	_hoops_CSRGR->yfudge = _hoops_CSRGR->_hoops_CCGRR = dc->_hoops_PGCC._hoops_PRPSR.y - 1;

	_hoops_HGGAH (dc);

	/* _hoops_PPSI _hoops_GGR _hoops_GHAR _hoops_RGGHR _hoops_ARI..._hoops_SAHR _hoops_GGR _hoops_AGIR _hoops_RH _hoops_RPGP _hoops_RPPS _hoops_ISHS */
	dc->_hoops_PGCC._hoops_PCHSR = 256;
	dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;
	dc->_hoops_PGCC.driver_type = "WOGL";
	dc->_hoops_PGCC._hoops_SCHSR = "$Revision: 1.154 $";
	dc->_hoops_PGCC._hoops_ICHSR = "frame buffer";
	dc->_hoops_PGCC._hoops_RCPGH = "mouse";
	
	/* _hoops_IHH _hoops_AAARR _hoops_ARP _hoops_IS _hoops_RCPP _hoops_CCGR _hoops_SR _hoops_CACH _hoops_IRS _hoops_APIP _hoops_GGSC */
	dc->_hoops_PGCC.flags &= ~_hoops_SGICP;
	dc->_hoops_PGCC.flags &= ~_hoops_GPPGH;

	dc->_hoops_PGCC.flags &= ~_hoops_GGISR;

	_hoops_CSRGR->_hoops_PPHGC = false;
	_hoops_CSRGR->_hoops_HGARR = true;

	_hoops_CSRGR->_hoops_ACGH._hoops_GRGI = _hoops_IICIA;
	_hoops_CSRGR->_hoops_ACGH._hoops_PAARR = _hoops_SARAR;
	dc->_hoops_PGCC._hoops_HCPGH = 4;

	dc->_hoops_PGCC._hoops_IIPGH[0] = QMoves_Accumulation;
	dc->_hoops_PGCC._hoops_IIPGH[1] = QMoves_Spriting;
	dc->_hoops_PGCC.flags |= _hoops_PAGIP;

	/*
	 * _hoops_SIHPC:	 _hoops_PGGA _hoops_IIH _hoops_HRGR _hoops_GCHPC _hoops_IIGR _hoops_HPHS _hoops_SGS _hoops_SR _hoops_AA _hoops_ASAI
	 * _hoops_ACPA _hoops_CCGR _hoops_PCCP _hoops_HIHH-_hoops_RAHRH-_hoops_RCHPC _hoops_RPPS _hoops_HRGR _hoops_SCGH, _hoops_SR _hoops_AA
	 * _hoops_PCCP _hoops_PAAP _hoops_CPHSR _hoops_SIHC _hoops_GGR _hoops_HGSR _hoops_ICCI
	 * _hoops_HGI _hoops_IGISR _hoops_GGR _hoops_AGRR _hoops_HPHS (_hoops_ACHPC _hoops_AHCA _hoops_RH _hoops_PHI
	 * _hoops_IIGR _hoops_GHC _hoops_HHPA _hoops_CR _hoops_SCH _hoops_HRGR _hoops_AACC _hoops_GGR _hoops_HHAA _hoops_CGPR _hoops_RHAC _hoops_AA _hoops_GHGPR
	 * _hoops_RHGPR) _hoops_SGS _hoops_CGH _hoops_PCHPC _hoops_SHH _hoops_CPHR _hoops_ARI... _hoops_AA _hoops_PCCP
	 * _hoops_HCHPC _hoops_ARI _hoops_HIH _hoops_PCSA _hoops_SGS _hoops_RGR _hoops_SIHC _hoops_GHCA _hoops_AGRP...
	 */
	if (_hoops_CSRGR->hGLRC)
		_hoops_IAHGC (dc);

	/* _hoops_CCRAA _hoops_ICHPC _hoops_CRPGH _hoops_HRGR _hoops_SHR _hoops_HHPA _hoops_GGR _hoops_HIHH */
	dc->_hoops_PGCC._hoops_CHHSR = _hoops_RCPGA;
/* _hoops_CSPH->_hoops_CPHSR._hoops_AAGAH = _hoops_CCHPC; *//* _hoops_SCHPC _hoops_RPGP */

	/* _hoops_IHH _hoops_AAARR */
	dc->_hoops_PGCC.flags |= _hoops_SGICP;
	dc->_hoops_PGCC.flags |= _hoops_GPPGH;

	dc->_hoops_PGCC._hoops_HGCC = 1; /*_hoops_RGR _hoops_ICHHR _hoops_AAPA _hoops_PAPA _hoops_SCSAH*/

	if (BIT (dc->options._hoops_IRARR, _hoops_GHGAC))
		dc->_hoops_PGCC.flags |= _hoops_GIHSR;

	if (GetSystemMetrics (SM_MOUSEPRESENT) != 0)
		dc->_hoops_PGCC.flags |= _hoops_RSHSR;
	else
		dc->_hoops_PGCC.flags &= ~_hoops_RSHSR;

	dc->_hoops_PGCC._hoops_ASHSR =
		GetSystemMetrics (SM_CMOUSEBUTTONS);

/*_hoops_CGHGH _hoops_SCPGH*/
	{
		int _hoops_ACISI;

		_hoops_ACISI = GetDeviceCaps (hDC, TEXTCAPS);

		_hoops_CSRGR->_hoops_RPICI = _hoops_CRGGH;
	}

	if (dc->options._hoops_RGHRP == _hoops_GGHRP || BIT (dc->options._hoops_IRARR, _hoops_GCSRH))
		dc->_hoops_PGCC.flags |= _hoops_RHPGH;
}

/*****************************************************************************
 *****************************************************************************
						_hoops_GCIH/_hoops_SCPRH _hoops_IPSRH 
 *****************************************************************************
 *****************************************************************************/

/****************************
* _hoops_GSHPC _hoops_IIGR _hoops_HGGSP _hoops_RSHPC
*****************************/

local LRESULT APIENTRY _hoops_ASHPC (
										HWND _hoops_GRCRH,
										UINT message,
										WPARAM wParam, 
										LPARAM lParam);

local LRESULT APIENTRY _hoops_AICRH (
										HWND _hoops_GRCRH,
										UINT message,
										WPARAM wParam, 
										LPARAM lParam);


/*
 * _hoops_SRAC
 */
bool start_device (Display_Context alter * dc) {

#ifdef _DEBUG
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	HOGLData *_hoops_CSRGR;
	ZALLOC (_hoops_CSRGR, HOGLData);

	/*_hoops_GIPR _hoops_ARP _hoops_HIS _hoops_AISRH _hoops_HRGR _hoops_IGI _hoops_IH _hoops_CSRPC*/
	dc->data = (void alter *) _hoops_CSRGR;
	dc->_hoops_RIHGR = (void alter *) _hoops_CSRGR;
	_hoops_CSRGR->dc = dc;

	_hoops_CSRGR->_hoops_IP	= NEW(H3DShaderHASH)(_hoops_CSRGR);
	_hoops_CSRGR->_hoops_RRCI = _hoops_APARR::Create(dc->memory_pool);

	if (!dc->options._hoops_GCHSR) {

		_hoops_CSRGR->_hoops_PIGRR = _hoops_PPSGR;
		_hoops_CSRGR->_hoops_SHGRR = GetDC (GetDesktopWindow ());
	} 
	else if (dc->options._hoops_RGHRP == _hoops_GGHRP || BIT (dc->options._hoops_IRARR, _hoops_GCSRH)) {
		Image alter				*image;

		image = (Image alter *)_hoops_RCSSR (dc->_hoops_RIGC, dc->options._hoops_GCHSR);
		if (image == null) {
			HE_ERROR (HEC_OPENGL_DRIVER, HES_INVALID_KEY,
					"An invalid key was passed to the OpenGL driver with USE_WINDOW_IS_IMAGE set."); 
			return false;
		}
		if (image->_hoops_PHGH == 0 ||
			!(image->format == Image_RGBA32 || 
			 image->format == _hoops_HRSRH || 
			 image->format == _hoops_CSGSP || 
			 image->format == _hoops_HHGH || 
			 image->format == _hoops_PCCRH ||
			 image->format == _hoops_AHGH)) {
			HE_ERROR (HEC_OPENGL_DRIVER, HES_INVALID_KEY,
					"OpenGL output image unsupported format."); 
			return false;
		}
		if (image->height < 1 || image->width < 1) {
			HE_ERROR (HEC_OPENGL_DRIVER, HES_INVALID_KEY,
					"OpenGL output images must be at least 1x1."); 
			return false;
		}

		/* _hoops_IIRAR _hoops_GSIA _hoops_AHPGH _hoops_AIH _hoops_SRGAC, _hoops_HIH _hoops_PSHPC 
			_hoops_GRS _hoops_SPHR _hoops_HSHPC _hoops_IS _hoops_ISHPC _hoops_RPP _hoops_ISCP _hoops_HGSR _hoops_RRGR _hoops_HRGR
			_hoops_CSHPC */
		_hoops_CSRGR->_hoops_PIGRR = DCT_IMAGE;
		_hoops_CSRGR->_hoops_SHGRR = GetDC (GetDesktopWindow ());
		_hoops_CSRGR->_hoops_IHGRR = image;
		_hoops_PRRH (_hoops_CSRGR->_hoops_IHGRR);
	}
	else {
		_hoops_CSRGR->_hoops_PIGRR = _hoops_HPSGR;
		_hoops_CSRGR->hWND = (HWND) dc->options._hoops_GCHSR;
		_hoops_CSRGR->hDC = GetDC (_hoops_CSRGR->hWND);
		_hoops_CSRGR->_hoops_SHGRR = _hoops_CSRGR->hDC;

#ifdef _WIN64
		_hoops_RCSRH (_hoops_ACSRH) =
			(HINSTANCE) GetWindowLongPtr (_hoops_CSRGR->hWND, GWLP_HINSTANCE);
#else
		_hoops_RCSRH (_hoops_ACSRH) =
			(HINSTANCE) GetWindowLong (_hoops_CSRGR->hWND, GWL_HINSTANCE);
#endif

		/* _hoops_GRPHA _hoops_RH _hoops_CSPH _hoops_HIS _hoops_SGS _hoops_PCSRH _hoops_GRS _hoops_IPHR */
		((Display_Context alter *) dc)->current._hoops_RAPGH = (POINTER_SIZED_INT) _hoops_CSRGR->hWND;

		if (!dc->options._hoops_CRSSP &&
			!BIT (dc->options._hoops_IRARR, _hoops_GCCRH)) {

			_hoops_CSRGR->_hoops_SHGRR = GetDC (GetDesktopWindow ());
#ifdef _WIN64
			_hoops_CSRGR->_hoops_GIGRR =
				(WNDPROC) GetWindowLongPtr (_hoops_CSRGR->hWND, GWLP_WNDPROC);

			SetWindowLongPtr (_hoops_CSRGR->hWND, GWLP_WNDPROC,
						   (POINTER_SIZED_INT) _hoops_AICRH);
#else
			_hoops_CSRGR->_hoops_GIGRR =
				(WNDPROC) GetWindowLong (_hoops_CSRGR->hWND, GWL_WNDPROC);

			SetWindowLong (_hoops_CSRGR->hWND, GWL_WNDPROC,
						   (LONG) _hoops_AICRH);
#endif
		}
	}

	return true;
}


/*
 * _hoops_SRAC
 */
void stop_device (Display_Context alter * dc) {
	HOGLData alter *_hoops_CSRGR = OGLD (dc);

	if (_hoops_CSRGR == null) return;

	/* _hoops_RCSH _hoops_GII _hoops_ASSRH _hoops_SHCA'_hoops_GRI _hoops_SR _hoops_SPIP */
	switch (_hoops_CSRGR->_hoops_PIGRR) {

		case _hoops_PPSGR:
		case _hoops_IPSGR:
		case DCT_IMAGE:
			_hoops_CSRGR->_hoops_PIGRR = _hoops_APSGR;
			ReleaseDC (GetDesktopWindow (), _hoops_CSRGR->_hoops_SHGRR);
			if (_hoops_CSRGR->_hoops_IHGRR) {
				_hoops_HPRH (_hoops_CSRGR->_hoops_IHGRR);
			}
		break;

		case _hoops_HPSGR:
			/* _hoops_IPPRA _hoops_RPPS _hoops_PSSRH _hoops_RPP _hoops_RGCI _hoops_ARP */
			if (!dc->options._hoops_CRSSP &&
				!BIT (dc->options._hoops_IRARR, _hoops_GCCRH)) {
#ifdef _WIN64
				SetWindowLongPtr (_hoops_CSRGR->hWND, GWLP_WNDPROC,
							   (POINTER_SIZED_INT) _hoops_CSRGR->_hoops_GIGRR);
#else
				SetWindowLong (_hoops_CSRGR->hWND, GWL_WNDPROC,
							   (LONG) _hoops_CSRGR->_hoops_GIGRR);
#endif
				_hoops_CSRGR->_hoops_GIGRR = null;
			}
			ReleaseDC (GetDesktopWindow (), _hoops_CSRGR->_hoops_SHGRR);

			/* _hoops_SSHPC (_hoops_CSPH); */
		break;
	}

	
	/*_hoops_RGR _hoops_CRRHP _hoops_RH _hoops_IRGH _hoops_HRCSR _hoops_HIGR*/
	{
		_hoops_SGRRR * _hoops_HSSRH = _hoops_CSRGR->_hoops_GRRRR;
		_hoops_SGRRR * _hoops_ISSRH;

		while (_hoops_HSSRH) {
			_hoops_ISSRH = _hoops_HSSRH->next;

			FREE_ARRAY (_hoops_HSSRH->name, _hoops_SSGR(_hoops_HSSRH->name) + 1, char);

			if (_hoops_HSSRH->specific)
				FREE_ARRAY (_hoops_HSSRH->specific, _hoops_SSGR(_hoops_HSSRH->specific) + 1, char);

			FREE (_hoops_HSSRH, _hoops_SGRRR);

			_hoops_HSSRH = _hoops_ISSRH;
		}

		_hoops_CSRGR->_hoops_GRRRR = 0;
	}

	if (_hoops_CSRGR->_hoops_PRARR)
		HI_Free_Driver_Config(_hoops_CSRGR->_hoops_PRARR);

	_hoops_CSRGR->_hoops_RRCI = null;

	_hoops_ACIRH(dc);

	_hoops_HP(_hoops_CSRGR->glewcontext); 
	_hoops_HP(_hoops_CSRGR->wglewcontext);

	FREE (_hoops_CSRGR, HOGLData);
	/*_hoops_GIPR _hoops_ARP _hoops_HIS _hoops_AISRH _hoops_HRGR _hoops_IGI _hoops_IH _hoops_CSRPC*/
	dc->data = null;
	dc->_hoops_RIHGR = null;
}


/*****************************************************************************
 *****************************************************************************
						_hoops_HGGSP _hoops_PARPI _hoops_ACPIH 
 *****************************************************************************
 *****************************************************************************/


local POINTER_SIZED_INT
_hoops_GGIPC(Display_Context *dc)
{
	HOGLData alter *_hoops_CSRGR = OGLD (dc);
	Image alter *image;

	image = _hoops_CSRGR->_hoops_IHGRR;

	_hoops_CSRGR->hWND = 
		CreateWindow ("HoopsWClassOGL2", "ogl_image_hwnd", 
			WS_POPUP,
			0,0, 
			_hoops_CSRGR->_hoops_IHGRR->width, 
			_hoops_CSRGR->_hoops_IHGRR->height,
			null, null, _hoops_RCSRH (_hoops_ACSRH), (LPSTR) dc);

	if (_hoops_CSRGR->hWND == null) {
		HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_CREATE_WINDOW,
				  "Unable to Create a Window in ogl_wgl:create image hwnd");
		HD_Kill_Driver (dc);
		return 0;
	}

	return (POINTER_SIZED_INT)(POINTER_SIZED_INT) _hoops_CSRGR->hWND;

} /* _hoops_RSGR _hoops_API '_hoops_ARPR _hoops_CSCR _hoops_RGIPC' */


local POINTER_SIZED_INT
_hoops_AGIPC(Display_Context *dc)
{
	HOGLData alter *_hoops_CSRGR = OGLD (dc);
	DWORD window_style;
	char _hoops_IAPIR[4096];
	HMONITOR		_hoops_IGRAH;
	MONITORINFO		_hoops_CGRAH = { sizeof(_hoops_CGRAH) };
	const	POINT			_hoops_SGRAH = { 0, 0 };

	/* _hoops_GAGAH _hoops_RAGAH _hoops_PPR _hoops_GPAA */
	if (dc->options._hoops_AASSP) {
		_hoops_CSRGR->_hoops_ACGRR =
			_hoops_CSRGR->_hoops_PCGRR = GetSystemMetrics (SM_CXFRAME);
		_hoops_CSRGR->_hoops_RCGRR = GetSystemMetrics (SM_CYFRAME);
	}
	else {
		_hoops_CSRGR->_hoops_ACGRR =
			_hoops_CSRGR->_hoops_PCGRR = GetSystemMetrics (SM_CXBORDER);
		_hoops_CSRGR->_hoops_RCGRR = GetSystemMetrics (SM_CYBORDER);
	}
	_hoops_CSRGR->_hoops_HCGRR = _hoops_CSRGR->_hoops_RCGRR +
		GetSystemMetrics (SM_CYCAPTION) - 1;

	/* _hoops_CAHA _hoops_GGSR _hoops_RH _hoops_RPPS _hoops_IAHA */
	window_style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW;

	if (!dc->options._hoops_AASSP) {
		window_style &= ~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_MINIMIZE | WS_THICKFRAME);
	}

	HI_Copy_Name_To_Chars (&dc->options._hoops_IAPIR, _hoops_IAPIR);
	_hoops_IAPIR[79] = '\0';

	_hoops_CSRGR->_hoops_SIGRR.x = dc->_hoops_RHPGA.left
		- _hoops_CSRGR->_hoops_PCGRR;
	_hoops_CSRGR->_hoops_SIGRR.y = _hoops_CSRGR->_hoops_CCGRR -
		dc->_hoops_RHPGA.top - _hoops_CSRGR->_hoops_HCGRR;
	_hoops_CSRGR->_hoops_CIGRR.x = _hoops_CSRGR->_hoops_GCGRR.x = dc->_hoops_RHPGA.right -
		dc->_hoops_RHPGA.left + _hoops_CSRGR->_hoops_ACGRR + _hoops_CSRGR->_hoops_PCGRR;
	_hoops_CSRGR->_hoops_CIGRR.y = _hoops_CSRGR->_hoops_GCGRR.y = dc->_hoops_RHPGA.top -
		dc->_hoops_RHPGA.bottom + _hoops_CSRGR->_hoops_HCGRR + _hoops_CSRGR->_hoops_RCGRR;

	if (BIT(dc->options.flags, _hoops_GIPRP)) {
		_hoops_IGRAH = MonitorFromPoint(_hoops_SGRAH, MONITOR_DEFAULTTOPRIMARY);
		GetMonitorInfo(_hoops_IGRAH, &_hoops_CGRAH);
		_hoops_CSRGR->hWND = 
			CreateWindow ("HoopsWClassOGL2", _hoops_IAPIR, WS_POPUP | WS_VISIBLE,
								_hoops_CGRAH.rcMonitor.left,
								_hoops_CGRAH.rcMonitor.top,
								_hoops_CGRAH.rcMonitor.right - _hoops_CGRAH.rcMonitor.left,
								_hoops_CGRAH.rcMonitor.bottom - _hoops_CGRAH.rcMonitor.top,
								NULL, NULL, _hoops_RCSRH (_hoops_ACSRH), (LPSTR)dc);
	}
	else {
		_hoops_CSRGR->hWND =
			CreateWindow ("HoopsWClassOGL2", _hoops_IAPIR, window_style,
						  dc->_hoops_RHPGA.left - _hoops_CSRGR->_hoops_PCGRR,
						  _hoops_CSRGR->_hoops_CCGRR -
						  dc->_hoops_RHPGA.top - _hoops_CSRGR->_hoops_HCGRR,
						  dc->_hoops_RHPGA.right -
						  dc->_hoops_RHPGA.left +
						  _hoops_CSRGR->_hoops_ACGRR + _hoops_CSRGR->_hoops_PCGRR,
						  dc->_hoops_RHPGA.top -
						  dc->_hoops_RHPGA.bottom +
						  _hoops_CSRGR->_hoops_HCGRR + _hoops_CSRGR->_hoops_RCGRR,
						  null, null, _hoops_RCSRH (_hoops_ACSRH), (LPSTR) dc);
	}

	if (_hoops_CSRGR->hWND == null) {
		HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_CREATE_WINDOW,
				  "Unable to Create a Window");
		HD_Kill_Driver (dc);
		return 0;
	}

	if (!dc->options._hoops_IASSP)
		ShowWindow (_hoops_CSRGR->hWND, SW_SHOWNORMAL);

	UpdateWindow (_hoops_CSRGR->hWND);

	if (dc->options._hoops_HRSSP) {
		HMENU _hoops_GRRAH;

		_hoops_GRRAH = GetSystemMenu (_hoops_CSRGR->hWND, FALSE);
	}

	SetRectEmpty ((RECT *) &_hoops_CSRGR->_hoops_IIGRR);

	return (POINTER_SIZED_INT)(POINTER_SIZED_INT) _hoops_CSRGR->hWND;

} /* _hoops_RSGR _hoops_API '_hoops_ARPR _hoops_GCGS _hoops_RGIPC' */



/*
 * _hoops_SRAC
 */
POINTER_SIZED_INT get_outer_window (Display_Context const * _hoops_SAGRH) 
{
	_hoops_RRPRH *_hoops_IRSRA = _hoops_ARPRH ();
	int temp;
	WNDCLASS window_class;
	Display_Context alter * dc = (Display_Context alter *) _hoops_SAGRH;
	HOGLData alter *_hoops_CSRGR = OGLD (dc);

	_hoops_CAAI (HOOPS_WORLD->_hoops_APHGI);

	/*_hoops_SHR _hoops_IRHH _hoops_IRS _hoops_CSHGR _hoops_IH _hoops_SGH _hoops_GGR _hoops_CRSRR _hoops_PPGRR*/
	if (!_hoops_IRSRA->_hoops_RRACI) {
		window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_GLOBALCLASS;
		window_class.lpfnWndProc = _hoops_ASHPC;
		window_class.cbClsExtra = 0;
		window_class.cbWndExtra = 0;
		window_class.hInstance = _hoops_RCSRH (_hoops_ACSRH);
		if (_hoops_CSRGR->_hoops_PIGRR == _hoops_PPSGR)
			window_class.hIcon = LoadIcon (_hoops_RCSRH (_hoops_HGRAH), "HoopsIcon");
		else
			window_class.hIcon = 0;
		window_class.hCursor = LoadCursor (null, IDC_ARROW);
		window_class.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
		window_class.lpszMenuName = null;
		window_class.lpszClassName = "HoopsWClassOGL2";

		temp = RegisterClass (&window_class);

		if (temp == 0) {
			HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_CREATE_WINDOW, "Unable to Register our class");
			HD_Kill_Driver (dc);
			_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);
			return 0;
		}
		_hoops_IRSRA->_hoops_RRACI = true;
	}

	/* _hoops_RH _hoops_HSPR _hoops_HAPR _hoops_CGH _hoops_GRCI _hoops_SAHR _hoops_ARR _hoops_HCCPR _hoops_SR _hoops_HPPR _hoops_PPR 
		_hoops_PHIS _hoops_IS _hoops_ARPR _hoops_IRS _hoops_CGSRC */
	for (;;) {
		_hoops_CHCGC((Display_Context alter *) dc);
		switch (_hoops_CSRGR->_hoops_PIGRR) {
			case _hoops_IPSGR:
			case DCT_IMAGE:
				_hoops_GGIPC (dc);
			break;

			case _hoops_PPSGR:
				_hoops_AGIPC (dc);
			break;

			case _hoops_HPSGR:
				/* _hoops_ISAP _hoops_IS _hoops_AA */
			break;
		}
		if (_hoops_CSRGR->hDC)
			ReleaseDC (_hoops_CSRGR->hWND, _hoops_CSRGR->hDC);

		_hoops_CSRGR->hDC = GetDC (_hoops_CSRGR->hWND);
		identify_renderer (dc);

		/*_hoops_CCPC _hoops_PGIPC*/
		/*_hoops_RGR _hoops_HRGR _hoops_RH _hoops_HSPP _hoops_IIGR _hoops_RH _hoops_HGASI _hoops_IH _hoops_RH _hoops_HGIPC*/
		/*_hoops_HGPC _hoops_ARPC _hoops_RPP _hoops_SR _hoops_HS _hoops_SGH _hoops_RPPS _hoops_CRSRR _hoops_PPR _hoops_ICCGR */
		/*_hoops_GCAC _hoops_SR _hoops_IRHH _hoops_IRS _hoops_GRH _hoops_RSRA _hoops_SRHR _hoops_GRAA _hoops_ICCI _hoops_AIR _hoops_RPCC*/
		/*_hoops_RH _hoops_IRHH _hoops_IRS _hoops_PSSCI _hoops_PPR _hoops_RSSCI _hoops_SISS _hoops_IS _hoops_SRGS _hoops_IS _hoops_PSCR*/
		/*_hoops_SR _hoops_CRPCI _hoops_RGR _hoops_IS _hoops_RH _hoops_HPHR _hoops_RPPS*/
#if 0
		if (_hoops_CSRGR->_hoops_PIGRR == DCT_IMAGE ||
			(_hoops_CSRGR->_hoops_PIGRR == _hoops_HPSGR &&  
			 _hoops_CSRGR->_hoops_GSGRR &&
			 dc->options._hoops_SRRRR)) {
			RECT rect;
			int w, h;
			
			_hoops_CSRGR->_hoops_APSRC = true;

			/*
			_hoops_IGIPC (_hoops_HGPGA);
			*/

			if (_hoops_CSRGR->_hoops_PIGRR == DCT_IMAGE) {
				w = _hoops_CSRGR->_hoops_IHGRR->width;
				h = _hoops_CSRGR->_hoops_IHGRR->height;
			}
			else {
				GetClientRect(_hoops_CSRGR->hWND, &rect);

				w = rect.right-rect.left;
				h = rect.bottom-rect.top;
				if (w<1) w=1;
				if (h<1) h=1;
			}

			_hoops_CSRGR->hBitmap = _hoops_CGIPC(
					_hoops_CSRGR->hDC,
					_hoops_CSRGR->_hoops_RIGRR,
					w,h);

			_hoops_CSRGR->_hoops_HIISI = CreateCompatibleDC(_hoops_CSRGR->hDC);

			_hoops_CSRGR->old_hBitmap = (HBITMAP)SelectObject(_hoops_CSRGR->_hoops_HIISI, _hoops_CSRGR->hBitmap);			

			_hoops_CSRGR->hGLRC = wglCreateContext (_hoops_CSRGR->_hoops_HIISI);

			if (!_hoops_CSRGR->hGLRC) {
				HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY,
						  "Unable to Set OpenGL Rendering Context");
				HD_Kill_Driver (dc);
				_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);
				return 0;
			}

			if (!wglMakeCurrent (_hoops_CSRGR->_hoops_HIISI, _hoops_CSRGR->hGLRC)) {
				HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY,
						  "Unable to Make Current OpenGL Rendering Context");
				HD_Kill_Driver (dc);
				_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);
				return 0;
			}

			/*_hoops_RGR _hoops_HRGR _hoops_ARP _hoops_GGR _hoops_SGIPC _hoops_IIGR _hoops_RH "_hoops_GSSR" _hoops_AGIR*/
			dc->_hoops_PGCC._hoops_CHHSR = _hoops_ACPGA;
			_hoops_CSRGR->_hoops_SRRRR = false;
		} 
		else
#endif
		{
			/*_hoops_HGAPR _hoops_ISCC _hoops_RCSPR "_hoops_GSHC" _hoops_GRAA _hoops_RSAIP _hoops_CRAA*/
			_hoops_CSRGR->_hoops_APSRC = false;
			wgl_arb_pixel_format(dc);
			_hoops_PRPPC (_hoops_CSRGR);

			_hoops_CSRGR->hGLRC = wglCreateContext (_hoops_CSRGR->hDC);

			if (!_hoops_CSRGR->_hoops_GSGRR &&
				!BIT (dc->options._hoops_IRARR, _hoops_HCARC)) {
				HOGLData const *_hoops_CAHPC;

				if (_hoops_IRSRA->_hoops_PRACI == null) {
					_hoops_IRSRA->_hoops_PRACI = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_SIGCI)(HOOPS_WORLD->memory_pool);
				}
				else {
					_hoops_CAHPC = _hoops_IRSRA->_hoops_PRACI->PeekFirst();
					wglShareLists (_hoops_CAHPC->hGLRC, _hoops_CSRGR->hGLRC);
				}
				_hoops_IRSRA->_hoops_PRACI->AddFirst(_hoops_CSRGR);
			}	

			if (!_hoops_CSRGR->hGLRC) {
				HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY,
						  "Unable to Set OpenGL Rendering Context");
				HD_Kill_Driver (dc);
				_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);
				return 0;
			}

			if (!wglMakeCurrent (_hoops_CSRGR->hDC, _hoops_CSRGR->hGLRC)) {
				HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY,
						  "Unable to Make Current OpenGL Rendering Context");
				HD_Kill_Driver (dc);
				_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);
				return 0;
			}

			_hoops_HP(_hoops_CSRGR->glewcontext);
			_hoops_HP(_hoops_CSRGR->wglewcontext);
			_hoops_CSRGR->glewcontext = new GLEWContext();
			_hoops_CSRGR->wglewcontext = new WGLEWContext();
			if (glewInit() != GLEW_OK || wglewInit() != GLEW_OK) {
				HE_ERROR (HEC_OPENGL_DRIVER, HEC_OPENGL_DRIVER,
					"Unable to initialize GLEW");
				HD_Kill_Driver (dc);
				_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);
				return 0;
			}
		}
		break;
	}

	GetClientRect (_hoops_CSRGR->hWND, (RECT *) &_hoops_CSRGR->_hoops_IIGRR);
	_hoops_PICGC((Display_Context alter *) dc);
	ZERO_STRUCT (&_hoops_CSRGR->_hoops_IIGRR, RECT);
	//_hoops_HHCRH (_hoops_CSPH);

	_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);

	return (POINTER_SIZED_INT)(POINTER_SIZED_INT) _hoops_CSRGR->hWND;
} /* _hoops_RSGR _hoops_API '_hoops_HGCR _hoops_CRIPR _hoops_RPPS' */


/*
 * _hoops_SRAC
 */
void free_outer_window (Display_Context const * dc) {
	HOGLData alter *_hoops_CSRGR = OGLD (dc);

	if (_hoops_CSRGR == null) 
		return;

	_hoops_CAAI (HOOPS_WORLD->_hoops_APHGI);

	wglMakeCurrent(_hoops_CSRGR->hDC, _hoops_CSRGR->hGLRC);

	/* _hoops_CASI _hoops_GH _hoops_SRCIA _hoops_CIPH*/
	_hoops_ACIRH((Display_Context *)dc);
	_hoops_CSRGR->_hoops_PP();

	_hoops_SPSGC(dc);

	unset_ogl (dc);

	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_PPSGR || 
		_hoops_CSRGR->_hoops_PIGRR == DCT_IMAGE|| 
		_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR) {
		DestroyWindow (_hoops_CSRGR->hWND);
		_hoops_CSRGR->hWND = null;
	}	

	_hoops_APAI (HOOPS_WORLD->_hoops_APHGI);
}


/*
 * _hoops_SRAC
 */
void _hoops_ASCSP (
	Display_Context const	*dc) 
{
	HOGLData alter *_hoops_CSRGR = OGLD (dc);

	SetWindowText (_hoops_CSRGR->hWND, dc->options._hoops_IAPIR.text);
}


/*
 * _hoops_SRAC
 */
void _hoops_RSCSP (Display_Context const * dc) {
	HOGLData alter *_hoops_CSRGR = OGLD (dc);

	_hoops_CSRGR->_hoops_HCAC = _hoops_CCC;
	_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
	_hoops_CSRGR->_hoops_IARRR = _hoops_CCC;
	_hoops_CSRGR->_hoops_ICAC = _hoops_CCC;

	if ((_hoops_CSRGR->_hoops_PIGRR == _hoops_PPSGR ||
		 _hoops_CSRGR->_hoops_PIGRR == _hoops_HPSGR) &&
		IsWindow (_hoops_CSRGR->hWND) &&
		(IsIconic (_hoops_CSRGR->hWND) || IsZoomed (_hoops_CSRGR->hWND))) {
		/* _hoops_CGP _hoops_RH _hoops_RPPS _hoops_HRGR _hoops_PRRAH _hoops_SR _hoops_SSPC _hoops_HCR _hoops_PCCS _hoops_SSHRH */
		return;
	}

	_hoops_CSRGR->_hoops_SIGRR.x = dc->_hoops_RHPGA.left - _hoops_CSRGR->_hoops_PCGRR;
	_hoops_CSRGR->_hoops_SIGRR.y = _hoops_CSRGR->_hoops_CCGRR -
		dc->_hoops_RHPGA.top - _hoops_CSRGR->_hoops_HCGRR;
	_hoops_CSRGR->_hoops_CIGRR.x = dc->_hoops_RHPGA.right -
		dc->_hoops_RHPGA.left + _hoops_CSRGR->_hoops_ACGRR + _hoops_CSRGR->_hoops_PCGRR;
	_hoops_CSRGR->_hoops_CIGRR.y = dc->_hoops_RHPGA.top -
		dc->_hoops_RHPGA.bottom + _hoops_CSRGR->_hoops_HCGRR +
		_hoops_CSRGR->_hoops_RCGRR;

	MoveWindow (_hoops_CSRGR->hWND,
				dc->_hoops_RHPGA.left - _hoops_CSRGR->_hoops_PCGRR,
				_hoops_CSRGR->_hoops_CCGRR -
				dc->_hoops_RHPGA.top - _hoops_CSRGR->_hoops_HCGRR,
				dc->_hoops_RHPGA.right - dc->_hoops_RHPGA.left +
				_hoops_CSRGR->_hoops_ACGRR + _hoops_CSRGR->_hoops_PCGRR,
				dc->_hoops_RHPGA.top - dc->_hoops_RHPGA.bottom +
				_hoops_CSRGR->_hoops_HCGRR + _hoops_CSRGR->_hoops_RCGRR, true);
}

/*****************************************************************************
 *****************************************************************************
						_hoops_HGGSP _hoops_SIIRH'_hoops_GRI _hoops_PPR _hoops_HICRR _hoops_SICAR
 *****************************************************************************
 *****************************************************************************/

/*
 * _hoops_PGAA
 */
local void
_hoops_SGCRH (HOGLData alter * _hoops_CSRGR,
			 HWND _hoops_GRCRH,
			 bool _hoops_RRCRH,
			 bool _hoops_ARCRH) {
	PAINTSTRUCT ps;
	HDC hDC;
	RECT _hoops_PRCRH;
	int _hoops_HHCAP = 0;			/* _hoops_GRIPC _hoops_RRAI _hoops_IS _hoops_PAAP _hoops_ARRGR */

	/* _hoops_SCHPC _hoops_PCR _hoops_CCA _hoops_PSHR _hoops_API _hoops_GGR _hoops_HRCRH _hoops_SCHGR */

	if (_hoops_CSRGR->pending_resize) {
		_hoops_CSRGR->pending_resize = false;
		if (!IsIconic (_hoops_GRCRH)
			&& (_hoops_RRCRH || IsWindowVisible (_hoops_GRCRH))) {
			GetClientRect (_hoops_CSRGR->hWND, (RECT *) &_hoops_CSRGR->_hoops_IIGRR);
			HD_Force_Refresh (_hoops_CSRGR->dc);
		}
	}

	hDC = BeginPaint (_hoops_CSRGR->hWND, (LPPAINTSTRUCT) & ps);
	EndPaint (_hoops_CSRGR->hWND, &ps);

	CopyRect (&_hoops_PRCRH, &ps.rcPaint);

	if (ps.rcPaint.bottom + ps.rcPaint.top + ps.rcPaint.right +
		ps.rcPaint.left == 0)
		;/*_hoops_RRIPC (_hoops_HGPGA->_hoops_CSPH);*/
	else {
		RECT rect;

		GetClientRect (_hoops_CSRGR->hWND, &rect);

		HD_Force_Partial_Refresh (_hoops_CSRGR->dc,
								  ps.rcPaint.left - _hoops_HHCAP,
								  ps.rcPaint.right - 1 + _hoops_HHCAP,
								  rect.bottom - 1 - ps.rcPaint.bottom - _hoops_HHCAP,
								  rect.bottom - 1 - ps.rcPaint.top + _hoops_HHCAP);
	}

	/* _hoops_IPCP _hoops_SHIR _hoops_ACPH _hoops_IH _hoops_RGR _hoops_HRGR _hoops_PCSH/_hoops_HCSH _hoops_GGGSI */
	if (_hoops_ARCRH)
		InvalidateRect (_hoops_CSRGR->hWND, (LPRECT) & ps.rcPaint, 0);
}



/* _hoops_GRAA-_hoops_SGH _hoops_RPPS _hoops_RCC _hoops_RPPS _hoops_AACRH */
local LRESULT APIENTRY
_hoops_ASHPC (HWND _hoops_GRCRH,
				 UINT message, 
				 WPARAM wParam, 
				 LPARAM lParam) {
	Display_Context alter *dc;

	if ((dc = HD_Find_DC_From_WID ((POINTER_SIZED_INT) _hoops_GRCRH)) != null) {
		HOGLData alter *_hoops_CSRGR;

		_hoops_CSRGR = OGLD (dc);

		switch (message) {
			case WM_CLOSE: {
				/*
				 * _hoops_HPIRA _hoops_RPISR _hoops_GRS _hoops_ISPR _hoops_RGR _hoops_RIP _hoops_PPR
				 * _hoops_PCHIA _hoops_RHPP - _hoops_ISCCP _hoops_SCH _hoops_ARI _hoops_CHH _hoops_HS _hoops_RPII _hoops_HACRH _hoops_IACRH
				 */
				char event_string[255];

				if (dc->options._hoops_GASSP && !dc->options._hoops_IRSSP) {
						
					HI_Queue_Special_Event (dc->_hoops_RIGC,"OpenGL:DeleteWindow",
						HI_Build_Special_Event_String(event_string, "OPENGL", dc->_hoops_AAHSR,
							(POINTER_SIZED_INT) _hoops_CSRGR->hWND, -1));
				}

				HI_Queue_Actor_Shutdown(dc->_hoops_GHRI, false);
			
			}	break;

			case WM_KEYDOWN: {
				consume_key (_hoops_CSRGR, wParam, lParam);
			}	break;

			case WM_MOUSEMOVE:
			case WM_RBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_LBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_MBUTTONUP:
			case WM_LBUTTONUP: {
				consume_mouse (_hoops_CSRGR, message, wParam, lParam);
			}	break;

			case WM_ERASEBKGND: {
				return true;
			}	_hoops_HHHI;

			case WM_WINDOWPOSCHANGING: {
				LPWINDOWPOS _hoops_CACRH;
				char _hoops_SACRH = false;

				_hoops_CACRH = (LPWINDOWPOS) lParam;
				if (IsIconic (_hoops_GRCRH) || IsZoomed (_hoops_GRCRH))
					break;

				if (dc->options._hoops_RASSP) {
					if (_hoops_CACRH->cx > 0 &&
						_hoops_CSRGR->_hoops_CIGRR.x == _hoops_CACRH->cx &&
						_hoops_CSRGR->_hoops_CIGRR.y == _hoops_CACRH->cy) {
						/*
						 * _hoops_ICIA _hoops_IHGC _hoops_IIGR _hoops_GPCRH _hoops_CGAPR _hoops_IH _hoops_SSRR _hoops_SGH
						 * _hoops_HPP _hoops_GAPGH-_hoops_GGRRR
						 */
						_hoops_CSRGR->_hoops_SIGRR.x = _hoops_CACRH->x;
						_hoops_CSRGR->_hoops_SIGRR.y = _hoops_CACRH->y;
						_hoops_SACRH = true;
					}
				}
				else {
					if (_hoops_CSRGR->_hoops_CIGRR.x == _hoops_CACRH->cx &&
						_hoops_CSRGR->_hoops_CIGRR.y == _hoops_CACRH->cy) {
						/* _hoops_RPCRH */
						_hoops_CACRH->flags |= (SWP_NOMOVE | SWP_NOREPOSITION);
						_hoops_SACRH = true;
					}
				}

				if (!dc->options._hoops_PASSP && 
					_hoops_CACRH->cx > 0 &&
					(_hoops_CSRGR->_hoops_CIGRR.x != _hoops_CACRH->cx ||
					 _hoops_CSRGR->_hoops_CIGRR.y != _hoops_CACRH->cy)) {
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
 
					cx = _hoops_HPCRH - _hoops_CSRGR->_hoops_CIGRR.x;
					cy = _hoops_PPCRH - _hoops_CSRGR->_hoops_CIGRR.y;

					if (Abs(cx) > Abs(cy)) {
						if (Abs(cy) == 0.0f) {
							_hoops_PPCRH = (int)((float) _hoops_HPCRH *
								(float)_hoops_CSRGR->_hoops_GCGRR.y /
								(float)_hoops_CSRGR->_hoops_GCGRR.x);

							if (_hoops_CPCRH != _hoops_CSRGR->_hoops_SIGRR.y)
								_hoops_CPCRH += (_hoops_CACRH->cy - _hoops_PPCRH);
						}
						else {
							_hoops_HPCRH = (int)((float) _hoops_PPCRH *
								(float)_hoops_CSRGR->_hoops_GCGRR.x /
								(float)_hoops_CSRGR->_hoops_GCGRR.y);

							if (_hoops_IPCRH != _hoops_CSRGR->_hoops_SIGRR.x)
								_hoops_IPCRH += (_hoops_CACRH->cx - _hoops_HPCRH);
						}
					}
					else {
						if (Abs(cx) == 0.0f) {
							_hoops_HPCRH = (int)((float) _hoops_PPCRH *
								(float)_hoops_CSRGR->_hoops_GCGRR.x /
								(float)_hoops_CSRGR->_hoops_GCGRR.y);

							if (_hoops_IPCRH != _hoops_CSRGR->_hoops_SIGRR.x)
								_hoops_IPCRH += (_hoops_CACRH->cx - _hoops_HPCRH);
						}
						else {
							_hoops_PPCRH = (int)((float) _hoops_HPCRH *
								(float)_hoops_CSRGR->_hoops_GCGRR.y /
								(float)_hoops_CSRGR->_hoops_GCGRR.x);

							if (_hoops_CPCRH != _hoops_CSRGR->_hoops_SIGRR.y)
								_hoops_CPCRH += (_hoops_CACRH->cy - _hoops_PPCRH);
						}
					}

					_hoops_CSRGR->_hoops_CIGRR.x = _hoops_HPCRH;
					_hoops_CSRGR->_hoops_CIGRR.y = _hoops_PPCRH;

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

			case WM_PALETTECHANGED: {
				if (_hoops_CSRGR->_hoops_RIGRR) {
					/*	_hoops_CGP _hoops_RGR _hoops_CCRPR _hoops_SSAS _hoops_HAR _hoops_AGRP _hoops_RH _hoops_IHCRH, _hoops_HAIHR
					   _hoops_PPR _hoops_CHCRH _hoops_RGR _hoops_CCRPR'_hoops_GRI _hoops_IHCRH  */

					if (wParam != (WPARAM) _hoops_GRCRH) {
						/* _hoops_ISGP _hoops_PPR _hoops_CHCRH _hoops_ISCP _hoops_IHCRH */

						_hoops_CSRGR->_hoops_AIGRR =
							SelectPalette (_hoops_CSRGR->hDC,
										   _hoops_CSRGR->_hoops_RIGRR, false);
						RealizePalette (_hoops_CSRGR->hDC);

						/*
						 * _hoops_PAAS _hoops_RIGRP _hoops_RH _hoops_PSHA _hoops_IH _hoops_PCCP _hoops_IPCR _hoops_RPPS,
						 * _hoops_SHCRH _hoops_PAH _hoops_SHH _hoops_PIGS _hoops_PGGA _hoops_SCH _hoops_HRGR _hoops_SPAC _hoops_HSAR
						 * _hoops_IGSIP _hoops_RH _hoops_RPRGR _hoops_CCAC (_hoops_PRGI _hoops_PHRI _hoops_RH _hoops_ACPP _hoops_CHR
						 * _hoops_HAR _hoops_GAR _hoops_RIRA)
						 */

						UpdateColors (_hoops_CSRGR->hDC);

						/* _hoops_SP _hoops_GH */

						if (_hoops_CSRGR->_hoops_AIGRR)
							SelectPalette (_hoops_CSRGR->hDC,
										   _hoops_CSRGR->_hoops_AIGRR, false);
					}
				}
			}	break;

			case WM_QUERYNEWPALETTE: {
				if (_hoops_CSRGR->_hoops_RIGRR) {
					/* _hoops_ISGP _hoops_PPR _hoops_CHCRH _hoops_RH _hoops_IHCRH */

					_hoops_CSRGR->_hoops_AIGRR =
						SelectPalette (_hoops_CSRGR->hDC, _hoops_CSRGR->_hoops_RIGRR,
									   FALSE);
					RealizePalette (_hoops_CSRGR->hDC);

					/* _hoops_HRHIP _hoops_RH _hoops_RPRGR _hoops_CCAC */

					InvalidateRect (_hoops_GRCRH, null, true);
					UpdateWindow (_hoops_GRCRH);

					if (_hoops_CSRGR->_hoops_AIGRR)
						SelectPalette (_hoops_CSRGR->hDC, _hoops_CSRGR->_hoops_AIGRR,
									   false);

					return true;
				}

				return FALSE;
			}	_hoops_HHHI;

			case WM_PAINT: {
				if (!_hoops_CSRGR->pending_resize)
					_hoops_SGCRH (_hoops_CSRGR, _hoops_GRCRH, true, false);
			}	break;
		}
	}

	return DefWindowProc (_hoops_GRCRH, message, wParam, lParam);
}



/*
 * _hoops_PGAA
 * _hoops_GICRH _hoops_HGGSP _hoops_SIIRH: _hoops_RICRH _hoops_IRS _hoops_CIAGR _hoops_PGCPR _hoops_SSHRH
 */
local LRESULT APIENTRY
_hoops_AICRH (HWND _hoops_GRCRH,
					  UINT message, 
					  WPARAM wParam, 
					  LPARAM lParam) 
{
	Display_Context *dc;
	LONG result;

	result = 0L;

	if ((dc = HD_Find_DC_From_WID ((POINTER_SIZED_INT) _hoops_GRCRH)) != null) {
		HOGLData alter *_hoops_CSRGR;

		_hoops_CSRGR = OGLD (dc);

		switch (message) {
			case WM_ERASEBKGND: {
				/*
				 * _hoops_ASSI _hoops_SPHGR _hoops_IGHP _hoops_SCAC
				 * _hoops_AGAH _hoops_GRS _hoops_RGHH _hoops_SCH
				 */
				return 1L;
			}	_hoops_HHHI;

			case WM_SIZE: {
				_hoops_CSRGR->pending_resize = true;
			}	break;

			case WM_PAINT: {
				_hoops_SGCRH (_hoops_CSRGR, _hoops_GRCRH, false, true);
			}	break;

			case WM_PALETTECHANGED: {
#ifndef _hoops_GPISI
				if (_hoops_CSRGR->_hoops_RIGRR) {
					/*
					 * _hoops_CGP _hoops_RGR _hoops_CCRPR _hoops_SSAS _hoops_HAR _hoops_AGRP _hoops_RH _hoops_IHCRH, _hoops_HAIHR
					 * _hoops_PPR _hoops_CHCRH _hoops_RGR _hoops_CCRPR'_hoops_GRI _hoops_IHCRH
					 */

					if (wParam != (WPARAM) _hoops_GRCRH) {
						/* _hoops_ISGP _hoops_PPR _hoops_CHCRH _hoops_ISCP _hoops_IHCRH */

						_hoops_CSRGR->_hoops_AIGRR =
							SelectPalette (_hoops_CSRGR->hDC,
										   _hoops_CSRGR->_hoops_RIGRR, false);
						RealizePalette (_hoops_CSRGR->hDC);

						UpdateColors (_hoops_CSRGR->hDC);

						/* _hoops_SP _hoops_GH */

						if (_hoops_CSRGR->_hoops_AIGRR)
							SelectPalette (_hoops_CSRGR->hDC,
										   _hoops_CSRGR->_hoops_AIGRR, false);
					}
				}
#endif
			}	break;

			case WM_QUERYNEWPALETTE: {
#ifndef _hoops_GPISI
				if (_hoops_CSRGR->_hoops_RIGRR) {
					_hoops_CSRGR->_hoops_AIGRR =
						SelectPalette (_hoops_CSRGR->hDC, _hoops_CSRGR->_hoops_RIGRR,
									   FALSE);
					RealizePalette (_hoops_CSRGR->hDC);

					/* _hoops_HRHIP _hoops_RH _hoops_RPRGR _hoops_CCAC */

					InvalidateRect (_hoops_GRCRH, null, true);
					UpdateWindow (_hoops_GRCRH);

					if (_hoops_CSRGR->_hoops_AIGRR)
						SelectPalette (_hoops_CSRGR->hDC, _hoops_CSRGR->_hoops_AIGRR,
									   false);

					return 1L;
				}
#endif
			}	break;

			default:	break;
		}

		if (result == 0L) {
			result = CallWindowProc (_hoops_CSRGR->_hoops_GIGRR,
									 _hoops_GRCRH, message, wParam, lParam);
		}

	}
	else {
		result = DefWindowProc (_hoops_GRCRH, message, wParam, lParam);
	}

	return result;
}






void _hoops_RSCSR (_hoops_APARR alter & _hoops_RRCI) {
	_hoops_GHCAC (_hoops_RRCI);

	/*_hoops_HRRPI _hoops_HRCSR _hoops_PRCA */
	_hoops_RRCI->measure_char = measure_char;
	/*_hoops_HPGR->_hoops_IHRPI = _hoops_IHRPI;*/
	_hoops_RRCI->_hoops_AACSR = _hoops_AACSR;
	_hoops_RRCI->_hoops_CACSR = _hoops_CACSR;
	_hoops_RRCI->find_all_fonts = find_all_fonts;
	_hoops_RRCI->load_font = load_font;
	_hoops_RRCI->unload_font = unload_font;
	_hoops_RRCI->_hoops_CSCSP = _hoops_CSCSP;
	_hoops_RRCI->_hoops_RGSSP = _hoops_RGSSP;
	_hoops_RRCI->_hoops_GGSSP = _hoops_GGSSP;	

}



/*
 * _hoops_IAAAH _hoops_PPICR
 */
extern "C" bool HC_CDECL HD_Win32_OpenGL2_Driver (
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
#endif /* _hoops_ARIPC */

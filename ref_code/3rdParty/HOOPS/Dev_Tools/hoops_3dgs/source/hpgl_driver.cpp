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
 * $Id: obf_tmp.txt 1.189 2010-08-03 23:51:11 jason Exp $
 */

#include "hoops.h"
#include "hd_proto.h"

#ifndef HPGL_DRIVER
extern "C"  bool HC_CDECL HD_HPGL_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (request_info);
	return HD_No_Driver (_hoops_RIGC, _hoops_GHRI, request, "hpgl");
}

#else

#include "database.h"
#include "driver.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "patterns.h"
#include "searchh.h"
#include "hversion.h"

#include <stdio.h>


/*
 * _hoops_HISRA _hoops_RHPP _hoops_HCSP _hoops_SIH
 */
#define _hoops_SPPAI				2
#define _hoops_GHPAI				4
#define _hoops_RHPAI		8		/* _hoops_RAIA _hoops_GGI _hoops_PISH _hoops_HAH */
#define _hoops_AHPAI				16
#define _hoops_PHPAI			32
#define _hoops_HHPAI				64


/*
 * _hoops_CPHSR _hoops_CSIIR
 */
#define _hoops_CHCRI		1024
#define _hoops_SHCRI		1024
#define _hoops_IHPAI		80


/*
 * _hoops_HSSP _hoops_CAPRR _hoops_IH _hoops_HSSP _hoops_ASCA
 */
#define _hoops_CHPAI			0
#define _hoops_SHPAI		1
#define _hoops_GIPAI				2


/*
 * _hoops_CSGSR _hoops_PRCA
 */
#define _hoops_RIPAI				256
#define _hoops_AIPAI			80.0


/*
 * _hoops_ASCA _hoops_PHSRI
 */
#define _hoops_PIPAI(str,xx,yy,state) {\
	long	_hoops_HIPAI;\
	char	_hoops_IIPAI[64], _hoops_CIPAI[64];\
	_hoops_HIPAI = (long)(xx) + (state)->_hoops_SIPAI.x;\
	Sprintf_LD (_hoops_IIPAI, "PU;PA%D,", _hoops_HIPAI);\
	_hoops_HIPAI = (long)(yy) + (state)->_hoops_SIPAI.y;\
	Sprintf_LD (_hoops_CIPAI, "%D;", _hoops_HIPAI);\
	Sprintf_SS ((str), "%s%s", _hoops_IIPAI, _hoops_CIPAI);\
	_hoops_SHSRI ((state), (str));\
}

#define _hoops_GCPAI(str,xx,yy,state) {\
	long	_hoops_RCPAI;\
	char	_hoops_ACPAI[64], _hoops_PCPAI[64];\
	_hoops_RCPAI = (long)(xx) + (state)->_hoops_SIPAI.x;\
	Sprintf_LD (_hoops_ACPAI, "PD;PA%D,", _hoops_RCPAI);\
	_hoops_RCPAI = (long)(yy) + (state)->_hoops_SIPAI.y;\
	Sprintf_LD (_hoops_PCPAI, "%D;", _hoops_RCPAI);\
	Sprintf_SS ((str), "%s%s", _hoops_ACPAI, _hoops_PCPAI);\
	_hoops_SHSRI ((state), (str));\
}




/*
 * _hoops_PIAP _hoops_PIH _hoops_SGS _hoops_RHGSR _hoops_HCPH _hoops_IS _hoops_RH _hoops_SRAC _hoops_SICAR
 */
struct _hoops_HCPAI {
	/* _hoops_RGHR _hoops_HAS/_hoops_GCSR */
	FILE						*_hoops_PSCRI;
	int							_hoops_ICPAI;
	bool					_hoops_CCPAI,
								_hoops_SCPAI;
	int							_hoops_GSPAI;
	bool					_hoops_RSPAI;

	/* _hoops_ASCA _hoops_IRGAA _hoops_PRCA */
	bool					_hoops_ASPAI,
								_hoops_PSPAI,
								_hoops_HSPAI;
	struct {long x, y;}			_hoops_ISPAI,
								_hoops_SIPAI,
								_hoops_CSPAI;
	float						_hoops_SSPAI;

	/* _hoops_IGRI _hoops_PRCA */
	_hoops_GARRR				_hoops_GGHAI,
								_hoops_RGHAI;
	int							_hoops_AGHAI[_hoops_RIPAI+1];
	int							_hoops_PGHAI;
	int							_hoops_HGHAI,
								_hoops_GASRI;
};


/*
 * _hoops_PHSRI _hoops_IS _hoops_ARP _hoops_GH _hoops_PIAP _hoops_CICRR
 */
#define _hoops_HHSRI(dc)		((_hoops_HCPAI alter *)(dc)->data)
#define _hoops_IHSRI(nr)		((_hoops_HCPAI alter *)(nr)->_hoops_SRA->data)


/*
 * _hoops_PGAA
 */
local void _hoops_SHSRI (
	_hoops_HCPAI alter		*state,
	char const				*data) {
	int						len;

	len = (int) _hoops_SSGR (data);

	/* _hoops_GGCR _hoops_IRS _hoops_CCAH _hoops_III _hoops_RPP _hoops_RH _hoops_III _hoops_SAGGR _hoops_HAH _hoops_RGRRR */
	if ((state->_hoops_GSPAI + len) > _hoops_IHPAI) {
		if ((fputs ("\n", state->_hoops_PSCRI) == -1))
			HE_ERROR (HEC_HPGL_DRIVER, HES_WRITE_FAILED,
					  "Can't write new line to file");
		state->_hoops_GSPAI = 0;
	}

	/* _hoops_GGI _hoops_RH _hoops_RIHRR _hoops_PIH */
	if ((fputs (data, state->_hoops_PSCRI) == -1))
		HE_ERROR (HEC_HPGL_DRIVER, HES_WRITE_FAILED,
				  "Can't write data to file");

	state->_hoops_GSPAI += len;
}


/*
 * _hoops_PGAA
 */
local void _hoops_IGHAI (
	_hoops_HCPAI alter		*state) {

	if (fflush (state->_hoops_PSCRI))
		HE_ERROR (HEC_HPGL_DRIVER, HES_CANNOT_FLUSH_WRITE_BUFFER,
				  "Can't flush write buffer");
}


/*
 * _hoops_PGAA
 */
local _hoops_GARSR _hoops_CGHAI (
	_hoops_HCPAI alter		*state,
	unsigned int			r,
	unsigned int			g,
	unsigned int			b) {
	int						pen;

	/*
	 * _hoops_ARI _hoops_HRGR _hoops_CAS _hoops_SR _hoops_ARCR _hoops_HII _hoops_HGGPA _hoops_IS _hoops_IRS _hoops_CSGSR:
	 *	8 _hoops_CISRI
	 *	_hoops_CSGSR # - _hoops_HAIR	_hoops_PCCIR, _hoops_ISHI, _hoops_RCSR _hoops_PIRA
	 *	1 - _hoops_APRP		0, 0, 0
	 *	2 - _hoops_HRRRA		0, 0, 1
	 *	3 - _hoops_ASSAA		0, 1, 0
	 *	4 - _hoops_SGHAI		0, 1, 1
	 *	5 - _hoops_PRRRA			1, 0, 0
	 *	6 - _hoops_ISSAA		1, 0, 1
	 *	7 - _hoops_RGGAI		1, 1, 0
	 *	8 - _hoops_GRHAI
	 */
	pen = (r * 4) + (g * 2) + (b * 1) + 1;
	if (pen == 8)
		pen = 1;

	/*
	 * _hoops_ARI _hoops_HRGR _hoops_CAS _hoops_SR _hoops_AHAA _hoops_HII _hoops_HGGPA _hoops_IS _hoops_IRS _hoops_RRHAI _hoops_CSGSR:
	 *	8 _hoops_CISRI
	 *	_hoops_CSGSR # - _hoops_HAIR
	 *	0 - _hoops_PGS
	 *	1 - _hoops_APRP
	 *	2 - _hoops_PRRRA
	 *	3 - _hoops_ASSAA
	 *	4 - _hoops_RGGAI
	 *	5 - _hoops_HRRRA
	 *	6 - _hoops_ISSAA
	 *	7 - _hoops_SGHAI
	 */
	if (state->_hoops_CCPAI)
		/* _hoops_SICR _hoops_GGSRA _hoops_CISRI _hoops_IS _hoops_RRHAI _hoops_CISRI _hoops_IS _hoops_PSSP _hoops_HIGR _hoops_ARRS */
		switch (pen) {
			case 1:
			case 3:
			case 6: {
				/* _hoops_GGSRA _hoops_APRP _hoops_SPASR _hoops_RRHAI _hoops_APRP */
				/* _hoops_GGSRA _hoops_ASSAA _hoops_SPASR _hoops_RRHAI _hoops_ASSAA */
				/* _hoops_GGSRA _hoops_ISSAA _hoops_SPASR _hoops_RRHAI _hoops_ISSAA */
			}	break;

			case 2: {
				/* _hoops_CICA _hoops_GGSRA _hoops_HRRRA _hoops_IS _hoops_RRHAI _hoops_HRRRA */
				pen = 5;
			}	break;

			case 4: {
				/* _hoops_CICA _hoops_GGSRA _hoops_SGHAI _hoops_IS _hoops_RRHAI _hoops_SGHAI */
				pen = 7;
			}	break;

			case 5: {
				/* _hoops_CICA _hoops_GGSRA _hoops_PRRRA _hoops_IS _hoops_RRHAI _hoops_PRRRA */
				pen = 2;
			}	break;

			case 7: {
				/* _hoops_CICA _hoops_GGSRA _hoops_RGGAI _hoops_IS _hoops_RRHAI _hoops_RGGAI */
				pen = 4;
			}	break;

			case 8: {
				/* _hoops_CICA _hoops_GGSRA _hoops_GRHAI _hoops_IS _hoops_RRHAI _hoops_PGS */
				pen = 0;
			}	break;

			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								   "incorrect pen calculation in HPGL");
			}	break;
		}

	return pen;
}


/*
 * _hoops_PGAA
 */
local void _hoops_ARHAI (
	_hoops_HCPAI alter		*state,
	_hoops_GARSR			index) {
	char					string[64];
	int						pen;

	/* _hoops_ARCR _hoops_AGAH _hoops_HAIR _hoops_IS _hoops_IGGAI _hoops_RPIHR _hoops_CSGSR _hoops_PHI */
	pen = state->_hoops_AGHAI[index];

	/*
	 * _hoops_SRCH _hoops_PRHAI _hoops_IRS _hoops_CSGSR _hoops_RPP _hoops_HAIR _hoops_AIAH _hoops_PACIA
	 * (_hoops_RGR _hoops_ICHHR _hoops_RH _hoops_RGHR _hoops_HRHC)
	 */
	if (pen != state->_hoops_HGHAI) {
		/* _hoops_HIS _hoops_RH _hoops_RHGS _hoops_CSGSR _hoops_ASSP'_hoops_RA _hoops_SHSP _hoops_IRS _hoops_PSCHR */
		_hoops_SHSRI (state, "PU;");

		Sprintf_D (string, "SP%d;", pen);
		_hoops_SHSRI (state, string);
		state->_hoops_HGHAI = pen;

		/* _hoops_HIS _hoops_RH _hoops_CCAH _hoops_CSGSR _hoops_ASSP'_hoops_RA _hoops_SHSP _hoops_IRS _hoops_PSCHR */
		if (pen > 0)
			_hoops_SHSRI (state, "PU;");
	}
}


/*
 * _hoops_PGAA
 */
local void _hoops_HRHAI (
	Display_Context const		*dc) {
	_hoops_HCPAI alter				*state = _hoops_HHSRI (dc);
	char							string[16];

	/*
	 * _hoops_HRGAI _hoops_IRHAI _hoops_CCGGR _hoops_RPP _hoops_CSGSR _hoops_ACHPR _hoops_RHPC _hoops_HRGR 0,
	 * _hoops_HIS _hoops_IRHH _hoops_SCH _hoops_GRAA-_hoops_AHHR.
	 */
	if (dc->options._hoops_GSHSR == 0.0f)
		((Display_Context alter *)dc)->options._hoops_GSHSR = 1.0f;

	/*
	 * _hoops_PHCH _hoops_AGAH 0 _hoops_IS 1 _hoops_IS _hoops_SISS 0 _hoops_IS _hoops_CRHAI
	 */
	Sprintf_D (string, "VS%d;",
			   (int)((dc->options._hoops_GSHSR) * _hoops_AIPAI));
	_hoops_SHSRI (state, string);
	state->_hoops_SSPAI = dc->options._hoops_GSHSR;
}


/*
 * _hoops_PGAA
 */
local void _hoops_AIPSR (
	int						pattern,
	_hoops_HCPAI alter		*state) {

	switch (pattern) {
		case LP_SOLID: {
			if (state->_hoops_PGHAI != LP_SOLID) {
				_hoops_SHSRI (state, "LT;");
				state->_hoops_PGHAI = LP_SOLID;
			}
		}	break;

#if 0
		case LP_DASHDOT: {
			if (state->_hoops_PGHAI != 5) {
				_hoops_SHSRI (state, "LT5,3;");
				state->_hoops_PGHAI = 5;
			}
		}	break;

		case LP_DASHED: {
			if (state->_hoops_PGHAI != 2) {
				_hoops_SHSRI (state, "LT2,1;");
				state->_hoops_PGHAI = 2;
			}
		}	break;

		case LP_DOTTED: {
			if (state->_hoops_PGHAI != 1) {
				_hoops_SHSRI (state, "LT1,1;");
				state->_hoops_PGHAI = 1;
			}
		}	break;
#endif

	/* _hoops_AGCR _hoops_III _hoops_CSSC _hoops_AAPR _hoops_AGIA _hoops_IS _hoops_HS _hoops_RPII _hoops_HCSRR,
		 * _hoops_HIS _hoops_SR _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_ARI*/

		case LP_DASHDOT:
		case LP_DASHED:
		case LP_DOTTED:

		case LP_LONG_DASH:
		case LP_DASH_2DOT:
		case LP_DASH_3DOT:
		case LP_CENTER:
		case LP_PHANTOM:
		case LP_FINEDOT: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "unexpected line type");
			if (state->_hoops_PGHAI != LP_SOLID) {
				_hoops_SHSRI (state, "LT;");
				state->_hoops_PGHAI = LP_SOLID;
			}
		}	break;

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
							   "invalid line type");
			if (state->_hoops_PGHAI != LP_SOLID) {
				_hoops_SHSRI (state, "LT;");
				state->_hoops_PGHAI = LP_SOLID;
			}
		}	break;
	}
}


/*
 * _hoops_PGAA
 */
local void _hoops_AHPSR (
	Net_Rendition const & nr,
	int						pattern,
	_hoops_HCPAI alter		*state) {
	int						_hoops_HSPSH;
	char					string[64];

	/*
	 * _hoops_PHGAI _hoops_HSGP _hoops_HRGR _hoops_HAR _hoops_GPCPR _hoops_PII _hoops_PCPA _hoops_RH _hoops_IRISR _hoops_HHGAI
	 * _hoops_CPPHR, _hoops_HIH _hoops_HRGR _hoops_HHASH _hoops_HII _hoops_HCR _hoops_HIASR.
	 */

	/* _hoops_GRAS _hoops_IRS _hoops_GHAR _hoops_IGIR _hoops_IH _hoops_RH _hoops_CISA */
	_hoops_HSPSH = (int) (0.01 * nr->_hoops_SRA->current._hoops_PRPSR.x);

	switch (pattern) {
		case FP_SOLID: {
			Sprintf_D (string, "FT1,%d,0;LT;", _hoops_HSPSH);
			if (state->_hoops_GASRI != 0) {
				_hoops_SHSRI (state, string);
				state->_hoops_GASRI = 0;
			}
		}	break;

		case FP_CHECKERBOARD:
		case FP_WINDOW_CHECKERBOARD: {
			float	scale;
			char	string1[64];
			char	string2[64];

			scale = (float)_hoops_HSPSH / 64.0f;
			Sprintf_D (string1, "FT4,%d,0;LT2,", _hoops_HSPSH);
			Sprintf_F (string2, "%f;", scale);
			Sprintf_SS (string, "%s%s", string1, string2);
			if (state->_hoops_GASRI != 1) {
				_hoops_SHSRI (state, string);
				state->_hoops_GASRI = 1;
			}
		}	break;

		case FP_CROSSHATCH:
		case FP_WINDOW_CROSSHATCH: {
			Sprintf_D (string, "FT4,%d,0;LT;", _hoops_HSPSH);
			if (state->_hoops_GASRI != 2) {
				_hoops_SHSRI (state, string);
				state->_hoops_GASRI = 2;
			}
		}	break;

		case FP_HORIZONTAL_BARS:
		case FP_WINDOW_HORIZONTAL_BARS: {
			Sprintf_D (string, "FT3,%d,0;LT;", _hoops_HSPSH);
			if (state->_hoops_GASRI != 3) {
				_hoops_SHSRI (state, string);
				state->_hoops_GASRI = 3;
			}
		}	break;

		case FP_VERTICAL_BARS:
		case FP_WINDOW_VERTICAL_BARS: {
			Sprintf_D (string, "FT3,%d,90;LT;", _hoops_HSPSH);
			if (state->_hoops_GASRI != 4) {
				_hoops_SHSRI (state, string);
				state->_hoops_GASRI = 4;
			}
		}	break;

		case FP_SLANT_LEFT:
		case FP_WINDOW_SLANT_LEFT: {
			Sprintf_D (string, "FT3,%d,135;LT;", _hoops_HSPSH);
			if (state->_hoops_GASRI != 5) {
				_hoops_SHSRI (state, string);
				state->_hoops_GASRI = 5;
			}
		}	break;

		case FP_SLANT_RIGHT:
		case FP_WINDOW_SLANT_RIGHT: {
			Sprintf_D (string, "FT3,%d,45;LT;", _hoops_HSPSH);
			if (state->_hoops_GASRI != 6) {
				_hoops_SHSRI (state, string);
				state->_hoops_GASRI = 6;
			}
		}	break;

		case FP_SQUARE_DOTS:
		case FP_WINDOW_SQUARE_DOTS: {
			Sprintf_D (string, "FT3,%d,0;LT1,1;", _hoops_HSPSH);
			if (state->_hoops_GASRI != 7) {
				_hoops_SHSRI (state, string);
				state->_hoops_GASRI = 7;
			}
		}	break;

		case FP_DIAMONDS:
		case FP_WINDOW_DIAMONDS: {
			Sprintf_D (string, "FT4,%d,45;LT;", _hoops_HSPSH);
			if (state->_hoops_GASRI != 8) {
				_hoops_SHSRI (state, string);
				state->_hoops_GASRI = 8;
			}
		}	break;

		/* _hoops_SGH _hoops_CAGRI _hoops_IH _hoops_IPSP _hoops_PAPR */
		case FP_USER_DEFINED: {
			Sprintf_D (string, "FT1,%d,0;LT;", _hoops_HSPSH);
			if (state->_hoops_GASRI != 0) {
				_hoops_SHSRI (state, string);
				state->_hoops_GASRI = 0;
			}
		}	break;

		/* _hoops_SGH _hoops_CAGRI _hoops_IH _hoops_SRHAI */
		default: {
			Sprintf_D (string, "FT1,%d,0;LT;", _hoops_HSPSH);
			if (state->_hoops_GASRI != 0) {
				_hoops_SHSRI (state, string);
				state->_hoops_GASRI = 0;
			}
		}	break;
	}
}


/*
 * _hoops_PGAA
 */
local void _hoops_PCPSR (
	Net_Rendition const &		nr) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_HCPAI alter *	state = _hoops_HHSRI (dc);
	char							string1[64];
	char							string2[64];
	char							_hoops_ASSRI[64];
	char							_hoops_GAHAI[64];
	long							left, right, bottom, top;

	if (state->_hoops_ASPAI) {
		if (state->_hoops_PSPAI) {
			/* _hoops_AHHGR _hoops_HRGR _hoops_GGR _hoops_GIRRR. _hoops_GPGP _hoops_RAHAI _hoops_CCH, _hoops_RH _hoops_HRGAI _hoops_PAH
			 * _hoops_CRCR _hoops_RH _hoops_HSPH _hoops_PCSRR _hoops_GGR _hoops_HRGAI _hoops_PSPA _hoops_HIS _hoops_SAHR _hoops_SGH _hoops_ACIPR
			 * _hoops_HSPH. _hoops_SPCA _hoops_HRGR _hoops_PSP _hoops_RRP _hoops_IS _hoops_RGIC _hoops_AHCA _hoops_RH _hoops_PIRA _hoops_IIGR _hoops_RH
			 * _hoops_GSSC _hoops_RAAP _hoops_ISRR (_hoops_PPAAI) _hoops_CR _hoops_CGSI _hoops_CHR _hoops_CPPSR _hoops_HII
			 * (0,0) _hoops_IS (_hoops_RPRAR,_hoops_PGGIR). _hoops_GPGP _hoops_RII _hoops_ARCCP, _hoops_PPAAI _hoops_PAH'_hoops_RA _hoops_SHH (-_hoops_RPRAR/2,-_hoops_PGGIR/2).
			 */
			left   = (long)_hoops_IHCR->_hoops_AGAA.left + 1L;
			bottom = (long)_hoops_IHCR->_hoops_AGAA.bottom + 1L;
			right  = (long)_hoops_IHCR->_hoops_AGAA.right - 1L;
			top	   = (long)_hoops_IHCR->_hoops_AGAA.top - 1L;
		}
		else {
			long	_hoops_AAHAI;

			/* _hoops_AHHGR _hoops_HRGR _hoops_GGR _hoops_GIRRR. _hoops_GPGP _hoops_HPRGR _hoops_CCH, _hoops_PRGI _hoops_PHRI
			 * _hoops_SAAA _hoops_HRGR _hoops_GGR _hoops_GIRRR, _hoops_RH _hoops_HSPH _hoops_PCSRR _hoops_HS _hoops_IS _hoops_SHH _hoops_ARP _hoops_GGR
			 * _hoops_HRGAI _hoops_PSPA. (_hoops_AHIPR'_hoops_GRI _hoops_PCPA _hoops_RH _hoops_HIHRA _hoops_CPPHR _hoops_PRGI _hoops_PHRI
			 * _hoops_RGR _hoops_AHPP _hoops_PAHAI _hoops_HAHAI.) _hoops_PHGP _hoops_SICR _hoops_HII _hoops_CPPSR
			 * _hoops_PSPA _hoops_ISSC _hoops_IS _hoops_HRGAI _hoops_PSPA.
			 */
			_hoops_AAHAI = (long)((float)(_hoops_IHCR->_hoops_AGAA.left - 1) *
							   (float)state->_hoops_CSPAI.x /
							   (float)dc->current._hoops_PRPSR.x);
			left = _hoops_AAHAI + 1L + state->_hoops_ISPAI.x;

			_hoops_AAHAI = (long)((float)(_hoops_IHCR->_hoops_AGAA.bottom - 1) *
							   (float)state->_hoops_CSPAI.y /
							   (float)dc->current._hoops_PRPSR.y);
			bottom = _hoops_AAHAI + 1L + state->_hoops_ISPAI.y;

			_hoops_AAHAI = (long)((float)(_hoops_IHCR->_hoops_AGAA.right + 1) *
							   (float)state->_hoops_CSPAI.x /
							   (float)dc->current._hoops_PRPSR.x);
			right = _hoops_AAHAI - 1L + state->_hoops_ISPAI.x;

			_hoops_AAHAI = (long)((float)(_hoops_IHCR->_hoops_AGAA.top + 1) *
							   (float)state->_hoops_CSPAI.y /
							   (float)dc->current._hoops_PRPSR.y);
			top = _hoops_AAHAI - 1L + state->_hoops_ISPAI.y;
		}
	}
	else {
		/*
		 * _hoops_AHHGR _hoops_HRGR _hoops_HAR _hoops_GGR _hoops_GIRRR (_hoops_SAHR _hoops_SGH _hoops_ACIPR _hoops_HSPH _hoops_PCSRR).
		 * _hoops_AGAH _hoops_IAGA _hoops_HII (0,0) _hoops_IS (_hoops_RPRAR,_hoops_PGGIR); _hoops_HGRRA, _hoops_HHH _hoops_IAHAI
		 * _hoops_HS (0,0) _hoops_HAR _hoops_GGR _hoops_RH _hoops_GSSC _hoops_RAAP, _hoops_HIH _hoops_GGR _hoops_RH _hoops_IRGP -
		 * _hoops_AGCR _hoops_IAHAI _hoops_PHHR _hoops_HII (-_hoops_RPRAR/2,-_hoops_PGGIR/2) _hoops_IS (_hoops_RPRAR/2,_hoops_PGGIR/2) _hoops_HIS
		 * _hoops_RH _hoops_PHCSH _hoops_GCA _hoops_CAHAI _hoops_PSAP (_hoops_CPRAA _hoops_IRS _hoops_HHHR
		 * _hoops_PIRA) _hoops_RH _hoops_RGGHR _hoops_ARSAR _hoops_HPP _hoops_AGAH
		 */
		left   = (long)_hoops_IHCR->_hoops_AGAA.left + 1L + state->_hoops_ISPAI.x;
		bottom = (long)_hoops_IHCR->_hoops_AGAA.bottom + 1L + state->_hoops_ISPAI.y;
		right  = (long)_hoops_IHCR->_hoops_AGAA.right - 1L + state->_hoops_ISPAI.x;
		top	   = (long)_hoops_IHCR->_hoops_AGAA.top - 1L + state->_hoops_ISPAI.y;
	}

	/* _hoops_RCSRR _hoops_PCCP _hoops_SAHAI _hoops_CPIRH _hoops_HGGSP _hoops_IRGAA _hoops_CCA _hoops_HRGAI _hoops_PSPA */
	Sprintf_LD (_hoops_ASSRI, "IW%D,", left);
	Sprintf_LD (_hoops_GAHAI, "%D,", bottom);
	Sprintf_SS (string1, "%s%s", _hoops_ASSRI, _hoops_GAHAI);
	Sprintf_LD (_hoops_ASSRI, "%D,", right);
	Sprintf_LD (_hoops_GAHAI, "%D;", top);
	Sprintf_SS (string2, "%s%s", _hoops_ASSRI, _hoops_GAHAI);
	Sprintf_SS (_hoops_ASSRI, "%s%s", string1, string2);
	_hoops_SHSRI (state, _hoops_ASSRI);
}


/*
 * _hoops_SRAC
 */
local bool start_device (
	Display_Context alter		*dc) {
	_hoops_HCPAI alter				*state;

	ZALLOC (state, _hoops_HCPAI);
	dc->data = (void alter *) state;

	/* _hoops_RGHR _hoops_HAS/_hoops_GCSR */
	state->_hoops_PSCRI = (FILE alter *)-1;
	state->_hoops_ICPAI = -1;

	/* _hoops_ASCA _hoops_IRGAA _hoops_PRCA */
	state->_hoops_HSPAI = true;
	state->_hoops_SSPAI = 1.0f;

	state->_hoops_HGHAI = _hoops_RIPAI;
	state->_hoops_PGHAI =
		state->_hoops_GASRI = -1;

	if ((state->_hoops_PSCRI = fopen (dc->_hoops_PCRSR, "w")) == null) {
		HE_ERROR (HEC_HPGL_DRIVER, HES_FILE_OPEN,
				  "Error opening a file for plotting");
		FREE (state, _hoops_HCPAI);
		dc->data = null;
		return false;
	}

	return true;
}


/*
 * _hoops_SRAC
 */
local void stop_device (
	Display_Context alter		*dc) {
	_hoops_HCPAI alter				*state = _hoops_HHSRI (dc);

	fprintf (state->_hoops_PSCRI, "VS;NR;\n");
	fclose (state->_hoops_PSCRI);

	FREE (state, _hoops_HCPAI);
	dc->data = null;
}


/*
 * _hoops_SRAC
 */
local void get_physical_info (
	Display_Context alter		*dc) {
	_hoops_HCPAI alter				*state = _hoops_HHSRI (dc);

	/*
	 * _hoops_IGIR _hoops_GGR _hoops_SAPSR
	 *
	 * _hoops_HGI _hoops_PCPH _hoops_IIGS _hoops_HPHS _hoops_AHCA _hoops_RH _hoops_SISS _hoops_IS _hoops_AAPA _hoops_AGAH.
	 * _hoops_HGI _hoops_PCPH _hoops_HRGR _hoops_HHASH _hoops_HII _hoops_RII _hoops_AGAH _hoops_SISS _hoops_SPSIR _hoops_GGR _hoops_SGS
	 * _hoops_RGR _hoops_PCPH _hoops_PIHA _hoops_ACPA _hoops_RH _hoops_CPHSR _hoops_IGIR _hoops_IIGR _hoops_RH _hoops_SISS _hoops_IS _hoops_IIS
	 * _hoops_AGAH _hoops_ACPA _hoops_RSH _hoops_AHPH _hoops_ASPA _hoops_RH _hoops_SISS _hoops_SSCP. _hoops_HSRR _hoops_SGS _hoops_SCPC, _hoops_RH
	 * _hoops_CPHSR _hoops_IGIR _hoops_RHPP _hoops_HCSP _hoops_HRGR _hoops_RAICR _hoops_IS _hoops_CACH _hoops_RPP _hoops_SCH _hoops_HRGR _hoops_ARP. _hoops_CGP
	 * _hoops_SCH _hoops_HRGR, _hoops_RH _hoops_CPHSR _hoops_IGIR _hoops_HRGR _hoops_ARP _hoops_IS _hoops_PSSP _hoops_RH _hoops_RHPP _hoops_HCSP _hoops_PIRA.
	 * _hoops_CGP _hoops_RH _hoops_RHPP _hoops_HCSP _hoops_HRGR _hoops_HAR _hoops_ARP, _hoops_IRS _hoops_SHIR _hoops_PIRA _hoops_HRGR _hoops_IGI. _hoops_HPGHR _hoops_GHGA
	 * _hoops_SCH _hoops_RGR _hoops_PPRRR, _hoops_RH _hoops_CPHSR _hoops_IGIR _hoops_SAGGR _hoops_ARP _hoops_IS _hoops_SHH _hoops_HISI _hoops_AGAH _hoops_HRGR
	 * _hoops_IGRC _hoops_CPIC _hoops_IS _hoops_SGH _hoops_IGH _hoops_RH _hoops_CPHSR _hoops_IGIR _hoops_RHPP _hoops_HCSP
	 * _hoops_SSCP _hoops_RPII _hoops_ARP _hoops_PAR _hoops_HAR.
	 */
	if (dc->options._hoops_SPHSR.x == -1) {
		/* _hoops_GPHAI _hoops_GGR _hoops_SHIR */
		dc->_hoops_PGCC.size.x = 18.0f;
		dc->_hoops_PGCC.size.y = 25.0f;
	}
	else {
		/* _hoops_GPHAI _hoops_RGR _hoops_GGR _hoops_HIS _hoops_HRGAI _hoops_HPI _hoops_IISRR _hoops_IPHR */
		dc->_hoops_PGCC.size.x = dc->options._hoops_SPHSR.x;
		dc->_hoops_PGCC.size.y = dc->options._hoops_SPHSR.y;
	}

        /* #11903 _hoops_RGAR _hoops_ARP _hoops_SHIR _hoops_III _hoops_SGCR _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_PIP _hoops_IPPSR _hoops_III _hoops_SGCR. */
        if(!dc->options._hoops_HHHSR)
            dc->_hoops_PGCC._hoops_IHHSR = dc->options._hoops_GHHSR/150.0f;

	/*
	 * _hoops_IGIR _hoops_GGR _hoops_HRGAI _hoops_PSPA
	 *
	 * _hoops_PAGAR _hoops_RH _hoops_PHI _hoops_IIGR _hoops_HRGAI _hoops_PSPA _hoops_HRGR _hoops_GAGPR 400 _hoops_IACH
	 * _hoops_RH _hoops_PHI _hoops_IIGR _hoops_SAPSR; _hoops_HGRRA, _hoops_RPHAI _hoops_APHAI _hoops_SSCP _hoops_PIIRH
	 * _hoops_HPGR _hoops_CHGC _hoops_SPR _hoops_HRGAI _hoops_SGS _hoops_SSCP _hoops_IRS _hoops_HAGH _hoops_PPHAI, _hoops_IAS._hoops_ISHI. 410.
	 * _hoops_RCPA _hoops_ASSS _hoops_HPHAI _hoops_IS _hoops_IPHAI _hoops_HGPP _hoops_IAHAI, _hoops_PPR _hoops_IS
	 * _hoops_SRCH _hoops_CPHAI _hoops_GGR _hoops_RH 410 _hoops_AGIR, _hoops_RH _hoops_RHPP _hoops_GAGPR _hoops_IHIGR
	 * _hoops_RH _hoops_CCRPR _hoops_IS _hoops_ARP _hoops_IRS _hoops_HISRA _hoops_IGRH _hoops_SGS _hoops_SIGH "_hoops_GHAP'_hoops_SPHAI _hoops_GHHAI
	 * _hoops_RH _hoops_AHHSR" _hoops_PPR _hoops_PSCR _hoops_RH _hoops_GGI _hoops_PISH _hoops_RHPP _hoops_HCSP (_hoops_PGAP _hoops_CHH
	 * _hoops_IAII _hoops_PHHR _hoops_PPRAR) _hoops_HRGR _hoops_RHHAI _hoops_CRGR _hoops_IHGS _hoops_RH _hoops_AHHSR.
	 */
	if (BIT (dc->options._hoops_IRARR, _hoops_RHPAI)) {
		if (dc->options._hoops_AGHRP < 1) {
			HE_ERROR2 (HEC_HPGL_DRIVER, HES_INVALID_NUMBER,
					  "With debug=8 enabled, the write mask option",
					  "must be specified greater than 1 (using 400)");
			state->_hoops_CSPAI.x = (long)(dc->_hoops_PGCC.size.x * 400);
			state->_hoops_CSPAI.y = (long)(dc->_hoops_PGCC.size.y * 400);
		}
		else {
			state->_hoops_CSPAI.x =
				(long)(dc->_hoops_PGCC.size.x * dc->options._hoops_AGHRP);
			state->_hoops_CSPAI.y =
				(long)(dc->_hoops_PGCC.size.y * dc->options._hoops_AGHRP);
		}
	}
	else {
		state->_hoops_CSPAI.x = (long)(dc->_hoops_PGCC.size.x * 400);
		state->_hoops_CSPAI.y = (long)(dc->_hoops_PGCC.size.y * 400);
	}

	/*
	 * _hoops_RHRRH _hoops_CPHSR _hoops_IGIR _hoops_IIGR _hoops_SISS _hoops_IS _hoops_AAPA _hoops_AGAH
	 *
	 * _hoops_AHHGR _hoops_HRGR _hoops_SIGR _hoops_IH _hoops_PCRR _hoops_SGS _hoops_CHH _hoops_IHCC 32,767.
	 * _hoops_IPCP _hoops_PIRA 32,000 _hoops_HRGR _hoops_IGI _hoops_IS _hoops_SHSP _hoops_RSIAR _hoops_IH _hoops_PCRR _hoops_SGS
	 * _hoops_HSSC _hoops_SIPP _hoops_RH _hoops_ASCA _hoops_CCAC _hoops_HIH _hoops_GIAA _hoops_RH _hoops_SHPP _hoops_HSPH _hoops_CCAC.
	 */
	if (state->_hoops_CSPAI.x > 32000L ||
		state->_hoops_CSPAI.y > 32000L ||
		BIT (dc->options._hoops_IRARR, _hoops_SPPAI)) {
		/* _hoops_IRGH _hoops_RIP _hoops_RAICR _hoops_GGR _hoops_ASCA _hoops_SICAR */
		state->_hoops_ASPAI = true;

		/* _hoops_IGI _hoops_GGR _hoops_AAPA _hoops_AGAH _hoops_IISRR */
		if (state->_hoops_CSPAI.x > state->_hoops_CSPAI.y) {
			dc->_hoops_PGCC._hoops_PRPSR.x = 32000;
			dc->_hoops_PGCC._hoops_PRPSR.y = (int)(32000.0f *
				(float)state->_hoops_CSPAI.y / (float)state->_hoops_CSPAI.x);
		}
		else {
			dc->_hoops_PGCC._hoops_PRPSR.x = (int)(32000.0f *
				(float)state->_hoops_CSPAI.x / (float)state->_hoops_CSPAI.y);
			dc->_hoops_PGCC._hoops_PRPSR.y = 32000;
		}

		/* _hoops_IGI _hoops_IH _hoops_IAHAI _hoops_CAS _hoops_GSSC _hoops_RAAP _hoops_HRGR _hoops_HAR (0,0) */
		if (BIT (dc->options._hoops_IRARR, _hoops_GHPAI)) {
			state->_hoops_ISPAI.x = (long)dc->options._hoops_PCPRP[0][0];
			state->_hoops_ISPAI.y = (long)dc->options._hoops_PCPRP[0][1];
		}
		else {
			state->_hoops_ISPAI.x = 0L;
			state->_hoops_ISPAI.y = 0L;
		}

		/*
		 * _hoops_PRGI _hoops_IH _hoops_IAHAI _hoops_CAS _hoops_GSSC _hoops_RAAP _hoops_HRGR _hoops_HAR (0,0), _hoops_ASCA
		 * _hoops_HRGR _hoops_HII (0,0) _hoops_IS (_hoops_RPRAR,_hoops_PGGIR) _hoops_CGPR _hoops_GGR _hoops_CPPSR _hoops_CCH
		 */
		state->_hoops_SIPAI.x = 0L;
		state->_hoops_SIPAI.y = 0L;

		/*
		 * _hoops_HSRR _hoops_SAAA _hoops_CCH, _hoops_CACH _hoops_RSH _hoops_RH _hoops_CIHH _hoops_PRCH _hoops_CGH _hoops_SHH _hoops_ARP.
		 * _hoops_HPGHR _hoops_SHIR, _hoops_SSIA _hoops_CHR _hoops_ARP _hoops_GGR _hoops_HRGAI _hoops_PSPA (_hoops_PRGI _hoops_GGR _hoops_CPPSR _hoops_CCH!)
		 * _hoops_HCCPR _hoops_RH _hoops_IPSP _hoops_SIGH _hoops_SGS _hoops_HPASR _hoops_SISS _hoops_SSCP _hoops_PCCP _hoops_AHHAI _hoops_CCH
		 * _hoops_PGAP _hoops_IIHH _hoops_CIHH _hoops_PRCH (_hoops_SAHAI _hoops_RHASR) _hoops_GGR _hoops_CPPSR _hoops_PSPA.
		 */
		if (BIT (dc->options._hoops_IRARR, _hoops_PHPAI))
			state->_hoops_PSPAI = true;
		else
			state->_hoops_PSPAI = false;
	}
	else {
		/* _hoops_IRGH _hoops_RIP _hoops_RAICR _hoops_GGR _hoops_ASCA _hoops_SICAR */
		state->_hoops_ASPAI = false;

		/* _hoops_IGI _hoops_GGR _hoops_AAPA _hoops_AGAH _hoops_IISRR */
		dc->_hoops_PGCC._hoops_PRPSR.x = (int)state->_hoops_CSPAI.x;
		dc->_hoops_PGCC._hoops_PRPSR.y = (int)state->_hoops_CSPAI.y;

		/* _hoops_IGI _hoops_IH _hoops_IAHAI _hoops_CAS _hoops_GSSC _hoops_RAAP _hoops_HRGR _hoops_HAR (0,0) */
		if (BIT (dc->options._hoops_IRARR, _hoops_GHPAI)) {
			state->_hoops_ISPAI.x = (long)dc->options._hoops_PCPRP[0][0];
			state->_hoops_ISPAI.y = (long)dc->options._hoops_PCPRP[0][1];
			state->_hoops_SIPAI.x = state->_hoops_ISPAI.x;
			state->_hoops_SIPAI.y = state->_hoops_ISPAI.y;
		}
		else {
			state->_hoops_ISPAI.x =
				state->_hoops_ISPAI.y =
				state->_hoops_SIPAI.x =
				state->_hoops_SIPAI.y = 0L;
		}
	}

	/* _hoops_SISPR _hoops_SPGC _hoops_CIHH _hoops_GPP _hoops_HHH _hoops_AGSHA, _hoops_SSHSR _hoops_PAH _hoops_HHSP */
	if (BIT (dc->options._hoops_IRARR, _hoops_AHPAI))
		state->_hoops_HSPAI = false;
	else
		state->_hoops_HSPAI = true;

	/* _hoops_III _hoops_PAIA _hoops_CHR _hoops_ARP _hoops_GH _hoops_IH 1024 _hoops_HIS _hoops_SRPA _hoops_IIHA _hoops_GPP _hoops_HRGAI _hoops_PSPA */
	dc->_hoops_PGCC._hoops_ICPGH =
		(float)dc->_hoops_PGCC._hoops_PRPSR.x / 1024.0f;

	dc->_hoops_PGCC._hoops_ARISR.x = 0;
	dc->_hoops_PGCC._hoops_ARISR.y = 0;

	dc->_hoops_PGCC._hoops_PIHSR = _hoops_SIHSR;
	dc->_hoops_PGCC._hoops_AAPSR = 256;
	dc->_hoops_PGCC._hoops_APASR = 0;
	dc->_hoops_PGCC._hoops_PCHSR = 2;
	dc->_hoops_PGCC.flags &= ~_hoops_GGISR;
	dc->_hoops_PGCC.flags |= _hoops_GIHSR;

	dc->_hoops_PGCC._hoops_CHHSR = _hoops_SHHSR;
	dc->_hoops_PGCC.driver_type = "HPGL";
	dc->_hoops_PGCC._hoops_SCHSR = "$Revision: 1.189 $";
	dc->_hoops_PGCC.flags &= ~_hoops_HSHSR;
	dc->_hoops_PGCC.flags &= ~_hoops_RSHSR;
	dc->_hoops_PGCC._hoops_ASHSR = 0;
	dc->_hoops_PGCC.flags &= ~_hoops_PSHSR;
	dc->_hoops_PGCC._hoops_ICHSR = "pen plotter";

	dc->flags |= _hoops_CSHSR;

	if (dc->options._hoops_HAPIR) {
		/* _hoops_SRPA _hoops_HII _hoops_PHHAI (_hoops_RPP _hoops_HAHH) */
		if (HI_CI_Wild_Equal_Strings_To_Max (dc->options._hoops_HAPIR->name.text,
											 dc->options._hoops_HAPIR->name.length,
											 "laser jet")) {
			/* _hoops_RPCC _hoops_IIGR "_hoops_RRHAI _hoops_HHHAI" _hoops_AGSR _hoops_SGH _hoops_IIIAR _hoops_CSGSR _hoops_ARCR */
			dc->_hoops_PGCC._hoops_ICHSR = "laser printer";
			state->_hoops_CCPAI = true;
		}
		else if (HI_CI_Wild_Equal_Strings_To_Max (
					 dc->options._hoops_HAPIR->name.text,
					 dc->options._hoops_HAPIR->name.length,
					 "RS232 connected")) {
			/* _hoops_RPCC _hoops_IIGR "_hoops_IHHAI _hoops_RIHA" _hoops_AGSR _hoops_GGCR _hoops_HGSR _hoops_RHASR */
			dc->_hoops_PGCC._hoops_ICHSR = "RS232 plotter";
			state->_hoops_SCPAI = true;
		}
	}
	else {
		/* _hoops_SRPA _hoops_HII _hoops_RGHR _hoops_PHHAI (_hoops_RPP _hoops_HAHH) */
		if (HI_CI_Wild_Equal_Strings_To_Max (dc->_hoops_PCRSR,
											 dc->_hoops_HCRSR,
											 "*.ljp")) {
			/* _hoops_PHHAI _hoops_IIGR ._hoops_CHHAI _hoops_AGSR _hoops_SGH _hoops_IIIAR _hoops_CSGSR _hoops_ARCR */
			dc->_hoops_PGCC._hoops_ICHSR = "laser printer";
			state->_hoops_CCPAI = true;
		}
		else if (HI_CI_Wild_Equal_Strings_To_Max (dc->_hoops_PCRSR,
												  dc->_hoops_HCRSR,
												  "*.232")) {
			/* _hoops_PHHAI _hoops_IIGR .232 _hoops_AGSR _hoops_GGCR _hoops_HGSR _hoops_RHASR */
			dc->_hoops_PGCC._hoops_ICHSR = "RS232 plotter";
			state->_hoops_SCPAI = true;
		}
	}

	if (BIT (dc->options._hoops_IRARR, _hoops_HHPAI))
		state->_hoops_RSPAI = true;
	else
		state->_hoops_RSPAI = false;
	/*
	 * _hoops_RHRPA _hoops_RGR _hoops_PPSR, _hoops_HCR _hoops_HPHS _hoops_SSCP _hoops_RPII _hoops_PIIRH _hoops_IS _hoops_AAPA _hoops_AGAH
	 * _hoops_IH _hoops_RH _hoops_RCAAI _hoops_HSCHR. _hoops_IPCP _hoops_IPSP _hoops_SSCP _hoops_ARP _hoops_RH _hoops_CPHSR _hoops_IGIR
	 * _hoops_RHPP _hoops_HCSP, _hoops_RH _hoops_PHI _hoops_IIGR _hoops_ASPA _hoops_SSCP _hoops_RPII _hoops_GGSRA _hoops_HII _hoops_RH
	 * _hoops_CPHSR _hoops_IGIR, _hoops_SR _hoops_HS _hoops_CIIHP _hoops_RPP _hoops_SR _hoops_RRP _hoops_SAAA _hoops_PAR _hoops_HAR, _hoops_PPR
	 * _hoops_RH _hoops_HCCIA _hoops_HIHP _hoops_SSCP _hoops_RPII _hoops_IGI _hoops_IS _hoops_ARP _hoops_RH _hoops_GSSC _hoops_RAAP
	 * _hoops_SISS _hoops_ISRR. _hoops_PHGP _hoops_HA _hoops_PCPA _hoops_RPP _hoops_RH _hoops_CCRPR _hoops_APSI
	 * _hoops_HISGH (_hoops_PGAP _hoops_HRGR _hoops_RH _hoops_SHIR _hoops_HPP _hoops_RH _hoops_PPRRR)?
	 *
	 * _hoops_PHGP _hoops_SGS _hoops_RH _hoops_CCRPR _hoops_RHAP _hoops_HAR _hoops_HS _hoops_IS _hoops_PHHR _hoops_ISSC _hoops_PPR _hoops_PRHSA _hoops_HCR _hoops_IIGR _hoops_AGCR
	 * _hoops_HRP, _hoops_AGAH _hoops_GRS _hoops_AA _hoops_RH _hoops_SHHAI _hoops_IH _hoops_HISGH. _hoops_GPGP _hoops_RII
	 * _hoops_ARCCP:
	 *
	 * (_hoops_IRS) _hoops_RH _hoops_CPHSR _hoops_IGIR _hoops_SISR _hoops_PPR _hoops_HAPC _hoops_GRS _hoops_SHH _hoops_AHPHR _hoops_HPP _hoops_AGAH _hoops_ARPP
	 *	   _hoops_SCH _hoops_RHAP _hoops_RGCI _hoops_IISRR, _hoops_IAS._hoops_ISHI. _hoops_GPIA _hoops_PPR _hoops_HCGR _hoops_IGIR
	 * (_hoops_RCSR) _hoops_RH _hoops_PHI _hoops_IIGR _hoops_ASPA _hoops_SISR _hoops_PPR _hoops_HAPC _hoops_GRS _hoops_SHH _hoops_AHPHR _hoops_HPP _hoops_AGAH _hoops_ARPP
	 *	   _hoops_SCH _hoops_RHAP _hoops_RGCI _hoops_IISRR, _hoops_IAS._hoops_ISHI. _hoops_CPSP->_hoops_GCRAI
	 *
	 * _hoops_IPCP _hoops_RGAR _hoops_CGSI _hoops_SGS _hoops_AGAH _hoops_SSSCP _hoops_IPHAI _hoops_CHR _hoops_RH _hoops_CGSI _hoops_SGS
	 * _hoops_CHR _hoops_CPHR _hoops_HCIAA _hoops_GGR _hoops_RH _hoops_RHPP. _hoops_GPGP _hoops_RGR _hoops_AGIR, _hoops_SGS _hoops_AGSR:
	 *
	 * (_hoops_IRS) _hoops_IRGH _hoops_HRGAI _hoops_PSPA (_hoops_IHGS _hoops_IGCGI _hoops_HCIAA _hoops_GAR _hoops_IRS _hoops_RGRRR _hoops_PGGA
	 *	   400 * _hoops_CPHSR _hoops_IGIR _hoops_GHCA _hoops_IHCC _hoops_PCCP _hoops_HHIPR)
	 * (_hoops_RCSR) _hoops_AASC _hoops_HSPH _hoops_PSPA (_hoops_IHGS _hoops_IGCGI _hoops_HCIAA _hoops_PGGA _hoops_HHH _hoops_IAHAI
	 *	   _hoops_HSPH _hoops_GGR _hoops_HRGAI _hoops_PSPA _hoops_PRGI _hoops_CGPR _hoops_GGR _hoops_CPPSR _hoops_CCH)
	 * (_hoops_GSGGR) _hoops_AASC _hoops_PGSA _hoops_PSPA (_hoops_IHGS _hoops_IGCGI _hoops_HCIAA _hoops_PGGA _hoops_HHH _hoops_IAHAI
	 *	   _hoops_HS (0,0) _hoops_GGR _hoops_RH _hoops_RHCH _hoops_RIIA _hoops_IIGR _hoops_RH _hoops_GSSC _hoops_RAAP)
	 *
	 * _hoops_PHGP _hoops_RPP _hoops_HISGH _hoops_HRGR _hoops_GGR _hoops_GIRRR, _hoops_AGCR _hoops_HSH _hoops_PIHA _hoops_SHH _hoops_AHPHR.
	 */
	dc->_hoops_PGCC.flags |= _hoops_ISHSR;
	if (dc->options._hoops_ARPSR) {
		long	temp;

		/* _hoops_HRGAI _hoops_PSPA */
		temp = state->_hoops_CSPAI.x;
		state->_hoops_CSPAI.x = state->_hoops_CSPAI.y;
		state->_hoops_CSPAI.y = temp;

		/* _hoops_AASC _hoops_HSPH _hoops_PSPA */
		temp = state->_hoops_ISPAI.x;
		state->_hoops_ISPAI.x = state->_hoops_ISPAI.y;
		state->_hoops_ISPAI.y = temp;

		/* _hoops_AASC _hoops_PGSA _hoops_HPI */
		temp = state->_hoops_SIPAI.x;
		state->_hoops_SIPAI.x = state->_hoops_SIPAI.y;
		state->_hoops_SIPAI.y = temp;
	}


#ifdef _hoops_CGSPR
  {
	int		i;

	printf ("dc->physical.number_of_pixels = (%d,%d)\n",
			dc->_hoops_PGCC._hoops_PRPSR.x,
			dc->_hoops_PGCC._hoops_PRPSR.y);
	printf ("state->plotter_unit = (%ld,%ld)\n",
			state->_hoops_CSPAI.x,
			state->_hoops_CSPAI.y);
	printf ("state->min_clip_unit = (%ld,%ld)\n",
			state->_hoops_ISPAI.x,
			state->_hoops_ISPAI.y);
	printf ("state->min_draw_unit = (%ld,%ld)\n",
			state->_hoops_SIPAI.x,
			state->_hoops_SIPAI.y);
	for (i = 0; i < 3; i++)
		printf ("locater transform[%d][0] = %f, [%d][1] = %f\n",
				i, dc->options._hoops_PCPRP[i][0],
				i, dc->options._hoops_PCPRP[i][1]);
  }
#endif /* _hoops_SHRS */
}


/*
 * _hoops_SRAC
 */
local void init_picture (
	Net_Rendition const & nr) {
	Display_Context const		*dc = nr->_hoops_SRA;
	_hoops_HCPAI alter				*state = _hoops_HHSRI (dc);

	if (!BIT(dc->flags, _hoops_SAISR)) return;

	/* _hoops_CSGSR _hoops_ACHPR _hoops_HRGR _hoops_GIHAI _hoops_GAR _hoops_SR _hoops_PHHR _hoops_IGIAR */
	if (state->_hoops_SSPAI != dc->options._hoops_GSHSR)
		_hoops_HRHAI (dc);

	/*
	 * _hoops_CPGP _hoops_CSGSR _hoops_HRGR _hoops_AGCA _hoops_ISSC _hoops_GGR _hoops_RIHAI _hoops_IH _hoops_GRR _hoops_CCAH _hoops_PAAP (_hoops_CCAH _hoops_HSHIA),
	 * _hoops_HIAP _hoops_HSHR _hoops_HSH _hoops_ARI.
	 */
	state->_hoops_GGHAI = (_hoops_GARRR)0;
}


/*
 * _hoops_SRAC
 */
local void finish_picture (
	Net_Rendition const & nr,
	bool						swap_buffers) {
	Display_Context const		*dc = nr->_hoops_SRA;
	_hoops_HCPAI alter				*state = _hoops_IHSRI (nr);

	UNREFERENCED (swap_buffers);

	if (!BIT(dc->flags, _hoops_SAISR)) return;

	if (!state->_hoops_CCPAI)
		/* _hoops_AIHAI _hoops_CSGSR _hoops_IH _hoops_CCAH _hoops_HSHIA */
		_hoops_ARHAI (state, (_hoops_GARSR)_hoops_RIPAI);

	/*
	 * _hoops_PIHAI _hoops_SCGR _hoops_HSHIA _hoops_PPR _hoops_IPPRH _hoops_IH _hoops_IRS _hoops_CCAH _hoops_HSHIA. _hoops_SGPR _hoops_RH _hoops_HIHAI _hoops_CCGGR
	 * _hoops_RIIA _hoops_IIGR _hoops_IIHAI _hoops_IH _hoops_AAACR _hoops_CCA _hoops_RII _hoops_CSAAI _hoops_IAHAI.
	 */
	/* _hoops_SR _hoops_IRAA _hoops_CIHAI _hoops_HAR _hoops_IS _hoops_AACC _hoops_RH _hoops_HSHIA _hoops_ARI*/
	if (state->_hoops_RSPAI)
		_hoops_SHSRI (state, "EC1;AF;");
	else
		_hoops_SHSRI (state, "AF;");

	if ((fputs ("\n", state->_hoops_PSCRI) == -1))
		HE_ERROR (HEC_HPGL_DRIVER, HES_WRITE_FAILED,
				  "Can't write finish new line to file");
	state->_hoops_GSPAI = 0;

	_hoops_IGHAI (state);
}


/*
 * _hoops_SRAC
 */
local POINTER_SIZED_INT get_outer_window (
	Display_Context const		*dc) {
	_hoops_HCPAI alter				*state = _hoops_HHSRI (dc);
	char							string[80];

	/* _hoops_IHPI */
	if (state->_hoops_SCPAI) {
		char const		*in;
		char const		*_hoops_SIHAI;
		char alter		*_hoops_PAGR;

		/* _hoops_PHCH _hoops_HRAIA-_hoops_IISGA-_hoops_IHRPR _hoops_IS \033 */
		in = dc->options._hoops_IAPIR.text;
		_hoops_SIHAI = dc->options._hoops_IAPIR.text + dc->options._hoops_IAPIR.length - 3;
		_hoops_PAGR = string;
		while (in <= _hoops_SIHAI)
			if (in[0] == 'E' && in[1] == 'S' && in[2] == 'C') {
				*_hoops_PAGR++ = '\033';
				in += 3;
			}
			else
				*_hoops_PAGR++ = *in++;
		*_hoops_PAGR++ = *in++;
		*_hoops_PAGR++ = *in;
		*_hoops_PAGR = '\0';
		_hoops_SHSRI (state, string);
	}
	_hoops_SHSRI (state, "IN;");

	/* _hoops_PSGR _hoops_ACHPR */
	Sprintf_D (string, "SP0;VS%d;", (int) _hoops_AIPAI);
	_hoops_SHSRI (state, string);

	/* _hoops_IRSHR 90 _hoops_ASIPR (_hoops_CPHR _hoops_GSSRH _hoops_PPAAI _hoops_PPR _hoops_HPAAI _hoops_HIAP) */
	if (!dc->options._hoops_ARPSR)
		_hoops_SHSRI (state, "RO90;");

	/* _hoops_HIAP _hoops_PPAAI _hoops_PPR _hoops_HPAAI _hoops_IS _hoops_IRS _hoops_SASI _hoops_AHC */
	{
		char	_hoops_GCHAI[64];
		char	_hoops_CGPCP[64];
		char	_hoops_RCHAI[64];
		char	_hoops_ACHAI[64];
		long	temp;

		Sprintf_LD (_hoops_RCHAI, "IP%D,", state->_hoops_ISPAI.x);
		Sprintf_LD (_hoops_ACHAI, "%D,", state->_hoops_ISPAI.y);
		Sprintf_SS (_hoops_GCHAI, "%s%s", _hoops_RCHAI, _hoops_ACHAI);
		temp = state->_hoops_CSPAI.x + state->_hoops_ISPAI.x;
		Sprintf_LD (_hoops_RCHAI, "%D,", temp);
		temp = state->_hoops_CSPAI.y + state->_hoops_ISPAI.y;
		Sprintf_LD (_hoops_ACHAI, "%D;", temp);
		Sprintf_SS (_hoops_CGPCP, "%s%s", _hoops_RCHAI, _hoops_ACHAI);
		Sprintf_SS (string, "%s%s", _hoops_GCHAI, _hoops_CGPCP);
		_hoops_SHSRI (state, string);
	}

	/* _hoops_SAAA */
	if (state->_hoops_ASPAI) {
		Sprintf_DD (string, "SC0,%d,0,%d;",
					dc->current._hoops_PRPSR.x,
					dc->current._hoops_PRPSR.y);
		_hoops_SHSRI (state, string);
	}

	return ((POINTER_SIZED_INT) state->_hoops_PSCRI);
}


/*
 * _hoops_SRAC
 */
local void draw_dc_polyline (
	Net_Rendition const &	nr,
	int						count,
	DC_Point const *		points) {
	Line_Rendition const &	_hoops_HC = nr->_hoops_AHP;

	if (nr->transform_rendition->_hoops_HCHH == null &&
		BIT(_hoops_HC->line_style->flags, LSF_SOLID) &&
		_hoops_HC->weight == 1 &&
		_hoops_HC->style == 0) {

		_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
		_hoops_HCPAI alter *	state = _hoops_IHSRI (nr);
		char						string[64];

		/* _hoops_PCHAI */
		if (state->_hoops_HSPAI &&
			_hoops_IHCR->_hoops_CPA != state->_hoops_RGHAI) {
			_hoops_PCPSR (nr);
			state->_hoops_RGHAI = _hoops_IHCR->_hoops_CPA;
		}

		/* _hoops_SSPC _hoops_HGICP->_hoops_SGCR _hoops_PPR _hoops_ARP _hoops_GH _hoops_PCSPR */
		if (_hoops_HC->_hoops_CPA != state->_hoops_GGHAI) {
			_hoops_AIPSR (LP_SOLID, state);
			_hoops_ARHAI (state, _hoops_HC->color._hoops_PGGCR);
			state->_hoops_GGHAI = _hoops_HC->_hoops_CPA;
		}

		/* _hoops_HCHAI */
		if (count > 0) {
			DC_Point const *_hoops_ICHAI = points + count;

			_hoops_PIPAI (string, points->x, points->y, state);
			while ((++points) != _hoops_ICHAI) {
				_hoops_GCPAI (string, (points->x), (points->y), state);
			}
		}
		else {
			int _hoops_RRC;

			_hoops_ICHC (count, _hoops_RRC, 2);
			while (count-- > 0) {
				_hoops_PIPAI (string, points[0].x, points[0].y, state);
				_hoops_GCPAI (string, points[1].x, points[1].y, state);
				points += _hoops_RRC;
			}
		}

	}else{

#ifdef _hoops_CCHAI
		int _hoops_SCHAI;

		/*
		 * _hoops_ASCA _hoops_AAIA _hoops_APGR _hoops_AIH _hoops_RH _hoops_HRGAI _hoops_HRGR _hoops_IRS _hoops_AHCI _hoops_GRIGI:
		 *		 1. _hoops_HHH _hoops_AAPI (_hoops_PGAP _hoops_GGHAA _hoops_AAIA _hoops_APGR) _hoops_SAHR
		 *			_hoops_SAHR _hoops_IIP _hoops_GSHAI _hoops_GH
		 *		 2. _hoops_RSHAI _hoops_APGR _hoops_RIAGR _hoops_ASHAI _hoops_CR _hoops_HPHC _hoops_CSAP _hoops_CPHR _hoops_GGR
		 *			_hoops_HRGAI _hoops_PSPA (_hoops_CPPPR _hoops_RISA), _hoops_HIH _hoops_HSGP _hoops_SAAA
		 *			_hoops_APPP _hoops_CRGR _hoops_HIHA _hoops_CSPH->_hoops_CPHSR._hoops_PSHAI
		 */
		_hoops_SCHAI = _hoops_HC->weight;
		((Line_Rendition alter &)_hoops_HC)->weight = 1;
		HD_Std_DC_Polyline (nr, count, points);
		((Line_Rendition alter &)_hoops_HC)->weight = _hoops_SCHAI;
#else
		HD_Std_DC_Polyline (nr, count, points);
#endif

	}
}


/*
 * _hoops_SRAC
 */
local void draw_dc_rectangle (
	Net_Rendition const &		nr,
	int							left,
	int							right,
	int							bottom,
	int							top) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HCPAI alter *	state = _hoops_IHSRI (nr);
	char						string[64];

	/*
	 * _hoops_HGGSP _hoops_RAGAH _hoops_CHR _hoops_CHCC _hoops_GRP _hoops_ISAC.
	 * _hoops_HGGSP _hoops_CISA _hoops_HRGR _hoops_CHCC _hoops_GRP _hoops_CIAC.
	 * _hoops_SAGAR, _hoops_GGR _hoops_RGR _hoops_RHPP _hoops_RPHSR _hoops_SPHGR _hoops_CHR _hoops_PPGP _hoops_IS _hoops_SHH _hoops_PGS.
	 * _hoops_PHGP _hoops_IH _hoops_RPHSR _hoops_SPHGR, _hoops_AA _hoops_ISAP.
	 */
	if (_hoops_SIGA->pattern == FP_SOLID) {
		/* _hoops_SSPC _hoops_PCHAI */
		/* _hoops_SSPC _hoops_RGSR _hoops_IIGR _hoops_PCSPR */
	}
	else {
		long	temp;
		char	_hoops_HGPHH[64], _hoops_HSHAI[64];

		/* _hoops_PCHAI */
		if (state->_hoops_HSPAI &&
			_hoops_IHCR->_hoops_CPA != state->_hoops_RGHAI) {
			_hoops_PCPSR (nr);
			state->_hoops_RGHAI = _hoops_IHCR->_hoops_CPA;
		}

		/* _hoops_PCSPR */
		if (_hoops_SIGA->_hoops_CPA != state->_hoops_GGHAI) {
			_hoops_AHPSR (nr, _hoops_SIGA->pattern, state);
			_hoops_ARHAI (state, _hoops_SIGA->contrast_color._hoops_PGGCR);
			state->_hoops_GGHAI = _hoops_SIGA->_hoops_CPA;
		}

		/* _hoops_HCHAI */
		_hoops_PIPAI (string, left, bottom, state);
		temp = (long)right + state->_hoops_SIPAI.x;
		Sprintf_LD (_hoops_HGPHH, "RA%D,", temp);
		temp = (long)top + state->_hoops_SIPAI.y;
		Sprintf_LD (_hoops_HSHAI, "%D;", temp);
		Sprintf_SS (string, "%s%s", _hoops_HGPHH, _hoops_HSHAI);
		_hoops_SHSRI (state, string);
	}
}


/*
 * _hoops_SRAC
 */
local void draw_dc_face (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HCPAI alter *	state = _hoops_IHSRI (nr);
	DC_Point const *			_hoops_ICHAI = points + count;
	char						string[64];

	if (nr->transform_rendition->_hoops_HCHH != null) {
		HD_Std_DC_Face (nr, count, points);
		return;
	}

	/* _hoops_PCHAI */
	if (state->_hoops_HSPAI &&
		_hoops_IHCR->_hoops_CPA != state->_hoops_RGHAI) {
		_hoops_PCPSR (nr);
		state->_hoops_RGHAI = _hoops_IHCR->_hoops_CPA;
	}

	/* _hoops_PCSPR */
	if (_hoops_SIGA->_hoops_CPA != state->_hoops_GGHAI) {
		_hoops_AHPSR (nr, _hoops_SIGA->pattern, state);

		/*
		 * _hoops_CISA _hoops_IIPH _hoops_AAPI _hoops_GRP _hoops_CGARA _hoops_HAIR;
		 * _hoops_CISA _hoops_RPHSR _hoops_AAPI _hoops_CCA _hoops_HSP _hoops_HAIR.
		 */
		if (_hoops_SIGA->pattern == FP_SOLID)
			_hoops_ARHAI (state, _hoops_SIGA->color._hoops_PGGCR);
		else
			_hoops_ARHAI (state, _hoops_SIGA->contrast_color._hoops_PGGCR);

		state->_hoops_GGHAI = _hoops_SIGA->_hoops_CPA;
	}

	/* _hoops_HCHAI */
	_hoops_PIPAI (string, points->x, points->y, state);
	Sprintf_D (string, "PM%d;", _hoops_CHPAI);
	_hoops_SHSRI (state, string);
	while ((++points) != _hoops_ICHAI) {
		_hoops_GCPAI (string, points->x, points->y, state);
	}
	Sprintf_D (string, "PM%d;FP;", _hoops_GIPAI);
	_hoops_SHSRI (state, string);
}


/*
 * _hoops_SRAC
 */
local void draw_dc_colorized_face (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*color) {
	_hoops_HHCR const	&_hoops_IHCR = nr->transform_rendition;
	_hoops_HCPAI alter				*state = _hoops_IHSRI (nr);
	DC_Point const				*_hoops_ICHAI = points + count;
	char							string[64];
	_hoops_GARSR					_hoops_ISHAI;

	if (nr->transform_rendition->_hoops_HCHH != null) {
		HD_Std_DC_Colorized_Face (nr, count, points, color);
		return;
	}

	/* _hoops_PCHAI */
	if (state->_hoops_HSPAI &&
		_hoops_IHCR->_hoops_CPA != state->_hoops_RGHAI) {
		_hoops_PCPSR (nr);
		state->_hoops_RGHAI = _hoops_IHCR->_hoops_CPA;
	}

	/* _hoops_PCSPR */
	_hoops_AHPSR (nr, FP_SOLID, state);
	_hoops_ISHAI = _hoops_CGHAI (state,
										(unsigned int)color->r/128,
										(unsigned int)color->g/128,
										(unsigned int)color->b/128);
	_hoops_ARHAI (state, _hoops_ISHAI);
	state->_hoops_GGHAI = (_hoops_GARRR)0;

	/* _hoops_HCHAI */
	_hoops_PIPAI (string, points->x, points->y, state);
	Sprintf_D (string, "PM%d;", _hoops_CHPAI);
	_hoops_SHSRI (state, string);
	while ((++points) != _hoops_ICHAI) {
		_hoops_GCPAI (string, points->x, points->y, state);
	}
	Sprintf_D (string, "PM%d;FP;", _hoops_GIPAI);
	_hoops_SHSRI (state, string);
}


/*
 * _hoops_SRAC
 */
local void draw_dc_polytriangle (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HCPAI alter *	state = _hoops_IHSRI (nr);
	char						string[64];
	int							_hoops_RRC;

	if (nr->transform_rendition->_hoops_HCHH != null) {
		HD_Std_DC_Polytriangle (nr, count, points);
		return;
	}

	/* _hoops_PCHAI */
	if (state->_hoops_HSPAI &&
		_hoops_IHCR->_hoops_CPA != state->_hoops_RGHAI) {
		_hoops_PCPSR (nr);
		state->_hoops_RGHAI = _hoops_IHCR->_hoops_CPA;
	}

	/* _hoops_PCSPR */
	if (_hoops_SIGA->_hoops_CPA != state->_hoops_GGHAI) {
		_hoops_AHPSR (nr, _hoops_SIGA->pattern, state);

		/*
		 * _hoops_CISA _hoops_IIPH _hoops_AAPI _hoops_GRP _hoops_CGARA _hoops_HAIR;
		 * _hoops_CISA _hoops_RPHSR _hoops_AAPI _hoops_CCA _hoops_HSP _hoops_HAIR.
		 */
		if (_hoops_SIGA->pattern == FP_SOLID)
			_hoops_ARHAI (state, _hoops_SIGA->color._hoops_PGGCR);
		else
			_hoops_ARHAI (state, _hoops_SIGA->contrast_color._hoops_PGGCR);

		state->_hoops_GGHAI = _hoops_SIGA->_hoops_CPA;
	}

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		/* _hoops_HCHAI */
		_hoops_PIPAI (string, points[0].x, points[0].y, state);
		Sprintf_D (string, "PM%d;", _hoops_CHPAI);
		_hoops_SHSRI (state, string);
		_hoops_GCPAI (string, points[1].x, points[1].y, state);
		_hoops_GCPAI (string, points[2].x, points[2].y, state);
		Sprintf_D (string, "PM%d;FP;", _hoops_GIPAI);
		_hoops_SHSRI (state, string);

		points += _hoops_RRC;
	}
}


/*
 * _hoops_SRAC
 */
local void draw_dc_colorized_polytriangle (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*colors,
	bool						single) {
	_hoops_HHCR const	&_hoops_IHCR = nr->transform_rendition;
	_hoops_HCPAI alter				*state = _hoops_IHSRI (nr);
	char							string[64];
	_hoops_GARSR					_hoops_ISHAI;
	int								_hoops_RRC;

	if (nr->transform_rendition->_hoops_HCHH != null) {
		HD_Std_DC_Colorized_Polytris (nr, count, points, colors, single);
		return;
	}

	/* _hoops_PCHAI */
	if (state->_hoops_HSPAI &&
		_hoops_IHCR->_hoops_CPA != state->_hoops_RGHAI) {
		_hoops_PCPSR (nr);
		state->_hoops_RGHAI = _hoops_IHCR->_hoops_CPA;
	}

	/* _hoops_PCSPR */
	_hoops_AHPSR (nr, FP_SOLID, state);
	if (single) {
		_hoops_ISHAI = _hoops_CGHAI (state,
											(unsigned int)colors->r/128,
											(unsigned int)colors->g/128,
											(unsigned int)colors->b/128);
		_hoops_ARHAI (state, _hoops_ISHAI);
	}
	state->_hoops_GGHAI = (_hoops_GARRR)0;

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		if (!single) {
			_hoops_ISHAI = _hoops_CGHAI (state,
												(unsigned int)colors->r/128,
												(unsigned int)colors->g/128,
												(unsigned int)colors->b/128);
			_hoops_ARHAI (state, _hoops_ISHAI);
		}

		/* _hoops_HCHAI */
		_hoops_PIPAI (string, points[0].x, points[0].y, state);
		Sprintf_D (string, "PM%d;", _hoops_CHPAI);
		_hoops_SHSRI (state, string);
		_hoops_GCPAI (string, points[1].x, points[1].y, state);
		_hoops_GCPAI (string, points[2].x, points[2].y, state);
		Sprintf_D (string, "PM%d;FP;", _hoops_GIPAI);
		_hoops_SHSRI (state, string);

		points += _hoops_RRC;
		if (!single)
			colors++;
	}
}


/*
 * _hoops_SRAC
 */
local void _hoops_CCCSR (
	Net_Rendition const & nr,
	DC_Point const				*start,
	DC_Point const				*end,
	int								row_bytes,
	unsigned char const				*_hoops_GAAC) {
	_hoops_HHCR const	&_hoops_IHCR = nr->transform_rendition;
	_hoops_HCPAI alter				*state = _hoops_IHSRI (nr);
	char							string[64];

	UNREFERENCED (row_bytes);

	/* _hoops_PCHAI */
	if (state->_hoops_HSPAI &&
		_hoops_IHCR->_hoops_CPA != state->_hoops_RGHAI) {
		_hoops_PCPSR (nr);
		state->_hoops_RGHAI = _hoops_IHCR->_hoops_CPA;
	}

	/* _hoops_PCSPR */
	_hoops_AIPSR (LP_SOLID, state);
	_hoops_ARHAI (state, (_hoops_GARSR)*_hoops_GAAC);
	state->_hoops_GGHAI = (_hoops_GARRR)0;

	/* _hoops_HCHAI */
	if (start->x != end->x && start->y != end->y) {
		/* _hoops_PGSA _hoops_IRS _hoops_ARRGR _hoops_CAS _hoops_RH _hoops_CSCR _hoops_CHH _hoops_HCAGR _hoops_PHHR */
		_hoops_PIPAI (string, start->x, start->y, state);
		_hoops_GCPAI (string, end->x, start->y, state);
		_hoops_GCPAI (string, end->x, end->y, state);
		_hoops_GCPAI (string, start->x, end->y, state);
		_hoops_GCPAI (string, start->x, start->y, state);
	}
	else {
		/* _hoops_PSP _hoops_IGAA _hoops_PAR _hoops_APPS, _hoops_SAHR _hoops_PGSA _hoops_IRS _hoops_III */
		_hoops_PIPAI (string, start->x, start->y, state);
		_hoops_GCPAI (string, end->x, end->y, state);
	}
}


#if 0
/*
 * _hoops_SRAC
 */
local void draw_dc_marker (
	Net_Rendition const &		nr,
	DC_Point const *			point) {
	_hoops_ICP const &	_hoops_RRGH = nr->_hoops_GSP;

	if (nr->transform_rendition->_hoops_HCHH != null) {
		HD_Std_DC_Marker (nr, point);
		return;
	}

	switch (_hoops_RRGH->symbol) {
		case MK_DOT:
		case MK_SOLID_CIRCLE:
		case MK_CIRCLE: {
			_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
			Line_Rendition const &		_hoops_HC = nr->_hoops_CSHAI;
			_hoops_HCPAI alter *	state = _hoops_IHSRI (nr);
			char						string[64];

			/* _hoops_PCHAI */
			if (state->_hoops_HSPAI &&
				_hoops_IHCR->_hoops_CPA != state->_hoops_RGHAI) {
				_hoops_PCPSR (nr);
				state->_hoops_RGHAI = _hoops_IHCR->_hoops_CPA;
			}

			/* _hoops_PCSPR */
			if (_hoops_HC->_hoops_CPA != state->_hoops_GGHAI) {
				_hoops_AIPSR (_hoops_HC->pattern, state);
				_hoops_ARHAI (state, _hoops_HC->color._hoops_PGGCR);
				state->_hoops_GGHAI = _hoops_HC->_hoops_CPA;
			}

			/* _hoops_HCHAI */
			_hoops_PIPAI (string, point->x, point->y, state);
			switch (_hoops_RRGH->symbol) {
				case MK_DOT: {
					Sprintf_D (string, "LT;FT;CT0;CI%d,5;", _hoops_RRGH->ysize/20);
					_hoops_SHSRI (state, string);
				}	break;

				case MK_SOLID_CIRCLE: {
					Sprintf_D (string, "LT;FT;CT0;WG%d,0,360,5;", _hoops_RRGH->ysize);
					_hoops_SHSRI (state, string);
				}	break;

				case MK_CIRCLE: {
					Sprintf_D (string, "LT;FT;CT0;CI%d,5;", _hoops_RRGH->ysize);
					_hoops_SHSRI (state, string);
				}	break;

				default: {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									   "unexpected marker symbol");
				}	break;
			}
		}	break;

		default: {
			HD_Std_DC_Marker (nr, point);
		}	break;
	}
}
#endif


/*
 * _hoops_SRAC
 */
local void _hoops_SCCSR (
	Display_Context const		*dc,
	unsigned int					r,
	unsigned int					g,
	unsigned int					b,
	int								index) {
	_hoops_HCPAI alter				*state = _hoops_HHSRI (dc);

	state->_hoops_AGHAI[index] = _hoops_CGHAI (state, r, g, b);
}


/*
 * _hoops_SRAC
 */
local void _hoops_RSCSR (
	_hoops_APARR alter &		_hoops_RRCI) {

	_hoops_RRCI->start_device					= start_device;
	_hoops_RRCI->stop_device						= stop_device;
	_hoops_RRCI->get_physical_info				= get_physical_info;
	_hoops_RRCI->init_picture					= init_picture;
	_hoops_RRCI->finish_picture					= finish_picture;
	_hoops_RRCI->get_outer_window				= get_outer_window;
	_hoops_RRCI->draw_dc_polyline				= draw_dc_polyline;
	_hoops_RRCI->draw_dc_face					= draw_dc_face;
	_hoops_RRCI->draw_dc_colorized_face			= draw_dc_colorized_face;
	_hoops_RRCI->draw_dc_polytriangle			= draw_dc_polytriangle;
	_hoops_RRCI->draw_dc_colorized_polytriangle	= draw_dc_colorized_polytriangle;
	_hoops_RRCI->draw_dc_rectangle				= draw_dc_rectangle;
	_hoops_RRCI->_hoops_CCCSR			= _hoops_CCCSR;
#if 0
	_hoops_RRCI->draw_dc_marker					= draw_dc_marker;
#endif
	_hoops_RRCI->_hoops_SCCSR			= _hoops_SCCSR;
}

extern "C"  bool HC_CDECL HD_HPGL_Driver (
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

#endif /* _hoops_CPPAI */

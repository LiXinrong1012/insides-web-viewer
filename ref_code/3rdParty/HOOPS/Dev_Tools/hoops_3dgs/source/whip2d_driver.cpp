/*
 * Copyright (c) 2005 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.56 2010-08-03 23:51:12 jason Exp $
 */


#ifndef WHIP2D_DRIVER

#include "hoops.h"
#include "hd_proto.h"

/*
* _hoops_APICR _hoops_PPICR
*/
extern "C" bool HC_CDECL HD_Whip2D_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR alter *			_hoops_GHRI, 
	int						request, 
	void *					request_info) 
{
	UNREFERENCED(request_info);
	return HD_No_Driver (_hoops_RIGC, _hoops_GHRI, request, "whip2d");
}

#else

#include "windows_wrapper.h"

// _hoops_PISRGR _hoops_CRRPR
#pragma warning(disable : 4290)
#pragma warning (disable: 4996)	// _hoops_HPRGR _hoops_GSGR _hoops_PSCH _hoops_GHSAR _hoops_HGPSA
#define VList DWF_VList
#include "dwfcore/File.h"
#include "dwf/package/Source.h"
#include "dwf/package/Paper.h"
#include "dwf/package/EPlotSection.h"
#include "dwf/whiptk/whip_toolkit.h"
#include "dwf/whiptk/file.h"
#include "dwf/whiptk/image.h"
#undef VList
//---]

#pragma warning(disable : 4291) // _hoops_CHARP _hoops_ASSP'_hoops_RA _hoops_SGH _hoops_RSIPH

#include "hoops.h"
#include "hd_proto.h"
#include "patterns.h"


#include <stdio.h>
#include "database.h"
#include "driver.h"
#include "filedata.h"
#include "hi_proto.h"
#include "hpserror.h"



using namespace DWFCore;
using namespace DWFToolkit;

/*
* _hoops_HSCAR _hoops_SGS _hoops_RHGSR _hoops_HCPH _hoops_IS _hoops_SRAC _hoops_SICAR
*/
struct W2DData {
	WT_File				*_hoops_HISRGR;
	/*! _hoops_AGAAH _hoops_PPR _hoops_APPS _hoops_CHR _hoops_GGR _hoops_IPIHH _hoops_ARI. */
	int	width, height;
	/*! _hoops_GAICC _hoops_GGR _hoops_PAGAI _hoops_RIR _hoops_CPIHH. */
	float				_hoops_HAP;
	Int_Rectangle	bounding_box;
	float				_hoops_IISRGR;
};


#define _hoops_CISRGR(dc)			((W2DData alter *)(dc->data))
#define _hoops_SISRGR(nr)			(_hoops_CISRGR ((nr)->_hoops_SRA))

#define _hoops_GCSRGR(_hoops_ASCSH)		((_hoops_ASCSH) * (float)(HK_Pi * 32768.0)) //((_hoops_RCSRGR) * _hoops_AIIC(180.0 / _hoops_ACSRGR)) * 65536/360
#define _hoops_PCSRGR(_hoops_RSCSH)		((_hoops_RSCSH) * (float)(65536/360))

#define DWFIO_LONG_MAX		LONG_MAX		//(2147414687)
#define DWFIO_HOOPS2LOGICAL(_hoops_HCSRGR, _hoops_ICSRGR)	

//#_hoops_PPIP _hoops_CCSRGR(_hoops_SCSRGR, _hoops_GSSRGR, _hoops_RSSRGR)	\
//{																			\
//	(_hoops_GSSRGR)._hoops_ASSRGR = (_hoops_PSSRGR)(((_hoops_GHGPR) _hoops_SCSRGR->_hoops_SISR) * ((_hoops_GHGPR)_hoops_HSSRGR) / ((_hoops_GHGPR)_hoops_RSSRGR->_hoops_ISSRGR));	\
//	(_hoops_GSSRGR)._hoops_CSSRGR = (_hoops_PSSRGR)(((_hoops_GHGPR) _hoops_SCSRGR->_hoops_HAPC) * ((_hoops_GHGPR)_hoops_HSSRGR) / ((_hoops_GHGPR)_hoops_RSSRGR->_hoops_ISSRGR));	\
//}																			\
//#_hoops_PPIP _hoops_SSSRGR(_hoops_GGGAGR, _hoops_RGGAGR, _hoops_GSSRGR, _hoops_RSSRGR)	\
//{																			\
//(_hoops_GSSRGR)._hoops_ASSRGR = (_hoops_PSSRGR)(((_hoops_GHGPR)(_hoops_GGGAGR)) * ((_hoops_GHGPR)_hoops_HSSRGR) / ((_hoops_GHGPR)_hoops_RSSRGR->_hoops_ISSRGR));	\
//(_hoops_GSSRGR)._hoops_CSSRGR = (_hoops_PSSRGR)(((_hoops_GHGPR)(_hoops_RGGAGR)) * ((_hoops_GHGPR)_hoops_HSSRGR) / ((_hoops_GHGPR)_hoops_RSSRGR->_hoops_ISSRGR));	\
//}																			\

inline void _hoops_AGGAGR(const DC_Point* _in_HT_DC_Point_, WT_Logical_Point& _hoops_PGGAGR, const W2DData* _hoops_HGGAGR)
{																			
	(_hoops_PGGAGR).m_x = (WT_Integer32)(((double) _in_HT_DC_Point_->x) * ((double)DWFIO_LONG_MAX) / ((double)_hoops_HGGAGR->_hoops_IISRGR));
	(_hoops_PGGAGR).m_y = (WT_Integer32)(((double) _in_HT_DC_Point_->y) * ((double)DWFIO_LONG_MAX) / ((double)_hoops_HGGAGR->_hoops_IISRGR));
}			

inline void XYDC2WTLP(const float _hoops_IGGAGR, const float _hoops_CGGAGR, WT_Logical_Point& _hoops_PGGAGR, const W2DData* _hoops_HGGAGR)	
{																			
	(_hoops_PGGAGR).m_x = (WT_Integer32)(((double)(_hoops_IGGAGR)) * ((double)DWFIO_LONG_MAX) / ((double)_hoops_HGGAGR->_hoops_IISRGR));	
	(_hoops_PGGAGR).m_y = (WT_Integer32)(((double)(_hoops_CGGAGR)) * ((double)DWFIO_LONG_MAX) / ((double)_hoops_HGGAGR->_hoops_IISRGR));	
}																			




#if 0

#include <stdio.h>


#define _hoops_ACRSC				256
#define _hoops_PCRSC				4

#define _hoops_HCRSC					3.0
#define _hoops_ICRSC							30
#define _hoops_CCRSC							42
#define _hoops_SCRSC							18
#define _hoops_GSRSC							24
#define _hoops_RSRSC							6
#define _hoops_ASRSC							4
#define _hoops_PSRSC							12
#define _hoops_HSRSC							8

#define _hoops_IHPAI				80
#define _hoops_ISRSC					256
#define _hoops_CSRSC					512

#define _hoops_SSRSC 4

local bool _hoops_GGASC (Display_Context alter *dc);

#define _hoops_RGASC			0x00000001
#define _hoops_AGASC		0x00000002
#define _hoops_PGASC	0x00000004
#define _hoops_HGASC	0x00000008
#define _hoops_IGASC	0
#define _hoops_CGASC 1
#define _hoops_SGASC	2

struct _hoops_GRASC {
	int					id;
	_hoops_HCRPR const		name;
};

struct _hoops_RRASC {
	char						family_name [_hoops_ISRSC];
	char						_hoops_RRHRI [_hoops_CSRSC];
	short						_hoops_ARASC;
	_hoops_RRASC alter *			next;
};

struct _hoops_PRASC {
	_hoops_GARRR					_hoops_CPA;
	_hoops_PRASC alter *	next;
};

/*
 * _hoops_RCPA _hoops_GRPR _hoops_RH _hoops_PGCR _hoops_HAGH _hoops_IPISR.
 * _hoops_AGAH _hoops_GSSS _hoops_GHAGI _hoops_HHHPP 1 _hoops_HIS _hoops_IGAA _hoops_IIGR _hoops_HRASC _hoops_HPRGR _hoops_IPISR
 * _hoops_GRS _hoops_RRP _hoops_IS _hoops_SHH _hoops_SPSPR _hoops_RPP _hoops_SCH _hoops_HRGR > 128
 */

#define		 _hoops_IRASC	0
#define		 _hoops_CRASC			1


#define		 _hoops_SRASC				0
#define		 _hoops_GAASC		1
#define		 _hoops_RAASC				2
#define		 _hoops_AAASC				3
#define		 _hoops_PAASC		4
#define		 _hoops_HAASC				5
#define		 _hoops_IAASC			6
#define		 _hoops_CAASC					7
#define		 _hoops_SAASC			8
#define		 _hoops_GPASC			9
#define		 _hoops_RPASC		10
#define		 _hoops_APASC	11
#define		 _hoops_PPASC				12
#define		 _hoops_HPASC					13
#define		 _hoops_IPASC				14
#define		 _hoops_CPASC				15
#define		 _hoops_SPASC				16
#define		 _hoops_GHASC				17
#define		 _hoops_RHASC				18
#define		 _hoops_AHASC		19
#define		 _hoops_PHASC		20
#define		 _hoops_HHASC		21
#define		 _hoops_IHASC		22
#define		 _hoops_CHASC			23
#define		 _hoops_SHASC			24
#define		 _hoops_GIASC		25
#define		 _hoops_RIASC			26
#define		 _hoops_AIASC		27


/*
 * _hoops_ACGR _hoops_RH _hoops_AAPSC _hoops_HII _hoops_PCCP _hoops_PAPSC _hoops_RGHR
 */

local int _hoops_HAPSC (
	_hoops_GRASC const			*table,
	char alter				* alter *_hoops_IAPSC) {
	char alter				*_hoops_CAPSC = *_hoops_IAPSC;

	while (*_hoops_CAPSC == '\t' || *_hoops_CAPSC == ' ') ++_hoops_CAPSC;

	_hoops_RGGA (table->id == _hoops_SRASC)
		if (_hoops_GPPSA (table->name.text, table->name.length, _hoops_CAPSC))
			break;
		else
			++table;

/*	  _hoops_RPP (_hoops_GASR->_hoops_CRSRR == _hoops_SAPSC) _hoops_IPRPR ("??? %_hoops_GRI\_hoops_ACHP", _hoops_GPPSC); */

	*_hoops_IAPSC = _hoops_CAPSC + table->name.length;
	return table->id;
}

/*
 * _hoops_AHGHR _hoops_RH _hoops_HRCSR _hoops_PCRIP _hoops_RSIRR _hoops_PPR _hoops_RH _hoops_HRCSR _hoops_GASR, _hoops_IRS _hoops_PAIP _hoops_GGR
 * _hoops_RH _hoops_SGGAGR _hoops_RHPP'_hoops_GRI _hoops_RHSAR _hoops_PIH , _hoops_SSS _hoops_RH _hoops_RSHCR
 * _hoops_IHIR _hoops_RGHR _hoops_RSIRR. _hoops_IPCP _hoops_PIRPR _hoops_HRGR _hoops_IGI _hoops_GGR _hoops_CACPC.
 */

local int _hoops_APPSC (
	char const			*family_name,
	_hoops_RRASC const	*_hoops_GPPIR,
	char alter			*_hoops_RRHRI,
	short alter			*_hoops_ARASC) {

	_hoops_RRASC const	*_hoops_PPPSC = _hoops_GPPIR;

	if (_hoops_PPPSC == null) {
		return 0;
	}
	else {
		while ((_hoops_PPPSC->next != null) &&
			(!_hoops_AGGR (family_name, _hoops_PPPSC->family_name))) {
			_hoops_PPPSC = _hoops_PPPSC->next;
		}
		_hoops_AAHR (_hoops_PPPSC->_hoops_RRHRI, _hoops_RRHRI);
		*_hoops_ARASC = _hoops_PPPSC->_hoops_ARASC;
		return 1;
	}
}

/*
 * _hoops_RGPA _hoops_SPR _hoops_PSAI _hoops_IIGR _hoops_PCRIP _hoops_HRCSR _hoops_RSIRR _hoops_PPR _hoops_RH _hoops_IHIR _hoops_PAPSC _hoops_CAIAH _hoops_IS
 * _hoops_RH _hoops_SGGAGR _hoops_RHPP'_hoops_GRI _hoops_RHSAR _hoops_PIH.
 */

local void _hoops_HPPSC (
	char const			*family_name,
	char const			*_hoops_RRHRI,
	short const			*_hoops_ARASC,
	W2DData alter		*state) {
	_hoops_RRASC alter	*_hoops_PPPSC = state->_hoops_GPPIR;

	if (_hoops_PPPSC == null) {
		ALLOC (state->_hoops_GPPIR, _hoops_RRASC);
		_hoops_AAHR (family_name, state->_hoops_GPPIR->family_name);
		_hoops_AAHR (_hoops_RRHRI, state->_hoops_GPPIR->_hoops_RRHRI);
		state->_hoops_GPPIR->_hoops_ARASC = *_hoops_ARASC;
		state->_hoops_GPPIR->next = null;
	}
	else {
		while (_hoops_PPPSC->next != null) _hoops_PPPSC = _hoops_PPPSC->next;
		ALLOC (_hoops_PPPSC->next, _hoops_RRASC);
		_hoops_PPPSC = _hoops_PPPSC->next;
		_hoops_AAHR (family_name, _hoops_PPPSC->family_name);
		_hoops_AAHR (_hoops_RRHRI, _hoops_PPPSC->_hoops_RRHRI);
		_hoops_PPPSC->_hoops_ARASC = *_hoops_ARASC;
		_hoops_PPPSC->next = null;
	}
}


local void _hoops_CSASR (
	W2DData alter			*state,
	Driver_Color const	*color) {
	FILE alter				*fp = state->fp;

	if (state->_hoops_PRGGH) return;

	if (state->_hoops_ARSRI != *color) {
		if (color->_hoops_HRIR.r == color->_hoops_HRIR.g &&
				color->_hoops_HRIR.r == color->_hoops_HRIR.b) {
			fprintf (fp, "%.2f SG ",
						(int) color->_hoops_HRIR.r / (float) _hoops_ACRSC);
			_hoops_AGPSC (state);
		}
		else {
			fprintf (fp, "%.2f %.2f %.2f SRGB ",
						(int) color->_hoops_HRIR.r / (float) _hoops_ACRSC,
						(int) color->_hoops_HRIR.g / (float) _hoops_ACRSC,
						(int) color->_hoops_HRIR.b / (float) _hoops_ACRSC);
			_hoops_AGPSC (state);
		}
		state->_hoops_ARSRI = *color;
	}
}


local void _hoops_IPPSC (
	W2DData alter	*state,
	RGBAS32 const	*color) {
	FILE alter		*fp = state->fp;

	if (state->_hoops_PRGGH) return;

	if (state->_hoops_ARSRI != color->_hoops_SRRCI) {
		if (color->r == color->g && color->r == color->b) {
			fprintf (fp, "%.2f SG ",
						(int) color->r / (float) _hoops_ACRSC);
			_hoops_AGPSC (state);
		}
		else {
			fprintf (fp, "%.2f %.2f %.2f SRGB ",
						(int) color->r / (float) _hoops_ACRSC,
						(int) color->g / (float) _hoops_ACRSC,
						(int) color->b / (float) _hoops_ACRSC);
			_hoops_AGPSC (state);
		}
		state->_hoops_ARSRI = color->_hoops_SRRCI;
	}
}



local void _hoops_SIPSC (
	W2DData alter	*state) {
	FILE alter		*fp = state->fp;

	if (state->_hoops_PRGGH) return;

	_hoops_IGPSC ("/SPL {%.2f LW [] 0 SD NP} bind def\n", _hoops_HCRSC);

	_hoops_ACIAI ("/HBARS {/I exch def /H exch def /W exch def /Y exch def\n");
	_hoops_ACIAI (" /X exch def SPL 0 I H {Y add X exch MT W 0 RLT} for SK} bind def\n");
	_hoops_ACIAI ("/VBARS {/I exch def /H exch def /W exch def /Y exch def\n");
	_hoops_ACIAI (" /X exch def SPL 0 I W {X add Y MT 0 H RLT} for SK} bind def\n");
	_hoops_ACIAI ("/CROSSH {5 copy HBARS VBARS} bind def\n");
	_hoops_ACIAI ("/SLANTR {/I exch def /Max exch def /Y exch def pop /X exch def SPL\n");
	_hoops_ACIAI (" 0 I Max {/D exch def X Y D sub MT X D add Y LT} for SK} bind def\n");
	_hoops_ACIAI ("/SLANTL {/I exch def /Max exch def pop /Y exch def /X exch def SPL\n");
	_hoops_ACIAI (" 0 I Max {/D exch def X D add Y MT X Y D add LT} for SK} bind def\n");
	_hoops_ACIAI ("/DIAMONDS {5 copy SLANTR SLANTL} bind def\n");
	_hoops_ACIAI ("/SQUARE {/PROC exch def /SIZE exch def /Y1 exch def /X1 exch def\n");
	_hoops_ACIAI (" /X2 {X1 SIZE add} def /Y2 {Y1 SIZE add} def\n");
	_hoops_ACIAI (" SPL X1 Y1 MT X1 Y2 LT X2 Y2 LT X2 Y1 LT CP PROC} bind def\n");
	_hoops_ACIAI ("/SQDOTS {/SIZE exch def /I exch def /H exch def /W exch def\n");
	_hoops_ACIAI (" /Y exch def /X exch def 0 I H {Y add /YLEVEL exch def\n");
	_hoops_ACIAI (" 0 I W {X add YLEVEL SIZE {FL} SQUARE} for} for} bind def\n");
	_hoops_ACIAI ("/CHECKBRD {/SIZE exch def /I exch def /H exch def /W exch def\n");
	_hoops_ACIAI (" /Y exch def /X exch def 0 I H {Y add /YLEVEL exch def\n");
	_hoops_ACIAI (" 0 I W {X add YLEVEL SIZE {SK} SQUARE} for} for} bind def\n");

	/* _hoops_SPHII _hoops_IS _hoops_GCPSC:
	**	_hoops_PHAA _hoops_GAHPC _hoops_ISPH _hoops_IS _hoops_SHH _hoops_IIPH:
	**			_hoops_RCPSC, _hoops_ACPSC, _hoops_IGAA, _hoops_APPS,
	**	_hoops_CPR _hoops_GAHPC _hoops_SGGGH _hoops_IIGR _hoops_RH _hoops_HSGP:
	**			_hoops_PCPSC, _hoops_HCPSC.
	**	_hoops_ICPSC _hoops_PGAP _hoops_HSGP _hoops_IS _hoops_SGH:
	**			_hoops_CCPSC
	*/
	_hoops_ACIAI ("/USER_PATTERN {/USER_TILE exch cvx def /SZY exch def /SZX exch def\n");
	_hoops_ACIAI (" /H exch def /W exch def /Y exch def /X exch def\n");
	_hoops_ACIAI (" 0 SZY H {Y add /YLEVEL exch def\n");
	_hoops_ACIAI ("	 0 SZX W {X add YLEVEL USER_TILE} for} for} bind def\n");
}

local void _hoops_SCPSC (
	W2DData alter	*state) {
	FILE alter		*fp = state->fp;

	if (state->_hoops_PRGGH) return;
	fprintf(fp, "/img_rle 4 string def\n");
	fprintf (fp, "/img_pixels 768 string def\n");
	_hoops_AGPSC (state);

	/* _hoops_IRS _hoops_HICRR _hoops_IH _hoops_GSPSC */
	fprintf (fp, "/IMGRDRLE {\n");
	fprintf (fp, "	currentfile img_rle readhexstring pop pop\n");
	fprintf (fp, "	2 dict begin\n");
	fprintf (fp, "	  /nbytes img_rle 0 get 3 mul def\n");
	fprintf (fp, "	  /color img_rle 1 3 getinterval def\n");
	fprintf (fp, "	  0 3 nbytes {img_pixels exch color putinterval} for\n");
	fprintf (fp, "	  img_pixels 0 nbytes getinterval\n");
	fprintf (fp, "	end\n");
	fprintf (fp, "} bind def\n");
	_hoops_AGPSC (state);

	/* _hoops_IRS _hoops_SGGAGR _hoops_RIGR _hoops_IS _hoops_PGSA _hoops_IRS _hoops_ARAS-_hoops_SPCC _hoops_PIGAI _hoops_CSCR */
	fprintf (fp, "/IRLE { GS  4 dict begin\n");
	fprintf (fp, "	/height exch def  /width exch def");
	fprintf (fp, "	/y exch def	 /x exch def\n");
	fprintf (fp, "	x .5 sub y .5 sub translate width height scale\n");
	fprintf (fp, "	width height 8 [width 0 0 height neg 0 height]\n");
	fprintf (fp, "	{IMGRDRLE} false 3 colorimage");
	fprintf (fp, "	end GR } bind def\n");
	_hoops_AGPSC (state);

	/* _hoops_IRS _hoops_SGGAGR _hoops_RIGR _hoops_IS _hoops_PGSA _hoops_PCCP _hoops_ARAS-_hoops_SPCC _hoops_PIGAI _hoops_CGHSI */
	fprintf (fp, "/SRLE { GS  3 dict begin\n");
	fprintf (fp, "	/width exch def	 /y exch def  /x exch def\n");
	fprintf (fp, "	x .5 sub y .5 sub translate width 1 scale");
	fprintf (fp, "	width 1 8 [width 0 0 -1 0 1]\n");
	fprintf (fp, "	{IMGRDRLE} false 3 colorimage");
	fprintf (fp, "	end GR } bind def\n");
	_hoops_AGPSC (state);

	/* _hoops_IRS _hoops_SGGAGR _hoops_RIGR _hoops_IS _hoops_PGSA _hoops_PCCP _hoops_CCRRP _hoops_CSCR */
	fprintf (fp, "/IMG { GS	 5 dict begin\n");
	fprintf (fp, "	/height exch def  /width exch def");
	fprintf (fp, "	/y exch def	 /x exch def\n");
	fprintf (fp, "	/imgbuf width string def\n");
	fprintf (fp, "	x .5 sub y .5 sub translate width height scale\n");
	fprintf (fp, "	width height 8 [width 0 0 height neg 0 height]\n");
	fprintf (fp, "	{currentfile imgbuf readhexstring pop} false 3 colorimage");
	fprintf (fp, "	end GR } bind def\n");
	_hoops_AGPSC (state);

	/* _hoops_IRS _hoops_SGGAGR _hoops_RIGR _hoops_IS _hoops_PGSA _hoops_IRS _hoops_RSRA _hoops_AIR */
	fprintf (fp, "/PIX { GS	 2 dict begin");
	fprintf (fp, "	/y exch def	 /x exch def  /imgbuf 1 string def\n");
	fprintf (fp, "	x .5 sub y .5 sub translate	 1 1 8 [1 0 0 1 neg 0 1]\n");
	fprintf (fp, "	{currentfile imgbuf readhexstring pop} false 3 colorimage");
	fprintf (fp, "	end GR } bind def\n");
	_hoops_AGPSC (state);
}

local void _hoops_CAHSC (FILE alter * fp,
					  unsigned int tag, unsigned int type,
					  unsigned long len, unsigned long offset) {
	_hoops_AGHSC	_hoops_SAHSC;

	_hoops_SAHSC.tag = tag;
	_hoops_SAHSC._hoops_HCAAR = type;
	_hoops_SAHSC.length = len;
	_hoops_SAHSC.offset = offset;

	_hoops_HRPSC (_hoops_SAHSC.tag);
	_hoops_HRPSC (_hoops_SAHSC._hoops_HCAAR);
	_hoops_HRPSC (_hoops_SAHSC.length);
	_hoops_HRPSC (_hoops_SAHSC.offset);

	fwrite (&_hoops_SAHSC, 1, sizeof (_hoops_AGHSC), fp);
}



local void free_outer_window (
	Display_Context const	*dc) {
	W2DData alter				*state = _hoops_CISRGR (dc);

	state->_hoops_ASASC = false;
}



local void finish_picture (
	Net_Rendition const		&nr,
	bool					swap_buffers) {
	Display_Context const	*dc = nr->_hoops_SRA;
	W2DData alter				*state = _hoops_CISRGR (dc);
	FILE alter					*fp = state->fp;

	UNREFERENCED (swap_buffers);

	if (!BIT(dc->flags, _hoops_SAISR) || state->_hoops_PRGGH) return;

	_hoops_ACIAI ("GR R SP\n");

	fflush (fp);

	state->_hoops_GSASC = state->_hoops_SCASC - 1;
}


local void _hoops_RIHSC (
	Net_Rendition const & nr) {
	_hoops_HHCR const	&_hoops_IHCR = nr->transform_rendition;
	Display_Context const		*dc = nr->_hoops_SRA;
	W2DData alter					*state = _hoops_CISRGR (dc);
	FILE alter						*fp = state->fp;
	_hoops_PACIR					_hoops_RCHS;

	if (state->_hoops_PRGGH) return;

	/* _hoops_ARP _hoops_CCAH _hoops_CIHH _hoops_PRCH */
	if (BIT (dc->options._hoops_IRARR, _hoops_RGASC))
		_hoops_ACIAI ("%% new clipping\n");

	_hoops_ACIAI ("GR GS\n");

	_hoops_RCHS.left = (float) _hoops_IHCR->_hoops_AGAA.left - 0.5f;
	_hoops_RCHS.right = (float) _hoops_IHCR->_hoops_AGAA.right + 0.5f;
	_hoops_RCHS.bottom = (float) _hoops_IHCR->_hoops_AGAA.bottom - 0.5f;
	_hoops_RCHS.top = (float) _hoops_IHCR->_hoops_AGAA.top + 0.5f;

	fprintf (fp, "NP %.1f %.1f MT %.1f %.1f LT %.1f %.1f LT %.1f %.1f LT CP CL\n",
		_hoops_RCHS.left, _hoops_RCHS.bottom, _hoops_RCHS.left, _hoops_RCHS.top,
		_hoops_RCHS.right, _hoops_RCHS.top, _hoops_RCHS.right, _hoops_RCHS.bottom);	 _hoops_AGPSC (state);

	if (_hoops_IHCR->_hoops_HCHH != null) {
		_hoops_ASHH const *	_hoops_CRAIR = _hoops_IHCR->_hoops_HCHH;
		int								i;

		fprintf (fp, "NP %.1f %.1f MT", _hoops_CRAIR->points[0].x, _hoops_CRAIR->points[0].y);
			 _hoops_AGPSC (state);
		for (i=1; i<_hoops_CRAIR->count; i++) {
			fprintf (fp, " %.1f %.1f LT", _hoops_CRAIR->points[i].x, _hoops_CRAIR->points[i].y);
				 _hoops_AGPSC (state);
			if (i%4 == 3)
				_hoops_ACIAI ("\n");
		}

		_hoops_ACIAI (" CP CL\n");
	}

	state->_hoops_RPICC = _hoops_IHCR->_hoops_CPA;

	/* _hoops_HIAP _hoops_RH _hoops_HCISR _hoops_PIAP	 */
	state->_hoops_ARSRI = _hoops_IAASP;
	state->_hoops_CRSRI = 0;
	state->_hoops_ICASC = -1;
	state->_hoops_CCASC = -1;
	state->_hoops_HCASC = -1.0f;
	state->_hoops_ACASC = -1;
}


local void _hoops_AIHSC (
	Net_Rendition const &	nr) {
	Line_Rendition const &	_hoops_HC = nr->_hoops_AHP;
	Display_Context const	*dc = nr->_hoops_SRA;
	W2DData alter				*state = _hoops_CISRGR (dc);
	FILE alter					*fp = state->fp;
	unsigned int	i;

	if (state->_hoops_PRGGH) return;

	if (BIT (dc->options._hoops_IRARR, _hoops_RGASC))
		_hoops_ACIAI ("%% new line rendition\n");

	if (state->_hoops_CRSRI != _hoops_HC->line_style) {
		int const		*_hoops_CAPSC;

		_hoops_CAPSC = _hoops_HC->line_style->_hoops_GHISR[0].pattern;
		state->_hoops_CRSRI = _hoops_HC->line_style;

		_hoops_ACIAI ("[");
		for (i=0;i<_hoops_HC->line_style->_hoops_GHISR[0]._hoops_RHISR;i++) {
			_hoops_IGPSC ("%d", (int) (*_hoops_CAPSC++ * state->_hoops_GRGAGR));
			if (i != _hoops_HC->line_style->_hoops_GHISR[0]._hoops_RHISR) _hoops_ACIAI (" ");
		}
		_hoops_ACIAI ("] 0 SD ");

	}
	if (state->_hoops_ICASC != (_hoops_HC->style & LCAP_MASK) >> LCAP_SHIFT) {
		state->_hoops_ICASC = (_hoops_HC->style & LCAP_MASK) >> LCAP_SHIFT;

		_hoops_IGPSC ("%d LC ", state->_hoops_ICASC);
	}
	if (state->_hoops_CCASC != (_hoops_HC->style & LJOIN_MASK) >> LJOIN_SHIFT) {
		state->_hoops_CCASC = (_hoops_HC->style & LJOIN_MASK) >> LJOIN_SHIFT;

		_hoops_IGPSC ("%d LJ ", state->_hoops_CCASC);
	}

	_hoops_CSASR (state, &_hoops_HC->color);

	if (state->_hoops_PRGGH) return;

	if (state->_hoops_HCASC != (float) _hoops_HC->weight) {
		state->_hoops_HCASC = (float) _hoops_HC->weight;
		_hoops_IGPSC ("%.2f LW", (float) _hoops_HC->weight);
	}

	_hoops_ACIAI ("\n");

	state->_hoops_ACASC = _hoops_HC->_hoops_CPA;
	state->_hoops_GGPSC = true;
}


/*
 * * _hoops_SRAC
 * */
local void draw_window (
		Net_Rendition const		&nr,
		Int_Rectangle const		*extent) {

		_hoops_CGRA const	&_hoops_SGRA = nr->_hoops_SAIR;
		Display_Context const	*dc = nr->_hoops_SRA;
		W2DData alter				*state = _hoops_CISRGR (dc);
		Image const				*image = null;
		FILE alter					*fp = state->fp;
		_hoops_RCR					*_hoops_IICSR = null;
		_hoops_CPAIR				_hoops_CICSR;

		float _hoops_PRPHA;

		if (_hoops_SGRA->_hoops_PGPH != null || _hoops_SGRA->_hoops_SICSR == null) {
				HD_Standard_Draw_Window(nr, extent);
				return;
		}

		if (nr->_hoops_GCCSR->count > 0) {
			_hoops_CICSR.textures = nr->_hoops_GCCSR->textures;
			_hoops_CICSR.keys = nr->_hoops_GCCSR->keys;
			_hoops_CICSR.count = nr->_hoops_GCCSR->count;
		}else{
			_hoops_CICSR.textures = 0;
			_hoops_CICSR.keys = 0;
			_hoops_CICSR.count = 0;
		}
		
		if ((_hoops_IICSR = HI_Activate_Texture((_hoops_RCR alter *)_hoops_SGRA->_hoops_SICSR, &_hoops_CICSR, false))) {
			image = _hoops_IICSR->image;
		}

		if (_hoops_IICSR == null || BIT(_hoops_IICSR->flags, _hoops_AIA)) {
			HD_Standard_Draw_Window(nr, extent);
			return;
		}

		_hoops_PRPHA = (float)(extent->right-extent->left)/(float)(image->width-1); 


		fprintf(fp,"GS %f dup scale 1.5 neg dup translate GS\n", _hoops_PRPHA);

		_hoops_AGPSC (state);

		HD_Standard_Draw_Window(nr, extent);

		_hoops_ACIAI("GR GR\n");

		if (_hoops_IICSR)
					_hoops_HPRH(_hoops_IICSR);
}

/************************************/

#endif

local void _hoops_RRGAGR (Net_Rendition const & nr) 
{
	 Display_Context const	*dc = nr->_hoops_SRA;
	 W2DData alter				*_hoops_ICSRGR = _hoops_CISRGR (dc);

	 if (!BIT(dc->flags, _hoops_SAISR)) 
		 return;

	 _hoops_ICSRGR->bounding_box.left		= (int)(dc->_hoops_RHPGA.left);
	 _hoops_ICSRGR->bounding_box.right	= (int)(dc->_hoops_RHPGA.right);
	 _hoops_ICSRGR->bounding_box.bottom	= (int)(dc->_hoops_RHPGA.bottom);
	 _hoops_ICSRGR->bounding_box.top		= (int)(dc->_hoops_RHPGA.top);
//
//	 // _hoops_PS _hoops_CSRA _hoops_RH _hoops_AGAH _hoops_SHCA _hoops_PCRR _hoops_IS _hoops_RH _hoops_ARGAGR _hoops_SICHR _hoops_GHARR. _hoops_HGI _hoops_PSAAA _hoops_IHHH _hoops_SRCH 
//	 // _hoops_RH _hoops_GPPS _hoops_PRGAGR. _hoops_IPCP _hoops_IRRPI _hoops_GHARR _hoops_HRGR _hoops_GRSSR _hoops_GAR _hoops_CAPP
//	 //----------------------------------------------------------------------------------
//	 //_hoops_IGGPH _hoops_IIGR _hoops_RH _hoops_PCRR _hoops_CHIA _hoops_GGR _hoops_HRGAGR! _hoops_PIH _hoops_CHR _hoops_GGR _hoops_SICHR _hoops_PCRR, 
//	 //_hoops_GAR _hoops_HISIP _hoops_IS _hoops_SHPR _hoops_PAR _hoops_SISS _hoops_PCRR. _hoops_IRRPI _hoops_PCRR _hoops_CHR _hoops_CHIA 
//	 //_hoops_GAR _hoops_RH _hoops_RPRHR _hoops_CCIR _hoops_IIGR 32-_hoops_IGRH _hoops_CPCSH _hoops_CAIPR (31 _hoops_SIH _hoops_IIGR _hoops_GPPS) _hoops_CCA _hoops_IRS 
//	 //_hoops_RPRI _hoops_CCIR _hoops_HII 0 _hoops_IS _hoops_IRS _hoops_CIAS _hoops_IIGR 2,147,483,647 (231 - 1). 
//	 //_hoops_PAGAR, _hoops_IRS _hoops_HRGAGR! _hoops_PIH _hoops_GIAR _hoops_CCRPR _hoops_CGH _hoops_CSRA _hoops_RH _hoops_RSHRC _hoops_PICA 
//	 //_hoops_IIGR _hoops_RH _hoops_IRGAGR _hoops_SGS _hoops_HRGR _hoops_IHGS _hoops_GCSS _hoops_HIS _hoops_SGS _hoops_IRS _hoops_CHPP _hoops_PRGGR _hoops_IIGR _hoops_RGR 31-_hoops_IGRH 
//	 //_hoops_CCIR _hoops_HRGR _hoops_IGI. _hoops_HGI _hoops_IHIGR _hoops_IRS _hoops_HRGAGR! _hoops_PIH _hoops_GPS _hoops_CCRPR _hoops_IS _hoops_CSRA _hoops_RH _hoops_IRGAGR 
//	 //_hoops_IH _hoops_RH _hoops_PIASR _hoops_AIRI _hoops_PAR _hoops_IRS _hoops_IPSP _hoops_IS _hoops_GRCPC _hoops_GGR _hoops_GPP _hoops_RH _hoops_ASCA _hoops_CCA _hoops_CHIS _hoops_GPPS 
//	 //_hoops_IS _hoops_SRGS _hoops_RCRAR _hoops_RCAHR.
//
//		// _hoops_CRGAGR _hoops_SRGAGR _hoops_CIHGS-_hoops_RACIR _hoops_GAGAGR
//		//	 _hoops_RAGAGR-_hoops_PGCR-_hoops_IGRH _hoops_HHIPR _hoops_HSH _hoops_CHR _hoops_IGI _hoops_PGGA _hoops_SSIA _hoops_ASSS _hoops_IH _hoops_RRI _hoops_GPPS _hoops_PPR 
//		//	 _hoops_RRPAR _hoops_CGGGA _hoops_ACHPR _hoops_HSAR 32-_hoops_IGRH _hoops_SAPS-_hoops_PPSR _hoops_HSH. _hoops_SRIGP _hoops_IIGR _hoops_IRS _hoops_SAPS-_hoops_PPSR 
//		//	 _hoops_PHI?_hoops_GRI 32 _hoops_SIH, 8 _hoops_SIH _hoops_CHR _hoops_IGI _hoops_IS _hoops_ASH _hoops_RRASR _hoops_PPR _hoops_HRASR _hoops_HPHS, _hoops_PHGHR _hoops_RGAR 24 _hoops_SIH 
//		//	 _hoops_IIGR _hoops_IHPR _hoops_GPPS (_hoops_HAR _hoops_IS _hoops_SHH _hoops_PCCGS _hoops_CCA _hoops_IRS _hoops_SAPS _hoops_PPSR _hoops_PHI?_hoops_GRI _hoops_CHPP _hoops_CCIR).
//
//		//	 _hoops_CGP _hoops_IRS _hoops_ARCR _hoops_AAPR _hoops_CHCC _hoops_CCA _hoops_HRGAGR! _hoops_PIH?_hoops_GRI 31-_hoops_IGRH _hoops_HHIPR _hoops_PCRR, _hoops_IAPR 
//		//	 21,000 _hoops_AAGAGR (>12,000 _hoops_PAGAGR) _hoops_IIGR _hoops_GIRA _hoops_HHS _hoops_SHH _hoops_HAGAGR _hoops_RHRI _hoops_ISHP _hoops_IS 1-_hoops_SPIHH 
//		//	 _hoops_IAGAGR. _hoops_CGP 32-_hoops_IGRH _hoops_SAPS-_hoops_PPSR _hoops_PCRR _hoops_AAPR _hoops_IGI, _hoops_RGAR 167 _hoops_AAGAGR (100 _hoops_PAGAGR) 
//		//	 _hoops_HHS _hoops_SHH _hoops_RHRI _hoops_IS _hoops_RGR _hoops_PAPA _hoops_IIGR _hoops_AHSIR. _hoops_HPGHR _hoops_CGARA, _hoops_CAGAGR _hoops_RAIA 64 _hoops_IGRH _hoops_GHGPR-_hoops_PCPP 
//		//	 _hoops_SAPS _hoops_PPSR _hoops_PCRR _hoops_IS _hoops_GRGPR _hoops_RGR _hoops_RCSRR, _hoops_CCA _hoops_IRS _hoops_ARGR 52 _hoops_SIH _hoops_IIGR _hoops_GPPS _hoops_PPR 
//		//	 _hoops_PCCP _hoops_SAGAGR _hoops_CCIR. _hoops_HSRR _hoops_RH _hoops_RRI _hoops_PPAC _hoops_AHAR _hoops_IIGR _hoops_APRAA _hoops_PCCP _hoops_GPGAGR _hoops_SGRAI, _hoops_HRGAGR! 
//		//	 _hoops_PIH'_hoops_GRI 31 _hoops_SIH _hoops_IIGR _hoops_GPPS _hoops_CHR _hoops_RRI _hoops_HSAR _hoops_HPARS. 
//	 //----------------------------------------------------------------------------------
//
	 double _hoops_RPGAGR = abs(dc->_hoops_RHPGA.right - dc->_hoops_RHPGA.left);
	 if (_hoops_RPGAGR == 0.0f)
		 _hoops_RPGAGR = 1.0f;

	 double _hoops_APGAGR = abs(dc->_hoops_RHPGA.top - dc->_hoops_RHPGA.bottom);
	 if (_hoops_APGAGR == 0.0f)
		 _hoops_APGAGR = 1.0f;
//
//	 // _hoops_RHHSR _hoops_RH _hoops_PPGAGR - _hoops_SGH _hoops_RH _hoops_AASC _hoops_IIGR _hoops_PGCR _hoops_CCPA
//	 _hoops_RPP (_hoops_HPGAGR < _hoops_IPGAGR)
//	 	_hoops_CPGAGR->_hoops_ISSRGR = _hoops_HPGAGR;
//	 _hoops_SHS
//		 _hoops_CPGAGR->_hoops_ISSRGR = _hoops_IPGAGR;
}

/*
* _hoops_SRAC
*/
local void _hoops_SPGAGR (
	Net_Rendition const	  &nr,
	Int_Rectangle const		*extent) 
{
	W2DData alter 	  *_hoops_ICSRGR = _hoops_SISRGR (nr);
	_hoops_CGRA const &_hoops_SGRA = nr->_hoops_SAIR;
	_hoops_CPAIR		_hoops_CICSR;
	Image const		*image = null;
	_hoops_RCR		  *_hoops_IICSR = null;

	if (_hoops_SGRA->_hoops_SICSR == null) 
	{
		HD_Standard_Draw_Window(nr, extent); /* _hoops_IIS _hoops_CSPH _hoops_ARRGR _hoops_RGHH _hoops_SCH */
		return;
	}

	if (nr->_hoops_GCCSR->count > 0) 
	{
		_hoops_CICSR.textures = nr->_hoops_GCCSR->textures;
		_hoops_CICSR.keys = nr->_hoops_GCCSR->keys;
		_hoops_CICSR.count = nr->_hoops_GCCSR->count;
	}
	else
	{
		_hoops_CICSR.textures = 0;
		_hoops_CICSR.keys = 0;
		_hoops_CICSR.count = 0;
	}
	if (BIT(_hoops_SGRA->_hoops_SICSR->flags, TF_UNEVALUATED))
	{
		if ((_hoops_IICSR = HI_Activate_Texture((_hoops_RCR alter *)_hoops_SGRA->_hoops_SICSR, &_hoops_CICSR, false))) {
			image = _hoops_IICSR->image;
		}else{
			image = null;
		}
	}
	else
	{
		image = _hoops_SGRA->_hoops_SICSR->image;
	}
	
	static WT_Integer32   _hoops_GHGAGR = 1;
	WT_Unsigned_Integer16 _hoops_RHGAGR    = image->height;
	WT_Unsigned_Integer16 _hoops_AHGAGR = image->width;
	WT_Color_Map const *  _hoops_PHGAGR = 0;
	WT_Logical_Point _hoops_HHGAGR, _hoops_IHGAGR;
	XYDC2WTLP(extent->left, extent->bottom, _hoops_HHGAGR, _hoops_ICSRGR);
	XYDC2WTLP(extent->right, extent->top, _hoops_IHGAGR, _hoops_ICSRGR);

	WT_Integer32 _hoops_CHGAGR;
	WT_Image::WT_Image_Format _hoops_SHGAGR;

	if (image->format == _hoops_HHGH)
	{
		_hoops_SHGAGR = WT_Image::RGB;
		_hoops_CHGAGR = _hoops_RHGAGR * _hoops_AHGAGR * 3;
	}
	else if (image->format == Image_RGBA32)
	{
		_hoops_SHGAGR = WT_Image::RGBA;
		_hoops_CHGAGR = _hoops_RHGAGR * _hoops_AHGAGR * 4;
	}
	else
	{
		HD_Standard_Draw_Window(nr, extent); /* _hoops_IIS _hoops_CSPH _hoops_ARRGR _hoops_RGHH _hoops_SCH */
		if (_hoops_IICSR)
			_hoops_HPRH(_hoops_IICSR);
		return;
	}

	WT_Image _hoops_GIGAGR(_hoops_RHGAGR, _hoops_AHGAGR, _hoops_SHGAGR, _hoops_GHGAGR, _hoops_PHGAGR, 
		_hoops_CHGAGR, (WT_Byte *) image->_hoops_PHGH,
		_hoops_HHGAGR, _hoops_IHGAGR, WD_True);

	_hoops_GHGAGR++;

	_hoops_GIGAGR.serialize(*_hoops_ICSRGR->_hoops_HISRGR);

	if (_hoops_IICSR)
		_hoops_HPRH(_hoops_IICSR);
}

local void _hoops_RIGAGR(
	Net_Rendition const		&nr,
	DC_Point const			*start,
	DC_Point const			*end,
	int							hoffset,
	Image_Format				format,
	int							row_bytes,
	void const					* const *_hoops_HCHIH,
	int							pattern,
	Driver_Color const		*contrast_color,
	Image const				*db_image)
{
	W2DData alter *_hoops_ICSRGR = _hoops_SISRGR (nr);
	WT_Image::WT_Image_Format _hoops_SHGAGR;
	WT_Integer32 _hoops_CHGAGR;

	if (!db_image)
	{
		HD_Std_DC_Image(nr, start, end, hoffset, format, row_bytes, 
			_hoops_HCHIH, pattern, contrast_color, db_image);
		return;
	}

	WT_Unsigned_Integer16 _hoops_RHGAGR    = db_image->height;
	WT_Unsigned_Integer16 _hoops_AHGAGR = db_image->width;

	if (format == _hoops_HHGH)
	{
		_hoops_SHGAGR = WT_Image::RGB;
		_hoops_CHGAGR = _hoops_RHGAGR * _hoops_AHGAGR * 3;
	}
	else if (format == Image_RGBA32)
	{
		_hoops_SHGAGR = WT_Image::RGBA;
		_hoops_CHGAGR = _hoops_RHGAGR * _hoops_AHGAGR * 4;
	}
	else
	{
		HD_Std_DC_Image(nr, start, end, hoffset, format, row_bytes, 
					    _hoops_HCHIH, pattern, contrast_color, db_image);
		return;
	}

	static WT_Integer32   _hoops_GHGAGR = 1;
	WT_Color_Map const *  _hoops_PHGAGR = 0;
	WT_Logical_Point _hoops_HHGAGR, _hoops_IHGAGR;
	_hoops_AGGAGR(start, _hoops_HHGAGR, _hoops_ICSRGR);
	_hoops_AGGAGR(end,   _hoops_IHGAGR, _hoops_ICSRGR);

	WT_Image _hoops_GIGAGR(_hoops_RHGAGR, _hoops_AHGAGR, _hoops_SHGAGR, _hoops_GHGAGR, _hoops_PHGAGR, 
					   _hoops_CHGAGR, (WT_Byte *) db_image->_hoops_PHGH,
						_hoops_HHGAGR, _hoops_IHGAGR, WD_True);

	_hoops_GHGAGR++;

	_hoops_GIGAGR.serialize(*_hoops_ICSRGR->_hoops_HISRGR);

}


struct _hoops_AIGAGR
{
	// _hoops_RGR _hoops_HRPR _hoops_HRGR _hoops_SAHR _hoops_IRS _hoops_GGAGA _hoops_IH _hoops_HA
	// _hoops_SR _hoops_GRS _hoops_GGCR _hoops_GIIGGR _hoops_GAR _hoops_PPR _hoops_CGPR _hoops_SIGR
	int _hoops_HCIS;
};

local bool _hoops_PIGAGR(
	Net_Rendition const & nr,
	Font_Instance const * instance,
	Karacter _hoops_IPCSR,
	float alter *_hoops_GGGS,
	bool alter *_hoops_CPCSR,
	void ** _hoops_SPCSR) 
{
	/* _hoops_GHAII: _hoops_GGRAI _hoops_PAPA _hoops_RAIA _hoops_RGR _hoops_IS _hoops_AHC _hoops_CGSI.  _hoops_HHIGR _hoops_HRS _hoops_RH _hoops_GAS _hoops_IGAA _hoops_GGR _hoops_ASPA.  _hoops_HIGAR _hoops_IS _hoops_ASRC _hoops_ARI?
		_hoops_GHAP _hoops_RHCA _hoops_IS _hoops_HSPP _hoops_CCA _hoops_SAHR _hoops_RCCAR _hoops_RPIHR _hoops_PIRA _hoops_IIHA _hoops_GPP _hoops_RH _hoops_APPS _hoops_IIGR _hoops_RH _hoops_HRCSR _hoops_IS _hoops_HGCR _hoops_CGSI _hoops_CRSH. */

	*_hoops_GGGS = instance->_hoops_ISISR;
	*_hoops_CPCSR = false;
	*_hoops_SPCSR = (void*)1;

	return true;
}


local void * _hoops_HIGAGR (
	Display_Context const		*dc,
	char const						*name,
	Font_Instance alter			*instance) 
{
	_hoops_AIGAGR				*_hoops_RHCSR;

	ALLOC (_hoops_RHCSR, _hoops_AIGAGR);
	return (void *)_hoops_RHCSR;
}

local void _hoops_IIGAGR (
	Display_Context const	*dc,
	Font_Instance alter		*instance) 
{
	W2DData alter	*state = _hoops_CISRGR (dc);
	_hoops_AIGAGR		*_hoops_RHCSR = (_hoops_AIGAGR*) instance->_hoops_GAASR;

	FREE (_hoops_RHCSR, _hoops_AIGAGR);
}


/*
* _hoops_SRAC
*/
local bool _hoops_CIGAGR (
	Display_Context alter	*dc,
	char const					 *_hoops_PACSR) 
{
	// _hoops_ARGAGR _hoops_IHIGR _hoops_IPSP _hoops_IS _hoops_AAIR _hoops_GII _hoops_HRCSR _hoops_IIGR _hoops_PAII _hoops_AHSGH - _hoops_SR _hoops_GRS _hoops_CRGS 
	// _hoops_IS _hoops_RH _hoops_AAPA _hoops_PAPA _hoops_SGS _hoops_SR _hoops_PAH _hoops_AA _hoops_GII _hoops_HRCSR - _hoops_HHAC _hoops_IHAC (15-_hoops_SIGAGR-05)
	HD_Record_Font_With_Encoding(dc, _hoops_PACSR, 0, _hoops_SACSR, 0, /*_hoops_GCISC/_hoops_PSSSP*/ 1);
	HD_Mark_Font_As_Transformable (dc, _hoops_PACSR, /*_hoops_IASRGR|_hoops_CASRGR|_hoops_SASRGR*/_hoops_IAGGH);
	return true;
}

local void _hoops_GCGAGR(
						Display_Context alter *dc) 
{
	return;
}


local void _hoops_RCGAGR(Net_Rendition const 	&nr,
						  Font_Instance const 	*specific,
						  Point const 			*where,
						  int					count,
						  Karacter const 		*kstring,
						  Vector const			*scale)
{
	Display_Context const *dc	= nr->_hoops_SRA;
	_hoops_IGCSR const &_hoops_HRCIR		= nr->_hoops_SISI;
	W2DData alter *_hoops_ICSRGR		= _hoops_SISRGR (nr);
	WT_Rendition *_hoops_GGCC			= &_hoops_ICSRGR->_hoops_HISRGR->desired_rendition();
	UNREFERENCED(scale);


	if (_hoops_HRCIR->transform == FT_FULL) {
		HD_Standard_Draw_Font(nr, specific, where, count, kstring, scale);
		return;
	}

	if (!_hoops_HRCIR->font) {
		HD_Standard_Draw_Font(nr, specific, where, count, kstring, scale);
		return;
	}

	switch (specific->family->_hoops_RRCSR)
	{
#ifndef DISABLE_DEFINED_FONTS
		case _hoops_ARCSR:
			specific->_hoops_SRCSR(nr, specific, where, count, kstring, scale);
			break;
#endif
//#_hoops_IHS _hoops_HSIGGR
		case _hoops_SISSP:
			/* _hoops_HGI _hoops_HRGR _hoops_IRS _hoops_CIH _hoops_GPRR _hoops_HRCSR. */
			{
				_hoops_IGPIR const	*name = _hoops_HRCIR->_hoops_HSRIP->_hoops_HGPIR;

				switch (name->_hoops_SSSGP) 
				{
				case GFN_SANS_SERIF:
					_hoops_GGCC->font().font_name().set(WT_String("Arial-GDI-VECTOR"));
					break;
				case GFN_ROMAN:
					_hoops_GGCC->font().font_name().set(WT_String("Times New Roman-GDI-VECTOR"));
					break;
				case GFN_TYPEWRITER:
					_hoops_GGCC->font().font_name().set(WT_String("Courier New-GDI-VECTOR"));
					break;
				case GFN_SPECIFIED: 
					_hoops_HCRPR _hoops_ACGAGR = _hoops_HRCIR->_hoops_HSRIP->_hoops_HGPIR->specified;
					_hoops_GGCC->font().font_name().set(WT_String(_hoops_ACGAGR.length, _hoops_ACGAGR.text));
					break;
				}

				// _hoops_SIGP: _hoops_ISPR _hoops_IH _hoops_CIHH
				WT_Logical_Point _hoops_PCGAGR;
				XYDC2WTLP(where->x, where->y, _hoops_PCGAGR, _hoops_ICSRGR);

				_hoops_GGCC->color() = WT_Color (_hoops_HRCIR->color._hoops_HRIR.r,
										 _hoops_HRCIR->color._hoops_HRIR.g,
										 _hoops_HRCIR->color._hoops_HRIR.b);

				//_hoops_IAGSP->_hoops_HRCSR()._hoops_APPS() = _hoops_IPHCS->_hoops_HRCSR->_hoops_PSSSP;
				_hoops_GGCC->font().style().set_bold((_hoops_HRCIR->_hoops_ASRIP) ? WD_True : WD_False);
				_hoops_GGCC->font().style().set_italic((_hoops_HRCIR->_hoops_PSRIP) ? WD_True : WD_False);
				_hoops_GGCC->font().style().set_underlined((_hoops_HRCIR->_hoops_SCRIP) ? WD_True : WD_False);
				_hoops_GGCC->font().rotation() = _hoops_PCSRGR(_hoops_HRCIR->rotation); 
				_hoops_GGCC->font().oblique() = _hoops_PCSRGR(_hoops_HRCIR->_hoops_IPGRP); 
				_hoops_GGCC->font().width_scale().set(_hoops_HRCIR->width_scale*1024.0f);
				_hoops_GGCC->font().spacing().set(_hoops_HRCIR->spacing*1024.0f);
				_hoops_GGCC->font().family() = WT_Font_Option_Family::FAMILY_UNKNOWN;
				_hoops_GGCC->font().pitch() = WT_Font_Option_Pitch::PITCH_DEFAULT;
				// _hoops_SIGP: _hoops_SGGGH
				//_hoops_IAGSP._hoops_HRCSR()._hoops_SGGGH()._hoops_ARP(512);

				WT_Text _hoops_HCGAGR(_hoops_PCGAGR, WT_String(kstring));

				_hoops_HCGAGR.serialize(*_hoops_ICSRGR->_hoops_HISRGR);
			}break;
//#_hoops_SHIIR
		default:
			{
				HD_Standard_Draw_Font(nr, specific, where, count, kstring, scale);
				return;

				///* _hoops_HGI _hoops_HRGR _hoops_IRS _hoops_CSHCC _hoops_HRCSR (_hoops_GAR _hoops_SR _hoops_RGAR _hoops_RGHH _hoops_SGRRI _hoops_PPR _hoops_CSHCC _hoops_GSPIP). */
				//{
				//	_hoops_ICGAGR _hoops_RCIC * _hoops_CCGAGR = (_hoops_ICGAGR _hoops_RCIC *)_hoops_IPHCS->_hoops_HRCSR->_hoops_HAASR;
				//	_hoops_RSIRR = _hoops_CCGAGR->_hoops_SCGAGR;
				//}
			}
	}

	return;
}

local void _hoops_GSGAGR(
	Net_Rendition const & nr,
	_hoops_HACC const *tx)
{
	_hoops_IGCSR const &_hoops_HRCIR = nr->_hoops_SISI;
	W2DData alter *_hoops_ICSRGR = _hoops_SISRGR (nr);
	WT_Rendition *_hoops_GGCC = &_hoops_ICSRGR->_hoops_HISRGR->desired_rendition();
	_hoops_IGPIR const	*name = _hoops_HRCIR->_hoops_HSRIP->_hoops_HGPIR;

	// _hoops_RGISR _hoops_HRCSR _hoops_HRGR _hoops_RH _hoops_RGAR _hoops_HRCSR _hoops_SR _hoops_GA'_hoops_RA _hoops_GCGH _hoops_ARI - _hoops_CAH _hoops_SCH
	if (name->_hoops_SSSGP == GFN_STROKED || name->_hoops_SSSGP == GFN_SYSTEM_DEFAULT)
	{
		HD_Std_3D_Text(nr, tx);
		return;
	}

	switch (name->_hoops_SSSGP) 
	{
		case GFN_SANS_SERIF:
			_hoops_GGCC->font().font_name().set(WT_String("Arial-GDI-VECTOR"));
			break;
		case GFN_ROMAN:
			_hoops_GGCC->font().font_name().set(WT_String("Times New Roman-GDI-VECTOR"));
			break;
		case GFN_TYPEWRITER:
			_hoops_GGCC->font().font_name().set(WT_String("Courier New-GDI-VECTOR"));
			break;
		case GFN_SPECIFIED: 
			_hoops_HCRPR _hoops_ACGAGR = _hoops_HRCIR->_hoops_HSRIP->_hoops_HGPIR->specified;
			_hoops_GGCC->font().font_name().set(WT_String(_hoops_ACGAGR.length, _hoops_ACGAGR.text));
			break;
	}

	// _hoops_SIGP: _hoops_ISPR _hoops_IH _hoops_CIHH
	Point _hoops_RSGAGR;
	Point _hoops_ASGAGR;

	_hoops_RSGAGR.x = tx->_hoops_CSAI.x;
	_hoops_RSGAGR.y = tx->_hoops_CSAI.y;
	_hoops_RSGAGR.z = tx->_hoops_CSAI.z;

	HI_Compute_Transformed_Points(1, &_hoops_RSGAGR, (float*)&nr->transform_rendition->_hoops_CGCC->data.elements, &_hoops_ASGAGR);

	_hoops_GGCC->color() = WT_Color (_hoops_HRCIR->color._hoops_HRIR.r,
							 _hoops_HRCIR->color._hoops_HRIR.g,
							 _hoops_HRCIR->color._hoops_HRIR.b);

	//_hoops_IAGSP->_hoops_HRCSR()._hoops_APPS() = _hoops_IPHCS->_hoops_HRCSR->_hoops_PSSSP;
	_hoops_GGCC->font().style().set_bold((_hoops_HRCIR->_hoops_ASRIP) ? WD_True : WD_False);
	_hoops_GGCC->font().style().set_italic((_hoops_HRCIR->_hoops_PSRIP) ? WD_True : WD_False);
	_hoops_GGCC->font().style().set_underlined((_hoops_HRCIR->_hoops_SCRIP) ? WD_True : WD_False);
	_hoops_GGCC->font().rotation() = _hoops_PCSRGR(_hoops_HRCIR->rotation); 
	_hoops_GGCC->font().oblique() = _hoops_PCSRGR(_hoops_HRCIR->_hoops_IPGRP); 
	_hoops_GGCC->font().width_scale().set(_hoops_HRCIR->width_scale*1024.0f);
	_hoops_GGCC->font().spacing().set(_hoops_HRCIR->spacing*1024.0f);
	_hoops_GGCC->font().family() = WT_Font_Option_Family::FAMILY_UNKNOWN;
	_hoops_GGCC->font().pitch() = WT_Font_Option_Pitch::PITCH_DEFAULT;
	// _hoops_SIGP: _hoops_SGGGH
	//_hoops_IAGSP._hoops_HRCSR()._hoops_SGGGH()._hoops_ARP(512);

	WT_Logical_Point _hoops_PCGAGR;
	XYDC2WTLP(_hoops_ASGAGR.x, _hoops_ASGAGR.y, _hoops_PCGAGR, _hoops_ICSRGR);
	WT_Text _hoops_HCGAGR(_hoops_PCGAGR, WT_String(tx->karacters));

	_hoops_HCGAGR.serialize(*_hoops_ICSRGR->_hoops_HISRGR);
}

local void _hoops_PSGAGR (
	 Net_Rendition const & nr,
	 DC_Point const				*where,
	 int								count,
	 Karacter const				*kstring) 
{
	_hoops_IGCSR const &_hoops_HRCIR = nr->_hoops_SISI;
	W2DData alter *_hoops_ICSRGR = _hoops_SISRGR (nr);
	WT_Rendition *_hoops_GGCC = &_hoops_ICSRGR->_hoops_HISRGR->desired_rendition();
	_hoops_IGPIR const	*name = _hoops_HRCIR->_hoops_HSRIP->_hoops_HGPIR;

	// _hoops_RGISR _hoops_HRCSR _hoops_HRGR _hoops_RH _hoops_RGAR _hoops_HRCSR _hoops_SR _hoops_GA'_hoops_RA _hoops_GCGH _hoops_ARI - _hoops_CAH _hoops_SCH
	if (name->_hoops_SSSGP == GFN_STROKED || name->_hoops_SSSGP == GFN_SYSTEM_DEFAULT)
	{
		HD_Std_DC_Text (nr, where, count, kstring);
		return;
	}

	switch (name->_hoops_SSSGP) 
	{
	case GFN_SANS_SERIF:
		_hoops_GGCC->font().font_name().set(WT_String("Arial-GDI-VECTOR"));
		break;
	case GFN_ROMAN:
		_hoops_GGCC->font().font_name().set(WT_String("Times New Roman-GDI-VECTOR"));
		break;
	case GFN_TYPEWRITER:
		_hoops_GGCC->font().font_name().set(WT_String("Courier New-GDI-VECTOR"));
		break;
	case GFN_SPECIFIED: 
		_hoops_HCRPR _hoops_ACGAGR = _hoops_HRCIR->_hoops_HSRIP->_hoops_HGPIR->specified;
		_hoops_GGCC->font().font_name().set(WT_String(_hoops_ACGAGR.length, _hoops_ACGAGR.text));
		break;
	}

	// _hoops_SIGP: _hoops_ISPR _hoops_IH _hoops_CIHH
	WT_Logical_Point _hoops_PCGAGR;
	_hoops_AGGAGR(where, _hoops_PCGAGR, _hoops_ICSRGR);

	_hoops_GGCC->color() = WT_Color (_hoops_HRCIR->color._hoops_HRIR.r,
							 _hoops_HRCIR->color._hoops_HRIR.g,
							 _hoops_HRCIR->color._hoops_HRIR.b);

	//_hoops_IAGSP->_hoops_HRCSR()._hoops_APPS() = _hoops_IPHCS->_hoops_HRCSR->_hoops_PSSSP;
	_hoops_GGCC->font().style().set_bold((_hoops_HRCIR->_hoops_ASRIP) ? WD_True : WD_False);
	_hoops_GGCC->font().style().set_italic((_hoops_HRCIR->_hoops_PSRIP) ? WD_True : WD_False);
	_hoops_GGCC->font().style().set_underlined((_hoops_HRCIR->_hoops_SCRIP) ? WD_True : WD_False);
	_hoops_GGCC->font().rotation() = _hoops_PCSRGR(_hoops_HRCIR->rotation); 
	_hoops_GGCC->font().oblique() = _hoops_PCSRGR(_hoops_HRCIR->_hoops_IPGRP); 
	_hoops_GGCC->font().width_scale().set(_hoops_HRCIR->width_scale*1024.0f);
	_hoops_GGCC->font().spacing().set(_hoops_HRCIR->spacing*1024.0f);
	_hoops_GGCC->font().family() = WT_Font_Option_Family::FAMILY_UNKNOWN;
	_hoops_GGCC->font().pitch() = WT_Font_Option_Pitch::PITCH_DEFAULT;
	// _hoops_SIGP: _hoops_SGGGH
	//_hoops_IAGSP._hoops_HRCSR()._hoops_SGGGH()._hoops_ARP(512);

	WT_Text _hoops_HCGAGR(_hoops_PCGAGR, WT_String(kstring));

	_hoops_HCGAGR.serialize(*_hoops_ICSRGR->_hoops_HISRGR);
}

/*
* _hoops_PGAA
* _hoops_RPR < 0 _hoops_AGSR _hoops_GIPGS _hoops_HIPH
* _hoops_RPR > 0 _hoops_AGSR _hoops_RIPGS _hoops_RIHA _hoops_CRHH
*/
local void _hoops_HSGAGR (
	W2DData alter *_hoops_ICSRGR,
	int	count,
	DC_Point const   *points,
	WT_Color const *color)
{
	WT_Rendition *_hoops_GGCC = &_hoops_ICSRGR->_hoops_HISRGR->desired_rendition();

	_hoops_GGCC->color() = *color;

	if (count > 0)
	{
		WT_Logical_Point  *_hoops_ISGAGR = new WT_Logical_Point[count];
		for (int i=0; i < count; i++)
		{
			_hoops_AGGAGR((&points[i]), _hoops_ISGAGR[i], _hoops_ICSRGR);
		}

		WT_Polytriangle _hoops_CSGAGR(count, _hoops_ISGAGR, WD_True);
		_hoops_CSGAGR.serialize(*_hoops_ICSRGR->_hoops_HISRGR);

		if (_hoops_ISGAGR)
			delete[] _hoops_ISGAGR;
	}
	else
	{
		count = -(count);
		WT_Logical_Point* _hoops_SSGAGR = new WT_Logical_Point[count];

		for (int i = 0; i < count; i++)
		{
			_hoops_AGGAGR((&points[i]), _hoops_SSGAGR[i], _hoops_ICSRGR);
		}

		WT_Polygon _hoops_GGRAGR = WT_Polygon(count, _hoops_SSGAGR, WD_True);

		if (_hoops_SSGAGR)
			delete[] _hoops_SSGAGR;

		// _hoops_RGRAGR _hoops_SCH.
		_hoops_GGRAGR.serialize (*_hoops_ICSRGR->_hoops_HISRGR);
	}
}


/*
* _hoops_SRAC
* _hoops_RPR < 0 _hoops_AGSR _hoops_GIPGS _hoops_HIPH
* _hoops_RPR > 0 _hoops_AGSR _hoops_RIPGS _hoops_RIHA _hoops_CRHH
*/
local void _hoops_AGRAGR (
	Net_Rendition const  &nr,
	int	count,
	DC_Point const   *points) 
{
	W2DData alter *_hoops_ICSRGR = _hoops_SISRGR (nr);
	WT_Rendition *_hoops_GGCC = &_hoops_ICSRGR->_hoops_HISRGR->desired_rendition();
	Driver_Color const *color;

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Std_DC_Polytriangle(nr, count, points);
		return;
	}
	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_GPHC);
		return;
	}
	//_hoops_PGRAGR(_hoops_CPGAGR, _hoops_SCII);

	color = &nr->_hoops_IHA->color;
	WT_Color _hoops_HGRAGR = WT_Color (color->_hoops_HRIR.r,
								  color->_hoops_HRIR.g,
								  color->_hoops_HRIR.b);
	_hoops_HSGAGR(_hoops_ICSRGR, count, points, &_hoops_HGRAGR);
}

/*
* _hoops_SRAC
*/
local void _hoops_IGRAGR (
	Net_Rendition const  &nr,
	int	count,
	DC_Point const   *points,
	RGBAS32 const	  *colors,
	bool single) 
{
	W2DData alter *_hoops_ICSRGR = _hoops_SISRGR (nr);
	WT_Rendition *_hoops_GGCC = &_hoops_ICSRGR->_hoops_HISRGR->desired_rendition();


	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Std_DC_Colorized_Polytris (nr, count, points, colors, single);
		return;
	}
	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, colors, 0, 0, 0, 0, 0, _hoops_GPHC|
			(single?_hoops_RAIC:_hoops_PAIC));
		return;
	}
	//_hoops_PGRAGR(_hoops_CPGAGR, _hoops_SCII);

	if (single)
	{
		WT_Color _hoops_HGRAGR = WT_Color(colors->r, colors->g, colors->b);
		_hoops_HSGAGR(_hoops_ICSRGR, count, points, &_hoops_HGRAGR);
	}
	else
	{
		// _hoops_PGSA _hoops_GRR _hoops_GAR _hoops_IRS _hoops_GIAH _hoops_HSSP _hoops_RAS _hoops_RGSR _hoops_SCH'_hoops_GRI _hoops_IGGA _hoops_HAIR
		int _hoops_RRC = 0;
		_hoops_ICHC(count, _hoops_RRC, 3);
		while (count-- > 0) 
		{
			_hoops_GGCC->color() = WT_Color (colors->r, colors->g, colors->b);

			WT_Logical_Point _hoops_SSGAGR[3];
			for (int i = 0; i < 3; i++)
				_hoops_AGGAGR((&points[i]), _hoops_SSGAGR[i], _hoops_ICSRGR);

			WT_Polygon _hoops_GGRAGR(3, _hoops_SSGAGR, WD_True);
			_hoops_GGRAGR.serialize(*_hoops_ICSRGR->_hoops_HISRGR);

			points += _hoops_RRC;
			colors++;
		}
	}
}

/*
* _hoops_SRAC
*/
local void _hoops_CGRAGR (Net_Rendition const &  nr,
											 int count,
											 DC_Point const * points,
											 RGBAS32 const * colors) 
{
	W2DData alter *_hoops_ICSRGR = _hoops_SISRGR (nr);
	WT_Rendition *_hoops_GGCC = &_hoops_ICSRGR->_hoops_HISRGR->desired_rendition();


	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Span_DC_Gouraud_Polytris (nr, count, points, colors);
		return;
	}
	//_hoops_PGRAGR(_hoops_CPGAGR, _hoops_SCII);

	if (count > 0)
	{
		WT_Logical_Point  *_hoops_ISGAGR = new WT_Logical_Point[count];
		WT_RGBA32 		  *_hoops_SGRAGR  = new WT_RGBA32[count];

		for (int i=0; i < count; i++)
		{
			_hoops_AGGAGR((&points[i]), _hoops_ISGAGR[i], _hoops_ICSRGR);
			_hoops_SGRAGR[i]  = WT_RGBA32(colors[i].r, colors[i].g, colors[i].b);
		}

		WT_Gouraud_Polytriangle _hoops_GRRAGR(count, _hoops_ISGAGR, _hoops_SGRAGR, WD_True);
		_hoops_GRRAGR.serialize(*_hoops_ICSRGR->_hoops_HISRGR);

		if (_hoops_ISGAGR)
			delete[] _hoops_ISGAGR;
	}
	else
	{
		// _hoops_PGSA _hoops_GRR _hoops_GAR _hoops_IRS _hoops_GIAH _hoops_HSSP _hoops_RAS _hoops_RGSR _hoops_SCH'_hoops_GRI _hoops_IGGA _hoops_HAIR
		int _hoops_RRC = 0;
		_hoops_ICHC(count, _hoops_RRC, 3);
		while (count-- > 0) 
		{
			_hoops_GGCC->color() = WT_Color (colors->r, colors->g, colors->b);

			WT_Logical_Point _hoops_SSGAGR[3]; 
			for (int i = 0; i < 3; i++)
				_hoops_AGGAGR((&points[i]), _hoops_SSGAGR[i], _hoops_ICSRGR);

			WT_Polygon _hoops_GGRAGR(3, _hoops_SSGAGR, WD_True);
			_hoops_GGRAGR.serialize(*_hoops_ICSRGR->_hoops_HISRGR);

			points += _hoops_RRC;
			colors++;
		}
	}
}


/*
* _hoops_SRAC
*/
local void _hoops_RRRAGR (
	Net_Rendition const  &nr,
	int	count,
	DC_Point const   *where) 
{
	W2DData alter *_hoops_ICSRGR = _hoops_SISRGR (nr);
	WT_Rendition *_hoops_GGCC = &_hoops_ICSRGR->_hoops_HISRGR->desired_rendition();
	Driver_Color const *color;

	//_hoops_PGRAGR(_hoops_CPGAGR, _hoops_SCII);

	color = &nr->_hoops_AHP->color;
	_hoops_GGCC->color() = WT_Color (color->_hoops_HRIR.r,
							color->_hoops_HRIR.g,
							color->_hoops_HRIR.b);

	while (count-- > 0) {
		WT_Logical_Point _hoops_ARRAGR[4]; 
		XYDC2WTLP(where->x,   where->y,   _hoops_ARRAGR[0], _hoops_ICSRGR);
		XYDC2WTLP(where->x+1, where->y,   _hoops_ARRAGR[1], _hoops_ICSRGR);
		XYDC2WTLP(where->x+1, where->y+1, _hoops_ARRAGR[2], _hoops_ICSRGR);
		XYDC2WTLP(where->x,   where->y+1, _hoops_ARRAGR[3], _hoops_ICSRGR);

		//_hoops_PRRAGR _hoops_HRRAGR(*_hoops_CPGAGR->_hoops_IRRAGR, 4, _hoops_CRRAGR);
		//_hoops_HRRAGR._hoops_SRRAGR(*_hoops_CPGAGR->_hoops_IRRAGR);
		WT_Polygon _hoops_GARAGR(4, _hoops_ARRAGR, WD_True);
		_hoops_GARAGR.serialize(*_hoops_ICSRGR->_hoops_HISRGR);
		where++;
	}
}


/*
* _hoops_SRAC
*/
local void _hoops_RARAGR (
	Net_Rendition const  &nr,
	int			left,
	int			right,
	int			bottom,
	int			top) 
{
	W2DData alter *_hoops_ICSRGR = _hoops_SISRGR (nr);
	WT_Rendition *_hoops_GGCC = &_hoops_ICSRGR->_hoops_HISRGR->desired_rendition();
	Driver_Color const *color;

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Std_DC_Rectangle (nr, left, right, bottom, top);
		return;
	}
	//_hoops_PGRAGR(_hoops_CPGAGR, _hoops_SCII);

	color = &nr->_hoops_IHA->color;
	_hoops_GGCC->color() = WT_Color (color->_hoops_HRIR.r,
							color->_hoops_HRIR.g,
							color->_hoops_HRIR.b);

	WT_Logical_Point _hoops_SSGAGR[4];
	XYDC2WTLP(left, bottom, _hoops_SSGAGR[0], _hoops_ICSRGR);
	XYDC2WTLP(right, bottom, _hoops_SSGAGR[1], _hoops_ICSRGR);
	XYDC2WTLP(right, top, _hoops_SSGAGR[2], _hoops_ICSRGR);
	XYDC2WTLP(left, top, _hoops_SSGAGR[3], _hoops_ICSRGR);

	WT_Polygon _hoops_GGRAGR = WT_Polygon(4, _hoops_SSGAGR, WD_True);

	// _hoops_RGRAGR _hoops_SCH.
	_hoops_GGRAGR.serialize (*_hoops_ICSRGR->_hoops_HISRGR);
}


local void _hoops_AARAGR (
	Net_Rendition const  &nr,
	int			count,
	DC_Point const   *points) 
{
	W2DData alter *_hoops_ICSRGR = _hoops_SISRGR (nr);
	WT_Rendition *_hoops_GGCC = &_hoops_ICSRGR->_hoops_HISRGR->desired_rendition();
	Driver_Color const *color;

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Std_DC_Face(nr, count, points);
		return;
	}
	//_hoops_PGRAGR(_hoops_CPGAGR, _hoops_SCII);

	color = &nr->_hoops_IHA->color;
	_hoops_GGCC->color() = WT_Color (color->_hoops_HRIR.r,
							color->_hoops_HRIR.g,
							color->_hoops_HRIR.b);

	WT_Logical_Point* _hoops_SSGAGR = new WT_Logical_Point[count];

	for (int i = 0; i < count; i++)
	{
		_hoops_AGGAGR((&points[i]), _hoops_SSGAGR[i], _hoops_ICSRGR);
	}

	WT_Polygon _hoops_GGRAGR = WT_Polygon(count, _hoops_SSGAGR, WD_True);

	if (_hoops_SSGAGR)
		delete[] _hoops_SSGAGR;

	// _hoops_RGRAGR _hoops_SCH.
	_hoops_GGRAGR.serialize (*_hoops_ICSRGR->_hoops_HISRGR);
}

/*
* _hoops_SRAC
*/
local void _hoops_PARAGR (
									   Net_Rendition const & nr,
									   int 		  count,
									   DC_Point const	*points,
									   RGBAS32 const	*color) 
{
	W2DData alter *_hoops_ICSRGR = _hoops_SISRGR (nr);
	WT_Rendition *_hoops_GGCC = &_hoops_ICSRGR->_hoops_HISRGR->desired_rendition();

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Std_DC_Colorized_Face(nr, count, points, color);
		return;
	}
	//_hoops_PGRAGR(_hoops_CPGAGR, _hoops_SCII);

	_hoops_GGCC->color() = WT_Color (color->r, color->g, color->b);

	WT_Logical_Point* _hoops_SSGAGR = new WT_Logical_Point[count];

	for (int i = 0; i < count; i++)
		_hoops_AGGAGR((&points[i]), _hoops_SSGAGR[i], _hoops_ICSRGR);

	WT_Polygon _hoops_GGRAGR = WT_Polygon(count, _hoops_SSGAGR, WD_True);

	if (_hoops_SSGAGR)
		delete[] _hoops_SSGAGR;

	// _hoops_RGRAGR _hoops_SCH.
	_hoops_GGRAGR.serialize (*_hoops_ICSRGR->_hoops_HISRGR);
}



/*
* _hoops_PGAA 
*/
local bool 
	_hoops_HARAGR(
	W2DData alter *_hoops_ICSRGR,
	Net_Rendition const &	nr)
{
	Line_Rendition const &	_hoops_HC = nr->_hoops_AHP;
	WT_Rendition *_hoops_GGCC = &_hoops_ICSRGR->_hoops_HISRGR->desired_rendition();
	Driver_Color const *color;
	float weight;
	WT_Integer16 *lengths;
	int i, count;

	/*
	_hoops_RPP (_hoops_CPGAGR->_hoops_CHPGS == _hoops_HGICP->_hoops_HSHR)
	_hoops_ASRC _hoops_IHPR;
	*/

	/* _hoops_SR _hoops_GA'_hoops_RA _hoops_RGHH _hoops_GII _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_GGAIA _hoops_III, _hoops_IIGSH _hoops_IGIR _hoops_PSPA
	* _hoops_PAR _hoops_RPHH _hoops_III _hoops_PAIA */
	if (BIT(_hoops_HC->flags, _hoops_SRPI) || 
		ANYBIT(_hoops_HC->line_style->flags, LSF_COMPLEX_ANYBITS)) {
		return false;
	}

	if ((weight = _hoops_HC->weight) < 0)
		weight = (int)(HD_Compute_Generic_Size (nr, _hoops_HC->_hoops_PHP, _hoops_HC->_hoops_HHP, 1.0f, false, 0, true)+0.5f);

	_hoops_GGCC->line_weight() = weight;

	switch (_hoops_HC->style & LCAP_MASK) 
	{
	case LCAP_BUTT:
		_hoops_GGCC->line_style().line_start_cap() = WT_Line_Style::Butt_Cap;
		_hoops_GGCC->line_style().line_end_cap() = WT_Line_Style::Butt_Cap;
		break;
	case LCAP_ROUND:
		_hoops_GGCC->line_style().line_start_cap() = WT_Line_Style::Round_Cap;
		_hoops_GGCC->line_style().line_end_cap() = WT_Line_Style::Round_Cap;
		break;
	case LCAP_SQUARE:
		_hoops_GGCC->line_style().line_start_cap() = WT_Line_Style::Square_Cap;
		_hoops_GGCC->line_style().line_end_cap() = WT_Line_Style::Square_Cap;
		break;
	}

	switch (_hoops_HC->style & LJOIN_MASK) {
		case LJOIN_MITER:
			_hoops_GGCC->line_style().line_join() = WT_Line_Style::Miter_Join;
			break;
		case LJOIN_ROUND:
			_hoops_GGCC->line_style().line_join() = WT_Line_Style::Round_Join;
			break;
		case LJOIN_BEVEL:
			_hoops_GGCC->line_style().line_join() = WT_Line_Style::Bevel_Join;
			break;
	}

	if (!BIT(_hoops_HC->line_style->flags, LSF_SOLID)) 
	{
		count = _hoops_HC->line_style->_hoops_GHISR[0]._hoops_RHISR;
		ALLOC_ARRAY (lengths, count, WT_Integer16);
		for (i = 0 ; i < count ; i++)
			lengths[i] = (float) _hoops_HC->line_style->_hoops_GHISR[0].pattern[i];

		// _hoops_IARAGR::_hoops_SGR+100 _hoops_CHR _hoops_CARAGR _hoops_IS _hoops_SHH _hoops_HHH _hoops_PISSH _hoops_HSGP _hoops_SARAGR.
		// _hoops_RCPA _hoops_SRCH _hoops_GGHS _hoops_RASAR _hoops_CCA _hoops_SCH, _hoops_RH _hoops_HRGAGR _hoops_GPRAGR _hoops_GPPRH _hoops_PCPGC _hoops_CPRAA 100
		_hoops_GGCC->dash_pattern() = WT_Dash_Pattern(WT_Line_Pattern::Count+100/*_hoops_RCC*/, 
			count/*_hoops_CIAAR _hoops_HSH*/, lengths);
		FREE_ARRAY (lengths, count, float);
	}
	else {
		_hoops_GGCC->dash_pattern() = WT_Dash_Pattern::kNull;
	}

	color = &_hoops_HC->color;
	_hoops_GGCC->color() = WT_Color (color->_hoops_HRIR.r,
							 color->_hoops_HRIR.g,
							 color->_hoops_HRIR.b);

	return true;

} /* _hoops_RSGR _hoops_API _hoops_RPRAGR _hoops_ARP _hoops_III _hoops_AIRC */



/*
* _hoops_SRAC
*/
local void _hoops_APRAGR (
	Net_Rendition const  &nr,
	DC_Point const   *center,
	DC_Point const   *radii) 
{
	W2DData alter *_hoops_ICSRGR = _hoops_SISRGR (nr);
	WT_Rendition *_hoops_GGCC = &_hoops_ICSRGR->_hoops_HISRGR->desired_rendition();
	Driver_Color const *color;

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Std_DC_Ellipse(nr, center, radii);
		return;
	}
	//_hoops_PPRAGR(_hoops_PPPGS, _hoops_SCII);

	color = &nr->_hoops_IHA->color;
	_hoops_GGCC->color() = WT_Color (color->_hoops_HRIR.r,
							 color->_hoops_HRIR.g,
							 color->_hoops_HRIR.b);

	WT_Logical_Point _hoops_HPRAGR, _hoops_IPRAGR;
	_hoops_AGGAGR(center, _hoops_HPRAGR, _hoops_ICSRGR);
	_hoops_AGGAGR(radii, _hoops_IPRAGR, _hoops_ICSRGR);
	WT_Filled_Ellipse _hoops_CPRAGR = WT_Filled_Ellipse(_hoops_HPRAGR.m_x, _hoops_HPRAGR.m_y, 
													 _hoops_IPRAGR.m_x, _hoops_IPRAGR.m_y);
	_hoops_CPRAGR.serialize (*_hoops_ICSRGR->_hoops_HISRGR);
}


/*
* _hoops_SRAC
*/
local void _hoops_SPRAGR (
	Net_Rendition const		&nr,
	DC_Point const			*center,
	DC_Point const			*radii)
{
	W2DData alter *_hoops_ICSRGR = _hoops_SISRGR (nr);
	WT_Rendition *_hoops_GGCC = &_hoops_ICSRGR->_hoops_HISRGR->desired_rendition();

	//_hoops_PGRAGR(_hoops_PPPGS, _hoops_SCII);
	if (!_hoops_HARAGR(_hoops_ICSRGR, nr)) {
		HD_Std_DC_Outline_Ellipse(nr, center, radii);
		return;
	}	

	WT_Outline_Ellipse _hoops_CPRAGR = WT_Outline_Ellipse(center->x, center->y, radii->x, radii->y);
	_hoops_CPRAGR.serialize (*_hoops_ICSRGR->_hoops_HISRGR);
}

/*
* _hoops_SRAC
*/
local void _hoops_GHRAGR (
	Net_Rendition const  &nr,
	DC_Point const   *center,
	DC_Point const   *radii,
	float 			start,
	float 			end) 
{
	W2DData alter *_hoops_ICSRGR = _hoops_SISRGR (nr);
	WT_Rendition *_hoops_GGCC = &_hoops_ICSRGR->_hoops_HISRGR->desired_rendition();
	
	//_hoops_PGRAGR(_hoops_CPGAGR, _hoops_SCII);
	if (!_hoops_HARAGR(_hoops_ICSRGR, nr)) {
		HD_Std_DC_Elliptical_Arc(nr, center, radii, start, end);
		return;
	}

	start = _hoops_GCSRGR(start);
	end = _hoops_GCSRGR(end);

	WT_Logical_Point _hoops_HPRAGR, _hoops_IPRAGR;
	_hoops_AGGAGR(center, _hoops_HPRAGR, _hoops_ICSRGR);
	_hoops_AGGAGR(radii, _hoops_IPRAGR, _hoops_ICSRGR);

	WT_Outline_Ellipse _hoops_CPRAGR = WT_Outline_Ellipse(_hoops_HPRAGR.m_x, _hoops_HPRAGR.m_y, 
													   _hoops_IPRAGR.m_x, _hoops_IPRAGR.m_y,
													   start, end);
	_hoops_CPRAGR.serialize (*_hoops_ICSRGR->_hoops_HISRGR);
}



/*
* _hoops_SRAC
*/
local void _hoops_RHRAGR (
	Net_Rendition const & nr,
	int	count,
	DC_Point const *points) 
{
	W2DData alter *_hoops_ICSRGR	   = _hoops_SISRGR (nr);

//	_hoops_PPRAGR(_hoops_PPPGS, _hoops_SCII);
	if (!_hoops_HARAGR(_hoops_ICSRGR, nr)) {
		HD_Std_DC_Polyline(nr, count, points);
		return;
	}
	
	if (count > 0)
	{
		WT_Logical_Point* _hoops_SSGAGR = new WT_Logical_Point[count];

		for (int i = 0; i < count; i++)
		{
			_hoops_AGGAGR((&points[i]), _hoops_SSGAGR[i], _hoops_ICSRGR);
		}

		WT_Polyline _hoops_AHRAGR = WT_Polyline(count, _hoops_SSGAGR, WD_True);

		if (_hoops_SSGAGR)
			delete[] _hoops_SSGAGR;

		// _hoops_RGRAGR _hoops_SCH.
		_hoops_AHRAGR.serialize (*_hoops_ICSRGR->_hoops_HISRGR);

	}
	else
	{
		int					_hoops_RRC;
		_hoops_ICHC (count, _hoops_RRC, 2);

		WT_Logical_Point _hoops_SSGAGR[2];
		while (count-- > 0) 
		{
			_hoops_AGGAGR((&points[0]) , _hoops_SSGAGR[0], _hoops_ICSRGR);
			_hoops_AGGAGR((&points[1]), _hoops_SSGAGR[1], _hoops_ICSRGR);
			WT_Polyline _hoops_AHRAGR = WT_Polyline(2, _hoops_SSGAGR, WD_True);

			// _hoops_RGRAGR _hoops_SCH.
			_hoops_AHRAGR.serialize (*_hoops_ICSRGR->_hoops_HISRGR);

			points += _hoops_RRC;
		}
	}

}

/*
* _hoops_SRAC
*/
local void
_hoops_PHRAGR (Net_Rendition const &  nr,
						  int count,
						  DC_Point const *points,
						  RGBAS32 const *colors) 
{
	W2DData alter *_hoops_ICSRGR = _hoops_SISRGR (nr);
	WT_Rendition *_hoops_GGCC = &_hoops_ICSRGR->_hoops_HISRGR->desired_rendition();

	//	_hoops_PPRAGR(_hoops_PPPGS, _hoops_SCII);
	if (!_hoops_HARAGR(_hoops_ICSRGR, nr)) {
		HD_Std_DC_Gouraud_Polyline (nr, count, points, colors);
		return;
	}

	if (count > 0)
	{
		WT_Logical_Point  *_hoops_ISGAGR = new WT_Logical_Point[count];
		WT_RGBA32 		  *_hoops_SGRAGR  = new WT_RGBA32[count];

		for (int i=0; i < count; i++)
		{
			_hoops_AGGAGR((&points[i]), _hoops_ISGAGR[i], _hoops_ICSRGR);
			_hoops_SGRAGR[i]  = WT_RGBA32(colors[i].r, colors[i].g, colors[i].b);
		}

		WT_Gouraud_Polyline _hoops_HHRAGR(count, _hoops_ISGAGR, _hoops_SGRAGR, WD_True);
		_hoops_HHRAGR.serialize(*_hoops_ICSRGR->_hoops_HISRGR);

		if (_hoops_ISGAGR)
			delete[] _hoops_ISGAGR;
	}
	else
	{
		// _hoops_PGSA _hoops_GRR _hoops_GAR _hoops_IRS _hoops_GIAH _hoops_HSSP _hoops_RAS _hoops_RGSR _hoops_SCH'_hoops_GRI _hoops_IGGA _hoops_HAIR
		int _hoops_RRC = 0;
		_hoops_ICHC(count, _hoops_RRC, 2);
		while (count-- > 0) 
		{
			_hoops_GGCC->color() = WT_Color (colors->r, colors->g, colors->b);

			WT_Logical_Point _hoops_SSGAGR[3]; 
			_hoops_AGGAGR((&points[0]), _hoops_SSGAGR[0], _hoops_ICSRGR);
			_hoops_AGGAGR((&points[1]), _hoops_SSGAGR[1], _hoops_ICSRGR);

			WT_Polyline _hoops_AHRAGR(2, _hoops_SSGAGR, WD_True);
			_hoops_AHRAGR.serialize(*_hoops_ICSRGR->_hoops_HISRGR);

			points += _hoops_RRC;
			colors += _hoops_RRC;
		}
	}

}


/*
* _hoops_SRAC
*/
local void _hoops_IHRAGR (
		Net_Rendition const & nr,
		DC_Point const 		*start,
		DC_Point const			*end,
		int						row_bytes,
		RGBAS32 const			*rasters) 
{
// _hoops_RGR _hoops_CRHPR _hoops_CGSI _hoops_CPPPR _hoops_HIAC - _hoops_AHAC _hoops_SCH _hoops_IH _hoops_HA

	W2DData alter *_hoops_ICSRGR = _hoops_SISRGR (nr);
	WT_Rendition *_hoops_GGCC = &_hoops_ICSRGR->_hoops_HISRGR->desired_rendition();
	RGBAS32	  const *color;
	int i, j, width, height;
	DC_Point where;

	//_hoops_PPRAGR(_hoops_PPPGS, _hoops_SCII);

	width = (int)end->x - (int)start->x + 1;
	height = (int)end->y - (int)start->y + 1;
	color = rasters;	
	where.x = start->x;
	where.y = start->y;
	for (j = 0 ; j < height ; j++) {
		for (i = 0 ; i < width ; i++) {

			_hoops_GGCC->color() = WT_Color (color->r, color->g, color->b);

			WT_Logical_Point _hoops_ARRAGR[4]; 
			XYDC2WTLP(where.x,   where.y,   _hoops_ARRAGR[0], _hoops_ICSRGR);
			XYDC2WTLP(where.x+1, where.y,   _hoops_ARRAGR[1], _hoops_ICSRGR);
			XYDC2WTLP(where.x+1, where.y+1, _hoops_ARRAGR[2], _hoops_ICSRGR);
			XYDC2WTLP(where.x,   where.y+1, _hoops_ARRAGR[3], _hoops_ICSRGR);
			
			//_hoops_PRRAGR _hoops_HRRAGR(*_hoops_CPGAGR->_hoops_IRRAGR, 4, _hoops_CRRAGR);
			//_hoops_HRRAGR._hoops_SRRAGR(*_hoops_CPGAGR->_hoops_IRRAGR);
			WT_Polygon _hoops_GARAGR(4, _hoops_ARRAGR, WD_True);
			_hoops_GARAGR.serialize(*_hoops_ICSRGR->_hoops_HISRGR);

			color++;
			where.x += 1;
		}
		where.x = start->x;
		where.y += 1;
	}

}

local void _hoops_CHRAGR (
								  Display_Context alter	*dc) 
{
	W2DData alter	*_hoops_ICSRGR = _hoops_CISRGR (dc);
	float width, height, _hoops_HGII;

	width = 8.5f;
	height = 11.0f;
	_hoops_HGII = 150;

	if (dc->options._hoops_SPHSR.x != -1) {
		width = dc->options._hoops_SPHSR.x / 2.54f;
		height = dc->options._hoops_SPHSR.y / 2.54f;
	}

	dc->_hoops_PGCC._hoops_ARISR.x = 0;
	dc->_hoops_PGCC._hoops_ARISR.y = 0;

	dc->_hoops_PGCC._hoops_PRPSR.x = (int) (_hoops_HGII * width);
	dc->_hoops_PGCC._hoops_PRPSR.y = (int) (_hoops_HGII * height);
	dc->_hoops_PGCC.size.x = width * 2.54;
	dc->_hoops_PGCC.size.y = height * 2.54;

	dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;
	/*_hoops_CSPH->_hoops_CPHSR._hoops_SHRAGR = _hoops_GIRAGR;*/

	dc->_hoops_PGCC._hoops_CHHSR = _hoops_SHHSR;
	dc->_hoops_PGCC._hoops_PCHSR = 256;
	dc->_hoops_PGCC.flags |= _hoops_CAPGH;
	dc->_hoops_PGCC.flags &= ~_hoops_RSHSR;
	dc->_hoops_PGCC.flags &= ~_hoops_PSHSR;
	dc->_hoops_PGCC.flags &= ~_hoops_HSHSR;
	dc->_hoops_PGCC.flags |= _hoops_ISHSR;
	dc->_hoops_PGCC.flags |= _hoops_HPPGH;
	dc->_hoops_PGCC.flags |= _hoops_GIHSR;
	dc->_hoops_PGCC.flags |= _hoops_IPPGH;
	dc->_hoops_PGCC.flags |= _hoops_CCHSR;
	dc->_hoops_PGCC.flags |= _hoops_ISRIP;

	dc->_hoops_PGCC.driver_type = "whip2d";
	dc->_hoops_PGCC._hoops_SCHSR = "$Revision: 1.56 $";
	dc->_hoops_PGCC._hoops_ICHSR = "vector";

        /* #11903 _hoops_RGAR _hoops_ARP _hoops_SHIR _hoops_III _hoops_SGCR _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_PIP _hoops_IPPSR _hoops_III _hoops_SGCR. */
        if(!dc->options._hoops_HHHSR)
            dc->_hoops_PGCC._hoops_IHHSR = dc->options._hoops_GHHSR/150.0f;


	//	// _hoops_PAIHR _hoops_AAPA-_hoops_PAPA _hoops_GPP _hoops_RGR _hoops_IS _hoops_HGCR 3D _hoops_PGSI _hoops_PIGS
	//  _hoops_CSPH->_hoops_SGI |= _hoops_AHRPI;
	//	_hoops_CSPH->_hoops_CPHSR._hoops_IAAGH = 65535;
	//	_hoops_CSPH->_hoops_CPHSR._hoops_RIRAGR = 65535.0f;
	//_hoops_RPP (_hoops_CSPH->_hoops_CPHSR._hoops_IAAGH > 0) 
	//	_hoops_CSPH->_hoops_SGI &= ~_hoops_AIRAGR;
	//_hoops_SHS 
	//	_hoops_CSPH->_hoops_SGI |= _hoops_AIRAGR;
	//
	//	// _hoops_HACSR _hoops_AAPA-_hoops_PAPA _hoops_IS _hoops_CHASA _hoops_CRRPA _hoops_IAPRR _hoops_PPR _hoops_HCGR _hoops_SIIGGR
	//	_hoops_CSPH->_hoops_SGI |= _hoops_PIRAGR;


	//_hoops_CPGAGR->_hoops_RAAA = _hoops_CSPH->_hoops_AAP._hoops_GPAGS;

}


local void
_hoops_HIRAGR(Display_Context alter * dc)
{
	W2DData alter *_hoops_ICSRGR = _hoops_CISRGR(dc);

	_hoops_ICSRGR->_hoops_HAP = dc->options._hoops_GHHSR;

	if (dc->options._hoops_SPHSR.x != -1) {
		_hoops_ICSRGR->width = 72 * dc->options._hoops_SPHSR.x / 2.54f;
		_hoops_ICSRGR->height = 72 * dc->options._hoops_SPHSR.y / 2.54f;
	} else {
		_hoops_ICSRGR->width = 72 * dc->_hoops_PGCC.size.x / 2.54f;
		_hoops_ICSRGR->height = 72 * dc->_hoops_PGCC.size.y / 2.54f;
	}

	dc->current._hoops_HAP.x = _hoops_ICSRGR->_hoops_HAP / 2.54f;
	dc->current._hoops_HAP.y = _hoops_ICSRGR->_hoops_HAP / 2.54f;
	dc->current._hoops_PRPSR.x = (int) (_hoops_ICSRGR->_hoops_HAP * _hoops_ICSRGR->width / 72.0f);
	dc->current._hoops_PRPSR.y = (int) (_hoops_ICSRGR->_hoops_HAP * _hoops_ICSRGR->height / 72.0f);

	return;
}

local POINTER_SIZED_INT _hoops_IIRAGR (
	Display_Context const	*_hoops_RSAAI) 
{
	Display_Context alter	*dc = (Display_Context alter*) _hoops_RSAAI;
	W2DData alter	*_hoops_ICSRGR = _hoops_CISRGR (dc);

	// _hoops_GHAP _hoops_PAH _hoops_GCAS _hoops_SGH _hoops_RGR _hoops_IH _hoops_RRHCP _hoops_SRPHR _hoops_IH _hoops_RH _hoops_PISRGR _hoops_CIRAGR - _hoops_HHAC _hoops_IHAC
	//_hoops_AIRII (_hoops_CPGII, "%%%%_hoops_SIRAGR: _hoops_AGAH %0.2f-%_hoops_GHGP\_hoops_ACHP",
	//		 (_hoops_AIIC)_hoops_GCRAGR / 100.0f, _hoops_RCRAGR);
	//_hoops_RPP (_hoops_CSPH->_hoops_AAP._hoops_CRSAI._hoops_SPCC != 0) {
	//	_hoops_AIRII (_hoops_CPGII, "%%%%_hoops_ACRAGR: %_hoops_GRI\_hoops_ACHP",
	//				_hoops_PCRAGR (_hoops_IRAP, "%_hoops_ACHP", &_hoops_CSPH->_hoops_AAP._hoops_CRSAI));

	if (dc->options._hoops_SPHSR.x != -1) {
		dc->_hoops_PGCC.extent.right = _hoops_ICSRGR->_hoops_HAP * dc->options._hoops_SPHSR.x / 2.54f;		
		dc->_hoops_PGCC.extent.top = _hoops_ICSRGR->_hoops_HAP * dc->options._hoops_SPHSR.y / 2.54f;
	} else {
		dc->_hoops_PGCC.extent.right = _hoops_ICSRGR->_hoops_HAP * 8.5f;	
		dc->_hoops_PGCC.extent.top = _hoops_ICSRGR->_hoops_HAP * 11.0f;
	}
	dc->_hoops_PGCC.extent.left = 0;
	dc->_hoops_PGCC.extent.bottom = 0;

	dc->_hoops_PGCC._hoops_PRPSR.x = (int) (dc->_hoops_PGCC.extent.right);
	dc->_hoops_PGCC._hoops_PRPSR.y = (int) (dc->_hoops_PGCC.extent.top);

	// _hoops_PS _hoops_CSRA _hoops_RH _hoops_AGAH _hoops_SHCA _hoops_PCRR _hoops_IS _hoops_RH _hoops_ARGAGR _hoops_SICHR _hoops_GHARR. _hoops_HGI _hoops_PSAAA _hoops_IHHH _hoops_SRCH 
	// _hoops_RH _hoops_GPPS _hoops_PRGAGR. _hoops_IPCP _hoops_IRRPI _hoops_GHARR _hoops_HRGR _hoops_GRSSR _hoops_GAR _hoops_CAPP
	//----------------------------------------------------------------------------------
	//_hoops_IGGPH _hoops_IIGR _hoops_RH _hoops_PCRR _hoops_CHIA _hoops_GGR _hoops_HRGAGR! _hoops_PIH _hoops_CHR _hoops_GGR _hoops_SICHR _hoops_PCRR, 
	//_hoops_GAR _hoops_HISIP _hoops_IS _hoops_SHPR _hoops_PAR _hoops_SISS _hoops_PCRR. _hoops_IRRPI _hoops_PCRR _hoops_CHR _hoops_CHIA 
	//_hoops_GAR _hoops_RH _hoops_RPRHR _hoops_CCIR _hoops_IIGR 32-_hoops_IGRH _hoops_CPCSH _hoops_CAIPR (31 _hoops_SIH _hoops_IIGR _hoops_GPPS) _hoops_CCA _hoops_IRS 
	//_hoops_RPRI _hoops_CCIR _hoops_HII 0 _hoops_IS _hoops_IRS _hoops_CIAS _hoops_IIGR 2,147,483,647 (231 - 1). 
	//_hoops_PAGAR, _hoops_IRS _hoops_HRGAGR! _hoops_PIH _hoops_GIAR _hoops_CCRPR _hoops_CGH _hoops_CSRA _hoops_RH _hoops_RSHRC _hoops_PICA 
	//_hoops_IIGR _hoops_RH _hoops_IRGAGR _hoops_SGS _hoops_HRGR _hoops_IHGS _hoops_GCSS _hoops_HIS _hoops_SGS _hoops_IRS _hoops_CHPP _hoops_PRGGR _hoops_IIGR _hoops_RGR 31-_hoops_IGRH 
	//_hoops_CCIR _hoops_HRGR _hoops_IGI. _hoops_HGI _hoops_IHIGR _hoops_IRS _hoops_HRGAGR! _hoops_PIH _hoops_GPS _hoops_CCRPR _hoops_IS _hoops_CSRA _hoops_RH _hoops_IRGAGR 
	//_hoops_IH _hoops_RH _hoops_PIASR _hoops_AIRI _hoops_PAR _hoops_IRS _hoops_IPSP _hoops_IS _hoops_GRCPC _hoops_GGR _hoops_GPP _hoops_RH _hoops_ASCA _hoops_CCA _hoops_CHIS _hoops_GPPS 
	//_hoops_IS _hoops_SRGS _hoops_RCRAR _hoops_RCAHR.

	// _hoops_CRGAGR _hoops_SRGAGR _hoops_CIHGS-_hoops_RACIR _hoops_GAGAGR
	//	 _hoops_RAGAGR-_hoops_PGCR-_hoops_IGRH _hoops_HHIPR _hoops_HSH _hoops_CHR _hoops_IGI _hoops_PGGA _hoops_SSIA _hoops_ASSS _hoops_IH _hoops_RRI _hoops_GPPS _hoops_PPR 
	//	 _hoops_RRPAR _hoops_CGGGA _hoops_ACHPR _hoops_HSAR 32-_hoops_IGRH _hoops_SAPS-_hoops_PPSR _hoops_HSH. _hoops_SRIGP _hoops_IIGR _hoops_IRS _hoops_SAPS-_hoops_PPSR 
	//	 _hoops_PHI’_hoops_GRI 32 _hoops_SIH, 8 _hoops_SIH _hoops_CHR _hoops_IGI _hoops_IS _hoops_ASH _hoops_RRASR _hoops_PPR _hoops_HRASR _hoops_HPHS, _hoops_PHGHR _hoops_RGAR 24 _hoops_SIH 
	//	 _hoops_IIGR _hoops_IHPR _hoops_GPPS (_hoops_HAR _hoops_IS _hoops_SHH _hoops_PCCGS _hoops_CCA _hoops_IRS _hoops_SAPS _hoops_PPSR _hoops_PHI’_hoops_GRI _hoops_CHPP _hoops_CCIR).

	//	 _hoops_CGP _hoops_IRS _hoops_ARCR _hoops_AAPR _hoops_CHCC _hoops_CCA _hoops_HRGAGR! _hoops_PIH’_hoops_GRI 31-_hoops_IGRH _hoops_HHIPR _hoops_PCRR, _hoops_IAPR 
	//	 21,000 _hoops_AAGAGR (>12,000 _hoops_PAGAGR) _hoops_IIGR _hoops_GIRA _hoops_HHS _hoops_SHH _hoops_HAGAGR _hoops_RHRI _hoops_ISHP _hoops_IS 1-_hoops_SPIHH 
	//	 _hoops_IAGAGR. _hoops_CGP 32-_hoops_IGRH _hoops_SAPS-_hoops_PPSR _hoops_PCRR _hoops_AAPR _hoops_IGI, _hoops_RGAR 167 _hoops_AAGAGR (100 _hoops_PAGAGR) 
	//	 _hoops_HHS _hoops_SHH _hoops_RHRI _hoops_IS _hoops_RGR _hoops_PAPA _hoops_IIGR _hoops_AHSIR. _hoops_HPGHR _hoops_CGARA, _hoops_CAGAGR _hoops_RAIA 64 _hoops_IGRH _hoops_GHGPR-_hoops_PCPP 
	//	 _hoops_SAPS _hoops_PPSR _hoops_PCRR _hoops_IS _hoops_GRGPR _hoops_RGR _hoops_RCSRR, _hoops_CCA _hoops_IRS _hoops_ARGR 52 _hoops_SIH _hoops_IIGR _hoops_GPPS _hoops_PPR 
	//	 _hoops_PCCP _hoops_SAGAGR _hoops_CCIR. _hoops_HSRR _hoops_RH _hoops_RRI _hoops_PPAC _hoops_AHAR _hoops_IIGR _hoops_APRAA _hoops_PCCP _hoops_GPGAGR _hoops_SGRAI, _hoops_HRGAGR! 
	//	 _hoops_PIH'_hoops_GRI 31 _hoops_SIH _hoops_IIGR _hoops_GPPS _hoops_CHR _hoops_RRI _hoops_HSAR _hoops_HPARS. 
	//----------------------------------------------------------------------------------

	double _hoops_RPGAGR = dc->_hoops_PGCC._hoops_PRPSR.x;
	if (_hoops_RPGAGR == 0.0f)
		_hoops_RPGAGR = 1.0f;

	double _hoops_APGAGR = dc->_hoops_PGCC._hoops_PRPSR.y;
	if (_hoops_APGAGR == 0.0f)
		_hoops_APGAGR = 1.0f;

	// _hoops_RHHSR _hoops_RH _hoops_PPGAGR - _hoops_SGH _hoops_RH _hoops_AASC _hoops_IIGR _hoops_PGCR _hoops_CCPA
	if (_hoops_RPGAGR > _hoops_APGAGR)
		_hoops_ICSRGR->_hoops_IISRGR = _hoops_RPGAGR;
	else
		_hoops_ICSRGR->_hoops_IISRGR = _hoops_APGAGR;
	return (POINTER_SIZED_INT) _hoops_ICSRGR->_hoops_HISRGR;
}

/*
* _hoops_SRAC
*/
local void
_hoops_HCRAGR (Net_Rendition const &  nr,
				int left, int right, int bottom, int top) 
{
	return;
}



local bool _hoops_ICRAGR (
		Display_Context alter	*dc) 
{
	W2DData alter				*_hoops_ICSRGR;

	// _hoops_ASGGR _hoops_RH _hoops_RGHR _hoops_IH _hoops_GGI
	WT_File *_hoops_CCRAGR = new WT_File();

	_hoops_CCRAGR->set_filename (dc->_hoops_PCRSR);
	_hoops_CCRAGR->set_file_mode (WT_File::File_Write);

	if (_hoops_CCRAGR->open() != WT_Result::Success)
	{
		HE_ERROR (HEC_WHIP2D_DRIVER, HES_FILE_OPEN,
			Sprintf_S (null,
			"HOOPS Whip2D driver cannot open %s file for writing",
			dc->_hoops_PCRSR));
		return false;
	}
     
    //_hoops_SCRAGR?
	//_hoops_GSRAGR->_hoops_SCSHP()._hoops_RSRAGR(_hoops_ASRAGR);
	_hoops_CCRAGR->heuristics().set_allow_data_compression(WD_True);
	// _hoops_ARPR _hoops_RHPP _hoops_PIH
	ZALLOC (_hoops_ICSRGR, W2DData);
	dc->data = (void alter *) _hoops_ICSRGR;

	// _hoops_ASH _hoops_RH _hoops_RGHR
	_hoops_ICSRGR->_hoops_HISRGR = _hoops_CCRAGR;

	/* _hoops_PAIA - _hoops_RCSC _hoops_RHAP _hoops_AAPA _hoops_PAPA _hoops_HHGC _hoops_RH _hoops_RHPP _hoops_IS _hoops_AA _hoops_RGR? _hoops_GHAP _hoops_GA'_hoops_RA _hoops_ACPA*/
	HD_Get_Bit_Patterns (dc, true);

	return true;
}


local void _hoops_PSRAGR (
	Display_Context alter *dc) 
{
	W2DData alter				*_hoops_ICSRGR = _hoops_CISRGR (dc);

	if (_hoops_ICSRGR->_hoops_HISRGR)
	{
		_hoops_ICSRGR->_hoops_HISRGR->close();
		delete _hoops_ICSRGR->_hoops_HISRGR;
	}

#ifdef _hoops_HSRAGR
	FILE alter					*fp = state->fp;
	_hoops_RRASC alter			*_hoops_PPPSC;
	_hoops_PRASC alter	*_hoops_GIPSC;

	/* _hoops_APSHR _hoops_GH _hoops_GII _hoops_PPGS _hoops_SGS _hoops_CSAP _hoops_PSPP.
	** _hoops_HGI _hoops_CRRPR:
	**			_hoops_AIPSC
	**			_hoops_PIPSC
	**			_hoops_PIAP (_hoops_ISRAGR)
	*/
	_hoops_PPPSC = state->_hoops_GPPIR;
	while (_hoops_PPPSC != null) {
		_hoops_PPPSC = state->_hoops_GPPIR->next;
		FREE(state->_hoops_GPPIR, _hoops_RRASC);
		state->_hoops_GPPIR = _hoops_PPPSC;
	}
#endif

	FREE(_hoops_ICSRGR, W2DData);

	dc->data = null;
}

/*
* _hoops_SRAC
*/
// _hoops_IRHRC _hoops_RH _hoops_CAGH.
// _hoops_RCIAH _hoops_HA _hoops_SR _hoops_CHR _hoops_GRP _hoops_RGR _hoops_IS _hoops_HGCR _hoops_RH _hoops_CSRAGR _hoops_HISS _hoops_IS _hoops_RH _hoops_SGHC _hoops_GAR _hoops_IPSP _hoops_AAP.
// _hoops_IPCP _hoops_API _hoops_SSRAGR _hoops_AIRC _hoops_IIGR _hoops_RH _hoops_CAGH _hoops_IH _hoops_IPSP _hoops_AAP. _hoops_SPAA _hoops_SCH _hoops_HCGC _hoops_RPP _hoops_RH _hoops_IPSP _hoops_HCSP _hoops_HRGR 
// _hoops_GGAAGR. _hoops_CGP _hoops_CHCAR _hoops_RGAAGR _hoops_SCH _hoops_IS _hoops_PISRGR _hoops_RGHR.
local void _hoops_AGAAGR (
	Net_Rendition const &	nr,
	_hoops_CRCP const *			_hoops_SRCP,
	_hoops_HICS const &	path) {
	Display_Context const*  dc = nr->_hoops_SRA;
	W2DData alter *			_hoops_ICSRGR = _hoops_SISRGR (nr);
	WT_Rendition *			_hoops_GGCC     = &_hoops_ICSRGR->_hoops_HISRGR->desired_rendition();

	 if (!BIT(dc->flags, _hoops_IRSI) && nr->current == nr->_hoops_RCSHR)  {
		 Attribute const *		_hoops_ASGPR;

		 WT_String name;
		 WT_String _hoops_PGAAGR;
		 WT_String _hoops_HGAAGR;
		 WT_Integer32 index = 0;
		 
		 /* _hoops_IHSH _hoops_IH _hoops_IGRI */
		 if ((_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR) != null) {
			 do {
				 WT_URL * _hoops_IGAAGR = new WT_URL;

				 // _hoops_ASIGA
				 if (_hoops_ASGPR->type >= HK_USER_OPTIONS) {
					 if (_hoops_ASGPR->type > HK_USER_OPTIONS)
						 break;

					 if (!BIT (_hoops_ASGPR->_hoops_RRHH, _hoops_HGAGR)) {
						 /* _hoops_HSPAR _hoops_RGR _hoops_IPSP _hoops_HCSP _hoops_IH _hoops_RH _hoops_CGAAGR _hoops_GSGR */
						 _hoops_HPPIR const *			_hoops_IPPIR = (_hoops_HPPIR *)_hoops_ASGPR;
						 Option_Value const *			option;
						
						 if ((option = _hoops_IPPIR->option_list) != null) {
							 // _hoops_PS _hoops_HS _hoops_IRS _hoops_HAPR _hoops_ARI _hoops_HIS _hoops_GAR _hoops_IS _hoops_HGCR _hoops_HCR _hoops_RH _hoops_CSRAGR _hoops_PIH _hoops_GCSS _hoops_GAR _hoops_HAGH _hoops_IPSP
							 // _hoops_AAP.
							 do {
								 if (!strcmp ("hyperlink name", option->type->name.text)) 
									 name = option->value._name->text;
								 else if (!strcmp ("hyperlink location", option->type->name.text)) 
									 _hoops_PGAAGR = option->value._name->text;
								 else if (!strcmp ("hyperlink description", option->type->name.text)) 
									 _hoops_HGAAGR = option->value._name->text;
							 } while ((option = option->next) != null);

							_hoops_IGAAGR->add_url (index, name, _hoops_HGAAGR);
							_hoops_IGAAGR->serialize (*_hoops_ICSRGR->_hoops_HISRGR);
							index++;
						}
					 }
				 }

				 delete _hoops_IGAAGR;
			} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
		 }
	 }

	 HD_Standard_Draw_Tree (nr, _hoops_SRCP, path);
}


local void _hoops_RSCSR (
	_hoops_APARR alter &		_hoops_RRCI) {

	/* _hoops_SISS */
	_hoops_RRCI->start_device					= _hoops_ICRAGR;
	_hoops_RRCI->stop_device						= _hoops_PSRAGR;
	_hoops_RRCI->get_physical_info				= _hoops_CHRAGR;
	_hoops_RRCI->get_current_info				= _hoops_HIRAGR;
	_hoops_RRCI->init_picture					= _hoops_RRGAGR;

	/* _hoops_RPPS */
	_hoops_RRCI->get_outer_window				= _hoops_IIRAGR;

	/* 3D _hoops_ASCA */
	//_hoops_HPGR->_hoops_SGAAGR					= _hoops_GRAAGR;


	/* 2D _hoops_ASCA */
	_hoops_RRCI->draw_dc_rgb32_rasters			= _hoops_IHRAGR;
	_hoops_RRCI->draw_dc_polyline				= _hoops_RHRAGR;
	_hoops_RRCI->draw_dc_ellipse					= _hoops_APRAGR;
	_hoops_RRCI->_hoops_SCISR			= _hoops_SPRAGR;
	_hoops_RRCI->_hoops_CCISR			= _hoops_GHRAGR;
	_hoops_RRCI->draw_dc_face					= _hoops_AARAGR;
	_hoops_RRCI->draw_dc_colorized_face			= _hoops_PARAGR;
	_hoops_RRCI->draw_dc_rectangle				= _hoops_RARAGR;
	_hoops_RRCI->draw_dc_polydot					= _hoops_RRRAGR;
	_hoops_RRCI->draw_dc_polytriangle			= _hoops_AGRAGR;
	_hoops_RRCI->draw_dc_colorized_polytriangle	= _hoops_IGRAGR;
	_hoops_RRCI->draw_dc_gouraud_polytriangle	= _hoops_CGRAGR;
	_hoops_RRCI->draw_dc_gouraud_polyline		= _hoops_PHRAGR;
	_hoops_RRCI->_hoops_HPCGA					= _hoops_RIGAGR;
	//_hoops_HPGR->_hoops_IHRPI					= _hoops_RRAAGR;

	_hoops_RRCI->draw_window = _hoops_SPGAGR;

	/* _hoops_GSPIP & _hoops_HCGR */
	//_hoops_HPGR->_hoops_ARAAGR					= _hoops_PRAAGR;
	//_hoops_HPGR->_hoops_CACPC						= _hoops_HRAAGR;
	//_hoops_HPGR->_hoops_SACPC						= _hoops_IRAAGR;
	//_hoops_HPGR->_hoops_HACPC					= _hoops_CRAAGR;
	//_hoops_HPGR->_hoops_HRPGS					= _hoops_SRAAGR;

	/* _hoops_AHCR _hoops_SRHR _hoops_PCPH - _hoops_ICHHH - _hoops_RGHP _hoops_IH _hoops_GHHS _hoops_HCPH _hoops_IS 3D _hoops_PGSI*/
	_hoops_RRCI->_hoops_CAAGR					= _hoops_HCRAGR;

	_hoops_RRCI->_hoops_SCCSP						= _hoops_AGAAGR;
	//_hoops_HPGR->_hoops_GAAAGR						= _hoops_RAAAGR;

/*	
	_hoops_HPGR->_hoops_AAAAGR	_hoops_PAAAGR;
	_hoops_HPGR->_hoops_HAAAGR		_hoops_IAAAGR;
	_hoops_HPGR->_hoops_CAAAGR		_hoops_SAAAGR;
	_hoops_HPGR->_hoops_GPAAGR				_hoops_RPAAGR;
	_hoops_HPGR->_hoops_APAAGR		_hoops_PPAAGR;
	_hoops_HPGR->_hoops_HPAAGR			_hoops_IPAAGR;
	_hoops_HPGR->_hoops_CPAAGR		_hoops_SPAAGR;
	_hoops_HPGR->_hoops_GHAAGR			_hoops_RHAAGR;

	_hoops_HPGR->_hoops_AHAAGR						_hoops_PHAAGR;
	_hoops_HPGR->_hoops_HHAAGR			_hoops_IHAAGR;
	_hoops_HPGR->_hoops_CHAAGR				_hoops_SHAAGR;
	_hoops_HPGR->_hoops_GIAAGR			_hoops_RIAAGR;
	_hoops_HPGR->_hoops_AIAAGR				_hoops_PIAAGR;
	_hoops_HPGR->_hoops_HIAAGR				_hoops_IHCAC;
	_hoops_HPGR->_hoops_IIAAGR			_hoops_CHCAC;
	_hoops_HPGR->_hoops_CIAAGR			_hoops_SHCAC;

	_hoops_HPGR->_hoops_HSGC					= _hoops_HSGC;
	_hoops_HPGR->_hoops_GACHS				= _hoops_GACHS;


	_hoops_HPGR->_hoops_IGGSP = _hoops_IGGSP;
	*/
}

extern "C" bool HC_CDECL HD_Whip2D_Driver (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (request_info);
	return HD_Connect_Standard_Driver (_hoops_RIGC, _hoops_GHRI, request, _hoops_RSCSR);
}


_hoops_HSCSR (_hoops_RSCSR)

#endif /* _hoops_SIAAGR */


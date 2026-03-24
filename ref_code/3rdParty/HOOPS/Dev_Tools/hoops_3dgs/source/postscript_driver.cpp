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
 * $Id: obf_tmp.txt 1.314 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "hd_proto.h"


#define _hoops_RCRSC

#ifndef POSTSCRIPT_DRIVER

extern "C" bool HC_CDECL HD_PostScript_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) {
	UNREFERENCED (request_info);

	return HD_No_Driver (_hoops_RIGC, _hoops_GHRI, request, "postscript");
}

#else

#include "database.h"
#include "driver.h"
#include "filedata.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "patterns.h"
#include "please.h"
#include "searchh.h"
#include "tandt.h"
#include "span.h"
#include "hversion.h"


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

local bool _hoops_GGASC (Display_Context alter *dc, Activity _hoops_SCISP);

#define _hoops_RGASC			0x00000001
#define _hoops_AGASC		0x00000002
#define _hoops_PGASC	0x00000004
#define _hoops_HGASC	0x00000008
#define _hoops_IGASC	0
#define _hoops_CGASC 1
#define _hoops_SGASC	2

struct _hoops_GRASC {
	int					id;
	_hoops_SRHSR			name;
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


local _hoops_GRASC const _hoops_PIASC[] = {
	{_hoops_GAASC,	_hoops_GRRCR ("StartFontMetrics")},
	{_hoops_RAASC,				_hoops_GRRCR ("Comment")},
	{_hoops_AAASC,				_hoops_GRRCR ("FontName")},
	{_hoops_PAASC,		_hoops_GRRCR ("EncodingScheme")},
	{_hoops_HAASC,				_hoops_GRRCR ("FullName")},
	{_hoops_IAASC,			_hoops_GRRCR ("FamilyName")},
	{_hoops_CAASC,				_hoops_GRRCR ("Weight")},
	{_hoops_SAASC,			_hoops_GRRCR ("ItalicAngle")},
	{_hoops_GPASC,		_hoops_GRRCR ("IsFixedPitch")},
	{_hoops_RPASC,	_hoops_GRRCR ("UnderlinePosition")},
	{_hoops_APASC,	_hoops_GRRCR ("UnderlineThickness")},
	{_hoops_PPASC,				_hoops_GRRCR ("Version")},
	{_hoops_HPASC,				_hoops_GRRCR ("Notice")},
	{_hoops_IPASC,				_hoops_GRRCR ("FontBBox")},
	{_hoops_CPASC,			_hoops_GRRCR ("CapHeight")},
	{_hoops_SPASC,				_hoops_GRRCR ("XHeight")},
	{_hoops_GHASC,				_hoops_GRRCR ("Descender")},
	{_hoops_RHASC,				_hoops_GRRCR ("Ascender")},
	{_hoops_AHASC,	_hoops_GRRCR ("StartCharMetrics")},
	{_hoops_PHASC,		_hoops_GRRCR ("EndCharMetrics")},
	{_hoops_HHASC,		_hoops_GRRCR ("StartKernData")},
	{_hoops_IHASC,		_hoops_GRRCR ("StartKernPairs")},
	{_hoops_CHASC,		_hoops_GRRCR ("EndKernPairs")},
	{_hoops_SHASC,			_hoops_GRRCR ("EndKernData")},
	{_hoops_GIASC,		_hoops_GRRCR ("StartComposites")},
	{_hoops_RIASC,		_hoops_GRRCR ("EndComposites")},
	{_hoops_AIASC,		_hoops_GRRCR ("EndFontMetrics")},
	{_hoops_SRASC,				_hoops_GRRCR ("")},
};

/*
 * _hoops_HSCAR _hoops_SGS _hoops_RHGSR _hoops_HCPH _hoops_IS _hoops_SRAC _hoops_SICAR
 */
struct _hoops_HIASC {
	float				width, height;
	FILE alter			*fp;
	bool				_hoops_IIASC,
						_hoops_CIASC,
						_hoops_SIASC,
						_hoops_GCASC;
	int					_hoops_RCASC;
	short				_hoops_CIACC;
	_hoops_GARRR			_hoops_RPICC,
						_hoops_ACASC,
						_hoops_PCASC;
	float				_hoops_HCASC;
	Driver_Color		_hoops_ARSRI;
	Line_Style			_hoops_CRSRI;
	int					_hoops_ICASC,
						_hoops_CCASC;
	int					_hoops_SCASC,
						_hoops_GSASC;
	_hoops_RRASC alter	*_hoops_GPPIR;
	_hoops_PRASC alter	*_hoops_RSASC;
	bool				_hoops_PRGGH;
	bool				_hoops_ASASC;
	int					_hoops_HAP;
	int					_hoops_PSASC;

	_hoops_GGAGR			*_hoops_HSASC;
	Image			*_hoops_ISASC;

	_hoops_PCCGA		_hoops_CSASC;
	bool				_hoops_SSASC;
	bool				_hoops_GGPSC;
	bool				_hoops_PPICC;
};


local char const _hoops_RGPSC[] =
				"Error writing PostScript file - disk may be full";


/* _hoops_ISPR _hoops_IH _hoops_HPCS */
#define _hoops_AGPSC(state)					\
	do if (ferror ((state)->fp)) {		\
		HE_ERROR (HEC_POSTSCRIPT_DRIVER, HES_DISK_FULL, \
				  _hoops_RGPSC);			\
		state->_hoops_PRGGH = true;				\
		return;							\
	} while (false)

/* _hoops_PSHR _hoops_IH _hoops_SICAR _hoops_PGAP _hoops_HS _hoops_IRS _hoops_ASRC _hoops_PIRA */
#define _hoops_PGPSC(state, retval)			\
	do if (ferror ((state)->fp)) {		\
		HE_ERROR (HEC_POSTSCRIPT_DRIVER, HES_DISK_FULL, \
				  _hoops_RGPSC);			\
		state->_hoops_PRGGH = true;				\
		return	(retval);				\
	} while (false)

/* _hoops_PPR _hoops_IH _hoops_IIHP _hoops_SR _hoops_PAH'_hoops_RA _hoops_ASRC */
#define _hoops_HGPSC(state)					\
	do if (ferror ((state)->fp)) {		\
		HE_ERROR (HEC_POSTSCRIPT_DRIVER, HES_DISK_FULL, \
				  _hoops_RGPSC);			\
		state->_hoops_PRGGH = true;				\
	} while (false)

/* _hoops_PPCAR _hoops_RAACR _hoops_IIGR _hoops_HIRAA _hoops_GGSR _hoops_PIH (_hoops_CPGII & _hoops_PIAP _hoops_CHHA _hoops_PRSAR) */
#define _hoops_ACIAI(s)		do {fprintf (fp, s);	_hoops_AGPSC (state);} while (false)
#define _hoops_IGPSC(s,v)	do {fprintf (fp, s, v); _hoops_AGPSC (state);} while (false)
#define _hoops_CGPSC(s)	do {fprintf (fp, s);	_hoops_PGPSC (state, 0L);} while (false)
#define _hoops_SGPSC(s,v) do {fprintf (fp, s, v); _hoops_PGPSC (state, 0L);} while (false)
#define _hoops_GRPSC(s)	do {fprintf (fp, s);	_hoops_HGPSC (state);} while (false)
#define _hoops_RRPSC(s,v) do {fprintf (fp, s, v); _hoops_HGPSC (state);} while (false)

#define _hoops_ARPSC(dc)			((_hoops_HIASC alter *)(dc->data))


#if HOOPS_BIGENDIAN

local void _hoops_PRPSC (void) {
	_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					   "Datasize error in PostScript driver byte-swap");
}


# define _hoops_HRPSC(x) do {										\
			char *	_hoops_IRPSC = (char *)&(x);		\
			char	_hoops_CRPSC;						\
			if (sizeof (x) == 2) {								\
				_hoops_CRPSC = _hoops_IRPSC[0];							\
				_hoops_IRPSC[0] = _hoops_IRPSC[1];						\
				_hoops_IRPSC[1] = _hoops_CRPSC;							\
			}													\
			else if (sizeof (x) == 4) {							\
				_hoops_CRPSC = _hoops_IRPSC[0];							\
				_hoops_IRPSC[0] = _hoops_IRPSC[3];						\
				_hoops_IRPSC[3] = _hoops_CRPSC;							\
				_hoops_CRPSC = _hoops_IRPSC[1];							\
				_hoops_IRPSC[1] = _hoops_IRPSC[2];						\
				_hoops_IRPSC[2] = _hoops_CRPSC;							\
			}													\
			else if (sizeof (x) != 1) {							\
				_hoops_PRPSC ();									\
			}													\
		} while (0)
#else
# define _hoops_HRPSC(x) _hoops_GRSSH(x)
#endif


/*
 * _hoops_RAPH
 */

/*
 * _hoops_RRPP _hoops_IRS _hoops_RSRA _hoops_III _hoops_HII _hoops_IRS _hoops_RGHR
 */

local void _hoops_SRPSC (
	void alter				*_hoops_GAPSC,
	char alter				*buffer,
	char alter				*_hoops_ARHR,
	char alter				* alter *_hoops_RAPSC,
	char alter				*line) {
	char alter				*_hoops_ASAPR = *_hoops_RAPSC;
	_hoops_HCRPR					_hoops_GGHGA, _hoops_RGHGA;
	int						_hoops_GSHHH;

	if (_hoops_ASAPR == _hoops_ARHR) {
		_hoops_ASAPR = buffer;
		HI_Read_File_Buffer (_hoops_GAPSC, buffer,
							 &_hoops_GSHHH, (int)(POINTER_SIZED_INT)(_hoops_ARHR - buffer),
							 &_hoops_GGHGA, &_hoops_RGHGA);
	}

	while (*_hoops_ASAPR == '\0' || *_hoops_ASAPR == '\r' || *_hoops_ASAPR == '\n') {
		++_hoops_ASAPR;
		if (_hoops_ASAPR == _hoops_ARHR) {
			_hoops_ASAPR = buffer;
			HI_Read_File_Buffer (_hoops_GAPSC, buffer,
								 &_hoops_GSHHH, (int)(POINTER_SIZED_INT)(_hoops_ARHR - buffer),
								 &_hoops_GGHGA, &_hoops_RGHGA);
		}
	}

	_hoops_RGGA (*_hoops_ASAPR == '\0' || *_hoops_ASAPR == '\r' || *_hoops_ASAPR == '\n') {
		*line++ = *_hoops_ASAPR++;
		if (_hoops_ASAPR == _hoops_ARHR) {
			_hoops_ASAPR = buffer;
			HI_Read_File_Buffer (_hoops_GAPSC, buffer,
								 &_hoops_GSHHH, (int)(POINTER_SIZED_INT)(_hoops_ARHR - buffer),
								 &_hoops_GGHGA, &_hoops_RGHGA);
		}
	}

	*line++ = '\0';
	*_hoops_RAPSC = _hoops_ASAPR;
}


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
 * _hoops_RH _hoops_RPPSC _hoops_RHPP'_hoops_GRI _hoops_RHSAR _hoops_PIH , _hoops_SSS _hoops_RH _hoops_RSHCR
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
 * _hoops_RH _hoops_RPPSC _hoops_RHPP'_hoops_GRI _hoops_RHSAR _hoops_PIH.
 */

local void _hoops_HPPSC (
	char const			*family_name,
	char const			*_hoops_RRHRI,
	short const			*_hoops_ARASC,
	_hoops_HIASC alter		*state) {
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
	_hoops_HIASC alter			*state,
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
	_hoops_HIASC alter	*state,
	RGBAS32 const	*color) {
	FILE alter		*fp = state->fp;

	if (state->_hoops_PRGGH) return;

	if (state->_hoops_ARSRI != *color) {
		if (color->r == color->g &&
				color->r == color->b) {
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
		state->_hoops_ARSRI = *color;
	}
}


local bool start_device (
	Display_Context alter	*dc) {
	_hoops_HIASC alter				*state;
	FILE alter					*fp;
	char const					*_hoops_RPPA;

	if ((fp = fopen (dc->_hoops_PCRSR, "w")) == null) {
	   HE_ERROR (HEC_POSTSCRIPT_DRIVER, HES_FILE_OPEN,
				 Sprintf_S (null,
							"Can not open PostScript driver output file - %s",
							dc->_hoops_PCRSR));
	   return false;
	}


	ZALLOC (state, _hoops_HIASC);

	dc->data = (void alter *) state;
	HD_Get_Bit_Patterns (dc, true);


	state->fp = fp;
	state->_hoops_ICASC = -1;
	state->_hoops_CCASC = -1;
	state->_hoops_SCASC = 1;
	state->_hoops_HAP = 75;
/* #_hoops_IHS _hoops_CPPSC */
#if 1
	state->_hoops_PSASC = _hoops_SGASC;
#else
	state->_hoops_PSASC = _hoops_IGASC;
#endif
	state->_hoops_SSASC = true;
	state->_hoops_GGPSC = true;

	_hoops_RPPA = dc->_hoops_PCRSR + dc->_hoops_HCRSR - 5;	/* 5 == "._hoops_HHSPI\0" */

	/* _hoops_RHAP _hoops_RSIRR _hoops_RSGR _hoops_GGR "._hoops_HHSPI" */
	if (dc->_hoops_HCRSR >= 5 &&
		_hoops_RPPA[0] == '.' && _hoops_RPPA[1] == 'e' && _hoops_RPPA[2] == 'p' && _hoops_RPPA[3] == 's')
		state->_hoops_IIASC = true;

	/* _hoops_CCSCI _hoops_GAHAH _hoops_HCSP _hoops_PAH _hoops_CHASA _hoops_AHSGH _hoops_IIHA _hoops_GPP _hoops_RGHR _hoops_RSIRR.
	 * _hoops_GARP _hoops_SPPSC (_hoops_HAR _hoops_SSCC _hoops_HGPS) _hoops_AAP _hoops_CHR:
	 *
	 *	_hoops_CAGA												--	_hoops_GHPSC
	 *	_hoops_RHPSC										   \
	 *	_hoops_AHPSC										\
	 *	_hoops_PHPSC			   -- _hoops_CRRPR _hoops_PSSCI		 \
	 *	_hoops_RHPSC-_hoops_HHPSC		\							  >---	_hoops_IHPSC
	 *	_hoops_AHPSC-_hoops_HHPSC		 >---_hoops_SGH _hoops_IIGR (_hoops_CHPSC) _hoops_HRGR _hoops_IHRI	 /
	 *	_hoops_PHPSC-_hoops_HHPSC		/  -- _hoops_CRRPR _hoops_PSSCI		/
	 *	_hoops_ASHCI-_hoops_RHPSC			   -- _hoops_CRRPR _hoops_SHPSC		   /
	 */
	if (dc->options._hoops_HAPIR) {
		_hoops_RPPA = dc->options._hoops_HAPIR->name.text;
		switch (dc->options._hoops_HAPIR->name.length) {
			case 0:
			default:		break;

			case 2: {
				if (_hoops_RPPA[0] == 'p' && _hoops_RPPA[1] == 's')
					state->_hoops_IIASC = false;
			}	break;

			case 3: {
				if (_hoops_RPPA[0] == 'e' && _hoops_RPPA[1] == 'p' && _hoops_RPPA[2] == 's')
					state->_hoops_IIASC = true;
			}	break;

			case 4: {
				if (_hoops_RPPA[0] == 'e' && _hoops_RPPA[1] == 'p' && _hoops_RPPA[2] == 's') switch (_hoops_RPPA[3]) {
					case 'i':		state->_hoops_CIASC = true;		_hoops_HHHI;

					case 'f':		state->_hoops_IIASC = true;		break;

					default:		break;
				}
			}	break;

			case 7: {
				if (_hoops_RPPA[0] == 'd' && _hoops_RPPA[1] == 'o' && _hoops_RPPA[2] == 's' &&
					_hoops_RPPA[3] == '-' &&
					_hoops_RPPA[4] == 'e' && _hoops_RPPA[5] == 'p' && _hoops_RPPA[6] == 's') {
					state->_hoops_IIASC = true;
					state->_hoops_CIASC = true;
					state->_hoops_SIASC = true;
				}
			}	break;

			case 9: {
				if (_hoops_RPPA[0] == 'e' && _hoops_RPPA[1] == 'p' && _hoops_RPPA[2] == 's' &&
					_hoops_RPPA[3] == '-' && _hoops_RPPA[4] == 'a' && _hoops_RPPA[5] == 't' &&
					_hoops_RPPA[6] == 'e' && _hoops_RPPA[7] == 'n' && _hoops_RPPA[8] == 'd') {
					state->_hoops_IIASC = true;
					state->_hoops_GCASC = true;
				}
			}	break;

			case 10: {
				if (_hoops_RPPA[0] == 'e' && _hoops_RPPA[1] == 'p' && _hoops_RPPA[2] == 's' &&
					(_hoops_RPPA[3] == 'f' || _hoops_RPPA[3] == 'i') &&
					_hoops_RPPA[4] == '-' && _hoops_RPPA[5] == 'a' && _hoops_RPPA[6] == 't' &&
					_hoops_RPPA[7] == 'e' && _hoops_RPPA[8] == 'n' && _hoops_RPPA[9] == 'd') {
					if (_hoops_RPPA[3] == 'i')
						state->_hoops_CIASC = true;
					state->_hoops_IIASC = true;
					state->_hoops_GCASC = true;
				}
			}	break;
		}
	}

	if (state->_hoops_CIASC)
		dc->_hoops_ACPGR->update = _hoops_GGASC;

	return true;
}


local void stop_device (
	Display_Context alter *dc) {
	_hoops_HIASC alter				*state = _hoops_ARPSC (dc);
	FILE alter					*fp = state->fp;
	_hoops_RRASC alter			*_hoops_PPPSC;
	_hoops_PRASC alter	*_hoops_GIPSC;

	if (!state->_hoops_PRGGH)
		_hoops_GRPSC ("cleartomark end\n");
	if (!state->_hoops_PRGGH)
		_hoops_GRPSC ("%%%%Trailer\n");

	if (!state->_hoops_PRGGH && state->_hoops_GCASC) {
		fprintf (fp, "%%%%BoundingBox: 0 0 %d %d\n", (int)(state->width), (int)(state->height));
		_hoops_HGPSC (state);
	}

	if (!state->_hoops_PRGGH)
		_hoops_GRPSC ("%%%%EOF\n");


	if (state->_hoops_SIASC && state->_hoops_RCASC != 0) {
		Integer32	_hoops_RIPSC;
		Integer32	_hoops_RIHRH;

		_hoops_RIPSC = ftell (fp);

		fseek (fp, 8, SEEK_SET);

		_hoops_RIHRH = _hoops_RIPSC - state->_hoops_RCASC;
		_hoops_HRPSC (_hoops_RIHRH);
		fwrite (&_hoops_RIHRH, 1, sizeof (Integer32), fp);
	}

	fclose (fp);


	/* _hoops_APSHR _hoops_GH _hoops_GII _hoops_PPGS _hoops_SGS _hoops_CSAP _hoops_PSPP.
	** _hoops_HGI _hoops_CRRPR:
	**			_hoops_AIPSC
	**			_hoops_PIPSC
	**			_hoops_PIAP (_hoops_HIPSC)
	*/
	_hoops_PPPSC = state->_hoops_GPPIR;
	while (_hoops_PPPSC != null) {
		_hoops_PPPSC = state->_hoops_GPPIR->next;
		FREE(state->_hoops_GPPIR, _hoops_RRASC);
		state->_hoops_GPPIR = _hoops_PPPSC;
	}

	_hoops_GIPSC = state->_hoops_RSASC;
	while (_hoops_GIPSC != null) {
		_hoops_GIPSC = state->_hoops_RSASC->next;
		FREE(state->_hoops_RSASC, _hoops_PRASC);
		state->_hoops_RSASC = _hoops_GIPSC;
	}

	if (state->_hoops_ISASC != null)
		_hoops_HPRH (state->_hoops_ISASC);
	if (state->_hoops_HSASC != null) {
		_hoops_HPRH (state->_hoops_HSASC);
	}

	FREE(state, _hoops_HIASC);
	dc->data = null;
}

/* _hoops_HGI _hoops_API _hoops_RGAR _hoops_CRGS _hoops_AGAH _hoops_RH _hoops_SHIR _hoops_IGIR _hoops_IH _hoops_RH _hoops_HGPPC _hoops_RHPP. */
local void
_hoops_IIPSC(Display_Context alter * dc)
{
	float const width = 8.5f;
	float const height = 11.0f;
	float const _hoops_HGII = 75;

	dc->_hoops_PGCC._hoops_ARISR.x = 0;
	dc->_hoops_PGCC._hoops_ARISR.y = 0;
	dc->_hoops_PGCC._hoops_PRPSR.x = (int) (_hoops_HGII * width);
	dc->_hoops_PGCC._hoops_PRPSR.y = (int) (_hoops_HGII * height);
	dc->_hoops_PGCC.size.x = width * 2.54;
	dc->_hoops_PGCC.size.y = height * 2.54;

	return;
}

/* _hoops_HGI _hoops_API _hoops_SAGGR _hoops_RH _hoops_AAP _hoops_HII _hoops_AGAH _hoops_IH _hoops_IGIR, _hoops_HGISR _hoops_RH _hoops_HGPPC _hoops_RHPP'_hoops_GRI _hoops_IGIR
 * _hoops_PPR _hoops_IGISR _hoops_GGR _hoops_RH _hoops_HSH _hoops_GGR _hoops_SCGR _hoops_HIS _hoops_AGAH _hoops_CGISR _hoops_PCPA _hoops_IGIR _hoops_SR _hoops_IGRC _hoops_ARP. */
local void
_hoops_CIPSC(Display_Context alter * dc)
{
	_hoops_HIASC *state = _hoops_ARPSC (dc);

	state->_hoops_HAP = dc->options._hoops_GHHSR;

	if (dc->options._hoops_SPHSR.x != -1) {
		state->width = (72 * dc->options._hoops_SPHSR.x / 2.54f);
		state->height = (72 * dc->options._hoops_SPHSR.y / 2.54f);
	} else {
		state->width = (72 * dc->_hoops_PGCC.size.x / 2.54f);
		state->height = (72 * dc->_hoops_PGCC.size.y / 2.54f);
	}

	if (state->width <= 0 || state->height <= 0) {
		HE_ERROR (HEC_POSTSCRIPT_DRIVER, HES_INVALID_WIDTH_OR_HEIGHT,
			"invalid width and/or height specified in postscript driver");
	}
	if (state->_hoops_HAP < 10) {
		HE_ERROR (HEC_POSTSCRIPT_DRIVER, HES_INVALID_SIZE,
			"invalid hardcopy resolution specified in postscript driver");
	}

	dc->current._hoops_HAP.x = state->_hoops_HAP / 2.54f;
	dc->current._hoops_HAP.y = state->_hoops_HAP / 2.54f;
	dc->current._hoops_PRPSR.x = (int) (state->_hoops_HAP * state->width / 72.0f);
	dc->current._hoops_PRPSR.y = (int) (state->_hoops_HAP * state->height / 72.0f);

	dc->current._hoops_ARISR.x = dc->_hoops_PGCC._hoops_ARISR.x;
	dc->current._hoops_ARISR.y = dc->_hoops_PGCC._hoops_ARISR.y;
	dc->current.size.x = dc->_hoops_PGCC.size.x;
	dc->current.size.y = dc->_hoops_PGCC.size.y;

	return;
}


local void get_current_info(Display_Context alter * dc)
{
	_hoops_CIPSC(dc);

	return;
}


local void get_physical_info (Display_Context * dc) {
	_hoops_HIASC *state = _hoops_ARPSC (dc);

        _hoops_IIPSC(dc);

	dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;
	dc->_hoops_PGCC._hoops_PCHSR = _hoops_ACRSC;
	dc->_hoops_PGCC._hoops_CHHSR = _hoops_SHHSR;
	dc->_hoops_PGCC.flags |= _hoops_CAPGH;
	dc->_hoops_PGCC.flags &= ~_hoops_RSHSR;
	dc->_hoops_PGCC.flags &= ~_hoops_PSHSR;
	dc->_hoops_PGCC.flags &= ~_hoops_HSHSR;
	dc->_hoops_PGCC.flags |= _hoops_ISHSR;
	dc->_hoops_PGCC.flags |= _hoops_GIHSR;
	dc->_hoops_PGCC.flags |= _hoops_ISRIP;
	dc->_hoops_PGCC.driver_type = "PostScript";
	dc->_hoops_PGCC._hoops_SCHSR = "$Revision: 1.314 $";
	dc->_hoops_PGCC._hoops_ICHSR = "laser printer";

	dc->flags |= _hoops_CSHSR;

        /* #11903 _hoops_RGAR _hoops_ARP _hoops_SHIR _hoops_III _hoops_SGCR _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_PIP _hoops_IPPSR _hoops_III _hoops_SGCR. */
        if(!dc->options._hoops_HHHSR)
            dc->_hoops_PGCC._hoops_IHHSR = dc->options._hoops_GHHSR/150.0f;


	/* _hoops_HGCR _hoops_PPSCP _hoops_CCH */
	if (BIT (dc->options._hoops_IRARR, _hoops_PGASC))
            state->_hoops_PSASC = _hoops_CGASC;
	else if (BIT (dc->options._hoops_IRARR, _hoops_HGASC))
            state->_hoops_PSASC = _hoops_SGASC;
}


local void _hoops_SIPSC (
	_hoops_HIASC alter	*state) {
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
	_hoops_HIASC alter	*state) {
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

	/* _hoops_IRS _hoops_RPPSC _hoops_RIGR _hoops_IS _hoops_PGSA _hoops_IRS _hoops_ARAS-_hoops_SPCC _hoops_PIGAI _hoops_CSCR */
	fprintf (fp, "/IRLE { GS  4 dict begin\n");
	fprintf (fp, "	/height exch def  /width exch def");
	fprintf (fp, "	/y exch def	 /x exch def\n");
	fprintf (fp, "	x .5 sub y .5 sub translate width height scale\n");
	fprintf (fp, "	width height 8 [width 0 0 height neg 0 height]\n");
	fprintf (fp, "	{IMGRDRLE} false 3 colorimage");
	fprintf (fp, "	end GR } bind def\n");
	_hoops_AGPSC (state);

	/* _hoops_IRS _hoops_RPPSC _hoops_RIGR _hoops_IS _hoops_PGSA _hoops_PCCP _hoops_ARAS-_hoops_SPCC _hoops_PIGAI _hoops_CGHSI */
	fprintf (fp, "/SRLE { GS  3 dict begin\n");
	fprintf (fp, "	/width exch def	 /y exch def  /x exch def\n");
	fprintf (fp, "	x .5 sub y .5 sub translate width 1 scale");
	fprintf (fp, "	width 1 8 [width 0 0 -1 0 1]\n");
	fprintf (fp, "	{IMGRDRLE} false 3 colorimage");
	fprintf (fp, "	end GR } bind def\n");
	_hoops_AGPSC (state);

	/* _hoops_IRS _hoops_RPPSC _hoops_RIGR _hoops_IS _hoops_PGSA _hoops_PCCP _hoops_CCRRP _hoops_CSCR */
	fprintf (fp, "/IMG { GS	 5 dict begin\n");
	fprintf (fp, "	/height exch def  /width exch def");
	fprintf (fp, "	/y exch def	 /x exch def\n");
	fprintf (fp, "	/imgbuf width string def\n");
	fprintf (fp, "	x .5 sub y .5 sub translate width height scale\n");
	fprintf (fp, "	width height 8 [width 0 0 height neg 0 height]\n");
	fprintf (fp, "	{currentfile imgbuf readhexstring pop} false 3 colorimage");
	fprintf (fp, "	end GR } bind def\n");
	_hoops_AGPSC (state);

	/* _hoops_IRS _hoops_RPPSC _hoops_RIGR _hoops_IS _hoops_PGSA _hoops_IRS _hoops_RSRA _hoops_AIR */
	fprintf (fp, "/PIX { GS	 2 dict begin");
	fprintf (fp, "	/y exch def	 /x exch def  /imgbuf 1 string def\n");
	fprintf (fp, "	x .5 sub y .5 sub translate	 1 1 8 [1 0 0 1 neg 0 1]\n");
	fprintf (fp, "	{currentfile imgbuf readhexstring pop} false 3 colorimage");
	fprintf (fp, "	end GR } bind def\n");
	_hoops_AGPSC (state);
}

local void _hoops_RSPSC (
	_hoops_HIASC alter			*state) {
	FILE alter				*fp = state->fp;

	if (state->_hoops_PRGGH) return;

	_hoops_ACIAI ("/reencodedict 12 dict def /ReEncode ");
	_hoops_ACIAI ("{reencodedict begin /newname exch def\n");
	_hoops_ACIAI ("/basefont exch def /basefontdict ");
	_hoops_ACIAI ("basefont findfont def /newfont\n");
	_hoops_ACIAI ("basefontdict maxlength dict def ");
	_hoops_ACIAI ("basefontdict {exch dup /FID ne {dup\n");
	_hoops_ACIAI ("/Encoding eq {exch dup length array ");
	_hoops_ACIAI ("copy newfont 3 1 roll put}{exch newfont\n");
	_hoops_ACIAI ("3 1 roll put} ifelse}{pop pop} ifelse} ");
	_hoops_ACIAI ("forall newfont /FontName newname put\n");
	_hoops_ACIAI ("EncVec aload length 2 idiv {newfont ");
	_hoops_ACIAI ("/Encoding get 3 1 roll put} repeat\n");
	_hoops_ACIAI ("newname newfont definefont pop end} def\n");

	_hoops_ACIAI ("/EncVec [ 8#244 /currency 8#246 ");
	_hoops_ACIAI ("/.notdef 8#250 /hungarumlaut 8#251\n");
	_hoops_ACIAI ("/.notdef 8#252 /ordfeminine 8#254 ");
	_hoops_ACIAI ("/.notdef 8#255 /endash 8#256 /.notdef\n");
	_hoops_ACIAI ("8#257 /emdash 8#260 /ring 8#261 ");
	_hoops_ACIAI ("/.notdef 8#262 /.notdef 8#263 /.notdef\n");
	_hoops_ACIAI ("8#264 /acute 8#265 /.notdef 8#267 ");
	_hoops_ACIAI ("/periodcentered 8#270 /cedilla 8#271\n");
	_hoops_ACIAI ("/.notdef 8#272 /ordmasculine 8#274 ");
	_hoops_ACIAI ("/.notdef 8#275 /.notdef 8#276 /.notdef\n");
	_hoops_ACIAI ("8#300 /Agrave 8#301 /Aacute 8#302 ");
	_hoops_ACIAI ("/Acircumflex 8#303 /Atilde 8#304\n");
	_hoops_ACIAI ("/Adieresis 8#305 /Aring 8#306 /AE ");
	_hoops_ACIAI ("8#307 /Ccedilla 8#310 /Egrave 8#311\n");
	_hoops_ACIAI ("/Eacute 8#312 /Ecircumflex 8#313 ");
	_hoops_ACIAI ("/Edieresis 8#314 /Igrave 8#315 /Iacute\n");
	_hoops_ACIAI ("8#316 /Icircumflex 8#317 /Idieresis ");
	_hoops_ACIAI ("8#320 /.notdef 8#321 /Ntilde 8#322\n");
	_hoops_ACIAI ("/Ograve 8#323 /Oacute 8#324 ");
	_hoops_ACIAI ("/Ocircumflex 8#325 /Otilde 8#326\n");
	_hoops_ACIAI ("/Odieresis 8#327 /.notdef 8#330 ");
	_hoops_ACIAI ("/Oslash 8#331 /Ugrave 8#332 /Uacute\n");
	_hoops_ACIAI ("8#333 /Ucircumflex 8#334 /Udieresis ");
	_hoops_ACIAI ("8#335 /.notdef 8#336 /.notdef 8#337\n");
	_hoops_ACIAI ("/germandbls 8#340 /agrave 8#341 ");
	_hoops_ACIAI ("/aacute 8#342 /acircumflex 8#343\n");
	_hoops_ACIAI ("/atilde 8#344 /adieresis 8#345 /aring ");
	_hoops_ACIAI ("8#346 /ae 8#347 /ccedilla 8#350\n");
	_hoops_ACIAI ("/egrave 8#351 /eacute 8#352 ");
	_hoops_ACIAI ("/ecircumflex 8#353 /edieresis 8#354\n");
	_hoops_ACIAI ("/igrave 8#355 /iacute 8#356 ");
	_hoops_ACIAI ("/icircumflex 8#357 /idieresis 8#360\n");
	_hoops_ACIAI ("/.notdef 8#361 /ntilde 8#362 /ograve ");
	_hoops_ACIAI ("8#363 /oacute 8#364 /ocircumflex 8#365\n");
	_hoops_ACIAI ("/otilde 8#366 /odieresis 8#367 ");
	_hoops_ACIAI ("/.notdef 8#370 /oslash 8#371 /ugrave\n");
	_hoops_ACIAI ("8#372 /uacute 8#373 /ucircumflex 8#374 ");
	_hoops_ACIAI ("/udieresis 8#375 /.notdef 8#376\n");
	_hoops_ACIAI ("/.notdef 8#377 /ydieresis 8#200 /acute ");
	_hoops_ACIAI ("8#201 /grave 8#202 /circumflex 8#203\n");
	_hoops_ACIAI ("/tilde 8#204 /dieresis 8#205 /cedilla ");
	_hoops_ACIAI ("8#206 /ring 8#207 /dotlessi ] def\n");

	_hoops_ACIAI ("/Courier /RCourier ReEncode ");
	_hoops_ACIAI ("/Courier-Oblique /RCourier-Oblique ReEncode\n");
	_hoops_ACIAI ("/Courier-Bold /RCourier-Bold ReEncode\n");
	_hoops_ACIAI ("/Courier-BoldOblique /RCourier-BoldOblique ReEncode\n");
	_hoops_ACIAI ("/Helvetica /RHelvetica ReEncode ");
	_hoops_ACIAI ("/Helvetica-Bold /RHelvetica-Bold ReEncode\n");
	_hoops_ACIAI ("/Helvetica-Oblique /RHelvetica-Oblique ReEncode\n");
	_hoops_ACIAI ("/Helvetica-BoldOblique /RHelvetica-BoldOblique ReEncode\n");
	_hoops_ACIAI ("/Times-Roman /RTimes-Roman ReEncode ");
	_hoops_ACIAI ("/Times-Italic /RTimes-Italic ReEncode\n");
	_hoops_ACIAI ("/Times-Bold /RTimes-Bold ReEncode ");
	_hoops_ACIAI ("/Times-BoldItalic /RTimes-BoldItalic ReEncode\n");
}


#define _hoops_ASPSC(x)		((float)(x) / state->_hoops_HAP * 72.0f + 0.5f)

struct _hoops_PSPSC {
	unsigned char		id[4];
	Integer32				_hoops_RCASC;
	Integer32				_hoops_RIHRH;
	Integer32				_hoops_HSPSC;
	Integer32				_hoops_ISPSC;
	Integer32				_hoops_CSPSC;
	Integer32				_hoops_SSPSC;
	unsigned short				_hoops_GRPPA;
};

struct _hoops_GGHSC {
	unsigned short		_hoops_RGHSC;
	unsigned short		version;
	unsigned Integer32		offset;
};

struct _hoops_AGHSC {
#		define	_hoops_PGHSC		254
#		define	_hoops_HGHSC		256
#		define	_hoops_IGHSC		257
#		define	_hoops_CGHSC	258
#		define	_hoops_SGHSC		259
#		define	_hoops_GRHSC		262
#		define	_hoops_RRHSC		273
#		define	_hoops_ARHSC	277
#		define	_hoops_PRHSC		278
#		define	_hoops_HRHSC	279
#		define	_hoops_IRHSC				282
#		define	_hoops_CRHSC				283
#		define	_hoops_SRHSC		284
#		define	_hoops_GAHSC			296

	unsigned short		tag;

#		define	_hoops_RAHSC				1
#		define	_hoops_AAHSC				2
#		define	_hoops_PAHSC				3
#		define	_hoops_HAHSC				4
#		define	_hoops_IAHSC			5

	unsigned short		_hoops_HCAAR;

	unsigned Integer32		length;
	unsigned Integer32		offset;
};


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

local POINTER_SIZED_INT get_outer_window (
	Display_Context const	*_hoops_RSAAI) {
	Display_Context alter	*dc = (Display_Context alter*) _hoops_RSAAI;
	_hoops_HIASC alter				*state = _hoops_ARPSC (dc);
	FILE alter					*fp = state->fp;

	if (state->_hoops_PRGGH) return 0L;

        if (dc->options._hoops_SPHSR.x != -1) {
                dc->_hoops_PGCC.extent.right = state->_hoops_HAP * dc->options._hoops_SPHSR.x / 2.54f;
                dc->_hoops_PGCC.extent.top = state->_hoops_HAP * dc->options._hoops_SPHSR.y / 2.54f;
        } else {
                dc->_hoops_PGCC.extent.right = state->_hoops_HAP * 8.5f;
                dc->_hoops_PGCC.extent.top = state->_hoops_HAP * 11.0f;
        }
        dc->_hoops_PGCC.extent.left = 0;
        dc->_hoops_PGCC.extent.bottom = 0;

        dc->_hoops_PGCC._hoops_PRPSR.x = (int) (dc->_hoops_PGCC.extent.right);
        dc->_hoops_PGCC._hoops_PRPSR.y = (int) (dc->_hoops_PGCC.extent.top);

	if (state->_hoops_CIACC == 0) {
		if (state->_hoops_ISASC != null && state->_hoops_SIASC) {
			Image	*image = state->_hoops_ISASC;
			_hoops_PSPSC		_hoops_GPHSC;
			_hoops_GGHSC			_hoops_RPHSC;
			unsigned short		_hoops_APHSC;
			int					_hoops_SSPSC;
			int					_hoops_PPHSC;
			int					_hoops_HPHSC, _hoops_IPHSC;
			int					_hoops_CPHSC;
			int					_hoops_SPHSC;
			int					_hoops_GHHSC;
			int					_hoops_CASGC;
			unsigned short		bpp = 8;
			long				tmp;
			int					row, col;
			Integer32				_hoops_RHHSC = 1;

			/* _hoops_GGI _hoops_IRS _hoops_GRH _hoops_RGSPR _hoops_IPSH _hoops_IRS _hoops_IHGP _hoops_PSRAI _hoops_CSCR */

			_hoops_CASGC = 3 * image->width * image->height;
			_hoops_APHSC = 14;

			_hoops_SSPSC = sizeof (_hoops_GGHSC);					/* _hoops_RGSPR */
			_hoops_SSPSC += sizeof (unsigned short);				/* _hoops_IRCCP _hoops_RPR */
			_hoops_SSPSC += _hoops_APHSC * sizeof (_hoops_AGHSC);	/* _hoops_AGGGI */
			_hoops_SSPSC += sizeof (Integer32);						/* _hoops_RSGR _hoops_IIGR _hoops_IRCCP */

			_hoops_PPHSC = _hoops_SSPSC;	/* _hoops_RPHR _hoops_RAS _hoops_AGGGI */
			_hoops_SSPSC += 3 * sizeof (unsigned short);			/* _hoops_AHHSC */

			_hoops_HPHSC = _hoops_SSPSC;
			_hoops_SSPSC += 2 * sizeof (Integer32);			/* _hoops_PHHSC */

			_hoops_IPHSC = _hoops_SSPSC;
			_hoops_SSPSC += 2 * sizeof (Integer32);			/* _hoops_HHHSC */

			_hoops_CPHSC = _hoops_SSPSC;
			_hoops_SSPSC += image->height * sizeof (Integer32);		/* _hoops_ISIA */

			_hoops_SPHSC = _hoops_SSPSC;
			_hoops_SSPSC += image->height * sizeof (Integer32);		/* _hoops_IIRGR */

			_hoops_GHHSC = _hoops_SSPSC;
			_hoops_SSPSC += _hoops_CASGC;							/* _hoops_CSCR _hoops_PIH */



			_hoops_GPHSC.id[0] = 0xC5;
			_hoops_GPHSC.id[1] = 0xD0;
			_hoops_GPHSC.id[2] = 0xD3;
			_hoops_GPHSC.id[3] = 0xC6;
			_hoops_GPHSC._hoops_RCASC = sizeof (_hoops_PSPSC) + _hoops_SSPSC;
			_hoops_GPHSC._hoops_RIHRH = -1; /* _hoops_RRP _hoops_IS _hoops_HGIHR _hoops_RGR _hoops_ARPP _hoops_CSGR _hoops_RGHR */
			_hoops_GPHSC._hoops_ISPSC = 0;
			_hoops_GPHSC._hoops_ISPSC = 0;
			_hoops_GPHSC._hoops_CSPSC = sizeof (_hoops_PSPSC);
			_hoops_GPHSC._hoops_SSPSC = _hoops_SSPSC;
			_hoops_GPHSC._hoops_GRPPA = (unsigned short)0xFFFF;

			/* _hoops_RGAR _hoops_AGCR 3 _hoops_CHR _hoops_HAR _hoops_AAPCA _hoops_GCSRR */
			_hoops_HRPSC (_hoops_GPHSC._hoops_RCASC);
			_hoops_HRPSC (_hoops_GPHSC._hoops_CSPSC);
			_hoops_HRPSC (_hoops_GPHSC._hoops_SSPSC);

			fwrite (&_hoops_GPHSC, 1, sizeof (_hoops_PSPSC), fp);

			state->_hoops_RCASC = _hoops_GPHSC._hoops_RCASC;


			_hoops_RPHSC._hoops_RGHSC = 'I' << 8 | 'I';
			_hoops_RPHSC.version = 42;
			_hoops_RPHSC.offset = sizeof (_hoops_GGHSC);

			_hoops_HRPSC (_hoops_RPHSC.version);
			_hoops_HRPSC (_hoops_RPHSC.offset);
			fwrite (&_hoops_RPHSC, 1, sizeof (_hoops_GGHSC), fp);

			_hoops_HRPSC (_hoops_APHSC);
			fwrite (&_hoops_APHSC, 1, sizeof (unsigned short), fp);

			_hoops_CAHSC (fp, _hoops_PGHSC,	   _hoops_HAHSC,  1, 0);
			_hoops_CAHSC (fp, _hoops_HGHSC,	   _hoops_PAHSC, 1, image->width);
			_hoops_CAHSC (fp, _hoops_IGHSC,	   _hoops_PAHSC, 1, image->height);
			_hoops_CAHSC (fp, _hoops_CGHSC,   _hoops_PAHSC, 3, _hoops_PPHSC);
			_hoops_CAHSC (fp, _hoops_SGHSC,	   _hoops_PAHSC, 1, 1);
			_hoops_CAHSC (fp, _hoops_GRHSC,	   _hoops_PAHSC, 1, 2);
			_hoops_CAHSC (fp, _hoops_RRHSC,	   _hoops_HAHSC,  image->height, _hoops_SPHSC);
			_hoops_CAHSC (fp, _hoops_ARHSC, _hoops_PAHSC, 1, 3);
			_hoops_CAHSC (fp, _hoops_PRHSC,	   _hoops_HAHSC,  1, 1);
			_hoops_CAHSC (fp, _hoops_HRHSC, _hoops_HAHSC,  image->height, _hoops_CPHSC);
			_hoops_CAHSC (fp, _hoops_IRHSC,			   _hoops_IAHSC, 1, _hoops_HPHSC);
			_hoops_CAHSC (fp, _hoops_CRHSC,			   _hoops_IAHSC, 1, _hoops_IPHSC);
			_hoops_CAHSC (fp, _hoops_SRHSC,	   _hoops_PAHSC, 1, 1);
			_hoops_CAHSC (fp, _hoops_GAHSC,		   _hoops_PAHSC, 1, 2);
			tmp = 0;
			fwrite (&tmp, 1, sizeof (Integer32), fp);

			_hoops_HRPSC (bpp);
			fwrite (&bpp, 1, sizeof (unsigned short), fp);
			fwrite (&bpp, 1, sizeof (unsigned short), fp);
			fwrite (&bpp, 1, sizeof (unsigned short), fp);

			/* _hoops_PHHSC & _hoops_HHHSC _hoops_GIPR _hoops_SAHR 1/1 */
			_hoops_HRPSC (_hoops_RHHSC);
			fwrite (&_hoops_RHHSC, 1, sizeof (Integer32), fp);
			fwrite (&_hoops_RHHSC, 1, sizeof (Integer32), fp);
			fwrite (&_hoops_RHHSC, 1, sizeof (Integer32), fp);
			fwrite (&_hoops_RHHSC, 1, sizeof (Integer32), fp);

			/* _hoops_HCR _hoops_IIRGR _hoops_PSHR _hoops_SPCC */
			tmp = 3*image->width;
			_hoops_HRPSC (tmp);
			for (row = 0; row < image->height; row++)
				fwrite (&tmp, 1, sizeof (Integer32), fp);

			/* _hoops_SHI _hoops_IS _hoops_PIH _hoops_IH _hoops_GRR _hoops_CGGR */
			for (row = 0; row < image->height; row++) {
				tmp = _hoops_GHHSC + row * 3*image->width;
				_hoops_HRPSC (tmp);
				fwrite (&tmp, 1, sizeof (Integer32), fp);
			}

			for (row = 0; row < image->height; row++) {
				RGBAS32 const * pp = (RGBAS32 alter *)image->rasters[row];

				for (col = 0; col < image->width; col++) {
					fwrite (&pp->r, 1, sizeof (unsigned char), fp);
					fwrite (&pp->g, 1, sizeof (unsigned char), fp);
					fwrite (&pp->b, 1, sizeof (unsigned char), fp);
					pp++;
				}
			}
		}

		if (!state->_hoops_IIASC)
			_hoops_CGPSC ("%%!PS-Adobe-2.0\n");
		else
			_hoops_CGPSC ("%%!PS-Adobe-2.0 EPSF-1.2\n");


		if (state->_hoops_GCASC) {
			/* _hoops_APSR _hoops_IASC _hoops_AHCRR _hoops_PISI _hoops_IS _hoops_RSGR _hoops_IIGR _hoops_RGHR */
			_hoops_CGPSC ("%%%%BoundingBox: (atend)\n");
		}
		else {
			fprintf (fp, "%%%%BoundingBox: 0 0 %d %d\n", (int)(state->width), (int)(state->height));
			_hoops_PGPSC (state, 0L);
		}

		fprintf (fp, "%%%%Creator: HOOPS %0.2f-%d\n",
				 (float)HOOPS_VERSION / 100.0f, HOOPS_SUBVERSION);
		_hoops_PGPSC (state, 0L);

		if (dc->options._hoops_IAPIR.length != 0) {
			fprintf (fp, "%%%%Title: %s\n",
						Sprintf_N (null, "%n", &dc->options._hoops_IAPIR));
			_hoops_PGPSC (state, 0L);
		}

		_hoops_CGPSC ("%%%%EndComments\n");

		/* _hoops_IHHSC _hoops_CSCR (_hoops_RPP _hoops_IRPR) */
		if (state->_hoops_ISASC != null && !state->_hoops_SIASC) {
			Image	*image = state->_hoops_ISASC;
			int			bpp = 4;
			int			row, col;

			/* _hoops_RPGH: _hoops_IGAA _hoops_APPS _hoops_AHHSC _hoops_APGR-_hoops_IIGR-_hoops_ACCAI-_hoops_PIH */
			fprintf (fp, "%%%%BeginPreview: %d %d %d %d\n",
						image->width/4, image->height/4,
						bpp, image->height/4);	/* _hoops_APGR == _hoops_APPS, _hoops_PSP _hoops_APIGP */
			_hoops_PGPSC (state, 0L);

			for (row = 0; row < image->height; row+=4) {
				_hoops_CGPSC ("%%");

				for (col = 0; col < image->width; col+=4) {
					int			_hoops_HAGR = 0;
					int			_hoops_PIAGI, _hoops_ARCAR;

					for (_hoops_PIAGI=0; _hoops_PIAGI<4; _hoops_PIAGI++) {
						RGBAS32 const * pp;

						pp = (RGBAS32 alter *)image->rasters[row+_hoops_PIAGI] + col;

						for (_hoops_ARCAR=0; _hoops_ARCAR<4; _hoops_ARCAR++) {
							_hoops_HAGR += pp->r + pp->g + pp->b;
							pp++;
						}
					}

					/* _hoops_CHHSC _hoops_HRGR _hoops_RRAS _hoops_IIGR 16 _hoops_ASPA * 3 _hoops_GRIP * 8 _hoops_SIH,
					** _hoops_CSRA _hoops_IS _hoops_IRS _hoops_RSRA 4-_hoops_IGRH _hoops_PIRA */
					_hoops_HAGR = (_hoops_HAGR / 3) >> 4 >> 4;

					_hoops_SGPSC ("%X", 0x0F - _hoops_HAGR);
				}
				if ((image->width & 1) != 0)
					_hoops_CGPSC ("0");

				_hoops_CGPSC ("\n");
			}

			_hoops_CGPSC ("%%%%EndPreview\n");
		}

		/* _hoops_PPIP _hoops_PSIGA _hoops_CIGR _hoops_IS _hoops_ASAC _hoops_GC _hoops_GGR _hoops_IIPR _hoops_RGHR */
		_hoops_CGPSC ("%%%%BeginProlog\n");
		_hoops_CGPSC ("240 dict begin\n/GS {gsave} bind def /GR {grestore} bind def\n");
		_hoops_CGPSC ("/NP {newpath} bind def /CP {closepath} bind def\n");
		_hoops_CGPSC ("/TR {translate} bind def /CRP {currentpoint} bind def\n");
		_hoops_CGPSC ("/MT {moveto} bind def /LT {lineto} bind def\n");
		_hoops_CGPSC ("/RMT {rmoveto} bind def /RLT {rlineto} bind def\n");
		_hoops_CGPSC ("/EL {/yr exch def /xr exch def /y exch def /x exch def\n");
		_hoops_CGPSC (" /mtrx matrix currentmatrix def x y translate xr yr scale\n");
		_hoops_CGPSC (" 0 0 1 0 360 arc mtrx setmatrix} bind def\n");
		_hoops_CGPSC ("/SK {stroke} bind def /FL {fill} bind def /CL {clip} bind def /EOCL {eoclip} bind def\n");
		_hoops_CGPSC ("/SRGB {setrgbcolor} bind def /SD {setdash} bind def\n");
		_hoops_CGPSC ("/LW {setlinewidth} bind def /SG {setgray} bind def\n");
		_hoops_CGPSC ("/LC {setlinecap} bind def /LJ {setlinejoin} bind def\n");
		_hoops_CGPSC ("/FA {false} bind def /IM {image} bind def\n");
		_hoops_CGPSC ("/SC {scale} bind def /S {save} bind def /R {restore} bind def\n");
		_hoops_CGPSC ("/IE {ifelse} bind def /SP {showpage} bind def\n");
		_hoops_SGPSC("/LANDSCAPE {%g 0 translate 90 rotate} bind def\n", state->width);
		_hoops_SGPSC("/UN_LANDSCAPE {-90 rotate -%g 0 translate} bind def\n", state->width);
		_hoops_SGPSC("/PAGE_SCALE {72 %d div dup scale} bind def\n", state->_hoops_HAP);
		_hoops_SGPSC("/UN_PSCALE {%d 72 div dup scale} bind def\n", state->_hoops_HAP);
		_hoops_CGPSC ("/CI {/H exch def 0 1 H length 3 idiv 1 sub {3\n");
		_hoops_CGPSC (" mul /I exch def H I get 255 div H I 1 add get 255\n");
		_hoops_CGPSC (" div H I 2 add get 255 div SRGB CRP 2 copy NP MT 1 0 RLT\n");
		_hoops_CGPSC (" 0 1 RLT -1 0 RLT CP FL MT 1 0 RMT} for} bind def\n");

		_hoops_CGPSC ("/RLE {/H exch def SRGB CRP 2 copy NP MT H 0 RLT\n");
		_hoops_CGPSC (" 0 1 RLT H neg 0 RLT CP FL MT H 0 RMT} bind def\n");

		/* _hoops_SPHII _hoops_IS _hoops_SHHSC (_hoops_PPIC _hoops_GIHSC _hoops_SGSS)
		** _hoops_GHCR, _hoops_GCIH _hoops_SPCR, _hoops_HCSH _hoops_SPCR, _hoops_GCIH _hoops_CSSGR (_hoops_AHGPH _hoops_PHGPH _hoops_IHAC), _hoops_HCSH _hoops_CSSGR
		*/
		_hoops_CGPSC ("/GSPAN {12 dict begin\n");
		_hoops_CGPSC (" /End_B exch 255 div def /End_G exch 255 div def /End_R exch 255 div def\n");
		_hoops_CGPSC (" /B exch 255 div def /G exch 255 div def /R exch 255 div def\n");
		_hoops_CGPSC (" /End_X exch def /Start_X exch .5 sub def /Y exch def\n");
		_hoops_CGPSC (" /Width End_X Start_X sub def  /DR End_R R sub Width div def\n");
		_hoops_CGPSC (" /DG End_G G sub Width div def /DB End_B B sub Width div def\n");
		_hoops_CGPSC (" Start_X 1 End_X 1 sub {R G B SRGB	NP Y MT 1 0 RLT SK\n");
		_hoops_CGPSC ("  /R R DR add def  /G G DG add def	/B B DB add def} for end} bind def\n");


		_hoops_SIPSC (state);
		if (state->_hoops_PRGGH) return 0L;
		_hoops_SCPSC(state);
		if (state->_hoops_PRGGH) return 0L;
		_hoops_RSPSC (state);
		if (state->_hoops_PRGGH) return 0L;

		_hoops_CGPSC ("%%%%EndProlog\nmark\n");

		HD_Unload_All_Fonts((Display_Context alter*)dc);

		state->_hoops_SCASC = 1;
		state->_hoops_GSASC = 0;
	}

	state->_hoops_ASASC = true;

	state->_hoops_RPICC = state->_hoops_ACASC =
		state->_hoops_PCASC = 0;

	return (POINTER_SIZED_INT) fp;
}


local void free_outer_window (
	Display_Context const	*dc) {
	_hoops_HIASC alter				*state = _hoops_ARPSC (dc);

	state->_hoops_ASASC = false;
}


local void init_picture (
	Net_Rendition const &		nr) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	FILE alter *				fp = state->fp;

	if (!BIT(dc->flags, _hoops_SAISR) || state->_hoops_PRGGH) return;

	if (state->_hoops_PPICC == true)
		return;

	state->_hoops_PPICC = true;
	++state->_hoops_CIACC;

	state->_hoops_RPICC = state->_hoops_ACASC = state->_hoops_PCASC = 0;
	state->_hoops_HCASC = 0.0f;
	state->_hoops_ARSRI = _hoops_IAASP;
	state->_hoops_CRSRI = null;
	state->_hoops_ICASC = -1;
	state->_hoops_CCASC = -1;

	_hoops_IGPSC ("%%%%Page: %d\n", state->_hoops_CIACC);

	fprintf (fp, "%%%%PageBoundingBox: 0 0 %d %d\n", (int)(state->width), (int)(state->height));
	_hoops_AGPSC (state);

	if (dc->options._hoops_ARPSR)
		_hoops_ACIAI ("%%%%PageOrientation: Landscape\n");
	else
		_hoops_ACIAI ("%%%%PageOrientation: Portrait\n");

	if (dc->options._hoops_ARPSR)
		_hoops_ACIAI ("LANDSCAPE ");

	_hoops_ACIAI ("S PAGE_SCALE GS\n");
}


local void finish_picture (
	Net_Rendition const &		nr,
	bool						swap_buffers) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	FILE alter *				fp = state->fp;

	UNREFERENCED (swap_buffers);

	if (!BIT(dc->flags, _hoops_SAISR) || state->_hoops_PRGGH) return;

	_hoops_ACIAI ("GR R SP\n");

	fflush (fp);

	state->_hoops_GSASC = state->_hoops_SCASC - 1;
	state->_hoops_PPICC = false;
}


local void _hoops_RIHSC (
	Net_Rendition const &		nr) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	FILE alter *				fp = state->fp;
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
		_hoops_ASHH const *	_hoops_CRAIR = _hoops_IHCR->_hoops_HCHH->_hoops_PSHH;
		int								i;

		do {
			if (!BIT (_hoops_CRAIR->flags, _hoops_RHIH)) {
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
			else {
				fprintf (fp, "NP %.1f %.1f MT %.1f %.1f LT %.1f %.1f LT %.1f %.1f LT CP\n",
					_hoops_RCHS.left, _hoops_RCHS.bottom, _hoops_RCHS.left, _hoops_RCHS.top,
					_hoops_RCHS.right, _hoops_RCHS.top, _hoops_RCHS.right, _hoops_RCHS.bottom);	 _hoops_AGPSC (state);

				fprintf (fp, "NP %.1f %.1f MT", _hoops_CRAIR->points[0].x, _hoops_CRAIR->points[0].y);
					 _hoops_AGPSC (state);
				for (i=1; i<_hoops_CRAIR->count; i++) {
					fprintf (fp, " %.1f %.1f LT", _hoops_CRAIR->points[i].x, _hoops_CRAIR->points[i].y);
						 _hoops_AGPSC (state);
					if (i%4 == 3)
						_hoops_ACIAI ("\n");
				}

				_hoops_ACIAI (" CP EOCL\n");
			}
		} while ((_hoops_CRAIR = _hoops_CRAIR->next) != null);
	}

	state->_hoops_RPICC = _hoops_IHCR->_hoops_CPA;

	/* _hoops_HIAP _hoops_RH _hoops_HCISR _hoops_PIAP	 */
	state->_hoops_ARSRI = _hoops_IAASP;
	state->_hoops_CRSRI = null;
	state->_hoops_ICASC = -1;
	state->_hoops_CCASC = -1;
	state->_hoops_HCASC = -1.0f;
	state->_hoops_ACASC = -1;
}


local void _hoops_AIHSC (
	Net_Rendition const &		nr,
	Line_Rendition const &		_hoops_HC) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	FILE alter *				fp = state->fp;
	unsigned int				i;

	if (state->_hoops_PRGGH) return;

	if (BIT (dc->options._hoops_IRARR, _hoops_RGASC))
		_hoops_ACIAI ("%% new line rendition\n");

	if (state->_hoops_CRSRI != _hoops_HC->line_style) {
		int const		*_hoops_CAPSC;

		_hoops_CAPSC = _hoops_HC->line_style->_hoops_GHISR[0].pattern;
		state->_hoops_CRSRI = _hoops_HC->line_style;

		_hoops_ACIAI ("[");
		for (i=0;i<_hoops_HC->line_style->_hoops_GHISR[0]._hoops_RHISR;i++) {
			_hoops_IGPSC ("%d", (int) (*_hoops_CAPSC++ * state->_hoops_HAP / 72.0f));
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
                float weight = _hoops_HC->weight == 0 ? 0 : _hoops_HC->weight -1;
		_hoops_IGPSC ("%.2f LW", weight);
	}

	_hoops_ACIAI ("\n");

	state->_hoops_ACASC = _hoops_HC->_hoops_CPA;
	state->_hoops_GGPSC = true;
}


local void draw_dc_polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
	Line_Rendition const &		_hoops_HC = nr->_hoops_AHP;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	FILE alter *				fp = state->fp;
	int							_hoops_PIHSC;
	DC_Point const *			_hoops_ICHAI = points + count;
	DC_Point const *			_hoops_GIAHR = points;
	DC_Point const *			_hoops_RSASI = (points + count - 1);

	if (BIT(_hoops_HC->flags, _hoops_SRPI) ||
		ANYBIT(_hoops_HC->line_style->flags, LSF_COMPLEX_ANYBITS) ||
		ANYBIT((_hoops_HC->style&LCAP_MASK), LCAP_COMPLEX_BITS) ||
		(_hoops_HC->style & LPAT_MASK) >> LPAT_SHIFT != (_hoops_HC->style & LCAP_MASK) >> LCAP_SHIFT) {
		HD_Std_DC_Polyline (nr, count, points);
		return;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_GPHC);
		return;
	}
	if (nr->transform_rendition->_hoops_CPA != state->_hoops_RPICC)
		_hoops_RIHSC (nr);

	if (_hoops_HC->_hoops_CPA != state->_hoops_ACASC)
		_hoops_AIHSC (nr, nr->_hoops_AHP);

	if (state->_hoops_PRGGH) return;

	if (BIT (dc->options._hoops_IRARR, _hoops_RGASC))
		_hoops_ACIAI ("%% polyline\n");

	if (count > 0) {
		fprintf (fp, "NP %.2f %.2f MT ", points->x, points->y); _hoops_AGPSC (state);
		_hoops_PIHSC = 2;
		while (++points != _hoops_ICHAI) {
			if (++_hoops_PIHSC > 6) {
				_hoops_ACIAI ("\n");
				_hoops_PIHSC = 0;
			}
			fprintf (fp, "%.2f %.2f LT ", points->x, points->y); _hoops_AGPSC (state);
		}
		/* _hoops_ISPR _hoops_IH _hoops_CAHC _hoops_CRAA */
		if (_hoops_GIAHR->x == _hoops_RSASI->x && _hoops_GIAHR->y == _hoops_RSASI->y)
			_hoops_ACIAI ("CP ");
		_hoops_ACIAI ("SK\n");
	}
	else {
		int		_hoops_RRC;

		_hoops_ICHC (count, _hoops_RRC, 2);
		while (count-- > 0) {
			fprintf (fp, "NP %.2f %.2f MT %.2f %.2f LT CP SK\n",
						points[0].x, points[0].y, points[1].x, points[1].y); _hoops_AGPSC (state);
			points += _hoops_RRC;
		}
	}
}


local void _hoops_SCISR (
	Net_Rendition const &		nr,
	DC_Point const *			where,
	DC_Point const *			radii) {
	Line_Rendition const &		_hoops_HC = nr->_hoops_AHP;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	FILE alter *				fp = state->fp;

	if (BIT(_hoops_HC->flags, _hoops_SRPI) ||
		ANYBIT(_hoops_HC->line_style->flags, LSF_COMPLEX_ANYBITS) ||
		BIT (nr->transform_rendition->flags, _hoops_CSP) ||
		ANYBIT((_hoops_HC->style&LCAP_MASK), LCAP_COMPLEX_BITS)) {
		HD_Std_DC_Outline_Ellipse(nr, where, radii);
		return;
	}

	if (nr->transform_rendition->_hoops_CPA != state->_hoops_RPICC)
		_hoops_RIHSC (nr);
	if (_hoops_HC->_hoops_CPA != state->_hoops_ACASC)
		_hoops_AIHSC (nr, nr->_hoops_AHP);

	if (state->_hoops_PRGGH) return;

	if (BIT (dc->options._hoops_IRARR, _hoops_RGASC))
		_hoops_ACIAI ("%% circumference\n");

	if (BIT (dc->options._hoops_IRARR, _hoops_AGASC))
		_hoops_ACIAI ("S ");

	fprintf (fp, "NP %.2f %.2f %.2f %.2f EL SK",
				where->x, where->y, radii->x, radii->y);
	_hoops_AGPSC (state);

	if (BIT (dc->options._hoops_IRARR, _hoops_AGASC))
		_hoops_ACIAI (" R\n");
	else
		_hoops_ACIAI ("\n");
}


local void _hoops_HIHSC (
	Net_Rendition const &		nr,
	_hoops_PACIR const *			_hoops_IIHSC,
	RGBAS32 const *				color) {
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	Int_Rectangle				_hoops_CIHSC;
	Int_Rectangle *				_hoops_RCHS = &_hoops_CIHSC;
	FILE alter *				fp = state->fp;
	int alter					_hoops_PRAA;
	int alter					_hoops_HRAA;

	if (color == null)
		_hoops_CSASR (state, &_hoops_SIGA->color);
	else
		_hoops_IPPSC (state, color);

	if (state->_hoops_PRGGH) return;

	if (_hoops_SIGA->pattern == FP_SOLID)
		_hoops_ACIAI ("FL\n");
	else {
		_hoops_CIHSC.top = CEILING (_hoops_IIHSC->top);
		_hoops_CIHSC.bottom = FLOOR (_hoops_IIHSC->bottom);
		_hoops_CIHSC.left = FLOOR (_hoops_IIHSC->left);
		_hoops_CIHSC.right = CEILING (_hoops_IIHSC->right);

		if (_hoops_SIGA->pattern != FP_USER_DEFINED) {
			_hoops_ACIAI ("GS FL GR GS CL ");
			_hoops_CSASR (state, &_hoops_SIGA->contrast_color);
		}
		else {
			/* _hoops_RASRR _hoops_PAPR _hoops_HSGP */
			switch (_hoops_SIGA->_hoops_PGPH->_hoops_ACHHP) {
				default:
				case 0: {
					_hoops_ACIAI ("GS FL GR GS CL ");
					_hoops_CSASR (state, &_hoops_SIGA->contrast_color);
				}	break;
				case 1: {
					_hoops_ACIAI ("GS CL ");
					_hoops_CSASR (state, &_hoops_SIGA->contrast_color);
				}	break;
				case 2: {
					_hoops_ACIAI ("GS CL ");
				}	break;
			}
		}

		if (state->_hoops_PRGGH) return;

		switch (_hoops_SIGA->pattern) {
			case FP_VERTICAL_BARS:
			case FP_HORIZONTAL_BARS:
			case FP_CROSSHATCH:
			case FP_SQUARE_DOTS:
			case FP_CHECKERBOARD:		_hoops_PRAA = _hoops_HRAA = _hoops_ICRSC;
										break;
			case FP_SLANT_RIGHT:
			case FP_SLANT_LEFT:
			case FP_DIAMONDS:			_hoops_PRAA = _hoops_HRAA = _hoops_CCRSC;
										break;
			case FP_WINDOW_VERTICAL_BARS:
			case FP_WINDOW_HORIZONTAL_BARS:
			case FP_WINDOW_CROSSHATCH:
			case FP_WINDOW_SQUARE_DOTS:
			case FP_WINDOW_CHECKERBOARD: _hoops_PRAA = _hoops_HRAA = _hoops_SCRSC;
										 break;
			case FP_WINDOW_SLANT_RIGHT:
			case FP_WINDOW_SLANT_LEFT:
			case FP_WINDOW_DIAMONDS:	_hoops_PRAA = _hoops_HRAA = _hoops_GSRSC;
										break;

			case FP_USER_DEFINED: {
					_hoops_PRAA = _hoops_SIGA->_hoops_PGPH->width  * _hoops_PCRSC;
					_hoops_HRAA = _hoops_SIGA->_hoops_PGPH->height * _hoops_PCRSC;
				}	break;

			default:	_hoops_PRAA = _hoops_HRAA = 1;
		}

		_hoops_RCHS->left   -= _hoops_RCHS->left % _hoops_PRAA;
		_hoops_RCHS->bottom -= _hoops_RCHS->bottom % _hoops_HRAA;
		_hoops_RCHS->right  += _hoops_PRAA - _hoops_RCHS->right % _hoops_PRAA;
		_hoops_RCHS->top	   += _hoops_HRAA - _hoops_RCHS->top % _hoops_HRAA;

		switch (_hoops_SIGA->pattern) {
			case FP_VERTICAL_BARS:
			case FP_WINDOW_VERTICAL_BARS: {
				fprintf (fp, "%d %d %d %d ",
					_hoops_RCHS->left, _hoops_RCHS->bottom,
					_hoops_RCHS->right - _hoops_RCHS->left, _hoops_RCHS->top - _hoops_RCHS->bottom);
				_hoops_AGPSC (state);
				_hoops_IGPSC ("%d VBARS GR\n", _hoops_PRAA);
			}	break;

			case FP_HORIZONTAL_BARS:
			case FP_WINDOW_HORIZONTAL_BARS: {
				fprintf (fp, "%d %d %d %d ",
					_hoops_RCHS->left, _hoops_RCHS->bottom,
					_hoops_RCHS->right - _hoops_RCHS->left, _hoops_RCHS->top - _hoops_RCHS->bottom);
				_hoops_AGPSC (state);
				_hoops_IGPSC ("%d HBARS GR\n", _hoops_PRAA);
			}	break;

			case FP_CROSSHATCH:
			case FP_WINDOW_CROSSHATCH: {
				fprintf (fp, "%d %d %d %d ",
					_hoops_RCHS->left, _hoops_RCHS->bottom,
					_hoops_RCHS->right - _hoops_RCHS->left, _hoops_RCHS->top - _hoops_RCHS->bottom);
				_hoops_AGPSC (state);
				_hoops_IGPSC ("%d CROSSH GR\n", _hoops_PRAA);
			}	break;

			case FP_SLANT_RIGHT:
			case FP_WINDOW_SLANT_RIGHT: {
				fprintf (fp, "%d %d %d %d ",
					_hoops_RCHS->left, _hoops_RCHS->bottom,
					_hoops_RCHS->top, _hoops_RCHS->right - _hoops_RCHS->left +
								 _hoops_RCHS->top - _hoops_RCHS->bottom);
				_hoops_AGPSC (state);
				_hoops_IGPSC ("%d SLANTR GR\n", _hoops_PRAA);
			}	break;

			case FP_SLANT_LEFT:
			case FP_WINDOW_SLANT_LEFT: {
				fprintf (fp, "%d %d %d %d ",
					_hoops_RCHS->left, _hoops_RCHS->bottom,
					_hoops_RCHS->top, _hoops_RCHS->right - _hoops_RCHS->left +
								 _hoops_RCHS->top - _hoops_RCHS->bottom);
				_hoops_AGPSC (state);
				_hoops_IGPSC ("%d SLANTL GR\n", _hoops_PRAA);
			}	break;

			case FP_DIAMONDS:
			case FP_WINDOW_DIAMONDS: {
				fprintf (fp, "%d %d %d %d ",
					_hoops_RCHS->left, _hoops_RCHS->bottom,
					_hoops_RCHS->top, _hoops_RCHS->right - _hoops_RCHS->left +
								 _hoops_RCHS->top - _hoops_RCHS->bottom);
				_hoops_AGPSC (state);
				_hoops_IGPSC ("%d DIAMONDS GR\n", _hoops_PRAA);
			}	break;

			case FP_SQUARE_DOTS:
			case FP_WINDOW_SQUARE_DOTS: {
				fprintf (fp, "%d %d %d %d ",
					_hoops_RCHS->left, _hoops_RCHS->bottom,
					_hoops_RCHS->right - _hoops_RCHS->left, _hoops_RCHS->top - _hoops_RCHS->bottom);
				_hoops_AGPSC (state);
				fprintf (fp, "%d %d SQDOTS GR\n", _hoops_PRAA,
						 _hoops_SIGA->pattern == FP_SQUARE_DOTS ? _hoops_RSRSC : _hoops_ASRSC);
				_hoops_AGPSC (state);
			}	break;

			case FP_CHECKERBOARD:
			case FP_WINDOW_CHECKERBOARD: {
				fprintf (fp, "%d %d %d %d ",
					_hoops_RCHS->left, _hoops_RCHS->bottom,
					_hoops_RCHS->right - _hoops_RCHS->left, _hoops_RCHS->top - _hoops_RCHS->bottom);
				_hoops_AGPSC (state);
				fprintf (fp, "%d %d CHECKBRD GR\n", _hoops_PRAA,
						 _hoops_SIGA->pattern == FP_CHECKERBOARD ? _hoops_PSRSC : _hoops_HSRSC);
				_hoops_AGPSC (state);
			}	break;

			case FP_USER_DEFINED: {
				unsigned int alter				_hoops_RCHA;
				int alter						_hoops_SIHSC;
				int alter						column;
				unsigned char const				*_hoops_SHHCR;
				int alter						_hoops_SHCSR;
				int alter						_hoops_GICSR;
				int alter						_hoops_GCHSC;
				int alter						_hoops_RCHSC;
				_hoops_PRASC alter		*_hoops_ACHSC;

#define _hoops_PCHSC 37
#define _hoops_HCHSC	8
#define _hoops_ICHSC	60

				/* _hoops_CACPR _hoops_CCHSC _hoops_PPR _hoops_SCHSC _hoops_AAPR _hoops_GGSRA _hoops_ARRS, _hoops_HIH _hoops_SSIA
				** _hoops_AAPR _hoops_GSHSC _hoops_RSHSC _hoops_IS _hoops_PRRP _hoops_CSRA _hoops_RH _hoops_HSGP.
				** _hoops_HAPI _hoops_SR _hoops_HHGC _hoops_IS _hoops_PHHR _hoops_ISSC _hoops_IS _hoops_RH _hoops_RIHRR _hoops_IGIR.
				*/
				_hoops_PRAA = _hoops_SIGA->_hoops_PGPH->width;
				_hoops_HRAA = _hoops_SIGA->_hoops_PGPH->height;

				/*
				** _hoops_IIRCI _hoops_SGS _hoops_CHR _hoops_HAH _hoops_RISA _hoops_GRS _hoops_IRHH _hoops_ICRP _hoops_SIRSI
				** _hoops_CPPPR _hoops_ASHSC _hoops_CR _hoops_SSIA _hoops_CHR _hoops_PSHSC _hoops_HIS _hoops_AHPH _hoops_IACH.
				** _hoops_GPGP _hoops_RGR _hoops_AGIR, _hoops_SR _hoops_SAHR "_hoops_IRHI" _hoops_RH _hoops_HSGP.
				*/
				if (_hoops_PRAA < _hoops_ICHSC)
						_hoops_GCHSC = (_hoops_ICHSC / _hoops_PRAA) * _hoops_PRAA + _hoops_PRAA;
				else	_hoops_GCHSC = _hoops_PRAA;
				if (_hoops_HRAA < _hoops_ICHSC)
						_hoops_RCHSC = (_hoops_ICHSC / _hoops_HRAA) * _hoops_HRAA + _hoops_HRAA;
				else	_hoops_RCHSC = _hoops_HRAA;


				/* _hoops_AIHH _hoops_RPP _hoops_SR'_hoops_RISP _hoops_IGI _hoops_RGR _hoops_HSGP _hoops_ARPP (_hoops_SSCP _hoops_SCH _hoops_RPII
				** _hoops_PAPR _hoops_IS _hoops_RH _hoops_GRGAI _hoops_GAPR?)
				** _hoops_IRHRC _hoops_RH _hoops_HSHSC _hoops_HIGR _hoops_IIGR _hoops_IPSP _hoops_PAIA _hoops_PAPR.
				*/
				if (_hoops_SIGA->_hoops_PGPH->_hoops_CPA != state->_hoops_PCASC) {

					/* _hoops_PS'_hoops_RISP _hoops_HGAS _hoops_PAIA.
					** _hoops_AIHH _hoops_RPP _hoops_SR'_hoops_RISP _hoops_SGIPR _hoops_PAPR _hoops_RGR _hoops_HSGP _hoops_GGR _hoops_RH _hoops_ISGR.
					*/
					for (_hoops_ACHSC = state->_hoops_RSASC;
						 _hoops_ACHSC != null;
						 _hoops_ACHSC = _hoops_ACHSC->next) {
						if (_hoops_ACHSC->_hoops_CPA ==
							_hoops_SIGA->_hoops_PGPH->_hoops_CPA) break;
					}

					if (!_hoops_ACHSC) {
						/*
						** _hoops_ISHSC, _hoops_SR'_hoops_RISP _hoops_IIP _hoops_GCRHA _hoops_RGR _hoops_HSGP _hoops_ARPP.
						** _hoops_ICAH _hoops_IS _hoops_GGARP _hoops_IRS _hoops_CCAH _hoops_HSGP _hoops_CRGR _hoops_RPPSC.
						*/
						fprintf(fp, "\n/TILE%ld { GS translate %d %d scale\n",
							(long)(POINTER_SIZED_INT)_hoops_SIGA->_hoops_PGPH->_hoops_CPA,
							_hoops_GCHSC * _hoops_PCRSC,
							_hoops_RCHSC * _hoops_PCRSC);
						_hoops_AGPSC (state);
						fprintf(fp, " %d %d %s [%d 0 0 %d 0 %d] { <\n",
							_hoops_GCHSC, _hoops_RCHSC,
							(_hoops_SIGA->_hoops_PGPH->_hoops_ACHHP < 2) ? "true" : "false",
							_hoops_GCHSC,
							_hoops_SIGA->_hoops_PGPH->_hoops_RCHHP ? - _hoops_RCHSC : _hoops_RCHSC,
							_hoops_SIGA->_hoops_PGPH->_hoops_RCHHP ?	_hoops_RCHSC : 0);
						_hoops_AGPSC (state);

						/* _hoops_CCSCI _hoops_RH _hoops_AHRH _hoops_GGR _hoops_RAAP-_hoops_IS-_hoops_RPHR _hoops_IGRH-_hoops_PHAP _hoops_ACCAI _hoops_GCSRR.
						*/
						_hoops_RCHA = _hoops_SIHSC = column = 0;
						_hoops_SHHCR = _hoops_SIGA->_hoops_PGPH->pattern;
						for (_hoops_GICSR = 0; _hoops_GICSR < _hoops_RCHSC; _hoops_GICSR++) {
							for (_hoops_SHCSR = 0; _hoops_SHCSR < _hoops_GCHSC; _hoops_SHCSR++) {
								/* _hoops_HGI _hoops_HRGR _hoops_SCIPA, _hoops_HIH _hoops_IIAH.
								** _hoops_HAIC _hoops_CASI _hoops_GH _hoops_SPHR
								*/
								_hoops_RCHA <<= 1;
								if (_hoops_SHHCR[(_hoops_SHCSR % _hoops_PRAA) +
										(_hoops_GICSR % _hoops_HRAA) * _hoops_PRAA]) _hoops_RCHA++;
								_hoops_SIHSC++;
								if (_hoops_SIHSC == _hoops_HCHSC) {
									fprintf(fp, "%02X", _hoops_RCHA);
									_hoops_AGPSC (state);
									_hoops_RCHA = _hoops_SIHSC = 0;
									column++;
									if (column > _hoops_PCHSC) {
										_hoops_ACIAI ("\n  ");
										column = 0;
									} /* _hoops_RPP _hoops_III _hoops_HIICP */
								} /* _hoops_RPP _hoops_GRGP _hoops_HIICP */
							} /* _hoops_CSHSC _hoops_HAPR */

							/*
							** _hoops_CGP _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_PPSCP _hoops_ASSP'_hoops_RA _hoops_HSSC _hoops_GPP _hoops_IRS _hoops_SSHSC
							** _hoops_HIICP, _hoops_PSCR _hoops_CRPSR _hoops_RH _hoops_GSSC _hoops_SIH _hoops_IIGR _hoops_RH _hoops_SSHSC.
							*/
							if (_hoops_SIHSC != 0) {
								_hoops_RCHA <<= _hoops_HCHSC - _hoops_SIHSC;
								_hoops_IGPSC ("%02X", _hoops_RCHA);
							}
							_hoops_ACIAI ("\n");
							column = _hoops_RCHA = _hoops_SIHSC = 0;
						} /* _hoops_GGISC _hoops_HAPR */

						_hoops_ACIAI ("\n > } imagemask GR } bind def\n");

						/* _hoops_AGGA _hoops_GGCR _hoops_RGR _hoops_IS _hoops_RH _hoops_HIGR _hoops_IIGR _hoops_PAPR _hoops_PAIA _hoops_SR
						** _hoops_ACPA _hoops_AHCA.
						*/
						_hoops_ACHSC = state->_hoops_RSASC;
						ALLOC (state->_hoops_RSASC, _hoops_PRASC);
						state->_hoops_RSASC->_hoops_CPA =
											_hoops_SIGA->_hoops_PGPH->_hoops_CPA;
						state->_hoops_RSASC->next = _hoops_ACHSC;
					} /* _hoops_CGP _hoops_RGISC == _hoops_IRAP, (_hoops_SR _hoops_HS _hoops_IRS _hoops_CCAH _hoops_HSGP)  */
				} /* _hoops_CGP _hoops_AGISC != _hoops_PGISC */

				state->_hoops_PCASC = _hoops_SIGA->_hoops_PGPH->_hoops_CPA;
				fprintf (fp, "%d %d %d %d ",
					_hoops_RCHS->left, _hoops_RCHS->bottom,
					_hoops_RCHS->right - _hoops_RCHS->left, _hoops_RCHS->top - _hoops_RCHS->bottom);
				_hoops_AGPSC (state);
				fprintf (fp, "%d %d /TILE%ld USER_PATTERN GR\n",
					_hoops_GCHSC * _hoops_PCRSC, _hoops_RCHSC * _hoops_PCRSC,
					(long)(POINTER_SIZED_INT)_hoops_SIGA->_hoops_PGPH->_hoops_CPA);
				_hoops_AGPSC (state);
			}	break;

			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								   "Invalid face/window pattern");
			}	break;
		}
		state->_hoops_ARSRI = _hoops_SIGA->color;  /* _hoops_CGARA _hoops_HAIR _hoops_PPACP */
	}

	state->_hoops_ACASC = _hoops_SIGA->_hoops_CPA;
}

local void draw_dc_rectangle (
	Net_Rendition const &		nr,
	int							left,
	int							right,
	int							bottom,
	int							top) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	FILE alter *				fp = state->fp;
	_hoops_PACIR				_hoops_RCHS;

	if (nr->transform_rendition->_hoops_CPA != state->_hoops_RPICC)
		_hoops_RIHSC (nr);

	if (state->_hoops_PRGGH) return;

	if (BIT (dc->options._hoops_IRARR, _hoops_RGASC))
		_hoops_ACIAI ("%% rectangle\n");

	_hoops_RCHS.left = (float) left - 0.5f;
	_hoops_RCHS.right = (float) right + 0.5f;
	_hoops_RCHS.bottom = (float) bottom - 0.5f;
	_hoops_RCHS.top = (float) top + 0.5f;

	fprintf (fp, "NP %.1f %.1f MT %.1f %.1f LT %.1f %.1f LT %.1f %.1f LT CP\n",
		_hoops_RCHS.left, _hoops_RCHS.bottom, _hoops_RCHS.left, _hoops_RCHS.top, _hoops_RCHS.right, _hoops_RCHS.top, _hoops_RCHS.right, _hoops_RCHS.bottom);
	_hoops_AGPSC (state);

	_hoops_HIHSC (nr, &_hoops_RCHS, null);
}


/*
 * * _hoops_SRAC
 * */
local void draw_window (
	Net_Rendition const &		nr,
	Int_Rectangle const *		extent) {

	HD_Standard_Draw_Window(nr, extent);
}



local void draw_3d_nurbs_curve (
	Net_Rendition const &		nr,
	_hoops_PIRGR const *			curve) {
#ifndef _hoops_CCPIR
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	FILE alter *				fp = state->fp;
	Line_Rendition const &		_hoops_HC = nr->_hoops_AHP;
	int							count, _hoops_PHISR, i, _hoops_PIHSC;
	Point *						_hoops_HHISR;
	DC_Point					*_hoops_IHISR, *points, *_hoops_ICHAI;
	float const *				mat;
	Polyline					polyline;

	/* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_GGR _hoops_CIHP _hoops_PHCR... */
	if (nr->transform_rendition->_hoops_SPH->projection != _hoops_CPPCR) {
		HD_Std_3D_NURBS_Curve (nr, curve);
		return;
	}

	if (nr->_hoops_ARA->_hoops_APPI._hoops_SAR ||
		BIT(_hoops_HC->flags, _hoops_SRPI) ||
		ANYBIT(_hoops_HC->line_style->flags, LSF_COMPLEX_ANYBITS) ||
		ANYBIT((_hoops_HC->style&LCAP_MASK), LCAP_COMPLEX_BITS)) {
		HD_Std_3D_NURBS_Curve (nr, curve);
		return;
	}

	if (curve->polyline.points == null) {
		HI_Generate_NURBS_Polyline (curve,
			&nr->_hoops_ARA->_hoops_APPI,
			&nr->transform_rendition->matrix->data,
			&polyline, 0);
		if (!polyline.points)
			return; /* _hoops_CHISR? */
		/* _hoops_CHPR _hoops_SAII _hoops_IIGR _hoops_RH _hoops_PIH _hoops_IS _hoops_RH _hoops_AGIS */
		((_hoops_PIRGR alter*)curve)->polyline.points    = polyline.points;
		((_hoops_PIRGR alter*)curve)->polyline.count 	  = polyline.count;
		((_hoops_PIRGR alter*)curve)->polyline.allocated = polyline.allocated;
	}
	else {
		polyline.points    = curve->polyline.points;
		polyline.count     = curve->polyline.count;
		polyline.allocated = curve->polyline.allocated;
	}
	count = polyline.count;
	_hoops_PHISR = count*3-2;
	ALLOC_ARRAY_ALIGNED (_hoops_HHISR, _hoops_PHISR, Point, 16);
	ALLOC_ARRAY_ALIGNED (_hoops_IHISR, _hoops_PHISR, DC_Point, 16);
	HI_Generate_Polyline_Bezier (count, polyline.points, _hoops_HHISR);

	mat = &nr->transform_rendition->matrix->data.elements[0][0];
	HI_Compute_Transformed_Points (_hoops_PHISR, _hoops_HHISR, mat, (Point *)_hoops_IHISR);

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		for (i = 0 ; i < _hoops_PHISR ; i++) {
			if (!HD_Point_Within_Cutting_Planes (nr->transform_rendition,
					_hoops_IHISR[i].x, _hoops_IHISR[i].y, _hoops_IHISR[i].z)) {
				HD_Std_3D_NURBS_Curve (nr, curve);
				goto done;
			}
		}
		/* _hoops_SHS _hoops_HSSC _hoops_RHIR _hoops_IS _hoops_SHISR _hoops_AGIR _hoops_CAPP */
	}

	if (nr->transform_rendition->_hoops_CPA != state->_hoops_RPICC)
		_hoops_RIHSC (nr);
	if (_hoops_HC->_hoops_CPA != state->_hoops_ACASC)
		_hoops_AIHSC (nr, nr->_hoops_AHP);
	if (state->_hoops_PRGGH)
		return;
	if (BIT (dc->options._hoops_IRARR, _hoops_RGASC))
		_hoops_ACIAI ("%% nurbs curve\n");

	points = _hoops_IHISR;
	_hoops_ICHAI = _hoops_IHISR + _hoops_PHISR;
	fprintf (fp, "NP %.2f %.2f MT ", points->x, points->y); _hoops_AGPSC (state);
	_hoops_PIHSC = 2;
	while (++points != _hoops_ICHAI) {
		if (++_hoops_PIHSC > 6) {
			_hoops_ACIAI ("\n");
			_hoops_PIHSC = 0;
		}
		fprintf (fp, "%.2f %.2f LT ", points->x, points->y); _hoops_AGPSC (state);
	}
	/* _hoops_ISPR _hoops_IH _hoops_CAHC _hoops_CRAA */
	if (_hoops_IHISR[0].x == _hoops_IHISR[_hoops_PHISR-1].x && _hoops_IHISR[0].y == _hoops_IHISR[_hoops_PHISR-1].y)
		_hoops_ACIAI ("CP ");
	_hoops_ACIAI ("SK\n");

  done:
	FREE_ARRAY_ALIGNED (_hoops_HHISR, _hoops_PHISR, Point, 16);
	FREE_ARRAY_ALIGNED (_hoops_IHISR, _hoops_PHISR, DC_Point, 16);
#endif
}


local void draw_3d_elliptical_arc (
	Net_Rendition const &		nr,
	Elliptical_Arc const *		arc) {
	_hoops_CIGA				_hoops_SIGA;
	Line_Rendition				_hoops_HC = nr->_hoops_AHP;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	FILE alter *				fp = state->fp;
	int							i, count;
	DC_Point					buffer[16];
	int							pass = 0;
	bool						done = false;

	/* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_GGR _hoops_CIHP _hoops_PHCR... */
	if (nr->transform_rendition->_hoops_SPH->projection != _hoops_CPPCR) {
		HD_Std_3D_Elliptical_Arc (nr, arc);
		return;
	}

	if (arc->type == _hoops_SGCP ||
		arc->type == _hoops_CGCP ||
		arc->type == _hoops_GRCP ||
		arc->type == _hoops_RRCP) {

		if (BIT (nr->_hoops_RGP, T_FACES))
			_hoops_SIGA = nr->_hoops_IHA;
		else
			_hoops_SIGA = null;

		if (ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE))
			_hoops_HC = nr->_hoops_RHP;
		else
			_hoops_HC = null;
	}

	if (_hoops_HC &&
		BIT(_hoops_HC->flags, _hoops_SRPI) ||
		(ANYBIT(_hoops_HC->line_style->flags, LSF_COMPLEX_ANYBITS) || ANYBIT((_hoops_HC->style&LCAP_MASK), LCAP_COMPLEX_BITS))) {
		HD_Std_3D_Elliptical_Arc (nr, arc);
		return;
	}

	HD_Generate_Elliptical_Bezier (nr, (_hoops_GHHI const *)arc, &count, buffer);

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		for (i = 0 ; i < count ; i++) {
			if (!HD_Point_Within_Cutting_Planes (nr->transform_rendition,
					buffer[i].x, buffer[i].y, buffer[i].z)) {
				HD_Std_3D_Elliptical_Arc (nr, arc);
				return;
			}
		}
		/* _hoops_SHS _hoops_HSSC _hoops_RHIR _hoops_IS _hoops_SHISR _hoops_AGIR _hoops_CAPP */
	}

	if (nr->transform_rendition->_hoops_CPA != state->_hoops_RPICC)
		_hoops_RIHSC (nr);

	if (state->_hoops_PRGGH) return;

	if (BIT (dc->options._hoops_IRARR, _hoops_RGASC))
		_hoops_ACIAI ("%% 3d elliptical arc\n");

	if (_hoops_HC && _hoops_HC->_hoops_CPA != state->_hoops_ACASC)
		_hoops_AIHSC (nr, _hoops_HC); /* _hoops_PCSA: _hoops_HGICP _hoops_GHCA _hoops_SHH _hoops_SCII->_hoops_CSIS _hoops_RIIA _hoops_IIGR _hoops_SCII->_hoops_HGISC */

	while (!done) {
		/*
		 * _hoops_IGISC _hoops_RCSPR _hoops_CGISC
		 */
		fprintf (fp, "NP %.2f %.2f MT\n", buffer[0].x, buffer[0].y); _hoops_AGPSC (state);
		for (i = 1 ; i < count ; i += 3) {
			fprintf (fp, "%.2f %.2f %.2f %.2f %.2f %.2f curveto\n",
				buffer[i].x, buffer[i].y, buffer[i+1].x, buffer[i+1].y, buffer[i+2].x, buffer[i+2].y);
			_hoops_AGPSC (state);
		}
		if (arc->type == _hoops_RRCP) {
			_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
			DC_Point _hoops_SGISC;
			float w;

			_hoops_SGISC.x = _hoops_HPRA (_hoops_IHCR->matrix->data.elements, arc->center);
			_hoops_SGISC.y = _hoops_IPRA (_hoops_IHCR->matrix->data.elements, arc->center);
			if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH) {
				w = _hoops_PHCP (_hoops_IHCR->matrix->data.elements, arc->center);
				_hoops_SGISC.x /= w;
				_hoops_SGISC.y /= w;
			}
			fprintf (fp, "%.2f %.2f LT\n", _hoops_SGISC.x, _hoops_SGISC.y); _hoops_AGPSC (state);
			fprintf (fp, "%.2f %.2f LT\n", buffer[0].x, buffer[0].y); _hoops_AGPSC (state);
			_hoops_ACIAI ("CP "); /* _hoops_HGPR _hoops_GAR _hoops_CAHC _hoops_CRAA */
		}
		else if (arc->type == _hoops_GRCP) {
			fprintf (fp, "%.2f %.2f LT\n", buffer[0].x, buffer[0].y); _hoops_AGPSC (state);
			_hoops_ACIAI ("CP "); /* _hoops_HGPR _hoops_GAR _hoops_CAHC _hoops_CRAA */
		}
		if (buffer[0].x == buffer[count-1].x && buffer[0].y == buffer[count-1].y)
			_hoops_ACIAI ("CP "); /* _hoops_HGPR _hoops_GAR _hoops_CAHC _hoops_CRAA */

		/*
		 * _hoops_GCIGC _hoops_RCSPR _hoops_CGISC
		 */
		if (_hoops_HC && pass == 0) {
			_hoops_ACIAI ("SK\n");
			if (!_hoops_SIGA)
				done = true;
		}
		else {
			if (_hoops_SIGA->pattern != FP_SOLID) {
				_hoops_PACIR _hoops_RCHS;

				_hoops_RCHS.right = _hoops_RCHS.left = buffer[0].x;
				_hoops_RCHS.bottom = _hoops_RCHS.top = buffer[0].y;
				for (i = 1 ; i < count ; i++) {
					if (buffer[i].x > _hoops_RCHS.right)
						_hoops_RCHS.right = buffer[i].x;
					else if (buffer[i].x < _hoops_RCHS.left)
						_hoops_RCHS.left = buffer[i].x;
					if (buffer[i].y > _hoops_RCHS.top)
						_hoops_RCHS.top = buffer[i].y;
					else if (buffer[i].y < _hoops_RCHS.bottom)
						_hoops_RCHS.bottom = buffer[i].y;
				}
				_hoops_HIHSC (nr, &_hoops_RCHS, null);
			}
			else
				_hoops_HIHSC (nr, null, null);
			done = true;
		}
		pass++;
	}
}

local void draw_3d_ellipse (
	Net_Rendition const &		nr,
	Ellipse const *				ellipse) {

	draw_3d_elliptical_arc (nr, (Elliptical_Arc const *)ellipse);
}


local void _hoops_CCISR (
	Net_Rendition const &		nr,
	DC_Point const *			center,
	DC_Point const *			radii,
	float 						start,
	float 						end) {
	Line_Rendition const &		_hoops_HC = nr->_hoops_AHP;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	FILE alter *				fp = state->fp;
	int							i, count;
	DC_Point 					_hoops_SPPSI[2];
	DC_Point 					buffer[16];

	if (BIT(_hoops_HC->flags, _hoops_SRPI) ||
		ANYBIT(_hoops_HC->line_style->flags, LSF_COMPLEX_ANYBITS) ||
		ANYBIT((_hoops_HC->style&LCAP_MASK), LCAP_COMPLEX_BITS)) {
		HD_Std_DC_Elliptical_Arc (nr, center, radii, start, end);
		return;
	}

	_hoops_SPPSI[0].x = radii->x;
	_hoops_SPPSI[0].y = 0;
	_hoops_SPPSI[0].z = 0;
	_hoops_SPPSI[1].x = 0;
	_hoops_SPPSI[1].y = radii->y;
	_hoops_SPPSI[1].z = 0;
	HD_DC_Generate_Elliptical_Bezier (nr, center, &_hoops_SPPSI[0], &_hoops_SPPSI[1], start, end, &count, buffer);

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		for (i = 0 ; i < count ; i++) {
			if (!HD_Point_Within_Cutting_Planes (nr->transform_rendition,
					buffer[i].x, buffer[i].y, buffer[i].z)) {
				HD_Std_DC_Elliptical_Arc (nr, center, radii, start, end);
				return;
			}
		}
		/* _hoops_SHS _hoops_HSSC _hoops_RHIR _hoops_IS _hoops_SHISR _hoops_AGIR _hoops_CAPP */
	}

	if (nr->transform_rendition->_hoops_CPA != state->_hoops_RPICC)
		_hoops_RIHSC (nr);

	if (_hoops_HC->_hoops_CPA != state->_hoops_ACASC)
		_hoops_AIHSC (nr, nr->_hoops_AHP);

	if (state->_hoops_PRGGH) return;

	if (BIT (dc->options._hoops_IRARR, _hoops_RGASC))
		_hoops_ACIAI ("%% dc elliptical arc\n");

	fprintf (fp, "NP %.2f %.2f MT\n", buffer[0].x, buffer[0].y); _hoops_AGPSC (state);
	for (i = 1 ; i < count ; i += 3) {
		fprintf (fp, "%.2f %.2f %.2f %.2f %.2f %.2f curveto\n",
			buffer[i].x, buffer[i].y, buffer[i+1].x, buffer[i+1].y, buffer[i+2].x, buffer[i+2].y);
		_hoops_AGPSC (state);
	}
	/* _hoops_ISPR _hoops_IH _hoops_CAHC _hoops_CRAA */
	if (buffer[0].x == buffer[count-1].x && buffer[0].y == buffer[count-1].y)
		_hoops_ACIAI ("CP ");
	_hoops_ACIAI ("SK\n");
}


local void draw_dc_ellipse (
	Net_Rendition const &		nr,
	DC_Point const *			where,
	DC_Point const *			radii) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	FILE alter *				fp = state->fp;
	_hoops_PACIR					_hoops_RCHS;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Std_DC_Ellipse (nr, where, radii);
		return;
	}
	if (nr->transform_rendition->_hoops_CPA != state->_hoops_RPICC)
		_hoops_RIHSC (nr);

	if (state->_hoops_PRGGH) return;

	if (BIT (dc->options._hoops_IRARR, _hoops_RGASC))
		_hoops_ACIAI ("%% ellipse\n");
	if (BIT (dc->options._hoops_IRARR, _hoops_AGASC))
		_hoops_ACIAI ("S ");

	_hoops_RCHS.left =	where->x - radii->x;
	_hoops_RCHS.right =	where->x + radii->x;
	_hoops_RCHS.bottom = where->y - radii->y;
	_hoops_RCHS.top =	where->y + radii->y;

	fprintf (fp, "NP %.2f %.2f %.2f %.2f EL\n", where->x, where->y,
										radii->x, radii->y);
	_hoops_AGPSC (state);

	_hoops_HIHSC (nr, &_hoops_RCHS, null);

	if (BIT (dc->options._hoops_IRARR, _hoops_AGASC))
		_hoops_ACIAI ("R ");
}


local void draw_dc_face (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	_hoops_PACIR			_hoops_RCHS;
	FILE alter *				fp = state->fp;
	int							_hoops_PIHSC;
	DC_Point const *			_hoops_ICHAI = points + count-1;

	ZERO_STRUCT(&_hoops_RCHS, _hoops_PACIR);

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Face (nr, count, points, 0, _hoops_GPHC);
		return;
	}
	if (nr->transform_rendition->_hoops_CPA != state->_hoops_RPICC)
		_hoops_RIHSC (nr);

	if (state->_hoops_PRGGH) return;

	if (BIT (dc->options._hoops_IRARR, _hoops_RGASC))
		_hoops_ACIAI ("%% face\n");

	if (_hoops_SIGA->pattern != FP_SOLID) {
		_hoops_RCHS.right = _hoops_RCHS.left = points->x;
		_hoops_RCHS.bottom = _hoops_RCHS.top = points->y;
	}
	fprintf (fp, "NP %.2f %.2f MT ", points->x, points->y);
	_hoops_AGPSC (state);

	_hoops_PIHSC = 2;
	while (++points <= _hoops_ICHAI) {

		if (_hoops_SIGA->pattern != FP_SOLID) {
				if (points->x > _hoops_RCHS.right)
						_hoops_RCHS.right = points->x;
				else if (points->x < _hoops_RCHS.left)
						_hoops_RCHS.left = points->x;
				if (points->y > _hoops_RCHS.top)
						_hoops_RCHS.top = points->y;
				else if (points->y < _hoops_RCHS.bottom)
						_hoops_RCHS.bottom = points->y;
		}

		if (++_hoops_PIHSC > 6) {
			_hoops_ACIAI ("\n");
			_hoops_PIHSC = 0;
		}
		fprintf (fp, "%.2f %.2f LT ", points->x, points->y);
		_hoops_AGPSC (state);
	}

	_hoops_ACIAI ("CP\n");

	_hoops_HIHSC (nr, &_hoops_RCHS, null);
}

local void draw_dc_polytriangle (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	_hoops_PACIR					_hoops_RCHS;
	FILE alter *				fp = state->fp;
	int							_hoops_RRC;

	ZERO_STRUCT(&_hoops_RCHS, _hoops_PACIR);

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_GPHC);
		return;
	}
	if (nr->transform_rendition->_hoops_CPA != state->_hoops_RPICC)
		_hoops_RIHSC (nr);

	if (state->_hoops_PRGGH) return;

	if (BIT (dc->options._hoops_IRARR, _hoops_RGASC))
		_hoops_ACIAI ("%% triangle\n");

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		int					i;

		if (_hoops_SIGA->pattern != FP_SOLID) {
			_hoops_RCHS.right = _hoops_RCHS.left = points->x;
			_hoops_RCHS.bottom = _hoops_RCHS.top = points->y;
		}

		fprintf (fp, "NP %.2f %.2f MT ", points[0].x, points[0].y);
		_hoops_AGPSC (state);

		for (i=1; i<3; i++) {
			if (_hoops_SIGA->pattern != FP_SOLID) {
				if (points[i].x > _hoops_RCHS.right)
					_hoops_RCHS.right = points[i].x;
				else if (points[i].x < _hoops_RCHS.left)
					_hoops_RCHS.left = points[i].x;

				if (points[i].y > _hoops_RCHS.top)
					_hoops_RCHS.top = points[i].y;
				else if (points[i].y < _hoops_RCHS.bottom)
					_hoops_RCHS.bottom = points[i].y;
			}

			fprintf (fp, "%.2f %.2f LT ", points[i].x, points[i].y);
			_hoops_AGPSC (state);
		}

		_hoops_ACIAI ("CP\n");

		_hoops_HIHSC (nr, &_hoops_RCHS, null);

		points += _hoops_RRC;
	}
}


local void draw_dc_colorized_polytriangle (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors,
	bool						single) {
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	_hoops_PACIR					_hoops_RCHS;
	FILE alter *				fp = state->fp;
	int							_hoops_RRC;

	ZERO_STRUCT(&_hoops_RCHS, _hoops_PACIR);

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, colors, 0, 0, 0, 0, 0, _hoops_GPHC|
																	(single?_hoops_RAIC:_hoops_PAIC));
		return;
	}

	if (nr->transform_rendition->_hoops_CPA != state->_hoops_RPICC)
		_hoops_RIHSC (nr);

	if (state->_hoops_PRGGH) return;

	if (BIT (dc->options._hoops_IRARR, _hoops_RGASC))
		_hoops_ACIAI ("%% triangle\n");

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		int					i;

		if (_hoops_SIGA->pattern != FP_SOLID) {
			_hoops_RCHS.right = _hoops_RCHS.left = points->x;
			_hoops_RCHS.bottom = _hoops_RCHS.top = points->y;
		}
		fprintf (fp, "NP %.2f %.2f MT ", points[0].x, points[0].y);
		_hoops_AGPSC (state);

		for (i=1; i<3; i++) {
			if (_hoops_SIGA->pattern != FP_SOLID) {
				if (points[i].x > _hoops_RCHS.right)
					_hoops_RCHS.right = points[i].x;
				else if (points[i].x < _hoops_RCHS.left)
					_hoops_RCHS.left = points[i].x;

				if (points[i].y > _hoops_RCHS.top)
					_hoops_RCHS.top = points[i].y;
				else if (points[i].y < _hoops_RCHS.bottom)
					_hoops_RCHS.bottom = points[i].y;
			}

			fprintf (fp, "%.2f %.2f LT ", points[i].x, points[i].y);
			_hoops_AGPSC (state);
		}

		_hoops_ACIAI ("CP\n");

		_hoops_HIHSC (nr, &_hoops_RCHS, colors);

		points += _hoops_RRC;
		if (!single)
			colors++;
	}
}

local void _hoops_ACCGA (
	Net_Rendition const &		nr,
	_hoops_GHISP const &		_hoops_RHISP,
	_hoops_AHISP const *				span,
	int							_hoops_PHISP,
	int							bottom) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	FILE alter *				fp = state->fp;

	_hoops_PCCAR {
		int						_hoops_GRISC, _hoops_RRISC;

		_hoops_GRISC = span->left.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
		_hoops_RRISC	= span->right.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;

		if (_hoops_RRISC > _hoops_GRISC) {
			int				left = _hoops_GRISC;
			int				right = _hoops_RRISC;

			if (left < _hoops_IHCR->_hoops_AGAA.left)
				left = _hoops_IHCR->_hoops_AGAA.left;
			if (right > _hoops_IHCR->_hoops_AGAA.right+1)	/* _hoops_CGHI _hoops_AIR _hoops_HAR _hoops_SGAAH */
				right = _hoops_IHCR->_hoops_AGAA.right+1;

			/* _hoops_CPPPR _hoops_ICHRR _hoops_AHRH _hoops_AA _hoops_GIH _hoops_CCA _hoops_ARISC */
			if (right - left < 3) {
				(*state->_hoops_CSASC) (nr, _hoops_RHISP, span, 1, bottom);
			} else {
				int				_hoops_CSHHP;
				int				_hoops_PRISC;
				int				_hoops_SASSR;


				_hoops_CSHHP = span->left.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR -
					 span->right.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
				if (_hoops_CSHHP < 0) _hoops_CSHHP = -_hoops_CSHHP;
				_hoops_PRISC = span->left.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR -
					 span->right.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
				if (_hoops_PRISC < 0) _hoops_PRISC = -_hoops_PRISC;
				_hoops_SASSR = span->left.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR -
					 span->right.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
				if (_hoops_SASSR < 0) _hoops_SASSR = -_hoops_SASSR;

				/* _hoops_AHRH _hoops_CCA _hoops_RGAR 1 _hoops_PAR 2 _hoops_PSHA _hoops_GACC _hoops_AA _hoops_GIH _hoops_CCA _hoops_ARISC */
				if (_hoops_CSHHP <= 1 && _hoops_PRISC <= 1 && _hoops_SASSR <= 1)
					(*state->_hoops_CSASC) (nr, _hoops_RHISP, span, 1, bottom);
				else {
					/* _hoops_SHHSC _hoops_CGH _hoops_SHH _hoops_GIH */

					if (state->_hoops_SSASC &&
						nr->transform_rendition->_hoops_CPA !=
								state->_hoops_RPICC) {
						_hoops_RIHSC (nr);
						state->_hoops_SSASC = false;
					}

					if (state->_hoops_GGPSC) {
						bool		_hoops_HRISC = false;

						if (state->_hoops_CRSRI &&
								!BIT(state->_hoops_CRSRI->flags, LSF_SOLID)) {
							_hoops_ACIAI ("[] 0 SD");
							state->_hoops_CRSRI= nr->_hoops_GCSHP->_hoops_IHRIP;
							state->_hoops_ACASC = (_hoops_GARRR)0;
							_hoops_HRISC = true;
						}

						if (state->_hoops_ICASC != LCAP_BUTT) {
							_hoops_IGPSC (" %d LC ", LCAP_BUTT);
							state->_hoops_ICASC = LCAP_BUTT;
							state->_hoops_ACASC = (_hoops_GARRR)0;
							_hoops_HRISC = true;
						}
						if (state->_hoops_HCASC != 1.0f) {
							_hoops_ACIAI (" 1 LW");
							state->_hoops_HCASC = 1.0f;
							state->_hoops_ACASC = (_hoops_GARRR)0;
							_hoops_HRISC = true;
						}
						if (_hoops_HRISC)
							_hoops_ACIAI ("\n");

						state->_hoops_GGPSC = true;
					}

					fprintf (fp, "%d %d %d %d %d %d %d %d %d GSPAN\n",
								bottom,	 _hoops_GRISC, _hoops_RRISC,
								span->left.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
								span->left.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
								span->left.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
								span->right.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
								span->right.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
								span->right.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR);
				}
			}
		}

		if (--_hoops_PHISP == 0)
			break;
		++span;
		++bottom;
	}
}


#define _hoops_IRISC (0.0039215686f)

local void draw_dc_gouraud_polytriangle (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	FILE alter	*				fp = state->fp;
#if 0
	bool						_hoops_CRISC = true;
#endif

	if (state->_hoops_PRGGH) return;

	if (BIT (dc->options._hoops_IRARR, _hoops_RGASC))
		_hoops_ACIAI ("%% gouraud triangle\n");

/*#_hoops_IHS _hoops_SRISC */
#if 0
	{
	int	 i;

	_hoops_ACIAI ("<< /ShadingType 4 /ColorSpace /DeviceRGB \n/DataSource \n[");
	for (i = 0; i < 3; i++)
	   fprintf (fp, "0 %d %d %1.2f %1.2f %1.2f ",
				(int)points[i].x, (int)points[i].y,
				_hoops_IRISC * colors[i].r, _hoops_IRISC * colors[i].g, _hoops_IRISC * colors[i].b);
	_hoops_ACIAI (fp, "]\n>> \nshfill\n");
	}
#else

	{
		_hoops_APARR &		_hoops_RRCI = (_hoops_APARR alter &) dc->_hoops_ACPGR;

		if (_hoops_RRCI->_hoops_ACCGA != _hoops_ACCGA) {
			state->_hoops_CSASC = _hoops_RRCI->_hoops_ACCGA;
			_hoops_RRCI->_hoops_ACCGA = _hoops_ACCGA;
		}

		state->_hoops_SSASC = true;

		HD_Span_DC_Gouraud_Polytris (nr, count, points, colors);

		_hoops_RRCI->_hoops_ACCGA = state->_hoops_CSASC;
	}
#endif
}




local int _hoops_GAISC (
	RGBAS32 const *		rgb,
	int const			_hoops_SPPI) {

	if (_hoops_SPPI == 1 ||
		rgb[0].r != rgb[1].r ||
		rgb[0].g != rgb[1].g ||
		rgb[0].b != rgb[1].b)
		return 1;

	{
		int				i;
		int				r = rgb->r;
		int				g = rgb->g;
		int				b = rgb->b;

		for (i = 2; i < _hoops_SPPI; i++) {
			if (rgb[i].r != r || rgb[i].g != g || rgb[i].b != b) break;
		}

		return i;
	}
}

/* _hoops_HGI _hoops_HRGR _hoops_RH _hoops_GIGR _hoops_AGAH _hoops_CRAC _hoops_API. _hoops_HHIGR _hoops_RAIA
 * _hoops_CSCHR _hoops_IHCI/_hoops_RRRS _hoops_IS _hoops_RAISC _hoops_AHRH _hoops_PPR _hoops_GIHII _hoops_CPPPR _hoops_AAISC.
 */
local void _hoops_PAISC (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							row_bytes,
	RGBAS32 const *				_hoops_SACCC) {
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	FILE alter *				fp = state->fp;
	RGBAS32 const *				_hoops_PSSAA = _hoops_SACCC;
	int							x, y;
	int							_hoops_GPCCC, _hoops_APCCC, _hoops_PPCCC;
	int							_hoops_HPCCC, _hoops_IPCCC;
	int							_hoops_CPCCC;
	int							_hoops_ICHPP;
	int							length;

	/* _hoops_GGI _hoops_IRS _hoops_RIS _hoops_IIGR _hoops_AIHSR _hoops_AHRH */

	if (nr->transform_rendition->_hoops_CPA != state->_hoops_RPICC)
		_hoops_RIHSC (nr);
	state->_hoops_ACASC = _hoops_RRGH->_hoops_CPA;
	state->_hoops_ARSRI = _hoops_IAASP;

	if (state->_hoops_PRGGH) return;

	if (row_bytes == 0)
		row_bytes = (int) ((end->x - start->x + 1.0f) * (int) sizeof (RGBAS32));

	_hoops_HPCCC = _hoops_IAAA (0, (int) start->y - (int) _hoops_IHCR->_hoops_AGAA.top);
	_hoops_IPCCC = _hoops_IAAA (0, (int) _hoops_IHCR->_hoops_AGAA.left - (int) start->x);
	_hoops_CPCCC = _hoops_IAAA (0, row_bytes +
		((int) start->x - 1 - (int) _hoops_IHCR->_hoops_AGAA.right)*(int) sizeof (RGBAS32));

	_hoops_GPCCC = (int) start->x + _hoops_IPCCC;
	y = (int) start->y - _hoops_HPCCC;
	_hoops_PSSAA = (RGBAS32 const *) (((char *) _hoops_PSSAA) + _hoops_HPCCC*row_bytes);

	_hoops_APCCC = _hoops_AHIA ((int) _hoops_IHCR->_hoops_AGAA.right,  (int) end->x);
	_hoops_PPCCC = _hoops_IAAA ((int) _hoops_IHCR->_hoops_AGAA.bottom, (int) end->y);

	while (y >= _hoops_PPCCC) {
		x = _hoops_GPCCC;
		_hoops_PSSAA += _hoops_IPCCC;

		fprintf (fp, "%d %d MT\n", x, y);
		_hoops_AGPSC (state);
		_hoops_ICHPP = 0;

		while (x <= _hoops_APCCC) {
			if (_hoops_ICHPP >= 72) {
				_hoops_ACIAI ("> CI\n");
				_hoops_ICHPP = 0;
			}
			/* _hoops_ARAS-_hoops_SPCC _hoops_HAISC */
			if ((length = _hoops_GAISC(_hoops_PSSAA, _hoops_APCCC - x + 1)) >= _hoops_SSRSC) {
				if (_hoops_ICHPP > 0) {
					_hoops_ACIAI ("> CI\n");
				}
				fprintf (fp, "%.2f %.2f %.2f %d RLE\n",
						 _hoops_PSSAA->r/(float) _hoops_ACRSC,
						 _hoops_PSSAA->g/(float) _hoops_ACRSC,
						 _hoops_PSSAA->b/(float) _hoops_ACRSC,
						 length);
				_hoops_AGPSC (state);
				_hoops_ICHPP = 0;
				x += length;
				_hoops_PSSAA += length;
			}
			else {
				if (_hoops_ICHPP == 0)
					_hoops_ACIAI ("<");
				fprintf (fp, "%02X%02X%02X", _hoops_PSSAA->r,
								_hoops_PSSAA->g, _hoops_PSSAA->b);
				_hoops_AGPSC (state);
				++_hoops_PSSAA;
				x++;
				_hoops_ICHPP += 6;
			}
		}
		if (_hoops_ICHPP > 0) {
			_hoops_ACIAI ("> CI\n");
			_hoops_ICHPP = 0;
		}
		_hoops_PSSAA = (RGBAS32 const *) (((char *) _hoops_PSSAA) + _hoops_CPCCC);
		y--;
	}
}


#define _hoops_IAISC(x,y) (((x)->r == (y)->r) && ((x)->g == (y)->g) && ((x)->b == (y)->b))

local void _hoops_CAISC (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							row_bytes,
	RGBAS32 const *				_hoops_SACCC) {
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	FILE alter *				fp = state->fp;
	int							x, y;
	int							_hoops_GPCCC, _hoops_RPCCC, _hoops_APCCC, _hoops_PPCCC;
	int							_hoops_HPCCC, _hoops_IPCCC;
	int							width;
	int							height;
	int							_hoops_SAISC;

	/* _hoops_GGI _hoops_IRS _hoops_RIS _hoops_IIGR _hoops_AIHSR _hoops_AHRH */

	if (nr->transform_rendition->_hoops_CPA != state->_hoops_RPICC)
		_hoops_RIHSC (nr);
	state->_hoops_ACASC = _hoops_RRGH->_hoops_CPA;
	state->_hoops_ARSRI = _hoops_IAASP;

	if (state->_hoops_PRGGH) return;

	if (row_bytes == 0)
		row_bytes = (int)((end->x - start->x + 1.0f) * (int) sizeof (RGBAS32));

	_hoops_HPCCC = _hoops_IAAA (0, (int) start->y - (int) _hoops_IHCR->_hoops_AGAA.top);
	_hoops_IPCCC = _hoops_IAAA (0, (int) _hoops_IHCR->_hoops_AGAA.left - (int) start->x);

	_hoops_GPCCC = (int) start->x + _hoops_IPCCC;
	_hoops_RPCCC = y = (int) start->y - _hoops_HPCCC;

	_hoops_APCCC = _hoops_AHIA  ((int) _hoops_IHCR->_hoops_AGAA.right, (int) end->x);
	_hoops_PPCCC = _hoops_IAAA  ((int) _hoops_IHCR->_hoops_AGAA.bottom, (int) end->y);

	/* _hoops_IPCP _hoops_RSIR _hoops_PRCGH _hoops_HRGR _hoops_SACH _hoops_SGGR.	 _hoops_ARRP _hoops_IS _hoops_AA. */
	if (_hoops_GPCCC > _hoops_APCCC || _hoops_RPCCC < _hoops_PPCCC) return;

	width = _hoops_APCCC - _hoops_GPCCC + 1;
	height = _hoops_RPCCC - _hoops_PPCCC + 1;

	_hoops_SACCC = (RGBAS32 const *) (((char *) _hoops_SACCC) + _hoops_HPCCC*row_bytes);

	if (state->_hoops_PSASC == _hoops_SGASC)
	{
#if 0
/* _hoops_GASA: _hoops_RGR _hoops_RRGR _hoops_RIS _hoops_GRGR _hoops_PGGA _hoops_GHAP _hoops_GPISC _hoops_HHH _hoops_CSSHH _hoops_RPISC */

	  /* _hoops_GASA: _hoops_APISC _hoops_IGAA 1 _hoops_GAR _hoops_IRS _hoops_GRH _hoops_AGIR _hoops_IH _hoops_ARISC _hoops_HACAR _hoops_IRS _hoops_RSCA _hoops_IGRH _hoops_IIGR _hoops_GC.
	   * _hoops_IH _hoops_PCAI, _hoops_SCH _hoops_PPISC 60_hoops_ARGI _hoops_HII _hoops_IRS 1.8_hoops_RPRAR _hoops_HGPPC _hoops_RGHR. */
	  if (width == 1)
	  {
		fprintf(fp,"%d %d PIX\n", _hoops_GPCCC, _hoops_PPCCC);
		fprintf (fp, "%02X%02X%02X",
				_hoops_PSSAA->r, _hoops_PSSAA->g, _hoops_PSSAA->b);
	  }
	  else
#endif
	  {
		/* _hoops_ARAS-_hoops_SPCC _hoops_IPISR */
		RGBAS32 const				*_hoops_PSSAA = _hoops_SACCC;
		int				_hoops_HPISC;		/* _hoops_SPCC _hoops_IIGR _hoops_SCGR _hoops_ARAS */
		const RGBAS32	*_hoops_IPISC;	/* _hoops_HAIR _hoops_HPGR _hoops_HSPP _hoops_IIGR _hoops_ARAS */

		if (height == 1)
			fprintf(fp,"%d %d %d SRLE\n", _hoops_GPCCC, _hoops_PPCCC, width);
		else
			fprintf(fp,"%d %d %d %d IRLE\n", _hoops_GPCCC, _hoops_PPCCC, width, height);

		_hoops_AGPSC (state);

		_hoops_SAISC = 0;
		while (y >= _hoops_PPCCC)
		{

			x = _hoops_GPCCC;
			_hoops_PSSAA = _hoops_SACCC + _hoops_IPCCC;

			while (x <= _hoops_APCCC)
			{
				_hoops_HPISC = 0;
				_hoops_IPISC = _hoops_PSSAA;

				/* _hoops_ACGR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_ARAS.
				 * _hoops_PS _hoops_CHR _hoops_GICPR _hoops_IS _hoops_SSSS _hoops_RGR _hoops_HAPR _hoops_HPGR _hoops_CHGC _hoops_ARR */
				while (_hoops_IAISC (_hoops_PSSAA, _hoops_IPISC) && (x <= _hoops_APCCC) && (_hoops_HPISC < 255))
				{
					_hoops_HPISC++;
					x++;
					_hoops_PSSAA++;
				}

				/* _hoops_GSCSR _hoops_RH _hoops_PRCGH _hoops_GGSR _hoops_IS _hoops_RH _hoops_RGHR */
					fprintf (fp, "%02X%02X%02X%02X",
						_hoops_HPISC, _hoops_IPISC->r, _hoops_IPISC->g, _hoops_IPISC->b);

				_hoops_AGPSC (state);
				_hoops_HPISC = 0;
				_hoops_SAISC += 8;

				if (_hoops_SAISC >= 80)
				{
					_hoops_ACIAI ("\n");
					_hoops_SAISC = 0;
				}
			} /* _hoops_RSGR _hoops_HPGP (_hoops_SISR) */

			_hoops_SACCC = (RGBAS32 const *) (((char *) _hoops_SACCC) + row_bytes);
			y--;
		} /* _hoops_RSGR _hoops_HPGP (_hoops_HAPC) */
	  }
	}
	else
	{

		RGBAS32 const				*_hoops_PSSAA = _hoops_SACCC;
		fprintf(fp,"%d %d %d %d IMG\n", _hoops_GPCCC, _hoops_PPCCC, width, height);
		_hoops_AGPSC (state);

		_hoops_SAISC = 0;
		while (y >= _hoops_PPCCC) {

			x = _hoops_GPCCC;
			_hoops_PSSAA = _hoops_SACCC + _hoops_IPCCC;

			while (x <= _hoops_APCCC) {
			  fprintf (fp, "%02X%02X%02X", _hoops_PSSAA->r,
					   _hoops_PSSAA->g, _hoops_PSSAA->b);
			  _hoops_AGPSC (state);

			  _hoops_SAISC += 6;
			  _hoops_PSSAA++;
			  x++;

			  if (_hoops_SAISC >= 78)
				{
				  _hoops_ACIAI ("\n");
				  _hoops_SAISC = 0;
				}
			}

			_hoops_SACCC = (RGBAS32 const *) (((char *) _hoops_SACCC) + row_bytes);
			y--;
		}
	}

	if (_hoops_SAISC > 0)
		_hoops_ACIAI ("\n");
}

local void draw_dc_rgb32_rasters (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							row_bytes,
	RGBAS32 const *				_hoops_SACCC) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);

  if (state->_hoops_PSASC != _hoops_IGASC)
	_hoops_CAISC(nr, start, end, row_bytes, _hoops_SACCC);
  else
	_hoops_PAISC(nr, start, end, row_bytes, _hoops_SACCC);
}


local	const unsigned char		_hoops_RPCSR[256 - 32] = {
 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149,
 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149,
 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149,
 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149,
 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149,
 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149,	  0,
   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,
   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,
   0, 149, 149, 149, 149, 149,	 0, 149, 149,	0, 149, 149,   0, 149,	 0, 149,
 149,	0,	 0,	  0, 149,	0, 149, 149, 149,	0, 149, 149,   0,	0,	 0, 149,
 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149,
   0, 149, 149, 149, 149, 149, 149,	  0, 149, 149, 149, 149, 149,	0,	 0, 149,
 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149,
   0, 149, 149, 149, 149, 149, 149,	  0, 149, 149, 149, 149, 149,	0,	 0, 149,
};

local	const unsigned char		_hoops_RRICC[256 - 32] = {
  70,  78,	89, 138, 138, 220, 165,	 56,  83,  83,	97, 145,  70,  83,	70,	 70,
 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,	70,	 70, 145, 145, 145, 138,
 250, 165, 165, 179, 179, 165, 152, 192, 179,  70, 124, 165, 138, 206, 179, 192,
 165, 192, 179, 165, 152, 179, 165, 233, 165, 165, 152,	 70,  70,  70, 117, 138,
  56, 138, 138, 124, 138, 138,	70, 138, 138,  56,	56, 124,  56, 206, 138, 138,
 138, 138,	83, 124,  70, 138, 124, 179, 124, 124, 124,	 84,  66,  84, 145,	  0,
   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,
   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,
   0,  83, 138, 138, 138, 138,	 0, 138,  83,	0,	93, 138,   0, 138,	 0, 247,
  83,	0,	 0,	  0,  83,	0, 133,	 70,  83,	0,	91, 138,   0,	0,	 0, 152,
 165, 165, 165, 165, 165, 165, 247, 179, 165, 165, 165, 165,  70,  70,	70,	 70,
   0, 179, 192, 192, 192, 192, 192,	  0, 192, 179, 179, 179, 179,	0,	 0, 152,
 138, 138, 138, 138, 138, 138, 220, 124, 138, 138, 138, 138,  70,  70,	70,	 70,
   0, 138, 138, 138, 138, 138, 138,	  0, 152, 138, 138, 138, 138,	0,	 0, 124,
};

local	const unsigned char		_hoops_ARICC[256 - 32] = {
  70,  83, 118, 138, 138, 220, 179,	 70,  83,  83,	97, 145,  70,  83,	70,	 70,
 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,	83,	 83, 145, 145, 145, 152,
 241, 179, 179, 179, 179, 165, 152, 192, 179,  70, 138, 179, 152, 206, 179, 192,
 165, 192, 179, 165, 152, 179, 165, 233, 165, 165, 152,	 83,  70,  83, 145, 138,
  70, 138, 152, 138, 152, 138,	83, 152, 152,  70,	70, 138,  70, 220, 152, 152,
 152, 152,	97, 138,  83, 152, 138, 192, 138, 138, 124,	 97,  71,  97, 145,	  0,
   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,
   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,
   0,  83, 138, 138, 138, 138,	 0, 138,  83,	0,	93, 138,   0, 138,	 0, 247,
  83,	0,	 0,	  0,  83,	0, 138,	 70,  83,	0,	91, 138,   0,	0,	 0, 152,
 179, 179, 179, 179, 179, 179, 247, 179, 165, 165, 165, 165,  70,  70,	70,	 70,
   0, 179, 192, 192, 192, 192, 192,	  0, 192, 179, 179, 179, 179,	0,	 0, 152,
 138, 138, 138, 138, 138, 138, 220, 138, 138, 138, 138, 138,  70,  70,	70,	 70,
   0, 152, 152, 152, 152, 152, 152,	  0, 152, 152, 152, 152, 152,	0,	 0, 138,
};

local	const unsigned char		_hoops_PPCSR[256 - 32] = {
  63,  83, 102, 124, 124, 206, 192,	 83,  83,  83, 124, 140,  63,  83,	63,	 70,
 124, 124, 124, 124, 124, 124, 124, 124, 124, 124,	70,	 70, 140, 140, 140, 111,
 227, 179, 165, 165, 179, 152, 138, 179, 179,  83,	97, 179, 152, 220, 179, 179,
 138, 179, 165, 138, 152, 179, 179, 233, 179, 179, 152,	 83,  70,  83, 117, 124,
  83, 111, 124, 111, 124, 111,	83, 124, 124,  70,	70, 124,  70, 192, 124, 124,
 124, 124,	83,	 97,  70, 124, 124, 179, 124, 124, 111, 119,  51, 119, 134,	  0,
   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,
   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,
   0,  83, 124, 124, 124, 124,	 0, 124,  83,	0,	70, 124,   0, 124,	 0, 247,
  83,	0,	 0,	  0,  83,	0, 113,	 63,  83,	0,	78, 124,   0,	0,	 0, 111,
 179, 179, 179, 179, 179, 179, 220, 165, 152, 152, 152, 152,  83,  83,	83,	 83,
   0, 179, 179, 179, 179, 179, 179,	  0, 179, 179, 179, 179, 179,	0,	 0, 124,
 111, 111, 111, 111, 111, 111, 165, 111, 111, 111, 111, 111,  70,  70,	70,	 70,
   0, 124, 124, 124, 124, 124, 124,	  0, 124, 124, 124, 124, 124,	0,	 0, 124,
};

local	const unsigned char		_hoops_PRICC[256 - 32] = {
  63,  83, 105, 124, 124, 206, 192,	 83,  83,  83, 124, 167,  63,  83,	63,	 70,
 124, 124, 124, 124, 124, 124, 124, 124, 124, 124,	83,	 83, 167, 167, 167, 124,
 227, 152, 152, 165, 179, 152, 152, 179, 179,  83, 111, 165, 138, 206, 165, 179,
 152, 179, 152, 124, 138, 179, 152, 206, 152, 138, 138,	 97,  70,  97, 105, 124,
  83, 124, 124, 111, 124, 111,	70, 124, 124,  70,	70, 111,  70, 179, 124, 124,
 124, 124,	97,	 97,  70, 124, 111, 165, 111, 111,	97, 100,  69, 100, 134,	  0,
   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,
   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,
   0,  97, 124, 124, 124, 124,	 0, 124,  83,	0,	70, 124,   0, 124,	 0, 220,
  83,	0,	 0,	  0,  83,	0, 130,	 63,  83,	0,	78, 124,   0,	0,	 0, 124,
 152, 152, 152, 152, 152, 152, 220, 165, 152, 152, 152, 152,  83,  83,	83,	 83,
   0, 165, 179, 179, 179, 179, 179,	  0, 179, 179, 179, 179, 179,	0,	 0, 124,
 124, 124, 124, 124, 124, 124, 165, 111, 111, 111, 111, 111,  70,  70,	70,	 70,
   0, 124, 124, 124, 124, 124, 124,	  0, 124, 124, 124, 124, 124,	0,	 0, 111,
};

local	const unsigned char		_hoops_HRICC[256 - 32] = {
  63,  83, 138, 124, 124, 247, 206,	 83,  83,  83, 124, 141,  63,  83,	63,	 70,
 124, 124, 124, 124, 124, 124, 124, 124, 124, 124,	83,	 83, 141, 141, 141, 124,
 230, 179, 165, 179, 179, 165, 152, 192, 192,  97, 124, 192, 165, 233, 179, 192,
 152, 192, 179, 138, 165, 179, 179, 247, 179, 179, 165,	 83,  70,  83, 144, 124,
  83, 124, 138, 111, 138, 111,	83, 124, 138,  70,	83, 138,  70, 206, 138, 124,
 138, 138, 111,	 97,  83, 138, 124, 179, 124, 124, 111,	 98,  56,  98, 129,	  0,
   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,
   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,
   0,  83, 124, 124, 124, 124,	 0, 124,  83,	0,	75, 124,   0, 124,	 0, 247,
  83,	0,	 0,	  0,  83,	0, 134,	 63,  83,	0,	83, 124,   0,	0,	 0, 124,
 179, 179, 179, 179, 179, 179, 247, 179, 165, 165, 165, 165,  97,  97,	97,	 97,
   0, 179, 192, 192, 192, 192, 192,	  0, 192, 179, 179, 179, 179,	0,	 0, 138,
 124, 124, 124, 124, 124, 124, 179, 111, 111, 111, 111, 111,  70,  70,	70,	 70,
   0, 138, 124, 124, 124, 124, 124,	  0, 124, 138, 138, 138, 138,	0,	 0, 124,
};

local	const unsigned char		_hoops_IRICC[256 - 32] = {
  63,  97, 138, 124, 124, 206, 192,	 83,  83,  83, 124, 141,  63,  83,	63,	 70,
 124, 124, 124, 124, 124, 124, 124, 124, 124, 124,	83,	 83, 141, 141, 141, 124,
 206, 165, 165, 165, 179, 165, 165, 179, 192,  97, 124, 165, 152, 220, 179, 179,
 152, 179, 165, 138, 152, 179, 165, 220, 165, 152, 152,	 83,  70,  83, 141, 124,
  83, 124, 124, 111, 124, 111,	83, 124, 138,  70,	70, 124,  70, 192, 138, 124,
 124, 124,	97,	 97,  70, 138, 111, 165, 124, 111,	97,	 87,  56,  87, 141,	  0,
   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,
   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,
   0,  97, 124, 124, 124, 124,	 0, 124,  83,	0,	67, 124,   0, 124,	 0, 247,
  83,	0,	 0,	  0,  83,	0, 124,	 63,  83,	0,	75, 124,   0,	0,	 0, 124,
 165, 165, 165, 165, 165, 165, 233, 165, 165, 165, 165, 165,  97,  97,	97,	 97,
   0, 179, 179, 179, 179, 179, 179,	  0, 179, 179, 179, 179, 179,	0,	 0, 124,
 124, 124, 124, 124, 124, 124, 179, 111, 111, 111, 111, 111,  70,  70,	70,	 70,
   0, 138, 124, 124, 124, 124, 124,	  0, 124, 138, 138, 138, 138,	0,	 0, 111,
};

local	const unsigned char		_hoops_HPCSR[256 - 32] = {
  63,  83, 176, 124, 136, 206, 192, 109,  83,  83, 124, 136,  63, 136,	63,	 70,
 124, 124, 124, 124, 124, 124, 124, 124, 124, 124,	70,	 70, 136, 136, 136, 111,
 136, 179, 165, 179, 152, 152, 189, 150, 179,  83, 156, 179, 170, 220, 179, 179,
 190, 183, 138, 147, 152, 171, 109, 190, 160, 197, 152,	 83, 213,  83, 163, 124,
 124, 156, 136, 136, 123, 109, 130, 103, 150,  83, 150, 136, 136, 143, 130, 136,
 136, 130, 136, 150, 109, 143, 176, 170, 123, 170, 123, 119,  51, 119, 136,	  0,
   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,
   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,   0,	0,	 0,	  0,
   0, 154,	62, 136,  43, 176, 124, 186, 186, 186, 186, 255, 244, 150, 244, 150,
 100, 136, 103, 136, 136, 176, 123, 115, 136, 136, 136, 136, 247, 150, 247, 163,
 203, 170, 197, 244, 190, 190, 203, 190, 190, 176, 176, 176, 176, 176, 176, 176,
 190, 176, 195, 195, 220, 203, 136,	 63, 176, 150, 150, 255, 244, 150, 244, 150,
 123,  83, 195, 195, 194, 176,	96,	 96,  96,  96,	96,	 96, 123, 123, 123, 123,
   0,  83,	69, 170, 170, 170,	96,	 96,  96,  96,	96,	 96, 123, 123, 123,	  0,
};


#define _hoops_IACSR(x) (float)(1.0f/(x))

local void find_all_fonts (
	Display_Context alter	*dc) {
	_hoops_HIASC alter				*state = _hoops_ARPSC (dc);
	_hoops_HCRPR						filter;
	_hoops_HCRPR						filename;
	void alter					*_hoops_CPISC;
	void alter					*_hoops_CRIPH;
	_hoops_HCRPR						_hoops_GGHGA, _hoops_RGHGA;
	int							mask, value;
	bool					_hoops_CPCA;
	bool					_hoops_SPISC = false;
	/*
	 * _hoops_ASC _hoops_SHHPC _hoops_RGGHR _hoops_ISPR _hoops_RPP _hoops_IIH _hoops_CHR _hoops_ASPRH-_hoops_RCCGI-_hoops_GHISC _hoops_PAR
	 * _hoops_ASPRH-_hoops_RCCGI, _hoops_RHISC-_hoops_GHISC, _hoops_RHISC, _hoops_AHISC, _hoops_PPR _hoops_AHISC-
	 * _hoops_GHISC.
	 */
	short						_hoops_PHISC = 0,
											_hoops_HHISC = 0,
											_hoops_IHISC = 0,
											_hoops_CHISC = 0,
											_hoops_SHISC = 0,
											_hoops_GIISC = 0;

	_hoops_AAPIR				*_hoops_RIISC;

	/*
	 * _hoops_CGP _hoops_RH _hoops_IPSP _hoops_SSCP _hoops_CHIA _hoops_PCCP _hoops_PAPSC _hoops_RGHR _hoops_CHHR ,
	 *	 _hoops_IRIGR _hoops_HCR ._hoops_AIISC _hoops_GSIHH _hoops_RHAPA _hoops_RH _hoops_CAAAI _hoops_PIISC _hoops_GAR _hoops_RH _hoops_AGAH _hoops_HRCSR _hoops_SGGGH
	 * _hoops_SHS _hoops_SR _hoops_GAGPR _hoops_SGH _hoops_RH _hoops_ACIPR _hoops_HIISC _hoops_HRASC _hoops_GSPIP.
	 */

	if ((_hoops_RIISC = HOOPS_WORLD->_hoops_AAGHP) != null) do {

		/*
		 * _hoops_PS _hoops_CHR _hoops_RGAR _hoops_GPIHR _hoops_GGR _hoops_SRRAH ._hoops_AIISC _hoops_GSIHH.
		 */
		value = mask = DIR_Select_File | DIR_Select_Readable;
		HI_Copy_Chars_To_Name ("*.afm", &filter);

		_hoops_GGHGA.length = _hoops_RGHGA.length = 0;
		if (!HI_Open_Directory (&_hoops_RIISC->name, &filter,
				mask, value, &_hoops_CPISC, &_hoops_GGHGA, &_hoops_RGHGA)) {
			char			_hoops_RAGH[MAX_ERRMSG];
			char			_hoops_AAGH[MAX_ERRMSG];

			HI_Copy_Name_To_Chars (&_hoops_GGHGA, _hoops_RAGH);
			HI_Copy_Name_To_Chars (&_hoops_RGHGA, _hoops_AAGH);
			HE_ERROR2 (HEC_POSTSCRIPT_DRIVER, HES_DIRECTORY_OPEN, _hoops_RAGH, _hoops_AAGH);
			_hoops_RGAIR (_hoops_GGHGA);
			_hoops_RGAIR (_hoops_RGHGA);
			_hoops_RGAIR (filter);
			continue;
		}

		_hoops_GGHGA.length = _hoops_RGHGA.length = 0;
		_hoops_RGGA ((_hoops_CPCA = HI_Read_Directory (_hoops_CPISC, &filename,
										 &_hoops_GGHGA, &_hoops_RGHGA)) == 0 ||
			   filename.length == 0) {
			char			_hoops_IIISC[1024];
			_hoops_HCRPR			_hoops_PSHAP;
			char			font_name[512];
			int				_hoops_CIISC = 0;
			short			_hoops_ARASC = 0;

			_hoops_SPISC = true;

			HI_Copy_Name (&_hoops_RIISC->name, &_hoops_PSHAP);
			HI_Add_Path_Delimiter (&_hoops_PSHAP, &filename);
			Sprintf_NN (_hoops_IIISC, "%n%n", &_hoops_PSHAP, &filename);
			_hoops_RGAIR (_hoops_PSHAP);
			_hoops_RGAIR (filename);
			HI_Copy_Chars_To_Name (_hoops_IIISC, &filename);

			/*
			 * _hoops_CIAPI _hoops_RH _hoops_PAPSC _hoops_RGHR _hoops_PPR _hoops_RHAPA _hoops_RH _hoops_CAAAI _hoops_SIISC _hoops_GAR _hoops_RH _hoops_GCISC
			 */
			_hoops_GGHGA.length = _hoops_RGHGA.length = 0;
			if (!HI_Open_File (&filename, FILE_For_Reading, &_hoops_CRIPH,
							   false, &_hoops_GGHGA, &_hoops_RGHGA)) {
				char			_hoops_RAGH[MAX_ERRMSG];
				char			_hoops_AAGH[MAX_ERRMSG];

				HI_Copy_Name_To_Chars (&_hoops_GGHGA, _hoops_RAGH);
				HI_Copy_Name_To_Chars (&_hoops_RGHGA, _hoops_AAGH);
				HE_ERROR2 (HEC_POSTSCRIPT_DRIVER, HES_FILE_OPEN, _hoops_RAGH, _hoops_AAGH);
				_hoops_RGAIR (_hoops_GGHGA);
				_hoops_RGAIR (_hoops_RGHGA);
			}

			else {
				char			buf[512];
				char alter		*_hoops_ASAPR = &buf[512];
				char			line[256];
				char alter		*_hoops_CAPSC;
				int				_hoops_RCISC;

				do {
					_hoops_SRPSC (_hoops_CRIPH, buf, buf + _hoops_GGAPR (buf), &_hoops_ASAPR, line);
					_hoops_CAPSC = line;
					_hoops_RCISC = _hoops_HAPSC (_hoops_PIASC, &_hoops_CAPSC);

					if (_hoops_RCISC == _hoops_AAASC) {
						while (*_hoops_CAPSC == ' ' || *_hoops_CAPSC == '\t') ++_hoops_CAPSC;
						_hoops_AAHR (_hoops_CAPSC, font_name);
					}
					else if (_hoops_RCISC == _hoops_PAASC) {
						while (*_hoops_CAPSC == ' ' || *_hoops_CAPSC == '\t') ++_hoops_CAPSC;
						if (_hoops_AGGR (_hoops_CAPSC, "AdobeStandardEncoding"))
							_hoops_ARASC = (short) _hoops_IRASC;
						else
							_hoops_ARASC = (short) _hoops_CRASC;
					}
					else if (_hoops_RCISC == _hoops_CPASC) {
						while (*_hoops_CAPSC == ' ' || *_hoops_CAPSC == '\t') ++_hoops_CAPSC;
						HI_Scan_Integer (dc->_hoops_RIGC, (char const * alter *)&_hoops_CAPSC, null, &_hoops_CIISC);
						_hoops_CIISC = (int) _hoops_IACSR (_hoops_CIISC * 0.001f);
					}
				} _hoops_RGGA (_hoops_RCISC == _hoops_AIASC);

				/*
				 * _hoops_CGP _hoops_IIH _hoops_HRGR _hoops_PSP _hoops_ACISC _hoops_GGR _hoops_RH _hoops_PAPSC _hoops_RGHR _hoops_SR _hoops_HSRS 708 _hoops_GAR _hoops_RH _hoops_SHIR,
				 * _hoops_IPCP _hoops_HPRGR _hoops_PCISC _hoops_PPR _hoops_HCISC _hoops_AA _hoops_HAR _hoops_HS _hoops_ACISC _hoops_HIS _hoops_SR _hoops_HSRS
				 * _hoops_RH _hoops_PHRHA	_hoops_ICISC _hoops_GAR _hoops_RH _hoops_SHIR.
				 *
				 */
				if (_hoops_CIISC == 0)
						_hoops_CIISC = (int) _hoops_IACSR (0.708f);

				_hoops_HPPSC (font_name, _hoops_IIISC, &_hoops_ARASC, state);

				HD_Record_Font (dc, font_name, "", 0.0f,(float) _hoops_CIISC);

				/*
				 * _hoops_HSCRH _hoops_RH _hoops_PHIGR _hoops_GSPIP _hoops_RPP _hoops_IIH _hoops_HRGR _hoops_CCISC-_hoops_RCCGI, _hoops_AHISC, _hoops_PAR _hoops_RHISC
				 * _hoops_SHS _hoops_AGAH _hoops_PHIGR _hoops_GSPIP _hoops_CHH _hoops_SHH _hoops_ACHPP.
				 */

				if (_hoops_AGGR (font_name, "Times-Roman-ISOLatin1"))
					_hoops_PHISC = 1;
				else if (_hoops_AGGR (font_name, "Helvetica-ISOLatin1"))
					_hoops_IHISC = 1;
				else if (_hoops_AGGR (font_name, "Courier-ISOLatin1"))
					_hoops_SHISC = 1;
				else if (_hoops_AGGR (font_name, "Times-Roman"))
					_hoops_HHISC = 1;
				else if (_hoops_AGGR (font_name, "Helvetica"))
					_hoops_CHISC = 1;
				else if (_hoops_AGGR (font_name, "Courier"))
					_hoops_GIISC = 1;

				/*
				 * _hoops_PGII _hoops_PAPSC _hoops_GSPIP _hoops_CHR _hoops_GRRRI
				 */

				HD_Mark_Font_As_Transformable (dc, font_name, _hoops_HAGGH);

				_hoops_GGHGA.length = _hoops_RGHGA.length = 0;
				if (!HI_Close_File (_hoops_CRIPH,  &_hoops_GGHGA, &_hoops_RGHGA)) {
					char			_hoops_RAGH[MAX_ERRMSG];
					char			_hoops_AAGH[MAX_ERRMSG];

					HI_Copy_Name_To_Chars (&_hoops_GGHGA, _hoops_RAGH);
					HI_Copy_Name_To_Chars (&_hoops_RGHGA, _hoops_AAGH);
					HE_ERROR2 (HEC_POSTSCRIPT_DRIVER, HES_DIRECTORY_CLOSE, _hoops_RAGH, _hoops_AAGH);
					_hoops_RGAIR (_hoops_GGHGA);
					_hoops_RGAIR (_hoops_RGHGA);
				}
			}

			_hoops_RGAIR (filename);
		}

		/*
		 * _hoops_HSCRH _hoops_GHAGI _hoops_SCISC _hoops_GAR _hoops_RH _hoops_GSISC _hoops_PHIGR _hoops_GSPIP
		 */

		if (_hoops_PHISC) {
			HD_Mark_Font_As_Generic (dc, "Times-Roman-ISOLatin1", GFN_ROMAN);
		}
		else if (_hoops_HHISC) {
			HD_Mark_Font_As_Generic (dc, "Times-Roman", GFN_ROMAN);
		}


		if (_hoops_IHISC) {
			HD_Mark_Font_As_Generic (dc, "Helvetica-ISOLatin1", GFN_SANS_SERIF);
		}
		else if (_hoops_CHISC) {
			HD_Mark_Font_As_Generic (dc, "Helvetica", GFN_SANS_SERIF);
		}

		if (_hoops_SHISC) {
			HD_Mark_Font_As_Generic (dc, "Courier-ISOLatin1",	GFN_TYPEWRITER);
		}
		else if (_hoops_GIISC) {
			HD_Mark_Font_As_Generic (dc, "Courier",		GFN_TYPEWRITER);
		}

		/*
		 * _hoops_CGP _hoops_IIH _hoops_HRGR _hoops_PA _hoops_RHPH _hoops_GGR _hoops_RSISC, _hoops_CAHP _hoops_PCCP _hoops_RIHH _hoops_GPSRR
		 */

		if (!_hoops_CPCA) {
			char			_hoops_RAGH[MAX_ERRMSG];
			char			_hoops_AAGH[MAX_ERRMSG];

			HI_Copy_Name_To_Chars (&_hoops_GGHGA, _hoops_RAGH);
			HI_Copy_Name_To_Chars (&_hoops_RGHGA, _hoops_AAGH);
			HE_ERROR2 (HEC_POSTSCRIPT_DRIVER, HES_DIRECTORY_READ, _hoops_RAGH, _hoops_AAGH);
			_hoops_RGAIR (_hoops_GGHGA);
			_hoops_RGAIR (_hoops_RGHGA);
		}

		_hoops_GGHGA.length = _hoops_RGHGA.length = 0;
		if (!HI_Close_Directory (_hoops_CPISC, &_hoops_GGHGA, &_hoops_RGHGA)) {
			char			_hoops_RAGH[MAX_ERRMSG];
			char			_hoops_AAGH[MAX_ERRMSG];

			HI_Copy_Name_To_Chars (&_hoops_GGHGA, _hoops_RAGH);
			HI_Copy_Name_To_Chars (&_hoops_RGHGA, _hoops_AAGH);
			HE_ERROR2 (HEC_POSTSCRIPT_DRIVER, HES_DIRECTORY_CLOSE, _hoops_RAGH, _hoops_AAGH);
			_hoops_RGAIR (_hoops_GGHGA);
			_hoops_RGAIR (_hoops_RGHGA);
		}

		_hoops_RGAIR (filter);
	}
	_hoops_RGGA ((_hoops_RIISC = _hoops_RIISC->next) == null);

	if (!_hoops_SPISC) {
		HD_Record_Font (dc, "Times-Roman",		"", 0.0f, _hoops_IACSR(0.6759));
		HD_Record_Font (dc, "Times-Italic",		"", 0.0f, _hoops_IACSR(0.6720));
		HD_Record_Font (dc, "Times-Bold",		"", 0.0f, _hoops_IACSR(0.6809));
		HD_Record_Font (dc, "Times-BoldItalic", "", 0.0f, _hoops_IACSR(0.6759));
		HD_Record_Font (dc, "Helvetica",		"", 0.0f, _hoops_IACSR(0.7290));
		HD_Record_Font (dc, "Helvetica-Oblique","", 0.0f, _hoops_IACSR(0.7290));
		HD_Record_Font (dc, "Helvetica-Bold",	"", 0.0f, _hoops_IACSR(0.7290));
		HD_Record_Font (dc, "Helvetica-BoldOblique","", 0.0f, _hoops_IACSR(0.7290));
		HD_Record_Font (dc, "Courier",			"", 0.0f, _hoops_IACSR(0.7290));
		HD_Record_Font (dc, "Courier-Oblique",	"", 0.0f, _hoops_IACSR(0.7290));
		HD_Record_Font (dc, "Courier-Bold",		"", 0.0f, _hoops_IACSR(0.7290));
		HD_Record_Font (dc, "Courier-BoldOblique", "", 0.0f, _hoops_IACSR(0.7290));

		HD_Record_Font (dc, "Symbol",			"", 0.0f, _hoops_IACSR(0.6729));

		HD_Mark_Font_As_Generic (dc, "Times-Roman", GFN_ROMAN);
		HD_Mark_Font_As_Generic (dc, "Helvetica",	GFN_SANS_SERIF);
		HD_Mark_Font_As_Generic (dc, "Courier",		GFN_TYPEWRITER);

		HD_Mark_Font_As_Transformable (dc, "Times-Roman",		_hoops_HAGGH);
		HD_Mark_Font_As_Transformable (dc, "Times-Italic",		_hoops_HAGGH);
		HD_Mark_Font_As_Transformable (dc, "Times-Bold",		_hoops_HAGGH);
		HD_Mark_Font_As_Transformable (dc, "Times-BoldItalic",	_hoops_HAGGH);
		HD_Mark_Font_As_Transformable (dc, "Helvetica",			_hoops_HAGGH);
		HD_Mark_Font_As_Transformable (dc, "Helvetica-Oblique", _hoops_HAGGH);
		HD_Mark_Font_As_Transformable (dc, "Helvetica-Bold",	_hoops_HAGGH);
		HD_Mark_Font_As_Transformable (dc, "Helvetica-BoldOblique", _hoops_HAGGH);
		HD_Mark_Font_As_Transformable (dc, "Courier",			_hoops_HAGGH);
		HD_Mark_Font_As_Transformable (dc, "Courier-Oblique",	_hoops_HAGGH);
		HD_Mark_Font_As_Transformable (dc, "Courier-Bold",		_hoops_HAGGH);
		HD_Mark_Font_As_Transformable (dc, "Courier-BoldOblique", _hoops_HAGGH);
		HD_Mark_Font_As_Transformable (dc, "Symbol",			_hoops_HAGGH);
	}
}


struct _hoops_PSISR {
	int	 _hoops_CSISR;
	float _hoops_HSISR[256];
};

local bool measure_char(
	Net_Rendition const & nr,
	Font_Instance const * instance,
	Karacter _hoops_IPCSR,
	float alter *_hoops_GGGS,
	bool alter *_hoops_CPCSR,
	void ** _hoops_SPCSR) {
	_hoops_PSISR *_hoops_RHCSR = (_hoops_PSISR*) instance->_hoops_GAASR;
	int index = _hoops_IPCSR & 0x00FF;

	UNREFERENCED(nr);

	if (_hoops_RHCSR->_hoops_HSISR[index] != 0.0f) {
		*_hoops_GGGS = _hoops_RHCSR->_hoops_HSISR[index];
		*_hoops_CPCSR = false;
	}
	else {
		*_hoops_GGGS = 0.0f;
		*_hoops_CPCSR = true;
	}

	*_hoops_SPCSR = (void*)1;

	return true;
}


local void * load_font (
	Display_Context const *	dc,
	char const *			name,
	Font_Instance alter *	instance) 
{
	_hoops_HIASC alter *			state = _hoops_ARPSC (dc);
	FILE alter *			fp = state->fp;
	float					_hoops_CCCRP;
	Integer32 alter			height = (Integer32)instance->_hoops_IGGGH;
	bool					_hoops_SPISC = false;
	short					_hoops_ARASC = _hoops_IRASC;
	char					string[_hoops_CSRSC];

	_hoops_PSISR *			_hoops_RHCSR;
	ALLOC (_hoops_RHCSR, _hoops_PSISR);

	/*_hoops_SIGP _hoops_ASISC _hoops_PSISC _hoops_PPR _hoops_RGR*/
	for (int ii = 0; ii < 256; ii++)
		_hoops_RHCSR->_hoops_HSISR[ii] = 0.0f;

	if (_hoops_APPSC (name, state->_hoops_GPPIR, string, &_hoops_ARASC)) {

		_hoops_HCRPR			filename, _hoops_GGHGA, _hoops_RGHGA;
		void alter *	_hoops_CRIPH;
		char			_hoops_RAGH[MAX_ERRMSG];
		char			_hoops_AAGH[MAX_ERRMSG];

		HI_Copy_Chars_To_Name (string, &filename);

		_hoops_GGHGA.length = _hoops_RGHGA.length = 0;
		if (!HI_Open_File (&filename, FILE_For_Reading, &_hoops_CRIPH, false, &_hoops_GGHGA, &_hoops_RGHGA)) {
			HI_Copy_Name_To_Chars (&_hoops_GGHGA, _hoops_RAGH);
			HI_Copy_Name_To_Chars (&_hoops_RGHGA, _hoops_AAGH);
			HE_ERROR2 (HEC_POSTSCRIPT_DRIVER, HES_FILE_OPEN, _hoops_RAGH, _hoops_AAGH);
			_hoops_RGAIR (_hoops_GGHGA);
			_hoops_RGAIR (_hoops_RGHGA);
		}
		else {
			char				buf[512];
			char alter *		_hoops_ASAPR = &buf[512];
			char				line[256];
			char alter *		_hoops_CAPSC;
			int					_hoops_RCISC;

			_hoops_SPISC = true;

			/* 93 _hoops_HRGR _hoops_HCGR _hoops_IGIR 1.0 */
			_hoops_CCCRP = height * (float)(1.0 / 93.0);
			if (_hoops_CCCRP < 1.0f)
				_hoops_CCCRP = 1.0f + 0.05f * (1.0f - _hoops_CCCRP);
			else
				_hoops_CCCRP = 1.0f;

			do {
				_hoops_SRPSC (_hoops_CRIPH, buf, buf + _hoops_GGAPR (buf), &_hoops_ASAPR, line);
				_hoops_CAPSC = line;
				_hoops_RCISC = _hoops_HAPSC (_hoops_PIASC, &_hoops_CAPSC);

				switch (_hoops_RCISC) {
				  case _hoops_AHASC:
					do {
						_hoops_SRPSC (_hoops_CRIPH, buf, buf + _hoops_GGAPR (buf),
								 &_hoops_ASAPR, line);
						_hoops_CAPSC = line;
						_hoops_RCISC = _hoops_HAPSC (_hoops_PIASC, &_hoops_CAPSC);

						if (_hoops_RCISC != _hoops_PHASC) {
							int _hoops_AGCPC;
							int _hoops_HSISC;
							char alter *_hoops_ISISC;

							/*
							 * _hoops_IPCP _hoops_RPR _hoops_AIAII, _hoops_IHRPR, _hoops_RHAP _hoops_HAR _hoops_SSCC
							 * _hoops_RPGAH _hoops_ARPP _hoops_RH _hoops_IGAA, _hoops_CSISC, _hoops_HIS _hoops_SR
							 * _hoops_IHIS _hoops_RH _hoops_CRS _hoops_IIGR _hoops_RH _hoops_GSGR _hoops_ISSC _hoops_IS _hoops_RH
							 * _hoops_AIGPH.
							 */

							_hoops_ISISC = _hoops_CAPSC;

							_hoops_RGGA (*_hoops_CAPSC == 'C') _hoops_CAPSC++;
							_hoops_CAPSC++;
							HI_Scan_Integer (dc->_hoops_RIGC, (char const * alter *)&_hoops_CAPSC, null, &_hoops_AGCPC);

							_hoops_CAPSC = _hoops_ISISC;

							_hoops_RGGA (*_hoops_CAPSC == 'W') _hoops_CAPSC++;
							_hoops_RGGA (*_hoops_CAPSC == 'X') _hoops_CAPSC++;
							_hoops_CAPSC++;
							HI_Scan_Integer (dc->_hoops_RIGC, (char const * alter *)&_hoops_CAPSC, null, &_hoops_HSISC);

							/*
							 * _hoops_AGAH _hoops_GSSS _hoops_GHAGI _hoops_HHHPP 1 _hoops_IPISR  _hoops_PPR _hoops_RGAR
							 * _hoops_PHI 32 - 128 _hoops_HRASC _hoops_HHRCP _hoops_SSISC
							 * _hoops_CHR _hoops_RH _hoops_PSHR _hoops_PSHR _hoops_GAR _hoops_GHAGI _hoops_HHHPP 1 _hoops_HIS _hoops_CGPR _hoops_SR
							 * _hoops_CISA _hoops_GGR _hoops_RH _hoops_IGAA _hoops_GASR _hoops_SGS _hoops_HRGR _hoops_ARRS 128
							 * _hoops_SR _hoops_RRP _hoops_IS _hoops_GGCSC _hoops_RH _hoops_IGAA.
							 */

							/* _hoops_ASAI _hoops_RGCSC _hoops_AGCSC
							_hoops_RPP ((_hoops_PGCSC == _hoops_HGCSC) && (_hoops_IGCSC > 128))
								_hoops_CGCSC = -_hoops_CGCSC;
								*/

							/*
							 * _hoops_PS _hoops_CHR _hoops_RGAR _hoops_GPIHR _hoops_GGR _hoops_RH _hoops_HPS _hoops_HII
							 * 32 _hoops_IS 255
							 */
							if (_hoops_AGCPC >= 32 && _hoops_AGCPC <= 255) {
								_hoops_RHCSR->_hoops_HSISR[_hoops_AGCPC] = (_hoops_SIRSP) (_hoops_HSISC * height * 0.001f);
							}
						}
					} _hoops_RGGA (_hoops_RCISC == _hoops_PHASC);
					break;

				  case _hoops_IHASC:
					do {
						_hoops_SRPSC (_hoops_CRIPH, buf, buf + _hoops_GGAPR (buf),
								 &_hoops_ASAPR, line);
						_hoops_CAPSC = line;
						_hoops_RCISC = _hoops_HAPSC (_hoops_PIASC, &_hoops_CAPSC);
					} _hoops_RGGA (_hoops_RCISC == _hoops_CHASC);
					break;
				}
			} _hoops_RGGA (_hoops_RCISC == _hoops_AIASC);

			if (!HI_Close_File (_hoops_CRIPH,  &_hoops_GGHGA, &_hoops_RGHGA)) {
				HI_Copy_Name_To_Chars (&_hoops_GGHGA, _hoops_RAGH);
				HI_Copy_Name_To_Chars (&_hoops_RGHGA, _hoops_AAGH);
				HE_ERROR2 (HEC_POSTSCRIPT_DRIVER, HES_FILE_CLOSE, _hoops_RAGH, _hoops_AAGH);
				_hoops_RGAIR (_hoops_GGHGA);
				_hoops_RGAIR (_hoops_RGHGA);
			}

			if (state->_hoops_ASASC) {
				fprintf (fp, "/HF%d {/%s findfont %d scalefont setfont} bind def\n",
						 state->_hoops_SCASC, name, height);
				_hoops_PGPSC (state, 0L);
			}
		}

		_hoops_RGAIR (filename);
	}

	if (!_hoops_SPISC) { /* _hoops_CSH _hoops_HRCSR _hoops_CHHR _hoops_PAR _hoops_PSP _hoops_PAPSC _hoops_GSIHH _hoops_IIH */
		unsigned char const		*table;

		switch (*name) {
			case 'C':
				table = _hoops_RPCSR;
				break;

			case 'S':
				table = _hoops_HPCSR;
				/* _hoops_HCR _hoops_CHR _hoops_GRH */
				/*
				_hoops_APPS = -_hoops_APPS;
				*/
				break;

			case 'H':
				if (name[9] == '-' && name[10] == 'B')
					table = _hoops_ARICC;
				else
					table = _hoops_RRICC;
				break;

			case 'T':
				switch (name[6]) {
					case 'R':	table = _hoops_PPCSR;			break;
					case 'I':	table = _hoops_PRICC;	break;
					default:	if (name[10] == '\0')
										table = _hoops_HRICC;
									else
										table = _hoops_IRICC;
									break;
				}
				break;

			default: {
				table = _hoops_RPCSR;
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								   "unexpected character table");
			}
		}

		/* _hoops_IGAA _hoops_CIAAI _hoops_HRGR _hoops_ASISR _hoops_HII 1 _hoops_HPGR _hoops_IGIR 1 _hoops_IS
		 * 1.2 _hoops_HPGR _hoops_IGIR .2 */

		/* 93 _hoops_HRGR _hoops_HCGR _hoops_IGIR 1.0 */
		_hoops_CCCRP = height * (float)(1.0 / 93.0);
		if (_hoops_CCCRP < 1.0f)
			_hoops_CCCRP = 1.0f + 0.05f * (1.0f - _hoops_CCCRP);
		else
			_hoops_CCCRP = 1.0f;

		for (int ii=32; ii<256; ii++)
			_hoops_RHCSR->_hoops_HSISR[ii] = (float) (height * _hoops_IRGCR (table[ii - 32]) *
									   (float)(1.042 / 255.0) * _hoops_CCCRP);

		if (state->_hoops_ASASC) {
			if (*name != 'S') {
				fprintf (fp, "/HF%d {/R%s findfont %d scalefont setfont} bind def\n",
						 state->_hoops_SCASC, name, height);
				_hoops_PGPSC (state, 0L);
			}
			else {
				fprintf (fp, "/HF%d {/%s findfont %d scalefont setfont} bind def\n",
						 state->_hoops_SCASC, name, height);
				_hoops_PGPSC (state, 0L);
			}
		}
	} /* _hoops_CSH _hoops_HRCSR _hoops_CHHR */

	_hoops_RHCSR->_hoops_CSISR = state->_hoops_SCASC++;

	return (void *)_hoops_RHCSR;
}



local void unload_font (
	Display_Context const	*dc,
	Font_Instance alter	*instance) {
	_hoops_HIASC alter	*state = _hoops_ARPSC (dc);
	FILE alter		*fp = state->fp;
	_hoops_PSISR		*_hoops_RHCSR = (_hoops_PSISR*) instance->_hoops_GAASR;

	if (!state->_hoops_PRGGH && state->_hoops_ASASC &&
			_hoops_RHCSR->_hoops_CSISR > state->_hoops_GSASC)
		_hoops_IGPSC ("/HF%d () def\n", _hoops_RHCSR->_hoops_CSISR);

	FREE (_hoops_RHCSR, _hoops_PSISR);
}


local void draw_dc_text (
	Net_Rendition const &		nr,
	DC_Point const *			where,
	int							count,
	Karacter const *			kstring) {
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	FILE alter *				fp = state->fp;
	int							value;
	int							len;
	_hoops_PSISR *				_hoops_RHCSR = (_hoops_PSISR *) _hoops_HRCIR->font->_hoops_GAASR;

	/* _hoops_ISPR _hoops_CIHH */
	if (nr->transform_rendition->_hoops_CPA != state->_hoops_RPICC)
		_hoops_RIHSC (nr);

	if (state->_hoops_PRGGH) return;

	if (_hoops_HRCIR->_hoops_CPA != state->_hoops_ACASC) {

		if (_hoops_RHCSR->_hoops_CSISR <= state->_hoops_GSASC) {
			/* _hoops_RH _hoops_CRSRR _hoops_HRGR _hoops_HII _hoops_RH _hoops_PGHC _hoops_HSHIA; _hoops_HHSA _hoops_IRS _hoops_CCAH _hoops_CACPC() */
			/* "_hoops_SGCSC" _hoops_HRGR _hoops_SACAR _hoops_IH _hoops_RH _hoops_GRCSC _hoops_RHPP. */
			HD_Force_Font_Load (nr);

			if (state->_hoops_PRGGH) return;
		}

		_hoops_CSASR (state, &_hoops_HRCIR->color);

		if (state->_hoops_PRGGH) return;

		state->_hoops_ACASC = _hoops_HRCIR->_hoops_CPA;

		_hoops_IGPSC ("HF%d ", _hoops_RHCSR->_hoops_CSISR);
	}

	if (_hoops_HRCIR->rotation != 0.0f || _hoops_HRCIR->width_scale != 1.0f || _hoops_HRCIR->_hoops_IPGRP != 0.0f) {
		fprintf (fp, "GS %.2f %.2f TR ", where->x, where->y);	_hoops_AGPSC (state);
		if (_hoops_HRCIR->rotation != 0.0f)
			_hoops_IGPSC ("%g rotate ", _hoops_HRCIR->rotation);

		if (_hoops_HRCIR->_hoops_IPGRP != 0.0f) {
			float			_hoops_GGHCR, _hoops_AGHCR;

			_hoops_RICH (_hoops_HRCIR->_hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR);
			fprintf (fp, "[%g 0 %g 1 0 0] concat ",
					 _hoops_HRCIR->width_scale, _hoops_GGHCR / _hoops_AGHCR);			_hoops_AGPSC (state);
		}
		else if (_hoops_HRCIR->width_scale != 1.0f) {
			_hoops_IGPSC ("%g 1 SC ", _hoops_HRCIR->width_scale);
		}
		_hoops_ACIAI ("0 0 MT\n");
	}
	else {
		fprintf (fp, "%.2f %.2f MT\n", where->x, where->y);		_hoops_AGPSC (state);
	}

	/* _hoops_IIPR _hoops_GSGR _hoops_GAR _hoops_CPHP _hoops_RH _hoops_GRGAI _hoops_GRS _hoops_IRAA */
	_hoops_ACIAI ("(");
	len = 1;
	do {
		value = (int) *kstring++ & 0xFF;
		if (value < 32	||	value > 126) {
			_hoops_IGPSC ("\\%03o", value);
			len += 4;
		}
		else switch ((char) value) {
			case '(':
			case ')':
			case '\\': {
				_hoops_IGPSC ("\\%c", value);
				len += 2;
			}	break;

			default: {
				_hoops_IGPSC ("%c", value);
				len++;
			}	break;
		}
		if (len > 70) {
			_hoops_ACIAI ("\\\n");
			len = 0;
		}
	} _hoops_RGGA (--count == 0);

	if (_hoops_HRCIR->rotation != 0.0f || _hoops_HRCIR->width_scale != 1.0f)
		_hoops_ACIAI (") show GR\n");
	else
		_hoops_ACIAI (") show\n");
}


local void draw_dc_polydot (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
	Display_Context const *		dc = nr->_hoops_SRA;
	Line_Rendition const &		_hoops_HC = nr->_hoops_AHP;
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	FILE alter *				fp = state->fp;

	if (BIT (dc->options._hoops_IRARR, _hoops_RGASC))
		_hoops_ACIAI ("%% dot\n");

	if (nr->transform_rendition->_hoops_CPA != state->_hoops_RPICC)
		_hoops_RIHSC (nr);
	if (_hoops_HC->_hoops_CPA != state->_hoops_ACASC)
		_hoops_AIHSC (nr, nr->_hoops_AHP);

	if (state->_hoops_PRGGH) return;

	if (BIT (dc->options._hoops_IRARR, _hoops_AGASC))
		_hoops_ACIAI ("S ");

	while (count-- > 0) {
		fprintf (fp, "NP %.2f %.2f 0.5 0.5 EL FL\n", points->x, points->y);
		_hoops_AGPSC (state);

		points++;
	}

	if (BIT (dc->options._hoops_IRARR, _hoops_AGASC))
		_hoops_ACIAI ("R\n");
}




/* _hoops_IPSCP _hoops_IH _hoops_PHPSC/_hoops_ASHCI _hoops_GARAI _hoops_PSPSI _hoops_CSCR */

local void _hoops_RRCSC (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							row_bytes,
	RGBAS32 const *				_hoops_GAAC) {
	Display_Context const *		dc = nr->_hoops_SRA;
	RGBAS32 const *				_hoops_SCGCR;
	RGBAS32 alter *				pp;
	RGBAS32 alter *				pe;
	Image alter *				image = (Image alter *)dc->data;
	int							x, y;
	int							width = (int)end->x - (int)start->x + 1;
	Int_Rectangle const *		_hoops_GPHH = &nr->transform_rendition->_hoops_AGAA;

	if (row_bytes == 0)
		row_bytes = width * sizeof (RGBAS32);

	y = (int)start->y;

	_hoops_RGGA (y < (int)end->y || y < _hoops_GPHH->bottom) {
		if (y <= _hoops_GPHH->top) {
			_hoops_SCGCR = _hoops_GAAC;
			pp = (RGBAS32 alter *)image->_hoops_RCPIR[y] + (int)start->x;
			pe = pp + width;
			x = (int)start->x;

			if (x < _hoops_GPHH->left) {
				int		delta = _hoops_GPHH->left - x;

				pp += delta;
				_hoops_SCGCR += delta;
				x += delta;
			}

			_hoops_RGGA (pp >= pe || x > _hoops_GPHH->right) {
				*pp = *_hoops_SCGCR;

				++pp;
				++_hoops_SCGCR;
				++x;
			}
		}
		_hoops_GAAC = (RGBAS32 const *)((unsigned char const *)_hoops_GAAC + row_bytes);
		--y;
	}
}


local POINTER_SIZED_INT _hoops_ARCSC (
	Display_Context const	*dc) {
	Image alter				*image = (Image alter *)dc->data;

	return (POINTER_SIZED_INT)image->key;
}

local bool _hoops_PRCSC (
	Display_Context alter	*dc) {

	HD_Get_Bit_Patterns_8 (dc, false);

	return true;
}

local void _hoops_HRCSC (
	Display_Context alter	*dc) {

	dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;
	dc->_hoops_PGCC._hoops_PCHSR = 256;
	dc->_hoops_PGCC._hoops_AAPSR = 1L << 24;

	dc->_hoops_PGCC._hoops_ARISR.x = 0;
	dc->_hoops_PGCC._hoops_ARISR.y = 0;

	/* _hoops_SPCS _hoops_HSH _hoops_AGHPA _hoops_SR _hoops_ACPA _hoops_GIH */
	dc->_hoops_PGCC._hoops_PRPSR.x = 256;
	dc->_hoops_PGCC._hoops_PRPSR.y = 200;
	dc->_hoops_PGCC.size.x = 10.0f * 2.54f;
	dc->_hoops_PGCC.size.y = 8.0f * 2.54f;

	dc->_hoops_PGCC._hoops_CHHSR = _hoops_SHHSR;
	dc->_hoops_PGCC.flags |= _hoops_CAPGH;
	dc->_hoops_PGCC.flags &= ~_hoops_RSHSR;
	dc->_hoops_PGCC.flags &= ~_hoops_PSHSR;
	dc->_hoops_PGCC.flags &= ~_hoops_HSHSR;
	dc->_hoops_PGCC._hoops_PIPGH = true;

	dc->_hoops_PGCC.driver_type = "Postscript Internal Image";
	dc->_hoops_PGCC._hoops_SCHSR = "$Revision: 1.314 $";
	dc->_hoops_PGCC._hoops_ICHSR = "HOOPS PS preview image";

}

local void _hoops_IRCSC (
	Display_Context alter	*dc) {

	UNREFERENCED(dc);

	/* _hoops_RSPH _hoops_PRCA _hoops_CRCSC _hoops_CCA _hoops_RGR
	_hoops_AARSP _hoops_RAPC				*_hoops_CSCR = (_hoops_AARSP _hoops_RAPC *)_hoops_CSPH->_hoops_PIH;

	_hoops_ICPCA (_hoops_CSCR);
	*/
}

local void _hoops_SRCSC (
	_hoops_APARR alter &		_hoops_RRCI) {

	_hoops_RRCI->start_device			= _hoops_PRCSC;
	_hoops_RRCI->get_physical_info		= _hoops_HRCSC;
	_hoops_RRCI->get_outer_window		= _hoops_ARCSC;
	_hoops_RRCI->stop_device				= _hoops_IRCSC;

	_hoops_RRCI->draw_dc_rectangle		= HD_Span_DC_Rectangle;

	_hoops_RRCI->draw_dc_rgb32_rasters	= _hoops_RRCSC;
}

local bool _hoops_GACSC (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (request_info);
	return HD_Connect_Standard_Driver (_hoops_RIGC, _hoops_GHRI, request, _hoops_SRCSC);
}

local POINTER_SIZED_INT _hoops_RACSC (
	Display_Context const	*dc) {

	UNREFERENCED(dc);
	return 1;
}

local bool _hoops_GGASC (
	Display_Context alter *		dc,
	Activity					_hoops_SCISP) {
	_hoops_HIASC alter *				state = _hoops_ARPSC (dc);
	Display_Context alter *		_hoops_AACSC;
	int							width, height;
	Activity					_hoops_PACSC = _hoops_GSCCA;

	if (state->_hoops_HSASC == null) {

		ZALLOC (state->_hoops_HSASC, _hoops_GGAGR);
		state->_hoops_HSASC->action =
			state->_hoops_HSASC->connected_action = _hoops_GACSC;
		state->_hoops_HSASC->type = HK_DRIVER;
		state->_hoops_HSASC->owner = dc->_hoops_GHRI->owner;
		state->_hoops_HSASC->backlink = &state->_hoops_HSASC->next;

		HI_Init_Driver (dc->_hoops_RIGC, state->_hoops_HSASC, true);

		/* _hoops_ASIGA "_hoops_SRSIR" _hoops_RGR _hoops_GRH _hoops_RHPP */
		//_hoops_PCSHA->_hoops_RRRPR->_hoops_AIHGP |= _hoops_HACSC;

		*state->_hoops_HSASC->_hoops_RAIAP = state->_hoops_HSASC->_hoops_CISHA;
		state->_hoops_HSASC->_hoops_RAIAP = &state->_hoops_HSASC->_hoops_CISHA;

		HD_Standard_Driver (dc->_hoops_RIGC, state->_hoops_HSASC, _hoops_AAGSC, null);
	}
	_hoops_AACSC = (Display_Context alter *)state->_hoops_HSASC->_hoops_PPRPR;

	/* _hoops_ICAH _hoops_IS _hoops_PICII/_hoops_PCCS _hoops_PCCP _hoops_IRPR _hoops_CSCR */
	if (dc->_hoops_SHCIP == null) {
		/* _hoops_RRP _hoops_IS _hoops_HGCR _hoops_HHH _hoops_IIGR _hoops_GSSR _hoops_PAAP _hoops_CPHR _hoops_IS _hoops_CGIC _hoops_IGIR */
		dc->_hoops_ACPGR->get_outer_window = _hoops_RACSC;
		HD_Minimum_Update (dc);

		/* _hoops_IRHH _hoops_RCRR _hoops_SGS _hoops_HPHR _hoops_PAAP _hoops_RHAP _hoops_RGR _hoops_PRRP */
		dc->flags &= ~_hoops_SAISR;
		dc->_hoops_ACPGR->get_outer_window = get_outer_window;
	}

	/* _hoops_IRHH _hoops_PCCP _hoops_CSCR _hoops_IIGR _hoops_AISRA _hoops_RH _hoops_PSHR _hoops_RIRPA, _hoops_CCA _hoops_IRS _hoops_AHPA _hoops_SPIS _hoops_IIGR 256 */
	width  = (int)(dc->current.extent.right - dc->current.extent.left + 1);
	height = (int)(dc->current.extent.top - dc->current.extent.bottom + 1);
	if (width > height) {
		height = 256 * height / width;
		height = (height + 3) & ~3;
		width = 256;
	}
	else {
		width = 256 * width / height;
		width = (width + 3) & ~3;
		height = 256;
	}

	if (state->_hoops_ISASC == null ||
		state->_hoops_ISASC->width != width ||
		state->_hoops_ISASC->height != height) {
		if (state->_hoops_ISASC != null)
			_hoops_HPRH (state->_hoops_ISASC);

		HI_Create_Image (&state->_hoops_ISASC,
						 null,
						 width, height,
						 _hoops_CSGSP, 0,
						 _hoops_HISCP, null);
		HI_Validate_Inverted_Rasters (state->_hoops_ISASC);
	}

	_hoops_AACSC->data = state->_hoops_ISASC;

	/* _hoops_GGCH _hoops_RH _hoops_CIPH _hoops_SGS _hoops_RSAS'_hoops_RA _hoops_HHPA _hoops_RHSP _hoops_PSPSI _hoops_IACSC */
	_hoops_AACSC->_hoops_PGCC._hoops_PRPSR.x = width;
	_hoops_AACSC->_hoops_PGCC._hoops_PRPSR.y = height;
	if (dc->options._hoops_ARPSR) {
		_hoops_AACSC->_hoops_PGCC.size.x = dc->_hoops_PGCC.size.y;
		_hoops_AACSC->_hoops_PGCC.size.y = dc->_hoops_PGCC.size.x;
	}
	else {
		_hoops_AACSC->_hoops_PGCC.size.x = dc->_hoops_PGCC.size.x;
		_hoops_AACSC->_hoops_PGCC.size.y = dc->_hoops_PGCC.size.y;
	}
	_hoops_AACSC->_hoops_PGCC.extent.left = 0.0f;
	_hoops_AACSC->_hoops_PGCC.extent.bottom = 0.0f;
	_hoops_AACSC->_hoops_PGCC.extent.right = width - 0.001f;
	_hoops_AACSC->_hoops_PGCC.extent.top = height - 0.001f;

	/* _hoops_PSPSI _hoops_IGIR _hoops_HRGR _hoops_HIAGR _hoops_IIGR "_hoops_HSHIA" _hoops_ISPH */
	_hoops_AACSC->options._hoops_HCPRP.left = -1.0f;
	_hoops_AACSC->options._hoops_HCPRP.right = 1.0f;
	_hoops_AACSC->options._hoops_HCPRP.bottom = -1.0f;
	_hoops_AACSC->options._hoops_HCPRP.top = 1.0f;

	/* _hoops_CAHP _hoops_RH _hoops_PSPSI */
	state->_hoops_HSASC->_hoops_CGPIR |= _hoops_CSRPH;
	HD_Standard_Driver (dc->_hoops_RIGC, state->_hoops_HSASC, _hoops_HAGSC, &_hoops_PACSC);
	state->_hoops_HSASC->_hoops_CGPIR &= ~_hoops_CSRPH;

	/* _hoops_HA _hoops_RH _hoops_HPHR _hoops_PAAP */
	return HD_Standard_Update (dc, _hoops_SCISP);
}

/************************************/




local void _hoops_RSCSR (
	_hoops_APARR alter &		_hoops_RRCI) {

	_hoops_RRCI->start_device					= start_device;
	_hoops_RRCI->stop_device						= stop_device;
	_hoops_RRCI->get_physical_info				= get_physical_info;
	_hoops_RRCI->get_current_info				= get_current_info;
	_hoops_RRCI->draw_dc_polydot					= draw_dc_polydot;
	_hoops_RRCI->draw_dc_polyline				= draw_dc_polyline;
	_hoops_RRCI->draw_dc_polytriangle			= draw_dc_polytriangle;
	_hoops_RRCI->draw_dc_rectangle				= draw_dc_rectangle;
	_hoops_RRCI->draw_dc_face					= draw_dc_face;
	_hoops_RRCI->init_picture					= init_picture;
	_hoops_RRCI->finish_picture					= finish_picture;
	_hoops_RRCI->get_outer_window				= get_outer_window;
	_hoops_RRCI->free_outer_window				= free_outer_window;
	_hoops_RRCI->draw_dc_rgb32_rasters			= draw_dc_rgb32_rasters;
	_hoops_RRCI->draw_dc_colorized_polytriangle	= draw_dc_colorized_polytriangle;
	_hoops_RRCI->draw_dc_gouraud_polytriangle	= draw_dc_gouraud_polytriangle;

	_hoops_RRCI->find_all_fonts					= find_all_fonts;
	_hoops_RRCI->load_font						= load_font;
	_hoops_RRCI->unload_font						= unload_font;
	_hoops_RRCI->draw_dc_text					= draw_dc_text;
	_hoops_RRCI->measure_char					= measure_char;

	_hoops_RRCI->draw_window = draw_window;

	_hoops_RRCI->draw_3d_nurbs_curve				= draw_3d_nurbs_curve;
	_hoops_RRCI->draw_3d_elliptical_arc			= draw_3d_elliptical_arc;
	_hoops_RRCI->draw_3d_ellipse					= draw_3d_ellipse;
	_hoops_RRCI->_hoops_CCISR			= _hoops_CCISR;
	_hoops_RRCI->draw_dc_ellipse					= draw_dc_ellipse;
	_hoops_RRCI->_hoops_SCISR			= _hoops_SCISR;
}


extern "C" bool HC_CDECL HD_PostScript_Driver (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (request_info);
	return HD_Connect_Standard_Driver (_hoops_RIGC, _hoops_GHRI, request, _hoops_RSCSR);
}


_hoops_HSCSR (_hoops_RSCSR)

#endif /* _hoops_CACSC */


/*
 * Copyright (c) by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.  Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.152 2011-01-05 18:48:10 reuben Exp $
 */

#include "hoops.h"
#include "hd_proto.h"

#ifndef CGM3_DRIVER

/* _hoops_APICR _hoops_PPICR */
extern "C" bool HC_CDECL
HD_CGM3_Driver(
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_GGAGR alter *			_hoops_GHRI, 
	int						request, 
	void *					request_info)
{
	UNREFERENCED(request_info);
	return HD_No_Driver(_hoops_RIGC, _hoops_GHRI, request, "cgm3");
}


#else				/* */

#include "database.h"
#include "driver.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "patterns.h"
#include "please.h"
#include "searchh.h"
#include "hversion.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _hoops_CGSPR
#	define _hoops_HPICR(a)				printf(a)
#else				/* */
#	define _hoops_HPICR(a)				(void)(a)
#endif				/* _hoops_SHRS */

#define _hoops_IPICR		2
#define _hoops_CPICR		4
#define _hoops_SPICR			8
#define _hoops_GHICR				16
#define _hoops_RHICR				32
#define _hoops_AHICR				64
#define _hoops_PHICR				128
#define _hoops_HHICR				256

#define MAX_COLORS		256
#define _hoops_IHICR		256

#define _hoops_CHICR					3
#define _hoops_SHICR				4
#define _hoops_GIICR						0

#define _hoops_RIICR	0
#define _hoops_AIICR		1
#define _hoops_PIICR			3

#define _hoops_RAAHR 0.0001

#define _hoops_HIICR(x, y) (((x)-(y)) * ((x)-(y)) < _hoops_RAAHR)

enum {
	_hoops_IIICR = 1,
	_hoops_CIICR = 2,
	_hoops_SIICR = 3
};

/* _hoops_GCICR _hoops_RCICR _hoops_ACICR _hoops_PCICR */
#define _hoops_HCICR						0
#define		_hoops_ICICR									 0
#define		_hoops_CCICR							 1
#define		_hoops_SCICR							 2
#define		_hoops_GSICR							 3
#define		_hoops_RSICR						 4
#define		_hoops_ASICR								 5
#define		_hoops_PSICR							 6
#define		_hoops_HSICR								 7
#define		_hoops_ISICR							 8
#define		_hoops_CSICR								 9
#define		_hoops_SSICR					13
#define		_hoops_GGCCR					14
#define		_hoops_RGCCR						15
#define		_hoops_AGCCR						16
#define		_hoops_PGCCR				17
#define		_hoops_HGCCR					18
#define		_hoops_IGCCR						19
#define		_hoops_CGCCR							20
#define		_hoops_SGCCR				21
#define		_hoops_GRCCR		22
#define		_hoops_RRCCR				23
#define _hoops_ARCCR						1
#define		_hoops_PRCCR						 1
#define		_hoops_HRCCR					 2
#define		_hoops_IRCCR								 3
#define		_hoops_CRCCR						 4
#define		_hoops_SRCCR							 5
#define		_hoops_GACCR							 6
#define		_hoops_RACCR							 7
#define		_hoops_AACCR					 8
#define		_hoops_PACCR						 9
#define		_hoops_HACCR						10
#define		_hoops_IACCR					11
#define		_hoops_CACCR			12
#define		_hoops_SACCR								13
#define		_hoops_GPCCR						14
#define		_hoops_RPCCR				15
#define		_hoops_APCCR							16
#define		_hoops_PPCCR						17
#define		_hoops_HPCCR					18
#define		_hoops_IPCCR								19
#define		_hoops_CPCCR						20
#define		_hoops_SPCCR							21
#define		GLYPH_MAPPING							22
#define		_hoops_GHCCR						23
#define		_hoops_RHCCR						24
#define _hoops_AHCCR							2
#define		_hoops_PHCCR							 1
#define		_hoops_HHCCR					 2
#define		_hoops_IHCCR			 3
#define		_hoops_CHCCR			 4
#define		_hoops_SHCCR			 5
#define		_hoops_GICCR								 6
#define		BACKGROUND_COLOR						 7
#define		_hoops_RICCR							 8
#define		_hoops_AICCR		 9
#define		_hoops_PICCR					10
#define		_hoops_HICCR						11
#define		_hoops_IICCR					12
#define		_hoops_CICCR						13
#define		_hoops_SICCR						14
#define		_hoops_GCCCR						15
#define		_hoops_RCCCR		16
#define		_hoops_ACCCR			17
#define		_hoops_PCCCR					18
#define		_hoops_HCCCR			19
#define		_hoops_ICCCR			20
#define _hoops_CCCCR							3
#define		_hoops_SCCCR					 1
#define		_hoops_GSCCR						 2
#define		AUXILIARY_COLOR							 3
#define		_hoops_RSCCR							 4
#define		_hoops_ASCCR							 5
#define		_hoops_PSCCR							 6
#define		_hoops_HSCCR						 7
#define		_hoops_ISCCR					 8
#define		_hoops_CSCCR						 9
#define		_hoops_SSCCR								10
#define		_hoops_GGSCR					11
#define		_hoops_RGSCR				12
#define		_hoops_AGSCR				17
#define		_hoops_PGSCR				18
#define		_hoops_HGSCR								19
#define		_hoops_IGSCR					20
#define _hoops_CGSCR						4
#define		_hoops_SGSCR								 1
#define		_hoops_GRSCR						 2
#define		_hoops_RRSCR								 3
#define		_hoops_ARSCR								 4
#define		_hoops_PRSCR							 5
#define		_hoops_HRSCR								 6
#define		_hoops_IRSCR									 7
#define		_hoops_CRSCR								 8
#define		_hoops_SRSCR								 9
#define		_hoops_GASCR			10
#define		_hoops_RASCR								11
#define		_hoops_AASCR									12
#define		_hoops_PASCR					13
#define		_hoops_HASCR				14
#define		_hoops_IASCR						15
#define		_hoops_CASCR				16
#define		_hoops_SASCR									17
#define		_hoops_GPSCR							18
#define		_hoops_RPSCR					19
#define		_hoops_APSCR			20
#define		_hoops_PPSCR							21
#define		_hoops_HPSCR							22
#define		_hoops_IPSCR							23
#define		_hoops_CPSCR					24
#define		_hoops_SPSCR			25
#define		_hoops_GHSCR								26
#define		_hoops_RHSCR								27
#define		_hoops_AHSCR							28
#define		_hoops_PHSCR									29
#define _hoops_HHSCR						5
#define		_hoops_IHSCR						 1
#define		_hoops_CHSCR								 2
#define		_hoops_SHSCR								 3
#define		LINE_COLOR								 4
#define		_hoops_GISCR						 5
#define		_hoops_RISCR								 6
#define		_hoops_AISCR								 7
#define		MARKER_COLOR							 8
#define		_hoops_PISCR						 9
#define		_hoops_HISCR							10
#define		_hoops_IISCR							11
#define		_hoops_CISCR				12
#define		_hoops_SISCR						13
#define		TEXT_COLOR								14
#define		_hoops_GCSCR						15
#define		_hoops_RCSCR					16
#define		_hoops_ACSCR								17
#define		_hoops_PCSCR							18
#define		_hoops_HCSCR						19
#define		_hoops_ICSCR			20
#define		_hoops_CCSCR						21
#define		_hoops_SCSCR							22
#define		FILL_COLOR								23
#define		_hoops_GSSCR								24
#define		_hoops_RSSCR							25
#define		_hoops_ASSCR						26
#define		_hoops_PSSCR								27
#define		_hoops_HSSCR								28
#define		EDGE_COLOR								29
#define		_hoops_ISSCR							30
#define		_hoops_CSSCR					31
#define		_hoops_SSSCR							32
#define		_hoops_GGGSR							33
#define		_hoops_RGGSR								34
#define		_hoops_AGGSR						35
#define		_hoops_PGGSR							36
#define		_hoops_HGGSR								37
#define		_hoops_IGGSR								38
#define		_hoops_CGGSR					39
#define		_hoops_SGGSR				40
#define		_hoops_GRGSR							41
#define		_hoops_RRGSR					42
#define		_hoops_ARGSR					43
#define		_hoops_PRGSR								44
#define		_hoops_HRGSR								45
#define		_hoops_IRGSR					46
#define		_hoops_CRGSR				47
#define		_hoops_SRGSR					48
#define		SYMBOL_COLOR							49
#define		_hoops_GAGSR								50
#define		_hoops_RAGSR						51
#define _hoops_AAGSR							6
#define		_hoops_PAGSR									 1
#define _hoops_HAGSR						7
#define		_hoops_IAGSR									 1
#define		_hoops_CAGSR						 2
#define _hoops_SAGSR							8
#define		_hoops_GPGSR							 1
#define		_hoops_RPGSR						 2
#define		_hoops_APGSR						 3
#define		_hoops_PPGSR					 4
#define		_hoops_HPGSR					 5
#define		_hoops_IPGSR				 6
#define		_hoops_CPGSR					 7
#define _hoops_SPGSR						9
#define		_hoops_GHGSR					 1

/* _hoops_HSCAR _hoops_SGS _hoops_RHGSR _hoops_HCPH _hoops_IS _hoops_SRAC _hoops_SICAR */
/* _hoops_ASC _hoops_CHR _hoops_PAPR _hoops_GAR _hoops_APPC _hoops_GSPR _hoops_HIS _hoops_SR'_hoops_GCPP _hoops_HGCR _hoops_AHGSR _hoops_CGPR _hoops_PHGSR
   _hoops_RH _hoops_ARRS _hoops_CPPC (_hoops_SCSH _hoops_RCIC _hoops_HA) _hoops_IS _hoops_RH _hoops_HHGSR* _hoops_PSCH.  _hoops_HGI _hoops_HRGR _hoops_IS
   _hoops_CRHR _hoops_IHGSR _hoops_HII _hoops_RCPH _hoops_CHGSR(_hoops_PIAP, _hoops_SHGSR, &_hoops_HAIR)
   _hoops_CAS _hoops_SR _hoops_GIGSR _hoops_AASA _hoops_CHGSR(_hoops_PIAP, _hoops_RIGSR, &_hoops_HAIR). */
static unsigned short const _hoops_AIGSR = 0;
static unsigned short const _hoops_PIGSR = 1;
static unsigned short const _hoops_HIGSR = 2;
static unsigned short const _hoops_IIGSR = 3;
static unsigned short const _hoops_CIGSR = 4;
static unsigned short const _hoops_SIGSR = 5;
static unsigned short const _hoops_GCGSR = 6;

static unsigned char const _hoops_RCGSR = 0;
static unsigned char const _hoops_ACGSR = 1;
static unsigned char const _hoops_PCGSR = 2;
static unsigned char const _hoops_HCGSR = 3;
static unsigned char const _hoops_ICGSR = 4;
static unsigned char const _hoops_CCGSR = 5;
static unsigned char const _hoops_SCGSR = 6;

static unsigned short const _hoops_GSGSR = 1;
static unsigned short const _hoops_RSGSR = 2;
static unsigned short const _hoops_ASGSR = 3;
static unsigned short const _hoops_PSGSR = 4;
static unsigned short const _hoops_HSGSR = 5;

/* _hoops_ISGSR _hoops_PAH _hoops_RSPC _hoops_CSGSR _hoops_PIH */
struct _hoops_SSGSR {
	unsigned char _hoops_GGRSR;
	struct {
			unsigned char r, g, b, number;
	} pen[MAX_COLORS];
};

struct _hoops_RGRSR {
	/* _hoops_RGHR _hoops_CRS */
	FILE *fp;
	int _hoops_AGRSR;
	char _hoops_PGRSR[_hoops_IHICR];
	char _hoops_HGRSR[_hoops_IHICR];
	char _hoops_IGRSR[_hoops_IHICR];

	/* _hoops_SCGR _hoops_HRP _hoops_CGRSR */
	Display_Context const *dc;
	int _hoops_SGRSR;
	int _hoops_GRRSR;
	int _hoops_RRRSR;
	int _hoops_ARRSR;
	float _hoops_RGRA;
	bool _hoops_PRRSR,
		_hoops_HRRSR, _hoops_IRRSR, _hoops_CRRSR, _hoops_SRRSR;
	_hoops_GARSR _hoops_RARSR,
		_hoops_AARSR, _hoops_PARSR, _hoops_HARSR,
		_hoops_IARSR;

	/* _hoops_IPSP _hoops_CARSR _hoops_ARCR _hoops_IIGR _hoops_PSHA */
	_hoops_SSGSR *_hoops_SARSR;
	struct {
		bool set;
		Driver_Color color;
		bool _hoops_GPRSR;
		int _hoops_RPRSR;
	} _hoops_CSIR[MAX_COLORS];
	struct {
		Driver_Color colors[_hoops_SCGSR];
		int fill_style,
			_hoops_APRSR,
			_hoops_PPRSR, _hoops_HPRSR, line_join, line_weight,
			_hoops_IPRSR, _hoops_CPRSR, _hoops_SPRSR, _hoops_GHRSR;
		unsigned short _hoops_RHRSR;
		_hoops_GARRR _hoops_AHRSR;
		Int_Rectangle _hoops_PHRSR;
		bool _hoops_HHRSR, _hoops_IHRSR;
		float _hoops_CHRSR;
	} _hoops_CSC;
	struct {
		float _hoops_SHRSR;
		float rotation;
		int _hoops_GIRSR;
		float _hoops_RIRSR;
		float _hoops_AIRSR;
		int _hoops_PIRSR;
	} text;

	/* _hoops_SISS _hoops_IGIR */
	float _hoops_HIRSR;

	/* _hoops_AH _hoops_CASPR */
	DC_Point points[3];

#ifdef _hoops_IIRSR
	int _hoops_CIRSR;

#endif				/* _hoops_SIRSR */
};

/* _hoops_CIGR _hoops_IS _hoops_GRAS _hoops_PIAP _hoops_CICRR _hoops_HII _hoops_PGI _hoops_IRS _hoops_CSPH _hoops_PAR _hoops_SCII */
#define _hoops_GCRSR(dc)		((_hoops_RGRSR alter *)(dc)->data)
#define _hoops_RCRSR(nr)		((_hoops_RGRSR alter *)(nr)->_hoops_SRA->data)


static int _hoops_ACRSR(Display_Context const *dc)
{
	if (HI_CI_Wild_Equal_Strings_To_Max (dc->_hoops_PCRSR, dc->_hoops_HCRSR, "*.ans")) {
		return _hoops_CHICR;
	}
	else if (HI_CI_Wild_Equal_Strings_To_Max (dc->_hoops_PCRSR, dc->_hoops_HCRSR, "*.txt")) {
		return _hoops_SHICR;
	}
	else {
		/* _hoops_GII _hoops_RSIRR _hoops_SGS _hoops_RHAP _hoops_HAR _hoops_PSSP _hoops_RH _hoops_ICRSR _hoops_SAGGR _hoops_CCRSR _hoops_PSHPR */
		return _hoops_CHICR;
	}
}


static int _hoops_SCRSR(_hoops_HCRPR const *name)
{
	if (HI_CI_Wild_Equal_Strings_To_Max (name->text, name->length, "ANSI binary")) {
		return _hoops_CHICR;
	}
	else if (HI_CI_Wild_Equal_Strings_To_Max (name->text, name->length, "clear text")) {
		return _hoops_SHICR;
	}
	else {
		/*
		* _hoops_GII _hoops_HCSP _hoops_PIRA _hoops_SGS _hoops_RHAP _hoops_HAR _hoops_PSSP _hoops_RH _hoops_ICRSR _hoops_SAGGR _hoops_CCRSR
		* _hoops_PSHPR
		*/
		return _hoops_GIICR;
	}
}


static int _hoops_GSRSR(Display_Context const *dc)
{
	_hoops_AAPIR const *list = dc->options._hoops_HAPIR;
	while (list) {
		int encoding = _hoops_SCRSR(&list->name);
		if (encoding != _hoops_GIICR)
			return encoding;
		list = list->next;
	}
	return _hoops_GIICR;
}


static int _hoops_RSRSR(_hoops_HCRPR const *name)
{
	if (HI_CI_Wild_Equal_Strings_To_Max (name->text, name->length, "abstract")) {
		return _hoops_RIICR;
	}
	else if (HI_CI_Wild_Equal_Strings_To_Max (name->text, name->length, "metric")) {
		return _hoops_AIICR;
	}
	else {
		/*
		* _hoops_GII _hoops_HCSP _hoops_PIRA _hoops_SGS _hoops_RHAP _hoops_HAR _hoops_PSSP _hoops_RH _hoops_ICRSR _hoops_SAGGR _hoops_CCRSR
		* _hoops_PSHPR
		*/
		return _hoops_PIICR;
	}
}


static int _hoops_ASRSR(Display_Context const *dc)
{
	_hoops_AAPIR const *list = dc->options._hoops_HAPIR;
	while (list) {
		int _hoops_PSRSR = _hoops_RSRSR(&list->name);
		if (_hoops_PSRSR != _hoops_PIICR)
			return _hoops_PSRSR;
		list = list->next;
	}
	return _hoops_AIICR;
}


static void _hoops_HSRSR(_hoops_RGRSR alter * state)
{
	_hoops_HPICR("close_CGM3_file\n");
	fclose(state->fp);
}


static void _hoops_ISRSR(_hoops_RGRSR alter * state, unsigned char data)
{
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			if (fwrite(&data, 1, 1, state->fp) < (size_t) 1) {
				_hoops_HSRSR(state);
				HE_ERROR(HEC_CGM_DRIVER, HES_WRITE_BYTE_TO_FILE_FAILED,
					"Write byte to CGM3 output file failed");
				HD_Kill_Driver(state->dc);
			}
		}	break;
		case _hoops_SHICR: {
			fputc(data, state->fp);
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Unexpected encoding on CGM3 write byte attempt");
		}	break;
	}
}


static void
_hoops_CSRSR(_hoops_RGRSR alter * state, char const *_hoops_SSRSR)
{
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			unsigned char const *byte;
			int i, count;

			byte = (unsigned char const *) _hoops_SSRSR;
			count = (int) _hoops_SSGR(_hoops_SSRSR);
			_hoops_ISRSR(state, (unsigned char) count);
			for (i = 0; i < count; i++) {
				_hoops_ISRSR(state, *byte++);
			}
			if (count % 2 == 0)
				_hoops_ISRSR(state, (unsigned char) 0);
		}	break;
		case _hoops_SHICR: {
			if (fprintf(state->fp, "%s", _hoops_SSRSR) == EOF) {
				_hoops_HSRSR(state);
				HE_ERROR(HEC_CGM_DRIVER, HES_ASCII_WRITE_TO_FILE_FAILED,
					"ASCII string write to CGM3 output file failed");
				HD_Kill_Driver(state->dc);
			}
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Unexpected encoding on write string attempt");
		}	break;
	}
}


static void
_hoops_GGASR(_hoops_RGRSR alter * state, unsigned short data)
{
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			unsigned char byte;

			byte = (unsigned char) (data >> 8);
			_hoops_ISRSR(state, byte);
			byte = (unsigned char) (data);
			_hoops_ISRSR(state, byte);
		}	break;
		case _hoops_SHICR: {
			Sprintf_D(state->_hoops_IGRSR, " %d ", (int) data);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Unexpected encoding on CGM3 write short attempt");
		}	break;
	}
}


static void _hoops_RGASR(_hoops_RGRSR alter * state, float value)
{
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			double _hoops_RCGCR, _hoops_AGASR;
			short _hoops_PGASR;

			_hoops_RCGCR = modf((double) value, &_hoops_AGASR);
			if (_hoops_RCGCR < 0.0) {	/* _hoops_HAR _hoops_GIR _hoops_CIAH _hoops_GGR _hoops_RHGS _hoops_RHPP? */
				_hoops_AGASR -= 1.0;
				_hoops_RCGCR = 1.0 + _hoops_RCGCR;
			}
			_hoops_GGASR(state, (short) _hoops_AGASR);
			_hoops_PGASR = (short) (_hoops_RCGCR * 65535.0);	/* _hoops_SAAA _hoops_HGASR _hoops_GGR _hoops_RHGS _hoops_RCICR _hoops_RHPP _hoops_ARI */
			_hoops_GGASR(state, _hoops_PGASR);
		}	break;
		case _hoops_SHICR: {
			fprintf(state->fp, " %g, ", value);
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Unexpected encoding on CGM3 write float attempt (non-ieee)");
		}	break;
	}
}


static void _hoops_IGASR(_hoops_RGRSR alter * state, float value)
{
	int _hoops_CGASR;
	float x;
	short _hoops_SGASR, _hoops_GRASR;
	long _hoops_RCGCR;
	unsigned long data;
	unsigned char byte;
	_hoops_HPICR("write_ieee_float_to_file\n");
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			if (value < 0.0)
				_hoops_SGASR = 1;
			else
				_hoops_SGASR = 0;
			x = (float) frexp((double) Abs(value), &_hoops_CGASR);

			/* _hoops_RRASR _hoops_HRGR _hoops_ARASR _hoops_CCA _hoops_IRS 1 _hoops_SHHA _hoops_GAR _hoops_PRASR */
			_hoops_GRASR = (short) (_hoops_CGASR - 1 + 127);
			_hoops_RCGCR = (long) (x * 16777216);

			/* _hoops_SRSGR: _hoops_HRASR _hoops_HRGR 1 _hoops_IGRH, _hoops_RRASR _hoops_HRGR 8, _hoops_IRASR _hoops_HRGR 23 */
			data = ((unsigned long) (_hoops_SGASR & 0x0001) << 31) |
				((unsigned long) (_hoops_GRASR & 0x007F) << 23) |
				((unsigned long) (_hoops_RCGCR & 0x007FFFFF));
			byte = (unsigned char) (data >> 24);
			_hoops_ISRSR(state, byte);
			byte = (unsigned char) (data >> 16);
			_hoops_ISRSR(state, byte);
			byte = (unsigned char) (data >> 8);
			_hoops_ISRSR(state, byte);
			byte = (unsigned char) (data);
			_hoops_ISRSR(state, byte);
		}	break;
		case _hoops_SHICR:
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Unexpected encoding on CGM3 write IEEE float attempt");
		}	break;
	}
}


static void
_hoops_CRASR(_hoops_RGRSR alter * state,
			  unsigned short _hoops_SRASR,
			  unsigned short _hoops_GAASR)
{
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			_hoops_GGASR(state, _hoops_SRASR);
			_hoops_GGASR(state, _hoops_GAASR);
		}	break;
		case _hoops_SHICR:
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Unexpected encoding on CGM3 header write attempt");
		}	break;
	}
}


static void
_hoops_RAASR(_hoops_RGRSR alter * state, DC_Point const *points,
			 int count)
{
	int i;
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			for (i = 0; i < count; i++) {
				_hoops_RGASR(state, points[i].x);
				_hoops_RGASR(state, points[i].y);
			}
		}	break;
		case _hoops_SHICR: {
			for (i = 0; i < count; i++) {
				Sprintf_FF(state->_hoops_IGRSR, "\n (%f,%f)", points[i].x, points[i].y);
				_hoops_CSRSR(state, state->_hoops_IGRSR);
			}
			_hoops_CSRSR(state, ";\n");
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Unexpected encoding on CGM3 points write attempt");
		}	break;
	}
}

static void
_hoops_AAASR(_hoops_RGRSR alter * state, unsigned short _hoops_SRASR,
			 unsigned short _hoops_GAASR, unsigned short _hoops_PAASR)
{
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			unsigned short data;

			if (_hoops_PAASR < (unsigned short) 31) {
				/* _hoops_ICHRR _hoops_SRSGR: _hoops_CSHGR _hoops_HRGR 4 _hoops_SIH, _hoops_HAASR _hoops_HRGR 7, _hoops_SPCC _hoops_HRGR  5 */
				data = ((_hoops_SRASR & 0xf) << 12) |
					   ((_hoops_GAASR & 0x7f) << 5) |
					   (_hoops_PAASR & 0x1f);
				_hoops_GGASR(state, data);
			}
			else {
				/* _hoops_SGH _hoops_ICHRR _hoops_SRSGR _hoops_CCA _hoops_SPCC = 31 */
				data = ((_hoops_SRASR & 0xf) << 12) |
					   ((_hoops_GAASR & 0x7f) << 5) |
					   (0x1f);
				_hoops_GGASR(state, data);

				/* _hoops_RGRRR _hoops_SRSGR: _hoops_SAS _hoops_HRGR 1 _hoops_IGRH (_hoops_PSAP), _hoops_SPCC _hoops_HRGR 15 */
				data = (_hoops_PAASR & 0xefff);
				_hoops_GGASR(state, data);
			}
		}	break;
		case _hoops_SHICR:
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Unexpected encoding on CGM3 header write attempt");
		}	break;
	}
}


/* _hoops_PGAA (_hoops_SIHR _hoops_RCICR _hoops_AGHS) */
static void
_hoops_IAASR(_hoops_RGRSR alter * state, Net_Rendition const &nr)
{
	Display_Context const * dc = nr->_hoops_SRA;
	int i, j, _hoops_CAASR, _hoops_SAASR;
	_hoops_GARSR background = nr->_hoops_SAIR->_hoops_GPIR._hoops_PGGCR;

	_hoops_HPICR ("add_supplied_pen_map\n");

	/* _hoops_CISA _hoops_GGR _hoops_CSGSR _hoops_RGGHR _hoops_HII _hoops_IPSP _hoops_CARSR _hoops_CSGSR _hoops_ARCR */
	if (state->_hoops_HRRSR)
		_hoops_CAASR = 0;
	else
		_hoops_CAASR = MAX_COLORS - 1;
	_hoops_SAASR = 0;
	for (i = 0; i < MAX_COLORS; i++)
		if (state->_hoops_CSIR[i].set) {
			/* _hoops_GPASR _hoops_AGAH _hoops_HAIR (_hoops_CIHA _hoops_HPP _hoops_HAS) _hoops_GGR _hoops_IPSP'_hoops_GRI _hoops_CSGSR _hoops_ARCR (_hoops_HPP _hoops_PPHR) */
			j = 0;
			while (j < _hoops_IRGCR (state->_hoops_SARSR->_hoops_GGRSR))
				if (state->_hoops_SARSR->pen[j].r == state->_hoops_CSIR[i].color._hoops_HRIR.r &&
					state->_hoops_SARSR->pen[j].g == state->_hoops_CSIR[i].color._hoops_HRIR.g &&
					state->_hoops_SARSR->pen[j].b == state->_hoops_CSIR[i].color._hoops_HRIR.b)
					break;
				else
					j++;

			/* _hoops_RGHH _hoops_GSGI _hoops_ARIPR _hoops_HA, _hoops_SR'_hoops_GCPP _hoops_AA _hoops_HAR _hoops_GSGI _hoops_SPHR */
			if (j < _hoops_IRGCR (state->_hoops_SARSR->_hoops_GGRSR)) {
				state->_hoops_CSIR[i]._hoops_RPRSR = state->_hoops_SARSR->pen[j].number;

				/* _hoops_GRHP _hoops_IHGC _hoops_IIGR _hoops_CGGPR _hoops_PPR _hoops_AHPA _hoops_IH _hoops_SPHR */
				if (state->_hoops_SARSR->pen[j].number < (unsigned char)_hoops_CAASR)
					_hoops_CAASR = (int)state->_hoops_SARSR->pen[j].number;
				if (state->_hoops_SARSR->pen[j].number > (unsigned char)_hoops_SAASR)
					_hoops_SAASR = (int)state->_hoops_SARSR->pen[j].number;

				/* _hoops_SGH _hoops_PHPH _hoops_IS _hoops_CRGS _hoops_SGS _hoops_RGCI _hoops_CIHA _hoops_SSCP _hoops_RPII _hoops_ARP */
				state->_hoops_CSIR[i]._hoops_GPRSR = true;
			}
		}

	/* _hoops_IPSP _hoops_GHCA _hoops_ARP _hoops_RPASR _hoops_HCSP _hoops_IS 1 _hoops_PPR _hoops_RSPC _hoops_IRS _hoops_ARCR _hoops_CCA _hoops_IRS 0 */
	if (_hoops_CAASR < dc->_hoops_PGCC._hoops_APASR)
		HE_ERROR2 (HEC_CGM_DRIVER, HES_FIRST_COLOR_IGNORED,
				   "Supplied pen map has values lower than first color",
				   "First color driver option will be ignored");

	/* _hoops_IPSP _hoops_GHCA _hoops_RSPC _hoops_IRS _hoops_ARCR _hoops_CCA _hoops_PPASR _hoops_RGGHR _hoops_GGR _hoops_SCH */
	if (_hoops_SAASR > MAX_COLORS - 1)
		HE_ERROR2 (HEC_CGM_DRIVER, HES_OUT_OF_RANGE_PEN_MAP,
				   "Supplied pen map has values greater than maximum",
				   "Indexes greater than max color will be ignored");

	/* _hoops_IPSP _hoops_GHCA _hoops_SGH _hoops_PSHA _hoops_HAR _hoops_GGR _hoops_HPASR _hoops_CARSR _hoops_ARCR _hoops_HIS */
	/* _hoops_SRSHR _hoops_GH _hoops_CAS _hoops_SR _hoops_RAAP _hoops_PSAP _hoops_PPR _hoops_IPASR _hoops_GII _hoops_HAR _hoops_GSGI */
	for (i = 0; i < MAX_COLORS; i++)
		if (state->_hoops_CSIR[i].set && !state->_hoops_CSIR[i]._hoops_GPRSR) {
			if (state->_hoops_IRRSR) {
				/* _hoops_ARCR _hoops_HCR _hoops_CPASR _hoops_AIRP _hoops_IS _hoops_RCICR _hoops_CIHA 1 */
				state->_hoops_CSIR[i]._hoops_RPRSR = (unsigned char)1;
				if (_hoops_SAASR < 1)
					_hoops_SAASR = 1;
			}
			else if (state->_hoops_ARRSR) {
				/* _hoops_ARCR _hoops_HCR _hoops_CPASR _hoops_AIRP _hoops_IS _hoops_AGAH' _hoops_CIHA */
				state->_hoops_CSIR[i]._hoops_RPRSR = (unsigned char)i;
				if (i > _hoops_SAASR)
					_hoops_SAASR = i;
			}
			else {
				/* _hoops_ARCR _hoops_HCR _hoops_CPASR _hoops_AIRP _hoops_IS _hoops_RH _hoops_SPS _hoops_HHPA _hoops_CIHA */
				if (++_hoops_SAASR < MAX_COLORS)
					state->_hoops_CSIR[i]._hoops_RPRSR = (unsigned char)_hoops_SAASR;
				else
					HE_ERROR2 (HEC_CGM_DRIVER, HES_INVALID_PEN_MAP_VALUE,
							   "Supplied pen map lacks values actually used",
							   "which led to too many colors");
			}
			state->_hoops_CSIR[i]._hoops_GPRSR = true;
		}

	/* _hoops_IRHH _hoops_RCRR _hoops_SRS _hoops_CIHA 0 _hoops_SPASR _hoops_GHASR _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_ARP */
	/* _hoops_CR _hoops_RCICR _hoops_GCA _hoops_RGR _hoops_RPP _hoops_GHASR _hoops_RHASR _hoops_CHR _hoops_AHASR */
	/* _hoops_SRS _hoops_HRGR _hoops_IGI _hoops_CR _hoops_RII _hoops_PSHA _hoops_HHS _hoops_GACC _hoops_ARCR _hoops_IS _hoops_CSGSR 0 */
	if (state->_hoops_HRRSR) {
		j = 0;
		while (j < MAX_COLORS)
			if (state->_hoops_CSIR[j].set &&
				state->_hoops_CSIR[j]._hoops_RPRSR == (unsigned char)0)
				break;
			else
				j++;
		if (j < MAX_COLORS) {
			if (state->_hoops_CSIR[j].color._hoops_HRIR.r != state->_hoops_CSIR[background].color._hoops_HRIR.r ||
				state->_hoops_CSIR[j].color._hoops_HRIR.g != state->_hoops_CSIR[background].color._hoops_HRIR.g ||
				state->_hoops_CSIR[j].color._hoops_HRIR.b != state->_hoops_CSIR[background].color._hoops_HRIR.b)
				HE_ERROR2 (HEC_CGM_DRIVER, HES_COLOR_INDEX_IGNORED,
						   "Supplied color map pen 0 RGB values do",
						   "not match the background color");
		}
	}

	/* _hoops_AHHR _hoops_GGSR _hoops_PHPH _hoops_SIH _hoops_CR _hoops_SR _hoops_PHASR _hoops_PPSPR _hoops_CAPR _hoops_ARRS */
	for (i = 0; i < MAX_COLORS; i++)
		state->_hoops_CSIR[i]._hoops_GPRSR = false;

	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			int		_hoops_HHASR;

			/* _hoops_IHASR _hoops_CHASR _hoops_SHASR _hoops_GIASR _hoops_PGGIR */
			_hoops_HHASR = _hoops_SAASR - _hoops_CAASR + 1;
			_hoops_AAASR (state, _hoops_HHSCR, _hoops_RGGSR, (unsigned short)(1 + (_hoops_HHASR * 3)));
			_hoops_ISRSR (state, (unsigned char)_hoops_CAASR);

			/* _hoops_RCSPR _hoops_PGGIR _hoops_IHASR _hoops_RIASR _hoops_AIASR */
			for (i = _hoops_CAASR; i <= _hoops_SAASR; i++) {
				/* _hoops_GPASR _hoops_PIASR _hoops_CIHA _hoops_GGR _hoops_HAIR _hoops_ARCR */
				j = 0;
				while (j < MAX_COLORS)
					if (state->_hoops_CSIR[j].set &&
						state->_hoops_CSIR[j]._hoops_RPRSR == (unsigned char)i)
						break;
					else
						j++;
				if (j < MAX_COLORS) {
					/* _hoops_GSGI - _hoops_GGI _hoops_SCH _hoops_GGR _hoops_RH _hoops_SCGR _hoops_CSRR */
					_hoops_ISRSR (state, state->_hoops_CSIR[j].color._hoops_HRIR.r);
					_hoops_ISRSR (state, state->_hoops_CSIR[j].color._hoops_HRIR.g);
					_hoops_ISRSR (state, state->_hoops_CSIR[j].color._hoops_HRIR.b);
					state->_hoops_CSIR[j]._hoops_GPRSR = true;

					/* _hoops_HPGGR _hoops_HIASR _hoops_CCA _hoops_PSHR _hoops_CIHA _hoops_GAR _hoops_CPHR _hoops_HAH */
					while (++j < MAX_COLORS)
						if (state->_hoops_CSIR[j].set &&
							state->_hoops_CSIR[j]._hoops_RPRSR == (unsigned char)i)
							state->_hoops_CSIR[j]._hoops_GPRSR = true;
				}
				else {
					/* _hoops_HAR _hoops_GSGI - _hoops_GGI _hoops_CPHP _hoops_SAHR _hoops_IS _hoops_CISA _hoops_RH _hoops_CSRR */
					if (state->_hoops_HRRSR && i == 0) {
						_hoops_ISRSR (state,
											state->_hoops_CSIR[background].color._hoops_HRIR.r);
						_hoops_ISRSR (state,
											state->_hoops_CSIR[background].color._hoops_HRIR.g);
						_hoops_ISRSR (state,
											state->_hoops_CSIR[background].color._hoops_HRIR.b);
					}
					else {
						_hoops_ISRSR (state, (unsigned char)0);
						_hoops_ISRSR (state, (unsigned char)0);
						_hoops_ISRSR (state, (unsigned char)i);
					}
				}
			}

			if (_hoops_HHASR % 2 == 0)
				_hoops_ISRSR (state, (unsigned char)0);
		}	break;

		case _hoops_SHICR: {
			/* _hoops_IHASR _hoops_CHASR _hoops_SHASR _hoops_GIASR _hoops_PGGIR */
			Sprintf_D (state->_hoops_IGRSR, "COLRTABLE %d", _hoops_CAASR);
			_hoops_CSRSR (state, state->_hoops_IGRSR);

			/* _hoops_RCSPR _hoops_PGGIR _hoops_IHASR _hoops_RIASR _hoops_AIASR */
			for (i = _hoops_CAASR; i <= _hoops_SAASR; i++) {
				/* _hoops_GPASR _hoops_PIASR _hoops_CIHA _hoops_GGR _hoops_HAIR _hoops_ARCR */
				j = 0;
				while (j < MAX_COLORS)
					if (state->_hoops_CSIR[j].set &&
						state->_hoops_CSIR[j]._hoops_RPRSR == (unsigned char)i)
						break;
					else
						j++;
				if (j < MAX_COLORS) {
					/* _hoops_GSGI - _hoops_GGI _hoops_SCH _hoops_GGR _hoops_RH _hoops_SCGR _hoops_CSRR */
					Sprintf_DD (state->_hoops_PGRSR, "\n (%d,%d,",
								(int)state->_hoops_CSIR[j].color._hoops_HRIR.r,
								(int)state->_hoops_CSIR[j].color._hoops_HRIR.g);
					Sprintf_SD (state->_hoops_IGRSR, "%s%d)",
								state->_hoops_PGRSR,
								(int)state->_hoops_CSIR[j].color._hoops_HRIR.b);
					_hoops_CSRSR (state, state->_hoops_IGRSR);
					state->_hoops_CSIR[j]._hoops_GPRSR = true;

					/* _hoops_HPGGR _hoops_HIASR _hoops_CCA _hoops_PSHR _hoops_CIHA _hoops_GAR _hoops_CPHR _hoops_HAH */
					while (++j < MAX_COLORS)
						if (state->_hoops_CSIR[j].set &&
							state->_hoops_CSIR[j]._hoops_RPRSR == (unsigned char)i)
							state->_hoops_CSIR[j]._hoops_GPRSR = true;
				}
				else {
					/* _hoops_HAR _hoops_GSGI - _hoops_GGI _hoops_CPHP _hoops_SAHR _hoops_IS _hoops_CISA _hoops_RH _hoops_CSRR */
					if (state->_hoops_HRRSR && i == 0) {
						Sprintf_DD (state->_hoops_PGRSR, "\n (%d,%d,",
									(int)state->_hoops_CSIR[background].color._hoops_HRIR.r,
									(int)state->_hoops_CSIR[background].color._hoops_HRIR.g);
						Sprintf_SD (state->_hoops_IGRSR, "%s%d)",
									state->_hoops_PGRSR,
									(int)state->_hoops_CSIR[background].color._hoops_HRIR.b);
					}
					else
						Sprintf_D (state->_hoops_IGRSR, "\n (0,0,%d)", i);
					_hoops_CSRSR (state, state->_hoops_IGRSR);
				}
			}
			_hoops_CSRSR (state, ";\n");
		}	break;

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "Invalid encoding in add supplied pen map");
		}	break;
	}
}


static bool
_hoops_IIASR(_hoops_RGRSR alter * state, Display_Context const *dc)
{
	_hoops_HPICR("open_CGM3_file\n");

	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			return (state->fp = fopen(dc->_hoops_PCRSR, "wb")) != null;
		}
		case _hoops_SHICR: {
			return (state->fp = fopen(dc->_hoops_PCRSR, "w")) != null;
		}
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Unexpected encoding in open CGM3 file");
			return false;
		}
	}
}

namespace _hoops_CIASR {
	static unsigned short const _hoops_SIASR[] = {
		LINE_COLOR,
		FILL_COLOR,
		MARKER_COLOR,
		TEXT_COLOR,
		BACKGROUND_COLOR,
		EDGE_COLOR
	};

	static char const * const _hoops_GCASR[] = {
		"LINE",
		"FILL",
		"MARKER",
		"TEXT",
		"BACK",
		"EDGE"
	};
};

static void
_hoops_RCASR(_hoops_RGRSR alter * state,
				 unsigned char geometry,
				 Driver_Color const *color)
{
	_hoops_ISC const *_hoops_ACASR = &color->_hoops_HRIR;
	_hoops_HPICR("set_color\n");

	if (state->_hoops_CSC.colors[geometry] != *color) {
		_hoops_HPICR("\t" "setting color" "\n");
		switch (state->_hoops_GRRSR) {
			case _hoops_CHICR: {
				unsigned short element = (geometry == _hoops_ICGSR) ? _hoops_AHCCR : _hoops_HHSCR;
				_hoops_AAASR(state, element, _hoops_CIASR::_hoops_SIASR[geometry], 3);
				_hoops_ISRSR(state, (unsigned char) _hoops_ACASR->r);
				_hoops_ISRSR(state, (unsigned char) _hoops_ACASR->g);
				_hoops_ISRSR(state, (unsigned char) _hoops_ACASR->b);
				_hoops_ISRSR(state, (unsigned char) 0);
			}	break;
			case _hoops_SHICR: {
				/* _hoops_PCASR _hoops_CSHA _hoops_IHASR */
				Sprintf_SD(state->_hoops_PGRSR, "%sCOLR (%d,", _hoops_CIASR::_hoops_GCASR[geometry], (int) _hoops_ACASR->r);
				Sprintf_DD(state->_hoops_HGRSR, "%d,%d);\n", (int) _hoops_ACASR->g, (int) _hoops_ACASR->b);
				Sprintf_SS(state->_hoops_IGRSR, "%s%s", state->_hoops_PGRSR, state->_hoops_HGRSR);
				_hoops_CSRSR(state, state->_hoops_IGRSR);
			}	break;
			default: {
				_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					"Invalid encoding in set color");
			}	break;
		}
		state->_hoops_CSC.colors[geometry] = *color;
	}
}


static void
_hoops_HCASR(_hoops_RGRSR alter * state,
				 unsigned char geometry,
				 Driver_Color const *color)
{
	int _hoops_ICASR = color->_hoops_PGGCR;

	bool _hoops_CCASR = false;

	_hoops_HPICR ("set_mapped_color\n");

	/*
	* _hoops_SCASR _hoops_RPGAR _hoops_IS _hoops_SGH _hoops_PSHA _hoops_SGS _hoops_CHR _hoops_HAR _hoops_ARP _hoops_PAR
	* _hoops_HAR _hoops_PHPH.	 _hoops_PGPR _hoops_GSASR _hoops_HRGR _hoops_GHASR _hoops_PGAP
	* _hoops_SAGGR _hoops_IGI _hoops_ARPP _hoops_SCH _hoops_IGRC _hoops_SAGGR _hoops_PHPH
	*/
	if (!state->_hoops_CSIR[_hoops_ICASR].set ||
		(!state->_hoops_CSIR[_hoops_ICASR]._hoops_GPRSR &&
		geometry != _hoops_ICGSR)) {
			_hoops_GARSR	_hoops_RSASR = 0;
			char		string[80];

			/* _hoops_SSS _hoops_GII _hoops_CIHA _hoops_SR _hoops_PAH _hoops_SGH (_hoops_SGH 255 _hoops_RPP _hoops_PIRC - _hoops_ASASR) */
			while (_hoops_RSASR < (_hoops_GARSR)255) {
				if (state->_hoops_CSIR[_hoops_RSASR].set && state->_hoops_CSIR[_hoops_RSASR]._hoops_GPRSR)
					break;
				else
					_hoops_RSASR++;
			}

			/* _hoops_RCSRR _hoops_RIHH _hoops_GPSRR _hoops_IIHA _hoops_GPP _hoops_PSASR */
			if (!state->_hoops_CSIR[_hoops_ICASR].set &&
				!state->_hoops_CSIR[_hoops_ICASR]._hoops_GPRSR)
				Sprintf_D (string, "Using color index %d that has not been set nor written", (int)_hoops_ICASR);
			else if (!state->_hoops_CSIR[_hoops_ICASR].set)
				Sprintf_D (string, "Using color index %d that has not been set", (int)_hoops_ICASR);
			else
				Sprintf_D (string, "Using color index %d that has not been written", (int)_hoops_ICASR);
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, string);

			/* _hoops_ICIC _hoops_IS _hoops_AA _hoops_HGAA _hoops_HA _hoops_SGS _hoops_HSASR _hoops_CHR _hoops_CPHR */
			_hoops_ICASR = _hoops_RSASR;
	}

	/* _hoops_ISPR _hoops_HAIR _hoops_RGSR _hoops_IIHA _hoops_GPP _hoops_CPAP */
	switch (geometry) {
		case _hoops_RCGSR: {
			_hoops_CCASR = state->_hoops_RARSR != _hoops_ICASR;
			if (_hoops_CCASR)
				state->_hoops_RARSR = _hoops_ICASR;
		}	break;

		case _hoops_ACGSR: {
			_hoops_CCASR = state->_hoops_AARSR != _hoops_ICASR;
			if (_hoops_CCASR)
				state->_hoops_AARSR = _hoops_ICASR;
		}	break;

		case _hoops_PCGSR: {
			_hoops_CCASR = state->_hoops_PARSR != _hoops_ICASR;
			if (_hoops_CCASR)
				state->_hoops_PARSR = _hoops_ICASR;
		}	break;

		case _hoops_CCGSR: {
			_hoops_CCASR = state->_hoops_IARSR != _hoops_ICASR;
			if (_hoops_CCASR)
				state->_hoops_IARSR = _hoops_ICASR;
		}

		default: {
			/* _hoops_CPAP = "_hoops_ISASR" */
			/* _hoops_SHR _hoops_GGI _hoops_RH _hoops_IGHP _hoops_HAIR */
			_hoops_CCASR = true;
		}	break;
	}

	/* _hoops_RCSRR _hoops_HAIR _hoops_AGRP _hoops_RPP _hoops_SIGR */
	if (_hoops_CCASR) {
		_hoops_HPICR ("\tsetting color\n");

		switch (state->_hoops_GRRSR) {
			case _hoops_CHICR: {
				/* _hoops_PCASR _hoops_CSHA _hoops_IHASR */
				switch (geometry) {
					case _hoops_RCGSR: {
						_hoops_AAASR (state, _hoops_HHSCR, LINE_COLOR, 1);
						_hoops_ISRSR (state, state->_hoops_CSIR[_hoops_ICASR]._hoops_RPRSR);
						_hoops_ISRSR (state, (unsigned char)0);
					}	break;

					case _hoops_ACGSR: {
						_hoops_AAASR (state, _hoops_HHSCR, FILL_COLOR, 1);
						_hoops_ISRSR (state,
							state->_hoops_CSIR[_hoops_ICASR]._hoops_RPRSR);
						_hoops_ISRSR (state, (unsigned char)0);
					}	break;

					case _hoops_PCGSR: {
						_hoops_AAASR (state, _hoops_HHSCR, MARKER_COLOR, 1);
						_hoops_ISRSR (state,
							state->_hoops_CSIR[_hoops_ICASR]._hoops_RPRSR);
						_hoops_ISRSR (state, (unsigned char)0);
					}	break;

					case _hoops_CCGSR: {
						_hoops_AAASR (state, _hoops_HHSCR, EDGE_COLOR, 1);
						_hoops_ISRSR (state,
							state->_hoops_CSIR[_hoops_ICASR]._hoops_RPRSR);
						_hoops_ISRSR (state, (unsigned char)0);
					}	break;

					default: {
						/* _hoops_ISASR */
						_hoops_AAASR (state, _hoops_AHCCR, BACKGROUND_COLOR, 3);
						_hoops_ISRSR (state, state->_hoops_CSIR[_hoops_ICASR].color._hoops_HRIR.r);
						_hoops_ISRSR (state, state->_hoops_CSIR[_hoops_ICASR].color._hoops_HRIR.g);
						_hoops_ISRSR (state, state->_hoops_CSIR[_hoops_ICASR].color._hoops_HRIR.b);
						_hoops_ISRSR (state, (unsigned char)0);
					}	break;
				}
			}	break;

			case _hoops_SHICR: {
				/* _hoops_PCASR _hoops_CSHA _hoops_IHASR */
				if (geometry == _hoops_ICGSR) {
					Sprintf_DD (state->_hoops_PGRSR, " BACKCOLR (%d,%d,",
								(int)state->_hoops_CSIR[_hoops_ICASR].color._hoops_HRIR.r,
								(int)state->_hoops_CSIR[_hoops_ICASR].color._hoops_HRIR.g);
					Sprintf_D (state->_hoops_HGRSR, "%d);\n",
								(int)state->_hoops_CSIR[_hoops_ICASR].color._hoops_HRIR.b);
					Sprintf_SS (state->_hoops_IGRSR, "%s%s",
								state->_hoops_PGRSR, state->_hoops_HGRSR);
				}
				else
					Sprintf_SD (state->_hoops_IGRSR, "%sCOLR %d;\n",
								_hoops_CIASR::_hoops_GCASR[geometry],
								(int)state->_hoops_CSIR[_hoops_ICASR]._hoops_RPRSR);
				_hoops_CSRSR (state, state->_hoops_IGRSR);
			}	break;

			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					"Invalid encoding in set mapped color");
			}	break;
		}
	}
}


static void
_hoops_CSASR(_hoops_RGRSR alter * state, unsigned char geometry, Driver_Color const *color)
{
	_hoops_HPICR("set_color\n");
	if (state->_hoops_CRRSR)
		_hoops_HCASR(state, geometry, color);
	else
		_hoops_RCASR(state, geometry, color);
}


static char **_hoops_SSASR(_hoops_RGRSR alter const *const state,
				 int *const _hoops_GGPSR)
{
	char **retval = 0;
	int length = 0;
	int i = 0;
	_hoops_IGPIR *table = state->dc->options._hoops_GPPIR;
	if (!table)
		return 0;
	while (table) {
		table = table->next;
		++length;
	}
	ZALLOC_ARRAY(retval, length, char *);
	table = state->dc->options._hoops_GPPIR;
	for (i = 0; i < length; ++i) {
		ALLOC_ARRAY(retval[i], _hoops_SSGR(table->specified.text) + 1, char);
		strcpy(retval[i], table->specified.text);
		table = table->next;
	}
	*_hoops_GGPSR = length;
	return retval;
}


static void _hoops_RGPSR(char **_hoops_AGPSR, int const length)
{
	int i;
	if (length == 0)
		return;
	for (i = 0; i < length; ++i) {
		FREE_ARRAY(_hoops_AGPSR[i], _hoops_SSGR(_hoops_AGPSR[i]) + 1, char);
	}
	FREE_ARRAY(_hoops_AGPSR, length, char *);
}


static void _hoops_PGPSR(_hoops_RGRSR alter * state)
{
	char *buffer, *s;
	int length = 0;
	int _hoops_HGPSR = 0;
	char **_hoops_AGPSR = 0;
	char const *const _hoops_IGPSR[] = { "Serif", "Times", "Courier", "Symbol", };
	int i;
	_hoops_AGPSR = _hoops_SSASR(state, &_hoops_HGPSR);
	state->text._hoops_PIRSR = _hoops_HGPSR;
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			for (i = 0; i < _hoops_HGPSR; ++i) {
				length += _hoops_SSGR(_hoops_AGPSR[i]) + 1;
			}
			for (i = 0; i < _hoops_GGAPR(_hoops_IGPSR); ++i) {
				length += _hoops_SSGR(_hoops_IGPSR[i]) + 1;
			}
			ALLOC_ARRAY(buffer, length + 1, char);
			for (s = buffer, i = 0; i < _hoops_HGPSR; ++i) {
				int _hoops_CGPSR = _hoops_SSGR(_hoops_AGPSR[i]);
				*s++ = (char) _hoops_CGPSR;
				strcpy(s, _hoops_AGPSR[i]);
				s += _hoops_CGPSR;
			}
			for (i = 0; i < _hoops_GGAPR(_hoops_IGPSR); ++i) {
				int _hoops_CGPSR = _hoops_SSGR(_hoops_IGPSR[i]);
				*s++ = (char) _hoops_CGPSR;
				strcpy(s, _hoops_IGPSR[i]);
				s += _hoops_CGPSR;
			}
			_hoops_AAASR(state, _hoops_ARCCR, _hoops_SACCR, length);
			for (i = 0; i < length; ++i) {
				_hoops_ISRSR(state, buffer[i]);
			}
			if (length & 1) {
				_hoops_ISRSR(state, 0);
			}
			FREE_ARRAY(buffer, length + 1, char);
		}	break;
		case _hoops_SHICR: {
			char font_name[256];
			_hoops_CSRSR(state, "FONTLIST ");
			for (i = 0; i < _hoops_HGPSR; ++i) {
				sprintf(font_name, "\"%s\" ", _hoops_AGPSR[i]);
				_hoops_CSRSR(state, font_name);
			}
			for (i = 0; i < _hoops_GGAPR(_hoops_IGPSR) - 1; ++i) {
				sprintf(font_name, "\"%s\" ", _hoops_IGPSR[i]);
				_hoops_CSRSR(state, font_name);
			}
			sprintf(font_name, "\"%s\";\n", _hoops_IGPSR[i]);
			_hoops_CSRSR(state, font_name);
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				"Invalid encoding in write_font_list");
		}	break;
	}
	_hoops_RGPSR(_hoops_AGPSR, _hoops_HGPSR);
}


static void
_hoops_SGPSR(_hoops_RGRSR alter * state, Net_Rendition const &nr)
{
	Display_Context const *dc = nr->_hoops_SRA;
	int _hoops_GRPSR, _hoops_RRPSR;
	_hoops_HPICR("add_begin_metafile_lines\n");
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			_hoops_AAASR(state, _hoops_HCICR, _hoops_CCICR,
								 (unsigned short) (_hoops_SSGR(dc->_hoops_PCRSR) + 1));
			_hoops_CSRSR(state, dc->_hoops_PCRSR);
			_hoops_AAASR(state, _hoops_ARCCR, _hoops_PRCCR,2);
			_hoops_GGASR(state, (unsigned short) state->_hoops_AGRSR);

			if (dc->options._hoops_IAPIR.length != 0)
				Sprintf_N(state->_hoops_IGRSR, "%n", &dc->options._hoops_IAPIR);
			else
				Sprintf_S(state->_hoops_IGRSR, "%s", "HOOPS Graphics System");
			_hoops_AAASR(state, _hoops_ARCCR, _hoops_HRCCR,
								 (unsigned short) (_hoops_SSGR(state->_hoops_IGRSR) +1));
			_hoops_CSRSR(state, state->_hoops_IGRSR);

			/* _hoops_HSPP _hoops_CCA _hoops_RH _hoops_CSCS _hoops_PHI _hoops_IIGR _hoops_IAGH, _hoops_GGCR _hoops_GAR _hoops_HAHH */
			_hoops_GRPSR = 33;
			if (state->_hoops_AGRSR == 3)
				_hoops_GRPSR += 4;
			if (state->_hoops_HRRSR)
				++_hoops_GRPSR;
			if (state->_hoops_CRRSR)
				_hoops_GRPSR += 2;

			_hoops_AAASR(state, _hoops_ARCCR, _hoops_IACCR,
								 (unsigned short) (2 + (_hoops_GRPSR * 4)));

			_hoops_GGASR(state, (unsigned short) _hoops_GRPSR);
			_hoops_CRASR(state, _hoops_HCICR, _hoops_SCICR);
			_hoops_CRASR(state, _hoops_ARCCR, _hoops_HRCCR);
			_hoops_CRASR(state, _hoops_ARCCR, _hoops_IRCCR);
			_hoops_CRASR(state, _hoops_ARCCR, _hoops_CACCR);
			_hoops_CRASR(state, _hoops_AHCCR, _hoops_GICCR);
			_hoops_CRASR(state, _hoops_AHCCR, _hoops_HHCCR);
			_hoops_CRASR(state, _hoops_AHCCR, _hoops_IHCCR);
			_hoops_CRASR(state, _hoops_AHCCR, _hoops_CHCCR);
			_hoops_CRASR(state, _hoops_CCCCR, _hoops_ASCCR);
			_hoops_CRASR(state, _hoops_CCCCR, _hoops_PSCCR);
			_hoops_CRASR(state, _hoops_CGSCR, _hoops_SASCR);
			_hoops_CRASR(state, _hoops_CGSCR, _hoops_SGSCR);
			_hoops_CRASR(state, _hoops_CGSCR, _hoops_IRSCR);
			_hoops_CRASR(state, _hoops_CGSCR, _hoops_RASCR);
			_hoops_CRASR(state, _hoops_CGSCR, _hoops_RRSCR);
			_hoops_CRASR(state, _hoops_CGSCR, _hoops_SRSCR);
			_hoops_CRASR(state, _hoops_HHSCR, _hoops_GGGSR);
			_hoops_CRASR(state, _hoops_HHSCR, _hoops_SSSCR);
			_hoops_CRASR(state, _hoops_HHSCR, LINE_COLOR);
			_hoops_CRASR(state, _hoops_HHSCR, FILL_COLOR);
			_hoops_CRASR(state, _hoops_HHSCR, MARKER_COLOR);
			_hoops_CRASR(state, _hoops_HHSCR, _hoops_SCSCR);
			_hoops_CRASR(state, _hoops_HHSCR, _hoops_GSSCR);
			_hoops_CRASR(state, _hoops_HHSCR, _hoops_RSSCR);
			_hoops_CRASR(state, _hoops_HHSCR, _hoops_CHSCR);
			_hoops_CRASR(state, _hoops_HHSCR, _hoops_SHSCR);
			if (state->_hoops_AGRSR == 3) {
				_hoops_CRASR(state, _hoops_HHSCR, _hoops_HGGSR);
				_hoops_CRASR(state, _hoops_HHSCR, _hoops_IGGSR);
				_hoops_CRASR(state, _hoops_HHSCR, _hoops_PRGSR);
				_hoops_CRASR(state, _hoops_HHSCR, _hoops_HRGSR);
			}
			_hoops_CRASR(state, _hoops_HHSCR, _hoops_PSSCR);
			_hoops_CRASR(state, _hoops_HHSCR, _hoops_HSSCR);
			_hoops_CRASR(state, _hoops_HHSCR, _hoops_ISSCR);
			_hoops_CRASR(state, _hoops_HHSCR, _hoops_RISCR);
			_hoops_CRASR(state, _hoops_HHSCR, _hoops_CSSCR);
			_hoops_CRASR(state, _hoops_HHSCR,_hoops_ARGSR);
			_hoops_CRASR(state, _hoops_AHCCR, _hoops_PHCCR);
			if (state->_hoops_CRRSR) {
				_hoops_CRASR(state, _hoops_ARCCR, _hoops_PACCR);
				_hoops_CRASR(state, _hoops_HHSCR, _hoops_RGGSR);
			}
			if (state->_hoops_HRRSR) {
				_hoops_CRASR(state, _hoops_AHCCR, BACKGROUND_COLOR);
			}

			_hoops_AAASR(state, _hoops_ARCCR, _hoops_IRCCR, 2);
			_hoops_GGASR(state, (unsigned short) 1);	/* 1 = _hoops_HPHR */

			_hoops_RRPSR = 18;
			if (state->_hoops_HRRSR)
				_hoops_RRPSR += 5;

			_hoops_AAASR(state, _hoops_ARCCR, _hoops_CACCR,
								 (unsigned short) _hoops_RRPSR);
			_hoops_AAASR(state, _hoops_AHCCR, _hoops_GICCR, 16);
			state->points[0].x = 0.0f;
			state->points[0].y = 0.0f;
			if (dc->options._hoops_ARPSR) {
				state->points[1].y = (float) dc->_hoops_PGCC._hoops_PRPSR.x;
				state->points[1].x = (float) dc->_hoops_PGCC._hoops_PRPSR.y;
			}
			else {
				state->points[1].x = (float) dc->_hoops_PGCC._hoops_PRPSR.x;
				state->points[1].y = (float) dc->_hoops_PGCC._hoops_PRPSR.y;
			}
			_hoops_RAASR(state, state->points, 2);

			/* _hoops_HRPSR _hoops_IHASR */
			if (state->_hoops_HRRSR) {
				_hoops_CGRA const &_hoops_SGRA = nr->_hoops_SAIR;

				/*
				* _hoops_IRPSR'_hoops_RA _hoops_AASA _hoops_CHGSR _hoops_PII _hoops_SCAC _hoops_HCGR _hoops_AGIR
				* _hoops_PGGA _hoops_IIGR _hoops_RH _hoops_PSHPR _hoops_CRPSR - _hoops_RGHH _hoops_ARI _hoops_SSPP
				*/
				_hoops_AAASR(state, _hoops_AHCCR, BACKGROUND_COLOR, 3);
				if (state->_hoops_CRRSR) {
					_hoops_GARSR c = _hoops_SGRA->_hoops_GPIR._hoops_PGGCR;
					_hoops_ISRSR(state, (unsigned char) state->_hoops_CSIR[c].color._hoops_HRIR.r);
					_hoops_ISRSR(state, (unsigned char) state->_hoops_CSIR[c].color._hoops_HRIR.g);
					_hoops_ISRSR(state, (unsigned char) state->_hoops_CSIR[c].color._hoops_HRIR.b);
				}
				else {
					_hoops_ISC const *_hoops_ACASR;
					_hoops_ACASR = &_hoops_SGRA->_hoops_GPIR._hoops_HRIR;
					_hoops_ISRSR(state, (unsigned char) _hoops_ACASR->r);
					_hoops_ISRSR(state, (unsigned char) _hoops_ACASR->g);
					_hoops_ISRSR(state, (unsigned char) _hoops_ACASR->b);
				}
			}

			/* _hoops_HIGGR _hoops_SRPSR _hoops_GAPSR */
			/* _hoops_ISGHR _hoops_SCAC _hoops_HCGR, _hoops_RSGR _hoops_HRGR _hoops_GIR _hoops_HPP _hoops_RAPSR _hoops_RPR */
			if (_hoops_RRPSR % 2 == 1)
				_hoops_ISRSR (state, (unsigned char)0);

			if (state->_hoops_CRRSR) {
				_hoops_AAASR (state, _hoops_ARCCR, _hoops_PACCR, 1);
				if (dc->options._hoops_AAPSR == 0)
					_hoops_ISRSR (state, (unsigned char)(MAX_COLORS - 1));
				else
					_hoops_ISRSR (state, (unsigned char)(dc->options._hoops_AAPSR - 1));
				_hoops_ISRSR (state, (unsigned char)0);
			}

			if (state->_hoops_AGRSR == 3)
				_hoops_PGPSR(state);
		}	break;
	case _hoops_SHICR: {
			Sprintf_S(state->_hoops_IGRSR, "BEGMF %S;\n", dc->_hoops_PCRSR);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
			_hoops_CSRSR(state, "MFVERSION 3;\n");
			if (dc->options._hoops_IAPIR.length != 0) {
				Sprintf_N(state->_hoops_IGRSR, "MFDESC \"%n\";\n",
					&dc->options._hoops_IAPIR);
				_hoops_CSRSR(state, state->_hoops_IGRSR);
			}
			else
				_hoops_CSRSR(state,"MFDESC \"HOOPS Graphics System\";\n");
			_hoops_CSRSR(state, "MFELEMLIST\n");
			_hoops_CSRSR(state, " \"MFDESC\n");
			_hoops_CSRSR(state, "	VDCTYPE\n");
			_hoops_CSRSR(state, "	BEGMFDEFAULTS\n");
			_hoops_CSRSR(state, "	VDCEXT\n");
			_hoops_CSRSR(state, "	ENDMFDEFAULTS\n");
			_hoops_CSRSR(state, "	BEGPIC\n");
			_hoops_CSRSR(state, "	BEGPICBODY\n");
			_hoops_CSRSR(state, "	ENDPIC\n");
			_hoops_CSRSR(state, "	PATSIZE\n");
			_hoops_CSRSR(state, "	PATTABLE\n");
			_hoops_CSRSR(state, "	LINECOLR\n");
			_hoops_CSRSR(state, "	FILLCOLR\n");
			_hoops_CSRSR(state, "	EDGECOLR\n");
			_hoops_CSRSR(state, "	MARKERCOLR\n");
			_hoops_CSRSR(state, "	INTSTYLE\n");
			_hoops_CSRSR(state, "	HATCHINDEX\n");
			_hoops_CSRSR(state, "	PATINDEX\n");
			_hoops_CSRSR(state, "	LINETYPE\n");
			_hoops_CSRSR(state, "	LINEWIDTH\n");
			if (state->_hoops_AGRSR == 3) {
				_hoops_CSRSR(state, "	LINECAP\n");
				_hoops_CSRSR(state, "	LINEJOIN\n");
				_hoops_CSRSR(state, "	EDGECAP\n");
				_hoops_CSRSR(state, "	EDGEJOIN\n");
			}
			_hoops_CSRSR(state, "	CLIPRECT\n");
			_hoops_CSRSR(state, "	CLIP\n");
			_hoops_CSRSR(state, "	ELLIPSE\n");
			_hoops_CSRSR(state, "	LINE\n");
			_hoops_CSRSR(state, "	POLYGON\n");
			_hoops_CSRSR(state, "	RECT\n");
			_hoops_CSRSR(state, "	MARKERTYPE\n");
			_hoops_CSRSR(state, "	MARKER\n");
			_hoops_CSRSR(state, "	COLRMODE\n");
			_hoops_CSRSR(state, "	LINEWIDTHMODE\n");
			_hoops_CSRSR(state, "	MARKERSIZEMODE\n");
			_hoops_CSRSR(state, "	SCALEMODE\n");
			_hoops_CSRSR(state, "	EDGEWIDTHMODE\n");
			_hoops_CSRSR(state, "	EDGEVIS\n");
			_hoops_CSRSR(state, "	EDGETYPE\n");
			_hoops_CSRSR(state, "	EDGEWIDTH\n");
			_hoops_CSRSR(state, "	CELLARRAY\";\n");

			if (state->_hoops_HRRSR)
				_hoops_CSRSR(state, "	BACKCOLR\n");
			_hoops_CSRSR(state, "VDCTYPE REAL;\n");
			if (state->_hoops_AGRSR == 3)
				_hoops_PGPSR(state);
			_hoops_CSRSR(state, "BEGMFDEFAULTS;\n");
			Sprintf_DD(state->_hoops_IGRSR, " VDCEXT (0,0) (%d,%d);\n",
				dc->_hoops_PGCC._hoops_PRPSR.x,
				dc->_hoops_PGCC._hoops_PRPSR.y);
			_hoops_CSRSR(state, state->_hoops_IGRSR);

			/* _hoops_HRPSR _hoops_IHASR */
			if (state->_hoops_HRRSR) {
				_hoops_CSASR(state, _hoops_ICGSR, &nr->_hoops_SAIR->_hoops_GPIR);
			}
			_hoops_CSRSR(state, "ENDMFDEFAULTS;\n");

			/* _hoops_PAPSR _hoops_IHASR _hoops_HAPSR */
			if (state->_hoops_CRRSR) {
				if (dc->options._hoops_AAPSR == 0)
					Sprintf_D (state->_hoops_IGRSR, "MAXCOLRINDEX %d;\n", MAX_COLORS - 1);
				else
					Sprintf_D (state->_hoops_IGRSR, "MAXCOLRINDEX %d;\n", (int)dc->options._hoops_AAPSR - 1);
				_hoops_CSRSR (state, state->_hoops_IGRSR);
			}
		}	break;
	default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				"Invalid encoding in add begin metafile lines");
		}	break;
	}
}


static void _hoops_IAPSR(_hoops_RGRSR alter * state)
{
	_hoops_HPICR("add_end_metafile_line\n");
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			_hoops_AAASR(state, _hoops_HCICR, _hoops_SCICR, 0);
		}	break;
		case _hoops_SHICR: {
			_hoops_CSRSR(state, "ENDMF;\n");
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in add end metafile line");
		}	break;
	}
}


static void _hoops_CAPSR(_hoops_RGRSR alter * state)
{

	/* _hoops_SICR _hoops_SAPSR _hoops_IS _hoops_GPPSR */
	float _hoops_RPPSR =
		state->_hoops_RGRA * 10.0f * (1.0f / state->_hoops_HIRSR);
	int _hoops_APPSR = _hoops_ASRSR(state->dc);
	_hoops_HPICR("add_begin_picture_lines\n");
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			Sprintf_D(state->_hoops_IGRSR, "PIC%d", state->_hoops_SGRSR);
			_hoops_AAASR(state, _hoops_HCICR, _hoops_GSICR,
								 (unsigned short) (_hoops_SSGR(state->_hoops_IGRSR) + 1));
			_hoops_CSRSR(state, state->_hoops_IGRSR);
			_hoops_AAASR(state, _hoops_AHCCR, _hoops_HHCCR, 2);
			if (state->_hoops_CRRSR)
				_hoops_GGASR(state, (unsigned short) 0);	/* 0 = _hoops_SCGH */
			else
				_hoops_GGASR(state, (unsigned short) 1);	/* 1 = _hoops_PPPSR */
			_hoops_AAASR(state, _hoops_AHCCR, _hoops_PHCCR, 6);
			_hoops_GGASR(state, (unsigned short) _hoops_APPSR);/* 1 = _hoops_HPPSR */
			_hoops_IGASR(state, _hoops_RPPSR);
			_hoops_AAASR(state, _hoops_AHCCR, _hoops_IHCCR, 2);
			_hoops_GGASR(state, (unsigned short) 0);	/* 0 = _hoops_IPPSR	*/
			_hoops_AAASR(state, _hoops_AHCCR, _hoops_CHCCR, 2);
			if (BIT(state->dc->options._hoops_IRARR, _hoops_HHICR))
				_hoops_GGASR(state, (unsigned short) 1);	/* 1 = _hoops_CPPSR */
			else
				_hoops_GGASR(state, (unsigned short) 0);	/* 0 = _hoops_IPPSR	*/
			_hoops_AAASR(state, _hoops_AHCCR, _hoops_SHCCR, 2);
			_hoops_GGASR(state, (unsigned short) 0);	/* 0 = _hoops_IPPSR	*/
			_hoops_AAASR(state, _hoops_HCICR,	_hoops_RSICR, 0);
		}	break;
		case _hoops_SHICR: {
			Sprintf_D(state->_hoops_IGRSR, "BEGPIC \"PIC%d\";\n", state->_hoops_SGRSR);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
			if (state->_hoops_CRRSR)
				_hoops_CSRSR(state, " COLRMODE INDEXED;\n");
			else
				_hoops_CSRSR(state, " COLRMODE DIRECT;\n");
			if (_hoops_APPSR == _hoops_AIICR)
				Sprintf_F(state->_hoops_IGRSR, " SCALEMODE METRIC %f;\n", _hoops_RPPSR);
			else
				Sprintf_F(state->_hoops_IGRSR, " SCALEMODE ABSTRACT %f;\n", _hoops_RPPSR);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
			_hoops_CSRSR(state, " LINEWIDTHMODE ABSOLUTE;\n");
			_hoops_CSRSR(state, " MARKERSIZEMODE ABSOLUTE;\n");
			_hoops_CSRSR(state, " EDGEWIDTHMODE ABSOLUTE;\n");
			_hoops_CSRSR(state, "BEGPICBODY;\n");
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				"Invalid encoding in add begin picture lines");
		}	break;
	}
}

static void
_hoops_SPPSR(_hoops_RGRSR alter * state,
					bool const vis)
{
	_hoops_HPICR("set_edge_visibility" "\n");

	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			if (state->_hoops_CSC._hoops_IHRSR != vis) {
				_hoops_HPICR("\t" "setting visibility" "\n");
				_hoops_AAASR(state, _hoops_HHSCR, _hoops_ISSCR, 2);
				_hoops_GGASR(state, (unsigned short)(vis ? 1 : 0));
				state->_hoops_CSC._hoops_IHRSR = vis;
			}
		}	break;
		case _hoops_SHICR: {
			if (state->_hoops_CSC._hoops_IHRSR != vis) {
				_hoops_HPICR("\t" "setting visibility" "\n");
				Sprintf_S(state->_hoops_IGRSR, "EDGEVIS %s;\n", (vis ? "ON" : "OFF"));
				_hoops_CSRSR(state, state->_hoops_IGRSR);
				state->_hoops_CSC._hoops_IHRSR = vis;
			}
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in set_edge_visibility");
		}	break;
	}
}


static void
_hoops_GHPSR(_hoops_RGRSR alter * state,
			   unsigned short const fill_style)
{
	_hoops_HPICR("set_fill_style\n");

	char const * const _hoops_RHPSR[] = { "HOLLOW", "SOLID", "PAT", "HATCH", "EMPTY", "GEOPAT", "INTERP" };

	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			if (state->_hoops_CSC.fill_style != fill_style) {
				_hoops_AAASR(state, _hoops_HHSCR, _hoops_SCSCR, 2);
				_hoops_GGASR(state, fill_style);
				state->_hoops_CSC.fill_style = fill_style;
			}
		}	break;
		case _hoops_SHICR: {
			if (state->_hoops_CSC.fill_style != fill_style) {
				Sprintf_S(state->_hoops_IGRSR, "INTSTYLE %S\n", _hoops_RHPSR[fill_style]);
				_hoops_CSRSR(state, state->_hoops_IGRSR);
				state->_hoops_CSC.fill_style = fill_style;
			}
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in draw_ellipse");
		}	break;
	}
}

static void
_hoops_AHPSR(_hoops_RGRSR alter * state,
				 Display_Context const *dc,
				 int _hoops_PHPSR)
{
	UNREFERENCED(dc);
	_hoops_HPICR("set_face_pattern\n");

	int _hoops_HHPSR = 0, _hoops_IHPSR = 0;
	switch (_hoops_PHPSR) {
		case FP_SOLID: {
			_hoops_HHPSR = _hoops_PIGSR;
			_hoops_IHPSR = state->_hoops_CSC._hoops_APRSR;	/* _hoops_SHSP _hoops_SCPCR */
		}	break;
		case FP_HORIZONTAL_BARS:
		case FP_WINDOW_HORIZONTAL_BARS: {
			_hoops_HHPSR = _hoops_IIGSR;
			_hoops_IHPSR = 1;
		}	break;
		case FP_VERTICAL_BARS:
		case FP_WINDOW_VERTICAL_BARS: {
			_hoops_HHPSR = _hoops_IIGSR;
			_hoops_IHPSR = 2;
		}	break;
		case FP_SLANT_RIGHT:
		case FP_WINDOW_SLANT_RIGHT: {
			_hoops_HHPSR = _hoops_IIGSR;
			_hoops_IHPSR = 3;
		}	break;
		case FP_WINDOW_SLANT_LEFT:
		case FP_SLANT_LEFT: {
			_hoops_HHPSR = _hoops_IIGSR;
			_hoops_IHPSR = 4;
		}	break;
		case FP_CHECKERBOARD:
		case FP_CROSSHATCH:
		case FP_SQUARE_DOTS:
		case FP_WINDOW_CHECKERBOARD:
		case FP_WINDOW_CROSSHATCH:
		case FP_WINDOW_SQUARE_DOTS: {
			_hoops_HHPSR = _hoops_IIGSR;
			_hoops_IHPSR = 5;
		}	break;
		case FP_DIAMONDS:
		case FP_WINDOW_DIAMONDS: {
			_hoops_HHPSR = _hoops_IIGSR;
			_hoops_IHPSR = 6;
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Unexpected face pattern");
			_hoops_HHPSR = _hoops_PIGSR;
			_hoops_IHPSR = state->_hoops_CSC._hoops_APRSR;	/* _hoops_SHSP
															* _hoops_SCPCR */
		}	break;
	}

	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			_hoops_GHPSR(state, _hoops_HHPSR);
			if (state->_hoops_CSC._hoops_APRSR != _hoops_IHPSR) {
				_hoops_HPICR("\t" "setting face pattern" "\n");
				_hoops_AAASR(state, _hoops_HHSCR, _hoops_GSSCR,2);
				_hoops_GGASR(state, (unsigned short) _hoops_IHPSR);
			}
		}	break;
		case _hoops_SHICR: {
			_hoops_GHPSR(state, _hoops_HHPSR);
			if (state->_hoops_CSC._hoops_APRSR != _hoops_IHPSR) {
				_hoops_HPICR("\t" "setting face pattern" "\n");
				Sprintf_D(state->_hoops_IGRSR, "HATCHINDEX %d;\n", _hoops_IHPSR);
				_hoops_CSRSR(state, state->_hoops_IGRSR);
			}
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						"Invalid encoding in set face pattern");
		}	break;
	}
	state->_hoops_CSC.fill_style = _hoops_HHPSR;
	state->_hoops_CSC._hoops_APRSR = _hoops_IHPSR;
}

static void
_hoops_CHPSR(_hoops_RGRSR alter * state,
				 int _hoops_PHPSR,
				 int _hoops_SHPSR)
{
	_hoops_HPICR("set_edge_pattern\n");

	int _hoops_CPRSR = _hoops_SHPSR & (LCAP_MASK | LPAT_MASK);
	int _hoops_SPRSR = _hoops_SHPSR & LJOIN_MASK;

	if (state->_hoops_CSC._hoops_IPRSR != _hoops_PHPSR) {
		_hoops_HPICR("\t" "setting edge pattern" "\n");

		switch (state->_hoops_GRRSR) {
			case _hoops_CHICR:{
				_hoops_AAASR(state, _hoops_HHSCR, _hoops_PSSCR, 2);
				switch (_hoops_PHPSR) {
					case LP_SOLID:
						_hoops_GGASR(state, (unsigned short) 1);
						break;
					case LP_DASHED:
						_hoops_GGASR(state, (unsigned short) 2);
						break;
					case LP_DOTTED:
						_hoops_GGASR(state, (unsigned short) 3);
						break;
					case LP_DASHDOT:
						_hoops_GGASR(state, (unsigned short) 4);
						break;
					case LP_DASH_2DOT:
						_hoops_GGASR(state, (unsigned short) 5);
						break;
				}
			}	break;

			case _hoops_SHICR:{
				switch (_hoops_PHPSR) {
					case LP_SOLID:
						_hoops_CSRSR(state, "EDGETYPE 1;\n");
						break;
					case LP_DASHED:
						_hoops_CSRSR(state, "EDGETYPE 2;\n");
						break;
					case LP_DOTTED:
						_hoops_CSRSR(state, "EDGETYPE 3;\n");
						break;
					case LP_DASHDOT:
						_hoops_CSRSR(state, "EDGETYPE 4;\n");
						break;
					case LP_DASH_2DOT:
						_hoops_CSRSR(state, "EDGETYPE 5;\n");
						break;
				}
			}	break;

			default:{
				_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								  "Invalid encoding in set line pattern");
			}	break;
		}
		state->_hoops_CSC._hoops_IPRSR = _hoops_PHPSR;
	}


	if (state->_hoops_AGRSR == 3 && state->_hoops_CSC._hoops_CPRSR != _hoops_CPRSR) {
		_hoops_HPICR("\tsetting line cap\n");

		switch (state->_hoops_GRRSR) {
			case _hoops_CHICR:{
				_hoops_AAASR(state, _hoops_HHSCR, _hoops_PRGSR, 4);
				switch (_hoops_CPRSR & LCAP_MASK) {
					case LCAP_BUTT:
						_hoops_GGASR(state, (unsigned short) 2);
						break;
					case LCAP_ROUND:
						_hoops_GGASR(state, (unsigned short) 3);
						break;
					case LCAP_SQUARE:
						_hoops_GGASR(state, (unsigned short) 4);
						break;
				}
				switch (_hoops_CPRSR & LPAT_MASK) {	/* _hoops_GIPSR _hoops_RIRR */
					case LPAT_BUTT:
						_hoops_GGASR(state, (unsigned short) 2);
						break;	/* _hoops_RIPSR (_hoops_PIRC) */
					default:
						_hoops_GGASR(state, (unsigned short) 3);
						break;	/* _hoops_PSSP _hoops_RSGR _hoops_RIRR */
				}
			}	break;

			case _hoops_SHICR:{
				switch (_hoops_CPRSR & LCAP_MASK) {
					case LCAP_BUTT:
						_hoops_CSRSR(state, "EDGECAP 1");
						break;
					case LCAP_ROUND:
						_hoops_CSRSR(state, "EDGECAP 2");
						break;
					case LCAP_SQUARE:
						_hoops_CSRSR(state, "EDGECAP 3");
						break;
				}
				switch (_hoops_CPRSR & LPAT_MASK) {	/* _hoops_GIPSR _hoops_RIRR */
					case LPAT_BUTT:
						_hoops_CSRSR(state, " 2;\n");
						break;	/* _hoops_RIPSR (_hoops_PIRC) */
					default:
						_hoops_CSRSR(state, " 3;\n");
						break;	/* _hoops_PSSP _hoops_RSGR _hoops_RIRR */
				}
			}	break;

			default:{
				_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								  "Invalid encoding in set edge pattern");
			}	break;
		}

		state->_hoops_CSC._hoops_CPRSR = _hoops_CPRSR;
	}

	if (state->_hoops_AGRSR == 3 && state->_hoops_CSC._hoops_SPRSR != _hoops_SPRSR) {
		_hoops_HPICR("\t" "setting edge join" "\n");

		switch (state->_hoops_GRRSR) {
			case _hoops_CHICR:{
				_hoops_AAASR(state, _hoops_HHSCR, _hoops_HRGSR, 2);

				switch (_hoops_SPRSR) {
					case LJOIN_MITER:
						_hoops_GGASR(state, (unsigned short) 2);
						break;
					case LJOIN_ROUND:
						_hoops_GGASR(state, (unsigned short) 3);
						break;
					case LJOIN_BEVEL:
						_hoops_GGASR(state, (unsigned short) 4);
						break;
				}
			}	break;

			case _hoops_SHICR:{
				switch (_hoops_SPRSR) {
					case LJOIN_MITER:
						_hoops_CSRSR(state, "EDGEJOIN 2;\n");
						break;
					case LJOIN_ROUND:
						_hoops_CSRSR(state, "EDGEJOIN 3;\n");
						break;
					case LJOIN_BEVEL:
						_hoops_CSRSR(state, "EDGEJOIN 4;\n");
						break;
				}
			}	break;

			default: {
				_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								  "Invalid encoding in set edge pattern");
			}	break;
		}
		state->_hoops_CSC._hoops_SPRSR = _hoops_SPRSR;
	}
}


static void
_hoops_AIPSR(_hoops_RGRSR alter * state, int _hoops_PHPSR,
		 int line_style)
{
	int _hoops_HPRSR = line_style & (LCAP_MASK | LPAT_MASK);
	int line_join = line_style & LJOIN_MASK;

	_hoops_HPICR("set_line_pattern\n");

	if (state->_hoops_CSC._hoops_PPRSR != _hoops_PHPSR) {
		_hoops_HPICR("\tsetting line pattern\n");

		switch (state->_hoops_GRRSR) {
			case _hoops_CHICR:{
				_hoops_AAASR(state, _hoops_HHSCR, _hoops_CHSCR, 2);
				switch (_hoops_PHPSR) {
					case LP_SOLID:
						_hoops_GGASR(state, (unsigned short) 1);
						break;
					case LP_DASHED:
						_hoops_GGASR(state, (unsigned short) 2);
						break;
					case LP_DOTTED:
						_hoops_GGASR(state, (unsigned short) 3);
						break;
					case LP_DASHDOT:
						_hoops_GGASR(state, (unsigned short) 4);
						break;
					case LP_DASH_2DOT:
						_hoops_GGASR(state, (unsigned short) 5);
						break;
				}
			}	break;

			case _hoops_SHICR:{
				switch (_hoops_PHPSR) {
					case LP_SOLID:
						_hoops_CSRSR(state, "LINETYPE 1;\n");
						break;
					case LP_DASHED:
						_hoops_CSRSR(state, "LINETYPE 2;\n");
						break;
					case LP_DOTTED:
						_hoops_CSRSR(state, "LINETYPE 3;\n");
						break;
					case LP_DASHDOT:
						_hoops_CSRSR(state, "LINETYPE 4;\n");
						break;
					case LP_DASH_2DOT:
						_hoops_CSRSR(state, "LINETYPE 5;\n");
						break;
				}
			}	break;

			default:{
				_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								  "Invalid encoding in set line pattern");
			}	break;
		}
		state->_hoops_CSC._hoops_PPRSR = _hoops_PHPSR;
	}


	if (state->_hoops_AGRSR == 3 && state->_hoops_CSC._hoops_HPRSR != _hoops_HPRSR) {
		_hoops_HPICR("\tsetting line cap\n");

		switch (state->_hoops_GRRSR) {
			case _hoops_CHICR:{
				_hoops_AAASR(state, _hoops_HHSCR, _hoops_HGGSR, 4);
				switch (_hoops_HPRSR & LCAP_MASK) {
					case LCAP_BUTT:
						_hoops_GGASR(state, (unsigned short) 2);
						break;
					case LCAP_ROUND:
						_hoops_GGASR(state, (unsigned short) 3);
						break;
					case LCAP_SQUARE:
						_hoops_GGASR(state, (unsigned short) 4);
						break;
				}
				switch (_hoops_HPRSR & LPAT_MASK) {	/* _hoops_GIPSR _hoops_RIRR */
					case LPAT_BUTT:
						_hoops_GGASR(state, (unsigned short) 2);
						break;	/* _hoops_RIPSR (_hoops_PIRC) */
					default:
						_hoops_GGASR(state, (unsigned short) 3);
						break;	/* _hoops_PSSP _hoops_RSGR _hoops_RIRR */
				}
			}	break;

			case _hoops_SHICR:{
				switch (_hoops_HPRSR & LCAP_MASK) {
					case LCAP_BUTT:
						_hoops_CSRSR(state, "LINECAP 1");
						break;
					case LCAP_ROUND:
						_hoops_CSRSR(state, "LINECAP 2");
						break;
					case LCAP_SQUARE:
						_hoops_CSRSR(state, "LINECAP 3");
						break;
				}
				switch (_hoops_HPRSR & LPAT_MASK) {	/* _hoops_GIPSR _hoops_RIRR */
					case LPAT_BUTT:
						_hoops_CSRSR(state, " 2;\n");
						break;	/* _hoops_RIPSR (_hoops_PIRC) */
					default:
						_hoops_CSRSR(state, " 3;\n");
						break;	/* _hoops_PSSP _hoops_RSGR _hoops_RIRR */
				}
			}	break;

			default:{
				_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								  "Invalid encoding in set line pattern");
			}	break;
		}

		state->_hoops_CSC._hoops_HPRSR = _hoops_HPRSR;
	}

	if (state->_hoops_AGRSR == 3 && state->_hoops_CSC.line_join != line_join) {
		_hoops_HPICR("\tsetting line join\n");

		switch (state->_hoops_GRRSR) {
			case _hoops_CHICR:{
				_hoops_AAASR(state, _hoops_HHSCR, _hoops_IGGSR, 2);

				switch (line_join) {
					case LJOIN_MITER:
						_hoops_GGASR(state, (unsigned short) 2);
						break;
					case LJOIN_ROUND:
						_hoops_GGASR(state, (unsigned short) 3);
						break;
					case LJOIN_BEVEL:
						_hoops_GGASR(state, (unsigned short) 4);
						break;
				}
			}	break;

			case _hoops_SHICR:{
				switch (line_join) {
					case LJOIN_MITER:
						_hoops_CSRSR(state, "LINEJOIN 2;\n");
						break;
					case LJOIN_ROUND:
						_hoops_CSRSR(state, "LINEJOIN 3;\n");
						break;
					case LJOIN_BEVEL:
						_hoops_CSRSR(state, "LINEJOIN 4;\n");
						break;
				}
			}	break;

			default: {
				_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								  "Invalid encoding in set line pattern");
			}	break;
		}
		state->_hoops_CSC.line_join = line_join;
	}
}


static void _hoops_PIPSR(_hoops_RGRSR alter * state, int weight)
{
	_hoops_HPICR("set_edge_weight\n");

	if (state->_hoops_CSC._hoops_GHRSR != weight) {
		_hoops_HPICR("\t" "setting edge weight" "\n");

		/* _hoops_HIPSR _hoops_IIPSR _hoops_CIPSR */
		float _hoops_SIPSR = (float)(weight > 0 ? weight -1 : 0);
		switch (state->_hoops_GRRSR) {
			case _hoops_CHICR: {
				_hoops_AAASR(state, _hoops_HHSCR, _hoops_HSSCR, 4);
				_hoops_RGASR(state, _hoops_SIPSR);
			}	break;

			case _hoops_SHICR: {
				Sprintf_F(state->_hoops_IGRSR, "EDGEWIDTH %f;\n",_hoops_SIPSR);
				_hoops_CSRSR(state, state->_hoops_IGRSR);
			}	break;

			default: {
				_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								  "Invalid encoding in set edge weight");
			}	break;
		}
		state->_hoops_CSC._hoops_GHRSR = weight;
	}
}

static void _hoops_GCPSR(_hoops_RGRSR alter * state, float const _hoops_CHRSR)
{
	_hoops_HPICR("set_marker_size\n");

	if (state->_hoops_CSC._hoops_CHRSR != _hoops_CHRSR) {
		_hoops_HPICR("\t" "setting marker size" "\n");

		switch (state->_hoops_GRRSR) {
			case _hoops_CHICR: {
				_hoops_AAASR(state, _hoops_HHSCR, _hoops_AISCR, 4);
				_hoops_RGASR(state, _hoops_CHRSR);
			}	break;

			case _hoops_SHICR: {
				Sprintf_F(state->_hoops_IGRSR, "MARKERSIZE %f;\n", _hoops_CHRSR);
				_hoops_CSRSR(state, state->_hoops_IGRSR);
			}	break;

			default: {
				_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									"Invalid encoding in set marker size");
			}	break;
		}
		state->_hoops_CSC._hoops_CHRSR = _hoops_CHRSR;
	}
}

static void _hoops_RCPSR(_hoops_RGRSR alter * state, unsigned short const _hoops_RHRSR)
{
	_hoops_HPICR("set_marker_symbol\n");

	if (state->_hoops_CSC._hoops_RHRSR != _hoops_RHRSR) {
		_hoops_HPICR("\t" "setting marker symbol" "\n");

		switch (state->_hoops_GRRSR) {
			case _hoops_CHICR: {
				_hoops_AAASR(state, _hoops_HHSCR, _hoops_RISCR, 2);
				_hoops_GGASR(state, _hoops_RHRSR);
			}	break;

			case _hoops_SHICR: {
				Sprintf_D(state->_hoops_IGRSR, "MARKERTYPE %d;\n", _hoops_RHRSR);
				_hoops_CSRSR(state, state->_hoops_IGRSR);
			}	break;

			default: {
				_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									"Invalid encoding in set marker symbol");
			}	break;
	}
		state->_hoops_CSC._hoops_RHRSR = _hoops_RHRSR;
	}
}

static void _hoops_ACPSR(_hoops_RGRSR alter * state, int weight)
{
	_hoops_HPICR("set_line_weight\n");

	if (state->_hoops_CSC.line_weight != weight) {
		_hoops_HPICR("\tsetting line weight\n");

		/* _hoops_HIPSR _hoops_IIPSR _hoops_CIPSR */
		float _hoops_SIPSR = (float)(weight > 0 ? weight -1 : 0);
		switch (state->_hoops_GRRSR) {
			case _hoops_CHICR: {
				_hoops_AAASR(state, _hoops_HHSCR, _hoops_SHSCR, 4);
				_hoops_RGASR(state, _hoops_SIPSR);
			}	break;

			case _hoops_SHICR: {
				Sprintf_F(state->_hoops_IGRSR, "LINEWIDTH %f;\n", _hoops_SIPSR);
				_hoops_CSRSR(state, state->_hoops_IGRSR);
			}	break;

			default: {
				_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									  "Invalid encoding in set line weight");
			}	break;
		}
		state->_hoops_CSC.line_weight = weight;
	}
}


static void
_hoops_PCPSR(_hoops_RGRSR alter * state, _hoops_HHCR const &_hoops_IHCR)
{
	_hoops_HPICR("set_clipping\n");
	if (state->_hoops_CSC._hoops_AHRSR != _hoops_IHCR->_hoops_CPA) {
		if (state->_hoops_CSC._hoops_PHRSR.left != _hoops_IHCR->_hoops_AGAA.left ||
			state->_hoops_CSC._hoops_PHRSR.right != _hoops_IHCR->_hoops_AGAA.right ||
			state->_hoops_CSC._hoops_PHRSR.bottom != _hoops_IHCR->_hoops_AGAA.bottom ||
			state->_hoops_CSC._hoops_PHRSR.top != _hoops_IHCR->_hoops_AGAA.top) {
			_hoops_HPICR("\tsetting clipping\n");
			switch (state->_hoops_GRRSR) {
				case _hoops_CHICR: {
					_hoops_AAASR(state, _hoops_CCCCR, _hoops_ASCCR, 16);
					state->points[0].x = (float) _hoops_IHCR->_hoops_AGAA.left;
					state->points[0].y = (float) _hoops_IHCR->_hoops_AGAA.bottom;
					state->points[1].x = (float) _hoops_IHCR->_hoops_AGAA.right;
					state->points[1].y = (float) _hoops_IHCR->_hoops_AGAA.top;
					_hoops_RAASR(state, state->points, 2);
					if (!state->_hoops_CSC._hoops_HHRSR) {
						_hoops_AAASR(state, _hoops_CCCCR, _hoops_PSCCR, 2);
						_hoops_GGASR(state, (unsigned short) 1);
						state->_hoops_CSC._hoops_HHRSR = true;
					}
				}	break;
				case _hoops_SHICR: {
					float _hoops_HCPSR, _hoops_ICPSR;
					_hoops_HCPSR = (float) _hoops_IHCR->_hoops_AGAA.left;
					_hoops_ICPSR = (float) _hoops_IHCR->_hoops_AGAA.bottom;
					Sprintf_FF(state->_hoops_PGRSR, "CLIPRECT (%f,%f) ",
						_hoops_HCPSR, _hoops_ICPSR);
					_hoops_HCPSR = (float) _hoops_IHCR->_hoops_AGAA.right;
					_hoops_ICPSR = (float) _hoops_IHCR->_hoops_AGAA.top;
					Sprintf_FF(state->_hoops_HGRSR, "(%f,%f);\n", _hoops_HCPSR, _hoops_ICPSR);
					Sprintf_SS(state->_hoops_IGRSR, "%s%s",
						state->_hoops_PGRSR, state->_hoops_HGRSR);
					_hoops_CSRSR(state, state->_hoops_IGRSR);
					if (!state->_hoops_CSC._hoops_HHRSR) {
						_hoops_CSRSR(state, "CLIP ON;\n");
						state->_hoops_CSC._hoops_HHRSR = true;
					}
				}	break;
				default: {
					_hoops_IPR(HEC_INTERNAL_ERROR,
						HES_PROCEDURAL_ERROR,
						"Invalid encoding in set clipping");
				}	break;
			}
			state->_hoops_CSC._hoops_PHRSR.left = _hoops_IHCR->_hoops_AGAA.left;
			state->_hoops_CSC._hoops_PHRSR.right = _hoops_IHCR->_hoops_AGAA.right;
			state->_hoops_CSC._hoops_PHRSR.bottom = _hoops_IHCR->_hoops_AGAA.bottom;
			state->_hoops_CSC._hoops_PHRSR.top = _hoops_IHCR->_hoops_AGAA.top;
		}
		state->_hoops_CSC._hoops_AHRSR = _hoops_IHCR->_hoops_CPA;
	}
}

static void
_hoops_CCPSR(_hoops_RGRSR alter * state,
			Point const *center,
			float const size)
{
	_hoops_HPICR("draw_circle\n");
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			_hoops_AAASR(state, _hoops_CGSCR, _hoops_AASCR, 12);
			state->points[0].x = center->x;
			state->points[0].y = center->y;
			_hoops_RAASR(state, state->points, 1);
			_hoops_RGASR(state, size);
		}	break;
		case _hoops_SHICR: {
			Sprintf_FF(state->_hoops_PGRSR, "CIRCLE (%f,%f),", center->x, center->y);
			Sprintf_F(state->_hoops_HGRSR, "%f;\n", size);
			Sprintf_SS(state->_hoops_IGRSR, "%s%s", state->_hoops_PGRSR, state->_hoops_HGRSR);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in draw_circle");
		}	break;
	}
}


static void
_hoops_SCPSR(_hoops_RGRSR alter * state,
			  int count,
			  DC_Point const *points)
{
	_hoops_HPICR("draw_polyline\n");
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			_hoops_AAASR(state, _hoops_CGSCR, _hoops_SGSCR, (unsigned short) (count * 8));
			if (count == 2 && points[0].x == points[1].x && points[0].y == points[1].y) {
				DC_Point _hoops_GSPSR[2];

				/* _hoops_RCICR _hoops_RSPSR _hoops_AHCA _hoops_ASPSR _hoops_PPSR _hoops_PGRC */
				_hoops_GSPSR[0].x = points[0].x;
				_hoops_GSPSR[0].y = points[0].y;
				_hoops_GSPSR[1].x = points[1].x;
				_hoops_GSPSR[1].y = points[1].y + 1.0f;
				_hoops_RAASR(state, _hoops_GSPSR, count);
			}
			else
				_hoops_RAASR(state, points, count);
		}	break;
		case _hoops_SHICR: {
			_hoops_CSRSR(state, "LINE");
			if (count == 2 && points[0].x == points[1].x && points[0].y == points[1].y) {
				DC_Point _hoops_GSPSR[2];

				/* _hoops_RCICR _hoops_RSPSR _hoops_AHCA _hoops_ASPSR _hoops_PPSR _hoops_PGRC */
				_hoops_GSPSR[0].x = points[0].x;
				_hoops_GSPSR[0].y = points[0].y;
				_hoops_GSPSR[1].x = points[1].x;
				_hoops_GSPSR[1].y = points[1].y + 1.0f;
				_hoops_RAASR(state, _hoops_GSPSR, count);
			}
			else
				_hoops_RAASR(state, points, count);
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in draw_polyline");
		}	break;
	}
}


static void
_hoops_PSPSR(_hoops_RGRSR alter * state, int count,
			   DC_Point const *points)
{
	_hoops_HPICR("draw_disjoint_polyline\n");
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			_hoops_AAASR(state, _hoops_CGSCR, _hoops_GRSCR, (unsigned short) (count * 8));
			if (count == 2 && points[0].x == points[1].x && points[0].y == points[1].y) {
				DC_Point _hoops_GSPSR[2];

				/* _hoops_RCICR _hoops_RSPSR _hoops_AHCA _hoops_ASPSR _hoops_PPSR _hoops_PGRC */
				_hoops_GSPSR[0].x = points[0].x;
				_hoops_GSPSR[0].y = points[0].y;
				_hoops_GSPSR[1].x = points[1].x;
				_hoops_GSPSR[1].y = points[1].y + 1.0f;
				_hoops_RAASR(state, _hoops_GSPSR, count);
			}
			else
				_hoops_RAASR(state, points, count);
		}	break;
		case _hoops_SHICR: {
			_hoops_CSRSR(state, "DISJTLINE");
			if (count == 2 && points[0].x == points[1].x && points[0].y == points[1].y) {
				DC_Point _hoops_GSPSR[2];

				/* _hoops_RCICR _hoops_RSPSR _hoops_AHCA _hoops_ASPSR _hoops_PPSR _hoops_PGRC */
				_hoops_GSPSR[0].x = points[0].x;
				_hoops_GSPSR[0].y = points[0].y;
				_hoops_GSPSR[1].x = points[1].x;
				_hoops_GSPSR[1].y = points[1].y + 1.0f;
				_hoops_RAASR(state, _hoops_GSPSR, count);
			}
			else
				_hoops_RAASR(state, points, count);
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in draw_disjoint_polyline");
		}	break;
	}
}


static void
_hoops_HSPSR(_hoops_RGRSR alter * state, int degree, int control_point_count,
	   DC_Point * control_points, float *knots, float start_u,
	   float end_u, float *weights)
{
	int i;
	_hoops_HPICR("draw_nurbs\n");
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			int size = 2 * (2 + 4) +
						control_point_count * (8 + 4) +
						(degree + control_point_count + 1) * 4;
			_hoops_AAASR(state, _hoops_CGSCR, _hoops_SPSCR, size);
			_hoops_GGASR(state, degree + 1);
			_hoops_GGASR(state, control_point_count);
			_hoops_RAASR(state, control_points, control_point_count);
			for (i = 0; i < degree + control_point_count + 1; ++i) {
				_hoops_RGASR(state, knots[i]);
			}
			_hoops_RGASR(state, start_u);
			_hoops_RGASR(state, end_u);
			for (i = 0; i < control_point_count; ++i) {
				_hoops_RGASR(state, weights[i]);
			}
		}	break;
		case _hoops_SHICR: {
			_hoops_CSRSR(state, "NON-UNIFORM RATIONAL B-SPLINE\n");
			Sprintf_D(state->_hoops_IGRSR, " %d,\n", degree + 1);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
			Sprintf_D(state->_hoops_IGRSR, " %d,\n", control_point_count);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
			for (i = 0; i < control_point_count; ++i) {
				Sprintf_FF(state->_hoops_IGRSR, " (%f,%f),\n", control_points[i].x, control_points[i].y);
				_hoops_CSRSR(state, state->_hoops_IGRSR);
			}
			for (i = 1; i < control_point_count + degree + 1; ++i) {
				Sprintf_F(state->_hoops_IGRSR, " %f,", knots[i]);
				_hoops_CSRSR(state, state->_hoops_IGRSR);
			}
			_hoops_CSRSR(state, "\n");
			Sprintf_FF(state->_hoops_IGRSR, " %f, %f,\n", start_u, end_u);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
			Sprintf_F(state->_hoops_IGRSR, " %f", weights[0]);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
			for (i = 1; i < control_point_count; ++i) {
				Sprintf_F(state->_hoops_IGRSR, ", %f", weights[i]);
				_hoops_CSRSR(state, state->_hoops_IGRSR);
			}
			_hoops_CSRSR(state, ";\n");
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in draw_nurbs");
		}	break;
	}
}

#ifdef _hoops_ISPSR

#define _hoops_CSPSR (unsigned short)1
#define _hoops_SSPSR (unsigned short)2

static void
_hoops_GGHSR(_hoops_RGRSR alter * state, int count, DC_Point const *points)
{
	_hoops_HPICR("draw_polybezier\n");
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			_hoops_AAASR(state, _hoops_CGSCR, _hoops_GHSCR, (unsigned short) (2 + count * 8));
			_hoops_GGASR(state, _hoops_SSPSR);
			_hoops_RAASR(state, points, count);
		}	break;
		case _hoops_SHICR: {
			_hoops_CSRSR(state, "POLYBEZIER");
			_hoops_CSRSR(state, " 1, ");	/* _hoops_RGHSR */
			_hoops_RAASR(state, points, count);
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in draw_polybezier");
		}	break;
	}
}
#endif

static void
_hoops_AGHSR(_hoops_RGRSR alter * state,
					  Point const * center,
					  Point const * _hoops_PGHSR,
					  Point const * _hoops_HGHSR)
{
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			state->points[0].x = center->x;
			state->points[0].y = center->y;

			state->points[1].x = _hoops_PGHSR->x;
			state->points[1].y = _hoops_PGHSR->y;

			state->points[2].x = _hoops_HGHSR->x;
			state->points[2].y = _hoops_HGHSR->y;

			_hoops_RAASR(state, state->points, 3);
		}	break;
		case _hoops_SHICR: {
			Sprintf_FF(state->_hoops_IGRSR, "(%f,%f)", center->x, center->y);
			Sprintf_FF(state->_hoops_HGRSR, "(%f,%f)", _hoops_PGHSR->x, _hoops_PGHSR->y);
			Sprintf_SS(state->_hoops_PGRSR, "%s%s", state->_hoops_IGRSR, state->_hoops_HGRSR);
			Sprintf_FF(state->_hoops_HGRSR, "(%f,%f)", _hoops_HGHSR->x, _hoops_HGHSR->y);
			Sprintf_SS(state->_hoops_IGRSR, "%s%s", state->_hoops_PGRSR,state->_hoops_HGRSR);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in draw_elliptical_arc");
		}	break;
	}
}

static void
_hoops_AGHSR(_hoops_RGRSR alter * state,
					  Vector const * _hoops_IGHSR,
					  Vector const * _hoops_CGHSR)
{
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			state->points[0].x = _hoops_IGHSR->x;
			state->points[0].y = _hoops_IGHSR->y;

			state->points[1].x = _hoops_CGHSR->x;
			state->points[1].y = _hoops_CGHSR->y;

			_hoops_RAASR(state, state->points, 2);
		}	break;
		case _hoops_SHICR: {
			Sprintf_FF(state->_hoops_PGRSR, "(%f,%f)", _hoops_IGHSR->x, _hoops_IGHSR->y);
			Sprintf_FF(state->_hoops_HGRSR, "(%f,%f)", _hoops_CGHSR->x, _hoops_CGHSR->y);
			Sprintf_SS(state->_hoops_IGRSR, "%s%s", state->_hoops_PGRSR,state->_hoops_HGRSR);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in draw_elliptical_arc");
		}	break;
	}
}

static void
_hoops_SGHSR(_hoops_RGRSR alter * state,
					Point const * center,
					Point const * _hoops_PGHSR,
					Point const * _hoops_HGHSR,
					Vector const * _hoops_IGHSR,
					Vector const * _hoops_CGHSR)
{

	_hoops_HPICR("draw_elliptical_arc\n");

	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			_hoops_AAASR(state, _hoops_CGSCR, _hoops_GPSCR, 5 * 8);
			_hoops_AGHSR(state, center, _hoops_PGHSR, _hoops_HGHSR);
			_hoops_AGHSR(state, _hoops_IGHSR, _hoops_CGHSR);
		}	break;
		case _hoops_SHICR: {
			_hoops_CSRSR(state, "ELLIPARC");
			_hoops_AGHSR(state, center, _hoops_PGHSR, _hoops_HGHSR);
			_hoops_AGHSR(state, _hoops_IGHSR, _hoops_CGHSR);
			_hoops_CSRSR(state, ";\n");
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in draw_elliptical_arc");
		}	break;
	}
}

static void
_hoops_GRHSR(_hoops_RGRSR alter * state,
					Point const * center,
					Point const * _hoops_PGHSR,
					Point const * _hoops_HGHSR)
{
	_hoops_HPICR("draw_ellipse\n");

	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			_hoops_AAASR(state, _hoops_CGSCR, _hoops_SASCR, 24);
			_hoops_AGHSR(state, center, _hoops_PGHSR, _hoops_HGHSR);
		}	break;
		case _hoops_SHICR: {
			_hoops_CSRSR(state, "ELLIPSE");
			_hoops_AGHSR(state, center, _hoops_PGHSR, _hoops_HGHSR);
			_hoops_CSRSR(state, ";\n");
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in draw_ellipse");
		}	break;
	}
}


static void
_hoops_RRHSR(_hoops_RGRSR alter * state, int count, DC_Point const *points)
{
	_hoops_HPICR("draw_polygon\n");
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			_hoops_AAASR(state, _hoops_CGSCR, _hoops_IRSCR, (unsigned short) (count * 8));
			_hoops_RAASR(state, points, count);
		}	break;
		case _hoops_SHICR: {
			_hoops_CSRSR(state, "POLYGON");
			_hoops_RAASR(state, points, count);
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in draw polygon");
		}	break;
	}
}


static void
_hoops_ARHSR(_hoops_RGRSR alter * state, int left, int right, int bottom,
		   int top)
{
	_hoops_HPICR("draw_rectangle\n");
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			_hoops_AAASR(state, _hoops_CGSCR, _hoops_RASCR, 16);
			state->points[0].x = (float) left;
			state->points[0].y = (float) bottom;
			state->points[1].x = (float) right;
			state->points[1].y = (float) top;
			_hoops_RAASR(state, state->points, 2);
		}	break;
		case _hoops_SHICR: {
			Sprintf_DD(state->_hoops_PGRSR, "RECT (%d,%d) ", left, top);
			Sprintf_DD(state->_hoops_HGRSR, "(%d,%d);\n", right, bottom);
			Sprintf_SS(state->_hoops_IGRSR, "%s%s", state->_hoops_PGRSR, state->_hoops_HGRSR);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in draw rectangle");
		}	break;
	}
}


static void _hoops_PRHSR(_hoops_RGRSR alter * state, int const count, DC_Point const *_hoops_HRHSR)
{
	_hoops_HPICR("draw_polydot\n");
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			_hoops_AAASR(state, _hoops_CGSCR, _hoops_RRSCR, 8 * count);
			_hoops_RAASR(state, _hoops_HRHSR, count);
		}	break;
		case _hoops_SHICR: {
			_hoops_CSRSR(state, "MARKER ");
			for (int i = 0; i < count; ++i) {
				Sprintf_FF(state->_hoops_IGRSR, "(%f,%f)", _hoops_HRHSR[i].x, _hoops_HRHSR[i].y);
				_hoops_CSRSR(state, state->_hoops_IGRSR);
			}
			_hoops_CSRSR(state, ";\n");
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in draw polydot");
		}	break;
	}
}


static void _hoops_IRHSR(_hoops_APARR alter & _hoops_RRCI);
static void _hoops_CRHSR(_hoops_APARR alter & _hoops_RRCI);
static bool start_device(Display_Context alter * dc)
{
	_hoops_HPICR("\nstart_device\n");
	_hoops_RGRSR alter *state;
	int i, _hoops_AGRSR = 0;
	_hoops_SRHSR _hoops_GAHSR = _hoops_GRRCR ("cgm");

	if (_hoops_RAHSR(_hoops_GAHSR, dc->_hoops_AAHSR->owner->name)) {
		_hoops_CRHSR(dc->_hoops_ACPGR);
		_hoops_AGRSR = 1;
	}
	else {
		_hoops_IRHSR(dc->_hoops_ACPGR);
		_hoops_AGRSR = 3;
	}

	/* _hoops_HPRGR _hoops_PAHSR - _hoops_CCPP _hoops_RH _hoops_PIAP _hoops_HRPR */
	ZALLOC(state, _hoops_RGRSR);
	state->_hoops_AGRSR = _hoops_AGRSR;
	dc->data = (void alter *) state;
	HD_Get_Bit_Patterns(dc, true);

	/* _hoops_HSPC _hoops_RH _hoops_PIAP _hoops_HRPR */
	state->fp = null;
	for (i = 0; i < _hoops_IHICR; i++) {
		state->_hoops_PGRSR[i] = state->_hoops_HGRSR[i] =
			state->_hoops_IGRSR[i] = '\0';
	}
	state->dc = dc;
	state->_hoops_SGRSR = 0;
	state->_hoops_GRRSR = _hoops_GSRSR(dc);
	if (state->_hoops_GRRSR == _hoops_GIICR) {
		state->_hoops_GRRSR = _hoops_ACRSR(dc);
	}
	//_hoops_PIAP->_hoops_HAHSR = _hoops_IAHSR;
	state->_hoops_SARSR = null;
	state->_hoops_RRRSR = 0;

	for (i = 0; i < MAX_COLORS; i++) {
		state->_hoops_CSIR[i].set = false;
		state->_hoops_CSIR[i].color._hoops_HRIR.r = 255;
		state->_hoops_CSIR[i].color._hoops_HRIR.g = 255;
		state->_hoops_CSIR[i].color._hoops_HRIR.b = 255;
		state->_hoops_CSIR[i]._hoops_GPRSR = false;
		state->_hoops_CSIR[i]._hoops_RPRSR = -1;
	}
	state->_hoops_RGRA = 0.0f;
	state->_hoops_PRRSR = true;
	state->_hoops_CSC.colors[_hoops_RCGSR] = _hoops_CAHSR::_hoops_SAHSR;
	state->_hoops_CSC.colors[_hoops_ACGSR] = _hoops_CAHSR::_hoops_SAHSR;
	state->_hoops_CSC.colors[_hoops_PCGSR] = _hoops_CAHSR::_hoops_SAHSR;
	state->_hoops_CSC.colors[_hoops_HCGSR] = _hoops_CAHSR::_hoops_SAHSR;
	state->_hoops_CSC.colors[_hoops_ICGSR] = _hoops_CAHSR::_hoops_SAHSR;

	state->_hoops_CSC.fill_style = -1;
	state->_hoops_CSC._hoops_APRSR = -1;

	state->_hoops_CSC._hoops_PPRSR = -1;
	state->_hoops_CSC._hoops_HPRSR = -1;
	state->_hoops_CSC.line_join = -1;
	state->_hoops_CSC.line_weight = -1;

	state->_hoops_CSC._hoops_IPRSR = -1;
	state->_hoops_CSC._hoops_CPRSR = -1;
	state->_hoops_CSC._hoops_SPRSR = -1;
	state->_hoops_CSC._hoops_GHRSR = -1;
	state->_hoops_CSC._hoops_IHRSR = false;

	state->_hoops_CSC._hoops_RHRSR = 0xffff;
	state->_hoops_CSC._hoops_CHRSR = -1;

	state->_hoops_CSC._hoops_AHRSR = (_hoops_GARRR) - 1;
	state->_hoops_CSC._hoops_HHRSR = false;
	state->text._hoops_SHRSR = -1.0f;
	state->text._hoops_GIRSR = 0;
	state->text._hoops_RIRSR = 0;
	state->text._hoops_AIRSR = 0;
	state->text.rotation = 0;
	state->_hoops_HIRSR = 0.0f;
		state->_hoops_HRRSR = false;
	state->_hoops_ARRSR = 0;
	for (i = 0; i < 3; i++) {
		state->points[i].x = state->points[i].y = state->points[i].z = 0.0f;
	}

	/* _hoops_IGS _hoops_RH _hoops_CHIA _hoops_RGHR _hoops_IH _hoops_IIPR */
	if (_hoops_IIASR(state, dc))
		return true;
	else {
		_hoops_SGSPR(HEC_CGM_DRIVER, HES_FILE_OPEN, "Unable to open CGM3 output file");
		FREE(state, _hoops_RGRSR);
		dc->data = null;
		return false;
	}
}


static void stop_device(Display_Context alter * dc)
{
	_hoops_RGRSR alter *state = _hoops_GCRSR(dc);
	_hoops_HPICR("\nstop_device\n");
	_hoops_IAPSR(state);
	_hoops_HSRSR(state);
	FREE(state, _hoops_RGRSR);
	dc->data = null;
}


static void _hoops_GPHSR(Net_Rendition const &nr, int left, int right,
		  int bottom, int top)
{
	_hoops_HPICR("\n" "draw_no_rectangle" "\n");
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;

	/*
	* _hoops_RH _hoops_RPHSR _hoops_PRGGR _hoops_IIGR _hoops_RH _hoops_ARRGR _hoops_HRGR _hoops_HAR _hoops_SIGR
	* _hoops_CR _hoops_RH _hoops_IGHP _hoops_HAIR _hoops_HRGR _hoops_AIAH _hoops_ARP
	*/

	/* _hoops_APHSR _hoops_RH _hoops_RPHSR _hoops_CCA _hoops_IRS _hoops_IIPH _hoops_HSSP _hoops_RPP _hoops_HAHH */
	if (_hoops_SIGA->pattern != FP_SOLID) {
		_hoops_HHCR const &_hoops_IHCR = nr->transform_rendition;
		Display_Context const *dc = nr->_hoops_SRA;
		_hoops_RGRSR alter *state = _hoops_GCRSR(dc);
		_hoops_PCPSR(state, _hoops_IHCR);
		_hoops_CSASR(state, FILL_COLOR, &_hoops_SIGA->contrast_color);
		_hoops_AHPSR(state, dc, _hoops_SIGA->pattern);
		_hoops_ARHSR(state, left, right, bottom, top);
	}
}

static void get_physical_info(Display_Context alter * dc)
{
	_hoops_RGRSR alter *state = _hoops_GCRSR(dc);
	float _hoops_PPHSR, _hoops_HIRSR, _hoops_HPHSR, _hoops_IPHSR;
	_hoops_HPICR("\nget_physical_info\n");

	/* _hoops_CGIC _hoops_CPHSR _hoops_IGIR _hoops_IIGR _hoops_SISS _hoops_GGR _hoops_SAPSR */
	if (dc->options._hoops_SPHSR.x == -1) {
		dc->_hoops_PGCC.size.x = 8.5f * 2.54f;
		dc->_hoops_PGCC.size.y = 11.0f * 2.54f;
	}
	else {
		dc->_hoops_PGCC.size.x = dc->options._hoops_SPHSR.x;
		dc->_hoops_PGCC.size.y = dc->options._hoops_SPHSR.y;
	}
	_hoops_HPHSR = dc->_hoops_PGCC.size.x;
	_hoops_IPHSR = dc->_hoops_PGCC.size.y;

	/* _hoops_SGH _hoops_GAR _hoops_AHPH _hoops_ASPA _hoops_GAR _hoops_SSRR */
	_hoops_PPHSR = (float) _hoops_AHIA(32000.0f, dc->options._hoops_GHHSR / 2.54f * _hoops_IAAA(_hoops_HPHSR, _hoops_IPHSR));

	/*
	* _hoops_RHHSR _hoops_HSIH _hoops_AHHSR _hoops_PPR _hoops_PHHSR _hoops_GGSR _hoops_IS _hoops_GAR _hoops_AHPH _hoops_ASPA _hoops_GAR
	* _hoops_SSRR
	*/
	_hoops_HIRSR = (float) FLOOR(_hoops_PPHSR / _hoops_IAAA(_hoops_HPHSR, _hoops_IPHSR));
	dc->_hoops_PGCC._hoops_PRPSR.x = (int) FLOOR(_hoops_HIRSR * _hoops_HPHSR);
	dc->_hoops_PGCC._hoops_PRPSR.y = (int) FLOOR(_hoops_HIRSR * _hoops_IPHSR);
	state->_hoops_HIRSR = _hoops_HIRSR;

	/* #11903 _hoops_RGAR _hoops_ARP _hoops_SHIR _hoops_III _hoops_SGCR _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_IPPSR _hoops_III _hoops_SGCR. */
	if (!dc->options._hoops_HHHSR)
		dc->_hoops_PGCC._hoops_IHHSR = dc->options._hoops_GHHSR/150.0f;

	/* _hoops_GHGPR _hoops_RHGPR _hoops_HRGR _hoops_HAR _hoops_SAGH */
	dc->_hoops_PGCC._hoops_CHHSR = _hoops_SHHSR;

	/* _hoops_HHCI _hoops_IHIS _hoops_HRGR _hoops_HAR _hoops_SAGH */
	dc->_hoops_PGCC.flags |= _hoops_GIHSR;

	/*
	* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_RIHSR _hoops_SR'_hoops_ASAR _hoops_GHGA _hoops_PPPSR _hoops_AIHSR. */
	dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;
	state->_hoops_CRRSR = false;
	if (state->_hoops_AGRSR == 1) {
		/* _hoops_HGSR _hoops_GAR _hoops_IIHSR _hoops_HCCPR _hoops_CIHSR _hoops_IS _hoops_AA _hoops_IAII */
		if (BIT(dc->options._hoops_IRARR, _hoops_CPICR)) {
			dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;
			state->_hoops_CRRSR = false;
		}
		else {
			dc->_hoops_PGCC._hoops_AAPSR = MAX_COLORS;
			dc->_hoops_PGCC._hoops_PIHSR = _hoops_SIHSR;
			state->_hoops_CRRSR = true;
			if (dc->options._hoops_GCHSR != 0L)
				HE_WARNING(HEC_CGM_DRIVER, HES_WINDOW_ID_REPLACED,
				"'use window ID' was replaced by 'use colormap ID'");

			/* _hoops_CGIC _hoops_RPP _hoops_RH _hoops_IPSP _hoops_APSI _hoops_IS _hoops_ARP _hoops_HPASR _hoops_HAII _hoops_SIA */
			if (dc->options._hoops_RCHSR == 0L)
				state->_hoops_SRRSR = false;
			else {
				state->_hoops_SRRSR = true;
				state->_hoops_SARSR =
					(_hoops_SSGSR alter *) dc->options._hoops_RCHSR;

				/* _hoops_CACH _hoops_RPP _hoops_ACHSR _hoops_PSHA _hoops_CGH _hoops_ARCR _hoops_IS _hoops_RCICR _hoops_CIHA 1 */
				if (BIT(dc->options._hoops_IRARR, _hoops_AHICR))
					state->_hoops_IRRSR = true;
				else
					state->_hoops_IRRSR = false;
			}
		}
		if (dc->options._hoops_AAPSR == 64)
			dc->_hoops_PGCC._hoops_PCHSR = 64;
		else
			dc->_hoops_PGCC._hoops_PCHSR = 256;

		/* _hoops_HGSR _hoops_GAR _hoops_HCHSR _hoops_SRHR _hoops_HCCPR _hoops_CIHSR _hoops_IS _hoops_AA _hoops_IAII */
		if (BIT(dc->options._hoops_IRARR, _hoops_SPICR)) {
			state->_hoops_HRRSR = true;
			dc->_hoops_PGCC._hoops_ICHSR = "pen plotter";
				dc->_hoops_ACPGR->draw_dc_rectangle = _hoops_GPHSR;
		}
		else {
			state->_hoops_HRRSR = false;
			dc->_hoops_PGCC._hoops_ICHSR = "frame buffer";
		}
	}
	dc->_hoops_PGCC.flags |= _hoops_CCHSR;

	/* _hoops_PIAAR _hoops_RH _hoops_RHPP _hoops_PPR _hoops_RH _hoops_ACSP _hoops_IIGR _hoops_RH _hoops_HPRGR _hoops_CIPH */
	dc->_hoops_PGCC.driver_type = "CGM3";
	dc->_hoops_PGCC._hoops_SCHSR = "$Revision: 1.152 $";

	/* _hoops_HGSR _hoops_GAR _hoops_HCHSR _hoops_SRHR _hoops_HCCPR _hoops_CIHSR _hoops_IS _hoops_AA _hoops_IAII */
	/* _hoops_CACH _hoops_RPP _hoops_RH _hoops_IPSP _hoops_HGRC _hoops_SAAA */
	if (BIT(dc->options._hoops_IRARR, _hoops_GHICR)) {
		state->_hoops_RGRA = dc->options._hoops_GSHSR;
	}
	else {
		state->_hoops_RGRA = 1.0f;
	}
	dc->_hoops_PGCC.flags &= ~_hoops_RSHSR;
	dc->_hoops_PGCC._hoops_ASHSR = 0;
	dc->_hoops_PGCC.flags &= ~_hoops_PSHSR;
	dc->_hoops_PGCC.flags &= ~_hoops_HSHSR;
	dc->_hoops_PGCC.flags |= _hoops_ISHSR;
	dc->flags |= _hoops_CSHSR;
	dc->_hoops_PGCC.flags |= _hoops_GIHSR;
	dc->_hoops_PGCC._hoops_CHHSR = _hoops_SHHSR;

	/* _hoops_GA'_hoops_RA _hoops_GGSP _hoops_HIS _hoops_SSHSR _hoops_IIGR _hoops_SGH _hoops_HGIR _hoops_RCC _hoops_HGCR _hoops_SSSHR _hoops_HSH */
	dc->_hoops_PGCC.flags &= ~_hoops_GGISR;
}

/*
 * _hoops_SSHSR _hoops_PAH _hoops_PRPS _hoops_RPP _hoops_SSIA _hoops_HHGC _hoops_IS _hoops_SGH _hoops_RH _hoops_SISS'_hoops_GRI _hoops_III _hoops_PAIA
 * _hoops_PAR _hoops_HS _hoops_AGAH _hoops_RGISR _hoops_CGSI _hoops_GGSR (_hoops_IH _hoops_AGISR _hoops_PPR _hoops_PGISR)
 */
static void draw_dc_polyline(Net_Rendition const &nr, int count,
				 DC_Point const *points);

/* _hoops_HGI _hoops_API _hoops_SAGGR _hoops_RH _hoops_AAP _hoops_HII _hoops_AGAH _hoops_IH _hoops_IGIR, _hoops_HGISR _hoops_RH _hoops_RHPP'_hoops_GRI _hoops_IGIR
 * _hoops_PPR _hoops_IGISR _hoops_GGR _hoops_RH _hoops_HSH _hoops_GGR _hoops_SCGR _hoops_HIS _hoops_AGAH _hoops_CGISR _hoops_PCPA _hoops_IGIR _hoops_SR _hoops_IGRC _hoops_ARP. */
local void
_hoops_SGISR(Display_Context alter * dc)
{
	//_hoops_GRISR *_hoops_PIAP = _hoops_RRISR(_hoops_CSPH);

	float _hoops_HAP = dc->options._hoops_GHHSR;
		float width, height;

	if (dc->options._hoops_SPHSR.x != -1) {
		width = (72 * dc->options._hoops_SPHSR.x / 2.54f);
		height = (72 * dc->options._hoops_SPHSR.y / 2.54f);
	}
	else {
		width = (72 * dc->_hoops_PGCC.size.x / 2.54f);
		height = (72 * dc->_hoops_PGCC.size.y / 2.54f);
	}

	dc->current._hoops_HAP.x = _hoops_HAP / 2.54f;
	dc->current._hoops_HAP.y = _hoops_HAP / 2.54f;
	dc->current._hoops_PRPSR.x = (int) (_hoops_HAP * width / 72.0f);
	dc->current._hoops_PRPSR.y = (int) (_hoops_HAP * height / 72.0f);

	dc->current._hoops_ARISR.x = dc->_hoops_PGCC._hoops_ARISR.x;
	dc->current._hoops_ARISR.y = dc->_hoops_PGCC._hoops_ARISR.y;
	dc->current.size.x = dc->_hoops_PGCC.size.x;
	dc->current.size.y = dc->_hoops_PGCC.size.y;

	return;
}

static void get_current_info(Display_Context alter * dc)
{
	_hoops_HPICR("\nget_current_info\n");
	_hoops_SGISR(dc);
}


static void _hoops_PRISR(_hoops_RGRSR alter * state, Net_Rendition const &nr)
{

	int	i;
	unsigned char	_hoops_RPRSR;
	int	_hoops_CAASR,
		_hoops_HRISR,
		_hoops_SAASR;
	_hoops_GARSR background = nr->_hoops_SAIR->_hoops_GPIR._hoops_PGGCR;

	_hoops_HPICR ("add_matching_color_map\n");

	/* _hoops_CGIC _hoops_CGGPR _hoops_PPR _hoops_AHPA _hoops_IGI _hoops_HPP _hoops_IRISR */
	_hoops_CAASR = 0;
	while (!state->_hoops_CSIR[_hoops_CAASR].set)
		_hoops_CAASR++;
	_hoops_HRISR = _hoops_CAASR;
	_hoops_SAASR = MAX_COLORS - 1;
	while (!state->_hoops_CSIR[_hoops_SAASR].set)
		_hoops_SAASR--;

	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			int		_hoops_RRRSR;

			if (state->_hoops_HRRSR) {
				/* _hoops_PIHA _hoops_HSPP _hoops_HPGR 0 _hoops_HIS _hoops_GHASR _hoops_SPASR */
				_hoops_CAASR = 0;
				_hoops_RPRSR = (unsigned char)_hoops_CAASR;

				/* _hoops_IHASR _hoops_CHASR _hoops_SHASR _hoops_GIASR 0 */
				_hoops_RRRSR = _hoops_SAASR + 1;
				_hoops_AAASR (state, _hoops_HHSCR, _hoops_RGGSR,
										(unsigned short)(1 + (_hoops_RRRSR * 3)));
				_hoops_ISRSR (state, _hoops_RPRSR);

				/* _hoops_HHSA _hoops_RH 0_hoops_CRISR _hoops_RARP _hoops_IS _hoops_SHH _hoops_RH _hoops_IGHP _hoops_HAIR */
				_hoops_ISRSR (state, state->_hoops_CSIR[background].color._hoops_HRIR.r);
				_hoops_ISRSR (state, state->_hoops_CSIR[background].color._hoops_HRIR.g);
				_hoops_ISRSR (state, state->_hoops_CSIR[background].color._hoops_HRIR.b);

				/* _hoops_HPPP _hoops_SAHR _hoops_PII _hoops_RH _hoops_HAPR */
				if (_hoops_HRISR == 0) {
					state->_hoops_CSIR[0]._hoops_RPRSR = _hoops_RPRSR++;
					state->_hoops_CSIR[0]._hoops_GPRSR = true;
				}

				/* _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RPP _hoops_IIH _hoops_HRGR _hoops_SRISR */
				if (_hoops_HRISR == 0 &&
					(state->_hoops_CSIR[0].color._hoops_HRIR.r != state->_hoops_CSIR[background].color._hoops_HRIR.r ||
					state->_hoops_CSIR[0].color._hoops_HRIR.g != state->_hoops_CSIR[background].color._hoops_HRIR.g ||
					state->_hoops_CSIR[0].color._hoops_HRIR.b != state->_hoops_CSIR[background].color._hoops_HRIR.b))
					HE_ERROR2 (HEC_CGM_DRIVER, HES_COLOR_INDEX_IGNORED,
								"Color map 0 RGB values do not match background",
								"color and will be ignored");

				/* _hoops_PH _hoops_GH _hoops_GAISR _hoops_IS 1 _hoops_CR _hoops_SR _hoops_RAISR _hoops_RH 0_hoops_CRISR _hoops_RARP */
				_hoops_CAASR++;
			}
			else {
				/* _hoops_HSPP _hoops_HPGR 0 _hoops_PAR 1 */
				_hoops_RPRSR = (unsigned char)_hoops_CAASR;

				/* _hoops_IHASR _hoops_CHASR _hoops_SHASR _hoops_GIASR _hoops_PGGIR */
				_hoops_RRRSR = _hoops_SAASR - _hoops_CAASR + 1;
				_hoops_AAASR (state, _hoops_HHSCR, _hoops_RGGSR,
										(unsigned short)(1 + (_hoops_RRRSR * 3)));
				_hoops_ISRSR (state, _hoops_RPRSR);
			}

			/* _hoops_RCSPR _hoops_PGGIR _hoops_IHASR _hoops_RIASR _hoops_AIASR */
			for (i = _hoops_CAASR; i <= _hoops_SAASR; i++) {
				if (state->_hoops_CSIR[i].set) {
					/* _hoops_CR _hoops_SCH'_hoops_GRI _hoops_ARP, _hoops_GGCR _hoops_SCH _hoops_IS _hoops_RH _hoops_RGHR */
					_hoops_ISRSR (state, state->_hoops_CSIR[i].color._hoops_HRIR.r);
					_hoops_ISRSR (state, state->_hoops_CSIR[i].color._hoops_HRIR.g);
					_hoops_ISRSR (state, state->_hoops_CSIR[i].color._hoops_HRIR.b);

					/* _hoops_PRIA _hoops_SCH'_hoops_GRI _hoops_AHC _hoops_GGR _hoops_RH _hoops_RCICR _hoops_HIGR */
					state->_hoops_CSIR[i]._hoops_RPRSR = _hoops_RPRSR++;
					state->_hoops_CSIR[i]._hoops_GPRSR = true;
				}
				else {
					/* _hoops_GGCR _hoops_IRS _hoops_SPCS _hoops_RARP _hoops_IS _hoops_CISA _hoops_RH _hoops_CSRR */
					_hoops_ISRSR (state, (unsigned char)0);
					_hoops_ISRSR (state, (unsigned char)0);
					_hoops_ISRSR (state, _hoops_RPRSR);
					_hoops_RPRSR++;
				}
			}
			if (_hoops_RRRSR % 2 == 0)
				_hoops_ISRSR (state, (unsigned char)0);
		}	break;

		case _hoops_SHICR: {
			if (state->_hoops_HRRSR) {
				/* _hoops_PIHA _hoops_HSPP _hoops_HPGR 0 _hoops_HIS _hoops_GHASR _hoops_SPASR */
				_hoops_CAASR = 0;
				_hoops_RPRSR = (unsigned char)_hoops_CAASR;

				/* _hoops_IHASR _hoops_CHASR _hoops_SHASR _hoops_GIASR 0 */
				Sprintf_D (state->_hoops_IGRSR, "COLRTABLE %d", (int)_hoops_RPRSR);
				_hoops_CSRSR (state, state->_hoops_IGRSR);

				/* _hoops_HHSA _hoops_RH 0_hoops_CRISR _hoops_RARP _hoops_IS _hoops_SHH _hoops_RH _hoops_IGHP _hoops_HAIR */
				Sprintf_DD (state->_hoops_PGRSR, "\n (%d,%d,",
							(int)state->_hoops_CSIR[background].color._hoops_HRIR.r,
							(int)state->_hoops_CSIR[background].color._hoops_HRIR.g);
				Sprintf_SD (state->_hoops_IGRSR, "%s%d)",
							state->_hoops_PGRSR,
							(int)state->_hoops_CSIR[background].color._hoops_HRIR.b);
				_hoops_CSRSR (state, state->_hoops_IGRSR);

				/* _hoops_HPPP _hoops_SAHR _hoops_PII _hoops_RH _hoops_HAPR */
				if (_hoops_HRISR == 0) {
					state->_hoops_CSIR[0]._hoops_RPRSR = _hoops_RPRSR++;
					state->_hoops_CSIR[0]._hoops_GPRSR = true;
				}

				/* _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RPP _hoops_IIH _hoops_HRGR _hoops_SRISR */
				if (_hoops_HRISR == 0 &&
					(state->_hoops_CSIR[0].color._hoops_HRIR.r != state->_hoops_CSIR[background].color._hoops_HRIR.r ||
					state->_hoops_CSIR[0].color._hoops_HRIR.g != state->_hoops_CSIR[background].color._hoops_HRIR.g ||
					state->_hoops_CSIR[0].color._hoops_HRIR.b != state->_hoops_CSIR[background].color._hoops_HRIR.b))
					HE_ERROR2 (HEC_CGM_DRIVER, HES_COLOR_INDEX_IGNORED,
								"Color map 0 RGB values do not match background",
								"color and will be ignored");

				/* _hoops_PH _hoops_GH _hoops_GAISR _hoops_IS 1 _hoops_CR _hoops_SR _hoops_RAISR _hoops_RH 0_hoops_CRISR _hoops_RARP */
				_hoops_CAASR++;
			}
			else {
				_hoops_RPRSR = (unsigned char)_hoops_CAASR;

				/* _hoops_IHASR _hoops_CHASR _hoops_SHASR _hoops_GIASR _hoops_PGGIR */
				Sprintf_D (state->_hoops_IGRSR, "COLRTABLE %d", (int)_hoops_RPRSR);
				_hoops_CSRSR (state, state->_hoops_IGRSR);
			}

			/* _hoops_RCSPR _hoops_PGGIR _hoops_IHASR _hoops_RIASR _hoops_AIASR */
			for (i = _hoops_CAASR; i <= _hoops_SAASR; i++) {
				if (state->_hoops_CSIR[i].set) {
					/* _hoops_CR _hoops_SCH'_hoops_GRI _hoops_ARP, _hoops_GGCR _hoops_SCH _hoops_IS _hoops_RH _hoops_RGHR */
					Sprintf_DD (state->_hoops_PGRSR, "\n (%d,%d,",
								(int)state->_hoops_CSIR[i].color._hoops_HRIR.r,
								(int)state->_hoops_CSIR[i].color._hoops_HRIR.g);
					Sprintf_SD (state->_hoops_IGRSR, "%s%d)",
								state->_hoops_PGRSR,
								(int)state->_hoops_CSIR[i].color._hoops_HRIR.b);
					_hoops_CSRSR (state, state->_hoops_IGRSR);

					/* _hoops_PRIA _hoops_SCH'_hoops_GRI _hoops_AHC _hoops_GGR _hoops_RH _hoops_RCICR _hoops_HIGR */
					state->_hoops_CSIR[i]._hoops_RPRSR = _hoops_RPRSR++;
					state->_hoops_CSIR[i]._hoops_GPRSR = true;
				}
				else {
					/* _hoops_GGCR _hoops_IRS _hoops_SPCS _hoops_RARP */
					Sprintf_D (state->_hoops_IGRSR, "\n (0,0,%d)", (int)_hoops_RPRSR);
					_hoops_CSRSR (state, state->_hoops_IGRSR);

					_hoops_RPRSR++;
				}
			}
			_hoops_CSRSR (state, ";\n");
		}	break;

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in add matching color map");
		}	break;
	}
}

static void _hoops_AAISR(_hoops_RGRSR alter * state, Net_Rendition const &nr)
{

	Display_Context const * dc = nr->_hoops_SRA;
	int i;
	unsigned char _hoops_RPRSR;
	_hoops_GARSR background = nr->_hoops_SAIR->_hoops_GPIR._hoops_PGGCR;

	_hoops_HPICR ("add_derived_color_map\n");

	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			if (state->_hoops_HRRSR) {
				/* _hoops_PIHA _hoops_HSPP _hoops_HPGR 0 _hoops_HIS _hoops_GHASR _hoops_SPASR */
				_hoops_RPRSR = (unsigned char)0;

				/* _hoops_IHASR _hoops_CHASR _hoops_SHASR _hoops_GIASR 0 */
				_hoops_AAASR (state, _hoops_HHSCR, _hoops_RGGSR,
										(unsigned short)(1 + (state->_hoops_RRRSR * 3)));
				_hoops_ISRSR (state, _hoops_RPRSR);

				/* _hoops_HHSA _hoops_RH 0_hoops_CRISR _hoops_RARP _hoops_IS _hoops_SHH _hoops_RH _hoops_IGHP _hoops_HAIR */
				_hoops_ISRSR (state, state->_hoops_CSIR[background].color._hoops_HRIR.r);
				_hoops_ISRSR (state, state->_hoops_CSIR[background].color._hoops_HRIR.g);
				_hoops_ISRSR (state, state->_hoops_CSIR[background].color._hoops_HRIR.b);

				/* _hoops_HPPP _hoops_SAHR _hoops_PII _hoops_RH _hoops_HAPR, _hoops_ARP _hoops_HIS _hoops_SCH'_hoops_GRI _hoops_HPSH */
				state->_hoops_CSIR[background]._hoops_RPRSR = _hoops_RPRSR++;
				state->_hoops_CSIR[background]._hoops_GPRSR = true;
				state->_hoops_CSIR[background].set = false;
			}
			else {
				/* _hoops_HSPP _hoops_HPGR 0 _hoops_PAR 1 */
				_hoops_RPRSR = (unsigned char)dc->_hoops_PGCC._hoops_APASR;

				/* _hoops_IHASR _hoops_CHASR _hoops_SHASR _hoops_GIASR _hoops_PGGIR */
				_hoops_AAASR (state, _hoops_HHSCR, _hoops_RGGSR,
										(unsigned short)(1 + (state->_hoops_RRRSR * 3)));
				_hoops_ISRSR (state, _hoops_RPRSR);
			}

			/* _hoops_RCSPR _hoops_PGGIR _hoops_IHASR _hoops_RIASR _hoops_AIASR */
			for (i = 0; i < MAX_COLORS; i++) {
				if (state->_hoops_CSIR[i].set) {
					/* _hoops_CR _hoops_SCH'_hoops_GRI _hoops_ARP, _hoops_GGCR _hoops_SCH _hoops_IS _hoops_RH _hoops_RGHR */
					_hoops_ISRSR (state, state->_hoops_CSIR[i].color._hoops_HRIR.r);
					_hoops_ISRSR (state, state->_hoops_CSIR[i].color._hoops_HRIR.g);
					_hoops_ISRSR (state, state->_hoops_CSIR[i].color._hoops_HRIR.b);

					/* _hoops_PRIA _hoops_SCH'_hoops_GRI _hoops_AHC _hoops_GGR _hoops_RH _hoops_RCICR _hoops_HIGR */
					state->_hoops_CSIR[i]._hoops_RPRSR = _hoops_RPRSR++;
					state->_hoops_CSIR[i]._hoops_GPRSR = true;
				}
				if (state->_hoops_RRRSR % 2 == 0)
					_hoops_ISRSR (state, (unsigned char)0);

				if (state->_hoops_HRRSR) {
					/* _hoops_PAISR _hoops_RH _hoops_GRH _hoops_HAISR _hoops_IAISR _hoops_IIGR _hoops_RH _hoops_HAPR */
					state->_hoops_CSIR[background].set = true;
				}
			}
		}	break;

		case _hoops_SHICR: {
			if (state->_hoops_HRRSR) {
				/* _hoops_PIHA _hoops_HSPP _hoops_HPGR 0 _hoops_HIS _hoops_GHASR _hoops_SPASR */
				_hoops_RPRSR = (unsigned char)0;

				/* _hoops_IHASR _hoops_CHASR _hoops_SHASR _hoops_GIASR 0 */
				Sprintf_D (state->_hoops_IGRSR, "COLRTABLE %d", (int)_hoops_RPRSR);
				_hoops_CSRSR (state, state->_hoops_IGRSR);

				/* _hoops_HHSA _hoops_RH 0_hoops_CRISR _hoops_RARP _hoops_IS _hoops_SHH _hoops_RH _hoops_IGHP _hoops_HAIR */
				Sprintf_DD (state->_hoops_PGRSR, "\n (%d,%d,",
							(int)state->_hoops_CSIR[background].color._hoops_HRIR.r,
							(int)state->_hoops_CSIR[background].color._hoops_HRIR.g);
				Sprintf_SD (state->_hoops_IGRSR, "%s%d)",
							state->_hoops_PGRSR,
							(int)state->_hoops_CSIR[background].color._hoops_HRIR.b);
				_hoops_CSRSR (state, state->_hoops_IGRSR);

				/* _hoops_HPPP _hoops_SAHR _hoops_PII _hoops_RH _hoops_HAPR, _hoops_ARP _hoops_HIS _hoops_SCH'_hoops_GRI _hoops_HPSH */
				state->_hoops_CSIR[background]._hoops_RPRSR = _hoops_RPRSR++;
				state->_hoops_CSIR[background]._hoops_GPRSR = true;
				state->_hoops_CSIR[background].set = false;
			}
			else {
				/* _hoops_HSPP _hoops_HPGR 0 _hoops_PAR 1 */
				_hoops_RPRSR = (unsigned char)dc->_hoops_PGCC._hoops_APASR;

				/* _hoops_IHASR _hoops_CHASR _hoops_SHASR _hoops_GIASR _hoops_PGGIR */
				Sprintf_D (state->_hoops_IGRSR, "COLRTABLE %d", (int)_hoops_RPRSR);
				_hoops_CSRSR (state, state->_hoops_IGRSR);
			}

			/* _hoops_RCSPR _hoops_PGGIR _hoops_IHASR _hoops_RIASR _hoops_AIASR */
			for (i = 0; i < MAX_COLORS; i++) {
				if (state->_hoops_CSIR[i].set) {
					/* _hoops_CR _hoops_SCH'_hoops_GRI _hoops_ARP, _hoops_GGCR _hoops_SCH _hoops_IS _hoops_RH _hoops_RGHR */
					Sprintf_DD (state->_hoops_PGRSR,
						"\n (%d,%d,",
						(int)state->_hoops_CSIR[i].color._hoops_HRIR.r,
						(int)state->_hoops_CSIR[i].color._hoops_HRIR.g);
					Sprintf_SD (state->_hoops_IGRSR,
						"%s%d)",
						state->_hoops_PGRSR,
						(int)state->_hoops_CSIR[i].color._hoops_HRIR.b);
					_hoops_CSRSR (state, state->_hoops_IGRSR);

					/* _hoops_PRIA _hoops_SCH'_hoops_GRI _hoops_AHC _hoops_GGR _hoops_RH _hoops_RCICR _hoops_HIGR */
					state->_hoops_CSIR[i]._hoops_RPRSR = _hoops_RPRSR++;
					state->_hoops_CSIR[i]._hoops_GPRSR = true;
				}
				_hoops_CSRSR (state, ";\n");

				if (state->_hoops_HRRSR) {
					/* _hoops_PAISR _hoops_RH _hoops_GRH _hoops_HAISR _hoops_IAISR _hoops_IIGR _hoops_RH _hoops_HAPR */
					state->_hoops_CSIR[background].set = true;
				}
			}
		}	break;

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in add derived color map");
		}	break;
	}
}

static void _hoops_CAISR(_hoops_RGRSR alter * state)
{
	register	int				i;

	for (i = 0; i < MAX_COLORS; i++) {
		if (state->_hoops_CSIR[i].set && !state->_hoops_CSIR[i]._hoops_GPRSR) {
			Sprintf_DD (state->_hoops_HGRSR, "missing: color map %d is (%d, ",
						i, (int)state->_hoops_CSIR[i].color._hoops_HRIR.r);
			Sprintf_SD (state->_hoops_PGRSR, "%s%d, ",
						state->_hoops_HGRSR,
						(int)state->_hoops_CSIR[i].color._hoops_HRIR.g);
			Sprintf_DD (state->_hoops_HGRSR, "%d) for %d",
						(int)state->_hoops_CSIR[i].color._hoops_HRIR.b,
						(int)state->_hoops_CSIR[i]._hoops_RPRSR);
			Sprintf_SS (state->_hoops_IGRSR, "%s%s",
						state->_hoops_PGRSR,
						state->_hoops_HGRSR);
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   state->_hoops_IGRSR);
		}
		else if (!state->_hoops_CSIR[i].set && state->_hoops_CSIR[i]._hoops_GPRSR) {
			Sprintf_DD (state->_hoops_HGRSR, "extra: color map %d is (%d, ",
						i, (int)state->_hoops_CSIR[i].color._hoops_HRIR.r);
			Sprintf_SD (state->_hoops_PGRSR, "%s%d, ",
						state->_hoops_HGRSR,
						(int)state->_hoops_CSIR[i].color._hoops_HRIR.g);
			Sprintf_DD (state->_hoops_HGRSR, "%d) for %d",
						(int)state->_hoops_CSIR[i].color._hoops_HRIR.b,
						(int)state->_hoops_CSIR[i]._hoops_RPRSR);
			Sprintf_SS (state->_hoops_IGRSR, "%s%s",
						state->_hoops_PGRSR,
						state->_hoops_HGRSR);
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   state->_hoops_IGRSR);
		}
	}
}

static void init_picture(Net_Rendition const &nr)
{
	Display_Context const *dc = nr->_hoops_SRA;
	_hoops_RGRSR alter *state = _hoops_GCRSR(dc);
	_hoops_HPICR("\ninit picture\n");
	if (!BIT(dc->flags, _hoops_SAISR))
		return;

	/* _hoops_GGCR _hoops_SCIA _hoops_APGR _hoops_IIGR _hoops_RGHR _hoops_GPP _hoops_SRS _hoops_PAAP */
	if (state->_hoops_SGRSR == 0)
		_hoops_SGPSR(state, nr);

	/* _hoops_GPISR _hoops_RH _hoops_RPISR _hoops_PHI _hoops_ARP _hoops_IS 0 _hoops_GGR _hoops_APISR */
	state->_hoops_SGRSR++;

	/* _hoops_GGCR _hoops_APGR _hoops_IS _hoops_PPIP _hoops_IRS _hoops_CCAH _hoops_RPISR */
	_hoops_CAPSR(state);
	if (state->_hoops_CRRSR) {
		if (state->_hoops_SRRSR)
			/* _hoops_GGCR _hoops_HAIR _hoops_ARCR _hoops_AIRP _hoops_IS _hoops_PSSP _hoops_PPISR _hoops_CARSR _hoops_HPP _hoops_IPSP */
			_hoops_IAASR(state, nr);
		else if (state->_hoops_ARRSR)
			/* _hoops_GGCR _hoops_HAIR _hoops_ARCR _hoops_AIRP _hoops_HPISR _hoops_HPP _hoops_ARP _hoops_SISS _hoops_HAIR _hoops_ARCR */
			/* _hoops_HIH _hoops_GRP _hoops_RH _hoops_CIHA _hoops_HSH _hoops_IGI _hoops_HPP _hoops_IRISR */
			_hoops_PRISR(state, nr);
		else
			/* _hoops_GGCR _hoops_HAIR _hoops_ARCR _hoops_AIRP _hoops_HPISR _hoops_HPP _hoops_ARP _hoops_SISS _hoops_HAIR _hoops_ARCR */
			_hoops_AAISR(state, nr);
		_hoops_CAISR(state);
	}

	/* _hoops_HHSPR _hoops_GPP _hoops_ASCA _hoops_AIRC _hoops_CR _hoops_SSIA _hoops_HSPC _hoops_CCA _hoops_GRR _hoops_RPISR */
	state->_hoops_PRRSR = true;
	state->_hoops_CSC.colors[_hoops_RCGSR] = _hoops_CAHSR::_hoops_SAHSR;
	state->_hoops_CSC.colors[_hoops_ACGSR] = _hoops_CAHSR::_hoops_SAHSR;
	state->_hoops_CSC.colors[_hoops_PCGSR] = _hoops_CAHSR::_hoops_SAHSR;
	state->_hoops_CSC.colors[_hoops_HCGSR] = _hoops_CAHSR::_hoops_SAHSR;
	state->_hoops_CSC.colors[_hoops_ICGSR] = _hoops_CAHSR::_hoops_SAHSR;

	state->_hoops_CSC.fill_style = -1;
	state->_hoops_CSC._hoops_APRSR = -1;

	state->_hoops_CSC._hoops_PPRSR = -1;
	state->_hoops_CSC.line_weight = -1;

	state->_hoops_CSC._hoops_IPRSR = -1;
	state->_hoops_CSC._hoops_GHRSR = -1;
	state->_hoops_CSC._hoops_IHRSR = false;

	state->_hoops_CSC._hoops_RHRSR = 0xffff;
	state->_hoops_CSC._hoops_CHRSR = -1;

	state->_hoops_CSC._hoops_AHRSR = (_hoops_GARRR) - 1;
	state->_hoops_CSC._hoops_HHRSR = false;
}


static void finish_picture(Net_Rendition const &nr, bool swap_buffers)
{
	Display_Context const *dc = nr->_hoops_SRA;
	_hoops_RGRSR alter *state = _hoops_RCRSR(nr);
	UNREFERENCED(swap_buffers);
	_hoops_HPICR("\nfinish picture\n");
	if (!BIT(dc->flags, _hoops_SAISR))
		return;
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			_hoops_AAASR(state, _hoops_HCICR, _hoops_ASICR, 0);
		}	break;
		case _hoops_SHICR: {
			_hoops_CSRSR(state, "ENDPIC;\n");
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in add end picture line");
		}	break;
	}
}


static POINTER_SIZED_INT get_outer_window(Display_Context const *dc)
{
	_hoops_RGRSR alter *state = _hoops_GCRSR(dc);

	/* _hoops_IPISR _hoops_GHCA _hoops_HS _hoops_HGAS _hoops_RAS _hoops_RH _hoops_PPSR _hoops_IIGR _hoops_APISR */
	int encoding = _hoops_GSRSR(dc);
	if (encoding != _hoops_GIICR)
		state->_hoops_GRRSR = encoding;
	_hoops_HPICR("\nget_outer_window\n");
	return 0L;
}


static bool _hoops_CPISR(Line_Rendition const & _hoops_HC, int *pattern)
{
	if (pattern != null)
		*pattern = LP_SOLID;

	if (BIT(_hoops_HC->flags, _hoops_SRPI) || ANYBIT(_hoops_HC->line_style->flags, LSF_COMPLEX_ANYBITS))
		return true;

	if (_hoops_HC->weight > 1) {
		if ((_hoops_HC->style & LCAP_MASK) != LCAP_ROUND &&
			(_hoops_HC->style & LCAP_MASK) != LCAP_BUTT &&
			(_hoops_HC->style & LCAP_MASK) != LCAP_SQUARE)
			return true;
		if (BIT(_hoops_HC->line_style->flags, LSF_SOLID))
			return false;
		else if ((_hoops_HC->style & LPAT_MASK) != LPAT_BUTT) {
			if ((_hoops_HC->style & LCAP_MASK) == LCAP_ROUND &&
				(_hoops_HC->style & LPAT_MASK) != LPAT_ROUND)
				return true;
			if ((_hoops_HC->style & LCAP_MASK) == LCAP_SQUARE &&
				(_hoops_HC->style & LPAT_MASK) != LPAT_SQUARE)
				return true;
		}
	}
	else if (BIT(_hoops_HC->line_style->flags, LSF_SOLID))
		return false;

	if (!BIT(_hoops_HC->line_style->flags, LSF_SOLID)) {
		Line_Style const &	line_style = _hoops_HC->line_style;
		int const *_hoops_SPISR = line_style->_hoops_GHISR[0].pattern;
		switch (line_style->_hoops_GHISR[0]._hoops_RHISR) {
			case 2:
				if (_hoops_SPISR[0] == 10 && _hoops_SPISR[1] == 6) {
					if (pattern != null)
						*pattern = LP_DASHED;
					return false;
				}
				if (_hoops_SPISR[0] == 5 && _hoops_SPISR[1] == 3) {
					if (pattern != null)
						*pattern = LP_DOTTED;
					return false;
				}
				break;
			case 4:
				if (_hoops_SPISR[0] == 18 && _hoops_SPISR[1] == 5 && _hoops_SPISR[2] == 4 && _hoops_SPISR[3] == 5) {
					if (pattern != null)
						*pattern = LP_DASHDOT;
					return false;
				}
				break;
			case 6:
				if (_hoops_SPISR[0] == 15 && _hoops_SPISR[1] == 4 && _hoops_SPISR[2] == 3 &&
					_hoops_SPISR[3] == 3 && _hoops_SPISR[4] == 3 && _hoops_SPISR[5] == 4) {
					if (pattern != null)
						*pattern = LP_DASH_2DOT;
					return false;
				}
				break;
		}
	}
	return true;
}


static bool _hoops_AHISR(Net_Rendition const &nr, _hoops_PIRGR const *curve, int *pattern)
{
	int count, _hoops_PHISR, i;
	Point *_hoops_HHISR;
	DC_Point *_hoops_IHISR;
	float const *mat;
	Polyline polyline;
	if (_hoops_CPISR(nr->_hoops_AHP, pattern)) {
		return true;
	}
	if (curve->control_points == null) {
		return true;
	}
	if (curve->knots == null) {
		return true;
	}
	if (curve->weights == null) {
		return true;
	}
	if (curve->polyline.points == null) {
		HI_Generate_NURBS_Polyline(curve, &nr->_hoops_ARA->_hoops_APPI,
									&nr->transform_rendition->matrix->data, &polyline, 0);
		if (!polyline.points)
			return true;	/* _hoops_CHISR? */

		/* _hoops_CHPR _hoops_SAII _hoops_IIGR _hoops_RH _hoops_PIH _hoops_IS _hoops_RH _hoops_AGIS */
		((_hoops_PIRGR alter *) curve)->polyline.points = polyline.points;
		((_hoops_PIRGR alter *) curve)->polyline.count = polyline.count;
		((_hoops_PIRGR alter *) curve)->polyline.allocated = polyline.allocated;
	}
	else {
		polyline.points = curve->polyline.points;
		polyline.count = curve->polyline.count;
		polyline.allocated = curve->polyline.allocated;
	}
	count = polyline.count;
	_hoops_PHISR = count * 3 - 2;
	ALLOC_ARRAY_ALIGNED(_hoops_HHISR, _hoops_PHISR, Point, 16);
	ALLOC_ARRAY_ALIGNED(_hoops_IHISR, _hoops_PHISR, DC_Point, 16);
	HI_Generate_Polyline_Bezier(count, polyline.points, _hoops_HHISR);
	mat = &nr->transform_rendition->matrix->data.elements[0][0];
	HI_Compute_Transformed_Points(_hoops_PHISR, _hoops_HHISR, mat, (Point *) _hoops_IHISR);
	if (BIT(nr->transform_rendition->flags, _hoops_CSP)) {
		for (i = 0; i < _hoops_PHISR; i++) {
			if (!HD_Point_Within_Cutting_Planes (nr->transform_rendition, _hoops_IHISR[i].x, _hoops_IHISR[i].y, _hoops_IHISR[i].z)) {
				FREE_ARRAY_ALIGNED(_hoops_HHISR, _hoops_PHISR, Point, 16);
				FREE_ARRAY_ALIGNED(_hoops_IHISR, _hoops_PHISR, DC_Point, 16);
				return true;
			}
		}

		/* _hoops_SHS _hoops_HSSC _hoops_RHIR _hoops_IS _hoops_SHISR _hoops_AGIR _hoops_CAPP */
	}
	FREE_ARRAY_ALIGNED(_hoops_HHISR, _hoops_PHISR, Point, 16);
	FREE_ARRAY_ALIGNED(_hoops_IHISR, _hoops_PHISR, DC_Point, 16);
	return false;
}


static void draw_3d_nurbs_curve(Net_Rendition const &nr, _hoops_PIRGR const *curve)
{
	_hoops_HPICR("\n" "draw_3d_nurbes_curve" "\n");
	_hoops_RGRSR alter *state = _hoops_RCRSR(nr);
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	DC_Point *_hoops_IHISR;
	float const *mat;
	int pattern;

	/* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_GGR _hoops_CIHP _hoops_PHCR... */
	if (nr->transform_rendition->_hoops_SPH->projection != _hoops_CPPCR) {
		HD_Std_3D_NURBS_Curve(nr, curve);
		return;
	}

	if (_hoops_AHISR(nr, curve, &pattern)) {
		HD_Std_3D_NURBS_Curve(nr, curve);
		return;
	}

	_hoops_PCPSR(state, nr->transform_rendition);
	_hoops_CSASR(state, _hoops_RCGSR, &_hoops_HC->color);
	_hoops_AIPSR(state, pattern, _hoops_HC->style);
	_hoops_ACPSR(state, _hoops_HC->weight);
	mat = &nr->transform_rendition->matrix->data.elements[0][0];
	ALLOC_ARRAY_ALIGNED(_hoops_IHISR, curve->control_point_count, DC_Point, 16);
	HI_Compute_Transformed_Points(curve->control_point_count, curve->control_points, mat, (Point *) _hoops_IHISR);
	_hoops_HSPSR(state, curve->degree, curve->control_point_count, _hoops_IHISR,
				curve->knots, curve->start_u, curve->end_u, curve->weights);
	FREE_ARRAY_ALIGNED(_hoops_IHISR, curve->control_point_count, DC_Point, 16);
}

local void
draw_3d_marker (Net_Rendition const & nr,
					Marker const * m)
{
	_hoops_HPICR("\n" "draw_3d_marker" "\n");

	if (BIT(nr->_hoops_SRA->options._hoops_IRARR, _hoops_PHICR)) {
		HD_Std_3D_Marker(nr, m);
		return;
	}

	/* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_GGR _hoops_CIHP _hoops_PHCR... */
	if (nr->transform_rendition->_hoops_SPH->projection != _hoops_CPPCR) {
		HD_Std_3D_Marker(nr, m);
		return;
	}

	float const * mat = &nr->transform_rendition->matrix->data.elements[0][0];
	Point _hoops_GIISR;
	HI_Compute_Transformed_Points(1, &m->_hoops_CSAI, mat, &_hoops_GIISR);

	if (nr->transform_rendition->_hoops_RGH &&
		!HD_Point_Within_Cutting_Planes(nr->transform_rendition, _hoops_GIISR.x, _hoops_GIISR.y, _hoops_GIISR.z)) {
		HD_Std_3D_Marker(nr, m);
		return;
	}

	_hoops_RGRSR alter *state = _hoops_RCRSR(nr);

	int size = 0;
	if (nr->_hoops_GSP->ysize < 0) {
		size = HD_Compute_Generic_Size (nr, nr->_hoops_GSP->_hoops_PHP, nr->_hoops_GSP->_hoops_HHP,
										1.0f, false, 0, true);
	}
	else {
		size = 2.0f * nr->_hoops_GSP->ysize;
	}

	if (size > 0) {
		_hoops_HCRPR const * const glyph = &nr->_hoops_GSP->glyph->name;
		if (_hoops_AGGR(glyph->text, "+"))
			_hoops_RCPSR(state, _hoops_RSGSR);
		else if (_hoops_AGGR(glyph->text, "()"))
			_hoops_RCPSR(state, _hoops_PSGSR);
		else if (_hoops_AGGR(glyph->text, "x"))
			_hoops_RCPSR(state, _hoops_HSGSR);
		else if (_hoops_AGGR(glyph->text, "*"))
			_hoops_RCPSR(state, _hoops_ASGSR);
		else if (_hoops_AGGR(glyph->text, ".")) {
			_hoops_RCPSR(state, _hoops_GSGSR);
			size = 0;
		}
		else {
			HD_Std_3D_Marker(nr, m);
			return;
		}
	}
	else {
		_hoops_RCPSR(state, _hoops_GSGSR);
		size = 0;
	}

	_hoops_GCPSR(state, size);
	_hoops_CSASR(state, _hoops_PCGSR, &nr->_hoops_GSP->color);
	_hoops_PRHSR(state, 1, &_hoops_GIISR);

	return;
}


static void _hoops_RIISR(Elliptical_Arc const * arc,
											  Vector * start,
											  Vector * end)
{
	Vector _hoops_CSPIR = arc->_hoops_GGHI;
	Vector _hoops_AIISR = _hoops_CSPIR._hoops_SAIAR(arc->_hoops_RGHI);

	_hoops_AIISR._hoops_AAIAR();

	*end = *start = _hoops_CSPIR;

	float matrix[16];
	HI_Compute_Offaxis_Rotation(_hoops_AIISR.x, _hoops_AIISR.y, _hoops_AIISR.z, 360.0 * arc->arc_start, matrix);
	HI_Compute_Transformed_Vectors(1, start, matrix, start);

	HI_Compute_Offaxis_Rotation(_hoops_AIISR.x, _hoops_AIISR.y, _hoops_AIISR.z, 360.0 * arc->_hoops_PHHI, matrix);
	HI_Compute_Transformed_Vectors(1, end, matrix, end);
}

static void draw_3d_elliptical_arc(Net_Rendition const &nr,
								   Elliptical_Arc const *arc)
{
	_hoops_HPICR("\ndraw_3d_elliptical_arc\n");

	/* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_GGR _hoops_CIHP _hoops_PHCR... */
	if (nr->transform_rendition->_hoops_SPH->projection != _hoops_CPPCR) {
		HD_Std_3D_Elliptical_Arc(nr, arc);
		return;
	}

	if (arc->type == _hoops_GRCP || arc->type == _hoops_RRCP) {
		/*
		 * _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA _hoops_RSH _hoops_IS _hoops_PGSA _hoops_PIISR _hoops_AGSAR _hoops_ARI, _hoops_PPR _hoops_CHH
		 * _hoops_HRII _hoops_HAR _hoops_HIISR _hoops_CCA _hoops_SCII->_hoops_CSIS
		 */
		HD_Std_3D_Elliptical_Arc(nr, arc);
		return;
	}

	int pattern;
	if (_hoops_CPISR(nr->_hoops_AHP, &pattern)) {
		HD_Std_3D_Elliptical_Arc(nr, arc);
		return;
	}

	/* _hoops_SSSA _hoops_RH _hoops_IIISR _hoops_IH _hoops_IPAC _hoops_CIHH. */
	DC_Point _hoops_CIISR[16];
	int count;
	HD_Generate_Elliptical_Bezier(nr, (_hoops_GHHI const *) arc, &count, _hoops_CIISR);

	/* _hoops_CGP _hoops_IIH _hoops_CHR _hoops_HPPA _hoops_GHC _hoops_GGR _hoops_RH _hoops_HIRA, _hoops_SR _hoops_RRP _hoops_AGAH _hoops_IS _hoops_HPPP _hoops_AGCR... */
	if (BIT(nr->transform_rendition->flags, _hoops_CSP)) {
		for (int i = 0; i < count; i++) {
			if (!HD_Point_Within_Cutting_Planes(nr->transform_rendition, _hoops_CIISR[i].x, _hoops_CIISR[i].y, _hoops_CIISR[i].z)) {
				HD_Std_3D_Elliptical_Arc(nr, arc);
				return;
			}
		}
	}

	/* _hoops_GPGP _hoops_RSPA _hoops_PHCR, _hoops_ASCA _hoops_RH 2d _hoops_HCPI _hoops_SSPP _hoops_IS _hoops_RH _hoops_RGHR
	   _hoops_APSH _hoops_GGSP _hoops_GAR _hoops_IIH _hoops_HRGR _hoops_PSP _hoops_AIHP _hoops_SIISR.  _hoops_RCICR _hoops_SSCP _hoops_PSP _hoops_AIHP
	   _hoops_SIISR _hoops_GAR _hoops_SCH'_hoops_GRI _hoops_IRS 2d "_hoops_SISS". */

	Vector normal;
	HI_Cross_Product(&arc->_hoops_GGHI, &arc->_hoops_RGHI, &normal);
	HI_Normalize(&normal);
	HI_Compute_Transformed_Vectors(1, &normal, &nr->transform_rendition->_hoops_IPH->data.elements[0][0], &normal);
	float const _hoops_SSRP = normal._hoops_SSRP(nr->transform_rendition->_hoops_SPH->_hoops_IIPCR);

	/* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HCHAR _hoops_HPGR _hoops_ISCP _hoops_PGIS _hoops_GCISR _hoops_ISHA _hoops_GPP... */
	if (_hoops_SSRP*_hoops_SSRP < 0.001f) {
		_hoops_HPICR("\t" "punting, nearly edge on" "\n");
		HD_Std_3D_Elliptical_Arc(nr, arc);
		return;
	}

	/* _hoops_GAGA _hoops_RGR _hoops_PGIS _hoops_HII 3d _hoops_IS 2d. */
	float const * mat = &nr->transform_rendition->matrix->data.elements[0][0];
	Point center;
	Vector _hoops_GGHI, _hoops_RGHI;
	HI_Compute_Transformed_Points(1, &arc->center, mat, &center);
	HI_Compute_Transformed_Vectors(1, &arc->_hoops_GGHI, mat, &_hoops_GGHI);
	HI_Compute_Transformed_Vectors(1, &arc->_hoops_RGHI, mat, &_hoops_RGHI);
	center.z = _hoops_GGHI.z = _hoops_RGHI.z = 0;

	/* _hoops_SIPR _hoops_RH _hoops_RCISR (_hoops_CACH _hoops_RCICR _hoops_ACISR) _hoops_RSSA. */
	Point _hoops_PGHSR;
	Point _hoops_HGHSR;
	_hoops_PGHSR = center + _hoops_GGHI;
	_hoops_HGHSR = center + _hoops_RGHI;

	if (Abs (center.x) > 32767 || Abs (center.y) > 32767 ||
		Abs (_hoops_PGHSR.x) > 32767 || Abs (_hoops_PGHSR.y) > 32767 ||
		Abs (_hoops_HGHSR.x) > 32767 || Abs (_hoops_HGHSR.y) > 32767) {
		_hoops_HPICR("\t" "punting, clipped control data" "\n");
		Net_Rendition	_hoops_CRAI = nr;

		if (!_hoops_CRAI->_hoops_ARA->_hoops_APPI._hoops_SAR)
			_hoops_CRAI.Modify()->_hoops_ARA.Modify()->_hoops_APPI._hoops_SAR = true;

		HD_Std_3D_Elliptical_Arc(_hoops_CRAI, arc);
		return;
	}

	Vector _hoops_IGHSR;
	Vector _hoops_CGHSR;
	_hoops_RIISR(arc, &_hoops_IGHSR, &_hoops_CGHSR);

	HI_Compute_Transformed_Vectors(1, &_hoops_IGHSR, mat, &_hoops_IGHSR);
	HI_Compute_Transformed_Vectors(1, &_hoops_CGHSR, mat, &_hoops_CGHSR);

	/* _hoops_IRSC _hoops_ARI _hoops_GPP _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_PCISR _hoops_HIS _hoops_SR _hoops_PAH _hoops_ARP _hoops_RH _hoops_HCISR _hoops_PIAP. */
	_hoops_RGRSR alter *state = _hoops_RCRSR(nr);
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	_hoops_PCPSR(state, nr->transform_rendition);
	_hoops_CSASR(state, _hoops_RCGSR, &_hoops_HC->color);
	_hoops_AIPSR(state, pattern, _hoops_HC->style);
	_hoops_ACPSR(state, _hoops_HC->weight);

	/* _hoops_CGP _hoops_RH _hoops_HARGR'_hoops_GRI _hoops_CHR _hoops_HAR _hoops_SASPR, _hoops_SR _hoops_SHR _hoops_PGSA _hoops_PCCP _hoops_ICISR _hoops_PGIS. */
	_hoops_SGHSR(state, &center, &_hoops_PGHSR, &_hoops_HGHSR, &_hoops_IGHSR, &_hoops_CGHSR);
}


/* _hoops_SRAC */
static void draw_3d_ellipse(Net_Rendition const &nr, Ellipse const *ellipse)
{
	_hoops_HPICR("\ndraw_3d_ellipse\n");
	_hoops_RGRSR alter *state = _hoops_RCRSR(nr);

	/* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_GGR _hoops_CIHP _hoops_PHCR... */
	if (nr->transform_rendition->_hoops_SPH->projection != _hoops_CPPCR) {
		HD_Std_3D_Ellipse(nr, ellipse);
		return;
	}

	/* _hoops_SIGP: _hoops_PS _hoops_RRP _hoops_IRS _hoops_HSP _hoops_IAHA _hoops_CAH. */

	/* _hoops_SSSA _hoops_RH _hoops_IIISR _hoops_IH _hoops_IPAC _hoops_CIHH. */
	DC_Point _hoops_CIISR[16];
	int count;
		HD_Generate_Elliptical_Bezier(nr, (_hoops_GHHI const *) ellipse, &count, _hoops_CIISR);

	/* _hoops_CGP _hoops_IIH _hoops_CHR _hoops_HPPA _hoops_GHC _hoops_GGR _hoops_RH _hoops_HIRA, _hoops_SR _hoops_RRP _hoops_AGAH _hoops_IS _hoops_HPPP _hoops_AGCR... */
	if (BIT(nr->transform_rendition->flags, _hoops_CSP)) {
		for (int i = 0; i < count; i++) {
			if (!HD_Point_Within_Cutting_Planes(nr->transform_rendition, _hoops_CIISR[i].x, _hoops_CIISR[i].y, _hoops_CIISR[i].z)) {
				HD_Std_3D_Ellipse(nr, ellipse);
				return;
			}
		}
	}

	/* _hoops_GPGP _hoops_RSPA _hoops_PHCR, _hoops_ASCA _hoops_RH 2d _hoops_HCPI _hoops_SSPP _hoops_IS _hoops_RH _hoops_RGHR
	   _hoops_APSH _hoops_GGSP _hoops_GAR _hoops_IIH _hoops_HRGR _hoops_PSP _hoops_AIHP _hoops_SIISR.  _hoops_RCICR _hoops_SSCP _hoops_PSP _hoops_AIHP
	   _hoops_SIISR _hoops_GAR _hoops_SCH'_hoops_GRI _hoops_IRS 2d "_hoops_SISS". */

	Vector normal;
	HI_Cross_Product(&ellipse->_hoops_GGHI, &ellipse->_hoops_RGHI, &normal);
	HI_Normalize(&normal);
	HI_Compute_Transformed_Vectors(1, &normal, &nr->transform_rendition->_hoops_IPH->data.elements[0][0], &normal);
	float const _hoops_SSRP = normal._hoops_SSRP(nr->transform_rendition->_hoops_SPH->_hoops_IIPCR);

	/* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HCHAR _hoops_HPGR _hoops_ISCP _hoops_PGIS _hoops_GCISR _hoops_ISHA _hoops_GPP... */
	if (_hoops_SSRP*_hoops_SSRP < 0.001f) {
		_hoops_HPICR("\t" "punting, nearly edge on" "\n");
		HD_Std_3D_Ellipse(nr, ellipse);
		return;
	}

	/* _hoops_GAGA _hoops_RGR _hoops_PGIS _hoops_HII 3d _hoops_IS 2d. */
	float const * mat = &nr->transform_rendition->matrix->data.elements[0][0];
	Point center;
	Vector _hoops_GGHI, _hoops_RGHI;
	HI_Compute_Transformed_Points(1, &ellipse->center, mat, &center);
	HI_Compute_Transformed_Vectors(1, &ellipse->_hoops_GGHI, mat, &_hoops_GGHI);
	HI_Compute_Transformed_Vectors(1, &ellipse->_hoops_RGHI, mat, &_hoops_RGHI);
	center.z = _hoops_GGHI.z = _hoops_RGHI.z = 0;

	/* _hoops_SIPR _hoops_RH _hoops_RCISR (_hoops_CACH _hoops_RCICR _hoops_ACISR) _hoops_RSSA. */
	Point _hoops_PGHSR;
	Point _hoops_HGHSR;
	_hoops_PGHSR = center + _hoops_GGHI;
	_hoops_HGHSR = center + _hoops_RGHI;

	if (Abs (center.x) > 32767 || Abs (center.y) > 32767 ||
		Abs (_hoops_PGHSR.x) > 32767 || Abs (_hoops_PGHSR.y) > 32767 ||
		Abs (_hoops_HGHSR.x) > 32767 || Abs (_hoops_HGHSR.y) > 32767) {
		_hoops_HPICR("\t" "punting, clipped control data" "\n");
		Net_Rendition	_hoops_CRAI = nr;

		if (!_hoops_CRAI->_hoops_ARA->_hoops_APPI._hoops_SAR)
			_hoops_CRAI.Modify()->_hoops_ARA.Modify()->_hoops_APPI._hoops_SAR = true;

		HD_Std_3D_Ellipse (_hoops_CRAI, ellipse);
		return;
	}

	_hoops_PCPSR(state, nr->transform_rendition);

	if (BIT (nr->_hoops_RGP, T_EDGES)) {
		int pattern;
		if (_hoops_CPISR(nr->_hoops_RHP, &pattern)) {
			HD_Std_3D_Ellipse(nr, ellipse);
			return;
		}
		else {
			_hoops_CSASR(state, _hoops_CCGSR, &nr->_hoops_RHP->color);
			_hoops_CHPSR(state, pattern, nr->_hoops_RHP->style);
			_hoops_PIPSR(state, nr->_hoops_RHP->weight);
			_hoops_SPPSR(state, true);
		}
	}
	else {
		_hoops_SPPSR(state, false);
	}

	if (BIT (nr->_hoops_RGP, T_FACES)) {
		_hoops_CSASR(state, _hoops_ACGSR, &nr->_hoops_IHA->color);
		_hoops_GHPSR(state, _hoops_PIGSR);
	}
	else {
		_hoops_GHPSR(state, _hoops_CIGSR);
	}

	switch (ellipse->type) {
		case _hoops_SGCP:
		case _hoops_CGCP:
			if (_hoops_HIICR(_hoops_GGHI.length(), _hoops_RGHI.length()))
					_hoops_CCPSR(state, &center, _hoops_GGHI.length());
			else
					_hoops_GRHSR(state, &center, &_hoops_PGHSR, &_hoops_HGHSR);
			break;

		default:
			_hoops_GRHSR(state, &center, &_hoops_PGHSR, &_hoops_HGHSR);
			break;
	}
}



/* _hoops_SRAC */
static void
_hoops_CCISR(Net_Rendition const &nr,
					   DC_Point const *center,
					   DC_Point const *radii,
					   float start,
					   float end)
{
	_hoops_HPICR("\ndraw_dc_elliptical_arc\n");

	int pattern;
	if (_hoops_CPISR(nr->_hoops_AHP, &pattern)) {
		HD_Std_DC_Elliptical_Arc(nr, center, radii, start, end);
		return;
	}

	Point _hoops_GGHI(radii->x, 0, 0);
	Point _hoops_RGHI(0, radii->y, 0);

	DC_Point _hoops_CIISR[16];
	int count;
	HD_DC_Generate_Elliptical_Bezier(nr, center, (DC_Point*)&_hoops_GGHI, (DC_Point*)&_hoops_RGHI, start, end, &count, _hoops_CIISR);

	if (BIT(nr->transform_rendition->flags, _hoops_CSP)) {
		for (int i = 0; i < count; i++) {
			if (!HD_Point_Within_Cutting_Planes(nr->transform_rendition, _hoops_CIISR[i].x, _hoops_CIISR[i].y, _hoops_CIISR[i].z)) {
				HD_Std_DC_Elliptical_Arc(nr, center, radii, start, end);
				return;
			}
		}
	}

	_hoops_RGRSR alter *state = _hoops_RCRSR(nr);
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	_hoops_PCPSR(state, nr->transform_rendition);
	_hoops_CSASR(state, _hoops_RCGSR, &_hoops_HC->color);
	_hoops_AIPSR(state, pattern, _hoops_HC->style);
	_hoops_ACPSR(state, _hoops_HC->weight);

	_hoops_GGHI += Vector(center->x, center->y, center->z);
	_hoops_RGHI += Vector(center->x, center->y, center->z);
	Vector _hoops_IGHSR;
	Vector _hoops_CGHSR;
	_hoops_IGHSR.x = cos(2 * HK_Pi * start);
	_hoops_IGHSR.y = sin(2 * HK_Pi * start);
	_hoops_CGHSR.x = cos(2 * HK_Pi * end);
	_hoops_CGHSR.y = sin(2 * HK_Pi * end);

	_hoops_SGHSR(state, (Point const*)center, &_hoops_GGHI, &_hoops_RGHI, &_hoops_IGHSR, &_hoops_CGHSR);
}


static void
draw_dc_ellipse(Net_Rendition const &nr, DC_Point const * center,
		DC_Point const *size)
{
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HPICR("\ndraw_dc_ellipse\n");

	/* _hoops_RGR _hoops_RHPP _hoops_RHAP _hoops_HAR _hoops_GCGH _hoops_IPSP _hoops_PAPR _hoops_PAIA */
	if (nr->transform_rendition->_hoops_HCHH != null || _hoops_SIGA->pattern == FP_USER_DEFINED) {
		HD_Std_DC_Ellipse(nr, center, size);
		return;
	}


	Display_Context const *dc = nr->_hoops_SRA;
	_hoops_RGRSR alter *state = _hoops_GCRSR(dc);

	/* _hoops_SIPR _hoops_RH _hoops_RCISR (_hoops_CACH _hoops_RCICR _hoops_ACISR) _hoops_RSSA. */
	Point _hoops_PGHSR(center->x + size->x, center->y, center->z);
	Point _hoops_HGHSR(center->x, center->y + size->y, center->z);

	_hoops_PCPSR(state, nr->transform_rendition);

	if (BIT (nr->_hoops_RGP, T_EDGES)) {
		int pattern;
		if (_hoops_CPISR(nr->_hoops_RHP, &pattern)) {
			HD_Std_DC_Ellipse(nr, center, size);
			return;
		}
		else {
			_hoops_CSASR(state, _hoops_CCGSR, &nr->_hoops_RHP->color);
			_hoops_CHPSR(state, pattern, nr->_hoops_RHP->style);
			_hoops_PIPSR(state, nr->_hoops_RHP->weight);
			_hoops_SPPSR(state, true);
		}
	}
	else {
		_hoops_SPPSR(state, false);
	}

	if (BIT (nr->_hoops_RGP, T_FACES)) {
		_hoops_CSASR(state, _hoops_ACGSR, &nr->_hoops_IHA->color);
		_hoops_GHPSR(state, _hoops_PIGSR);
	}
	else {
		_hoops_GHPSR(state, _hoops_CIGSR);
	}

	if (_hoops_HIICR(size->x, size->y))
		_hoops_CCPSR(state, center, size->x);
	else
		_hoops_GRHSR(state, center, &_hoops_PGHSR, &_hoops_HGHSR);
}


static void
_hoops_SCISR(Net_Rendition const &nr, DC_Point const *center,
			DC_Point const *size)
{
	_hoops_HPICR("\n" "draw_dc_outline_ellipse" "\n");

	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	_hoops_HHCR const &_hoops_IHCR = nr->transform_rendition;
	_hoops_RGRSR alter *state = _hoops_RCRSR(nr);

	int pattern;
	if (_hoops_CPISR(nr->_hoops_AHP, &pattern)) {
		HD_Std_DC_Outline_Ellipse(nr, center, size);
		return;
	}

	_hoops_PCPSR(state, _hoops_IHCR);
	_hoops_CSASR(state, _hoops_CCGSR, &_hoops_HC->color);
	_hoops_CHPSR(state, pattern, _hoops_HC->style);
	_hoops_PIPSR(state, _hoops_HC->weight);
	_hoops_SPPSR(state, true);
	_hoops_GHPSR(state, _hoops_CIGSR);

	Point _hoops_GGHI(center->x + size->x, center->y, center->z);
	Point _hoops_RGHI(center->x, center->y + size->y, center->z);

	_hoops_GRHSR(state, (Point const*)center, &_hoops_GGHI, &_hoops_RGHI);
}


static void draw_dc_polyline(Net_Rendition const &nr, int count,
		 DC_Point const *points)
{
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	_hoops_HHCR const &_hoops_IHCR = nr->transform_rendition;
	_hoops_RGRSR alter *state = _hoops_RCRSR(nr);
	int pattern;
	_hoops_HPICR("\ndraw_dc_polyline\n");
	if (_hoops_CPISR(nr->_hoops_AHP, &pattern)) {
		HD_Std_DC_Polyline(nr, count, points);
		return;
	}
	if (BIT(nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline(nr, count, points, 0, 0, 0, 0, 0, 0,
			_hoops_GPHC);
		return;
	}

	_hoops_PCPSR(state, _hoops_IHCR);
	_hoops_CSASR(state, _hoops_RCGSR, &_hoops_HC->color);
	_hoops_AIPSR(state, pattern, _hoops_HC->style);
	_hoops_ACPSR(state, _hoops_HC->weight);

	int const _hoops_GSISR = 100;
	if (count < 0) {
		count = -count;
		while (count > _hoops_GSISR) {
			_hoops_PSPSR(state, _hoops_GSISR, points);
			count -= _hoops_GSISR;
			points += _hoops_GSISR;
		}
		_hoops_PSPSR(state, count, points);
	}
	else {
		while (count > _hoops_GSISR) {
			_hoops_SCPSR(state, _hoops_GSISR, points);
			count -= _hoops_GSISR -1;
			points += _hoops_GSISR -1;
		}
		_hoops_SCPSR(state, count, points);
	}
}


static void draw_dc_face(Net_Rendition const &nr, int count, DC_Point const *points)
{
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HPICR("\ndraw_dc_face\n");

	/* _hoops_RGR _hoops_RHPP _hoops_RHAP _hoops_HAR _hoops_GCGH _hoops_IPSP _hoops_PAPR _hoops_PAIA */
	if (nr->transform_rendition->_hoops_HCHH != null || _hoops_SIGA->pattern == FP_USER_DEFINED)
		HD_Std_DC_Face(nr, count, points);
	else {
		_hoops_HHCR const &_hoops_IHCR = nr->transform_rendition;
		Display_Context const *dc = nr->_hoops_SRA;
		_hoops_RGRSR alter *state = _hoops_GCRSR(dc);

		/* _hoops_PGSA _hoops_RH _hoops_RPHSR _hoops_HSP */
		_hoops_PCPSR(state, _hoops_IHCR);
		_hoops_CSASR(state, _hoops_ACGSR, &_hoops_SIGA->color);
		_hoops_AHPSR(state, dc, FP_SOLID);
		_hoops_GHPSR(state, _hoops_PIGSR);
		_hoops_SPPSR(state, false);

		_hoops_RRHSR(state, count, points);

		if (_hoops_SIGA->pattern != FP_SOLID) {
			/* _hoops_APHSR _hoops_RH _hoops_HSGP */
			_hoops_CSASR(state, _hoops_ACGSR, &_hoops_SIGA->contrast_color);
			_hoops_AHPSR(state, dc, _hoops_SIGA->pattern);
			_hoops_RRHSR(state, count, points);
		}
	}
}


static void draw_dc_colorized_face(Net_Rendition const &nr, int count,
			   DC_Point const *points, RGBAS32 const *color)
{
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HPICR("\ndraw_dc_colorized_face\n");

	/* _hoops_RGR _hoops_RHPP _hoops_RHAP _hoops_HAR _hoops_GCGH _hoops_IPSP _hoops_PAPR _hoops_PAIA */
	if (nr->transform_rendition->_hoops_HCHH != null || _hoops_SIGA->pattern == FP_USER_DEFINED)
		HD_Std_DC_Face(nr, count, points);
	else {
		_hoops_HHCR const &_hoops_IHCR = nr->transform_rendition;
		Display_Context const *dc = nr->_hoops_SRA;
		_hoops_RGRSR alter *state = _hoops_GCRSR(dc);
		Driver_Color _hoops_RSISR;

		/* _hoops_PGSA _hoops_RH _hoops_RPHSR _hoops_HSP */
		_hoops_PCPSR(state, _hoops_IHCR);
		_hoops_RSISR = *color;
		_hoops_CSASR(state, _hoops_ACGSR, &_hoops_RSISR);
		_hoops_AHPSR(state, dc, FP_SOLID);
		_hoops_GHPSR(state, _hoops_PIGSR);
		_hoops_SPPSR(state, false);

		_hoops_RRHSR(state, count, points);

		if (_hoops_SIGA->pattern != FP_SOLID) {
			/* _hoops_APHSR _hoops_RH _hoops_HSGP */
			_hoops_CSASR(state, _hoops_ACGSR, &_hoops_SIGA->contrast_color);
			_hoops_AHPSR(state, dc, _hoops_SIGA->pattern);
			_hoops_RRHSR(state, count, points);
		}
	}
}


static void draw_dc_polytriangle(Net_Rendition const &nr, int count,
			 DC_Point const *points)
{
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HPICR("\ndraw_dc_polytriangle\n");

	/* _hoops_RGR _hoops_RHPP _hoops_RHAP _hoops_HAR _hoops_GCGH _hoops_IPSP _hoops_PAPR _hoops_PAIA */
	if (nr->transform_rendition->_hoops_HCHH != null || _hoops_SIGA->pattern == FP_USER_DEFINED)
		HD_Span_DC_Polytriangle(nr, count, points);
	else {
		_hoops_HHCR const &_hoops_IHCR = nr->transform_rendition;
		Display_Context const *dc = nr->_hoops_SRA;
		_hoops_RGRSR alter *state = _hoops_GCRSR(dc);
		int _hoops_RRC;
		_hoops_PCPSR(state, _hoops_IHCR);
		_hoops_ICHC(count, _hoops_RRC, 3);
		while (count--) {
			/* _hoops_PGSA _hoops_RH _hoops_RPHSR _hoops_SCPH */
			_hoops_CSASR(state, _hoops_ACGSR, &_hoops_SIGA->color);
			_hoops_AHPSR(state, dc, FP_SOLID);
			_hoops_GHPSR(state, _hoops_PIGSR);
			_hoops_SPPSR(state, false);

			_hoops_RRHSR(state, 3, points);

			if (_hoops_SIGA->pattern != FP_SOLID) {
				/* _hoops_APHSR _hoops_RH _hoops_HSGP */
				_hoops_CSASR(state, _hoops_ACGSR, &_hoops_SIGA->contrast_color);
				_hoops_AHPSR(state, dc, _hoops_SIGA->pattern);
				_hoops_RRHSR(state, 3, points);
			}
			points += _hoops_RRC;
		}
	}
}


static void draw_dc_colorized_polytriangle(Net_Rendition const &nr,
										   int count,
										   DC_Point const *points,
										   RGBAS32 const *color,
										   bool single)
{
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HPICR("\ndraw_dc_colorized_polytriangle\n");

	/* _hoops_RGR _hoops_RHPP _hoops_RHAP _hoops_HAR _hoops_GCGH _hoops_IPSP _hoops_PAPR _hoops_PAIA */
	if (nr->transform_rendition->_hoops_HCHH != null || _hoops_SIGA->pattern == FP_USER_DEFINED)
		HD_Span_DC_Colorized_Polytris(nr, count, points, color, single);
	else {
		_hoops_HHCR const &_hoops_IHCR = nr->transform_rendition;
		Display_Context const *dc = nr->_hoops_SRA;
		_hoops_RGRSR alter *state = _hoops_GCRSR(dc);
		Driver_Color _hoops_RSISR;
		int _hoops_RRC;
		_hoops_PCPSR(state, _hoops_IHCR);
		_hoops_ICHC(count, _hoops_RRC, 3);
		while (count--) {
			/* _hoops_PGSA _hoops_RH _hoops_RPHSR _hoops_HSP */
			_hoops_RSISR = *color;
			_hoops_CSASR(state, _hoops_ACGSR, &_hoops_RSISR);
			_hoops_AHPSR(state, dc, FP_SOLID);
			_hoops_GHPSR(state, _hoops_PIGSR);
			_hoops_SPPSR(state, false);

			_hoops_RRHSR(state, 3, points);

			if (_hoops_SIGA->pattern != FP_SOLID) {
				/* _hoops_APHSR _hoops_RH _hoops_HSGP */
				_hoops_CSASR(state, _hoops_ACGSR, &_hoops_SIGA->contrast_color);
				_hoops_AHPSR(state, dc, _hoops_SIGA->pattern);
				_hoops_RRHSR(state, 3, points);
			}
			points += _hoops_RRC;
			if (!single)
				++color;
		}
	}
}


static void draw_dc_gouraud_polytriangle(Net_Rendition const &nr,
										 int count,
										 DC_Point const *points,
										 RGBAS32 const *colors)
{
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HPICR("\ndraw_dc_gouraud_polytriangle\n");

	/* _hoops_RGR _hoops_RHPP _hoops_RHAP _hoops_HAR _hoops_GCGH _hoops_IPSP _hoops_PAPR _hoops_PAIA */
	if (nr->transform_rendition->_hoops_HCHH != null || _hoops_SIGA->pattern == FP_USER_DEFINED)
		HD_Span_DC_Gouraud_Polytris(nr, count, points, colors);
	else {
		_hoops_HHCR const &_hoops_IHCR = nr->transform_rendition;
		Display_Context const *dc = nr->_hoops_SRA;
		_hoops_RGRSR alter *state = _hoops_GCRSR(dc);
		int _hoops_RRC;

		/* _hoops_PGSA _hoops_RH _hoops_RPHSR _hoops_HSP */
		_hoops_PCPSR(state, _hoops_IHCR);
		_hoops_GHPSR(state, _hoops_PIGSR);
		_hoops_SPPSR(state, false);

		_hoops_ICHC(count, _hoops_RRC, 3);
		while (count--) {
			/* _hoops_PPIP _hoops_ASISR _hoops_APSA */
			switch (state->_hoops_GRRSR) {
				case _hoops_CHICR: {
					_hoops_GHPSR(state, _hoops_GCGSR);
					_hoops_AAASR(state, _hoops_HHSCR, _hoops_CSSCR, 8);
					_hoops_RAASR(state, points, 1);
					_hoops_AAASR(state, _hoops_HHSCR, _hoops_ARGSR, 2 + 16 + 2 + 9);
					_hoops_GGASR(state, (unsigned short) 3);

					state->points[0].x = points[1].x - points[0].x;
					state->points[0].y = points[1].y - points[0].y;
					state->points[1].x = points[2].x - points[0].x;
					state->points[1].y = points[2].y - points[0].y;
					_hoops_RAASR(state, state->points, 2);
					_hoops_GGASR(state, (unsigned short) 0);
					_hoops_ISRSR(state, (unsigned char) colors[0].r);
					_hoops_ISRSR(state, (unsigned char) colors[0].g);
					_hoops_ISRSR(state, (unsigned char) colors[0].b);
					_hoops_ISRSR(state, (unsigned char) colors[1].r);
					_hoops_ISRSR(state, (unsigned char) colors[1].g);
					_hoops_ISRSR(state, (unsigned char) colors[1].b);
					_hoops_ISRSR(state, (unsigned char) colors[2].r);
					_hoops_ISRSR(state, (unsigned char) colors[2].g);
					_hoops_ISRSR(state, (unsigned char) colors[2].b);
					_hoops_ISRSR(state, (unsigned char) 0);
				}	break;
				case _hoops_SHICR: {
					_hoops_GHPSR(state, _hoops_GCGSR);
					Sprintf_FF(state->_hoops_IGRSR, "FILLREFPT (%f,%f)\n", points[0].x, points[0].y);
					_hoops_CSRSR(state, state->_hoops_IGRSR);
					state->points[0].x = points[1].x - points[0].x;
					state->points[0].y = points[1].y - points[0].y;
					state->points[1].x = points[2].x - points[0].x;
					state->points[1].y = points[2].y - points[0].y;
					Sprintf_FF(state->_hoops_IGRSR, " INTERPINT 3 (%f,%f) ", state->points[0].x, state->points[0].y);
					_hoops_CSRSR(state, state->_hoops_IGRSR);
					Sprintf_FF(state->_hoops_IGRSR, "(%f,%f) 0 ", state->points[1].x, state->points[1].y);
					_hoops_CSRSR(state, state->_hoops_IGRSR);
					Sprintf_DD(state->_hoops_IGRSR, "(%d,%d,", (int) colors[0].r, (int) colors[0].g);
					_hoops_CSRSR(state, state->_hoops_IGRSR);
					Sprintf_DD(state->_hoops_IGRSR, "%d)(%d", (int) colors[0].b, (int) colors[1].r);
					_hoops_CSRSR(state, state->_hoops_IGRSR);
					Sprintf_DD(state->_hoops_IGRSR, "%d,%d)", (int) colors[1].g, (int) colors[1].b);
					_hoops_CSRSR(state, state->_hoops_IGRSR);
					Sprintf_DD(state->_hoops_IGRSR, "(%d,%d,", (int) colors[2].r, (int) colors[2].g);
					_hoops_CSRSR(state, state->_hoops_IGRSR);
					Sprintf_D(state->_hoops_IGRSR, "%d);\n ", (int) colors[2].b);
					_hoops_CSRSR(state, state->_hoops_IGRSR);
				}	break;
				default: {
					_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
										"Invalid encoding in draw gouraud polytriangle");
				}	break;
			}
			_hoops_RRHSR(state, 3, points);
			if (_hoops_SIGA->pattern != FP_SOLID) {
				/* _hoops_APHSR _hoops_RH _hoops_HSGP */
				_hoops_CSASR(state, _hoops_ACGSR, &_hoops_SIGA->contrast_color);
				_hoops_AHPSR(state, dc, _hoops_SIGA->pattern);
				_hoops_RRHSR(state, _hoops_CCCCR, points);
			}
			points += _hoops_RRC;
			colors += _hoops_RRC;
		}
	}
}


static void draw_dc_rectangle(Net_Rendition const &nr,
							  int left,
							  int right,
							  int bottom,
							  int top)
{
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HPICR("\ndraw_dc_rectangle\n");

	/* _hoops_RGR _hoops_RHPP _hoops_RHAP _hoops_HAR _hoops_GCGH _hoops_IPSP _hoops_PAPR _hoops_PAIA */
	if (nr->transform_rendition->_hoops_HCHH != null || _hoops_SIGA->pattern == FP_USER_DEFINED)
		HD_Std_DC_Rectangle(nr, left, right, bottom, top);
	else {
		_hoops_HHCR const &_hoops_IHCR = nr->transform_rendition;
		Display_Context const *dc = nr->_hoops_SRA;
		_hoops_RGRSR alter *state = _hoops_GCRSR(dc);

		/* _hoops_PGSA _hoops_IRS _hoops_RPHSR _hoops_AHCRR _hoops_HII _hoops_RH _hoops_AAPA _hoops_RAAP _hoops_IS _hoops_RH _hoops_GSSC _hoops_RPHR */
		_hoops_PCPSR(state, _hoops_IHCR);
		_hoops_CSASR(state, _hoops_ACGSR, &_hoops_SIGA->color);
		_hoops_AHPSR(state, dc, FP_SOLID);
		_hoops_GHPSR(state, _hoops_PIGSR);
		_hoops_SPPSR(state, false);

		_hoops_ARHSR(state, left, right, bottom, top);

		/* _hoops_APHSR _hoops_RH _hoops_RPHSR _hoops_CCA _hoops_IRS _hoops_IIPH _hoops_HSSP _hoops_RPP _hoops_HAHH */
		if (_hoops_SIGA->pattern != FP_SOLID) {
			_hoops_CSASR(state, _hoops_ACGSR, &_hoops_SIGA->contrast_color);
			_hoops_AHPSR(state, dc, _hoops_SIGA->pattern);
			_hoops_ARHSR(state, left, right, bottom, top);
		}
	}
}


static void draw_dc_polydot(Net_Rendition const &nr, int count, DC_Point const *points)
{
	_hoops_HPICR("\ndraw_dc_polydot\n");

	_hoops_HHCR const &_hoops_IHCR = nr->transform_rendition;
	if (nr->transform_rendition->_hoops_HCHH != null) {
		HD_Std_DC_Polydot(nr, count, points);
		return;
	}

	_hoops_RGRSR alter *state = _hoops_RCRSR(nr);
	_hoops_RCPSR(state, _hoops_GSGSR);
	_hoops_PCPSR(state, _hoops_IHCR);
	_hoops_CSASR(state, _hoops_PCGSR, &nr->_hoops_AHP->color);
	_hoops_GCPSR(state, 1);

	_hoops_PRHSR(state, count, points);
}

struct _hoops_PSISR {
	unsigned char const *_hoops_HSISR;
	float _hoops_ISISR;
	int _hoops_CSISR;
	char *_hoops_SSISR;
};


static void _hoops_GGCSR(_hoops_RGRSR alter * const state, int const _hoops_CSISR)
{
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			if (state->text._hoops_GIRSR != _hoops_CSISR) {
				state->text._hoops_GIRSR = _hoops_CSISR;
				_hoops_AAASR(state, _hoops_HHSCR, _hoops_HISCR, 2);
				_hoops_GGASR(state, (unsigned short) state->text._hoops_GIRSR);
			}
		}	break;
		case _hoops_SHICR: {
			if (state->text._hoops_GIRSR != _hoops_CSISR) {
				state->text._hoops_GIRSR = _hoops_CSISR;
				Sprintf_D(state->_hoops_IGRSR, "TEXTFONTINDEX %d;\n",
					state->text._hoops_GIRSR);
				_hoops_CSRSR(state, state->_hoops_IGRSR);
			}
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in set_font_index");
		}	break;
	}
}


static void
draw_text(_hoops_RGRSR alter * const state,
		  DC_Point const *const where,
		  float _hoops_RGCSR,
		  Driver_Color const color,
		  float const rotation,
		  int count,
		  Karacter const *kstring)
{
	_hoops_RGCSR *= 0.66f;
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			int i;
			if (state->text._hoops_SHRSR != _hoops_RGCSR) {
				_hoops_AAASR(state, _hoops_HHSCR, _hoops_GCSCR, 2);
				_hoops_GGASR(state, (unsigned short) _hoops_RGCSR);
				state->text._hoops_SHRSR = _hoops_RGCSR;
			}
			if (state->_hoops_CSC.colors[_hoops_HCGSR] != color) {
				_hoops_CSASR(state, _hoops_HCGSR, &color);
				state->_hoops_CSC.colors[_hoops_HCGSR] = color;
			}
			if (state->text.rotation != rotation) {
				float x, y;
				state->text.rotation = rotation;
				_hoops_AAASR(state, _hoops_HHSCR, _hoops_RCSCR, 8);
				x = cos(_hoops_PCSR(rotation) + HK_Pi / 2.0f);
				y = sin(_hoops_PCSR(rotation) + HK_Pi / 2.0f);
				_hoops_RGASR(state, x);
				_hoops_RGASR(state, y);
				x = cos(_hoops_PCSR(rotation));
				y = sin(_hoops_PCSR(rotation));
				_hoops_RGASR(state, x);
				_hoops_RGASR(state, y);
			}
			_hoops_AAASR(state, _hoops_CGSCR, _hoops_ARSCR, 11 + count);
			_hoops_RAASR(state, where, 1);
			_hoops_GGASR(state, (short) 1 /* _hoops_HACH */);
			_hoops_ISRSR(state, (unsigned char) count);
			for (i = 0; i < count; i++) {
				_hoops_ISRSR(state, (char) *kstring++);
			}
			if (count % 2 == 0)
				_hoops_ISRSR(state, (unsigned char) 0);
		}	break;
		case _hoops_SHICR: {
			if (state->text._hoops_SHRSR != _hoops_RGCSR) {
				Sprintf_F(state->_hoops_IGRSR, "CHARHEIGHT %f;\n", _hoops_RGCSR);
				_hoops_CSRSR(state, state->_hoops_IGRSR);
				state->text._hoops_SHRSR = _hoops_RGCSR;
			}
			if (state->_hoops_CSC.colors[_hoops_HCGSR] != color) {
				_hoops_CSASR(state, _hoops_HCGSR, &color);
				state->_hoops_CSC.colors[_hoops_HCGSR] = color;
			}
			if (state->text.rotation != rotation) {
				float x, y;
				state->text.rotation = rotation;
				x = cos(_hoops_PCSR(rotation) + HK_Pi / 2.0f);
				y = sin(_hoops_PCSR(rotation) + HK_Pi / 2.0f);
				Sprintf_FF(state->_hoops_PGRSR, "CharOri %f,%f,", x, y);
				x = cos(_hoops_PCSR(rotation));
				y = sin(_hoops_PCSR(rotation));
				Sprintf_FF(state->_hoops_HGRSR, "%f,%f;", x, y);
				Sprintf_SS(state->_hoops_IGRSR, "%s%s", state->_hoops_PGRSR, state->_hoops_HGRSR);
				_hoops_CSRSR(state, state->_hoops_IGRSR);
			}
			Sprintf_FF(state->_hoops_IGRSR, "TEXT %f, %f, final, \"",
			where->x, where->y);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
			while (count--) {
				_hoops_ISRSR(state, (unsigned char) *kstring++);
			}
			_hoops_CSRSR(state, "\";\n");
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in draw_dc_text");
		}	break;
	}
}


static void
_hoops_AGCSR(Net_Rendition const &nr,
				_hoops_HACC const *text,
				Point const *where,
				int count,
				Karacter const *kstring,
				_hoops_PGCSR const *_hoops_HGCSR)
{
	_hoops_IGCSR const &_hoops_HRCIR = nr->_hoops_SISI;
	Font_Instance const *font = _hoops_HRCIR->font;
	UNREFERENCED(text);
	UNREFERENCED(_hoops_HGCSR);
	if (!font->_hoops_CGCSR) {
		if (!HD_Load_Font(nr->_hoops_SRA, font))
			return;		/* _hoops_RCRP _hoops_GH _hoops_RPP _hoops_SR _hoops_PAH'_hoops_RA _hoops_SGCSR */
	}
	if (_hoops_HRCIR->_hoops_GRCSR != 0 && font->family->_hoops_RRCSR == _hoops_ARCSR) {
		/* _hoops_PRCSR _hoops_HRCSR */
		_hoops_RGRSR alter *state = _hoops_GCRSR(nr->_hoops_SRA);
		DC_Point _hoops_IRCSR;
		_hoops_IRCSR.x = where->x;
		_hoops_IRCSR.y = where->y;
		_hoops_GGCSR(state, _hoops_HRCIR->_hoops_GRCSR);
		draw_text(state, &_hoops_IRCSR, 20, _hoops_HRCIR->color, _hoops_HRCIR->rotation, count, kstring);
	}
	else {
		Vector const _hoops_CRCSR = Vector(1.0f, 1.0f, 1.0f);
		(*font->_hoops_SRCSR) (nr, font, where, count, kstring, &_hoops_CRCSR);
	}
}


static void
draw_dc_text(Net_Rendition const &nr,
			 DC_Point const *where,
			 int count,
			 Karacter const *kstring)
{
	_hoops_RGRSR alter *state = _hoops_GCRSR(nr->_hoops_SRA);
	_hoops_IGCSR const &_hoops_HRCIR = nr->_hoops_SISI;
	_hoops_PSISR const *_hoops_GACSR = (_hoops_PSISR const *) _hoops_HRCIR->font->_hoops_GAASR;
	_hoops_HPICR("\ndraw_dc_text\n");
	_hoops_GGCSR(state, state->text._hoops_PIRSR + _hoops_GACSR->_hoops_CSISR);
	draw_text(state, where, _hoops_HRCIR->font->_hoops_RACSR, _hoops_HRCIR->color, _hoops_HRCIR->rotation, count, kstring);
}


static bool
_hoops_AACSR(Display_Context alter * dc, char const *_hoops_PACSR)
{
	UNREFERENCED(dc);
	UNREFERENCED(_hoops_PACSR);
	_hoops_HPICR("\nfind_one_font\n");

	/* _hoops_HACSR _hoops_AAPA _hoops_PAPA _hoops_SR _hoops_PAH _hoops_AA _hoops_GII _hoops_HRCSR */
	return true;
}


#define _hoops_IACSR(x) (float)(1.0f/(x))
static void _hoops_CACSR(Display_Context alter * dc)
{
	_hoops_HPICR("\nfind_basic_fonts\n");
	HD_Record_Font_With_Encoding(dc, "Serif", "", _hoops_SACSR, 0.0f, _hoops_IACSR(0.7290));
	HD_Record_Font_With_Encoding(dc, "Times", "", _hoops_SACSR, 0.0f, _hoops_IACSR(0.6759));
	HD_Record_Font_With_Encoding(dc, "Courier", "", _hoops_SACSR, 0.0f, _hoops_IACSR(0.7290));
	HD_Mark_Font_As_Generic(dc, "Serif", GFN_SANS_SERIF);
	HD_Mark_Font_As_Generic(dc, "Times", GFN_ROMAN);
	HD_Mark_Font_As_Generic(dc, "Courier", GFN_TYPEWRITER);
	HD_Mark_Font_As_Transformable(dc, "Times", _hoops_GPCSR);
	HD_Mark_Font_As_Transformable(dc, "Serif", _hoops_GPCSR);
	HD_Mark_Font_As_Transformable(dc, "Courier", _hoops_GPCSR);
	return;
}


static const unsigned char _hoops_RPCSR[256 - 32] =
	{ 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149,
	149,
	149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149,
	149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149,
	149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149,
	149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149,
	149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149,
	149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149,
	149, 149, 149, 149, 149, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	149, 149, 149, 149, 149, 0, 149, 149, 0, 149, 149, 0, 149, 0, 149, 149,
	0, 0, 0, 149, 0, 149, 149, 149, 0, 149, 149, 0, 0, 0,
	149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149,
	149, 149, 149, 0, 149, 149, 149, 149, 149, 149, 0, 149,
	149, 149, 149, 149, 0, 0, 149, 149, 149, 149, 149, 149, 149, 149, 149,
	149, 149, 149, 149, 149, 149, 149, 149, 0, 149, 149,
	149, 149, 149, 149, 0, 149, 149, 149, 149, 149, 0, 0, 149,
};


static const unsigned char _hoops_APCSR[256 - 32] =
	{ 70, 78, 89, 138, 138, 220, 165, 56, 83, 83, 97, 145, 70, 83, 70, 70,
	138,
	138, 138, 138, 138, 138, 138, 138, 138, 138, 70, 70, 145, 145, 145,
	138, 250, 165, 165, 179, 179, 165, 152, 192, 179, 70,
	124, 165, 138, 206, 179, 192, 165, 192, 179, 165, 152, 179, 165, 233,
	165, 165, 152, 70, 70, 70, 117, 138, 56, 138, 138, 124,
	138, 138, 70, 138, 138, 56, 56, 124, 56, 206, 138, 138, 138, 138, 83,
	124, 70, 138, 124, 179, 124, 124, 124, 84, 66, 84, 145,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 83, 138, 138, 138, 138,
	0, 138, 83, 0, 93, 138, 0, 138, 0, 247, 83, 0, 0, 0, 83, 0, 133, 70,
	83, 0, 91, 138, 0, 0, 0, 152, 165, 165, 165, 165, 165,
	165, 247, 179, 165, 165, 165, 165, 70, 70, 70, 70, 0, 179, 192, 192,
	192, 192, 192, 0, 192, 179, 179, 179, 179, 0, 0, 152,
	138, 138, 138, 138, 138, 138, 220, 124, 138, 138, 138, 138, 70, 70, 70,
	70, 0, 138, 138, 138, 138, 138, 138, 0, 152, 138,
	138, 138, 138, 0, 0, 124,
};


static const unsigned char _hoops_PPCSR[256 - 32] =
	{ 63, 83, 102, 124, 124, 206, 192, 83, 83, 83, 124, 140, 63, 83, 63,
	70,
	124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 70, 70, 140, 140,
	140, 111, 227, 179, 165, 165, 179, 152, 138, 179, 179,
	83, 97, 179, 152, 220, 179, 179, 138, 179, 165, 138, 152, 179, 179,
	233, 179, 179, 152, 83, 70, 83, 117, 124, 83, 111, 124,
	111, 124, 111, 83, 124, 124, 70, 70, 124, 70, 192, 124, 124, 124, 124,
	83, 97, 70, 124, 124, 179, 124, 124, 111, 119, 51,
	119, 134, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 83, 124, 124,
	124, 124, 0, 124, 83, 0, 70, 124, 0, 124, 0, 247, 83, 0, 0, 0, 83, 0,
	113, 63, 83, 0, 78, 124, 0, 0, 0, 111, 179, 179, 179,
	179, 179, 179, 220, 165, 152, 152, 152, 152, 83, 83, 83, 83, 0, 179,
	179, 179, 179, 179, 179, 0, 179, 179, 179, 179, 179, 0,
	0, 124, 111, 111, 111, 111, 111, 111, 165, 111, 111, 111, 111, 111, 70,
	70, 70, 70, 0, 124, 124, 124, 124, 124, 124, 0, 124,
	124, 124, 124, 124, 0, 0, 124,
};


static const unsigned char _hoops_HPCSR[256 - 32] =
	{ 63, 83, 176, 124, 136, 206, 192, 109, 83, 83, 124, 136, 63, 136, 63,
	70,
	124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 70, 70, 136, 136,
	136, 111, 136, 179, 165, 179, 152, 152, 189, 150, 179, 83,
	156, 179, 170, 220, 179, 179, 190, 183, 138, 147, 152, 171, 109, 190,
	160, 197, 152, 83, 213, 83, 163, 124, 124, 156, 136,
	136, 123, 109, 130, 103, 150, 83, 150, 136, 136, 143, 130, 136, 136,
	130, 136, 150, 109, 143, 176, 170, 123, 170, 123, 119,
	51, 119, 136, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 154, 62,
	136, 43, 176, 124, 186, 186, 186, 186, 255, 244, 150, 244, 150, 100,
	136, 103, 136, 136, 176, 123, 115, 136, 136, 136, 136,
	247, 150, 247, 163, 203, 170, 197, 244, 190, 190, 203, 190, 190, 176,
	176, 176, 176, 176, 176, 176, 190, 176, 195, 195, 220,
	203, 136, 63, 176, 150, 150, 255, 244, 150, 244, 150, 123, 83, 195,
	195, 194, 176, 96, 96, 96, 96, 96, 96, 123, 123, 123, 123,
	0, 83, 69, 170, 170, 170, 96, 96, 96, 96, 96, 96, 123, 123, 123, 0,
};


static bool
measure_char(Net_Rendition const &nr,
		 Font_Instance const *instance, Karacter _hoops_IPCSR,
		 float alter * _hoops_GGGS, bool alter * _hoops_CPCSR,
		 void **_hoops_SPCSR)
{

	/* _hoops_GRISR _hoops_RAPC *_hoops_PIAP = _hoops_RRISR (_hoops_SCII->_hoops_GHCSR); */
	_hoops_PSISR *_hoops_RHCSR = (_hoops_PSISR *) instance->_hoops_GAASR;
	int index = _hoops_IPCSR & 0x00FF;
	UNREFERENCED(nr);
	_hoops_HPICR("\nmeasure_char\n");
	if (index >= 32 && _hoops_RHCSR->_hoops_HSISR[index - 32] > 0) {
		*_hoops_GGGS = ((float) _hoops_RHCSR->_hoops_HSISR[index - 32] * (_hoops_RHCSR->_hoops_ISISR) / 255.0);
		*_hoops_CPCSR = false;
	}
	else {
		*_hoops_GGGS = 0.0f;
		*_hoops_CPCSR = true;
	}
	*_hoops_SPCSR = (void *) 1;
	return (true);
}


static _hoops_PSISR *_hoops_AHCSR(_hoops_RGRSR alter * state,
				  int const _hoops_CSISR,
				  char const *const font_name,
				  unsigned char const *const _hoops_HSISR,
				  float const _hoops_ISISR)
{
	_hoops_PSISR *retval;
	UNREFERENCED(state);
	ALLOC(retval, _hoops_PSISR);
	retval->_hoops_CSISR = _hoops_CSISR;
	ALLOC_ARRAY(retval->_hoops_SSISR, _hoops_SSGR(font_name) + 1, char);
	COPY_MEMORY(font_name, _hoops_SSGR(font_name) + 1, retval->_hoops_SSISR);
	retval->_hoops_HSISR = _hoops_HSISR;
	retval->_hoops_ISISR = _hoops_ISISR;
	return (retval);
}


static void
_hoops_PHCSR(_hoops_RGRSR alter * state, _hoops_PSISR * const _hoops_RHCSR)
{
	UNREFERENCED(state);
	FREE_ARRAY(_hoops_RHCSR->_hoops_SSISR, _hoops_SSGR(_hoops_RHCSR->_hoops_SSISR) + 1, char);
	FREE(_hoops_RHCSR, _hoops_PSISR);
	return;
}


static void *load_font(Display_Context const *dc, char const *name,
			   Font_Instance alter * instance)
{
	_hoops_RGRSR alter *state = _hoops_GCRSR(dc);
	_hoops_PSISR *_hoops_RHCSR = (_hoops_PSISR *) 0;
	int _hoops_ISISR = (int) instance->_hoops_RACSR;
	_hoops_HPICR("\nload_font\n");
	switch (name[0]) {
		default:
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"unexpected character table");
			_hoops_HHHI;
		case 'C':
			_hoops_RHCSR = _hoops_AHCSR(state, _hoops_SIICR, "Courier", _hoops_RPCSR, _hoops_ISISR);
			break;
		case 'S':
			_hoops_RHCSR = _hoops_AHCSR(state, _hoops_IIICR, "Serif", _hoops_APCSR, _hoops_ISISR);
			break;
		case 'T':
			_hoops_RHCSR = _hoops_AHCSR(state, _hoops_CIICR, "Times-Roman", _hoops_PPCSR, _hoops_ISISR);
			break;
	}
	return ((void *) _hoops_RHCSR);
}


static void
unload_font(Display_Context const *dc, Font_Instance alter * instance)
{
	_hoops_RGRSR alter *state = _hoops_GCRSR(dc);
	_hoops_PSISR *_hoops_RHCSR = (_hoops_PSISR *) instance->_hoops_GAASR;
	_hoops_HPICR("\nunload_font\n");
	UNREFERENCED(dc);
	_hoops_PHCSR(state, _hoops_RHCSR);
	return;
}


static void
draw_dc_rgb32_rasters(Net_Rendition const &nr,
					  DC_Point const *start,
					  DC_Point const *end,
					  int row_bytes,
					  RGBAS32 const *rasters)
{
	_hoops_RGRSR alter *state = _hoops_RCRSR(nr);
	DC_Point _hoops_HHCSR, _hoops_IHCSR, _hoops_CHCSR;
	int _hoops_SHCSR, _hoops_GICSR;
	RGBAS32 const *row;
	_hoops_HPICR("\ndraw_dc_rgb32_rasters\n");
	_hoops_PCPSR(state, nr->transform_rendition);
	if (row_bytes == 0)
		row_bytes = ((int) (end->x - start->x) + 1) * sizeof(RGBAS32);
	_hoops_SHCSR = (int) (end->x - start->x) + 1;
	_hoops_GICSR = (int) (start->y - end->y) + 1;
	_hoops_HHCSR.x = start->x;
	_hoops_HHCSR.y = start->y;
	_hoops_HHCSR.z = 0.0f;
	_hoops_IHCSR.x = end->x + 1.0f;
	_hoops_IHCSR.y = end->y + 1.0f;
	_hoops_IHCSR.z = 0.0f;
	_hoops_CHCSR.x = end->x + 1.0f;
	_hoops_CHCSR.y = start->y;
	_hoops_CHCSR.z = 0.0f;
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			int _hoops_RICSR;
			_hoops_RICSR = 32 + (_hoops_SHCSR * _hoops_GICSR * 3);
			_hoops_AAASR(state, _hoops_CGSCR, _hoops_SRSCR, (unsigned short) _hoops_RICSR);
			_hoops_RAASR(state, &_hoops_HHCSR, 1);
			_hoops_RAASR(state, &_hoops_IHCSR, 1);
			_hoops_RAASR(state, &_hoops_CHCSR, 1);
			_hoops_GGASR(state, (unsigned short) _hoops_SHCSR);
			_hoops_GGASR(state, (unsigned short) _hoops_GICSR);
			_hoops_GGASR(state, (unsigned short) 0);
			_hoops_GGASR(state, (unsigned char) 1);

			/* _hoops_AICSR: _hoops_HAIR _hoops_HSH */
			row = rasters;
			while (_hoops_GICSR-- > 0) {
				RGBAS32 const *_hoops_PICSR, *_hoops_HICSR;
				_hoops_PICSR = row;
				_hoops_HICSR = row + _hoops_SHCSR;
				while (row < _hoops_HICSR) {
					_hoops_ISRSR(state, (unsigned char) row->r);
					_hoops_ISRSR(state, (unsigned char) row->g);
					_hoops_ISRSR(state, (unsigned char) row->b);
					row++;
				}
				row = (RGBAS32 const *) ((unsigned char const *) _hoops_PICSR + row_bytes);
			}
			if (_hoops_RICSR % 2 == 1)
				_hoops_ISRSR(state, (unsigned char) 0);
		}	break;
		case _hoops_SHICR: {
			Sprintf_FF(state->_hoops_IGRSR, "CELLARRAY (%f,%f) ", _hoops_HHCSR.x, _hoops_HHCSR.y);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
			Sprintf_FF(state->_hoops_IGRSR, "(%f,%f) ", _hoops_IHCSR.x, _hoops_IHCSR.y);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
			Sprintf_FF(state->_hoops_IGRSR, "(%f,%f) ", _hoops_CHCSR.x, _hoops_CHCSR.y);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
			Sprintf_DD(state->_hoops_IGRSR, "%d %d 0", _hoops_SHCSR, _hoops_GICSR);
			_hoops_CSRSR(state, state->_hoops_IGRSR);

			/* _hoops_HAIR _hoops_HSH */
			row = rasters;
			while (_hoops_GICSR-- > 0) {
				RGBAS32 const *_hoops_PICSR, *_hoops_HICSR;
				_hoops_PICSR = row;
				_hoops_HICSR = row + _hoops_SHCSR;
				while (row < _hoops_HICSR) {
					Sprintf_DD(state->_hoops_PGRSR, "\n (%d,%d,",
						(int) row->r, (int) row->g);
					Sprintf_SD(state->_hoops_IGRSR, "%s%d)",
						state->_hoops_PGRSR, (int) row->b);
					_hoops_CSRSR(state, state->_hoops_IGRSR);
					row++;
				}
				row = (RGBAS32 const *) ((unsigned char const *) _hoops_PICSR + row_bytes);
			}
			_hoops_CSRSR(state, ";\n");
		}	break;
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in draw direct cell array");
		}	break;
	}
}


static void
draw_window(Net_Rendition const &nr, Int_Rectangle const *extent)
{
	_hoops_CGRA const &_hoops_SGRA = nr->_hoops_SAIR;
	Image const *image = null;
	_hoops_RCR *_hoops_IICSR = null;
	_hoops_AIGH *rasters;
	_hoops_RGRSR alter *state = _hoops_RCRSR(nr);
	DC_Point _hoops_HHCSR, _hoops_IHCSR, _hoops_CHCSR;
	int _hoops_SHCSR, _hoops_GICSR;
	_hoops_CPAIR _hoops_CICSR;

	_hoops_HPICR("\ndraw_window\n");

	if (_hoops_SGRA->_hoops_PGPH != null || _hoops_SGRA->_hoops_SICSR == null) {
		HD_Standard_Draw_Window(nr, extent);
		return;
	}

	if (nr->_hoops_GCCSR->count > 0) {
		_hoops_CICSR.textures = nr->_hoops_GCCSR->textures;
		_hoops_CICSR.keys = nr->_hoops_GCCSR->keys;
		_hoops_CICSR.count = nr->_hoops_GCCSR->count;
	}
	else {
		_hoops_CICSR.textures = 0;
		_hoops_CICSR.keys = 0;
		_hoops_CICSR.count = 0;
	}

	if ((_hoops_IICSR = HI_Activate_Texture ((_hoops_RCR alter *) _hoops_SGRA->_hoops_SICSR, &_hoops_CICSR, false)) != null) {
		image = _hoops_IICSR->image;
	}

	if (image == null) {
		HD_Standard_Draw_Window (nr, extent);
		goto _hoops_RCCSR;
	}

	if (_hoops_IICSR == null || BIT (_hoops_IICSR->flags, _hoops_AIA)) {
		HD_Standard_Draw_Window (nr, extent);
		goto _hoops_RCCSR;
	}

	rasters = *(_hoops_AIGH **) image->rasters;
	_hoops_SHCSR = image->width;
	_hoops_GICSR = image->height;
	_hoops_HHCSR.x = extent->left;
	_hoops_HHCSR.y = extent->top;
	_hoops_HHCSR.z = 0.0f;
	_hoops_IHCSR.x = extent->right;
	_hoops_IHCSR.y = extent->bottom;
	_hoops_IHCSR.z = 0.0f;
	_hoops_CHCSR.x = extent->right;
	_hoops_CHCSR.y = extent->top;
	_hoops_CHCSR.z = 0.0f;

	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			int _hoops_RICSR;
			_hoops_RICSR = 32 + (_hoops_SHCSR * _hoops_GICSR * 3);
			_hoops_AAASR(state, _hoops_CGSCR, _hoops_SRSCR, (unsigned short) _hoops_RICSR);
			_hoops_RAASR(state, &_hoops_HHCSR, 1);
			_hoops_RAASR(state, &_hoops_IHCSR, 1);
			_hoops_RAASR(state, &_hoops_CHCSR, 1);
			_hoops_GGASR(state, (unsigned short) _hoops_SHCSR);
			_hoops_GGASR(state, (unsigned short) _hoops_GICSR);
			_hoops_GGASR(state, (unsigned short) 0);
			_hoops_GGASR(state, (unsigned char) 1);

			/* _hoops_AICSR: _hoops_HAIR _hoops_HSH */
			while (_hoops_GICSR--) {
				int _hoops_ACCSR = _hoops_SHCSR;
				while (_hoops_ACCSR--) {
					_hoops_ISRSR(state, (unsigned char) rasters->r);
					_hoops_ISRSR(state, (unsigned char) rasters->g);
					_hoops_ISRSR(state, (unsigned char) rasters->b);
					++rasters;
				}
			}
			if (_hoops_RICSR % 2 == 1)
				_hoops_ISRSR(state, (unsigned char) 0);
		}	break;

		case _hoops_SHICR: {
			Sprintf_FF(state->_hoops_IGRSR, "CELLARRAY (%f,%f) ", _hoops_HHCSR.x, _hoops_HHCSR.y);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
			Sprintf_FF(state->_hoops_IGRSR, "(%f,%f) ", _hoops_IHCSR.x, _hoops_IHCSR.y);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
			Sprintf_FF(state->_hoops_IGRSR, "(%f,%f) ", _hoops_CHCSR.x, _hoops_CHCSR.y);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
			Sprintf_DD(state->_hoops_IGRSR, "%d %d 0", _hoops_SHCSR, _hoops_GICSR);
			_hoops_CSRSR(state, state->_hoops_IGRSR);

			/* _hoops_HAIR _hoops_HSH */
			while (_hoops_GICSR--) {
				int _hoops_ACCSR = _hoops_SHCSR;
				while (_hoops_ACCSR--) {
					Sprintf_DD(state->_hoops_PGRSR, "\n\t(%d,%d,",
						(int) rasters->r, (int) rasters->g);
					Sprintf_SD(state->_hoops_IGRSR, "%s%d)",
						state->_hoops_PGRSR, (int) rasters->b);
					_hoops_CSRSR(state, state->_hoops_IGRSR);
					++rasters;
				}
			}
			_hoops_CSRSR(state, ";\n");
		}	break;

		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in draw direct cell array");
		}	break;
	}

_hoops_RCCSR:
	if (_hoops_IICSR)
		_hoops_HPRH (_hoops_IICSR);
	return;
}


/* _hoops_PGAA (_hoops_SIHR _hoops_RCICR _hoops_AGHS) */
static void
_hoops_PCCSR(Net_Rendition const &nr,
					   DC_Point const *start,
					   DC_Point const *end,
					   int row_bytes,
					   unsigned char const *array)
{
	_hoops_RGRSR alter *state = _hoops_RCRSR(nr);
	DC_Point _hoops_HHCSR, _hoops_IHCSR, _hoops_CHCSR;
	int _hoops_SHCSR, _hoops_GICSR;
	unsigned char const *row;
	_hoops_HPICR("draw_mapped_cell_array\n");
	_hoops_SHCSR = (int) (end->x - start->x) + 1;
	_hoops_GICSR = (int) (start->y - end->y) + 1;
	_hoops_HHCSR.x = start->x;
	_hoops_HHCSR.y = start->y;
	_hoops_HHCSR.z = 0.0f;
	_hoops_IHCSR.x = end->x + 1.0f;
	_hoops_IHCSR.y = end->y + 1.0f;
	_hoops_IHCSR.z = 0.0f;
	_hoops_CHCSR.x = end->x + 1.0f;
	_hoops_CHCSR.y = start->y;
	_hoops_CHCSR.z = 0.0f;
	switch (state->_hoops_GRRSR) {
		case _hoops_CHICR: {
			int _hoops_RICSR;

			/* _hoops_HCCSR _hoops_ICCSR */
			_hoops_RICSR = 32 + (_hoops_SHCSR * _hoops_GICSR);
			_hoops_AAASR(state, _hoops_CGSCR, _hoops_SRSCR, (unsigned short) _hoops_RICSR);
			_hoops_RAASR(state, &_hoops_HHCSR, 1);
			_hoops_RAASR(state, &_hoops_IHCSR, 1);
			_hoops_RAASR(state, &_hoops_CHCSR, 1);
			_hoops_GGASR(state, (unsigned short) _hoops_SHCSR);
			_hoops_GGASR(state, (unsigned short) _hoops_GICSR);
			_hoops_GGASR(state, (unsigned short) 0);
			_hoops_GGASR(state, (unsigned char) 1);

			row = array;
			while (_hoops_GICSR-- > 0) {
				unsigned char const *_hoops_PICSR, *_hoops_HICSR;
				_hoops_PICSR = row;
				_hoops_HICSR = row + _hoops_SHCSR;
				while (row < _hoops_HICSR)
					_hoops_ISRSR(state, state->_hoops_CSIR[*row++]._hoops_RPRSR);
				row = (unsigned char const *) (_hoops_PICSR + row_bytes);
			}
			if (_hoops_RICSR % 2 == 1)
				_hoops_ISRSR(state, (unsigned char) 0);
		}	break;

		case _hoops_SHICR: {
			/* _hoops_HCCSR _hoops_ICCSR */
			Sprintf_FF(state->_hoops_IGRSR, "CELLARRAY (%f,%f) ", _hoops_HHCSR.x, _hoops_HHCSR.y);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
			Sprintf_FF(state->_hoops_IGRSR, "(%f,%f) ", _hoops_IHCSR.x, _hoops_IHCSR.y);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
			Sprintf_FF(state->_hoops_IGRSR, "(%f,%f) ", _hoops_CHCSR.x, _hoops_CHCSR.y);
			_hoops_CSRSR(state, state->_hoops_IGRSR);
			Sprintf_DD(state->_hoops_IGRSR, "%d %d 0", _hoops_SHCSR, _hoops_GICSR);
			_hoops_CSRSR(state, state->_hoops_IGRSR);

			/* _hoops_HAIR _hoops_HSH */
			row = array;
			while (_hoops_GICSR-- > 0) {
				unsigned char const *_hoops_PICSR, *_hoops_HICSR;
				_hoops_PICSR = row;
				_hoops_HICSR = row + _hoops_SHCSR;
				while (row < _hoops_HICSR) {
					Sprintf_D(state->_hoops_IGRSR, "\n %d", (int) state->_hoops_CSIR[*row++]._hoops_RPRSR);
					_hoops_CSRSR(state, state->_hoops_IGRSR);
				}
				row = (unsigned char const *) (_hoops_PICSR + row_bytes);
			}
			_hoops_CSRSR(state, ";\n");
		}	break;

		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Invalid encoding in draw mapped cell array");
		}	break;
	}
	state->_hoops_CSC.colors[LINE_COLOR] = state->_hoops_CSC.colors[FILL_COLOR] =
		_hoops_CAHSR::_hoops_SAHSR;
}


/* _hoops_SRAC (_hoops_RCICR _hoops_RPCC-_hoops_HIAGR) */
static void
_hoops_CCCSR(Net_Rendition const &nr, DC_Point const *start,
			DC_Point const *end, int row_bytes,
			unsigned char const *rasters)
{
	_hoops_HHCR const &_hoops_IHCR = nr->transform_rendition;
	_hoops_RGRSR alter *state = _hoops_RCRSR(nr);
	_hoops_HPICR("\ndraw_dc_mapped8_rasters\n");
	if (row_bytes == 0)
		row_bytes = ((int) (end->x - start->x) + 1) * sizeof(unsigned char);
	_hoops_PCPSR(state, _hoops_IHCR);
	_hoops_PCCSR(nr, start, end, row_bytes, rasters);
}


/* _hoops_SRAC (_hoops_RCICR _hoops_RPCC-_hoops_HIAGR) */
static void
_hoops_SCCSR(Display_Context const *dc, unsigned int r,
			 unsigned int g, unsigned int b, int index)
{
	_hoops_RGRSR alter *state = _hoops_GCRSR(dc);
	_hoops_HPICR("\nset_device_color_map\n");

	/* _hoops_RGAR _hoops_IRS _hoops_CCAH _hoops_HAIR _hoops_RPP _hoops_SCH _hoops_CCACR'_hoops_RA _hoops_RPII _hoops_ARP, _hoops_IAII _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_HIAP */
	if (!state->_hoops_CSIR[index].set) {
		state->_hoops_RRRSR++;
	}

	/* _hoops_ASH _hoops_SGGR _hoops_HIS _hoops_SR _hoops_PAH _hoops_GSCSR _hoops_GGSR _hoops_HPGR _hoops_SPR _hoops_GHIR _hoops_GGR _hoops_IHPI _hoops_RPISR */
	state->_hoops_CSIR[index].color._hoops_HRIR.r = r;
	state->_hoops_CSIR[index].color._hoops_HRIR.g = g;
	state->_hoops_CSIR[index].color._hoops_HRIR.b = b;
	state->_hoops_CSIR[index].color._hoops_HRIR.a = 0;
	state->_hoops_CSIR[index].set = true;
}


static void _hoops_IRHSR(_hoops_APARR alter & _hoops_RRCI)
{
	_hoops_HPICR("\nget_actions\n");

	_hoops_RRCI->draw_dc_gouraud_polytriangle = draw_dc_gouraud_polytriangle;
	_hoops_RRCI->draw_3d_nurbs_curve = draw_3d_nurbs_curve;

	_hoops_RRCI->draw_window = draw_window;
	_hoops_RRCI->draw_dc_text = draw_dc_text;
	_hoops_RRCI->_hoops_AGCSR = _hoops_AGCSR;
	_hoops_RRCI->_hoops_CACSR = _hoops_CACSR;
	_hoops_RRCI->measure_char = measure_char;
	_hoops_RRCI->load_font = load_font;
	_hoops_RRCI->unload_font = unload_font;
	_hoops_RRCI->_hoops_AACSR = _hoops_AACSR;
}


static void
_hoops_CRHSR(_hoops_APARR alter & _hoops_RRCI)
{
	_hoops_HPICR("\nget_actions\n");
	_hoops_RRCI->_hoops_CCCSR = _hoops_CCCSR;
	_hoops_RRCI->_hoops_SCCSR = _hoops_SCCSR;
}


static void
_hoops_RSCSR(_hoops_APARR alter & _hoops_RRCI)
{
	_hoops_RRCI->start_device = start_device;
	_hoops_RRCI->stop_device = stop_device;
	_hoops_RRCI->get_physical_info = get_physical_info;
	_hoops_RRCI->get_current_info = get_current_info;
	_hoops_RRCI->init_picture = init_picture;
	_hoops_RRCI->finish_picture = finish_picture;
	_hoops_RRCI->get_outer_window = get_outer_window;

	_hoops_RRCI->draw_3d_elliptical_arc = draw_3d_elliptical_arc;
	_hoops_RRCI->draw_3d_ellipse = draw_3d_ellipse;
	_hoops_RRCI->draw_3d_marker = draw_3d_marker;

	_hoops_RRCI->_hoops_CCISR = _hoops_CCISR;
	_hoops_RRCI->draw_dc_ellipse = draw_dc_ellipse;
	_hoops_RRCI->_hoops_SCISR = _hoops_SCISR;
	_hoops_RRCI->draw_dc_polyline = draw_dc_polyline;
	_hoops_RRCI->draw_dc_face = draw_dc_face;
	_hoops_RRCI->draw_dc_colorized_face = draw_dc_colorized_face;
	_hoops_RRCI->draw_dc_polytriangle = draw_dc_polytriangle;
	_hoops_RRCI->draw_dc_colorized_polytriangle = draw_dc_colorized_polytriangle;
	_hoops_RRCI->draw_dc_rectangle = draw_dc_rectangle;
	_hoops_RRCI->draw_dc_polydot = draw_dc_polydot;

	_hoops_RRCI->draw_dc_rgb32_rasters = draw_dc_rgb32_rasters;
}

extern "C"  bool HC_CDECL HD_CGM3_Driver (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (request_info);
	return HD_Connect_Standard_Driver (_hoops_RIGC, _hoops_GHRI, request, _hoops_RSCSR);
}


/* _hoops_ASCSR _hoops_RARP _hoops_PPSR (_hoops_IGI _hoops_GPP _hoops_PSCSR) */
_hoops_HSCSR(_hoops_RSCSR);




#endif				/* _hoops_ISCSR */

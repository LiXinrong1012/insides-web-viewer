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
 * $Id: obf_tmp.txt 1.103 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "searchh.h"
#include "hpserror.h"
#include "patterns.h"
#include "driver.h"
#include "hd_proto.h"

/* _hoops_PIHA _hoops_PSSP _hoops_AGR _hoops_GGR _hoops_HSGP._hoops_GGHR */
local const char * _hoops_GPIPI[] = {
	"-", "-.", "- -", ".", "-..", "-...", "-- --", "center", "phantom", "finedot"}; 

#define _hoops_RPIPI 7
local const char * _hoops_APIPI[_hoops_RPIPI] = {
"-------------------------------------------------------------------------------", 
"...............................................................................", 
"-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.", 
"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- - - - - - - - ", 
"-..-..-..-..-..-..-..-..-..-..-..-..-..-..-..-..-..-..-..-..-..-..-..-..-..-..-", 
"-...-...-...-...-...-...-...-...-...-...-...-...-...-...-...-..-...-...-...-...", 
"-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -"
}; 

local int _hoops_PPIPI[_hoops_RPIPI] = {1,1,2,2,3,4,3};
local int _hoops_HPIPI[_hoops_RPIPI] = {0,3,1,2,4,5,6};


local void find_line_extras (
	char const		*string,
	int				length,
	short			*_hoops_HHCAP,
	int				*_hoops_ISRAA,
	int				*_hoops_SIPI) {
	
	int i=0;

	*_hoops_HHCAP=*_hoops_ISRAA=*_hoops_SIPI=0;
	
	while (i<length && string[i] == ' ') i++;

	switch (string[i]) {
		case '|': *_hoops_HHCAP |= LCAP_BUTT; i++; *_hoops_ISRAA=i; break;
		case '(':
		case ')': *_hoops_HHCAP |= LCAP_ROUND; i++; *_hoops_ISRAA=i ;break;
		case '[':
		case ']': *_hoops_HHCAP |= LCAP_SQUARE; i++; *_hoops_ISRAA=i; break;
		case '<':
		case '>': *_hoops_HHCAP |= LCAP_TRIANGLE; i++; *_hoops_ISRAA=i; break;
		default:break;
	}

	switch (string[i]) {
		case '|': *_hoops_HHCAP |= LCAP_END_BUTT; i++; *_hoops_ISRAA=i; break;
		case '(':
		case ')': *_hoops_HHCAP |= LCAP_END_ROUND; i++; *_hoops_ISRAA=i ;break;
		case '[':
		case ']': *_hoops_HHCAP |= LCAP_END_SQUARE; i++; *_hoops_ISRAA=i; break;
		case '<':
		case '>': *_hoops_HHCAP |= LCAP_END_TRIANGLE; i++; *_hoops_ISRAA=i; break;
		default:break;
	}

	if ((*_hoops_HHCAP & LCAP_MASK) == LCAP_BUTT && 
		(*_hoops_HHCAP & LCAP_END_MASK)== LCAP_END_BUTT)
		*_hoops_HHCAP &= ~LCAP_END_BUTT;
	if ((*_hoops_HHCAP & LCAP_MASK) == LCAP_ROUND && 
		(*_hoops_HHCAP & LCAP_END_MASK) == LCAP_END_ROUND)
		*_hoops_HHCAP &= ~LCAP_END_ROUND;
	if ((*_hoops_HHCAP & LCAP_MASK) == LCAP_SQUARE && 
		(*_hoops_HHCAP & LCAP_END_MASK) == LCAP_END_SQUARE)
		*_hoops_HHCAP &= ~LCAP_END_SQUARE;
	if ((*_hoops_HHCAP & LCAP_MASK) == LCAP_TRIANGLE && 
		(*_hoops_HHCAP & LCAP_END_MASK) == LCAP_END_TRIANGLE)
		*_hoops_HHCAP &= ~LCAP_END_TRIANGLE;

	i=length-1;

	while (i>0 && string[i] == ' ') i--;

	switch (string[i]) {
		case '@': *_hoops_HHCAP |= LPAT_ROUND; i--; *_hoops_SIPI=length-1-i; break;
		case '#': *_hoops_HHCAP |= LPAT_SQUARE; i--; *_hoops_SIPI=length-1-i; break;
		case '^': *_hoops_HHCAP |= LPAT_TRIANGLE; i--; *_hoops_SIPI=length-1-i; break;
		default:break;
	}
	switch (string[i]) {
		case '>':
		case '<': *_hoops_HHCAP |= LJOIN_MITER; i--; *_hoops_SIPI=length-1-i; break;
		case ')':
		case '(': *_hoops_HHCAP |= LJOIN_ROUND; i--; *_hoops_SIPI=length-1-i; break;
		case '|':
		case '[':
		case ']': *_hoops_HHCAP |= LJOIN_BEVEL; i--; *_hoops_SIPI=length-1-i; break;
		default:break;
	}
}

GLOBAL_FUNCTION void HI_Canonize_Line_Pattern(
	char const		*_hoops_IPIPI,
	_hoops_HCRPR			*name,
	Integer32		*_hoops_CPIPI) {

	int _hoops_ISRAA, _hoops_SIPI;
	int length;
	short _hoops_HHCAP;
	char string_data[1024];
	char *string = string_data;
	

	if (!_hoops_IPIPI) {
		if (name) {
			name->text=0;
			name->length=0;
		}
		return;
	}

	_hoops_AAHR(_hoops_IPIPI, string);

	length = _hoops_SSGR(string);

	find_line_extras (string, length, &_hoops_HHCAP, &_hoops_ISRAA, &_hoops_SIPI);

	if (_hoops_CPIPI)
		*_hoops_CPIPI = _hoops_HHCAP;

	if (!name)
		return;

	length -= _hoops_ISRAA+_hoops_SIPI; 
	string += _hoops_ISRAA;

	string[length] = '\0';

	if (length > 0 && (string[0] == '-' || string[0] == ' ' || string[0] == '.')) {

		int i,j;

		for (i=0;i<_hoops_RPIPI;i++) {
			for (j=0;j<_hoops_PPIPI[i];j++) {
				if (_hoops_GPPSA(string, length, &_hoops_APIPI[i][j])) {
					HI_Canonize_Chars(_hoops_GPIPI[_hoops_HPIPI[i]], name);
					return;
				}
			}
		}
	}

	if (length == 1 && string[0] >= '0' && string[0] <= '9') {
		HI_Canonize_Chars(_hoops_GPIPI[string[0]-'0'], name); 
		return;
	}

	HI_Canonize_Chars(string, name);
	return;
}

GLOBAL_FUNCTION Line_Style HD_Find_Line_Style_Legacy (
	Net_Rendition const &		nr,
	char						pattern) {

	if (pattern < LP_SOLID || pattern > LP_FINEDOT)
		pattern = LP_SOLID;

	return HD_Find_Line_Style(nr, _hoops_GPIPI[(int)pattern]);
}

GLOBAL_FUNCTION char HD_Find_Line_Style_Legacy_P (
	Line_Style const &	line_style) {

	for (int i=LP_SOLID; i<LP_FINEDOT; i++) 
		if (_hoops_AGGR(_hoops_GPIPI[i], line_style->name.text))
			return i;

	return MK_DOT;
}

GLOBAL_FUNCTION Line_Style HD_Find_Line_Style (
	Net_Rendition const &		nr,
	const char *				name) {
	_hoops_HCRPR						_hoops_SPIPI;
	int							i;

	HI_Canonize_Line_Pattern(name, &_hoops_SPIPI, 0);

	for (i=0; i<nr->_hoops_GCSHP->count; i++) {
		if (_hoops_AGGR(_hoops_SPIPI.text, nr->_hoops_GCSHP->_hoops_HPAIR[i]->name.text)) {
			_hoops_RGAIR(_hoops_SPIPI);
			return nr->_hoops_GCSHP->_hoops_HPAIR[i];
		}
	}

	_hoops_RGAIR(_hoops_SPIPI);

	return null;
}




#if 0
local const unsigned short
		_hoops_HASHH[]			= {0,	0,								0},		/*--------------------------------*/
		_hoops_GHIPI[]		= {4,	18, 5, 4, 5,					0},		/*------------------	 ----	  */
		_hoops_RHIPI[]		= {2,	10, 6,							0},		/*----------	  ----------	  */
		_hoops_AHIPI[]		= {2,	5, 3,							0},		/*---	  ---	  ---	  ---	  */
		_hoops_PHIPI[]		= {6,	15, 4, 3, 3, 3, 4,				0},		/*---------------	 ---   ---	  */
		_hoops_HHIPI[]		= {8,	15, 2, 3, 2, 3, 2, 3, 2,		0},		/*---------------  ---	---	 ---  */
		_hoops_IHIPI[]		= {2,	26, 6,							0},		/*--------------------------	  */
		center[]		= {4,	100, 10, 20, 10,				0},		/*----------------------  ------  */
		_hoops_CHIPI[]		= {6,	86, 8, 15, 8, 15, 8,			0},		/*--------------  ------  ------  */
		_hoops_SHIPI[]		= {2,	1, 3,							0};		/*-	  -	  -	  -	  -	  -	  -	  -	  */
/* _hoops_RPCC _hoops_HRGR:			 _hoops_RPR	   _hoops_CGISH				   _hoops_ISHRH */
#endif

local void _hoops_GIIPI (
	Line_Style alter &			line_style,
	Line_Style_Parallel *		_hoops_RIIPI,
	int							_hoops_AIIPI) {
	int 						_hoops_PIIPI;
	int 						count;
	int 						total, _hoops_HIIPI, d;
	int 						_hoops_IIIPI;
	int 						start, end;
	int 						i;
	unsigned int				result;
	int 						scale;
	int 						scaled;
	bool						_hoops_CIIPI;
	int *						pattern;

	count = _hoops_RIIPI->_hoops_RHISR;
	ALLOC_ARRAY(pattern, count, int);
	_hoops_AIGA(_hoops_RIIPI->pattern, count, int, pattern);

	/* _hoops_PSRAR _hoops_HSGP _hoops_IS _hoops_PSHSH _hoops_SRSGR */
	scaled = 1;
	d=2;
	_hoops_HIIPI = _hoops_IICIA;
	while (_hoops_HIIPI>=d) {

		while (1) {
			for (i=0; i<count; ++i) 
				if (pattern[i]%d != 0) goto _hoops_SIIPI;

			for (i=0; i<count; ++i) 
				pattern[i] = pattern[i]/d;

			scaled *= d;
		}

_hoops_SIIPI:
		
		for (i=0; i<count; ++i) 
			if (pattern[i] < _hoops_HIIPI) _hoops_HIIPI=pattern[i];

		d++;
	}

	total = 0;
	for (i=0; i<count; ++i) 
		total += pattern[i];

	/* _hoops_RARIR _hoops_SIH _hoops_RPP _hoops_SCH _hoops_HRGR _hoops_HAR _hoops_CPIC _hoops_IPHR _hoops_PSCR _hoops_SHSP */
	if (total>_hoops_AIIPI)
		if (total%_hoops_AIIPI != 0) goto _hoops_RCCSR;
	else
		if (_hoops_AIIPI%total != 0) goto _hoops_RCCSR;

	/* _hoops_CAHP _hoops_SIH */
	if (total < _hoops_AIIPI) {
		_hoops_PIIPI = 2;
		while (_hoops_PIIPI < total)
			_hoops_PIIPI <<= 1;
		scale = scaled;
	}
	else {
		_hoops_PIIPI = _hoops_AIIPI;
		scale = (total + (_hoops_AIIPI >> 2)) / _hoops_AIIPI;
		scale *= scaled;
	}

	start = 0;
	_hoops_IIIPI = 0;
	_hoops_CIIPI = true;
	result = 0;
	for (i=0; i<count; ++i) {
		_hoops_IIIPI += (int)pattern[i];
		end = (_hoops_PIIPI * _hoops_IIIPI + total/2) / total;
		if (_hoops_CIIPI) {
			while (start < end)
				result |= 1 << start++;
		}
		else
			start = end;
		_hoops_CIIPI = !_hoops_CIIPI;
	}

	while (_hoops_PIIPI < _hoops_AIIPI) {
		/* _hoops_HSGP _hoops_CSAP _hoops_PAPR _hoops_ICHRR, _hoops_GCIPI _hoops_SCH _hoops_IS _hoops_CISA _hoops_RCIPI */
		result |= result << _hoops_PIIPI;
		_hoops_PIIPI += _hoops_PIIPI;
	}

	if (_hoops_AIIPI == 16) {
		line_style->flags |= LSF_BITS16;
		line_style->_hoops_SPCAP = 0x0000FFFF & result;
		line_style->_hoops_CPCAP = scale;

	}
	else if (_hoops_AIIPI == 32) {
		line_style->flags |= LSF_BITS32;
		line_style->bits32 = result;
		line_style->scale32 = scale;
	}

_hoops_RCCSR:
	FREE_ARRAY(pattern, count, int);

}

GLOBAL_FUNCTION Line_Style HD_Define_Line_Style_Legacy (
	Net_Rendition const &		nr,
	void *						pointer,
	int 						_hoops_CHHIH,
	int 						_hoops_SHHIH,
	bool						_hoops_GIHIH) {
	Line_Style					line_style;
	int							length = _hoops_CHHIH;
	int *						pattern;
	int							i;

	UNREFERENCED(nr);

	if (length <= 0) {
		HE_ERROR (HEC_POLYLINE, HES_INVALID_LIST_LENGTH,
		"User-defined line pattern length is unreasonable");
		return null;
	}

	line_style =  Line_Style::Create();

	ZALLOC (line_style->_hoops_GHISR, Line_Style_Parallel);
	line_style->_hoops_IPCAP=1;

	ALLOC_ARRAY (pattern, length, int);
	line_style->_hoops_GHISR[0].pattern = pattern;
	line_style->_hoops_GHISR[0]._hoops_RHISR = length;

	if (_hoops_GIHIH) {
		unsigned short const *input = (unsigned short *)pointer;

		for (i=0; i<length; i++)
			*pattern++ = *input++;
	}
	else {
		unsigned char const *input = (unsigned char *)pointer;

		for (i=0; i<length; i++)
			*pattern++ = (unsigned short)*input++;
	}

	_hoops_GIIPI (line_style, line_style->_hoops_GHISR, 32);
	_hoops_GIIPI (line_style, line_style->_hoops_GHISR, 16);

	if (_hoops_SHHIH != 0) {
		line_style->_hoops_GHISR[0].flags |= LSF_ABSOLUTE_LENGTH;
		line_style->flags |= LSF_ABSOLUTE_LENGTH;
	}

	return line_style;
}

INLINE Line_Style_Item * _hoops_ACIPI(
	Line_Style_Item *	_hoops_PCIPI, 
	const char *		name, 
	float				rotation,
	float				_hoops_HCIPI,
	_hoops_GIGRP	_hoops_ICIPI,
	bool				_hoops_CCIPI, 
	bool				_hoops_SCIPI, 
	bool				_hoops_GSIPI, 
	bool				_hoops_RSIPI,
	bool				_hoops_ASIPI, 
	float				value, 
	bool				_hoops_PSIPI, 
	_hoops_GIGRP	_hoops_HHP) 
{

	Line_Style_Item * _hoops_HSIPI = _hoops_PCIPI;

	if (!_hoops_HSIPI)
		ZALLOC(_hoops_HSIPI, Line_Style_Item);
	HI_Canonize_Chars (name, &_hoops_HSIPI->name);

	_hoops_HCARA(_hoops_HSIPI->name, _hoops_HSIPI->key);

	if (rotation != 0.0f) {
		_hoops_HSIPI->rotation = rotation;
		_hoops_HSIPI->flags |= _hoops_HACAP;
	}

	if (_hoops_HCIPI != 0.0f) {
		_hoops_HSIPI->weight.value = _hoops_HCIPI;
		_hoops_HSIPI->weight._hoops_HHP = _hoops_ICIPI;
		_hoops_HSIPI->flags |= _hoops_IACAP;
	}

	if (_hoops_CCIPI) 
		_hoops_HSIPI->flags |= _hoops_RACAP;
	if (_hoops_SCIPI) 
		_hoops_HSIPI->flags |= _hoops_GACAP;
	if (_hoops_GSIPI) 
		_hoops_HSIPI->flags |= _hoops_AACAP;
	if (_hoops_RSIPI) 
		_hoops_HSIPI->flags |= _hoops_PACAP;

	if (_hoops_ASIPI) {
		_hoops_HSIPI->size.value = (value);
		if (_hoops_PSIPI)
			_hoops_HSIPI->size._hoops_HHP = _hoops_HHP;
		else
			_hoops_HSIPI->size._hoops_HHP = GSU_PIXELS;
	}

	return _hoops_HSIPI;
}


local bool _hoops_ISIPI (
	_hoops_AIGPR *	_hoops_RIGC,
	Line_Style_Parallel *	_hoops_RIIPI, 
	char const **			_hoops_CSIPI, 
	char const *			_hoops_SSRPR, 
	bool *					_hoops_SSIPI, 
	bool *					_hoops_GGCPI, 
	bool *					_hoops_RGCPI,
	float *					_hoops_AGCPI,
	float *					_hoops_PGCPI,
	bool *					_hoops_ASIPI, 
	float					value, 
	bool *					_hoops_PSIPI, 
	_hoops_GIGRP		_hoops_HHP,
	int *					pattern,
	int *					length,
	Line_Style_Item *		pattern_items,
	int	 *					pattern_items_n) 
{
	bool					_hoops_CCIPI = false;
	bool					_hoops_SCIPI = false;
	bool					_hoops_GSIPI = false;
	bool					_hoops_RSIPI = false;
	float					rotation = 0.0f;
	float					_hoops_HCIPI = 0.0f;	
	_hoops_GIGRP		_hoops_ICIPI = GSU_PIXELS;	
	char					buffer[4096];
	char const *			_hoops_RPPA = *_hoops_CSIPI;
	char const *			_hoops_HRCAR;

	while (_hoops_RPPA < _hoops_SSRPR && (*_hoops_RPPA == ' ')) 
		_hoops_RPPA++;

	_hoops_HRCAR = _hoops_RPPA;
	while (_hoops_RPPA < _hoops_SSRPR && (*_hoops_RPPA != ',')) 
		_hoops_RPPA++;

	if (_hoops_HRCAR == _hoops_RPPA) 
		return false;

	COPY_MEMORY(_hoops_HRCAR, _hoops_RPPA-_hoops_HRCAR, buffer);
	buffer[_hoops_RPPA-_hoops_HRCAR] = '\0';

	/* _hoops_HRGAH _hoops_IACH _hoops_IS _hoops_ASSS _hoops_GII _hoops_AGR */

	bool _hoops_HGCPI = true;
	while (_hoops_HGCPI) {

		_hoops_HGCPI = false;

		while (_hoops_RPPA < _hoops_SSRPR && (*_hoops_RPPA == ' ' || *_hoops_RPPA == ',')) 
			_hoops_RPPA++;

		if (_hoops_GPPSA(_hoops_RPPA, 5, "fixed")) {
			_hoops_CCIPI=true;
			_hoops_RPPA+=5;
			_hoops_HGCPI = true;
		}

		while (_hoops_RPPA < _hoops_SSRPR && (*_hoops_RPPA == ' ' || *_hoops_RPPA == ',')) 
			_hoops_RPPA++;

		if (_hoops_GPPSA(_hoops_RPPA, 6, "mirror")) {
			_hoops_RSIPI=true;
			_hoops_RPPA+=6;
			_hoops_HGCPI = true;
		}

		while (_hoops_RPPA < _hoops_SSRPR && (*_hoops_RPPA == ' ' || *_hoops_RPPA == ',')) 
			_hoops_RPPA++;

		if (_hoops_GPPSA(_hoops_RPPA, 5, "inset")) {
			_hoops_SCIPI=true;
			_hoops_RPPA+=5;
			_hoops_HGCPI = true;
		}
		else if (_hoops_GPPSA(_hoops_RPPA, 6, "inline")) {
			_hoops_GSIPI=true;
			_hoops_RPPA+=6;
			_hoops_HGCPI = true;
		}

		while (_hoops_RPPA < _hoops_SSRPR && (*_hoops_RPPA == ' ' || *_hoops_RPPA == ',')) 
			_hoops_RPPA++;

		if (_hoops_GPPSA(_hoops_RPPA, 8, "rotation")) {
			_hoops_RPPA+=8;

			/*_hoops_HSGR _hoops_ISGR = */
			while (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == ' ') 
				_hoops_RPPA++;
			if (_hoops_SSRPR - _hoops_RPPA >= 1 && _hoops_RPPA[0] != '=') 
				break;
			_hoops_RPPA++;
			while (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == ' ') 
				_hoops_RPPA++;

			if (HI_Scan_Float (_hoops_RIGC, &_hoops_RPPA, _hoops_SSRPR, &rotation)) {
				rotation=0.0f;
				/*_hoops_ASIGA _hoops_ASRHR*/
			}

			_hoops_HGCPI = true;
		}

		if (_hoops_GPPSA(_hoops_RPPA, 8, "weighted")) {

			_hoops_RPPA+=8;
			_hoops_HGCPI = true;

			/*_hoops_HSGR _hoops_ISGR = */
			while (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == ' ') 
				_hoops_RPPA++;
			if (_hoops_SSRPR - _hoops_RPPA >= 1 && _hoops_RPPA[0] != '=') 
				break;
			_hoops_RPPA++;
			while (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == ' ') 
				_hoops_RPPA++;
			
			_hoops_HCIPI = 0.0f;	
			_hoops_ICIPI = GSU_PIXELS;	

			if (!HI_Scan_Float (_hoops_RIGC, &_hoops_RPPA, _hoops_SSRPR, &_hoops_HCIPI)) {

				while (_hoops_RPPA < _hoops_SSRPR && (*_hoops_RPPA == ' ')) 
					_hoops_RPPA++;

				int _hoops_IGCPI = 1;

				while (_hoops_RPPA+_hoops_IGCPI < _hoops_SSRPR && 
					_hoops_RPPA[_hoops_IGCPI-1] != ' ' && 
					_hoops_RPPA[_hoops_IGCPI] != ',' && 
					_hoops_RPPA[_hoops_IGCPI] != '=' &&
					_hoops_RPPA[_hoops_IGCPI] != '\0') _hoops_IGCPI++;

				while (_hoops_IGCPI >= 1 && _hoops_RPPA[_hoops_IGCPI-1] == ' ') 
					_hoops_IGCPI--;

				/*_hoops_IHSH _hoops_IH _hoops_IRS _hoops_CGCPI*/
				if (_hoops_IGCPI == 5 && _hoops_GPPSA(_hoops_RPPA, 5, "point") ||
					_hoops_IGCPI == 6 && _hoops_GPPSA(_hoops_RPPA, 6, "points")) {
						_hoops_ICIPI = GSU_POINTS;
						_hoops_RPPA += 5;
						if (*_hoops_RPPA == 's') 
							_hoops_RPPA++;
				}
				else if (_hoops_IGCPI == 5 && _hoops_GPPSA(_hoops_RPPA, 5, "pixel") ||
					_hoops_IGCPI == 6 && _hoops_GPPSA(_hoops_RPPA, 6, "pixels")) {
						_hoops_RPPA += 5;
						if (*_hoops_RPPA == 's') 
							_hoops_RPPA++;
				}
				else if (_hoops_IGCPI == 3 && _hoops_GPPSA(_hoops_RPPA, 3, "pts")) {
					_hoops_ICIPI = GSU_POINTS;
					_hoops_RPPA += 3;
				}
				else if (_hoops_IGCPI == 3 && _hoops_GPPSA(_hoops_RPPA, 3, "pxl")) {
					_hoops_RPPA += 3;
				}
				else if (_hoops_IGCPI == 3 && _hoops_GPPSA(_hoops_RPPA, 3, "oru")) {
					_hoops_ICIPI = GSU_ORU;
					_hoops_RPPA += 3;
				}
				else if (_hoops_IGCPI == 3 && _hoops_GPPSA(_hoops_RPPA, 3, "sru")) {
					_hoops_ICIPI = GSU_SRU;
					_hoops_RPPA += 3;
				}
				else if (_hoops_IGCPI == 3 && _hoops_GPPSA(_hoops_RPPA, 3, "wru")) {
					_hoops_ICIPI = GSU_WRU;
					_hoops_RPPA += 3;
				}
				else if (_hoops_IGCPI == 3 && _hoops_GPPSA(_hoops_RPPA, 3, "wsu")) {
					_hoops_ICIPI = _hoops_SPSC;
					_hoops_RPPA += 3;
				}
				else if (_hoops_IGCPI == 2 && _hoops_GPPSA(_hoops_RPPA, 2, "pt")) {
					_hoops_ICIPI  =GSU_POINTS;
					_hoops_RPPA += 2;
				}
				else if (_hoops_IGCPI == 2 && _hoops_GPPSA(_hoops_RPPA, 2, "px")) {
					_hoops_RPPA += 2;
				}
				else if (_hoops_IGCPI == 1 && _hoops_GPPSA(_hoops_RPPA, 1, "%")) {
					_hoops_ICIPI = GSU_PERCENT;
					_hoops_RPPA += 1;
				}
			}
		}
	}

	*_hoops_CSIPI = _hoops_RPPA;

	if (*_hoops_SSIPI || *_hoops_GGCPI || *_hoops_RGCPI) {
		if (*_hoops_SSIPI) {
			
			float r=rotation+*_hoops_PGCPI;
			Line_Style_Item * _hoops_HSIPI = _hoops_ACIPI(null, buffer, r, 
				_hoops_HCIPI, _hoops_ICIPI,
				_hoops_CCIPI, _hoops_SCIPI, _hoops_GSIPI, _hoops_RSIPI, 
				*_hoops_ASIPI, value, 
				*_hoops_PSIPI, _hoops_HHP);
			_hoops_RIIPI->start_glyph = _hoops_HSIPI;
			_hoops_RIIPI->flags |= LSF_START_GLYPH;
		}

		if (*_hoops_GGCPI) {

			Line_Style_Item * _hoops_HSIPI = _hoops_ACIPI(null, buffer, rotation, 
				_hoops_HCIPI, _hoops_ICIPI,
				_hoops_CCIPI, _hoops_SCIPI, _hoops_GSIPI, _hoops_RSIPI, 
				*_hoops_ASIPI, value, 
				*_hoops_PSIPI, _hoops_HHP);

			_hoops_RIIPI->middle_glyph = _hoops_HSIPI;
			_hoops_RIIPI->flags |= LSF_MIDDLE_GLYPH;
		}

		if (*_hoops_RGCPI) {
			float r=rotation+*_hoops_AGCPI;
			Line_Style_Item * _hoops_HSIPI = _hoops_ACIPI(null, buffer, r, 
				_hoops_HCIPI, _hoops_ICIPI,
				_hoops_CCIPI, _hoops_SCIPI, _hoops_GSIPI, _hoops_RSIPI, 
				*_hoops_ASIPI, value, 
				*_hoops_PSIPI, _hoops_HHP);

			_hoops_RIIPI->end_glyph = _hoops_HSIPI;
			_hoops_RIIPI->flags |= LSF_END_GLYPH;
		}

		*_hoops_AGCPI = 0.0f;
		*_hoops_SSIPI = false;
		*_hoops_GGCPI = false;
		*_hoops_RGCPI = false;
		*_hoops_ASIPI = false;
		*_hoops_PSIPI=false;
	}
	else {
		Line_Style_Item *	_hoops_HSIPI = &pattern_items[*pattern_items_n];

		_hoops_ACIPI(_hoops_HSIPI, buffer, rotation, _hoops_HCIPI, _hoops_ICIPI,
						_hoops_CCIPI, _hoops_SCIPI, _hoops_GSIPI, _hoops_RSIPI, 
						*_hoops_ASIPI, value, 
						*_hoops_PSIPI, _hoops_HHP);

		pattern[*length] = _hoops_PPCAP;
		_hoops_RIIPI->flags |= LSF_GLYPHS;

		*length += 1;
		*pattern_items_n += 1;
		*_hoops_ASIPI = false;
		*_hoops_PSIPI=false;
	}

	return true;
}



GLOBAL_FUNCTION bool HI_Validate_Line_Style (
	_hoops_AIGPR *		_hoops_RIGC,
	Line_Style alter &			line_style) {
	char const *				_hoops_RPPA = line_style->definition.text;
	char const *				_hoops_SSRPR = _hoops_RPPA + line_style->definition.length;
	char const *				_hoops_HRCAR;
	Line_Style_Item				pattern_items[4096];
	int 						pattern_items_n = 0;
	int 						pattern[4096];
	int 						length = 0;
	Line_Style_Parallel *		_hoops_RIIPI=0;
	bool 						_hoops_ASIPI, _hoops_PSIPI;
	bool 						_hoops_SSIPI, _hoops_GGCPI, _hoops_RGCPI;
	float						_hoops_AGCPI, _hoops_PGCPI;
	float						value = 0.0f;
	_hoops_GIGRP			_hoops_HHP = _hoops_SHGRP;
	bool						draw;
	unsigned int				i;


	line_style->flags = _hoops_ICIAP;

	if (_hoops_RPPA == _hoops_SSRPR) {
		HE_ERROR (HEC_LINE_STYLE, HES_DEGENERATE_DEFINITION,
			"Line style definition is degenerate");
		return false;
	}

_hoops_SGCPI:

	_hoops_ASIPI = _hoops_PSIPI = false;
	_hoops_SSIPI = _hoops_GGCPI = _hoops_RGCPI = false;
	_hoops_AGCPI = _hoops_PGCPI = 0.0f;
	length = 0;
	pattern_items_n = 0;
	draw = true;

	ZERO_ARRAY(pattern_items, 4096, Line_Style_Item);

	ZALLOC (_hoops_RIIPI, Line_Style_Parallel);

	while (_hoops_RPPA < _hoops_SSRPR && (*_hoops_RPPA == ' ')) _hoops_RPPA++;

	_hoops_HRCAR=_hoops_RPPA;

	do {
		int			_hoops_IGCPI = 0;
		
		while (_hoops_RPPA < _hoops_SSRPR && (*_hoops_RPPA == ' ')) _hoops_RPPA++;

		while (_hoops_RPPA+_hoops_IGCPI < _hoops_SSRPR && 
				_hoops_RPPA[_hoops_IGCPI] != ',' && 
				_hoops_RPPA[_hoops_IGCPI] != '=' &&
				_hoops_RPPA[_hoops_IGCPI] != '\0') _hoops_IGCPI++;

		while (_hoops_IGCPI >= 1 && _hoops_RPPA[_hoops_IGCPI-1] == ' ') _hoops_IGCPI--;

		switch (*_hoops_RPPA) {
			case ',': {
				/*_hoops_CGH _hoops_IIP _hoops_HS _hoops_PSPA _hoops_RAAP*/
				if (_hoops_ASIPI || _hoops_PSIPI)
					break;
				/*_hoops_CGH _hoops_IIP _hoops_SHH _hoops_HCHAR _hoops_IH _hoops_IRS _hoops_RPHH*/
				if (_hoops_SSIPI || _hoops_GGCPI || _hoops_SSIPI)
					break;

				_hoops_RPPA++;
			}	break;

			case 'a': {
				if (_hoops_IGCPI == 15 && _hoops_GPPSA(_hoops_RPPA, 15, "absolute weight")) {
					_hoops_RPPA += 15;
					_hoops_RIIPI->flags |= LSF_ABSOLUTE_WEIGHT;
				}
				else if (_hoops_IGCPI == 15 && _hoops_GPPSA(_hoops_RPPA, 15, "absolute length")) {
					_hoops_RPPA += 15;
					_hoops_RIIPI->flags |= LSF_ABSOLUTE_LENGTH;
				}
				else if (_hoops_IGCPI == 8 &&
						 _hoops_GPPSA(_hoops_RPPA, 8, "absolute")) {
					_hoops_RPPA += 8;
					_hoops_RIIPI->flags |= LSF_ABSOLUTE_LENGTH|LSF_ABSOLUTE_WEIGHT;
				}
				else if ((_hoops_IGCPI == 5 && _hoops_GPPSA(_hoops_RPPA, 5, "arrow")) ||
						 (_hoops_IGCPI == 6 && _hoops_GPPSA(_hoops_RPPA, 6, "arrows"))) {
					_hoops_RPPA += 5;
					if (*_hoops_RPPA == 's') _hoops_RPPA++;
   
					/*_hoops_HSGR _hoops_ISGR = */
					while (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == ' ') _hoops_RPPA++;
					if (_hoops_SSRPR - _hoops_RPPA >= 1 && _hoops_RPPA[0] != '=') break;
					_hoops_RPPA++;

					_hoops_PGCPI = 90.0f;
					_hoops_AGCPI = 270.0f;
					_hoops_SSIPI=true;
					_hoops_RGCPI=true;
				}
				else if (!_hoops_ISIPI (_hoops_RIGC, _hoops_RIIPI, &_hoops_RPPA, _hoops_SSRPR,
											&_hoops_SSIPI, &_hoops_GGCPI, &_hoops_RGCPI,
											&_hoops_AGCPI, &_hoops_PGCPI,
											&_hoops_ASIPI, value, 
											&_hoops_PSIPI, _hoops_HHP,
											pattern, &length,
											pattern_items, &pattern_items_n))
					goto _hoops_PRSPR;
			}	break;

			case 's': {
				if (_hoops_IGCPI == 9 && _hoops_GPPSA(_hoops_RPPA, 9, "segmented")) {
					_hoops_RPPA += 9;
					_hoops_RIIPI->flags |= LSF_SEGMENTED;
				}
				else if ((_hoops_IGCPI == 9 && _hoops_GPPSA(_hoops_RPPA, 9, "start cap")) ||
						 (_hoops_IGCPI == 10 && _hoops_GPPSA(_hoops_RPPA, 10, "start caps"))) {
					_hoops_RPPA += 9;
					if (*_hoops_RPPA == 's') _hoops_RPPA++;

					/*_hoops_HSGR _hoops_ISGR = */
					while (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == ' ') _hoops_RPPA++;
					if (_hoops_SSRPR - _hoops_RPPA >= 1 && _hoops_RPPA[0] != '=') break;
					_hoops_RPPA++;

					_hoops_SSIPI=true;
				}
				else if ((_hoops_IGCPI == 11 && _hoops_GPPSA(_hoops_RPPA, 11, "start arrow")) ||
						 (_hoops_IGCPI == 12 &&_hoops_GPPSA(_hoops_RPPA, 12, "start arrows"))) {
					_hoops_RPPA += 11;
					if (*_hoops_RPPA == 's') _hoops_RPPA++;

					/*_hoops_HSGR _hoops_ISGR = */
					while (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == ' ') _hoops_RPPA++;
					if (_hoops_SSRPR - _hoops_RPPA >= 1 && _hoops_RPPA[0] != '=') break;
					_hoops_RPPA++;

					_hoops_PGCPI = 90.0f;
					_hoops_SSIPI=true;
				}
				else if (!_hoops_ISIPI (_hoops_RIGC, _hoops_RIIPI, &_hoops_RPPA, _hoops_SSRPR,
											&_hoops_SSIPI, &_hoops_GGCPI, &_hoops_RGCPI,
											&_hoops_AGCPI, &_hoops_PGCPI,
											&_hoops_ASIPI, value, 
											&_hoops_PSIPI, _hoops_HHP,
											pattern, &length,
											pattern_items, &pattern_items_n))
					goto _hoops_PRSPR;
			}	break;

			case 't': {
				if (_hoops_IGCPI == 11 && _hoops_GPPSA(_hoops_RPPA, 11, "transformed")) {
					_hoops_RPPA += 11;
					line_style->flags |= _hoops_PRCAP;
				}
				else if (!_hoops_ISIPI (_hoops_RIGC, _hoops_RIIPI, &_hoops_RPPA, _hoops_SSRPR,
											&_hoops_SSIPI, &_hoops_GGCPI, &_hoops_RGCPI,
											&_hoops_AGCPI, &_hoops_PGCPI,
											&_hoops_ASIPI, value, 
											&_hoops_PSIPI, _hoops_HHP,
											pattern, &length,
											pattern_items, &pattern_items_n))
					goto _hoops_PRSPR;
			}	break;

			case 'e': {
				if (_hoops_IGCPI == 7 && _hoops_GPPSA(_hoops_RPPA, 7, "end cap") ||
					_hoops_IGCPI == 8 &&_hoops_GPPSA(_hoops_RPPA, 8, "end caps")) {
					_hoops_RPPA += 7;
					if (*_hoops_RPPA == 's') _hoops_RPPA++;

					/*_hoops_HSGR _hoops_ISGR = */
					while (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == ' ') _hoops_RPPA++;
					if (_hoops_SSRPR - _hoops_RPPA >= 1 && _hoops_RPPA[0] != '=') break;
					_hoops_RPPA++;

					_hoops_RGCPI=true;
				}
				else if (_hoops_IGCPI == 9 && _hoops_GPPSA(_hoops_RPPA, 9, "end arrow") ||
						 _hoops_IGCPI == 10 && _hoops_GPPSA(_hoops_RPPA, 10, "end arrows")) {
					_hoops_RPPA += 9;
					if (*_hoops_RPPA == 's') _hoops_RPPA++;

					/*_hoops_HSGR _hoops_ISGR = */
					while (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == ' ') _hoops_RPPA++;
					if (_hoops_SSRPR - _hoops_RPPA >= 1 && _hoops_RPPA[0] != '=') break;
					_hoops_RPPA++;

					_hoops_AGCPI = 270.0f;
					_hoops_RGCPI=true;
				}
				else if (!_hoops_ISIPI (_hoops_RIGC, _hoops_RIIPI, &_hoops_RPPA, _hoops_SSRPR,
											&_hoops_SSIPI, &_hoops_GGCPI, &_hoops_RGCPI,
											&_hoops_AGCPI, &_hoops_PGCPI,
											&_hoops_ASIPI, value, 
											&_hoops_PSIPI, _hoops_HHP,
											pattern, &length,
											pattern_items, &pattern_items_n))
					goto _hoops_PRSPR;
			}	break;

			case 'm': {
				if (_hoops_IGCPI == 6 && _hoops_GPPSA(_hoops_RPPA, 6, "middle") ||
					_hoops_IGCPI == 7 && _hoops_GPPSA(_hoops_RPPA, 7, "middles")) { 
					_hoops_RPPA += 6;
					if (*_hoops_RPPA == 's') _hoops_RPPA++;

					/*_hoops_HSGR _hoops_ISGR = */
					while (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == ' ') _hoops_RPPA++;
					if (_hoops_SSRPR - _hoops_RPPA >= 1 && _hoops_RPPA[0] != '=') break;
					_hoops_RPPA++;

					_hoops_GGCPI=true;
				}
				else if (!_hoops_ISIPI(_hoops_RIGC, _hoops_RIIPI, &_hoops_RPPA, _hoops_SSRPR,
											&_hoops_SSIPI, &_hoops_GGCPI, &_hoops_RGCPI,
											&_hoops_AGCPI, &_hoops_PGCPI,
											&_hoops_ASIPI, value, 
											&_hoops_PSIPI, _hoops_HHP,
											pattern, &length,
											pattern_items, &pattern_items_n))
					goto _hoops_PRSPR;
			}	break;

			case 'g': {
				if (_hoops_IGCPI == 5 && _hoops_GPPSA(_hoops_RPPA, 5, "glyph") ||
					_hoops_IGCPI == 6 && _hoops_GPPSA(_hoops_RPPA, 6, "glyphs")) {
					_hoops_RPPA += 5;
					if (*_hoops_RPPA == 's') _hoops_RPPA++;

					/*_hoops_HSGR _hoops_ISGR = */
					while (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == ' ') _hoops_RPPA++;
					if (_hoops_SSRPR - _hoops_RPPA >= 1 && _hoops_RPPA[0] != '=') break;
					_hoops_RPPA++;

					_hoops_SSIPI=true;
					_hoops_GGCPI=true;
					_hoops_RGCPI=true;
				}
				else if (!_hoops_ISIPI (_hoops_RIGC, _hoops_RIIPI, &_hoops_RPPA, _hoops_SSRPR,
											&_hoops_SSIPI, &_hoops_GGCPI, &_hoops_RGCPI,
											&_hoops_AGCPI, &_hoops_PGCPI,
											&_hoops_ASIPI, value, 
											&_hoops_PSIPI, _hoops_HHP,
											pattern, &length,
											pattern_items, &pattern_items_n))
					goto _hoops_PRSPR;
			}	break;

			case 'd': {
				if (_hoops_IGCPI == 4 && _hoops_GPPSA(_hoops_RPPA, 4, "dash") ||
					_hoops_IGCPI > 4 && _hoops_GPPSA(_hoops_RPPA, 4, "dash(")) {

					Line_Style_Item *	_hoops_GRCPI = null;
					
					if (_hoops_IGCPI > 4)
						_hoops_GRCPI = &pattern_items[pattern_items_n];

					_hoops_RPPA += 4;

					if (_hoops_ASIPI) {
						if (_hoops_PSIPI) {
							pattern[length++] = _hoops_GPCAP;
							_hoops_HGGIH(pattern_items[pattern_items_n].name);
							pattern_items[pattern_items_n].size.value = value;
							pattern_items[pattern_items_n].size._hoops_HHP = _hoops_HHP;
							pattern_items_n++;
							_hoops_PSIPI=false;
						}
						else if (!draw || _hoops_GRCPI) {
							pattern[length++] = _hoops_GPCAP;
							_hoops_HGGIH(pattern_items[pattern_items_n].name);
							pattern_items[pattern_items_n].size.value = value;
							pattern_items[pattern_items_n].size._hoops_HHP = GSU_PIXELS;
							pattern_items_n++;
							_hoops_PSIPI=false;
						}
						else {
							pattern[length++] = (int)value;
						}
						_hoops_ASIPI = false;
					}
					else {

						if (length == 0 && !_hoops_GRCPI) {
							_hoops_RIIPI->flags |= LSF_SOLID;
							break;
						}

						if (!draw || _hoops_GRCPI) {
							pattern[length++] = _hoops_GPCAP;
							_hoops_HGGIH(pattern_items[pattern_items_n].name);
							pattern_items[pattern_items_n].size.value = (float)_hoops_IICIA;
							pattern_items[pattern_items_n].size._hoops_HHP = GSU_PIXELS;
							pattern_items_n++;
							_hoops_PSIPI=false;
						}
						else {
							pattern[length++] = (int)_hoops_IICIA;
						}
					}

					// _hoops_RHAPA _hoops_HAIR
					if (_hoops_GRCPI) {
						float _hoops_RRCPI[3];
						int _hoops_GCAIR=0;

						// _hoops_GIPSR
						_hoops_IGCPI-=4; 

						// (
						_hoops_RPPA++;
						_hoops_IGCPI--; 

						while (_hoops_IGCPI > 0) {
							if (*_hoops_RPPA == ')') {
								_hoops_RPPA++;
								_hoops_IGCPI--;
								continue;
							}

							while (_hoops_IGCPI > 0 && (*_hoops_RPPA == ' ')) {
								_hoops_RPPA++;
								_hoops_IGCPI--;
								continue;
							}

							if (*_hoops_RPPA >= '0' && *_hoops_RPPA <= '9') {
								char const * _hoops_ARCPI = _hoops_RPPA;

								if (!HI_Scan_Float (_hoops_RIGC, &_hoops_RPPA, _hoops_SSRPR, &_hoops_RRCPI[_hoops_GCAIR])) {
									_hoops_IGCPI -= (int)(_hoops_RPPA - _hoops_ARCPI);
									_hoops_GCAIR++;
								}
								else 
									_hoops_IGCPI=-1; // _hoops_RIHH
							}
							else
								_hoops_IGCPI=-1; // _hoops_RIHH
						}

						if (_hoops_IGCPI == 0) {
							if (_hoops_GCAIR == 1) {
								_hoops_GRCPI->flags |= _hoops_HRCAP;
								_hoops_GRCPI->index = _hoops_PSCSH(_hoops_RRCPI[0]);
							}
							else if (_hoops_GCAIR == 3) {
								_hoops_GRCPI->flags |= _hoops_IRCAP;
								_hoops_GRCPI->rgb.red = _hoops_RRCPI[0];
								_hoops_GRCPI->rgb.green = _hoops_RRCPI[1];
								_hoops_GRCPI->rgb.blue = _hoops_RRCPI[2];
							}
							// _hoops_SHS _hoops_RIHH
						}
						// _hoops_SHS _hoops_RIHH
					}

					draw = false;
				} 
				else if (!_hoops_ISIPI (_hoops_RIGC, _hoops_RIIPI, &_hoops_RPPA, _hoops_SSRPR,
											&_hoops_SSIPI, &_hoops_GGCPI, &_hoops_RGCPI,
											&_hoops_AGCPI, &_hoops_PGCPI,
											&_hoops_ASIPI, value, 
											&_hoops_PSIPI, _hoops_HHP,
											pattern, &length,
											pattern_items, &pattern_items_n))
					goto _hoops_PRSPR;
			}	break;

			case 'b': {
				if (_hoops_IGCPI == 5 && _hoops_GPPSA(_hoops_RPPA, 5, "bevel")) {
					_hoops_RPPA += 5;
					_hoops_RIIPI->flags |= _hoops_ARCAP;
				}
				else if (_hoops_IGCPI == 5 && _hoops_GPPSA(_hoops_RPPA, 5, "blank")) {
					_hoops_RPPA += 5;

					if (_hoops_ASIPI) {
						if (_hoops_PSIPI) {
							pattern[length++] = _hoops_RPCAP;
							_hoops_HGGIH(pattern_items[pattern_items_n].name);
							pattern_items[pattern_items_n].size.value = value;
							pattern_items[pattern_items_n].size._hoops_HHP = _hoops_HHP;
							pattern_items_n++;
							_hoops_PSIPI=false;
						}
						else if (draw) {
							pattern[length++] = _hoops_RPCAP;
							_hoops_HGGIH(pattern_items[pattern_items_n].name);
							pattern_items[pattern_items_n].size.value = value;
							pattern_items[pattern_items_n].size._hoops_HHP = GSU_PIXELS;
							pattern_items_n++;
						}
						else {
							pattern[length++] = (int)value;
						}
						_hoops_ASIPI = false;
					}
					else {
						pattern[length++] = _hoops_RPCAP;
						_hoops_HGGIH(pattern_items[pattern_items_n].name);
						pattern_items[pattern_items_n].size.value = (float)_hoops_IICIA;
						pattern_items[pattern_items_n].size._hoops_HHP = GSU_PIXELS;
						pattern_items_n++;
					}
					draw = true;
				} 
				else if (!_hoops_ISIPI (_hoops_RIGC, _hoops_RIIPI, &_hoops_RPPA, _hoops_SSRPR,
											&_hoops_SSIPI, &_hoops_GGCPI, &_hoops_RGCPI,
											&_hoops_AGCPI, &_hoops_PGCPI,
											&_hoops_ASIPI, value, 
											&_hoops_PSIPI, _hoops_HHP,
											pattern, &length,
											pattern_items, &pattern_items_n))
					goto _hoops_PRSPR;
			} break;

			case 'c': {
				if (_hoops_IGCPI == 8 && _hoops_GPPSA(_hoops_RPPA, 8, "contrast")) {
					_hoops_RPPA += 8;

					if (_hoops_ASIPI) {
						if (_hoops_PSIPI) {
							pattern[length++] = _hoops_APCAP;
							_hoops_HGGIH(pattern_items[pattern_items_n].name);
							pattern_items[pattern_items_n].size.value = value;
							pattern_items[pattern_items_n].size._hoops_HHP = _hoops_HHP;
							pattern_items_n++;
							_hoops_PSIPI=false;
						}
						else {
							pattern[length++] = _hoops_APCAP;
							_hoops_HGGIH(pattern_items[pattern_items_n].name);
							pattern_items[pattern_items_n].size.value = value;
							pattern_items[pattern_items_n].size._hoops_HHP = GSU_PIXELS;
							pattern_items_n++;
						}
						_hoops_ASIPI = false;
					}
					else {
						pattern[length++] = _hoops_APCAP;
						_hoops_HGGIH(pattern_items[pattern_items_n].name);
						pattern_items[pattern_items_n].size.value = (float)_hoops_IICIA;
						pattern_items[pattern_items_n].size._hoops_HHP = GSU_PIXELS;
						pattern_items_n++;
					}

					_hoops_RIIPI->flags |= LSF_CONTRAST;
					draw = false;
				} 
				else if (_hoops_IGCPI == 3 && _hoops_GPPSA(_hoops_RPPA, 3, "cap") ||
						 _hoops_IGCPI == 4 && _hoops_GPPSA(_hoops_RPPA, 4, "caps")) {
					_hoops_RPPA += 3;
					if (*_hoops_RPPA == 's') _hoops_RPPA++;

					/*_hoops_HSGR _hoops_ISGR = */
					while (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == ' ') _hoops_RPPA++;
					if (_hoops_SSRPR - _hoops_RPPA >= 1 && _hoops_RPPA[0] != '=') break;
					_hoops_RPPA++;

					_hoops_SSIPI=true;
					_hoops_RGCPI=true;
				}
				else if (!_hoops_ISIPI (_hoops_RIGC, _hoops_RIIPI, &_hoops_RPPA, _hoops_SSRPR,
											&_hoops_SSIPI, &_hoops_GGCPI, &_hoops_RGCPI,
											&_hoops_AGCPI, &_hoops_PGCPI,
											&_hoops_ASIPI, value, 
											&_hoops_PSIPI, _hoops_HHP,
											pattern, &length,
											pattern_items, &pattern_items_n))
					goto _hoops_PRSPR;
			}	break;

			case 'w': {
				if (_hoops_IGCPI == 6 && _hoops_GPPSA(_hoops_RPPA, 6, "weight")) {
					_hoops_RPPA += 6;

					if (_hoops_ASIPI) {
						if (_hoops_PSIPI) {
							_hoops_RIIPI->weight.value = value;
							_hoops_RIIPI->weight._hoops_HHP = _hoops_HHP;
							_hoops_PSIPI=false;
						}
						else {
							_hoops_RIIPI->weight.value = value;
							_hoops_RIIPI->weight._hoops_HHP = GSU_PIXELS;
						}
						_hoops_ASIPI = false;
					}
					else {
						_hoops_RIIPI->weight.value = (float)_hoops_IICIA;
						_hoops_RIIPI->weight._hoops_HHP = GSU_PIXELS;
					}

					if (_hoops_RIIPI->weight._hoops_HHP != GSU_PIXELS ||
						_hoops_RIIPI->weight.value != 1)
						_hoops_RIIPI->flags |= LSF_WEIGHT;
				} 
				else if (!_hoops_ISIPI (_hoops_RIGC, _hoops_RIIPI, &_hoops_RPPA, _hoops_SSRPR,
											&_hoops_SSIPI, &_hoops_GGCPI, &_hoops_RGCPI,
											&_hoops_AGCPI, &_hoops_PGCPI,
											&_hoops_ASIPI, value, 
											&_hoops_PSIPI, _hoops_HHP,
											pattern, &length,
											pattern_items, &pattern_items_n))
					goto _hoops_PRSPR;
			}	break;

			case 'o': {
				if (_hoops_IGCPI == 6 && _hoops_GPPSA(_hoops_RPPA, 6, "offset")) {
					_hoops_RPPA += 6;

					if (_hoops_ASIPI) {
						if (_hoops_PSIPI) {
							_hoops_RIIPI->offset.value = value;
							_hoops_RIIPI->offset._hoops_HHP = _hoops_HHP;
							_hoops_PSIPI=false;
						}
						else {
							_hoops_RIIPI->offset.value = value;
							_hoops_RIIPI->offset._hoops_HHP = GSU_PIXELS;
						}
						_hoops_ASIPI = false;
					}
					else {
						_hoops_RIIPI->offset.value = (float)_hoops_IICIA;
						_hoops_RIIPI->offset._hoops_HHP = GSU_PIXELS;
					}

					_hoops_RIIPI->flags |= LSF_OFFSET;
				} 
				else if (!_hoops_ISIPI (_hoops_RIGC, _hoops_RIIPI, &_hoops_RPPA, _hoops_SSRPR,
											&_hoops_SSIPI, &_hoops_GGCPI, &_hoops_RGCPI,
											&_hoops_AGCPI, &_hoops_PGCPI,
											&_hoops_ASIPI, value, 
											&_hoops_PSIPI, _hoops_HHP,
											pattern, &length,
											pattern_items, &pattern_items_n))
					goto _hoops_PRSPR;
			}	break;

			case 'f': {
				if (_hoops_IGCPI == 3 && _hoops_GPPSA(_hoops_RPPA, 3, "fit")) {
					_hoops_RPPA += 3;

					/*_hoops_HSGR _hoops_ISGR = */
					while (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == ' ') _hoops_RPPA++;
					if (_hoops_SSRPR - _hoops_RPPA >= 1 && _hoops_RPPA[0] != '=') {
						_hoops_HRCAR = _hoops_RPPA;

						if (!_hoops_ISIPI (_hoops_RIGC, _hoops_RIIPI, &_hoops_RPPA, _hoops_SSRPR,
												&_hoops_SSIPI, &_hoops_GGCPI, &_hoops_RGCPI,
												&_hoops_AGCPI, &_hoops_PGCPI,
												&_hoops_ASIPI, value, 
												&_hoops_PSIPI, _hoops_HHP,
												pattern, &length,
												pattern_items, &pattern_items_n))
							goto _hoops_PRSPR;
					}
					else {
						_hoops_RPPA++;
						while (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == ' ') _hoops_RPPA++;

						if (_hoops_GPPSA(_hoops_RPPA, 6, "center")) {
							_hoops_RPPA += 6;
							_hoops_RIIPI->flags |=	LSF_FIT_CENTER;

						}
						else if (_hoops_GPPSA(_hoops_RPPA, 6, "stretch")) {
							_hoops_RPPA += 7;
							_hoops_RIIPI->flags |=	LSF_FIT_STRETCH;

						}
						else
							goto _hoops_PRSPR;
					}
				}
				else if (_hoops_IGCPI == 12 && _hoops_GPPSA(_hoops_RPPA, 12, "fixed offset")) {
					_hoops_RPPA += 12;

					if (_hoops_ASIPI) {
						if (_hoops_PSIPI) {
							_hoops_RIIPI->offset.value = value;
							_hoops_RIIPI->offset._hoops_HHP = _hoops_HHP;
							_hoops_PSIPI=false;
						}
						else {
							_hoops_RIIPI->offset.value = value;
							_hoops_RIIPI->offset._hoops_HHP = GSU_PIXELS;
						}
						_hoops_ASIPI = false;
					}
					else {
						_hoops_RIIPI->offset.value = (float)_hoops_IICIA;
						_hoops_RIIPI->offset._hoops_HHP = GSU_PIXELS;
					}

					_hoops_RIIPI->flags |= LSF_OFFSET|LSF_FIXED_OFFSET;
				} 
				else if (_hoops_IGCPI == 12 && _hoops_GPPSA(_hoops_RPPA, 12, "fixed weight")) {
					_hoops_RPPA += 12;

					if (_hoops_ASIPI) {
						if (_hoops_PSIPI) {
							_hoops_RIIPI->weight.value = value;
							_hoops_RIIPI->weight._hoops_HHP = _hoops_HHP;
							_hoops_PSIPI=false;
						}
						else {
							_hoops_RIIPI->weight.value = value;
							_hoops_RIIPI->weight._hoops_HHP = GSU_PIXELS;
						}
						_hoops_ASIPI = false;
					}
					else{
						_hoops_RIIPI->weight.value = (float)_hoops_IICIA;
						_hoops_RIIPI->weight._hoops_HHP = GSU_PIXELS;
					}

					_hoops_RIIPI->flags |= LSF_WEIGHT|LSF_FIXED_WEIGHT;
				} 
				else if (!_hoops_ISIPI (_hoops_RIGC, _hoops_RIIPI, &_hoops_RPPA, _hoops_SSRPR,
											&_hoops_SSIPI, &_hoops_GGCPI, &_hoops_RGCPI,
											&_hoops_AGCPI, &_hoops_PGCPI,
											&_hoops_ASIPI, value, 
											&_hoops_PSIPI, _hoops_HHP,
											pattern, &length,
											pattern_items, &pattern_items_n))
					goto _hoops_PRSPR;
			}	break;

			case 'j': {
				if (_hoops_IGCPI == 4 && _hoops_GPPSA(_hoops_RPPA, 4, "join")) {
					_hoops_RPPA += 4;
					_hoops_RIIPI->flags |= LSF_JOIN;
				} 
				else if (!_hoops_ISIPI (_hoops_RIGC, _hoops_RIIPI, &_hoops_RPPA, _hoops_SSRPR,
											&_hoops_SSIPI, &_hoops_GGCPI, &_hoops_RGCPI,
											&_hoops_AGCPI, &_hoops_PGCPI,
											&_hoops_ASIPI, value, 
											&_hoops_PSIPI, _hoops_HHP,
											pattern, &length,
											pattern_items, &pattern_items_n))
					goto _hoops_PRSPR;
			}	break;

			case 'p': {
				if (_hoops_IGCPI == 8 && _hoops_GPPSA(_hoops_RPPA, 8, "parallel")) {
					_hoops_RPPA += 8;

					/* _hoops_IRS _hoops_IHH '_hoops_GGAIA' _hoops_HPGR _hoops_HSPP*/
					if (_hoops_RPPA!=_hoops_HRCAR)
						goto _hoops_PRCPI;
				} 
				else if (!_hoops_ISIPI (_hoops_RIGC, _hoops_RIIPI, &_hoops_RPPA, _hoops_SSRPR,
											&_hoops_SSIPI, &_hoops_GGCPI, &_hoops_RGCPI,
											&_hoops_AGCPI, &_hoops_PGCPI,
											&_hoops_ASIPI, value, 
											&_hoops_PSIPI, _hoops_HHP,
											pattern, &length,
											pattern_items, &pattern_items_n))
					goto _hoops_PRSPR;
			}	break;


			case '-':
			case '+':
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9': {
				if (!HI_Scan_Float (_hoops_RIGC, &_hoops_RPPA, _hoops_SSRPR, &value)) {
					_hoops_ASIPI = true;

					while (_hoops_RPPA < _hoops_SSRPR && (*_hoops_RPPA == ' ')) _hoops_RPPA++;

					_hoops_IGCPI = 0;

					while (_hoops_RPPA+_hoops_IGCPI+1 < _hoops_SSRPR && 
							_hoops_RPPA[_hoops_IGCPI] != ' ' && 
							_hoops_RPPA[_hoops_IGCPI+1] != ',' && 
							_hoops_RPPA[_hoops_IGCPI+1] != '=' &&
							_hoops_RPPA[_hoops_IGCPI+1] != '\0') _hoops_IGCPI++;

					while (_hoops_IGCPI >= 1 && _hoops_RPPA[_hoops_IGCPI-1] == ' ') _hoops_IGCPI--;

					/*_hoops_IHSH _hoops_IH _hoops_IRS _hoops_CGCPI*/
					if (_hoops_IGCPI == 5 && _hoops_GPPSA(_hoops_RPPA, 5, "point") ||
						_hoops_IGCPI == 6 && _hoops_GPPSA(_hoops_RPPA, 6, "points")) {
						_hoops_PSIPI = true;
						_hoops_HHP = GSU_POINTS;
						_hoops_RPPA += 5;
						if (*_hoops_RPPA == 's') _hoops_RPPA++;
					}
					else if (_hoops_IGCPI == 5 && _hoops_GPPSA(_hoops_RPPA, 5, "pixel") ||
							 _hoops_IGCPI == 6 && _hoops_GPPSA(_hoops_RPPA, 6, "pixels")) {
						_hoops_RPPA += 5;
						if (*_hoops_RPPA == 's') _hoops_RPPA++;
					}
					else if (_hoops_IGCPI == 3 && _hoops_GPPSA(_hoops_RPPA, 3, "pts")) {
						_hoops_PSIPI = true;
						_hoops_HHP = GSU_POINTS;
						_hoops_RPPA += 3;
					}
					else if (_hoops_IGCPI == 3 && _hoops_GPPSA(_hoops_RPPA, 3, "pxl")) {
						_hoops_RPPA += 3;
					}
					else if (_hoops_IGCPI == 3 && _hoops_GPPSA(_hoops_RPPA, 3, "oru")) {
						_hoops_PSIPI = true;
						_hoops_HHP = GSU_ORU;
						_hoops_RPPA += 3;
					}
					else if (_hoops_IGCPI == 3 && _hoops_GPPSA(_hoops_RPPA, 3, "sru")) {
						_hoops_PSIPI = true;
						_hoops_HHP = GSU_SRU;
						_hoops_RPPA += 3;
					}
					else if (_hoops_IGCPI == 3 && _hoops_GPPSA(_hoops_RPPA, 3, "wru")) {
						_hoops_PSIPI = true;
						_hoops_HHP = GSU_WRU;
						_hoops_RPPA += 3;
					}
					else if (_hoops_IGCPI == 3 && _hoops_GPPSA(_hoops_RPPA, 3, "wsu")) {
						_hoops_PSIPI = true;
						_hoops_HHP = _hoops_SPSC;
						_hoops_RPPA += 3;
					}
					else if (_hoops_IGCPI == 2 && _hoops_GPPSA(_hoops_RPPA, 2, "pt")) {
						_hoops_PSIPI = true;
						_hoops_HHP  =GSU_POINTS;
						_hoops_RPPA += 2;
					}
					else if (_hoops_IGCPI == 2 && _hoops_GPPSA(_hoops_RPPA, 2, "px")) {
						_hoops_RPPA += 2;
					}
					else if (_hoops_IGCPI == 1 && _hoops_GPPSA(_hoops_RPPA, 1, "%")) {
						_hoops_RIIPI->flags |= LSF_PERCENT;
						_hoops_PSIPI = true;
						_hoops_HHP = GSU_PERCENT;
						_hoops_RPPA += 1;
					}

				}
				else if (!_hoops_ISIPI (_hoops_RIGC, _hoops_RIIPI, &_hoops_RPPA, _hoops_SSRPR,
											&_hoops_SSIPI, &_hoops_GGCPI, &_hoops_RGCPI,
											&_hoops_AGCPI, &_hoops_PGCPI,
											&_hoops_ASIPI, value, 
											&_hoops_PSIPI, _hoops_HHP,
											pattern, &length,
											pattern_items, &pattern_items_n))
					goto _hoops_PRSPR;
			}	break;

			default: {
				if (!_hoops_ISIPI (_hoops_RIGC, _hoops_RIIPI, &_hoops_RPPA, _hoops_SSRPR,
										&_hoops_SSIPI, &_hoops_GGCPI, &_hoops_RGCPI,
										&_hoops_AGCPI, &_hoops_PGCPI,
										&_hoops_ASIPI, value, 
										&_hoops_PSIPI, _hoops_HHP,
										pattern, &length,
										pattern_items, &pattern_items_n))
					goto _hoops_PRSPR;
			}	break;
		}
	}
	while (_hoops_RPPA < _hoops_SSRPR);

_hoops_PRSPR:

	//_hoops_CASI _hoops_GH _hoops_PCCP _hoops_GRCIR _hoops_HGS
	while (_hoops_RPPA < _hoops_SSRPR && (*_hoops_RPPA == ' ')) _hoops_RPPA++;

	if (_hoops_RPPA < _hoops_SSRPR) {
		char _hoops_HHCHR[MAX_ERRMSG];
		for (i=0;i<(unsigned int)pattern_items_n;i++) 
			_hoops_RGAIR(pattern_items[i].name);
		HE_ERROR (HEC_LINE_STYLE, HES_DEGENERATE_DEFINITION,
			Sprintf_S(_hoops_HHCHR, "Line style definition is degenerate --->", _hoops_RPPA));
		FREE (_hoops_RIIPI, Line_Style_Parallel);
		return false;
	}

_hoops_PRCPI:

	if (_hoops_RPPA == _hoops_HRCAR && line_style->_hoops_GHISR) {
		FREE (_hoops_RIIPI, Line_Style_Parallel);
	}
	else {
		if (length) {
			_hoops_RIIPI->_hoops_RHISR = length;
			ALLOC_ARRAY(_hoops_RIIPI->pattern, _hoops_RIIPI->_hoops_RHISR, int);
			_hoops_AIGA(pattern, length, int, _hoops_RIIPI->pattern);

			for (i=0; i<_hoops_RIIPI->_hoops_RHISR; i++) 
				if (_hoops_RIIPI->pattern[i] > 127) _hoops_RIIPI->flags |= LSF_LONG_LENGTHS;

			if (pattern_items_n == 0 && line_style->_hoops_IPCAP == 0) {
				_hoops_GIIPI (line_style, _hoops_RIIPI, 32);
				_hoops_GIIPI (line_style, _hoops_RIIPI, 16);
			}
			else {
				_hoops_RIIPI->pattern_items_n=pattern_items_n;
				if (_hoops_RIIPI->pattern_items_n) {
					ALLOC_ARRAY(_hoops_RIIPI->pattern_items, _hoops_RIIPI->pattern_items_n, Line_Style_Item);
					_hoops_AIGA(pattern_items, pattern_items_n, Line_Style_Item, _hoops_RIIPI->pattern_items);
					_hoops_RIIPI->flags |= LSF_PATTERN_ITEMS;
				}
			}
		}
		else {
			_hoops_RIIPI->flags |= LSF_SOLID;
			if (pattern_items_n) {
				for (i=0;i<(unsigned int)pattern_items_n;i++) 
					_hoops_RGAIR(pattern_items[i].name);
				HE_ERROR (HEC_LINE_STYLE, HES_DEGENERATE_DEFINITION,
					"Line style definition is degenerate");
				FREE (_hoops_RIIPI, Line_Style_Parallel);
				return false;
			}
		}

		// _hoops_AGGAR _hoops_GGR _hoops_CCAH _hoops_GGAIA
		_hoops_RIIPI->next = line_style->_hoops_GHISR;
		line_style->_hoops_GHISR = _hoops_RIIPI;
		line_style->_hoops_IPCAP++;

		while (_hoops_RPPA < _hoops_SSRPR && (*_hoops_RPPA == ' ')) _hoops_RPPA++;
		if (_hoops_RPPA < _hoops_SSRPR)
			goto _hoops_SGCPI;
	}

	// _hoops_RARHR _hoops_III _hoops_IAHA _hoops_SGI
	_hoops_RIIPI = line_style->_hoops_GHISR;
	do {
		if (BIT(_hoops_RIIPI->flags, LSF_ABSOLUTE_LENGTH) && 
			(_hoops_RIIPI->_hoops_RHISR == 0 && _hoops_RIIPI->pattern_items_n == 0))
			_hoops_RIIPI->flags &= ~LSF_ABSOLUTE_LENGTH;

		line_style->flags |= _hoops_RIIPI->flags;
	} while ((_hoops_RIIPI = _hoops_RIIPI->next) != null);

	
	if (line_style->_hoops_IPCAP > 1 || 
		ANYBIT(line_style->flags, LSF_COMPLEX_ANYBITS)) {

		// _hoops_PSP _hoops_III _hoops_CCA _hoops_HRCPI _hoops_PAH _hoops_SHH _hoops_RPHSR
		line_style->flags &= ~LSF_SOLID;

		// _hoops_CRSRR _hoops_RH "_hoops_RPGR" _hoops_HSGP _hoops_III
		if (line_style->_hoops_IPCAP == 1 &&
			BIT(LSF_PATTERN_ITEMS, line_style->_hoops_GHISR[0].flags) &&
			!ANYBIT(~LSF_PATTERN_ITEMS, line_style->_hoops_GHISR[0].flags) &&
			line_style->_hoops_GHISR[0].pattern_items_n == 1 &&
			line_style->_hoops_GHISR[0].pattern[0] == _hoops_RPCAP &&
			line_style->_hoops_GHISR[0].pattern_items[0].size._hoops_HHP == GSU_PIXELS &&
			line_style->_hoops_GHISR[0].pattern_items[0].size.value == (float)_hoops_IICIA)
			line_style->flags |= _hoops_CRCAP;
	}

	line_style->id = _hoops_CIAGP (&HOOPS_WORLD->global_id);
	
	return true;
}


#ifndef _hoops_IRCPI
local Attribute * _hoops_CRCPI (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR) 
{
	_hoops_APAIR const *	_hoops_CRGIH = (_hoops_APAIR const *)_hoops_CPACR;
	_hoops_APAIR alter *	_hoops_SRGIH = (_hoops_APAIR alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (item);

	ASSERT(_hoops_SRGIH->count == 1);

	if (_hoops_CRGIH) {

		for (int i=0; i<_hoops_CRGIH->count; i++) {
			if (_hoops_CRGIH->keys[i] == _hoops_SRGIH->keys[0] &&
				_hoops_RAHSR(_hoops_SRGIH->_hoops_HPAIR[0]->name, _hoops_CRGIH->_hoops_HPAIR[i]->name)) {

				/* _hoops_IIIAA _hoops_PPR _hoops_SRAI */
				_hoops_PGRCA(_hoops_CRGIH)->_hoops_HPAIR[i] = _hoops_SRGIH->_hoops_HPAIR[0];

				_hoops_SRGIH->_hoops_HPAIR[0] = null;
				FREE_ARRAY(_hoops_SRGIH->_hoops_HPAIR, 1, Line_Style);
				FREE_ARRAY(_hoops_SRGIH->keys, 1, Integer32);

				_hoops_SRGIH->_hoops_HPAIR = _hoops_CRGIH->_hoops_HPAIR;
				_hoops_SRGIH->keys = _hoops_CRGIH->keys;
				_hoops_SRGIH->count = _hoops_CRGIH->count;

				_hoops_PGRCA(_hoops_CRGIH)->_hoops_HPAIR =null;
				_hoops_PGRCA(_hoops_CRGIH)->keys = null;
				_hoops_PGRCA(_hoops_CRGIH)->count = 0;

				return _hoops_SRGIH;
			}
		}

		// _hoops_HASC
		if (_hoops_CRGIH->count > 0) {
			int	count = _hoops_CRGIH->count+1;

			Line_Style *	_hoops_HPAIR;
			ZALLOC_ARRAY(_hoops_HPAIR, count, Line_Style);

			Integer32 *	keys;
			ALLOC_ARRAY(keys, count, Integer32);

			_hoops_AIGA(_hoops_SRGIH->_hoops_HPAIR, 1, Line_Style, _hoops_HPAIR);
			_hoops_AIGA(_hoops_SRGIH->keys, 1, Integer32, keys);
			FREE_ARRAY(_hoops_SRGIH->_hoops_HPAIR, 1, Line_Style);
			FREE_ARRAY(_hoops_SRGIH->keys, 1, Integer32);

			// _hoops_RGR _hoops_HRGR _hoops_HIGIP
			_hoops_AIGA(_hoops_CRGIH->keys, _hoops_CRGIH->count, Integer32, &keys[1]);
			_hoops_AIGA(_hoops_CRGIH->_hoops_HPAIR, _hoops_CRGIH->count, Line_Style, &_hoops_HPAIR[1]);
			FREE_ARRAY(_hoops_CRGIH->_hoops_HPAIR, _hoops_CRGIH->count, Line_Style);
			FREE_ARRAY(_hoops_CRGIH->keys, _hoops_CRGIH->count, Integer32);
			_hoops_PGRCA(_hoops_CRGIH)->_hoops_HPAIR =null;
			_hoops_PGRCA(_hoops_CRGIH)->keys = null;
			_hoops_PGRCA(_hoops_CRGIH)->count = 0;

			_hoops_SRGIH->_hoops_HPAIR = _hoops_HPAIR;
			_hoops_SRGIH->keys = keys;
			_hoops_SRGIH->count = count;
		}
	}

	return _hoops_SRGIH;
}

local Line_Style _hoops_SRCPI (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HCRPR *					name,
	char const *			definition) 
{

	/* _hoops_RARIR _hoops_PGRIP */
	if (!definition) { 
		HE_WARNING (HEC_LINE_STYLE, HES_INVALID_INPUT, 
				Sprintf_N (null, "Line_Style '%n' has null definition ",&name));
		return null;
	}

	Line_Style	line_style = Line_Style::Create();

	HI_Canonize_Chars (definition, &line_style->definition);

	/* _hoops_SRAI _hoops_RSIRR */
	line_style->name.text = name->text;
	line_style->name.length = name->length;
	name->text = null;
	name->length = 0;

	/* _hoops_GISA _hoops_IRS _hoops_CCAH _hoops_PGRIP _hoops_IPPHR */
	if (!HI_Validate_Line_Style(_hoops_RIGC, line_style)) {
		HE_WARNING (HEC_LINE_STYLE, HES_INVALID_INPUT, 
					Sprintf_N (null, "Line_Style '%n' has bad definition ",&line_style->name));
		return null;
	}

	_hoops_HCARA(line_style->name,line_style->key);

	return line_style;
}
#endif



GLOBAL_FUNCTION bool HI_Set_Line_Style_Defs(
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_HPAH *				item, 
	_hoops_APAIR *		line_style)
{
	return HI_Set_Attribute (_hoops_RIGC, item, _hoops_RPAIR, _hoops_CRCPI, line_style);
}

HC_INTERFACE void HC_CDECL HC_Define_Line_Style (
	char const *			name,
	char const *			definition) 
{
	_hoops_PAPPR context("Define_Line_Style");

#ifdef _hoops_IRCPI
	_hoops_IRPPR ("Line_Style");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Define_Line_Style (%S, %S);\n", name, definition));
	);

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars (name, &_hoops_CRPCR);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_LINE_STYLE, HES_NULL_INPUT, "Line_Style name is blank or null");
		return;
	}

	Line_Style line_style = _hoops_SRCPI (context, &_hoops_CRPCR, definition);


	if (line_style != null) {

		bool				used = false;
		_hoops_APAIR *	_hoops_GACPI;
		ZALLOC (_hoops_GACPI, _hoops_APAIR);
		_hoops_GACPI->count = 1;
		ZALLOC_ARRAY(_hoops_GACPI->_hoops_HPAIR, 1, Line_Style);
		ALLOC_ARRAY(_hoops_GACPI->keys, 1, Integer32);

		_hoops_GACPI->_hoops_HPAIR[0] = line_style;
		_hoops_GACPI->keys[0] = line_style->key;

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_CARPP)) != null) {
			used = HI_Set_Line_Style_Defs(context, target, _hoops_GACPI);
			_hoops_IRRPR();
		}

		if (!used) {
			FREE_ARRAY(_hoops_GACPI->_hoops_HPAIR, 1, Line_Style);
			FREE_ARRAY(_hoops_GACPI->keys, 1, Integer32);
			FREE (_hoops_GACPI, _hoops_APAIR);
		}
	}

	_hoops_RGAIR(_hoops_CRPCR);
#endif
}



GLOBAL_FUNCTION void HI_UnSet_Defined_Line_Style(
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_HPAH *				item, 
	_hoops_HCRPR const &			_hoops_CRPCR) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_APAIR * _hoops_RACPI = (_hoops_APAIR *) HI_Find_Attribute(_hoops_RIGC, item, -_hoops_RPAIR);

	if (!_hoops_RACPI) {
		HE_ERROR (HEC_LINE_STYLE, HES_INVALID_INPUT, "No Line_Style definitions found");
		goto Release;
	}

	Integer32	key;
	_hoops_HCARA(_hoops_CRPCR,key); 

	for (int i=0; i<_hoops_RACPI->count; i++) {
		if (_hoops_RACPI->keys[i] == key && _hoops_RAHSR(_hoops_CRPCR, _hoops_RACPI->_hoops_HPAIR[i]->name)) {
			_hoops_RACPI->_hoops_HPAIR[i] = null;

			if (_hoops_RACPI->count == 1) {
				FREE_ARRAY(_hoops_RACPI->_hoops_HPAIR, 1, Line_Style);
				FREE_ARRAY(_hoops_RACPI->keys, 1, Integer32);
				_hoops_RACPI->_hoops_HPAIR = null;
				_hoops_RACPI->keys = null;
				_hoops_RACPI->count = 0;
			}
			else {
				Line_Style *		_hoops_AHRIP;
				Integer32 *				new_keys;
				int						_hoops_RGCCA;

				_hoops_RGCCA = _hoops_RACPI->count-1;

				ZALLOC_ARRAY(_hoops_AHRIP, _hoops_RGCCA, Line_Style);
				ALLOC_ARRAY(new_keys, _hoops_RGCCA, Integer32);

				if (i > 0) {
					_hoops_AIGA(_hoops_RACPI->_hoops_HPAIR, i, Line_Style, _hoops_AHRIP);
					_hoops_AIGA(_hoops_RACPI->keys, i, Integer32, new_keys);
				}

				if (i < _hoops_RGCCA) {
					_hoops_AIGA(&_hoops_RACPI->_hoops_HPAIR[i+1], _hoops_RGCCA-i, Line_Style, &_hoops_AHRIP[i]);
					_hoops_AIGA(&_hoops_RACPI->keys[i+1], _hoops_RGCCA-i, Integer32, &new_keys[i]);
				}

				FREE_ARRAY(_hoops_RACPI->_hoops_HPAIR, _hoops_RACPI->count, Line_Style);
				FREE_ARRAY(_hoops_RACPI->keys, _hoops_RACPI->count, Integer32);

				_hoops_RACPI->_hoops_HPAIR = _hoops_AHRIP;
				_hoops_RACPI->keys = new_keys;
				_hoops_RACPI->count = _hoops_RGCCA;
			}

			goto Release;
		}
	}

	HE_WARNING (HEC_LINE_STYLE, HES_INVALID_INPUT, Sprintf_N (null, "Line_Style '%n' not found ",&_hoops_CRPCR));

Release:
	if (_hoops_RACPI)
		_hoops_HPRH(_hoops_RACPI);
}

HC_INTERFACE void HC_CDECL HC_UnDefine_Line_Style (
	char const *			name) 
{
	_hoops_PAPPR context("UnDefine_Line_Style");

#ifdef _hoops_AACPI
	_hoops_IRPPR ("Line_Style");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnDefine_Line_Style (%S);\n", name));
	);

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars (name, &_hoops_CRPCR);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_LINE_STYLE, HES_NULL_INPUT, "Line_Style name is blank or null");
		return;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_CARPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Defined_Line_Style(context, target, _hoops_CRPCR);
		_hoops_IRRPR();
	}

	_hoops_RGAIR(_hoops_CRPCR);
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Line_Style (
	char const *		name,
	char *				definition) 
{
	_hoops_PAPPR context("Show_Line_Style");

#ifdef _hoops_IRCPI
	_hoops_IRPPR ("Line_Style");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Line_Style () */\n");
	);

	definition[0] = '\0';

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars (name, &_hoops_CRPCR);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_LINE_STYLE, HES_NULL_INPUT, "Line_Style name is blank or null");
		return;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HCRPP)) != null) {

		_hoops_APAIR *	_hoops_RACPI;

		if ((_hoops_RACPI = (_hoops_APAIR *) HI_Find_Attribute(context, target, _hoops_RPAIR)) != null) {

			Integer32	key;
			_hoops_HCARA(_hoops_CRPCR,key); 

			for (int i=0; i<_hoops_RACPI->count; i++) {
				if (_hoops_RACPI->keys[i] == key && _hoops_RAHSR(_hoops_CRPCR, _hoops_RACPI->_hoops_HPAIR[i]->name)) {
					Line_Style	line_style = _hoops_RACPI->_hoops_HPAIR[i];
					HI_Return_Chars (definition, -1, line_style->definition.text, line_style->definition.length);
					break;
				}
			}
			_hoops_HPRH(_hoops_RACPI);
		}
		_hoops_IRRPR();
	}

	_hoops_RGAIR (_hoops_CRPCR);
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Line_Style_Size (
	char const *			name,
	int *					size) 
{
	_hoops_PAPPR context("Show_Line_Style_Size");

#ifdef _hoops_IRCPI
	_hoops_IRPPR ("Line_Style");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Line_Style_Size () */\n");
	);

	*size = 0;

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars (name, &_hoops_CRPCR);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_LINE_STYLE, HES_NULL_INPUT, "Line_Style name is blank or null");
		return;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HCRPP)) != null) {

		_hoops_APAIR *	_hoops_RACPI;

		if ((_hoops_RACPI = (_hoops_APAIR *) HI_Find_Attribute(context, target, _hoops_RPAIR)) != null) {

			Integer32	key;
			_hoops_HCARA(_hoops_CRPCR,key); 

			for (int i=0; i<_hoops_RACPI->count; i++) {
				if (_hoops_RACPI->keys[i] == key && _hoops_RAHSR(_hoops_CRPCR, _hoops_RACPI->_hoops_HPAIR[i]->name)) {
					Line_Style	line_style = _hoops_RACPI->_hoops_HPAIR[i];
					*size = (int) line_style->definition.length;
					break;
				}
			}

			_hoops_HPRH(_hoops_RACPI);
		}
		_hoops_IRRPR();
	}

	_hoops_RGAIR (_hoops_CRPCR);
#endif
}

HC_INTERFACE void HC_CDECL HC_PShow_Net_Line_Style (
	int						count,
	Key const *				keys,
	char const *			name,
	char *					definition) 
{
	_hoops_PAPPR context("PShow_Net_Line_Style");

#ifdef _hoops_IRCPI
	_hoops_IRPPR ("Line_Style");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Line_Style () */\n");
	);

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars (name, &_hoops_CRPCR);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_LINE_STYLE, HES_NULL_INPUT, "Line_Style name is blank or null");
		return;
	}

	definition[0] = '\0';

	_hoops_APAIR *	_hoops_RACPI;
	if ((_hoops_RACPI = (_hoops_APAIR *) HI_Find_Attribute_And_Lock(context, _hoops_HCRPP, _hoops_HRPCR, count, keys)) != null) {

		Integer32	key;
		_hoops_HCARA(_hoops_CRPCR,key); 

		Line_Style	line_style;
		for (int i=0; i<_hoops_RACPI->count; i++) {
			if (_hoops_RACPI->keys[i] == key && _hoops_RAHSR(_hoops_CRPCR, _hoops_RACPI->_hoops_HPAIR[i]->name)) {
				line_style = _hoops_RACPI->_hoops_HPAIR[i];
				break;
			}
		}

		_hoops_HPRH(_hoops_RACPI);

		if (line_style != null)
			HI_Return_Chars (definition, -1, line_style->definition.text, line_style->definition.length);
		else 
			HE_ERROR (HEC_LINE_STYLE, HES_DEFINITION_NOT_FOUND,
				Sprintf_N (null, "Line_Style '%n' not found", &_hoops_CRPCR));

		_hoops_IRRPR();
	}
	else
		HE_ERROR (HEC_LINE_STYLE, HES_INVALID_INPUT, "No Line_Style definitions found");

	_hoops_RGAIR (_hoops_CRPCR);
#endif
}



HC_INTERFACE void HC_CDECL HC_PShow_Net_Line_Style_Size (
	int						count,
	Key const *				keys,
	char const *			name,
	int *					size) {
	_hoops_PAPPR context("PShow_Net_Line_Style_Size");

#ifdef _hoops_IRCPI
	_hoops_IRPPR ("Line_Style");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Line_Style_Size () */\n");
	);

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars (name, &_hoops_CRPCR);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_LINE_STYLE, HES_NULL_INPUT, "Line_Style name is blank or null");
		return;
	}

	*size = 0;

	_hoops_APAIR *	_hoops_RACPI;
	if ((_hoops_RACPI = (_hoops_APAIR *) HI_Find_Attribute_And_Lock(context, _hoops_HCRPP, _hoops_HRPCR, count, keys)) != null) {

		Integer32	key;
		_hoops_HCARA(_hoops_CRPCR,key); 

		Line_Style	line_style;
		for (int i=0; i<_hoops_RACPI->count; i++) {
			if (_hoops_RACPI->keys[i] == key && _hoops_RAHSR(_hoops_CRPCR, _hoops_RACPI->_hoops_HPAIR[i]->name)) {
				line_style = _hoops_RACPI->_hoops_HPAIR[i];
				break;
			}
		}

		_hoops_HPRH(_hoops_RACPI);

		if (line_style != null) 
			*size = (int) line_style->definition.length;
		else 
			HE_ERROR (HEC_LINE_STYLE, HES_DEFINITION_NOT_FOUND,
				Sprintf_N (null, "Line_Style '%n' not found", &_hoops_CRPCR));

		_hoops_IRRPR();
	}
	else
		HE_ERROR (HEC_LINE_STYLE, HES_INVALID_INPUT, "No Line_Style definitions found");

	_hoops_RGAIR (_hoops_CRPCR);
#endif
}



#ifndef DISABLE_SEARCH
#ifndef _hoops_IRCPI
local void _hoops_PACPI (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP * _hoops_SRCP)
{
	_hoops_SSPPR *		_hoops_GGHPR;
	_hoops_AGHPR *		node;

	ZALLOC (_hoops_GGHPR, _hoops_SSPPR);
	_hoops_GGHPR->prev = _hoops_RIGC->_hoops_GIPGI;
	_hoops_RIGC->_hoops_GIPGI = _hoops_GGHPR;

	if (_hoops_SRCP == null) {
		if (_hoops_RIGC->open_list != null && _hoops_RIGC->open_list->_hoops_GCRIR == _hoops_RCRIR ||
			HI_Find_Our_Open (_hoops_RIGC)) {

			if (_hoops_RIGC->open_list->_hoops_GCRIR == _hoops_RCRIR)
				_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_IGRPR;
			else {
				HE_ERROR (HEC_LINE_STYLE, HES_NO_OPEN_SEGMENT, "Line_Styles require open segment");
				return;
			}
		}
		else {
			HE_ERROR (HEC_LINE_STYLE, HES_NO_OPEN_SEGMENT, "Line_Style require open segment, none can be found");
			return;
		}
	}

	_hoops_APAIR * _hoops_RACPI = (_hoops_APAIR *) HI_Find_Attribute (_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP, -_hoops_RPAIR);

	if (_hoops_RACPI) {
		for (int i=0; i<_hoops_RACPI->count; i++) {
			Line_Style *		_hoops_ACCI;

			ZALLOC (_hoops_ACCI, Line_Style);
			*_hoops_ACCI = _hoops_RACPI->_hoops_HPAIR[i];

			ALLOC (node, _hoops_AGHPR);
			node->next = _hoops_GGHPR->list;
			_hoops_GGHPR->list = node;
			node->item = (_hoops_HPAH *)_hoops_ACCI;
			node->_hoops_AGRI = false;
			++_hoops_GGHPR->count;
		}

		_hoops_HPRH(_hoops_RACPI);
	}
}
#endif
#endif

HC_INTERFACE void HC_CDECL HC_Begin_Line_Style_Search (void) {
	_hoops_PAPPR context("Begin_Line_Style_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef _hoops_IRCPI
	_hoops_IRPPR ("Line_Style");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Begin_Line_Style_Search () */\n");
		++HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_CSPPR();
	_hoops_PACPI (context, null);
	_hoops_IRRPR();

#endif
#endif
}
 

HC_INTERFACE bool HC_CDECL HC_Find_Line_Style (
	char *				_hoops_IAGIH) 
{
	_hoops_PAPPR context("Find_Line_Style");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef _hoops_IRCPI
	_hoops_IRPPR ("Line_Style");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Find_Line_Style () */\n");
	);

	_hoops_AGHPR	*			list;

	if (context->_hoops_GIPGI == null) {
		HE_ERROR (HEC_LINE_STYLE, HES_INACTIVE_SEARCH, "No line_style search is active");
		return false;
	}

	if ((list = context->_hoops_GIPGI->list) != null) {
		Line_Style *	item = (Line_Style *)list->item;

		context->_hoops_GIPGI->list = list->next;
		FREE (list, _hoops_AGHPR);
		list = context->_hoops_GIPGI->list;

		HI_Return_Sprintf1 (_hoops_IAGIH, -1, "%n", (void *)&(*item)->name);

		*item = null;
		FREE (item, Line_Style);

		return true;
	}

#endif
#endif

	return false;
}



HC_INTERFACE void HC_CDECL HC_Show_Line_Style_Count (
	int *					count) {
	_hoops_SSPPR *			_hoops_GGHPR;
	_hoops_PAPPR context("Show_Line_Style_Count");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef _hoops_IRCPI
	_hoops_IRPPR ("Line_Style");
	*count = 0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Line_Style_Count () */\n");
	);

	_hoops_GGHPR = context->_hoops_GIPGI;
	if (_hoops_GGHPR == null) {
		*count = 0;
		HE_ERROR (HEC_LINE_STYLE, HES_INACTIVE_SEARCH,"No line_style search is active");
	}
	else
		*count = _hoops_GGHPR->count;
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_End_Line_Style_Search (void) {
	_hoops_SSPPR *			_hoops_GGHPR;
	_hoops_AGHPR				*node, *_hoops_CAGIH;
	_hoops_PAPPR context("End_Line_Style_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef _hoops_HACPI
	_hoops_IRPPR ("Line_Style");
#else
	CODE_GENERATION (
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("/* HC_End_Line_Style_Search () */\n");
	);

	_hoops_GGHPR = context->_hoops_GIPGI;
	if (_hoops_GGHPR == null) {
		HE_ERROR (HEC_LINE_STYLE, HES_END_WITHOUT_BEGIN_SEARCH,"End without Begin");
		return;
	}
	node = _hoops_GGHPR->list;

	_hoops_RGGA (node == null) {
		_hoops_CAGIH = node->next;

		Line_Style *		item = (Line_Style *) node->item;
		*item = null;
		FREE (item, Line_Style);

		FREE (node, _hoops_AGHPR);
		node = _hoops_CAGIH;
	}
	context->_hoops_GIPGI = _hoops_GGHPR->prev;
	FREE (_hoops_GGHPR, _hoops_SSPPR);
#endif
#endif
}


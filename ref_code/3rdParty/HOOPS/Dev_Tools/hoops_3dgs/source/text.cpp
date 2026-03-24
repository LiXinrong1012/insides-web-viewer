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
 * $Id: obf_tmp.txt 1.111 2010-10-06 19:16:14 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "patterns.h"
#include "adt.h"


struct _hoops_ARPGGR {
	Point				where;
	char const *		string;
	_hoops_IHGRP		encoding;

	_hoops_HACC *				text;
	int					_hoops_IGSSR;
};



local void _hoops_PRPGGR (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH *					owner,
	_hoops_ARPGGR *	data) 
{

	_hoops_HACC *	text;
	ZALLOC (text, _hoops_HACC);
	text->type = _hoops_AGCP;
	text->_hoops_CPGPR = _hoops_PHSSR;
	text->_hoops_HHGRP = (unsigned Integer32)~0;

	text->_hoops_CSAI = data->where;
	text->encoding = data->encoding;

	KName				_hoops_SIHSA;

	HI_Convert_Char_To_KName (data->string, &_hoops_SIHSA, data->encoding);
	text->karacters = _hoops_SIHSA._hoops_IPPPP;
	text->count = _hoops_SIHSA.length;

	if (text->karacters != null) {
		Karacter *			_hoops_RSSIH;
		int					_hoops_HRPGGR;
		int i;

		text->_hoops_PICHR = 1;
		for (i = 0; i < text->count; ++i) {
			if (text->karacters[i] == (Karacter)'\n')
				++text->_hoops_PICHR;
		}

		ALLOC_ARRAY (text->_hoops_ICI, text->_hoops_PICHR, int);
		ALLOC_ARRAY (text->_hoops_RIHIR, text->_hoops_PICHR, Karacter *);

		_hoops_HRPGGR = 0;
		/* _hoops_SPS _hoops_SPAHS _hoops_RH _hoops_PISC _hoops_AGIR _hoops_IIGR _hoops_IRS _hoops_HACH \_hoops_ACHP */
		text->_hoops_RIHIR[text->_hoops_PICHR-1] = &text->karacters[text->count];

		text->_hoops_RIHIR[0] = _hoops_RSSIH = text->karacters;
		for (i = 0; i < text->count; ++i) {
			if (text->karacters[i] == (Karacter)'\n') {
				if (_hoops_RSSIH != null)
					text->_hoops_ICI[_hoops_HRPGGR++] = &text->karacters[i] - _hoops_RSSIH;
				else {
					/* _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_GGR _hoops_IRS _hoops_GAGHR */
					text->_hoops_RIHIR[_hoops_HRPGGR] = &text->karacters[i];
					text->_hoops_ICI[_hoops_HRPGGR++] = 0;
				}
				_hoops_RSSIH = null;
			}
			else if (_hoops_RSSIH == null)
				text->_hoops_RIHIR[_hoops_HRPGGR] = _hoops_RSSIH = &text->karacters[i];
		}
		if (_hoops_RSSIH == null)
			text->_hoops_ICI[_hoops_HRPGGR] = 0;
		else
			text->_hoops_ICI[_hoops_HRPGGR] = &text->karacters[i] - _hoops_RSSIH;
	}

	HI_Insert_Geometry (_hoops_RIGC, owner, (Geometry *) text,
		text->_hoops_CSAI.z == 0.0f,
		_hoops_IHSSR|_hoops_RSCCA);

	data->text = text;
	++data->_hoops_IGSSR;
}



GLOBAL_FUNCTION Key HI_Insert_Text_With_Encoding (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const &			where,
	_hoops_IHGRP			encoding,
	void const *			string) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_ARPGGR data;
	ZERO_STRUCT(&data, _hoops_ARPGGR);
	data.where = where;	  
	data.string = (char const*)string;
	data.encoding = encoding;

	_hoops_PRPGGR (_hoops_RIGC, item, &data);

	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.text);

	return _hoops_CHSSR;
}


HC_INTERFACE Key HC_CDECL HC_Insert_Text (
	double			x,
	double			y,
	double			z,
	char const *	string) 
{
	_hoops_PAPPR context("Insert_Text");

	if (string == null)
		string = "\0";

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Text_With_Encoding (context, target, Point(x,y,z), HOOPS_WORLD->encoding, (void const *)string);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "DEFINE (HC_Insert_Text (%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F, ", z));
		HI_Dump_Code (Sprintf_S (null, "%S), ", string));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
	);

	return _hoops_CHSSR;
}



HC_INTERFACE Key HC_CDECL HC_Insert_Text_With_Encoding (
	double					x,
	double					y,
	double					z,
	char const *			encoding,
	void const *			string) 
{
	_hoops_PAPPR context("Insert_Text_With_Encoding");

	_hoops_IHGRP	_hoops_IRPGGR = HI_Decipher_Encoding(context, encoding);

	if (_hoops_IRPGGR == _hoops_PIIGI) 
		return _hoops_SHSSR;

	unsigned short _hoops_AHRCC = 0;

	if (string == null)
		string = (unsigned short const *)&_hoops_AHRCC;

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Text_With_Encoding (context, target, Point(x,y,z), _hoops_IRPGGR, string);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "DEFINE (HC_Insert_Text_With_Encoding (%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F, ", z));
		HI_Dump_Code ("\"utf8\", ");
		H_UTF8 _hoops_ASPPH;
		if (_hoops_IGGPA(encoding, "utf8")) {
			_hoops_ASPPH.encodedText((utf8_char const*) string);
		}
		else if (_hoops_IGGPA(encoding, "utf16")|| _hoops_IGGPA(encoding, "unicode")) {
			H_UTF16 _hoops_RSPPH;
			_hoops_RSPPH.encodedText((utf16_char const*) string);
			_hoops_ASPPH = H_UTF8(_hoops_RSPPH);
		}
		else if (_hoops_IGGPA(encoding, "utf32")) {
			H_UTF32 _hoops_ISPPH;
			_hoops_ISPPH.encodedText((utf32_char const*) string);
			_hoops_ASPPH = H_UTF8(_hoops_ISPPH);
		}
		else if (_hoops_IGGPA(encoding, "wcs")) {
			H_WCS _hoops_GGHPH;
			_hoops_GGHPH.encodedText((wchar_t const*) string);
			_hoops_ASPPH = H_UTF8(_hoops_GGHPH);
		}
		else if (_hoops_IGGPA(encoding, "mbs")) {
			_hoops_ASPPH = H_UTF8((char const*) string);
		}
		else {
			_hoops_ASPPH = H_UTF8("encoding not handled");
		}
		HI_Dump_Code (Sprintf_S (null, "%S), ", _hoops_ASPPH.encodedText()));
		HI_Dump_Code (Sprintf_LD (null, "%D);", _hoops_CHSSR));
		if (!_hoops_IGGPA(encoding, "utf8"))
			HI_Dump_Code (Sprintf_S (null, " /* <- converted from %S to \"utf8\" for code generation */\n", _hoops_ASPPH.encodedText()));
		else
			HI_Dump_Code ("\n");
	);

	return _hoops_CHSSR;
}


HC_INTERFACE Key HC_CDECL HC_Insert_Unicode_Text (
	double					x,
	double					y,
	double					z,
	unsigned short const *	_hoops_AGRIH) 
{
	_hoops_PAPPR context("Insert_Unicode_Text");

	unsigned short _hoops_AHRCC = 0;

	if (_hoops_AGRIH == null)
		_hoops_AGRIH = (unsigned short const *)&_hoops_AHRCC;

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Text_With_Encoding (context, target, Point(x,y,z), _hoops_SACSR, (void const *)_hoops_AGRIH);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		unsigned short * _hoops_CRPGGR = (unsigned short *)_hoops_AGRIH;
		int len=1;
		while (*_hoops_CRPGGR++ != (unsigned short)'\0')
			len++;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "short* widechars = (short*) malloc(sizeof(short)*%d);\n", len));
		for (int i=0; i<len; i++) // _hoops_HAPR _hoops_RHIR _hoops_PPR _hoops_HSPC _hoops_GRR
			HI_Dump_Code (Sprintf_DD (null, "widechars[%d] = %o;\n", i, _hoops_AGRIH[i]));
		HI_Dump_Code (Sprintf_FF (null, "DEFINE (HC_Insert_Unicode_Text (%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F, widechars), ", z));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
		HI_Dump_Code ("free (widechars);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	return _hoops_CHSSR;
}


HC_INTERFACE void HC_CDECL HC_Show_Text (
	Key				key,
	float *			x,
	float *			y,
	float *			z,
	char *			text)
{	
	_hoops_PAPPR context("Show_Text");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Text () */\n");
	);

	_hoops_CSPPR();

	_hoops_HACC *	_hoops_SRPGGR = (_hoops_HACC *)_hoops_RCSSR (context, key);

	if (_hoops_SRPGGR == null ||
		_hoops_SRPGGR->type != _hoops_AGCP ||
		BIT (_hoops_SRPGGR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TEXT, HES_INVALID_KEY, "Provided key does not refer to valid text");
	}
	else {
		if (x != null)
			*x = _hoops_SRPGGR->_hoops_CSAI.x;
		if (y != null)
			*y = _hoops_SRPGGR->_hoops_CSAI.y;
		if (z != null)
			*z = _hoops_SRPGGR->_hoops_CSAI.z;

		if (text != null)
			HI_Return_Kars (text, -1, _hoops_SRPGGR->karacters, _hoops_SRPGGR->count, _hoops_SRPGGR->encoding);
	}

	_hoops_IRRPR();
#endif
}




HC_INTERFACE void HC_CDECL HC_Show_Text_Count (
	Key			key,
	int *		count) 
{
	_hoops_PAPPR context("Show_Text_Count");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Text_Count () */\n");
	);

	_hoops_CSPPR();

	_hoops_HACC *	_hoops_SRPGGR = (_hoops_HACC *)_hoops_RCSSR (context, key);

	if (_hoops_SRPGGR == null || _hoops_SRPGGR->type != _hoops_AGCP ||
		BIT (_hoops_SRPGGR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TEXT, HES_INVALID_KEY, "Provided key does not refer to valid text");
	}
	else {
		*count = _hoops_SRPGGR->count;	/* _hoops_PHI _hoops_IIGR _hoops_HPS */
	}

	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Text_Length (
	Key			key,
	int *		length) 
{
	_hoops_PAPPR context("Show_Text_Length");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Text_Length () */\n");
	);

	_hoops_CSPPR();

	_hoops_HACC *	_hoops_SRPGGR = (_hoops_HACC *)_hoops_RCSSR (context, key);

	if (_hoops_SRPGGR == null || _hoops_SRPGGR->type != _hoops_AGCP ||
		BIT (_hoops_SRPGGR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TEXT, HES_INVALID_KEY, "Provided key does not refer to valid text");
	}
	else {
		/* _hoops_CGIC _hoops_PHI _hoops_IIGR _hoops_GCSRR _hoops_RGHP */

		switch (_hoops_SRPGGR->encoding) {
			case _hoops_SSAIP:*length = _hoops_SRPGGR->count;		break;
			
			case _hoops_GSPPH:{
				if (_hoops_SRPGGR->karacters) {
					H_UTF16 _hoops_RSPPH;
					_hoops_RSPPH.encodedText((utf16_char const*)_hoops_SRPGGR->karacters);
					H_UTF8 _hoops_ASPPH(_hoops_RSPPH);
					utf8_char const * _hoops_PSPPH = _hoops_ASPPH.encodedText();
					while(*_hoops_PSPPH != 0) ++_hoops_PSPPH;
					*length = _hoops_PSPPH - _hoops_ASPPH.encodedText();
				}
				else *length = 0;
			} break;

			case _hoops_HSPPH:{
				if (_hoops_SRPGGR->karacters) {
					H_UTF16 _hoops_RSPPH;
					_hoops_RSPPH.encodedText((utf16_char const*)_hoops_SRPGGR->karacters);
					H_UTF32 _hoops_ISPPH(_hoops_RSPPH);
					utf32_char const * _hoops_PSPPH = _hoops_ISPPH.encodedText();
					while(*_hoops_PSPPH != 0) ++_hoops_PSPPH;
					*length = (int)(sizeof(utf32_char) * (_hoops_PSPPH - _hoops_ISPPH.encodedText()));
				}
				else *length = 0;
			} break;
			
			case _hoops_CSPPH:
			case _hoops_SSPPH:{
				if (_hoops_SRPGGR->karacters) {
					H_UTF16 _hoops_RSPPH;
					_hoops_RSPPH.encodedText((utf16_char const*)_hoops_SRPGGR->karacters);
					H_WCS _hoops_GGHPH(_hoops_RSPPH);
					wchar_t const * _hoops_PSPPH = _hoops_GGHPH.encodedText();
					while(*_hoops_PSPPH != L'\0') ++_hoops_PSPPH;
					*length = (int)(sizeof(wchar_t) * (_hoops_PSPPH - _hoops_GGHPH.encodedText()));
				}
				else *length = 0;
			} break;
			
			case _hoops_RGHPH:
			case _hoops_AGHPH:
			case _hoops_SACSR:		*length = 2 * _hoops_SRPGGR->count; break;

			default: {	/* _hoops_AA _hoops_SCH _hoops_RH _hoops_ACIPR _hoops_PPRRR */
				Karacter		*_hoops_IHSCP = _hoops_SRPGGR->karacters;
				int				count = _hoops_SRPGGR->count;

				*length = 0;
				while (count-- > 0) {
					if ((*_hoops_IHSCP++ & 0xFF00) != 0)
						*length += 2;
					else
						(*length)++;
				}
			}	break;
		}
	}

	_hoops_IRRPR();
#endif
}


GLOBAL_FUNCTION void HI_Show_Encoding_Type (
	char *				string,
	int					length,
	_hoops_IHGRP		encoding) 
{
	switch (encoding) {
		case _hoops_SSAIP: {
				HI_Return_Chars (string, length, "iso latin one", 13);
		}	break;
		case _hoops_HIIGI: {
				HI_Return_Chars (string, length, "iso latin", 9);
		}	break;

		case _hoops_RPHPH: {
				HI_Return_Chars (string, length, "jec", 3);
		}	break;
		case _hoops_APHPH: {
				HI_Return_Chars (string, length, "euc", 3);
		}	break;

		case _hoops_RGHPH: {
				HI_Return_Chars (string, length, "16", 2);
		}	break;

		case _hoops_SACSR: {
				HI_Return_Chars (string, length, "unicode", 7);
		}	break;

		case _hoops_GSPPH: {
				HI_Return_Chars (string, length, "utf8", 4);
		}	break;

		case _hoops_AGHPH: {
				HI_Return_Chars (string, length, "utf16", 5);
		}	break;

		case _hoops_HSPPH: {
				HI_Return_Chars (string, length, "utf32", 5);
		}	break;

		case _hoops_CSPPH: /* _hoops_GAPGGR _hoops_RAPSR _hoops_RHIPP _hoops_GRS _hoops_SHH _hoops_GIIA _hoops_GAR _hoops_RAPGGR _hoops_GSGR (_hoops_AAPGGR). */
		case _hoops_SSPPH: {
				HI_Return_Chars (string, length, "wcs", 3);
		}	break;

		default: {
				HI_Return_Chars (string, length, "", 0);
		}	break;
	}
}

HC_INTERFACE void HC_CDECL HC_Show_Text_With_Encoding (
	Key			key,
	float *		x,
	float *		y,
	float *		z,
	char *		encoding,
	void *		text) 
{
	_hoops_PAPPR context("Show_Text_With_Encoding");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Text_With_Encoding () */\n");
	);

	_hoops_CSPPR();

	_hoops_HACC *	_hoops_SRPGGR = (_hoops_HACC *)_hoops_RCSSR (context, key);

	if (_hoops_SRPGGR == null ||
		_hoops_SRPGGR->type != _hoops_AGCP ||
		BIT (_hoops_SRPGGR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TEXT, HES_INVALID_KEY, "Provided key does not refer to valid text");
	}
	else {
		if (x != null)
			*x = _hoops_SRPGGR->_hoops_CSAI.x;
		if (y != null)
			*y = _hoops_SRPGGR->_hoops_CSAI.y;
		if (z != null)
			*z = _hoops_SRPGGR->_hoops_CSAI.z;

		if (text != null)
			HI_Return_Kars ((char*)text, -1, _hoops_SRPGGR->karacters, _hoops_SRPGGR->count, _hoops_SRPGGR->encoding);
		if (encoding != null)
			HI_Show_Encoding_Type (encoding, -1, _hoops_SRPGGR->encoding);
	}

	_hoops_IRRPR();
#endif
}





HC_INTERFACE void HC_CDECL HC_Show_Text_Encoding (
	Key			key,
	char *		encoding) 
{
	_hoops_PAPPR context("Show_Text_Encoding");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Text_Encoding () */\n");
	);

	_hoops_CSPPR();

	_hoops_HACC *	_hoops_SRPGGR = (_hoops_HACC *)_hoops_RCSSR (context, key);

	if (_hoops_SRPGGR == null ||
		_hoops_SRPGGR->type != _hoops_AGCP ||
		BIT (_hoops_SRPGGR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TEXT, HES_INVALID_KEY, "Provided key does not refer to valid text");
	}
	else {
		HI_Show_Encoding_Type (encoding, -1, _hoops_SRPGGR->encoding);
	}

	_hoops_IRRPR();
#endif
}




HC_INTERFACE void HC_CDECL HC_Show_Unicode_Text (
	Key					key,
	float *				x,
	float *				y,
	float *				z,
	unsigned short *	text) 
{
	_hoops_PAPPR context("Show_Unicode_Text");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Unicode_Text () */\n");
	);

	_hoops_CSPPR();
	_hoops_HACC *	_hoops_SRPGGR = (_hoops_HACC *)_hoops_RCSSR (context, key);

	if (_hoops_SRPGGR == null || _hoops_SRPGGR->type != _hoops_AGCP ||
		BIT (_hoops_SRPGGR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TEXT, HES_INVALID_KEY, "Provided key does not refer to valid text");
	}
	else {
		/* _hoops_ASRHR/_hoops_RIHH _hoops_RPP _hoops_HAR _hoops_PAPGGR/_hoops_CSPGA? */

		if (x != null)
			*x = _hoops_SRPGGR->_hoops_CSAI.x;
		if (y != null)
			*y = _hoops_SRPGGR->_hoops_CSAI.y;
		if (z != null)
			*z = _hoops_SRPGGR->_hoops_CSAI.z;

		if (text != null) {
			Karacter const *	_hoops_IHSCP = _hoops_SRPGGR->karacters;
			int					count = _hoops_SRPGGR->count;

			while (count-- > 0)
				*text++ = *_hoops_IHSCP++;
			*text = 0;
		}
	}

	_hoops_IRRPR();
#endif
}




HC_INTERFACE void HC_CDECL HC_Move_Text (
	Key				key,
	double			x,
	double			y,
	double			z) 
{
	_hoops_PAPPR context("Move_Text");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Move_Text (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F);\n", z));
	);


	_hoops_RPPPR();

	_hoops_HACC *	text = (_hoops_HACC *)_hoops_RCSSR (context, key);

	if (text == null || text->type != _hoops_AGCP ||
		BIT (text->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TEXT, HES_INVALID_KEY, "Provided key does not refer to a valid \"Text\" item");
	}
	else {

		_hoops_CRCP *	_hoops_SRCP = text->owner;

#ifndef DISABLE_PARTIAL_ERASE
		if (text->count > 0) {		/* _hoops_PSP _hoops_AIIAP _hoops_RPP _hoops_RHPA */
			Geometry *		_hoops_HCIS;
			/* _hoops_GRHP _hoops_IRS _hoops_RSPH _hoops_IPS _hoops_AARI _hoops_IH _hoops_IASI-_hoops_AHPIP _hoops_IS _hoops_SGH */
			_hoops_HCIS = HI_Copy_Geometry (context, (Geometry *)text);
			_hoops_HCIS->_hoops_RRHH = _hoops_HGAGR;

			/* _hoops_AGGAR _hoops_SPCS _hoops_SPS _hoops_IS _hoops_GIGR */
			if ((_hoops_HCIS->next = _hoops_SRCP->_hoops_SCGPR()) != null)
				_hoops_HCIS->next->backlink = &_hoops_HCIS->next;
			_hoops_SRCP->_hoops_RSGPR (_hoops_HCIS);
		}
#endif

		text->_hoops_CSAI = Point(x,y,z);
		text->_hoops_CPGPR |= _hoops_HHSSR;

		if (!BIT (text->_hoops_RRHH, _hoops_RSPCR)) {
			if (text->_hoops_CSAI.z != 0.0f) {
				text->_hoops_RRHH |= _hoops_RSPCR;
				if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_ASPCR))
					HI_Propagate_Maybes (context, _hoops_SRCP, _hoops_ASPCR);
			}
		}

		if (text->count > 0)		/* _hoops_PSP _hoops_AIIAP _hoops_RPP _hoops_RHPA */
			_hoops_SASIR (context, _hoops_SRCP, _hoops_HRCCA|_hoops_GGARA|
									 _hoops_PISSR|_hoops_RPSIR);

	}

	_hoops_IRRPR();
}



local void _hoops_HAPGGR (
	int				left,
	Karacter		*karacters,
	int				count,
	Karacter		*_hoops_IAPGGR) {
	int				tmp;
	Karacter		*_hoops_RPPA, *_hoops_GSPPR;

	if ((tmp = left) == 0) 
		return;
	else if (_hoops_IAPGGR != null) {
		if (tmp > 0) {
			_hoops_RPPA = _hoops_IAPGGR;
			_hoops_GSPPR = karacters;
			do *_hoops_RPPA++ = *_hoops_GSPPR++;					/* _hoops_HSCI _hoops_CHSAH */
			_hoops_RGGA (--tmp == 0);
			tmp = count - left;
			_hoops_RPPA = karacters;
			_hoops_RGGA (--tmp < 0) *_hoops_RPPA++ = *_hoops_GSPPR++;	/* _hoops_IPS _hoops_CHSAH _hoops_IAPR */
			tmp = left;
			_hoops_RGGA (--tmp < 0) *_hoops_RPPA++ = (Karacter)' ';/* _hoops_RPGR _hoops_GGSR _hoops_CHSAH */
		}
		else {
			int				right = -left;

			tmp = right;
			_hoops_RPPA = _hoops_IAPGGR + tmp;
			_hoops_GSPPR = karacters + tmp;
			do *--_hoops_RPPA = *--_hoops_GSPPR;					/* _hoops_HSCI _hoops_CHSAH */
			_hoops_RGGA (--tmp == 0);
			tmp = count - right;
			_hoops_RPPA = karacters + count;
			_hoops_RGGA (--tmp < 0) *--_hoops_RPPA = *--_hoops_GSPPR;	/* _hoops_IPS _hoops_CHSAH _hoops_IAPR */
			tmp = right;
			_hoops_RGGA (--tmp < 0) *--_hoops_RPPA = (Karacter)' ';/* _hoops_RPGR _hoops_GGSR _hoops_CHSAH */
		}
	}
	else {
		if (tmp > 0) {
			tmp = count - left;
			_hoops_RPPA = karacters;
			_hoops_GSPPR = karacters + left;
			_hoops_RGGA (--tmp < 0) *_hoops_RPPA++ = *_hoops_GSPPR++;	/* _hoops_IPS _hoops_CHSAH _hoops_IAPR */
			tmp = left;
			_hoops_RGGA (--tmp < 0) *_hoops_RPPA++ = (Karacter)' ';/* _hoops_RPGR _hoops_GGSR _hoops_CHSAH */
		}
		else {
			int				right = -left;

			tmp = count - right;
			_hoops_RPPA = karacters + count;
			_hoops_GSPPR = _hoops_RPPA - right;
			_hoops_RGGA (--tmp < 0) *--_hoops_RPPA = *--_hoops_GSPPR;	/* _hoops_IPS _hoops_CHSAH _hoops_IAPR */
			tmp = right;
			_hoops_RGGA (--tmp < 0) *--_hoops_RPPA = (Karacter)' ';/* _hoops_RPGR _hoops_GGSR _hoops_CHSAH */
		}
	}
}


HC_INTERFACE void HC_CDECL HC_Scroll_Text (
	Key				key,
	int				left,
	int				up) 
{
	_hoops_PAPPR context("Scroll_Text");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Scroll_Text (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d);\n", left, up));
	);

	_hoops_CSPPR();

	_hoops_HACC *	text = (_hoops_HACC *)_hoops_RCSSR (context, key);

	if (text == null || text->type != _hoops_AGCP ||
		BIT (text->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TEXT, HES_INVALID_KEY,"Key does not refer to a valid Text item");
	}
	else if (left == 0 && up == 0) { 
		/* _hoops_RPAPR */
	}
	else {

		int	_hoops_CAPGGR = Abs(left);
		int	_hoops_SAPGGR = Abs(up);

		if (_hoops_SAPGGR > 1) {
			HE_ERROR (HEC_TEXT, HES_CANNOT_SCROLL,
					Sprintf_D (null,"Can't scroll up '%d' rows - plain Text only has one",up));
		}
		else if (_hoops_CAPGGR > text->count) {
			HE_ERROR (HEC_TEXT, HES_CANNOT_SCROLL,
					Sprintf_DD (null,"Can't scroll left '%d' - Text only has %d karacters",left, text->count));
		}
		else {

			/* _hoops_HCR _hoops_GPRS */

			if (up != 0 || _hoops_CAPGGR == text->count) {
				_hoops_SAPGGR = up = 0;
				_hoops_CAPGGR = left = text->count;
			}

			_hoops_RPPPR();
#ifndef DISABLE_PARTIAL_ERASE
			if (text->count > 0) {		/* _hoops_PSP _hoops_AIIAP _hoops_RPP _hoops_RHPA */
				_hoops_CRCP		*_hoops_SRCP = text->owner;
				Geometry		*_hoops_HCIS;
				/* _hoops_GRHP _hoops_IRS _hoops_RSPH _hoops_IPS _hoops_AARI _hoops_IH _hoops_IASI-_hoops_AHPIP _hoops_IS _hoops_SGH */
				_hoops_HCIS = HI_Copy_Geometry (context, (Geometry *)text);
				_hoops_HCIS->_hoops_RRHH = _hoops_HGAGR;

				if ((_hoops_HCIS->next = _hoops_SRCP->_hoops_SCGPR()) != null)
					_hoops_HCIS->next->backlink = &_hoops_HCIS->next;
				_hoops_SRCP->_hoops_RSGPR (_hoops_HCIS);
			}
#endif

			_hoops_HAPGGR (left, text->karacters, text->count, null);

			text->_hoops_CPGPR |= _hoops_HHSSR;

			_hoops_SASIR (context, text->owner, _hoops_HRCCA|_hoops_GGARA|_hoops_RPSIR);
			_hoops_IRRPR(); // _hoops_PHCHH
		}
	}
	_hoops_IRRPR();
}




local _hoops_SHCAP const * _hoops_GPPGGR (
	Attribute const *		_hoops_ASGPR) {
	_hoops_SHCAP const *	_hoops_ARRIP = null;

	do {
		if (_hoops_ASGPR->type > _hoops_IAAA (HK_STYLE, HK_TEXT_ALIGNMENT))
			break;
#ifndef DISABLE_STYLE_SEGMENT
		else if (_hoops_ASGPR->type == HK_STYLE) {
			Style const *				style = (Style const *)_hoops_ASGPR;

			if (style->_hoops_IGRPR && style->_hoops_IGRPR->_hoops_IPPGR != null) {
				_hoops_SHCAP const *	_hoops_RPPGGR;

				if ((_hoops_RPPGGR = _hoops_GPPGGR (style->_hoops_IGRPR->_hoops_IPPGR)) != null)
					_hoops_ARRIP = _hoops_RPPGGR;
			}
		}
#endif
		else if (_hoops_ASGPR->type == HK_TEXT_ALIGNMENT) {
			return (_hoops_SHCAP const *)_hoops_ASGPR;
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	return _hoops_ARRIP;
}


local bool _hoops_APPGGR (
	_hoops_CRCP const *				_hoops_SRCP) {

	while (_hoops_SRCP != null) {
		_hoops_SHCAP const *	_hoops_ARRIP;

		if (_hoops_SRCP->_hoops_SGRPR() != null) {
			Xref			*_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR();

			do if (!BIT (_hoops_AHICA->_hoops_RRHH, _hoops_HGAGR)) {
				if (_hoops_AHICA->type == _hoops_AGRPR && !_hoops_APPGGR (_hoops_AHICA->owner))
					return false;
			} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);
		}

		if (_hoops_SRCP->_hoops_IPPGR != null) {
			if ((_hoops_ARRIP = _hoops_GPPGGR (_hoops_SRCP->_hoops_IPPGR)) != null)
				return (_hoops_ARRIP->value == TA_LOWERLEFT ||
						_hoops_ARRIP->value == TA_CENTERLEFT ||
						_hoops_ARRIP->value == TA_UPPERLEFT) &&
					   _hoops_ARRIP->_hoops_HHCAP == TJUST_LEFT;
		}
		_hoops_SRCP = _hoops_SRCP->owner;

		if (_hoops_SRCP->type != _hoops_IRCP)
			break;
	}

	return false;
}


HC_INTERFACE void HC_CDECL HC_Edit_Text (
	Key				key,
	int				row,
	int				column,
	int				erase,
	int				ndelete,
	char const *	new_text) 
{
	_hoops_PAPPR context("Edit_Text");

#ifdef DISABLE_GEOMETRY_EDIT
	_hoops_IRPPR ("Geometry Edit");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Text (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, ", row, column));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, ", erase, ndelete));
		HI_Dump_Code (Sprintf_S (null, "%S);\n", new_text));
	);

	_hoops_RPPPR();

	_hoops_HACC *	text = (_hoops_HACC *)_hoops_RCSSR (context, key);

	if (text == null || text->type != _hoops_AGCP ||
		BIT (text->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TEXT, HES_INVALID_KEY, "Provided key does not refer to a valid Text item");
	}
	else {

		KName	_hoops_SIHSA;
		_hoops_IHAGI(_hoops_SIHSA);
		if (new_text != null)
			HI_Convert_Char_To_KName (new_text, &_hoops_SIHSA, text->encoding);

		HI_Edit_Text (context, text, row, column, erase, ndelete, _hoops_SIHSA.length, _hoops_SIHSA._hoops_IPPPP);

		_hoops_PRPIR (_hoops_SIHSA);
	}

	_hoops_IRRPR();
#endif
}


GLOBAL_FUNCTION void HI_Edit_Text (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HACC *					text,
	int						row,
	int						column,
	int						erase,
	int						ndelete,
	int						insert,
	Karacter *				_hoops_GHCIH) 
{
	Karacter *				_hoops_PPPGGR, *_hoops_CCPHC;
	int						_hoops_IPHAP;
	bool					_hoops_HPPGGR = false;
	Karacter *				_hoops_IPPGGR;
	int						_hoops_RGCCA;
	Karacter *				_hoops_CPPGGR = _hoops_GHCIH;

	if (row < 0) {
		HE_ERROR (HEC_TEXT, HES_INVALID_ROW,Sprintf_D (null,"Row #%d not valid - must not be negative", row));
		return;
	}

	if (column < 0) {
		HE_ERROR (HEC_TEXT, HES_INVALID_COLUMN,Sprintf_D (null,"Column #%d not valid - must not be negative", column));
		return;
	}

	if (ndelete < 0 && ndelete != -1) {
		HE_ERROR (HEC_TEXT, HES_INVALID_DELETE_COUNT,Sprintf_D (null,"Delete of %d not valid - must be nonnegative (or -1)", ndelete));
		return;
	}

	if (erase < 0) {
		HE_ERROR (HEC_TEXT, HES_INVALID_ERASE_COUNT, Sprintf_D (null,"Erase of %d not valid - must be nonnegative", erase));
		return;
	}

	if (ndelete == -1) 
		ndelete = insert;

	if (column > text->count) {
		HE_ERROR (HEC_TEXT, HES_INVALID_COLUMN,Sprintf_DD (null,"Can't start at column (character) %d - only have %d",column, text->count));
		return;
	}

	if (row > 0) {
		if (row >= text->_hoops_PICHR) {
			HE_ERROR (HEC_TEXT, HES_INVALID_ROW,Sprintf_DD (null,"Can't start at row %d - only have %d", row, text->_hoops_PICHR));
			return;
		}

		column += text->_hoops_RIHIR[row] - text->karacters;
	}

	if (ndelete > text->count - column) {
		_hoops_PHPGR (HEC_TEXT, HES_INVALID_DELETE_COUNT,
				Sprintf_DD (null,"Can't delete as many as %d characters starting at %d -",ndelete, column),
				"Will do the best we can");

		ndelete = text->count - column;
	}

	if (erase > text->count - column - ndelete) {
		_hoops_PHPGR (HEC_TEXT, HES_INVALID_ERASE_COUNT,
				Sprintf_DD (null,"Can't erase as many as %d characters starting at %d",erase, column),
				"Will do the best we can");

		erase = text->count - column - ndelete;
	}

	if (insert == 0 && erase == 0 && ndelete == 0) 
		return; /* _hoops_RPAPR */

	/* _hoops_CCPP _hoops_IRS _hoops_CCAH _hoops_GSGR */

	if ((_hoops_IPHAP = _hoops_RGCCA = text->count - ndelete + insert) == 0) {
		/* _hoops_PSP _hoops_CCAH _hoops_PPGS */

		/* _hoops_CIH _hoops_RHGS _hoops_PPGS */
		if ((_hoops_IPHAP = text->count) != 0) {
			_hoops_PPPGGR = text->karacters;
			do {
				if (*_hoops_PPPGGR++ != (Karacter)' ') {
					_hoops_HPPGGR = true;
					break;
				}
			} _hoops_RGGA (--_hoops_IPHAP == 0);

			FREE_ARRAY (text->karacters, text->count+1, Karacter);
		}

		text->count = 0;
		text->karacters = null;
	}
	else {
		/* _hoops_HGCR _hoops_CCAH _hoops_PPGS */

		ALLOC_ARRAY (_hoops_IPPGGR, _hoops_IPHAP+1, Karacter);

		/* _hoops_RIIPS _hoops_GH _hoops_IS _hoops_RH _hoops_SCGR _hoops_PIHP */
		_hoops_PPPGGR = text->karacters;
		_hoops_CCPHC = _hoops_IPPGGR;
		if ((_hoops_IPHAP = column) > 0) {
			do *_hoops_CCPHC++ = *_hoops_PPPGGR++;
			_hoops_RGGA (--_hoops_IPHAP == 0);
		}

		/* _hoops_AHPIP _hoops_CHSAH */
		if ((_hoops_IPHAP = erase) > 0) {
			do {
				if (*_hoops_PPPGGR++ != (Karacter)' ') _hoops_HPPGGR = true;
				*_hoops_CCPHC++ = (Karacter)' ';
			}
			_hoops_RGGA (--_hoops_IPHAP == 0);
		}

		/* _hoops_HSCI _hoops_CHSAH */

		if ((_hoops_IPHAP = ndelete) > 0) {
			do if (*_hoops_PPPGGR++ != (Karacter)' ') _hoops_HPPGGR = true;
			_hoops_RGGA (--_hoops_IPHAP == 0);
		}

		/* _hoops_GSRGR _hoops_CHSAH */
		if ((_hoops_IPHAP = insert) > 0) {
			do *_hoops_CCPHC++ = *_hoops_CPPGGR++;
			_hoops_RGGA (--_hoops_IPHAP == 0);

			_hoops_CPPGGR -= insert;
		}

		/* _hoops_IPS _hoops_HHRPA _hoops_CHSAH */
		if ((_hoops_IPHAP = text->count - ndelete - erase - column) > 0) {
			if (_hoops_RGCCA == text->count) {
				/* (_hoops_HAR _hoops_HGIPR _hoops_PA _hoops_GPP _hoops_RH _hoops_SHPR) */
				do *_hoops_CCPHC++ = *_hoops_PPPGGR++;
				_hoops_RGGA (--_hoops_IPHAP == 0);
			}
			else {
				do {
					if (*_hoops_PPPGGR != (Karacter)' ') _hoops_HPPGGR = true;
					*_hoops_CCPHC++ = *_hoops_PPPGGR++;
				}
				_hoops_RGGA (--_hoops_IPHAP == 0);
			}
		}

		*_hoops_CCPHC = '\0';

		/* _hoops_CIH _hoops_RHGS _hoops_PPGS */
		if ((_hoops_IPHAP = text->count) != 0)
			FREE_ARRAY (text->karacters, _hoops_IPHAP+1, Karacter);

		/* _hoops_SGH _hoops_CCAH _hoops_PPGS */
		text->karacters = _hoops_IPPGGR;
		text->count = _hoops_RGCCA;
	}

	if (text->count == 0) {
		if (text->_hoops_PICHR > 0) {
			if (text->_hoops_ICI != null)
				FREE_ARRAY (text->_hoops_ICI, text->_hoops_PICHR, int);
			if (text->_hoops_RIHIR != null)
				FREE_ARRAY (text->_hoops_RIHIR, text->_hoops_PICHR, Karacter *);
		}

		text->_hoops_PICHR = 0;
		text->_hoops_ICI = null;
		text->_hoops_RIHIR = null;
	}
	else {
		int						i;
		Karacter *				_hoops_RSSIH;
		int						_hoops_HRPGGR;
		int						_hoops_PICHR;

		_hoops_PICHR = 1;
		for (i = 0; i < text->count; ++i)
			if (text->karacters[i] == (Karacter)'\n')
				++_hoops_PICHR;

		if (text->_hoops_PICHR > 0) {
			if (text->_hoops_ICI != null)
				FREE_ARRAY (text->_hoops_ICI, text->_hoops_PICHR, int);
			if (text->_hoops_RIHIR != null)
				FREE_ARRAY (text->_hoops_RIHIR, text->_hoops_PICHR, Karacter *);
		}

		text->_hoops_PICHR = _hoops_PICHR;

		ALLOC_ARRAY (text->_hoops_ICI, text->_hoops_PICHR, int);
		ALLOC_ARRAY (text->_hoops_RIHIR, text->_hoops_PICHR, Karacter *);

		_hoops_HRPGGR = 0;
		/* _hoops_SPS _hoops_SPAHS _hoops_RH _hoops_PISC _hoops_AGIR _hoops_IIGR _hoops_IRS _hoops_HACH \_hoops_ACHP */
		text->_hoops_RIHIR[text->_hoops_PICHR-1] = &text->karacters[text->count];

		text->_hoops_RIHIR[0] = _hoops_RSSIH = text->karacters;
		for (i = 0; i < text->count; ++i) {
			if (text->karacters[i] == (Karacter)'\n') {
				if (_hoops_RSSIH != null)
					text->_hoops_ICI[_hoops_HRPGGR++] = &text->karacters[i] - _hoops_RSSIH;
				else {
					/* _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_GGR _hoops_IRS _hoops_GAGHR */
					text->_hoops_RIHIR[_hoops_HRPGGR] = &text->karacters[i];
					text->_hoops_ICI[_hoops_HRPGGR++] = 0;
				}
				_hoops_RSSIH = null;
			}
			else if (_hoops_RSSIH == null)
				text->_hoops_RIHIR[_hoops_HRPGGR] = _hoops_RSSIH = &text->karacters[i];
		}
		if (_hoops_RSSIH != null)
			text->_hoops_ICI[_hoops_HRPGGR] = &text->karacters[i] - _hoops_RSSIH;
		else
			text->_hoops_ICI[_hoops_HRPGGR] = 0;
	}

	if (text->_hoops_AAPGR != null) {
		_hoops_PIGPR		*sc = text->_hoops_AAPGR;

		do if (!BIT(sc->_hoops_RRHH, _hoops_HGAGR) &&
			   sc->column > text->count) {
			PUSHNAME(_hoops_RIGC);
			HC_Move_String_Cursor (_hoops_AIRIR (sc), 0, text->count);
			POPNAME(_hoops_RIGC);
		}
		_hoops_RGGA ((sc = (_hoops_PIGPR *)sc->next) == null);
	}

	if (text->owner)
		HI_Antiquate_Bounding (text->owner, true);

	text->_hoops_CPGPR |= _hoops_HHSSR;

	/* _hoops_HPGGR _hoops_IH _hoops_AIIAP */
	if (!_hoops_HPPGGR && _hoops_APPGGR (text->owner))
		_hoops_SASIR (_hoops_RIGC, text, _hoops_GGARA|_hoops_RPSIR|_hoops_RSCCA);
	else
		_hoops_SASIR (_hoops_RIGC, text, _hoops_RAGGA|_hoops_RPSIR|_hoops_RSCCA);
}

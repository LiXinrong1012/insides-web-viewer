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
 * $Id: obf_tmp.txt 1.65 2010-06-04 21:37:19 jason Exp $
 */

#include "windows_wrapper.h"	// _hoops_CGRI <_hoops_SPHGR._hoops_GGHR>, _hoops_PIHA _hoops_RCPS _hoops_SRS :(


#include "hoops.h"
#include "driver.h"
#include "hi_proto.h"

#if defined(WIN32_SYSTEM) && !defined(_WIN32_WCE) && !defined(NUTCRACKER)

#include "msw.h"
#include "hd_proto.h"

#include <stdio.h>


GLOBAL_FUNCTION _hoops_RAARP * HI_W32_make_font_stencil (
	Font_Instance const		*instance,
	unsigned short			_hoops_IPCSR,
	int						_hoops_RHSIH,
	int						bolding_level,
	float					xrslant,
	float					xrrotation,
	float					xrwidth,
	bool					antialias) {
	HDC _hoops_HIISI;
	HFONT _hoops_HCCRGR;
	_hoops_RAARP * stencil;
	unsigned char *_hoops_AGCCI;
	int _hoops_ICCRGR;
	int _hoops_GPGSI=0, _hoops_AGCPC, _hoops_HRSAS, _hoops_CCCRGR, _hoops_CRASS ,_hoops_IAPHA;
	int _hoops_SCAIP;
	int i,j;
	int tmp;
	int _hoops_SCCRGR=0;
	int _hoops_RPGSI = 0;
	ABC _hoops_HPCSA;
	_hoops_GCGCI *_hoops_RHCSR = (_hoops_GCGCI *) instance->_hoops_GAASR;
	int	bitmap_height = _hoops_RHSIH;
	int _hoops_GSCRGR;
	int _hoops_RSCRGR;
	int _hoops_ASCRGR;

	UNREFERENCED (bolding_level);
	UNREFERENCED (antialias);

	if (!_hoops_RHCSR->_hoops_HCGCI) 
		return 0;

	_hoops_HIISI = CreateCompatibleDC (NULL);

	if (!_hoops_HIISI) 
		return 0;
	
	if (xrrotation == 0.0f && xrwidth == 1.0f && 
		xrslant == 0.0f && bitmap_height == _hoops_RHCSR->_hoops_RCGCI) {

		_hoops_HCCRGR = (HFONT)SelectObject (_hoops_HIISI, _hoops_RHCSR->_hoops_HCGCI);

		_hoops_GSCRGR = _hoops_RHCSR->_hoops_RCGCI;
		_hoops_RSCRGR = _hoops_RHCSR->descent;
		_hoops_ASCRGR = _hoops_RHCSR->_hoops_ACGCI;
	}
	else {
		if (xrrotation != _hoops_RHCSR->_hoops_GSGCI ||
			xrwidth != _hoops_RHCSR->_hoops_RSGCI ||
			xrslant != _hoops_RHCSR->_hoops_ASGCI ||
			bitmap_height != _hoops_RHCSR->_hoops_SCGCI) {
			TEXTMETRIC tm;
			
			if (_hoops_RHCSR->_hoops_HSGCI)
				DeleteObject(_hoops_RHCSR->_hoops_HSGCI);

			_hoops_RHCSR->_hoops_PSGCI.lfOrientation = 
				_hoops_RHCSR->_hoops_PSGCI.lfEscapement = (long)(xrrotation * 10.0f);
			
			_hoops_RHCSR->_hoops_SCGCI = bitmap_height;
			_hoops_RHCSR->_hoops_PSGCI.lfHeight = -_hoops_RHCSR->_hoops_SCGCI * instance->_hoops_GRGGH;
			

			if (xrwidth != 1.0f)
				_hoops_RHCSR->_hoops_PSGCI.lfWidth = 
					(long)((_hoops_RHCSR->_hoops_PSGCI.lfHeight * xrwidth * _hoops_RHCSR->_hoops_PRPHA)+0.5f);
			else
				_hoops_RHCSR->_hoops_PSGCI.lfWidth = 0;
				
			if (xrslant != 0.0f || _hoops_PSGGI("-ITALIC", instance->family->name.text))
				_hoops_RHCSR->_hoops_PSGCI.lfItalic = TRUE;
			else
				_hoops_RHCSR->_hoops_PSGCI.lfItalic = FALSE;

			if(xrrotation)
				_hoops_RHCSR->_hoops_PSGCI.lfOutPrecision = OUT_TT_ONLY_PRECIS;

			_hoops_RHCSR->_hoops_HSGCI = CreateFontIndirect (&_hoops_RHCSR->_hoops_PSGCI);

			_hoops_RHCSR->_hoops_ASGCI = xrslant; 
			_hoops_RHCSR->_hoops_GSGCI = xrrotation;
			_hoops_RHCSR->_hoops_RSGCI = xrwidth;

			_hoops_HCCRGR = (HFONT)SelectObject (_hoops_HIISI, _hoops_RHCSR->_hoops_HSGCI);

			if (GetTextMetrics (_hoops_HIISI, &tm)) {
				_hoops_RHCSR->_hoops_ISGCI = tm.tmDescent;
				_hoops_RHCSR->_hoops_CSGCI = tm.tmMaxCharWidth;
			}
			else {
				/* _hoops_CGH _hoops_IIP _hoops_IHPS */
				_hoops_RHCSR->_hoops_ISGCI = _hoops_RHCSR->descent;
				_hoops_RHCSR->_hoops_CSGCI = _hoops_RHCSR->_hoops_ACGCI;
			}
		}
		else {
			_hoops_HCCRGR = (HFONT)SelectObject (_hoops_HIISI, _hoops_RHCSR->_hoops_HSGCI);
		}

		_hoops_GSCRGR = _hoops_RHCSR->_hoops_SCGCI;
		_hoops_RSCRGR = _hoops_RHCSR->_hoops_ISGCI;
		_hoops_ASCRGR = _hoops_RHCSR->_hoops_CSGCI;
	}

	if ((_hoops_RPGSI = GetCharABCWidthsW (_hoops_HIISI, _hoops_IPCSR, _hoops_IPCSR, &_hoops_HPCSA)) == 0 &&
		!GetCharWidth32W (_hoops_HIISI, _hoops_IPCSR, _hoops_IPCSR, &_hoops_GPGSI)) {

		if ((_hoops_RPGSI = GetCharABCWidths (_hoops_HIISI, _hoops_IPCSR, _hoops_IPCSR, &_hoops_HPCSA)) == 0 &&
			!GetCharWidth (_hoops_HIISI, _hoops_IPCSR, _hoops_IPCSR, &_hoops_GPGSI)) {
			/* _hoops_SGPR _hoops_RH _hoops_HPGSI _hoops_GAR _hoops_IRS _hoops_IIPGA _hoops_AHC. */
			_hoops_GPGSI = _hoops_ASCRGR;
		}
	}

	if (_hoops_RPGSI) {
		GCP_RESULTSW _hoops_IPGSI;
		DWORD _hoops_PSRGA = 0;
		DWORD result;
		unsigned short glyph;
		_hoops_IPGSI.lStructSize=sizeof(GCP_RESULTSW);
		_hoops_IPGSI.lpOutString = 0;
		_hoops_IPGSI.lpOrder = 0;
		_hoops_IPGSI.lpDx = 0;
		_hoops_IPGSI.lpCaretPos = 0;
		_hoops_IPGSI.lpClass = 0;
		_hoops_IPGSI.lpGlyphs = (LPWSTR)&glyph;
		_hoops_IPGSI.nGlyphs = 1;
		_hoops_IPGSI.nMaxFit = 0;

		if ((result = GetCharacterPlacementW(_hoops_HIISI, (LPCWSTR)&_hoops_IPCSR, 1, 0, &_hoops_IPGSI, _hoops_PSRGA)) != 0) {
			if (glyph == 0x0000) {
				SelectObject (_hoops_HIISI, _hoops_HCCRGR);
				DeleteDC (_hoops_HIISI);
				return 0;
			}
		}

		_hoops_SCAIP = _hoops_HPCSA.abcA + _hoops_HPCSA.abcB + _hoops_HPCSA.abcC;

		if (_hoops_HPCSA.abcA<0) _hoops_HPCSA.abcA = 0;
		if (_hoops_HPCSA.abcC<0) _hoops_HPCSA.abcC = 0;
		_hoops_GPGSI = _hoops_HPCSA.abcA + _hoops_HPCSA.abcB + _hoops_HPCSA.abcC;

		_hoops_SCCRGR = 0;
	}
	else {
		_hoops_SCAIP = _hoops_GPGSI;
	}

	if (_hoops_GPGSI == 0) {
		SelectObject (_hoops_HIISI, _hoops_HCCRGR);
		DeleteDC (_hoops_HIISI);
		return 0;
	}

	_hoops_AGCPC = _hoops_GSCRGR;

	_hoops_CRASS = _hoops_GPGSI;

	if (xrrotation != 0.0f) {
		_hoops_AGCPC = _hoops_GPGSI = ((int)(_hoops_SGIHR((float)(
			(_hoops_RHCSR->_hoops_PSGCI.lfHeight*_hoops_RHCSR->_hoops_PSGCI.lfHeight)+
				_hoops_GPGSI*_hoops_GPGSI)) + 0.5f) + _hoops_RSCRGR); 
	}
	else {
		_hoops_RHCSR->_hoops_CCGCI = (int)((float)_hoops_AGCPC * 0.125f) + 16; //_hoops_RPCRC: _hoops_GAGIP _hoops_RRI _hoops_CCPCR, _hoops_HII 4 _hoops_IS 16
		_hoops_AGCPC += _hoops_RHCSR->_hoops_CCGCI + _hoops_RSCRGR;
		_hoops_GPGSI += (int)((float)_hoops_GPGSI * 0.25f) + 6;
	}

	_hoops_HRSAS = ((_hoops_GPGSI+_hoops_SCCRGR + 31) / 32) * 32;
	_hoops_CCCRGR = _hoops_AGCPC;

	stencil = HI_Clone_Stencil(0);

	if (!stencil)
		goto _hoops_RCCSR;

	stencil->width = _hoops_GPGSI+_hoops_SCCRGR;
	stencil->height = _hoops_AGCPC;
	stencil->id = _hoops_IPCSR;
	stencil->rotation = xrrotation;
	stencil->width_scale = xrwidth;

	if (xrrotation == 0.0f) {
		stencil->_hoops_HAARP = _hoops_SCAIP+_hoops_SCCRGR;
		stencil->_hoops_IAARP = 0;
		stencil->_hoops_CAARP = (int)((float)_hoops_CRASS * 0.125f) + 3;
		stencil->_hoops_SAARP = _hoops_RSCRGR;
	}
	else {
		float _hoops_GGHCR, _hoops_AGHCR;

		_hoops_RICH (xrrotation, _hoops_GGHCR, _hoops_AGHCR);

		stencil->_hoops_HAARP = (int)((_hoops_SCAIP+_hoops_SCCRGR) * _hoops_AGHCR); 
		stencil->_hoops_IAARP = (int)((_hoops_SCAIP+_hoops_SCCRGR) * _hoops_GGHCR);

		if (_hoops_RHCSR->_hoops_PSGCI.lfHeight < 0) 
			_hoops_IAPHA = -_hoops_RHCSR->_hoops_PSGCI.lfHeight;
		else
			_hoops_IAPHA = _hoops_RHCSR->_hoops_PSGCI.lfHeight;
			
		if (_hoops_GGHCR > 0.0f) {
			if (_hoops_AGHCR > 0.0f) {
				stencil->_hoops_CAARP = (int)(_hoops_IAPHA * _hoops_GGHCR);
				stencil->_hoops_SAARP = 0;
				stencil->_hoops_CPARP = (int)(_hoops_IAPHA * _hoops_GGHCR) - (int)(_hoops_GGHCR * _hoops_RSCRGR);
			}
			else {
				stencil->_hoops_CAARP = (int)(_hoops_IAPHA * _hoops_GGHCR + _hoops_CRASS * -_hoops_AGHCR);
				stencil->_hoops_SAARP = (int)(_hoops_IAPHA * -_hoops_AGHCR);
				stencil->_hoops_CPARP = (int)(_hoops_IAPHA * _hoops_GGHCR + _hoops_CRASS * -_hoops_AGHCR) - (int)(_hoops_GGHCR * _hoops_RSCRGR);
			}
		}
		else {
			if (_hoops_AGHCR<0.0f) {
				stencil->_hoops_CAARP = (int)(_hoops_CRASS * -_hoops_AGHCR);
				stencil->_hoops_SAARP = (int)(_hoops_IAPHA * -_hoops_AGHCR + _hoops_CRASS * -_hoops_GGHCR);
				stencil->_hoops_CPARP = (int)(_hoops_CRASS * -_hoops_AGHCR) - (int)(_hoops_GGHCR * _hoops_RSCRGR); 
			}
			else {
				stencil->_hoops_CAARP = 0;
				stencil->_hoops_SAARP = (int)(_hoops_CRASS * -_hoops_GGHCR);
			}
		}

		stencil->_hoops_SAARP += (int)(_hoops_AGHCR * _hoops_RSCRGR);
		stencil->_hoops_CAARP -= (int)(_hoops_GGHCR * _hoops_RSCRGR);
	}

	{
		BOOL test;
		if (SystemParametersInfo (SPI_GETFONTSMOOTHING, 0, &test, 0)) 
			if (!test)
				antialias = false;
	}

	{
		HBITMAP			hBitmap, tBitmap;
		BITMAPINFO		*_hoops_RIPSI;
		void			*_hoops_RCHA;
		int				_hoops_CHPSI;
		int				_hoops_PPICI;
		unsigned char	*_hoops_PSCRGR;
		
		/*_hoops_HGCR _hoops_PPGS _hoops_IH _hoops_GAS _hoops_HSCRGR _hoops_RHSHP _hoops_RH _hoops_PIH */
		_hoops_CHPSI = (3 - ((3 + stencil->width) % 4)) + stencil->width;

		if (antialias)
			_hoops_PPICI = sizeof(BITMAPINFO);
		else
			_hoops_PPICI = sizeof(BITMAPINFO)+sizeof(RGBQUAD)*2;
		
		ZALLOC_ARRAY(_hoops_PSCRGR, _hoops_PPICI, unsigned char);
		_hoops_RIPSI = (BITMAPINFO*)_hoops_PSCRGR;

		/*_hoops_ISCRGR _hoops_GAS _hoops_ISSC _hoops_HII _hoops_ASPSI */
		_hoops_RIPSI->bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
		_hoops_RIPSI->bmiHeader.biWidth = _hoops_CHPSI;
		_hoops_RIPSI->bmiHeader.biHeight = stencil->height;
		_hoops_RIPSI->bmiHeader.biPlanes = 1;
		_hoops_RIPSI->bmiHeader.biCompression = BI_RGB;

		if (antialias) {
			_hoops_RIPSI->bmiHeader.biBitCount = 24;
		}
		else {
			RGBQUAD alter	*rgb;
			
			_hoops_RIPSI->bmiHeader.biBitCount = 8;
			_hoops_RIPSI->bmiHeader.biClrUsed = 2;
			_hoops_RIPSI->bmiHeader.biClrImportant = 2;
		
			rgb = (RGBQUAD alter *)_hoops_RIPSI->bmiColors;
			rgb->rgbBlue=255;
			rgb->rgbGreen=255;
			rgb->rgbRed=255;
			rgb->rgbReserved=0;
			rgb++;
			rgb->rgbBlue=0;
			rgb->rgbGreen=0;
			rgb->rgbRed=0;
			rgb->rgbReserved=0;
		}

		hBitmap = CreateDIBSection(_hoops_HIISI, _hoops_RIPSI, DIB_RGB_COLORS, &_hoops_RCHA, NULL, 0);

		FREE_ARRAY(_hoops_RIPSI, _hoops_PPICI, unsigned char);

		if (!hBitmap) {
			SelectObject (_hoops_HIISI, _hoops_HCCRGR);
			DeleteDC (_hoops_HIISI);
			return 0;
		}

		tBitmap = (HBITMAP)SelectObject (_hoops_HIISI, hBitmap);

		SelectObject (_hoops_HIISI, GetStockObject (WHITE_BRUSH));
		SelectObject (_hoops_HIISI, GetStockObject (WHITE_PEN));
		GDI_Rectangle (_hoops_HIISI, 0, 0, _hoops_CHPSI, stencil->height);

		SetTextAlign (_hoops_HIISI, TA_BASELINE | TA_LEFT);

		stencil->_hoops_IPARP = (int)(.10 * stencil->height);
		stencil->_hoops_CPARP /= 4;

		int bitmap_height = 0;
		float _hoops_RIRSS = 0.0;
		bitmap_height = HI_Get_Stencil_Cache_Height ((int)instance->_hoops_RACSR, false);
		_hoops_RIRSS = (instance->_hoops_RACSR / (float)bitmap_height) * instance->_hoops_GCHSA;

		/* _hoops_RH _hoops_CSCRGR _hoops_IIP _hoops_SHPH _hoops_ARR _hoops_SCH _hoops_IRIRA 254, _hoops_HIS _hoops_ARI _hoops_SR _hoops_SAHR _hoops_SGH _hoops_IRS _hoops_SRSR _hoops_SHI */
		if(bitmap_height < 254)
			stencil->_hoops_IPARP *= _hoops_RIRSS;
		else
			stencil->_hoops_IPARP = 20;

		if(stencil->height <= 8)
			stencil->_hoops_IPARP = 0;

		int _hoops_SSCRGR = 0.0;

		int _hoops_GGSRGR = _hoops_AGCPC-stencil->_hoops_SAARP- (1 + stencil->_hoops_IPARP);

		/*_hoops_RPP (_hoops_RGSRGR < _hoops_AGSRGR->_hoops_PGSRGR)
			_hoops_HGSRGR = _hoops_APSP->_hoops_IGSRGR;*/

		/* _hoops_SR _hoops_HHGC _hoops_HAGH _hoops_GRRII _hoops_RPP _hoops_SR _hoops_CHR _hoops_ARI _hoops_HII _hoops_IRS _hoops_HACPC _hoops_AASA _hoops_RIIA _hoops_IIGR _hoops_IRS _hoops_GGARP _hoops_HRCSR, _hoops_PAR _hoops_CPHP _hoops_SHS */
		if(instance->_hoops_ARGGH && stencil->height <= 12)
			_hoops_SSCRGR += stencil->_hoops_IPARP;


		tmp = TextOutW (_hoops_HIISI, stencil->_hoops_CAARP + stencil->_hoops_CPARP, _hoops_GGSRGR + _hoops_SSCRGR, (LPCWSTR)&_hoops_IPCSR, 1);

		if (antialias) {
			/*_hoops_HGCR _hoops_PPGS _hoops_IH _hoops_GAS, _hoops_CGSRGR _hoops_RHSHP _hoops_RH _hoops_PIH */
			_hoops_ICCRGR = _hoops_CHPSI * stencil->height;

			ALLOC_ARRAY(_hoops_AGCCI, _hoops_ICCRGR, unsigned char);

			if (!_hoops_AGCCI) {
				SelectObject (_hoops_HIISI, tBitmap);
				HI_Cleanup_Stencil(stencil, true); 
				stencil = 0;
				goto _hoops_RCCSR;
			}

			stencil->_hoops_APARP = _hoops_CHPSI;
			stencil->_hoops_PPARP = 8;
			stencil->bitmap = _hoops_AGCCI;

			for (i = 0; i < stencil->height; i++)
				for (j = 0; j < _hoops_CHPSI; j++)
					_hoops_AGCCI[i*_hoops_CHPSI+j] = 255-((unsigned char*)_hoops_RCHA)[((stencil->height-i-1)*_hoops_CHPSI*3)+j*3];
		}
		else {
			/*_hoops_HGCR _hoops_PPGS _hoops_IH _hoops_GAS, _hoops_CGSRGR _hoops_RHSHP _hoops_RH _hoops_PIH */
			_hoops_ICCRGR = stencil->_hoops_APARP =(_hoops_CHPSI + 7) / 8;
			_hoops_ICCRGR *= stencil->height;

			ZALLOC_ARRAY(_hoops_AGCCI, _hoops_ICCRGR, unsigned char);

			if (!_hoops_AGCCI) {
				SelectObject (_hoops_HIISI, tBitmap);
				HI_Cleanup_Stencil(stencil, true); 
				stencil = 0;
				goto _hoops_RCCSR;
			}

			stencil->_hoops_PPARP = 1;
			stencil->bitmap = _hoops_AGCCI;

			for (i = 0; i < stencil->height; i++) {
				unsigned char alter *row = stencil->bitmap + i * stencil->_hoops_APARP;
				for (j = 0; j < _hoops_CHPSI; j++)
					if ((((unsigned char*)_hoops_RCHA)[((stencil->height-i-1)*_hoops_CHPSI)+j]))
						row[j >> 3] |= (0x0080 >> (j & 0x0007));
			}

		}

		SelectObject (_hoops_HIISI, tBitmap);
		DeleteObject (hBitmap);
	}

_hoops_RCCSR:
	SelectObject (_hoops_HIISI, _hoops_HCCRGR);
	DeleteDC (_hoops_HIISI);

	return stencil;
}

GLOBAL_FUNCTION _hoops_SGRRR alter *HI_W32_find_font (
	_hoops_SGRRR  *list,
	const char * name) {

	while (list) {
		if (_hoops_IGGPA (list->name, name)) 
			return list;
		else if (list->specific)
				if (_hoops_IGGPA (list->specific, name)) 
					return list;

		list = list->next;
	}

	return 0;
}


local void HI_W32_save_font (
	_hoops_SGRRR alter **list,
	const LOGFONT *_hoops_PCGCI,
	char const *name,
	char const *specific,
	float _hoops_IARCI,
	float _hoops_IGGGH,
	float _hoops_PRPHA,
	Integer32 _hoops_CARCI,
	_hoops_IHGRP encoding) {
	_hoops_SGRRR alter *item;

	ALLOC (item, _hoops_SGRRR);

	memcpy(&item->_hoops_PCGCI, _hoops_PCGCI, sizeof (LOGFONT));

	ALLOC_ARRAY (item->name, _hoops_SSGR (name) + 1, char);
	strcpy(item->name, name);

	if (specific) {
		ALLOC_ARRAY (item->specific, _hoops_SSGR (specific) +1, char);
		strcpy(item->specific, specific);
	}
	else
		item->specific = 0;

	item->_hoops_IARCI = _hoops_IARCI;
	item->_hoops_IGGGH = _hoops_IGGGH;
	item->_hoops_PRPHA = _hoops_PRPHA;
	item->_hoops_CARCI = _hoops_CARCI;
	item->encoding = encoding;

	item->next = *list;
	*list = item;
}


GLOBAL_FUNCTION bool HI_W32_measure_char_stenciled(
	Net_Rendition const &	nr,
	Font_Instance const * instance,
	Karacter _hoops_IPCSR,
	float alter *_hoops_GGGS,
	bool alter *_hoops_CPCSR,
	void ** _hoops_HPSRH) {
	_hoops_RAARP	*stencil = 0;
	_hoops_RAARP	**_hoops_PPSIH = 0;
	int _hoops_HGCGGR, height, bitmap_height;
	float _hoops_RIRSS;

	UNREFERENCED(nr);

	_hoops_HGCGGR = height = (int)instance->_hoops_RACSR;

	bitmap_height = HI_Get_Stencil_Cache_Height (height, false);

	_hoops_RIRSS = (float)_hoops_HGCGGR / (float)bitmap_height;

	_hoops_PPSIH = HI_Get_Stencil_Cache(instance, bitmap_height, 0, 0, 0, 1.0f, false);

	stencil = HI_Lookup_Stencil(_hoops_PPSIH, _hoops_IPCSR);

	if (!stencil) {
		((Font_Instance*)instance)->_hoops_ARGGH = true;
		stencil = HI_W32_make_font_stencil(instance, _hoops_IPCSR, bitmap_height, 0, 0, 0, 1.0f, false);
		((Font_Instance*)instance)->_hoops_ARGGH = false;

		if (stencil)
			HI_Store_Stencil (_hoops_PPSIH, stencil); 
	}

	if (stencil) {
		*_hoops_GGGS = (float)stencil->_hoops_HAARP*_hoops_RIRSS;
		*_hoops_CPCSR = false;
		*_hoops_HPSRH=(void*)1;
	}
	else {
		*_hoops_GGGS = 0.0f;
		*_hoops_CPCSR = true;
		*_hoops_HPSRH=(void*)0;
	}

	return true;
}


GLOBAL_FUNCTION void HI_W32_unload_font_stenciled (
	Display_Context const * dc, 
	Font_Instance alter *instance) {
	_hoops_GCGCI alter *_hoops_RHCSR = (_hoops_GCGCI alter *) instance->_hoops_GAASR;

	UNREFERENCED(dc);

	if (_hoops_RHCSR != null) {
		HI_Clean_Stencil_Cache(instance);

		DeleteObject (_hoops_RHCSR->_hoops_HCGCI);
		if (_hoops_RHCSR->_hoops_HSGCI) 
			DeleteObject(_hoops_RHCSR->_hoops_HSGCI);

		FREE(_hoops_RHCSR, _hoops_GCGCI);
	}
}


GLOBAL_FUNCTION void * HI_W32_load_font_stenciled(
	Display_Context const		*dc,
	char const					*name,
	Font_Instance alter			*instance,
	void *						_hoops_SGSRGR,
	_hoops_SGRRR				**_hoops_GRRRR,
	_hoops_SGRRR				**_hoops_AHSIH) {

	_hoops_GCGCI alter *_hoops_RHCSR = 0;
	_hoops_SGRRR const *_hoops_HSSRH;
	/* _hoops_APPC _hoops_SCSH _hoops_GRSRGR = 0;*/
	bool _hoops_SAACP=true;
	HDC				hDC = (HDC)_hoops_SGSRGR;

	UNREFERENCED(dc);

	instance->_hoops_HRGGH = true;

	_hoops_HSSRH = HI_W32_find_font (*_hoops_AHSIH, name);

	if (!_hoops_HSSRH) 
		_hoops_HSSRH = HI_W32_find_font (*_hoops_GRRRR, name);

	if (!_hoops_HSSRH) {
		/* _hoops_AIRS - _hoops_HPPR _hoops_IHGSI */
		if (!_hoops_IGGPA ("Arial-GDI-VECTOR", name)) {

			_hoops_ARGIP (HEC_GL_DRIVER, HES_LOAD_FONT_FAILED,
					 "Unable to find font in internally recorded font list",
					 name, "Substituting Arial Font");

			_hoops_HSSRH = HI_W32_find_font (*_hoops_AHSIH, name);
		}

		if (!_hoops_HSSRH) {

			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, 
					"Arial Font could not be in internally recorded font list");

			return 0;
		}
	}

	ZALLOC(_hoops_RHCSR, _hoops_GCGCI);

	_hoops_RSAI(&_hoops_HSSRH->_hoops_PCGCI, LOGFONT, &_hoops_RHCSR->_hoops_PCGCI);
	_hoops_RSAI(&_hoops_HSSRH->_hoops_PCGCI, LOGFONT, &_hoops_RHCSR->_hoops_PSGCI);

	_hoops_RHCSR->_hoops_RCGCI = (int)instance->_hoops_RACSR;
	float _hoops_RRSRGR = (float)_hoops_RHCSR->_hoops_RCGCI / (float)((_hoops_RHCSR->_hoops_RCGCI > 512) ? 512 : _hoops_RHCSR->_hoops_RCGCI);
	_hoops_RHCSR->_hoops_RCGCI = (_hoops_RHCSR->_hoops_RCGCI > 512) ? 512 : _hoops_RHCSR->_hoops_RCGCI;

	_hoops_RHCSR->_hoops_PRPHA = _hoops_HSSRH->_hoops_PRPHA;
	
	_hoops_RHCSR->_hoops_ICGCI = _hoops_RHCSR->_hoops_PCGCI.lfWidth;
	_hoops_RHCSR->_hoops_PSGCI.lfWidth = _hoops_RHCSR->_hoops_PCGCI.lfWidth = 0;

	_hoops_RHCSR->_hoops_PCGCI.lfOrientation = _hoops_RHCSR->_hoops_PSGCI.lfEscapement = 0;
	_hoops_RHCSR->_hoops_PSGCI.lfOrientation = _hoops_RHCSR->_hoops_PCGCI.lfEscapement = 0;

	_hoops_RHCSR->_hoops_PSGCI.lfHeight = _hoops_RHCSR->_hoops_PCGCI.lfHeight = -_hoops_RHCSR->_hoops_RCGCI;

	_hoops_RHCSR->_hoops_HCGCI = CreateFontIndirect (&_hoops_RHCSR->_hoops_PCGCI);

	if (_hoops_RHCSR->_hoops_HCGCI) {
		HFONT _hoops_ARSRGR;
		TEXTMETRIC tm;

		_hoops_ARSRGR = (HFONT) SelectObject (hDC, _hoops_RHCSR->_hoops_HCGCI);

		if (GetTextMetrics (hDC, &tm)) {
			_hoops_RHCSR->descent = tm.tmDescent;
			_hoops_RHCSR->_hoops_ACGCI = tm.tmMaxCharWidth;
			
			if (_hoops_SAACP && _hoops_RHCSR->_hoops_RCGCI > 3) {
				_hoops_RAARP * stencil=0;
				Karacter _hoops_IPCSR;
				
				_hoops_SAACP=false;

				_hoops_IPCSR = (Karacter)'A';
				/* _hoops_AGCHS _hoops_RGR _hoops_GGR _hoops_RSIH _hoops_IH _hoops_PRSRGR */
				instance->_hoops_GAASR = (void*)_hoops_RHCSR;
				stencil = HI_W32_make_font_stencil(instance, _hoops_IPCSR, _hoops_RHCSR->_hoops_RCGCI, 0, 0, 0.0f, 1.0f, false);

				int bitmap_height = 0;
				float _hoops_RIRSS = 0.0;
				bitmap_height = HI_Get_Stencil_Cache_Height ((int)instance->_hoops_RACSR, false);
				_hoops_RIRSS = (instance->_hoops_RACSR / (float)bitmap_height) * instance->_hoops_GCHSA * _hoops_RRSRGR;

				if (stencil) {
					int x, y;
					int _hoops_HRSRGR = 0;
					if(bitmap_height < 254)
						_hoops_HRSRGR = (int)(.10 * stencil->height * _hoops_RIRSS  * _hoops_RRSRGR);
					else
						_hoops_HRSRGR = 20;


					for (y=0; y<stencil->height; y++) {
						unsigned char const *row;

						row = stencil->bitmap + y * stencil->_hoops_APARP;

						if (stencil->_hoops_PPARP == 1) {
							for (x=0; x<stencil->width; x++) {
								if ((row[x >> 3] & (0x0080 >> (x & 0x0007))))
									goto _hoops_PRSPR;
							}
						}
						else {
							for (x=0; x<stencil->width; x++) {
								if (row[x])
									goto _hoops_PRSPR;
							}
						}
					}
_hoops_PRSPR:
					HI_Cleanup_Stencil(stencil,true);

					if ((_hoops_RHCSR->_hoops_RCGCI+_hoops_RHCSR->_hoops_CCGCI-y)>0) {

						/* _hoops_RH (_hoops_SCSH)(.10 * _hoops_APSP->_hoops_APPS) _hoops_IGI _hoops_ARI _hoops_HCPRI _hoops_CCA _hoops_RH _hoops_APSP->_hoops_IGSRGR */
						instance->_hoops_GRGGH = (float)_hoops_RHCSR->_hoops_RCGCI/(float)(_hoops_RHCSR->_hoops_RCGCI+_hoops_RHCSR->_hoops_CCGCI-y -_hoops_HRSRGR); 

						_hoops_RHCSR->_hoops_PSGCI.lfHeight = _hoops_RHCSR->_hoops_PCGCI.lfHeight = -_hoops_RHCSR->_hoops_RCGCI * instance->_hoops_GRGGH;

						DeleteObject(_hoops_RHCSR->_hoops_HCGCI);
						_hoops_RHCSR->_hoops_HCGCI = CreateFontIndirect (&_hoops_RHCSR->_hoops_PCGCI);

					}
				}
			}
			SelectObject (hDC, _hoops_ARSRGR);

		}
		else {
			SelectObject (hDC, _hoops_ARSRGR);
			DeleteObject(_hoops_RHCSR->_hoops_HCGCI);
			_hoops_RHCSR->_hoops_HCGCI = 0;				
		}

		_hoops_RHCSR->_hoops_GSGCI = 0.0f;
		_hoops_RHCSR->_hoops_RSGCI = 1.0f;
		_hoops_RHCSR->_hoops_HSGCI = 0;
	}

	/*_hoops_ASAI _hoops_IRSRGR _hoops_CRSRGR _hoops_RGGCI*/
	
	if (!_hoops_RHCSR->_hoops_HCGCI) {
		/* _hoops_CHGSI _hoops_AHCI _hoops_ARPC - _hoops_SASRR _hoops_SRIGP */
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Font could not be loaded");
		FREE(_hoops_RHCSR, _hoops_GCGCI);
		_hoops_RHCSR = 0;
	}

	return _hoops_RHCSR;
}


/* _hoops_RIGR _hoops_IS _hoops_PICP _hoops_IIGR _hoops_AHCI _hoops_HRCSR _hoops_RRPIP _hoops_RAGA _hoops_ISSC _hoops_HPP _hoops_PSCSR */
#define _hoops_SRSRGR(_hoops_IGGGH, _hoops_ISISR)	\
	if (_hoops_IGGGH < _hoops_ISISR)				\
		_hoops_IGGGH = _hoops_ISISR;

typedef struct {
	HDC					_hoops_AGICI;
	bool			_hoops_RCCCI;
	_hoops_SGRRR	*list;
} W32_Font_Enum_Passthru;


local int APIENTRY HI_W32_font_callback_proc (
	const LOGFONT				*_hoops_GASRGR,
	const TEXTMETRIC			*tm,
	DWORD						_hoops_GSHIH,
	LPARAM						data) {
	LOGFONT						*_hoops_PCGCI = (LOGFONT alter *) _hoops_GASRGR;
	W32_Font_Enum_Passthru alter	*_hoops_RASRGR = (W32_Font_Enum_Passthru alter *)data;
	float						_hoops_ISISR;
	float						_hoops_IGGGH;
	char						specific[1024];
	char						_hoops_AASRGR[1024];
	char alter					*_hoops_ASAPR = specific;
	char alter					*_hoops_PSAPR = specific + _hoops_GGAPR (specific);
	int							tmp;

#ifdef _WIN32_WCE
	char lfFaceName[1024];
	_hoops_PASRGR(lfFaceName, _hoops_PCGCI->lfFaceName, 1024);
#endif

#ifndef _WIN32_WCE
	if (BIT (_hoops_GSHIH, DEVICE_FONTTYPE)) return true;
#endif

	if (BIT (_hoops_GSHIH, RASTER_FONTTYPE)) {
		/* _hoops_AHRH _hoops_HRCSR */

#ifdef MINITAB
		_hoops_ISISR = (float) (tm->tmAscent + tm->tmDescent) - tm->tmInternalLeading;
#else
		_hoops_ISISR = (float) tm->tmAscent - tm->tmInternalLeading;
#endif

		_hoops_IGGGH = (float) tm->tmHeight;
		_hoops_SRSRGR (_hoops_IGGGH, _hoops_ISISR);

#ifdef _WIN32_WCE
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", lfFaceName);
#else
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", _hoops_PCGCI->lfFaceName);
#endif
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%s", "GDI");
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%s", "RASTER");
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%d", (tmp = _hoops_PCGCI->lfHeight, &tmp));
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%d", (tmp = _hoops_PCGCI->lfWidth, &tmp));
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%d", (tmp = _hoops_PCGCI->lfWeight, &tmp));
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%d", (tmp = _hoops_PCGCI->lfCharSet, &tmp));

		if (_hoops_ASAPR == _hoops_PSAPR) {
			_hoops_ASAPR = NULL;
		}
		if (_hoops_ASAPR == NULL) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Font spec overflow");
			return true;
		}
		*_hoops_ASAPR = '\0';

		_hoops_ASAPR = _hoops_AASRGR;
		_hoops_PSAPR = _hoops_AASRGR + _hoops_GGAPR (_hoops_AASRGR);

#ifdef _WIN32_WCE
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", lfFaceName);
#else
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", _hoops_PCGCI->lfFaceName);
#endif
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%s", "GDI");
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%s", "RASTER");
		if (_hoops_PCGCI->lfItalic) _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%s", "ITALIC");
		if (_hoops_PCGCI->lfUnderline) _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%s", "UNDERLINE");
		if (_hoops_PCGCI->lfStrikeOut) _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%s", "STRIKEOUT");

		if (_hoops_ASAPR == _hoops_PSAPR) {
			_hoops_ASAPR = NULL;
		}
		if (_hoops_ASAPR == NULL) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Font spec overflow");
			return true;
		}
		*_hoops_ASAPR = '\0';

		if (HI_W32_find_font (_hoops_RASRGR->list, specific) == NULL) {
			int _hoops_CARCI;

			if (BIT (_hoops_GSHIH, TRUETYPE_FONTTYPE)) 
				/*_hoops_HASRGR = _hoops_IASRGR|_hoops_CASRGR|_hoops_SASRGR;*/
				_hoops_CARCI = _hoops_IAGGH;
			else
				_hoops_CARCI = _hoops_CRGGH;

			if (_hoops_ISISR != 0.0f)
				HI_W32_save_font (&_hoops_RASRGR->list, _hoops_PCGCI, _hoops_AASRGR, specific, _hoops_ISISR, _hoops_IGGGH, 1.0f, _hoops_CARCI, _hoops_SSAIP);

		}
	}
	else {
		/* _hoops_AAGA _hoops_HRCSR */

#ifdef MINITAB
		_hoops_ISISR = (float) (tm->tmAscent + tm->tmDescent) - tm->tmInternalLeading;
#else
		_hoops_ISISR = (float) tm->tmAscent - tm->tmInternalLeading;
#endif

		/* * _hoops_CAIP'_hoops_RA _hoops_GCIS _hoops_GPSRGR * _hoops_PS _hoops_RRP _hoops_IS _hoops_SHH _hoops_SHSS _hoops_IS _hoops_RPSRH _hoops_RH _hoops_APACA _hoops_APPS */
		_hoops_IGGGH = (float) tm->tmHeight;
		_hoops_SRSRGR (_hoops_IGGGH, _hoops_ISISR);

#ifdef _WIN32_WCE
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", lfFaceName);
#else
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", _hoops_PCGCI->lfFaceName);
#endif
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%s", "GDI");
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%s", "VECTOR");
		if (_hoops_PCGCI->lfItalic) _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%s", "ITALIC");
		if (_hoops_PCGCI->lfUnderline) _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%s", "UNDERLINE");
		if (_hoops_PCGCI->lfStrikeOut) _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%s", "STRIKEOUT");
		if (_hoops_PCGCI->lfWeight == 700) _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%s", "BOLD");

		*_hoops_ASAPR = '\0';

		_hoops_AAHR (specific, _hoops_AASRGR);
		if (_hoops_ASAPR == _hoops_PSAPR) {
			_hoops_ASAPR = NULL;
		}
		if (_hoops_ASAPR == NULL) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "Font spec overflow");
			return true;
		}
		*_hoops_ASAPR = '\0';

		if (!HI_W32_find_font (_hoops_RASRGR->list, specific)) {
			HI_W32_save_font (&_hoops_RASRGR->list, _hoops_PCGCI, _hoops_AASRGR, 0, 
				0.0f, _hoops_IGGGH/_hoops_ISISR, ((float)tm->tmAveCharWidth/(float)tm->tmAscent),
				_hoops_GPCSR|_hoops_PAGGH|_hoops_GAGGH, _hoops_SACSR);

			if (BIT (_hoops_GSHIH, TRUETYPE_FONTTYPE)) {
				if (!_hoops_RASRGR->_hoops_RCCCI) {
					_hoops_RASRGR->_hoops_RCCCI = true;

					/* _hoops_RPSRGR */
					_hoops_PCGCI->lfItalic = TRUE;
					_hoops_PCGCI->lfUnderline = FALSE;
					_hoops_PCGCI->lfStrikeOut = FALSE;
					_hoops_PCGCI->lfWeight = 0;
					HI_W32_font_callback_proc (_hoops_PCGCI, tm, _hoops_GSHIH, data);

					/* _hoops_APSRGR */
					_hoops_PCGCI->lfItalic = FALSE;
					_hoops_PCGCI->lfUnderline = TRUE;
					_hoops_PCGCI->lfStrikeOut = FALSE;
					_hoops_PCGCI->lfWeight = 0;
					HI_W32_font_callback_proc (_hoops_PCGCI, tm, _hoops_GSHIH, data);

					/* _hoops_PPSRGR */
					_hoops_PCGCI->lfItalic = FALSE;
					_hoops_PCGCI->lfUnderline = FALSE;
					_hoops_PCGCI->lfStrikeOut = TRUE;
					_hoops_PCGCI->lfWeight = 0;
					HI_W32_font_callback_proc (_hoops_PCGCI, tm, _hoops_GSHIH, data);

					/* _hoops_HPSRGR */
					_hoops_PCGCI->lfItalic = FALSE;
					_hoops_PCGCI->lfUnderline = FALSE;
					_hoops_PCGCI->lfStrikeOut = FALSE;
					_hoops_PCGCI->lfWeight = 700;
					HI_W32_font_callback_proc (_hoops_PCGCI, tm, _hoops_GSHIH, data);

					/* _hoops_RPSRGR, _hoops_APSRGR */
					_hoops_PCGCI->lfItalic = TRUE;
					_hoops_PCGCI->lfUnderline = TRUE;
					_hoops_PCGCI->lfStrikeOut = FALSE;
					_hoops_PCGCI->lfWeight = 0;
					HI_W32_font_callback_proc (_hoops_PCGCI, tm, _hoops_GSHIH, data);

					/* _hoops_RPSRGR, _hoops_PPSRGR */
					_hoops_PCGCI->lfItalic = TRUE;
					_hoops_PCGCI->lfUnderline = FALSE;
					_hoops_PCGCI->lfStrikeOut = TRUE;
					_hoops_PCGCI->lfWeight = 0;
					HI_W32_font_callback_proc (_hoops_PCGCI, tm, _hoops_GSHIH, data); 

					/* _hoops_RPSRGR, _hoops_APSRGR, _hoops_PPSRGR */
					_hoops_PCGCI->lfItalic = TRUE;
					_hoops_PCGCI->lfUnderline = TRUE;
					_hoops_PCGCI->lfStrikeOut = TRUE;
					_hoops_PCGCI->lfWeight = 0;
					HI_W32_font_callback_proc (_hoops_PCGCI, tm, _hoops_GSHIH, data);

					/* _hoops_RPSRGR, _hoops_APSRGR, _hoops_PPSRGR, _hoops_HPSRGR */
					_hoops_PCGCI->lfItalic = TRUE;
					_hoops_PCGCI->lfUnderline = TRUE;
					_hoops_PCGCI->lfStrikeOut = TRUE;
					_hoops_PCGCI->lfWeight = 700;
					HI_W32_font_callback_proc (_hoops_PCGCI, tm, _hoops_GSHIH, data);

					/* _hoops_RPSRGR, _hoops_HPSRGR */
					_hoops_PCGCI->lfItalic = TRUE;
					_hoops_PCGCI->lfUnderline = FALSE;
					_hoops_PCGCI->lfStrikeOut = FALSE;
					_hoops_PCGCI->lfWeight = 700;
					HI_W32_font_callback_proc (_hoops_PCGCI, tm, _hoops_GSHIH, data);

					/* _hoops_RPSRGR, _hoops_APSRGR, _hoops_HPSRGR */
					_hoops_PCGCI->lfItalic = TRUE;
					_hoops_PCGCI->lfUnderline = TRUE;
					_hoops_PCGCI->lfStrikeOut = FALSE;
					_hoops_PCGCI->lfWeight = 700;
					HI_W32_font_callback_proc (_hoops_PCGCI, tm, _hoops_GSHIH, data);

					/* _hoops_RPSRGR, _hoops_PPSRGR, _hoops_HPSRGR */
					_hoops_PCGCI->lfItalic = TRUE;
					_hoops_PCGCI->lfUnderline = FALSE;
					_hoops_PCGCI->lfStrikeOut = TRUE;
					_hoops_PCGCI->lfWeight = 700;
					HI_W32_font_callback_proc (_hoops_PCGCI, tm, _hoops_GSHIH, data);

					/* _hoops_PPSRGR, _hoops_HPSRGR */
					_hoops_PCGCI->lfItalic = FALSE;
					_hoops_PCGCI->lfUnderline = FALSE;
					_hoops_PCGCI->lfStrikeOut = TRUE;
					_hoops_PCGCI->lfWeight = 700;
					HI_W32_font_callback_proc (_hoops_PCGCI, tm, _hoops_GSHIH, data);

					/* _hoops_APSRGR, _hoops_HPSRGR*/
					_hoops_PCGCI->lfItalic = FALSE;
					_hoops_PCGCI->lfUnderline = TRUE;
					_hoops_PCGCI->lfStrikeOut = FALSE;
					_hoops_PCGCI->lfWeight = 700;
					HI_W32_font_callback_proc (_hoops_PCGCI, tm, _hoops_GSHIH, data);

					/* _hoops_APSRGR, _hoops_PPSRGR, _hoops_HPSRGR */
					_hoops_PCGCI->lfItalic = FALSE;
					_hoops_PCGCI->lfUnderline = TRUE;
					_hoops_PCGCI->lfStrikeOut = TRUE;
					_hoops_PCGCI->lfWeight = 700;
					HI_W32_font_callback_proc (_hoops_PCGCI, tm, _hoops_GSHIH, data);

					_hoops_RASRGR->_hoops_RCCCI = false;
				}
			}
		}
	}

	return true;
}


local int APIENTRY HI_W32_font_family_callback_proc (
	const LOGFONT				*_hoops_PCGCI,
	const TEXTMETRIC			*tm,
	DWORD						_hoops_GSHIH,
	LPARAM						data) {
	W32_Font_Enum_Passthru alter	*_hoops_RASRGR = (W32_Font_Enum_Passthru alter *)data;

	UNREFERENCED(tm);

	if (BIT (_hoops_GSHIH, TRUETYPE_FONTTYPE))
		(void)EnumFontFamilies (_hoops_RASRGR->_hoops_AGICI, _hoops_PCGCI->lfFaceName, HI_W32_font_callback_proc, data);

	if (BIT (_hoops_GSHIH, RASTER_FONTTYPE))
		(void)EnumFontFamilies (_hoops_RASRGR->_hoops_AGICI, _hoops_PCGCI->lfFaceName, HI_W32_font_callback_proc, data);

	return true;
}


GLOBAL_FUNCTION void HI_W32_find_all_fonts (
	Display_Context alter		*dc,
	_hoops_SGRRR				**_hoops_GRRRR,
	_hoops_SGRRR				**_hoops_AHSIH) {
	W32_Font_Enum_Passthru _hoops_RASRGR;
	_hoops_SGRRR * font;

	if (*_hoops_AHSIH == null) {
		_hoops_RASRGR._hoops_RCCCI = false;
		_hoops_RASRGR.list = 0;
		_hoops_RASRGR._hoops_AGICI = GetDC (GetDesktopWindow ());

		(void) EnumFontFamilies (_hoops_RASRGR._hoops_AGICI, NULL, HI_W32_font_family_callback_proc, (LPARAM)&_hoops_RASRGR);

		*_hoops_AHSIH = _hoops_RASRGR.list;

		ReleaseDC (GetDesktopWindow (), _hoops_RASRGR._hoops_AGICI);
	}

	font = *_hoops_AHSIH;

	while (font) {
		/* _hoops_GA'_hoops_RA _hoops_RHRRH _hoops_HRCSR _hoops_AIAH _hoops_HCIAA _hoops_GSGI */
		if (!HI_W32_find_font(*_hoops_GRRRR, font->name)) { 

			HD_Record_Font_With_Encoding(dc, font->name, font->specific, font->encoding, font->_hoops_IARCI, font->_hoops_IGGGH);

			if (font->_hoops_CARCI)
				HD_Mark_Font_As_Transformable (dc, font->name, font->_hoops_CARCI);
		}
		font = font->next;
	}
}


GLOBAL_FUNCTION bool HI_W32_find_one_font (
	Display_Context alter		*dc,
	char const						*_hoops_PACSR,
	void *							_hoops_SGSRGR,
	_hoops_SGRRR				**_hoops_GRRRR,
	_hoops_SGRRR				**_hoops_AHSIH) {
	LOGFONT			_hoops_IPSRGR;		
	LOGFONT			*_hoops_PCGCI = (LOGFONT alter *) &_hoops_IPSRGR;
	_hoops_SGRRR	*_hoops_HSSRH;
	char			opt[1024];
	int				i,ii;
	bool		_hoops_CPSRGR=false;
	bool		_hoops_SPSRGR=false;
	bool		_hoops_GHSRGR=false;
	HFONT			_hoops_PIRSI;
	HFONT			_hoops_RHGSI;
	float			_hoops_ISISR;
	float			_hoops_IGGGH;
	TEXTMETRIC		tm;
	unsigned int	_hoops_AHGSI = 0;
	char			error[4096];
	HDC				hDC = 0;

	UNREFERENCED (_hoops_SGSRGR);

	/* _hoops_AA _hoops_SR _hoops_HS _hoops_SCH _hoops_AIAH? */
	_hoops_HSSRH = HI_W32_find_font (*_hoops_AHSIH, _hoops_PACSR);

	if (_hoops_HSSRH && dc->_hoops_HSAGH) return true;

	_hoops_HSSRH = HI_W32_find_font (*_hoops_GRRRR, _hoops_PACSR);

	if (_hoops_HSSRH) return true;

	ZERO_STRUCT(_hoops_PCGCI, LOGFONT);

	i = 0;
	while (_hoops_PACSR[i] != '\0' && i < _hoops_GGAPR(_hoops_PCGCI->lfFaceName)-1 && _hoops_PACSR[i] != '-')
		_hoops_PCGCI->lfFaceName[i] = _hoops_PACSR[i++];

	_hoops_PCGCI->lfFaceName[i] = '\0';		

	while (_hoops_PACSR[i] != '\0' && _hoops_PACSR[i] != '-')
		i++;		/* _hoops_RPP _hoops_SR _hoops_CHGRH _hoops_RSIRR, _hoops_IHSH _hoops_IH '-' */

	while (_hoops_PACSR[i] == '-') {
		i++;
		ii = 0;

		while (_hoops_PACSR[i] != '\0' && _hoops_PACSR[i] != '-')
			opt[ii++] = _hoops_PACSR[i++];

		opt[ii] = '\0';

		if (_hoops_IGGPA(opt, "gdi"))
			_hoops_CPSRGR = true;
		else if (_hoops_IGGPA(opt, "vector"))
			_hoops_SPSRGR = true;
		else if (_hoops_IGGPA(opt, "raster"))
			_hoops_GHSRGR = true;
		else if (_hoops_IGGPA(opt, "italic"))
			_hoops_PCGCI->lfItalic = TRUE;
		else if (_hoops_IGGPA(opt, "underline"))
			_hoops_PCGCI->lfUnderline = TRUE;
		else if (_hoops_IGGPA(opt, "strikeout"))
			_hoops_PCGCI->lfStrikeOut = TRUE;
		else if (_hoops_IGGPA(opt, "bold"))
			_hoops_PCGCI->lfWeight = 700;
	}

	if (_hoops_CPSRGR && _hoops_GHSRGR)
		return false;

	if (!_hoops_CPSRGR || !_hoops_SPSRGR)
		return false;

	_hoops_PCGCI->lfCharSet = DEFAULT_CHARSET;
#ifndef _WIN32_WCE
	_hoops_PCGCI->lfClipPrecision = CLIP_EMBEDDED;
#endif
 
	_hoops_PIRSI = CreateFontIndirect(_hoops_PCGCI);

	if (_hoops_PIRSI == NULL)
		return false;

	hDC = GetDC (GetDesktopWindow ());

	_hoops_RHGSI = (HFONT) SelectObject (hDC, _hoops_PIRSI);

	if (!GetTextMetrics (hDC, &tm)) {
		_hoops_AHGSI = GetLastError ();

		sprintf (error, "GetTextMetrics failed with return code %ld on font", _hoops_AHGSI);
		_hoops_ARGIP (HEC_MSW_DRIVER, HES_LOAD_FONT_FAILED, error, _hoops_PCGCI->lfFaceName, "");

		SelectObject (hDC, _hoops_RHGSI);
		DeleteObject(_hoops_PIRSI);
		ReleaseDC (GetDesktopWindow (), hDC);
		return false;
	}

	SelectObject (hDC, _hoops_RHGSI);
	DeleteObject(_hoops_PIRSI);

	_hoops_ISISR = (float) tm.tmAscent - tm.tmInternalLeading;
	_hoops_IGGGH = (float) tm.tmHeight;
	_hoops_SRSRGR (_hoops_IGGGH, _hoops_ISISR);

	HI_W32_save_font (_hoops_GRRRR, _hoops_PCGCI, _hoops_PACSR, 0, 
		0.0f, _hoops_IGGGH/_hoops_ISISR, ((float)tm.tmAveCharWidth/(float)tm.tmAscent), 
		/*_hoops_IASRGR|_hoops_CASRGR|_hoops_SASRGR*/_hoops_IAGGH, _hoops_SACSR);

	HD_Record_Font_With_Encoding(dc, _hoops_PACSR, 0, _hoops_SACSR, 0, _hoops_IGGGH/_hoops_ISISR);

	HD_Mark_Font_As_Transformable (dc, _hoops_PACSR, /*_hoops_IASRGR|_hoops_CASRGR|_hoops_SASRGR*/_hoops_IAGGH);

	ReleaseDC (GetDesktopWindow (), hDC);
	return true;
}


GLOBAL_FUNCTION void HI_W32_find_basic_fonts (
	Display_Context alter	*dc,
	void *						_hoops_SGSRGR,
	_hoops_SGRRR			**_hoops_GRRRR,
	_hoops_SGRRR			**_hoops_AHSIH) {
   
	bool _hoops_RHSRGR = false, _hoops_AHSRGR = false, _hoops_PHSRGR = false; 
	bool _hoops_HHSRGR = false, _hoops_IHSRGR = false, _hoops_CHSRGR = false; 
	HDC hDC = (HDC)_hoops_SGSRGR;

	if (HI_W32_find_one_font (dc, "Arial-GDI-VECTOR", hDC, _hoops_GRRRR, _hoops_AHSIH)) {
		HD_Mark_Font_As_Generic (dc, "Arial-GDI-VECTOR", GFN_SANS_SERIF);
		_hoops_RHSRGR = true;
	}

	if (HI_W32_find_one_font (dc, "Times New Roman-GDI-VECTOR", hDC, _hoops_GRRRR, _hoops_AHSIH)) {
		HD_Mark_Font_As_Generic (dc, "Times New Roman-GDI-VECTOR", GFN_ROMAN);
		_hoops_AHSRGR = true;
	}

	if (HI_W32_find_one_font (dc, "Courier New-GDI-VECTOR", hDC, _hoops_GRRRR, _hoops_AHSIH)) {
		HD_Mark_Font_As_Generic (dc, "Courier New-GDI-VECTOR", GFN_TYPEWRITER);
		_hoops_PHSRGR = true;
	}
   
	if (HI_W32_find_one_font (dc, "Arial-GDI-VECTOR-BOLD", hDC, _hoops_GRRRR, _hoops_AHSIH)) {
		HD_Mark_Font_As_Generic (dc, "Arial-GDI-VECTOR-BOLD", _hoops_GIIGI);
		_hoops_HHSRGR = true;
	}

	if (HI_W32_find_one_font (dc, "Times New Roman-GDI-VECTOR-BOLD", hDC, _hoops_GRRRR, _hoops_AHSIH)) {
		HD_Mark_Font_As_Generic (dc, "Times New Roman-GDI-VECTOR-BOLD", _hoops_AIIGI);
		_hoops_IHSRGR = true;
	}

	if (HI_W32_find_one_font (dc, "Courier New-GDI-VECTOR-BOLD", hDC, _hoops_GRRRR, _hoops_AHSIH)) {
		HD_Mark_Font_As_Generic (dc, "Courier New-GDI-VECTOR-BOLD", _hoops_RIIGI);
		_hoops_CHSRGR = true;
	}
   
	if (!_hoops_RHSRGR && HI_W32_find_one_font (dc, "MS Sans Serif-GDI-RASTER", hDC, _hoops_GRRRR, _hoops_AHSIH)) {
		HD_Mark_Font_As_Generic (dc, "MS Sans Serif-GDI-RASTER", GFN_SANS_SERIF);
		_hoops_RHSRGR = true;
	}

	if (!_hoops_AHSRGR && HI_W32_find_one_font (dc, "MS Serif-GDI-RASTER", hDC, _hoops_GRRRR, _hoops_AHSIH)) {
		HD_Mark_Font_As_Generic (dc, "MS Serif-GDI-RASTER", GFN_ROMAN);
		_hoops_AHSRGR = true;
	}

	if (!_hoops_PHSRGR && HI_W32_find_one_font (dc, "Courier-GDI-RASTER", hDC, _hoops_GRRRR, _hoops_AHSIH)) {
		HD_Mark_Font_As_Generic (dc, "Courier-GDI-RASTER", GFN_TYPEWRITER);
		_hoops_PHSRGR = true;
	}

	if (!_hoops_HHSRGR && HI_W32_find_one_font (dc, "MS Sans Serif-GDI-RASTER-BOLD", hDC, _hoops_GRRRR, _hoops_AHSIH)) {
		HD_Mark_Font_As_Generic (dc, "MS Sans Serif-GDI-RASTER-BOLD", _hoops_GIIGI);
		_hoops_HHSRGR = true;
	}

	if (!_hoops_IHSRGR && HI_W32_find_one_font (dc, "MS Serif-GDI-RASTER-BOLD", hDC, _hoops_GRRRR, _hoops_AHSIH)) {
		HD_Mark_Font_As_Generic (dc, "MS Serif-GDI-RASTER-BOLD", _hoops_AIIGI);
		_hoops_IHSRGR = true;
	}

	if (!_hoops_CHSRGR && HI_W32_find_one_font (dc, "Courier-GDI-RASTER-BOLD", hDC, _hoops_GRRRR, _hoops_AHSIH)) {
		HD_Mark_Font_As_Generic (dc, "Courier-GDI-RASTER-BOLD", _hoops_RIIGI);
		_hoops_CHSRGR = true;
	}


	/*_hoops_ASIGA _hoops_PRGS
	_hoops_RPP (_hoops_SHSRGR (_hoops_CSPH, "_hoops_RHISC _hoops_CGIPP-_hoops_HRRPI-_hoops_SSSR", _hoops_SASRC, _hoops_GISRGR, _hoops_RISRGR)) {
		_hoops_AISRGR (_hoops_CSPH, "_hoops_RHISC _hoops_CGIPP-_hoops_HRRPI-_hoops_SSSR", -1);
	}*/
}

GLOBAL_FUNCTION bool HI_W32_name_font(
	Net_Rendition const &		nr,
	_hoops_IGPIR const *			_hoops_RRCSP,
	_hoops_IGPIR alter *			_hoops_ARCSP) {
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	char						specific[1024];
	char alter *				_hoops_ASAPR = specific;
	char alter *				_hoops_PSAPR = specific + _hoops_GGAPR (specific);

	_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", _hoops_RRCSP->specified.text);
	_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%s", "GDI");
	_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%s", "VECTOR");
	if (_hoops_HRCIR->_hoops_PSRIP) 
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%s", "ITALIC");
	if (_hoops_HRCIR->_hoops_ASRIP) 
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "-%s", "BOLD");

	*_hoops_ASAPR = '\0';

	ZERO_STRUCT(_hoops_ARCSP, _hoops_IGPIR);

	HI_Copy_Chars_To_Name(specific, &_hoops_ARCSP->specified);

	return true;
}

#else


GLOBAL_FUNCTION _hoops_RAARP * 
HI_W32_make_font_stencil (
	Font_Instance const	*instance,
	unsigned short			_hoops_IPCSR,
	int						_hoops_RHSIH,
	int						bolding_level,
	float					xrslant,
	float					xrrotation,
	float					xrwidth,
	bool				antialias) {

	UNREFERENCED (instance);
	UNREFERENCED (_hoops_IPCSR);
	UNREFERENCED (_hoops_RHSIH);
	UNREFERENCED (bolding_level);
	UNREFERENCED (xrslant);
	UNREFERENCED (xrrotation);
	UNREFERENCED (xrwidth);
	UNREFERENCED (antialias);

	return 0;
}
		
GLOBAL_FUNCTION bool HI_W32_measure_char_stenciled(
	Net_Rendition const &	nr,
	Font_Instance const * instance,
	Karacter _hoops_IPCSR,
	float alter *_hoops_GGGS,
	bool alter *_hoops_CPCSR,
	void ** _hoops_HPSRH) {

	UNREFERENCED (nr);
	UNREFERENCED (instance);
	UNREFERENCED (_hoops_IPCSR);
	UNREFERENCED (_hoops_GGGS);
	UNREFERENCED (_hoops_CPCSR);
	UNREFERENCED (_hoops_HPSRH);

	return false;
}
		
GLOBAL_FUNCTION void * 
HI_W32_load_font_stenciled(
	Display_Context const		*dc,
	char const						*name,
	Font_Instance alter			*instance,
	void *							hDC,
	_hoops_SGRRR		**_hoops_GRRRR,
	_hoops_SGRRR		**_hoops_AHSIH) {

	UNREFERENCED (dc);
	UNREFERENCED (name);
	UNREFERENCED (instance);
	UNREFERENCED (hDC);
	UNREFERENCED (_hoops_GRRRR);
	UNREFERENCED (_hoops_AHSIH);

	return 0;
}	

GLOBAL_FUNCTION void HI_W32_find_all_fonts (
	Display_Context alter		*dc,
	_hoops_SGRRR		**_hoops_GRRRR,
	_hoops_SGRRR		**_hoops_AHSIH) {

		
	UNREFERENCED (dc);
	UNREFERENCED (_hoops_GRRRR);	
	UNREFERENCED (_hoops_AHSIH);
}
		
GLOBAL_FUNCTION bool HI_W32_find_one_font (
	Display_Context alter		*dc,
	char const						*_hoops_PACSR,
	void *							hDC,
	_hoops_SGRRR		**_hoops_GRRRR,
	_hoops_SGRRR		**_hoops_AHSIH) {

	UNREFERENCED (dc);
	UNREFERENCED (_hoops_PACSR);
	UNREFERENCED (hDC);
	UNREFERENCED (_hoops_GRRRR);
	UNREFERENCED (_hoops_AHSIH);

	return false;
}
		
#define HDC void *
GLOBAL_FUNCTION void HI_W32_find_basic_fonts (
	Display_Context alter	*dc,
	HDC						hDC,
	_hoops_SGRRR	**_hoops_GRRRR,
	_hoops_SGRRR	**_hoops_AHSIH) {

	UNREFERENCED (dc);
	UNREFERENCED (hDC);
	UNREFERENCED (_hoops_GRRRR);
	UNREFERENCED (_hoops_AHSIH);
}
		
GLOBAL_FUNCTION bool HI_W32_name_font(
	Net_Rendition const &	nr,
	_hoops_IGPIR const			*_hoops_RRCSP,
	_hoops_IGPIR alter			*_hoops_ARCSP) {

		
	UNREFERENCED (nr);
	UNREFERENCED (_hoops_RRCSP);
	UNREFERENCED (_hoops_ARCSP);

	return false;
}

GLOBAL_FUNCTION _hoops_SGRRR alter *HI_W32_find_font (
	_hoops_SGRRR  *list,
	const char * name) {

	UNREFERENCED (list);
	UNREFERENCED (name);

	return 0;
}

GLOBAL_FUNCTION void HI_W32_unload_font_stenciled (
	Display_Context const * dc, 
	Font_Instance alter *instance) {

	UNREFERENCED(dc);
	UNREFERENCED(instance);

}


#endif 




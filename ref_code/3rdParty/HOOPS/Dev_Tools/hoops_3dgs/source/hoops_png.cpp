/*
 * Copyright (c) 2010 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.3 2010-10-14 17:20:32 heppe Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"
#include "hpserror.h"


#ifndef _hoops_AASSH
extern "C" {
	# include <png/png.h>
}
#include <setjmp.h>
#ifdef _MSC_VER         // _hoops_HHSP _hoops_RGR _hoops_GPSRR, _hoops_SR _hoops_CHR _hoops_RHRIR _hoops_IS _hoops_SGH _hoops_RGAR _hoops_IHRPR _hoops_RRGR _hoops_AARI _hoops_RH _hoops_CAARI
#   pragma warning (disable: 4611)  // _hoops_SAARI _hoops_GAPA '_hoops_GPARI' _hoops_PPR _hoops_IHRPR++ _hoops_CARA _hoops_HPGRR _hoops_HRGR _hoops_GRAA-_hoops_RPARI
#endif


struct _hoops_RRCRI {
	unsigned char const *_hoops_PHGH;
	unsigned int _hoops_PASIH;
	unsigned int _hoops_ARCRI;
	bool status;
};


static void _hoops_PRCRI(
		png_structp png_ptr,
		png_bytep data,
		png_size_t length)
{
	_hoops_RRCRI *rc = (_hoops_RRCRI *) png_get_io_ptr(png_ptr);
	if (length + rc->_hoops_ARCRI > rc->_hoops_PASIH) {
		rc->status = false;
	}
	else {
		COPY_MEMORY (rc->_hoops_PHGH + rc->_hoops_ARCRI, length, data);
		rc->_hoops_ARCRI += (unsigned int)length;
	}
}


GLOBAL_FUNCTION Image *HI_PNG_Decompress (
	Image		const *_hoops_HHARI) 
{
	Image *			_hoops_IHARI = null;
	Image_Format	_hoops_HRCRI;
	bool			status = true;
	unsigned char *	_hoops_PHGH = null;
	_hoops_RRCRI rc;

	int width = 0, height, i, y, offset;
	png_structp png_ptr;
	png_infop _hoops_IRCRI;
	int _hoops_CRCRI;
	int _hoops_SRCRI = 0;
	png_colorp _hoops_GACRI = null;
	unsigned char *scratch = null;

	ZERO_STRUCT (&rc, _hoops_RRCRI);
	rc._hoops_PHGH = (unsigned char const *)_hoops_HHARI->_hoops_PHGH;
	rc._hoops_PASIH = _hoops_HHARI->_hoops_IARH;
	rc.status = true;
	rc._hoops_ARCRI = 8; // _hoops_HSGR _hoops_IAPR _hoops_RH _hoops_PAPIA

	png_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		rc.status = false;
		goto _hoops_HPAGR;
	}
	_hoops_IRCRI = png_create_info_struct(png_ptr);
	if (!_hoops_IRCRI) {
		rc.status = false;
		goto _hoops_HPAGR;
	}
	if (setjmp(png_jmpbuf(png_ptr))) {
		rc.status = false;
		goto _hoops_HPAGR;
	}
	png_set_sig_bytes (png_ptr, 8);
	png_set_read_fn (png_ptr, &rc, (png_rw_ptr)_hoops_PRCRI);
	png_read_info (png_ptr, _hoops_IRCRI);


	width = _hoops_IRCRI->width;
	height = _hoops_IRCRI->height;
	if (BIT (_hoops_IRCRI->color_type, PNG_COLOR_MASK_ALPHA))
		_hoops_HRCRI = Image_RGBA32;
	else if (BIT (_hoops_IRCRI->valid, PNG_INFO_PLTE)) {
		png_get_PLTE (png_ptr, _hoops_IRCRI, &_hoops_GACRI, &_hoops_SRCRI);
		if (_hoops_IRCRI->color_type != PNG_COLOR_TYPE_PALETTE ||
			_hoops_SRCRI == 0) {
			HE_ERROR (HEC_IMAGE, HES_INVALID_TYPE, "unexpected color palette contents found during png decompression");
			rc.status = false;
			goto _hoops_HPAGR;
		}
		//_hoops_GIPHR _hoops_RH _hoops_IHCRH _hoops_IH _hoops_GII _hoops_RARP _hoops_SGS _hoops_PAH'_hoops_RA _hoops_IPHR _hoops_CCA _hoops_HIAH
		png_color *_hoops_APHCP = _hoops_GACRI;
		_hoops_HRCRI = _hoops_AHGH;
		for (i = 0 ; i < _hoops_SRCRI ; i++) {
			if (_hoops_APHCP->red != _hoops_APHCP->green || 
				_hoops_APHCP->green != _hoops_APHCP->blue) {
				_hoops_HRCRI = _hoops_HHGH;
				break;
			}
		}
		ALLOC_ARRAY (scratch, width, unsigned char);
	}
	else if (_hoops_IRCRI->color_type == PNG_COLOR_TYPE_GRAY)
		_hoops_HRCRI = _hoops_AHGH;
	else if (_hoops_IRCRI->color_type == PNG_COLOR_TYPE_RGB)
		_hoops_HRCRI = _hoops_HHGH;
	else  {
		HE_ERROR (HEC_IMAGE, HES_INVALID_TYPE, "unrecognized color type during png decompression");
		rc.status = false;
		goto _hoops_HPAGR;
	}


	/* _hoops_PS _hoops_RRP _hoops_IS _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_CSCR */
	HI_Create_Image(&_hoops_IHARI,
					null,
					width, height,
					_hoops_HRCRI, 0,
					_hoops_RRPGI, null);
	_hoops_IHARI->flags  |= (_hoops_HHARI->flags & _hoops_SCRRP);

	if (!_hoops_IHARI) {
		status = false;
		goto _hoops_HPAGR;
	}
	if (!_hoops_IHARI->_hoops_PHGH) {
		HE_ERROR (HEC_SYSTEM, HES_INVALID_TYPE,
			"Allocation failure during PNG decompression.");
		status = false;
		goto _hoops_HPAGR;
	}
	_hoops_PHGH = (unsigned char *)_hoops_IHARI->_hoops_PHGH;

	//_hoops_SR _hoops_ACPA _hoops_IH _hoops_RCRR _hoops_SR _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_RSRHR _hoops_SPHS _hoops_GPP _hoops_AGCR _hoops_SIH:
	// _hoops_RACRI (_hoops_CPHSR _hoops_HAARR)
	// _hoops_AACRI (_hoops_PACRI _hoops_GHIR)
	// _hoops_HACRI (_hoops_HAIR _hoops_IHCRH)
	if (ANYBIT (_hoops_IRCRI->valid, 
			PNG_INFO_gAMA | PNG_INFO_sBIT | PNG_INFO_cHRM | PNG_INFO_bKGD | 
			PNG_INFO_hIST | PNG_INFO_oFFs | PNG_INFO_pCAL | PNG_INFO_sRGB | PNG_INFO_sPLT | 
			PNG_INFO_sCAL | PNG_INFO_IDAT | PNG_INFO_tRNS | PNG_INFO_iCCP)) {
		//_hoops_RIHH _hoops_GPP _hoops_IACRI _hoops_ICHRH?
	}

	_hoops_CRCRI = png_set_interlace_handling (png_ptr);
	png_read_update_info (png_ptr, _hoops_IRCRI);
	for (y = 0 ; y < height ; y++) {
		offset = y * _hoops_IHARI->row_bytes;
		if (_hoops_GACRI == null) {
			png_read_row (png_ptr, (png_bytep)&_hoops_PHGH[offset], null);
		}
		else {
			unsigned char *_hoops_PCAP;
			png_color *_hoops_APHCP;
			png_read_row (png_ptr, scratch, null);
			_hoops_PCAP = &_hoops_PHGH[offset];
			for (i = 0 ; i < width ; i++) {
				 _hoops_APHCP = &_hoops_GACRI[scratch[i]];
				*_hoops_PCAP++ = _hoops_APHCP->red;
				if (_hoops_HRCRI == _hoops_HHGH) {
					*_hoops_PCAP++ = _hoops_APHCP->green;
					*_hoops_PCAP++ = _hoops_APHCP->blue;
				}
			}
		}
	}
	png_destroy_read_struct(&png_ptr, &_hoops_IRCRI, null);

  _hoops_HPAGR:
	if (scratch) {
		FREE_ARRAY (scratch, width, unsigned char);
	}
	if (!status) {
		if (_hoops_IHARI != null) {
			HI_Au_Revoir ((_hoops_HPAH *)_hoops_IHARI);
			_hoops_IHARI = null;
		}
	}
	return _hoops_IHARI;
}


GLOBAL_FUNCTION bool HI_Query_PNG_Dimensions (
		int _hoops_PASIH, 
		const void *_hoops_PHGH, 
		int alter *width, 
		int alter *height) 
{
	_hoops_RRCRI rc;
	png_structp png_ptr;
	png_infop _hoops_IRCRI;

	ZERO_STRUCT (&rc, _hoops_RRCRI);
	rc._hoops_PHGH = (unsigned char const *)_hoops_PHGH;
	rc._hoops_PASIH = _hoops_PASIH;
	rc.status = true;
	rc._hoops_ARCRI = 8; // _hoops_HSGR _hoops_IAPR _hoops_RH _hoops_PAPIA

	png_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		rc.status = false;
		goto _hoops_HPAGR;
	}
	_hoops_IRCRI = png_create_info_struct(png_ptr);
	if (!_hoops_IRCRI) {
		rc.status = false;
		goto _hoops_HPAGR;
	}
	if (setjmp(png_jmpbuf(png_ptr))) {
		rc.status = false;
		goto _hoops_HPAGR;
	}

	png_set_sig_bytes (png_ptr, 8);
	png_set_read_fn (png_ptr, &rc, (png_rw_ptr)_hoops_PRCRI);
	png_read_info (png_ptr, _hoops_IRCRI);
	if (width)
		*width = _hoops_IRCRI->width;
	if (height)
		*height = _hoops_IRCRI->height;
	png_destroy_read_struct(&png_ptr, &_hoops_IRCRI, null);

  _hoops_HPAGR:
	return rc.status;
}


GLOBAL_FUNCTION bool HI_PNG_Check_Transparency(
	Image		const *image) 
{
	_hoops_RRCRI rc;
	png_structp png_ptr;
	png_infop _hoops_IRCRI;
	bool _hoops_SHRC = false;

	ZERO_STRUCT (&rc, _hoops_RRCRI);
	rc._hoops_PHGH = (unsigned char const *)image->_hoops_PHGH;
	rc._hoops_PASIH = _hoops_IICIA;
	rc.status = true;
	rc._hoops_ARCRI = 8; // _hoops_HSGR _hoops_IAPR _hoops_RH _hoops_PAPIA
	png_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		goto _hoops_HPAGR;
	}
	_hoops_IRCRI = png_create_info_struct(png_ptr);
	if (!_hoops_IRCRI) {
		goto _hoops_HPAGR;
	}
	if (setjmp(png_jmpbuf(png_ptr))) {
		goto _hoops_HPAGR;
	}
	png_set_sig_bytes (png_ptr, 8);
	png_set_read_fn (png_ptr, &rc, (png_rw_ptr)_hoops_PRCRI);
	png_read_info (png_ptr, _hoops_IRCRI);
	_hoops_SHRC = BIT (_hoops_IRCRI->color_type, PNG_COLOR_MASK_ALPHA);

  _hoops_HPAGR:
	if (png_ptr)
		png_destroy_read_struct(&png_ptr, &_hoops_IRCRI, null);
	return _hoops_SHRC;
}


#else

GLOBAL_FUNCTION bool HI_Query_PNG_Dimensions (
		int _hoops_PASIH, 
		const void *_hoops_PHGH, 
		int alter *width, 
		int alter *height) 
{
	return false;
}



GLOBAL_FUNCTION Image *HI_PNG_Decompress (
	Image		const *image) 
{
	return null;
}

GLOBAL_FUNCTION bool HI_PNG_Check_Transparency(
	Image		const *image) 
{
	return false;
}

#endif


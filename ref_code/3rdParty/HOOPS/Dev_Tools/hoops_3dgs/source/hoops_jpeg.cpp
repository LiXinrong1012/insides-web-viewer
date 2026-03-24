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
 * $Id: obf_tmp.txt 1.5 2010-10-08 18:07:15 heppe Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"
#include "hpserror.h"


#ifndef _hoops_RASSH

//_hoops_PRRHP _hoops_IRS _hoops_CIAGR _hoops_RSIRR _hoops_IAARI
#define XMD_H
#ifdef FAR
#  undef FAR
#endif
extern "C" {
	# include "jpeglib.h"
}
#include <setjmp.h>
#ifdef _MSC_VER         // _hoops_HHSP _hoops_RGR _hoops_GPSRR, _hoops_SR _hoops_CHR _hoops_RHRIR _hoops_IS _hoops_SGH _hoops_RGAR _hoops_IHRPR _hoops_RRGR _hoops_AARI _hoops_RH _hoops_CAARI
#   pragma warning (disable: 4611)  // _hoops_SAARI _hoops_GAPA '_hoops_GPARI' _hoops_PPR _hoops_IHRPR++ _hoops_CARA _hoops_HPGRR _hoops_HRGR _hoops_GRAA-_hoops_RPARI
#endif


struct my_error_mgr {
	struct jpeg_error_mgr       jerr;       // _hoops_HPHR _hoops_APARI _hoops_RIHH _hoops_PPARI _hoops_HPGR _hoops_RSGI

	jmp_buf                     _hoops_HPARI;   // _hoops_RRSAR _hoops_PIH _hoops_RAS
};

struct image_data_buffer {
	unsigned char *                 buffer;	
	unsigned int                    allocated;	
	unsigned int                    used;		
};

extern "C" {
	static void my_jpeg_messages (j_common_ptr cinfo) {
		char                        msg_buffer[JMSG_LENGTH_MAX];

		(*cinfo->err->format_message) (cinfo, msg_buffer);
		HE_ERROR (HEC_JPEG, HES_DATA_ERROR, msg_buffer);
	}

	static void my_jpeg_error (j_common_ptr cinfo) {
		struct my_error_mgr *       err = (my_error_mgr *)cinfo->err;

		(*cinfo->err->output_message) (cinfo);  // _hoops_CRGH _hoops_RH _hoops_GPSRR

		longjmp (err->_hoops_HPARI, 1);             // _hoops_HGCR _hoops_ISSC _hoops_IS _hoops_RH _hoops_HGSI _hoops_IRIGR/_hoops_GGI _hoops_API & _hoops_RGRIR _hoops_HPCS
	}

	static void init_source (j_decompress_ptr cinfo) {
		struct jpeg_source_mgr *        src = cinfo->src;
		image_data_buffer *				_hoops_IPARI = (image_data_buffer *)cinfo->client_data;

		src->next_input_byte = (JOCTET *)_hoops_IPARI->buffer;
		src->bytes_in_buffer = _hoops_IPARI->allocated;
	}

	static boolean fill_input_buffer (j_decompress_ptr cinfo) {
		UNREFERENCED(cinfo);
		HE_ERROR (HEC_JPEG, HES_DATA_ERROR, "Jpeg decompress needs more data?");
		return FALSE;   // _hoops_RGRIR _hoops_RIARR
	}

	static void skip_input_data (j_decompress_ptr cinfo, long _hoops_CPARI) {
		struct jpeg_source_mgr *        src = cinfo->src;

		if (_hoops_CPARI <= 0)
			return;

		if ((unsigned int)_hoops_CPARI > src->bytes_in_buffer) {
			// _hoops_PAHA'_hoops_RA _hoops_IHPS, _hoops_GRS _hoops_RGRIR _hoops_IRS _hoops_SPARI() & _hoops_PHIS
			src->bytes_in_buffer = 0;
			return;
		}

		src->next_input_byte += _hoops_CPARI;
		src->bytes_in_buffer -= _hoops_CPARI;
	}

	static void term_source (j_decompress_ptr cinfo) {
		UNREFERENCED(cinfo);
	}
}



GLOBAL_FUNCTION bool HI_Query_JPEG_Dimensions (
		int _hoops_PASIH, 
		const void *_hoops_PHGH, 
		int alter *width, 
		int alter *height) 
{
	bool							status = true;
	struct jpeg_decompress_struct   cinfo;
	struct jpeg_source_mgr          src;
	struct my_error_mgr             err;
	image_data_buffer				scratch;
	ZERO_STRUCT (&scratch, image_data_buffer);

	if (_hoops_PHGH == null)
		return false;

	scratch.allocated = _hoops_PASIH;
	scratch.buffer = (unsigned char *)_hoops_PHGH;

	cinfo.err = jpeg_std_error (&err.jerr);
	cinfo.client_data = null;
	err.jerr.output_message = my_jpeg_messages;
	err.jerr.error_exit = my_jpeg_error;

	jpeg_create_decompress (&cinfo);

	//_hoops_GHARI (&_hoops_RHARI, _hoops_GCGIH * _hoops_AHARI);
	src.init_source = init_source;
	src.fill_input_buffer = null;
	src.skip_input_data = skip_input_data;
	src.resync_to_restart = jpeg_resync_to_restart;
	src.term_source = term_source;
	cinfo.src = &src;
	cinfo.client_data = &scratch;

	// _hoops_SR _hoops_HS _hoops_HCR _hoops_RH _hoops_PIH, _hoops_PIRC _hoops_IIGR _hoops_AGCR _hoops_PSCH _hoops_CGH _hoops_RHCA _hoops_CIIA _hoops_HRGR "_hoops_PHARI"
	jpeg_read_header (&cinfo, TRUE);
	jpeg_destroy_decompress (&cinfo);

	if (width)
		*width = cinfo.image_width;
	if (height)
		*height = cinfo.image_height;
	return status;
}


//_hoops_APPP _hoops_IRS _hoops_SGRH _hoops_CSCR, _hoops_HRS _hoops_PCCP _hoops_CCRRP _hoops_CSCR
GLOBAL_FUNCTION Image *HI_JPEG_Decompress (
		Image const *		_hoops_HHARI) 
{
	Image *							_hoops_IHARI = null;
	bool							status = true;
	struct jpeg_decompress_struct   cinfo;
	struct jpeg_source_mgr          src;
	struct my_error_mgr             err;
	JSAMPROW                        _hoops_CHARI[1];
	int                             row_bytes = _hoops_HHARI->width * 3;
	unsigned char *					_hoops_PHGH = null;
	image_data_buffer				scratch;
	ZERO_STRUCT (&scratch, image_data_buffer);

	if (_hoops_HHARI->format != _hoops_RGRH) {
		HE_ERROR (HEC_SYSTEM, HES_INVALID_TYPE,
			"Attempted JPEG decompression of non-JPEG image.");
		return null;
	}

	/* _hoops_PS _hoops_RRP _hoops_IS _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_CSCR */
	HI_Create_Image(&_hoops_IHARI,
					null,
					_hoops_HHARI->width, _hoops_HHARI->height,
					_hoops_HHGH, 0,
					_hoops_RRPGI, null);

	if (!_hoops_IHARI) {
		status = false;
		goto _hoops_HPAGR;
	}

	if (!_hoops_IHARI->_hoops_PHGH) {
		HE_ERROR (HEC_SYSTEM, HES_INVALID_TYPE,
			"Allocation failure during JPEG decompression.");
		status = false;
		goto _hoops_HPAGR;
	}
	_hoops_PHGH = (unsigned char *)_hoops_IHARI->_hoops_PHGH;

	scratch.allocated = _hoops_HHARI->_hoops_IARH;
	scratch.buffer = (unsigned char *)_hoops_HHARI->_hoops_PHGH;

	cinfo.err = jpeg_std_error (&err.jerr);
	cinfo.client_data = null;
	err.jerr.output_message = my_jpeg_messages;
	err.jerr.error_exit = my_jpeg_error;

	//_hoops_SHH _hoops_RHRIR _hoops_IS _hoops_SGH _hoops_RGAR _hoops_IHRPR _hoops_RRGR _hoops_AARI _hoops_RGR _hoops_CAARI
	if (setjmp (err._hoops_HPARI) != 0) {
		jpeg_destroy_decompress (&cinfo);
		HE_ERROR (HEC_JPEG, HES_DATA_ERROR, "jpeg decompression failure.");
		status = false;
		goto _hoops_HPAGR;
	}

	jpeg_create_decompress (&cinfo);

	//_hoops_GHARI (&_hoops_RHARI, _hoops_GCGIH * _hoops_AHARI);
	src.init_source = init_source;
	src.fill_input_buffer = fill_input_buffer;
	src.skip_input_data = skip_input_data;
	src.resync_to_restart = jpeg_resync_to_restart;
	src.term_source = term_source;
	cinfo.src = &src;
	cinfo.client_data = &scratch;

	// _hoops_SR _hoops_HS _hoops_HCR _hoops_RH _hoops_PIH, _hoops_PIRC _hoops_IIGR _hoops_AGCR _hoops_PSCH _hoops_CGH _hoops_RHCA _hoops_CIIA _hoops_HRGR "_hoops_PHARI"
	jpeg_read_header (&cinfo, TRUE);
	jpeg_start_decompress (&cinfo);
	while (cinfo.output_scanline < cinfo.output_height) {
		_hoops_CHARI[0] = (unsigned char *)&_hoops_PHGH[cinfo.output_scanline * row_bytes];
		jpeg_read_scanlines (&cinfo, _hoops_CHARI, 1);
	}
	jpeg_finish_decompress (&cinfo);
	jpeg_destroy_decompress (&cinfo);

	_hoops_IHARI->flags  |= (_hoops_HHARI->flags & _hoops_SCRRP);

  _hoops_HPAGR:
	if (!status) {
		if (_hoops_IHARI != null) {
			HI_Au_Revoir ((_hoops_HPAH *)_hoops_IHARI);
			_hoops_IHARI = null;
		}
	}
	return _hoops_IHARI;
}

#else

GLOBAL_FUNCTION Image *HI_JPEG_Decompress (
	Image		const *image) 
{

	return null;
}

#endif





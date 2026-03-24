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
 * $Id: obf_tmp.txt 1.192 2010-10-28 18:48:05 david Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "tandt.h"

#define _hoops_HISHS(_x_)	(unsigned char)((_x_) < 0 ? 0 : (_x_) <= 255 ? (_x_) : 255)
#define _hoops_IISHS(_r_,_hoops_RHAIC)	((unsigned char const *)image->rasters[_r_])[_hoops_RHAIC]
#define _hoops_CISHS(_r_,_hoops_RHAIC)	((_hoops_SHGH const *)image->rasters[_r_])[_hoops_RHAIC]
#define _hoops_SISHS(_r_,_hoops_RHAIC)	((_hoops_AIGH const *)image->rasters[_r_])[_hoops_RHAIC]

#if 0
#define _hoops_GCSHS
#endif
#ifdef _hoops_GCSHS
#include <stdio.h>
local void _hoops_RCSHS(Image * image) {
	_hoops_AIGH *	_hoops_ACSHS;
	FILE *		file;
	char		_hoops_RCCRC[4096];
	int			row, col;
	static		int _hoops_CICRC = 0;

	sprintf(_hoops_RCCRC,"scaled_image_%d.hmf", _hoops_CICRC++);
	file = fopen(_hoops_RCCRC, "wb");
	fprintf(file,";; HMF V1.24 TEXT\n");
	fprintf(file,"(Image 0 0 0 \"rgba, name=scaled_image \"(\n");

	for (row = 0; row < image->height; row++) {
		_hoops_ACSHS = (_hoops_AIGH*)image->rasters[row];
		fprintf(file,"(");
		for (col = 0; col < image->width; col++) {
			unsigned char _hoops_PIAGI = _hoops_ACSHS[col].r;
			unsigned char _hoops_RSIGH = _hoops_ACSHS[col].g;
			unsigned char _hoops_HIAGI = _hoops_ACSHS[col].b;
			unsigned char _hoops_IIAGI = _hoops_ACSHS[col].a;
			fprintf(file,"%d %d %d %d ", _hoops_PIAGI, _hoops_RSIGH, _hoops_HIAGI, _hoops_IIAGI);
			if (col%3 == 0) fprintf(file,"\n");
		}
		fprintf(file,")\n");
	}
	fprintf(file,"))");
	fclose(file);
}
#else
#define _hoops_RCSHS(image)
#endif


local bool
_hoops_PCSHS(unsigned int x) {
	return !(x & (x-1));
}


local Image * HI_Convert_To_RGBA32 (
	Net_Rendition const &		nr,
	Image *						image) 
{
	Image *_hoops_IHARI = null;
	Image *_hoops_HCSHS = null;
	int row;

	//_hoops_GRH _hoops_PRCA _hoops_IH _hoops_RH _hoops_CIAGR _hoops_ARAR _hoops_SGS _hoops_RRP _hoops_IS _hoops_IHPS _hoops_ARPP _hoops_RH _hoops_ICSHS
	switch (image->format) {
		case _hoops_GGRH: {
			_hoops_HCSHS = HI_PNG_Decompress (image);
			image = _hoops_HCSHS;
			if (image == null)
				return null;
		} break;

		case _hoops_RGRH: {
			_hoops_HCSHS = HI_JPEG_Decompress (image);
			image = _hoops_HCSHS;
			if (image == null)
				return null;
		} break;

		case _hoops_AGRH: {
			_hoops_HCSHS = HI_TARGA_Decompress (image);
			image = _hoops_HCSHS;
			if (image == null)
				return null;
		} break;

		case _hoops_IRRH:
		case _hoops_CRRH:
		case _hoops_SRRH: 
			//_hoops_GSRPI _hoops_SR _hoops_PAH _hoops_AA _hoops_ARI?
			HE_ERROR (HEC_SYSTEM, HES_INVALID_TYPE,
					"Software decompression of dxt images is not supported.");
			return null;

		//_hoops_AA _hoops_ISAP
		default:
			break;
	}

	/* _hoops_PS _hoops_RRP _hoops_IS _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_CSCR */
	HI_Create_Image(&_hoops_IHARI,
					null,
					image->width, image->height,
					Image_RGBA32, 0,
					_hoops_RRPGI, null);
	if (!_hoops_IHARI)
		return null;

	_hoops_IHARI->flags |= image->flags;
	if (BIT(image->flags, _hoops_SHCC))
		HOOPS_WORLD->_hoops_ACPIR++;

	if (BIT(image->flags, _hoops_GCRH))
		_hoops_IHARI->_hoops_HPIR = image->_hoops_HPIR;

	switch (image->format) {

		case _hoops_AHGH: {
			_hoops_AIGH alter *			_hoops_CCSHS;
			unsigned char const	*	_hoops_ACSHS;
			unsigned char const	*	_hoops_SCSHS;

			for (row = 0; row < image->height; row++) {
				_hoops_CCSHS = (_hoops_AIGH *) _hoops_IHARI->rasters[row];
				_hoops_ACSHS	= (unsigned char *) image->rasters[row];
				_hoops_SCSHS	= _hoops_ACSHS + image->width;

				while (_hoops_ACSHS < _hoops_SCSHS) {
					_hoops_CCSHS->r = 
						_hoops_CCSHS->g = 
						_hoops_CCSHS->b = *_hoops_ACSHS;
					_hoops_CCSHS->a = (unsigned char) 255;
					_hoops_CCSHS++;
					_hoops_ACSHS++;
				}
			}
		} break;

#ifndef DISABLE_NON_RGB_IMAGES
		case Image_MAPPED_8: {
#ifndef DISABLE_COLOR_MAPS
			_hoops_AIGH alter *			_hoops_CCSHS;
			unsigned char const	*	_hoops_ACSHS;
			unsigned char const	*	_hoops_SCSHS;
			Named_Material const *	_hoops_HAA;
			int						_hoops_GSSHS;

			_hoops_HAA = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR->_hoops_HAA;
			_hoops_GSSHS = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR->length - 1;

			if (_hoops_HAA) {
				for (row = 0; row < image->height; row++) {
					_hoops_CCSHS = (_hoops_AIGH *) _hoops_IHARI->rasters[row];
					_hoops_ACSHS	= (unsigned char *) image->rasters[row];
					_hoops_SCSHS	= _hoops_ACSHS + image->width;

					while (_hoops_ACSHS < _hoops_SCSHS) {
						if (*_hoops_ACSHS > _hoops_GSSHS) {
							HE_WARNING (HEC_COLOR_MAP, HES_COLOR_INDEX_IGNORED,
								Sprintf_DD (null,
										"Index %d of this mapped texture exceeds the local colormap size of %d.",
										_hoops_PSCSH(*_hoops_ACSHS), _hoops_GSSHS + 1));
							_hoops_CCSHS->r = _hoops_CCSHS->g = _hoops_CCSHS->b = _hoops_CCSHS->a = 255;
							_hoops_CCSHS++;
							_hoops_ACSHS++;
						}
						else {
							_hoops_CCSHS->r = (unsigned char) (255.99f *
								_hoops_HAA[*_hoops_ACSHS]._hoops_CSHR.red);
							_hoops_CCSHS->g = (unsigned char) (255.99f *
								_hoops_HAA[*_hoops_ACSHS]._hoops_CSHR.green);
							_hoops_CCSHS->b = (unsigned char) (255.99f *
								_hoops_HAA[*_hoops_ACSHS]._hoops_CSHR.blue);
							_hoops_CCSHS->a = (unsigned char) 255;
							_hoops_CCSHS++;
							_hoops_ACSHS++;
						}
					}
				}
			}
			else {
				HE_WARNING (HEC_COLOR_MAP, HES_COLOR_INDEX_IGNORED,
					"A 'Mapped 8' texture was applied, but no color map is in scope.");
			}
#endif
		}	break;

		case Image_MAPPED_16: {
#ifndef DISABLE_COLOR_MAPS
			_hoops_AIGH alter *			_hoops_CCSHS;
			unsigned short const *	_hoops_ACSHS;
			unsigned short const *	_hoops_SCSHS;
			Named_Material const *	_hoops_HAA;
			int						_hoops_GSSHS;

			_hoops_HAA = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR->_hoops_HAA;
			_hoops_GSSHS = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR->length - 1;

			if (_hoops_HAA) {
				for (row = 0; row < image->height; row++) {
					_hoops_CCSHS = (_hoops_AIGH *) _hoops_IHARI->rasters[row];
					_hoops_ACSHS	= (unsigned short *) image->rasters[row];
					_hoops_SCSHS	= _hoops_ACSHS + image->width;

					while (_hoops_ACSHS < _hoops_SCSHS) {
						if (*_hoops_ACSHS > _hoops_GSSHS) {
							HE_WARNING (HEC_COLOR_MAP, HES_COLOR_INDEX_IGNORED,
								Sprintf_DD (null,
										"Index %d of this mapped texture exceeds the local colormap size of %d.",
										_hoops_PSCSH(*_hoops_ACSHS), _hoops_GSSHS + 1));
							_hoops_CCSHS->r = _hoops_CCSHS->g = _hoops_CCSHS->b = _hoops_CCSHS->a = 255;
							_hoops_CCSHS++;
							_hoops_ACSHS++;
						}
						else{
							_hoops_CCSHS->r = (unsigned char) (255.99f *
								_hoops_HAA[*_hoops_ACSHS]._hoops_CSHR.red);
							_hoops_CCSHS->g = (unsigned char) (255.99f *
								_hoops_HAA[*_hoops_ACSHS]._hoops_CSHR.green);
							_hoops_CCSHS->b = (unsigned char) (255.99f *
								_hoops_HAA[*_hoops_ACSHS]._hoops_CSHR.blue);
							_hoops_CCSHS->a = (unsigned char) 255;
							_hoops_CCSHS++;
							_hoops_ACSHS++;
						}
					}
				}
			}
			else {
				HE_WARNING (HEC_COLOR_MAP, HES_COLOR_INDEX_IGNORED,
					"A 'Mapped 16' texture was applied, but no color map is in scope.");
			}
#endif
		}	break;
		case _hoops_HRSRH: {
			_hoops_AIGH alter *		_hoops_CCSHS;
			_hoops_IRSRH const *		_hoops_ACSHS;
			_hoops_IRSRH const *		_hoops_SCSHS;

			for (row = 0; row < image->height; row++) {
				_hoops_CCSHS = (_hoops_AIGH *) _hoops_IHARI->rasters[row];
				_hoops_ACSHS	= (_hoops_IRSRH *) image->rasters[row];
				_hoops_SCSHS	= _hoops_ACSHS + image->width;

				while (_hoops_ACSHS < _hoops_SCSHS) {
					_hoops_CCSHS->r = _hoops_ACSHS->r;
					_hoops_CCSHS->g = _hoops_ACSHS->g;
					_hoops_CCSHS->b = _hoops_ACSHS->b;
					_hoops_CCSHS->a = _hoops_ACSHS->a;
					_hoops_CCSHS++;
					_hoops_ACSHS++;
				}
			}
		}	break;
#endif

		case _hoops_HHGH: {
			_hoops_AIGH alter *		_hoops_CCSHS;
			_hoops_SHGH const *		_hoops_ACSHS;
			_hoops_SHGH const *		_hoops_SCSHS;

			for (row = 0; row < image->height; row++) {
				_hoops_CCSHS = (_hoops_AIGH *) _hoops_IHARI->rasters[row];
				_hoops_ACSHS	= (_hoops_SHGH *) image->rasters[row];
				_hoops_SCSHS	= _hoops_ACSHS + image->width;

				while (_hoops_ACSHS < _hoops_SCSHS) {
					_hoops_CCSHS->r = _hoops_ACSHS->r;
					_hoops_CCSHS->g = _hoops_ACSHS->g;
					_hoops_CCSHS->b = _hoops_ACSHS->b;
					_hoops_CCSHS->a = _hoops_GPGCR;
					_hoops_CCSHS++;
					_hoops_ACSHS++;
				}
			}
		}	break;

		case _hoops_CSGSP: {
			_hoops_AIGH alter *		_hoops_CCSHS;
			RGBAS32 const *		_hoops_ACSHS;
			RGBAS32 const *		_hoops_SCSHS;

			for (row = 0; row < image->height; row++) {
				_hoops_CCSHS = (_hoops_AIGH *) _hoops_IHARI->rasters[row];
				_hoops_ACSHS	= (RGBAS32 *) image->rasters[row];
				_hoops_SCSHS	= _hoops_ACSHS + image->width;

				if (BIT(image->flags, _hoops_SHCC)) {
					while (_hoops_ACSHS < _hoops_SCSHS) {
						_hoops_CCSHS->r = _hoops_ACSHS->r;
						_hoops_CCSHS->g = _hoops_ACSHS->g;
						_hoops_CCSHS->b = _hoops_ACSHS->b;
						_hoops_CCSHS->a = _hoops_ACSHS->a;
						_hoops_CCSHS++;
						_hoops_ACSHS++;
					}
				}
				else {
					while (_hoops_ACSHS < _hoops_SCSHS) {
						_hoops_CCSHS->r = _hoops_ACSHS->r;
						_hoops_CCSHS->g = _hoops_ACSHS->g;
						_hoops_CCSHS->b = _hoops_ACSHS->b;
						_hoops_CCSHS->a = _hoops_GPGCR;
						_hoops_CCSHS++;
						_hoops_ACSHS++;
					}
				}
			}
		}	break;

		case _hoops_PCCRH: {
			_hoops_AIGH alter *		_hoops_CCSHS;
			float const *		_hoops_ACSHS;
			float const *		_hoops_SCSHS;

			for (row = 0; row < image->height; row++) {
				_hoops_CCSHS = (_hoops_AIGH *) _hoops_IHARI->rasters[row];
				_hoops_ACSHS	= (float *) image->rasters[row];
				_hoops_SCSHS	= _hoops_ACSHS + image->width;

				while (_hoops_ACSHS < _hoops_SCSHS) {
					_hoops_CCSHS->r =
						_hoops_CCSHS->g =
							_hoops_CCSHS->b = int (*_hoops_ACSHS * 0xff);
					_hoops_CCSHS->a = _hoops_GPGCR;
					_hoops_CCSHS++;
					_hoops_ACSHS++;
				}
			}
		}	break;

		case Image_RGBA32: {
			_hoops_AIGH alter *		_hoops_CCSHS;
			_hoops_AIGH const *		_hoops_ACSHS;

			for (row = 0; row < image->height; row++) {
				_hoops_CCSHS = (_hoops_AIGH *) _hoops_IHARI->rasters[row];
				_hoops_ACSHS	= (_hoops_AIGH *) image->rasters[row];

				_hoops_AIGA(_hoops_ACSHS, image->width, _hoops_AIGH, _hoops_CCSHS);
			}
		}	break;

		default: {
			HE_ERROR (HEC_SYSTEM, HES_INVALID_TYPE,
			"Unknown texture image type.  System may have corrupted memory.");
		}	break;
	} /* _hoops_CICA (_hoops_CSCR-_hoops_RPCC) */

	if (_hoops_HCSHS) {
		HI_Au_Revoir ((_hoops_HPAH *)_hoops_HCSHS);
	}

	_hoops_RCSHS(_hoops_IHARI);
	return _hoops_IHARI;
}

/* _hoops_HGI _hoops_API _hoops_RSSAR _hoops_IRS _hoops_HH _hoops_GHRP _hoops_IH _hoops_SGH _hoops_GAR _hoops_IRS _hoops_RSSHS
 * _hoops_AISR.  _hoops_HHIGR _hoops_GRIRA _hoops_IRS _hoops_SCAC _hoops_HGPC _hoops_IGIAR _hoops_RH _hoops_SPPR _hoops_IH _hoops_AGSRH _hoops_PHIRC.
 * (_hoops_HIS _hoops_HISI _hoops_API _hoops_GRS _hoops_SHH _hoops_IHRHA _hoops_RH _hoops_PSIAH _hoops_SSCP _hoops_IS _hoops_HIHA _hoops_IH _hoops_SGS)
 * _hoops_IPCP _hoops_CRIPR _hoops_PRHC (_hoops_GCRGC) _hoops_SHR _hoops_IGISR _hoops_RH _hoops_ACSP _hoops_IIGR _hoops_RH _hoops_HH.  _hoops_IPCP _hoops_PSSPR
 * _hoops_PRHC _hoops_IGISR _hoops_IRS _hoops_PRGGR _hoops_GAR _hoops_ASSHS _hoops_HPP _hoops_PSSHS.	_hoops_HSSHS _hoops_HRGR _hoops_IISGR
 * _hoops_GAPA _hoops_RH _hoops_PGCR.	 _hoops_IPCP _hoops_HH _hoops_HRGR _hoops_PGS _hoops_SSPH, _hoops_HIH _hoops_HHRP _hoops_ISSHS _hoops_CCA
 * _hoops_AIIR _hoops_HSH.  _hoops_CCSCI _hoops_HRGR _hoops_SHR _hoops_RRAA (_hoops_AAPC _hoops_SISR _hoops_AAPC) */

GLOBAL_FUNCTION Image * HI_Create_Spotlight_Image (
	int					_hoops_HGII,
	float				_hoops_HASIH) {
#ifndef DISABLE_EXTENDED_TEXTURE
	_hoops_AIGH alter *		_hoops_CSSHS;
	_hoops_AIGH const *		end;
	int					row;
	Image *				_hoops_IHARI = null;
	float				_hoops_GHASH, _hoops_SPASH, x, y, _hoops_SSSHS, _hoops_GGGIS;

	/* _hoops_PS _hoops_RRP _hoops_IS _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_CSCR */
	HI_Create_Image(&_hoops_IHARI,
					null,
					_hoops_HGII, _hoops_HGII,
					Image_RGBA32, 0,
					_hoops_RRPGI, null);

	if (!_hoops_IHARI)
		return null;

	_hoops_GHASH = _hoops_SPASH = 1.0f/(((float)_hoops_HGII/2)-1);
	y = -_hoops_SPASH * (_hoops_HGII/2);
	_hoops_GGGIS = _hoops_HASIH*_hoops_HASIH;
	for (row = 0 ; row < _hoops_HGII ; row++) {
		x = -_hoops_GHASH * (_hoops_HGII/2);
		_hoops_CSSHS = (_hoops_AIGH *) _hoops_IHARI->rasters[row];
		end = _hoops_CSSHS + _hoops_HGII;
		while (_hoops_CSSHS < end) {
			_hoops_CSSHS->a = 255;
			_hoops_SSSHS = x*x + y*y;
			if (_hoops_SSSHS > 1.0f)
				_hoops_CSSHS->r = _hoops_CSSHS->g = _hoops_CSSHS->b = 0;
			else if (_hoops_SSSHS < _hoops_GGGIS)
				_hoops_CSSHS->r = _hoops_CSSHS->g = _hoops_CSSHS->b = 255;
			else {
				/* _hoops_RPP _hoops_PSSHS _hoops_HRGR _hoops_RRPAR _hoops_HSAR _hoops_PAR _hoops_SASPR _hoops_IS 1, _hoops_SCH _hoops_PAHA'_hoops_RA
				 * _hoops_SHH _hoops_SSRR _hoops_IS _hoops_HGCR _hoops_ARI */
				/* _hoops_AGHR (_hoops_PSSHS < 1.0f); */
				_hoops_CSSHS->r = _hoops_CSSHS->g = _hoops_CSSHS->b = (unsigned char)(255.99 * (1.0f - HI_Sqrt(_hoops_SSSHS)) / (1.0f - _hoops_HASIH));
			}
			x += _hoops_GHASH;
			_hoops_CSSHS++;
		}
		y += _hoops_SPASH;
	}
	/* _hoops_CISA _hoops_GGR _hoops_RH _hoops_SCIA _hoops_PPR _hoops_PRPC */
	_hoops_CSSHS = (_hoops_AIGH *) _hoops_IHARI->rasters[0];
	end = _hoops_CSSHS + _hoops_HGII;
	while (_hoops_CSSHS < end) {
		_hoops_CSSHS->r = _hoops_CSSHS->g = _hoops_CSSHS->b = 0;
		_hoops_CSSHS->a = 255;
		_hoops_CSSHS++;
	}
	_hoops_AIGA ((void *)_hoops_IHARI->rasters[0], _hoops_HGII, _hoops_AIGH, (void *)_hoops_IHARI->rasters[_hoops_HGII-1]);
	/* _hoops_CISA _hoops_GGR _hoops_RH _hoops_RAAP _hoops_PPR _hoops_RPHR _hoops_IAPHR */
	for (row = 0 ; row < _hoops_HGII ; row++) {
		_hoops_CSSHS = (_hoops_AIGH *)_hoops_IHARI->rasters[row];
		_hoops_CSSHS->r = _hoops_CSSHS->g = _hoops_CSSHS->b = 0;
		_hoops_CSSHS->a = 255;
		_hoops_CSSHS = (_hoops_AIGH *)_hoops_IHARI->rasters[row] + _hoops_HGII-1;
		_hoops_CSSHS->r = _hoops_CSSHS->g = _hoops_CSSHS->b = 0;
		_hoops_CSSHS->a = 255;
	}


	/* _hoops_RGGIS(_hoops_AGGIS); */
	return _hoops_IHARI;
#else
	return null;
#endif
}




//_hoops_RSSAR _hoops_PCCP _hoops_CSCR _hoops_SGS _hoops_PAH _hoops_SHH _hoops_IGI _hoops_GAR _hoops_IRS _hoops_HH _hoops_IH _hoops_HAIR _hoops_AHIAR _hoops_CPAP
GLOBAL_FUNCTION Image * HI_Create_Indexication_Image (
		Net_Rendition const &nr)
{
#ifndef DISABLE_EXTENDED_TEXTURE
	Image *				_hoops_IHARI = null;
	_hoops_RHAH const		*_hoops_CSIR;
	int					i;
	RGB	const *			rgb;
	_hoops_AIGH alter *		_hoops_SISA;
	int					length;

	_hoops_CSIR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;
	length = _hoops_CSIR->length;
	/* _hoops_PS _hoops_RRP _hoops_IS _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_CSCR */
	HI_Create_Image(&_hoops_IHARI,
					null,
					length, 1,
					Image_RGBA32, 0,
					_hoops_RRPGI, null);


	_hoops_SISA = (_hoops_AIGH *) _hoops_IHARI->rasters[0];
	for (i = 0 ; i < length ; i++) {
		rgb = &_hoops_CSIR->_hoops_HAA[i]._hoops_CSHR;
		_hoops_SISA->r = (unsigned char)(rgb->red * 255);
		_hoops_SISA->g = (unsigned char)(rgb->green * 255);
		_hoops_SISA->b = (unsigned char)(rgb->blue * 255);
		_hoops_SISA->a = (unsigned char)(255);
		_hoops_SISA++;
	}

	if (!_hoops_IHARI)
		return null;

	/* _hoops_RGGIS(_hoops_AGGIS); */
	return _hoops_IHARI;
#else
	return null;
#endif
}


local Image * _hoops_PGGIS (
	Image const *				image,
	_hoops_AHAH const &				_hoops_PHAH) {
	_hoops_AIGH alter *				_hoops_CSSHS;
	int							row, col;
	Image *						_hoops_IHARI = null;

	/* _hoops_PS _hoops_RRP _hoops_IS _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_CSCR */
	HI_Create_Image(&_hoops_IHARI,
					null,
					image->width, image->height,
					Image_RGBA32, 0,
					_hoops_RRPGI, null);

	if (!_hoops_IHARI)
		return null;

	_hoops_IHARI->flags |= image->flags;
	_hoops_IHARI->flags |= _hoops_GIRH;
	_hoops_IHARI->_hoops_PHAH = _hoops_PHAH;
	if (BIT(image->flags, _hoops_SHCC))
		HOOPS_WORLD->_hoops_ACPIR++;

	if (image->format == _hoops_HHGH) {
		_hoops_SHGH const *				_hoops_ACSHS;

		for (row = 0; row < image->height; row++) {
			_hoops_ACSHS = (_hoops_SHGH const *) image->rasters[row];
			_hoops_CSSHS = (_hoops_AIGH alter *) _hoops_IHARI->rasters[row];

			for (col = 0; col < image->width; col++) {
				RGB		tmp = *_hoops_ACSHS;
				tmp = HD_Apply_Color_Effects (tmp, _hoops_PHAH);
				*_hoops_CSSHS++ = _hoops_AIGH (tmp, (unsigned char)0xff);
				_hoops_ACSHS++;
			}
		}
	}
	else
	{
		_hoops_AIGH const *				_hoops_ACSHS;

		ASSERT (image->format == Image_RGBA32);
		for (row = 0; row < image->height; row++) {
			_hoops_ACSHS = (_hoops_AIGH const *) image->rasters[row];
			_hoops_CSSHS = (_hoops_AIGH alter *) _hoops_IHARI->rasters[row];

			for (col = 0; col < image->width; col++) {
				RGB		tmp = *_hoops_ACSHS;
				tmp = HD_Apply_Color_Effects (tmp, _hoops_PHAH);
				*_hoops_CSSHS++ = _hoops_AIGH (tmp, _hoops_ACSHS->a);
				_hoops_ACSHS++;
			}
		}
	}

	return _hoops_IHARI;
}


enum _hoops_HGGIS {
	_hoops_IGGIS		= 0,
	_hoops_CGGIS		= 1,
	_hoops_SGGIS			= 2,
	_hoops_GRGIS		= 3,
	_hoops_RRGIS	= 9, //_hoops_HAR _hoops_APP
	_hoops_ARGIS		= 10,
	_hoops_PRGIS = 11,
	_hoops_HRGIS		= 0x8,
};

GLOBAL_FUNCTION bool HI_Query_TARGA_Dimensions (
		int _hoops_PASIH, 
		const void *_hoops_PHGH, 
		int alter *width, 
		int alter *height)
{
#ifndef DISABLE_EXTENDED_TEXTURE
	unsigned const char *data = (unsigned const char *)_hoops_PHGH;
	int w, h;

	switch (data[2]) {
		case _hoops_SGGIS:
		case _hoops_GRGIS:
		case _hoops_ARGIS:
		case _hoops_PRGIS: {
			w = data[12] + (data[13] << 8);
			h = data[14] + (data[15] << 8);
			*width = w;
			*height = h;
		} break;

		case _hoops_CGGIS:
		case _hoops_RRGIS: {
			int _hoops_IRGIS = data[1];
			if (_hoops_IRGIS == 1) {
				HE_ERROR (HEC_TEXTURE, HES_INVALID_TYPE, "Color-mapped TARGA images are not supported");
				return false;
			}
		} //_hoops_CRGIS;
		default:
			HE_ERROR (HEC_SYSTEM, HES_INVALID_TYPE, "invalid TARGA image data");
			return false;
	}
	UNREFERENCED (_hoops_PASIH);
	return true;
#else
	return false;
#endif
}



//_hoops_IIHA _hoops_GPP _hoops_SRGIS _hoops_SIHC _hoops_AHCA _hoops_RSSGC _hoops_HII _hoops_IHHRA://_hoops_IIHRH._hoops_GAGIS._hoops_GIHRA/_hoops_RAGIS/_hoops_AAGIS
GLOBAL_FUNCTION Image *HI_TARGA_Decompress (
		Image const *_hoops_HHARI)
{
#ifndef DISABLE_EXTENDED_TEXTURE
	Image *				_hoops_IHARI = null;
	bool				status = true;
	unsigned const char *_hoops_PHGH = (unsigned const char *)_hoops_HHARI->_hoops_PHGH;
	unsigned const char *src;
	unsigned const char *end;
	unsigned char *		_hoops_PCAP;
	unsigned char *		scratch = null;
	int					size;
	int					i;

	if (_hoops_HHARI->format != _hoops_AGRH) {
		HE_ERROR (HEC_SYSTEM, HES_INVALID_TYPE,
			"Attempted TARGA decompression of non-TARGA image.");
		return null;
	}

	//_hoops_SCSH _hoops_PAGIS = _hoops_RIS[0];
	//_hoops_SCSH _hoops_HAGIS = _hoops_RIS[1];
	ASSERT (_hoops_PHGH[1] == 0); //_hoops_HAIR _hoops_ARCR (_hoops_HAR _hoops_GIR _hoops_GAPR)
	int _hoops_IAGIS = _hoops_PHGH[2];
	ASSERT (_hoops_PHGH[3] == 0 && _hoops_PHGH[4] == 0 && _hoops_PHGH[5] == 0 && _hoops_PHGH[6] == 0 && _hoops_PHGH[7] == 0); //_hoops_SIHC _hoops_AHCA _hoops_HAIR _hoops_ARCR (_hoops_HAR _hoops_GIR _hoops_GAPR)
	//_hoops_SCSH _hoops_RCPSC = _hoops_RIS[ 8] + (_hoops_RIS[ 9] << 8);
	//_hoops_SCSH _hoops_ACPSC = _hoops_RIS[10] + (_hoops_RIS[11] << 8);
	int w = _hoops_PHGH[12] + (_hoops_PHGH[13] << 8);
	int h = _hoops_PHGH[14] + (_hoops_PHGH[15] << 8);
	int _hoops_GCPIR = _hoops_PHGH[16] / 8;
	int _hoops_CAGIS = _hoops_PHGH[17] & 0xF;
	int _hoops_SAGIS = !BIT(_hoops_PHGH[17], 0x20);
	ASSERT (!ANYBIT (_hoops_PHGH[17], 0xC0)); //_hoops_AAPA 2 _hoops_SIH _hoops_GPGIS _hoops_IS _hoops_RPGIS (_hoops_HAR _hoops_GIR _hoops_GAPR)

	Image_Format _hoops_APGIS;
	if (_hoops_CAGIS != 0) {
		_hoops_APGIS = Image_RGBA32;
		size = 4*w*h;
	}
	else if (_hoops_GCPIR == 3) {
		_hoops_APGIS = _hoops_HHGH;
		size = 3*w*h;
	}
	else {
		_hoops_APGIS = _hoops_AHGH;
		size = w*h;
	}

	/* _hoops_PS _hoops_RRP _hoops_IS _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_CSCR */
	HI_Create_Image(&_hoops_IHARI,
					null,
					w, h,
					_hoops_APGIS, 0,
					_hoops_RRPGI, null);
	if (!_hoops_IHARI->_hoops_PHGH) {
		HE_ERROR (HEC_SYSTEM, HES_INVALID_TYPE,
			"Allocation failure during TARGA decompression.");
		status = false;
		goto _hoops_HPAGR;
	}

	if (_hoops_SAGIS) {
		ALLOC_ARRAY_CACHED (scratch, size, unsigned char);
		_hoops_PCAP = scratch;
	}
	else
		_hoops_PCAP = (unsigned char *)_hoops_IHARI->_hoops_PHGH;
	src = _hoops_PHGH + 18 + _hoops_PHGH[0]; //_hoops_GGCR _hoops_RGSPR _hoops_SPCC _hoops_PPR _hoops_CSCR _hoops_CRSRR _hoops_SPCC 
	end = _hoops_PCAP + size;
	if (BIT (_hoops_IAGIS, _hoops_HRGIS)) {
		do {
			//_hoops_RGR _hoops_ARIP _hoops_IIHA _hoops_GPP _hoops_SIHC _hoops_HII 
			//   _hoops_IHHRA://_hoops_IRGH._hoops_PPGIS._hoops_HPGIS._hoops_IRPII._hoops_IPGIS/~_hoops_CPGIS/_hoops_SPGIS/_hoops_RRSPC  
			int _hoops_GHGIS = *src++;
			if (_hoops_GHGIS & 0x80) {
				//_hoops_ARISC-_hoops_PIGAI _hoops_RHGIS
				int _hoops_AHGIS = 1 + (_hoops_GHGIS & 0x7F);
				if (_hoops_APGIS == _hoops_AHGH) {
					for (i = 0 ; i < _hoops_AHGIS ; i++) {
						*_hoops_PCAP++ = *src;
					} 
					src++;
				}
				else if (_hoops_APGIS == _hoops_HHGH) {
					for (i = 0 ; i < _hoops_AHGIS ; i++) {
						*_hoops_PCAP++ = src[2];
						*_hoops_PCAP++ = src[1];
						*_hoops_PCAP++ = src[0];
					} 
					src += 3;
				}
				else { 
					ASSERT(_hoops_APGIS == Image_RGBA32); 
					if (_hoops_GCPIR == 4) {
						for (i = 0 ; i < _hoops_AHGIS ; i++) {
							*_hoops_PCAP++ = src[2];
							*_hoops_PCAP++ = src[1];
							*_hoops_PCAP++ = src[0];
							*_hoops_PCAP++ = src[3];
						} 
						src += 4; 
					}
					else if (_hoops_GCPIR == 2) {
						for (i = 0 ; i < _hoops_AHGIS ; i++) {
							*_hoops_PCAP++ = src[0]; //_hoops_PCCIR
							*_hoops_PCAP++ = src[0]; //_hoops_ISHI
							*_hoops_PCAP++ = src[0]; //_hoops_RCSR
							*_hoops_PCAP++ = src[1]; //_hoops_IRS
						} 
						src += 2; 
					}
				}
			}
			else {
				//_hoops_AGGP _hoops_RHGIS
				int _hoops_PHGIS = 1 + (_hoops_GHGIS & 0x7F);
				if (_hoops_APGIS == _hoops_AHGH) {
					for (i = 0 ; i < _hoops_PHGIS ; i++) {
						*_hoops_PCAP++ = *src++;
					}
				}
				else if (_hoops_APGIS == _hoops_HHGH) {
					for (i = 0 ; i < _hoops_PHGIS ; i++) {
						*_hoops_PCAP++ = src[2];
						*_hoops_PCAP++ = src[1];
						*_hoops_PCAP++ = src[0];
						src += 3;
					}
				}
				else {
					ASSERT(_hoops_APGIS == Image_RGBA32); 
					if (_hoops_GCPIR == 4) {
						for (i = 0 ; i < _hoops_PHGIS ; i++) {
							*_hoops_PCAP++ = src[2];
							*_hoops_PCAP++ = src[1];
							*_hoops_PCAP++ = src[0];
							*_hoops_PCAP++ = src[3];
							src += 4;
						}
					}
					else {
						for (i = 0 ; i < _hoops_PHGIS ; i++) {
							*_hoops_PCAP++ = src[0]; //_hoops_PCCIR
							*_hoops_PCAP++ = src[0]; //_hoops_ISHI
							*_hoops_PCAP++ = src[0]; //_hoops_RCSR
							*_hoops_PCAP++ = src[1]; //_hoops_IRS
							src += 2;
						}
					}
				}
			}
		} while (_hoops_PCAP < end);
	}
	else {
		if (_hoops_APGIS == _hoops_AHGH) {
			COPY_MEMORY (src, size, _hoops_PCAP);
		}
		else if (_hoops_APGIS == _hoops_HHGH) {
			do {
				*_hoops_PCAP++ = src[2];
				*_hoops_PCAP++ = src[1];
				*_hoops_PCAP++ = src[0];
				src += 3;
			} while (_hoops_PCAP < end);
		}
		else {
			ASSERT(_hoops_APGIS == Image_RGBA32); 
			if (_hoops_GCPIR == 4) {
				do {
					*_hoops_PCAP++ = src[2];
					*_hoops_PCAP++ = src[1];
					*_hoops_PCAP++ = src[0];
					*_hoops_PCAP++ = src[3];
					src += 4;
				} while (_hoops_PCAP < end);
			}
			else if (_hoops_GCPIR == 2) {
				for (;;) {
					*_hoops_PCAP++ = src[0]; //_hoops_PCCIR
					*_hoops_PCAP++ = src[0]; //_hoops_ISHI
					*_hoops_PCAP++ = src[0]; //_hoops_RCSR
					*_hoops_PCAP++ = src[1]; //_hoops_IRS
					src += 2;
					if (_hoops_PCAP >= end)
						break;
				}
			}
			else
				ASSERT(0);
		}
	}
	ASSERT (_hoops_PCAP == end);

	if (_hoops_SAGIS) {
		int row_bytes = (w * _hoops_GCPIR);
		_hoops_PCAP = (unsigned char *)_hoops_IHARI->_hoops_PHGH;
		src = scratch + size - row_bytes;
		for (i = 0 ; i < h ; i++) {
			_hoops_AIGA (src, row_bytes, unsigned char, _hoops_PCAP);
			_hoops_PCAP += row_bytes;
			src -= row_bytes;
		}
	}

  _hoops_HPAGR:
	if (scratch != null)
		FREE_ARRAY (scratch, size, unsigned char);

	if (!status) {
		if (_hoops_IHARI != null) {
			HI_Au_Revoir ((_hoops_HPAH *)_hoops_IHARI);
			_hoops_IHARI = null;
		}
	}
	return _hoops_IHARI;
#else
	return null;
#endif
}


GLOBAL_FUNCTION bool HI_DXT_Check_Transparency(
		Image const *image)
{
#ifndef DISABLE_EXTENDED_TEXTURE
	int i;
	int _hoops_HHGIS;
	unsigned const char *_hoops_IHGIS;
	
	_hoops_IHGIS = (unsigned const char *)image->_hoops_PHGH;
	_hoops_HHGIS = image->width * image->height / 16;

	if (image->format == _hoops_IRRH) {
		return false;
	}
	else if (image->format == _hoops_CRRH) {
		for (i = 0 ; i < _hoops_HHGIS ; i++) {
			unsigned int const *_hoops_CHGIS = (unsigned int const *)_hoops_IHGIS;
			//_hoops_SRS 64 _hoops_SIH _hoops_HAISC _hoops_AIIR.  _hoops_CGP _hoops_CCGC _hoops_PGPC, _hoops_RH _hoops_RIS _hoops_HRGR _hoops_CIGC
			if (_hoops_CHGIS[0] != ~0 ||
				_hoops_CHGIS[1] != ~0)
				return true;
			_hoops_IHGIS += 16;
		}
	}
	else {
		ASSERT (image->format == _hoops_SRRH);
		for (i = 0 ; i < _hoops_HHGIS ; i++) {
			//0 _hoops_PPR 5 _hoops_CHR _hoops_IRS _hoops_GRH _hoops_AARRA _hoops_SGS _hoops_CRHPR _hoops_RH _hoops_RIS _hoops_CIGC (_hoops_AISP _hoops_SHGIS _hoops_HII _hoops_GIGIS _hoops_RRRRA)
			if (_hoops_IHGIS[0] != 0 || 
				_hoops_IHGIS[1] != 5)
				return true; 
			_hoops_IHGIS += 16;
		}
	}
	return false;
#else
	return false;
#endif
}

GLOBAL_FUNCTION bool HI_TARGA_Check_Transparency(
		Image const *_hoops_HHARI)
{
#ifndef DISABLE_EXTENDED_TEXTURE
	unsigned const char *_hoops_PHGH = (unsigned const char *)_hoops_HHARI->_hoops_PHGH;
	unsigned const char *src;

	if (_hoops_HHARI->format != _hoops_AGRH) {
		_hoops_IPR (HEC_TEXTURE, HES_INVALID_TYPE, 
					"Attempted TARGA query on non-TARGA image.");
		return false;
	}

	//_hoops_SCSH _hoops_PAGIS = _hoops_RIS[0];
	//_hoops_SCSH _hoops_HAGIS = _hoops_RIS[1];
	//_hoops_AGHR (_hoops_RIS[1] == 0)
	int _hoops_IAGIS = _hoops_PHGH[2];
	//_hoops_AGHR (_hoops_RIS[3] == 0 && _hoops_RIS[4] == 0 && _hoops_RIS[5] == 0 && _hoops_RIS[6] == 0 && _hoops_RIS[7] == 0); //_hoops_SIHC _hoops_AHCA _hoops_HAIR _hoops_ARCR
	//_hoops_SCSH _hoops_RCPSC = _hoops_RIS[ 8] + (_hoops_RIS[ 9] << 8);
	//_hoops_SCSH _hoops_ACPSC = _hoops_RIS[10] + (_hoops_RIS[11] << 8);
	int w = _hoops_PHGH[12] + (_hoops_PHGH[13] << 8);
	int h = _hoops_PHGH[14] + (_hoops_PHGH[15] << 8);
	int _hoops_RIGIS = w * h;
	int _hoops_GCPIR = _hoops_PHGH[16] / 8;
	int _hoops_CAGIS = _hoops_PHGH[17] & 0xF;
	//_hoops_SCSH _hoops_AIGIS = (_hoops_RIS[17] >> 4);

	if (_hoops_CAGIS == 0)
		return false;

	ASSERT (_hoops_GCPIR == 2 || _hoops_GCPIR == 4);

	src = _hoops_PHGH + 18 + _hoops_PHGH[0]; //_hoops_GGCR _hoops_RGSPR _hoops_SPCC _hoops_PPR _hoops_CSCR _hoops_CRSRR _hoops_SPCC 
	if (BIT (_hoops_IAGIS, _hoops_HRGIS)) {
		int i = 0;
		while (i < _hoops_RIGIS) {
			int _hoops_GHGIS = *src++;
			int count = 1 + (_hoops_GHGIS & 0x7F);

			if (_hoops_GHGIS & 0x80) {
				//_hoops_ARISC-_hoops_PIGAI _hoops_RHGIS
				if (src[_hoops_GCPIR - 1] != 255)
					return true;
				src += _hoops_GCPIR;
			}
			else {
				//_hoops_AGGP _hoops_RHGIS
				for (int j = 0 ; j < count ; j++) {
					if (src[_hoops_GCPIR - 1] != 255)
						return true;
					src += _hoops_GCPIR;
				}
			}
			i += count;
		}

	}
	else {
		if (_hoops_GCPIR == 2) {
			for (int j = 0 ; j < _hoops_RIGIS ; j++) {
				if (src[1] != 255)
					return true;
				src += 2;
			}
		}
		else {
			for (int j = 0 ; j < _hoops_RIGIS ; j++) {
				if (src[3] != 255)
					return true;
				src += 4;
			}
		}
	}
	return false;
#else
	return false;
#endif
}


#ifndef DISABLE_EXTENDED_TEXTURE
local Image * HI_Remap_Image (
	Net_Rendition const &		nr,
	_hoops_RCR const *				txr,
	Image const *				image) {
	_hoops_AIGH const *				_hoops_ACSHS;
	_hoops_AIGH alter *				_hoops_CSSHS;
	int							row, col;
	Image *						_hoops_IHARI = null;

	UNREFERENCED(nr);

	/* _hoops_PS _hoops_RRP _hoops_IS _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_CSCR */
	HI_Create_Image(&_hoops_IHARI,
					null,
					image->width, image->height,
					Image_RGBA32, 0,
					_hoops_RRPGI, null);

	if (!_hoops_IHARI)
		return null;

	_hoops_IHARI->flags |= image->flags;
	_hoops_IHARI->flags |= _hoops_GCRH;
	if (BIT(image->flags, _hoops_SHCC))
		HOOPS_WORLD->_hoops_ACPIR++;

	ASSERT (image->format == Image_RGBA32);
	if ((txr->_hoops_HPIR._hoops_RSRRP == _hoops_AGRRP || txr->_hoops_HPIR._hoops_RSRRP == _hoops_PGRRP) &&
		(txr->_hoops_HPIR._hoops_PSRRP == _hoops_AGRRP || txr->_hoops_HPIR._hoops_PSRRP == _hoops_IGRRP) &&
		(txr->_hoops_HPIR._hoops_ASRRP == _hoops_AGRRP || txr->_hoops_HPIR._hoops_ASRRP == _hoops_HGRRP) &&
		(txr->_hoops_HPIR._hoops_HSRRP == _hoops_AGRRP || txr->_hoops_HPIR._hoops_HSRRP == _hoops_CGRRP)) {

		for (row = 0; row < image->height; row++) {
			_hoops_CSSHS = (_hoops_AIGH *) _hoops_IHARI->rasters[row];
			_hoops_ACSHS = (_hoops_AIGH *) image->rasters[row];

			_hoops_AIGA(_hoops_ACSHS, image->width, _hoops_AIGH, _hoops_CSSHS);
		}
	}
	else {
		for (row = 0; row < image->height; row++) {
			_hoops_ACSHS = (_hoops_AIGH const*) image->rasters[row];
			_hoops_CSSHS = (_hoops_AIGH alter*) _hoops_IHARI->rasters[row];

			switch (txr->_hoops_HPIR._hoops_RSRRP) {
				case _hoops_AGRRP:
				case _hoops_PGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->r = (_hoops_ACSHS++)->r;
					}
				}	break;
				case _hoops_HGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->r = (_hoops_ACSHS++)->g;
					}
				}	break;
				case _hoops_IGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->r = (_hoops_ACSHS++)->b;
					}
				}	break;
				case _hoops_CGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->r = (_hoops_ACSHS++)->a;
					}
				}	break;
				case _hoops_SGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->r = (unsigned char) 0;
					}
				}	break;
				case _hoops_GRRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->r = (unsigned char) 255;
					}
				}	break;
				case _hoops_RRRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->r = (unsigned char)_hoops_IRASP (_hoops_ACSHS->r, _hoops_ACSHS->g, _hoops_ACSHS->b);
						_hoops_ACSHS++;
					}
				}	break;
				default: break;
			} /* _hoops_PRRAI _hoops_GPP _hoops_PRRRA _hoops_HCGP */

			_hoops_ACSHS = (_hoops_AIGH const *) image->rasters[row];
			_hoops_CSSHS = (_hoops_AIGH alter *) _hoops_IHARI->rasters[row];

			switch (txr->_hoops_HPIR._hoops_ASRRP) {
				case _hoops_AGRRP:
				case _hoops_HGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->g = (_hoops_ACSHS++)->g;
					}
				}	break;
				case _hoops_PGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->g = (_hoops_ACSHS++)->r;
					}
				}	break;
				case _hoops_IGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->g = (_hoops_ACSHS++)->b;
					}
				}	break;
				case _hoops_CGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->g = (_hoops_ACSHS++)->a;
					}
				}	break;
				case _hoops_SGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->g = (unsigned char) 0;
					}
				}	break;
				case _hoops_GRRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->g = (unsigned char) 255;
					}
				}	break;
				case _hoops_RRRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->g = (unsigned char)_hoops_IRASP (_hoops_ACSHS->r, _hoops_ACSHS->g, _hoops_ACSHS->b);
						_hoops_ACSHS++;
					}
				}	break;
				default: break;
			} /* _hoops_PRRAI _hoops_GPP _hoops_ASSAA _hoops_HCGP */

			_hoops_ACSHS = (_hoops_AIGH const *) image->rasters[row];
			_hoops_CSSHS = (_hoops_AIGH alter *) _hoops_IHARI->rasters[row];

			switch (txr->_hoops_HPIR._hoops_PSRRP) {
				case _hoops_AGRRP:
				case _hoops_IGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->b = (_hoops_ACSHS++)->b;
					}
				}	break;
				case _hoops_PGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->b = (_hoops_ACSHS++)->r;
					}
				}	break;
				case _hoops_HGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->b = (_hoops_ACSHS++)->g;
					}
				}	break;
				case _hoops_CGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->b = (_hoops_ACSHS++)->a;
					}
				}	break;
				case _hoops_SGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->b = (unsigned char) 0;
					}
				}	break;
				case _hoops_GRRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->b = (unsigned char) 255;
					}
				}	break;
				case _hoops_RRRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->b = (unsigned char)_hoops_IRASP (_hoops_ACSHS->r, _hoops_ACSHS->g, _hoops_ACSHS->b);
						_hoops_ACSHS++;
					}
				}	break;
				default: break;
			} /* _hoops_PRRAI _hoops_GPP _hoops_HRRRA _hoops_HCGP */

			_hoops_ACSHS = (_hoops_AIGH const *) image->rasters[row];
			_hoops_CSSHS = (_hoops_AIGH alter *) _hoops_IHARI->rasters[row];

			switch (txr->_hoops_HPIR._hoops_HSRRP) {
				case _hoops_AGRRP:
				case _hoops_CGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->a = (_hoops_ACSHS++)->a;
					}
				}	break;
				case _hoops_PGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->a = (_hoops_ACSHS++)->r;
					}
				}	break;
				case _hoops_HGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->a = (_hoops_ACSHS++)->g;
					}
				}	break;
				case _hoops_IGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->a = (_hoops_ACSHS++)->b;
					}
				}	break;
				case _hoops_SGRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->a = (unsigned char) 0;
					}
				}	break;
				case _hoops_GRRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->a = (unsigned char) 255;
					}
				}	break;
				case _hoops_RRRRP: {
					for (col = 0; col < image->width; col++) {
						(_hoops_CSSHS++)->a = (unsigned char)_hoops_IRASP(_hoops_ACSHS->r, _hoops_ACSHS->g, _hoops_ACSHS->b);
						_hoops_ACSHS++;
					}
				}	break;
				default: break;
			} /* _hoops_PRRAI _hoops_GPP _hoops_AIIR _hoops_HCGP */
		} /* _hoops_IH (_hoops_GRR _hoops_PPSCP _hoops_GGR _hoops_RH _hoops_CSCR) */
	}

	_hoops_IHARI->_hoops_HPIR._hoops_RSRRP = txr->_hoops_HPIR._hoops_RSRRP;
	_hoops_IHARI->_hoops_HPIR._hoops_ASRRP = txr->_hoops_HPIR._hoops_ASRRP;
	_hoops_IHARI->_hoops_HPIR._hoops_PSRRP = txr->_hoops_HPIR._hoops_PSRRP;
	_hoops_IHARI->_hoops_HPIR._hoops_HSRRP = txr->_hoops_HPIR._hoops_HSRRP;

	/* _hoops_HCGA _hoops_PIRA _hoops_CSRA _hoops_RPP _hoops_GII */
	if ((txr->_hoops_HPIR._hoops_IIRH != 0.0f || txr->_hoops_HPIR._hoops_CIRH != 1.0f)) {
		float 		_hoops_ARGCR;
		float 		_hoops_PIGIS;

		_hoops_PIGIS = txr->_hoops_HPIR._hoops_IIRH * 255.99f;
		_hoops_ARGCR = txr->_hoops_HPIR._hoops_CIRH - txr->_hoops_HPIR._hoops_IIRH;

		for (row = 0; row < image->height; row++) {
			_hoops_ACSHS = (_hoops_AIGH const *) image->rasters[row];
			_hoops_CSSHS = (_hoops_AIGH alter *) _hoops_IHARI->rasters[row];

			for (col = 0; col < image->width; col++) {
				float red;
				float green;
				float blue;
				float max;

				red = (float) _hoops_ACSHS->r * _hoops_ARGCR + _hoops_PIGIS;
				green = (float) _hoops_ACSHS->g * _hoops_ARGCR + _hoops_PIGIS;
				blue = (float) _hoops_ACSHS->b * _hoops_ARGCR + _hoops_PIGIS;
				if (red < 0.0f) red = 0.0f;
				if (green < 0.0f) green = 0.0f;
				if (blue < 0.0f) blue = 0.0f;
				max = _hoops_IAAA(_hoops_IAAA(red,green),blue);
				if (max > 255.0f) {
					/* _hoops_IPISI _hoops_RHSHS _hoops_CGPR _hoops_SAAA */
					max = 255.0f / max;
					red	  *= max;
					green *= max;
					blue  *= max;
				}
				_hoops_CSSHS->r = (unsigned char) red;
				_hoops_CSSHS->g = (unsigned char) green;
				_hoops_CSSHS->b = (unsigned char) blue;
				_hoops_CSSHS++;
				_hoops_ACSHS++;
			} /* _hoops_IH (_hoops_GRR _hoops_PSCCP) */
		} /* _hoops_IH (_hoops_GRR _hoops_GAGHR) */

		_hoops_IHARI->_hoops_HPIR._hoops_IIRH = txr->_hoops_HPIR._hoops_IIRH;
		_hoops_IHARI->_hoops_HPIR._hoops_CIRH = txr->_hoops_HPIR._hoops_CIRH;
	} /* _hoops_CGP (_hoops_PIRA _hoops_CSRA) */

	/* _hoops_HCGA _hoops_HCGGR _hoops_RPP _hoops_GII */
	if (txr->_hoops_HPIR._hoops_SIRH != 1.0f ||
		txr->_hoops_HPIR._hoops_IPIR.red != 0.0f ||
		txr->_hoops_HPIR._hoops_IPIR.green != 0.0f ||
		txr->_hoops_HPIR._hoops_IPIR.blue != 0.0f) {

		for (row = 0; row < image->height; row++) {
			_hoops_ACSHS = (_hoops_AIGH const *) image->rasters[row];
			_hoops_CSSHS = (_hoops_AIGH alter *) _hoops_IHARI->rasters[row];

			for (col = 0; col < image->width; col++) {
				float 		red;
				float 		green;
				float 		blue;
				float 		max;

				red = (float) _hoops_ACSHS->r * txr->_hoops_HPIR._hoops_SIRH + txr->_hoops_HPIR._hoops_IPIR.red;
				green = (float) _hoops_ACSHS->g * txr->_hoops_HPIR._hoops_SIRH + txr->_hoops_HPIR._hoops_IPIR.green;
				blue = (float) _hoops_ACSHS->b * txr->_hoops_HPIR._hoops_SIRH + txr->_hoops_HPIR._hoops_IPIR.blue;
				if (red < 0.0f) red = 0.0f;
				if (green < 0.0f) green = 0.0f;
				if (blue < 0.0f) blue = 0.0f;
				max = _hoops_IAAA(_hoops_IAAA(red,green),blue);
				if (max > 255.0f) {
					/* _hoops_IPISI _hoops_RHSHS _hoops_CGPR _hoops_SAAA */
					max = 255.0f / max;
					red	  *= max;
					green *= max;
					blue  *= max;
				}
				_hoops_CSSHS->r = (unsigned char) red;
				_hoops_CSSHS->g = (unsigned char) green;
				_hoops_CSSHS->b = (unsigned char) blue;
				_hoops_CSSHS++;
				_hoops_ACSHS++;
			} /* _hoops_IH (_hoops_GRR _hoops_PSCCP) */
		} /* _hoops_IH (_hoops_GRR _hoops_GAGHR) */

		_hoops_IHARI->_hoops_HPIR._hoops_SIRH = txr->_hoops_HPIR._hoops_SIRH;
		_hoops_IHARI->_hoops_HPIR._hoops_IPIR = txr->_hoops_HPIR._hoops_IPIR;
	} /* _hoops_CGP (_hoops_PIRA _hoops_CSRA) */

	_hoops_RCSHS(_hoops_IHARI);
	return _hoops_IHARI;
}
#endif


/* _hoops_HIGIS _hoops_SSRA _hoops_CRGR _hoops_APHS _hoops_SSRA _hoops_HPP _hoops_GRP _hoops_AIAA _hoops_PCIAR _hoops_IIGR _hoops_RH _hoops_PIH. */
#ifndef DISABLE_EXTENDED_TEXTURE
local Image * HI_Create_Mirror_Image (
	Image const *		image) {
	Image *				_hoops_IHARI = null;
	int					row, col;

	/* _hoops_PS _hoops_RRP _hoops_IS _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_CSCR */
	HI_Create_Image(&_hoops_IHARI,
					null,
					image->width*2, image->height*2,
					image->format, 0,
					_hoops_RRPGI, null);

	if (!_hoops_IHARI)
		return null;

	_hoops_IHARI->flags |= image->flags;
	_hoops_IHARI->flags |= _hoops_SIRRP;
	if (BIT(image->flags, _hoops_SHCC))
		HOOPS_WORLD->_hoops_ACPIR++;

	if (BIT(image->flags, _hoops_GCRH))
		_hoops_IHARI->_hoops_HPIR = image->_hoops_HPIR;


	if (image->format == Image_RGBA32)
	{
		/* _hoops_PHAA _hoops_HIGIS _hoops_RH _hoops_GSSC _hoops_RAAP _hoops_CSCR _hoops_PPR _hoops_RH _hoops_GSSC _hoops_RPHR */
		for (row = 0; row < image->height; row++) {
			_hoops_AIGH alter *		_hoops_ACSHS = (_hoops_AIGH *) image->rasters[row];
			_hoops_AIGH alter *		_hoops_CSSHS = (_hoops_AIGH *) _hoops_IHARI->rasters[row+image->height];
			_hoops_AIGH alter *		_hoops_SCSHS = _hoops_CSSHS + (image->width*2) - 1;

			for (col = 0; col < image->width; col++) {
				_hoops_SCSHS->r = _hoops_CSSHS->r = _hoops_ACSHS->r;
				_hoops_SCSHS->g = _hoops_CSSHS->g = _hoops_ACSHS->g;
				_hoops_SCSHS->b = _hoops_CSSHS->b = _hoops_ACSHS->b;
				_hoops_SCSHS->a = _hoops_CSSHS->a = _hoops_ACSHS->a;
				_hoops_SCSHS--;
				_hoops_CSSHS++;
				_hoops_ACSHS++;
			}
		}
		/* _hoops_GRHI, _hoops_HIGIS _hoops_RH _hoops_PRPC _hoops_PGCR _hoops_RRRH _hoops_IS _hoops_RH _hoops_SCIA */
		for (row = 0; row < image->height; row++) {
			_hoops_AIGH alter *		_hoops_ACSHS	= (_hoops_AIGH *) _hoops_IHARI->rasters[row+image->height];
			_hoops_AIGH alter *		_hoops_SCSHS	= (_hoops_AIGH *) _hoops_IHARI->rasters[image->height-row-1];

			_hoops_AIGA(_hoops_ACSHS, _hoops_IHARI->width, _hoops_AIGH, _hoops_SCSHS);
		}
	}
	else if (image->format == _hoops_HHGH) {
		/* _hoops_PHAA _hoops_HIGIS _hoops_RH _hoops_GSSC _hoops_RAAP _hoops_CSCR _hoops_PPR _hoops_RH _hoops_GSSC _hoops_RPHR */
		for (row = 0; row < image->height; row++) {
			_hoops_SHGH alter *		_hoops_ACSHS = (_hoops_SHGH *) image->rasters[row];
			_hoops_SHGH alter *		_hoops_CSSHS = (_hoops_SHGH *) _hoops_IHARI->rasters[row+image->height];
			_hoops_SHGH alter *		_hoops_SCSHS = _hoops_CSSHS + (image->width*2) - 1;

			for (col = 0; col < image->width; col++) {
				_hoops_SCSHS->r = _hoops_CSSHS->r = _hoops_ACSHS->r;
				_hoops_SCSHS->g = _hoops_CSSHS->g = _hoops_ACSHS->g;
				_hoops_SCSHS->b = _hoops_CSSHS->b = _hoops_ACSHS->b;
				_hoops_SCSHS--;
				_hoops_CSSHS++;
				_hoops_ACSHS++;
			}
		}
		/* _hoops_GRHI, _hoops_HIGIS _hoops_RH _hoops_PRPC _hoops_PGCR _hoops_RRRH _hoops_IS _hoops_RH _hoops_SCIA */
		for (row = 0; row < image->height; row++) {
			_hoops_SHGH alter *		_hoops_ACSHS	= (_hoops_SHGH *) _hoops_IHARI->rasters[row+image->height];
			_hoops_SHGH alter *		_hoops_SCSHS	= (_hoops_SHGH *) _hoops_IHARI->rasters[image->height-row-1];

			_hoops_AIGA(_hoops_ACSHS, _hoops_IHARI->width, _hoops_SHGH, _hoops_SCSHS);
		}
	}
	else {
		ASSERT (image->format == _hoops_AHGH);
		/* _hoops_PHAA _hoops_HIGIS _hoops_RH _hoops_GSSC _hoops_RAAP _hoops_CSCR _hoops_PPR _hoops_RH _hoops_GSSC _hoops_RPHR */
		for (row = 0; row < image->height; row++) {
			unsigned char alter *		_hoops_ACSHS = (unsigned char *) image->rasters[row];
			unsigned char alter *		_hoops_CSSHS = (unsigned char *) _hoops_IHARI->rasters[row+image->height];
			unsigned char alter *		_hoops_SCSHS = _hoops_CSSHS + (image->width*2) - 1;

			for (col = 0; col < image->width; col++) {
				*_hoops_SCSHS = *_hoops_CSSHS = *_hoops_ACSHS;
				_hoops_SCSHS--;
				_hoops_CSSHS++;
				_hoops_ACSHS++;
			}
		}
		/* _hoops_GRHI, _hoops_HIGIS _hoops_RH _hoops_PRPC _hoops_PGCR _hoops_RRRH _hoops_IS _hoops_RH _hoops_SCIA */
		for (row = 0; row < image->height; row++) {
			unsigned char alter *		_hoops_ACSHS	= (unsigned char *) _hoops_IHARI->rasters[row+image->height];
			unsigned char alter *		_hoops_SCSHS	= (unsigned char *) _hoops_IHARI->rasters[image->height-row-1];

			_hoops_AIGA(_hoops_ACSHS, _hoops_IHARI->width, unsigned char, _hoops_SCSHS);
		}
	}

	_hoops_RCSHS(_hoops_IHARI);
	return _hoops_IHARI;
}
#endif



local Image *_hoops_IIGIS(
	Image const *		image,
	int 				nh,
	int 				nw,
	Image *				_hoops_IHARI) 
{
	int					row, col;
	int					_hoops_CIGIS, _hoops_SIGIS, _hoops_GCGIS, _hoops_RCGIS;
	int					_hoops_ACGIS, _hoops_PCGIS, _hoops_HCGIS, _hoops_ICGIS;

	ASSERT (image->format == _hoops_AHGH);

	for (row = 0; row < nh; row++) {
		float		_hoops_CCGIS;

		_hoops_CCGIS = (row+0.5f)/(float)nh*(float)image->height-0.5f;
		_hoops_CIGIS = _hoops_PSCSH(_hoops_CCGIS);
		_hoops_CCGIS -= (float)_hoops_CIGIS;

		_hoops_SIGIS = _hoops_CIGIS - 1;   if (_hoops_SIGIS < 0) _hoops_SIGIS = 0;
		_hoops_GCGIS = _hoops_CIGIS + 1;   if (_hoops_GCGIS >= image->height) _hoops_GCGIS = image->height - 1;
		_hoops_RCGIS = _hoops_CIGIS + 2;   if (_hoops_RCGIS >= image->height) _hoops_RCGIS = image->height - 1;

		for (col = 0; col < nw; col++) {
			float		_hoops_SCGIS;
			/* _hoops_AIAHR _hoops_IH _hoops_GGAR */
			float		s0 = -1.0f, s1 = -1.0f, s2 = -1.0f, _hoops_CAPH = -1.0f;
			float		_hoops_CPPCP = -1.0f, _hoops_HCPSR = -1.0f, _hoops_ICPSR = -1.0f, _hoops_GSGIS = -1.0f;
			/* _hoops_GIRPA _hoops_HSH */
			float 		_hoops_RSGIS, _hoops_ASGIS, _hoops_PSGIS, _hoops_HSGIS;
			/* _hoops_GHPP */
			int			_hoops_ISGIS;
			unsigned char  *output = &((unsigned char *)_hoops_IHARI->rasters[row])[col];

			_hoops_SCGIS = (col+0.5f)/(float)nw*(float)image->width-0.5f;
			_hoops_ACGIS = _hoops_PSCSH(_hoops_SCGIS);
			_hoops_SCGIS -= (float)_hoops_ACGIS;

			_hoops_PCGIS = _hoops_ACGIS - 1;   if (_hoops_PCGIS < 0) _hoops_PCGIS = 0;
			_hoops_HCGIS = _hoops_ACGIS + 1;   if (_hoops_HCGIS >= image->width) _hoops_HCGIS = image->width - 1;
			_hoops_ICGIS = _hoops_ACGIS + 2;   if (_hoops_ICGIS >= image->width) _hoops_ICGIS = image->width - 1;

			if (_hoops_SCGIS == 0.0 && _hoops_CCGIS == 0.0) {
				/* _hoops_SAHR _hoops_IPS _hoops_AIR! */
				*output = _hoops_IISHS(_hoops_CIGIS,_hoops_ACGIS);
			}
			else {
				if (_hoops_SCGIS != 0.0) {
					s0 = ((2-_hoops_SCGIS)*_hoops_SCGIS-1)*_hoops_SCGIS;
					s1 = (3*_hoops_SCGIS-5)*_hoops_SCGIS*_hoops_SCGIS+2;
					s2 = ((4-3*_hoops_SCGIS)*_hoops_SCGIS+1)*_hoops_SCGIS;
					_hoops_CAPH = (_hoops_SCGIS-1)*_hoops_SCGIS*_hoops_SCGIS;
				}
				if (_hoops_CCGIS != 0.0) {
					_hoops_CPPCP = ((2-_hoops_CCGIS)*_hoops_CCGIS-1)*_hoops_CCGIS;
					_hoops_HCPSR = (3*_hoops_CCGIS-5)*_hoops_CCGIS*_hoops_CCGIS+2;
					_hoops_ICPSR = ((4-3*_hoops_CCGIS)*_hoops_CCGIS+1)*_hoops_CCGIS;
					_hoops_GSGIS = (_hoops_CCGIS-1)*_hoops_CCGIS*_hoops_CCGIS;
				}

				if (_hoops_CCGIS == 0.0) {
					_hoops_RSGIS	= s0 * (float)_hoops_IISHS(_hoops_CIGIS,_hoops_PCGIS) + s1 * (float)_hoops_IISHS(_hoops_CIGIS,_hoops_ACGIS) +
						  s2 * (float)_hoops_IISHS(_hoops_CIGIS,_hoops_HCGIS) + _hoops_CAPH * (float)_hoops_IISHS(_hoops_CIGIS,_hoops_ICGIS);
					_hoops_ISGIS	  = _hoops_ISCSH(0.5f * _hoops_RSGIS);
				}
				else if (_hoops_SCGIS == 0.0) {
					_hoops_RSGIS = _hoops_CPPCP * (float)_hoops_IISHS(_hoops_SIGIS,_hoops_ACGIS) + _hoops_HCPSR * (float)_hoops_IISHS(_hoops_CIGIS,_hoops_ACGIS) +
					      _hoops_ICPSR * (float)_hoops_IISHS(_hoops_GCGIS,_hoops_ACGIS) + _hoops_GSGIS * (float)_hoops_IISHS(_hoops_RCGIS,_hoops_ACGIS);
					_hoops_ISGIS = _hoops_ISCSH(0.5f * _hoops_RSGIS);
				}
				else {
					_hoops_RSGIS	  = s0 * (float)_hoops_IISHS(_hoops_SIGIS,_hoops_PCGIS) + s1 * (float)_hoops_IISHS(_hoops_SIGIS,_hoops_ACGIS) +
							s2 * (float)_hoops_IISHS(_hoops_SIGIS,_hoops_HCGIS) + _hoops_CAPH * (float)_hoops_IISHS(_hoops_SIGIS,_hoops_ICGIS);
					_hoops_ASGIS	  = s0 * (float)_hoops_IISHS(_hoops_CIGIS,_hoops_PCGIS) + s1 * (float)_hoops_IISHS(_hoops_CIGIS,_hoops_ACGIS) +
							s2 * (float)_hoops_IISHS(_hoops_CIGIS,_hoops_HCGIS) + _hoops_CAPH * (float)_hoops_IISHS(_hoops_CIGIS,_hoops_ICGIS);
					_hoops_PSGIS	  = s0 * (float)_hoops_IISHS(_hoops_GCGIS,_hoops_PCGIS) + s1 * (float)_hoops_IISHS(_hoops_GCGIS,_hoops_ACGIS) +
							s2 * (float)_hoops_IISHS(_hoops_GCGIS,_hoops_HCGIS) + _hoops_CAPH * (float)_hoops_IISHS(_hoops_GCGIS,_hoops_ICGIS);
					_hoops_HSGIS	  = s0 * (float)_hoops_IISHS(_hoops_RCGIS,_hoops_PCGIS) + s1 * (float)_hoops_IISHS(_hoops_RCGIS,_hoops_ACGIS) +
							s2 * (float)_hoops_IISHS(_hoops_RCGIS,_hoops_HCGIS) + _hoops_CAPH * (float)_hoops_IISHS(_hoops_RCGIS,_hoops_ICGIS);
					_hoops_ISGIS = _hoops_ISCSH(0.25f *	
								(_hoops_CPPCP * _hoops_RSGIS	+ _hoops_HCPSR * _hoops_ASGIS	 + _hoops_ICPSR * _hoops_PSGIS	  + _hoops_GSGIS * _hoops_HSGIS ));
				}
				*output = _hoops_HISHS (_hoops_ISGIS); 
			}
		}
	}
	return _hoops_IHARI;
}


local Image *_hoops_CSGIS(
	Image const *		image,
	int 				nh,
	int 				nw,
	Image *				_hoops_IHARI) 
{
	int					row, col;
	int					_hoops_CIGIS, _hoops_SIGIS, _hoops_GCGIS, _hoops_RCGIS;
	int					_hoops_ACGIS, _hoops_PCGIS, _hoops_HCGIS, _hoops_ICGIS;

	ASSERT (image->format == _hoops_HHGH);

	for (row = 0; row < nh; row++) {
		float		_hoops_CCGIS;

		_hoops_CCGIS = (row+0.5f)/(float)nh*(float)image->height-0.5f;
		_hoops_CIGIS = _hoops_PSCSH(_hoops_CCGIS);
		_hoops_CCGIS -= (float)_hoops_CIGIS;

		_hoops_SIGIS = _hoops_CIGIS - 1;   if (_hoops_SIGIS < 0) _hoops_SIGIS = 0;
		_hoops_GCGIS = _hoops_CIGIS + 1;   if (_hoops_GCGIS >= image->height) _hoops_GCGIS = image->height - 1;
		_hoops_RCGIS = _hoops_CIGIS + 2;   if (_hoops_RCGIS >= image->height) _hoops_RCGIS = image->height - 1;

		for (col = 0; col < nw; col++) {
			float		_hoops_SCGIS;
			/* _hoops_AIAHR _hoops_IH _hoops_GGAR */
			float		s0 = -1.0f, s1 = -1.0f, s2 = -1.0f, _hoops_CAPH = -1.0f;
			float		_hoops_CPPCP = -1.0f, _hoops_HCPSR = -1.0f, _hoops_ICPSR = -1.0f, _hoops_GSGIS = -1.0f;
			/* _hoops_GIRPA _hoops_HSH */
			RGB 		_hoops_RSGIS, _hoops_ASGIS, _hoops_PSGIS, _hoops_HSGIS;
			/* _hoops_GHPP */
			int			red, green, blue;
			_hoops_SHGH  *	output = &((_hoops_SHGH*)_hoops_IHARI->rasters[row])[col];

			_hoops_SCGIS = (col+0.5f)/(float)nw*(float)image->width-0.5f;
			_hoops_ACGIS = _hoops_PSCSH(_hoops_SCGIS);
			_hoops_SCGIS -= (float)_hoops_ACGIS;

			_hoops_PCGIS = _hoops_ACGIS - 1;   if (_hoops_PCGIS < 0) _hoops_PCGIS = 0;
			_hoops_HCGIS = _hoops_ACGIS + 1;   if (_hoops_HCGIS >= image->width) _hoops_HCGIS = image->width - 1;
			_hoops_ICGIS = _hoops_ACGIS + 2;   if (_hoops_ICGIS >= image->width) _hoops_ICGIS = image->width - 1;

			if (_hoops_SCGIS == 0.0 && _hoops_CCGIS == 0.0) {
				/* _hoops_SAHR _hoops_IPS _hoops_AIR! */
				*output = _hoops_CISHS(_hoops_CIGIS,_hoops_ACGIS);
			}
			else {
				if (_hoops_SCGIS != 0.0) {
					s0 = ((2-_hoops_SCGIS)*_hoops_SCGIS-1)*_hoops_SCGIS;
					s1 = (3*_hoops_SCGIS-5)*_hoops_SCGIS*_hoops_SCGIS+2;
					s2 = ((4-3*_hoops_SCGIS)*_hoops_SCGIS+1)*_hoops_SCGIS;
					_hoops_CAPH = (_hoops_SCGIS-1)*_hoops_SCGIS*_hoops_SCGIS;
				}
				if (_hoops_CCGIS != 0.0) {
					_hoops_CPPCP = ((2-_hoops_CCGIS)*_hoops_CCGIS-1)*_hoops_CCGIS;
					_hoops_HCPSR = (3*_hoops_CCGIS-5)*_hoops_CCGIS*_hoops_CCGIS+2;
					_hoops_ICPSR = ((4-3*_hoops_CCGIS)*_hoops_CCGIS+1)*_hoops_CCGIS;
					_hoops_GSGIS = (_hoops_CCGIS-1)*_hoops_CCGIS*_hoops_CCGIS;
				}

				if (_hoops_CCGIS == 0.0) {
					_hoops_RSGIS.red	  = s0 * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_PCGIS).r + s1 * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_ACGIS).r +
								s2 * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_HCGIS).r + _hoops_CAPH * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_ICGIS).r;
					_hoops_RSGIS.green = s0 * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_PCGIS).g + s1 * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_ACGIS).g +
								s2 * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_HCGIS).g + _hoops_CAPH * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_ICGIS).g;
					_hoops_RSGIS.blue  = s0 * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_PCGIS).b + s1 * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_ACGIS).b +
								s2 * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_HCGIS).b + _hoops_CAPH * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_ICGIS).b;

					red	  = _hoops_ISCSH(0.5f * _hoops_RSGIS.red	);
					green = _hoops_ISCSH(0.5f * _hoops_RSGIS.green);
					blue  = _hoops_ISCSH(0.5f * _hoops_RSGIS.blue	);
				}
				else if (_hoops_SCGIS == 0.0) {
					_hoops_RSGIS.red	  = _hoops_CPPCP * (float)_hoops_CISHS(_hoops_SIGIS,_hoops_ACGIS).r + _hoops_HCPSR * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_ACGIS).r +
								_hoops_ICPSR * (float)_hoops_CISHS(_hoops_GCGIS,_hoops_ACGIS).r + _hoops_GSGIS * (float)_hoops_CISHS(_hoops_RCGIS,_hoops_ACGIS).r;
					_hoops_RSGIS.green = _hoops_CPPCP * (float)_hoops_CISHS(_hoops_SIGIS,_hoops_ACGIS).g + _hoops_HCPSR * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_ACGIS).g +
								_hoops_ICPSR * (float)_hoops_CISHS(_hoops_GCGIS,_hoops_ACGIS).g + _hoops_GSGIS * (float)_hoops_CISHS(_hoops_RCGIS,_hoops_ACGIS).g;
					_hoops_RSGIS.blue  = _hoops_CPPCP * (float)_hoops_CISHS(_hoops_SIGIS,_hoops_ACGIS).b + _hoops_HCPSR * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_ACGIS).b +
								_hoops_ICPSR * (float)_hoops_CISHS(_hoops_GCGIS,_hoops_ACGIS).b + _hoops_GSGIS * (float)_hoops_CISHS(_hoops_RCGIS,_hoops_ACGIS).b;

					red	  = _hoops_ISCSH(0.5f * _hoops_RSGIS.red	);
					green = _hoops_ISCSH(0.5f * _hoops_RSGIS.green);
					blue  = _hoops_ISCSH(0.5f * _hoops_RSGIS.blue	);
				}
				else {
					_hoops_RSGIS.red	  = s0 * (float)_hoops_CISHS(_hoops_SIGIS,_hoops_PCGIS).r + s1 * (float)_hoops_CISHS(_hoops_SIGIS,_hoops_ACGIS).r +
								s2 * (float)_hoops_CISHS(_hoops_SIGIS,_hoops_HCGIS).r + _hoops_CAPH * (float)_hoops_CISHS(_hoops_SIGIS,_hoops_ICGIS).r;
					_hoops_RSGIS.green = s0 * (float)_hoops_CISHS(_hoops_SIGIS,_hoops_PCGIS).g + s1 * (float)_hoops_CISHS(_hoops_SIGIS,_hoops_ACGIS).g +
								s2 * (float)_hoops_CISHS(_hoops_SIGIS,_hoops_HCGIS).g + _hoops_CAPH * (float)_hoops_CISHS(_hoops_SIGIS,_hoops_ICGIS).g;
					_hoops_RSGIS.blue  = s0 * (float)_hoops_CISHS(_hoops_SIGIS,_hoops_PCGIS).b + s1 * (float)_hoops_CISHS(_hoops_SIGIS,_hoops_ACGIS).b +
								s2 * (float)_hoops_CISHS(_hoops_SIGIS,_hoops_HCGIS).b + _hoops_CAPH * (float)_hoops_CISHS(_hoops_SIGIS,_hoops_ICGIS).b;
					_hoops_ASGIS.red	  = s0 * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_PCGIS).r + s1 * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_ACGIS).r +
								s2 * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_HCGIS).r + _hoops_CAPH * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_ICGIS).r;
					_hoops_ASGIS.green = s0 * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_PCGIS).g + s1 * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_ACGIS).g +
								s2 * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_HCGIS).g + _hoops_CAPH * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_ICGIS).g;
					_hoops_ASGIS.blue  = s0 * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_PCGIS).b + s1 * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_ACGIS).b +
								s2 * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_HCGIS).b + _hoops_CAPH * (float)_hoops_CISHS(_hoops_CIGIS,_hoops_ICGIS).b;
					_hoops_PSGIS.red	  = s0 * (float)_hoops_CISHS(_hoops_GCGIS,_hoops_PCGIS).r + s1 * (float)_hoops_CISHS(_hoops_GCGIS,_hoops_ACGIS).r +
								s2 * (float)_hoops_CISHS(_hoops_GCGIS,_hoops_HCGIS).r + _hoops_CAPH * (float)_hoops_CISHS(_hoops_GCGIS,_hoops_ICGIS).r;
					_hoops_PSGIS.green = s0 * (float)_hoops_CISHS(_hoops_GCGIS,_hoops_PCGIS).g + s1 * (float)_hoops_CISHS(_hoops_GCGIS,_hoops_ACGIS).g +
								s2 * (float)_hoops_CISHS(_hoops_GCGIS,_hoops_HCGIS).g + _hoops_CAPH * (float)_hoops_CISHS(_hoops_GCGIS,_hoops_ICGIS).g;
					_hoops_PSGIS.blue  = s0 * (float)_hoops_CISHS(_hoops_GCGIS,_hoops_PCGIS).b + s1 * (float)_hoops_CISHS(_hoops_GCGIS,_hoops_ACGIS).b +
								s2 * (float)_hoops_CISHS(_hoops_GCGIS,_hoops_HCGIS).b + _hoops_CAPH * (float)_hoops_CISHS(_hoops_GCGIS,_hoops_ICGIS).b;
					_hoops_HSGIS.red	  = s0 * (float)_hoops_CISHS(_hoops_RCGIS,_hoops_PCGIS).r + s1 * (float)_hoops_CISHS(_hoops_RCGIS,_hoops_ACGIS).r +
								s2 * (float)_hoops_CISHS(_hoops_RCGIS,_hoops_HCGIS).r + _hoops_CAPH * (float)_hoops_CISHS(_hoops_RCGIS,_hoops_ICGIS).r;
					_hoops_HSGIS.green = s0 * (float)_hoops_CISHS(_hoops_RCGIS,_hoops_PCGIS).g + s1 * (float)_hoops_CISHS(_hoops_RCGIS,_hoops_ACGIS).g +
								s2 * (float)_hoops_CISHS(_hoops_RCGIS,_hoops_HCGIS).g + _hoops_CAPH * (float)_hoops_CISHS(_hoops_RCGIS,_hoops_ICGIS).g;
					_hoops_HSGIS.blue  = s0 * (float)_hoops_CISHS(_hoops_RCGIS,_hoops_PCGIS).b + s1 * (float)_hoops_CISHS(_hoops_RCGIS,_hoops_ACGIS).b +
								s2 * (float)_hoops_CISHS(_hoops_RCGIS,_hoops_HCGIS).b + _hoops_CAPH * (float)_hoops_CISHS(_hoops_RCGIS,_hoops_ICGIS).b;

					red	  = _hoops_ISCSH(0.25f *
								(_hoops_CPPCP * _hoops_RSGIS.red	+ _hoops_HCPSR * _hoops_ASGIS.red	 + _hoops_ICPSR * _hoops_PSGIS.red	  + _hoops_GSGIS * _hoops_HSGIS.red ));
					green = _hoops_ISCSH(0.25f *
								(_hoops_CPPCP * _hoops_RSGIS.green + _hoops_HCPSR * _hoops_ASGIS.green + _hoops_ICPSR * _hoops_PSGIS.green + _hoops_GSGIS * _hoops_HSGIS.green));
					blue  = _hoops_ISCSH(0.25f *
								(_hoops_CPPCP * _hoops_RSGIS.blue	+ _hoops_HCPSR * _hoops_ASGIS.blue	 + _hoops_ICPSR * _hoops_PSGIS.blue  + _hoops_GSGIS * _hoops_HSGIS.blue));
				}

				output->r = _hoops_HISHS (red);
				output->g = _hoops_HISHS (green);
				output->b = _hoops_HISHS (blue);
			}
		}
	}
	return _hoops_IHARI;
}


local Image *_hoops_SSGIS(
	Image const *		image,
	int 				nh,
	int 				nw,
	Image *				_hoops_IHARI) {
	int					row, col;
	int					_hoops_CIGIS, _hoops_SIGIS, _hoops_GCGIS, _hoops_RCGIS;
	int					_hoops_ACGIS, _hoops_PCGIS, _hoops_HCGIS, _hoops_ICGIS;
	int					_hoops_GGRIS = -1;

	ASSERT (image->format == Image_RGBA32);

	for (row = 0; row < nh; row++) {
		float		_hoops_CCGIS;

		_hoops_CCGIS = (row+0.5f)/(float)nh*(float)image->height-0.5f;
		_hoops_CIGIS = _hoops_PSCSH(_hoops_CCGIS);
		_hoops_CCGIS -= (float)_hoops_CIGIS;

		_hoops_SIGIS = _hoops_CIGIS - 1;   if (_hoops_SIGIS < 0) _hoops_SIGIS = 0;
		_hoops_GCGIS = _hoops_CIGIS + 1;   if (_hoops_GCGIS >= image->height) _hoops_GCGIS = image->height - 1;
		_hoops_RCGIS = _hoops_CIGIS + 2;   if (_hoops_RCGIS >= image->height) _hoops_RCGIS = image->height - 1;

		for (col = 0; col < nw; col++) {
			float		_hoops_SCGIS;
			/* _hoops_AIAHR _hoops_IH _hoops_GGAR */
			float		s0 = -1.0f, s1 = -1.0f, s2 = -1.0f, _hoops_CAPH = -1.0f;
			float		_hoops_CPPCP = -1.0f, _hoops_HCPSR = -1.0f, _hoops_ICPSR = -1.0f, _hoops_GSGIS = -1.0f;
			/* _hoops_GIRPA _hoops_HSH */
			RGBA		_hoops_RSGIS, _hoops_ASGIS, _hoops_PSGIS, _hoops_HSGIS;
			/* _hoops_GHPP */
			int			red, green, blue, alpha;
			_hoops_AIGH *	output = &((_hoops_AIGH*)_hoops_IHARI->rasters[row])[col];

			_hoops_SCGIS = (col+0.5f)/(float)nw*(float)image->width-0.5f;
			_hoops_ACGIS = _hoops_PSCSH(_hoops_SCGIS);
			_hoops_SCGIS -= (float)_hoops_ACGIS;

			_hoops_PCGIS = _hoops_ACGIS - 1;   if (_hoops_PCGIS < 0) _hoops_PCGIS = 0;
			_hoops_HCGIS = _hoops_ACGIS + 1;   if (_hoops_HCGIS >= image->width) _hoops_HCGIS = image->width - 1;
			_hoops_ICGIS = _hoops_ACGIS + 2;   if (_hoops_ICGIS >= image->width) _hoops_ICGIS = image->width - 1;

			if (_hoops_SCGIS == 0.0 && _hoops_CCGIS == 0.0) {
				/* _hoops_SAHR _hoops_IPS _hoops_AIR! */
				*output = _hoops_SISHS(_hoops_CIGIS,_hoops_ACGIS);
			}
			else {
				if (_hoops_SCGIS != 0.0) {
					s0 = ((2-_hoops_SCGIS)*_hoops_SCGIS-1)*_hoops_SCGIS;
					s1 = (3*_hoops_SCGIS-5)*_hoops_SCGIS*_hoops_SCGIS+2;
					s2 = ((4-3*_hoops_SCGIS)*_hoops_SCGIS+1)*_hoops_SCGIS;
					_hoops_CAPH = (_hoops_SCGIS-1)*_hoops_SCGIS*_hoops_SCGIS;
				}
				if (_hoops_CCGIS != 0.0) {
					_hoops_CPPCP = ((2-_hoops_CCGIS)*_hoops_CCGIS-1)*_hoops_CCGIS;
					_hoops_HCPSR = (3*_hoops_CCGIS-5)*_hoops_CCGIS*_hoops_CCGIS+2;
					_hoops_ICPSR = ((4-3*_hoops_CCGIS)*_hoops_CCGIS+1)*_hoops_CCGIS;
					_hoops_GSGIS = (_hoops_CCGIS-1)*_hoops_CCGIS*_hoops_CCGIS;
				}

				if (_hoops_CCGIS == 0.0) {
					_hoops_RSGIS.red	  = s0 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_PCGIS).r + s1 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ACGIS).r +
								s2 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_HCGIS).r + _hoops_CAPH * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ICGIS).r;
					_hoops_RSGIS.green = s0 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_PCGIS).g + s1 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ACGIS).g +
								s2 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_HCGIS).g + _hoops_CAPH * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ICGIS).g;
					_hoops_RSGIS.blue  = s0 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_PCGIS).b + s1 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ACGIS).b +
								s2 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_HCGIS).b + _hoops_CAPH * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ICGIS).b;
					_hoops_RSGIS.alpha = s0 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_PCGIS).a + s1 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ACGIS).a +
								s2 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_HCGIS).a + _hoops_CAPH * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ICGIS).a;

					red	  = _hoops_ISCSH(0.5f * _hoops_RSGIS.red	);
					green = _hoops_ISCSH(0.5f * _hoops_RSGIS.green);
					blue  = _hoops_ISCSH(0.5f * _hoops_RSGIS.blue	);
					alpha = _hoops_ISCSH(0.5f * _hoops_RSGIS.alpha);
				}
				else if (_hoops_SCGIS == 0.0) {
					_hoops_RSGIS.red	  = _hoops_CPPCP * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_ACGIS).r + _hoops_HCPSR * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ACGIS).r +
								_hoops_ICPSR * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_ACGIS).r + _hoops_GSGIS * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_ACGIS).r;
					_hoops_RSGIS.green = _hoops_CPPCP * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_ACGIS).g + _hoops_HCPSR * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ACGIS).g +
								_hoops_ICPSR * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_ACGIS).g + _hoops_GSGIS * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_ACGIS).g;
					_hoops_RSGIS.blue  = _hoops_CPPCP * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_ACGIS).b + _hoops_HCPSR * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ACGIS).b +
								_hoops_ICPSR * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_ACGIS).b + _hoops_GSGIS * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_ACGIS).b;
					_hoops_RSGIS.alpha = _hoops_CPPCP * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_ACGIS).a + _hoops_HCPSR * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ACGIS).a +
								_hoops_ICPSR * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_ACGIS).a + _hoops_GSGIS * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_ACGIS).a;

					red	  = _hoops_ISCSH(0.5f * _hoops_RSGIS.red	);
					green = _hoops_ISCSH(0.5f * _hoops_RSGIS.green);
					blue  = _hoops_ISCSH(0.5f * _hoops_RSGIS.blue	);
					alpha = _hoops_ISCSH(0.5f * _hoops_RSGIS.alpha);
				}
				else {
					_hoops_RSGIS.red	  = s0 * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_PCGIS).r + s1 * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_ACGIS).r +
								s2 * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_HCGIS).r + _hoops_CAPH * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_ICGIS).r;
					_hoops_RSGIS.green = s0 * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_PCGIS).g + s1 * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_ACGIS).g +
								s2 * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_HCGIS).g + _hoops_CAPH * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_ICGIS).g;
					_hoops_RSGIS.blue  = s0 * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_PCGIS).b + s1 * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_ACGIS).b +
								s2 * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_HCGIS).b + _hoops_CAPH * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_ICGIS).b;
					_hoops_RSGIS.alpha = s0 * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_PCGIS).a + s1 * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_ACGIS).a +
								s2 * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_HCGIS).a + _hoops_CAPH * (float)_hoops_SISHS(_hoops_SIGIS,_hoops_ICGIS).a;
					_hoops_ASGIS.red	  = s0 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_PCGIS).r + s1 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ACGIS).r +
								s2 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_HCGIS).r + _hoops_CAPH * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ICGIS).r;
					_hoops_ASGIS.green = s0 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_PCGIS).g + s1 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ACGIS).g +
								s2 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_HCGIS).g + _hoops_CAPH * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ICGIS).g;
					_hoops_ASGIS.blue  = s0 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_PCGIS).b + s1 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ACGIS).b +
								s2 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_HCGIS).b + _hoops_CAPH * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ICGIS).b;
					_hoops_ASGIS.alpha = s0 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_PCGIS).a + s1 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ACGIS).a +
								s2 * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_HCGIS).a + _hoops_CAPH * (float)_hoops_SISHS(_hoops_CIGIS,_hoops_ICGIS).a;
					_hoops_PSGIS.red	  = s0 * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_PCGIS).r + s1 * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_ACGIS).r +
								s2 * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_HCGIS).r + _hoops_CAPH * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_ICGIS).r;
					_hoops_PSGIS.green = s0 * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_PCGIS).g + s1 * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_ACGIS).g +
								s2 * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_HCGIS).g + _hoops_CAPH * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_ICGIS).g;
					_hoops_PSGIS.blue  = s0 * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_PCGIS).b + s1 * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_ACGIS).b +
								s2 * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_HCGIS).b + _hoops_CAPH * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_ICGIS).b;
					_hoops_PSGIS.alpha = s0 * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_PCGIS).a + s1 * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_ACGIS).a +
								s2 * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_HCGIS).a + _hoops_CAPH * (float)_hoops_SISHS(_hoops_GCGIS,_hoops_ICGIS).a;
					_hoops_HSGIS.red	  = s0 * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_PCGIS).r + s1 * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_ACGIS).r +
								s2 * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_HCGIS).r + _hoops_CAPH * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_ICGIS).r;
					_hoops_HSGIS.green = s0 * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_PCGIS).g + s1 * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_ACGIS).g +
								s2 * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_HCGIS).g + _hoops_CAPH * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_ICGIS).g;
					_hoops_HSGIS.blue  = s0 * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_PCGIS).b + s1 * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_ACGIS).b +
								s2 * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_HCGIS).b + _hoops_CAPH * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_ICGIS).b;
					_hoops_HSGIS.alpha = s0 * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_PCGIS).a + s1 * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_ACGIS).a +
								s2 * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_HCGIS).a + _hoops_CAPH * (float)_hoops_SISHS(_hoops_RCGIS,_hoops_ICGIS).a;

					red	  = _hoops_ISCSH(0.25f *
								(_hoops_CPPCP * _hoops_RSGIS.red	+ _hoops_HCPSR * _hoops_ASGIS.red	 + _hoops_ICPSR * _hoops_PSGIS.red	  + _hoops_GSGIS * _hoops_HSGIS.red ));
					green = _hoops_ISCSH(0.25f *
								(_hoops_CPPCP * _hoops_RSGIS.green + _hoops_HCPSR * _hoops_ASGIS.green + _hoops_ICPSR * _hoops_PSGIS.green + _hoops_GSGIS * _hoops_HSGIS.green));
					blue  = _hoops_ISCSH(0.25f *
								(_hoops_CPPCP * _hoops_RSGIS.blue	+ _hoops_HCPSR * _hoops_ASGIS.blue	 + _hoops_ICPSR * _hoops_PSGIS.blue  + _hoops_GSGIS * _hoops_HSGIS.blue));
					alpha = _hoops_ISCSH(0.25f *
								(_hoops_CPPCP * _hoops_RSGIS.alpha + _hoops_HCPSR * _hoops_ASGIS.alpha + _hoops_ICPSR * _hoops_PSGIS.alpha + _hoops_GSGIS * _hoops_HSGIS.alpha));
				}

				output->r = _hoops_HISHS (red);
				output->g = _hoops_HISHS (green);
				output->b = _hoops_HISHS (blue);
				output->a = _hoops_HISHS (alpha);

				if (_hoops_GGRIS) {
					_hoops_AIGH		border = _hoops_SISHS(_hoops_CIGIS, _hoops_ACGIS);

					/* _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_GPP _hoops_RH _hoops_HGPC */
					if (row == 0)
						border = _hoops_SISHS(0, _hoops_ACGIS);
					else if (col == 0)
						border = _hoops_SISHS(_hoops_CIGIS, col);
					else if (row == nh-1)
						border = _hoops_SISHS(	image->height -1, _hoops_ACGIS);
					else if (col == nw-1)
						border = _hoops_SISHS(_hoops_CIGIS, image->width -1);
					else
						continue; /* _hoops_HAR _hoops_GPP _hoops_RH _hoops_HGPC, _hoops_HIS _hoops_SAS _hoops_GPP _hoops_IS _hoops_RH _hoops_SPS _hoops_AIR */

					/* _hoops_RPP _hoops_RH _hoops_GIGR _hoops_HGPC _hoops_RIAGR _hoops_AHHR _hoops_AIIR _hoops_PIRA, _hoops_SGH _hoops_SGS _hoops_GPP _hoops_RH _hoops_CCAH _hoops_HGPC.
					   _hoops_RPP _hoops_RH _hoops_RGRIS _hoops_RHAP _hoops_HAR _hoops_HS _hoops_PCCP _hoops_AIIR _hoops_HGPC, _hoops_SR _hoops_PAH _hoops_HSGR _hoops_HCR _hoops_IIGR _hoops_RGR
					   _hoops_IPAC _hoops_IH _hoops_RH _hoops_ACSP _hoops_IIGR _hoops_RH _hoops_CSCR */
					if (border.a == 0)
						output->a = 0;
					else
						_hoops_GGRIS = 0;
				}
			}
		}
	}
	return _hoops_IHARI;
}

local Image * HI_Create_Bicubic_Scaled_Image (
	Image const *		image,
	int 				nh,
	int 				nw,
	Image *				_hoops_IHARI) 
{
	if (image->format == Image_RGBA32)
		return _hoops_SSGIS (image, nh, nw, _hoops_IHARI);
	else if (image->format == _hoops_HHGH)
		return _hoops_CSGIS (image, nh, nw, _hoops_IHARI);
	else if (image->format == _hoops_AHGH)
		return _hoops_IIGIS (image, nh, nw, _hoops_IHARI);
	return null;
}

/**
 * _hoops_AGRIS _hoops_CSCR _hoops_CRGR _hoops_AGGIS _hoops_IIGR _hoops_IGIR _hoops_PGRIS, _hoops_HGRIS _hoops_GRP _hoops_IRS _hoops_AHCRR _hoops_RGRR.
 *
 * _hoops_IGRIS:
 * - _hoops_CSCR _hoops_PPR _hoops_AGGIS _hoops_CHR
 * - _hoops_CSCR->_hoops_IGAA, _hoops_CSCR->_hoops_APPS _hoops_CHR _hoops_CGRIS
 * - _hoops_HGRIS, _hoops_PGRIS _hoops_CHR _hoops_CGRIS, _hoops_PPR _hoops_CRGP _hoops_HSAR _hoops_CSCR->_hoops_IGAA, _hoops_CSCR->_hoops_APPS
 */
local Image * _hoops_SGRIS (
	Image const *		image,
	int 				nh,
	int 				nw,
	Image *				_hoops_IHARI) {
	int					row, col;
	int					_hoops_CIGIS, _hoops_ACGIS;
	int					_hoops_GGRIS = -1;

	ASSERT(image->format == Image_RGBA32);

	// _hoops_PGRIS _hoops_GAISH _hoops_CSCR->_hoops_IGAA _hoops_CR _hoops_GIPR _hoops_CHR _hoops_RIIR _hoops_IIGR 2 (_hoops_PSHR _hoops_IH _hoops_HGRIS)
	int _hoops_PIIH = image->width / nw;
	int _hoops_HIIH = image->height / nh;
	int _hoops_GRRIS = _hoops_PIIH * _hoops_HIIH;

	for (row = 0; row < nh; row++) {

		for (col = 0; col < nw; col++) {
			int			i, j;
			_hoops_AIGH *	output = &((_hoops_AIGH*)_hoops_IHARI->rasters[row])[col];
			int			_hoops_RRRIS = 0;
			int			_hoops_ARRIS = 0;
			int			_hoops_PRRIS = 0;
			int			_hoops_HRRIS = 0;

			/* _hoops_PSPHS _hoops_HCGP _hoops_RIS _hoops_ASPA _hoops_RSHCR _hoops_IS _hoops_SISH _hoops_AIR. */
			for (i = 0; i < _hoops_HIIH; i++) {
				for (j = 0; j < _hoops_PIIH; j++) {
					_hoops_CIGIS = _hoops_HIIH*row + i;
					_hoops_ACGIS = _hoops_PIIH*col + j;

					_hoops_AIGH p = _hoops_SISHS(_hoops_CIGIS, _hoops_ACGIS);
					_hoops_RRRIS += p.r;
					_hoops_ARRIS += p.g;
					_hoops_PRRIS += p.b;
					_hoops_HRRIS += p.a;
				}
			}

			output->r = _hoops_HISHS ((float)_hoops_RRRIS/_hoops_GRRIS);
			output->g = _hoops_HISHS ((float)_hoops_ARRIS/_hoops_GRRIS);
			output->b = _hoops_HISHS ((float)_hoops_PRRIS/_hoops_GRRIS);
			output->a = _hoops_HISHS ((float)_hoops_HRRIS/_hoops_GRRIS);

			if (_hoops_GGRIS) {
				_hoops_CIGIS = _hoops_HIIH*row;
				_hoops_ACGIS = _hoops_PIIH*col;

				_hoops_AIGH		border = _hoops_SISHS(_hoops_CIGIS, _hoops_ACGIS);

				/* _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_GPP _hoops_RH _hoops_HGPC */
				if (row == 0)
					border = _hoops_SISHS(0, _hoops_ACGIS);
				else if (col == 0)
					border = _hoops_SISHS(_hoops_CIGIS, col);
				else if (row == nh-1)
					border = _hoops_SISHS(	image->height -1, _hoops_ACGIS);
				else if (col == nw-1)
					border = _hoops_SISHS(_hoops_CIGIS, image->width -1);
				else
					continue; /* _hoops_HAR _hoops_GPP _hoops_RH _hoops_HGPC, _hoops_HIS _hoops_SAS _hoops_GPP _hoops_IS _hoops_RH _hoops_SPS _hoops_AIR */

				/* _hoops_RPP _hoops_RH _hoops_GIGR _hoops_HGPC _hoops_RIAGR _hoops_AHHR _hoops_AIIR _hoops_PIRA, _hoops_SGH _hoops_SGS _hoops_GPP _hoops_RH _hoops_CCAH _hoops_HGPC.
				   _hoops_RPP _hoops_RH _hoops_RGRIS _hoops_RHAP _hoops_HAR _hoops_HS _hoops_PCCP _hoops_AIIR _hoops_HGPC, _hoops_SR _hoops_PAH _hoops_HSGR _hoops_HCR _hoops_IIGR _hoops_RGR
				   _hoops_IPAC _hoops_IH _hoops_RH _hoops_ACSP _hoops_IIGR _hoops_RH _hoops_CSCR */
				if (border.a == 0)
					output->a = 0;
				else
					_hoops_GGRIS = 0;
			}
		}
	}
	return _hoops_IHARI;
}


local Image * _hoops_IRRIS (
	Image const *		image,
	int 				nh,
	int 				nw,
	Image *				_hoops_IHARI) {
	int					row, col;
	int					_hoops_CIGIS, _hoops_ACGIS;

	ASSERT(image->format == _hoops_HHGH);

	// _hoops_PGRIS _hoops_GAISH _hoops_CSCR->_hoops_IGAA _hoops_CR _hoops_GIPR _hoops_CHR _hoops_RIIR _hoops_IIGR 2 (_hoops_PSHR _hoops_IH _hoops_HGRIS)
	int _hoops_PIIH = image->width / nw;
	int _hoops_HIIH = image->height / nh;
	int _hoops_GRRIS = _hoops_PIIH * _hoops_HIIH;

	for (row = 0; row < nh; row++) {

		for (col = 0; col < nw; col++) {
			int			i, j;
			_hoops_SHGH *	output = &((_hoops_SHGH*)_hoops_IHARI->rasters[row])[col];
			int			_hoops_RRRIS = 0;
			int			_hoops_ARRIS = 0;
			int			_hoops_PRRIS = 0;

			/* _hoops_PSPHS _hoops_HCGP _hoops_RIS _hoops_ASPA _hoops_RSHCR _hoops_IS _hoops_SISH _hoops_AIR. */
			for (i = 0; i < _hoops_HIIH; i++) {
				for (j = 0; j < _hoops_PIIH; j++) {
					_hoops_CIGIS = _hoops_HIIH*row + i;
					_hoops_ACGIS = _hoops_PIIH*col + j;

					_hoops_SHGH p = _hoops_CISHS(_hoops_CIGIS, _hoops_ACGIS);
					_hoops_RRRIS += p.r;
					_hoops_ARRIS += p.g;
					_hoops_PRRIS += p.b;
				}
			}

			output->r = _hoops_HISHS ((float)_hoops_RRRIS/_hoops_GRRIS);
			output->g = _hoops_HISHS ((float)_hoops_ARRIS/_hoops_GRRIS);
			output->b = _hoops_HISHS ((float)_hoops_PRRIS/_hoops_GRRIS);
		}
	}
	return _hoops_IHARI;
}


local Image * _hoops_CRRIS (
	Image const *		image,
	int 				nh,
	int 				nw,
	Image *				_hoops_IHARI) {
	int					row, col;
	int					_hoops_CIGIS, _hoops_ACGIS;

	ASSERT(image->format == _hoops_AHGH);

	// _hoops_PGRIS _hoops_GAISH _hoops_CSCR->_hoops_IGAA _hoops_CR _hoops_GIPR _hoops_CHR _hoops_RIIR _hoops_IIGR 2 (_hoops_PSHR _hoops_IH _hoops_HGRIS)
	int _hoops_PIIH = image->width / nw;
	int _hoops_HIIH = image->height / nh;
	int _hoops_GRRIS = _hoops_PIIH * _hoops_HIIH;

	for (row = 0; row < nh; row++) {

		for (col = 0; col < nw; col++) {
			int			i, j;
			unsigned char *	output = &((unsigned char*)_hoops_IHARI->rasters[row])[col];
			int			_hoops_ARAHR = 0;

			/* _hoops_PSPHS _hoops_HCGP _hoops_RIS _hoops_ASPA _hoops_RSHCR _hoops_IS _hoops_SISH _hoops_AIR. */
			for (i = 0; i < _hoops_HIIH; i++) {
				for (j = 0; j < _hoops_PIIH; j++) {
					_hoops_CIGIS = _hoops_HIIH*row + i;
					_hoops_ACGIS = _hoops_PIIH*col + j;

					_hoops_ARAHR += _hoops_IISHS(_hoops_CIGIS, _hoops_ACGIS);
				}
			}

			*output = _hoops_HISHS ((float)_hoops_ARAHR/_hoops_GRRIS);
		}
	}
	return _hoops_IHARI;
}


local Image * HI_Create_Box_Downsampled_Image (
	Image const *		image,
	int 				nh,
	int 				nw,
	Image *				_hoops_IHARI) {

	if (image->format == Image_RGBA32)
		return _hoops_SGRIS (image, nh, nw, _hoops_IHARI);
	else if (image->format == _hoops_HHGH)
		return _hoops_IRRIS (image, nh, nw, _hoops_IHARI);
	else if (image->format == _hoops_AHGH)
		return _hoops_CRRIS (image, nh, nw, _hoops_IHARI);
	return null;
}




local void HI_Create_Scaled_Image_Copy (
	Image **				_hoops_IHARI,
	const Image *			_hoops_SRRIS,
	int						h,
	int						w) {

	HI_Create_Image(_hoops_IHARI,
					null,
					w, h,
					_hoops_SRRIS->format, 0,
					_hoops_RRPGI, null);

	if (!*_hoops_IHARI)
		return;

	(*_hoops_IHARI)->flags |= _hoops_SRRIS->flags;
	if (BIT(_hoops_SRRIS->flags, _hoops_SHCC))
		HOOPS_WORLD->_hoops_ACPIR++;

	if (BIT(_hoops_SRRIS->flags, _hoops_GCRH))
		(*_hoops_IHARI)->_hoops_HPIR = _hoops_SRRIS->_hoops_HPIR;
}

#define _hoops_GARIS	1
#define _hoops_RARIS	2

local Image * HI_Create_Scaled_Image (
	Image const *		image,
	int 				nh,
	int 				nw,
	int 				_hoops_RCCRR) {
	int					row, col;
	Image *				_hoops_IHARI = null;
	int					_hoops_CIGIS;
	int					_hoops_ACGIS;

	/* _hoops_PS _hoops_RRP _hoops_IS _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_CSCR */
	HI_Create_Scaled_Image_Copy(&_hoops_IHARI, image, nh, nw);

	if (!_hoops_IHARI)
		return null;

	if (_hoops_RCCRR == _hoops_GARIS) {
		float		_hoops_PIIH, _hoops_HIIH;

		_hoops_PIIH = (float)image->width/(float)nw;
		_hoops_HIIH = (float)image->height/(float)nh;

		if (image->format == Image_RGBA32) {
			_hoops_AIGH *_hoops_ACSHS, *_hoops_CSSHS;
			for (row = 0; row < nh; row++) {
				_hoops_CIGIS = _hoops_PSCSH((float)row*_hoops_HIIH);
				_hoops_ACSHS = (_hoops_AIGH*)image->rasters[_hoops_CIGIS];
				_hoops_CSSHS = (_hoops_AIGH*)_hoops_IHARI->rasters[row];

				for (col = 0; col < nw; col++) {
					_hoops_ACGIS = _hoops_PSCSH((float)col*_hoops_PIIH);
					_hoops_CSSHS[col] = _hoops_ACSHS[_hoops_ACGIS];
				}
			}
		}
		else if (image->format == _hoops_HHGH) {
			_hoops_SHGH *_hoops_ACSHS, *_hoops_CSSHS;
			for (row = 0; row < nh; row++) {
				_hoops_CIGIS = _hoops_PSCSH((float)row*_hoops_HIIH);
				_hoops_ACSHS = (_hoops_SHGH*)image->rasters[_hoops_CIGIS];
				_hoops_CSSHS = (_hoops_SHGH*)_hoops_IHARI->rasters[row];

				for (col = 0; col < nw; col++) {
					_hoops_ACGIS = _hoops_PSCSH((float)col*_hoops_PIIH);
					_hoops_CSSHS[col] = _hoops_ACSHS[_hoops_ACGIS];
				}
			}
		}
		else {
			ASSERT (image->format == _hoops_AHGH);
			unsigned char *_hoops_ACSHS, *_hoops_CSSHS;
			for (row = 0; row < nh; row++) {
				_hoops_CIGIS = _hoops_PSCSH((float)row*_hoops_HIIH);
				_hoops_ACSHS = (unsigned char*)image->rasters[_hoops_CIGIS];
				_hoops_CSSHS = (unsigned char*)_hoops_IHARI->rasters[row];

				for (col = 0; col < nw; col++) {
					_hoops_ACGIS = _hoops_PSCSH((float)col*_hoops_PIIH);
					_hoops_CSSHS[col] = _hoops_ACSHS[_hoops_ACGIS];
				}
			}
		}
	}
	else if (nw < image->width &&
			 nh < image->height &&
			 image->width < 4096 &&
			 image->height < 4096 &&
			 _hoops_PCSHS(nw) &&
			 _hoops_PCSHS(nh) )
			{

		// _hoops_AARIS _hoops_IS _hoops_RIIR _hoops_IIGR 2 _hoops_GRP _hoops_PARIS _hoops_RHRP
		Image * _hoops_HARIS = null;
		int _hoops_IARIS = _hoops_HSHGI(_hoops_IAAA(image->width, nw));
		int _hoops_CARIS = _hoops_HSHGI(_hoops_IAAA(image->height, nh));
		HI_Create_Scaled_Image_Copy(&_hoops_HARIS, image, _hoops_CARIS, _hoops_IARIS);
		_hoops_HARIS = HI_Create_Bicubic_Scaled_Image(image, _hoops_CARIS, _hoops_IARIS, _hoops_HARIS);
		_hoops_RCSHS(_hoops_HARIS);

		// _hoops_PGIP _hoops_GRP _hoops_AHCRR _hoops_RGRR
		_hoops_IHARI = HI_Create_Box_Downsampled_Image(_hoops_HARIS, nh, nw, _hoops_IHARI);

		_hoops_HPRH(_hoops_HARIS);
	}
	else {
		_hoops_IHARI = HI_Create_Bicubic_Scaled_Image(image, nh, nw, _hoops_IHARI);
	}

	_hoops_RCSHS(_hoops_IHARI);
	return _hoops_IHARI;
}


local Image * HI_Copy_Image(
	Image const *		image) {
	Image *				_hoops_IHARI = null;
	unsigned char alter *_hoops_CSSHS;
	unsigned char const *_hoops_ACSHS;
	int					row;

	/* _hoops_PS _hoops_RRP _hoops_IS _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_CSCR */
	HI_Create_Image(&_hoops_IHARI,
					null,
					image->width, image->height,
					image->format, 0,
					_hoops_RRPGI, null);

	if (!_hoops_IHARI)
		return null;

	_hoops_IHARI->flags |= image->flags;
	if (BIT(image->flags, _hoops_SHCC))
		HOOPS_WORLD->_hoops_ACPIR++;

	if (BIT(image->flags, _hoops_GCRH))
		_hoops_IHARI->_hoops_HPIR = image->_hoops_HPIR;

	ASSERT (!BIT (image->flags, _hoops_SSGH));

	for (row = 0; row < image->height; row++) {
		_hoops_ACSHS = (unsigned char *) image->rasters[row];
		_hoops_CSSHS = (unsigned char *) _hoops_IHARI->rasters[row];

		_hoops_AIGA(_hoops_ACSHS, image->row_bytes, unsigned char, _hoops_CSSHS);
	}

	_hoops_RCSHS(_hoops_IHARI);
	return _hoops_IHARI;
}


local Image * HI_Create_Inset_Image (
	Image const *		image,
	int 				nh,
	int 				nw) {
	int					row, _hoops_SARIS, _hoops_CAAIP;
	Image *				_hoops_IHARI = null;

	/* _hoops_PS _hoops_RRP _hoops_IS _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_CSCR */
	HI_Create_Image(&_hoops_IHARI,
					null,
					nw, nh,
					image->format, 0,
					_hoops_RRPGI, null);

	if (!_hoops_IHARI)
		return null;

	_hoops_IHARI->flags |= image->flags;
	_hoops_IHARI->flags |= _hoops_PCRH;
	if (BIT(image->flags, _hoops_SHCC))
		HOOPS_WORLD->_hoops_ACPIR++;

	_hoops_SARIS = _hoops_AHIA(image->row_bytes, _hoops_IHARI->row_bytes);

	_hoops_CAAIP = _hoops_IHARI->height - image->height;

	for (row = 0; row < image->height; row++) {
		COPY_MEMORY(image->rasters[row], _hoops_SARIS, (void*)_hoops_IHARI->rasters[row+_hoops_CAAIP]);
	}

	_hoops_RCSHS(_hoops_IHARI);
	return _hoops_IHARI;
}

local Image * HI_Create_Bordered_Image(
	Image const *		image) {
	int					row, col;
	Image *				_hoops_IHARI = null;

	ASSERT (image->format == Image_RGBA32 ||
		image->format == _hoops_HHGH ||
		image->format == _hoops_AHGH);

	/* _hoops_PS _hoops_RRP _hoops_IS _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_CSCR */
	HI_Create_Image(&_hoops_IHARI,
					null,
					image->width+2, image->height+2,
					image->format, 0,
					_hoops_RRPGI, null);

	if (!_hoops_IHARI)
		return null;

	_hoops_IHARI->flags |= image->flags;
	_hoops_IHARI->flags |= _hoops_AGSC;
	if (BIT(image->flags, _hoops_SHCC))
		HOOPS_WORLD->_hoops_ACPIR++;

	if (BIT(image->flags, _hoops_GCRH))
		_hoops_IHARI->_hoops_HPIR = image->_hoops_HPIR;

	COPY_MEMORY(_hoops_IHARI->rasters[1],
			_hoops_IHARI->row_bytes,
			(void*)_hoops_IHARI->rasters[0]);

	COPY_MEMORY(_hoops_IHARI->rasters[_hoops_IHARI->height-2],
				_hoops_IHARI->row_bytes,
				(void*)_hoops_IHARI->rasters[_hoops_IHARI->height-1]);


	if (image->format == Image_RGBA32) {
		_hoops_AIGH alter *		_hoops_CSSHS;
		_hoops_AIGH const *		_hoops_ACSHS;
		for (row = 0; row < image->height; row++) {
			_hoops_ACSHS = (_hoops_AIGH *) image->rasters[row];
			_hoops_CSSHS = (_hoops_AIGH *) _hoops_IHARI->rasters[row+1];

			_hoops_CSSHS++;
			_hoops_AIGA(_hoops_ACSHS, image->width, _hoops_AIGH, _hoops_CSSHS);
		}

		for (row = 0; row < image->height; row++) {
			((_hoops_AIGH*)_hoops_IHARI->rasters[row+1])[0] = ((_hoops_AIGH*)image->rasters[row])[0];
			((_hoops_AIGH*)_hoops_IHARI->rasters[row+1])[_hoops_IHARI->width-1] = ((_hoops_AIGH*)image->rasters[row])[image->width-1];
		}

		if (BIT (image->flags, _hoops_PPRH)) {
			for (row = 0 ; row < _hoops_IHARI->height ; row++) {
				((_hoops_AIGH*)_hoops_IHARI->rasters[row])[0].a = 0;
				((_hoops_AIGH*)_hoops_IHARI->rasters[row])[_hoops_IHARI->width-1].a = 0;
			}
			for (col = 0 ; col < _hoops_IHARI->width ; col++) {
				((_hoops_AIGH*)_hoops_IHARI->rasters[0])[col].a = 0;
				((_hoops_AIGH*)_hoops_IHARI->rasters[_hoops_IHARI->height - 1])[col].a = 0;
			}
		}
	}
	else if (image->format == _hoops_HHGH) {
		_hoops_SHGH alter *		_hoops_CSSHS;
		_hoops_SHGH const *		_hoops_ACSHS;
		for (row = 0; row < image->height; row++) {
			_hoops_ACSHS = (_hoops_SHGH *) image->rasters[row];
			_hoops_CSSHS = (_hoops_SHGH *) _hoops_IHARI->rasters[row+1];

			_hoops_CSSHS++;
			for (col = 0 ; col < image->width ; col++)
				*_hoops_CSSHS++ = *_hoops_ACSHS++;
		}

		for (row = 0; row < image->height; row++) {
			((_hoops_SHGH*)_hoops_IHARI->rasters[row+1])[0] = ((_hoops_SHGH*)image->rasters[row])[0];
			((_hoops_SHGH*)_hoops_IHARI->rasters[row+1])[_hoops_IHARI->width-1] = ((_hoops_SHGH*)image->rasters[row])[image->width-1];
		}
	}
	else {
		ASSERT (image->format == _hoops_AHGH);
		unsigned char alter *		_hoops_CSSHS;
		unsigned char const *		_hoops_ACSHS;
		for (row = 0; row < image->height; row++) {
			_hoops_ACSHS = (unsigned char *) image->rasters[row];
			_hoops_CSSHS = (unsigned char *) _hoops_IHARI->rasters[row+1];

			_hoops_CSSHS++;
			_hoops_AIGA(_hoops_ACSHS, image->width, unsigned char, _hoops_CSSHS);
		}

		for (row = 0; row < image->height; row++) {
			((unsigned char*)_hoops_IHARI->rasters[row+1])[0] = ((unsigned char*)image->rasters[row])[0];
			((unsigned char*)_hoops_IHARI->rasters[row+1])[_hoops_IHARI->width-1] = ((unsigned char*)image->rasters[row])[image->width-1];
		}
	}

	_hoops_RCSHS(_hoops_IHARI);
	return _hoops_IHARI;
}


GLOBAL_FUNCTION void HD_Set_Image_Alpha(
	Image alter *		image,
	unsigned char		alpha) {
	_hoops_AIGH alter *		_hoops_GPRIS;
	int					row, col;

	if (!BIT(image->flags, _hoops_PPRH)) {
		HE_WARNING (HEC_TEXTURE, HES_INVALID_IMAGE,
			"Trying to set the alpha on non-forced-alpha image");
		return;
	}

	if (image->_hoops_PGARP == alpha)
		return;

	image->_hoops_PGARP = alpha;

	for (row = 0; row < image->height; row++) {
		_hoops_GPRIS = (_hoops_AIGH alter *)image->rasters[row];
		for (col = 0; col < image->width; col++) {
			_hoops_GPRIS[col].a = alpha;
		}
	}
}


GLOBAL_FUNCTION void HD_Clean_Texture_Image_Cache (
	Net_Rendition const &		nr,
	_hoops_RCR const *				txr) {
	Image *						image = txr->image;
	_hoops_GACR const *		dl;

	if (image)
		image = image->next;

	while (image) {
		if (BIT(image->flags, _hoops_RCRRP)) {
			if (image->_hoops_GAHA && image->_hoops_PHGH &&
				!BIT (image->_hoops_RRHH, _hoops_IIPIR) &&
					!BIT(image->flags, _hoops_PPRH)) {

				if ((dl = image->_hoops_GAHA) != null) do {
					if (dl->_hoops_GHRI == nr->_hoops_SRA->_hoops_GHRI) break;
				} while ((dl = dl->next) != null);

				if (dl) {
					if (image->width * image->height > 0) {
						FREE_ARRAY (image->_hoops_PHGH, image->row_bytes * image->height, char);
						if (image->rasters)
							FREE_ARRAY (image->rasters, image->height, void const *);
						if (image->_hoops_RCPIR)
							FREE_ARRAY (image->_hoops_RCPIR, image->height, void const *);
						image->_hoops_PHGH = 0;
						image->rasters = 0;
						image->_hoops_RCPIR = 0;
						image->flags |= _hoops_APAH;
					}
				}
			}
			image = image->next;
		}
		else {
			Image *		_hoops_RPRIS = image;

			image = image->next;
			_hoops_RPRIS->prev->next = _hoops_RPRIS->next;
			if (_hoops_RPRIS->next) {
				_hoops_RPRIS->next->prev = _hoops_RPRIS->prev;
				_hoops_RPRIS->next = 0;
			}
			_hoops_HPRH(_hoops_RPRIS);
		}
	}
}


GLOBAL_FUNCTION void HD_Activate_Texture_Image (
	Net_Rendition const &		nr,
	_hoops_RCR alter *				txr,
	_hoops_HIGH					_hoops_ICRRH,
	int 						_hoops_AGIIH,
	int 						_hoops_PGIIH,
	int 						_hoops_HGIIH,
	int 						_hoops_IGIIH) {
#ifndef DISABLE_TEXTURING
	Image * 					_hoops_APRIS = null;
	Image * 					_hoops_IHARI = null;
	Image * 					_hoops_PPRIS = null;
	Image * 					image = null;
	bool						_hoops_HPRIS = false;
	int							nw, nh;
	bool						_hoops_IPRIS = false; 

	_hoops_GPRH(_hoops_RCRGH)++;

	image = txr->image;

	//_hoops_IS _hoops_SHH _hoops_GCPRA _hoops_GIGS, _hoops_HIAH _hoops_PPR _hoops_CPRIS _hoops_RRP _hoops_IS _hoops_SHH 4-_hoops_RAPSR _hoops_RGCGA
	if (BIT(_hoops_ICRRH, _hoops_HCRRP) ||
		image->row_bytes & 0x3)
		_hoops_IPRIS = true;

	/* _hoops_ARGII _hoops_RH _hoops_SSSHR _hoops_CSCR _hoops_IGIR */
#define _hoops_SPRIS 1
	if (_hoops_AGIIH == 0) _hoops_AGIIH=_hoops_SPRIS;
	if (_hoops_HGIIH == 0) _hoops_HGIIH=_hoops_SPRIS;

	if (_hoops_PGIIH != 0) {
		if (BIT(_hoops_ICRRH, _hoops_GHRH)) {
			int _hoops_GHRIS = _hoops_HSHGI(_hoops_IAAA(_hoops_PGIIH, _hoops_AGIIH));
			if (_hoops_GHRIS > _hoops_PGIIH) {
				_hoops_PGIIH /= 2;
				_hoops_PGIIH = _hoops_HSHGI(_hoops_IAAA(_hoops_PGIIH, _hoops_AGIIH));
			}
		}
	}
	else {
		_hoops_PGIIH = _hoops_IICIA;
	}

	if (_hoops_IGIIH != 0) {
		if (BIT(_hoops_ICRRH, _hoops_GHRH)) {
			int _hoops_RHRIS = _hoops_HSHGI(_hoops_IAAA(_hoops_IGIIH, _hoops_HGIIH));
			if (_hoops_RHRIS > _hoops_PGIIH) {
				_hoops_IGIIH /= 2;
				_hoops_IGIIH = _hoops_HSHGI(_hoops_IAAA(_hoops_IGIIH, _hoops_HGIIH));
			}
		}
	}
	else {
		_hoops_IGIIH = _hoops_IICIA;
	}

	if (ANYBIT(_hoops_ICRRH, _hoops_RIRH|_hoops_AIRH|_hoops_GHRH)) {
#define _hoops_AHRIS 256
		if (_hoops_PCSHS (txr->image->width))
			nw = txr->image->width;
		else if (txr->image->width >= _hoops_AHRIS)
			nw = _hoops_HSHGI(_hoops_IAAA(txr->image->width, _hoops_AGIIH));
		else
			nw = _hoops_AHRIS;
		if (_hoops_PCSHS (txr->image->height))
			nh = txr->image->height;
		else if (txr->image->height >= _hoops_AHRIS)
			nh = _hoops_HSHGI(_hoops_IAAA(txr->image->height, _hoops_HGIIH));
		else
			nh = _hoops_AHRIS;

		if (ANYBIT(_hoops_ICRRH, _hoops_RIRH|_hoops_AIRH))
			nw = nh = _hoops_IAAA(nw, nh);
	}
	else {
		nw = image->width;
		nh = image->height;
		if (nw<_hoops_AGIIH) nw=_hoops_AGIIH;
		if (nh<_hoops_HGIIH) nh=_hoops_HGIIH;
	}

#ifndef DISABLE_EXTENDED_TEXTURE
	if (BIT(_hoops_ICRRH, _hoops_SIRRP)) {
		nw *= 2;
		nh *= 2;
	}
#endif

	if (nw > _hoops_PGIIH) nw = _hoops_PGIIH;
	if (nh > _hoops_IGIIH) nh = _hoops_IGIIH;
	/* _hoops_HA _hoops_SR _hoops_ACPA _hoops_RH _hoops_SIGR _hoops_IGIR */


_hoops_PHRIS:

	while (image &&
		   ((image->format != Image_RGBA32 && image->format != _hoops_HHGH && image->format != _hoops_AHGH) ||
		    (image->format != Image_RGBA32 && _hoops_IPRIS) ||
		 	BIT(_hoops_ICRRH, _hoops_HHRH) && !image->_hoops_PHGH && !image->_hoops_GAHA ||
		 	BIT(_hoops_ICRRH, _hoops_AGSC) && !BIT(image->flags, _hoops_AGSC) ||
		 	!BIT(_hoops_ICRRH, _hoops_AGSC) && BIT(image->flags, _hoops_AGSC) ||
		 	!BIT(_hoops_ICRRH, _hoops_RIRH) && BIT(image->flags, _hoops_RIRH) ||
		 	!BIT(_hoops_ICRRH, _hoops_AIRH) && BIT(image->flags, _hoops_AIRH) ||
		 	!BIT(_hoops_ICRRH, _hoops_PCRH) && BIT(image->flags, _hoops_PCRH) ||
		 	!BIT(_hoops_ICRRH, _hoops_PPRH) && BIT(image->flags, _hoops_PPRH)
#ifndef DISABLE_EXTENDED_TEXTURE
		 	||
		 	BIT(_hoops_ICRRH, _hoops_SIRRP) != BIT(image->flags, _hoops_SIRRP) ||
		 	BIT(_hoops_ICRRH, _hoops_GCRH) != BIT(image->flags, _hoops_GCRH) ||
		 	BIT(_hoops_ICRRH, _hoops_GIRH) != BIT(image->flags, _hoops_GIRH) ||
				BIT(_hoops_ICRRH, _hoops_GIRH) && image->_hoops_PHAH != nr->_hoops_ARA->_hoops_IHRH ||
		 	BIT(_hoops_ICRRH, _hoops_GCRH) && !BIT(_hoops_ICRRH, _hoops_GIRH) && txr->_hoops_HPIR != image->_hoops_HPIR
#endif
		   )) image = image->next;

	if (image) {

		/*_hoops_ISPR _hoops_IGIR*/
		if ((!BIT(_hoops_ICRRH, _hoops_AGSC) &&
				(nw == image->width && nh == image->height)) ||
			(BIT(_hoops_ICRRH, _hoops_AGSC) &&
				(nw+2 == image->width && nh+2 == image->height)) ||
			((BIT(_hoops_ICRRH, _hoops_SIRRP) && !BIT(_hoops_ICRRH, _hoops_AGSC)) &&
				(nw*2 == image->width && nh*2 == image->height)) ||
			((BIT(_hoops_ICRRH, _hoops_SIRRP) && BIT(_hoops_ICRRH, _hoops_AGSC)) &&
				(nw*2+2 == image->width && nh*2+2 == image->height))) {

			_hoops_GACR const *		dl = null;

			if (BIT(_hoops_ICRRH, _hoops_PPRH) && !BIT(image->flags, _hoops_PPRH)) {
				if (!BIT(image->flags, _hoops_APAH))
					_hoops_PPRIS = image;

				/* _hoops_GRHP _hoops_HCHAR */
				image = image->next;
				goto _hoops_PHRIS;
			}

			if (BIT(_hoops_ICRRH, _hoops_GIRH) && !BIT(image->flags, _hoops_GIRH)) {
				if (!BIT(image->flags, _hoops_APAH))
					_hoops_PPRIS = image;

				/* _hoops_GRHP _hoops_HCHAR */
				image = image->next;
				goto _hoops_PHRIS;
			}

			if (BIT(_hoops_ICRRH, _hoops_PCRH) && !BIT(image->flags, _hoops_PCRH)) {
				if (!BIT(image->flags, _hoops_APAH))
					_hoops_PPRIS = image;

				/* _hoops_GRHP _hoops_HCHAR */
				image = image->next;
				goto _hoops_PHRIS;
			}

			if (BIT(_hoops_ICRRH, _hoops_RIRH) && !BIT(image->flags, _hoops_RIRH)) {
				if (!BIT(image->flags, _hoops_APAH))
					_hoops_PPRIS = image;

				/* _hoops_GRHP _hoops_HCHAR */
				image = image->next;
				goto _hoops_PHRIS;
			}

			if (BIT(_hoops_ICRRH, _hoops_AIRH) && !BIT(image->flags, _hoops_AIRH)) {
				if (!BIT(image->flags, _hoops_APAH))
					_hoops_PPRIS = image;

				/* _hoops_GRHP _hoops_HCHAR */
				image = image->next;
				goto _hoops_PHRIS;
			}

			if (!BIT(_hoops_ICRRH, _hoops_ACRRP) &&
						BIT(_hoops_ICRRH, _hoops_HHRH) && !image->_hoops_PHGH) {
				_hoops_GACR **		_hoops_HHRIS = null;

				_hoops_HHRIS=&image->_hoops_GAHA;

				while ((dl = *_hoops_HHRIS) != null) {
					if (dl->_hoops_GHRI == nr->_hoops_SRA->_hoops_GHRI) {
						if (dl->list != null)
							break;
						*_hoops_HHRIS = dl->next;
						_hoops_HPRH(dl);
					}
					else {
						_hoops_HHRIS = (_hoops_GACR**)&dl->next;
					}
				}

				if (!dl) {
					/* _hoops_GRHP _hoops_HCHAR */
					image = image->next;
					goto _hoops_PHRIS;
				}
			}

			if (!dl && BIT(image->flags, _hoops_APAH)) {
				/* _hoops_GRHP _hoops_HCHAR */
				image = image->next;
				goto _hoops_PHRIS;
			}

			/* _hoops_PS _hoops_PAH _hoops_SGH _hoops_RGR _hoops_CSCR!! */
			goto _hoops_IHRIS;
		}

		if (!BIT(image->flags, _hoops_AGSC)) {
			/* _hoops_HRGR _hoops_RGR _hoops_RH _hoops_RRHP _hoops_IGIR */
			if ((nw == image->width || nh == image->height) &&
				!BIT(image->flags, _hoops_APAH))
					_hoops_PPRIS = image;

			/* _hoops_HRGR _hoops_RGR _hoops_RH _hoops_IGIR _hoops_IIGR _hoops_RH _hoops_GIGR */
			if (!_hoops_PPRIS &&
				(txr->image->width == image->width &&
				txr->image->width == image->width) &&
				!BIT(image->flags, _hoops_APAH))
					_hoops_PPRIS = image;
		}

		/* _hoops_GRHP _hoops_HCHAR */
		image = image->next;
		goto _hoops_PHRIS;
	}

	if ((image = _hoops_PPRIS) == null) {
		image = txr->image;
_hoops_CHRIS:
		while (image &&
			   ((image->format != Image_RGBA32 && image->format != _hoops_HHGH && image->format != _hoops_AHGH) ||
			    (image->format != Image_RGBA32 && _hoops_IPRIS) ||
				BIT(image->flags, _hoops_HHRH) && !image->_hoops_PHGH ||
				ANYBIT(image->flags, _hoops_APAH | _hoops_SIRRP | _hoops_AGSC | _hoops_PCRH |
									 _hoops_PPRH | _hoops_GIRH | _hoops_GCRH)))
			image = image->next;

		if (image) {
			/* _hoops_HRGR _hoops_RGR _hoops_RH _hoops_RRHP _hoops_IGIR */
			if (nw == image->width || nh == image->height)
				_hoops_PPRIS = image;

			/* _hoops_HRGR _hoops_RGR _hoops_RH _hoops_IGIR _hoops_IIGR _hoops_RH _hoops_GIGR */
			if (!_hoops_PPRIS &&
				txr->image->width == image->width &&
				txr->image->width == image->width)
				_hoops_PPRIS = image;

			/* _hoops_GRHP _hoops_HCHAR */
			image = image->next;
			goto _hoops_CHRIS;
		}
		else {
			if (_hoops_PPRIS)
				image = _hoops_PPRIS;
			else
				image = txr->image;
		}
	}

	_hoops_HPRIS = true;
	_hoops_GPRH(_hoops_ACRGH)++;

_hoops_SHRIS:

	if (image->format == _hoops_GGRH ||
		image->format == _hoops_RGRH ||
		image->format == _hoops_AGRH) {
		if (image->format == _hoops_GGRH)
			_hoops_IHARI = HI_PNG_Decompress (txr->image);
		else if (image->format == _hoops_RGRH)
			_hoops_IHARI = HI_JPEG_Decompress (txr->image);
		else
			_hoops_IHARI = HI_TARGA_Decompress (txr->image);

		if (_hoops_IHARI == null)
			goto _hoops_GIRIS;

		//_hoops_RGR _hoops_HRGR _hoops_PHPHA _hoops_PIH, _hoops_HIS _hoops_GA'_hoops_RA _hoops_SGHPA _hoops_GPP _hoops_IS _hoops_SCH _hoops_RAS _hoops_SCH'_hoops_GRI _hoops_RPII _hoops_PGGGH _hoops_CIAA _hoops_GSIA
		_hoops_IHARI->flags |= _hoops_GPAH;

		/* _hoops_AGGAR _hoops_GGR _hoops_RH _hoops_CSCR */
		_hoops_IHARI->next = image->next;
		if (_hoops_IHARI->next)
			_hoops_IHARI->next->prev = _hoops_IHARI;
		image->next = _hoops_IHARI;
		_hoops_IHARI->prev = image;

		image = _hoops_IHARI;
	}		

	/* _hoops_SR _hoops_GHCA _hoops_SHH _hoops_CRSH _hoops_CCA _hoops_RH _hoops_GIGR */
	/* _hoops_PAR _hoops_IRS _hoops_PIS _hoops_GRAA _hoops_RIRIS  _hoops_AIRIS _hoops_CSCR */
	if (((image->format != Image_RGBA32) && (image->format != _hoops_HHGH) && (image->format != _hoops_AHGH)) ||
		((image->format != Image_RGBA32) && _hoops_IPRIS) ||
		BIT(_hoops_ICRRH, _hoops_HHRH) && !image->_hoops_PHGH) {

		_hoops_IHARI = HI_Convert_To_RGBA32(nr, image);

		if (_hoops_IHARI == null)
			goto _hoops_GIRIS;

		/* _hoops_AGGAR _hoops_GGR _hoops_RH _hoops_CSCR */
		_hoops_IHARI->next = image->next;
		if (_hoops_IHARI->next)
			_hoops_IHARI->next->prev = _hoops_IHARI;
		image->next = _hoops_IHARI;
		_hoops_IHARI->prev = image;

		image = _hoops_IHARI;
	}

#ifndef DISABLE_EXTENDED_TEXTURE
	/* _hoops_AHAA _hoops_GAR _hoops_SIGR */
	if (BIT(_hoops_ICRRH, _hoops_GCRH) && txr->_hoops_HPIR != image->_hoops_HPIR) {
		if (image->format != Image_RGBA32) {
			_hoops_IPRIS = true;
			goto _hoops_SHRIS;
		}

		_hoops_IHARI = HI_Remap_Image(nr, txr, image);

		if (_hoops_IHARI == null)
			goto _hoops_GIRIS;

		/* _hoops_AGGAR _hoops_GGR _hoops_RH _hoops_CSCR */
		_hoops_IHARI->next = image->next;
		if (_hoops_IHARI->next)
			_hoops_IHARI->next->prev = _hoops_IHARI;
		image->next = _hoops_IHARI;
		_hoops_IHARI->prev = image;

		image = _hoops_IHARI;
	}

#endif

	if (BIT(_hoops_ICRRH, _hoops_GIRH) && 
		!BIT(image->flags, _hoops_GIRH) && 
		image->format != _hoops_AHGH) {
		_hoops_IHARI = _hoops_PGGIS (image, nr->_hoops_ARA->_hoops_IHRH);

		if (_hoops_IHARI == null)
			goto _hoops_GIRIS;

		/* _hoops_AGGAR _hoops_GGR _hoops_RH _hoops_CSCR */
		_hoops_IHARI->next = image->next;
		if (_hoops_IHARI->next)
			_hoops_IHARI->next->prev = _hoops_IHARI;
		image->next = _hoops_IHARI;
		_hoops_IHARI->prev = image;

		image = _hoops_IHARI;
	}

#ifndef DISABLE_EXTENDED_TEXTURE
	/* _hoops_AA _hoops_SR _hoops_RRP _hoops_IRS _hoops_HIGIS _hoops_CSCR */
	if (BIT(_hoops_ICRRH, _hoops_SIRRP) && !BIT(image->flags, _hoops_SIRRP)) {
		_hoops_IHARI = HI_Create_Mirror_Image(image);

		if (_hoops_IHARI == null)
			goto _hoops_GIRIS;

		if (nw == _hoops_IHARI->width || nh != _hoops_IHARI->height) {
			/* _hoops_AGGAR _hoops_GGR _hoops_RH _hoops_CSCR */
			_hoops_IHARI->next = image->next;
			if (_hoops_IHARI->next)
				_hoops_IHARI->next->prev = _hoops_IHARI;
			image->next = _hoops_IHARI;
			_hoops_IHARI->prev = image;
		}
		else {
			_hoops_APRIS = _hoops_IHARI;
		}

		image = _hoops_IHARI;
	}
#endif

	/* _hoops_AA _hoops_SR _hoops_RRP _hoops_IRS _hoops_PIRIS _hoops_CSCR */
	if (BIT(_hoops_ICRRH, _hoops_PCRH) &&
		(nw > image->width || nh > image->height)) {

		_hoops_IHARI = HI_Create_Inset_Image(image, nh, nw);

		if (_hoops_IHARI == null)
			goto _hoops_GIRIS;

		/* _hoops_AGGAR _hoops_GGR _hoops_RH _hoops_CSCR */
		_hoops_IHARI->next = image->next;
		if (_hoops_IHARI->next)
			_hoops_IHARI->next->prev = _hoops_IHARI;
		image->next = _hoops_IHARI;
		_hoops_IHARI->prev = image;

		image = _hoops_IHARI;
	}

	/* _hoops_AA _hoops_SR _hoops_RRP _hoops_IRS _hoops_CPPSR _hoops_CSCR */
	if (nw != image->width || nh != image->height) {
		if (txr->_hoops_PSCC == _hoops_HSCC)
			_hoops_IHARI = HI_Create_Scaled_Image(image, nh, nw, _hoops_GARIS);
		else
			_hoops_IHARI = HI_Create_Scaled_Image(image, nh, nw, _hoops_RARIS);

		if (_hoops_IHARI == null)
			goto _hoops_GIRIS;

		if (_hoops_APRIS)
			_hoops_HPRH(_hoops_APRIS);

		/* _hoops_AGGAR _hoops_GGR _hoops_RH _hoops_CSCR */
		_hoops_IHARI->next = image->next;
		if (_hoops_IHARI->next)
			_hoops_IHARI->next->prev = _hoops_IHARI;
		image->next = _hoops_IHARI;
		_hoops_IHARI->prev = image;

		image = _hoops_IHARI;
	}

	if (BIT(_hoops_ICRRH, _hoops_PPRH) && !BIT(image->flags, _hoops_PPRH)) {
		if (image->format == Image_RGBA32)
			_hoops_IHARI = HI_Copy_Image(image);
		else
			_hoops_IHARI = HI_Convert_To_RGBA32(nr, image);

		if (_hoops_IHARI == null)
			goto _hoops_GIRIS;

		_hoops_IHARI->flags |= _hoops_PPRH;

		/* _hoops_AGGAR _hoops_GGR _hoops_RH _hoops_CSCR */
		_hoops_IHARI->next = image->next;
		if (_hoops_IHARI->next)
			_hoops_IHARI->next->prev = _hoops_IHARI;
		image->next = _hoops_IHARI;
		_hoops_IHARI->prev = image;

		image = _hoops_IHARI;
	}

	/* _hoops_AA _hoops_SR _hoops_RRP _hoops_IRS _hoops_RIRIS _hoops_CSCR */
	if (BIT(_hoops_ICRRH, _hoops_AGSC)) {
		_hoops_IHARI = HI_Create_Bordered_Image(image);

		if (_hoops_IHARI == null)
			goto _hoops_GIRIS;

		/* _hoops_AGGAR _hoops_GGR _hoops_RH _hoops_CSCR */
		_hoops_IHARI->next = image->next;
		if (_hoops_IHARI->next)
			_hoops_IHARI->next->prev = _hoops_IHARI;
		image->next = _hoops_IHARI;
		_hoops_IHARI->prev = image;

		image = _hoops_IHARI;
	}

	if (BIT(_hoops_ICRRH, _hoops_RIRH)) {
		if (!_hoops_IHARI) {
			if (ANYBIT(image->flags, _hoops_AIRH|_hoops_PCRRP)) {

				_hoops_IHARI = HI_Copy_Image(image);

				if (_hoops_IHARI == null)
					goto _hoops_GIRIS;

				/* _hoops_AGGAR _hoops_GGR _hoops_RH _hoops_CSCR */
				_hoops_IHARI->next = image->next;
				if (_hoops_IHARI->next)
					_hoops_IHARI->next->prev = _hoops_IHARI;
				image->next = _hoops_IHARI;
				_hoops_IHARI->prev = image;

				image = _hoops_IHARI;
			}
			else {
				image->flags |= _hoops_RIRH;
				_hoops_HPRIS = false;
				goto _hoops_IHRIS;
			}
		}

		_hoops_IHARI->flags |= _hoops_RIRH;
	}

	if (BIT(_hoops_ICRRH, _hoops_AIRH)) {
		if (!_hoops_IHARI) {
			if (ANYBIT(image->flags, _hoops_RIRH|_hoops_PCRRP)) {

				_hoops_IHARI = HI_Copy_Image(image);

				if (_hoops_IHARI == null)
					goto _hoops_GIRIS;

				/* _hoops_AGGAR _hoops_GGR _hoops_RH _hoops_CSCR */
				_hoops_IHARI->next = image->next;
				if (_hoops_IHARI->next)
					_hoops_IHARI->next->prev = _hoops_IHARI;
				image->next = _hoops_IHARI;
				_hoops_IHARI->prev = image;

				image = _hoops_IHARI;
			}
			else {
				image->flags |= _hoops_AIRH;
				_hoops_HPRIS = false;
				goto _hoops_IHRIS;
			}
		}

		_hoops_IHARI->flags |= _hoops_AIRH;
	}

	/* _hoops_RH _hoops_HIRIS _hoops_AGIR */
	if (!ANYBIT(_hoops_ICRRH, _hoops_RIRH|_hoops_AIRH) &&
		ANYBIT(image->flags, _hoops_RIRH|_hoops_AIRH)) {

		_hoops_IHARI = HI_Copy_Image(image);

		if (_hoops_IHARI == null)
			goto _hoops_GIRIS;

		/* _hoops_AGGAR _hoops_GGR _hoops_RH _hoops_CSCR */
		_hoops_IHARI->next = image->next;
		if (_hoops_IHARI->next)
			_hoops_IHARI->next->prev = _hoops_IHARI;
		image->next = _hoops_IHARI;
		_hoops_IHARI->prev = image;

		image = _hoops_IHARI;

		image->flags &= ~(_hoops_RIRH|_hoops_AIRH);
	}

_hoops_IHRIS:

	if (!ANYBIT(image->flags, _hoops_RIRH|_hoops_AIRH))
		image->flags |= _hoops_PCRRP;

	if (txr->_hoops_RHGH)
		_hoops_HPRH(txr->_hoops_RHGH);
	txr->_hoops_RHGH = image;
	_hoops_PRRH(txr->_hoops_RHGH);

	txr->_hoops_RHGH->flags |= _hoops_RCRRP;

_hoops_GIRIS:
	
	if (_hoops_HPRIS)
		HD_Clean_Texture_Image_Cache(nr, txr);
#endif
}


GLOBAL_FUNCTION void HD_Standard_Compute_Texture (
	Net_Rendition const &		nr,
	_hoops_RCR const *				txr,
	Point const *				_hoops_ICAGA,
	_hoops_ARPA const *				plane,
	_hoops_RSSH const *			_hoops_IIRIS,
	int							param_width,
	_hoops_SSIC				param_flags,
	_hoops_ARGRA			_hoops_GCI,
	RGBA alter *				_hoops_CGIIH) {
#ifndef DISABLE_TEXTURING
#ifndef DISABLE_SOFTWARE_TEXTURE
	_hoops_RSSH					param[3];
	_hoops_RSSH					_hoops_CIRIS[3];
	_hoops_RSSH *					params;
	Image const *				image;
	int							_hoops_SIRIS;
	int							_hoops_GCRIS;
	_hoops_PCGRP				_hoops_GAARP = txr->_hoops_GAARP;
	Param_Source				_hoops_PSR = txr->_hoops_PSR;
	float						_hoops_RCRIS[4][4];
	bool						_hoops_ACRIS = true;

	if (txr->_hoops_RHGH &&
		(BIT(txr->_hoops_RHGH->flags, _hoops_APAH) ||
			BIT(txr->_hoops_RHGH->flags, _hoops_PPRH))) {
			_hoops_HPRH(txr->_hoops_RHGH);
			((_hoops_RCR*)txr)->_hoops_RHGH = null;
	}

	if (txr->_hoops_RHGH &&
		!BIT(txr->_hoops_RHGH->flags, _hoops_GIRH) &&
		(BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI) ||
		 BIT(nr->_hoops_ARA->_hoops_IHRH.options, _hoops_CHRH))) {
		_hoops_HPRH(txr->_hoops_RHGH);
		((_hoops_RCR*)txr)->_hoops_RHGH = null;
	}

	if (!txr->_hoops_RHGH) {
		_hoops_HIGH				_hoops_IIGH = 0;

		if (txr->_hoops_CGA == _hoops_PSGRP)
			_hoops_IIGH |= _hoops_SIRRP;

		if (ANYBIT(txr->flags, _hoops_HIRH) ||
			txr->_hoops_HPIR._hoops_IIRH != 0.0f ||
			txr->_hoops_HPIR._hoops_CIRH != 1.0f)
			_hoops_IIGH |= _hoops_GCRH;

		if (BIT(nr->_hoops_ARA->_hoops_IHRH.options, _hoops_CHRH))
			_hoops_IIGH |= _hoops_GIRH;

		if (txr->image->format != Image_RGBA32)
			_hoops_IIGH |= _hoops_HCRRP;

		HD_Activate_Texture_Image (nr, (_hoops_RCR alter*)txr, _hoops_IIGH, 0, 0, 0, 0);
	}

	if ((image = txr->_hoops_RHGH) == null) {
		return;
	}

	if (_hoops_IIRIS == null) {
		param_width = 3;
		param_flags = 0;
		params=_hoops_CIRIS;
		params[0] = params[1] = params[2] = 0.0f;
	}
	else {
		int offset = txr->_hoops_RSCP;

		if (offset+2>param_width)
			offset=0;

		param_width-=offset;

		/*_hoops_CISRP _hoops_IS 3 _hoops_IH _hoops_HA*/
		_hoops_CIRIS[0] = _hoops_IIRIS[offset];
		if (param_width>1)
			_hoops_CIRIS[1] = _hoops_IIRIS[offset+1];
		else
			_hoops_CIRIS[1]=0.0f;
		if (param_width>2)
			_hoops_CIRIS[2] = _hoops_IIRIS[offset+2];
		else
			_hoops_CIRIS[2]=0.0f;
		params = _hoops_CIRIS;
		param_width = 3;
	}

	if (_hoops_ICAGA == null)
		_hoops_ICAGA = &nr->transform_rendition->_hoops_SPH->target;

	/* _hoops_ISGP _hoops_RH _hoops_ISCRC _hoops_HCGP. */
	if (_hoops_GCI == _hoops_GCARA) {
		if (txr->_hoops_PSR == _hoops_HSR)
			_hoops_PSR = _hoops_HSR;
		else
			_hoops_PSR = HK_PS_REFLECTION_VECTOR;
	}
	else if (_hoops_PSR == HK_PS_UNSPECIFIED)
		_hoops_PSR = HK_PS_UV;


	/*_hoops_RPP _hoops_CHHA _hoops_RHPS _hoops_APIP _hoops_SGH _hoops_CAPR*/
	if (!BIT(param_flags,_hoops_HSRSP) &&
		BIT(param_flags,_hoops_ASRSP)) {
		_hoops_PSR = HK_PS_UVW;
	}

	switch (_hoops_PSR) {
		case HK_PS_U: {
			param[0] = params[0];
			param[1] = 0.0f;
			param[2] = 0.0f;
		}	break;

		case HK_PS_NATURAL_UV:
		case HK_PS_UV: {
			param[0] = params[0];
			param[1] = params[1];
			param[2] = 0.0f;
		}	break;

		case HK_PS_UVW: {
			param[0] = params[0];
			param[1] = params[1];
			param[2] = params[2];
		}	break;

		case HK_PS_OBJECT: {
			_hoops_SGCC const &	matrix = nr->transform_rendition->_hoops_IPH;

			if (matrix->data._hoops_RAGR != _hoops_SGICR) {
				matrix->_hoops_PPRA ();

				HI_Compute_Transformed_Points (1, _hoops_ICAGA, &matrix->data._hoops_APRA->data.elements[0][0], (Point *)param);
				break;
			}
			/* _hoops_SHS _hoops_CARA == _hoops_GSSP */
		}	_hoops_HHHI;

		case HK_PS_WORLD: {
			param[0] = _hoops_ICAGA->x;
			param[1] = _hoops_ICAGA->y;
			param[2] = _hoops_ICAGA->z;
		}	break;

		/*_hoops_CPHR _hoops_GGGGR*/
		case HK_PS_SURFACE_NORMAL: {
			param[0] = plane->a;
			param[1] = plane->b;
			param[2] = plane->c;
		}	break;

		/*_hoops_CGH _hoops_IIP _hoops_IHPS*/
		case HK_PS_SPHERE:
		case HK_PS_CYLINDER: {
			param[0] = params[0];
			param[1] = params[1];
			param[2] = params[2];
		}	break;

		case HK_PS_REFLECTION_VECTOR: {
			_hoops_HHRA const *		_hoops_SPH;
			float				_hoops_GRRRC;
			Vector				_hoops_SGRRC;
			Vector const *		normal = (Vector const *)plane;
			_hoops_ARPA				_hoops_RRRRC, _hoops_ARRRC;
			Point				_hoops_PRRRC;

			_hoops_SPH = nr->transform_rendition->_hoops_SPH;
			HI_Validate_Matrix_Adjoint(&_hoops_SPH->_hoops_PRPA);

			_hoops_PRRRC.x = _hoops_HPRA (_hoops_SPH->_hoops_PRPA.elements, *_hoops_ICAGA);
			_hoops_PRRRC.y = _hoops_IPRA (_hoops_SPH->_hoops_PRPA.elements, *_hoops_ICAGA);
			_hoops_PRRRC.z = _hoops_CPRA (_hoops_SPH->_hoops_PRPA.elements, *_hoops_ICAGA);

#if 1		/* _hoops_HPCAR _hoops_IRGH _hoops_GSCHS */
			_hoops_SGRRC.x = _hoops_PRRRC.x;
			_hoops_SGRRC.y = _hoops_PRRRC.y;
			_hoops_SGRRC.z = _hoops_PRRRC.z + _hoops_SPH->_hoops_SRIR;

			QUICK_NORMALIZE (_hoops_SGRRC);
#else
			_hoops_SGRRC.x = 0.0f;
			_hoops_SGRRC.y = 0.0f;
			_hoops_SGRRC.z = 1.0f;
#endif

			_hoops_RRRRC.a = normal->x;
			_hoops_RRRRC.b = normal->y;
			_hoops_RRRRC.c = normal->z;
			_hoops_RRRRC.d = -(normal->x*_hoops_ICAGA->x +
								normal->y*_hoops_ICAGA->y +
								normal->z*_hoops_ICAGA->z);

			_hoops_ARRRC.a = _hoops_HRRRC (_hoops_SPH->_hoops_PRPA._hoops_APRA->data.elements, _hoops_RRRRC);
			_hoops_ARRRC.b = _hoops_IRRRC (_hoops_SPH->_hoops_PRPA._hoops_APRA->data.elements, _hoops_RRRRC);
			_hoops_ARRRC.c = _hoops_CRRRC (_hoops_SPH->_hoops_PRPA._hoops_APRA->data.elements, _hoops_RRRRC);

			QUICK_NORMALIZE (_hoops_ARRRC);

			_hoops_GRRRC = _hoops_SGRRC.x * _hoops_ARRRC.a +
					_hoops_SGRRC.y * _hoops_ARRRC.b +
					_hoops_SGRRC.z * _hoops_ARRRC.c;

			_hoops_GRRRC *= 2.0f;

			param[0] = _hoops_SGRRC.x - _hoops_GRRRC * _hoops_ARRRC.a;
			param[1] = _hoops_SGRRC.y - _hoops_GRRRC * _hoops_ARRRC.b;
			param[2] = _hoops_SGRRC.z - _hoops_GRRRC * _hoops_ARRRC.c;

			if (!BIT(nr->transform_rendition->flags, _hoops_PGCH))
				param[0] = -param[0];

		}	break;

		case _hoops_HSR: {
			_hoops_HHRA const *		_hoops_SPH;
			float				_hoops_GRRRC;
			Vector				_hoops_SGRRC;
			Vector const *		normal = (Vector const *)plane;

			_hoops_SPH = nr->transform_rendition->_hoops_SPH;

			_hoops_SGRRC.x = _hoops_ICAGA->x - _hoops_SPH->position.x;
			_hoops_SGRRC.y = _hoops_ICAGA->y - _hoops_SPH->position.y;
			_hoops_SGRRC.z = _hoops_ICAGA->z - _hoops_SPH->position.z;

			QUICK_NORMALIZE (_hoops_SGRRC);

			_hoops_GRRRC = _hoops_SGRRC.x * normal->x +
					_hoops_SGRRC.y * normal->y +
					_hoops_SGRRC.z * normal->z;

			_hoops_GRRRC *= 2.0f;

			param[0] = _hoops_SGRRC.x - _hoops_GRRRC * normal->x;
			param[1] = _hoops_SGRRC.y - _hoops_GRRRC * normal->y;
			param[2] = _hoops_SGRRC.z - _hoops_GRRRC * normal->z;

			if (!BIT(nr->transform_rendition->flags, _hoops_PGCH))
				param[0] = -param[0];
		}	break;

		default: {
			_hoops_IPR (HEC_TEXTURE, HES_INVALID_TYPE, "Unexpected texture parameterization source");
			param[0] = 0.0f;
			param[1] = 0.0f;
			param[2] = 0.0f;
		}	break;
	}

	if (_hoops_GAARP == _hoops_HCGRP) {
		if (_hoops_GCI == _hoops_GCARA)
			_hoops_GAARP = _hoops_CCGRP;
		else
			_hoops_GAARP = _hoops_ICGRP;
	}
	switch (_hoops_GAARP) {
		case _hoops_ICGRP:			/* _hoops_PRGH _hoops_IHRI _hoops_GAR _hoops_HRGR */
			break;

		case _hoops_CCGRP: {
			float					tmp;

			tmp = 1.0f - param[2];
			tmp = _hoops_SGIHR (param[0] * param[0] +
						param[1] * param[1] +
						tmp * tmp);
			if (tmp < 0.000001f)
				tmp = 0.000001f;
			tmp = 0.5f / tmp;

			param[0] = param[0] * tmp + 0.5f;
			param[1] = param[1] * tmp + 0.5f;
			param[2] = 0.0f;
		}	break;

		case _hoops_SCGRP: {
			/* _hoops_AHAA -1 _hoops_IS 1 _hoops_CRGR 0 _hoops_IS 1, _hoops_IPSH _hoops_HSRS "_hoops_PPAP" _hoops_IIHA _hoops_GPP _hoops_SSH */

			param[0] = 0.25f * param[0] + 0.25f;
			param[1] = 0.50f * param[1] + 0.50f;
			if (param[2] < 0.0f)
				param[0] += 0.5f;
			param[2] = 0.0f;
		}	break;

		case _hoops_GSGRP: {
			/* _hoops_SIGP */
		}	break;

		default: {
			_hoops_IPR (HEC_TEXTURE, HES_INVALID_TYPE,
							   "Unexpected texture layout");
		}	break;
	}

	if (!BIT (param_flags, _hoops_RSRSP)) {
		_hoops_GAAIR const *		tm = nr->_hoops_IRR->_hoops_APGH;

		if (txr->_hoops_GAGH) {
			/* _hoops_PS _hoops_HS _hoops_IRS _hoops_HH-_hoops_IIHA _hoops_RSGA */
			if (!BIT(txr->flags, _hoops_IPGH) &&
				ANYBIT (tm->matrix._hoops_RAGR, _hoops_CICH)) {
				/* _hoops_SGPR _hoops_GIPR _hoops_IRS _hoops_CAGH-_hoops_IIHA _hoops_RSGA _hoops_PPR _hoops_IRS _hoops_HH-_hoops_IIHA _hoops_RSGA. */
				if (tm->matrix._hoops_APRA == null)
					HI_Validate_Matrix_Adjoint (&tm->matrix);

				HI_Matmul_44_by_44(
					(float *)tm->matrix._hoops_APRA->data.elements,
					(float *)txr->_hoops_GAGH->matrix._hoops_APRA->data.elements,
					(float *)_hoops_RCRIS);
				_hoops_ACRIS = false;
			}
			else {
				/* _hoops_SGPR _hoops_RGAR _hoops_IRS _hoops_HH-_hoops_IIHA _hoops_RSGA */
				_hoops_AIGA(txr->_hoops_GAGH->matrix._hoops_APRA->data.elements, 16, float, _hoops_RCRIS);
				_hoops_ACRIS = false;
			}

		}
		else {
			/* _hoops_PS _hoops_GA'_hoops_RA _hoops_HS _hoops_IRS _hoops_HH-_hoops_IIHA _hoops_RSGA */
			if (!BIT(txr->flags, _hoops_IPGH) &&
				ANYBIT (tm->matrix._hoops_RAGR, _hoops_CICH)) {

				if (tm->matrix._hoops_APRA == null)
					HI_Validate_Matrix_Adjoint(&tm->matrix);

				/* _hoops_SGPR _hoops_RGAR _hoops_IRS _hoops_CAGH-_hoops_IIHA _hoops_RSGA */
				_hoops_AIGA(tm->matrix._hoops_APRA->data.elements, 16, float, _hoops_RCRIS);
				_hoops_ACRIS = false;
			}
		}
	}

	if (!_hoops_ACRIS) {
		_hoops_RSSH alter		_hoops_PCRIS[3];

		_hoops_PCRIS[0] = param[0];
		_hoops_PCRIS[1] = param[1];
		_hoops_PCRIS[2] = param[2];

		if (_hoops_RCRIS[0][3] != 0.0f || _hoops_RCRIS[1][3] != 0.0f || _hoops_RCRIS[2][3] != 0.0f) {
			/*_hoops_HCRIS*/
			float alter		_hoops_APCP;
#if 0
			/*_hoops_GHAP _hoops_RHCA _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_RHGS _hoops_CAGRH*/
			_hoops_APCP	= 1.0f / _hoops_ICRIS(txr->_hoops_GAGH->matrix._hoops_APRA, _hoops_PCRIS);
#else
			_hoops_APCP	= 1.0f / _hoops_ICRIS(_hoops_RCRIS, _hoops_PCRIS);
#endif
			param[0] = _hoops_CCRIS(_hoops_RCRIS, _hoops_PCRIS) * _hoops_APCP;
			param[1] = _hoops_SCRIS(_hoops_RCRIS, _hoops_PCRIS) * _hoops_APCP;
			param[2] = _hoops_GSRIS(_hoops_RCRIS, _hoops_PCRIS) * _hoops_APCP;
		}
		else {
			param[0] = _hoops_CCRIS(_hoops_RCRIS, _hoops_PCRIS);
			param[1] = _hoops_SCRIS(_hoops_RCRIS, _hoops_PCRIS);
			param[2] = _hoops_GSRIS(_hoops_RCRIS, _hoops_PCRIS);
		}
	}

#ifndef DISABLE_EXTENDED_TEXTURE
	/* _hoops_HIGIS _hoops_SSRA _hoops_HIAIH _hoops_CSCR _hoops_IGIR */
	if (BIT(image->flags, _hoops_SIRRP)) {
		param[0] *= 0.5f;
		param[1] *= 0.5f;
	}
#endif

	_hoops_SIRIS = image->width - 1;
	_hoops_GCRIS = image->height - 1;

	/* _hoops_RSRIS */
	switch (txr->_hoops_CGA) {
		case _hoops_SGA: {
			if (param[0] > 1.0f ||
				param[0] < 0.0f ||
				param[1] > 1.0f ||
				param[1] < 0.0f) {
				_hoops_CGIIH->red = _hoops_CGIIH->green = _hoops_CGIIH->blue = _hoops_CGIIH->alpha = 0;
				return;
			}
		}	break;
		case _hoops_ASCC: {
			if		(param[0] > 1.0f) param[0] = 1.0f;
			else if (param[0] < 0.0f) param[0] = 0.0f;

			if		(param[1] > 1.0f) param[1] = 1.0f;
			else if (param[1] < 0.0f) param[1] = 0.0f;

			if		(param[2] > 1.0f) param[2] = 1.0f;
			else if (param[2] < 0.0f) param[2] = 0.0f;
		}	break;
		case _hoops_PSGRP:
		case _hoops_ASGRP: {
			if ((param[0] = param[0] - (float)(long)param[0]) < 0.0f) param[0] += 1.0f;
			if ((param[1] = param[1] - (float)(long)param[1]) < 0.0f) param[1] += 1.0f;
			if ((param[2] = param[2] - (float)(long)param[2]) < 0.0f) param[2] += 1.0f;
		}	break;
	} /* _hoops_CICA (_hoops_SSRA) */

	/* _hoops_IHAA _hoops_RHPC _hoops_HIS _hoops_ISCP _hoops_RRRH _hoops_SPGA'_hoops_RA _hoops_ASRIS-_hoops_ISHP */
	param[1] = 1.0f - param[1];

	switch (txr->_hoops_PSCC) {
		case _hoops_HSCC: {
			int				index;
			_hoops_AIGH const *	_hoops_GAAC;

			index  = _hoops_PSCSH(param[1] * (_hoops_GCRIS + 0.9999f));

			if(index >= image->height)
				break;

			_hoops_GAAC = (_hoops_AIGH const *)image->rasters[index];

			index = _hoops_PSCSH(param[0] * (_hoops_SIRIS + 0.9999f));
			_hoops_GAAC += index;

			_hoops_CGIIH->red	 = _hoops_PSHGI(_hoops_GAAC->r);
			_hoops_CGIIH->green = _hoops_PSHGI(_hoops_GAAC->g);
			_hoops_CGIIH->blue	 = _hoops_PSHGI(_hoops_GAAC->b);
			_hoops_CGIIH->alpha = _hoops_PSHGI(_hoops_GAAC->a);
		}	break;

		case _hoops_HSGRP: {
			_hoops_AIGH const *	_hoops_PSRIS;
			_hoops_AIGH const *	_hoops_HSRIS;
			RGBA			_hoops_PHASI;
			RGBA			_hoops_HHASI;
			float			_hoops_ISRIS;
			int				_hoops_CSRIS;
			int				_hoops_SSRIS;
			float			_hoops_GGAIS;
			int				_hoops_RGAIS;
			int				_hoops_AGAIS;

			/* _hoops_ICAH _hoops_IS _hoops_SSS _hoops_RH _hoops_AIAA _hoops_RPIA _hoops_CGPC _hoops_PPR _hoops_SGCR _hoops_PAII
			** _hoops_RIGII _hoops_IS _hoops_RH _hoops_HACH _hoops_HAIR.
			*/
			switch (txr->_hoops_CGA) {
				case _hoops_SGA:
				case _hoops_ASCC:
				case _hoops_PSGRP: {
					_hoops_ISRIS = param[0] * _hoops_SIRIS;
					_hoops_CSRIS = _hoops_PSCSH(_hoops_ISRIS);  
					_hoops_ISRIS -= _hoops_CSRIS;
					if (_hoops_CSRIS >= _hoops_SIRIS) 
						_hoops_SSRIS = 0;
					else 
						_hoops_SSRIS = 1;

					_hoops_GGAIS = param[1] * _hoops_GCRIS;
					_hoops_RGAIS = _hoops_PSCSH(_hoops_GGAIS);
					_hoops_GGAIS -= _hoops_RGAIS;
					_hoops_AGAIS = _hoops_RGAIS + 1;
					if (_hoops_AGAIS > _hoops_GCRIS) 
						_hoops_AGAIS = _hoops_GCRIS;
				}	break;

				case _hoops_ASGRP: {
					_hoops_ISRIS = param[0] * image->width - 0.5f;
					_hoops_CSRIS = _hoops_PSCSH(_hoops_ISRIS);  
					_hoops_ISRIS -= _hoops_CSRIS;
					if (_hoops_CSRIS >= _hoops_SIRIS) 
						_hoops_SSRIS = - _hoops_SIRIS;
					else if (_hoops_ISRIS < 0.0f) {
						_hoops_ISRIS = - _hoops_ISRIS;
						_hoops_CSRIS = 0;
						_hoops_SSRIS = _hoops_SIRIS;
					}
					else 
						_hoops_SSRIS = 1;

					_hoops_GGAIS = param[1] * image->height - 0.5f;
					_hoops_RGAIS = _hoops_PSCSH(_hoops_GGAIS); 
					_hoops_GGAIS -= _hoops_RGAIS;
					if (_hoops_RGAIS >= _hoops_GCRIS) 
						_hoops_AGAIS = 0;
					else if (_hoops_GGAIS < 0.0f) {
						_hoops_GGAIS = - _hoops_GGAIS;
						_hoops_RGAIS = 0;
						_hoops_AGAIS = _hoops_GCRIS;
					}
					else 
						_hoops_AGAIS = _hoops_RGAIS + 1;
				}	break;

				default: {
					_hoops_IPR (HEC_TEXTURE, HES_INVALID_TYPE, "Unexpected texture tiling style");
					_hoops_ISRIS = 0.0f;
					_hoops_CSRIS = 0;
					_hoops_SSRIS = 0;
					_hoops_GGAIS = 0.0f;
					_hoops_RGAIS = 0;
					_hoops_AGAIS = 0;
				}	break;
			}

			if (_hoops_RGAIS<0) _hoops_RGAIS=0;
			if (_hoops_RGAIS>image->height-1) 
				_hoops_RGAIS=image->height-1;

			if (_hoops_AGAIS<0) _hoops_AGAIS=0;
			if (_hoops_AGAIS>image->height-1) 
				_hoops_AGAIS=image->height-1;

			_hoops_PSRIS = (_hoops_AIGH const *)image->rasters[_hoops_RGAIS] + _hoops_CSRIS;
			_hoops_HSRIS = _hoops_PSRIS + _hoops_SSRIS;

			_hoops_PHASI.red	 =	_hoops_PSHGI(_hoops_PSRIS->r) + _hoops_ISRIS *
							(_hoops_PSHGI(_hoops_HSRIS->r) - _hoops_PSHGI(_hoops_PSRIS->r));
			_hoops_PHASI.green =	_hoops_PSHGI(_hoops_PSRIS->g) + _hoops_ISRIS *
							(_hoops_PSHGI(_hoops_HSRIS->g) - _hoops_PSHGI(_hoops_PSRIS->g));
			_hoops_PHASI.blue	 =	_hoops_PSHGI(_hoops_PSRIS->b) + _hoops_ISRIS *
							(_hoops_PSHGI(_hoops_HSRIS->b) - _hoops_PSHGI(_hoops_PSRIS->b));
			_hoops_PHASI.alpha =	_hoops_PSHGI(_hoops_PSRIS->a) + _hoops_ISRIS *
							(_hoops_PSHGI(_hoops_HSRIS->a) - _hoops_PSHGI(_hoops_PSRIS->a));

			_hoops_PSRIS = (_hoops_AIGH const *)image->rasters[_hoops_AGAIS] + _hoops_CSRIS;
			_hoops_HSRIS = _hoops_PSRIS + _hoops_SSRIS;

			_hoops_HHASI.red	 =	_hoops_PSHGI(_hoops_PSRIS->r) + _hoops_ISRIS *
							(_hoops_PSHGI(_hoops_HSRIS->r) - _hoops_PSHGI(_hoops_PSRIS->r));
			_hoops_HHASI.green =	_hoops_PSHGI(_hoops_PSRIS->g) + _hoops_ISRIS *
							(_hoops_PSHGI(_hoops_HSRIS->g) - _hoops_PSHGI(_hoops_PSRIS->g));
			_hoops_HHASI.blue	 =	_hoops_PSHGI(_hoops_PSRIS->b) + _hoops_ISRIS *
							(_hoops_PSHGI(_hoops_HSRIS->b) - _hoops_PSHGI(_hoops_PSRIS->b));
			_hoops_HHASI.alpha =	_hoops_PSHGI(_hoops_PSRIS->a) + _hoops_ISRIS *
							(_hoops_PSHGI(_hoops_HSRIS->a) - _hoops_PSHGI(_hoops_PSRIS->a));

			_hoops_CGIIH->red = _hoops_PHASI.red + _hoops_GGAIS * (_hoops_HHASI.red - _hoops_PHASI.red);
			_hoops_CGIIH->green = _hoops_PHASI.green + _hoops_GGAIS * (_hoops_HHASI.green - _hoops_PHASI.green);
			_hoops_CGIIH->blue = _hoops_PHASI.blue + _hoops_GGAIS * (_hoops_HHASI.blue - _hoops_PHASI.blue);
			_hoops_CGIIH->alpha = _hoops_PHASI.alpha + _hoops_GGAIS * (_hoops_HHASI.alpha - _hoops_PHASI.alpha);
		}	break;

		case _hoops_GGRRP: {
			_hoops_AIGH const *	_hoops_GAAC;
			int				index;

			index  = (int)(param[1] * _hoops_GCRIS + _hoops_ASHGI());
			if (index > _hoops_GCRIS) index = _hoops_GCRIS;
			_hoops_GAAC = (_hoops_AIGH const *)image->rasters[index];

			index = (int)(param[0] * _hoops_SIRIS + _hoops_ASHGI());
			if (index > _hoops_SIRIS) index = _hoops_SIRIS;
			_hoops_GAAC += index;

			_hoops_CGIIH->red	 = _hoops_PSHGI(_hoops_GAAC->r);
			_hoops_CGIIH->green = _hoops_PSHGI(_hoops_GAAC->g);
			_hoops_CGIIH->blue	 = _hoops_PSHGI(_hoops_GAAC->b);
			_hoops_CGIIH->alpha = _hoops_PSHGI(_hoops_GAAC->a);
		}	break;

		default: {
			_hoops_IPR (HEC_TEXTURE, HES_INVALID_TYPE, "Unexpected texture interpolation filter");
		}	break;
	} /* _hoops_PRRAI (_hoops_PGAIS) */

#endif
#endif
}

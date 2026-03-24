/*
 * Copyright (c) 2000 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.70 2010-10-06 19:16:14 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hc_proto.h"
#include "hpserror.h"


/*_hoops_CHGSS _hoops_RAIGC*/

#define _hoops_SHGSS (1<<8)
#define _hoops_GIGSS (_hoops_SHGSS-1)

typedef struct _hoops_RIGSS {
	struct _hoops_RIGSS	*next;
	_hoops_RAARP		*_hoops_GCAH[_hoops_SHGSS];
	Font_Instance const	*_hoops_AGGGH;
	Font_Instance const	*instance;
	int						height;
	int						bolding_level;
	float					_hoops_IPGRP;
	float					rotation;
	float					width_scale;
	bool				antialias;
} _hoops_AIGSS;


GLOBAL_FUNCTION void HI_Init_Stencil_Cache(void) {
	HOOPS_WORLD->_hoops_SAHGI = 0;
}

local void _hoops_PIGSS (_hoops_AIGSS * sc) {
	int			i;

	sc->_hoops_AGGGH = 0;

	for (i=0; i<_hoops_SHGSS; i++) {
		if (sc->_hoops_GCAH[i]) {
			_hoops_RAARP	*stencil = sc->_hoops_GCAH[i];

			if (stencil) {
				while (stencil) {
					_hoops_RAARP *next = stencil->next;
					HI_Cleanup_Stencil(stencil, true);
					stencil = next;
				}
			}

			sc->_hoops_GCAH[i] = 0;
		}
	}
}

GLOBAL_FUNCTION void HI_Free_Stencil_Cache(void) {	
	_hoops_AIGSS		*_hoops_PPSIH;

	_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);	

	_hoops_PPSIH = (_hoops_AIGSS *) HOOPS_WORLD->_hoops_SAHGI;
	while (_hoops_PPSIH) {
		_hoops_AIGSS		*next = _hoops_PPSIH->next;

		_hoops_PIGSS (_hoops_PPSIH);

		FREE(_hoops_PPSIH, _hoops_AIGSS);

		_hoops_PPSIH = next;
	}

	HOOPS_WORLD->_hoops_SAHGI=0;

	_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);	
}

GLOBAL_FUNCTION void HI_Clean_Stencil_Cache (
	Font_Instance const	*instance) {
	_hoops_AIGSS		*_hoops_PPSIH;
	_hoops_AIGSS		**_hoops_HIGSS;

	_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);	

	_hoops_PPSIH = (_hoops_AIGSS *) HOOPS_WORLD->_hoops_SAHGI;
	_hoops_HIGSS = (_hoops_AIGSS **) &HOOPS_WORLD->_hoops_SAHGI;

	while (_hoops_PPSIH) {
		_hoops_AIGSS		*next = _hoops_PPSIH->next;

		if (_hoops_PPSIH->instance == instance) {
			*_hoops_HIGSS = _hoops_PPSIH->next;
			_hoops_PIGSS (_hoops_PPSIH);
			FREE(_hoops_PPSIH, _hoops_AIGSS);
		}
		else
			_hoops_HIGSS = &_hoops_PPSIH->next;

		_hoops_PPSIH = next;
	}

	_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);	
}

GLOBAL_FUNCTION _hoops_RAARP ** HI_Get_Stencil_Cache (
	Font_Instance const	*instance, 
	int						height, 
	int						bolding_level,
	float					_hoops_IPGRP, 
	float					rotation,
	float					width_scale,
	bool				antialias) {
	_hoops_AIGSS		*_hoops_PPSIH;
	_hoops_AIGSS		**_hoops_HIGSS;

	_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);	

	_hoops_HIGSS = (_hoops_AIGSS **) &HOOPS_WORLD->_hoops_SAHGI;
	_hoops_PPSIH = (_hoops_AIGSS *) HOOPS_WORLD->_hoops_SAHGI;

	while (_hoops_PPSIH) {
		if (_hoops_PPSIH->_hoops_AGGGH == instance->_hoops_AGGGH &&
			_hoops_PPSIH->height == height &&
			_hoops_PPSIH->bolding_level == bolding_level &&
			_hoops_PPSIH->_hoops_IPGRP == _hoops_IPGRP  &&
			_hoops_PPSIH->rotation == rotation &&
			_hoops_PPSIH->width_scale == width_scale &&
			_hoops_PPSIH->antialias == antialias) {

			/*_hoops_RGGGH _hoops_HIGR*/
			if (_hoops_PPSIH != HOOPS_WORLD->_hoops_SAHGI) {
				*_hoops_HIGSS = _hoops_PPSIH->next;
				_hoops_PPSIH->next = (_hoops_AIGSS *)HOOPS_WORLD->_hoops_SAHGI;
				HOOPS_WORLD->_hoops_SAHGI = (void*)_hoops_PPSIH;
			}

			break;
		}

		_hoops_HIGSS = &_hoops_PPSIH->next;
		_hoops_PPSIH = _hoops_PPSIH->next;
	}

	if (_hoops_PPSIH == null) {
		/* _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_RARP */
		ZALLOC_CACHED(_hoops_PPSIH, _hoops_AIGSS); 

		_hoops_PPSIH->_hoops_AGGGH = instance->_hoops_AGGGH;
		_hoops_PPSIH->instance = instance;
		_hoops_PPSIH->height = height;
		_hoops_PPSIH->bolding_level = bolding_level;
		_hoops_PPSIH->_hoops_IPGRP = _hoops_IPGRP;
		_hoops_PPSIH->rotation = rotation;
		_hoops_PPSIH->width_scale = width_scale;
		_hoops_PPSIH->antialias = antialias;

		_hoops_PPSIH->next = (_hoops_AIGSS *)HOOPS_WORLD->_hoops_SAHGI;
		HOOPS_WORLD->_hoops_SAHGI = (void*)_hoops_PPSIH;
	}

	_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);	

	return _hoops_PPSIH->_hoops_GCAH;
}

GLOBAL_FUNCTION _hoops_RAARP * HI_Lookup_Stencil(
	_hoops_RAARP	**_hoops_IIGSS, 
	unsigned short		_hoops_SRCSP) {

	_hoops_RAARP	*stencil;

	stencil = _hoops_IIGSS[_hoops_SRCSP & _hoops_GIGSS];

	while (stencil) {
		if (stencil->id == _hoops_SRCSP)
			return stencil;

		stencil = stencil->next;
	}

	return (_hoops_RAARP *) 0;
}


GLOBAL_FUNCTION void HI_Store_Stencil(
	_hoops_RAARP	**_hoops_IIGSS, 
	_hoops_RAARP	*stencil) {

	stencil->next = _hoops_IIGSS[stencil->id & _hoops_GIGSS];
	_hoops_IIGSS[stencil->id & _hoops_GIGSS] = stencil;
}


GLOBAL_FUNCTION int HI_Get_Stencil_Cache_Height (int height, bool _hoops_HPSIH) {
	if (height <= 2)
		return 2;

	if (_hoops_HPSIH) {
			if (height <= 32)
			return height;

		if (height <= 62)
			return 62;

		if (height <= 126)
			return 126;
	}
	else {
		if (height <= 126)
			return height;
	}

	return 254;
}



/*_hoops_APRAH _hoops_RRGR*/
GLOBAL_FUNCTION _hoops_RAARP * HI_Clone_Stencil(_hoops_RAARP const * stencil) 
{
	_hoops_RAARP * _hoops_CIGSS=0;
	int size;

	ALLOC(_hoops_CIGSS, _hoops_RAARP);

	if (!stencil) {
		ZERO_STRUCT(_hoops_CIGSS, _hoops_RAARP);
		return _hoops_CIGSS;
	}

	_hoops_RSAI (stencil, _hoops_RAARP, _hoops_CIGSS);

	if (stencil->bitmap) {
		size = stencil->height * stencil->_hoops_APARP;
		ALLOC_ARRAY (_hoops_CIGSS->bitmap, size, unsigned char);
		COPY_MEMORY (stencil->bitmap, size, _hoops_CIGSS->bitmap);
	}
	if (stencil->_hoops_AAARP) {
		ALLOC_ARRAY (_hoops_CIGSS->_hoops_AAARP, _hoops_CIGSS->_hoops_PAARP, unsigned char);
		COPY_MEMORY (stencil->_hoops_AAARP, _hoops_CIGSS->_hoops_PAARP, _hoops_CIGSS->_hoops_AAARP);
	}
	if (stencil->txr)
		_hoops_PRRH(_hoops_CIGSS->txr);

	return _hoops_CIGSS;
}


GLOBAL_FUNCTION void HI_Cleanup_Stencil(_hoops_RAARP * stencil, bool _hoops_HRPHP) 
{
	if (stencil->bitmap) {
		int		size = stencil->height * stencil->_hoops_APARP;	
		FREE_ARRAY (stencil->bitmap, size, unsigned char);
		stencil->bitmap=0;
	}

	if (stencil->_hoops_AAARP) {
		FREE_ARRAY (stencil->_hoops_AAARP, stencil->_hoops_PAARP, unsigned char);
		stencil->_hoops_AAARP=0;
	}

	if (stencil->txr) {
		_hoops_HPRH(stencil->txr);
		stencil->txr=0;
	}

	if (_hoops_HRPHP)
		FREE (stencil, _hoops_RAARP);
}



GLOBAL_FUNCTION void HI_Make_RLE_Stencil(_hoops_RAARP alter* stencil) 
{
#define _hoops_SIGSS 4096
	unsigned char _hoops_GCGSS[_hoops_SIGSS];	
	unsigned char * _hoops_AAARP;
	unsigned char * _hoops_RCGSS;
	int _hoops_RSIGR = _hoops_SIGSS;
	int x, y, n;

	if (stencil->height > 255 || stencil->width > 255) return;

	n = 0;
	_hoops_AAARP = _hoops_GCGSS;

#if 0
	SET_MEMORY(stencil->bitmap, stencil->height*stencil->_hoops_APARP, 255);
#endif

	if (stencil->_hoops_PPARP == 1) {
		int _hoops_ACGSS=0,_hoops_PCGSS=0,_hoops_HCGSS;

		_hoops_AAARP[n++] = 0xFF;

		for (y=0; y<stencil->height; y++) {
			unsigned char const *row;

			row = stencil->bitmap + y * stencil->_hoops_APARP;
			_hoops_HCGSS = 0;

			for (x=0; x<stencil->width; x++) {
				if ((row[x >> 3] & (0x0080 >> (x & 0x0007)))) {
					if (_hoops_HCGSS==0) {
						_hoops_ACGSS = x;
						_hoops_PCGSS = y;
						_hoops_HCGSS = 1;
					}
					else {
						_hoops_HCGSS++;
						if (_hoops_HCGSS == 0xFF) {
							if (n+4 > _hoops_RSIGR) {
								ALLOC_ARRAY (_hoops_RCGSS, _hoops_RSIGR*2, unsigned char);
								COPY_MEMORY (_hoops_AAARP, _hoops_RSIGR, _hoops_RCGSS);
								if (_hoops_AAARP != _hoops_GCGSS) FREE_ARRAY (_hoops_AAARP, _hoops_RSIGR, unsigned char);
								_hoops_RSIGR *= 2;
								_hoops_AAARP = _hoops_RCGSS;
							}
							_hoops_AAARP[n++] = _hoops_ACGSS;
							_hoops_AAARP[n++] = _hoops_PCGSS;
							_hoops_AAARP[n++] = _hoops_HCGSS;
							_hoops_HCGSS = 0;
						}
					}
				}
				else {
					if (_hoops_HCGSS>0) {
						if (n+4 > _hoops_RSIGR) {
							ALLOC_ARRAY (_hoops_RCGSS, _hoops_RSIGR*2, unsigned char);
							COPY_MEMORY (_hoops_AAARP, _hoops_RSIGR, _hoops_RCGSS);
							if (_hoops_AAARP!=_hoops_GCGSS) FREE_ARRAY (_hoops_AAARP, _hoops_RSIGR, unsigned char);
							_hoops_RSIGR *= 2;
							_hoops_AAARP = _hoops_RCGSS;
						}
						_hoops_AAARP[n++] = _hoops_ACGSS;
						_hoops_AAARP[n++] = _hoops_PCGSS;
						_hoops_AAARP[n++] = _hoops_HCGSS;
						_hoops_HCGSS = 0;
					}
				}
			}
			if (_hoops_HCGSS>0) {
				if (n+4 > _hoops_RSIGR) {
					ALLOC_ARRAY (_hoops_RCGSS, _hoops_RSIGR*2, unsigned char);
					COPY_MEMORY (_hoops_AAARP, _hoops_RSIGR, _hoops_RCGSS);
					if (_hoops_AAARP != _hoops_GCGSS) FREE_ARRAY (_hoops_AAARP, _hoops_RSIGR, unsigned char);
					_hoops_RSIGR *= 2;
					_hoops_AAARP = _hoops_RCGSS;
				}
				_hoops_AAARP[n++] = _hoops_ACGSS;
				_hoops_AAARP[n++] = _hoops_PCGSS;
				_hoops_AAARP[n++] = _hoops_HCGSS;
				_hoops_HCGSS = 0;
			}
		}
	}
	else {
		struct _hoops_ICGSS{
			_hoops_ICGSS *next;
			char x;
			char y;
		};

		_hoops_ICGSS *	_hoops_CCGSS[256];
		int				_hoops_ICI[256];
		int				i, max, total;

		SET_MEMORY(_hoops_CCGSS, sizeof(_hoops_CCGSS), 0);
		SET_MEMORY(_hoops_ICI, sizeof(_hoops_ICI), 0);

		for (y=0; y<stencil->height; y++) {
			unsigned char const *row;

			row = stencil->bitmap + y * stencil->_hoops_APARP;

			for (x=0; x<stencil->width; x++) {
				if (row[x]) {
					_hoops_ICGSS *	_hoops_SCGSS;

					ALLOC(_hoops_SCGSS, _hoops_ICGSS);
					_hoops_SCGSS->x = x;
					_hoops_SCGSS->y = y;
					_hoops_SCGSS->next = _hoops_CCGSS[row[x]];
					_hoops_CCGSS[row[x]] = _hoops_SCGSS;
					_hoops_ICI[row[x]]++;
				}
			}
		}

		total = 0;
		max = 0;
		for (i=0; i<256; i++) { 
			if (_hoops_ICI[i]) {
				total += _hoops_ICI[i];
				if (_hoops_ICI[i] > _hoops_ICI[max])
					max = i;
			}
		}
		if ((total*4)+1 > _hoops_RSIGR) {
			_hoops_RSIGR = (total*4)+1;
			ALLOC_ARRAY (_hoops_AAARP, _hoops_RSIGR, unsigned char);
		}

		n = 0;
		_hoops_AAARP[n++] = 0x00;

		if (total>0) {
			while (1) {
				i = 0;
				while (_hoops_CCGSS[max]) {
					_hoops_ICGSS *_hoops_SCGSS;

					if (i == 0) {
						_hoops_AAARP[n++]=max;
						_hoops_AAARP[n++]=_hoops_AHIA(_hoops_ICI[max],255);	
					}

					if (++i == 255)
						i=0;
					_hoops_ICI[max]--;
					total--;

					_hoops_SCGSS = _hoops_CCGSS[max];
					_hoops_CCGSS[max] = _hoops_SCGSS->next;

					_hoops_AAARP[n++] = _hoops_SCGSS->x;
					_hoops_AAARP[n++] = _hoops_SCGSS->y;

					FREE(_hoops_SCGSS, _hoops_ICGSS);
				}
				
				if (total == 0) 
					break;

				max = 0;
				for (i=0; i<256; i++) { 
					if (_hoops_ICI[i] > _hoops_ICI[max])
						max = i;
				}
			}
		}
	}

	ALLOC_ARRAY (_hoops_RCGSS, n, unsigned char);
	COPY_MEMORY (_hoops_AAARP, n, _hoops_RCGSS);
	if (_hoops_AAARP != _hoops_GCGSS) 
		FREE_ARRAY (_hoops_AAARP, _hoops_RSIGR, unsigned char);
	stencil->_hoops_AAARP = _hoops_RCGSS;
	stencil->_hoops_PAARP = n;
}


#define _hoops_GSGSS 4096
#define _hoops_RSGSS  256*256


local void _hoops_GAPCS(_hoops_RAARP alter *stencil, bool antialias)
{
	_hoops_RCR alter *	txr = HI_Clone_Texture(0);
	Image alter *	image;
	int nw, nh;
	int i, j, _hoops_CAAIP;

	txr->flags |= _hoops_IAPS;
	HOOPS_WORLD->_hoops_ACPIR++;

	if (!antialias) {
		txr->flags |= _hoops_RARRP;
		txr->_hoops_PSCC = _hoops_HSCC;
	}

	txr->flags |= _hoops_AARRP;
	/*_hoops_CAGRC->_hoops_RAPCS = _hoops_AAPCS;*/
	txr->_hoops_RARH = _hoops_PARH;

	txr->_hoops_CGA = _hoops_ASCC;

	nw = _hoops_HSHGI(_hoops_IAAA(stencil->width+2, 4));
	nh = _hoops_HSHGI(_hoops_IAAA(stencil->height+2, 4));

	nw = nh = _hoops_IAAA(nw, nh);

	HI_Create_Image (&txr->image,
					 null,
					 nw, nh,
					 Image_RGBA32, 0,
					 _hoops_RRPGI, null);

	image=txr->image;
	
	image->flags |= _hoops_SHCC;

	for (i = 0; i < image->height; i++) {
		_hoops_AIGH alter *_hoops_GPRIS = (_hoops_AIGH alter *)image->rasters[i];
		for (j = 0; j < image->width; j++) {
			_hoops_GPRIS[j].a = 0;
			_hoops_GPRIS[j].r = 255;
			_hoops_GPRIS[j].g = 255;
			_hoops_GPRIS[j].b = 255;
		}
	}

	_hoops_CAAIP = image->height - stencil->height;

	if (stencil->_hoops_PPARP == 1) {
		for (i = 0; i < stencil->height; i++) {
			unsigned char const *row = stencil->bitmap + i * stencil->_hoops_APARP;
			for (j = 0; j < stencil->width; j++) {
				if ((row[j >> 3] & (0x0080 >> (j & 0x0007)))) {
					_hoops_AIGH alter *_hoops_GPRIS = (_hoops_AIGH *) image->rasters[i+_hoops_CAAIP-1];
					_hoops_GPRIS[j].a = 255;
				}
			}
		}
	}
	else {
		for (i = 0; i < stencil->height; i++) {
			unsigned char const *row = stencil->bitmap + i * stencil->_hoops_APARP;
			for (j = 0; j < stencil->width; j++) {
				if (row[j]) {
					_hoops_AIGH alter *_hoops_GPRIS = (_hoops_AIGH *) image->rasters[i+_hoops_CAAIP-1];
					_hoops_GPRIS[j].a = row[j];
				}
			}
		}
	}

#if 0
	/* _hoops_HISRA _hoops_AHCRR */
	for (j = 0; j < stencil->width; j++) {
		_hoops_AIGH alter *_hoops_GPRIS = (_hoops_AIGH *) image->rasters[0+_hoops_CAAIP-1];
		_hoops_GPRIS[j].a = 255;
	}
	for (j = 0; j < stencil->width; j++) {
		_hoops_AIGH alter *_hoops_GPRIS = (_hoops_AIGH *) image->rasters[stencil->height-1+_hoops_CAAIP-1];
		_hoops_GPRIS[j].a = 255;
	}
	for (i = 0; i < stencil->height; i++) {
		_hoops_AIGH alter *_hoops_GPRIS = (_hoops_AIGH *) image->rasters[i+_hoops_CAAIP-1];
		_hoops_GPRIS[0].a = 255;
	}
	for (i = 0; i < stencil->height; i++) {
		_hoops_AIGH alter *_hoops_GPRIS = (_hoops_AIGH *) image->rasters[i+_hoops_CAAIP-1];
		_hoops_GPRIS[stencil->width-1].a = 255;
	}
#endif
	
	stencil->txr = txr;
}

local void _hoops_ASGSS(
	Net_Rendition const &		in_nr,
	Point const *				points,
	_hoops_RAARP const *		stencil) {
	Net_Rendition				nr = in_nr;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_RSSH					params[8];
	float						_hoops_ACCRR,_hoops_ISPI,_hoops_PCCRR,_hoops_CSPI,_hoops_PAPCS,_hoops_HAPCS;
	int							i;

	_hoops_HHCR alter &			_hoops_IHCR = nr.Modify()->transform_rendition.Modify(1<<24);
	_hoops_GCIR alter &		_hoops_RCIR = nr->_hoops_CPP.Modify();
	_hoops_CIGA alter &				_hoops_SIGA = nr->_hoops_IHA.Modify();
	_hoops_HHA alter &			mat = _hoops_SIGA->_hoops_CHA.Modify();

	_hoops_SIGA->_hoops_AGP = null;
	nr->_hoops_RGP &= ~T_LIGHTS_FOR_FACES;

	if (!ANYBIT(nr->current, _hoops_GSSHP|_hoops_RSSHP) &&
		BIT(dc->flags, _hoops_AASHP)) {
		_hoops_RCIR->_hoops_PRH._hoops_HRH = false;
		_hoops_RCIR->_hoops_PRH.style = Transparency_STYLE_BLENDING;
	}
	else {
		_hoops_RCIR->_hoops_PRH._hoops_HRH = true;
		_hoops_RCIR->_hoops_PRH.style = Transparency_STYLE_BLENDING;
	}
	
	HI_Free_Diffuse_Channel_List (mat->_hoops_SCA);
	mat->_hoops_SCA = null;
	for (i=0; i<_hoops_GAGRA; i++)
		if (mat->texture[i] != null) {
			_hoops_HPRH(mat->texture[i]);
			mat->texture[i] = null;
		}

	_hoops_IHCR->flags |= _hoops_ISH;
	_hoops_IHCR->_hoops_CHIH = 0.0f;

	if (!stencil->txr)
		_hoops_GAPCS((_hoops_RAARP alter *)stencil, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_CRAAP));

	mat->_hoops_SCA = HI_New_Diffuse_Channel (stencil->txr);
	mat->_hoops_ARIR = true;

	mat->_hoops_SCA->flags |= _hoops_PRA|_hoops_PPIR;
	mat->_hoops_CSHR.red = _hoops_PSHGI(nr->_hoops_SISI->color._hoops_HRIR.r);
	mat->_hoops_CSHR.green = _hoops_PSHGI(nr->_hoops_SISI->color._hoops_HRIR.g);
	mat->_hoops_CSHR.blue = _hoops_PSHGI(nr->_hoops_SISI->color._hoops_HRIR.b);

	/* _hoops_RHCHH _hoops_IH _hoops_CSCR _hoops_HCPC _hoops_APSP _hoops_IGIR _hoops_PPR _hoops_AHC */
	_hoops_PCCRR = (float)stencil->width/(float)stencil->txr->image->width;
	_hoops_CSPI = (float)stencil->height/(float)stencil->txr->image->height;

	_hoops_ACCRR = 1.0f/(float)stencil->txr->image->width;
	_hoops_ISPI = 1.0f/(float)stencil->txr->image->height;

	_hoops_PCCRR += _hoops_ACCRR;
	_hoops_CSPI += _hoops_ISPI;

	/* _hoops_CIAAI _hoops_IS _hoops_GGCR _hoops_IHH _hoops_HGPC _hoops_AIR _hoops_IH _hoops_GGAR _hoops_IAPCS */
	_hoops_PAPCS = (float)(stencil->width+2)/(float)stencil->width; 
	_hoops_HAPCS = (float)(stencil->height+2)/(float)stencil->height;

	_hoops_PAPCS *= _hoops_ACCRR;
	_hoops_HAPCS *= _hoops_ISPI;

	_hoops_ACCRR -= _hoops_PAPCS;
	_hoops_ISPI -= _hoops_HAPCS;
	_hoops_PCCRR += _hoops_PAPCS;
	_hoops_CSPI += _hoops_HAPCS;

	params[0] = _hoops_ACCRR;
	params[1] = _hoops_ISPI;

	params[2] = _hoops_ACCRR;
	params[3] = _hoops_CSPI;

	params[4] = _hoops_PCCRR;
	params[5] = _hoops_ISPI;

	params[6] = _hoops_PCCRR;
	params[7] = _hoops_CSPI;

	if (dc->_hoops_HCAGH || !BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_CRAAP))
		_hoops_HCRGA(nr, 4, points, 0, 0, params, 2, _hoops_RSRSP|_hoops_ASRSP|_hoops_HSRSP);
	else
		HD_Hide_DC_Textured_Polytris(nr, 4, points, 0, 0, params, 2, _hoops_RSRSP|_hoops_ASRSP|_hoops_HSRSP);

#if 0
	_hoops_SCGGA(nr, 4, (DC_Point*)points);
#endif
}

GLOBAL_FUNCTION void HD_Std_DC_Stenciled_Quad (
	Net_Rendition const &		in_nr,
	DC_Point const *			points,
	_hoops_RAARP const *		stencil) {
	Net_Rendition				nr = in_nr;
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	Int_Rectangle const &		_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;
	DC_Point					_hoops_PSGSS[_hoops_GSGSS];
	DC_Point alter *			_hoops_GSICP = _hoops_PSGSS;
	DC_Point alter *			_hoops_SSRP;
	RGBAS32						_hoops_HSGSS[_hoops_GSGSS];
	RGBAS32 alter *				_hoops_GCICS = _hoops_HSGSS;
	RGBAS32 alter *				_hoops_IASGR;
	int							width = (int)(points[2].x - points[0].x + 0.001f);// + 1.49f);
	int							height = (int)(points[1].y - points[0].y + 0.001f); /* +0.001 _hoops_IS _hoops_CRHR _hoops_SIRCP _hoops_HHGS*/
	int							_hoops_ISGSS = height;
	int							x = (int) points[1].x;
	int							y = (int) points[1].y;
	int							z = (int) points[0].z;
	int							_hoops_CSGSS, _hoops_SSGSS, _hoops_GGRSS, _hoops_RGRSS;
	int							ii, _hoops_ICRHH;

	if (_hoops_HRCIR->rotation - stencil->rotation == 0 && (width == 0 || height == 0) )
		return;

#if 1
	if (_hoops_HRCIR->rotation-stencil->rotation != 0.0f || 
			_hoops_HRCIR->width_scale-stencil->width_scale != 0.0f) {

		_hoops_ASGSS(nr,points,stencil);

		return;
	}
#endif

	if (!stencil->_hoops_AAARP && stencil->height<=255 && stencil->width<=255)
		HI_Make_RLE_Stencil((_hoops_RAARP alter*)stencil);

	if (stencil->_hoops_PPARP != 8) {
		if (nr->_hoops_AHP != _hoops_HRCIR->_hoops_RGIHP) {
			if (_hoops_HRCIR->_hoops_RGIHP == null) {
				Display_Context const *		dc = nr->_hoops_SRA;

				((_hoops_IGCSR alter &)_hoops_HRCIR)->_hoops_RGIHP = nr->_hoops_AHP;
				Line_Rendition alter &		_hoops_ASAIP = ((_hoops_IGCSR alter &)_hoops_HRCIR)->_hoops_RGIHP.Modify();

				_hoops_ASAIP->_hoops_CHA = _hoops_HRCIR->_hoops_CHA;
				_hoops_ASAIP->color = _hoops_HRCIR->color;
				HD_Replace_Line_Style(_hoops_ASAIP, nr->_hoops_GCSHP->_hoops_IHRIP);
				_hoops_ASAIP->weight = dc->_hoops_PGCC._hoops_IHHSR;
				//_hoops_RGISR->_hoops_GGCS = _hoops_IRAP;
			}

			nr.Modify()->_hoops_AHP = _hoops_HRCIR->_hoops_RGIHP;
		}
	}
	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS))
		nr.Modify()->transform_rendition.Modify()->flags |= _hoops_AIHS;

	if (width*height > _hoops_GSGSS) {
		if (width*height > _hoops_RSGSS) {
			/* _hoops_APSP _hoops_HRGR **_hoops_APHHH** _hoops_AHSC.  _hoops_AA _hoops_SCH _hoops_III _hoops_HPP _hoops_III */
			/* _hoops_HIH _hoops_RPP _hoops_RGCI **_hoops_AGRSS** _hoops_AHSC _hoops_SAHR _hoops_ASRC */
			if(width > 16384)
				return;
			ALLOC_ARRAY (_hoops_GSICP, width, DC_Point);
			if (stencil->_hoops_PPARP == 8)
				ALLOC_ARRAY (_hoops_GCICS, width, RGBAS32);
			_hoops_ISGSS = 1;
		}
		else {
			/* _hoops_APSP _hoops_HRGR _hoops_AHSC, _hoops_HIH _hoops_HAR _hoops_HIS _hoops_AHSC _hoops_SGS _hoops_SR _hoops_HHGC _hoops_IS _hoops_AA _hoops_SCH _hoops_III _hoops_HPP _hoops_III */
			ALLOC_ARRAY (_hoops_GSICP, width*height, DC_Point);
			if (stencil->_hoops_PPARP == 8)
				ALLOC_ARRAY (_hoops_GCICS, width*height, RGBAS32);
		}
	}
	_hoops_SSRP = _hoops_GSICP;
	_hoops_IASGR = _hoops_GCICS;


	_hoops_SSGSS = _hoops_IAAA (0, _hoops_GPHH.left - (int)points[1].x);
	_hoops_RGRSS	= _hoops_AHIA (width, _hoops_GPHH.right+1 - (int)points[1].x);
	_hoops_CSGSS = _hoops_IAAA (0, (int)points[1].y - _hoops_GPHH.top);
	_hoops_GGRSS	= _hoops_AHIA (height, (int)points[1].y - (_hoops_GPHH.bottom-1));

#if 0
	_hoops_SCGGA (nr, 4, points);
#endif
	
	if (width != stencil->width ||
		height != stencil->height ||
		points[0].x != points[1].x || points[2].x != points[3].x ||
		points[0].y != points[2].y || points[1].y != points[3].y ||
		_hoops_ISGSS != height) {
		/* _hoops_HAR _hoops_GGR _hoops_IHGP _hoops_SRSGR*/
		int		_hoops_PGRSS, _hoops_HGRSS;
		float	_hoops_PIIH, _hoops_HIIH;
		int		_hoops_IGRSS, _hoops_CGRSS;

		_hoops_PIIH = ((float)stencil->width/(float)width);
		_hoops_HIIH = ((float)stencil->height/(float)height);

		if (stencil->_hoops_PPARP == 8)
			nr.Modify()->_hoops_CPP.Modify()->_hoops_PRH._hoops_HRH = true;

		_hoops_IGRSS = _hoops_CSGSS;
		_hoops_CGRSS = _hoops_AHIA (_hoops_GGRSS, _hoops_CSGSS+_hoops_ISGSS);
		while (_hoops_IGRSS < _hoops_GGRSS) {
			if (stencil->_hoops_PPARP == 1) {
				for (ii=_hoops_IGRSS; ii<_hoops_CGRSS; ++ii) {
					unsigned char const		*row;

					_hoops_HGRSS = (int)(_hoops_HIIH * ii);
					row = stencil->bitmap + _hoops_HGRSS * stencil->_hoops_APARP;

					for (_hoops_ICRHH=_hoops_SSGSS; _hoops_ICRHH<_hoops_RGRSS; ++_hoops_ICRHH) {
						_hoops_PGRSS = (int)(_hoops_PIIH * _hoops_ICRHH);
						if ((row[_hoops_PGRSS>>3] & (0x0080>>(_hoops_PGRSS & 0x0007)))) {
							_hoops_SSRP->x = (float)(x + _hoops_ICRHH);
							_hoops_SSRP->y = (float)(y - ii);
							_hoops_SSRP->z = (float)z;
							++_hoops_SSRP;
						}
					}
				}
			}
			else if (stencil->_hoops_PPARP == 8) {
				for (ii=_hoops_IGRSS; ii<_hoops_CGRSS; ++ii) {
					unsigned char const		*row;

					_hoops_HGRSS = (int)(_hoops_HIIH * ii);
					row = stencil->bitmap + _hoops_HGRSS * stencil->_hoops_APARP;

					for (_hoops_ICRHH=_hoops_SSGSS; _hoops_ICRHH<_hoops_RGRSS; ++_hoops_ICRHH) {
						_hoops_PGRSS = (int)(_hoops_PIIH * _hoops_ICRHH);
						if (row[_hoops_PGRSS]) {
							_hoops_SSRP->x = (float)(x + _hoops_ICRHH);
							_hoops_SSRP->y = (float)(y - ii);
							_hoops_SSRP->z = (float)z;
							++_hoops_SSRP;
							_hoops_IASGR->r = _hoops_HRCIR->color._hoops_HRIR.r;
							_hoops_IASGR->g = _hoops_HRCIR->color._hoops_HRIR.g;
							_hoops_IASGR->b = _hoops_HRCIR->color._hoops_HRIR.b;
							_hoops_IASGR->a = row[_hoops_PGRSS];
							_hoops_IASGR++;
						}
					}
				}
			}

			if (_hoops_SSRP != _hoops_GSICP) {
				if (stencil->_hoops_PPARP == 8)
					_hoops_RIGGA (nr, _hoops_SSRP-_hoops_GSICP, _hoops_GSICP, _hoops_GCICS, false);
				else
					_hoops_AIGGA (nr, _hoops_SSRP-_hoops_GSICP, _hoops_GSICP);
			}

			_hoops_IGRSS += _hoops_ISGSS;
			_hoops_CGRSS += _hoops_ISGSS;
			_hoops_SSRP = _hoops_GSICP;
			_hoops_IASGR = _hoops_GCICS;
		}
	}
	else {
		if (stencil->_hoops_AAARP) { 
			int _hoops_HCGSS, _hoops_SGRSS, _hoops_GRRSS;
			unsigned int n=0;

			if (stencil->_hoops_AAARP[n++] == 0x00) {
				while (n < stencil->_hoops_PAARP) {
					char alpha = stencil->_hoops_AAARP[n++];
					_hoops_HCGSS = stencil->_hoops_AAARP[n++];

					while (_hoops_HCGSS-- > 0) {
						_hoops_SGRSS = x + stencil->_hoops_AAARP[n++];
						_hoops_GRRSS = y - stencil->_hoops_AAARP[n++];

						if (_hoops_GRRSS >= _hoops_GPHH.bottom && _hoops_GRRSS <= _hoops_GPHH.top) {
							if (_hoops_GPHH.left <= _hoops_SGRSS && _hoops_GPHH.right >= _hoops_SGRSS) {
								_hoops_SSRP->x = (float)_hoops_SGRSS;
								_hoops_SSRP->y = (float)_hoops_GRRSS;
								_hoops_SSRP->z = (float)z;
								++_hoops_SSRP;

								_hoops_IASGR->r = _hoops_HRCIR->color._hoops_HRIR.r;
								_hoops_IASGR->g = _hoops_HRCIR->color._hoops_HRIR.g;
								_hoops_IASGR->b = _hoops_HRCIR->color._hoops_HRIR.b;
								_hoops_IASGR->a = alpha;
								++_hoops_IASGR;
							}
						}
					}
				}
			}
			else {
				while (n<stencil->_hoops_PAARP) {
					_hoops_SGRSS = x + stencil->_hoops_AAARP[n++];
					_hoops_GRRSS = y - stencil->_hoops_AAARP[n++];
					_hoops_HCGSS = stencil->_hoops_AAARP[n++];			

					if (_hoops_GRRSS >= _hoops_GPHH.bottom && _hoops_GRRSS <= _hoops_GPHH.top) {
						int _hoops_RRRSS = _hoops_SGRSS;
						int _hoops_ARRSS = _hoops_SGRSS+_hoops_HCGSS;

						if (_hoops_GPHH.left > _hoops_RRRSS) 
							_hoops_RRRSS = _hoops_GPHH.left;
						if (_hoops_GPHH.right+1 < _hoops_ARRSS) 
							_hoops_ARRSS = _hoops_GPHH.right+1;

						for (;_hoops_RRRSS<_hoops_ARRSS;_hoops_RRRSS++) {
							_hoops_SSRP->x = (float)_hoops_RRRSS;
							_hoops_SSRP->y = (float)_hoops_GRRSS;
							_hoops_SSRP->z = (float)z;
							++_hoops_SSRP;

						}
					}
				}
			}
		} 
		else if (stencil->_hoops_PPARP == 1) {
			for (ii=_hoops_CSGSS; ii<_hoops_GGRSS; ++ii) {
				unsigned char const		*row;

				row = stencil->bitmap + ii * stencil->_hoops_APARP;

				for (_hoops_ICRHH=_hoops_SSGSS; _hoops_ICRHH<_hoops_RGRSS; ++_hoops_ICRHH) {
					if ((row[_hoops_ICRHH>>3] & (0x0080>>(_hoops_ICRHH & 0x0007)))) {
						_hoops_SSRP->x = (float)(x + _hoops_ICRHH);
						_hoops_SSRP->y = (float)(y - ii);
						_hoops_SSRP->z = (float)z;
						++_hoops_SSRP;
					}
				}
			}
		}
		else if (stencil->_hoops_PPARP == 8) {
			for (ii=_hoops_CSGSS; ii<_hoops_GGRSS; ++ii) {
				unsigned char const		*row;

				row = stencil->bitmap + ii * stencil->_hoops_APARP;

				for (_hoops_ICRHH=_hoops_SSGSS; _hoops_ICRHH<_hoops_RGRSS; ++_hoops_ICRHH) {
					if (row[_hoops_ICRHH]) {
						_hoops_SSRP->x = (float)(x + _hoops_ICRHH);
						_hoops_SSRP->y = (float)(y - ii);
						_hoops_SSRP->z = (float)z;
						++_hoops_SSRP;
						_hoops_IASGR->r = _hoops_HRCIR->color._hoops_HRIR.r;
						_hoops_IASGR->g = _hoops_HRCIR->color._hoops_HRIR.g;
						_hoops_IASGR->b = _hoops_HRCIR->color._hoops_HRIR.b;
						_hoops_IASGR->a = row[_hoops_ICRHH];
						_hoops_IASGR++;
					}
				}
			}
		}

		if (_hoops_SSRP != _hoops_GSICP) {
			if (stencil->_hoops_PPARP == 8) {
				nr.Modify()->_hoops_CPP.Modify()->_hoops_PRH._hoops_HRH = true;
				_hoops_RIGGA (nr, _hoops_SSRP-_hoops_GSICP, _hoops_GSICP, _hoops_GCICS, false);
			}
			else
				_hoops_AIGGA (nr, _hoops_SSRP-_hoops_GSICP, _hoops_GSICP);
		}
	}

	if (width*height > _hoops_GSGSS) {
		if (width*height > _hoops_RSGSS) {
			FREE_ARRAY (_hoops_GSICP, width, DC_Point);
			if (stencil->_hoops_PPARP == 8)
				FREE_ARRAY (_hoops_GCICS, width, RGBAS32);
		}
		else {
			FREE_ARRAY (_hoops_GSICP, width*height, DC_Point);
			if (stencil->_hoops_PPARP == 8)
				FREE_ARRAY (_hoops_GCICS, width*height, RGBAS32);
		}
	}
}

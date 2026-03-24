
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
 * $Id: obf_tmp.txt 1.280 2011-01-22 06:23:53 covey Exp $
 */

#include "windows_wrapper.h"	// _hoops_CGRI <_hoops_SPHGR._hoops_GGHR>, _hoops_PIHA _hoops_RCPS _hoops_SRS :(

#include "hoops.h"

#include "hc_proto.h"
#include "database.h"
#include "driver.h"
#include "filedata.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "patterns.h"
#include "please.h"
#include "tandt.h"
#include "phedron.h"



#ifdef FREETYPE

#include "ft2build.h"
#ifdef VMS_SYSTEM
#include "freetype.h"
#include "ftglyph.h"
#include "ftoutln.h"
#else
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#endif



#undef CONST

struct _hoops_GRCGI {
	FT_Face						face;
	int							_hoops_RRCGI;
	struct _hoops_ARCGI *	_hoops_PRCGI;
	int							offset;
	unsigned short				_hoops_HRCGI;
	int							_hoops_IRCGI;
};

#define _hoops_CRCGI 72


#define _hoops_SRCGI 0.005
#define _hoops_GACGI 0.030


typedef struct _hoops_RACGI {
	struct _hoops_RACGI *	next;
	char *							name;
	char *							_hoops_AACGI;
	char *							_hoops_SSISR;
	char *							_hoops_PACGI;
	char *							_hoops_HACGI;
	char *							_hoops_IACGI;
	int								index;
	_hoops_IHGRP					encoding;
	int								_hoops_CACGI;
} _hoops_SACGI;

typedef struct _hoops_GPCGI {
	struct _hoops_GPCGI *	next;
	char *					name;
} _hoops_RPCGI;

typedef struct _hoops_APCGI {
	_hoops_SACGI *		_hoops_HGPIR;
	_hoops_RPCGI *			_hoops_PPCGI;
	bool					_hoops_HPCGI;
}	_hoops_IPCGI;

#define _hoops_CPCGI 256
#define _hoops_SPCGI 0xFF

typedef struct _hoops_ARCGI {
	struct _hoops_GHCGI *	item[_hoops_CPCGI];
	int									_hoops_RHCGI;
	int									bolding_level;
} _hoops_AHCGI;


typedef struct _hoops_PHCGI{
	Point			bbox[4];
	Polyedge *		polyedge;
} _hoops_HHCGI;

typedef struct _hoops_GHCGI {
	Point *						points;
	int *						face_list;
	int							point_count;
	int							face_count;
	float						_hoops_IHCGI;
	float						_hoops_CHCGI;
	Tristrip *					_hoops_PCHAR;
	_hoops_HHCGI *	_hoops_SHCGI;
	unsigned short				_hoops_SRCSP;
} _hoops_GICGI;




local void _hoops_RICGI (char const * message, int error) {
	char	buffer[2048];

	sprintf (buffer, "freetype error: %d %s", error, message);

	_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, buffer);
}

local FT_Library * _hoops_AICGI (bool _hoops_PHIPP) {
	_hoops_PPGGH *	_hoops_PICGI;
	FT_Library *			_hoops_HICGI;
	int						error;

	if ((_hoops_PICGI = (_hoops_PPGGH *)HOOPS_WORLD->global_font_data_freetype) == null) {
		_hoops_IPCGI *		_hoops_IPGGH = null;

		if (!_hoops_PHIPP)
			return null;

		ZALLOC (_hoops_PICGI, _hoops_PPGGH);
		HOOPS_WORLD->global_font_data_freetype = _hoops_PICGI;

		ZALLOC (_hoops_HICGI, FT_Library);
		_hoops_PICGI->_hoops_HPGGH = (void *)_hoops_HICGI;

		error = FT_Init_FreeType(_hoops_HICGI);

		if (error) {
			_hoops_RICGI("FT_Init_Freetype failed",error);

			FREE (_hoops_PICGI->_hoops_HPGGH, FT_Library);
			FREE (_hoops_PICGI, _hoops_PPGGH);
			HOOPS_WORLD->global_font_data_freetype = null;
			return null;
		}

		ZALLOC(_hoops_IPGGH, _hoops_IPCGI);
		_hoops_PICGI->_hoops_IPGGH = _hoops_IPGGH;
	}
	else
		_hoops_HICGI = (FT_Library *)_hoops_PICGI->_hoops_HPGGH;

	return _hoops_HICGI;
}


local unsigned short
_hoops_IICGI (FT_Face face, unsigned long _hoops_CICGI) {
	unsigned short		result = FT_Get_Char_Index (face, _hoops_CICGI);

	if (result == 0 &&
		face->charmap->platform_id == 0 &&		// _hoops_HHH _hoops_GRAA-_hoops_HPRGR _hoops_GSPIP _hoops_SGH _hoops_RH _hoops_CPAGI _hoops_PHIAH
		face->charmap->encoding_id == 0 &&		// _hoops_CCA _hoops_RH "_hoops_SHIR" _hoops_SICGI, _hoops_HRII _hoops_HSAR _hoops_CPAGI 2.0+
		face->charmap->encoding == FT_ENCODING_UNICODE &&	// _hoops_GA'_hoops_RA _hoops_SHAC _hoops_RPP _hoops_HAR _hoops_GPP _hoops_RH _hoops_SHIR _hoops_ARCR
		_hoops_CICGI < 0x0100) {					// _hoops_RGAR _hoops_HPPR _hoops_RGR _hoops_IH _hoops_CSCS _hoops_HPS
		// _hoops_HPPR _hoops_HCPRA _hoops_SIGSP _hoops_IS _hoops_PCCP _hoops_IIIAR _hoops_HIIA
		if (FT_Select_Charmap (face, FT_ENCODING_APPLE_ROMAN) == 0) {
			result = FT_Get_Char_Index (face, _hoops_CICGI);
			FT_Select_Charmap (face, FT_ENCODING_UNICODE);
		}

// _hoops_GA'_hoops_RA _hoops_RRP _hoops_RGR _hoops_IHH _hoops_RRGR _hoops_IH _hoops_HA, _hoops_GAR _hoops_HCR _hoops_RH _hoops_PISC _hoops_GSPIP _hoops_HCR _hoops_AHGS _hoops_IS _hoops_IPHR _hoops_CCA _hoops_GCCGI-_hoops_RCCGI
// _hoops_PPR _hoops_RGR _hoops_CHH _hoops_SAHR _hoops_GGCR _hoops_ACCGI _hoops_GPP _hoops_RH _hoops_PCCGI _hoops_IIGR _hoops_GRAA-_hoops_PHIPR _hoops_HPS
#if 0
		if (result == 0) {	// _hoops_RPP _hoops_RH _hoops_GCCGI-_hoops_RCCGI _hoops_HIIA _hoops_HGGC _hoops_SARS'_hoops_RA _hoops_IPHR...
			// _hoops_GRH _hoops_RSAIP _hoops_IH _hoops_HHH _hoops_GSPIP _hoops_SGS _hoops_AHGS _hoops_IS _hoops_PPIP _hoops_HCCGI-_hoops_PIGGP _hoops_ICCGI _hoops_GGR _hoops_IPSP-_hoops_PAPR _hoops_GC
			_hoops_CICGI |= 0xF000;
			result = FT_Get_Char_Index (face, _hoops_CICGI);
		}
#endif
	}
	return result;
}


local float _hoops_CCCGI (_hoops_GRCGI * _hoops_SCCGI, float height) {
	float			_hoops_GSCGI;
	unsigned short	_hoops_SRCSP;
	int				_hoops_IRPRH;
	int				error;
	FT_Glyph		glyph;
	FT_BBox			bbox;

	_hoops_GSCGI = 10.0f * height;

	if (_hoops_GSCGI < 32.0f)
		_hoops_GSCGI = 32.0f;

	if (_hoops_GSCGI > 5000.0f)
		_hoops_GSCGI = 5000.0f;

	_hoops_SRCSP = _hoops_IICGI (_hoops_SCCGI->face, _hoops_SCCGI->offset+_hoops_SCCGI->_hoops_HRCGI);

	error = FT_Set_Char_Size (_hoops_SCCGI->face, 0, (long)_hoops_GSCGI*64, _hoops_CRCGI, _hoops_CRCGI);
	error = FT_Load_Glyph (_hoops_SCCGI->face, _hoops_SRCSP, _hoops_SCCGI->_hoops_RRCGI);

	error = FT_Get_Glyph (_hoops_SCCGI->face->glyph, &glyph);
	FT_Glyph_Get_CBox (glyph, ft_glyph_bbox_gridfit, &bbox);

	(void)error;		/* _hoops_ARP _hoops_HIH _hoops_HAR _hoops_IGI _hoops_IAII */

	_hoops_IRPRH = (bbox.yMax - bbox.yMin) / 64;

	FT_Done_Glyph (glyph);

	if (_hoops_IRPRH == 0)	/* _hoops_PSP '_hoops_SPCR' -- _hoops_IIGSH _hoops_HRCSR? */
		return 1.0f;
	else
		return _hoops_GSCGI / (float)_hoops_IRPRH;
}


GLOBAL_FUNCTION void HD_Get_Freetype_Font_Bounding (
	Font_Instance const *		instance,
	_hoops_SASC alter &		_hoops_RSHIH) {
	_hoops_GPGGH const *		_hoops_RSCGI = (_hoops_GPGGH const *)instance->_hoops_GAASR;
	_hoops_GRCGI const *	_hoops_SCCGI = (_hoops_GRCGI*)_hoops_RSCGI->_hoops_RPGGH;

	_hoops_RSHIH.min.x = _hoops_SCCGI->face->bbox.xMin;
	_hoops_RSHIH.min.y = _hoops_SCCGI->face->bbox.yMin;
	_hoops_RSHIH.min.z = 0.0f;
	_hoops_RSHIH.max.x = _hoops_SCCGI->face->bbox.xMax;
	_hoops_RSHIH.max.y = _hoops_SCCGI->face->bbox.yMax;
	_hoops_RSHIH.max.z = 0.0f;
}


GLOBAL_FUNCTION void * HD_Load_Freetype_Font (
	Display_Context const *		dc,
	char const *				name,
	Font_Instance alter *		instance) {
	_hoops_GPGGH alter *		_hoops_RSCGI;
	_hoops_GRCGI *		_hoops_SCCGI;
	_hoops_PPGGH *			_hoops_PICGI;
	FT_Library *				_hoops_HPGGH;
	_hoops_IPCGI *				_hoops_IPGGH;
	_hoops_SACGI *			font_name;
	int							error;

	UNREFERENCED (dc);

	instance->_hoops_HRGGH = true;

	if ((_hoops_HPGGH = _hoops_AICGI(true)) == null)
		return 0;

	_hoops_PICGI = (_hoops_PPGGH *)HOOPS_WORLD->global_font_data_freetype;

	_hoops_IPGGH = (_hoops_IPCGI *) _hoops_PICGI->_hoops_IPGGH;
	font_name = _hoops_IPGGH->_hoops_HGPIR;

	if ((_hoops_RSCGI = (_hoops_GPGGH alter *)instance->family->data) == null) {
		_hoops_AAPIR *	_hoops_ASCGI;
		_hoops_HCRPR			_hoops_PSCGI;
		_hoops_HCRPR			filename;
		FILE *			fp = null;
		char			_hoops_HSCGI[4096];

		while (font_name) {
			_hoops_SACGI *next = font_name->next;

			if (font_name->_hoops_IACGI != null &&
				(font_name->name && _hoops_IGGPA (name, font_name->name)) ||
				(font_name->_hoops_AACGI && _hoops_IGGPA (name, font_name->_hoops_AACGI)) ||
				(font_name->_hoops_SSISR && _hoops_IGGPA (name, font_name->_hoops_SSISR)) ||
				(font_name->_hoops_PACGI && _hoops_IGGPA (name, font_name->_hoops_PACGI)) ||
				(font_name->_hoops_HACGI && _hoops_IGGPA (name, font_name->_hoops_HACGI))) {

				if ((fp = fopen (font_name->_hoops_IACGI, "rb")) != null) {
					_hoops_AAHR (font_name->_hoops_IACGI, _hoops_HSCGI);
					break;
				}
			}

			font_name=next;
		}

		if (fp == null) {
			_hoops_ASCGI = HOOPS_WORLD->_hoops_AAGHP;

			/* _hoops_HPPR _hoops_IS _hoops_SSS _hoops_RH _hoops_HRCSR */
			while (_hoops_ASCGI) {
				HI_Copy_Name (&_hoops_ASCGI->name, &_hoops_PSCGI);
				HI_Copy_Chars_To_Name (name, &filename);
				HI_Add_Path_Delimiter (&_hoops_PSCGI, &filename);
				Sprintf_NN (_hoops_HSCGI, "%n%n", &_hoops_PSCGI, &filename);
				_hoops_RGAIR (filename);
				_hoops_RGAIR (_hoops_PSCGI);

				if ((fp = fopen (_hoops_HSCGI, "rb")) != null)
					break;

				_hoops_ASCGI = _hoops_ASCGI->next;
			}
		}

		/* _hoops_PAH'_hoops_RA _hoops_SSS _hoops_RH _hoops_HRCSR */
		/* _hoops_GAAP _hoops_AICRR _hoops_PGHPR _hoops_SCH? */
		if (fp == null)
			return 0;

		/* _hoops_CHCAR _hoops_SR _hoops_HS _hoops_GSGI _hoops_RH _hoops_HRCSR */
		fclose (fp);

		ZALLOC (_hoops_RSCGI, _hoops_GPGGH);

		_hoops_ICAI(_hoops_RSCGI);

		HI_Copy_Chars_To_Name (_hoops_HSCGI, &_hoops_RSCGI->_hoops_APGGH);

		if (font_name->_hoops_SSISR != null)
			HI_Copy_Chars_To_Name (font_name->_hoops_SSISR, &_hoops_RSCGI->_hoops_SSISR);

		ZALLOC (_hoops_RSCGI->_hoops_RPGGH, _hoops_GRCGI);

		_hoops_SCCGI = (_hoops_GRCGI*)_hoops_RSCGI->_hoops_RPGGH;
		_hoops_SCCGI->_hoops_HRCGI = 'X';

		/* _hoops_AGCR _hoops_ASRC _hoops_GRAA 0 _hoops_GPP _hoops_RIHH */

		if ((error = FT_New_Face (*_hoops_HPGGH, _hoops_HSCGI, instance->_hoops_SSPAR, &_hoops_SCCGI->face)) != 0) {
			_hoops_RGAIR(_hoops_RSCGI->_hoops_APGGH);
			_hoops_RGAIR(_hoops_RSCGI->_hoops_SSISR);
			FREE (_hoops_RSCGI->_hoops_RPGGH, _hoops_GRCGI);
			FREE (_hoops_RSCGI, _hoops_GPGGH);
			return 0;
		}

		if (!_hoops_SCCGI->face->charmap) {
			if (FT_Select_Charmap (_hoops_SCCGI->face, FT_ENCODING_APPLE_ROMAN))
				FT_Set_Charmap (_hoops_SCCGI->face, _hoops_SCCGI->face->charmaps[0]);
		}

		//_hoops_RPP (_hoops_ISCGI (_hoops_RSIRR, "_hoops_CSCGI._hoops_SSCGI") ||
		//	_hoops_ISCGI (_hoops_RSIRR, "_hoops_GGSGI._hoops_SSCGI") ||
		//	_hoops_ISCGI (_hoops_RSIRR, "_hoops_RGSGI._hoops_SSCGI"))
		//	_hoops_AGSGI (_hoops_PGSGI->_hoops_HSP, _hoops_HGSGI);

		if (_hoops_SCCGI->face->family_name &&
			_hoops_IGGPA (_hoops_SCCGI->face->family_name, "FBTol")) {
			FT_Set_Charmap (_hoops_SCCGI->face, _hoops_SCCGI->face->charmaps[1]);
			_hoops_SCCGI->offset = 0xF000;
			_hoops_SCCGI->_hoops_HRCGI = 'o';
		}

		if (_hoops_IGGPA (name, "mingliu.ttc") ||
			_hoops_IGGPA (name, "dffn_r3.ttc") ||
			_hoops_IGGPA (name, "kaiu.ttf")	||
			_hoops_IGGPA (name, "msgothic.ttc")	||
			_hoops_IGGPA (name, "pmingliu.ttf"))
			_hoops_SCCGI->_hoops_RRCGI = FT_LOAD_DEFAULT |
									FT_LOAD_IGNORE_GLOBAL_ADVANCE_WIDTH | FT_LOAD_NO_BITMAP;
		else
			_hoops_SCCGI->_hoops_RRCGI = FT_LOAD_FORCE_AUTOHINT | FT_LOAD_NO_BITMAP;

		instance->_hoops_GRGGH = _hoops_CCCGI(_hoops_SCCGI, instance->_hoops_RACSR);

		/* _hoops_IGSGI _hoops_CGH _hoops_SHH _hoops_SHPR _hoops_CGSGI */
		error = FT_Set_Char_Size (_hoops_SCCGI->face, 0, (long)(instance->_hoops_RACSR*64), _hoops_CRCGI, _hoops_CRCGI);
	}
	else	/* _hoops_SR _hoops_HS _hoops_RH _hoops_HRCSR _hoops_AIAH */
		_hoops_CAHS (_hoops_RSCGI);

	(void)error;		/* _hoops_ARP _hoops_HIH _hoops_HAR _hoops_IGI _hoops_IAII */

	return (void *) _hoops_RSCGI;
}



local void _hoops_SGSGI (_hoops_AHCGI * _hoops_PRCGI) {
	for (int i=0; i<_hoops_CPCGI; i++) {
		_hoops_GICGI * item = _hoops_PRCGI->item[i];

		if (item) {
			if (item->points) {
				if (item->_hoops_PCHAR != null && item->points == item->_hoops_PCHAR->points) {
					item->_hoops_PCHAR->points = null;
					item->_hoops_PCHAR->point_count = 0;
				}
				FREE_ARRAY_ALIGNED (item->points, item->point_count, Point, 16);
			}
			if (item->face_list)
				FREE_ARRAY (item->face_list, item->face_count, int);
			if (item->_hoops_SHCGI) {
				Polyedge *pe = item->_hoops_SHCGI->polyedge;
				if (pe && _hoops_ISAI (pe) == 0) {
					HI_Free_Polyedge (pe);
				}
				FREE (item->_hoops_SHCGI, _hoops_HHCGI);
			}
			if (item->_hoops_PCHAR) {
				if (_hoops_ISAI (item->_hoops_PCHAR) == 0)
					HI_Free_Tristrip (item->_hoops_PCHAR);
			}
			FREE (item, _hoops_GICGI);
		}
	}
}

local void _hoops_GRSGI (
	_hoops_GRCGI *	_hoops_SCCGI,
	int						_hoops_RHCGI,
	int						bolding_level,
	float					_hoops_IPGRP,
	float					rotation,
	float					width_scale) {
	_hoops_AHCGI *		_hoops_PRCGI = _hoops_SCCGI->_hoops_PRCGI;

	UNREFERENCED (_hoops_IPGRP);
	UNREFERENCED (rotation);
	UNREFERENCED (width_scale);

	if (_hoops_PRCGI &&
		_hoops_PRCGI->_hoops_RHCGI == _hoops_RHCGI &&
		_hoops_PRCGI->bolding_level == bolding_level) return;

	if (!_hoops_PRCGI)
		ZALLOC_CACHED (_hoops_PRCGI, _hoops_AHCGI);
	else
		_hoops_SGSGI(_hoops_PRCGI);

	ZERO_ARRAY (&_hoops_PRCGI->item[0], _hoops_CPCGI, _hoops_GICGI *);
	_hoops_PRCGI->_hoops_RHCGI = _hoops_RHCGI;
	_hoops_PRCGI->bolding_level = bolding_level;

	_hoops_SCCGI->_hoops_PRCGI = _hoops_PRCGI;
}


local void _hoops_RRSGI (_hoops_GRCGI *_hoops_SCCGI) {
	_hoops_AHCGI *	_hoops_PRCGI = _hoops_SCCGI->_hoops_PRCGI;

	_hoops_SGSGI (_hoops_PRCGI);
	FREE (_hoops_PRCGI, _hoops_AHCGI);

	_hoops_SCCGI->_hoops_PRCGI = 0;
}


GLOBAL_FUNCTION void HD_Unload_Freetype_Font (
	Display_Context const	*dc,
	Font_Instance alter		*instance) {
	_hoops_PPGGH *	_hoops_PICGI;
	_hoops_GPGGH *		_hoops_RSCGI = (_hoops_GPGGH *) instance->_hoops_GAASR;
	_hoops_GRCGI *	_hoops_SCCGI = (_hoops_GRCGI*) _hoops_RSCGI->_hoops_RPGGH;

	UNREFERENCED (dc);

	if ((_hoops_PICGI = (_hoops_PPGGH *)HOOPS_WORLD->global_font_data_freetype) == null) {
		_hoops_RICGI ("Request to unload Freetype font without global data", 0);
		return;
	}

	if (_hoops_ISAI (_hoops_RSCGI) == 0) {
		if (_hoops_SCCGI->_hoops_PRCGI)
			_hoops_RRSGI (_hoops_SCCGI);

		FT_Done_Face (_hoops_SCCGI->face);

		HI_Clean_Stencil_Cache(instance);

		_hoops_RGAIR (_hoops_RSCGI->_hoops_APGGH);
		_hoops_RGAIR (_hoops_RSCGI->_hoops_SSISR);
		FREE (_hoops_RSCGI->_hoops_RPGGH, _hoops_GRCGI);
		FREE (_hoops_RSCGI, _hoops_GPGGH);
	}
}

GLOBAL_FUNCTION unsigned short HD_Map_Freetype_Char_Index(
	Font_Instance const	*	specific,
	Karacter				_hoops_IPCSR) {
	_hoops_GPGGH *			_hoops_RSCGI = (_hoops_GPGGH *) specific->_hoops_GAASR;
	_hoops_GRCGI *		_hoops_SCCGI = (_hoops_GRCGI*)_hoops_RSCGI->_hoops_RPGGH;

	return _hoops_IICGI (_hoops_SCCGI->face, _hoops_SCCGI->offset+_hoops_IPCSR);
}

GLOBAL_FUNCTION _hoops_RAARP * HD_Make_Freetype_Stencil(
	Net_Rendition const &	nr,
	Font_Instance const *	instance,
	unsigned short			_hoops_SRCSP,
	int						_hoops_RHSIH,
	int						bolding_level,
	float					xrslant,
	float					xrrotation,
	float					xrwidth_scale,
	bool					antialias) {
	_hoops_GPGGH *			_hoops_RSCGI = (_hoops_GPGGH *) instance->_hoops_GAASR;
	_hoops_GRCGI *	_hoops_SCCGI = (_hoops_GRCGI*)_hoops_RSCGI->_hoops_RPGGH;
	int						error;
	float					_hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR;
	_hoops_RAARP *		stencil;
	FT_Matrix				matrix;
	FT_Vector				vector;
	FT_Glyph				glyph;
	FT_BitmapGlyph			glyph_bitmap;
	FT_BBox					bbox;
	int						bitmap_height = (int)(_hoops_RHSIH * instance->_hoops_GRGGH);

	UNREFERENCED(nr);

	if (_hoops_SCCGI->_hoops_IRCGI != bitmap_height*64) {
		_hoops_SCCGI->_hoops_IRCGI = bitmap_height*64;
		error = FT_Set_Char_Size (_hoops_SCCGI->face, 0, _hoops_SCCGI->_hoops_IRCGI, _hoops_CRCGI, _hoops_CRCGI);
	}

	/* _hoops_CSGA _hoops_HSAIP _hoops_SRS */
	_hoops_RICH (xrslant, _hoops_GGHCR, _hoops_AGHCR);
	_hoops_IPGRP = _hoops_GGHCR / _hoops_AGHCR;
	/* _hoops_HA _hoops_HGCR _hoops_IHSPA & _hoops_HHSPA _hoops_IIGR _hoops_ICSA */
	_hoops_RICH (xrrotation, _hoops_GGHCR, _hoops_AGHCR);

	ZALLOC (stencil, _hoops_RAARP);

	stencil->rotation = xrrotation;
	stencil->width_scale = xrwidth_scale;

	error = FT_Load_Glyph (_hoops_SCCGI->face, _hoops_SRCSP, _hoops_SCCGI->_hoops_RRCGI);
	error = FT_Get_Glyph (_hoops_SCCGI->face->glyph, &glyph);

	if (bolding_level > 0)
		FT_Outline_Embolden(&((FT_OutlineGlyph)glyph)->outline, bolding_level*64);

	FT_Glyph_Get_CBox (glyph, ft_glyph_bbox_gridfit, &bbox);

	stencil->_hoops_HAARP = (int)(((float)_hoops_SCCGI->face->glyph->metrics.horiAdvance/64.0f) * _hoops_AGHCR * xrwidth_scale);
	stencil->_hoops_IAARP = (int)(((float)_hoops_SCCGI->face->glyph->metrics.horiAdvance/64.0f) * _hoops_GGHCR * xrwidth_scale);

	if (bbox.xMax == 0 && bbox.xMin == 0) {
		FT_Done_Glyph (glyph);

		FREE(stencil, _hoops_RAARP);
		return 0;
	}

	matrix.xx = (long)(_hoops_AGHCR * xrwidth_scale * 65536);
	matrix.xy = (long)(((-_hoops_GGHCR* xrwidth_scale)+_hoops_IPGRP*_hoops_AGHCR) * 65536);
	matrix.yx = (long)(_hoops_GGHCR * 65536);
	matrix.yy = (long)((_hoops_AGHCR+_hoops_IPGRP*_hoops_GGHCR) * 65536);

	FT_Glyph_Transform (glyph, &matrix, 0);
	FT_Glyph_Get_CBox (glyph, ft_glyph_bbox_gridfit, &bbox);

	vector.x = -(bbox.xMin-128);
	vector.y = -(bbox.yMin-128);

	FT_Glyph_Transform(glyph, 0, &vector);

	if (antialias)
		error = FT_Glyph_To_Bitmap (&glyph, FT_RENDER_MODE_NORMAL, 0, 1);
	else
		error = FT_Glyph_To_Bitmap (&glyph, FT_RENDER_MODE_MONO, 0, 1);

	if (error) {
		FT_Done_Glyph (glyph);

		FREE(stencil, _hoops_RAARP);
		return 0;
	}

	glyph_bitmap = (FT_BitmapGlyph)glyph;

	stencil->_hoops_CAARP = -(bbox.xMin-128) / 64;
	stencil->_hoops_SAARP = -(bbox.yMin-128) / 64;
	stencil->width = glyph_bitmap->bitmap.width;
	stencil->height = glyph_bitmap->bitmap.rows;
	stencil->_hoops_APARP = glyph_bitmap->bitmap.pitch;
	if (glyph_bitmap->bitmap.pixel_mode == FT_PIXEL_MODE_MONO)
		stencil->_hoops_PPARP = 1;
	else
		stencil->_hoops_PPARP = 8;
	stencil->id = _hoops_SRCSP;

	stencil->_hoops_RPARP = 3;

	ALLOC_ARRAY (stencil->bitmap, (stencil->height*stencil->_hoops_APARP), unsigned char);
	COPY_MEMORY(glyph_bitmap->bitmap.buffer, stencil->height*stencil->_hoops_APARP, stencil->bitmap);

	FT_Done_Glyph (glyph);

	(void)error;		/* _hoops_ARP _hoops_HIH _hoops_HAR _hoops_IGI _hoops_IAII */

	return stencil;
}


GLOBAL_FUNCTION bool HD_Freetype_Will_Use_Stencil(
	Net_Rendition const &		nr,
	Font_Instance const *		specific) {
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	Display_Context const *		dc = nr->_hoops_SRA;
	bool						antialias = BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_CRAAP);

	_hoops_RCPAP				_hoops_IISGH = _hoops_HRCIR->_hoops_CSPAP[1];

	/* _hoops_ASIGA _hoops_CAGRH */
	if (nr->_hoops_IRR->_hoops_SRI == _hoops_PRAAP)
		antialias = false;

	if (_hoops_HRCIR->_hoops_SCPAP > 0) {
		int	_hoops_GHRGR = (int)(HD_Compute_Generic_Size (nr,
										_hoops_HRCIR->_hoops_SCPAP,
										_hoops_HRCIR->_hoops_PGHAP,
										1.0f, (_hoops_HRCIR->transform == FT_FULL),
										0, true) + 0.5f);

		if (specific->_hoops_ISISR <= _hoops_GHRGR)
			_hoops_IISGH = _hoops_HRCIR->_hoops_CSPAP[0];
	}

	if (_hoops_IISGH == _hoops_GRHRP && BIT(dc->_hoops_PGCC.flags, _hoops_ISRIP))
		_hoops_IISGH = _hoops_SGHRP;

	/*_hoops_RGR _hoops_HRGR _hoops_CAS _hoops_RH _hoops_RPGP _hoops_IH _hoops_ARSGI _hoops_IAGA*/
	if (_hoops_HRCIR->outline || _hoops_IISGH == _hoops_SGHRP || _hoops_IISGH == _hoops_RRHRP || (_hoops_HRCIR->transform == FT_FULL && !antialias))
		return false;

	return true;
}

/*
_hoops_GGHSA _hoops_SRPC _hoops_PRSGI(
	_hoops_CIHRR _hoops_RCIC		&_hoops_SCII,
	_hoops_HRSGI _hoops_RCIC		*_hoops_HRCSR) {
	_hoops_AIIC	_hoops_IRSGI, _hoops_APPS;

	_hoops_RPP (_hoops_SCII->_hoops_CRSGI->_hoops_HIHP == _hoops_SRSGI) {
		_hoops_IRSGI = _hoops_APPS = _hoops_HRCSR->_hoops_PSSSP * _hoops_HRCSR->_hoops_SIISR;

		_hoops_RPP (!_hoops_HRCSR->_hoops_GASGI) {
			_hoops_RPP (_hoops_APPS < 24.0f)
				_hoops_APPS = 24.0f;

			_hoops_RPP (_hoops_APPS > 256.0f)
				_hoops_APPS = 256.0f;
		}
		_hoops_SHS {
			_hoops_ASHPA _hoops_RCIC	*	_hoops_IASPH = _hoops_SCII->_hoops_RICC->_hoops_SICH;
			_hoops_GPIP _hoops_RCIC	*	_hoops_SARA = _hoops_SCII->_hoops_RICC->_hoops_SARA;

			_hoops_RPP (_hoops_IASPH->_hoops_GCCH != 0.0f) {
				_hoops_APPS *= _hoops_IASPH->_hoops_GCCH;
			}
			_hoops_SHS {
				_hoops_AIIC			_hoops_RASGI, _hoops_AASGI, _hoops_PASGI, _hoops_HASGI;

				_hoops_RASGI = (_hoops_AIIC)_hoops_IASGI ((_hoops_CASGI _hoops_RCIC *)&_hoops_IASPH->_hoops_IAGH[0][0]);
				_hoops_AASGI = (_hoops_AIIC)_hoops_IASGI ((_hoops_CASGI _hoops_RCIC *)&_hoops_IASPH->_hoops_IAGH[1][0]);
				_hoops_PASGI = (_hoops_AIIC)_hoops_IASGI ((_hoops_CASGI _hoops_RCIC *)&_hoops_IASPH->_hoops_IAGH[2][0]);

				_hoops_HASGI = _hoops_SASGI(_hoops_SASGI(_hoops_RASGI, _hoops_AASGI), _hoops_PASGI);

				_hoops_APPS *= _hoops_HASGI;
			}

			_hoops_APPS /= _hoops_SARA->_hoops_PCPCR*0.5f;

			_hoops_APPS = (_hoops_SCSH)_hoops_GPSGI ((_hoops_SCSH)_hoops_APPS, _hoops_IHPR);
		}
	}
	_hoops_SHS
		_hoops_IRSGI = _hoops_APPS = (_hoops_SCSH)(_hoops_HRCSR->_hoops_PSSSP * _hoops_HRCSR->_hoops_SIISR);


	((_hoops_HRSGI _hoops_RAPC *)_hoops_HRCSR)->_hoops_RPSGI = _hoops_APPS;
	_hoops_RPP (_hoops_APPS > 0)
		((_hoops_HRSGI _hoops_RAPC *)_hoops_HRCSR)->_hoops_APSGI = (_hoops_AIIC)_hoops_IRSGI/(_hoops_AIIC)_hoops_APPS;
	_hoops_SHS
		((_hoops_HRSGI _hoops_RAPC *)_hoops_HRCSR)->_hoops_APSGI = 1.0f;
}
*/

GLOBAL_FUNCTION bool HD_Measure_Freetype_Char (
	Net_Rendition const & 		nr,
	Font_Instance const *		instance,
	unsigned short				_hoops_IPCSR,
	float *						_hoops_GGGS,
	bool *						_hoops_CPCSR,
	void **						_hoops_SPCSR) {
	_hoops_GPGGH *				_hoops_RSCGI = (_hoops_GPGGH *)instance->_hoops_GAASR;
	_hoops_GRCGI *		_hoops_SCCGI = (_hoops_GRCGI*) _hoops_RSCGI->_hoops_RPGGH;
	unsigned short				_hoops_SRCSP;
	int							height;

	UNREFERENCED (nr);

	if (HOOPS_WORLD->global_font_data_freetype == null) {
		_hoops_RICGI("Request to measure Freetype font without global data",0);
		return false;
	}

	*_hoops_GGGS = 0.0f;
	*_hoops_CPCSR = false;

	height = (int)(instance->_hoops_RACSR * instance->_hoops_GRGGH);

	if (_hoops_SCCGI->_hoops_IRCGI != height*64) {
		_hoops_SCCGI->_hoops_IRCGI = height*64;
		FT_Set_Char_Size (_hoops_SCCGI->face, 0, _hoops_SCCGI->_hoops_IRCGI, _hoops_CRCGI, _hoops_CRCGI);
	}

	_hoops_SRCSP = _hoops_IICGI (_hoops_SCCGI->face, _hoops_SCCGI->offset+_hoops_IPCSR);

	if (_hoops_SRCSP == 0) {
		*_hoops_CPCSR = true;
		*_hoops_SPCSR = (void*)0;
		return true;
	}

	int _hoops_RHCGI = (int)nr->_hoops_SISI->font->_hoops_RACSR;
	int bolding_level = 0;

	if (nr->_hoops_SISI->_hoops_ASRIP) {
		if (_hoops_RHCGI>12)
			bolding_level = _hoops_RHCGI/32+1;
	}

	FT_Load_Glyph (_hoops_SCCGI->face, _hoops_SRCSP, _hoops_SCCGI->_hoops_RRCGI);
	*_hoops_GGGS += (float)_hoops_SCCGI->face->glyph->metrics.horiAdvance / 64.0f + bolding_level;

	*_hoops_SPCSR = (void*)1;

	return true;
}


local float const _hoops_HGHHA[7][6] = {
		{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
		{1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
		{1.0f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f},
		{1.0f, 3.0f, 3.0f, 1.0f, 0.0f, 0.0f},
		{1.0f, 4.0f, 6.0f, 4.0f, 1.0f, 0.0f},
		{1.0f, 5.0f, 10.0f, 10.0f, 5.0f, 1.0f}
};


local void _hoops_PPSGI (
	int			_hoops_SISAA,
	int			_hoops_IAAGA,
	Point *	in_points,
	Point *	out_points,
	int *		_hoops_HPSGI) {
	int			_hoops_IPSGI = *_hoops_HPSGI;
	int			k, l, m;
	float		_hoops_HGGRH = 1.0f / (float) _hoops_SISAA;
	float		t = _hoops_HGGRH;
	float		_hoops_AGPHR;
	float		_hoops_CPSGI;

	for (k=1; k < _hoops_SISAA; k++) {
		_hoops_AGPHR= 1.0f - t;

		out_points[_hoops_IPSGI].x = 0.0f;
		out_points[_hoops_IPSGI].y = 0.0f;
		out_points[_hoops_IPSGI].z = 0.0f;

		for (l = 0; l < _hoops_IAAGA; l++) {
			_hoops_CPSGI = _hoops_HGHHA[_hoops_IAAGA][l];

			for (m = 0; m < _hoops_IAAGA-1; m++) {
				if (m >= l)
					_hoops_CPSGI *= _hoops_AGPHR;
				else
					_hoops_CPSGI *= t;
			}

			out_points[_hoops_IPSGI].x += _hoops_CPSGI * in_points[l].x;
			out_points[_hoops_IPSGI].y += _hoops_CPSGI * in_points[l].y;
		}

		++_hoops_IPSGI;
		t += _hoops_HGGRH;
	}

	*_hoops_HPSGI = _hoops_IPSGI;
}


typedef struct {
	int			height;
	int			_hoops_SPSGI;

	int			_hoops_CICP;

	int			_hoops_GIAHR;
	int			_hoops_GHSGI;
	int			_hoops_RHSGI;

	Point *	points;
	int *		face_list;

	int			_hoops_AHSGI;
} _hoops_PHSGI;


local void _hoops_HHSGI (_hoops_PHSGI * _hoops_IHSGI) {
	Point *	new_points;
	int *		new_face_list;

	ALLOC_ARRAY (new_points, _hoops_IHSGI->_hoops_AHSGI*2, Point);
	ALLOC_ARRAY (new_face_list, _hoops_IHSGI->_hoops_AHSGI*2, int);

	_hoops_AIGA (_hoops_IHSGI->points, _hoops_IHSGI->_hoops_AHSGI, Point, new_points);
	_hoops_AIGA (_hoops_IHSGI->face_list, _hoops_IHSGI->_hoops_AHSGI, int, new_face_list);

	FREE_ARRAY (_hoops_IHSGI->points, _hoops_IHSGI->_hoops_AHSGI, Point);
	FREE_ARRAY (_hoops_IHSGI->face_list, _hoops_IHSGI->_hoops_AHSGI, int);

	_hoops_IHSGI->points = new_points;
	_hoops_IHSGI->face_list = new_face_list;
	_hoops_IHSGI->_hoops_AHSGI = _hoops_IHSGI->_hoops_AHSGI * 2;
}


local int _hoops_CHSGI (const FT_Vector * to, void * _hoops_SHSGI) {
	_hoops_PHSGI *		_hoops_IHSGI = (_hoops_PHSGI *) _hoops_SHSGI;

	while (_hoops_IHSGI->_hoops_GHSGI > _hoops_IHSGI->_hoops_AHSGI-1)
		_hoops_HHSGI(_hoops_IHSGI);

	if (_hoops_IHSGI->_hoops_GIAHR != _hoops_IHSGI->_hoops_GHSGI) {
		while (_hoops_IHSGI->_hoops_RHSGI > _hoops_IHSGI->_hoops_AHSGI-1)
			_hoops_HHSGI(_hoops_IHSGI);

		_hoops_IHSGI->face_list[_hoops_IHSGI->_hoops_RHSGI] = _hoops_IHSGI->_hoops_GHSGI - _hoops_IHSGI->_hoops_GIAHR;
		if (_hoops_IHSGI->_hoops_CICP != 1) _hoops_IHSGI->face_list[_hoops_IHSGI->_hoops_RHSGI]=-_hoops_IHSGI->face_list[_hoops_IHSGI->_hoops_RHSGI];
		_hoops_IHSGI->_hoops_RHSGI++;

		while (_hoops_IHSGI->_hoops_GIAHR < _hoops_IHSGI->_hoops_GHSGI) {
			while (_hoops_IHSGI->_hoops_RHSGI > _hoops_IHSGI->_hoops_AHSGI-1)
				_hoops_HHSGI(_hoops_IHSGI);

			_hoops_IHSGI->face_list[_hoops_IHSGI->_hoops_RHSGI] = _hoops_IHSGI->_hoops_GIAHR;
			_hoops_IHSGI->_hoops_RHSGI++;
			_hoops_IHSGI->_hoops_GIAHR++;
		}
	}

	_hoops_IHSGI->points[_hoops_IHSGI->_hoops_GHSGI].x = (float)to->x / 64.0f;
	_hoops_IHSGI->points[_hoops_IHSGI->_hoops_GHSGI].y = (float)to->y / 64.0f;
	_hoops_IHSGI->points[_hoops_IHSGI->_hoops_GHSGI].z = 0.0f;

	_hoops_IHSGI->_hoops_GIAHR = _hoops_IHSGI->_hoops_GHSGI;
	_hoops_IHSGI->_hoops_GHSGI++;
	_hoops_IHSGI->_hoops_CICP++;

	return 0;
}

local int _hoops_GISGI (const FT_Vector * to, void * _hoops_SHSGI) {
	_hoops_PHSGI *		_hoops_IHSGI = (_hoops_PHSGI *) _hoops_SHSGI;

	while (_hoops_IHSGI->_hoops_GHSGI > _hoops_IHSGI->_hoops_AHSGI-1)
		_hoops_HHSGI(_hoops_IHSGI);

	_hoops_IHSGI->points[_hoops_IHSGI->_hoops_GHSGI].x = (float)to->x / 64.0f;
	_hoops_IHSGI->points[_hoops_IHSGI->_hoops_GHSGI].y = (float)to->y / 64.0f;
	_hoops_IHSGI->points[_hoops_IHSGI->_hoops_GHSGI].z = 0.0f;

	_hoops_IHSGI->_hoops_GHSGI++;

	return 0;
}

local int _hoops_RISGI (const FT_Vector * control, const FT_Vector * to, void * _hoops_SHSGI) {
	_hoops_PHSGI *		_hoops_IHSGI = (_hoops_PHSGI *) _hoops_SHSGI;
	float							xmax, ymax, xmin, ymin, area;
	int								n,i;
	Point						in_points[3];

	in_points[0].x = _hoops_IHSGI->points[_hoops_IHSGI->_hoops_GHSGI-1].x;
	in_points[0].y = _hoops_IHSGI->points[_hoops_IHSGI->_hoops_GHSGI-1].y;

	in_points[1].x = (float)control->x / 64.0f;
	in_points[1].y = (float)control->y / 64.0f;

	in_points[2].x = (float)to->x / 64.0f;
	in_points[2].y = (float)to->y / 64.0f;

	xmin = in_points[0].x;
	ymin = in_points[0].y;
	xmax = in_points[0].x;
	ymax = in_points[0].y;

	for (i=1; i<3; i++) {
		if (xmin > in_points[i].x) xmin = in_points[i].x;
		if (ymin > in_points[i].y) ymin = in_points[i].y;
		if (xmax < in_points[i].x) xmax = in_points[i].x;
		if (ymax < in_points[i].y) ymax = in_points[i].y;
	}

	area = (xmax - xmin) * (ymax - ymin);

	n = (int)((6*area) / _hoops_IHSGI->height) + 3 + _hoops_IHSGI->_hoops_SPSGI;

	while (_hoops_IHSGI->_hoops_GHSGI+n > _hoops_IHSGI->_hoops_AHSGI-1)
		_hoops_HHSGI(_hoops_IHSGI);

	_hoops_PPSGI (n, 3, in_points, _hoops_IHSGI->points, &_hoops_IHSGI->_hoops_GHSGI);

	_hoops_IHSGI->points[_hoops_IHSGI->_hoops_GHSGI].x = (float)to->x/64.0f;
	_hoops_IHSGI->points[_hoops_IHSGI->_hoops_GHSGI].y = (float)to->y/64.0f;
	_hoops_IHSGI->points[_hoops_IHSGI->_hoops_GHSGI].z = 0.0f;

	_hoops_IHSGI->_hoops_GHSGI++;

	return 0;
}

local int _hoops_AISGI (const FT_Vector * _hoops_PISGI, const FT_Vector * _hoops_HISGI, const FT_Vector * to, void * _hoops_SHSGI) {
	_hoops_PHSGI *		_hoops_IHSGI = (_hoops_PHSGI *) _hoops_SHSGI;
	float							xmax, ymax, xmin, ymin, area;
	int								n,i;
	Point						in_points[4];

	in_points[0].x = _hoops_IHSGI->points[_hoops_IHSGI->_hoops_GHSGI-1].x;
	in_points[0].y = _hoops_IHSGI->points[_hoops_IHSGI->_hoops_GHSGI-1].y;

	in_points[1].x = (float)_hoops_PISGI->x / 64.0f;
	in_points[1].y = (float)_hoops_PISGI->y / 64.0f;

	in_points[2].x = (float)_hoops_HISGI->x / 64.0f;
	in_points[2].y = (float)_hoops_HISGI->y / 64.0f;

	in_points[3].x = (float)to->x / 64.0f;
	in_points[3].y = (float)to->y / 64.0f;

	xmin = in_points[0].x;
	ymin = in_points[0].y;
	xmax = in_points[0].x;
	ymax = in_points[0].y;

	for (i=1; i<4; i++) {
		if (xmin > in_points[i].x) xmin = in_points[i].x;
		if (ymin > in_points[i].y) ymin = in_points[i].y;
		if (xmax < in_points[i].x) xmax = in_points[i].x;
		if (ymax < in_points[i].y) ymax = in_points[i].y;
	}

	area = (xmax - xmin) * (ymax - ymin);

	n = (int)((6*area) / _hoops_IHSGI->height) + 3 + _hoops_IHSGI->_hoops_SPSGI;

	while (_hoops_IHSGI->_hoops_GHSGI+n > _hoops_IHSGI->_hoops_AHSGI-1)
		_hoops_HHSGI(_hoops_IHSGI);

	_hoops_PPSGI (n, 4, in_points, _hoops_IHSGI->points, &_hoops_IHSGI->_hoops_GHSGI);

	while (_hoops_IHSGI->_hoops_GHSGI > _hoops_IHSGI->_hoops_AHSGI-1)
		_hoops_HHSGI(_hoops_IHSGI);

	_hoops_IHSGI->points[_hoops_IHSGI->_hoops_GHSGI].x = (float)to->x / 64.0f;
	_hoops_IHSGI->points[_hoops_IHSGI->_hoops_GHSGI].y = (float)to->y / 64.0f;
	_hoops_IHSGI->points[_hoops_IHSGI->_hoops_GHSGI].z = 0.0f;

	_hoops_IHSGI->_hoops_GHSGI++;

	return 0;
}

local void _hoops_IISGI (
	_hoops_GRCGI *		_hoops_SCCGI,
	int							height,
	int							bolding_level,
	int							count,
	float						xrslant,
	float						xrrotation,
	float						xrwidth_scale,
	Karacter const *			string,
	Point **					_hoops_CISGI,
	int **						_hoops_SISGI,
	int *						_hoops_AHSGI,
	int *						_hoops_GHSGI,
	int *						_hoops_RHSGI,
	int							_hoops_SPSGI,
	float *						_hoops_GCSGI,
	float *						_hoops_RCSGI) {
	int							index;
	unsigned short				_hoops_SRCSP;
	int							error;
	float						_hoops_ACSGI;
	float						_hoops_PCSGI;
	float						x = 0.0f;
	float						y = 0.0f;
	float						_hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR;
	_hoops_PHSGI	_hoops_HCSGI;
	_hoops_PHSGI * _hoops_IHSGI = &_hoops_HCSGI;
	FT_Matrix					matrix;
	FT_Vector					vector;
	FT_Glyph					glyph;
	FT_OutlineGlyph				_hoops_ICSGI;
	FT_Outline_Funcs			_hoops_CCSGI;

	if (!_hoops_GCSGI) _hoops_GCSGI=&_hoops_ACSGI;
	if (!_hoops_RCSGI) _hoops_RCSGI=&_hoops_PCSGI;
	*_hoops_GCSGI = 0;
	*_hoops_RCSGI = 0;

	_hoops_CCSGI.move_to = _hoops_CHSGI;
	_hoops_CCSGI.line_to = _hoops_GISGI;
	_hoops_CCSGI.conic_to = _hoops_RISGI;
	_hoops_CCSGI.cubic_to = _hoops_AISGI;
	_hoops_CCSGI.shift = 0;
	_hoops_CCSGI.delta = 0;


	_hoops_IHSGI->height = height;
	_hoops_IHSGI->_hoops_SPSGI = _hoops_SPSGI;

	_hoops_IHSGI->points = *_hoops_CISGI;
	_hoops_IHSGI->face_list = *_hoops_SISGI;
	_hoops_IHSGI->_hoops_GHSGI = *_hoops_GHSGI;
	_hoops_IHSGI->_hoops_RHSGI = *_hoops_RHSGI;
	_hoops_IHSGI->_hoops_AHSGI = *_hoops_AHSGI;

	/* _hoops_CSGA _hoops_HSAIP _hoops_SRS */
	_hoops_RICH (xrslant, _hoops_GGHCR, _hoops_AGHCR);
	_hoops_IPGRP = _hoops_GGHCR / _hoops_AGHCR;
	/* _hoops_HA _hoops_HGCR _hoops_IHSPA & _hoops_HHSPA _hoops_IIGR _hoops_ICSA */
	_hoops_RICH (xrrotation, _hoops_GGHCR, _hoops_AGHCR);

	matrix.xx = (long)(_hoops_AGHCR * xrwidth_scale * 65536);
	matrix.xy = (long)(((-_hoops_GGHCR * xrwidth_scale)+_hoops_IPGRP*_hoops_AGHCR) * 65536);
	matrix.yx = (long)(_hoops_GGHCR * 65536);
	matrix.yy = (long)((_hoops_AGHCR+_hoops_IPGRP*_hoops_GGHCR) * 65536);

	for (index=0; index<count; index++) {
		_hoops_SRCSP = _hoops_IICGI (_hoops_SCCGI->face, _hoops_SCCGI->offset+string[index]);

		error = FT_Load_Glyph (_hoops_SCCGI->face, _hoops_SRCSP, _hoops_SCCGI->_hoops_RRCGI);
		error = FT_Get_Glyph (_hoops_SCCGI->face->glyph, &glyph);

		if (bolding_level > 0)
			FT_Outline_Embolden(&((FT_OutlineGlyph)glyph)->outline, bolding_level*64);

		vector.x = (int) x * 64;
		vector.y = (int) y * 64;

		FT_Glyph_Transform (glyph, &matrix,	&vector);

		_hoops_ICSGI = (FT_OutlineGlyph)glyph;

		_hoops_IHSGI->_hoops_GIAHR = _hoops_IHSGI->_hoops_GHSGI;
		_hoops_IHSGI->_hoops_CICP = 0;

		error = FT_Outline_Decompose (&_hoops_ICSGI->outline, &_hoops_CCSGI, (void*)_hoops_IHSGI);

		if (!error) {
			while (_hoops_IHSGI->_hoops_RHSGI > _hoops_IHSGI->_hoops_AHSGI-1)
				_hoops_HHSGI(_hoops_IHSGI);

			_hoops_IHSGI->face_list[_hoops_IHSGI->_hoops_RHSGI] = _hoops_IHSGI->_hoops_GHSGI - _hoops_IHSGI->_hoops_GIAHR;
			if (_hoops_IHSGI->_hoops_CICP != 1) _hoops_IHSGI->face_list[_hoops_IHSGI->_hoops_RHSGI]=-_hoops_IHSGI->face_list[_hoops_IHSGI->_hoops_RHSGI];
			_hoops_IHSGI->_hoops_RHSGI++;

			while (_hoops_IHSGI->_hoops_GIAHR < _hoops_IHSGI->_hoops_GHSGI) {
				while (_hoops_IHSGI->_hoops_RHSGI > _hoops_IHSGI->_hoops_AHSGI-1)
					_hoops_HHSGI(_hoops_IHSGI);

				_hoops_IHSGI->face_list[_hoops_IHSGI->_hoops_RHSGI] = _hoops_IHSGI->_hoops_GIAHR;
				_hoops_IHSGI->_hoops_RHSGI++;
				_hoops_IHSGI->_hoops_GIAHR++;
			}
		}
		else
			_hoops_IHSGI->_hoops_GHSGI = _hoops_IHSGI->_hoops_GIAHR;


		*_hoops_GCSGI = ((float)_hoops_SCCGI->face->glyph->metrics.horiAdvance / 64.0f) * _hoops_AGHCR * xrwidth_scale;
		*_hoops_RCSGI = ((float)_hoops_SCCGI->face->glyph->metrics.horiAdvance / 64.0f) * _hoops_GGHCR * xrwidth_scale;
		x += *_hoops_GCSGI;
		y += *_hoops_RCSGI;

		FT_Done_Glyph(glyph);
	}

	*_hoops_GHSGI = _hoops_IHSGI->_hoops_GHSGI;
	*_hoops_RHSGI = _hoops_IHSGI->_hoops_RHSGI;
	*_hoops_AHSGI = _hoops_IHSGI->_hoops_AHSGI;

	*_hoops_CISGI = _hoops_IHSGI->points;
	*_hoops_SISGI = _hoops_IHSGI->face_list;

	(void)error;		/* _hoops_ARP _hoops_HIH _hoops_HAR _hoops_IGI _hoops_IAII */
}


struct _hoops_PIPHA {
	Net_Rendition		_hoops_APHGA;
	DC_Point const *	points;
	_hoops_GRCAR const *	_hoops_RRCAR;
};


local void _hoops_SCSGI (
	void *					info,
	int						_hoops_HAPH,
	Point const *		p1,
	Point const *		p2,
	Point const *		_hoops_IAPH,
	int						s1,
	int						s2,
	int						_hoops_CAPH,
	Intersection const * i1,
	Intersection const * i2,
	Intersection const * _hoops_SAPH) {
	struct _hoops_PIPHA *			data = (struct _hoops_PIPHA *)info;
	Net_Rendition const & 	nr = data->_hoops_APHGA;
	_hoops_GRCAR const *		_hoops_ARCAR = data->_hoops_RRCAR;
	DC_Point					_hoops_RCHHR[3];

	UNREFERENCED(_hoops_HAPH);
	UNREFERENCED(s1);
	UNREFERENCED(s2);
	UNREFERENCED(_hoops_CAPH);
	UNREFERENCED(i1);
	UNREFERENCED(i2);
	UNREFERENCED(_hoops_SAPH);
	UNREFERENCED(p1);
	UNREFERENCED(p2);
	UNREFERENCED(_hoops_IAPH);

	if (s1 >= 0 && s2 >= 0 && _hoops_CAPH >= 0 &&
		ANYBIT (_hoops_ARCAR[s1] & _hoops_ARCAR[s2] & _hoops_ARCAR[_hoops_CAPH], ~_hoops_RPCAR))
		return;					/* _hoops_HCR _hoops_SACH _hoops_SGGR */

	if (s1 >= 0) {
		_hoops_RCHHR[0].x = data->points[s1].x;
		_hoops_RCHHR[0].y = data->points[s1].y;
		_hoops_RCHHR[0].z = data->points[s1].z;
	}
	else {
		int		si = i1->_hoops_PICHR[0]._hoops_PCIGI;
		int		ei = i1->_hoops_PICHR[0]._hoops_HCIGI;
		float	f  = i1->_hoops_PICHR[0]._hoops_RCGCR;

		_hoops_RCHHR[0].x = data->points[si].x + f * (data->points[ei].x - data->points[si].x);
		_hoops_RCHHR[0].y = data->points[si].y + f * (data->points[ei].y - data->points[si].y);
		_hoops_RCHHR[0].z = data->points[si].z + f * (data->points[ei].z - data->points[si].z);
	}

	if (s2 >= 0) {
		_hoops_RCHHR[1].x = data->points[s2].x;
		_hoops_RCHHR[1].y = data->points[s2].y;
		_hoops_RCHHR[1].z = data->points[s2].z;
	}
	else {
		int		si = i2->_hoops_PICHR[0]._hoops_PCIGI;
		int		ei = i2->_hoops_PICHR[0]._hoops_HCIGI;
		float	f  = i2->_hoops_PICHR[0]._hoops_RCGCR;

		_hoops_RCHHR[1].x = data->points[si].x + f * (data->points[ei].x - data->points[si].x);
		_hoops_RCHHR[1].y = data->points[si].y + f * (data->points[ei].y - data->points[si].y);
		_hoops_RCHHR[1].z = data->points[si].z + f * (data->points[ei].z - data->points[si].z);
	}

	if (_hoops_CAPH >= 0) {
		_hoops_RCHHR[2].x = data->points[_hoops_CAPH].x;
		_hoops_RCHHR[2].y = data->points[_hoops_CAPH].y;
		_hoops_RCHHR[2].z = data->points[_hoops_CAPH].z;
	}
	else {
		int		si = _hoops_SAPH->_hoops_PICHR[0]._hoops_PCIGI;
		int		ei = _hoops_SAPH->_hoops_PICHR[0]._hoops_HCIGI;
		float	f  = _hoops_SAPH->_hoops_PICHR[0]._hoops_RCGCR;

		_hoops_RCHHR[2].x = data->points[si].x + f * (data->points[ei].x - data->points[si].x);
		_hoops_RCHHR[2].y = data->points[si].y + f * (data->points[ei].y - data->points[si].y);
		_hoops_RCHHR[2].z = data->points[si].z + f * (data->points[ei].z - data->points[si].z);
	}

	_hoops_CSIGH (nr, _hoops_RCHHR);
}


local void _hoops_GSSGI (
	Net_Rendition const & nr,
	_hoops_GICGI const *	item,
	Point const *					points) {
	_hoops_PRHIR alter *		_hoops_CICP;
	Point alter *		new_points;
	int faces = 0;
	int i, n;

	ZALLOC(_hoops_CICP, _hoops_PRHIR);
	_hoops_CICP->type = _hoops_ARHIR;
	_hoops_CICP->_hoops_HIHI = 1;

	i = 0;
	while (i < item->face_count) {
		faces++;
		if (item->face_list[i] < 0)
			i += -item->face_list[i] + 1;
		else
			i += item->face_list[i] + 1;
	}

	_hoops_CICP->_hoops_IRHIR = _hoops_CICP->_hoops_CASGP = faces;
	ALLOC_ARRAY (_hoops_CICP->lengths, _hoops_CICP->_hoops_IRHIR, int);

	_hoops_CICP->count = _hoops_CICP->allocated = item->point_count;
	ALLOC_ARRAY (new_points, _hoops_CICP->count, Point);
	_hoops_CICP->points = new_points;

	i = 0;
	n = 0;
	while (i<item->face_count) {
		int		length = Abs (item->face_list[i++]);

		_hoops_CICP->lengths[n++] = length;

		_hoops_AIGA (&points[item->face_list[i]], length, Point, new_points);
		new_points += length;
		i += length;
	}

	HD_Std_3D_Contour (nr, _hoops_CICP);

	_hoops_HPRH(_hoops_CICP);
}

struct _hoops_RSSGI {	/* _hoops_ICGI _hoops_GCHA _hoops_IH _hoops_GRR _hoops_HAPR */
	int					_hoops_ASSGI;
	char				orientation;
	Point			min, max;
};


struct _hoops_PSSGI {	/* _hoops_HIAAR _hoops_RH _hoops_HAPR _hoops_HSSGI _hoops_ICAAA */
	_hoops_RSSGI *	_hoops_IGGI;
	_hoops_PSSGI *		next;	/* _hoops_HCIIA */
	_hoops_PSSGI *		_hoops_HCPIH;	/* _hoops_RPSI */
};


/* _hoops_HSRR _hoops_IRS _hoops_RAGA _hoops_SCRPA, _hoops_HRS _hoops_IHPR _hoops_RPP _hoops_ISSGI _hoops_HRGR _hoops_GIAA _hoops_CSSGI */
local bool _hoops_SSSGI (Point * points, int * _hoops_SAGPA, _hoops_RSSGI * _hoops_GGGRI, _hoops_RSSGI * _hoops_RGGRI)
{
	int	const	_hoops_AGGRI = _hoops_GGGRI->_hoops_ASSGI;
	int	const	_hoops_PGGRI = _hoops_RGGRI->_hoops_ASSGI;
	int const	s1 = Abs(_hoops_SAGPA[_hoops_AGGRI]);
	int	const	s2 = Abs(_hoops_SAGPA[_hoops_PGGRI]);
	int 		i, j;
	int 		v;
	int 		total;

	if (_hoops_GGGRI->min.x < _hoops_RGGRI->min.x ||
		_hoops_GGGRI->min.y < _hoops_RGGRI->min.y ||
		_hoops_GGGRI->max.x > _hoops_RGGRI->max.x ||
		_hoops_GGGRI->max.y > _hoops_RGGRI->max.y)
		return false;

	/* _hoops_HGGRI _hoops_IRS _hoops_RRI _hoops_GGR-_hoops_HCH _hoops_ISPR.
	 * _hoops_GCRR _hoops_RCRR _hoops_HCR _hoops_RSSA _hoops_IIGR _hoops_ISSGI _hoops_CHR _hoops_ASSA _hoops_CSSGI.
	 */
	j = _hoops_AGGRI + 1;
	for (j = _hoops_AGGRI + 1; j < _hoops_AGGRI + 1 + s1; j++)
	{
		int _hoops_IGGRI = s2;
		v = _hoops_SAGPA[j];
		total = 0;

		for (i = _hoops_PGGRI + 1; i < _hoops_PGGRI + 1 + _hoops_IGGRI; i++) {
			/* _hoops_IH _hoops_GRR _hoops_III _hoops_CAGH _hoops_GGR _hoops_CSSGI, _hoops_CACH _hoops_RPP _hoops_IRS _hoops_IRPHR _hoops_III _hoops_AGCPR _hoops_HII _hoops_IRS _hoops_GPHA _hoops_GGR
			 * _hoops_III 1 (_hoops_HPPC) _hoops_HSRAA _hoops_SCH, _hoops_PPR _hoops_RPR _hoops_GH _hoops_RH _hoops_APSR.
			 */
			int i2;
			int p1, p2;

			if (i == _hoops_PGGRI + _hoops_IGGRI)
				i2 = _hoops_PGGRI + 1;
			else
				i2 = i + 1;

			p1 = _hoops_SAGPA[i];
			p2 = _hoops_SAGPA[i2];

			/* _hoops_RPP _hoops_HPPC _hoops_HRGR _hoops_GAPA _hoops_PARAA _hoops_PPR _hoops_AARAA */
			if (points[v].x < points[p1].x && points[v].x > points[p2].x ||
				points[v].x < points[p2].x && points[v].x > points[p1].x) {

				/* _hoops_RPP _hoops_HPPC _hoops_HRGR _hoops_GSSC _hoops_HSAR _hoops_GIPR _hoops_PARAA _hoops_PPR _hoops_AARAA, _hoops_SSIA _hoops_ARCRA */
				if (points[v].y < points[p1].y && points[v].y < points[p2].y)
						total++;
				/* _hoops_RPP _hoops_HPPC _hoops_HRGR _hoops_GSSC _hoops_HSAR _hoops_SPR _hoops_HIH _hoops_HAR _hoops_RH _hoops_RII, _hoops_SGH _hoops_CGGRI _hoops_IS _hoops_CAHA _hoops_GGSR _hoops_RPP _hoops_SCH _hoops_HSRAA _hoops_PAR _hoops_HAR */
				else if (points[v].y < points[p1].y || points[v].y < points[p2].y) {
					float	y = points[p1].y + (points[v].x - points[p1].x) *
												(points[p2].y - points[p1].y) / (points[p2].x - points[p1].x);

					if (points[v].y < y)
						total++;
				}
			}
			/* _hoops_RPP _hoops_HPPC _hoops_HRGR _hoops_SSPP _hoops_SGGRI _hoops_PARAA */
			else if (points[v].x == points[p1].x && points[v].y < points[p1].y) {
				int		_hoops_GRGRI = i, _hoops_RRGRI = i2;

				/* _hoops_ARAS _hoops_IGIAR _hoops_RH _hoops_RSSA _hoops_GIPR _hoops_SSGAR _hoops_CCGR _hoops_RHAC _hoops_SSS _hoops_IRS _hoops_AGRP _hoops_GGR _hoops_SISR */
				while (points[_hoops_SAGPA[_hoops_GRGRI]].x == points[p1].x) {
					_hoops_GRGRI--;
					if (_hoops_GRGRI == _hoops_PGGRI)
						_hoops_GRGRI = _hoops_PGGRI + _hoops_IGGRI;
				}
				while (points[_hoops_SAGPA[_hoops_RRGRI]].x == points[p1].x) {
					_hoops_RRGRI++;
					if (_hoops_RRGRI == _hoops_PGGRI + _hoops_IGGRI + 1)
						_hoops_RRGRI = _hoops_PGGRI + 1;
				}

				if (!(points[_hoops_SAGPA[_hoops_GRGRI]].x < points[p1].x &&
					  points[_hoops_SAGPA[_hoops_RRGRI]].x < points[p1].x ||
					  points[_hoops_SAGPA[_hoops_GRGRI]].x > points[p1].x &&
					  points[_hoops_SAGPA[_hoops_RRGRI]].x > points[p1].x))
					total++;

				if (_hoops_GRGRI > i) /* _hoops_RPP _hoops_ARGRI _hoops_PRGRI _hoops_AARI, _hoops_GA'_hoops_RA _hoops_RHSHA _hoops_AGAP _hoops_SGHC */
					_hoops_IGGRI = (_hoops_GRGRI - _hoops_PGGRI - 1);
				if (_hoops_RRGRI < i2) /* _hoops_RPP _hoops_HRGRI _hoops_PRGRI _hoops_AARI _hoops_AIAH, _hoops_PSCR _hoops_SR'_hoops_ASAR _hoops_CPHR */
					i = _hoops_PGGRI + 1 + _hoops_IGGRI;
				else if (i < _hoops_RRGRI)
					i = _hoops_RRGRI - 1; /* _hoops_AIAH _hoops_RAICR _hoops_RH _hoops_SGHC _hoops_GAPA _hoops_HAS _hoops_PPR _hoops_HRGRI, _hoops_HIS _hoops_HSGR _hoops_CPCHR */
			}
		}
		if (total % 2 == 0)
			return false;
	}

	return true;
}

local bool _hoops_IRGRI(
	Point *		points,
	int *		_hoops_SAGPA,
	int			index,
	_hoops_RSSGI *	loops,
	_hoops_PSSGI *		node) {
	_hoops_PSSGI *		_hoops_HCPIH = node->_hoops_HCPIH;
	_hoops_PSSGI *		_hoops_CRGRI = null;
	_hoops_PSSGI *		_hoops_SRGRI = null;

	if (!_hoops_HCPIH) {
		ZALLOC (node->_hoops_HCPIH, _hoops_PSSGI);
		node->_hoops_HCPIH->_hoops_IGGI = &loops[index];
		return true;
	}
	else {
		while (_hoops_HCPIH) {
			if (_hoops_SSSGI(points, _hoops_SAGPA, &loops[index], _hoops_HCPIH->_hoops_IGGI)) {
				/* _hoops_CCAH _hoops_HAPR _hoops_HRGR _hoops_GIAA _hoops_RGR _hoops_RPSI _hoops_HAPR, _hoops_HIS _hoops_GHHA */
				if (!_hoops_IRGRI (points, _hoops_SAGPA, index, loops, _hoops_HCPIH)) {
					/* _hoops_IRPSR'_hoops_RA _hoops_SSS _hoops_PCIRA _hoops_GGR _hoops_PGHAA, _hoops_HIS _hoops_GGCR _hoops_ARI */
					ZALLOC (_hoops_CRGRI, _hoops_PSSGI);
					_hoops_CRGRI->_hoops_IGGI = &loops[index];
					_hoops_CRGRI->next = node->_hoops_HCPIH;
					node->_hoops_HCPIH = _hoops_CRGRI;
				}
				return true;
			}
			_hoops_HCPIH = _hoops_HCPIH->next;
		}

		/* _hoops_RRP _hoops_IS _hoops_HSPAR _hoops_HCR _hoops_RASI _hoops_PPR _hoops_GCAS _hoops_HGHC _hoops_CAPR _hoops_RRGI _hoops_RGR _hoops_CCAH _hoops_HAPR */
		_hoops_HCPIH = node->_hoops_HCPIH;
		_hoops_SRGRI = null;

		ZALLOC (_hoops_CRGRI, _hoops_PSSGI);
		_hoops_CRGRI->_hoops_IGGI = &loops[index];

		while (_hoops_HCPIH) {
			if (_hoops_SSSGI(points, _hoops_SAGPA, _hoops_HCPIH->_hoops_IGGI, &loops[index])) {
				/* _hoops_RPP _hoops_RPSI _hoops_HRGR _hoops_ASSA _hoops_HAPR, _hoops_IHIS _hoops_SCH _hoops_IIH */
				_hoops_PSSGI *_hoops_GAGRI = _hoops_CRGRI->_hoops_HCPIH;
				_hoops_CRGRI->_hoops_HCPIH = _hoops_HCPIH;
				if (_hoops_SRGRI)
					_hoops_HCPIH = _hoops_SRGRI->next = _hoops_HCPIH->next;
				else
					_hoops_HCPIH = node->_hoops_HCPIH = _hoops_HCPIH->next;
				_hoops_CRGRI->_hoops_HCPIH->next = _hoops_GAGRI;
			}
			else {
				_hoops_SRGRI = _hoops_HCPIH;
				_hoops_HCPIH = _hoops_HCPIH->next;
			}
		}

		/* _hoops_GGCR _hoops_IS _hoops_RIPS _hoops_IIGR _hoops_HIGR */
		_hoops_CRGRI->next = node->_hoops_HCPIH;
		node->_hoops_HCPIH = _hoops_CRGRI;
		return true;
	}
}

local void _hoops_RAGRI(int * _hoops_AAGRI, int * _hoops_HCGPA, int * _hoops_SAACA, _hoops_PSSGI * node)
{
	bool		_hoops_PAGRI = (node->_hoops_IGGI == 0);
	int				index = -1;
	int				_hoops_HAGRI = -1;
	_hoops_PSSGI *		_hoops_HCPIH;
	int				_hoops_IAGRI = 0;

	if (!_hoops_PAGRI) {
		index = node->_hoops_IGGI->_hoops_ASSGI;
		_hoops_HAGRI = Abs(_hoops_AAGRI[index]) + 1;
	}
	if (_hoops_SAACA == null)
		_hoops_SAACA = &_hoops_IAGRI;

	/* _hoops_IISH _hoops_GGSR _hoops_RH _hoops_SCGR _hoops_HAPR */
	if (!_hoops_PAGRI) {
		_hoops_AIGA (&_hoops_AAGRI[index], _hoops_HAGRI, int, &_hoops_HCGPA[*_hoops_SAACA]);
		_hoops_HCGPA[*_hoops_SAACA] = -Abs(_hoops_AAGRI[index]);
		*_hoops_SAACA += _hoops_HAGRI;
	}

	/* _hoops_IISH _hoops_GGSR _hoops_GII _hoops_CAGRI _hoops_RRGI _hoops_RGR _hoops_HAPR */
	_hoops_HCPIH = node->_hoops_HCPIH;
	while (_hoops_HCPIH) {
		int position = *_hoops_SAACA;

		_hoops_RAGRI(_hoops_AAGRI, _hoops_HCGPA, _hoops_SAACA, _hoops_HCPIH);

		/* _hoops_RGHS _hoops_CRGC _hoops_RRGI _hoops_SRRPR _hoops_CHR _hoops_HCR (_hoops_PPR _hoops_RH _hoops_RGAR) "_hoops_RPHSR" _hoops_RGHS */
		if (_hoops_PAGRI)
			_hoops_HCGPA[position] = Abs(_hoops_HCGPA[position]);

		_hoops_HCPIH = _hoops_HCPIH->next;
	}

	/* _hoops_SP _hoops_GH */
	while (node->_hoops_HCPIH) {
		_hoops_HCPIH = node->_hoops_HCPIH->next;
		FREE (node->_hoops_HCPIH, _hoops_PSSGI);
		node->_hoops_HCPIH = _hoops_HCPIH;
	}
}



#define _hoops_SAGRI 512

local void _hoops_GPGRI (
	Net_Rendition const &		inr,
	Font_Instance const *		specific,
	Point const *				where,
	int							_hoops_RPGRI,
	Karacter const *			string,
	Vector const *				scale) {
	Net_Rendition				nr = inr;
	_hoops_GPGGH *				_hoops_RSCGI = (_hoops_GPGGH *) specific->_hoops_GAASR;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_PSIHP			_hoops_HSIHP = nr->_hoops_RSGC;
	_hoops_GRCGI *		_hoops_SCCGI = (_hoops_GRCGI*)_hoops_RSCGI->_hoops_RPGGH;
	int							error;
	int							_hoops_RHCGI;
	float						x = where->x;
	float						y = where->y;
	float						z = where->z;
 	float						_hoops_IHPIA[4][4];
	float						_hoops_APGRI[4][4];
	float						_hoops_PPGRI[4][4];
	float						_hoops_HPGRI,_hoops_IPGRI;
	Point						_hoops_CPGRI;
	_hoops_AHCGI *			_hoops_PRCGI;
	int							_hoops_SPGRI = 0;
	int							index;
	int							i;
	int							_hoops_AHSGI = 0;
	Point *						points = null;
	int	 *						face_list = null;
	float						_hoops_GHGRI = 1.0f;
	float						_hoops_RHGRI = _hoops_HRCIR->_hoops_IPGRP;
	int							bolding_level = 0;
	int							_hoops_GHRGR = 0;
	bool						_hoops_AHGRI = false;

	if (HOOPS_WORLD->global_font_data_freetype == null) {
		_hoops_RICGI("Request to draw Freetype font without global data", 0);
		return;
	}

	if (_hoops_HRCIR->_hoops_RGIHP == null) {
		((_hoops_IGCSR alter &)_hoops_HRCIR)->_hoops_RGIHP = nr->_hoops_AHP;
		Line_Rendition alter &	_hoops_ASAIP = ((_hoops_IGCSR alter &)_hoops_HRCIR)->_hoops_RGIHP.Modify();

		_hoops_ASAIP->_hoops_CHA = _hoops_HRCIR->_hoops_CHA;
		_hoops_ASAIP->color = _hoops_HRCIR->color;
		HD_Replace_Line_Style(_hoops_ASAIP, nr->_hoops_GCSHP->_hoops_IHRIP);
		_hoops_ASAIP->weight = dc->_hoops_PGCC._hoops_IHHSR;
		//_hoops_RGISR->_hoops_GGCS = _hoops_IRAP;
	}

	Line_Rendition alter &		_hoops_HC = nr->_hoops_AHP = _hoops_HRCIR->_hoops_RGIHP;
	nr->_hoops_RHP = _hoops_HC;

	if (_hoops_HC->_hoops_IHA == null) {
		_hoops_HC->_hoops_IHA = nr->_hoops_IHA;
		_hoops_CIGA alter &		_hoops_SIGA = _hoops_HC->_hoops_IHA.Modify();

		_hoops_SIGA->pattern = FP_SOLID;

		_hoops_SIGA->_hoops_CHA = _hoops_HC->_hoops_CHA;
		_hoops_SIGA->_hoops_GIA = _hoops_HC->_hoops_CHA;

		_hoops_SIGA->color = _hoops_HC->color;
		_hoops_SIGA->_hoops_RGIR = _hoops_HC->color;

		_hoops_SIGA->_hoops_AGP = null;
	}
	nr->_hoops_IHA = _hoops_HC->_hoops_IHA;


	if (_hoops_HSIHP->action.draw_dc_polyline != _hoops_HSIHP->action._hoops_SPCHP ||
		_hoops_HSIHP->action.draw_dc_face != _hoops_HSIHP->action._hoops_RHCHP ||
		_hoops_HSIHP->action.draw_3d_polyline != _hoops_HSIHP->action._hoops_GCCHP ||
		_hoops_HSIHP->action.draw_3d_polygon != _hoops_HSIHP->action._hoops_ACCHP) {
		_hoops_PSIHP alter &		_hoops_PHGRI = nr.Modify()->_hoops_RSGC.Modify();

		_hoops_PHGRI->action.draw_dc_polyline = _hoops_HSIHP->action._hoops_SPCHP;
		_hoops_PHGRI->action.draw_dc_face = _hoops_HSIHP->action._hoops_RHCHP;
		_hoops_PHGRI->action.draw_3d_polyline = _hoops_HSIHP->action._hoops_GCCHP;
		_hoops_PHGRI->action.draw_3d_polygon = _hoops_HSIHP->action._hoops_ACCHP;
	}


	_hoops_RHCGI = (int)_hoops_HRCIR->font->_hoops_RACSR;

	if (_hoops_HRCIR->_hoops_PSRIP)
		_hoops_RHGRI += 10.0f;

	if (_hoops_HRCIR->_hoops_ASRIP) {
		if (_hoops_RHCGI>12)
			bolding_level = _hoops_RHCGI/32+1;
	}

	_hoops_GRSGI (_hoops_SCCGI, _hoops_RHCGI, bolding_level, _hoops_RHGRI, _hoops_HRCIR->rotation, _hoops_HRCIR->width_scale);

	_hoops_PRCGI = _hoops_SCCGI->_hoops_PRCGI;

	HI_Compute_Scale_Matrix (_hoops_HRCIR->width_scale, 1.0f, 1.0f, &_hoops_APGRI[0][0]);

	if (_hoops_RHGRI != 0.0f) {
		HI_Compute_Identity_Matrix (&_hoops_IHPIA[0][0]);
		HI_SinCos (_hoops_RHGRI, &_hoops_HPGRI,&_hoops_IPGRI);
		_hoops_IHPIA[1][0] = _hoops_HPGRI/_hoops_IPGRI;
		HI_Compute_Matrix_Product (&_hoops_APGRI[0][0], &_hoops_IHPIA[0][0], &_hoops_APGRI[0][0]);
	}

	if (_hoops_HRCIR->rotation != 0.0f) {
		HI_Compute_Rotation_Matrix (0.0f, 0.0f, _hoops_HRCIR->rotation, &_hoops_PPGRI[0][0]);
		HI_Compute_Matrix_Product (&_hoops_APGRI[0][0], &_hoops_PPGRI[0][0], &_hoops_APGRI[0][0]);
	}

	HI_Compute_Scale_Matrix (	scale->x * _hoops_HRCIR->font->_hoops_GCHSA * _hoops_HRCIR->font->_hoops_GRGGH,
								scale->y * _hoops_HRCIR->font->_hoops_GCHSA * _hoops_HRCIR->font->_hoops_GRGGH,
								scale->z, &_hoops_IHPIA[0][0]);
	HI_Compute_Matrix_Product (&_hoops_APGRI[0][0], &_hoops_IHPIA[0][0], &_hoops_APGRI[0][0]);

	_hoops_CPGRI.z = 0.0f;


	for (index=0; index<_hoops_RPGRI; index++) {
		unsigned short			_hoops_SRCSP;
		_hoops_GICGI *	item;
		int						_hoops_HHGRI = 0;

		_hoops_SRCSP = _hoops_IICGI(_hoops_SCCGI->face, _hoops_SCCGI->offset+string[index]);

		item = _hoops_PRCGI->item[_hoops_SRCSP&_hoops_SPCGI];

		if (item && item->_hoops_SRCSP != _hoops_SRCSP) {
			if (item->points) {
				FREE_ARRAY_ALIGNED (item->points, item->point_count, Point, 16);
				item->points = null;
			}
			if (item->face_list) {
				FREE_ARRAY (item->face_list, item->face_count, int);
				item->face_list = null;
			}
			if (item->_hoops_SHCGI) {
				Polyedge *pe = item->_hoops_SHCGI->polyedge;
				if (pe && _hoops_ISAI (pe) == 0) {
					HI_Free_Polyedge (pe);
				}
				FREE(item->_hoops_SHCGI, _hoops_HHCGI);
				item->_hoops_SHCGI = null;
			}
			if (item->_hoops_PCHAR &&
				_hoops_ISAI (item->_hoops_PCHAR) == 0) {
				HI_Free_Tristrip (item->_hoops_PCHAR);
			}
			item->_hoops_PCHAR = null;
			_hoops_HHGRI = 1;
		}
		if (!item) {
			ZALLOC(item, _hoops_GICGI);
			_hoops_PRCGI->item[_hoops_SRCSP&_hoops_SPCGI]=item;
			_hoops_HHGRI=1;
		}

		if (_hoops_HHGRI) {
			int		_hoops_GHSGI=0;
			int		_hoops_RHSGI=0;
			float	_hoops_IHGRI;
			float	_hoops_CHGRI;

			if (!_hoops_SPGRI) {
				if (_hoops_SCCGI->_hoops_IRCGI != _hoops_RHCGI*64) {
					_hoops_SCCGI->_hoops_IRCGI = _hoops_RHCGI*64;
					error = FT_Set_Char_Size(_hoops_SCCGI->face, 0, _hoops_SCCGI->_hoops_IRCGI, _hoops_CRCGI, _hoops_CRCGI);
				}
				_hoops_SPGRI = 1;
			}

			_hoops_AHSGI = 128;
			ALLOC_ARRAY_CACHED (points, _hoops_AHSGI, Point);
			ALLOC_ARRAY_CACHED (face_list, _hoops_AHSGI, int);

			_hoops_IISGI (_hoops_SCCGI, _hoops_RHCGI, bolding_level, 1, 0.0f, 0.0f, 1.0f,
				&string[index], &points, &face_list, &_hoops_AHSGI, &_hoops_GHSGI, &_hoops_RHSGI, 0,
				&_hoops_IHGRI, &_hoops_CHGRI);

			if (_hoops_GHSGI) {
				int 			_hoops_SHGRI = 0;
				int 			j = 0;
				int 			_hoops_GIGRI = 0;
				_hoops_RSSGI *		_hoops_RIGRI = null;
				_hoops_PSSGI				root;
				bool			_hoops_AIGRI = true;
				bool			_hoops_PIGRI = true;

				ALLOC_ARRAY_ALIGNED_CACHED (item->points, _hoops_GHSGI, Point, 16);
				ALLOC_ARRAY_CACHED (item->face_list, _hoops_RHSGI, int);
				_hoops_AIGA (points, _hoops_GHSGI, Point, item->points);

				/* _hoops_SSCR _hoops_GGSR _hoops_RSH _hoops_AHPH _hoops_RGHS _hoops_CHR _hoops_GGR _hoops_RH _hoops_SCRPA */
				for (_hoops_SHGRI = 0; _hoops_SHGRI < _hoops_RHSGI; _hoops_GIGRI++)
					_hoops_SHGRI += Abs(face_list[_hoops_SHGRI]) + 1;

				/* _hoops_GISA _hoops_PCCP _hoops_CRPR _hoops_IIAAR _hoops_RH _hoops_HSCHR _hoops_PPR _hoops_ACAGR _hoops_IIGR _hoops_GRR _hoops_HAPR */
				POOL_ALLOC_ARRAY_CACHED (_hoops_RIGRI, _hoops_GIGRI, _hoops_RSSGI, dc->memory_pool);
				_hoops_SHGRI = 0;
				for (i = 0; i < _hoops_GIGRI; i++) {
					int size = Abs(face_list[_hoops_SHGRI]);
					float orientation = 0;

					for (j = _hoops_SHGRI+1; j <= _hoops_SHGRI+size; j++) {
						Point p1 = points[face_list[j]];
						Point p2;
						if (j < _hoops_SHGRI+size)
							p2 = points[face_list[j+1]];
						else
							p2 = points[face_list[_hoops_SHGRI+1]];
						orientation += p1.x * p2.y - p2.x * p1.y;
					}

					_hoops_RIGRI[i]._hoops_ASSGI = _hoops_SHGRI;
					_hoops_RIGRI[i].orientation = (orientation <= 0) ? -1 : 1;
					_hoops_SHGRI += Abs(face_list[_hoops_SHGRI]) + 1;
				}

				for (i = 0; i < _hoops_GIGRI; i++) {
					if (_hoops_RIGRI[i].orientation > 0)
						_hoops_AIGRI = false;
					if (_hoops_RIGRI[i].orientation < 0)
						_hoops_PIGRI = false;
					if (!_hoops_AIGRI && !_hoops_PIGRI)
						break;
				}

				/* _hoops_CGP _hoops_HCR _hoops_RH _hoops_RGHS _hoops_CHR _hoops_PRP, _hoops_PSCR _hoops_SAHR _hoops_IRHH _hoops_RH _hoops_SCRPA _hoops_PRP */
				if (_hoops_AIGRI || _hoops_PIGRI) {
					_hoops_AIGA (face_list, _hoops_RHSGI, int, item->face_list);

					if (_hoops_AIGRI) {
						/* _hoops_ICAH _hoops_IS _hoops_IRHH _hoops_CPS _hoops_GGR _hoops_SCRPA _hoops_RPRHR */
						for (i = 0; i < _hoops_GIGRI; i++) {
							index = _hoops_RIGRI[i]._hoops_ASSGI;
							item->face_list[index] = Abs(item->face_list[index]);
						}
					}
				}
				else {					/* _hoops_HGI _hoops_CRAA _hoops_HRGR _hoops_IHPH... */
					ZERO_STRUCT(&root, _hoops_PSSGI);

					/* _hoops_PSIH _hoops_HCR _hoops_RH _hoops_HAPR _hoops_SHIAR */
					for (i = 0; i < _hoops_GIGRI; i++) {
						Point	*min, *max;
						int			v;
						int			size;

						min = &_hoops_RIGRI[i].min;
						max = &_hoops_RIGRI[i].max;
						index = _hoops_RIGRI[i]._hoops_ASSGI;
						size = Abs(face_list[index]);

						*min = *max = points[face_list[index+1]];
						for (j = index + 1; j < index + 1 + size; j++) {
							v = face_list[j];
							if (points[v].x < min->x) min->x = points[v].x;
							if (points[v].y < min->y) min->y = points[v].y;
							if (points[v].x > max->x) max->x = points[v].x;
							if (points[v].y > max->y) max->y = points[v].y;
						}
					}

					/* _hoops_HIGRI _hoops_RH _hoops_RGHS _hoops_CRGR _hoops_IRS _hoops_IHIR "_hoops_HSSGI" _hoops_HHIS _hoops_ICAAA */
					for (i = 0; i < _hoops_GIGRI; i++)
						_hoops_IRGRI(points, face_list, i, _hoops_RIGRI, &root);

					/* _hoops_PCCIA _hoops_RH _hoops_HHIS _hoops_PPR _hoops_CASRR _hoops_RH _hoops_HACH _hoops_SCRPA. */
					_hoops_RAGRI(face_list, item->face_list, 0, &root);
				}
				FREE_ARRAY (_hoops_RIGRI, _hoops_GIGRI, _hoops_RSSGI);
			}
			else {
				item->points = 0;
				item->face_list = 0;
			}
			item->point_count = _hoops_GHSGI;
			item->face_count = _hoops_RHSGI;
			item->_hoops_IHCGI = _hoops_IHGRI;
			item->_hoops_CHCGI = _hoops_CHGRI;
			item->_hoops_SRCSP = _hoops_SRCSP;
		}

		if (item->point_count == 0)
			goto _hoops_SGHCP;

		if (item->face_count>_hoops_AHSGI) {
			if (_hoops_AHSGI > 0) {
				FREE_ARRAY (points, _hoops_AHSGI, Point);
				FREE_ARRAY (face_list, _hoops_AHSGI, int);
			}
			_hoops_AHSGI = item->face_count;
			ALLOC_ARRAY_CACHED (points, _hoops_AHSGI, Point);
			ALLOC_ARRAY_CACHED (face_list, _hoops_AHSGI, int);
		}

		_hoops_AHGRI = false;

		_hoops_GHRGR = (int)(HD_Compute_Generic_Size (nr,
										_hoops_HRCIR->_hoops_SCPAP,
										_hoops_HRCIR->_hoops_PGHAP,
										1.0f, (_hoops_HRCIR->transform == FT_FULL),
										0, true) + 0.5f);

		if(_hoops_HRCIR->font->_hoops_RACSR > _hoops_GHRGR){
			if(_hoops_HRCIR->_hoops_CSPAP[1] == _hoops_RRHRP)
				_hoops_AHGRI = true;
		}
		else{
			if(_hoops_HRCIR->_hoops_CSPAP[0] == _hoops_RRHRP)
				_hoops_AHGRI = true;
		}


		if (_hoops_HRCIR->outline || _hoops_AHGRI) {
			/* _hoops_RGR _hoops_HRGR _hoops_RH _hoops_PGSA _hoops_ARSGI _hoops_AGIR */
			_hoops_APGRI[3][0] = x;
			_hoops_APGRI[3][1] = y;
			_hoops_APGRI[3][2] = z;

			for (i=0; i<item->point_count; i++) {
				points[i].x = _hoops_HPRA (_hoops_APGRI, item->points[i]);
				points[i].y = _hoops_IPRA (_hoops_APGRI, item->points[i]);
				points[i].z = _hoops_CPRA (_hoops_APGRI, item->points[i]);
			}

			i = 0;

			if (_hoops_HRCIR->transform == FT_FULL) {
				Polyline *	polyline = null;
				Point *		pl;

				while (i < item->face_count) {
					int			_hoops_HSPIR = Abs(item->face_list[i]);

					if (polyline == null || polyline->_hoops_HIHI != 1) {

						if (polyline != null)
							_hoops_HPRH (polyline);

						POOL_ZALLOC (polyline, Polyline, dc->memory_pool);
						polyline->_hoops_HIHI = 1;
						polyline->type = _hoops_IIIP;
						polyline->_hoops_CPGPR = _hoops_PHSSR;
					}

					if (polyline->allocated < _hoops_HSPIR+1) {
						if (polyline->allocated != 0)
						FREE_ARRAY (polyline->points, polyline->allocated, Point);

						polyline->allocated = _hoops_HSPIR + 16;
						POOL_ALLOC_ARRAY_CACHED (polyline->points, polyline->allocated, Point, dc->memory_pool);
					}
					polyline->count = _hoops_HSPIR+1;
					pl = polyline->points;

					_hoops_AIGA (&points[item->face_list[i+1]], _hoops_HSPIR*3, float, pl);
					pl[_hoops_HSPIR].x = points[item->face_list[i+1]+_hoops_HSPIR-1].x;
					pl[_hoops_HSPIR].y = points[item->face_list[i+1]+_hoops_HSPIR-1].y;
					pl[_hoops_HSPIR].z = points[item->face_list[i+1]+_hoops_HSPIR-1].z;

					_hoops_CPAGR (nr, polyline);

					i += _hoops_HSPIR+1;
				}

				_hoops_HPRH (polyline);
			}
			else {
				while (i < item->face_count) {
					int			_hoops_HSPIR = Abs(item->face_list[i]);
					Point	tmp[2];

					_hoops_SCGGA (nr, _hoops_HSPIR, (DC_Point*)&points[item->face_list[i+1]]);

					tmp[0].x = points[item->face_list[i+1]].x;
					tmp[0].y = points[item->face_list[i+1]].y;
					tmp[0].z = points[item->face_list[i+1]].z;
					tmp[1].x = points[item->face_list[i+1]+_hoops_HSPIR-1].x;
					tmp[1].y = points[item->face_list[i+1]+_hoops_HSPIR-1].y;
					tmp[1].z = points[item->face_list[i+1]+_hoops_HSPIR-1].z;

					_hoops_SCGGA (nr, 2, (DC_Point*)tmp);

					i += _hoops_HSPIR+1;
				}
			}
		}
		else {
			if (dc->_hoops_APHHP == null) {
				/* _hoops_RH _hoops_PGSA _hoops_CCGI _hoops_AGIR */

				if (item->_hoops_PCHAR &&
					!BIT(item->_hoops_PCHAR->_hoops_SRHA, DL_TEMPORARY_DATA)) {
					if (_hoops_ISAI (item->_hoops_PCHAR) == 0)
						HI_Free_Tristrip (item->_hoops_PCHAR);
					item->_hoops_PCHAR = null;
				}

				if (item->_hoops_PCHAR == null) {
					HI_Assemble_Simple_Shell_Tristrips (item->point_count, item->points,
														item->face_count, item->face_list,
														&item->_hoops_PCHAR);
					if (item->_hoops_PCHAR == null)
						goto _hoops_SGHCP;
					item->_hoops_PCHAR->point_count = item->point_count;
					item->_hoops_PCHAR->face_count = item->face_count;
					item->_hoops_PCHAR->points = item->points;
					item->_hoops_PCHAR->_hoops_SRHA |= DL_TEMPORARY_DATA;
				}

				if (_hoops_HRCIR->transform != FT_FULL) {
					if (_hoops_HRCIR->transform == FT_NONE) {
						Net_Rendition					_hoops_IIGRI;
						_hoops_HHCR				_hoops_GGCC;
						_hoops_HHRA *						_hoops_CIGRI;

						/* _hoops_GGHP _hoops_ARI _hoops_HPP _hoops_HCGR _hoops_CIHCA */
						_hoops_APGRI[3][0] = x;
						_hoops_APGRI[3][1] = y;
						_hoops_APGRI[3][2] = z;

						for (i=0; i<item->point_count; i++) {
							points[i].x = _hoops_HPRA (_hoops_APGRI, item->points[i]);
							points[i].y = _hoops_IPRA (_hoops_APGRI, item->points[i]);
							points[i].z = _hoops_CPRA (_hoops_APGRI, item->points[i]);
						}

						/*_hoops_IPS _hoops_SHIR _hoops_IPP*/
						_hoops_IIGRI = nr;
						_hoops_GGCC = _hoops_IIGRI.Modify()->transform_rendition.Modify();


						_hoops_GGCC->_hoops_IPH = _hoops_SGCC::Create (dc);
						_hoops_GGCC = null;	//_hoops_IHSA _hoops_HSSRR _hoops_HIS _hoops_SIGRI _hoops_ASSP'_hoops_RA _hoops_IRHH _hoops_GAPR _hoops_HPIH

						ZALLOC(_hoops_CIGRI, _hoops_HHRA);
						HI_Default_Camera(_hoops_CIGRI);
						_hoops_CIGRI->projection = _hoops_CPPCR;
						HD_Downwind_Camera (_hoops_IIGRI, _hoops_CIGRI);
						_hoops_GGCC = _hoops_IIGRI->transform_rendition;	// _hoops_HA _hoops_HGCR _hoops_SCH _hoops_GICS

						_hoops_GGCC->matrix->_hoops_PPRA();
						HI_Compute_Transformed_Points  (item->point_count, points,
														&_hoops_GGCC->matrix->data._hoops_APRA->data.elements[0][0], points);

						item->_hoops_PCHAR->_hoops_SRHA |= _hoops_SRHH;
						item->_hoops_PCHAR->points = points;

						if (BIT(dc->_hoops_PGCC.flags, _hoops_IPPGH) &&
							(dc->_hoops_IPCI->_hoops_RPCGA != HD_Std_DC_Polygon ||
								dc->_hoops_IPCI->_hoops_RPCGA == HD_Hide_DC_Polygon)) {
							_hoops_GSSGI(_hoops_IIGRI, item, points);
						}
						else {
							_hoops_RACIP (_hoops_IIGRI, item->_hoops_PCHAR);
						}
						_hoops_GHGRI = _hoops_HRCIR->width_scale;
					}
					else {
						_hoops_APGRI[3][0] = x;
						_hoops_APGRI[3][1] = y;
						_hoops_APGRI[3][2] = z;

						for (i=0; i<item->point_count; i++) {
							points[i].x = _hoops_HPRA (_hoops_APGRI, item->points[i]);
							points[i].y = _hoops_IPRA (_hoops_APGRI, item->points[i]);
							points[i].z = _hoops_CPRA (_hoops_APGRI, item->points[i]);
						}

						_hoops_IHCR->matrix->_hoops_PPRA();
						HI_Compute_Transformed_Points (item->point_count, points,
													   &_hoops_IHCR->matrix->data._hoops_APRA->data.elements[0][0], points);

						item->_hoops_PCHAR->_hoops_SRHA |= _hoops_SRHH;
						item->_hoops_PCHAR->points = points;

						if (BIT(dc->_hoops_PGCC.flags, _hoops_IPPGH) &&
							(dc->_hoops_IPCI->_hoops_RPCGA != HD_Std_DC_Polygon ||
								dc->_hoops_IPCI->_hoops_RPCGA == HD_Hide_DC_Polygon)) {
							_hoops_GSSGI (nr, item, points);
						}
						else {
							_hoops_RACIP (nr, item->_hoops_PCHAR);
						}
					}

				}
				else {
					Net_Rendition alter &		_hoops_GCGRI = nr;
					_hoops_HHCR			_hoops_GGCC;
					_hoops_SGCC			mat;
					_hoops_SGCC			_hoops_RCGRI;
					Point *						_hoops_ACGRI = 0;
					int *						_hoops_PCGRI = 0;
					int *						_hoops_HCGRI = 0;
					int							_hoops_ICGRI = 0;
					Point *						bbox = 0;
					Point						_hoops_SRHPA[4];
					Point						_hoops_CCGRI, _hoops_SCGRI;
					float						area;

 					_hoops_APGRI[3][0] = x;
					_hoops_APGRI[3][1] = y;
					_hoops_APGRI[3][2] = z;

					_hoops_GGCC = _hoops_GCGRI.Modify()->transform_rendition.Modify();

					_hoops_GGCC->heuristics |= _hoops_GPSA;

					_hoops_RCGRI = _hoops_SGCC::Create (dc);
					_hoops_RCGRI->data._hoops_CPH = _hoops_GGCC->_hoops_IPH->data._hoops_CPH;
					_hoops_RCGRI->data._hoops_RAGR = _hoops_CICH & ~_hoops_HRICR;

					mat = _hoops_SGCC::Create (dc);
					mat->data._hoops_RAGR = _hoops_CICH;

					HI_Compute_Matrix_Product (&_hoops_APGRI[0][0], &_hoops_GGCC->matrix->data.elements[0][0], &mat->data.elements[0][0]);
					HI_Compute_Matrix_Product (&_hoops_APGRI[0][0], &_hoops_GGCC->_hoops_IPH->data.elements[0][0],
												&_hoops_RCGRI->data.elements[0][0]);

					_hoops_GGCC->_hoops_IPH = _hoops_RCGRI;
					_hoops_GGCC->matrix = mat;

					item->_hoops_PCHAR->_hoops_SRHA |= DL_SUPPRESS_SEGMENT_DISPLAY_LISTS;
					item->_hoops_PCHAR->_hoops_SRHA &= ~DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS;
					item->_hoops_PCHAR->points = item->points;

					if (!nr->_hoops_SISI->_hoops_CCRIP) {
						if (BIT(dc->_hoops_PGCC.flags, _hoops_IPPGH) &&
							(dc->_hoops_IPCI->_hoops_RPCGA != HD_Std_DC_Polygon ||
								dc->_hoops_IPCI->_hoops_RPCGA == HD_Hide_DC_Polygon)) {
							_hoops_GSSGI(_hoops_GCGRI, item, item->points);
						}
						else {
							_hoops_RACIP (_hoops_GCGRI, item->_hoops_PCHAR);
						}
					}
					else {
						if (item->_hoops_SHCGI == 0) {
							POOL_ZALLOC(item->_hoops_SHCGI, _hoops_HHCGI, dc->memory_pool);
							bbox = item->_hoops_SHCGI->bbox;

							bbox[0] = points[0];
							bbox[2] = points[0];
							bbox[0].z = 0;
							bbox[1].z = 0;
							bbox[2].z = 0;
							bbox[3].z = 0;
							for (i = 1 ; i < item->_hoops_PCHAR->point_count ; i++) {
								if (bbox[2].x < points[i].x)
									bbox[2].x = points[i].x;
								if (bbox[2].y < points[i].y)
									bbox[2].y = points[i].y;

								if (bbox[0].x > points[i].x)
									bbox[0].x = points[i].x;
								if (bbox[0].y > points[i].y)
									bbox[0].y = points[i].y;
							}

							bbox[1].x = bbox[0].x;
							bbox[1].y = bbox[2].y;
							bbox[3].x = bbox[2].x;
							bbox[3].y = bbox[0].y;
						}
						else
							bbox = item->_hoops_SHCGI->bbox;

						HI_Compute_Transformed_Points(4, bbox, &mat->data.elements[0][0], _hoops_SRHPA);
						_hoops_CCGRI = _hoops_SRHPA[0];
						_hoops_SCGRI = _hoops_SRHPA[0];
 						for (i=0; i<4; i++) {
							if (_hoops_SCGRI.x < _hoops_SRHPA[i].x)
								_hoops_SCGRI.x = _hoops_SRHPA[i].x;
							if (_hoops_SCGRI.y < _hoops_SRHPA[i].y)
								_hoops_SCGRI.y = _hoops_SRHPA[i].y;

							if (_hoops_CCGRI.x > _hoops_SRHPA[i].x)
								_hoops_CCGRI.x = _hoops_SRHPA[i].x;
							if (_hoops_CCGRI.y > _hoops_SRHPA[i].y)
								_hoops_CCGRI.y = _hoops_SRHPA[i].y;
						}

						area = (_hoops_SCGRI.x - _hoops_CCGRI.x) * (_hoops_SCGRI.y - _hoops_CCGRI.y);
						area = 100.0f * area /
							((nr->_hoops_SAIR->_hoops_CIIH.right - nr->_hoops_SAIR->_hoops_CIIH.left) *
							 (nr->_hoops_SAIR->_hoops_CIIH.top - nr->_hoops_SAIR->_hoops_CIIH.bottom));
						if (area > _hoops_SRCGI) {
							_hoops_RACIP (_hoops_GCGRI, item->_hoops_PCHAR);
						}
						if (area < _hoops_GACGI)  {
							Polyedge *pe = item->_hoops_SHCGI->polyedge;

							if (pe == 0) {
								Point		_hoops_RICIR;
								int				_hoops_GSGRI, _hoops_PPISP, _hoops_RSGRI,j;

								POOL_ZALLOC (pe, Polyedge, dc->memory_pool);
								_hoops_ICAI (pe);
								item->_hoops_SHCGI->polyedge = pe;

								for (i=0; i<item->_hoops_PCHAR->_hoops_PHHA; i++)
 									_hoops_ICGRI += item->_hoops_PCHAR->lengths[i] - 2;

								int _hoops_ASGRI = _hoops_ICGRI * 4;
								int _hoops_PSGRI = _hoops_ICGRI * 4;
								int _hoops_HSGRI = _hoops_ICGRI;
								
								ALLOC_ARRAY_ALIGNED_CACHED (_hoops_ACGRI, _hoops_ASGRI, Point, 16);
								ALLOC_ARRAY_CACHED (_hoops_PCGRI, _hoops_PSGRI, int);
 								ALLOC_ARRAY_CACHED (_hoops_HCGRI, _hoops_HSGRI, int);

								_hoops_PPISP = 0;
								_hoops_GSGRI = 0;
								_hoops_ICGRI=0;
								for (i=0; i<item->_hoops_PCHAR->_hoops_PHHA; i++) {
									_hoops_RSGRI = _hoops_GSGRI;
									for (j=0; j<item->_hoops_PCHAR->lengths[i]-2; j++) {
										int _hoops_ISGRI, _hoops_CSGRI, _hoops_SSGRI;

										_hoops_SSGRI = item->_hoops_PCHAR->_hoops_AIHA[j+_hoops_PPISP + 1];
										_hoops_CSGRI = item->_hoops_PCHAR->_hoops_AIHA[j+_hoops_PPISP];
										_hoops_ISGRI = item->_hoops_PCHAR->_hoops_AIHA[j+_hoops_PPISP + 2];

										_hoops_RICIR.x = (item->points[_hoops_SSGRI].x + item->points[_hoops_CSGRI].x + item->points[_hoops_ISGRI].x) / 3.0f;
										_hoops_RICIR.y = (item->points[_hoops_SSGRI].y + item->points[_hoops_CSGRI].y + item->points[_hoops_ISGRI].y) / 3.0f;
										_hoops_RICIR.z = (item->points[_hoops_SSGRI].z + item->points[_hoops_CSGRI].z + item->points[_hoops_ISGRI].z) / 3.0f;

										_hoops_ACGRI[_hoops_GSGRI] = item->points[_hoops_ISGRI];
										_hoops_ACGRI[_hoops_GSGRI].x = _hoops_ACGRI[_hoops_GSGRI].x - (_hoops_ACGRI[_hoops_GSGRI].x - _hoops_RICIR.x)*0.4f;
										_hoops_ACGRI[_hoops_GSGRI].y = _hoops_ACGRI[_hoops_GSGRI].y - (_hoops_ACGRI[_hoops_GSGRI].y - _hoops_RICIR.y)*0.4f;
										_hoops_ACGRI[_hoops_GSGRI].z = _hoops_ACGRI[_hoops_GSGRI].z - (_hoops_ACGRI[_hoops_GSGRI].z - _hoops_RICIR.z)*0.4f;
										_hoops_PCGRI[_hoops_GSGRI] = _hoops_GSGRI;
										_hoops_GSGRI++;

										_hoops_ACGRI[_hoops_GSGRI] = item->points[_hoops_CSGRI];
										_hoops_ACGRI[_hoops_GSGRI].x = _hoops_ACGRI[_hoops_GSGRI].x - (_hoops_ACGRI[_hoops_GSGRI].x - _hoops_RICIR.x)*0.4f;
										_hoops_ACGRI[_hoops_GSGRI].y = _hoops_ACGRI[_hoops_GSGRI].y - (_hoops_ACGRI[_hoops_GSGRI].y - _hoops_RICIR.y)*0.4f;
										_hoops_ACGRI[_hoops_GSGRI].z = _hoops_ACGRI[_hoops_GSGRI].z - (_hoops_ACGRI[_hoops_GSGRI].z - _hoops_RICIR.z)*0.4f;
										_hoops_PCGRI[_hoops_GSGRI] = _hoops_GSGRI;
										_hoops_GSGRI++;
										_hoops_ACGRI[_hoops_GSGRI] = item->points[_hoops_SSGRI];
										_hoops_ACGRI[_hoops_GSGRI].x = _hoops_ACGRI[_hoops_GSGRI].x - (_hoops_ACGRI[_hoops_GSGRI].x - _hoops_RICIR.x)*0.4f;
										_hoops_ACGRI[_hoops_GSGRI].y = _hoops_ACGRI[_hoops_GSGRI].y - (_hoops_ACGRI[_hoops_GSGRI].y - _hoops_RICIR.y)*0.4f;
										_hoops_ACGRI[_hoops_GSGRI].z = _hoops_ACGRI[_hoops_GSGRI].z - (_hoops_ACGRI[_hoops_GSGRI].z - _hoops_RICIR.z)*0.4f;
										_hoops_PCGRI[_hoops_GSGRI] = _hoops_GSGRI;
										_hoops_GSGRI++;
										_hoops_ACGRI[_hoops_GSGRI] = item->points[_hoops_ISGRI];
										_hoops_ACGRI[_hoops_GSGRI].x = _hoops_ACGRI[_hoops_GSGRI].x - (_hoops_ACGRI[_hoops_GSGRI].x - _hoops_RICIR.x)*0.4f;
										_hoops_ACGRI[_hoops_GSGRI].y = _hoops_ACGRI[_hoops_GSGRI].y - (_hoops_ACGRI[_hoops_GSGRI].y - _hoops_RICIR.y)*0.4f;
										_hoops_ACGRI[_hoops_GSGRI].z = _hoops_ACGRI[_hoops_GSGRI].z - (_hoops_ACGRI[_hoops_GSGRI].z - _hoops_RICIR.z)*0.4f;
										_hoops_PCGRI[_hoops_GSGRI] = _hoops_GSGRI;
										_hoops_GSGRI++;
										_hoops_HCGRI[_hoops_ICGRI] = 4;
										_hoops_ICGRI++;
									}

									_hoops_PPISP += item->_hoops_PCHAR->lengths[i];
								}

								pe->_hoops_RAHH = _hoops_AAHH|_hoops_AIPI;
								pe->lengths = _hoops_HCGRI;
								pe->lengths_allocated = _hoops_HSGRI;
								pe->_hoops_AIHA = _hoops_PCGRI;
								pe->_hoops_IPII = _hoops_PSGRI;
								pe->total = _hoops_GSGRI;
								pe->_hoops_PHHA = _hoops_ICGRI;
								pe->points = _hoops_ACGRI;
								pe->point_count = _hoops_ASGRI;
								pe->_hoops_SRHA = DL_SUPPRESS_SEGMENT_DISPLAY_LISTS; //_hoops_GGRRI _hoops_RGAR
							}

							_hoops_RAIGH (_hoops_GCGRI, item->_hoops_SHCGI->polyedge);
						}
					}
				}
			}
			else {
				/* _hoops_CSPH->_hoops_PIICP != _hoops_IRAP */
				Vector			normal;
				DC_Point *		_hoops_CGCAR;
				float *			ws;
				_hoops_GRCAR *		_hoops_RRCAR;
				int				_hoops_CRCAR;
				int				count;

				_hoops_APGRI[3][0] = x;
				_hoops_APGRI[3][1] = y;
				_hoops_APGRI[3][2] = z;

				for (i=0; i<item->point_count; i++) {
					points[i].x = _hoops_HPRA (_hoops_APGRI, item->points[i]);
					points[i].y = _hoops_IPRA (_hoops_APGRI, item->points[i]);
					points[i].z = _hoops_CPRA (_hoops_APGRI, item->points[i]);
				}

				if (_hoops_HRCIR->transform == FT_FULL)
					HI_Compute_Transformed_Points (item->point_count, points, &_hoops_IHCR->matrix->data.elements[0][0], points);

				count = item->point_count;

				normal.x = 0;
				normal.y = 0;
				normal.z = 1;

				POOL_ALLOC_ARRAY_ALIGNED_CACHED (_hoops_CGCAR, count, DC_Point, 16, dc->memory_pool);
				POOL_ALLOC_ARRAY_ALIGNED_CACHED (ws, count, float, 16, dc->memory_pool);
				POOL_ALLOC_ARRAY_CACHED (_hoops_RRCAR, count, _hoops_GRCAR, dc->memory_pool);

				_hoops_CRCAR = HD_Transform_Not_At_All (_hoops_IHCR,
						count, points, null, &nr->_hoops_SAIR->_hoops_HHCAR, _hoops_CGCAR, ws, _hoops_RRCAR);

				if (_hoops_CRCAR == 0) {
					_hoops_GRCAR const *_hoops_ARCAR = _hoops_RRCAR;
					int			_hoops_IHCAR;
					int			remaining = count;

					_hoops_IHCAR = (int)*_hoops_ARCAR;
					++_hoops_ARCAR;
					--remaining;

					_hoops_RGGA (remaining-- == 0) {
						_hoops_IHCAR &= (int)*_hoops_ARCAR;

						if (_hoops_IHCAR == 0) {
							_hoops_CRCAR = 1;	/* _hoops_RGRRI, _hoops_RSPH _hoops_SPR _hoops_GIAA */
							break;
						}
						++_hoops_ARCAR;
					}
				}

				if (BIT (_hoops_IHCR->flags, _hoops_CSP)) {
					int		_hoops_RICAR;

					_hoops_RICAR = HD_Compute_Trimmed_Clip_Points (_hoops_IHCR, count, _hoops_CGCAR, ws, _hoops_RRCAR);
					if (_hoops_CRCAR > _hoops_RICAR) _hoops_CRCAR = _hoops_RICAR;
				}

				if (_hoops_CRCAR != 0) {
					struct _hoops_PIPHA		data;
					int					j = 0;

					data._hoops_APHGA = nr;
					data.points = _hoops_CGCAR;
					data._hoops_RRCAR = _hoops_RRCAR;

					i = 0;
					while (i < item->face_count) {
						j = i + item->face_list[i] + 1;

						while ((j < item->face_count) && (item->face_list[j]<0)) {
							j += Abs(item->face_list[j]) + 1;
						}

						HI_Triangulate_Face_X (item->points, &normal,
												&item->face_list[i], &item->face_list[j],
												_hoops_SCSGI, (void *)&data);

						i = j;
					}
				}

				FREE_ARRAY_ALIGNED (_hoops_CGCAR, count, DC_Point, 16);
				FREE_ARRAY_ALIGNED (ws, count, float, 16);
				FREE_ARRAY (_hoops_RRCAR, count, _hoops_GRCAR);
			}
		}

_hoops_SGHCP:
		_hoops_CPGRI.x = item->_hoops_IHCGI * (scale->x * _hoops_HRCIR->font->_hoops_GCHSA * _hoops_HRCIR->font->_hoops_GRGGH)*_hoops_GHGRI;
		_hoops_CPGRI.y = item->_hoops_CHCGI * (scale->y * _hoops_HRCIR->font->_hoops_GCHSA * _hoops_HRCIR->font->_hoops_GRGGH)*_hoops_GHGRI;

		if (_hoops_HRCIR->rotation != 0.0f)
			HI_Compute_Transformed_Points (1, &_hoops_CPGRI, &_hoops_PPGRI[0][0], &_hoops_CPGRI);

		x += _hoops_CPGRI.x;
		y += _hoops_CPGRI.y;
	}

	if (_hoops_AHSGI > 0) {
		FREE_ARRAY (points, _hoops_AHSGI, Point);
		FREE_ARRAY (face_list, _hoops_AHSGI, int);
	}

#undef _hoops_SAGRI

	(void)error;		/* _hoops_ARP _hoops_HIH _hoops_HAR _hoops_IGI _hoops_IAII */
}


GLOBAL_FUNCTION void HD_Draw_Freetype_Font (
	Net_Rendition const & 	nr,
	Font_Instance const *	instance,
	Point const *			where,
	int						count,
	Karacter const *		string,
	Vector const *			scale) {

	if (BIT(nr->_hoops_SRA->_hoops_PGCC.flags, _hoops_HPPGH))
		_hoops_GACIP(nr, _hoops_SRCSR)(nr, instance, where, count, string, scale);
	else if (instance->_hoops_RRGGH)
		HD_Draw_Stenciled_Font(nr, instance, where, count, string, scale);
	else
		_hoops_GPGRI	(nr, instance, where, count, string, scale);
}


GLOBAL_FUNCTION void HD_Gather_Freetype_Text (
	Net_Rendition const & 		nr,
	Font_Instance const *		specific,
	int							count,
	Karacter const *			string,
	Vector const *				scale,
	_hoops_IHGRP				encoding,
	_hoops_PGHGH *			_hoops_GCHIH) {
	_hoops_GPGGH *				_hoops_RSCGI = (_hoops_GPGGH *) specific->_hoops_GAASR;
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	_hoops_GRCGI *		_hoops_SCCGI = (_hoops_GRCGI*)_hoops_RSCGI->_hoops_RPGGH;
	int							error;
	int							height;
	int							_hoops_AHSGI = 1024;
	Point *						points;
	int *						face_list;
	int							_hoops_GHSGI = 0;
	int							_hoops_RHSGI = 0;
	int							bolding_level = 0;

	UNREFERENCED (scale);
	UNREFERENCED (encoding);


	if (HOOPS_WORLD->global_font_data_freetype == null) {
		_hoops_RICGI("Request to draw Freetype font without global data", 0);
		return;
	}

	ALLOC_ARRAY (points, _hoops_AHSGI, Point);
	ALLOC_ARRAY (face_list, _hoops_AHSGI, int);

	height = (int)(_hoops_HRCIR->font->_hoops_ISISR * _hoops_HRCIR->font->_hoops_GRGGH);

	if (height < 24)
		height = 24;

	if (_hoops_SCCGI->_hoops_IRCGI != height*64) {
		_hoops_SCCGI->_hoops_IRCGI = height*64;
		error = FT_Set_Char_Size (_hoops_SCCGI->face, 0, _hoops_SCCGI->_hoops_IRCGI, _hoops_CRCGI, _hoops_CRCGI);
	}

	_hoops_IISGI (_hoops_SCCGI, height, bolding_level, count, _hoops_HRCIR->_hoops_IPGRP, _hoops_HRCIR->rotation, _hoops_HRCIR->width_scale,
		string, &points, &face_list, &_hoops_AHSGI, &_hoops_GHSGI, &_hoops_RHSGI, 0,0,0);

	_hoops_GCHIH->face_list_length = _hoops_RHSGI;
	_hoops_GCHIH->count = _hoops_GHSGI;

	if (_hoops_GCHIH->points && _hoops_GCHIH->face_list) {
		float	_hoops_IHPIA[4][4];

		HI_Compute_Scale_Matrix (_hoops_HRCIR->font->_hoops_GRGGH/(float)height, _hoops_HRCIR->font->_hoops_GRGGH/(float)height, 1.0f,
								 &_hoops_IHPIA[0][0]);

		HI_Compute_Transformed_Points (_hoops_GHSGI, points, &_hoops_IHPIA[0][0], _hoops_GCHIH->points);
		_hoops_AIGA (face_list, _hoops_RHSGI, int, _hoops_GCHIH->face_list);
	}

	FREE_ARRAY (points, _hoops_AHSGI, Point);
	FREE_ARRAY (face_list, _hoops_AHSGI, int);

	(void)error;		/* _hoops_ARP _hoops_HIH _hoops_HAR _hoops_IGI _hoops_IAII */
}



GLOBAL_FUNCTION void HD_Free_Freetype_Globals (
	_hoops_IGHGP *				_hoops_SSGGA) {
	_hoops_PPGGH *	_hoops_PICGI;
	FT_Library *		_hoops_HPGGH;
	_hoops_RPCGI *		file;
	_hoops_IPCGI *		_hoops_IPGGH;
	_hoops_SACGI *	font_name;

	UNREFERENCED(_hoops_SSGGA);

	if ((_hoops_HPGGH = _hoops_AICGI(false)) != null)
		FT_Done_FreeType (*_hoops_HPGGH);

	if ((_hoops_PICGI = (_hoops_PPGGH *)HOOPS_WORLD->global_font_data_freetype) == null)
		return;

	_hoops_IPGGH = (_hoops_IPCGI *) _hoops_PICGI->_hoops_IPGGH;
	font_name = _hoops_IPGGH->_hoops_HGPIR;

	while (font_name) {
		_hoops_SACGI *	next = font_name->next;

		if (font_name->name)
			FREE_ARRAY (font_name->name, _hoops_SSGR (font_name->name)+1, char);
		if (font_name->_hoops_AACGI)
			FREE_ARRAY (font_name->_hoops_AACGI, _hoops_SSGR (font_name->_hoops_AACGI)+1, char);
		if (font_name->_hoops_SSISR)
			FREE_ARRAY (font_name->_hoops_SSISR, _hoops_SSGR (font_name->_hoops_SSISR)+1, char);
		if (font_name->_hoops_PACGI)
			FREE_ARRAY (font_name->_hoops_PACGI, _hoops_SSGR (font_name->_hoops_PACGI)+1, char);
		if (font_name->_hoops_HACGI)
			FREE_ARRAY (font_name->_hoops_HACGI, _hoops_SSGR (font_name->_hoops_HACGI)+1, char);
		if (font_name->_hoops_IACGI)
			FREE_ARRAY (font_name->_hoops_IACGI, _hoops_SSGR (font_name->_hoops_IACGI)+1, char);

		FREE (font_name, _hoops_SACGI);

		font_name = next;
	}

	file = _hoops_IPGGH->_hoops_PPCGI;

	while (file) {
		_hoops_RPCGI	*	tmp;

		FREE_ARRAY (file->name, _hoops_SSGR (file->name)+1, char);
		tmp = file;
		file = file->next;
		FREE (tmp, _hoops_RPCGI);
	}

	FREE(_hoops_IPGGH, _hoops_IPCGI);

	FREE (_hoops_PICGI->_hoops_HPGGH, FT_Library);

	FREE (_hoops_PICGI, _hoops_PPGGH);
	HOOPS_WORLD->global_font_data_freetype = null;
}


local bool _hoops_AGRRI (char const *_hoops_PGRRI, char const *_hoops_HGRRI)
{
	char const *_hoops_AIPPA, *_hoops_PIPPA;

	if (!_hoops_PGRRI || !_hoops_HGRRI)
		return false;

	/* _hoops_SSS _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_GIPR _hoops_RHIPP */
	for (_hoops_AIPPA = _hoops_PGRRI;  *_hoops_AIPPA != '\0'; _hoops_AIPPA++)
		; /* _hoops_AA _hoops_ISAP */
	for (_hoops_PIPPA = _hoops_HGRRI; *_hoops_PIPPA != '\0'; _hoops_PIPPA++)
		; /* _hoops_AA _hoops_ISAP */

	for (;;) {
		if (*_hoops_AIPPA != *_hoops_PIPPA)
			return false;
		if (_hoops_AIPPA == _hoops_PGRRI || _hoops_PIPPA == _hoops_HGRRI)
			return true;  /* _hoops_RHHR _hoops_RH _hoops_RSGI _hoops_IIGR _hoops_SPR _hoops_IIGR _hoops_RH _hoops_RHIPP */
		_hoops_AIPPA--;
		_hoops_PIPPA--;
	}
}


local void _hoops_IGRRI (
		char const *				_hoops_CGRRI,
		Display_Context const *	dc,
		_hoops_SACGI *			font_name) {

	HD_Record_Font_With_Encoding (dc, _hoops_CGRRI, null,
					font_name->encoding, 0.0f, 1.7f);
	/* _hoops_HCR _hoops_SGRRI _hoops_GSPIP _hoops_CHR _hoops_GRRRI */
	if (!HD_Mark_Font_As_Transformable (dc, _hoops_CGRRI, _hoops_IAGGH) ||
		!HD_Mark_Font_As_Freetype (dc, _hoops_CGRRI))
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						   "Unexpected problem marking font");
	/* _hoops_RPP _hoops_RH _hoops_CRSRR _hoops_GSGR _hoops_HRGR _hoops_HAR _hoops_RH _hoops_PSHR _hoops_GAR _hoops_RH _hoops_RGHR _hoops_RSIRR _hoops_SGS _hoops_RH _hoops_HRCSR _hoops_PISRA _hoops_HII,
			_hoops_HPGGR _hoops_SCH _hoops_GAR _hoops_PCCP _hoops_PHPPR */
	if (!_hoops_IGGPA (font_name->name, _hoops_CGRRI)) {
		if (!HD_Mark_Font_As_Aliased (dc, _hoops_CGRRI, font_name->name, font_name->index))
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "Unexpected problem marking font as 'aliased'");
	}
}

//#_hoops_PPIP _hoops_RRRRI
#ifdef _hoops_ARRRI
#include <stdio.h>
static FILE *_hoops_PRRRI=NULL;
#endif

local bool _hoops_HRRRI (
	FT_Library *		_hoops_HPGGH,
	_hoops_IPCGI *		_hoops_IPGGH,
	char const *		_hoops_IRRRI,
	char const *		_hoops_HSCGI,
	char const *		_hoops_CRRRI) {
	char				_hoops_AACGI[4096];
	char				_hoops_PACGI[4096];
	_hoops_RPCGI *		file = _hoops_IPGGH->_hoops_PPCGI;
	_hoops_SACGI *	_hoops_SRRRI = null;
	_hoops_SACGI *	_hoops_GARRI = null;
	long				_hoops_SSPAR = 0, _hoops_RARRI = -1;
	_hoops_IHGRP		encoding;
	int					error = 0;
	bool				_hoops_AARRI = false;
	bool				_hoops_PARRI = (_hoops_CRRRI != null);

	/* _hoops_SRS _hoops_ISPR _hoops_RPP _hoops_RGR _hoops_RGHR _hoops_SSCP _hoops_RPII _hoops_HPPP _hoops_GAPR */
	while (file) {
		if (_hoops_AGGR (file->name, _hoops_IRRRI))
			return _hoops_AARRI;
		file = file->next;
	}

#ifdef _hoops_ARRRI
	if (_hoops_PRRRI == NULL)
		_hoops_PRRRI = fopen("ffile.txt", "w+");

	fprintf(_hoops_PRRRI,"%s %s %s\n", _hoops_IRRRI, _hoops_HSCGI, _hoops_CRRRI);
	fflush(_hoops_PRRRI);
#endif

	ASSERT (file == null);

	while (1) {
		FT_Face				face;
		_hoops_SACGI *	font_name;
		char const *		_hoops_SSISR;

		if ((error = FT_New_Face (*_hoops_HPGGH, _hoops_HSCGI, _hoops_SSPAR, &face)) != 0)
			break;

		if (face->num_charmaps == 0) {
			FT_Done_Face (face);
			break;
		}

		if (file == null) {
			ZALLOC (file, _hoops_RPCGI);
			ALLOC_ARRAY (file->name, _hoops_SSGR (_hoops_IRRRI)+1, char);
			_hoops_AAHR (_hoops_IRRRI, file->name);
			file->next = _hoops_IPGGH->_hoops_PPCGI;
			_hoops_IPGGH->_hoops_PPCGI = file;
		}

		if (!face->charmap)
			FT_Select_Charmap (face, FT_ENCODING_APPLE_ROMAN);

		if (face->charmap)
			encoding = _hoops_SACSR;
		else
			encoding = _hoops_RGHPH;


		if (!face->style_name || face->style_name[0] == '\0') {
			sprintf(_hoops_AACGI, "%s", face->family_name);
			_hoops_PACGI[0] = '\0';
		}
		else {
			sprintf(_hoops_AACGI, "%s %s", face->family_name, face->style_name);

			if (_hoops_AGRRI("Regular",face->style_name) ||
				_hoops_AGRRI("Normal",face->style_name) ||
				_hoops_AGRRI("Medium",face->style_name) ||
				(_hoops_AGRRI("Roman", face->style_name) &&
				 _hoops_AGRRI("BT", face->family_name)) ){
				strcpy(_hoops_PACGI,face->family_name);
			}
			else
				_hoops_PACGI[0] = '\0';
		}


		if (_hoops_AACGI[0] != '\0') {
			ZALLOC (font_name, _hoops_SACGI);
			ALLOC_ARRAY (font_name->_hoops_IACGI, _hoops_SSGR (_hoops_HSCGI)+1, char);
			_hoops_AAHR (_hoops_HSCGI, font_name->_hoops_IACGI);
			ALLOC_ARRAY (font_name->name, _hoops_SSGR (_hoops_IRRRI)+1, char);
			_hoops_AAHR (_hoops_IRRRI, font_name->name);
			ALLOC_ARRAY (font_name->_hoops_AACGI, (long)strlen(_hoops_AACGI)+1, char);
			_hoops_AAHR (_hoops_AACGI, font_name->_hoops_AACGI);
			if (_hoops_PACGI[0] != '\0') {
				ALLOC_ARRAY (font_name->_hoops_PACGI, (long)strlen(_hoops_PACGI)+1, char);
				_hoops_AAHR (_hoops_PACGI, font_name->_hoops_PACGI);
			}
			if (_hoops_CRRRI && !_hoops_AARRI &&
				_hoops_IGGPA (_hoops_CRRRI, font_name->_hoops_AACGI))
				_hoops_AARRI = true;
			if ((_hoops_SSISR = FT_Get_Postscript_Name(face)) != null) {
				ALLOC_ARRAY (font_name->_hoops_SSISR, (long)strlen(_hoops_SSISR)+1, char);
				_hoops_AAHR (_hoops_SSISR, font_name->_hoops_SSISR);
				if (_hoops_CRRRI && !_hoops_AARRI &&
					_hoops_IGGPA (_hoops_CRRRI, font_name->_hoops_SSISR))
					_hoops_AARRI = true;
			}
			else
				font_name->_hoops_SSISR = null;

			/* _hoops_GAAP _hoops_HHH _hoops_RII _hoops_RPIHR _hoops_GH _hoops_RSIRR */
			if (_hoops_PARRI) {
				if ((font_name->name && !_hoops_IGGPA (_hoops_CRRRI, font_name->name)) &&
				(font_name->_hoops_AACGI && !_hoops_IGGPA (_hoops_CRRRI, font_name->_hoops_AACGI)) &&
				(font_name->_hoops_SSISR && !_hoops_IGGPA (_hoops_CRRRI, font_name->_hoops_SSISR)) &&
				(font_name->_hoops_PACGI && !_hoops_IGGPA (_hoops_CRRRI, font_name->_hoops_PACGI))) {
					// _hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_PSSP _hoops_GII _hoops_HSSPR _hoops_RSIRR, _hoops_SR _hoops_GHCA _hoops_HGGC _hoops_RRP _hoops_IRS _hoops_GGCH
				}
				else
					_hoops_PARRI = false;
			}


			font_name->index = _hoops_SSPAR;
			if (_hoops_SSPAR == 0) {
				_hoops_RARRI = face->num_faces;
			}
			font_name->encoding = encoding;
			font_name->_hoops_CACGI = false;

			font_name->next = _hoops_IPGGH->_hoops_HGPIR;
			_hoops_IPGGH->_hoops_HGPIR = font_name;

			if (_hoops_SRRRI == null &&
				(_hoops_AGRRI("Regular",face->style_name) ||
				_hoops_AGRRI("Normal",face->style_name) ||
				 _hoops_AGRRI("Medium",face->style_name))) {
				_hoops_SRRRI = font_name;
				_hoops_GARRI = font_name;

				if (_hoops_CRRRI && !_hoops_AARRI) {
					char *	ptr = _hoops_CCGGI (' ', font_name->_hoops_AACGI);
					if (ptr) {
						*ptr = '\0';
						if (_hoops_IGGPA (_hoops_CRRRI, font_name->_hoops_AACGI))
							_hoops_AARRI = true;
						*ptr = ' ';
					}
				}
			}
			else if (_hoops_GARRI == null)
				_hoops_GARRI = font_name;
		}

		FT_Done_Face (face);
		_hoops_SSPAR++;
		if (_hoops_SSPAR == _hoops_RARRI)
			break;
	}

	if (_hoops_SRRRI == null)
		_hoops_SRRRI = _hoops_GARRI;

	if (!_hoops_SRRRI)
		return false;

		_hoops_SRRRI->_hoops_CACGI = true;

	if (_hoops_PARRI) {
		ALLOC_ARRAY (_hoops_GARRI->_hoops_HACGI, (long)strlen(_hoops_CRRRI)+1, char);
		_hoops_AAHR (_hoops_CRRRI, _hoops_GARRI->_hoops_HACGI);
	}

	return _hoops_AARRI;
}

local void _hoops_HARRI (
	Display_Context const *	dc,
	_hoops_SACGI *			font_name) {

	while (font_name) {
		if (font_name->_hoops_AACGI) {
			const char * iname = font_name->_hoops_AACGI;

			if (_hoops_IGGPA (iname, "roman"))
				iname = "roman-TTF";
			else if (_hoops_IGGPA (iname, "san serif"))
				iname = "san serif-TTF";
			else if (_hoops_IGGPA (iname, "stroked"))
				iname = "stroked-TTF";
			else if (_hoops_IGGPA (iname, "system default"))
				iname = "system default-TTF";
			else if (_hoops_IGGPA (iname, "typewriter"))
				iname = "typewriter-TTF";

			_hoops_IGRRI(iname, dc, font_name);
			if (_hoops_AGRRI("Regular",iname) ||
				_hoops_AGRRI("Normal",iname) ||
				_hoops_AGRRI("Medium",iname)) {
				char *	ptr = _hoops_CCGGI (' ', font_name->_hoops_AACGI);
				if (ptr) {
					*ptr = '\0';
					_hoops_IGRRI(font_name->_hoops_AACGI, dc, font_name);
					*ptr = ' ';
				}
			}
			if (font_name->_hoops_CACGI)
				_hoops_IGRRI(font_name->name, dc, font_name);

			if (font_name->_hoops_SSISR)
				_hoops_IGRRI(font_name->_hoops_SSISR, dc, font_name);
			if (font_name->_hoops_PACGI) {
				iname = font_name->_hoops_PACGI;

				if (_hoops_IGGPA (iname, "roman"))
					iname = "roman-TTF";
				else if (_hoops_IGGPA (iname, "san serif"))
					iname = "san serif-TTF";
				else if (_hoops_IGGPA (iname, "stroked"))
					iname = "stroked-TTF";
				else if (_hoops_IGGPA (iname, "system default"))
					iname = "system default-TTF";
				else if (_hoops_IGGPA (iname, "typewriter"))
					iname = "typewriter-TTF";
				_hoops_IGRRI(iname, dc, font_name);
			}
			if (font_name->_hoops_HACGI) {
				iname = font_name->_hoops_HACGI;

				if (_hoops_IGGPA (iname, "roman"))
					iname = "roman-TTF";
				else if (_hoops_IGGPA (iname, "san serif"))
					iname = "san serif-TTF";
				else if (_hoops_IGGPA (iname, "stroked"))
					iname = "stroked-TTF";
				else if (_hoops_IGGPA (iname, "system default"))
					iname = "system default-TTF";
				else if (_hoops_IGGPA (iname, "typewriter"))
					iname = "typewriter-TTF";
				_hoops_IGRRI(iname, dc, font_name);
			}
		}
		else {
			/* _hoops_HGAPR _hoops_IARRI _hoops_RCSPR _hoops_CGHGH _hoops_CARRI _hoops_GCGIH _hoops_CAAPA */
			_hoops_IGRRI (font_name->name, dc, font_name);
		}

		font_name = font_name->next;
	}
}

#ifdef OSX_SYSTEM

#ifdef __x86_64__	

#define Point _hoops_SARRI
#define Style OSX_Style
#define Marker _hoops_GPRRI
#define Polygon _hoops_RPRRI
#define Button OSX_Button
#define Line _hoops_APRRI
#undef local

#include <ApplicationServices/ApplicationServices.h>

#define local static
#undef Point
#undef Style
#undef Marker
#undef Polygon
#undef Button
#undef Line

local bool _hoops_PPRRI(const char *_hoops_HPRRI, char *file, char *_hoops_IPRRI, int limit) {	
	
	CFStringRef _hoops_CPRRI = CFStringCreateWithCString(null,_hoops_HPRRI,kCFStringEncodingUTF8);
	CFArrayRef _hoops_SPRRI = CTFontManagerCopyAvailableFontURLs();
	CFArrayRef _hoops_GHRRI = null;
	bool status = false;
	_hoops_IPRRI[0] = '\0';
		
	for (int i = 0 ; i < CFArrayGetCount(_hoops_SPRRI) ; i++) {
	
		CFURLRef url = (CFURLRef)CFArrayGetValueAtIndex(_hoops_SPRRI,i);				
		CFArrayRef _hoops_GHRRI = CTFontManagerCreateFontDescriptorsFromURL(url);		
		
		for (int j = 0 ; j < CFArrayGetCount(_hoops_GHRRI) ; j++) {
			
			CTFontDescriptorRef desc = (CTFontDescriptorRef)CFArrayGetValueAtIndex(_hoops_GHRRI,j);
			CFStringRef _hoops_RHRRI = (CFStringRef)CTFontDescriptorCopyAttribute(desc,kCTFontNameAttribute);
			
			if (CFStringCompare(_hoops_RHRRI, _hoops_CPRRI,0) ==  kCFCompareEqualTo) {
				
				CFStringRef str = CFURLCopyFileSystemPath(url,kCFURLPOSIXPathStyle);	
				CFStringGetCString(str,_hoops_IPRRI,limit,kCFStringEncodingUTF8);		
				CFRelease(str);
				
				printf("%s \n",_hoops_IPRRI);
				status = true;
				goto _hoops_HPAGR;
				
			}
			
			CFRelease(_hoops_RHRRI);
		}
		
		CFRelease(_hoops_GHRRI);
		_hoops_GHRRI = null;
	}		
	
_hoops_HPAGR:
	
	if (_hoops_GHRRI)
		CFRelease(_hoops_GHRRI);
	
	CFRelease(_hoops_SPRRI);	
	
	char const * ptr = null;
	
	if ((ptr = strrchr(_hoops_IPRRI, '/')) != null)
		strcpy(file, ptr);
	else
		status = false;
	
	return status;
}

#else

#undef _hoops_AHRRI
#define _hoops_AHRRI static _hoops_PHRRI

#define Point _hoops_SARRI
#define Style OSX_Style
#define Marker _hoops_GPRRI
#define Polygon _hoops_RPRRI
#define Button OSX_Button
#define Line _hoops_APRRI

#undef local
#include <Carbon/Carbon.h>
#define local static

#undef Point
#undef Style
#undef Marker
#undef Polygon
#undef Button
#undef Line



local ATSUFontID Get_ATSUFontID_From_ATSFontRef(const ATSFontRef _hoops_HHRRI)
{
	return FMGetFontFromATSFontRef(_hoops_HHRRI);
}

local ATSUFontID _hoops_IHRRI(const CFStringRef _hoops_CHRRI)
{
	ATSUFontID	_hoops_SHRRI	= 0;
	ATSFontRef	atRef	= ATSFontFindFromPostScriptName(_hoops_CHRRI, kATSOptionFlagsComposeFontPostScriptName);

	if (atRef != 0)
		_hoops_SHRRI = Get_ATSUFontID_From_ATSFontRef(atRef);
	return _hoops_SHRRI;
}

local CFStringRef Copy_FontContainerPathString_From_ATSUFontID(ATSUFontID _hoops_SHRRI)
{
		FSSpec		spec;
		CFStringRef	_hoops_GIRRI = 0;

		OSStatus	err = FMGetFontContainer(_hoops_SHRRI, &spec);

		if (err == noErr) {
			FSRef	_hoops_RIRRI;

			if (FSpMakeFSRef(&spec, &_hoops_RIRRI) == noErr) {
				CFURLRef	url = CFURLCreateFromFSRef(0, &_hoops_RIRRI);

				if (url) {
					_hoops_GIRRI = CFURLCopyFileSystemPath(url, kCFURLPOSIXPathStyle);
					CFRelease(url);
				}
			}
		}
		return _hoops_GIRRI;
}

local CFStringRef Copy_FontContainerPathString_From_PostscriptName(const CFStringRef _hoops_CHRRI)
{
	ATSUFontID		_hoops_SHRRI = _hoops_IHRRI(_hoops_CHRRI);

	if (_hoops_SHRRI != 0)
		return Copy_FontContainerPathString_From_ATSUFontID(_hoops_SHRRI);
	return 0;
}

/* _hoops_IPRRH _hoops_RH _hoops_HCGR _hoops_GGSR _hoops_IIGR _hoops_IRS _hoops_AIRRI _hoops_PCAI
		_hoops_GSPR	_hoops_PIRRI[2048];
		_hoops_RPP (_hoops_HIRRI(_hoops_IIRRI, _hoops_PIRRI, _hoops_GGHSP(_hoops_PIRRI), _hoops_CIRRI))
		{
				.. _hoops_HA _hoops_SR _hoops_HS _hoops_SCH _hoops_GAR _hoops_PCCP _hoops_SIRRI _hoops_SRHR ..
		}

		* _hoops_SGP _hoops_IRS _hoops_AIRRI _hoops_HII _hoops_PCCP _hoops_GCRRI _hoops_GSGR
		_hoops_AIRRI _hoops_RCRRI		= _hoops_ACRRI(0, _hoops_PIRRI, _hoops_CIRRI);

		* _hoops_SGP _hoops_IRS _hoops_AIRRI _hoops_HII _hoops_PCCP _hoops_HCCGI _hoops_GSGR
		_hoops_AIRRI _hoops_RCRRI		= _hoops_ACRRI(0, _hoops_PCRRI, _hoops_HCRRI);

*/
local bool _hoops_PPRRI(const char *_hoops_HPRRI, char *file, char *_hoops_IPRRI, int limit)
{
	CFStringRef		cf_face = 0, cf_path = 0;
	bool		status = true;
	char *			ptr;

	_hoops_IPRRI[0] = '\0';
	/* _hoops_ARPR _hoops_IRS _hoops_AIRRI _hoops_HII _hoops_PCCP _hoops_HCCGI _hoops_GSGR */
	cf_face = CFStringCreateWithCString(0, _hoops_HPRRI, kCFStringEncodingMacRoman);
	if (cf_face)
		cf_path = Copy_FontContainerPathString_From_PostscriptName(cf_face);
	else
		status = false;

	/* _hoops_HGCR _hoops_RH _hoops_HCGR _hoops_GGSR _hoops_IIGR _hoops_RH _hoops_ICRRI _hoops_AIRRI.	 _hoops_PS _hoops_IIRAR _hoops_CCRRI, _hoops_HIH _hoops_GRS _hoops_SCRRI _hoops_IH _hoops_SIRRI*/
	if (cf_path &&
		!CFStringGetCString(cf_path, _hoops_IPRRI, limit, kCFStringEncodingASCII) &&
		!CFStringGetCString(cf_path, _hoops_IPRRI, limit, kCFStringEncodingUTF8)) {
		status = false;
	}

	/* _hoops_CRAA _hoops_CGH _hoops_HA _hoops_SHH _hoops_PIISR _hoops_GGR */
	if ((ptr = strrchr(_hoops_IPRRI, '/')) != null)
		strcpy(file, ptr);
	else
		status = false;

	/* _hoops_RGHR _hoops_CGH _hoops_HA _hoops_SHH _hoops_PIISR _hoops_GGR */
	if (cf_face)
		CFRelease(cf_face);
	if (cf_path)
		CFRelease(cf_path);

	return status;
}

#endif

#else
/* _hoops_GRAA-_hoops_GSRRI */

#if defined( WINDOWS_SYSTEM ) && !defined( NUTCRACKER )
#include "msw.h"

local void _hoops_RSRRI () {
	HKEY				_hoops_ASRRI;
	DWORD				length;
	DWORD				count;
	DWORD				_hoops_PSRRI;
	DWORD				_hoops_HSRRI = 0;
	char				_hoops_ISRRI[4096];
	char				file[4096];
	DWORD				type;
	_hoops_RRPRH const *	_hoops_IRSRA = _hoops_ARPRH ();
	char const *		_hoops_CSRRI = "SOFTWARE\\MICROSOFT\\WINDOWS NT\\CURRENTVERSION\\FONTS";
	_hoops_PPGGH *	_hoops_PICGI;
	_hoops_IPCGI *		_hoops_IPGGH;
	FT_Library *		_hoops_HPGGH;

	if ((_hoops_HPGGH = _hoops_AICGI(true)) == null)
		return;

	if ((_hoops_PICGI = (_hoops_PPGGH *)HOOPS_WORLD->global_font_data_freetype) == null)
		return;

	_hoops_IPGGH = (_hoops_IPCGI*)_hoops_PICGI->_hoops_IPGGH;

	if (_hoops_IRSRA->_hoops_SSRRI == _hoops_GGARI || _hoops_IRSRA->_hoops_SSRRI == _hoops_RGARI)
		_hoops_CSRRI = "SOFTWARE\\MICROSOFT\\WINDOWS\\CURRENTVERSION\\FONTS";

	if (RegOpenKeyEx (HKEY_LOCAL_MACHINE, _hoops_CSRRI, 0L, KEY_QUERY_VALUE, &_hoops_ASRRI) != ERROR_SUCCESS)
			return;


	do {
		count = 4096;
		_hoops_PSRRI = RegEnumValue (_hoops_ASRRI, _hoops_HSRRI, _hoops_ISRRI, &count, NULL, &type, NULL, NULL);

		if (count > 0 &&
			_hoops_PSRRI == ERROR_SUCCESS &&
			type == REG_SZ &&
			_hoops_CISGH ("(TrueType)", _hoops_ISRRI)) {

			length = 4096;
			if (RegQueryValueEx (_hoops_ASRRI, _hoops_ISRRI, NULL, NULL, (LPBYTE)file, &length) == ERROR_SUCCESS) {
				if (_hoops_PSGGI (":\\", file)) {
					char	_hoops_IPRRI[4096];
					int		i;

					_hoops_AAHR (file, _hoops_IPRRI);
					/* _hoops_HASIR _hoops_GII _hoops_AGARI _hoops_CRAA */
					i = _hoops_SSGR (file);
					while (i >=0) {
						if (file[i] == '\\') {
							int		ii = 0;

							i++;
							while ((file[ii++]=file[i++]) != '\0') ;

							break;
						}
						i--;
					}

					_hoops_HRRRI (_hoops_HPGGH, _hoops_IPGGH, file, _hoops_IPRRI, 0);
				}
			}
		}

		_hoops_HSRRI++;

	} while (_hoops_PSRRI == ERROR_SUCCESS);

	RegCloseKey (_hoops_ASRRI);
}


local bool _hoops_PPRRI (const char * _hoops_HPRRI, char * file, char * _hoops_IPRRI, int limit) {
	HKEY	_hoops_ASRRI;
	DWORD	length;
	char	_hoops_PGARI[4096];
	int		i;
	_hoops_RRPRH const *	_hoops_IRSRA = _hoops_ARPRH ();
	char const *		_hoops_CSRRI = "SOFTWARE\\MICROSOFT\\WINDOWS NT\\CURRENTVERSION\\FONTS";

	UNREFERENCED(_hoops_IPRRI);

	if (_hoops_IRSRA->_hoops_SSRRI == _hoops_GGARI || _hoops_IRSRA->_hoops_SSRRI == _hoops_RGARI)
		_hoops_CSRRI = "SOFTWARE\\MICROSOFT\\WINDOWS\\CURRENTVERSION\\FONTS";

	if (RegOpenKeyEx (HKEY_LOCAL_MACHINE, _hoops_CSRRI, 0L, KEY_QUERY_VALUE, &_hoops_ASRRI) != ERROR_SUCCESS) {
		return false;
	}

	/* _hoops_RSAIP _hoops_IH _hoops_RHGS _hoops_HGARI _hoops_HRCSR _hoops_HIIA */
	if (_hoops_PSGGI ("swis721", _hoops_HPRRI) ||
		_hoops_PSGGI ("monospac821", _hoops_HPRRI) ||
		_hoops_PSGGI ("dutch801", _hoops_HPRRI) ||
		_hoops_PSGGI ("bankgothic", _hoops_HPRRI) ||
		_hoops_PSGGI ("commercialscript", _hoops_HPRRI) ||
		_hoops_PSGGI ("commercialpi", _hoops_HPRRI)) {

		if (_hoops_PSGGI ("swis721", _hoops_HPRRI))
			_hoops_AAHR ("Swiss 721 ",_hoops_PGARI);
		else if (_hoops_PSGGI ("monospac821", _hoops_HPRRI))
			_hoops_AAHR ("Monospace 821 ",_hoops_PGARI);
		else if (_hoops_PSGGI ("dutch801", _hoops_HPRRI))
			_hoops_AAHR ("Dutch 801 ",_hoops_PGARI);
		else if (_hoops_PSGGI ("bankgothic", _hoops_HPRRI))
			_hoops_AAHR ("Bank Gothic ",_hoops_PGARI);
		else if (_hoops_PSGGI ("commercialscript", _hoops_HPRRI))
			_hoops_AAHR ("Commercial Script ",_hoops_PGARI);
					else
			_hoops_AAHR ("Commercial Pi ",_hoops_PGARI);


		if (_hoops_PSGGI ("Blk", _hoops_HPRRI))
			strcat(_hoops_PGARI, "Black ");

		if (_hoops_PSGGI ("xbd", _hoops_HPRRI))
			strcat(_hoops_PGARI, "Extra Bold ");
		else
			if (_hoops_PSGGI ("Bd", _hoops_HPRRI))
				strcat(_hoops_PGARI, "Bold ");

		if (_hoops_PSGGI ("lt", _hoops_HPRRI))
			strcat(_hoops_PGARI, "Light ");

		if (_hoops_PSGGI ("cn", _hoops_HPRRI))
			strcat(_hoops_PGARI, "Condensed ");

		if (_hoops_PSGGI ("ex", _hoops_HPRRI))
			strcat(_hoops_PGARI, "Extended ");

		if (_hoops_PSGGI ("Oul", _hoops_HPRRI))
			strcat(_hoops_PGARI, "Outline ");

		if (_hoops_PSGGI ("Rm", _hoops_HPRRI))
			strcat(_hoops_PGARI, "Roman ");

		if (_hoops_PSGGI ("Md", _hoops_HPRRI))
			strcat(_hoops_PGARI, "Medium ");

		strcat(_hoops_PGARI, "BT (TrueType)");
	}
	else
		sprintf(_hoops_PGARI,"%s (TrueType)", _hoops_HPRRI);

	length = limit;
	if (RegQueryValueEx (_hoops_ASRRI, _hoops_PGARI, NULL, NULL, (LPBYTE)file, &length) != ERROR_SUCCESS) {
		/* _hoops_HPPR _hoops_IGARI, _hoops_GAAP _hoops_IRS _hoops_CGARI */
		DWORD _hoops_PSRRI;
		DWORD _hoops_HSRRI = 0;
		char _hoops_ISRRI[4096];
		DWORD count;
		DWORD type;

		do {
			count = 4096;
			_hoops_PSRRI = RegEnumValue (_hoops_ASRRI, _hoops_HSRRI, _hoops_ISRRI, &count, NULL, &type, NULL, NULL);

			if (_hoops_PSRRI == ERROR_SUCCESS &&
				type == REG_SZ &&
				_hoops_CISGH ("(TrueType)", _hoops_ISRRI) &&
				_hoops_CISGH ("&", _hoops_ISRRI) &&
				_hoops_PSGGI (_hoops_HPRRI, _hoops_ISRRI)) {

				/* _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_HRGR _hoops_HAR _hoops_CPHP _hoops_PII _hoops_SGARI _hoops_GRARI _hoops_CGPR _hoops_HCHAR _hoops_IH _hoops_SGARI */
				const char * first=_hoops_PSGGI (_hoops_HPRRI, _hoops_ISRRI);

				first += _hoops_SSGR (_hoops_HPRRI);

				while (*first == ' ') first++;

				if (*first == '&' || *first == '(') {
					length = limit;
					if (RegQueryValueEx (_hoops_ASRRI, _hoops_ISRRI, NULL, NULL,
						(LPBYTE)file,
						&length) == ERROR_SUCCESS)
						goto _hoops_RRARI;
				}
			}

			_hoops_HSRRI++;

		} while (_hoops_PSRRI == ERROR_SUCCESS);

		RegCloseKey (_hoops_ASRRI);
		return false;
	}

_hoops_RRARI:
	RegCloseKey (_hoops_ASRRI);

	if (length == 0)
		return false;


	if (_hoops_PSGGI (":\\", file)) {
		_hoops_AAHR (file,_hoops_IPRRI);
	}

	/* _hoops_HASIR _hoops_GII _hoops_AGARI _hoops_CRAA */
	i = _hoops_SSGR (file);
	while (i >=0) {
		if (file[i] == '\\') {
			int ii=0;

			i++;
			while ((file[ii++] = file[i++]) != '\0') ;

			break;
		}
		i--;
	}

	return true;
}

#else

local bool _hoops_PPRRI (const char *_hoops_HPRRI, char *file, char *_hoops_IPRRI, int limit)
{
	UNREFERENCED(_hoops_IPRRI);
	UNREFERENCED(limit);
	if (_hoops_IGGPA(_hoops_HPRRI, "Arial")) {
		_hoops_AAHR ("arial.ttf",file);
		return true;
	}

	return false;
}

#endif
#endif

GLOBAL_FUNCTION bool HD_Find_One_Freetype_Font (
	Display_Context const *dc,
	char const *			_hoops_CRRRI) {
	_hoops_PPGGH *		_hoops_PICGI;
	_hoops_IPCGI *			_hoops_IPGGH;
	FT_Library *			_hoops_HPGGH;

	if (dc->_hoops_HSAGH)
		return false;

	if ((_hoops_HPGGH = _hoops_AICGI(true)) == null)
		return false;

	if ((_hoops_PICGI = (_hoops_PPGGH *)HOOPS_WORLD->global_font_data_freetype) == null)
		return false;

	_hoops_IPGGH = (_hoops_IPCGI*)_hoops_PICGI->_hoops_IPGGH;

	if (_hoops_IPGGH->_hoops_HPCGI) {
		if (!dc->_hoops_ISAGH) {
			/* _hoops_RHRRH _hoops_HCR _hoops_HSSPR _hoops_RPPCR */
			_hoops_HARRI(dc, _hoops_IPGGH->_hoops_HGPIR);
			((Display_Context alter *)dc)->_hoops_ISAGH=true;
		}
		else {
			/* _hoops_SR _hoops_HCR _hoops_HRPP _hoops_ACPA _hoops_HCR _hoops_GSPIP _hoops_HIS _hoops_SHSP */
			return false;
		}
	}
	else {
		char						_hoops_IRRRI[4096];
		char						_hoops_HSCGI[4096];

		_hoops_IRRRI[0] = '\0';
		_hoops_HSCGI[0] = '\0';

		/* _hoops_ARI _hoops_SR _hoops_RRP _hoops_IS _hoops_PSSP _hoops_RH _hoops_ARARI _hoops_IS _hoops_RH _hoops_RGHR _hoops_IS _hoops_GGARP
		   _hoops_CISA _hoops_GGR _hoops_PRARI _hoops_CCA _hoops_RH _hoops_AGPC _hoops_HRARI _hoops_RGHR _hoops_PPR _hoops_IRARI
		   _hoops_CCA _hoops_RH _hoops_CSCS _hoops_RGHR _hoops_RSIRR */
		if (_hoops_PPRRI(_hoops_CRRRI, _hoops_IRRRI, _hoops_HSCGI, 4096)) {
			_hoops_SACGI *	_hoops_CRARI = null;
			bool				_hoops_SRARI = false;

			/* _hoops_ASAC _hoops_AGCR _hoops_IH _hoops_SPHR */
			_hoops_CRARI=_hoops_IPGGH->_hoops_HGPIR;
			_hoops_IPGGH->_hoops_HGPIR=0;

			if (_hoops_HSCGI[0] == '\0') {
				_hoops_HCRPR		_hoops_PSCGI;
				_hoops_HCRPR		filename;

				_hoops_AAPIR *		_hoops_ASCGI;

				_hoops_ASCGI = HOOPS_WORLD->_hoops_AAGHP;
				while (!_hoops_SRARI && _hoops_ASCGI) {
					HI_Copy_Name (&_hoops_ASCGI->name, &_hoops_PSCGI);
					HI_Copy_Chars_To_Name (_hoops_IRRRI, &filename);

					Sprintf_N (_hoops_IRRRI, "%n", &filename);
					HI_Add_Path_Delimiter (&_hoops_PSCGI, &filename);
					Sprintf_NN (_hoops_HSCGI, "%n%n", &_hoops_PSCGI, &filename);

					_hoops_SRARI = _hoops_HRRRI(_hoops_HPGGH, _hoops_IPGGH, _hoops_IRRRI, _hoops_HSCGI, _hoops_CRRRI);

					_hoops_RGAIR (_hoops_PSCGI);
					_hoops_RGAIR (filename);
					_hoops_ASCGI = _hoops_ASCGI->next;
				}

				if (!_hoops_SRARI && HOOPS_WORLD->_hoops_HAHGI.length != 0) {
					HI_Copy_Name (&HOOPS_WORLD->_hoops_HAHGI, &_hoops_PSCGI);
					HI_Copy_Chars_To_Name (_hoops_IRRRI, &filename);

					Sprintf_N (_hoops_IRRRI, "%n", &filename);
					HI_Add_Path_Delimiter (&_hoops_PSCGI, &filename);
					Sprintf_NN (_hoops_HSCGI, "%n%n", &_hoops_PSCGI, &filename);

					_hoops_SRARI = _hoops_HRRRI(_hoops_HPGGH, _hoops_IPGGH, _hoops_IRRRI, _hoops_HSCGI, _hoops_CRRRI);

					_hoops_RGAIR (_hoops_PSCGI);
					_hoops_RGAIR (filename);
				}
			}
			else
				_hoops_SRARI = _hoops_HRRRI(_hoops_HPGGH, _hoops_IPGGH, _hoops_IRRRI, _hoops_HSCGI, _hoops_CRRRI);

			/* _hoops_RHRRH _hoops_GII _hoops_CCAH _hoops_RPPCR */
			if (_hoops_IPGGH->_hoops_HGPIR) {
				_hoops_SACGI *	_hoops_GAARI = null;

				_hoops_HARRI (dc, _hoops_IPGGH->_hoops_HGPIR);

				/* _hoops_AGGAR _hoops_GII _hoops_RHGS _hoops_RPPCR _hoops_ISSC _hoops_HPGR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_HIGR */
				_hoops_GAARI=_hoops_IPGGH->_hoops_HGPIR;

				while (_hoops_GAARI->next)
					_hoops_GAARI = _hoops_GAARI->next;

				_hoops_GAARI->next = _hoops_CRARI;
			}
			else
				_hoops_IPGGH->_hoops_HGPIR = _hoops_CRARI;

			if (!_hoops_SRARI) {
				/* _hoops_SR _hoops_RRP _hoops_IS _hoops_RHRRH _hoops_RCSAR _hoops_AHAP _hoops_SR _hoops_AA _hoops_ACPA */
				_hoops_HARRI(dc, _hoops_IPGGH->_hoops_HGPIR);
			}
		}
	}

	/* _hoops_ISPR _hoops_RPP _hoops_SR _hoops_HS _hoops_GSGI _hoops_SCH */
	{
		int				_hoops_ARAHR = 0;
		char const *		_hoops_RPPA = _hoops_CRRRI;
		int					count = _hoops_SSGR (_hoops_CRRRI);
		_hoops_SHSSP const *	next;

		_hoops_RGGA (--count < 0) _hoops_ARAHR += _hoops_SHPCR (*_hoops_RPPA), _hoops_RPPA++;

		next = dc->_hoops_GRHGH[_hoops_ARAHR & (_hoops_HHRSP - 1)];

		while (next != null) {
			if (_hoops_IGGPA(next->name.text, _hoops_CRRRI))
				return true;

			next = next->_hoops_SSCAP;
		}
	}

	return false;
}

GLOBAL_FUNCTION void HD_Find_Freetype_Fonts (
	Display_Context const *	dc) {
	_hoops_AAPIR *				_hoops_ASCGI;
	void *					context;
	int					_hoops_RAARI;
	_hoops_HCRPR				filename;
	_hoops_HCRPR				_hoops_PSCGI;
	_hoops_HCRPR				_hoops_HHCHR, _hoops_IHCHR;
	_hoops_SRHSR *			_hoops_PPCGI;
#if defined(OSX_SYSTEM)
	_hoops_SRHSR			_hoops_AAARI[] = { _hoops_GRRCR ("*") , _hoops_PCGSA };
#elif defined(UNIX_SYSTEM)
	_hoops_SRHSR			_hoops_AAARI[] = {  _hoops_GRRCR ("*.otf"), _hoops_GRRCR ("*.OTF"), /*_hoops_CAAPA ("*._hoops_PAARI"), _hoops_CAAPA ("*._hoops_HAARI"),*/	 _hoops_GRRCR ("*.ttf") , _hoops_GRRCR ("*.TTF") , _hoops_GRRCR ("*.ttc") ,_hoops_GRRCR ("*.TTC") , _hoops_GRRCR ("*.pfa") , _hoops_GRRCR ("*.PFA") , _hoops_GRRCR ("*.pfb") , _hoops_GRRCR ("*.PFB") , _hoops_PCGSA };
#else
	_hoops_SRHSR			_hoops_AAARI[] = { _hoops_GRRCR ("*.otf"), /*_hoops_CAAPA ("*._hoops_PAARI"),*/ _hoops_GRRCR ("*.ttf") , _hoops_GRRCR ("*.ttc") , _hoops_GRRCR ("*.pfa") , _hoops_GRRCR ("*.pfb") , _hoops_PCGSA };
#endif
	char				_hoops_IRRRI[4096];
	char				_hoops_HSCGI[4096];

	_hoops_PPGGH *		_hoops_PICGI;
	_hoops_IPCGI *			_hoops_IPGGH;
	FT_Library *			_hoops_HPGGH;
	_hoops_SACGI *		_hoops_CRARI = null;

	if ((_hoops_HPGGH = _hoops_AICGI(true)) == null)
		return;

	if ((_hoops_PICGI = (_hoops_PPGGH *)HOOPS_WORLD->global_font_data_freetype) == null)
		return;

#if defined( WINDOWS_SYSTEM ) && !defined( NUTCRACKER )
	_hoops_RSRRI();
#endif

	_hoops_IPGGH = (_hoops_IPCGI*)_hoops_PICGI->_hoops_IPGGH;

	/* _hoops_ASAC _hoops_AGCR _hoops_IH _hoops_HHPRH */
	_hoops_CRARI = _hoops_IPGGH->_hoops_HGPIR;
	_hoops_IPGGH->_hoops_HGPIR = 0;

	if (!_hoops_IPGGH->_hoops_HPCGI) {
		_hoops_ASCGI = HOOPS_WORLD->_hoops_AAGHP;

		while (_hoops_ASCGI) {
			_hoops_PPCGI = _hoops_AAARI;

			HI_Copy_Name (&_hoops_ASCGI->name, &_hoops_PSCGI);

			while (_hoops_PPCGI->length != 0) {
				_hoops_HHCHR.length = _hoops_IHCHR.length = 0;

				_hoops_RAARI = DIR_Select_File | DIR_Select_Readable;

				if (!HI_Open_Directory (&_hoops_PSCGI, (_hoops_HCRPR const *)_hoops_PPCGI,
									_hoops_RAARI, _hoops_RAARI, &context,
									&_hoops_HHCHR, &_hoops_IHCHR)) {
					_hoops_RGAIR (_hoops_HHCHR);
					_hoops_RGAIR (_hoops_IHCHR);
					break;
				}

				filename.length = 0;

				while (HI_Read_Directory (context, &filename, &_hoops_HHCHR, &_hoops_IHCHR)) {
					if (filename.length == 0) break;

					Sprintf_N (_hoops_IRRRI, "%n", &filename);
					HI_Add_Path_Delimiter (&_hoops_PSCGI, &filename);
					Sprintf_NN (_hoops_HSCGI, "%n%n", &_hoops_PSCGI, &filename);
					_hoops_HRRRI(_hoops_HPGGH, _hoops_IPGGH, _hoops_IRRRI, _hoops_HSCGI, 0);

					_hoops_RGAIR (filename);
					filename.length = 0;
				}

				_hoops_RGAIR (filename);

				HI_Close_Directory (context, &_hoops_HHCHR, &_hoops_IHCHR);

				_hoops_RGAIR (_hoops_HHCHR);
				_hoops_RGAIR (_hoops_IHCHR);

				_hoops_PPCGI++;
			}

			_hoops_RGAIR (_hoops_PSCGI);
			_hoops_ASCGI = _hoops_ASCGI->next;
		}
	}

	_hoops_IPGGH->_hoops_HPCGI = true;
	((Display_Context alter *)dc)->_hoops_ISAGH=true;


	if (_hoops_CRARI) {
		_hoops_HARRI(dc, _hoops_CRARI);
	}

	if (_hoops_IPGGH->_hoops_HGPIR) {
		_hoops_SACGI		*_hoops_GAARI=0;

		_hoops_HARRI(dc, _hoops_IPGGH->_hoops_HGPIR);

		/* _hoops_AGGAR _hoops_GII _hoops_RHGS _hoops_RPPCR _hoops_ISSC _hoops_HPGR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_HIGR */
		_hoops_GAARI = _hoops_IPGGH->_hoops_HGPIR;

		while (_hoops_GAARI->next)
			_hoops_GAARI = _hoops_GAARI->next;

		_hoops_GAARI->next = _hoops_CRARI;
	}
	else
		_hoops_IPGGH->_hoops_HGPIR = _hoops_CRARI;

}

#else
GLOBAL_FUNCTION bool HD_Find_One_Freetype_Font (
	Display_Context const *	dc,
	char const *			_hoops_CRRRI)
{
	UNREFERENCED(dc);
	UNREFERENCED(_hoops_CRRRI);
	return false;
}

#endif


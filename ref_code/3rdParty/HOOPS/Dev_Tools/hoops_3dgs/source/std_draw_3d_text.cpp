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
 * $Id: obf_tmp.txt 1.293 2010-11-24 00:42:12 covey Exp $
 */


#include "hoops.h"
#include "database.h"
#include "patterns.h"
#include "driver.h"
#include "tandt.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

// _hoops_PASC
/* _hoops_RH _hoops_CIHH _hoops_RPGP _hoops_IH _hoops_PCCP _hoops_CAPCS _hoops_GAS _hoops_AHCRR... */
#define _hoops_SAPCS(_hoops_IHCR, _hoops_GPHH, pt, width, height)				\
	  ((pt).x + ((width)-1) >= _hoops_GPHH.left &&					\
	   (pt).x			   <= _hoops_GPHH.right &&					\
	   (pt).y + ((height)-1) >= _hoops_GPHH.bottom &&				\
	   (pt).y				<= _hoops_GPHH.top &&					\
	   /* _hoops_GPPCS _hoops_HRGR _hoops_PRRHA! (_hoops_SSH) >= 0 && */					\
	   (!BIT ((_hoops_IHCR)->flags, _hoops_CSP) ||			\
		HD_Box_Within_Cutting_Planes (_hoops_IHCR, (pt).x, (pt).y + (height)-1,	\
										  (pt).z, (int)(width), (int)(height))))


local bool _hoops_RPPCS (
	_hoops_HHCR const &	_hoops_IHCR,
	Point const *				position,
	Point alter *				result,
	bool						_hoops_CIPAR) {
	_hoops_RPRA const *			matrix;
	Point						tmp;

	tmp.x = position->x;
	tmp.y = position->y;
	tmp.z = position->z;

	if (_hoops_CIPAR)
		matrix = _hoops_IHCR->matrix->_hoops_PPRA()->data.elements;
	else
		matrix = _hoops_IHCR->matrix->data.elements;

	switch (_hoops_IHCR->_hoops_HGSC) {
		case _hoops_SIPHP: {
			result->x = tmp.x;
			result->y = tmp.y;
			result->z = 0.0f;
		}	break;

		case _hoops_CIPHP: {
			result->x = _hoops_PRPPI (matrix, tmp);
			result->y = _hoops_HRPPI (matrix, tmp);
			result->z = 0.0f;
		}	break;

		case _hoops_PCPHP: {
			result->x = _hoops_HPRA (matrix, tmp);
			result->y = _hoops_IPRA (matrix, tmp);
			result->z = 0.0f;
		}	break;

		case _hoops_RCPHP: {
			float			w;

			w = _hoops_PHCP (matrix, tmp);
			if (w <= _hoops_IHCR->_hoops_CHCR)
				return false;

			result->x = _hoops_HPRA (matrix, tmp) / w;
			result->y = _hoops_IPRA (matrix, tmp) / w;
			result->z = 0.0f;
		}	break;

		case _hoops_ACPHP: {
			result->x = _hoops_HPRA (matrix, tmp);
			result->y = _hoops_IPRA (matrix, tmp);
			result->z = _hoops_CPRA (matrix, tmp);
			result->z = _hoops_IGSC (result->z, _hoops_IHCR);
		}	break;

		case _hoops_GCPHP: {
			float			w;

			w = _hoops_PHCP (matrix, tmp);
			if (w <= _hoops_IHCR->_hoops_CHCR)
				return false;

			result->x = _hoops_HPRA (matrix, tmp) / w;
			result->y = _hoops_IPRA (matrix, tmp) / w;
			result->z = _hoops_CPRA (matrix, tmp) / w;
			result->z = _hoops_IGSC (result->z, _hoops_IHCR);
		}	break;
	}

	return true;
}



GLOBAL_FUNCTION void HI_Free_Text_Info (
	Text_Info alter *		ti) {

	for (int i = 0; i < ti->text->count; i++) {
		ti->_hoops_HGCSR[i].nr.release();

		if (ti->_hoops_HGCSR[i]._hoops_APPSP != null)
			_hoops_HPRH (ti->_hoops_HGCSR[i]._hoops_APPSP);
	}

	if (ti->text->count > 0)
		FREE_ARRAY (ti->_hoops_HGCSR, ti->text->count, _hoops_PGCSR);

	if (ti->_hoops_PPPSP != null)
		FREE_ARRAY (ti->_hoops_PPPSP, ti->text->count, int);

	_hoops_PRPIR (ti->_hoops_SIHSA);
	FREE (ti, Text_Info);
}

GLOBAL_FUNCTION Text_Info * HI_Clone_Text_Info (
	Text_Info const *		ti) {
	Text_Info alter	*		_hoops_APPCS;

	ALLOC (_hoops_APPCS, Text_Info);
	_hoops_RSAI (ti, Text_Info, _hoops_APPCS);

	if (ti->text->count > 0) {
		HI_Copy_KName (&ti->_hoops_SIHSA, &_hoops_APPCS->_hoops_SIHSA);

		ZALLOC_ARRAY (_hoops_APPCS->_hoops_HGCSR, ti->text->count, _hoops_PGCSR);
		if (ti->_hoops_PPPSP != null)
			ALLOC_ARRAY (_hoops_APPCS->_hoops_PPPSP, ti->text->count, int);

		for (int i = 0; i < ti->text->count; i++) {
			_hoops_APPCS->_hoops_HGCSR[i] =  ti->_hoops_HGCSR[i];

			if (_hoops_APPCS->_hoops_PPPSP != null)
				_hoops_APPCS->_hoops_PPPSP[i] = ti->_hoops_PPPSP[i];
		}
	}

	return _hoops_APPCS;
}


static const Karacter	_hoops_PPPCS = (Karacter)_hoops_RHHPP('_');

local void _hoops_HPPCS (
	Net_Rendition const &		inr,
	_hoops_PIGPR const *		cursor,
	Point const *				point) {
	Net_Rendition				nr = inr;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	Geometry const *			_hoops_IPPCS = dc->_hoops_RAI;
	_hoops_PGCSR			_hoops_HGCSR;
	Text_Info					text_info;
	Text_Info *					ti = &text_info;
	_hoops_HACC *						_hoops_GRRPH;

	if (dc->_hoops_IGHGH == null && !BIT (nr->_hoops_RGP, T_STRING_CURSORS) ||
		 dc->_hoops_IGHGH != null && !BIT (dc->_hoops_IGHGH->_hoops_SHGGH, T_STRING_CURSORS)) return;

	/* _hoops_GRPHA */
	if (dc->_hoops_IGHGH != null)
		dc->_hoops_IGHGH->_hoops_AHGGH = cursor;
	((Display_Context alter *)dc)->_hoops_RAI = (Geometry*)cursor;


	ZALLOC (_hoops_GRRPH, _hoops_HACC);
	_hoops_GRRPH->type = _hoops_AGCP;
	_hoops_GRRPH->_hoops_HIHI = 1;
	_hoops_GRRPH->_hoops_CSAI.x = point->x;
	_hoops_GRRPH->_hoops_CSAI.y = point->y;
	_hoops_GRRPH->_hoops_CSAI.z = point->z;
	_hoops_GRRPH->count = 1;
	_hoops_GRRPH->_hoops_PICHR = 1;

	ALLOC_ARRAY (_hoops_GRRPH->_hoops_ICI, 1, int);
	_hoops_GRRPH->_hoops_ICI[0] = 1;

	ALLOC_ARRAY (_hoops_GRRPH->karacters, 2, Karacter);
	_hoops_GRRPH->karacters[0] = _hoops_PPPCS;
	_hoops_GRRPH->karacters[1] = 0;

	ALLOC_ARRAY (_hoops_GRRPH->_hoops_RIHIR, 1, Karacter*);
	_hoops_GRRPH->_hoops_RIHIR[0] = _hoops_GRRPH->karacters;

	_hoops_GRRPH->encoding = _hoops_SSAIP;


	/* _hoops_IHPI _hoops_RH _hoops_PAPPI */
	ti->text = _hoops_GRRPH;
	ti->flags = _hoops_AAPSP;
	ti->_hoops_PPPSP = null;
	ti->_hoops_RIPSP = 0;
	ti->_hoops_GIPSP = _hoops_HRCIR->font->_hoops_IGGGH;
	ti->_hoops_ICGH = _hoops_HRCIR->font->_hoops_ISISR;
	ti->_hoops_HGCSR = &_hoops_HGCSR;
	ti->_hoops_CPPSP = Vector(0.0f, 0.0f, 0.0f);

	ti->_hoops_HGCSR[0].nr = nr;
	ti->_hoops_HGCSR[0]._hoops_APPSP = null;
	ti->_hoops_HGCSR[0].flags = TKIF_NONE;
	ti->_hoops_HGCSR[0].height = _hoops_HRCIR->font->_hoops_ISISR;

	if (HD_Measure_Characters (ti->_hoops_HGCSR[0].nr, 1, &_hoops_GRRPH->karacters[0], _hoops_GRRPH->encoding, &ti->_hoops_HGCSR[0].width)) {
		return;
	}

	ti->_hoops_HGCSR[0].position.x = point->x - 0.5f * ti->_hoops_HGCSR[0].width * _hoops_HRCIR->path.x;
	ti->_hoops_HGCSR[0].position.y = point->y - 0.5f * ti->_hoops_HGCSR[0].width * _hoops_HRCIR->path.y;
	ti->_hoops_HGCSR[0].position.z = point->z;

	ti->_hoops_HGCSR[0].position.x += 0.1f * ti->_hoops_HGCSR[0].height * _hoops_HRCIR->path.y;
	ti->_hoops_HGCSR[0].position.y += 0.1f * ti->_hoops_HGCSR[0].height * -_hoops_HRCIR->path.x;

	ti->_hoops_HGCSR[0].screen.x = 0;
	ti->_hoops_HGCSR[0].screen.y = 0;
	ti->_hoops_HGCSR[0].screen.width = ti->_hoops_HGCSR[0].width;
	ti->_hoops_HGCSR[0].screen.height = ti->_hoops_HGCSR[0].height;

	ti->_hoops_SIHSA._hoops_IPPPP = _hoops_GRRPH->karacters;
	ti->_hoops_SIHSA.length = 1;
	ti->_hoops_PPPSP = 0;

	if (_hoops_HRCIR->transform == FT_FULL ||
			_hoops_SAPCS (_hoops_IHCR, _hoops_SGRA->_hoops_SCIH, ti->_hoops_HGCSR[0].position,
						ti->_hoops_HGCSR[0].width, ti->_hoops_HGCSR[0].height))
		_hoops_CGIGH (nr, ti);

	/* _hoops_ISSPR _hoops_GRPHA */
	((Display_Context alter *)dc)->_hoops_RAI = _hoops_IPPCS;
	if (dc->_hoops_IGHGH != null)
		dc->_hoops_IGHGH->_hoops_AHGGH = null;

	_hoops_HPRH(_hoops_GRRPH);
}


local inline bool _hoops_CPPCS (
	Net_Rendition const &		nr,
	_hoops_HACC const *				text) {
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	Display_Context const *		dc = nr->_hoops_SRA;

	if (!text->bounding._hoops_HICAR() &&
		BIT(dc->flags, _hoops_GIRIP) &&
		_hoops_HRCIR->transform == FT_FULL &&
		!BIT (nr->current, _hoops_CRSI)  &&
		BIT (_hoops_RRGH->_hoops_SHHS, _hoops_PIIRP) &&
		dc->_hoops_SHCI() != _hoops_HIAGH &&
		dc->_hoops_AHSI != null && 
		dc->_hoops_AHSI->_hoops_CIHS > 0) {

		if (BIT (_hoops_IHCR->_hoops_APH, _hoops_RIHS) ||
			BIT (_hoops_IHCR->_hoops_APH, Heur_Culling_EXTENT) && _hoops_RRGH->_hoops_PCHS != Heur_MAX_EXTENT_MODE_DEFER) {
			int		_hoops_SIHS = 0;
			float	_hoops_SPPCS;
			float   _hoops_GHPCS = dc->_hoops_AHSI->_hoops_CIHS;

			if (BIT (_hoops_IHCR->_hoops_APH, _hoops_RIHS))
				_hoops_SIHS = _hoops_RRGH->_hoops_GCHS;
			if (BIT (_hoops_IHCR->_hoops_APH, Heur_Culling_EXTENT))
				_hoops_SIHS = _hoops_IAAA(_hoops_RRGH->_hoops_GRGC, _hoops_SIHS);

			if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH)
				_hoops_SPPCS = 0.7f;
			else
				_hoops_SPPCS = 0.8f;
			if (_hoops_GHPCS * text->bounding->sphere.radius < 
					_hoops_SIHS * _hoops_SPPCS * dc->_hoops_AHSI->segment->bounding->sphere.radius) {
				return true;
			}
		}
	}
	return false;
}


GLOBAL_FUNCTION void HD_Std_3D_Text (
	Net_Rendition const &		inr,
	_hoops_HACC const *				text) {
	Net_Rendition				nr = inr.Copy();
	_hoops_IGCSR alter &		_hoops_HRCIR = nr->_hoops_SISI;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	Text_Info *					ti = null;
	Point						position;
	DC_Point					_hoops_RHPCS;
	float						_hoops_AHPCS,
								_hoops_RSICC,
								_hoops_PHPCS,
								_hoops_HHPCS,
								_hoops_IHPCS;
	Karacter const *			_hoops_IHSCP;
	int							count;
	int							_hoops_CHPCS, _hoops_SHPCS;
	float						_hoops_GIPCS;
	float						_hoops_RIPCS,
								_hoops_AIPCS;
	float						_hoops_PIPCS;
	Point						_hoops_HIPCS;	/* _hoops_SGGGA _hoops_IH _hoops_ICSA */
	_hoops_IHGRP				encoding = text->encoding;
	int							line;
	int							_hoops_IIPCS;
	float						_hoops_CIPCS = 0.0f;
	float						_hoops_SIPCS = 0.0f;
	Vector						_hoops_GCPCS;
	Vector						_hoops_RCPCS;
	float						_hoops_ACPCS;
	bool						_hoops_CGSPH;
	float						_hoops_PCPCS = 0.0f;
	Karacter					*_hoops_HCPCS = null;
	int							*_hoops_ICPCS = null;
	float						*_hoops_CCPCS = null;
	float						*_hoops_SCPCS = null;
	float						*_hoops_GSPCS = null;
	Vector *					_hoops_HHPSP = null;
	Point						_hoops_RSPCS[4];
	float						_hoops_ASPCS;
	_hoops_ISGI			_hoops_PSPCS;
	float const *				_hoops_HSPCS = null;
	int							i;
	Action_Mask					_hoops_HPCI;
	bool						_hoops_ISPCS = false;
	bool						_hoops_CSPCS = false;

	dc->_hoops_SCGC |= _hoops_PGCP;

	if (text->count == 0 && text->_hoops_AAPGR == null) return; /* _hoops_IIP _hoops_IRIPR */
	_hoops_HPCI = dc->_hoops_IPCI->mask;
	dc->_hoops_IPCI->mask |= _hoops_CIIP;

	_hoops_RCCA(_hoops_HIRGH)++;

	if (text->_hoops_IPPGR != null) {
		HD_Downwind_Rendition (nr, text->_hoops_IPPGR, T_TEXT|T_STRING_CURSORS, true);

		/* _hoops_PIP: _hoops_GGCR _hoops_GRH _hoops_PRCA _hoops_RPP _hoops_HAIR _hoops_PAH _hoops_SHH _hoops_ARP _hoops_PPR _hoops_IHSP _hoops_GSH _hoops_HCGR */
	}

	bool _hoops_SSPCS = (BIT (dc->_hoops_CPGPR, _hoops_RSCCA) || ANYBIT (text->_hoops_CPGPR, _hoops_CASIR|_hoops_AHSGA));
	if (_hoops_SSPCS && 
		text->_hoops_HHGRP != dc->_hoops_GHRI->_hoops_GPPI) {
		_hoops_PGRCA(text)->bounding = Bounding::Create();
		_hoops_PGRCA(text)->_hoops_HHGRP = dc->_hoops_GHRI->_hoops_GPPI;
		_hoops_ISPCS = true;
	}

	if (_hoops_CPPCS (nr, text)) {
		_hoops_RCCA(_hoops_IIRGH)++;
		return;
	}

	/* _hoops_HGSR _hoops_AAPGS _hoops_SHR */
	if (nr->_hoops_AHP != _hoops_HRCIR->_hoops_RGIHP) {
		if (_hoops_HRCIR->_hoops_RGIHP == null) {
			_hoops_HRCIR->_hoops_RGIHP = nr->_hoops_AHP;
			Line_Rendition alter &	_hoops_ASAIP = _hoops_HRCIR->_hoops_RGIHP.Modify();

			_hoops_ASAIP->_hoops_CHA = _hoops_HRCIR->_hoops_CHA;
			_hoops_ASAIP->color = _hoops_HRCIR->color;

			if (_hoops_ASAIP->line_style != null)
				HD_Replace_Line_Style(_hoops_ASAIP, nr->_hoops_GCSHP->_hoops_IHRIP);

			_hoops_ASAIP->weight = dc->_hoops_PGCC._hoops_IHHSR;
			//_hoops_RGISR->_hoops_GGCS = _hoops_IRAP;
		}

		nr->_hoops_AHP = _hoops_HRCIR->_hoops_RGIHP;
	}

	/* _hoops_HGSR _hoops_AAPGS _hoops_SHR */
	if (_hoops_HRCIR->transform == FT_FULL &&
		!BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_IPCRP)) {
		nr->_hoops_ASIR.Modify()->_hoops_GCCI.options |= _hoops_IPCRP;
	}

	if (nr->transform_rendition->_hoops_CHIH != 0.0f ||
		ANYBIT(nr->transform_rendition->flags, _hoops_GRHH|_hoops_IGSP) ||
		ANYBIT(nr->transform_rendition->heuristics,
			_hoops_GPSA|_hoops_SASA)) {

		_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

		_hoops_GGCC->_hoops_CHIH = 0.0f;
		_hoops_GGCC->flags &= ~_hoops_GRHH;
		_hoops_GGCC->flags &= ~_hoops_IGSP;
		_hoops_GGCC->heuristics &= ~(_hoops_GPSA | _hoops_SASA);
	}

	if (!ALLBITS(nr->_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE|T_LINES)) {
		nr.Modify()->_hoops_RGP |= T_FACES|T_ANY_POLYGON_EDGE|T_LINES;
	}

	_hoops_CAAI (HOOPS_WORLD->_hoops_HPHGI);
	if (_hoops_HRCIR->font == null || 
		!HI_Encoding_Is_Compatible (encoding, _hoops_HRCIR->font->encoding)) {

		do {
			HD_Choose_Font (nr, _hoops_HRCIR->_hoops_HSRIP->_hoops_HGPIR, encoding, true);

			/* _hoops_GHCA _hoops_HAR _hoops_SHH _hoops_SHSS _hoops_IS _hoops_HSRS _hoops_GII _hoops_HRCSR _hoops_GGR _hoops_RGR _hoops_AGIR, _hoops_HIS _hoops_RCRP _hoops_GH */
			if (_hoops_HRCIR->font == null)
				goto _hoops_PP;

		} while (!HD_Load_Font (dc, _hoops_HRCIR->font));
	}
	else {
		/* _hoops_PAAP _hoops_RH _hoops_SCGR _hoops_HRCSR _hoops_HPHS */
		Font_Instance alter *	_hoops_GGHCS = (Font_Instance alter*)_hoops_HRCIR->font;

		(*_hoops_GGHCS->_hoops_SSCSP)(nr, _hoops_GGHCS);
	}

	if (_hoops_HRCIR->font->_hoops_RACSR == 0.0f)
		goto _hoops_PP;

	/* _hoops_CIGS _hoops_ISPH _hoops_HGSR */
	_hoops_GCPCS.x = 1.0f;
	_hoops_GCPCS.y = _hoops_GCPCS.z = 0.0f;

	if (text->region != null) {
		Point				box[4]; /* 2 _hoops_PAR 3 _hoops_IH _hoops_HA */

		if (BIT (text->region->options, _hoops_GGGRP)) {
			Point				scale, translate;

			_hoops_AIGA (text->region->points, text->region->count, Point, box);

			scale.x = 0.5f * (_hoops_SGRA->_hoops_PHRA.right - _hoops_SGRA->_hoops_PHRA.left);
			scale.y = 0.5f * (_hoops_SGRA->_hoops_PHRA.top	- _hoops_SGRA->_hoops_PHRA.bottom);
			scale.z = 1.0f;

			if (BIT (text->region->options, _hoops_RGGRP)) {
				if (!_hoops_RPPCS (_hoops_IHCR, &text->_hoops_CSAI, &translate, false))
					goto _hoops_PP;
			}
			else {
				translate.x = 0.5f*(float)(_hoops_SGRA->_hoops_PHRA.left + _hoops_SGRA->_hoops_PHRA.right);
				translate.y = 0.5f*(float)(_hoops_SGRA->_hoops_PHRA.bottom + _hoops_SGRA->_hoops_PHRA.top);
				translate.z = 0.0f;
			}

			/* _hoops_HIHP _hoops_HII _hoops_RPPS _hoops_IS _hoops_ASPA, _hoops_PPR _hoops_SGS _hoops_IS _hoops_CARA _hoops_GC */
			for (i=0; i<text->region->count; i++) {
				box[i].x = box[i].x * scale.x + translate.x;
				box[i].y = box[i].y * scale.y + translate.y;
				box[i].z = box[i].z * scale.z + translate.z;

				if (!_hoops_RPPCS (_hoops_IHCR, &box[i], &_hoops_RSPCS[i], true))
					goto _hoops_PP;

			}
		}
		else {
			_hoops_AIGA (text->region->points, text->region->count, Point, _hoops_RSPCS);

			if (BIT (text->region->options, _hoops_RGGRP)) {
				/* _hoops_GGCR _hoops_GPP _hoops_HCGR _hoops_AHC */
				for (i=0; i<text->region->count; i++) {
					_hoops_RSPCS[i].x += text->_hoops_CSAI.x;
					_hoops_RSPCS[i].y += text->_hoops_CSAI.y;
					_hoops_RSPCS[i].z += text->_hoops_CSAI.z;
				}
			}

			/* _hoops_HIHP _hoops_IS _hoops_ASPA */
			for (i=0; i<text->region->count; i++)
				if (!_hoops_RPPCS (_hoops_IHCR, &_hoops_RSPCS[i], &box[i], false))
					goto _hoops_PP;
		}

		if (BIT (text->region->options, _hoops_AGGRP)) {
			if (box[0].x > box[1].x  ||  box[0].x == box[1].x && box[0].y > box[1].y) {
				if (text->region->count == 3) {
					Vector			_hoops_SHGCR = box[1] - box[0];
					Vector			_hoops_HAHCR = box[2] - box[0];
					Vector			_hoops_SAIAR = _hoops_SHGCR._hoops_SAIAR (_hoops_HAHCR);

					if (_hoops_SAIAR.z > 0.0f) {
						box[2] = box[1] - (box[2] - box[0]);
						_hoops_RSPCS[2] = _hoops_RSPCS[1] - (_hoops_RSPCS[2] - _hoops_RSPCS[0]);
					}
				}
				else if (text->region->count == 4) {
					Swap (box[2], box[3]);
					Swap (_hoops_RSPCS[2], _hoops_RSPCS[3]);
				}

				Swap (box[0], box[1]);
				Swap (_hoops_RSPCS[0], _hoops_RSPCS[1]);

				_hoops_CSPCS = true;
			}
			else {
				if (text->region->count == 3) {
					Vector			_hoops_SHGCR = box[1] - box[0];
					Vector			_hoops_HAHCR = box[2] - box[0];
					Vector			_hoops_SAIAR = _hoops_SHGCR._hoops_SAIAR (_hoops_HAHCR);

					if (_hoops_SAIAR.z < 0.0f) {
						box[2] = box[1] - (box[2] - box[0]);
						_hoops_RSPCS[2] = _hoops_RSPCS[1] - (_hoops_RSPCS[2] - _hoops_RSPCS[0]);
					}
				}
			}
		}

		position = box[0];

		_hoops_GCPCS = box[1] - box[0];

		if (_hoops_HRCIR->transform != FT_FULL) {
			_hoops_CIPCS = _hoops_SGIHR (_hoops_GCPCS.x * _hoops_GCPCS.x + _hoops_GCPCS.y * _hoops_GCPCS.y);

			if (_hoops_CIPCS > 0.0f)
				_hoops_GCPCS /= _hoops_CIPCS;

			_hoops_PCPCS = _hoops_ISSSR (_hoops_GCPCS.x);
			if (_hoops_GCPCS.y < 0.0f)
				_hoops_PCPCS = 360.0f - _hoops_PCPCS;

			if (_hoops_PCPCS != 0.0f)
				_hoops_HRCIR.Modify()->rotation += _hoops_PCPCS;
		}
		else {
			Point						temp;
			float						_hoops_ARPAA;

			/* _hoops_HCIA _hoops_IRAA _hoops_PICP _hoops_IIGR _hoops_ISPH _hoops_RIHCR, _hoops_HIS _hoops_ARP _hoops_ISSC _hoops_IS _hoops_IHGP _hoops_IRGGA */
			_hoops_GCPCS = _hoops_IRGA::X_Axis;
			position = _hoops_HPCH::_hoops_IPCH;

			HI_Ident_Matrix (&_hoops_PSPCS.matrix);
			_hoops_PSPCS.matrix._hoops_RAGR = _hoops_GRICR | _hoops_PRICR;

			temp.x = _hoops_RSPCS[1].x - _hoops_RSPCS[0].x;
			temp.y = _hoops_RSPCS[1].y - _hoops_RSPCS[0].y;
			temp.z = _hoops_RSPCS[1].z - _hoops_RSPCS[0].z;
			_hoops_CIPCS = _hoops_SGIHR (temp.x * temp.x + temp.y * temp.y + temp.z * temp.z);
			_hoops_ARPAA = 1.0f / _hoops_CIPCS;
			_hoops_PSPCS.matrix.elements[0][0] = temp.x * _hoops_ARPAA;
			_hoops_PSPCS.matrix.elements[0][1] = temp.y * _hoops_ARPAA;
			_hoops_PSPCS.matrix.elements[0][2] = temp.z * _hoops_ARPAA;

			if (text->region->count > 2) {
				_hoops_PSPCS.matrix.elements[1][0] = _hoops_RSPCS[2].x - _hoops_RSPCS[0].x;
				_hoops_PSPCS.matrix.elements[1][1] = _hoops_RSPCS[2].y - _hoops_RSPCS[0].y;
				_hoops_PSPCS.matrix.elements[1][2] = _hoops_RSPCS[2].z - _hoops_RSPCS[0].z;
				HI_Cross_Product ((Vector *)&_hoops_PSPCS.matrix.elements[0][0],
								  (Vector *)&_hoops_PSPCS.matrix.elements[1][0],
								  (Vector *)&_hoops_PSPCS.matrix.elements[2][0]);
				HI_Normalize ((Vector *)&_hoops_PSPCS.matrix.elements[2][0]);
				HI_Cross_Product ((Vector *)&_hoops_PSPCS.matrix.elements[2][0],
								  (Vector *)&_hoops_PSPCS.matrix.elements[0][0],
								  (Vector *)&_hoops_PSPCS.matrix.elements[1][0]);
				HI_Normalize ((Vector *)&_hoops_PSPCS.matrix.elements[1][0]);
			}
			else if (BIT (text->region->options, _hoops_AGGRP)) {
				Vector		_hoops_ISPI, _hoops_CSPI;

				_hoops_RSPCS[2].x = _hoops_RSPCS[0].x - _hoops_PSPCS.matrix.elements[0][1];
				_hoops_RSPCS[2].y = _hoops_RSPCS[0].y + _hoops_PSPCS.matrix.elements[0][0];
				_hoops_RSPCS[2].z = _hoops_RSPCS[0].z;
				_hoops_RPPCS (_hoops_IHCR, &_hoops_RSPCS[2], &box[2], false);
				_hoops_ISPI.x = box[1].x - box[0].x;
				_hoops_ISPI.y = box[1].y - box[0].y;
				_hoops_CSPI.x = box[2].x - box[0].x;
				_hoops_CSPI.y = box[2].y - box[0].y;

				if (_hoops_ISPI.x * _hoops_CSPI.y - _hoops_CSPI.x * _hoops_ISPI.y > 0.0f) {
					_hoops_PSPCS.matrix.elements[1][0] = -_hoops_PSPCS.matrix.elements[0][1];
					_hoops_PSPCS.matrix.elements[1][1] =  _hoops_PSPCS.matrix.elements[0][0];
				}
				else {
					_hoops_PSPCS.matrix.elements[1][0] =  _hoops_PSPCS.matrix.elements[0][1];
					_hoops_PSPCS.matrix.elements[1][1] = -_hoops_PSPCS.matrix.elements[0][0];
				}
				_hoops_PSPCS.matrix.elements[2][2] = -1.0f;
			}
			else {
				_hoops_PSPCS.matrix.elements[1][0] = -_hoops_PSPCS.matrix.elements[0][1];
				_hoops_PSPCS.matrix.elements[1][1] =  _hoops_PSPCS.matrix.elements[0][0];
				_hoops_PSPCS.matrix.elements[2][2] = -1.0f;
			}
			_hoops_PSPCS.matrix.elements[3][0] = _hoops_RSPCS[0].x;
			_hoops_PSPCS.matrix.elements[3][1] = _hoops_RSPCS[0].y;
			_hoops_PSPCS.matrix.elements[3][2] = _hoops_RSPCS[0].z;

			_hoops_HSPCS = &_hoops_PSPCS.matrix.elements[0][0];

			HD_Downwind_Modelling_Matrix (nr, (Attribute *)&_hoops_PSPCS);

			/* _hoops_PAGA: '_hoops_CPSP' _hoops_RGHCS */
		}
	}
	else {
		if (!_hoops_RPPCS (_hoops_IHCR, &text->_hoops_CSAI, &position, false))
			goto _hoops_PP;
	}


	/* _hoops_IHPI _hoops_RH _hoops_PAPPI */
	ZALLOC (ti, Text_Info);
	ti->position = position;
	ti->text = text;
	ti->_hoops_GIPSP = _hoops_HRCIR->font->_hoops_IGGGH;
	ti->_hoops_ICGH = _hoops_HRCIR->font->_hoops_ISISR;

	ti->_hoops_IPPSP = text->_hoops_CSAI;
	if (text->region != null && _hoops_HRCIR->transform == FT_FULL)
		ti->_hoops_IPPSP = _hoops_HPCH::_hoops_IPCH;

	if (_hoops_HRCIR->font->family->font != null)
		ti->flags |= _hoops_HAPSP;

	if (text->count > 0)
		ZALLOC_ARRAY_CACHED (ti->_hoops_HGCSR, text->count, _hoops_PGCSR);

	/* _hoops_HGSR _hoops_RIR _hoops_GAS _hoops_HGIIP */
	if (text->_hoops_PIHIR != null) {
		ti->flags |= _hoops_AAPSP;

		for (i=0; i<text->count; i++) {
			_hoops_HIHIR *_hoops_PIHIR = &text->_hoops_PIHIR[i];

			ti->_hoops_HGCSR[i].flags = TKIF_NONE;

			if (BIT(_hoops_PIHIR->_hoops_HAICA, _hoops_PAGRP)) {
				ti->_hoops_HGCSR[i].flags |= TKIF_OMITTED;
				ti->_hoops_RIPSP++;
				ti->_hoops_HGCSR[i].nr = nr;
				ti->_hoops_HGCSR[i]._hoops_APPSP = null;
				ti->_hoops_HGCSR[i].height = _hoops_HRCIR->font->_hoops_IGGGH;
			}
			else {
				if (BIT(_hoops_PIHIR->_hoops_HAICA, _hoops_HAGRP))
					ti->_hoops_HGCSR[i].flags |= _hoops_IAPSP;

				if (BIT(_hoops_PIHIR->_hoops_HAICA, _hoops_AAGRP)) {
					bool _hoops_IA;

					ti->_hoops_HGCSR[i]._hoops_HPGRP =
						HD_Compute_Generic_Size (nr,
							_hoops_PIHIR->_hoops_HPGRP,
							_hoops_PIHIR->_hoops_RHGRP,
							_hoops_HRCIR->font->_hoops_IGGGH, false, &_hoops_IA, true);

					/* _hoops_RIP _hoops_RPP _hoops_HIIA _hoops_AICS */
					if (_hoops_IA)
						ti->_hoops_HGCSR[i].flags |= _hoops_SAPSP;
				}

				if (BIT(_hoops_PIHIR->_hoops_HAICA, _hoops_APGRP)) {
					bool _hoops_IA;

					ti->_hoops_HGCSR[i]._hoops_PPGRP =
						HD_Compute_Generic_Size (nr,
							_hoops_PIHIR->_hoops_PPGRP,
							_hoops_PIHIR->_hoops_AHGRP,
							_hoops_HRCIR->font->_hoops_IGGGH, false, &_hoops_IA, true);

					/* _hoops_RIP _hoops_RPP _hoops_HIIA _hoops_AICS */
					if (_hoops_IA)
						ti->_hoops_HGCSR[i].flags |= _hoops_GPPSP;
				}

				if (ANYBIT(_hoops_PIHIR->_hoops_HAICA, _hoops_GAGRP|_hoops_RAGRP|_hoops_IAGRP|_hoops_CAGRP|_hoops_SAGRP)) {
					ti->_hoops_HGCSR[i].nr = nr.Copy();
					Net_Rendition alter &	_hoops_CRAI = ti->_hoops_HGCSR[i].nr;
					_hoops_IGCSR alter &	_hoops_IRRIP = _hoops_CRAI->_hoops_SISI.Modify();

					if (BIT (_hoops_PIHIR->_hoops_HAICA, _hoops_RAGRP)) {
						_hoops_IRRIP->_hoops_GHGRP = _hoops_PIHIR->_hoops_GHGRP;
						_hoops_IRRIP->_hoops_PHP = _hoops_PIHIR->size;
						if (_hoops_IRRIP->_hoops_GHGRP == GSU_PERCENT) {
							_hoops_IRRIP->_hoops_PHP = HD_Compute_Generic_Size (nr,
									_hoops_IRRIP->_hoops_PHP, _hoops_IRRIP->_hoops_GHGRP,
									_hoops_HRCIR->font->_hoops_ISISR, false, 0, true);
							_hoops_IRRIP->_hoops_GHGRP = GSU_PIXELS;
						}
					}

					if (BIT (_hoops_PIHIR->_hoops_HAICA, _hoops_CAGRP))
						_hoops_IRRIP->width_scale = _hoops_PIHIR->width_scale;

					if (BIT (_hoops_PIHIR->_hoops_HAICA, _hoops_IAGRP))
						_hoops_IRRIP->_hoops_IPGRP = _hoops_PIHIR->_hoops_IPGRP;

					if (_hoops_PIHIR->_hoops_HGPIR != null) {
						_hoops_HPRH (_hoops_IRRIP->_hoops_HSRIP);
						POOL_ZALLOC(ti->_hoops_HGCSR[i]._hoops_APPSP, _hoops_AGPIR, dc->memory_pool);
						ti->_hoops_HGCSR[i]._hoops_APPSP->type = HK_TEXT_FONT;
						ti->_hoops_HGCSR[i]._hoops_APPSP->_hoops_HIHI = 1;
						ti->_hoops_HGCSR[i]._hoops_APPSP->_hoops_HGPIR = HI_Copy_Font_Names(_hoops_PIHIR->_hoops_HGPIR);
						_hoops_IRRIP->_hoops_HSRIP = ti->_hoops_HGCSR[i]._hoops_APPSP;
						_hoops_PRRH (_hoops_IRRIP->_hoops_HSRIP);
					}
					else
						ti->_hoops_HGCSR[i]._hoops_APPSP = null;

					if (BIT (_hoops_PIHIR->_hoops_HAICA, _hoops_SAGRP)) {
						if (BIT (_hoops_PIHIR->_hoops_HAICA, _hoops_GPGRP))
							_hoops_IRRIP->rotation = _hoops_PIHIR->rotation + _hoops_PCPCS;	/* _hoops_ISPH _hoops_RCSA _hoops_GPP _hoops_SCIA _hoops_IIGR _hoops_RGSR */
						else
							_hoops_IRRIP->rotation += _hoops_PIHIR->rotation + _hoops_PCPCS;
					}

					if (BIT (_hoops_PIHIR->_hoops_HAICA, _hoops_RPGRP)) {
						HD_Figure_Driver_Color (_hoops_CRAI, &_hoops_PIHIR->color, &_hoops_IRRIP->color);
						_hoops_IRRIP->_hoops_CHA.Modify()->_hoops_CSHR = _hoops_PIHIR->color;
						_hoops_IRRIP->_hoops_RGIHP = null;
						ti->_hoops_HGCSR[i].flags |= _hoops_RPPSP;
					}

					// _hoops_PCHIA _hoops_RHGS _hoops_HRCSR _hoops_RPP _hoops_GII
					_hoops_IRRIP->_hoops_SRRIP();

					do {
						HD_Choose_Font (_hoops_CRAI, _hoops_IRRIP->_hoops_HSRIP->_hoops_HGPIR, encoding, true);

						/* _hoops_GHCA _hoops_HAR _hoops_SHH _hoops_SHSS _hoops_IS _hoops_HSRS _hoops_GII _hoops_HRCSR _hoops_GGR _hoops_RGR _hoops_AGIR, _hoops_HIS _hoops_SGH _hoops_HGSI _hoops_SPR */
						if (_hoops_IRRIP->font == null) {
							/*_hoops_ASIGA _hoops_PSIIR */
							_hoops_IRRIP->font = _hoops_HRCIR->font;
						}
					} _hoops_RGGA (HD_Load_Font (dc, _hoops_IRRIP->font));

					ti->_hoops_HGCSR[i].height = _hoops_IRRIP->font->_hoops_ISISR;

					if (_hoops_IRRIP->font->_hoops_IGGGH > ti->_hoops_GIPSP)
						ti->_hoops_GIPSP = _hoops_IRRIP->font->_hoops_IGGGH;

					if (_hoops_IRRIP->font->_hoops_ISISR > ti->_hoops_ICGH)
						ti->_hoops_ICGH = _hoops_IRRIP->font->_hoops_ISISR;

					if (_hoops_IRRIP->font->family->font != null)
						ti->flags |= _hoops_HAPSP;
				}
				else {
					ti->_hoops_HGCSR[i].nr = nr;
					ti->_hoops_HGCSR[i]._hoops_APPSP = null;
					ti->_hoops_HGCSR[i].height = _hoops_HRCIR->font->_hoops_ISISR;

					if (BIT (_hoops_PIHIR->_hoops_HAICA, _hoops_RPGRP)) {
						Net_Rendition alter &	_hoops_CRAI = ti->_hoops_HGCSR[i].nr.Modify();
						_hoops_IGCSR alter &	_hoops_IRRIP = _hoops_CRAI->_hoops_SISI.Modify();

						HD_Figure_Driver_Color (_hoops_CRAI, &_hoops_PIHIR->color, &_hoops_IRRIP->color);
						_hoops_IRRIP->_hoops_CHA.Modify()->_hoops_CSHR = _hoops_PIHIR->color;
						_hoops_IRRIP->_hoops_RGIHP = null;
						ti->_hoops_HGCSR[i].flags |= _hoops_RPPSP;
					}
				}
 			}
		}
	}
	else {
		for (i=0; i<text->count; i++) {
			ti->_hoops_HGCSR[i].nr = nr;
			ti->_hoops_HGCSR[i]._hoops_APPSP = null;
			ti->_hoops_HGCSR[i].flags = TKIF_NONE;
			ti->_hoops_HGCSR[i].height = _hoops_HRCIR->font->_hoops_ISISR;
		}
	}



	/* _hoops_SICR _hoops_AGHCS _hoops_PPR _hoops_PSPA _hoops_IS _hoops_RIHRR _hoops_ASPA */
	if (_hoops_HRCIR->_hoops_PCPAP != 0.0f) {
		bool	_hoops_IA;

		ti->_hoops_PCPAP = HD_Compute_Generic_Size (nr, _hoops_HRCIR->_hoops_PCPAP, _hoops_HRCIR->_hoops_GGHAP,
												   1.0f, (_hoops_HRCIR->transform == FT_FULL),  &_hoops_IA, false);

		if (!_hoops_IA) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "'extra space units' ?");
			ti->_hoops_PCPAP = 0;
		}

		if (_hoops_HRCIR->transform == FT_FULL &&
			_hoops_HRCIR->_hoops_GGHAP != GSU_ORU &&
			_hoops_HRCIR->_hoops_GGHAP != _hoops_SPSC) {
			_hoops_HHRA const *		_hoops_SPH = nr->transform_rendition->_hoops_SPH;

			if (_hoops_SPH->_hoops_CSIH < _hoops_SGRA->_hoops_CSIH) {
				if (_hoops_SPH->_hoops_CSIH > 1.0f && _hoops_SGRA->_hoops_CSIH >= 1.0f)
					ti->_hoops_PCPAP /= _hoops_SPH->_hoops_CSIH;
			}
			else {
				if (_hoops_SPH->_hoops_CSIH < 1.0f && _hoops_SGRA->_hoops_CSIH <= 1.0f)
					ti->_hoops_PCPAP *= _hoops_SPH->_hoops_CSIH;
			}
		}
	}
	else
		ti->_hoops_PCPAP = 0.0f;

	/* _hoops_SICR _hoops_PGHCS _hoops_PPR _hoops_PSPA _hoops_IS _hoops_RIHRR _hoops_ASPA */
	if (_hoops_HRCIR->_hoops_HCPAP != 0.0f && dc->_hoops_APHHP == null) {
		bool	_hoops_IA;

		ti->_hoops_HCPAP = HD_Compute_Generic_Size (nr,  _hoops_HRCIR->_hoops_HCPAP, _hoops_HRCIR->_hoops_RGHAP,
													  1.0f, (_hoops_HRCIR->transform == FT_FULL),  &_hoops_IA, false);

		if (!_hoops_IA) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "'greeking limit units' ?");
			ti->_hoops_HCPAP = 0;
		}

	}
	else
		ti->_hoops_HCPAP = 0.0f;


	if (BIT (_hoops_HRCIR->transform, FT_POSITION_ONLY) && _hoops_HRCIR->_hoops_CRRIP) {
		Point		line[2];

		line[0] = text->_hoops_CSAI;
		line[1] = line[0] + _hoops_HRCIR->path;
		_hoops_RPPCS (_hoops_IHCR, &line[0], &line[0], false);
		_hoops_RPPCS (_hoops_IHCR, &line[1], &line[1], false);

		_hoops_HRCIR.Modify()->path = line[1] - line[0];
		_hoops_HRCIR->path.z = 0.0f;
		_hoops_HRCIR->path._hoops_AAIAR();
		_hoops_HRCIR->rotation = _hoops_AGGGA (_hoops_HRCIR->path.y, _hoops_HRCIR->path.x);

		if (_hoops_HRCIR->transform == FT_POSITION_ADJUSTED && BIT (_hoops_HRCIR->_hoops_PRRIP, TALIGN_INSERTION_POINT)) {
			if (line[0].x > line[1].x  ||  line[0].x == line[1].x && line[0].y > line[1].y) {
				_hoops_HRCIR->path = -_hoops_HRCIR->path;
				_hoops_HRCIR->rotation += 180.0f;
				if (ANYBIT (_hoops_HRCIR->_hoops_PRRIP, TALIGN_HORIZONTAL_MASK))	// _hoops_HAR _hoops_HGHCS
					_hoops_HRCIR->_hoops_PRRIP ^= TALIGN_LEFT | TALIGN_RIGHT;
			}
		}

		_hoops_HRCIR->transform = FT_NONE;
	}


	_hoops_ACPCS = _hoops_AGGGA (_hoops_HRCIR->path.y, _hoops_HRCIR->path.x) + _hoops_PCPCS;
	if (_hoops_ACPCS < 0.0f)
		_hoops_ACPCS += 360.0f;
	_hoops_CGSPH = _hoops_HRCIR->_hoops_CRRIP || (Abs (_hoops_HRCIR->rotation - _hoops_ACPCS) < 0.5f);


	ti->path.x = _hoops_RCPCS.x = _hoops_HRCIR->path.x * _hoops_HRCIR->spacing;
	ti->path.y = _hoops_RCPCS.y = _hoops_HRCIR->path.y * _hoops_HRCIR->spacing;
	ti->path.z = _hoops_RCPCS.z = _hoops_HRCIR->path.z * _hoops_HRCIR->spacing;


	/* _hoops_HGAPR _hoops_IGHCS _hoops_AGGPA _hoops_CGHCS _hoops_SGHCS _hoops_GCPAR _hoops_GRHCS _hoops_GCPAR _hoops_RRHCS _hoops_ARAGP! */

	ti->_hoops_CSAGR = ti->position;

	/* _hoops_PAGA: _hoops_IRISR _hoops_IPPHR _hoops_CPPHR _hoops_HPRGR _hoops_IGAA *_hoops_CRRPR* _hoops_GC,
	**		 _hoops_HPGP _hoops_HPRGR _hoops_APPS _hoops_RHAP _hoops_HAR.							*/

	/* _hoops_RCSA _hoops_GRR _hoops_GAS _hoops_GRS _hoops_SHH _hoops_CHCC */
	_hoops_RICH (_hoops_HRCIR->rotation - _hoops_PCPCS, ti->_hoops_GHPSP.y, ti->_hoops_GHPSP.x);
	ti->_hoops_GHPSP.z = 0.0f;

	_hoops_HIPCS.x = _hoops_HRCIR->path.x * ti->_hoops_GHPSP.x	+  _hoops_HRCIR->path.y * ti->_hoops_GHPSP.y;
	_hoops_HIPCS.y = _hoops_HRCIR->path.y * ti->_hoops_GHPSP.x	-  _hoops_HRCIR->path.x * ti->_hoops_GHPSP.y;
	_hoops_HIPCS.z = _hoops_HRCIR->path.z;

#if 1	/* _hoops_HHH _hoops_RRGR _hoops_GGR _hoops_ARHCS [_hoops_PAHH _hoops_PPRAR] & _hoops_PGHGR _hoops_CIGR _hoops_SGH _hoops_RGR, _hoops_HIH _hoops_PAHH _hoops_RHPH _hoops_HA */
	ti->_hoops_AHPSP.x = _hoops_HIPCS.x * _hoops_HIPCS.x;
	ti->_hoops_AHPSP.y = _hoops_HIPCS.y * _hoops_HIPCS.y;
	ti->_hoops_AHPSP.z = _hoops_HIPCS.z * _hoops_HIPCS.z;	/* _hoops_GRS _hoops_SIPIR _hoops_GGR _hoops_HCH _hoops_SPHR */
#endif

	ti->_hoops_PHPSP.x =  _hoops_HRCIR->path.y * _hoops_HRCIR->font->_hoops_IGGGH * _hoops_HRCIR->_hoops_ICPAP;
	ti->_hoops_PHPSP.y = -_hoops_HRCIR->path.x * _hoops_HRCIR->font->_hoops_IGGGH * _hoops_HRCIR->_hoops_ICPAP;
	ti->_hoops_PHPSP.z = 0.0f;


	/* _hoops_CSGA _hoops_III _hoops_PPR _hoops_GAS _hoops_SISRI */
	_hoops_GIPCS = 0.0f;
	_hoops_IIPCS = 0;


	if (_hoops_HRCIR->_hoops_ICRIP) {
		for (line = 0; line < text->_hoops_PICHR; ++line) {
			if (text->_hoops_ICI[line] > 0) {
				for (i=0; i<text->_hoops_ICI[line]; i++) {
					int ki = (text->_hoops_RIHIR[line] - text->karacters) + i;

					if (!BIT(ti->_hoops_HGCSR[i].flags, TKIF_OMITTED)) {
						if (HD_Measure_Characters (ti->_hoops_HGCSR[ki].nr, 1, &text->karacters[ki], encoding, &ti->_hoops_HGCSR[ki].width)) {
							ti->flags |= _hoops_AAPSP|_hoops_PAPSP;
							ti->_hoops_HGCSR[ki].flags |= _hoops_CAPSP;
						}
						/* _hoops_GHAA _hoops_IGAA _hoops_CSRA */
						ti->_hoops_HGCSR[ki].width *= Abs(ti->_hoops_HGCSR[ki].nr->_hoops_SISI->width_scale);

						if (_hoops_SIPCS < ti->_hoops_HGCSR[ki].width)
							_hoops_SIPCS = ti->_hoops_HGCSR[ki].width;
					}
				}
			}
		}
	}

	if (text->_hoops_PICHR > 0) {
		ALLOC_ARRAY (_hoops_CCPCS, text->_hoops_PICHR, float);
		ALLOC_ARRAY (_hoops_SCPCS, text->_hoops_PICHR, float);
		ALLOC_ARRAY (_hoops_GSPCS, text->_hoops_PICHR, float);
		ALLOC_ARRAY (_hoops_HHPSP, text->_hoops_PICHR, Vector);
	}

	_hoops_AHPCS	 = 0.0f;
	_hoops_RSICC = 0.0f;
	_hoops_PHPCS	 = 0.0f;

	for (line = 0; line < text->_hoops_PICHR; ++line) {
		_hoops_CCPCS[line] = 0.0f;
		_hoops_SCPCS[line] = 0.0f;
		_hoops_GSPCS[line] = 0.0f;

		if (text->_hoops_ICI[line] > 0) {
			_hoops_PGCSR *		_hoops_PRHCS = null;
			_hoops_PGCSR *		_hoops_HRHCS = null;
			int							_hoops_IRHCS = 0;
			Vector						_hoops_AHPSP = _hoops_IRGA::_hoops_CRGA;
			bool						_hoops_CRHCS = false;

			for (i=0; i<text->_hoops_ICI[line]; i++) {
				int						ki = (text->_hoops_RIHIR[line] - text->karacters) + i;
				_hoops_PGCSR *	_hoops_HGCSR = &ti->_hoops_HGCSR[ki];

				_hoops_HGCSR->offset = ki;

				if (!BIT(ti->_hoops_HGCSR[i].flags, TKIF_OMITTED)) {
					Vector			_hoops_SRHCS;
					float				_hoops_GAHCS = 0.0f;

					if (_hoops_HRCIR->_hoops_ICRIP) {
						_hoops_GAHCS = 0.5f * (_hoops_SIPCS - _hoops_HGCSR->width);
						_hoops_HGCSR->width = _hoops_SIPCS;
					}
					else {
						if (HD_Measure_Characters (_hoops_HGCSR->nr, 1, &text->karacters[ki], encoding, &_hoops_HGCSR->width)) {
							ti->flags |= _hoops_AAPSP|_hoops_PAPSP;
							_hoops_HGCSR->flags |= _hoops_CAPSP;
						}

						/* _hoops_GHAA _hoops_IGAA _hoops_CSRA */
						_hoops_HGCSR->width *= Abs (_hoops_HGCSR->nr->_hoops_SISI->width_scale);
					}

					/* _hoops_RCSA _hoops_IIGR _hoops_GRR _hoops_GAS _hoops_CSCHR _hoops_IS _hoops_SCH'_hoops_GRI _hoops_CRAA */
					_hoops_SRHCS.z = 0.0f;

					if (Abs (_hoops_HGCSR->nr->_hoops_SISI->rotation - _hoops_ACPCS) > 0.5f) {
						_hoops_RICH (_hoops_HGCSR->nr->_hoops_SISI->rotation - _hoops_ACPCS,
								_hoops_SRHCS.y, _hoops_SRHCS.x);

						_hoops_HGCSR->string.width =  Abs (_hoops_HGCSR->width  * _hoops_SRHCS.x) +
											   Abs (_hoops_HGCSR->height * _hoops_SRHCS.y);
						_hoops_HGCSR->string.height = Abs (_hoops_HGCSR->width  * _hoops_SRHCS.y) +
											   Abs (_hoops_HGCSR->height * _hoops_SRHCS.x);
					}
					else {
						_hoops_SRHCS.x = 1.0f;
						_hoops_SRHCS.y = 0.0f;

						_hoops_HGCSR->string.width = _hoops_HGCSR->width;
						_hoops_HGCSR->string.height = _hoops_HGCSR->height;
					}

					if (_hoops_HGCSR->nr->_hoops_SISI->width_scale < 0.0f) {
						_hoops_SRHCS.x = -_hoops_SRHCS.x;
						_hoops_SRHCS.y = -_hoops_SRHCS.y;

						if (_hoops_SRHCS.x > 0) {
							if (_hoops_SRHCS.y >= 0) {
								_hoops_HGCSR->string.x = 0;
								_hoops_HGCSR->string.y = _hoops_HGCSR->height * _hoops_SRHCS.x;
							}
							else {
								_hoops_HGCSR->string.x = -_hoops_HGCSR->height * _hoops_SRHCS.y;
								_hoops_HGCSR->string.y = _hoops_HGCSR->string.height;
							}
						}
						else {
							if (_hoops_SRHCS.y >= 0) {
								_hoops_HGCSR->string.x = -_hoops_HGCSR->width * _hoops_SRHCS.x;
								_hoops_HGCSR->string.y = 0;
							}
							else {
								_hoops_HGCSR->string.x = _hoops_HGCSR->string.width;
								_hoops_HGCSR->string.y = -_hoops_HGCSR->width * _hoops_SRHCS.y;
							}
						}
					}
					else {
						if (_hoops_SRHCS.x > 0) {
							if (_hoops_SRHCS.y >= 0) {
								_hoops_HGCSR->string.x = _hoops_HGCSR->height * _hoops_SRHCS.y;
								_hoops_HGCSR->string.y = 0;
							}
							else {
								_hoops_HGCSR->string.x = 0;
								_hoops_HGCSR->string.y = -_hoops_HGCSR->width * _hoops_SRHCS.y;
							}
						}
						else {
							if (_hoops_SRHCS.y >= 0) {
								_hoops_HGCSR->string.x = _hoops_HGCSR->string.width;
								_hoops_HGCSR->string.y = -_hoops_HGCSR->height * _hoops_SRHCS.x;
							}
							else {
								_hoops_HGCSR->string.x = -_hoops_HGCSR->width * _hoops_SRHCS.x;
								_hoops_HGCSR->string.y = _hoops_HGCSR->string.height;
							}
						}
					}

					if (_hoops_CRHCS) {
						_hoops_HGCSR->string.x += _hoops_GAHCS * _hoops_SRHCS.x;
						_hoops_HGCSR->string.y += _hoops_GAHCS * _hoops_SRHCS.y;
					}

					/* _hoops_RIGII _hoops_IS _hoops_GIRA _hoops_HRGR _hoops_IIHA _hoops_GPP _hoops_RH _hoops_GAS _hoops_HSCHR _hoops_CSCHR _hoops_IS _hoops_RH _hoops_CRAA */
					_hoops_AHPSP.x = _hoops_SRHCS.x * _hoops_SRHCS.x;
					_hoops_AHPSP.y = _hoops_SRHCS.y * _hoops_SRHCS.y;
					_hoops_AHPSP.z = _hoops_HRCIR->path.z * _hoops_HRCIR->path.z;


					/* _hoops_RCSA _hoops_GRR _hoops_GAS _hoops_GRS _hoops_SHH _hoops_CHCC _hoops_GPP _hoops_SHPR (_hoops_HAPP _hoops_ICSA) */
					if (_hoops_HGCSR->nr->_hoops_SISI->rotation != _hoops_PCPCS) {
						_hoops_RICH (_hoops_HGCSR->nr->_hoops_SISI->rotation - _hoops_PCPCS,
								_hoops_SRHCS.y, _hoops_SRHCS.x);

						_hoops_HGCSR->screen.width =  Abs (_hoops_HGCSR->width *  _hoops_SRHCS.x) +
											   Abs (_hoops_HGCSR->height * _hoops_SRHCS.y);
						_hoops_HGCSR->screen.height = Abs (_hoops_HGCSR->width *  _hoops_SRHCS.y) +
											   Abs (_hoops_HGCSR->height * _hoops_SRHCS.x);
					}
					else {
						_hoops_SRHCS.x = 1.0f;
						_hoops_SRHCS.y = 0.0f;

						_hoops_HGCSR->screen.width = _hoops_HGCSR->width;
						_hoops_HGCSR->screen.height = _hoops_HGCSR->height;
					}

					if (_hoops_HGCSR->nr->_hoops_SISI->width_scale < 0.0f) {
						_hoops_SRHCS.x = -_hoops_SRHCS.x;
						_hoops_SRHCS.y = -_hoops_SRHCS.y;

						if (_hoops_SRHCS.x > 0) {
							if (_hoops_SRHCS.y >= 0) {
								_hoops_HGCSR->screen.x = 0;
								_hoops_HGCSR->screen.y = _hoops_HGCSR->height * _hoops_SRHCS.x;
							}
							else {
								_hoops_HGCSR->screen.x = -_hoops_HGCSR->height * _hoops_SRHCS.y;
								_hoops_HGCSR->screen.y = _hoops_HGCSR->screen.height;
							}
						}
						else {
							if (_hoops_SRHCS.y >= 0) {
								_hoops_HGCSR->screen.x = -_hoops_HGCSR->width * _hoops_SRHCS.x;
								_hoops_HGCSR->screen.y = 0;
							}
							else {
								_hoops_HGCSR->screen.x = _hoops_HGCSR->screen.width;
								_hoops_HGCSR->screen.y = -_hoops_HGCSR->width * _hoops_SRHCS.y;
							}
						}
					}
					else {
						if (_hoops_SRHCS.x > 0) {
							if (_hoops_SRHCS.y >= 0) {
								_hoops_HGCSR->screen.x = _hoops_HGCSR->height * _hoops_SRHCS.y;
								_hoops_HGCSR->screen.y = 0;
							}
							else {
								_hoops_HGCSR->screen.x = 0;
								_hoops_HGCSR->screen.y = -_hoops_HGCSR->width * _hoops_SRHCS.y;
							}
						}
						else {
							if (_hoops_SRHCS.y >= 0) {
								_hoops_HGCSR->screen.x = _hoops_HGCSR->screen.width;
								_hoops_HGCSR->screen.y = -_hoops_HGCSR->height * _hoops_SRHCS.x;
							}
							else {
								_hoops_HGCSR->screen.x = -_hoops_HGCSR->width * _hoops_SRHCS.x;
								_hoops_HGCSR->screen.y = _hoops_HGCSR->screen.height;
							}
						}
					}

					if (_hoops_CRHCS) {
						_hoops_HGCSR->screen.x += _hoops_GAHCS * _hoops_SRHCS.x;
						_hoops_HGCSR->screen.y += _hoops_GAHCS * _hoops_SRHCS.y;
					}


					if (_hoops_HGCSR->nr->_hoops_SISI->_hoops_IPGRP < 0.0f ||
						_hoops_HRHCS && _hoops_HRHCS->nr->_hoops_SISI->_hoops_IPGRP > 0.0f) {
						float	_hoops_GGHCR, _hoops_AGHCR;
						float	_hoops_RAHCS, _hoops_AAHCS;
						float	_hoops_PAHCS, _hoops_HAHCS;
						float	_hoops_IAHCS;

						_hoops_PAHCS = _hoops_HGCSR->height;
						if (BIT(_hoops_HGCSR->flags, _hoops_SAPSP) &&
							_hoops_HGCSR->_hoops_HPGRP > 0.0f) {
							_hoops_PAHCS += _hoops_HGCSR->_hoops_HPGRP;
						}

						if (_hoops_HRHCS) {
							_hoops_HAHCS = _hoops_HRHCS->height;
							if (BIT(_hoops_HRHCS->flags, _hoops_SAPSP) &&
								_hoops_HRHCS->_hoops_HPGRP > 0.0f) {
								_hoops_HAHCS += _hoops_HRHCS->_hoops_HPGRP;
							}

							_hoops_IAHCS = _hoops_AHIA (_hoops_PAHCS, _hoops_HAHCS);
						}
						else
							_hoops_IAHCS = _hoops_PAHCS;


						_hoops_RICH (_hoops_HGCSR->nr->_hoops_SISI->_hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR);
						_hoops_RAHCS = _hoops_IAHCS * _hoops_GGHCR / _hoops_AGHCR;

						if (_hoops_HRHCS) {
							_hoops_RICH (_hoops_HRHCS->nr->_hoops_SISI->_hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR);
							_hoops_AAHCS = _hoops_IAHCS * _hoops_GGHCR / _hoops_AGHCR;
						}
						else
							_hoops_AAHCS = 0.0f;

						_hoops_HGCSR->slant_extra = _hoops_AAHCS - _hoops_RAHCS;
						if (_hoops_HGCSR->slant_extra < 0.0f)
							_hoops_HGCSR->slant_extra = 0.0f;
					}
					else
						_hoops_HGCSR->slant_extra = 0.0f;

					if (_hoops_PRHCS == null) {
						if (_hoops_HGCSR->nr->_hoops_SISI->_hoops_IPGRP < 0.0f) {
							float	_hoops_GGHCR, _hoops_AGHCR;
							float	_hoops_IPGRP;
							float	height;

							height = _hoops_HGCSR->height;
							if (BIT(_hoops_HGCSR->flags, _hoops_SAPSP) &&
								_hoops_HGCSR->_hoops_HPGRP > 0.0f) {
								height += _hoops_HGCSR->_hoops_HPGRP;
							}

							_hoops_RICH (_hoops_HGCSR->nr->_hoops_SISI->_hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR);
							_hoops_IPGRP = height * _hoops_GGHCR / _hoops_AGHCR;

							_hoops_SCPCS[line] = _hoops_IPGRP;

							_hoops_CCPCS[line] += _hoops_AHPSP.x * _hoops_SCPCS[line];
						}

						_hoops_PRHCS = _hoops_HGCSR;
					}

					/* _hoops_CSGA _hoops_GRR _hoops_SPR _hoops_IS _hoops_SRCH _hoops_HCHAR _hoops_IAISR _hoops_IH _hoops_CAHCS _hoops_SAHCS */
					if (_hoops_HGCSR->nr->_hoops_SISI->_hoops_IPGRP > 0.0f) {
						float	_hoops_GGHCR, _hoops_AGHCR;
						float	_hoops_IPGRP;
						float	height;

						height = _hoops_HGCSR->height;
						if (BIT(_hoops_HGCSR->flags, _hoops_SAPSP) &&
							_hoops_HGCSR->_hoops_HPGRP > 0.0f) {
							height += _hoops_HGCSR->_hoops_HPGRP;
						}

						_hoops_RICH (_hoops_HGCSR->nr->_hoops_SISI->_hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR);
						_hoops_IPGRP = height * _hoops_GGHCR / _hoops_AGHCR;

						_hoops_GSPCS[line] = _hoops_IPGRP;
					}
					else
						_hoops_GSPCS[line] = 0.0f;

					_hoops_HGCSR->_hoops_CGSIR = _hoops_AHPSP.x * _hoops_HGCSR->width +
									  _hoops_AHPSP.y * _hoops_HGCSR->nr->_hoops_SISI->font->_hoops_IGGGH +
									  _hoops_AHPSP.z * _hoops_HGCSR->width;
					_hoops_CCPCS[line] += _hoops_HGCSR->_hoops_CGSIR;
					_hoops_CCPCS[line] += _hoops_HGCSR->slant_extra * (_hoops_AHPSP.x + _hoops_AHPSP.z);

					_hoops_IRHCS++;

					_hoops_HRHCS = &ti->_hoops_HGCSR[ki];
				}
			}
			_hoops_CCPCS[line] += _hoops_AHPSP.x * _hoops_GSPCS[line];	/* _hoops_GPHCS _hoops_GRS _hoops_PSSP _hoops_CHHHP _hoops_GSPR */

			_hoops_RIPCS = _hoops_PRHCS->width;
			_hoops_AIPCS = _hoops_HRHCS->width;


			_hoops_CCPCS[line] += ti->_hoops_PCPAP * (_hoops_IRHCS - 1);

			_hoops_HHPSP[line] = ti->path * _hoops_CCPCS[line];

			if (_hoops_CCPCS[line] > _hoops_GIPCS) {
				_hoops_GIPCS = _hoops_CCPCS[line];
				_hoops_IIPCS = line;
			}

			_hoops_CCPCS[line] -= 0.5f * (_hoops_PRHCS->_hoops_CGSIR + _hoops_HRHCS->_hoops_CGSIR);

			{
				float	width, height, depth;

				width  = Abs (ti->path.x) * _hoops_CCPCS[line] +
							0.5f * (_hoops_PRHCS->screen.width + _hoops_HRHCS->screen.width);
				height = Abs (ti->path.y) * _hoops_CCPCS[line] +
							0.5f * (_hoops_PRHCS->screen.height + _hoops_HRHCS->screen.height);
				depth  = Abs (ti->path.z) * _hoops_CCPCS[line];

				if (width > _hoops_AHPCS)
					_hoops_AHPCS = width;
				if (height > _hoops_RSICC)
					_hoops_RSICC = height;
				if (depth > _hoops_PHPCS)
					_hoops_PHPCS = depth;
			}
		}
	}


	if (_hoops_GIPCS > 0) {
		_hoops_CHPCS = text->_hoops_RIHIR[_hoops_IIPCS] - text->karacters;
		_hoops_SHPCS = (text->_hoops_RIHIR[_hoops_IIPCS] - text->karacters) + text->_hoops_ICI[_hoops_IIPCS] - 1;

		/* _hoops_SRCH _hoops_CAHCS */
		while (BIT(ti->_hoops_HGCSR[_hoops_CHPCS].flags, TKIF_OMITTED)) _hoops_CHPCS++;
		while (BIT(ti->_hoops_HGCSR[_hoops_SHPCS].flags, TKIF_OMITTED)) _hoops_SHPCS--;


		_hoops_RIPCS = ti->_hoops_HGCSR[_hoops_CHPCS].width;
		_hoops_AIPCS = ti->_hoops_HGCSR[_hoops_SHPCS].width;



		_hoops_HHPCS  = (text->_hoops_PICHR - 1) * Abs (ti->_hoops_PHPSP.x);
		_hoops_IHPCS = (text->_hoops_PICHR - 1) * Abs (ti->_hoops_PHPSP.y);

		_hoops_AHPCS	 += _hoops_HHPCS;
		_hoops_RSICC += _hoops_IHPCS;

		if (text->region != null) {
			float	_hoops_RPHCS = 1.0f;

			if (_hoops_HRCIR->transform == FT_FULL) {	// _hoops_IS _hoops_SICR _hoops_ASPA _hoops_IS (_hoops_RRI _hoops_PAR _hoops_CRGP) _hoops_GPRPS
				_hoops_HHRA const *		_hoops_SPH = nr->transform_rendition->_hoops_SPH;

				// _hoops_PAGA: _hoops_RGR _hoops_APSH _hoops_PII _hoops_SCH _hoops_HHS _hoops_SHH:   _hoops_APHCS = 1.0 / _hoops_PPHCS (1.0, _hoops_GPRPS);
				if (_hoops_SPH->projection == _hoops_SSIH ||
					_hoops_SPH->_hoops_CSIH >= _hoops_SGRA->_hoops_CSIH)
					_hoops_RPHCS = nr->transform_rendition->_hoops_SPH->_hoops_SSPA /
									(_hoops_SGRA->_hoops_PHRA.top - _hoops_SGRA->_hoops_PHRA.bottom);
				else
					_hoops_RPHCS = nr->transform_rendition->_hoops_SPH->_hoops_ISPA /
									(_hoops_SGRA->_hoops_PHRA.right - _hoops_SGRA->_hoops_PHRA.left);

				if (_hoops_HRCIR->_hoops_GHGRP != GSU_ORU)
					_hoops_RPHCS /= _hoops_SPH->_hoops_SSPA*0.5f;
			}

			_hoops_AHPCS *= _hoops_RPHCS;

			if (text->region->_hoops_IRGRP == _hoops_PRGRP) {
				if (_hoops_AHPCS != _hoops_CIPCS && ti->path.x != 0.0f) {
					if (_hoops_CHPCS != _hoops_SHPCS) {
						float						_hoops_HPHCS;
						float						_hoops_PRPHA;

						//_hoops_RPP (_hoops_IPHCS->_hoops_HIHP == _hoops_SRSGI)
						//	_hoops_CPHCS *= 0.5f * _hoops_APHCS * (_hoops_RSCHA->_hoops_SPHCS._hoops_SCIA - _hoops_RSCHA->_hoops_SPHCS._hoops_PRPC);

						_hoops_HPHCS = 0.5f * (ti->_hoops_HGCSR[_hoops_CHPCS].screen.width + ti->_hoops_HGCSR[_hoops_SHPCS].screen.width);
						_hoops_HPHCS *= _hoops_RPHCS;

						_hoops_PRPHA = (_hoops_CIPCS - _hoops_HPHCS) / (_hoops_AHPCS - _hoops_HPHCS);

						ti->path.x *= _hoops_PRPHA;
						_hoops_RCPCS.x *= _hoops_PRPHA;
						_hoops_HRCIR.Modify()->spacing *= _hoops_PRPHA;

						for (line=0; line<text->_hoops_PICHR; line++)
							_hoops_HHPSP[line].x *= _hoops_PRPHA;
					}
					else if (text->region->_hoops_IRGRP == _hoops_ARGRP && _hoops_CSPCS) {
						ti->position += (_hoops_AHPCS - _hoops_CIPCS) * _hoops_GCPCS;
					}

					_hoops_AHPCS = _hoops_CIPCS;
				}
			}
			else if (text->region->_hoops_IRGRP == _hoops_ARGRP) {
				if (_hoops_CSPCS) {
					if (_hoops_HRCIR->transform != FT_FULL)
						ti->position += (_hoops_CIPCS - _hoops_AHPCS) * _hoops_GCPCS;
					else {
						_hoops_ISGI			_hoops_GHHCS;

						HI_Ident_Matrix (&_hoops_GHHCS.matrix);
						_hoops_GHHCS.matrix.elements[3][0] = _hoops_CIPCS - _hoops_AHPCS;
						_hoops_GHHCS.matrix._hoops_RAGR = _hoops_PRICR;

						for (i=0; i<text->count; i++) {
							if (ti->_hoops_HGCSR[i].nr == nr)
								ti->_hoops_HGCSR[i].nr = null;
						}

						HD_Downwind_Modelling_Matrix (nr, &_hoops_GHHCS);

						for (i=0; i<text->count; i++) {
							if (ti->_hoops_HGCSR[i].nr == null)
								ti->_hoops_HGCSR[i].nr = nr;
							else
								HD_Downwind_Modelling_Matrix (ti->_hoops_HGCSR[i].nr, &_hoops_GHHCS);
						}
					}
				}
			}

			_hoops_AHPCS /= _hoops_RPHCS;

			if (_hoops_PCPCS != 0.0f) {
				float							_hoops_RHHCS, _hoops_AHHCS, x, y;

				/* _hoops_GHAA _hoops_ICSA _hoops_IS _hoops_GPAC (_hoops_AHSAR _hoops_PHHCS) */
				_hoops_RICH (_hoops_PCPCS, _hoops_RHHCS, _hoops_AHHCS);
				x =	 ti->path.x * _hoops_AHHCS - ti->path.y * _hoops_RHHCS;
				y =	 ti->path.x * _hoops_RHHCS + ti->path.y * _hoops_AHHCS;
				ti->path.x = x;
				ti->path.y = y;

				x =	 ti->_hoops_PHPSP.x * _hoops_AHHCS - ti->_hoops_PHPSP.y * _hoops_RHHCS;
				y =	 ti->_hoops_PHPSP.x * _hoops_RHHCS + ti->_hoops_PHPSP.y * _hoops_AHHCS;
				ti->_hoops_PHPSP.x = x;
				ti->_hoops_PHPSP.y = y;

				for (line=0; line<text->_hoops_PICHR; line++) {
					x =	 _hoops_HHPSP[line].x * _hoops_AHHCS - _hoops_HHPSP[line].y * _hoops_RHHCS;
					y =	 _hoops_HHPSP[line].x * _hoops_RHHCS + _hoops_HHPSP[line].y * _hoops_AHHCS;
					_hoops_HHPSP[line].x = x;
					_hoops_HHPSP[line].y = y;
				}

				/* _hoops_PPR _hoops_PAAP _hoops_HAPPI _hoops_IS _hoops_HACH _hoops_RCSA */
				_hoops_RICH (_hoops_HRCIR->rotation, ti->_hoops_GHPSP.y, ti->_hoops_GHPSP.x);
			}
		}

		/* _hoops_GSPR _hoops_HCH _hoops_HRGR _hoops_ACHPP - _hoops_HIS _hoops_IRHH _hoops_SCH _hoops_IGGRA _hoops_HHSH _hoops_PII _hoops_RH _hoops_IGAA */
		if (text->count > 1)
			_hoops_PIPCS = _hoops_PHPCS / (float)(text->count - 1);
		else
			_hoops_PIPCS = 0;

		/* _hoops_PAPPI->_hoops_GPHCS._hoops_SSH *= _hoops_HHHCS; */
	}
	else {
		_hoops_HACC		*_hoops_GRRPH;

		/* _hoops_PSP _hoops_RIHRR _hoops_HCGR - _hoops_PIHA _hoops_SHH _hoops_IRS _hoops_HASRH? */
		if (text->_hoops_AAPGR == null)
			goto _hoops_PP;

		ALLOC(_hoops_GRRPH, _hoops_HACC);
		ZERO_STRUCT(_hoops_GRRPH, _hoops_HACC);
		_hoops_GRRPH->type = _hoops_AGCP;
		_hoops_GRRPH->_hoops_HIHI = 1;
		_hoops_GRRPH->_hoops_CSAI.x = text->_hoops_CSAI.x;
		_hoops_GRRPH->_hoops_CSAI.y = text->_hoops_CSAI.y;
		_hoops_GRRPH->_hoops_CSAI.z = text->_hoops_CSAI.z;
		_hoops_GRRPH->count = 1;
		_hoops_GRRPH->_hoops_PICHR = 1;

		ALLOC_ARRAY (_hoops_GRRPH->_hoops_ICI, 1, int);
		_hoops_GRRPH->_hoops_ICI[0] = 1;

		ALLOC_ARRAY (_hoops_GRRPH->karacters, 2, Karacter);
		_hoops_GRRPH->karacters[0] = _hoops_PPPCS;
		_hoops_GRRPH->karacters[1] = 0;

		ALLOC_ARRAY (_hoops_GRRPH->_hoops_RIHIR, 1, Karacter*);
		_hoops_GRRPH->_hoops_RIHIR[0] = _hoops_GRRPH->karacters;

		_hoops_GRRPH->encoding = _hoops_SSAIP;

		_hoops_PAPGR(nr, _hoops_GRRPH);

		_hoops_HPRH(_hoops_GRRPH);

		goto _hoops_PP;
	}


	/* _hoops_PPR _hoops_HHH _hoops_SIHC _hoops_IH _hoops_ASGC */

	ti->_hoops_CHPSP.x = -ti->_hoops_GHPSP.y;
	ti->_hoops_CHPSP.y =  ti->_hoops_GHPSP.x;
	ti->_hoops_CHPSP.z = 0.0f;

	ti->_hoops_IHPSP.x = _hoops_HHPSP[_hoops_IIPCS].x;
	ti->_hoops_IHPSP.y = _hoops_HHPSP[_hoops_IIPCS].y;
	ti->_hoops_IHPSP.z = _hoops_HHPSP[_hoops_IIPCS].z;

	ti->_hoops_HPPSP.x = 0;
	ti->_hoops_HPPSP.y = 0;
	ti->_hoops_HPPSP.z = 0;

	if (text->region != null) {
		/* _hoops_HCAGR _hoops_PII _hoops_GSSC-_hoops_RAAP, _hoops_HIH _hoops_SGGGA _hoops_IH _hoops_ISPH _hoops_RCSA */
		float					_hoops_RSIPA;

		switch (text->region->options & _hoops_CGGRP) {
			case _hoops_PGGRP: {
				/* _hoops_IHIS _hoops_GH _hoops_IS _hoops_PRPC _hoops_IIGR _hoops_SCIA _hoops_III _hoops_RPP _hoops_GSIPR-_hoops_III */
				ti->position.x -= _hoops_IHPCS * _hoops_GCPCS.y;
				ti->position.y += _hoops_IHPCS * _hoops_GCPCS.x;
			}	break;

			case _hoops_HGGRP: {
				/* _hoops_GH _hoops_IS _hoops_PRPC _hoops_IIGR _hoops_SCIA _hoops_III _hoops_RPP _hoops_GSIPR-_hoops_III */
				ti->position.x -= 0.5f * (_hoops_IHPCS - _hoops_HRCIR->font->_hoops_ISISR) * _hoops_GCPCS.y;
				ti->position.y += 0.5f * (_hoops_IHPCS - _hoops_HRCIR->font->_hoops_ISISR) * _hoops_GCPCS.x;
			}	break;

			case _hoops_IGGRP: {
				/* _hoops_IHIS _hoops_ISHP _hoops_IS _hoops_PPSI _hoops_HCGR _hoops_RRGI _hoops_RH _hoops_III */
				ti->position.x -= -_hoops_HRCIR->font->_hoops_ISISR * _hoops_GCPCS.y;
				ti->position.y += -_hoops_HRCIR->font->_hoops_ISISR * _hoops_GCPCS.x;
			}	break;
		}

		if (_hoops_HRCIR->path.x < 0.0f) {		/* _hoops_GIGR _hoops_CRAA, _hoops_HAR _hoops_SRSS */
			_hoops_RSIPA = _hoops_AHPCS - ti->_hoops_HGCSR[_hoops_CHPCS].width;
			ti->position.x += _hoops_RSIPA * _hoops_GCPCS.x;
			ti->position.y += _hoops_RSIPA * _hoops_GCPCS.y;
		}

		if (_hoops_HRCIR->path.y < 0.0f) {		/* _hoops_GIGR _hoops_CRAA, _hoops_HAR _hoops_SRSS */
			_hoops_RSIPA = _hoops_RSICC - ti->_hoops_HGCSR[_hoops_CHPCS].height;
			ti->position.x -= _hoops_RSIPA * _hoops_GCPCS.y;
			ti->position.y += _hoops_RSIPA * _hoops_GCPCS.x;
		}

		/* _hoops_HCH _hoops_AHSGP _hoops_HRGR _hoops_ACHPP - _hoops_HIS _hoops_IRHH _hoops_SCH "_hoops_RIPS" _hoops_RGCGA. */
		if (_hoops_HRCIR->path.z < 0.0f)
			ti->position.z += _hoops_PHPCS;
	}
	else if (BIT (_hoops_HRCIR->_hoops_PRRIP, TALIGN_INSERTION_POINT)) {
		// _hoops_PGGRS _hoops_IH _hoops_GSIPR-_hoops_III
		if (ti->path.y > 0.0f)
			ti->position.x -= _hoops_HHPCS;
		else
			ti->position.x += _hoops_HHPCS;
		if (ti->path.x > 0.0f)
			ti->position.y += _hoops_IHPCS;
		else
			ti->position.y -= _hoops_IHPCS;

		switch (_hoops_HRCIR->_hoops_PRRIP & TALIGN_HORIZONTAL_MASK) {
			case TALIGN_LEFT: {
				/* _hoops_AIAH _hoops_ARP _hoops_IH _hoops_RGR */
			}	break;
			case TALIGN_CENTER: {
				ti->position -= 0.5f * ti->_hoops_IHPSP;
			}	break;
			case TALIGN_RIGHT: {
				ti->position -= ti->_hoops_IHPSP;
			}	break;
		}
		switch (_hoops_HRCIR->_hoops_PRRIP & TALIGN_VERTICAL_MASK) {
			case TALIGN_LOWER: {
				/* _hoops_AIAH _hoops_ARP _hoops_IH _hoops_RGR */
			}	break;
			case TALIGN_CENTER: {
				float		_hoops_CCIIP = _hoops_HRCIR->font->_hoops_ISISR + (text->_hoops_PICHR - 1) * _hoops_HRCIR->font->_hoops_IGGGH * _hoops_HRCIR->_hoops_ICPAP;

				ti->position.x += 0.5f * ti->path.y * _hoops_CCIIP;
				ti->position.y -= 0.5f * ti->path.x * _hoops_CCIIP;
			}	break;
			case TALIGN_UPPER: {
				float		_hoops_CCIIP = _hoops_HRCIR->font->_hoops_ISISR + (text->_hoops_PICHR - 1) * _hoops_HRCIR->font->_hoops_IGGGH * _hoops_HRCIR->_hoops_ICPAP;

				ti->position.x += ti->path.y * _hoops_CCIIP;
				ti->position.y -= ti->path.x * _hoops_CCIIP;
			}	break;
		}
	}
	else {
		/* _hoops_IRGGA _hoops_RHCHH */
		switch (_hoops_HRCIR->_hoops_PRRIP) {
			case TA_LOWERLEFT:
			case TA_CENTERLEFT:
			case TA_UPPERLEFT: {
				if (ti->_hoops_PHPSP.x < 0.0f)
					ti->position.x += _hoops_HHPCS;
			}	break;

			case TA_LOWERCENTER:
			case TA_CENTERCENTER:
			case TA_UPPERCENTER: {
				/* _hoops_RHRIR: _hoops_HHAA _hoops_IH _hoops_IHHCS, _hoops_PPR _hoops_HHAA _hoops_IH _hoops_SPRHS */
				ti->_hoops_HPPSP.x = -0.25f * (ti->_hoops_HGCSR[_hoops_CHPCS].width + ti->_hoops_HGCSR[_hoops_SHPCS].width);
				ti->position.x -= _hoops_AHPCS * 0.5f;

				if (ti->_hoops_PHPSP.x < 0.0f)
					ti->position.x += _hoops_HHPCS;
			}	break;

			case TA_LOWERRIGHT:
			case TA_CENTERRIGHT:
			case TA_UPPERRIGHT: {
				ti->position.x -= _hoops_AHPCS;

				if (ti->_hoops_PHPSP.x < 0.0f)
					ti->position.x += _hoops_HHPCS;
			}	break;
		}

		if (ti->path.x < 0.0f)
			ti->position.x += _hoops_AHPCS - ti->_hoops_HGCSR[_hoops_CHPCS].screen.width;

		if (ti->_hoops_PHPSP.y > 0.0f)
			ti->position.x -= _hoops_HHPCS;

		/* _hoops_IRPHR _hoops_RHCHH */
		switch (_hoops_HRCIR->_hoops_PRRIP) {
			case TA_LOWERLEFT:
			case TA_LOWERCENTER:
			case TA_LOWERRIGHT: {
				ti->position.y += _hoops_IHPCS;
			}	break;

			case TA_CENTERLEFT:
			case TA_CENTERCENTER:
			case TA_CENTERRIGHT: {
				ti->position.y += _hoops_IHPCS - _hoops_RSICC * 0.5f;

				/* _hoops_RHRIR: _hoops_HHAA _hoops_IH _hoops_IHHCS, _hoops_PPR _hoops_HHAA _hoops_IH _hoops_SPRHS */
				ti->_hoops_HPPSP.y = -0.25f * (ti->_hoops_HGCSR[_hoops_CHPCS].width + ti->_hoops_HGCSR[_hoops_SHPCS].width);
			}	break;

			case TA_UPPERLEFT:
			case TA_UPPERCENTER:
			case TA_UPPERRIGHT: {
				ti->position.y -= _hoops_RSICC - _hoops_IHPCS;
			}	break;
		}

		if (ti->path.y < 0.0f)
			ti->position.y += _hoops_RSICC - ti->_hoops_HGCSR[_hoops_CHPCS].screen.height;


		if (ti->_hoops_PHPSP.y > 0.0f)
			ti->position.y -= _hoops_IHPCS;
		if (ti->_hoops_PHPSP.x < 0.0f)
			ti->position.y -= _hoops_IHPCS;

		/* _hoops_HCH _hoops_AHSGP _hoops_HRGR _hoops_ACHPP - _hoops_HIS _hoops_IRHH _hoops_SCH "_hoops_RIPS" _hoops_RGCGA. */
		if (ti->path.z < 0.0f)
			ti->position.z += _hoops_PHPCS;
	}

	if (_hoops_HRCIR->transform != FT_NONE  ||  ti->path.z != 0.0f) {
		_hoops_HHRA const *		_hoops_SPH = _hoops_IHCR->_hoops_SPH;
		Point				translate;

		/* _hoops_IH _hoops_HICIP, _hoops_GGRGR-_hoops_GRAS _hoops_RH _hoops_HAHH _hoops_HIHP */

		HD_Compute_Screen_Transform (nr, (Point*)&ti->scale, &translate);

		if (_hoops_HRCIR->_hoops_GHGRP == GSU_ORU)
			ti->scale.y /= 0.5f * _hoops_SPH->_hoops_SSPA;
		ti->scale.x = ti->scale.y;

#if 0
		if (_hoops_SPH->projection == _hoops_SSIH) {
			if (_hoops_SPH->_hoops_CSIH < _hoops_SGRA->_hoops_CSIH)
				ti->scale.y /= _hoops_SGRA->_hoops_CSIH;
			else
				ti->scale.x *= _hoops_SGRA->_hoops_CSIH;
		}
#endif

		if (ti->scale.x < 0.0f)
			ti->scale.x = -ti->scale.x;

		/* _hoops_PPR _hoops_PCPA _hoops_SR _hoops_CPSA _hoops_HHGC _hoops_HRGR _hoops_RH _hoops_AGICR */
		/* ("== 0.0f" _hoops_CGH _hoops_IIP _hoops_IHPS _hoops_IH _hoops_IRS _hoops_SHPR _hoops_HIHP) */
		if (ti->scale.x != 0.0f) ti->scale.x = 1.0f / ti->scale.x;
		if (ti->scale.y != 0.0f) ti->scale.y = 1.0f / ti->scale.y;
		if (ti->scale.z != 0.0f) ti->scale.z = 1.0f / ti->scale.z;

		_hoops_PHPCS *= ti->scale.z;
	}
	else
		ti->scale.x = ti->scale.y = ti->scale.z = 1.0f;

	_hoops_RHPCS.x = ti->position.x;
	_hoops_RHPCS.y = ti->position.y;
	_hoops_RHPCS.z = ti->position.z;

	_hoops_ASPCS = ti->_hoops_ICGH;

	if (_hoops_HRCIR->transform == FT_FULL &&
		_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH) {
		/* _hoops_PHPHA _hoops_HII _hoops_PISH _hoops_HIHP _hoops_RRGR _hoops_IH _hoops_IPAP _hoops_AIHP */
		_hoops_HHRA const *				_hoops_SPH = _hoops_IHCR->_hoops_SPH;
		_hoops_SGCC const &	_hoops_HSGA = _hoops_IHCR->_hoops_IPH;
		Point						origin;
		float						scale;

		/* _hoops_CSCS _hoops_AHC _hoops_IIGR _hoops_RH _hoops_HCGR */
		if (text->region != null) {
			origin.x = 0.5f * (_hoops_RSPCS[0].x + _hoops_RSPCS[1].x);
			origin.y = 0.5f * (_hoops_RSPCS[0].y + _hoops_RSPCS[1].y);
			origin.z = 0.5f * (_hoops_RSPCS[0].z + _hoops_RSPCS[1].z);
			HI_Transform_Points_43 (1, &origin, &_hoops_HSGA->data.elements[0][0], &origin);
		}
		else
			HI_Transform_Points_43 (1, &text->_hoops_CSAI, &_hoops_HSGA->data.elements[0][0], &origin);

		/* '_hoops_GHGP' _hoops_IIGR _hoops_IPPA _hoops_PHGSR _hoops_RHIR _hoops_SARA _hoops_AHC */
		scale = -(_hoops_SPH->position.x * _hoops_SPH->_hoops_IIPCR.x +
				  _hoops_SPH->position.y * _hoops_SPH->_hoops_IIPCR.y +
				  _hoops_SPH->position.z * _hoops_SPH->_hoops_IIPCR.z);
		/* _hoops_PRRGR _hoops_CGRS _hoops_CIAA _hoops_SARA _hoops_AAGA _hoops_CSCHR _hoops_IS _hoops_SARA _hoops_AHC */
		scale += origin.x * _hoops_SPH->_hoops_IIPCR.x + origin.y * _hoops_SPH->_hoops_IIPCR.y + origin.z * _hoops_SPH->_hoops_IIPCR.z;
		/* _hoops_CSRA _hoops_RRPS _hoops_IS _hoops_SARA _hoops_GIRA */
		scale /= _hoops_SPH->_hoops_SRIR;

		/* _hoops_PSSSR _hoops_IH _hoops_AHCI _hoops_ARAR */
		if (scale > _hoops_IHCR->_hoops_CHCR) {
			/* _hoops_PAGA: _hoops_SR _hoops_SGH _hoops_CSRA _hoops_PGCHR _hoops_IIGR _hoops_RH _hoops_IPAP _hoops_AGIR, _hoops_SR _hoops_HHGC _hoops_IS _hoops_HGCR _hoops_RH _hoops_IGIR, _hoops_HAR _hoops_PAISR _hoops_SCH */
			_hoops_ASPCS /= scale;
		}
	}


	if (_hoops_GIPCS == 0) goto _hoops_PP; /* _hoops_PIHA _hoops_SHH _hoops_HASRH _hoops_RGAR */

	/* _hoops_PGSA _hoops_RH _hoops_HCGR _hoops_III _hoops_HPP _hoops_III */
	for (line = 0; line < text->_hoops_PICHR; ++line) {
		int				_hoops_PPPSP;

		if ((count = text->_hoops_ICI[line]) == 0)
			continue;

		ti->line_index = line;
		_hoops_IHSCP = text->_hoops_RIHIR[line];
		_hoops_PPPSP = text->_hoops_RIHIR[line] - text->karacters;

		ti->position = _hoops_RHPCS + line * ti->_hoops_PHPSP;
		ti->_hoops_HHPSP = _hoops_HHPSP[line];

		if (_hoops_HRCIR->_hoops_HRRIP != TJUST_LEFT) {
			float			_hoops_SGSPH;
			int				_hoops_CHHCS = text->_hoops_ICI[_hoops_IIPCS] - text->_hoops_ICI[line];

			_hoops_SGSPH = _hoops_CCPCS[_hoops_IIPCS] - _hoops_CCPCS[line];
			_hoops_SGSPH += ti->_hoops_PCPAP * _hoops_CHHCS;

			if (_hoops_HRCIR->_hoops_HRRIP == TJUST_CENTER)
				_hoops_SGSPH *= 0.5f;

			ti->position += ti->path * _hoops_SGSPH;
		}

		/* _hoops_IGI _hoops_HPP _hoops_PGHGR */
		ti->_hoops_AGRI = _hoops_HPCH::_hoops_IPCH;

		if ((ti->_hoops_SIHSA.length = count) == 0) continue;	/* _hoops_ISAP _hoops_RAAP!? */

		if (ti->_hoops_RIPSP > 0 || line > 0) {
			int		_hoops_SHHCS = 0;

			if (!_hoops_HCPCS)
				ALLOC_ARRAY(_hoops_HCPCS, text->count, Karacter);

			if (!_hoops_ICPCS)
				ALLOC_ARRAY(_hoops_ICPCS, text->count, int);

			ti->_hoops_PPPSP = _hoops_ICPCS;
			ti->_hoops_SIHSA._hoops_IPPPP = _hoops_HCPCS;

			for (i=0; i<count; i++) {
				if (!BIT(ti->_hoops_HGCSR[_hoops_PPPSP].flags, TKIF_OMITTED)) {
					ti->_hoops_PPPSP[_hoops_SHHCS] = _hoops_PPPSP;
					ti->_hoops_SIHSA._hoops_IPPPP[_hoops_SHHCS] = *_hoops_IHSCP;
					_hoops_SHHCS++;
				}
				else
					ti->_hoops_SIHSA.length--;

				_hoops_PPPSP++;
				_hoops_IHSCP++;
			}
		}
		else {
			ti->_hoops_SIHSA._hoops_IPPPP = (Karacter alter *)_hoops_IHSCP;
			ti->_hoops_PPPSP = 0;
		}

		int		_hoops_GIHCS = 1, _hoops_RIHCS = 0;
		float	_hoops_PARPS, _hoops_AIHCS = 0.0;
		bool	_hoops_IA;

		Point	_hoops_PIHCS, _hoops_HIHCS, _hoops_ICHAI;

		if (_hoops_HRCIR->_hoops_HCPAP != 0.0) {
			_hoops_PARPS = HD_Compute_Generic_Size (nr,  _hoops_HRCIR->_hoops_PHP, _hoops_HRCIR->_hoops_GHGRP,
												 1.0f, (_hoops_HRCIR->transform == FT_FULL),  &_hoops_IA, false);

			if (_hoops_HRCIR->transform == FT_FULL) {
				if (_hoops_HRCIR->_hoops_GHGRP == GSU_POINTS || _hoops_HRCIR->_hoops_GHGRP == GSU_PIXELS || _hoops_HRCIR->_hoops_GHGRP == GSU_WRU) {
					_hoops_ICHAI.x = ti->_hoops_IPPSP.x + ti->_hoops_CHPSP.x * _hoops_PARPS * ti->scale.x / ((_hoops_HRCIR->_hoops_RGHAP == GSU_WRU || _hoops_HRCIR->_hoops_RGHAP == GSU_ORU) ? _hoops_HRCIR->font->_hoops_GRGGH : 1.0) ;
					_hoops_ICHAI.y = ti->_hoops_IPPSP.y + ti->_hoops_CHPSP.y * _hoops_PARPS * ti->scale.y / ((_hoops_HRCIR->_hoops_RGHAP == GSU_WRU || _hoops_HRCIR->_hoops_RGHAP == GSU_ORU) ? _hoops_HRCIR->font->_hoops_GRGGH : 1.0) ;
					_hoops_ICHAI.z = ti->_hoops_IPPSP.z + ti->_hoops_CHPSP.z * _hoops_PARPS * ti->scale.z / ((_hoops_HRCIR->_hoops_RGHAP == GSU_WRU || _hoops_HRCIR->_hoops_RGHAP == GSU_ORU) ? _hoops_HRCIR->font->_hoops_GRGGH : 1.0) ;

					if (_hoops_HRCIR->_hoops_RGHAP == GSU_ORU) {
						Point 	_hoops_IIHCS;
						Vector 	_hoops_CIHCS;
						Point 	_hoops_SIHCS, _hoops_GCHCS, _hoops_RCHCS;
						float 	_hoops_ACHCS, _hoops_PCHCS;

						_hoops_RIHCS = 1;

						_hoops_IIHCS = ti->_hoops_IPPSP + ti->_hoops_CHPSP * _hoops_HRCIR->_hoops_HCPAP;

						_hoops_CIHCS = _hoops_ICHAI - ti->_hoops_IPPSP;


						HI_Transform_Points_44 (1, &ti->_hoops_IPPSP, (const float*)_hoops_IHCR->matrix->data.elements, _hoops_IHCR->_hoops_CHCR, &_hoops_SIHCS, 0);
						HI_Transform_Points_44 (1, &_hoops_ICHAI, (const float*)_hoops_IHCR->matrix->data.elements, _hoops_IHCR->_hoops_CHCR, &_hoops_GCHCS, 0);
						HI_Transform_Points_44 (1, &_hoops_IIHCS, (const float*)_hoops_IHCR->matrix->data.elements, _hoops_IHCR->_hoops_CHCR, &_hoops_RCHCS, 0);


						_hoops_PCHCS = _hoops_SGIHR((_hoops_RCHCS.x - _hoops_SIHCS.x)*(_hoops_RCHCS.x - _hoops_SIHCS.x) +
										(_hoops_RCHCS.y - _hoops_SIHCS.y)*(_hoops_RCHCS.y - _hoops_SIHCS.y));

						_hoops_ACHCS = _hoops_SGIHR((_hoops_GCHCS.x - _hoops_SIHCS.x)*(_hoops_GCHCS.x - _hoops_SIHCS.x) +
										(_hoops_GCHCS.y - _hoops_SIHCS.y)*(_hoops_GCHCS.y - _hoops_SIHCS.y));


						_hoops_GIHCS = _hoops_ACHCS >= _hoops_PCHCS ? 1 : 0;

						_hoops_AIHCS = _hoops_CIHCS.length() / _hoops_HRCIR->font->_hoops_GRGGH;
					}
				}
				else if (_hoops_HRCIR->_hoops_GHGRP == GSU_ORU) {
					_hoops_ICHAI = ti->_hoops_IPPSP + ti->_hoops_CHPSP * _hoops_HRCIR->_hoops_PHP;

					if (_hoops_HRCIR->_hoops_RGHAP == GSU_ORU) {
						_hoops_RIHCS = true;
						_hoops_AIHCS = _hoops_HRCIR->_hoops_PHP;
					}
				}
				else {
					_hoops_ICHAI = ti->_hoops_IPPSP + ti->_hoops_CHPSP * _hoops_PARPS;
				}

				HI_Transform_Points_44 (1, &ti->_hoops_IPPSP, (const float*)_hoops_IHCR->matrix->data.elements, _hoops_IHCR->_hoops_CHCR, &_hoops_PIHCS, 0);
				HI_Transform_Points_44 (1, &_hoops_ICHAI, (const float*)_hoops_IHCR->matrix->data.elements, _hoops_IHCR->_hoops_CHCR, &_hoops_HIHCS, 0);

				if (!_hoops_RIHCS) {
					_hoops_AIHCS = _hoops_SGIHR((_hoops_HIHCS.x - _hoops_PIHCS.x)*(_hoops_HIHCS.x - _hoops_PIHCS.x) +
												(_hoops_HIHCS.y - _hoops_PIHCS.y)*(_hoops_HIHCS.y - _hoops_PIHCS.y));


				}

				if (_hoops_HRCIR->_hoops_RGHAP == GSU_ORU)
					_hoops_GIHCS = _hoops_AIHCS >= _hoops_HRCIR->_hoops_HCPAP ? 1 : 0;
				else
					_hoops_GIHCS = _hoops_AIHCS >= ti->_hoops_HCPAP ? 1 : 0;
			}
			else {
				_hoops_GIHCS = _hoops_PARPS >= ti->_hoops_HCPAP ? 1 : 0;
			}
		}

		if (_hoops_GIHCS || BIT(dc->flags, _hoops_CSHSR) || BIT(dc->flags, _hoops_IRSI)) {
			Point					point, _hoops_GIAHR;
			_hoops_PGCSR *	_hoops_HRHCS = null;
			float					_hoops_HCHCS = 0.0f;
			_hoops_CRCP *				_hoops_SRCP = text->owner;

			// _hoops_GGR _hoops_AGIR _hoops_SR _hoops_GGHP _hoops_ARI _hoops_AIH _hoops_IRS _hoops_CGRPR, _hoops_SR _hoops_HHGC _hoops_IS _hoops_PPSI _hoops_RH _hoops_PRCH *_hoops_IIH*
			_hoops_AAGSP *		_hoops_ICHCS = dc->_hoops_SPA;
			if (_hoops_ICHCS != dc->_hoops_ISAGR) do {
				_hoops_SRCP = _hoops_ICHCS->_hoops_CSAGR->owner;
			} while ((_hoops_ICHCS = _hoops_ICHCS->next) != dc->_hoops_ISAGR);

			point = _hoops_GIAHR = ti->position;

			for (i=0; i<ti->_hoops_SIHSA.length; i++) {
				_hoops_PGCSR *	_hoops_HGCSR;

				if (ti->_hoops_PPPSP)
					_hoops_PPPSP = ti->_hoops_PPPSP[i];
				else
					_hoops_PPPSP = i;

				_hoops_HGCSR = &ti->_hoops_HGCSR[_hoops_PPPSP];

				if (_hoops_HRHCS != null) {
					float				_hoops_CGSIR;

					/* _hoops_CCHCS _hoops_HRGR:
							1/2 _hoops_GSPR _hoops_CPCHR _hoops_HII _hoops_GSPR _hoops_GSSC-_hoops_RAAP _hoops_IS _hoops_GSSC-_hoops_RHCH
							_hoops_GRR _hoops_GSPR _hoops_SCHCS 1/2 _hoops_RGCI _hoops_GIRA _hoops_CPCHR _hoops_IGIAR _hoops_RH _hoops_CRAA
							_hoops_GII _hoops_IHH _hoops_GC _hoops_HRGR _hoops_GACC _hoops_IGIAR _hoops_RH _hoops_CRAA
							1/2 _hoops_GSPR _hoops_ISSC _hoops_HII _hoops_GSPR _hoops_GSSC-_hoops_RHCH _hoops_IS _hoops_GSSC-_hoops_RAAP
					*/
					if (_hoops_CGSPH) {
						/* _hoops_PIHGR _hoops_AGIR, _hoops_CPS _hoops_IHCI _hoops_IGIAR _hoops_PAPPI->_hoops_CRAA */
						_hoops_CGSIR = 0.5f * (_hoops_HRHCS->string.width - _hoops_HGCSR->string.width +
											 _hoops_HGCSR->_hoops_CGSIR + _hoops_HRHCS->_hoops_CGSIR) +
								   ti->_hoops_PCPAP;
						point.x += _hoops_CGSIR * ti->path.x;
						point.y += _hoops_CGSIR * ti->path.y;
					}
					else {
						/* _hoops_IGARI, _hoops_HPS _hoops_HAR _hoops_SSCC _hoops_RGCGA */
						_hoops_CGSIR = 0.5f * (_hoops_HRHCS->screen.width - _hoops_HGCSR->screen.width);
						if (_hoops_HRCIR->width_scale > 0.0f || ti->_hoops_GHPSP.x > 0) {
							point.x += _hoops_CGSIR * ti->_hoops_GHPSP.x;
							point.y += _hoops_CGSIR * ti->_hoops_GHPSP.y;
						}
						else {
							point.x -= _hoops_CGSIR * ti->_hoops_GHPSP.x;
							point.y -= _hoops_CGSIR * ti->_hoops_GHPSP.y;
						}

						_hoops_CGSIR = 0.5f * (_hoops_HGCSR->_hoops_CGSIR + _hoops_HRHCS->_hoops_CGSIR) + ti->_hoops_PCPAP;
						point += _hoops_CGSIR * ti->path;
					}
				}
				else if (!BIT (_hoops_HRCIR->_hoops_PRRIP, TALIGN_INSERTION_POINT)) {
					/* _hoops_SRS _hoops_GAS, _hoops_GHIR _hoops_IH _hoops_GII _hoops_HACH _hoops_RHCHH */
					if (_hoops_CGSPH) {
						/* _hoops_AGRP _hoops_PCRR _hoops_HII '_hoops_SHPR' _hoops_AHCRR _hoops_IS '_hoops_GSGR' _hoops_AHCRR */
						_hoops_GIAHR.x += _hoops_HGCSR->screen.x * _hoops_GCPCS.x - _hoops_HGCSR->screen.y * _hoops_GCPCS.y;
						_hoops_GIAHR.y += _hoops_HGCSR->screen.y * _hoops_GCPCS.x + _hoops_HGCSR->screen.x * _hoops_GCPCS.y;
						_hoops_GIAHR.x -= _hoops_HGCSR->string.x * ti->path.x - _hoops_HGCSR->string.y * ti->path.y;
						_hoops_GIAHR.y -= _hoops_HGCSR->string.y * ti->path.x + _hoops_HGCSR->string.x * ti->path.y;

						point.x = _hoops_GIAHR.x;
						point.y = _hoops_GIAHR.y;
					}
					else {
						/* _hoops_SRPA _hoops_CGRPR _hoops_PPSR _hoops_IH _hoops_GSHCS */
						float				_hoops_RSHCS, _hoops_ASHCS;

						if (_hoops_RCPCS.x >= 0.0f) {
							if (_hoops_RCPCS.y >= 0.0f) {
								_hoops_RSHCS = 0.0f;
								_hoops_ASHCS = _hoops_RCPCS.y * _hoops_HGCSR->height;
							}
							else {
								_hoops_RSHCS = _hoops_RCPCS.y * _hoops_HGCSR->string.width;
								_hoops_ASHCS = 0.0f;
							}
						}
						else {
							if (_hoops_RCPCS.y >= 0.0f) {
								_hoops_RSHCS = _hoops_RCPCS.x * _hoops_HGCSR->width;
								_hoops_ASHCS = _hoops_HGCSR->height;
							}
							else {
								_hoops_RSHCS = -_hoops_HGCSR->string.width;
								_hoops_ASHCS = -_hoops_RCPCS.x * _hoops_HGCSR->height;
							}
						}

						_hoops_GIAHR.x += _hoops_RSHCS * ti->path.x + _hoops_ASHCS * ti->path.y;
						_hoops_GIAHR.y += _hoops_RSHCS * ti->path.y - _hoops_ASHCS * ti->path.x;
					}
				}

				/* _hoops_CGRPR _hoops_PPSR _hoops_IH _hoops_GSGR _hoops_ARSIR */
				_hoops_HGCSR->point = point;

				if (_hoops_HGCSR->slant_extra != 0.0f) {
					point += ti->path * _hoops_HGCSR->slant_extra;
				}

				/* _hoops_HA _hoops_RIR-_hoops_GAS _hoops_RHCHH _hoops_SGS _hoops_GA'_hoops_RA _hoops_AGRP _hoops_GSGR _hoops_CCHCS */
				_hoops_HGCSR->position = point;

				if (BIT(_hoops_HGCSR->flags, _hoops_SAPSP)) {
					_hoops_HGCSR->position.x -= ti->path.y * _hoops_HGCSR->_hoops_HPGRP;
					_hoops_HGCSR->position.y += ti->path.x * _hoops_HGCSR->_hoops_HPGRP;
				}

				if (BIT(_hoops_HGCSR->flags, _hoops_GPPSP)) {
					_hoops_HGCSR->position.x += ti->path.x * _hoops_HGCSR->_hoops_PPGRP;
					_hoops_HGCSR->position.y += ti->path.y * _hoops_HGCSR->_hoops_PPGRP;
				}

				/* _hoops_AGRP _hoops_HII _hoops_GSSC-_hoops_RAAP _hoops_IIGR _hoops_RH _hoops_GAS '_hoops_AHCRR' _hoops_IS _hoops_GSSC-_hoops_RAAP _hoops_IIGR _hoops_RH _hoops_RPHH */
				if (_hoops_CGSPH || BIT (_hoops_HRCIR->_hoops_PRRIP, TALIGN_INSERTION_POINT)) {
					_hoops_HGCSR->position.x += _hoops_HGCSR->string.x * ti->path.x - _hoops_HGCSR->string.y * ti->path.y;
					_hoops_HGCSR->position.y += _hoops_HGCSR->string.y * ti->path.x + _hoops_HGCSR->string.x * ti->path.y;
				}
				else {
					_hoops_HGCSR->position.x += _hoops_HGCSR->screen.x * _hoops_GCPCS.x - _hoops_HGCSR->screen.y * _hoops_GCPCS.y;
					_hoops_HGCSR->position.y += _hoops_HGCSR->screen.y * _hoops_GCPCS.x + _hoops_HGCSR->screen.x * _hoops_GCPCS.y;
				}

				if (_hoops_HRCIR->transform == FT_NONE) {
					if (!_hoops_SAPCS (_hoops_IHCR, _hoops_SGRA->_hoops_SCIH, _hoops_HGCSR->position,
									_hoops_HGCSR->screen.width, _hoops_HGCSR->screen.height))
						_hoops_HGCSR->flags |= _hoops_IAPSP;
				}
				else if (_hoops_HRCIR->transform == FT_FULL) {
					Point			box[4];
					DC_Point		_hoops_PAGR[4];
					float			ws[4];
					_hoops_GRCAR		_hoops_ARCAR[4];
					int				j;

					for (j=0; j<4;j++) {
						box[j] = _hoops_HGCSR->position;
						if (BIT (j, 1))
							box[j].x += _hoops_HGCSR->screen.width-1;
						if (BIT (j, 2))
							box[j].y += _hoops_HGCSR->screen.height-1;

						box[j].x = (box[j].x - ti->_hoops_CSAGR.x) * ti->scale.x;
						box[j].y = (box[j].y - ti->_hoops_CSAGR.y) * ti->scale.y;
						box[j].z = (box[j].z - ti->_hoops_CSAGR.z) * ti->scale.z;
					}
					if (text->region == null) {
						for (j=0; j<4;j++) {
							box[j].x += text->_hoops_CSAI.x;
							box[j].y += text->_hoops_CSAI.y;
							box[j].z += text->_hoops_CSAI.z;
						}
					}

					if (_hoops_SSPCS) {
						Point const *		_hoops_PSHCS = box;
						Point				_hoops_SIRRC[4];

						if (_hoops_HSPCS != null) {
							HI_Transform_Points_43 (4, box, _hoops_HSPCS, _hoops_SIRRC);
							_hoops_PSHCS = _hoops_SIRRC;
						}
						_hoops_PGRCA(text)->bounding.Merge (4, _hoops_PSHCS);
					}

					if (HD_Acquire_Clip_Points (nr, null, 4, box, _hoops_PAGR, ws, _hoops_ARCAR) == 0)
						_hoops_HGCSR->flags |= _hoops_IAPSP;
				}

				_hoops_HRHCS = _hoops_HGCSR;
				_hoops_HCHCS = _hoops_HRHCS->nr->_hoops_SISI->rotation;

				if (_hoops_HGCSR->nr == nr)
					_hoops_HGCSR->nr = null;
			}

			if (_hoops_SSPCS && _hoops_SRCP != null) {
#if 0			// _hoops_RPGP _hoops_RRGR _hoops_IS "_hoops_PRPIS" _hoops_HCGR _hoops_IASC _hoops_IRS _hoops_RSCA
				float			depth = 0.01f * text->bounding->sphere.radius;

				if (text->bounding->cuboid.max.z - text->bounding->cuboid.min.z < 1.99f * depth) {
					float		_hoops_SPGIR = text->bounding->sphere.center.z;

					_hoops_PGRCA(text)->bounding->cuboid.min.z = _hoops_SPGIR - depth;
					_hoops_PGRCA(text)->bounding->cuboid.max.z = _hoops_SPGIR + depth;
				}
#endif
				HI_Propagate_Bounding (dc->_hoops_RIGC, _hoops_SRCP, text->bounding, null);
				if (_hoops_CPPCS(nr,text)) {
					_hoops_RCCA(_hoops_IIRGH)++;
					goto _hoops_PP;
				}
			}

			ti->flags |= _hoops_AAPSP;

			/* _hoops_RH _hoops_SHISR _hoops_PGSA _hoops_CRAA */
			_hoops_CGIGH (nr, ti);

			/* _hoops_GGCR _hoops_III _hoops_HSHCS */
			if (_hoops_HRCIR->_hoops_SCRIP || _hoops_HRCIR->_hoops_GSRIP || _hoops_HRCIR->_hoops_RSRIP) {
				DC_Point				_hoops_PICHR[6];
				int						current = 0;
				int						in_use = 0;
				Vector				_hoops_HAHCR;

				_hoops_HAHCR.x = -ti->path.y;
				_hoops_HAHCR.y =  ti->path.x;
				_hoops_HAHCR.z = 0.0f;
				HI_Normalize (&_hoops_HAHCR);
				_hoops_HAHCR.x *= _hoops_HRCIR->font->_hoops_ISISR;
				_hoops_HAHCR.y *= _hoops_HRCIR->font->_hoops_ISISR;

				_hoops_PICHR[0].x = _hoops_GIAHR.x;
				_hoops_PICHR[0].y = _hoops_GIAHR.y;
				_hoops_PICHR[0].z = _hoops_GIAHR.z;
				_hoops_PICHR[1].x = _hoops_PICHR[0].x + _hoops_HHPSP[line].x;
				_hoops_PICHR[1].y = _hoops_PICHR[0].y + _hoops_HHPSP[line].y;
				_hoops_PICHR[1].z = _hoops_PICHR[0].z + _hoops_HHPSP[line].z;

				/* _hoops_ARP _hoops_IRS _hoops_IGRH _hoops_GSSC _hoops_HSAR _hoops_RHPSP */
				_hoops_PICHR[0].x -= 0.2f * _hoops_HAHCR.x;
				_hoops_PICHR[0].y -= 0.2f * _hoops_HAHCR.y;
				_hoops_PICHR[1].x -= 0.2f * _hoops_HAHCR.x;
				_hoops_PICHR[1].y -= 0.2f * _hoops_HAHCR.y;

				if (_hoops_HRCIR->_hoops_SCRIP)
					in_use += 2;

				/* _hoops_PARRH _hoops_GH _hoops_IS _hoops_IRGP */
				if (in_use > current) {
					_hoops_AIGA (&_hoops_PICHR[current], 2, DC_Point, &_hoops_PICHR[in_use]);
					current += 2;
				}
				_hoops_PICHR[current+0].x += 0.7f * _hoops_HAHCR.x;
				_hoops_PICHR[current+0].y += 0.7f * _hoops_HAHCR.y;
				_hoops_PICHR[current+1].x += 0.7f * _hoops_HAHCR.x;
				_hoops_PICHR[current+1].y += 0.7f * _hoops_HAHCR.y;

				if (_hoops_HRCIR->_hoops_GSRIP)
					in_use += 2;

				/* _hoops_PARRH _hoops_IRS _hoops_IGRH _hoops_ARRS _hoops_RH _hoops_SCIA */
				if (in_use > current) {
					_hoops_AIGA (&_hoops_PICHR[current], 2, DC_Point, &_hoops_PICHR[in_use]);
					current += 2;
				}
				_hoops_PICHR[current+0].x += 0.7f * _hoops_HAHCR.x;
				_hoops_PICHR[current+0].y += 0.7f * _hoops_HAHCR.y;
				_hoops_PICHR[current+1].x += 0.7f * _hoops_HAHCR.x;
				_hoops_PICHR[current+1].y += 0.7f * _hoops_HAHCR.y;

				if (_hoops_HRCIR->_hoops_RSRIP)
					in_use += 2;

				Net_Rendition			_hoops_CRAI = nr;

				if (_hoops_HRCIR->_hoops_ASRIP && _hoops_HRCIR->font->family->_hoops_RRCSR != _hoops_ARCSR)
					_hoops_CRAI.Modify()->_hoops_AHP.Modify()->weight = (int)(_hoops_HRCIR->font->_hoops_ISISR * 0.05f);

				/* _hoops_HRPP _hoops_IS _hoops_PGSA, _hoops_HIH _hoops_GHCA _hoops_RRP _hoops_IS _hoops_SHH _hoops_CHIAR */
				if (_hoops_HRCIR->transform == FT_FULL) {
					Polyline *			pl;
					_hoops_ISGI	_hoops_RSIPA;
					_hoops_RPRA alter *	m;

					// _hoops_GIRRR _hoops_HRGR _hoops_HAICR' = (_hoops_HAICR - _hoops_CGRPR) * _hoops_CSRA + _hoops_ISHCS
					HI_Figure_Scale_Matrix (ti->scale.x, ti->scale.y, ti->scale.z, &_hoops_RSIPA.matrix);
					m = (_hoops_RPRA alter *)_hoops_RSIPA.matrix.elements;
					m[3][0] = text->_hoops_CSAI.x - ti->scale.x * ti->_hoops_CSAGR.x;
					m[3][1] = text->_hoops_CSAI.y - ti->scale.y * ti->_hoops_CSAGR.y;
					m[3][2] = text->_hoops_CSAI.z - ti->scale.z * ti->_hoops_CSAGR.z;
					_hoops_RSIPA.matrix._hoops_RAGR |= _hoops_PRICR;
					if (m[3][2] != 0.0f)
						_hoops_RSIPA.matrix._hoops_RAGR |= _hoops_ASPCR;

					HD_Downwind_Modelling_Matrix (_hoops_CRAI, (Attribute const *)&_hoops_RSIPA);


					ZALLOC (pl, Polyline);
					pl->type = _hoops_IIIP;
					pl->_hoops_HIHI = 1;
					pl->_hoops_RRHH |= _hoops_PCPIR;

					pl->points = _hoops_PICHR;
					pl->count = -in_use;


					_hoops_CCAIP (_hoops_CRAI, pl);

					_hoops_HPRH (pl);
				}
				else
					_hoops_SRPIP (_hoops_CRAI, -in_use, _hoops_PICHR);
			}
		}
		else if (_hoops_HRCIR->_hoops_SGHAP != _hoops_HGHAP) {
			/* _hoops_IAPIP _hoops_RH _hoops_HCGR */
			Net_Rendition			_hoops_SSGS = nr;
			Point					box[6];

			if (_hoops_HRCIR->_hoops_SGHAP == _hoops_CGHAP) {
				_hoops_SIHHP alter *		up;
				unsigned short					value;
				unsigned short const *			_hoops_HAPAR;
				unsigned char alter *			_hoops_SCGCR;

				_hoops_CIGA alter &			_hoops_SIGA = _hoops_SSGS.Modify()->_hoops_IHA.Modify();

				_hoops_SSGS->_hoops_CPP.Modify()->_hoops_PRH.style = _hoops_GCPI;

				_hoops_SIGA->_hoops_CHA->_hoops_IRIR = 0.5f;

				if ((up = (_hoops_SIHHP alter *)_hoops_SIGA->_hoops_PGPH) != null) {
					if (_hoops_ISAI (up) == 0) {
						if (up->pattern != null)
							FREE_ARRAY (up->pattern, up->width * up->height,
										unsigned char);

						FREE (up, _hoops_SIHHP);
					}
				}

				ALLOC (up, _hoops_SIHHP);
				_hoops_ICAI (up);
				up->_hoops_CPA = _hoops_SSGS->_hoops_SRA->_hoops_GCHHP();
				up->width = up->height = 8;
				up->_hoops_RCHHP = true;
				up->_hoops_ACHHP = UPAT_NO_CONTRAST;
				ALLOC_ARRAY (_hoops_SCGCR, 64, unsigned char);
				up->pattern = _hoops_SCGCR;

				value = (unsigned short)(0.5f * 0x0000FFFF);
				_hoops_HAPAR = &HOOPS_READ_ONLY._hoops_CHGCR[0][0];
				for (i=0; i<64; i++) {
					*_hoops_SCGCR++ = (value < *_hoops_HAPAR++) ? 1 : 0;	/* 1 _hoops_HRGR _hoops_ASPA _hoops_IS _hoops_HSGR */
				}
				up->stipple = 32;

				_hoops_SIGA->_hoops_PGPH = up;
				_hoops_SIGA->pattern = FP_USER_DEFINED;
				_hoops_SIGA->color = _hoops_HRCIR->color;
			}


			if (BIT (_hoops_HRCIR->transform, FT_POSITION_ONLY)) {
				Vector		_hoops_CHPSP;

				_hoops_CHPSP.x = ti->_hoops_ICGH * ti->_hoops_CHPSP.x;
				_hoops_CHPSP.y = ti->_hoops_ICGH * ti->_hoops_CHPSP.y;

				_hoops_CHPSP.z = 0;

				for (i=0; i<count; ++i) {
					Vector				_hoops_GAGCR;
					Point const *		p;
					float					width;

					width = HD_Compute_Character_Width (_hoops_SSGS, ti, i);

					_hoops_GAGCR.x = ti->_hoops_GHPSP.x * width;
					_hoops_GAGCR.y = ti->_hoops_GHPSP.y * width;
					_hoops_GAGCR.z = 0;

					p = HD_Compute_Character_Position (_hoops_SSGS, ti, i);
					p = HD_Compute_Transformed_Text_Position (_hoops_SSGS, ti, p);

					box[0].x = p->x;
					box[0].y = p->y;
					box[0].z = p->z;
					box[1].x = box[0].x + _hoops_GAGCR.x;
					box[1].y = box[0].y + _hoops_GAGCR.y;
					box[1].z = box[0].z + _hoops_GAGCR.z;
					box[2].x = box[0].x + _hoops_GAGCR.x + _hoops_CHPSP.x;
					box[2].y = box[0].y + _hoops_GAGCR.y + _hoops_CHPSP.y;
					box[2].z = box[0].z + _hoops_GAGCR.z + _hoops_CHPSP.z;
					box[3].x = box[0].x + _hoops_CHPSP.x;
					box[3].y = box[0].y + _hoops_CHPSP.y;
					box[3].z = box[0].z + _hoops_CHPSP.z;

					if (_hoops_HRCIR->_hoops_SGHAP == _hoops_IGHAP) {
						box[4].x = box[0].x;
						box[4].y = box[0].y;
						box[4].z = box[0].z;
						box[5].x = box[2].x;
						box[5].y = box[2].y;
						box[5].z = box[2].z;

						_hoops_SRPIP (_hoops_SSGS, 6, (DC_Point *)box);

						box[2].x = box[3].x;
						box[2].y = box[3].y;
						box[2].z = box[3].z;

						_hoops_SRPIP (_hoops_SSGS, 2, (DC_Point *)&box[1]);
					}
					else {

						_hoops_HRPIP (_hoops_SSGS, 4, (DC_Point *)box);

						Vector _hoops_SAIAR, target;
						float _hoops_ISSPA = 0.0;
						target.x = nr->transform_rendition->_hoops_SPH->_hoops_IIPCR.x;
						target.y = nr->transform_rendition->_hoops_SPH->_hoops_IIPCR.y;
						target.z = nr->transform_rendition->_hoops_SPH->_hoops_IIPCR.z;
						
						Vector _hoops_CSHCS;
						_hoops_CSHCS.x = box[1].x - box[0].x;
						_hoops_CSHCS.y = box[1].y - box[0].y;
						_hoops_CSHCS.z = box[1].z - box[0].z;

						Vector _hoops_HAHCR;
						_hoops_HAHCR.x = box[2].x - box[1].x;
						_hoops_HAHCR.y = box[2].y - box[1].y;
						_hoops_HAHCR.z = box[2].z - box[1].z;


						HI_Cross_Product(&_hoops_CSHCS, &_hoops_HAHCR, &_hoops_SAIAR);
						_hoops_ISSPA = HI_Compute_Dot_Product(&target, &_hoops_SAIAR);
						if(Abs(_hoops_ISSPA) <= 0.1)
							_hoops_SRPIP (_hoops_SSGS, 2, (DC_Point *)&box[0]);
						else
							_hoops_HRPIP (_hoops_SSGS, 4, (DC_Point *)box);
					}
				}
			}
			else {
				Vector				_hoops_SSHCS;
				Vector				_hoops_GGICS;
				bool				draw = true;

				box[0].x = ti->position.x;
				box[0].y = ti->position.y;
				box[0].z = ti->position.z;
				box[1].x = box[0].x + ti->_hoops_HHPSP.x;
				box[1].y = box[0].y + ti->_hoops_HHPSP.y;
				box[1].z = box[0].z + ti->_hoops_HHPSP.z;
				box[2].x = box[1].x + ti->_hoops_ICGH * ti->_hoops_CHPSP.x;
				box[2].y = box[1].y + ti->_hoops_ICGH * ti->_hoops_CHPSP.y;
				box[2].z = box[1].z + ti->_hoops_ICGH * ti->_hoops_CHPSP.z;
				box[3].x = box[0].x + ti->_hoops_ICGH * ti->_hoops_CHPSP.x;
				box[3].y = box[0].y + ti->_hoops_ICGH * ti->_hoops_CHPSP.y;
				box[3].z = box[0].z + ti->_hoops_ICGH * ti->_hoops_CHPSP.z;
				box[4].x = box[0].x;
				box[4].y = box[0].y;
				box[4].z = box[0].z;

				if (_hoops_HRCIR->transform == FT_FULL) {
					for (i=0; i<5; ++i) {
						Point const *		p;

						p = HD_Compute_Transformed_Text_Position (_hoops_SSGS, ti, &box[i]);
						if (p == null) {
							draw = false;
							break;
						}
						box[i].x = p->x;
						box[i].y = p->y;
						box[i].z = p->z;
					}
				}

				if (draw) {
					if (_hoops_HRCIR->_hoops_SGHAP == _hoops_IGHAP) {
						_hoops_SRPIP (_hoops_SSGS, 5, (DC_Point *)box);

						_hoops_SSHCS.x = 0.25f * (box[3].x - box[0].x);
						_hoops_SSHCS.y = 0.25f * (box[3].y - box[0].y);
						_hoops_SSHCS.z = 0.25f * (box[3].z - box[0].z);
						_hoops_GGICS.x = 0.25f * (box[2].x - box[1].x);
						_hoops_GGICS.y = 0.25f * (box[2].y - box[1].y);
						_hoops_GGICS.z = 0.25f * (box[2].z - box[1].z);

						for (i=0; i<3; i++) {
							box[0].x += _hoops_SSHCS.x;
							box[0].y += _hoops_SSHCS.y;
							box[0].z += _hoops_SSHCS.z;

							box[1].x += _hoops_GGICS.x;
							box[1].y += _hoops_GGICS.y;
							box[1].z += _hoops_GGICS.z;

							_hoops_SRPIP (_hoops_SSGS, 2, (DC_Point *)box);
						}
					}
					else {
						_hoops_HRPIP (_hoops_SSGS, 4, (DC_Point *)box);

						Vector _hoops_SAIAR, target;
						float _hoops_ISSPA = 0.0;
						target.x = nr->transform_rendition->_hoops_SPH->_hoops_IIPCR.x;
						target.y = nr->transform_rendition->_hoops_SPH->_hoops_IIPCR.y;
						target.z = nr->transform_rendition->_hoops_SPH->_hoops_IIPCR.z;
						
						Vector _hoops_CSHCS;
						_hoops_CSHCS.x = box[1].x - box[0].x;
						_hoops_CSHCS.y = box[1].y - box[0].y;
						_hoops_CSHCS.z = box[1].z - box[0].z;

						Vector _hoops_HAHCR;
						_hoops_HAHCR.x = box[2].x - box[1].x;
						_hoops_HAHCR.y = box[2].y - box[1].y;
						_hoops_HAHCR.z = box[2].z - box[1].z;


						HI_Cross_Product(&_hoops_CSHCS, &_hoops_HAHCR, &_hoops_SAIAR);
						_hoops_ISSPA = HI_Compute_Dot_Product(&target, &_hoops_SAIAR);
						if(Abs(_hoops_ISSPA) <= 0.1)
							_hoops_SRPIP (_hoops_SSGS, 2, (DC_Point *)&box[0]);
						else
							_hoops_HRPIP (_hoops_SSGS, 4, (DC_Point *)box);
					}
				}
			}
		}
	}

	if (_hoops_ASPCS >= ti->_hoops_HCPAP && text->_hoops_AAPGR != null) {
		_hoops_PIGPR const	*sc = text->_hoops_AAPGR;
		Point				point;

		do if (!BIT (sc->_hoops_RRHH, _hoops_HGAGR)) {
			int		_hoops_PPPSP = text->_hoops_RIHIR[sc->row] - text->karacters + sc->column;

			if (sc->column >= text->_hoops_ICI[sc->row]) {
				float	_hoops_RGICS;

				if (HD_Measure_Characters (nr, 1, &_hoops_PPPCS, encoding, &_hoops_RGICS))
					continue;

				if (text->_hoops_ICI[sc->row] == 0) {
					point.x = _hoops_RHPCS.x + sc->row * ti->_hoops_PHPSP.x + 0.5f * _hoops_RGICS * ti->path.x;
					point.y = _hoops_RHPCS.y + sc->row * ti->_hoops_PHPSP.y + 0.5f * _hoops_RGICS * ti->path.y;
					point.z = _hoops_RHPCS.z + sc->row * ti->_hoops_PHPSP.z;
				}
				else {
					_hoops_PPPSP--;

					if (BIT(ti->_hoops_HGCSR[_hoops_PPPSP].flags, TKIF_OMITTED))
						continue;

					point = ti->_hoops_HGCSR[_hoops_PPPSP].point;

					point.x += (ti->_hoops_HGCSR[_hoops_PPPSP].screen.width + 0.5f * _hoops_RGICS) * ti->path.x;
					point.y += (ti->_hoops_HGCSR[_hoops_PPPSP].screen.width + 0.5f * _hoops_RGICS) * ti->path.y;
				}
			}
			else {
				if (BIT(ti->_hoops_HGCSR[_hoops_PPPSP].flags, TKIF_OMITTED))
					continue;

				point = ti->_hoops_HGCSR[_hoops_PPPSP].point;

				point.x += 0.5f * ti->_hoops_HGCSR[_hoops_PPPSP].screen.width * ti->path.x;
				point.y += 0.5f * ti->_hoops_HGCSR[_hoops_PPPSP].screen.width * ti->path.y;
			}

			_hoops_HPPCS (nr, sc, &point);
		} _hoops_RGGA ((sc = (_hoops_PIGPR const *)sc->next) == null);
	}

_hoops_PP:
	dc->_hoops_IPCI->mask = _hoops_HPCI;

	_hoops_APAI (HOOPS_WORLD->_hoops_HPHGI);

	if (_hoops_CCPCS != null) {
		FREE_ARRAY (_hoops_CCPCS, text->_hoops_PICHR, float);
		FREE_ARRAY (_hoops_SCPCS, text->_hoops_PICHR, float);
		FREE_ARRAY (_hoops_GSPCS, text->_hoops_PICHR, float);
		FREE_ARRAY (_hoops_HHPSP, text->_hoops_PICHR, Vector);
	}

	if (_hoops_HCPCS)
		FREE_ARRAY(_hoops_HCPCS, text->count, Karacter);

	if (_hoops_ICPCS)
		FREE_ARRAY(_hoops_ICPCS, text->count, int);

	if (ti) {
		/* _hoops_AGICS _hoops_HGGPR _hoops_GAR _hoops_PGICS _hoops_ARRS */
		ti->_hoops_PPPSP = null;
		/* _hoops_HGICS _hoops_HRGR _hoops_IRGH */
		_hoops_IHAGI(ti->_hoops_SIHSA);
		HI_Free_Text_Info (ti);
	}
}





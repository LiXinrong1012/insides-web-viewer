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
 * $Id: obf_tmp.txt 1.186 2010-12-10 03:32:35 covey Exp $
 */


#include "hoops.h"
#include "database.h"
#include "patterns.h"
#include "driver.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


local void _hoops_PRRSS (
	Net_Rendition const &			nr,
	_hoops_HACC const *					text,
	Point const *					point,
	int								count,
	Karacter const *				_hoops_IHSCP,
	_hoops_PGCSR *			_hoops_HGCSR) {
	Display_Context const *			dc = nr->_hoops_SRA;
	int								_hoops_IIICS = dc->_hoops_PGCC._hoops_PIHSR;
	_hoops_HHCR const &		_hoops_IHCR = nr->transform_rendition;
	_hoops_HHRA const *					_hoops_SPH = _hoops_IHCR->_hoops_SPH;
	Point							_hoops_AISHS;
	RGB const *						_hoops_PRHAC = &nr->_hoops_SAIR->_hoops_GRAIP;
	float							hither, yon, _hoops_CRIR, _hoops_SIRH, _hoops_PISHS;
	_hoops_GCIR const &	_hoops_RCIR = nr->_hoops_CPP;
	RGB								_hoops_SGIIS;
	RGBAS32							color;

	_hoops_SGIIS = nr->_hoops_SISI->_hoops_CHA->_hoops_CSHR;
	color = _hoops_SGIIS;

	{
		_hoops_RPRA const *			elements = nr->transform_rendition->_hoops_IPH->data.elements;

		_hoops_AISHS.x = _hoops_HPRA (elements, text->_hoops_CSAI) - _hoops_SPH->position.x;
		_hoops_AISHS.y = _hoops_IPRA (elements, text->_hoops_CSAI) - _hoops_SPH->position.y;
		_hoops_AISHS.z = _hoops_CPRA (elements, text->_hoops_CSAI) - _hoops_SPH->position.z;
	}

	hither = _hoops_RCIR->_hoops_CRIR.hither;
	yon	   = _hoops_RCIR->_hoops_CRIR.yon;

	_hoops_PISHS = _hoops_AISHS.x * _hoops_AISHS.x + _hoops_AISHS.y * _hoops_AISHS.y + _hoops_AISHS.z * _hoops_AISHS.z;

	if (_hoops_PISHS <= hither*hither)
		_hoops_SIRH	  = 1.0f;
	else if (_hoops_PISHS >= yon*yon)
		_hoops_SIRH	  = 0.0f;
	else
		_hoops_SIRH = (_hoops_SGIHR(_hoops_PISHS) - yon) / (hither - yon);

	_hoops_CRIR = 255.0f * (1.0f - _hoops_SIRH);

	color.r = (unsigned char)(_hoops_SIRH * color.r + _hoops_CRIR * _hoops_PRHAC->red);
	color.g = (unsigned char)(_hoops_SIRH * color.g + _hoops_CRIR * _hoops_PRHAC->green);
	color.b = (unsigned char)(_hoops_SIRH * color.b + _hoops_CRIR * _hoops_PRHAC->blue);
	color.a = _hoops_GPGCR;

	Net_Rendition					_hoops_RHICP = nr;
	_hoops_IGCSR alter &			_hoops_HRRSS = _hoops_RHICP.Modify()->_hoops_SISI.Modify();
	_hoops_HRRSS->_hoops_RGIHP = null;

	if (BIT (nr->current, _hoops_RSSHP) ||
		dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) {
		/* _hoops_HGPSA _hoops_HIIC! */
		((Display_Context alter *)dc)->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;

		_hoops_HRRSS->color = color;
	}
	else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
		_hoops_GARSR		colors[4+1];
		int				_hoops_AHHIR[3+1];

		/* _hoops_SGH "_hoops_AAH" _hoops_HAIR */
		(void)HD_Find_Dither_Pattern (nr, &color, colors, _hoops_AHHIR);
		_hoops_HRRSS->color._hoops_PGGCR = colors[0];
	}
	else /* _hoops_AIHHP */ {
		RGB				rgb = color;

		_hoops_HRRSS->color = _hoops_CAHSR::_hoops_SAHSR;
		_hoops_HRRSS->color._hoops_PIHHP = (_hoops_HIHHP)(rgb._hoops_CPIR() *
											   ((float)dc->_hoops_PGCC._hoops_PCHSR - 0.01f));
	}

	_hoops_ASIGH (_hoops_RHICP, text, point, count, _hoops_IHSCP, _hoops_HGCSR);

	((Display_Context alter *)dc)->_hoops_PGCC._hoops_PIHSR = _hoops_IIICS;
}

/* _hoops_RH _hoops_CIHH _hoops_RPGP _hoops_IH _hoops_PCCP _hoops_CAPCS _hoops_GAS _hoops_AHCRR... */
#define _hoops_SAPCS(_hoops_IHCR, _hoops_GPHH, x, y, z, width, height)				\
	  ((x)+((width)-1) >= _hoops_GPHH.left &&							\
	   (x)			   <= _hoops_GPHH.right &&							\
	   (y)+((height)-1) >= _hoops_GPHH.bottom &&						\
	   (y)				<= _hoops_GPHH.top &&							\
	   /* _hoops_GPPCS _hoops_HRGR _hoops_PRRHA! (_hoops_SSH) >= 0 && */						\
	   (!BIT ((_hoops_IHCR)->flags, _hoops_CSP) ||				\
		HD_Box_Within_Cutting_Planes (_hoops_IHCR, (x), (y)+(height)-1,	\
										  (z), (int)(width), (int)(height))))

local void _hoops_IRRSS (
	Net_Rendition const &		nr,
	Text_Info const *			ti,
	Point const *				start,
	Karacter const *			_hoops_IHSCP,
	_hoops_PGCSR *		_hoops_HGCSR) {
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HACC const *				text = ti->text;
	Vector const *				scale = &ti->scale;
	Point const *				_hoops_RRPPI = &ti->_hoops_IPPSP;
	Point const *				ref = &ti->_hoops_CSAGR;
	Point const *				_hoops_CRIPA = &ti->_hoops_HPPSP;
	Point						_hoops_CSAI;
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	int							_hoops_CRRSS;
	_hoops_PACIR			_hoops_GPHH;

	int	_hoops_SRRSS = (int)(_hoops_SGRA->_hoops_HHCAR.right - _hoops_SGRA->_hoops_SCIH.right);
	if (_hoops_SRRSS < 0)
		_hoops_SRRSS = 0;	/* _hoops_SAHR _hoops_GGR _hoops_AGIR */

	if (_hoops_HRCIR->transform != FT_FULL)
		_hoops_CRRSS = (int) _hoops_HRCIR->font->_hoops_IGGGH;
	else
		_hoops_CRRSS = 0;

	if (_hoops_CRRSS > _hoops_SRRSS) {
		float			delta;

		delta = _hoops_CRRSS - _hoops_SRRSS + 10.499f;

		_hoops_GPHH = _hoops_SGRA->_hoops_HHCAR;
		_hoops_GPHH._hoops_IACHA(delta);
	}
	else {
		_hoops_GPHH = _hoops_SGRA->_hoops_HHCAR;
	}

	/* _hoops_SICR _hoops_SCH _hoops_HII _hoops_SHPR _hoops_GC _hoops_ISSC _hoops_IS _hoops_GCRAC-_hoops_SARA _hoops_GC */
	_hoops_CSAI.x = _hoops_RRPPI->x + (start->x - (ref->x+_hoops_CRIPA->x)) * scale->x;
	_hoops_CSAI.y = _hoops_RRPPI->y + (start->y - (ref->y+_hoops_CRIPA->y)) * scale->y;
	_hoops_CSAI.z = _hoops_RRPPI->z + (start->z - (ref->z+_hoops_CRIPA->z)) * scale->z;

	if (_hoops_HRCIR->transform == FT_FULL) {
		Font_Instance const	*		font = _hoops_HRCIR->font;

		_hoops_CSAI.x += _hoops_CRIPA->x * scale->x;
		_hoops_CSAI.y += _hoops_CRIPA->y * scale->y;
		_hoops_CSAI.z += _hoops_CRIPA->z * scale->z;

		if (dc->_hoops_IGHGH != null) {
			/* "_hoops_GARSS" _hoops_HRGR _hoops_IS _hoops_RARSS _hoops_IRS _hoops_RIH-_hoops_RHIR _hoops_IS _hoops_AARSS */
			dc->_hoops_IGHGH->_hoops_RHGGH = text;
			dc->_hoops_IGHGH->_hoops_PHGGH = _hoops_HGCSR->offset;
		}

		(*font->_hoops_SRCSR)(nr, font, &_hoops_CSAI, 1, _hoops_IHSCP, scale);

		if (dc->_hoops_IGHGH != null) {
			/* "_hoops_GARSS" _hoops_HRGR _hoops_IS _hoops_RARSS _hoops_IRS _hoops_RIH-_hoops_RHIR _hoops_IS _hoops_AARSS */
			dc->_hoops_IGHGH->_hoops_RHGGH = null;
			dc->_hoops_IGHGH->_hoops_PHGGH = 0;
		}
	}
	else {
		_hoops_HHCR const &		_hoops_IHCR = nr->transform_rendition;
		_hoops_RPRA const *				elements = _hoops_IHCR->matrix->data.elements;
		Point							point = _hoops_HPCH::_hoops_IPCH;

		/* _hoops_AA _hoops_IRS _hoops_GPICR _hoops_GGAIP */

		switch (_hoops_IHCR->_hoops_HGSC) {
			case _hoops_SIPHP: {
				point.x = _hoops_CSAI.x;
				point.y = _hoops_CSAI.y;
				point.z = 0.0f;
			}			break;

			case _hoops_CIPHP: {
				point.x = _hoops_PRPPI (elements, _hoops_CSAI);
				point.y = _hoops_HRPPI (elements, _hoops_CSAI);
				point.z = 0.0f;
			}	break;

			case _hoops_PCPHP: {
				point.x = _hoops_HPRA (elements, _hoops_CSAI);
				point.y = _hoops_IPRA (elements, _hoops_CSAI);
				point.z = 0.0f;
			}	break;

			case _hoops_RCPHP: {
				float			w;

				w = _hoops_PHCP (elements, _hoops_CSAI);
				if (w <= _hoops_IHCR->_hoops_CHCR)
					return;

				point.x = _hoops_HPRA (elements, _hoops_CSAI) / w;
				point.y = _hoops_IPRA (elements, _hoops_CSAI) / w;
				point.z = 0.0f;
			}	break;

			case _hoops_ACPHP: {
				point.x = _hoops_HPRA (elements, _hoops_CSAI);
				point.y = _hoops_IPRA (elements, _hoops_CSAI);
				point.z = _hoops_CPRA (elements, _hoops_CSAI);
				point.z = _hoops_IGSC (point.z, _hoops_IHCR);
			}	break;

			case _hoops_GCPHP: {
				float			w;

				w = _hoops_PHCP (elements, _hoops_CSAI);
				if (w <= _hoops_IHCR->_hoops_CHCR)
					return;

				point.x = _hoops_HPRA (elements, _hoops_CSAI) / w;
				point.y = _hoops_IPRA (elements, _hoops_CSAI) / w;
				point.z = _hoops_CPRA (elements, _hoops_CSAI) / w;
				point.z = _hoops_IGSC (point.z, _hoops_IHCR);
			}	break;
		}

		point.x += _hoops_CRIPA->x;
		point.y += _hoops_CRIPA->y;
		point.z += _hoops_CRIPA->z;

		/* _hoops_IIS'_hoops_GRI _hoops_HPPR _hoops_ASCA _hoops_SCH _hoops_HA */
		if (_hoops_SAPCS (_hoops_IHCR, _hoops_GPHH, point.x, point.y, point.z, 1, 1)) {
			if (BIT (nr->_hoops_IRR->_hoops_PPH,
					 _hoops_HPH)) {
				_hoops_PRRSS (nr, text, &point, 1, _hoops_IHSCP, _hoops_HGCSR);
			}
			else
				_hoops_ASIGH (nr, text, &point, 1, _hoops_IHSCP, _hoops_HGCSR);
		}
	}
}


#define _hoops_PARSS(nr, font) \
		(_hoops_RAHCR == 0.0f && _hoops_HRCIR->path.x == 1.0f || \
		  (!BIT (nr->current, _hoops_RSSHP) && \
		  (!BIT (font->_hoops_CAGGH, _hoops_PAGGH) && \
		   _hoops_HRCIR->_hoops_CRRIP && \
		   (BIT (font->_hoops_CAGGH, _hoops_GPCSR) || \
			_hoops_HARSS && \
			BIT (font->_hoops_CAGGH, _hoops_SRGGH)))))
#define _hoops_IARSS(_hoops_HRCIR, font) \
		(_hoops_HRCIR->_hoops_IPGRP == 0.0f || \
		  (BIT (font->_hoops_CAGGH, _hoops_RAGGH) && \
		  !BIT (font->_hoops_CAGGH, _hoops_PAGGH)))


#define _hoops_CARSS 1024

GLOBAL_FUNCTION void HD_Standard_Draw_Inter_Text (
	Net_Rendition const &		inr,
	Text_Info const *			ti) {
	Net_Rendition				nr = inr;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_IGCSR				_hoops_HRCIR = nr->_hoops_SISI;
	_hoops_HACC const *				text = ti->text;
	Display_Context const *		dc = nr->_hoops_SRA;
	Point						point;
	float						_hoops_RAHCR;
	int							tmp;
	bool						_hoops_HARSS;
	int							count = ti->_hoops_SIHSA.length;
	Karacter const *			_hoops_AARPS = ti->_hoops_SIHSA._hoops_IPPPP;
	Karacter const *			_hoops_IHSCP;
	Karacter					_hoops_SARSS[_hoops_CARSS];
	Karacter *					_hoops_GPRSS = null;
	_hoops_IHGRP				encoding = text->encoding;
	bool						_hoops_RPRSS = false;

	/* _hoops_HRCSR _hoops_GHCA _hoops_HS _hoops_RPII _hoops_CPCGP _hoops_AIH _hoops_GHAP._hoops_RPRAR. */
	if (_hoops_HRCIR->font == null ||
		!HI_Encoding_Is_Compatible (encoding, _hoops_HRCIR->font->encoding)) {

		_hoops_RPRSS = true;
		_hoops_CAAI (HOOPS_WORLD->_hoops_HPHGI);
		do {
			HD_Choose_Font (nr, _hoops_HRCIR->_hoops_HSRIP->_hoops_HGPIR, encoding, true);

			/* _hoops_GHCA _hoops_HAR _hoops_SHH _hoops_SHSS _hoops_IS _hoops_HSRS _hoops_GII _hoops_HRCSR _hoops_GGR _hoops_RGR _hoops_AGIR, _hoops_HIS _hoops_RCRP _hoops_GH */
			if (_hoops_HRCIR->font == null) {
				_hoops_APAI (HOOPS_WORLD->_hoops_HPHGI);
				return;
			}

		} _hoops_RGGA (HD_Load_Font (dc, _hoops_HRCIR->font));
	}
	else {
		if (!_hoops_HRCIR->font->_hoops_PRGGH && !_hoops_HRCIR->font->_hoops_CGCSR)
			HD_Load_Font (nr->_hoops_SRA, _hoops_HRCIR->font);
	}

	if (_hoops_HRCIR->font == null || _hoops_HRCIR->font->_hoops_PRGGH || !_hoops_HRCIR->font->_hoops_CGCSR) {
		if (_hoops_RPRSS)
			_hoops_APAI (HOOPS_WORLD->_hoops_HPHGI);
		return;
	}

/* _hoops_ASIGA _hoops_RIR _hoops_GAS _hoops_IPISR */
	/*_hoops_APRSS _hoops_RRAGC _hoops_HCSRH _hoops_AIGSC _hoops_PPRSS _hoops_GGHPC _hoops_RRHCS _hoops_CRAIA _hoops_AGGPA _hoops_HPRSS _hoops_IPRSS*/
	if (encoding != _hoops_HRCIR->font->encoding &&
			HI_Encoding_Is_Compatible(encoding, _hoops_HRCIR->font->encoding) == _hoops_ACIGI) {
		/*_hoops_CGH _hoops_RGAR _hoops_SHH _hoops_CPRSS _hoops_PAR _hoops_SPRSS */
		if (count > _hoops_CARSS) {
			ALLOC_ARRAY(_hoops_GPRSS, count, Karacter);
			_hoops_IHSCP = _hoops_GPRSS;
		}
		else
			_hoops_IHSCP = _hoops_SARSS;

		HI_Convert_Karacters_Encoding (count, _hoops_AARPS, (Karacter*) _hoops_IHSCP, encoding, _hoops_HRCIR->font->encoding);
		encoding = _hoops_HRCIR->font->encoding;
	}
	else
		_hoops_IHSCP = _hoops_AARPS;


	point.x = ti->position.x;
	point.y = ti->position.y;
	point.z = ti->position.z;

	_hoops_RAHCR = _hoops_HRCIR->rotation;
	tmp = (int)(_hoops_RAHCR / 90.0f + 0.5f);
	_hoops_HARSS = (Abs(_hoops_RAHCR - tmp*90.0f) <= 0.25f);


	/* _hoops_AIHH _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_RH "_hoops_GSSR" _hoops_AGIR. _hoops_GHRSS */
	if (_hoops_HRCIR->spacing == 1.0f &&
		!BIT(ti->flags, _hoops_AAPSP) &&
		_hoops_HRCIR->transform == FT_NONE &&
#ifndef _hoops_IRRHP
		!BIT (nr->transform_rendition->flags, _hoops_GSASP) &&
#endif
		_hoops_HRCIR->path.z == 0.0f &&
		_hoops_PARSS(nr, _hoops_HRCIR->font) &&
		_hoops_IARSS(_hoops_HRCIR, _hoops_HRCIR->font) &&
		ti->_hoops_PCPAP == 0.0f) { 

		if (BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HPH)) 
			_hoops_PRRSS (nr, text, &point, count, _hoops_IHSCP, ti->_hoops_HGCSR);
		else
			_hoops_ASIGH (nr, text, &point, count, _hoops_IHSCP, ti->_hoops_HGCSR);
	}
	else {		
		/* _hoops_GAS _hoops_HPP _hoops_GAS */
		float					_hoops_RAPPI, _hoops_RGAGH;
		float					_hoops_CGSIR;
		float					_hoops_CCCRP;
		Karacter				_hoops_RHRSS;
		Font_Instance const *	font;
		Net_Rendition			_hoops_AHRSS;
		bool					first;
		int						_hoops_ISAIP;
		_hoops_SCSSP alter * _hoops_RGPIP;
		int						x = 0;

		first = true;
		_hoops_RGAGH = 0.0f;

		while (1) {
			bool				_hoops_PHRSS=true;
			int					_hoops_PPPSP = 0;
			int					_hoops_HHRSS = 0;

			/*_hoops_SGH _hoops_RIR _hoops_GAS */
			if (ti->_hoops_HGCSR) {
				if (ti->_hoops_PPPSP)
					_hoops_PPPSP = ti->_hoops_PPPSP[x++];
				else
					_hoops_PPPSP = x++;

				_hoops_HHRSS = ti->_hoops_HGCSR[_hoops_PPPSP].flags;
				nr = ti->_hoops_HGCSR[_hoops_PPPSP].nr;
				if (nr == null) 
					nr = inr;
				_hoops_HRCIR = nr->_hoops_SISI;
				font = _hoops_HRCIR->font;
				_hoops_RGPIP = ((Font_Instance alter *)font)->_hoops_RGPIP;
				_hoops_RAPPI = ti->_hoops_HGCSR[_hoops_PPPSP].width;

				if (BIT(ti->_hoops_HGCSR[_hoops_PPPSP].flags, _hoops_IAPSP)) 
					_hoops_PHRSS=false;
				else {
					_hoops_ISAIP = _hoops_GGPIP(*_hoops_IHSCP);
					if (_hoops_RGPIP[_hoops_ISAIP]._hoops_CSAIP != *_hoops_IHSCP) {
						/* _hoops_RIAGR _hoops_SCH _hoops_IHSHH _hoops_ARPP, _hoops_HIH _hoops_IHAH _hoops_HA _hoops_SSCP _hoops_CPHP _hoops_SHS */
						HD_Measure_Characters (nr, 1, _hoops_IHSCP, encoding, &_hoops_RAPPI);	/* _hoops_HHSA _hoops_SGCSR */
					}
				}
			}
			else {
				font = _hoops_HRCIR->font;
				_hoops_RGPIP = ((Font_Instance alter *)font)->_hoops_RGPIP;
				HD_Measure_Characters (nr, 1, _hoops_IHSCP, encoding, &_hoops_RAPPI);
				_hoops_RAPPI *= _hoops_HRCIR->width_scale;
			}

			_hoops_ISAIP = _hoops_GGPIP(*_hoops_IHSCP);

			if (!_hoops_RGPIP[_hoops_ISAIP].valid ||
				_hoops_RGPIP[_hoops_ISAIP]._hoops_CSAIP != *_hoops_IHSCP) {
					/*_hoops_SIGP _hoops_PGSA _hoops_AHCRR _hoops_PPR _hoops_GRHP _hoops_CPIC*/
					_hoops_IHSCP++;
					if (--count == 0) break;
					_hoops_RGAGH = 0.0f;
					continue;
			}

			if (_hoops_RGPIP[_hoops_ISAIP]._hoops_RSSSP) {
				font = _hoops_RGPIP[_hoops_ISAIP]._hoops_RSSSP;
				_hoops_RHRSS = _hoops_RGPIP[_hoops_ISAIP]._hoops_CSSSP;

				if (font && !font->_hoops_PRGGH) {
					if (!font->_hoops_CGCSR)
						HD_Load_Font (nr->_hoops_SRA, font);

					_hoops_AHRSS = nr;
					_hoops_IGCSR alter &		_hoops_IRRIP = _hoops_AHRSS.Modify()->_hoops_SISI.Modify();

					_hoops_IRRIP->font = font;
					_hoops_HRCIR = _hoops_IRRIP;
				}
				else {
					/*_hoops_SIGP _hoops_PGSA _hoops_AHCRR _hoops_PPR _hoops_GRHP _hoops_CPIC*/
					_hoops_IHSCP++;
					if (--count == 0) break;
					_hoops_RGAGH = 0.0f;
					continue;
				}
			}
			else {
				_hoops_AHRSS = nr;
				_hoops_RHRSS = *_hoops_IHSCP;
			}

			if (!ti->_hoops_HGCSR) {
				if (!first) {
					if (_hoops_HRCIR->_hoops_HCRIP) {
						_hoops_CGSIR = ti->_hoops_SHPSP / (float)(ti->_hoops_SIHSA.length - 1);
					}
					else {
						/*
						**	_hoops_IAPPI _hoops_IIGR _hoops_PIAHR _hoops_PPSR._hoops_SISR _hoops_CIAAI:
						**
						**		_hoops_PPSR._hoops_SISR += 0.5 * _hoops_IHRSS;		_hoops_RAAP -> _hoops_RHCH
						**		_hoops_PPSR._hoops_SISR += _hoops_CRAA._hoops_SISR * _hoops_GIRA;		_hoops_CCAH _hoops_RHCH
						**		_hoops_PPSR._hoops_SISR -= 0.5 * _hoops_CHRSS;		_hoops_RHCH -> _hoops_RAAP
						*/
						_hoops_CGSIR = ti->_hoops_AHPSP.x * 0.5f * (_hoops_RGAGH + _hoops_RAPPI) +
								   (ti->_hoops_AHPSP.y * (float)_hoops_HRCIR->font->_hoops_IGGGH) + 
								   ti->_hoops_AHPSP.z + ti->_hoops_PCPAP;
					}

					_hoops_CCCRP = 0.5f * (_hoops_RGAGH - _hoops_RAPPI);

					point.x += ti->path.x * _hoops_CGSIR  +	ti->_hoops_GHPSP.x * _hoops_CCCRP;
					point.y += ti->path.y * _hoops_CGSIR  +	ti->_hoops_GHPSP.y * _hoops_CCCRP;
					point.z += ti->path.z * _hoops_CGSIR; /* _hoops_PAPPI->_hoops_HAPPI._hoops_SSH _hoops_HRGR _hoops_SHR 0 */

				}
				else
					first = false;

				_hoops_RGAGH = _hoops_RAPPI;			
			
				if (_hoops_HRCIR->transform != FT_NONE) 
					_hoops_IRRSS (_hoops_AHRSS, ti, &point, &_hoops_RHRSS, null);
				else if (BIT (_hoops_AHRSS->_hoops_IRR->_hoops_PPH, _hoops_HPH))
					_hoops_PRRSS (_hoops_AHRSS, text, &point, 1, &_hoops_RHRSS, null);
				else
					_hoops_ASIGH (_hoops_AHRSS, text, &point, 1, &_hoops_RHRSS, null);			
			}
			else {
#if 0
				DC_Point pts[5];
				pts[0].x = ti->_hoops_HGCSR[_hoops_PPPSP].position.x;
				pts[0].y = ti->_hoops_HGCSR[_hoops_PPPSP].position.y;
				pts[0].z = 0.0f;
				pts[1].x = ti->_hoops_HGCSR[_hoops_PPPSP].position.x + ti->_hoops_HGCSR[_hoops_PPPSP].width;
				pts[1].y = ti->_hoops_HGCSR[_hoops_PPPSP].position.y;
				pts[1].z = 0.0f;
				pts[2].x = ti->_hoops_HGCSR[_hoops_PPPSP].position.x + ti->_hoops_HGCSR[_hoops_PPPSP].width;
				pts[2].y = ti->_hoops_HGCSR[_hoops_PPPSP].position.y + ti->_hoops_HGCSR[_hoops_PPPSP].height;
				pts[2].z = 0.0f;
				pts[3].x = ti->_hoops_HGCSR[_hoops_PPPSP].position.x;
				pts[3].y = ti->_hoops_HGCSR[_hoops_PPPSP].position.y + ti->_hoops_HGCSR[_hoops_PPPSP].height;
				pts[3].z = 0.0f;
				pts[4].x = ti->_hoops_HGCSR[_hoops_PPPSP].position.x;
				pts[4].y = ti->_hoops_HGCSR[_hoops_PPPSP].position.y;
				pts[4].z = 0.0f;
				_hoops_SCGGA(nr, 5, pts);
#endif
				if (_hoops_PHRSS) {
					/* _hoops_IH _hoops_PGHGR _hoops_HAIR _hoops_SHPH */
					if (!BIT (_hoops_HHRSS, _hoops_RPPSP) && inr->_hoops_SISI->color != _hoops_HRCIR->color) {
						if (_hoops_AHRSS == nr)
							_hoops_HRCIR = _hoops_AHRSS.Modify()->_hoops_SISI.Modify();

						_hoops_HRCIR->_hoops_RGIHP = null;

						_hoops_HRCIR->_hoops_CHA = inr->_hoops_SISI->_hoops_CHA;
						_hoops_HRCIR->color = inr->_hoops_SISI->color;
					}

					/* _hoops_IH _hoops_PGHGR _hoops_CIHH _hoops_SHPH */
					if (_hoops_IHCR->_hoops_HCHH != _hoops_AHRSS->transform_rendition->_hoops_HCHH) {
						_hoops_HHCR alter &		_hoops_GGCC = _hoops_AHRSS.Modify()->transform_rendition.Modify();

						_hoops_GGCC->_hoops_HCHH = _hoops_IHCR->_hoops_HCHH;
					}

					ti->_hoops_HGCSR[_hoops_PPPSP].position += ti->_hoops_CPPSP;

					if (_hoops_HRCIR->transform != FT_NONE) 
						_hoops_IRRSS (_hoops_AHRSS, ti, &ti->_hoops_HGCSR[_hoops_PPPSP].position, &_hoops_RHRSS,
										 &ti->_hoops_HGCSR[_hoops_PPPSP]);
					else if (BIT (_hoops_AHRSS->_hoops_IRR->_hoops_PPH, _hoops_HPH))
						_hoops_PRRSS (_hoops_AHRSS, text, &ti->_hoops_HGCSR[_hoops_PPPSP].position, 1, &_hoops_RHRSS,
										  &ti->_hoops_HGCSR[_hoops_PPPSP]);
					else
						_hoops_ASIGH (_hoops_AHRSS, text, &ti->_hoops_HGCSR[_hoops_PPPSP].position, 1, &_hoops_RHRSS,
											 &ti->_hoops_HGCSR[_hoops_PPPSP]);
				}
			}

			_hoops_HRCIR = nr->_hoops_SISI;

			if (--count == 0) break;

			_hoops_IHSCP++;
		}
	}

	if (_hoops_RPRSS)
		_hoops_APAI (HOOPS_WORLD->_hoops_HPHGI);

	if (_hoops_GPRSS)
		FREE_ARRAY (_hoops_GPRSS, count, Karacter);
}

local const Vector			_hoops_CRCSR (1.0f, 1.0f, 1.0f);

GLOBAL_FUNCTION void HD_Standard_Draw_Plain_Text (
	Net_Rendition const &		nr,
	_hoops_HACC const *				_hoops_PCHIH,
	Point const *				position,
	int							count,
	Karacter const *			_hoops_IHSCP,
	_hoops_PGCSR const *	_hoops_HGCSR) {
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	Font_Instance const	*		font = _hoops_HRCIR->font;
	Display_Context alter *		_hoops_RHSRH = (Display_Context alter *) nr->_hoops_SRA;

	UNREFERENCED (_hoops_PCHIH);
	UNREFERENCED (_hoops_HGCSR);

	/* _hoops_RPP _hoops_HCGR _hoops_HRGR _hoops_PISI (_hoops_HGPP _hoops_GAR _hoops_PSAAS'_hoops_GRI), _hoops_HRCSR _hoops_SIAS _hoops_HS _hoops_RPII _hoops_SHRSS */
	if (!font->_hoops_CGCSR)
		if (!HD_Load_Font (nr->_hoops_SRA, font))
			return;		/* _hoops_RCRP _hoops_GH _hoops_SCH _hoops_RPP _hoops_SR _hoops_PAH'_hoops_RA _hoops_SGCSR */

	_hoops_RHSRH->_hoops_HRIC = true;
	(*font->_hoops_SRCSR)(nr, font, position, count, _hoops_IHSCP, &_hoops_CRCSR);
	_hoops_RHSRH->_hoops_HRIC = false;

}


GLOBAL_FUNCTION void HD_Draw_Dead_Font (
	Net_Rendition const &		inr,
	Font_Instance const *		instance,
	Point const *				position,
	int							count,
	Karacter const *			_hoops_IHSCP,
	Vector const *				scale) {
	Net_Rendition				nr = inr;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_IGPIR					_hoops_RCPPI;
	float						width;

	UNREFERENCED (instance);

	if (!scale) 
		scale = &_hoops_CRCSR;

	_hoops_RCPPI.specified.length = 0;
	_hoops_RCPPI.next = null;
	_hoops_RCPPI._hoops_SSSGP = GFN_STROKED;

	nr.Modify()->_hoops_SISI.Modify()->_hoops_SRRIP();

	/* _hoops_HPRAR _hoops_GIRSS _hoops_RPP _hoops_SR _hoops_HS _hoops_IS */
	if (!ANYBIT(nr->current, _hoops_GSSHP|_hoops_RSSHP) &&
		ANYBIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP|_hoops_CRAAP) &&
		 BIT(dc->flags, _hoops_AASHP)) {

		nr->_hoops_IRR.Modify()->_hoops_CHP &= ~(_hoops_SHP|_hoops_CRAAP);
	}


	/* _hoops_PAHA'_hoops_RA _hoops_RRP _hoops_IS _hoops_RGIC _hoops_AHCA _hoops_HRCSR _hoops_HAGAR _hoops_GGRRA _hoops_ARI */
	HD_Choose_Font (nr, &_hoops_RCPPI, _hoops_SACSR, true);
	
	HD_Measure_Characters (nr, count, _hoops_IHSCP, nr->_hoops_SISI->font->encoding, &width);

	HD_Draw_Defined_Font(nr, nr->_hoops_SISI->font, position, count, _hoops_IHSCP, scale);
}


GLOBAL_FUNCTION void HD_Draw_Stenciled_Font (
	Net_Rendition const & 		in_nr,
	Font_Instance const *		instance,
	Point const *				where,
	int							count,
	Karacter const *			string,
	Vector const *				scale) {
	Net_Rendition				nr = in_nr;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	bool						antialias = BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_CRAAP);
	Point						points[4];
	float						x = where->x, y = where->y, z = where->z;
	float						_hoops_IPGRP = _hoops_HRCIR->_hoops_IPGRP; 
	float						rotation = _hoops_HRCIR->rotation;
	float						width_scale = _hoops_HRCIR->width_scale;
	float						_hoops_RIRSS;
	float						_hoops_AIRSS;
	float						_hoops_PIRSS;
	int							bitmap_height;
	int							bolding_level = 0;
	int							index;
	_hoops_RAARP **			_hoops_PPSIH = 0;
	float						_hoops_HIRSS = 0.0, _hoops_IIRSS = 0.0;

	if (!instance->_hoops_RGSSP) {
		HD_Draw_Dead_Font (nr, instance, where, count, string, scale);
		return;
	}

	if (_hoops_HRCIR->transform == FT_FULL && 
		 !ANYBIT(nr->current, _hoops_GSSHP|_hoops_RSSHP) &&
		 BIT(dc->flags, _hoops_AASHP))
			antialias = false;


	if (nr->_hoops_IRR->_hoops_SRI == _hoops_PRAAP)
		antialias = false;

	if (_hoops_HRCIR->_hoops_PSRIP)
		_hoops_IPGRP += 10.0f;

	bitmap_height = HI_Get_Stencil_Cache_Height ((int)instance->_hoops_RACSR, (_hoops_HRCIR->transform == FT_FULL));
	_hoops_RIRSS = (instance->_hoops_RACSR / (float)bitmap_height) * instance->_hoops_GCHSA;
	if (_hoops_HRCIR->transform == FT_FULL) {
		_hoops_AIRSS = _hoops_RIRSS * scale->x;
		_hoops_PIRSS = _hoops_RIRSS * scale->y;
	}
	else
		_hoops_AIRSS = _hoops_PIRSS = _hoops_RIRSS;

	if (_hoops_HRCIR->_hoops_ASRIP) {
		if (bitmap_height>12)
			bolding_level = bitmap_height/32+1;
	}

	_hoops_PPSIH = HI_Get_Stencil_Cache (instance, 
											bitmap_height, bolding_level, _hoops_IPGRP, 
											rotation, width_scale, antialias);

	for (index=0; index<count; index++) {
		_hoops_RAARP *	stencil = 0;
		unsigned short		_hoops_SRCSP = (*instance->map_font_char_index)(instance, string[index]);
		float				_hoops_CIRSS, _hoops_SIRSS;

		_hoops_IIRSS = 0.0, _hoops_HIRSS = 0.0;

		

		stencil = HI_Lookup_Stencil (_hoops_PPSIH, _hoops_SRCSP);

		if (!stencil) {
			stencil = (*instance->_hoops_RGSSP)(nr, instance, _hoops_SRCSP, bitmap_height, 
													bolding_level, _hoops_IPGRP, rotation, width_scale, antialias);

			if (!stencil) {
				/* _hoops_HGHC _hoops_GCRSS _hoops_IH _hoops_IGRIP _hoops_APSP */
				ZALLOC (stencil, _hoops_RAARP);

				stencil->id = _hoops_SRCSP;
				stencil->height = -1;
			}
			else{
				/* _hoops_CPPPR _hoops_GRH _hoops_AGIR _hoops_IH _hoops_RISA _hoops_PGPSH _hoops_RCRSS */
				if (string[index] == 46 && !antialias && stencil->width == 2 && stencil->height == 1 && stencil->bitmap[0] == 0){
					stencil->bitmap[0] = 64;
				}
			}

			HI_Store_Stencil (_hoops_PPSIH, stencil); 
		}

		/* _hoops_RPCRC: _hoops_SSCR _hoops_GGSR _hoops_IGH _hoops_PAR _hoops_HAR _hoops_RH !_hoops_SRSGI _hoops_AGIR _hoops_ARI _hoops_CGH _hoops_HS _hoops_ACRSS _hoops_SGGA*/
		if ((_hoops_HRCIR->transform == FT_FULL)){
			_hoops_HIRSS = stencil->_hoops_IPARP  * _hoops_PIRSS;
			_hoops_IIRSS  = stencil->_hoops_CPARP * _hoops_AIRSS;
		}
		else{
			_hoops_HIRSS = stencil->_hoops_IPARP * _hoops_PIRSS;
			_hoops_IIRSS  = stencil->_hoops_CPARP * _hoops_AIRSS;
		}

		if (stencil->height == -1) {
			Point alter		loc;

			loc.x = x;
			loc.y = y;
			loc.z = z;
			
			HD_Draw_Dead_Font(nr, instance, &loc, 1, &string[index], scale);
			continue;
		}

		points[0].x = x + _hoops_AIRSS * -stencil->_hoops_CAARP - _hoops_IIRSS;
		points[0].y = y + _hoops_PIRSS * (stencil->_hoops_RPARP - stencil->_hoops_SAARP) - _hoops_HIRSS;
		points[0].z = z;
		points[1].x = points[0].x;	
		points[1].y = points[0].y + _hoops_PIRSS * (stencil->height-1);
		points[1].z = z;
		points[2].x = points[0].x + _hoops_AIRSS * (stencil->width-1);
		points[2].y = points[0].y;
		points[2].z = z;
		points[3].x = points[2].x;
		points[3].y = points[1].y;
		points[3].z = z;

		/* _hoops_RPP _hoops_SR _hoops_AA _hoops_RGR _hoops_AGRP _hoops_GPP _hoops_HCGR _hoops_APPR _hoops_HSAR 254 (_hoops_RH _hoops_IRRPA _hoops_APSP _hoops_IGIR) _hoops_PSCR
		   _hoops_SCH _hoops_GCSRS _hoops_CGSI _hoops_PPRRR _hoops_PSAP, _hoops_HIS _hoops_RGAR _hoops_AA _hoops_SCH _hoops_GPP _hoops_GRAA-_hoops_IRRPA _hoops_PCPP _hoops_RCRSS */
		if (bitmap_height < 254 && _hoops_HRCIR->transform != FT_FULL){
			points[1].y = points[0].y + (stencil->height); 
			points[2].x = points[0].x + (stencil->width); 
			points[3].x = points[2].x;
			points[3].y = points[1].y;
		}

		if (rotation-stencil->rotation != 0.0f || 
			width_scale-stencil->width_scale != 0.0f) {
			_hoops_RICH(rotation, _hoops_SIRSS, _hoops_CIRSS);
		
			points[0].x = _hoops_CIRSS*(_hoops_AIRSS * -stencil->_hoops_CAARP) + -_hoops_SIRSS*(_hoops_PIRSS * -stencil->_hoops_SAARP) + x - _hoops_IIRSS; 
			points[0].y = _hoops_SIRSS*(_hoops_AIRSS * -stencil->_hoops_CAARP) +  _hoops_CIRSS*(_hoops_PIRSS * -stencil->_hoops_SAARP) + y - _hoops_CIRSS*_hoops_HIRSS;
			points[0].z = z;
			points[1].x = _hoops_CIRSS*(_hoops_AIRSS * -stencil->_hoops_CAARP) + -_hoops_SIRSS*_hoops_PIRSS*(-stencil->_hoops_SAARP + stencil->height-1) + x- _hoops_IIRSS;
			points[1].y = _hoops_SIRSS*(_hoops_AIRSS * -stencil->_hoops_CAARP) +  _hoops_CIRSS*_hoops_PIRSS*(-stencil->_hoops_SAARP + stencil->height-1) + y - _hoops_CIRSS*_hoops_HIRSS ;
			points[1].z = z;
			points[2].x = _hoops_CIRSS*_hoops_AIRSS*width_scale*(-stencil->_hoops_CAARP + stencil->width -1) + -_hoops_SIRSS*_hoops_PIRSS*(-stencil->_hoops_SAARP) + x- _hoops_IIRSS;
			points[2].y = _hoops_SIRSS*_hoops_AIRSS*width_scale*(-stencil->_hoops_CAARP + stencil->width -1) +  _hoops_CIRSS*_hoops_PIRSS*(-stencil->_hoops_SAARP) + y - _hoops_CIRSS*_hoops_HIRSS ;
			points[2].z = z;
			points[3].x = _hoops_CIRSS*_hoops_AIRSS*width_scale*(-stencil->_hoops_CAARP + stencil->width -1) + -_hoops_SIRSS*_hoops_PIRSS*(-stencil->_hoops_SAARP + stencil->height-1) + x- _hoops_IIRSS;
			points[3].y = _hoops_SIRSS*_hoops_AIRSS*width_scale*(-stencil->_hoops_CAARP + stencil->width -1) +  _hoops_CIRSS*_hoops_PIRSS*(-stencil->_hoops_SAARP + stencil->height-1) + y - _hoops_CIRSS*_hoops_HIRSS ;
			points[3].z = z;
		}
		

#if 0	/* _hoops_PGSA _hoops_RH _hoops_APSP _hoops_RSSA _hoops_IH _hoops_GSPHR */
		{
			Polyline polyline;	/* _hoops_AGCR _hoops_GPP _hoops_RRGC _hoops_HRGR _hoops_HAR _hoops_CPSA _hoops_ICIC... */
			Point _hoops_PCRSS[4];

			ZERO_STRUCT(&polyline, Polyline);

			_hoops_AIGA (points, 4, Point, _hoops_PCRSS);

			polyline.points=_hoops_PCRSS;
			polyline.count=4;
			_hoops_CPAGR(nr, &polyline);
		}
#endif

		if (_hoops_HRCIR->transform == FT_FULL)
			_hoops_HGCGH (nr, points, stencil);
		else
			_hoops_GGRCP(nr, (DC_Point*)points, stencil);

		x += stencil->_hoops_HAARP * _hoops_RIRSS;
		y += stencil->_hoops_IAARP * _hoops_RIRSS;
	}
}



GLOBAL_FUNCTION void HD_Standard_Draw_Font (
	Net_Rendition const &		nr,
	Font_Instance const *		instance,
	Point const *				position,
	int							count,
	Karacter const *			_hoops_IHSCP,
	Vector const *				scale) {
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;

	if (_hoops_HRCIR->transform == FT_FULL || instance->_hoops_HRGGH)
		HD_Draw_Stenciled_Font (nr,instance,position,count,_hoops_IHSCP,scale);
	else
		_hoops_RAICP (nr, (DC_Point*)position, count, _hoops_IHSCP);

}

GLOBAL_FUNCTION void HD_Std_DC_Text (
	Net_Rendition const & 		nr,
	DC_Point const *			position,
	int							count,
	Karacter const *			kstring) {
	Vector const				_hoops_CRCSR = Vector(1.0f, 1.0f, 1.0f);
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	Font_Instance const *		font = _hoops_HRCIR->font;

	if (font == null) do {
		HD_Choose_Font (nr, _hoops_HRCIR->_hoops_HSRIP->_hoops_HGPIR, _hoops_SSAIP, true);

		if ((font = _hoops_HRCIR->font) == null)
			break;
	} while (!HD_Load_Font (nr->_hoops_SRA, font));

	if (font != null)
		font->_hoops_SRCSR (nr, font, position, count, kstring, &_hoops_CRCSR);
}


GLOBAL_FUNCTION void HD_Clip_DC_Text (
	Net_Rendition const & 			inr,
	DC_Point const *				position,
	int								count,
	Karacter const *				kstring) {
	Net_Rendition					nr = inr.Copy();
	_hoops_HHCR alter &		_hoops_GGCC = nr->transform_rendition.Modify();
	_hoops_IGCSR const &			_hoops_HRCIR = nr->_hoops_SISI;
	Font_Instance const *			font = _hoops_HRCIR->font;
	DC_Point						point;
	float							width;
	_hoops_GPPA const *	_hoops_RPGGA[4];
	_hoops_GPPA const *	_hoops_APGGA = 0;
	_hoops_IAPA const		*	_hoops_CAPA = null;
	int								_hoops_CPGGA = 0;
   
	// _hoops_PAGA: _hoops_SIHH _hoops_RGSHA _hoops_SGI _hoops_GAR _hoops_IGI _hoops_GGR _hoops_RH _hoops_HCRSS _hoops_PSCH, _hoops_SR _hoops_HPCAR _hoops_RH _hoops_HRGI _hoops_AGIR _hoops_SRS _hoops_PPR _hoops_RGAR _hoops_HPPP
	// _hoops_SGS, _hoops_HPIAA _hoops_RH _hoops_RHPP _hoops_PAH _hoops_RGHH _hoops_RH _hoops_RPGS _hoops_ARAR.  _hoops_HGI _hoops_AGSR _hoops_SR _hoops_GHCA _hoops_GHHA _hoops_IRS _hoops_CIAGR _hoops_IACH _hoops_GPGA _hoops_GPP _hoops_RSH
	// _hoops_RSCA _hoops_RH _hoops_RHPP _hoops_PAH _hoops_RGHH.  _hoops_ICRSS, _hoops_SR _hoops_CHH _hoops_ARP _hoops_GH _hoops_IRS _hoops_SASI _hoops_CCRSS _hoops_API _hoops_SGS _hoops_APPP _hoops_SGI
	// _hoops_PPR _hoops_AIAGI _hoops_RGR _hoops_HGSR _hoops_IS _hoops_IHSH _hoops_PII _hoops_RH _hoops_RII _hoops_SCRSS (_hoops_RH _hoops_PHSPR _hoops_RGHS _hoops_CHR _hoops_HRPP _hoops_IS _hoops_RGHH _hoops_RH
	// _hoops_GPGR _hoops_RGCSA _hoops_AGIR _hoops_PRGI _hoops_PHRI _hoops_SCH'_hoops_GRI _hoops_IPIH _hoops_GSRSS _hoops_IS _hoops_HAIHR _hoops_IRS _hoops_RSRA _hoops_AGIR)
	if (BIT (_hoops_GGCC->flags, _hoops_CSP)) {
		_hoops_SSP const &		_hoops_GGH = inr->transform_rendition->_hoops_RGH;

		if (BIT (_hoops_GGCC->flags, _hoops_HHGGA))
			HD_Set_DC_Cutting_Planes (nr);

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
		}
		else
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
		
		_hoops_RPGGA[_hoops_CPGGA++] = _hoops_CAPA->_hoops_APPA;
		_hoops_CAPA = _hoops_CAPA->next;

		_hoops_GGCC->_hoops_RGH = null;
		_hoops_GGCC->flags &= ~_hoops_CSP;
	}
	else if (_hoops_GGCC->_hoops_HCHH) {
		_hoops_ASHH const		*_hoops_CRAIR;

		_hoops_CRAIR = _hoops_GGCC->_hoops_HCHH->_hoops_PSHH;
		if (!_hoops_CRAIR->_hoops_GRCPR)
			HD_Validate_Clip_Half_Planes ((_hoops_ASHH alter *)_hoops_CRAIR);

		_hoops_RPGGA[_hoops_CPGGA++] = _hoops_CRAIR->_hoops_GRCPR;

		_hoops_GGCC->_hoops_HCHH = null;
	}
	else if (!BIT (_hoops_GGCC->flags, _hoops_AIHS)) {
		_hoops_RPGGA[_hoops_CPGGA++] = _hoops_APGGA = HD_Create_Hard_Clip_Cuts (inr, &_hoops_GGCC->_hoops_AGAA, null, 0);
		_hoops_GGCC->flags |= _hoops_AIHS;
	}
	////

	_hoops_RPGGA[_hoops_CPGGA] = 0;

	if (_hoops_CPGGA == 0) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						   "Std_DC_Text called with no clip/cut requirements");
		return;
	}

	Karacter const *		_hoops_RSRSS = kstring;

	_hoops_PCCAR {
		point.x = position->x;
		point.y = position->y;
		point.z = position->z;

		for (int i=0; i<count; ++i) {
			bool						_hoops_ASRSS = false;

			HD_Measure_Characters (nr, 1, kstring, font->encoding, &width);
			width *= _hoops_HRCIR->width_scale;

			if (width != 0) {
				_hoops_GPPA const **_hoops_IHGGA = _hoops_RPGGA;
				_hoops_GPPA const *_hoops_GRCPR;
				while ((_hoops_GRCPR = *_hoops_IHGGA++) != null) {
					do {
						DC_Point		test = point;

						if (_hoops_GRCPR->_hoops_SPPA.a * test.x +
							 _hoops_GRCPR->_hoops_SPPA.b * test.y +
							  _hoops_GRCPR->_hoops_SPPA.c * test.z +
							   _hoops_GRCPR->_hoops_SPPA.d > 0.0f) {
							_hoops_ASRSS = true;
							break;
						}

						test.x += _hoops_HRCIR->path.x * width;
						test.y += _hoops_HRCIR->path.y * width;
						if (_hoops_GRCPR->_hoops_SPPA.a * test.x +
							 _hoops_GRCPR->_hoops_SPPA.b * test.y +
							  _hoops_GRCPR->_hoops_SPPA.c * test.z +
							   _hoops_GRCPR->_hoops_SPPA.d > 0.0f) {
							_hoops_ASRSS = true;
							break;
						}

						test.x -= _hoops_HRCIR->path.y * font->_hoops_ISISR;
						test.y += _hoops_HRCIR->path.x * font->_hoops_ISISR;
						if (_hoops_GRCPR->_hoops_SPPA.a * test.x +
							 _hoops_GRCPR->_hoops_SPPA.b * test.y +
							  _hoops_GRCPR->_hoops_SPPA.c * test.z +
							   _hoops_GRCPR->_hoops_SPPA.d > 0.0f) {
							_hoops_ASRSS = true;
							break;
						}

						test.x -= _hoops_HRCIR->path.x * width;
						test.y -= _hoops_HRCIR->path.y * width;
						if (_hoops_GRCPR->_hoops_SPPA.a * test.x +
							 _hoops_GRCPR->_hoops_SPPA.b * test.y +
							  _hoops_GRCPR->_hoops_SPPA.c * test.z +
							   _hoops_GRCPR->_hoops_SPPA.d > 0.0f) {
							_hoops_ASRSS = true;
							break;
						}
					} while ((_hoops_GRCPR = _hoops_GRCPR->next) != null);

					if (_hoops_ASRSS)
						break;
				}
			}

			if (!_hoops_ASRSS)
				_hoops_RAICP (nr, &point, 1, kstring);

			point.x += _hoops_HRCIR->path.x * width;
			point.y += _hoops_HRCIR->path.y * width;
			point.z += _hoops_HRCIR->path.z * width;

			++kstring;
		}

		if (_hoops_CAPA == null)
			break;
		else {
			_hoops_RPGGA[_hoops_CPGGA-1] = _hoops_CAPA->_hoops_APPA;
			_hoops_CAPA = _hoops_CAPA->next;

			kstring = _hoops_RSRSS;
		}
	}

	while (_hoops_APGGA) {
		_hoops_GPPA const *	c = _hoops_APGGA;

		_hoops_APGGA = _hoops_APGGA->next;		
		FREE (c, _hoops_GPPA);
	}
}

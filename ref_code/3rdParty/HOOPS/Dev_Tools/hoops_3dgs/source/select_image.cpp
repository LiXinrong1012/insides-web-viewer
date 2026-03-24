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
 * $Id: obf_tmp.txt 1.78 2010-07-14 23:29:16 covey Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "tandt.h"
#include "select.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "patterns.h"

#ifndef DISABLE_SELECTION

/* _hoops_HRS _hoops_IHPR _hoops_RPP _hoops_SR'_hoops_ASAR *_hoops_ASSA* _hoops_RH _hoops_CARA */

struct _hoops_AICCP {
	float		_hoops_HHGGH;
	int			_hoops_RRCAS;
	int			_hoops_ARCAS;
};

local void _hoops_PRCAS (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							hoffset,
	Image_Format				format,
	int							row_bytes,
	void const * const *		rasters,
	int							pattern,
	Driver_Color const *		contrast_color,
	Image const *				db_image) {
	_hoops_ACCCP alter	*	sc;
	struct _hoops_AICCP alter		*info;
	int							left   = (int)start->x;
	int							right  = (int)end->x;
	int							top	   = (int)start->y;
	int							bottom = (int)end->y;
	float						_hoops_HSHGA,
								_hoops_ISHGA,
								_hoops_CIPAS,
								a,
								b;
	int							_hoops_HRCAS,
								_hoops_IRCAS;

	UNREFERENCED (hoffset);
	UNREFERENCED (format);
	UNREFERENCED (row_bytes);
	UNREFERENCED (rasters);
	UNREFERENCED (pattern);
	UNREFERENCED (contrast_color);
	UNREFERENCED (db_image);

	sc = nr->_hoops_SRA->_hoops_APHHP;
	info = (struct _hoops_AICCP alter *)sc->_hoops_AICCP;

	if ((_hoops_HSHGA = (float)((int)sc->_hoops_AICAH.x - left)) < 0.0f)
		_hoops_HRCAS = left;
	else if ((_hoops_HSHGA = (float)((int)sc->_hoops_AICAH.x - right)) > 0.0f)
		_hoops_HRCAS = right;
	else {
		_hoops_HSHGA = 0.0f;
		_hoops_HRCAS = (int)sc->_hoops_AICAH.x;
	}

	if ((_hoops_ISHGA = (float)((int)sc->_hoops_AICAH.y - bottom)) < 0.0f)
		_hoops_IRCAS = bottom;
	else if ((_hoops_ISHGA = (float)((int)sc->_hoops_AICAH.y - top)) > 0.0f)
		_hoops_IRCAS = top;
	else {
		_hoops_ISHGA = 0.0f;
		_hoops_IRCAS = (int)sc->_hoops_AICAH.y;
	}

	/* _hoops_GHARP _hoops_RPGP */
	a = _hoops_HSHGA / sc->_hoops_HICAH.x;
	b = _hoops_ISHGA / sc->_hoops_HICAH.y;
	_hoops_CIPAS = a*a + b*b;
	if (_hoops_CIPAS > sc->_hoops_GICAH) return;

	/* _hoops_SCH'_hoops_GRI _hoops_AIRAI _hoops_PPR _hoops_IRS _hoops_RIRA _hoops_SPR */

	info->_hoops_RRCAS = _hoops_HRCAS;
	info->_hoops_ARCAS = _hoops_IRCAS;
	info->_hoops_HHGGH = _hoops_CIPAS;
}
#endif


GLOBAL_FUNCTION void HD_Select_Image (
	Net_Rendition const &		nr,
	Image const *				image) {
#ifndef DISABLE_SELECTION
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter *	sc = dc->_hoops_APHHP;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_RPRA const *			elements = _hoops_IHCR->matrix->data.elements;
	float						_hoops_CRCAS, _hoops_SRCAS,
								_hoops_CIPAS,
								_hoops_HGCPC,
								_hoops_GACAS,
								_hoops_HSHGA, _hoops_ISHGA,
								a, b;
	int							left, right, bottom, top;
	int							offset1, offset2;

	if (BIT (sc->options, _hoops_IICAH)) {
		HD_Select_Dot (nr, (Geometry alter *)image, image->key, _hoops_AIRIR(image), T_IMAGES,
					   &image->_hoops_CSAI);
		return;
	}

	if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
		_hoops_HGCPC = 1.0f;
		_hoops_CRCAS = _hoops_HPRA (elements, image->_hoops_CSAI) -
				image->width * 0.5f + 0.501f;

		if (_hoops_CRCAS > sc->bounding.right ||
			_hoops_CRCAS + image->width < sc->bounding.left) return;

		_hoops_SRCAS = _hoops_IPRA (elements, image->_hoops_CSAI) -
				  image->height * 0.5f + 0.501f;
	}
	else {
		_hoops_HGCPC = _hoops_PHCP (elements, image->_hoops_CSAI);
		if (_hoops_HGCPC <= _hoops_IHCR->_hoops_CHCR) return;

		_hoops_CRCAS = _hoops_HPRA (elements, image->_hoops_CSAI) / _hoops_HGCPC -
				image->width * 0.5f + 0.501f;

		if (_hoops_CRCAS > sc->bounding.right ||
			_hoops_CRCAS + image->width < sc->bounding.left) return;

		_hoops_SRCAS = _hoops_IPRA (elements, image->_hoops_CSAI) / _hoops_HGCPC -
				  image->height * 0.5f + 0.501f;
	}

	if (_hoops_SRCAS > sc->bounding.top ||
		_hoops_SRCAS + image->height < sc->bounding.bottom) return;

	/* _hoops_CAHA _hoops_RH _hoops_SACH _hoops_PRCH _hoops_IIGR _hoops_RH _hoops_AIR _hoops_CRPR */

	left = (int)_hoops_CRCAS;
	right = left + image->width - 1;

	if (left < (int)sc->bounding.left)
		left = (int)sc->bounding.left;
	else if (left > (int)sc->bounding.right) return;

	if (right > (int)sc->bounding.right)
		right = (int)sc->bounding.right;
	else if (right < (int)sc->bounding.left) return;

	bottom = (int)_hoops_SRCAS;
	top = bottom + image->height - 1;

	if (bottom < (int)sc->bounding.bottom)
		bottom = (int)sc->bounding.bottom;
	else if (bottom > (int)sc->bounding.top) return;

	if (top > (int)sc->bounding.top)
		top = (int)sc->bounding.top;
	else if (top < (int)sc->bounding.bottom) return;

	if ((_hoops_HSHGA = (float)((int)sc->_hoops_AICAH.x - left)) < 0.0f) {/* _hoops_HASRH _hoops_HRGR _hoops_IS _hoops_RH _hoops_RAAP */}
	else if ((_hoops_HSHGA = (float)((int)sc->_hoops_AICAH.x - right)) > 0.0f) {/* _hoops_PAR _hoops_IS _hoops_RH _hoops_RPHR */}
	else _hoops_HSHGA = 0.0f;						/* _hoops_PAR _hoops_GIAA */

	if ((_hoops_ISHGA = (float)((int)sc->_hoops_AICAH.y - bottom)) < 0.0f) {/* _hoops_HASRH _hoops_HRGR _hoops_CAPP */}
	else if ((_hoops_ISHGA = (float)((int)sc->_hoops_AICAH.y - top)) > 0.0f) {/* _hoops_PAR _hoops_ARRS */}
	else _hoops_ISHGA = 0.0f;						/* _hoops_PAR _hoops_GIAA */

	if (_hoops_HSHGA == 0.0f && _hoops_ISHGA == 0.0f) {
		/* _hoops_HASRH'_hoops_GRI _hoops_GIAA - _hoops_IRAA _hoops_SCH! */
		_hoops_CIPAS = 0.0f;
	}
	else {
		/* _hoops_GHARP _hoops_RPGP */
		a = _hoops_HSHGA / sc->_hoops_HICAH.x;
		b = _hoops_ISHGA / sc->_hoops_HICAH.y;
		_hoops_CIPAS = a*a + b*b;
		if (_hoops_CIPAS > sc->_hoops_GICAH) return;

		/* _hoops_SCH'_hoops_GRI _hoops_AIRAI _hoops_PPR _hoops_IRS _hoops_RIRA _hoops_SPR */
	}

	_hoops_GACAS = _hoops_CPRA (elements, image->_hoops_CSAI);
	if (_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) _hoops_GACAS /= _hoops_HGCPC;

	/* _hoops_RPGP _hoops_AHCR */
	if (_hoops_GACAS < sc->bounding.hither || _hoops_GACAS > sc->bounding.yon) return;

	/* _hoops_AA _hoops_SR _hoops_PICP _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_SIGC? */
	if (BIT (sc->options, _hoops_CRPAS)) {
		DC_Point							pts[4];
		bool							_hoops_RCAI = false;

		_hoops_IGRS (dc);

		if (sc->_hoops_GPPAS) {
			void *							_hoops_CCHSP;

			pts[0].x = (float)left;	   pts[0].y = (float)bottom;
			pts[1].x = (float)right;   pts[1].y = (float)bottom;
			pts[2].x = (float)right;   pts[2].y = (float)top;
			pts[3].x = (float)left;	   pts[3].y = (float)top;
			pts[0].z = pts[1].z = pts[2].z = pts[3].z = _hoops_GACAS;

			_hoops_CCHSP = _hoops_AACGH (nr, true);
			_hoops_RSGCP (nr, 4, pts);
			_hoops_PACGH (nr, _hoops_CCHSP);

			if (_hoops_IACGH (nr, _hoops_CCHSP) == 0)
				_hoops_RCAI = true;
		}
		else {
			_hoops_HCSIR alter *	_hoops_ICSIR = null;

			if (nr->_hoops_SAIR->_hoops_ASSIR != null)
				_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
			if (_hoops_ICSIR == null) {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									"Expected frame buffer not found");
				_hoops_RCAI = true;
				goto _hoops_SIPAS;
			}

			pts[0].x = (float)left;	   pts[0].y = (float)bottom;
			pts[1].x = (float)right;   pts[1].y = (float)bottom;
			pts[2].x = (float)left;	   pts[2].y = (float)top;
			pts[3].x = (float)right;   pts[3].y = (float)top;
			pts[0].z = pts[1].z = pts[2].z = pts[3].z = _hoops_GACAS;

			_hoops_ICSIR->input.vertex[0].point = &pts[0];
			_hoops_ICSIR->input.vertex[1].point = &pts[1];
			_hoops_ICSIR->input.vertex[2].point = &pts[2];
			_hoops_ICSIR->input.vertex[3].point = &pts[3];

			_hoops_ICSIR->input._hoops_PHHSP = 0;
			HD_SZB_Process_Rectangle (nr);
			if (_hoops_ICSIR->input._hoops_PHHSP == 0)
				_hoops_RCAI = true;
		}

	  _hoops_SIPAS:
		_hoops_SGRS (dc);
		if (_hoops_RCAI)
			return;
	}

	/* _hoops_AICP _hoops_SCH. */

	if (BIT (_hoops_IHCR->flags, _hoops_CSP)) {
		DC_Point					start;
		DC_Point					end;
		float						_hoops_RGRHI = _hoops_SRCAS + (image->height - 1);
		struct _hoops_AICCP			info;
		Display_Context alter	*_hoops_RACAS = sc->_hoops_SRA;

		_hoops_HGCGA (_hoops_RACAS, "select image", nr);
		_hoops_RACAS->_hoops_IPCI->_hoops_HPCGA = _hoops_PRCAS;

		info._hoops_HHGGH = sc->_hoops_GICAH;
		info._hoops_RRCAS = -1;
		info._hoops_ARCAS = -1;
		sc->_hoops_AICCP = (void alter *)&info;

		start.x = (float)left;
		start.y = (float)top;
		start.z = _hoops_GACAS;

		end.x = (float)right;
		end.y = (float)bottom;
		end.z = _hoops_GACAS;

		HD_Draw_Trimmed_DC_Image (nr, &start, &end,
								  left - (int)_hoops_CRCAS, image->format, 0,
								  image->rasters + (top - (int)_hoops_RGRHI),
								  FP_SOLID, null, null);

		_hoops_HGSGA (_hoops_RACAS, "select image");

		if (info._hoops_RRCAS >= 0)
			HD_Elaborate_Selection (nr, dc->_hoops_RAI,
									dc->_hoops_RAI->key, _hoops_AIRIR(dc->_hoops_RAI),
									info._hoops_RRCAS - (int)_hoops_CRCAS, (int)_hoops_RGRHI - info._hoops_ARCAS, 0,
									_hoops_GACAS, info._hoops_HHGGH, T_IMAGES, null);
	}
	else {
		if (_hoops_HSHGA < 0.0f)
			offset1 = 0;
		else if (_hoops_HSHGA > 0.0f)
			offset1 = image->width - 1;
		else
			offset1 = (int)sc->_hoops_AICAH.x - (int)_hoops_CRCAS;

		if (_hoops_ISHGA < 0.0f)
			offset2 = image->height - 1;
		else if (_hoops_ISHGA > 0.0f)
			offset2 = 0;
		else
			offset2 = (image->height - 1) -
					  ((int)sc->_hoops_AICAH.y - (int)_hoops_SRCAS);

		HD_Elaborate_Selection (nr, dc->_hoops_RAI,
								dc->_hoops_RAI->key, _hoops_AIRIR(dc->_hoops_RAI),
								offset1, offset2, 0,
								_hoops_GACAS, _hoops_CIPAS, T_IMAGES, null);
	}
#endif
}

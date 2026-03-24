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
 * $Id: obf_tmp.txt 1.235 2010-10-27 00:51:29 covey Exp $
 */


#include "hoops.h"
#include "database.h"
#include "please.h"		/* _hoops_HSRR _hoops_CPCSS _hoops_HSH */
#include "driver.h"
#include "select.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "adt.h"


#ifndef DISABLE_SELECTION

/*
 * _hoops_AHGHR _hoops_SISR & _hoops_HAPC _hoops_GGR _hoops_CSHCR _hoops_IIGR -1..1 _hoops_PCRR _hoops_GIAA _hoops_RH _hoops_CGRHH _hoops_RPPS,
 * _hoops_IPSH _hoops_RH _hoops_APHR _hoops_CAGH, _hoops_SSS _hoops_RH _hoops_SRSHR, _hoops_RPP _hoops_GII.
 *
 * _hoops_GIGHR: _hoops_HCPPH->_hoops_SPCSS _hoops_GPGH'_hoops_RA _hoops_RPHR _hoops_IH _hoops_CPAP
 *
 * _hoops_GIGHR: _hoops_RPP _hoops_IIH _hoops_CSAP _hoops_PCCP _hoops_RIHH _hoops_GPP _hoops_RH _hoops_CGHI _hoops_PAAP, _hoops_SR _hoops_CGH _hoops_PAHH
 *		 _hoops_HAR _hoops_HPPR _hoops_RGR, _hoops_CR _hoops_IIH'_hoops_GRI _hoops_CRGP _hoops_RIHH _hoops_IPAC _hoops_ARI.
 */


local void _hoops_GHCSS (
	Net_Rendition const &		nr,
	Window_Tree alter *			_hoops_ACCAA) {

	_hoops_ACCAA->_hoops_RRPAS.left = _hoops_ACCAA->window.left = -1.0f;
	_hoops_ACCAA->_hoops_RRPAS.right = _hoops_ACCAA->window.right = 1.0f;
	_hoops_ACCAA->_hoops_RRPAS.bottom = _hoops_ACCAA->window.bottom = -1.0f;
	_hoops_ACCAA->_hoops_RRPAS.top = _hoops_ACCAA->window.top = 1.0f;

	_hoops_ACCAA->_hoops_AAICA = nr->_hoops_IRR->_hoops_AAICA;
	_hoops_ACCAA->restricted_selectability = nr->_hoops_IRR->restricted_selectability;
	_hoops_ACCAA->_hoops_PHARP = nr->_hoops_IRR->_hoops_PHARP;
	_hoops_ACCAA->_hoops_RGP = nr->_hoops_RGP;
}



#ifndef DISABLE_POLY_SELECTION
/*
 * _hoops_SP _hoops_GGSR _hoops_RHCSS _hoops_GHSHA _hoops_AAAPR
 */
local void _hoops_AHCSS (
	_hoops_ACCCP alter	*		sc) {

	if (sc->_hoops_HAPAS != null) {
		HI_Free_Wedge_Tree (sc->_hoops_HAPAS);
		sc->_hoops_HAPAS = null;
	}

	if (sc->_hoops_SAPAS != null) {
		HI_Free_Wings (sc->_hoops_CAPAS, sc->_hoops_SAPAS);
		sc->_hoops_SAPAS = null;
		sc->_hoops_CAPAS = 0;
	}

	/*
	 * _hoops_PGISI _hoops_PSPAR _hoops_PPR _hoops_PHCSS _hoops_HS _hoops_RPR-1 _hoops_IAGH
	 */
	if (sc->_hoops_AAPAS != null) {
		FREE_ARRAY (sc->_hoops_AAPAS, sc->count - 1, Vector);
		sc->_hoops_AAPAS = null;
	}
	if (sc->_hoops_PAPAS != null) {
		FREE_ARRAY (sc->_hoops_PAPAS, sc->count - 1, float);
		sc->_hoops_PAPAS = null;
	}

	if (sc->_hoops_RAPAS != null) {
		FREE_ARRAY (sc->_hoops_RAPAS, sc->count, Point);
		sc->_hoops_RAPAS = null;
	}

	sc->count = 0;
}



local void _hoops_HHCSS (
	_hoops_ACCCP alter *	sc,
	Point alter *				scale,
	Point alter *				translate) {

	/*
	 * _hoops_GAGA _hoops_SCIRA _hoops_RSSA _hoops_HII _hoops_RH _hoops_GHSHA _hoops_PGRRR _hoops_GC _hoops_IS
	 * _hoops_RHIR _hoops_RH _hoops_CSRA & _hoops_PHCH _hoops_IS _hoops_IRHH _hoops_SCIRA _hoops_RSSA _hoops_IH _hoops_RH
	 * _hoops_GHSHA _hoops_GGSC.  _hoops_GPGP _hoops_RH _hoops_HPPP, _hoops_SSS _hoops_RH _hoops_IHCSS.
	 */
	{
		int				count = sc->event->count;
		Point alter	*	_hoops_GIISA = sc->event->_hoops_HARIR;
		Point alter	*	_hoops_HHCSA;

		sc->count = count;
		ALLOC_ARRAY (_hoops_HHCSA, count, Point);
		sc->_hoops_RAPAS = _hoops_HHCSA;

		sc->_hoops_GPIS.x = 0.0f;
		sc->_hoops_GPIS.y = 0.0f;

		while (count-- > 0) {
			_hoops_HHCSA->x = _hoops_GIISA->x * scale->x + translate->x;
			sc->_hoops_GPIS.x += _hoops_HHCSA->x;

			_hoops_HHCSA->y = _hoops_GIISA->y * scale->y + translate->y;
			sc->_hoops_GPIS.y += _hoops_HHCSA->y;

			_hoops_HHCSA->z = 0.0f;

			++_hoops_GIISA;
			++_hoops_HHCSA;
		}

		sc->_hoops_GPIS.x /= sc->count;
		sc->_hoops_GPIS.y /= sc->count;
	}


	/*
	 * _hoops_SSSA _hoops_IRS _hoops_GCHPA _hoops_HHIS _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_PRHAI _hoops_HPP _hoops_HSSP
	 */
	if (!BIT (sc->options, _hoops_PRPAS))
		sc->_hoops_HAPAS = null;
	else {
		Vector		_hoops_RRASA, _hoops_HIHHA;

		_hoops_RRASA.x = sc->_hoops_RAPAS[0].x - sc->_hoops_GPIS.x;
		_hoops_RRASA.y = sc->_hoops_RAPAS[0].y - sc->_hoops_GPIS.y;

		_hoops_HIHHA.x = sc->_hoops_RAPAS[1].x - sc->_hoops_GPIS.x;
		_hoops_HIHHA.y = sc->_hoops_RAPAS[1].y - sc->_hoops_GPIS.y;

		sc->_hoops_IAPAS = (_hoops_RRASA.x * _hoops_HIHHA.y > _hoops_HIHHA.x * _hoops_RRASA.y);

		if (sc->_hoops_HAPAS != null)
			HI_Free_Wedge_Tree (sc->_hoops_HAPAS);
		sc->_hoops_HAPAS = HI_Create_Polygon_Wedge_Tree (sc->count, sc->_hoops_RAPAS,
													   &sc->_hoops_GPIS,
													   sc->_hoops_IAPAS);
	}


	/*
	 * _hoops_SSSA _hoops_ISII _hoops_PSPAR _hoops_PPR _hoops_IHHA
	 */
	{
		float			length;
		int				_hoops_SIIRR = sc->count - 1;
		Point alter	*	_hoops_CHCSS = &sc->_hoops_RAPAS[0];
		Vector alter *	_hoops_SHCSS;
		float alter *	_hoops_GICSS;

		ALLOC_ARRAY (_hoops_SHCSS, _hoops_SIIRR, Vector);
		sc->_hoops_AAPAS = _hoops_SHCSS;
		ALLOC_ARRAY (_hoops_GICSS, _hoops_SIIRR, float);
		sc->_hoops_PAPAS = _hoops_GICSS;

		_hoops_RGGA (_hoops_SIIRR-- <= 0) {
			_hoops_SHCSS->x = _hoops_CHCSS[1].x - _hoops_CHCSS[0].x;
			_hoops_SHCSS->y = _hoops_CHCSS[1].y - _hoops_CHCSS[0].y;
			_hoops_SHCSS->z = 0.0f;

			*_hoops_GICSS = length = _hoops_SGIHR (_hoops_SHCSS->x * _hoops_SHCSS->x +
										_hoops_SHCSS->y * _hoops_SHCSS->y);
			if (length > 0.0f)
				length = 1.0f / length;
			else
				length = 1.0f;

			_hoops_SHCSS->x *= length;
			_hoops_SHCSS->y *= length;

			++_hoops_CHCSS;
			++_hoops_SHCSS;
			++_hoops_GICSS;
		}
	}

	{
		bool		polygon = BIT (sc->options, _hoops_PRPAS);

		sc->_hoops_CAPAS = HI_Create_Polyglin_Wings (sc->count - (polygon ? 1:0),
												   sc->_hoops_RAPAS,
												   polygon,
												   _hoops_SRPAS,
												   &sc->_hoops_SAPAS);
	}
}
#endif



local bool _hoops_RICSS (
	_hoops_ACCCP alter	*	sc,
	Net_Rendition const &		nr,
	Window_Tree alter *			_hoops_AICSS) {
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	Selection_Event alter *		_hoops_GPIIR = sc->event;
	Point						_hoops_PICSS;
	Point						_hoops_HICSS;


	if (_hoops_GPIIR->_hoops_GHIIR != null) {
		/* _hoops_GGARP _hoops_RPPS _hoops_PCRR */
		sc->bounding.left	= _hoops_GPIIR->_hoops_IHSHA.left;
		sc->bounding.right	= _hoops_GPIIR->_hoops_IHSHA.right;
		sc->bounding.bottom = _hoops_GPIIR->_hoops_IHSHA.bottom;
		sc->bounding.top	= _hoops_GPIIR->_hoops_IHSHA.top;

		_hoops_PICSS.x = 1.0f;
		_hoops_PICSS.y = 1.0f;
		_hoops_PICSS.z = 1.0f;

		_hoops_HICSS.x = 0.0f;
		_hoops_HICSS.y = 0.0f;
		_hoops_HICSS.z = 0.0f;
	}
	else {
		_hoops_PACIR	_hoops_IICSS;

		_hoops_IICSS.left   = _hoops_GPIIR->_hoops_IHSHA.left;
		_hoops_IICSS.right  = _hoops_GPIIR->_hoops_IHSHA.right;
		_hoops_IICSS.bottom = _hoops_GPIIR->_hoops_IHSHA.bottom;
		_hoops_IICSS.top	   = _hoops_GPIIR->_hoops_IHSHA.top;

		if (_hoops_IICSS.left   < _hoops_AICSS->_hoops_RRPAS.left)
			_hoops_IICSS.left   = _hoops_AICSS->_hoops_RRPAS.left;
		if (_hoops_IICSS.right  > _hoops_AICSS->_hoops_RRPAS.right)
			_hoops_IICSS.right  = _hoops_AICSS->_hoops_RRPAS.right;
		if (_hoops_IICSS.bottom < _hoops_AICSS->_hoops_RRPAS.bottom)
			_hoops_IICSS.bottom = _hoops_AICSS->_hoops_RRPAS.bottom;
		if (_hoops_IICSS.top	   > _hoops_AICSS->_hoops_RRPAS.top)
			_hoops_IICSS.top	   = _hoops_AICSS->_hoops_RRPAS.top;

		_hoops_PICSS.x = 2.0f / (_hoops_AICSS->window.right - _hoops_AICSS->window.left);
		_hoops_HICSS.x = -_hoops_AICSS->window.left * _hoops_PICSS.x - 1.0f;
		sc->bounding.left  = _hoops_IICSS.left  * _hoops_PICSS.x + _hoops_HICSS.x;
		sc->bounding.right = _hoops_IICSS.right * _hoops_PICSS.x + _hoops_HICSS.x;

		_hoops_PICSS.y = 2.0f / (_hoops_AICSS->window.top - _hoops_AICSS->window.bottom);
		_hoops_HICSS.y = -_hoops_AICSS->window.bottom * _hoops_PICSS.y - 1.0f;
		sc->bounding.bottom = _hoops_IICSS.bottom * _hoops_PICSS.y + _hoops_HICSS.y;
		sc->bounding.top	= _hoops_IICSS.top	 * _hoops_PICSS.y + _hoops_HICSS.y;

		_hoops_PICSS.z = 1.0f;
		_hoops_HICSS.z = 0.0f;

		sc->xw = (sc->bounding.left + sc->bounding.right) * 0.5f;
		sc->yw = (sc->bounding.bottom + sc->bounding.top) * 0.5f;
	}
	sc->bounding.hither = _hoops_GPIIR->_hoops_IHSHA.hither;
	sc->bounding.yon	= _hoops_GPIIR->_hoops_IHSHA.yon;


	if (!BIT (sc->options, _hoops_IICAH)) {
		Point				scale;
		Point				translate;

		HD_Compute_Screen_Transform (nr, &scale, &translate);

		/* _hoops_CICSS _hoops_CHASA _hoops_SISR _hoops_PPR _hoops_HAPC _hoops_AHGGR */
		scale.x = (_hoops_SGRA->_hoops_PHRA.right - _hoops_SGRA->_hoops_PHRA.left) * 0.5f;
		scale.y = (_hoops_SGRA->_hoops_PHRA.top - _hoops_SGRA->_hoops_PHRA.bottom) * 0.5f;
		translate.x = (_hoops_SGRA->_hoops_PHRA.right + _hoops_SGRA->_hoops_PHRA.left) * 0.5f;
		translate.y = (_hoops_SGRA->_hoops_PHRA.top + _hoops_SGRA->_hoops_PHRA.bottom) * 0.5f;

		sc->bounding.left	= sc->bounding.left	  * scale.x + translate.x;
		sc->bounding.right	= sc->bounding.right  * scale.x + translate.x;
		sc->bounding.bottom = sc->bounding.bottom * scale.y + translate.y;
		sc->bounding.top	= sc->bounding.top	  * scale.y + translate.y;

		if (sc->bounding.left	- _hoops_SGRA->_hoops_PHRA.right	>  0.001f ||
			sc->bounding.right	- _hoops_SGRA->_hoops_PHRA.left	< -0.001f ||
			sc->bounding.bottom - _hoops_SGRA->_hoops_PHRA.top	>  0.001f ||
			sc->bounding.top	- _hoops_SGRA->_hoops_PHRA.bottom < -0.001f)
			return false;

		if (sc->bounding.left	< (float)_hoops_SGRA->_hoops_PHRA.left)
			sc->bounding.left	= (float)_hoops_SGRA->_hoops_PHRA.left;
		if (sc->bounding.right	> (float)_hoops_SGRA->_hoops_PHRA.right)
			sc->bounding.right	= (float)_hoops_SGRA->_hoops_PHRA.right;
		if (sc->bounding.bottom < (float)_hoops_SGRA->_hoops_PHRA.bottom)
			sc->bounding.bottom = (float)_hoops_SGRA->_hoops_PHRA.bottom;
		if (sc->bounding.top	> (float)_hoops_SGRA->_hoops_PHRA.top)
			sc->bounding.top	= (float)_hoops_SGRA->_hoops_PHRA.top;

		sc->bounding.hither = sc->bounding.hither * scale.z + translate.z;
		sc->bounding.yon	= sc->bounding.yon	  * scale.z + translate.z;

		translate.x += scale.x * _hoops_HICSS.x;
		translate.y += scale.y * _hoops_HICSS.y;
		translate.z += scale.z * _hoops_HICSS.z;
		scale.x *= _hoops_PICSS.x;
		scale.y *= _hoops_PICSS.y;
		scale.z *= _hoops_PICSS.z;

#ifndef DISABLE_POLY_SELECTION
		if (_hoops_GPIIR->count > 0) {
			if (sc->count > 0)
				_hoops_AHCSS (sc);
			_hoops_HHCSS (sc, &scale, &translate);
		}
#endif
	}


	sc->_hoops_AICAH.x = (sc->bounding.left + sc->bounding.right) * 0.5f;
	sc->_hoops_AICAH.y = (sc->bounding.bottom + sc->bounding.top) * 0.5f;
	sc->_hoops_AICAH.z = 0.0f;

	return true;
}



local _hoops_RISAP alter * _hoops_SICSS (
	Window_Tree alter	*			_hoops_PACAS) {
	_hoops_RISAP alter	*			_hoops_HACAH = null;
	_hoops_RISAP alter	* alter *	_hoops_ASRGR = &_hoops_HACAH;

	do if (_hoops_PACAS->_hoops_GIPIA->type == _hoops_AGRPR) {
		_hoops_RISAP alter	*		_hoops_GCCSS;

		ALLOC (_hoops_GCCSS, _hoops_RISAP);
		_hoops_GCCSS->include = (_hoops_PGRPR alter *)_hoops_PACAS->_hoops_GIPIA;
		_hoops_GCCSS->prev = null;
		*_hoops_ASRGR = _hoops_GCCSS;
		_hoops_ASRGR = &_hoops_GCCSS->prev;
	} while ((_hoops_PACAS = _hoops_PACAS->_hoops_SCAAR) != null);

	return _hoops_HACAH;
}


local void _hoops_RCCSS (
	_hoops_RISAP alter	*			_hoops_HACAH) {
	_hoops_RISAP alter	*			prev;

	if (_hoops_HACAH != null) do {
		prev = _hoops_HACAH->prev;
		FREE (_hoops_HACAH, _hoops_RISAP);
	} while ((_hoops_HACAH = prev) != null);
}


local void _hoops_ACCSS (
	_hoops_ACCCP alter	*		sc,
	_hoops_RPIIR alter *			si) {

	if (BIT (sc->options, _hoops_IICAH)) {
		do {
			si->_hoops_RCSAP = si->_hoops_PCSAP;

			si->xc = si->xw;
			si->yc = si->yw;
			si->zc = si->_hoops_RCSAP;

			si->_hoops_APHGA = null;
		} while ((si = si->next) != null);
	}
	else {
		do {
			Net_Rendition const &	nr = si->_hoops_APHGA;
			_hoops_HHRA const *			_hoops_SPH = nr->transform_rendition->_hoops_SPH;
			Point					scale,
									translate;

			/* _hoops_GCIH _hoops_HPP _hoops_GHGA _hoops_RH _hoops_PSHR _hoops_AHAP _hoops_GAR _hoops_PCCSS! */

			HD_Compute_Screen_Transform (nr, &scale, &translate);

			if (scale.x == 0.0f || scale.y == 0.0f || scale.z == 0.0f) {
				/* _hoops_PIHA _hoops_SHH _hoops_IRS _hoops_ARHAR _hoops_SHPR _hoops_RPPS, _hoops_SAHR _hoops_CISA _hoops_GGR _hoops_CPHP */
				si->_hoops_RCSAP = si->_hoops_PCSAP;

				si->xc = si->xw;
				si->yc = si->yw;
				si->zc = si->_hoops_RCSAP;
			}
			else {
				si->_hoops_RCSAP = (si->_hoops_PCSAP - translate.z) / scale.z;

				if (_hoops_SPH->_hoops_GRCC._hoops_APRA == null)
					HI_Validate_Matrix_Adjoint (&_hoops_SPH->_hoops_GRCC);

				{
					_hoops_RPRA const *		_hoops_APRA = _hoops_SPH->_hoops_GRCC._hoops_APRA->data.elements;
					float					x, y, z, w;

					/* _hoops_RH _hoops_SARA _hoops_AGICR _hoops_HRGR _hoops_RCPGR _hoops_GAPA _hoops_HGISR, _hoops_HIS _hoops_HCCSS _hoops_GPP
					 * _hoops_ISCP _hoops_ICCSS _hoops_PPR _hoops_SGH _hoops_SGS _hoops_HRII _hoops_HSAR _hoops_RH _hoops_AGICR _hoops_IIGR _hoops_RH _hoops_RRI
					 * _hoops_SICHR _hoops_RICC->_hoops_RSGA.
					 */


					/* _hoops_CCCSS... */

					x = (sc->_hoops_AICAH.x - translate.x) / scale.x;
					y = (sc->_hoops_AICAH.y - translate.y) / scale.y;
					z = si->_hoops_RCSAP;

					/* _hoops_AGGA, _hoops_PAISR _hoops_RH _hoops_SARA _hoops_HPP _hoops_RRPRA _hoops_RH _hoops_AGICR (_hoops_IGRC _hoops_RH _hoops_GGRA)*/

					if (_hoops_SPH->projection != _hoops_GHH)
						w = _hoops_APRA[3][3];
					else
						w = _hoops_APRA[0][3] * x +
							_hoops_APRA[1][3] * y +
							_hoops_APRA[2][3] * z +
							_hoops_APRA[3][3];

					if (w == 0.0f)
						w = 1.0f;		/* ?? (_hoops_SRCH _hoops_GSGRC) */

					si->xc = (_hoops_APRA[0][0] * x +
							  _hoops_APRA[1][0] * y +
							  _hoops_APRA[2][0] * z +
							  _hoops_APRA[3][0]) / w;
					si->yc = (_hoops_APRA[0][1] * x +
							  _hoops_APRA[1][1] * y +
							  _hoops_APRA[2][1] * z +
							  _hoops_APRA[3][1]) / w;
					si->zc = (_hoops_APRA[0][2] * x +
							  _hoops_APRA[1][2] * y +
							  _hoops_APRA[2][2] * z +
							  _hoops_APRA[3][2]) / w;
				}
			}

			si->_hoops_APHGA = null;
		} while ((si = si->next) != null);
	}
}


local Window_Tree alter * _hoops_SCCSS (
	_hoops_CRCP const *				_hoops_SRCP,
	Window_Tree alter * alter *	_hoops_GSCSS) {
	Window_Tree alter *			_hoops_PACAS;
	Window_Tree alter *			_hoops_ACCAA;

	ZALLOC (_hoops_PACAS, Window_Tree);
	_hoops_PACAS->_hoops_SRCP = _hoops_SRCP;
	_hoops_PACAS->_hoops_GIPIA = (Subsegment alter *)_hoops_SRCP;
	_hoops_PACAS->_hoops_SGPAS = true;

	_hoops_ACCAA = _hoops_PACAS;

	_hoops_SRCP = _hoops_SRCP->owner;
	while (_hoops_SRCP->type != _hoops_PRAIR) {
		Window_Tree alter	*_hoops_RSCSS;

		ZALLOC (_hoops_RSCSS, Window_Tree);
		_hoops_RSCSS->_hoops_ICHSP = _hoops_PACAS;
		_hoops_RSCSS->_hoops_SRCP = _hoops_SRCP;
		_hoops_RSCSS->_hoops_GIPIA = (Subsegment alter *)_hoops_SRCP;
		_hoops_RSCSS->_hoops_SGPAS = true;

		_hoops_PACAS->_hoops_SCAAR = _hoops_RSCSS;
		_hoops_PACAS = _hoops_RSCSS;

		_hoops_SRCP = _hoops_SRCP->owner;
	}

	_hoops_PACAS->_hoops_SCAAR = null;
	*_hoops_GSCSS = _hoops_PACAS;
	return _hoops_ACCAA;
}


local void _hoops_AACAS (
	Window_Tree alter *		_hoops_PACAS) {
	Window_Tree alter *		next;

	do {
		next = _hoops_PACAS->_hoops_ICHSP;
		if (_hoops_PACAS->_hoops_CGPAS != null) { /* (_hoops_IIGSH _hoops_AGIR) */
			if (next != null) _hoops_AACAS (next);
			next = _hoops_PACAS->_hoops_CGPAS;
		}
		FREE (_hoops_PACAS, Window_Tree);
	} while ((_hoops_PACAS = next) != null);
}


local bool _hoops_ASCSS (
	Window_Tree alter *		_hoops_AICSS) {

	/* _hoops_SR _hoops_HGCR _hoops_SRS _hoops_RPSI _hoops_IS _hoops_ISPR, _hoops_PSCR _hoops_GCHGA _hoops_RHIR _hoops_RH _hoops_ACSP */
	do {
		/* _hoops_RPPS _hoops_ARI? */
		if (BIT (_hoops_AICSS->_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR))
			return true;

		/* _hoops_AA _hoops_GII _hoops_IIGR _hoops_RGCI _hoops_RASI _hoops_HS _hoops_SPHGR? */
		if (_hoops_AICSS->_hoops_ICHSP != null) {
			if (_hoops_ASCSS (_hoops_AICSS->_hoops_ICHSP))
				return true;
		}

		/* _hoops_HGGC _hoops_PIRC, _hoops_HPPR _hoops_RH _hoops_SPS */
	} while ((_hoops_AICSS = _hoops_AICSS->_hoops_CGPAS) != null);

	/* _hoops_PIRC _hoops_GSGI! */
	return false;
}


local bool _hoops_PSCSS (
	Window_Tree alter *		_hoops_AICSS) {

	/* _hoops_SR _hoops_HGCR _hoops_SRS _hoops_RPSI _hoops_IS _hoops_ISPR, _hoops_PSCR _hoops_GCHGA _hoops_RHIR _hoops_RH _hoops_ACSP */
	do {
		/* _hoops_HRGR _hoops_RGR _hoops_RPSI _hoops_CIGC? */
		if (BIT (_hoops_AICSS->_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR) &&
			(_hoops_AICSS->_hoops_SGPAS || !BIT (_hoops_AICSS->_hoops_SRCP->_hoops_PHSI, _hoops_RCHGP)))
			 return false;

		/* _hoops_CHR _hoops_GII _hoops_IIGR _hoops_RGCI _hoops_RASI _hoops_CIGC? */
		if (_hoops_AICSS->_hoops_ICHSP != null) {
			if (!_hoops_PSCSS (_hoops_AICSS->_hoops_ICHSP))
				return false;
		}

		/* _hoops_HGGC _hoops_IHRI, _hoops_HPPR _hoops_RH _hoops_SPS */
	} while ((_hoops_AICSS = _hoops_AICSS->_hoops_CGPAS) != null);

	/* _hoops_PIHA _hoops_SHH _hoops_HCR _hoops_IHRI! */
	return true;
}


local Net_Rendition _hoops_HSCSS (
	Net_Rendition const &			inr,
	_hoops_CRCP const *					_hoops_SRCP) {
	Net_Rendition					nr = inr;

	if (_hoops_SRCP->_hoops_PAGSA() == 0 &&
		nr->transform_rendition->_hoops_RGH == null)
		return nr; /* _hoops_IAGRS */

	/* _hoops_GCRR _hoops_IRS _hoops_CASI _hoops_CPSP _hoops_IS _hoops_IPHR _hoops_GPP */
	_hoops_HHCR alter &		_hoops_IHCR = nr.Modify()->transform_rendition.Modify();

	/* _hoops_ACGR _hoops_CAPR */
	HD_Find_Cutting_Planes (nr, _hoops_SRCP);

	if (_hoops_IHCR->_hoops_RGH != null) {
		/* _hoops_CGP _hoops_GSGI, _hoops_AHGRH _hoops_CGSI */

		if (BIT (nr->_hoops_SRA->_hoops_APHHP->options, _hoops_IICAH)) {
			_hoops_GPPA alter		*_hoops_IRCAR;

			/* _hoops_GCRR '_hoops_CSPH' _hoops_GHC _hoops_RH _hoops_PSHR _hoops_GAR _hoops_GSSP _hoops_GHC, _hoops_GGR _hoops_AGIR
			 * _hoops_HRCC _hoops_APSI _hoops_IS _hoops_SGH _hoops_CAPR.
			 */
			_hoops_IRCAR = (_hoops_GPPA alter *)
				_hoops_IHCR->_hoops_RGH->_hoops_PHCA->_hoops_APPA;
			do {
				_hoops_IRCAR->_hoops_SPPA.a = _hoops_IRCAR->_hoops_SHPA.a;
				_hoops_IRCAR->_hoops_SPPA.b = _hoops_IRCAR->_hoops_SHPA.b;
				_hoops_IRCAR->_hoops_SPPA.c = _hoops_IRCAR->_hoops_SHPA.c;
				_hoops_IRCAR->_hoops_SPPA.d = _hoops_IRCAR->_hoops_SHPA.d;
			} while ((_hoops_IRCAR = (_hoops_GPPA alter *)_hoops_IRCAR->next) != null);

			_hoops_IHCR->flags &= ~_hoops_HHGGA;
		}
		else {
			/* _hoops_GCRR _hoops_RCRR _hoops_ISCSS _hoops_CHR _hoops_CCCI */
			if (!BIT (_hoops_IHCR->flags, _hoops_HHGGA)) {
				HD_Set_DC_Cutting_Planes (nr);
				_hoops_IHCR->flags |= _hoops_HHGGA;
			}
		}

		/* _hoops_PHIC _hoops_IGH _hoops_SR'_hoops_ASAR _hoops_GHGA _hoops_RGR *_hoops_RPHR _hoops_HA* */
		if (BIT (nr->_hoops_RGP, T_CUTTING_PLANES))
			_hoops_IHCR->flags |= _hoops_CSP;
	}

	return nr;
}


struct _hoops_CSCSS : public _hoops_HIGGH {
	public:
		_hoops_CSCSS ()  {}
		bool _hoops_PPCRR (Net_Rendition alter & nr, _hoops_CRCP const * _hoops_SRCP, _hoops_HICS const & path);
};

bool _hoops_CSCSS::_hoops_PPCRR (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path) {
	_hoops_GRGH				_hoops_RRGH = nr->_hoops_IRR;
	UNREFERENCED (_hoops_SRCP);
	UNREFERENCED (path);

	if (ANYBIT (nr->_hoops_RCSHR, _hoops_CRSI|_hoops_SRSI)) {
		if (_hoops_RRGH->_hoops_AAICA == 0 && _hoops_RRGH->_hoops_PHARP == 0)
			return false;

		nr.Modify();
		nr->_hoops_RCSHR &= ~(_hoops_CRSI|_hoops_SRSI);
		nr->current &= ~(_hoops_CRSI|_hoops_SRSI);
	}

	return true;
}


local void elaborate_leaves (
	Net_Rendition const &	nr,
	Window_Tree *			_hoops_AICSS,
	bool					_hoops_SSCSS);


local void _hoops_GGSSS (
	Net_Rendition const &		inr,
	Window_Tree alter *			_hoops_AICSS,
	bool						_hoops_SSCSS) {
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter *	sc = dc->_hoops_APHHP;

	UNREFERENCED (_hoops_SSCSS);

	if (_hoops_AICSS->_hoops_CGPAS != null)
		_hoops_GGSSS (nr, _hoops_AICSS->_hoops_CGPAS, true);

	if (sc->_hoops_GHPPI)
		return;

	nr.Modify()->_hoops_IRR.Modify();		  /* _hoops_HGCR _hoops_SPR _hoops_IS _hoops_GRPHA */
	if (_hoops_AICSS->_hoops_SRCP->_hoops_IPPGR != null)
		HD_Selection_Downwind (nr, _hoops_AICSS->_hoops_SRCP->_hoops_IPPGR);
	elaborate_leaves (nr, _hoops_AICSS, true);
}


local void elaborate_leaves (
	Net_Rendition const &		inr,
	Window_Tree alter *			_hoops_AICSS,
	bool						_hoops_SSCSS) {
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter *	sc = dc->_hoops_APHHP;
	Selection_Event alter *		_hoops_GPIIR = sc->event;
	Activity					_hoops_RGSSS = dc->_hoops_CPGPR;
	Activity					_hoops_AGSSS = _hoops_AICSS->_hoops_SRCP->_hoops_CPGPR;
	_hoops_GRGH				_hoops_RRGH = nr->_hoops_IRR;
	_hoops_HHCR			_hoops_IHCR;
	_hoops_CGRA			_hoops_SGRA;
	_hoops_ACHR					_hoops_PGSSS;
	int i;

	/* _hoops_IRHH _hoops_RCRR _hoops_SGS _hoops_RH _hoops_SCGR _hoops_HGSSS, _hoops_AHI. _hoops_RRGPR _hoops_CIAH _hoops_IH
	 * _hoops_RGR _hoops_RPPS (_hoops_HAR _hoops_IRS _hoops_CRRIR _hoops_HII _hoops_IRS _hoops_RRH _hoops_IGSSS) */
	_hoops_RRGH->_hoops_AAICA = _hoops_AICSS->_hoops_AAICA;
	_hoops_RRGH->restricted_selectability = _hoops_AICSS->restricted_selectability;
	_hoops_RRGH->_hoops_PHARP = _hoops_AICSS->_hoops_PHARP;
	_hoops_RRGH->_hoops_AARIP = _hoops_AICSS->_hoops_RGP;

	nr->_hoops_RGP = _hoops_AICSS->_hoops_RGP;

	if (!BIT (sc->options, _hoops_IICAH))
		nr = _hoops_HSCSS (nr, _hoops_AICSS->_hoops_SRCP);

	if (_hoops_SSCSS) _hoops_PCCAR {
		if (_hoops_AICSS->_hoops_ICHSP == null) break;

		if (ANYBIT (_hoops_AICSS->_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR) &&
			!BIT (_hoops_AICSS->_hoops_SRCP->_hoops_PHSI, _hoops_RCHGP) &&
			_hoops_ASCSS (_hoops_AICSS->_hoops_ICHSP) &&
			_hoops_PSCSS (_hoops_AICSS->_hoops_ICHSP)) {
			/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_HPGR _hoops_PCCP _hoops_CIGC _hoops_RPPS _hoops_CCA _hoops_RGAR _hoops_RRH _hoops_HGHIP,
			 * _hoops_SR _hoops_PIHA _hoops_HSPP _hoops_CCA _hoops_IRS _hoops_GHSHA _hoops_HII _hoops_ARI, _hoops_GAR _hoops_PA _hoops_HII _hoops_ARI
			 * _hoops_ISHP (_hoops_PGAP _hoops_HRGR _hoops_HAR _hoops_GIAA _hoops_IRS _hoops_CGSSS) _hoops_SIAS _hoops_SHH _hoops_PACIA _hoops_RHIR
			 * _hoops_RH _hoops_RRH _hoops_RPSI[_hoops_SGSSS] */
			Net_Rendition		_hoops_PPHIP = nr;

			_hoops_PPHIP.Modify()->_hoops_IRR.Modify();			  /* _hoops_HGCR _hoops_SPR _hoops_IS _hoops_GRPHA */
			elaborate_leaves (_hoops_PPHIP, _hoops_AICSS, false);

			if (sc->_hoops_GHPPI)
				goto _hoops_HPAGR;
		}

		_hoops_AICSS = _hoops_AICSS->_hoops_ICHSP;
		_hoops_AGSSS = _hoops_AICSS->_hoops_SRCP->_hoops_CPGPR;

		if (_hoops_AICSS->_hoops_CGPAS != null)
			_hoops_GGSSS (nr, _hoops_AICSS->_hoops_CGPAS, true);

		if (sc->_hoops_GHPPI) goto _hoops_HPAGR;

		if (_hoops_AICSS->_hoops_SRCP->_hoops_IPPGR != null) {
			HD_Selection_Downwind (nr, _hoops_AICSS->_hoops_SRCP->_hoops_IPPGR);
			_hoops_RRGH = nr->_hoops_IRR;

			if (BIT (_hoops_AICSS->_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR) &&
				!BIT (sc->options, _hoops_IICAH) &&
				!BIT (nr->transform_rendition->flags, _hoops_ASPIP)) {
				nr.Modify();
				nr->transform_rendition.Modify();
				nr->_hoops_SAIR.Modify();

				HD_Compute_Hard_Clip (nr, null);
				nr = _hoops_HSCSS (nr, _hoops_AICSS->_hoops_SRCP);

				_hoops_IHCR = nr->transform_rendition;
				_hoops_SGRA = nr->_hoops_SAIR;

				_hoops_IHCR->_hoops_AGAA.left		= _hoops_SGRA->_hoops_PHRA.left;
				_hoops_IHCR->_hoops_AGAA.right		= _hoops_SGRA->_hoops_PHRA.right;
				_hoops_IHCR->_hoops_AGAA.bottom	= _hoops_SGRA->_hoops_PHRA.bottom;
				_hoops_IHCR->_hoops_AGAA.top		= _hoops_SGRA->_hoops_PHRA.top;
			}
		}

		_hoops_AICSS->_hoops_AAICA = _hoops_RRGH->_hoops_AAICA;
		_hoops_AICSS->restricted_selectability = _hoops_RRGH->restricted_selectability;
		_hoops_AICSS->_hoops_PHARP = _hoops_RRGH->_hoops_PHARP;
		_hoops_AICSS->_hoops_RGP = nr->_hoops_RGP;
	}

	if (!_hoops_RICSS (sc, nr, _hoops_AICSS)) {
		goto _hoops_HPAGR;
	}

	/* _hoops_ARP _hoops_GH _hoops_IH _hoops_GRSSS */
	sc->_hoops_ASCAH = _hoops_SICSS (_hoops_AICSS);

	/* _hoops_ARP _hoops_GH _hoops_RH _hoops_RPPS _hoops_HIHP... (_hoops_HII _hoops_HPCIP) */

	_hoops_IHCR = nr->transform_rendition;
	_hoops_SGRA = nr->_hoops_SAIR;

	sc->_hoops_GCCIA = nr->_hoops_IRR->_hoops_GCCIA;

	if (BIT (_hoops_SGRA->_hoops_ASIHP, _hoops_AIARP)) {
		_hoops_HRPA			_hoops_RHSPR;

		HD_Undo_Screen (nr, &_hoops_RHSPR);

		_hoops_ARHIP (nr, &_hoops_SGRA->_hoops_PHRA, &_hoops_SGRA->_hoops_RRAIP, true);

		_hoops_SGRA->_hoops_PHRA.left	  += _hoops_SGRA->_hoops_RRAIP.left;
		_hoops_SGRA->_hoops_PHRA.right  -= _hoops_SGRA->_hoops_RRAIP.right;
		_hoops_SGRA->_hoops_PHRA.bottom += _hoops_SGRA->_hoops_RRAIP.bottom;
		_hoops_SGRA->_hoops_PHRA.top	  -= _hoops_SGRA->_hoops_RRAIP.top;

		if (!BIT(_hoops_SGRA->_hoops_ASIHP, _hoops_CIARP)) {
			_hoops_SGRA->_hoops_CIIH.left	= _hoops_SGRA->_hoops_PHRA.left;
			_hoops_SGRA->_hoops_CIIH.right	= _hoops_SGRA->_hoops_PHRA.right;
			_hoops_SGRA->_hoops_CIIH.bottom	= _hoops_SGRA->_hoops_PHRA.bottom;
			_hoops_SGRA->_hoops_CIIH.top	= _hoops_SGRA->_hoops_PHRA.top;
		}

		/* _hoops_HSIH _hoops_AHHSR _hoops_GGCH */
		if (_hoops_SGRA->_hoops_PHRA.right > _hoops_SGRA->_hoops_PHRA.left)
			_hoops_SGRA->_hoops_CSIH = (float)(_hoops_SGRA->_hoops_CIIH.top - _hoops_SGRA->_hoops_CIIH.bottom) /
						 (float)(_hoops_SGRA->_hoops_CIIH.right - _hoops_SGRA->_hoops_CIIH.left) *
						 dc->current._hoops_AGRS;

		if (_hoops_IHCR->_hoops_AGAA.left < _hoops_SGRA->_hoops_PHRA.left)
			_hoops_IHCR->_hoops_AGAA.left = _hoops_SGRA->_hoops_PHRA.left;
		if (_hoops_IHCR->_hoops_AGAA.right > _hoops_SGRA->_hoops_PHRA.right)
			_hoops_IHCR->_hoops_AGAA.right = _hoops_SGRA->_hoops_PHRA.right;
		if (_hoops_IHCR->_hoops_AGAA.bottom < _hoops_SGRA->_hoops_PHRA.bottom)
			_hoops_IHCR->_hoops_AGAA.bottom = _hoops_SGRA->_hoops_PHRA.bottom;
		if (_hoops_IHCR->_hoops_AGAA.top > _hoops_SGRA->_hoops_PHRA.top)
			_hoops_IHCR->_hoops_AGAA.top = _hoops_SGRA->_hoops_PHRA.top;

		float	width = nr->_hoops_SAIR->_hoops_PHRA.right - nr->_hoops_SAIR->_hoops_PHRA.left;
		_hoops_IHCR->_hoops_HIPHP = width / _hoops_IHCR->_hoops_SPH->_hoops_ISPA;
		if (width > 0.0f)
			_hoops_IHCR->_hoops_IIPHP = _hoops_IHCR->_hoops_SPH->_hoops_ISPA / width;
		else
			_hoops_IHCR->_hoops_IIPHP = 1.0e9f;

		HD_Redo_Screen (nr, &_hoops_RHSPR);
	}

	_hoops_PGSSS = _hoops_AICSS->_hoops_SRCP->_hoops_RCGC & _hoops_RAHGP & _hoops_IRHGP;
	if (BIT (_hoops_PGSSS, T_FACES))
		_hoops_PGSSS |= _hoops_GPA;

	if (!ANYBIT (_hoops_AICSS->_hoops_SRCP->_hoops_RCGC, _hoops_APHGP | _hoops_RPHGP)) {
		if (!BIT (_hoops_AICSS->_hoops_SRCP->_hoops_RCGC, _hoops_RPHGP))
			_hoops_PGSSS &= nr->_hoops_IRR->_hoops_AAICA;
		if (!BIT (_hoops_AICSS->_hoops_SRCP->_hoops_RCGC, _hoops_APHGP)) {
			_hoops_ACHR		_hoops_HSIPH = nr->_hoops_RGP;

			if (BIT (_hoops_HSIPH, T_FACES))
				_hoops_HSIPH |= _hoops_GPA;
			if (ANYBIT (_hoops_HSIPH, T_ANY_EDGE))
				_hoops_HSIPH |= T_EDGES;

			_hoops_PGSSS &= _hoops_HSIPH | nr->_hoops_IRR->_hoops_PHARP;
		}
	}

	if (!BIT (sc->options, _hoops_IICAH)) {
		switch (_hoops_IHCR->_hoops_HGSC) {
			case _hoops_PCPHP: {
				nr.Modify()->transform_rendition.Modify()->_hoops_HGSC = _hoops_ACPHP;
			}	break;

			case _hoops_RCPHP: {
				nr.Modify()->transform_rendition.Modify()->_hoops_HGSC = _hoops_GCPHP;
			}	break;

			/* (_hoops_PGII _hoops_HIASR _hoops_PAH _hoops_CCHRC _hoops_RH _hoops_PPRRR _hoops_SSIA _hoops_CHR.) */
		}

		_hoops_IHCR = nr->transform_rendition;

		if (BIT (_hoops_AICSS->_hoops_AAICA, T_WINDOWS)) {
			if (nr->_hoops_RSGC->action.draw_window != nullroutine) {
				_hoops_HCHGH(nr, _hoops_CGACR);
				_hoops_SHICP (nr, draw_window)(&nr, (Int_Rectangle *)_hoops_AICSS->_hoops_SRCP);
				_hoops_SCHGH(nr);
			}
			else {
				Point				scale,
												translate;
				/* _hoops_CAHA _hoops_CAS _hoops_RH _hoops_AHCR=0 _hoops_IPPA _hoops_HRGR _hoops_GGR _hoops_SHPR _hoops_CPHH -
				 * "_hoops_PHCH._hoops_SSH" */

				HD_Compute_Screen_Transform (nr, &scale, &translate);

				HD_Elaborate_Selection (nr, (Geometry alter *)_hoops_AICSS->_hoops_SRCP, _hoops_AICSS->_hoops_SRCP->key, _hoops_AIRIR(_hoops_AICSS->_hoops_SRCP),
										-1, -1, -1,
										translate.z, MAX_FLOAT, T_WINDOWS, null);
			}
		}
	}

	if (sc->_hoops_GHPPI) {
		goto _hoops_HPAGR;
	}

	if (_hoops_PGSSS != false) {
		/* _hoops_HAIHR _hoops_CPAP! */
		_hoops_HCSIR alter *	_hoops_ICSIR = null;

		dc->_hoops_CPGPR |= _hoops_RCGSA; /* _hoops_RHGGP _hoops_SCHCP */

		/* _hoops_RIRRR _hoops_HII _hoops_RRSSS */

		if (ANYBIT (sc->options, _hoops_RHCAH|_hoops_RSCAH)) {
			/* _hoops_CGCH _hoops_RPGP - _hoops_GARIR _hoops_GPP _hoops_RH _hoops_SPCR _hoops_PPR _hoops_GHCR _hoops_IPCAH/_hoops_IASC _hoops_AHCRR
			 * _hoops_HCGC.
			 */

			sc->_hoops_RICAH.x = 9999.0f;
			sc->_hoops_RICAH.y = 9999.0f;
			sc->_hoops_GICAH = 9999.0f;
		}
		else {
			float			_hoops_ARSSS;

			/* "_hoops_IRHI" _hoops_RH _hoops_ISPR _hoops_CCAC _hoops_HPP _hoops_RH _hoops_IPCAH */

			if (dc->options._hoops_SHSHA < 0.0f) {
				HE_WARNING (HEC_DRIVER, HES_INVALID_SELECTION_PROXIMITY,
						"Negative 'selection proximity' driver option ignored");
				_hoops_ARSSS = 9999.0f;
			}
			else if (dc->options._hoops_SHSHA > 9999.0f)
				_hoops_ARSSS = 9999.0f;
			else
				_hoops_ARSSS = dc->options._hoops_SHSHA;

			/* _hoops_SICR _hoops_HII _hoops_SAPSR _hoops_IS _hoops_ASPA */
			sc->_hoops_RICAH.x = _hoops_ARSSS * sc->_hoops_HICAH.x;
			sc->_hoops_RICAH.y = _hoops_ARSSS * sc->_hoops_HICAH.y;

			/* _hoops_RRAA _hoops_SCH */
			sc->_hoops_GICAH = _hoops_ARSSS * _hoops_ARSSS;

			sc->bounding.left	-= sc->_hoops_RICAH.x;
			sc->bounding.right	+= sc->_hoops_RICAH.x;
			sc->bounding.bottom -= sc->_hoops_RICAH.y;
			sc->bounding.top	+= sc->_hoops_RICAH.y;
		}

		if (!BIT (sc->options, _hoops_IICAH)) {
			/* _hoops_AA _hoops_IRS _hoops_ARRPA _hoops_ISPR _hoops_GPP _hoops_RH _hoops_RGGHR*/

			if (sc->bounding.left < (float)_hoops_SGRA->_hoops_PHRA.left)
				sc->bounding.left = (float)_hoops_SGRA->_hoops_PHRA.left;
			if (sc->bounding.right > (float)_hoops_SGRA->_hoops_PHRA.right)
				sc->bounding.right = (float)_hoops_SGRA->_hoops_PHRA.right;
			if (sc->bounding.bottom < (float)_hoops_SGRA->_hoops_PHRA.bottom)
				sc->bounding.bottom = (float)_hoops_SGRA->_hoops_PHRA.bottom;
			if (sc->bounding.top > (float)_hoops_SGRA->_hoops_PHRA.top)
				sc->bounding.top = (float)_hoops_SGRA->_hoops_PHRA.top;

			if (sc->bounding.left > sc->bounding.right + 0.001f &&
				sc->bounding.bottom > sc->bounding.top + 0.001f) {
				_hoops_RCCSS (sc->_hoops_ASCAH);
				sc->_hoops_ASCAH = null;
				goto _hoops_HPAGR;
			}

			if (sc->_hoops_AICAH.x < (float)_hoops_SGRA->_hoops_PHRA.left)
				sc->_hoops_AICAH.x = (float)_hoops_SGRA->_hoops_PHRA.left;
			else if (sc->_hoops_AICAH.x > (float)_hoops_SGRA->_hoops_PHRA.right)
				sc->_hoops_AICAH.x = (float)_hoops_SGRA->_hoops_PHRA.right;

			if (sc->_hoops_AICAH.y < (float)_hoops_SGRA->_hoops_PHRA.bottom)
				sc->_hoops_AICAH.y = (float)_hoops_SGRA->_hoops_PHRA.bottom;
			else if (sc->_hoops_AICAH.y > (float)_hoops_SGRA->_hoops_PHRA.top)
				sc->_hoops_AICAH.y = (float)_hoops_SGRA->_hoops_PHRA.top;
		}

		/*
		 * _hoops_SSCR _hoops_RH _hoops_PHPHA _hoops_IPCAH _hoops_RGGHR _hoops_HII _hoops_RH _hoops_RHCH _hoops_IPSH
		 * _hoops_RH _hoops_IASC _hoops_AHCRR.
		 * _hoops_PAAS _hoops_PRHAI _hoops_HPP _hoops_ISII/_hoops_HSSP, _hoops_RH _hoops_PRSSS _hoops_HRGR
		 * _hoops_AIAH _hoops_PIISR _hoops_GGR _hoops_ARRS, _hoops_PPR _hoops_RH _hoops_IASC _hoops_HRGR _hoops_AIPH, _hoops_HIS
		 * _hoops_SR _hoops_AASGA _hoops_RGR _hoops_IAPPI.
		 */
		if (_hoops_GPIIR->_hoops_HARIR == null) {
			sc->_hoops_RICAH.x = _hoops_IAAA (sc->bounding.right - sc->_hoops_AICAH.x,
										 sc->_hoops_AICAH.x - sc->bounding.left);
			sc->_hoops_RICAH.y = _hoops_IAAA (sc->bounding.top - sc->_hoops_AICAH.y,
										 sc->_hoops_AICAH.y - sc->bounding.bottom);

			if (BIT (sc->options, _hoops_RHCAH)) {
				sc->_hoops_GICAH = sc->_hoops_RICAH.x * sc->_hoops_RICAH.x +
											   sc->_hoops_RICAH.y * sc->_hoops_RICAH.y;
				sc->_hoops_RICAH.x =
					sc->_hoops_RICAH.y =
						_hoops_SGIHR (sc->_hoops_GICAH);
			}
		}

		if (BIT (sc->options, _hoops_RSCAH)) {
			if (BIT (sc->options, _hoops_IICAH)) {
				sc->_hoops_GICAH =
						sc->_hoops_RICAH.x*sc->_hoops_RICAH.x +
						sc->_hoops_RICAH.y*sc->_hoops_RICAH.y;
			}
			else {
				float			_hoops_HRSSS, _hoops_IRSSS;

				_hoops_HRSSS = sc->_hoops_RICAH.x / sc->_hoops_HICAH.x;
				_hoops_IRSSS = sc->_hoops_RICAH.y / sc->_hoops_HICAH.y;

				/* _hoops_CAHA _hoops_IRS _hoops_GHARP _hoops_IPCAH _hoops_SGS *_hoops_CRRPR* _hoops_RH _hoops_AHCRR */
				sc->_hoops_GICAH = _hoops_HRSSS*_hoops_HRSSS + _hoops_IRSSS*_hoops_IRSSS;
			}
		}

		if (BIT (_hoops_IHCR->heuristics, _hoops_AAIRP) &&
			!BIT (sc->options, _hoops_IICAH)) {
			sc->options |= _hoops_CRPAS;

			if (_hoops_IHCR->_hoops_AGAA.left < (int)sc->bounding.left)
				_hoops_IHCR->_hoops_AGAA.left = (int)sc->bounding.left;
			if (_hoops_IHCR->_hoops_AGAA.right > (int)sc->bounding.right)
				_hoops_IHCR->_hoops_AGAA.right = (int)sc->bounding.right;
			if (_hoops_IHCR->_hoops_AGAA.bottom < (int)sc->bounding.bottom)
				_hoops_IHCR->_hoops_AGAA.bottom = (int)sc->bounding.bottom;
			if (_hoops_IHCR->_hoops_AGAA.top > (int)sc->bounding.top)
				_hoops_IHCR->_hoops_AGAA.top = (int)sc->bounding.top;


#if 0	/* _hoops_ACGRH _hoops_CRSSS _hoops_IGPIP _hoops_ARCRC _hoops_CRAIA _hoops_SRSSS! */
			sc->_hoops_GPPAS =
						(dc->_hoops_ACPGR->_hoops_CRGIP != nullroutine);
#else
			sc->_hoops_GPPAS = false;
#endif


			if (sc->_hoops_GPPAS) {
				HD_Set_Z_Buffering_Transform (nr, true, true,
											  dc->_hoops_PGCC._hoops_PASHP);

				(*dc->_hoops_ACPGR->init_update) (dc);
			}
			else {
				_hoops_APARR		_hoops_RRCI;

				nr->_hoops_ASIR->buffer._hoops_SPAAP = 0;
				nr->flags &= ~_hoops_SISHP;

				HD_Set_Z_Buffering_Transform (nr, true, true,
											  (float)_hoops_HSCHA);

				_hoops_ICSIR = HD_Init_Frame_Buffer_Info (nr, _hoops_AICSS->_hoops_SRCP, _hoops_HICS());

				/* _hoops_PGSA "_hoops_HIRA" _hoops_RPP _hoops_SIGR */
				if (_hoops_ICSIR->depth_buffer == null ||
					_hoops_ICSIR->_hoops_HSGSP < HOOPS_WORLD->_hoops_GPPI ||
					_hoops_IHCR->_hoops_AGAA.left	 < _hoops_ICSIR->_hoops_CHHSP.left	||
					_hoops_IHCR->_hoops_AGAA.right	 > _hoops_ICSIR->_hoops_CHHSP.right	||
					_hoops_IHCR->_hoops_AGAA.bottom < _hoops_ICSIR->_hoops_CHHSP.bottom ||
					_hoops_IHCR->_hoops_AGAA.top	 > _hoops_ICSIR->_hoops_CHHSP.top) {
					bool _hoops_PSPIP;
					Int_Rectangle				_hoops_PHGPS;
					_hoops_RGHPP			_hoops_GASSS[_hoops_CHSSP];
					_hoops_RGHPP			_hoops_RASSS;
					bool						_hoops_AASSS;

					_hoops_ICSIR->_hoops_PSSCP = _hoops_PGGSP;
					nr->current = _hoops_RSSHP; /* _hoops_HAISR _hoops_HGSR _hoops_CRGR _hoops_HAGC _hoops_AHCR */
					_hoops_AASSS = HD_Setup_Frame_Buffer (nr);
					nr->current = 0;

					/* _hoops_ARP _hoops_HSPH _hoops_IS _hoops_GCIS _hoops_PCPA _hoops_SR _hoops_RRP _hoops_CHCC */
					_hoops_RSAI (&_hoops_IHCR->_hoops_AGAA, Int_Rectangle, &_hoops_PHGPS);
					if (_hoops_ICSIR->_hoops_HSGSP == HOOPS_WORLD->_hoops_GPPI) {
						if (_hoops_IHCR->_hoops_AGAA.left	 > _hoops_ICSIR->_hoops_CHHSP.left)
							_hoops_IHCR->_hoops_AGAA.left	 = _hoops_ICSIR->_hoops_CHHSP.left;
						if (_hoops_IHCR->_hoops_AGAA.right	 < _hoops_ICSIR->_hoops_CHHSP.right)
							_hoops_IHCR->_hoops_AGAA.right	 = _hoops_ICSIR->_hoops_CHHSP.right;
						if (_hoops_IHCR->_hoops_AGAA.bottom > _hoops_ICSIR->_hoops_CHHSP.bottom)
							_hoops_IHCR->_hoops_AGAA.bottom = _hoops_ICSIR->_hoops_CHHSP.bottom;
						if (_hoops_IHCR->_hoops_AGAA.top	 < _hoops_ICSIR->_hoops_CHHSP.top)
							_hoops_IHCR->_hoops_AGAA.top	 = _hoops_ICSIR->_hoops_CHHSP.top;
					}
					_hoops_ICSIR->_hoops_CHHSP.left	 = _hoops_IHCR->_hoops_AGAA.left;
					_hoops_ICSIR->_hoops_CHHSP.right	 = _hoops_IHCR->_hoops_AGAA.right;
					_hoops_ICSIR->_hoops_CHHSP.bottom = _hoops_IHCR->_hoops_AGAA.bottom;
					_hoops_ICSIR->_hoops_CHHSP.top	 = _hoops_IHCR->_hoops_AGAA.top;

					/* _hoops_GA'_hoops_RA _hoops_RRP _hoops_IHIR _hoops_HIRA */
					_hoops_ICSIR->input._hoops_SASCP.update = _hoops_GPSCP;
					_hoops_ICSIR->input._hoops_SASCP._hoops_PPCCP = _hoops_RAHSP | _hoops_AAHSP | _hoops_PAHSP;

					nr->_hoops_RCSHR |= _hoops_RSSHP|_hoops_CSGGR|_hoops_PRHIP;
					nr->_hoops_RCSHR &= ~_hoops_CRHPP;

					dc->_hoops_CPGPR |= _hoops_RCGSA;
					_hoops_PSPIP = _hoops_ICSIR->_hoops_PSPIP;

					_hoops_AIGA (dc->_hoops_HRHPP, _hoops_CHSSP, _hoops_RGHPP, _hoops_GASSS);
					_hoops_RSAI (&dc->_hoops_GPSIP, _hoops_RGHPP, &_hoops_RASSS);
					for (i = 0; i < _hoops_CHSSP; ++i) {
						dc->_hoops_HRHPP[i].list = null;
						dc->_hoops_HRHPP[i]._hoops_ASRGR = &dc->_hoops_HRHPP[i].list;
					}

					dc->_hoops_GPSIP.list = null;
					dc->_hoops_GPSIP._hoops_ASRGR = &dc->_hoops_GPSIP.list;

					_hoops_PGHPP *	_hoops_PASSS = dc->_hoops_AGHPP;
					_hoops_IGHPP *	_hoops_HASSS = dc->_hoops_HGHPP;

					dc->_hoops_AGHPP = null;
					dc->_hoops_HGHPP = null;

					bool	_hoops_GIIIP = BIT(dc->flags, _hoops_RPSRR);
					dc->flags |= _hoops_RPSRR;

					dc->Add_Filter (POOL_NEW(dc->memory_pool, _hoops_CSCSS)());
					_hoops_AASS (nr, _hoops_AICSS->_hoops_SRCP, _hoops_HICS());
					HD_Draw_Deferred_Trees (dc);
					dc->Remove_Filter();

					if (!_hoops_GIIIP)
						dc->flags &= ~_hoops_RPSRR;


					for (i = 0; i < _hoops_CHSSP; ++i) {
						while (dc->_hoops_HRHPP[i].list != null) {
							_hoops_HSPPP alter * _hoops_PASIP = (_hoops_HSPPP alter *)dc->_hoops_HRHPP[i].list;
							dc->_hoops_HRHPP[i].list = _hoops_PASIP->next;

							_hoops_PASIP->_hoops_APHGA.release();
							FREE (_hoops_PASIP, _hoops_HSPPP);
						}
					}

					while (dc->_hoops_GPSIP.list != null) {
						_hoops_HSPPP alter * _hoops_PASIP = (_hoops_HSPPP alter *)dc->_hoops_GPSIP.list;
						dc->_hoops_GPSIP.list = _hoops_PASIP->next;

						_hoops_PASIP->_hoops_APHGA.release();
						FREE (_hoops_PASIP, _hoops_HSPPP);
					}
					_hoops_AIGA (_hoops_GASSS, _hoops_CHSSP, _hoops_RGHPP, dc->_hoops_HRHPP);
					_hoops_RSAI (&_hoops_RASSS, _hoops_RGHPP, &dc->_hoops_GPSIP);

					if (dc->_hoops_AGHPP != null) {
						_hoops_RGHPP alter *	_hoops_SGCCA = null;
						int							_hoops_IGIC;

						while (dc->_hoops_AGHPP->Pop(&_hoops_SGCCA, &_hoops_IGIC)) {
							dc->_hoops_HGHPP->RemoveItem(_hoops_IGIC);

							_hoops_HSPPP alter * _hoops_ISPPP = _hoops_SGCCA->list;

							while (_hoops_ISPPP) {
								_hoops_HSPPP alter * next = _hoops_ISPPP->next;
								_hoops_ISPPP->_hoops_APHGA.release();
								FREE (_hoops_ISPPP, _hoops_HSPPP);
								_hoops_ISPPP = next;
							}

							FREE (_hoops_SGCCA, _hoops_RGHPP);
						}

						ASSERT(dc->_hoops_AGHPP->Count() == 0);
						ASSERT(dc->_hoops_HGHPP->Count() == 0);
					}

					dc->_hoops_AGHPP = _hoops_PASSS;
					dc->_hoops_HGHPP = _hoops_HASSS;

					_hoops_ICSIR->_hoops_PSPIP = _hoops_PSPIP;
					_hoops_RSAI (&_hoops_PHGPS, Int_Rectangle, &_hoops_IHCR->_hoops_AGAA);

					if (_hoops_AASSS)
						((_hoops_CRCP *)_hoops_AICSS->_hoops_SRCP)->_hoops_CPGPR |= _hoops_RCGSA;
				}
				else if ((_hoops_GPIIR->_hoops_HARIR != null ||
						  !ANYBIT (sc->options, _hoops_RHCAH|_hoops_RSCAH)) &&
						 _hoops_ICSIR->_hoops_HCSCP == null) {
					_hoops_ICSIR->_hoops_PSSCP = _hoops_PGGSP;

					/* _hoops_ICHRR-_hoops_AACC _hoops_PCPA _hoops_SR _hoops_CHH _hoops_IAII _hoops_IIS _hoops_SIIR _hoops_RGHH */
					_hoops_CSSCP (nr,
											 _hoops_ICSIR->depth_buffer->width,
											 _hoops_ICSIR->depth_buffer->height,
											 _hoops_PGGSP,
											 &_hoops_ICSIR->_hoops_HCSCP,
											 &_hoops_ICSIR->_hoops_ICSCP);
				}

				/* _hoops_GII _hoops_GASAR "_hoops_ASCA" _hoops_HRGR _hoops_IGI _hoops_IH _hoops_APSP _hoops_RGAP _hoops_PAR
				   _hoops_RCIRP _hoops_ISPR, _hoops_HIS _hoops_ARP _hoops_GH _hoops_HSSPR _hoops_GPAC
				*/
				_hoops_RRCI = _hoops_HGCGA (dc, "visual selection", nr);

				_hoops_RRCI->draw_3d_sphere					= HD_Std_3D_Sphere;
				_hoops_RRCI->draw_3d_polycylinder			= HD_Std_3D_PolyCylinder;
				_hoops_RRCI->draw_3d_cylinder				= HD_Std_3D_Cylinder;
				_hoops_RRCI->draw_3d_nurbs_curve				= HD_Std_3D_NURBS_Curve;
				_hoops_RRCI->draw_3d_nurbs_surface			= HD_Std_3D_NURBS_Surface;
				_hoops_RRCI->draw_3d_ellipse					= HD_Std_3D_Ellipse;
				_hoops_RRCI->draw_3d_elliptical_arc			= HD_Std_3D_Elliptical_Arc;
				_hoops_RRCI->draw_3d_marker					= HD_Std_3D_Marker;
				_hoops_RRCI->_hoops_RIICP				= HD_Std_3D_Multimarker;
				_hoops_RRCI->_hoops_PPAS			= HD_Draw_Indexicated_3D_Polyedge;
				_hoops_RRCI->draw_3d_polyedge				= HD_Std_3D_Polyedge;
				_hoops_RRCI->draw_3d_polyedge_from_tristrip	= nullroutine;
				_hoops_RRCI->draw_3d_polymarker				= HD_Std_3D_Polymarker;
				_hoops_RRCI->draw_3d_polyline				= HD_Std_3D_Polyline;
				_hoops_RRCI->draw_3d_polygon					= HD_Std_3D_Polygon;
				_hoops_RRCI->_hoops_SHCHP					= HD_Std_3D_Contour;
				_hoops_RRCI->draw_3d_polyhedron				= HD_Std_3D_Polyhedron;
				_hoops_RRCI->draw_3d_image					= HD_Std_3D_Image;
				_hoops_RRCI->draw_3d_text					= HD_Std_3D_Text;
				_hoops_RRCI->_hoops_ARCI			= HD_Draw_Indexicated_3D_Tristrip;
				_hoops_RRCI->draw_3d_tristrip				= HD_Std_3D_Tristrip;
				_hoops_RRCI->_hoops_CRCGA			= HD_Std_3D_Stenciled_Quad;
				_hoops_RRCI->_hoops_CSCGA					= HD_Standard_Draw_Inter_Text;
				_hoops_RRCI->draw_dc_face					= HD_Std_DC_Face;
				_hoops_RRCI->draw_dc_colorized_face			= HD_Std_DC_Colorized_Face;
				_hoops_RRCI->_hoops_RPCGA					= HD_Std_DC_Polygon;
				_hoops_RRCI->draw_dc_polyline				= HD_Std_DC_Polyline;
				_hoops_RRCI->draw_dc_polydot					= HD_Std_DC_Polydot;
				_hoops_RRCI->draw_dc_ellipse					= HD_Std_DC_Ellipse;
				_hoops_RRCI->_hoops_CCISR			= HD_Std_DC_Elliptical_Arc;
				_hoops_RRCI->_hoops_SCISR			= HD_Std_DC_Outline_Ellipse;
				_hoops_RRCI->draw_dc_polymarker				= HD_Std_DC_Polymarker;
				_hoops_RRCI->_hoops_SPCGA			= HD_Std_DC_Stenciled_Quad;
				_hoops_RRCI->_hoops_CHCI							= HD_Standard_Render;

				_hoops_RRCI->draw_dc_polytriangle			= HD_SZB_DC_Polytriangle;
				_hoops_RRCI->draw_dc_colorized_polytriangle	= HD_SZB_DC_Colorized_Polytris;
				_hoops_RRCI->draw_dc_gouraud_polytriangle	= HD_SZB_DC_Gouraud_Polytris;
				_hoops_RRCI->draw_dc_phong_polytriangle		= HD_SZB_DC_Phong_Polytris;
				_hoops_RRCI->draw_dc_textured_polytriangle	= HD_SZB_DC_Textured_Polytris;
				_hoops_RRCI->draw_dc_polyline				= HD_SZB_DC_Polyline;
				_hoops_RRCI->draw_dc_colorized_polyline		= HD_Span_DC_Colorized_Polyline;
				_hoops_RRCI->draw_dc_gouraud_polyline		= HD_Span_DC_Gouraud_Polyline;


				_hoops_ICSIR->input._hoops_SASCP._hoops_PPCCP = _hoops_RAHSP | _hoops_AAHSP | _hoops_PAHSP;

				if (_hoops_GPIIR->_hoops_HARIR != null ||
					!ANYBIT (sc->options, _hoops_RHCAH|_hoops_RSCAH)) {
						_hoops_SCASP			_hoops_AICIP = _hoops_IHCR->flags;

					/* _hoops_PGSA _hoops_CRGR _hoops_APSP _hoops_SRHR; _hoops_PSP _hoops_SSH, _hoops_CSCR, _hoops_PAR _hoops_IAGP */
					_hoops_ICSIR->input._hoops_SASCP.test = _hoops_IRHSP;
					_hoops_ICSIR->input._hoops_SASCP.update = _hoops_GPSCP | _hoops_IRHSP | FBI_OCCLUSION;

					_hoops_ICSIR->input.required.update = _hoops_SRHSP;
					_hoops_ICSIR->input._hoops_RPHSP = _hoops_GPHSP;
					_hoops_ICSIR->input._hoops_RHHSP = _hoops_HPHSP;

					/* _hoops_IRHH _hoops_RCRR _hoops_CCAC _hoops_HRGR _hoops_SCAC _hoops_SRS */
					_hoops_ICSIR->input._hoops_APHSP = 0;
					HD_SZB_DC_Rectangle (nr, _hoops_IHCR->_hoops_AGAA.left, _hoops_IHCR->_hoops_AGAA.right,
											 _hoops_IHCR->_hoops_AGAA.bottom, _hoops_IHCR->_hoops_AGAA.top);

					/* _hoops_HA _hoops_RH _hoops_CAHA */
					_hoops_ICSIR->input._hoops_APHSP = 1;
					_hoops_IHCR->flags &= ~_hoops_CSP;
					if (_hoops_GPIIR->_hoops_HARIR == null) {
						DC_Point				center, radii;

						center.x = sc->_hoops_AICAH.x;
						center.y = sc->_hoops_AICAH.y;
						center.z = 0.0f;
						radii.x = sc->_hoops_RICAH.x;
						radii.y = sc->_hoops_RICAH.y;
						radii.z = 0.0f;

						// _hoops_PGSA _hoops_CPHP _hoops_RIISH _hoops_RPHSR, _hoops_GAR _hoops_RH _hoops_HCPI _hoops_SPGHS _hoops_IS _hoops_CAHP
						// _hoops_SPPSH _hoops_GHIIS _hoops_PGAP _hoops_AAGAI _hoops_GA'_hoops_RA _hoops_ARHSA _hoops_GII _hoops_PSIGA _hoops_ASPA
						HD_SZB_DC_Rectangle (nr, center.x-0.75f*radii.x, center.x+0.75f*radii.x,
												 center.y-0.75f*radii.y, center.y+0.75f*radii.y);

						if (radii.x <= 1.0f || radii.y <= 1.0f)
							_hoops_PAPIP (nr, &center, &radii);
						_hoops_AAPIP (nr, &center, &radii);
					}
					else {
						if (BIT (_hoops_GPIIR->flags, _hoops_CCSHA))
							_hoops_RSGCP (nr, sc->count, (DC_Point const *)sc->_hoops_RAPAS);
						else
							_hoops_SCGGA(nr, sc->count, (DC_Point const *)sc->_hoops_RAPAS);
					}
					_hoops_IHCR->flags = _hoops_AICIP;

					/* _hoops_PHIH _hoops_GSSR _hoops_CAPRR */
					_hoops_ICSIR->input._hoops_SASCP.test = _hoops_HRHSP;
					/* _hoops_HIH _hoops_AGCR _hoops_CHR _hoops_HGAS _hoops_CRGC _hoops_CAPP _hoops_APIC
					_hoops_RSIIP->_hoops_CIIA._hoops_IASSS._hoops_PAAP = _hoops_CASSS;
					_hoops_RSIIP->_hoops_CIIA._hoops_RGHP._hoops_PAAP = _hoops_CASSS;
					*/

					/* _hoops_HA _hoops_ASGGR _hoops_APSP _hoops_RPGP */
					_hoops_ICSIR->input.required.test = _hoops_SRHSP;
					_hoops_ICSIR->input._hoops_RHHSP = _hoops_PPHSP;
					_hoops_ICSIR->input._hoops_RPHSP = TEST_EQUAL;
				}

				/* _hoops_HRPP _hoops_IH _hoops_IAGP _hoops_RPGP */
				_hoops_ICSIR->input._hoops_SASCP.update = _hoops_GPSCP | _hoops_IRHSP | _hoops_SRHSP;
				_hoops_ICSIR->input.required.update = FBI_OCCLUSION;
				_hoops_ICSIR->input._hoops_AHHSP = 1;		/* _hoops_GII _hoops_HRGR _hoops_RIRA _hoops_RAPR */
			}
		}

		sc->_hoops_GCCIA = nr->_hoops_IRR->_hoops_GCCIA;

		_hoops_HGCGA (dc, "detailed selection", nr);
		HD_Vanillify_Actions (~0, dc->_hoops_IPCI);
		dc->_hoops_IPCI->draw_dc_polyline = HD_Select_DC_Polyline;
		dc->_hoops_IPCI->draw_dc_polytriangle = HD_Select_DC_Polytriangle;
		dc->_hoops_IPCI->draw_dc_face = HD_Std_DC_Face;
		dc->_hoops_IPCI->draw_dc_polymarker = HD_Std_DC_Polymarker;
		dc->_hoops_IPCI->draw_dc_ellipse = HD_Std_DC_Ellipse;
		dc->_hoops_IPCI->_hoops_CCISR	= HD_Std_DC_Elliptical_Arc;
		dc->_hoops_IPCI->_hoops_SCISR = HD_Std_DC_Outline_Ellipse;

		if (BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_AARAP) &&
			BIT(nr->_hoops_RGP, T_CUTTING_PLANES) ||
			_hoops_AICSS->_hoops_SRCP->_hoops_PAGSA() > 0 && _hoops_AICSS->_hoops_SRCP->geometry != null)
			HD_Find_Local_Cutting_Planes (nr, _hoops_AICSS->_hoops_SRCP);

		/* _hoops_AA _hoops_RH _hoops_HPHR _hoops_IPHR */
		HD_Selection_Walk_Tree (nr, _hoops_AICSS->_hoops_SRCP, _hoops_HICS());

		// _hoops_CASI _hoops_GII _hoops_RGHC _hoops_ACPH _hoops_PIRRR
		_hoops_HGSGA (dc, "detailed selection");

		if (BIT (sc->options, _hoops_CRPAS) && !sc->_hoops_GPPAS)
			_hoops_HGSGA (dc, "visual selection");

		if (dc->_hoops_IPCI->prev != null)
			_hoops_HGSGA (dc, "error");

		if (BIT (sc->options, _hoops_CRPAS)) {
			if (sc->_hoops_GPPAS) {
				(*dc->_hoops_ACPGR->finish_update) (dc);
			}
			else {
				/* _hoops_PPSI _hoops_ISSC _hoops_HSSHH _hoops_GPP _hoops_PA _hoops_SR _hoops_SIAS _hoops_HS _hoops_RHIAA */
				_hoops_ICSIR->input._hoops_SASCP.test = _hoops_HRHSP;
				_hoops_ICSIR->input._hoops_SASCP.update = _hoops_HRHSP;
				_hoops_ICSIR->input._hoops_SASCP._hoops_PPCCP = _hoops_HRHSP;
				_hoops_ICSIR->input.required.test = _hoops_HRHSP;
				_hoops_ICSIR->input.required.update = _hoops_HRHSP;

				_hoops_ICSIR->input._hoops_RPHSP = _hoops_GPHSP;
			}
		}
	}
_hoops_HPAGR:
	dc->_hoops_CPGPR = _hoops_RGSSS;
	_hoops_PGRCA(_hoops_AICSS->_hoops_SRCP)->_hoops_CPGPR = _hoops_AGSSS;
}


local void _hoops_SASSS (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP) {
	_hoops_CRCP const *				owner = _hoops_SRCP->owner;

	while (owner->type != _hoops_PRAIR) {
		if (owner->type == _hoops_IRCP &&
			owner->_hoops_IPPGR != null) {
			_hoops_SASSS (nr, owner);
			break;
		}
		owner = owner->owner;
	}

	if (_hoops_SRCP->_hoops_IPPGR != null)
		HD_Selection_Downwind (nr, _hoops_SRCP->_hoops_IPPGR);
}

#define _hoops_RCCAH(_hoops_AIPPA,_hoops_PIPPA) \
			((_hoops_AIPPA->_hoops_PCSAP > _hoops_PIPPA->_hoops_PCSAP) ||  \
			 (_hoops_AIPPA->_hoops_PCSAP == _hoops_PIPPA->_hoops_PCSAP && _hoops_AIPPA->_hoops_HCSAP > _hoops_PIPPA->_hoops_HCSAP))

#define QS_TYPE					_hoops_RPIIR **
#define QS_COMPARETYPE			_hoops_RPIIR *
#define QS_VAL(thing,a)			(thing[a]->_hoops_PCSAP)
#define QS_PIVOT_VAL(thing,a)	(thing[a])
#define QS_COMPLEX_COMPARE(thing,a,b) _hoops_RCCAH(thing[a],thing[b])
#define QS_COMPLEX_COMPARE_P1(thing,pivot,b) _hoops_RCCAH(pivot,thing[b])
#define QS_COMPLEX_COMPARE_P2(thing,a,pivot) _hoops_RCCAH(thing[a],pivot)
#define QS_SWAP(thing,a,b)		{_hoops_RPIIR * tmp = thing[a]; thing[a] = thing[b]; thing[b] = tmp;}
#include "utility/hqsort.h"


local void _hoops_GPSSS (
	Net_Rendition const &		nr,
	Selection_Event *			_hoops_GPIIR,
	_hoops_ACCCP *			sc) {
	_hoops_RPIIR **			_hoops_ASRGR = &_hoops_GPIIR->_hoops_APIIR;
	_hoops_IPIIR *		heap = _hoops_GPIIR->_hoops_HPIIR;

	UNREFERENCED(nr);

	sc->_hoops_GCCAH = 0;
	while (*_hoops_ASRGR != null && sc->_hoops_GCCAH <= sc->_hoops_GCCIA) {
		_hoops_ASRGR = &(*_hoops_ASRGR)->next;
		++sc->_hoops_GCCAH;
	}

	// _hoops_CCPH _hoops_GII _hoops_RGIAS
	while (*_hoops_ASRGR != null) {
		_hoops_RPIIR *		victim = *_hoops_ASRGR;

		*_hoops_ASRGR = victim->next;
		HI_Free_Selection_Item (victim);
	}

	// _hoops_PAR _hoops_GGCR _hoops_HII _hoops_RPSSS _hoops_APSAR
	if (sc->_hoops_GCCAH <= sc->_hoops_GCCIA) {
		_hoops_RPIIR *		si;

		if (BIT(heap->flags, _hoops_CCSAP)) {
			_hoops_RPIIR **	_hoops_PCAHA;
			int					count;

			count = heap->_hoops_GSSAP;
			if (count > 0) {
				ALLOC_ARRAY (_hoops_PCAHA, count, _hoops_RPIIR *);

				si = heap->_hoops_SCSAP;
				for (int i = 0; i < count; i++) {
					_hoops_PCAHA[i] = si;
					si->_hoops_HCSAP = i;
					si = si->next;
				}
				quick_sort(_hoops_PCAHA, 0, count - 1);
				for (int i = 0; i < count-1; i++) {
					_hoops_PCAHA[i]->next = _hoops_PCAHA[i+1];
				}
				_hoops_PCAHA[count-1]->next = null;

				*_hoops_ASRGR = _hoops_PCAHA[0];
				sc->_hoops_GCCAH += count;

				FREE_ARRAY (_hoops_PCAHA, count, _hoops_RPIIR *);
			}
		}
		else {
			while ((si = HI_Selection_Item_Heap_Pop (heap)) != null) {
				si->next = *_hoops_ASRGR;
				*_hoops_ASRGR = si;
				sc->_hoops_GCCAH++;
			}
		}
	}
	else {
		for (int i = 0; i < heap->used; i++)
			HI_Free_Selection_Item(heap->_hoops_SPIIR[i]);
	}
}


local void _hoops_APSSS (
	Net_Rendition const &		nr,
	Selection_Event *			_hoops_GPIIR,
	_hoops_ACCCP *			sc) {
	_hoops_RPIIR				*ptr, *victim, *next;

	UNREFERENCED(nr);

	if (sc->_hoops_GCCAH-1 > sc->_hoops_GCCIA) {
		ptr = _hoops_GPIIR->_hoops_APIIR;
		sc->_hoops_GCCAH = 0;
		for (;;) {
			if (sc->_hoops_GCCAH < sc->_hoops_GCCIA)
				sc->_hoops_GCCAH++;
			else
				break;
			ptr = ptr->next;
		}
		while ((victim = ptr->next) != null) {
			next = victim->next;
			ptr->next = next;
			HI_Free_Selection_Item(victim);
		}
	}
}


#endif



GLOBAL_FUNCTION bool HD_Standard_Select (
	Display_Context alter *		dc,
	Selection_Event alter *		_hoops_GPIIR) {
#ifndef DISABLE_SELECTION
	Net_Rendition				nr;
	Window_Tree alter 			*head,
								*_hoops_HCSR;
	_hoops_ACCCP *			sc;
	_hoops_HHCR			_hoops_IHCR;
	Activity					_hoops_PPSSS = dc->_hoops_CPGPR;
	int							_hoops_HGRS = 0;

	while (dc->_hoops_IPCI->prev != null) {
		_hoops_HGRS++;
		_hoops_IGRS (dc);
	}

	if (dc->_hoops_SHCIP != null)
		nr = dc->_hoops_SHCIP;
	else
		nr = Net_Rendition::Create(dc);

	_hoops_IHCR = nr.Modify()->transform_rendition.Modify();

	_hoops_IHCR->matrix = _hoops_SGCC::Create (dc);
	_hoops_IHCR->_hoops_IPH = _hoops_SGCC::Create (dc);


	/* _hoops_SIHA _hoops_RIRA _hoops_SIHC... */
	ZALLOC (sc, _hoops_ACCCP);
	dc->_hoops_APHHP = sc; /* (_hoops_HCGR _hoops_RAIA _hoops_RGR) */

	sc->_hoops_SRA = dc;
	sc->event = _hoops_GPIIR;
	sc->xw = (_hoops_GPIIR->_hoops_IHSHA.left + _hoops_GPIIR->_hoops_IHSHA.right) * 0.5f;
	sc->yw = (_hoops_GPIIR->_hoops_IHSHA.bottom + _hoops_GPIIR->_hoops_IHSHA.top) * 0.5f;
	//_hoops_SAIAS->_hoops_HPSSS = 0;
	//_hoops_SAIAS->_hoops_IPSSS = 0; /* _hoops_CPSSS _hoops_HPGR _hoops_GHIR _hoops_IIGR _hoops_SPSSS */
	//_hoops_SAIAS->_hoops_GHSSS = _hoops_IRAP;

	/* _hoops_SP _hoops_GGSR _hoops_RHCSS _hoops_GHSHA _hoops_AAAPR */
	//_hoops_SAIAS->_hoops_RPR = 0;
	//_hoops_SAIAS->_hoops_RHSSS = _hoops_IRAP;
	//_hoops_SAIAS->_hoops_AHSSS = _hoops_IRAP;
	//_hoops_SAIAS->_hoops_PHSSS = _hoops_IRAP;
	//_hoops_SAIAS->_hoops_HHSSS = _hoops_IRAP;
	//_hoops_SAIAS->_hoops_IHSSS = _hoops_IRAP;
	//_hoops_SAIAS->_hoops_CHSSS = 0;

	//_hoops_SAIAS->_hoops_SHSSS = _hoops_RCPP;
	//_hoops_SAIAS->_hoops_AAP = 0;

	if (BIT (_hoops_GPIIR->flags, _hoops_ICSHA))
		sc->options |= _hoops_IICAH;

#if 0
	if (BIT (_hoops_GPIIR->flags, _hoops_ASSAP))
		sc->options |= _hoops_CRPAS;
#endif

	if (BIT (_hoops_GPIIR->flags, _hoops_HCSHA)) {
		sc->options |= _hoops_RSCAH;

		if (_hoops_GPIIR->_hoops_IHSHA.hither < -MAX_FLOAT*0.99f &&
			_hoops_GPIIR->_hoops_IHSHA.yon > MAX_FLOAT*0.99f)
			sc->options |= _hoops_RHCAH;
	}

	if (BIT (_hoops_GPIIR->flags, _hoops_CCSHA))
		sc->options |= _hoops_PRPAS;


	_hoops_SASSS (nr, dc->_hoops_AAHSR);
	if (!BIT (sc->options, _hoops_IICAH))
		HD_Adjust_WLimit (nr, dc->_hoops_AAHSR, _hoops_HICS());
	if (_hoops_GPIIR->heuristics != null)
		HD_Selection_Downwind (nr, _hoops_GPIIR->heuristics);
	_hoops_IHCR = nr->transform_rendition;

	_hoops_IHCR->_hoops_AGAA.left	 = nr->_hoops_SAIR->_hoops_PHRA.left;
	_hoops_IHCR->_hoops_AGAA.right	 = nr->_hoops_SAIR->_hoops_PHRA.right;
	_hoops_IHCR->_hoops_AGAA.bottom = nr->_hoops_SAIR->_hoops_PHRA.bottom;
	_hoops_IHCR->_hoops_AGAA.top	 = nr->_hoops_SAIR->_hoops_PHRA.top;

	if (BIT (sc->options, _hoops_IICAH)) {
		sc->_hoops_HICAH.x = 1.0f;
		sc->_hoops_HICAH.y = 1.0f;

		/* _hoops_RSPC _hoops_IRS _hoops_IRAP _hoops_HIHP */
		{
			_hoops_IHCR->matrix = _hoops_SGCC::Create (dc);
			_hoops_IHCR->_hoops_IPH = _hoops_SGCC::Create (dc);

#if 0
			_hoops_IHCR->flags = _hoops_ASPIP;
#endif
			_hoops_IHCR->flags = _hoops_PRAIP;
			_hoops_IHCR->_hoops_HGSC = _hoops_SIPHP;
		}

		/* _hoops_SSIAA _hoops_HCR _hoops_AIRC */
		nr->_hoops_IRR->locks._hoops_IPPGR = 0;

		/* _hoops_SGARH _hoops_HCR _hoops_RH _hoops_ARGPR _hoops_AIRC */
		sc->options |= _hoops_HRPAS;
		_hoops_HCSR = _hoops_SCCSS (_hoops_GPIIR->_hoops_GHIIR, &head);
		HD_Selection_Downwind (nr, head->_hoops_SRCP->_hoops_IPPGR);

		{	Window_Tree alter	*_hoops_AICSS;
			_hoops_AICSS = head;
			do {
				_hoops_AICSS = _hoops_AICSS->_hoops_ICHSP;
				if (_hoops_AICSS->_hoops_SRCP->_hoops_IPPGR != null)
					HD_Selection_Downwind (nr, _hoops_AICSS->_hoops_SRCP->_hoops_IPPGR);
			}
			_hoops_RGGA (_hoops_AICSS == _hoops_HCSR);
		}

		/* _hoops_SPIC _hoops_RH _hoops_HHIS */
		sc->options |= _hoops_IRPAS;
		sc->options &= ~_hoops_HRPAS;
		_hoops_HCSR->_hoops_APHHP = sc;
		_hoops_GHCSS (nr, _hoops_HCSR);
		elaborate_leaves (nr, _hoops_HCSR, true);
	}
	else {
		sc->_hoops_HICAH.x = dc->current._hoops_HAP.x;
		sc->_hoops_HICAH.y = dc->current._hoops_HAP.y;

		/* _hoops_SRS _hoops_SSS _hoops_RH _hoops_PACIA _hoops_RPPS, _hoops_PPR _hoops_GRHP _hoops_IHGC _hoops_IIGR _hoops_RH _hoops_CAGH
		 * _hoops_AASH _hoops_SGS _hoops_SCH _hoops_GISSS _hoops_IS _hoops_HGCR _hoops_IIH.
		 */

		if (_hoops_GPIIR->_hoops_GHIIR != null) {
			_hoops_HCSR = _hoops_SCCSS (_hoops_GPIIR->_hoops_GHIIR, &head);
			_hoops_HCSR->_hoops_APHHP = sc;

			_hoops_RGGA (_hoops_HCSR->_hoops_SRCP == dc->_hoops_AAHSR)
				if ((_hoops_HCSR = _hoops_HCSR->_hoops_SCAAR) == null) break; /* (_hoops_PSP _hoops_SCCHH) */

			if (_hoops_HCSR != null) {
				_hoops_GHCSS (nr, _hoops_HCSR);
				elaborate_leaves (nr, _hoops_HCSR, true);
			}
		}
		else {	/* _hoops_PSP _hoops_HSPP _hoops_CAGH - _hoops_HAIHR _hoops_IRS _hoops_RPPS, _hoops_IPHIA */
			_hoops_HCSR = _hoops_SCCSS (dc->_hoops_AAHSR, &head);
			_hoops_HCSR->_hoops_APHHP = sc;

			_hoops_GHCSS (nr, _hoops_HCSR);

			if (BIT (dc->_hoops_AAHSR->_hoops_RCGC, T_WINDOWS) &&
				dc->_hoops_AAHSR->_hoops_RGRPR != null) {
				_hoops_RSAI (&nr->_hoops_IRR->locks, _hoops_PIGRA, &_hoops_HCSR->locks);
				_hoops_RSAI (&nr->_hoops_IRR->_hoops_HHGIP, _hoops_PIGRA, &_hoops_HCSR->_hoops_HHGIP);
				HD_Select_Inner_Window (dc->_hoops_AAHSR->_hoops_RGRPR, _hoops_HCSR);
			}

			elaborate_leaves (nr, _hoops_HCSR, true);
		}
	}

	if (_hoops_GPIIR->_hoops_HPIIR != null)
		_hoops_GPSSS(nr, _hoops_GPIIR, sc);
	if (sc->_hoops_GCCAH-1 > sc->_hoops_GCCIA)
		_hoops_APSSS(nr, _hoops_GPIIR, sc);
	if (_hoops_GPIIR->_hoops_APIIR != null)
		_hoops_ACCSS (sc, _hoops_GPIIR->_hoops_APIIR);


	_hoops_AACAS (head);
	_hoops_RCCSS (sc->_hoops_ASCAH);
#ifndef DISABLE_POLY_SELECTION
	_hoops_AHCSS (sc);
#endif

	FREE (sc, _hoops_ACCCP);
	dc->_hoops_APHHP = null;

	dc->_hoops_CPGPR = _hoops_PPSSS;

	while (_hoops_HGRS-- > 0)
		_hoops_SGRS (dc);

	return (_hoops_GPIIR->_hoops_APIIR != null);
#else
	return false;
#endif
}

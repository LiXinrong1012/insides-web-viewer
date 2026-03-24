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
 * $Id: obf_tmp.txt 1.41 2010-09-22 02:29:38 trask Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "database.h"
#include "hd_proto.h"
#include "span.h"

/*
 * _hoops_GISP _hoops_IRS _hoops_PSCHR _hoops_CRGR _hoops_IRS 24 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 * _hoops_PPR 16 _hoops_IGRH _hoops_HCH _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polydot_C24_Z16 (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const				*points) {
#ifndef _hoops_GCSIR
	_hoops_RCSIR					pt[1];
	Driver_Color				color;
	RGBAS32 alter * const		*_hoops_ACSIR;
	_hoops_RAAH alter * const			*_hoops_PCSIR;
	_hoops_HCSIR const		*_hoops_ICSIR;
	bool						_hoops_CCSIR = !BIT(nr->transform_rendition->flags, _hoops_ISH);

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polydot (nr, count, points, 0, _hoops_SCSIR);
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
	color = nr->_hoops_AHP->color;

	while (count-- > 0) {
		_hoops_RAAH alter					*_hoops_HSSIR;
		RGBAS32 alter				*_hoops_RPPA;

		LOAD_ARGUMENT (points);
		TRUNCATE_POINT (points, 0, pt, 0, x);
		TRUNCATE_POINT (points, 0, pt, 0, y);
		TRUNCATE_POINT (points, 0, pt, 0, z);

		pt[0].x -= _hoops_ICSIR->offset.x;
		pt[0].y -= _hoops_ICSIR->offset.y;

		pt[0].z += nr->transform_rendition->_hoops_SHIH * 
			_hoops_ISSIR(nr->transform_rendition);


		_hoops_ACSIR = &((_hoops_CSSIR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[pt[0].y];
		_hoops_PCSIR = &((_hoops_SSSIR)_hoops_ICSIR->depth_buffer->_hoops_RCPIR)[pt[0].y];

		_hoops_HSSIR = &_hoops_PCSIR[0][pt[0].x];
		_hoops_RPPA = &_hoops_ACSIR[0][pt[0].x];

		if (pt[0].z <= (int)_hoops_HSSIR[0]) {
			if (_hoops_CCSIR)
				_hoops_HSSIR[0] = pt[0].z;
			else if (_hoops_HSSIR[0] == _hoops_GGGCR)
				_hoops_HSSIR[0]--;

			_hoops_RPPA[0] = color;
		}

		points++;
	}
#endif
}



/*
 * _hoops_GISP _hoops_IRS _hoops_PSCHR _hoops_CRGR _hoops_IRS 24 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polydot_C24_Z00 (
	Net_Rendition const &			nr,
	int								count,
	DC_Point const				*points) {
#ifndef _hoops_RGGCR
	_hoops_RCSIR					pt[1];
	RGBAS32 alter * const		*_hoops_ACSIR;
	Driver_Color					color;
	_hoops_HCSIR const		*_hoops_ICSIR;

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polydot (nr, count, points, 0, _hoops_SCSIR);
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
	color = nr->_hoops_AHP->color;

	while (count-- > 0) {
		LOAD_ARGUMENT (points);
		TRUNCATE_POINT (points, 0, pt, 0, x);
		TRUNCATE_POINT (points, 0, pt, 0, y);

		pt[0].x -= _hoops_ICSIR->offset.x;
		pt[0].y -= _hoops_ICSIR->offset.y;

		_hoops_ACSIR = &((_hoops_CSSIR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[pt[0].y];

		_hoops_ACSIR[0][pt[0].x] = color;

		points++;
	}
#endif
}


/*
 * _hoops_GISP _hoops_IRS _hoops_PSCHR _hoops_CRGR _hoops_PCCP 8 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 * _hoops_PPR 16 _hoops_IGRH _hoops_HCH _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polydot_C08_Z16 (
	Net_Rendition const &			nr,
	int								count,
	DC_Point const				*points) {
#ifndef _hoops_GCSIR
	_hoops_RCSIR					pt[1];
	unsigned char alter * const		*_hoops_ACSIR;
	_hoops_RAAH alter * const			*_hoops_PCSIR;
	unsigned char					color;
	_hoops_HCSIR const		*_hoops_ICSIR;
	bool						_hoops_AGGCR = !BIT(nr->transform_rendition->flags, _hoops_ISH);
	int								offset;
   
	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polydot (nr, count, points, 0, _hoops_SCSIR);
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
	color = (unsigned char)nr->_hoops_AHP->color._hoops_PGGCR;
	offset = (int)(nr->transform_rendition->_hoops_SHIH * 
					_hoops_ISSIR(nr->transform_rendition));

	while (count-- > 0) {
		LOAD_ARGUMENT (points);
		TRUNCATE_POINT (points, 0, pt, 0, x);
		TRUNCATE_POINT (points, 0, pt, 0, y);
		TRUNCATE_POINT (points, 0, pt, 0, z);

		pt[0].x -= _hoops_ICSIR->offset.x;
		pt[0].y -= _hoops_ICSIR->offset.y;
		pt[0].z += offset;
		
		_hoops_ACSIR = &((_hoops_HGGCR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[pt[0].y];
		_hoops_PCSIR = &((_hoops_SSSIR)_hoops_ICSIR->depth_buffer->_hoops_RCPIR)[pt[0].y];

		if (pt[0].z <= (int)_hoops_PCSIR[0][pt[0].x]) {
			if (_hoops_AGGCR)
				_hoops_PCSIR[0][pt[0].x] = pt[0].z;
			_hoops_ACSIR[0][pt[0].x] = color;
		}

		points++;
	}
#endif
}


/*
 * _hoops_GISP _hoops_IRS _hoops_PSCHR _hoops_CRGR _hoops_PCCP 8 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polydot_C08_Z00 (
	Net_Rendition const &			nr,
	int								count,
	DC_Point const				*points) {
#ifndef _hoops_RGGCR
	_hoops_RCSIR					pt[1];
	unsigned char alter * const		*_hoops_ACSIR;
	unsigned char					color;
	_hoops_HCSIR const		*_hoops_ICSIR;

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polydot (nr, count, points, 0, _hoops_SCSIR);
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
	color = (unsigned char)nr->_hoops_AHP->color._hoops_PGGCR;

	while (count-- > 0) {
		LOAD_ARGUMENT (points);
		TRUNCATE_POINT (points, 0, pt, 0, x);
		TRUNCATE_POINT (points, 0, pt, 0, y);

		pt[0].x -= _hoops_ICSIR->offset.x;
		pt[0].y -= _hoops_ICSIR->offset.y;

		_hoops_ACSIR = &((_hoops_HGGCR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[pt[0].y];

		_hoops_ACSIR[0][pt[0].x] = color;

		points++;
	}
#endif
}



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
 * $Id: obf_tmp.txt 1.15 2010-06-04 21:37:19 jason Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "database.h"
#include "hd_proto.h"
#include "span.h"


GLOBAL_FUNCTION void HD_SZB_DC_Rectangle (
	Net_Rendition const &			nr,
	int								left,
	int								right,
	int								bottom,
	int								top) {
	_hoops_HCSIR alter *	_hoops_ICSIR;
	DC_Point						pts[4];

	_hoops_ICSIR = (_hoops_HCSIR alter *)nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	pts[0].x = (float)left;	   pts[0].y = (float)bottom;
	pts[1].x = (float)right;   pts[1].y = (float)bottom;
	pts[2].x = (float)left;	   pts[2].y = (float)top;
	pts[3].x = (float)right;   pts[3].y = (float)top;

	/* _hoops_GPGP _hoops_HAGIR, _hoops_AHCR _hoops_HSH _hoops_GRS _hoops_IIP _hoops_SHH _hoops_SIGR _hoops_PGGA _hoops_CIPSI
	 * _hoops_CHR _hoops_RGAR _hoops_CHCC _hoops_GGR _hoops_GRAA-_hoops_CCSHP-_hoops_ISSGR _hoops_CCH. _hoops_GPGP _hoops_PAHSR, _hoops_SHH
	 * _hoops_AGAPR _hoops_PPR _hoops_RSPC _hoops_HHH _hoops_HSH.
	 */
	pts[0].z = pts[1].z = pts[2].z = pts[3].z = nr->transform_rendition->_hoops_PCHH;

	_hoops_ICSIR->input.vertex[0].point = &pts[0];
	_hoops_ICSIR->input.vertex[1].point = &pts[1];
	_hoops_ICSIR->input.vertex[2].point = &pts[2];
	_hoops_ICSIR->input.vertex[3].point = &pts[3];
	_hoops_ICSIR->input.color = nr->_hoops_IHA->color;

	_hoops_ICSIR->input._hoops_AIPRA._hoops_PPCCP = _hoops_HRHSP;
	_hoops_ICSIR->input._hoops_AIPRA.test = _hoops_HRHSP;
	_hoops_ICSIR->input._hoops_AIPRA.update = _hoops_GPSCP;
	if (BIT(nr->transform_rendition->flags, _hoops_PASP)) {
		_hoops_ICSIR->input._hoops_AIPRA.test				|= _hoops_IRHSP;
		_hoops_ICSIR->input._hoops_AIPRA.update				|= _hoops_IRHSP;
	}

	HD_SZB_Process_Rectangle (nr);
}




GLOBAL_FUNCTION void HD_SZB_Process_Rectangle (
	Net_Rendition const &		nr) {
#ifndef _hoops_GCSIR
	_hoops_HCSIR alter *	_hoops_ICSIR;
	int							left, right, bottom, top, z;
	Int_Rectangle				_hoops_GPHH;
	int							test, update, _hoops_PPCCP;

	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;

#if 0
#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif
#endif

	_hoops_ICSIR = (_hoops_HCSIR alter *)nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	test = _hoops_ICSIR->input._hoops_AIPRA.test & ~_hoops_ICSIR->input._hoops_SASCP.test | _hoops_ICSIR->input.required.test;
	update = _hoops_ICSIR->input._hoops_AIPRA.update & ~_hoops_ICSIR->input._hoops_SASCP.update | _hoops_ICSIR->input.required.update;
	_hoops_PPCCP = _hoops_ICSIR->input._hoops_AIPRA._hoops_PPCCP & ~_hoops_ICSIR->input._hoops_SASCP._hoops_PPCCP | _hoops_ICSIR->input.required._hoops_PPCCP;

	_hoops_GPHH.left	= _hoops_IHCR->_hoops_AGAA.left	- _hoops_ICSIR->offset.x;
	_hoops_GPHH.right	= _hoops_IHCR->_hoops_AGAA.right	- _hoops_ICSIR->offset.x;
	_hoops_GPHH.bottom = _hoops_IHCR->_hoops_AGAA.bottom - _hoops_ICSIR->offset.y;
	_hoops_GPHH.top	= _hoops_IHCR->_hoops_AGAA.top	- _hoops_ICSIR->offset.y;

	left   = (int)_hoops_ICSIR->input.vertex[0].point->x - _hoops_ICSIR->offset.x;
	right  = (int)_hoops_ICSIR->input.vertex[3].point->x - _hoops_ICSIR->offset.x;
	bottom = (int)_hoops_ICSIR->input.vertex[0].point->y - _hoops_ICSIR->offset.y;
	top	   = (int)_hoops_ICSIR->input.vertex[3].point->y - _hoops_ICSIR->offset.y;
	z	   = (int)_hoops_ICSIR->input.vertex[0].point->z;

	if (left > _hoops_GPHH.right || right < _hoops_GPHH.left ||
		bottom > _hoops_GPHH.top || top < _hoops_GPHH.bottom)
		return;

	if (_hoops_PPCCP == 0 || 1) {
		_hoops_RAAH alter					*_hoops_HSSIR = null;
		RGBAS32 alter				*_hoops_RPPA = null;
		unsigned char alter				*sp = null;
		_hoops_RAAH alter * const			*_hoops_PCSIR = null;
		RGBAS32 alter * const		*_hoops_ACSIR = null;
		unsigned char alter * const		*_hoops_RARGGR = null;

		if (left < _hoops_GPHH.left)
			left = _hoops_GPHH.left;
		if (right > _hoops_GPHH.right)
			right = _hoops_GPHH.right;
		if (bottom < _hoops_GPHH.bottom)
			bottom = _hoops_GPHH.bottom;
		if (top > _hoops_GPHH.top)
			top = _hoops_GPHH.top;

		if (_hoops_ICSIR->_hoops_HCSCP != null)
			_hoops_RARGGR = &((unsigned char alter * alter *)
						 _hoops_ICSIR->_hoops_HCSCP->_hoops_RCPIR)[bottom];
		if (_hoops_ICSIR->depth_buffer != null)
			_hoops_PCSIR = &((_hoops_RAAH alter * alter *)
						 _hoops_ICSIR->depth_buffer->_hoops_RCPIR)[bottom];
		if (_hoops_ICSIR->_hoops_HIAI != null)
			_hoops_ACSIR = &((RGBAS32 alter * alter *)
						 _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[bottom];

		do {
			int								x = left;

			if (_hoops_RARGGR != null)
				sp = &_hoops_RARGGR[0][x];
			if (_hoops_PCSIR != null)
				_hoops_HSSIR = &_hoops_PCSIR[0][x];
			if (_hoops_ACSIR != null)
				_hoops_RPPA = &_hoops_ACSIR[0][x];

			do {
				int		_hoops_AARGGR = _hoops_PPHSP;

				if (BIT (test, _hoops_SRHSP)) {
					int		_hoops_PARGGR = _hoops_ICSIR->input._hoops_RPHSP;
					int		_hoops_HAGR = *sp;
					int		ref = _hoops_ICSIR->input._hoops_APHSP;
					int		result;

					if (_hoops_HAGR < ref)
						result = _hoops_IAHSP;
					else if (_hoops_HAGR == ref)
						result = TEST_EQUAL;
					else
						result = TEST_GREATER;

					if ((result & _hoops_PARGGR) == 0) {
						_hoops_AARGGR = _hoops_ICSIR->input._hoops_RRIH;
						goto _hoops_SCAIP;
					}
				}

				if (BIT (test, _hoops_IRHSP)) {
					int		_hoops_CHRAS = _hoops_ICSIR->input._hoops_RCSCP;
					int		_hoops_HAGR = z;
					int		ref = *_hoops_HSSIR;
					int		result;

					if (_hoops_HAGR < ref)
						result = _hoops_IAHSP;
					else if (_hoops_HAGR == ref)
						result = TEST_EQUAL;
					else
						result = TEST_GREATER;

					if ((result & _hoops_CHRAS) == 0) {
						_hoops_AARGGR = _hoops_ICSIR->input._hoops_PRIH;
						goto _hoops_SCAIP;
					}
				}

				_hoops_AARGGR = _hoops_ICSIR->input._hoops_RHHSP;


/* _hoops_GGCR _hoops_IRPR _hoops_GIPRC _hoops_RPGP & _hoops_GIAGR (_hoops_RHGGP _hoops_RRH _hoops_HCPC _hoops_CGARA)
				_hoops_RPP (_hoops_HARGGR && ! _hoops_IARGGR  )
					_hoops_HHIIA _hoops_GCHGA;
*/


				if (BIT (update, _hoops_IRHSP))
					*_hoops_HSSIR = z;

				if (BIT (update, _hoops_GPSCP))
					_hoops_RPPA[0] = _hoops_ICSIR->input.color;

				if (BIT (update, FBI_OCCLUSION)) {
					if (++_hoops_ICSIR->input._hoops_PHHSP >=
							  _hoops_ICSIR->input._hoops_AHHSP)
						return;
				}

			  _hoops_SCAIP:
				if (BIT (update, _hoops_SRHSP)) {
					switch (_hoops_AARGGR) {
						case _hoops_PPHSP:
							break;
						case _hoops_HPHSP:
							*sp = _hoops_ICSIR->input._hoops_APHSP;
							break;
						case _hoops_IPHSP:
							if (*sp < 255) ++*sp;
							break;
						case _hoops_CPHSP:
							if (*sp > 0) --*sp;
							break;
						case _hoops_SPHSP:
							*sp = ~*sp & 0x00FF;
							break;
						case _hoops_GHHSP:
							*sp = 0;
							break;
					}
				}

				if (sp != null)
					sp++;
				if (_hoops_HSSIR != null)
					_hoops_HSSIR++;
				if (_hoops_RPPA != null)
					_hoops_RPPA++;
			} while (++x <= right);

			if (_hoops_RARGGR != null)
				++_hoops_RARGGR;
			if (_hoops_PCSIR != null)
				++_hoops_PCSIR;
			if (_hoops_ACSIR != null)
				++_hoops_ACSIR;
		} while (++bottom <= top);
	}
	else {
		/* _hoops_CIPH _hoops_PII _hoops_GGHSS _hoops_RPPS, _hoops_GAAP _hoops_GAGS/_hoops_CSCR _hoops_IGHP */

		/* _hoops_RRP _hoops_IS _hoops_ARP _hoops_GH _hoops_IRPHR _hoops_CGISH _hoops_ARPP _hoops_IRPHR _hoops_CIHH
		   (_hoops_HPGCA _hoops_PRPC _hoops_PPR _hoops_SARGA _hoops_SCIA)
		   _hoops_IRGGA _hoops_CIHH _hoops_PSCR _hoops_CPHR _hoops_RIR-_hoops_PPSCP?
		*/
	}
#endif
}

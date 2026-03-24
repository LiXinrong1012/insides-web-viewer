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
 * $Id: obf_tmp.txt 1.78 2010-10-06 19:16:28 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hpspsf.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

GLOBAL_FUNCTION void HD_Find_Geometry_Screen_Plane (
	Net_Rendition const &		nr,
	Geometry const *			geometry,
	_hoops_ARPA alter *				plane) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_ARPA const *				_hoops_SARRH = null;
	float						max;
	_hoops_ARPA						temp;

	switch (geometry->type) {
		case _hoops_CHIP: {
			/* _hoops_IRCPH _hoops_GRRC _hoops_CHR _hoops_HAR _hoops_SSCC _hoops_HPSS */
			plane->a = 0.0f;
			plane->b = 0.0f;
			plane->c = 0.0f;
			plane->d = 0.0f;
			return;
		}	_hoops_HHHI;

		case _hoops_RCIP: {
			if (!BIT (geometry->_hoops_RRHH, _hoops_ARHH))
				HI_Find_Polygon_Plane ((Polygon alter *)geometry);/*_hoops_HGPSA*/

			if (!BIT (geometry->_hoops_RRHH, _hoops_IASGP)) {
				/* _hoops_CPAP _hoops_HRGR _hoops_ARHAR */

				plane->a = 0.0f;
				plane->b = 0.0f;
				plane->c = 0.0f;
				plane->d = 0.0f;
				return;
			}

			_hoops_SARRH = &((Polygon const *)geometry)->plane;
		}	break;

		case _hoops_GRCP:
		case _hoops_RRCP:
		case _hoops_SGCP: {
			if (BIT (geometry->_hoops_RRHH, _hoops_SHHI)) {
				temp.a = temp.b = temp.d = 0.0f;
				temp.c = -1.0f;
				_hoops_SARRH = &temp;
			}
			else
				_hoops_SARRH = &((_hoops_PHPIR const *)geometry)->plane;
		}	 break;

		case _hoops_CGCP:		_hoops_SARRH = &((Ellipse const *)geometry)->plane;		break;

		case _hoops_GGCP:			_hoops_SARRH = &((Grid const *)geometry)->plane;			break;

		case _hoops_ICIP: {
			_hoops_SHPIR const *		light = (_hoops_SHPIR const *)geometry;	// _hoops_RGAR _hoops_CPSA _hoops_AHSIR _hoops_CCAC _hoops_RRR

			if (light->_hoops_PRR != _hoops_S || light->count < 3) {
				plane->a = 0.0f;
				plane->b = 0.0f;
				plane->c = 0.0f;
				plane->d = 0.0f;
				return;
			}
			HI_Figure_Plane_From_Points(light->count,
				(Point alter *)light->points, /* _hoops_ICIC _hoops_HIIC */
				&temp);
			_hoops_SARRH = &temp;
		}	break;

		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "f-s-plane confusion");
			return;
	}

	/* _hoops_CAHA _hoops_RH _hoops_IPPA */

	_hoops_RPRA const *		_hoops_APRA = _hoops_IHCR->matrix->_hoops_PPRA()->data.elements;

	/* "_hoops_IRSIR _hoops_HIHP _hoops_GAR _hoops_GPRRH . _hoops_HAICR" - _hoops_RPRRH & _hoops_APRRH */

	plane->a = _hoops_APRA[0][0] * _hoops_SARRH->a +
			   _hoops_APRA[0][1] * _hoops_SARRH->b +
			   _hoops_APRA[0][2] * _hoops_SARRH->c +
			   _hoops_APRA[0][3] * _hoops_SARRH->d;

	plane->b = _hoops_APRA[1][0] * _hoops_SARRH->a +
			   _hoops_APRA[1][1] * _hoops_SARRH->b +
			   _hoops_APRA[1][2] * _hoops_SARRH->c +
			   _hoops_APRA[1][3] * _hoops_SARRH->d;

	plane->c = _hoops_APRA[2][0] * _hoops_SARRH->a +
			   _hoops_APRA[2][1] * _hoops_SARRH->b +
			   _hoops_APRA[2][2] * _hoops_SARRH->c +
			   _hoops_APRA[2][3] * _hoops_SARRH->d;

	plane->d = _hoops_APRA[3][0] * _hoops_SARRH->a +
			   _hoops_APRA[3][1] * _hoops_SARRH->b +
			   _hoops_APRA[3][2] * _hoops_SARRH->c +
			   _hoops_APRA[3][3] * _hoops_SARRH->d;

	max = Abs (plane->a);
	if (max < Abs (plane->b)) max = Abs (plane->b);
	if (max < Abs (plane->c)) max = Abs (plane->c);

	if (max == 0.0f) {
		plane->a = 0.0f;
		plane->b = 0.0f;
		plane->c = 0.0f;
		plane->d = 0.0f;
	}
	else {
		plane->a /= max;
		plane->b /= max;
		plane->c /= max;
		plane->d /= max;
	}
}


GLOBAL_FUNCTION float HD_Find_Geometry_Screen_Plane_C (
	Net_Rendition const &		nr,
	Geometry const *			geometry) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_ARPA const *				_hoops_SARRH;
	_hoops_ARPA						temp;

	switch (geometry->type) {
		case _hoops_RCIP: {
			Polygon alter *		polygon = (Polygon alter *)geometry;

			if (!BIT (polygon->_hoops_RRHH, _hoops_ARHH))
				HI_Find_Polygon_Plane (polygon); /* _hoops_HGPSA */

			if (!BIT (polygon->_hoops_RRHH, _hoops_IASGP))
				return 0.0f;

			_hoops_SARRH = &polygon->plane;
		}	break;

		case _hoops_GRCP:
		case _hoops_RRCP:
		case _hoops_SGCP: {
			_hoops_PHPIR alter *		_hoops_HGSSR = (_hoops_PHPIR alter *)geometry;

			if (BIT (geometry->_hoops_RRHH, _hoops_SHHI)) {
				temp.a = temp.b = temp.d = 0.0f;
				temp.c = -1.0f;
				_hoops_SARRH = &temp;
			}
			else
				_hoops_SARRH = &_hoops_HGSSR->plane;
		}	 break;

		case _hoops_CGCP:		_hoops_SARRH = &((Ellipse *)geometry)->plane;	break;
		case _hoops_GGCP:			_hoops_SARRH = &((Grid *)geometry)->plane;		break;

		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "f-s-plane confusion");
			return 0.0f;
	}

	_hoops_RPRA const *	_hoops_APRA = _hoops_IHCR->matrix->_hoops_PPRA()->data.elements;

	return _hoops_APRA[2][0] * _hoops_SARRH->a +
		   _hoops_APRA[2][1] * _hoops_SARRH->b +
		   _hoops_APRA[2][2] * _hoops_SARRH->c +
		   _hoops_APRA[2][3] * _hoops_SARRH->d;
}




GLOBAL_FUNCTION void HD_Compute_Screen_Plane_Facings (
	Net_Rendition const &		nr,
	int							count,
	_hoops_ARPA const *				planes,
	bool						_hoops_CRCPH,
	int alter *					directions) {
	_hoops_HRPA const *			_hoops_SRCPH;
	float const *				_hoops_GACPH;

	if (_hoops_CRCPH) {
		if (!BIT (nr->transform_rendition->flags, _hoops_HCPHP))
			HD_Validate_Object_To_Proj (nr);
		_hoops_SRCPH = &nr->transform_rendition->object_to_projection_matrix->data;
		nr->transform_rendition->object_to_projection_matrix->_hoops_PPRA();
	}
	else {
		_hoops_SRCPH = &nr->transform_rendition->_hoops_SPH->_hoops_GRCC;
		if (_hoops_SRCPH->_hoops_APRA == null)
			HI_Validate_Matrix_Adjoint ((_hoops_HRPA alter *)_hoops_SRCPH);
	}

	_hoops_GACPH = _hoops_SRCPH->_hoops_APRA->data.elements[2];

#ifdef _hoops_IIIPA
	if (BIT (HOOPS_WORLD->_hoops_CIIPA, _hoops_SIIPA) && count >= 4) {
		unsigned int			mxcsr;

		if (HOOPS_WORLD->_hoops_RCIPA != 0) {
			unsigned int			temp;

			__asm	lea			eax, temp
			STMXCSR (EAX)

			mxcsr = temp;
			temp |= HOOPS_WORLD->_hoops_RCIPA;	/* _hoops_ACIPA _hoops_GHPA & _hoops_PCIPA-_hoops_RAHP-_hoops_GHPA _hoops_RPP _hoops_APP */

			__asm	lea			eax, temp	/* _hoops_GGR _hoops_AGIR _hoops_IHRPR _hoops_APGR _hoops_HCIPA _hoops_GPP _hoops_ICIPA */
			LDMXCSR	(EAX)
		}

		/* _hoops_PAGA: _hoops_SR _hoops_HHGC _hoops_IS:
				_hoops_AA {} _hoops_HPGP ((_hoops_RPR -= 4) >= 4);
		   _hoops_HIH _hoops_RH _hoops_RPGP _hoops_HRGR _hoops_SCIPA.  _hoops_RIIA _hoops_SR _hoops_PAH:
				_hoops_RPR -= 4;
				_hoops_AA {} _hoops_HPGP ((_hoops_RPR -= 4) >= 0);
				_hoops_RPR += 4;
		   _hoops_RGR _hoops_IGRIR 2 _hoops_GSRH, _hoops_HIH _hoops_GSIPA _hoops_PCCP _hoops_IHH _hoops_RPGP _hoops_ASSA _hoops_RH _hoops_HAPR
		*/

		__asm {
			mov				eax, dword ptr planes
			mov				ebx, dword ptr directions
			mov				ecx, count

			; _hoops_CSIPA the part of the matrix _hoops_IHIIR _hoops_HSIPA, _hoops_RACPH for _hoops_AACPH
			mov				edx, dword ptr _hoops_GACPH
			MOVUPS			(XMM0, EDX)
			XORPS			(XMM7, XMM7)

			sub				ecx, 4					; _hoops_RSIPA count for 0-_hoops_ASIPA test
		  _hoops_PSIPA:
			; _hoops_CSIPA 4 planes
			MOVAPS			(XMM1, EAX)				; 1: _hoops_IRPPA
			add				eax, 16
			MOVAPS			(XMM2, EAX)				; 2: _hoops_CRPPA
			add				eax, 16
			MOVAPS			(XMM3, EAX)				; 3: _hoops_PACPH
			add				eax, 16
			MOVAPS			(XMM4, EAX)				; 4: _hoops_HACPH
			add				eax, 16

			; _hoops_ARCPA the _hoops_PRGRA
			MULPS			(XMM1, XMM0)			; 1: _hoops_GIGCR = p1 _hoops_SSRP _hoops_IACPH
			MULPS			(XMM2, XMM0)			; 2: _hoops_RIGCR = p2 _hoops_SSRP _hoops_IACPH
			MULPS			(XMM3, XMM0)			; 3: d3 = _hoops_IAPH _hoops_SSRP _hoops_IACPH
			MULPS			(XMM4, XMM0)			; 4: _hoops_CACPH = _hoops_SRRPA _hoops_SSRP _hoops_IACPH

			; "transpose" _hoops_SACPH _hoops_IHIIR _hoops_GPCPH _hoops_GAGSP _hoops_RPCPH
			MOVAPS			(XMM5, XMM1)			; 5: _hoops_APCPH of _hoops_GIGCR
			MOVAPS			(XMM6, XMM3)			; 6: _hoops_APCPH of d3

			UNPCKLPS		(XMM1, XMM2)			; 1: _hoops_PPCPH, _hoops_HPCPH, _hoops_IPCPH, _hoops_CPCPH
			UNPCKLPS		(XMM3, XMM4)			; 3: d3a, _hoops_SPCPH, d3b, _hoops_GHCPH

			UNPCKHPS		(XMM5, XMM2)			; 5: _hoops_RHCPH, _hoops_AHCPH, _hoops_PHCPH, _hoops_HHCPH
			UNPCKHPS		(XMM6, XMM4)			; 6: d3c, _hoops_IHCPH, d3d, _hoops_CHCPH

			MOVAPS			(XMM2, XMM1)			; 2: _hoops_PPCPH, _hoops_HPCPH, _hoops_IPCPH, _hoops_CPCPH
			MOVAPS			(XMM4, XMM5)			; 4: _hoops_RHCPH, _hoops_AHCPH, _hoops_PHCPH, _hoops_AHCPH

			SHUFPS			(XMM1, XMM3, 0x44)		; 1: _hoops_PPCPH, _hoops_HPCPH, d3a, _hoops_SPCPH
			SHUFPS			(XMM2, XMM3, 0xEE)		; 2: _hoops_IPCPH, _hoops_CPCPH, d3b, _hoops_GHCPH
			SHUFPS			(XMM4, XMM6, 0x44)		; 4: _hoops_RHCPH, _hoops_AHCPH, d3c, _hoops_IHCPH
			SHUFPS			(XMM5, XMM6, 0xEE)		; 5: _hoops_PHCPH, _hoops_HHCPH, d3d, _hoops_CHCPH

			; _hoops_ARAHR the _hoops_CAGCR to _hoops_SHCPH _hoops_HGHHA values for planes
			ADDPS			(XMM1, XMM2)			; 1: 1a + 1b, 2a + 2b...
			ADDPS			(XMM4, XMM5)			; 4: 1c + 1d, 2a + 2b...
			ADDPS			(XMM1, XMM4)			; 1: 1C, 2C, 3C, 4C

			; and _hoops_HACPA which _hoops_GICPH _hoops_RICPH point
			CMPLTPS			(XMM1, XMM7)			; 1: _hoops_HGHHA < 0.0

			MOVAPS			(EBX, XMM1)				; _hoops_PACPA 4 _hoops_AICPH
			add				ebx, 16

			; _hoops_HACPA if _hoops_IHIIR _hoops_IACPA 4 _hoops_CACPA to do
			sub				ecx, 4
			jge				_hoops_PSIPA

			; _hoops_SACPA count & _hoops_AICHR in case _hoops_IHIIR _hoops_IACPA _hoops_CACPA to process _hoops_GPCPA
			mov				dword ptr planes, eax
			mov				dword ptr directions, ebx
			add				ecx, 4
			mov				count, ecx
		}

		if (HOOPS_WORLD->_hoops_RCIPA != 0) {
			__asm	lea			eax, mxcsr
			LDMXCSR	(EAX)
		}
	}
#endif

#if 0
/* _hoops_RGR _hoops_CSAP _hoops_HAR _hoops_RICPR _hoops_CIAH
#_hoops_IHS _hoops_PICPH
*/
    if (count >= 4) {
		vector float _hoops_HICPH = (vector float) _hoops_IICPH(0, (unsigned char *) _hoops_GACPH);
		vector float _hoops_CICPH = (vector float) (0);
		float const *_hoops_SICPH = (float const *)planes;
		int _hoops_GCCPH = 0;
		int _hoops_RCCPH = 0;
		int _hoops_ACCPH = (count * 4) - 16;

		/* _hoops_IPRPR("\_hoops_PCCPH: 0x%08lX, _hoops_HCCPH: 0x%08lX, _hoops_SSGAR: 0x%08lX.", _hoops_ICCPH, _hoops_HCCPH, _hoops_SSGAR); */
		while (_hoops_RCCPH < _hoops_ACCPH) {
#if 1
			vector unsigned char QW0, QW1, QW2, QW3, QW4;
			vector unsigned char mask;

			QW0 = _hoops_CCCPH(_hoops_GCCPH, (unsigned char*) _hoops_SICPH);
			QW1 = _hoops_CCCPH(_hoops_GCCPH + 16, (unsigned char*) _hoops_SICPH);
			QW2 = _hoops_CCCPH(_hoops_GCCPH + 32, (unsigned char*) _hoops_SICPH);
			QW3 = _hoops_CCCPH(_hoops_GCCPH + 48, (unsigned char*) _hoops_SICPH);
			QW4 = _hoops_CCCPH(_hoops_GCCPH + 64, (unsigned char*) _hoops_SICPH);

			/* _hoops_ARPR _hoops_RH _hoops_SCCPH _hoops_PISH */
			mask = _hoops_GSCPH(0, _hoops_SICPH + _hoops_GCCPH);

			/* _hoops_HGCR _hoops_RH _hoops_RSCPH _hoops_PIH */
			vector float _hoops_ASCPH = (vector float) _hoops_PSCPH(QW0, QW1, mask);
			vector float _hoops_HSCPH = (vector float) _hoops_PSCPH(QW1, QW2, mask);
			vector float _hoops_ISCPH = (vector float) _hoops_PSCPH(QW2, QW3, mask);
			vector float _hoops_CSCPH = (vector float) _hoops_PSCPH(QW3, QW4, mask);
#else
			vector float _hoops_ASCPH = (vector float) _hoops_IICPH(_hoops_GCCPH, (unsigned char *) _hoops_SICPH);
			vector float _hoops_HSCPH = (vector float) _hoops_IICPH(_hoops_GCCPH + 16, (unsigned char *) _hoops_SICPH);
			vector float _hoops_ISCPH = (vector float) _hoops_IICPH(_hoops_GCCPH + 32, (unsigned char *) _hoops_SICPH);
			vector float _hoops_CSCPH = (vector float) _hoops_IICPH(_hoops_GCCPH + 48, (unsigned char *) _hoops_SICPH);
#endif
			_hoops_GCCPH += 16 * 4;

			_hoops_ASCPH = _hoops_SSCPH(_hoops_HICPH, _hoops_ASCPH, _hoops_CICPH);
			_hoops_HSCPH = _hoops_SSCPH(_hoops_HICPH, _hoops_HSCPH, _hoops_CICPH);
			_hoops_ISCPH = _hoops_SSCPH(_hoops_HICPH, _hoops_ISCPH, _hoops_CICPH);
			_hoops_CSCPH = _hoops_SSCPH(_hoops_HICPH, _hoops_CSCPH, _hoops_CICPH);

			vector float _hoops_GGSPH = _hoops_RGSPH(_hoops_ASCPH, _hoops_HSCPH, _hoops_ISCPH, _hoops_CSCPH);

			vector bool int _hoops_AGSPH = _hoops_PGSPH(_hoops_GGSPH, _hoops_CICPH);
			_hoops_HGSPH((vector unsigned char) _hoops_AGSPH, _hoops_RCCPH, (unsigned char *) directions);
			_hoops_RCCPH += 16;
		}
		directions += _hoops_RCCPH >> 2;
		planes += _hoops_RCCPH >> 2;
		count -= _hoops_RCCPH >> 2;
	}
#endif

	while (count-- > 0) {
		*directions++ = (_hoops_GACPH[0] * planes->a +
						 _hoops_GACPH[1] * planes->b +
						 _hoops_GACPH[2] * planes->c +
						 _hoops_GACPH[3] * planes->d) < 0.0f ? (~0) : 0;

		planes++;
	}
}



GLOBAL_FUNCTION void HD_Compute_Screen_Plane_Dot_Products (
	Net_Rendition const &		nr,
	int							count,
	_hoops_ARPA const *				planes,
	bool						_hoops_CRCPH,
	float alter *				_hoops_IGSPH) {
	_hoops_HRPA const *			_hoops_SRCPH;
	float const *				_hoops_GACPH;

	if (_hoops_CRCPH) {
		if (!BIT (nr->transform_rendition->flags, _hoops_HCPHP))
			HD_Validate_Object_To_Proj (nr);
		_hoops_SRCPH = &nr->transform_rendition->object_to_projection_matrix->data;
		nr->transform_rendition->object_to_projection_matrix->_hoops_PPRA();
	}
	else {
		_hoops_SRCPH = &nr->transform_rendition->_hoops_SPH->_hoops_GRCC;
		if (_hoops_SRCPH->_hoops_APRA == null)
			HI_Validate_Matrix_Adjoint ((_hoops_HRPA alter *)_hoops_SRCPH);
	}

	_hoops_GACPH = _hoops_SRCPH->_hoops_APRA->data.elements[2];

#ifdef _hoops_IIIPA
	if (BIT (HOOPS_WORLD->_hoops_CIIPA, _hoops_SIIPA) && count >= 4) {
		unsigned int			mxcsr;

		if (HOOPS_WORLD->_hoops_RCIPA != 0) {
			unsigned int			temp;

			__asm	lea			eax, temp
			STMXCSR (EAX)

			mxcsr = temp;
			temp |= HOOPS_WORLD->_hoops_RCIPA;	/* _hoops_ACIPA _hoops_GHPA & _hoops_PCIPA-_hoops_RAHP-_hoops_GHPA _hoops_RPP _hoops_APP */

			__asm	lea			eax, temp	/* _hoops_GGR _hoops_AGIR _hoops_IHRPR _hoops_APGR _hoops_HCIPA _hoops_GPP _hoops_ICIPA */
			LDMXCSR	(EAX)
		}

		/* _hoops_PAGA: _hoops_SR _hoops_HHGC _hoops_IS:
				_hoops_AA {} _hoops_HPGP ((_hoops_RPR -= 4) >= 4);
		   _hoops_HIH _hoops_RH _hoops_RPGP _hoops_HRGR _hoops_SCIPA.  _hoops_RIIA _hoops_SR _hoops_PAH:
				_hoops_RPR -= 4;
				_hoops_AA {} _hoops_HPGP ((_hoops_RPR -= 4) >= 0);
				_hoops_RPR += 4;
		   _hoops_RGR _hoops_IGRIR 2 _hoops_GSRH, _hoops_HIH _hoops_GSIPA _hoops_PCCP _hoops_IHH _hoops_RPGP _hoops_ASSA _hoops_RH _hoops_HAPR
		*/

		__asm {
			mov				eax, dword ptr planes
			mov				ebx, dword ptr _hoops_IGSPH
			mov				ecx, count

			; _hoops_CSIPA the part of the matrix _hoops_IHIIR _hoops_HSIPA, _hoops_RACPH for _hoops_AACPH
			mov				edx, dword ptr _hoops_GACPH
			MOVUPS			(XMM0, EDX)
			XORPS			(XMM7, XMM7)

			sub				ecx, 4					; _hoops_RSIPA count for 0-_hoops_ASIPA test
		  _hoops_PSIPA:
			; _hoops_CSIPA 4 planes
			MOVAPS			(XMM1, EAX)				; 1: _hoops_IRPPA
			add				eax, 16
			MOVAPS			(XMM2, EAX)				; 2: _hoops_CRPPA
			add				eax, 16
			MOVAPS			(XMM3, EAX)				; 3: _hoops_PACPH
			add				eax, 16
			MOVAPS			(XMM4, EAX)				; 4: _hoops_HACPH
			add				eax, 16

			; _hoops_ARCPA the _hoops_PRGRA
			MULPS			(XMM1, XMM0)			; 1: _hoops_GIGCR = p1 _hoops_SSRP _hoops_IACPH
			MULPS			(XMM2, XMM0)			; 2: _hoops_RIGCR = p2 _hoops_SSRP _hoops_IACPH
			MULPS			(XMM3, XMM0)			; 3: d3 = _hoops_IAPH _hoops_SSRP _hoops_IACPH
			MULPS			(XMM4, XMM0)			; 4: _hoops_CACPH = _hoops_SRRPA _hoops_SSRP _hoops_IACPH

			; "transpose" _hoops_SACPH _hoops_IHIIR _hoops_GPCPH _hoops_GAGSP _hoops_RPCPH
			MOVAPS			(XMM5, XMM1)			; 5: _hoops_APCPH of _hoops_GIGCR
			MOVAPS			(XMM6, XMM3)			; 6: _hoops_APCPH of d3

			UNPCKLPS		(XMM1, XMM2)			; 1: _hoops_PPCPH, _hoops_HPCPH, _hoops_IPCPH, _hoops_CPCPH
			UNPCKLPS		(XMM3, XMM4)			; 3: d3a, _hoops_SPCPH, d3b, _hoops_GHCPH

			UNPCKHPS		(XMM5, XMM2)			; 5: _hoops_RHCPH, _hoops_AHCPH, _hoops_PHCPH, _hoops_HHCPH
			UNPCKHPS		(XMM6, XMM4)			; 6: d3c, _hoops_IHCPH, d3d, _hoops_CHCPH

			MOVAPS			(XMM2, XMM1)			; 2: _hoops_PPCPH, _hoops_HPCPH, _hoops_IPCPH, _hoops_CPCPH
			MOVAPS			(XMM4, XMM5)			; 4: _hoops_RHCPH, _hoops_AHCPH, _hoops_PHCPH, _hoops_AHCPH

			SHUFPS			(XMM1, XMM3, 0x44)		; 1: _hoops_PPCPH, _hoops_HPCPH, d3a, _hoops_SPCPH
			SHUFPS			(XMM2, XMM3, 0xEE)		; 2: _hoops_IPCPH, _hoops_CPCPH, d3b, _hoops_GHCPH
			SHUFPS			(XMM4, XMM6, 0x44)		; 4: _hoops_RHCPH, _hoops_AHCPH, d3c, _hoops_IHCPH
			SHUFPS			(XMM5, XMM6, 0xEE)		; 5: _hoops_PHCPH, _hoops_HHCPH, d3d, _hoops_CHCPH

			; _hoops_ARAHR the _hoops_CAGCR to _hoops_SHCPH _hoops_HGHHA values for planes
			ADDPS			(XMM1, XMM2)			; 1: 1a + 1b, 2a + 2b...
			ADDPS			(XMM4, XMM5)			; 4: 1c + 1d, 2a + 2b...
			ADDPS			(XMM1, XMM4)			; 1: 1C, 2C, 3C, 4C

			; (do not do the _hoops_CGSPH. this should be the only _hoops_SGSPH _hoops_GRSPH this function and HD_Compute_Screen_Plane_Facings)
			;        CMPLTPS			(XMM1, XMM7)			; 1: _hoops_HGHHA < 0.0

			MOVAPS			(EBX, XMM1)				; _hoops_PACPA 4 _hoops_AICPH
			add				ebx, 16

			; _hoops_HACPA if _hoops_IHIIR _hoops_IACPA 4 _hoops_CACPA to do
			sub				ecx, 4
			jge				_hoops_PSIPA

			; _hoops_SACPA count & _hoops_AICHR in case _hoops_IHIIR _hoops_IACPA _hoops_CACPA to process _hoops_GPCPA
			mov				dword ptr planes, eax
			mov				dword ptr _hoops_IGSPH, ebx
			add				ecx, 4
			mov				count, ecx
		}

		if (HOOPS_WORLD->_hoops_RCIPA != 0) {
			__asm	lea			eax, mxcsr
			LDMXCSR	(EAX)
		}
	}
#endif

	while (count-- > 0) {
		*_hoops_IGSPH++ = _hoops_GACPH[0] * planes->a +
							 _hoops_GACPH[1] * planes->b +
							 _hoops_GACPH[2] * planes->c +
							 _hoops_GACPH[3] * planes->d;

		planes++;
	}
}



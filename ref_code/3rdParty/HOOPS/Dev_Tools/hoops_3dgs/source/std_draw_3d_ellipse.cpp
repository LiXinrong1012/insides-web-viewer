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
 * $Id: obf_tmp.txt 1.172 2010-10-02 07:04:42 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "tandt.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

#define _hoops_SHPIS		16384	/* _hoops_CRCH _hoops_IGIGC _hoops_GPPS _hoops_HPP _hoops_RGR _hoops_GHIR */
#define _hoops_HPPGS (0.5522847498f)  /* _hoops_HII _hoops_GIPIS... */

/* _hoops_CGH _hoops_SHH _hoops_RIPPR _hoops_IS _hoops_IRS _hoops_CCAH _hoops_RGHR _hoops_HPGR _hoops_HHH _hoops_PPSR */
/* _hoops_HGI _hoops_API _hoops_APPP _hoops_PCCP _hoops_PPHHH _hoops_ISII, _hoops_PPR _hoops_RIPIS _hoops_SCH _hoops_GGSR _hoops_CRGR _hoops_IRS _hoops_AIPIS,
 * _hoops_CCA 2 _hoops_CCAH _hoops_RGSHA _hoops_RSSA _hoops_GPP _hoops_PGI _hoops_PPAP _hoops_IIGR _hoops_RCSAR _hoops_GHCPR _hoops_GPHA, _hoops_PPR 1 _hoops_CCAH _hoops_SPR 
 * _hoops_IH _hoops_RH _hoops_GSHIA.  _hoops_CCSCI, "_hoops_SRHR", _hoops_IRHS _hoops_IS _hoops_HS (3*_hoops_RPR - 2)*_hoops_GGHSP(_hoops_RACIR) _hoops_PSPP */
GLOBAL_FUNCTION void HI_Generate_Polyline_Bezier (
	int count,
	Point const *	points,
	Point alter *	buffer)
{
	Point alter *ptr;
	Point v;
	int i;

	ptr = buffer;
	_hoops_RSAI (&points[0], Point, ptr);
	ptr++;
	v.x = (points[1].x - points[0].x)/4;
	v.y = (points[1].y - points[0].y)/4;
	v.z = (points[1].z - points[0].z)/4;
	ptr->x = points[0].x + v.x;
	ptr->y = points[0].y + v.y;
	ptr->z = points[0].z + v.z;
	ptr++;
	for (i = 1 ; i < count-1 ; i++) {
		v.x = (points[i+1].x - points[i-1].x)/8;
		v.y = (points[i+1].y - points[i-1].y)/8;
		v.z = (points[i+1].z - points[i-1].z)/8;
		ptr->x = points[i].x - v.x;
		ptr->y = points[i].y - v.y;
		ptr->z = points[i].z - v.z;
		ptr++;
		_hoops_RSAI (&points[i], Point, ptr);
		ptr++;
		ptr->x = points[i].x + v.x;
		ptr->y = points[i].y + v.y;
		ptr->z = points[i].z + v.z;
		ptr++;
	}
	v.x = (points[count-1].x - points[count-2].x)/4;
	v.y = (points[count-1].y - points[count-2].y)/4;
	v.z = (points[count-1].z - points[count-2].z)/4;
	ptr->x = points[count-1].x - v.x;
	ptr->y = points[count-1].y - v.y;
	ptr->z = points[count-1].z - v.z;
	ptr++;
	_hoops_RSAI (&points[count-1], Point, ptr);
}


local float _hoops_PIPIS (Vector const *_hoops_ISPI, Vector const *_hoops_CSPI)
{
	float _hoops_HRPPA = HI_Sqrt (_hoops_ISPI->x * _hoops_ISPI->x + _hoops_ISPI->y * _hoops_ISPI->y + _hoops_ISPI->z * _hoops_ISPI->z);
	float _hoops_SPPPA = HI_Sqrt (_hoops_CSPI->x * _hoops_CSPI->x + _hoops_CSPI->y * _hoops_CSPI->y + _hoops_CSPI->z * _hoops_CSPI->z);
	const float _hoops_HIPIS = 1e-7f;

	if (_hoops_SPPPA > _hoops_HRPPA * _hoops_HIPIS)
		return _hoops_HRPPA/_hoops_SPPPA;
	else 
		return 1/_hoops_HIPIS;
}

/* _hoops_IIPIS _hoops_IRS _hoops_PHIGR _hoops_PGIS _hoops_IS _hoops_RH _hoops_SRSGR _hoops_IIGR _hoops_PCCP _hoops_ICISR _hoops_PGIS, _hoops_SHRAA _hoops_GGR 
	_hoops_HISI _hoops_HSH _hoops_AAPR _hoops_CHHA */
GLOBAL_FUNCTION void HD_Validate_Elliptical_Arc (
		_hoops_GHHI const *curve, 
		Elliptical_Arc alter *arc,
		float *_hoops_CSIH) 
{
	ZERO_STRUCT (arc, Elliptical_Arc);
	switch (curve->type) {
		case _hoops_SGCP:
		case _hoops_CGCP: {
			if (BIT (curve->_hoops_RRHH, _hoops_SHHI)) {
				_hoops_AIHI const *	c;

				/* _hoops_SR _hoops_ACPA _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_PRHC _hoops_PGGA _hoops_IIH _hoops_HRGR _hoops_HAR (_hoops_GAPR) 
				   _hoops_GII _hoops_CIPIS _hoops_GPRR */
				c = (_hoops_AIHI const *)curve;
				arc->center.x = c->center.x;
				arc->center.y = c->center.y;
				arc->center.z = 0.0f;
				arc->_hoops_GGHI.x = c->radius;
				arc->_hoops_GGHI.y = 0.0f;
				arc->_hoops_GGHI.z = 0.0f;
				arc->_hoops_RGHI.x = 0.0f;
				arc->_hoops_RGHI.y = c->radius;
				arc->_hoops_RGHI.z = 0.0f;
				arc->plane.a = 0.0f;
				arc->plane.b = 0.0f;
				arc->plane.c = -1.0f;
				arc->plane.d = 0.0f;
				arc->arc_start = 0;
				arc->_hoops_PHHI = 1;
			}
			else {
				_hoops_RSAI (&curve->center, Point, &arc->center);
				_hoops_RSAI (&curve->_hoops_GGHI, Vector, &arc->_hoops_GGHI);
				_hoops_RSAI (&curve->_hoops_RGHI, Vector, &arc->_hoops_RGHI);
				_hoops_RSAI (&curve->plane, _hoops_ARPA, &arc->plane);
				arc->arc_start = 0;
				arc->_hoops_PHHI = 1;
			}
			if (_hoops_CSIH) {
				if (curve->type == _hoops_CGCP)
					*_hoops_CSIH = _hoops_PIPIS (&arc->_hoops_GGHI, &arc->_hoops_RGHI);
				else
					*_hoops_CSIH = 1;
			}
		} break;

		case _hoops_RIIP:
		case _hoops_GIIP:
		case _hoops_GRCP:
		case _hoops_RRCP: {
			if (BIT (curve->_hoops_RRHH, _hoops_SHHI)) {
				Circular_Arc_Lite const *	a;

				a = (Circular_Arc_Lite const *)curve;
				arc->center.x = a->center.x;
				arc->center.y = a->center.y;
				arc->center.z = 0.0f;
				arc->_hoops_GGHI.x = a->radius;
				arc->_hoops_GGHI.y = 0.0f;
				arc->_hoops_GGHI.z = 0.0f;
				arc->_hoops_RGHI.x = 0.0f;
				arc->_hoops_RGHI.y = a->radius;
				arc->_hoops_RGHI.z = 0.0f;
				arc->plane.a = 0.0f;
				arc->plane.b = 0.0f;
				arc->plane.c = -1.0f;
				arc->plane.d = 0.0f;
				arc->arc_start = a->arc_start;
				arc->_hoops_PHHI = a->_hoops_PHHI;
			}
			else if (curve->type == _hoops_GIIP) {
				_hoops_RSAI (curve, Elliptical_Arc, arc); /* _hoops_SCH'_hoops_GRI _hoops_AIAH _hoops_GGR _hoops_RH _hoops_RPHR _hoops_SRSGR */
				if (_hoops_CSIH)
					*_hoops_CSIH = _hoops_PIPIS (&arc->_hoops_GGHI, &arc->_hoops_RGHI);
			}
			else {
				Circular_Arc const *	a = (Circular_Arc const *)curve;
				_hoops_RSAI (&a->center, Point, &arc->center);
				_hoops_RSAI (&a->_hoops_GGHI, Vector, &arc->_hoops_GGHI);
				_hoops_RSAI (&a->_hoops_RGHI, Vector, &arc->_hoops_RGHI);
				_hoops_RSAI (&a->plane, _hoops_ARPA, &arc->plane);
				arc->arc_start = a->arc_start;
				arc->_hoops_PHHI = a->_hoops_PHHI;
				if (_hoops_CSIH)
					*_hoops_CSIH = 1;
			}
		} break;

		default:		/* _hoops_CGH _hoops_IIP _hoops_HGCR _hoops_ARI */
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, 
				"Unexpected value in HD_Validate_Elliptical_Arc");
			break;
	}
} /* _hoops_RSGR _hoops_PHGCP _hoops_AASPR _hoops_HIPIH _hoops_SIPIS */


local void _hoops_GCPIS (	
		DC_Point const *_hoops_SGISC, 
		DC_Point const *_hoops_RCPIS, 
		DC_Point const *_hoops_ACPIS, 
		int which,
		DC_Point alter *ptr)
{
	/* _hoops_IH _hoops_IRS _hoops_APRAR _hoops_HCPI.  _hoops_RH _hoops_RGSHA _hoops_RSSA _hoops_CHH _hoops_SHH:
	 *  432
	 * 5   1
	 * 6   0,_hoops_IHRPR
	 * 7   _hoops_IHAC
	 *  89A    */
	switch (which) {
		case 0:
		case 4: {  /* _hoops_CAHP _hoops_RSSA 1,2,3 */
			ptr[0].x = _hoops_SGISC->x + _hoops_RCPIS->x + _hoops_HPPGS*_hoops_ACPIS->x;
			ptr[1].x = _hoops_SGISC->x + _hoops_ACPIS->x + _hoops_HPPGS*_hoops_RCPIS->x;
			ptr[2].x = _hoops_SGISC->x + _hoops_ACPIS->x;
			ptr[0].y = _hoops_SGISC->y + _hoops_RCPIS->y + _hoops_HPPGS*_hoops_ACPIS->y;
			ptr[1].y = _hoops_SGISC->y + _hoops_ACPIS->y + _hoops_HPPGS*_hoops_RCPIS->y;
			ptr[2].y = _hoops_SGISC->y + _hoops_ACPIS->y;
		} break;
		case 1:
		case 5: {  /* _hoops_CAHP _hoops_RSSA 4,5,6 */
			ptr[0].x = _hoops_SGISC->x + _hoops_ACPIS->x - _hoops_HPPGS*_hoops_RCPIS->x;
			ptr[1].x = _hoops_SGISC->x - _hoops_RCPIS->x + _hoops_HPPGS*_hoops_ACPIS->x;
			ptr[2].x = _hoops_SGISC->x - _hoops_RCPIS->x;
			ptr[0].y = _hoops_SGISC->y + _hoops_ACPIS->y - _hoops_HPPGS*_hoops_RCPIS->y;
			ptr[1].y = _hoops_SGISC->y - _hoops_RCPIS->y + _hoops_HPPGS*_hoops_ACPIS->y;
			ptr[2].y = _hoops_SGISC->y - _hoops_RCPIS->y;
		} break;
		case 2:
		case 6: {  /* _hoops_CAHP _hoops_RSSA 7,8,9 */
			ptr[0].x = _hoops_SGISC->x - _hoops_RCPIS->x - _hoops_HPPGS*_hoops_ACPIS->x;
			ptr[1].x = _hoops_SGISC->x - _hoops_ACPIS->x - _hoops_HPPGS*_hoops_RCPIS->x;
			ptr[2].x = _hoops_SGISC->x - _hoops_ACPIS->x;
			ptr[0].y = _hoops_SGISC->y - _hoops_RCPIS->y - _hoops_HPPGS*_hoops_ACPIS->y;
			ptr[1].y = _hoops_SGISC->y - _hoops_ACPIS->y - _hoops_HPPGS*_hoops_RCPIS->y;
			ptr[2].y = _hoops_SGISC->y - _hoops_ACPIS->y;
		} break;
		case 3:
		case 7: {  /* _hoops_CAHP _hoops_RSSA 10,11,12 (_hoops_IRS._hoops_ARGI._hoops_IRS 0xA, 0xB, 0xC) */
			ptr[0].x = _hoops_SGISC->x - _hoops_ACPIS->x + _hoops_HPPGS*_hoops_RCPIS->x;
			ptr[1].x = _hoops_SGISC->x + _hoops_RCPIS->x - _hoops_HPPGS*_hoops_ACPIS->x;
			ptr[2].x = _hoops_SGISC->x + _hoops_RCPIS->x;
			ptr[0].y = _hoops_SGISC->y - _hoops_ACPIS->y + _hoops_HPPGS*_hoops_RCPIS->y;
			ptr[1].y = _hoops_SGISC->y + _hoops_RCPIS->y - _hoops_HPPGS*_hoops_ACPIS->y;
			ptr[2].y = _hoops_SGISC->y + _hoops_RCPIS->y;
		} break;
	}
}

local void _hoops_PCPIS (
		DC_Point const *_hoops_SGISC, 
		DC_Point const *_hoops_RCPIS, 
		DC_Point const *_hoops_ACPIS, 
		float _hoops_GGHCR,
		float _hoops_AGHCR,
		DC_Point alter *pt)
{
	pt->x = _hoops_SGISC->x + _hoops_RCPIS->x*_hoops_AGHCR + _hoops_ACPIS->x*_hoops_GGHCR;
	pt->y = _hoops_SGISC->y + _hoops_RCPIS->y*_hoops_AGHCR + _hoops_ACPIS->y*_hoops_GGHCR;
	pt->z = 0;
}


local void _hoops_HCPIS (
		DC_Point const *_hoops_RCPIS, 
		DC_Point const *_hoops_ACPIS, 
		float _hoops_GGHCR,
		float _hoops_AGHCR,
		Vector alter *v)
{
	v->x = (_hoops_ACPIS->x*_hoops_AGHCR - _hoops_RCPIS->x*_hoops_GGHCR);
	v->y = (_hoops_ACPIS->y*_hoops_AGHCR - _hoops_RCPIS->y*_hoops_GGHCR);
	v->z = 0;
}


/* _hoops_ICPIS _hoops_SPSSR _hoops_GHSSR: 
	_hoops_GGSR->_hoops_SISR == _hoops_PARAA->_hoops_SISR + _hoops_ACPCP*_hoops_CCPIS->_hoops_SISR == _hoops_AARAA->_hoops_SISR + _hoops_PCPCP*_hoops_SCPIS->_hoops_SISR; (_hoops_IRS)
	_hoops_GGSR->_hoops_SISR == _hoops_PARAA->_hoops_HAPC + _hoops_ACPCP*_hoops_CCPIS->_hoops_HAPC == _hoops_AARAA->_hoops_HAPC + _hoops_PCPCP*_hoops_SCPIS->_hoops_HAPC; (_hoops_RCSR)
	_hoops_CPSSR _hoops_IH _hoops_SPR _hoops_IIGR _hoops_RH _hoops_PRISA _hoops_HSH, _hoops_ACPCP _hoops_PAR _hoops_PCPCP, _hoops_IS _hoops_GRAS "_hoops_GGSR" 
	_hoops_ACPCP == (_hoops_AARAA->_hoops_SISR - _hoops_PARAA->_hoops_SISR + _hoops_PCPCP*_hoops_SCPIS->_hoops_SISR) / _hoops_CCPIS->_hoops_SISR; (_hoops_SRSIR _hoops_ACPCP _hoops_GGR (_hoops_IRS))
	_hoops_PARAA->_hoops_HAPC + ((_hoops_AARAA->_hoops_SISR - _hoops_PARAA->_hoops_SISR + _hoops_PCPCP*_hoops_SCPIS->_hoops_SISR) / _hoops_CCPIS->_hoops_SISR)*_hoops_CCPIS->_hoops_HAPC - _hoops_AARAA->_hoops_HAPC - _hoops_PCPCP*_hoops_SCPIS->_hoops_HAPC == 0; (_hoops_SIGPS _hoops_ARRS _hoops_CRGR (_hoops_RCSR))
	_hoops_PARAA->_hoops_HAPC - _hoops_AARAA->_hoops_HAPC + (_hoops_AARAA->_hoops_SISR - _hoops_PARAA->_hoops_SISR)*(_hoops_CCPIS->_hoops_HAPC/_hoops_CCPIS->_hoops_SISR) + _hoops_PCPCP*_hoops_SCPIS->_hoops_SISR*(_hoops_CCPIS->_hoops_HAPC/_hoops_CCPIS->_hoops_SISR) - _hoops_PCPCP*_hoops_SCPIS->_hoops_HAPC == 0; (_hoops_GHSI _hoops_SRSIR _hoops_PCPCP)
	_hoops_PARAA->_hoops_HAPC - _hoops_AARAA->_hoops_HAPC + (_hoops_AARAA->_hoops_SISR - _hoops_PARAA->_hoops_SISR)*(_hoops_CCPIS->_hoops_HAPC/_hoops_CCPIS->_hoops_SISR) == _hoops_PCPCP * (_hoops_SCPIS->_hoops_HAPC - _hoops_SCPIS->_hoops_SISR*_hoops_CCPIS->_hoops_HAPC/_hoops_CCPIS->_hoops_SISR); (_hoops_IHIS _hoops_PCPCP _hoops_IS _hoops_RII _hoops_PPAP _hoops_PPR _hoops_IGGHA _hoops_AAACA)
	_hoops_PCPCP = (_hoops_PARAA->_hoops_HAPC - _hoops_AARAA->_hoops_HAPC + (_hoops_AARAA->_hoops_SISR - _hoops_PARAA->_hoops_SISR)*(_hoops_CCPIS->_hoops_HAPC/_hoops_CCPIS->_hoops_SISR)) / (_hoops_SCPIS->_hoops_HAPC - _hoops_SCPIS->_hoops_SISR*_hoops_CCPIS->_hoops_HAPC/_hoops_CCPIS->_hoops_SISR); _hoops_CPHR!
*/
local void _hoops_GSPIS (
		DC_Point const *p1,
		Vector const *_hoops_RSPIS,
		DC_Point const *p2,
		Vector const *_hoops_ASPIS,
		DC_Point alter *_hoops_PAGR)
{
	float const _hoops_HIPIS = 1e-5f;
	float t, _hoops_PSPIS;

	if (_hoops_RSPIS->x < -_hoops_HIPIS || _hoops_HIPIS < _hoops_RSPIS->x) {
		_hoops_PSPIS = (_hoops_ASPIS->y - _hoops_ASPIS->x*_hoops_RSPIS->y/_hoops_RSPIS->x);
		if (-_hoops_HIPIS < _hoops_PSPIS && _hoops_PSPIS < _hoops_HIPIS) {
			_hoops_PAGR->x = (p1->x + p2->x) / 2;
			_hoops_PAGR->y = (p1->y + p2->y) / 2;
		}
		else {
			t = (p1->y - p2->y + (p2->x - p1->x)*(_hoops_RSPIS->y/_hoops_RSPIS->x)) / _hoops_PSPIS;
			_hoops_PAGR->x = p1->x + t * _hoops_RSPIS->x;
			_hoops_PAGR->y = p1->y + t * _hoops_RSPIS->y;
		}
	}
	else if (_hoops_RSPIS->y < -_hoops_HIPIS || _hoops_HIPIS < _hoops_RSPIS->y) {
		_hoops_PSPIS = (_hoops_ASPIS->x - _hoops_ASPIS->y*_hoops_RSPIS->x/_hoops_RSPIS->y);
		if (-_hoops_HIPIS < _hoops_PSPIS && _hoops_PSPIS < _hoops_HIPIS) {
			_hoops_PAGR->x = (p1->x + p2->x) / 2;
			_hoops_PAGR->y = (p1->y + p2->y) / 2;
		}
		else {
			t = (p1->x - p2->x + (p2->y - p1->y)*(_hoops_RSPIS->x/_hoops_RSPIS->y)) / _hoops_PSPIS;
			_hoops_PAGR->x = p1->x + t * _hoops_RSPIS->x;
			_hoops_PAGR->y = p1->y + t * _hoops_RSPIS->y;
		}
	}
	else {
		/* _hoops_SR _hoops_CGH _hoops_IIP _hoops_HGCR _hoops_ARI (_hoops_AHSAR _hoops_IH _hoops_CPSA _hoops_RISA _hoops_RRRC). */
		*_hoops_PAGR = *p1;
	}
	_hoops_PAGR->z = 0;
}


local void _hoops_HSPIS (
		DC_Point const *_hoops_SGISC, 
		DC_Point const *_hoops_RCPIS, 
		DC_Point const *_hoops_ACPIS, 
		float start, 
		float end, 
		DC_Point alter *ptr)
{
	DC_Point _hoops_ISPIS, _hoops_CRPIP, _hoops_RSPSA;
	Vector _hoops_CSPIS, _hoops_SSPIS;
	float _hoops_GGHIS, _hoops_RGHIS, _hoops_AGHIS, _hoops_PGHIS;

	HI_SinCos (start * 360.0f, &_hoops_GGHIS, &_hoops_RGHIS);
	HI_SinCos (end * 360.0f, &_hoops_AGHIS, &_hoops_PGHIS);
	
	_hoops_PCPIS   (_hoops_SGISC, _hoops_RCPIS, _hoops_ACPIS, _hoops_GGHIS, _hoops_RGHIS, &_hoops_ISPIS);
	_hoops_HCPIS (_hoops_RCPIS, _hoops_ACPIS, _hoops_GGHIS, _hoops_RGHIS, &_hoops_CSPIS);
	_hoops_CSPIS.x *= -1;
	_hoops_CSPIS.y *= -1;
	_hoops_PCPIS   (_hoops_SGISC, _hoops_RCPIS, _hoops_ACPIS, _hoops_AGHIS, _hoops_PGHIS, &_hoops_CRPIP);
	_hoops_HCPIS (_hoops_RCPIS, _hoops_ACPIS, _hoops_AGHIS, _hoops_PGHIS, &_hoops_SSPIS);
	_hoops_GSPIS (&_hoops_ISPIS, &_hoops_CSPIS, &_hoops_CRPIP, &_hoops_SSPIS, &_hoops_RSPSA);

	ptr[0].x = _hoops_ISPIS.x + _hoops_HPPGS*(_hoops_RSPSA.x-_hoops_ISPIS.x);
	ptr[0].y = _hoops_ISPIS.y + _hoops_HPPGS*(_hoops_RSPSA.y-_hoops_ISPIS.y);
	ptr[1].x = _hoops_CRPIP.x + _hoops_HPPGS*(_hoops_RSPSA.x-_hoops_CRPIP.x);
	ptr[1].y = _hoops_CRPIP.y + _hoops_HPPGS*(_hoops_RSPSA.y-_hoops_CRPIP.y);
	ptr[2].x = _hoops_CRPIP.x;
	ptr[2].y = _hoops_CRPIP.y;
}


/* _hoops_GPISP _hoops_IRS _hoops_HGHIS _hoops_AIPIS _hoops_IGHIS _hoops_IS _hoops_IRS _hoops_AGIS.  
   _hoops_PAGA _hoops_SGS _hoops_ISGHR _hoops_RH _hoops_GRPGS _hoops_ACPH, _hoops_RGR _hoops_API _hoops_RHAP
   _hoops_HAR _hoops_HPCAR _hoops_SGS _hoops_RH _hoops_PGIS'_hoops_GRI _hoops_AHIRH _hoops_CHR _hoops_IRSS-_hoops_RGCGA.  */
GLOBAL_FUNCTION void HD_DC_Generate_Elliptical_Bezier (
		Net_Rendition const & nr,
		DC_Point const		 *_hoops_SGISC,
		DC_Point const		 *_hoops_RCPIS,
		DC_Point const		 *_hoops_ACPIS,
		float 				 start,
		float 				 end, 
		int alter				 *count,
		DC_Point alter		 *buffer) 
{
	const float _hoops_HIPIS = 1e-5f;
	int i;
	DC_Point *ptr;

	UNREFERENCED (nr);

	if (start < 0) {
		start += 1;
		end += 1;
	}
	/* _hoops_RPP _hoops_RSGR < _hoops_HSPP _hoops_SGS _hoops_AGSR _hoops_SR _hoops_HS _hoops_IS _hoops_PHHR _hoops_AARI _hoops_RH _hoops_RGRRR _hoops_PPRRR */
	if (end < start)
		end += 1;

	ZERO_ARRAY (buffer, 16, DC_Point);
	ptr = buffer;
	if (start == 0 && end == 1) {
		/* _hoops_IRS _hoops_APRAR _hoops_HCPI.  _hoops_RGSHA _hoops_RSSA, _hoops_GGR _hoops_AGR:
		 *  432
		 * 5   1
		 * 6   0,_hoops_IHRPR
		 * 7   _hoops_IHAC
		 *  89A    */
		ptr[0].x = _hoops_SGISC->x + _hoops_RCPIS->x;
		ptr[0].y = _hoops_SGISC->y + _hoops_RCPIS->y;
		ptr++;
		for (i = 0 ; i < 4 ; i++) {
			_hoops_GCPIS (_hoops_SGISC, _hoops_RCPIS, _hoops_ACPIS, i, ptr);
			ptr += 3;
		}
		*count = 13;
	}
	else {
		float t, _hoops_HGGRH, _hoops_GGHCR, _hoops_AGHCR;
		bool done = false;

		t = 0;
		i = 0;
		_hoops_HGGRH = 0.25f;
		HI_SinCos (start * 360.0f, &_hoops_GGHCR, &_hoops_AGHCR);
		_hoops_PCPIS (_hoops_SGISC, _hoops_RCPIS, _hoops_ACPIS, _hoops_GGHCR, _hoops_AGHCR, ptr);
		ptr++;
		while (!done) {
			if (start < t + _hoops_HGGRH - _hoops_HIPIS) {
				/* _hoops_RH _hoops_PGIS _hoops_RRGPR _hoops_GGR _hoops_RH _hoops_SCGR _hoops_RCIH */
				if (end < t + _hoops_HGGRH - _hoops_HIPIS) {
					/* _hoops_RRGPR _hoops_PPR _hoops_HCPA _hoops_GIAA _hoops_PSHR _hoops_RCIH */
					_hoops_HSPIS (_hoops_SGISC, _hoops_RCPIS, _hoops_ACPIS, start, end, ptr);
					ptr += 3;
					done = true;
				}
				else {
					if (start > t + _hoops_HIPIS) {
						/* _hoops_IRS _hoops_IASI _hoops_ICSHR _hoops_IS _hoops_HSPP (_hoops_GAAP)*/
						_hoops_HSPIS (_hoops_SGISC, _hoops_RCPIS, _hoops_ACPIS, start, t + _hoops_HGGRH, ptr);
						t += _hoops_HGGRH;
						i++;
						ptr += 3;
					}
					while (t + _hoops_HGGRH < end + _hoops_HIPIS) {
						/* _hoops_APRAR _hoops_PCAPA _hoops_GGR _hoops_GAPA _hoops_HSPP _hoops_PPR _hoops_RSGR (_hoops_RPP _hoops_GII)*/
						_hoops_GCPIS (_hoops_SGISC, _hoops_RCPIS, _hoops_ACPIS, i, ptr);
						t += _hoops_HGGRH;
						i++;
						ptr += 3;
					}
					if (t < end - _hoops_HIPIS) {
						/* _hoops_IRS _hoops_IASI _hoops_ICSHR _hoops_IS _hoops_RSGR (_hoops_GAAP)*/
						_hoops_HSPIS (_hoops_SGISC, _hoops_RCPIS, _hoops_ACPIS, t, end, ptr);
						ptr += 3;
					}
					done = true;
				}
			}
			t += _hoops_HGGRH;
			i++;
		}
		*count = ptr - buffer;
		if (*count < 4) {
			/* _hoops_SR _hoops_CGH _hoops_SHR _hoops_PSSP _hoops_HPGR _hoops_CHGC _hoops_SPR _hoops_IIGR _hoops_RH _hoops_ARAR _hoops_SGS _hoops_GGCR _hoops_HHH _hoops_RSSA _hoops_IS _hoops_RH _hoops_AIPIS */
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, 
				"Unexpected value in HD_DC_Generate_Elliptical_Bezier");
		}
	}
}

/* _hoops_GAR _hoops_ARRS, _hoops_HIH _hoops_PHCH _hoops_HII 3d _hoops_IS _hoops_CSPH _hoops_SRS */
GLOBAL_FUNCTION void HD_Generate_Elliptical_Bezier (
	Net_Rendition const	&		nr,
	_hoops_GHHI const *			curve, 
	int *						count,
	DC_Point *					buffer) {
	DC_Point					_hoops_CGHIS, _hoops_SGISC, _hoops_SPPSI[2];
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_RPRA const *			elements = _hoops_IHCR->matrix->data.elements;
	Elliptical_Arc				arc;

	HD_Validate_Elliptical_Arc (curve, &arc, null);

	_hoops_SGISC.x = _hoops_HPRA (elements, arc.center);
	_hoops_SGISC.y = _hoops_IPRA (elements, arc.center);
	_hoops_CGHIS.x = _hoops_HPRA (elements, _hoops_HPCH::_hoops_IPCH);
	_hoops_CGHIS.y = _hoops_IPRA (elements, _hoops_HPCH::_hoops_IPCH);
	_hoops_SPPSI[0].x = _hoops_HPRA (elements, arc._hoops_GGHI);
	_hoops_SPPSI[0].y = _hoops_IPRA (elements, arc._hoops_GGHI);
	_hoops_SPPSI[1].x = _hoops_HPRA (elements, arc._hoops_RGHI);
	_hoops_SPPSI[1].y = _hoops_IPRA (elements, arc._hoops_RGHI);

	if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH) {
		float w;
		w = _hoops_PHCP (elements, arc.center);
		_hoops_SGISC.x /= w;
		_hoops_SGISC.y /= w;
		w = _hoops_PHCP (elements, _hoops_HPCH::_hoops_IPCH);
		_hoops_CGHIS.x /= w;
		_hoops_CGHIS.y /= w;
		w = _hoops_PHCP (elements, arc._hoops_GGHI);
		_hoops_SPPSI[0].x /= w;
		_hoops_SPPSI[0].y /= w;
		w = _hoops_PHCP (elements, arc._hoops_RGHI);
		_hoops_SPPSI[1].x /= w;
		_hoops_SPPSI[1].y /= w;
	}
	_hoops_SPPSI[0].x -= _hoops_CGHIS.x;
	_hoops_SPPSI[0].y -= _hoops_CGHIS.y;
	_hoops_SPPSI[1].x -= _hoops_CGHIS.x;
	_hoops_SPPSI[1].y -= _hoops_CGHIS.y;

	HD_DC_Generate_Elliptical_Bezier (nr, &_hoops_SGISC, &_hoops_SPPSI[0], &_hoops_SPPSI[1], arc.arc_start, arc._hoops_PHHI, count, buffer);
}



/*
 * _hoops_SHHH _hoops_ASRC _hoops_CCA _hoops_AAPC _hoops_ARP _hoops_IS _hoops_IHIR-_hoops_AGIS _hoops_RAAA _hoops_IIGR
 *				  0	  _hoops_PSP _hoops_RSSA _hoops_IS _hoops_PGSA
 *				  1	  _hoops_PGSA _hoops_IRS _hoops_PSCHR
 *				 4*_hoops_ACHP  _hoops_PGSA _hoops_IRS _hoops_AGIS
 */
local bool _hoops_SGHIS (
	Net_Rendition const &		nr,
	_hoops_GHHI const *			curve,
	DC_Point alter *			_hoops_SGISC,
	DC_Point alter *			_hoops_GRHIS,
	int alter *					_hoops_HGII,
	float alter *				start,
	float alter *				end) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_RPRA const *			elements = _hoops_IHCR->matrix->data.elements;
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	Point						pt;
	Vector						_hoops_IHHI, _hoops_CHHI;

	if (BIT (curve->_hoops_RRHH, _hoops_SHHI)) {
		_hoops_AIHI const *	c;
		c = (_hoops_AIHI const *)curve;		/* _hoops_IHRI _hoops_IH _hoops_PIHI _hoops_HAH */

		pt.x = c->center.x;
		pt.y = c->center.y;
		pt.z = 0.0f;

		_hoops_SGISC->x = _hoops_PRPPI (elements, pt);
		_hoops_SGISC->y = _hoops_HRPPI (elements, pt);
		_hoops_SGISC->z = 0.0f;

		pt.x += c->radius;
		_hoops_IHHI.x = _hoops_PRPPI (elements, pt) - _hoops_SGISC->x;
		_hoops_IHHI.y = _hoops_HRPPI (elements, pt) - _hoops_SGISC->y;

		pt.x = c->center.x;
		pt.y += c->radius;
		_hoops_CHHI.x = _hoops_PRPPI (elements, pt) - _hoops_SGISC->x;
		_hoops_CHHI.y = _hoops_HRPPI (elements, pt) - _hoops_SGISC->y;
	}
	else {
		/* _hoops_HIHP _hoops_RHCH */
		_hoops_SGISC->x = _hoops_PRPPI (elements, curve->center);
		_hoops_SGISC->y = _hoops_HRPPI (elements, curve->center);
		_hoops_SGISC->z = 0.0f;

		pt.z = 0.0f;

		pt.x = curve->center.x + curve->_hoops_GGHI.x;
		pt.y = curve->center.y + curve->_hoops_GGHI.y;
		_hoops_IHHI.x = _hoops_PRPPI (elements, pt) - _hoops_SGISC->x;
		_hoops_IHHI.y = _hoops_HRPPI (elements, pt) - _hoops_SGISC->y;

		pt.x = curve->center.x + curve->_hoops_RGHI.x;
		pt.y = curve->center.y + curve->_hoops_RGHI.y;
		_hoops_CHHI.x = _hoops_PRPPI (elements, pt) - _hoops_SGISC->x;
		_hoops_CHHI.y = _hoops_HRPPI (elements, pt) - _hoops_SGISC->y;
	}

	/* _hoops_RRHIS _hoops_ISPR _hoops_RPP _hoops_RGCI _hoops_SACH */
	if (BIT (_hoops_IHCR->heuristics, _hoops_PICAR) &&
		!BIT (_hoops_IHCR->flags, _hoops_AIHS)) {
		float			temp;
		float			_hoops_AGSAA, _hoops_PGSAA,
						_hoops_HGSAA, _hoops_IGSAA;
		float			left   = _hoops_SGRA->_hoops_HHCAR.left,
						right  = _hoops_SGRA->_hoops_HHCAR.right,
						bottom = _hoops_SGRA->_hoops_HHCAR.bottom,
						top	   = _hoops_SGRA->_hoops_HHCAR.top;

		_hoops_PGSAA = _hoops_AGSAA = _hoops_SGISC->x - _hoops_IHHI.x - _hoops_CHHI.x;
		_hoops_IGSAA = _hoops_HGSAA = _hoops_SGISC->y - _hoops_IHHI.y - _hoops_CHHI.y;

		temp = _hoops_SGISC->x + _hoops_IHHI.x + _hoops_CHHI.x;
		if (temp > _hoops_PGSAA) _hoops_PGSAA = temp;
		else if (temp < _hoops_AGSAA) _hoops_AGSAA = temp;
		temp = _hoops_SGISC->y + _hoops_IHHI.y + _hoops_CHHI.y;
		if (temp > _hoops_IGSAA) _hoops_IGSAA = temp;
		else if (temp < _hoops_HGSAA) _hoops_HGSAA = temp;

		temp = _hoops_SGISC->x - _hoops_IHHI.x + _hoops_CHHI.x;
		if (temp > _hoops_PGSAA) _hoops_PGSAA = temp;
		else if (temp < _hoops_AGSAA) _hoops_AGSAA = temp;
		temp = _hoops_SGISC->y - _hoops_IHHI.y + _hoops_CHHI.y;
		if (temp > _hoops_IGSAA) _hoops_IGSAA = temp;
		else if (temp < _hoops_HGSAA) _hoops_HGSAA = temp;

		temp = _hoops_SGISC->x + _hoops_IHHI.x - _hoops_CHHI.x;
		if (temp > _hoops_PGSAA) _hoops_PGSAA = temp;
		else if (temp < _hoops_AGSAA) _hoops_AGSAA = temp;
		temp = _hoops_SGISC->y + _hoops_IHHI.y - _hoops_CHHI.y;
		if (temp > _hoops_IGSAA) _hoops_IGSAA = temp;
		else if (temp < _hoops_HGSAA) _hoops_HGSAA = temp;

		if (_hoops_PGSAA < left || _hoops_AGSAA > right || _hoops_IGSAA < bottom || _hoops_HGSAA > top) {
			/* _hoops_CCGC _hoops_SIPP */
			*_hoops_HGII = 0;			/* _hoops_GRH _hoops_GCAPR _hoops_HAR _hoops_IS _hoops_PGSA */
			return	true;		/* _hoops_GA'_hoops_RA _hoops_IHIS _hoops_GPP _hoops_IS 3D _hoops_AGIR */
		}

		if (_hoops_AGSAA < left || _hoops_PGSAA > right || _hoops_HGSAA < bottom || _hoops_IGSAA > top)
			return	false;		/* _hoops_IASI -- _hoops_IIS _hoops_ICCGR _hoops_RGHH _hoops_SCH */
	}

	{
		float					radius, _hoops_SSRP;
		Vector				_hoops_ARHIS,
												_hoops_PRHIS;

		/* _hoops_RPP _hoops_HAR _hoops_RPHR _hoops_RCSA (_hoops_PSCHR _hoops_HPAHR ~= 0), _hoops_IASC _hoops_AHCRR _hoops_HAR _hoops_IPRAH */
		_hoops_SSRP = _hoops_IHHI.x * _hoops_CHHI.x + _hoops_IHHI.y * _hoops_CHHI.y;
		if (_hoops_SSRP > 1.0f || _hoops_SSRP < -1.0f) return false;

		_hoops_ARHIS.x = Abs (_hoops_IHHI.x);
		_hoops_ARHIS.y = Abs (_hoops_IHHI.y);
		_hoops_PRHIS.x = Abs (_hoops_CHHI.x);
		_hoops_PRHIS.y = Abs (_hoops_CHHI.y);

		/* _hoops_HRGR _hoops_SCH _hoops_PCCP _hoops_IRSS-_hoops_RGCGA _hoops_AGIS? */
		if (_hoops_ARHIS.x < 1.0f && _hoops_ARHIS.y > 1.0f && _hoops_PRHIS.x > 1.0f && _hoops_PRHIS.y < 1.0f ||
			_hoops_ARHIS.x > 1.0f && _hoops_ARHIS.y < 1.0f && _hoops_PRHIS.x < 1.0f && _hoops_PRHIS.y > 1.0f) {
			/* _hoops_RGCGA, _hoops_IPRAH _hoops_IASC _hoops_AHCRR */

			_hoops_GRHIS->x = _hoops_IAAA (_hoops_ARHIS.x, _hoops_PRHIS.x);
			_hoops_GRHIS->y = _hoops_IAAA (_hoops_ARHIS.y, _hoops_PRHIS.y);
			radius = _hoops_IAAA (_hoops_GRHIS->x, _hoops_GRHIS->y);
		}
		else {
			float			_hoops_HRHIS;

			/* _hoops_HAR _hoops_RGCGA, _hoops_HIH _hoops_GHCA _hoops_SHH _hoops_GRII... */

			/* _hoops_RPP _hoops_IASC _hoops_AHCRR _hoops_HAR _hoops_IRHIS, _hoops_PAH'_hoops_RA _hoops_SHH _hoops_RRAA, _hoops_HIS _hoops_AGIS _hoops_HAR _hoops_PRHC */
			radius = _hoops_ARHIS.x * _hoops_ARHIS.x + _hoops_ARHIS.y * _hoops_ARHIS.y;
			_hoops_HRHIS = (_hoops_PRHIS.x * _hoops_PRHIS.x + _hoops_PRHIS.y * _hoops_PRHIS.y) / radius;
			if (_hoops_HRHIS > 1.01f || _hoops_HRHIS < -1.01f ||
				_hoops_HRHIS < 0.99f && _hoops_HRHIS > -0.99f)
				return false;

			/* _hoops_HRGR _hoops_CPSA _hoops_PRHC, _hoops_GRAS _hoops_CCAH _hoops_PSAA */
			radius = _hoops_SGIHR (radius);
			_hoops_GRHIS->x = _hoops_GRHIS->y = radius;
		}
		_hoops_GRHIS->z = 0.0f;

		*_hoops_HGII = (int)(4.0f * _hoops_SGIHR (radius) + 0.5f);
		if (*_hoops_HGII > _hoops_SHPIS)
			*_hoops_HGII = _hoops_SHPIS;
		else if (*_hoops_HGII > 1) {
			*_hoops_HGII += 3;
			*_hoops_HGII -= *_hoops_HGII & 0x0003;
		}
	}

	if (curve->type == _hoops_RIIP ||
		curve->type == _hoops_GIIP) {
		if (BIT (curve->_hoops_RRHH, _hoops_SHHI)) {
			Circular_Arc_Lite const *	arc = (Circular_Arc_Lite const *)curve;

			*start = arc->arc_start;
			*end   = arc->_hoops_PHHI;
		}
		else {
			Elliptical_Arc const *	arc = (Elliptical_Arc const *)curve;

			*start = arc->arc_start;
			*end   = arc->_hoops_PHHI;
		}

		if (_hoops_IHHI.y == 0.0f) {
			if (_hoops_IHHI.x < 0.0f) return false;

			if (_hoops_CHHI.y < 0.0f) {
				float			_hoops_CRHIS = *start;

				*start = 1.0f - *end;
				*end   = 1.0f - _hoops_CRHIS;
			}
		}
		else {
			float			length;
			float			offset;

			length = _hoops_SGIHR (_hoops_IHHI.x * _hoops_IHHI.x + _hoops_IHHI.y * _hoops_IHHI.y);

			offset = _hoops_ISSSR (_hoops_IHHI.x / length) * (1.0f/360.0f);
			if (_hoops_IHHI.y < 0.0f)
				offset = 1.0f - offset;

			if (_hoops_IHHI.x * _hoops_CHHI.y	 >	_hoops_CHHI.x * _hoops_IHHI.y) {
				*start += offset;
				*end   += offset;
			}
			else {
				float			_hoops_CRHIS = *start;

				*start = offset - *end;
				*end   = offset - _hoops_CRHIS;
			}
		}
	}

	return true;
}


/*
 * _hoops_HCGAR _hoops_IRS _hoops_IHIR-_hoops_AGIS _hoops_RAAA _hoops_IIGR
 *		0	_hoops_PSP _hoops_RSSA _hoops_IS _hoops_PGSA
 *		2	_hoops_PGSA _hoops_AASC _hoops_ARP
 *	   2*_hoops_ACHP	_hoops_PGSA _hoops_IHIR _hoops_AGIS
 */
GLOBAL_FUNCTION int HD_Determine_Elliptical_Res (
	Net_Rendition const &		nr,
	_hoops_GHHI const *			curve) {
	float						_hoops_SRHIS;
	float						_hoops_GAHIS;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	Point						point;
	Point						min, max;
	float						w;
	int							_hoops_RAHIS = 0;
	Point const *				center;
	Vector const *				_hoops_GGHI;
	Vector const *				_hoops_RGHI;
	Point						_hoops_GRIAA;
	Vector						_hoops_RRIAA;
	Vector						_hoops_ARIAA;
	float						radius = 1.0f;
	float						_hoops_PRPHA = 1.0f;
	int							_hoops_HGII = 0;

	if (BIT (curve->_hoops_RRHH, _hoops_SHHI)) {
		_hoops_AIHI const *	c;

		c = (_hoops_AIHI const *)curve;

		_hoops_GRIAA.x = c->center.x;
		_hoops_GRIAA.y = c->center.y;
		_hoops_GRIAA.z = 0.0f;

		_hoops_RRIAA.x = c->radius;
		_hoops_RRIAA.y = 0.0f;
		_hoops_RRIAA.z = 0.0f;

		_hoops_ARIAA.x = 0.0f;
		_hoops_ARIAA.y = c->radius;
		_hoops_ARIAA.z = 0.0f;

		center = &_hoops_GRIAA;
		_hoops_GGHI = &_hoops_RRIAA;
		_hoops_RGHI = &_hoops_ARIAA;
		radius = c->radius;
	}
	else {
		center = &curve->center;
		_hoops_GGHI = &curve->_hoops_GGHI;
		_hoops_RGHI = &curve->_hoops_RGHI;
		switch (curve->type) {
			case _hoops_SGCP:
				radius = ((_hoops_PHPIR const *)curve)->radius;
				break;
			case _hoops_RIIP:
			case _hoops_GRCP:
			case _hoops_RRCP:
				radius = ((Circular_Arc const *)curve)->radius;
				break;
			case _hoops_CGCP:
			case _hoops_GIIP:

				radius = HI_Compute_Vector_Length (_hoops_GGHI);
				_hoops_PRPHA = HI_Compute_Vector_Length (_hoops_RGHI);
				if (radius>_hoops_PRPHA)
					_hoops_PRPHA = _hoops_PRPHA/radius;
				else
					_hoops_PRPHA = radius/_hoops_PRPHA;

		}
	}

	if (!nr->_hoops_ARA->_hoops_APPI._hoops_SAR) {
		int				_hoops_SIAPI;
		float			tmp;

		if ((tmp = nr->_hoops_ARA->_hoops_APPI._hoops_IPPI) != 0.0f) {
			tmp = (radius - tmp) / radius;
			if (tmp > 0) {
				tmp = 2.0f * HI_ACos (tmp);	/* _hoops_RCSA _hoops_PIIRC _hoops_HPP _hoops_IRS _hoops_RCHPA _hoops_CCA _hoops_SGS _hoops_GIHPA */
				_hoops_SIAPI = (int) (360.0f / tmp + 0.5f);
				if (_hoops_SIAPI > _hoops_HGII)
					_hoops_HGII = _hoops_SIAPI;
			}
		}
		if ((tmp = nr->_hoops_ARA->_hoops_APPI._hoops_SPPI) != 0.0f) {
			tmp = 0.5f * tmp / radius;
			if (tmp < 1.0f) {
				tmp = _hoops_SGIHR (1.0f - tmp*tmp);
				tmp = 2.0f * HI_ACos (tmp);		/* _hoops_RCSA _hoops_PIIRC _hoops_HPP _hoops_IRS _hoops_RCHPA _hoops_CCA _hoops_SGS _hoops_SPCC */
				_hoops_SIAPI = (int) (360.0f / tmp + 0.5f);
				if (_hoops_SIAPI > _hoops_HGII)
					_hoops_HGII = _hoops_SIAPI;
			}
		}
		if ((tmp = nr->_hoops_ARA->_hoops_APPI._hoops_CPPI) != 0.0f) {
			tmp *= _hoops_PRPHA;					/* (_hoops_RRHIS) _hoops_HHSA _hoops_RRI _hoops_IS _hoops_HIISR _hoops_CCA _hoops_AAHIS */
			_hoops_SIAPI = (int) (360.0f / tmp + 0.5f);
			if (_hoops_SIAPI > _hoops_HGII)
				_hoops_HGII = _hoops_SIAPI;
		}

		if (_hoops_HGII > nr->_hoops_ARA->_hoops_APPI._hoops_PPPI)
			_hoops_HGII = nr->_hoops_ARA->_hoops_APPI._hoops_PPPI;
	}
	else {
		_hoops_RPRA const *			elements = _hoops_IHCR->matrix->data.elements;
		/*
		 * _hoops_SRSGR _hoops_IASC _hoops_ARRGR _hoops_PPR _hoops_HIHP
		 */
		if (_hoops_IHCR->_hoops_HGSC == _hoops_CIPHP) {
			point.z = 0.0f; /* _hoops_HAR _hoops_IGI - _hoops_ICHHR _hoops_PAHIS _hoops_SCSAH */

			point.x = center->x - _hoops_GGHI->x - _hoops_RGHI->x;
			point.y = center->y - _hoops_GGHI->y - _hoops_RGHI->y;
			_hoops_SRHIS = _hoops_PRPPI (elements, point);
			_hoops_GAHIS = _hoops_HRPPI (elements, point);
			min.x = max.x = _hoops_SRHIS;
			min.y = max.y = _hoops_GAHIS;

			point.x = center->x - _hoops_GGHI->x + _hoops_RGHI->x;
			point.y = center->y - _hoops_GGHI->y + _hoops_RGHI->y;
			_hoops_SRHIS = _hoops_PRPPI (elements, point);
			_hoops_GAHIS = _hoops_HRPPI (elements, point);
			if (_hoops_SRHIS < min.x) min.x = _hoops_SRHIS;
			else if (_hoops_SRHIS > max.x) max.x = _hoops_SRHIS;
			if (_hoops_GAHIS < min.y) min.y = _hoops_GAHIS;
			else if (_hoops_GAHIS > max.y) max.y = _hoops_GAHIS;

			point.x = center->x + _hoops_GGHI->x + _hoops_RGHI->x;
			point.y = center->y + _hoops_GGHI->y + _hoops_RGHI->y;
			_hoops_SRHIS = _hoops_PRPPI (elements, point);
			_hoops_GAHIS = _hoops_HRPPI (elements, point);
			if (_hoops_SRHIS < min.x) min.x = _hoops_SRHIS;
			else if (_hoops_SRHIS > max.x) max.x = _hoops_SRHIS;
			if (_hoops_GAHIS < min.y) min.y = _hoops_GAHIS;
			else if (_hoops_GAHIS > max.y) max.y = _hoops_GAHIS;

			point.x = center->x + _hoops_GGHI->x - _hoops_RGHI->x;
			point.y = center->y + _hoops_GGHI->y - _hoops_RGHI->y;
			_hoops_SRHIS = _hoops_PRPPI (elements, point);
			_hoops_GAHIS = _hoops_HRPPI (elements, point);
			if (_hoops_SRHIS < min.x) min.x = _hoops_SRHIS;
			else if (_hoops_SRHIS > max.x) max.x = _hoops_SRHIS;
			if (_hoops_GAHIS < min.y) min.y = _hoops_GAHIS;
			else if (_hoops_GAHIS > max.y) max.y = _hoops_GAHIS;
		}
		else {
			point.x = center->x - _hoops_GGHI->x - _hoops_RGHI->x;
			point.y = center->y - _hoops_GGHI->y - _hoops_RGHI->y;
			point.z = center->z - _hoops_GGHI->z - _hoops_RGHI->z;
			if ((w = _hoops_PHCP (elements, point)) == 0.0f) {
				_hoops_SRHIS = _hoops_HPRA (elements, point);
				_hoops_GAHIS = _hoops_IPRA (elements, point);
			}
			else {
				_hoops_SRHIS = _hoops_HPRA (elements, point) / w;
				_hoops_GAHIS = _hoops_IPRA (elements, point) / w;
				if (w < 0.0f) ++_hoops_RAHIS;
			}
			min.x = max.x = _hoops_SRHIS;
			min.y = max.y = _hoops_GAHIS;


			point.x = center->x - _hoops_GGHI->x + _hoops_RGHI->x;
			point.y = center->y - _hoops_GGHI->y + _hoops_RGHI->y;
			point.z = center->z - _hoops_GGHI->z + _hoops_RGHI->z;
			if ((w = _hoops_PHCP (elements, point)) == 0.0f) {
				_hoops_SRHIS = _hoops_HPRA (elements, point);
				_hoops_GAHIS = _hoops_IPRA (elements, point);
			}
			else {
				_hoops_SRHIS = _hoops_HPRA (elements, point) / w;
				_hoops_GAHIS = _hoops_IPRA (elements, point) / w;
				if (w < 0.0f) ++_hoops_RAHIS;
			}
			if (_hoops_SRHIS < min.x) min.x = _hoops_SRHIS;
			else if (_hoops_SRHIS > max.x) max.x = _hoops_SRHIS;
			if (_hoops_GAHIS < min.y) min.y = _hoops_GAHIS;
			else if (_hoops_GAHIS > max.y) max.y = _hoops_GAHIS;


			point.x = center->x + _hoops_GGHI->x + _hoops_RGHI->x;
			point.y = center->y + _hoops_GGHI->y + _hoops_RGHI->y;
			point.z = center->z + _hoops_GGHI->z + _hoops_RGHI->z;
			if ((w = _hoops_PHCP (elements, point)) == 0.0f) {
				_hoops_SRHIS = _hoops_HPRA (elements, point);
				_hoops_GAHIS = _hoops_IPRA (elements, point);
			}
			else {
				_hoops_SRHIS = _hoops_HPRA (elements, point) / w;
				_hoops_GAHIS = _hoops_IPRA (elements, point) / w;
				if (w < 0.0f) ++_hoops_RAHIS;
			}
			if (_hoops_SRHIS < min.x) min.x = _hoops_SRHIS;
			else if (_hoops_SRHIS > max.x) max.x = _hoops_SRHIS;
			if (_hoops_GAHIS < min.y) min.y = _hoops_GAHIS;
			else if (_hoops_GAHIS > max.y) max.y = _hoops_GAHIS;


			point.x = center->x + _hoops_GGHI->x - _hoops_RGHI->x;
			point.y = center->y + _hoops_GGHI->y - _hoops_RGHI->y;
			point.z = center->z + _hoops_GGHI->z - _hoops_RGHI->z;
			if ((w = _hoops_PHCP (elements, point)) == 0.0f) {
				_hoops_SRHIS = _hoops_HPRA (elements, point);
				_hoops_GAHIS = _hoops_IPRA (elements, point);
			}
			else {
				_hoops_SRHIS = _hoops_HPRA (elements, point) / w;
				_hoops_GAHIS = _hoops_IPRA (elements, point) / w;
				if (w < 0.0f) ++_hoops_RAHIS;
			}
			if (_hoops_SRHIS < min.x) min.x = _hoops_SRHIS;
			else if (_hoops_SRHIS > max.x) max.x = _hoops_SRHIS;
			if (_hoops_GAHIS < min.y) min.y = _hoops_GAHIS;
			else if (_hoops_GAHIS > max.y) max.y = _hoops_GAHIS;
		}

		if (_hoops_RAHIS == 4 ||			/* _hoops_AGIRH _hoops_GHIPR */
			_hoops_RAHIS == 0 &&			/* _hoops_GGR _hoops_RIPS _hoops_PPR _hoops_SIPP */
			(min.x > _hoops_SGRA->_hoops_HHCAR.right ||
			 max.x < _hoops_SGRA->_hoops_HHCAR.left ||
			 min.y > _hoops_SGRA->_hoops_HHCAR.top ||
			 max.y < _hoops_SGRA->_hoops_HHCAR.bottom)) return 0;

		{
			float	dx = max.x - min.x;
			float	_hoops_CRRAR = max.y - min.y;

			_hoops_HGII = (int)(4.0f * _hoops_SGIHR (_hoops_IAAA (dx, _hoops_CRRAR)) + 0.5f);
			if (_hoops_RAHIS != 0)
				_hoops_HGII = 4096; /* _hoops_HAH _hoops_ACIPR */
		}
	}

	if (_hoops_HGII <= 1)
		return 2;
	else if (_hoops_HGII > _hoops_SHPIS) switch (curve->type) {
		case _hoops_SGCP:
		case _hoops_CGCP: {
			return _hoops_SHPIS;
		}	_hoops_HHHI;

		case _hoops_RIIP:
		case _hoops_GIIP:
		case _hoops_GRCP:
		case _hoops_RRCP: {
			float					start, end;
			int						_hoops_GPIGR;

			if (BIT (curve->_hoops_RRHH, _hoops_SHHI)) {
				Circular_Arc_Lite const *	arc;

				arc = (Circular_Arc_Lite const *)curve;

				start = arc->arc_start;
				end = arc->_hoops_PHHI;
			}
			else {
				Elliptical_Arc const *		arc;

				arc = (Elliptical_Arc const *)curve;
				start = arc->arc_start;
				end = arc->_hoops_PHHI;
			}

			if (end < start)
				end += 1.0f;

			if (end < start + 0.0001f)
				return 2;

			_hoops_GPIGR = (int)((float)_hoops_HGII * (end - start));
			_hoops_GPIGR += 3;
			_hoops_GPIGR -= _hoops_GPIGR & 0x03;
			if (_hoops_GPIGR <= 0) _hoops_GPIGR = 4;
			if (_hoops_GPIGR > _hoops_SHPIS) _hoops_GPIGR = _hoops_SHPIS;
			return (int)(_hoops_GPIGR / (end - start));
		}	_hoops_HHHI;
	}
	else {
		_hoops_HGII += 3;
		return _hoops_HGII - (_hoops_HGII & 0x03);
	}

	return 0; /* _hoops_ASAI _hoops_HAHIS */
}



local void _hoops_IAHIS (
	Net_Rendition const &	_hoops_SGIIH,
	DC_Point const *		_hoops_SGISC,
	DC_Point const *		_hoops_GRHIS) {
	Net_Rendition			nr = _hoops_SGIIH;

	/* _hoops_HAR _hoops_GCAAC, _hoops_HAR _hoops_HGRAR, _hoops_PSP _hoops_RGCSA, _hoops_PSP _hoops_IPSP _hoops_CHASA */

	/* _hoops_AHHCP _hoops_III _hoops_CCA _hoops_ISHA */
	nr.Modify()->_hoops_AHP = nr->_hoops_RHP;

	if (BIT (nr->_hoops_RGP, T_FACES))
		_hoops_AAPIP (nr, _hoops_SGISC, _hoops_GRHIS);
	if (ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE))
		_hoops_PAPIP (nr, _hoops_SGISC, _hoops_GRHIS);
}



/* _hoops_GASA: _hoops_RPP "_hoops_CAHIS" _hoops_HRGR _hoops_IHPR, _hoops_IIH _hoops_PIHA _hoops_SHH "_hoops_RPR"+1 _hoops_RSSA
 * _hoops_PSPP _hoops_GHIPR "_hoops_SAHIS".  _hoops_CGP _hoops_RCPP, _hoops_PSCR _hoops_RGAR _hoops_RPR _hoops_RSSA _hoops_CHR _hoops_RGHP.
 * _hoops_GCAAA _hoops_RH _hoops_PHI _hoops_IIGR _hoops_RSSA _hoops_PIISR. */
GLOBAL_FUNCTION int HD_Generate_Complete_Points (
	Point const *		center,
	Vector const *		_hoops_GGHI,
	Vector const *		_hoops_RGHI,
	int					count,
	bool				_hoops_SRIIH,
	Point alter *		pl) {
	int					ii;
	int					count2 = count / 2;
	float				theta = 90.0f;
	float				delta = 360.0f / (float)count;

	if (!_hoops_SRIIH) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				"feature not yet implemented within HD_Generate_Complete_Points");
	}
		
	ii = count2 / 2;
	do {
		float			s, t;
		float			_hoops_CGIAA;
		float			_hoops_SGIAA;
		Point alter	*_hoops_GGIAR = &pl[ii];
		Point alter	*p1 = &pl[count2-ii];
		Point alter	*p2 = &pl[count2+ii];
		Point alter	*_hoops_IAPH = &pl[count-ii];

		_hoops_RICH (theta, t, s);
		theta -= delta;

		_hoops_CGIAA = s * _hoops_GGHI->x;
		_hoops_SGIAA = t * _hoops_RGHI->x;
		_hoops_GGIAR->x = center->x + _hoops_CGIAA + _hoops_SGIAA;
		p1->x = center->x - _hoops_CGIAA + _hoops_SGIAA;
		p2->x = center->x - _hoops_CGIAA - _hoops_SGIAA;
		_hoops_IAPH->x = center->x + _hoops_CGIAA - _hoops_SGIAA;

		_hoops_CGIAA = s * _hoops_GGHI->y;
		_hoops_SGIAA = t * _hoops_RGHI->y;
		_hoops_GGIAR->y = center->y + _hoops_CGIAA + _hoops_SGIAA;
		p1->y = center->y - _hoops_CGIAA + _hoops_SGIAA;
		p2->y = center->y - _hoops_CGIAA - _hoops_SGIAA;
		_hoops_IAPH->y = center->y + _hoops_CGIAA - _hoops_SGIAA;

		_hoops_CGIAA = s * _hoops_GGHI->z;
		_hoops_SGIAA = t * _hoops_RGHI->z;
		_hoops_GGIAR->z = center->z + _hoops_CGIAA + _hoops_SGIAA;
		p1->z = center->z - _hoops_CGIAA + _hoops_SGIAA;
		p2->z = center->z - _hoops_CGIAA - _hoops_SGIAA;
		_hoops_IAPH->z = center->z + _hoops_CGIAA - _hoops_SGIAA;
	} while (ii-- != 0);

	return count + 1;
}


/* _hoops_GASA: _hoops_RRHCP _hoops_GPRCP _hoops_HRGR _hoops_IS _hoops_HS _hoops_RH 2_hoops_GRSP _hoops_HHAA _hoops_IIGR _hoops_RGR _hoops_API _hoops_SAHR _hoops_AASA _hoops_GGSR _hoops_IS _hoops_RH _hoops_ARRS, 
 * _hoops_GPHIS, _hoops_HIH _hoops_GHAP _hoops_RRP _hoops_IS _hoops_RGHH _hoops_RPHIS */
local void _hoops_IGIAA (
	Net_Rendition const &	nr,
	_hoops_GHHI const *		curve,
	int						_hoops_HGII,
	Point alter *			pl) {
	int						ii;
	Point const *			center;
	Vector const *			_hoops_GGHI;
	Vector const *			_hoops_RGHI;
	int						_hoops_GSAAA = _hoops_HGII / 2;
	float					theta = 90.0f;
	float					delta = 360.0f / (float)_hoops_HGII;
	Point					_hoops_GRIAA;
	Vector					_hoops_RRIAA;
	Vector					_hoops_ARIAA;

	if (_hoops_HGII <= 0) return;				/* _hoops_RSAIP */

	if (BIT (curve->_hoops_RRHH, _hoops_SHHI)) {
		_hoops_AIHI const *		c = (_hoops_AIHI const *)curve;

		_hoops_GRIAA.x = c->center.x;
		_hoops_GRIAA.y = c->center.y;
		_hoops_GRIAA.z = 0.0f;

		_hoops_RRIAA.x = c->radius;
		_hoops_RRIAA.y = 0.0f;
		_hoops_RRIAA.z = 0.0f;

		_hoops_ARIAA.x = 0.0f;
		_hoops_ARIAA.y = c->radius;
		_hoops_ARIAA.z = 0.0f;

		center = &_hoops_GRIAA;
		_hoops_GGHI = &_hoops_RRIAA;
		_hoops_RGHI = &_hoops_ARIAA;
	}
	else {
		center = &curve->center;
		_hoops_GGHI = &curve->_hoops_GGHI;
		_hoops_RGHI = &curve->_hoops_RGHI;
	}

	ii = _hoops_GSAAA / 2;
	do {
		float			s, t;
		float			_hoops_CGIAA;
		float			_hoops_SGIAA;
		Point alter	*	_hoops_GGIAR = &pl[ii];
		Point alter	*	p1 = &pl[_hoops_GSAAA-ii];
		Point alter	*	p2 = &pl[_hoops_GSAAA+ii];
		Point alter	*	_hoops_IAPH = &pl[_hoops_HGII-ii];

		_hoops_RICH (theta, t, s);
		theta -= delta;

		_hoops_CGIAA = s * _hoops_GGHI->x;
		_hoops_SGIAA = t * _hoops_RGHI->x;
		_hoops_GGIAR->x = center->x + _hoops_CGIAA + _hoops_SGIAA;
		p1->x = center->x - _hoops_CGIAA + _hoops_SGIAA;
		p2->x = center->x - _hoops_CGIAA - _hoops_SGIAA;
		_hoops_IAPH->x = center->x + _hoops_CGIAA - _hoops_SGIAA;

		_hoops_CGIAA = s * _hoops_GGHI->y;
		_hoops_SGIAA = t * _hoops_RGHI->y;
		_hoops_GGIAR->y = center->y + _hoops_CGIAA + _hoops_SGIAA;
		p1->y = center->y - _hoops_CGIAA + _hoops_SGIAA;
		p2->y = center->y - _hoops_CGIAA - _hoops_SGIAA;
		_hoops_IAPH->y = center->y + _hoops_CGIAA - _hoops_SGIAA;

		if (nr && nr->transform_rendition->_hoops_HGSC == _hoops_CIPHP)
			_hoops_GGIAR->z = p1->z = p2->z = _hoops_IAPH->z = center->z;
		else {
			_hoops_CGIAA = s * _hoops_GGHI->z;
			_hoops_SGIAA = t * _hoops_RGHI->z;
			_hoops_GGIAR->z = center->z + _hoops_CGIAA + _hoops_SGIAA;
			p1->z = center->z - _hoops_CGIAA + _hoops_SGIAA;
			p2->z = center->z - _hoops_CGIAA - _hoops_SGIAA;
			_hoops_IAPH->z = center->z + _hoops_CGIAA - _hoops_SGIAA;
		}
	} _hoops_RGGA (ii-- == 0);
}


/* _hoops_GASA: _hoops_IH _hoops_IRS _hoops_IHGP _hoops_PHIGR _hoops_GSGRS, _hoops_RHAC _hoops_GHCA _hoops_RIH _hoops_IRAP _hoops_IH "_hoops_SCII" */
GLOBAL_FUNCTION int HD_Generate_Elliptical_Points (
	Net_Rendition  const & 		nr,
	_hoops_GHHI const *			curve,
	int							_hoops_HGII,
	Point alter *				_hoops_IAIRA) {
	Point alter *				pl = _hoops_IAIRA;
	Point const *				center;
	Vector const *				_hoops_GGHI;
	Vector const *				_hoops_RGHI;
	Point						_hoops_GRIAA;
	Vector						_hoops_RRIAA;
	Vector						_hoops_ARIAA;
	bool						_hoops_AGSSR;

	if (curve->type == _hoops_RIIP &&
		BIT (curve->_hoops_RRHH, _hoops_RGGGA)) {
		_hoops_SSSSR const *	arc = (_hoops_SSSSR const *)curve;

		/* _hoops_SAHR _hoops_IRAA _hoops_RH _hoops_SRS _hoops_PPR _hoops_CGHI _hoops_RSSA */
		*pl++ = arc->points[0];
		*pl++ = arc->points[1];
		*pl++ = arc->points[2];

		return pl - _hoops_IAIRA;
	}

	if (BIT (curve->_hoops_RRHH, _hoops_SHHI)) {
		_hoops_AIHI const *	c = (_hoops_AIHI const *)curve;

		_hoops_GRIAA.x = c->center.x;
		_hoops_GRIAA.y = c->center.y;
		_hoops_GRIAA.z = 0.0f;

		_hoops_RRIAA.x = c->radius;
		_hoops_RRIAA.y = 0.0f;
		_hoops_RRIAA.z = 0.0f;

		_hoops_ARIAA.x = 0.0f;
		_hoops_ARIAA.y = c->radius;
		_hoops_ARIAA.z = 0.0f;

		center = &_hoops_GRIAA;
		_hoops_GGHI = &_hoops_RRIAA;
		_hoops_RGHI = &_hoops_ARIAA;
		_hoops_AGSSR = true;
	}
	else {
		center = &curve->center;
		_hoops_GGHI = &curve->_hoops_GGHI;
		_hoops_RGHI = &curve->_hoops_RGHI;
		_hoops_AGSSR = (nr && nr->transform_rendition->_hoops_HGSC == _hoops_CIPHP);
	}


	switch (curve->type) {
		case _hoops_SGCP:
		case _hoops_CGCP: {
			if (_hoops_HGII == 2) {
				pl[0].x = pl[1].x = center->x;
				pl[0].y = pl[1].y = center->y;
				pl[0].z = pl[1].z = center->z;
				return _hoops_HGII;
			}
			else {
				_hoops_IGIAA (nr, curve, _hoops_HGII, pl);
				return _hoops_HGII+1;
			}
		} _hoops_HHHI;

		case _hoops_RIIP:
		case _hoops_GIIP:
		case _hoops_GRCP:
		case _hoops_RRCP: {
			float				start, end, _hoops_GSAHR;

			if (BIT (curve->_hoops_RRHH, _hoops_SHHI)) {
				Circular_Arc_Lite const *	arc;

				arc = (Circular_Arc_Lite const *)curve;

				start = arc->arc_start;
				end = arc->_hoops_PHHI;
				_hoops_GSAHR = arc->radius;
			}
			else {
				Elliptical_Arc const *		arc = (Elliptical_Arc const *)curve;

				start = arc->arc_start;
				end = arc->_hoops_PHHI;
				if (end < start)
					end += 1.0f;

				if (curve->type != _hoops_GIIP)
					_hoops_GSAHR = ((Circular_Arc const *)curve)->radius;
				else
					_hoops_GSAHR = _hoops_SGIHR (arc->_hoops_GGHI.x * arc->_hoops_GGHI.x +
									arc->_hoops_GGHI.y * arc->_hoops_GGHI.y +
									arc->_hoops_GGHI.z * arc->_hoops_GGHI.z);
			}
			_hoops_GSAHR *= 1.0e-5f;

			if (_hoops_HGII == 2) {
				float			s, t;

				_hoops_RICH (360.0f * start, t, s);
				pl->x = center->x + s * _hoops_GGHI->x + t * _hoops_RGHI->x;
				pl->y = center->y + s * _hoops_GGHI->y + t * _hoops_RGHI->y;
				if (_hoops_AGSSR)
					pl->z = center->z;
				else
					pl->z = center->z + s * _hoops_GGHI->z + t * _hoops_RGHI->z;

				++pl;

				_hoops_RICH (360.0f * end, t, s);
				pl->x = center->x + s * _hoops_GGHI->x + t * _hoops_RGHI->x;
				pl->y = center->y + s * _hoops_GGHI->y + t * _hoops_RGHI->y;
				if (_hoops_AGSSR)
					pl->z = center->z;
				else
					pl->z = center->z + s * _hoops_GGHI->z +
										t * _hoops_RGHI->z;

				return _hoops_HGII;
			}
			else if (start == 0.0f && end == 1.0f) {
				_hoops_IGIAA (nr, curve, _hoops_HGII, pl);
				return _hoops_HGII+1;
			}
			else {
				int				ii;
				float			theta;
				float			delta;
				Point *			first;

				if (curve->type == _hoops_RRCP) {
					pl->x = center->x;
					pl->y = center->y;
					pl->z = center->z;
					++pl;
				}

				theta = 360.0f * start;
				ii = (int)((float)_hoops_HGII * Abs (end - start) + 0.5f);
				if (ii > 0)
					delta = 360.0f * Abs (end - start) / (float)ii;
				else
					delta = 0.0f;
				if (end < start)
					delta = -delta;

				first = pl;		/* _hoops_SRS _hoops_PPSR _hoops_GGR _hoops_ARGR _hoops_AGIS */
				if (curve->type != _hoops_GIIP &&
					!BIT (curve->_hoops_RRHH, _hoops_SHHI)) {
					Circular_Arc const *	_hoops_PRIAA = (Circular_Arc const *)curve;

					*pl++ = _hoops_PRIAA->start;

					--ii; /* _hoops_ARR _hoops_IH _hoops_RGR _hoops_PPSR */
					--ii; /* _hoops_PPR _hoops_ARR _hoops_IH _hoops_RH _hoops_RSGR _hoops_PPSR - _hoops_SPHR */
					theta += delta;
				}

				_hoops_RGGA (ii-- < 0) {
					float			s, t;

					_hoops_RICH (theta, t, s);
					pl->x = center->x + s * _hoops_GGHI->x + t * _hoops_RGHI->x;
					pl->y = center->y + s * _hoops_GGHI->y + t * _hoops_RGHI->y;
					if (_hoops_AGSSR)
						pl->z = center->z;
					else
						pl->z = center->z + s * _hoops_GGHI->z + t * _hoops_RGHI->z;
					++pl;
					theta += delta;
				}

				if (curve->type != _hoops_GIIP &&
					!BIT (curve->_hoops_RRHH, _hoops_SHHI)) {
					Circular_Arc const *	_hoops_PRIAA = (Circular_Arc const *)curve;

					*pl++ = _hoops_PRIAA->end;
				}
				else {
					float			s, t;

					_hoops_RICH (360.0f*end , t, s);
					pl->x = center->x + s * _hoops_GGHI->x + t * _hoops_RGHI->x;
					pl->y = center->y + s * _hoops_GGHI->y + t * _hoops_RGHI->y;
					if (nr && nr->transform_rendition->_hoops_HGSC == _hoops_CIPHP)
						pl->z = center->z;
					else
						pl->z = center->z + s * _hoops_GGHI->z + t * _hoops_RGHI->z;
					++pl;
				}
				if (Abs (pl[-1].x - pl[-2].x) < _hoops_GSAHR &&
						Abs (pl[-1].y - pl[-2].y) < _hoops_GSAHR &&
							Abs (pl[-1].z - pl[-2].z) < _hoops_GSAHR)
					--pl;

				if (curve->type == _hoops_GRCP) {
					pl->x = first->x;
					pl->y = first->y;
					pl->z = first->z;
					++pl;
				}
				else if (curve->type == _hoops_RRCP) {
					pl->x = center->x;
					pl->y = center->y;
					pl->z = center->z;
					++pl;
				}

				return (pl - _hoops_IAIRA);
			}
		}	_hoops_HHHI;

		default:		/* _hoops_CGH _hoops_IIP _hoops_HGCR _hoops_ARI */
			break;
	}

	return 0; /* _hoops_ASAI _hoops_HAHIS */
}


local void _hoops_APHIS (
	Net_Rendition const &		nr,
	_hoops_GHHI const *			curve) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	int							_hoops_HGII;
	Point alter *				pl;

	_hoops_HGII = HD_Determine_Elliptical_Res (nr, curve);
	if (_hoops_HGII <= 0) return;				/* _hoops_RSAIP */

	switch (curve->type) {
		case _hoops_SGCP:
		case _hoops_CGCP: {
			Polygon alter *		polygon;

			POOL_ZALLOC (polygon, Polygon, nr->_hoops_SRA->memory_pool);

			polygon->_hoops_HIHI = 1;
			polygon->type = _hoops_RCIP;
			polygon->_hoops_RRHH = (curve->_hoops_RRHH & _hoops_RSPCR) |
								 _hoops_ARHH|_hoops_IASGP;
			polygon->owner = null;
			polygon->_hoops_CPGPR = curve->_hoops_CPGPR;
			polygon->_hoops_SPGPR = curve->_hoops_SPGPR;
			polygon->_hoops_IPPGR = null;

			POOL_ALLOC_ARRAY_CACHED (pl, _hoops_HGII + 1, Point, nr->_hoops_SRA->memory_pool);

			polygon->points = pl;
			polygon->allocated = _hoops_HGII + 1;
			polygon->count = HD_Generate_Elliptical_Points (nr, curve, _hoops_HGII, pl);
			if (polygon->count > 2)
				--polygon->count;	/* _hoops_HASIR _hoops_RH _hoops_IHH _hoops_SR _hoops_ACPA _hoops_AGHP _hoops_RRAI */

			if (BIT (curve->_hoops_RRHH, _hoops_SHHI)) {
				polygon->plane.a = 0.0f;
				polygon->plane.b = 0.0f;
				polygon->plane.c = -1.0f;
				polygon->plane.d = 0.0f;
				if (BIT (_hoops_IHCR->heuristics, _hoops_GPSA))
					polygon->plane.c = 1.0f;
			}
			else
				polygon->plane = ((Ellipse const *)curve)->plane;

			_hoops_RCAIP (nr, polygon);

			_hoops_HPRH (polygon);
		}	break;

		case _hoops_GRCP:
		case _hoops_RRCP: {
			Polygon alter *		polygon;
			int					_hoops_SGII;
			float				start, end;
			Net_Rendition		_hoops_PPHIS = nr;

			if (BIT (curve->_hoops_RRHH, _hoops_SHHI)) {
				Circular_Arc_Lite const *	arc = (Circular_Arc_Lite const *)curve;

				start = arc->arc_start;
				end = arc->_hoops_PHHI;
			}
			else {
				Elliptical_Arc const *		arc = (Elliptical_Arc const *)curve;

				start = arc->arc_start;
				end = arc->_hoops_PHHI;
				if (end < start)
					end += 1.0f;
			}


			POOL_ZALLOC (polygon, Polygon, nr->_hoops_SRA->memory_pool);

			polygon->_hoops_HIHI = 1;
			polygon->type = _hoops_RCIP;
			polygon->_hoops_RRHH = (curve->_hoops_RRHH & _hoops_RSPCR) |
								 _hoops_ARHH|_hoops_IASGP;
			polygon->owner = null;
			polygon->_hoops_CPGPR = curve->_hoops_CPGPR;
			polygon->_hoops_SPGPR = curve->_hoops_SPGPR;
			polygon->_hoops_IPPGR = null;

			_hoops_SGII = (int)((float)_hoops_HGII * Abs(end - start) + 0.5f);

			POOL_ALLOC_ARRAY_CACHED (pl, _hoops_SGII + 4, Point, nr->_hoops_SRA->memory_pool);

			polygon->points = pl;
			polygon->allocated = _hoops_SGII + 4;
			polygon->count = HD_Generate_Elliptical_Points (nr, curve, _hoops_HGII, pl);

			if (BIT (curve->_hoops_RRHH, _hoops_SHHI)) {
				polygon->plane.a = 0.0f;
				polygon->plane.b = 0.0f;
				polygon->plane.c = -1.0f;
				polygon->plane.d = 0.0f;
				if (BIT (_hoops_IHCR->heuristics, _hoops_GPSA))
					polygon->plane.c = 1.0f;
			}
			else
				polygon->plane = ((Ellipse const *)curve)->plane;

			if (BIT (nr->_hoops_RGP, T_FACES)) {
				
				if (Abs(end - start) > 0.5f) {
					if (!BIT (nr->transform_rendition->heuristics, _hoops_CGCS))
						_hoops_PPHIS.Modify()->transform_rendition.Modify()->heuristics |= _hoops_CGCS;
				}
				else {
					if (BIT (nr->transform_rendition->heuristics, _hoops_CGCS))
						_hoops_PPHIS.Modify()->transform_rendition.Modify()->heuristics &= ~_hoops_CGCS;
				}
			}

			_hoops_RCAIP (_hoops_PPHIS, polygon);

			_hoops_HPRH (polygon);

		}	break;

		case _hoops_RIIP:
		case _hoops_GIIP: {
			Polyline alter *	polyline;
			int					_hoops_SGII;
			float				start, end;

			if (BIT (curve->_hoops_RRHH, _hoops_SHHI)) {
				Circular_Arc_Lite const *	arc = (Circular_Arc_Lite const *)curve;

				start = arc->arc_start;
				end = arc->_hoops_PHHI;
			}
			else {
				Elliptical_Arc const *		arc = (Elliptical_Arc const *)curve;

				start = arc->arc_start;
				end = arc->_hoops_PHHI;
				if (end < start)
					end += 1.0f;
			}

			POOL_ZALLOC (polyline, Polyline, nr->_hoops_SRA->memory_pool);

			polyline->_hoops_HIHI = 1;
			polyline->type = _hoops_IIIP;
			polyline->_hoops_RRHH = (curve->_hoops_RRHH & _hoops_RSPCR);
			polyline->owner = null;
			polyline->_hoops_CPGPR = curve->_hoops_CPGPR;
			polyline->_hoops_SPGPR = curve->_hoops_SPGPR;
			polyline->_hoops_IPPGR = null;

			_hoops_SGII = (int)((float)_hoops_HGII * Abs (end - start) + 0.5f);

			POOL_ALLOC_ARRAY_CACHED (pl, _hoops_SGII + 3, Point, nr->_hoops_SRA->memory_pool);

			polyline->points = pl;
			polyline->allocated = _hoops_SGII + 3;
			polyline->count = HD_Generate_Elliptical_Points (nr, curve, _hoops_HGII, pl);

			_hoops_CCAIP (nr, polyline);

			_hoops_HPRH (polyline);
		}	break;
	}
}


local void _hoops_HPHIS (
	Net_Rendition const &		in_nr,
	_hoops_GHHI const *			curve) {
	Net_Rendition				nr = in_nr;
	Line_Rendition const &		_hoops_HC = nr->_hoops_AHP;
	Line_Rendition const &		_hoops_GHP = nr->_hoops_RHP;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	int							_hoops_HGII;
	bool						_hoops_ASHCA;

	if ((curve->type == _hoops_SGCP || curve->type == _hoops_CGCP)) {
		if (!ALLBITS (_hoops_GHP->flags, _hoops_AGRIP) &&
			ANYBIT (_hoops_GHP->line_style->flags, _hoops_RHISA|LSF_JOIN)) {
			nr.Modify()->_hoops_RHP.Modify()->flags |= _hoops_AGRIP;
		}
		_hoops_ASHCA = ANYBIT (_hoops_GHP->line_style->flags, LSF_COMPLEX_ANYBITS);
	}
	else {
		if (!BIT (_hoops_HC->flags, _hoops_HGRIP) &&
			BIT (_hoops_HC->line_style->flags, LSF_MIDDLE_GLYPH|LSF_JOIN)) {
			nr.Modify()->_hoops_AHP.Modify()->flags |= _hoops_HGRIP;
		}
		_hoops_ASHCA = BIT(nr->_hoops_AHP->flags, _hoops_SRPI) || ANYBIT (_hoops_HC->line_style->flags, LSF_COMPLEX_ANYBITS);
	}

	if (curve->type == _hoops_RIIP &&
		BIT (curve->_hoops_RRHH, _hoops_RGGGA)) {
		_hoops_SSSSR const *	arc = (_hoops_SSSSR const *)curve;
		Polyline alter	*			polyline;
		Point alter *				pl;

		ZALLOC (polyline, Polyline);

		polyline->_hoops_HIHI = 1;
		polyline->type = _hoops_IIIP;
		polyline->_hoops_RRHH = (arc->_hoops_RRHH & _hoops_RSPCR);
		polyline->owner = null;
		polyline->_hoops_CPGPR = arc->_hoops_CPGPR;
		polyline->_hoops_SPGPR = arc->_hoops_SPGPR;
		polyline->_hoops_IPPGR = null;

		ALLOC_ARRAY (pl, 3, Point);

		polyline->points = pl;
		polyline->allocated = 3;
		polyline->count = 3;
		_hoops_AIGA (arc->points, 3, Point, pl);

		_hoops_CCAIP (nr, polyline);

		_hoops_HPRH (polyline);

		goto _hoops_PRSPR;
	}

	if (_hoops_ASHCA) {
		/* _hoops_PAH'_hoops_RA _hoops_IIS _hoops_SCH _hoops_IISPR _hoops_IS "_hoops_GSIA" _hoops_CR _hoops_AGR _hoops_HGIRR'_hoops_RA _hoops_SHH _hoops_IPHIS */
		_hoops_APHIS (nr, curve);
	}
	else if (BIT (nr->current, _hoops_CSGGR) && !BIT(_hoops_IHCR->flags, _hoops_PASP)) {
		/* _hoops_HHSA _hoops_SCH _hoops_RHIR _hoops_CPHIS */
		/* _hoops_HGAPR _hoops_ISCC _hoops_RAIGR _hoops_SPHIS _hoops_GGHIP _hoops_GHHIS _hoops_RHHIS _hoops_GGHIP _hoops_AHHIS _hoops_PHHIS _hoops_HHHIS
		 * _hoops_RCSPR _hoops_IHHIS-_hoops_CHHIS _hoops_SCPGH _hoops_PGSGS.
		 */

		_hoops_APHIS (nr, curve);
	}
	else switch (_hoops_IHCR->_hoops_HGSC) {
		case _hoops_SIPHP:
		case _hoops_CIPHP: {
			DC_Point		_hoops_SGISC,
							_hoops_GRHIS;
			float			_hoops_HCIS;

			if (!ANYBIT (_hoops_IHCR->flags, _hoops_GRHH|_hoops_CSP) &&
				!BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HPH) &&
				nr->_hoops_RSGC->action.draw_3d_polygon  == nullroutine &&
				nr->_hoops_RSGC->action.draw_3d_polyline == nullroutine &&
				nr->_hoops_RSGC->action.draw_dc_face	   == nullroutine &&
				nr->_hoops_RSGC->action.draw_dc_polyline == nullroutine) {

				switch (curve->type) {
				  case _hoops_SGCP:
				  case _hoops_CGCP:
					if (_hoops_SGHIS (nr, curve, &_hoops_SGISC, &_hoops_GRHIS, &_hoops_HGII, &_hoops_HCIS, &_hoops_HCIS)) {
						if (_hoops_HGII <= 0) { /* _hoops_RPAPR */ }
						else if (_hoops_HGII == 1)
							_hoops_HAPIP (nr, &_hoops_SGISC);
						else
							_hoops_IAHIS (nr, &_hoops_SGISC, &_hoops_GRHIS);
					}
					else
						_hoops_APHIS (nr, curve);
					break;

				  case _hoops_GIIP:
				  case _hoops_RIIP: {
					float	start, end;

					if (BIT (curve->_hoops_RRHH, _hoops_SHHI)) {
						Circular_Arc_Lite const *	arc = (Circular_Arc_Lite const *)curve;

						start = arc->arc_start;
						end = arc->_hoops_PHHI;
					}
					else {
						Elliptical_Arc const *		arc = (Elliptical_Arc const *)curve;

						start = arc->arc_start;
						end = arc->_hoops_PHHI;
					}

					  if (_hoops_SGHIS (nr, curve, &_hoops_SGISC, &_hoops_GRHIS, &_hoops_HGII, &start, &end) &&
							end > start) {
						  if (_hoops_HGII <= 0) { /* _hoops_RPAPR */ }
						  else if (_hoops_HGII == 1)
							  _hoops_HAPIP (nr, &_hoops_SGISC);
						  else if (start == 0.0f && end == 1.0f)
							  _hoops_PAPIP (nr, &_hoops_SGISC, &_hoops_GRHIS);
						  else
							  _hoops_PSIGH (nr, &_hoops_SGISC, &_hoops_GRHIS, start, end);
					  }
					  else
						  _hoops_APHIS (nr, curve);
				  }	  break;

				  default:
					_hoops_APHIS (nr, curve);
					break;
				}
			}
			else
				_hoops_APHIS (nr, curve);
		}	break;

		case _hoops_ACPHP:
		case _hoops_PCPHP:
		case _hoops_RCPHP:
		case _hoops_GCPHP: {
				_hoops_APHIS (nr, curve);
		}	break;
	}

_hoops_PRSPR:;
}


GLOBAL_FUNCTION void HD_Std_3D_Elliptical_Arc (
	Net_Rendition const &		nr,
	Elliptical_Arc const *		arc) {

	_hoops_HPHIS (nr, (_hoops_GHHI const *)arc);
}


GLOBAL_FUNCTION void HD_Std_3D_Ellipse (
	Net_Rendition const &		nr,
	Ellipse const *				ellipse) {

	_hoops_HPHIS (nr, (_hoops_GHHI const *)ellipse);
}

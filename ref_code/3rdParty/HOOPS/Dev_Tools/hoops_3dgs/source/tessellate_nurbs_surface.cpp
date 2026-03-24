/*
 * Copyright (c) 2001 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.97 2010-12-06 22:05:40 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hd_proto.h"
#include "phedron.h"
#include "hpserror.h"
#include "adt.h"

#ifndef _hoops_GSPIR


local const float _hoops_ASRHH[] = {
		0,	1,	2,	3,	4,	5,	6,	7,	8,	9,	10, 11, 12, 13, 14, 15,
		16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
local const float _hoops_PSRHH[] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

#define _hoops_CACIR (1e-5f)


#define _hoops_RIRGGR(u,v) ((((POINTER_SIZED_INT)((u) * 65535)<<16)|(POINTER_SIZED_INT)((v) * 65535)))

GLOBAL_FUNCTION void HI_Get_UV_Region_Triangle(
		UV_Region_Set *set,
		UV_Region *region,
		UV_Edge alter **a,
		UV_Edge alter **b,
		UV_Edge alter **c);


#define _hoops_AIRGGR 0x1
#define _hoops_PIRGGR 0x2
typedef struct {
	int flags;
	Point point;
	Vector normal;
} _hoops_HIRGGR;

typedef VHash<POINTER_SIZED_INT, _hoops_HIRGGR *> _hoops_IIRGGR;

local _hoops_HIRGGR *_hoops_CIRGGR(void) {
	_hoops_HIRGGR *info;
	ALLOC(info, _hoops_HIRGGR);
	info->flags = 0;
	return info;
}
local void _hoops_SIRGGR(_hoops_HIRGGR *info) {
	FREE(info, _hoops_HIRGGR);
}
/* _hoops_HSPR _hoops_API _hoops_HCPH _hoops_RHIR _hoops_HPRGR _hoops_CCPSA -- _hoops_HICP _hoops_SACAR _hoops_IS _hoops_HS
 * _hoops_IRS _hoops_CSPP _hoops_PIS _hoops_RH _hoops_RGHP _hoops_PAPIA _hoops_IH _hoops_GCRGGR */
local void _hoops_RCRGGR(
	_hoops_HIRGGR *info,
	POINTER_SIZED_INT _hoops_HCIS,
	void const * const _hoops_AGPAR) {
	_hoops_SIRGGR(info);
	UNREFERENCED(_hoops_HCIS);
	UNREFERENCED(_hoops_AGPAR);
}

typedef struct _hoops_ACRGGR {
	int index;
	float t;
	float priority;
	struct _hoops_ACRGGR *next;
} _hoops_GPHPA;

typedef struct _hoops_PCRGGR {
	UV_Point *uvpoints;
	int allocated;
	int used;
} _hoops_HCRGGR;


/* _hoops_AIHH _hoops_IGPHH 2.1 _hoops_GPP _hoops_HSHIA 68 _hoops_IIGR "_hoops_IPCP _hoops_IRCPH _hoops_CGPHH", _hoops_SGPHH&_hoops_GRPHH, 2_hoops_GRSP _hoops_RRPHH */
local int _hoops_ARPHH (int n, int p, float _hoops_ISAHH, const float *_hoops_PRPHH) {
	int low, _hoops_SPGIR, high;

	if (_hoops_ISAHH == _hoops_PRPHH[n+1])
		return n-1;
	low = p;
	high = n+1;
	_hoops_SPGIR = (low + high) / 2;
	while (_hoops_ISAHH < _hoops_PRPHH[_hoops_SPGIR] || _hoops_ISAHH >= _hoops_PRPHH[_hoops_SPGIR+1])
	{
		if (_hoops_ISAHH < _hoops_PRPHH[_hoops_SPGIR])
			high = _hoops_SPGIR;
		else
			low = _hoops_SPGIR;
		_hoops_SPGIR = (low + high) / 2;
	}
	return _hoops_SPGIR;
} /* _hoops_RSGR _hoops_API _hoops_ICRGGR */


/* _hoops_AIHH _hoops_IGPHH 2.2 _hoops_GPP _hoops_HSHIA 70 _hoops_IIGR "_hoops_IPCP _hoops_IRCPH _hoops_CGPHH", _hoops_SGPHH&_hoops_GRPHH, 2_hoops_GRSP _hoops_RRPHH */
local void _hoops_IRPHH (int i, float _hoops_ISAHH, int p, const float *_hoops_PRPHH, float *_hoops_PAGR) {
	int	 r, j;
	float _hoops_HPRS, temp;
	/* _hoops_CRPHH 16 _hoops_GGR _hoops_HSPR _hoops_III _hoops_IGIPR _hoops_SAIPR _hoops_IIGR _hoops_CPSH 16 _hoops_GPP _hoops_GRRC */
	float left[16], right[16]; 

	_hoops_PAGR[0] = 1;
	for (j = 1; j <= p; j++)
	{
		left[j] = _hoops_ISAHH-_hoops_PRPHH[i+1-j];
		right[j] = _hoops_PRPHH[i+j] - _hoops_ISAHH;
		_hoops_HPRS = 0;
		for (r = 0; r < j; r++)
		{
			temp = _hoops_PAGR[r] /	 (right[r+1] + left[j-r]);
			_hoops_PAGR[r] = _hoops_HPRS + right[r+1] * temp;
			_hoops_HPRS = left[j-r] * temp;
		}
		_hoops_PAGR[j] = _hoops_HPRS;
	}
} /* _hoops_RSGR _hoops_API _hoops_SRPHH */



/* _hoops_AIHH _hoops_IGPHH 4.3 _hoops_GPP _hoops_HSHIA 134 _hoops_IIGR "_hoops_IPCP _hoops_IRCPH _hoops_CGPHH", _hoops_SGPHH&_hoops_GRPHH, 2_hoops_GRSP _hoops_RRPHH  */
local void _hoops_CCRGGR (
	_hoops_APPGR const *	_hoops_SSHIH, 
	float					_hoops_SCRGGR, 
	float					_hoops_GSRGGR, 
	Point *					_hoops_PAGR, 
	_hoops_IIRGGR *	_hoops_CSC) 
{
	Point temp[16]; /* _hoops_IGIPR _hoops_CIAS _hoops_ISSGR _hoops_CPSH _hoops_IIGR 16 */
	float *_hoops_RSRGGR, _hoops_ASRGGR[20], *_hoops_PSRGGR, _hoops_HSRGGR[20];
	Point const *point;
	int _hoops_ISRGGR, _hoops_CSRGGR;
	float weight, _hoops_SSRGGR;
	int j, k;
	float _hoops_ISAHH, _hoops_APCGH;
	float start_u = _hoops_SSHIH->u_knots[_hoops_SSHIH->u_degree];
	float end_u = _hoops_SSHIH->u_knots[_hoops_SSHIH->n_u_vertices];
	float _hoops_GRSIH = _hoops_SSHIH->v_knots[_hoops_SSHIH->v_degree];
	float _hoops_RRSIH = _hoops_SSHIH->v_knots[_hoops_SSHIH->n_v_vertices];
	float _hoops_GGAGGR = end_u - start_u;
	float _hoops_RGAGGR = _hoops_RRSIH - _hoops_GRSIH;
	float _hoops_AGAGGR = _hoops_GGAGGR * _hoops_CACIR;
	float _hoops_PGAGGR = _hoops_RGAGGR * _hoops_CACIR;
	_hoops_HIRGGR *_hoops_HGAGGR = null;
	POINTER_SIZED_INT _hoops_IGAGGR = _hoops_RIRGGR(_hoops_SCRGGR, _hoops_GSRGGR);

	if (_hoops_CSC != null) {
		if (_hoops_CSC->LookupItem(_hoops_IGAGGR, &_hoops_HGAGGR) == VHASH_STATUS_SUCCESS) {

			if (_hoops_HGAGGR->flags & _hoops_AIRGGR) {
				_hoops_RSAI (&_hoops_HGAGGR->point, Point, _hoops_PAGR);
				return;
			}
		}			
		else {
			_hoops_HGAGGR = _hoops_CIRGGR();
			_hoops_CSC->InsertItem(_hoops_IGAGGR, _hoops_HGAGGR);
		}
	}

	_hoops_ISAHH = (_hoops_SCRGGR * _hoops_GGAGGR) + start_u;
	_hoops_APCGH = (_hoops_GSRGGR * _hoops_RGAGGR) + _hoops_GRSIH;
	if (_hoops_ISAHH > end_u - _hoops_AGAGGR) _hoops_ISAHH = end_u - _hoops_AGAGGR;
	if (_hoops_APCGH > _hoops_RRSIH - _hoops_PGAGGR) _hoops_APCGH = _hoops_RRSIH - _hoops_PGAGGR;
	if (_hoops_ISAHH < start_u + _hoops_AGAGGR) _hoops_ISAHH = start_u + _hoops_AGAGGR;
	if (_hoops_APCGH < _hoops_GRSIH + _hoops_PGAGGR) _hoops_APCGH = _hoops_GRSIH + _hoops_PGAGGR;

	if (_hoops_SSHIH->n_u_vertices > 20 || _hoops_SSHIH->n_v_vertices > 20) {
		ALLOC_ARRAY_CACHED (_hoops_RSRGGR, _hoops_SSHIH->n_u_vertices, float); 
		ALLOC_ARRAY_CACHED (_hoops_PSRGGR, _hoops_SSHIH->n_v_vertices, float); 
	}
	else {
		_hoops_RSRGGR = _hoops_ASRGGR;
		_hoops_PSRGGR = _hoops_HSRGGR;
	}

	_hoops_ISRGGR = _hoops_ARPHH (_hoops_SSHIH->n_u_vertices, _hoops_SSHIH->u_degree, _hoops_ISAHH, _hoops_SSHIH->u_knots);
	_hoops_IRPHH (_hoops_ISRGGR, _hoops_ISAHH, _hoops_SSHIH->u_degree, _hoops_SSHIH->u_knots, _hoops_RSRGGR);
	_hoops_CSRGGR = _hoops_ARPHH (_hoops_SSHIH->n_v_vertices, _hoops_SSHIH->v_degree, _hoops_APCGH, _hoops_SSHIH->v_knots);
	_hoops_IRPHH (_hoops_CSRGGR, _hoops_APCGH, _hoops_SSHIH->v_degree, _hoops_SSHIH->v_knots, _hoops_PSRGGR);

	_hoops_ISRGGR -= _hoops_SSHIH->u_degree;
	_hoops_CSRGGR -= _hoops_SSHIH->v_degree;
	if (_hoops_SSHIH->weights == null) {
		for (j = 0; j <=  _hoops_SSHIH->v_degree; j++) {
			temp[j].x = temp[j].y = temp[j].z = 0;
			for (k = 0; k <= _hoops_SSHIH->u_degree; k++) {
				point = &_hoops_SSHIH->control_points[((k+_hoops_ISRGGR)*_hoops_SSHIH->n_v_vertices) + j+_hoops_CSRGGR];
				temp[j].x += _hoops_RSRGGR[k] * point->x;
				temp[j].y += _hoops_RSRGGR[k] * point->y;
				temp[j].z += _hoops_RSRGGR[k] * point->z;
			}
		}
		_hoops_PAGR->x = _hoops_PAGR->y = _hoops_PAGR->z = 0;
		for (j = 0; j <= _hoops_SSHIH->v_degree; j++) {
			_hoops_PAGR->x += _hoops_PSRGGR[j] * temp[j].x;
			_hoops_PAGR->y += _hoops_PSRGGR[j] * temp[j].y;
			_hoops_PAGR->z += _hoops_PSRGGR[j] * temp[j].z;
		}
	}
	else {
		_hoops_SSRGGR = 0;
		for (j = 0; j <=  _hoops_SSHIH->v_degree; j++) {
			temp[j].x = temp[j].y = temp[j].z = 0;
			for (k = 0; k <= _hoops_SSHIH->u_degree; k++) {
				point = &_hoops_SSHIH->control_points[((k+_hoops_ISRGGR)*_hoops_SSHIH->n_v_vertices) + j+_hoops_CSRGGR];
				weight = _hoops_SSHIH->weights[((k+_hoops_ISRGGR)*_hoops_SSHIH->n_v_vertices) + j+_hoops_CSRGGR];
				temp[j].x += _hoops_RSRGGR[k] * point->x * weight;
				temp[j].y += _hoops_RSRGGR[k] * point->y * weight;
				temp[j].z += _hoops_RSRGGR[k] * point->z * weight;
				_hoops_SSRGGR += weight * _hoops_RSRGGR[k] * _hoops_PSRGGR[j]; 
			}
		}
		_hoops_PAGR->x = _hoops_PAGR->y = _hoops_PAGR->z = 0;
		for (j = 0; j <= _hoops_SSHIH->v_degree; j++) {
			_hoops_PAGR->x += _hoops_PSRGGR[j] * temp[j].x;
			_hoops_PAGR->y += _hoops_PSRGGR[j] * temp[j].y;
			_hoops_PAGR->z += _hoops_PSRGGR[j] * temp[j].z;
		}
		_hoops_PAGR->x /= _hoops_SSRGGR;
		_hoops_PAGR->y /= _hoops_SSRGGR;
		_hoops_PAGR->z /= _hoops_SSRGGR;
	}
	if (_hoops_SSHIH->n_u_vertices > 20 || _hoops_SSHIH->n_v_vertices > 20) {
		FREE_ARRAY (_hoops_RSRGGR, _hoops_SSHIH->n_u_vertices, float); 
		FREE_ARRAY (_hoops_PSRGGR, _hoops_SSHIH->n_v_vertices, float);
	}
	if (_hoops_HGAGGR != null) {
		_hoops_HGAGGR->flags |= _hoops_AIRGGR;
		_hoops_RSAI (_hoops_PAGR, Point, &_hoops_HGAGGR->point);
	}
	
} /* _hoops_RSGR _hoops_API _hoops_CGAGGR	*/


/* _hoops_RAIGR _hoops_SGAGGR _hoops_PSISC _hoops_IS _hoops_CPSSR _hoops_GRAGGR _hoops_IIGR _hoops_RH _hoops_RCA _hoops_HHGS _hoops_CCA _hoops_RRAGGR _hoops_PPPHH _hoops_ISSGR.
 * _hoops_PS _hoops_CHH _hoops_CPSA _hoops_PII _hoops_IS _hoops_HS _hoops_IRS _hoops_CGCHI _hoops_IIHA _hoops_GPP _hoops_ARAGGR 3.7, 3.8, _hoops_PPR 4.4,
 * _hoops_CPGP _hoops_HHH _hoops_HSSSR _hoops_HHGS _hoops_CCA _hoops_RGR _hoops_CCHRA _hoops_CHR _hoops_IS _hoops_SHH _hoops_SSSHR. */
local void _hoops_PRAGGR (
	_hoops_APPGR const *	_hoops_SSHIH, 
	float					_hoops_ISAHH, 
	float					_hoops_APCGH, 
	Vector *				_hoops_PAGR,
	_hoops_IIRGGR *	_hoops_CSC) 
{
	float offset = 0.01f;
	float _hoops_ACCRR, _hoops_PCCRR, _hoops_ISPI, _hoops_CSPI;
	Point _hoops_HRAGGR, _hoops_IRAGGR, _hoops_CRAGGR, _hoops_SRAGGR;
	Vector _hoops_GAAGGR, _hoops_RAAGGR;
	_hoops_HIRGGR *_hoops_HGAGGR = null;
	POINTER_SIZED_INT _hoops_IGAGGR = _hoops_RIRGGR(_hoops_ISAHH, _hoops_APCGH);

	if (_hoops_CSC != null) {
		if (_hoops_CSC->LookupItem (_hoops_IGAGGR, &_hoops_HGAGGR) == VHASH_STATUS_SUCCESS) {
			if (_hoops_HGAGGR->flags & _hoops_PIRGGR) {
				_hoops_RSAI (&_hoops_HGAGGR->normal, Vector, _hoops_PAGR);
				return;
			}
		}			
		else {
			_hoops_HGAGGR = _hoops_CIRGGR();
			_hoops_CSC->InsertItem (_hoops_IGAGGR, _hoops_HGAGGR);
		}
	}

	_hoops_ACCRR = _hoops_ISAHH - offset;
	_hoops_PCCRR = _hoops_ISAHH + offset;
	_hoops_ISPI = _hoops_APCGH - offset;
	_hoops_CSPI = _hoops_APCGH + offset;
	_hoops_CCRGGR (_hoops_SSHIH, _hoops_ACCRR, _hoops_APCGH, &_hoops_HRAGGR, null);
	_hoops_CCRGGR (_hoops_SSHIH, _hoops_PCCRR, _hoops_APCGH, &_hoops_IRAGGR, null);
	_hoops_CCRGGR (_hoops_SSHIH, _hoops_ISAHH, _hoops_ISPI, &_hoops_CRAGGR, null);
	_hoops_CCRGGR (_hoops_SSHIH, _hoops_ISAHH, _hoops_CSPI, &_hoops_SRAGGR, null);
	_hoops_GAAGGR.x = _hoops_IRAGGR.x - _hoops_HRAGGR.x;
	_hoops_GAAGGR.y = _hoops_IRAGGR.y - _hoops_HRAGGR.y;
	_hoops_GAAGGR.z = _hoops_IRAGGR.z - _hoops_HRAGGR.z;
	_hoops_RAAGGR.x = _hoops_SRAGGR.x - _hoops_CRAGGR.x;
	_hoops_RAAGGR.y = _hoops_SRAGGR.y - _hoops_CRAGGR.y;
	_hoops_RAAGGR.z = _hoops_SRAGGR.z - _hoops_CRAGGR.z;
	HI_Cross_Product (&_hoops_RAAGGR, &_hoops_GAAGGR, _hoops_PAGR);
	HI_Normalize (_hoops_PAGR);

	if (_hoops_HGAGGR != null) {
		_hoops_HGAGGR->flags |= _hoops_PIRGGR;
		_hoops_RSAI (_hoops_PAGR, Vector,  &_hoops_HGAGGR->normal);
	}
}



local void _hoops_AAAGGR(_hoops_PIRGR *_hoops_CPHPA, UV_Trim_Curve const *_hoops_PSSSI )
{
	int i;

	_hoops_CPHPA->degree = _hoops_PSSSI->degree;
	_hoops_CPHPA->control_point_count = _hoops_PSSSI->control_point_count;
	ALLOC_ARRAY (_hoops_CPHPA->control_points, _hoops_CPHPA->control_point_count, Point);
	for (i = 0; i < _hoops_PSSSI->control_point_count; i++) {
		_hoops_CPHPA->control_points[i].x = _hoops_PSSSI->control_points[i].u;
		_hoops_CPHPA->control_points[i].y = _hoops_PSSSI->control_points[i].v;
		_hoops_CPHPA->control_points[i].z = 0;
	}
	_hoops_CPHPA->weights = _hoops_PSSSI->weights;
	_hoops_CPHPA->knots = _hoops_PSSSI->knots;
	_hoops_CPHPA->start_u = 0;
	_hoops_CPHPA->end_u = 1;
	if (_hoops_CPHPA->knots == null) {
		int _hoops_PAAGGR = _hoops_PSSSI->control_point_count + _hoops_PSSSI->degree + 1;
		if (_hoops_PAAGGR > _hoops_GGAPR (_hoops_ASRHH)) {
			ALLOC_ARRAY (_hoops_CPHPA->knots, _hoops_PAAGGR, float);
			for (i = 0; i < _hoops_PAAGGR; i++)
				_hoops_CPHPA->knots[i] = (float)i;
		}
		else
			_hoops_CPHPA->knots = (float *)_hoops_ASRHH; /* _hoops_SR _hoops_PPPPR'_hoops_RA _hoops_AGRP _hoops_SCH -- _hoops_GPHHH */
	}
	if (_hoops_CPHPA->weights == null) {
		if (_hoops_PSSSI->control_point_count > _hoops_GGAPR (_hoops_PSRHH)) {
			ALLOC_ARRAY (_hoops_CPHPA->weights, _hoops_PSSSI->control_point_count, float);
			for (i = 0; i < _hoops_PSSSI->control_point_count; i++)
				_hoops_CPHPA->weights[i] = 1;
		}
		else
			_hoops_CPHPA->weights = (float *)_hoops_PSRHH; /* _hoops_SR _hoops_PPPPR'_hoops_RA _hoops_AGRP _hoops_SCH -- _hoops_GPHHH */
	}
}


local void _hoops_HAAGGR(_hoops_PIRGR *_hoops_CPHPA, UV_Trim_Curve const *_hoops_PSSSI)
{
	FREE_ARRAY (_hoops_CPHPA->control_points, _hoops_CPHPA->control_point_count, Point);
	if (_hoops_PSSSI->knots == null && _hoops_CPHPA->knots != _hoops_ASRHH) {
		int _hoops_PAAGGR = _hoops_CPHPA->control_point_count + _hoops_CPHPA->degree + 1;
		FREE_ARRAY (_hoops_CPHPA->knots, _hoops_PAAGGR, float);
	}
	if (_hoops_PSSSI->weights == null && _hoops_CPHPA->weights != _hoops_PSRHH)
		FREE_ARRAY (_hoops_CPHPA->weights, _hoops_CPHPA->control_point_count, float);
}

local float _hoops_IPHPA(_hoops_GPHPA *edge, _hoops_PIRGR const *_hoops_CPHPA)
{	
	Point start, end, _hoops_SPGIR, _hoops_APIS, _hoops_ARGCR;
	HI_Point_On_NURBS_Curve (_hoops_CPHPA, edge->t, &start);
	HI_Point_On_NURBS_Curve (_hoops_CPHPA, edge->next->t, &end);
	HI_Point_On_NURBS_Curve (_hoops_CPHPA, (edge->t + edge->next->t)/2, &_hoops_APIS);
	_hoops_SPGIR.x = (start.x + end.x) / 2;
	_hoops_SPGIR.y = (start.y + end.y) / 2;
	_hoops_ARGCR.x = _hoops_APIS.x - _hoops_SPGIR.x;
	_hoops_ARGCR.y = _hoops_APIS.y - _hoops_SPGIR.y;
	return HI_Sqrt(
		(_hoops_ARGCR.x * _hoops_ARGCR.x) + 
		(_hoops_ARGCR.y * _hoops_ARGCR.y));
}


local void _hoops_IAAGGR (
	_hoops_HCRGGR *_hoops_HARIR)
{
	int old_allocated;
	UV_Point *temp;

	old_allocated = _hoops_HARIR->allocated;
	if (old_allocated >= 10)
		_hoops_HARIR->allocated *= 2;
	else
		_hoops_HARIR->allocated = 20;
	ALLOC_ARRAY_CACHED(temp, _hoops_HARIR->allocated, UV_Point);
	if (old_allocated) {
		if (_hoops_HARIR->used)
			_hoops_AIGA(_hoops_HARIR->uvpoints, _hoops_HARIR->used, UV_Point, temp);
		FREE_ARRAY(_hoops_HARIR->uvpoints, old_allocated, UV_Point);
	}
	_hoops_HARIR->uvpoints = temp;
}

typedef VHeap<_hoops_GPHPA *,float, true, true> _hoops_CAAGGR;

local void _hoops_SAAGGR (
	_hoops_AIGPR *						_hoops_RIGC,
	UV_Trim_Curve const *						curve, 
	_hoops_AIIAA const *	configs,
	_hoops_HCRGGR *							_hoops_HARIR) 
{
	int i;
	_hoops_PIRGR _hoops_CPHPA;
	Point _hoops_GPAGGR;
	float _hoops_RPAGGR, _hoops_APAGGR, t, _hoops_HGGRH;
	int _hoops_PPAGGR;
	_hoops_GPHPA *head, *edge, *prev, *_hoops_IHHPA;
	float priority;
	_hoops_CAAGGR *_hoops_HHHPA;
	UV_Point *uvpoints;
	int _hoops_HPAGGR;

	while ((_hoops_HARIR->allocated < _hoops_HARIR->used + curve->control_point_count) ||
		(_hoops_HARIR->allocated < _hoops_HARIR->used + configs->_hoops_CSHRP))
		_hoops_IAAGGR(_hoops_HARIR);


	if (curve->degree == 1) {
		/* _hoops_GRRC _hoops_CCA _hoops_CPSH 1 _hoops_IGGRA _hoops_SAHR _hoops_PII _hoops_PGRC */
		_hoops_AIGA (curve->control_points, curve->control_point_count, UV_Point, 
					&(_hoops_HARIR->uvpoints[_hoops_HARIR->used]));
		_hoops_HARIR->used += curve->control_point_count;
	}
	else {
		ALLOC_ARRAY_CACHED(uvpoints, configs->_hoops_CSHRP, UV_Point);
		_hoops_AAAGGR(&_hoops_CPHPA, curve);
		_hoops_PPAGGR = curve->control_point_count;
		if (_hoops_PPAGGR > configs->_hoops_CSHRP)
			_hoops_PPAGGR = configs->_hoops_CSHRP;
		_hoops_RPAGGR = _hoops_CPHPA.knots[curve->degree];
		_hoops_APAGGR = _hoops_CPHPA.knots[curve->control_point_count];
		t = _hoops_RPAGGR;
		_hoops_HGGRH = (_hoops_APAGGR - _hoops_RPAGGR) / (_hoops_PPAGGR - 1);
		head = prev = null;
		for (i = 0; i < _hoops_PPAGGR ; i++) {
			ALLOC(edge, _hoops_GPHPA);
			if (head == null)
				head = edge;
			if (prev != null)
				prev->next = edge;
			if (t < _hoops_RPAGGR + _hoops_CACIR) t = _hoops_RPAGGR + _hoops_CACIR;
			if (t > _hoops_APAGGR - _hoops_CACIR) t = _hoops_APAGGR - _hoops_CACIR;
			edge->index = i;
			edge->t = t;
			HI_Point_On_NURBS_Curve (&_hoops_CPHPA, t, &_hoops_GPAGGR);
			uvpoints[i].u = _hoops_GPAGGR.x;
			uvpoints[i].v = _hoops_GPAGGR.y;
			edge->next = null;
			prev = edge;
			t += _hoops_HGGRH;
		}
		_hoops_HPAGGR = i;

		/* _hoops_IPAGGR _hoops_RH _hoops_CCPH _hoops_AGIS _hoops_GIHPA _hoops_HRGII */
		_hoops_HHHPA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_CAAGGR)(_hoops_RIGC->memory_pool);
		edge = head;
		while (edge->next != null) {
			priority = _hoops_IPHPA(edge, &_hoops_CPHPA);
			edge->priority = priority;
			_hoops_HHHPA->Push(edge, priority); 
			edge = edge->next;
		}
		for (;;) {
			if (_hoops_HPAGGR >= configs->_hoops_CSHRP)
				goto done;
			if (!_hoops_HHHPA->Peek(&edge, &priority))
				break;
			if (priority < configs->_hoops_GGIRP)
				break;
			ALLOC(_hoops_IHHPA, _hoops_GPHPA);
			_hoops_IHHPA->index = _hoops_HPAGGR;
			_hoops_IHHPA->t = (edge->t + edge->next->t) / 2;
			HI_Point_On_NURBS_Curve (&_hoops_CPHPA, _hoops_IHHPA->t, &_hoops_GPAGGR);
			uvpoints[_hoops_HPAGGR].u = _hoops_GPAGGR.x;
			uvpoints[_hoops_HPAGGR].v = _hoops_GPAGGR.y;
			_hoops_HPAGGR++;
			_hoops_IHHPA->next = edge->next;
			edge->next = _hoops_IHHPA;
			priority = _hoops_IPHPA(edge, &_hoops_CPHPA);
			edge->priority = priority;
			_hoops_HHHPA->Update(edge, priority); /* _hoops_RPSGA */
			priority = _hoops_IPHPA(_hoops_IHHPA, &_hoops_CPHPA);
			_hoops_IHHPA->priority = priority;
			_hoops_HHHPA->Push(_hoops_IHHPA, priority); /* _hoops_CPAGGR _hoops_CCAH */
		}

		done:
		edge = head;
		while (edge != null) {
			_hoops_HARIR->uvpoints[ _hoops_HARIR->used ].u = uvpoints[edge->index].u;
			_hoops_HARIR->uvpoints[ _hoops_HARIR->used ].v = uvpoints[edge->index].v;
			_hoops_HARIR->used++;
			prev = edge;
			edge = edge->next;
			FREE(prev, _hoops_GPHPA);
		}
		FREE_ARRAY(uvpoints, configs->_hoops_CSHRP, UV_Point);
		delete _hoops_HHHPA;
		_hoops_HAAGGR(&_hoops_CPHPA, curve);
	}

}


local void _hoops_SPAGGR(
	UV_Trim_Poly const *node,
	_hoops_HCRGGR *_hoops_HARIR)
{
	while (_hoops_HARIR->allocated < _hoops_HARIR->used + node->count)
		_hoops_IAAGGR(_hoops_HARIR);
	_hoops_AIGA(node->points, node->count, UV_Point, &(_hoops_HARIR->uvpoints[_hoops_HARIR->used]));
	_hoops_HARIR->used += node->count;
}


local void _hoops_GHAGGR (
	_hoops_AIGPR *						_hoops_RIGC,
	UV_Trim *									node, 
	_hoops_AIIAA const *	configs, 
	_hoops_HCRGGR *							_hoops_HARIR) 
{
	if (node->next != null) {
		_hoops_GHAGGR(_hoops_RIGC, node->next, configs, _hoops_HARIR);
	}
	switch (node->type) {
		case _hoops_IARIR: {
			_hoops_SAAGGR(_hoops_RIGC, (UV_Trim_Curve *)node, configs, _hoops_HARIR);
		} break;
		case _hoops_PARIR: {
			_hoops_SPAGGR((UV_Trim_Poly *)node, _hoops_HARIR);
		} break;
		case _hoops_CARIR:
		default: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, 
				"unrecognized nurbs surface trimming type (or collection inside collection)");
		}
	}
}



local UV_Trim_Poly *_hoops_RHAGGR(
	_hoops_AIGPR *						_hoops_RIGC,
	UV_Trim *									trim, 
	_hoops_AIIAA const *	configs) 
{
	_hoops_HCRGGR temp;
	UV_Trim_Poly *_hoops_ASSSI;

	temp.used = 0;
	temp.allocated = 50;
	ALLOC_ARRAY_CACHED(temp.uvpoints, temp.allocated, UV_Point);
	switch (trim->type) {
		case _hoops_CARIR: {
			_hoops_GHAGGR(_hoops_RIGC, ((UV_Trim_Collection *)trim)->_hoops_GPRIR, configs, &temp);
		} break;
		case _hoops_IARIR: {
			_hoops_SAAGGR(_hoops_RIGC, (UV_Trim_Curve *)trim, configs, &temp);
		} break;
		case _hoops_PARIR: {
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, 
				"generate_trim_polyline should be used only for non-poly trims");
		}
		default:
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, 
				"unrecognized nurbs surface trimming type in generate_trim_polyline");
		break;
	}

	ALLOC(_hoops_ASSSI, UV_Trim_Poly);
	_hoops_ASSSI->type = _hoops_PARIR;
	_hoops_ASSSI->flags = 0;
	_hoops_ASSSI->next = null;
	_hoops_ASSSI->count = temp.used;
	ALLOC_ARRAY(_hoops_ASSSI->points, _hoops_ASSSI->count, UV_Point);	  
	_hoops_AIGA(temp.uvpoints, temp.used, UV_Point, _hoops_ASSSI->points);
	FREE_ARRAY(temp.uvpoints, temp.allocated, UV_Point);
	
	return _hoops_ASSSI;
}


local int _hoops_AHAGGR(
	UV_Trim *trim, 
	_hoops_AIIAA const *configs) 
{
	int length;
	UV_Trim *node; 

	length = 0;
	switch (trim->type) {
		case _hoops_CARIR: {
			if ((node = ((UV_Trim_Collection *)trim)->_hoops_GPRIR) != null) do {
				length += _hoops_AHAGGR(node, configs); /* _hoops_GHHA */
			} while ((node = node->next) != null);
		} break;
		case _hoops_IARIR: {
			length += ((UV_Trim_Curve *)trim)->control_point_count;
		} break;
		case _hoops_PARIR: {
			length += ((UV_Trim_Poly *)trim)->count;
		} break;
		default:
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, 
				"unrecognized nurbs surface trimming type in estimate_final_trim_length");
		break;
	}
	return length;
}


local void _hoops_PHAGGR(
	_hoops_AIGPR *						_hoops_RIGC,
	_hoops_APPGR const *						_hoops_SSHIH, 
	_hoops_AIIAA const *	configs,
	UV_Region_Set alter *						set)
{
	UV_Trim *node;
	UV_Trim_Poly *_hoops_HARIR;
	UV_Region_Set *_hoops_HHAGGR;

	node = _hoops_SSHIH->_hoops_GPRIR;
	while (node != null) {
		if (node->type == _hoops_PARIR) {
			_hoops_HARIR = (UV_Trim_Poly *) node;
		}
		else {
			_hoops_HARIR = _hoops_RHAGGR (_hoops_RIGC, node, configs);
		}
		if (node->flags & _hoops_RSSSI)
			_hoops_HHAGGR = HI_Generate_Polygonal_Region_Set	(-_hoops_HARIR->count, _hoops_HARIR->points, false);
		else
			_hoops_HHAGGR = HI_Generate_Polygonal_Region_Set	(_hoops_HARIR->count, _hoops_HARIR->points, false);
		HI_Subtract_Region_From_Region_Set	(set, _hoops_HHAGGR);
		HI_Free_Region_Set (_hoops_HHAGGR);
		if (_hoops_HARIR != (UV_Trim_Poly *) node)
			HI_Delete_Trim ((UV_Trim *) _hoops_HARIR);
		node = node->next;
	}
}


local bool _hoops_IHAGGR(
		int						count,
		UV_Point				*points)
{
	int i;
	for (i = 0 ; i < count ; i++) {
		if (points[i].u < 0 || 
			points[i].v < 0 ||
			points[i].u > 1 ||
			points[i].v > 1)
			return false;
	}
	return true;
}


local bool _hoops_CHAGGR(
	_hoops_AIGPR *						_hoops_RIGC,
	_hoops_APPGR const *						_hoops_SSHIH, 
	_hoops_AIIAA const *	configs,
	UV_Region_Set alter **						set)
{
	UV_Trim *node;
	UV_Trim_Poly *_hoops_HARIR;
	UV_Region_Set *_hoops_HHAGGR;
	bool status;
	int i;
	
	node = _hoops_SSHIH->_hoops_GPRIR;
	/* _hoops_SR _hoops_PAH _hoops_RGAR _hoops_RGHH _hoops_RSRA _hoops_SAPPA */
	if (node->next != null)
		return false;

	/* _hoops_ISCP _hoops_SHAGGR _hoops_RRGR (_hoops_PIGS _hoops_HII _hoops_RH _hoops_SHISR _hoops_CHHSI _hoops_CRAA) _hoops_SSCP _hoops_HHH
	 * _hoops_GIAGGR _hoops_HHGS, _hoops_HIS _hoops_ASSS _hoops_RGR _hoops_API _hoops_IS _hoops_RGHH _hoops_AARAR _hoops_CCA _hoops_RIAGGR _hoops_RGRRR _hoops_SAPPA, _hoops_PRGI
	 * _hoops_RPP _hoops_RH _hoops_RGSHA _hoops_RSSA _hoops_SPGA'_hoops_RA _hoops_IRPAA */
	if (!BIT(_hoops_SSHIH->_hoops_SHIAA, _hoops_CCSSI) &&
		_hoops_AHAGGR(node, configs) < configs->_hoops_CSHRP)
		return false;

	if (node->type == _hoops_PARIR) {
		_hoops_HARIR = (UV_Trim_Poly *) node;
	}
	else {
		_hoops_HARIR = _hoops_RHAGGR (_hoops_RIGC, node, configs);
	}
	if (_hoops_IHAGGR(_hoops_HARIR->count, _hoops_HARIR->points)) {
		if (node->flags & _hoops_RSSSI)
			_hoops_HHAGGR = HI_Generate_Polygonal_Region_Set	(_hoops_HARIR->count, _hoops_HARIR->points, true);
		else {
			_hoops_HHAGGR = HI_Generate_Polygonal_Region_Set	(-_hoops_HARIR->count, _hoops_HARIR->points, true);
			/* _hoops_CR _hoops_SR'_hoops_ASAR _hoops_CCGRA, _hoops_HAR _hoops_CAHAI, _hoops_SR _hoops_RRP _hoops_RH _hoops_RPAGP _hoops_ISPH _hoops_ARP _hoops_IS _hoops_SHH _hoops_IRPIS [0..1].
			 * _hoops_AIAGGR _hoops_GRS _hoops_GGCR 4 _hoops_IHH _hoops_RSSA _hoops_SGS _hoops_CHH _hoops_HCAGR _hoops_SSHSH _hoops_GRHCP */
			for (i = _hoops_HARIR->count ; i < _hoops_HARIR->count + 4 ; i++) {
				if (_hoops_HHAGGR->points[i].u < 0) 
					_hoops_HHAGGR->points[i].u = 0;
				else if (_hoops_HHAGGR->points[i].u > 1)
					_hoops_HHAGGR->points[i].u = 1;
				if (_hoops_HHAGGR->points[i].v < 0) 
					_hoops_HHAGGR->points[i].v = 0;
				else if (_hoops_HHAGGR->points[i].v > 1)
					_hoops_HHAGGR->points[i].v = 1;
			}
		}
		HI_Free_Region_Set (*set);
		*set = _hoops_HHAGGR;
		status = true;
	}
	else
		status = false;
	if (_hoops_HARIR != (UV_Trim_Poly *) node)
		HI_Delete_Trim ((UV_Trim *) _hoops_HARIR);
	return status;
}


local float _hoops_PIAGGR(
	UV_Region_Set const *set,
	UV_Edge const *a,
	UV_Edge const *b,
	_hoops_APPGR const *_hoops_SSHIH, 
	_hoops_IIRGGR alter *_hoops_CSC)
{
	UV_Point _hoops_HIAGGR, _hoops_IIAGGR, _hoops_SSPHH;
	Point _hoops_CIAGGR, _hoops_SIAGGR, _hoops_GCAGGR, _hoops_RCAGGR, _hoops_ARGCR;

	_hoops_HIAGGR.u = set->points[ a->index ].u; 
	_hoops_HIAGGR.v = set->points[ a->index ].v; 
	_hoops_IIAGGR.u = set->points[ b->index ].u; 
	_hoops_IIAGGR.v = set->points[ b->index ].v; 
	_hoops_SSPHH.u = (_hoops_HIAGGR.u + _hoops_IIAGGR.u) / 2;
	_hoops_SSPHH.v = (_hoops_HIAGGR.v + _hoops_IIAGGR.v) / 2;
	_hoops_CCRGGR (_hoops_SSHIH, _hoops_SSPHH.u, _hoops_SSPHH.v, &_hoops_RCAGGR, _hoops_CSC);
	_hoops_CCRGGR (_hoops_SSHIH, _hoops_HIAGGR.u, _hoops_HIAGGR.v, &_hoops_CIAGGR, _hoops_CSC);
	_hoops_CCRGGR (_hoops_SSHIH, _hoops_IIAGGR.u, _hoops_IIAGGR.v, &_hoops_SIAGGR, _hoops_CSC);
	_hoops_GCAGGR.x = (_hoops_CIAGGR.x + _hoops_SIAGGR.x) / 2;
	_hoops_GCAGGR.y = (_hoops_CIAGGR.y + _hoops_SIAGGR.y) / 2;
	_hoops_GCAGGR.z = (_hoops_CIAGGR.z + _hoops_SIAGGR.z) / 2;
	_hoops_ARGCR.x = _hoops_RCAGGR.x - _hoops_GCAGGR.x;
	_hoops_ARGCR.y = _hoops_RCAGGR.y - _hoops_GCAGGR.y;
	_hoops_ARGCR.z = _hoops_RCAGGR.z - _hoops_GCAGGR.z;
	return HI_Sqrt(
		(_hoops_ARGCR.x * _hoops_ARGCR.x) +
		(_hoops_ARGCR.y * _hoops_ARGCR.y) +
		(_hoops_ARGCR.z * _hoops_ARGCR.z));
}


local float _hoops_ACAGGR(
	UV_Region_Set const *set,
	UV_Edge const *a,
	UV_Edge const *b,
	_hoops_APPGR const *_hoops_SSHIH, 
	_hoops_IIRGGR alter *_hoops_CSC)
{
	Vector _hoops_ICIPR, _hoops_CCIPR;
	UV_Point *start, *end;
	float _hoops_SSRP;

	start = &set->points[a->index];
	end = &set->points[b->index];
	_hoops_PRAGGR (_hoops_SSHIH, start->u, start->v, &_hoops_ICIPR, _hoops_CSC);
	_hoops_PRAGGR (_hoops_SSHIH, end->u, end->v, &_hoops_CCIPR, _hoops_CSC);
	_hoops_SSRP = (_hoops_ICIPR.x * _hoops_CCIPR.x) + (_hoops_ICIPR.y * _hoops_CCIPR.y) + (_hoops_ICIPR.z * _hoops_CCIPR.z);
	return HI_ACos(_hoops_SSRP); /* _hoops_ASGA _hoops_AAPR _hoops_SCGA _hoops_HPP _hoops_PCAGGR() */
}


local float _hoops_HCAGGR(
	UV_Region_Set const *set,
	UV_Edge const *a,
	UV_Edge const *b)
{
	UV_Point _hoops_ARGCR;
	_hoops_ARGCR.u = set->points[ b->index ].u - set->points[ a->index ].u;
	_hoops_ARGCR.v = set->points[ b->index ].v - set->points[ a->index ].v;
	return HI_Sqrt(
		(_hoops_ARGCR.u * _hoops_ARGCR.u) +
		(_hoops_ARGCR.v * _hoops_ARGCR.v));
}


local int _hoops_ICAGGR(UV_Region *region) 
{
	UV_Edge *edge = region->_hoops_GRCPR;
	int count = 0;

	do {
		count++;
	} while ((edge = edge->next) != region->_hoops_GRCPR);
	return count;
}



local void _hoops_CCAGGR(
	UV_Region_Set alter *set,
	UV_Region alter *region,
	int level,
	int _hoops_SCAGGR,
	_hoops_APPGR const *_hoops_SSHIH, 
	_hoops_AIIAA const *configs,
	_hoops_IIRGGR alter *_hoops_CSC) 
{
	bool _hoops_GSAGGR = false;
	int i, _hoops_RSAGGR;
	UV_Region alter **_hoops_ASAGGR;
	UV_Edge *a, *b, *c;
	
	if (level < _hoops_SCAGGR &&
		set->point_count < configs->_hoops_SSHRP) {

		if (_hoops_ICAGGR(region) > 6) {
			_hoops_GSAGGR = true;
		}
		else {

			HI_Get_UV_Region_Triangle(set, region, &a, &b, &c);

			if (_hoops_PIAGGR(set, a, b, _hoops_SSHIH, _hoops_CSC) > configs->_hoops_RGIRP || 
				_hoops_ACAGGR(set, a, b, _hoops_SSHIH, _hoops_CSC) > configs->_hoops_AGIRP || 
				_hoops_PIAGGR(set, b, c, _hoops_SSHIH, _hoops_CSC) > configs->_hoops_RGIRP || 
				_hoops_ACAGGR(set, b, c, _hoops_SSHIH, _hoops_CSC) > configs->_hoops_AGIRP || 
				_hoops_PIAGGR(set, c, a, _hoops_SSHIH, _hoops_CSC) > configs->_hoops_RGIRP || 
				_hoops_ACAGGR(set, c, a, _hoops_SSHIH, _hoops_CSC) > configs->_hoops_AGIRP) {
				_hoops_GSAGGR = true;
			}
			else if (configs->_hoops_PGIRP < 1.41) {
				if (_hoops_HCAGGR(set, a, b) > configs->_hoops_PGIRP ||
					_hoops_HCAGGR(set, a, b) > configs->_hoops_PGIRP ||
					_hoops_HCAGGR(set, a, b) > configs->_hoops_PGIRP) {
					_hoops_GSAGGR = true;
				}
			}
		}

		if (_hoops_GSAGGR) {
			HI_Midpoint_Split_Triangle(set, region, &_hoops_RSAGGR, &_hoops_ASAGGR);
			ASSERT(_hoops_RSAGGR == 4);
			for (i = 0 ; i < _hoops_RSAGGR ; i++) {
				_hoops_CCAGGR(set, _hoops_ASAGGR[i], level+1, _hoops_SCAGGR, _hoops_SSHIH, configs, _hoops_CSC);
			}
			FREE_ARRAY(_hoops_ASAGGR, _hoops_RSAGGR, UV_Region *);
		}
	}
}


local void _hoops_PSAGGR(
	_hoops_APPGR const *_hoops_SSHIH, 
	_hoops_AIIAA const *configs,
	int recursion_limit,
	UV_Region_Set alter *set,
	_hoops_IIRGGR alter *_hoops_CSC)
{
	UV_Region *region, *tail;
	
	region = tail = set->regions;
	while (tail->next != null)
		tail = tail->next;
	while (region != tail) {
		_hoops_CCAGGR(set, region, 0, recursion_limit, _hoops_SSHIH, configs, _hoops_CSC);
		region = region->next;
		if (set->point_count >= configs->_hoops_SSHRP)
			return; /* _hoops_ICPPA -- _hoops_SR'_hoops_GCPP _hoops_HPPR _hoops_GICS _hoops_SPHR _hoops_CCA _hoops_IRS _hoops_GSSC _hoops_PAGIR _hoops_SAIPR */
	}
	_hoops_CCAGGR(set, tail, 0, recursion_limit, _hoops_SSHIH, configs, _hoops_CSC);

	/* _hoops_HRHH _hoops_PGHH _hoops_SGS _hoops_AAPR _hoops_RAAP _hoops_CCA _hoops_HHGP _hoops_SPPR */
	region = set->regions;
	while (region != null) {
		HI_Triangulate_Region(set, region);
		region = region->next;
	}

} /* _hoops_RSGR _hoops_API _hoops_HSAGGR */


local void _hoops_ISAGGR(
	_hoops_AIGPR *			_hoops_RIGC,
	UV_Region_Set const *			set, 
	_hoops_IIRGGR alter *	_hoops_CSC, 
	_hoops_APPGR alter *			_hoops_SSHIH)
{
	Shell *_hoops_SPHPR;
	Polyhedron *phon;
	Point *_hoops_CSAGGR;
	Vector *_hoops_SSAGGR;
	_hoops_RSSH *_hoops_GGPGGR;
	int i;

	if (_hoops_SSHIH->_hoops_IPRI != null)
		HI_Au_Revoir((_hoops_HPAH *)_hoops_SSHIH->_hoops_IPRI);
	ZALLOC (_hoops_SPHPR, Shell);
	_hoops_SSHIH->_hoops_IPRI = phon = (Polyhedron *)_hoops_SPHPR;
	phon->backlink = (Geometry **)&_hoops_SSHIH->_hoops_IPRI;
	phon->_hoops_HIHI = 1;
	phon->type = _hoops_SCIP;
	phon->_hoops_CPGPR = _hoops_CASIR;
	phon->owner = _hoops_SSHIH->owner;
	phon->key = _hoops_SSHIH->key;
	phon->priority = _hoops_SSHIH->priority;
	phon->_hoops_SPHA = -1; /* _hoops_HAR _hoops_HSSPR _hoops_GAPR */

	if (set->point_count != 0) {
		ALLOC_ARRAY_ALIGNED (_hoops_CSAGGR, set->point_count, Point, 16);
		ALLOC_ARRAY	(_hoops_SSAGGR, set->point_count, Vector);
		ALLOC_ARRAY	(_hoops_GGPGGR, 2*set->point_count, _hoops_RSSH);

		for (i = 0; i < set->point_count; i++) {
			_hoops_CCRGGR  (_hoops_SSHIH, set->points[i].u, set->points[i].v, &_hoops_CSAGGR[i], _hoops_CSC);
			/* _hoops_IH _hoops_GSPHR: _hoops_IS _hoops_SHRPA _hoops_GGR _hoops_PRISA _hoops_RGPGGR _hoops_RIIA _hoops_IIGR _hoops_CARA _hoops_SGGPR _hoops_GC...
			_hoops_AGPGGR[_hoops_HAS]._hoops_SISR = _hoops_ARP->_hoops_RSSA[_hoops_HAS]._hoops_IARGR;
			_hoops_AGPGGR[_hoops_HAS]._hoops_HAPC = _hoops_ARP->_hoops_RSSA[_hoops_HAS]._hoops_HPPC;
			_hoops_AGPGGR[_hoops_HAS]._hoops_SSH = 0;
			*/
			_hoops_PRAGGR  (_hoops_SSHIH, set->points[i].u, set->points[i].v, &_hoops_SSAGGR[i], _hoops_CSC);
			_hoops_GGPGGR[i*2]   = set->points[i].u;
			_hoops_GGPGGR[i*2+1] = set->points[i].v;
		}
		phon->point_count = set->point_count;
		phon->points = _hoops_CSAGGR;
		HI_Convert_Regions_To_Facelist (
					set, 
					&_hoops_SPHPR->face_list, 
					&_hoops_SPHPR->face_list_length, 
					&phon->face_count);
		/* _hoops_ARP _hoops_RH _hoops_ASGA _hoops_CRS _hoops_PPR _hoops_RH _hoops_APIP _hoops_IGRH, _hoops_HIH _hoops_HAR _hoops_RH _hoops_IRGH _hoops_RIR-_hoops_GPHA
		 * _hoops_SGI -- _hoops_SR _hoops_HHGC _hoops_ASGA _hoops_IS _hoops_SHH _hoops_HSHA _hoops_GAR _hoops_IHPPR _hoops_PRHI */
		phon->local_vertex_attributes.normals = _hoops_SSAGGR;
		phon->local_vertex_attributes.explicit_normal_count = phon->point_count;
		phon->local_vertex_attributes._hoops_SIIPR = phon->point_count;
		phon->local_vertex_attributes._hoops_IPHIR = _hoops_GGPGGR;
		phon->local_vertex_attributes._hoops_SGRHR |= LVA_EXPLICIT_NORMAL | _hoops_HHIAA;
		phon->polyhedron_flags |= PHF_VERTEX_NORMALS_VALID;
	}

	phon->_hoops_CPGPR = _hoops_AHSGA;
	HI_Figure_Geometry_Bounding ((Geometry *)phon, phon->bounding);
	phon->_hoops_CPGPR = _hoops_CASIR;

	HI_Propagate_Bounding (_hoops_RIGC, _hoops_SSHIH->owner, phon->bounding, null);

	UNREFERENCED(_hoops_CSC);

} /* _hoops_RSGR _hoops_API _hoops_PGPGGR */


local void _hoops_HGPGGR(_hoops_APPGR alter *_hoops_SSHIH, float alter **_hoops_IGPGGR, float alter **_hoops_CGPGGR)
{
	int i;
	int _hoops_RSPIR = _hoops_SSHIH->u_degree + _hoops_SSHIH->n_u_vertices + 1;
	int _hoops_ASPIR = _hoops_SSHIH->v_degree + _hoops_SSHIH->n_v_vertices + 1;

	*_hoops_IGPGGR = _hoops_SSHIH->u_knots;
	*_hoops_CGPGGR = _hoops_SSHIH->v_knots;
	if (_hoops_SSHIH->u_knots == null) {
		ALLOC_ARRAY (_hoops_SSHIH->u_knots, _hoops_RSPIR, float);
		for (i = 0; i < _hoops_RSPIR; i++) {
			_hoops_SSHIH->u_knots[i] = (float) i;
		}
	}
	if (_hoops_SSHIH->v_knots == null) {
		ALLOC_ARRAY (_hoops_SSHIH->v_knots, _hoops_ASPIR, float);
		for (i = 0; i < _hoops_ASPIR; i++) {
			_hoops_SSHIH->v_knots[i] = (float) i;
		}
	}
}

local void _hoops_SGPGGR(_hoops_APPGR alter *_hoops_SSHIH, float const *_hoops_IGPGGR, float const *_hoops_CGPGGR)
{
	int _hoops_RSPIR = _hoops_SSHIH->u_degree + _hoops_SSHIH->n_u_vertices + 1;
	int _hoops_ASPIR = _hoops_SSHIH->v_degree + _hoops_SSHIH->n_v_vertices + 1;

	if (_hoops_IGPGGR == null) {
		FREE_ARRAY (_hoops_SSHIH->u_knots, _hoops_RSPIR, float);
		_hoops_SSHIH->u_knots = null;
	}
	if (_hoops_CGPGGR == null) {
		FREE_ARRAY (_hoops_SSHIH->v_knots, _hoops_ASPIR, float);
		_hoops_SSHIH->v_knots = null;
	}
}



#endif /*#_hoops_CHS _hoops_IRIPS*/


GLOBAL_FUNCTION void HI_Tessellate_NURBS_Surface (
	_hoops_AIGPR *						_hoops_RIGC,
	_hoops_APPGR const *						_hoops_GRPGGR, 
	_hoops_AIIAA const *	configs) 
{
#ifndef _hoops_GSPIR
	_hoops_APPGR alter *_hoops_SSHIH = (_hoops_APPGR alter *)_hoops_GRPGGR;
	float *_hoops_IGPGGR, *_hoops_CGPGGR;
	UV_Region_Set *set;
	int recursion_limit;

	/* _hoops_IH _hoops_RH _hoops_AHAR _hoops_IIGR _hoops_GSGRS, _hoops_SR _hoops_GCGRA _hoops_GII _hoops_IRAP _hoops_SGHSA _hoops_CCA _hoops_PAII
	 * _hoops_HPRGR _hoops_GHRHR _hoops_HSSHH, _hoops_HIH _hoops_PAPGS, _hoops_SR _hoops_CIH _hoops_PPR _hoops_PHIH _hoops_IS _hoops_IRAP (_hoops_RPP _hoops_SAGH)
	 * _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_AGS _hoops_GH _hoops_GII _hoops_PPGS _hoops_SRPSI. _hoops_PAGA _hoops_SGS _hoops_IIH _hoops_HRGR _hoops_PSP _hoops_RRP _hoops_IS _hoops_AA _hoops_HIS _hoops_IH _hoops_HHRP,
	 * _hoops_CR _hoops_RH _hoops_GSSC-_hoops_PAPA _hoops_SICAR _hoops_PAH _hoops_CRSHS _hoops_IRAP _hoops_CGI _hoops_GGR _hoops_IH _hoops_AGAP. */
	_hoops_HGPGGR(_hoops_SSHIH, &_hoops_IGPGGR, &_hoops_CGPGGR);

	_hoops_IIRGGR *	_hoops_CSC = 
		POOL_NEW(_hoops_RIGC->memory_pool, _hoops_IIRGGR)(_hoops_RIGC->memory_pool, configs->_hoops_SSHRP * 2);

	if (BIT(_hoops_SSHIH->_hoops_SHIAA,_hoops_CCSSI)) {
		set = HI_Generate_Rectangular_Regions (0, 1, 0, 1, 1, 1);
	}
	else if (BIT (HOOPS_WORLD->_hoops_IRARR, _hoops_SGHGI)) {
		int ucount, vcount, _hoops_PPPI;
		/* _hoops_SGH _hoops_IRS _hoops_HAGH _hoops_SHIR _hoops_IH _hoops_RGR _hoops_AGIR */
		if (configs->_hoops_SSHRP == 10000) /* _hoops_PIHA _hoops_PSSP _hoops_RRPGGR._hoops_GSGGR */
			_hoops_PPPI = 400;
		else
			_hoops_PPPI = configs->_hoops_SSHRP;
		ucount = vcount = (int) _hoops_SGIHR ((float)_hoops_PPPI);
		if (ucount < _hoops_SSHIH->n_u_vertices - 1) ucount = _hoops_SSHIH->n_u_vertices - 1;
		if (vcount < _hoops_SSHIH->n_v_vertices - 1) vcount = _hoops_SSHIH->n_v_vertices - 1;
		set = HI_Generate_Rectangular_Regions (0, 1, 0, 1, ucount, vcount);
	}
	else {
		recursion_limit = 4;
		for (;;) {
			/* _hoops_HSPP _hoops_HPP _hoops_PSCS _hoops_IRS _hoops_CAPS _hoops_IPHIC [0..1][0..1] */
			set = HI_Generate_Triangular_Regions (0, 1, 0, 1, _hoops_SSHIH->n_u_vertices - 1, _hoops_SSHIH->n_v_vertices - 1);
			_hoops_PSAGGR(_hoops_SSHIH, configs, recursion_limit, set, _hoops_CSC);
			if (set->point_count < configs->_hoops_SSHRP || recursion_limit == 1)
				break;
			HI_Free_Region_Set (set);
			recursion_limit--;
		}
	}
	if (_hoops_SSHIH->_hoops_GPRIR != null) {
		if (!_hoops_CHAGGR(_hoops_RIGC, _hoops_SSHIH, configs, &set))
			_hoops_PHAGGR(_hoops_RIGC, _hoops_SSHIH, configs, set);
	}
	_hoops_ISAGGR(_hoops_RIGC, set, _hoops_CSC, _hoops_SSHIH);
	_hoops_SSHIH->_hoops_GRPPA = configs->_hoops_GRPPA;

	/* _hoops_GGAS */
	if (_hoops_CSC != null) {
		_hoops_CSC->MapFunction(_hoops_RCRGGR, null);
		delete _hoops_CSC;
	}
	HI_Free_Region_Set (set);
	_hoops_SGPGGR(_hoops_SSHIH, _hoops_IGPGGR, _hoops_CGPGGR);
#endif
} 


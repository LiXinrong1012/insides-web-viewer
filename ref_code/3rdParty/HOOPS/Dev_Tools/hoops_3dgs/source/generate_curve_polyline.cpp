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
 * $Id: obf_tmp.txt 1.70 2010-07-21 19:46:37 covey Exp $
 */

#include "hoops.h"
#include "hc_proto.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "tandt.h"
#include "hpserror.h"
#include <math.h>

#ifndef _hoops_CCPIR


static const float _hoops_ASRHH[] = {
		0,	1,	2,	3,	4,	5,	6,	7,	8,	9,	10, 11, 12, 13, 14, 15 };
static const float _hoops_PSRHH[] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };



#define _hoops_HSRHH 32
#define _hoops_IACIR (1e20f)
#define _hoops_ISRHH 8
#define _hoops_IRGPA 2.0f
#define _hoops_CSRHH 50
#define _hoops_SSRHH (0.345f)
#define _hoops_GGAHH (0.645f)
#define _hoops_CACIR (1e-5f)

#define _hoops_PCAHP(i) ((i-1)/2)
#define _hoops_HCAHP(i) (2*i+1)
#define _hoops_ICAHP(i) (2*i+2)


struct _hoops_RGAHH {
	float priority;
	float u_left;
	Point _hoops_AGAHH;
};


/* _hoops_RGR _hoops_PPARR _hoops_GIASP _hoops_GIHPA _hoops_HII _hoops_RH _hoops_PRISA _hoops_IPPHR */
struct  _hoops_PGAHH : public _hoops_RGAHH {
	float _hoops_HGAHH;
	Point _hoops_IGAHH, _hoops_CGAHH, _hoops_SGAHH;
};


/* _hoops_RGR _hoops_PPARR _hoops_GIASP _hoops_RCSA _hoops_GAPA _hoops_SCGR _hoops_PPR _hoops_SPS _hoops_III _hoops_SGHC (_hoops_HAS._hoops_IAS. _hoops_RCSA _hoops_HPGR _hoops_GPHA _hoops_GPP _hoops_RPHR) */
struct _hoops_GRAHH : public _hoops_RGAHH {
	struct _hoops_GRAHH *next;
};



struct _hoops_RRAHH {
	_hoops_RGAHH **array;
	int allocated, used;
};

/* _hoops_GIASP _hoops_RH _hoops_GIHPA _hoops_IIGR _hoops_RH _hoops_RAII _hoops_III _hoops_SGHC _hoops_HII _hoops_RH _hoops_AGIS'_hoops_GRI _hoops_IHPR _hoops_CRAA */
typedef struct _hoops_ARAHH {
	float *data;
	int used, allocated;
} _hoops_PRAHH;

local void _hoops_HRAHH (_hoops_PRAHH *_hoops_IRAHH, float _hoops_HAGR) {
	if (_hoops_IRAHH->used == _hoops_IRAHH->allocated) {
		float *temp;
		int i;

		ALLOC_ARRAY (temp, _hoops_IRAHH->allocated * 2, float);
		for (i = 0; i < _hoops_IRAHH->used; i++)
			temp[i] = _hoops_IRAHH->data[i];
		FREE_ARRAY (_hoops_IRAHH->data, _hoops_IRAHH->allocated, float);
		_hoops_IRAHH->allocated *= 2;
		_hoops_IRAHH->data = temp;
	}
	_hoops_IRAHH->data[_hoops_IRAHH->used++] = _hoops_HAGR;
}

local void swaph(_hoops_RRAHH *heap, int i, int j);		/* _hoops_CPCHR */

#define QS_TYPE				_hoops_RRAHH *					/* _hoops_RH _hoops_GPRR _hoops_IIGR _hoops_CARA _hoops_PAR _hoops_CRPR _hoops_SGS _hoops_ICGI _hoops_HCR _hoops_HSH */
#define QS_VAL(thing,a)		(thing->array[a]->u_left)	/* _hoops_HRS _hoops_RH _hoops_PIRA _hoops_IIGR _hoops_PCCP _hoops_IGCI _hoops_CCA _hoops_CIHA _hoops_IRS */
#define QS_COMPARE(f1,f2)	(f1>f2)					/* _hoops_SGH ">" _hoops_IS _hoops_GHIS _hoops_GACPR, "<" _hoops_IS _hoops_GHIS _hoops_CPIHR */
#define QS_SWAP(thing,a,b)	swaph(thing, a, b)		/* _hoops_SPIHR _hoops_PGCR _hoops_HSH */
#include "utility/hqsort.h"								/* _hoops_RSSAR _hoops_IRS _hoops_API, "_hoops_CRAHH" _hoops_SGS _hoops_RAIA _hoops_RH _hoops_ARRS _hoops_CIGR */


/*
 * _hoops_IPCP _hoops_HSPR 3 _hoops_HICRR _hoops_PSCH, _hoops_SRAHH(), _hoops_GAAHH(), _hoops_PPR _hoops_GGCR()
 * _hoops_CHR _hoops_HSHPR _hoops_IS _hoops_RH _hoops_ARIPR _hoops_PAPR _hoops_GGR _hoops_RAAHH._hoops_GSGGR
 */

/*********************************************************************\
 *	_hoops_SRAHH:
 *	_hoops_PGAA
 *	_hoops_IRS _hoops_CPPPR _hoops_AAAHH _hoops_HAPRR _hoops_API _hoops_IIHA _hoops_GGR _hoops_ARIP
 *	_hoops_GPP _hoops_HHH _hoops_RRGR _hoops_HII _hoops_PAAHH.
 *	_hoops_HGI _hoops_API _hoops_RHAP *_hoops_ASAI* _hoops_AA _hoops_CIHH.  _hoops_PS _hoops_RGAR _hoops_RRP _hoops_SCH _hoops_IS
 *	_hoops_CACH _hoops_RPP _hoops_PGCR _hoops_RSSA _hoops_GRS _hoops_RPGAH _hoops_RH _hoops_PSHR _hoops_GPP _hoops_RH _hoops_SHPR.
\*********************************************************************/
local void _hoops_HAAHH (_hoops_HRPA const	*matrix, Point const *in, Point *_hoops_PAGR) {
	float _hoops_SACC, w;

	if ((w = _hoops_PHCP (matrix->elements, in[0])) == 0.0f) {
		/* _hoops_ASAC _hoops_CAPR _hoops_HII _hoops_IAAHH _hoops_HPP _hoops_AHHR... */
		_hoops_PAGR->x = 0.0f;
		_hoops_PAGR->y = 0.0f;
		_hoops_PAGR->z = 0.0f;
	}
	else {
		_hoops_PAGR->x = _hoops_HPRA (matrix->elements, in[0]) / w;
		_hoops_PAGR->y = _hoops_IPRA (matrix->elements, in[0]) / w;
		_hoops_SACC = _hoops_CPRA (matrix->elements, in[0]) / w;
		_hoops_PAGR->z = _hoops_SACC;/*_hoops_CAAHH (_hoops_SAAHH, _hoops_CPSP);*/
	}

} /* _hoops_RSGR _hoops_API _hoops_SRAHH */


/*********************************************************************\
 *	_hoops_GPAHH
 *	_hoops_PGAA
 *	_hoops_HRS _hoops_IHPR _hoops_CHGRR _hoops_RH _hoops_PGCR _hoops_CIIA _hoops_RSSA _hoops_CHH _hoops_HIHP _hoops_CRGR
 *	_hoops_RH _hoops_PSHR _hoops_PPSR _hoops_GPP _hoops_RH _hoops_AIRI (_hoops_IS _hoops_GIAA _hoops_IRS _hoops_AAHP).
\*********************************************************************/
local int _hoops_RPAHH (_hoops_HRPA const *matrix, Point const *f1, Point const *f2) {
	Point _hoops_APAHH, _hoops_PPAHH;
	float _hoops_ARGCR = 0;

	_hoops_HAAHH (matrix, f1, &_hoops_APAHH);
	_hoops_HAAHH (matrix, f2, &_hoops_PPAHH);

	if (_hoops_APAHH.x > _hoops_PPAHH.x)
		_hoops_ARGCR += (_hoops_APAHH.x - _hoops_PPAHH.x);
	else
		_hoops_ARGCR -= (_hoops_APAHH.x - _hoops_PPAHH.x);
	if (_hoops_APAHH.y > _hoops_PPAHH.y)
		_hoops_ARGCR += (_hoops_APAHH.y - _hoops_PPAHH.y);
	else
		_hoops_ARGCR -= (_hoops_APAHH.y - _hoops_PPAHH.y);
	if (_hoops_APAHH.z > _hoops_PPAHH.z)
		_hoops_ARGCR += (_hoops_APAHH.z - _hoops_PPAHH.z);
	else
		_hoops_ARGCR -= (_hoops_APAHH.z - _hoops_PPAHH.z);

	if (_hoops_ARGCR > _hoops_IRGPA)
		return 0;
	else
		return 1;
} /* _hoops_RSGR _hoops_API _hoops_GPAHH */


/*********************************************************************\
 *	_hoops_HPAHH
 *	_hoops_AAGA + _hoops_AAGA
\*********************************************************************/
local void _hoops_IPAHH (const Point *_hoops_GGIAR, const Point *p1, Point *_hoops_PAGR) {
	_hoops_PAGR->x = _hoops_GGIAR->x + p1->x;
	_hoops_PAGR->y = _hoops_GGIAR->y + p1->y;
	_hoops_PAGR->z = _hoops_GGIAR->z + p1->z;
}

/* _hoops_GGCR _hoops_PARAA _hoops_HII _hoops_PCCP _hoops_CRPR _hoops_IIGR _hoops_SHGS */
local void _hoops_CPAHH (Point *array, const Point *p, int count)
{
	int i;

	for (i = 0; i < count; i++) {
		array->x += p->x;
		array->y += p->y;
		array->z += p->z;
		array++;
	}
}


/*********************************************************************\
 *	_hoops_SPAHH
 *	_hoops_PGAA
 *	_hoops_AAGA _hoops_GHAHH _hoops_HPP _hoops_IRS _hoops_RHAHH
\*********************************************************************/
local void _hoops_AHAHH (Point const *_hoops_PHAHH, float _hoops_HHAHH, Point *_hoops_IHAHH) {
	_hoops_IHAHH->x = _hoops_PHAHH->x / _hoops_HHAHH;
	_hoops_IHAHH->y = _hoops_PHAHH->y / _hoops_HHAHH;
	_hoops_IHAHH->z = _hoops_PHAHH->z / _hoops_HHAHH;
} /* _hoops_RSGR _hoops_API _hoops_SPAHH */




/*********************************************************************\
 *	_hoops_CHAHH:
 *	_hoops_PGAA
 *	_hoops_SHAHH = _hoops_RRAS (_hoops_PPSR[_hoops_HAS] * _hoops_SGCR[_hoops_HAS])
 *	_hoops_HAR _hoops_GICPR _hoops_GGSP _hoops_RPP _hoops_SHAHH _hoops_GIHRR _hoops_GGR _hoops_RSSA
\*********************************************************************/
local void _hoops_GIAHH (int start, int end, const Point *points, const float *weights, Point *_hoops_SSPSA) {
	int i;

	_hoops_SSPSA->x = _hoops_SSPSA->y = _hoops_SSPSA->z = 0;

	for (i = start; i < end; i++)
	{
		_hoops_SSPSA->x += points[i].x * weights[i];
		_hoops_SSPSA->y += points[i].y * weights[i];
		_hoops_SSPSA->z += points[i].z * weights[i];
	}
} /* _hoops_RSGR _hoops_API _hoops_CHAHH */


/* _hoops_ICHRA _hoops_PARAA _hoops_HII _hoops_PCCP _hoops_CRPR _hoops_IIGR _hoops_SHGS */
local void _hoops_RIAHH (Point *array, const Point *p, int count)
{
	int i;

	for (i = 0; i < count; i++) {
		array->x -= p->x;
		array->y -= p->y;
		array->z -= p->z;
		array++;
	}
}


local float _hoops_AIAHH (Vector const *v)
{
	return  (v->x * v->x) +
			(v->y * v->y) +
			(v->z * v->z);
}


#if 0
/*********************************************************************\
 *	_hoops_PIAHH
 *	_hoops_AAGA - _hoops_AAGA
\*********************************************************************/
local void _hoops_HIAHH (const Point *_hoops_GGIAR, const Point *p1, Point *_hoops_PAGR) {
	_hoops_PAGR->x = _hoops_GGIAR->x - p1->x;
	_hoops_PAGR->y = _hoops_GGIAR->y - p1->y;
	_hoops_PAGR->z = _hoops_GGIAR->z - p1->z;
}


local float _hoops_IIAHH (Point const *_hoops_ISPI, Point const *_hoops_CSPI) {
	return (
		(_hoops_ISPI->x * _hoops_CSPI->x) +
		(_hoops_ISPI->y * _hoops_CSPI->y) +
		(_hoops_ISPI->z * _hoops_CSPI->z)
	);
}
/*********************************************************************\
 *	_hoops_CIAHH
 *	_hoops_PGAA
 *	_hoops_GCAAA _hoops_PCCP _hoops_RIHH _hoops_CSHHR _hoops_IIHA _hoops_GPP _hoops_RH _hoops_RCSA _hoops_GAPA _hoops_PSPAR
 *	_hoops_IPCP _hoops_RHPHR _hoops_IH _hoops_RH _hoops_CSHHR _hoops_HRGR
 *		 [(|_hoops_IIHHR|*|_hoops_CIHHR|) / _hoops_PSCHR(_hoops_IIHHR,_hoops_CIHHR)]^2
 *	_hoops_PAR
 *		 [1/_hoops_HHSPA(_hoops_CCSA)]^2
\*********************************************************************/
local float _hoops_SIAHH (Point const *left, Point const *_hoops_SPGIR, Point const *right) {
	Point _hoops_ISPI, _hoops_CSPI;
	float _hoops_GCAHH, _hoops_RCAHH, f;

	_hoops_HIAHH (_hoops_SPGIR, left, &_hoops_ISPI);
	_hoops_HIAHH (_hoops_SPGIR, right, &_hoops_CSPI);
	_hoops_GCAHH = _hoops_AIAHH (&_hoops_ISPI);
	_hoops_RCAHH = _hoops_AIAHH (&_hoops_CSPI);
	if (
		 (_hoops_GCAHH < _hoops_CACIR && _hoops_GCAHH > -_hoops_CACIR) ||
		 (_hoops_RCAHH < _hoops_CACIR && _hoops_RCAHH > -_hoops_CACIR)
	 )
		return 0;
	f = _hoops_IIAHH (&_hoops_ISPI, &_hoops_CSPI);
	f = (_hoops_GCAHH * _hoops_RCAHH) / (f * f);
	return f;
} /* _hoops_RSGR _hoops_API _hoops_CIAHH */
#endif

/*********************************************************************\
 *	_hoops_ACAHH
 *	_hoops_PGAA
 *	_hoops_IPS _hoops_IRS _hoops_AAGA _hoops_IS _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_CCAHR'_hoops_GRI _hoops_RSSA _hoops_CRPR.  _hoops_IPCS
 *	_hoops_RH _hoops_CRPR _hoops_RPP _hoops_HAHH.
\*********************************************************************/
local void _hoops_PCAHH (const Point *_hoops_PHAHH, Polyline *p) {
	if (p->count >= p->allocated)
	{
		Point *temp;

		ALLOC_ARRAY (temp, p->allocated*2, Point);
		_hoops_AIGA (p->points, p->count, Point, temp);
		FREE_ARRAY (p->points, p->allocated, Point);
		p->allocated *= 2;
		p->points = temp;
	}
	p->points[p->count].x = _hoops_PHAHH->x;
	p->points[p->count].y = _hoops_PHAHH->y;
	p->points[p->count].z = _hoops_PHAHH->z;
	p->count++;
} /* _hoops_RSGR _hoops_API _hoops_ACAHH */


/* #_hoops_PPIP _hoops_HCAHH  */
#ifdef _hoops_ICAHH
/*********************************************************************\
 *
 *	_hoops_PGGIR
 *	_hoops_PGAA
 *	_hoops_IIS _hoops_HAS==_hoops_CRSRR, _hoops_PPR _hoops_ARGI==_hoops_CPSH, _hoops_PPR _hoops_CCAHH _hoops_HRGR _hoops_RH _hoops_PRISA _hoops_PIRA _hoops_IGIAR _hoops_RH _hoops_AGIS
 *	_hoops_PGGIR _hoops_HRGR _hoops_RH _hoops_SCAHH _hoops_IIGR _hoops_RH _hoops_CCIAH _hoops_API _hoops_IH _hoops_IRS _hoops_RAGA _hoops_GPHA _hoops_CRSRR
 *	_hoops_IH _hoops_IRS _hoops_RAGA _hoops_CPSH _hoops_IH _hoops_IRS _hoops_RAGA _hoops_PRISA _hoops_PIRA _hoops_GPP _hoops_RH _hoops_AGIS.  _hoops_HHIGR _hoops_HRGR
 *	_hoops_HRGR _hoops_GSAHH _hoops_RSAHH _hoops_IH _hoops_RH _hoops_HSPR _hoops_API:
 *	  _hoops_ASAHH,_hoops_ARGI (_hoops_CCAHH) = ((_hoops_CCAHH-_hoops_PSAHH) * _hoops_ASAHH,_hoops_ARGI-1 (_hoops_CCAHH))   (_hoops_PSAHH+_hoops_ARGI - _hoops_CCAHH) _hoops_ASAHH+1,_hoops_ARGI-1 (_hoops_CCAHH))
 *				  ----------------------- + --------------------------
 *					   _hoops_PSAHH+_hoops_ARGI-1 - _hoops_PSAHH			  _hoops_PSAHH+_hoops_ARGI - _hoops_PSAHH+_hoops_HAS
 *	_hoops_CCA _hoops_RH _hoops_AIRA _hoops_AGIR _hoops_PAPR _hoops_IH
 *	  _hoops_ASAHH,1 (_hoops_CCAHH) = 1 _hoops_CHGRR  (_hoops_CCAHH > _hoops_HSAHH[_hoops_HAS])&& (_hoops_CCAHH < _hoops_HSAHH[_hoops_HAS+1])
 *	  _hoops_ASAHH,1 (_hoops_CCAHH) = 0 _hoops_IAII
\*********************************************************************/
local double _hoops_HCRHH (int id, int degree, double _hoops_ISAHH, const float *_hoops_CSAHH) {
	double _hoops_SSAHH, _hoops_GGPHH, _hoops_RGPHH, _hoops_AGPHH, _hoops_PGPHH, _hoops_HGPHH;

	  /* _hoops_AIRA _hoops_AGIR _hoops_HCPA _hoops_PAGIR */
	if (degree == 1)
		if ((_hoops_ISAHH > _hoops_CSAHH[id])&& (_hoops_ISAHH <= _hoops_CSAHH[id+1]))
		  return 1.0;
		  else return 0.0;

	_hoops_SSAHH =  (_hoops_ISAHH - _hoops_CSAHH[id]) * _hoops_HCRHH (id, degree-1, _hoops_ISAHH, _hoops_CSAHH);
	_hoops_GGPHH =  (_hoops_CSAHH[id + degree] - _hoops_ISAHH) * _hoops_HCRHH (id+1, degree-1, _hoops_ISAHH, _hoops_CSAHH);
	_hoops_RGPHH = _hoops_CSAHH[id + degree - 1] - _hoops_CSAHH[id];
	_hoops_AGPHH = _hoops_CSAHH[id + degree] - _hoops_CSAHH[id+1];

	  /* _hoops_SRCH _hoops_GHAHH _hoops_HPP 0 */
	if (_hoops_RGPHH < _hoops_CACIR && _hoops_RGPHH > -_hoops_CACIR)
		_hoops_PGPHH = 0.0;
	else
		_hoops_PGPHH = _hoops_SSAHH / _hoops_RGPHH;

	if (_hoops_AGPHH < _hoops_CACIR && _hoops_AGPHH > -_hoops_CACIR)
		_hoops_HGPHH = 0.0;
	else
		_hoops_HGPHH = _hoops_GGPHH / _hoops_AGPHH;

	return _hoops_PGPHH + _hoops_HGPHH;
} /* _hoops_RSGR _hoops_API _hoops_PGGIR */

#else

/* _hoops_AIHH _hoops_IGPHH 2.1 _hoops_GPP _hoops_HSHIA 68 _hoops_IIGR "_hoops_IPCP _hoops_IRCPH _hoops_CGPHH", _hoops_SGPHH&_hoops_GRPHH, 2_hoops_GRSP _hoops_RRPHH */
local int _hoops_ARPHH (int n, int p, float _hoops_ISAHH, const float *_hoops_PRPHH) {
	int low, _hoops_SPGIR, high;

	if (_hoops_ISAHH >= _hoops_PRPHH[n+1])		// >= _hoops_RIIA _hoops_IIGR == _hoops_IS _hoops_ASSS _hoops_IH _hoops_AAHRP _hoops_HRPHH
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
}

/* _hoops_AIHH _hoops_IGPHH 2.2 _hoops_GPP _hoops_HSHIA 70 _hoops_IIGR "_hoops_IPCP _hoops_IRCPH _hoops_CGPHH", _hoops_SGPHH&_hoops_GRPHH, 2_hoops_GRSP _hoops_RRPHH */
local void _hoops_IRPHH (int i, float _hoops_ISAHH, int p, const float *_hoops_PRPHH, float *_hoops_PAGR) {
	int	 r, j;
	float _hoops_HPRS, temp;
	/* _hoops_CRPHH 16 _hoops_GGR _hoops_HSPR _hoops_III _hoops_IGIPR _hoops_SAIPR _hoops_IIGR _hoops_CPSH 16 _hoops_GPP _hoops_GRRC */
	float left[32], right[32];

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

#endif

/*********************************************************************\
 *	_hoops_GAPHH
 *	_hoops_CAHP _hoops_IRS _hoops_PPSR _hoops_GPP _hoops_RH _hoops_AGIS _hoops_IH _hoops_RH _hoops_RAGA _hoops_PRISA _hoops_PIRA, _hoops_CCAHH
 *	_hoops_PS _hoops_CSGA _hoops_RH _hoops_RAPHH _hoops_RGAR _hoops_CAS _hoops_SSIA _hoops_CHR _hoops_HAR _hoops_GICPR
 *	   _hoops_IS _hoops_SHH 0, (_hoops_HAS._hoops_IAS., _hoops_GIAA _hoops_RH _hoops_AGIS _hoops_ICSHR'_hoops_GRI _hoops_GCGH)
\*********************************************************************/
GLOBAL_FUNCTION void HI_Point_On_NURBS_Curve  (
		_hoops_PIRGR const *curve,
		float _hoops_ISAHH,
		Point *_hoops_PPHPA) {
	float _hoops_AAPHH[_hoops_HSRHH];
	float *_hoops_PAPHH;
	float _hoops_HAPHH;
	int j, start, end, _hoops_IAPHH;

	_hoops_IAPHH = curve->control_point_count + curve->degree + 1;
	if (_hoops_IAPHH > _hoops_HSRHH)
		ALLOC_ARRAY (_hoops_PAPHH, _hoops_IAPHH, float);
	else
		_hoops_PAPHH = _hoops_AAPHH;

#ifdef _hoops_ICAHH
	start = 0;
	end = curve->control_point_count;
	_hoops_HAPHH = 0;
	for	 (j = 0; j < curve->control_point_count; j++)
	{
		_hoops_PAPHH[j] = (float) _hoops_HCRHH (j, curve->degree + 1, _hoops_ISAHH, curve->knots);
		_hoops_PAPHH[j] *= curve->weights[j];
		_hoops_HAPHH += (float) fabs (_hoops_PAPHH[j]);
	}
	_hoops_GIAHH (start, end, curve->control_points, _hoops_PAPHH, _hoops_PPHPA);
#else
	start = _hoops_ARPHH (curve->control_point_count, curve->degree, _hoops_ISAHH, curve->knots);
	_hoops_IRPHH (start, _hoops_ISAHH, curve->degree, curve->knots, _hoops_PAPHH+start);
	end = _hoops_AHIA (_hoops_IAPHH-1, start + curve->degree + 1);
	if (curve->weights != _hoops_PSRHH) {
		_hoops_HAPHH = 0;
		for	 (j = start; j < end; j++)
		{
			_hoops_PAPHH[j] *= curve->weights[j-curve->degree];
			_hoops_HAPHH += (float) fabs (_hoops_PAPHH[j]);
		}
	}
	else {
		_hoops_HAPHH = 1;
	}
	_hoops_GIAHH (start, end, curve->control_points - curve->degree, _hoops_PAPHH, _hoops_PPHPA);
	/* _hoops_HPGIR _hoops_IIPR _hoops_PPSR _hoops_HPP _hoops_CAPHH _hoops_IS _hoops_HRSPA _hoops_PHCRA _hoops_IIGR _hoops_SAPHH */
	if (_hoops_HAPHH != 1)
		_hoops_AHAHH (_hoops_PPHPA, _hoops_HAPHH, _hoops_PPHPA);
#endif

	if (_hoops_PAPHH != _hoops_AAPHH)
		FREE_ARRAY (_hoops_PAPHH, _hoops_IAPHH, float);
} /* _hoops_RSGR _hoops_API _hoops_GPPHH */




/*********************************************************************\
 *	_hoops_RPPHH
 *	_hoops_RAR-_hoops_AAR _hoops_PHRSA _hoops_APPHH _hoops_IIGR _hoops_RH _hoops_PPPHH _hoops_AGIS
\*********************************************************************/
local void _hoops_HPPHH (
				_hoops_PIRGR const *curve,
				_hoops_HRPA const *matrix,
				Polyline *p,
				_hoops_PRAHH *_hoops_IRAHH,
				Point const *_hoops_AGAHH, Point const *_hoops_IGAHH,
				float u_left, float _hoops_HGAHH,
				int _hoops_IPPHH) {
	Point _hoops_CPPHH, _hoops_SPPHH;
	float _hoops_GHPHH = (u_left + _hoops_HGAHH) / 2.0f;

	_hoops_IPAHH (_hoops_AGAHH, _hoops_IGAHH, &_hoops_CPPHH);
	_hoops_AHAHH (&_hoops_CPPHH, 2.0f, &_hoops_CPPHH);

	HI_Point_On_NURBS_Curve (curve, _hoops_GHPHH, &_hoops_SPPHH);

	/* _hoops_RAR _hoops_AAR _hoops_SHPR-_hoops_GC _hoops_RHPHH */
	if ((_hoops_IPPHH > 0) && !_hoops_RPAHH (matrix, &_hoops_CPPHH, &_hoops_SPPHH))
	{
		_hoops_HPPHH (curve, matrix, p, _hoops_IRAHH, _hoops_AGAHH, &_hoops_SPPHH, u_left, _hoops_GHPHH, _hoops_IPPHH - 1);
		_hoops_PCAHH (&_hoops_SPPHH, p);
		_hoops_HPPHH (curve, matrix, p, _hoops_IRAHH, &_hoops_SPPHH, _hoops_IGAHH, _hoops_GHPHH, _hoops_HGAHH, _hoops_IPPHH - 1);
	}
	else
		_hoops_PCAHH (&_hoops_SPPHH, p);
} /* _hoops_RSGR _hoops_PHRSA _hoops_API _hoops_RPPHH */


/*********************************************************************\
 *	_hoops_SIHPA _hoops_PGPP
\*********************************************************************/
local void _hoops_AHPHH(_hoops_RRAHH *heap) {
	heap->allocated = 10;
	heap->used = 0;
	ALLOC_ARRAY (heap->array, heap->allocated, _hoops_RGAHH *);
}

local void _hoops_PHPHH(_hoops_RRAHH *heap) {
	FREE_ARRAY (heap->array, heap->allocated, _hoops_RGAHH *);
	heap->allocated = 0;
	heap->used = 0;
	heap->array = null;
}

local void swaph(_hoops_RRAHH *heap, int i, int j) {
	_hoops_RGAHH *tmp;
	tmp = heap->array[i];
	heap->array[i] = heap->array[j];
	heap->array[j] = tmp;
}

local void _hoops_HHPHH(_hoops_RRAHH *heap, int i) {
	int p = _hoops_PCAHP(i);

	while (i > 0)
	{
		if (heap->array[i]->priority > heap->array[p]->priority)
		{
			swaph(heap, i, p);
			i = p;
			p = _hoops_PCAHP(p);
		}
		else
			break;
	}
}

local void _hoops_IHPHH(_hoops_RRAHH *heap, int i) {
	int l = _hoops_HCAHP(i);
	int r = _hoops_ICAHP(i);
	int _hoops_PSAHP = i;
	int _hoops_HSAHP = i;

	while (l < heap->used)
	{
		if (heap->array[l]->priority > heap->array[_hoops_HSAHP]->priority)
			_hoops_PSAHP = l;
		if (r < heap->used)
			if (heap->array[r]->priority > heap->array[_hoops_PSAHP]->priority)
				_hoops_PSAHP = r;
		if (_hoops_PSAHP != _hoops_HSAHP)
		{
			swaph(heap, _hoops_HSAHP, _hoops_PSAHP);
			l = _hoops_HCAHP (_hoops_PSAHP);
			r = _hoops_ICAHP (_hoops_PSAHP);
			_hoops_HSAHP = _hoops_PSAHP;
		}
		else
			break;
	}
}


local void _hoops_CHPHH(
		_hoops_RRAHH *heap,
		_hoops_RGAHH *node)
{
	if (heap->allocated==heap->used) {
		_hoops_RGAHH **temp;

		heap->allocated *= 2;
		ALLOC_ARRAY (temp, heap->allocated, _hoops_RGAHH *);
		_hoops_AIGA (heap->array, heap->used, _hoops_RGAHH *, temp);
		FREE_ARRAY (heap->array, heap->used, _hoops_RGAHH *);
		heap->array = temp;
	}
	heap->used++;
	heap->array[ heap->used-1 ] = node;
	_hoops_HHPHH(heap, heap->used-1);
}



local void _hoops_SHPHH(
		_hoops_PIRGR const *curve,
		_hoops_RRAHH *heap,
		float left, float right)
{
	float _hoops_IGIGA = left + _hoops_SSRHH * (right - left);
	float _hoops_CGIGA = left + _hoops_GGAHH * (right - left);
	Point _hoops_GIPHH, _hoops_RIPHH;
	_hoops_PGAHH *_hoops_AIPHH;

	ALLOC (_hoops_AIPHH, _hoops_PGAHH);

	HI_Point_On_NURBS_Curve (curve, left + _hoops_CACIR, &_hoops_AIPHH->_hoops_AGAHH);
	HI_Point_On_NURBS_Curve (curve, _hoops_IGIGA, &_hoops_AIPHH->_hoops_CGAHH);
	HI_Point_On_NURBS_Curve (curve, _hoops_CGIGA, &_hoops_AIPHH->_hoops_SGAHH);
	HI_Point_On_NURBS_Curve (curve, right - _hoops_CACIR, &_hoops_AIPHH->_hoops_IGAHH);
	_hoops_AIPHH->u_left = left;
	_hoops_AIPHH->_hoops_HGAHH = right;
	_hoops_GIPHH.x = _hoops_AIPHH->_hoops_AGAHH.x * (1.0f-_hoops_SSRHH) + _hoops_AIPHH->_hoops_IGAHH.x * _hoops_SSRHH;
	_hoops_GIPHH.y = _hoops_AIPHH->_hoops_AGAHH.y * (1.0f-_hoops_SSRHH) + _hoops_AIPHH->_hoops_IGAHH.y * _hoops_SSRHH;
	_hoops_GIPHH.z = _hoops_AIPHH->_hoops_AGAHH.z * (1.0f-_hoops_SSRHH) + _hoops_AIPHH->_hoops_IGAHH.z * _hoops_SSRHH;
	_hoops_RIPHH.x = _hoops_AIPHH->_hoops_AGAHH.x * (1.0f-_hoops_GGAHH) + _hoops_AIPHH->_hoops_IGAHH.x * _hoops_GGAHH;
	_hoops_RIPHH.y = _hoops_AIPHH->_hoops_AGAHH.y * (1.0f-_hoops_GGAHH) + _hoops_AIPHH->_hoops_IGAHH.y * _hoops_GGAHH;
	_hoops_RIPHH.z = _hoops_AIPHH->_hoops_AGAHH.z * (1.0f-_hoops_GGAHH) + _hoops_AIPHH->_hoops_IGAHH.z * _hoops_GGAHH;
	_hoops_AIPHH->priority =
		Abs (_hoops_GIPHH.x - _hoops_AIPHH->_hoops_CGAHH.x) +
		Abs (_hoops_GIPHH.y - _hoops_AIPHH->_hoops_CGAHH.y) +
		Abs (_hoops_GIPHH.z - _hoops_AIPHH->_hoops_CGAHH.z) +
		Abs (_hoops_RIPHH.x - _hoops_AIPHH->_hoops_SGAHH.x) +
		Abs (_hoops_RIPHH.y - _hoops_AIPHH->_hoops_SGAHH.y) +
		Abs (_hoops_RIPHH.z - _hoops_AIPHH->_hoops_SGAHH.z);
	_hoops_CHPHH(heap, (_hoops_RGAHH *)_hoops_AIPHH);
}


local void _hoops_PIPHH (_hoops_RRAHH *heap, _hoops_RGAHH **node)
{
	if (heap->used > 1) {
		swaph(heap, 0, heap->used - 1);
		heap->used--;
		_hoops_IHPHH(heap, 0);
	}
	else if (heap->used == 1) {
		heap->used--;
	}
	else if (heap->used < 1) {
		return;
	}
	*node = heap->array[heap->used];
}

/* _hoops_IGISR _hoops_GGR _hoops_GIIS->_hoops_GHCP */
local void _hoops_HIPHH(_hoops_GRAHH *node)
{
	_hoops_GRAHH *next, *_hoops_IIPHH;
	Vector _hoops_CIPHH, _hoops_SIPHH;
	next = node->next;
	_hoops_IIPHH = next->next;
	_hoops_CIPHH.x = next->_hoops_AGAHH.x - node->_hoops_AGAHH.x;
	_hoops_CIPHH.y = next->_hoops_AGAHH.y - node->_hoops_AGAHH.y;
	_hoops_CIPHH.z = next->_hoops_AGAHH.z - node->_hoops_AGAHH.z;
	_hoops_SIPHH.x = _hoops_IIPHH->_hoops_AGAHH.x - next->_hoops_AGAHH.x;
	_hoops_SIPHH.y = _hoops_IIPHH->_hoops_AGAHH.y - next->_hoops_AGAHH.y;
	_hoops_SIPHH.z = _hoops_IIPHH->_hoops_AGAHH.z - next->_hoops_AGAHH.z;

	node->priority = HI_Compute_Vector_Angle(&_hoops_CIPHH, &_hoops_SIPHH);
}


/*********************************************************************\
 *	_hoops_GCPHH
 *	_hoops_RAR-_hoops_HIAGR _hoops_RGAP _hoops_IIGR _hoops_RH _hoops_RSSA _hoops_GPP _hoops_RH _hoops_PPPHH _hoops_AGIS
\*********************************************************************/
local void _hoops_RCPHH (
		_hoops_PIRGR const *curve,
		Polyline *p,
		float u_left, float _hoops_HGAHH,
		int _hoops_PPPI,
		float _hoops_IPPI,
		float _hoops_CPPI,
		float _hoops_SPPI)
{
	int i, count;
	float left, right, _hoops_IGIGA, _hoops_CGIGA;
	_hoops_RRAHH *_hoops_ACPHH = null;
	_hoops_PGAHH *_hoops_PCPHH;
	_hoops_GRAHH *head = null, *ptr, *prev;
	_hoops_RGAHH *node;

	if (_hoops_HGAHH - u_left < 2.0f * _hoops_CACIR) {
		/* _hoops_RH _hoops_AGIS _hoops_HRGR _hoops_HAH _hoops_RISA _hoops_IS _hoops_HIISR _hoops_CCA.  _hoops_GCGRA _hoops_SCH _hoops_CCA _hoops_IRS _hoops_RGCPR _hoops_III */
		p->allocated = p->count = 2;
		ALLOC_ARRAY (p->points, p->allocated, Point);
		left = u_left + _hoops_CACIR * (_hoops_HGAHH - u_left);
		right = _hoops_HGAHH - _hoops_CACIR * (_hoops_HGAHH - u_left);
		HI_Point_On_NURBS_Curve (curve, left, &p->points[0]);
		HI_Point_On_NURBS_Curve (curve, right, &p->points[1]);
		return;
	}

	/* _hoops_GHAA _hoops_HCPHH _hoops_PPR _hoops_ICPHH _hoops_ISCRH */
	if (_hoops_CPPI > 0 || (_hoops_SPPI > 0 && _hoops_SPPI < 1)) {
		_hoops_GRAHH *_hoops_CCPHH, *_hoops_SCPHH, *_hoops_GSPHH;
		_hoops_RRAHH *_hoops_RSPHH;
		bool _hoops_ASPHH;
		float _hoops_PSPHH;
		float _hoops_HSPHH = _hoops_IPPI * _hoops_IPPI;
		float u, _hoops_IRIAR;
		_hoops_GRAHH **_hoops_ASRGR;

		ALLOC (_hoops_RSPHH, _hoops_RRAHH);
		_hoops_AHPHH (_hoops_RSPHH);
		left = u_left + _hoops_CACIR;
		right = _hoops_HGAHH - _hoops_CACIR;
		count = curve->control_point_count + 3;
		_hoops_ASRGR = &head;
		u = left;
		_hoops_IRIAR = (right-left) / (count-1);
		for (i = 0; i < count; i++) {
			if (i == count-1)
				u = right;
			ALLOC (_hoops_CCPHH, _hoops_GRAHH);
			_hoops_CCPHH->u_left = u;
			HI_Point_On_NURBS_Curve (curve, _hoops_CCPHH->u_left, &_hoops_CCPHH->_hoops_AGAHH);
			_hoops_CCPHH->next = null;
			*_hoops_ASRGR = _hoops_CCPHH;
			_hoops_ASRGR = &_hoops_CCPHH->next;
			_hoops_CCPHH->priority = 0;
			u += _hoops_IRIAR;
		}
		if (_hoops_CPPI > 0) {
			_hoops_CCPHH = head;
			for (i = 0; i < count-2; i++) {
				_hoops_HIPHH (_hoops_CCPHH); /* _hoops_IGISR _hoops_GGR _hoops_ISPHH->_hoops_GHCP */
				_hoops_CHPHH (_hoops_RSPHH, (_hoops_RGAHH *)_hoops_CCPHH);
				_hoops_CCPHH = _hoops_CCPHH->next;
			}
			while (_hoops_RSPHH->used < _hoops_PPPI - 2) {
				_hoops_PIPHH(_hoops_RSPHH, &node);
				_hoops_SCPHH = (_hoops_GRAHH *) node;
				if (_hoops_SCPHH->priority < _hoops_CPPI)
					break;
				ALLOC (_hoops_GSPHH, _hoops_GRAHH);
				count++;
				left = _hoops_SCPHH->u_left;
				right = _hoops_SCPHH->next->next->u_left;
				_hoops_IGIGA = left + _hoops_SSRHH * (right - left);
				_hoops_CGIGA = left + _hoops_GGAHH * (right - left);
				HI_Point_On_NURBS_Curve (curve, _hoops_IGIGA, &_hoops_GSPHH->_hoops_AGAHH);
				HI_Point_On_NURBS_Curve (curve, _hoops_CGIGA, &_hoops_SCPHH->next->_hoops_AGAHH);
				_hoops_GSPHH->u_left = _hoops_IGIGA;
				_hoops_SCPHH->next->u_left = _hoops_CGIGA;
				/* _hoops_GSRGR _hoops_RH _hoops_CCAH _hoops_GIIS _hoops_GAPA _hoops_CSPHH _hoops_PPR _hoops_CSPHH->_hoops_SPS */
				_hoops_GSPHH->next = _hoops_SCPHH->next;
				_hoops_SCPHH->next = _hoops_GSPHH;
				_hoops_HIPHH (_hoops_SCPHH);
				_hoops_HIPHH (_hoops_GSPHH);
				_hoops_CHPHH (_hoops_RSPHH, (_hoops_RGAHH *)_hoops_SCPHH);
				_hoops_CHPHH (_hoops_RSPHH, (_hoops_RGAHH *)_hoops_GSPHH);
			}
		}
		if (_hoops_SPPI > 0 && _hoops_SPPI < 1) {
			ptr = head;
			do {
				while (ptr->next &&
					   (_hoops_RSPHH->used < _hoops_PPPI - 2) &&
					   (ptr->next->u_left - ptr->u_left > _hoops_SPPI))
				{
					ALLOC (_hoops_GSPHH, _hoops_GRAHH);
					count++;
					_hoops_GSPHH->u_left = (ptr->next->u_left + ptr->u_left) / 2;
					HI_Point_On_NURBS_Curve (curve, _hoops_GSPHH->u_left, &_hoops_GSPHH->_hoops_AGAHH);
					_hoops_GSPHH->next = ptr->next;
					ptr->next = _hoops_GSPHH;
				}
			} while ((ptr = ptr->next) != null);
		}
		_hoops_PHPHH(_hoops_RSPHH);
		FREE (_hoops_RSPHH, _hoops_RRAHH);

		_hoops_ASPHH = true;
		if (_hoops_IPPI > 0 && (count < _hoops_PPPI)) {
			/* _hoops_AA _hoops_IRS _hoops_HHCI _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RPP _hoops_SR _hoops_PAH _hoops_HSGR _hoops_IPAC _hoops_RH _hoops_AGIS
			   _hoops_ACSRR _hoops_RH _hoops_ARSAR _hoops_CIAS _hoops_GIHPA */
			for (ptr = head; ptr->next != null; ptr = ptr->next) {
				_hoops_PSPHH =
					Abs(ptr->_hoops_AGAHH.x - ptr->next->_hoops_AGAHH.x) +
					Abs(ptr->_hoops_AGAHH.y - ptr->next->_hoops_AGAHH.y) +
					Abs(ptr->_hoops_AGAHH.z - ptr->next->_hoops_AGAHH.z);
				if (_hoops_PSPHH > _hoops_IPPI) {
					Point _hoops_SPGIR, _hoops_SSPHH;
					Vector _hoops_ARGCR;

					_hoops_SPGIR.x = ptr->_hoops_AGAHH.x + ptr->next->_hoops_AGAHH.x;
					_hoops_SPGIR.y = ptr->_hoops_AGAHH.y + ptr->next->_hoops_AGAHH.y;
					_hoops_SPGIR.z = ptr->_hoops_AGAHH.z + ptr->next->_hoops_AGAHH.z;
					HI_Point_On_NURBS_Curve	 (curve, (ptr->u_left + ptr->next->u_left)/2, &_hoops_SSPHH);
					_hoops_ARGCR.x = _hoops_SPGIR.x - _hoops_SSPHH.x;
					_hoops_ARGCR.y = _hoops_SPGIR.y - _hoops_SSPHH.y;
					_hoops_ARGCR.z = _hoops_SPGIR.z - _hoops_SSPHH.z;
					if (_hoops_AIAHH(&_hoops_ARGCR) > _hoops_HSPHH) {
						_hoops_ASPHH = false;
						break;
					}
				}
			}
		}
		if (_hoops_ASPHH) {
			p->allocated = count;
			p->count = p->allocated;
			ALLOC_ARRAY (p->points, p->allocated, Point);
			ptr = head;
			i = 0;
			do {
				p->points[i].x = ptr->_hoops_AGAHH.x;
				p->points[i].y = ptr->_hoops_AGAHH.y;
				p->points[i].z = ptr->_hoops_AGAHH.z;
				prev = ptr;
				ptr = ptr->next;
				i++;
				FREE (prev, _hoops_GRAHH);
			} while (ptr != null);
			return;
		}
		else {
			ALLOC (_hoops_ACPHH, _hoops_RRAHH);
			_hoops_AHPHH (_hoops_ACPHH);
			ptr = head;
			do {
				if (ptr->next != null)
					_hoops_SHPHH (curve, _hoops_ACPHH, ptr->u_left, ptr->next->u_left);
				prev = ptr;
				ptr = ptr->next;
				FREE (prev, _hoops_GRAHH);
			} while (ptr != null);
		}
	}
	else {
		ALLOC (_hoops_ACPHH, _hoops_RRAHH);
		_hoops_AHPHH (_hoops_ACPHH);
		left = u_left + _hoops_CACIR;
		right = _hoops_HGAHH - _hoops_CACIR;
		_hoops_SHPHH(curve, _hoops_ACPHH, left, right);
	}

	while (_hoops_ACPHH->used < _hoops_PPPI - 2)
	{
		_hoops_PIPHH(_hoops_ACPHH, &node);
		if (node->priority < _hoops_IPPI) {
			/* _hoops_PPSI _hoops_SCH _hoops_ISSC, _hoops_PSCR _hoops_GGHHH _hoops_GGSR _hoops_IIGR _hoops_RH _hoops_HAPR.  _hoops_SR'_hoops_ASAR _hoops_CPHR */
			_hoops_CHPHH(_hoops_ACPHH, node);
			break;
		}
		else {
			_hoops_PCPHH = (_hoops_PGAHH *) node;
			_hoops_IGIGA = _hoops_PCPHH->u_left + _hoops_SSRHH * (_hoops_PCPHH->_hoops_HGAHH - _hoops_PCPHH->u_left);
			_hoops_CGIGA = _hoops_PCPHH->u_left + _hoops_GGAHH * (_hoops_PCPHH->_hoops_HGAHH - _hoops_PCPHH->u_left);
			_hoops_SHPHH(curve, _hoops_ACPHH, _hoops_PCPHH->u_left, _hoops_IGIGA);
			_hoops_SHPHH(curve, _hoops_ACPHH, _hoops_IGIGA, _hoops_CGIGA);
			_hoops_SHPHH(curve, _hoops_ACPHH, _hoops_CGIGA, _hoops_PCPHH->_hoops_HGAHH);
			FREE (_hoops_PCPHH, _hoops_PGAHH);
		}
	}

	/* _hoops_GHIS _hoops_RGHHH _hoops_HPP _hoops_IARGR _hoops_PIRA */
	quick_sort (_hoops_ACPHH, 0, _hoops_ACPHH->used - 1);
	/* _hoops_AGHR (_hoops_AGHHH (_hoops_PGHHH)); */

	p->allocated = _hoops_ACPHH->used+1;
	p->count = p->allocated;
	ALLOC_ARRAY (p->points, p->allocated, Point);
	p->points[_hoops_ACPHH->used] = ((_hoops_PGAHH *)_hoops_ACPHH->array[_hoops_ACPHH->used-1])->_hoops_IGAHH;
	for (i=0; i<_hoops_ACPHH->used; i++) {
		p->points[i] = _hoops_ACPHH->array[i]->_hoops_AGAHH;
		FREE (_hoops_ACPHH->array[i], _hoops_PGAHH);
	}

	_hoops_PHPHH (_hoops_ACPHH);
	FREE (_hoops_ACPHH, _hoops_RRAHH);

} /* _hoops_RSGR _hoops_GCPHH */

#endif

/*********************************************************************\
 *	_hoops_HGHHH
 *
 *	_hoops_RGR _hoops_PCPH _hoops_PAPRR _hoops_IRS _hoops_IRCPH _hoops_RHPHH.
 *
 *	**_hoops_IGHHH**: _hoops_SCH _hoops_HRGR _hoops_GH _hoops_IS _hoops_RH _hoops_RCPH _hoops_API _hoops_IS _hoops_CIH _hoops_RH
 *		_hoops_CRPR _hoops_SGS _hoops_HRGR _hoops_PSPP _hoops_GGR _hoops_CCAHR->_hoops_RSSA  !!!!
 *
\*********************************************************************/
GLOBAL_FUNCTION void HI_Generate_NURBS_Polyline	 (
		_hoops_PIRGR const *curve,
		_hoops_PARC const *control,
		_hoops_HRPA const *matrix,
		Polyline alter *p,
		float _hoops_CGHHH)
{
#ifndef _hoops_CCPIR
	int i, recursion_limit;
	float _hoops_SGHHH, _hoops_GRHHH, _hoops_RRHHH, _hoops_ARHHH, _hoops_PRHHH;
	Point _hoops_HIPCP;
	Point const *_hoops_HRHHH;
	float _hoops_ISAHH;
	const int _hoops_IRHHH = curve->control_point_count + curve->degree + 1;
	const int _hoops_CRHHH = curve->control_point_count - curve->degree;
	_hoops_PRAHH _hoops_IRAHH;
	int _hoops_SRHHH;
	_hoops_PIRGR *_hoops_ARCAR;
	Point _hoops_GAHHH;
	_hoops_PARC alter _hoops_RAHHH;

	if (control == null) {

		/* _hoops_ARP _hoops_GH _hoops_SHIR _hoops_HSH. */
		_hoops_RAHHH._hoops_PPPI = 512;
		_hoops_RAHHH._hoops_HPPI = 0;
		_hoops_RAHHH._hoops_IPPI = _hoops_CGHHH;
		_hoops_RAHHH._hoops_CPPI = 20; /* _hoops_HRGR _hoops_RGR _hoops_HAH _hoops_RIRA _hoops_IIGR _hoops_IRS _hoops_SHIR ? */
		_hoops_RAHHH._hoops_SPPI = 1;
		_hoops_RAHHH._hoops_SAR = false;

		control = &_hoops_RAHHH;
	}

	ZERO_STRUCT(p, Polyline);
	p->_hoops_HIHI = 1;
	p->type = _hoops_IIIP;
	p->_hoops_CPGPR = _hoops_PHSSR;

	/* _hoops_IRS _hoops_HHCI _hoops_IGHAR _hoops_AGIR _hoops_IH _hoops_CPSH 1, _hoops_GGR _hoops_PGAP _hoops_AGIR _hoops_RH _hoops_RGSHA _hoops_RSSA _hoops_AIAH _hoops_CHR
	 * _hoops_RH _hoops_ISII _hoops_RSSA _hoops_SGS _hoops_SR _hoops_HHGC _hoops_IS _hoops_IIPR */
	if (curve->degree == 1 &&
		curve->start_u < _hoops_CACIR &&
		curve->end_u > 1.0f - _hoops_CACIR) {
		p->allocated = p->count = curve->control_point_count;
		ALLOC_ARRAY (p->points, p->allocated, Point);
		_hoops_AIGA(curve->control_points, curve->control_point_count, Point, p->points);
		return;
	}

	/* _hoops_PHAA _hoops_IRHH _hoops_IRS _hoops_ICGR _hoops_IPS (_hoops_AAHHH).  _hoops_PS _hoops_GRS _hoops_CHASA _hoops_HHH _hoops_IIGR _hoops_RH _hoops_AIRP _hoops_SPHR _hoops_RPP _hoops_HAHH */
	ALLOC(_hoops_ARCAR, _hoops_PIRGR);
	_hoops_RSAI (curve, _hoops_PIRGR, _hoops_ARCAR);
	_hoops_GAHHH = curve->control_points[0];
	_hoops_RIAHH(curve->control_points, &_hoops_GAHHH, curve->control_point_count);

	recursion_limit = _hoops_ISRHH;

	p->count = 0;
	p->allocated = 0;
	p->points = null;

	/* _hoops_RCRP _hoops_SHIR _hoops_HSH _hoops_IS _hoops_RH _hoops_SGHSA _hoops_PPR _hoops_HHRP _hoops_RPP _hoops_SSIA _hoops_AAPR _hoops_PAHHH _hoops_IRAP */
	if (!curve->knots) {
		if (_hoops_IRHHH > (int)(sizeof (_hoops_ASRHH) / 4))
		{
			float *_hoops_HAHHH;
			ALLOC_ARRAY (_hoops_HAHHH, _hoops_IRHHH, float);
			for (i = 0; i < _hoops_IRHHH; i++)
				_hoops_HAHHH[i] = (float)i;
			_hoops_ARCAR->knots = _hoops_HAHHH;
		}
		else
			/* _hoops_IAHHH _hoops_IRS _hoops_RSCA _hoops_ARI _hoops_IS _hoops_CAHHH _hoops_SCH _hoops_CRGR _hoops_SAHHH, _hoops_HIH _hoops_SR _hoops_PPPPR'_hoops_RA _hoops_CIPAA _hoops_SCH.  _hoops_PS _hoops_GPHHH! */
			_hoops_ARCAR->knots = (float alter *) _hoops_ASRHH;
	}
	if (!curve->weights) {
		if (_hoops_ARCAR->control_point_count > (int)(sizeof (_hoops_PSRHH) / 4))
		{
			float *_hoops_HAHHH;
			ALLOC_ARRAY (_hoops_HAHHH, _hoops_ARCAR->control_point_count, float);
			for (i = 0; i < _hoops_ARCAR->control_point_count; i++)
				_hoops_HAHHH[i] = 1.0f;
			_hoops_ARCAR->weights = _hoops_HAHHH;
		}
		else
			/* _hoops_IAHHH _hoops_IRS _hoops_RSCA _hoops_ARI _hoops_IS _hoops_CAHHH _hoops_SCH _hoops_CRGR _hoops_SAHHH, _hoops_HIH _hoops_SR _hoops_PPPPR'_hoops_RA _hoops_CIPAA _hoops_SCH.  _hoops_PS _hoops_GPHHH! */
			_hoops_ARCAR->weights = (float alter *) _hoops_PSRHH;
	}

	/* _hoops_CAHA _hoops_GGSR _hoops_RH _hoops_HSPP _hoops_PPR _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_GRRC, _hoops_IPSH _hoops_RH _hoops_CIGS _hoops_RPHHH */
	_hoops_SGHHH = _hoops_ARCAR->knots[_hoops_ARCAR->degree];
	_hoops_GRHHH = _hoops_ARCAR->knots[_hoops_ARCAR->control_point_count];
	_hoops_PRHHH = (_hoops_GRHHH - _hoops_SGHHH) / (2.0f * (_hoops_ARCAR->control_point_count - _hoops_ARCAR->degree));
	if (_hoops_GRHHH < _hoops_SGHHH)
		return;
	if (curve->start_u > 0)
		_hoops_RRHHH = _hoops_IAAA (_hoops_SGHHH, _hoops_SGHHH + ((_hoops_GRHHH - _hoops_SGHHH) * curve->start_u));
	else
		_hoops_RRHHH = _hoops_SGHHH;
	if (curve->end_u < 1)
		_hoops_ARHHH = _hoops_AHIA (_hoops_GRHHH, _hoops_SGHHH + ((_hoops_GRHHH - _hoops_SGHHH) * curve->end_u));
	else
		_hoops_ARHHH = _hoops_GRHHH;
	_hoops_SGHHH = _hoops_RRHHH;
	_hoops_GRHHH = _hoops_ARHHH;

	ALLOC_ARRAY (_hoops_IRAHH.data, 50, float);
	_hoops_IRAHH.allocated = 50;
	_hoops_IRAHH.used = 0;

	if (_hoops_SGHHH + 2*_hoops_CACIR > _hoops_GRHHH) {
		/* _hoops_GRH _hoops_PRCA _hoops_RPP _hoops_RH _hoops_AGIS _hoops_PRCGH _hoops_HRGR **_hoops_APHHH** _hoops_ICHRR */
		float u_left, _hoops_HGAHH;

		u_left = (2*_hoops_SGHHH + _hoops_GRHHH) / 3;
		if (u_left < _hoops_SGHHH)
			u_left = _hoops_SGHHH;
		_hoops_HGAHH = (_hoops_SGHHH + 2*_hoops_GRHHH) / 3;
		if (_hoops_HGAHH > _hoops_GRHHH)
			_hoops_HGAHH = _hoops_GRHHH;

		p->allocated = 2;
		ALLOC_ARRAY (p->points, p->allocated, Point);
		HI_Point_On_NURBS_Curve	 (_hoops_ARCAR, u_left, &_hoops_HIPCP);
		_hoops_PCAHH (&_hoops_HIPCP, p);
		HI_Point_On_NURBS_Curve	 (_hoops_ARCAR, _hoops_HGAHH, &_hoops_HIPCP);
		_hoops_PCAHH (&_hoops_HIPCP, p);
	}
	else if (control->_hoops_SAR) {
		/* _hoops_CCPP _hoops_PCCP _hoops_CIGS _hoops_SSAI _hoops_IIGR _hoops_RSSA _hoops_IH _hoops_RH _hoops_IIPR (_hoops_SR'_hoops_GCPP _hoops_PCCS _hoops_SPHR _hoops_RPP _hoops_HAHH) */
		p->allocated = 256;
		ALLOC_ARRAY (p->points, p->allocated, Point);

		  /* _hoops_RGHH _hoops_RH _hoops_SRS _hoops_AGIS _hoops_GPHA */
		HI_Point_On_NURBS_Curve	 (_hoops_ARCAR, _hoops_SGHHH + _hoops_CACIR, &_hoops_HIPCP);

		_hoops_HRAHH (&_hoops_IRAHH, _hoops_IACIR);
		_hoops_PCAHH (&_hoops_HIPCP, p);

		  /* _hoops_RGHH _hoops_RH _hoops_IRGP _hoops_AGIS _hoops_GIHA */
		for	 (_hoops_ISAHH = _hoops_SGHHH + _hoops_PRHHH; _hoops_ISAHH < _hoops_GRHHH; _hoops_ISAHH += _hoops_PRHHH)
		{
			_hoops_HRHHH = &p->points[(p->count-1)];
			HI_Point_On_NURBS_Curve	 (_hoops_ARCAR, _hoops_ISAHH, &_hoops_HIPCP);
			_hoops_HPPHH (_hoops_ARCAR, matrix, p, &_hoops_IRAHH, _hoops_HRHHH, &_hoops_HIPCP, _hoops_ISAHH - _hoops_PRHHH, _hoops_ISAHH, recursion_limit);
			_hoops_HRAHH (&_hoops_IRAHH, _hoops_IACIR);
			_hoops_PCAHH (&_hoops_HIPCP, p);
		}

		  /*_hoops_RGHH _hoops_RH _hoops_CGHI _hoops_AGIS _hoops_GPHA */
		_hoops_HRHHH = &p->points[(p->count-1)];
		HI_Point_On_NURBS_Curve	 (_hoops_ARCAR, _hoops_GRHHH - _hoops_CACIR, &_hoops_HIPCP);
		_hoops_HPPHH (_hoops_ARCAR, matrix, p, &_hoops_IRAHH, _hoops_HRHHH, &_hoops_HIPCP, _hoops_ISAHH - _hoops_PRHHH, _hoops_GRHHH - _hoops_CACIR, recursion_limit);
		_hoops_HRAHH (&_hoops_IRAHH, _hoops_IACIR);
		_hoops_PCAHH (&_hoops_HIPCP, p);
	}
	else {
		_hoops_SRHHH = control->_hoops_PPPI;
		_hoops_SRHHH += (_hoops_CRHHH-1) * control->_hoops_HPPI;
		_hoops_RCPHH (_hoops_ARCAR, p,
			_hoops_SGHHH, _hoops_GRHHH,
			_hoops_SRHHH, control->_hoops_IPPI,
			control->_hoops_CPPI, control->_hoops_SPPI);
	}

	/* _hoops_RPP _hoops_RH _hoops_PPHHH _hoops_SGHSA _hoops_PPR _hoops_HHRP _hoops_AAPR _hoops_IRAP, _hoops_PPR _hoops_RH _hoops_AGIS _hoops_CSAP _hoops_HAH _hoops_AHSC,
	 * _hoops_SR _hoops_RIAGR _hoops_IS _hoops_CCPP _hoops_AH _hoops_SIRGR _hoops_IS _hoops_CRCC _hoops_SHIR _hoops_HSH */
	if (!curve->knots) {
		if (_hoops_IRHHH > (int)(sizeof (_hoops_ASRHH) / 4))
			FREE_ARRAY (_hoops_ARCAR->knots, _hoops_IRHHH, float);
	}
	if (!curve->weights) {
		if (_hoops_ARCAR->control_point_count > (int)(sizeof (_hoops_PSRHH) / 4))
			FREE_ARRAY (_hoops_ARCAR->weights, _hoops_ARCAR->control_point_count, float);
	}
	FREE_ARRAY (_hoops_IRAHH.data, _hoops_IRAHH.allocated, float);
	FREE(_hoops_ARCAR, _hoops_PIRGR);
	_hoops_CPAHH(curve->control_points, &_hoops_GAHHH, curve->control_point_count);
	_hoops_CPAHH(p->points, &_hoops_GAHHH, p->count);

#endif
} /* _hoops_RSGR _hoops_API _hoops_HGHHH */


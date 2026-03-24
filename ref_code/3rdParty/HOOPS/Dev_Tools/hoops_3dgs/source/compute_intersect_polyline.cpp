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
 * $Id: obf_tmp.txt 1.75 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "hpserror.h"

#ifndef _hoops_SSAPA

#include "hc_proto.h"
#include "hi_proto.h"
#include "hd_proto.h"
#include "adt.h"
#include "csutil.h"



#ifndef _hoops_CACIR
# define _hoops_CACIR (1e-5f)
#endif

struct _hoops_GGPPA {
	Point start;
	Point end;
};

typedef VArray<_hoops_GGPPA *> _hoops_RGPPA;

struct _hoops_AGPPA {
	Point const *		points1;
	const int *			face_list1;
	VBSP *				_hoops_PGPPA;
	Point const *		points2;
	const int *			face_list2;
	VBSP *				_hoops_HGPPA;
	_hoops_RGPPA *	_hoops_PICHR;
	int					_hoops_IGPPA;
	bool				_hoops_CGPPA;
};

struct _hoops_SGPPA {
	int			_hoops_GRPPA;
	int			polyline_count;
	int *		polyline_lengths;
	int			_hoops_RRPPA;
	Point *		polyline_points;
};



/* _hoops_SAHR _hoops_PIHHR _hoops_IRS _hoops_ARGHR _hoops_IIGR _hoops_CIPH _hoops_GIRP */
#define _hoops_ARPPA() \
 (\
   point_count1 ^ \
   (point_count2<<4) ^ \
   (face_list_length1 << 8) ^ \
   (face_list_length2 << 12) ^\
   ((POINTER_SIZED_INT)(points1)) ^\
   ((POINTER_SIZED_INT)(points2)) ^\
   ((POINTER_SIZED_INT)(face_list1)) ^\
   ((POINTER_SIZED_INT)(face_list2)) ^\
   (*(const int *)(&points1[0].x)) ^\
   (*(const int *)(&points1[0].y)>>2) ^\
   (*(const int *)(&points1[0].z)>>4) ^\
   (*(const int *)(&points2[0].x)>>6) ^\
   (*(const int *)(&points2[0].y)>>8) ^\
   (*(const int *)(&points2[0].z)>>10)\
)



local void _hoops_PRPPA(
	Point *			line,
	Point const *	points1, 
	int				_hoops_HRPPA,
	const int *		_hoops_AIIPR,
	_hoops_ARPA const *	_hoops_IRPPA,
	_hoops_ARPA const *	_hoops_CRPPA)
{	
	bool in = false;

	/* _hoops_RGR _hoops_SRS _hoops_HAPR _hoops_HRGR _hoops_RGAR _hoops_IS _hoops_CAHA _hoops_GGSR _hoops_PGAP _hoops_PPAP _hoops_IIGR _hoops_RH _hoops_SRPPA _hoops_SR _hoops_CGH _hoops_IAIC _hoops_IS _hoops_SHH "_hoops_GGR" */
	for (int i = 0; i < _hoops_HRPPA; i++) {	 

		Point const * _hoops_GAPPA = &points1[_hoops_AIIPR[i]];
		Point const * _hoops_RAPPA; 
		if (i+1 < _hoops_HRPPA)
			_hoops_RAPPA = &points1[_hoops_AIIPR[i+1]];
		else
			_hoops_RAPPA = &points1[_hoops_AIIPR[i+1-_hoops_HRPPA]]; /* _hoops_ARGAR _hoops_AARI */

		Vector _hoops_ARGCR = *_hoops_RAPPA - *_hoops_GAPPA;

		_hoops_ARPA _hoops_AAPPA;

		bool status = HI_Normalize(&_hoops_ARGCR);
		HI_Compute_Cross_Product (&_hoops_ARGCR, (Vector const *)_hoops_IRPPA, (Vector *)&_hoops_AAPPA);
		if (!HI_Normalize ((Vector*)&_hoops_AAPPA))
			status = false;

		if (!status)
			continue;

		/* _hoops_GHGP _hoops_IHSR _hoops_HRGR -(_hoops_PAPPA + _hoops_HPP + _hoops_IIHCR) */
		_hoops_AAPPA.d = -(_hoops_RAPPA->x*_hoops_AAPPA.a + _hoops_RAPPA->y*_hoops_AAPPA.b + _hoops_RAPPA->z*_hoops_AAPPA.c);

		/* _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA _hoops_RPP _hoops_RH _hoops_HSP _hoops_HRGR _hoops_SRGGA _hoops_PAR _hoops_HAPPA, _hoops_HIH _hoops_SR
		 * _hoops_PAH _hoops_HPCAR _hoops_SGS _hoops_RH 3_hoops_IAPPA _hoops_PPSR _hoops_HRGR "_hoops_GGR", _hoops_HIS _hoops_SR _hoops_SAHR _hoops_PHHR _hoops_HPP _hoops_SGS. _hoops_PS _hoops_PAH _hoops_HGCR
		 * _hoops_SGGR _hoops_CCA _hoops_GHGA _hoops_RGR _hoops_RGAR _hoops_ARR, _hoops_PGGA "_hoops_GGR" _hoops_GRS _hoops_SHH _hoops_RH _hoops_PSHR _hoops_IH _hoops_HCR _hoops_SPPR*/
		Point const * _hoops_CAPPA; 
		if (i+2 < _hoops_HRPPA)
			_hoops_CAPPA = &points1[_hoops_AIIPR[i+2]];
		else
			_hoops_CAPPA = &points1[_hoops_AIIPR[i+2-_hoops_HRPPA]]; /* _hoops_ARGAR _hoops_AARI */

		in = _hoops_AAPPA * *_hoops_CAPPA > 0;

		break;
	}
	
	/* _hoops_RGR _hoops_SPS _hoops_HAPR _hoops_SAPPA _hoops_RH _hoops_III _hoops_IS _hoops_RH _hoops_SRPPA _hoops_PAPR _hoops_HPP _hoops_RH _hoops_GPPPA _hoops_HSSP'_hoops_GRI _hoops_SPPR */
	Point * _hoops_RPPPA = &line[0];
	Point * _hoops_APPPA = &line[1];

	for (int i = 0; i < _hoops_HRPPA; i++) {

		Point const * _hoops_GAPPA = &points1[_hoops_AIIPR[i]];
		Point const * _hoops_RAPPA; 

		if (i+1 < _hoops_HRPPA)
			_hoops_RAPPA = &points1[_hoops_AIIPR[i+1]];
		else
			_hoops_RAPPA = &points1[_hoops_AIIPR[i+1-_hoops_HRPPA]]; /* _hoops_ARGAR _hoops_AARI */

		/* _hoops_RPP _hoops_GIPR _hoops_RSSA _hoops_IIGR _hoops_RH _hoops_SCGR _hoops_ISHA _hoops_CHR _hoops_GPP _hoops_RH _hoops_PSHR _hoops_PPAP _hoops_IIGR _hoops_PPPPA, _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_GPIHR */
		if ((*_hoops_CRPPA * *_hoops_GAPPA > 0) == (_hoops_RAPPA, *_hoops_CRPPA * *_hoops_RAPPA > 0))
			continue;

		Vector _hoops_ARGCR = *_hoops_RAPPA - *_hoops_GAPPA;

		_hoops_ARPA _hoops_AAPPA;

		bool status = HI_Normalize(&_hoops_ARGCR);
		HI_Compute_Cross_Product (&_hoops_ARGCR, (Vector *)_hoops_IRPPA, (Vector *)&_hoops_AAPPA);
		if (!HI_Normalize ((Vector*)&_hoops_AAPPA))
			status = false;

		if (!status)
			continue;

		/* _hoops_GRAS _hoops_GHGP. _hoops_HPPPA _hoops_IH _hoops_GHGP _hoops_IHSR _hoops_HRGR -(_hoops_PAPPA + _hoops_HPP + _hoops_IIHCR) */
		_hoops_AAPPA.d = -(_hoops_RAPPA->x*_hoops_AAPPA.a + _hoops_RAPPA->y*_hoops_AAPPA.b + _hoops_RAPPA->z*_hoops_AAPPA.c);

		if ((_hoops_AAPPA * *_hoops_RPPPA > 0) != in)
			_hoops_IPPPA (_hoops_RPPPA, _hoops_APPPA, &_hoops_AAPPA, _hoops_RPPPA);

		if ((_hoops_AAPPA * *_hoops_APPPA > 0) != in)
			_hoops_IPPPA (_hoops_RPPPA, _hoops_APPPA, &_hoops_AAPPA, _hoops_APPPA);
	}
} 


local bool _hoops_CPPPA (
	Point const *	points1, 
	int				_hoops_HRPPA,
	const int *		_hoops_AIIPR,
	_hoops_ARPA const *	_hoops_IRPPA,
	Point const *	points2,
	int				_hoops_SPPPA,
	const int *		_hoops_HIIPR,
	_hoops_ARPA const *	_hoops_CRPPA,
	Point alter *	_hoops_GHPPA) 
{
	Point alter * _hoops_RHPPA = &_hoops_GHPPA[0];
	Point alter * _hoops_AHPPA = &_hoops_RHPPA[2];

	Point const * prev = &points2[_hoops_HIIPR[0]];

	bool _hoops_PHPPA = (*_hoops_IRPPA * *prev > 0);

	bool in  = false;

	for (int i = 0; i < _hoops_SPPPA; i++) { 

		Point const *	pt;

		if (i+1 < _hoops_SPPPA)
			pt = points2 + _hoops_HIIPR[i+1];
		else
			pt = points2 + _hoops_HIIPR[i+1-_hoops_SPPPA]; /* _hoops_ARGAR _hoops_AARI */

		in = (*_hoops_IRPPA * *pt > 0);

		if (in != _hoops_PHPPA) {
			_hoops_IPPPA (pt, prev, _hoops_IRPPA, _hoops_RHPPA);
			_hoops_RHPPA++;
			if (_hoops_RHPPA >= _hoops_AHPPA)
				break;
		}

		prev = pt;
		_hoops_PHPPA = in;
	}

	/* _hoops_HA _hoops_SR _hoops_HS _hoops_RH _hoops_III _hoops_CAGH (_hoops_RPP _hoops_SCH _hoops_HICP) */
	if (_hoops_RHPPA < _hoops_AHPPA)
		/* _hoops_HHPPA, _hoops_APSH _hoops_PII _hoops_SR _hoops_SARS'_hoops_RA _hoops_RHHR _hoops_RH _hoops_IPPA _hoops_HPGR _hoops_HCR (_hoops_IHPPA, _hoops_PSP _hoops_RASAR) */
		return false;  

	_hoops_PRPPA (_hoops_GHPPA, points1, _hoops_HRPPA, _hoops_AIIPR, _hoops_IRPPA, _hoops_CRPPA);

	return true;
}


local void _hoops_CHPPA(
	_hoops_AGPPA *	info, 
	_hoops_SHPPA *						_hoops_AIIPR, 
	_hoops_SHPPA *						_hoops_HIIPR) 
{
	info->_hoops_IGPPA++;
	if (info->_hoops_PICHR != null) {
		_hoops_GGPPA *node;

		ALLOC(node, _hoops_GGPPA);
		if (_hoops_CPPPA (
			info->points1, _hoops_AIIPR->len, _hoops_AIIPR->_hoops_GIPPA, &_hoops_AIIPR->plane, 
			info->points2, _hoops_HIIPR->len, _hoops_HIIPR->_hoops_GIPPA, &_hoops_HIIPR->plane,
			&node->start))
			info->_hoops_PICHR->Append(node);
		else
			FREE(node, _hoops_GGPPA);
	}
}


local _hoops_CSCAR _hoops_RIPPA(void *ptr, void *_hoops_AIPPA, void *_hoops_PIPPA)
{
	_hoops_AGPPA *info = (_hoops_AGPPA *)ptr;
	_hoops_SHPPA *_hoops_AIIPR = (_hoops_SHPPA *)_hoops_AIPPA;
	_hoops_SHPPA *_hoops_HIIPR = (_hoops_SHPPA *)_hoops_PIPPA;

	if (!_hoops_HIPPA (info->points1, _hoops_AIIPR->len, _hoops_AIIPR->_hoops_GIPPA, _hoops_HIIPR->plane)) {
		return VBSP_STATUS_CONTINUE;
	}
	else {

		if (!_hoops_HIPPA (info->points2, _hoops_HIIPR->len, _hoops_HIIPR->_hoops_GIPPA, _hoops_AIIPR->plane))
			return VBSP_STATUS_CONTINUE;

		if (!_hoops_AIIPR->bbox._hoops_RPCIR(_hoops_HIIPR->bbox))
			return VBSP_STATUS_CONTINUE;

		if (!_hoops_IIPPA (
								info->points1, 
								_hoops_AIIPR->len,
								_hoops_AIIPR->_hoops_GIPPA,
								&_hoops_AIIPR->plane, 
								info->points2, 
								_hoops_HIIPR->len,
								_hoops_HIIPR->_hoops_GIPPA,
								&_hoops_HIIPR->plane,
								null))
			return VBSP_STATUS_CONTINUE;

		_hoops_CHPPA (info, _hoops_AIIPR, _hoops_HIIPR);
	}

	if (info->_hoops_CGPPA)
		return VBSP_STATUS_STOP;
	else
		return VBSP_STATUS_CONTINUE;
}


/* _hoops_CSGA _hoops_IASC _hoops_AHCRR _hoops_IIGR _hoops_HCR _hoops_RH _hoops_RSSA _hoops_GGR _hoops_RH _hoops_III _hoops_SGHC,
 * _hoops_PPR _hoops_IIS _hoops_RH _hoops_AAHP _hoops_SHH _hoops_IRS _hoops_SRSR _hoops_CIPPA _hoops_IIGR _hoops_RH _hoops_CPIS _hoops_SPIS */
local float _hoops_SIPPA(_hoops_RGPPA *_hoops_GCPPA) 
{
	if (!_hoops_GCPPA->Count())
		return 0;

	_hoops_SASC	bbox;

	for (int i = 0; i < _hoops_GCPPA->Count(); i++) {
		_hoops_GGPPA * line = (*_hoops_GCPPA)[i];
		bbox.Merge(1, &line->start); 
		bbox.Merge(1, &line->end); 
	}

	Vector	_hoops_ARGCR = bbox.max - bbox.min;

	return _hoops_IAAA(_hoops_ARGCR.x, _hoops_ARGCR.y, _hoops_ARGCR.z);
}


typedef VList<_hoops_GGPPA *> _hoops_RCPPA;
typedef VList<_hoops_RCPPA *> _hoops_ACPPA;

#define _hoops_PCPPA 0
#define _hoops_HPHGA 1
#define _hoops_IPHGA		2
#define _hoops_CPHGA	3
#define _hoops_SPHGA	4

local bool _hoops_GHHGA (_hoops_RCPPA *_hoops_RHHGA, _hoops_ACPPA *_hoops_AHHGA, float tolerance)
{
	_hoops_RCPPA *_hoops_HHHGA;
	_hoops_GGPPA *_hoops_IHHGA, *_hoops_CHHGA, *_hoops_SHHGA, *_hoops_GIHGA, *line;
	float _hoops_RIHGA = (tolerance * tolerance);
	float _hoops_ARGCR, _hoops_HCPPA;
	int _hoops_PIHGA = -1;
	int _hoops_HIHGA, i;
	int _hoops_IIHGA = _hoops_PCPPA;

	_hoops_IHHGA = _hoops_RHHGA->PeekFirst();
	_hoops_CHHGA = _hoops_RHHGA->PeekLast();

	_hoops_HIHGA = _hoops_AHHGA->Count();
	_hoops_AHHGA->ResetCursor();

	for (i = 0; i < _hoops_HIHGA; i++) {

		/* _hoops_HGCR _hoops_IRS _hoops_SIHGA */
		_hoops_HHHGA = _hoops_AHHGA->PeekCursor();

		_hoops_SHHGA = _hoops_HHHGA->PeekFirst();
		_hoops_GIHGA = _hoops_HHHGA->PeekLast();

		_hoops_ARGCR = (_hoops_IHHGA->start - _hoops_SHHGA->start)._hoops_PPSSR();	/* _hoops_HSPP _hoops_HSPP */
		if (_hoops_ARGCR < _hoops_RIHGA) {
			_hoops_PIHGA = i;
			_hoops_RIHGA = _hoops_ARGCR;
			_hoops_IIHGA = _hoops_HPHGA;
		}
		_hoops_ARGCR = (_hoops_CHHGA->end - _hoops_GIHGA->end)._hoops_PPSSR();			/* _hoops_RSGR _hoops_RSGR */
		if (_hoops_ARGCR < _hoops_RIHGA) {
			_hoops_PIHGA = i;
			_hoops_RIHGA = _hoops_ARGCR;
			_hoops_IIHGA = _hoops_IPHGA;
		}
		_hoops_ARGCR = (_hoops_CHHGA->end - _hoops_SHHGA->start)._hoops_PPSSR();				/* _hoops_RSGR _hoops_HSPP */
		if (_hoops_ARGCR < _hoops_RIHGA) {
			_hoops_PIHGA = i;
			_hoops_RIHGA = _hoops_ARGCR;
			_hoops_IIHGA = _hoops_CPHGA;
		}
		_hoops_ARGCR = (_hoops_IHHGA->start - _hoops_GIHGA->end)._hoops_PPSSR();		/* _hoops_HSPP _hoops_RSGR */
		if (_hoops_ARGCR < _hoops_RIHGA) {
			_hoops_PIHGA = i;
			_hoops_RIHGA = _hoops_ARGCR;
			_hoops_IIHGA = _hoops_SPHGA;
		}
		/* _hoops_GCHGA _hoops_IS _hoops_RH _hoops_SPS _hoops_SIHGA */
		_hoops_AHHGA->AdvanceCursor();
	}
	/* _hoops_HCHGA _hoops_RSIH _hoops_RPP _hoops_ISAP _hoops_SIHRR */
	if (_hoops_PIHGA == -1)
		return false;

	/* _hoops_ICPPA _hoops_RPP _hoops_RH _hoops_ISII _hoops_CSAP _hoops_AIAH _hoops_CAHC */
	_hoops_HCPPA = (_hoops_IHHGA->start - _hoops_CHHGA->end)._hoops_PPSSR();
	if ((_hoops_IHHGA != _hoops_CHHGA) && (_hoops_HCPPA < _hoops_RIHGA))
		return false;

	/* _hoops_ASAR-_hoops_CCHGA _hoops_RH _hoops_AAH _hoops_SIHRR _hoops_HII _hoops_RH _hoops_SIHGA _hoops_HIGR */
	_hoops_HHHGA = _hoops_AHHGA->NthItem(_hoops_PIHGA);

	/* _hoops_RPP _hoops_IIH _hoops_CHR _hoops_RRI _hoops_HSAR _hoops_SAHR _hoops_IRS _hoops_CIAGR _hoops_III _hoops_SGHC _hoops_GGR _hoops_RH _hoops_SIHGA, _hoops_CACH _hoops_RPP 
	 * _hoops_SCH _hoops_ICHGA _hoops_ACAS _hoops_IS _hoops_IRS _hoops_PHPA _hoops_GPPS _hoops_HSAR _hoops_RH _hoops_PSSP _hoops_SR _hoops_GSGI.	*/
	if (_hoops_HHHGA->Count() > 3) {
		_hoops_SHHGA = _hoops_HHHGA->PeekFirst();
		_hoops_GIHGA = _hoops_HHHGA->PeekLast();
		if ((_hoops_SHHGA->start - _hoops_GIHGA->end)._hoops_PPSSR() < _hoops_RIHGA)
			return false; /* _hoops_RH _hoops_SIHGA _hoops_CSAP _hoops_AIAH _hoops_CAHC */
	}

	switch (_hoops_IIHGA) {
		case _hoops_HPHGA:
			while ((line = _hoops_RHHGA->RemoveFirst()) != null) {
				Swap (line->start, line->end);
				_hoops_HHHGA->AddFirst(line);
			}
		break;
		case _hoops_IPHGA:
			_hoops_RHHGA->Reverse();
			while ((line = _hoops_RHHGA->RemoveFirst()) != null) {
				Swap (line->start, line->end);
				_hoops_HHHGA->AddLast(line);
			}
		break;
		case _hoops_CPHGA:
			_hoops_RHHGA->Reverse();
			while ((line = _hoops_RHHGA->RemoveFirst()) != null) {
				_hoops_HHHGA->AddFirst(line);
			}
		break;
		case _hoops_SPHGA:
			while ((line = _hoops_RHHGA->RemoveFirst()) != null) {
				_hoops_HHHGA->AddLast(line);
			}
		break;
		default:
			/* _hoops_RGR _hoops_CGH _hoops_IIP _hoops_IHPS -- _hoops_RPP _hoops_ISAP _hoops_RIAGR _hoops_SIHRR, _hoops_SR _hoops_CGH _hoops_HS
			 * _hoops_AIAH _hoops_SCHGA */
			return false;
	}

	delete _hoops_RHHGA;
	_hoops_RHHGA = null;

	return true;

} /* _hoops_RSGR _hoops_API _hoops_CCPPA */


/* _hoops_PASGA _hoops_HII _hoops_PCCP _hoops_CRPR _hoops_IIGR _hoops_SCPPA *'_hoops_GRI _hoops_CRGR _hoops_IRS _hoops_ARP _hoops_IIGR _hoops_PGRC.  _hoops_GSPPA _hoops_HII
 * _hoops_HHH _hoops_RSPPA _hoops_RRGR _hoops_GGR _hoops_ASPPA, _hoops_PGAP _hoops_CSAP _hoops_IGI _hoops_IH _hoops_PSPPA _hoops_RSSI.
 * _hoops_HSPPA _hoops_HRGR _hoops_RGGIR(_hoops_PGGIR^2) (_hoops_IRIGR: _hoops_IHPH) */
local void _hoops_ISPPA (
	_hoops_AIGPR *			_hoops_RIGC,
	_hoops_RGPPA *				_hoops_GCPPA, 
	_hoops_SGPPA *	_hoops_CSPPA)
{				
	_hoops_GGPPA *line, *_hoops_SSPPA;
	_hoops_RCPPA *		_hoops_RHHGA;
	int count;
	float tolerance;
	Point *ptr;

	tolerance = _hoops_SIPPA (_hoops_GCPPA);

	_hoops_ACPPA *	_hoops_AHHGA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_ACPPA)(_hoops_RIGC->memory_pool);
	_hoops_ACPPA *	_hoops_GGHPA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_ACPPA)(_hoops_RIGC->memory_pool);

	/* _hoops_PSSP _hoops_RGHPA _hoops_III _hoops_SGHC _hoops_CRGR _hoops_IRS _hoops_CCHHR _hoops_HIGR */
	for (int i = 0; i < _hoops_GCPPA->Count(); i++) {
		line = (*_hoops_GCPPA)[i];
		if ((line->start - line->end)._hoops_PPSSR() > 1e-10) {
			_hoops_RHHGA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_RCPPA)(_hoops_RIGC->memory_pool);
			_hoops_RHHGA->AddFirst(line);
			_hoops_AHHGA->AddLast(_hoops_RHHGA);
		}
	}
	while ((_hoops_RHHGA = _hoops_AHHGA->RemoveFirst()) != null) {
		if (_hoops_GHHGA(_hoops_RHHGA, _hoops_AHHGA, tolerance))
			continue;
		_hoops_GGHPA->AddFirst(_hoops_RHHGA);
	}
	delete _hoops_AHHGA;

	/* _hoops_HA _hoops_PGGC _hoops_RH _hoops_CCHHR _hoops_CPCI _hoops_CRGR _hoops_SIRGR */
	_hoops_CSPPA->_hoops_GRPPA = 0; /* _hoops_PSCPR _hoops_SHRRR _hoops_AGHPA _hoops_SR _hoops_ACPA _hoops_SCH'_hoops_GRI _hoops_SIGR */
	_hoops_CSPPA->polyline_count = _hoops_GGHPA->Count();
	_hoops_CSPPA->_hoops_RRPPA = 0;
	_hoops_GGHPA->ResetCursor();
	count = _hoops_GGHPA->Count();
	for (int i = 0; i < count; i++) {
		_hoops_RHHGA = _hoops_GGHPA->PeekCursor();
		_hoops_CSPPA->_hoops_RRPPA += _hoops_RHHGA->Count() + 1;
		_hoops_GGHPA->AdvanceCursor();
	}
	if (_hoops_CSPPA->polyline_count)
	{	
	    ALLOC_ARRAY(_hoops_CSPPA->polyline_lengths, _hoops_CSPPA->polyline_count, int);
	    ALLOC_ARRAY(_hoops_CSPPA->polyline_points, _hoops_CSPPA->_hoops_RRPPA, Point);
	    _hoops_GGHPA->ResetCursor();
	    ptr = _hoops_CSPPA->polyline_points;
	    for (int i = 0; i < count; i++) {
			_hoops_RHHGA = _hoops_GGHPA->RemoveFirst();
			if (_hoops_RHHGA->Count()) {
				_hoops_CSPPA->polyline_lengths[i] = _hoops_RHHGA->Count() + 1;
				_hoops_SSPPA = null;
				while ((line = _hoops_RHHGA->RemoveFirst()) != null) {
					*ptr = line->start;
					ptr++;
					_hoops_SSPPA = line;
				}
				*ptr = _hoops_SSPPA->end;
				ptr++;
			}
			delete  _hoops_RHHGA;
	    }
	}
	delete _hoops_GGHPA;

}


#define _hoops_PGHPA 15
/* _hoops_IRS _hoops_PPCAR _hoops_PCPH _hoops_PIGS _hoops_HPP _hoops_GIPR _hoops_HGHPA _hoops_PPR 
 * _hoops_IGHPA.  _hoops_PAAS _hoops_PIGS _hoops_HPP _hoops_HGHPA, 
 * _hoops_RH "_hoops_CGHPA" _hoops_CGH _hoops_SHH _hoops_IHPR, _hoops_GGR _hoops_PGAP _hoops_AGIR _hoops_SR _hoops_SGHPA _hoops_ISCP _hoops_ACPP _hoops_PSAP _hoops_GRHPA
 * _hoops_CRGR _hoops_IRS _hoops_PPARR _hoops_SGS _hoops_ICGI _hoops_IRS _hoops_RRHPA, _hoops_IS _hoops_SHH _hoops_ARHPA _hoops_HPP _hoops_RH _hoops_SPS _hoops_AASA 
 * _hoops_IS _hoops_IGHPA _hoops_SIHH _hoops_PRHPA _hoops_IS _hoops_HRHPA */
GLOBAL_FUNCTION int HI_Compute_Intersect_Polyline (
	_hoops_AIGPR *	_hoops_RIGC,
	int						point_count1, 
	Point const *			points1, 
	int						face_list_length1, 
	int const *				face_list1,
	int						point_count2, 
	Point const *			points2, 
	int						face_list_length2, 
	int const *				face_list2,
	int alter *				polyline_count,
	int alter *				polyline_lengths,
	int alter *				_hoops_RRPPA,
	Point alter *			polyline_points,
	bool					_hoops_IRHPA)
{
	
	if (point_count1 == 0 || point_count2 == 0)
		return 0;

	_hoops_SASC _hoops_CRHPA(point_count1, points1);
	_hoops_SASC _hoops_SRHPA(point_count2, points2);

	VBSP * _hoops_PGPPA = HI_New_BSP (HOOPS_WORLD->memory_pool, _hoops_CRHPA, _hoops_PGHPA);
	VBSP * _hoops_HGPPA = HI_New_BSP (HOOPS_WORLD->memory_pool, _hoops_SRHPA, _hoops_PGHPA);

	_hoops_GAHPA (_hoops_PGPPA, point_count1, points1, face_list_length1, face_list1, false);
	_hoops_GAHPA (_hoops_HGPPA, point_count2, points2, face_list_length2, face_list2, false);

	_hoops_AGPPA info;
	info.points1	= points1;
	info.face_list1 = face_list1;
	info._hoops_PGPPA		= _hoops_PGPPA;
	info.points2	= points2;
	info.face_list2 = face_list2;
	info._hoops_HGPPA		= _hoops_HGPPA;
	info._hoops_PICHR		= POOL_NEW(_hoops_RIGC->memory_pool, _hoops_RGPPA)(_hoops_RIGC->memory_pool);
	info._hoops_IGPPA = 0;
	info._hoops_CGPPA	= false;
	
	HI_Test_BSP_BSP (_hoops_PGPPA, _hoops_RIPPA, &info, _hoops_HGPPA , false);

	if (polyline_count)
		*polyline_count = 0;		
	if (_hoops_RRPPA)
		*_hoops_RRPPA = 0;	
	int _hoops_HPIS = 0;

	if (info._hoops_PICHR->Count()) {

		_hoops_SGPPA *results;
		ALLOC(results, _hoops_SGPPA);
		_hoops_ISPPA (_hoops_RIGC, info._hoops_PICHR, results);
		_hoops_HPIS = results->polyline_count;

		if (polyline_count)
			*polyline_count = results->polyline_count;
		if (polyline_lengths)
			_hoops_AIGA (results->polyline_lengths, results->polyline_count, int, polyline_lengths);
		if (_hoops_RRPPA)
			*_hoops_RRPPA = results->_hoops_RRPPA;
		if (polyline_points)
			_hoops_AIGA (results->polyline_points, results->_hoops_RRPPA, Point, polyline_points);

		if (_hoops_IRHPA) {

			if (_hoops_RIGC->_hoops_RAHPA)
				HI_Delete_Intersect_Polyline_Cache (_hoops_RIGC->_hoops_RAHPA);
			results->_hoops_GRPPA = _hoops_ARPPA();
			_hoops_RIGC->_hoops_RAHPA = results;
		}
		else {
			HI_Delete_Intersect_Polyline_Cache (results);
		}
	}

	if (_hoops_PGPPA != null) {
		HI_BSP_Map_Function (_hoops_PGPPA, _hoops_AAHPA, null);
		HI_Delete_BSP (_hoops_PGPPA);
	}

	if (_hoops_HGPPA != null) {
		HI_BSP_Map_Function (_hoops_HGPPA, _hoops_AAHPA, null);
		HI_Delete_BSP (_hoops_HGPPA);
	}

	if (info._hoops_PICHR != null) {
		for (int i = 0; i < info._hoops_PICHR->Count(); i++) {
			_hoops_GGPPA * line = (*info._hoops_PICHR)[i];
			FREE(line, _hoops_GGPPA);
		}
		delete info._hoops_PICHR;
	}

	return _hoops_HPIS;

} /* _hoops_RSGR _hoops_API _hoops_PAHPA */



GLOBAL_FUNCTION bool HI_Compute_Intersect_Polyline_Nonzero (
	_hoops_AIGPR *	_hoops_RIGC,
	VBSP *					_hoops_PGPPA,
	int						point_count1, 
	Point const *			points1, 
	int						face_list_length1, 
	int const *				face_list1,
	int						point_count2, 
	Point const *			points2, 
	int						face_list_length2, 
	int const *				face_list2)
{
	UNREFERENCED(_hoops_RIGC);

	face_list_length1 = 0;

	if (point_count1 == 0 || point_count2 == 0)
		return 0;

	_hoops_SASC  _hoops_SRHPA(point_count2, points2);

 	VBSP * _hoops_HGPPA = HI_New_BSP (HOOPS_WORLD->memory_pool, _hoops_SRHPA, _hoops_PGHPA);
 	_hoops_GAHPA (_hoops_HGPPA, point_count2, points2, face_list_length2, face_list2, false);

	_hoops_AGPPA info;
	info.points1	= points1;
	info.face_list1 = face_list1;
	info._hoops_PGPPA		= _hoops_PGPPA;
	info.points2	= points2;
	info.face_list2 = face_list2;
	info._hoops_HGPPA		= _hoops_HGPPA;
	info._hoops_PICHR		= null;
	info._hoops_IGPPA = 0;
	info._hoops_CGPPA = true;

	HI_Test_BSP_BSP (_hoops_PGPPA, _hoops_RIPPA, &info, _hoops_HGPPA , false);

 	if (_hoops_HGPPA != null) {
		HI_BSP_Map_Function (_hoops_HGPPA, _hoops_AAHPA, null);
		HI_Delete_BSP (_hoops_HGPPA);
	}

	if (info._hoops_IGPPA) 
		return true;

	return false;
}

HC_INTERFACE int HC_Show_Intersect_Polyline_Size (
	int				point_count1, 
	Point const *	points1, 
	int				face_list_length1, 
	int const *		face_list1,
	int				point_count2, 
	Point const *	points2, 
	int				face_list_length2, 
	int const *		face_list2,
	int alter *		polyline_count,
	int alter *		_hoops_RRPPA) 
{
	_hoops_PAPPR context("Show_Intersect_Polyline_Size");

	return HI_Compute_Intersect_Polyline (
			context,
			point_count1, 
			points1, 
			face_list_length1, 
			face_list1,
			point_count2, 
			points2, 
			face_list_length2, 
			face_list2,
			polyline_count,
			null,
			_hoops_RRPPA,
			null,
			true);
}


HC_INTERFACE int HC_Compute_Intersect_Polyline (
	int				point_count1, 
	Point const *	points1, 
	int				face_list_length1, 
	int const *		face_list1,
	int				point_count2, 
	Point const *	points2, 
	int				face_list_length2, 
	int const *		face_list2,
	int alter *		polyline_count,
	int alter *		polyline_lengths,
	int alter *		_hoops_RRPPA,
	Point alter *	polyline_points) 
{
	_hoops_PAPPR context("HC_Compute_Intersect_Polyline");

	_hoops_SGPPA *_hoops_CSC;

	_hoops_CSC = (_hoops_SGPPA *) context->_hoops_RAHPA;
	if (_hoops_CSC &&
		_hoops_CSC->_hoops_GRPPA == _hoops_ARPPA()) {
		if (polyline_count) 
			*polyline_count = _hoops_CSC->polyline_count;
		if (polyline_lengths)
			_hoops_AIGA(_hoops_CSC->polyline_lengths, _hoops_CSC->polyline_count, int, polyline_lengths);
		if (_hoops_RRPPA)
			*_hoops_RRPPA = _hoops_CSC->_hoops_RRPPA;
		if (polyline_points)
			_hoops_AIGA(_hoops_CSC->polyline_points, _hoops_CSC->_hoops_RRPPA, Point, polyline_points);
		return _hoops_CSC->polyline_count;
	}
	else {
		return HI_Compute_Intersect_Polyline (
				context,
				point_count1, 
				points1, 
				face_list_length1, 
				face_list1,
				point_count2, 
				points2, 
				face_list_length2, 
				face_list2,
				polyline_count,
				polyline_lengths,
				_hoops_RRPPA,
				polyline_points,
				false);
	}
} /* _hoops_RSGR _hoops_API _hoops_IGHPA */


GLOBAL_FUNCTION void HI_Delete_Intersect_Polyline_Cache (void *_hoops_HAHPA) 
{
	_hoops_SGPPA *_hoops_CSC = (_hoops_SGPPA *)_hoops_HAHPA;
	if (_hoops_CSC->polyline_count)
		FREE_ARRAY(_hoops_CSC->polyline_lengths, _hoops_CSC->polyline_count, int);
	if (_hoops_CSC->_hoops_RRPPA)
		FREE_ARRAY(_hoops_CSC->polyline_points, _hoops_CSC->_hoops_RRPPA, Point);
	FREE(_hoops_CSC, _hoops_SGPPA);
}

#define _hoops_IAHPA	(long)(_hoops_CAHPA-9)

local const _hoops_IGRCR _hoops_SAHPA[] = {
	{_hoops_IAHPA,		_hoops_GRRCR ("maximum deviation"),			_hoops_SPPCR, -2, true},
};

struct _hoops_GPHPA {
	int index;
	float t;
	float priority;
	_hoops_GPHPA *next;
};

typedef VHeap<_hoops_GPHPA *,float, true, false> _hoops_RPHPA;


local void _hoops_APHPA(Elliptical_Arc const* curve, float u, Point* _hoops_PPHPA, bool _hoops_HPHPA = true) {
	float			s, t;
	Point const *	center;
	Vector const *	_hoops_GGHI;
	Vector const *	_hoops_RGHI;
	

	if (_hoops_HPHPA)
		center = &curve->center;
	else
		center = &_hoops_HPCH::_hoops_IPCH;
	_hoops_GGHI = &curve->_hoops_GGHI;
	_hoops_RGHI = &curve->_hoops_RGHI;

	_hoops_RICH (360.0f * u, t, s);
	_hoops_PPHPA->x = center->x + s * _hoops_GGHI->x + t * _hoops_RGHI->x;
	_hoops_PPHPA->y = center->y + s * _hoops_GGHI->y + t * _hoops_RGHI->y;
	_hoops_PPHPA->z = center->z + s * _hoops_GGHI->z + t * _hoops_RGHI->z;

}

local float _hoops_IPHPA(_hoops_GPHPA *edge, Elliptical_Arc const *_hoops_CPHPA)
{	
	Point start, end, _hoops_SPGIR, _hoops_APIS, _hoops_ARGCR;
	_hoops_APHPA (_hoops_CPHPA, edge->t, &start, false);
	_hoops_APHPA (_hoops_CPHPA, edge->next->t, &end, false);
	_hoops_APHPA (_hoops_CPHPA, (edge->t + edge->next->t)/2, &_hoops_APIS, false);
	_hoops_SPGIR.x = (start.x + end.x) / 2;
	_hoops_SPGIR.y = (start.y + end.y) / 2;
	_hoops_ARGCR.x = _hoops_APIS.x - _hoops_SPGIR.x;
	_hoops_ARGCR.y = _hoops_APIS.y - _hoops_SPGIR.y;
	/*_hoops_SPHPA(_hoops_GHHPA._hoops_SISR, _hoops_GHHPA._hoops_HAPC, 0,  _hoops_HHGP._hoops_SISR, _hoops_HHGP._hoops_HAPC, 0);*/
	return HI_Sqrt(
		(_hoops_ARGCR.x * _hoops_ARGCR.x) + 
		(_hoops_ARGCR.y * _hoops_ARGCR.y));
}

HC_INTERFACE void HC_Compute_Pline_From_Crv_Size (
	Key				key,
	char const *	options,
	int *			pcount) {
	HC_Compute_Polyline_From_Curve (key, options, pcount, null);
}

HC_INTERFACE void HC_Compute_Polyline_From_Curve (
	Key					key,
	char const *		options,
	int *				pcount,
	Point *				points) 
{
	_hoops_PAPPR context("Compute_Polyline_From_Curve");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Polyline_From_Curve () */\n");
	);

	_hoops_HIACR (_hoops_RHHPA, _hoops_SAHPA);

	Option_Value *	option_list;
	if (!HI_Parse_Options (context, options, _hoops_CIACR (_hoops_RHHPA), &option_list, _hoops_SIACR))
		return;

	float	_hoops_IPPI = -1.0f;

	Option_Value *	option;
	if ((option = option_list) != null) do {
		switch (option->type->id) {
			case _hoops_IAHPA: {
				if (!option->_hoops_GCACR)
					_hoops_IPPI = option->value._hoops_PIPCR[0];
			}	break;

			default : {
				HE_ERROR (HEC_GEOMETRY, HES_INVALID_OPTION, "Unknown option");
			}
		}
	}
	_hoops_RGGA ((option = option->next) == null);
	HI_Free_Option_List (context, option_list);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, key, _hoops_AHHPA)) != null) {

		if (_hoops_IPPI == -1.0f) {

			Bounding	bounding = Bounding::Create();

			HI_Add_Geometry_Bounding (context, (Geometry *)target, 
				null, T_ANY_DRAWABLE_GEOMETRY, null, _hoops_GACAA|_hoops_ICIAA, bounding);

			_hoops_IPPI = 0.05f;
			_hoops_IPPI *= bounding->sphere.radius * 0.0125f;
			if (_hoops_IPPI<_hoops_CACIR)
				_hoops_IPPI=_hoops_CACIR;
		}

		switch (target->type) {

			case _hoops_SGCP: 
			case _hoops_RIIP: 
			case _hoops_GRCP: 
			case _hoops_RRCP:
			case _hoops_CGCP: 
			case _hoops_GIIP: {

				Elliptical_Arc			arc;
				_hoops_RPHPA *	_hoops_PHHPA;
				_hoops_RPHPA *	_hoops_HHHPA;
				float					priority = 0;
				_hoops_GPHPA *			edge;
				_hoops_GPHPA *			_hoops_SSAC;
				_hoops_GPHPA *			_hoops_IHHPA;
				Point *					_hoops_CHHPA;
				float					start, _hoops_SPGIR, end;

				/* _hoops_RCGPA _hoops_CPS _hoops_CRGR _hoops_PCCP _hoops_ICISR _hoops_PGIS */
				HD_Validate_Elliptical_Arc ((_hoops_GHHI const *)target, &arc, null);
				
				if (arc.arc_start > arc._hoops_PHHI) { 
					end = arc._hoops_PHHI;
					_hoops_SPGIR = ((arc.arc_start -1) + (arc._hoops_PHHI)) / 2;
					start = arc.arc_start -1;
				}
				else { 
					end = arc._hoops_PHHI;
					_hoops_SPGIR = (arc.arc_start + arc._hoops_PHHI)/ 2;
					start = arc.arc_start;
				}

				_hoops_HHHPA = POOL_NEW(context->memory_pool, _hoops_RPHPA)(context->memory_pool);
				ZALLOC (edge, _hoops_GPHPA);

				/* _hoops_HSPP _hoops_PPSR */
				edge->t = start;
				_hoops_HHHPA->Push(edge, 0.0f);
				_hoops_SSAC = edge;

				/* _hoops_HHAA-_hoops_PPRRR _hoops_PPSR _hoops_GAPA _hoops_HSPP _hoops_PPR _hoops_RSGR */
				ZALLOC (edge, _hoops_GPHPA);
				edge->t = _hoops_SPGIR;
				edge->next = _hoops_SSAC;
				edge->priority = _hoops_IPHPA(edge, &arc);
				_hoops_HHHPA->Push(edge, edge->priority);
				_hoops_SSAC = edge;

				/* _hoops_RSGR _hoops_PPSR */
				ZALLOC(edge, _hoops_GPHPA);
				edge->t = end;
				edge->next = _hoops_SSAC;
				edge->priority = _hoops_IPHPA(edge, &arc);
				_hoops_HHHPA->Push(edge, edge->priority);

				/* _hoops_SHHPA _hoops_CCGR _hoops_RH _hoops_GIHPA _hoops_HRGR _hoops_CAPP _hoops_ISCP _hoops_SAIPR */
				for (;;) {
					if (!_hoops_HHHPA->Peek(&edge, &priority))
						break;
					if (priority < _hoops_IPPI) /* _hoops_SR'_hoops_ASAR _hoops_CPHR */
						break;
					/* _hoops_CGP _hoops_SR _hoops_HHGC _hoops_IS _hoops_GGCR _hoops_IRS _hoops_PPSR _hoops_RIHPA _hoops_HCSP, _hoops_SAHR _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RPP 
					   _hoops_AIHPA->_hoops_PIHPA->_hoops_IGI _hoops_HRGR _hoops_SGRIR _hoops_HSAR _hoops_RH _hoops_RIHPA.  _hoops_CGP _hoops_HIS, _hoops_IHSA.
					   _hoops_PS _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_AA _hoops_PA _hoops_GRH _hoops_HIHPA _hoops_SGS _hoops_ISPR. 
					   _hoops_HHIGR'_hoops_GRI _hoops_IRS 1-_hoops_IIHPA */
		
					/* _hoops_CIHPA _hoops_RH _hoops_SCIA, _hoops_PSCR _hoops_GCGRA _hoops_SCH _hoops_CCA _hoops_PGCR _hoops_CCAH _hoops_ARIPR */
					_hoops_HHHPA->Pop(&edge, &priority);

					/* _hoops_SRS _hoops_CCAH _hoops_ISHA */
					ZALLOC(_hoops_IHHPA, _hoops_GPHPA);
					if (edge->next != null)
						_hoops_IHHPA->t = (edge->t + edge->next->t) /2;
					_hoops_IHHPA->next = edge->next;
					_hoops_IHHPA->priority = _hoops_IPHPA(_hoops_IHHPA, &arc);
					_hoops_SSAC = _hoops_IHHPA;
					_hoops_HHHPA->Push(_hoops_IHHPA, _hoops_IHHPA->priority);

					/* _hoops_HA _hoops_IH _hoops_RH _hoops_GIAP _hoops_CCAH _hoops_ISHA*/
					edge->next = _hoops_IHHPA;
					edge->priority = _hoops_IPHPA(edge, &arc);
					_hoops_HHHPA->Push(edge, edge->priority);

				} 

				/* _hoops_SR'_hoops_ASAR _hoops_CPHR, _hoops_AGSGR _hoops_CAPR _hoops_CRGR _hoops_SHGS _hoops_PPR _hoops_ASRC! */
				*pcount = _hoops_HHHPA->Count();

				_hoops_CHHPA = points;

				/* _hoops_SGH _hoops_HPIH _hoops_SIHPA _hoops_IS _hoops_GHIS _hoops_HPP _hoops_RA, _hoops_HIS _hoops_RH _hoops_RSSA _hoops_CHR _hoops_GGR _hoops_ISII _hoops_AGR */
				_hoops_PHHPA = POOL_NEW(context->memory_pool, _hoops_RPHPA)(context->memory_pool, _hoops_HHHPA->Count());
				while (_hoops_HHHPA->Pop(&edge)) 
					_hoops_PHHPA->Push(edge, edge->t);

				while (_hoops_PHHPA->Pop(&edge)) {
					if (_hoops_CHHPA != null) {
						_hoops_APHPA (&arc, edge->t, _hoops_CHHPA);
						_hoops_CHHPA++;
					}
					FREE(edge, _hoops_GPHPA);
				} 
				
				
				/* _hoops_IH _hoops_IRS _hoops_GCHPA, _hoops_GGCR _hoops_RH _hoops_RHCH _hoops_PPSR, _hoops_PSCR _hoops_ISSC _hoops_IS _hoops_RH _hoops_SRS _hoops_PPSR */
				if (target->type == _hoops_RRCP) {
					if (_hoops_CHHPA != null) {
						*_hoops_CHHPA = arc.center; _hoops_CHHPA++;
						*_hoops_CHHPA = *points;	
					}
					*pcount += 2;
				}
				
				/* _hoops_IH _hoops_IRS _hoops_RCHPA, _hoops_SAHR _hoops_GGCR _hoops_RH _hoops_APHR _hoops_PPSR */
				if (target->type == _hoops_GRCP) {
					if (_hoops_CHHPA != null) *_hoops_CHHPA = *points;	
					*pcount += 1;
				}

				delete _hoops_HHHPA;
				delete _hoops_PHHPA;

			}	break;

			case _hoops_CHIP: {
				Polyline polyline;
				HI_Generate_NURBS_Polyline ((_hoops_PIRGR const *)target, null, null, &polyline, _hoops_IPPI);
				if (points != null) 
					_hoops_AIGA(polyline.points, polyline.count, Point, points);
				*pcount = polyline.count;
				FREE_ARRAY (polyline.points, polyline.allocated, Point);
			}	break;

			default: {
				ASSERT(0);
				HE_ERROR (HEC_INVALID_KEY, HES_INVALID_TYPE, "Invalid key type");
			}
		}
		
		_hoops_IRRPR();
	}

}



HC_INTERFACE Key HC_CDECL HC_Generate_Poly_From_Geometry (
	Key					key,
	char const *		options) 
{
	_hoops_PAPPR context("Generate_Polyline_From_Geometry");

	Key	_hoops_ACHPA = _hoops_SHSSR;

	_hoops_HPAH * _hoops_PCHPA;
	if ((_hoops_PCHPA = HI_Find_Target_And_Lock(context, key, _hoops_AHHPA)) != null) {

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {

			Polyline *	polyline = null;
			ZALLOC (polyline, Polyline);

			polyline->type = _hoops_IIIP;
			polyline->_hoops_CPGPR = _hoops_PHSSR;

			PUSHNAME(context);
			HC_Compute_Polyline_From_Curve (key, options, &polyline->count, null);
			polyline->allocated = polyline->count;
			if (polyline->count > 0) {
				ALLOC_ARRAY (polyline->points, polyline->count, Point);
				HC_Compute_Polyline_From_Curve (key, options, &polyline->count, polyline->points);
			}
			POPNAME(context);

			polyline->_hoops_CPGPR = _hoops_HCHPA;

			Activity	_hoops_CPGPR = polyline->count > 0 ?
				_hoops_IHSSR|_hoops_ICHPA : _hoops_CCHPA;

			HI_Insert_Geometry (context, target, polyline, false, _hoops_CPGPR);

			if (polyline->owner != null)
				_hoops_SASIR (context, polyline->owner, _hoops_PHSSR);

			_hoops_ACHPA = _hoops_AIRIR (polyline);

			_hoops_IRRPR();
		}
 
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Generate_Polyline_From_Geometry (LOOKUP (%D),", key));
		HI_Dump_Code (Sprintf_S (null, "%S), ", options));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_ACHPA));
	);

	return _hoops_ACHPA;
}


#else


HC_INTERFACE int HC_Show_Intersect_Polyline_Size (
						int point_count1, 
						Point const *points1, 
						int face_list_length1, 
						int const *face_list1,
						int point_count2, 
						Point const *points2, 
						int face_list_length2, 
						int const *face_list2,
						int alter *polyline_count,
						int alter *_hoops_RRPPA) {
	_hoops_IRPPR ("Selection By Shell");
	return 0;
}
HC_INTERFACE int HC_Compute_Intersect_Polyline (
						int point_count1, 
						Point const *points1, 
						int face_list_length1, 
						int const *face_list1,
						int point_count2, 
						Point const *points2, 
						int face_list_length2, 
						int const *face_list2,
						int alter *polyline_count,
						int alter *polyline_lengths,
						int alter *_hoops_RRPPA,
						Point alter *polyline_points) {
	_hoops_IRPPR ("Selection By Shell");
	return 0;
}
GLOBAL_FUNCTION void HI_Delete_Intersect_Polyline_Cache (void *_hoops_CSC) {
	_hoops_IRPPR ("Selection By Shell");
}

HC_INTERFACE void HC_Compute_Pline_From_Crv_Size (
	Key			key,
	char const *	options,
	int *			pcount) {
	_hoops_IRPPR ("Selection By Shell");
}

HC_INTERFACE void HC_Compute_Polyline_From_Curve (
	Key			key,
	char const *	options,
	int *			pcount,
	Point *		points) {
	_hoops_IRPPR ("Selection By Shell");
}


HC_INTERFACE Key HC_CDECL HC_Generate_Poly_From_Geometry (
	Key			key,
	char const		*options) {
	_hoops_IRPPR ("Selection By Shell");
	return 0;
}


#endif /* _hoops_CHS _hoops_SCHPA */




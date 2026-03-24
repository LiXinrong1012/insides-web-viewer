/*
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unaxuthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.64.2.1 2011-01-10 23:56:05 guido Exp $
 */

#include "hoops.h"
#include "hc_proto.h"
#include "adt.h"
#include "csutil.h"
#include "hpserror.h"
#include "hi_proto.h"


#ifndef _hoops_CACIR
# define _hoops_CACIR (1e-5f)
#endif

#ifndef MAX
#define MAX(a,b)            (((a) > (b)) ? (a) : (b))
#endif

/*------------_hoops_HSP _hoops_GIIS _hoops_RARIA------------------*/

_hoops_SHPPA *_hoops_SIIIA(
	int					flags,
	int					len,
	int const *			indices, 
	Point const *		points,
	_hoops_HRPA const *	matrix,
	_hoops_ARPA const &		_hoops_PCPSA,
	int					index)
{
	_hoops_SHPPA *face;
	ALLOC(face, _hoops_SHPPA);
	face->type = _hoops_GPHIA;
	face->flags = flags;
	face->len = len;
	face->_hoops_GIPPA = indices;
	face->plane = _hoops_PCPSA;
	face->index = index;
	_hoops_CHHIA(points, matrix, len, indices, face->bbox);
	return face;
}


_hoops_ACHHA *_hoops_HCPSA(
  	const Point *	point, 
	float			tolerance, 
	int				_hoops_HCHHA)
{
	_hoops_ACHHA *vertex;
	ALLOC(vertex, _hoops_ACHHA);
	vertex->type = _hoops_ACPSA;
	vertex->vertex = *point;
	vertex->_hoops_HCHHA = _hoops_HCHHA;

	vertex->bbox = _hoops_SASC(1, point);
	vertex->bbox._hoops_IACHA(tolerance);

	return vertex;
}



local float _hoops_HHSPS(PolyCylinder *_hoops_HSPIR, int start, int end)
{
	float _hoops_SAGP = 0.0f;

	if (_hoops_HSPIR->radii == null)
		return 0;

	if (_hoops_HSPIR->_hoops_ISPIR == 1)
		return _hoops_HSPIR->radii[0];

	if (_hoops_HSPIR->_hoops_ISPIR > end) {
		for (int i = start; i <= end; i++) {
			if (_hoops_SAGP < _hoops_HSPIR->radii[i])
				_hoops_SAGP = _hoops_HSPIR->radii[i];
		}	
	}
	else {
		for (int i = start; i <= end; i++) {
			int index = i % _hoops_HSPIR->_hoops_ISPIR;
			if (_hoops_SAGP < _hoops_HSPIR->radii[index])
				_hoops_SAGP = _hoops_HSPIR->radii[index];
		}
	}

	return _hoops_SAGP;
}


_hoops_RRHIA *_hoops_HSIIA(
	int					start,
	int					end,
	PolyCylinder *		_hoops_HSPIR,
	_hoops_HRPA const *	matrix)
{
	UNREFERENCED(matrix);

	_hoops_RRHIA *_hoops_PSIIA;
	ALLOC(_hoops_PSIIA, _hoops_RRHIA);
	_hoops_PSIIA->type = _hoops_GCPSA;
	_hoops_PSIIA->start = start;
	_hoops_PSIIA->end = end;
	_hoops_PSIIA->flags = _hoops_PRHIA;

	int count = 1 + end - start;

	_hoops_PSIIA->bbox = _hoops_SASC(count, &_hoops_HSPIR->points[start]);
	
	float	_hoops_SAGP = _hoops_HHSPS(_hoops_HSPIR, start, end);

	Vector	_hoops_IHSPS(_hoops_SAGP, _hoops_SAGP, _hoops_SAGP);
		
	_hoops_PSIIA->bbox.min -= _hoops_IHSPS;
	_hoops_PSIIA->bbox.max += _hoops_IHSPS;

	return _hoops_PSIIA;
}


local void _hoops_CHSPS(_hoops_SHPPA *face)
{
	if (face->flags & _hoops_GCIIA)
		FREE_ARRAY(face->_hoops_GIPPA, face->len, int);

	FREE(face, _hoops_SHPPA);
}
local void _hoops_SHSPS(_hoops_ACHHA *vertex)
{
 	FREE(vertex, _hoops_ACHHA);
}

local void _hoops_GISPS(_hoops_RRHIA *_hoops_PSIIA)
{
	FREE(_hoops_PSIIA, _hoops_RRHIA);
}

/* _hoops_PAPIA _hoops_SSCP _hoops_IS _hoops_PSSP _hoops_SGS _hoops_CHIA _hoops_GGR _hoops_SSSAR.
 * _hoops_ICPSA _hoops_HPGR _hoops_GPRR _hoops_GGR _hoops_RGSPR _hoops_IS _hoops_CGIC _hoops_PGAP _hoops_CCPSA _hoops_IS _hoops_AASA */
_hoops_CSCAR _hoops_AAHPA(void *ptr, void *user_data)
{
	_hoops_SGGIA *h = (_hoops_SGGIA *)ptr;

	switch (h->type) {
		case _hoops_GPHIA:
			_hoops_CHSPS((_hoops_SHPPA *) ptr);
			break;
		case _hoops_ACPSA:
			_hoops_SHSPS((_hoops_ACHHA *) ptr);
			break;
		case _hoops_GCPSA:
			_hoops_GISPS((_hoops_RRHIA *)ptr);
			break;
		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					"Attempt to delete unrecognized type in internal shell utilities");
			break;
	}
	/* _hoops_RISPS _hoops_PRGH _hoops_HRGR _hoops_RGAR _hoops_RGHP _hoops_HIS _hoops_SGS _hoops_SR _hoops_PSSP _hoops_RH _hoops_CAPGR _hoops_PAPIA
	 * _hoops_CHIA _hoops_GGR _hoops_AISPS */
	UNREFERENCED(user_data); 

	return VBSP_STATUS_CONTINUE;
}


/*_hoops_HICRR*/
/* _hoops_RH _hoops_III _hoops_PISRA _hoops_HII _hoops_RH _hoops_HSP _hoops_CCA _hoops_PPPPA _hoops_GAR _hoops_RGCI _hoops_GSSR.  _hoops_HHIGR _hoops_IGISH
 * _hoops_RH _hoops_PISPS _hoops_IGIAR _hoops_IRS _hoops_HISPS _hoops_PRCGH.	_hoops_PS _hoops_HHGC _hoops_IS _hoops_ACPA _hoops_RPP _hoops_SGS _hoops_HISPS _hoops_PRCGH
 * _hoops_ICHIA _hoops_GII _hoops_IIGR _hoops_RH _hoops_HHAA-_hoops_HGS _hoops_AARI _hoops_RH _hoops_SPPR _hoops_IIGR _hoops_PSRPA */
local bool _hoops_IISPS(
	Point const *	line,
	Point const *	points1, 
	int				_hoops_HRPPA,
	const int *		_hoops_AIIPR,
	_hoops_ARPA const *	_hoops_IRPPA,
	_hoops_ARPA const *	_hoops_CRPPA, 
	float			_hoops_ISCIA = 0.0f)
{	 
	/* _hoops_ISAP _hoops_PAH _hoops_RASAR _hoops_CCA _hoops_IRS _hoops_ARHAR _hoops_HSP */
	if (_hoops_HRPPA < 3)
		return false;

	Point const * _hoops_RPPPA = &line[0];
	Point const * _hoops_APPPA = &line[1];

	for (int i = 0; i < _hoops_HRPPA; i++) {	 
		int index = (_hoops_AIIPR ? _hoops_AIIPR[i] : i);

		Point const * _hoops_GAPPA = &points1[index];
		Point const * _hoops_RAPPA;

		if (i+1 < _hoops_HRPPA) {
			index = (_hoops_AIIPR ? _hoops_AIIPR[i+1] : i+1);
			_hoops_RAPPA = &points1[index];
		}
		else {
			index = (_hoops_AIIPR ? _hoops_AIIPR[i+1-_hoops_HRPPA] : i+1-_hoops_HRPPA);
			_hoops_RAPPA = &points1[index]; /* _hoops_ARGAR _hoops_AARI */
		}

		/* _hoops_RPP _hoops_GIPR _hoops_RSSA _hoops_IIGR _hoops_RH _hoops_SCGR _hoops_ISHA _hoops_CHR _hoops_GPP _hoops_RH _hoops_PSHR _hoops_PPAP _hoops_IIGR _hoops_PPPPA, _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_GPIHR */
		if ((*_hoops_GAPPA * *_hoops_CRPPA> 0) == (*_hoops_RAPPA * *_hoops_CRPPA > 0))
			continue;

		Vector _hoops_ARGCR = *_hoops_RAPPA - *_hoops_GAPPA;

		bool status = HI_Normalize(&_hoops_ARGCR);

		_hoops_ARPA _hoops_AAPPA;
		HI_Compute_Cross_Product((Vector *)&_hoops_ARGCR, (Vector *)_hoops_IRPPA, (Vector *)&_hoops_AAPPA);

		if (!HI_Normalize((Vector*)&_hoops_AAPPA))
			status = false;

		if (!status)
			continue;

		/* _hoops_GHGP _hoops_IHSR _hoops_HRGR -(_hoops_PAPPA + _hoops_HPP + _hoops_IIHCR) */
		_hoops_AAPPA.d = -(_hoops_RAPPA->x*_hoops_AAPPA.a + _hoops_RAPPA->y*_hoops_AAPPA.b + _hoops_RAPPA->z*_hoops_AAPPA.c);

		float _hoops_SCAAA = *_hoops_RPPPA * _hoops_AAPPA;
		float _hoops_GSAAA = *_hoops_APPPA * _hoops_AAPPA;

		if (_hoops_SCAAA<=-_hoops_ISCIA && _hoops_GSAAA>=_hoops_ISCIA || _hoops_GSAAA<=-_hoops_ISCIA && _hoops_SCAAA>=_hoops_ISCIA) 
			return true;
	}

	return false;
} 

local float _hoops_CISPS (Point const * p, Point const * _hoops_GAPPA, Point const * _hoops_RAPPA) 
{
	Vector _hoops_SISPS = *p - *_hoops_GAPPA;
	float _hoops_GCSPS = _hoops_SISPS._hoops_PPSSR();

	Vector _hoops_RCSPS = *p - *_hoops_RAPPA;
	float _hoops_ACSPS = _hoops_RCSPS._hoops_PPSSR();

	Vector _hoops_PCSPS = *_hoops_GAPPA - *_hoops_RAPPA;
	float _hoops_HCSPS = _hoops_PCSPS._hoops_PPSSR();

	float _hoops_ICSPS = sqrt(_hoops_HCSPS);

	float _hoops_CCSPS = (_hoops_GCSPS + _hoops_HCSPS - _hoops_ACSPS)/(2*_hoops_ICSPS);

	if (_hoops_CCSPS < 0 )
		return sqrt(_hoops_GCSPS); 

	if (_hoops_CCSPS > _hoops_ICSPS ) 
		return sqrt(_hoops_ACSPS); 

	return	sqrt(_hoops_GCSPS - _hoops_CCSPS*_hoops_CCSPS);
}


/*_hoops_HICRR*/
/* _hoops_RH _hoops_III _hoops_PISRA _hoops_HII _hoops_RH _hoops_HSP _hoops_CCA _hoops_PPPPA _hoops_GAR _hoops_RGCI _hoops_GSSR.  _hoops_HHIGR _hoops_IGISH
 * _hoops_RH _hoops_PISPS _hoops_IGIAR _hoops_IRS _hoops_HISPS _hoops_PRCGH.	_hoops_PS _hoops_HHGC _hoops_IS _hoops_ACPA _hoops_RPP _hoops_SGS _hoops_HISPS _hoops_PRCGH
 * _hoops_ICHIA _hoops_GII _hoops_IIGR _hoops_RH _hoops_HHAA-_hoops_HGS _hoops_AARI _hoops_RH _hoops_SPPR _hoops_IIGR _hoops_PSRPA */
local bool _hoops_SCSPS(
	Point const *	line,
	Point const *	points1, 
	int				_hoops_HRPPA,
	const int *		_hoops_AIIPR,
	_hoops_ARPA const *	_hoops_IRPPA)
{	 
	/* _hoops_ISAP _hoops_PAH _hoops_RASAR _hoops_CCA _hoops_IRS _hoops_ARHAR _hoops_HSP */
	if (_hoops_HRPPA < 3)
		return false;

	Point const *	_hoops_RPPPA = &line[0];
	Point const *	_hoops_APPPA = &line[1];

	for (int i = 0; i < _hoops_HRPPA; i++) {	 
		int index = (_hoops_AIIPR ? _hoops_AIIPR[i] : i);

		Point const *	_hoops_GAPPA = &points1[index];
		Point const *	_hoops_RAPPA;

		if (i+1 < _hoops_HRPPA) {
			index = (_hoops_AIIPR ? _hoops_AIIPR[i+1] : i+1);
			_hoops_RAPPA = points1 + index;
		}
		else {
			index = (_hoops_AIIPR ? _hoops_AIIPR[i+1-_hoops_HRPPA] : i+1-_hoops_HRPPA);
			_hoops_RAPPA = points1 + index; /* _hoops_ARGAR _hoops_AARI */
		}
		
		Vector _hoops_ARGCR = *_hoops_RAPPA - *_hoops_GAPPA;

		bool status = HI_Normalize(&_hoops_ARGCR);

		_hoops_ARPA _hoops_AAPPA;

		HI_Compute_Cross_Product(&_hoops_ARGCR, (Vector *)_hoops_IRPPA, (Vector *)&_hoops_AAPPA);

		if (!HI_Normalize((Vector*)&_hoops_AAPPA))
			status = false;

		if (!status)
			continue;

		/* _hoops_GHGP _hoops_IHSR _hoops_HRGR -(_hoops_PAPPA + _hoops_HPP + _hoops_IIHCR) */
		_hoops_AAPPA.d = -(_hoops_RAPPA->x*_hoops_AAPPA.a + _hoops_RAPPA->y*_hoops_AAPPA.b + _hoops_RAPPA->z*_hoops_AAPPA.c);

  		if ((_hoops_AAPPA * *_hoops_RPPPA > 0) !=
			(_hoops_AAPPA * *_hoops_APPPA > 0)) {

			Point _hoops_RSPSA;
			_hoops_IPPPA(_hoops_RPPPA, _hoops_APPPA, &_hoops_AAPPA, &_hoops_RSPSA);

			if (fabs(_hoops_CISPS (&_hoops_RSPSA, _hoops_GAPPA, _hoops_RAPPA)) < _hoops_CACIR)
				return true;
		}
	}
	return false;
} 


/* _hoops_PAPRR _hoops_RH _hoops_SGSSR _hoops_GAPA _hoops_IRS _hoops_III _hoops_CAGH (_hoops_GAR _hoops_PAPR _hoops_HPP _hoops_RGCI _hoops_PGCR _hoops_GSHIA) _hoops_PPR _hoops_IRS _hoops_IPPA */
void _hoops_IPPPA(Point const * _hoops_GAPPA, Point const * _hoops_RAPPA, _hoops_ARPA const * _hoops_AAPPA, Point alter * _hoops_PAGR)
{
	float _hoops_RSS = Abs (*_hoops_AAPPA * *_hoops_GAPPA);
	float _hoops_ASS = Abs (*_hoops_AAPPA * *_hoops_RAPPA);
	
	if (_hoops_RSS >= _hoops_CACIR) {
		*_hoops_PAGR = Point (
			((_hoops_RSS * _hoops_RAPPA->x) + (_hoops_ASS * _hoops_GAPPA->x)) / (_hoops_RSS + _hoops_ASS),
			((_hoops_RSS * _hoops_RAPPA->y) + (_hoops_ASS * _hoops_GAPPA->y)) / (_hoops_RSS + _hoops_ASS),
			((_hoops_RSS * _hoops_RAPPA->z) + (_hoops_ASS * _hoops_GAPPA->z)) / (_hoops_RSS + _hoops_ASS));
	}
	else
		*_hoops_PAGR = *_hoops_GAPPA;

}





float _hoops_GSSPS(const float *pt,const float *plane) 
{
	float _hoops_HCPSR,_hoops_ICPSR;
	_hoops_HCPSR = fabs( pt[0] * plane[0] + pt[1] * plane[1] + pt[2] * plane[2] + plane[3]);
	_hoops_ICPSR = sqrt(plane[0] * plane[0] + plane[1] * plane[1] + plane[2] * plane[2]);
	return (_hoops_HCPSR/_hoops_ICPSR);
}



bool _hoops_PCPIA(
	Point const *	points1, 
	Vector const *	_hoops_RCGAA,
	_hoops_ARPA const *	_hoops_IRPPA,
	int				_hoops_HRPPA,
	const int *		_hoops_AIIPR,					
	Point const *	points2,
	int				_hoops_SPPPA,
	const int *		_hoops_HIIPR,
	_hoops_ARPA const *	_hoops_CRPPA,
	Point *			_hoops_RSPSA,
	float			_hoops_RCPIA) 
{
	

	bool _hoops_HCAGA = false;
 

	float _hoops_RSSPS = 0.0f;
 	for (int i=0;i<_hoops_HRPPA;i++)
	{
		Vector _hoops_ISPI;
		if (i<_hoops_HRPPA-1)
			_hoops_ISPI = points1[_hoops_AIIPR[i+1]] - points1[_hoops_AIIPR[i]];
		else
			_hoops_ISPI = points1[_hoops_AIIPR[0]] - points1[_hoops_AIIPR[i]];
		float vl = HI_Compute_Vector_Length(&_hoops_ISPI);
		if (vl > _hoops_RSSPS)
			_hoops_RSSPS = vl;
	}
 	if (_hoops_RSSPS < fabs(_hoops_RCPIA))
		return false;

 	int *_hoops_ASSPS = new int[_hoops_HRPPA];

	Point *_hoops_PSSPS = new Point[_hoops_HRPPA];

 	for (int i=0;i<_hoops_HRPPA;i++)
		_hoops_ASSPS[i] = i;
 		
	for (int j=0;j<_hoops_HRPPA;j++) {
		int index = _hoops_AIIPR[j];
		_hoops_PSSPS[j] = points1[index] + _hoops_RCGAA[index] * _hoops_RCPIA;
	}


	bool _hoops_CARGA = true;
	float _hoops_HSSPS = 0.0f;
	for (int i=0;i<_hoops_HRPPA;i++)
	{
		
		float			_hoops_SSRP = *_hoops_IRPPA * _hoops_PSSPS[i];
		if (i > 0 && ((_hoops_SSRP > _hoops_CACIR && _hoops_HSSPS < -_hoops_CACIR) || (_hoops_SSRP < -_hoops_CACIR && _hoops_HSSPS > _hoops_CACIR)))
		{				
			_hoops_CARGA = false;
			break;
		}
		_hoops_HSSPS = _hoops_SSRP;
 
	}

	if (_hoops_CARGA)
	{
		_hoops_ARPA plane;
		_hoops_APHIA(_hoops_PSSPS, _hoops_HRPPA, _hoops_ASSPS, false, &plane);

	  
		_hoops_HCAGA = _hoops_ACPIA(
									_hoops_PSSPS, 
									_hoops_HRPPA,
									_hoops_ASSPS,
									&plane, 
									points2,
									_hoops_SPPPA,
									_hoops_HIIPR,
									_hoops_CRPPA, _hoops_RSPSA, 0,true);
	
	}

	delete [] _hoops_PSSPS;
	delete [] _hoops_ASSPS;

	return _hoops_HCAGA;
}



/* _hoops_RIIRA:
 * _hoops_CPSSR _hoops_IH _hoops_RH _hoops_HSPP _hoops_PPR _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_III _hoops_CAGH _hoops_GPP _hoops_PGAP _hoops_ASRPA _hoops_HSRAA _hoops_PISPS (_hoops_SCH 
 * _hoops_GRS _hoops_SHH _hoops_HPGR _hoops_ICRP _hoops_SPR _hoops_IH _hoops_SGCS _hoops_RSSI).  _hoops_IPCP _hoops_AAPI _hoops_ARCRA _hoops_RPP _hoops_PPR _hoops_RGAR _hoops_RPP
 *	 _hoops_IRS) _hoops_RH _hoops_III _hoops_CAGH _hoops_ICHIA _hoops_HPGR _hoops_CHGC _hoops_SPR _hoops_IIGR _hoops_PSRPA'_hoops_GRI _hoops_SPPR; _hoops_PAR
 *	 _hoops_RCSR) _hoops_RH _hoops_HSPP _hoops_PPSR _hoops_HRGR _hoops_GIHRR _hoops_ASSA _hoops_HCR _hoops_IIGR _hoops_PSRPA'_hoops_GRI _hoops_SPPR
 */
bool _hoops_IIPPA(
	Point const *	points1, 
	int				_hoops_HRPPA,
	const int *		_hoops_AIIPR,
	_hoops_ARPA const *	_hoops_IRPPA,
	Point const *	points2,
	int				_hoops_SPPPA,
	const int *		_hoops_HIIPR,
	_hoops_ARPA const *	_hoops_CRPPA,
	Point *			_hoops_RSPSA)
{
	Point			line[3];
	Point *			_hoops_RHPPA = &line[0];
	Point *			_hoops_AHPPA = &line[2];

	int				index = (_hoops_HIIPR ? _hoops_HIIPR[0] : 0);

	Point const *	prev = &points2[index];

	bool			_hoops_PHPPA = (*prev * *_hoops_IRPPA > 0);

  	for (int i = 0; i < _hoops_SPPPA; i++) { 
		Point const *	pt;

		index = (_hoops_HIIPR ? _hoops_HIIPR[i] : i);
		prev = &points2[index];

		if (i+1 < _hoops_SPPPA) {
			index = (_hoops_HIIPR ? _hoops_HIIPR[i+1] : i+1);
			pt = &points2[index];
		}
		else {
			index = (_hoops_HIIPR ? _hoops_HIIPR[0] : 0);
			pt = &points2[index]; /* _hoops_ARGAR _hoops_AARI */
		}

		bool	in = (*pt * *_hoops_IRPPA > 0);

 		if (in != _hoops_PHPPA ) {
			*_hoops_RHPPA = _hoops_IRPPA->_hoops_HRAGI(*pt, *prev);
			_hoops_RHPPA++;
			if (_hoops_RHPPA >= _hoops_AHPPA)
				break;
		}

		_hoops_PHPPA = in;
	}

	/* _hoops_HA _hoops_SR _hoops_HS _hoops_RH _hoops_III _hoops_CAGH (_hoops_RPP _hoops_SCH _hoops_HICP) */
	if (_hoops_RHPPA == line) {
		/* _hoops_HHPPA, _hoops_APSH _hoops_PII _hoops_SR _hoops_SARS'_hoops_RA _hoops_RHHR _hoops_RH _hoops_IPPA _hoops_HPGR _hoops_HCR (_hoops_IHPPA, _hoops_PSP _hoops_RASAR) */
		return 0;  
	}

	line[2] = _hoops_AICIR(line[0], line[1]);
 
 	if (_hoops_IISPS(&line[0], points1, _hoops_HRPPA, _hoops_AIIPR, _hoops_IRPPA, _hoops_CRPPA) ||
		_hoops_AHHHA(&line[2], points1, _hoops_HRPPA, _hoops_AIIPR, _hoops_IRPPA, 0.0f) == _hoops_HPHHA) {

		if (_hoops_RSPSA)
			*_hoops_RSPSA = line[0];

		return true;
	}
	
	return false;
}


#define _hoops_ISSPS 0
#define _hoops_CSSPS 1
#define _hoops_SSSPS 2

local int _hoops_GGGHS(
	int				_hoops_HRPPA, 
	const int *		_hoops_AIIPR, 
	Point const *	points1, 
	_hoops_ARPA const *	plane, 
	Point **		_hoops_RHPPA, 
	Point const *	_hoops_AHPPA,
	bool			_hoops_RGGHS, 
	bool			_hoops_PRRIA = true)
{
	_hoops_ARPA const *	_hoops_CRPPA;
	_hoops_ARPA			_hoops_AGGHS;

	if (_hoops_RGGHS){
		_hoops_AGGHS = *plane;
		
		if (_hoops_PRRIA)
			_hoops_AGGHS.d = plane->d + _hoops_CACIR*2.0f;
		else
			_hoops_AGGHS.d = plane->d - _hoops_CACIR*2.0f;

		_hoops_CRPPA = &_hoops_AGGHS;
	}
	else
		_hoops_CRPPA = plane;

	int index = (_hoops_AIIPR ? _hoops_AIIPR[0] : 0);

	Point const * prev = &points1[index];

	float _hoops_HGII = *_hoops_CRPPA * *prev;

	int _hoops_PHPPA;
	if (_hoops_HGII > -_hoops_CACIR && _hoops_HGII < _hoops_CACIR) {
		_hoops_PHPPA = 2;
	}
	else { 
		if (_hoops_HGII>0.0f)
			_hoops_PHPPA = 0;
		else 
			_hoops_PHPPA = 1;
	}

	bool _hoops_PGGHS[3];
	_hoops_PGGHS[0] = false;
	_hoops_PGGHS[1] = false;
	_hoops_PGGHS[_hoops_PHPPA] = true;

	for (int i = 0; i < _hoops_HRPPA; i++) { 
		index = (_hoops_AIIPR ? _hoops_AIIPR[i] : i);
		prev = &points1[index];

		Point const * pt;
		if (i+1 < _hoops_HRPPA) {
			index = (_hoops_AIIPR ? _hoops_AIIPR[i+1] : i+1);
			pt = &points1[index];
		}
		else {
			index = (_hoops_AIIPR ? _hoops_AIIPR[0] : 0);
			pt = &points1[index]; /* _hoops_ARGAR _hoops_AARI */
		}
	
		float _hoops_HGII = *_hoops_CRPPA * *pt;

		int in;
		if (_hoops_HGII > -_hoops_CACIR && _hoops_HGII < _hoops_CACIR) {
			in = 2;
		}
		else {
			if (_hoops_HGII>0.0f)
				in = 0;
			else
				in = 1;
		}

		_hoops_PGGHS[in] = true;

		if (_hoops_RHPPA && in != _hoops_PHPPA) {
			_hoops_IPPPA(pt, prev, _hoops_CRPPA, *_hoops_RHPPA);

			(*_hoops_RHPPA)++;

			if ((*_hoops_RHPPA) >= _hoops_AHPPA)
				break;
		}

		_hoops_PHPPA = in;
	}

	if (!_hoops_PGGHS[0] && !_hoops_PGGHS[1])
		return _hoops_SSSPS;
	else if (!_hoops_PGGHS[0] || !_hoops_PGGHS[1])
		return _hoops_ISSPS;
	else 
		return _hoops_CSSPS;
}

 local void _hoops_HGGHS(Point const *points1, int _hoops_HRPPA, const int *	_hoops_AIIPR, Point const * points2, int _hoops_SPPPA, const int *_hoops_HIIPR, _hoops_SASC *_hoops_RSPSA)
 {
	 _hoops_SASC _hoops_PIGCR;
	 for (int i = 0; i<_hoops_HRPPA;i++)
		_hoops_RSPSA->Merge(points1[_hoops_AIIPR[i]]);
	 for (int i = 0; i<_hoops_SPPPA;i++)
		_hoops_PIGCR.Merge(points2[_hoops_HIIPR[i]]);
	 _hoops_RSPSA->_hoops_PGPGP(_hoops_PIGCR);
 }



/* _hoops_RIIRA:
 * _hoops_CPSSR _hoops_IH _hoops_RH _hoops_HSPP _hoops_PPR _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_III _hoops_CAGH _hoops_GPP _hoops_PGAP _hoops_ASRPA _hoops_HSRAA _hoops_PISPS (_hoops_SCH 
 * _hoops_GRS _hoops_SHH _hoops_HPGR _hoops_ICRP _hoops_SPR _hoops_IH _hoops_SGCS _hoops_RSSI).  _hoops_IPCP _hoops_AAPI _hoops_ARCRA _hoops_RPP _hoops_PPR _hoops_RGAR _hoops_RPP
 *	 _hoops_IRS) _hoops_RH _hoops_III _hoops_CAGH _hoops_ICHIA _hoops_HPGR _hoops_CHGC _hoops_SPR _hoops_IIGR _hoops_PSRPA'_hoops_GRI _hoops_SPPR; _hoops_PAR
 *	 _hoops_RCSR) _hoops_RH _hoops_HSPP _hoops_PPSR _hoops_HRGR _hoops_GIHRR _hoops_ASSA _hoops_HCR _hoops_IIGR _hoops_PSRPA'_hoops_GRI _hoops_SPPR
 */
bool _hoops_ACPIA(
	Point const *		points1, 
	int					_hoops_HRPPA,
	const int *			_hoops_AIIPR,
	_hoops_ARPA const *		_hoops_IRPPA,
	Point const *		points2,
	int					_hoops_SPPPA,
	const int *			_hoops_HIIPR,
	_hoops_ARPA const *		_hoops_CRPPA,
	Point *				_hoops_RSPSA,
	_hoops_SASC		*_hoops_HRRIA,
	bool				_hoops_ASPSA,
	bool				_hoops_PRRIA)
{

	Point line[3];
 	Point * _hoops_RHPPA = &line[0];
	Point * _hoops_AHPPA = &line[2];

	int _hoops_IGGHS = _hoops_GGGHS(_hoops_SPPPA, _hoops_HIIPR, points2, _hoops_IRPPA, &_hoops_RHPPA, _hoops_AHPPA, false);

	if (!_hoops_ASPSA) {
		if (_hoops_IGGHS!=_hoops_CSSPS) {
			_hoops_RHPPA = &line[0];

 			if (_hoops_GGGHS(_hoops_SPPPA, _hoops_HIIPR, points2, _hoops_IRPPA, &_hoops_RHPPA, _hoops_AHPPA,true, _hoops_PRRIA) != _hoops_CSSPS)
				return false;
			else {
	 			if (_hoops_GGGHS(_hoops_HRPPA, _hoops_AIIPR, points1, _hoops_CRPPA, 0, 0,false)!=_hoops_CSSPS)
				{
 					if ( _hoops_GGGHS(_hoops_HRPPA, _hoops_AIIPR, points1, _hoops_CRPPA, 0, 0,true, _hoops_PRRIA) != _hoops_CSSPS)
						return false;				
				}
			}
		}
		else {
 			if (_hoops_GGGHS(_hoops_HRPPA, _hoops_AIIPR, points1, _hoops_CRPPA, 0, 0,false) != _hoops_CSSPS) {
 				if (_hoops_GGGHS(_hoops_HRPPA, _hoops_AIIPR, points1, _hoops_CRPPA, 0, 0,true, _hoops_PRRIA) != _hoops_CSSPS)
					return false;				
			}
		}
	}


	/* _hoops_HA _hoops_SR _hoops_HS _hoops_RH _hoops_III _hoops_CAGH (_hoops_RPP _hoops_SCH _hoops_HICP) */
	if (_hoops_RHPPA == line) {
		
		if (_hoops_ASPSA && _hoops_IGGHS == _hoops_SSSPS) {
			_hoops_SASC _hoops_RSPSA;
			for (int i=0;i<_hoops_HRPPA;i++) {
				int index = (_hoops_AIIPR ? _hoops_AIIPR[i] : i);
				Point const *	p = &points1[index];
				if (_hoops_AHHHA(p, points2, _hoops_SPPPA, _hoops_HIIPR, _hoops_CRPPA, 0.00001f) == _hoops_HPHHA)
				{
					if (_hoops_HRRIA)
					{
						_hoops_HGGHS(points1, _hoops_HRPPA, _hoops_AIIPR, points2, _hoops_SPPPA, _hoops_HIIPR,&_hoops_RSPSA);
 						_hoops_HRRIA->Merge(_hoops_RSPSA);
					}
					goto _hoops_CGGHS;
				}
			}

			for (int i=0;i<_hoops_SPPPA;i++) {
				int index = (_hoops_HIIPR ? _hoops_HIIPR[i] : i);
				Point const *	p = &points2[index];
				if (_hoops_AHHHA(p, points1, _hoops_HRPPA, _hoops_AIIPR, _hoops_IRPPA, 0.00001f) == _hoops_HPHHA)
				{
					if (_hoops_HRRIA)
					{
						_hoops_HGGHS(points1, _hoops_HRPPA, _hoops_AIIPR, points2, _hoops_SPPPA, _hoops_HIIPR,&_hoops_RSPSA);
 						_hoops_HRRIA->Merge(_hoops_RSPSA);
					}
					goto _hoops_CGGHS;
				}
			}

			for (int i=0; i<_hoops_SPPPA; i++) {
				Point _hoops_SGGHS[2];

				int index = (_hoops_HIIPR ? _hoops_HIIPR[i] : i);
				
				_hoops_SGGHS[0] = points2[index];

				index = (i<_hoops_SPPPA-1) ? (_hoops_HIIPR ? _hoops_HIIPR[i+1] : i+1) : (_hoops_HIIPR ? _hoops_HIIPR[0] : 0);

				_hoops_SGGHS[1] = points2[index];

				if (_hoops_SCSPS(_hoops_SGGHS, points1, _hoops_HRPPA, _hoops_AIIPR, _hoops_IRPPA))
				{
					if (_hoops_HRRIA)
					{
						_hoops_HGGHS(points1, _hoops_HRPPA, _hoops_AIIPR, points2, _hoops_SPPPA, _hoops_HIIPR,&_hoops_RSPSA);
 						_hoops_HRRIA->Merge(_hoops_RSPSA);
					}
					goto _hoops_CGGHS;
				}
 			}

		}

		/* _hoops_HHPPA, _hoops_APSH _hoops_PII _hoops_SR _hoops_SARS'_hoops_RA _hoops_RHHR _hoops_RH _hoops_IPPA _hoops_HPGR _hoops_HCR (_hoops_IHPPA, _hoops_PSP _hoops_RASAR) */
		return false;  
	}

	line[2] = _hoops_AICIR(line[0], line[1]);
 
	if (_hoops_ASPSA) {
	 	if (!_hoops_IISPS(line, points1, _hoops_HRPPA, _hoops_AIIPR, _hoops_IRPPA, _hoops_CRPPA) &&
			_hoops_AHHHA(&line[2], points1, _hoops_HRPPA, _hoops_AIIPR, _hoops_IRPPA, 0.00001f) != _hoops_HPHHA)
			return false;
	}
	else {
 		if (!_hoops_IISPS(line, points1, _hoops_HRPPA, _hoops_AIIPR, _hoops_IRPPA, _hoops_CRPPA,_hoops_CACIR) &&
			_hoops_AHHHA(&line[2], points1, _hoops_HRPPA, _hoops_AIIPR, _hoops_IRPPA, 0) != _hoops_HPHHA)
			return false;
	}

	if (_hoops_HRRIA)
	{
		_hoops_SCPSA(line, points1, _hoops_HRPPA, _hoops_AIIPR, _hoops_IRPPA, 0.00001f);
		_hoops_HRRIA->Merge(line[0]);
		_hoops_HRRIA->Merge(line[1]);
	}

_hoops_CGGHS:
	if (_hoops_RSPSA)
		*_hoops_RSPSA = line[0];
	
 
	return true;
}




bool _hoops_HIPPA(
	Point const *	points, 
	int				len,
	const int *		_hoops_GAHI,
	_hoops_ARPA const &	plane) 
{	 
	if (_hoops_GAHI == null) {
		bool _hoops_GRGHS = (plane * *points > 0);
		
		for (int i = 1; i < len; i++) {
			points++;

			/* _hoops_RPP _hoops_SR _hoops_SHHP _hoops_HII _hoops_SPR _hoops_PPAP _hoops_IIGR _hoops_RH _hoops_IPPA _hoops_IS _hoops_RH _hoops_RII */
			if (_hoops_GRGHS != (plane * *points > 0))
				return true;
		}
	}
	else {
		Point const *	pt =  &points[_hoops_GAHI[0]];
		float			_hoops_SSRP = plane * *pt;

		if (_hoops_SSRP<_hoops_CACIR && _hoops_SSRP>-_hoops_CACIR) {
			float dist = HI_Sqrt(pt->x * pt->x + pt->y * pt->y + pt->z * pt->z);

			float _hoops_RRGHS = dist*_hoops_SSRP;

			if (_hoops_RRGHS<_hoops_CACIR && _hoops_RRGHS>-_hoops_CACIR)
				return true;
		}
		
		bool _hoops_GRGHS = _hoops_SSRP>0;

		for (int i = 1; i < len; i++) {
			pt = &points[_hoops_GAHI[i]];

			/* _hoops_RPP _hoops_SR _hoops_SHHP _hoops_HII _hoops_SPR _hoops_PPAP _hoops_IIGR _hoops_RH _hoops_IPPA _hoops_IS _hoops_RH _hoops_RII */
			if (_hoops_GRGHS != (pt, plane * *pt > 0))
				return true;
		}
	}

	return false;
}


bool _hoops_PSPSA(
	Point const *	points, 
	int				len,
	const int *		_hoops_GAHI,
	_hoops_ARPA const &	plane, 
	float			_hoops_RCPIA) 
{
	Point const *	pt = points;

	if (_hoops_GAHI != null)
		pt = &points[_hoops_GAHI[0]];

	float min, max;
	min = max = plane * *pt;

	for (int i = 1; i < len; i++) {
		if (_hoops_GAHI != null)
			pt = &points[_hoops_GAHI[i]];
		else
			pt++;

		float _hoops_SSRP = plane * *pt;

		if (_hoops_SSRP < min)
			min = _hoops_SSRP;
		else if (_hoops_SSRP > max)
			max = _hoops_SSRP;
	}

	if (min < -_hoops_RCPIA && max > _hoops_RCPIA)
		return true;

	return false;
}

/*_hoops_HICRR*/
#define _hoops_GIAHA 8
bool _hoops_APHIA(
	Point const *	_hoops_SRHC, 
	int				len,
	int const *		_hoops_GAHI, 
	bool			_hoops_HSPSA,
	_hoops_ARPA alter *	_hoops_RGHIA) 
{
	Point			min, max;

	min = max = _hoops_SRHC[_hoops_GAHI[0]];

	for (int i = 1; i < len; ++i) {
		Point	p = _hoops_SRHC[_hoops_GAHI[i]];

		min.x = _hoops_AHIA (min.x, p.x);
		min.y = _hoops_AHIA (min.y, p.y);
		min.z = _hoops_AHIA (min.z, p.z);
		max.x = _hoops_IAAA (max.x, p.x);
		max.y = _hoops_IAAA (max.y, p.y);
		max.z = _hoops_IAAA (max.z, p.z);
	}

	float	tolerance = 0.001f * _hoops_IAAA (max.x - min.x, max.y - min.y, max.z - min.z);

	Point	_hoops_ARGHS[_hoops_GIAHA];
	Point *	points;

	if (len > _hoops_GIAHA)
		ALLOC_ARRAY(points, len, Point);
	else
		points = _hoops_ARGHS;

	int		count = 0;

	/* _hoops_IPS _hoops_RH _hoops_RSSA _hoops_CRGR _hoops_IRS _hoops_ISIAR _hoops_SRHR */
	if (!_hoops_HSPSA) {
		for (int i = 0; i < len; i++) {
			points[count] = _hoops_SRHC[_hoops_GAHI[i]];

			++count;
			if (count > 1) {
				if (Abs (points[count-1].x - points[count-2].x) < tolerance &&
					Abs (points[count-1].y - points[count-2].y) < tolerance &&
					Abs (points[count-1].z - points[count-2].z) < tolerance)
					--count;
			}
		}
	}
	else {
		for (int i = 0; i < len; i++) {
			points[count] = _hoops_SRHC[_hoops_GAHI[len-i-1]];

			++count;

			if (count > 1) {
				if (Abs (points[count-1].x - points[count-2].x) < tolerance &&
					Abs (points[count-1].y - points[count-2].y) < tolerance &&
					Abs (points[count-1].z - points[count-2].z) < tolerance)
					--count;
			}
		}
	}

	if (count > 1) {
		if (Abs (points[count-1].x - points[0].x) < tolerance &&
			Abs (points[count-1].y - points[0].y) < tolerance &&
			Abs (points[count-1].z - points[0].z) < tolerance)
			--count;
	}

	bool	_hoops_IA = false;

	if (count >= 3)
		_hoops_IA = HI_Figure_Plane_From_Points (len, points, _hoops_RGHIA);

	if (points != _hoops_ARGHS)
		FREE_ARRAY(points, len, Point);

	return _hoops_IA;
}


void _hoops_GAHPA(
	VBSP *			tree, 
	int				point_count, 
	Point const *	points, 
	int				face_list_length, 
	const int *		face_list, 
	bool			_hoops_HSPSA) 
{
	const int *		_hoops_GAHI = face_list;
	const int *		end = _hoops_GAHI + face_list_length;
	int				index = 0;

 	while (_hoops_GAHI < end) {
		/* _hoops_GA'_hoops_RA _hoops_IAIC _hoops_HHHR _hoops_RSSI (_hoops_HAS._hoops_IAS. _hoops_PCCPR _hoops_GGR _hoops_RSSI) */
		if (*_hoops_GAHI < 0) {
			_hoops_GAHI += -(*_hoops_GAHI) + 1;
			continue;
		}

		int len = _hoops_GAHI[0];

		_hoops_ARPA	plane;
		if (_hoops_APHIA(points, len, _hoops_GAHI+1, _hoops_HSPSA, &plane)) {
			_hoops_SHPPA *	face = _hoops_SIIIA(0, len, _hoops_GAHI+1, points, null, plane, index);
			HI_BSP_Insert(tree, face, null);
		}

		index++;
		_hoops_GAHI += (*_hoops_GAHI) + 1;
	}
	UNREFERENCED(point_count);
}


void _hoops_SACHA(
	VBSP *			tree, 
	int				point_count, 
	const Point *	points,
	float			tolerance)
{
	for (int i = 0; i < point_count;i++){	
  		_hoops_ACHHA * vertex = _hoops_HCPSA(&points[i], tolerance, i);
		HI_BSP_Insert(tree, vertex, null);
	}
}


/* _hoops_PGAA */
void _hoops_CHHIA(
	Point const *			points, 
	_hoops_HRPA const *		matrix,
	int						len,
	int const *				_hoops_GAHI, 
	_hoops_SASC alter &	_hoops_ISPSA) 
{
	ASSERT(len > 0);

	Point p;

	if (matrix)
		HI_Compute_Transformed_Points(1, &points[_hoops_GAHI[0]], &matrix->elements[0][0], &p);
	else
		p = points[_hoops_GAHI[0]];

	_hoops_ISPSA = _hoops_SASC(1, &p);

	for (int i = 1; i < len; i++) {
		if (matrix)
			HI_Compute_Transformed_Points(1, &points[_hoops_GAHI[i]], &matrix->elements[0][0], &p);
		else
			p = points[_hoops_GAHI[i]];

		_hoops_ISPSA.Merge(1, &p);
	}
}

/* _hoops_RPGP _hoops_IS _hoops_CACH _hoops_RPP "_hoops_SGPSH" _hoops_SSPAA _hoops_GIAA _hoops_RH _hoops_PRGHS _hoops_PAPR _hoops_HPP _hoops_PSSIA _hoops_RH _hoops_HSSP _hoops_PAPR 
 * _hoops_HPP {"_hoops_RSSA","_hoops_GHIIA","_hoops_HRGHS"} _hoops_IGIAR _hoops_RH _hoops_GSSR _hoops_IIGR _hoops_RGCI "_hoops_IPPA".  _hoops_CGP _hoops_RH _hoops_PPSR _hoops_SSPAA 
 * _hoops_GIAA "_hoops_CCPCR" _hoops_IIGR _hoops_RH _hoops_PRGHS, _hoops_ASRC _hoops_PIRA _hoops_HRGR _hoops_IRGHS.  

  */
int _hoops_AHHHA(
	Point const *	pt,
	Point const *	points1, 
	int				len,
	int const *		_hoops_AIIPR,
	_hoops_ARPA const *	_hoops_IRPPA,
	float			_hoops_RCPIA)
{	 
	int _hoops_HPIS = _hoops_HPHHA;

	/* _hoops_ISAP _hoops_PAH _hoops_RASAR _hoops_CCA _hoops_IRS _hoops_ARHAR _hoops_HSP */
	if (len < 3)
		return 0;

	int	_hoops_CRGHS = 1;
	int in = 0;

	for (int i = 0; i < len; i++) {	
		Point const * _hoops_GAPPA = &points1[_hoops_AIIPR[i]];
		Point const * _hoops_RAPPA;

		if (i+1 < len)
			_hoops_RAPPA = &points1[_hoops_AIIPR[i+1]];
		else
			_hoops_RAPPA = &points1[_hoops_AIIPR[i+1-len]]; /* _hoops_ARGAR _hoops_AARI */

		Vector _hoops_ARGCR = *_hoops_RAPPA - *_hoops_GAPPA;

		bool status = HI_Normalize(&_hoops_ARGCR);

		_hoops_ARPA _hoops_AAPPA;

		HI_Compute_Cross_Product(&_hoops_ARGCR, (Vector *)_hoops_IRPPA, (Vector *)&_hoops_AAPPA);

		if (!HI_Normalize((Vector *)&_hoops_AAPPA))
			status = false;

		if (!status)
			continue;

		/* _hoops_GHGP _hoops_IHSR _hoops_HRGR -(_hoops_PAPPA + _hoops_HPP + _hoops_IIHCR) */
		_hoops_AAPPA.d = -(_hoops_RAPPA->x*_hoops_AAPPA.a + _hoops_RAPPA->y*_hoops_AAPPA.b + _hoops_RAPPA->z*_hoops_AAPPA.c);

		if (_hoops_CRGHS) {
			Point const * _hoops_CAPPA;
			/* _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA _hoops_RPP _hoops_RH _hoops_HSP _hoops_HRGR _hoops_SRGGA _hoops_PAR _hoops_HAPPA, _hoops_HIH _hoops_SR
			 * _hoops_PAH _hoops_HPCAR _hoops_SGS _hoops_RH 3_hoops_IAPPA _hoops_PPSR _hoops_HRGR "_hoops_GGR", _hoops_HIS _hoops_SR _hoops_SAHR _hoops_PHHR _hoops_HPP _hoops_SGS. _hoops_PS _hoops_PAH _hoops_HGCR
			 * _hoops_SGGR _hoops_CCA _hoops_GHGA _hoops_RGR _hoops_RGAR _hoops_ARR, _hoops_PGGA "_hoops_GGR" _hoops_GRS _hoops_SHH _hoops_RH _hoops_PSHR _hoops_IH _hoops_HCR _hoops_SPPR*/
			if (i+2 < len)
				_hoops_CAPPA = &points1[_hoops_AIIPR[i+2]];
			else
				_hoops_CAPPA = &points1[_hoops_AIIPR[i+2-len]]; /* _hoops_ARGAR _hoops_AARI */

			in = (_hoops_AAPPA * *_hoops_CAPPA > 0);
			
			_hoops_CRGHS = 0;
		}

		float _hoops_SRGHS = _hoops_AAPPA * *pt;

		if (in > 0) {
			if (_hoops_SRGHS <= 0) {
				if (_hoops_SRGHS > -_hoops_RCPIA)
					_hoops_HPIS = _hoops_IPHHA;
				else
					return _hoops_CPHHA;
			}
		}
		else {
			if (_hoops_SRGHS >= 0) {
 				if (_hoops_SRGHS < _hoops_RCPIA)
					_hoops_HPIS = _hoops_IPHHA;
				else
					return _hoops_CPHHA;
			}
		}
	}

	if (_hoops_CRGHS)
		return _hoops_CPHHA; /* _hoops_ISAP _hoops_HSRAA _hoops_IRS _hoops_HSP _hoops_GRPAA _hoops_RSSA _hoops_CHR _hoops_HCR _hoops_GARAA */

	return _hoops_HPIS;
} 


/* _hoops_RPGP _hoops_IS _hoops_CACH _hoops_RPP "_hoops_SGPSH" _hoops_SSPAA _hoops_GIAA _hoops_RH _hoops_PRGHS _hoops_PAPR _hoops_HPP _hoops_PSSIA _hoops_RH _hoops_HSSP _hoops_PAPR 
 * _hoops_HPP {"_hoops_RSSA","_hoops_GHIIA","_hoops_HRGHS"} _hoops_IGIAR _hoops_RH _hoops_GSSR _hoops_IIGR _hoops_RGCI "_hoops_IPPA".  _hoops_CGP _hoops_RH _hoops_PPSR _hoops_SSPAA 
 * _hoops_GIAA "_hoops_CCPCR" _hoops_IIGR _hoops_RH _hoops_PRGHS, _hoops_ASRC _hoops_PIRA _hoops_HRGR _hoops_IRGHS.  

  */
void _hoops_SCPSA(
	Point		   *line,
	Point const *	points1, 
	int				len,
	int const *		_hoops_AIIPR,
	_hoops_ARPA const *	_hoops_IRPPA,
	float			_hoops_RCPIA)
{	 	
	/* _hoops_ISAP _hoops_PAH _hoops_RASAR _hoops_CCA _hoops_IRS _hoops_ARHAR _hoops_HSP */
	if (len < 3)
		return;

	int	_hoops_CRGHS = 1;
	int in = 0;

	for (int i = 0; i < len; i++) {	
		Point const * _hoops_GAPPA = &points1[_hoops_AIIPR[i]];
		Point const * _hoops_RAPPA;

		if (i+1 < len)
			_hoops_RAPPA = &points1[_hoops_AIIPR[i+1]];
		else
			_hoops_RAPPA = &points1[_hoops_AIIPR[i+1-len]]; /* _hoops_ARGAR _hoops_AARI */

		Vector _hoops_ARGCR = *_hoops_RAPPA - *_hoops_GAPPA;

		bool status = HI_Normalize(&_hoops_ARGCR);

		_hoops_ARPA _hoops_AAPPA;

		HI_Compute_Cross_Product(&_hoops_ARGCR, (Vector *)_hoops_IRPPA, (Vector *)&_hoops_AAPPA);

		if (!HI_Normalize((Vector *)&_hoops_AAPPA))
			status = false;

		if (!status)
			continue;

		/* _hoops_GHGP _hoops_IHSR _hoops_HRGR -(_hoops_PAPPA + _hoops_HPP + _hoops_IIHCR) */
		_hoops_AAPPA.d = -(_hoops_RAPPA->x*_hoops_AAPPA.a + _hoops_RAPPA->y*_hoops_AAPPA.b + _hoops_RAPPA->z*_hoops_AAPPA.c);

		if (_hoops_CRGHS) {
			Point const * _hoops_CAPPA;
			/* _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA _hoops_RPP _hoops_RH _hoops_HSP _hoops_HRGR _hoops_SRGGA _hoops_PAR _hoops_HAPPA, _hoops_HIH _hoops_SR
			 * _hoops_PAH _hoops_HPCAR _hoops_SGS _hoops_RH 3_hoops_IAPPA _hoops_PPSR _hoops_HRGR "_hoops_GGR", _hoops_HIS _hoops_SR _hoops_SAHR _hoops_PHHR _hoops_HPP _hoops_SGS. _hoops_PS _hoops_PAH _hoops_HGCR
			 * _hoops_SGGR _hoops_CCA _hoops_GHGA _hoops_RGR _hoops_RGAR _hoops_ARR, _hoops_PGGA "_hoops_GGR" _hoops_GRS _hoops_SHH _hoops_RH _hoops_PSHR _hoops_IH _hoops_HCR _hoops_SPPR*/
			if (i+2 < len)
				_hoops_CAPPA = &points1[_hoops_AIIPR[i+2]];
			else
				_hoops_CAPPA = &points1[_hoops_AIIPR[i+2-len]]; /* _hoops_ARGAR _hoops_AARI */

			in = (_hoops_AAPPA * *_hoops_CAPPA > 0);
			
			_hoops_CRGHS = 0;
		}

		float _hoops_GAGHS = _hoops_AAPPA * line[0];
		float _hoops_RAGHS = _hoops_AAPPA * line[1];

		if (in > 0) {
			if (_hoops_GAGHS < _hoops_RCPIA && _hoops_RAGHS > -_hoops_RCPIA) 
				_hoops_IPPPA(&line[0], &line[1], &_hoops_AAPPA, &line[0]);
			else if (_hoops_GAGHS > -_hoops_RCPIA && _hoops_RAGHS < _hoops_RCPIA) 
				_hoops_IPPPA(&line[0], &line[1], &_hoops_AAPPA, &line[1]);
 			
		}
		else {
 			if (_hoops_GAGHS < _hoops_RCPIA && _hoops_RAGHS > -_hoops_RCPIA) 
				_hoops_IPPPA(&line[0], &line[1], &_hoops_AAPPA, &line[1]);
			else if (_hoops_GAGHS > -_hoops_RCPIA && _hoops_RAGHS < _hoops_RCPIA) 
				_hoops_IPPPA(&line[0], &line[1], &_hoops_AAPPA, &line[0]);
 			
		}
	
	}

 
 } 







#define _hoops_AAGHS (1e-10f)
int _hoops_PPHHA(
	Point const *		points, 
	_hoops_SHPPA const *	face,
	Point const *		start, 
	Vector const *		direction, 
	float alter *		_hoops_CSPSA,
	Point alter *		_hoops_PAGHS)
{
	float _hoops_HAGHS = Vector(face->plane)._hoops_SSRP(*direction);

	float _hoops_IAGHS = Vector(face->plane)._hoops_SSRP(Vector(start->x, start->y, start->z));

	if (-_hoops_AAGHS < _hoops_HAGHS && _hoops_HAGHS < _hoops_AAGHS) {

		//_hoops_AIIC _hoops_CAGHS = _hoops_HSP->_hoops_IPPA->_hoops_GHGP + _hoops_SAGHS;
		//_hoops_AIIC _hoops_GPGHS = 1e-5f * _hoops_RPGHS(_hoops_HSPP->_hoops_SISR*_hoops_HSPP->_hoops_SISR + _hoops_HSPP->_hoops_HAPC*_hoops_HSPP->_hoops_HAPC + _hoops_HSPP->_hoops_SSH*_hoops_HSPP->_hoops_SSH);
		//_hoops_RPP (-_hoops_GPGHS < _hoops_CAGHS && _hoops_CAGHS < _hoops_GPGHS)
		return _hoops_CPHHA;
	}

	float t = -(face->plane.d + _hoops_IAGHS)/_hoops_HAGHS;

	if (_hoops_CSPSA)
		*_hoops_CSPSA = t;

	if (t < 0)
		return _hoops_CPHHA;

	Point _hoops_SPCIR = *start + *direction * t;

	float _hoops_APGHS = direction->length();
	float dist = t * _hoops_APGHS;
	float _hoops_PSPHH = fabs(_hoops_SPCIR.x) + fabs(_hoops_SPCIR.y) + fabs(_hoops_SPCIR.z);
	float _hoops_RCPIA = MAX(_hoops_PSPHH, dist) * 0.0001f;

	if (_hoops_PAGHS)
		*_hoops_PAGHS = _hoops_SPCIR;

	if (!face->bbox._hoops_HPCIR(_hoops_SPCIR, _hoops_RCPIA))
		return _hoops_CPHHA;

	return _hoops_AHHHA(
			&_hoops_SPCIR,
			points,
			face->len,
			face->_hoops_GIPPA,
			&face->plane,
			_hoops_RCPIA);
}





int _hoops_SGHIA(
	Point const *points, 
	_hoops_SHPPA const *face,
	Point const *p1, 
	Point const *p2)
{
	Vector _hoops_ARGCR;
	float t;
	int result;

	_hoops_ARGCR.x = p2->x - p1->x;
	_hoops_ARGCR.y = p2->y - p1->y;
	_hoops_ARGCR.z = p2->z - p1->z;
	result = _hoops_PPHHA(points, face, p1, &_hoops_ARGCR, &t,0);
	if (result == _hoops_HPHHA && 
		t > 1) {
		return _hoops_CPHHA;
	}
	else
		return result;
}



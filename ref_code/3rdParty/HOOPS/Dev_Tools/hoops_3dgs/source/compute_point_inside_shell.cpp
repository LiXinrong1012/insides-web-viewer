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
 * $Id: obf_tmp.txt 1.96 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"

#ifndef _hoops_SSAPA 

#include "hc_proto.h"
#include "hi_proto.h"
#include "adt.h"
#include "csutil.h"

GLOBAL_FUNCTION bool HI_Compute_Intersect_Polyline_Nonzero (
	_hoops_AIGPR *	_hoops_RIGC,
	VBSP *_hoops_SGHHA,
	int point_count1, 
	Point const *points1, 
	int face_list_length1, 
	int const *face_list1,
	int point_count2, 
	Point const *points2, 
	int face_list_length2,
	int const *_hoops_ASPH);

typedef VArray<_hoops_SHPPA*> _hoops_GRHHA;
typedef VArray<float*> _hoops_RRHHA;

struct _hoops_ARHHA {
	Point start;
	Vector direction;
	_hoops_GRHHA *_hoops_PSRGA; /* _hoops_PCCP _hoops_CRPR _hoops_IIGR _hoops_CICRR _hoops_IS _hoops_HSP _hoops_AIIS */
	_hoops_RRHHA *_hoops_SSGPA; /* _hoops_PCCP _hoops_CRPR _hoops_IIGR _hoops_CICRR _hoops_IS _hoops_PHRP _hoops_IS _hoops_IHGC _hoops_IAHI */
	bool abort;
};


struct _hoops_PRHHA {
	_hoops_AIGPR * _hoops_RIGC;
 	float tolerance;
	Point const *points;
	Point const *_hoops_CIIRR;
	int _hoops_RISRA;
	int *faces;
	int _hoops_RHGIR;
	int * results;
	float * _hoops_HRHHA;
	int *_hoops_IRHHA;
	VBSP *_hoops_CRHHA;
	bool _hoops_SRHHA;
};


struct _hoops_GAHHA {
	_hoops_AIGPR *	_hoops_RIGC;
	Point const *pt;
	float tolerance;
	bool result;
};

struct _hoops_RAHHA {
	int _hoops_GRPPA;
	VBSP *BSP;
};



/* _hoops_PGAA */
local bool _hoops_AAHHA(
		int len, 
		int const *_hoops_GAHI,
		Point const *points, 
		_hoops_ARHHA alter *_hoops_PAHHA) 
{
	int i;
	Point _hoops_GPIS;
	Point const *point;

	_hoops_GPIS.x = _hoops_GPIS.y = _hoops_GPIS.z = 0;
	for (i = 0; i < len; i++) {
		point = &points[_hoops_GAHI[i]];
		_hoops_GPIS.x += point->x;
		_hoops_GPIS.y += point->y;
		_hoops_GPIS.z += point->z;
	}
	_hoops_GPIS.x /= (float)i;
	_hoops_GPIS.y /= (float)i;
	_hoops_GPIS.z /= (float)i;
	_hoops_PAHHA->direction.x = _hoops_GPIS.x - _hoops_PAHHA->start.x;
	_hoops_PAHHA->direction.y = _hoops_GPIS.y - _hoops_PAHHA->start.y;
	_hoops_PAHHA->direction.z = _hoops_GPIS.z - _hoops_PAHHA->start.z;
	return true;
}


local bool _hoops_HAHHA(
		int _hoops_SSPAR,
		int face_list_length, 
		int const *face_list,
		Point const *points, 
		_hoops_ARHHA alter *_hoops_PAHHA) 
{
	int const *_hoops_GAHI, *end;
	int i;

	_hoops_GAHI = face_list;
	end = face_list + face_list_length;
	i = 0;
	while (i < _hoops_SSPAR && _hoops_GAHI < end) {
		if (_hoops_GAHI[0] < 0) {
			_hoops_GAHI += -_hoops_GAHI[0] + 1;
		}
		else {
			_hoops_GAHI += _hoops_GAHI[0] + 1;
			i++;
		}
	}
	if (_hoops_GAHI >= end)
		return false;
	_hoops_AAHHA (_hoops_GAHI[0], _hoops_GAHI+1, points, _hoops_PAHHA);
	return true;
}

local bool _hoops_IAHHA (
		int _hoops_CAHHA,
		_hoops_ARHHA alter *_hoops_PAHHA) 
{
	switch (_hoops_CAHHA) {
		case 0:
			_hoops_PAHHA->direction.x = 1;
			_hoops_PAHHA->direction.y = 0;
			_hoops_PAHHA->direction.z = 0;
			break;
		case 1:
			_hoops_PAHHA->direction.x = 0;
			_hoops_PAHHA->direction.y = 1;
			_hoops_PAHHA->direction.z = 0;
			break;
		case 2:
			_hoops_PAHHA->direction.x = 0;
			_hoops_PAHHA->direction.y = 0;
			_hoops_PAHHA->direction.z = 1;
			break;
		default:
			return false;
	}
	return true;
}




/* _hoops_CRSAR _hoops_IISA _hoops_HII _hoops_IPHRA.  _hoops_SRSAR _hoops_PPR _hoops_SAHHA _hoops_RCPS _hoops_HII _hoops_GPHHA _hoops_RSCRR _hoops_HIGR.
 * _hoops_PASI _hoops_HRS 1 _hoops_PGGA _hoops_SR _hoops_HHGC _hoops_RH _hoops_IPHRA _hoops_IS _hoops_SAS _hoops_HHCPR. 
 * _hoops_RH _hoops_RGAR _hoops_GSASR _hoops_HRGR _hoops_RPP _hoops_SR _hoops_HHGC _hoops_IS _hoops_ICPPA _hoops_RSIH */
local _hoops_CSCAR _hoops_RPHHA (void *_hoops_HCSAR, void *_hoops_IASAR, void *_hoops_CASAR) 
{
	Point *points = (Point *)_hoops_HCSAR;
	_hoops_SHPPA *face = (_hoops_SHPPA *)_hoops_IASAR;
	_hoops_ARHHA *info = (_hoops_ARHHA *)_hoops_CASAR;
	float t, *_hoops_APHHA;
	int result;

	result = _hoops_PPHHA (points, face, &info->start, &info->direction, &t,0);
	switch (result) {
		case _hoops_HPHHA:
			info->_hoops_PSRGA->Append(face);
			ALLOC (_hoops_APHHA, float);
			*_hoops_APHHA = t;
			info->_hoops_SSGPA->Append(_hoops_APHHA);
			break;
		case _hoops_IPHHA:
			info->abort = true;
			break;
		case _hoops_CPHHA:
		default:
			break;
	}
	if (info->abort)
		return VBSP_STATUS_STOP;

	return VBSP_STATUS_CONTINUE;
}


/* _hoops_CRSAR _hoops_IISA _hoops_HII _hoops_RH _hoops_IPHRA.  _hoops_SAHHA _hoops_PPR _hoops_SRSAR _hoops_RCPS _hoops_HII _hoops_RSCRR _hoops_HIGR _hoops_GGR _hoops_GPHHA
 * _hoops_SHR _hoops_HRS _hoops_SPHHA _hoops_PGGA _hoops_SR _hoops_HHGC _hoops_RH _hoops_IPHRA _hoops_IS _hoops_GRHP _hoops_HHCPR */
local _hoops_CSCAR _hoops_GHHHA (void *_hoops_HCSAR, void *_hoops_IASAR, void *_hoops_CASAR) 
{
	_hoops_GAHHA *	info = (_hoops_GAHHA *)_hoops_CASAR;
	Point const *			points = (Point const *)_hoops_HCSAR;
	_hoops_SHPPA *			face = (_hoops_SHPPA *)_hoops_IASAR;
	Point const *			pt = info->pt;
	float					tolerance = info->tolerance;
	_hoops_ARPA const &			plane = face->plane;

	float _hoops_RHHHA = Vector(plane)._hoops_PPSSR();

	if (_hoops_RHHHA < 1e-5f)
		return VBSP_STATUS_CONTINUE;

	/* _hoops_CSGA (_hoops_PAPPA + _hoops_HPP + _hoops_IIHCR + _hoops_GHGP) */
	float equation = plane * *pt;
	
	if (-tolerance > equation || equation > tolerance)
		return VBSP_STATUS_CONTINUE;
	
	int status = _hoops_AHHHA (pt, points, face->len, face->_hoops_GIPPA, &plane, tolerance);

	if (status == _hoops_HPHHA || status == _hoops_IPHHA)
		info->result = true;
	
	return VBSP_STATUS_CONTINUE;
}

#define _hoops_PHHHA(p,q) ((p)->x = (q)->x, (p)->y = (q)->y, (p)->z = (q)->z) 



#define _hoops_HHHHA(p,a,b,c) ((p)->x = (a), (p)->y = (b), (p)->z = (c)) 





 


local bool _hoops_IHHHA(Point const * p, Point const *pl, int _hoops_RHGIR )
{
	_hoops_ARPA _hoops_IRPA;
	HI_Figure_Plane_From_Points (_hoops_RHGIR, pl, &_hoops_IRPA);
 
 	for (int i=0; i<_hoops_RHGIR; i++) {
		int i1,i2;

		if (i<_hoops_RHGIR-1) {		
			i1 = i;
			i2 = i+1;
		}
		else {
			i1 = i;
			i2 = 0;
		}

		Point pp[3];
		pp[0] = pl[i1];
		pp[1] = pl[i2];
		pp[2] = Point(pl[i1].x + _hoops_IRPA.a, pl[i1].y + _hoops_IRPA.b, pl[i1].z + _hoops_IRPA.c);

		_hoops_ARPA _hoops_CHHHA;	
		HI_Figure_Plane_From_Points (3, pp, &_hoops_CHHHA);

		float dist = ((_hoops_CHHHA.a * p->x + _hoops_CHHHA.b * p->y + _hoops_CHHHA.c * p->z + _hoops_CHHHA.d ) / 
						sqrt(_hoops_CHHHA.a * _hoops_CHHHA.a + _hoops_CHHHA.b * _hoops_CHHHA.b + _hoops_CHHHA.c * _hoops_CHHHA.c));

		if (dist>0)
			return false;
	}

	return true;
}
 
GLOBAL_FUNCTION bool HI_Distance_Point_Polygon(
	Point const *	p, 
	Point const *	points, 
	int				_hoops_RHGIR, 
	Point alter *	_hoops_SHHHA, 
	float alter *	dist) 
{	
	*_hoops_SHHHA = Point(0,0,0);

  	if (_hoops_IHHHA(p, points, _hoops_RHGIR)) {
		_hoops_ARPA pl;
		HI_Figure_Plane_From_Points (_hoops_RHGIR, points, &pl);

		*dist = fabs((pl.a * p->x + pl.b * p->y + pl.c * p->z + pl.d ) / 
						sqrt(pl.a * pl.a + pl.b * pl.b + pl.c * pl.c));

		Point _hoops_GIHHA(p->x + pl.a, p->y + pl.b, p->z + pl.c);

		*_hoops_SHHHA = pl._hoops_RIHHA(*p, _hoops_GIHHA);

		return true;
	}	 

	return false;
}


local float _hoops_AIHHA(Point p1, Point *p2, int _hoops_PIHHA, Point *_hoops_SCAAA, Point *_hoops_GSAAA)
{
	Point _hoops_HIHHA;
	float _hoops_IIHHA = 1.0e6;
		
	for (int j=0;j<_hoops_PIHHA;j++) {

		int _hoops_CIHHA,_hoops_SIHHA;
		if (j<_hoops_PIHHA-1){
			_hoops_CIHHA = j;
			_hoops_SIHHA = j+1;
		}
		else{
			_hoops_CIHHA = j;
			_hoops_SIHHA = 0;
		}			
			
		float dist;
		if (HI_Compute_Point_To_Line_Distance(&p1, &p2[_hoops_CIHHA],  &p2[_hoops_SIHHA], &dist, &_hoops_HIHHA)) {
	
			if (dist<_hoops_IIHHA) {
				_hoops_IIHHA = dist;	
				*_hoops_SCAAA = _hoops_HIHHA;
			}			
		}
	}
	
	float dist;
	bool _hoops_GCHHA  = HI_Distance_Point_Polygon(&p1, p2, _hoops_PIHHA, &_hoops_HIHHA, &dist);

	if (_hoops_GCHHA && dist<_hoops_IIHHA){
		_hoops_IIHHA = dist;	
		*_hoops_SCAAA = _hoops_HIHHA;
		*_hoops_GSAAA = p1;
	}			

	return _hoops_IIHHA;
}



/* _hoops_CRSAR _hoops_IISA _hoops_HII _hoops_RH _hoops_IPHRA.  _hoops_SAHHA _hoops_PPR _hoops_SRSAR _hoops_RCPS _hoops_HII _hoops_RSCRR _hoops_HIGR _hoops_GGR _hoops_GPHHA
 * _hoops_SHR _hoops_HRS 1 _hoops_PGGA _hoops_SR _hoops_HHGC _hoops_RH _hoops_IPHRA _hoops_IS _hoops_GRHP _hoops_HHCPR */
local _hoops_CSCAR _hoops_RCHHA (void *_hoops_HCSAR, void *_hoops_IASAR, void *_hoops_CASAR) 
{
	_hoops_PRHHA *	info = (_hoops_PRHHA *)_hoops_HCSAR;
	Point const *			points = info->points;
	Point const *			_hoops_CIIRR = info->_hoops_CIIRR;
 	_hoops_SHPPA *			face = (_hoops_SHPPA *)_hoops_IASAR;
	_hoops_ACHHA *			vertex = (_hoops_ACHHA *)_hoops_CASAR;
	Point  *				pt = &vertex->vertex;
	float					tolerance = info->tolerance;
	_hoops_ARPA const &			plane = face->plane;
	
	float _hoops_RHHHA = Vector(plane)._hoops_PPSSR();

	if (_hoops_RHHHA < 1e-5f)
		return VBSP_STATUS_CONTINUE;

	/* _hoops_CSGA (_hoops_PAPPA + _hoops_HPP + _hoops_IIHCR + _hoops_GHGP) */
	float equation = plane * *pt;

	if (-tolerance > equation || equation > tolerance)
		return VBSP_STATUS_CONTINUE;

	int status = _hoops_AHHHA (pt, points, face->len, face->_hoops_GIPPA, &plane, tolerance);

	if (status == _hoops_HPHHA || status == _hoops_IPHHA) {	
		if (info->_hoops_SRHHA) {		
			if (_hoops_CIIRR) {	
				Point _hoops_PCHHA(
					pt->x + _hoops_CIIRR[vertex->_hoops_HCHHA].x * 100.0f,
					pt->y + _hoops_CIIRR[vertex->_hoops_HCHHA].y * 100.0f,
					pt->z + _hoops_CIIRR[vertex->_hoops_HCHHA].z * 100.0f);

				Point _hoops_HGII = plane._hoops_RIHHA(*pt, _hoops_PCHHA);

				status = _hoops_AHHHA (&_hoops_HGII, points, face->len, face->_hoops_GIPPA, &plane, 0);

				if (status == _hoops_HPHHA || status == _hoops_IPHHA)
					info->results[vertex->_hoops_HCHHA] = face->index;
			}
			else
				info->results[vertex->_hoops_HCHHA] = face->index;
		}
		else
			info->results[vertex->_hoops_HCHHA] = 0;
	}

	return VBSP_STATUS_CONTINUE;
}

/* _hoops_CRSAR _hoops_IISA _hoops_HII _hoops_RH _hoops_IPHRA.  _hoops_SAHHA _hoops_PPR _hoops_SRSAR _hoops_RCPS _hoops_HII _hoops_RSCRR _hoops_HIGR _hoops_GGR _hoops_GPHHA
 * _hoops_SHR _hoops_HRS 1 _hoops_PGGA _hoops_SR _hoops_HHGC _hoops_RH _hoops_IPHRA _hoops_IS _hoops_GRHP _hoops_HHCPR */
local _hoops_CSCAR _hoops_ICHHA (void *_hoops_HCSAR, void *_hoops_IASAR, void *_hoops_CASAR) 
{
	_hoops_PRHHA *	info = (_hoops_PRHHA *)_hoops_HCSAR;
	Point const *			points = info->points;
  	_hoops_SHPPA *			face = (_hoops_SHPPA *)_hoops_IASAR;
	_hoops_ACHHA *			vertex = (_hoops_ACHHA *)_hoops_CASAR;
	Point  *				pt = &vertex->vertex;
	float					tolerance = info->tolerance;
 
	Point _hoops_CCHHA[256];
	ASSERT(face->len < 256);
	for (int i=0;i<face->len;i++)
		_hoops_CCHHA[i] = points[face->_hoops_GIPPA[i]];

	Point _hoops_SCAAA, _hoops_GSAAA;
 	float _hoops_CGSIR = _hoops_AIHHA(*pt, _hoops_CCHHA, face->len, &_hoops_SCAAA, &_hoops_GSAAA);

	if (_hoops_CGSIR < tolerance && (info->_hoops_HRHHA[vertex->_hoops_HCHHA]<0 || info->_hoops_HRHHA[vertex->_hoops_HCHHA]>_hoops_CGSIR))
	{
		if (info->_hoops_IRHHA)
			info->_hoops_IRHHA[vertex->_hoops_HCHHA] = face->index;
 		info->_hoops_HRHHA[vertex->_hoops_HCHHA] = _hoops_CGSIR;
	}
	
	return VBSP_STATUS_CONTINUE;
}


Begin_HOOPS_Namespace
	struct _hoops_SCHHA {
		int			count;
		void **		_hoops_GSHHA;
		int			_hoops_RSHHA;
	};

	struct _hoops_ASHHA;

	typedef VList<_hoops_ASHHA *> _hoops_PSHHA;

	struct _hoops_HSHHA : CMO {
		_hoops_SCHHA *		items;	
		_hoops_PSHHA *					_hoops_ISHHA;
		const Point *				points;
		_hoops_SASC				cuboid;
		Vector						delta;
		int							_hoops_PRAA;
		int							_hoops_HRAA;
		int							_hoops_CSHHA;
		float						tolerance;
	};

	struct _hoops_ASHHA : CMO{
		int				len;
		Point *			points;
		_hoops_ARPA *			planes;
		_hoops_ARPA			pl;
		Vector			_hoops_IRPA;
		_hoops_SASC	cuboid;
		int				index;
		int				_hoops_SSHHA[4];
	};

	struct _hoops_GGIHA : CMO {
		_hoops_HSHHA *	_hoops_RGIHA;
		_hoops_HSHHA *	_hoops_AGIHA;
		float				tolerance;
		float *				results;
		int	*				face_results;
		int					_hoops_RCAI;
	};	
End_HOOPS_Namespace;


INLINE _hoops_SCHHA * _hoops_PGIHA(_hoops_HSHHA const * _hoops_HGIHA, int x, int y, int z) 
{
	int index = x + y*_hoops_HGIHA->_hoops_PRAA + z * (_hoops_HGIHA->_hoops_PRAA*_hoops_HGIHA->_hoops_HRAA);
	return &_hoops_HGIHA->items[index];
}


INLINE void _hoops_IGIHA(_hoops_HSHHA const * grid, int x, int y, int z, _hoops_SASC alter & _hoops_CGIHA)
{
	_hoops_CGIHA.min = Point(
		grid->cuboid.min.x + x * grid->delta.x, 
		grid->cuboid.min.y + y * grid->delta.y, 
		grid->cuboid.min.z + z * grid->delta.z);

	_hoops_CGIHA.max = Point(
		grid->cuboid.min.x + x * grid->delta.x + grid->delta.x, 
		grid->cuboid.min.y + y * grid->delta.y + grid->delta.y, 
		grid->cuboid.min.z + z * grid->delta.z + grid->delta.z);
}


local bool _hoops_SGIHA(Point *p, _hoops_ASHHA *_hoops_GRIHA )
{
  	for (int i=0; i<_hoops_GRIHA->len; i++) {
		_hoops_ARPA const & _hoops_CHHHA = _hoops_GRIHA->planes[i];

		float dist = ((_hoops_CHHHA.a * p->x + _hoops_CHHHA.b * p->y + _hoops_CHHHA.c * p->z + _hoops_CHHHA.d ) / 
						sqrt(_hoops_CHHHA.a * _hoops_CHHHA.a + _hoops_CHHHA.b * _hoops_CHHHA.b + _hoops_CHHHA.c * _hoops_CHHHA.c));
		if (dist > 0)
			return false;
	}
	return true;
}


local bool _hoops_RRIHA(Point *p, _hoops_ASHHA *_hoops_GRIHA, float *dist)						  
{	
  	if (_hoops_SGIHA(p, _hoops_GRIHA)) {
		_hoops_ARPA pl = _hoops_GRIHA->pl;
		Point _hoops_GIHHA;		
		*dist = fabs( (pl.a * p->x + pl.b * p->y + pl.c * p->z + pl.d ) / 
			sqrt(pl.a * pl.a + pl.b * pl.b + pl.c * pl.c));		
 		return true;
	}	 
	return false;
}


local float _hoops_ARIHA(Point p1, _hoops_ASHHA *_hoops_GRIHA)
{
	Point *p2 = _hoops_GRIHA->points;
	int _hoops_PIHHA = _hoops_GRIHA->len;

	float _hoops_IIHHA = 1.0e6;

	float dist;
	if (_hoops_RRIHA(&p1, _hoops_GRIHA, &dist))			
		return dist;		

	if (_hoops_PIHHA == 3) {
		if (HI_Compute_Point_To_Line_Distance(&p1, &p2[0],  &p2[1], &dist)) {
 			if (dist<_hoops_IIHHA)
				_hoops_IIHHA = dist;						
		}
		if (HI_Compute_Point_To_Line_Distance(&p1, &p2[1],  &p2[2], &dist)) {
 			if (dist<_hoops_IIHHA)
				_hoops_IIHHA = dist;						
		}
		if (HI_Compute_Point_To_Line_Distance(&p1, &p2[2],  &p2[0], &dist)) {
 			if (dist<_hoops_IIHHA)
				_hoops_IIHHA = dist;					
		}
		return _hoops_IIHHA;
	}


	for (int j=0;j<_hoops_PIHHA;j++) {			
		int _hoops_CIHHA,_hoops_SIHHA;

		if (j<_hoops_PIHHA-1){
			_hoops_CIHHA = j;
			_hoops_SIHHA = j+1;
		}
		else {
			_hoops_CIHHA = j;
			_hoops_SIHHA = 0;
		}			
			
		if (HI_Compute_Point_To_Line_Distance(&p1, &p2[_hoops_CIHHA],  &p2[_hoops_SIHHA], &dist)) {
 			if (dist<_hoops_IIHHA)
				_hoops_IIHHA = dist;						
		}
	}
	
	return _hoops_IIHHA;
}







local _hoops_HSHHA *_hoops_PRIHA (_hoops_SASC const & _hoops_RCHS, float tolerance, int x, int y, int z) {
	_hoops_HSHHA	*_hoops_HGIHA = NEW(_hoops_HSHHA)();

	_hoops_HGIHA->_hoops_PRAA  = x;
	_hoops_HGIHA->_hoops_HRAA  = y;
	_hoops_HGIHA->_hoops_CSHHA  = z;

	TRY_ALLOC_ARRAY (_hoops_HGIHA->items, _hoops_HGIHA->_hoops_PRAA*_hoops_HGIHA->_hoops_HRAA*_hoops_HGIHA->_hoops_CSHHA, _hoops_SCHHA);
	
	if (_hoops_HGIHA->items == null)
		return _hoops_HGIHA;
 
	ZERO_ARRAY (_hoops_HGIHA->items, _hoops_HGIHA->_hoops_PRAA*_hoops_HGIHA->_hoops_HRAA*_hoops_HGIHA->_hoops_CSHHA, _hoops_SCHHA);

	_hoops_HGIHA->cuboid = _hoops_RCHS;
	_hoops_HGIHA->tolerance = tolerance;
	_hoops_HGIHA->delta = (_hoops_HGIHA->cuboid.max - _hoops_HGIHA->cuboid.min) / (float)_hoops_HGIHA->_hoops_PRAA;
	_hoops_HGIHA->points = null;

 	return _hoops_HGIHA;
}



local void _hoops_HRIHA(_hoops_SCHHA *item, void *fp)
{
	if (item->count >= item->_hoops_RSHHA) {
		int _hoops_IRIHA = item->_hoops_RSHHA;
		item->_hoops_RSHHA += 40;
		void **_hoops_CRIHA;
		ALLOC_ARRAY(_hoops_CRIHA, item->_hoops_RSHHA, void*);
		if (item->_hoops_GSHHA != null) {
			COPY_MEMORY(item->_hoops_GSHHA, item->count*sizeof(void*), _hoops_CRIHA);
			FREE_ARRAY(item->_hoops_GSHHA, _hoops_IRIHA, void*);
		}
		item->_hoops_GSHHA = _hoops_CRIHA;
	}
	item->_hoops_GSHHA[item->count] = fp;
	item->count++;
 }

local void _hoops_SRIHA (
	_hoops_HSHHA *		_hoops_HGIHA,
	_hoops_SASC const &	_hoops_GAIHA, 
	void *					fp, 
	_hoops_ARPA const *			p = null) 
{
	Vector v;
	
	v = _hoops_GAIHA.min - _hoops_HGIHA->cuboid.min;
	v.x /= _hoops_HGIHA->delta.x;
	v.y /= _hoops_HGIHA->delta.y;
	v.z /= _hoops_HGIHA->delta.z;
	int xmin = _hoops_AHIA((int)v.x, _hoops_HGIHA->_hoops_PRAA-1);
	int ymin = _hoops_AHIA((int)v.y, _hoops_HGIHA->_hoops_HRAA-1);
	int _hoops_RICR = _hoops_AHIA((int)v.z, _hoops_HGIHA->_hoops_CSHHA-1);
	
	v = _hoops_GAIHA.max - _hoops_HGIHA->cuboid.min;
	v.x /= _hoops_HGIHA->delta.x;
	v.y /= _hoops_HGIHA->delta.y;
	v.z /= _hoops_HGIHA->delta.z;
	int xmax = _hoops_AHIA((int)v.x, _hoops_HGIHA->_hoops_PRAA-1);
	int ymax = _hoops_AHIA((int)v.y, _hoops_HGIHA->_hoops_HRAA-1);
	int _hoops_AICR = _hoops_AHIA((int)v.z, _hoops_HGIHA->_hoops_CSHHA-1);

	for (int x = xmin; x <= xmax; x++) {
		for (int y = ymin; y <= ymax; y++) {
			for (int z = _hoops_RICR; z <= _hoops_AICR; z++) {
				if (p != null) {
					_hoops_SASC _hoops_CGIHA;
					_hoops_IGIHA(_hoops_HGIHA, x, y, z, _hoops_CGIHA);

					if (p->a < 0.0f)
						Swap (_hoops_CGIHA.min.x, _hoops_CGIHA.max.x);
					if (p->b < 0.0f)
						Swap (_hoops_CGIHA.min.y, _hoops_CGIHA.max.y);
					if (p->c < 0.0f)
						Swap (_hoops_CGIHA.min.z, _hoops_CGIHA.max.z);

					if (*p * _hoops_CGIHA.min > _hoops_HGIHA->tolerance || *p * _hoops_CGIHA.max < -_hoops_HGIHA->tolerance)
						continue;
				}

				_hoops_SCHHA *item = _hoops_PGIHA(_hoops_HGIHA, x,y,z);
				_hoops_HRIHA(item, fp);
			}
		}
	}
}

local void _hoops_RAIHA(
	_hoops_HSHHA *	_hoops_HGIHA, 
	int					_hoops_RISRA, 
	Point const *		points)
{
	for (POINTER_SIZED_INT i=0;i<_hoops_RISRA;i++) {	
		_hoops_SASC bounding(1, &points[i]);			
		_hoops_SRIHA (_hoops_HGIHA, bounding, (void *)i);
	}
	_hoops_HGIHA->points = points; 	
}



local void _hoops_AAIHA(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HSHHA *		_hoops_HGIHA, 
	Point const *			points, 
	int						_hoops_RHGIR, 
	const int *				_hoops_ASPH)
{

	int _hoops_SHHCR = 0;

	_hoops_HGIHA->_hoops_ISHHA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_PSHHA)(_hoops_RIGC->memory_pool);

	int _hoops_SSPAR = 0;
	while (1) {
 		_hoops_ASHHA *face = NEW(_hoops_ASHHA)();
		face->_hoops_SSHHA[0] = 0;
		face->_hoops_SSHHA[1] = 0;
		face->_hoops_SSHHA[2] = 0;
		face->_hoops_SSHHA[3] = 0;
		face->index = _hoops_SSPAR++;
		int len = _hoops_ASPH[_hoops_SHHCR++];
 		ALLOC_ARRAY(face->points, len, Point);
		ALLOC_ARRAY(face->planes, len, _hoops_ARPA);
		face->len = len;

		for (int i=0;i<len;i++)
			face->points[i] = points[_hoops_ASPH[_hoops_SHHCR++]];
			
		_hoops_SASC bounding(len, face->points);
		
		HI_Figure_Plane_From_Points (len, face->points, &face->pl);
		_hoops_ARPA const & _hoops_IRPA = face->pl;

		for (int i=0;i<len;i++) {
			int i1,i2;

			if (i<len-1) {		
				i1 = i;
				i2 = i+1;
			}
			else {
				i1 = i;
				i2 = 0;
			}

			Point pp[3];
			pp[0] = face->points[i1];
			pp[1] = face->points[i2];
			pp[2] = Point(face->points[i1].x + _hoops_IRPA.a, face->points[i1].y + _hoops_IRPA.b, face->points[i1].z + _hoops_IRPA.c);
			
			HI_Figure_Plane_From_Points (3, pp, &face->planes[i]);
		}

		face->cuboid = bounding;

		face->_hoops_IRPA = Vector(_hoops_IRPA);

		_hoops_HGIHA->_hoops_ISHHA->AddLast(face);
 		_hoops_SRIHA (_hoops_HGIHA, bounding, face, &face->pl);
		if (_hoops_SHHCR>=_hoops_RHGIR-1)
			break;
	}
}



local void _hoops_PAIHA(
	_hoops_HSHHA *		_hoops_RGIHA, 
	void **					_hoops_HAIHA,
	_hoops_SASC const &	_hoops_IAIHA, 
	int						_hoops_CAIHA, 
	int						_hoops_SAIHA, 
	int						_hoops_SHCR, 
	float &					_hoops_GPIHA, 
	int &					_hoops_RPIHA, 
	int						_hoops_APIHA)
{
	_hoops_SCHHA *item = _hoops_PGIHA(_hoops_RGIHA, _hoops_CAIHA,_hoops_SAIHA,_hoops_SHCR);

	if (item->_hoops_GSHHA) {
		bool _hoops_PPIHA = false;

		for (int i=0; i<item->count; i++) {
			_hoops_ASHHA *_hoops_GRIHA = (_hoops_ASHHA *)item->_hoops_GSHHA[i];
			if (!_hoops_GRIHA->_hoops_SSHHA[_hoops_APIHA]) {
				_hoops_PPIHA = true;
				break;
			}										
		}
		
		if (_hoops_PPIHA) {
			bool _hoops_HPIHA = false;
			_hoops_SASC _hoops_CGIHA;
			_hoops_IGIHA(_hoops_RGIHA, _hoops_CAIHA, _hoops_SAIHA, _hoops_SHCR, _hoops_CGIHA);

			if (_hoops_GPIHA <0) {
				_hoops_GPIHA = HI_Cuboid_To_Cuboid_Max_Distance(_hoops_IAIHA, _hoops_CGIHA);					
				_hoops_HPIHA = true;
			}
			else {
				float _hoops_IPIHA = HI_Cuboid_To_Cuboid_Distance(_hoops_IAIHA, _hoops_CGIHA);
				if (_hoops_IPIHA <= _hoops_GPIHA)
					_hoops_HPIHA = true;
			}
			if (_hoops_HPIHA) {
				for (int i=0; i<item->count; i++) {
					_hoops_ASHHA *_hoops_GRIHA = (_hoops_ASHHA *)item->_hoops_GSHHA[i];
					if (!_hoops_GRIHA->_hoops_SSHHA[_hoops_APIHA]) {
						_hoops_PPIHA = true;
						_hoops_GRIHA->_hoops_SSHHA[_hoops_APIHA] = true;
						_hoops_HAIHA[_hoops_RPIHA++] = (void *)_hoops_GRIHA;
					}
				}						
			}
		}	
	}	
}



local void _hoops_CPIHA(
	_hoops_HSHHA *	_hoops_RGIHA, 
	int					cx, 
	int					cy, 
	int					_hoops_SPIHA,
	void **				_hoops_HAIHA, 
	int &				_hoops_RPIHA, 
	int					_hoops_APIHA, 
	int					_hoops_GHIHA)
{
	float _hoops_RHIHA = -1.0f;

	int _hoops_AHIHA, _hoops_PHIHA, _hoops_HHIHA;
	_hoops_AHIHA = cx;
	_hoops_PHIHA = cy;
	_hoops_HHIHA = _hoops_SPIHA;

	int _hoops_IHIHA = _hoops_GHIHA;

	if (_hoops_IHIHA < 4)
		_hoops_IHIHA = 4;

	int _hoops_CHIHA = 0;

	_hoops_SASC _hoops_CGIHA;
	_hoops_IGIHA(_hoops_RGIHA, cx, cy, _hoops_SPIHA, _hoops_CGIHA);

 	while (1) {	
		_hoops_IHIHA--;

		if (_hoops_IHIHA<=0)
			break;

		if (_hoops_IHIHA==(_hoops_GHIHA - 1))
			_hoops_PAIHA(_hoops_RGIHA, _hoops_HAIHA, _hoops_CGIHA, cx, cy, _hoops_SPIHA, _hoops_RHIHA, _hoops_RPIHA, _hoops_APIHA);
		else {
			for (int x=cx; x<=_hoops_AHIHA; x++) {
				for (int z=_hoops_SPIHA; z<=_hoops_HHIHA; z++) {
					_hoops_PAIHA(_hoops_RGIHA, _hoops_HAIHA, _hoops_CGIHA, x, cy, z, _hoops_RHIHA, _hoops_RPIHA, _hoops_APIHA);
					_hoops_PAIHA(_hoops_RGIHA, _hoops_HAIHA, _hoops_CGIHA, x, _hoops_PHIHA, z,_hoops_RHIHA, _hoops_RPIHA, _hoops_APIHA);
				}
			}
			for (int x=cx; x<=_hoops_AHIHA; x++) {
				for (int y=cy; y<=_hoops_PHIHA; y++) {
					_hoops_PAIHA(_hoops_RGIHA, _hoops_HAIHA, _hoops_CGIHA, x, y, _hoops_SPIHA, _hoops_RHIHA, _hoops_RPIHA, _hoops_APIHA);
					_hoops_PAIHA(_hoops_RGIHA, _hoops_HAIHA, _hoops_CGIHA,x, y, _hoops_HHIHA, _hoops_RHIHA, _hoops_RPIHA, _hoops_APIHA);
				}
			}
			for (int y=cy; y<=_hoops_PHIHA; y++) {
				for (int z=_hoops_SPIHA; z<=_hoops_HHIHA; z++) {
					_hoops_PAIHA(_hoops_RGIHA, _hoops_HAIHA, _hoops_CGIHA, cx, y, z, _hoops_RHIHA, _hoops_RPIHA, _hoops_APIHA);
					_hoops_PAIHA(_hoops_RGIHA, _hoops_HAIHA, _hoops_CGIHA, _hoops_AHIHA, y, z, _hoops_RHIHA, _hoops_RPIHA, _hoops_APIHA);
				}
			}
		}

		if (_hoops_RHIHA >0 && !_hoops_CHIHA)
			_hoops_CHIHA = 2;

		if (_hoops_CHIHA) {
			_hoops_CHIHA--;
			if (_hoops_CHIHA == 0)
				break;
		}
		
		cx--;
		cy--;
		_hoops_SPIHA--;
		_hoops_AHIHA++;
		_hoops_PHIHA++;
		_hoops_HHIHA++;

		if (cx < 0 && cy < 0 && _hoops_SPIHA < 0 && 
			_hoops_AHIHA >= _hoops_RGIHA->_hoops_PRAA && 
			_hoops_PHIHA >= _hoops_RGIHA->_hoops_HRAA && 
			_hoops_HHIHA >= _hoops_RGIHA->_hoops_CSHHA)
			break;
		
		if (cx < 0)
			cx = 0;
		if (cy < 0)
			cy = 0;
		if (_hoops_SPIHA < 0)
			_hoops_SPIHA = 0;

		if (_hoops_AHIHA>_hoops_RGIHA->_hoops_PRAA-1)
			_hoops_AHIHA = _hoops_RGIHA->_hoops_PRAA-1;
		if (_hoops_PHIHA>_hoops_RGIHA->_hoops_HRAA-1)
			_hoops_PHIHA = _hoops_RGIHA->_hoops_HRAA-1;
		if (_hoops_HHIHA>_hoops_RGIHA->_hoops_CSHHA-1)
			_hoops_HHIHA = _hoops_RGIHA->_hoops_CSHHA-1;
	}
}





local void _hoops_SHIHA(_hoops_HSHHA *_hoops_RGIHA, _hoops_HSHHA *_hoops_GIIHA, float tolerance, int _hoops_RCAI, float *results, int *face_results)
{
	int _hoops_RIIHA = _hoops_RCAI;	
  	
	float vl = HI_Compute_Vector_Length(&_hoops_RGIHA->delta);
	int _hoops_GHIHA = (int)((int)tolerance/vl);

 	for (int x=_hoops_RIIHA; x<_hoops_RGIHA->_hoops_PRAA; x+=4) {
		for (int y=0; y<_hoops_RGIHA->_hoops_HRAA; y++) {
			for (int z=0; z<_hoops_RGIHA->_hoops_CSHHA; z++) {
				_hoops_SCHHA *item = _hoops_PGIHA(_hoops_GIIHA, x,y,z);

				if (item->_hoops_GSHHA) {				
					void *_hoops_AIIHA[4096];
					int _hoops_PIIHA = 0;
 					
					_hoops_CPIHA(_hoops_RGIHA,  x,  y,  z, _hoops_AIIHA, _hoops_PIIHA, _hoops_RIIHA, _hoops_GHIHA);

					if (_hoops_PIIHA) {
						for (int j=0; j<_hoops_PIIHA; j++)						
							((_hoops_ASHHA *)_hoops_AIIHA[j])->_hoops_SSHHA[_hoops_RIIHA] = false;
	 						
						for (int i=0; i<item->count; i++) {
							int _hoops_HCHHA = (int)(POINTER_SIZED_INT)item->_hoops_GSHHA[i];
							float _hoops_HIIHA = 100000000;
							int _hoops_IIIHA = -1;

							for (int j=0; j<_hoops_PIIHA; j++) {
  								_hoops_ASHHA *_hoops_GRIHA = (_hoops_ASHHA *)_hoops_AIIHA[j]; 						
								Point const & p = _hoops_GIIHA->points[_hoops_HCHHA];							
								if (j == 0 || 
									HI_Cuboid_To_Point_Distance(_hoops_GRIHA->cuboid, p) <_hoops_HIIHA) {	

									float dist =  _hoops_ARIHA(p, _hoops_GRIHA);
 									if (dist < tolerance && dist < _hoops_HIIHA)
									{
										_hoops_IIIHA = _hoops_GRIHA->index;
										_hoops_HIIHA = dist;							
									}
								}
 							}
							if (_hoops_HIIHA <= tolerance)
							{
								results[_hoops_HCHHA] = _hoops_HIIHA;							
								if (face_results)
									face_results[_hoops_HCHHA] = _hoops_IIIHA;
							}
 						}	
					}				
 				}
			}
		}
	}
}


local void _hoops_CIIHA(_hoops_HSHHA *_hoops_HGIHA)
{
	for (int i=0; i<_hoops_HGIHA->_hoops_PRAA*_hoops_HGIHA->_hoops_HRAA*_hoops_HGIHA->_hoops_CSHHA; i++) {
			_hoops_SCHHA item = _hoops_HGIHA->items[i];

			if (item._hoops_GSHHA) {
				FREE_ARRAY(item._hoops_GSHHA, item._hoops_RSHHA, void*);
				//_hoops_HSCI [] _hoops_IGCI._hoops_SIIHA;
 			}
 	}

	FREE_ARRAY(_hoops_HGIHA->items, _hoops_HGIHA->_hoops_PRAA*_hoops_HGIHA->_hoops_HRAA*_hoops_HGIHA->_hoops_CSHHA, _hoops_SCHHA);
	//_hoops_HSCI [] _hoops_GCIHA->_hoops_APSAR;
}

				



THREAD_FUNCTION(CalculateDistanceThread) 
{
	_hoops_GGIHA *_hoops_RCIHA = THREAD_FUNCTION_DATA(_hoops_GGIHA *); 	
	_hoops_SHIHA(_hoops_RCIHA->_hoops_RGIHA, _hoops_RCIHA->_hoops_AGIHA,_hoops_RCIHA->tolerance, _hoops_RCIHA->_hoops_RCAI, _hoops_RCIHA->results, _hoops_RCIHA->face_results);
 	return 0;
}

#include "task_queue.h"

class _hoops_ACIHA : public _hoops_GCARR {

public:

	_hoops_ACIHA(_hoops_GGIHA *_hoops_PCIHA) {
		_hoops_HCIHA=_hoops_PCIHA;
		HOOPS_WORLD->_hoops_ACARR->_hoops_PCARR(this);
	};

	virtual ~_hoops_ACIHA() {;}

	virtual _hoops_ICARR Type() {return _hoops_ICIHA;}

	virtual void _hoops_HCARR(bool _hoops_SCARR) {
		UNREFERENCED(_hoops_SCARR);

		_hoops_CIIHA(_hoops_HCIHA->_hoops_AGIHA);
		_hoops_CIIHA(_hoops_HCIHA->_hoops_RGIHA);
		delete _hoops_HCIHA->_hoops_AGIHA;

		_hoops_HCIHA->_hoops_RGIHA->_hoops_ISHHA->ResetCursor();
		while (1) {
			_hoops_ASHHA *face = _hoops_HCIHA->_hoops_RGIHA->_hoops_ISHHA->PeekCursor();
			if (!face)
				break;

			FREE_ARRAY(face->points, face->len, Point);
			FREE_ARRAY(face->planes, face->len, _hoops_ARPA);
			delete face;
			_hoops_HCIHA->_hoops_RGIHA->_hoops_ISHHA->AdvanceCursor();		
		}
		delete _hoops_HCIHA->_hoops_RGIHA->_hoops_ISHHA;
		delete _hoops_HCIHA->_hoops_RGIHA;
		delete _hoops_HCIHA;	

		delete this;
	}

private:
	_hoops_GGIHA *_hoops_HCIHA;
};



/* _hoops_CRSAR _hoops_IISA _hoops_HII _hoops_RH _hoops_IPHRA.  _hoops_SAHHA _hoops_PPR _hoops_SRSAR _hoops_RCPS _hoops_HII _hoops_RSCRR _hoops_HIGR _hoops_GGR _hoops_GPHHA
 * _hoops_SHR _hoops_HRS 1 _hoops_PGGA _hoops_SR _hoops_HHGC _hoops_RH _hoops_IPHRA _hoops_IS _hoops_GRHP _hoops_HHCPR */
local _hoops_CSCAR _hoops_CCIHA (
	void *	_hoops_HCSAR, 
	void *	_hoops_IASAR, 
	void *	_hoops_CASAR) 
{
	_hoops_PRHHA *	info = (_hoops_PRHHA *)_hoops_HCSAR;
  	_hoops_SASC const *	bbox = (_hoops_SASC const *)_hoops_IASAR;

	_hoops_CASAR = _hoops_CASAR;

	Point					points[8];
	int						_hoops_ASPH[30];
	HI_Generate_Cuboid_Points(bbox->max, bbox->min, points, _hoops_ASPH);
	
	bool _hoops_SCIHA = HI_Compute_Intersect_Polyline_Nonzero (info->_hoops_RIGC, info->_hoops_CRHHA,
													 info->_hoops_RISRA, info->points, info->_hoops_RHGIR, info->faces,
													 8, points, 30, _hoops_ASPH);
	if (_hoops_SCIHA) {	
		if (HI_Compute_Point_Inside_Shell (info->_hoops_RIGC, (const Point *)bbox, 
											info->_hoops_RISRA, info->points, info->_hoops_RHGIR, info->faces))
			return -1;
		else 
			return VBSP_STATUS_STOP;
	}

	return VBSP_STATUS_CONTINUE;
}



/* _hoops_CRSAR _hoops_IISA _hoops_HII _hoops_RH _hoops_IPHRA.  _hoops_SAHHA _hoops_PPR _hoops_SRSAR _hoops_RCPS _hoops_HII _hoops_RSCRR _hoops_HIGR _hoops_GGR _hoops_GPHHA
 * _hoops_SHR _hoops_HRS 1 _hoops_PGGA _hoops_SR _hoops_HHGC _hoops_RH _hoops_IPHRA _hoops_IS _hoops_GRHP _hoops_HHCPR */
local _hoops_CSCAR _hoops_GSIHA (void *_hoops_HCSAR, void *_hoops_IASAR, int _hoops_HGII) 
{
  	_hoops_PRHHA *info = (_hoops_PRHHA *)_hoops_HCSAR;
  	_hoops_ACHHA *vertex = (_hoops_ACHHA *)_hoops_IASAR;

	if (info->results[vertex->_hoops_HCHHA] == 2)
   		info->results[vertex->_hoops_HCHHA] = _hoops_HGII;
 	return VBSP_STATUS_CONTINUE;
}



#define _hoops_IACIR 1e10f
local int _hoops_RSIHA (_hoops_RRHHA *_hoops_SSGPA)
{
	int i, j, count;
	float t, _hoops_ASIHA, _hoops_ARGCR, _hoops_PSIHA;

	if (_hoops_SSGPA->Count() == 1)
		return 1;

	count = 0;
	for (i = 0; i < _hoops_SSGPA->Count(); i++) {
		_hoops_ASIHA = _hoops_IACIR;
		t = *((*_hoops_SSGPA)[i]);
		_hoops_PSIHA = 0.1f * t;
		for (j = i+1; j < _hoops_SSGPA->Count(); j++) {
			_hoops_ARGCR = t - *((*_hoops_SSGPA)[j]);
			if (_hoops_ARGCR < 0) _hoops_ARGCR = -_hoops_ARGCR;
			if (_hoops_ARGCR < _hoops_ASIHA)
				_hoops_ASIHA = _hoops_ARGCR;
		}
		if (_hoops_ASIHA > _hoops_PSIHA)
			count++; 
	}
	return count;
}


GLOBAL_FUNCTION void * HI_New_Point_Inside_Shell_Cache  (void) 
{
	_hoops_RAHHA *_hoops_CSC;

	ALLOC (_hoops_CSC, _hoops_RAHHA);
	_hoops_CSC->_hoops_GRPPA = 0;
	_hoops_CSC->BSP = null;
	return _hoops_CSC;
}


GLOBAL_FUNCTION void HI_Delete_Point_Inside_Shell_Cache  (void *_hoops_HAHPA) 
{
	_hoops_RAHHA *_hoops_CSC = (_hoops_RAHHA *)_hoops_HAHPA;

	if (_hoops_CSC->BSP) {
		HI_BSP_Map_Function (_hoops_CSC->BSP, _hoops_AAHPA, null);
		HI_Delete_BSP (_hoops_CSC->BSP);
		_hoops_CSC->BSP = null;
	}
	FREE (_hoops_CSC, _hoops_RAHHA);
}


/* _hoops_SAHR _hoops_PIHHR _hoops_IRS _hoops_ARGHR _hoops_IIGR _hoops_CIPH _hoops_GIRP */
#define _hoops_ARPPA() \
 (\
   point_count ^ \
   (face_list_length << 8) ^ \
   ((POINTER_SIZED_INT)(points)) ^\
   ((POINTER_SIZED_INT)(face_list)) ^\
   (*(const int *)(&points[0].x)) ^\
   (*(const int *)(&points[0].y)>>2) ^\
   (*(const int *)(&points[0].z)>>4) \
)



#define _hoops_PGHPA 15
GLOBAL_FUNCTION bool HI_Compute_Point_Inside_Shell (
	_hoops_AIGPR *	_hoops_RIGC,
	Point const *			pt, 
	int						point_count, 
	Point const *			points, 
	int						face_list_length, 
	int const *				face_list) 
{
	VBSP *					BSP = null;
	

	_hoops_RAHHA *	_hoops_CSC = null;
	
	if (_hoops_RIGC->_hoops_HSIHA != null) {
		_hoops_CSC = (_hoops_RAHHA *)_hoops_RIGC->_hoops_HSIHA;
		int _hoops_GRPPA = _hoops_ARPPA();
		if (_hoops_CSC->_hoops_GRPPA == _hoops_GRPPA) {
			BSP = _hoops_CSC->BSP;
		}
		else {
			if (_hoops_CSC->BSP != null) {
				HI_Delete_BSP (_hoops_CSC->BSP);
				_hoops_CSC->BSP = null;
			}
			BSP = null;
		}
		_hoops_CSC->_hoops_GRPPA = _hoops_GRPPA;
	}

	if (BSP == null) {
		_hoops_SASC  bbox(point_count, points);
		BSP = HI_New_BSP (HOOPS_WORLD->memory_pool, bbox, _hoops_PGHPA);
		_hoops_GAHPA (BSP, point_count, points, face_list_length, face_list, false);
	}

	_hoops_ARHHA		_hoops_PAHHA;


	_hoops_PAHHA.start.x = pt->x;
	_hoops_PAHHA.start.y = pt->y;
	_hoops_PAHHA.start.z = pt->z;
	_hoops_PAHHA._hoops_PSRGA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_GRHHA)(_hoops_RIGC->memory_pool);
	_hoops_PAHHA._hoops_SSGPA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_RRHHA)(_hoops_RIGC->memory_pool);
	_hoops_GRHHA * _hoops_ISIHA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_GRHHA)(_hoops_RIGC->memory_pool);

	int		i = 0;
	int		_hoops_SSPAR = 0;
	int		_hoops_CSIHA = 0;
	int		_hoops_SSIHA = 0;
	bool	_hoops_GGCHA = false;
	bool	_hoops_RGCHA = false;

	do {
		_hoops_PAHHA._hoops_PSRGA->SetCount(0);
		_hoops_PAHHA._hoops_SSGPA->SetCount(0);
		_hoops_PAHHA.abort = false;
		if (_hoops_IAHHA (i, &_hoops_PAHHA)) {
			/* _hoops_AGCHA _hoops_RAIGR: _hoops_PGCHA _hoops_IRS _hoops_HGGS _hoops_IGIAR _hoops_SPR _hoops_IIGR _hoops_RH _hoops_HGCHA */
			HI_Test_BSP_Ray (BSP, _hoops_RPHHA, (void *)points, &_hoops_PAHHA, &_hoops_PAHHA.start, &_hoops_PAHHA.direction);
			for (int j = 0; j < 2 && j < _hoops_PAHHA._hoops_PSRGA->Count(); j++)
				_hoops_ISIHA->Append((*_hoops_PAHHA._hoops_PSRGA)[j]);
		}
		else {
			if (_hoops_ISIHA->Count() != 0) {
				/* _hoops_AGCHA _hoops_IHAC: _hoops_PGCHA _hoops_IRS _hoops_HGGS _hoops_RHIR _hoops_SPR _hoops_IIGR _hoops_RH _hoops_RSSI _hoops_SGS _hoops_RH _hoops_IRSS _hoops_HGGS _hoops_RHHR */
				_hoops_SHPPA * _hoops_IGCHA = (*_hoops_ISIHA)[_hoops_ISIHA->Count()-1];
				_hoops_ISIHA->Pop();
				if (!_hoops_AAHHA (_hoops_IGCHA->len, _hoops_IGCHA->_hoops_GIPPA, points, &_hoops_PAHHA))
					break; /* _hoops_RGR _hoops_PAHA'_hoops_RA _hoops_SGIPR _hoops_IHPS */
			}
			else {
				/* _hoops_AGCHA _hoops_IHRPR: _hoops_SRPS _hoops_IRS _hoops_HSP _hoops_GGSR _hoops_IIGR _hoops_RH _hoops_HSP _hoops_HIGR _hoops_IS _hoops_PGCHA _hoops_IRS _hoops_HGGS _hoops_RHIR */
				if (!_hoops_HAHHA (_hoops_SSPAR, face_list_length, face_list, points, &_hoops_PAHHA))
					break;
				_hoops_SSPAR++;
			}
			HI_Test_BSP_Ray (BSP, _hoops_RPHHA, (void *)points, &_hoops_PAHHA, &_hoops_PAHHA.start, &_hoops_PAHHA.direction);
		}

		int _hoops_CGCHA = _hoops_RSIHA (_hoops_PAHHA._hoops_SSGPA);

		if (_hoops_CGCHA & 0x1) {
			/* _hoops_RPP _hoops_PISC */
			_hoops_RGCHA = true;
			_hoops_CSIHA++;
		}
		else {
			/* _hoops_RPP _hoops_PRGI */
			_hoops_RGCHA = false;
			_hoops_SSIHA++;
		}

		_hoops_GGCHA =  (_hoops_CGCHA != _hoops_PAHHA._hoops_SSGPA->Count() || _hoops_PAHHA.abort);

		for (int j = 0; j < _hoops_PAHHA._hoops_SSGPA->Count(); j++)
			FREE ((*_hoops_PAHHA._hoops_SSGPA)[j], float);

		i++;

	} while (_hoops_GGCHA && i < 20);

	delete _hoops_PAHHA._hoops_PSRGA;
	delete _hoops_PAHHA._hoops_SSGPA;
	delete _hoops_ISIHA;

	if (_hoops_CSC == null) {
		HI_BSP_Map_Function (BSP, _hoops_AAHPA, null);
		HI_Delete_BSP (BSP);
	}
	else
		_hoops_CSC->BSP = BSP;

	if (_hoops_GGCHA)
		_hoops_RGCHA = (_hoops_CSIHA > _hoops_SSIHA)? true : false;

	return _hoops_RGCHA;
} 


GLOBAL_FUNCTION bool HI_Compute_Point_On_Shell  (
	_hoops_AIGPR *	_hoops_RIGC,
	Point const *			pt, 
	double					tolerance,
	int						point_count, 
	Point const *			points, 
	int						face_list_length, 
	int const *				face_list) 
{
	VBSP *					BSP = null;

	_hoops_GAHHA	_hoops_SGCHA;
	_hoops_RAHHA *_hoops_CSC = null;
	int						_hoops_GRPPA;

	if (_hoops_RIGC->_hoops_HSIHA != null) {
		_hoops_CSC = (_hoops_RAHHA *)_hoops_RIGC->_hoops_HSIHA;
		_hoops_GRPPA = _hoops_ARPPA();
		if (_hoops_CSC->_hoops_GRPPA == _hoops_GRPPA) {
			BSP = _hoops_CSC->BSP;
		}
		else {
			if (_hoops_CSC->BSP != null) {
				HI_Delete_BSP (_hoops_CSC->BSP);
				_hoops_CSC->BSP = null;
			}
			BSP = null;
		}
		_hoops_CSC->_hoops_GRPPA = _hoops_GRPPA;
	}

	if (BSP == null) {
		_hoops_SASC _hoops_GRCHA(point_count, points);

		if (!_hoops_GRCHA._hoops_HPCIR(*pt, tolerance))
			return false;

		BSP = HI_New_BSP (HOOPS_WORLD->memory_pool, _hoops_GRCHA, _hoops_PGHPA);
		_hoops_GAHPA (BSP, point_count, points, face_list_length, face_list, false);
	}

	_hoops_SGCHA._hoops_RIGC = _hoops_RIGC;
	_hoops_SGCHA.pt = pt;
	_hoops_SGCHA.tolerance = tolerance;
	_hoops_SGCHA.result = false; 

	Vector _hoops_CAAPR(tolerance, tolerance, tolerance);

	_hoops_SASC bbox; 
	bbox.min = *pt - _hoops_CAAPR;
	bbox.max = *pt - _hoops_CAAPR;

	HI_Test_BSP (BSP, _hoops_GHHHA, (void *)points, &_hoops_SGCHA, bbox, false);

	if (_hoops_CSC == null) {
		HI_BSP_Map_Function (BSP, _hoops_AAHPA, null);
		HI_Delete_BSP (BSP);
	}
	else
		_hoops_CSC->BSP = BSP;

	return _hoops_SGCHA.result;
} 






#define _hoops_RRCHA			0x1
#define IDENTIFY_FACE_OPTION			0x2
#define _hoops_ARCHA				0x4
  
local const _hoops_IGRCR _hoops_PRCHA[] = {
	{_hoops_RRCHA, _hoops_GRRCR ("vertex vector"), _hoops_RRRCR, 0, true},
	{IDENTIFY_FACE_OPTION, _hoops_GRRCR ("identify face"), _hoops_RRRCR, 0, true},
	{_hoops_ARCHA, _hoops_GRRCR ("tolerance"), _hoops_SPPCR, 1, true}
 };

local const _hoops_HPAGA _hoops_HRCHA = {
	_hoops_GGAPR (_hoops_PRCHA),
	_hoops_PRCHA,
};


 
struct configs {
	bool	_hoops_IRCHA;
	bool	_hoops_CRCHA;
 	float		tolerance;
};

local bool _hoops_CHGAA (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			option_string,
	struct configs *		_hoops_SHGAA) 
{
	/* _hoops_ARP _hoops_SHIR _hoops_HSH _hoops_IH _hoops_HCR _hoops_IIGR _hoops_RH _hoops_GIGAA */
	_hoops_SHGAA->_hoops_IRCHA = false;
	_hoops_SHGAA->_hoops_CRCHA = false;
	_hoops_SHGAA->tolerance = 0;
 	if (option_string == null) 
		return false;

	_hoops_HIACR (_hoops_SRCHA, _hoops_PRCHA);

	Option_Value *	option_list = null;
	Option_Value *	option;

	if (!HI_Parse_Options (_hoops_RIGC, option_string, _hoops_CIACR (_hoops_SRCHA), &option_list, _hoops_SIACR))
		return false;

	if ((option = option_list) != null) do {
		if (!option->_hoops_GCACR) {
			switch (option->type->id) {
				case _hoops_RRCHA: {
					_hoops_SHGAA->_hoops_IRCHA = true;
				} break;
				case IDENTIFY_FACE_OPTION: {
					_hoops_SHGAA->_hoops_CRCHA = true;		
				}  break;
				case _hoops_ARCHA: {
					_hoops_SHGAA->tolerance = option->value._hoops_PIPCR[0];		
				} break;
			}
		}
	} while ((option = option->next) != null);

	HI_Free_Option_List (_hoops_RIGC, option_list);
	return true;
}













GLOBAL_FUNCTION void HI_Compute_Points_Inside_Shell (
	_hoops_AIGPR *	_hoops_RIGC,
	int						_hoops_GACHA,
	Point const *			_hoops_RACHA, 
	Point const *			_hoops_AACHA, 
	int						point_count, 
	Point const *			points, 
	int						face_list_length, 
	int const *				face_list,
	const char *			options,
	int *					results) 
{

 	struct configs	config;
	_hoops_CHGAA(_hoops_RIGC, options, &config);

	float	tolerance = config.tolerance;

	bool	_hoops_PACHA = false;

	if (_hoops_RIGC->_hoops_HSIHA == null) {
		HI_Begin_Shell_Selection (_hoops_RIGC);
		_hoops_PACHA = true;
	}
 
	_hoops_RAHHA *	_hoops_CSC = null;
	VBSP *							BSP = null;

	if (_hoops_RIGC->_hoops_HSIHA != null) {
		_hoops_CSC = (_hoops_RAHHA *)_hoops_RIGC->_hoops_HSIHA;
		int _hoops_GRPPA = _hoops_ARPPA();
		if (_hoops_CSC->_hoops_GRPPA == _hoops_GRPPA) {
			BSP = _hoops_CSC->BSP;
		}
		else {
			if (_hoops_CSC->BSP != null) {
				HI_Delete_BSP (_hoops_CSC->BSP);
				_hoops_CSC->BSP = null;
			}
			BSP = null;
		}
		_hoops_CSC->_hoops_GRPPA = _hoops_GRPPA;
	}
 
	if (BSP == null) {
		_hoops_SASC _hoops_GRCHA(point_count, points);
 		BSP = HI_New_BSP (HOOPS_WORLD->memory_pool, _hoops_GRCHA, _hoops_PGHPA);
		_hoops_GAHPA (BSP, point_count, points, face_list_length, face_list, false);
	}
	if (_hoops_CSC)
		_hoops_CSC->BSP = BSP;


	_hoops_SASC	_hoops_HACHA(_hoops_GACHA, _hoops_RACHA);
	
	if (tolerance)
		_hoops_HACHA._hoops_IACHA(tolerance);

	VBSP *	_hoops_CACHA = HI_New_BSP (HOOPS_WORLD->memory_pool, _hoops_HACHA, 32);

	_hoops_SACHA (_hoops_CACHA, _hoops_GACHA, _hoops_RACHA, tolerance);

	_hoops_PRHHA	_hoops_SGCHA;
	_hoops_SGCHA._hoops_RIGC = _hoops_RIGC;
	_hoops_SGCHA.points = points;
	_hoops_SGCHA.results = results;
	_hoops_SGCHA.faces = (int *)face_list;
	_hoops_SGCHA._hoops_RHGIR = face_list_length;
	_hoops_SGCHA._hoops_RISRA = point_count;
	_hoops_SGCHA.tolerance = tolerance;
	_hoops_SGCHA._hoops_CRHHA = BSP;

	if (config._hoops_IRCHA)
		_hoops_SGCHA._hoops_CIIRR = _hoops_AACHA;
	else
		_hoops_SGCHA._hoops_CIIRR = 0;

	if (config._hoops_CRCHA)
		_hoops_SGCHA._hoops_SRHHA = true;
	else
		_hoops_SGCHA._hoops_SRHHA = false;
	
	for (int i=0; i<_hoops_GACHA; i++)	
		results[i] = -3;		

	if (tolerance) 	
 		HI_Test_BSP_BSP(BSP, _hoops_RCHHA, &_hoops_SGCHA, _hoops_CACHA, false);

	HI_BSP_Map_Function (_hoops_CACHA, _hoops_AAHPA, null);
	HI_Delete_BSP (_hoops_CACHA);
	_hoops_CACHA = null;
	
	if (!config._hoops_CRCHA) {
		_hoops_CACHA = HI_New_BSP (HOOPS_WORLD->memory_pool, _hoops_HACHA, 12);
		_hoops_SACHA (_hoops_CACHA, _hoops_GACHA, _hoops_RACHA, tolerance);
		HI_Test_BSP_Bounding_Reject(_hoops_CACHA,_hoops_CCIHA, _hoops_GSIHA, &_hoops_SGCHA, 0, _hoops_HACHA);
	}
	
	if (!config._hoops_CRCHA) {
		for (int i=0; i<_hoops_GACHA; i++) {	
			if (results[i] == -3) {		
				if (HI_Compute_Point_Inside_Shell (_hoops_RIGC, (const Point *)&_hoops_RACHA[i], 
													_hoops_SGCHA._hoops_RISRA, _hoops_SGCHA.points, _hoops_SGCHA._hoops_RHGIR, _hoops_SGCHA.faces))
					results[i] = -1;
				else
					results[i] = -2;
			}
		}
	}
	if (_hoops_CSC == null) {
		HI_BSP_Map_Function (BSP, _hoops_AAHPA, null);
		HI_Delete_BSP (BSP);	
	}
	else
		_hoops_CSC->BSP = BSP;

	if (_hoops_PACHA)
		HI_End_Shell_Selection(_hoops_RIGC);	

	if (_hoops_CACHA) {	
		HI_BSP_Map_Function (_hoops_CACHA, _hoops_AAHPA, null);
		HI_Delete_BSP (_hoops_CACHA);
	}

}



GLOBAL_FUNCTION int HI_Compute_Points_On_Shell (
	_hoops_AIGPR *	_hoops_RIGC,
	int						_hoops_GACHA,
	Point const *			_hoops_RACHA, 
	double					tolerance,
	int						point_count, 
	Point const *			points, 
	int						face_list_length, 
	int const *				face_list,
	int *					results) 
{
	bool	_hoops_PACHA = false;

	if (_hoops_RIGC->_hoops_HSIHA == null) {
		HI_Begin_Shell_Selection (_hoops_RIGC);
		_hoops_PACHA = true;
	}
 
	_hoops_RAHHA *	_hoops_CSC = null;
	VBSP *							BSP = null;

	if (_hoops_RIGC->_hoops_HSIHA != null) {
		_hoops_CSC = (_hoops_RAHHA *)_hoops_RIGC->_hoops_HSIHA;
		int _hoops_GRPPA = _hoops_ARPPA();
		if (_hoops_CSC->_hoops_GRPPA == _hoops_GRPPA) {
			BSP = _hoops_CSC->BSP;
		}
		else {
			if (_hoops_CSC->BSP != null) {
				HI_Delete_BSP (_hoops_CSC->BSP);
				_hoops_CSC->BSP = null;
			}
			BSP = null;
		}
		_hoops_CSC->_hoops_GRPPA = _hoops_GRPPA;
	}

	if (BSP == null) {
		_hoops_SASC _hoops_GRCHA(point_count, points);
 		BSP = HI_New_BSP (HOOPS_WORLD->memory_pool, _hoops_GRCHA, _hoops_PGHPA);
		_hoops_GAHPA (BSP, point_count, points, face_list_length, face_list, false);
	}

	VBSP *	_hoops_CACHA = null;
	if (_hoops_CACHA == null) {
		_hoops_SASC _hoops_HACHA(_hoops_GACHA, _hoops_RACHA);

		if (tolerance)
			_hoops_HACHA._hoops_IACHA(tolerance);

 		_hoops_CACHA = HI_New_BSP (HOOPS_WORLD->memory_pool, _hoops_HACHA, 32);
		_hoops_SACHA (_hoops_CACHA, _hoops_GACHA, _hoops_RACHA, tolerance);
	}

	_hoops_PRHHA	_hoops_SGCHA;
	_hoops_SGCHA._hoops_RIGC = _hoops_RIGC;
	_hoops_SGCHA.points = points;
	_hoops_SGCHA.results = results;
	_hoops_SGCHA.faces = (int *)face_list;
	_hoops_SGCHA._hoops_RHGIR = face_list_length;
	_hoops_SGCHA._hoops_RISRA = point_count;
	_hoops_SGCHA.tolerance = tolerance;
	_hoops_SGCHA._hoops_CRHHA = BSP;
	_hoops_SGCHA._hoops_SRHHA = false;

	for (int i=0; i<_hoops_GACHA; i++)	
		results[i] = -1;		

	HI_Test_BSP_BSP(BSP, _hoops_RCHHA, &_hoops_SGCHA, _hoops_CACHA, false);

	HI_BSP_Map_Function (_hoops_CACHA, _hoops_AAHPA, null);
	HI_Delete_BSP (_hoops_CACHA);

	if (_hoops_CSC == null) {
		HI_BSP_Map_Function (BSP, _hoops_AAHPA, null);
		HI_Delete_BSP (BSP);	
	}
	else
		_hoops_CSC->BSP = BSP;

	if (_hoops_PACHA)
		HI_End_Shell_Selection(_hoops_RIGC);	


	int	_hoops_GPCHA = 0;

	for (int i=0; i<_hoops_GACHA; i++) {
		results[i] = ~results[i];
		if (results[i])
			_hoops_GPCHA++;
	}

	return _hoops_GPCHA;
} 




local int _hoops_RPCHA(
	_hoops_AIGPR *	_hoops_RIGC,
	int						_hoops_APCHA, 
	Point const *			_hoops_PPCHA,
	float					tolerance, 
	int						_hoops_HPCHA, 
	Point const *			_hoops_IPCHA,
	int						_hoops_RHGIR, 
	const int *				_hoops_ASPH, 
	float *					_hoops_CPCHA,
	int *					face_results)
{

	float *results;
 
	if (_hoops_CPCHA)	
		results = _hoops_CPCHA;
	else
		ALLOC_ARRAY(results, _hoops_APCHA, float);

  	_hoops_SASC bounding(_hoops_APCHA, _hoops_PPCHA);
	bounding.Merge(_hoops_HPCHA, _hoops_IPCHA);

	for (int i=0;i<_hoops_APCHA;i++) 
		results[i] = -1.0f;

	_hoops_HSHHA *	_hoops_RGIHA;	
	_hoops_HSHHA *	_hoops_GIIHA;
	int					size = 160;

	_hoops_PCCAR {
		_hoops_RGIHA = _hoops_PRIHA(bounding, tolerance, size,size,size);	
		_hoops_GIIHA = _hoops_PRIHA(bounding, tolerance, size,size,size);

		if (_hoops_RGIHA->items != null && _hoops_GIIHA->items != null)
			break;		// _hoops_RIRA _hoops_IS _hoops_PHHR

		if (_hoops_RGIHA->items != null)
			FREE_ARRAY(_hoops_RGIHA->items, _hoops_RGIHA->_hoops_PRAA*_hoops_RGIHA->_hoops_HRAA*_hoops_RGIHA->_hoops_CSHHA, _hoops_SCHHA);
		delete _hoops_RGIHA;
		if (_hoops_GIIHA->items != null)
			FREE_ARRAY(_hoops_GIIHA->items, _hoops_GIIHA->_hoops_PRAA*_hoops_GIIHA->_hoops_HRAA*_hoops_GIIHA->_hoops_CSHHA, _hoops_SCHHA);
		delete _hoops_GIIHA;


		size /= 2;	// _hoops_HPPR _hoops_HRHC
	}

	_hoops_AAIHA(_hoops_RIGC, _hoops_RGIHA, _hoops_IPCHA, _hoops_RHGIR, _hoops_ASPH);
	_hoops_RAIHA(_hoops_GIIHA, _hoops_APCHA, _hoops_PPCHA);

#if 1

 	_hoops_GGIHA _hoops_SPCHA;
	_hoops_GGIHA _hoops_GHCHA;
	_hoops_GGIHA _hoops_RHCHA;
	_hoops_GGIHA _hoops_AHCHA;

	_hoops_SPCHA._hoops_RGIHA = _hoops_RGIHA;
	_hoops_SPCHA._hoops_AGIHA = _hoops_GIIHA;
	_hoops_SPCHA.tolerance = tolerance;
	_hoops_SPCHA.results = results;
	_hoops_SPCHA.face_results = face_results;
	_hoops_SPCHA._hoops_RCAI = 0;

	_hoops_GHCHA._hoops_RGIHA = _hoops_RGIHA;
	_hoops_GHCHA._hoops_AGIHA = _hoops_GIIHA;
	_hoops_GHCHA.tolerance = tolerance;
	_hoops_GHCHA.results = results;
	_hoops_GHCHA.face_results = face_results;
	_hoops_GHCHA._hoops_RCAI = 1;

	_hoops_RHCHA._hoops_RGIHA = _hoops_RGIHA;
	_hoops_RHCHA._hoops_AGIHA = _hoops_GIIHA;
	_hoops_RHCHA.tolerance = tolerance;
	_hoops_RHCHA.results = results;
	_hoops_RHCHA.face_results = face_results;
	_hoops_RHCHA._hoops_RCAI = 2;

	_hoops_AHCHA._hoops_RGIHA = _hoops_RGIHA;
	_hoops_AHCHA._hoops_AGIHA = _hoops_GIIHA;
	_hoops_AHCHA.tolerance = tolerance;
	_hoops_AHCHA.results = results;
	_hoops_AHCHA.face_results = face_results;
	_hoops_AHCHA._hoops_RCAI = 3;

 
	int _hoops_PHCHA = 4;
	HThreadHandle *	threads;
	ALLOC_ARRAY(threads, _hoops_PHCHA, HThreadHandle);
	CREATE_THREAD(threads[0], CalculateDistanceThread, (void *)&_hoops_SPCHA);
	CREATE_THREAD(threads[1], CalculateDistanceThread, (void *)&_hoops_GHCHA);
	CREATE_THREAD(threads[2], CalculateDistanceThread, (void *)&_hoops_RHCHA);
	CREATE_THREAD(threads[3], CalculateDistanceThread, (void *)&_hoops_AHCHA);


	for(int i = 0; i < _hoops_PHCHA; ++i){
		JOIN_THREAD(threads[i]);
	}

	FREE_ARRAY(threads, _hoops_PHCHA, HThreadHandle);

#else	
	_hoops_SHIHA(_hoops_RGIHA, _hoops_GIIHA,tolerance,0, results);
	_hoops_SHIHA(_hoops_RGIHA, _hoops_GIIHA,tolerance,1, results);
	_hoops_SHIHA(_hoops_RGIHA, _hoops_GIIHA,tolerance,2, results);
	_hoops_SHIHA(_hoops_RGIHA, _hoops_GIIHA,tolerance,3, results);
#endif

	int _hoops_GPCHA = 0;
	for (int i=0; i<_hoops_APCHA; i++) {
 		if (results[i]>=0)
			_hoops_GPCHA++;
	}

	_hoops_GGIHA *	_hoops_HHCHA = NEW(_hoops_GGIHA)();
	_hoops_HHCHA->_hoops_RGIHA = _hoops_RGIHA;
	_hoops_HHCHA->_hoops_AGIHA = _hoops_GIIHA;

	NEW(_hoops_ACIHA)(_hoops_HHCHA);

	if (!_hoops_CPCHA)
		FREE_ARRAY(results, _hoops_APCHA, float);


	return _hoops_GPCHA;
}





#define _hoops_IHCHA				0x1
#define _hoops_CHCHA							0x2
#define _hoops_SHCHA							0x3
#define _hoops_GICHA					0x4


local const _hoops_IGRCR _hoops_RICHA[] = {
    {_hoops_CHCHA,	_hoops_GRRCR ("octree"),	_hoops_RRRCR, 0, false},
    {_hoops_SHCHA, 	_hoops_GRRCR ("grid"),		_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_AICHA = {
    _hoops_GGAPR (_hoops_RICHA),
    _hoops_RICHA,
};

  
local const _hoops_IGRCR _hoops_PICHA[] = {
	{_hoops_IHCHA, _hoops_GRRCR("mode"), _hoops_GHAGA, -999,false,	&_hoops_AICHA },
  };

local const _hoops_HPAGA _hoops_HICHA = {
	_hoops_GGAPR (_hoops_PICHA),
	_hoops_PICHA,
};




struct _hoops_IICHA {
	bool _hoops_CICHA;
	float tolerance;
	
};

local bool _hoops_SICHA (
	_hoops_AIGPR *					_hoops_RIGC,
	char const *							option_string,
	struct _hoops_IICHA *	_hoops_SHGAA) 
{


	/* _hoops_ARP _hoops_SHIR _hoops_HSH _hoops_IH _hoops_HCR _hoops_IIGR _hoops_RH _hoops_GIGAA */
	_hoops_SHGAA->_hoops_CICHA = true;	
	_hoops_SHGAA->tolerance = 0.5f;
 	if (option_string == null) 
		return false;

	_hoops_HIACR (_hoops_GCCHA, _hoops_PICHA);

	Option_Value *	option_list = null;
	Option_Value *	option;

	if (!HI_Parse_Options (_hoops_RIGC, option_string, _hoops_CIACR (_hoops_GCCHA), &option_list, _hoops_SIACR))
		return false;

	if ((option = option_list) != null) do {
		if (!option->_hoops_GCACR) {
			switch (option->type->id) {
				case _hoops_IHCHA: {
					if (option->value.option_list->type->id == _hoops_CHCHA)
						_hoops_SHGAA->_hoops_CICHA = true;
					else
						_hoops_SHGAA->_hoops_CICHA = false;
				} break;
 			}
		}
	} _hoops_RGGA ((option = option->next) == null);

	HI_Free_Option_List (_hoops_RIGC, option_list);
	return true;
}



GLOBAL_FUNCTION int HI_Compute_Points_Distance_From_Shell (
	_hoops_AIGPR *	_hoops_RIGC,
	int						_hoops_GACHA,
	Point const *			_hoops_RACHA, 
	double					tolerance,
	int						point_count, 
	Point const *			points, 
	int						face_list_length, 
	int const *				face_list,
	const char *			options,
	float *					results, 
	int *					face_results) 
{
 	struct _hoops_IICHA	config;
	_hoops_SICHA(_hoops_RIGC, options, &config);

	if (face_results)
	{
		for (int i=0;i<_hoops_GACHA;i++)
			face_results[i] = -1;
	}
	if (!config._hoops_CICHA)
		return (_hoops_RPCHA(_hoops_RIGC, _hoops_GACHA, _hoops_RACHA, tolerance,
			point_count, points, face_list_length, face_list, results, face_results));

	bool	_hoops_PACHA = false;
	if (_hoops_RIGC->_hoops_HSIHA == null) {
		HI_Begin_Shell_Selection (_hoops_RIGC);
		_hoops_PACHA = true;
	}
 
	_hoops_RAHHA *	_hoops_CSC = null;
	VBSP *							BSP = null;

	if (_hoops_RIGC->_hoops_HSIHA != null) {
		_hoops_CSC = (_hoops_RAHHA *)_hoops_RIGC->_hoops_HSIHA;
		int _hoops_GRPPA = _hoops_ARPPA();
		if (_hoops_CSC->_hoops_GRPPA == _hoops_GRPPA) {
			BSP = _hoops_CSC->BSP;
		}
		else {
			if (_hoops_CSC->BSP != null) {
				HI_Delete_BSP (_hoops_CSC->BSP);
				_hoops_CSC->BSP = null;
			}
			BSP = null;
		}
		_hoops_CSC->_hoops_GRPPA = _hoops_GRPPA;
	}

	if (BSP == null) {
		_hoops_SASC _hoops_GRCHA(point_count, points);
 		BSP = HI_New_BSP (HOOPS_WORLD->memory_pool, _hoops_GRCHA, _hoops_PGHPA);
		_hoops_GAHPA (BSP, point_count, points, face_list_length, face_list, false);
	}


	VBSP *	_hoops_CACHA = null;

	if (_hoops_CACHA == null) {
		_hoops_SASC _hoops_HACHA(_hoops_GACHA, _hoops_RACHA);
		if (tolerance)
			_hoops_HACHA._hoops_IACHA(tolerance);
 		_hoops_CACHA = HI_New_BSP (HOOPS_WORLD->memory_pool, _hoops_HACHA, 32);
		_hoops_SACHA (_hoops_CACHA, _hoops_GACHA, _hoops_RACHA, tolerance);
	}

	_hoops_PRHHA	_hoops_SGCHA;
	_hoops_SGCHA._hoops_RIGC = _hoops_RIGC;
	_hoops_SGCHA.points = points;
	if (results)	
		_hoops_SGCHA._hoops_HRHHA = results;
	else
		ALLOC_ARRAY(_hoops_SGCHA._hoops_HRHHA, _hoops_GACHA, float);
	_hoops_SGCHA._hoops_IRHHA = face_results;


	_hoops_SGCHA.faces = (int *)face_list;
	_hoops_SGCHA._hoops_RHGIR = face_list_length;
	_hoops_SGCHA._hoops_RISRA = point_count;
	_hoops_SGCHA.tolerance = tolerance;
	_hoops_SGCHA._hoops_CRHHA = BSP;
	_hoops_SGCHA._hoops_SRHHA = false;

	for (int i=0; i<_hoops_GACHA; i++)	
		_hoops_SGCHA._hoops_HRHHA[i] = -1.0f;		

	HI_Test_BSP_BSP(BSP, _hoops_ICHHA, &_hoops_SGCHA, _hoops_CACHA, false);

	HI_BSP_Map_Function (_hoops_CACHA, _hoops_AAHPA, null);
	HI_Delete_BSP (_hoops_CACHA);

	if (_hoops_CSC == null) {
		HI_BSP_Map_Function (BSP, _hoops_AAHPA, null);
		HI_Delete_BSP (BSP);	
	}
	else
		_hoops_CSC->BSP = BSP;

	if (_hoops_PACHA)
		HI_End_Shell_Selection(_hoops_RIGC);	


	int	_hoops_GPCHA = 0;

	for (int i=0; i<_hoops_GACHA; i++) {
 		if (_hoops_SGCHA._hoops_HRHHA[i]>=0)
			_hoops_GPCHA++;
	}

	if (!results)
		FREE_ARRAY(_hoops_SGCHA._hoops_HRHHA, _hoops_GACHA, float);
	return _hoops_GPCHA;
} 




HC_INTERFACE bool HC_CDECL HC_Compute_Point_Inside_Shell  (
	Point const *		pt, 
	int					point_count, 
	Point const *		points, 
	int					face_list_length, 
	int const *			face_list) 
{
	_hoops_PAPPR context("Compute_Point_Inside_Shell");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Point_Inside_Shell () */\n");
	);

	return HI_Compute_Point_Inside_Shell (context, pt, point_count, points, face_list_length, face_list);
}


HC_INTERFACE bool HC_CDECL HC_Compute_Point_On_Shell  (
	Point const *pt,
	double tolerance, 
	int point_count, 
	Point const *points, 
	int face_list_length, 
	int const *face_list) 
{
	_hoops_PAPPR context("Compute_Point_On_Shell");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Point_Inside_Shell () */\n");
	);

	return HI_Compute_Point_On_Shell (context, pt, (float)tolerance, point_count, points, face_list_length, face_list);
}


HC_INTERFACE void HC_CDECL HC_Compute_Points_Inside_Shell  (
	int				_hoops_GACHA,
	Point const *	_hoops_RACHA,
	Point const *	_hoops_RCCHA,
	int				point_count, 
	Point const *	points, 
	int				face_list_length, 
	int const *		face_list,
	char const *	options,
	int *			result) 
{
	_hoops_PAPPR context("Compute_Points_Inside_Shell");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Points_Inside_Shell () */\n");
	);

	HI_Compute_Points_Inside_Shell (
		context,
		_hoops_GACHA, _hoops_RACHA, 
		_hoops_RCCHA,
		point_count, points, 
		face_list_length, face_list, 
		options, result);
}


HC_INTERFACE int HC_CDECL HC_Compute_Points_Distance_F_Sh  (
	int				_hoops_GACHA,
	Point const *	_hoops_RACHA,
	double			tolerance, 
	int				point_count, 
	Point const *	points, 
	int				face_list_length, 
	int const *		face_list,
	char const *	options,
	float *			result) 
{
	_hoops_PAPPR context("Compute_Points_On_Shell");
	
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Points_On_Shell () */\n");
	);

	return HI_Compute_Points_Distance_From_Shell (
		context, 
		_hoops_GACHA, 
		_hoops_RACHA, 
		(float)tolerance, 
		point_count, points, 
		face_list_length, face_list, 
		options, result,0);
}

HC_INTERFACE int HC_CDECL HC_Compute_Points_Distance_F_S2  (
	int				_hoops_GACHA,
	Point const *	_hoops_RACHA,
	double			tolerance, 
	int				point_count, 
	Point const *	points, 
	int				face_list_length, 
	int const *		face_list,
	char const *	options,
	float *			results, 
	int *			face_results) 
{
	_hoops_PAPPR context("Compute_Points_On_Shell");
	
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Points_On_Shell () */\n");
	);

	return HI_Compute_Points_Distance_From_Shell (
		context, 
		_hoops_GACHA, 
		_hoops_RACHA, 
		(float)tolerance, 
		point_count, points, 
		face_list_length, face_list, 
		options, results,face_results);
}


HC_INTERFACE int HC_CDECL HC_Compute_Points_On_Shell  (
	int					_hoops_GACHA,
	Point const *		_hoops_RACHA,
	double				tolerance, 
	int					point_count, 
	Point const *		points, 
	int					face_list_length, 
	int const *			face_list,
	int *				result) 
{
	_hoops_PAPPR context("Compute_Points_On_Shell");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Points_On_Shell () */\n");
	);

	return HI_Compute_Points_On_Shell (context, _hoops_GACHA, _hoops_RACHA, (float)tolerance, point_count, points, face_list_length, face_list, result);
}

HC_INTERFACE void HC_CDECL HC_Compute_Shell_Enclosure  (
	int					point_count1, 
	Point const *		points1, 
	int					face_list_length1, 
	int const *			face_list1,
	int					point_count2, 
	Point const *		points2, 
	int					face_list_length2, 
	int const *			face_list2,
	char alter *		result) 
{
	_hoops_PAPPR context("Compute_Shell_Enclosure");
	
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Shell_Enclosure () */\n");
	);

	int polyline_count;
			
	if (!point_count1 || !point_count2 || !face_list_length2) {
		HI_Return_Chars (result, -1, "error", 5);
		return;
	}
	HI_Compute_Intersect_Polyline (context, point_count1,  points1, face_list_length1, face_list1,
									point_count2, points2, face_list_length2, face_list2,
									&polyline_count, null, null, null, false);
	if (polyline_count != 0) {
		HI_Return_Chars (result, -1, "clash", 5);
		return;
	}
	if (HI_Compute_Point_Inside_Shell (context, &points1[0], point_count2, points2, face_list_length2, face_list2))
		HI_Return_Chars (result, -1, "in", 2);
	else
		HI_Return_Chars (result, -1, "out", 3);
}



#else


GLOBAL_FUNCTION void HI_Delete_Point_Inside_Shell_Cache  (
						void *_hoops_HAHPA) 
{
	_hoops_IRPPR ("Selection By Shell");
	return 0;
}
HC_INTERFACE bool HC_CDECL HC_Compute_Point_Inside_Shell  (
						Point const *pt, 
						int point_count, 
						Point const *points, 
						int face_list_length, 
						int const *face_list) {
	_hoops_IRPPR ("Selection By Shell");
	return 0;
}
HC_INTERFACE bool HC_CDECL HC_Compute_Point_On_Shell  (
						Point const *pt, 
						double tolerance, 
						int point_count, 
						Point const *points, 
						int face_list_length, 
						int const *face_list) {
	_hoops_IRPPR ("Selection By Shell");
	return 0;
}

HC_INTERFACE void HC_CDECL HC_Compute_Shell_Enclosure  (
						int point_count1, 
						Point const *points1, 
						int face_list_length1, 
						int const *face_list1,
						int point_count2, 
						Point const *points2, 
						int face_list_length2, 
						int const *face_list2,
						char alter *result) {
	_hoops_IRPPR ("Selection By Shell");
	return 0;
}

#endif /* _hoops_CHS _hoops_SCHPA */



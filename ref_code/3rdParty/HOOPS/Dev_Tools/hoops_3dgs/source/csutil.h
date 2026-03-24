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
 * $Id: obf_tmp.txt 1.40.2.1 2011-01-10 23:56:05 guido Exp $
 */

#ifndef _hoops_SIPSA
#define _hoops_SIPSA

#include "hoops.h"
#include "adt.h"
#include "database.h"

/*------------_hoops_PIH _hoops_HRPR _hoops_PAIGR------------------*/

#define _hoops_GPHIA					1
#define _hoops_GCPSA	2
#define _hoops_GGPIA				3 /* _hoops_CACH _hoops_RCPSA._hoops_GSGGR */
#define _hoops_IGPIA		4 /* _hoops_CACH _hoops_RCPSA._hoops_GSGGR */
#define _hoops_RRPIA			5 /* _hoops_CACH _hoops_RCPSA._hoops_GSGGR */
#define _hoops_PGPIA			6 /* _hoops_CACH _hoops_RCPSA._hoops_GSGGR */
#define _hoops_PRPIA				7 /* _hoops_CACH _hoops_RCPSA._hoops_GSGGR */
#define _hoops_SGPIA				8 /* _hoops_CACH _hoops_RCPSA._hoops_GSGGR */
#define _hoops_ACPSA					9 /* _hoops_CACH _hoops_RCPSA._hoops_GSGGR */

extern "C" {

struct _hoops_SGGIA {
	_hoops_SASC	bbox;				/* _hoops_GAHIA _hoops_IASC _hoops_AHCRR _hoops_AARI _hoops_RH _hoops_CARA */
	char			type;
	char			flags;				/* _hoops_GPRR _hoops_SASI */
};


#define _hoops_GCIIA	 0x1	/* _hoops_PPGS _hoops_IH _hoops_RHIIA _hoops_HRGR _hoops_HCIAA _hoops_HHRI (_hoops_PPR _hoops_PRGPR _hoops_PIHA _hoops_SHH _hoops_PGHPR _hoops_HPGR _hoops_HHH _hoops_PPSR) */

struct _hoops_SHPPA : public _hoops_SGGIA {
	short			len;
	int const *		_hoops_GIPPA;			/* _hoops_CRS _hoops_CRGR _hoops_RH _hoops_HSP _hoops_HIGR (_hoops_PAR _hoops_CCGI' _hoops_GPHA _hoops_CIHA _hoops_CRPR) -- _hoops_RHAP _hoops_HAR _hoops_GCIS _hoops_SPCC. */
	_hoops_ARPA			plane;				/* _hoops_GAHIA _hoops_IPPA _hoops_IIGR _hoops_RH _hoops_HSP */
	int				index;
};


struct _hoops_ACHHA : public _hoops_SGGIA {
	int				_hoops_HCHHA;
	Point			vertex;
};

#define _hoops_PRHIA	0x1
struct _hoops_RRHIA : public _hoops_SGGIA {
	int				start;						
	int				end;
};


struct _hoops_PIGIA {
	_hoops_SHPPA *	f1;
	_hoops_SHPPA *	f2;
	float			min;
	float			max;
	void *			_hoops_IIAIA;
};

_hoops_SHPPA *_hoops_SIIIA(
	int					flags,
	int					len,
	int const *			indices, 
	Point const *		points,
	_hoops_HRPA const *	matrix,
	_hoops_ARPA const &		_hoops_PCPSA,
	int					index);


_hoops_ACHHA *_hoops_HCPSA( 
	Point const *	point, 
	float			tolerance, 
	int				_hoops_HCHHA);

_hoops_RRHIA *_hoops_HSIIA( 
	int					start,
	int					end,
	PolyCylinder *		_hoops_HSPIR,
	_hoops_HRPA const *	matrix);

/* _hoops_PAPIA _hoops_SPASR _hoops_SSSAR.  
 * _hoops_ICPSA _hoops_HPGR _hoops_GPRR _hoops_GGR _hoops_RGSPR _hoops_IS _hoops_CGIC _hoops_PGAP _hoops_CCPSA _hoops_IS _hoops_AASA */
_hoops_CSCAR _hoops_AAHPA( void *ptr, void *_hoops_PIPPA );

void _hoops_IPPPA(
	Point const * _hoops_GAPPA, 
	Point const * _hoops_RAPPA, 
	_hoops_ARPA const * _hoops_AAPPA, 
	Point alter * _hoops_PAGR);

#define _hoops_CPHHA		0  /* _hoops_PIHA _hoops_SHH _hoops_AHHR */
#define _hoops_HPHHA		1
#define _hoops_IPHHA	2

int _hoops_AHHHA( 
	Point const *	pt,
	Point const *	points1,
	int				_hoops_HRPPA,
	const int *		_hoops_AIIPR,
	_hoops_ARPA const *	_hoops_IRPPA,
	float			tolerance);

void _hoops_SCPSA( 
	Point		 *	pt,
	Point const *	points1,
	int				_hoops_HRPPA,
	const int *		_hoops_AIIPR,
	_hoops_ARPA const *	_hoops_IRPPA,
	float			tolerance);

bool _hoops_IIPPA( 
	Point const *	points1, 
	int				_hoops_HRPPA,
	const int *		_hoops_AIIPR,
	_hoops_ARPA const *	_hoops_IRPPA,
	Point const *	points2,
	int				_hoops_SPPPA,
	const int *		_hoops_HIIPR,
	_hoops_ARPA const *	_hoops_CRPPA,
	Point *			_hoops_GSPSA);

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
	bool				_hoops_PRRIA = true);

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
	Point *			_hoops_GSPSA,
	float			_hoops_RCPIA = 0.0f);

bool _hoops_HIPPA(
	Point const *	points, 
	int				len,
	const int *		_hoops_GAHI,
	_hoops_ARPA const &	plane); 

bool _hoops_PSPSA( 
	Point const *	points, 
	int				len,
	const int *		_hoops_GAHI,
	_hoops_ARPA const *	plane,
	float			_hoops_RCPIA); 

void _hoops_GAHPA(
	VBSP *			tree, 
	int				point_count, 
	Point const *	points, 
	int				face_list_length, 
	const int *		face_list, 
	bool			_hoops_HSPSA); 

void _hoops_SACHA( 
	VBSP *			tree, 
	int				point_count, 
	Point const *	points,
	float			tolerance);

void _hoops_CHHIA(
	Point const *			points, 
	_hoops_HRPA const *		matrix,
	int						len,
	int const *				_hoops_GAHI, 
	_hoops_SASC alter &	_hoops_ISPSA); 

bool _hoops_APHIA(
	Point const *	_hoops_SRHC, 
	int				len,
	int const *		_hoops_GAHI, 
	bool			_hoops_HSPSA,
	_hoops_ARPA alter *	_hoops_RGHIA); 

int _hoops_PPHHA(
	Point const *		points, 
	_hoops_SHPPA const *	face,
	Point const *		start, 
	Vector const *		direction, 
	float alter *		_hoops_CSPSA,
	Point alter *		_hoops_SSPSA);

int _hoops_SGHIA( 
	Point const *		points, 
	_hoops_SHPPA const *	face,
	Point const *		p1, 
	Point const *		p2);

} //_hoops_GGHSA

#endif

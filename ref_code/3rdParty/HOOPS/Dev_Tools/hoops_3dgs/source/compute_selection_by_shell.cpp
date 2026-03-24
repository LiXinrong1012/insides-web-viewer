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
 * $Id: obf_tmp.txt 1.275.2.1 2011-01-10 23:56:05 guido Exp $
 */

#include "hoops.h"
#include "phedron.h"
#include "adt.h"
#include "hpserror.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hd_proto.h"


#ifndef _hoops_CACIR
# define _hoops_CACIR (1e-5f)
#endif


#ifndef _hoops_SSAPA


#include "csutil.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#define _hoops_GSSHA 24
#define _hoops_RSSHA 32
#define _hoops_GIAHA 16
#define _hoops_ASSHA 5
#define _hoops_PSSHA ((360/5)+10)


/*------------_hoops_PIH _hoops_HCCGR------------------*/

struct _hoops_HSSHA {
	Point const *	start;
	Vector const *	direction;
};


struct _hoops_ISSHA {
	int					face;
	Vector				direction;
	_hoops_CSSHA	_hoops_SSSHA;
	int					start;
	int					end;
	bool				used;
	int					_hoops_GGGIA;
	_hoops_ISSHA *			_hoops_RGGIA;
};


#define _hoops_AGGIA				0x1
/* _hoops_PAIGR _hoops_SASI _hoops_IS _hoops_PGGIA._hoops_PPCAR._hoops_GGHR._hoops_SGI */
#define _hoops_HGGIA	0x2
#define _hoops_IGGIA		0x4

struct _hoops_CGGIA : public _hoops_SGGIA{
	/* _hoops_PIISR _hoops_GGR _hoops_CRGC */
	float			_hoops_GRGIA;
	float			_hoops_RRGIA;
	Key				key; /* _hoops_HAR _hoops_SSCC _hoops_HSGS _hoops_RPP _hoops_GSIPR-_hoops_ARGIA */
	_hoops_HRPA	*	matrix; /* _hoops_RH _hoops_PRGIA _hoops_RSGA _hoops_HPGR _hoops_RH _hoops_PPSR _hoops_CGPR _hoops_SR _hoops_HRGIA */
	_hoops_IRGIA *		path; /* _hoops_RH _hoops_CRPR _hoops_IIGR _hoops_CAGH _hoops_CRGIA _hoops_HPP _hoops_PGAP _hoops_SR _hoops_HRGIA _hoops_HPGR _hoops_RGR _hoops_CARA */
};

/* _hoops_IGI _hoops_IH _hoops_SRGIA _hoops_SCHS (_hoops_PAR _hoops_GAGIA _hoops_IIGR _hoops_SCHS) _hoops_HII _hoops_RH _hoops_RHI */
struct _hoops_RAGIA : public _hoops_CGGIA {
	/* _hoops_PIISR _hoops_GGR _hoops_RHSP _hoops_AAGIA, _hoops_RAS _hoops_PPGAR _hoops_PAGPR _hoops_RHHR */
	VBSP *				BSP;
	Polyhedron *		phon;
	Point *				_hoops_PAGIA;
	_hoops_ARPA *				_hoops_HAGIA;
	_hoops_SHPPA *		_hoops_IAGIA;
	Point				_hoops_CAGIA;
};


/* _hoops_PAHGA _hoops_IRS _hoops_HGAGA _hoops_IIGR "_hoops_IHGP" _hoops_CPAP _hoops_CSSC:
	_hoops_SAGIA, _hoops_GPGIA, _hoops_RPGIA, _hoops_APGIA, _hoops_PPGIA */
struct _hoops_HPGIA : public _hoops_CGGIA {
	/* _hoops_PIISR _hoops_GGR _hoops_RHSP _hoops_AAGIA, _hoops_RAS _hoops_PPGAR _hoops_PAGPR _hoops_RHHR */
	VBSP *				BSP;
	_hoops_IPGIA *	_hoops_CPGIA;
};


/* _hoops_IGI _hoops_IH _hoops_SRGIA _hoops_HAHAR (_hoops_PAR _hoops_SPGIA _hoops_IIGR _hoops_HAHAR) _hoops_HII _hoops_RH _hoops_RHI */
struct _hoops_GHGIA : public _hoops_CGGIA {
	/* _hoops_PIISR _hoops_GGR _hoops_RHSP _hoops_AAGIA, _hoops_RAS _hoops_PPGAR _hoops_PAGPR _hoops_RHHR */
	VBSP *				BSP;
	PolyCylinder *		_hoops_HSPIR;
};


/* _hoops_IGI _hoops_IH _hoops_SRGIA _hoops_HAHAR (_hoops_PAR _hoops_SPGIA _hoops_IIGR _hoops_HAHAR) _hoops_HII _hoops_RH _hoops_RHI */
struct _hoops_RHGIA : public _hoops_CGGIA {
	Sphere *			s;
};


/* _hoops_IGI _hoops_IH _hoops_SRGIA _hoops_GCPA (_hoops_PAR _hoops_SPGIA _hoops_IIGR _hoops_GCPA) _hoops_HII _hoops_RH _hoops_RHI */
struct _hoops_AHGIA : public _hoops_CGGIA {
	Cylinder *			c;
};


struct _hoops_PHGIA : public _hoops_CGGIA {
	/* _hoops_PIISR _hoops_GGR _hoops_RHSP _hoops_AAGIA, _hoops_RAS _hoops_PPGAR _hoops_PAGPR _hoops_RHHR */
	bool				_hoops_HHGIA;
	Grid *				_hoops_IHGIA;
};


struct _hoops_CHGIA {
	_hoops_RAGIA *	_hoops_SHGIA;
	_hoops_HRPA			matrix;
	bool				_hoops_GIGIA;
};

struct _hoops_RIGIA {
	float	x, y, z, t;
	int		_hoops_SSPAR;
};

typedef VList<_hoops_CGGIA *> _hoops_AIGIA;
typedef VList<_hoops_PIGIA *> _hoops_HIGIA;
typedef VList<_hoops_ISSHA *> _hoops_IIGIA;

typedef VHash<Key, _hoops_CHGIA *> _hoops_CIGIA;
typedef VHash<POINTER_SIZED_INT, _hoops_ISSHA *> _hoops_SIGIA;

typedef VArray<_hoops_CGGIA *> _hoops_GCGIA;
typedef VArray<_hoops_RIGIA *> _hoops_RCGIA;
//_hoops_ACGIA _hoops_PCGIA<_hoops_HCGIA *> _hoops_ICGIA;

/* _hoops_IGI _hoops_IH _hoops_SRGIA _hoops_RH _hoops_RRCPR _hoops_HII _hoops_RH _hoops_ARIP, _hoops_IPSH _hoops_AGRR _hoops_RII _hoops_HRSAR _hoops_PIH _hoops_RHSP _hoops_RH
 * _hoops_IHPHR _hoops_IIGR _hoops_IRS _hoops_HGGAR */
struct global_compare_info {
	_hoops_AIGPR *			_hoops_RIGC;
	Key								_hoops_CCGIA;
	Point const *					_hoops_SCGIA;
	Vector *						_hoops_GSGIA;
	const int *						_hoops_RSGIA;
	VBSP *							_hoops_ASGIA;
	_hoops_HSSHA *							_hoops_PSGIA;
	_hoops_CGGIA *					_hoops_HSGIA;
	_hoops_GCGIA *				_hoops_ISGIA;
	int								_hoops_CSGIA;
	_hoops_AIGIA *					_hoops_SSGIA;
	_hoops_HIGIA *			_hoops_GGRIA;
 	_hoops_RCGIA *	_hoops_RGRIA;
	int								_hoops_AGRIA;
	_hoops_GCGIA *				_hoops_PGRIA;
	VBSP *							tree;
	float							_hoops_HGRIA;
	float							_hoops_IGRIA;
	float							_hoops_CGRIA;

	_hoops_CIGIA *			_hoops_SGRIA;
	bool							_hoops_GRRIA;
	float							_hoops_RRRIA;
	bool							_hoops_ARRIA;
	bool							_hoops_PRRIA;

	_hoops_SASC					*_hoops_HRRIA;
 	struct {
		int _hoops_IRRIA;
		int _hoops_CRRIA;
		int _hoops_SRRIA;
	} _hoops_GARIA;
};




/*------------_hoops_PAGPR _hoops_RARIA------------------*/

local bool _hoops_IHHHA(Point *p, Point *pl,int _hoops_RHGIR)
{
	_hoops_ARPA _hoops_IRPA;

	HI_Figure_Plane_From_Points(_hoops_RHGIR, pl, &_hoops_IRPA);

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

		_hoops_ARPA _hoops_CHHHA;
		Point pp[3];

		pp[0] = pl[i1];
		pp[1] = pl[i2];
		pp[2] = pl[i1] + Vector(_hoops_IRPA);
		HI_Figure_Plane_From_Points(3, pp, &_hoops_CHHHA);

		float dist = ((_hoops_CHHHA.a * p->x + _hoops_CHHHA.b * p->y + _hoops_CHHHA.c * p->z + _hoops_CHHHA.d) /
						sqrt(_hoops_CHHHA.a * _hoops_CHHHA.a + _hoops_CHHHA.b * _hoops_CHHHA.b + _hoops_CHHHA.c * _hoops_CHHHA.c));

		if (dist>0)
			return false;
	}

	return true;
}


local float _hoops_AARIA (Point *_hoops_PARIA, Point *_hoops_HARIA, Point *_hoops_IARIA, Point *_hoops_CARIA, Point *_hoops_SCAAA, Point *_hoops_GSAAA)
{
	Vector _hoops_SARIA;
	Vector _hoops_GPRIA;

	double  _hoops_RPRIA,  _hoops_APRIA,  _hoops_PPRIA,
			_hoops_HPRIA, _hoops_IPRIA, _hoops_CPRIA,
			_hoops_SPRIA, _hoops_GHRIA, _hoops_RHRIA;

	double dist;

/*	 _hoops_AHRIA _hoops_IS _hoops_SHH _hoops_IGI _hoops_IH _hoops_PSCHR _hoops_RSSSR */
	double  X_x1, X_Y, X_X, X_y1,
			_hoops_PHRIA, _hoops_HHRIA, _hoops_IHRIA, X_y2,
			_hoops_CHRIA;

	/*	 _hoops_SHRIA _hoops_CCPAR _hoops_HII _hoops_SHPR
		 _hoops_HGI _hoops_GIRIA _hoops_RH _hoops_RIRIA _hoops_CCPAR
		 _hoops_AIRIA _hoops_PIRIA _hoops_HIRIA  */
	double              _hoops_IIRIA,_hoops_CIRIA = 0.0, _hoops_SIRIA = 0.0;


	/*
	 _hoops_GCRIA _hoops_RH _hoops_AAGA _hoops_SPCR = _hoops_RCRIA->_hoops_ACRIA
	 _hoops_HAPI _hoops_RCRIA = (_hoops_AIRIA, _hoops_PCRIA, _hoops_HCRIA)
	 _hoops_HAPI _hoops_ACRIA = (_hoops_ICRIA, _hoops_CCRIA, _hoops_SCRIA)
	*/

	_hoops_SARIA.x = _hoops_HARIA->x - _hoops_PARIA->x;
	_hoops_SARIA.y = _hoops_HARIA->y - _hoops_PARIA->y;
	_hoops_SARIA.z = _hoops_HARIA->z - _hoops_PARIA->z;

	/*
	 _hoops_GCRIA _hoops_RH _hoops_AAGA _hoops_GHCR = _hoops_GSRIA->_hoops_RSRIA
	 _hoops_HAPI _hoops_GSRIA = (_hoops_ASRIA, _hoops_PSRIA, _hoops_HSRIA)
	 _hoops_HAPI _hoops_RSRIA = (_hoops_ISRIA, _hoops_CSRIA, _hoops_SSRIA)
	 */

	_hoops_GPRIA.x = _hoops_CARIA->x - _hoops_IARIA->x;
	_hoops_GPRIA.y = _hoops_CARIA->y - _hoops_IARIA->y;
	_hoops_GPRIA.z = _hoops_CARIA->z - _hoops_IARIA->z;

	/* _hoops_GCRIA _hoops_RH _hoops_PSCHR _hoops_RSSSR */

	X_x1 = HI_Compute_Dot_Product(&_hoops_SARIA,(Vector const*)_hoops_PARIA);
	X_Y = HI_Compute_Dot_Product(&_hoops_SARIA, (Vector const*)&_hoops_GPRIA);
	X_X = HI_Compute_Dot_Product(&_hoops_SARIA, (Vector const*)&_hoops_SARIA);
	X_y1 = HI_Compute_Dot_Product(&_hoops_SARIA,(Vector const*)_hoops_IARIA);
	_hoops_PHRIA = HI_Compute_Dot_Product(&_hoops_GPRIA, (Vector const*)&_hoops_GPRIA);
	_hoops_IHRIA = HI_Compute_Dot_Product(&_hoops_GPRIA,(Vector const*)_hoops_IARIA);
	_hoops_HHRIA = HI_Compute_Dot_Product(&_hoops_GPRIA,(Vector const*)_hoops_PARIA);
	X_y2 = HI_Compute_Dot_Product(&_hoops_SARIA,(Vector const*)_hoops_CARIA);
	_hoops_CHRIA = HI_Compute_Dot_Product(&_hoops_GPRIA,(Vector const*)_hoops_HARIA);

	_hoops_RPRIA = (X_X * _hoops_PHRIA) - (X_Y * X_Y);

	if (_hoops_RPRIA == 0) {
		/* _hoops_GPGP _hoops_RH _hoops_AGIR _hoops_IIGR _hoops_GGAIA _hoops_RGAIA _hoops_SGHC,
		_hoops_IIH _hoops_CHR _hoops_AGAIA _hoops_RSSA _hoops_SGS _hoops_GRS _hoops_IPHR.
		_hoops_PS _hoops_GRS _hoops_SGH _hoops_RH _hoops_APSSR _hoops_IIGR _hoops_AGCR.*/

		/* _hoops_IPCP _hoops_AGIR _hoops_IIGR _hoops_IRS _hoops_CAGH _hoops_APHR _hoops_PPR _hoops_PGAIA
		 _hoops_HPGR _hoops_RH _hoops_PSHR _hoops_PPSR _hoops_HRGR _hoops_GACC _hoops_GIR _hoops_ARI.*/

		/* _hoops_CPGP _hoops_HGAIA _hoops_HRGR _hoops_RH _hoops_PSCHR _hoops_HPAHR _hoops_IIGR _hoops_RH
		 _hoops_AAGA _hoops_SPCR _hoops_IACH _hoops_ACAS, _hoops_SCH _hoops_HRGR _hoops_RGAR 0.0
		 _hoops_CGPR _hoops_SPCR _hoops_HRGR _hoops_IIGR _hoops_AHHR _hoops_SPCC. */

		if (X_X != 0.0) {
			/* _hoops_IGAIA _hoops_PPSR _hoops_IS _hoops_GSRIA */
			_hoops_CPRIA = (X_y1 - X_x1) / X_X;

			if (_hoops_CPRIA < 0.0)
				_hoops_CPRIA = 0.0;
			else if (_hoops_CPRIA > 1.0)
				_hoops_CPRIA = 1.0;

			/* _hoops_IGAIA _hoops_PPSR _hoops_IS _hoops_RSRIA */
			_hoops_GHRIA = (X_y2 - X_x1) / X_X;
			if (_hoops_GHRIA < 0.0)
					_hoops_GHRIA = 0.0;
			else if (_hoops_GHRIA > 1.0)
				_hoops_GHRIA = 1.0;
		}
		else {
			_hoops_CPRIA = 0.0;
			_hoops_GHRIA = 0.0;
		}

		/* _hoops_CPGP _hoops_CGAIA _hoops_HRGR _hoops_RH _hoops_PSCHR _hoops_HPAHR _hoops_IIGR _hoops_RH
		 _hoops_AAGA _hoops_GHCR _hoops_IACH _hoops_ACAS, _hoops_SCH _hoops_HRGR _hoops_RGAR 0.0
		 _hoops_CGPR _hoops_GHCR _hoops_HRGR _hoops_IIGR _hoops_AHHR _hoops_SPCC. */

		if (_hoops_PHRIA != 0.0) {
			/*  _hoops_IGAIA _hoops_PPSR _hoops_IS _hoops_RCRIA */
			_hoops_SPRIA = (_hoops_HHRIA - _hoops_IHRIA) / _hoops_PHRIA;
			if (_hoops_SPRIA < 0.0)
				_hoops_SPRIA = 0.0;
			else if (_hoops_SPRIA > 1.0)
				_hoops_SPRIA =1.0;

			/*  _hoops_IGAIA _hoops_PPSR _hoops_IS _hoops_ACRIA */
			_hoops_RHRIA = (_hoops_CHRIA - _hoops_IHRIA) / _hoops_PHRIA;

			if (_hoops_RHRIA < 0.0)
				_hoops_RHRIA = 0.0;
			else if (_hoops_RHRIA > 1.0)
				_hoops_RHRIA =1.0;
		}
		else {
			_hoops_SPRIA = 0.0;
			_hoops_RHRIA = 0.0;
		}

		/* _hoops_SGAIA _hoops_RH _hoops_APSSR */
		_hoops_CIRIA = (_hoops_CPRIA + _hoops_GHRIA) / 2;
		_hoops_SIRIA = (_hoops_SPRIA + _hoops_RHRIA) / 2;

		_hoops_IIRIA = 0;
	}
	else {
		/* _hoops_AGGA _hoops_RH _hoops_AGIR _hoops_IIGR _hoops_GRAIA _hoops_SGHC
		_hoops_IIGR _hoops_RRAIA _hoops_SPCC _hoops_HRGR _hoops_GIR.
		  _hoops_GAIRA + _hoops_HPGHR + _hoops_IHRPR = 0
		  _hoops_ARAIA + _hoops_PRAIA + _hoops_HRAIA = 0 _hoops_SSCP _hoops_IRAIA _hoops_IIGR

		 _hoops_SISR = (_hoops_CRAIA - _hoops_SRAIA) / (_hoops_GAAIA - _hoops_RAAIA) _hoops_GCPAR
		 _hoops_HAPC = (_hoops_AAAIA - _hoops_PAAIA) / (_hoops_GAAIA - _hoops_RAAIA) _hoops_ARSAR (_hoops_GAAIA - _hoops_RAAIA) <> 0
		*/

		_hoops_APRIA = (X_Y * _hoops_HHRIA) - (X_Y * _hoops_IHRIA)
						- (_hoops_PHRIA * X_x1) + (_hoops_PHRIA * X_y1);
		_hoops_PPRIA = (X_X * _hoops_HHRIA) - (X_X * _hoops_IHRIA)
						+ (X_Y * X_y1) - (X_Y * X_x1);

		/* _hoops_HAAIA _hoops_IH _hoops_RH _hoops_III _hoops_PPR _hoops_SGHC _hoops_SISPR _hoops_RH
		 _hoops_PSHR _hoops_PSAI _hoops_IIGR _hoops_PHRHA _hoops_RSSA.
		 */

		_hoops_HPRIA = _hoops_APRIA / _hoops_RPRIA;
		_hoops_IPRIA = _hoops_PPRIA / _hoops_RPRIA;

		/* _hoops_IGAIA _hoops_PPSR _hoops_IS _hoops_GSRIA */
		_hoops_CPRIA = (X_y1 - X_x1) / X_X;

		/* _hoops_IGAIA _hoops_PPSR _hoops_IS _hoops_RCRIA */
		_hoops_SPRIA = (_hoops_HHRIA - _hoops_IHRIA) / _hoops_PHRIA;

		/* _hoops_IGAIA _hoops_PPSR _hoops_IS _hoops_RSRIA */
		_hoops_GHRIA = (X_y2 - X_x1) / X_X;

		/* _hoops_IGAIA _hoops_PPSR _hoops_IS _hoops_ACRIA */
		_hoops_RHRIA = (_hoops_CHRIA - _hoops_IHRIA) / _hoops_PHRIA;

		/* _hoops_IAAIA _hoops_HHCPR

		 _hoops_SGSH _hoops_CCA _hoops_RH _hoops_RHAR _hoops_AGIR _hoops_IIGR _hoops_APGR _hoops_PPR _hoops_SGHC
		 _hoops_SISPR _hoops_RH _hoops_PSHR _hoops_PSAI _hoops_IIGR _hoops_PHRHA _hoops_RSSA.
		 */

		if ((0.0 <= _hoops_HPRIA) && (_hoops_HPRIA <= 1.0)
			&& (0.0 <= _hoops_IPRIA)  && (_hoops_IPRIA <= 1.0)) {
			_hoops_CIRIA = _hoops_HPRIA;
			_hoops_SIRIA = _hoops_IPRIA;
			_hoops_IIRIA = 1;
		}
		else if ((_hoops_HPRIA < 0.0) && (0.0 <= _hoops_IPRIA)
			&& (_hoops_IPRIA <= 1.0)) {
			_hoops_CIRIA = _hoops_HPRIA;
			_hoops_SIRIA = _hoops_SPRIA;
			_hoops_IIRIA = 2;
		}
		else if ((1.0 < _hoops_HPRIA) && (0.0 <= _hoops_IPRIA)
			&& (_hoops_IPRIA <= 1.0)) {
			_hoops_CIRIA = _hoops_HPRIA;
			_hoops_SIRIA = _hoops_RHRIA;
			_hoops_IIRIA = 3;
		}
		else if ((0.0 <= _hoops_HPRIA) && (_hoops_HPRIA <= 1.0) && (_hoops_IPRIA < 0.0)) {
			_hoops_CIRIA = _hoops_CPRIA;
			_hoops_SIRIA = _hoops_IPRIA;
			_hoops_IIRIA = 4;
		}
		else if ((0.0 <= _hoops_HPRIA) && (_hoops_HPRIA <= 1.0) && (1.0 < _hoops_IPRIA)) {
			_hoops_CIRIA = _hoops_GHRIA;
			_hoops_SIRIA = _hoops_IPRIA;
			_hoops_IIRIA = 5;
		}
		else if ((_hoops_HPRIA < 0.0) && (_hoops_IPRIA < 0.0)) {
			_hoops_CIRIA = _hoops_CPRIA;
			_hoops_SIRIA = _hoops_SPRIA;
			_hoops_IIRIA = 6;
		}
		else if ((_hoops_HPRIA < 0.0) && (1.0 < _hoops_IPRIA)) {
			_hoops_CIRIA = _hoops_GHRIA;
			_hoops_SIRIA = _hoops_SPRIA;
			_hoops_IIRIA = 7;
		}
		else if ((1.0 < _hoops_HPRIA) && (_hoops_IPRIA < 0.0)) {
			_hoops_CIRIA = _hoops_CPRIA;
			_hoops_SIRIA = _hoops_RHRIA;
			_hoops_IIRIA = 8;
		}
		else if ((1.0 < _hoops_HPRIA) && (1.0 < _hoops_IPRIA)) {
			_hoops_CIRIA = _hoops_GHRIA;
			_hoops_SIRIA = _hoops_RHRIA;
			_hoops_IIRIA = 9;
		}

		/*      _hoops_CRCI _hoops_CPHR _hoops_ARI _hoops_ICHHR _hoops_RH _hoops_CAAIA _hoops_RPP _hoops_ARRS _hoops_SAAIA. */
		if (_hoops_CIRIA < 0.0)
			_hoops_CIRIA = 0.0;
		else if (_hoops_CIRIA > 1.0)
			_hoops_CIRIA = 1.0;

		if (_hoops_SIRIA < 0.0)
			_hoops_SIRIA = 0.0;
		else if (_hoops_SIRIA > 1.0)
			_hoops_SIRIA = 1.0;
	}

	/*      _hoops_GPAIA  _hoops_HACH _hoops_RPAIA */

	_hoops_SCAAA->x  = _hoops_CIRIA * _hoops_SARIA.x + _hoops_PARIA->x;
	_hoops_SCAAA->y  = _hoops_CIRIA * _hoops_SARIA.y + _hoops_PARIA->y;
	_hoops_SCAAA->z  = _hoops_CIRIA * _hoops_SARIA.z + _hoops_PARIA->z;
	_hoops_GSAAA->x  = _hoops_SIRIA * _hoops_GPRIA.x + _hoops_IARIA->x;
	_hoops_GSAAA->y  = _hoops_SIRIA * _hoops_GPRIA.y + _hoops_IARIA->y;
	_hoops_GSAAA->z  = _hoops_SIRIA * _hoops_GPRIA.z + _hoops_IARIA->z;


	dist = _hoops_SRCIR(*_hoops_SCAAA, *_hoops_GSAAA);
	return dist;
}



#define _hoops_APAIA (3.14159265358979323846264338327950288)

#define _hoops_PPAIA(r) ((r) * 180.0f / _hoops_APAIA)

local bool _hoops_HPAIA(Point & p1, Point & p2,
								 Point & _hoops_IPAIA, Point & _hoops_CPAIA, Point & _hoops_HSPIR,
								 Point * p, bool _hoops_SPAIA = true)
{
   float d;
   float a1,a2,a3;
   float total,_hoops_SSHGA,_hoops_GHAIA;
   Vector n,_hoops_RHAIA,_hoops_AHAIA,_hoops_PHAIA;

   /* _hoops_PSIH _hoops_RH _hoops_GRPAR _hoops_IH _hoops_RH _hoops_IPPA */
   n.x = (_hoops_CPAIA.y - _hoops_IPAIA.y)*(_hoops_HSPIR.z - _hoops_IPAIA.z) - (_hoops_CPAIA.z - _hoops_IPAIA.z)*(_hoops_HSPIR.y - _hoops_IPAIA.y);
   n.y = (_hoops_CPAIA.z - _hoops_IPAIA.z)*(_hoops_HSPIR.x - _hoops_IPAIA.x) - (_hoops_CPAIA.x - _hoops_IPAIA.x)*(_hoops_HSPIR.z - _hoops_IPAIA.z);
   n.z = (_hoops_CPAIA.x - _hoops_IPAIA.x)*(_hoops_HSPIR.y - _hoops_IPAIA.y) - (_hoops_CPAIA.y - _hoops_IPAIA.y)*(_hoops_HSPIR.x - _hoops_IPAIA.x);
   HI_Normalize(&n);

   d = - n.x * _hoops_IPAIA.x - n.y * _hoops_IPAIA.y - n.z * _hoops_IPAIA.z;

   /* _hoops_PSIH _hoops_RH _hoops_AHC _hoops_GPP _hoops_RH _hoops_III _hoops_SGS _hoops_HSRAA _hoops_RH _hoops_IPPA */
   _hoops_SSHGA = n.x * (p2.x - p1.x) + n.y * (p2.y - p1.y) + n.z * (p2.z - p1.z);
   if (Abs(_hoops_SSHGA) < 0.00001f)         /* _hoops_RGAIA _hoops_PPR _hoops_IPPA _hoops_GA'_hoops_RA _hoops_ARCRA */
      return false;

   _hoops_GHAIA = - (d + n.x * p1.x + n.y * p1.y + n.z * p1.z) / _hoops_SSHGA;
   p->x = (float)(p1.x + _hoops_GHAIA * (p2.x - p1.x));
   p->y = (float)(p1.y + _hoops_GHAIA * (p2.y - p1.y));
   p->z = (float)(p1.z + _hoops_GHAIA * (p2.z - p1.z));
   if (_hoops_GHAIA < 0 || _hoops_GHAIA > 1)   /* _hoops_HHAIA _hoops_HAR _hoops_IGIAR _hoops_III _hoops_CAGH */
      return false;

   if (_hoops_SPAIA) {
	   /* _hoops_HGH _hoops_IGH _hoops_PAR _hoops_HAR _hoops_RH _hoops_SGSSR _hoops_PPSR _hoops_HRGR _hoops_IHAIA _hoops_HPP _hoops_CHAIA,_hoops_SHAIA,_hoops_GIAIA */
	   _hoops_RHAIA.x = _hoops_IPAIA.x - p->x;
	   _hoops_RHAIA.y = _hoops_IPAIA.y - p->y;
	   _hoops_RHAIA.z = _hoops_IPAIA.z - p->z;
	   HI_Normalize(&_hoops_RHAIA);

	   _hoops_AHAIA.x = _hoops_CPAIA.x - p->x;
	   _hoops_AHAIA.y = _hoops_CPAIA.y - p->y;
	   _hoops_AHAIA.z = _hoops_CPAIA.z - p->z;
	   HI_Normalize(&_hoops_AHAIA);

	   _hoops_PHAIA.x = _hoops_HSPIR.x - p->x;
	   _hoops_PHAIA.y = _hoops_HSPIR.y - p->y;
	   _hoops_PHAIA.z = _hoops_HSPIR.z - p->z;
	   HI_Normalize(&_hoops_PHAIA);


	   a1 = _hoops_RHAIA.x*_hoops_AHAIA.x + _hoops_RHAIA.y*_hoops_AHAIA.y + _hoops_RHAIA.z*_hoops_AHAIA.z;
	   a2 = _hoops_AHAIA.x*_hoops_PHAIA.x + _hoops_AHAIA.y*_hoops_PHAIA.y + _hoops_AHAIA.z*_hoops_PHAIA.z;
	   a3 = _hoops_PHAIA.x*_hoops_RHAIA.x + _hoops_PHAIA.y*_hoops_RHAIA.y + _hoops_PHAIA.z*_hoops_RHAIA.z;

	   total = (acos(a1) + acos(a2) + acos(a3)) * 180.0f / _hoops_APAIA;
	   if (Abs(total - 360) > 1.0f)
		  return false;
   }

   return true;
}



local float _hoops_RIAIA(Point *p1, int _hoops_AIAIA, Point *p2, int _hoops_PIHHA, Point *_hoops_SCAAA, Point *_hoops_GSAAA)
{
	float _hoops_IIHHA = 1.0e6;
	Point _hoops_HIHHA;

	for (int i=0; i<_hoops_AIAIA; i++) {
		int i1,i2;

		if (i < _hoops_AIAIA-1) {
			i1 = i;
			i2 = i+1;
		}
		else {
			i1 = i;
			i2 = 0;
		}

		if (_hoops_HPAIA (p1[i1], p1[i2], p2[0], p2[1], p2[2], &_hoops_HIHHA, false)) {
			if ((_hoops_HIHHA - p1[i1])._hoops_SSRP(_hoops_HIHHA - p1[i2]) <= 0 && _hoops_IHHHA(&_hoops_HIHHA, p2, _hoops_PIHHA)) {
				_hoops_IIHHA = 0;
				*_hoops_SCAAA = p1[i1];
				*_hoops_GSAAA = _hoops_HIHHA;
				return _hoops_IIHHA;
			}
		}

		for (int j=0; j<_hoops_PIHHA; j++) {
			int _hoops_CIHHA,_hoops_SIHHA;

			if (j < _hoops_PIHHA-1) {
				_hoops_CIHHA = j;
				_hoops_SIHHA = j+1;
			}
			else {
				_hoops_CIHHA = j;
				_hoops_SIHHA = 0;
			}

			Point _hoops_PIAIA;
 			float dist = _hoops_AARIA(&p1[i1], &p1[i2], &p2[_hoops_CIHHA], &p2[_hoops_SIHHA], &_hoops_HIHHA, &_hoops_PIAIA);
			if (dist<_hoops_IIHHA) {
				_hoops_IIHHA = dist;
				*_hoops_SCAAA = _hoops_HIHHA;
				*_hoops_GSAAA = _hoops_PIAIA;
			}
		}
	}

	for (int j=0; j<_hoops_PIHHA; j++) {
		int _hoops_CIHHA,_hoops_SIHHA;

		if (j < _hoops_PIHHA-1) {
			_hoops_CIHHA = j;
			_hoops_SIHHA = j+1;
		}
		else {
			_hoops_CIHHA = j;
			_hoops_SIHHA = 0;
		}

		if (_hoops_HPAIA (p2[_hoops_CIHHA], p2[_hoops_SIHHA], p1[0], p1[1], p1[2], &_hoops_HIHHA, false)) {
			if ((_hoops_HIHHA - p2[_hoops_CIHHA])._hoops_SSRP(_hoops_HIHHA - p2[_hoops_SIHHA]) <= 0 && _hoops_IHHHA(&_hoops_HIHHA, p1, _hoops_AIAIA)) {
				_hoops_IIHHA = 0;
				*_hoops_SCAAA = p2[_hoops_CIHHA];
				*_hoops_GSAAA = _hoops_HIHHA;
				return _hoops_IIHHA;
			}
		}
	}


	for (int i=0; i<_hoops_AIAIA; i++) {
		float dist;
		bool _hoops_GCHHA  = HI_Distance_Point_Polygon(&p1[i], p2, _hoops_PIHHA, &_hoops_HIHHA, &dist);
		if (_hoops_GCHHA && dist<_hoops_IIHHA) {
			_hoops_IIHHA = dist;
			*_hoops_SCAAA = _hoops_HIHHA;
			*_hoops_GSAAA = p1[i];
		}
	}

	for (int i=0; i<_hoops_PIHHA; i++) {
		float dist;
		bool _hoops_GCHHA = HI_Distance_Point_Polygon(&p2[i], p1, _hoops_AIAIA, &_hoops_HIHHA, &dist);
		if (_hoops_GCHHA && dist<_hoops_IIHHA) {
			_hoops_IIHHA = dist;
			*_hoops_SCAAA = _hoops_HIHHA;
			*_hoops_GSAAA = p2[i];
		}
	}

	return _hoops_IIHHA;
}



local float _hoops_HIAIA(_hoops_PIGIA *node, const Point *_hoops_SCGIA, Point *_hoops_SCAAA, Point *_hoops_GSAAA)
{
 	_hoops_RAGIA *_hoops_IIAIA = (_hoops_RAGIA *)node->_hoops_IIAIA;

	Point p1[128];
	Point p2[128];

	ASSERT(node->f1->len < 128);
	ASSERT(node->f2->len < 128);

	for (int i=0; i<node->f1->len; i++)
		p1[i] = _hoops_SCGIA[node->f1->_hoops_GIPPA[i]];

	for (int i=0; i<node->f2->len; i++)
		p2[i] = _hoops_IIAIA->_hoops_PAGIA[node->f2->_hoops_GIPPA[i]];

	return (_hoops_RIAIA(p1, node->f1->len, p2, node->f2->len, _hoops_SCAAA, _hoops_GSAAA));
}




local float _hoops_CIAIA(
	Point *		p1,
	int			_hoops_AIAIA,
	Point *		p2,
	int			_hoops_PIHHA,
	Vector		_hoops_CCSAR,
	Point *		_hoops_SCAAA,
	Point *		_hoops_GSAAA)
{
	Point p[4];

	float _hoops_IIHHA = 1.0e6;

	_hoops_CCSAR *= 1000.0f;

	_hoops_ARPA pl;
	HI_Figure_Plane_From_Points(_hoops_AIAIA, p1, &pl);

	for (int i=0; i<_hoops_AIAIA; i++) {
		int i1,i2;
		if (i<_hoops_AIAIA-1) {
			i1 = i;
			i2 = i+1;
		}
		else {
			i1 = i;
			i2 = 0;
		}

		p[0] = p1[i1];
		p[1] = p1[i2];

		p[2] = p[1] + _hoops_CCSAR;
		p[3] = p[0] + _hoops_CCSAR;

		for (int j=0; j<_hoops_PIHHA; j++) {
			int _hoops_CIHHA,_hoops_SIHHA;

			if (j<_hoops_PIHHA-1) {
				_hoops_CIHHA = j;
				_hoops_SIHHA = j+1;
			}
			else {
				_hoops_CIHHA = j;
				_hoops_SIHHA = 0;
			}

			Point _hoops_SIAIA;

			if (_hoops_HPAIA(p2[_hoops_CIHHA], p2[_hoops_SIHHA], p[0], p[1], p[2],&_hoops_SIAIA)) {
				if (_hoops_IHHHA(&_hoops_SIAIA, p, 4)) {
					Point _hoops_GCAIA = _hoops_SIAIA - _hoops_CCSAR;
					Point _hoops_RCAIA;

					if (_hoops_HPAIA(_hoops_SIAIA, _hoops_GCAIA, p1[0],p1[1], p1[2], &_hoops_RCAIA)) {
		  				float dist = _hoops_SRCIR(_hoops_SIAIA, _hoops_RCAIA);

						if (dist<_hoops_IIHHA) {
							*_hoops_SCAAA = _hoops_RCAIA;
							*_hoops_GSAAA = _hoops_SIAIA;
							_hoops_IIHHA = dist;
						}
					}
				}
			}
		}
	}


	HI_Figure_Plane_From_Points(_hoops_PIHHA, p2, &pl);

	for (int i=0; i<_hoops_PIHHA; i++) {
		int i1,i2;

		if (i<_hoops_PIHHA-1) {
			i1 = i;
			i2 = i+1;
		}
		else {
			i1 = i;
			i2 = 0;
		}

		p[0] = p2[i1];
		p[1] = p2[i2];

		p[2] = p[1] - _hoops_CCSAR;
		p[3] = p[0] - _hoops_CCSAR;

		for (int j=0; j<_hoops_AIAIA; j++) {
			int _hoops_CIHHA,_hoops_SIHHA;

			if (j<_hoops_AIAIA-1) {
				_hoops_CIHHA = j;
				_hoops_SIHHA = j+1;
			}
			else {
				_hoops_CIHHA = j;
				_hoops_SIHHA = 0;
			}

			Point _hoops_SIAIA;
			if (_hoops_HPAIA(p1[_hoops_CIHHA], p1[_hoops_SIHHA], p[0], p[1], p[2],&_hoops_SIAIA)) {
				if (_hoops_IHHHA(&_hoops_SIAIA, p, 4)) {
					Point _hoops_GCAIA = _hoops_SIAIA + _hoops_CCSAR;
					Point _hoops_RCAIA;

					if (_hoops_HPAIA(_hoops_SIAIA, _hoops_GCAIA, p2[0],p2[1], p2[2], &_hoops_RCAIA)) {
						float dist = _hoops_SRCIR(_hoops_SIAIA, _hoops_RCAIA);

						if (dist<_hoops_IIHHA) {
							*_hoops_SCAAA = _hoops_RCAIA;
							*_hoops_GSAAA = _hoops_SIAIA;
							_hoops_IIHHA = dist;
						}
					}
				}
			}
		}
	}


	HI_Figure_Plane_From_Points(_hoops_PIHHA, p2, &pl);

	for (int i=0; i<_hoops_AIAIA; i++) {
 		Point _hoops_GCAIA = p1[i] + _hoops_CCSAR;
		Point _hoops_HGII;

		if (_hoops_HPAIA(p1[i], _hoops_GCAIA, p2[0], p2[1], p2[2],&_hoops_HGII)) {
 			if (_hoops_IHHHA(&_hoops_HGII, p2, _hoops_PIHHA)) {
				float dist = _hoops_SRCIR(p1[i], _hoops_HGII);

				if (dist<_hoops_IIHHA) {
					_hoops_IIHHA = dist;
					*_hoops_SCAAA = _hoops_HGII;
					*_hoops_GSAAA = p1[i];
				}
			}
		}
	}

	HI_Figure_Plane_From_Points(_hoops_AIAIA, p1, &pl);

	for (int i=0; i<_hoops_PIHHA; i++) {
 		Point _hoops_GCAIA = p2[i] - _hoops_CCSAR;
		Point _hoops_HGII;

		if (_hoops_HPAIA(p2[i], _hoops_GCAIA, p1[0], p1[1], p1[2],&_hoops_HGII)) {
			if (_hoops_IHHHA(&_hoops_HGII, p1, _hoops_AIAIA)) {
				float dist = _hoops_SRCIR(p2[i], _hoops_HGII);

				if (dist<_hoops_IIHHA) {
					_hoops_IIHHA = dist;
					*_hoops_SCAAA = _hoops_HGII;
					*_hoops_GSAAA = p2[i];
				}
			}
		}
	}

	return _hoops_IIHHA;
}


local float _hoops_ACAIA(
	_hoops_PIGIA *	node,
	Point const*		_hoops_SCGIA,
	Vector				_hoops_CCSAR,
	Point *				_hoops_SCAAA,
	Point *				_hoops_GSAAA)
{
	Point p1[128];
	Point p2[128];
  	_hoops_RAGIA *_hoops_IIAIA = (_hoops_RAGIA *)node->_hoops_IIAIA;

	ASSERT(node->f1->len < 128);
	ASSERT(node->f2->len < 128);

	for (int i=0; i<node->f1->len; i++)
		p1[i] = _hoops_SCGIA[node->f1->_hoops_GIPPA[i]];

	for (int i=0; i<node->f2->len; i++)
		p2[i] = _hoops_IIAIA->_hoops_PAGIA[node->f2->_hoops_GIPPA[i]];

	return (_hoops_CIAIA(p1, node->f1->len, p2, node->f2->len, _hoops_CCSAR, _hoops_SCAAA, _hoops_GSAAA));
}




local _hoops_CSCAR _hoops_PCAIA(void *_hoops_HASAR, void *_hoops_AIPPA, void *_hoops_PIPPA)
{
	global_compare_info *	info = (global_compare_info *)_hoops_HASAR;
	_hoops_CGGIA *			ei = (_hoops_CGGIA *)_hoops_AIPPA;
	_hoops_SASC const &	bbox = *((_hoops_SASC const *)_hoops_PIPPA);

	info->_hoops_GARIA._hoops_IRRIA++;
	if (bbox._hoops_RPCIR(ei->bbox)) {
		if (info->_hoops_ISGIA->Count() != info->_hoops_CSGIA) {
			info->_hoops_ISGIA->Append(ei);
			return VBSP_STATUS_CONTINUE;
		}
		return VBSP_STATUS_STOP;
	}
	else
		return VBSP_STATUS_CONTINUE; /* _hoops_GRHP _hoops_HCHAR */
}


local _hoops_CSCAR _hoops_HCAIA(void *_hoops_HASAR, void *_hoops_AIPPA, void *_hoops_PIPPA)
{
	global_compare_info *info = (global_compare_info *)_hoops_HASAR;
	_hoops_CGGIA *ei = (_hoops_CGGIA *)_hoops_AIPPA;
	_hoops_SASC const * bbox = (_hoops_SASC const *)_hoops_PIPPA;

	float _hoops_GIGCR = HI_Cuboid_To_Cuboid_Distance(*bbox, ei->bbox);
	float _hoops_RIGCR = HI_Cuboid_To_Cuboid_Max_Distance(*bbox, ei->bbox);

	info->_hoops_GARIA._hoops_IRRIA++;

	if (!info->_hoops_SSGIA->PeekFirst()) {
		info->_hoops_HGRIA = _hoops_GIGCR;
		info->_hoops_IGRIA = _hoops_RIGCR;
		ei->_hoops_GRGIA = _hoops_GIGCR;
		ei->_hoops_RRGIA = _hoops_RIGCR;
		info->_hoops_SSGIA->AddLast(ei);
	}
	else {
 		if (_hoops_GIGCR <= info->_hoops_IGRIA) {
			if (_hoops_GIGCR < info->_hoops_HGRIA)
				info->_hoops_HGRIA = _hoops_GIGCR;
			if (_hoops_RIGCR < info->_hoops_IGRIA)
				info->_hoops_IGRIA = _hoops_RIGCR;

			ei->_hoops_GRGIA = _hoops_GIGCR;
			ei->_hoops_RRGIA = _hoops_RIGCR;
			info->_hoops_SSGIA->ResetCursor();

			while (1) {
				_hoops_CGGIA *temp = info->_hoops_SSGIA->PeekCursor();

 				if (temp && temp->_hoops_GRGIA > _hoops_RIGCR) {
					info->_hoops_SSGIA->RemoveAtCursor();
				}
				else {
					if (!temp || temp->_hoops_GRGIA >= _hoops_GIGCR) {
						info->_hoops_SSGIA->AddBeforeCursor(ei);
						break;
					}
					if (!temp)
						break;
 					info->_hoops_SSGIA->AdvanceCursor();
				}
			}
		}
	}
	return VBSP_STATUS_CONTINUE;
}


local _hoops_CSCAR _hoops_ICAIA(void *_hoops_HASAR, void *_hoops_AIPPA, void *_hoops_PIPPA)
{
	global_compare_info *	info = (global_compare_info *)_hoops_HASAR;
	_hoops_CGGIA *			ei = (_hoops_CGGIA *)_hoops_AIPPA;
	_hoops_SASC const &	bbox = *((_hoops_SASC const *)_hoops_PIPPA);
	Vector 					_hoops_CCSAR = info->_hoops_ASGIA->_hoops_CCSAR;

	Point _hoops_CCAIA = _hoops_AICIR(bbox.max, bbox.min);
	Point _hoops_SCAIA = _hoops_AICIR(ei->bbox.max, ei->bbox.min);

	float _hoops_GSAIA = ei->bbox._hoops_RSAIA().length();
	float _hoops_ASAIA = bbox._hoops_RSAIA().length();

 	_hoops_CCSAR *= 1000.0f;

	Point	_hoops_PSAIA = _hoops_CCAIA + _hoops_CCSAR;

	Point	_hoops_HGII;
	float	dist;

	if (HI_Compute_Point_To_Line_Distance(&_hoops_SCAIA, &_hoops_CCAIA, &_hoops_PSAIA, &dist, &_hoops_HGII)) {
		if (dist < (_hoops_GSAIA/2.0f + _hoops_ASAIA/2.0f)) {
			float _hoops_RIGCR = _hoops_SRCIR(_hoops_CCAIA, _hoops_HGII) + _hoops_ASAIA/2.0f  + _hoops_GSAIA/2.0f;
			float _hoops_GIGCR = _hoops_SRCIR(_hoops_CCAIA, _hoops_HGII);

			info->_hoops_GARIA._hoops_IRRIA++;
			if (!info->_hoops_SSGIA->PeekFirst()) {
				info->_hoops_HGRIA = _hoops_GIGCR;
				info->_hoops_IGRIA = _hoops_RIGCR;
				ei->_hoops_GRGIA = _hoops_GIGCR;
				ei->_hoops_RRGIA = _hoops_RIGCR;
				info->_hoops_SSGIA->AddLast(ei);
			}
			else {
 				if (_hoops_GIGCR <= info->_hoops_IGRIA) {
					if (_hoops_GIGCR < info->_hoops_HGRIA)
						info->_hoops_HGRIA = _hoops_GIGCR;
					if (_hoops_RIGCR < info->_hoops_IGRIA)
						info->_hoops_IGRIA = _hoops_RIGCR;

					ei->_hoops_GRGIA = _hoops_GIGCR;
					ei->_hoops_RRGIA = _hoops_RIGCR;
					info->_hoops_SSGIA->ResetCursor();

					while (1) {
						_hoops_CGGIA *temp = info->_hoops_SSGIA->PeekCursor();
 						if (temp && temp->_hoops_GRGIA > _hoops_RIGCR) {
							info->_hoops_SSGIA->RemoveAtCursor();
						}
						else {
							if (!temp || temp->_hoops_GRGIA >= _hoops_GIGCR) {
 								info->_hoops_SSGIA->AddBeforeCursor(ei);
								break;
							}
							if (!temp)
								break;
 							info->_hoops_SSGIA->AdvanceCursor();
						}
					}
				}
			}
		}
	}

	return VBSP_STATUS_CONTINUE;
}



local _hoops_CSCAR _hoops_HSAIA(void *_hoops_HASAR, void *_hoops_AIPPA, void *_hoops_PIPPA)
{
	global_compare_info *	info = (global_compare_info *)_hoops_HASAR;
	_hoops_CGGIA *			ei = (_hoops_CGGIA *)_hoops_AIPPA;
	_hoops_HSSHA *					_hoops_PAHHA = (_hoops_HSSHA *)_hoops_PIPPA;

	if (ei->bbox._hoops_RPCIR(*_hoops_PAHHA->start, *_hoops_PAHHA->direction)) {
		if (info->_hoops_ISGIA->Count() != info->_hoops_CSGIA) {
			info->_hoops_ISGIA->Append(ei);
			return VBSP_STATUS_CONTINUE;
		}
		else
			return VBSP_STATUS_STOP;
	}
	else
		return VBSP_STATUS_CONTINUE; /* _hoops_GRHP _hoops_HCHAR */
}


/* _hoops_HRS _hoops_RCPP _hoops_RPP _hoops_RH _hoops_RAGA _hoops_CPAP'_hoops_GRI _hoops_IASC _hoops_AHCRR _hoops_PAH'_hoops_RA _hoops_SHH _hoops_ISAIA _hoops_CRGR _hoops_IRS _hoops_IPIS */
local bool _hoops_CSAIA(
	_hoops_AIGPR *	_hoops_RIGC,
	Key						key,
	_hoops_SASC alter &	cuboid)
{

	_hoops_HPAH * thing = _hoops_RCSSR (_hoops_RIGC, key);

	if (thing->type == _hoops_IRCP) {
		_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *)thing;
		cuboid = _hoops_SRCP->bounding->cuboid;
		return true;
	}
	else {
		Geometry const *	geo = (Geometry const *)thing;
		Bounding			_hoops_RCHS;

		if (geo->type == _hoops_GSIP || geo->type == _hoops_SCIP) {
			Polyhedron const *	_hoops_HARIR = (Polyhedron const *)geo;
			_hoops_RCHS = _hoops_HARIR->bounding;
		}
		else if (geo->type == _hoops_CSIP) {
			PolyCylinder const *	_hoops_HARIR = (PolyCylinder const *)geo;
			_hoops_RCHS = _hoops_HARIR->bounding;
		}
		else if (geo->type == _hoops_AHIP) {
			_hoops_PHIP const *	_hoops_RRA = (_hoops_PHIP const *)geo;
			_hoops_RCHS = _hoops_RRA->bounding;
			if (_hoops_RCHS._hoops_HICAR())
				HI_Figure_Geometry_Bounding (geo, _hoops_RCHS);
		}
		else
			HI_Figure_Geometry_Bounding (geo, _hoops_RCHS);

		if (_hoops_RCHS._hoops_HICAR() ||
			ANYBIT(_hoops_RCHS->flags, _hoops_HGCIR|_hoops_IGCIR|Bounding_TRANSFORM_DEPENDENT))
			return false;

		cuboid = _hoops_RCHS->cuboid;
	}

	return true;
}


local _hoops_RAGIA *_hoops_SSAIA(void)
{
	_hoops_RAGIA *info;

	ZALLOC(info, _hoops_RAGIA);
	/* _hoops_HII _hoops_RH _hoops_RGSPR */
	info->type = _hoops_GGPIA;
	/* _hoops_HII _hoops_RH _hoops_PPCAR _hoops_RGPIA */
	info->key = -1;
	return info;
}


local _hoops_HPGIA *_hoops_AGPIA(void)
{
	_hoops_HPGIA *info;

	ZALLOC(info, _hoops_HPGIA);
	/* _hoops_HII _hoops_RH _hoops_RGSPR */
	info->type = _hoops_PGPIA;
	/* _hoops_HII _hoops_RH _hoops_PPCAR _hoops_RGPIA */
	info->key = -1;
	return info;
}


local _hoops_GHGIA *_hoops_HGPIA(void)
{
	_hoops_GHGIA *info;

	ZALLOC(info, _hoops_GHGIA);
	/* _hoops_HII _hoops_RH _hoops_RGSPR */
	info->type = _hoops_IGPIA;
	/* _hoops_HII _hoops_RH _hoops_PPCAR _hoops_RGPIA */
	info->key = -1;
	return info;
}


local _hoops_RHGIA *_hoops_CGPIA(void)
{
	_hoops_RHGIA *info;

	ZALLOC(info, _hoops_RHGIA);
	/* _hoops_HII _hoops_RH _hoops_RGSPR */
	info->type = _hoops_SGPIA;
	/* _hoops_HII _hoops_RH _hoops_PPCAR _hoops_RGPIA */
	info->key = -1;
	return info;
}


local _hoops_AHGIA *_hoops_GRPIA(void)
{
	_hoops_AHGIA *info;

	ZALLOC(info, _hoops_AHGIA);
	/* _hoops_HII _hoops_RH _hoops_RGSPR */
	info->type = _hoops_RRPIA;
	/* _hoops_HII _hoops_RH _hoops_PPCAR _hoops_RGPIA */
	info->key = -1;
	return info;
}


local _hoops_PHGIA *_hoops_ARPIA(void)
{
	_hoops_PHGIA *info;

	ZALLOC(info, _hoops_PHGIA);
	/* _hoops_HII _hoops_RH _hoops_RGSPR */
	info->type = _hoops_PRPIA;
	/* _hoops_HII _hoops_RH _hoops_PPCAR _hoops_RGPIA */
	info->key = -1;
	/* _hoops_RH _hoops_ACSP */
	ZALLOC(info->_hoops_IHGIA, Grid);
	return info;
}


local void _hoops_HRPIA(_hoops_RAGIA *info)
{
	if (info->_hoops_PAGIA != null) {
		if (info->flags & _hoops_IGGIA)
			FREE_ARRAY(info->_hoops_PAGIA, info->phon->point_count, Point);
	}
	if (info->_hoops_HAGIA != null) {
		if (info->flags & _hoops_HGGIA)
			FREE_ARRAY(info->_hoops_HAGIA, info->phon->face_count, _hoops_ARPA);
	}

	if (info->BSP != null) {
		/* _hoops_HSCI _hoops_RH _hoops_HSP _hoops_AIIS */
		HI_BSP_Map_Function(info->BSP, _hoops_AAHPA, null);
		HI_Delete_BSP(info->BSP);
	}


	if (info->matrix != null) {
		if (info->matrix->_hoops_APRA != null)
			info->matrix->_hoops_APRA.release();
		FREE(info->matrix, _hoops_HRPA);
	}


	FREE(info, _hoops_RAGIA);
}


local void _hoops_IRPIA(_hoops_HPGIA *info)
{
	if (info->BSP != null) {
		HI_Delete_BSP(info->BSP);
	}
	if (info->_hoops_CPGIA != null)
		delete info->_hoops_CPGIA;

	FREE(info, _hoops_HPGIA);
}


local void _hoops_CRPIA(_hoops_GHGIA *info)
{
	if (info->BSP != null) {
		/* _hoops_HSCI _hoops_RH _hoops_SRPIA _hoops_HII _hoops_RH _hoops_IPHRA */
		HI_BSP_Map_Function(info->BSP, _hoops_AAHPA, null);
		HI_Delete_BSP(info->BSP);
	}
	FREE(info, _hoops_GHGIA);
}


local void _hoops_GAPIA(_hoops_RHGIA *info)
{
	FREE(info, _hoops_RHGIA);
}


local void _hoops_RAPIA(_hoops_AHGIA *info)
{
	FREE(info, _hoops_AHGIA);
}


local void _hoops_AAPIA(_hoops_PHGIA *info)
{
	FREE(info->_hoops_IHGIA, Grid);
	FREE(info, _hoops_PHGIA);
}


/* _hoops_PAPIA _hoops_SPASR _hoops_HAPIA _hoops_IH _hoops_CAPGR _hoops_GGR _hoops_SSSAR */
local _hoops_CSCAR _hoops_IAPIA(void *_hoops_AIPPA, void *user_data)
{
	_hoops_CGGIA *info = (_hoops_CGGIA *)_hoops_AIPPA;

	/* _hoops_HSCI _hoops_RH _hoops_CIPH _hoops_GGSR _hoops_IIGR _hoops_RH _hoops_PPCAR _hoops_CAPIA */
	if (info->matrix != null) {
		info->matrix->_hoops_APRA.release();
		FREE (info->matrix, _hoops_HRPA);
		info->matrix = null;
	}
	if (info->path != null) {
		delete info->path;
		info->path = null;
	}

	/* _hoops_HA _hoops_HSCI _hoops_RH _hoops_ACSP.	 _hoops_HHIGR _hoops_HRGR _hoops_SAPIA _hoops_SGS _hoops_RGR _hoops_ARIP _hoops_RCPS _hoops_CGHI
	 * _hoops_CR _hoops_SCH _hoops_GACC _hoops_GPPIA _hoops_RH _hoops_SHSC _hoops_RGGAR _hoops_PPARR */
	switch (info->type) {
		case _hoops_GGPIA:
			_hoops_HRPIA((_hoops_RAGIA *)info);
			break;
		case _hoops_PGPIA:
			_hoops_IRPIA((_hoops_HPGIA *)info);
			break;
		case _hoops_IGPIA:
			_hoops_CRPIA((_hoops_GHGIA *)info);
			break;
		case _hoops_SGPIA:
			_hoops_GAPIA((_hoops_RHGIA *)info);
			break;
		case _hoops_RRPIA:
			_hoops_RAPIA((_hoops_AHGIA *)info);
			break;
		case _hoops_PRPIA:
			_hoops_AAPIA((_hoops_PHGIA *)info);
			break;
		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					"Attempt to delete unrecognized type in compute selection by shell");
			break;
	}
	UNREFERENCED(user_data);
	return VBSP_STATUS_CONTINUE; /* _hoops_GRHP _hoops_SIA */
}


local int _hoops_RPPIA(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_IRGIA const *		path)
{
	char result[32];
	int _hoops_APPIA = 0;
	Key const * path_keys = &(*path)[0];

	PUSHNAME(_hoops_RIGC);
	HC_PShow_One_Net_Selectability(path->Count(), path_keys, "faces", result);
	if (strstr(result, "v"))
		_hoops_APPIA = 1;
	/* _hoops_RPP _hoops_RH _hoops_ACPH _hoops_PPPIA _hoops_HPPIA, _hoops_HIH _hoops_PSP '!', _hoops_SR _hoops_PHHR _hoops_HPP _hoops_HPRC */
	if (_hoops_APPIA && !strchr(result, '!')) {
		HC_PShow_One_Net_Visibility(path->Count(), path_keys, "faces", result);
		if (_hoops_AGGR(result, "off"))
			_hoops_APPIA = 0;
	}
	POPNAME(_hoops_RIGC);
	return _hoops_APPIA;
}


local void _hoops_IPPIA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_PHGIA *		env_info,
	Grid *					g);

local void _hoops_CPPIA(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP const *			_hoops_SRCP,
	_hoops_IRGIA *				path,
	_hoops_HRPA const &		modelling_matrix,
	global_compare_info *	_hoops_SPPIA)
{
	bool	  		_hoops_GHPIA = false;
	bool	  		_hoops_RHPIA = false;
	bool	  		_hoops_AHPIA = false;

	Geometry *		g = _hoops_SRCP->geometry;
	_hoops_CGGIA *	_hoops_IIAIA;

	while (g != null) {
		Bounding	  bounding;
		_hoops_IIAIA = null;
		_hoops_RHPIA = false;
		_hoops_AHPIA = false;
		switch (g->type) {
			case _hoops_PRCP:
			case _hoops_SCIP:
			case _hoops_GSIP:
				path->Reverse();
				if (_hoops_RPPIA(_hoops_SPPIA->_hoops_RIGC, path))
					_hoops_IIAIA = (_hoops_CGGIA *) _hoops_SSAIA();
				path->Reverse();
				_hoops_SPPIA->_hoops_ARRIA = BIT (((Polyhedron *)g)->polyhedron_flags,
								 PHF_IMPLICIT_NORMALS_REVERSED);
				break;
			case _hoops_CSIP:
				_hoops_IIAIA = (_hoops_CGGIA *) _hoops_HGPIA();
				break;
			case _hoops_HSIP:
				_hoops_IIAIA = (_hoops_CGGIA *) _hoops_CGPIA();
				break;
			case _hoops_ASIP:
				_hoops_IIAIA = (_hoops_CGGIA *) _hoops_GRPIA();
				break;
			case _hoops_GGCP: {
				Grid *grid = (Grid *)g;
				if (!grid->count1 || !grid->count2)
					_hoops_AHPIA = true;
				_hoops_IIAIA = (_hoops_CGGIA *) _hoops_ARPIA();
			} break;
			case _hoops_RCIP:
			case _hoops_SGCP:
			case _hoops_CGCP:
			case _hoops_GRCP:
			case _hoops_RRCP: {
				if (_hoops_GHPIA)
					break;
				Bounding _hoops_HSRIR;
				HI_Figure_Segment_Bounding(g->owner, bounding, _hoops_HSRIR);
				_hoops_RHPIA = true;
				_hoops_IIAIA = (_hoops_CGGIA *) _hoops_AGPIA();
			}	break;

			default:
				break;
		}
		if (_hoops_IIAIA != null) {
			_hoops_IIAIA->key = _hoops_AIRIR(g);
			_hoops_IIAIA->path = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_IRGIA)(_hoops_RIGC->memory_pool, path);
			_hoops_IIAIA->path->Reverse();
			if (_hoops_AHPIA) {
				if (_hoops_SPPIA->_hoops_PGRIA == null)
					_hoops_SPPIA->_hoops_PGRIA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_GCGIA)(_hoops_RIGC->memory_pool);
				if (!modelling_matrix._hoops_PPGH()) {
					ZALLOC(_hoops_IIAIA->matrix, _hoops_HRPA);
					*_hoops_IIAIA->matrix = modelling_matrix;
				}
				_hoops_IPPIA(_hoops_SPPIA->_hoops_RIGC, (_hoops_PHGIA *)_hoops_IIAIA, (Grid *)g);
				_hoops_SPPIA->_hoops_PGRIA->Append(_hoops_IIAIA);
			}
			else {
				if (!_hoops_RHPIA)
					HI_Figure_Geometry_Bounding (g, bounding);

				if (!bounding._hoops_HICAR()) {
					if (!modelling_matrix._hoops_PPGH()) {
						ZALLOC(_hoops_IIAIA->matrix, _hoops_HRPA);
						*_hoops_IIAIA->matrix = modelling_matrix;
						_hoops_IIAIA->bbox = bounding->cuboid._hoops_SCIS (modelling_matrix);
					}
					else
						_hoops_IIAIA->bbox = bounding->cuboid;

					HI_BSP_Insert(_hoops_SPPIA->tree, _hoops_IIAIA, null);
				}
			}
		}
		g = g->next;
	}
}


local void _hoops_PHPIA(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP const *			_hoops_SRCP,
	_hoops_IRGIA *				path,
	_hoops_HRPA const &		_hoops_HHPIA,
	global_compare_info *	_hoops_SPPIA)
{
	_hoops_HRPA *			modelling_matrix = (_hoops_HRPA *)&_hoops_HHPIA;

	Attribute *				_hoops_ASGPR = null;
	/* _hoops_ISPR _hoops_IH _hoops_HCIA */
	if ((_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR) != null) do {
		if (_hoops_ASGPR->type > HK_MODELLING_MATRIX)
			break;
		if (_hoops_ASGPR->type == HK_MODELLING_MATRIX) {
			_hoops_ISGI const *	_hoops_IHPIA = (_hoops_ISGI const *)_hoops_ASGPR;
			ZALLOC(modelling_matrix, _hoops_HRPA);
			//*_hoops_CHPIA = _hoops_SHPIA;
			HI_Compute_Matrix_Product(
				&_hoops_IHPIA->matrix.elements[0][0],
				&_hoops_HHPIA.elements[0][0],
				&modelling_matrix->elements[0][0]);
			modelling_matrix->_hoops_RAGR = _hoops_HHPIA._hoops_RAGR | _hoops_IHPIA->matrix._hoops_RAGR;
			break;
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);


	Subsegment const *	_hoops_GIPIA;
	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		_hoops_CRCP const *		_hoops_RIPIA;

		if (_hoops_GIPIA->type == _hoops_AGRPR) {
			path->Append(_hoops_GIPIA->key);
			_hoops_RIPIA = ((_hoops_PGRPR const *)_hoops_GIPIA)->_hoops_IGRPR;
		}
		else
			_hoops_RIPIA = (_hoops_CRCP const *)_hoops_GIPIA;

		path->Append(_hoops_RIPIA->key);

		_hoops_PHPIA(_hoops_RIGC, _hoops_RIPIA, path, *modelling_matrix, _hoops_SPPIA);

		path->Pop();

		if (_hoops_GIPIA->type == _hoops_AGRPR)
			path->Pop();
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);


	if (_hoops_SRCP->geometry)
		_hoops_CPPIA(_hoops_RIGC, _hoops_SRCP, path, *modelling_matrix, _hoops_SPPIA);

	if (modelling_matrix != &_hoops_HHPIA) {
		modelling_matrix->_hoops_APRA.release();
		FREE(modelling_matrix, _hoops_HRPA);
	}
}

/* _hoops_GIRIA _hoops_IRS _hoops_IPHRA _hoops_CCA _hoops_RH _hoops_CPAP _hoops_HII _hoops_IRS _hoops_CAGH _hoops_HHIS */
local void _hoops_AIPIA(
	_hoops_AIGPR *	_hoops_RIGC,
	Key						_hoops_CCGIA,
	global_compare_info *	_hoops_SPPIA) {
	_hoops_CRCP *			_hoops_SRCP = (_hoops_CRCP *)_hoops_RCSSR (_hoops_SPPIA->_hoops_RIGC, _hoops_CCGIA);
	ASSERT(_hoops_SRCP->type == _hoops_IRCP);

	_hoops_HRPA modelling_matrix;
	ZERO_STRUCT(&modelling_matrix, _hoops_HRPA);

	HI_Compute_Identity_Matrix(&modelling_matrix.elements[0][0]);

	_hoops_IRGIA *	path = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_IRGIA)(_hoops_RIGC->memory_pool);
	path->Append(_hoops_CCGIA);
	_hoops_PHPIA(_hoops_RIGC, _hoops_SRCP, path, modelling_matrix, _hoops_SPPIA);
	path->Pop();

	ASSERT(path->Count() == 0);

	delete path;
}


#if 0
/* _hoops_ISPR _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_HCR _hoops_IIGR _hoops_RH _hoops_RSSA _hoops_PRCS _hoops_GIAA _hoops_RH _hoops_RAGA _hoops_IPPA */
local int _hoops_PIPIA(_hoops_SHPPA *node, float *points)
{
	float value;
	const int *face = node->_hoops_GIPPA;
	const float *plane = node->plane;
	const float *pt;
	int i;
	int _hoops_HIPIA = 1;

	for (i = 0; i < node->len; i++) {
		pt = points + 3*face[i];
		value = ((pt[0]*plane[0])+(pt[1]*plane[1])+(pt[2]*plane[2])+plane[3]);
		if (value > _hoops_CACIR || value < -_hoops_CACIR)
			_hoops_HIPIA = 0;
	}
	return _hoops_HIPIA;
}
#endif


INLINE void _hoops_IIPIA(
	_hoops_RAGIA *_hoops_IIAIA)
{
	int point_count = _hoops_IIAIA->phon->point_count;
	ALLOC_ARRAY(_hoops_IIAIA->_hoops_PAGIA, point_count, Point);
	HI_Compute_Transformed_Points(point_count, _hoops_IIAIA->phon->points, &_hoops_IIAIA->matrix->elements[0][0], _hoops_IIAIA->_hoops_PAGIA);
	_hoops_IIAIA->flags |= _hoops_IGGIA;
}


/* _hoops_SASI _hoops_IS _hoops_HHCPR _hoops_GPRR _hoops_PGGIA.
 * _hoops_SAHHA _hoops_IISA _hoops_HII _hoops_GPHHA _hoops_RSCRR _hoops_HIGR.
 *	 _hoops_CRSAR _hoops_IISA _hoops_HII 1_hoops_ICPC _hoops_IPHRA (_hoops_ARIP).
 *	 _hoops_SRSAR _hoops_IISA _hoops_HII 2_hoops_GRSP _hoops_IPHRA (_hoops_RHI). */
local _hoops_CSCAR _hoops_CIPIA(void *_hoops_HCSAR, void *_hoops_IASAR, void *_hoops_CASAR)
{
	global_compare_info *	info = (global_compare_info *)_hoops_HCSAR;
	_hoops_SHPPA *			_hoops_SIPIA = (_hoops_SHPPA *)_hoops_IASAR;
	_hoops_SHPPA *			_hoops_GCPIA = (_hoops_SHPPA *)_hoops_CASAR;

	if (!_hoops_SIPIA->bbox._hoops_RPCIR(_hoops_GCPIA->bbox))
		return VBSP_STATUS_CONTINUE; /* _hoops_GRHP _hoops_HHCPR */

	info->_hoops_GARIA._hoops_CRRIA++;

	float _hoops_RCPIA = 0;

	if (!info->_hoops_GRRIA) {
		if (!_hoops_HIPPA(
				info->_hoops_SCGIA,
				_hoops_SIPIA->len,
				_hoops_SIPIA->_hoops_GIPPA,
				_hoops_GCPIA->plane))
				return VBSP_STATUS_CONTINUE; /* _hoops_GRHP _hoops_HHCPR */
	}
	else {
 		_hoops_RCPIA = info->_hoops_RRRIA;
 		if (!_hoops_HIPPA(
				info->_hoops_SCGIA,
				_hoops_SIPIA->len,
				_hoops_SIPIA->_hoops_GIPPA,
				_hoops_GCPIA->plane))
				return VBSP_STATUS_CONTINUE;  /* _hoops_GRHP _hoops_HHCPR */
	}

	info->_hoops_GARIA._hoops_SRRIA++;

	_hoops_RAGIA *	_hoops_IIAIA = (_hoops_RAGIA *) info->_hoops_HSGIA;
	if (_hoops_IIAIA->type != _hoops_GGPIA) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				"incorrect callback used in compute selection by shell");
		return VBSP_STATUS_STOP;
	}
	if (_hoops_IIAIA->_hoops_PAGIA == null)
		_hoops_IIPIA(_hoops_IIAIA);

	if (!_hoops_HIPPA(
			_hoops_IIAIA->_hoops_PAGIA,
			_hoops_GCPIA->len,
			_hoops_GCPIA->_hoops_GIPPA,
			_hoops_SIPIA->plane))
			return VBSP_STATUS_CONTINUE; /* _hoops_GRHP _hoops_HHCPR */

 	if (!info->_hoops_GRRIA) {
  		if (!_hoops_ACPIA(
								info->_hoops_SCGIA,
								_hoops_SIPIA->len,
								_hoops_SIPIA->_hoops_GIPPA,
								&_hoops_SIPIA->plane,
								_hoops_IIAIA->_hoops_PAGIA,
								_hoops_GCPIA->len,
								_hoops_GCPIA->_hoops_GIPPA,
								&_hoops_GCPIA->plane,
								&_hoops_IIAIA->_hoops_CAGIA,
								info->_hoops_HRRIA,
								info->_hoops_RRRIA ? true : false,
								info->_hoops_PRRIA))
			return VBSP_STATUS_CONTINUE; /* _hoops_GRHP _hoops_HHCPR */
	}
	else {
		if (!_hoops_PCPIA(
								info->_hoops_SCGIA,
								info->_hoops_GSGIA,
								&_hoops_SIPIA->plane,
								_hoops_SIPIA->len,
								_hoops_SIPIA->_hoops_GIPPA,
								_hoops_IIAIA->_hoops_PAGIA,
								_hoops_GCPIA->len,
								_hoops_GCPIA->_hoops_GIPPA,
								&_hoops_GCPIA->plane,
								&_hoops_IIAIA->_hoops_CAGIA,
								_hoops_RCPIA))
			return VBSP_STATUS_CONTINUE; /* _hoops_GRHP _hoops_HHCPR */
	}


	/* _hoops_CIGAA, _hoops_PPR _hoops_GRHP _hoops_HHCPR _hoops_RPP _hoops_SR _hoops_SIPGR'_hoops_RA _hoops_GAPR _hoops_RHHR _hoops_RH _hoops_SAIPR */
	_hoops_IIAIA->_hoops_IAGIA = _hoops_GCPIA;

	if (info->_hoops_ISGIA->Count() != info->_hoops_CSGIA) {
 		info->_hoops_ISGIA->Append(info->_hoops_HSGIA);
		return VBSP_STATUS_CONTINUE;
	}

	return VBSP_STATUS_STOP;
}


/* _hoops_SASI _hoops_IS _hoops_HHCPR _hoops_GPRR _hoops_PGGIA.
 * _hoops_SAHHA _hoops_IISA _hoops_HII _hoops_GPHHA _hoops_RSCRR _hoops_HIGR.
 *	 _hoops_CRSAR _hoops_IISA _hoops_HII 1_hoops_ICPC _hoops_IPHRA (_hoops_ARIP).
 *	 _hoops_SRSAR _hoops_IISA _hoops_HII 2_hoops_GRSP _hoops_IPHRA (_hoops_RHI). */
local _hoops_CSCAR _hoops_HCPIA(void *_hoops_HCSAR, void *_hoops_IASAR, void *_hoops_CASAR)
{
	_hoops_PIGIA *_hoops_ICPIA;
	float _hoops_GIGCR,_hoops_RIGCR;
	global_compare_info *info = (global_compare_info *)_hoops_HCSAR;
	_hoops_SHPPA *_hoops_SIPIA = (_hoops_SHPPA *)_hoops_IASAR;
	_hoops_SHPPA *_hoops_GCPIA = (_hoops_SHPPA *)_hoops_CASAR;
	_hoops_RAGIA *_hoops_IIAIA;
	info->_hoops_GARIA._hoops_CRRIA++;

	info->_hoops_GARIA._hoops_SRRIA++;
	_hoops_IIAIA = (_hoops_RAGIA *) info->_hoops_HSGIA;

	if (_hoops_IIAIA->_hoops_PAGIA == null)
		_hoops_IIPIA(_hoops_IIAIA);

	_hoops_GIGCR = HI_Cuboid_To_Cuboid_Distance(_hoops_SIPIA->bbox, _hoops_GCPIA->bbox);
//	_hoops_CCPIA = _hoops_SCPIA(_hoops_GSPIA->_hoops_PAGPR, _hoops_RSPIA->_hoops_PAGPR);
	info->_hoops_GARIA._hoops_IRRIA++;
	if (!info->_hoops_GGRIA->PeekFirst()) {
		_hoops_RIGCR = HI_Cuboid_To_Cuboid_Max_Distance(_hoops_SIPIA->bbox, _hoops_GCPIA->bbox);

		ALLOC(_hoops_ICPIA, _hoops_PIGIA);
		_hoops_ICPIA->f1 = _hoops_SIPIA;
		_hoops_ICPIA->f2 = _hoops_GCPIA;
		_hoops_ICPIA->min = _hoops_GIGCR;
		_hoops_ICPIA->max = _hoops_RIGCR;
		_hoops_ICPIA->_hoops_IIAIA = (void *)_hoops_IIAIA;
		info->_hoops_HGRIA = _hoops_GIGCR;
		info->_hoops_IGRIA = _hoops_RIGCR;
		if (!info->_hoops_ASGIA->_hoops_GSSAR) {
			info->_hoops_ASGIA->_hoops_GSSAR = true;
			info->_hoops_ASGIA->_hoops_SCSAR = _hoops_RIGCR;
		}
		else if (_hoops_RIGCR < info->_hoops_IGRIA)
			info->_hoops_ASGIA->_hoops_SCSAR = _hoops_RIGCR;

 		info->_hoops_GGRIA->AddLast(_hoops_ICPIA);
	}
	else {
 		if (_hoops_GIGCR <= info->_hoops_IGRIA) {
			_hoops_RIGCR = HI_Cuboid_To_Cuboid_Max_Distance(_hoops_SIPIA->bbox, _hoops_GCPIA->bbox);
			if (_hoops_GIGCR < info->_hoops_HGRIA)
				info->_hoops_HGRIA = _hoops_GIGCR;
			if (_hoops_RIGCR < info->_hoops_IGRIA) {
				info->_hoops_IGRIA = _hoops_RIGCR;
				info->_hoops_ASGIA->_hoops_SCSAR = _hoops_RIGCR;
			}

			ALLOC(_hoops_ICPIA, _hoops_PIGIA);
			_hoops_ICPIA->f1 = _hoops_SIPIA;
			_hoops_ICPIA->f2 = _hoops_GCPIA;
			_hoops_ICPIA->min = _hoops_GIGCR;
			_hoops_ICPIA->max = _hoops_RIGCR;
			_hoops_ICPIA->_hoops_IIAIA = (void *)_hoops_IIAIA;
			info->_hoops_GGRIA->AddLast(_hoops_ICPIA);
		}
	}
	return VBSP_STATUS_CONTINUE;
}


/* _hoops_SASI _hoops_IS _hoops_HHCPR _hoops_GPRR _hoops_PGGIA.
 * _hoops_SAHHA _hoops_IISA _hoops_HII _hoops_GPHHA _hoops_RSCRR _hoops_HIGR.
 *	 _hoops_CRSAR _hoops_IISA _hoops_HII 1_hoops_ICPC _hoops_IPHRA (_hoops_ARIP).
 *	 _hoops_SRSAR _hoops_IISA _hoops_HII 2_hoops_GRSP _hoops_IPHRA (_hoops_RHI). */
local _hoops_CSCAR _hoops_ASPIA(void *_hoops_HCSAR, void *_hoops_IASAR, void *_hoops_CASAR)
{
	_hoops_PIGIA *		_hoops_ICPIA;
 	global_compare_info *	info = (global_compare_info *)_hoops_HCSAR;
	_hoops_SHPPA *			_hoops_SIPIA = (_hoops_SHPPA *)_hoops_IASAR;
	_hoops_SHPPA *			_hoops_GCPIA = (_hoops_SHPPA *)_hoops_CASAR;

	Vector	_hoops_CCSAR = info->_hoops_ASGIA->_hoops_CCSAR;
	_hoops_CCSAR *= 1000.0f;

	Point _hoops_CCAIA = _hoops_AICIR(_hoops_SIPIA->bbox.max, _hoops_SIPIA->bbox.min);
	Point _hoops_SCAIA = _hoops_AICIR(_hoops_GCPIA->bbox.max, _hoops_GCPIA->bbox.min);

	float _hoops_ASAIA = _hoops_SIPIA->bbox._hoops_RSAIA().length();
	float _hoops_GSAIA = _hoops_GCPIA->bbox._hoops_RSAIA().length();

	Point _hoops_PSAIA(_hoops_CCAIA.x + _hoops_CCSAR.x, _hoops_CCAIA.y + _hoops_CCSAR.y, _hoops_CCAIA.z + _hoops_CCSAR.z);

	info->_hoops_GARIA._hoops_CRRIA++;
	info->_hoops_GARIA._hoops_SRRIA++;

	_hoops_RAGIA *_hoops_IIAIA = (_hoops_RAGIA *) info->_hoops_HSGIA;
	if (_hoops_IIAIA->type != _hoops_GGPIA) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
			"incorrect callback used in compute selection by shell");
		return VBSP_STATUS_STOP;
	}
	if (_hoops_IIAIA->_hoops_PAGIA == null)
		_hoops_IIPIA(_hoops_IIAIA);

	Point _hoops_HGII;
	float dist;

	if (HI_Compute_Point_To_Line_Distance(&_hoops_SCAIA, &_hoops_CCAIA, &_hoops_PSAIA, &dist, &_hoops_HGII)) {
		if (dist < (_hoops_GSAIA/2.0f + _hoops_ASAIA/2.0f)) {
			float _hoops_RIGCR = _hoops_SRCIR(_hoops_CCAIA, _hoops_HGII) + _hoops_ASAIA/2.0f  + _hoops_GSAIA/2.0f;
			float _hoops_GIGCR = _hoops_SRCIR(_hoops_CCAIA, _hoops_HGII);

 			info->_hoops_GARIA._hoops_IRRIA++;

			if (!info->_hoops_GGRIA->PeekFirst()) {
				ALLOC(_hoops_ICPIA, _hoops_PIGIA);
				_hoops_ICPIA->f1 = _hoops_SIPIA;
				_hoops_ICPIA->f2 = _hoops_GCPIA;
				_hoops_ICPIA->min = _hoops_GIGCR;
				_hoops_ICPIA->max = _hoops_RIGCR;
				_hoops_ICPIA->_hoops_IIAIA = (void *)_hoops_IIAIA;
				info->_hoops_HGRIA = _hoops_GIGCR;
				info->_hoops_IGRIA = _hoops_RIGCR;

				if (!info->_hoops_ASGIA->_hoops_GSSAR) {
					info->_hoops_ASGIA->_hoops_GSSAR = true;
					info->_hoops_ASGIA->_hoops_SCSAR = _hoops_RIGCR;
				}
				else if (_hoops_RIGCR < info->_hoops_IGRIA)
					info->_hoops_ASGIA->_hoops_SCSAR = _hoops_RIGCR;

 				info->_hoops_GGRIA->AddLast(_hoops_ICPIA);
			}
			else {
				if (_hoops_GIGCR <= info->_hoops_IGRIA) {
					if (_hoops_GIGCR < info->_hoops_HGRIA)
						info->_hoops_HGRIA = _hoops_GIGCR;

					if (_hoops_RIGCR < info->_hoops_IGRIA) {
						info->_hoops_IGRIA = _hoops_RIGCR;
						info->_hoops_ASGIA->_hoops_SCSAR = _hoops_RIGCR;
					}

					info->_hoops_GGRIA->ResetCursor();

					while (1) {
						_hoops_PIGIA *temp = info->_hoops_GGRIA->PeekCursor();

						if (temp && temp->min > _hoops_RIGCR) {
							_hoops_PIGIA *t = info->_hoops_GGRIA->RemoveAtCursor();
							FREE(t, _hoops_PIGIA);
						}
						else {
							if (!temp || temp->min >= _hoops_GIGCR) {
								ALLOC(_hoops_ICPIA, _hoops_PIGIA);
								_hoops_ICPIA->f1 = _hoops_SIPIA;
								_hoops_ICPIA->f2 = _hoops_GCPIA;
								_hoops_ICPIA->min = _hoops_GIGCR;
								_hoops_ICPIA->max = _hoops_RIGCR;
								_hoops_ICPIA->_hoops_IIAIA = (void *)_hoops_IIAIA;
								info->_hoops_GGRIA->AddBeforeCursor(_hoops_ICPIA);
								break;
							}

							if (!temp)
								break;

							info->_hoops_GGRIA->AdvanceCursor();
						}
					}
				}
			}
		}
	}
	return VBSP_STATUS_CONTINUE;
}


local _hoops_CSCAR _hoops_PSPIA(_hoops_GHHI *arc, _hoops_ARPA *plane)
{
	/* _hoops_CSGA _hoops_SHHP _hoops_HPAHR _hoops_IS _hoops_CGIC _hoops_IPPA _hoops_CGSSR */
	plane->a = arc->_hoops_GGHI.y * arc->_hoops_RGHI.z - arc->_hoops_RGHI.y * arc->_hoops_GGHI.z;
	plane->b = arc->_hoops_GGHI.z * arc->_hoops_RGHI.x - arc->_hoops_RGHI.z * arc->_hoops_GGHI.x;
	plane->c = arc->_hoops_GGHI.x * arc->_hoops_RGHI.y - arc->_hoops_RGHI.x * arc->_hoops_GGHI.y;
	plane->d = -((plane->a * arc->center.x) +
				 (plane->b * arc->center.y) +
				 (plane->c * arc->center.z));
	if (!HI_Normalize_Plane (plane))
		return VBSP_STATUS_STOP;
	return VBSP_STATUS_CONTINUE;
}


#define 	_hoops_HSPIA		0
#define 	_hoops_ISPIA	1
#define 	_hoops_CSPIA	2

local int _hoops_SSPIA(
	Geometry const *	_hoops_GGHIA,
	_hoops_HRPA const *	matrix,
	int alter *			_hoops_CRPHA,
	_hoops_ARPA alter *		_hoops_RGHIA,
	Point alter **		_hoops_AGHIA)
{
	int point_count;
	Point *_hoops_PAGIA = *_hoops_AGHIA;

	switch (_hoops_GGHIA->type) {
		case _hoops_RCIP: {
			Polygon *polygon = (Polygon *)_hoops_GGHIA;
			*_hoops_CRPHA = point_count = polygon->count;
			if (point_count > _hoops_RSSHA) {
				ALLOC_ARRAY(_hoops_PAGIA, point_count, Point);
				*_hoops_AGHIA = _hoops_PAGIA;
			}
			if (matrix != null) {
				HI_Compute_Transformed_Points (point_count, polygon->points, &matrix->elements[0][0], _hoops_PAGIA);
				if (!HI_Figure_Plane_From_Points (point_count, _hoops_PAGIA, _hoops_RGHIA))
					return _hoops_HSPIA;
			}
			else {
				*_hoops_AGHIA = _hoops_PAGIA = polygon->points;
				if (!BIT (polygon->_hoops_RRHH, _hoops_ARHH))
					  HI_Find_Polygon_Plane	 ((Polygon alter *) polygon);
				COPY_MEMORY(&polygon->plane, sizeof(_hoops_ARPA), _hoops_RGHIA);
			}
		} break;
		case _hoops_SGCP:
		case _hoops_CGCP:
		case _hoops_GRCP:
		case _hoops_RRCP: {
			_hoops_GHHI *	arc = (_hoops_GHHI *)_hoops_GGHIA;

			if (matrix != null) {
				_hoops_GHHI save;
				if (BIT (_hoops_GGHIA->_hoops_RRHH, _hoops_RGGGA)) {
					HI_Compute_Transformed_Points(3, ((_hoops_SSSSR *)_hoops_GGHIA)->points, &matrix->elements[0][0], _hoops_PAGIA);
					return _hoops_ISPIA;
				}
				else if (BIT (_hoops_GGHIA->_hoops_RRHH, _hoops_SHHI)) {
					*_hoops_CRPHA = point_count = HD_Generate_Elliptical_Points(null, arc, _hoops_RSSHA, _hoops_PAGIA);
					HI_Compute_Transformed_Points (point_count, _hoops_PAGIA, &matrix->elements[0][0], _hoops_PAGIA);

					_hoops_ARPA _hoops_RIHI(0, 0, -1, 0);
					HI_Compute_Transformed_Planes(1, &_hoops_RIHI, matrix, _hoops_RGHIA);
					break;
				}
				COPY_MEMORY(arc, sizeof(_hoops_GHHI), &save);
				HI_Compute_Transformed_Points (1, &arc->center, &matrix->elements[0][0], &arc->center);
				HI_Compute_Transformed_Vectors (2, &arc->_hoops_GGHI, &matrix->elements[0][0], &arc->_hoops_GGHI);
				*_hoops_CRPHA = point_count = HD_Generate_Elliptical_Points(null, arc, _hoops_RSSHA, _hoops_PAGIA);
				_hoops_PSPIA(arc, _hoops_RGHIA);
				COPY_MEMORY(&save, sizeof(_hoops_GHHI), arc);
			}
			else {
				*_hoops_CRPHA = point_count = HD_Generate_Elliptical_Points(null, arc, _hoops_RSSHA, _hoops_PAGIA);
				COPY_MEMORY(&arc->plane, sizeof(_hoops_ARPA), _hoops_RGHIA);
			}
		} break;

		default:
			return _hoops_HSPIA;
	}
	return _hoops_CSPIA;
} /* _hoops_RSGR _hoops_API '_hoops_GRAS _hoops_HSSP _hoops_SIHC _hoops_CHIAR _hoops_RSSA' */


/* _hoops_SASI _hoops_IS _hoops_HHCPR _hoops_GPRR _hoops_PGHIA.
 * _hoops_SAHHA _hoops_IISA _hoops_HII _hoops_GPHHA _hoops_RSCRR _hoops_HIGR.
 *	 _hoops_CRSAR _hoops_IISA _hoops_HII 1_hoops_ICPC _hoops_IPHRA (_hoops_ARIP).
 *	 _hoops_SRSAR _hoops_IISA _hoops_HII 2_hoops_GRSP _hoops_IPHRA (_hoops_RHI). */
local _hoops_CSCAR _hoops_HGHIA(void *_hoops_HCSAR, void *_hoops_IASAR, void *_hoops_CASAR)
{
	global_compare_info *	info = (global_compare_info *)_hoops_HCSAR;
	_hoops_SHPPA *			_hoops_SIPIA = (_hoops_SHPPA *)_hoops_IASAR;
	Geometry *				_hoops_GGHIA = (Geometry *)_hoops_CASAR;
	_hoops_HPGIA *	_hoops_IIAIA = (_hoops_HPGIA *) info->_hoops_HSGIA;
	_hoops_HRPA const *		matrix = _hoops_IIAIA->matrix;

	info->_hoops_GARIA._hoops_CRRIA++;

	if (_hoops_IIAIA->type != _hoops_PGPIA) {
		ASSERT(0);
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				"incorrect callback used in compute selection by shell");
		return VBSP_STATUS_STOP; /* _hoops_ICPPA */
	}

	Bounding bounding;
	HI_Figure_Geometry_Bounding(_hoops_GGHIA, bounding);
	_hoops_SASC cuboid = bounding->cuboid;

	if (matrix != null && !matrix->_hoops_PPGH())
		cuboid = cuboid._hoops_SCIS (*matrix);

	if (!_hoops_SIPIA->bbox._hoops_RPCIR(cuboid))
		return VBSP_STATUS_CONTINUE;

	info->_hoops_GARIA._hoops_SRRIA++;

	_hoops_CSCAR	status = VBSP_STATUS_CONTINUE;	 /* _hoops_GRHP _hoops_HHCPR, _hoops_HCCPR _hoops_SR _hoops_IGHIA _hoops_IAII */
	_hoops_ARPA		_hoops_CGHIA;
	int			point_count = 0;
	Point		_hoops_PIAI[_hoops_RSSHA+1];
	Point *		_hoops_PAGIA = _hoops_PIAI;

    switch (_hoops_SSPIA(_hoops_GGHIA, matrix, &point_count, &_hoops_CGHIA, &_hoops_PAGIA)) {
		case _hoops_ISPIA: {
			if (!_hoops_SGHIA(info->_hoops_SCGIA, _hoops_SIPIA, &_hoops_PAGIA[0], &_hoops_PAGIA[1]) == _hoops_HPHHA)
				goto _hoops_HPAGR;

			if (!_hoops_SGHIA(info->_hoops_SCGIA, _hoops_SIPIA, &_hoops_PAGIA[1], &_hoops_PAGIA[2]) == _hoops_HPHHA)
				goto _hoops_HPAGR;
		} break;

		case _hoops_CSPIA: {
			if (!_hoops_HIPPA(_hoops_PAGIA, point_count, null, _hoops_SIPIA->plane))
				goto _hoops_HPAGR;

			if (!_hoops_HIPPA(info->_hoops_SCGIA, _hoops_SIPIA->len, _hoops_SIPIA->_hoops_GIPPA, _hoops_CGHIA))
				goto _hoops_HPAGR;

			if (!_hoops_IIPPA(
					info->_hoops_SCGIA,
					_hoops_SIPIA->len,
					_hoops_SIPIA->_hoops_GIPPA,
					&_hoops_SIPIA->plane,
					_hoops_PAGIA,
					point_count,
					null,
					&_hoops_CGHIA,
					null))
					goto _hoops_HPAGR;
		} break;

		case _hoops_HSPIA:
			goto _hoops_HPAGR;
	}

	/* _hoops_CIGAA, _hoops_PPR _hoops_GRHP _hoops_HHCPR _hoops_RPP _hoops_SR _hoops_SIPGR'_hoops_RA _hoops_GAPR _hoops_RHHR _hoops_RH _hoops_SAIPR */
	status = _hoops_IIAIA->_hoops_CPGIA->Append(_hoops_GGHIA);

_hoops_HPAGR:

	if (matrix != null &&
		_hoops_PAGIA != null &&
		_hoops_PAGIA != _hoops_PIAI) {
		FREE_ARRAY(_hoops_PAGIA, point_count, Point);
	}

	return status;
}



local void _hoops_GRHIA(_hoops_GHGIA *info, _hoops_RRHIA *_hoops_ARHIA)
{
	Point points[_hoops_GSSHA+2];
	PolyCylinder *_hoops_HSPIR = info->_hoops_HSPIR;

	_hoops_ARHIA->flags &= ~_hoops_PRHIA;

	_hoops_ARHIA->bbox = _hoops_SASC();

	if (info->matrix) {
		Point pt;
		Vector _hoops_HRHIA, _hoops_IRHIA;

		for (int i=0; i<_hoops_HSPIR->point_count; i++) {
			Vector		axis[2];
			float radius = _hoops_HSPIR->radii[i % _hoops_HSPIR->_hoops_ISPIR];

			axis[0].x = _hoops_HSPIR->_hoops_CSPIR[i].axis[0].x * radius;
			axis[0].y = _hoops_HSPIR->_hoops_CSPIR[i].axis[0].y * radius;
			axis[0].z = _hoops_HSPIR->_hoops_CSPIR[i].axis[0].z * radius;
			axis[1].x = _hoops_HSPIR->_hoops_CSPIR[i].axis[1].x * radius;
			axis[1].y = _hoops_HSPIR->_hoops_CSPIR[i].axis[1].y * radius;
			axis[1].z = _hoops_HSPIR->_hoops_CSPIR[i].axis[1].z * radius;

			HI_Compute_Transformed_Points(1, &_hoops_HSPIR->points[i], &info->matrix->elements[0][0], &pt);
			HI_Compute_Transformed_Points(1, (Point const *)(&axis[0]), &info->matrix->elements[0][0], (Point *)&_hoops_HRHIA);
			HI_Compute_Transformed_Points(1, (Point const *)(&axis[1]), &info->matrix->elements[0][0], (Point *)&_hoops_IRHIA);

			HD_Generate_Complete_Points(&pt, &_hoops_HRHIA, &_hoops_IRHIA, _hoops_GSSHA, true, points);

			_hoops_ARHIA->bbox.Merge (_hoops_GSSHA, points);
		}
	}
	else {
		for (int i=0; i<_hoops_HSPIR->point_count; i++) {
			Vector		axis[2];
			float radius = _hoops_HSPIR->radii[i % _hoops_HSPIR->_hoops_ISPIR];

			axis[0].x = _hoops_HSPIR->_hoops_CSPIR[i].axis[0].x * radius;
			axis[0].y = _hoops_HSPIR->_hoops_CSPIR[i].axis[0].y * radius;
			axis[0].z = _hoops_HSPIR->_hoops_CSPIR[i].axis[0].z * radius;
			axis[1].x = _hoops_HSPIR->_hoops_CSPIR[i].axis[1].x * radius;
			axis[1].y = _hoops_HSPIR->_hoops_CSPIR[i].axis[1].y * radius;
			axis[1].z = _hoops_HSPIR->_hoops_CSPIR[i].axis[1].z * radius;

			HD_Generate_Complete_Points(&_hoops_HSPIR->points[i],&axis[0],&axis[1],_hoops_GSSHA, true, points);

			_hoops_ARHIA->bbox.Merge (_hoops_GSSHA, points);
		}
	}
}


local bool _hoops_CRHIA(
		_hoops_SHPPA const *	_hoops_SIPIA,
		Point const *		_hoops_SCGIA,
		_hoops_SHPPA const *	_hoops_GCPIA,
		Point const *		_hoops_SRHIA)
{
	if (!_hoops_HIPPA(_hoops_SCGIA, _hoops_SIPIA->len, _hoops_SIPIA->_hoops_GIPPA, _hoops_GCPIA->plane))
		return false;

	if (!_hoops_HIPPA(_hoops_SRHIA, _hoops_GCPIA->len, _hoops_GCPIA->_hoops_GIPPA, _hoops_SIPIA->plane))
		return false;

	if (!_hoops_IIPPA(
							_hoops_SCGIA,
							_hoops_SIPIA->len,
							_hoops_SIPIA->_hoops_GIPPA,
							&_hoops_SIPIA->plane,
							_hoops_SRHIA,
							_hoops_GCPIA->len,
							_hoops_GCPIA->_hoops_GIPPA,
							&_hoops_GCPIA->plane,
							null))
		return false;

	return true;
}


/* _hoops_CPS _hoops_PIHA _hoops_SHH _hoops_GAHIA.
 * "_hoops_RAHIA" != 0 _hoops_AGSR _hoops_RPGP _hoops_RH _hoops_PRPC _hoops_IIGR _hoops_RH _hoops_AAHIA */
local bool _hoops_PAHIA(
	Point const *		_hoops_SCGIA,
	_hoops_SHPPA const *	_hoops_SIPIA,
	Point const *		_hoops_HAHIA,
	Point const *		bottom,
	_hoops_SSPIR const *	_hoops_CSPIR,
	int					_hoops_IAHIA)
{
	Point _hoops_CAHIA[2 + _hoops_GSSHA];
	int indices[2 + _hoops_GSSHA], _hoops_RCHHR[3];

	_hoops_ARPA plane;
	HI_Cross_Product (&_hoops_CSPIR->axis[0], &_hoops_CSPIR->axis[1], (Vector *)&plane);

	plane.d = -(bottom->x * plane.a + bottom->y * plane.b + bottom->z * plane.c);

	/* _hoops_HSII _hoops_RH _hoops_RAHIA _hoops_GAR _hoops_IRS _hoops_HHAA _hoops_GC _hoops_PPR _hoops_CACH _hoops_RPP _hoops_RH _hoops_RAGA _hoops_HSP _hoops_PAH _hoops_SHH
	 * _hoops_CCGC _hoops_SACH _hoops_SGGR. */

	bool	in = (plane * *_hoops_HAHIA > 0);

	int i;
	for (i = 0; i < _hoops_SIPIA->len; i++) {
		if (in == (plane * _hoops_SCGIA[_hoops_SIPIA->_hoops_GIPPA[i]] > 0))
			break;
	}

	if (i == _hoops_SIPIA->len)
		return false;

	_hoops_SHPPA _hoops_SAHIA;
	_hoops_SAHIA.type = _hoops_GPHIA;
	_hoops_SAHIA.flags = 0;
	_hoops_SAHIA.len = _hoops_GSSHA;
	_hoops_SAHIA.plane = plane;

	HD_Generate_Complete_Points (bottom, &_hoops_CSPIR->axis[0], &_hoops_CSPIR->axis[1], _hoops_GSSHA, true, _hoops_CAHIA);

	if (_hoops_IAHIA) {
		for (i = 0; i < _hoops_GSSHA; i++)
			indices[i] = i;
		_hoops_SAHIA._hoops_GIPPA = indices;
		if (_hoops_CRHIA(_hoops_SIPIA, _hoops_SCGIA, &_hoops_SAHIA, _hoops_CAHIA))
			return true;
	}

	/* _hoops_RH _hoops_RPHIA */
	COPY_MEMORY(_hoops_HAHIA, sizeof(Point), &_hoops_CAHIA[_hoops_GSSHA+1]);
	_hoops_SAHIA._hoops_GIPPA = _hoops_RCHHR;
	_hoops_RCHHR[0] = _hoops_GSSHA+1;
	_hoops_SAHIA.len = 3;
	for (i = 0; i < _hoops_GSSHA; i++) {
		_hoops_RCHHR[1] = i;
		_hoops_RCHHR[2] = i+1;
		_hoops_APHIA(_hoops_CAHIA, 3, _hoops_RCHHR, false, &plane);
		if (_hoops_CRHIA(_hoops_SIPIA, _hoops_SCGIA, &_hoops_SAHIA, _hoops_CAHIA))
			return true;
	}

	/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_ARI, _hoops_SGS _hoops_AGSR _hoops_SGS _hoops_SR _hoops_IIP _hoops_RHHR _hoops_GII _hoops_IIGR _hoops_RH _hoops_RSSI.
	 * (_hoops_HAR _hoops_PCCP _hoops_PPHIA _hoops_HPHIA.	_hoops_IPHIA _hoops_HPPR _hoops_GICS; -)). */
	return false;
}


/* _hoops_GCIAR _hoops_PIHA _hoops_SHH _hoops_GAHIA.
 * "_hoops_PCAS" _hoops_SIGH _hoops_RAHIA _hoops_CPHIA: _hoops_SPHIA _hoops_PPR/_hoops_PAR _hoops_GHHIA */
local bool _hoops_RHHIA(
		Point const *_hoops_SCGIA,
		_hoops_SHPPA const *_hoops_SIPIA,
		Point const *p1,
		Point const *p2,
		_hoops_SSPIR const *_hoops_GGHI,
		_hoops_SSPIR const *_hoops_RGHI,
		int _hoops_AHHIA)
{
	_hoops_ARPA planes[2];

	HI_Cross_Product (&_hoops_GGHI->axis[0], &_hoops_GGHI->axis[1], (Vector *)&planes[0]);
	planes[0].d = -(p1->x * planes[0].a + p1->y * planes[0].b + p1->z * planes[0].c);

	/* _hoops_RHRIR: _hoops_HSPR _hoops_HRGR _hoops_PIIA _hoops_AGR _hoops_HII _hoops_PGHC _hoops_SHHP _hoops_HPAHR */
	HI_Cross_Product (&_hoops_RGHI->axis[1], &_hoops_RGHI->axis[0], (Vector *)&planes[1]);
	planes[1].d = -(p2->x * planes[1].a + p2->y * planes[1].b + p2->z * planes[1].c);

	bool in;
	/* _hoops_HSII _hoops_RH _hoops_PGCR _hoops_PCAS _hoops_GAR _hoops_HHAA _hoops_HGS _hoops_PPR _hoops_CACH _hoops_RPP _hoops_RH _hoops_RAGA _hoops_HSP _hoops_PAH _hoops_SHH
	 * _hoops_CCGC _hoops_SACH _hoops_SGGR. */
	for (int j = 0; j < 2; j++) {
		in = false;
		for (int i = 0; i < _hoops_SIPIA->len && !in; i++) {
			in = (planes[j] * _hoops_SCGIA[_hoops_SIPIA->_hoops_GIPPA[i]] > 0);
		}
		if (!in)
			return false;
	}

	int indices[2 + _hoops_GSSHA];

	_hoops_SHPPA _hoops_SAHIA;
	_hoops_SAHIA.type = _hoops_GPHIA;
	_hoops_SAHIA.flags = 0;
	_hoops_SAHIA.len = _hoops_GSSHA;
	_hoops_SAHIA._hoops_GIPPA = indices;

	if (_hoops_AHHIA)
		for (int i = 0; i < _hoops_GSSHA; i++)
			indices[i] = i;

	Point _hoops_CAHIA[2 + _hoops_GSSHA*2];
	Point alter *	_hoops_PHHIA;
	Point alter *	_hoops_HHHIA;

	_hoops_PHHIA = _hoops_CAHIA;

	HD_Generate_Complete_Points (p1, &_hoops_GGHI->axis[0], &_hoops_GGHI->axis[1],
								 _hoops_GSSHA, true, _hoops_PHHIA);

	if (_hoops_AHHIA & _hoops_IHHIA) {
		_hoops_SAHIA.plane = planes[0];
		_hoops_CHHIA(_hoops_PHHIA, null, _hoops_GSSHA, indices, _hoops_SAHIA.bbox);
		if (_hoops_CRHIA(_hoops_SIPIA, _hoops_SCGIA, &_hoops_SAHIA, _hoops_PHHIA))
			return true;
	}


	_hoops_PHHIA = _hoops_CAHIA + _hoops_GSSHA + 1;
	HD_Generate_Complete_Points (p2, &_hoops_RGHI->axis[0], &_hoops_RGHI->axis[1],
								 _hoops_GSSHA, true, _hoops_PHHIA);

	if (_hoops_AHHIA & _hoops_SHHIA) {
		_hoops_SAHIA.plane = planes[1];
		_hoops_CHHIA(_hoops_PHHIA, null, _hoops_GSSHA, indices, _hoops_SAHIA.bbox);
		if (_hoops_CRHIA(_hoops_SIPIA, _hoops_SCGIA, &_hoops_SAHIA, _hoops_PHHIA))
			return true;
	}


	indices[0] = 0;
	indices[1] = 1;
	indices[2] = _hoops_GSSHA+2;
	indices[3] = _hoops_GSSHA+1;
	_hoops_SAHIA.len = 4;

	for (int i = 0; i < _hoops_GSSHA; i++) {
		_hoops_HHHIA = &_hoops_CAHIA[i];
		_hoops_APHIA(_hoops_HHHIA, 4, indices, false, &_hoops_SAHIA.plane);
		_hoops_CHHIA(_hoops_HHHIA, null, 4, indices, _hoops_SAHIA.bbox);
		if (_hoops_CRHIA(_hoops_SIPIA, _hoops_SCGIA, &_hoops_SAHIA, _hoops_HHHIA))
			return true;
	}

	/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_ARI, _hoops_SGS _hoops_AGSR _hoops_SGS _hoops_SR _hoops_IIP _hoops_RHHR _hoops_GII _hoops_IIGR _hoops_RH _hoops_RSSI.
	 * (_hoops_HAR _hoops_PCCP _hoops_PPHIA _hoops_HPHIA.	_hoops_IPHIA _hoops_HPPR _hoops_GICS; -)). */
	return false;
}


/* _hoops_SASI _hoops_IS _hoops_HHCPR _hoops_GPRR _hoops_GIHIA */
local _hoops_CSCAR _hoops_RIHIA(void *_hoops_HCSAR, void *_hoops_IASAR, void *_hoops_CASAR)
{
	global_compare_info *		info = (global_compare_info *)_hoops_HCSAR;
	_hoops_SHPPA *				_hoops_SIPIA = (_hoops_SHPPA *)_hoops_IASAR;
	_hoops_RRHIA *					_hoops_ARHIA = (_hoops_RRHIA *)_hoops_CASAR;
	_hoops_GHGIA *	env_info = (_hoops_GHGIA *) info->_hoops_HSGIA;


	PolyCylinder const *		_hoops_HSPIR = env_info->_hoops_HSPIR;
	_hoops_HRPA const *			matrix = env_info->matrix;

	float _hoops_AIHIA, _hoops_PIHIA, radius, _hoops_HIHIA;
	int state, _hoops_IIHIA;
	bool _hoops_CIHIA;
	Point *_hoops_PAGIA = null;
	_hoops_SSPIR *_hoops_SIHIA = null;
	Point _hoops_GCHIA[_hoops_GIAHA];
	_hoops_SSPIR _hoops_RCHIA[_hoops_GIAHA];
	int _hoops_ACHIA = _hoops_ARHIA->end - _hoops_ARHIA->start + 1;

	int flags;

	_hoops_CSCAR		status = VBSP_STATUS_CONTINUE; /* _hoops_GRHP _hoops_HHCPR _hoops_HCCPR _hoops_SR _hoops_IGHIA _hoops_IAII */

	info->_hoops_GARIA._hoops_CRRIA++;

	if (!_hoops_SIPIA->bbox._hoops_RPCIR(_hoops_ARHIA->bbox))
		return status;

	if (env_info->type != _hoops_IGPIA) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				"incorrect type encountered in test_face_pc_callback");
		status = VBSP_STATUS_STOP; /* _hoops_ICPPA */
		return status;
	}

	if (_hoops_ARHIA->flags & _hoops_PRHIA) {
		_hoops_GRHIA(env_info, _hoops_ARHIA);
		if (!_hoops_SIPIA->bbox._hoops_RPCIR(_hoops_ARHIA->bbox))
			return status;
	}

	info->_hoops_GARIA._hoops_SRRIA++;

	if (matrix != null) {
		float _hoops_HGSRR[16];

		if (_hoops_ACHIA > _hoops_GIAHA) {
			ALLOC_ARRAY(_hoops_PAGIA, _hoops_ACHIA, Point);
			ALLOC_ARRAY(_hoops_SIHIA, _hoops_ACHIA, _hoops_SSPIR);
		}
		else {
			_hoops_PAGIA = _hoops_GCHIA;
			_hoops_SIHIA = _hoops_RCHIA;
		}
		HI_Compute_Transformed_Points(_hoops_ACHIA, (Point const *)(_hoops_HSPIR->points + _hoops_ARHIA->start), &matrix->elements[0][0], (Point *)_hoops_PAGIA);

		/* _hoops_IPS _hoops_RH _hoops_RSGA _hoops_PPR _hoops_PCHIA _hoops_RH _hoops_HCHIA _hoops_IHSR */
		COPY_MEMORY(matrix, 12*sizeof(float), _hoops_HGSRR);
		_hoops_HGSRR[12] = 0;
		_hoops_HGSRR[13] = 0;
		_hoops_HGSRR[14] = 0;
		_hoops_HGSRR[15] = 1;
		HI_Compute_Transformed_Points(2 * _hoops_ACHIA, (Point const *)(_hoops_HSPIR->_hoops_CSPIR + _hoops_ARHIA->start), _hoops_HGSRR, (Point *)_hoops_SIHIA);
	}
	else {
		_hoops_PAGIA = _hoops_HSPIR->points + _hoops_ARHIA->start;
		_hoops_SIHIA = _hoops_HSPIR->_hoops_CSPIR + _hoops_ARHIA->start;
	}

	int		index = 0;

	_hoops_AIHIA = _hoops_SIPIA->plane * _hoops_PAGIA[index];

	radius = (_hoops_HSPIR->_hoops_ISPIR == 0 ? 0 : _hoops_HSPIR->radii[index % _hoops_HSPIR->_hoops_ISPIR]);
	state = (_hoops_AIHIA > radius ? 1 : (_hoops_AIHIA < -radius ? -1 : 0)); /* _hoops_ARRS, _hoops_CAPP, _hoops_PAR _hoops_IAGPR */
	do {
		_hoops_PIHIA = _hoops_AIHIA;
		_hoops_IIHIA = state;
		_hoops_HIHIA = radius;
		index++;

		_hoops_AIHIA = _hoops_SIPIA->plane * _hoops_PAGIA[index];

		radius = (_hoops_HSPIR->_hoops_ISPIR == 0 ? 0 : _hoops_HSPIR->radii[index % _hoops_HSPIR->_hoops_ISPIR]);
		state = (_hoops_AIHIA > radius ? 1 : (_hoops_AIHIA < -radius ? -1 : 0)); /* _hoops_ARRS, _hoops_CAPP, _hoops_PAR _hoops_IAGPR */
		flags = 0;
		if ((_hoops_ARHIA->start + index == 1) &&
			(_hoops_HSPIR->flags & _hoops_IHHIA))
			flags |= _hoops_IHHIA;
		if ((_hoops_ARHIA->start + index + 1 == _hoops_HSPIR->point_count) &&
			(_hoops_HSPIR->flags & _hoops_SHHIA))
			flags |= _hoops_SHHIA;
		/* _hoops_RPP _hoops_III _hoops_ICSHR _hoops_ICHIA _hoops_IPPA, _hoops_PAR _hoops_RPP _hoops_SCGR _hoops_PAR _hoops_PGHC _hoops_PRHC _hoops_CHR _hoops_GGR, _hoops_GASAR _hoops_HHCPR _hoops_RGHP */
		if (_hoops_IIHIA != state || !_hoops_IIHIA || !state) {
			_hoops_SSPIR	_hoops_CSPIR, _hoops_CCHIA;

			_hoops_CSPIR.axis[0] = _hoops_SIHIA[index].axis[0] * radius;
			_hoops_CSPIR.axis[1] = _hoops_SIHIA[index].axis[1] * radius;
			_hoops_CCHIA.axis[0] = _hoops_SIHIA[index-1].axis[0] * _hoops_HIHIA;
			_hoops_CCHIA.axis[1] = _hoops_SIHIA[index-1].axis[1] * _hoops_HIHIA;

			if (radius < _hoops_CACIR) {
				if (_hoops_HIHIA < _hoops_CACIR) {
					_hoops_CIHIA = (_hoops_SGHIA(
						(Point *)info->_hoops_SCGIA,
						_hoops_SIPIA,
						&_hoops_PAGIA[index-1],
						&_hoops_PAGIA[index]) == _hoops_HPHHA);
				}
				else {
					_hoops_CIHIA = _hoops_PAHIA(
						(Point *)info->_hoops_SCGIA,
						_hoops_SIPIA,
						&_hoops_PAGIA[index],
						&_hoops_PAGIA[index-1],
						&_hoops_CCHIA,
						(flags&_hoops_IHHIA));
				}
			}
			else if (_hoops_HIHIA < _hoops_CACIR) {
				_hoops_CIHIA = _hoops_PAHIA(
					(Point *)info->_hoops_SCGIA,
					_hoops_SIPIA,
					&_hoops_PAGIA[index-1],
					&_hoops_PAGIA[index],
					&_hoops_CSPIR,
					(flags&_hoops_SHHIA));
			}
			else {
				_hoops_CIHIA = _hoops_RHHIA(
					(Point *)info->_hoops_SCGIA,
					_hoops_SIPIA,
					&_hoops_PAGIA[index-1],
					&_hoops_PAGIA[index],
					&_hoops_CCHIA,
					&_hoops_CSPIR,
					flags);
			}
			if (_hoops_CIHIA) {
				/* _hoops_CIGAA, _hoops_PPR _hoops_GRHP _hoops_HHCPR _hoops_RPP _hoops_SR _hoops_SIPGR'_hoops_RA _hoops_GAPR _hoops_RHHR _hoops_RH _hoops_SAIPR */
				if (info->_hoops_ISGIA->Count() != info->_hoops_CSGIA) {
					info->_hoops_ISGIA->Append(info->_hoops_HSGIA);
					status = VBSP_STATUS_CONTINUE;
				}
				else {
					status = VBSP_STATUS_STOP;
					goto _hoops_HPAGR;
				}
			}
		}
	} while (index < _hoops_ACHIA-1);

  _hoops_HPAGR:
	if (matrix != null) {
		if (_hoops_PAGIA != _hoops_GCHIA)
			FREE_ARRAY(_hoops_PAGIA, _hoops_ACHIA, Point);
		if (_hoops_SIHIA != _hoops_RCHIA)
			FREE_ARRAY(_hoops_SIHIA, _hoops_ACHIA, _hoops_SSPIR);
	}
	return status;
}




/* _hoops_HRS _hoops_GRAA-_hoops_AHHR _hoops_RPP _hoops_PPR _hoops_RGAR _hoops_RPP _hoops_IH _hoops_HHH _hoops_ISHA(_hoops_HAS) _hoops_GPP _hoops_RH _hoops_RAGA _hoops_HSP
	_hoops_IRS) _hoops_RH _hoops_PPSR "_hoops_CCAHR" _hoops_HRGR _hoops_SCHIA _hoops_IS _hoops_ISHA(_hoops_HAS) _hoops_HSAR _hoops_PGI _hoops_IIGR _hoops_RGCI _hoops_GSHIA; _hoops_PPR
	_hoops_RCSR) _hoops_ISHA(_hoops_HAS) _hoops_IISA _hoops_IS _hoops_GIAA _hoops_GHRPA _hoops_IIGR _hoops_PPSR "_hoops_CCAHR".  */
local int _hoops_RSHIA(
		const Point *p,
		const float _hoops_PARPA,
		const Point *_hoops_ASHIA,
		int _hoops_HRPPA,
		const int *_hoops_AIIPR)
{
	const Point *_hoops_GAPPA, *_hoops_RAPPA;
	Vector _hoops_ISPI, _hoops_CSPI, v;
	int i, index;
	float _hoops_SSHGA, _hoops_PSHIA, _hoops_PIAIA, t;

	/* _hoops_ISAP _hoops_PAH _hoops_RASAR _hoops_CCA _hoops_IRS _hoops_ARHAR _hoops_HSP */
	if (_hoops_HRPPA < 3)
		return 0;

	for (i = 0; i < _hoops_HRPPA; i++) {
		index = (_hoops_AIIPR ? _hoops_AIIPR[i] : i);
		_hoops_GAPPA = _hoops_ASHIA + index;
		if (i+1 < _hoops_HRPPA) {
			index = (_hoops_AIIPR ? _hoops_AIIPR[i+1] : i+1);
			_hoops_RAPPA = _hoops_ASHIA + index;
		}
		else {
			index = (_hoops_AIIPR ? _hoops_AIIPR[i+1-_hoops_HRPPA] : i+1-_hoops_HRPPA);
			_hoops_RAPPA = _hoops_ASHIA + index; /* _hoops_ARGAR _hoops_AARI */
		}
		_hoops_ISPI.x = _hoops_RAPPA->x - _hoops_GAPPA->x;
		_hoops_ISPI.y = _hoops_RAPPA->y - _hoops_GAPPA->y;
		_hoops_ISPI.z = _hoops_RAPPA->z - _hoops_GAPPA->z;
		_hoops_CSPI.x = p->x - _hoops_GAPPA->x;
		_hoops_CSPI.y = p->y - _hoops_GAPPA->y;
		_hoops_CSPI.z = p->z - _hoops_GAPPA->z;

		/* _hoops_HII _hoops_HSHIA 99 _hoops_IIGR "_hoops_IRS _hoops_ISHIA'_hoops_GRI _hoops_CPAP" _hoops_HPP _hoops_CSHIA _hoops_PPR _hoops_SSHIA
			_hoops_RA = _hoops_RCHP(_hoops_GGIIA-_hoops_RGIIA) + _hoops_ISHI(_hoops_AGIIA-_hoops_PGIIA) + _hoops_GGHR(_hoops_HGIIA-_hoops_IGIIA) / (_hoops_RCHP^2 + _hoops_ISHI^2 + _hoops_GGHR^2)
			_hoops_PGSHA: _hoops_RCHP,_hoops_ISHI,_hoops_GGHR == _hoops_IIHHR;	 *_hoops_CGIIA-*_hoops_SGIIA == _hoops_CIHHR
		*/
		_hoops_SSHGA = (_hoops_ISPI.x*_hoops_ISPI.x + _hoops_ISPI.y*_hoops_ISPI.y + _hoops_ISPI.z*_hoops_ISPI.z);
		_hoops_PSHIA = _hoops_SSHGA*_hoops_SSHGA;
		if (_hoops_PSHIA < _hoops_CACIR)
			continue;

		t = (_hoops_ISPI.x*_hoops_CSPI.x + _hoops_ISPI.y*_hoops_CSPI.y + _hoops_ISPI.z*_hoops_CSPI.z)/_hoops_SSHGA;
		if (t < 0 || t > 1)
			continue;

		/* _hoops_AAGA _hoops_HII _hoops_PPSR _hoops_IS _hoops_HISGR _hoops_PPSR _hoops_GPP _hoops_ISHA */
		v.x = p->x - (_hoops_GAPPA->x + _hoops_ISPI.x*t);
		v.y = p->y - (_hoops_GAPPA->y + _hoops_ISPI.y*t);
		v.z = p->z - (_hoops_GAPPA->z + _hoops_ISPI.z*t);

		_hoops_PIAIA = v.x*v.x + v.y*v.y + v.z*v.z;
		if (_hoops_PIAIA > _hoops_PARPA*_hoops_PARPA)
			continue;

		return 1;
	}
	return 0;
}



/* _hoops_SASI _hoops_IS _hoops_HHCPR _hoops_GPRR _hoops_GRIIA */
local _hoops_CSCAR _hoops_RRIIA(void *_hoops_HCSAR, void *_hoops_IASAR, void *_hoops_CASAR)
{
	global_compare_info *info = (global_compare_info *)_hoops_HCSAR;
	_hoops_SHPPA *_hoops_SIPIA = (_hoops_SHPPA *)_hoops_IASAR;
	_hoops_RHGIA *env_info = (_hoops_RHGIA *)_hoops_CASAR;

	float dist, _hoops_PIAIA;
	_hoops_CSCAR status;

	int const *_hoops_GIPPA;
	int _hoops_HARGA, _hoops_IARGA;

	bool _hoops_CIHIA;
	Point _hoops_ARIIA;
	float _hoops_PRIIA;

	status = VBSP_STATUS_CONTINUE; /* _hoops_GRHP _hoops_HHCPR _hoops_CCGR _hoops_SR _hoops_IGHIA _hoops_IAII */

	info->_hoops_GARIA._hoops_CRRIA++;

	if (!_hoops_SIPIA->bbox._hoops_RPCIR(env_info->bbox))
		return status;

	env_info = (_hoops_RHGIA *) info->_hoops_HSGIA;
	if (env_info->type != _hoops_SGPIA) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				"incorrect type encountered by test_face_sphere_callback");
		status = VBSP_STATUS_STOP; /* _hoops_ICPPA */
		return status;
	}

	info->_hoops_GARIA._hoops_SRRIA++;

	Sphere *		s = env_info->s;

	_hoops_HRPA	*	matrix = env_info->matrix;

	if (matrix != null && !matrix->_hoops_PPGH()) {
		/* _hoops_PHHSR _hoops_RH _hoops_PSAA _hoops_HPP _hoops_RH _hoops_CSRA _hoops_GGR _hoops_RH _hoops_SISR _hoops_HAGA
		 * (_hoops_SRSA: _hoops_IGIPR _hoops_PSP _hoops_HRIIA _hoops_PAR _hoops_GRAA-_hoops_GHRHR _hoops_CCPA _hoops_GGR _hoops_RH _hoops_RSGA) */

		_hoops_PRIIA = s->data.radius * _hoops_SGIHR(
				matrix->elements[0][0]*matrix->elements[0][0] +
				matrix->elements[0][1]*matrix->elements[0][1] +
				matrix->elements[0][2]*matrix->elements[0][2]);

		HI_Compute_Transformed_Points(1, &s->data.center, &matrix->elements[0][0], &_hoops_ARIIA);
	}
	else {
		_hoops_ARIIA = s->data.center;
		_hoops_PRIIA = s->data.radius;
	}

	/* _hoops_ARAS _hoops_RH _hoops_CHHRR _hoops_RHCH _hoops_ACSRR _hoops_RH _hoops_IPPA _hoops_CGSSR _hoops_IS _hoops_HGCR _hoops_RH _hoops_GIRA
	 * _hoops_HII _hoops_CHHRR _hoops_RHCH _hoops_IS _hoops_RH _hoops_HISGR _hoops_PPSR _hoops_GPP _hoops_RH _hoops_IPPA.  _hoops_CGP _hoops_SGS _hoops_HRGR _hoops_SIPP
	 * _hoops_RH _hoops_CHHRR, _hoops_SR'_hoops_ASAR _hoops_CPHR. */
	float _hoops_AIHIA = _hoops_SIPIA->plane * _hoops_ARIIA;
	if (_hoops_AIHIA > 0)
		dist = _hoops_AIHIA;
	else
		dist = -_hoops_AIHIA;
	if (dist > _hoops_PRIIA)
		return status;

	_hoops_GIPPA = _hoops_SIPIA->_hoops_GIPPA;

	Point const * pts = info->_hoops_SCGIA;
	_hoops_HARGA = _hoops_IARGA = 0;
	_hoops_PIAIA = _hoops_PRIIA * _hoops_PRIIA;

	for (int i = 0; i < _hoops_SIPIA->len; i++) {
		float _hoops_IRIIA = (_hoops_ARIIA - pts[_hoops_GIPPA[i]])._hoops_PPSSR();
		if (_hoops_IRIIA > _hoops_PIAIA)
			_hoops_IARGA++;
		else
			_hoops_HARGA++;
	}

	_hoops_CIHIA = false;
	if (_hoops_HARGA && _hoops_IARGA) {
		_hoops_CIHIA = true;
	}
	else if (_hoops_IARGA) {
		if (_hoops_RSHIA(&_hoops_ARIIA, _hoops_PRIIA, pts, _hoops_SIPIA->len, _hoops_GIPPA))
			_hoops_CIHIA = true;
		else {
			Point p = _hoops_ARIIA + Vector(_hoops_SIPIA->plane) * _hoops_AIHIA;
			if (_hoops_AHHHA(&p, pts, _hoops_SIPIA->len, _hoops_GIPPA, &_hoops_SIPIA->plane, 0))
				_hoops_CIHIA = true;
		}
	}
	if (_hoops_CIHIA) {
		/* _hoops_CIGAA.	_hoops_CGP _hoops_SR _hoops_SIPGR'_hoops_RA _hoops_GAPR _hoops_RHHR _hoops_RH _hoops_SAIPR, _hoops_ASRC _hoops_PIRA _hoops_SIGH _hoops_IGH _hoops_IS _hoops_SAS _hoops_HHCPR */
		if (info->_hoops_ISGIA->Count() != info->_hoops_CSGIA) {
			info->_hoops_ISGIA->Append(info->_hoops_HSGIA);
			status = VBSP_STATUS_CONTINUE;
		}
		else
			status = VBSP_STATUS_STOP;
	}

	return status;
}




/* _hoops_SASI _hoops_IS _hoops_HHCPR _hoops_GPRR _hoops_CRIIA */
local _hoops_CSCAR _hoops_SRIIA(void *_hoops_HCSAR, void *_hoops_IASAR, void *_hoops_CASAR)
{
	global_compare_info *		info = (global_compare_info *)_hoops_HCSAR;
	_hoops_SHPPA *				_hoops_SIPIA = (_hoops_SHPPA *)_hoops_IASAR;
	_hoops_AHGIA *		env_info = (_hoops_AHGIA *)_hoops_CASAR;


	float _hoops_PIHIA, radius;
	int state, _hoops_IIHIA;

	Point *_hoops_PAGIA = null;
	_hoops_SSPIR *_hoops_GAIIA = null;
	Point _hoops_GCHIA[2];
	_hoops_SSPIR _hoops_RCHIA[1];

	_hoops_CSCAR	status = VBSP_STATUS_CONTINUE; /* _hoops_GRHP _hoops_HHCPR _hoops_CCGR _hoops_SR _hoops_IGHIA _hoops_IAII */

	info->_hoops_GARIA._hoops_CRRIA++;

	if (!_hoops_SIPIA->bbox._hoops_RPCIR(env_info->bbox))
		return status;

	env_info = (_hoops_AHGIA *) info->_hoops_HSGIA;

	if (env_info->type != _hoops_RRPIA) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				"incorrect type encountered by test_face_cyl_callback");
		status = VBSP_STATUS_STOP; /* _hoops_ICPPA */
		return status;
	}

	info->_hoops_GARIA._hoops_SRRIA++;

	Cylinder *			c = env_info->c;
	_hoops_HRPA const *	matrix = env_info->matrix;

	if (matrix != null) {
		float _hoops_HGSRR[16];

		_hoops_PAGIA = _hoops_GCHIA;
		_hoops_GAIIA = _hoops_RCHIA;
		HI_Compute_Transformed_Points(2, (Point const *)c->axis, &matrix->elements[0][0], (Point *)_hoops_PAGIA);
		/* _hoops_IPS _hoops_RH _hoops_RSGA _hoops_PPR _hoops_PCHIA _hoops_RH _hoops_HCHIA _hoops_IHSR */
		COPY_MEMORY(matrix, 12*sizeof(float), _hoops_HGSRR);
		_hoops_HGSRR[12] = 0;
		_hoops_HGSRR[13] = 0;
		_hoops_HGSRR[14] = 0;
		_hoops_HGSRR[15] = 1;
		HI_Compute_Transformed_Points(2, (Point const *)&c->_hoops_CSPIR, _hoops_HGSRR, (Point *)_hoops_GAIIA);

		_hoops_GAIIA->axis[0] *= c->radius;
		_hoops_GAIIA->axis[1] *= c->radius;
	}
	else {
		_hoops_PAGIA = c->axis;
		_hoops_GAIIA = _hoops_RCHIA;
		_hoops_GAIIA->axis[0] = c->_hoops_CSPIR.axis[0] * c->radius;
		_hoops_GAIIA->axis[1] = c->_hoops_CSPIR.axis[1] * c->radius;
	}

	float _hoops_AIHIA = _hoops_SIPIA->plane * _hoops_PAGIA[0];

	radius = c->radius;
	state = (_hoops_AIHIA > radius ? 1 : (_hoops_AIHIA < -radius ? -1 : 0)); /* _hoops_ARRS, _hoops_CAPP, _hoops_PAR _hoops_IAGPR */
	_hoops_PIHIA = _hoops_AIHIA;
	_hoops_IIHIA = state;

	_hoops_AIHIA = _hoops_SIPIA->plane * _hoops_PAGIA[1];

	state = (_hoops_AIHIA > radius ? 1 : (_hoops_AIHIA < -radius ? -1 : 0)); /* _hoops_ARRS, _hoops_CAPP, _hoops_PAR _hoops_IAGPR */

	/* _hoops_RPP _hoops_III _hoops_ICSHR _hoops_ICHIA _hoops_IPPA, _hoops_PAR _hoops_RPP _hoops_SCGR _hoops_PAR _hoops_PGHC _hoops_PRHC _hoops_CHR _hoops_GGR, _hoops_GASAR _hoops_HHCPR _hoops_RGHP */
	if (_hoops_IIHIA != state || !_hoops_IIHIA || !state) {
		if (_hoops_RHHIA(
			(Point *)info->_hoops_SCGIA,
			_hoops_SIPIA,
			&_hoops_PAGIA[0],
			&_hoops_PAGIA[1],
			_hoops_GAIIA,
			_hoops_GAIIA,
			c->flags)) {
			/* _hoops_CIGAA, _hoops_PPR _hoops_GRHP _hoops_HHCPR _hoops_RPP _hoops_SR _hoops_SIPGR'_hoops_RA _hoops_GAPR _hoops_RHHR _hoops_RH _hoops_SAIPR */
			if (info->_hoops_ISGIA->Count() != info->_hoops_CSGIA) {
				info->_hoops_ISGIA->Append(info->_hoops_HSGIA);
				status = VBSP_STATUS_CONTINUE;
			}
			else
				status = VBSP_STATUS_STOP;
		}
	}

	return status;
}


/* _hoops_SASI _hoops_IS _hoops_HHCPR _hoops_GPRR _hoops_HCGIA. _hoops_GGR _hoops_GPSAR _hoops_SRSGR (_hoops_HAS._hoops_IAS. _hoops_SSSAR) */
local _hoops_CSCAR _hoops_RAIIA(void *ptr, void *user_data)
{
	global_compare_info *info = (global_compare_info *)user_data;
	_hoops_SHPPA *_hoops_SIPIA = (_hoops_SHPPA *)ptr;
	_hoops_PHGIA *env_info;
	_hoops_CSCAR status = VBSP_STATUS_CONTINUE;
	Point _hoops_CAHIA[_hoops_PSSHA];
	Point *p, *_hoops_AAIIA;
	Grid *grid;
	bool _hoops_CIHIA = false;

	env_info = (_hoops_PHGIA *) info->_hoops_HSGIA;
	grid = env_info->_hoops_IHGIA;
	if (env_info->type != _hoops_PRPIA) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				"incorrect type encountered by test_face_grid_callback");
		status = VBSP_STATUS_STOP; /* _hoops_ICPPA */
		goto _hoops_HPAGR;
	}
	if (!_hoops_HIPPA(
			info->_hoops_SCGIA,
			_hoops_SIPIA->len,
			_hoops_SIPIA->_hoops_GIPPA,
			env_info->_hoops_IHGIA->plane))
		goto _hoops_HPAGR;
	if (env_info->_hoops_HHGIA) {
		_hoops_CIHIA = true;
		goto _hoops_HPAGR;
	}
	else {
		_hoops_SHPPA _hoops_SAHIA;

		_hoops_SAHIA.type = _hoops_GPHIA;
		_hoops_SAHIA.flags = 0;
		_hoops_SAHIA.plane = grid->plane;
		_hoops_SAHIA._hoops_GIPPA = null;

		if (grid->_hoops_APIAA == _hoops_PPIAA) {
			int _hoops_PAIIA, _hoops_HAIIA;
			int _hoops_IAIIA, _hoops_CAIIA;
			/* _hoops_HHHR _hoops_RPR _hoops_AGSR _hoops_SGS _hoops_CAPS _hoops_HRGR _hoops_RPR*2 _hoops_AAIA, _hoops_CCA _hoops_RPR # _hoops_IIGR _hoops_SAIIA _hoops_GGR _hoops_GRR _hoops_HAGA */
			if (grid->count1 < 0) {
				_hoops_PAIIA = grid->count1;
				_hoops_HAIIA = -grid->count1;
			}
			else {
				_hoops_PAIIA = 0;
				_hoops_HAIIA = grid->count1;
			}
			if (grid->count2 < 0) {
				_hoops_IAIIA = grid->count2;
				_hoops_CAIIA = -grid->count2;
			}
			else {
				_hoops_IAIIA = 0;
				_hoops_CAIIA = grid->count1;
			}
			p = _hoops_CAHIA;
			p[0].x = grid->origin.x + _hoops_PAIIA * grid->_hoops_GGHI.x + _hoops_IAIIA * grid->_hoops_RGHI.x;
			p[0].y = grid->origin.y + _hoops_PAIIA * grid->_hoops_GGHI.y + _hoops_IAIIA * grid->_hoops_RGHI.y;
			p[0].z = grid->origin.z + _hoops_PAIIA * grid->_hoops_GGHI.z + _hoops_IAIIA * grid->_hoops_RGHI.z;

			p[1].x = grid->origin.x + _hoops_HAIIA   * grid->_hoops_GGHI.x + _hoops_IAIIA * grid->_hoops_RGHI.x;
			p[1].y = grid->origin.y + _hoops_HAIIA   * grid->_hoops_GGHI.y + _hoops_IAIIA * grid->_hoops_RGHI.y;
			p[1].z = grid->origin.z + _hoops_HAIIA   * grid->_hoops_GGHI.z + _hoops_IAIIA * grid->_hoops_RGHI.z;

			p[2].x = grid->origin.x + _hoops_HAIIA   * grid->_hoops_GGHI.x + _hoops_CAIIA * grid->_hoops_RGHI.x;
			p[2].y = grid->origin.y + _hoops_HAIIA   * grid->_hoops_GGHI.y + _hoops_CAIIA * grid->_hoops_RGHI.y;
			p[2].z = grid->origin.z + _hoops_HAIIA   * grid->_hoops_GGHI.z + _hoops_CAIIA * grid->_hoops_RGHI.z;

			p[3].x = grid->origin.x + _hoops_PAIIA * grid->_hoops_GGHI.x + _hoops_CAIIA * grid->_hoops_RGHI.x;
			p[3].y = grid->origin.y + _hoops_PAIIA * grid->_hoops_GGHI.y + _hoops_CAIIA * grid->_hoops_RGHI.y;
			p[3].z = grid->origin.z + _hoops_PAIIA * grid->_hoops_GGHI.z + _hoops_CAIIA * grid->_hoops_RGHI.z;

			_hoops_SAHIA.len = 4;
			if (_hoops_CRHIA(_hoops_SIPIA, info->_hoops_SCGIA, &_hoops_SAHIA, p)) {
				_hoops_CIHIA = true;
				goto _hoops_HPAGR;
			}
		}
		else {
			float start, end, _hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR, increment;
			int count1 = grid->count1;
			int count2 = grid->count2;
			bool _hoops_GPIIA = false;

			if (count2 == 0) {
				start = 0.0f;
				end = 360.0f;
				count2 = grid->_hoops_IPIAA - 1;
			}
			else if (count2 > 0) {
				start = 0.0f;
				if (count2 >= grid->_hoops_IPIAA) {
					end = 360.0f;
					count2 = grid->_hoops_IPIAA - 1;
				}
				else {
					end = count2 * 360.0f / grid->_hoops_IPIAA;
					_hoops_GPIIA = true;
				}
			}
			else {
				/* _hoops_HHHR _hoops_RPR _hoops_AGSR _hoops_SGS _hoops_CAPS _hoops_HRGR _hoops_RPR*2 _hoops_AAIA, _hoops_CCA _hoops_RPR # _hoops_IIGR _hoops_SAIIA _hoops_GGR _hoops_GRR _hoops_HAGA */
				count2 *= -2;
				if (count2 >= grid->_hoops_IPIAA) {
					start = 0.0f;
					end = 360.0f;
					count2 = grid->_hoops_IPIAA - 1;
				}
				else {
					end = count2 * 180.0f / grid->_hoops_IPIAA;
					start = -end;
					_hoops_GPIIA = true;
				}
			}

			_hoops_RAHCR = start;
			increment = (float)_hoops_ASSHA;
			p = _hoops_AAIIA = _hoops_CAHIA;
			do {
				_hoops_RICH (_hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR);
				p->x = grid->origin.x +
						 count1 * (_hoops_AGHCR * grid->_hoops_GGHI.x + _hoops_GGHCR * grid->_hoops_RGHI.x);
				p->y = grid->origin.y +
						 count1 * (_hoops_AGHCR * grid->_hoops_GGHI.y + _hoops_GGHCR * grid->_hoops_RGHI.y);
				p->z = grid->origin.z +
						 count1 * (_hoops_AGHCR * grid->_hoops_GGHI.z + _hoops_GGHCR * grid->_hoops_RGHI.z);
				++p;

				if (_hoops_RAHCR + increment >= 180) {
					_hoops_SAHIA.len = p - _hoops_AAIIA;
					if (_hoops_CRHIA(_hoops_SIPIA, info->_hoops_SCGIA, &_hoops_SAHIA, _hoops_AAIIA)) {
						_hoops_CIHIA = true;
						goto _hoops_HPAGR;
					}
					_hoops_AAIIA = p;
				}
			} _hoops_RGGA ((_hoops_RAHCR += increment) >= end);

			_hoops_RICH (end, _hoops_GGHCR, _hoops_AGHCR);
			p->x = grid->origin.x +
						count1 * (_hoops_AGHCR * grid->_hoops_GGHI.x + _hoops_GGHCR * grid->_hoops_RGHI.x);
			p->y = grid->origin.y +
						count1 * (_hoops_AGHCR * grid->_hoops_GGHI.y + _hoops_GGHCR * grid->_hoops_RGHI.y);
			p->z = grid->origin.z +
						count1 * (_hoops_AGHCR * grid->_hoops_GGHI.z + _hoops_GGHCR * grid->_hoops_RGHI.z);
			++p;

			if (_hoops_GPIIA) {
				p->x = grid->origin.x;
				p->y = grid->origin.y;
				p->z = grid->origin.z;
				++p;
			}

			_hoops_SAHIA.len = p - _hoops_AAIIA;
			if (_hoops_CRHIA(_hoops_SIPIA, info->_hoops_SCGIA, &_hoops_SAHIA, _hoops_AAIIA)) {
				_hoops_CIHIA = true;
				goto _hoops_HPAGR;
			}
		}
	}

  _hoops_HPAGR:
	if (_hoops_CIHIA) {
		if (info->_hoops_ISGIA->Count() != info->_hoops_CSGIA) {
			info->_hoops_ISGIA->Append(info->_hoops_HSGIA);
			status = VBSP_STATUS_CONTINUE;
		}
		else
			status = VBSP_STATUS_STOP;
	}
	return status;
} /* _hoops_RPIIA */



/* _hoops_SASI _hoops_IS _hoops_HHCPR _hoops_GPRR _hoops_HCGIA.  _hoops_GGR _hoops_GGSAR _hoops_SRSGR (_hoops_HAS._hoops_IAS. _hoops_HII _hoops_ACSAR*) */
local _hoops_CSCAR _hoops_APIIA(void *_hoops_HCSAR, void *_hoops_IASAR, void *_hoops_CASAR)
{
	global_compare_info *info = (global_compare_info *)_hoops_HCSAR;
	_hoops_SHPPA *_hoops_SIPIA = (_hoops_SHPPA *)_hoops_IASAR;

	UNREFERENCED(_hoops_CASAR);
	/* _hoops_SAHR _hoops_AASA _hoops_RHIR */
	return _hoops_RAIIA(_hoops_SIPIA, info);
} /* _hoops_PPIIA */




local const int _hoops_HPIIA[4] = {0, 1, 2, 3};

/* _hoops_SASI _hoops_IS _hoops_HHCPR _hoops_GPRR _hoops_HCGIA. _hoops_GGR _hoops_GPSAR _hoops_SRSGR (_hoops_HAS._hoops_IAS. _hoops_SSSAR) */
local _hoops_CSCAR _hoops_IPIIA(_hoops_HSSHA *_hoops_PAHHA, global_compare_info *info)
{

	_hoops_CSCAR			status = VBSP_STATUS_CONTINUE;
	_hoops_PHGIA *	env_info = (_hoops_PHGIA *) info->_hoops_HSGIA;
	Grid *				grid = env_info->_hoops_IHGIA;

	Point	_hoops_SPCIR;
	bool	_hoops_CIHIA = false;


/*	_hoops_RPP (!_hoops_CPIIA(
			_hoops_SIHC->_hoops_SPIIA,
			_hoops_GSPIA->_hoops_GHIIA,
			_hoops_GSPIA->_hoops_RHIIA,
			(_hoops_AIIC *)&_hoops_AHIIA->_hoops_PHIIA->_hoops_IPPA))
		_hoops_HHIIA _hoops_GGAS;
		*/

	if (env_info->_hoops_HHGIA) {
		_hoops_CIHIA = true;
		goto _hoops_HPAGR;
	}
	else {
		Point _hoops_CAHIA[_hoops_PSSHA];
		float t;

		_hoops_SHPPA _hoops_SAHIA;
		_hoops_SAHIA.type = _hoops_GPHIA;
		_hoops_SAHIA.flags = 0;
		_hoops_SAHIA.plane = grid->plane;

		_hoops_SAHIA._hoops_GIPPA = _hoops_HPIIA;

		if (grid->_hoops_APIAA == _hoops_PPIAA) {
			int _hoops_PAIIA, _hoops_HAIIA;
			int _hoops_IAIIA, _hoops_CAIIA;

			/* _hoops_HHHR _hoops_RPR _hoops_AGSR _hoops_SGS _hoops_CAPS _hoops_HRGR _hoops_RPR*2 _hoops_AAIA, _hoops_CCA _hoops_RPR # _hoops_IIGR _hoops_SAIIA _hoops_GGR _hoops_GRR _hoops_HAGA */
			if (grid->count1 < 0) {
				_hoops_PAIIA = grid->count1;
				_hoops_HAIIA = -grid->count1;
			}
			else {
				_hoops_PAIIA = 0;
				_hoops_HAIIA = grid->count1;
			}
			if (grid->count2 < 0) {
				_hoops_IAIIA = grid->count2;
				_hoops_CAIIA = -grid->count2;
			}
			else {
				_hoops_IAIIA = 0;
				_hoops_CAIIA = grid->count1;
			}

			Point *	p = _hoops_CAHIA;
			p[0].x = grid->origin.x + _hoops_PAIIA * grid->_hoops_GGHI.x + _hoops_IAIIA * grid->_hoops_RGHI.x;
			p[0].y = grid->origin.y + _hoops_PAIIA * grid->_hoops_GGHI.y + _hoops_IAIIA * grid->_hoops_RGHI.y;
			p[0].z = grid->origin.z + _hoops_PAIIA * grid->_hoops_GGHI.z + _hoops_IAIIA * grid->_hoops_RGHI.z;

			p[1].x = grid->origin.x + _hoops_HAIIA   * grid->_hoops_GGHI.x + _hoops_IAIIA * grid->_hoops_RGHI.x;
			p[1].y = grid->origin.y + _hoops_HAIIA   * grid->_hoops_GGHI.y + _hoops_IAIIA * grid->_hoops_RGHI.y;
			p[1].z = grid->origin.z + _hoops_HAIIA   * grid->_hoops_GGHI.z + _hoops_IAIIA * grid->_hoops_RGHI.z;

			p[2].x = grid->origin.x + _hoops_HAIIA   * grid->_hoops_GGHI.x + _hoops_CAIIA * grid->_hoops_RGHI.x;
			p[2].y = grid->origin.y + _hoops_HAIIA   * grid->_hoops_GGHI.y + _hoops_CAIIA * grid->_hoops_RGHI.y;
			p[2].z = grid->origin.z + _hoops_HAIIA   * grid->_hoops_GGHI.z + _hoops_CAIIA * grid->_hoops_RGHI.z;

			p[3].x = grid->origin.x + _hoops_PAIIA * grid->_hoops_GGHI.x + _hoops_CAIIA * grid->_hoops_RGHI.x;
			p[3].y = grid->origin.y + _hoops_PAIIA * grid->_hoops_GGHI.y + _hoops_CAIIA * grid->_hoops_RGHI.y;
			p[3].z = grid->origin.z + _hoops_PAIIA * grid->_hoops_GGHI.z + _hoops_CAIIA * grid->_hoops_RGHI.z;

			_hoops_SAHIA.bbox = _hoops_SASC(4, p);

			_hoops_SAHIA.len = 4;

 			if (_hoops_PPHHA(p, &_hoops_SAHIA,_hoops_PAHHA->start, _hoops_PAHHA->direction, &t, &_hoops_SPCIR)) {
 				_hoops_CIHIA = true;
				goto _hoops_HPAGR;
			}
		}
		else {
			float start, end, _hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR, increment;
			int count1 = grid->count1;
			int count2 = grid->count2;
			bool _hoops_GPIIA = false;

			if (count2 == 0) {
				start = 0.0f;
				end = 360.0f;
				count2 = grid->_hoops_IPIAA - 1;
			}
			else if (count2 > 0) {
				start = 0.0f;
				if (count2 >= grid->_hoops_IPIAA) {
					end = 360.0f;
					count2 = grid->_hoops_IPIAA - 1;
				}
				else {
					end = count2 * 360.0f / grid->_hoops_IPIAA;
					_hoops_GPIIA = true;
				}
			}
			else {
				/* _hoops_HHHR _hoops_RPR _hoops_AGSR _hoops_SGS _hoops_CAPS _hoops_HRGR _hoops_RPR*2 _hoops_AAIA, _hoops_CCA _hoops_RPR # _hoops_IIGR _hoops_SAIIA _hoops_GGR _hoops_GRR _hoops_HAGA */
				count2 *= -2;
				if (count2 >= grid->_hoops_IPIAA) {
					start = 0.0f;
					end = 360.0f;
					count2 = grid->_hoops_IPIAA - 1;
				}
				else {
					end = count2 * 180.0f / grid->_hoops_IPIAA;
					start = -end;
					_hoops_GPIIA = true;
				}
			}

			_hoops_RAHCR = start;
			increment = (float)_hoops_ASSHA;
			Point *	p = _hoops_CAHIA;
			Point *	_hoops_AAIIA = _hoops_CAHIA;
			do {
				_hoops_RICH (_hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR);
				p->x = grid->origin.x +
						 count1 * (_hoops_AGHCR * grid->_hoops_GGHI.x + _hoops_GGHCR * grid->_hoops_RGHI.x);
				p->y = grid->origin.y +
						 count1 * (_hoops_AGHCR * grid->_hoops_GGHI.y + _hoops_GGHCR * grid->_hoops_RGHI.y);
				p->z = grid->origin.z +
						 count1 * (_hoops_AGHCR * grid->_hoops_GGHI.z + _hoops_GGHCR * grid->_hoops_RGHI.z);
				++p;

				if (_hoops_RAHCR + increment >= 180) {
					_hoops_SAHIA.len = p - _hoops_AAIIA;
					if (_hoops_PPHHA(_hoops_AAIIA, &_hoops_SAHIA,_hoops_PAHHA->start, _hoops_PAHHA->direction, &t, &_hoops_SPCIR)) {
 						_hoops_CIHIA = true;
						goto _hoops_HPAGR;
					}
					_hoops_AAIIA = p;
				}
			} _hoops_RGGA ((_hoops_RAHCR += increment) >= end);

			_hoops_RICH (end, _hoops_GGHCR, _hoops_AGHCR);
			p->x = grid->origin.x +
						count1 * (_hoops_AGHCR * grid->_hoops_GGHI.x + _hoops_GGHCR * grid->_hoops_RGHI.x);
			p->y = grid->origin.y +
						count1 * (_hoops_AGHCR * grid->_hoops_GGHI.y + _hoops_GGHCR * grid->_hoops_RGHI.y);
			p->z = grid->origin.z +
						count1 * (_hoops_AGHCR * grid->_hoops_GGHI.z + _hoops_GGHCR * grid->_hoops_RGHI.z);
			++p;

			if (_hoops_GPIIA) {
				p->x = grid->origin.x;
				p->y = grid->origin.y;
				p->z = grid->origin.z;
				++p;
			}

			_hoops_SAHIA.len = p - _hoops_AAIIA;
			if (_hoops_PPHHA(_hoops_AAIIA, &_hoops_SAHIA,_hoops_PAHHA->start, _hoops_PAHHA->direction, &t, &_hoops_SPCIR)) {
 				_hoops_CIHIA = true;
				goto _hoops_HPAGR;
			}
		}
	}

  _hoops_HPAGR:

	if (_hoops_CIHIA) {
		if (info->_hoops_RGRIA &&
			(info->_hoops_RGRIA->Count() != info->_hoops_AGRIA)) {
			_hoops_RIGIA *sp;
			ALLOC(sp, _hoops_RIGIA);
			sp->x = _hoops_SPCIR.x;
			sp->y = _hoops_SPCIR.y;
			sp->z = _hoops_SPCIR.z;
			sp->_hoops_SSPAR = -1;
			info->_hoops_RGRIA->Append(sp);
		}
		/* _hoops_CIGAA, _hoops_PPR _hoops_GRHP _hoops_HHCPR _hoops_RPP _hoops_SR _hoops_SIPGR'_hoops_RA _hoops_GAPR _hoops_RHHR _hoops_RH _hoops_SAIPR */
		if (info->_hoops_ISGIA->Count() != info->_hoops_CSGIA) {
			info->_hoops_ISGIA->Append(info->_hoops_HSGIA);
			return VBSP_STATUS_CONTINUE;
		}
		else
			return VBSP_STATUS_STOP;
	}

	return status;
}










/* _hoops_CRSAR _hoops_IISA _hoops_HII _hoops_RH _hoops_IPHRA.  _hoops_SAHHA _hoops_PPR _hoops_SRSAR _hoops_RCPS _hoops_HII _hoops_GPHHA _hoops_IRGAA */
local _hoops_CSCAR _hoops_RPHHA(void *_hoops_HCSAR, void *_hoops_IASAR, void *_hoops_CASAR)
{
	global_compare_info *info = (global_compare_info *)_hoops_HCSAR;
	_hoops_SHPPA *target = (_hoops_SHPPA *)_hoops_IASAR;
	_hoops_HSSHA *_hoops_PAHHA = (_hoops_HSSHA *)_hoops_CASAR;
	_hoops_RAGIA *_hoops_IIAIA;
	int result;
	float t;

	_hoops_IIAIA = (_hoops_RAGIA *) info->_hoops_HSGIA;
	if (_hoops_IIAIA->_hoops_PAGIA == null && _hoops_IIAIA->type == _hoops_GGPIA)
		_hoops_IIPIA(_hoops_IIAIA);
	result = _hoops_PPHHA(
				(Point const *)_hoops_IIAIA->_hoops_PAGIA,
				target,
				_hoops_PAHHA->start,
				_hoops_PAHHA->direction,
				&t,0);
	if (result == _hoops_HPHHA || result == _hoops_IPHHA) {
		if (info->_hoops_RGRIA &&
			(info->_hoops_RGRIA->Count() != info->_hoops_AGRIA)) {
			_hoops_RIGIA *sp;
			ALLOC(sp, _hoops_RIGIA);
			sp->t = t;
			sp->x = _hoops_PAHHA->start->x + (t * _hoops_PAHHA->direction->x);
			sp->y = _hoops_PAHHA->start->y + (t * _hoops_PAHHA->direction->y);
			sp->z = _hoops_PAHHA->start->z + (t * _hoops_PAHHA->direction->z);
			sp->_hoops_SSPAR = target->index;
			info->_hoops_RGRIA->Append(sp);
		}
		/* _hoops_CIGAA, _hoops_PPR _hoops_GRHP _hoops_HHCPR _hoops_RPP _hoops_SR _hoops_SIPGR'_hoops_RA _hoops_GAPR _hoops_RHHR _hoops_RH _hoops_SAIPR */
		if (info->_hoops_ISGIA->Count() != info->_hoops_CSGIA) {
			info->_hoops_ISGIA->Append(info->_hoops_HSGIA);
			return VBSP_STATUS_CONTINUE;
		}
		else
			return VBSP_STATUS_STOP;
	}
	else
		return VBSP_STATUS_CONTINUE; /* _hoops_GRHP _hoops_HHCPR */
}


/* _hoops_CRSAR _hoops_IISA _hoops_HII _hoops_RH _hoops_IPHRA.  _hoops_SAHHA _hoops_PPR _hoops_SRSAR _hoops_RCPS _hoops_HII _hoops_GPHHA _hoops_IRGAA */
local _hoops_CSCAR _hoops_IHIIA(
	void *		_hoops_HCSAR,
	void *		_hoops_IASAR,
	void *		_hoops_CASAR)
{
	global_compare_info *	info = (global_compare_info *)_hoops_HCSAR;
	Geometry *				_hoops_GGHIA = (Geometry *)_hoops_IASAR;
	_hoops_HSSHA *					_hoops_PAHHA = (_hoops_HSSHA *)_hoops_CASAR;

	Point					_hoops_PIAI[_hoops_RSSHA+1];
	Point *					_hoops_PAGIA = _hoops_PIAI;
	int						point_count=0;

	_hoops_CSCAR				status = VBSP_STATUS_CONTINUE;

	Bounding				bounding;
	_hoops_ARPA					plane;

	_hoops_SHPPA _hoops_CHIIA;
	ZERO_STRUCT (&_hoops_CHIIA, _hoops_SHPPA);

	_hoops_HPGIA *	_hoops_IIAIA = (_hoops_HPGIA *) info->_hoops_HSGIA;
	_hoops_GGHIA = (Geometry *)_hoops_RCSSR (info->_hoops_RIGC, _hoops_IIAIA->key);
	if (_hoops_IIAIA->type != _hoops_PGPIA) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				"incorrect callback used in compute selection by shell");
		status = VBSP_STATUS_STOP; /* _hoops_ICPPA */
		return status;
	}

	HI_Figure_Geometry_Bounding(_hoops_GGHIA, bounding);
	_hoops_CHIIA.bbox = bounding->cuboid;
	if (_hoops_IIAIA->matrix != null && !_hoops_IIAIA->matrix->_hoops_PPGH())
		_hoops_CHIIA.bbox = _hoops_CHIIA.bbox._hoops_SCIS(*_hoops_IIAIA->matrix);

    if (_hoops_SSPIA(_hoops_GGHIA, _hoops_IIAIA->matrix,
		&point_count, &plane, &_hoops_PAGIA) != _hoops_CSPIA)
		return status;

	int _hoops_SHIIA [] = { 4, 0, 1, 2, 3 };
	int *face_list = _hoops_SHIIA;

	_hoops_CHIIA.type = _hoops_GPHIA;
	_hoops_CHIIA.len = point_count;
	_hoops_CHIIA.plane = plane;
	if (point_count > 4) {
		ALLOC_ARRAY (face_list, point_count + 1, int);
		for (int i = 0; i < point_count; i++)
			face_list[i+1] = i;
	}

	face_list[0] = point_count;
	_hoops_CHIIA._hoops_GIPPA = &face_list[1];

	float t;
	int result = _hoops_PPHHA(_hoops_PAGIA, &_hoops_CHIIA, _hoops_PAHHA->start, _hoops_PAHHA->direction, &t, 0);

	if (result == _hoops_HPHHA || result == _hoops_IPHHA) {
		if (info->_hoops_RGRIA &&
			(info->_hoops_RGRIA->Count() != info->_hoops_AGRIA)) {
			_hoops_RIGIA *sp;
			ALLOC(sp, _hoops_RIGIA);
			sp->t = t;
			sp->x = _hoops_PAHHA->start->x + (t * _hoops_PAHHA->direction->x);
			sp->y = _hoops_PAHHA->start->y + (t * _hoops_PAHHA->direction->y);
			sp->z = _hoops_PAHHA->start->z + (t * _hoops_PAHHA->direction->z);
			sp->_hoops_SSPAR = -1;
			info->_hoops_RGRIA->Append(sp);
		}
		/* _hoops_CIGAA, _hoops_PPR _hoops_GRHP _hoops_HHCPR _hoops_RPP _hoops_SR _hoops_SIPGR'_hoops_RA _hoops_GAPR _hoops_RHHR _hoops_RH _hoops_SAIPR */
		if (info->_hoops_ISGIA->Count() != info->_hoops_CSGIA)
			info->_hoops_ISGIA->Append(info->_hoops_HSGIA);

		_hoops_IIAIA->_hoops_CPGIA->Append(_hoops_GGHIA);
		status = VBSP_STATUS_CONTINUE;
	}

	if (_hoops_IIAIA->matrix != null &&
		_hoops_PAGIA != _hoops_PIAI) {
		FREE_ARRAY(_hoops_PAGIA, point_count, Point);
	}

	return status;
}


#define _hoops_PGHPA 32
local bool _hoops_GIIIA (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_RAGIA *			env_info,
	Polyhedron *				phon,
	Polyhedron **				victim = 0)
{
	Point *				points;
	_hoops_ARPA *				_hoops_RIIIA;
	int					_hoops_SSPAR;
	int i, j, _hoops_AIIIA;

	_hoops_SHPPA *		_hoops_RCHHR;
	int *vi, *fi;
	Tristrip *ts;
	int *_hoops_PIIIA;

	if (phon->type == _hoops_PRCP) {
		_hoops_APPGR *	surface = (_hoops_APPGR *)phon;
		_hoops_SPAGR			_hoops_RIIAA (surface->_hoops_RHAGR, _hoops_RIGC->thread_id);

		if (surface->_hoops_IPRI == null) {
			_hoops_AIIAA configs;
			HI_Fake_NURBS_Surface_Configs(&configs);
			HI_Tessellate_NURBS_Surface(_hoops_RIGC, surface, &configs);
		}
		phon = surface->_hoops_IPRI;
	}

	if (phon->type == _hoops_ASIP ||
		phon->type == _hoops_CSIP ||
		phon->type == _hoops_HSIP) {

		Shell *victim = 0;
		Shell *_hoops_SPHPR = (Shell *)_hoops_RCSSR (_hoops_RIGC, env_info->key);
		HI_Convert_To_Shell (_hoops_RIGC, null, (Geometry *)_hoops_SPHPR, &_hoops_SPHPR, &victim);

		phon = (Polyhedron *)_hoops_SPHPR;
		HI_Figure_Geometry_Bounding ((Geometry *)phon, phon->bounding); // _hoops_IRAP);
	}

	_hoops_HRPA const *	matrix = null;
	if (env_info->matrix &&
		!env_info->matrix->_hoops_PPGH())
		matrix = env_info->matrix;

	if (phon->face_count == 0)
		return false;

	_hoops_SASC bbox;
	if (_hoops_CSAIA(_hoops_RIGC, env_info->key, bbox) &&
		matrix != null)
		bbox = bbox._hoops_SCIS(*matrix);

	env_info->BSP = HI_New_BSP(HOOPS_WORLD->memory_pool, bbox, _hoops_PGHPA);
	env_info->phon = phon;
	env_info->flags |= _hoops_AGGIA;

	/* _hoops_RRP _hoops_IS _hoops_HSGIR _hoops_RPP _hoops_HSP _hoops_ASGA _hoops_GA'_hoops_RA _hoops_GAPR _hoops_GGCA */
	if (!BIT (phon->polyhedron_flags, _hoops_ASAHR) || !phon->local_face_attributes.normals)
		HI_Assemble_Face_Normals (phon);

	points = phon->points;
	if (matrix != null) {
		int				count = phon->face_count;
		_hoops_ARPA const *	_hoops_HIIIA = phon->local_face_attributes.normals;
		_hoops_ARPA *			_hoops_IIIIA;
		ALLOC_ARRAY(_hoops_IIIIA, count, _hoops_ARPA);
		HI_Compute_Transformed_Planes(count, _hoops_HIIIA, matrix, _hoops_IIIIA);
		env_info->_hoops_HAGIA = _hoops_IIIIA;
		env_info->flags |= _hoops_HGGIA;
	}
	else {
		env_info->_hoops_HAGIA = phon->local_face_attributes.normals;
		env_info->_hoops_PAGIA = phon->points;
	}
	_hoops_RIIIA = env_info->_hoops_HAGIA;

	if (phon->tristrips == null)
		HI_Assemble_3D_Tristrips (phon, 0xff, true);

	ts = phon->tristrips;
	while (ts != null) {
		vi = ts->_hoops_AIHA;
		fi = ts->face_indices;
		j = _hoops_AIIIA = 0;
		_hoops_SSPAR = -1;
		for (i = 0; i < ts->_hoops_PHHA; i++) {
			if (fi)
				fi += 2;
			if (ts->lengths[i] > 0) {
				_hoops_AIIIA += ts->lengths[i];
				while (j < _hoops_AIIIA - 2) {
					if (fi)
						_hoops_SSPAR = *fi++;
					else
						_hoops_SSPAR++;
					/* _hoops_PIP: _hoops_CIIIA _hoops_ISSC _hoops_CRGR _hoops_RH _hoops_GIGR _hoops_CRPR _hoops_HIRGR _hoops_RCSAR _hoops_RII _hoops_SCPH
					 * _hoops_IS _hoops_SHH _hoops_HPIPR, _hoops_HIH _hoops_SGS _hoops_PAHA'_hoops_RA _hoops_RPSHR _hoops_IH _hoops_AGCR _hoops_GCGC */
					_hoops_RCHHR = _hoops_SIIIA(0, 3, &vi[j], points, matrix, _hoops_RIIIA[_hoops_SSPAR], _hoops_SSPAR);
					HI_BSP_Insert(env_info->BSP, _hoops_RCHHR, null);
					j++;
				}
			}
			else {
				/* _hoops_RPP _hoops_GARI->_hoops_IHHA[_hoops_HAS] _hoops_HRGR _hoops_HHHR, _hoops_SR _hoops_CHR _hoops_CPSA _hoops_HCHAR _hoops_HPGR _hoops_IRS _hoops_SCPH _hoops_PRII, _hoops_HAR _hoops_IRS _hoops_CRHH */
				_hoops_AIIIA += -ts->lengths[i];
				while (j < _hoops_AIIIA - 2) {
					if (fi)
						_hoops_SSPAR = *fi++;
					else
						_hoops_SSPAR++;
					ALLOC_ARRAY(_hoops_PIIIA, 3, int);
					_hoops_PIIIA[0] = vi[0];
					_hoops_PIIIA[1] = vi[j+1];
					_hoops_PIIIA[2] = vi[j+2];
					_hoops_RCHHR = _hoops_SIIIA(_hoops_GCIIA, 3, _hoops_PIIIA, points, matrix, _hoops_RIIIA[_hoops_SSPAR], _hoops_SSPAR);
					HI_BSP_Insert(env_info->BSP, _hoops_RCHHR, null);
					_hoops_PIIIA = null;
				}
			}
			j = _hoops_AIIIA;
		}
		ts = ts->next;
	}
	if (victim) {
		*victim = phon;
		phon->_hoops_HIHI = 1;
	}
	return true;
}  /* _hoops_RSGR _hoops_API _hoops_RCIIA */



local bool _hoops_ACIIA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_RAGIA *		env_info,
	Polyhedron *			phon,
	bool				_hoops_PCIIA)
{

	_hoops_HRPA const *	matrix = null;
 	if (env_info->matrix && !env_info->matrix->_hoops_PPGH())
		matrix = env_info->matrix;

	if (phon->face_count == 0)
		return false;

	_hoops_SASC bbox;

	if (_hoops_PCIIA) {
		if (_hoops_CSAIA(_hoops_RIGC, env_info->key, bbox) &&
			matrix != null)
			bbox = bbox._hoops_SCIS(*matrix);

		env_info->BSP = HI_New_BSP(HOOPS_WORLD->memory_pool, bbox, _hoops_PGHPA);
		env_info->phon = phon;
		env_info->flags |= _hoops_AGGIA;
		return true;
	}

	/* _hoops_RRP _hoops_IS _hoops_HSGIR _hoops_RPP _hoops_HSP _hoops_ASGA _hoops_GA'_hoops_RA _hoops_GAPR _hoops_GGCA */
	if (!BIT (phon->polyhedron_flags, PHF_FACE_NORMALS_VALID))
		HI_Assemble_Face_Normals (phon);

	int *_hoops_GAHI, *end;
	_hoops_ARPA const *_hoops_RIIIA;
	int index;
	int i, j;
	int len;

	Point * points = phon->points;
	if (matrix != null) {
		_hoops_ARPA const *	_hoops_HIIIA;
		_hoops_ARPA *			_hoops_IIIIA;
		int				count;
		Point *			_hoops_SRHC;
		Point *			_hoops_SRPHA;
 		count = phon->face_count;
		_hoops_HIIIA = phon->local_face_attributes.normals;
		if (!env_info->_hoops_HAGIA)
			ALLOC_ARRAY(_hoops_IIIIA, count, _hoops_ARPA);
		else
			_hoops_IIIIA = env_info->_hoops_HAGIA;
		HI_Compute_Transformed_Planes(count, _hoops_HIIIA, matrix, _hoops_IIIIA);
		env_info->_hoops_HAGIA = _hoops_IIIIA;
		env_info->flags |= _hoops_HGGIA;
		count = phon->point_count;
		_hoops_SRHC = phon->points;
		if (!env_info->_hoops_PAGIA)
			ALLOC_ARRAY(_hoops_SRPHA, count, Point);
		else
			_hoops_SRPHA = env_info->_hoops_PAGIA;

		HI_Compute_Transformed_Points(count, _hoops_SRHC, &matrix->elements[0][0], _hoops_SRPHA);

		env_info->_hoops_PAGIA = _hoops_SRPHA;
		env_info->flags |= _hoops_IGGIA;
	}
	else {
		env_info->_hoops_PAGIA = phon->points;
		env_info->_hoops_HAGIA = phon->local_face_attributes.normals;
	}
	_hoops_RIIIA = env_info->_hoops_HAGIA;

	if (phon->type != _hoops_SCIP ||
		((Shell const *)phon)->face_list == null) {

		int const *vi, *fi;
		int *_hoops_PIIIA;
		_hoops_SHPPA *_hoops_RCHHR;
		Tristrip *ts;
		int _hoops_AIIIA;
		int face = -1;

		if (phon->tristrips == null)
			HI_Assemble_3D_Tristrips (phon, 0xff, true);

		ts = phon->tristrips;
		while (ts != null) {
			vi = ts->_hoops_AIHA;
			fi = ts->face_indices;
			j = _hoops_AIIIA = 0;
			for (i = 0; i < ts->_hoops_PHHA; i++) {
				/* _hoops_RPP _hoops_GARI->_hoops_IHHA[_hoops_HAS] _hoops_HRGR _hoops_HHHR, _hoops_SR _hoops_CHR _hoops_CPSA _hoops_HCHAR _hoops_HPGR _hoops_IRS _hoops_SCPH _hoops_PRII, _hoops_HAR _hoops_IRS _hoops_CRHH */
				if (fi) fi += 2;
				if (ts->lengths[i] > 0) {
					_hoops_AIIIA += ts->lengths[i];
					while (j < _hoops_AIIIA - 2) {
						if (fi)
							face = *fi++;
						else
							face++;
						/* _hoops_PIP: _hoops_CIIIA _hoops_ISSC _hoops_CRGR _hoops_RH _hoops_GIGR _hoops_CRPR _hoops_HIRGR _hoops_RCSAR _hoops_RII _hoops_SCPH
						 * _hoops_IS _hoops_SHH _hoops_HPIPR, _hoops_HIH _hoops_SGS _hoops_PAHA'_hoops_RA _hoops_RPSHR _hoops_IH _hoops_AGCR _hoops_GCGC */
						_hoops_RCHHR = _hoops_SIIIA(0, 3, &vi[j], points, matrix, _hoops_RIIIA[face], face);
						HI_BSP_Insert(env_info->BSP, _hoops_RCHHR, null);
						j++;
					}
				}
				else {
					_hoops_AIIIA += -ts->lengths[i];
					while (j < _hoops_AIIIA - 2) {
						if (fi)
							face = *fi++;
						else
							face++;

						ALLOC_ARRAY(_hoops_PIIIA, 3, int);
						_hoops_PIIIA[0] = vi[0];
						_hoops_PIIIA[1] = vi[j+1];
						_hoops_PIIIA[2] = vi[j+2];
						_hoops_RCHHR = _hoops_SIIIA(_hoops_GCIIA, 3, _hoops_PIIIA, points, matrix, _hoops_RIIIA[face], face);
						HI_BSP_Insert(env_info->BSP, _hoops_RCHHR, null);
						_hoops_PIIIA = null;
					}
				}
				j = _hoops_AIIIA;
			}
			ts = ts->next;
		}
	}
	else {
		Shell const *	_hoops_SPHPR = (Shell const *)phon;
		_hoops_SHPPA *face;
		_hoops_GAHI = _hoops_SPHPR->face_list;
		end = _hoops_GAHI + _hoops_SPHPR->face_list_length;
		index = 0;
		while (_hoops_GAHI < end) {
			/* _hoops_GA'_hoops_RA _hoops_IAIC _hoops_HHHR _hoops_RSSI (_hoops_HAS._hoops_IAS. _hoops_PCCPR _hoops_GGR _hoops_RSSI) */
			if (*_hoops_GAHI < 0) {
				_hoops_GAHI += -(*_hoops_GAHI) + 1;
				continue;
			}
			len = _hoops_GAHI[0];
			face = _hoops_SIIIA(0, len, &_hoops_GAHI[1], points, matrix, _hoops_RIIIA[index], index);
			HI_BSP_Insert(env_info->BSP, face, null);
			_hoops_GAHI += len + 1;
			index++;
		}
	}

	return true;
}




/* "_hoops_ISHI" _hoops_RSSA _hoops_IS _hoops_SPR _hoops_GPSPR _hoops_IIGR _hoops_CPAP.	 _hoops_HGI _hoops_API _hoops_RAGC _hoops_SCH _hoops_PPR
 * _hoops_HCR _hoops_IIGR _hoops_RGCI _hoops_HCIIA _hoops_GGR _hoops_IRS _hoops_CAGH _hoops_CRGR _hoops_IRS _hoops_IPHRA _hoops_IH _hoops_AGCRA _hoops_PPS */
local void _hoops_ICIIA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPGIA *	env_info,
	Geometry *				g)
{
	_hoops_CRCP *_hoops_SRCP = (_hoops_CRCP *)g->owner;

	if (_hoops_SRCP->type != _hoops_IRCP)
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					"Expected geometry owner to be a segment.");

	Bounding _hoops_CCIIA;
	Bounding _hoops_SCIIA;
	HI_Figure_Segment_Bounding(_hoops_SRCP, _hoops_CCIIA, _hoops_SCIIA);

	_hoops_HRPA const *	matrix = null;
	if (env_info->matrix && !env_info->matrix->_hoops_PPGH())
		matrix = env_info->matrix;

	_hoops_SASC bbox = _hoops_CCIIA->cuboid;
	if (matrix != null)
		bbox = bbox._hoops_SCIS (*matrix);

	env_info->BSP = HI_New_BSP(_hoops_RIGC->memory_pool, bbox, _hoops_PGHPA);
	env_info->_hoops_CPGIA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_IPGIA)(_hoops_RIGC->memory_pool);
	env_info->flags |= _hoops_AGGIA;

	g = _hoops_SRCP->geometry;
	/* _hoops_SIHA _hoops_HCR _hoops_IIGR _hoops_RH _hoops_CPAP _hoops_GGR _hoops_IRS _hoops_CAGH _hoops_CRGR _hoops_IRS _hoops_IPHRA. */
	while (g != null) {
		switch (g->type) {
			case _hoops_RCIP:
			case _hoops_SGCP:
			case _hoops_CGCP:
			case _hoops_GRCP:
			case _hoops_RRCP: {
				Bounding bounding;
				HI_Figure_Geometry_Bounding(g, bounding);
				_hoops_SASC bbox = bounding->cuboid;
				if (matrix != null)
					bbox = bbox._hoops_SCIS (*matrix);
				HI_BSP_Insert(env_info->BSP, g, &bbox);
			} break;
			default:
				break;
		}
		g = g->next;
	}
}


local void _hoops_GSIIA (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_GHGIA *	env_info,
	PolyCylinder *				_hoops_HSPIR)
{
	_hoops_HRPA const *	matrix = null;
	if (env_info->matrix && !env_info->matrix->_hoops_PPGH())
		matrix = env_info->matrix;

	env_info->flags |= _hoops_AGGIA;

	_hoops_SASC bbox;
	if (_hoops_CSAIA(_hoops_RIGC, env_info->key, bbox) &&
		matrix != null)
		bbox = bbox._hoops_SCIS(*matrix);

	env_info->BSP = HI_New_BSP(HOOPS_WORLD->memory_pool, bbox, _hoops_PGHPA);
	env_info->_hoops_HSPIR = _hoops_HSPIR;

	for (int i = 0; i < _hoops_HSPIR->point_count-1; i++) {
		float	len = 0.0f;
		float	width = 0.0f;
		int		j;

		for (j = i+1; j < _hoops_HSPIR->point_count-1; j++) {
			float _hoops_RSIIA = (_hoops_HSPIR->points[j] - _hoops_HSPIR->points[j+1]).length();
			float _hoops_ASIIA = _hoops_HSPIR->radii[i % _hoops_HSPIR->_hoops_ISPIR];

			if (_hoops_ASIIA > width)
				width = _hoops_ASIIA;

			if (len + _hoops_RSIIA > width)
				break;

			len += _hoops_RSIIA;
		}

		_hoops_RRHIA *	_hoops_PSIIA = _hoops_HSIIA(i, j, _hoops_HSPIR, matrix);
		HI_BSP_Insert(env_info->BSP, _hoops_PSIIA, null);
	}
}


local void _hoops_IPPIA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_PHGIA *		env_info,
	Grid *					g)
{
	Grid *					_hoops_ISIIA = env_info->_hoops_IHGIA;

	_hoops_HRPA const *	matrix = null;
	if (env_info->matrix && !env_info->matrix->_hoops_PPGH())
		matrix = env_info->matrix;

	if (!g->count1 || !g->count2)
		env_info->_hoops_HHGIA = true;
	else {
		if (_hoops_CSAIA(_hoops_RIGC, env_info->key, env_info->bbox) &&
			matrix != null)
			env_info->bbox = env_info->bbox._hoops_SCIS(*matrix);
	}

	COPY_MEMORY(g, sizeof(Grid), _hoops_ISIIA);

	if (matrix != null) {
		HI_Compute_Transformed_Points(1, &_hoops_ISIIA->origin, &matrix->elements[0][0], &_hoops_ISIIA->origin);
		HI_Compute_Transformed_Points(1, &_hoops_ISIIA->ref1, &matrix->elements[0][0], &_hoops_ISIIA->ref1);
		HI_Compute_Transformed_Points(1, &_hoops_ISIIA->ref2, &matrix->elements[0][0], &_hoops_ISIIA->ref2);
		HI_Compute_Transformed_Vectors(1, &_hoops_ISIIA->_hoops_GGHI, &matrix->elements[0][0], &_hoops_ISIIA->_hoops_GGHI);
		HI_Compute_Transformed_Vectors(1, &_hoops_ISIIA->_hoops_RGHI, &matrix->elements[0][0], &_hoops_ISIIA->_hoops_RGHI);
		HI_Compute_Transformed_Planes(1, &_hoops_ISIIA->plane, matrix, &_hoops_ISIIA->plane);
	}
}





local bool _hoops_CSIIA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CGGIA *			env_info)
{
	bool status = true;
	Geometry *g = (Geometry *) _hoops_RCSSR (_hoops_RIGC, env_info->key);

	if (g == null)
		return false;
	switch (g->type) {
		case _hoops_CSIP:
			_hoops_GSIIA(_hoops_RIGC,
				(_hoops_GHGIA *)env_info,
				(PolyCylinder *)g);
			break;
		case _hoops_SCIP:
		case _hoops_GSIP:
		case _hoops_PRCP:
			status = _hoops_GIIIA(
				_hoops_RIGC,
				(_hoops_RAGIA *)env_info,
				(Polyhedron *)g);
			break;
		case _hoops_HSIP:

			if (_hoops_CSAIA(_hoops_RIGC, env_info->key, env_info->bbox) &&
				env_info->matrix != null)
				env_info->bbox = env_info->bbox._hoops_SCIS(*env_info->matrix);

			((_hoops_RHGIA *)env_info)->s = (Sphere *)g;
			break;
		case _hoops_ASIP:

			if (_hoops_CSAIA(_hoops_RIGC, env_info->key, env_info->bbox) &&
				env_info->matrix != null)
				env_info->bbox = env_info->bbox._hoops_SCIS(*env_info->matrix);

			((_hoops_AHGIA *)env_info)->c = (Cylinder *)g;
			break;
		case _hoops_GGCP:
			_hoops_IPPIA(_hoops_RIGC,(_hoops_PHGIA *)env_info, (Grid *)g);
			break;
		case _hoops_RCIP:
		case _hoops_SGCP:
		case _hoops_CGCP:
		case _hoops_GRCP:
		case _hoops_RRCP:
			_hoops_ICIIA(_hoops_RIGC,(_hoops_HPGIA *)env_info, g);
			break;
		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					"unrecognized type in build_env_info, called from compute selection by shell");
			return false;
	}
	return status;
}




local void _hoops_SSIIA(
		_hoops_HSSHA *_hoops_PAHHA,
		global_compare_info *_hoops_SPPIA,
		_hoops_CGGIA *env_info)
{
	switch (env_info->type) {
		case _hoops_GGPIA: {
		case _hoops_RRPIA:
		case _hoops_IGPIA:
		case _hoops_SGPIA:
			HI_Test_BSP_Ray(
					((_hoops_RAGIA *)env_info)->BSP,
					_hoops_RPHHA,
					_hoops_SPPIA,
					_hoops_PAHHA,
					_hoops_PAHHA->start,
					_hoops_PAHHA->direction);
		} break;
		case _hoops_PGPIA: {
			HI_Test_BSP_Ray(
					((_hoops_HPGIA *)env_info)->BSP,
					_hoops_IHIIA,
					_hoops_SPPIA,
					_hoops_PAHHA,
					_hoops_PAHHA->start,
					_hoops_PAHHA->direction);
		} break;
		case _hoops_PRPIA:  {
			_hoops_IPIIA(_hoops_PAHHA, _hoops_SPPIA);
		} break;
		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					"Attempt to compare against unrecognized type in compute_selection_by_ray");
	}
}



local bool _hoops_GGCIA (
	_hoops_AIGPR *	_hoops_RIGC,
	global_compare_info *	_hoops_SPPIA,
	_hoops_HSSHA *					_hoops_PAHHA,
	_hoops_CGGIA *			env_info,
	_hoops_AIGIA *			_hoops_SIAI)
{
	bool status = true;
	Geometry *g = (Geometry *) _hoops_RCSSR (_hoops_RIGC, env_info->key);
	_hoops_RAGIA * _hoops_RGCIA;
	if (g == null)
		return false;
	switch (g->type) {
		case _hoops_ASIP:
		case _hoops_CSIP:
		case _hoops_HSIP: {
			Polyhedron *victim = null;
			_hoops_RGCIA = _hoops_SSAIA();
 			*((_hoops_CGGIA*)_hoops_RGCIA) = *((_hoops_CGGIA*)env_info);
			_hoops_RGCIA->type = _hoops_GGPIA;
			_hoops_SPPIA->_hoops_HSGIA = (_hoops_CGGIA *)_hoops_RGCIA;
			if (!BIT(env_info->flags,_hoops_AGGIA))
				status = _hoops_GIIIA(_hoops_RIGC,
					(_hoops_RAGIA *)_hoops_RGCIA,
					(Polyhedron *)g, &victim);
			_hoops_SSIIA(_hoops_PAHHA, _hoops_SPPIA, (_hoops_CGGIA *)_hoops_RGCIA);
			_hoops_SIAI->AddLast((_hoops_CGGIA *)_hoops_RGCIA);
			if (victim)
				_hoops_HPRH(victim);
  		}	break;
		case _hoops_SCIP:
		case _hoops_GSIP:
		case _hoops_PRCP:
			if (!BIT(env_info->flags,_hoops_AGGIA))
				status = _hoops_GIIIA(
					_hoops_RIGC,
					(_hoops_RAGIA *)env_info,
					(Polyhedron *)g);
			_hoops_SSIIA(_hoops_PAHHA, _hoops_SPPIA, (_hoops_CGGIA *)env_info);
			break;
		case _hoops_GGCP:
			if (!BIT(env_info->flags,_hoops_AGGIA))
				_hoops_IPPIA(_hoops_RIGC,
					(_hoops_PHGIA *)env_info,
					(Grid *)g);
			_hoops_SSIIA(_hoops_PAHHA, _hoops_SPPIA, (_hoops_CGGIA *)env_info);
			break;
		case _hoops_RCIP:
		case _hoops_SGCP:
		case _hoops_CGCP:
		case _hoops_GRCP:
		case _hoops_RRCP:
			if (!BIT(env_info->flags,_hoops_AGGIA))
				_hoops_ICIIA(_hoops_RIGC,(_hoops_HPGIA *)env_info, g);
			_hoops_SSIIA(_hoops_PAHHA, _hoops_SPPIA, (_hoops_CGGIA *)env_info);
			break;
		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					"unrecognized type in build_env_info, called from compute selection by shell");
			return false;
	}
	return status;
}


local void _hoops_AGCIA(
		VBSP *_hoops_ASGIA,
		global_compare_info *_hoops_SPPIA,
		_hoops_CGGIA *env_info,
		bool _hoops_SAGPR
 		)
{
	switch (env_info->type) {
		case _hoops_GGPIA: {
			if (!_hoops_SAGPR) {
				HI_Test_BSP_BSP(
					_hoops_ASGIA,
					_hoops_CIPIA,
					_hoops_SPPIA,
					((_hoops_RAGIA *)env_info)->BSP, false);
			}
			else {
				if (_hoops_ASGIA->_hoops_ICSAR)
					HI_Test_BSP_BSP(
						_hoops_ASGIA,
						_hoops_ASPIA,
						_hoops_SPPIA,
						((_hoops_RAGIA *)env_info)->BSP, true);
				else
					HI_Test_BSP_BSP(
						_hoops_ASGIA,
						_hoops_HCPIA,
						_hoops_SPPIA,
						((_hoops_RAGIA *)env_info)->BSP, true);
			}
		} break;
		case _hoops_PGPIA: {
			_hoops_HPGIA *_hoops_PGCIA = (_hoops_HPGIA *)env_info;
			HI_Test_BSP_BSP(
					_hoops_ASGIA,
					_hoops_HGHIA,
					_hoops_SPPIA,
					_hoops_PGCIA->BSP, false);
			if (_hoops_PGCIA->_hoops_CPGIA->Count() > 0 &&
				_hoops_SPPIA->_hoops_ISGIA->Count() != _hoops_SPPIA->_hoops_CSGIA)
					_hoops_SPPIA->_hoops_ISGIA->Append((_hoops_CGGIA*)_hoops_PGCIA);
		} break;
		case _hoops_IGPIA: {
			HI_Test_BSP_BSP(
					_hoops_ASGIA,
					_hoops_RIHIA,
					_hoops_SPPIA,
					((_hoops_GHGIA *)env_info)->BSP, false);
		} break;
		case _hoops_RRPIA: {
			if (!_hoops_SAGPR) {
				HI_Test_BSP(
						_hoops_ASGIA,
						_hoops_SRIIA,
						_hoops_SPPIA,
						env_info,
						env_info->bbox, _hoops_SAGPR);
			}
		} break;
		case _hoops_SGPIA: {
			if (!_hoops_SAGPR) {
				HI_Test_BSP(
						_hoops_ASGIA,
						_hoops_RRIIA,
						_hoops_SPPIA,
						env_info,
						env_info->bbox, _hoops_SAGPR);
			}
		} break;
		case _hoops_PRPIA: {
			if (!_hoops_SAGPR) {
				HI_Test_BSP(
						_hoops_ASGIA,
						_hoops_APIIA,
						_hoops_SPPIA,
						env_info,
						env_info->bbox, _hoops_SAGPR);
			}
		} break;
		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					"Attempt to compare against unrecognized type in compute selection by shell");
	}
}

local void _hoops_HGCIA(global_compare_info *info)
{
	info->_hoops_GARIA._hoops_IRRIA = 0;
	info->_hoops_GARIA._hoops_CRRIA = 0;
	info->_hoops_GARIA._hoops_SRRIA = 0;
}


local global_compare_info *_hoops_IGCIA(
	_hoops_AIGPR *	_hoops_RIGC)
{
	global_compare_info *_hoops_SPPIA;

	POOL_ZALLOC(_hoops_SPPIA, global_compare_info, _hoops_RIGC->memory_pool);
	_hoops_SPPIA->_hoops_CCGIA = -1;
	_hoops_HGCIA(_hoops_SPPIA);
	_hoops_SPPIA->_hoops_SGRIA= POOL_NEW(_hoops_RIGC->memory_pool, _hoops_CIGIA)(_hoops_RIGC->memory_pool, 64);
	return _hoops_SPPIA;
}




local void _hoops_CGCIA(_hoops_CHGIA *_hoops_SGCIA)
{
	_hoops_HRPIA(_hoops_SGCIA->_hoops_SHGIA);
	FREE(_hoops_SGCIA, _hoops_CHGIA);
}

local void _hoops_GRCIA(
	_hoops_CHGIA *info,
	Key _hoops_HCIS,
	void const * const _hoops_AGPAR)
{
 	_hoops_CGCIA(info);
	UNREFERENCED(_hoops_HCIS);
	UNREFERENCED(_hoops_AGPAR);
}
local void _hoops_RRCIA(global_compare_info *_hoops_SPPIA)
{
	int i;

	if (_hoops_SPPIA == null)
		return;
	if (_hoops_SPPIA->tree != null) {
		HI_BSP_Map_Function(_hoops_SPPIA->tree, _hoops_IAPIA, null);
		HI_Delete_BSP(_hoops_SPPIA->tree);
		_hoops_SPPIA->tree = null;
	}
	if (_hoops_SPPIA->_hoops_PGRIA != null) {
		_hoops_GCGIA *_hoops_ARCIA = _hoops_SPPIA->_hoops_PGRIA;
		for (i = 0; i < _hoops_ARCIA->Count(); i++)
			_hoops_IAPIA((*_hoops_ARCIA)[i], null);
		delete _hoops_ARCIA;
	}
	if (_hoops_SPPIA->_hoops_SGRIA) {
		_hoops_SPPIA->_hoops_SGRIA->MapFunction (_hoops_GRCIA, null);
		delete _hoops_SPPIA->_hoops_SGRIA;
	}
	FREE(_hoops_SPPIA, global_compare_info);
}


GLOBAL_FUNCTION void HI_Delete_Shell_Selection_Cache (void *_hoops_CSC)
{
	global_compare_info *_hoops_SPPIA = (global_compare_info *)_hoops_CSC;

	if (_hoops_SPPIA != null)
		_hoops_RRCIA(_hoops_SPPIA);
}

GLOBAL_FUNCTION void HI_Begin_Shell_Selection (
	_hoops_AIGPR	*_hoops_RIGC)
{
	if (_hoops_RIGC->_hoops_PRCIA != null)
		HI_Delete_Shell_Selection_Cache(_hoops_RIGC->_hoops_PRCIA);
	_hoops_RIGC->_hoops_PRCIA = _hoops_IGCIA(_hoops_RIGC);

	if (_hoops_RIGC->_hoops_HSIHA != null)
		HI_Delete_Point_Inside_Shell_Cache(_hoops_RIGC->_hoops_HSIHA);
	_hoops_RIGC->_hoops_HSIHA = HI_New_Point_Inside_Shell_Cache();
}

HC_INTERFACE void HC_Begin_Shell_Selection ()
{
	_hoops_PAPPR context("Begin_Shell_Selection");

	CODE_GENERATION (
		HI_Dump_Code ("HC_Begin_Shell_Selection ();\n");
	);

	HI_Begin_Shell_Selection (context);
}

GLOBAL_FUNCTION void HI_End_Shell_Selection (
	_hoops_AIGPR	*_hoops_RIGC)
{

	if (_hoops_RIGC->_hoops_PRCIA != null)
		HI_Delete_Shell_Selection_Cache(_hoops_RIGC->_hoops_PRCIA);
	_hoops_RIGC->_hoops_PRCIA = null;

	if (_hoops_RIGC->_hoops_HSIHA != null)
		HI_Delete_Point_Inside_Shell_Cache(_hoops_RIGC->_hoops_HSIHA);
	_hoops_RIGC->_hoops_HSIHA = null;
}

HC_INTERFACE void HC_End_Shell_Selection ()
{
	_hoops_PAPPR context("End_Shell_Selection");

	CODE_GENERATION (
		HI_Dump_Code ("HC_End_Shell_Selection ();\n");
	);

	HI_End_Shell_Selection (context);
}


local void _hoops_HRCIA(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CGGIA *			env_info,
	char *					pathname)
{
	/* _hoops_PCAI:
	"/_hoops_GCIS _hoops_GIRPR/_hoops_IRCIA/_hoops_CRCIA/@805b6c40 <<< /_hoops_RHPP/_hoops_SRCIA/_hoops_GACIA+0/_hoops_HIRA" */
	_hoops_IRGIA *			path = env_info->path;
	Key const *			path_keys = &(*path)[0];
	_hoops_CRCP const *		_hoops_IGRPR = null;
	_hoops_PGRPR const *		inc;

	Key	key, _hoops_RACIA;
	key = _hoops_RACIA = HI_Show_Owner_Key_By_Key (_hoops_RIGC, env_info->key, true, true);

	_hoops_CRCP const *includee = (_hoops_CRCP const *) _hoops_RCSSR (_hoops_RIGC, _hoops_RACIA);

	char * ptr = pathname;
	HI_Return_Sprintf1 (ptr, -1, "%p", (void *)includee);
	ptr += strlen(ptr);

	int	_hoops_AACIA = 0;

	for (int i = 1; i < path->Count(); i++) {
		key = path_keys[i];

		if (key >= 0)
			key = HI_Show_Owner_Key_By_Key (_hoops_RIGC, _hoops_RACIA, true, true);

		_hoops_HPAH const * thing = (_hoops_HPAH const *) _hoops_RCSSR (_hoops_RIGC, key);

		if (thing->type == _hoops_AGRPR) {
			strcat(ptr, " <");
			while (_hoops_AACIA > 0) {
				strcat(ptr, "<");
				_hoops_AACIA--;
 				includee = includee->owner;
			}
 			/* _hoops_RH _hoops_HSPR _hoops_RRGR _hoops_SIHR _hoops_IRS _hoops_GRH _hoops_AGIR _hoops_CAS _hoops_RH _hoops_PACIA _hoops_CPAP
			 * _hoops_CSAP _hoops_RIPPR _hoops_ISHP _hoops_SPR _hoops_CAGH _hoops_PAPA (_hoops_IAS._hoops_ISHI. _hoops_HPP _hoops_HACIA _hoops_IH _hoops_IACIA */
			inc = (_hoops_PGRPR const *) _hoops_RCSSR (_hoops_RIGC, key);
			_hoops_IGRPR = (_hoops_CRCP const *) (inc->_hoops_IGRPR);

			if (includee != _hoops_IGRPR &&
				includee->owner == _hoops_IGRPR)
				strcat(ptr, "<");
			strcat(ptr, " ");
			ptr += strlen(ptr);

			Key owner = HI_Show_Owner_Key_By_Key (_hoops_RIGC, key, true, false);

			_hoops_CRCP const *_hoops_CACIA = (_hoops_CRCP const *) _hoops_RCSSR (_hoops_RIGC, owner);
			HI_Return_Sprintf1 (ptr, -1, "%p", (void *)_hoops_CACIA);
			ptr += strlen(ptr);

			includee = (_hoops_CRCP const *) _hoops_RCSSR (_hoops_RIGC, owner);
 			ptr += strlen(ptr);
			_hoops_AACIA = -1;
		}
		else
			_hoops_AACIA++;

		_hoops_RACIA = key;
	}
}


local int _hoops_SACIA(
	_hoops_AIGPR *	_hoops_RIGC,
	const char *			action,
	_hoops_CGGIA const *		env_info)
{
	char result[32];
	int _hoops_APPIA = 0;
	_hoops_IRGIA const * path = env_info->path;
	Key const * path_keys = &(*path)[0];

	PUSHNAME(_hoops_RIGC);
	HC_PShow_One_Net_Selectability(path->Count(), path_keys, "faces", result);
	if (strstr(result, action))
		_hoops_APPIA = 1;
	/* _hoops_RPP _hoops_RH _hoops_ACPH _hoops_PPPIA _hoops_HPPIA, _hoops_HIH _hoops_PSP '!', _hoops_SR _hoops_PHHR _hoops_HPP _hoops_HPRC */
	if (_hoops_APPIA && !strchr(result, '!')) {
		HC_PShow_One_Net_Visibility(path->Count(), path_keys, "faces", result);
		if (_hoops_AGGR(result, "off"))
			_hoops_APPIA = 0;
	}
	POPNAME(_hoops_RIGC);
	return _hoops_APPIA;
}


local global_compare_info *	_hoops_GPCIA(
	_hoops_AIGPR *	_hoops_RIGC,
	Key						_hoops_RPCIA,
	_hoops_GCGIA *		_hoops_APCIA)
{
	global_compare_info *_hoops_SPPIA;

	if (_hoops_RIGC->_hoops_PRCIA != null) {
		_hoops_SPPIA = (global_compare_info *) _hoops_RIGC->_hoops_PRCIA;
		_hoops_HGCIA(_hoops_SPPIA);
		if (_hoops_SPPIA->_hoops_CCGIA != -1 &&
			_hoops_SPPIA->_hoops_CCGIA != _hoops_RPCIA) {
			/* _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_GRP _hoops_RH _hoops_PSHR _hoops_HSPP _hoops_CAGH _hoops_GAR _hoops_ARPP.  _hoops_PIHA _hoops_PIAGR _hoops_HII _hoops_SI */
			_hoops_RRCIA(_hoops_SPPIA);
			_hoops_RIGC->_hoops_PRCIA = _hoops_SPPIA = _hoops_IGCIA(_hoops_RIGC);
			_hoops_SPPIA->_hoops_CCGIA = _hoops_RPCIA;
		}
	}
	else
		_hoops_SPPIA = _hoops_IGCIA(_hoops_RIGC);

	_hoops_SPPIA->_hoops_RIGC = _hoops_RIGC;
	/* _hoops_SHSP _hoops_PPCIA _hoops_HPCIA _hoops_IH _hoops_HA, _hoops_SR _hoops_GHCA _hoops_RRP _hoops_IS _hoops_GHIS _hoops_ARPP _hoops_SR _hoops_PAH _hoops_RGSP */
	_hoops_SPPIA->_hoops_AGRIA = -1;


	/* _hoops_IPCIA _hoops_RHI _hoops_IPHRA _hoops_RPP _hoops_SCH _hoops_CCACR'_hoops_RA _hoops_AIAH _hoops_RPII _hoops_CPHR */
	if (!_hoops_SPPIA->tree) {
		_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)_hoops_RCSSR (_hoops_SPPIA->_hoops_RIGC, _hoops_RPCIA);
		ASSERT(_hoops_SRCP->type == _hoops_IRCP);

		_hoops_SASC _hoops_CPCIA;

		if (!_hoops_SRCP->bounding._hoops_HICAR())
			_hoops_CPCIA = _hoops_SRCP->bounding->cuboid;
		else {
			Bounding _hoops_HSRIR;
			HI_Figure_Segment_Bounding(_hoops_SRCP, _hoops_SRCP->bounding, _hoops_HSRIR);
		}

		_hoops_SPPIA->tree = HI_New_BSP(HOOPS_WORLD->memory_pool, _hoops_CPCIA, _hoops_PGHPA);
		_hoops_AIPIA(_hoops_RIGC, _hoops_RPCIA, _hoops_SPPIA);

		_hoops_SPPIA->_hoops_CCGIA = _hoops_RPCIA;
	}

	_hoops_SPPIA->_hoops_ISGIA = _hoops_APCIA;
	_hoops_SPPIA->_hoops_CSGIA = -1;
	_hoops_SPPIA->_hoops_RRRIA = -2.0f;
	return _hoops_SPPIA;
}



local global_compare_info *_hoops_SPCIA(
	_hoops_AIGPR *	_hoops_RIGC,
	Key						_hoops_RPCIA,
	_hoops_AIGIA *			_hoops_GHCIA)
{
	global_compare_info *_hoops_SPPIA;

	if (_hoops_RIGC->_hoops_PRCIA != null) {
		_hoops_SPPIA = (global_compare_info *) _hoops_RIGC->_hoops_PRCIA;
		_hoops_HGCIA(_hoops_SPPIA);
		if (_hoops_SPPIA->_hoops_CCGIA != -1 &&
			_hoops_SPPIA->_hoops_CCGIA != _hoops_RPCIA) {
			/* _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_GRP _hoops_RH _hoops_PSHR _hoops_HSPP _hoops_CAGH _hoops_GAR _hoops_ARPP.  _hoops_PIHA _hoops_PIAGR _hoops_HII _hoops_SI */
			_hoops_RRCIA(_hoops_SPPIA);
			_hoops_RIGC->_hoops_PRCIA = _hoops_SPPIA = _hoops_IGCIA(_hoops_RIGC);
			_hoops_SPPIA->_hoops_CCGIA = _hoops_RPCIA;
		}
	}
	else
		_hoops_SPPIA = _hoops_IGCIA(_hoops_RIGC);

	_hoops_SPPIA->_hoops_RIGC = _hoops_RIGC;

	/* _hoops_IPCIA _hoops_RHI _hoops_IPHRA _hoops_RPP _hoops_SCH _hoops_CCACR'_hoops_RA _hoops_AIAH _hoops_RPII _hoops_CPHR */
	if (!_hoops_SPPIA->tree) {
		_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)_hoops_RCSSR (_hoops_SPPIA->_hoops_RIGC, _hoops_RPCIA);
		ASSERT(_hoops_SRCP->type == _hoops_IRCP);

		_hoops_SASC _hoops_CPCIA;

		if (!_hoops_SRCP->bounding._hoops_HICAR())
			_hoops_CPCIA = _hoops_SRCP->bounding->cuboid;
		else {
			Bounding _hoops_HSRIR;
			HI_Figure_Segment_Bounding(_hoops_SRCP, _hoops_SRCP->bounding, _hoops_HSRIR);
		}

		_hoops_SPPIA->tree = HI_New_BSP(HOOPS_WORLD->memory_pool, _hoops_CPCIA, _hoops_PGHPA);
		_hoops_AIPIA(_hoops_RIGC, _hoops_RPCIA, _hoops_SPPIA);

		_hoops_SPPIA->_hoops_CCGIA = _hoops_RPCIA;
	}

	_hoops_SPPIA->_hoops_RIGC = _hoops_RIGC;
 	_hoops_SPPIA->_hoops_SSGIA = _hoops_GHCIA;

	return _hoops_SPPIA;
}


local Key _hoops_RHCIA(_hoops_HPGIA *_hoops_PGCIA)
{
	Geometry *g;
	g = _hoops_PGCIA->_hoops_CPGIA->Pop();
	return g->key;
}


struct _hoops_AHCIA {
	_hoops_GCGIA *keys;
	_hoops_RCGIA *_hoops_SIAIR;
};

#define QS_TYPE				struct _hoops_AHCIA *
#define QS_VAL(thing,a)		(*(thing)->_hoops_SIAIR)[a]->t
#define QS_COMPARE(f1,f2)	(f1>f2)	/* _hoops_GHIS _hoops_GACPR */
#define QS_SWAP(thing,a,b) {		\
	Swap ((*(thing)->keys)[a], (*(thing)->keys)[b]); \
	Swap ((*(thing)->_hoops_SIAIR)[a], (*(thing)->_hoops_SIAIR)[b]); \
}
#include "utility/hqsort.h"


local void _hoops_PHCIA(
	_hoops_AIGPR *			_hoops_RIGC,
	_hoops_GCGIA *				_hoops_HHCIA,
	_hoops_RCGIA *	_hoops_IHCIA,
	char const *					start_seg)
{
	float x, y, z, t;
	float _hoops_CHCIA =0, _hoops_SHCIA = 0, _hoops_GICIA = 0;
	int i, j;
	char pathname[4096];
	char _hoops_RICIA[64];
	Key _hoops_AICIA;
	_hoops_CGGIA *env_info;
	_hoops_RIGIA *sp;

	int _hoops_PICIA = -1;

	_hoops_GHAIR *	_hoops_GIGC;

	int _hoops_HICIA = _hoops_IICIA;

	_hoops_HPAH const *	_hoops_CICIA = (_hoops_HPAH const *)HI_One_Segment_Search (_hoops_RIGC, start_seg, true);

	if (_hoops_CICIA != null) {
		if ((_hoops_GIGC = (_hoops_GHAIR *)HI_Find_Net_Attribute (_hoops_RIGC, _hoops_CICIA, HK_HEURISTICS)) != null) {
			if (BIT (_hoops_GIGC->mask&_hoops_GIGC->value, _hoops_SICIA))
				_hoops_HICIA = _hoops_GIGC->_hoops_GCCIA;
			_hoops_HPRH(_hoops_GIGC);
		}
	}

	ASSERT(_hoops_HICIA >= 0);

	if (_hoops_IHCIA) {
		struct _hoops_AHCIA _hoops_RCCIA;
		_hoops_RCCIA.keys = _hoops_HHCIA;
		_hoops_RCCIA._hoops_SIAIR = _hoops_IHCIA;
		quick_sort(&_hoops_RCCIA, 0, _hoops_HHCIA->Count()-1);
	}


	/* _hoops_IRHH _hoops_PCIAR _hoops_IIGR _hoops_ACCIA.	 _hoops_PCCIA _hoops_RH _hoops_HIGR _hoops_HPIPR _hoops_HIS _hoops_SGS _hoops_SR _hoops_PAH _hoops_CIGAA _hoops_IS _hoops_RH _hoops_RSGR */
	for (i = _hoops_HHCIA->Count() - 1; i >= 0; i--) {
		env_info = (*_hoops_HHCIA)[i];
		if (env_info->type == _hoops_PGPIA) {
			_hoops_HPGIA *_hoops_PGCIA = (_hoops_HPGIA *)env_info;
			for (j = 1; j < _hoops_PGCIA->_hoops_CPGIA->Count(); j++)
				_hoops_HHCIA->Append((_hoops_CGGIA *)_hoops_PGCIA);
		}
	}

	env_info = (*_hoops_HHCIA)[0];
	if (env_info->type == _hoops_PGPIA)
		_hoops_AICIA = _hoops_RHCIA((_hoops_HPGIA *)env_info);
	else
		_hoops_AICIA = env_info->key;
	if (_hoops_IHCIA) {
		sp = (*_hoops_IHCIA)[0];
		x = sp->x;
		y = sp->y;
		z = sp->z;
		_hoops_GICIA = sp->t;
		_hoops_PICIA = sp->_hoops_SSPAR;
	}
	else
		x = y = z = t = 0;
	_hoops_HRCIA(_hoops_RIGC, env_info, pathname);

	if (env_info->type == _hoops_GGPIA) {
 		if (((_hoops_RAGIA *)env_info)->_hoops_IAGIA) {
			_hoops_CHCIA = ((_hoops_RAGIA *)env_info)->_hoops_CAGIA.x;
			_hoops_SHCIA = ((_hoops_RAGIA *)env_info)->_hoops_CAGIA.y;
			_hoops_GICIA = ((_hoops_RAGIA *)env_info)->_hoops_CAGIA.z;
			_hoops_PICIA = ((_hoops_RAGIA *)env_info)->_hoops_IAGIA->index;
		}
	}

	HI_Queue_Selection_Event(
		_hoops_RIGC,
		"",		/* _hoops_HCCIA */
		"",		/* _hoops_AIRI */
		"v",	/* _hoops_ACPH */
		0,				/* _hoops_HSAGA */
		pathname,		/* _hoops_ICCIA */
		_hoops_AICIA,		/* _hoops_SIC */
		-1, -1, _hoops_PICIA, /* _hoops_CCCIA, _hoops_SCCIA, _hoops_GSCIA */
		x, y, z,		/* _hoops_RPPS _hoops_SGGPR */
		_hoops_CHCIA, _hoops_SHCIA, _hoops_GICIA,			/* _hoops_SARA _hoops_SGGPR */
		0
	);

	for (i = 1; i < _hoops_HHCIA->Count() && i < _hoops_HICIA; i++) {
 		_hoops_CHCIA = _hoops_SHCIA = _hoops_GICIA = 0;
		x = y = z = 0;
		env_info = (*_hoops_HHCIA)[i];
 		if (env_info->type == _hoops_PGPIA)
			_hoops_AICIA = _hoops_RHCIA((_hoops_HPGIA *)env_info);
		else
			_hoops_AICIA = env_info->key;
		if (_hoops_IHCIA && i < _hoops_IHCIA->Count()) {
			sp = (*_hoops_IHCIA)[i];
			x = sp->x;
			y = sp->y;
			z = sp->z;
			_hoops_GICIA = sp->t;
		}
		_hoops_HRCIA(_hoops_RIGC, env_info, pathname);

		if (env_info->type == _hoops_GGPIA) {
			if (((_hoops_RAGIA *)env_info)->_hoops_IAGIA) {
				_hoops_CHCIA = ((_hoops_RAGIA *)env_info)->_hoops_CAGIA.x;
				_hoops_SHCIA = ((_hoops_RAGIA *)env_info)->_hoops_CAGIA.y;
				_hoops_GICIA = ((_hoops_RAGIA *)env_info)->_hoops_CAGIA.z;
				_hoops_PICIA = ((_hoops_RAGIA *)env_info)->_hoops_IAGIA->index;
			}
			else
				_hoops_PICIA = -1;
		}
		HI_Queue_Related_Selection(
			_hoops_RIGC,
			pathname,	/* _hoops_ICCIA */
			_hoops_AICIA,	/* _hoops_SIC */
			_hoops_PICIA, 0, 0,	/* _hoops_CCCIA, _hoops_SCCIA, _hoops_GSCIA */
			x, y, z,	/* _hoops_RPPS _hoops_SGGPR */
			_hoops_CHCIA, _hoops_SHCIA,_hoops_GICIA		/* _hoops_SARA _hoops_SGGPR */
		);
	}

	HI_Await_Event (_hoops_RIGC, _hoops_RICIA, -1);
}



local void _hoops_RSCIA(
	_hoops_IHSAR *			_hoops_ASCIA,
	Vector const &		_hoops_SHHCR)
{

	if (_hoops_ASCIA->_hoops_PAIS && _hoops_ASCIA->_hoops_PAIS->used) {
		for (int i=0; i<_hoops_ASCIA->_hoops_PAIS->used; i++) {
			_hoops_SHPPA * face = (_hoops_SHPPA *)_hoops_ASCIA->_hoops_PAIS->items[i];
			face->bbox.min += _hoops_SHHCR;
			face->bbox.max += _hoops_SHHCR;
			float _hoops_ISSPA = _hoops_SHHCR._hoops_SSRP(Vector(face->plane));
			face->plane.d -= _hoops_ISSPA;
		}
	}

	if (_hoops_ASCIA->_hoops_AISAR) {
		for (int i=0; i<_hoops_ASCIA->_hoops_AISAR; i++) {
			_hoops_SHPPA * face = (_hoops_SHPPA *)_hoops_ASCIA->_hoops_RAGR[i];
			face->bbox.min += _hoops_SHHCR;
			face->bbox.max += _hoops_SHHCR;
			float _hoops_ISSPA = _hoops_SHHCR._hoops_SSRP(Vector(face->plane));
			face->plane.d -= _hoops_ISSPA;
		}
	}

	if (_hoops_ASCIA->kids[0])
		_hoops_RSCIA(_hoops_ASCIA->kids[0], _hoops_SHHCR);
	if (_hoops_ASCIA->kids[1])
		_hoops_RSCIA(_hoops_ASCIA->kids[1], _hoops_SHHCR);
	if (_hoops_ASCIA->kids[2])
		_hoops_RSCIA(_hoops_ASCIA->kids[2], _hoops_SHHCR);
}


local void _hoops_PSCIA(
	VBSP *			tree,
	Vector const &	_hoops_SHHCR,
	bool			_hoops_PCIIA)
{
	if (_hoops_PCIIA) {
		tree->bbox.min += _hoops_SHHCR;
		tree->bbox.max += _hoops_SHHCR;
	}
	else
		_hoops_RSCIA(tree->root, _hoops_SHHCR);
}



#define _hoops_HSCIA(a,b,_hoops_ISCIA) ((fabs((a)-(b))<(_hoops_ISCIA)))

local _hoops_RAGIA * _hoops_CSCIA(
	global_compare_info *	info,
	Key						key,
	float const *			matrix,
	bool					_hoops_PCIIA)
 {
	Geometry *			g;
	_hoops_RAGIA *	_hoops_SHGIA;
	_hoops_CHGIA *	_hoops_SGCIA = 0;

	if (info)
		info->_hoops_SGRIA->LookupItem(key, &_hoops_SGCIA);

	if (!_hoops_SGCIA) {
		ZALLOC(_hoops_SGCIA, _hoops_CHGIA);
		if (!matrix)
			HI_Compute_Identity_Matrix(&_hoops_SGCIA->matrix.elements[0][0]);
		else
			HI_Figure_General_Modelling_Mtx (matrix, &_hoops_SGCIA->matrix);
		info->_hoops_SGRIA->InsertItem(key, _hoops_SGCIA);
	}

	_hoops_SHGIA = _hoops_SGCIA->_hoops_SHGIA;

	if (!_hoops_SHGIA) {
		_hoops_SHGIA =_hoops_SSAIA();
		g = (Geometry *) _hoops_RCSSR (info->_hoops_RIGC, key);
		_hoops_SHGIA->key = key;

		ZALLOC(_hoops_SHGIA->matrix, _hoops_HRPA);
		if (!matrix)
			HI_Compute_Identity_Matrix(&_hoops_SHGIA->matrix->elements[0][0]);
		else
			HI_Figure_General_Modelling_Mtx (matrix, _hoops_SHGIA->matrix);

		_hoops_ACIIA (info->_hoops_RIGC, _hoops_SHGIA, (Polyhedron *)g, _hoops_PCIIA);
		_hoops_SGCIA->_hoops_SHGIA = _hoops_SHGIA;
	}
	else {
		bool _hoops_SSCIA = true;

 		_hoops_HRPA mat;

		if (!matrix)
			HI_Compute_Identity_Matrix(&mat.elements[0][0]);
		else
			HI_Figure_General_Modelling_Mtx (matrix, &mat);

		for (int i=0; i<11; i++) {
			if (!_hoops_HSCIA(((float*)mat.elements)[i], ((float*)_hoops_SGCIA->matrix.elements)[i], 1e-6f)) {
				_hoops_SSCIA = false;
				break;
			}
		}

		if (!_hoops_SSCIA) {
			g = (Geometry *) _hoops_RCSSR (info->_hoops_RIGC, key);
			_hoops_HRPIA(_hoops_SHGIA);
			_hoops_SHGIA = _hoops_SSAIA();
			_hoops_SHGIA->key = key;
			ZALLOC(_hoops_SHGIA->matrix, _hoops_HRPA);
			HI_Figure_General_Modelling_Mtx (matrix, _hoops_SHGIA->matrix);
			HI_Figure_General_Modelling_Mtx (matrix, &_hoops_SGCIA->matrix);
			_hoops_ACIIA (info->_hoops_RIGC, _hoops_SHGIA, (Polyhedron *)g, _hoops_PCIIA);
			_hoops_SGCIA->_hoops_GIGIA = !_hoops_PCIIA;
			_hoops_SGCIA->_hoops_SHGIA = _hoops_SHGIA;
		}
		else {
			Point _hoops_SHHCR(0,0,0);
			Point _hoops_IHAS(0,0,0);

			HI_Compute_Transformed_Points(1, &_hoops_SHHCR, &_hoops_SGCIA->matrix.elements[0][0], &_hoops_SHHCR);
			HI_Compute_Transformed_Points(1, &_hoops_IHAS, &mat.elements[0][0], &_hoops_IHAS);

			Vector delta = _hoops_IHAS - _hoops_SHHCR;

			_hoops_PSCIA(_hoops_SHGIA->BSP, delta, _hoops_PCIIA);

			if (_hoops_PCIIA)
				return _hoops_SGCIA->_hoops_SHGIA;

			if (!_hoops_SGCIA->_hoops_GIGIA) {
				g = (Geometry *) _hoops_RCSSR (info->_hoops_RIGC, key);
 				_hoops_ACIIA (info->_hoops_RIGC, _hoops_SHGIA,(Polyhedron *)g, false);
			}

			_hoops_SGCIA->_hoops_GIGIA = true;

			for (int i=0; i<_hoops_SHGIA->phon->point_count; i++)
				_hoops_SHGIA->_hoops_PAGIA[i] += delta;

			_hoops_SGCIA->matrix = mat;
		}
	}

	return 	_hoops_SGCIA->_hoops_SHGIA;
 }



HC_INTERFACE int HC_Compute_Selection_By_Key (
	char const *	action,
	char const *	start_seg,
	Key				key,
	float const	*	_hoops_CASPA)
{
	_hoops_PAPPR context("Compute_Selection_By_Key");

	CODE_GENERATION (
		HI_Dump_Code ("HC_Compute_Selection_By_Key (");
		HI_Dump_Code (Sprintf_SS (null, "%S, %S,", action, start_seg));
		HI_Dump_Code (Sprintf_LD (null, "LOOKUP (%D), ", key));
		if (_hoops_CASPA) {
			for (int i = 0; i < 16; i += 4) {
				HI_Dump_Code (_hoops_CHCHR (null, "matrix[%d] = %f; ", i, _hoops_CASPA[i]));
				HI_Dump_Code (_hoops_CHCHR (null, "matrix[%d] = %f; ", i+1, _hoops_CASPA[i+1]));
				HI_Dump_Code (_hoops_CHCHR (null, "matrix[%d] = %f; ", i+2, _hoops_CASPA[i+2]));
				HI_Dump_Code (_hoops_CHCHR (null, "matrix[%d] = %f;\n", i+3, _hoops_CASPA[i+3]));
			}
			HI_Dump_Code ("matrix");
		}
		else {
			HI_Dump_Code ("0");
		}
		HI_Dump_Code (");\n");
	);

	if (start_seg == null || *start_seg == '\0') {
		HE_ERROR (HEC_SYNTAX, HES_NULL_INPUT, "Blank or null segment specification");
		return 0;
	}

	if (_hoops_CASPA == null) {
		HE_ERROR (HEC_SYNTAX, HES_NULL_INPUT, "Null matrix specification");
		return 0;
	}

	int _hoops_PPIHA = 0;

	_hoops_CSPPR();
	_hoops_CRCP *	_hoops_SRCP;
	if ((_hoops_SRCP = HI_One_Segment_Search (context, start_seg, true)) != null) {
		_hoops_CGGIA *env_info = null;

		Key	_hoops_RPCIA = _hoops_SRCP->key;

 		_hoops_GCGIA *		_hoops_APCIA = POOL_NEW(context->memory_pool, _hoops_GCGIA)(context->memory_pool);
		global_compare_info *	_hoops_SPPIA = _hoops_GPCIA(context, _hoops_RPCIA, _hoops_APCIA);
		_hoops_RAGIA *		_hoops_SGCIA = _hoops_CSCIA(_hoops_SPPIA, key, _hoops_CASPA, true);

		Polyhedron *	g = (Polyhedron *) _hoops_RCSSR (context, key);

 		/* _hoops_AA _hoops_IRS _hoops_HHCI _hoops_IASC _hoops_AHCRR _hoops_RPGP _hoops_IS _hoops_GGSIA _hoops_HIGR _hoops_IIGR _hoops_RGSIA */
		HI_Test_BSP (_hoops_SPPIA->tree, _hoops_PCAIA, _hoops_SPPIA,
					 (void*)&_hoops_SGCIA->BSP->bbox, _hoops_SGCIA->BSP->bbox, false);

		if (!_hoops_SPPIA->_hoops_ISGIA->Count() && !_hoops_SPPIA->_hoops_PGRIA) {
			_hoops_CSCIA (_hoops_SPPIA, key, _hoops_CASPA, false);
		}
		else {
			/* _hoops_IH _hoops_GRR _hoops_IIGR _hoops_RH _hoops_SCHS _hoops_SGS _hoops_AIPAA _hoops_RH _hoops_ARRS _hoops_RPGP, _hoops_AA _hoops_IRS _hoops_RRI _hoops_CICAR _hoops_ISPR
			 * _hoops_HPP _hoops_CIHH _hoops_RSSI _hoops_ACSRR _hoops_GHC _hoops_PPR _hoops_RPP _hoops_SGS _hoops_IIAH, _hoops_HSSC _hoops_ISSC _hoops_IS _hoops_PCCP (_hoops_IHPH)
			 * _hoops_CCCI _hoops_HSSP _hoops_IS _hoops_HSSP _hoops_RPGP */
			_hoops_SGCIA = _hoops_CSCIA (_hoops_SPPIA, key, _hoops_CASPA, false);

			VBSP *	_hoops_ASGIA = _hoops_SGCIA->BSP;
 			if (_hoops_SGCIA->_hoops_PAGIA)
				_hoops_SPPIA->_hoops_SCGIA = _hoops_SGCIA->_hoops_PAGIA;
			else
				_hoops_SPPIA->_hoops_SCGIA = g->points;

  			_hoops_SPPIA->_hoops_RSGIA = ((Shell const *)_hoops_SGCIA->phon)->face_list;
			_hoops_SPPIA->_hoops_ASGIA = _hoops_ASGIA;
			_hoops_GCGIA * _hoops_AGSIA = POOL_NEW(context->memory_pool, _hoops_GCGIA)(context->memory_pool);
			_hoops_SPPIA->_hoops_ISGIA = _hoops_AGSIA;
			_hoops_SPPIA->_hoops_CSGIA = 1;

			_hoops_GCGIA * _hoops_HHCIA = POOL_NEW(context->memory_pool, _hoops_GCGIA)(context->memory_pool);
			for (int i = 0; i < _hoops_APCIA->Count(); i++) {
				env_info = (*_hoops_APCIA)[i];
				if (_hoops_SACIA(context, action, env_info)) {
					_hoops_SPPIA->_hoops_HSGIA = env_info;
 					if (!(env_info->flags & _hoops_AGGIA))
						if (!_hoops_CSIIA(context, env_info))
							continue;
					_hoops_AGCIA(_hoops_ASGIA, _hoops_SPPIA, env_info, false);
					if (_hoops_AGSIA->Count()) {
						/* _hoops_RPP _hoops_IIH _hoops_CSAP _hoops_IRS _hoops_RHHR, _hoops_IHIS _hoops_SCH _hoops_IS _hoops_RH _hoops_HACH _hoops_PCGIA */
						_hoops_HHCIA->Append((*_hoops_AGSIA)[0]);
						_hoops_AGSIA->SetCount(0);
					}
				}
			}

			if (_hoops_HHCIA->Count() > 0) {
				_hoops_PHCIA(context, _hoops_HHCIA, null, start_seg);
				_hoops_PPIHA = _hoops_HHCIA->Count();
			}


			if (_hoops_AGSIA != null)
				delete _hoops_AGSIA;

			if (_hoops_HHCIA != null)
				delete _hoops_HHCIA;
		}

		if (_hoops_APCIA != null)
			delete _hoops_APCIA;

 		if (context->_hoops_PRCIA == null)
			_hoops_RRCIA(_hoops_SPPIA);
	}
	_hoops_IRRPR();

	return _hoops_PPIHA;
}




#define _hoops_IRGPA			0x1
#define _hoops_PGSIA			0x2

#define _hoops_HGSIA		0x3
#define _hoops_IGSIA	0x4



local const _hoops_IGRCR _hoops_RPGAA[] = {
	{_hoops_HGSIA,		_hoops_GRRCR ("left"),				_hoops_RRRCR, 0, false},
	{_hoops_IGSIA,		_hoops_GRRCR ("right"),				_hoops_RRRCR, 0, false},
};


local const _hoops_HPAGA _hoops_CGSIA = {
	_hoops_GGAPR (_hoops_RPGAA),			_hoops_RPGAA,
};


local const _hoops_IGRCR _hoops_SGSIA[] = {
	{_hoops_IRGPA, _hoops_GRRCR ("tolerance"), _hoops_SPPCR, 1, false},
	{_hoops_PGSIA,_hoops_GRRCR ("handedness"),	_hoops_GHAGA, -999, false,&_hoops_CGSIA},

  };

local const _hoops_HPAGA _hoops_GRSIA = {
	_hoops_GGAPR (_hoops_SGSIA),
	_hoops_SGSIA,
};



struct _hoops_RRSIA {
	float	tolerance;
	bool    _hoops_ARSIA;
};

local bool _hoops_PRSIA (
	_hoops_AIGPR *				_hoops_RIGC,
	char const *						option_string,
	struct _hoops_RRSIA *	_hoops_SHGAA)
{
	/* _hoops_ARP _hoops_SHIR _hoops_HSH _hoops_IH _hoops_HCR _hoops_IIGR _hoops_RH _hoops_GIGAA */
	_hoops_SHGAA->tolerance = -2;
	_hoops_SHGAA->_hoops_ARSIA = true;

 	if (option_string == null)
		return false;

	_hoops_HIACR (_hoops_HRSIA, _hoops_SGSIA);

	Option_Value *	option_list = null;
	Option_Value *	option;

	if (!HI_Parse_Options (_hoops_RIGC, option_string, _hoops_CIACR (_hoops_HRSIA), &option_list, _hoops_SIACR))
		return false;


	if ((option = option_list) != null) do {
		switch (option->type->id) {
		  case _hoops_PGSIA:
				if (option->value.option_list->type->id == _hoops_IGSIA)
 					_hoops_SHGAA->_hoops_ARSIA =  false;
		   break;
		  case _hoops_IRGPA: {
			  	  _hoops_SHGAA->tolerance = option->value._hoops_PIPCR[0];
		  }	  break;
		}
	} while ((option = option->next) != null);

	HI_Free_Option_List (_hoops_RIGC, option_list);
	return true;
}





struct _hoops_PIPHA{
	int *		_hoops_HCGPA;
	int			_hoops_HIPHA;
	int			_hoops_ICGH;
};


local void _hoops_IIPHA (
	void *						info,
	Integer32				_hoops_HAPH,
	Integer32				_hoops_ISPI,
	Integer32				_hoops_CSPI,
	Integer32				_hoops_SSPI) {
	struct _hoops_PIPHA *			data = (struct _hoops_PIPHA *)info;

	UNREFERENCED (_hoops_HAPH);

	/* _hoops_RPP _hoops_CRPR _hoops_PRCH _hoops_GRS _hoops_SHH _hoops_CIPHA, _hoops_SIPHA */
	if (data->_hoops_HIPHA + 4 >= data->_hoops_ICGH) {
		/* _hoops_GRHP _hoops_IHGC _hoops_IIGR _hoops_RHGS _hoops_PIH, _hoops_CCPP _hoops_CCAH _hoops_PPGS, _hoops_IPS _hoops_PPGS _hoops_IAPR, _hoops_CIH _hoops_RHGS _hoops_PIH */
		int *	_hoops_IRSIA = data->_hoops_HCGPA;
		int		_hoops_CIGRR = data->_hoops_ICGH;
		data->_hoops_ICGH *= 2;
		ALLOC_ARRAY_CACHED(data->_hoops_HCGPA, data->_hoops_ICGH, int);
		_hoops_AIGA (_hoops_IRSIA, _hoops_CIGRR, int, data->_hoops_HCGPA);
		FREE_ARRAY(_hoops_IRSIA, _hoops_CIGRR, int);
	}

	data->_hoops_HCGPA[data->_hoops_HIPHA] = 3;
	data->_hoops_HCGPA[data->_hoops_HIPHA+1] = _hoops_ISPI;
	data->_hoops_HCGPA[data->_hoops_HIPHA+2] = _hoops_CSPI;
	data->_hoops_HCGPA[data->_hoops_HIPHA+3] = _hoops_SSPI;

	data->_hoops_HIPHA += 4;
}




local void _hoops_CRSIA(
	_hoops_AIGPR *	_hoops_RIGC,
	Point const *			points,
	int						face_list_length,
	int const *				face_list,
	int **					new_face_list,
	int *					_hoops_PAAHA,
	int *					_hoops_SRSIA)
{
	if (face_list_length == 0) {
		*new_face_list = null;
		*_hoops_PAAHA = 0;
		*_hoops_SRSIA = 0;
		return;
	}

	_hoops_PIPHA	data;
	data._hoops_HIPHA = 0;
	data._hoops_ICGH = face_list_length * 4;
	POOL_ALLOC_ARRAY_CACHED(data._hoops_HCGPA, data._hoops_ICGH, int, _hoops_RIGC->memory_pool);

	int *		in_face_list = (int *)face_list;
	int const *	global_end = face_list + face_list_length;

	do {
		bool _hoops_ICGIR = false;
		int const *				_hoops_CRRHR = in_face_list + 1 + *in_face_list;

		/* _hoops_HSGR _hoops_ISGR _hoops_ARAH-_hoops_RSSI */
		while (_hoops_CRRHR != global_end && *_hoops_CRRHR < 0) {
			_hoops_CRRHR += 1 - *_hoops_CRRHR;
			_hoops_ICGIR =true;
		}

		if (*in_face_list == 3 || *in_face_list == 4 && !_hoops_ICGIR) {
			int len = *in_face_list;
			/* _hoops_RPP _hoops_CRPR _hoops_PRCH _hoops_GRS _hoops_SHH _hoops_CIPHA, _hoops_SIPHA */
			if (data._hoops_HIPHA + len + 1 >= data._hoops_ICGH) {
				/* _hoops_GRHP _hoops_IHGC _hoops_IIGR _hoops_RHGS _hoops_PIH, _hoops_CCPP _hoops_CCAH _hoops_PPGS, _hoops_IPS _hoops_PPGS _hoops_IAPR, _hoops_CIH _hoops_RHGS _hoops_PIH */
				int *	_hoops_IRSIA = data._hoops_HCGPA;
				int		_hoops_GASIA = data._hoops_ICGH;
				data._hoops_ICGH *= 2;
				POOL_ALLOC_ARRAY(data._hoops_HCGPA, data._hoops_ICGH, int, _hoops_RIGC->memory_pool);
				_hoops_AIGA (_hoops_IRSIA, _hoops_GASIA, int, data._hoops_HCGPA);
				FREE_ARRAY(_hoops_IRSIA, _hoops_GASIA, int);
			}
 			for (int i=0; i<=len; i++)
				data._hoops_HCGPA[data._hoops_HIPHA+i] = in_face_list[i];
			data._hoops_HIPHA+=len+1;
		}
		else
			HI_Triangulate_Face(points,null,in_face_list,_hoops_CRRHR, _hoops_IIPHA,&data);

		in_face_list = (int *)_hoops_CRRHR;
	} while (in_face_list != global_end);



	*_hoops_PAAHA = data._hoops_HIPHA;
	*_hoops_SRSIA = data._hoops_ICGH;
	*new_face_list = data._hoops_HCGPA;
}





static int _hoops_RASIA (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			action,
	char const *			start_seg,
	int						point_count,
	Point const *			points,
	int						face_list_length,
	int const *				face_list,
	const char *			options,
	_hoops_SASC *			_hoops_HRRIA = 0)
{

	if (start_seg == null || *start_seg == '\0') {
		HE_ERROR (HEC_SYNTAX, HES_NULL_INPUT, "Blank or null segment specification");
		return 0;
	}

	_hoops_GCGIA *_hoops_APCIA = null, *_hoops_AGSIA = null, *_hoops_HHCIA = null;
	VBSP *_hoops_ASGIA = null;
	bool _hoops_AASIA = false;
	int _hoops_PPIHA = 0;
	global_compare_info *_hoops_SPPIA = null;
	_hoops_CGGIA *env_info = null;

	bool  _hoops_PASIA = false;

	_hoops_CSPPR();
	_hoops_CRCP *	_hoops_SRCP;
	if ((_hoops_SRCP = HI_One_Segment_Search (_hoops_RIGC, start_seg, true)) == null) {
		_hoops_IRRPR();
		return 0;
	}
	Key		_hoops_RPCIA = _hoops_SRCP->key;

	int *	new_face_list = 0;
	int		_hoops_PAAHA;
	int		_hoops_SRSIA;

	Point *		_hoops_HASIA = null;
	int *		_hoops_IASIA = null;
	Vector *	normals = null;

	int _hoops_CASIA = 0;
	int _hoops_SASIA = 0;
	int _hoops_GPSIA = 0;

	_hoops_CRSIA(_hoops_RIGC, points, face_list_length, face_list, 
		&new_face_list, &_hoops_PAAHA, &_hoops_SRSIA);

	face_list = new_face_list;
	face_list_length = _hoops_PAAHA;

	struct _hoops_RRSIA	config;
	_hoops_PRSIA(_hoops_RIGC, options, &config);

	_hoops_APCIA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_GCGIA)(_hoops_RIGC->memory_pool);
	_hoops_SPPIA = _hoops_GPCIA(_hoops_RIGC, _hoops_RPCIA, _hoops_APCIA);
	_hoops_SPPIA->_hoops_PRRIA = config._hoops_ARSIA;
	_hoops_SPPIA->_hoops_HRRIA = _hoops_HRRIA;
 	/* _hoops_AA _hoops_IRS _hoops_HHCI _hoops_IASC _hoops_AHCRR _hoops_RPGP _hoops_IS _hoops_GGSIA _hoops_HIGR _hoops_IIGR _hoops_RGSIA */
	_hoops_SASC _hoops_RPSIA = _hoops_SASC(point_count, points);

	Vector delta = _hoops_RPSIA.max - _hoops_RPSIA.min;

	_hoops_SPPIA->_hoops_CGRIA = delta.length();

	HI_Test_BSP (_hoops_SPPIA->tree, _hoops_PCAIA, _hoops_SPPIA, (void*)&_hoops_RPSIA, _hoops_RPSIA, false);

	if (!_hoops_SPPIA->_hoops_ISGIA->Count() && !_hoops_SPPIA->_hoops_PGRIA)
		goto done; /* _hoops_RSIH _hoops_PGPCR _hoops_RPP _hoops_IIH'_hoops_GRI _hoops_ISAP _hoops_RAAP _hoops_IS _hoops_AA. */

	/* _hoops_IH _hoops_GRR _hoops_IIGR _hoops_RH _hoops_SCHS _hoops_SGS _hoops_AIPAA _hoops_RH _hoops_ARRS _hoops_RPGP, _hoops_AA _hoops_IRS _hoops_RRI _hoops_CICAR _hoops_ISPR
	 * _hoops_HPP _hoops_CIHH _hoops_RSSI _hoops_ACSRR _hoops_GHC _hoops_PPR _hoops_RPP _hoops_SGS _hoops_IIAH, _hoops_HSSC _hoops_ISSC _hoops_IS _hoops_PCCP (_hoops_IHPH)
	 * _hoops_CCCI _hoops_HSSP _hoops_IS _hoops_HSSP _hoops_RPGP */

	if (config.tolerance > 0 || config.tolerance == -1) {
		_hoops_PASIA = true;

		_hoops_GPSIA = point_count;
		ALLOC_ARRAY_CACHED(_hoops_HASIA, _hoops_GPSIA, Point);

		_hoops_SASIA = face_list_length;
		ALLOC_ARRAY_CACHED(_hoops_IASIA, _hoops_SASIA, int);

		_hoops_SPPIA->_hoops_GRRIA = true;

		if (config.tolerance >=0)
 			_hoops_SPPIA->_hoops_RRRIA = config.tolerance;
		else
			_hoops_SPPIA->_hoops_RRRIA = _hoops_SPPIA->_hoops_CGRIA / 20.0f;

		int	_hoops_APSIA = 0;
		int _hoops_PPSIA = 0;

		HI_Compute_Optimized_Shell(_hoops_RIGC,
			point_count, points, 0,
			face_list_length,face_list,"",
			&_hoops_PPSIA,_hoops_HASIA,
			&_hoops_APSIA,
			_hoops_IASIA,0,0);


		_hoops_CASIA = _hoops_PPSIA;
		ZALLOC_ARRAY_CACHED(normals, _hoops_CASIA, Vector);

		int *_hoops_GPGIR = _hoops_IASIA + _hoops_APSIA;
		int *_hoops_HPSIA = _hoops_IASIA;
		int _hoops_SAGIR;
 		_hoops_ARPA _hoops_HRAHR;
		while (_hoops_HPSIA < _hoops_GPGIR) {
			_hoops_SAGIR = *_hoops_HPSIA;

			_hoops_APHIA(_hoops_HASIA,_hoops_SAGIR, _hoops_HPSIA+1, false, &_hoops_HRAHR);

			/* _hoops_GGR _hoops_RH _hoops_AGIR _hoops_IIGR _hoops_HHHR _hoops_RSSI, _hoops_RGR _hoops_HAPR _hoops_PPPPR'_hoops_RA _hoops_SSSS */
			for (int i = 1; i <= _hoops_SAGIR; i++) {
				int vertex = *(_hoops_HPSIA + i);
				normals[vertex] += Vector(_hoops_HRAHR);
			}

			_hoops_HPSIA += _hoops_SAGIR + 1;
		}
		HI_Normalize_Vectors (_hoops_PPSIA, normals);
		points = _hoops_HASIA;
		point_count = _hoops_PPSIA;
		face_list_length = _hoops_APSIA;
		face_list = _hoops_IASIA;
		_hoops_SPPIA->_hoops_GSGIA = normals;
	}
	else {
 		_hoops_SPPIA->_hoops_GRRIA = false;
		_hoops_SPPIA->_hoops_RRRIA = config.tolerance;
	}


	_hoops_ASGIA = HI_New_BSP(HOOPS_WORLD->memory_pool, _hoops_RPSIA, _hoops_PGHPA);
	_hoops_SPPIA->_hoops_SCGIA = points;
 	_hoops_SPPIA->_hoops_RSGIA = face_list;
	_hoops_SPPIA->_hoops_ASGIA = _hoops_ASGIA;

	_hoops_AGSIA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_GCGIA)(_hoops_RIGC->memory_pool);
	_hoops_SPPIA->_hoops_ISGIA = _hoops_AGSIA;
	if (!_hoops_HRRIA)
		_hoops_SPPIA->_hoops_CSGIA = 1;

	_hoops_HHCIA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_GCGIA)(_hoops_RIGC->memory_pool);
	for (int i = 0; i < _hoops_APCIA->Count(); i++) {
		env_info = (*_hoops_APCIA)[i];
		if (_hoops_SACIA(_hoops_RIGC, action, env_info)) {
			_hoops_SPPIA->_hoops_HSGIA = env_info;
			if (!_hoops_AASIA) {
				_hoops_GAHPA(_hoops_ASGIA, point_count, points, face_list_length, face_list, !_hoops_SPPIA->_hoops_ARRIA);
				_hoops_AASIA = true;
			}
			if (!(env_info->flags & _hoops_AGGIA))
				if (!_hoops_CSIIA(_hoops_RIGC, env_info))
					continue;
			if (_hoops_PASIA) {
				int _hoops_CIHIA = 0;
				for (int i=0; i<2; i++) {
					_hoops_AGSIA->SetCount(0);
					_hoops_AGCIA(_hoops_ASGIA, _hoops_SPPIA, env_info, false);
					_hoops_SPPIA->_hoops_RRRIA = - _hoops_SPPIA->_hoops_RRRIA;
					if (_hoops_AGSIA->Count())
						_hoops_CIHIA++;
					else
						break;
				}
				if (_hoops_CIHIA == 2) {
					/* _hoops_RPP _hoops_IIH _hoops_CSAP _hoops_IRS _hoops_RHHR, _hoops_IHIS _hoops_SCH _hoops_IS _hoops_RH _hoops_HACH _hoops_PCGIA */
 					_hoops_HHCIA->Append((*_hoops_AGSIA)[0]);
					_hoops_AGSIA->SetCount(0);
				}
				else
					_hoops_AGSIA->SetCount(0);
			}
			else {
				_hoops_AGCIA(_hoops_ASGIA, _hoops_SPPIA, env_info, false);
				if (_hoops_AGSIA->Count()) {
				/* _hoops_RPP _hoops_IIH _hoops_CSAP _hoops_IRS _hoops_RHHR, _hoops_IHIS _hoops_SCH _hoops_IS _hoops_RH _hoops_HACH _hoops_PCGIA */
 					_hoops_HHCIA->Append((*_hoops_AGSIA)[0]);
					_hoops_AGSIA->SetCount(0);
				}
			}
		}
	}

	/* _hoops_GII _hoops_PGGS _hoops_IPSIA _hoops_SGS _hoops_SSCP _hoops_RPII _hoops_CPSIA _hoops_HS _hoops_IS _hoops_SHH _hoops_SPSIA _hoops_ACSRR _hoops_HCR _hoops_RSSI.
	 * _hoops_HHIGR _hoops_CGH _hoops_SHH _hoops_PSP _hoops_RRI _hoops_HSAR _hoops_IRS _hoops_CIAGR _hoops_APSAR, _hoops_PHRI, _hoops_RPP _hoops_GII */
	if (_hoops_SPPIA->_hoops_PGRIA != null) {
		_hoops_GCGIA *_hoops_ARCIA = _hoops_SPPIA->_hoops_PGRIA;

		for (int i = 0; i < _hoops_ARCIA->Count(); i++) {
			_hoops_SPPIA->_hoops_HSGIA = (*_hoops_ARCIA)[i];
			_hoops_SPPIA->_hoops_ISGIA = _hoops_HHCIA;
			if (!_hoops_AASIA) {
				_hoops_GAHPA(_hoops_ASGIA, point_count, points, face_list_length, face_list, false);
				_hoops_AASIA = true;
			}
			HI_BSP_Map_Function(_hoops_ASGIA, _hoops_RAIIA, _hoops_SPPIA);
		}
	}

	if (_hoops_HHCIA->Count() > 0) {
		_hoops_PHCIA(_hoops_RIGC, _hoops_HHCIA, null, start_seg);
		_hoops_PPIHA = _hoops_HHCIA->Count();
	}

  done:

	_hoops_IRRPR();

	if (_hoops_PASIA) {
		FREE_ARRAY(_hoops_HASIA, _hoops_GPSIA, Point);
		FREE_ARRAY(_hoops_IASIA, _hoops_SASIA, int);
		FREE_ARRAY(normals, _hoops_CASIA, Vector);
	}

	FREE_ARRAY(new_face_list, _hoops_SRSIA, int);

	if (_hoops_APCIA != null)
		delete _hoops_APCIA;
	if (_hoops_AGSIA != null)
		delete _hoops_AGSIA;
	if (_hoops_HHCIA != null)
		delete _hoops_HHCIA;

	if (_hoops_ASGIA != null) {
		HI_BSP_Map_Function(_hoops_ASGIA, _hoops_AAHPA, null);
		HI_Delete_BSP(_hoops_ASGIA);
	}

	if (_hoops_RIGC->_hoops_PRCIA == null)
		_hoops_RRCIA(_hoops_SPPIA);

	return _hoops_PPIHA;
}




HC_INTERFACE int HC_Compute_Selection_By_Sh_W_Op (
	char const *	action,
	char const *	start_seg,
	int				point_count,
	Point const *	points,
	int				face_list_length,
	int const *		face_list,
	const char *	options)
{
	_hoops_PAPPR context("Compute_Selection_By_Shell");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Selection_By_Sh_W_Op () */\n");
	);

	return _hoops_RASIA(context, action, start_seg, point_count, points, face_list_length, face_list, options);
}


HC_INTERFACE int HC_Compute_Selection_By_Shell (
	char const *		action,
	char const *		start_seg,
	int					point_count,
	Point const *		points,
	int					face_list_length,
	int const *			face_list)
{
	_hoops_PAPPR context("Compute_Selection_By_Shell");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Selection_By_Shell () */\n");
	);

	return _hoops_RASIA(context, action, start_seg, point_count, points, face_list_length, face_list, "");
}


#define _hoops_GHSIA			0x1
#define _hoops_RHSIA					0x2

// _hoops_PAGA: _hoops_PSPA _hoops_GPRR _hoops_HAR _hoops_CPSA _hoops_IGI, _hoops_SAHR _hoops_IH _hoops_PIPPR _hoops_IPAC
local const _hoops_IGRCR _hoops_AHSIA[] = {
	{0,		_hoops_GRRCR (""),				_hoops_RRRCR,	0,	false},
	{0,		_hoops_GRRCR ("oru"),			_hoops_RRRCR,	0,	false},
};
local const _hoops_HPAGA _hoops_PHSIA = {
	_hoops_GGAPR (_hoops_AHSIA),		_hoops_AHSIA,
};


local const _hoops_IGRCR _hoops_HHSIA[] = {
	{_hoops_GHSIA, _hoops_GRRCR ("vector"),	_hoops_SPPCR,				3, true},
	{_hoops_RHSIA, _hoops_GRRCR ("maximum distance"),	_hoops_CIGHA,	1, true,
																	&_hoops_PHSIA},
 };

local const _hoops_HPAGA _hoops_IHSIA = {
	_hoops_GGAPR (_hoops_HHSIA),
	_hoops_HHSIA,
};



struct configs {
	bool	_hoops_ICSAR;
	Vector	_hoops_CCSAR;
	float	_hoops_CHSIA;
};

local bool _hoops_CHGAA (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			option_string,
	struct configs *		_hoops_SHGAA)
{
	/* _hoops_ARP _hoops_SHIR _hoops_HSH _hoops_IH _hoops_HCR _hoops_IIGR _hoops_RH _hoops_GIGAA */
	_hoops_SHGAA->_hoops_ICSAR = false;
	_hoops_SHGAA->_hoops_CHSIA = -1;

	if (option_string == null)
		return false;

	_hoops_HIACR (_hoops_SHSIA, _hoops_HHSIA);

	Option_Value *	option_list = null;
	Option_Value *	option;

	if (!HI_Parse_Options (_hoops_RIGC, option_string, _hoops_CIACR (_hoops_SHSIA), &option_list, _hoops_SIACR))
		return false;

	if ((option = option_list) != null) do {
		switch (option->type->id) {
			case _hoops_GHSIA: {
				if (!option->_hoops_GCACR) {
				  	_hoops_SHGAA->_hoops_ICSAR = true;
				  	_hoops_SHGAA->_hoops_CCSAR.x = option->value._hoops_PIPCR[0];
				  	_hoops_SHGAA->_hoops_CCSAR.y = option->value._hoops_PIPCR[1];
				  	_hoops_SHGAA->_hoops_CCSAR.z = option->value._hoops_PIPCR[2];
				  }
			  }	  break;
			  case _hoops_RHSIA: {
				if (!option->_hoops_GCACR) {
 					_hoops_SHGAA->_hoops_CHSIA = option->value._hoops_PIPCR[0];
				}
			}	break;
		}
	} while ((option = option->next) != null);

	HI_Free_Option_List (_hoops_RIGC, option_list);
	return true;
}



local void _hoops_GISIA(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_PIGIA *		_hoops_RISIA,
	Point					p1,
	Point					p2,
	char const *			start_seg)
{
	float x, y, z;
 	char pathname[4096];
	char _hoops_RICIA[64];
	Key _hoops_AICIA;
	_hoops_CGGIA *env_info;
 	_hoops_AISIA *_hoops_PISIA;

	_hoops_GHAIR *	_hoops_GIGC;

	int _hoops_HICIA = _hoops_IICIA;

	_hoops_HPAH const *	_hoops_CICIA = (_hoops_HPAH const *)HI_One_Segment_Search (_hoops_RIGC, start_seg, true);

	if (_hoops_CICIA != null) {
		if ((_hoops_GIGC = (_hoops_GHAIR *)HI_Find_Net_Attribute (_hoops_RIGC, _hoops_CICIA, HK_HEURISTICS)) != null) {
			if (BIT (_hoops_GIGC->mask&_hoops_GIGC->value, _hoops_SICIA))
				_hoops_HICIA = _hoops_GIGC->_hoops_GCCIA;
			_hoops_HPRH(_hoops_GIGC);
		}
	}

	ASSERT(_hoops_HICIA >= 0);

  	env_info = (_hoops_CGGIA *)_hoops_RISIA->_hoops_IIAIA;
	if (env_info->type == _hoops_PGPIA)
		_hoops_AICIA = _hoops_RHCIA((_hoops_HPGIA *)env_info);
	else
		_hoops_AICIA = env_info->key;
 	x = p2.x;
	y = p2.y;
	z = p2.z;
/*	_hoops_RA = _hoops_HISIA->_hoops_RA; */

	ZALLOC(_hoops_PISIA, _hoops_AISIA);
	_hoops_PISIA->hit_location = p1;
 	_hoops_HRCIA(_hoops_RIGC,env_info, pathname);

	HI_Queue_Selection_Event(_hoops_RIGC,
		"",		/* _hoops_HCCIA */
		"",		/* _hoops_AIRI */
		"v",	/* _hoops_ACPH */
		0,				/* _hoops_HSAGA */
		pathname,		/* _hoops_ICCIA */
		_hoops_AICIA,		/* _hoops_SIC */
		0, 0, 0,		/* _hoops_CCCIA, _hoops_SCCIA, _hoops_GSCIA */
		0, 0, 0,		/* _hoops_RPPS _hoops_SGGPR */
		x, y, z, _hoops_PISIA			/* _hoops_SARA _hoops_SGGPR */
	);

	HI_Await_Event (_hoops_RIGC, _hoops_RICIA, -1);
}


HC_INTERFACE float HC_Compute_Selection_Dist_By_Sh (
	char const *			action,
	char const *			start_seg,
	int						point_count,
	Point const *			points,
	int						face_list_length,
	int const *				face_list,
	const char *			options)
{
	_hoops_PAPPR context("Compute_Selection_Distance_By_Shell");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Selection_Distance_By_Shell () */\n");
	);

	float	_hoops_IISIA = -1.0f;

	_hoops_CSPPR();
	_hoops_CRCP *	_hoops_SRCP;
	if ((_hoops_SRCP = HI_One_Segment_Search (context, start_seg, true)) != null) {
		Key	_hoops_RPCIA = _hoops_SRCP->key;

		struct configs	config;
		_hoops_CHGAA(context, options, &config);

  		_hoops_AIGIA *	_hoops_APCIA = POOL_NEW(context->memory_pool, _hoops_AIGIA)(context->memory_pool);
		global_compare_info *	_hoops_SPPIA = _hoops_SPCIA(context, _hoops_RPCIA, _hoops_APCIA);

		VBSP *	_hoops_ASGIA;
		bool	_hoops_AASIA = false;
		ZALLOC(_hoops_ASGIA, VBSP);
		if (config._hoops_ICSAR) {
 			_hoops_ASGIA->_hoops_CCSAR = config._hoops_CCSAR;
			_hoops_ASGIA->_hoops_ICSAR = true;
		}
		else
			_hoops_ASGIA->_hoops_ICSAR = false;

 		_hoops_SPPIA->_hoops_ASGIA = _hoops_ASGIA;

		/* _hoops_AA _hoops_IRS _hoops_HHCI _hoops_IASC _hoops_AHCRR _hoops_RPGP _hoops_IS _hoops_GGSIA _hoops_HIGR _hoops_IIGR _hoops_RGSIA */
		_hoops_SASC _hoops_RPSIA(point_count, points);


		if (config._hoops_ICSAR) {
			HI_Test_BSP (_hoops_SPPIA->tree, _hoops_ICAIA, _hoops_SPPIA,
						 (void*)&_hoops_RPSIA, _hoops_RPSIA, true);
		}
		else {
			HI_Test_BSP (_hoops_SPPIA->tree, _hoops_HCAIA, _hoops_SPPIA,
						 (void*)&_hoops_RPSIA, _hoops_RPSIA, true);
		}

		FREE(_hoops_ASGIA, VBSP);
		_hoops_ASGIA = null;
		if (_hoops_SPPIA->_hoops_SSGIA->PeekFirst()) {
			/* _hoops_IH _hoops_GRR _hoops_IIGR _hoops_RH _hoops_SCHS _hoops_SGS _hoops_AIPAA _hoops_RH _hoops_ARRS _hoops_RPGP, _hoops_AA _hoops_IRS _hoops_RRI _hoops_CICAR _hoops_ISPR
			 * _hoops_HPP _hoops_CIHH _hoops_RSSI _hoops_ACSRR _hoops_GHC _hoops_PPR _hoops_RPP _hoops_SGS _hoops_IIAH, _hoops_HSSC _hoops_ISSC _hoops_IS _hoops_PCCP (_hoops_IHPH)
			 * _hoops_CCCI _hoops_HSSP _hoops_IS _hoops_HSSP _hoops_RPGP */

			_hoops_ASGIA = HI_New_BSP(context->memory_pool, _hoops_RPSIA, _hoops_PGHPA);
			if (config._hoops_ICSAR) {
 				_hoops_ASGIA->_hoops_CCSAR = config._hoops_CCSAR;
				_hoops_ASGIA->_hoops_ICSAR = true;
			}
			else
				_hoops_ASGIA->_hoops_ICSAR = false;

			_hoops_SPPIA->_hoops_SCGIA = points;
			_hoops_SPPIA->_hoops_RSGIA = face_list;
			_hoops_SPPIA->_hoops_ASGIA = _hoops_ASGIA;

			_hoops_HIGIA *	_hoops_AGSIA = POOL_NEW(context->memory_pool, _hoops_HIGIA)(context->memory_pool);

 			_hoops_SPPIA->_hoops_GGRIA = _hoops_AGSIA;
 			_hoops_ASGIA->_hoops_GSSAR = false;

			_hoops_APCIA->ResetCursor();
			while (1) {
				_hoops_CGGIA *	env_info = _hoops_APCIA->PeekCursor();
				if (!env_info)
					break;
 				if (_hoops_SACIA(context, action, env_info)) {
					_hoops_SPPIA->_hoops_HSGIA = env_info;
					if (!_hoops_AASIA) {
						_hoops_GAHPA(_hoops_ASGIA, point_count, points, face_list_length, face_list, false);
						_hoops_AASIA = true;
					}
					if (!(env_info->flags & _hoops_AGGIA))
						if (!_hoops_CSIIA(context, env_info))
							continue;
					_hoops_AGCIA(_hoops_ASGIA, _hoops_SPPIA, env_info, true);
				}
				_hoops_APCIA->AdvanceCursor();
			}

			_hoops_AGSIA->ResetCursor();
			_hoops_PIGIA *	_hoops_RISIA = _hoops_AGSIA->PeekCursor();
			if (_hoops_RISIA) {
				Point	_hoops_CISIA, _hoops_SISIA;
				Point	_hoops_GCSIA, _hoops_RCSIA;

				if (!config._hoops_ICSAR)
					_hoops_IISIA = _hoops_HIAIA(_hoops_RISIA, _hoops_SPPIA->_hoops_SCGIA, &_hoops_CISIA, &_hoops_SISIA);
				else
					_hoops_IISIA = _hoops_ACAIA(_hoops_RISIA, _hoops_SPPIA->_hoops_SCGIA, _hoops_ASGIA->_hoops_CCSAR, &_hoops_CISIA, &_hoops_SISIA);

				_hoops_AGSIA->AdvanceCursor();
				while (1) {
					float _hoops_ACSIA;
					_hoops_PIGIA *temp = _hoops_AGSIA->PeekCursor();

					if (!temp)
						break;
					if (temp->min < _hoops_IISIA) {
						if (!config._hoops_ICSAR)
							_hoops_ACSIA = _hoops_HIAIA(temp, (Point *)_hoops_SPPIA->_hoops_SCGIA, &_hoops_GCSIA, &_hoops_RCSIA);
						else
							_hoops_ACSIA = _hoops_ACAIA(temp, (Point *)_hoops_SPPIA->_hoops_SCGIA, _hoops_ASGIA->_hoops_CCSAR, &_hoops_GCSIA, &_hoops_RCSIA);

						if (_hoops_ACSIA < _hoops_IISIA && _hoops_ACSIA < 1.0e6)	 {
							_hoops_IISIA = _hoops_ACSIA;
							FREE(_hoops_RISIA, _hoops_PIGIA);
							_hoops_RISIA = temp;
							_hoops_CISIA = _hoops_GCSIA;
							_hoops_SISIA = _hoops_RCSIA;
						}
						else
							FREE(temp, _hoops_PIGIA);
					}
					else
						FREE(temp, _hoops_PIGIA);
					_hoops_AGSIA->AdvanceCursor();
				}


				if (_hoops_RISIA && (config._hoops_CHSIA < 0 || _hoops_IISIA <= config._hoops_CHSIA) && _hoops_IISIA<1.0e6) {
					_hoops_GISIA(context, _hoops_RISIA, _hoops_CISIA, _hoops_SISIA, start_seg);
				}
				else
					_hoops_IISIA = -1;
				FREE(_hoops_RISIA, _hoops_PIGIA);
			}
			else
				_hoops_IISIA = -1;

			delete _hoops_AGSIA;
		}

		delete _hoops_APCIA;

		if (_hoops_ASGIA != null) {
			HI_BSP_Map_Function(_hoops_ASGIA, _hoops_AAHPA, null);
			HI_Delete_BSP(_hoops_ASGIA);
		}
		if (context->_hoops_PRCIA == null) {
			_hoops_RRCIA(_hoops_SPPIA);
		}
	}
	_hoops_IRRPR();

	return _hoops_IISIA;
}


HC_INTERFACE int HC_Compute_Selection_By_Ray (
	char const *	action,
	char const *	start_seg,
	Point const *	start,
	Point const *	_hoops_PCSIA)
{
	_hoops_PAPPR context("Compute_Selection_By_Shell");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Selection_By_Ray () */\n");
	);

	if (start_seg == null || *start_seg == '\0') {
		HE_ERROR (HEC_SYNTAX, HES_NULL_INPUT, "Blank or null segment specification");
		return 0;
	}

	Vector const *	direction = (Vector const *)_hoops_PCSIA;
	_hoops_GCGIA *_hoops_APCIA = null, *_hoops_AGSIA = null, *_hoops_HHCIA = null;
	_hoops_RCGIA *_hoops_HCSIA = null, *_hoops_IHCIA = null;
	int _hoops_PPIHA = 0;
	global_compare_info *_hoops_SPPIA = null;
	_hoops_CGGIA *env_info = null;
	Key _hoops_RPCIA;
	_hoops_HSSHA _hoops_PAHHA;
	int _hoops_ICSIA;
	_hoops_RIGIA *sp;
	_hoops_AIGIA *_hoops_SIAI = null;
	_hoops_SIAI = POOL_NEW(context->memory_pool, _hoops_AIGIA)(context->memory_pool);


	_hoops_CSPPR();
	_hoops_CRCP *	_hoops_SRCP;
	if ((_hoops_SRCP = HI_One_Segment_Search (context, start_seg, true)) == null)
		goto done;

	_hoops_RPCIA = _hoops_SRCP->key;

	_hoops_APCIA = POOL_NEW(context->memory_pool, _hoops_GCGIA)(context->memory_pool);
	_hoops_SPPIA = _hoops_GPCIA(context, _hoops_RPCIA, _hoops_APCIA);

	/* _hoops_AA _hoops_IRS _hoops_HHCI _hoops_IASC _hoops_AHCRR _hoops_RPGP _hoops_IS _hoops_GGSIA _hoops_HIGR _hoops_IIGR _hoops_RGSIA */
	_hoops_PAHHA.start = start;
	_hoops_PAHHA.direction = (Vector const *)direction;
	HI_Test_BSP_Ray (_hoops_SPPIA->tree, _hoops_HSAIA, _hoops_SPPIA,
					 &_hoops_PAHHA, start, direction);

	if (_hoops_APCIA->Count() == 0 &&
		!_hoops_SPPIA->_hoops_PGRIA)
		goto done; /* _hoops_RSIH _hoops_PGPCR _hoops_RPP _hoops_IIH'_hoops_GRI _hoops_ISAP _hoops_RAAP _hoops_IS _hoops_AA. */


	_hoops_SPPIA->_hoops_SCGIA = null;
	_hoops_SPPIA->_hoops_RSGIA = null;
	_hoops_SPPIA->_hoops_ASGIA = null;
	_hoops_SPPIA->_hoops_PSGIA = &_hoops_PAHHA;
	_hoops_AGSIA = POOL_NEW(context->memory_pool, _hoops_GCGIA)(context->memory_pool);
	_hoops_HCSIA = POOL_NEW(context->memory_pool,_hoops_RCGIA)(context->memory_pool);
	/* _hoops_ARP _hoops_RH _hoops_HSPR _hoops_PCSRR _hoops_IS "1" _hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_SSCC _hoops_RRP _hoops_IS _hoops_SSS _hoops_RH _hoops_PHRHA _hoops_SGSSR */
	_hoops_SPPIA->_hoops_ISGIA = _hoops_AGSIA;
	_hoops_SPPIA->_hoops_RGRIA = _hoops_HCSIA;
	_hoops_SPPIA->_hoops_CSGIA = -1;
	_hoops_SPPIA->_hoops_AGRIA = -1;

	_hoops_HHCIA = POOL_NEW(context->memory_pool, _hoops_GCGIA)(context->memory_pool);
	_hoops_IHCIA = POOL_NEW(context->memory_pool,_hoops_RCGIA)(context->memory_pool);
	for (int i = 0; i < _hoops_APCIA->Count(); i++) {
		env_info = (_hoops_CGGIA *) (*_hoops_APCIA)[i];
		if (_hoops_SACIA(context, action, env_info)) {
			_hoops_SPPIA->_hoops_HSGIA = env_info;
			if (!_hoops_GGCIA(context, _hoops_SPPIA, &_hoops_PAHHA,env_info,_hoops_SIAI))
				continue;
 			if (_hoops_AGSIA->Count()) {
				ASSERT(_hoops_AGSIA->Count() == _hoops_HCSIA->Count());
				/* _hoops_RPP _hoops_IIH _hoops_CSAP _hoops_IRS _hoops_RHHR, _hoops_IHIS _hoops_SCH _hoops_IS _hoops_RH _hoops_HACH _hoops_PCGIA */
				sp = (*_hoops_HCSIA)[0];
				_hoops_ICSIA = 0;
				/* _hoops_GIPHR _hoops_RH _hoops_CCSIA _hoops_IH _hoops_AASC _hoops_RA */
				for (int j = 1; j < _hoops_HCSIA->Count(); j++) {
					if ((*_hoops_HCSIA)[j]->t < sp->t) {
						sp = (*_hoops_HCSIA)[j];
						_hoops_ICSIA = j;
					}
				}
				/* _hoops_CIH _hoops_HCR _hoops_GHSHA _hoops_AHC _hoops_SIHC'_hoops_GRI _hoops_AHSAR _hoops_RH _hoops_AAH _hoops_SIHRR */
				for (int j = 0; j < _hoops_HCSIA->Count(); j++) {
					if (j != _hoops_ICSIA) {
						FREE ((*_hoops_HCSIA)[j], _hoops_RIGIA);
					}
				}
				_hoops_HHCIA->Append((*_hoops_AGSIA)[_hoops_ICSIA]);
				_hoops_IHCIA->Append(sp);
				_hoops_AGSIA->SetCount(0);
				_hoops_HCSIA->SetCount(0);
			}
		}
	}

	if (_hoops_HHCIA->Count() > 0) {
		_hoops_PHCIA(context, _hoops_HHCIA, _hoops_IHCIA, start_seg);
		_hoops_PPIHA = _hoops_HHCIA->Count();
	}


	_hoops_SIAI->ResetCursor();
	while (1)  {
		_hoops_RAGIA * env_info = (_hoops_RAGIA *)_hoops_SIAI->PeekCursor();
		if (!env_info)
			break;
		_hoops_HRPIA(env_info);

		_hoops_SIAI->AdvanceCursor();
	}

done:
	_hoops_IRRPR();

	delete _hoops_SIAI;
	if (_hoops_APCIA != null) delete _hoops_APCIA;
	if (_hoops_AGSIA != null) delete _hoops_AGSIA;
	if (_hoops_HCSIA != null) delete _hoops_HCSIA;
	if (_hoops_HHCIA != null) delete _hoops_HHCIA;
	if (_hoops_IHCIA != null) {
		for (int i = 0; i < _hoops_IHCIA->Count(); i++) {
			FREE((*_hoops_IHCIA)[i], _hoops_RIGIA);
		}
		delete _hoops_IHCIA;
	}

	if (context->_hoops_PRCIA == null) {
		_hoops_RRCIA(_hoops_SPPIA);
	}

	return _hoops_PPIHA;
}



/* _hoops_SCSIA _hoops_RIPS/_hoops_ISSC _hoops_GSSIA _hoops_RSSIA _hoops_IS _hoops_PGHH _hoops_CAS _hoops_RSSI _hoops_CHR _hoops_ISHA-_hoops_GPP _hoops_IS _hoops_GGAHR _hoops_HAGA,
 * _hoops_PSCR _hoops_GRAS _hoops_RH _hoops_ASSIA _hoops_ISII _hoops_SGS _hoops_SR _hoops_GRS _hoops_SHH _hoops_PSSIA.
 * _hoops_HGI _hoops_HICRR _hoops_API _hoops_HSSIA _hoops_PPGS _hoops_IH _hoops_RGCI _hoops_IIPR _hoops_CCPAR (_hoops_AHSAR _hoops_ISSIA) _hoops_IH
 * _hoops_PGAP _hoops_SCH _hoops_HRGR _hoops_RH _hoops_CIS'_hoops_GRI _hoops_CSSAR _hoops_IS _hoops_HSCI */
static void _hoops_CSSIA(
	_hoops_AIGPR *	_hoops_RIGC,
	Polyhedron const *		phon,
	int						_hoops_SSSIA,
	int alter *				_hoops_GGGCA,
	int *					_hoops_RGGCA,
	int *					_hoops_AGGCA,
	int **					_hoops_PGGCA,
	int **					_hoops_HGGCA)
{
	int i, j, length, start, end, count;
	_hoops_HICRA *_hoops_IGGCA;
	_hoops_CGGCA *_hoops_SGGCA;
	int *_hoops_GRGCA, *_hoops_GASI;
	int const *_hoops_RRGCA, *_hoops_ARGCA;
	POINTER_SIZED_INT _hoops_PRGCA, pair;
	int *lengths = 0;
	int *_hoops_HRGCA = 0;
	_hoops_CGGCA *_hoops_IRGCA;
	_hoops_CRGCA *_hoops_SRGCA;
	int total;
	bool _hoops_IHRPA;
	int index, _hoops_GAGCA, *_hoops_RAGCA;
	const int **_hoops_AAGCA;
	int *_hoops_PAGCA, *_hoops_HAGCA, _hoops_IAGCA, _hoops_CAGCA;

	_hoops_IGGCA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_HICRA)(_hoops_RIGC->memory_pool, 8 * phon->point_count);
	_hoops_SGGCA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_CGGCA)(_hoops_RIGC->memory_pool);

	/*_hoops_SCSH _hoops_RGR _hoops_HAPR, _hoops_SR _hoops_ARPR _hoops_RH _hoops_ISHA _hoops_SCAH*/
	Shell const *	_hoops_SPHPR = (Shell const *)phon;

	_hoops_RRGCA = _hoops_SPHPR->face_list;
	_hoops_ARGCA = _hoops_SPHPR->face_list + _hoops_SPHPR->face_list_length;
	i = 0;
	while (_hoops_RRGCA < _hoops_ARGCA) {
		length = _hoops_RRGCA[0];
		ASSERT(length > 0);
		for (j = 0; j < length; j++) {
			if (j == 0)
				start = _hoops_RRGCA[length];
			else
				start = _hoops_RRGCA[j];
			end = _hoops_RRGCA[j+1];
			_hoops_PRGCA = (start << 16) ^ end;
			_hoops_IGGCA->InsertItem(_hoops_PRGCA, i);
		}
		_hoops_RRGCA += length + 1;
		i++;
	}

	ALLOC_ARRAY(_hoops_RAGCA, _hoops_SSSIA, int);
	ALLOC_ARRAY(_hoops_AAGCA, _hoops_SSSIA, const int *);
	_hoops_GAGCA = 0;
	_hoops_RRGCA = _hoops_SPHPR->face_list;
	_hoops_ARGCA = _hoops_SPHPR->face_list + _hoops_SPHPR->face_list_length;
	i = 0;
	while (_hoops_RRGCA < _hoops_ARGCA) {
		length = _hoops_RRGCA[0];
		if (_hoops_GGGCA[i] == 0) {
			_hoops_RAGCA[_hoops_GAGCA] = i;
			_hoops_AAGCA[_hoops_GAGCA] = _hoops_RRGCA;
			_hoops_GAGCA++;
		}
		_hoops_RRGCA += length + 1;
		i++;
	}
	/* _hoops_RPP _hoops_IIH _hoops_CHR _hoops_HHH _hoops_GSSIA _hoops_SGS _hoops_CHR _hoops_RHGC*/
	if (_hoops_GAGCA) {
		int _hoops_SAGCA = _hoops_GAGCA;

		ALLOC_ARRAY(_hoops_PAGCA, _hoops_SAGCA, int);
		ALLOC_ARRAY(_hoops_HAGCA,_hoops_SAGCA, int);

		do {
			_hoops_IHRPA = false;
			_hoops_IAGCA = 0;
			_hoops_CAGCA = 0;

			/* _hoops_RGR _hoops_HAPR _hoops_SSCP _hoops_IS _hoops_ARAS _hoops_HPIPR _hoops_PGGA _hoops_SR _hoops_CIHPA _hoops_GPGCA _hoops_PSAP _hoops_RH _hoops_RSGR*/
			for (i = _hoops_GAGCA-1; i >= 0; i--) {
				_hoops_RRGCA = _hoops_AAGCA[i];
				length = _hoops_RRGCA[0];
				for (j = 0; j < length; j++) {
					if (j == 0)
						start = _hoops_RRGCA[length];
					else
						start = _hoops_RRGCA[j];
					end = _hoops_RRGCA[j+1];
					/*_hoops_IHSH _hoops_IH _hoops_RH _hoops_PSAI (_hoops_PIIA _hoops_RH _hoops_SCAH _hoops_SIC)*/
					_hoops_PRGCA = (end << 16) ^ start;
					if (_hoops_IGGCA->LookupItem(_hoops_PRGCA, &pair) == _hoops_HICRA::Success) {
						if (_hoops_GGGCA[pair] != 0) {
							_hoops_IHRPA = true;
							index = _hoops_RAGCA[i];
							if (_hoops_GAGCA > 0) {
								/* _hoops_CIHPA _hoops_PCCP _hoops_RHGC _hoops_HSP _hoops_PSAP _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_CRPR _hoops_IS _hoops_CISA _hoops_GGR _hoops_IH _hoops_ISCP _hoops_RPGCA _hoops_RHRI _hoops_SPR*/
								_hoops_RAGCA[i] = _hoops_RAGCA[_hoops_GAGCA-1];
								_hoops_AAGCA[i] = _hoops_AAGCA[_hoops_GAGCA-1];
								_hoops_GAGCA--;
							}
							if (_hoops_GGGCA[pair] == 1) {
								_hoops_PAGCA[_hoops_IAGCA] = index;
								_hoops_IAGCA++;
								break;
							}
							else if (_hoops_GGGCA[pair] == -1) {
								_hoops_HAGCA[_hoops_CAGCA] = index;
								_hoops_CAGCA++;
								break;
							}
						}
					}
				}
			}
			/* _hoops_SRGC _hoops_RH _hoops_SHPH _hoops_PPR _hoops_ASGGR _hoops_IH _hoops_RH _hoops_SPS _hoops_IPGR.  _hoops_PAGA _hoops_SGS _hoops_SR _hoops_HHS _hoops_HAR
			 * _hoops_IRHH _hoops_SHPH _hoops_IS _hoops_RH _hoops_APGCA _hoops_SSPP _hoops_GGR _hoops_RH _hoops_HAPR _hoops_ARRS _hoops_PGGA _hoops_SR _hoops_HHGC
			 * _hoops_PPGCA _hoops_IS _hoops_HPGCA _hoops_HPGR _hoops_ICRP _hoops_SPR _hoops_HSP _hoops_RIR _hoops_IPGR */
			for (i = 0; i < _hoops_IAGCA; i++) {
				_hoops_GGGCA[_hoops_PAGCA[i]] = 1;
			}
			for (i = 0; i < _hoops_CAGCA; i++) {
				_hoops_GGGCA[_hoops_HAGCA[i]] = -1;
			}
		} while (_hoops_IHRPA);
		FREE_ARRAY(_hoops_PAGCA, _hoops_SAGCA, int);
		FREE_ARRAY(_hoops_HAGCA, _hoops_SAGCA, int);
	}
	/* _hoops_RPP _hoops_PA _hoops_HRGR **_hoops_HGGC** _hoops_GHSAR _hoops_RHGC (_hoops_IAS._hoops_ISHI. _hoops_PCCP _hoops_IPGCA _hoops_HSP _hoops_SGS _hoops_HRGR _hoops_PSAP _hoops_GPP _hoops_RGCI _hoops_HAII)
	   _hoops_HSII _hoops_SCH _hoops_GAR _hoops_RIPS _hoops_CPGCA */
	for (i = 0; i < _hoops_GAGCA; i++) {
		_hoops_GGGCA[_hoops_RAGCA[i]] = 1;
	}
	FREE_ARRAY(_hoops_RAGCA, _hoops_SSSIA, int);
	FREE_ARRAY(_hoops_AAGCA, _hoops_SSSIA, int *);

	/*_hoops_GGR _hoops_RGR _hoops_HAPR, _hoops_SR _hoops_HSGIR _hoops_IRS _hoops_HIGR _hoops_IIGR _hoops_III _hoops_SGHC*/
	_hoops_RRGCA = _hoops_SPHPR->face_list;
	_hoops_ARGCA = _hoops_SPHPR->face_list + _hoops_SPHPR->face_list_length;
	i = 0;
	while (_hoops_RRGCA < _hoops_ARGCA) {
		length = _hoops_RRGCA[0];
		for (j = 0; j < length; j++) {
			if (j == 0)
				start = _hoops_RRGCA[length];
			else
				start = _hoops_RRGCA[j];
			end = _hoops_RRGCA[j+1];
			/* _hoops_RGAR _hoops_IHSH _hoops_RPP _hoops_HSPP < _hoops_RSGR _hoops_HIS _hoops_SGS _hoops_SR _hoops_RGAR _hoops_SGH _hoops_RH _hoops_ISHA _hoops_ARR*/
			if (start < end) {
				/*_hoops_IHSH _hoops_IH _hoops_RH _hoops_PSAI (_hoops_PIIA _hoops_RH _hoops_SCAH _hoops_SIC)*/
				_hoops_PRGCA = (end << 16) ^ start;
				if (_hoops_IGGCA->LookupItem(_hoops_PRGCA, &pair) == _hoops_HICRA::Success) {
					if (_hoops_GGGCA[pair] * _hoops_GGGCA[i] == -1) {
						ALLOC_ARRAY(_hoops_GRGCA, 2, int);
 						/*_hoops_SGH _hoops_RH _hoops_HSH _hoops_GGR _hoops_APGCA _hoops_IS _hoops_PSSP _hoops_RH _hoops_HSCHR _hoops_IIGR _hoops_RH _hoops_RIPS _hoops_PPR _hoops_ISSC _hoops_RSSI*/
						if (_hoops_GGGCA[i] > 0) {
							_hoops_GRGCA[0] = start;
							_hoops_GRGCA[1] = end;
						}
						else {
							_hoops_GRGCA[0] = end;
							_hoops_GRGCA[1] = start;
						}
						_hoops_SGGCA->AddFirst(_hoops_GRGCA);
					}
				}
			}
		}
		_hoops_RRGCA += length + 1;
		i++;
	}

	/*_hoops_GGR _hoops_RGR _hoops_SPGCA _hoops_RH _hoops_III _hoops_SGHC _hoops_CRGR _hoops_PGRC*/
	_hoops_SRGCA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_CRGCA)(_hoops_RIGC->memory_pool);
 	total = 0;
	/*_hoops_HASC _hoops_RH _hoops_III _hoops_SGHC _hoops_CRGR _hoops_PGRC*/
	while ((_hoops_GRGCA=_hoops_SGGCA->RemoveFirst()) != null) {
		/*_hoops_GHGCA _hoops_SRPS _hoops_GII _hoops_III _hoops_SGHC _hoops_SGS _hoops_HSPP _hoops_CAS _hoops_RH _hoops_PGHC _hoops_SPR _hoops_RHGCA
		  _hoops_RGR _hoops_HRGR _hoops_RGGIR(_hoops_ACHP^2).  _hoops_PS _hoops_PAH _hoops_PAHH _hoops_AA _hoops_GIH, _hoops_HIH _hoops_RRP _hoops_CPHP _hoops_HHCI _hoops_PPR _hoops_CAGGR,
		  _hoops_IPSH _hoops_RGR _hoops_HRGR _hoops_ASASR _hoops_IS _hoops_SHH _hoops_IRS _hoops_AHGCA _hoops_PHGCA.*/
		_hoops_IRGCA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_CGGCA)(_hoops_RIGC->memory_pool);
		_hoops_IRGCA->AddFirst(_hoops_GRGCA);
		for (;;) {
			_hoops_SGGCA->ResetCursor();
			_hoops_GASI = _hoops_SGGCA->PeekFirst();
			if (_hoops_GASI != null && _hoops_GASI[0]==_hoops_GRGCA[1]) {
				_hoops_GRGCA = _hoops_GASI;
				_hoops_IRGCA->AddLast(_hoops_GASI);
				_hoops_SGGCA->RemoveFirst();
			}
			else while ((_hoops_GASI = _hoops_SGGCA->PeekCursorNext()) != null) {
				if (_hoops_GASI[0] == _hoops_GRGCA[1]) {
					_hoops_GRGCA = _hoops_GASI;
					_hoops_IRGCA->AddLast(_hoops_GASI);
					_hoops_SGGCA->RemoveCursorNext();
					break;
				}
				_hoops_SGGCA->AdvanceCursor();
			}
			if (_hoops_GASI == null) {
				_hoops_SRGCA->AddFirst(_hoops_IRGCA);
				total += _hoops_IRGCA->Count() + 1;
				break;
			}
		}
	}
	count = _hoops_SRGCA->Count();
	if (count)
		ALLOC_ARRAY(lengths, count, int);
	*_hoops_PGGCA = lengths;
	if (total)
		ALLOC_ARRAY(_hoops_HRGCA, total, int);
	*_hoops_HGGCA = _hoops_HRGCA;
	*_hoops_RGGCA = count;
	*_hoops_AGGCA = total;
	while ((_hoops_IRGCA=_hoops_SRGCA->RemoveFirst()) != null) {
		*lengths++ = _hoops_IRGCA->Count() + 1;
		_hoops_GRGCA = _hoops_IRGCA->RemoveFirst();
		*_hoops_HRGCA++ = _hoops_GRGCA[0];
		do {
			*_hoops_HRGCA++ = _hoops_GRGCA[1];
			FREE_ARRAY(_hoops_GRGCA, 2, int);
		} while ((_hoops_GRGCA=_hoops_IRGCA->RemoveFirst()) != null);
		delete _hoops_IRGCA;
	}
	delete _hoops_SRGCA;
	while ((_hoops_GRGCA = _hoops_SGGCA->RemoveFirst()) != null)
		FREE_ARRAY(_hoops_GRGCA, 2, int);
	delete _hoops_SGGCA;
	delete _hoops_IGGCA;
}





local int _hoops_HHGCA (
	_hoops_AIGPR *	_hoops_RIGC,
	Key						shellkey,
	Vector const *			direction_in,
	Key *					front_key,
	Key *					back_key,
	Key *					side_key,
	int						_hoops_IHGCA,
	float const *			matrix = 0,
	bool					_hoops_CHGCA = false,
	char const *			action = 0,
	char const *			start_seg = 0,
 	int *					_hoops_SHGCA = 0,
	_hoops_SASC			*_hoops_HRRIA = 0
	)
{
	int i, j, length = 0, _hoops_GIGCA, _hoops_RIGCA = 0;
	int *_hoops_RRGCA, *_hoops_ARGCA;
	_hoops_ARPA *_hoops_AIGCA;
	int _hoops_PIGCA, _hoops_HIGCA, _hoops_IIGCA=0, _hoops_CIGCA;
	int *_hoops_SIGCA, *_hoops_GCGCA;
	int *_hoops_RCGCA = 0;
	int *_hoops_ACGCA = 0;
	int *_hoops_PCGCA = 0;
	int *_hoops_HCGCA = 0;
	int _hoops_ICGCA, _hoops_CCGCA;
	int *_hoops_GGGCA;
	int *_hoops_SCGCA;
	int *_hoops_GSGCA;
	int _hoops_RSGCA, _hoops_ASGCA, _hoops_PSGCA;
	Point _hoops_HSGCA;
	Point *_hoops_ISGCA = 0, *_hoops_CSGCA;
	Point *points = 0;
	Vector *normals = 0;
	Vector direction;
	float _hoops_SSRP;
 	Point const *p, *_hoops_SSGCA;
	Point *_hoops_GGRCA, *_hoops_RGRCA;

	Key temp;
	int result = true;
	bool _hoops_AGRCA = false;


	Polyhedron *	phon = (Polyhedron *)_hoops_RCSSR (_hoops_RIGC, shellkey);
	Shell const *	_hoops_SPHPR = (Shell const *)phon;

	if (phon->point_count == 0)
		return false;
	if (HI_Compute_Vector_Length(direction_in) < _hoops_CACIR)
		return false;

	if (_hoops_SPHPR->face_list == null)
		HI_Face_List_From_Tristrips(_hoops_RIGC, _hoops_PGRCA(_hoops_SPHPR));
	if (!(phon->polyhedron_flags & PHF_FACE_NORMALS_VALID))
		HI_Assemble_Face_Normals (phon);
	if (!(phon->polyhedron_flags & PHF_FACE_NORMALS_VALID))
		return false;

	HI_Assemble_Vertex_Normals (phon);
	if (!(phon->polyhedron_flags & PHF_VERTEX_NORMALS_VALID))
		return false;
	j = 0;
	for (i=1; i<phon->point_count; ++i) {
		Point const &	current = phon->points[j];
		Point const &	test = phon->points[i];

		if (test.x < current.x ||
			test.x == current.x &&
			(test.y < current.y ||
			 test.y == current.y &&
			 test.z < current.z))
			j = i;
	}
	if (phon->local_vertex_attributes.normals[j]._hoops_SSRP (phon->points[j] - phon->bounding->sphere.center) < 0)
		_hoops_AGRCA = true;

	direction.x = direction_in->x + 0.001f;
	direction.y = direction_in->y + 0.001f;
	direction.z = direction_in->z + 0.001f;


	/*_hoops_SSSHR _hoops_PHI _hoops_IIGR _hoops_SPPR _hoops_HRGR 3*_hoops_CIRGR, _hoops_HIS _hoops_CCPP _hoops_IRS _hoops_SCAH _hoops_CCA _hoops_RPPR _hoops_RRI _hoops_HSAR 2 _hoops_IACH _hoops_SGS*/
 	ALLOC_ARRAY(_hoops_GGGCA, phon->face_count, int);

	_hoops_PIGCA = 0;
	_hoops_HIGCA = 0;
	_hoops_ICGCA = 0;
	_hoops_CCGCA = 0;

	if (matrix) {
		ALLOC_ARRAY(_hoops_AIGCA, phon->face_count, _hoops_ARPA);
		HI_Compute_Transformed_Planes2(phon->face_count,
				phon->local_face_attributes.normals, matrix, _hoops_AIGCA);
	}
	else
		_hoops_AIGCA = phon->local_face_attributes.normals;
 	i = 0;
	while (i < phon->face_count) {
		_hoops_SSRP = (_hoops_AIGCA->a * direction.x) +
			  (_hoops_AIGCA->b * direction.y) +
			  (_hoops_AIGCA->c * direction.z);
		if (_hoops_AGRCA)
			_hoops_SSRP = -_hoops_SSRP;

 		if (_hoops_SSRP > _hoops_CACIR) {
			_hoops_GGGCA[i] = 1;
		}
		else if (_hoops_SSRP < -_hoops_CACIR) {
			_hoops_GGGCA[i] = -1;
		}
		else
			_hoops_GGGCA[i] = 0;
		_hoops_AIGCA++;
		i++;
	}

	ALLOC_ARRAY(_hoops_GGRCA, phon->point_count, Point);
 	p = phon->points;
	_hoops_SSGCA = phon->points + phon->point_count;
	_hoops_RGRCA = _hoops_GGRCA;
	while (p < _hoops_SSGCA) {
		_hoops_RGRCA->x = p->x;
		_hoops_RGRCA->y = p->y;
		_hoops_RGRCA->z = p->z;
		p++;
		_hoops_RGRCA++;
	}

 	if (matrix)
		HI_Compute_Transformed_Points(phon->point_count, _hoops_GGRCA, matrix,_hoops_GGRCA);

  	_hoops_AIGCA = phon->local_face_attributes.normals;
  	/*_hoops_CIS (_hoops_HAS._hoops_IAS. _hoops_HGRCA _hoops_RRCPR) _hoops_HRGR _hoops_HGSAR _hoops_IH _hoops_IGRCA _hoops_CGRCA _hoops_PPR _hoops_SGRCA */
	_hoops_CSSIA(
		_hoops_RIGC,
		phon,
		phon->face_count,
		_hoops_GGGCA,
		&_hoops_RSGCA,
		&_hoops_ASGCA,
		&_hoops_SCGCA,
		&_hoops_GSGCA);

	if (!_hoops_RSGCA) {
		result = false;
		goto _hoops_HPAGR;
	}


 /*=============================================*/

	_hoops_PIGCA = 0;
	_hoops_HIGCA = 0;
	_hoops_ICGCA = 0;
	_hoops_CCGCA = 0;
	i = 0;
	_hoops_RRGCA = (int *)_hoops_SPHPR->face_list;
	_hoops_ARGCA = (int *)_hoops_SPHPR->face_list + _hoops_SPHPR->face_list_length;
	while (_hoops_RRGCA < _hoops_ARGCA) {
		length = _hoops_RRGCA[0];
		if (_hoops_GGGCA[i] == 1) {
			_hoops_ICGCA++;
			_hoops_PIGCA += length + 1;
			_hoops_GGGCA[i] = 1;
		}
		else if (_hoops_GGGCA[i] == -1) {
			_hoops_CCGCA++;
			_hoops_HIGCA += length + 1;
			_hoops_GGGCA[i] = -1;
		}
		_hoops_RRGCA += length + 1;
		i++;
	}

	ALLOC_ARRAY(_hoops_RCGCA, _hoops_PIGCA, int);
	ALLOC_ARRAY(_hoops_ACGCA, _hoops_HIGCA, int);
	_hoops_SIGCA = _hoops_RCGCA;
	_hoops_GCGCA = _hoops_ACGCA;
	_hoops_RRGCA = (int *)_hoops_SPHPR->face_list;
	i = 0;
	while (_hoops_RRGCA < _hoops_ARGCA) {
		length = _hoops_RRGCA[0];
		if (_hoops_GGGCA[i] > 0) {
			memcpy(_hoops_SIGCA, _hoops_RRGCA, (length+1) * sizeof(int));
			_hoops_SIGCA += length + 1;
		}
		else if (_hoops_GGGCA[i] < 0) {
			memcpy(_hoops_GCGCA, _hoops_RRGCA, (length+1) * sizeof(int));
			_hoops_GCGCA += length + 1;
		}
		_hoops_RRGCA += length + 1;
		i++;
	}

 	for (i = 0; i < _hoops_RSGCA; i++) {
 		_hoops_IIGCA += 5 * (_hoops_SCGCA[i] - 1);
	}
 	if (_hoops_ASGCA) {
		ALLOC_ARRAY(points,  _hoops_ASGCA * 2, Point);
		ALLOC_ARRAY(normals,  _hoops_ASGCA * 2 , Vector);
	}
	else {
		points = null;
		normals = null;
	}
	_hoops_HSGCA.x = 0;
	_hoops_HSGCA.y = 0;
	_hoops_HSGCA.z = 0;
 	for (i = 0; i < _hoops_ASGCA; i++) {
		points[i].x = _hoops_GGRCA[_hoops_GSGCA[i]].x;
		points[i].y = _hoops_GGRCA[_hoops_GSGCA[i]].y;
		points[i].z = _hoops_GGRCA[_hoops_GSGCA[i]].z;
		_hoops_HSGCA.x += points[i].x;
		_hoops_HSGCA.y += points[i].y;
		_hoops_HSGCA.z += points[i].z;
	}
	for (i = 0; i < _hoops_ASGCA; i++) {
		points[i+_hoops_ASGCA].x = points[i].x + direction.x;
		points[i+_hoops_ASGCA].y = points[i].y + direction.y;
		points[i+_hoops_ASGCA].z = points[i].z + direction.z;
	}


 	if (_hoops_IIGCA)
		ALLOC_ARRAY(_hoops_HCGCA, _hoops_IIGCA, int);
	_hoops_RRGCA = _hoops_HCGCA;
	_hoops_GIGCA = 0;
	for (i = 0; i < _hoops_RSGCA; i++) {
		/*_hoops_IRS _hoops_ISII _hoops_IIGR _hoops_SPCC _hoops_ACHP _hoops_GRRCA _hoops_GGSR _hoops_ACHP-1 _hoops_RSSI*/
		for (j = 0; j < _hoops_SCGCA[i]-1; j++) {
			_hoops_RRGCA[0] = 4;
			if (_hoops_AGRCA) {
				_hoops_RRGCA[1] = _hoops_GIGCA;
				_hoops_RRGCA[2] = _hoops_GIGCA + 1;
				_hoops_RRGCA[3] = _hoops_GIGCA + _hoops_ASGCA + 1;
				_hoops_RRGCA[4] = _hoops_GIGCA + _hoops_ASGCA;
			}
			else {
				_hoops_RRGCA[4] = _hoops_GIGCA;
				_hoops_RRGCA[3] = _hoops_GIGCA + 1;
				_hoops_RRGCA[2] = _hoops_GIGCA + _hoops_ASGCA + 1;
				_hoops_RRGCA[1] = _hoops_GIGCA + _hoops_ASGCA;
			}
			_hoops_RRGCA += 5;
			_hoops_GIGCA++;
		}
		_hoops_GIGCA++;
	}

	ALLOC_ARRAY(_hoops_ISGCA, phon->point_count, Point);
	for (i = 0; i<phon->point_count; i++) {
		_hoops_ISGCA[i] = phon->points[i] + direction;
	}

	if (_hoops_IHGCA || _hoops_CHGCA) {
		_hoops_CIGCA = _hoops_IIGCA + _hoops_PIGCA + _hoops_HIGCA;

		_hoops_PSGCA = phon->point_count * 2 + _hoops_ASGCA * 2;
		ALLOC_ARRAY(_hoops_CSGCA, _hoops_PSGCA, Point);
		ALLOC_ARRAY(_hoops_PCGCA, _hoops_CIGCA, int);

		for (i = 0; i < phon->point_count; i++) {
			_hoops_CSGCA[i] = _hoops_ISGCA[i];
		}

		for (j = 0; j < phon->point_count; j++) {
			_hoops_CSGCA[i] = phon->points[j];
			i++;
		}

		for (j = 0; j < _hoops_ASGCA * 2; j++) {
			_hoops_CSGCA[i] = points[j];
			i++;
		}

		/* _hoops_ARP _hoops_GH _hoops_RPHGA _hoops_HSP _hoops_HIGR _hoops_HA */
		for (i = 0; i < _hoops_PIGCA; i++) {
			_hoops_PCGCA[i] = _hoops_RCGCA[i];
		}

		_hoops_RIGCA = 0;
		for (j = 0; j < _hoops_HIGCA; j++) {
			if (_hoops_RIGCA == 0) {
				/* _hoops_HSP _hoops_PPSR _hoops_RPR */
				_hoops_RIGCA = _hoops_ACGCA[j];
				_hoops_PCGCA[i] = _hoops_RIGCA;
			}
			else {
				_hoops_PCGCA[i] = _hoops_ACGCA[j] + phon->point_count;
				_hoops_RIGCA--;
			}
			i++;
		}

		_hoops_RIGCA = 0;
		for (j = 0; j < _hoops_IIGCA; j++) {
			if (_hoops_RIGCA == 0) {
				/* _hoops_HSP _hoops_PPSR _hoops_RPR */
				_hoops_RIGCA = _hoops_HCGCA[j];
				_hoops_PCGCA[i] = _hoops_RIGCA;
			}
			else {
				_hoops_PCGCA[i] = _hoops_HCGCA[j] + 2*phon->point_count;
				_hoops_RIGCA--;
			}
			i++;
		}
		if (_hoops_CHGCA)
			*_hoops_SHGCA = _hoops_RASIA(_hoops_RIGC, action, start_seg, _hoops_PSGCA, _hoops_CSGCA, _hoops_CIGCA, _hoops_PCGCA,"", _hoops_HRRIA);
		else
 			*front_key = HC_Insert_Shell(_hoops_PSGCA, _hoops_CSGCA, _hoops_CIGCA, _hoops_PCGCA);
		FREE_ARRAY(_hoops_CSGCA, _hoops_PSGCA, Point);
		FREE_ARRAY(_hoops_PCGCA, _hoops_CIGCA, int);
	}
	else {
		temp = HC_Insert_Shell(phon->point_count, _hoops_ISGCA, _hoops_PIGCA, _hoops_RCGCA);
		if (front_key)
			*front_key = temp;
		temp = HC_Insert_Shell(phon->point_count, phon->points, _hoops_HIGCA, _hoops_ACGCA);
		if (back_key)
			*back_key = temp;
		temp = HC_Insert_Shell(_hoops_ASGCA * 2, points, _hoops_IIGCA, _hoops_HCGCA);
		if (side_key)
			*side_key = temp;
	}

_hoops_HPAGR:

 	if (matrix)
		FREE_ARRAY(_hoops_AIGCA, phon->face_count, _hoops_ARPA);

	if (_hoops_GGGCA)
		FREE_ARRAY (_hoops_GGGCA, phon->face_count, int);

 	if (_hoops_SCGCA)
		FREE_ARRAY (_hoops_SCGCA, _hoops_RSGCA, int);

	if (_hoops_GSGCA)
 		FREE_ARRAY (_hoops_GSGCA, _hoops_ASGCA, int);

	if (_hoops_GGRCA)
		FREE_ARRAY (_hoops_GGRCA, phon->point_count, Point);

	if (_hoops_RCGCA)
		FREE_ARRAY (_hoops_RCGCA, _hoops_PIGCA, int);

	if (_hoops_ACGCA)
		FREE_ARRAY (_hoops_ACGCA, _hoops_HIGCA, int);

	if (points)
		FREE_ARRAY (points,  _hoops_ASGCA * 2, Point);

	if (normals)
		FREE_ARRAY (normals,  _hoops_ASGCA * 2 , Vector);

	if (_hoops_HCGCA)
		FREE_ARRAY (_hoops_HCGCA, _hoops_IIGCA, int);

	if (_hoops_ISGCA)
		FREE_ARRAY (_hoops_ISGCA, phon->point_count, Point);

	return result;
}


local int _hoops_RRRCA(
 	_hoops_IIGIA *_hoops_GCSHR,
	_hoops_CGGCA *_hoops_SGGCA,
	int _hoops_ARRCA
	)
{
	int _hoops_PRRCA = 0;
	int *_hoops_GRGCA;

	_hoops_GCSHR->ResetCursor();
	while (1) {
		_hoops_ISSHA *edge;
		_hoops_ISSHA *_hoops_HRRCA;
		edge = _hoops_GCSHR->PeekCursor();

		if (!edge)
			break;

		if (!edge->used) {
			if (edge->_hoops_RGGIA) {
				_hoops_HRRCA = edge->_hoops_RGGIA;
				edge->used = true;
				_hoops_HRRCA->used = true;
				if (edge->_hoops_SSSHA != _hoops_HRRCA->_hoops_SSSHA || edge->_hoops_SSSHA == 0) {
					ALLOC_ARRAY(_hoops_GRGCA, 2, int);
					_hoops_GRGCA[0] = edge->start;
					_hoops_GRGCA[1] = edge->end;
					_hoops_SGGCA->AddFirst(_hoops_GRGCA);
					_hoops_PRRCA++;
					edge->_hoops_GGGIA = _hoops_ARRCA;
					_hoops_HRRCA->_hoops_GGGIA = _hoops_ARRCA;
				}
				else if (edge->_hoops_GGGIA) {
					edge->_hoops_GGGIA--;
					_hoops_HRRCA->_hoops_GGGIA--;
					if (_hoops_HRRCA->_hoops_GGGIA<0)
						_hoops_HRRCA->_hoops_GGGIA = 0;
					ALLOC_ARRAY(_hoops_GRGCA, 2, int);
					_hoops_GRGCA[0] = edge->start;
					_hoops_GRGCA[1] = edge->end;
					_hoops_SGGCA->AddFirst(_hoops_GRGCA);
					_hoops_PRRCA++;
				}
			}
			else {
				ALLOC_ARRAY(_hoops_GRGCA, 2, int);
				_hoops_GRGCA[0] = edge->start;
				_hoops_GRGCA[1] = edge->end;
				_hoops_SGGCA->AddFirst(_hoops_GRGCA);
				_hoops_PRRCA++;
			}
		}

 		_hoops_GCSHR->AdvanceCursor();
	}
	return _hoops_PRRCA;
}


static void _hoops_IRRCA(
	Polyhedron const *phon,
	_hoops_SIGIA *_hoops_IGGCA,
	_hoops_IIGIA *_hoops_GCSHR
	)
{
  	int i, j, length, start, end;
	int const *_hoops_RRGCA, *_hoops_ARGCA;
	POINTER_SIZED_INT _hoops_PRGCA;

	/*_hoops_GGR _hoops_RGR _hoops_HAPR, _hoops_SR _hoops_ARPR _hoops_RH _hoops_ISHA _hoops_SCAH*/
	_hoops_RRGCA = ((Shell const *)phon)->face_list;
	_hoops_ARGCA = ((Shell const *)phon)->face_list + ((Shell const *)phon)->face_list_length;
	i = 0;
	while (_hoops_RRGCA < _hoops_ARGCA) {
		length = _hoops_RRGCA[0];
		ASSERT(length > 0);
		for (j = 0; j < length; j++) {
			if (j == 0)
				start = _hoops_RRGCA[length];
			else
				start = _hoops_RRGCA[j];
			end = _hoops_RRGCA[j+1];
 			_hoops_PRGCA = (start << 16) ^ end;
			_hoops_ISSHA * edge;
			ALLOC(edge, _hoops_ISSHA);
			edge->face = i;
			edge->start = start;
			edge->end = end;
			edge->_hoops_RGGIA = 0;
			edge->_hoops_GGGIA = false;
			_hoops_IGGCA->InsertItem(_hoops_PRGCA, edge);

			_hoops_GCSHR->AddLast(edge);
			_hoops_PRGCA = (edge->end << 16) ^ edge->start;
			_hoops_ISSHA *_hoops_HRRCA = 0;
			if (_hoops_IGGCA->LookupItem(_hoops_PRGCA, &_hoops_HRRCA) == _hoops_SIGIA::Success) {
				edge->_hoops_RGGIA = _hoops_HRRCA;
				_hoops_HRRCA->_hoops_RGGIA = edge;
			}
		}
		_hoops_RRGCA += length + 1;
		i++;
	}
}


static void _hoops_CRRCA(
	Point *points1,
	Point *points2,
	_hoops_ARPA *_hoops_HAGIA,
 	_hoops_IIGIA *_hoops_GCSHR,
	_hoops_CSSHA *_hoops_GGGCA,
	float _hoops_SRRCA)
{
	_hoops_ISSHA *edge;
	int start, end, fid;
	Point _hoops_IARAA, _hoops_CARAA;
	Point _hoops_AGPHR;
	float _hoops_GARCA, _hoops_RARCA;

	_hoops_GCSHR->ResetCursor();
	while ((edge = _hoops_GCSHR->PeekCursor()) != null) {
		_hoops_GCSHR->AdvanceCursor();

		start = edge->start;
		end = edge->end;
		fid = edge->face;
		_hoops_IARAA.x = points2[start].x - points1[end].x;
		_hoops_IARAA.y = points2[start].y - points1[end].y;
		_hoops_IARAA.z = points2[start].z - points1[end].z;
		HI_Normalize((Vector*)&_hoops_IARAA);

		_hoops_CARAA.x = points2[end].x - points1[end].x;
		_hoops_CARAA.y = points2[end].y - points1[end].y;
		_hoops_CARAA.z = points2[end].z - points1[end].z;
		HI_Normalize((Vector*)&_hoops_CARAA);
		_hoops_AGPHR.x = (_hoops_CARAA.x + _hoops_IARAA.x) / 2.0f;
		_hoops_AGPHR.y = (_hoops_CARAA.y + _hoops_IARAA.y) / 2.0f;
		_hoops_AGPHR.z = (_hoops_CARAA.z + _hoops_IARAA.z) / 2.0f;
		HI_Normalize((Vector*)&_hoops_AGPHR);
		edge->direction.x = _hoops_AGPHR.x;
		edge->direction.y = _hoops_AGPHR.y;
		edge->direction.z = _hoops_AGPHR.z;

		_hoops_GARCA = (_hoops_HAGIA[fid].a * _hoops_IARAA.x) +
			  (_hoops_HAGIA[fid].b * _hoops_IARAA.y) +
			  (_hoops_HAGIA[fid].c * _hoops_IARAA.z);
		_hoops_RARCA = (_hoops_HAGIA[fid].a * _hoops_CARAA.x) +
			  (_hoops_HAGIA[fid].b * _hoops_CARAA.y) +
			  (_hoops_HAGIA[fid].c * _hoops_CARAA.z);
		edge->used = false;
 		if (_hoops_GARCA >= _hoops_SRRCA) {
			if (_hoops_RARCA >= _hoops_SRRCA)
				edge->_hoops_SSSHA = _hoops_AARCA;
			else
				edge->_hoops_SSSHA = _hoops_PARCA;
		}
		else if (_hoops_GARCA < -_hoops_SRRCA) {
			if (_hoops_RARCA < -_hoops_SRRCA)
				edge->_hoops_SSSHA = _hoops_HARCA;
			else
				edge->_hoops_SSSHA = _hoops_PARCA;
		}
		else
			edge->_hoops_SSSHA  = _hoops_PARCA;
		_hoops_GGGCA[fid] |= edge->_hoops_SSSHA;
 	}
}



#define _hoops_IARCA			0x1
#define _hoops_CARCA			0x2
#define _hoops_SARCA				0x3
#define _hoops_GPRCA			0x4

local const _hoops_IGRCR _hoops_RPRCA[] = {
	{_hoops_IARCA,		_hoops_GRRCR ("generate front"),	_hoops_RRRCR,	0, true},
	{_hoops_CARCA,		_hoops_GRRCR ("generate back"),		_hoops_RRRCR,	0, true},
	{_hoops_SARCA,			_hoops_GRRCR ("deviation"),			_hoops_SPPCR,	1, false},
	{_hoops_GPRCA,	_hoops_GRRCR ("last silhouettes"),	_hoops_APRCA,		1, false},
	{_hoops_GPRCA,	_hoops_GRRCR ("last silhouette"),	_hoops_APRCA,		1, false}
 };

local const _hoops_HPAGA _hoops_PPRCA = {
	_hoops_GGAPR (_hoops_RPRCA),
	_hoops_RPRCA,
};



struct _hoops_HPRCA {
	bool	_hoops_IPRCA;
	bool	_hoops_CPRCA;
	float	_hoops_SRRCA;
	int		_hoops_ARRCA;
};

local bool _hoops_SPRCA (
	_hoops_AIGPR *			_hoops_RIGC,
	char const *					option_string,
	struct _hoops_HPRCA *	_hoops_SHGAA)
{

	/* _hoops_ARP _hoops_SHIR _hoops_HSH _hoops_IH _hoops_HCR _hoops_IIGR _hoops_RH _hoops_GIGAA */
	_hoops_SHGAA->_hoops_IPRCA = true;
	_hoops_SHGAA->_hoops_CPRCA = true;
	_hoops_SHGAA->_hoops_SRRCA = 0.00001f;
	_hoops_SHGAA->_hoops_ARRCA = 1;
 	if (option_string == null)
		return false;

	_hoops_HIACR (_hoops_GHRCA, _hoops_RPRCA);

	Option_Value *	option_list = null;
	Option_Value *	option;

	if (!HI_Parse_Options (_hoops_RIGC, option_string, _hoops_CIACR (_hoops_GHRCA), &option_list, _hoops_SIACR))
		return false;

	if ((option = option_list) != null) do {
		switch (option->type->id) {
		  case _hoops_IARCA: {
			  if (option->_hoops_GCACR)
				_hoops_SHGAA->_hoops_IPRCA = false;
		  }	  break;
		  case _hoops_CARCA: {
			  if (option->_hoops_GCACR)
				  _hoops_SHGAA->_hoops_CPRCA = false;
				}	  break;
		  case _hoops_SARCA: {
			  _hoops_SHGAA->_hoops_SRRCA = option->value._hoops_PIPCR[0]; }
			break;
		  case _hoops_GPRCA: {
			  _hoops_SHGAA->_hoops_ARRCA = option->value._hoops_RIARA[0]; }
			break;
		}
	} while ((option = option->next) != null);

	HI_Free_Option_List (_hoops_RIGC, option_list);
	return true;
}


local void _hoops_RHRCA (
	Shell const *_hoops_SPHPR,
	Point const *_hoops_PAGIA,
	_hoops_CSSHA *_hoops_GGGCA,
	_hoops_CSSHA *_hoops_AHRCA,
	int *_hoops_PHRCA,
	Point *_hoops_HHRCA,
	int *_hoops_IHRCA,
	int *_hoops_CHRCA)
{
	int _hoops_ASPS = 0;
	int length;
	int i, j;
	int *src = _hoops_SPHPR->face_list;
	int *_hoops_PCAP = _hoops_CHRCA;
	int *_hoops_PHAS;

	ALLOC_ARRAY_CACHED (_hoops_PHAS, _hoops_SPHPR->point_count, int);
	SET_MEMORY (_hoops_PHAS, _hoops_SPHPR->point_count*sizeof(int), -1);
	for (i = 0; i < _hoops_SPHPR->face_count; i++) {
		length = src[0] + 1;
		ASSERT(length > 0);
		if (_hoops_GGGCA[i] != _hoops_AHRCA[i] ||
			BIT (_hoops_GGGCA[i], _hoops_PARCA)) {
			*_hoops_PCAP++ = *src;
			for (j = 1; j < length; j++) {
				if (_hoops_PHAS[src[j]] < 0) {
					_hoops_PHAS[src[j]] = _hoops_ASPS;
					_hoops_HHRCA[_hoops_ASPS] = _hoops_PAGIA[src[j]];
					_hoops_ASPS++;
				}
				*_hoops_PCAP++ = _hoops_PHAS[src[j]];
			}
		}
		src += length;
	}
	*_hoops_IHRCA = _hoops_PCAP - _hoops_CHRCA;
	*_hoops_PHRCA = _hoops_ASPS;
	FREE_ARRAY (_hoops_PHAS, _hoops_SPHPR->point_count, int);
}



local int _hoops_SHRCA (
	_hoops_AIGPR *	_hoops_RIGC,
	Key						shellkey,
	int						sweepcount,
	float const *			matrices,
	const char *			options,
	bool					_hoops_CHGCA = false,
	char const *			action = 0,
	char const *			start_seg = 0,
	int *					_hoops_SHGCA = 0,
	_hoops_SASC *			_hoops_HRRIA = 0)
{
	int i, _hoops_GIRCA;
  	int  _hoops_IIGCA;
	int *_hoops_HCGCA = null;
	int _hoops_IHRCA;
	int *_hoops_CHRCA = null;
	int _hoops_PHRCA;
	Point *_hoops_HHRCA;
 	Point *points;
 	struct _hoops_HPRCA	config;
	Point *_hoops_GGRCA;
	Point *_hoops_RIRCA;
	float const *_hoops_PIIAA;
	_hoops_ARPA *_hoops_AIRCA;
	_hoops_SIGIA *_hoops_IGGCA = 0;
	_hoops_IIGIA *_hoops_GCSHR = 0;
	_hoops_CSSHA *_hoops_GGGCA, *_hoops_AHRCA;

	if (_hoops_CHGCA)
		*_hoops_SHGCA = 0;
	Shell const *	_hoops_SPHPR = (Shell const *)_hoops_RCSSR (_hoops_RIGC, shellkey);
	ASSERT (_hoops_SPHPR->type == _hoops_SCIP);

	if (_hoops_SPHPR->point_count == 0)
		return false;

	_hoops_SPRCA(_hoops_RIGC, options, &config);



	if (_hoops_SPHPR->face_list == null)
		HI_Face_List_From_Tristrips(_hoops_RIGC, (Shell *) _hoops_SPHPR);
	if (!(_hoops_SPHPR->polyhedron_flags & PHF_FACE_NORMALS_VALID))
		HI_Assemble_Face_Normals ((Polyhedron alter *) _hoops_SPHPR);
	if (!(_hoops_SPHPR->polyhedron_flags & PHF_FACE_NORMALS_VALID))
		return false;

	/*_hoops_SSSHR _hoops_PHI _hoops_IIGR _hoops_SPPR _hoops_HRGR 3*_hoops_CIRGR, _hoops_HIS _hoops_CCPP _hoops_IRS _hoops_SCAH _hoops_CCA _hoops_RPPR _hoops_RRI _hoops_HSAR 2 _hoops_IACH _hoops_SGS*/
	ALLOC_ARRAY_CACHED (_hoops_GGRCA, _hoops_SPHPR->point_count, Point);	//_hoops_PIRCA
	ALLOC_ARRAY_CACHED (_hoops_RIRCA, _hoops_SPHPR->point_count, Point);	//_hoops_HIRCA
	ALLOC_ARRAY_CACHED (_hoops_HHRCA, _hoops_SPHPR->point_count, Point);	//_hoops_PIRCA
	ALLOC_ARRAY_CACHED (_hoops_AIRCA, _hoops_SPHPR->face_count, _hoops_ARPA);
	ALLOC_ARRAY_CACHED (_hoops_CHRCA, _hoops_SPHPR->face_list_length, int);
	ZALLOC_ARRAY_CACHED (_hoops_GGGCA, _hoops_SPHPR->face_count, _hoops_CSSHA);
	ALLOC_ARRAY_CACHED (_hoops_AHRCA, _hoops_SPHPR->face_count, _hoops_CSSHA);

	_hoops_GCSHR = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_IIGIA)(_hoops_RIGC->memory_pool);
	_hoops_IGGCA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_SIGIA)(_hoops_RIGC->memory_pool, 8 * _hoops_SPHPR->point_count);

	_hoops_IRRCA(_hoops_SPHPR, _hoops_IGGCA, _hoops_GCSHR);

	_hoops_CGGCA *_hoops_SGGCA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_CGGCA)(_hoops_RIGC->memory_pool);
	for (_hoops_GIRCA=0; _hoops_GIRCA<sweepcount-1; _hoops_GIRCA++) {
		_hoops_PIIAA = &matrices[_hoops_GIRCA*16];
		HI_Compute_Transformed_Points(_hoops_SPHPR->point_count, _hoops_SPHPR->points, _hoops_PIIAA,_hoops_GGRCA);
		HI_Compute_Transformed_Points(_hoops_SPHPR->point_count, _hoops_SPHPR->points, _hoops_PIIAA+16,_hoops_RIRCA);

		HI_Compute_Transformed_Planes2(_hoops_SPHPR->face_count, _hoops_SPHPR->local_face_attributes.normals,
										_hoops_PIIAA, _hoops_AIRCA);

		_hoops_CRRCA(_hoops_GGRCA, _hoops_RIRCA, _hoops_AIRCA, _hoops_GCSHR, _hoops_GGGCA, config._hoops_SRRCA);
 		int _hoops_IIRCA = _hoops_RRRCA(_hoops_GCSHR, _hoops_SGGCA, config._hoops_ARRCA);
		if (_hoops_GIRCA != 0) {
			_hoops_RHRCA (_hoops_SPHPR, _hoops_GGRCA, _hoops_GGGCA, _hoops_AHRCA,
						&_hoops_PHRCA, _hoops_HHRCA, &_hoops_IHRCA, _hoops_CHRCA);
			if (_hoops_CHGCA)
				*_hoops_SHGCA+= _hoops_RASIA(_hoops_RIGC, action, start_seg, _hoops_PHRCA, _hoops_HHRCA, _hoops_IHRCA, _hoops_CHRCA,"",_hoops_HRRIA);
			else
				HC_Insert_Shell(_hoops_PHRCA, _hoops_HHRCA, _hoops_IHRCA, _hoops_CHRCA);
		}

		if (_hoops_IIRCA) {
			_hoops_IIGCA = _hoops_IIRCA *  5;
			ALLOC_ARRAY_CACHED (points, _hoops_IIRCA * 4, Point);
			ALLOC_ARRAY_CACHED (_hoops_HCGCA, _hoops_IIGCA, int);
			_hoops_SGGCA->ResetCursor();
			for (i=0; i<_hoops_IIRCA; i++) {
				int *_hoops_GRGCA;
				_hoops_GRGCA = _hoops_SGGCA->PeekCursor();
				if (!_hoops_GRGCA)
					break;
				points[i*4] = _hoops_GGRCA[ _hoops_GRGCA[0] ];		//_hoops_SCGR _hoops_RSGA
				points[i*4+1] = _hoops_GGRCA[ _hoops_GRGCA[1] ];	//_hoops_SCGR _hoops_RSGA
				points[i*4+2] = _hoops_RIRCA[ _hoops_GRGCA[1] ];	//_hoops_SPS _hoops_RSGA
				points[i*4+3] = _hoops_RIRCA[ _hoops_GRGCA[0] ];	//_hoops_SPS _hoops_RSGA
				_hoops_SGGCA->AdvanceCursor();
				_hoops_HCGCA[i*5] = 4;
				_hoops_HCGCA[i*5+1] = i*4;
				_hoops_HCGCA[i*5+2] = i*4+1;
				_hoops_HCGCA[i*5+3] = i*4+2;
				_hoops_HCGCA[i*5+4] = i*4+3;
			}

			if (_hoops_CHGCA)
				*_hoops_SHGCA+= _hoops_RASIA(_hoops_RIGC, action, start_seg, _hoops_IIRCA * 4 , points, _hoops_IIGCA, _hoops_HCGCA,"", _hoops_HRRIA);
			else
				HC_Insert_Shell(_hoops_IIRCA * 4, points, _hoops_IIGCA, _hoops_HCGCA);

			if (points) {
  				FREE_ARRAY (points,  _hoops_IIRCA * 4, Point);
				points = null;
			}
			if (_hoops_HCGCA) {
 				FREE_ARRAY (_hoops_HCGCA, _hoops_IIGCA, int);
				_hoops_HCGCA = null;
			}
		}

		if (_hoops_GIRCA == 0 && config._hoops_IPRCA && (!_hoops_CHGCA || *_hoops_SHGCA == 0 || _hoops_HRRIA)) {
			if (_hoops_CHGCA)
				*_hoops_SHGCA+= _hoops_RASIA(_hoops_RIGC, action, start_seg, _hoops_SPHPR->point_count, _hoops_GGRCA, ((Shell const *)_hoops_SPHPR)->face_list_length,  ((Shell const *)_hoops_SPHPR)->face_list,"",_hoops_HRRIA);
			else
				HC_Insert_Shell(_hoops_SPHPR->point_count,_hoops_GGRCA,((Shell const *)_hoops_SPHPR)->face_list_length, ((Shell const *)_hoops_SPHPR)->face_list);
		}
		if ((_hoops_GIRCA == sweepcount -2) && config._hoops_CPRCA && (!_hoops_CHGCA || *_hoops_SHGCA == 0 || _hoops_HRRIA)) {
			if (_hoops_CHGCA)
				*_hoops_SHGCA+= _hoops_RASIA(_hoops_RIGC, action, start_seg, _hoops_SPHPR->point_count, _hoops_RIRCA, ((Shell const *)_hoops_SPHPR)->face_list_length,  ((Shell const *)_hoops_SPHPR)->face_list,"",_hoops_HRRIA);
			else
				HC_Insert_Shell(_hoops_SPHPR->point_count,_hoops_RIRCA,((Shell const *)_hoops_SPHPR)->face_list_length, ((Shell const *)_hoops_SPHPR)->face_list);
		}

		int *_hoops_GRGCA;
		while ((_hoops_GRGCA = _hoops_SGGCA->RemoveFirst()) != null)
			FREE_ARRAY(_hoops_GRGCA,2,int);

		if (_hoops_CHGCA && (*_hoops_SHGCA > 0 && !_hoops_HRRIA))
			break;

		//_hoops_GGSHR _hoops_RH _hoops_GSSIA _hoops_PSCA, _hoops_PSCR _hoops_AHHR _hoops_GGSR _hoops_RH _hoops_CCAH _hoops_SPR
		_hoops_CSSHA *temp = _hoops_GGGCA;
		_hoops_GGGCA = _hoops_AHRCA;
		_hoops_AHRCA = temp;
		ZERO_ARRAY (_hoops_GGGCA, _hoops_SPHPR->face_count, _hoops_CSSHA);
	}
	delete _hoops_SGGCA;
	

 	FREE_ARRAY (_hoops_GGRCA, _hoops_SPHPR->point_count, Point);
	FREE_ARRAY (_hoops_RIRCA, _hoops_SPHPR->point_count, Point);
	FREE_ARRAY (_hoops_HHRCA, _hoops_SPHPR->point_count, Point);
	FREE_ARRAY (_hoops_AIRCA, _hoops_SPHPR->face_count, _hoops_ARPA);
	FREE_ARRAY (_hoops_CHRCA, _hoops_SPHPR->face_list_length, int);
	FREE_ARRAY (_hoops_GGGCA, _hoops_SPHPR->face_count, _hoops_CSSHA);
	FREE_ARRAY (_hoops_AHRCA, _hoops_SPHPR->face_count, _hoops_CSSHA);


	_hoops_ISSHA *edge;
	while ((edge = _hoops_GCSHR->RemoveFirst()) != null)
		FREE(edge,_hoops_ISSHA);

	delete _hoops_GCSHR;
	delete _hoops_IGGCA;
	return true;
}







/* _hoops_SIGP: _hoops_IHIS _hoops_IS _hoops_IRS _hoops_GIAH _hoops_RGHR */
HC_INTERFACE void HC_Compute_Swept_Shell_Along_P (
		Key					shellkey,
		int					sweepcount,
		float const *		matrices,
		char const *		options)
{
	_hoops_PAPPR context("Compute_Swept_Shell_Along_P");

	CODE_GENERATION (
		int i;
		HI_Dump_Code (Sprintf_D (null, "{float* matrix_data = (float*) malloc(sizeof(float)*%d);\n", sweepcount * 16));
		++HOOPS_WORLD->_hoops_ISPPR;
		for (i = 0; i < sweepcount * 16; i++) {
			HI_Dump_Code (_hoops_CHCHR (null, "matrix_data[%d] = %f;\n", i, matrices[i]));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_Compute_Swept_Shell_Along_Path (LOOKUP (%D),", shellkey));
		HI_Dump_Code (Sprintf_D (null, "%d, matrix_data,", sweepcount));
		HI_Dump_Code (Sprintf_S (null, "%S);\n", options));

		HI_Dump_Code ("free (matrix_data);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	UNREFERENCED(options);
	_hoops_CSPPR();
	_hoops_SHRCA(context, shellkey, sweepcount, matrices, options);
	_hoops_IRRPR();
}




HC_INTERFACE Key HC_Compute_Swept_Shell (
	Key					shellkey,
	Point const *		direction_in,
	Key *				front_key,
	Key *				back_key,
	Key *				side_key,
	char const *		options)
{
	_hoops_PAPPR context("Compute_Swept_Shell");

	Key _hoops_CHSSR;

	_hoops_CSPPR();
	int status = _hoops_HHGCA (context, shellkey,
										(Vector const*)direction_in,
										&_hoops_CHSSR, back_key, side_key,
										_hoops_AGGR(options, "merge"));
	_hoops_IRRPR();

	if (front_key != null)
		*front_key = _hoops_CHSSR;

	CODE_GENERATION (
		HI_Dump_Code ("{");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("HC_POINT direction;\n");
		HI_Dump_Code ("HC_KEY front, back, side;\n");
		HI_Dump_Code (Sprintf_FF (null, "direction.x = %.6ff;  direction.y = %.6ff;	 ", direction_in->x, direction_in->y));
		HI_Dump_Code (Sprintf_F (null, "direction.z = %.6ff;\n", direction_in->z));
		HI_Dump_Code (Sprintf_LD (null, "HC_Compute_Swept_Shell (LOOKUP (%D), direction, &front, &back, &side, ", shellkey));
		HI_Dump_Code (Sprintf_S (null, "%S);\n", options));
		if (front_key)
			HI_Dump_Code (Sprintf_LD (null, "DEFINE (front, %D);", *front_key));
		if (back_key)
			HI_Dump_Code (Sprintf_LD (null, "DEFINE (back, %D);", *back_key));
		if (front_key)
			HI_Dump_Code (Sprintf_LD (null, "DEFINE (side, %D);", *side_key));
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	if (status)
		return _hoops_CHSSR;
	else
		return _hoops_SHSSR;
}






static int _hoops_CIRCA (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *		action,
	char const *		start_seg,
	Key					key,
	int					sweepcount,
	float const *		matrices,
	char const *		options,
	float *				_hoops_HRRIA
	)
{

	int _hoops_SHGCA = 0;
	int i = 0;
	if (sweepcount == 2) {
		for (i=0; i<12; i++)
			if (matrices[i+16]!=0)
				break;
	}

 	if (_hoops_HRRIA)
	{
		_hoops_HRRIA[0] = _hoops_HRRIA[1] = _hoops_HRRIA[2]  = MAX_FLOAT;
		_hoops_HRRIA[3] = _hoops_HRRIA[4] = _hoops_HRRIA[5]  = -MAX_FLOAT;
 	}
	_hoops_CSPPR();
	if (sweepcount == 2 && i==12) {
		Vector direction;
		direction.x = matrices[28];
		direction.y = matrices[29];
		direction.z = matrices[30];
 		_hoops_HHGCA(_hoops_RIGC, key, &direction,0,0,0,true,matrices,true,action, start_seg,&_hoops_SHGCA,(HOOPS::_hoops_SASC *)_hoops_HRRIA);
	}
	else {
  		_hoops_SHRCA (_hoops_RIGC, key, sweepcount, matrices,options,true, action, start_seg, &_hoops_SHGCA, (HOOPS::_hoops_SASC *)_hoops_HRRIA);
	}
	_hoops_IRRPR();

	return _hoops_SHGCA;
}



HC_INTERFACE int HC_Compute_Selection_By_Swept_S (
	char const *		action,
	char const *		start_seg,
	Key					key,
	int					sweepcount,
	float const *		matrices,
	char const *		options)
{
	_hoops_PAPPR context("Compute_Selection_By_Swept_S");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_D (null, "{float* matrix_data = (float*) malloc(sizeof(float)*%d);\n", sweepcount * 16));
		++HOOPS_WORLD->_hoops_ISPPR;
		for (int i = 0; i < sweepcount * 16; i++) {
			HI_Dump_Code (_hoops_CHCHR (null, "matrix_data[%d] = %f;\n", i, matrices[i]));
		}
		HI_Dump_Code (Sprintf_SS (null, "Compute_Selection_By_Swept_Shell (%S, %S, ", action, start_seg));
		HI_Dump_Code (Sprintf_LD (null, "LOOKUP (%D),", key));
		HI_Dump_Code (Sprintf_D (null, "%d, matrix_data,", sweepcount));
		HI_Dump_Code (Sprintf_S (null, "%S);\n", options));
		HI_Dump_Code ("free (matrix_data);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	return _hoops_CIRCA(context, action, start_seg, key, sweepcount, matrices, options,null);
}


HC_INTERFACE int HC_Compute_Selection_By_Swept_2 (
	char const *		action,
	char const *		start_seg,
	Key					key,
	int					sweepcount,
	float const *		matrices,
	char const *		options,
	float *				bounding_box
	)
{
	_hoops_PAPPR context("Compute_Selection_By_Swept_S");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_D (null, "{float* matrix_data = (float*) malloc(sizeof(float)*%d);\n", sweepcount * 16));
		++HOOPS_WORLD->_hoops_ISPPR;
		for (int i = 0; i < sweepcount * 16; i++) {
			HI_Dump_Code (_hoops_CHCHR (null, "matrix_data[%d] = %f;\n", i, matrices[i]));
		}
		HI_Dump_Code (Sprintf_SS (null, "Compute_Selection_By_Swept_Shell (%S, %S, ", action, start_seg));
		HI_Dump_Code (Sprintf_LD (null, "LOOKUP (%D),", key));
		HI_Dump_Code (Sprintf_D (null, "%d, matrix_data,", sweepcount));
		HI_Dump_Code (Sprintf_S (null, "%S);\n", options));
		HI_Dump_Code ("free (matrix_data);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	return _hoops_CIRCA(context, action, start_seg, key, sweepcount, matrices, options,bounding_box);
}






#else

GLOBAL_FUNCTION void HI_Begin_Shell_Selection (
	_hoops_AIGPR	*_hoops_RIGC)
{
}
GLOBAL_FUNCTION void HI_End_Shell_Selection (
	_hoops_AIGPR	*_hoops_RIGC)
{
}
GLOBAL_FUNCTION void HI_Delete_Shell_Selection_Cache (void *_hoops_CSC) {
	_hoops_IRPPR ("Selection By Shell");
}
HC_INTERFACE void HC_Begin_Shell_Selection () {
	_hoops_IRPPR ("Selection By Shell");
}
HC_INTERFACE void HC_End_Shell_Selection () {
	_hoops_IRPPR ("Selection By Shell");
}
HC_INTERFACE int HC_Compute_Selection_By_Shell (
						char const *action,
						char const *start_seg,
						int point_count,
						Point const *points,
						int face_list_length,
						int const *face_list) {
	_hoops_IRPPR ("Selection By Shell");
	return 0;
}
HC_INTERFACE int HC_Compute_Selection_By_Ray (
						char const *action,
						char const *start_seg,
						Point const *start,
						Point const *direction)
{
	_hoops_IRPPR ("Selection By Shell");
	return 0;
}
HC_INTERFACE int HC_Compute_Selection_By_Key (
	char const *	action,
	char const *	start_seg,
	Key				key,
	float const	*	_hoops_CASPA)
{
	_hoops_IRPPR ("Selection By Shell");
	return 0;
}
HC_INTERFACE int HC_Compute_Selection_By_Sh_W_Op (
						char const *action,
						char const *start_seg,
						int point_count,
						Point const *points,
						int face_list_length,
						int const *face_list,
						const char *options)
{
	_hoops_IRPPR ("Selection By Shell");
	return 0;
}
HC_INTERFACE float HC_Compute_Selection_Dist_By_Sh (
						char const *action,
						char const *start_seg,
						int point_count,
						Point const *points,
						int face_list_length,
						int const *face_list,
						const char *options
						)
{
	_hoops_IRPPR ("Selection By Shell");
	return -1;
}
HC_INTERFACE void HC_Compute_Swept_Shell_Along_P (
		Key					shellkey,
		int					sweepcount,
		float const *		matrices,
		char const *		options)
{
	_hoops_IRPPR ("Selection By Shell");
}
HC_INTERFACE int HC_Compute_Swept_Shell (
	Key					shellkey,
	Point const *		direction_in,
	Key *				front_key,
	Key *				back_key,
	Key *				side_key,
	char const *		options)
{
	_hoops_IRPPR ("Selection By Shell");
	return 0;
}
HC_INTERFACE int HC_Compute_Selection_By_Swept_S (
	char const *		action,
	char const *		start_seg,
	Key					key,
	int					sweepcount,
	float const *		matrices,
	char const *		options)
{
	_hoops_IRPPR ("Selection By Shell");
	return 0;
}
HC_INTERFACE int HC_Compute_Selection_By_Swept_2 (
	char const *		action,
	char const *		start_seg,
	Key					key,
	int					sweepcount,
	float const *		matrices,
	char const *		options)
{
	_hoops_IRPPR ("Selection By Shell");
	return 0;
}

#endif /* _hoops_CHS _hoops_SCHPA */



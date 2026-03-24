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
 * $Id: obf_tmp.txt 1.55 2010-06-16 22:04:10 covey Exp $
 */

#ifndef _hoops_IGPAS

Begin_HOOPS_Namespace

struct Window_Tree {
	_hoops_ACCCP alter *	_hoops_APHHP;
	Window_Tree alter *			_hoops_CGPAS;
	Window_Tree alter *			_hoops_ICHSP;
	Window_Tree alter *			_hoops_SCAAR;
	_hoops_CRCP const *				_hoops_SRCP;
	bool						_hoops_SGPAS;
	Subsegment const *			_hoops_GIPIA;				// _hoops_IH _hoops_GPAPA _hoops_GRPAS
	_hoops_PACIR			window;
	_hoops_PACIR			_hoops_RRPAS;		// _hoops_RAS _hoops_RRISP _hoops_RHSI
	_hoops_ACHR					_hoops_AAICA,
								restricted_selectability,
								_hoops_PHARP,
								_hoops_RGP;
	_hoops_PIGRA				locks;			// _hoops_CISI _hoops_SGHS
	_hoops_PIGRA				_hoops_HHGIP;	// _hoops_PPGP _hoops_SGHS (_hoops_RPSI _hoops_SSSCP _hoops_AGRP)
};

typedef int		_hoops_ARPAS;

#define _hoops_RHCAH			(_hoops_ARPAS)0x0001
#define _hoops_RSCAH		(_hoops_ARPAS)0x0002
#define _hoops_IICAH		(_hoops_ARPAS)0x0004
#define _hoops_PRPAS			(_hoops_ARPAS)0x0008
#define _hoops_HRPAS (_hoops_ARPAS)0x0010
#define _hoops_IRPAS	(_hoops_ARPAS)0x0020
#define _hoops_CRPAS			(_hoops_ARPAS)0x0040


struct _hoops_ICCAH {
	_hoops_ICCAH	 *	next;
	_hoops_CRCP const *				segment;
	float						_hoops_RCSAP,
								_hoops_HCSAP;
	_hoops_ACHR					_hoops_SCCAH;
	bool						valid;
};



#define _hoops_SRPAS	1
#define _hoops_GAPAS	2

struct _hoops_ACCCP {
	Display_Context alter *		_hoops_SRA;
	Selection_Event alter *		event;

	float						xw,
								yw;

	float						_hoops_GICAH;	// _hoops_GGR _hoops_SRPGH? (_hoops_RRAHA!)
	XY							_hoops_RICAH;

	_hoops_PGCIR						bounding;
	Point						_hoops_AICAH;

	int							count;

	Point alter *				_hoops_RAPAS;
	Vector alter *				_hoops_AAPAS;
	float alter *				_hoops_PAPAS;
	Point						_hoops_GPIS;
	_hoops_RGASA alter *			_hoops_HAPAS;
	bool						_hoops_IAPAS;
	int							_hoops_CAPAS;
	_hoops_GPCIH alter * alter *		_hoops_SAPAS;

	_hoops_ARPAS			options;
	_hoops_RISAP alter *		_hoops_ASCAH;
	_hoops_ICCAH *	_hoops_HCCAH;
	int							_hoops_GCCAH;
	int							_hoops_GCCIA;
	XY							_hoops_HICAH;
	bool						_hoops_GHPPI;
	bool						_hoops_GSCAH;

	bool						_hoops_GPPAS;

	void alter *				_hoops_AICCP;				// _hoops_RIH-_hoops_RHIR _hoops_IIGR _hoops_IHH _hoops_PIH

	struct {
		Geometry const *		_hoops_RAI;	// _hoops_IH _hoops_CICAR _hoops_GHSHA
		int						_hoops_PHGGH;
		float					_hoops_HHGGH, _hoops_IHGGH;
		int						_hoops_CHGGH;
		int						_hoops_RPPAS;
		bool					_hoops_CIHIA;
		_hoops_AISAP *		_hoops_ACSAP;
		_hoops_AISAP **		_hoops_APPAS;
		int						_hoops_PPPAS;
	}							_hoops_HPPAS;

};



#ifndef _hoops_IPPAS
#include "tandt.h"
#endif

struct _hoops_CPPAS {
	float						_hoops_HISAP;
	DC_Point const *			vertex1;
	DC_Point const *			vertex2;
	int							face;
	float						_hoops_RCSAP;
};

struct _hoops_PCCCP {
	_hoops_ACCCP *		sc;
	Polyhedron const *		_hoops_IPRI;

	DC_Point *				_hoops_CGCAR;
	float *					ws;
	_hoops_GRCAR *				_hoops_RRCAR;

	_hoops_CPPAS					_hoops_SPPAS,
								_hoops_GHPAS,
								_hoops_CCCCP,
								_hoops_RHPAS;
	bool						_hoops_AHPAS,
								_hoops_PHPAS,
								_hoops_HHPAS,
								_hoops_IHPAS;
	_hoops_AISAP			*_hoops_ACSAP;
	_hoops_AISAP			**_hoops_APPAS;
	int							_hoops_PPPAS;
	bool						_hoops_CHPAS;
	bool						_hoops_SHPAS;
};

End_HOOPS_Namespace;

#define _hoops_IGPAS
#endif

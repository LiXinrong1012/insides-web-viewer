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
 * $Id: obf_tmp.txt 1.198 2011-01-08 00:54:14 jason Exp $
 */

#include "hoops.h"
#include "hversion.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


/* _hoops_ICIPP _hoops_ASSS _hoops_IHHH _hoops_IS _hoops_SGH _hoops_RH "_hoops_IGRH" _hoops_HSH _hoops_IH _hoops_RH _hoops_RII _hoops_AAP */
#define _hoops_CCIPP						-1
#define _hoops_SCIPP					-2
#define _hoops_GSIPP						-3
#define _hoops_RSIPP				-4
#define _hoops_ASIPP			-5
#define _hoops_PSIPP				-6
#define _hoops_HSIPP				-7
#define _hoops_ISIPP				-8
#define _hoops_CSIPP		-9
#define _hoops_SSIPP						-10
#define _hoops_GGCPP			-11
#define _hoops_RGCPP			-12
#define _hoops_AGCPP		-13
#define _hoops_PGCPP					-14
#define _hoops_HGCPP		-15
#define _hoops_IGCPP				-16
#define _hoops_CGCPP		-17
#define _hoops_SGCPP				-18
#define _hoops_GRCPP				-19
#define _hoops_RRCPP					-20
#define _hoops_ARCPP			-21
#define _hoops_PRCPP			-22
#define _hoops_HRCPP				-23
#define _hoops_IRCPP				-24
#define _hoops_CRCPP   -25
#define _hoops_SRCPP			-26
#define _hoops_GACPP					-27
#define _hoops_RACPP						-28
#define _hoops_AACPP				-29
#define _hoops_PACPP	-30
#define _hoops_HACPP		-31
#define _hoops_IACPP			-32
#define _hoops_CACPP			-33
#define _hoops_SACPP			-99

#define	_hoops_GPCPP	1
#define	_hoops_RPCPP			2


#define _hoops_APCPP		-1
#define _hoops_PPCPP			-2
#define _hoops_HPCPP				-3


local const _hoops_IGRCR _hoops_IPCPP[] = {
	{_hoops_CPCPP|_hoops_SPCPP,		_hoops_GRRCR ("air"),			_hoops_RRRCR, 0, true},
	{_hoops_CPCPP|_hoops_SPCPP,		_hoops_GRRCR ("a.i.r."),		_hoops_RRRCR, 0, true},
	{_hoops_GHCPP|_hoops_SPCPP,		_hoops_GRRCR ("im"),			_hoops_RRRCR, 0, true},
	{_hoops_GHCPP|_hoops_SPCPP,		_hoops_GRRCR ("i.m."),			_hoops_RRRCR, 0, true},
	{_hoops_RHCPP|_hoops_SPCPP,		_hoops_GRRCR ("kanji"),			_hoops_RRRCR, 0, true},
	{_hoops_SPCPP,					_hoops_GRRCR ("classic"),		_hoops_RRRCR, 0, true},
	{_hoops_AHCPP,						_hoops_GRRCR ("hsf"),			_hoops_RRRCR, 0, true},
};

local const _hoops_HPAGA _hoops_PHCPP = {
	_hoops_GGAPR (_hoops_IPCPP),	_hoops_IPCPP,
};

local const _hoops_IGRCR _hoops_HHCPP[] = {
	{_hoops_APCPP,	_hoops_GRRCR ("customer"),		_hoops_PRRCR, 1, false},
	{_hoops_APCPP,	_hoops_GRRCR ("user"),			_hoops_PRRCR, 1, false},
	{_hoops_APCPP,	_hoops_GRRCR ("company"),		_hoops_PRRCR, 1, false},
	{_hoops_PPCPP,	_hoops_GRRCR ("product"),		_hoops_GHAGA, -999, false,
														&_hoops_PHCPP},
	{_hoops_PPCPP,	_hoops_GRRCR ("products"),		_hoops_GHAGA, -999, false,
														&_hoops_PHCPP},
	{_hoops_PPCPP,	_hoops_GRRCR ("package"),		_hoops_GHAGA, -999, false,
														&_hoops_PHCPP},
	{_hoops_PPCPP,	_hoops_GRRCR ("packages"),		_hoops_GHAGA, -999, false,
														&_hoops_PHCPP},
	{_hoops_HPCPP,		_hoops_GRRCR ("key"),			_hoops_PRRCR, 1, false},
};

local const _hoops_HPAGA _hoops_IHCPP = {
	_hoops_GGAPR (_hoops_HHCPP),	_hoops_HHCPP,
};


#define _hoops_CHCPP		0
#define _hoops_SHCPP		1

local const _hoops_IGRCR _hoops_GICPP[] = {
	{_hoops_CHCPP,	_hoops_GRRCR ("off"),			_hoops_RRRCR, 0, false},
	{_hoops_CHCPP,	_hoops_GRRCR ("no"),			_hoops_RRRCR, 0, false},
	{_hoops_CHCPP,	_hoops_GRRCR ("false"),			_hoops_RRRCR, 0, false},
	{_hoops_CHCPP,	_hoops_GRRCR ("none"),			_hoops_RRRCR, 0, false},

	{_hoops_SHCPP,	_hoops_GRRCR ("low"),			_hoops_RRRCR, 0, false},
	{_hoops_SHCPP,	_hoops_GRRCR ("basic"),			_hoops_RRRCR, 0, false},
	{_hoops_SHCPP,	_hoops_GRRCR ("minimum"),		_hoops_RRRCR, 0, false},

	{_hoops_SHCPP,	_hoops_GRRCR ("on"),			_hoops_RRRCR, 0, false},
	{_hoops_SHCPP,	_hoops_GRRCR ("yes"),			_hoops_RRRCR, 0, false},
	{_hoops_SHCPP,	_hoops_GRRCR ("true"),			_hoops_RRRCR, 0, false},
	{_hoops_SHCPP,	_hoops_GRRCR ("full"),			_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_RICPP = {
	_hoops_GGAPR (_hoops_GICPP),		_hoops_GICPP,
};


local const _hoops_IGRCR _hoops_AICPP[] = {
	{_hoops_PICPP,		_hoops_GRRCR ("off"),			_hoops_RRRCR, 0, false},
	{_hoops_PICPP,		_hoops_GRRCR ("no"),			_hoops_RRRCR, 0, false},
	{_hoops_PICPP,		_hoops_GRRCR ("false"),			_hoops_RRRCR, 0, false},
	{_hoops_PICPP,		_hoops_GRRCR ("none"),			_hoops_RRRCR, 0, false},

	{_hoops_HICPP, _hoops_GRRCR ("on"),			_hoops_RRRCR, 0, false},
	{_hoops_HICPP, _hoops_GRRCR ("yes"),			_hoops_RRRCR, 0, false},
	{_hoops_HICPP, _hoops_GRRCR ("true"),		_hoops_RRRCR, 0, false},
	{_hoops_HICPP, _hoops_GRRCR ("everything"),	_hoops_RRRCR, 0, false},

	{_hoops_SRRIR,		_hoops_GRRCR ("face list"), _hoops_RRRCR, 0, true},
	{_hoops_SRRIR,		_hoops_GRRCR ("face lists"), _hoops_RRRCR, 0, true},
	{_hoops_IICPP, _hoops_GRRCR ("facings"),	_hoops_RRRCR, 0, true},
	{_hoops_IICPP, _hoops_GRRCR ("facing"),	_hoops_RRRCR, 0, true},
	{_hoops_AHSSR,	_hoops_GRRCR ("circles"),	_hoops_RRRCR, 0, true},
	{_hoops_AHSSR,	_hoops_GRRCR ("circle"),	_hoops_RRRCR, 0, true},
	{_hoops_IGGHR,			_hoops_GRRCR ("polyedges"),	_hoops_RRRCR, 0, true},
	{_hoops_IGGHR,			_hoops_GRRCR ("polyedge"),	_hoops_RRRCR, 0, true},
};

local const _hoops_HPAGA _hoops_CICPP = {
	_hoops_GGAPR (_hoops_AICPP), _hoops_AICPP,
};


local const _hoops_IGRCR _hoops_SICPP[] = {
	{_hoops_GCCPP,		_hoops_GRRCR ("off"),			_hoops_ARSAP, -999, false},
	{_hoops_GCCPP,		_hoops_GRRCR ("disable"),		_hoops_ARSAP, -999, false},
	{_hoops_GCCPP,		_hoops_GRRCR ("no"),			_hoops_RRRCR,      0, false},
	{_hoops_GCCPP,		_hoops_GRRCR ("false"),			_hoops_RRRCR,      0, false},
	{_hoops_GCCPP,		_hoops_GRRCR ("none"),			_hoops_RRRCR,      0, false},

	{_hoops_RCCPP,		_hoops_GRRCR ("on"),			_hoops_ARSAP, -999, false},
	{_hoops_RCCPP,		_hoops_GRRCR ("enable"),		_hoops_ARSAP, -999, false},
	{_hoops_RCCPP,		_hoops_GRRCR ("yes"),			_hoops_RRRCR,      0, false},
	{_hoops_RCCPP,		_hoops_GRRCR ("true"),			_hoops_RRRCR,      0, false},
	{_hoops_RCCPP,		_hoops_GRRCR ("everything"),	_hoops_RRRCR,      0, false},

	{_hoops_ACCPP,	_hoops_GRRCR ("once"),			_hoops_ARSAP, -999, true},
};

local const _hoops_HPAGA _hoops_PCCPP = {
	_hoops_GGAPR (_hoops_SICPP), _hoops_SICPP,
};


local const _hoops_IGRCR _hoops_HCCPP[] = {
	{_hoops_GPCPP,		_hoops_GRRCR ("definition set"),	_hoops_RRRCR,      0, true},
	{_hoops_RPCPP,				_hoops_GRRCR ("thread"),			_hoops_RRRCR,      0, true},

	{_hoops_GPCPP |
	 _hoops_RPCPP,				_hoops_GRRCR ("all"),				_hoops_RRRCR,      0, false},
	{_hoops_GPCPP |
	 _hoops_RPCPP,				_hoops_GRRCR ("on"),				_hoops_RRRCR,      0, false},
	{_hoops_GPCPP |
	 _hoops_RPCPP,				_hoops_GRRCR ("yes"),				_hoops_RRRCR,      0, false},
	{_hoops_GPCPP |
	 _hoops_RPCPP,				_hoops_GRRCR ("true"),				_hoops_RRRCR,      0, false},
	{0,									_hoops_GRRCR ("none"),				_hoops_RRRCR,      0, false},
	{0,									_hoops_GRRCR ("off"),				_hoops_RRRCR,      0, false},
	{0,									_hoops_GRRCR ("no"),				_hoops_RRRCR,      0, false},
	{0,									_hoops_GRRCR ("false"),				_hoops_RRRCR,      0, false},
};

local const _hoops_HPAGA _hoops_ICCPP = {
	_hoops_GGAPR (_hoops_HCCPP), _hoops_HCCPP,
};


#define _hoops_CCCPP	0x1
#define _hoops_SCCPP		0x2
#define _hoops_GSCPP		0x4

local const _hoops_IGRCR _hoops_RSCPP[] = {
	{_hoops_CCCPP, _hoops_GRRCR (""),			 _hoops_RRRCR, 0, false},
	{_hoops_CCCPP, _hoops_GRRCR ("bytes"),	 _hoops_RRRCR, 0, false},
	{_hoops_SCCPP,	 _hoops_GRRCR ("kb"),		 _hoops_RRRCR, 0, false},
	{_hoops_SCCPP,	 _hoops_GRRCR ("kilobytes"), _hoops_RRRCR, 0, false},
	{_hoops_GSCPP,	 _hoops_GRRCR ("mb"),		 _hoops_RRRCR, 0, false},
	{_hoops_GSCPP,	 _hoops_GRRCR ("megabytes"), _hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_ASCPP = {
	_hoops_GGAPR (_hoops_RSCPP),
	_hoops_RSCPP,
};



local const _hoops_IGRCR _hoops_PSCPP[] = {
	{_hoops_RSIPP,						_hoops_GRRCR ("fatal error"),			_hoops_GHAGA, -9, true, &_hoops_PCCPP},
	{_hoops_GSIPP,							_hoops_GRRCR ("error"),					_hoops_GHAGA, -9, true, &_hoops_PCCPP},
	{_hoops_SCIPP,							_hoops_GRRCR ("warning"),				_hoops_GHAGA, -9, true, &_hoops_PCCPP},
	{_hoops_CCIPP,							_hoops_GRRCR ("info"),					_hoops_GHAGA, -9, true, &_hoops_PCCPP},
	{_hoops_CCIPP,							_hoops_GRRCR ("informational"),			_hoops_GHAGA, -9, true, &_hoops_PCCPP},
	{_hoops_RSIPP,						_hoops_GRRCR ("fatal errors"),			_hoops_GHAGA, -9, true, &_hoops_PCCPP},
	{_hoops_GSIPP,							_hoops_GRRCR ("errors"),				_hoops_GHAGA, -9, true, &_hoops_PCCPP},
	{_hoops_SCIPP,							_hoops_GRRCR ("warnings"),				_hoops_GHAGA, -9, true, &_hoops_PCCPP},
	{_hoops_CCIPP,							_hoops_GRRCR ("infos"),					_hoops_GHAGA, -9, true, &_hoops_PCCPP},
	{_hoops_CCIPP,							_hoops_GRRCR ("informationals"),		_hoops_GHAGA, -9, true, &_hoops_PCCPP},

	{_hoops_PSIPP,						_hoops_GRRCR ("application"),			_hoops_PRRCR,	1, false},
	{_hoops_ASIPP,					_hoops_GRRCR ("c string length"),		_hoops_APRCA,		1, true},
	{_hoops_SSIPP,							_hoops_GRRCR ("debug"),					_hoops_APRCA,		1, true},
	{_hoops_GRCPP,						_hoops_GRRCR ("clear debug"),			_hoops_APRCA,		1, false},
	{_hoops_RRCPP,						_hoops_GRRCR ("set debug"),				_hoops_APRCA,		1, false},
	{_hoops_HSIPP,					_hoops_GRRCR ("event checker"),			_hoops_PRRCR,	1, true},
	{_hoops_ISIPP,					_hoops_GRRCR ("message limit"),			_hoops_APRCA,		1, true},
	{_hoops_CSIPP,			_hoops_GRRCR ("string history limit"),	_hoops_APRCA,		1, true},
	{_hoops_HGCPP,				_hoops_GRRCR ("processor override"),	_hoops_APRCA,		1, true},

	{_hoops_GGCPP,					_hoops_GRRCR ("font directory"),			_hoops_PRRCR,	-999, true},
	{_hoops_GGCPP,					_hoops_GRRCR ("font directories"),			_hoops_PRRCR,	-999, true},
	{_hoops_RGCPP,				_hoops_GRRCR ("driver directory"),			_hoops_PRRCR,	-999, true},
	{_hoops_RGCPP,				_hoops_GRRCR ("driver directories"),		_hoops_PRRCR,	-999, true},
	{_hoops_AGCPP,				_hoops_GRRCR ("metafile directory"),		_hoops_PRRCR,	-999, true},
	{_hoops_AGCPP,				_hoops_GRRCR ("metafile directories"),		_hoops_PRRCR,	-999, true},
	{_hoops_PACPP,		_hoops_GRRCR ("code generation directory"),	_hoops_PRRCR,	-999, true},
	{_hoops_HACPP,				_hoops_GRRCR ("driver config file"),		_hoops_PRRCR,	-999, true},

	{_hoops_HSCPP,				_hoops_GRRCR ("continuous update"),			_hoops_RRRCR,	0, true},
	{_hoops_HSCPP,				_hoops_GRRCR ("continuous updates"),		_hoops_RRRCR,	0, true},
	{_hoops_ISCPP,				_hoops_GRRCR ("obsolete checking"),			_hoops_RRRCR,	0, true},
	{_hoops_SACPP,					_hoops_GRRCR ("sanity checking"),			_hoops_RRRCR,	0, true},
	{_hoops_SRCPP,					_hoops_GRRCR ("update control"),			_hoops_GHAGA, -9, true, &_hoops_ICCPP},
	{_hoops_SACPP,					_hoops_GRRCR ("bounding volumes"),			_hoops_RRRCR,	0, true},
	{_hoops_IGHGA,					_hoops_GRRCR ("code generation"),			_hoops_RRRCR,	0, true},
	{_hoops_CRCPP,			_hoops_GRRCR ("code generation comment"),	_hoops_PRRCR,	1, false},
	{_hoops_CSCPP,				_hoops_GRRCR ("ignore environment"),		_hoops_RRRCR,	0, true},

	{_hoops_RGRI,				_hoops_GRRCR ("generate consistent normals"),	_hoops_RRRCR,	0, true},
	{_hoops_SSCPP,				_hoops_GRRCR ("old style pathnames"),			_hoops_RRRCR,	0, true},
	{_hoops_SSCPP,				_hoops_GRRCR ("old-style pathnames"),			_hoops_RRRCR,	0, true},

	{_hoops_CSRRA,				_hoops_GRRCR ("region tristrips"),				_hoops_RRRCR,	0, true},
	{_hoops_GGSPP,			_hoops_GRRCR ("legacy mesh face numbering"),	_hoops_RRRCR,	0, true},
	{_hoops_RGSPP,			_hoops_GRRCR ("legacy text extent"),			_hoops_RRRCR,	0, true},

	{_hoops_AGSPP,			_hoops_GRRCR ("shell restrip on point edit"),	_hoops_RRRCR,	0, true},
	{_hoops_AGSPP,			_hoops_GRRCR ("restrip on edit"),				_hoops_RRRCR,	0, true},

	{_hoops_PGCPP,							_hoops_GRRCR ("license"),						_hoops_GHAGA, -999, true, &_hoops_IHCPP},
	{_hoops_PGCPP,							_hoops_GRRCR ("licenses"),						_hoops_GHAGA, -999, true, &_hoops_IHCPP},

	{_hoops_PGSPP,					_hoops_GRRCR ("conserve memory"),				_hoops_GHAGA, -999, true, &_hoops_CICPP},

	{_hoops_IGCPP,						_hoops_GRRCR ("multithreading"),				_hoops_GHAGA, -1, true, &_hoops_RICPP},
	{_hoops_IGCPP,						_hoops_GRRCR ("multi-threading"),				_hoops_GHAGA, -1, true, &_hoops_RICPP},
	{_hoops_IGCPP,						_hoops_GRRCR ("multithreaded"),					_hoops_GHAGA, -1, true, &_hoops_RICPP},
	{_hoops_IGCPP,						_hoops_GRRCR ("multi-threaded"),				_hoops_GHAGA, -1, true, &_hoops_RICPP},

	{_hoops_CGCPP,			_hoops_GRRCR ("extended font search"),			_hoops_RRRCR,		0, true},
	{_hoops_SGCPP, 					_hoops_GRRCR ("video memory"),					_hoops_CIGHA, 1, true, &_hoops_ASCPP},
	{_hoops_SGCPP, 					_hoops_GRRCR ("video memory limit"),			_hoops_CIGHA, 1, true, &_hoops_ASCPP},

	{_hoops_ARCPP,				_hoops_GRRCR ("camera near limit"),				_hoops_SPPCR,	1, false},

	{_hoops_PRCPP,					_hoops_GRRCR ("definition set"),				_hoops_APRCA,		1, true},

	{_hoops_HRCPP,					_hoops_GRRCR ("metafile root"),					_hoops_PRRCR,	 1, true},
	{_hoops_IRCPP,					_hoops_GRRCR ("texture root"),					_hoops_PRRCR,	 1, true},
	{_hoops_HGSPP,		_hoops_GRRCR ("near limit update promotion"),	_hoops_RRRCR,	 0, true},

	{Sysop_RAW_MEMORY,						_hoops_GRRCR ("raw memory"),					_hoops_RRRCR,	0, true},
	{_hoops_GACPP,							_hoops_GRRCR ("malloc"),						_hoops_PRRCR,	1, true},
	{_hoops_RACPP,							_hoops_GRRCR ("free"),							_hoops_PRRCR,	1, true},
	{_hoops_PAI,		_hoops_GRRCR ("disable ambient material"),		_hoops_RRRCR,	0, true},
	{_hoops_AACPP,						_hoops_GRRCR ("deleted key callback"),			_hoops_PRRCR,	1, true},
	{_hoops_AACPP,						_hoops_GRRCR ("delete key callback"),			_hoops_PRRCR,	1, true},
	{_hoops_IACPP,				_hoops_GRRCR ("automatic geometry boundings"),	_hoops_RRRCR,	0, true},
	{_hoops_CACPP,				_hoops_GRRCR ("dpi scale factor"),				_hoops_SPPCR,	1, true},
};




#define _hoops_IGSPP(a, b, n) _hoops_GHIA (					\
	unsigned long	_hoops_CGSPP;					\
	unsigned long	_hoops_SGSPP;					\
	_hoops_CGSPP = ((a) >> (32 - (n))) & ((1L << (n)) - 1);	\
	(a) <<= (n);										\
	_hoops_SGSPP = ((b) >> (32 - (n))) & ((1L << (n)) - 1);	\
	(b) <<= (n);										\
	(a) |= _hoops_SGSPP;										\
	(b) |= _hoops_CGSPP;)


local void _hoops_GRSPP (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HCRPR const *			_hoops_RRSPP,
	_hoops_HCRPR const *			_hoops_ARSPP,
	unsigned long *			_hoops_PRSPP,
	unsigned long *			_hoops_HRSPP) 
{
	unsigned long			_hoops_IRSPP;
	unsigned long			_hoops_CRSPP;
	unsigned long			_hoops_SRSPP;
	unsigned long			_hoops_GASPP;
	unsigned long			_hoops_RASPP;
	unsigned long			_hoops_AASPP;
	unsigned long			_hoops_PASPP;
	char const *			_hoops_HASPP;
	char const *			_hoops_IASPP;
	char alter *			_hoops_CASPP;

	/* _hoops_HPCAR _hoops_HPCS */
	*_hoops_PRSPP = 0;
	*_hoops_HRSPP = 0;

	_hoops_CASPP = Sprintf_N (null, "0x%n", _hoops_ARSPP);

	/* _hoops_SRS _hoops_HHAA -- "_hoops_RHGS" _hoops_SIC _hoops_IH _hoops_RSSSR & _hoops_CSPP */

	HI_Scan_Long (_hoops_RIGC, (char const **)&_hoops_CASPP, null, (long *)&_hoops_AASPP);
	*_hoops_CASPP = 'x';
	--_hoops_CASPP;
	*_hoops_CASPP = '0';
	HI_Scan_Long (_hoops_RIGC, (char const **)&_hoops_CASPP, null, (long *)&_hoops_PASPP);

	_hoops_IRSPP = (_hoops_PASPP >> 24) & 0x000000FF;
	_hoops_SRSPP = (_hoops_PASPP >> 16) & 0x000000FF;

	_hoops_GASPP = _hoops_IRSPP;
	_hoops_RASPP = 0;

	while (_hoops_RASPP < (1L << 16)) {
		_hoops_HASPP = _hoops_RRSPP->text;
		_hoops_IASPP = _hoops_HASPP + _hoops_RRSPP->length;
		_hoops_RGGA (_hoops_HASPP == _hoops_IASPP) {
			_hoops_IGSPP (_hoops_GASPP, _hoops_RASPP, 3);
			_hoops_GASPP ^= *_hoops_HASPP++;
			if (BIT (_hoops_GASPP, 1))
				_hoops_GASPP ^= _hoops_SRSPP;
			else
				_hoops_GASPP ^= _hoops_IRSPP;
		}

		_hoops_IGSPP (_hoops_GASPP, _hoops_RASPP, 3);
		_hoops_GASPP ^= _hoops_IRSPP;
	}

	if ((_hoops_AASPP	   & 0x7FFFFFFF) !=
		(_hoops_GASPP & 0x7FFFFFFF) ||
		(_hoops_PASPP	   & 0x0000FFFF) !=
		(_hoops_RASPP & 0x0000FFFF) ||
		HOOPS_VERSION / 10 > _hoops_SRSPP)
		return;

	/* _hoops_GIAP _hoops_HHAA -- _hoops_CCAH _hoops_SIC _hoops_IH _hoops_SASPP */

	*_hoops_CASPP = 'x';
	--_hoops_CASPP;
	*_hoops_CASPP = '0';
	HI_Scan_Long (_hoops_RIGC, (char const **)&_hoops_CASPP, null, (long *)&_hoops_AASPP);
	*_hoops_CASPP = 'x';
	--_hoops_CASPP;
	*_hoops_CASPP = '0';
	HI_Scan_Long (_hoops_RIGC, (char const **)&_hoops_CASPP, null, (long *)&_hoops_PASPP);

	_hoops_CRSPP =	_hoops_PASPP & 0x0000003F;
	_hoops_CRSPP |= (_hoops_AASPP & 0x0000003F) << 6;

	_hoops_GASPP = _hoops_CRSPP;
	_hoops_RASPP = 0;

	while (_hoops_RASPP < (1L << 20)) {
		_hoops_HASPP = _hoops_RRSPP->text;
		_hoops_IASPP = _hoops_HASPP + _hoops_RRSPP->length;
		_hoops_RGGA (_hoops_HASPP == _hoops_IASPP) {
			_hoops_IGSPP (_hoops_GASPP, _hoops_RASPP, 3);
			_hoops_GASPP ^= *_hoops_HASPP++;
			if (BIT (_hoops_GASPP, 1))
				_hoops_GASPP ^= _hoops_SRSPP;
			else
				_hoops_GASPP ^= _hoops_CRSPP;
		}

		_hoops_IGSPP (_hoops_GASPP, _hoops_RASPP, 3);
		_hoops_GASPP ^= _hoops_IRSPP;
	}

	if ((_hoops_AASPP	   & 0x7FFFFFC0) !=
		(_hoops_GASPP & 0x7FFFFFC0) ||
		(_hoops_PASPP	   & 0x7FFFFFC0) !=
		(_hoops_RASPP & 0x7FFFFFC0))
		return;

	*_hoops_PRSPP = _hoops_IRSPP;
	*_hoops_HRSPP = _hoops_CRSPP;
}


local void _hoops_GPSPP (
	_hoops_AIGPR *	_hoops_RIGC,
	Option_Value *			option) 
{
	_hoops_HCRPR *					_hoops_RRSPP = null;
	_hoops_HCRPR *					_hoops_ARSPP = null;
	int						_hoops_RPSPP = false;
	int						_hoops_APSPP = false;
	unsigned long			_hoops_IRSPP;
	unsigned long			_hoops_CRSPP;
	int						_hoops_PPSPP;

	if (option != null) do switch (option->type->id) {
		case _hoops_APCPP: {
			_hoops_RRSPP = option->value._name;
		}	break;

		case _hoops_PPCPP: {
			Option_Value			*_hoops_AHSAA;

			if ((_hoops_AHSAA = option->value.option_list) != null) do {
				if (_hoops_AHSAA->_hoops_GCACR)
					_hoops_RPSPP &= ~_hoops_AHSAA->type->id;
				else
					_hoops_RPSPP |= _hoops_AHSAA->type->id;

				_hoops_APSPP |= _hoops_AHSAA->type->id;
			} _hoops_RGGA ((_hoops_AHSAA = _hoops_AHSAA->next) == null);
		}	break;

		case _hoops_HPCPP: {
			_hoops_ARSPP = option->value._name;
		}		break;
	} _hoops_RGGA ((option = option->next) == null);

	if (_hoops_RRSPP == null) {
		HE_ERROR (HEC_SYSTEM, HES_INVALID_LICENSE,
				  "You must define the \"customer\" field of the license.");
		return;
	}
	if (_hoops_ARSPP == null) {
		HE_ERROR (HEC_SYSTEM, HES_INVALID_LICENSE,
				  "You must define the \"key\" field of the license.");
		return;
	}


	_hoops_GRSPP (_hoops_RIGC, _hoops_RRSPP, _hoops_ARSPP,
					  &_hoops_IRSPP, &_hoops_CRSPP);

	if (BIT (_hoops_RPSPP & _hoops_APSPP, _hoops_SPCPP)) {
		_hoops_APSPP  |= _hoops_GHCPP;
		_hoops_RPSPP |= _hoops_GHCPP;
	}
	if (BIT (_hoops_IRSPP, _hoops_SPCPP))
		_hoops_IRSPP |= _hoops_GHCPP;


	HOOPS_WORLD->_hoops_HPSPP &= ~(_hoops_IRSPP & _hoops_APSPP);
	HOOPS_WORLD->_hoops_HPSPP |= _hoops_IRSPP & _hoops_RPSPP;

	if (!HOOPS_WORLD->_hoops_IPSPP) {
		_hoops_PPSPP = (int)~_hoops_IRSPP & _hoops_RPSPP;

#if 0
		if (BIT (_hoops_PPSPP, _hoops_CPCPP)) {
			_hoops_PHPGR (HEC_SYSTEM, HES_INVALID_LICENSE,
						 "The key you provided does not contain a license for",
						 "this version of A.I.R. on this platform.");
		}
		if (BIT (_hoops_PPSPP, _hoops_GHCPP)) {
			_hoops_PHPGR (HEC_SYSTEM, HES_INVALID_LICENSE,
						 "The key you provided does not contain a license for",
						 "this version of I.M. on this platform.");
		}
		if (BIT (_hoops_PPSPP, _hoops_RHCPP)) {
			_hoops_PHPGR (HEC_SYSTEM, HES_INVALID_LICENSE,
						 "The key you provided does not contain a license for",
						 "this version of Kanji on this platform.");
		}
#endif
		if (BIT (_hoops_PPSPP, _hoops_SPCPP)) {
			_hoops_PHPGR (HEC_SYSTEM, HES_INVALID_LICENSE,
						 "The key you provided does not contain a license for",
						 "this version of HOOPS on this platform.");
		}
		if (BIT (_hoops_PPSPP, _hoops_AHCPP)) {
			_hoops_PHPGR (HEC_SYSTEM, HES_INVALID_LICENSE,
						 "The key you provided does not contain a license for",
						 "this version of HSF on this platform.");
		}


		if (~_hoops_CRSPP & HK_PLATFORM_ID) {
			HE_WARNING (HEC_SYSTEM, HES_INVALID_LICENSE,
						"The key you provided does not contain a license for this version and/or platform.");
		}
	}

#ifndef AIR
	if (BIT (HOOPS_WORLD->_hoops_HPSPP, _hoops_CPCPP)) {
#if 0
		if (!HOOPS_WORLD->_hoops_IPSPP) {
			_hoops_PHPGR (HEC_SYSTEM, HES_INVALID_LICENSE,
						 "Your request to enable the A.I.R. product was denied, because",
						 "it is absent in the version of Hoops you are using. Oh dear.");
		}
		HOOPS_WORLD->_hoops_HPSPP &= ~_hoops_CPCPP;
#endif
	}
#endif

	return;
}

GLOBAL_FUNCTION _hoops_CPSPP ** HI_Lookup_Error_Control (
	_hoops_CPSPP **	_hoops_ASRGR,
	int					category,
	int					specific) {
	_hoops_CPSPP *	control;

	while ((control = *_hoops_ASRGR) != null) {
		if (control->category == category && control->specific == specific)
			break;
		_hoops_ASRGR = &control->next;
	}

	return _hoops_ASRGR;
}

local void _hoops_SPSPP (
	_hoops_CPSPP **	_hoops_ASRGR,
	int					state) {
	_hoops_CPSPP *		control;

	while ((control = *_hoops_ASRGR) != null) {
		if (BIT (control->_hoops_GHSPP, _hoops_RHSPP)) {
			if (state == _hoops_GCCPP)
				control->state = _hoops_GCCPP;
			else
				control->state = control->_hoops_GHSPP & ~_hoops_RHSPP;

			_hoops_ASRGR = &control->next;
		}
		else {
			*_hoops_ASRGR = control->next;
			FREE (control, _hoops_CPSPP);
		}
	}
}

HC_INTERFACE void HC_CDECL HC_Define_System_Options (
	char const *		list)
{
	Option_Value *		option_list;
	Option_Value *		option;
	int					_hoops_IHAGA;
	Error_Mask			_hoops_AHSPP;
	_hoops_CPSPP *		_hoops_PHSPP[4];
	int					_hoops_HHSPP = 0, _hoops_IHSPP = 0;
	_hoops_CHSPP		_hoops_SHSPP = null;
	_hoops_GISPP			_hoops_RISPP = null;
	bool				_hoops_AISPP = false;
	bool				_hoops_PISPP = false;
	bool				_hoops_HISPP = false;


	/* _hoops_PAH'_hoops_RA _hoops_SHR _hoops_SGH _hoops_IISPP(), _hoops_GAR _hoops_SR _hoops_GHCA _hoops_HHGC _hoops_IS _hoops_HPPP _hoops_PCHC _hoops_AAP
	 * _hoops_ARPP _hoops_CGCGA _hoops_RH _hoops_SGCRP _hoops_CISPP
	 */
	_hoops_AIGPR *	_hoops_SISPP = null;
	if (HOOPS_WORLD && HOOPS_WORLD->_hoops_GCSPP)
		_hoops_SISPP = HI_Set_Name ("Define_System_Options");
	else {
		/* _hoops_AASC _hoops_SR _hoops_PAH _hoops_HGCR _hoops_SGGR _hoops_CCA _hoops_IH _hoops_HA */
		if (!HOOPS_WORLD)
			HI_Init_Internal_Data ();
		HOOPS_WORLD->_hoops_PGSCA->_hoops_RCSPP = "Define_System_Options";
		_hoops_SISPP = HOOPS_WORLD->_hoops_PGSCA;
	}

	_hoops_PAPPR context(_hoops_SISPP);

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Define_System_Options (%S);\n", list));
	);

	if (BIT (HOOPS_WORLD->system_flags, Sysop_RAW_MEMORY))
		_hoops_HISPP=true;

	_hoops_HIACR (_hoops_ACSPP, _hoops_PSCPP);

	_hoops_IHAGA = HI_Parse_Options (context, list, _hoops_CIACR (_hoops_ACSPP),
									 &option_list, _hoops_SIACR);

	/* _hoops_ARPP _hoops_CISPP, _hoops_SRRI _hoops_CRGR _hoops_RH _hoops_AAP, _hoops_PPR _hoops_CACH _hoops_RPP _hoops_AHGSR _hoops_CHR _hoops_IHGS _hoops_IHPPP _hoops_PSAP */
	/* _hoops_PIP: _hoops_CHPCR _hoops_RIHH _hoops_HRP _hoops_GPP _hoops_PAR _hoops_PSAP, _hoops_CICAR _hoops_HRP _hoops_SPHR */
	// _hoops_PRSSR _hoops_ISPR _hoops_IH "_hoops_SSPC _hoops_RHI" _hoops_GGR _hoops_AGIR _hoops_SR _hoops_CHR _hoops_ARPP _hoops_RH _hoops_GASCA
	if (_hoops_IHAGA) {
		if ((option = option_list) != null) do {
			switch (option->type->id) {
				case _hoops_RSIPP: {
					if (option->_hoops_GCACR)
						HOOPS_WORLD->error_mask |= 1 << _hoops_PCSPP;
					else if (option->_hoops_AIPCR == 0)
						HOOPS_WORLD->error_mask &= ~(1 << _hoops_PCSPP);
					else if (option->_hoops_AIPCR == 1 &&
							 option->value.option_list->_hoops_AIPCR == 0) {
						if (option->value.option_list->type->id == _hoops_GCCPP)
							HOOPS_WORLD->error_mask |= 1 << _hoops_PCSPP;
						else if (option->value.option_list->type->id == _hoops_RCCPP)
							HOOPS_WORLD->error_mask &= ~(1 << _hoops_PCSPP);
					}
				}	break;

				case _hoops_GSIPP: {
					if (option->_hoops_GCACR)
						HOOPS_WORLD->error_mask |= 1 << _hoops_HCSPP;
					else if (option->_hoops_AIPCR == 0)
						HOOPS_WORLD->error_mask &= ~(1 << _hoops_HCSPP);
					else if (option->_hoops_AIPCR == 1 &&
							 option->value.option_list->_hoops_AIPCR == 0) {
						if (option->value.option_list->type->id == _hoops_GCCPP)
							HOOPS_WORLD->error_mask |= 1 << _hoops_HCSPP;
						else if (option->value.option_list->type->id == _hoops_RCCPP)
							HOOPS_WORLD->error_mask &= ~(1 << _hoops_HCSPP);
					}
				}	break;

				case _hoops_SCIPP: {
					if (option->_hoops_GCACR)
						HOOPS_WORLD->error_mask |= 1 << _hoops_ICSPP;
					else if (option->_hoops_AIPCR == 0)
						HOOPS_WORLD->error_mask &= ~(1 << _hoops_ICSPP);
					else if (option->_hoops_AIPCR == 1 &&
							 option->value.option_list->_hoops_AIPCR == 0) {
						if (option->value.option_list->type->id == _hoops_GCCPP)
							HOOPS_WORLD->error_mask |= 1 << _hoops_ICSPP;
						else if (option->value.option_list->type->id == _hoops_RCCPP)
							HOOPS_WORLD->error_mask &= ~(1 << _hoops_ICSPP);
					}
				}	break;

				case _hoops_CCIPP: {
					if (option->_hoops_GCACR)
						HOOPS_WORLD->error_mask |= 1 << _hoops_CCSPP;
					else if (option->_hoops_AIPCR == 0)
						HOOPS_WORLD->error_mask &= ~(1 << _hoops_CCSPP);
					else if (option->_hoops_AIPCR == 1 &&
							 option->value.option_list->_hoops_AIPCR == 0) {
						if (option->value.option_list->type->id == _hoops_GCCPP)
							HOOPS_WORLD->error_mask |= 1 << _hoops_CCSPP;
						else if (option->value.option_list->type->id == _hoops_RCCPP)
							HOOPS_WORLD->error_mask &= ~(1 << _hoops_CCSPP);
					}
				}	break;


				case _hoops_CSCPP: {
					if (option->_hoops_GCACR)
						HOOPS_WORLD->system_flags &= ~_hoops_CSCPP;
					else
						HOOPS_WORLD->system_flags |= _hoops_CSCPP;
				}	break;


				case Sysop_RAW_MEMORY: {
					_hoops_HISPP = !option->_hoops_GCACR;
					_hoops_AISPP = true;
				}	break;

				case _hoops_GACPP: {
			  		_hoops_HCRPR *		name = option->value._name;
					POINTER_SIZED_INT	value;

					if (option->_hoops_GCACR)
						_hoops_PISPP = true;
					else {
						char *		_hoops_RPPA = name->text;
						if (HI_Scan_Ptr (context, (char const **)&_hoops_RPPA, _hoops_RPPA+name->length, &value) == null) {
							_hoops_SHSPP = (_hoops_CHSPP)value;
						}
						else
							HE_ERROR (HEC_HOOPS_SYSTEM, HES_BAD_VALUE,
								Sprintf_N (null, "malloc '%n' is not a valid pointer", name));
					}
				}	break;

				case _hoops_RACPP: {
			  		_hoops_HCRPR *		name = option->value._name;
					POINTER_SIZED_INT		value;

					if (option->_hoops_GCACR)
						_hoops_PISPP = true;
					else {
						char *	_hoops_RPPA = name->text;
						if (HI_Scan_Ptr (context, (char const **)&_hoops_RPPA, _hoops_RPPA+name->length, &value) == null) {
							_hoops_RISPP = (_hoops_GISPP)value;
						}
						else
							HE_ERROR (HEC_HOOPS_SYSTEM, HES_BAD_VALUE,
								Sprintf_N (null, "free '%n' is not a valid pointer", name));
					}
				}	break;
			}
		} while ((option = option->next) != null);
	}


	/* _hoops_HA, _hoops_GCSH, _hoops_SR _hoops_PAH _hoops_HSPC _hoops_RPP _hoops_SIGR (_hoops_GGR _hoops_AGIR _hoops_SR _hoops_RIAGR _hoops_IS _hoops_AASGA _hoops_IISPP() _hoops_ARRS) */

	if (_hoops_SHSPP && !_hoops_RISPP || !_hoops_SHSPP && _hoops_RISPP) {
		HE_ERROR (HEC_INVALID_INPUT, HES_BAD_VALUE, "Malloc and free must be both provided");
		_hoops_SHSPP = null;
		_hoops_RISPP = null;
	}

	if (!HOOPS_WORLD->_hoops_GCSPP) {
		if (_hoops_SHSPP || _hoops_PISPP || _hoops_AISPP) {

			_hoops_CIACR (_hoops_ACSPP)->table = null;
			_hoops_CIACR (_hoops_ACSPP)->size = 0;
			_hoops_CIACR (_hoops_ACSPP)->count = 0;

			if (_hoops_SHSPP) {
				HOOPS_WORLD->_hoops_SCSPP = true;
				HOOPS_WORLD->malloc = _hoops_SHSPP;
				HOOPS_WORLD->free = _hoops_RISPP;
			}
			else {
				HOOPS_WORLD->_hoops_SCSPP = false;
				HOOPS_WORLD->malloc = HOOPS_WORLD->_hoops_GSSPP;
				HOOPS_WORLD->free = HOOPS_WORLD->_hoops_RSSPP;
			}


			Memory_Pool * _hoops_ASSPP = HOOPS_WORLD->memory_pool;

			_hoops_AIGPR *	_hoops_RIGC = HOOPS_WORLD->_hoops_PGSCA;

			LOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);
			do {
				HI_Destroy_Memory_Pool (_hoops_RIGC->memory_pool);
			} while ((_hoops_RIGC = _hoops_RIGC->next) != null);
			UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);

			HOOPS_WORLD->memory_pool = null;
			HI_Destroy_Memory_Pool(_hoops_ASSPP);

			if (_hoops_HISPP)
				HOOPS_WORLD->system_flags |= Sysop_RAW_MEMORY;
			else
				HOOPS_WORLD->system_flags &= ~Sysop_RAW_MEMORY;

			HOOPS_WORLD->memory_pool = HI_Create_Memory_Pool(MPF_DEFAULT);

			_hoops_RIGC = HOOPS_WORLD->_hoops_PGSCA;

			LOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);
			do {
				_hoops_RIGC->memory_pool = HI_Create_Memory_Pool(MPF_NONE);
			} while ((_hoops_RIGC = _hoops_RIGC->next) != null);
			UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RIPSA);


			_hoops_HIACR (_hoops_ACSPP, _hoops_PSCPP);

			_hoops_IHAGA = HI_Parse_Options (context, list, _hoops_CIACR (_hoops_ACSPP), &option_list, _hoops_SIACR);
		}

		HI_Start_Hoops ("Define_System_Options");
	}
	else if (_hoops_SHSPP || _hoops_AISPP) {
		HE_ERROR (HEC_INVALID_INPUT, HES_BAD_VALUE, "Memory system changes must happen before anything else.");
		_hoops_SHSPP = null;
		_hoops_RISPP = null;
		if (_hoops_AISPP)
			HOOPS_WORLD->system_flags &= ~Sysop_RAW_MEMORY;
	}



	_hoops_AHSPP = HOOPS_WORLD->error_mask;
	HOOPS_WORLD->error_mask = false;
	_hoops_AIGA (HOOPS_WORLD->_hoops_PSSPP, 4, _hoops_CPSPP *, _hoops_PHSPP);
	ZERO_ARRAY (HOOPS_WORLD->_hoops_PSSPP, 4, _hoops_CPSPP *);

	if (_hoops_IHAGA) {
		if ((option = option_list) != null) do {
			if (option->type->id == _hoops_PGSPP) {
				if (option->_hoops_GCACR) {
					HOOPS_WORLD->system_flags &= ~_hoops_PGSPP;
					HOOPS_WORLD->_hoops_HGGHR = _hoops_PICPP;
				}
				else if (option->_hoops_AIPCR == 0) {
					HOOPS_WORLD->system_flags |= _hoops_PGSPP;
					HOOPS_WORLD->_hoops_HGGHR = _hoops_HICPP;
				}
				else {
					Option_Value const *_hoops_AHSAA = option->value.option_list;

					if (_hoops_AHSAA != null) do {
						if (_hoops_AHSAA->_hoops_GCACR)
							HOOPS_WORLD->_hoops_HGGHR &= ~_hoops_AHSAA->type->id;
						else
							HOOPS_WORLD->_hoops_HGGHR |= _hoops_AHSAA->type->id;
					} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);

					if (HOOPS_WORLD->_hoops_HGGHR == _hoops_PICPP)
						HOOPS_WORLD->system_flags &= ~_hoops_PGSPP;
					else
						HOOPS_WORLD->system_flags |= _hoops_PGSPP;
				}
			}
			else if (option->type->id > 0) {
				/* _hoops_IH _hoops_ICRP _hoops_IIGR _hoops_RH _hoops_GHARR _hoops_AAP _hoops_SGS _hoops_CHR _hoops_HSSPP _hoops_PAPR _hoops_GGR
				   _hoops_CHARP._hoops_GGHR (_hoops_PGAP _hoops_CHR _hoops_HCR > 0), _hoops_SCH _hoops_HRGR _hoops_RAPR _hoops_IS _hoops_SAHR _hoops_ARP _hoops_RH _hoops_IGRH. */
				if (option->_hoops_GCACR) {
					HOOPS_WORLD->system_flags &= ~option->type->id;
				}
				else {
					HOOPS_WORLD->system_flags |= option->type->id;

					if (option->type->id == _hoops_IGHGA &&
						!HOOPS_WORLD->_hoops_AGHGA) {
						Option_Value * _hoops_ISSPP = option;
						while ((_hoops_ISSPP = _hoops_ISSPP->next) != null) {
							if (_hoops_ISSPP->type->id == _hoops_PACPP) {
								_hoops_RGAIR (HOOPS_WORLD->_hoops_GRHGA);
								HI_Copy_Name (_hoops_ISSPP->value._name, &HOOPS_WORLD->_hoops_GRHGA);
								break;
							}
						}
						HI_Start_Code_Generation ();
					}
				}
			}
			else switch (option->type->id) {
				case _hoops_SGCPP: {
					if (option->_hoops_GCACR) {
						HOOPS_WORLD->_hoops_PHARR = _hoops_CSSPP;
					}
					else if (option->value._hoops_RRRHA[0].value < 0.0f) {
						HE_ERROR (HEC_INVALID_INPUT, HES_BAD_VALUE, "Video memory limit must be non-negative");
						HI_Free_Option_List (context, option_list);
					}
					else {
						_hoops_CAAI (HOOPS_WORLD->_hoops_PIPSA);
						switch (option->value._hoops_RRRHA[0]._hoops_HHP) {
							case _hoops_CCCPP:
								HOOPS_WORLD->_hoops_PHARR = (size_t) option->value._hoops_RRRHA[0].value;
								break;
							case _hoops_SCCPP:
								HOOPS_WORLD->_hoops_PHARR = 1000 * (size_t) option->value._hoops_RRRHA[0].value;
								break;
							case _hoops_GSCPP:
								HOOPS_WORLD->_hoops_PHARR = 1000000 * (size_t) option->value._hoops_RRRHA[0].value;
								break;
						}
						_hoops_APAI (HOOPS_WORLD->_hoops_PIPSA);
						if (HOOPS_WORLD->_hoops_PHARR > 0 && HOOPS_WORLD->_hoops_PHARR < 10000)
							HE_WARNING (HEC_SYSTEM, HES_BAD_VALUE,
								 "Video memory limit was specified as less "
								 "than 10,000 bytes.  Did you mean xxx MB?");
					}
				}	  break;

				case _hoops_RSIPP:
				case _hoops_GSIPP:
				case _hoops_SCIPP:
				case _hoops_CCIPP: {
					int			severity = 0, bit;

					switch (option->type->id) {
						case _hoops_CCIPP:		severity = _hoops_CCSPP;		break;
						case _hoops_SCIPP:		severity = _hoops_ICSPP;	break;
						case _hoops_GSIPP:		severity = _hoops_HCSPP;		break;
						case _hoops_RSIPP:	severity = _hoops_PCSPP;		break;
					}
					bit = 1 << severity;


					if (option->_hoops_GCACR) {
						_hoops_AHSPP |= bit;
						_hoops_SPSPP (&_hoops_PHSPP[severity], _hoops_GCCPP);
					}
					else if (option->_hoops_AIPCR == 0) {
						_hoops_AHSPP &= ~bit;
						_hoops_SPSPP (&_hoops_PHSPP[severity], _hoops_RCCPP);
					}
					else {
						Option_Value const *	_hoops_AHSAA = option->value.option_list;

						do {
							int						_hoops_GHSPP = _hoops_AHSAA->type->id;

							if (_hoops_AHSAA->_hoops_AIPCR == 0) {
								if (_hoops_GHSPP == _hoops_ACCPP) {
									HE_ERROR2 (HEC_HOOPS_SYSTEM, HES_INVALID_INPUT,
												"Specific category/class combination(s)required for 'once' setting,",
												"it may not be set as a general state");
								}
								else {
									/* _hoops_IHGP "_hoops_GPP/_hoops_PSAP/_hoops_HHPR/_hoops_HHSP */
									if (_hoops_GHSPP == _hoops_GCCPP)
										_hoops_AHSPP |= bit;
									else
										_hoops_AHSPP &= ~bit;

									_hoops_SPSPP (&_hoops_PHSPP[severity], _hoops_GHSPP);
								}
							}
							else {
								int				count;
								_hoops_HCRPR			*name;

								count = _hoops_AHSAA->_hoops_AIPCR;
								name = _hoops_AHSAA->value._name;

								while (count-- > 0) {
									if (name->length > 0) {
										_hoops_CPSPP **	_hoops_ASRGR;
										_hoops_CPSPP *		control;
										int					category = -1, specific = -1;
										char const *		_hoops_RPPA = name->text;
										bool				_hoops_CPCA = true;

										/* _hoops_PSH _hoops_RSIRR _hoops_GAR "_hoops_SSSPP/_hoops_ACISR" &_hoops_GGCR _hoops_IS _hoops_RH _hoops_HIGR _hoops_GGGHP[_hoops_RGGHP]
										 * _hoops_PAR _hoops_AGRP _hoops_PCCP _hoops_APRS _hoops_RARP, _hoops_RPP _hoops_GII
										 */
										if (HI_Scan_Integer (context, &_hoops_RPPA, null, &category) != null)
											_hoops_CPCA = false;
										if (_hoops_CPCA) {
											while (*_hoops_RPPA == ' ') _hoops_RPPA++;
											if (*_hoops_RPPA++ != '/')
												_hoops_CPCA = false;
											if (_hoops_CPCA) {
												if (HI_Scan_Integer (context, &_hoops_RPPA, null, &specific) != null)
													_hoops_CPCA = false;
												if (_hoops_CPCA) {
													while (*_hoops_RPPA == ' ') _hoops_RPPA++;
													if (*_hoops_RPPA != '\0')
														_hoops_CPCA = false;
												}
											}
										}

										if (_hoops_CPCA) {
											_hoops_ASRGR = HI_Lookup_Error_Control (&_hoops_PHSPP[severity],
																			  category, specific);
											if ((control = *_hoops_ASRGR) == null) {
												ALLOC (control, _hoops_CPSPP);
												ZERO_STRUCT (control, _hoops_CPSPP);
												*_hoops_ASRGR = control;
												control->category = category;
												control->specific = specific;
											}

											control->_hoops_GHSPP = control->state = _hoops_GHSPP;
										}
										else
											HE_ERROR (HEC_HOOPS_SYSTEM, HES_INVALID_INPUT,
													Sprintf_N (null,
															   "Cannot interpret '%n' as category/specific combination -- ignoring",
															   name));
									}
									++name;
								}
							}
						} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
					}
				}	break;


				case _hoops_ASIPP: {
					if (option->_hoops_GCACR)
						HOOPS_WORLD->_hoops_RAPPR = _hoops_AGGHP;
					else if (option->value._hoops_RIARA[0] < 2)
						HE_ERROR (HEC_HOOPS_SYSTEM, HES_OUT_OF_RANGE_STRING_LENGTH,
								Sprintf_D (null,
										   "A 'C string length' of %d is unreasonable",
										   option->value._hoops_RIARA[0]));
					else
						HOOPS_WORLD->_hoops_RAPPR = option->value._hoops_RIARA[0];
				}	break;

				case _hoops_HSIPP: {
					_hoops_HCHIR *		_hoops_IGPCR;

					if (option->_hoops_GCACR) {
						HOOPS_WORLD->_hoops_PGGHP = nullroutine;
						if (HOOPS_WORLD->_hoops_HGGHP != null) {
							_hoops_HPRH (HOOPS_WORLD->_hoops_HGGHP);
							HOOPS_WORLD->_hoops_HGGHP = null;
						}
					}
#ifndef DISABLE_CALLBACKS
					else if ((_hoops_IGPCR = * HI_Look_Up_Callback_Name (context, option->value._name[0].text,
																   option->value._name[0].length)) != null) {
						HOOPS_WORLD->_hoops_HGGHP = _hoops_IGPCR;
						HOOPS_WORLD->_hoops_PGGHP = (_hoops_IGGHP)_hoops_IGPCR->address;
						_hoops_PRRH (_hoops_IGPCR);
					}
#endif
					else {
						_hoops_HCRPR *		name = &option->value._name[0];
						char *		_hoops_RPPA = name->text;
						POINTER_SIZED_INT		value;

						if (HI_Scan_Ptr (context, (char const **)&_hoops_RPPA, _hoops_RPPA+name->length, &value) == null) {
							if (BIT (HOOPS_WORLD->system_flags, _hoops_ISCPP))
								_hoops_SHCHR (HEC_MISC, HES_OBSOLETE_USAGE,
										"Direct specification of event checker address",
										"has been replaced with callback definition");

							HOOPS_WORLD->_hoops_PGGHP = *(void (HC_CDECL **)(void))&value;
						}
						else
							HE_ERROR (HEC_HOOPS_SYSTEM, HES_EVENT_CHECKER,
									  Sprintf_N (null,"Event Checker '%n' is neither a defined callback nor a pointer value",name));
					}
				}	break;

				case _hoops_AACPP: {
					_hoops_HCHIR *		_hoops_IGPCR;

					if (option->_hoops_GCACR) {
						HOOPS_WORLD->_hoops_HHRIR = nullroutine;
						if (HOOPS_WORLD->_hoops_CGGHP != null) {
							_hoops_HPRH (HOOPS_WORLD->_hoops_CGGHP);
							HOOPS_WORLD->_hoops_CGGHP = null;
						}
					}
#ifndef DISABLE_CALLBACKS
					else if ((_hoops_IGPCR = * HI_Look_Up_Callback_Name (context, option->value._name[0].text,
																   option->value._name[0].length)) != null) {
						HOOPS_WORLD->_hoops_CGGHP = _hoops_IGPCR;
						HOOPS_WORLD->_hoops_HHRIR = (HOOPS::_hoops_SGGHP)_hoops_IGPCR->address;
						_hoops_PRRH (_hoops_IGPCR);
					}
#endif
					else {
						_hoops_HCRPR *		name = &option->value._name[0];

						HE_ERROR (HEC_HOOPS_SYSTEM, HES_EVENT_CHECKER,
							  Sprintf_N (null, "Delete Key Callback '%n' is not a defined callback.", name));
					}
				}	break;

				case _hoops_PSIPP: {
					_hoops_RGAIR (HOOPS_WORLD->_hoops_GRGHP);

					HI_Copy_Name (option->value._name, &HOOPS_WORLD->_hoops_GRGHP);

					HOOPS_WORLD->root->_hoops_CPGPR |= _hoops_AHGPR|_hoops_AHSGA;
					HOOPS_WORLD->root->_hoops_IPPGR->_hoops_CPGPR |= _hoops_AHSGA;
				}	break;

				case _hoops_ISIPP: {
					if (option->_hoops_GCACR)
						HOOPS_WORLD->_hoops_RRGHP = 0;
					else if (option->value._hoops_RIARA[0] <= 0)
						HE_ERROR (HEC_HOOPS_SYSTEM, HES_OUT_OF_RANGE_MESSAGE_LIMIT,
								Sprintf_D (null, "A 'message limit' of %d is unreasonable", option->value._hoops_RIARA[0]));
					else
						HOOPS_WORLD->_hoops_RRGHP = option->value._hoops_RIARA[0];

					HOOPS_WORLD->_hoops_ARGHP = 0;		/* _hoops_HIAP _hoops_RGR _hoops_HA */
				}	break;

				case _hoops_CSIPP: {
					_hoops_GGAGR *		_hoops_GHRI;

					if (option->_hoops_GCACR)
						HOOPS_WORLD->_hoops_PRGHP = _hoops_IICIA;		/* _hoops_HRGHP */
					else if (option->value._hoops_RIARA[0] < 0)
						HE_ERROR (HEC_HOOPS_SYSTEM, HES_OUT_OF_RANGE_STRING_HISTORY,
								Sprintf_D (null, "A 'string history limit' of %d is unreasonable", option->value._hoops_RIARA[0]));
					else
						HOOPS_WORLD->_hoops_PRGHP = option->value._hoops_RIARA[0];

					if ((_hoops_GHRI = HOOPS_WORLD->_hoops_CISHA) != null) do {
						if (_hoops_GHRI->_hoops_HHIAP > HOOPS_WORLD->_hoops_PRGHP) {
							_hoops_RRPIR **		sl;
							int					count;

							sl = &_hoops_GHRI->_hoops_ARPIR;
							count = HOOPS_WORLD->_hoops_PRGHP;

							while (count-- > 0) {
								if (*sl == null) {
									_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									  "Inconsistent string history list and count");
									break;
								}
								sl = &(*sl)->prev;
							}

							while (*sl != null) {
								_hoops_RRPIR			*victim;

								victim = *sl;
								*sl = victim->prev;

								_hoops_PRPIR (victim->string);
								FREE (victim, _hoops_RRPIR);
							}
						}
					} while ((_hoops_GHRI = _hoops_GHRI->_hoops_CISHA) != null);
				}	break;

				case _hoops_SSIPP: {
					if (option->_hoops_GCACR)
						HOOPS_WORLD->_hoops_IRARR = 0;
					else
						HOOPS_WORLD->_hoops_IRARR = option->value._hoops_RIARA[0];
				}	break;

				case _hoops_GRCPP: {
						_hoops_IHSPP = option->value._hoops_RIARA[0];
				}	break;

				case _hoops_RRCPP: {
						_hoops_HHSPP = option->value._hoops_RIARA[0];
				}	break;

				case _hoops_ARCPP: {
					HOOPS_WORLD->_hoops_GCPCR = option->value._hoops_PIPCR[0];
				}	break;

				case _hoops_CACPP: {
					if (option->_hoops_GCACR)
						HOOPS_WORLD->_hoops_IRGHP = HOOPS_WORLD->_hoops_CRGHP;
					else
						HOOPS_WORLD->_hoops_IRGHP = option->value._hoops_PIPCR[0];
				}	break;

				case _hoops_HGCPP: {
					if (option->_hoops_GCACR)
						HOOPS_WORLD->_hoops_SRGHP = 0;
					else
						HOOPS_WORLD->_hoops_SRGHP = option->value._hoops_RIARA[0];

					HOOPS_WORLD->_hoops_CIIPA =
						HOOPS_WORLD->_hoops_GAGHP &
						~HOOPS_WORLD->_hoops_SRGHP;
				}	break;

				case _hoops_CGCPP: {
					if (option->_hoops_GCACR)
					  HOOPS_WORLD->_hoops_RAGHP = true;
					else
					  HOOPS_WORLD->_hoops_RAGHP = false;
				}	break;

				case _hoops_GGCPP: {
					_hoops_AAPIR	**item;

				  /* _hoops_CIH _hoops_GII _hoops_RHGS _hoops_RPPCR */
					if (*(item = &HOOPS_WORLD->_hoops_AAGHP) != null) do {
						_hoops_AAPIR	*victim = *item;

						*item = victim->next;
						_hoops_RGAIR (victim->name);
						FREE (victim, _hoops_AAPIR);
					} _hoops_RGGA (*item == null);

					if (!option->_hoops_GCACR) {
						int				count;
						_hoops_HCRPR			*_hoops_HGPIR;

						count = option->_hoops_AIPCR;
						item	= &HOOPS_WORLD->_hoops_AAGHP;
						_hoops_HGPIR = option->value._name;

						_hoops_RGGA (count-- == 0) {
							if (_hoops_HGPIR->length > 0) {
								ALLOC (*item, _hoops_AAPIR);
								HI_Copy_Name (_hoops_HGPIR, &(*item)->name);
								item = &(*item)->next;
								*item = null;
							}
							++_hoops_HGPIR;
						}
					}
				}	break;

				case _hoops_RGCPP: {
					_hoops_AAPIR	**item;

					_hoops_RPPPR();
					/* _hoops_CIH _hoops_GII _hoops_RHGS _hoops_RPPCR */
					if (*(item = &HOOPS_WORLD->_hoops_PAGHP) != null) do {
						_hoops_AAPIR	*victim = *item;

						*item = victim->next;
						_hoops_RGAIR (victim->name);
						FREE (victim, _hoops_AAPIR);
					} while (*item != null);

					if (!option->_hoops_GCACR) {
						int				count;
						_hoops_HCRPR			*_hoops_HGPIR;

						count = option->_hoops_AIPCR;
						item	= &HOOPS_WORLD->_hoops_PAGHP;
						_hoops_HGPIR = option->value._name;

						while (count-- > 0) {
							if (_hoops_HGPIR->length > 0) {
								ALLOC (*item, _hoops_AAPIR);
								HI_Copy_Name (_hoops_HGPIR, &(*item)->name);
								item = &(*item)->next;
								*item = null;
							}
							++_hoops_HGPIR;
						}
					}
					_hoops_IRRPR();
				}	break;

				case _hoops_AGCPP: {
					_hoops_AAPIR	**item;

					_hoops_RPPPR();
					/* _hoops_CIH _hoops_GII _hoops_RHGS _hoops_RPPCR */
					if (*(item = &HOOPS_WORLD->_hoops_HAGHP) != null) do {
						_hoops_AAPIR	*victim = *item;

						*item = victim->next;
						_hoops_RGAIR (victim->name);
						FREE (victim, _hoops_AAPIR);
					} while (*item != null);

					if (!option->_hoops_GCACR) {
						int				count;
						_hoops_HCRPR			*_hoops_HGPIR;

						count = option->_hoops_AIPCR;
						item	= &HOOPS_WORLD->_hoops_HAGHP;
						_hoops_HGPIR = option->value._name;

						while (count-- > 0) {
							if (_hoops_HGPIR->length > 0) {
								ALLOC (*item, _hoops_AAPIR);
								HI_Copy_Name (_hoops_HGPIR, &(*item)->name);
								item = &(*item)->next;
								*item = null;
							}
							++_hoops_HGPIR;
						}
					}
					_hoops_IRRPR();
				}	break;

				case _hoops_PACPP: {
					_hoops_RGAIR (HOOPS_WORLD->_hoops_GRHGA);
					if (!option->_hoops_GCACR)
						HI_Copy_Name (option->value._name, &HOOPS_WORLD->_hoops_GRHGA);
				}	break;

				case _hoops_HACPP: {
					_hoops_RGAIR (HOOPS_WORLD->_hoops_PARPR);
					if (!option->_hoops_GCACR) {
						HI_Copy_Name (option->value._name, &HOOPS_WORLD->_hoops_PARPR);
						HI_Read_Driver_Config_File();
					}
				}	break;


				case _hoops_SACPP: {
					// _hoops_AA _hoops_ISAP
				}	break;

				case _hoops_PGCPP: {
					if (option->_hoops_GCACR)
						HOOPS_WORLD->_hoops_HPSPP = false;
					else if (option->_hoops_AIPCR > 0)
						_hoops_GPSPP (context, option->value.option_list);
				}	break;

				case _hoops_IGCPP: {
					bool _hoops_IAGHP = false;

					if (!option->_hoops_GCACR) {
						if (option->_hoops_AIPCR > 0) {
							if (option->value.option_list->type->id == _hoops_SHCPP)
								_hoops_IAGHP = true;
						}
						else
							_hoops_IAGHP = true;
					}

					if (BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP)) {
						if (!_hoops_IAGHP) {
							HI_Use_Memory_Task(HOOPS_WORLD->memory_pool, false);
							HOOPS_WORLD->system_flags &= ~_hoops_HCAGP;
						}
					}
					else {
						if (_hoops_IAGHP) {
							HOOPS_WORLD->system_flags |= _hoops_HCAGP;
							HI_Use_Memory_Task(HOOPS_WORLD->memory_pool, true);
						}
					}

					context._hoops_IGSCA();

#ifdef DISABLE_MUTEX
					if (BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP))
						HE_ERROR2 (0, 0, _hoops_CAGHP (_hoops_SAGHP), "Multi-threading");
#endif
				}	break;

				case _hoops_PRCPP: {
					if (option->_hoops_GCACR)
						context->_hoops_IAPCR = 0;
					else {
						context->_hoops_IAPCR = option->value._hoops_RIARA[0];
						HI_Ensure_Definition_Set(context);
					}
				}	break;

				case _hoops_HRCPP: {
					_hoops_HCRPR *		_hoops_GPGHP;

					_hoops_GPGHP = &_hoops_RSPPR(context, _hoops_ISHAP);

					_hoops_RGAIR (*_hoops_GPGHP);
					if (option->_hoops_GCACR) {}
					else if (option->value._name->text[option->value._name->length-1] == '/') {
						_hoops_GPGHP->length = option->value._name->length-1;
						ALLOC_ARRAY(_hoops_GPGHP->text, _hoops_GPGHP->length, char);
						_hoops_AIGA(option->value._name->text, _hoops_GPGHP->length, char, _hoops_GPGHP->text);
						_hoops_GPGHP->text[_hoops_GPGHP->length]='\0';
					}
					else
						HI_Copy_Name (option->value._name, _hoops_GPGHP);
				}	break;

				case _hoops_IRCPP: {
					if (option->_hoops_GCACR) {
						_hoops_RSPPR(context, _hoops_RPGHP) = HOOPS_WORLD->root;
					}
					else {
						_hoops_CSPPR();
						_hoops_CRCP *  _hoops_SRCP = HI_One_Segment_Search (context, option->value._name->text, true);
						_hoops_IRRPR();

						if (_hoops_SRCP)
							_hoops_RSPPR(context, _hoops_RPGHP) = _hoops_SRCP;
					}
				}	break;

				case _hoops_SRCPP: {
					if (option->_hoops_GCACR) {
						_hoops_RSPPR(context, flags) |= _hoops_GRSCA;
					}
					else {
						Option_Value *		_hoops_AHSAA;

						if ((_hoops_AHSAA = option->value.option_list) == null)
							_hoops_RSPPR(context, flags) &= ~_hoops_GRSCA;
						else do {
							if (_hoops_AHSAA->type->id == 0) {
								_hoops_RSPPR(context, flags) |= _hoops_GRSCA;
								context->flags  |= _hoops_RRSCA;
							}
							else {
								if (_hoops_AHSAA->_hoops_GCACR) {
									if (BIT (_hoops_AHSAA->type->id, _hoops_GPCPP))
										_hoops_RSPPR(context, flags) |= _hoops_GRSCA;
									if (BIT (_hoops_AHSAA->type->id, _hoops_RPCPP))
										context->flags |= _hoops_RRSCA;
								}
								else {
									if (BIT (_hoops_AHSAA->type->id, _hoops_GPCPP))
										_hoops_RSPPR(context, flags) &= ~_hoops_GRSCA;
									if (BIT (_hoops_AHSAA->type->id, _hoops_RPCPP))
										context->flags &= ~_hoops_RRSCA;
								}
							}
						} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
					}
				}	break;

				case _hoops_IACPP: {
					if (option->_hoops_GCACR)
						_hoops_RSPPR(context, flags) |= _hoops_APGHP;
					else
						_hoops_RSPPR(context, flags) &= ~_hoops_APGHP;
				}	break;

				case Sysop_RAW_MEMORY:
				case _hoops_GACPP:
				case _hoops_RACPP:
				case _hoops_CRCPP: {
					/* _hoops_ISAP _hoops_IS _hoops_AA */
				}	break;

				default: {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
										"Unrecognized system option type");
				}	break;
			}
		} while ((option = option->next) != null);

		HI_Free_Option_List (context, option_list);
	}

	HOOPS_WORLD->error_mask = _hoops_AHSPP;
	_hoops_AIGA (_hoops_PHSPP, 4, _hoops_CPSPP *, HOOPS_WORLD->_hoops_PSSPP);

	HOOPS_WORLD->_hoops_IRARR &= ~_hoops_IHSPP;
	HOOPS_WORLD->_hoops_IRARR |= _hoops_HHSPP;
}




local char *_hoops_PPGHP (
	char			*_hoops_ASAPR) {

	if (_hoops_ASAPR == null)
		return null;

	_hoops_ASAPR[0] = 'n'; _hoops_ASAPR[1] = 'o'; _hoops_ASAPR[2] = ' ';
	return _hoops_ASAPR + 3;
}


local char *_hoops_HPGHP (
	char			*_hoops_ASAPR,
	char const		*string) {

	if (_hoops_ASAPR == null)
		return null;

	do *_hoops_ASAPR++ = *string++;
	_hoops_RGGA (*string == '\0');

	*_hoops_ASAPR++ = ',';
	return _hoops_ASAPR;
}

local char * _hoops_IPGHP (
	_hoops_CPSPP const *		_hoops_CPGHP,
	int							_hoops_GHSPP,
	char const *				_hoops_SPGHP,
	char *						_hoops_ASAPR,
	char *						_hoops_PSAPR) {
	_hoops_CPSPP const *		control;
	int							count;

	/* _hoops_GII _hoops_GIAGR _hoops_IH _hoops_RGR _hoops_RGSR? */
	count = 0;
	control = _hoops_CPGHP;
	do if (control->_hoops_GHSPP == _hoops_GHSPP) {
		if (++count > 1)	/* _hoops_RAPR _hoops_IS _hoops_ACPA _hoops_SR _hoops_HHGC ()_hoops_GRI */
			break;
	} while ((control = control->next) != null);

	/* _hoops_GII _hoops_IS _hoops_GGI? */
	if (count > 0) {
		_hoops_ASAPR = HI_Copy_Chars (_hoops_SPGHP, _hoops_ASAPR);
		_hoops_ASAPR = HI_Copy_Chars ("=", _hoops_ASAPR);
		if (count > 1)
			_hoops_ASAPR = HI_Copy_Chars ("(", _hoops_ASAPR);

		count = 0;
		control = _hoops_CPGHP;
		do if (control->_hoops_GHSPP == _hoops_GHSPP) {
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%d", &control->category);
			_hoops_ASAPR = HI_Copy_Chars ("/", _hoops_ASAPR);
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%d", &control->specific);
			_hoops_ASAPR = HI_Copy_Chars (",", _hoops_ASAPR);
			++count;
		} while ((control = control->next) != null);
		if (_hoops_ASAPR != null)
			--_hoops_ASAPR;
		if (count > 1)
			_hoops_ASAPR = HI_Copy_Chars (")", _hoops_ASAPR);
		_hoops_ASAPR = HI_Copy_Chars (",", _hoops_ASAPR);
	}

	return _hoops_ASAPR;
}

local char * _hoops_GHGHP (
	bool					_hoops_CAPRA,
	_hoops_CPSPP const *	_hoops_CPGHP,
	char *						_hoops_ASAPR,
	char *						_hoops_PSAPR) {

	if (_hoops_CAPRA)
		_hoops_ASAPR = HI_Copy_Chars ("on,", _hoops_ASAPR);
	else
		_hoops_ASAPR = HI_Copy_Chars ("off,", _hoops_ASAPR);

	if (_hoops_CPGHP != null) {
		_hoops_ASAPR = _hoops_IPGHP (_hoops_CPGHP, _hoops_GCCPP,  "disable", _hoops_ASAPR, _hoops_PSAPR);
		_hoops_ASAPR = _hoops_IPGHP (_hoops_CPGHP, _hoops_RCCPP,   "enable",  _hoops_ASAPR, _hoops_PSAPR);
		_hoops_ASAPR = _hoops_IPGHP (_hoops_CPGHP, _hoops_ACCPP, "once",    _hoops_ASAPR, _hoops_PSAPR);
	}
	if (_hoops_ASAPR != null)
		*--_hoops_ASAPR = '\0';	/* _hoops_HASIR _hoops_HACH ',' */

	return _hoops_ASAPR;
}


HC_INTERFACE void HC_CDECL HC_Show_System_Options (
	char *		list)
{
	_hoops_PAPPR context("Show_System_Options");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_System_Options () */\n");
	);

	char					buf[4096];
	char					*_hoops_ASAPR = buf;
	char					*_hoops_PSAPR = buf+_hoops_GGAPR(buf)-1;


	if (HOOPS_WORLD->_hoops_PSSPP[0] != null) {
		_hoops_ASAPR = HI_Copy_Chars ("info=(", _hoops_ASAPR);
		_hoops_ASAPR = _hoops_GHGHP (!BIT (HOOPS_WORLD->error_mask, 1<<0), HOOPS_WORLD->_hoops_PSSPP[0], _hoops_ASAPR, _hoops_PSAPR);
		_hoops_ASAPR = HI_Copy_Chars ("),", _hoops_ASAPR);
	}
	else {
		if (BIT (HOOPS_WORLD->error_mask, 1<<0)) _hoops_ASAPR = _hoops_PPGHP (_hoops_ASAPR);
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "info");
	}

	if (HOOPS_WORLD->_hoops_PSSPP[1] != null) {
		_hoops_ASAPR = HI_Copy_Chars ("warnings=(", _hoops_ASAPR);
		_hoops_ASAPR = _hoops_GHGHP (!BIT (HOOPS_WORLD->error_mask, 1<<1), HOOPS_WORLD->_hoops_PSSPP[1], _hoops_ASAPR, _hoops_PSAPR);
		_hoops_ASAPR = HI_Copy_Chars ("),", _hoops_ASAPR);
	}
	else {
		if (BIT (HOOPS_WORLD->error_mask, 1<<0)) _hoops_ASAPR = _hoops_PPGHP (_hoops_ASAPR);
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "warnings");
	}

	if (HOOPS_WORLD->_hoops_PSSPP[2] != null) {
		_hoops_ASAPR = HI_Copy_Chars ("errors=(", _hoops_ASAPR);
		_hoops_ASAPR = _hoops_GHGHP (!BIT (HOOPS_WORLD->error_mask, 1<<2), HOOPS_WORLD->_hoops_PSSPP[2], _hoops_ASAPR, _hoops_PSAPR);
		_hoops_ASAPR = HI_Copy_Chars ("),", _hoops_ASAPR);
	}
	else {
		if (BIT (HOOPS_WORLD->error_mask, 1<<0)) _hoops_ASAPR = _hoops_PPGHP (_hoops_ASAPR);
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "errors");
	}

	if (HOOPS_WORLD->_hoops_PSSPP[3] != null) {
		_hoops_ASAPR = HI_Copy_Chars ("fatal errors=(", _hoops_ASAPR);
		_hoops_ASAPR = _hoops_GHGHP (!BIT (HOOPS_WORLD->error_mask, 1<<3), HOOPS_WORLD->_hoops_PSSPP[3], _hoops_ASAPR, _hoops_PSAPR);
		_hoops_ASAPR = HI_Copy_Chars ("),", _hoops_ASAPR);
	}
	else {
		if (BIT (HOOPS_WORLD->error_mask, 1<<0)) _hoops_ASAPR = _hoops_PPGHP (_hoops_ASAPR);
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "fatal errors");
	}

	if (!BIT (HOOPS_WORLD->system_flags, _hoops_HSCPP)) _hoops_ASAPR = _hoops_PPGHP (_hoops_ASAPR);
	_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "continuous update");
	if (!BIT (HOOPS_WORLD->system_flags, _hoops_ISCPP)) _hoops_ASAPR = _hoops_PPGHP (_hoops_ASAPR);
	_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "obsolete checking");
	// _hoops_SHR _hoops_GPP
	_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "sanity checking");
	// _hoops_SHR _hoops_GPP
	_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "bounding volumes");
	if (!BIT (HOOPS_WORLD->system_flags, _hoops_IGHGA)) _hoops_ASAPR = _hoops_PPGHP (_hoops_ASAPR);
	_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "code generation");
	if (!BIT (HOOPS_WORLD->system_flags, _hoops_RGRI)) _hoops_ASAPR = _hoops_PPGHP (_hoops_ASAPR);
	_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "generate consistent normals");

	if (!BIT (HOOPS_WORLD->system_flags, _hoops_PGSPP)) _hoops_ASAPR = _hoops_PPGHP (_hoops_ASAPR);
	_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "conserve memory");
	if (BIT (HOOPS_WORLD->system_flags, _hoops_PGSPP) &&
		HOOPS_WORLD->_hoops_HGGHR != _hoops_HICPP) {
			_hoops_ASAPR[-1] = '=';
			*_hoops_ASAPR++ = '(';
			if (!BIT (HOOPS_WORLD->_hoops_HGGHR, _hoops_SRRIR))
				_hoops_ASAPR = _hoops_PPGHP (_hoops_ASAPR);
			_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "face list");
			if (!BIT (HOOPS_WORLD->_hoops_HGGHR, _hoops_IICPP))
				_hoops_ASAPR = _hoops_PPGHP (_hoops_ASAPR);
			_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "facings");
			if (!BIT (HOOPS_WORLD->_hoops_HGGHR, _hoops_AHSSR))
				_hoops_ASAPR = _hoops_PPGHP (_hoops_ASAPR);
			_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "circles");
			if (!BIT (HOOPS_WORLD->_hoops_HGGHR, _hoops_IGGHR))
				_hoops_ASAPR = _hoops_PPGHP (_hoops_ASAPR);
			_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "polyedges");
			_hoops_ASAPR[-1] = ')';
			*_hoops_ASAPR++ = ',';
	}

	if (!BIT (HOOPS_WORLD->system_flags, _hoops_AGSPP)) _hoops_ASAPR = _hoops_PPGHP (_hoops_ASAPR);
	_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "shell restrip on point edit");
	if (!BIT (HOOPS_WORLD->system_flags, _hoops_CSRRA)) _hoops_ASAPR = _hoops_PPGHP (_hoops_ASAPR);
	_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "region tristrips");
	if (!BIT (HOOPS_WORLD->system_flags, _hoops_GGSPP)) _hoops_ASAPR = _hoops_PPGHP (_hoops_ASAPR);
	_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "legacy mesh face numbering");
	if (!BIT (HOOPS_WORLD->system_flags, _hoops_RGSPP)) _hoops_ASAPR = _hoops_PPGHP (_hoops_ASAPR);
	_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "legacy text extent");
	if (!BIT (HOOPS_WORLD->system_flags, _hoops_SSCPP)) _hoops_ASAPR = _hoops_PPGHP (_hoops_ASAPR);
	_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "old style pathnames");

	if (BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP))
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "multithreading");
	else
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "no multithreading");

	if (HOOPS_WORLD->_hoops_RAPPR == _hoops_AGGHP)
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "no C string length");
	else
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "C string length=%d,",
		(void *)&HOOPS_WORLD->_hoops_RAPPR);

	_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "application=%qn,",
		(void *)&HOOPS_WORLD->_hoops_GRGHP);


	if (HOOPS_WORLD->_hoops_RRGHP == 0)
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "no message limit");
	else
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "message limit=%d,",
		(void *)&HOOPS_WORLD->_hoops_RRGHP);

	if (HOOPS_WORLD->_hoops_PRGHP == _hoops_IICIA)
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "no string_history limit");
	else
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "string history limit=%d,",
		(void *)&HOOPS_WORLD->_hoops_PRGHP);

	if (HOOPS_WORLD->_hoops_IRARR == 0)
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "no debug");
	else
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "debug=%d,", (void *)&HOOPS_WORLD->_hoops_IRARR);

	_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "camera near limit=%f,", (void *)&HOOPS_WORLD->_hoops_GCPCR);

	if (HOOPS_WORLD->_hoops_RAGHP == false)
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "extended font search");
	else
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "no extended font search");

	if (HOOPS_WORLD->_hoops_PHARR == _hoops_CSSPP)
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "no video memory limit");
	else
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "video memory limit=%P,", (void *)&HOOPS_WORLD->_hoops_PHARR);

	if (HOOPS_WORLD->_hoops_SRGHP == 0)
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "no processor override");
	else
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "processor override=%d,",
		(void *)&HOOPS_WORLD->_hoops_SRGHP);

	if (HOOPS_WORLD->_hoops_PGGHP == nullroutine)
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "no event checker");
	else if (HOOPS_WORLD->_hoops_HGGHP != null)
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "event checker=%n,",
		(void *)&HOOPS_WORLD->_hoops_HGGHP->name);
	else
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "event checker=%D,",
		(void *)&HOOPS_WORLD->_hoops_PGGHP);

	if (HOOPS_WORLD->_hoops_HHRIR == nullroutine)
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "no deleted key callback");
	else
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "deleted key callback=%n,",
		(void *)&HOOPS_WORLD->_hoops_CGGHP->name);

	if (HOOPS_WORLD->_hoops_AAGHP == null) {
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "no font directory");
	}
	else {
		_hoops_AAPIR			*item = HOOPS_WORLD->_hoops_AAGHP;

		_hoops_ASAPR = HI_Copy_Chars ("font directory=", _hoops_ASAPR);
		if (item->next != null) _hoops_ASAPR = HI_Copy_Chars ("(", _hoops_ASAPR);
		do _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn,", (void *)&item->name);
		_hoops_RGGA ((item = item->next) == null);
		if (_hoops_ASAPR != null) --_hoops_ASAPR;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
		if (HOOPS_WORLD->_hoops_AAGHP->next != null) _hoops_ASAPR = HI_Copy_Chars (")", _hoops_ASAPR);
		_hoops_ASAPR = HI_Copy_Chars (",", _hoops_ASAPR);
	}

	if (HOOPS_WORLD->_hoops_PAGHP == null) {
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "no driver directory");
	}
	else {
		_hoops_AAPIR			*item = HOOPS_WORLD->_hoops_PAGHP;

		_hoops_ASAPR = HI_Copy_Chars ("driver directory=", _hoops_ASAPR);
		if (item->next != null) _hoops_ASAPR = HI_Copy_Chars ("(", _hoops_ASAPR);
		do _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn,", (void *)&item->name);
		_hoops_RGGA ((item = item->next) == null);
		if (_hoops_ASAPR != null) --_hoops_ASAPR;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
		if (HOOPS_WORLD->_hoops_PAGHP->next != null) _hoops_ASAPR = HI_Copy_Chars (")", _hoops_ASAPR);
		_hoops_ASAPR = HI_Copy_Chars (",", _hoops_ASAPR);
	}

	/* _hoops_PSP _hoops_GRCIR _hoops_RRCIR */
	if (HOOPS_WORLD->_hoops_HAGHP == null) {
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "no metafile directory");
	}
	else {
		_hoops_AAPIR			*item = HOOPS_WORLD->_hoops_HAGHP;

		_hoops_ASAPR = HI_Copy_Chars ("metafile directory=", _hoops_ASAPR);
		if (item->next != null) _hoops_ASAPR = HI_Copy_Chars ("(", _hoops_ASAPR);
		do _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn,", (void *)&item->name);
		_hoops_RGGA ((item = item->next) == null);
		if (_hoops_ASAPR != null) --_hoops_ASAPR;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
		if (HOOPS_WORLD->_hoops_HAGHP->next != null)
			_hoops_ASAPR = HI_Copy_Chars (")", _hoops_ASAPR);
		_hoops_ASAPR = HI_Copy_Chars (",", _hoops_ASAPR);
	}

	if (HOOPS_WORLD->_hoops_GRHGA.length == 0)
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "no code generation directory");
	else
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "code generation directory=%qn,", (void*)&HOOPS_WORLD->_hoops_GRHGA);

	if (HOOPS_WORLD->_hoops_PARPR.length == 0)
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "no driver config file");
	else
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "driver config file=%qn,", (void*)&HOOPS_WORLD->_hoops_PARPR);

	/* _hoops_IPPHR _hoops_ARP _hoops_SASI */

	_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "definition set=%d,", (void *)&context->_hoops_IAPCR);

	if (_hoops_RSPPR(context, _hoops_ISHAP).length > 0)
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "metafile root=%n,", (void *)&_hoops_RSPPR(context, _hoops_ISHAP));

	if (_hoops_RSPPR(context, _hoops_RPGHP) != HOOPS_WORLD->root)
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "texture root=%p,", (void *)_hoops_RSPPR(context, _hoops_RPGHP));

	if (BIT (_hoops_RSPPR(context, flags), _hoops_APGHP))
		_hoops_ASAPR = _hoops_HPGHP(_hoops_ASAPR, "automatic geometry boundings");


	if (!BIT (context->flags, _hoops_RRSCA)) {
		if (BIT (_hoops_RSPPR(context, flags), _hoops_GRSCA))
			_hoops_ASAPR = _hoops_PPGHP (_hoops_ASAPR);
		_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "update control");
	}
	else {
		if (BIT (_hoops_RSPPR(context, flags), _hoops_GRSCA))
			_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "update control=none");
		else
			_hoops_ASAPR = _hoops_HPGHP (_hoops_ASAPR, "update control=thread");
	}

	_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "dpi scale factor=%f,", (void *)&HOOPS_WORLD->_hoops_IRGHP);

	if (_hoops_ASAPR != null) --_hoops_ASAPR;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */

	HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
}




local void _hoops_RHGHP (
	bool	_hoops_CAPRA,
	char *	list,
	int	_hoops_GGCIR)
{
	if (_hoops_CAPRA)
		HI_Return_Chars (list, _hoops_GGCIR, "on", 2);
	else
		HI_Return_Chars (list, _hoops_GGCIR, "off", 3);
}


HC_INTERFACE void HC_CDECL HC_Show_One_System_Option (
	char const *		which,
	char *				list)
{
	_hoops_HCRPR			_hoops_AHGHP;
	local _hoops_SRHSR
		info = _hoops_GRRCR ("info"),
		error = _hoops_GRRCR ("error"),
		errors = _hoops_GRRCR ("errors"),
		warning = _hoops_GRRCR ("warning"),
		_hoops_PHGHP = _hoops_GRRCR ("warnings"),
		_hoops_HHGHP = _hoops_GRRCR ("fatal error"),
		_hoops_IHGHP = _hoops_GRRCR ("fatal errors"),
		_hoops_CHGHP = _hoops_GRRCR ("continuous update"),
		_hoops_SHGHP = _hoops_GRRCR ("continuous updates"),
		_hoops_GIGHP = _hoops_GRRCR ("obsolete checking"),
		_hoops_RIGHP = _hoops_GRRCR ("sanity checking"),
		_hoops_AIGHP = _hoops_GRRCR ("bounding volumes"),
		_hoops_PIGHP = _hoops_GRRCR ("code generation"),
		_hoops_HIGHP = _hoops_GRRCR ("generate consistent normals"),
		_hoops_IIGHP = _hoops_GRRCR ("update control"),
		_hoops_CIGHP = _hoops_GRRCR ("c string length"),
		_hoops_GRGHP = _hoops_GRRCR ("application"),
		_hoops_RRGHP = _hoops_GRRCR ("message limit"),
		_hoops_PRGHP = _hoops_GRRCR ("string history limit"),
		_hoops_IRARR = _hoops_GRRCR ("debug"),
		_hoops_GCPCR = _hoops_GRRCR ("camera near limit"),
		_hoops_IRGHP = _hoops_GRRCR ("dpi scale factor"),
		_hoops_SIGHP = _hoops_GRRCR ("processor override"),
		_hoops_GCGHP = _hoops_GRRCR ("conserve memory"),
		_hoops_AAGHP = _hoops_GRRCR ("font directory"),
		_hoops_RCGHP = _hoops_GRRCR ("extended font search"),
		_hoops_CARH = _hoops_GRRCR ("video memory"),
		_hoops_PHARR = _hoops_GRRCR ("video memory limit"),
		_hoops_PAGHP = _hoops_GRRCR ("driver directory"),
		_hoops_HAGHP = _hoops_GRRCR ("metafile directory"),
		_hoops_GRHGA = _hoops_GRRCR ("code generation directory"),
		_hoops_PARPR = _hoops_GRRCR ("driver config file"),
		_hoops_PGGHP = _hoops_GRRCR ("event checker"),
		_hoops_HHRIR = _hoops_GRRCR ("deleted key callback"),
		_hoops_ACGHP = _hoops_GRRCR ("restrip on edit"),
		_hoops_PCGHP = _hoops_GRRCR ("shell restrip on point edit"),
		_hoops_HCGHP = _hoops_GRRCR ("region tristrips"),
		_hoops_ICGHP  = _hoops_GRRCR ("legacy mesh face numbering"),
		_hoops_CCGHP  = _hoops_GRRCR ("legacy text extent"),
		_hoops_SCGHP = _hoops_GRRCR ("old style pathnames"),
		_hoops_GSGHP = _hoops_GRRCR ("old-style pathnames"),
		_hoops_RSGHP = _hoops_GRRCR ("multithreading"),
		_hoops_ASGHP = _hoops_GRRCR ("multi-threading"),
		_hoops_PSGHP = _hoops_GRRCR ("multithreaded"),
		_hoops_HSGHP = _hoops_GRRCR ("multi-threaded"),
		_hoops_ISGHP = _hoops_GRRCR ("definition set"),
		_hoops_ISHAP = _hoops_GRRCR ("metafile root"),
		_hoops_RPGHP = _hoops_GRRCR ("texture root");
	char			buf[4096],
		*_hoops_ASAPR = buf;

	_hoops_PAPPR context("Show_One_System_Option");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_System_Option () */\n");
	);

	HI_Canonize_Chars (which, &_hoops_AHGHP);

	if (_hoops_RAHSR (info, _hoops_AHGHP)) {
		_hoops_ASAPR = _hoops_GHGHP (!BIT (HOOPS_WORLD->error_mask, 1<<0), HOOPS_WORLD->_hoops_PSSPP[0], _hoops_ASAPR, buf+_hoops_GGAPR(buf));
		HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (_hoops_RAHSR (warning, _hoops_AHGHP) ||
		_hoops_RAHSR (_hoops_PHGHP, _hoops_AHGHP)) {
			_hoops_ASAPR = _hoops_GHGHP (!BIT (HOOPS_WORLD->error_mask, 1<<1), HOOPS_WORLD->_hoops_PSSPP[1], _hoops_ASAPR, buf+_hoops_GGAPR(buf));
			HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (_hoops_RAHSR (error, _hoops_AHGHP) ||
		_hoops_RAHSR (errors, _hoops_AHGHP)) {
			_hoops_ASAPR = _hoops_GHGHP (!BIT (HOOPS_WORLD->error_mask, 1<<2), HOOPS_WORLD->_hoops_PSSPP[2], _hoops_ASAPR, buf+_hoops_GGAPR(buf));
			HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (_hoops_RAHSR (_hoops_HHGHP, _hoops_AHGHP) ||
		_hoops_RAHSR (_hoops_IHGHP, _hoops_AHGHP)) {
			_hoops_ASAPR = _hoops_GHGHP (!BIT (HOOPS_WORLD->error_mask, 1<<3), HOOPS_WORLD->_hoops_PSSPP[3], _hoops_ASAPR, buf+_hoops_GGAPR(buf));
			HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (_hoops_RAHSR (_hoops_CIGHP, _hoops_AHGHP)) {
		if (HOOPS_WORLD->_hoops_RAPPR == _hoops_AGGHP)
			HI_Return_Chars (list, -1, "off", 3);
		else {
			_hoops_ASAPR = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf), "%d",
				(void *)&HOOPS_WORLD->_hoops_RAPPR);
			HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
		}
	}
	else if (_hoops_RAHSR (_hoops_RRGHP, _hoops_AHGHP)) {
		if (HOOPS_WORLD->_hoops_RRGHP == 0)
			HI_Return_Chars (list, -1, "off", 3);
		else {
			_hoops_ASAPR = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf), "%d",
				(void *)&HOOPS_WORLD->_hoops_RRGHP);
			HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
		}
	}
	else if (_hoops_RAHSR (_hoops_PRGHP, _hoops_AHGHP)) {
		if (HOOPS_WORLD->_hoops_PRGHP == _hoops_IICIA)
			HI_Return_Chars (list, -1, "off", 3);
		else {
			_hoops_ASAPR = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf), "%d",
				(void *)&HOOPS_WORLD->_hoops_PRGHP);
			HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
		}
	}
	else if (_hoops_RAHSR (_hoops_RCGHP, _hoops_AHGHP)) {
		if (HOOPS_WORLD->_hoops_RAGHP == false)
			HI_Return_Chars (list, -1, "on", 2);
		else {
			HI_Return_Chars (list, -1, "off", 3);
		}
	}
	else if (_hoops_RAHSR (_hoops_PHARR, _hoops_AHGHP) ||
		_hoops_RAHSR (_hoops_CARH, _hoops_AHGHP)) {
			if (HOOPS_WORLD->_hoops_PHARR == _hoops_CSSPP)
				HI_Return_Chars (list, -1, "no video memory limit", 21);
			else {
				_hoops_ASAPR = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf), "%d",
					(void *)&HOOPS_WORLD->_hoops_PHARR);
				HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
			}
	}
	else if (_hoops_RAHSR (_hoops_IRARR, _hoops_AHGHP)) {
		if (HOOPS_WORLD->_hoops_IRARR == 0)
			HI_Return_Chars (list, -1, "off", 3);
		else {
			_hoops_ASAPR = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf), "%d",
				(void *)&HOOPS_WORLD->_hoops_IRARR);
			HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
		}
	}
	else if (_hoops_RAHSR (_hoops_GCPCR, _hoops_AHGHP)) {
		_hoops_ASAPR = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf), "%f",
			(void *)&HOOPS_WORLD->_hoops_GCPCR);
		HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (_hoops_RAHSR (_hoops_IRGHP, _hoops_AHGHP)) {
		_hoops_ASAPR = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf), "%f",
			(void *)&HOOPS_WORLD->_hoops_IRGHP);
		HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (_hoops_RAHSR (_hoops_SIGHP, _hoops_AHGHP)) {
		if (HOOPS_WORLD->_hoops_SRGHP == 0)
			HI_Return_Chars (list, -1, "off", 3);
		else {
			_hoops_ASAPR = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf), "%d",
				(void *)&HOOPS_WORLD->_hoops_SRGHP);
			HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
		}
	}
	else if (_hoops_RAHSR (_hoops_PGGHP, _hoops_AHGHP)) {
		if (HOOPS_WORLD->_hoops_PGGHP == nullroutine)
			HI_Return_Chars (list, -1, "off", 3);
		else if (HOOPS_WORLD->_hoops_HGGHP != null)
			_hoops_ASAPR = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf), "%n",
			(void *)&HOOPS_WORLD->_hoops_HGGHP->name);
		else {
			_hoops_ASAPR = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf), "%D",
				(void *)&HOOPS_WORLD->_hoops_PGGHP);
			HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
		}
	}
	else if (_hoops_RAHSR (_hoops_HHRIR, _hoops_AHGHP)) {
		if (HOOPS_WORLD->_hoops_HHRIR == nullroutine)
			HI_Return_Chars (list, -1, "off", 3);
		else
			_hoops_ASAPR = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf), "%n",
			(void *)&HOOPS_WORLD->_hoops_CGGHP->name);
	}
	else if (_hoops_RAHSR (_hoops_GRGHP, _hoops_AHGHP))
		HI_Return_Chars (list, -1, HOOPS_WORLD->_hoops_GRGHP.text,
		HOOPS_WORLD->_hoops_GRGHP.length);
	else if (_hoops_RAHSR (_hoops_AAGHP, _hoops_AHGHP)) {
		if (HOOPS_WORLD->_hoops_AAGHP == null)
			HI_Return_Chars (list, -1, "off", 3);
		else {
			_hoops_AAPIR *	item = HOOPS_WORLD->_hoops_AAGHP;

			_hoops_ASAPR = buf;

			do _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, buf+_hoops_GGAPR(buf), "%qn,", (void *)&item->name);
			_hoops_RGGA ((item = item->next) == null);

			if (_hoops_ASAPR != null)
				--_hoops_ASAPR;		/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */

			HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
		}
	}
	else if (_hoops_RAHSR (_hoops_PAGHP, _hoops_AHGHP)) {
		if (HOOPS_WORLD->_hoops_PAGHP == null)
			HI_Return_Chars (list, -1, "off", 3);
		else {
			_hoops_AAPIR *	item = HOOPS_WORLD->_hoops_PAGHP;

			_hoops_ASAPR = buf;

			do _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, buf+_hoops_GGAPR(buf), "%qn,", (void *)&item->name);
			_hoops_RGGA ((item = item->next) == null);

			if (_hoops_ASAPR != null)
				--_hoops_ASAPR;		/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */

			HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
		}
	}
	else if (_hoops_RAHSR (_hoops_HAGHP, _hoops_AHGHP)) {
		if (HOOPS_WORLD->_hoops_HAGHP == null)
			HI_Return_Chars (list, -1, "off", 3);
		else {
			_hoops_AAPIR *	item = HOOPS_WORLD->_hoops_HAGHP;

			_hoops_ASAPR = buf;

			do _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, buf+_hoops_GGAPR(buf), "%qn,", (void *)&item->name);
			_hoops_RGGA ((item = item->next) == null);
			if (_hoops_ASAPR != null)
				--_hoops_ASAPR;		/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */

			HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
		}
	}
	else if (_hoops_RAHSR (_hoops_GRHGA, _hoops_AHGHP)) {
		if (HOOPS_WORLD->_hoops_GRHGA.length == 0)
			HI_Return_Chars (list, -1, "off", 3);
		else {
			HI_Return_Chars (list, -1, HOOPS_WORLD->_hoops_GRHGA.text,
				HOOPS_WORLD->_hoops_GRHGA.length);
		}
	}
	else if (_hoops_RAHSR (_hoops_PARPR, _hoops_AHGHP)) {
		if (HOOPS_WORLD->_hoops_PARPR.length == 0)
			HI_Return_Chars (list, -1, "off", 3);
		else {
			HI_Return_Chars (list, -1, HOOPS_WORLD->_hoops_PARPR.text,
				HOOPS_WORLD->_hoops_PARPR.length);
		}
	}
	else if (_hoops_RAHSR (_hoops_CHGHP, _hoops_AHGHP) ||
		_hoops_RAHSR (_hoops_SHGHP, _hoops_AHGHP))
		_hoops_RHGHP (BIT (HOOPS_WORLD->system_flags, _hoops_HSCPP), list, -1);
	else if (_hoops_RAHSR (_hoops_GIGHP, _hoops_AHGHP))
		_hoops_RHGHP (BIT (HOOPS_WORLD->system_flags, _hoops_ISCPP), list, -1);
	else if (_hoops_RAHSR (_hoops_RIGHP, _hoops_AHGHP))
		_hoops_RHGHP (true, list, -1);
	else if (_hoops_RAHSR (_hoops_AIGHP, _hoops_AHGHP))
		_hoops_RHGHP (true, list, -1);
	else if (_hoops_RAHSR (_hoops_PIGHP, _hoops_AHGHP))
		_hoops_RHGHP (BIT (HOOPS_WORLD->system_flags, _hoops_IGHGA), list, -1);
	else if (_hoops_RAHSR (_hoops_HIGHP, _hoops_AHGHP))
		_hoops_RHGHP (BIT (HOOPS_WORLD->system_flags, _hoops_RGRI), list, -1);
	else if (_hoops_RAHSR (_hoops_GCGHP, _hoops_AHGHP)) {
		_hoops_RHGHP (BIT (HOOPS_WORLD->system_flags, _hoops_PGSPP), list, -1);
		if (!BIT (HOOPS_WORLD->system_flags, _hoops_PGSPP))
			HI_Return_Chars (list, -1, "off", 3);
		else if (HOOPS_WORLD->_hoops_HGGHR == _hoops_HICPP)
			HI_Return_Chars (list, -1, "on", 2);
		else {
			_hoops_ASAPR = buf;

			if (!BIT (HOOPS_WORLD->_hoops_HGGHR, _hoops_SRRIR))
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, buf+_hoops_GGAPR(buf), "no face list,", null);
			else
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, buf+_hoops_GGAPR(buf), "face list,", null);

			if (!BIT (HOOPS_WORLD->_hoops_HGGHR, _hoops_IICPP))
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, buf+_hoops_GGAPR(buf), "no facings", null);
			else
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, buf+_hoops_GGAPR(buf), "facings", null);

			if (!BIT (HOOPS_WORLD->_hoops_HGGHR, _hoops_AHSSR))
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, buf+_hoops_GGAPR(buf), "no circles", null);
			else
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, buf+_hoops_GGAPR(buf), "circles", null);

			if (!BIT (HOOPS_WORLD->_hoops_HGGHR, _hoops_IGGHR))
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, buf+_hoops_GGAPR(buf), "no polyedges", null);
			else
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, buf+_hoops_GGAPR(buf), "polyedges", null);

			HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
		}
	}
	else if (_hoops_RAHSR (_hoops_ACGHP, _hoops_AHGHP) ||
		_hoops_RAHSR (_hoops_PCGHP, _hoops_AHGHP))
		_hoops_RHGHP (BIT (HOOPS_WORLD->system_flags, _hoops_AGSPP), list, -1);
	else if (_hoops_RAHSR (_hoops_HCGHP, _hoops_AHGHP))
		_hoops_RHGHP (BIT (HOOPS_WORLD->system_flags, _hoops_CSRRA), list, -1);
	else if (_hoops_RAHSR (_hoops_ICGHP, _hoops_AHGHP))
		_hoops_RHGHP (BIT (HOOPS_WORLD->system_flags, _hoops_GGSPP), list, -1);
	else if (_hoops_RAHSR (_hoops_CCGHP, _hoops_AHGHP))
		_hoops_RHGHP (BIT (HOOPS_WORLD->system_flags, _hoops_RGSPP), list, -1);
	else if (_hoops_RAHSR (_hoops_SCGHP, _hoops_AHGHP) ||
		_hoops_RAHSR (_hoops_GSGHP, _hoops_AHGHP))
		_hoops_RHGHP (BIT (HOOPS_WORLD->system_flags, _hoops_SSCPP), list, -1);
	else if (_hoops_RAHSR (_hoops_RSGHP, _hoops_AHGHP) ||
		_hoops_RAHSR (_hoops_ASGHP, _hoops_AHGHP) ||
		_hoops_RAHSR (_hoops_PSGHP, _hoops_AHGHP) ||
		_hoops_RAHSR (_hoops_HSGHP, _hoops_AHGHP)) {

			if (BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP))
				HI_Return_Chars (list, -1, "on", 2);
			else
				HI_Return_Chars (list, -1, "off", 3);
	}
	else if (_hoops_RAHSR (_hoops_IIGHP, _hoops_AHGHP)) {
		if (!BIT (context->flags, _hoops_RRSCA))
			_hoops_RHGHP (!BIT (_hoops_RSPPR(context, flags), _hoops_GRSCA), list, -1);
		else {
			if (BIT (_hoops_RSPPR(context, flags), _hoops_GRSCA))
				HI_Return_Chars (list, -1, "none", 2);
			else
				HI_Return_Chars (list, -1, "on", 2);
		}
	}
	else if (_hoops_RAHSR (_hoops_ISGHP, _hoops_AHGHP)) {
		_hoops_ASAPR = buf;
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, buf+_hoops_GGAPR(buf), "%d", (void*)&context->_hoops_IAPCR);

		HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
	}
	else if (_hoops_RAHSR (_hoops_ISHAP, _hoops_AHGHP)) {
		if (_hoops_RSPPR(context, _hoops_ISHAP).length > 0) {
			_hoops_ASAPR = buf;
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, buf+_hoops_GGAPR(buf), "%n", (void *)&_hoops_RSPPR(context, _hoops_ISHAP));

			HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
		}
		else
			HI_Return_Chars (list, -1, "", 0);
	}
	else if (_hoops_RAHSR (_hoops_RPGHP, _hoops_AHGHP)) {
		_hoops_ASAPR = buf;
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, buf+_hoops_GGAPR(buf), "%p", (void *)_hoops_RSPPR(context, _hoops_RPGHP));

		HI_Return_Chars (list, -1, buf, (int)(_hoops_ASAPR - buf));
	}
	else
		HE_ERROR (HEC_HOOPS_SYSTEM, HES_INVALID_OPTION,
		Sprintf_S (null, "'%s' is not a recognized system option type", which));

	_hoops_RGAIR(_hoops_AHGHP);
}



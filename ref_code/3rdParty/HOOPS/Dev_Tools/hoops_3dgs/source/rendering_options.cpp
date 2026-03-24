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
 * $Id: obf_tmp.txt 1.415 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "patterns.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

local const _hoops_IGRCR _hoops_SPARS[] = {
	{Display_List_NONE,				_hoops_GRRCR ("off"),						_hoops_RRRCR, 0, false},
	{Display_List_GEOMETRY,			_hoops_GRRCR ("on"),						_hoops_RRRCR, 0, false},
	{Display_List_GEOMETRY,			_hoops_GRRCR ("geometry"),					_hoops_RRRCR, 0, false},
	{Display_List_GEOMETRY,			_hoops_GRRCR ("entity"),					_hoops_RRRCR, 0, false},
	{Display_List_SEGMENT,			_hoops_GRRCR ("segment"),					_hoops_RRRCR, 0, false},
	{_hoops_ASAAP,		_hoops_GRRCR ("segment tree"),				_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_GHARS = {
	_hoops_GGAPR (_hoops_SPARS),		_hoops_SPARS,
};

local const _hoops_IGRCR _hoops_RHARS[] = {
	{_hoops_SGAAP,		_hoops_GRRCR ("hardware z buffer"),				_hoops_RRRCR, 0, false},
	{_hoops_SGAAP,		_hoops_GRRCR ("hardware z-buffer"),				_hoops_RRRCR, 0, false},
	{_hoops_GRAAP,				_hoops_GRRCR ("painter"),						_hoops_RRRCR, 0, false},
	{_hoops_GRAAP,				_hoops_GRRCR ("painters"),						_hoops_RRRCR, 0, false},
	{_hoops_RRAAP,		_hoops_GRRCR ("software z buffer"),				_hoops_RRRCR, 0, false},
	{_hoops_RRAAP,		_hoops_GRRCR ("software z-buffer"),				_hoops_RRRCR, 0, false},
	{_hoops_HSSS,			_hoops_GRRCR ("z-sort only"),					_hoops_RRRCR, 0, false},
	{_hoops_HSSS,			_hoops_GRRCR ("z sort only"),					_hoops_RRRCR, 0, false},
	{_hoops_CGAAP,					_hoops_GRRCR ("off"),							_hoops_RRRCR, 0, false},
	{_hoops_CGAAP,					_hoops_GRRCR ("no"),							_hoops_RRRCR, 0, false},
	{_hoops_CGAAP,					_hoops_GRRCR ("false"),							_hoops_RRRCR, 0, false},
	{_hoops_CGAAP,					_hoops_GRRCR ("none"),							_hoops_RRRCR, 0, false},

	/* _hoops_PHSSA */
	{_hoops_SGAAP,		_hoops_GRRCR ("hzb"),							_hoops_RRRCR, 0, false},
	{_hoops_RRAAP,		_hoops_GRRCR ("szb"),							_hoops_RRRCR, 0, false},
	{_hoops_HSSS,			_hoops_GRRCR ("zso"),							_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_AHARS = {
	_hoops_GGAPR (_hoops_RHARS),			_hoops_RHARS,
};

local const _hoops_IGRCR _hoops_PHARS[] = {
	{_hoops_CGAAP,					_hoops_GRRCR ("off"),							_hoops_RRRCR, 0, false},
	{_hoops_CGAAP,					_hoops_GRRCR ("no"),							_hoops_RRRCR, 0, false},
	{_hoops_CGAAP,					_hoops_GRRCR ("false"),							_hoops_RRRCR, 0, false},
	{_hoops_CGAAP,					_hoops_GRRCR ("none"),							_hoops_RRRCR, 0, false},

	{_hoops_HSSS,			_hoops_GRRCR ("on"),							_hoops_RRRCR, 0, false},
	{_hoops_HSSS,			_hoops_GRRCR ("yes"),							_hoops_RRRCR, 0, false},
	{_hoops_HSSS,			_hoops_GRRCR ("true"),							_hoops_RRRCR, 0, false},
	{_hoops_HSSS,			_hoops_GRRCR ("default"),						_hoops_RRRCR, 0, false},

	{_hoops_GRAAP,				_hoops_GRRCR ("painter"),						_hoops_RRRCR, 0, false},
	{_hoops_GRAAP,				_hoops_GRRCR ("painters"),						_hoops_RRRCR, 0, false},
	{_hoops_HSSS,			_hoops_GRRCR ("z-sort only"),					_hoops_RRRCR, 0, false},
	{_hoops_HSSS,			_hoops_GRRCR ("z sort only"),					_hoops_RRRCR, 0, false},
	{_hoops_PIII,			_hoops_GRRCR ("depth peeling"),					_hoops_RRRCR, 0, false},

	{_hoops_HSSS,			_hoops_GRRCR ("zso"),							_hoops_RRRCR, 0, false},
	{_hoops_HSSS,			_hoops_GRRCR ("zsort"),							_hoops_RRRCR, 0, false},
	{_hoops_HSSS,			_hoops_GRRCR ("zsort only"),					_hoops_RRRCR, 0, false},
	{_hoops_HSSS,			_hoops_GRRCR ("z-sort"),						_hoops_RRRCR, 0, false},
	{_hoops_HSSS,			_hoops_GRRCR ("z sort"),						_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_HHARS = {
	_hoops_GGAPR (_hoops_PHARS), _hoops_PHARS,
};

local const _hoops_IGRCR _hoops_IHARS[] = {
	{_hoops_SGAAP,		_hoops_GRRCR ("hardware z buffer"),				_hoops_RRRCR, 0, false},
	{_hoops_SGAAP,		_hoops_GRRCR ("hardware z-buffer"),				_hoops_RRRCR, 0, false},
	{_hoops_GRAAP,				_hoops_GRRCR ("painter"),						_hoops_RRRCR, 0, false},
	{_hoops_GRAAP,				_hoops_GRRCR ("painters"),						_hoops_RRRCR, 0, false},
	{_hoops_RRAAP,		_hoops_GRRCR ("software z buffer"),				_hoops_RRRCR, 0, false},
	{_hoops_RRAAP,		_hoops_GRRCR ("software z-buffer"),				_hoops_RRRCR, 0, false},
	{_hoops_HSSS,			_hoops_GRRCR ("z-sort only"),					_hoops_RRRCR, 0, false},
	{_hoops_HSSS,			_hoops_GRRCR ("z sort only"),					_hoops_RRRCR, 0, false},
	{_hoops_HSSS,			_hoops_GRRCR ("z-sort"),						_hoops_RRRCR, 0, false},
	{_hoops_HSSS,			_hoops_GRRCR ("z sort"),						_hoops_RRRCR, 0, false},
	{_hoops_HSSS,			_hoops_GRRCR ("zsort"),							_hoops_RRRCR, 0, false},
	{_hoops_GAI,				_hoops_GRRCR ("priority"),						_hoops_RRRCR, 0, false},

	{_hoops_HRAAP,			_hoops_GRRCR ("transparent"),					_hoops_GHAGA, 1, true,
																			&_hoops_HHARS},
	{_hoops_HRAAP,			_hoops_GRRCR ("transparency"),					_hoops_GHAGA, 1, true,
																			&_hoops_HHARS},
	{_hoops_PRAAP,			_hoops_GRRCR ("hidden-line"),					_hoops_RRRCR, 0, false},
	{_hoops_PRAAP,			_hoops_GRRCR ("hidden line"),					_hoops_RRRCR, 0, false},

	{_hoops_SICI,			_hoops_GRRCR ("fast hidden-line"),				_hoops_RRRCR, 0, false},
	{_hoops_SICI,			_hoops_GRRCR ("fast hidden line"),				_hoops_RRRCR, 0, false},

	/* _hoops_PHSSA */
	{_hoops_SGAAP,		_hoops_GRRCR ("hzb"),							_hoops_RRRCR, 0, false},
	{_hoops_RRAAP,		_hoops_GRRCR ("szb"),							_hoops_RRRCR, 0, false},
	{_hoops_HSSS,			_hoops_GRRCR ("zso"),							_hoops_RRRCR, 0, false},
	{_hoops_HRAAP,			_hoops_GRRCR ("trans"),							_hoops_GHAGA, 1, true,
																			&_hoops_HHARS},
	{_hoops_PRAAP,			_hoops_GRRCR ("hlr"),							_hoops_RRRCR, 0, false},
	{_hoops_SICI,			_hoops_GRRCR ("zhlr"),							_hoops_RRRCR, 0, false},
	{_hoops_SICI,			_hoops_GRRCR ("fast hlr"),						_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_CHARS = {
	_hoops_GGAPR (_hoops_IHARS),				_hoops_IHARS,
};


local const _hoops_IGRCR _hoops_SHARS[] = {
	{_hoops_AIII,			_hoops_GRRCR ("off"),					_hoops_RRRCR, 0, false},
	{_hoops_AIII,			_hoops_GRRCR ("no"),					_hoops_RRRCR, 0, false},
	{_hoops_AIII,			_hoops_GRRCR ("false"),					_hoops_RRRCR, 0, false},
	{_hoops_AIII,			_hoops_GRRCR ("none"),					_hoops_RRRCR, 0, false},

	{Transparency_STYLE_BLENDING,		_hoops_GRRCR ("blend"),					_hoops_RRRCR, 0, false},
	{Transparency_STYLE_BLENDING,		_hoops_GRRCR ("blended"),				_hoops_RRRCR, 0, false},
	{Transparency_STYLE_BLENDING,		_hoops_GRRCR ("blending"),				_hoops_RRRCR, 0, false},
	{Transparency_STYLE_BLENDING,		_hoops_GRRCR ("on"),					_hoops_RRRCR, 0, false},
	{Transparency_STYLE_BLENDING,		_hoops_GRRCR ("yes"),					_hoops_RRRCR, 0, false},
	{Transparency_STYLE_BLENDING,		_hoops_GRRCR ("true"),					_hoops_RRRCR, 0, false},
	{Transparency_STYLE_BLENDING,		_hoops_GRRCR ("default"),				_hoops_RRRCR, 0, false},

	{_hoops_GCPI,	_hoops_GRRCR ("screen door"),			_hoops_RRRCR, 0, false},
	{_hoops_GCPI,	_hoops_GRRCR ("screen-door"),			_hoops_RRRCR, 0, false},
	{_hoops_GCPI,	_hoops_GRRCR ("screendoor"),			_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_GIARS = {
	_hoops_GGAPR (_hoops_SHARS),		_hoops_SHARS,
};

local const _hoops_IGRCR _hoops_RIARS[] = {
	{0,					_hoops_GRRCR ("line"),					_hoops_APRCA, 1, true},
	{0,					_hoops_GRRCR ("lines"),					_hoops_APRCA, 1, true},
	{1,					_hoops_GRRCR ("edge"),					_hoops_APRCA, 1, true},
	{1,					_hoops_GRRCR ("edges"),					_hoops_APRCA, 1, true},
};
local const _hoops_HPAGA _hoops_AIARS = {
	_hoops_GGAPR (_hoops_RIARS),		_hoops_RIARS,
};


local const _hoops_IGRCR _hoops_PIARS[] = {
	{_hoops_IRAAP,				_hoops_GRRCR ("off"),					_hoops_RRRCR, 0, false},
	{_hoops_IRAAP,				_hoops_GRRCR ("no"),					_hoops_RRRCR, 0, false},
	{_hoops_IRAAP,				_hoops_GRRCR ("false"),					_hoops_RRRCR, 0, false},
	{_hoops_SRAAP,				_hoops_GRRCR ("on"),					_hoops_RRRCR, 0, false},
	{_hoops_SRAAP,				_hoops_GRRCR ("yes"),					_hoops_RRRCR, 0, false},
	{_hoops_SRAAP,				_hoops_GRRCR ("true"),					_hoops_RRRCR, 0, false},
	{_hoops_GPSP,			_hoops_GRRCR ("screen"),				_hoops_RRRCR, 0, true},
	{_hoops_GPSP,			_hoops_GRRCR ("full screen"),			_hoops_RRRCR, 0, true},
	{_hoops_CRAAP,			_hoops_GRRCR ("text"),					_hoops_RRRCR, 0, true},
	{_hoops_SHP,			_hoops_GRRCR ("line"),					_hoops_RRRCR, 0, true},
	{_hoops_SHP,			_hoops_GRRCR ("lines"),					_hoops_RRRCR, 0, true},
};
local const _hoops_HPAGA _hoops_HIARS = {
	_hoops_GGAPR (_hoops_PIARS),		_hoops_PIARS,
};


local const _hoops_IGRCR _hoops_IIARS[] = {
	{-1,						_hoops_GRRCR (""),								_hoops_RRRCR, 0, false},
	{-1,						_hoops_GRRCR ("pixels"),						_hoops_RRRCR, 0, false},
	{ 1,						_hoops_GRRCR ("%"),								_hoops_RRRCR, 0, false},
	{ 1,						_hoops_GRRCR ("percent"),						_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_CIARS = {
	_hoops_GGAPR (_hoops_IIARS),		_hoops_IIARS,
};

local const _hoops_IGRCR _hoops_SIARS[] = {
	{_hoops_HAAAP,		_hoops_GRRCR ("layers"),					_hoops_APRCA, 1, false},
	{_hoops_IAAAP,		_hoops_GRRCR ("minimum area"),				_hoops_CIGHA, 1, true,
																				&_hoops_CIARS},
	{_hoops_IAAAP,		_hoops_GRRCR ("min area"),					_hoops_CIGHA, 1, true,
																				&_hoops_CIARS},
};
local const _hoops_HPAGA _hoops_GCARS = {
	_hoops_GGAPR (_hoops_SIARS),			_hoops_SIARS,
};

#define _hoops_RCARS -1
#define _hoops_ACARS -2

local const _hoops_IGRCR _hoops_PCARS[] = {
	{_hoops_RCARS,				_hoops_GRRCR ("fast"),						_hoops_RRRCR, 0, false},
	{_hoops_ACARS,				_hoops_GRRCR ("nice"),						_hoops_RRRCR, 0, false},
	{_hoops_RCARS,				_hoops_GRRCR ("fastest"),					_hoops_RRRCR, 0, false},
	{_hoops_ACARS,				_hoops_GRRCR ("nicest"),					_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_HCARS = {
	_hoops_GGAPR (_hoops_PCARS),			_hoops_PCARS,
};


local const _hoops_IGRCR _hoops_SSHCA[] = {
	{_hoops_RAAAP,			_hoops_GRRCR ("style"),							_hoops_GHAGA, 1, true,
																			&_hoops_GIARS},

	{_hoops_AAAAP,				_hoops_GRRCR ("hidden surface removal algorithm"),_hoops_GHAGA, 1, true,
																			&_hoops_HHARS},
	{_hoops_AAAAP,				_hoops_GRRCR ("visible surface algorithm"),		_hoops_GHAGA, 1, true,
																			&_hoops_HHARS},
	{_hoops_AAAAP,				_hoops_GRRCR ("hsr algorithm"),					_hoops_GHAGA, 1, true,
																			&_hoops_HHARS},
	{_hoops_AAAAP,				_hoops_GRRCR ("hsra"),							_hoops_GHAGA, 1, true,
																			&_hoops_HHARS},

	{_hoops_PAAAP,			_hoops_GRRCR ("hardware acceleration"),			_hoops_RRRCR, 0, true},
	{_hoops_PAAAP,			_hoops_GRRCR ("hardware"),						_hoops_RRRCR, 0, true},

	{_hoops_CAAAP,	_hoops_GRRCR ("depth peeling options"),_hoops_GHAGA, -9, false,&_hoops_GCARS},

	{_hoops_SAAAP,		_hoops_GRRCR ("zsort options"),_hoops_GHAGA, 1, false,&_hoops_HCARS},
	{_hoops_SAAAP,		_hoops_GRRCR ("z-sort options"),_hoops_GHAGA, 1, false,&_hoops_HCARS},
	{_hoops_SAAAP,		_hoops_GRRCR ("z sort options"),_hoops_GHAGA, 1, false,&_hoops_HCARS},

	{_hoops_GPAAP,	_hoops_GRRCR ("depth writing"),					_hoops_RRRCR, 0, true },
};
local const _hoops_HPAGA _hoops_ICARS = {
	_hoops_GGAPR (_hoops_SSHCA),				_hoops_SSHCA,
};




local const _hoops_IGRCR _hoops_CCARS[] = {
	{_hoops_RHAAP,	_hoops_GRRCR ("match device"),					_hoops_RRRCR, 0, false},
	{_hoops_PHAAP,	_hoops_GRRCR ("full color"),					_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_SCARS = {
	_hoops_GGAPR (_hoops_CCARS),		_hoops_CCARS,
};


local const _hoops_IGRCR _hoops_GSARS[] = {
	{-1,						_hoops_GRRCR ("byte"),							_hoops_RRRCR, 0, false},
	{-1,						_hoops_GRRCR ("bytes"),							_hoops_RRRCR, 0, false},
	{ 1,						_hoops_GRRCR ("raster"),						_hoops_RRRCR, 0, false},
	{ 1,						_hoops_GRRCR ("rasters"),						_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_RSARS = {
	_hoops_GGAPR (_hoops_GSARS),		_hoops_GSARS,
};


local const _hoops_IGRCR _hoops_RGICA[] = {
	{_hoops_HPAAP,			_hoops_GRRCR ("size limit"),					_hoops_CIGHA, 1, true,
																			&_hoops_RSARS},
	{_hoops_IPAAP,			_hoops_GRRCR ("retention"),						_hoops_RRRCR,			 0, true},
	{_hoops_CPAAP,		_hoops_GRRCR ("color depth"),					_hoops_GHAGA,		 1, false,
																			&_hoops_SCARS},
};
local const _hoops_HPAGA _hoops_ASARS = {
	_hoops_GGAPR (_hoops_RGICA),			_hoops_RGICA,
};




local const _hoops_IGRCR _hoops_AHSIA[] = {
	{_hoops_SHGRP,	_hoops_GRRCR (""),				_hoops_RRRCR, 0, false},
	{GSU_ORU,			_hoops_GRRCR ("oru"),			_hoops_RRRCR, 0, false},
	{GSU_SRU,			_hoops_GRRCR ("sru"),			_hoops_RRRCR, 0, false},
	{GSU_WRU,			_hoops_GRRCR ("wru"),			_hoops_RRRCR, 0, false},
	{_hoops_SPSC,			_hoops_GRRCR ("wsu"),			_hoops_RRRCR, 0, false},
	{_hoops_SPSC,			_hoops_GRRCR ("world"),			_hoops_RRRCR, 0, false},
	{GSU_PIXELS,		_hoops_GRRCR ("pixels"),		_hoops_RRRCR, 0, false},
	{GSU_PIXELS,		_hoops_GRRCR ("pixel"),			_hoops_RRRCR, 0, false},
	{GSU_PIXELS,		_hoops_GRRCR ("pxl"),			_hoops_RRRCR, 0, false},
	{GSU_PIXELS,		_hoops_GRRCR ("px"),			_hoops_RRRCR, 0, false},
	{GSU_POINTS,		_hoops_GRRCR ("points"),		_hoops_RRRCR, 0, false},
	{GSU_POINTS,		_hoops_GRRCR ("point"),			_hoops_RRRCR, 0, false},
	{GSU_POINTS,		_hoops_GRRCR ("pts"),			_hoops_RRRCR, 0, false},
	{GSU_POINTS,		_hoops_GRRCR ("pt"),			_hoops_RRRCR, 0, false},

	/* _hoops_RGR _hoops_RARP _hoops_RGAR _hoops_IGI _hoops_CCA _hoops_GRH _hoops_GASR _hoops_GAR _hoops_IRS _hoops_GGAGA _hoops_IH _hoops_IPCGP _hoops_HHRP */
	{-1,				_hoops_GRRCR ("*"),				_hoops_RRRCR, 0, true},
};
local const _hoops_HPAGA _hoops_PHSIA = {
	_hoops_GGAPR (_hoops_AHSIA)-1,		_hoops_AHSIA,
};
local const _hoops_HPAGA _hoops_PSARS = {
	_hoops_GGAPR (_hoops_AHSIA),		_hoops_AHSIA,
};

local const _hoops_IGRCR _hoops_CGICA[] = {
	{_hoops_RCCI,			_hoops_GRRCR ("visibility"),				_hoops_RRRCR, 0, true},
	{_hoops_APCRP,			_hoops_GRRCR ("dim factor"),				_hoops_SPPCR, 1, false},
	{_hoops_RPCRP,				_hoops_GRRCR ("pattern"),					_hoops_ARSAP, 1, true},
	{_hoops_RPCRP,				_hoops_GRRCR ("line pattern"),				_hoops_ARSAP, 1, true},
	{_hoops_GHCRP,				_hoops_GRRCR ("weight"),					_hoops_CIGHA, 1, true,
																				&_hoops_PHSIA},
	{_hoops_SPCRP,					_hoops_GRRCR ("color"),						_hoops_ARSAP, 1, true},
	{_hoops_PPCRP,		_hoops_GRRCR ("face displacement"),			_hoops_SPPCR, 1, false},
	{_hoops_HPCRP,			_hoops_GRRCR ("render faces"),				_hoops_RRRCR, 0, true},
	{_hoops_IPCRP,			_hoops_GRRCR ("render text"),				_hoops_RRRCR, 0, true},
	{_hoops_CPCRP,	_hoops_GRRCR ("silhouette cleanup"),		_hoops_RRRCR, 0, true},
	{_hoops_RHCRP,			_hoops_GRRCR ("image outline"),				_hoops_RRRCR, 0, true},
	{_hoops_RHCRP,			_hoops_GRRCR ("image outlines"),			_hoops_RRRCR, 0, true},
	{_hoops_RHCRP,			_hoops_GRRCR ("image outlining"),			_hoops_RRRCR, 0, true},
	{_hoops_AHCRP,			_hoops_GRRCR ("rendered face sorting algorithm"),
																			_hoops_GHAGA, 1, false,
																				&_hoops_AHARS},
	{_hoops_AHCRP,			_hoops_GRRCR ("rfsa"),						_hoops_GHAGA, 1, false,
																				&_hoops_AHARS},
	{_hoops_PHCRP,	_hoops_GRRCR ("transparency cutoff"),		_hoops_SPPCR, 1, false},
};
local const _hoops_HPAGA _hoops_HSARS = {
	_hoops_GGAPR (_hoops_CGICA),				_hoops_CGICA,
};





local const _hoops_IGRCR _hoops_ISARS[] = {
	{T_FACES,				_hoops_GRRCR ("face"),				_hoops_RRRCR, 0, true},
	{T_FACES,				_hoops_GRRCR ("faces"),				_hoops_RRRCR, 0, true},

	{T_FACES,				_hoops_GRRCR ("on"),				_hoops_RRRCR, 0, false},
	{0,						_hoops_GRRCR ("off"),				_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_CSARS = {
	_hoops_GGAPR (_hoops_ISARS),		_hoops_ISARS,
};

local const _hoops_IGRCR _hoops_SSARS[] = {
	{-1,					_hoops_GRRCR ("scale"),				_hoops_SPPCR, 1, false},
	{-2,					_hoops_GRRCR ("translate"),			_hoops_SPPCR, 1, false},
};
local const _hoops_HPAGA _hoops_GGPRS = {
	_hoops_GGAPR (_hoops_SSARS),		_hoops_SSARS,
};

local const _hoops_IGRCR _hoops_RGPRS[] = {
	{_hoops_PCCRP,		_hoops_GRRCR ("none"),				_hoops_RRRCR, 0, false},
	{_hoops_PCCRP,		_hoops_GRRCR ("default"),			_hoops_RRRCR, 0, false},
	{_hoops_HCCRP,	_hoops_GRRCR ("normalized"),		_hoops_RRRCR, 0, false},
	{_hoops_ICCRP,	_hoops_GRRCR ("explicit"),			_hoops_GHAGA, -9, false,
															&_hoops_GGPRS},
};
local const _hoops_HPAGA _hoops_AGPRS = {
	_hoops_GGAPR (_hoops_RGPRS),		_hoops_RGPRS,
};

local const _hoops_IGRCR _hoops_PGPRS[] = {
	{_hoops_RICRP,				_hoops_GRRCR ("visibility"),				_hoops_GHAGA, -9, true,
																				&_hoops_CSARS},
	{_hoops_AICRP,				_hoops_GRRCR ("value adjustment"),			_hoops_GHAGA, -9, true,
																				&_hoops_AGPRS},
};
local const _hoops_HPAGA _hoops_HGPRS = {
	_hoops_GGAPR (_hoops_PGPRS),					_hoops_PGPRS,
};


local const _hoops_IGRCR _hoops_IGPRS[] = {
	{-1,					_hoops_GRRCR ("interval"),			_hoops_SPPCR, 1, false},
	{-2,					_hoops_GRRCR ("offset"),			_hoops_SPPCR, 1, false},
};
local const _hoops_HPAGA _hoops_CGPRS = {
	_hoops_GGAPR (_hoops_IGPRS),		_hoops_IGPRS,
};


local const _hoops_IGRCR _hoops_SGPRS[] = {
	{_hoops_SCCRP,				_hoops_GRRCR ("repeat"),					_hoops_GHAGA, -9, false,
																				&_hoops_CGPRS},
	{_hoops_SCCRP,				_hoops_GRRCR ("repeated"),					_hoops_GHAGA, -9, false,
																				&_hoops_CGPRS},
	{_hoops_SCCRP,				_hoops_GRRCR ("repeating"),					_hoops_GHAGA, -9, false,
																				&_hoops_CGPRS},
	{_hoops_GSCRP,					_hoops_GRRCR ("explicit"),					_hoops_SPPCR, -999, false},
	{-1,								_hoops_GRRCR ("default"),					_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_GRPRS = {
	_hoops_GGAPR (_hoops_SGPRS),			_hoops_SGPRS,
};

local const _hoops_IGRCR _hoops_RRPRS[] = {
	{_hoops_HICRP,				_hoops_GRRCR ("visibility"),				_hoops_RRRCR, 0, true},
	{_hoops_HICRP,				_hoops_GRRCR ("visible"),					_hoops_RRRCR, 0, true},

	{_hoops_IICRP,					_hoops_GRRCR ("position"),					_hoops_GHAGA, 1, false,
																				&_hoops_GRPRS},
	{_hoops_IICRP,					_hoops_GRRCR ("positions"),					_hoops_GHAGA, 1, false,
																				&_hoops_GRPRS},
	{_hoops_CICRP,						_hoops_GRRCR ("color"),						_hoops_ARSAP, -999, true},
	{_hoops_CICRP,						_hoops_GRRCR ("colors"),					_hoops_ARSAP, -999, true},
	{_hoops_SICRP,					_hoops_GRRCR ("pattern"),					_hoops_ARSAP, -999, true},
	{_hoops_SICRP,					_hoops_GRRCR ("patterns"),					_hoops_ARSAP, -999, true},
	{_hoops_GCCRP,					_hoops_GRRCR ("weight"),					_hoops_CIGHA, -999, true,
																				&_hoops_PSARS},
	{_hoops_GCCRP,					_hoops_GRRCR ("weights"),					_hoops_CIGHA, -999, true,
																				&_hoops_PSARS},
	{_hoops_RCCRP,					_hoops_GRRCR ("lighting"),					_hoops_RRRCR, 0, true},
};
local const _hoops_HPAGA _hoops_ARPRS = {
	_hoops_GGAPR (_hoops_RRPRS),					_hoops_RRPRS,
};



local const _hoops_IGRCR _hoops_PRPRS[] = {
	{_hoops_CIGRP,				_hoops_GRRCR ("grayscale"),					_hoops_RRRCR, 0, false},
	{_hoops_CIGRP,				_hoops_GRRCR ("greyscale"),					_hoops_RRRCR, 0, false},
	{_hoops_SIGRP,				_hoops_GRRCR ("modulate"),					_hoops_RRRCR, 0, false},
	{_hoops_SIGRP,				_hoops_GRRCR ("modulated"),					_hoops_RRRCR, 0, false},
	{_hoops_GCGRP,	_hoops_GRRCR ("modulate grayscale"),		_hoops_RRRCR, 0, false},
	{_hoops_GCGRP,	_hoops_GRRCR ("modulate greyscale"),		_hoops_RRRCR, 0, false},
	{_hoops_GCGRP,	_hoops_GRRCR ("modulated grayscale"),		_hoops_RRRCR, 0, false},
	{_hoops_GCGRP,	_hoops_GRRCR ("modulated greyscale"),		_hoops_RRRCR, 0, false},
	{_hoops_RCGRP,					_hoops_GRRCR ("tone"),						_hoops_RRRCR, 0, false},
	{_hoops_RCGRP,					_hoops_GRRCR ("toned"),						_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_HRPRS = {
	_hoops_GGAPR (_hoops_PRPRS),				_hoops_PRPRS,
};

local const _hoops_IGRCR _hoops_IRPRS[] = {
	{_hoops_CHRH,						_hoops_GRRCR ("on"),						_hoops_RRRCR, 0, false},
	{0,									_hoops_GRRCR ("off"),						_hoops_RRRCR, 0, false},

	{_hoops_AIGRP,						_hoops_GRRCR ("range"),						_hoops_SPPCR, 2, false},
	{_hoops_PIGRP,						_hoops_GRRCR ("color"),						_hoops_ARSAP, 1, false},

	{_hoops_HIGRP,						_hoops_GRRCR ("effect"),					_hoops_GHAGA, 1, false,
																				&_hoops_HRPRS},
};
local const _hoops_HPAGA _hoops_CRPRS = {
	_hoops_GGAPR (_hoops_IRPRS),					_hoops_IRPRS,
};





local const _hoops_IGRCR _hoops_GARRS[] = {
	{_hoops_CRSRP,			_hoops_GRRCR ("tpcm2"),							_hoops_RRRCR, 0, false},
	{_hoops_CRSRP,			_hoops_GRRCR ("triangles per square cm"),		_hoops_RRRCR, 0, false},
	{_hoops_CRSRP,			_hoops_GRRCR ("triangles per square centimeter"), _hoops_RRRCR, 0, false},
	{_hoops_SRSRP,		_hoops_GRRCR ("tppix2"),						_hoops_RRRCR, 0, false},
	{_hoops_SRSRP,		_hoops_GRRCR ("triangles per square pixel"),	_hoops_RRRCR, 0, false},
	{_hoops_RASRP,		_hoops_GRRCR ("% area"),						_hoops_RRRCR, 0, false},
	{_hoops_RASRP,		_hoops_GRRCR ("%"),								_hoops_RRRCR, 0, false},
	{_hoops_AASRP,			_hoops_GRRCR (""),								_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_SRPRS = {
	_hoops_GGAPR (_hoops_GARRS),
	_hoops_GARRS,
};


/* _hoops_CHII _hoops_HII _hoops_GAPRS._hoops_GSGGR (_hoops_RAPRS._hoops_GSGGR)
 * _hoops_CARA _hoops_CSCHR _hoops_PSPA, _hoops_PAR _hoops_IRGHA _hoops_CSCHR _hoops_PSPA */
local const _hoops_IGRCR _hoops_GAGHA[] = {
	{_hoops_HSCRP,		_hoops_GRRCR ("oru"),							_hoops_RRRCR, 0, false},
	{_hoops_HSCRP,		_hoops_GRRCR (""),								_hoops_RRRCR, 0, false},
	{_hoops_PSCRP,		_hoops_GRRCR ("%"),								_hoops_RRRCR, 0, false},
	{_hoops_PSCRP,		_hoops_GRRCR ("% fru"),							_hoops_RRRCR, 0, false},
	{_hoops_PSCRP,		_hoops_GRRCR ("% feature relative units"),		_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_AAPRS = {
	_hoops_GGAPR (_hoops_GAGHA),
	_hoops_GAGHA,
};

local const _hoops_IGRCR _hoops_AARRS[] = {
	{_hoops_ARSRP,	_hoops_GRRCR ("current"),						_hoops_RRRCR, 0, false},
	{_hoops_PRSRP,	_hoops_GRRCR ("explicit"),						_hoops_SPPCR, 6, false},
};
local const _hoops_HPAGA _hoops_PAPRS = {
	_hoops_GGAPR (_hoops_AARRS),
	_hoops_AARRS,
};

local const _hoops_IGRCR _hoops_HARRS[] = {
	{_hoops_CASRP,		_hoops_GRRCR ("diagonal ratio per triangle"),	_hoops_RRRCR, 0, false},
	{_hoops_SASRP,			_hoops_GRRCR ("diagonal ratio"),				_hoops_RRRCR, 0, false},
	{_hoops_GPSRP,				_hoops_GRRCR ("diagonal per triangle"),			_hoops_RRRCR, 0, false},
	{_hoops_RPSRP,					_hoops_GRRCR ("diagonal"),						_hoops_RRRCR, 0, false},
	{_hoops_APSRP,		_hoops_GRRCR ("volume ratio per triangle"),		_hoops_RRRCR, 0, false},
	{_hoops_PPSRP,			_hoops_GRRCR ("volume ratio"),					_hoops_RRRCR, 0, false},
	{_hoops_HPSRP,				_hoops_GRRCR ("volume per triangle"),			_hoops_RRRCR, 0, false},
	{_hoops_IPSRP,					_hoops_GRRCR ("volume"),						_hoops_RRRCR, 0, false},
	{_hoops_CPSRP,				_hoops_GRRCR ("triangle size"),					_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_HAPRS = {
	_hoops_GGAPR (_hoops_HARRS),
	_hoops_HARRS,
};

local const _hoops_IGRCR _hoops_CARRS[] = {
	{_hoops_SPSRP,					_hoops_GRRCR ("none"),						_hoops_RRRCR, 0, false},
	{_hoops_GHSRP,				_hoops_GRRCR ("bounding"),					_hoops_RRRCR, 0, false},
	{_hoops_RHSRP,				_hoops_GRRCR ("coarsest"),					_hoops_RRRCR, 0, false},
	{_hoops_AHSRP,		_hoops_GRRCR ("coarsest none"),				_hoops_RRRCR, 0, false},
	{_hoops_IHSRP,	_hoops_GRRCR ("coarsest bounding"),			_hoops_RRRCR, 0, false},
	{_hoops_CHSRP,		_hoops_GRRCR ("bounding none"),				_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_IAPRS = {
	_hoops_GGAPR (_hoops_CARRS),
	_hoops_CARRS,
};

local const _hoops_IGRCR _hoops_GPRRS[] = {
	{_hoops_SHSRP,				_hoops_GRRCR ("fast"),						_hoops_RRRCR, 0, false},
	{_hoops_GISRP,				_hoops_GRRCR ("nice"),						_hoops_RRRCR, 0, false},
	{_hoops_SHSRP,				_hoops_GRRCR ("fastest"),					_hoops_RRRCR, 0, false},
	{_hoops_GISRP,				_hoops_GRRCR ("nicest"),					_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_CAPRS = {
	_hoops_GGAPR (_hoops_GPRRS),
	_hoops_GPRRS,
};

local const _hoops_IGRCR _hoops_IRRRS[] = {
	{_hoops_CGSRP,					_hoops_GRRCR ("segment"),					_hoops_RRRCR, 0, false},
	{~_hoops_CGSRP,					_hoops_GRRCR ("geometry"),					_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_SAPRS = {
	_hoops_GGAPR (_hoops_IRRRS),
	_hoops_IRRRS,
};

local const _hoops_IGRCR _hoops_GRICA[] = {
	{_hoops_ISCRP,					_hoops_GRRCR ("ratio"),							_hoops_SPPCR, -_hoops_IGAIR, false},
	{_hoops_IASRP,				_hoops_GRRCR ("threshold"),						_hoops_CIGHA, -_hoops_IGAIR, false,
																			&_hoops_SRPRS},
	{_hoops_CSCRP,	_hoops_GRRCR ("min triangle count"),			_hoops_APRCA, 1, true},
	{_hoops_CSCRP,	_hoops_GRRCR ("mtc"),							_hoops_APRCA, 1, true},
	{_hoops_HASRP,					_hoops_GRRCR ("clamp"),							_hoops_APRCA, 1, true},
	{_hoops_SSCRP,			_hoops_GRRCR ("levels"),						_hoops_APRCA, 1, false},
	{_hoops_SSCRP,			_hoops_GRRCR ("num levels"),					_hoops_APRCA, 1, false},
	{_hoops_IGSRP,				_hoops_GRRCR ("algorithm"),						_hoops_GHAGA, 1, false,
																			&_hoops_CAPRS},
	{_hoops_ASCRP, _hoops_GRRCR ("conserve memory"),				_hoops_RRRCR, 0, true},
	{_hoops_SGSRP,		_hoops_GRRCR ("preprocess"),					_hoops_RRRCR, 0, true},
	{_hoops_GGSRP,			_hoops_GRRCR ("max degree"),					_hoops_APRCA, 1, true},
	{_hoops_CGSRP,			_hoops_GRRCR ("mode"),							_hoops_GHAGA, 1, false,
																			&_hoops_SAPRS},
	{_hoops_AGSRP,				_hoops_GRRCR ("tolerance"),						_hoops_CIGHA, 1,
																			false, &_hoops_AAPRS},
	{_hoops_RRSRP,				_hoops_GRRCR ("bounding"),						_hoops_GHAGA, 1, true,
																			&_hoops_PAPRS},
	{_hoops_GRSRP,	_hoops_GRRCR ("usefulness heuristic"),			_hoops_GHAGA, 1, true,
																			&_hoops_HAPRS},
	{_hoops_IRSRP,	_hoops_GRRCR ("calculation usefulness cutoff"),	_hoops_SPPCR, -_hoops_IGAIR, true},
	{_hoops_IRSRP,	_hoops_GRRCR ("calculation cutoff"),			_hoops_SPPCR, -_hoops_IGAIR, true},
	{_hoops_IRSRP,	_hoops_GRRCR ("cutoff"),						_hoops_SPPCR, -_hoops_IGAIR, true},
	{_hoops_PASRP,				_hoops_GRRCR ("fallback"),						_hoops_GHAGA, 1, true,
																			&_hoops_IAPRS},
	{_hoops_RGSRP,		_hoops_GRRCR ("collapse duplicate vertices"),	_hoops_RRRCR, 0, true},
};
local const _hoops_HPAGA _hoops_GPPRS = {
	_hoops_GGAPR (_hoops_GRICA),				_hoops_GRICA,
};




#define _hoops_RPPRS		1
#define _hoops_APPRS			2

local const _hoops_IGRCR _hoops_PPPRS[] = {
	{_hoops_RPPRS, _hoops_GRRCR ("hither"), _hoops_SPPCR, 1, false},
	{_hoops_APPRS,	 _hoops_GRRCR ("yon"),	  _hoops_SPPCR, 1, false},
};
local const _hoops_HPAGA _hoops_HPPRS = {
	_hoops_GGAPR (_hoops_PPPRS),				_hoops_PPPRS,
};


local const _hoops_IGRCR _hoops_IHAIR[] = {
	{_hoops_ICSRP,			_hoops_GRRCR ("color range"),		_hoops_SPPCR, -2, true},
	{_hoops_SCSRP,		_hoops_GRRCR ("diffuse weight"),	_hoops_SPPCR, 1, false},
	{_hoops_GSSRP,			_hoops_GRRCR ("color map segment"),	_hoops_PRRCR, 1, true},
	{_hoops_GSSRP,			_hoops_GRRCR ("colormap segment"),	_hoops_PRRCR, 1, true},
};
local const _hoops_HPAGA _hoops_IPPRS = {
	_hoops_GGAPR (_hoops_IHAIR), _hoops_IHAIR,
};


#define _hoops_CPPRS	(_hoops_HIRAP|_hoops_IIRAP)
local const _hoops_IGRCR _hoops_SPPRS [] = {
	{(Integer32)_hoops_CPPRS,				_hoops_GRRCR ("on"),			_hoops_RRRCR, 0, false},
	{(Integer32)_hoops_CPPRS,				_hoops_GRRCR ("yes"),			_hoops_RRRCR, 0, false},
	{(Integer32)_hoops_IHGPR,									_hoops_GRRCR ("off"),			_hoops_RRRCR, 0, false},
	{(Integer32)_hoops_IHGPR,									_hoops_GRRCR ("no"),			_hoops_RRRCR, 0, false},
	{(Integer32)_hoops_IHGPR,									_hoops_GRRCR ("none"),			_hoops_RRRCR, 0, false},
	{(Integer32)_hoops_IHGPR,									_hoops_GRRCR ("flat"),			_hoops_RRRCR, 0, false},
	{(Integer32)(_hoops_GCP|_hoops_SSA),		_hoops_GRRCR ("phong"),			_hoops_RRRCR, 0, false},
	{(Integer32)(_hoops_HIRAP|_hoops_IIRAP),	_hoops_GRRCR ("gouraud"),		_hoops_RRRCR, 0, false},
	{(Integer32)(_hoops_RCP|_hoops_GGP),		_hoops_GRRCR ("gooch"),			_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_GHPRS = {
	_hoops_GGAPR (_hoops_SPPRS),		_hoops_SPPRS,
};


local const _hoops_IGRCR _hoops_RHPRS[] = {
	{(Integer32)_hoops_CPPRS,				_hoops_GRRCR ("on"),			_hoops_RRRCR, 0, false},
	{(Integer32)_hoops_CPPRS,				_hoops_GRRCR ("yes"),			_hoops_RRRCR, 0, false},
	{(Integer32)_hoops_IHGPR,									_hoops_GRRCR ("off"),			_hoops_RRRCR, 0, false},
	{(Integer32)_hoops_IHGPR,									_hoops_GRRCR ("no"),			_hoops_RRRCR, 0, false},
	{(Integer32)_hoops_IHGPR,									_hoops_GRRCR ("none"),			_hoops_RRRCR, 0, false},
	{(Integer32)_hoops_IHGPR,									_hoops_GRRCR ("flat"),			_hoops_RRRCR, 0, false},
	{(Integer32)(_hoops_GCP|_hoops_SSA),		_hoops_GRRCR ("phong"),			_hoops_RRRCR, 0, false},
	{(Integer32)(_hoops_HIRAP|_hoops_IIRAP),	_hoops_GRRCR ("gouraud"),		_hoops_RRRCR, 0, false},
	{(Integer32)(_hoops_RCP|_hoops_GGP),		_hoops_GRRCR ("gooch"),			_hoops_RRRCR, 0, false},
	{(Integer32)(_hoops_HIRAP|_hoops_RCP|_hoops_GCP),	_hoops_GRRCR ("edges"),			_hoops_GHAGA, -1, true,
																							&_hoops_GHPRS},
	{(Integer32)(_hoops_IIRAP|_hoops_GGP|_hoops_SSA),	_hoops_GRRCR ("faces"),			_hoops_GHAGA, -1, true,
																							&_hoops_GHPRS},
};
local const _hoops_HPAGA _hoops_AHPRS = {
	_hoops_GGAPR (_hoops_RHPRS),			_hoops_RHPRS,
};


#define _hoops_PHPRS ~_hoops_HHGAP	/* _hoops_SAHR _hoops_HAGH _hoops_HII _hoops_RH _hoops_HIASR */

local const _hoops_IGRCR _hoops_HHPRS[] = {
	{_hoops_PHPRS,				_hoops_GRRCR ("view independent"),				_hoops_RRRCR,	0, true},
	{_hoops_HHGAP,				_hoops_GRRCR ("view dependent"),				_hoops_RRRCR,	0, true},
	{_hoops_CHGAP,						_hoops_GRRCR ("budget"),						_hoops_APRCA,		1, false},
	{_hoops_SHGAP,				_hoops_GRRCR ("continued budget"),				_hoops_APRCA,		1, true},
	{_hoops_GIGAP,					_hoops_GRRCR ("max deviation"),					_hoops_SPPCR,	1, true},
	{_hoops_RIGAP,						_hoops_GRRCR ("max angle"),						_hoops_SPPCR,	1, true},
	{_hoops_AIGAP,					_hoops_GRRCR ("max length"),					_hoops_SPPCR,	1, true},
	{_hoops_GIGAP,					_hoops_GRRCR ("maximum deviation"),				_hoops_SPPCR,	1, true},
	{_hoops_RIGAP,						_hoops_GRRCR ("maximum angle"),					_hoops_SPPCR,	1, true},
	{_hoops_AIGAP,					_hoops_GRRCR ("maximum length"),				_hoops_SPPCR,	1, true},
};
local const _hoops_HPAGA _hoops_IHPRS = {
	_hoops_GGAPR (_hoops_HHPRS),				_hoops_HHPRS,
};


/* _hoops_PA _hoops_RRAI _hoops_ARI _hoops_CGH _hoops_GACC _hoops_PHHR _hoops_CRGR _hoops_RH _hoops_CHPRS _hoops_GASR _hoops_IGI _hoops_HPP _hoops_SHPRS */
local const _hoops_IGRCR _hoops_GIPRS[] = {
	{_hoops_PIGAP,	_hoops_GRRCR ("trim curve deviation"),			_hoops_SPPCR,	1, false},
	{_hoops_PIGAP,	_hoops_GRRCR ("max trim curve deviation"),		_hoops_SPPCR,	1, false},
	{_hoops_PIGAP,	_hoops_GRRCR ("maximum trim curve deviation"),	_hoops_SPPCR,	1, false},
	{_hoops_IIGAP,			_hoops_GRRCR ("trim budget"),					_hoops_APRCA,		1, false},
	{_hoops_IIGAP,			_hoops_GRRCR ("trim curve budget"),				_hoops_APRCA,		1, false},
	{_hoops_CIGAP,			_hoops_GRRCR ("facet deviation"),				_hoops_SPPCR,	1, false},
	{_hoops_CIGAP,			_hoops_GRRCR ("max facet deviation"),			_hoops_SPPCR,	1, false},
	{_hoops_CIGAP,			_hoops_GRRCR ("maximum facet deviation"),		_hoops_SPPCR,	1, false},
	{_hoops_SIGAP,				_hoops_GRRCR ("facet angle"),					_hoops_SPPCR,	1, false},
	{_hoops_SIGAP,				_hoops_GRRCR ("max facet angle"),				_hoops_SPPCR,	1, false},
	{_hoops_SIGAP,				_hoops_GRRCR ("maximum facet angle"),			_hoops_SPPCR,	1, false},
	{_hoops_GCGAP,				_hoops_GRRCR ("facet width"),					_hoops_SPPCR,	1, false},
	{_hoops_GCGAP,				_hoops_GRRCR ("max facet width"),				_hoops_SPPCR,	1, false},
	{_hoops_GCGAP,				_hoops_GRRCR ("maximum facet width"),			_hoops_SPPCR,	1, false},
	{_hoops_GCGAP,				_hoops_GRRCR ("facet length"),					_hoops_SPPCR,	1, false},
	{_hoops_GCGAP,				_hoops_GRRCR ("max facet length"),				_hoops_SPPCR,	1, false},
	{_hoops_GCGAP,				_hoops_GRRCR ("maximum facet length"),			_hoops_SPPCR,	1, false},
	{_hoops_RCGAP,						_hoops_GRRCR ("budget"),						_hoops_APRCA,		1, false},
	{_hoops_RCGAP,						_hoops_GRRCR ("surface budget"),				_hoops_APRCA,		1, false},
};
local const _hoops_HPAGA _hoops_RIPRS = {
	_hoops_GGAPR (_hoops_GIPRS),			_hoops_GIPRS,
};


local const _hoops_IGRCR _hoops_AIPRS[] = {
	{_hoops_ACGAP,	_hoops_GRRCR ("cylinder"),	_hoops_APRCA, -8, false},
	{_hoops_PCGAP,	_hoops_GRRCR ("sphere"),	_hoops_APRCA, -8, false},
};
local const _hoops_HPAGA _hoops_PIPRS = {
	_hoops_GGAPR (_hoops_AIPRS),				_hoops_AIPRS,
};


local const _hoops_IGRCR _hoops_HIPRS[] = {
	{0,											_hoops_GRRCR ("off"),		_hoops_RRRCR, 0, false},
	{0,											_hoops_GRRCR ("no"),		_hoops_RRRCR, 0, false},
	{0,											_hoops_GRRCR ("false"),		_hoops_RRRCR, 0, false},
	{_hoops_PHGAP,		_hoops_GRRCR ("on"),		_hoops_RRRCR, 0, false},
	{_hoops_PHGAP,		_hoops_GRRCR ("yes"),		_hoops_RRRCR, 0, false},
	{_hoops_PHGAP,		_hoops_GRRCR ("true"),		_hoops_RRRCR, 0, false},
	{_hoops_RHGAP,	_hoops_GRRCR ("radii"),		_hoops_RRRCR, 0, true},
	{_hoops_AHGAP,	_hoops_GRRCR ("colors"),	_hoops_RRRCR, 0, true},
	{_hoops_RHGAP,	_hoops_GRRCR ("radius"),	_hoops_RRRCR, 0, true},
	{_hoops_AHGAP,	_hoops_GRRCR ("color"),		_hoops_RRRCR, 0, true},
};
local const _hoops_HPAGA _hoops_IIPRS = {
	_hoops_GGAPR (_hoops_HIPRS),		_hoops_HIPRS,
};


local const _hoops_IGRCR geometry_options[] = {
	{_hoops_GHGAP,				_hoops_GRRCR ("hard edge dihedral angle "),	_hoops_SPPCR, 1, false},
	{_hoops_GHGAP,				_hoops_GRRCR ("hard edge angle"),			_hoops_SPPCR, 1, false},
	{_hoops_GHGAP,				_hoops_GRRCR ("dihedral angle"),			_hoops_SPPCR, 1, false},
	{_hoops_GHGAP,				_hoops_GRRCR ("dihedral"),					_hoops_SPPCR, 1, false},
	{_hoops_PHGAP,	_hoops_GRRCR ("invert polycylinders"),		_hoops_GHAGA, -9, true,
																					&_hoops_IIPRS},
	{_hoops_PHGAP,	_hoops_GRRCR ("invert cylinders"),			_hoops_GHAGA, -9, true,
																					&_hoops_IIPRS},
	{_hoops_PHGAP,	_hoops_GRRCR ("reverse polycylinders"),		_hoops_GHAGA, -9, true,
																					&_hoops_IIPRS},
	{_hoops_PHGAP,	_hoops_GRRCR ("reverse cylinders"),			_hoops_GHAGA, -9, true,
																					&_hoops_IIPRS},
	{_hoops_PHGAP,	_hoops_GRRCR ("invert polycylinder"),		_hoops_GHAGA, -9, true,
																					&_hoops_IIPRS},
	{_hoops_PHGAP,	_hoops_GRRCR ("invert cylinder"),			_hoops_GHAGA, -9, true,
																					&_hoops_IIPRS},
	{_hoops_PHGAP,	_hoops_GRRCR ("reverse polycylinder"),		_hoops_GHAGA, -9, true,
																					&_hoops_IIPRS},
	{_hoops_PHGAP,	_hoops_GRRCR ("reverse cylinder"),			_hoops_GHAGA, -9, true,
																					&_hoops_IIPRS},
};
local const _hoops_HPAGA _hoops_CIPRS = {
	_hoops_GGAPR (geometry_options),					geometry_options,
};



local const _hoops_IGRCR _hoops_SIPRS[] = {
	{0,							_hoops_GRRCR (""),		_hoops_RRRCR, 0, false},
	{_hoops_ISSRP,	_hoops_GRRCR ("%"),		_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_GCPRS = {
	_hoops_GGAPR (_hoops_SIPRS),	_hoops_SIPRS,
};

local const _hoops_IGRCR _hoops_RCPRS[] = {
	{_hoops_AHIGA,			_hoops_GRRCR ("entity"),		_hoops_RRRCR, 0, false},
	{_hoops_AHIGA,			_hoops_GRRCR ("geometry"),		_hoops_RRRCR, 0, false},
	{_hoops_SSSRP,		_hoops_GRRCR ("segment"),		_hoops_RRRCR, 0, false},
	{_hoops_GGGAP,	_hoops_GRRCR ("segment tree"),	_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_ACPRS = {
	_hoops_GGAPR (_hoops_RCPRS),	_hoops_RCPRS,
};

local const _hoops_IGRCR _hoops_PCPRS[] = {
	{_hoops_AGGAP,_hoops_GRRCR ("on"),			_hoops_RRRCR, 0, false},
	{_hoops_AGGAP,_hoops_GRRCR ("yes"),			_hoops_RRRCR, 0, false},
	{_hoops_AGGAP,_hoops_GRRCR ("true"),			_hoops_RRRCR, 0, false},

	/* _hoops_SGH _hoops_HCPRS _hoops_GAR _hoops_SAHR _hoops_IRS _hoops_HSSPR _hoops_HAGH _hoops_PIRA _hoops_IS _hoops_RIP _hoops_PSAP */
	{_hoops_RGGAP,_hoops_GRRCR ("off"),			_hoops_RRRCR, 0, false},
	{_hoops_RGGAP,_hoops_GRRCR ("no"),			_hoops_RRRCR, 0, false},
	{_hoops_RGGAP,_hoops_GRRCR ("false"),		_hoops_RRRCR, 0, false},


	{_hoops_AGGAP,_hoops_GRRCR ("current"),		_hoops_RRRCR, 0, false},
	{_hoops_GAIGA,	_hoops_GRRCR ("first"),			_hoops_RRRCR, 0, false},
	{_hoops_AAIGA,	_hoops_GRRCR ("last"),			_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_ICPRS = {
	_hoops_GGAPR (_hoops_PCPRS),	_hoops_PCPRS,
};

local const _hoops_IGRCR _hoops_CCPRS[] = {
	{_hoops_RSSRP,		_hoops_GRRCR ("level"),				_hoops_GHAGA,		 1, false, &_hoops_ACPRS},
	{_hoops_HSSRP,	_hoops_GRRCR ("match color"),		_hoops_GHAGA,		-1, true,  &_hoops_ICPRS},
	{_hoops_HSSRP,	_hoops_GRRCR ("match colors"),		_hoops_GHAGA,		-1, true,  &_hoops_ICPRS},
	{_hoops_PSSRP,	_hoops_GRRCR ("tolerance"),			_hoops_CIGHA, 1, false, &_hoops_GCPRS},
};
local const _hoops_HPAGA _hoops_SCPRS = {
	_hoops_GGAPR (_hoops_CCPRS),				_hoops_CCPRS,
};


local const _hoops_IGRCR _hoops_GSPRS[] = {
	{0,							_hoops_GRRCR ("off"),			_hoops_RRRCR,	0, false},
	{0,							_hoops_GRRCR ("no"),			_hoops_RRRCR,	0, false},
	{0,							_hoops_GRRCR ("false"),			_hoops_RRRCR,	0, false},
	{0,							_hoops_GRRCR ("none"),			_hoops_RRRCR,	0, false},
	{_hoops_PGGAP,		_hoops_GRRCR ("on"),			_hoops_RRRCR,	0, false},
	{_hoops_PGGAP,		_hoops_GRRCR ("yes"),			_hoops_RRRCR,	0, false},
	{_hoops_PGGAP,		_hoops_GRRCR ("true"),			_hoops_RRRCR,	0, false},
	{-1,						_hoops_GRRCR ("auto"),			_hoops_RRRCR,	0, false},

	{_hoops_IGGAP,		_hoops_GRRCR ("plane"),			_hoops_SPPCR,	4, false},
	{_hoops_CGGAP,		_hoops_GRRCR ("light"),			_hoops_SPPCR,	3, false},

	{_hoops_SGGAP,		_hoops_GRRCR ("color"),			_hoops_PRRCR,	1, false},
	{_hoops_GRGAP,		_hoops_GRRCR ("opacity"),		_hoops_SPPCR,	1, false},
	{_hoops_GRGAP,		_hoops_GRRCR ("alpha"),			_hoops_SPPCR,	1, false},

	{_hoops_RRGAP,	_hoops_GRRCR ("resolution"),	_hoops_APRCA,		1, false},
	{_hoops_ARGAP,	_hoops_GRRCR ("blurring"),		_hoops_APRCA,		1, false},
	{_hoops_ARGAP,	_hoops_GRRCR ("blur"),			_hoops_APRCA,		1, false},
	{_hoops_ARGAP,	_hoops_GRRCR ("softness"),		_hoops_APRCA,		1, false},

	{_hoops_PRGAP,	_hoops_GRRCR ("ignore transparency"),	_hoops_RRRCR,	0, true},
	{_hoops_PRGAP,	_hoops_GRRCR ("ignore transparencies"),	_hoops_RRRCR,	0, true},
};
local const _hoops_HPAGA _hoops_RSPRS = {
	_hoops_GGAPR (_hoops_GSPRS),			_hoops_GSPRS,
};

#define _hoops_ASPRS ~_hoops_IAGAP

local const _hoops_IGRCR _hoops_PSPRS[] = {
	{0,							_hoops_GRRCR ("off"),			_hoops_RRRCR,	0, false},
	{0,							_hoops_GRRCR ("no"),			_hoops_RRRCR,	0, false},
	{0,							_hoops_GRRCR ("false"),			_hoops_RRRCR,	0, false},
	{0,							_hoops_GRRCR ("none"),			_hoops_RRRCR,	0, false},
	{_hoops_GAGAP,		_hoops_GRRCR ("on"),			_hoops_RRRCR,	0, false},
	{_hoops_GAGAP,		_hoops_GRRCR ("yes"),			_hoops_RRRCR,	0, false},
	{_hoops_GAGAP,		_hoops_GRRCR ("true"),			_hoops_RRRCR,	0, false},
	{_hoops_AAGAP,			_hoops_GRRCR ("jitter"),		_hoops_RRRCR,	0, true},
	{_hoops_AAGAP,			_hoops_GRRCR ("jittered"),		_hoops_RRRCR,	0, true},
	{-1,						_hoops_GRRCR ("auto"),			_hoops_RRRCR,	0, false},

	{_hoops_PAGAP,		_hoops_GRRCR ("resolution"),	_hoops_APRCA,		1, false},
	{_hoops_HAGAP,		_hoops_GRRCR ("samples"),		_hoops_APRCA,		1, false},
	{_hoops_ASPRS,	_hoops_GRRCR ("view independent"), _hoops_RRRCR,	0, true},
	{_hoops_IAGAP,		_hoops_GRRCR ("view dependent"), _hoops_RRRCR,	0, true},
};
local const _hoops_HPAGA _hoops_HSPRS = {
	_hoops_GGAPR (_hoops_PSPRS),			_hoops_PSPRS,
};




local const _hoops_IGRCR _hoops_ISPRS[] = {
	{_hoops_CAHGP,	_hoops_GRRCR("on"),				_hoops_RRRCR, 0, false},
	{0,							_hoops_GRRCR("off"),			_hoops_RRRCR, 0, false},

	{_hoops_CAHGP,	_hoops_GRRCR("everything"),		_hoops_RRRCR, 0, true},
	{_hoops_AAHGP,			_hoops_GRRCR("geometry"),		_hoops_RRRCR, 0, true},
	{0,							_hoops_GRRCR("nothing"),		_hoops_RRRCR, 0, false},

	{T_ANY_EDGE,		_hoops_GRRCR("edge"),					_hoops_RRRCR, 0, true},
	{T_FACES,			_hoops_GRRCR("face"),					_hoops_RRRCR, 0, true},
	{T_ANY_LIGHTS,		_hoops_GRRCR("light"),					_hoops_RRRCR, 0, true},
	{T_ANY_LIGHTS,		_hoops_GRRCR("lighting"),				_hoops_RRRCR, 0, true},
	{T_LINES,			_hoops_GRRCR("line"),					_hoops_RRRCR, 0, true},
	{T_LINES,			_hoops_GRRCR("polyline"),				_hoops_RRRCR, 0, true},
	{T_MARKERS,			_hoops_GRRCR("marker only"),			_hoops_RRRCR, 0, true},
	{T_VERTICES,		_hoops_GRRCR("vertex"),					_hoops_RRRCR, 0, true},
	{T_MARKERS|T_VERTICES,_hoops_GRRCR("marker"),				_hoops_RRRCR, 0, true},
	{T_IMAGES,			_hoops_GRRCR("image"),					_hoops_RRRCR, 0, true},
	{T_IMAGES,			_hoops_GRRCR("pixel array"),			_hoops_RRRCR, 0, true},
	{T_TEXT,			_hoops_GRRCR("text"),					_hoops_RRRCR, 0, true},
	{T_STRING_CURSORS,	_hoops_GRRCR("string cursor"),			_hoops_RRRCR, 0, true},
	{T_WINDOWS,			_hoops_GRRCR("window"),					_hoops_RRRCR, 0, true},
	{T_FACES|T_ANY_EDGE,_hoops_GRRCR("polygon"),				_hoops_RRRCR, 0, true},
	{T_CUTTING_PLANES,	_hoops_GRRCR("cutting plane"),			_hoops_RRRCR, 0, true},

	{T_ANY_EDGE,		_hoops_GRRCR("edges"),					_hoops_RRRCR, 0, true},
	{T_FACES,			_hoops_GRRCR("faces"),					_hoops_RRRCR, 0, true},
	{T_ANY_LIGHTS,		_hoops_GRRCR("lights"),					_hoops_RRRCR, 0, true},
	{T_LINES,			_hoops_GRRCR("lines"),					_hoops_RRRCR, 0, true},
	{T_LINES,			_hoops_GRRCR("polylines"),				_hoops_RRRCR, 0, true},
	{T_MARKERS,			_hoops_GRRCR("markers only"),			_hoops_RRRCR, 0, true},
	{T_VERTICES,		_hoops_GRRCR("vertices"),				_hoops_RRRCR, 0, true},
	{T_MARKERS|T_VERTICES,_hoops_GRRCR("markers"),				_hoops_RRRCR, 0, true},
	{T_IMAGES,			_hoops_GRRCR("images"),					_hoops_RRRCR, 0, true},
	{T_IMAGES,			_hoops_GRRCR("pixel arrays"),			_hoops_RRRCR, 0, true},
	{T_STRING_CURSORS,	_hoops_GRRCR("string cursors"),			_hoops_RRRCR, 0, true},
	{T_WINDOWS,			_hoops_GRRCR("windows"),				_hoops_RRRCR, 0, true},
	{T_FACES|T_ANY_EDGE,_hoops_GRRCR("polygons"),				_hoops_RRRCR, 0, true},
	{T_CUTTING_PLANES,	_hoops_GRRCR("cutting planes"),			_hoops_RRRCR, 0, true},

	{T_CUT_GEOMETRY,	_hoops_GRRCR ("cut geometry"),			_hoops_RRRCR, 0, true},

	{T_ANY_SHADOW,		_hoops_GRRCR ("shadow"),				_hoops_RRRCR, 0, true},
	{T_ANY_SHADOW,		_hoops_GRRCR ("shadows"),				_hoops_RRRCR, 0, true},
};
local const _hoops_HPAGA _hoops_CSPRS = {
	_hoops_GGAPR (_hoops_ISPRS),		_hoops_ISPRS,
};
// _hoops_PSHR (_hoops_IGI _hoops_IS _hoops_SHRGS _hoops_RCAR _hoops_HRP)
local const _hoops_HPAGA _hoops_SSPRS = {
	_hoops_GGAPR (_hoops_ISPRS),		_hoops_ISPRS,
};


local const _hoops_IGRCR _hoops_GGHRS[] = {
	{0,							_hoops_GRRCR ("off"),			_hoops_RRRCR,	0, false},
	{0,							_hoops_GRRCR ("no"),			_hoops_RRRCR,	0, false},
	{0,							_hoops_GRRCR ("false"),			_hoops_RRRCR,	0, false},
	{0,							_hoops_GRRCR ("none"),			_hoops_RRRCR,	0, false},
	{_hoops_CAGAP,	_hoops_GRRCR ("on"),			_hoops_RRRCR,	0, false},
	{_hoops_CAGAP,	_hoops_GRRCR ("yes"),			_hoops_RRRCR,	0, false},
	{_hoops_CAGAP,	_hoops_GRRCR ("true"),			_hoops_RRRCR,	0, false},

	{_hoops_GPGAP,	_hoops_GRRCR ("plane"),			_hoops_SPPCR,	4, false},

	{_hoops_RPGAP,	_hoops_GRRCR ("opacity"),		_hoops_SPPCR,	1, false},
	{_hoops_RPGAP,	_hoops_GRRCR ("alpha"),			_hoops_SPPCR,	1, false},

	{_hoops_APGAP,	_hoops_GRRCR ("fading"),		_hoops_RRRCR,	0, true},
	{_hoops_APGAP,	_hoops_GRRCR ("fade"),			_hoops_RRRCR,	0, true},
	{_hoops_PPGAP,	_hoops_GRRCR ("attenuation"), _hoops_GHAGA, 2, true,
															&_hoops_HPPRS},
	{_hoops_HPGAP,	_hoops_GRRCR ("blur"),		_hoops_APRCA,		1, true},
	{_hoops_HPGAP,	_hoops_GRRCR ("blurring"),	_hoops_APRCA,		1, true},

	{_hoops_IPGAP,	_hoops_GRRCR ("visibility"),	_hoops_GHAGA, -999, true,
																	&_hoops_SSPRS},
};
local const _hoops_HPAGA _hoops_RGHRS = {
	_hoops_GGAPR (_hoops_GGHRS),			_hoops_GGHRS,
};


local const _hoops_IGRCR _hoops_AGHRS[] = {
	{_hoops_AIAAP,			_hoops_GRRCR ("rotation"),				_hoops_RRRCR, 0, true},
	{_hoops_AIAAP,			_hoops_GRRCR ("rotate"),				_hoops_RRRCR, 0, true},
	{_hoops_RIAAP,				_hoops_GRRCR ("scale"),					_hoops_RRRCR, 0, true},
	{_hoops_RIAAP,				_hoops_GRRCR ("scaling"),				_hoops_RRRCR, 0, true},
	{_hoops_PIAAP,		_hoops_GRRCR ("translation"),			_hoops_RRRCR, 0, true},
	{_hoops_PIAAP,		_hoops_GRRCR ("translate"),				_hoops_RRRCR, 0, true},
	{_hoops_HIAAP,		_hoops_GRRCR ("perspective"),			_hoops_RRRCR, 0, true},
};
local const _hoops_HPAGA _hoops_PGHRS = {
	_hoops_GGAPR (_hoops_AGHRS),			_hoops_AGHRS,
};

local const _hoops_IGRCR _hoops_HGHRS[] = {
	{_hoops_CIAAP,			_hoops_GRRCR ("rotation"),				_hoops_RRRCR, 0, true},
	{_hoops_CIAAP,			_hoops_GRRCR ("rotate"),				_hoops_RRRCR, 0, true},
	{_hoops_IIAAP,				_hoops_GRRCR ("scale"),					_hoops_RRRCR, 0, true},
	{_hoops_IIAAP,				_hoops_GRRCR ("scaling"),				_hoops_RRRCR, 0, true},
	{_hoops_SIAAP,			_hoops_GRRCR ("translation"),			_hoops_RRRCR, 0, true},
	{_hoops_SIAAP,			_hoops_GRRCR ("translate"),				_hoops_RRRCR, 0, true},
};
local const _hoops_HPAGA _hoops_IGHRS = {
	_hoops_GGAPR (_hoops_HGHRS),			_hoops_HGHRS,
};

local const _hoops_IGRCR _hoops_CGHRS[] = {
	{_hoops_AIAAP,			_hoops_GRRCR ("camera"),				_hoops_RRRCR, 0, true},
	{_hoops_CIAAP,			_hoops_GRRCR ("model"),					_hoops_RRRCR, 0, true},
	{_hoops_CIAAP,			_hoops_GRRCR ("modelling"),				_hoops_RRRCR, 0, true},
	{_hoops_CIAAP,			_hoops_GRRCR ("modelling matrix"),		_hoops_RRRCR, 0, true},
};
local const _hoops_HPAGA _hoops_SGHRS = {
	_hoops_GGAPR (_hoops_CGHRS),		_hoops_CGHRS,
};

local const _hoops_IGRCR _hoops_GRHRS[] = {
	{_hoops_RIAAP,				_hoops_GRRCR ("camera"),				_hoops_RRRCR, 0, true},
	{_hoops_IIAAP,				_hoops_GRRCR ("model"),					_hoops_RRRCR, 0, true},
	{_hoops_IIAAP,				_hoops_GRRCR ("modelling"),				_hoops_RRRCR, 0, true},
	{_hoops_IIAAP,				_hoops_GRRCR ("modelling matrix"),		_hoops_RRRCR, 0, true},
};
local const _hoops_HPAGA _hoops_RRHRS = {
	_hoops_GGAPR (_hoops_GRHRS),			_hoops_GRHRS,
};

local const _hoops_IGRCR _hoops_ARHRS[] = {
	{_hoops_PIAAP,		_hoops_GRRCR ("camera"),				_hoops_RRRCR, 0, true},
	{_hoops_SIAAP,			_hoops_GRRCR ("model"),					_hoops_RRRCR, 0, true},
	{_hoops_SIAAP,			_hoops_GRRCR ("modelling"),				_hoops_RRRCR, 0, true},
	{_hoops_SIAAP,			_hoops_GRRCR ("modelling matrix"),		_hoops_RRRCR, 0, true},
};
local const _hoops_HPAGA _hoops_PRHRS = {
	_hoops_GGAPR (_hoops_ARHRS),		_hoops_ARHRS,
};

local const _hoops_IGRCR _hoops_HRHRS[] = {
	{_hoops_HIAAP,		_hoops_GRRCR ("camera"),				_hoops_RRRCR, 0, true},
};
local const _hoops_HPAGA _hoops_IRHRS = {
	_hoops_GGAPR (_hoops_HRHRS),		_hoops_HRHRS,
};

local const _hoops_IGRCR _hoops_CRHRS[] = {
	{_hoops_RCAAP,			_hoops_GRRCR ("camera"),					_hoops_GHAGA, -999, true,
																				&_hoops_PGHRS},
	{_hoops_ACAAP,				_hoops_GRRCR ("model"),						_hoops_GHAGA, -999, true,
																				&_hoops_IGHRS},
	{_hoops_ACAAP,				_hoops_GRRCR ("modelling"),					_hoops_GHAGA, -999, true,
																				&_hoops_IGHRS},
	{_hoops_ACAAP,				_hoops_GRRCR ("modelling matrix"),			_hoops_GHAGA, -999, true,
																				&_hoops_IGHRS},
	{_hoops_HCAAP,			_hoops_GRRCR ("rotation"),					_hoops_GHAGA, -999, true,
																				&_hoops_SGHRS},
	{_hoops_HCAAP,			_hoops_GRRCR ("rotate"),					_hoops_GHAGA, -999, true,
																				&_hoops_SGHRS},
	{_hoops_PCAAP,				_hoops_GRRCR ("scale"),						_hoops_GHAGA, -999, true,
																				&_hoops_RRHRS},
	{_hoops_PCAAP,				_hoops_GRRCR ("scaling"),					_hoops_GHAGA, -999, true,
																				&_hoops_RRHRS},
	{_hoops_ICAAP,		_hoops_GRRCR ("translation"),				_hoops_GHAGA, -999, true,
																				&_hoops_PRHRS},
	{_hoops_ICAAP,		_hoops_GRRCR ("translate"),					_hoops_GHAGA, -999, true,
																				&_hoops_PRHRS},
	{_hoops_CCAAP,		_hoops_GRRCR ("perspective"),				_hoops_GHAGA, -999, true,
																				&_hoops_IRHRS},
};
local const _hoops_HPAGA _hoops_SRHRS = {
	_hoops_GGAPR (_hoops_CRHRS),	_hoops_CRHRS,
};



local const _hoops_IGRCR _hoops_GAHRS[] = {
	/* _hoops_PPCAR _hoops_GGAR _hoops_AAP */
	{(Integer32)(_hoops_PIRAP),				_hoops_GRRCR ("on"),		_hoops_RRRCR, 0, false},
	{(Integer32)(_hoops_PIRAP),				_hoops_GRRCR ("yes"),		_hoops_RRRCR, 0, false},

	{(Integer32)_hoops_IHGPR,									_hoops_GRRCR ("off"),		_hoops_RRRCR, 0, false},
	{(Integer32)_hoops_IHGPR,									_hoops_GRRCR ("no"),		_hoops_RRRCR, 0, false},

	{(Integer32)(_hoops_AIRAP),				_hoops_GRRCR ("face"),		_hoops_RRRCR, 0, true},
	{(Integer32)(_hoops_AIRAP),				_hoops_GRRCR ("faces"),		_hoops_RRRCR, 0, true},

	{(Integer32)(_hoops_RIRAP),				_hoops_GRRCR ("edge"),		_hoops_RRRCR, 0, true},
	{(Integer32)(_hoops_RIRAP),				_hoops_GRRCR ("edges"),		_hoops_RRRCR, 0, true},

	{(Integer32)(_hoops_GIRAP),				_hoops_GRRCR ("marker"),	_hoops_RRRCR, 0, true},
	{(Integer32)(_hoops_GIRAP),				_hoops_GRRCR ("markers"),	_hoops_RRRCR, 0, true},

	/* _hoops_RAHRS _hoops_RGAR _hoops_IGI _hoops_IH _hoops_CIHA _hoops_GGAR _hoops_AHSGH _hoops_GASR */
	{(Integer32)_hoops_IHRAP,			_hoops_GRRCR ("isoline"),	_hoops_RRRCR, 0, true},
	{(Integer32)_hoops_IHRAP,			_hoops_GRRCR ("isolines"),	_hoops_RRRCR, 0, true},
};

/* _hoops_HH & _hoops_HAIR _hoops_GGAR _hoops_GA'_hoops_RA _hoops_ASSS _hoops_ACGC (_hoops_PAISP) */
local const _hoops_HPAGA _hoops_AAHRS = {
	_hoops_GGAPR (_hoops_GAHRS) - 2,		_hoops_GAHRS,
};

local const _hoops_HPAGA _hoops_PAHRS = {
	_hoops_GGAPR (_hoops_GAHRS) - 2,		_hoops_GAHRS,
};

local const _hoops_HPAGA _hoops_HAHRS = {
	_hoops_GGAPR (_hoops_GAHRS),			_hoops_GAHRS,
};



local const _hoops_IGRCR _hoops_IAHRS[] = {
	{M_DIFFUSE,				_hoops_GRRCR ("diffuse"),			_hoops_RRRCR, 0, true},
	{M_SPECULAR,			_hoops_GRRCR ("specular"),			_hoops_RRRCR, 0, true},
	{M_MIRROR,				_hoops_GRRCR ("mirror"),			_hoops_RRRCR, 0, true},
	{M_TRANSMISSION,		_hoops_GRRCR ("transmission"),		_hoops_RRRCR, 0, true},
	{M_EMISSION,			_hoops_GRRCR ("emission"),			_hoops_RRRCR, 0, true},
	{_hoops_RAGRA,				_hoops_GRRCR ("gloss"),				_hoops_RRRCR, 0, true},
	{_hoops_AAGRA,				_hoops_GRRCR ("index"),				_hoops_RRRCR, 0, true},
	{_hoops_SIARA,		_hoops_GRRCR ("bump"),				_hoops_RRRCR, 0, true},
	{_hoops_GCARA, _hoops_GRRCR ("environment"),		_hoops_RRRCR, 0, true},

	{~0,					_hoops_GRRCR ("on"),				_hoops_RRRCR, 0, false},
	{~0,					_hoops_GRRCR ("yes"),				_hoops_RRRCR, 0, false},
	{0,						_hoops_GRRCR ("off"),				_hoops_RRRCR, 0, false},
	{0,						_hoops_GRRCR ("no"),				_hoops_RRRCR, 0, false},
	{0,						_hoops_GRRCR ("nothing"),			_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_CAHRS = {
	_hoops_GGAPR (_hoops_IAHRS),	_hoops_IAHRS,
};

local const _hoops_IGRCR _hoops_SAHRS[] = {
	{Color_FRONT,			_hoops_GRRCR ("front"),				_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_BACK,			_hoops_GRRCR ("back"),				_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_FACE,			_hoops_GRRCR ("face"),				_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_EDGE,			_hoops_GRRCR ("edge"),				_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_POLYGON,			_hoops_GRRCR ("polygon"),			_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_LINE,			_hoops_GRRCR ("line"),				_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_LINE,			_hoops_GRRCR ("polyline"),			_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_VERTEX,			_hoops_GRRCR ("vertex"),			_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_MARKER,			_hoops_GRRCR ("marker only"),		_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_MARKER|Color_VERTEX,_hoops_GRRCR ("marker"),			_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_TEXT,			_hoops_GRRCR ("text"),				_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_CUT_FACE,		_hoops_GRRCR ("cut face"),			_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_CUT_EDGE,		_hoops_GRRCR ("cut edge"),			_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_CUT_GEOMETRY,	_hoops_GRRCR ("cut geometry"),		_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_WINDOW,			_hoops_GRRCR ("window"),			_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},

	{_hoops_SGARA,_hoops_GRRCR ("simple reflection"),_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},

	{_hoops_RRARA,	_hoops_GRRCR ("front contrast"),	_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{_hoops_GRARA,	_hoops_GRRCR ("back contrast"),		_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_FACE_CONTRAST,	_hoops_GRRCR ("face contrast"),		_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_FACE_CONTRAST,	_hoops_GRRCR ("polygon contrast"),	_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_EDGE_CONTRAST,	_hoops_GRRCR ("edge contrast"),		_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_LINE_CONTRAST,	_hoops_GRRCR ("line contrast"),		_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_VERTEX_CONTRAST, _hoops_GRRCR ("vertex contrast"),	_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_MARKER_CONTRAST, _hoops_GRRCR ("marker contrast"),	_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_TEXT_CONTRAST,	_hoops_GRRCR ("text contrast"),		_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_CUT_FACE,		_hoops_GRRCR ("cut face contrast"),	_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_CUT_EDGE,		_hoops_GRRCR ("cut edge contrast"),	_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_CUT_GEOMETRY,	_hoops_GRRCR ("cut geometry contrast"),	_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_WINDOW_CONTRAST, _hoops_GRRCR ("window contrast"),	_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},

	{_hoops_PRARA,		_hoops_GRRCR ("ambient up"),		_hoops_RRRCR, 0, true},
	{_hoops_HRARA,	_hoops_GRRCR ("ambient down"),		_hoops_RRRCR, 0, true},
	{_hoops_IRARA,		_hoops_GRRCR ("ambient"),			_hoops_RRRCR, 0, true},
	{Color_LIGHTING,		_hoops_GRRCR ("lighting"),			_hoops_RRRCR, 0, true},

	{Color_GEOMETRY,		_hoops_GRRCR ("geometry"),			_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_EVERYTHING,		_hoops_GRRCR ("everything"),		_hoops_GHAGA, -999, false,
															&_hoops_CAHRS},

	{Color_EVERYTHING,		_hoops_GRRCR ("on"),				_hoops_RRRCR, 0, false},
	{Color_EVERYTHING,		_hoops_GRRCR ("yes"),				_hoops_RRRCR, 0, false},
	{Color_NONE,			_hoops_GRRCR ("off"),				_hoops_RRRCR, 0, false},
	{Color_NONE,			_hoops_GRRCR ("no"),				_hoops_RRRCR, 0, false},
	{Color_NONE,			_hoops_GRRCR ("nothing"),			_hoops_RRRCR, 0, false},


	{Color_FRONT,			_hoops_GRRCR ("fronts"),			_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_BACK,			_hoops_GRRCR ("backs"),				_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_FACE,			_hoops_GRRCR ("faces"),				_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_EDGE,			_hoops_GRRCR ("edges"),				_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_POLYGON,			_hoops_GRRCR ("polygons"),			_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_LINE,			_hoops_GRRCR ("lines"),				_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_LINE,			_hoops_GRRCR ("polylines"),			_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_WINDOW,			_hoops_GRRCR ("windows"),			_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_VERTEX,			_hoops_GRRCR ("vertices"),			_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_MARKER,			_hoops_GRRCR ("markers only"),		_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_MARKER|Color_VERTEX,_hoops_GRRCR ("markers"),		_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_CUT_FACE,		_hoops_GRRCR ("cut faces"),			_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_CUT_EDGE,		_hoops_GRRCR ("cut edges"),			_hoops_GHAGA, -999, true,
															&_hoops_CAHRS},
	{Color_LIGHTING,		_hoops_GRRCR ("light"),				_hoops_RRRCR, 0, true},
	{Color_LIGHTING,		_hoops_GRRCR ("lights"),			_hoops_RRRCR, 0, true},
};
local const _hoops_HPAGA _hoops_GPHRS = {
	_hoops_GGAPR (_hoops_SAHRS),		_hoops_SAHRS,
};



local const _hoops_IGRCR _hoops_RPHRS[] = {
	{_hoops_GGCAA(HK_STYLE),				_hoops_GRRCR ("style"),					_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_RENDERING_OPTIONS),	_hoops_GRRCR ("rendering option"),		_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_SELECTABILITY),		_hoops_GRRCR ("selectability"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_VISIBILITY),			_hoops_GRRCR ("visibility"),			_hoops_GHAGA, -999, true,
																				&_hoops_CSPRS},
	{_hoops_GGCAA(HK_WINDOW_FRAME),		_hoops_GRRCR ("window frame"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_COLOR_MAP),			_hoops_GRRCR ("color map"),				_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_COLOR),				_hoops_GRRCR ("color"),					_hoops_GHAGA, -999, true,
																				&_hoops_GPHRS},
	{_hoops_GGCAA(HK_CAMERA),				_hoops_GRRCR ("camera"),				_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_CALLBACK),			_hoops_GRRCR ("callback"),				_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_CLIP_REGION),		_hoops_GRRCR ("clip region"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_DRIVER_OPTIONS),		_hoops_GRRCR ("driver option"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_EDGE_PATTERN),		_hoops_GRRCR ("edge pattern"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_EDGE_WEIGHT),		_hoops_GRRCR ("edge weight"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_FACE_PATTERN),		_hoops_GRRCR ("face pattern"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_HANDEDNESS),			_hoops_GRRCR ("handedness"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_HEURISTICS),			_hoops_GRRCR ("heuristics"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_LINE_PATTERN),		_hoops_GRRCR ("line pattern"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_LINE_WEIGHT),		_hoops_GRRCR ("line weight"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_MARKER_SIZE),		_hoops_GRRCR ("marker size"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_MARKER_SYMBOL),		_hoops_GRRCR ("marker symbol"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_MODELLING_MATRIX),	_hoops_GRRCR ("modelling matrix"),		_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_TEXT_ALIGNMENT),		_hoops_GRRCR ("text alignment"),		_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_TEXT_FONT),			_hoops_GRRCR ("text font"),				_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_TEXT_PATH),			_hoops_GRRCR ("text path"),				_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_TEXT_SPACING),		_hoops_GRRCR ("text spacing"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_USER_OPTIONS),		_hoops_GRRCR ("user option"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_USER_VALUE),			_hoops_GRRCR ("user value"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_WINDOW_PATTERN),		_hoops_GRRCR ("window pattern"),		_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_TEXTURE_MATRIX),		_hoops_GRRCR ("texture matrix"),		_hoops_RRRCR, 0, true},
#ifdef _hoops_APHRS
	{_hoops_GGCAA(HK_WINDOW),				_hoops_GRRCR ("window"),				_hoops_RRRCR, 0, true},
#endif

/* _hoops_PPHRS _hoops_RAACR */
	{_hoops_GGCAA(HK_STYLE),				_hoops_GRRCR ("styles"),				_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_RENDERING_OPTIONS),	_hoops_GRRCR ("rendering options"),		_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_SELECTABILITY),		_hoops_GRRCR ("selectabilities"),		_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_VISIBILITY),			_hoops_GRRCR ("visibilities"),			_hoops_GHAGA, -999, true,
																				&_hoops_CSPRS},
	{_hoops_GGCAA(HK_WINDOW_FRAME),		_hoops_GRRCR ("window frames"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_COLOR_MAP),			_hoops_GRRCR ("color maps"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_COLOR),				_hoops_GRRCR ("colors"),				_hoops_GHAGA, -999, true,
																				&_hoops_GPHRS},
	{_hoops_GGCAA(HK_CAMERA),				_hoops_GRRCR ("cameras"),				_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_CALLBACK),			_hoops_GRRCR ("callbacks"),				_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_CLIP_REGION),		_hoops_GRRCR ("clip regions"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_DRIVER_OPTIONS),		_hoops_GRRCR ("driver options"),		_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_EDGE_PATTERN),		_hoops_GRRCR ("edge patterns"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_EDGE_WEIGHT),		_hoops_GRRCR ("edge weights"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_FACE_PATTERN),		_hoops_GRRCR ("face patterns"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_HEURISTICS),			_hoops_GRRCR ("heuristics"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_LINE_PATTERN),		_hoops_GRRCR ("line patterns"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_LINE_WEIGHT),		_hoops_GRRCR ("line weights"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_MARKER_SIZE),		_hoops_GRRCR ("marker sizes"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_MARKER_SYMBOL),		_hoops_GRRCR ("marker symbols"),		_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_MODELLING_MATRIX),	_hoops_GRRCR ("modelling matrices"),	_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_TEXT_ALIGNMENT),		_hoops_GRRCR ("text alignments"),		_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_TEXT_FONT),			_hoops_GRRCR ("text fonts"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_TEXT_PATH),			_hoops_GRRCR ("text paths"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_TEXT_SPACING),		_hoops_GRRCR ("text spacings"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_USER_OPTIONS),		_hoops_GRRCR ("user options"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_USER_VALUE),			_hoops_GRRCR ("user values"),			_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_WINDOW_PATTERN),		_hoops_GRRCR ("window patterns"),		_hoops_RRRCR, 0, true},
	{_hoops_GGCAA(HK_TEXTURE_MATRIX),		_hoops_GRRCR ("texture matrices"),		_hoops_RRRCR, 0, true},
#ifdef _hoops_APHRS
	{_hoops_GGCAA(HK_WINDOW),				_hoops_GRRCR ("windows"),				_hoops_RRRCR, 0, true},
#endif

#define _hoops_HPHRS	 ~(_hoops_GGCAA(HK_WINDOW))

	{_hoops_HPHRS,			_hoops_GRRCR ("everything"),			_hoops_RRRCR, 0, true},
	{_hoops_HPHRS,			_hoops_GRRCR ("on"),					_hoops_RRRCR, 0, true},
	{_hoops_IHGPR,					_hoops_GRRCR ("off"),					_hoops_RRRCR, 0, true},
};
local const _hoops_HPAGA _hoops_IPHRS = {
	_hoops_GGAPR (_hoops_RPHRS),		_hoops_RPHRS,
};


local const _hoops_IGRCR _hoops_CPHRS[] = {
	{Quantization_THRESHOLD,	   _hoops_GRRCR ("threshold"),		 _hoops_RRRCR, 0, false},
	{Quantization_DITHER,		   _hoops_GRRCR ("dither"),			 _hoops_RRRCR, 0, false},
	{Quantization_DITHER,		   _hoops_GRRCR ("dithering"),		 _hoops_RRRCR, 0, false},
	{Quantization_DITHER,		   _hoops_GRRCR ("ordered dither"),	 _hoops_RRRCR, 0, false},
	{Quantization_ERROR_DIFFUSION, _hoops_GRRCR ("error diffusion"), _hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_SPHRS = {
	_hoops_GGAPR (_hoops_CPHRS),		_hoops_CPHRS,
};


local const _hoops_IGRCR _hoops_GHHRS[] = {
	{_hoops_ACRAP,				_hoops_GRRCR ("standard"), _hoops_RRRCR, 0, false},
#ifndef DISABLE_AIR_OPTIONS
	{_hoops_PCRAP,				_hoops_GRRCR ("radiosity"), _hoops_RRRCR, 0, false},
	{_hoops_HCRAP,				_hoops_GRRCR ("ray-trace"), _hoops_RRRCR, 0, false},
	{_hoops_HCRAP,				_hoops_GRRCR ("ray trace"), _hoops_RRRCR, 0, false},
#endif
	{_hoops_ICRAP,	_hoops_GRRCR ("software frame buffer"), _hoops_RRRCR, 0, false},
	{_hoops_ICRAP,	_hoops_GRRCR ("frame buffer"), _hoops_RRRCR, 0, false},
	{_hoops_ICRAP,	_hoops_GRRCR ("sfb"), _hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_RHHRS = {
	_hoops_GGAPR (_hoops_GHHRS),		_hoops_GHHRS,
};


local const _hoops_IGRCR _hoops_ASCGH[] = {
	{false,		_hoops_GRRCR (""),		_hoops_RRRCR, 0, false},
	{true,		_hoops_GRRCR ("%"),		_hoops_RRRCR, 0, false},
};

/* _hoops_GIGHR: _hoops_RGR _hoops_SPR _hoops_CGPR _hoops_RH "%" _hoops_HRGR _hoops_RGHP... */
local const _hoops_HPAGA _hoops_AHHRS = {
	_hoops_GGAPR (_hoops_ASCGH) - 1,	&_hoops_ASCGH[1],
};

/* ... _hoops_PPR _hoops_RGR _hoops_CGPR _hoops_SCH'_hoops_GRI _hoops_RIRCP */
local const _hoops_HPAGA _hoops_PSCGH = {
	_hoops_GGAPR (_hoops_ASCGH),		_hoops_ASCGH,
};




#ifndef DISABLE_AIR_OPTIONS

local const _hoops_IGRCR _hoops_PHHRS[] = {
	{_hoops_HSAAP,	_hoops_GRRCR ("convergence goal"),			_hoops_CIGHA, 1, false, &_hoops_AHHRS},
	{_hoops_GGPAP, _hoops_GRRCR ("internal subdivision"),		_hoops_CIGHA, -3, true, &_hoops_PSCGH},
	{_hoops_GGPAP, _hoops_GRRCR ("internal subdivisions"),	_hoops_CIGHA, -3, true, &_hoops_PSCGH},
	{_hoops_CSAAP,		_hoops_GRRCR ("interim display"),			_hoops_RRRCR, 0, true},
	{_hoops_CSAAP,		_hoops_GRRCR ("interim displays"),			_hoops_RRRCR, 0, true},
	{_hoops_SSAAP,		_hoops_GRRCR ("special events"),			_hoops_RRRCR, 0, true},
	{_hoops_CGPAP, _hoops_GRRCR ("interference detection"),	_hoops_RRRCR, 0, true},
	{_hoops_SGPAP,			_hoops_GRRCR ("autoscale"),					_hoops_RRRCR, 0, true},
	{_hoops_RGPAP,			_hoops_GRRCR ("accuracy"),					_hoops_APRCA, 1, false},
	{_hoops_HGPAP,			_hoops_GRRCR ("brightness"),				_hoops_SPPCR, 1, false},
	{_hoops_IGPAP,			_hoops_GRRCR ("contrast"),					_hoops_SPPCR, 1, false},
	{_hoops_AGPAP, _hoops_GRRCR ("boundary continuity"),		_hoops_RRRCR, 0, true},
	{_hoops_PGPAP, _hoops_GRRCR ("energy preservation"),		_hoops_RRRCR, 0, true},
};
local const _hoops_HPAGA _hoops_HHHRS = {
	_hoops_GGAPR (_hoops_PHHRS),		_hoops_PHHRS,
};


local const _hoops_IGRCR _hoops_IHHRS[] = {
	{_hoops_AAPAP,	_hoops_GRRCR ("sequential raster"),		_hoops_RRRCR, 0, false},
	{_hoops_AAPAP,	_hoops_GRRCR ("sequential rasters"),	_hoops_RRRCR, 0, false},
	{_hoops_AAPAP,	_hoops_GRRCR ("sequential"),			_hoops_RRRCR, 0, false},
	{_hoops_RAPAP,	_hoops_GRRCR ("interlaced raster"),		_hoops_RRRCR, 0, false},
	{_hoops_RAPAP,	_hoops_GRRCR ("interlaced rasters"),	_hoops_RRRCR, 0, false},
	{_hoops_RAPAP,	_hoops_GRRCR ("interlace raster"),		_hoops_RRRCR, 0, false},
	{_hoops_RAPAP,	_hoops_GRRCR ("interlace rasters"),		_hoops_RRRCR, 0, false},
	{_hoops_RAPAP,	_hoops_GRRCR ("interlaced"),			_hoops_RRRCR, 0, false},
	{_hoops_RAPAP,	_hoops_GRRCR ("interlace"),				_hoops_RRRCR, 0, false},
	{_hoops_CAPAP,			_hoops_GRRCR ("fill"),					_hoops_RRRCR, 0, false},
	{_hoops_CAPAP,			_hoops_GRRCR ("filled"),				_hoops_RRRCR, 0, false},

	/* _hoops_GRAA-_hoops_PPPPI _hoops_CHHRS */
	{_hoops_PAPAP,			_hoops_GRRCR ("grid"),					_hoops_RRRCR, 0, false},
	{_hoops_HAPAP,		_hoops_GRRCR ("recursive"),				_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_SHHRS = {
	_hoops_GGAPR (_hoops_IHHRS),	_hoops_IHHRS,
};


local const _hoops_IGRCR _hoops_GIHRS[] = {
	{_hoops_GAPAP, _hoops_GRRCR ("super-sample"),			_hoops_APRCA, 1, false},
	{_hoops_GAPAP, _hoops_GRRCR ("super-sampling"),		_hoops_APRCA, 1, false},
};
local const _hoops_HPAGA _hoops_RIHRS = {
	_hoops_GGAPR (_hoops_GIHRS), _hoops_GIHRS,
};


#if 0
local const _hoops_IGRCR _hoops_AIHRS[] = {
	{false,		_hoops_GRRCR (""),		_hoops_RRRCR, 0, false},
	{true,		_hoops_GRRCR ("step"),	_hoops_RRRCR, 0, false},
	{true,		_hoops_GRRCR ("steps"), _hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_PIHRS = {
	_hoops_GGAPR (_hoops_AIHRS),		_hoops_AIHRS,
};
#endif


local const _hoops_IGRCR _hoops_HIHRS[] = {
	{_hoops_GRPAP,	_hoops_GRRCR ("special events"),				_hoops_RRRCR, 0, true},
	{_hoops_ARPAP,_hoops_GRRCR ("scan-line method"),				_hoops_RRRCR, 0, true},
	{_hoops_HRPAP,	_hoops_GRRCR ("bounce limit"),					_hoops_APRCA, 1, true},
	{_hoops_IRPAP, _hoops_GRRCR ("required contribution"),	_hoops_CIGHA, 1, true, &_hoops_AHHRS},
	{_hoops_CRPAP,	_hoops_GRRCR ("display style"),					_hoops_GHAGA, -999, true, &_hoops_SHHRS},
	{_hoops_PRPAP,	_hoops_GRRCR ("anti-aliasing"),					_hoops_GHAGA, -999, true, &_hoops_RIHRS},
	{_hoops_PRPAP,	_hoops_GRRCR ("anti-alias"),					_hoops_GHAGA, -999, true, &_hoops_RIHRS},
	{_hoops_PRPAP,	_hoops_GRRCR ("antialiasing"),					_hoops_GHAGA, -999, true, &_hoops_RIHRS},
	{_hoops_PRPAP,	_hoops_GRRCR ("antialias"),						_hoops_GHAGA, -999, true, &_hoops_RIHRS},
	{_hoops_PRPAP,	_hoops_GRRCR ("anti aliasing"),					_hoops_GHAGA, -999, true, &_hoops_RIHRS},
	{_hoops_PRPAP,	_hoops_GRRCR ("anti alias"),					_hoops_GHAGA, -999, true, &_hoops_RIHRS},
	{_hoops_SRPAP,		_hoops_GRRCR ("blocking"),						_hoops_APRCA, 1, true},
	{_hoops_SRPAP,		_hoops_GRRCR ("blocking factor"),				_hoops_APRCA, 1, true},
};
local const _hoops_HPAGA _hoops_IIHRS = {
	_hoops_GGAPR (_hoops_HIHRS),		_hoops_HIHRS,
};

#endif

#define _hoops_CIHRS	Integer32

#define _hoops_SIHRS	(-1)
#define _hoops_GCHRS		(-2)

local const _hoops_IGRCR _hoops_RCHRS[] = {
	{(_hoops_CIHRS)_hoops_CIRAP,	_hoops_GRRCR ("lighting interpolation"),		_hoops_GHAGA, -999, true,
																						&_hoops_AHPRS},
	{(_hoops_CIHRS)_hoops_CIRAP,	_hoops_GRRCR ("lighting"),						_hoops_GHAGA, -999, true,
																						&_hoops_AHPRS},
	{(_hoops_CIHRS)_hoops_SHRAP,		_hoops_GRRCR ("texture interpolation"),			_hoops_GHAGA, -999, true,
																						&_hoops_AAHRS},
	{(_hoops_CIHRS)_hoops_AHRAP,		_hoops_GRRCR ("color interpolation"),			_hoops_GHAGA, -999, true,
																						&_hoops_PAHRS},
	{(_hoops_CIHRS)_hoops_HHRAP,	_hoops_GRRCR ("color index interpolation"),		_hoops_GHAGA, -999, true,
																						&_hoops_HAHRS},

	{_hoops_SRRAP,				_hoops_GRRCR ("hidden surface removal algorithm"),	_hoops_GHAGA, -999, false,
																						&_hoops_CHARS},
	{_hoops_SRRAP,				_hoops_GRRCR ("visible surface algorithm"),			_hoops_GHAGA, -999, false,
																						&_hoops_CHARS},
	{_hoops_SRRAP,				_hoops_GRRCR ("hsr algorithm"),						_hoops_GHAGA, -999, false,
																						&_hoops_CHARS},
	{_hoops_SRRAP,				_hoops_GRRCR ("hsra"),								_hoops_GHAGA, -999, false,
																						&_hoops_CHARS},

	{_hoops_GSIAA,				_hoops_GRRCR ("attribute lock"),				_hoops_GHAGA, -999, true,
																					&_hoops_IPHRS},
	{_hoops_GSIAA,				_hoops_GRRCR ("attribute locks"),				_hoops_GHAGA, -999, true,
																					&_hoops_IPHRS},

	{_hoops_RGRAP,					_hoops_GRRCR ("ignore subsegment lock"),		_hoops_GHAGA, -999, true,
																					&_hoops_IPHRS},
	{_hoops_RGRAP,					_hoops_GRRCR ("ignore subsegment locks"),		_hoops_GHAGA, -999, true,
																					&_hoops_IPHRS},

	{_hoops_PRRAP,						_hoops_GRRCR ("debug"),							_hoops_APRCA, 1, true},
	{_hoops_SIHRS,					_hoops_GRRCR ("clear debug"),					_hoops_APRCA, 1, false},
	{_hoops_GCHRS,					_hoops_GRRCR ("set debug"),						_hoops_APRCA, 1, false},

	{_hoops_CARAP,					_hoops_GRRCR ("technology"),					_hoops_GHAGA, -999, true,
																					&_hoops_RHHRS},

	{_hoops_PARAP,				_hoops_GRRCR ("quantization"),					_hoops_GHAGA, 1, false,
																					&_hoops_SPHRS},

	{_hoops_GGICA,				_hoops_GRRCR ("software frame buffer options"),	_hoops_GHAGA, -999, false,
																					&_hoops_ASARS},
	{_hoops_GGICA,				_hoops_GRRCR ("sfb options"),					_hoops_GHAGA, -999, false,
																					&_hoops_ASARS},
	{_hoops_GGICA,				_hoops_GRRCR ("sfbo"),							_hoops_GHAGA, -999, false,
																					&_hoops_ASARS},

	{_hoops_CRRAP,			_hoops_GRRCR ("face displacement"),				_hoops_APRCA, 1, true},
	{_hoops_IPRAP,			_hoops_GRRCR ("vertex displacement"),			_hoops_APRCA, 1, true},

	{_hoops_SARAP,		_hoops_GRRCR ("general displacement"),			_hoops_APRCA, 1, true},

	{_hoops_SPRAP,			_hoops_GRRCR ("scaled displacement"),			_hoops_RRRCR, 0, true},

	{_hoops_CRI,		_hoops_GRRCR ("frame buffer effects"),			_hoops_RRRCR, 0, true},

	{_hoops_GPRAP,			_hoops_GRRCR ("join cutoff angle"),				_hoops_AASAP, -9, true,
																					&_hoops_AIARS},

	{_hoops_HARAP,						_hoops_GRRCR ("stereo"),						_hoops_RRRCR, 0, true},
	{_hoops_IARAP,			_hoops_GRRCR ("stereo separation"),				_hoops_SPPCR, 1, true},
	{_hoops_RPRAP,				_hoops_GRRCR ("stereo distance"),				_hoops_SPPCR, 1, true},

	{_hoops_ISGAP,			_hoops_GRRCR ("anti-alias"),					_hoops_GHAGA, -999, true,
																					&_hoops_HIARS},
	{_hoops_ISGAP,			_hoops_GRRCR ("anti alias"),					_hoops_GHAGA, -999, true,
																					&_hoops_HIARS},
	{_hoops_ISGAP,			_hoops_GRRCR ("anti-aliasing"),					_hoops_GHAGA, -999, true,
																					&_hoops_HIARS},
	{_hoops_ISGAP,			_hoops_GRRCR ("anti aliasing"),					_hoops_GHAGA, -999, true,
																					&_hoops_HIARS},
	{_hoops_ISGAP,			_hoops_GRRCR ("antialias"),						_hoops_GHAGA, -999, true,
																					&_hoops_HIARS},
	{_hoops_ISGAP,			_hoops_GRRCR ("antialiasing"),					_hoops_GHAGA, -999, true,
																					&_hoops_HIARS},

	{Rendo_LOCAL_VIEWER,				_hoops_GRRCR ("local viewer"),					_hoops_RRRCR, 0, true},

	{_hoops_IGICA,			_hoops_GRRCR ("hidden line removal options"),	_hoops_GHAGA, -999, false,
																					&_hoops_HSARS},
	{_hoops_IGICA,			_hoops_GRRCR ("hlr options"),					_hoops_GHAGA, -999, false,
																					&_hoops_HSARS},
	{_hoops_IGICA,			_hoops_GRRCR ("hlro"),							_hoops_GHAGA, -999, false,
																					&_hoops_HSARS},

	{_hoops_AGRAP,				_hoops_GRRCR ("color index interpolation options"),
																				_hoops_GHAGA, -999, false,
																					&_hoops_HGPRS},
	{_hoops_AGRAP,				_hoops_GRRCR ("cii options"),					_hoops_GHAGA, -999, false,
																					&_hoops_HGPRS},
	{_hoops_AGRAP,				_hoops_GRRCR ("ciio"),							_hoops_GHAGA, -999, false,
																					&_hoops_HGPRS},
	{_hoops_AGRAP,				_hoops_GRRCR ("contour options"),				_hoops_GHAGA, -999, false,
																					&_hoops_HGPRS},

	{_hoops_PRICA,				_hoops_GRRCR ("isoline options"),				_hoops_GHAGA, -999, false,
																					&_hoops_ARPRS},

	{_hoops_HPH,		_hoops_GRRCR ("atmospheric attenuation"),		_hoops_GHAGA, 2, true,
																					&_hoops_HPPRS},
	{_hoops_HPH,		_hoops_GRRCR ("fog"),							_hoops_GHAGA, 2, true,
																					&_hoops_HPPRS},

	{_hoops_CSGGA,		_hoops_GRRCR ("perspective correction"),		_hoops_RRRCR, 0, true},

	{_hoops_IRICA,			_hoops_GRRCR ("nurbs curve"),					_hoops_GHAGA, -999, false,
																					&_hoops_IHPRS},
	{_hoops_IRICA,			_hoops_GRRCR ("general curve"),					_hoops_GHAGA, -999, false,
																					&_hoops_IHPRS},

	{_hoops_CRICA,		_hoops_GRRCR ("nurbs surface"),					_hoops_GHAGA, -999, false,
																					&_hoops_RIPRS},

	{_hoops_SRICA,		_hoops_GRRCR ("tessellation"),					_hoops_GHAGA, -999, false,
																					&_hoops_PIPRS},

	{_hoops_HRICA,			_hoops_GRRCR ("geometry options"),				_hoops_GHAGA, -999, false,
																					&_hoops_CIPRS},
	{_hoops_HRICA,			_hoops_GRRCR ("geometry"),						_hoops_GHAGA, -999, false,
																					&_hoops_CIPRS},

	{_hoops_ARICA,		_hoops_GRRCR ("cut geometry options"),			_hoops_GHAGA, -999, false,
																					&_hoops_SCPRS},
	{_hoops_ARICA,		_hoops_GRRCR ("cut geometry"),					_hoops_GHAGA, -999, false,
																					&_hoops_SCPRS},

	{_hoops_RRICA,		_hoops_GRRCR ("simple shadow"),					_hoops_GHAGA, -999, true,
																					&_hoops_RSPRS},
	{_hoops_CSGAP,			_hoops_GRRCR ("shadow map"),					_hoops_GHAGA, -999, true,
																					&_hoops_HSPRS},
	{_hoops_CSGAP,			_hoops_GRRCR ("shadow maps"),					_hoops_GHAGA, -999, true,
																					&_hoops_HSPRS},
	{_hoops_SSGAP,	_hoops_GRRCR ("simple reflection"),				_hoops_GHAGA, -999, true,
																					&_hoops_RGHRS},

	{_hoops_HRRAP,					_hoops_GRRCR ("depth range"),					_hoops_SPPCR, 2, false},
	{_hoops_APRAP,				_hoops_GRRCR ("screen range"),					_hoops_SPPCR, 4, false},
	{_hoops_PPRAP,			_hoops_GRRCR ("ambient up vector"),				_hoops_SPPCR, 3, true},
	{_hoops_PPRAP,			_hoops_GRRCR ("ambient vector"),				_hoops_SPPCR, 3, true},

	{_hoops_GARAP,					_hoops_GRRCR ("image scale"),					_hoops_SPPCR, -2, true},

	{_hoops_RARAP,					_hoops_GRRCR ("image tint"),					_hoops_PRRCR, 1, true},
	{_hoops_CPRAP,		_hoops_GRRCR ("diffuse texture tint"),			_hoops_PRRCR, 1, true},

	{_hoops_GGRAP,				_hoops_GRRCR ("gooch options"),					_hoops_GHAGA, -999, false,
																					&_hoops_IPPRS },
	{_hoops_CSHCA,		_hoops_GRRCR ("transparency options"),			_hoops_GHAGA, -999, false,
																					&_hoops_ICARS},
	{_hoops_CSHCA,		_hoops_GRRCR ("transparency"),					_hoops_GHAGA, -999, false,
																					&_hoops_ICARS},

	{_hoops_SGICA,					_hoops_GRRCR ("level of detail options"),		_hoops_GHAGA, -999, true,
																					&_hoops_GPPRS },
	{_hoops_SGICA,					_hoops_GRRCR ("lod options"),					_hoops_GHAGA, -999, true,
																					&_hoops_GPPRS },
	{_hoops_SGICA,					_hoops_GRRCR ("lodo"),							_hoops_GHAGA, -999, true,
																					&_hoops_GPPRS },
	{_hoops_GRRAP,							_hoops_GRRCR ("level of detail"),				_hoops_RRRCR, 0, true },
	{_hoops_GRRAP,							_hoops_GRRCR ("levels of detail"),				_hoops_RRRCR, 0, true },
	{_hoops_GRRAP,							_hoops_GRRCR ("lod"),							_hoops_RRRCR, 0, true },
	{_hoops_HPRAP,			_hoops_GRRCR ("vertex decimation"),				_hoops_SPPCR, 1, true },


	{_hoops_IRRAP,				_hoops_GRRCR ("display lists"),					_hoops_GHAGA, -1, true,
																					&_hoops_GHARS},
	{_hoops_IRRAP,				_hoops_GRRCR ("display list"),					_hoops_GHAGA, -1, true,
																					&_hoops_GHARS},
	{_hoops_IRRAP,				_hoops_GRRCR ("use display lists"),				_hoops_GHAGA, -1, true,
																					&_hoops_GHARS},
	{_hoops_IRRAP,				_hoops_GRRCR ("use display list"),				_hoops_GHAGA, -1, true,
																					&_hoops_GHARS},

	{_hoops_AARAP,		_hoops_GRRCR ("local cutting planes"),			_hoops_RRRCR, 0, true},
	{_hoops_AARAP,		_hoops_GRRCR ("local cutting plane"),			_hoops_RRRCR, 0, true},

	{_hoops_AGICA,				_hoops_GRRCR ("mask transform"),				_hoops_GHAGA, -999, true,
																					&_hoops_SRHRS},
	{_hoops_AGICA,				_hoops_GRRCR ("mask transforms"),				_hoops_GHAGA, -999, true,
																					&_hoops_SRHRS},

#ifndef DISABLE_AIR_OPTIONS
	{_hoops_HGRAP,			_hoops_GRRCR ("radiosity options"),				_hoops_GHAGA, -999, true,
																					&_hoops_HHHRS},
	{_hoops_IGRAP,			_hoops_GRRCR ("ray-trace options"),				_hoops_GHAGA, -999, true,
																					&_hoops_IIHRS},
	{_hoops_IGRAP,			_hoops_GRRCR ("ray trace options"),				_hoops_GHAGA, -999, true,
																					&_hoops_IIHRS},
#endif

	/* _hoops_PHSSA _hoops_RSARA _hoops_IH _hoops_SGCRP _hoops_SGH _hoops_RGAR */
	{(_hoops_CIHRS)_hoops_SHRAP,			_hoops_GRRCR ("texture int"),			_hoops_GHAGA, -999, true,
																					&_hoops_AAHRS},
	{(_hoops_CIHRS)_hoops_AHRAP,			_hoops_GRRCR ("color int"),				_hoops_GHAGA, -999, true,
																					&_hoops_PAHRS},
	{(_hoops_CIHRS)_hoops_HHRAP,		_hoops_GRRCR ("index int"),				_hoops_GHAGA, -999, true,
																					&_hoops_HAHRS},
	{_hoops_GSIAA,						_hoops_GRRCR ("atlock"),				_hoops_GHAGA, -999, true,
																					&_hoops_IPHRS},
	{_hoops_RGRAP,							_hoops_GRRCR ("ignore lock"),			_hoops_GHAGA, -999, true,
																					&_hoops_IPHRS},
	{_hoops_RGRAP,							_hoops_GRRCR ("ignore locks"),			_hoops_GHAGA, -999, true,
																					&_hoops_IPHRS},
	{_hoops_HAI,				_hoops_GRRCR ("force greyscale"),				_hoops_RRRCR, 0, true },
	{_hoops_HAI,				_hoops_GRRCR ("force grey scale"),				_hoops_RRRCR, 0, true },
	{_hoops_HAI,				_hoops_GRRCR ("force grayscale"),				_hoops_RRRCR, 0, true },
	{_hoops_HAI,				_hoops_GRRCR ("force gray scale"),				_hoops_RRRCR, 0, true },

	{_hoops_PGRAP,			_hoops_GRRCR ("diffuse color tint"),			_hoops_GHAGA, -999, true,
																					&_hoops_CRPRS},
};


// _hoops_CCAH _hoops_CPRC & _hoops_IPCGP _hoops_HRP _hoops_SIGR _hoops_IS _hoops_ACHRS _hoops_RH _hoops_RHGS "_hoops_HAIR _hoops_CIHA _hoops_GGAR=_hoops_ACGC" _hoops_RGSR
// _hoops_PRRAA _hoops_CIAAI _hoops_PPR _hoops_IPCGP _hoops_RCA _hoops_CHR _hoops_HAR _hoops_PASGH
#define _hoops_PCHRS				(_hoops_RICRP | _hoops_HICRP | \
											 _hoops_IICRP | _hoops_CICRP | _hoops_SICRP |  _hoops_GCCRP)
#define _hoops_HCHRS				(_hoops_RICRP | _hoops_HICRP)		// _hoops_RIR-_hoops_IPCGP _hoops_HRP "_hoops_PSAP"

#define _hoops_ICHRS		(T_FACES | T_EDGES)
#define _hoops_CCHRS	(T_EDGES)



local Attribute *_hoops_SCHRS (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH alter *			item,
	Attribute const *			_hoops_CPACR,
	Attribute alter *			_hoops_SPACR)
{
	_hoops_RHAIR const *	_hoops_GASGH = (_hoops_RHAIR const *)_hoops_CPACR;
	_hoops_RHAIR alter *	_hoops_RASGH = (_hoops_RHAIR alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (item);

	_hoops_RASGH->_hoops_RRHH = 0;

	if (_hoops_GASGH != null) {
		_hoops_GHGI				_hoops_GSHRS = 0;

		if (!BIT (_hoops_RASGH->_hoops_PSHCA, _hoops_PRRAP))
			_hoops_RASGH->_hoops_IRARR = _hoops_GASGH->_hoops_IRARR;

		if (!BIT (_hoops_RASGH->_hoops_PSHCA, _hoops_PARAP))
			_hoops_RASGH->_hoops_SIRAP = _hoops_GASGH->_hoops_SIRAP;

		if (!BIT (_hoops_RASGH->_hoops_PSHCA, _hoops_SRRAP))
			_hoops_RASGH->_hoops_SRI = _hoops_GASGH->_hoops_SRI;

		if (!BIT (_hoops_RASGH->_hoops_PSHCA, _hoops_CARAP))
			_hoops_RASGH->_hoops_RCRAP = _hoops_GASGH->_hoops_RCRAP;

		if (!BIT (_hoops_RASGH->_hoops_PSHCA, _hoops_CRRAP))
			_hoops_RASGH->_hoops_CHIH = _hoops_GASGH->_hoops_CHIH;

		if (!BIT (_hoops_RASGH->_hoops_PSHCA, _hoops_IPRAP))
			_hoops_RASGH->_hoops_IGAAP = _hoops_GASGH->_hoops_IGAAP;

		if (!BIT (_hoops_RASGH->_hoops_PSHCA, _hoops_SARAP))
			_hoops_RASGH->_hoops_SHIH = _hoops_GASGH->_hoops_SHIH;

		if (!BIT (_hoops_RASGH->_hoops_PSHCA, _hoops_GPRAP)) {
			_hoops_RASGH->_hoops_GSAAP = _hoops_GASGH->_hoops_GSAAP;
			_hoops_RASGH->_hoops_RSAAP = _hoops_GASGH->_hoops_RSAAP;
		}
		else {
			if (_hoops_RASGH->_hoops_GSAAP == -1)
				_hoops_RASGH->_hoops_GSAAP = _hoops_GASGH->_hoops_GSAAP;
			if (_hoops_RASGH->_hoops_RSAAP == -1)
				_hoops_RASGH->_hoops_RSAAP = _hoops_GASGH->_hoops_RSAAP;
		}


		if (_hoops_GASGH->_hoops_HHAIR != null) {
			if (!BIT (_hoops_RASGH->_hoops_PSHCA, _hoops_IARAP)) {
				if (_hoops_RASGH->_hoops_HHAIR == null)
					ZALLOC(_hoops_RASGH->_hoops_HHAIR, _hoops_RIAIR);
				_hoops_RASGH->_hoops_HHAIR->_hoops_ACSRP = _hoops_GASGH->_hoops_HHAIR->_hoops_ACSRP;
			}

			if (!BIT (_hoops_RASGH->_hoops_PSHCA, _hoops_RPRAP)) {
				if (_hoops_RASGH->_hoops_HHAIR == null)
					ZALLOC(_hoops_RASGH->_hoops_HHAIR, _hoops_RIAIR);
				_hoops_RASGH->_hoops_HHAIR->_hoops_PCSRP = _hoops_GASGH->_hoops_HHAIR->_hoops_PCSRP;
			}

			if (!BIT (_hoops_RASGH->_hoops_PSHCA, _hoops_HPH)) {
				if (BIT (_hoops_GASGH->_hoops_RRRAP, _hoops_HPH)) {
					if (_hoops_RASGH->_hoops_HHAIR == null)
						ZALLOC(_hoops_RASGH->_hoops_HHAIR, _hoops_RIAIR);
					_hoops_RASGH->_hoops_HHAIR->_hoops_CRIR.hither = _hoops_GASGH->_hoops_HHAIR->_hoops_CRIR.hither;
					_hoops_RASGH->_hoops_HHAIR->_hoops_CRIR.yon = _hoops_GASGH->_hoops_HHAIR->_hoops_CRIR.yon;
				}
			}

			if (BIT (_hoops_GASGH->_hoops_RRRAP, _hoops_PPRAP)) {
				if (!BIT (_hoops_RASGH->_hoops_RRRAP, _hoops_PPRAP)) {
					if (_hoops_RASGH->_hoops_HHAIR == null)
						ZALLOC(_hoops_RASGH->_hoops_HHAIR, _hoops_RIAIR);
					_hoops_RSAI (&_hoops_GASGH->_hoops_HHAIR->_hoops_HRGA, Vector, &_hoops_RASGH->_hoops_HHAIR->_hoops_HRGA);
				}
			}
		}

		if (BIT (_hoops_GASGH->_hoops_RRRAP, _hoops_HRRAP)) {
			if (!BIT (_hoops_RASGH->_hoops_RRRAP, _hoops_HRRAP)) {
				_hoops_RASGH->_hoops_HHAAP[0] = _hoops_GASGH->_hoops_HHAAP[0];
				_hoops_RASGH->_hoops_HHAAP[1] = _hoops_GASGH->_hoops_HHAAP[1];
			}
		}
		if (BIT (_hoops_GASGH->_hoops_RRRAP, _hoops_APRAP)) {
			if (!BIT (_hoops_RASGH->_hoops_RRRAP, _hoops_APRAP))
				_hoops_RASGH->_hoops_HCIH = _hoops_GASGH->_hoops_HCIH;
		}
		if (BIT (_hoops_GASGH->_hoops_RRRAP, _hoops_HPRAP)) {
			if (!BIT (_hoops_RASGH->_hoops_RRRAP, _hoops_HPRAP)) {
				_hoops_RASGH->_hoops_CSRS = _hoops_GASGH->_hoops_CSRS;
			}
		}
		if (BIT (_hoops_GASGH->_hoops_RRRAP, _hoops_GARAP)) {
			if (!BIT (_hoops_RASGH->_hoops_RRRAP, _hoops_GARAP)) {
				_hoops_RASGH->_hoops_IHAAP[0] = _hoops_GASGH->_hoops_IHAAP[0];
				_hoops_RASGH->_hoops_IHAAP[1] = _hoops_GASGH->_hoops_IHAAP[1];
			}
		}
		if (BIT (_hoops_GASGH->_hoops_RRRAP, _hoops_RARAP)) {
			if (!BIT (_hoops_RASGH->_hoops_RRRAP, _hoops_RARAP))
				_hoops_RASGH->_hoops_CHAAP = _hoops_GASGH->_hoops_CHAAP;
		}
		if (BIT (_hoops_GASGH->_hoops_RRRAP, _hoops_CPRAP)) {
			if (!BIT (_hoops_RASGH->_hoops_RRRAP, _hoops_CPRAP))
				_hoops_RASGH->_hoops_HRA = _hoops_GASGH->_hoops_HRA;
		}

		if (!BIT (_hoops_RASGH->_hoops_PSHCA, _hoops_IRRAP))
			_hoops_RASGH->_hoops_PSAAP = _hoops_GASGH->_hoops_PSAAP;


		if (BIT (_hoops_GASGH->_hoops_RSIAA, _hoops_IGICA)) {
			if (_hoops_RASGH->_hoops_AIAIR == null)
				ZALLOC(_hoops_RASGH->_hoops_AIAIR, _hoops_HIAIR);

			if (!BIT (_hoops_RASGH->_hoops_AIAIR->mask, _hoops_RPCRP)) {
				HI_Copy_Name(&_hoops_GASGH->_hoops_AIAIR->_hoops_PIAIR, &_hoops_RASGH->_hoops_AIAIR->_hoops_PIAIR);
				_hoops_RASGH->_hoops_AIAIR->_hoops_HHCRP = _hoops_GASGH->_hoops_AIAIR->_hoops_HHCRP;
			}

			if (!BIT (_hoops_RASGH->_hoops_AIAIR->mask, _hoops_GHCRP))
				_hoops_RASGH->_hoops_AIAIR->weight = _hoops_GASGH->_hoops_AIAIR->weight;

			if (!BIT (_hoops_RASGH->_hoops_AIAIR->mask, _hoops_SPCRP)) {
				_hoops_RASGH->_hoops_AIAIR->color.red = _hoops_GASGH->_hoops_AIAIR->color.red;
				_hoops_RASGH->_hoops_AIAIR->color.green = _hoops_GASGH->_hoops_AIAIR->color.green;
				_hoops_RASGH->_hoops_AIAIR->color.blue = _hoops_GASGH->_hoops_AIAIR->color.blue;
			}

			if (!BIT (_hoops_RASGH->_hoops_AIAIR->mask, _hoops_APCRP))
				_hoops_RASGH->_hoops_AIAIR->_hoops_IHCRP = _hoops_GASGH->_hoops_AIAIR->_hoops_IHCRP;

			if (!BIT (_hoops_RASGH->_hoops_AIAIR->mask, _hoops_PPCRP))
				_hoops_RASGH->_hoops_AIAIR->_hoops_CHIH = _hoops_GASGH->_hoops_AIAIR->_hoops_CHIH;

			if (!BIT (_hoops_RASGH->_hoops_AIAIR->mask, _hoops_PHCRP))
				_hoops_RASGH->_hoops_AIAIR->_hoops_CHCRP = _hoops_GASGH->_hoops_AIAIR->_hoops_CHCRP;

			if (!BIT (_hoops_RASGH->_hoops_AIAIR->mask, _hoops_AHCRP))
				_hoops_RASGH->_hoops_AIAIR->_hoops_SRI = _hoops_GASGH->_hoops_AIAIR->_hoops_SRI;

			_hoops_RASGH->_hoops_AIAIR->value |= _hoops_GASGH->_hoops_AIAIR->value & _hoops_GASGH->_hoops_AIAIR->mask & ~_hoops_RASGH->_hoops_AIAIR->mask;
			_hoops_RASGH->_hoops_AIAIR->mask |= _hoops_GASGH->_hoops_AIAIR->mask;
		}


		if (_hoops_RASGH->_hoops_IIAIR == null &&
			BIT (_hoops_RASGH->_hoops_ISHCA, _hoops_IHRAP) &&
			!BIT (_hoops_RASGH->_hoops_GHRAP, _hoops_IHRAP) &&
			_hoops_GASGH->_hoops_IIAIR != null &&
			_hoops_GASGH->_hoops_IIAIR->mask == _hoops_PCHRS &&
			_hoops_GASGH->_hoops_IIAIR->value == _hoops_HCHRS &&
			_hoops_GASGH->_hoops_IIAIR->_hoops_RGP.mask == _hoops_ICHRS &&
			_hoops_GASGH->_hoops_IIAIR->_hoops_RGP.value == _hoops_CCHRS) {
			// _hoops_HS _hoops_RH _hoops_HRP _hoops_PIS _hoops_PCCP _hoops_RHGS "_hoops_HAIR _hoops_CIHA _hoops_GGAR=_hoops_ACGC" _hoops_PPR _hoops_IRS _hoops_CCAH _hoops_RGSR
			// _hoops_SGS'_hoops_GRI _hoops_RGSR _hoops_SCH _hoops_PSAP, _hoops_HIS _hoops_SR _hoops_PAH _hoops_SAHR _hoops_SSPC _hoops_RH _hoops_RHGS _hoops_RGSR
			_hoops_GSHRS = _hoops_AGRAP | _hoops_PRICA;
		}
		else {
			if (BIT (_hoops_GASGH->_hoops_RSIAA, _hoops_AGRAP)) {
				if (_hoops_RASGH->_hoops_IIAIR == null)
					ZALLOC(_hoops_RASGH->_hoops_IIAIR, _hoops_ICAIR);

				if (!BIT (_hoops_RASGH->_hoops_IIAIR->mask, _hoops_RICRP)) {
					_hoops_RASGH->_hoops_IIAIR->_hoops_RGP.value |= _hoops_GASGH->_hoops_IIAIR->_hoops_RGP.value &
																  _hoops_GASGH->_hoops_IIAIR->_hoops_RGP.mask &
																  ~_hoops_RASGH->_hoops_IIAIR->_hoops_RGP.mask;
					_hoops_RASGH->_hoops_IIAIR->_hoops_RGP.mask |= _hoops_GASGH->_hoops_IIAIR->_hoops_RGP.mask;
				}
				if (!BIT (_hoops_RASGH->_hoops_IIAIR->mask, _hoops_AICRP)) {
					_hoops_RASGH->_hoops_IIAIR->_hoops_CCCRP = _hoops_GASGH->_hoops_IIAIR->_hoops_CCCRP;
					_hoops_RASGH->_hoops_IIAIR->scale = _hoops_GASGH->_hoops_IIAIR->scale;
					_hoops_RASGH->_hoops_IIAIR->translate = _hoops_GASGH->_hoops_IIAIR->translate;
				}

				_hoops_RASGH->_hoops_IIAIR->value |= _hoops_GASGH->_hoops_IIAIR->value & _hoops_PICRP &
												   _hoops_GASGH->_hoops_IIAIR->mask &
												   ~_hoops_RASGH->_hoops_IIAIR->mask;
				_hoops_RASGH->_hoops_IIAIR->mask |= _hoops_GASGH->_hoops_IIAIR->mask & _hoops_PICRP;
			}
			if (BIT (_hoops_GASGH->_hoops_RSIAA, _hoops_PRICA)) {
				if (_hoops_RASGH->_hoops_IIAIR == null)
					ZALLOC(_hoops_RASGH->_hoops_IIAIR, _hoops_ICAIR);

				if (!BIT (_hoops_RASGH->_hoops_IIAIR->mask, _hoops_HICRP)) {
					_hoops_RASGH->_hoops_IIAIR->_hoops_RGP.value |= _hoops_GASGH->_hoops_IIAIR->_hoops_RGP.value &
																  _hoops_GASGH->_hoops_IIAIR->_hoops_RGP.mask &
																  ~_hoops_RASGH->_hoops_IIAIR->_hoops_RGP.mask;
					_hoops_RASGH->_hoops_IIAIR->_hoops_RGP.mask |= _hoops_GASGH->_hoops_IIAIR->_hoops_RGP.mask;
				}
				if (!BIT (_hoops_RASGH->_hoops_IIAIR->mask, _hoops_IICRP)) {
					_hoops_RASGH->_hoops_IIAIR->_hoops_RSCRP = _hoops_GASGH->_hoops_IIAIR->_hoops_RSCRP;
					if ((_hoops_RASGH->_hoops_IIAIR->_hoops_CIAIR = _hoops_GASGH->_hoops_IIAIR->_hoops_CIAIR) != 0) {
						_hoops_APRGA (_hoops_GASGH->_hoops_IIAIR->_hoops_SIAIR,
									 _hoops_RASGH->_hoops_IIAIR->_hoops_CIAIR, float,
									 _hoops_RASGH->_hoops_IIAIR->_hoops_SIAIR);
					}
				}

				if (!BIT (_hoops_RASGH->_hoops_IIAIR->mask, _hoops_CICRP)) {
					if ((_hoops_RASGH->_hoops_IIAIR->_hoops_GCAIR = _hoops_GASGH->_hoops_IIAIR->_hoops_GCAIR) != 0) {
						_hoops_APRGA (_hoops_GASGH->_hoops_IIAIR->colors,
									 _hoops_RASGH->_hoops_IIAIR->_hoops_GCAIR, RGB,
									 _hoops_RASGH->_hoops_IIAIR->colors);
					}
				}

				if (!BIT (_hoops_RASGH->_hoops_IIAIR->mask, _hoops_SICRP)) {
					if ((_hoops_RASGH->_hoops_IIAIR->_hoops_RCAIR = _hoops_GASGH->_hoops_IIAIR->_hoops_RCAIR) != 0) {
						ALLOC_ARRAY (_hoops_RASGH->_hoops_IIAIR->_hoops_ACAIR,
									 _hoops_RASGH->_hoops_IIAIR->_hoops_RCAIR, _hoops_HCRPR);

						for (int i=0; i<_hoops_RASGH->_hoops_IIAIR->_hoops_RCAIR; i++)
							HI_Copy_Name (&_hoops_GASGH->_hoops_IIAIR->_hoops_ACAIR[i],
										  &_hoops_RASGH->_hoops_IIAIR->_hoops_ACAIR[i]);

						_hoops_APRGA (_hoops_GASGH->_hoops_IIAIR->_hoops_PCAIR,
									 _hoops_RASGH->_hoops_IIAIR->_hoops_RCAIR, Integer32,
									 _hoops_RASGH->_hoops_IIAIR->_hoops_PCAIR);
					}
				}

				if (!BIT (_hoops_RASGH->_hoops_IIAIR->mask, _hoops_GCCRP)) {
					if ((_hoops_RASGH->_hoops_IIAIR->weight_count = _hoops_GASGH->_hoops_IIAIR->weight_count) != 0) {
						_hoops_APRGA (_hoops_GASGH->_hoops_IIAIR->weights,
									 _hoops_RASGH->_hoops_IIAIR->weight_count, _hoops_HCAIR,
									 _hoops_RASGH->_hoops_IIAIR->weights);
					}
				}

				_hoops_RASGH->_hoops_IIAIR->value |= _hoops_GASGH->_hoops_IIAIR->value & _hoops_ACCRP &
												   _hoops_GASGH->_hoops_IIAIR->mask &
												   ~_hoops_RASGH->_hoops_IIAIR->mask;
				_hoops_RASGH->_hoops_IIAIR->mask |= _hoops_GASGH->_hoops_IIAIR->mask & _hoops_ACCRP;
			}
		}

		if (BIT (_hoops_GASGH->_hoops_RSIAA, _hoops_PGRAP)) {
			if (!BIT (_hoops_RASGH->_hoops_SHAAP, _hoops_AIGRP)) {
				_hoops_RASGH->_hoops_IHRH.scale = _hoops_GASGH->_hoops_IHRH.scale;
				_hoops_RASGH->_hoops_IHRH.translate = _hoops_GASGH->_hoops_IHRH.translate;
			}
			if (!BIT (_hoops_RASGH->_hoops_SHAAP, _hoops_PIGRP))
				_hoops_RASGH->_hoops_IHRH.color = _hoops_GASGH->_hoops_IHRH.color;
			if (!BIT (_hoops_RASGH->_hoops_SHAAP, _hoops_HIGRP))
				_hoops_RASGH->_hoops_IHRH._hoops_ACGRP = _hoops_GASGH->_hoops_IHRH._hoops_ACGRP;

			_hoops_RASGH->_hoops_GIAAP |= _hoops_GASGH->_hoops_GIAAP & _hoops_GASGH->_hoops_SHAAP & ~_hoops_RASGH->_hoops_SHAAP;
			_hoops_RASGH->_hoops_SHAAP |= _hoops_GASGH->_hoops_SHAAP;
		}

		if (BIT (_hoops_GASGH->_hoops_RSIAA, _hoops_GGRAP)) {
			if (_hoops_RASGH->_hoops_HHAIR == null)
				ZALLOC(_hoops_RASGH->_hoops_HHAIR, _hoops_RIAIR);

			if (!BIT (_hoops_RASGH->_hoops_HHAIR->_hoops_IHAIR.mask, _hoops_ICSRP)) {
				_hoops_RASGH->_hoops_HHAIR->_hoops_IHAIR._hoops_HCIR[0] = _hoops_GASGH->_hoops_HHAIR->_hoops_IHAIR._hoops_HCIR[0];
				_hoops_RASGH->_hoops_HHAIR->_hoops_IHAIR._hoops_HCIR[1] = _hoops_GASGH->_hoops_HHAIR->_hoops_IHAIR._hoops_HCIR[1];
			}
			if (!BIT (_hoops_RASGH->_hoops_HHAIR->_hoops_IHAIR.mask, _hoops_SCSRP)) {
				_hoops_RASGH->_hoops_HHAIR->_hoops_IHAIR._hoops_GRCR = _hoops_GASGH->_hoops_HHAIR->_hoops_IHAIR._hoops_GRCR;
			}
			if (!BIT (_hoops_RASGH->_hoops_HHAIR->_hoops_IHAIR.mask, _hoops_GSSRP)) {
				if (_hoops_GASGH->_hoops_HHAIR->_hoops_IHAIR._hoops_CHAIR != null) {
					// _hoops_SRAI _hoops_SCH
					Style * style = _hoops_GASGH->_hoops_HHAIR->_hoops_IHAIR._hoops_CHAIR;
					_hoops_RASGH->_hoops_HHAIR->_hoops_IHAIR._hoops_CHAIR = style;
					style->backlink = (Attribute**)&_hoops_RASGH->_hoops_HHAIR->_hoops_IHAIR._hoops_CHAIR;
					_hoops_GASGH->_hoops_HHAIR->_hoops_IHAIR._hoops_CHAIR = null;
					style->owner = (_hoops_CRCP*)_hoops_RASGH;
				}
				HI_Copy_Name (&_hoops_GASGH->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR,
							  &_hoops_RASGH->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR);
			}
			_hoops_RASGH->_hoops_HHAIR->_hoops_IHAIR.value |= _hoops_GASGH->_hoops_HHAIR->_hoops_IHAIR.value &
													 _hoops_GASGH->_hoops_HHAIR->_hoops_IHAIR.mask &
													 ~_hoops_RASGH->_hoops_HHAIR->_hoops_IHAIR.mask;
			_hoops_RASGH->_hoops_HHAIR->_hoops_IHAIR.mask |= _hoops_GASGH->_hoops_HHAIR->_hoops_IHAIR.mask;
		}

		if (BIT (_hoops_GASGH->_hoops_RSIAA, _hoops_SGICA)) {
			if (_hoops_RASGH->_hoops_PRSI == null)
				ZALLOC(_hoops_RASGH->_hoops_PRSI, _hoops_PHAIR);

			if (!BIT (_hoops_RASGH->_hoops_PRSI->mask, _hoops_SSCRP))
				_hoops_RASGH->_hoops_PRSI->_hoops_IRSH = _hoops_GASGH->_hoops_PRSI->_hoops_IRSH;
			if (!BIT (_hoops_RASGH->_hoops_PRSI->mask, _hoops_IGSRP))
				_hoops_RASGH->_hoops_PRSI->_hoops_ARPHA = _hoops_GASGH->_hoops_PRSI->_hoops_ARPHA;
			for (int i = 0; i < _hoops_IGAIR; i++) {
				if (!BIT (_hoops_RASGH->_hoops_PRSI->mask, _hoops_ISCRP))
					_hoops_RASGH->_hoops_PRSI->_hoops_PRPHA[i] = _hoops_GASGH->_hoops_PRSI->_hoops_PRPHA[i];
				if (!BIT (_hoops_RASGH->_hoops_PRSI->mask, _hoops_IASRP))
					_hoops_RASGH->_hoops_PRSI->_hoops_AISRP[i] = _hoops_GASGH->_hoops_PRSI->_hoops_AISRP[i];
				if (!BIT (_hoops_RASGH->_hoops_PRSI->mask, _hoops_IRSRP))
					_hoops_RASGH->_hoops_PRSI->_hoops_GHRGR[i] = _hoops_GASGH->_hoops_PRSI->_hoops_GHRGR[i];
			}
			if (!ANYBIT(_hoops_RASGH->_hoops_PRSI->mask, _hoops_HRSRP)) {
				if (_hoops_GASGH->_hoops_PRSI->value & _hoops_PRSRP)
					_hoops_RASGH->_hoops_PRSI->bounding = _hoops_GASGH->_hoops_PRSI->bounding;
			}
			if (!BIT (_hoops_RASGH->_hoops_PRSI->mask, _hoops_CSCRP))
				_hoops_RASGH->_hoops_PRSI->_hoops_HISRP = _hoops_GASGH->_hoops_PRSI->_hoops_HISRP;
			if (!BIT (_hoops_RASGH->_hoops_PRSI->mask, _hoops_HASRP))
				_hoops_RASGH->_hoops_PRSI->_hoops_IISRP = _hoops_GASGH->_hoops_PRSI->_hoops_IISRP;
			if (!BIT (_hoops_RASGH->_hoops_PRSI->mask, _hoops_GGSRP))
				_hoops_RASGH->_hoops_PRSI->_hoops_RHPHA = _hoops_GASGH->_hoops_PRSI->_hoops_RHPHA;
			if (!BIT (_hoops_RASGH->_hoops_PRSI->mask, _hoops_AGSRP))
				_hoops_RASGH->_hoops_PRSI->tolerance = _hoops_GASGH->_hoops_PRSI->tolerance;
			if (!BIT (_hoops_RASGH->_hoops_PRSI->mask, _hoops_GRSRP))
				_hoops_RASGH->_hoops_PRSI->_hoops_SRHHR = _hoops_GASGH->_hoops_PRSI->_hoops_SRHHR;
			if (!BIT (_hoops_RASGH->_hoops_PRSI->mask, _hoops_PASRP))
				_hoops_RASGH->_hoops_PRSI->_hoops_RCSRP = _hoops_GASGH->_hoops_PRSI->_hoops_RCSRP;

			_hoops_RASGH->_hoops_PRSI->value |= _hoops_GASGH->_hoops_PRSI->value & _hoops_GASGH->_hoops_PRSI->mask & ~_hoops_RASGH->_hoops_PRSI->mask;
			_hoops_RASGH->_hoops_PRSI->mask |= _hoops_GASGH->_hoops_PRSI->mask;
		}

		if (BIT (_hoops_GASGH->_hoops_RSIAA, _hoops_IRICA)) {
			if (_hoops_RASGH->geometry == null)
				ZALLOC(_hoops_RASGH->geometry, _hoops_SCAIR);

			if (!BIT (_hoops_RASGH->geometry->_hoops_APPI.mask, _hoops_CHGAP))
				_hoops_RASGH->geometry->_hoops_APPI._hoops_PPPI = _hoops_GASGH->geometry->_hoops_APPI._hoops_PPPI;
			if (!BIT (_hoops_RASGH->geometry->_hoops_APPI.mask, _hoops_SHGAP))
				_hoops_RASGH->geometry->_hoops_APPI._hoops_HPPI = _hoops_GASGH->geometry->_hoops_APPI._hoops_HPPI;
			if (!BIT (_hoops_RASGH->geometry->_hoops_APPI.mask, _hoops_GIGAP))
				_hoops_RASGH->geometry->_hoops_APPI._hoops_IPPI = _hoops_GASGH->geometry->_hoops_APPI._hoops_IPPI;
			if (!BIT (_hoops_RASGH->geometry->_hoops_APPI.mask, _hoops_RIGAP))
				_hoops_RASGH->geometry->_hoops_APPI._hoops_CPPI = _hoops_GASGH->geometry->_hoops_APPI._hoops_CPPI;
			if (!BIT (_hoops_RASGH->geometry->_hoops_APPI.mask, _hoops_AIGAP))
				_hoops_RASGH->geometry->_hoops_APPI._hoops_SPPI = _hoops_GASGH->geometry->_hoops_APPI._hoops_SPPI;

			_hoops_RASGH->geometry->_hoops_APPI.value |= _hoops_GASGH->geometry->_hoops_APPI.value &
													_hoops_GASGH->geometry->_hoops_APPI.mask &
													~_hoops_RASGH->geometry->_hoops_APPI.mask;
			_hoops_RASGH->geometry->_hoops_APPI.mask |= _hoops_GASGH->geometry->_hoops_APPI.mask;
		}

		if (BIT (_hoops_GASGH->_hoops_RSIAA, _hoops_CRICA)) {
			if (_hoops_RASGH->geometry == null)
				ZALLOC(_hoops_RASGH->geometry, _hoops_SCAIR);

			if (!BIT (_hoops_RASGH->geometry->_hoops_PSRIR.mask, _hoops_PIGAP))
				_hoops_RASGH->geometry->_hoops_PSRIR.configs._hoops_GGIRP = _hoops_GASGH->geometry->_hoops_PSRIR.configs._hoops_GGIRP;
			if (!BIT (_hoops_RASGH->geometry->_hoops_PSRIR.mask, _hoops_IIGAP))
				_hoops_RASGH->geometry->_hoops_PSRIR.configs._hoops_CSHRP = _hoops_GASGH->geometry->_hoops_PSRIR.configs._hoops_CSHRP;
			if (!BIT (_hoops_RASGH->geometry->_hoops_PSRIR.mask, _hoops_CIGAP))
				_hoops_RASGH->geometry->_hoops_PSRIR.configs._hoops_RGIRP = _hoops_GASGH->geometry->_hoops_PSRIR.configs._hoops_RGIRP;
			if (!BIT (_hoops_RASGH->geometry->_hoops_PSRIR.mask, _hoops_SIGAP))
				_hoops_RASGH->geometry->_hoops_PSRIR.configs._hoops_AGIRP = _hoops_GASGH->geometry->_hoops_PSRIR.configs._hoops_AGIRP;
			if (!BIT (_hoops_RASGH->geometry->_hoops_PSRIR.mask, _hoops_GCGAP))
				_hoops_RASGH->geometry->_hoops_PSRIR.configs._hoops_PGIRP = _hoops_GASGH->geometry->_hoops_PSRIR.configs._hoops_PGIRP;
			if (!BIT (_hoops_RASGH->geometry->_hoops_PSRIR.mask, _hoops_RCGAP))
				_hoops_RASGH->geometry->_hoops_PSRIR.configs._hoops_SSHRP = _hoops_GASGH->geometry->_hoops_PSRIR.configs._hoops_SSHRP;

			_hoops_ISHRP(_hoops_RASGH->geometry->_hoops_PSRIR.configs);

			_hoops_RASGH->geometry->_hoops_PSRIR.value |= _hoops_GASGH->geometry->_hoops_PSRIR.value &
													   _hoops_GASGH->geometry->_hoops_PSRIR.mask &
													   ~_hoops_RASGH->geometry->_hoops_PSRIR.mask;
			_hoops_RASGH->geometry->_hoops_PSRIR.mask |= _hoops_GASGH->geometry->_hoops_PSRIR.mask;
		}

		if (BIT (_hoops_GASGH->_hoops_RSIAA, _hoops_SRICA)) {
			if (_hoops_RASGH->geometry == null)
				ZALLOC(_hoops_RASGH->geometry, _hoops_SCAIR);

			if (!BIT (_hoops_RASGH->geometry->_hoops_GAICA.mask, _hoops_ACGAP)) {
				for (int i = 0; i < _hoops_IGAIR; i++)
					_hoops_RASGH->geometry->_hoops_GAICA.cylinder[i] = _hoops_GASGH->geometry->_hoops_GAICA.cylinder[i];
			}
			if (!BIT (_hoops_RASGH->geometry->_hoops_GAICA.mask, _hoops_PCGAP)) {
				for (int i = 0; i < _hoops_IGAIR; i++)
					_hoops_RASGH->geometry->_hoops_GAICA.sphere[i] = _hoops_GASGH->geometry->_hoops_GAICA.sphere[i];
			}
			_hoops_RASGH->geometry->_hoops_GAICA.mask |= _hoops_GASGH->geometry->_hoops_GAICA.mask;
		}

		if (BIT (_hoops_GASGH->_hoops_RSIAA, _hoops_HRICA)) {
			if (_hoops_RASGH->geometry == null)
				ZALLOC(_hoops_RASGH->geometry, _hoops_SCAIR);

			if (!BIT (_hoops_RASGH->geometry->mask, _hoops_GHGAP))
				_hoops_RASGH->geometry->_hoops_GCIPR = _hoops_GASGH->geometry->_hoops_GCIPR;

			_hoops_RASGH->geometry->value |= _hoops_GASGH->geometry->value & _hoops_GASGH->geometry->mask & ~_hoops_RASGH->geometry->mask;
			_hoops_RASGH->geometry->mask |= _hoops_GASGH->geometry->mask;
		}

		if (BIT (_hoops_GASGH->_hoops_RSIAA, _hoops_ARICA)) {
			if (_hoops_RASGH->_hoops_HHAIR == null)
				ZALLOC(_hoops_RASGH->_hoops_HHAIR, _hoops_RIAIR);

			if (!BIT (_hoops_RASGH->_hoops_HHAIR->_hoops_PRIGA.mask, _hoops_RSSRP))
				_hoops_RASGH->_hoops_HHAIR->_hoops_PRIGA.level = _hoops_GASGH->_hoops_HHAIR->_hoops_PRIGA.level;

			if (!BIT (_hoops_RASGH->_hoops_HHAIR->_hoops_PRIGA.mask, _hoops_HSSRP))
				_hoops_RASGH->_hoops_HHAIR->_hoops_PRIGA._hoops_SRIGA = _hoops_GASGH->_hoops_HHAIR->_hoops_PRIGA._hoops_SRIGA;

			if (!BIT (_hoops_RASGH->_hoops_HHAIR->_hoops_PRIGA.mask, _hoops_PSSRP))
				_hoops_RASGH->_hoops_HHAIR->_hoops_PRIGA.tolerance = _hoops_GASGH->_hoops_HHAIR->_hoops_PRIGA.tolerance;

			_hoops_RASGH->_hoops_HHAIR->_hoops_PRIGA.value |= _hoops_GASGH->_hoops_HHAIR->_hoops_PRIGA.value &
													_hoops_GASGH->_hoops_HHAIR->_hoops_PRIGA.mask &
													~_hoops_RASGH->_hoops_HHAIR->_hoops_PRIGA.mask;
			_hoops_RASGH->_hoops_HHAIR->_hoops_PRIGA.mask |= _hoops_GASGH->_hoops_HHAIR->_hoops_PRIGA.mask;
		}

		if (BIT (_hoops_GASGH->_hoops_RSIAA, _hoops_RRICA)) {
			if (_hoops_RASGH->_hoops_HHAIR == null)
				ZALLOC(_hoops_RASGH->_hoops_HHAIR, _hoops_RIAIR);

			if (!BIT (_hoops_RASGH->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_PGGAP))
				_hoops_RASGH->_hoops_HHAIR->_hoops_GHSS._hoops_RGP = _hoops_GASGH->_hoops_HHAIR->_hoops_GHSS._hoops_RGP;

			if (!BIT (_hoops_RASGH->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_IGGAP))
				_hoops_RSAI (&_hoops_GASGH->_hoops_HHAIR->_hoops_GHSS.plane, _hoops_ARPA,
							 &_hoops_RASGH->_hoops_HHAIR->_hoops_GHSS.plane);

			if (!BIT (_hoops_RASGH->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_CGGAP))
				_hoops_RSAI (&_hoops_GASGH->_hoops_HHAIR->_hoops_GHSS.light, Vector,
							 &_hoops_RASGH->_hoops_HHAIR->_hoops_GHSS.light);

			if (!BIT (_hoops_RASGH->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_SGGAP)) {
				HI_Copy_Name (&_hoops_GASGH->_hoops_HHAIR->_hoops_GHSS.color.name,
							  &_hoops_RASGH->_hoops_HHAIR->_hoops_GHSS.color.name);
				_hoops_RASGH->_hoops_HHAIR->_hoops_GHSS.color.rgb = _hoops_GASGH->_hoops_HHAIR->_hoops_GHSS.color.rgb;
			}
			if (!BIT (_hoops_RASGH->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_GRGAP))
				_hoops_RASGH->_hoops_HHAIR->_hoops_GHSS._hoops_IRIR = _hoops_GASGH->_hoops_HHAIR->_hoops_GHSS._hoops_IRIR;
			if (!BIT (_hoops_RASGH->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_RRGAP))
				_hoops_RASGH->_hoops_HHAIR->_hoops_GHSS._hoops_HAP = _hoops_GASGH->_hoops_HHAIR->_hoops_GHSS._hoops_HAP;
			if (!BIT (_hoops_RASGH->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_ARGAP))
				_hoops_RASGH->_hoops_HHAIR->_hoops_GHSS._hoops_IGGGR = _hoops_GASGH->_hoops_HHAIR->_hoops_GHSS._hoops_IGGGR;

			_hoops_RASGH->_hoops_HHAIR->_hoops_GHSS.value |= _hoops_GASGH->_hoops_HHAIR->_hoops_GHSS.value &
													 _hoops_GASGH->_hoops_HHAIR->_hoops_GHSS.mask &
													 ~_hoops_RASGH->_hoops_HHAIR->_hoops_GHSS.mask;
			_hoops_RASGH->_hoops_HHAIR->_hoops_GHSS.mask |= _hoops_GASGH->_hoops_HHAIR->_hoops_GHSS.mask;
		}

		if (BIT (_hoops_GASGH->_hoops_RSIAA, _hoops_CSGAP)) {
			if (_hoops_RASGH->_hoops_HHAIR == null)
				ZALLOC(_hoops_RASGH->_hoops_HHAIR, _hoops_RIAIR);

			if (!BIT (_hoops_RASGH->_hoops_HHAIR->_hoops_HRR.mask, _hoops_PAGAP))
				_hoops_RASGH->_hoops_HHAIR->_hoops_HRR._hoops_HAP = _hoops_GASGH->_hoops_HHAIR->_hoops_HRR._hoops_HAP;
			if (!BIT (_hoops_RASGH->_hoops_HHAIR->_hoops_HRR.mask, _hoops_HAGAP))
				_hoops_RASGH->_hoops_HHAIR->_hoops_HRR._hoops_CAP = _hoops_GASGH->_hoops_HHAIR->_hoops_HRR._hoops_CAP;

			_hoops_RASGH->_hoops_HHAIR->_hoops_HRR.value |= _hoops_GASGH->_hoops_HHAIR->_hoops_HRR.value &
													_hoops_GASGH->_hoops_HHAIR->_hoops_HRR.mask &
													~_hoops_RASGH->_hoops_HHAIR->_hoops_HRR.mask;
			_hoops_RASGH->_hoops_HHAIR->_hoops_HRR.mask |= _hoops_GASGH->_hoops_HHAIR->_hoops_HRR.mask;
		}

		if (BIT (_hoops_GASGH->_hoops_RSIAA, _hoops_SSGAP)) {
			if (_hoops_RASGH->_hoops_HHAIR == null)
				ZALLOC(_hoops_RASGH->_hoops_HHAIR, _hoops_RIAIR);

			if (!BIT (_hoops_RASGH->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_GPGAP))
				_hoops_RSAI (&_hoops_GASGH->_hoops_HHAIR->_hoops_RHGGR.plane, _hoops_ARPA,
							 &_hoops_RASGH->_hoops_HHAIR->_hoops_RHGGR.plane);

			if (!BIT (_hoops_RASGH->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_RPGAP))
				_hoops_RASGH->_hoops_HHAIR->_hoops_RHGGR._hoops_IRIR = _hoops_GASGH->_hoops_HHAIR->_hoops_RHGGR._hoops_IRIR;
			if (!BIT (_hoops_RASGH->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_HPGAP))
				_hoops_RASGH->_hoops_HHAIR->_hoops_RHGGR._hoops_IGGGR = _hoops_GASGH->_hoops_HHAIR->_hoops_RHGGR._hoops_IGGGR;
			if (!BIT (_hoops_RASGH->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_PPGAP)) {
				_hoops_RASGH->_hoops_HHAIR->_hoops_RHGGR.hither = _hoops_GASGH->_hoops_HHAIR->_hoops_RHGGR.hither;
				_hoops_RASGH->_hoops_HHAIR->_hoops_RHGGR.yon = _hoops_GASGH->_hoops_HHAIR->_hoops_RHGGR.yon;
			}

			_hoops_RASGH->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.value |= _hoops_GASGH->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.value &
																	_hoops_GASGH->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.mask &
																	~_hoops_RASGH->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.mask;
			_hoops_RASGH->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.mask |= _hoops_GASGH->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.mask;

			_hoops_RASGH->_hoops_HHAIR->_hoops_RHGGR.value |= _hoops_GASGH->_hoops_HHAIR->_hoops_RHGGR.value &
														 _hoops_GASGH->_hoops_HHAIR->_hoops_RHGGR.mask &
														 ~_hoops_RASGH->_hoops_HHAIR->_hoops_RHGGR.mask;
			_hoops_RASGH->_hoops_HHAIR->_hoops_RHGGR.mask |= _hoops_GASGH->_hoops_HHAIR->_hoops_RHGGR.mask;
		}

		if (BIT (_hoops_GASGH->_hoops_RSIAA, _hoops_GGICA)) {
			if (!BIT (_hoops_RASGH->_hoops_RGICA.mask, _hoops_HPAAP))
				_hoops_RASGH->_hoops_RGICA._hoops_SPAAP = _hoops_GASGH->_hoops_RGICA._hoops_SPAAP;

			if (!BIT (_hoops_RASGH->_hoops_RGICA.mask, _hoops_CPAAP))
				_hoops_RASGH->_hoops_RGICA._hoops_GHAAP = _hoops_GASGH->_hoops_RGICA._hoops_GHAAP;

			_hoops_RASGH->_hoops_RGICA.value |= _hoops_GASGH->_hoops_RGICA.value &
											 _hoops_GASGH->_hoops_RGICA.mask &
											 ~_hoops_RASGH->_hoops_RGICA.mask;
			_hoops_RASGH->_hoops_RGICA.mask |= _hoops_GASGH->_hoops_RGICA.mask;
		}

		if (BIT (_hoops_GASGH->_hoops_RSIAA, _hoops_CSHCA)) {
			if (!BIT (_hoops_RASGH->_hoops_SSHCA.mask, _hoops_RAAAP))
				_hoops_RASGH->_hoops_SSHCA.style = _hoops_GASGH->_hoops_SSHCA.style;

			if (!BIT (_hoops_RASGH->_hoops_SSHCA.mask, _hoops_AAAAP))
				_hoops_RASGH->_hoops_SSHCA._hoops_SRI = _hoops_GASGH->_hoops_SSHCA._hoops_SRI;

			if (!BIT (_hoops_RASGH->_hoops_SSHCA.mask, _hoops_HAAAP))
				_hoops_RASGH->_hoops_SSHCA._hoops_RPAAP = _hoops_GASGH->_hoops_SSHCA._hoops_RPAAP;
			if (!BIT (_hoops_RASGH->_hoops_SSHCA.mask, _hoops_IAAAP))
				_hoops_RASGH->_hoops_SSHCA._hoops_APAAP = _hoops_GASGH->_hoops_SSHCA._hoops_APAAP;

			_hoops_RASGH->_hoops_SSHCA.value |= _hoops_GASGH->_hoops_SSHCA.value &
													_hoops_GASGH->_hoops_SSHCA.mask &
													~_hoops_RASGH->_hoops_SSHCA.mask;
			_hoops_RASGH->_hoops_SSHCA.mask |= _hoops_GASGH->_hoops_SSHCA.mask;
		}

		if (BIT (_hoops_GASGH->_hoops_RSIAA, _hoops_ISGAP)) {
			_hoops_RASGH->_hoops_CHP.value |= _hoops_GASGH->_hoops_CHP.value &
												_hoops_GASGH->_hoops_CHP.mask &
												~_hoops_RASGH->_hoops_CHP.mask;
			_hoops_RASGH->_hoops_CHP.mask |= _hoops_GASGH->_hoops_CHP.mask;
		}

		if (BIT (_hoops_GASGH->_hoops_RSIAA, _hoops_GSIAA)) {
			if (_hoops_RASGH->locks == null)
				ZALLOC(_hoops_RASGH->locks, _hoops_CCAIR);

			_hoops_PIGRA	_hoops_HAHPP;

			_hoops_RSAI (&_hoops_GASGH->locks->normal.value, _hoops_PIGRA, &_hoops_HAHPP);
			_hoops_HSIAA (&_hoops_HAHPP, &_hoops_RASGH->locks->normal.mask, sizeof (_hoops_PIGRA));
			_hoops_ISIAA (&_hoops_RASGH->locks->normal.value, &_hoops_HAHPP, sizeof (_hoops_PIGRA));

			_hoops_ISIAA (&_hoops_RASGH->locks->normal.mask, &_hoops_GASGH->locks->normal.mask, sizeof (_hoops_PIGRA));
		}

		if (BIT (_hoops_GASGH->_hoops_RSIAA, _hoops_RGRAP)) {
			if (_hoops_RASGH->locks == null)
				ZALLOC(_hoops_RASGH->locks, _hoops_CCAIR);

			_hoops_PIGRA	_hoops_HAHPP;

			_hoops_RSAI (&_hoops_GASGH->locks->_hoops_SACRP.value, _hoops_PIGRA, &_hoops_HAHPP);
			_hoops_HSIAA (&_hoops_HAHPP, &_hoops_RASGH->locks->_hoops_SACRP.mask, sizeof (_hoops_PIGRA));
			_hoops_ISIAA (&_hoops_RASGH->locks->_hoops_SACRP.value, &_hoops_HAHPP, sizeof (_hoops_PIGRA));

			_hoops_ISIAA (&_hoops_RASGH->locks->_hoops_SACRP.mask, &_hoops_GASGH->locks->_hoops_SACRP.mask, sizeof (_hoops_PIGRA));
		}

		_hoops_RASGH->_hoops_PGICA |= _hoops_GASGH->_hoops_PGICA & ~_hoops_RASGH->_hoops_HGICA;



		_hoops_RASGH->_hoops_GHRAP |= _hoops_GASGH->_hoops_GHRAP & _hoops_GASGH->_hoops_ISHCA & ~_hoops_RASGH->_hoops_ISHCA;
		_hoops_RASGH->_hoops_ISHCA |= _hoops_GASGH->_hoops_ISHCA;

		_hoops_RASGH->_hoops_RRRAP |= _hoops_GASGH->_hoops_RRRAP & _hoops_GASGH->_hoops_PSHCA & ~_hoops_RASGH->_hoops_PSHCA;
		_hoops_RASGH->_hoops_PSHCA |= _hoops_GASGH->_hoops_PSHCA;

		_hoops_RASGH->_hoops_RSIAA |= _hoops_GASGH->_hoops_RSIAA & _hoops_GASGH->_hoops_SCIAA & ~_hoops_RASGH->_hoops_SCIAA &
								  ~_hoops_GSHRS;
		_hoops_RASGH->_hoops_SCIAA |= _hoops_GASGH->_hoops_SCIAA & ~_hoops_GSHRS;
	}

	if (_hoops_RASGH->_hoops_PSHRP != null) {
		_hoops_RASGH->_hoops_IRARR &= ~_hoops_RASGH->_hoops_PSHRP->clear;
		_hoops_RASGH->_hoops_IRARR |= _hoops_RASGH->_hoops_PSHRP->set;

		_hoops_RASGH->_hoops_PSHCA |= _hoops_PRRAP;
		_hoops_RASGH->_hoops_RRRAP |= _hoops_PRRAP;

		/* _hoops_HAR _hoops_GCPRA */
		FREE (_hoops_RASGH->_hoops_PSHRP, _hoops_SCGAP);
		_hoops_RASGH->_hoops_PSHRP = null;
	}

	/* _hoops_IRHH _hoops_RCRR _hoops_CASH-_hoops_PAPA _hoops_AAHS _hoops_GHSAI _hoops_RSHRS _hoops_ISHP _hoops_IS _hoops_ISPAA */
	if (BIT(_hoops_RASGH->_hoops_SCIAA, _hoops_GSIAA)) {
		if (_hoops_RASGH->locks == null)
			ZALLOC (_hoops_RASGH->locks, _hoops_CCAIR);

		if (!BIT(_hoops_RASGH->_hoops_SCIAA & _hoops_RASGH->_hoops_RSIAA, _hoops_GSIAA)) {
			if (BIT(_hoops_RASGH->_hoops_SCIAA, _hoops_GSIAA))
				_hoops_RASGH->locks->normal.mask._hoops_IPPGR = _hoops_HPHRS;
			else
				_hoops_RASGH->locks->normal.mask._hoops_IPPGR = 0;
			_hoops_RASGH->locks->normal.value._hoops_IPPGR = 0;
		}
		if (!BIT(_hoops_RASGH->locks->normal.mask._hoops_IPPGR &
				 _hoops_RASGH->locks->normal.value._hoops_IPPGR, _hoops_GGCAA(HK_COLOR))) {
			if (BIT(_hoops_RASGH->locks->normal.mask._hoops_IPPGR, _hoops_GGCAA(HK_COLOR)))
				_hoops_RASGH->locks->normal.mask.color = ~0U;
			else
				_hoops_RASGH->locks->normal.mask.color = 0;
			_hoops_RASGH->locks->normal.value.color = 0;
		}

		for (int i=0; i<_hoops_IIGRA; i++) {
			if (!BIT(_hoops_RASGH->locks->normal.mask.color &
					 _hoops_RASGH->locks->normal.value.color, 1UL<<i)) {
				if (BIT(_hoops_RASGH->locks->normal.mask.color, 1UL<<i))
					_hoops_RASGH->locks->normal.mask._hoops_HAA[i] = ~0U;
				else
					_hoops_RASGH->locks->normal.mask._hoops_HAA[i] = 0;
				_hoops_RASGH->locks->normal.value._hoops_HAA[i] = 0;
			}
		}
		if (!BIT(_hoops_RASGH->locks->normal.mask._hoops_IPPGR &
				 _hoops_RASGH->locks->normal.value._hoops_IPPGR, _hoops_GGCAA(HK_VISIBILITY))) {
			if (BIT(_hoops_RASGH->locks->normal.mask._hoops_IPPGR, _hoops_GGCAA(HK_VISIBILITY)))
				_hoops_RASGH->locks->normal.mask._hoops_RGP = ~0;
			else
				_hoops_RASGH->locks->normal.mask._hoops_RGP = 0;
			_hoops_RASGH->locks->normal.value._hoops_RGP = 0;
		}

		if (!BIT(_hoops_RASGH->_hoops_SCIAA & _hoops_RASGH->_hoops_RSIAA, _hoops_RGRAP)) {
			if (BIT(_hoops_RASGH->_hoops_SCIAA, _hoops_RGRAP))
				_hoops_RASGH->locks->_hoops_SACRP.mask._hoops_IPPGR = _hoops_HPHRS;
			else
				_hoops_RASGH->locks->_hoops_SACRP.mask._hoops_IPPGR = 0;
			_hoops_RASGH->locks->_hoops_SACRP.value._hoops_IPPGR = 0;
		}
		if (!BIT(_hoops_RASGH->locks->_hoops_SACRP.mask._hoops_IPPGR &
				 _hoops_RASGH->locks->_hoops_SACRP.value._hoops_IPPGR, _hoops_GGCAA(HK_COLOR))) {
			if (BIT(_hoops_RASGH->locks->_hoops_SACRP.mask._hoops_IPPGR, _hoops_GGCAA(HK_COLOR)))
				_hoops_RASGH->locks->_hoops_SACRP.mask.color = ~0U;
			else
				_hoops_RASGH->locks->_hoops_SACRP.mask.color = 0;
			_hoops_RASGH->locks->_hoops_SACRP.value.color = 0;
		}
		for (int i=0; i<_hoops_IIGRA; i++) {
			if (!BIT(_hoops_RASGH->locks->_hoops_SACRP.mask.color &
					 _hoops_RASGH->locks->_hoops_SACRP.value.color, 1UL<<i)) {
				if (BIT(_hoops_RASGH->locks->_hoops_SACRP.mask.color, 1UL<<i))
					_hoops_RASGH->locks->_hoops_SACRP.mask._hoops_HAA[i] = ~0U;
				else
					_hoops_RASGH->locks->_hoops_SACRP.mask._hoops_HAA[i] = 0;
				_hoops_RASGH->locks->_hoops_SACRP.value._hoops_HAA[i] = 0;
			}
		}
		if (!BIT(_hoops_RASGH->locks->_hoops_SACRP.mask._hoops_IPPGR &
				 _hoops_RASGH->locks->_hoops_SACRP.value._hoops_IPPGR, _hoops_GGCAA(HK_VISIBILITY))) {
			if (BIT(_hoops_RASGH->locks->_hoops_SACRP.mask._hoops_IPPGR, _hoops_GGCAA(HK_VISIBILITY)))
				_hoops_RASGH->locks->_hoops_SACRP.mask._hoops_RGP = ~0;
			else
				_hoops_RASGH->locks->_hoops_SACRP.mask._hoops_RGP = 0;
			_hoops_RASGH->locks->_hoops_SACRP.value._hoops_RGP = 0;
		}
	}

	return _hoops_RASGH;
}


local void _hoops_ASHRS (
	Option_Value *			option,
	_hoops_RHAIR *		_hoops_APHCR,
	_hoops_GHGI				_hoops_PSHRS,
	_hoops_CACRP *	_hoops_HSHRS) {

	if (option == null) {
		SET_MEMORY (_hoops_HSHRS, sizeof (_hoops_CACRP), ~0);
		_hoops_HSHRS->mask._hoops_IPPGR &= _hoops_HPHRS;
		_hoops_APHCR->_hoops_RSIAA |= _hoops_PSHRS;
	}
	else do {
		_hoops_HHAGP				mask;

		if ((mask = option->type->id) != 0) {
			Option_Value			*_hoops_CHAGA;

			_hoops_HSHRS->mask._hoops_IPPGR |= mask;

			if (mask == _hoops_GGCAA(HK_COLOR)) {
				if (option->_hoops_GCACR) {
					/* '_hoops_PSP _hoops_HAIR' -- _hoops_SSIAA _hoops_HCR _hoops_PSHA */
					_hoops_HSHRS->value._hoops_IPPGR &= ~mask;
					_hoops_HSHRS->mask.color = _hoops_HSHRS->value.color = 0;
					ZERO_ARRAY (_hoops_HSHRS->mask._hoops_HAA, _hoops_IIGRA, _hoops_ARGRA);
					ZERO_ARRAY (_hoops_HSHRS->value._hoops_HAA, _hoops_IIGRA, _hoops_ARGRA);
				}
				else if ((_hoops_CHAGA = option->value.option_list) == null) {
					/* '_hoops_HAIR' -- _hoops_AAHS _hoops_HCR _hoops_PSHA */
					_hoops_HSHRS->value._hoops_IPPGR |= mask;
					_hoops_HSHRS->mask.color = _hoops_HSHRS->value.color = Color_EVERYTHING & ~Color_CUT_GEOMETRY;
					SET_MEMORY (_hoops_HSHRS->mask._hoops_HAA, _hoops_IIGRA*sizeof (_hoops_ARGRA), ~0);
					SET_MEMORY (_hoops_HSHRS->value._hoops_HAA, _hoops_IIGRA*sizeof (_hoops_ARGRA), ~0);
				}
				else do {
					Color_Object			_hoops_ISHRS;

					if ((_hoops_ISHRS = (Color_Object)_hoops_CHAGA->type->id) != 0) {
						/* _hoops_CPHP _hoops_PII '_hoops_HAIR=_hoops_III' */
						Option_Value *				_hoops_CCIIH;
						_hoops_ARGRA			channel = 0;
						_hoops_ARGRA			set = 0;
						_hoops_ARGRA			_hoops_ASHIP = ~0;

						_hoops_HSHRS->mask.color |= _hoops_ISHRS;

						if (_hoops_CHAGA->_hoops_GCACR) {
							/* '_hoops_HAIR=_hoops_PSP _hoops_III' -- _hoops_GRS _hoops_SSIAA _hoops_HCR _hoops_III _hoops_GRIP */
							_hoops_HSHRS->value.color &= ~_hoops_ISHRS;
							channel = ~0;
							_hoops_ASHIP = 0;
							set = 0;
						}
						else if ((_hoops_CCIIH = _hoops_CHAGA->value.option_list) == null) {
							/* '_hoops_HAIR=_hoops_III' -- _hoops_GRS _hoops_AAHS _hoops_HCR _hoops_III _hoops_GRIP */
							_hoops_HSHRS->value.color |= _hoops_ISHRS;
							channel = ~0;
							_hoops_ASHIP = ~0;
							set = ~0;
						}
						else {
							_hoops_HSHRS->value.color |= _hoops_ISHRS;
							do {
								_hoops_ARGRA			_hoops_CSHRS;

								if ((_hoops_CSHRS = _hoops_CCIIH->type->id) == 0) {
									/* '_hoops_HAIR=_hoops_III=_hoops_PSAP' -- _hoops_GRS _hoops_SSIAA _hoops_HCR _hoops_III _hoops_GRIP*/
									channel = ~0;
									_hoops_ASHIP = ~0;
									set = ~0;
								}
								else if (_hoops_CCIIH->_hoops_GCACR) {
									/* '_hoops_HAIR=_hoops_III=_hoops_PSP _hoops_SPI' -- _hoops_GRS _hoops_SSIAA _hoops_RH _hoops_CHIA _hoops_III _hoops_GRIP*/
									channel |= _hoops_CSHRS;
									_hoops_ASHIP &= ~_hoops_CSHRS;
									set &= ~_hoops_CSHRS;
								}
								else {
									/* '_hoops_HAIR=_hoops_III=_hoops_SPI' -- _hoops_GRS _hoops_AAHS _hoops_RH _hoops_CHIA _hoops_III _hoops_GRIP*/
									channel |= _hoops_CSHRS;
									set |= _hoops_CSHRS;
								}
							} while ((_hoops_CCIIH = _hoops_CCIIH->next) != null);
						}

						/* _hoops_GHAA _hoops_RH _hoops_PHPHA _hoops_SIH _hoops_IS _hoops_HCR _hoops_IRPR _hoops_HAIR _hoops_AGSAR (_hoops_GAAP _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_CPAP _hoops_GPRR) */
						for (int i=0; i<_hoops_IIGRA; i++) {
							if (BIT (_hoops_ISHRS, 1<<i)) {
								_hoops_HSHRS->mask._hoops_HAA[i] |= channel;
								_hoops_HSHRS->value._hoops_HAA[i] &= _hoops_ASHIP;
								_hoops_HSHRS->value._hoops_HAA[i] |= set;
							}
						}

						_hoops_HSHRS->value._hoops_IPPGR |= mask;
					}
					else {	/* ' _hoops_HAIR=_hoops_PSAP' -- _hoops_PSHR _hoops_GAR '_hoops_PSP _hoops_HAIR' */
						_hoops_HSHRS->value._hoops_IPPGR &= ~mask;
						_hoops_HSHRS->mask.color = 0;
						_hoops_HSHRS->value.color = 0;
						ZERO_ARRAY (_hoops_HSHRS->mask._hoops_HAA, _hoops_IIGRA, _hoops_ARGRA);
						ZERO_ARRAY (_hoops_HSHRS->value._hoops_HAA, _hoops_IIGRA, _hoops_ARGRA);
					}
				} while ((_hoops_CHAGA = _hoops_CHAGA->next) != null);
			}
			else if (mask == _hoops_GGCAA(HK_VISIBILITY)) {
				if (option->_hoops_GCACR) {
					_hoops_HSHRS->mask._hoops_RGP = 0;
					_hoops_HSHRS->value._hoops_RGP = 0;
					_hoops_HSHRS->value._hoops_IPPGR &= ~mask;
				}
				else if ((_hoops_CHAGA = option->value.option_list) == null) {
					_hoops_HSHRS->mask._hoops_RGP = ~0;
					_hoops_HSHRS->value._hoops_RGP = ~0;
					_hoops_HSHRS->value._hoops_IPPGR |= mask;
				}
				else do {
					_hoops_ACHR		_hoops_SSHRS;

					if ((_hoops_SSHRS = _hoops_CHAGA->type->id) != 0) {
						_hoops_HSHRS->mask._hoops_RGP |= _hoops_SSHRS;

						if (_hoops_CHAGA->_hoops_GCACR)
							_hoops_HSHRS->value._hoops_RGP &= ~_hoops_SSHRS;
						else
							_hoops_HSHRS->value._hoops_RGP |= _hoops_SSHRS;

						_hoops_HSHRS->value._hoops_IPPGR |= mask;
					}
					else {
						_hoops_HSHRS->mask._hoops_RGP = 0;
						_hoops_HSHRS->value._hoops_RGP = 0;
						_hoops_HSHRS->value._hoops_IPPGR &= ~mask;
					}
				} while ((_hoops_CHAGA = _hoops_CHAGA->next) != null);
			}
			else if (option->_hoops_GCACR) {
				_hoops_HSHRS->value._hoops_IPPGR &= ~mask;

				if (BIT (mask, _hoops_GGCAA(HK_COLOR))) {
					_hoops_HSHRS->mask.color = _hoops_HSHRS->value.color = 0;
					ZERO_ARRAY (_hoops_HSHRS->mask._hoops_HAA, _hoops_IIGRA, _hoops_ARGRA);
					ZERO_ARRAY (_hoops_HSHRS->value._hoops_HAA, _hoops_IIGRA, _hoops_ARGRA);
				}
				if (BIT (mask, _hoops_GGCAA(HK_VISIBILITY))) {
					_hoops_HSHRS->mask._hoops_RGP = 0;
					_hoops_HSHRS->value._hoops_RGP = 0;
				}
			}
			else {
				_hoops_HSHRS->value._hoops_IPPGR |= mask;

				if (BIT (mask, _hoops_GGCAA(HK_COLOR))) {
					_hoops_HSHRS->mask.color = _hoops_HSHRS->value.color = Color_EVERYTHING & ~Color_CUT_GEOMETRY;
					SET_MEMORY (_hoops_HSHRS->mask._hoops_HAA, _hoops_IIGRA*sizeof (_hoops_ARGRA), ~0);
					SET_MEMORY (_hoops_HSHRS->value._hoops_HAA, _hoops_IIGRA*sizeof (_hoops_ARGRA), ~0);
				}
				if (BIT (mask, _hoops_GGCAA(HK_VISIBILITY))) {
					_hoops_HSHRS->mask._hoops_RGP = ~0;
					_hoops_HSHRS->value._hoops_RGP = ~0;
				}
			}

			_hoops_APHCR->_hoops_RSIAA |= _hoops_PSHRS;
		}
		else {
			_hoops_HSHRS->mask._hoops_IPPGR = false;
			_hoops_HSHRS->value._hoops_IPPGR = false;
			_hoops_APHCR->_hoops_RSIAA &= ~_hoops_PSHRS;
		}
	} while ((option = option->next) != null);
}


local bool _hoops_GGIRS (
	Option_Value *			option,
	_hoops_RHAIR *		_hoops_APHCR) {

	if (option == null)
		return false;

	do {
		_hoops_PPAAP		mask;
		bool				_hoops_GCACR;

		mask = (_hoops_PPAAP)option->type->id;
		_hoops_GCACR = option->_hoops_GCACR;

		if (mask == _hoops_PHPRS) {
			/* _hoops_RSAIP _hoops_IS _hoops_IRHH _hoops_CCAR _hoops_RGIRS _hoops_PCCP _hoops_AGIRS _hoops_IIGR _hoops_CCAR _hoops_PGIRS */
			mask = _hoops_HHGAP;
			_hoops_GCACR = !_hoops_GCACR;
		}

		_hoops_APHCR->geometry->_hoops_APPI.mask |= mask;

		if (_hoops_GCACR) {
			_hoops_APHCR->geometry->_hoops_APPI.value &= ~mask;
		}
		else {
			_hoops_APHCR->geometry->_hoops_APPI.value |= mask;

			if (mask == _hoops_CHGAP) {
				if (option->value._hoops_RIARA[0] < 0) {
					HE_ERROR2 (HEC_RENDERING, HES_BAD_SIZE_LIMIT,
							   "The curve option 'budget'",
							   "requires a non-negative value");
					return false;
				}
				_hoops_APHCR->geometry->_hoops_APPI._hoops_PPPI = option->value._hoops_RIARA[0];
			}
			else if (mask == _hoops_SHGAP) {
				if (option->value._hoops_RIARA[0] < 0) {
					HE_ERROR2 (HEC_RENDERING, HES_BAD_SIZE_LIMIT,
							   "The curve option 'continued budget'",
							   "requires a non-negative value");
					return false;
				}
				_hoops_APHCR->geometry->_hoops_APPI._hoops_HPPI = option->value._hoops_RIARA[0];
			}
			else if (mask == _hoops_GIGAP) {
				if (option->value._hoops_PIPCR[0] < 0) {
					HE_ERROR2 (HEC_RENDERING, HES_BAD_SIZE_LIMIT,
							   "The curve option 'max deviation'",
							   "requires a non-negative value");
					return false;
				}
				_hoops_APHCR->geometry->_hoops_APPI._hoops_IPPI = option->value._hoops_PIPCR[0];
			}
			else if (mask == _hoops_RIGAP) {
				if (option->value._hoops_PIPCR[0] < 0) {
					HE_ERROR2 (HEC_RENDERING, HES_BAD_SIZE_LIMIT,
							   "The curve option 'max angle'",
							   "requires a non-negative value");
					return false;
				}
				_hoops_APHCR->geometry->_hoops_APPI._hoops_CPPI = option->value._hoops_PIPCR[0];
			}
			else if (mask == _hoops_AIGAP) {
				if (option->value._hoops_PIPCR[0] < 0) {
					HE_ERROR2 (HEC_RENDERING, HES_BAD_SIZE_LIMIT,
							   "The curve option 'max length'",
							   "requires a non-negative value");
					return false;
				}
				_hoops_APHCR->geometry->_hoops_APPI._hoops_SPPI = option->value._hoops_PIPCR[0];
			}
		}
	} while ((option = option->next) != null);

	return true;
}


GLOBAL_FUNCTION bool HI_Process_NURBS_Surface_Options (
	Option_Value const *		option,
	_hoops_RHAIR alter *	_hoops_APHCR) {

	if (option == null)
		return false;

	do {
		_hoops_PPAAP			mask;
		bool					_hoops_GCACR;

		mask = (_hoops_PPAAP)option->type->id;
		_hoops_GCACR = option->_hoops_GCACR;

		_hoops_APHCR->geometry->_hoops_PSRIR.mask |= mask;

		if (_hoops_GCACR) {
			_hoops_APHCR->geometry->_hoops_PSRIR.value &= ~mask;
		}
		else {
			_hoops_APHCR->geometry->_hoops_PSRIR.value |= mask;

			if (mask == _hoops_PIGAP) {
				if (option->value._hoops_PIPCR[0] < 0) {
					HE_ERROR2 (HEC_RENDERING, HES_BAD_SIZE_LIMIT,
							   "The NURBS Surface option 'max trim curve deviation'",
							   "requires a non-negative value");
					return false;
				}
				_hoops_APHCR->geometry->_hoops_PSRIR.configs._hoops_GGIRP = option->value._hoops_PIPCR[0];
			}
			else if (mask == _hoops_IIGAP) {
				if (option->value._hoops_RIARA[0] < 0) {
					HE_ERROR2 (HEC_RENDERING, HES_BAD_SIZE_LIMIT,
							   "The NURBS Surface option 'trim curve budget'",
							   "requires a non-negative value");
					return false;
				}
				_hoops_APHCR->geometry->_hoops_PSRIR.configs._hoops_CSHRP = option->value._hoops_RIARA[0];
			}
			else if (mask == _hoops_CIGAP) {
				if (option->value._hoops_PIPCR[0] < 0) {
					HE_ERROR2 (HEC_RENDERING, HES_BAD_SIZE_LIMIT,
							   "The NURBS Surface option 'max facet deviation'",
							   "requires a non-negative value");
					return false;
				}
				_hoops_APHCR->geometry->_hoops_PSRIR.configs._hoops_RGIRP = option->value._hoops_PIPCR[0];
			}
			else if (mask == _hoops_SIGAP) {
				if (option->value._hoops_PIPCR[0] < 0) {
					HE_ERROR2 (HEC_RENDERING, HES_BAD_SIZE_LIMIT,
							   "The NURBS Surface option 'max facet angle'",
							   "requires a non-negative value");
					return false;
				}
				_hoops_APHCR->geometry->_hoops_PSRIR.configs._hoops_AGIRP = option->value._hoops_PIPCR[0];
			}
			else if (mask == _hoops_GCGAP) {
				if (option->value._hoops_PIPCR[0] < 0) {
					HE_ERROR2 (HEC_RENDERING, HES_BAD_SIZE_LIMIT,
							   "The NURBS Surface option 'max facet width'",
							   "requires a non-negative value");
					return false;
				}
				_hoops_APHCR->geometry->_hoops_PSRIR.configs._hoops_PGIRP = option->value._hoops_PIPCR[0];
			}
			else if (mask == _hoops_RCGAP) {
				if (option->value._hoops_RIARA[0] < 0) {
					HE_ERROR2 (HEC_RENDERING, HES_BAD_SIZE_LIMIT,
							   "The NURBS Surface option 'budget'",
							   "requires a non-negative value");
					return false;
				}
				_hoops_APHCR->geometry->_hoops_PSRIR.configs._hoops_SSHRP = option->value._hoops_RIARA[0];
			}
			/* _hoops_SHS _hoops_AA _hoops_ISAP */
		}
	} while ((option = option->next) != null);
	_hoops_APHCR->geometry->_hoops_PSRIR.configs._hoops_GRPPA = 0; /* _hoops_SR'_hoops_GCPP _hoops_CAHA _hoops_GGSR _hoops_RH _hoops_RRHPA _hoops_SPHR */

	return true;
}


local bool _hoops_HGIRS (
	Option_Value *				option,
	_hoops_RHAIR *			_hoops_APHCR) {
	int							i, j;

	if (option == null)
		return false;

	do {
		_hoops_PPAAP			mask;

		mask = (_hoops_PPAAP)option->type->id;

		_hoops_APHCR->geometry->_hoops_GAICA.mask |= mask;

		/* _hoops_SGH _hoops_IRS _hoops_IGRH _hoops_RPGP _hoops_HRII _hoops_HSAR _hoops_CGCH _hoops_GHRCC _hoops_PGGA _hoops_IGIRS _hoops_HRGR _hoops_PCCP _hoops_PHPPR _hoops_IH _hoops_GIPR
		 * _hoops_CGIRS _hoops_PPR _hoops_SGIRS */
		if (BIT (mask, _hoops_ACGAP)) {
			if (option->_hoops_AIPCR == 0) {
				HE_ERROR2 (HEC_RENDERING, HES_INVALID_COUNT,
						   "The Tessellation option 'cylinder'",
						   "requires 1 or more values");
				return false;
			}
			for (i=0; i<option->_hoops_AIPCR; ++i)
				_hoops_APHCR->geometry->_hoops_GAICA.cylinder[i] = option->value._hoops_RIARA[i];
			for (j=i; j<_hoops_IGAIR; ++j)
				_hoops_APHCR->geometry->_hoops_GAICA.cylinder[j] = _hoops_APHCR->geometry->_hoops_GAICA.cylinder[j-1];
		}
		else if (BIT (mask, _hoops_PCGAP)) {
			if (option->_hoops_AIPCR == 0) {
				HE_ERROR2 (HEC_RENDERING, HES_INVALID_COUNT,
						   "The Tessellation option 'sphere'",
						   "requires 1 or more values");
				return false;
			}
			for (i=0; i<option->_hoops_AIPCR; ++i)
				_hoops_APHCR->geometry->_hoops_GAICA.sphere[i] = option->value._hoops_RIARA[i];
			for (j=i; j<_hoops_IGAIR; ++j)
				_hoops_APHCR->geometry->_hoops_GAICA.sphere[j] = _hoops_APHCR->geometry->_hoops_GAICA.sphere[j-1];
		}
	} while ((option = option->next) != null);

	return true;
}


local bool _hoops_GRIRS (
	Option_Value *			option,
	_hoops_RHAIR *		_hoops_APHCR) {

	if (option == null)
		_hoops_APHCR->_hoops_PGICA = _hoops_APHCR->_hoops_HGICA = _hoops_SCAAP;
	else do {
		int	mask = (int)option->type->id;


		if (option->_hoops_GCACR) {
			_hoops_APHCR->_hoops_HGICA |= mask;
			_hoops_APHCR->_hoops_PGICA &= ~mask;
		}
		else {
			Option_Value *		_hoops_AHSAA;

			if ((_hoops_AHSAA = option->value.option_list) == null) {
				_hoops_APHCR->_hoops_HGICA |= mask;
				_hoops_APHCR->_hoops_PGICA |= mask;
			}
			else {
				do {
					int			_hoops_PHSAA = (int)_hoops_AHSAA->type->id;

					_hoops_APHCR->_hoops_HGICA |= _hoops_PHSAA;

					if (_hoops_AHSAA->_hoops_GCACR)
						_hoops_APHCR->_hoops_PGICA &= ~_hoops_PHSAA;
					else
						_hoops_APHCR->_hoops_PGICA |= _hoops_PHSAA;
				} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
			}
		}
	} while ((option = option->next) != null);

	return true;
}

local bool _hoops_RRIRS (
	Option_Value *				option,
	_hoops_RHAIR *			_hoops_APHCR) {

	if (option == null) {
		_hoops_APHCR->_hoops_HHAIR->_hoops_PRIGA.mask = 0;
		_hoops_APHCR->_hoops_HHAIR->_hoops_PRIGA.value = 0;
	}
	else do {
		_hoops_PPAAP			mask;

		mask = (_hoops_PPAAP)option->type->id;
		_hoops_APHCR->_hoops_HHAIR->_hoops_PRIGA.mask |= mask;

		if (option->_hoops_GCACR) {
			_hoops_APHCR->_hoops_HHAIR->_hoops_PRIGA.value &= ~mask;
		}
		else {
			_hoops_APHCR->_hoops_HHAIR->_hoops_PRIGA.value |= mask;

			if (mask == _hoops_RSSRP) {
				_hoops_APHCR->_hoops_HHAIR->_hoops_PRIGA.level =
								(int)option->value.option_list->type->id;
			}
			else if (mask == _hoops_HSSRP) {
				if (option->_hoops_AIPCR == 0)
					_hoops_APHCR->_hoops_HHAIR->_hoops_PRIGA._hoops_SRIGA = _hoops_AGGAP;
				else if (option->value.option_list->type->id ==
						 _hoops_RGGAP)	/* _hoops_PSAP _hoops_RIP */
					_hoops_APHCR->_hoops_HHAIR->_hoops_PRIGA.value &= ~mask;
				else
					_hoops_APHCR->_hoops_HHAIR->_hoops_PRIGA._hoops_SRIGA =
									(int)option->value.option_list->type->id;
			}
			else if (mask == _hoops_PSSRP) {
				if (option->value._hoops_RRRHA[0].value < 0) {
					HE_ERROR2 (HEC_RENDERING, HES_BAD_SIZE_LIMIT,
							   "The cut geometry option 'tolerance'",
							   "requires a non-negative value");
					return false;
				}
				_hoops_APHCR->_hoops_HHAIR->_hoops_PRIGA.tolerance =
								option->value._hoops_RRRHA[0].value;

				_hoops_APHCR->_hoops_HHAIR->_hoops_PRIGA.mask &= ~_hoops_ISSRP;
				_hoops_APHCR->_hoops_HHAIR->_hoops_PRIGA.value &= ~_hoops_ISSRP;
				_hoops_APHCR->_hoops_HHAIR->_hoops_PRIGA.mask |=
								(int)option->value._hoops_RRRHA[0]._hoops_HHP;
				_hoops_APHCR->_hoops_HHAIR->_hoops_PRIGA.value |=
								(int)option->value._hoops_RRRHA[0]._hoops_HHP;
			}
		}
	} while ((option = option->next) != null);

	return true;
}

local bool _hoops_ARIRS (
	_hoops_AIGPR *	_hoops_RIGC,
	Option_Value *			option,
	_hoops_RHAIR *		_hoops_APHCR) {

	/* _hoops_CIS _hoops_APPP _hoops_PICP _hoops_IIGR (_hoops_HCSP == _hoops_IRAP) _hoops_AGIR */
	do {
		_hoops_HGGAP			mask;

		mask = (_hoops_HGGAP)option->type->id;

		if (mask == 0) {		/* _hoops_PSAP */
			_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.mask |= _hoops_PGGAP;
			_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.value &= ~_hoops_PGGAP;
			_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS._hoops_RGP = _hoops_HRGAP;
		}
		else if (mask == -1) {	 /* _hoops_GRH _hoops_RIP _hoops_IH _hoops_SPRS */
			_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.mask |= _hoops_PGGAP;
			_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.value |= _hoops_PGGAP;
			_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS._hoops_RGP = _hoops_CRGAP;
		}
		else {
			_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.mask |= mask;

			if (option->_hoops_GCACR) {
				_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.value &= ~mask;
			}
			else {
				_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.value |= mask;

				if (mask == _hoops_PGGAP) {
					_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS._hoops_RGP = _hoops_IRGAP;
				}
				else if (mask == _hoops_IGGAP) {
					_hoops_AIGA (option->value._hoops_PIPCR, 4, float, &_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.plane);

					if (!HI_Normalize_Plane (&_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.plane)) {
						HE_WARNING (HEC_INTERNAL_ERROR, HES_SINGULAR_PLANE,
									"Bad simple shadow plane definition");
						_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.value &= ~mask;
					}
				}
				else if (mask == _hoops_CGGAP) {
					_hoops_AIGA (option->value._hoops_PIPCR, 3, float, &_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.light);

					if (!HI_Normalize (&_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.light)) {
						HE_WARNING (HEC_RENDERING, HES_ZERO_LENGTH,
									"Bad simple shadow light direction");
						_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.value &= ~mask;
					}
				}
				else if (mask == _hoops_SGGAP) {
					Named_Material		_hoops_GGPRA;

					if (option->value._name[0].text[0] == '#') {
						char const *	_hoops_CSHPP;
						char const *	_hoops_RASGR;

						_hoops_CSHPP = &option->value._name[0].text[1];
						_hoops_RASGR = _hoops_CSHPP + option->value._name[0].length - 1;

						if (HI_Scan_Float (_hoops_RIGC, &_hoops_CSHPP, _hoops_RASGR,
									&_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.color.rgb.red) != null ||
							_hoops_CSHPP != _hoops_RASGR) {
							/* _hoops_RIHH */
							return false;
						}
						_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.color.rgb.green =
						  _hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.color.rgb.blue = -1.0f;
					}
					else {
						ZERO_STRUCT(&_hoops_GGPRA, Named_Material);
						if (!HI_Evaluate_Color (_hoops_RIGC, &option->value._name[0], &_hoops_GGPRA, 0, true)) {
							/* (_hoops_RIHH _hoops_AIAH _hoops_CRPPR) */
							HI_Free_Material_Names (&_hoops_GGPRA, 1);
							return false;
						}

						/* _hoops_HGI _hoops_RRGR _hoops_IHCI _hoops_RH _hoops_APIR/_hoops_HH _hoops_IPPHR _hoops_SGS _hoops_CSAP
						** _hoops_CRPRA _hoops_GGSR _hoops_CRGR _hoops_SRPRA _hoops_IAPR _hoops_IS _hoops_RH _hoops_GCRRA _hoops_HRPR.
						*/
						if (ANYBIT (_hoops_GGPRA._hoops_PRGRA, ~(M_DIFFUSE|_hoops_RHGRA)) ||
							_hoops_GGPRA._hoops_SCA != null) {		/* _hoops_IRHH _hoops_SCH _hoops_IHGP */
							/* _hoops_RIHH */
							HI_Free_Material_Names (&_hoops_GGPRA, 1);
							return false;
						}

						HI_HLS_To_RGB ((_hoops_PACHR const *)&_hoops_GGPRA._hoops_CSHR,
									   &_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.color.rgb);

						HI_Free_Material_Names (&_hoops_GGPRA, 1);
					}
					HI_Copy_Name (&option->value._name[0],
									&_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.color.name);
				}
				else if (mask == _hoops_GRGAP) {
					_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS._hoops_IRIR = option->value._hoops_PIPCR[0];
					if (_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS._hoops_IRIR < 0.0f ||
						_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS._hoops_IRIR > 1.0f) {
						HE_WARNING (HEC_RENDERING, HES_INVALID_RANGE,
									"Simple shadow opacity may only be between 0 and 1");
						_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.value &= ~mask;
					}
				}
				else if (mask == _hoops_RRGAP) {
					_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS._hoops_HAP = option->value._hoops_RIARA[0];
					if (_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS._hoops_HAP < 32 ||
						_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS._hoops_HAP > 1024) {
						HE_WARNING (HEC_RENDERING, HES_INVALID_RANGE,
									"Simple shadow resolution may only be between 32 and 1024");
						_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.value &= ~mask;
					}
				}
				else if (mask == _hoops_ARGAP) {
					_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS._hoops_IGGGR = option->value._hoops_RIARA[0];
					if (_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS._hoops_IGGGR < 1 ||
						_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS._hoops_IGGGR > 32) {
						HE_WARNING (HEC_RENDERING, HES_INVALID_RANGE,
									"Simple shadow blurring may only be between 1 and 32");
						_hoops_APHCR->_hoops_HHAIR->_hoops_GHSS.value &= ~mask;
					}
				}
			}
		}
	} while ((option = option->next) != null);

	return true;
}

local bool _hoops_PRIRS (
	Option_Value *			option,
	_hoops_RHAIR *		_hoops_APHCR) {

	/* _hoops_CIS _hoops_APPP _hoops_PICP _hoops_IIGR (_hoops_HCSP == _hoops_IRAP) _hoops_AGIR */
	do {
		_hoops_RAGAP			mask;

		mask = (_hoops_RAGAP)option->type->id;

		if (mask == 0) {		/* _hoops_PSAP */
			_hoops_APHCR->_hoops_HHAIR->_hoops_HRR.mask |= _hoops_GAGAP;
			_hoops_APHCR->_hoops_HHAIR->_hoops_HRR.value &= ~_hoops_GAGAP;
		}
		else if (mask == -1) {	 /* _hoops_GRH _hoops_RIP _hoops_IH _hoops_SPRS */
			_hoops_APHCR->_hoops_HHAIR->_hoops_HRR.mask |= _hoops_GAGAP;
			_hoops_APHCR->_hoops_HHAIR->_hoops_HRR.value |= _hoops_GAGAP;
		}
		else {
			bool _hoops_GCACR = option->_hoops_GCACR;

			if (mask == _hoops_ASPRS) {
				/* _hoops_IRHH "_hoops_RAR _hoops_HRIRS" _hoops_PCCP _hoops_AGIRS _hoops_IIGR "_hoops_RAR _hoops_AIAGR" */
				mask = _hoops_IAGAP;
				_hoops_GCACR = !_hoops_GCACR;
			}

			_hoops_APHCR->_hoops_HHAIR->_hoops_HRR.mask |= mask;

			if (_hoops_GCACR) {
				_hoops_APHCR->_hoops_HHAIR->_hoops_HRR.value &= ~mask;
			}
			else {
				_hoops_APHCR->_hoops_HHAIR->_hoops_HRR.value |= mask;

				if (mask == _hoops_PAGAP) {
					_hoops_APHCR->_hoops_HHAIR->_hoops_HRR._hoops_HAP = option->value._hoops_RIARA[0];
					if (_hoops_APHCR->_hoops_HHAIR->_hoops_HRR._hoops_HAP < 512 ||
						_hoops_APHCR->_hoops_HHAIR->_hoops_HRR._hoops_HAP > 4096) {
						HE_WARNING (HEC_RENDERING, HES_INVALID_RANGE,
									"Shadow Map resolution may only be between 512 and 4096");
						_hoops_APHCR->_hoops_HHAIR->_hoops_HRR.value &= ~mask;
					}
				}
				if (mask == _hoops_HAGAP) {
					_hoops_APHCR->_hoops_HHAIR->_hoops_HRR._hoops_CAP = option->value._hoops_RIARA[0];
					if (_hoops_APHCR->_hoops_HHAIR->_hoops_HRR._hoops_CAP < 1 ||
						_hoops_APHCR->_hoops_HHAIR->_hoops_HRR._hoops_CAP > 16) {
						HE_WARNING (HEC_RENDERING, HES_INVALID_RANGE,
									"Shadow Map samples may only be between 1 and 16");
						_hoops_APHCR->_hoops_HHAIR->_hoops_HRR.value &= ~mask;
					}
				}
			}
		}
	} while ((option = option->next) != null);

	return true;
}


local bool _hoops_IRIRS (
	Option_Value *		option,
	float *				hither,
	float *				yon) {

	if (option != null) do switch (option->type->id) {
		case _hoops_RPPRS:
			*hither = option->value._hoops_PIPCR[0];
			break;

		case _hoops_APPRS:
			*yon = option->value._hoops_PIPCR[0];
			break;

		default:
			return false;
			_hoops_HHHI;
	} while ((option = option->next) != null);

	return true;
}


local bool _hoops_CRIRS (
	Option_Value *			option,
	_hoops_RHAIR *		_hoops_APHCR) {

	/* _hoops_CIS _hoops_APPP _hoops_PICP _hoops_IIGR (_hoops_HCSP == _hoops_IRAP) _hoops_AGIR */
	do {
		_hoops_SAGAP			mask;

		mask = (_hoops_SAGAP)option->type->id;

		if (mask == 0) {		/* _hoops_PSAP */
			_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR.mask |= _hoops_CAGAP;
			_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR.value &= ~_hoops_CAGAP;
		}
		else {
			_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR.mask |= mask;

			if (option->_hoops_GCACR)
				_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR.value &= ~mask;
			else
				_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR.value |= mask;

			if (mask == _hoops_GPGAP) {
				_hoops_AIGA (option->value._hoops_PIPCR, 4, float, &_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR.plane);

				if (!HI_Normalize_Plane (&_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR.plane)) {
					HE_WARNING (HEC_INTERNAL_ERROR, HES_SINGULAR_PLANE,
								"Bad simple reflection plane definition");
					_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR.value &= ~mask;
				}
			}
			else if (mask == _hoops_RPGAP) {
				_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR._hoops_IRIR = option->value._hoops_PIPCR[0];
				if (_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR._hoops_IRIR < 0.0f ||
					_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR._hoops_IRIR > 1.0f) {
					HE_WARNING (HEC_RENDERING, HES_INVALID_RANGE,
								"Simple reflection opacity may only be between 0 and 1");
					_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR.value &= ~mask;
				}
			}
			else if (mask == _hoops_HPGAP) {
				if (option->_hoops_GCACR)
					_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR._hoops_IGGGR = 0;
				else {
					_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR._hoops_IGGGR = option->value._hoops_RIARA[0];

					if (_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR._hoops_IGGGR < 1.0f ||
						_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR._hoops_IGGGR > 32.0f) {
						HE_WARNING (HEC_RENDERING, HES_INVALID_RANGE,
									"Simple reflection blur may only be between 1 and 32");
						_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR.value &= ~mask;
					}
				}
			}
			else if (mask == _hoops_PPGAP) {
				if (option->_hoops_GCACR)
					_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR.yon = _hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR.hither = 0;
				else if (!_hoops_IRIRS (
						option->value.option_list,
						&_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR.hither,
						&_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR.yon))
					return false;

				if (_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR.yon < _hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR.hither) {
					HE_WARNING (HEC_RENDERING, HES_INVALID_RANGE,
								"Simple reflection hither must be less than or equal to yon");
					return false;
				}
			}
			else if (mask == _hoops_IPGAP) {
				Option_Value *		_hoops_CHAGA;

				if (option->_hoops_GCACR) {
					_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.mask = 0;
					_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.value = 0;
				}
				else if ((_hoops_CHAGA = option->value.option_list) == null) {
					_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.mask = _hoops_CAHGP;
					_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.value = _hoops_CAHGP;
				}
				else do {
					_hoops_ACHR		_hoops_SSHRS;

					if ((_hoops_SSHRS = _hoops_CHAGA->type->id) != 0) {
						_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.mask |= _hoops_SSHRS;

						if (_hoops_CHAGA->_hoops_GCACR)
							_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.value &= ~_hoops_SSHRS;
						else
							_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.value |= _hoops_SSHRS;
					}
					else {
						_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.mask = _hoops_CAHGP;
						_hoops_APHCR->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.value = 0;
					}
				} while ((_hoops_CHAGA = _hoops_CHAGA->next) != null);
			}
		}
	} while ((option = option->next) != null);

	return true;
}

local bool _hoops_SRIRS (
	Option_Value *				option,
	_hoops_RHAIR *			_hoops_APHCR) {

	if (option == null) {
		_hoops_APHCR->_hoops_RGICA.mask = true;
		_hoops_APHCR->_hoops_RGICA.value = true;
	}
	else do {
		_hoops_PPAAP			mask;

		mask = (_hoops_PPAAP)option->type->id;
		_hoops_APHCR->_hoops_RGICA.mask |= mask;

		if (option->_hoops_GCACR) {
			_hoops_APHCR->_hoops_RGICA.value &= ~mask;
		}
		else {
			_hoops_APHCR->_hoops_RGICA.value |= mask;

			if (mask == _hoops_HPAAP) {
				if (option->value._hoops_RRRHA[0].value < 0) {
					HE_ERROR2 (HEC_RENDERING, HES_BAD_SIZE_LIMIT,
							   "The software frame buffer option 'size limit'",
							   "requires a non-negative value");
					return false;
				}
				_hoops_APHCR->_hoops_RGICA._hoops_SPAAP = (int)
					(option->value._hoops_RRRHA[0].value *
					 (float)option->value._hoops_RRRHA[0]._hoops_HHP);
			}
			else if (mask == _hoops_CPAAP) {
				_hoops_APHCR->_hoops_RGICA._hoops_GHAAP = (int)option->value.option_list->type->id;
			}
		}
	} while ((option = option->next) != null);

	return true;
}

local bool _hoops_GAIRS (
	Option_Value *			option,
	_hoops_RHAIR *		_hoops_APHCR) {

	if (option == null)
		return false;

	do switch (option->type->id) {
		case _hoops_RRAAP:
#ifdef _hoops_GCSIR
				_hoops_IRPPR("Software Z buffer");
				break;
#endif
		case _hoops_SGAAP:
		case _hoops_GRAAP:
		case _hoops_HSSS:
		case _hoops_GAI:
		case _hoops_PRAAP:
		case _hoops_SICI:
			_hoops_APHCR->_hoops_PSHCA	|= _hoops_SRRAP;
			_hoops_APHCR->_hoops_RRRAP |= _hoops_SRRAP;
			_hoops_APHCR->_hoops_SRI = option->type->id;
			break;


		case _hoops_HRAAP:
			_hoops_APHCR->_hoops_SCIAA	 |= _hoops_CSHCA;
			_hoops_APHCR->_hoops_RSIAA |= _hoops_CSHCA;
			_hoops_APHCR->_hoops_SSHCA.mask  |= _hoops_AAAAP;
			_hoops_APHCR->_hoops_SSHCA.value |= _hoops_AAAAP;
			if (option->_hoops_GCACR)
				_hoops_APHCR->_hoops_SSHCA._hoops_SRI = _hoops_CGAAP;
			else
				_hoops_APHCR->_hoops_SSHCA._hoops_SRI =
								   option->value.option_list->type->id;
			break;

		default:
			return false;
			_hoops_HHHI;
	} while ((option = option->next) != null);

	return true;
}

local bool _hoops_RAIRS (
	Option_Value *			option,
	_hoops_RHAIR *		_hoops_APHCR) {

	if (option == null)
		return false;

	do switch (option->type->id) {
		case _hoops_GPAAP:
		case _hoops_PAAAP:
			_hoops_APHCR->_hoops_SSHCA.mask |= option->type->id;
			if (option->_hoops_GCACR)
				_hoops_APHCR->_hoops_SSHCA.value &= ~(option->type->id);
			else
				_hoops_APHCR->_hoops_SSHCA.value |=  option->type->id;
			break;

		case _hoops_RAAAP:
			_hoops_APHCR->_hoops_SSHCA.mask  |= _hoops_RAAAP;
			_hoops_APHCR->_hoops_SSHCA.value |= _hoops_RAAAP;
			if (option->_hoops_GCACR)
				_hoops_APHCR->_hoops_SSHCA.style = _hoops_CGAAP;
			else
				_hoops_APHCR->_hoops_SSHCA.style = (char)(option->value.option_list->type->id);
			break;

		case _hoops_AAAAP:
			_hoops_APHCR->_hoops_SSHCA.mask  |= _hoops_AAAAP;
			_hoops_APHCR->_hoops_SSHCA.value |= _hoops_AAAAP;
			if (option->_hoops_GCACR)
				_hoops_APHCR->_hoops_SSHCA._hoops_SRI = _hoops_CGAAP;
			else
				_hoops_APHCR->_hoops_SSHCA._hoops_SRI =
								   option->value.option_list->type->id;
			break;

		case _hoops_CAAAP: {
			Option_Value			*_hoops_AHSAA = option->value.option_list;

			do switch (_hoops_AHSAA->type->id) {
				case _hoops_HAAAP: {
					_hoops_APHCR->_hoops_SSHCA.mask |= _hoops_HAAAP;
					_hoops_APHCR->_hoops_SSHCA._hoops_RPAAP = _hoops_AHSAA->value._hoops_RIARA[0];
				}	break;

				case _hoops_IAAAP: {
					_hoops_APHCR->_hoops_SSHCA.mask |= _hoops_IAAAP;
					if (_hoops_AHSAA->_hoops_GCACR)
						_hoops_APHCR->_hoops_SSHCA._hoops_APAAP = 0.0f;
					else
						_hoops_APHCR->_hoops_SSHCA._hoops_APAAP =
									_hoops_AHSAA->value._hoops_RRRHA[0].value *
									_hoops_AHSAA->value._hoops_RRRHA[0]._hoops_HHP;
				}	break;
			} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
		}	break;


		case _hoops_SAAAP: {
			Option_Value			*_hoops_AHSAA = option->value.option_list;

			_hoops_APHCR->_hoops_SSHCA.mask |= _hoops_SAAAP;
			do switch (_hoops_AHSAA->type->id) {
				case _hoops_RCARS: {
					_hoops_APHCR->_hoops_SSHCA.value |= _hoops_SAAAP;
				}	break;

				case _hoops_ACARS: {
					_hoops_APHCR->_hoops_SSHCA.value &= ~_hoops_SAAAP;
				}	break;
			} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
		}	break;

		default:
			return false;
			_hoops_HHHI;
	} while ((option = option->next) != null);

	return true;
}


local bool _hoops_AAIRS (
	Option_Value *			option,
	_hoops_RHAIR *		_hoops_APHCR) {

	if (option == null) {
		_hoops_APHCR->_hoops_CHP.mask  |= _hoops_GAAAP;
		_hoops_APHCR->_hoops_CHP.value |= _hoops_GAAAP;
		return true;
	}

	do switch (option->type->id) {
		case _hoops_IRAAP:
			_hoops_APHCR->_hoops_CHP.mask  = _hoops_GAAAP;
			_hoops_APHCR->_hoops_CHP.value = _hoops_IRAAP;
			break;

		case _hoops_SRAAP:
		case _hoops_SHP:
		case _hoops_CRAAP:
		case _hoops_GPSP:
			_hoops_APHCR->_hoops_CHP.mask  |= option->type->id;
			if (option->_hoops_GCACR)
				_hoops_APHCR->_hoops_CHP.value &= ~option->type->id;
			else
				_hoops_APHCR->_hoops_CHP.value |=  option->type->id;
			break;

		default:
			return false;
			_hoops_HHHI;
	} while ((option = option->next) != null);

	return true;
}


local bool _hoops_PAIRS (
	_hoops_AIGPR *	_hoops_RIGC,
	Option_Value *			option,
	_hoops_RHAIR *		_hoops_APHCR) {

	if (option != null) do {
		_hoops_GPCRP			mask;

		mask = (_hoops_GPCRP)option->type->id;
		_hoops_APHCR->_hoops_AIAIR->mask |= mask;

		if (option->_hoops_GCACR) {
			_hoops_APHCR->_hoops_AIAIR->value &= ~mask;
		}
		else {
			_hoops_APHCR->_hoops_AIAIR->value |= mask;

			if (mask == _hoops_RPCRP) {
				HI_Canonize_Line_Pattern(option->value._name->text, &_hoops_APHCR->_hoops_AIAIR->_hoops_PIAIR, 0);
				_hoops_HCARA(_hoops_APHCR->_hoops_AIAIR->_hoops_PIAIR,  _hoops_APHCR->_hoops_AIAIR->_hoops_HHCRP);
			}
			else if (mask == _hoops_GHCRP) {
				_hoops_APHCR->_hoops_AIAIR->weight.value = option->value._hoops_RRRHA[0].value;
				_hoops_APHCR->_hoops_AIAIR->weight._hoops_HHP = (_hoops_GIGRP)option->value._hoops_RRRHA[0]._hoops_HHP;
			}
			else if (mask == _hoops_APCRP) {
				_hoops_APHCR->_hoops_AIAIR->_hoops_IHCRP = option->value._hoops_PIPCR[0];
			}
			else if (mask == _hoops_PPCRP) {
				_hoops_APHCR->_hoops_AIAIR->_hoops_CHIH = option->value._hoops_PIPCR[0];
			}
			else if (mask == _hoops_PHCRP) {
				_hoops_APHCR->_hoops_AIAIR->_hoops_CHCRP = option->value._hoops_PIPCR[0];
			}
			else if (mask == _hoops_AHCRP) {
				_hoops_APHCR->_hoops_AIAIR->_hoops_SRI = option->value.option_list->type->id;
			}
			else if (mask == _hoops_SPCRP) {
				Named_Material			_hoops_GGPRA;

				ZERO_STRUCT(&_hoops_GGPRA, Named_Material);
				if (!HI_Evaluate_Color (_hoops_RIGC, &option->value._name[0], &_hoops_GGPRA, 0, false)) {
					/* (_hoops_RIHH _hoops_AIAH _hoops_CRPPR) */
					HI_Free_Material_Names (&_hoops_GGPRA, 1);
					return false;
				}

				/* _hoops_HGI _hoops_RRGR _hoops_IHCI _hoops_RH _hoops_APIR/_hoops_HH _hoops_IPPHR _hoops_SGS _hoops_CSAP
				** _hoops_CRPRA _hoops_GGSR _hoops_CRGR _hoops_SRPRA _hoops_IAPR _hoops_IS _hoops_RH _hoops_GCRRA _hoops_HRPR.
				*/
				if (ANYBIT (_hoops_GGPRA._hoops_PRGRA, ~(M_DIFFUSE|_hoops_RHGRA)) ||
					_hoops_GGPRA._hoops_SCA != null) {		/* _hoops_IRHH _hoops_SCH _hoops_IHGP */
					/* _hoops_RIHH */
					HI_Free_Material_Names (&_hoops_GGPRA, 1);
					return false;
				}

				HI_HLS_To_RGB ((_hoops_PACHR const *)&_hoops_GGPRA._hoops_CSHR, &_hoops_APHCR->_hoops_AIAIR->color);
				HI_Free_Material_Names (&_hoops_GGPRA, 1);
			}
		}

		_hoops_APHCR->_hoops_RSIAA |= _hoops_IGICA;
	} while ((option = option->next) != null);

	return true;
}

local bool _hoops_HAIRS (
	Option_Value *					option,
	_hoops_RHAIR *				_hoops_APHCR) {

	if (option != null) do {
		_hoops_GICRP		mask = (_hoops_GPCRP)option->type->id;

		_hoops_APHCR->_hoops_IIAIR->mask |= mask;

		if (option->_hoops_GCACR) {
			_hoops_APHCR->_hoops_IIAIR->value &= ~mask;

			if (mask == _hoops_RICRP) {
				_hoops_APHCR->_hoops_IIAIR->_hoops_RGP.mask |= T_FACES;
				_hoops_APHCR->_hoops_IIAIR->_hoops_RGP.value &= ~T_FACES;
			}
		}
		else {
			_hoops_APHCR->_hoops_IIAIR->value |= mask;

			if (mask == _hoops_AICRP) {
				Option_Value *		_hoops_AHSAA = option->value.option_list;

				if (_hoops_AHSAA == null) {
					_hoops_APHCR->_hoops_IIAIR->_hoops_CCCRP = _hoops_HCCRP;
				}
				else do {
					int				_hoops_PHSAA = _hoops_AHSAA->type->id;

					_hoops_APHCR->_hoops_IIAIR->_hoops_CCCRP = _hoops_PHSAA;
					// _hoops_HPCAR _hoops_HSSHH _hoops_HCCPR _hoops_SR _hoops_CGIC _hoops_IAII
					_hoops_APHCR->_hoops_IIAIR->scale = 1.0f;
					_hoops_APHCR->_hoops_IIAIR->translate = 0.0f;

					if (_hoops_PHSAA == _hoops_ICCRP) {
						Option_Value *		_hoops_IAIRS = _hoops_AHSAA->value.option_list;

						if (_hoops_IAIRS != null) do {
							if (_hoops_IAIRS->type->id == -1)
								_hoops_APHCR->_hoops_IIAIR->scale = _hoops_IAIRS->value._hoops_PIPCR[0];
							else
								_hoops_APHCR->_hoops_IIAIR->translate = _hoops_IAIRS->value._hoops_PIPCR[0];
						} while ((_hoops_IAIRS = _hoops_IAIRS->next) != null);
					}
				} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
			}
			else if (mask == _hoops_RICRP) {
				Option_Value *		_hoops_AHSAA = option->value.option_list;

				if (_hoops_AHSAA == null) {
					_hoops_APHCR->_hoops_IIAIR->_hoops_RGP.mask |= T_FACES;
					_hoops_APHCR->_hoops_IIAIR->_hoops_RGP.value |= T_FACES;
				}
				else do {
					_hoops_ACHR		_hoops_PHSAA = _hoops_AHSAA->type->id;

					_hoops_APHCR->_hoops_IIAIR->_hoops_RGP.mask |= T_FACES;
					if (_hoops_AHSAA->_hoops_GCACR || _hoops_PHSAA == 0)
						_hoops_APHCR->_hoops_IIAIR->_hoops_RGP.value &= ~T_FACES;
					else
						_hoops_APHCR->_hoops_IIAIR->_hoops_RGP.value |= T_FACES;
				} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
			}
		}

		_hoops_APHCR->_hoops_RSIAA |= _hoops_AGRAP;
	} while ((option = option->next) != null);

	return true;
}


local _hoops_SRHSR	_hoops_HGSH = _hoops_GRRCR("*");
local _hoops_SRHSR	_hoops_PGHHP = _hoops_GRRCR("-");


local bool _hoops_CAIRS (
	_hoops_AIGPR *			_hoops_RIGC,
	Option_Value *					option,
	_hoops_RHAIR *				_hoops_APHCR) {

	if (option != null) do {
		_hoops_GICRP		mask;

		mask = (_hoops_GICRP)option->type->id;
		_hoops_APHCR->_hoops_IIAIR->mask |= mask;

		if (option->_hoops_GCACR) {
			_hoops_APHCR->_hoops_IIAIR->value &= ~mask;
			if (mask == _hoops_HICRP) {
				_hoops_APHCR->_hoops_IIAIR->_hoops_RGP.mask |= T_EDGES;
				_hoops_APHCR->_hoops_IIAIR->_hoops_RGP.value &= ~T_EDGES;
			}
		}
		else {
			_hoops_APHCR->_hoops_IIAIR->value |= mask;

			if (mask == _hoops_IICRP) {
				Option_Value *		_hoops_AHSAA = option->value.option_list;
				int					count = _hoops_AHSAA->_hoops_AIPCR;

				if (_hoops_AHSAA->type->id == _hoops_GSCRP) {
					_hoops_APHCR->_hoops_IIAIR->_hoops_RSCRP = _hoops_GSCRP;
					if ((_hoops_APHCR->_hoops_IIAIR->_hoops_CIAIR = count) > 0) {
						ALLOC_ARRAY (_hoops_APHCR->_hoops_IIAIR->_hoops_SIAIR, count, float);

						for (int i=0; i<count; i++) {
							_hoops_APHCR->_hoops_IIAIR->_hoops_SIAIR[i] = _hoops_AHSAA->value._hoops_PIPCR[i];

							if (i > 0 && _hoops_APHCR->_hoops_IIAIR->_hoops_SIAIR[i] <= _hoops_APHCR->_hoops_IIAIR->_hoops_SIAIR[i-1]) {
								HE_WARNING (HEC_RENDERING, HES_INVALID_OFFSET,
											"Explicit positions must be increasing values; positions ignored.");

								FREE_ARRAY (_hoops_APHCR->_hoops_IIAIR->_hoops_SIAIR, count, float);
								_hoops_APHCR->_hoops_IIAIR->_hoops_SIAIR = null;
								_hoops_APHCR->_hoops_IIAIR->_hoops_CIAIR = 0;
								_hoops_APHCR->_hoops_IIAIR->mask  &= ~_hoops_IICRP;
								_hoops_APHCR->_hoops_IIAIR->value &= ~_hoops_IICRP;
								break;
							}
						}
					}
				}
				else {
					_hoops_APHCR->_hoops_IIAIR->_hoops_RSCRP = _hoops_SCCRP;
					_hoops_APHCR->_hoops_IIAIR->_hoops_CIAIR = 2;
					ALLOC_ARRAY (_hoops_APHCR->_hoops_IIAIR->_hoops_SIAIR, 2, float);
					_hoops_APHCR->_hoops_IIAIR->_hoops_SIAIR[0] = 1.0f;	// _hoops_SGAHP
					_hoops_APHCR->_hoops_IIAIR->_hoops_SIAIR[1] = 0.0f;	// _hoops_SHI

					if (_hoops_AHSAA->value.option_list != null) {
						Option_Value *		_hoops_IAIRS =  _hoops_AHSAA->value.option_list;

						do {
							if (_hoops_IAIRS->type->id == -1) {				// _hoops_SGAHP
								_hoops_APHCR->_hoops_IIAIR->_hoops_SIAIR[0] = _hoops_IAIRS->value._hoops_PIPCR[0];

								if (_hoops_APHCR->_hoops_IIAIR->_hoops_SIAIR[0] <= 0.0f) {
									HE_WARNING (HEC_RENDERING, HES_INVALID_INTERVAL,
												"Repeating position interval must be positive; position setting ignored.");

									FREE_ARRAY (_hoops_APHCR->_hoops_IIAIR->_hoops_SIAIR, 2, float);
									_hoops_APHCR->_hoops_IIAIR->_hoops_SIAIR = null;
									_hoops_APHCR->_hoops_IIAIR->_hoops_CIAIR = 0;
									_hoops_APHCR->_hoops_IIAIR->mask  &= ~_hoops_IICRP;
									_hoops_APHCR->_hoops_IIAIR->value &= ~_hoops_IICRP;
								}
							}
							else									// _hoops_SHI
								_hoops_APHCR->_hoops_IIAIR->_hoops_SIAIR[1] = _hoops_IAIRS->value._hoops_PIPCR[0];
						} while ((_hoops_IAIRS = _hoops_IAIRS->next) != null);
					}
				}
			}
			else if (mask == _hoops_CICRP) {
				if ((_hoops_APHCR->_hoops_IIAIR->_hoops_GCAIR = option->_hoops_AIPCR) > 0) {
					ALLOC_ARRAY (_hoops_APHCR->_hoops_IIAIR->colors, _hoops_APHCR->_hoops_IIAIR->_hoops_GCAIR, RGB);

					for (int i=0; i<_hoops_APHCR->_hoops_IIAIR->_hoops_GCAIR; i++) {
						if (_hoops_RAHSR (option->value._name[i], _hoops_HGSH)) {
							_hoops_APHCR->_hoops_IIAIR->colors[i] = _hoops_GPSR::_hoops_RPSR;
							_hoops_APHCR->_hoops_IIAIR->colors[i].red = -1.0f;	// _hoops_CAPGP
						}
						else if (_hoops_RAHSR (option->value._name[i], _hoops_PGHHP)) {
							_hoops_APHCR->_hoops_IIAIR->colors[i] = _hoops_GPSR::_hoops_RPSR;
							_hoops_APHCR->_hoops_IIAIR->colors[i].red = -2.0f;	// _hoops_ACIAR
						}
						else {
							Named_Material			_hoops_GGPRA;

							ZERO_STRUCT (&_hoops_GGPRA, Named_Material);
							if (!HI_Evaluate_Color (_hoops_RIGC, &option->value._name[i], &_hoops_GGPRA, 0, false)) {
								/* (_hoops_RIHH _hoops_AIAH _hoops_CRPPR) */
								HI_Free_Material_Names (&_hoops_GGPRA, 1);
								return false;
							}

							/* _hoops_HGI _hoops_RRGR _hoops_IHCI _hoops_RH _hoops_APIR/_hoops_HH _hoops_IPPHR _hoops_SGS _hoops_CSAP
							** _hoops_CRPRA _hoops_GGSR _hoops_CRGR _hoops_SRPRA _hoops_IAPR _hoops_IS _hoops_RH _hoops_GCRRA _hoops_HRPR.
							*/
							if (ANYBIT (_hoops_GGPRA._hoops_PRGRA, ~(M_DIFFUSE|_hoops_RHGRA)) ||
								_hoops_GGPRA._hoops_SCA != null) {		/* _hoops_IRHH _hoops_SCH _hoops_IHGP */
								/* _hoops_RIHH */
								HI_Free_Material_Names (&_hoops_GGPRA, 1);
								return false;
							}

							HI_HLS_To_RGB ((_hoops_PACHR const *)&_hoops_GGPRA._hoops_CSHR, &_hoops_APHCR->_hoops_IIAIR->colors[i]);
							HI_Free_Material_Names (&_hoops_GGPRA, 1);
						}
					}
				}
			}
			else if (mask == _hoops_SICRP) {
				if ((_hoops_APHCR->_hoops_IIAIR->_hoops_RCAIR = option->_hoops_AIPCR) > 0) {
					ALLOC_ARRAY (_hoops_APHCR->_hoops_IIAIR->_hoops_ACAIR, _hoops_APHCR->_hoops_IIAIR->_hoops_RCAIR, _hoops_HCRPR);
					ALLOC_ARRAY (_hoops_APHCR->_hoops_IIAIR->_hoops_PCAIR, _hoops_APHCR->_hoops_IIAIR->_hoops_RCAIR, Integer32);

					for (int i=0; i<_hoops_APHCR->_hoops_IIAIR->_hoops_RCAIR; i++) {
						HI_Canonize_Line_Pattern (option->value._name[i].text,
												  &_hoops_APHCR->_hoops_IIAIR->_hoops_ACAIR[i], 0);
						if (_hoops_RAHSR (_hoops_APHCR->_hoops_IIAIR->_hoops_ACAIR[i], _hoops_HGSH))
							_hoops_RGAIR (_hoops_APHCR->_hoops_IIAIR->_hoops_ACAIR[i]);
						_hoops_HCARA(_hoops_APHCR->_hoops_IIAIR->_hoops_ACAIR[i],
								_hoops_APHCR->_hoops_IIAIR->_hoops_PCAIR[i]);
					}
				}
			}
			else if (mask == _hoops_GCCRP) {
				if ((_hoops_APHCR->_hoops_IIAIR->weight_count = option->_hoops_AIPCR) > 0) {
					ALLOC_ARRAY (_hoops_APHCR->_hoops_IIAIR->weights, _hoops_APHCR->_hoops_IIAIR->weight_count, _hoops_HCAIR);

					for (int i=0; i<_hoops_APHCR->_hoops_IIAIR->weight_count; i++) {
						_hoops_APHCR->_hoops_IIAIR->weights[i].value = option->value._hoops_RRRHA[i].value;
						_hoops_APHCR->_hoops_IIAIR->weights[i]._hoops_HHP =
												(_hoops_GIGRP)option->value._hoops_RRRHA[i]._hoops_HHP;
					}
				}
			}
			else if (mask == _hoops_HICRP) {
				Option_Value *		_hoops_AHSAA = option->value.option_list;

				if (_hoops_AHSAA == null) {
					_hoops_APHCR->_hoops_IIAIR->_hoops_RGP.mask |= T_EDGES;
					_hoops_APHCR->_hoops_IIAIR->_hoops_RGP.value |= T_EDGES;
				}
				else do {
					_hoops_ACHR		_hoops_PHSAA = _hoops_AHSAA->type->id;

					_hoops_APHCR->_hoops_IIAIR->_hoops_RGP.mask |= _hoops_PHSAA;
					if (_hoops_AHSAA->_hoops_GCACR)
						_hoops_APHCR->_hoops_IIAIR->_hoops_RGP.value &= ~_hoops_PHSAA;
					else
						_hoops_APHCR->_hoops_IIAIR->_hoops_RGP.value |= _hoops_PHSAA;
				} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
			}
		}

		_hoops_APHCR->_hoops_RSIAA |= _hoops_PRICA;
	} while ((option = option->next) != null);

	return true;
}

local bool _hoops_SAIRS (
	_hoops_AIGPR *			_hoops_RIGC,
	Option_Value *					option,
	_hoops_RHAIR *				_hoops_APHCR) {

	_hoops_APHCR->_hoops_RSIAA |= _hoops_PGRAP;

	if (option == null) {
		_hoops_APHCR->_hoops_SHAAP |= _hoops_CHRH;
		_hoops_APHCR->_hoops_GIAAP |= _hoops_CHRH;
	}
	else do {
		int		mask = option->type->id;

		_hoops_APHCR->_hoops_SHAAP |= mask;

		if (mask == 0) {
			_hoops_APHCR->_hoops_SHAAP |= _hoops_CHRH;
			_hoops_APHCR->_hoops_GIAAP &= ~_hoops_CHRH;
		}
		else if (option->_hoops_GCACR) {
			_hoops_APHCR->_hoops_GIAAP &= ~mask;
		}
		else {
			_hoops_APHCR->_hoops_GIAAP |= mask;

			if (mask == _hoops_HIGRP) {
				_hoops_APHCR->_hoops_IHRH._hoops_ACGRP = option->value.option_list->type->id;
			}
			else if (mask == _hoops_AIGRP) {
				float		min = option->value._hoops_PIPCR[0];
				float		max = option->value._hoops_PIPCR[1];

				_hoops_APHCR->_hoops_IHRH.scale = max - min;
				_hoops_APHCR->_hoops_IHRH.translate = min;
			}
			else if (mask == _hoops_PIGRP) {
				Named_Material			_hoops_GGPRA;

				ZERO_STRUCT (&_hoops_GGPRA, Named_Material);
				if (!HI_Evaluate_Color (_hoops_RIGC, &option->value._name[0], &_hoops_GGPRA, 0, false)) {
					/* (_hoops_RIHH _hoops_AIAH _hoops_CRPPR) */
					HI_Free_Material_Names (&_hoops_GGPRA, 1);
					return false;
				}

				/* _hoops_HGI _hoops_RRGR _hoops_IHCI _hoops_RH _hoops_APIR/_hoops_HH _hoops_IPPHR _hoops_SGS _hoops_CSAP
				** _hoops_CRPRA _hoops_GGSR _hoops_CRGR _hoops_SRPRA _hoops_IAPR _hoops_IS _hoops_RH _hoops_GCRRA _hoops_HRPR.
				*/
				if (ANYBIT (_hoops_GGPRA._hoops_PRGRA, ~(M_DIFFUSE|_hoops_RHGRA)) ||
					_hoops_GGPRA._hoops_SCA != null) {		/* _hoops_IRHH _hoops_SCH _hoops_IHGP */
					/* _hoops_RIHH */
					HI_Free_Material_Names (&_hoops_GGPRA, 1);
					return false;
				}

				HI_HLS_To_RGB ((_hoops_PACHR const *)&_hoops_GGPRA._hoops_CSHR, &_hoops_APHCR->_hoops_IHRH.color);
				HI_Free_Material_Names (&_hoops_GGPRA, 1);
			}
		}
	} while ((option = option->next) != null);

	return true;
}


local bool _hoops_GPIRS (
	Option_Value *			option,
	_hoops_RHAIR *		_hoops_APHCR) {

	if (option != null) do {
		_hoops_CCSRP			mask;

		mask = (_hoops_CCSRP) option->type->id;
		_hoops_APHCR->_hoops_HHAIR->_hoops_IHAIR.mask |= mask;

		if (option->_hoops_GCACR) {
			_hoops_APHCR->_hoops_HHAIR->_hoops_IHAIR.value &= ~mask;
			if (mask == _hoops_SCSRP)
				_hoops_APHCR->_hoops_HHAIR->_hoops_IHAIR._hoops_GRCR = 0;
		}
		else {
			_hoops_APHCR->_hoops_HHAIR->_hoops_IHAIR.value |= mask;
			if (mask == _hoops_SCSRP) {
				_hoops_APHCR->_hoops_HHAIR->_hoops_IHAIR._hoops_GRCR = option->value._hoops_PIPCR[0];
			}
			else if (mask == _hoops_ICSRP) {
				_hoops_APHCR->_hoops_HHAIR->_hoops_IHAIR._hoops_HCIR[0] = option->value._hoops_PIPCR[0];
				_hoops_APHCR->_hoops_HHAIR->_hoops_IHAIR._hoops_HCIR[1] = option->value._hoops_PIPCR[1];
			}
			else if (mask == _hoops_GSSRP) {
				HI_Copy_Name (option->value._name, &_hoops_APHCR->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR);
			}
		}

		_hoops_APHCR->_hoops_RSIAA |= _hoops_GGRAP;
	} while ((option = option->next) != null);

	return true;
}


local bool _hoops_RPIRS (
	Option_Value *			option,
	_hoops_RHAIR *		_hoops_APHCR)
{
	int						i, j;

	/* _hoops_GASA: _hoops_RHRIR... _hoops_HHH _hoops_IIGR _hoops_AGCR _hoops_ARAR _hoops_HS _hoops_APIRS _hoops_GGR _hoops_PPIRS._hoops_GSGGR:_hoops_HPIRS()
		_hoops_SGS _hoops_GACC _hoops_RRP _hoops_IS _hoops_SHH _hoops_GCPRA _hoops_GH _hoops_IS _hoops_ICGIP */
	if (option != null) do {
		_hoops_RRPHA			mask;

		mask = (_hoops_RRPHA) option->type->id;
		_hoops_APHCR->_hoops_PRSI->mask |= mask;

		if (option->_hoops_GCACR) {
			_hoops_APHCR->_hoops_PRSI->value &= ~mask;
			if (mask == _hoops_CSCRP)
				_hoops_APHCR->_hoops_PRSI->_hoops_HISRP = 0;
			else if (mask == _hoops_AGSRP)
				_hoops_APHCR->_hoops_PRSI->tolerance = 0;
			else if (mask == _hoops_GRSRP)
				_hoops_APHCR->_hoops_PRSI->_hoops_SRHHR = 0;
			else if (mask == _hoops_IRSRP)
				for (i = 0; i < _hoops_IGAIR; i++)
					_hoops_APHCR->_hoops_PRSI->_hoops_GHRGR[i] = 0;
			else if (mask == _hoops_PASRP)
				_hoops_APHCR->_hoops_PRSI->_hoops_RCSRP = _hoops_SPSRP;
		}
		else {
			_hoops_APHCR->_hoops_PRSI->value |= mask;
			if (mask == _hoops_ISCRP) {
				for (i = 0; i < option->_hoops_AIPCR; i++)
					_hoops_APHCR->_hoops_PRSI->_hoops_PRPHA[i] = option->value._hoops_PIPCR[i];
				for (j = i; j < _hoops_IGAIR; j++)
					_hoops_APHCR->_hoops_PRSI->_hoops_PRPHA[j] = _hoops_APHCR->_hoops_PRSI->_hoops_PRPHA[i-1];
			}
			else if (mask == _hoops_IRSRP) {
				for (i = 0; i < option->_hoops_AIPCR; i++)
					_hoops_APHCR->_hoops_PRSI->_hoops_GHRGR[i] = option->value._hoops_PIPCR[i];
				for (j = i; j < _hoops_IGAIR; j++)
					_hoops_APHCR->_hoops_PRSI->_hoops_GHRGR[j] = _hoops_APHCR->_hoops_PRSI->_hoops_GHRGR[i-1];
			}
			else if (mask == _hoops_IASRP) {
				int _hoops_IPIRS = _hoops_AASRP;
				for (i = 0; i < option->_hoops_AIPCR; i++) {
					_hoops_APHCR->_hoops_PRSI->_hoops_AISRP[i] =
						option->value._hoops_RRRHA[i].value;
					if (_hoops_IPIRS == _hoops_AASRP)
						_hoops_IPIRS = option->value._hoops_RRRHA[i]._hoops_HHP;
				}
				for (j = i; j < _hoops_IGAIR; j++)
					_hoops_APHCR->_hoops_PRSI->_hoops_AISRP[j] = _hoops_APHCR->_hoops_PRSI->_hoops_AISRP[i-1];
				_hoops_APHCR->_hoops_PRSI->value |= _hoops_IPIRS;
				_hoops_APHCR->_hoops_PRSI->mask |= _hoops_IPIRS;
			}
			else if (mask == _hoops_AGSRP) {
				_hoops_APHCR->_hoops_PRSI->tolerance =
					option->value._hoops_RRRHA[0].value;

				_hoops_APHCR->_hoops_PRSI->value |= _hoops_PSCRP;
				if (option->value._hoops_RRRHA[0]._hoops_HHP == _hoops_PSCRP) {
					_hoops_APHCR->_hoops_PRSI->value |= _hoops_PSCRP;
				}
				else
					_hoops_APHCR->_hoops_PRSI->value &= ~_hoops_PSCRP;
			}
			else if (mask == _hoops_CSCRP) {
				_hoops_APHCR->_hoops_PRSI->_hoops_HISRP = option->value._hoops_RIARA[0];
			}
			else if (mask == _hoops_HASRP) {
				int _hoops_HAGR = option->value._hoops_RIARA[0];
				if (_hoops_HAGR < 0)
					_hoops_APHCR->_hoops_PRSI->value &= ~_hoops_HASRP;
				_hoops_APHCR->_hoops_PRSI->_hoops_IISRP = _hoops_HAGR;
			}
			else if (mask == _hoops_SSCRP) {
				if (option->value._hoops_RIARA[0] > _hoops_IGAIR) {
					HE_ERROR (HEC_RENDERING, HES_INVALID_COUNT,
								"Number of LOD levels exceeds maximum supported");
					return false;
				}
				_hoops_APHCR->_hoops_PRSI->_hoops_IRSH = option->value._hoops_RIARA[0];
			}
			else if (mask == _hoops_IGSRP) {
				_hoops_RRPHA _hoops_PHSAA = option->value.option_list->type->id;
				_hoops_APHCR->_hoops_PRSI->_hoops_ARPHA = _hoops_PHSAA;
			}
			else if (mask == _hoops_GGSRP) {
				_hoops_APHCR->_hoops_PRSI->_hoops_RHPHA = option->value._hoops_RIARA[0];
			}
			else if (mask == _hoops_GRSRP) {
				_hoops_RRPHA _hoops_PHSAA = option->value.option_list->type->id;
				_hoops_APHCR->_hoops_PRSI->_hoops_SRHHR = _hoops_PHSAA;
			}
			else if (mask == _hoops_RRSRP) {
				_hoops_RRPHA _hoops_PHSAA = option->value.option_list->type->id;
				_hoops_APHCR->_hoops_PRSI->mask |= _hoops_HRSRP;
				_hoops_APHCR->_hoops_PRSI->value &= ~(_hoops_HRSRP);
				if (!option->_hoops_GCACR) {
					if (_hoops_PHSAA == _hoops_ARSRP) {
						_hoops_APHCR->_hoops_PRSI->value |= _hoops_ARSRP;
					}
					else {
						Point pts[2];
						_hoops_APHCR->_hoops_PRSI->value |= _hoops_PRSRP;
						pts[0].x = option->value._hoops_PIPCR[0];
						pts[0].y = option->value._hoops_PIPCR[1];
						pts[0].z = option->value._hoops_PIPCR[2];
						pts[1].x = option->value._hoops_PIPCR[3];
						pts[1].y = option->value._hoops_PIPCR[4];
						pts[1].z = option->value._hoops_PIPCR[5];
						_hoops_APHCR->_hoops_PRSI->bounding.Merge (2, pts);
					}
				}
			}
			else if (mask == _hoops_PASRP) {
				_hoops_RRPHA _hoops_PHSAA = option->value.option_list->type->id;

				_hoops_APHCR->_hoops_PRSI->_hoops_RCSRP = _hoops_PHSAA;
			}
		}

		_hoops_APHCR->_hoops_RSIAA |= _hoops_SGICA;
	} while ((option = option->next) != null);

	return true;
}


local bool _hoops_CPIRS (
	Option_Value *			option,
	_hoops_GHGI				_hoops_SPIRS,
	_hoops_RHAIR *		_hoops_APHCR) {

	if (option == null) {
		_hoops_APHCR->_hoops_ISHCA  |= _hoops_SPIRS;
		_hoops_APHCR->_hoops_GHRAP &= ~_hoops_SPIRS;
		_hoops_APHCR->_hoops_GHRAP |= _hoops_CPPRS & _hoops_SPIRS;
	}
	else do {
		_hoops_GHGI			mask;

		mask = option->type->id & _hoops_SPIRS;
		if (!mask) {
			option->_hoops_GCACR = true;
			mask = _hoops_SPIRS;
		}

		if (mask == (_hoops_GCP|_hoops_SSA) ||
			mask == (_hoops_RCP|_hoops_GGP) ||
			mask == (_hoops_HIRAP|_hoops_IIRAP)) {
			_hoops_APHCR->_hoops_ISHCA |= _hoops_CIRAP;
			_hoops_APHCR->_hoops_GHRAP &= ~(_hoops_CIRAP);
			_hoops_APHCR->_hoops_GHRAP |= mask;
		}
		else if (mask == (_hoops_GCP|_hoops_RCP|_hoops_HIRAP) ||
			mask == (_hoops_SSA|_hoops_GGP|_hoops_IIRAP)) {
			/* _hoops_RGR _hoops_CGH _hoops_SHH _hoops_AIARR _hoops_RGAR _hoops_GPP _hoops_RH _hoops_SRS _hoops_GHIR _hoops_RHIR */

			_hoops_APHCR->_hoops_GHRAP &= ~mask;
			_hoops_APHCR->_hoops_ISHCA |= mask;

			if (!option->_hoops_GCACR)
				if (!_hoops_CPIRS (option->value.option_list, mask, _hoops_APHCR))
					return false;
		}
		else {
			_hoops_APHCR->_hoops_ISHCA |= mask;
			if (option->_hoops_GCACR)
				_hoops_APHCR->_hoops_GHRAP &= ~mask;
			else
				_hoops_APHCR->_hoops_GHRAP |= mask;
		}
	} while ((option = option->next) != null);

	return true;
}



local bool _hoops_GHIRS (
	Option_Value *			option,
	_hoops_GHGI				_hoops_SPIRS,
	_hoops_RHAIR *		_hoops_APHCR) {

	if (option == null) {
		_hoops_APHCR->_hoops_ISHCA  |= _hoops_SPIRS;
		_hoops_APHCR->_hoops_GHRAP |= _hoops_SPIRS;

		if (BIT (_hoops_SPIRS, (_hoops_PHGI & ~_hoops_AHGI)) &&
			!BIT (_hoops_SPIRS, (_hoops_IHRAP & ~_hoops_AHGI))) {
			_hoops_APHCR->_hoops_ISHCA  |= _hoops_IHRAP;
			_hoops_APHCR->_hoops_GHRAP &= ~_hoops_IHRAP;
		}
	}
	else do {
		_hoops_GHGI			mask = option->type->id;

		if (mask == _hoops_IHRAP) {
			/* _hoops_CGH _hoops_RGAR _hoops_IHPS _hoops_CCA _hoops_RHIRS */
			mask |= _hoops_PHGI;

			_hoops_APHCR->_hoops_SCIAA |= _hoops_AGRAP | _hoops_PRICA;
			_hoops_APHCR->_hoops_RSIAA |= _hoops_AGRAP | _hoops_PRICA;

			if (_hoops_APHCR->_hoops_IIAIR == null)
				ZALLOC (_hoops_APHCR->_hoops_IIAIR, _hoops_ICAIR);

			// _hoops_CCAH _hoops_HRP _hoops_SGS _hoops_ACHRS _hoops_RHGS _hoops_RGSR
			_hoops_APHCR->_hoops_IIAIR->mask = _hoops_PCHRS;
			_hoops_APHCR->_hoops_IIAIR->value = _hoops_HCHRS;
			_hoops_APHCR->_hoops_IIAIR->_hoops_RGP.mask = _hoops_ICHRS;
			_hoops_APHCR->_hoops_IIAIR->_hoops_RGP.value = _hoops_CCHRS;
		}
		else {
			mask &= _hoops_SPIRS & ~_hoops_AHGI;
			if (!mask) {
				/* _hoops_HSII "_hoops_SAAP=_hoops_PSAP" _hoops_GAR _hoops_RPP _hoops_SCH _hoops_RIAGR _hoops_RPII "_hoops_PSP _hoops_SAAP" */
				option->_hoops_GCACR = true;
				mask = _hoops_SPIRS;
			}
		}

		_hoops_APHCR->_hoops_ISHCA |= mask;
		if (option->_hoops_GCACR)
			_hoops_APHCR->_hoops_GHRAP &= ~mask;
		else
			_hoops_APHCR->_hoops_GHRAP |= mask;

		if (BIT (mask, (_hoops_PHGI & ~_hoops_AHGI)) &&
			!BIT (mask, (_hoops_IHRAP & ~_hoops_AHGI))) {
			_hoops_APHCR->_hoops_ISHCA  |= _hoops_IHRAP;
			_hoops_APHCR->_hoops_GHRAP &= ~_hoops_IHRAP;
		}
	} while ((option = option->next) != null);

	return true;
}


local void _hoops_AHIRS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_RHAIR &		_hoops_APHCR)
{
	UNREFERENCED(_hoops_RIGC);

	if (_hoops_APHCR._hoops_PSHRP != null) {
		FREE (_hoops_APHCR._hoops_PSHRP, _hoops_SCGAP);
	}

	if (_hoops_APHCR._hoops_PRSI != null) {
		_hoops_APHCR._hoops_PRSI->bounding.release();
		FREE (_hoops_APHCR._hoops_PRSI, _hoops_PHAIR);
	}

	if (_hoops_APHCR.locks != null) {
		FREE (_hoops_APHCR.locks, _hoops_CCAIR);
	}

	if (_hoops_APHCR._hoops_AIAIR != null) {
		_hoops_RGAIR (_hoops_APHCR._hoops_AIAIR->_hoops_PIAIR);
		FREE (_hoops_APHCR._hoops_AIAIR, _hoops_HIAIR);
	}

	if (_hoops_APHCR._hoops_HHAIR != null) {
		_hoops_RGAIR (_hoops_APHCR._hoops_HHAIR->_hoops_GHSS.color.name);
		_hoops_RGAIR (_hoops_APHCR._hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR);
		FREE (_hoops_APHCR._hoops_HHAIR, _hoops_RIAIR);
	}

	if (_hoops_APHCR.geometry != null) {
		FREE (_hoops_APHCR.geometry, _hoops_SCAIR);
	}

	if (_hoops_APHCR._hoops_IIAIR != null) {
		if (_hoops_APHCR._hoops_IIAIR->_hoops_CIAIR != 0) {
			FREE_ARRAY (_hoops_APHCR._hoops_IIAIR->_hoops_SIAIR, _hoops_APHCR._hoops_IIAIR->_hoops_CIAIR, float);
		}

		if (_hoops_APHCR._hoops_IIAIR->_hoops_GCAIR != 0) {
			FREE_ARRAY (_hoops_APHCR._hoops_IIAIR->colors, _hoops_APHCR._hoops_IIAIR->_hoops_GCAIR, RGB);
		}

		if (_hoops_APHCR._hoops_IIAIR->_hoops_RCAIR != 0) {
			for (int i=0; i<_hoops_APHCR._hoops_IIAIR->_hoops_RCAIR; i++)
				_hoops_RGAIR (_hoops_APHCR._hoops_IIAIR->_hoops_ACAIR[i]);

			FREE_ARRAY (_hoops_APHCR._hoops_IIAIR->_hoops_ACAIR, _hoops_APHCR._hoops_IIAIR->_hoops_RCAIR, _hoops_HCRPR);

			FREE_ARRAY (_hoops_APHCR._hoops_IIAIR->_hoops_PCAIR,
				_hoops_APHCR._hoops_IIAIR->_hoops_RCAIR, Integer32);
		}

		if (_hoops_APHCR._hoops_IIAIR->weight_count != 0) {
			FREE_ARRAY (_hoops_APHCR._hoops_IIAIR->weights, _hoops_APHCR._hoops_IIAIR->weight_count, _hoops_HCAIR);
		}

		FREE (_hoops_APHCR._hoops_IIAIR, _hoops_ICAIR);
	}
}

local void _hoops_PHIRS(_hoops_RHAIR & _hoops_APHCR)
{
	ZALLOC (_hoops_APHCR._hoops_PRSI, _hoops_PHAIR);
	for (int i = 0; i < _hoops_IGAIR; i++) {
		_hoops_APHCR._hoops_PRSI->_hoops_PRPHA[i] = 0.5f;
		_hoops_APHCR._hoops_PRSI->_hoops_AISRP[i] = 30.0f;
		_hoops_APHCR._hoops_PRSI->_hoops_GHRGR[i] = 0.0f;
	}
	_hoops_APHCR._hoops_PRSI->_hoops_IISRP = -1;
	_hoops_APHCR._hoops_PRSI->_hoops_HISRP = 25;
	_hoops_APHCR._hoops_PRSI->_hoops_IRSH = 2;
	_hoops_APHCR._hoops_PRSI->_hoops_RHPHA = 15;
	_hoops_APHCR._hoops_PRSI->tolerance = 0.0f;
	_hoops_APHCR._hoops_PRSI->_hoops_SRHHR = _hoops_PPSRP;
	_hoops_APHCR._hoops_PRSI->_hoops_RCSRP = _hoops_AHSRP;
	_hoops_APHCR._hoops_PRSI->_hoops_ARPHA = _hoops_SHSRP;
}

local bool _hoops_HHIRS (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			list,
	_hoops_RHAIR &		_hoops_APHCR)
{
	ZERO_STRUCT (&_hoops_APHCR, _hoops_RHAIR);

	_hoops_HIACR (_hoops_HAPPP, _hoops_RCHRS);

	Option_Value *	option_list;
	if (!HI_Parse_Options (_hoops_RIGC, list, _hoops_CIACR (_hoops_HAPPP), &option_list, _hoops_SIACR))
		return false;

	Option_Value *	option;

	if ((option = option_list) != null) do {
		_hoops_GHGI			mask = option->type->id;

		if (mask == _hoops_SIHRS) {
			if (_hoops_APHCR._hoops_PSHRP == null)
				ZALLOC (_hoops_APHCR._hoops_PSHRP, _hoops_SCGAP);
			_hoops_APHCR._hoops_PSHRP->clear = option->value._hoops_RIARA[0];
		}
		else if (mask == _hoops_GCHRS) {
			if (_hoops_APHCR._hoops_PSHRP == null)
				ZALLOC (_hoops_APHCR._hoops_PSHRP, _hoops_SCGAP);
			_hoops_APHCR._hoops_PSHRP->set = option->value._hoops_RIARA[0];
		}
		else if ((mask & _hoops_AHGI) == _hoops_PSGAP) {
			if (mask == _hoops_CIRAP) {
				if (option->_hoops_GCACR) {
					_hoops_APHCR._hoops_ISHCA |= mask;
					_hoops_APHCR._hoops_GHRAP &= ~mask;
				}
				else if (!_hoops_CPIRS (option->value.option_list, _hoops_CIRAP, &_hoops_APHCR)) {
					goto Failed;
				}
			}
			else if (mask == _hoops_SHRAP ||
					 mask == _hoops_AHRAP ||
					 mask == _hoops_HHRAP) {
				if (option->_hoops_GCACR) {
					_hoops_APHCR._hoops_ISHCA |= mask;
					_hoops_APHCR._hoops_GHRAP &= ~mask;

					if (mask == _hoops_HHRAP) {
						_hoops_APHCR._hoops_ISHCA |= _hoops_IHRAP;

						if (_hoops_APHCR._hoops_IIAIR == null)
							ZALLOC (_hoops_APHCR._hoops_IIAIR, _hoops_ICAIR);

						if (!BIT (_hoops_APHCR._hoops_SCIAA, _hoops_AGRAP) ||
							!ANYBIT (_hoops_APHCR._hoops_IIAIR->mask, _hoops_RICRP|_hoops_HICRP)) {
							_hoops_APHCR._hoops_SCIAA |= _hoops_AGRAP;
							_hoops_APHCR._hoops_RSIAA |= _hoops_AGRAP;

							_hoops_APHCR._hoops_IIAIR->mask = _hoops_RICRP | _hoops_HICRP;
							_hoops_APHCR._hoops_IIAIR->value = _hoops_RICRP | _hoops_HICRP;

							_hoops_APHCR._hoops_IIAIR->_hoops_RGP.mask = T_FACES | T_EDGES;
							_hoops_APHCR._hoops_IIAIR->_hoops_RGP.value = T_FACES;
						}
					}
				}
				else if (!_hoops_GHIRS (option->value.option_list,
														 mask,
														 &_hoops_APHCR)) {
					goto Failed;
				}
			}
		}
		else if ((mask & _hoops_AHGI) == _hoops_ASGAP) {
			_hoops_APHCR._hoops_PSHCA |= mask;

			if (mask == _hoops_PRRAP) {
				if (option->_hoops_GCACR) {
					_hoops_APHCR._hoops_RRRAP &= ~mask;
					_hoops_APHCR._hoops_IRARR = 0;
				}
				else {
					_hoops_APHCR._hoops_RRRAP |= mask;
					_hoops_APHCR._hoops_IRARR = option->value._hoops_RIARA[0];
				}
			}
			else if (mask == _hoops_CRRAP) {
				if (option->_hoops_GCACR) {
					_hoops_APHCR._hoops_RRRAP &= ~mask;
					_hoops_APHCR._hoops_CHIH = 0;
				}
				else {
					_hoops_APHCR._hoops_RRRAP |= mask;
					_hoops_APHCR._hoops_CHIH = option->value._hoops_RIARA[0];
				}
			}
			else if (mask == _hoops_IPRAP) {
				if (option->_hoops_GCACR) {
					_hoops_APHCR._hoops_RRRAP &= ~mask;
					_hoops_APHCR._hoops_IGAAP = 0;
				}
				else {
					_hoops_APHCR._hoops_RRRAP |= mask;
					_hoops_APHCR._hoops_IGAAP = option->value._hoops_RIARA[0];
				}
			}
			else if (mask == _hoops_SARAP) {
				if (option->_hoops_GCACR) {
					_hoops_APHCR._hoops_RRRAP &= ~mask;
					_hoops_APHCR._hoops_SHIH = 0;
				}
				else {
					_hoops_APHCR._hoops_RRRAP |= mask;
					_hoops_APHCR._hoops_SHIH = option->value._hoops_RIARA[0];
				}
			}
			else if (mask == _hoops_SPRAP) {
				if (option->_hoops_GCACR) {
					_hoops_APHCR._hoops_RRRAP &= ~mask;
				}
				else {
					_hoops_APHCR._hoops_RRRAP |= mask;
				}
			}
			else if (mask == _hoops_GPRAP) {
				if (option->_hoops_GCACR) {
					_hoops_APHCR._hoops_RRRAP &= ~mask;
					_hoops_APHCR._hoops_GSAAP = 180;
					_hoops_APHCR._hoops_RSAAP = 180;
				}
				else if (option->_hoops_SGSAP == _hoops_APRCA) {
					_hoops_APHCR._hoops_RRRAP |= mask;
					_hoops_APHCR._hoops_GSAAP = option->value._hoops_RIARA[0];
					_hoops_APHCR._hoops_RSAAP = option->value._hoops_RIARA[0];
				}
				else {
					Option_Value *		_hoops_CHAGA = option->value.option_list;

					_hoops_APHCR._hoops_RRRAP |= mask;
					_hoops_APHCR._hoops_GSAAP = -1;
					_hoops_APHCR._hoops_RSAAP = -1;

					do {
						if (!_hoops_CHAGA->_hoops_GCACR) {
							if (_hoops_CHAGA->type->id == 0)
								_hoops_APHCR._hoops_GSAAP = _hoops_CHAGA->value._hoops_RIARA[0];
							else
								_hoops_APHCR._hoops_RSAAP = _hoops_CHAGA->value._hoops_RIARA[0];
						}
					} while ((_hoops_CHAGA = _hoops_CHAGA->next) != null);
				}
			}
			else if (mask == _hoops_IRRAP) {
				if (option->_hoops_GCACR) {
					_hoops_APHCR._hoops_RRRAP &= ~mask;
					_hoops_APHCR._hoops_PSAAP = Display_List_NONE;
				}
				else {
					_hoops_APHCR._hoops_RRRAP |= mask;
					if (option->value.option_list != null) {
						_hoops_APHCR._hoops_PSAAP = (int)option->value.option_list->type->id;
						if (_hoops_APHCR._hoops_PSAAP == Display_List_NONE)
							_hoops_APHCR._hoops_RRRAP &= ~mask;
					}
					else
						_hoops_APHCR._hoops_PSAAP = Display_List_GEOMETRY;
				}
			}
			else if (mask == _hoops_IARAP) {
				if (_hoops_APHCR._hoops_HHAIR == null)
					ZALLOC (_hoops_APHCR._hoops_HHAIR, _hoops_RIAIR);

				if (option->_hoops_GCACR) {
					_hoops_APHCR._hoops_RRRAP &= ~mask;
					_hoops_APHCR._hoops_HHAIR->_hoops_ACSRP = 0;
				}
				else {
					_hoops_APHCR._hoops_RRRAP |= mask;
					_hoops_APHCR._hoops_HHAIR->_hoops_ACSRP = option->value._hoops_PIPCR[0];
				}
			}
			else if (mask == _hoops_RPRAP) {
				if (_hoops_APHCR._hoops_HHAIR == null)
					ZALLOC (_hoops_APHCR._hoops_HHAIR, _hoops_RIAIR);

				if (option->_hoops_GCACR) {
					_hoops_APHCR._hoops_RRRAP &= ~mask;
					_hoops_APHCR._hoops_HHAIR->_hoops_PCSRP = 0;
				}
				else {
					_hoops_APHCR._hoops_RRRAP |= mask;
					_hoops_APHCR._hoops_HHAIR->_hoops_PCSRP = option->value._hoops_PIPCR[0];
				}
			}
			else if (mask == _hoops_GRRAP) {
				if (_hoops_APHCR._hoops_PRSI == null)
					_hoops_PHIRS(_hoops_APHCR);

				if (option->_hoops_GCACR) {
					_hoops_APHCR._hoops_RRRAP &= ~mask;
					_hoops_APHCR._hoops_PRSI->mask |= _hoops_HRSI;
					_hoops_APHCR._hoops_PRSI->value &= ~(_hoops_HRSI);
				}
				else {
					_hoops_APHCR._hoops_RRRAP |= mask;
					_hoops_APHCR._hoops_PRSI->mask |= _hoops_HRSI;
					_hoops_APHCR._hoops_PRSI->value |= _hoops_HRSI;
				}
			}
			else if (mask == _hoops_HPRAP) {
				if (option->_hoops_GCACR) {
					_hoops_APHCR._hoops_RRRAP &= ~mask;
					_hoops_APHCR._hoops_CSRS = 1.0;
				}
				else {
					_hoops_APHCR._hoops_RRRAP |= mask;
					_hoops_APHCR._hoops_CSRS = option->value._hoops_PIPCR[0];
				}
			}
			else if (mask == _hoops_PARAP) {
				_hoops_APHCR._hoops_RRRAP |= mask;
				_hoops_APHCR._hoops_SIRAP = (int)option->value.option_list->type->id;
			}
			else if (mask == _hoops_HAI) {
				_hoops_APHCR._hoops_SCIAA |= _hoops_PGRAP;
				_hoops_APHCR._hoops_RSIAA |= _hoops_PGRAP;

				if (option->_hoops_GCACR) {
					_hoops_APHCR._hoops_RRRAP &= ~mask;
					_hoops_APHCR._hoops_SHAAP |= _hoops_CHRH;
					_hoops_APHCR._hoops_GIAAP &= ~_hoops_CHRH;
				}
				else {
					_hoops_APHCR._hoops_RRRAP |= mask;
					_hoops_APHCR._hoops_SHAAP |= _hoops_CHRH|_hoops_HIGRP|_hoops_AIGRP|_hoops_PIGRP;
					_hoops_APHCR._hoops_GIAAP |= _hoops_CHRH|_hoops_HIGRP|_hoops_AIGRP|_hoops_PIGRP;
					_hoops_APHCR._hoops_IHRH._hoops_ACGRP = _hoops_CIGRP;
					_hoops_APHCR._hoops_IHRH.scale = 1.0f;
					_hoops_APHCR._hoops_IHRH.translate = 0.0f;
					_hoops_APHCR._hoops_IHRH.color = _hoops_GPSR::_hoops_IAHHP;
				}
			}
			else if (option->_hoops_GCACR) {
				_hoops_APHCR._hoops_RRRAP &= ~mask;
			}
			else if (mask == _hoops_HRRAP) {
				_hoops_APHCR._hoops_RRRAP |= mask;

				if (option->_hoops_AIPCR != 2) {
					HE_ERROR (HEC_RENDERING, HES_INVALID_COUNT, "The depth range rendering option requires 2 values");
					goto Failed;
				}
				_hoops_APHCR._hoops_HHAAP[0] = option->value._hoops_PIPCR[0];
				_hoops_APHCR._hoops_HHAAP[1] = option->value._hoops_PIPCR[1];
			}
			else if (mask == _hoops_APRAP) {
				_hoops_APHCR._hoops_RRRAP |= mask;

				if (option->_hoops_AIPCR != 4) {
					HE_ERROR (HEC_RENDERING, HES_INVALID_COUNT, "The screen range rendering option requires 4 values");
					goto Failed;
				}
				_hoops_APHCR._hoops_HCIH.left = option->value._hoops_PIPCR[0];
				_hoops_APHCR._hoops_HCIH.right = option->value._hoops_PIPCR[1];
				_hoops_APHCR._hoops_HCIH.bottom = option->value._hoops_PIPCR[2];
				_hoops_APHCR._hoops_HCIH.top = option->value._hoops_PIPCR[3];
			}
			else if (mask == _hoops_PPRAP) {
				_hoops_APHCR._hoops_RRRAP |= mask;

				if (option->_hoops_AIPCR != 3) {
					HE_ERROR (HEC_RENDERING, HES_INVALID_COUNT, "The ambient up vector rendering option requires 3 values");
					goto Failed;
				}

				if (_hoops_APHCR._hoops_HHAIR == null)
					ZALLOC (_hoops_APHCR._hoops_HHAIR, _hoops_RIAIR);

				_hoops_APHCR._hoops_HHAIR->_hoops_HRGA.x = option->value._hoops_PIPCR[0];
				_hoops_APHCR._hoops_HHAIR->_hoops_HRGA.y = option->value._hoops_PIPCR[1];
				_hoops_APHCR._hoops_HHAIR->_hoops_HRGA.z = option->value._hoops_PIPCR[2];
			}
			else if (mask == _hoops_GARAP) {
				_hoops_APHCR._hoops_RRRAP |= mask;

				if (option->_hoops_AIPCR == 0) {
					HE_ERROR (HEC_RENDERING, HES_INVALID_COUNT, "The Image Scale option requires 1 or 2 values");
					goto Failed;
				}

				_hoops_APHCR._hoops_IHAAP[0] = option->value._hoops_PIPCR[0];
				if (option->_hoops_AIPCR == 1)
					_hoops_APHCR._hoops_IHAAP[1] = _hoops_APHCR._hoops_IHAAP[0];
				else
					_hoops_APHCR._hoops_IHAAP[1] = option->value._hoops_PIPCR[1];
			}
			else if (mask == _hoops_RARAP) {
				Named_Material			_hoops_GGPRA;
				bool					_hoops_IA = true;

				ZERO_STRUCT(&_hoops_GGPRA, Named_Material);
				if (!HI_Evaluate_Color (_hoops_RIGC, &option->value._name[0], &_hoops_GGPRA, 0, true)) {
					_hoops_IA = false;
				}

				if (ANYBIT (_hoops_GGPRA._hoops_PRGRA, ~(M_DIFFUSE|_hoops_RHGRA)) ||
					_hoops_GGPRA._hoops_SCA != null) {		/* _hoops_IRHH _hoops_SCH _hoops_IHGP */
					_hoops_IA = false;
				}

				if (_hoops_IA) {
					_hoops_APHCR._hoops_RRRAP |= mask;
					HI_HLS_To_RGB ((_hoops_PACHR const *)&_hoops_GGPRA._hoops_CSHR, &_hoops_APHCR._hoops_CHAAP);
				}
				else {
					HE_WARNING (HEC_RENDERING, HES_INVALID_RANGE, "Image Tint must be a simple color.");
				}

				HI_Free_Material_Names (&_hoops_GGPRA, 1);
			}
			else if (mask == _hoops_CPRAP) {
				Named_Material			_hoops_GGPRA;
				bool					_hoops_IA = true;

				ZERO_STRUCT(&_hoops_GGPRA, Named_Material);
				if (!HI_Evaluate_Color (_hoops_RIGC, &option->value._name[0], &_hoops_GGPRA, 0, true)) {
					_hoops_IA = false;
				}

				if (ANYBIT (_hoops_GGPRA._hoops_PRGRA, ~(M_DIFFUSE|_hoops_RHGRA)) ||
					_hoops_GGPRA._hoops_SCA != null) {		/* _hoops_IRHH _hoops_SCH _hoops_IHGP */
					_hoops_IA = false;
				}

				if (_hoops_IA) {
					_hoops_APHCR._hoops_RRRAP |= mask;
					HI_HLS_To_RGB ((_hoops_PACHR const *)&_hoops_GGPRA._hoops_CSHR, &_hoops_APHCR._hoops_HRA);
				}
				else {
					HE_WARNING (HEC_RENDERING, HES_INVALID_RANGE,"Diffuse Texture Tint must be a simple color.");
				}

				HI_Free_Material_Names (&_hoops_GGPRA, 1);
			}
			else if (mask == _hoops_SRRAP) {
				if (!_hoops_GAIRS (option->value.option_list, &_hoops_APHCR)) {
					char			_hoops_SSSSI [MAX_ERRMSG];

					HE_ERROR3 (HEC_SYNTAX, HES_PARSE_STRING,
							Sprintf_S (_hoops_SSSSI,"Error parsing option string '%s' -", list),
							"Can't find parameter list for 'hidden surface removal algorithm'",
							"(If you have unquoted string parameters, quote marks may fix the problem.)");

					goto Failed;
				}
			}
			else if (mask == _hoops_HPH) {
				_hoops_APHCR._hoops_RRRAP |= mask;

				if (_hoops_APHCR._hoops_HHAIR == null)
					ZALLOC (_hoops_APHCR._hoops_HHAIR, _hoops_RIAIR);

				if (!_hoops_IRIRS (option->value.option_list, &_hoops_APHCR._hoops_HHAIR->_hoops_CRIR.hither, &_hoops_APHCR._hoops_HHAIR->_hoops_CRIR.yon)) {
					goto Failed;
				}
			}
			else if (mask == _hoops_CARAP) {
				Option_Value *		_hoops_AHSAA;

				_hoops_APHCR._hoops_RRRAP |= mask;

				_hoops_APHCR._hoops_RCRAP = 0;
				if ((_hoops_AHSAA = option->value.option_list) != null) do {
					_hoops_APHCR._hoops_RCRAP |= (int)_hoops_AHSAA->type->id;
				} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
			}
			else
				_hoops_APHCR._hoops_RRRAP |= mask;
		}
		else {
			if (mask == _hoops_GRRAP) {
				if (_hoops_APHCR._hoops_PRSI == null)
					_hoops_PHIRS(_hoops_APHCR);

				/* _hoops_IHIRS-_hoops_HCSP */
				_hoops_APHCR._hoops_SCIAA |= _hoops_SGICA;
				_hoops_APHCR._hoops_RSIAA |= _hoops_SGICA;
				_hoops_APHCR._hoops_PRSI->mask |= _hoops_HRSI;
				if (option->_hoops_GCACR)
					_hoops_APHCR._hoops_PRSI->value &= ~_hoops_HRSI;
				else
					_hoops_APHCR._hoops_PRSI->value |= _hoops_HRSI;
			}
			else {
				_hoops_APHCR._hoops_SCIAA |= mask;

				if (mask == _hoops_GSIAA) {
					if (option->_hoops_GCACR)
						_hoops_APHCR._hoops_RSIAA &= ~mask;
					else {
						if (_hoops_APHCR.locks == null)
							ZALLOC (_hoops_APHCR.locks, _hoops_CCAIR);

						_hoops_ASHRS (option->value.option_list, &_hoops_APHCR, _hoops_GSIAA, &_hoops_APHCR.locks->normal);
					}
				}
				else if (mask == _hoops_RGRAP) {
					if (option->_hoops_GCACR)
						_hoops_APHCR._hoops_RSIAA &= ~mask;
					else {
						if (_hoops_APHCR.locks == null)
							ZALLOC (_hoops_APHCR.locks, _hoops_CCAIR);

						_hoops_ASHRS (option->value.option_list, &_hoops_APHCR, _hoops_RGRAP, &_hoops_APHCR.locks->_hoops_SACRP);
					}
				}
				else if (mask == _hoops_RRICA) {
					_hoops_APHCR._hoops_RSIAA |= mask;

					if (_hoops_APHCR._hoops_HHAIR == null)
						ZALLOC (_hoops_APHCR._hoops_HHAIR, _hoops_RIAIR);

					if (option->_hoops_GCACR) {
						_hoops_APHCR._hoops_HHAIR->_hoops_GHSS.mask |= _hoops_PGGAP;
						_hoops_APHCR._hoops_HHAIR->_hoops_GHSS.value &= ~_hoops_PGGAP;
						_hoops_APHCR._hoops_HHAIR->_hoops_GHSS._hoops_RGP = _hoops_HRGAP;
					}
					else if (option->value.option_list == null) {
						_hoops_APHCR._hoops_HHAIR->_hoops_GHSS.mask |= _hoops_PGGAP;
						_hoops_APHCR._hoops_HHAIR->_hoops_GHSS.value |= _hoops_PGGAP;
						_hoops_APHCR._hoops_HHAIR->_hoops_GHSS._hoops_RGP = _hoops_IRGAP;
					}
					else if (!_hoops_ARIRS (_hoops_RIGC, option->value.option_list, &_hoops_APHCR)) {
						goto Failed;
					}
				}
				else if (mask == _hoops_CSGAP) {
					_hoops_APHCR._hoops_RSIAA |= mask;

					if (_hoops_APHCR._hoops_HHAIR == null)
						ZALLOC (_hoops_APHCR._hoops_HHAIR, _hoops_RIAIR);

					if (option->_hoops_GCACR) {
						_hoops_APHCR._hoops_HHAIR->_hoops_HRR.mask |= _hoops_GAGAP;
						_hoops_APHCR._hoops_HHAIR->_hoops_HRR.value &= ~_hoops_GAGAP;
					}
					else if (option->value.option_list == null) {
						_hoops_APHCR._hoops_HHAIR->_hoops_HRR.mask |= _hoops_GAGAP;
						_hoops_APHCR._hoops_HHAIR->_hoops_HRR.value |= _hoops_GAGAP;
					}
					else if (!_hoops_PRIRS (option->value.option_list, &_hoops_APHCR)) {
						goto Failed;
					}
				}
				else if (mask == _hoops_SSGAP) {
					_hoops_APHCR._hoops_RSIAA |= mask;

					if (_hoops_APHCR._hoops_HHAIR == null)
						ZALLOC (_hoops_APHCR._hoops_HHAIR, _hoops_RIAIR);

					if (option->_hoops_GCACR) {
						_hoops_APHCR._hoops_HHAIR->_hoops_RHGGR.mask |= _hoops_CAGAP;
						_hoops_APHCR._hoops_HHAIR->_hoops_RHGGR.value &= ~_hoops_CAGAP;
					}
					else if (option->value.option_list == null) {
						_hoops_APHCR._hoops_HHAIR->_hoops_RHGGR.mask |= _hoops_CAGAP;
						_hoops_APHCR._hoops_HHAIR->_hoops_RHGGR.value |= _hoops_CAGAP;
					}
					else if (!_hoops_CRIRS (option->value.option_list, &_hoops_APHCR)) {
						goto Failed;
					}
				}
				else if (option->_hoops_GCACR) {
					_hoops_APHCR._hoops_RSIAA &= ~mask;
				}
				else if (mask == _hoops_AGICA) {
					_hoops_APHCR._hoops_RSIAA |= mask;

					if (!_hoops_GRIRS (option->value.option_list, &_hoops_APHCR)) {
						goto Failed;
					}
				}
				else if (mask == _hoops_GGICA) {
					_hoops_APHCR._hoops_RSIAA |= mask;

					if (!_hoops_SRIRS (option->value.option_list, &_hoops_APHCR)) {
						goto Failed;
					}
				}
				else if (mask == _hoops_CSHCA) {
					_hoops_APHCR._hoops_RSIAA |= mask;

					if (!_hoops_RAIRS (option->value.option_list, &_hoops_APHCR)) {
						goto Failed;
					}
				}
				else if (mask == _hoops_ISGAP) {
					_hoops_APHCR._hoops_RSIAA |= mask;

					if (!_hoops_AAIRS (option->value.option_list, &_hoops_APHCR)) {
						goto Failed;
					}
				}
				else if (mask == _hoops_IRICA) {
					_hoops_APHCR._hoops_RSIAA |= mask;

					if (_hoops_APHCR.geometry == null)
						ZALLOC (_hoops_APHCR.geometry, _hoops_SCAIR);

					if (!_hoops_GGIRS (option->value.option_list, &_hoops_APHCR)) {
						char			_hoops_SSSSI [MAX_ERRMSG];

						HE_ERROR3 (HEC_SYNTAX, HES_PARSE_STRING,
								Sprintf_S (_hoops_SSSSI,"Error parsing option string '%s' -", list),
								"Invalid parameter list for 'nurbs curve'",
								"(If you have unquoted string parameters, quote marks may fix the problem.)");

						goto Failed;
					}
				}
				else if (mask == _hoops_CRICA) {
					_hoops_APHCR._hoops_RSIAA |= mask;

					if (_hoops_APHCR.geometry == null)
						ZALLOC (_hoops_APHCR.geometry, _hoops_SCAIR);

					if (!HI_Process_NURBS_Surface_Options (option->value.option_list, &_hoops_APHCR)) {
						char			_hoops_SSSSI [MAX_ERRMSG];

						HE_ERROR3 (HEC_SYNTAX, HES_PARSE_STRING,
								Sprintf_S (_hoops_SSSSI, "Error parsing option string '%s' -",list),
								"Invalid parameter list for 'nurbs surface'",
								"(If you have unquoted string parameters, quote marks may fix the problem.)");


						goto Failed;
					}
				}
				else if (mask == _hoops_SRICA) {
					_hoops_APHCR._hoops_RSIAA |= mask;

					if (_hoops_APHCR.geometry == null)
						ZALLOC (_hoops_APHCR.geometry, _hoops_SCAIR);

					if (!_hoops_HGIRS (option->value.option_list, &_hoops_APHCR)) {
						char			_hoops_SSSSI [MAX_ERRMSG];

						HE_ERROR3 (HEC_SYNTAX, HES_PARSE_STRING,
								Sprintf_S (_hoops_SSSSI,"Error parsing option string '%s' -", list),
								"Invalid parameter list for 'tessellation'",
								"(If you have unquoted string parameters, quote marks may fix the problem.)");


						goto Failed;
					}
				}
				else if (mask == _hoops_HRICA) {
					Option_Value const *		_hoops_AHSAA = option->value.option_list;

					_hoops_APHCR._hoops_RSIAA |= mask;

					if (_hoops_APHCR.geometry == null)
						ZALLOC (_hoops_APHCR.geometry, _hoops_SCAIR);

					if (_hoops_AHSAA != null) do {
						int						_hoops_PHSAA = _hoops_AHSAA->type->id;

						if (_hoops_PHSAA == _hoops_GHGAP) {
							_hoops_APHCR.geometry->mask |= _hoops_PHSAA;
							_hoops_APHCR.geometry->value |= _hoops_PHSAA;
							_hoops_APHCR.geometry->_hoops_GCIPR = _hoops_AHSAA->value._hoops_PIPCR[0];

							if (_hoops_APHCR.geometry->_hoops_GCIPR < 0.0f ||
								_hoops_APHCR.geometry->_hoops_GCIPR > 180.0f) {
								char			_hoops_SSSSI [MAX_ERRMSG];

								HE_ERROR2 (HEC_RENDERING, HES_OUT_OF_RANGE,
										Sprintf_S (_hoops_SSSSI,"Error parsing option string '%s' -",list),
										"Hard edge dihedral angle must be from 0 to 180");


								goto Failed;
							}
						}
						else if (_hoops_PHSAA == _hoops_PHGAP) {
							if (_hoops_AHSAA->_hoops_GCACR) {
								_hoops_APHCR.geometry->mask |= _hoops_PHSAA;
								_hoops_APHCR.geometry->value &= ~_hoops_PHSAA;
							}
							else if (_hoops_AHSAA->_hoops_AIPCR == 0) {
								_hoops_APHCR.geometry->mask |= _hoops_PHSAA;
								_hoops_APHCR.geometry->value |= _hoops_PHSAA;
							}
							else {
								Option_Value const *		_hoops_CHSAA = _hoops_AHSAA->value.option_list;

								do {
									int						_hoops_SHSAA = _hoops_CHSAA->type->id;

									if (_hoops_SHSAA == 0) {
										_hoops_APHCR.geometry->mask |= _hoops_PHSAA;
										_hoops_APHCR.geometry->value &= ~_hoops_PHSAA;
									}
									else {
										_hoops_APHCR.geometry->mask |= _hoops_SHSAA;
										if (_hoops_CHSAA->_hoops_GCACR)
											_hoops_APHCR.geometry->value &= ~_hoops_SHSAA;
										else
											_hoops_APHCR.geometry->value |= _hoops_SHSAA;
									}
								} while ((_hoops_CHSAA = _hoops_CHSAA->next) != null);
							}
						}
					} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
				}
				else if (mask == _hoops_ARICA) {
					_hoops_APHCR._hoops_RSIAA |= mask;

					if (_hoops_APHCR._hoops_HHAIR == null)
						ZALLOC (_hoops_APHCR._hoops_HHAIR, _hoops_RIAIR);

					if (!_hoops_RRIRS (option->value.option_list, &_hoops_APHCR)) {
						goto Failed;
					}
				}
				else if (mask == _hoops_IGICA) {
					_hoops_APHCR._hoops_RSIAA |= mask;

					if (_hoops_APHCR._hoops_AIAIR == null)
						ZALLOC (_hoops_APHCR._hoops_AIAIR, _hoops_HIAIR);

					if (!_hoops_PAIRS (_hoops_RIGC, option->value.option_list, &_hoops_APHCR)) {
						goto Failed;
					}
				}
				else if (mask == _hoops_AGRAP) {
					_hoops_APHCR._hoops_RSIAA |= mask;

					if (_hoops_APHCR._hoops_IIAIR == null)
						ZALLOC (_hoops_APHCR._hoops_IIAIR, _hoops_ICAIR);

					if (!_hoops_HAIRS (option->value.option_list, &_hoops_APHCR)) {
						goto Failed;
					}
				}
				else if (mask == _hoops_PRICA) {
					_hoops_APHCR._hoops_RSIAA |= mask;

					if (_hoops_APHCR._hoops_IIAIR == null)
						ZALLOC (_hoops_APHCR._hoops_IIAIR, _hoops_ICAIR);

					if (!_hoops_CAIRS (_hoops_RIGC, option->value.option_list, &_hoops_APHCR)) {
						goto Failed;
					}
				}
				else if (mask == _hoops_PGRAP) {
					_hoops_APHCR._hoops_RSIAA |= mask;

					if (option->_hoops_GCACR) {
						_hoops_APHCR._hoops_SHAAP |= _hoops_CHRH;
						_hoops_APHCR._hoops_GIAAP &= ~_hoops_CHRH;
					}
					else if (!_hoops_SAIRS (_hoops_RIGC, option->value.option_list, &_hoops_APHCR)) {
						goto Failed;
					}
				}
				else if (mask == _hoops_SGICA) {
					_hoops_APHCR._hoops_RSIAA |= mask;

					if (_hoops_APHCR._hoops_PRSI == null)
						_hoops_PHIRS(_hoops_APHCR);

					if (!_hoops_RPIRS (option->value.option_list, &_hoops_APHCR)) {
						goto Failed;
					}
				}
				else if (mask == _hoops_GGRAP) {
					_hoops_APHCR._hoops_RSIAA |= mask;

					if (_hoops_APHCR._hoops_HHAIR == null)
						ZALLOC (_hoops_APHCR._hoops_HHAIR, _hoops_RIAIR);

					if (!_hoops_GPIRS (option->value.option_list, &_hoops_APHCR)) {
						goto Failed;
					}
				}
				else
					_hoops_APHCR._hoops_RSIAA |= mask;
			}
		}
	} while ((option = option->next) != null);

	HI_Free_Option_List (_hoops_RIGC, option_list);

	_hoops_APHCR._hoops_PSHCA  &= ~_hoops_AHGI;
	_hoops_APHCR._hoops_RRRAP &= ~_hoops_AHGI;
	_hoops_APHCR._hoops_ISHCA  &= ~_hoops_AHGI;
	_hoops_APHCR._hoops_GHRAP &= ~_hoops_AHGI;

	return true;

Failed:
	if (option_list)
		HI_Free_Option_List (_hoops_RIGC, option_list);

	_hoops_AHIRS(_hoops_RIGC, _hoops_APHCR);

	return false;
}


GLOBAL_FUNCTION bool HI_Set_Rendering_Options(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_RHAIR *		_hoops_RSHCA)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_RENDERING_OPTIONS, _hoops_SCHRS, _hoops_RSHCA);
}


HC_INTERFACE void HC_CDECL HC_Set_Rendering_Options (
	char const *	list)
{
	_hoops_PAPPR context("Set_Rendering_Options");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Rendering_Options (%S);\n", list));
	);

	bool				used = false;
	_hoops_RHAIR * _hoops_RSHCA;
	ZALLOC(_hoops_RSHCA, _hoops_RHAIR);

	if (_hoops_HHIRS (context, list, *_hoops_RSHCA)) {
		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_IPRPP)) != null) {
			used = HI_Set_Rendering_Options(context, target, _hoops_RSHCA);
			_hoops_IRRPR();
		}
	}

	if (!used) {
		_hoops_AHIRS(context, *_hoops_RSHCA);
		FREE (_hoops_RSHCA, _hoops_RHAIR);
	}
}

GLOBAL_FUNCTION bool HI_Unset_Rendering_Options (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_RHAIR *		_hoops_RCIHP) 
{
	/* _hoops_RRGRA */
	UNREFERENCED(_hoops_RIGC);
	UNREFERENCED(item);
	UNREFERENCED(_hoops_RCIHP);
	return false;
}

HC_INTERFACE void HC_CDECL HC_UnSet_Rendering_Options (void) 
{
	_hoops_PAPPR context("UnSet_Rendering_Options");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Rendering_Options ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_IPRPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute (context,  target, HK_RENDERING_OPTIONS);
		_hoops_IRRPR();
	}
}



#ifdef DISABLE_SHOW
#	ifdef DISABLE_METAFILE
#		define	_hoops_CHIRS
#	endif
#endif

#ifndef _hoops_CHIRS

local const struct _hoops_SHIRS {
	_hoops_GHGI				mask;
	_hoops_SRHSR				name;
}		_hoops_GIIRS[] = {
	{_hoops_CIRAP,		_hoops_GRRCR ("lighting interpolation")},
	{_hoops_SHRAP,		_hoops_GRRCR ("texture interpolation")},
	{_hoops_AHRAP,			_hoops_GRRCR ("color interpolation")},
	{_hoops_HHRAP,	_hoops_GRRCR ("color index interpolation")},
	{_hoops_GSIAA,				_hoops_GRRCR ("attribute lock")},
	{_hoops_RGRAP,					_hoops_GRRCR ("ignore subsegment lock")},
	{_hoops_PRRAP,						_hoops_GRRCR ("debug")},
	{_hoops_CARAP,					_hoops_GRRCR ("technology")},
#ifndef DISABLE_AIR_OPTIONS
	{_hoops_HGRAP,			_hoops_GRRCR ("radiosity options")},
	{_hoops_IGRAP,			_hoops_GRRCR ("ray-trace options")},
#endif
	{_hoops_PARAP,				_hoops_GRRCR ("quantization")},
	{_hoops_SRRAP,				_hoops_GRRCR ("hidden surface removal algorithm")},
	{_hoops_GGICA,				_hoops_GRRCR ("software frame buffer options")},
	{_hoops_IGICA,			_hoops_GRRCR ("hidden line removal options")},
	{_hoops_GRRAP,							_hoops_GRRCR ("lod")},
	{_hoops_SGICA,					_hoops_GRRCR ("level of detail options")},
	{_hoops_CRRAP,			_hoops_GRRCR ("face displacement")},
	{_hoops_IPRAP,			_hoops_GRRCR ("vertex displacement")},
	{_hoops_SARAP,		_hoops_GRRCR ("general displacement")},
	{_hoops_CRI,		_hoops_GRRCR ("frame buffer effects")},
	{_hoops_GPRAP,			_hoops_GRRCR ("join cutoff angle")},
	{_hoops_HARAP,						_hoops_GRRCR ("stereo")},
	{_hoops_IARAP,			_hoops_GRRCR ("stereo separation")},
	{_hoops_RPRAP,				_hoops_GRRCR ("stereo distance")},
	{_hoops_IRRAP,				_hoops_GRRCR ("display lists")},
	{_hoops_IRRAP,				_hoops_GRRCR ("display list")},
	{_hoops_IRRAP,				_hoops_GRRCR ("use display lists")},
	{_hoops_IRRAP,				_hoops_GRRCR ("use display list")},
	{Rendo_LOCAL_VIEWER,				_hoops_GRRCR ("local viewer")},
	{_hoops_HRRAP,					_hoops_GRRCR ("depth range")},
	{_hoops_APRAP,				_hoops_GRRCR ("screen range")},
	{_hoops_PPRAP,			_hoops_GRRCR ("ambient up vector")},
	{_hoops_HPH,		_hoops_GRRCR ("atmospheric attenuation")},
	{_hoops_CSGGA,		_hoops_GRRCR ("perspective correction")},
	{_hoops_IRICA,			_hoops_GRRCR ("general curve")},
	{_hoops_IRICA,			_hoops_GRRCR ("nurbs curve")},
	{_hoops_CRICA,		_hoops_GRRCR ("nurbs surface")},
	{_hoops_SRICA,		_hoops_GRRCR ("tessellation")},
	{_hoops_HRICA,			_hoops_GRRCR ("geometry options")},
	{_hoops_ARICA,		_hoops_GRRCR ("cut geometry options")},
	{_hoops_RRICA,		_hoops_GRRCR ("simple shadow")},
	{_hoops_CSGAP,			_hoops_GRRCR ("shadow map")},
	{_hoops_SSGAP,	_hoops_GRRCR ("simple reflection")},
	{_hoops_GGRAP,				_hoops_GRRCR ("gooch options")},
	{_hoops_CSHCA,		_hoops_GRRCR ("transparency options")},
	{_hoops_ISGAP,			_hoops_GRRCR ("anti-alias")},
	{_hoops_AGICA,				_hoops_GRRCR ("mask transform")},
	{_hoops_AARAP,		_hoops_GRRCR ("local cutting planes")},
	{_hoops_GARAP,					_hoops_GRRCR ("image scale")},
	{_hoops_RARAP,					_hoops_GRRCR ("image tint")},
	{_hoops_CPRAP,		_hoops_GRRCR ("diffuse texture tint")},
	{_hoops_HAI,				_hoops_GRRCR ("force grayscale")},
	{_hoops_HPRAP,			_hoops_GRRCR ("vertex decimation")},
	{_hoops_SPRAP,			_hoops_GRRCR ("scaled displacement")},
	{_hoops_AGRAP,				_hoops_GRRCR ("color index interpolation options")},
	{_hoops_PRICA,				_hoops_GRRCR ("isoline options")},
	{_hoops_PGRAP,			_hoops_GRRCR ("diffuse color tint")},
	{false, _hoops_PCGSA}};


local const struct _hoops_RIIRS {
	_hoops_HHAGP		mask;
	_hoops_SRHSR			name;
}		_hoops_AIIRS[] = {
	{_hoops_GGCAA(HK_STYLE),					_hoops_GRRCR ("style")},
	{_hoops_GGCAA(HK_RENDERING_OPTIONS),		_hoops_GRRCR ("rendering options")},
	{_hoops_GGCAA(HK_SELECTABILITY),			_hoops_GRRCR ("selectability")},
	{_hoops_GGCAA(HK_VISIBILITY),				_hoops_GRRCR ("visibility")},
	{_hoops_GGCAA(HK_WINDOW_FRAME),			_hoops_GRRCR ("window frame")},
	{_hoops_GGCAA(HK_WINDOW),					_hoops_GRRCR ("window")},
	{_hoops_GGCAA(HK_COLOR_MAP),				_hoops_GRRCR ("color map")},
	{_hoops_GGCAA(HK_COLOR),					_hoops_GRRCR ("color")},
	{_hoops_GGCAA(HK_CAMERA),					_hoops_GRRCR ("camera")},
	{_hoops_GGCAA(HK_CALLBACK),				_hoops_GRRCR ("callback")},
	{_hoops_GGCAA(HK_CLIP_REGION),			_hoops_GRRCR ("clip region")},
	{_hoops_GGCAA(HK_DRIVER_OPTIONS),			_hoops_GRRCR ("driver options")},
	{_hoops_GGCAA(HK_EDGE_PATTERN),			_hoops_GRRCR ("edge pattern")},
	{_hoops_GGCAA(HK_EDGE_WEIGHT),			_hoops_GRRCR ("edge weight")},
	{_hoops_GGCAA(HK_FACE_PATTERN),			_hoops_GRRCR ("face pattern")},
	{_hoops_GGCAA(HK_HANDEDNESS),				_hoops_GRRCR ("handedness")},
	{_hoops_GGCAA(HK_HEURISTICS),				_hoops_GRRCR ("heuristics")},
	{_hoops_GGCAA(HK_LINE_PATTERN),			_hoops_GRRCR ("line pattern")},
	{_hoops_GGCAA(HK_LINE_WEIGHT),			_hoops_GRRCR ("line weight")},
	{_hoops_GGCAA(HK_MARKER_SIZE),			_hoops_GRRCR ("marker size")},
	{_hoops_GGCAA(HK_MARKER_SYMBOL),			_hoops_GRRCR ("marker symbol")},
	{_hoops_GGCAA(HK_MODELLING_MATRIX),		_hoops_GRRCR ("modelling matrix")},
	{_hoops_GGCAA(HK_TEXT_ALIGNMENT),			_hoops_GRRCR ("text alignment")},
	{_hoops_GGCAA(HK_TEXT_FONT),				_hoops_GRRCR ("text font")},
	{_hoops_GGCAA(HK_TEXT_PATH),				_hoops_GRRCR ("text path")},
	{_hoops_GGCAA(HK_TEXT_SPACING),			_hoops_GRRCR ("text spacing")},
	{_hoops_GGCAA(HK_USER_OPTIONS),			_hoops_GRRCR ("user options")},
	{_hoops_GGCAA(HK_USER_VALUE),				_hoops_GRRCR ("user value")},
	{_hoops_GGCAA(HK_WINDOW_PATTERN),			_hoops_GRRCR ("window pattern")},
	{_hoops_GGCAA(HK_TEXTURE_MATRIX),			_hoops_GRRCR ("texture matrix")},
	{false, _hoops_PCGSA}};

#define _hoops_PIIRS		((unsigned Integer32)(~0UL))



	/* _hoops_RPCC _hoops_IRHAP _hoops_GPP _hoops_IGH _hoops_RGSR _hoops_GHCA _hoops_SHH _hoops_PSAP */
#define _hoops_ISIIH(_hoops_ASSGH, _hoops_CSIIH, _hoops_HSSGH, _hoops_ISSGH, _hoops_CSSGH) do {			\
			if (_hoops_CSIIH) {												\
				if (_hoops_HSSGH == null)										\
					_hoops_ISSGH = HI_Sprintf1 (_hoops_ISSGH, _hoops_CSSGH, "%s,", _hoops_ASSGH);		\
				else													\
					_hoops_ISSGH = HI_Copy_Chars ("on,", _hoops_ISSGH);					\
			}															\
			else {														\
				if (_hoops_HSSGH == null)										\
					_hoops_ISSGH = HI_Sprintf1 (_hoops_ISSGH, _hoops_CSSGH, "no %s,", _hoops_ASSGH);	\
				else													\
					_hoops_ISSGH = HI_Copy_Chars ("off,", _hoops_ISSGH);					\
			}															\
		} while (0)

#define _hoops_HIIRS(_hoops_ASSGH, _hoops_CSIIH, _hoops_IIIRS, _hoops_HSSGH, _hoops_ISSGH, _hoops_CSSGH) do {	\
			if (_hoops_CSIIH) {												\
				if (_hoops_HSSGH == null)										\
					_hoops_ISSGH = HI_Sprintf1 (_hoops_ISSGH, _hoops_CSSGH, "%s=", _hoops_ASSGH);		\
				_hoops_ISSGH = HI_Sprintf1 (p, pe,"%s,", _hoops_IIIRS);				\
			}															\
			else {														\
				if (_hoops_HSSGH == null)										\
					_hoops_ISSGH = HI_Sprintf1 (_hoops_ISSGH, _hoops_CSSGH, "no %s,", _hoops_ASSGH);	\
				else													\
					_hoops_ISSGH = HI_Copy_Chars ("off,", _hoops_ISSGH);					\
			}															\
		} while (0)

#define _hoops_CIIRS(_hoops_ASSGH, _hoops_CSIIH, _hoops_SIIRS, _hoops_HSSGH, _hoops_ISSGH, _hoops_CSSGH) do {		\
			if (_hoops_CSIIH) {												\
				if (_hoops_HSSGH == null)										\
					_hoops_ISSGH = HI_Sprintf1 (_hoops_ISSGH, _hoops_CSSGH, "%s=", _hoops_ASSGH);		\
				_hoops_ISSGH = HI_Sprintf1 (p, pe,"%d,", &_hoops_SIIRS);				\
			}															\
			else {														\
				if (_hoops_HSSGH == null)										\
					_hoops_ISSGH = HI_Sprintf1 (_hoops_ISSGH, _hoops_CSSGH, "no %s,", _hoops_ASSGH);	\
				else													\
					_hoops_ISSGH = HI_Copy_Chars ("off,", _hoops_ISSGH);					\
			}															\
		} while (0)

#define _hoops_GCIRS(_hoops_ASSGH, _hoops_CSIIH, _hoops_SIIRS, _hoops_HSSGH, _hoops_ISSGH, _hoops_CSSGH) do {		\
			if (_hoops_CSIIH) {												\
				if (_hoops_HSSGH == null)										\
					_hoops_ISSGH = HI_Sprintf1 (_hoops_ISSGH, _hoops_CSSGH, "%s=", _hoops_ASSGH);		\
				_hoops_ISSGH = HI_Sprintf1 (p, pe,"%D,", &_hoops_SIIRS);				\
			}															\
			else {														\
				if (_hoops_HSSGH == null)										\
					_hoops_ISSGH = HI_Sprintf1 (_hoops_ISSGH, _hoops_CSSGH, "no %s,", _hoops_ASSGH);	\
				else													\
					_hoops_ISSGH = HI_Copy_Chars ("off,", _hoops_ISSGH);					\
			}															\
		} while (0)

#define _hoops_RCIRS(_hoops_ASSGH, _hoops_CSIIH, _hoops_PSSGH, _hoops_HSSGH, _hoops_ISSGH, _hoops_CSSGH) do {		\
			if (_hoops_CSIIH) {												\
				if (_hoops_HSSGH == null)										\
					_hoops_ISSGH = HI_Sprintf1 (_hoops_ISSGH, _hoops_CSSGH, "%s=", _hoops_ASSGH);		\
				_hoops_ISSGH = HI_Sprintf1 (p, pe,"%f,", &_hoops_PSSGH);				\
			}															\
			else {														\
				if (_hoops_HSSGH == null)										\
					_hoops_ISSGH = HI_Sprintf1 (_hoops_ISSGH, _hoops_CSSGH, "no %s,", _hoops_ASSGH);	\
				else													\
					_hoops_ISSGH = HI_Copy_Chars ("off,", _hoops_ISSGH);					\
			}															\
		} while (0)

/* _hoops_IIH _hoops_HRGR _hoops_PSP '_hoops_PSAP' _hoops_SRSGR _hoops_IH _hoops_AGCR */
#define _hoops_ACIRS(_hoops_ASSGH, _hoops_IIIRS, _hoops_HSSGH, _hoops_ISSGH, _hoops_CSSGH) do {			\
			if (_hoops_HSSGH == null)											\
				_hoops_ISSGH = HI_Sprintf1 (_hoops_ISSGH, _hoops_CSSGH, "%s=", _hoops_ASSGH);			\
			_hoops_ISSGH = HI_Sprintf1 (p, pe,"%s,", _hoops_IIIRS);					\
		} while (0)

#define _hoops_PCIRS(_hoops_ASSGH, _hoops_SIIRS, _hoops_HSSGH, _hoops_ISSGH, _hoops_CSSGH) do {				\
			if (_hoops_HSSGH == null)											\
				_hoops_ISSGH = HI_Sprintf1 (_hoops_ISSGH, _hoops_CSSGH, "%s=", _hoops_ASSGH);			\
			_hoops_ISSGH = HI_Sprintf1 (p, pe,"%d,", &_hoops_SIIRS);					\
		} while (0)

#define _hoops_HCIRS(_hoops_ASSGH, _hoops_SIIRS, _hoops_HSSGH, _hoops_ISSGH, _hoops_CSSGH) do {				\
			if (_hoops_HSSGH == null)											\
				_hoops_ISSGH = HI_Sprintf1 (_hoops_ISSGH, _hoops_CSSGH, "%s=", _hoops_ASSGH);			\
			_hoops_ISSGH = HI_Sprintf1 (p, pe,"%D,", &_hoops_SIIRS);					\
		} while (0)

#define _hoops_RSSGH(_hoops_ASSGH,	 _hoops_PSSGH, _hoops_HSSGH, _hoops_ISSGH, _hoops_CSSGH) do {			\
			if (_hoops_HSSGH == null)											\
				_hoops_ISSGH = HI_Sprintf1 (_hoops_ISSGH, _hoops_CSSGH, "%s=", _hoops_ASSGH);			\
			_hoops_ISSGH = HI_Sprintf1 (p, pe,"%f,", &_hoops_PSSGH);					\
		} while (0)




local char const * _hoops_ICIRS (
	_hoops_ARGRA	type) {

	switch (type) {
		case M_DIFFUSE:					return "diffuse";
		case M_SPECULAR:				return "specular";
		case M_MIRROR:					return "mirror";
		case M_TRANSMISSION:			return "transmission";
		case M_EMISSION:				return "emission";
		case _hoops_RAGRA:					return "gloss";
		case _hoops_AAGRA:					return "index";
		case _hoops_SIARA:			return "bump";
		case _hoops_GCARA:		return "environment";

		default: {
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
									"Can't choose color channel name");
			return "oops";
		}
	}
}

local char const * _hoops_CCIRS (
	Color_Object type) {

	switch (type) {
		case Color_FRONT:				return "front";
		case Color_BACK:				return "back";
		case Color_EDGE:				return "edge";
		case Color_LINE:				return "line";
		case Color_VERTEX:				return "marker";
		case Color_MARKER:				return "marker only";
		case Color_TEXT:				return "text";
		case Color_CUT_FACE:			return "cut face";
		case Color_CUT_EDGE:			return "cut edge";
		case Color_WINDOW:				return "window";

		case _hoops_SGARA:	return "simple reflection";

		case _hoops_RRARA:		return "front contrast";
		case _hoops_GRARA:		return "back contrast";
		case Color_EDGE_CONTRAST:		return "edge contrast";
		case Color_LINE_CONTRAST:		return "line contrast";
		case Color_TEXT_CONTRAST:		return "text contrast";
		case Color_VERTEX_CONTRAST:		return "vertex contrast";
		case Color_MARKER_CONTRAST:		return "marker contrast";
		case _hoops_HGARA:	return "cut face contrast";
		case _hoops_PGARA:	return "cut edge contrast";
		case Color_WINDOW_CONTRAST:		return "window contrast";

		case Color_LIGHTING:			return "lighting";
		case _hoops_PRARA:			return "ambient up";
		case _hoops_HRARA:		return "ambient down";

		default: {
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
									"Can't choose color name");
			return "oops";
		}
	}
}

local _hoops_ARGRA _hoops_SCIRS (
	Color_Object				type,
	_hoops_PIGRA const *	lock) {
	int							i;

	if (type < 1<<_hoops_IIGRA) {
		for (i=0; i<_hoops_IIGRA; i++)
			if (type == 1<<i)
				return lock->_hoops_HAA[i];
	}
	else if (type < 1<<_hoops_SSGRA)
		return _hoops_CIGRA;		/* _hoops_CAHAR _hoops_RCA _hoops_CSSC _hoops_CHR _hoops_SAHR '_hoops_GPP' */

	_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
							"Can't choose color name");
	return 0;
}

local char *_hoops_GSIRS (
	char					*_hoops_RHPRA,
	Option_Value const * option,
	_hoops_ARGRA	mask,
	_hoops_ARGRA	value) {
	char					*_hoops_ASAPR = _hoops_RHPRA;
	char					*_hoops_PSAPR = _hoops_RHPRA+256;
	_hoops_ARGRA	next;
	_hoops_ARGRA	_hoops_RSIRS;

	if (option != null)
		_hoops_RSIRS = option->type->id;
	else
		_hoops_RSIRS = ~0;

	mask &= _hoops_CIGRA;
	while (mask != 0) {
		next = _hoops_RIII (mask);

		if (BIT (_hoops_RSIRS, next))
			_hoops_ISIIH (_hoops_ICIRS (next), BIT (value, next), option, _hoops_ASAPR, _hoops_PSAPR);

		mask &= ~next;
	}

	if (_hoops_ASAPR != _hoops_RHPRA && _hoops_ASAPR != null)
		--_hoops_ASAPR;

	return _hoops_ASAPR;
}


local bool _hoops_ASIRS (
	Color_Object			mask,
	_hoops_CACRP *	locks) {
	Color_Object			first = _hoops_RIII (mask);
	int						i = 0;
	int						_hoops_PSGRA = 0;

	for (i=0; i<_hoops_IIGRA; i++) {
		if (first == 1<<i) {
			_hoops_PSGRA = i++;
			break;
		}
	}

	for (; i<_hoops_IIGRA; i++) {
		if (BIT (mask, 1<<i)) {
			if (locks->mask._hoops_HAA[i]  != locks->mask._hoops_HAA[_hoops_PSGRA]  ||
				locks->value._hoops_HAA[i] != locks->value._hoops_HAA[_hoops_PSGRA]) {
				return false;
			}
		}
	}

	return true;
}

local char * _hoops_PSIRS (
	char alter *			_hoops_RHPRA,
	Option_Value const *	option,
	_hoops_CACRP *	locks) {
	Color_Object			mask = locks->mask.color;
	Color_Object			value = locks->value.color;
	char alter *			_hoops_ASAPR = _hoops_RHPRA;
	char const *			_hoops_PSAPR = _hoops_RHPRA + 4096;
	_hoops_ARGRA		_hoops_GRPP;
	_hoops_ARGRA		_hoops_HSIRS;
	Color_Object			next;
	Color_Object			_hoops_RSIRS;
	Option_Value const *	_hoops_AHSAA = null;

	if (option != null) {
		_hoops_RSIRS = option->type->id;
		_hoops_AHSAA = option->value.option_list;
	}
	else
		_hoops_RSIRS = ~0;

	mask &= Color_EVERYTHING;
	/* _hoops_HPCAR _hoops_SGS _hoops_RH _hoops_IIPR _hoops_SRHR _hoops_SSCP _hoops_RAPR _hoops_RSIAR -- _hoops_GA'_hoops_RA _hoops_ISPR _hoops_PHPRA */

	if (ALLBITS (_hoops_RSIRS & mask, Color_GEOMETRY) &&
		_hoops_ASIRS (Color_GEOMETRY, locks)) {
		if (ALLBITS (value, Color_GEOMETRY)) {
			if (option == null)
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)"geometry");

			_hoops_GRPP = _hoops_SCIRS (Color_FRONT, &locks->mask);
			_hoops_HSIRS = _hoops_SCIRS (Color_FRONT, &locks->value);

			if (ANYBIT (_hoops_HSIRS, _hoops_CIGRA)) {
				if (!ALLBITS (_hoops_GRPP & _hoops_HSIRS, _hoops_CIGRA)) {
					if (option == null) {
						*_hoops_ASAPR++ = '=';
						if (_hoops_GRPP != _hoops_RIII (_hoops_GRPP))
							*_hoops_ASAPR++ = '(';
					}

					_hoops_ASAPR = _hoops_GSIRS (_hoops_ASAPR, _hoops_AHSAA, _hoops_GRPP, _hoops_HSIRS);

					if (option == null) {
						if (_hoops_GRPP != _hoops_RIII (_hoops_GRPP))
							*_hoops_ASAPR++ = ')';
					}
				}
			}
			*_hoops_ASAPR++ = ',';

			mask &= ~Color_GEOMETRY;
		}
		else if (ALLBITS (~value, Color_GEOMETRY)) {
			_hoops_ISIIH ("geometry", false, option, _hoops_ASAPR, _hoops_PSAPR);
			mask &= ~Color_GEOMETRY;
		}
	}
	if (ALLBITS (_hoops_RSIRS & mask, Color_POLYGON) &&
		_hoops_ASIRS (Color_POLYGON, locks)) {
		if (ALLBITS (value, Color_POLYGON)) {
			if (option == null)
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)"polygon");

			_hoops_GRPP = _hoops_SCIRS (Color_FRONT, &locks->mask);
			_hoops_HSIRS = _hoops_SCIRS (Color_FRONT, &locks->value);

			if (ANYBIT (_hoops_HSIRS, _hoops_CIGRA)) {
				if (!ALLBITS (_hoops_GRPP & _hoops_HSIRS, _hoops_CIGRA)) {
					if (option == null) {
						*_hoops_ASAPR++ = '=';
						if (_hoops_GRPP != _hoops_RIII (_hoops_GRPP))
							*_hoops_ASAPR++ = '(';
					}

					_hoops_ASAPR = _hoops_GSIRS (_hoops_ASAPR, _hoops_AHSAA, _hoops_GRPP, _hoops_HSIRS);

					if (option == null) {
						if (_hoops_GRPP != _hoops_RIII (_hoops_GRPP))
							*_hoops_ASAPR++ = ')';
					}
				}
			}
			*_hoops_ASAPR++ = ',';

			mask &= ~Color_POLYGON;
		}
		else if (ALLBITS (~value, Color_POLYGON)) {
			_hoops_ISIIH ("polygon", false, option, _hoops_ASAPR, _hoops_PSAPR);
			mask &= ~Color_POLYGON;
		}
	}
	if (ALLBITS (_hoops_RSIRS & mask, Color_FACE) &&
		_hoops_ASIRS (Color_FACE, locks)) {
		if (ALLBITS (value, Color_FACE)) {
			if (option == null)
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)"face");

			_hoops_GRPP = _hoops_SCIRS (Color_FRONT, &locks->mask);
			_hoops_HSIRS = _hoops_SCIRS (Color_FRONT, &locks->value);

			if (ANYBIT (_hoops_HSIRS, _hoops_CIGRA)) {
				if (!ALLBITS (_hoops_GRPP & _hoops_HSIRS, _hoops_CIGRA)) {
					if (option == null) {
						*_hoops_ASAPR++ = '=';
						if (_hoops_GRPP != _hoops_RIII (_hoops_GRPP))
							*_hoops_ASAPR++ = '(';
					}

					_hoops_ASAPR = _hoops_GSIRS (_hoops_ASAPR, _hoops_AHSAA, _hoops_GRPP, _hoops_HSIRS);

					if (option == null) {
						if (_hoops_GRPP != _hoops_RIII (_hoops_GRPP))
							*_hoops_ASAPR++ = ')';
					}
				}
			}
			*_hoops_ASAPR++ = ',';

			mask &= ~Color_FACE;
		}
		else if (ALLBITS (~value, Color_FACE)) {
			_hoops_ISIIH ("face", false, option, _hoops_ASAPR, _hoops_PSAPR);
			mask &= ~Color_FACE;
		}
	}
	if (ALLBITS (_hoops_RSIRS & mask, Color_FACE_CONTRAST) &&
		_hoops_ASIRS (Color_FACE_CONTRAST, locks)) {
		if (ALLBITS (value, Color_FACE_CONTRAST)) {
			if (option == null)
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)"face contrast");

			_hoops_GRPP = _hoops_SCIRS (_hoops_RRARA, &locks->mask);
			_hoops_HSIRS = _hoops_SCIRS (_hoops_RRARA, &locks->value);

			if (ANYBIT (_hoops_HSIRS, _hoops_CIGRA)) {
				if (!ALLBITS (_hoops_GRPP & _hoops_HSIRS, _hoops_CIGRA)) {
					if (option == null) {
						*_hoops_ASAPR++ = '=';
						if (_hoops_GRPP != _hoops_RIII (_hoops_GRPP))
							*_hoops_ASAPR++ = '(';
					}

					_hoops_ASAPR = _hoops_GSIRS (_hoops_ASAPR, _hoops_AHSAA, _hoops_GRPP, _hoops_HSIRS);

					if (option == null) {
						if (_hoops_GRPP != _hoops_RIII (_hoops_GRPP))
							*_hoops_ASAPR++ = ')';
					}
				}
			}
			*_hoops_ASAPR++ = ',';

			mask &= ~Color_FACE;
		}
		else if (ALLBITS (~value, Color_FACE)) {
			_hoops_ISIIH ("face contrast", false, option, _hoops_ASAPR, _hoops_PSAPR);
			mask &= ~Color_FACE;
		}
	}
	if (ALLBITS (_hoops_RSIRS & mask, Color_MARKER|Color_VERTEX) &&
		_hoops_ASIRS (Color_MARKER|Color_VERTEX, locks)) {
		if (ALLBITS (value, Color_MARKER|Color_VERTEX)) {
			if (option == null)
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)"marker");

			_hoops_GRPP = _hoops_SCIRS (Color_MARKER, &locks->mask);
			_hoops_HSIRS = _hoops_SCIRS (Color_MARKER, &locks->value);

			if (ANYBIT (_hoops_HSIRS, _hoops_CIGRA)) {
				if (!ALLBITS (_hoops_GRPP & _hoops_HSIRS, _hoops_CIGRA)) {
					if (option == null) {
						*_hoops_ASAPR++ = '=';
						if (_hoops_GRPP != _hoops_RIII (_hoops_GRPP))
							*_hoops_ASAPR++ = '(';
					}

					_hoops_ASAPR = _hoops_GSIRS (_hoops_ASAPR, _hoops_AHSAA, _hoops_GRPP, _hoops_HSIRS);

					if (option == null) {
						if (_hoops_GRPP != _hoops_RIII (_hoops_GRPP))
							*_hoops_ASAPR++ = ')';
					}
				}
			}
			*_hoops_ASAPR++ = ',';

			mask &= ~(Color_MARKER|Color_VERTEX);
		}
		else if (ALLBITS (~value, Color_MARKER|Color_VERTEX)) {
			_hoops_ISIIH ("marker", false, option, _hoops_ASAPR, _hoops_PSAPR);
			mask &= ~(Color_MARKER|Color_VERTEX);
		}
	}
	if (ALLBITS (_hoops_RSIRS & mask, Color_CUT_GEOMETRY) &&
		_hoops_ASIRS (Color_CUT_GEOMETRY, locks)) {
		if (ALLBITS (value, Color_CUT_GEOMETRY)) {
			if (option == null)
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)"cut geometry");

			_hoops_GRPP = _hoops_SCIRS (Color_CUT_EDGE, &locks->mask);
			_hoops_HSIRS = _hoops_SCIRS (Color_CUT_EDGE, &locks->value);

			if (ANYBIT (_hoops_HSIRS, _hoops_CIGRA)) {
				if (!ALLBITS (_hoops_GRPP & _hoops_HSIRS, _hoops_CIGRA)) {
					if (option == null) {
						*_hoops_ASAPR++ = '=';
						if (_hoops_GRPP != _hoops_RIII (_hoops_GRPP))
							*_hoops_ASAPR++ = '(';
					}

					_hoops_ASAPR = _hoops_GSIRS (_hoops_ASAPR, _hoops_AHSAA, _hoops_GRPP, _hoops_HSIRS);

					if (option == null) {
						if (_hoops_GRPP != _hoops_RIII (_hoops_GRPP))
							*_hoops_ASAPR++ = ')';
					}
				}
			}
			*_hoops_ASAPR++ = ',';

			mask &= ~Color_CUT_GEOMETRY;
		}
		else if (ALLBITS (~value, Color_GEOMETRY)) {
			_hoops_ISIIH ("cut geometry", false, option, _hoops_ASAPR, _hoops_PSAPR);
			mask &= ~Color_CUT_GEOMETRY;
		}
	}
	if (ALLBITS (_hoops_RSIRS & mask, _hoops_IGARA) &&
		_hoops_ASIRS (_hoops_IGARA, locks)) {
		if (ALLBITS (value, _hoops_IGARA)) {
			if (option == null)
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)"cut geometry contrast");

			_hoops_GRPP = _hoops_SCIRS (_hoops_HGARA, &locks->mask);
			_hoops_HSIRS = _hoops_SCIRS (_hoops_HGARA, &locks->value);

			if (ANYBIT (_hoops_HSIRS, _hoops_CIGRA)) {
				if (!ALLBITS (_hoops_GRPP & _hoops_HSIRS, _hoops_CIGRA)) {
					if (option == null) {
						*_hoops_ASAPR++ = '=';
						if (_hoops_GRPP != _hoops_RIII (_hoops_GRPP))
							*_hoops_ASAPR++ = '(';
					}

					_hoops_ASAPR = _hoops_GSIRS (_hoops_ASAPR, _hoops_AHSAA, _hoops_GRPP, _hoops_HSIRS);

					if (option == null) {
						if (_hoops_GRPP != _hoops_RIII (_hoops_GRPP))
							*_hoops_ASAPR++ = ')';
					}
				}
			}
			*_hoops_ASAPR++ = ',';

			mask &= ~Color_CUT_GEOMETRY;
		}
		else if (ALLBITS (~value, _hoops_IGARA)) {
			_hoops_ISIIH ("cut geometry contrast", false, option, _hoops_ASAPR, _hoops_PSAPR);
			mask &= ~_hoops_IGARA;
		}
	}

	while (mask != Color_NONE) {
		next = _hoops_RIII (mask);

		_hoops_GRPP = _hoops_SCIRS (next, &locks->mask);
		_hoops_HSIRS = _hoops_SCIRS (next, &locks->value);

		if (BIT (_hoops_RSIRS, next)) {
			char const *		name = _hoops_CCIRS (next);

			if (BIT (value, next) && ANYBIT (_hoops_HSIRS, _hoops_CIGRA)) {
				if (option == null)
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)_hoops_CCIRS (next));

				if (!ALLBITS (_hoops_GRPP & _hoops_HSIRS, _hoops_CIGRA)) {
					if (option == null) {
						*_hoops_ASAPR++ = '=';
						if (_hoops_GRPP != _hoops_RIII (_hoops_GRPP))
							*_hoops_ASAPR++ = '(';
					}

					_hoops_ASAPR = _hoops_GSIRS (_hoops_ASAPR, _hoops_AHSAA, _hoops_GRPP, _hoops_HSIRS);

					if (option == null) {
						if (_hoops_GRPP != _hoops_RIII (_hoops_GRPP))
							*_hoops_ASAPR++ = ')';
					}
				}
				*_hoops_ASAPR++ = ',';
			}
			else
				_hoops_ISIIH (name, false, option, _hoops_ASAPR, _hoops_PSAPR);
		}
		mask &= ~next;
	}

	if (_hoops_ASAPR != _hoops_RHPRA && _hoops_ASAPR != null)
		--_hoops_ASAPR;

	return _hoops_ASAPR;
}


local const struct _hoops_ISIRS {
	_hoops_ACHR		mask;
	char const			*name;
}		_hoops_CSIRS[] = {
	{T_FACES,					"face"},
	{T_ANY_EDGE,				"edge"},
	{T_LINES,					"line"},
	{T_MARKERS,					"marker only"},
	{T_VERTICES,				"vertex"},
	{T_IMAGES,					"image"},
	{T_TEXT,					"text"},
	{T_STRING_CURSORS,			"string cursor"},
	{T_WINDOWS,					"window"},
	{T_CUTTING_PLANES,			"cutting plane"},
	{T_ANY_LIGHTS,				"lighting"},
	{T_ANY_SHADOW,				"shadows"},
	{T_CUT_GEOMETRY,			"cut geometry"},
	{false, null}};


local char * _hoops_SSIRS (
	char alter *			_hoops_RHPRA,
	Option_Value const *	option,
	_hoops_ACHR				mask,
	_hoops_ACHR				value) {
	char alter *			_hoops_ASAPR = _hoops_RHPRA;
	char const *			_hoops_PSAPR = _hoops_RHPRA + 256;
	struct _hoops_ISIRS const *_hoops_GGCRS = _hoops_CSIRS;
	_hoops_ACHR				_hoops_RSIRS;

	if (option != null)
		_hoops_RSIRS = option->type->id;
	else
		_hoops_RSIRS = ~0;

	/* _hoops_HPCAR _hoops_SGS _hoops_RH _hoops_IIPR _hoops_SRHR _hoops_SSCP _hoops_RAPR _hoops_RSIAR -- _hoops_GA'_hoops_RA _hoops_ISPR _hoops_PHPRA */

	if (ALLBITS (_hoops_RSIRS & mask, _hoops_AAHGP)) {
		if (ALLBITS (value, _hoops_AAHGP)) {
			_hoops_ISIIH ("geometry", true, option, _hoops_ASAPR, _hoops_PSAPR);
			mask &= ~_hoops_AAHGP;
		}
		else if (ALLBITS (~value, _hoops_AAHGP)) {
			_hoops_ISIIH ("geometry", false, option, _hoops_ASAPR, _hoops_PSAPR);
			mask &= ~_hoops_AAHGP;
		}
	}
	if (ALLBITS (_hoops_RSIRS & mask, T_FACES|T_ANY_EDGE)) {
		if (ALLBITS (value, T_FACES|T_ANY_EDGE)) {
			_hoops_ISIIH ("polygon", true, option, _hoops_ASAPR, _hoops_PSAPR);
			mask &= ~(T_FACES|T_ANY_EDGE);
		}
		else if (ALLBITS (~value, T_FACES|T_ANY_EDGE)) {
			_hoops_ISIIH ("polygon", false, option, _hoops_ASAPR, _hoops_PSAPR);
			mask &= ~(T_FACES|T_ANY_EDGE);
		}
	}
	if (ALLBITS (_hoops_RSIRS & mask, T_MARKERS|T_VERTICES)) {
		if (ALLBITS (value, T_MARKERS|T_VERTICES)) {
			_hoops_ISIIH ("marker", true, option, _hoops_ASAPR, _hoops_PSAPR);
			mask &= ~(T_MARKERS|T_VERTICES);
		}
		else if (ALLBITS (~value, T_MARKERS|T_VERTICES)) {
			_hoops_ISIIH ("marker", false, option, _hoops_ASAPR, _hoops_PSAPR);
			mask &= ~(T_MARKERS|T_VERTICES);
		}
	}

	if (mask != false) do if (ANYBIT (_hoops_RSIRS & mask, _hoops_GGCRS->mask)) {
		_hoops_ISIIH (_hoops_GGCRS->name, ALLBITS (value, _hoops_GGCRS->mask), option, _hoops_ASAPR, _hoops_PSAPR);
		mask &= ~_hoops_GGCRS->mask;
	} while ((++_hoops_GGCRS)->mask != 0);

	if (_hoops_ASAPR != _hoops_RHPRA && _hoops_ASAPR != null)
		--_hoops_ASAPR;

	return _hoops_ASAPR;
}


local char * _hoops_RGCRS (
	char *							p,
	Option_Value const *			option,
	_hoops_CACRP *			locks,
	bool							_hoops_AGCRS) {
	_hoops_HHAGP					mask = locks->mask._hoops_IPPGR,
									value = locks->value._hoops_IPPGR;
	struct _hoops_RIIRS const *	_hoops_RRCI = _hoops_AIIRS;
	_hoops_HHAGP					_hoops_RSIRS;

	if (option != null)
		_hoops_RSIRS = option->type->id;
	else
		_hoops_RSIRS = ~0U;

	if (mask != false) do {
		if (BIT (_hoops_RSIRS & mask, _hoops_RRCI->mask) &&
			(_hoops_AGCRS || BIT (value, _hoops_RRCI->mask))) {
			if (option == null) {
				if (!BIT (value, _hoops_RRCI->mask)) {
					*p++ = 'n';
					*p++ = 'o';
					*p++ = ' ';
				}

				p = HI_Copy_Chars (_hoops_RRCI->name.text, p);
			}

			if (BIT (value, _hoops_RRCI->mask)) {
				if (_hoops_RRCI->mask == _hoops_GGCAA(HK_COLOR)) {
					Color_Object			_hoops_RAIH = locks->mask.color,
											_hoops_PGCRS = locks->value.color;
					Option_Value const *	_hoops_AHSAA = null;

					if (option != null)
						_hoops_AHSAA = option->value.option_list;

					if (_hoops_AHSAA != null ||
						(_hoops_RAIH & _hoops_PGCRS) != (Color_EVERYTHING & ~Color_CUT_GEOMETRY) ||
						!_hoops_ASIRS (Color_EVERYTHING & ~Color_CUT_GEOMETRY, locks)) {

						bool			_hoops_HISCA;

						/* _hoops_HCAAA _hoops_GSIPR-_hoops_IGRH _hoops_RPPCR _hoops_GAR _hoops_IRS _hoops_RSRA _hoops_IGRH _hoops_HA _hoops_IS _hoops_CACH _hoops_RPP _hoops_SR _hoops_HS
						 * _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_CGRIR _hoops_HCSP
						 */
						if (ALLBITS (_hoops_RAIH, Color_GEOMETRY) &&
							_hoops_ASIRS (Color_GEOMETRY, locks))
							_hoops_RAIH &= ~(Color_GEOMETRY & ~Color_FACE);
						if (ALLBITS (_hoops_RAIH, Color_POLYGON) &&
							_hoops_ASIRS (Color_POLYGON, locks))
							_hoops_RAIH &= ~(Color_POLYGON & ~Color_FACE);
						if (ALLBITS (_hoops_RAIH, Color_FACE) &&
							_hoops_ASIRS (Color_FACE, locks))
							_hoops_RAIH &= ~(Color_FACE & ~Color_FRONT);
						if (ALLBITS (_hoops_RAIH, Color_FACE_CONTRAST) &&
							_hoops_ASIRS (Color_FACE_CONTRAST, locks))
							_hoops_RAIH &= ~(Color_FACE_CONTRAST & ~_hoops_RRARA);
						if (ALLBITS (_hoops_RAIH, Color_MARKER|Color_VERTEX) &&
							_hoops_ASIRS (Color_MARKER|Color_VERTEX, locks))
							_hoops_RAIH &= ~Color_VERTEX;
						if (ALLBITS (_hoops_RAIH, Color_CUT_GEOMETRY) &&
							_hoops_ASIRS (Color_CUT_GEOMETRY, locks))
							_hoops_RAIH &= ~(Color_CUT_GEOMETRY & ~Color_CUT_EDGE);
						if (ALLBITS (_hoops_RAIH, _hoops_IGARA) &&
							_hoops_ASIRS (_hoops_IGARA, locks))
							_hoops_RAIH &= ~(_hoops_IGARA & ~_hoops_PGARA);

						_hoops_HISCA = _hoops_RAIH != _hoops_RIII (_hoops_RAIH);

						if (option == null && _hoops_RAIH != 0) {
							*p++ = '=';
							if (_hoops_HISCA)
								*p++ = '(';
						}

						p = _hoops_PSIRS (p, _hoops_AHSAA, locks);

						if (option == null && _hoops_RAIH != 0) {
							if (_hoops_HISCA)
								*p++ = ')';
						}
					}
				}
				else if (_hoops_RRCI->mask == _hoops_GGCAA(HK_VISIBILITY)) {
					_hoops_ACHR				_hoops_HGCRS = locks->mask._hoops_RGP,
											_hoops_IGCRS = locks->value._hoops_RGP;
					Option_Value const *	_hoops_AHSAA = null;

					if (option != null)
						_hoops_AHSAA = option->value.option_list;

					if (_hoops_AHSAA != null ||
						!ALLBITS (_hoops_HGCRS & _hoops_IGCRS, _hoops_CAHGP)) {

						_hoops_ACHR		_hoops_CGCRS = _hoops_HGCRS;
						bool			_hoops_HISCA;

						/* _hoops_HCAAA _hoops_GSIPR-_hoops_IGRH _hoops_RPPCR _hoops_GAR _hoops_IRS _hoops_RSRA _hoops_IGRH _hoops_HA _hoops_IS _hoops_CACH _hoops_RPP _hoops_SR _hoops_HS
						 * _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_CGRIR _hoops_HCSP
						 */
						if (ALLBITS (_hoops_CGCRS, _hoops_AAHGP))
							_hoops_CGCRS &= ~(_hoops_AAHGP & ~T_FACES);
						if (ALLBITS (_hoops_CGCRS, T_FACES|T_ANY_EDGE))
							_hoops_CGCRS &= ~T_ANY_EDGE;
						if (ALLBITS (_hoops_CGCRS, T_MARKERS|T_VERTICES))
							_hoops_CGCRS &= ~T_VERTICES;

						_hoops_HISCA = _hoops_CGCRS != _hoops_RIII (_hoops_CGCRS);

						if (option == null && _hoops_HGCRS != 0) {
							*p++ = '=';
							if (_hoops_HISCA)
								*p++ = '(';
						}

						p = _hoops_SSIRS (p, _hoops_AHSAA, _hoops_HGCRS, _hoops_IGCRS);

						if (option == null && _hoops_HGCRS != 0) {
							if (_hoops_HISCA)
								*p++ = ')';
						}
					}
				}
				else if (option != null)
					p = HI_Copy_Chars ("on", p);
			}
			else if (option != null)
				p = HI_Copy_Chars ("off", p);

			*p++ = ',';
		}
	} while ((++_hoops_RRCI)->mask != 0);

	return	--p;
}




local char * _hoops_SGCRS (
	_hoops_RHAIR const *	_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	_hoops_GPCRP			mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (BIT (mask & _hoops_RCIHP->_hoops_AIAIR->mask, _hoops_RCCI))
		_hoops_ISIIH ("visibility",
					  BIT (_hoops_RCIHP->_hoops_AIAIR->value, _hoops_RCCI),
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_AIAIR->mask, _hoops_RPCRP))
		_hoops_HIIRS ("pattern",
					 BIT (_hoops_RCIHP->_hoops_AIAIR->value, _hoops_RPCRP),
					 _hoops_RCIHP->_hoops_AIAIR->_hoops_PIAIR.text,
					 option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_AIAIR->mask, _hoops_GHCRP)) {
		char			tmp[64];

		tmp[0] = '\0';
		if (BIT (_hoops_RCIHP->_hoops_AIAIR->value, _hoops_GHCRP))
			HI_Format_Generic_Size_String (&_hoops_RCIHP->_hoops_AIAIR->weight, tmp, -1);

		_hoops_HIIRS ("weight",
					 BIT (_hoops_RCIHP->_hoops_AIAIR->value, _hoops_GHCRP),
					 tmp,
					 option, p, pe);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_AIAIR->mask, _hoops_SPCRP)) {
		char			tmp[64];

		tmp[0] = '\0';
		if (BIT (_hoops_RCIHP->_hoops_AIAIR->value, _hoops_SPCRP)) {
			char *			t = tmp;
			char *			_hoops_RHHPH = t + _hoops_GGAPR(tmp);

			t = HI_Sprintf1 (t, _hoops_RHHPH,"R=%f ", &_hoops_RCIHP->_hoops_AIAIR->color.red);
			t = HI_Sprintf1 (t, _hoops_RHHPH,"G=%f ", &_hoops_RCIHP->_hoops_AIAIR->color.green);
			t = HI_Sprintf1 (t, _hoops_RHHPH,"B=%f",	&_hoops_RCIHP->_hoops_AIAIR->color.blue);
			*t = '\0';
		}

		_hoops_HIIRS ("color",
					 BIT (_hoops_RCIHP->_hoops_AIAIR->value, _hoops_SPCRP),
					 tmp,
					 option, p, pe);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_AIAIR->mask, _hoops_APCRP))
		_hoops_RSSGH ("dim factor",
					 _hoops_RCIHP->_hoops_AIAIR->_hoops_IHCRP,
					 option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_AIAIR->mask, _hoops_PPCRP))
		_hoops_RSSGH ("face displacement",
					 _hoops_RCIHP->_hoops_AIAIR->_hoops_CHIH,
					 option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_AIAIR->mask, _hoops_PHCRP))
		_hoops_RSSGH ("transparency cutoff",
					 _hoops_RCIHP->_hoops_AIAIR->_hoops_CHCRP,
					 option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_AIAIR->mask, _hoops_CPCRP))
		_hoops_ISIIH ("silhouette cleanup",
					  BIT (_hoops_RCIHP->_hoops_AIAIR->value, _hoops_CPCRP),
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_AIAIR->mask, _hoops_RHCRP))
		_hoops_ISIIH ("image outline",
					  BIT (_hoops_RCIHP->_hoops_AIAIR->value, _hoops_RHCRP),
					  option, p, pe);

	if (BIT (_hoops_RCIHP->_hoops_AIAIR->mask, _hoops_HPCRP))
		_hoops_ISIIH ("render faces",
					  BIT (_hoops_RCIHP->_hoops_AIAIR->value, _hoops_HPCRP),
					  option, p, pe);
	if (BIT (_hoops_RCIHP->_hoops_AIAIR->mask, _hoops_IPCRP))
		_hoops_ISIIH ("render text",
					  BIT (_hoops_RCIHP->_hoops_AIAIR->value, _hoops_IPCRP),
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_AIAIR->mask, _hoops_AHCRP)) {
		if (option == null)
			p = HI_Copy_Chars ("rendered face sorting algorithm=", p);

		if (BIT (_hoops_RCIHP->_hoops_AIAIR->_hoops_SRI, _hoops_SGAAP))
			p = HI_Copy_Chars ("hardware z buffer,", p);
		else if (BIT (_hoops_RCIHP->_hoops_AIAIR->_hoops_SRI, _hoops_RRAAP))
			p = HI_Copy_Chars ("software z buffer,", p);
		else if (BIT (_hoops_RCIHP->_hoops_AIAIR->_hoops_SRI, _hoops_GRAAP))
			p = HI_Copy_Chars ("painters,", p);
		else if (BIT (_hoops_RCIHP->_hoops_AIAIR->_hoops_SRI, _hoops_HSSS))
			p = HI_Copy_Chars ("z sort only,", p);
		else if (_hoops_RCIHP->_hoops_AIAIR->_hoops_SRI == _hoops_CGAAP)
			p = HI_Copy_Chars ("none,", p);
	}

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}

local char * _hoops_GRCRS (
	_hoops_RHAIR const *		_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	_hoops_GICRP			mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (BIT (mask & _hoops_RCIHP->_hoops_IIAIR->mask, _hoops_RICRP)) {
		_hoops_ISIIH ("visibility",
					  BIT (_hoops_RCIHP->_hoops_IIAIR->_hoops_RGP.value, T_FACES),
					  option, p, pe);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_IIAIR->mask, _hoops_AICRP)) {
		if (option == null)
			p = HI_Copy_Chars ("value adjustment=", p);

		if (_hoops_RCIHP->_hoops_IIAIR->_hoops_CCCRP == _hoops_PCCRP)
			p = HI_Copy_Chars ("none,", p);
		else if (_hoops_RCIHP->_hoops_IIAIR->_hoops_CCCRP == _hoops_HCCRP)
			p = HI_Copy_Chars ("normalized,", p);
		else {
			p = HI_Sprintf1 (p, pe, "explicit=(scale=%f,", &_hoops_RCIHP->_hoops_IIAIR->scale);
			p = HI_Sprintf1 (p, pe, "translate=%f),", &_hoops_RCIHP->_hoops_IIAIR->translate);
		}
	}

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}

local char * _hoops_RRCRS (
	_hoops_RHAIR const *		_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	_hoops_GICRP			mask;
	char							tmp[4096];

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (BIT (mask & _hoops_RCIHP->_hoops_IIAIR->mask, _hoops_HICRP)) {
		_hoops_ISIIH ("visibility",
					  BIT (_hoops_RCIHP->_hoops_IIAIR->_hoops_RGP.value, T_EDGES),
					  option, p, pe);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_IIAIR->mask, _hoops_IICRP)) {
		if (option == null)
			p = HI_Copy_Chars ("position=", p);

		if (_hoops_RCIHP->_hoops_IIAIR->_hoops_RSCRP == _hoops_SCCRP) {
			if (_hoops_RCIHP->_hoops_IIAIR->_hoops_SIAIR == null ||
				_hoops_RCIHP->_hoops_IIAIR->_hoops_SIAIR[0] == 1.0f &&
				_hoops_RCIHP->_hoops_IIAIR->_hoops_SIAIR[1] == 0.0f)
				p = HI_Copy_Chars ("default,", p);
			else {
				p = HI_Sprintf1 (p, pe, "repeat=(interval=%f,", &_hoops_RCIHP->_hoops_IIAIR->_hoops_SIAIR[0]);
				p = HI_Sprintf1 (p, pe, "offset=%f),", &_hoops_RCIHP->_hoops_IIAIR->_hoops_SIAIR[1]);
			}
		}
		else {
			p = HI_Copy_Chars ("explicit=", p);
			if (_hoops_RCIHP->_hoops_IIAIR->_hoops_CIAIR > 1)
				p = HI_Copy_Chars ("(", p);
			for (int i=0; i<_hoops_RCIHP->_hoops_IIAIR->_hoops_CIAIR; i++)
				p = HI_Sprintf1 (p, pe, "%f,", &_hoops_RCIHP->_hoops_IIAIR->_hoops_SIAIR[i]);
			--p;
			if (_hoops_RCIHP->_hoops_IIAIR->_hoops_CIAIR > 1)
				p = HI_Copy_Chars (")", p);
			p = HI_Copy_Chars (",", p);
		}
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_IIAIR->mask, _hoops_CICRP)) {
		tmp[0] = '\0';
		if (BIT (_hoops_RCIHP->_hoops_IIAIR->value, _hoops_CICRP)) {
			char *			t = tmp;
			char *			_hoops_RHHPH = t + _hoops_GGAPR(tmp);

			if (_hoops_RCIHP->_hoops_IIAIR->_hoops_GCAIR > 1)
				t = HI_Copy_Chars ("(", t);
			for (int i=0; i<_hoops_RCIHP->_hoops_IIAIR->_hoops_GCAIR; i++) {
				if (_hoops_RCIHP->_hoops_IIAIR->colors[i].red == -1.0f)
					t = HI_Copy_Chars ("*,", t);
				else if (_hoops_RCIHP->_hoops_IIAIR->colors[i].red == -1.0f)
					t = HI_Copy_Chars ("-,", t);
				else {
					t = HI_Sprintf1 (t, _hoops_RHHPH, "R=%f ", &_hoops_RCIHP->_hoops_IIAIR->colors[i].red);
					t = HI_Sprintf1 (t, _hoops_RHHPH, "G=%f ", &_hoops_RCIHP->_hoops_IIAIR->colors[i].green);
					t = HI_Sprintf1 (t, _hoops_RHHPH, "B=%f,", &_hoops_RCIHP->_hoops_IIAIR->colors[i].blue);
				}
			}
			--t;
			if (_hoops_RCIHP->_hoops_IIAIR->_hoops_GCAIR > 1)
				t = HI_Copy_Chars (")", t);
			*t = '\0';
		}

		_hoops_HIIRS ("colors",
					 BIT (_hoops_RCIHP->_hoops_IIAIR->value, _hoops_CICRP),
					 tmp,
					 option, p, pe);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_IIAIR->mask, _hoops_SICRP)) {
		tmp[0] = '\0';
		if (BIT (_hoops_RCIHP->_hoops_IIAIR->value, _hoops_SICRP)) {
			char *			t = tmp;
			char *			_hoops_RHHPH = t + _hoops_GGAPR(tmp);

			if (_hoops_RCIHP->_hoops_IIAIR->_hoops_RCAIR > 1)
				t = HI_Copy_Chars ("(", t);
			for (int i=0; i<_hoops_RCIHP->_hoops_IIAIR->_hoops_RCAIR; i++) {
				if (_hoops_RCIHP->_hoops_IIAIR->_hoops_ACAIR[i].length == 0)
					t = HI_Copy_Chars ("*,", t);
				else
					t = HI_Sprintf1 (t, _hoops_RHHPH, "%s,", _hoops_RCIHP->_hoops_IIAIR->_hoops_ACAIR[i].text);
			}
			--t;
			if (_hoops_RCIHP->_hoops_IIAIR->_hoops_RCAIR > 1)
				t = HI_Copy_Chars (")", t);
			*t = '\0';
		}

		_hoops_HIIRS ("patterns",
					 BIT (_hoops_RCIHP->_hoops_IIAIR->value, _hoops_RPCRP),
					 tmp,
					 option, p, pe);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_IIAIR->mask, _hoops_GCCRP)) {
		char		_hoops_ARCRS[64];

		tmp[0] = '\0';
		if (BIT (_hoops_RCIHP->_hoops_IIAIR->value, _hoops_GCCRP)) {
			char *			t = tmp;
			char *			_hoops_RHHPH = t + _hoops_GGAPR(tmp);

			if (_hoops_RCIHP->_hoops_IIAIR->weight_count > 1)
				t = HI_Copy_Chars ("(", t);
			for (int i=0; i<_hoops_RCIHP->_hoops_IIAIR->weight_count; i++) {
				if (_hoops_RCIHP->_hoops_IIAIR->weights[i]._hoops_HHP == -1)
					t = HI_Copy_Chars ("*,", t);
				else {
					HI_Format_Generic_Size_String (&_hoops_RCIHP->_hoops_IIAIR->weights[i], _hoops_ARCRS, -1);
					t = HI_Sprintf1 (t, _hoops_RHHPH, "%s,", _hoops_ARCRS);
				}
			}
			--t;
			if (_hoops_RCIHP->_hoops_IIAIR->weight_count > 1)
				t = HI_Copy_Chars (")", t);
			*t = '\0';
		}

		_hoops_HIIRS ("weights",
					 BIT (_hoops_RCIHP->_hoops_IIAIR->value, _hoops_GCCRP),
					 tmp,
					 option, p, pe);
	}


	if (BIT (mask & _hoops_RCIHP->_hoops_IIAIR->mask, _hoops_RCCRP))
		_hoops_ISIIH ("lighting",
					  BIT (_hoops_RCIHP->_hoops_IIAIR->value, _hoops_RCCRP),
					  option, p, pe);

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}

local char * _hoops_PRCRS (
	_hoops_RHAIR const *		_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	_hoops_GICRP			mask;
	char							tmp[4096];

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (BIT (mask & _hoops_RCIHP->_hoops_SHAAP, _hoops_CHRH)) {
		if (BIT (_hoops_RCIHP->_hoops_GIAAP, _hoops_CHRH))
			p = HI_Copy_Chars ("on,", p);
		else
			p = HI_Copy_Chars ("off,", p);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_SHAAP, _hoops_AIGRP)) {
		if (option == null)
			p = HI_Copy_Chars ("range=", p);

		float		min = _hoops_RCIHP->_hoops_IHRH.translate;
		float		max = min + _hoops_RCIHP->_hoops_IHRH.scale;

		p = HI_Sprintf1 (p, pe, "(%f,", &min);
		p = HI_Sprintf1 (p, pe, "%f),", &max);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_SHAAP, _hoops_PIGRP)) {
		char *			t = tmp;
		char *			_hoops_RHHPH = t + _hoops_GGAPR(tmp);
		tmp[0] = '\0';

		t = HI_Sprintf1 (t, _hoops_RHHPH, "R=%f ", &_hoops_RCIHP->_hoops_IHRH.color.red);
		t = HI_Sprintf1 (t, _hoops_RHHPH, "G=%f ", &_hoops_RCIHP->_hoops_IHRH.color.green);
		t = HI_Sprintf1 (t, _hoops_RHHPH, "B=%f",  &_hoops_RCIHP->_hoops_IHRH.color.blue);
		*t = '\0';

		_hoops_HIIRS ("color",
					 BIT (_hoops_RCIHP->_hoops_GIAAP, _hoops_PIGRP),
					 tmp,
					 option, p, pe);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_SHAAP, _hoops_HIGRP)) {
		if (option == null)
			p = HI_Copy_Chars ("effect=", p);

		switch (_hoops_RCIHP->_hoops_IHRH._hoops_ACGRP) {
			case _hoops_CIGRP:				p = HI_Copy_Chars ("grayscale,", p);			break;
			case _hoops_SIGRP:				p = HI_Copy_Chars ("modulate,", p);				break;
			case _hoops_GCGRP:	p = HI_Copy_Chars ("modulate grayscale,", p);	break;
			case _hoops_RCGRP:					p = HI_Copy_Chars ("tone,", p);					break;
		}
	}

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}

local char * _hoops_HRCRS (
	_hoops_RHAIR const *	_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	_hoops_HGGAP			mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_PGGAP)) {
		if (_hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS._hoops_RGP == _hoops_CRGAP)
			p = HI_Copy_Chars ("auto,", p);
		else if (BIT (_hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS.value, _hoops_PGGAP))
			p = HI_Copy_Chars ("on,", p);
		else
			p = HI_Copy_Chars ("off,", p);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_IGGAP)) {
		_hoops_ARPA const *		plane;

		if (option == null)
			p = HI_Copy_Chars ("plane=(", p);

		plane = &_hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS.plane;
		p = HI_Sprintf1 (p, pe, "%f,", &plane->a);
		p = HI_Sprintf1 (p, pe, "%f,", &plane->b);
		p = HI_Sprintf1 (p, pe, "%f,", &plane->c);
		p = HI_Sprintf1 (p, pe, "%f",  &plane->d);

		if (option == null)
			p = HI_Copy_Chars (")", p);
		p = HI_Copy_Chars (",", p);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_CGGAP)) {
		Vector const *		light;

		if (option == null)
			p = HI_Copy_Chars ("light=(", p);

		light = &_hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS.light;
		p = HI_Sprintf1 (p, pe, "%f,", &light->x);
		p = HI_Sprintf1 (p, pe, "%f,", &light->y);
		p = HI_Sprintf1 (p, pe, "%f",  &light->z);

		if (option == null)
			p = HI_Copy_Chars (")", p);
		p = HI_Copy_Chars (",", p);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_SGGAP)) {
		int		i;

		if (option == null)
			p = HI_Copy_Chars ("color=", p);

		for (i=0; i<_hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS.color.name.length; ++i)
			if (_hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS.color.name.text[i] == '=')
				break;

		if (i != _hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS.color.name.length)
			p = HI_Sprintf1 (p, pe, "'%n',",
							 &_hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS.color.name);
		else
			p = HI_Sprintf1 (p, pe, "%n,",
							 &_hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS.color.name);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_GRGAP))
		_hoops_RSSGH ("opacity",
					 _hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS._hoops_IRIR,
					 option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_RRGAP))
		_hoops_PCIRS ("resolution",
					 _hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS._hoops_HAP,
					 option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_ARGAP))
		_hoops_PCIRS ("blurring",
					 _hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS._hoops_IGGGR,
					 option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_PRGAP))
		_hoops_ISIIH ("ignore transparency",
					  BIT (_hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS.value, _hoops_PRGAP),
					  option, p, pe);


	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}

local char * _hoops_IRCRS (
	_hoops_RHAIR const *	_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	_hoops_RAGAP				mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_HRR.mask, _hoops_GAGAP)) {
		if (BIT (_hoops_RCIHP->_hoops_HHAIR->_hoops_HRR.value, _hoops_GAGAP))
			p = HI_Copy_Chars ("on,", p);
		else
			p = HI_Copy_Chars ("off,", p);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_HRR.mask, _hoops_AAGAP)) {
		if (BIT (_hoops_RCIHP->_hoops_HHAIR->_hoops_HRR.value, _hoops_AAGAP))
			p = HI_Copy_Chars ("jitter,", p);
		else
			p = HI_Copy_Chars ("no jitter,", p);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_HRR.mask, _hoops_IAGAP)) {
		if (BIT (_hoops_RCIHP->_hoops_HHAIR->_hoops_HRR.value, _hoops_IAGAP))
			p = HI_Copy_Chars ("view dependent,", p);
		else
			p = HI_Copy_Chars ("view independent,", p);
	}


	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_HRR.mask, _hoops_PAGAP))
		_hoops_PCIRS ("resolution",
					 _hoops_RCIHP->_hoops_HHAIR->_hoops_HRR._hoops_HAP,
					 option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_HRR.mask, _hoops_HAGAP))
		_hoops_PCIRS ("samples",
					 _hoops_RCIHP->_hoops_HHAIR->_hoops_HRR._hoops_CAP,
					 option, p, pe);

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}

local char * _hoops_CRCRS (
	_hoops_RHAIR const *	_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	_hoops_SAGAP		mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_CAGAP)) {
		if (BIT (_hoops_RCIHP->_hoops_HHAIR->_hoops_RHGGR.value, _hoops_CAGAP))
			p = HI_Copy_Chars ("on,", p);
		else
			p = HI_Copy_Chars ("off,", p);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_GPGAP)) {
		_hoops_ARPA const *		plane;

		if (option == null)
			p = HI_Copy_Chars ("plane=(", p);

		plane = &_hoops_RCIHP->_hoops_HHAIR->_hoops_RHGGR.plane;
		p = HI_Sprintf1 (p, pe, "%f,", &plane->a);
		p = HI_Sprintf1 (p, pe, "%f,", &plane->b);
		p = HI_Sprintf1 (p, pe, "%f,", &plane->c);
		p = HI_Sprintf1 (p, pe, "%f",  &plane->d);

		if (option == null)
			p = HI_Copy_Chars (")", p);
		p = HI_Copy_Chars (",", p);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_RPGAP))
		_hoops_RSSGH ("opacity",
					 _hoops_RCIHP->_hoops_HHAIR->_hoops_RHGGR._hoops_IRIR,
					 option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_APGAP))
		_hoops_ISIIH ("fading",
					  BIT (_hoops_RCIHP->_hoops_HHAIR->_hoops_RHGGR.value, _hoops_APGAP),
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_HPGAP))
		if (BIT (_hoops_RCIHP->_hoops_HHAIR->_hoops_RHGGR.value, _hoops_HPGAP))
			p = HI_Sprintf1 (p, pe, "blur=%d,", (void *)&_hoops_RCIHP->_hoops_HHAIR->_hoops_RHGGR._hoops_IGGGR);
		else
			p = HI_Copy_Chars ("no blur,", p);

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_PPGAP)) {
		p = HI_Sprintf1 (p, pe, "attenuation=(hither=%f,",
						 (void *)&_hoops_RCIHP->_hoops_HHAIR->_hoops_RHGGR.hither);
		p = HI_Sprintf1 (p, pe, "yon=%f),",
						 (void *)&_hoops_RCIHP->_hoops_HHAIR->_hoops_RHGGR.yon);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_IPGAP)) {
		_hoops_ACHR				_hoops_HGCRS = _hoops_RCIHP->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.mask,
								_hoops_IGCRS = _hoops_RCIHP->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.value;
		Option_Value const *	_hoops_AHSAA = null;

		if (option == null)
			p = HI_Copy_Chars ("visibility", p);
		else
			_hoops_AHSAA = option->value.option_list;

		if (_hoops_AHSAA != null ||
			!ALLBITS (_hoops_HGCRS & _hoops_IGCRS, _hoops_CAHGP)) {

			_hoops_ACHR		_hoops_CGCRS = _hoops_HGCRS;
			bool			_hoops_HISCA;

			/* _hoops_HCAAA _hoops_GSIPR-_hoops_IGRH _hoops_RPPCR _hoops_GAR _hoops_IRS _hoops_RSRA _hoops_IGRH _hoops_HA _hoops_IS _hoops_CACH _hoops_RPP _hoops_SR _hoops_HS
			 * _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_CGRIR _hoops_HCSP
			 */
			if (ALLBITS (_hoops_CGCRS, _hoops_AAHGP))
				_hoops_CGCRS &= ~(_hoops_AAHGP & ~T_FACES);
			if (ALLBITS (_hoops_CGCRS, T_FACES|T_ANY_EDGE))
				_hoops_CGCRS &= ~T_ANY_EDGE;
			if (ALLBITS (_hoops_CGCRS, T_MARKERS|T_VERTICES))
				_hoops_CGCRS &= ~T_VERTICES;

			_hoops_HISCA = _hoops_CGCRS != _hoops_RIII (_hoops_CGCRS);

			if (option == null && _hoops_HGCRS != 0) {
				*p++ = '=';
				if (_hoops_HISCA)
					*p++ = '(';
			}

			p = _hoops_SSIRS (p, _hoops_AHSAA, _hoops_HGCRS, _hoops_IGCRS);

			if (option == null && _hoops_HGCRS != 0) {
				if (_hoops_HISCA)
					*p++ = ')';
			}
		}
		*p++ = ',';
	}

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}

local char * _hoops_SRCRS (
	_hoops_RHAIR const *	_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	_hoops_ASSRP			mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_PRIGA.mask, _hoops_RSSRP)) {
		if (option == null)
			p = HI_Copy_Chars ("level=", p);

		if (_hoops_RCIHP->_hoops_HHAIR->_hoops_PRIGA.level == _hoops_AHIGA)
			p = HI_Copy_Chars ("entity,", p);
		else if (_hoops_RCIHP->_hoops_HHAIR->_hoops_PRIGA.level == _hoops_SSSRP)
			p = HI_Copy_Chars ("segment,", p);
		else if (_hoops_RCIHP->_hoops_HHAIR->_hoops_PRIGA.level == _hoops_GGGAP)
			p = HI_Copy_Chars ("segment tree,", p);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_PRIGA.mask, _hoops_PSSRP)) {
		if (option == null)
			p = HI_Copy_Chars ("tolerance=", p);

		p = HI_Sprintf1 (p, pe, "%f",
						 (void *)&_hoops_RCIHP->_hoops_HHAIR->_hoops_PRIGA.tolerance);
		if (BIT (_hoops_RCIHP->_hoops_HHAIR->_hoops_PRIGA.value, _hoops_ISSRP))
			p = HI_Copy_Chars ("%", p);
		p = HI_Copy_Chars (",", p);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_PRIGA.mask, _hoops_HSSRP)) {
		char const *		tmp = null;

		if (BIT (_hoops_RCIHP->_hoops_HHAIR->_hoops_PRIGA.value, _hoops_HSSRP)) {
			switch (_hoops_RCIHP->_hoops_HHAIR->_hoops_PRIGA._hoops_SRIGA) {
				case _hoops_GAIGA:		tmp = "first";	break;
				case _hoops_AAIGA:		tmp = "last";	break;
				case _hoops_AGGAP:	tmp = "current";	break;
				case _hoops_RGGAP:	tmp = "off";	break;
			}
		}

		_hoops_HIIRS ("match color",
					 BIT (_hoops_RCIHP->_hoops_HHAIR->_hoops_PRIGA.value, _hoops_HSSRP),
					 tmp,
					 option, p, pe);
	}

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}

local char * _hoops_GACRS (
	_hoops_RHAIR const *	_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	_hoops_PPAAP					mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (BIT (mask & _hoops_RCIHP->_hoops_RGICA.mask, _hoops_HPAAP)) {
		char		tmp[64];

		tmp[0] = '\0';
		if (BIT (_hoops_RCIHP->_hoops_RGICA.value, _hoops_HPAAP)) {
			if (_hoops_RCIHP->_hoops_RGICA._hoops_SPAAP < 0)
				Sprintf_D (tmp, "%d bytes", -_hoops_RCIHP->_hoops_RGICA._hoops_SPAAP);
			else
				Sprintf_D (tmp, "%d rasters", _hoops_RCIHP->_hoops_RGICA._hoops_SPAAP);
		}

		_hoops_HIIRS ("size limit",
					  BIT (_hoops_RCIHP->_hoops_RGICA.value, _hoops_HPAAP),
					  tmp,
					  option, p, pe);
	}
	if (BIT (mask & _hoops_RCIHP->_hoops_RGICA.mask, _hoops_IPAAP)) {
		_hoops_ISIIH ("retention",
					  BIT (_hoops_RCIHP->_hoops_RGICA.value, _hoops_IPAAP),
					  option, p, pe);
	}
	if (BIT (mask & _hoops_RCIHP->_hoops_RGICA.mask, _hoops_CPAAP)) {
		if (option == null)
			p = HI_Copy_Chars ("color depth=", p);

		if (_hoops_RCIHP->_hoops_RGICA._hoops_GHAAP == _hoops_RHAAP)
			p = HI_Copy_Chars ("match device,", p);
		else
			p = HI_Copy_Chars ("full color,", p);
	}

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}

local char * _hoops_RACRS (
	_hoops_RHAIR const *	_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	_hoops_RRPHA					mask;
	int								i, _hoops_AACRS;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (BIT (mask & _hoops_RCIHP->_hoops_PRSI->mask, _hoops_ISCRP)) {
		_hoops_AACRS = 0;
		for (i = 1; i < _hoops_IGAIR; i++)
			if (_hoops_RCIHP->_hoops_PRSI->_hoops_PRPHA[i] != _hoops_RCIHP->_hoops_PRSI->_hoops_PRPHA[i-1])
				_hoops_AACRS = i;

		if (option == null)
			p = HI_Copy_Chars ("ratio=", p);

		if (_hoops_AACRS)
			p = HI_Copy_Chars ("(", p);
		for (i = 0; i <= _hoops_AACRS; i++)
			p = HI_Sprintf1 (p, pe,"%f,", &_hoops_RCIHP->_hoops_PRSI->_hoops_PRPHA[i]);
		if (p != null)
			--p;
		if (_hoops_AACRS)
			p = HI_Copy_Chars (")", p);
		p = HI_Copy_Chars (",", p);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_PRSI->mask, _hoops_IASRP)) {
		_hoops_AACRS = 0;
		for (i = 1; i < _hoops_IGAIR; i++)
			if (_hoops_RCIHP->_hoops_PRSI->_hoops_AISRP[i] != _hoops_RCIHP->_hoops_PRSI->_hoops_AISRP[i-1])
				_hoops_AACRS = i;

		if (option == null)
			p = HI_Copy_Chars ("threshold=", p);

		if (_hoops_AACRS)
			p = HI_Copy_Chars ("(", p);
		for (i = 0; i <= _hoops_AACRS; i++)
			p = HI_Sprintf1 (p, pe,"%f,", &_hoops_RCIHP->_hoops_PRSI->_hoops_AISRP[i]);
		if (p != null)
			--p;

		if (BIT (_hoops_RCIHP->_hoops_PRSI->value, _hoops_SRSRP))
			p = HI_Copy_Chars ("tppix2", p);
		else if (BIT (_hoops_RCIHP->_hoops_PRSI->value, _hoops_RASRP))
			p = HI_Copy_Chars ("% area", p);
		else if (BIT (_hoops_RCIHP->_hoops_PRSI->value, _hoops_CRSRP))
			p = HI_Copy_Chars ("tpcm2", p);
		/* _hoops_SHS _hoops_RPP _hoops_PACRS _hoops_AA _hoops_ISAP */

		if (_hoops_AACRS)
			p = HI_Copy_Chars (")", p);
		p = HI_Copy_Chars (",", p);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_PRSI->mask, _hoops_IRSRP)) {
		if (BIT (_hoops_RCIHP->_hoops_PRSI->value, _hoops_IRSRP)) {
			_hoops_AACRS = 0;
			for (i = 1; i < _hoops_IGAIR; i++)
				if (_hoops_RCIHP->_hoops_PRSI->_hoops_GHRGR[i] !=
						 _hoops_RCIHP->_hoops_PRSI->_hoops_GHRGR[i-1])
					_hoops_AACRS = i;
			if (_hoops_AACRS) {
				p = HI_Sprintf1 (p, pe,
						"calculation usefulness cutoff=(%f",
						&_hoops_RCIHP->_hoops_PRSI->_hoops_GHRGR[0]);
				for (i = 1; i <= _hoops_AACRS; i++)
					p = HI_Sprintf1 (p, pe,",%f",
								&_hoops_RCIHP->_hoops_PRSI->_hoops_GHRGR[i]);
				p = HI_Sprintf1 (p, pe, "%s", "),");
			}
			else
				p = HI_Sprintf1 (p, pe,
						"calculation usefulness cutoff=%f,",
							 &_hoops_RCIHP->_hoops_PRSI->_hoops_GHRGR[0]);
		}
		else
			p = HI_Copy_Chars ("no calculation usefulness cutoff,", p);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_PRSI->mask, _hoops_GRSRP)) {
		char const *		tmp = null;

		if (BIT (_hoops_RCIHP->_hoops_PRSI->value, _hoops_GRSRP)) {
			switch (_hoops_RCIHP->_hoops_PRSI->_hoops_SRHHR) {
				case _hoops_CASRP:	tmp = "diagonal ratio per triangle";	break;
				case _hoops_SASRP:		tmp = "diagonal ratio";					break;
				case _hoops_GPSRP:			tmp = "diagonal per triangle";			break;
				case _hoops_RPSRP:				tmp = "diagonal";						break;
				case _hoops_APSRP:	tmp = "volume ratio per triangle";		break;
				case _hoops_PPSRP:		tmp = "volume ratio";					break;
				case _hoops_HPSRP:			tmp = "volume per triangle";			break;
				case _hoops_IPSRP:				tmp = "volume";							break;
				case _hoops_CPSRP:			tmp = "triangle size";					break;
			}
		}

		_hoops_HIIRS ("usefulness heuristic",
					BIT (_hoops_RCIHP->_hoops_PRSI->value, _hoops_GRSRP),
					tmp,
					option, p, pe);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_PRSI->mask, _hoops_CSCRP))
		_hoops_PCIRS ("min triangle count",
					  _hoops_RCIHP->_hoops_PRSI->_hoops_HISRP,
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_PRSI->mask, _hoops_HASRP))
		_hoops_CIIRS ("clamp",
					  BIT (_hoops_RCIHP->_hoops_PRSI->value, _hoops_HASRP),
					  _hoops_RCIHP->_hoops_PRSI->_hoops_IISRP,
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_PRSI->mask, _hoops_SSCRP))
		_hoops_PCIRS ("num levels",
					  _hoops_RCIHP->_hoops_PRSI->_hoops_IRSH,
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_PRSI->mask, _hoops_GGSRP))
		_hoops_PCIRS ("max degree",
					  _hoops_RCIHP->_hoops_PRSI->_hoops_RHPHA,
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_PRSI->mask, _hoops_IGSRP)) {
		char const *	tmp = null;

		switch (_hoops_RCIHP->_hoops_PRSI->_hoops_ARPHA) {
			case _hoops_SHSRP:	tmp = "fast";	break;
			case _hoops_GISRP:	tmp = "nice";	break;
		}

		_hoops_ACIRS ("algorithm", tmp, option, p, pe);
	}


	if (BIT (mask & _hoops_RCIHP->_hoops_PRSI->mask, _hoops_ASCRP))
		_hoops_ISIIH ("conserve memory",
					  BIT (_hoops_RCIHP->_hoops_PRSI->value, _hoops_ASCRP),
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_PRSI->mask, _hoops_SGSRP))
		_hoops_ISIIH ("preprocess",
					  BIT (_hoops_RCIHP->_hoops_PRSI->value, _hoops_SGSRP),
					  option, p, pe);

	if (ANYBIT (mask & _hoops_RCIHP->_hoops_PRSI->mask, _hoops_HRSRP)) {
		char				tmp[128];

		_hoops_AAHR ("current,", tmp);
		if (_hoops_RCIHP->_hoops_PRSI->value & _hoops_PRSRP) {
			char *		t = tmp;
			char const *_hoops_RHHPH = t + _hoops_GGAPR(tmp);

			t = HI_Sprintf1 (t, _hoops_RHHPH, "(%f,", &_hoops_RCIHP->_hoops_PRSI->bounding->cuboid.min.x);
			t = HI_Sprintf1 (t, _hoops_RHHPH, "%f,",	&_hoops_RCIHP->_hoops_PRSI->bounding->cuboid.min.y);
			t = HI_Sprintf1 (t, _hoops_RHHPH, "%f,",	&_hoops_RCIHP->_hoops_PRSI->bounding->cuboid.min.z);
			t = HI_Sprintf1 (t, _hoops_RHHPH, "%f,",	&_hoops_RCIHP->_hoops_PRSI->bounding->cuboid.max.x);
			t = HI_Sprintf1 (t, _hoops_RHHPH, "%f,",	&_hoops_RCIHP->_hoops_PRSI->bounding->cuboid.max.y);
			t = HI_Sprintf1 (t, _hoops_RHHPH, "%f),", &_hoops_RCIHP->_hoops_PRSI->bounding->cuboid.max.z);
		}

		_hoops_HIIRS ("bounding",
					 ANYBIT (_hoops_RCIHP->_hoops_PRSI->value, _hoops_ARSRP|_hoops_PRSRP),
					 tmp,
					 option, p, pe);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_PRSI->mask, _hoops_PASRP)) {
		char const *		tmp = null;

		switch (_hoops_RCIHP->_hoops_PRSI->_hoops_RCSRP) {
			case _hoops_SPSRP:					tmp = "none";		break;
			case _hoops_GHSRP:				tmp = "bounding";			break;
			case _hoops_RHSRP:				tmp = "coarsest";			break;
			case _hoops_AHSRP:		tmp = "coarsest none";		break;
			case _hoops_IHSRP:	tmp = "coarsest bounding";	break;
			case _hoops_CHSRP:		tmp = "bounding none";		break;
		}

		_hoops_HIIRS ("fallback",
					 _hoops_RCIHP->_hoops_PRSI->_hoops_RCSRP != 0,
					 tmp,
					 option, p, pe);
	}
	if (BIT (mask & _hoops_RCIHP->_hoops_PRSI->mask, _hoops_RGSRP))
		_hoops_ISIIH ("collapse duplicate vertices",
					  BIT (_hoops_RCIHP->_hoops_PRSI->value, _hoops_RGSRP),
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_PRSI->mask, _hoops_CGSRP)) {
		char const *		tmp = "geometry";

		if (BIT (_hoops_RCIHP->_hoops_PRSI->value, _hoops_CGSRP))
			tmp = "segment";

		_hoops_ACIRS ("mode", tmp, option, p, pe);
	}

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}

local char * _hoops_HACRS (
	_hoops_RHAIR const *	_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	_hoops_IHGAP			mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (BIT (mask & _hoops_RCIHP->geometry->_hoops_APPI.mask, _hoops_HHGAP))
		_hoops_ISIIH ("view dependent",
					  BIT (_hoops_RCIHP->geometry->_hoops_APPI.value, _hoops_HHGAP),
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->geometry->_hoops_APPI.mask, _hoops_CHGAP))
		_hoops_PCIRS ("budget",
					  _hoops_RCIHP->geometry->_hoops_APPI._hoops_PPPI,
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->geometry->_hoops_APPI.mask, _hoops_SHGAP))
		_hoops_CIIRS ("continued budget",
					  BIT (_hoops_RCIHP->geometry->_hoops_APPI.value, _hoops_SHGAP),
					  _hoops_RCIHP->geometry->_hoops_APPI._hoops_HPPI,
					  option, p, pe);
	if (BIT (mask & _hoops_RCIHP->geometry->_hoops_APPI.mask, _hoops_GIGAP))
		_hoops_RSSGH("max deviation",
					  _hoops_RCIHP->geometry->_hoops_APPI._hoops_IPPI,
					  option, p, pe);
	if (BIT (mask & _hoops_RCIHP->geometry->_hoops_APPI.mask, _hoops_RIGAP))
		_hoops_RSSGH("max angle",
					  _hoops_RCIHP->geometry->_hoops_APPI._hoops_CPPI,
					  option, p, pe);
	if (BIT (mask & _hoops_RCIHP->geometry->_hoops_APPI.mask, _hoops_AIGAP))
		_hoops_RSSGH("max length",
					  _hoops_RCIHP->geometry->_hoops_APPI._hoops_SPPI,
					  option, p, pe);

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}


local char * _hoops_IACRS (
	_hoops_RHAIR const *	_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	_hoops_HIGAP			mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (BIT (mask & _hoops_RCIHP->geometry->_hoops_PSRIR.mask, _hoops_PIGAP))
		_hoops_RSSGH ("max trim curve deviation",
					  _hoops_RCIHP->geometry->_hoops_PSRIR.configs._hoops_GGIRP,
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->geometry->_hoops_PSRIR.mask, _hoops_IIGAP))
		_hoops_PCIRS ("trim curve budget",
					  _hoops_RCIHP->geometry->_hoops_PSRIR.configs._hoops_CSHRP,
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->geometry->_hoops_PSRIR.mask, _hoops_CIGAP))
		_hoops_RSSGH ("max facet deviation",
					  _hoops_RCIHP->geometry->_hoops_PSRIR.configs._hoops_RGIRP,
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->geometry->_hoops_PSRIR.mask, _hoops_SIGAP))
		_hoops_RSSGH ("max facet angle",
					  _hoops_RCIHP->geometry->_hoops_PSRIR.configs._hoops_AGIRP,
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->geometry->_hoops_PSRIR.mask, _hoops_GCGAP))
		_hoops_RSSGH ("max facet width",
					  _hoops_RCIHP->geometry->_hoops_PSRIR.configs._hoops_PGIRP,
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->geometry->_hoops_PSRIR.mask, _hoops_RCGAP))
		_hoops_PCIRS ("budget",
					  _hoops_RCIHP->geometry->_hoops_PSRIR.configs._hoops_SSHRP,
					  option, p, pe);

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}


local char * _hoops_CACRS (
		_hoops_RHAIR const *	_hoops_RCIHP,
		Option_Value const *		option,
		char *						p,
		char const *				pe)
{
	short mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;
	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR.mask, _hoops_SCSRP)) {
		if (option == null)
			p = HI_Copy_Chars ("diffuse weight=", p);
		p = HI_Sprintf1 (p, pe,"%f,", &_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_GRCR);
	}
	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR.mask, _hoops_ICSRP)) {
		if (BIT (_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR.value, _hoops_ICSRP)) {
			if (option == null)
				p = HI_Copy_Chars ("color range=(", p);
			p = HI_Sprintf1 (p, pe,"%f,", &_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_HCIR[0]);
			p = HI_Sprintf1 (p, pe,"%f,", &_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_HCIR[1]);
			if (option == null) {
				--p;
				p = HI_Copy_Chars ("),", p);
			}
		}
		else {
			if (option == null)
				p = HI_Copy_Chars ("no color range,", p);
			else
				p = HI_Copy_Chars ("off,", p);
		}
	}
	if (BIT (mask & _hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR.mask, _hoops_GSSRP)) {
		if (BIT (_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR.value, _hoops_GSSRP)) {
			if (option == null) {
				if (_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR.length>0) {
					p = HI_Copy_Chars ("color map segment=", p);
					p = HI_Sprintf1 (p, pe, "%N,", &_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR);
				}
				else
					p = HI_Sprintf1 (p, pe, "no color map segment,", null);
			}
			else {
				if (_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR.length>0)
					p = HI_Sprintf1 (p, pe, "%N,", &_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR);
				else
					p = HI_Sprintf1 (p, pe, "off,", null);
			}
		}
		else {
			if (option == null)
				p = HI_Copy_Chars ("no color map segment,", p);
			else
				p = HI_Copy_Chars ("off,", p);
		}
	}
	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}


local char * _hoops_SACRS (
		_hoops_RHAIR const *	_hoops_RCIHP,
		Option_Value const *		option,
		char *						p,
		char const *				pe)
{
	short							mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (BIT (mask & _hoops_RCIHP->_hoops_SSHCA.mask, _hoops_RAAAP)) {
		if (option == null)
			p = HI_Copy_Chars ("style=", p);

		if (_hoops_RCIHP->_hoops_SSHCA.style == Transparency_STYLE_BLENDING)
			p = HI_Copy_Chars ("blending,", p);
		else if (_hoops_RCIHP->_hoops_SSHCA.style == _hoops_GCPI)
			p = HI_Copy_Chars ("screen door,", p);
		else
			p = HI_Copy_Chars ("off,", p);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_SSHCA.mask, _hoops_AAAAP)) {
		if (option == null)
			p = HI_Copy_Chars ("hsr algorithm=", p);

		if (BIT (_hoops_RCIHP->_hoops_SSHCA._hoops_SRI, _hoops_GRAAP))
			p = HI_Copy_Chars ("painters,", p);
		else if (BIT (_hoops_RCIHP->_hoops_SSHCA._hoops_SRI, _hoops_HSSS))
			p = HI_Copy_Chars ("z sort only,", p);
		else if (BIT (_hoops_RCIHP->_hoops_SSHCA._hoops_SRI, _hoops_PIII))
			p = HI_Copy_Chars ("depth peeling,", p);
		else
			p = HI_Copy_Chars ("none,", p);
	}

	if (ANYBIT (mask & _hoops_RCIHP->_hoops_SSHCA.mask, _hoops_CAAAP)) {
		bool		_hoops_RGPRA = false;
		Option_Value	*_hoops_AHSAA = null;
		short			_hoops_PHSAA;

		if (option == null) {
			short			_hoops_RCHA = mask & _hoops_RCIHP->_hoops_SSHCA.mask & _hoops_CAAAP;

			_hoops_RGPRA = (_hoops_RIII (_hoops_RCHA) != _hoops_RCHA);
			p = HI_Copy_Chars ("depth peeling options=", p);
			if (_hoops_RGPRA)
				p = HI_Copy_Chars ("(", p);
		}

		if (option != null)
			_hoops_AHSAA = option->value.option_list;
		if (_hoops_AHSAA != null)
			_hoops_PHSAA = _hoops_AHSAA->type->id;
		else
			_hoops_PHSAA = ~0;

		if (BIT (_hoops_PHSAA & _hoops_RCIHP->_hoops_SSHCA.mask, _hoops_HAAAP)) {
			if (_hoops_AHSAA == null)
				p = HI_Copy_Chars ("layers=", p);
			p = HI_Sprintf1 (p, pe,"%d,", &_hoops_RCIHP->_hoops_SSHCA._hoops_RPAAP);
		}
		if (BIT (_hoops_PHSAA & _hoops_RCIHP->_hoops_SSHCA.mask, _hoops_IAAAP)) {
			if (_hoops_AHSAA == null)
				p = HI_Copy_Chars ("minimum area=", p);
			if (_hoops_RCIHP->_hoops_SSHCA._hoops_APAAP < 0.0f) {
				float		temp = -_hoops_RCIHP->_hoops_SSHCA._hoops_APAAP;

				p = HI_Sprintf1 (p, pe,"%f pixels,", &temp);
			}
			else
				p = HI_Sprintf1 (p, pe,"%f%%,", &_hoops_RCIHP->_hoops_SSHCA._hoops_APAAP);
		}
		if (p != null)
			--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */

		if (_hoops_RGPRA)
			p = HI_Copy_Chars (")", p);
		p = HI_Copy_Chars (",", p);
	}

	if (ANYBIT (mask & _hoops_RCIHP->_hoops_SSHCA.mask, _hoops_SAAAP)) {
		if (option == null)
			p = HI_Copy_Chars ("zsort options=", p);

		if (BIT (_hoops_RCIHP->_hoops_SSHCA.value, _hoops_SAAAP))
			p = HI_Copy_Chars ("fastest,", p);
		else
			p = HI_Copy_Chars ("nicest,", p);
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_SSHCA.mask, _hoops_PAAAP))
		_hoops_ISIIH ("hardware acceleration",
					  BIT (_hoops_RCIHP->_hoops_SSHCA.value, _hoops_PAAAP),
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_SSHCA.mask, _hoops_GPAAP))
		_hoops_ISIIH ("depth writing",
					  BIT (_hoops_RCIHP->_hoops_SSHCA.value, _hoops_GPAAP),
					  option, p, pe);

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}

local char * _hoops_GPCRS (
	_hoops_RHAIR const *	_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	_hoops_CCGAP			mask;
	int								i, _hoops_AACRS;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (BIT (mask & _hoops_RCIHP->geometry->_hoops_GAICA.mask, _hoops_ACGAP)) {
		if (option == null)
			p = HI_Copy_Chars ("cylinder=", p);

		_hoops_AACRS = 0;
		for (i = 1; i < _hoops_IGAIR; i++)
			if (_hoops_RCIHP->geometry->_hoops_GAICA.cylinder[i] !=
						_hoops_RCIHP->geometry->_hoops_GAICA.cylinder[i-1])
				_hoops_AACRS = i;

		if (_hoops_AACRS)
			p = HI_Copy_Chars ("(", p);

		for (i = 0; i <= _hoops_AACRS; i++)
			p = HI_Sprintf1 (p, pe,"%d,",
							 &_hoops_RCIHP->geometry->_hoops_GAICA.cylinder[i]);
		--p;
		if (_hoops_AACRS)
			p = HI_Copy_Chars (")", p);
		p = HI_Copy_Chars (",", p);
	}
	if (BIT (mask & _hoops_RCIHP->geometry->_hoops_GAICA.mask, _hoops_PCGAP)) {
		if (option == null)
			p = HI_Copy_Chars ("sphere=", p);

		_hoops_AACRS = 0;
		for (i = 1; i < _hoops_IGAIR; i++)
			if (_hoops_RCIHP->geometry->_hoops_GAICA.sphere[i] !=
						_hoops_RCIHP->geometry->_hoops_GAICA.sphere[i-1])
				_hoops_AACRS = i;

		if (_hoops_AACRS)
			p = HI_Copy_Chars ("(", p);

		for (i = 0; i <= _hoops_AACRS; i++)
			p = HI_Sprintf1 (p, pe,"%d,",
							 &_hoops_RCIHP->geometry->_hoops_GAICA.sphere[i]);
		--p;
		if (_hoops_AACRS)
			p = HI_Copy_Chars (")", p);
		p = HI_Copy_Chars (",", p);
	}

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}

local char * _hoops_RPCRS (
	_hoops_RHAIR const *	_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	int								mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (BIT (mask & _hoops_RCIHP->geometry->mask, _hoops_GHGAP)) {
		if (option == null)
			p = HI_Copy_Chars ("hard edge angle=", p);

		p = HI_Sprintf1 (p, pe,"%f,", &_hoops_RCIHP->geometry->_hoops_GCIPR);
	}
	if (ANYBIT (mask & _hoops_RCIHP->geometry->mask, _hoops_PHGAP)) {
		if (ALLBITS (mask & _hoops_RCIHP->geometry->mask, _hoops_PHGAP)) {
			if (ALLBITS (mask & _hoops_RCIHP->geometry->value, _hoops_PHGAP))
				if (option == null)
					p = HI_Copy_Chars ("invert polycylinders,", p);
				else
					p = HI_Copy_Chars ("on,", p);
			else if (!ANYBIT (mask & _hoops_RCIHP->geometry->value, _hoops_PHGAP))
				if (option == null)
					p = HI_Copy_Chars ("no invert polycylinders,", p);
				else
					p = HI_Copy_Chars ("off,", p);
			else {
				if (option == null)
					p = HI_Copy_Chars ("invert polycylinders=(", p);

				if (BIT (mask & _hoops_RCIHP->geometry->value, _hoops_RHGAP))
					p = HI_Copy_Chars ("radii,", p);
				else
					p = HI_Copy_Chars ("no radii,", p);
				if (BIT (mask & _hoops_RCIHP->geometry->value, _hoops_AHGAP))
					p = HI_Copy_Chars ("colors,", p);
				else
					p = HI_Copy_Chars ("no colors,", p);
				--p;

				if (option == null)
					p = HI_Copy_Chars (")", p);

				p = HI_Copy_Chars (",", p);
			}
		}
		else if (BIT (mask & _hoops_RCIHP->geometry->mask, _hoops_RHGAP)) {
			if (option == null)
					p = HI_Copy_Chars ("invert polycylinders=", p);

			if (BIT (mask & _hoops_RCIHP->geometry->value, _hoops_RHGAP))
				p = HI_Copy_Chars ("radii,", p);
			else
				p = HI_Copy_Chars ("no radii,", p);
		}
		else if (BIT (mask & _hoops_RCIHP->geometry->mask, _hoops_AHGAP)) {
			if (option == null)
					p = HI_Copy_Chars ("invert polycylinders=", p);

			if (BIT (mask & _hoops_RCIHP->geometry->value, _hoops_AHGAP))
				p = HI_Copy_Chars ("colors,", p);
			else
				p = HI_Copy_Chars ("no colors,", p);
		}
	}

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}


local char * _hoops_APCRS (
	_hoops_RHAIR const *	_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	int								mask;

	UNREFERENCED (pe);

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;

	if (ALLBITS (mask, _hoops_RCAAP) &&
		ANYBIT (_hoops_RCIHP->_hoops_PGICA, _hoops_RCAAP)) {
		if (option == null)
			p = HI_Copy_Chars ("camera", p);

		if (!ALLBITS (_hoops_RCIHP->_hoops_PGICA, _hoops_RCAAP)) {
			int				_hoops_IGGRH, part;
			bool		_hoops_PPCRS;

			part = _hoops_RCIHP->_hoops_PGICA & _hoops_RCAAP;
			_hoops_IGGRH = _hoops_RIII (part);
			_hoops_PPCRS = ANYBIT (part, ~_hoops_IGGRH) && option == null;

			if (option == null)
				*p++ = '=';
			if (_hoops_PPCRS) *p++ = '(';

			if (BIT (part, _hoops_AIAAP))
				p = HI_Copy_Chars ("rotation,", p);
			if (BIT (part, _hoops_RIAAP))
				p = HI_Copy_Chars ("scale,", p);
			if (BIT (part, _hoops_PIAAP))
				p = HI_Copy_Chars ("translation,", p);
			if (BIT (part, _hoops_HIAAP))
				p = HI_Copy_Chars ("perspective,", p);

			--p;		/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
			if (_hoops_PPCRS) *p++ = ')';
		}
		else if (option != null)
			p = HI_Copy_Chars ("on", p);
		*p++ = ',';

		mask &= ~_hoops_RCAAP;
	}
	if (ALLBITS (mask, _hoops_ACAAP) &&
		ANYBIT (_hoops_RCIHP->_hoops_PGICA, _hoops_ACAAP)) {
		if (option == null)
			p = HI_Copy_Chars ("model", p);

		if (!ALLBITS (_hoops_RCIHP->_hoops_PGICA, _hoops_ACAAP)) {
			int				_hoops_IGGRH, part;
			bool		_hoops_PPCRS;

			part = _hoops_RCIHP->_hoops_PGICA & _hoops_ACAAP;
			_hoops_IGGRH = _hoops_RIII (part);
			_hoops_PPCRS = ANYBIT (part, ~_hoops_IGGRH) && option == null;

			if (option == null)
				*p++ = '=';
			if (_hoops_PPCRS) *p++ = '(';

			if (BIT (part, _hoops_CIAAP))
				p = HI_Copy_Chars ("rotation,", p);
			if (BIT (part, _hoops_IIAAP))
				p = HI_Copy_Chars ("scale,", p);
			if (BIT (part, _hoops_SIAAP))
				p = HI_Copy_Chars ("translation,", p);

			--p;		/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
			if (_hoops_PPCRS) *p++ = ')';
		}
		else if (option != null)
			p = HI_Copy_Chars ("on", p);
		*p++ = ',';

		mask &= ~_hoops_ACAAP;
	}

	/* _hoops_IPCP _hoops_HSPR _hoops_CHR _hoops_IS _hoops_PSSP _hoops_IIIAR _hoops_AGSR _hoops_IIGR _hoops_RGSR. _hoops_PAGA _hoops_SGS _hoops_RH _hoops_PGHC _hoops_ARAR
	 * _hoops_SCAC _hoops_PISH _hoops_SIH _hoops_AIAH _hoops_CHHHP, _hoops_HIS _hoops_RH _hoops_SHIR _hoops_AGIR _hoops_GRS _hoops_HAR _hoops_APHS _hoops_SIH _hoops_ARI
	 */
	if (ALLBITS (mask, _hoops_PCAAP) &&
		ANYBIT (_hoops_RCIHP->_hoops_PGICA, _hoops_PCAAP)) {
		if (option == null)
			p = HI_Copy_Chars ("scale", p);

		if (!ALLBITS (_hoops_RCIHP->_hoops_PGICA, _hoops_PCAAP)) {
			int				_hoops_IGGRH, part;
			bool		_hoops_PPCRS;

			part = _hoops_RCIHP->_hoops_PGICA & _hoops_PCAAP;
			_hoops_IGGRH = _hoops_RIII (part);
			_hoops_PPCRS = ANYBIT (part, ~_hoops_IGGRH) && option == null;

			if (option == null)
				*p++ = '=';
			if (_hoops_PPCRS) *p++ = '(';

			if (BIT (part, _hoops_RIAAP))
				p = HI_Copy_Chars ("camera,", p);
			if (BIT (part, _hoops_IIAAP))
				p = HI_Copy_Chars ("model,", p);

			--p;		/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
			if (_hoops_PPCRS) *p++ = ')';
		}
		else if (option != null)
			p = HI_Copy_Chars ("on", p);
		*p++ = ',';
	}
	if (ALLBITS (mask, _hoops_HCAAP) &&
		ANYBIT (_hoops_RCIHP->_hoops_PGICA, _hoops_HCAAP)) {
		if (option == null)
			p = HI_Copy_Chars ("rotation", p);

		if (!ALLBITS (_hoops_RCIHP->_hoops_PGICA, _hoops_HCAAP)) {
			int				_hoops_IGGRH, part;
			bool		_hoops_PPCRS;

			part = _hoops_RCIHP->_hoops_PGICA & _hoops_HCAAP;
			_hoops_IGGRH = _hoops_RIII (part);
			_hoops_PPCRS = ANYBIT (part, ~_hoops_IGGRH) && option == null;

			if (option == null)
				*p++ = '=';
			if (_hoops_PPCRS) *p++ = '(';

			if (BIT (part, _hoops_AIAAP))
				p = HI_Copy_Chars ("camera,", p);
			if (BIT (part, _hoops_CIAAP))
				p = HI_Copy_Chars ("model,", p);

			--p;		/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
			if (_hoops_PPCRS) *p++ = ')';
		}
		else if (option != null)
			p = HI_Copy_Chars ("on", p);
		*p++ = ',';
	}
	if (ALLBITS (mask, _hoops_ICAAP) &&
		ANYBIT (_hoops_RCIHP->_hoops_PGICA, _hoops_ICAAP)) {
		if (option == null)
			p = HI_Copy_Chars ("translation", p);

		if (!ALLBITS (_hoops_RCIHP->_hoops_PGICA, _hoops_ICAAP)) {
			int				_hoops_IGGRH, part;
			bool		_hoops_PPCRS;

			part = _hoops_RCIHP->_hoops_PGICA & _hoops_ICAAP;
			_hoops_IGGRH = _hoops_RIII (part);
			_hoops_PPCRS = ANYBIT (part, ~_hoops_IGGRH) && option == null;

			if (option == null)
				*p++ = '=';
			if (_hoops_PPCRS) *p++ = '(';

			if (BIT (part, _hoops_PIAAP))
				p = HI_Copy_Chars ("camera,", p);
			if (BIT (part, _hoops_SIAAP))
				p = HI_Copy_Chars ("model,", p);

			--p;		/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
			if (_hoops_PPCRS) *p++ = ')';
		}
		else if (option != null)
			p = HI_Copy_Chars ("on", p);
		*p++ = ',';
	}
	if (ANYBIT (mask & _hoops_RCIHP->_hoops_PGICA, _hoops_CCAAP))
		if (option == null)
			p = HI_Copy_Chars ("perspective,", p);
		else
			p = HI_Copy_Chars ("on,", p);

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}

#define	_hoops_HHSSH	((_hoops_SSA|_hoops_GCP) & ~_hoops_AHGI)
#define	_hoops_HPCRS	((_hoops_GGP|_hoops_RCP) & ~_hoops_AHGI)
#define	_hoops_IPCRS	((_hoops_IIRAP|_hoops_HIRAP) & ~_hoops_AHGI)
local char * _hoops_CPCRS (
	_hoops_RHAIR const *	_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	_hoops_GHGI						mask;
	char const * const				_hoops_HAACP = "phong";
	char const * const				_hoops_GIC = "gooch";
	char const * const				_hoops_SPCRS = "gouraud";
	char const *					_hoops_ARPPH;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0U;

	if (ALLBITS (mask & _hoops_RCIHP->_hoops_ISHCA, _hoops_IPCRS|_hoops_HHSSH|_hoops_HPCRS)) {
		if (ALLBITS (_hoops_RCIHP->_hoops_GHRAP, _hoops_IPCRS)) {
			p = HI_Copy_Chars ("gouraud,", p);
			mask = 0;
		}
		else if (ALLBITS (_hoops_RCIHP->_hoops_GHRAP, _hoops_HPCRS)) {
			p = HI_Copy_Chars ("gooch,", p);
			mask = 0;
		}
		else if (ALLBITS (_hoops_RCIHP->_hoops_GHRAP, _hoops_HHSSH)) {
			p = HI_Copy_Chars ("phong,", p);
			mask = 0;
		}
		else if (!ANYBIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_HHSSH|_hoops_HPCRS|_hoops_IPCRS)) {
			p = HI_Copy_Chars ("off,", p);
			mask = 0;
		}
	}

	if (ANYBIT (mask & _hoops_RCIHP->_hoops_ISHCA, _hoops_SSA|_hoops_GGP|_hoops_IIRAP)) {
		_hoops_ARPPH = null;
		if (BIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_IIRAP))
			_hoops_ARPPH = _hoops_SPCRS;
		else if (BIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_GGP))
			_hoops_ARPPH = _hoops_GIC;
		else if (BIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_SSA))
			_hoops_ARPPH = _hoops_HAACP;
		_hoops_HIIRS ("faces", _hoops_ARPPH != null, _hoops_ARPPH, option, p, pe);
	}

	if (ANYBIT (mask & _hoops_RCIHP->_hoops_ISHCA, _hoops_GCP|_hoops_RCP|_hoops_HIRAP)) {
		_hoops_ARPPH = null;
		if (BIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_HIRAP))
			_hoops_ARPPH = _hoops_SPCRS;
		else if (BIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_RCP))
			_hoops_ARPPH = _hoops_GIC;
		else if (BIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_GCP))
			_hoops_ARPPH = _hoops_HAACP;
		_hoops_HIIRS ("edges", _hoops_ARPPH != null, _hoops_ARPPH, option, p, pe);
	}

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}

local char * _hoops_GHCRS (
	_hoops_RHAIR const *	_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	_hoops_GHGI					mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0U;

	if (ALLBITS (mask & _hoops_RCIHP->_hoops_ISHCA, _hoops_SHRAP & ~_hoops_AHGI)) {
		if (ALLBITS (_hoops_RCIHP->_hoops_GHRAP, _hoops_SHRAP & ~_hoops_AHGI)) {
			p = HI_Copy_Chars ("on,", p);
			mask = 0;
		}
		else if (!ANYBIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_SHRAP & ~_hoops_AHGI)) {
			p = HI_Copy_Chars ("off,", p);
			mask = 0;
		}
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_ISHCA, _hoops_GSRC))
		_hoops_ISIIH ("faces", BIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_GSRC),
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_ISHCA, _hoops_RGAC))
		_hoops_ISIIH ("edges", BIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_RGAC),
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_ISHCA, _hoops_CHRAP))
		_hoops_ISIIH ("markers", BIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_CHRAP),
					  option, p, pe);

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}

local char * _hoops_RHCRS (
	_hoops_RHAIR const *	_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	_hoops_GHGI					mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0U;

	if (ALLBITS (mask & _hoops_RCIHP->_hoops_ISHCA, _hoops_AHRAP & ~_hoops_AHGI)) {
		if (ALLBITS (_hoops_RCIHP->_hoops_GHRAP, _hoops_AHRAP & ~_hoops_AHGI)) {
			p = HI_Copy_Chars ("on,", p);
			mask = 0;
		}
		else if (!ANYBIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_AHRAP & ~_hoops_AHGI)) {
			p = HI_Copy_Chars ("off,", p);
			mask = 0;
		}
	}

	if (BIT (mask & _hoops_RCIHP->_hoops_ISHCA, _hoops_HIRC))
		_hoops_ISIIH ("faces", BIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_HIRC),
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_ISHCA, _hoops_SSRC))
		_hoops_ISIIH ("edges", BIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_SSRC),
					  option, p, pe);

	if (BIT (mask & _hoops_RCIHP->_hoops_ISHCA, _hoops_RHRAP))
		_hoops_ISIIH ("markers", BIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_RHRAP),
					  option, p, pe);

	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}

local char * _hoops_AHCRS (
	_hoops_RHAIR const *	_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	_hoops_GHGI					mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0U;


	if (BIT (mask & _hoops_RCIHP->_hoops_ISHCA, _hoops_PHGI) &&
		BIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_IHRAP)) {
		p = HI_Copy_Chars ("isolines,", p);

		if (BIT (mask & _hoops_RCIHP->_hoops_ISHCA, _hoops_CSRC))
			_hoops_ISIIH ("edges", BIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_CSRC),
						  option, p, pe);
	}
	else if (ALLBITS (mask & _hoops_RCIHP->_hoops_ISHCA, _hoops_HHRAP &
													   ~_hoops_AHGI)) {
		if (ALLBITS (_hoops_RCIHP->_hoops_GHRAP, _hoops_HHRAP &
												~_hoops_AHGI))
			p = HI_Copy_Chars ("on,", p);
		else
			p = HI_Copy_Chars ("off,", p);
	}
	else {
		if (BIT (mask & _hoops_RCIHP->_hoops_ISHCA, _hoops_PHGI))
			_hoops_ISIIH ("faces", BIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_PHGI),
						  option, p, pe);

		if (BIT (mask & _hoops_RCIHP->_hoops_ISHCA, _hoops_CSRC))
			_hoops_ISIIH ("edges", BIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_CSRC),
						  option, p, pe);

		if (BIT (mask & _hoops_RCIHP->_hoops_ISHCA, _hoops_PHRAP))
			_hoops_ISIIH ("edges", BIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_PHRAP),
						  option, p, pe);
	}


	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}

#	if 0
local char * _hoops_PHCRS (
	_hoops_RHAIR const *	_hoops_RCIHP,
	Option_Value const *			option,
	char *							p,
	char const *					pe) {
	_hoops_HHCRS				mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0;



	if (p != null)
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
	return p;
}

#	endif
#endif

#define	_hoops_IPCRS	((_hoops_IIRAP|_hoops_HIRAP) & ~_hoops_AHGI)

GLOBAL_FUNCTION void HI_Show_Rendering_Options (
	_hoops_RHAIR *			_hoops_RCIHP,
	char *						list,
	int							_hoops_GGCIR) {
#ifndef _hoops_CHIRS
	char						buf[16384];
	char *						p = buf;
	char *						pe = buf+_hoops_GGAPR(buf);
	const struct _hoops_SHIRS *	_hoops_IHCRS = _hoops_GIIRS;
	long						_hoops_IGGRH;
	bool						_hoops_HISCA;
	_hoops_GHGI					_hoops_ASHCA = _hoops_RCIHP->_hoops_SCIAA;
	_hoops_GHGI					simple = _hoops_RCIHP->_hoops_PSHCA;
	_hoops_GHGI					_hoops_RHGI = _hoops_RCIHP->_hoops_ISHCA;

	if (_hoops_ASHCA || simple || _hoops_RHGI) do {
		if ((_hoops_IHCRS->mask & _hoops_AHGI) == _hoops_PSGAP) {
			if (ANYBIT (_hoops_RHGI, _hoops_IHCRS->mask)) {
				_hoops_RHGI &= ~_hoops_IHCRS->mask;			/* _hoops_RGAR _hoops_SGH _hoops_SRS _hoops_PPPIA _hoops_SRSGR */

				if (ALLBITS (_hoops_RCIHP->_hoops_ISHCA, _hoops_IHCRS->mask & ~_hoops_AHGI) &&
					!ANYBIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_IHCRS->mask)) {
					*p++ = 'n';
					*p++ = 'o';
					*p++ = ' ';
				}

				p = HI_Copy_Chars (_hoops_IHCRS->name.text, p);

				if (!ANYBIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_IHCRS->mask)) {}
				else if (_hoops_IHCRS->mask == _hoops_CIRAP) {
					_hoops_GHGI	_hoops_CHCRS = _hoops_RCIHP->_hoops_ISHCA & _hoops_IHCRS->mask;

					if (ALLBITS (_hoops_CHCRS, _hoops_IPCRS) &&
						ALLBITS (_hoops_RCIHP->_hoops_GHRAP, _hoops_IPCRS)) {}
					else {
						*p++ = '=';

						/* _hoops_CACH _hoops_RPP _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_IGRH _hoops_ARP */
						_hoops_IGGRH = _hoops_RIII (_hoops_CHCRS);
						_hoops_HISCA = ANYBIT (_hoops_CHCRS, ~_hoops_IGGRH);
						if (_hoops_HISCA) *p++ = '(';
						p = _hoops_CPCRS (_hoops_RCIHP, null, p, pe);
						if (_hoops_HISCA) *p++ = ')';
					}
				}
				else if (_hoops_IHCRS->mask == _hoops_SHRAP) {
					_hoops_GHGI	_hoops_CHCRS = _hoops_RCIHP->_hoops_ISHCA & _hoops_IHCRS->mask;

					if (ALLBITS (_hoops_CHCRS, _hoops_SHRAP & ~_hoops_AHGI) &&
						ALLBITS (_hoops_RCIHP->_hoops_GHRAP, _hoops_SHRAP & ~_hoops_AHGI)) {}
					else {
						*p++ = '=';

						/* _hoops_CACH _hoops_RPP _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_IGRH _hoops_ARP */
						_hoops_IGGRH = _hoops_RIII (_hoops_CHCRS);
						_hoops_HISCA = ANYBIT (_hoops_CHCRS, ~_hoops_IGGRH);
						if (_hoops_HISCA) *p++ = '(';
						p = _hoops_GHCRS (_hoops_RCIHP, null, p, pe);
						if (_hoops_HISCA) *p++ = ')';
					}
				}
				else if (_hoops_IHCRS->mask == _hoops_AHRAP) {
					_hoops_GHGI	_hoops_CHCRS = _hoops_RCIHP->_hoops_ISHCA & _hoops_IHCRS->mask;

					if (ALLBITS (_hoops_CHCRS, _hoops_AHRAP & ~_hoops_AHGI) &&
						ALLBITS (_hoops_RCIHP->_hoops_GHRAP, _hoops_AHRAP & ~_hoops_AHGI)) {}
					else {
						*p++ = '=';

						/* _hoops_CACH _hoops_RPP _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_IGRH _hoops_ARP */
						_hoops_IGGRH = _hoops_RIII (_hoops_CHCRS);
						_hoops_HISCA = ANYBIT (_hoops_CHCRS, ~_hoops_IGGRH);
						if (_hoops_HISCA) *p++ = '(';
						p = _hoops_RHCRS (_hoops_RCIHP, null, p, pe);
						if (_hoops_HISCA) *p++ = ')';
					}
				}
				else if (_hoops_IHCRS->mask == _hoops_HHRAP) {
					_hoops_GHGI	_hoops_CHCRS = _hoops_RCIHP->_hoops_ISHCA & _hoops_IHCRS->mask;

					if (ALLBITS (_hoops_CHCRS, _hoops_HHRAP & ~_hoops_AHGI) &&
						ALLBITS (_hoops_RCIHP->_hoops_GHRAP, _hoops_HHRAP & ~_hoops_AHGI)) {}
					else {
						*p++ = '=';

						/* _hoops_CACH _hoops_RPP _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_IGRH _hoops_ARP */
						_hoops_IGGRH = _hoops_RIII (_hoops_CHCRS);
						_hoops_HISCA = ANYBIT (_hoops_CHCRS, ~_hoops_IGGRH);
						if (_hoops_HISCA) *p++ = '(';
						p = _hoops_AHCRS (_hoops_RCIHP, null, p, pe);
						if (_hoops_HISCA) *p++ = ')';
					}
				}

				*p++ = ',';
			}
		}
		else if ((_hoops_IHCRS->mask & _hoops_AHGI) == _hoops_ASGAP) {
			if (ANYBIT (simple, _hoops_IHCRS->mask)) {
				simple &= ~_hoops_IHCRS->mask;			/* _hoops_RGAR _hoops_SGH _hoops_SRS _hoops_PPPIA _hoops_SRSGR */

				if (!ANYBIT (_hoops_RCIHP->_hoops_RRRAP, _hoops_IHCRS->mask)) {
					*p++ = 'n';
					*p++ = 'o';
					*p++ = ' ';
				}

				p = HI_Copy_Chars (_hoops_IHCRS->name.text, p);

				if (ANYBIT (_hoops_RCIHP->_hoops_RRRAP, _hoops_IHCRS->mask)) {
					if (_hoops_IHCRS->mask == _hoops_PRRAP) {
							long			tmp = _hoops_RCIHP->_hoops_IRARR;

							p = HI_Sprintf1 (p, pe, "=%D", &tmp);
					}
					else if (_hoops_IHCRS->mask == _hoops_CRRAP) {
						long			tmp = _hoops_RCIHP->_hoops_CHIH;

						p = HI_Sprintf1 (p, pe, "=%D", &tmp);
					}
					else if (_hoops_IHCRS->mask == _hoops_IPRAP) {
						long			tmp = _hoops_RCIHP->_hoops_IGAAP;

						p = HI_Sprintf1 (p, pe, "=%D", &tmp);
					}
					else if (_hoops_IHCRS->mask == _hoops_SARAP) {
						long			tmp = _hoops_RCIHP->_hoops_SHIH;

						p = HI_Sprintf1 (p, pe, "=%D", &tmp);
					}
					else if (_hoops_IHCRS->mask == _hoops_HPRAP) {
						float			tmp = _hoops_RCIHP->_hoops_CSRS;

						p = HI_Sprintf1 (p, pe, "=%f", &tmp);
					}
					else if (_hoops_IHCRS->mask == _hoops_GPRAP) {
						if (_hoops_RCIHP->_hoops_GSAAP == _hoops_RCIHP->_hoops_RSAAP) {
							long			tmp = _hoops_RCIHP->_hoops_GSAAP;

							p = HI_Sprintf1 (p, pe, "=%D", &tmp);
						}
						else if (_hoops_RCIHP->_hoops_RSAAP == -1) {
							long			tmp = _hoops_RCIHP->_hoops_GSAAP;

							p = HI_Sprintf1 (p, pe, "=line=%D", &tmp);
						}
						else if (_hoops_RCIHP->_hoops_GSAAP == -1) {
							long			tmp = _hoops_RCIHP->_hoops_RSAAP;

							p = HI_Sprintf1 (p, pe, "=edge=%D", &tmp);
						}
						else {
							long			tmp = _hoops_RCIHP->_hoops_GSAAP;

							p = HI_Sprintf1 (p, pe, "=(line=%D,", &tmp);

							tmp = _hoops_RCIHP->_hoops_RSAAP;
							p = HI_Sprintf1 (p, pe, "edge=%D)", &tmp);
						}
					}
					else if (_hoops_IHCRS->mask == _hoops_IARAP) {
						float			tmp = _hoops_RCIHP->_hoops_HHAIR->_hoops_ACSRP;

						p = HI_Sprintf1 (p, pe, "=%f", &tmp);
					}
					else if (_hoops_IHCRS->mask == _hoops_RPRAP) {
						float			tmp = _hoops_RCIHP->_hoops_HHAIR->_hoops_PCSRP;

						p = HI_Sprintf1 (p, pe, "=%f", &tmp);
					}
					else if (_hoops_IHCRS->mask == _hoops_PARAP) {
						if (BIT (_hoops_RCIHP->_hoops_SIRAP, Quantization_THRESHOLD))
							p = HI_Copy_Chars ("=threshold", p);
						else if (BIT (_hoops_RCIHP->_hoops_SIRAP, Quantization_DITHER))
							p = HI_Copy_Chars ("=dither", p);
						else
							p = HI_Copy_Chars ("=error diffusion", p);
					}
					else if (_hoops_IHCRS->mask == _hoops_HRRAP) {
						p = HI_Sprintf1 (p, pe, "=(%f,",
										 (void *)&_hoops_RCIHP->_hoops_HHAAP[0]);
						p = HI_Sprintf1 (p, pe, "%f)",
										 (void *)&_hoops_RCIHP->_hoops_HHAAP[1]);
					}
					else if (_hoops_IHCRS->mask == _hoops_APRAP) {
						p = HI_Sprintf1 (p, pe, "=(%f,",
										 (void *)&_hoops_RCIHP->_hoops_HCIH.left);
						p = HI_Sprintf1 (p, pe, "%f,",
										 (void *)&_hoops_RCIHP->_hoops_HCIH.right);
						p = HI_Sprintf1 (p, pe, "%f,",
										 (void *)&_hoops_RCIHP->_hoops_HCIH.bottom);
						p = HI_Sprintf1 (p, pe, "%f)",
										 (void *)&_hoops_RCIHP->_hoops_HCIH.top);
					}
					else if (_hoops_IHCRS->mask == _hoops_PPRAP) {
						p = HI_Sprintf1 (p, pe, "=(%f,",
										 (void *)&_hoops_RCIHP->_hoops_HHAIR->_hoops_HRGA.x);
						p = HI_Sprintf1 (p, pe, "%f,",
										 (void *)&_hoops_RCIHP->_hoops_HHAIR->_hoops_HRGA.y);
						p = HI_Sprintf1 (p, pe, "%f)",
										 (void *)&_hoops_RCIHP->_hoops_HHAIR->_hoops_HRGA.z);
					}
					else if (_hoops_IHCRS->mask == _hoops_GARAP) {
						p = HI_Sprintf1 (p, pe, "=(%f,",
										 (void *)&_hoops_RCIHP->_hoops_IHAAP[0]);
						p = HI_Sprintf1 (p, pe, "%f)",
										 (void *)&_hoops_RCIHP->_hoops_IHAAP[1]);
					}
					else if (_hoops_IHCRS->mask == _hoops_RARAP) {
						p = HI_Sprintf1 (p, pe,"='R=%f ", &_hoops_RCIHP->_hoops_CHAAP.red);
						p = HI_Sprintf1 (p, pe,"G=%f ", &_hoops_RCIHP->_hoops_CHAAP.green);
						p = HI_Sprintf1 (p, pe,"B=%f'",	&_hoops_RCIHP->_hoops_CHAAP.blue);
					}
					else if (_hoops_IHCRS->mask == _hoops_CPRAP) {
						p = HI_Sprintf1 (p, pe,"='R=%f ", &_hoops_RCIHP->_hoops_HRA.red);
						p = HI_Sprintf1 (p, pe,"G=%f ", &_hoops_RCIHP->_hoops_HRA.green);
						p = HI_Sprintf1 (p, pe,"B=%f'",	&_hoops_RCIHP->_hoops_HRA.blue);
					}
					else if (_hoops_IHCRS->mask == _hoops_HPH) {
						p = HI_Sprintf1 (p, pe, "=(hither=%f,",
										 (void *)&_hoops_RCIHP->_hoops_HHAIR->_hoops_CRIR.hither);
						p = HI_Sprintf1 (p, pe, "yon=%f)",
										 (void *)&_hoops_RCIHP->_hoops_HHAIR->_hoops_CRIR.yon);
					}
					else if (_hoops_IHCRS->mask == _hoops_SRRAP) {
						*p++ = '=';

						if (BIT (_hoops_RCIHP->_hoops_SRI, _hoops_SGAAP))
							p = HI_Copy_Chars ("hardware z buffer", p);
						else if (BIT (_hoops_RCIHP->_hoops_SRI, _hoops_GRAAP))
							p = HI_Copy_Chars ("painters", p);
						else if (BIT (_hoops_RCIHP->_hoops_SRI, _hoops_RRAAP))
							p = HI_Copy_Chars ("software z buffer", p);
						else if (BIT (_hoops_RCIHP->_hoops_SRI, _hoops_PRAAP))
							p = HI_Copy_Chars ("hidden line", p);
						else if (BIT (_hoops_RCIHP->_hoops_SRI, _hoops_SICI))
							p = HI_Copy_Chars ("fast hidden line", p);
						else if (BIT (_hoops_RCIHP->_hoops_SRI, _hoops_HSSS))
							p = HI_Copy_Chars ("z sort only", p);
						else if (BIT (_hoops_RCIHP->_hoops_SRI, _hoops_GAI))
							p = HI_Copy_Chars ("priority", p);
					}
					else if (_hoops_IHCRS->mask == _hoops_CARAP) {
						_hoops_IGGRH = _hoops_RIII (_hoops_RCIHP->_hoops_RCRAP);
						_hoops_HISCA = ANYBIT (_hoops_RCIHP->_hoops_RCRAP, ~_hoops_IGGRH);

						*p++ = '=';
						if (_hoops_HISCA) *p++ = '(';
#ifndef DISABLE_AIR_OPTIONS
						if (BIT (_hoops_RCIHP->_hoops_RCRAP, _hoops_PCRAP))
							p = HI_Copy_Chars ("radiosity,", p);
						if (BIT (_hoops_RCIHP->_hoops_RCRAP, _hoops_HCRAP))
							p = HI_Copy_Chars ("ray-trace,", p);
#endif
						if (BIT (_hoops_RCIHP->_hoops_RCRAP, _hoops_ICRAP))
							p = HI_Copy_Chars ("software frame buffer,", p);
						if (BIT (_hoops_RCIHP->_hoops_RCRAP, _hoops_ACRAP) ||
							_hoops_RCIHP->_hoops_RCRAP == false)
							p = HI_Copy_Chars ("standard,", p);
						--p;		/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
						if (_hoops_HISCA) *p++ = ')';
					}
					else if (_hoops_IHCRS->mask == _hoops_IRRAP) {
						if (_hoops_RCIHP->_hoops_PSAAP == Display_List_SEGMENT)
							p = HI_Copy_Chars ("=segment", p);
						else if (_hoops_RCIHP->_hoops_PSAAP == _hoops_ASAAP)
							p = HI_Copy_Chars ("=segment tree", p);
					}
				}

				*p++ = ',';
			}
		}
		else if (_hoops_IHCRS->mask == _hoops_GRRAP) {
			/* _hoops_IHIRS-_hoops_HCSP, _hoops_RGHH _hoops_PPGA */
			if (BIT (_hoops_ASHCA, _hoops_SGICA) &&
				BIT (_hoops_RCIHP->_hoops_PRSI->mask, _hoops_HRSI)) {
				if (!BIT (_hoops_RCIHP->_hoops_PRSI->value, _hoops_HRSI)) {
					*p++ = 'n';
					*p++ = 'o';
					*p++ = ' ';
				}

				p = HI_Copy_Chars (_hoops_IHCRS->name.text, p);

				*p++ = ',';
			}
		}
		else if (_hoops_IHCRS->mask == _hoops_SGICA &&
				 ANYBIT (_hoops_ASHCA, _hoops_IHCRS->mask)) {
			/* _hoops_RGHH _hoops_RGR _hoops_SPR _hoops_ICACR _hoops_GGR _hoops_AGIR _hoops_RH _hoops_RGAR _hoops_HCSP _hoops_HRGR "_hoops_SPIGA" */
			_hoops_RRPHA		_hoops_SHCRS = _hoops_RCIHP->_hoops_PRSI->mask &
														~_hoops_HRSI;

			_hoops_ASHCA &= ~_hoops_IHCRS->mask;			/* _hoops_RGAR _hoops_SGH _hoops_SRS _hoops_PPPIA _hoops_SRSGR */
			if (_hoops_SHCRS != 0) {
				_hoops_IGGRH = _hoops_RIII (_hoops_SHCRS);
				_hoops_HISCA = ANYBIT (_hoops_SHCRS, ~_hoops_IGGRH);

				p = HI_Copy_Chars (_hoops_IHCRS->name.text, p);

				*p++ = '=';
				if (_hoops_HISCA) *p++ = '(';
				p = _hoops_RACRS (_hoops_RCIHP, null, p, pe);
				if (_hoops_HISCA) *p++ = ')';

				*p++ = ',';
			}
		}
		else if (ANYBIT (_hoops_ASHCA, _hoops_IHCRS->mask) &&
				 (BIT (HOOPS_WORLD->_hoops_HPSPP, _hoops_CPCPP) ||
				  _hoops_IHCRS->mask != _hoops_HGRAP &&
				  _hoops_IHCRS->mask != _hoops_IGRAP)) {

			_hoops_ASHCA &= ~_hoops_IHCRS->mask;			/* _hoops_RGAR _hoops_SGH _hoops_SRS _hoops_PPPIA _hoops_SRSGR */

			if (!ANYBIT (_hoops_RCIHP->_hoops_RSIAA, _hoops_IHCRS->mask)) {
				*p++ = 'n';
				*p++ = 'o';
				*p++ = ' ';
			}

			p = HI_Copy_Chars (_hoops_IHCRS->name.text, p);

			if (ANYBIT (_hoops_RCIHP->_hoops_RSIAA, _hoops_IHCRS->mask)) {
				if (_hoops_IHCRS->mask == _hoops_GSIAA) {
					_hoops_HHAGP		_hoops_CHCRS = _hoops_RCIHP->locks->normal.mask._hoops_IPPGR,
										_hoops_GICRS = _hoops_RCIHP->locks->normal.value._hoops_IPPGR;
					_hoops_HHAGP		_hoops_RICRS;
					bool				_hoops_AICRS;

					_hoops_AICRS = !ALLBITS (_hoops_CHCRS & _hoops_GICRS, _hoops_PIIRS);
					if (!_hoops_AICRS) {
						_hoops_AICRS = !ALLBITS (_hoops_RCIHP->locks->normal.mask.color & _hoops_RCIHP->locks->normal.value.color,
											Color_EVERYTHING & ~Color_CUT_GEOMETRY);
						if (!_hoops_AICRS) {
							int				i;

							for (i=0; i<_hoops_IIGRA; i++) {
								if (!ALLBITS (_hoops_RCIHP->locks->normal.mask._hoops_HAA[i] & _hoops_RCIHP->locks->normal.value._hoops_HAA[i],
											  _hoops_CIGRA)) {
									_hoops_AICRS = true;
									break;
								}
							}
						}
					}

					if (_hoops_AICRS) {
						*p++ = '=';

						/* _hoops_CACH _hoops_RPP _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_IGRH _hoops_ARP */
						_hoops_RICRS = _hoops_RIII ((Integer32)_hoops_CHCRS);
						if (_hoops_CHCRS & ~_hoops_RICRS) *p++ = '(';

						p = _hoops_RGCRS (p, null, &_hoops_RCIHP->locks->normal, true);

						if (_hoops_CHCRS & ~_hoops_RICRS) *p++ = ')';
					}
				}
				else if (_hoops_IHCRS->mask == _hoops_RGRAP) {
					_hoops_HHAGP		_hoops_CHCRS = _hoops_RCIHP->locks->_hoops_SACRP.mask._hoops_IPPGR,
										_hoops_GICRS = _hoops_RCIHP->locks->_hoops_SACRP.value._hoops_IPPGR;
					_hoops_HHAGP		_hoops_RICRS;
					bool				_hoops_AICRS;

					_hoops_AICRS = !ALLBITS (_hoops_CHCRS & _hoops_GICRS, _hoops_PIIRS);
					if (!_hoops_AICRS) {
						_hoops_AICRS = !ALLBITS (_hoops_RCIHP->locks->_hoops_SACRP.mask.color & _hoops_RCIHP->locks->_hoops_SACRP.value.color,
											Color_EVERYTHING & ~Color_CUT_GEOMETRY);
						if (!_hoops_AICRS) {
							int				i;

							for (i=0; i<_hoops_IIGRA; i++) {
								if (!ALLBITS (_hoops_RCIHP->locks->_hoops_SACRP.mask._hoops_HAA[i] & _hoops_RCIHP->locks->_hoops_SACRP.value._hoops_HAA[i],
											  _hoops_CIGRA)) {
									_hoops_AICRS = true;
									break;
								}
							}
						}
					}

					if (_hoops_AICRS) {
						*p++ = '=';

						/* _hoops_CACH _hoops_RPP _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_IGRH _hoops_ARP */
						_hoops_RICRS = _hoops_RIII ((Integer32)_hoops_CHCRS);
						if (_hoops_CHCRS & ~_hoops_RICRS) *p++ = '(';

						p = _hoops_RGCRS (p, null, &_hoops_RCIHP->locks->_hoops_SACRP, false);

						if (_hoops_CHCRS & ~_hoops_RICRS) *p++ = ')';
					}
				}
				else if (_hoops_IHCRS->mask == _hoops_GGICA) {
					_hoops_IGGRH = _hoops_RIII (_hoops_RCIHP->_hoops_RGICA.mask);
					_hoops_HISCA = ANYBIT (_hoops_RCIHP->_hoops_RGICA.mask, ~_hoops_IGGRH);

					*p++ = '=';
					if (_hoops_HISCA) *p++ = '(';
					p = _hoops_GACRS (_hoops_RCIHP, null, p, pe);
					if (_hoops_HISCA) *p++ = ')';
				}
				else if (_hoops_IHCRS->mask == _hoops_IGICA) {
					_hoops_IGGRH = _hoops_RIII (_hoops_RCIHP->_hoops_AIAIR->mask);
					_hoops_HISCA = ANYBIT (_hoops_RCIHP->_hoops_AIAIR->mask, ~_hoops_IGGRH);

					*p++ = '=';
					if (_hoops_HISCA) *p++ = '(';
					p = _hoops_SGCRS (_hoops_RCIHP, null, p, pe);
					if (_hoops_HISCA) *p++ = ')';
				}
				else if (_hoops_IHCRS->mask == _hoops_AGRAP) {
					_hoops_IGGRH = _hoops_RIII (_hoops_RCIHP->_hoops_IIAIR->mask & _hoops_PICRP);
					_hoops_HISCA = ANYBIT (_hoops_RCIHP->_hoops_IIAIR->mask & _hoops_PICRP, ~_hoops_IGGRH);

					*p++ = '=';
					if (_hoops_HISCA) *p++ = '(';
					p = _hoops_GRCRS (_hoops_RCIHP, null, p, pe);
					if (_hoops_HISCA) *p++ = ')';
				}
				else if (_hoops_IHCRS->mask == _hoops_PRICA) {
					_hoops_IGGRH = _hoops_RIII (_hoops_RCIHP->_hoops_IIAIR->mask & _hoops_ACCRP);
					_hoops_HISCA = ANYBIT (_hoops_RCIHP->_hoops_IIAIR->mask & _hoops_ACCRP, ~_hoops_IGGRH);

					*p++ = '=';
					if (_hoops_HISCA) *p++ = '(';
					p = _hoops_RRCRS (_hoops_RCIHP, null, p, pe);
					if (_hoops_HISCA) *p++ = ')';
				}
				else if (_hoops_IHCRS->mask == _hoops_PGRAP) {
					_hoops_IGGRH = _hoops_RIII (_hoops_RCIHP->_hoops_SHAAP);
					_hoops_HISCA = ANYBIT (_hoops_RCIHP->_hoops_SHAAP, ~_hoops_IGGRH);

					*p++ = '=';
					if (_hoops_HISCA) *p++ = '(';
					p = _hoops_PRCRS (_hoops_RCIHP, null, p, pe);
					if (_hoops_HISCA) *p++ = ')';
				}
				else if (_hoops_IHCRS->mask == _hoops_IRICA) {
					_hoops_IGGRH = _hoops_RIII (_hoops_RCIHP->geometry->_hoops_APPI.mask);
					_hoops_HISCA = ANYBIT (_hoops_RCIHP->geometry->_hoops_APPI.mask, ~_hoops_IGGRH);

					*p++ = '=';
					if (_hoops_HISCA) *p++ = '(';
					p = _hoops_HACRS (_hoops_RCIHP, null, p, pe);
					if (_hoops_HISCA) *p++ = ')';
				}
				else if (_hoops_IHCRS->mask == _hoops_CRICA) {
					_hoops_IGGRH = _hoops_RIII (_hoops_RCIHP->geometry->_hoops_PSRIR.mask);
					_hoops_HISCA = ANYBIT (_hoops_RCIHP->geometry->_hoops_PSRIR.mask, ~_hoops_IGGRH);

					*p++ = '=';
					if (_hoops_HISCA) *p++ = '(';
					p = _hoops_IACRS (_hoops_RCIHP, null, p, pe);
					if (_hoops_HISCA) *p++ = ')';
				}
				else if (_hoops_IHCRS->mask == _hoops_SRICA) {
					_hoops_IGGRH = _hoops_RIII (_hoops_RCIHP->geometry->_hoops_GAICA.mask);
					_hoops_HISCA = ANYBIT (_hoops_RCIHP->geometry->_hoops_GAICA.mask, ~_hoops_IGGRH);

					*p++ = '=';
					if (_hoops_HISCA) *p++ = '(';
					p = _hoops_GPCRS (_hoops_RCIHP, null, p, pe);
					if (_hoops_HISCA) *p++ = ')';
				}
				else if (_hoops_IHCRS->mask == _hoops_HRICA) {
					int			_hoops_PICRS = _hoops_RCIHP->geometry->mask;

					/* _hoops_GRH _hoops_PISH _hoops_PRCA _hoops_CAS 2 _hoops_SIH _hoops_CGH _hoops_SHH _hoops_HSHA _hoops_GAR 1 _hoops_IS _hoops_HIRAI _hoops_GPGR */
					if (ALLBITS (_hoops_PICRS, _hoops_PHGAP))
						_hoops_PICRS &= ~_hoops_AHGAP;

					_hoops_IGGRH = _hoops_RIII (_hoops_PICRS);
					_hoops_HISCA = ANYBIT (_hoops_PICRS, ~_hoops_IGGRH);

					*p++ = '=';
					if (_hoops_HISCA) *p++ = '(';
					p = _hoops_RPCRS (_hoops_RCIHP, null, p, pe);
					if (_hoops_HISCA) *p++ = ')';
				}
				else if (_hoops_IHCRS->mask == _hoops_ARICA) {
					_hoops_IGGRH = _hoops_RIII (_hoops_RCIHP->_hoops_HHAIR->_hoops_PRIGA.mask);
					_hoops_HISCA = ANYBIT (_hoops_RCIHP->_hoops_HHAIR->_hoops_PRIGA.mask &
									   ~_hoops_ISSRP, ~_hoops_IGGRH);

					*p++ = '=';
					if (_hoops_HISCA) *p++ = '(';
					p = _hoops_SRCRS (_hoops_RCIHP, null, p, pe);
					if (_hoops_HISCA) *p++ = ')';
				}
				else if (_hoops_IHCRS->mask == _hoops_RRICA) {
					_hoops_IGGRH = _hoops_RIII (_hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS.mask);
					_hoops_HISCA = ANYBIT (_hoops_RCIHP->_hoops_HHAIR->_hoops_GHSS.mask, ~_hoops_IGGRH);

					*p++ = '=';
					if (_hoops_HISCA) *p++ = '(';
					p = _hoops_HRCRS (_hoops_RCIHP, null, p, pe);
					if (_hoops_HISCA) *p++ = ')';
				}
				else if (_hoops_IHCRS->mask == _hoops_CSGAP) {
					_hoops_IGGRH = _hoops_RIII (_hoops_RCIHP->_hoops_HHAIR->_hoops_HRR.mask);
					_hoops_HISCA = ANYBIT (_hoops_RCIHP->_hoops_HHAIR->_hoops_HRR.mask, ~_hoops_IGGRH);

					*p++ = '=';
					if (_hoops_HISCA) *p++ = '(';
					p = _hoops_IRCRS (_hoops_RCIHP, null, p, pe);
					if (_hoops_HISCA) *p++ = ')';
				}
				else if (_hoops_IHCRS->mask == _hoops_SSGAP) {
					_hoops_IGGRH = _hoops_RIII (_hoops_RCIHP->_hoops_HHAIR->_hoops_RHGGR.mask);
					_hoops_HISCA = ANYBIT (_hoops_RCIHP->_hoops_HHAIR->_hoops_RHGGR.mask, ~_hoops_IGGRH);

					*p++ = '=';
					if (_hoops_HISCA) *p++ = '(';
					p = _hoops_CRCRS (_hoops_RCIHP, null, p, pe);
					if (_hoops_HISCA) *p++ = ')';
				}
				else if (_hoops_IHCRS->mask == _hoops_AGICA) {
					_hoops_HISCA = ANYBIT (_hoops_RCIHP->_hoops_PGICA, _hoops_RCAAP) &&
							   ANYBIT (_hoops_RCIHP->_hoops_PGICA, _hoops_ACAAP);

					*p++ = '=';
					if (_hoops_HISCA) *p++ = '(';
					p = _hoops_APCRS (_hoops_RCIHP, null, p, pe);
					if (_hoops_HISCA) *p++ = ')';
				}
				else if (_hoops_IHCRS->mask == _hoops_GGRAP) {
					_hoops_IGGRH = _hoops_RIII (_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR.mask);
					_hoops_HISCA = ANYBIT (_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR.mask, ~_hoops_IGGRH);

					*p++ = '=';
					if (_hoops_HISCA) *p++ = '(';

					p = _hoops_CACRS (_hoops_RCIHP, null, p, pe);

					if (_hoops_HISCA) *p++ = ')';
				}
				else if (_hoops_IHCRS->mask == _hoops_CSHCA) {
					_hoops_IGGRH = _hoops_RIII (_hoops_RCIHP->_hoops_SSHCA.mask);
					_hoops_HISCA = ANYBIT (_hoops_RCIHP->_hoops_SSHCA.mask, ~_hoops_IGGRH);

					*p++ = '=';
					if (_hoops_HISCA) *p++ = '(';

					p = _hoops_SACRS (_hoops_RCIHP, null, p, pe);

					if (_hoops_HISCA) *p++ = ')';
				}
				else if (_hoops_IHCRS->mask == _hoops_ISGAP) {
					bool	_hoops_HICRS = true;

					if (ALLBITS(_hoops_RCIHP->_hoops_CHP.mask, _hoops_GAAAP)) {
						if (ALLBITS(_hoops_RCIHP->_hoops_CHP.value, _hoops_GAAAP)) {
							_hoops_HICRS = false;
						}
						else if (!ANYBIT(_hoops_RCIHP->_hoops_CHP.value, _hoops_GAAAP)) {
							p = HI_Copy_Chars ("=off", p);
							_hoops_HICRS = false;
						}
					}
					if (_hoops_HICRS) {
						_hoops_IGGRH = _hoops_RIII (_hoops_RCIHP->_hoops_CHP.mask);
						_hoops_HISCA = ANYBIT (_hoops_RCIHP->_hoops_CHP.mask, ~_hoops_IGGRH);

						*p++ = '=';
						if (_hoops_HISCA) *p++ = '(';

						if (BIT(_hoops_RCIHP->_hoops_CHP.mask, _hoops_GPSP)) {
							if (!BIT(_hoops_RCIHP->_hoops_CHP.value, _hoops_GPSP))
								p = HI_Copy_Chars ("no ", p);
							p = HI_Copy_Chars ("screen,", p);
						}
						if (BIT(_hoops_RCIHP->_hoops_CHP.mask, _hoops_CRAAP)) {
							if (!BIT(_hoops_RCIHP->_hoops_CHP.value, _hoops_CRAAP))
								p = HI_Copy_Chars ("no ", p);
							p = HI_Copy_Chars ("text,", p);
						}
						if (BIT(_hoops_RCIHP->_hoops_CHP.mask, _hoops_SHP)) {
							if (!BIT(_hoops_RCIHP->_hoops_CHP.value, _hoops_SHP))
								p = HI_Copy_Chars ("no ", p);
							p = HI_Copy_Chars ("lines,", p);
						}
						--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
						if (_hoops_HISCA) *p++ = ')';
					}
				}
			}

			*p++ = ',';
		}
	} while ((++_hoops_IHCRS)->mask != 0);
	--p;

	HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(p - buf));
#endif
}


#ifndef DISABLE_SHOW

local void _hoops_IICRS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_RHAIR *		_hoops_RCIHP,
	char const *			_hoops_HSGIH,
	char *					list,
	int						_hoops_GGCIR)
{
	Option_Value *			option;

	if (!HI_Parse_Options (_hoops_RIGC, _hoops_HSGIH, _hoops_CIACR (_hoops_HAPPP), &option,
		_hoops_CGPCR|_hoops_PAPCA))
		return;

	if (option == null)
		return;

	_hoops_GHGI	mask = option->type->id;

	char	buf[1000];
	char *	p = buf;
	char *	pe = buf+_hoops_GGAPR(buf);

	if ((mask & _hoops_AHGI) == _hoops_PSGAP) {
		if (!ANYBIT (mask, _hoops_RCIHP->_hoops_ISHCA)) {
			HE_ERROR (HEC_RENDERING, HES_NO_LOCAL_SETTING, Sprintf_SP (null, "'%s' has no setting in '%p'",_hoops_HSGIH, _hoops_RCIHP->owner));
			HI_Free_Option_List (_hoops_RIGC, option);
			return;
		}

		if (mask == _hoops_CIRAP &&
			ANYBIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_CIRAP)) {
			p = _hoops_CPCRS (_hoops_RCIHP, option->value.option_list, p, pe);
			HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
		}
		else if (mask == _hoops_SHRAP &&
			ANYBIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_SHRAP)) {
			p = _hoops_GHCRS (_hoops_RCIHP, option->value.option_list, p, pe);
			HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
		}
		else if (mask == _hoops_AHRAP &&
			ANYBIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_AHRAP)) {
			p = _hoops_RHCRS (_hoops_RCIHP, option->value.option_list, p, pe);
			HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
		}
		else if (mask == _hoops_HHRAP &&
			ANYBIT (_hoops_RCIHP->_hoops_GHRAP, _hoops_HHRAP)) {
			p = _hoops_AHCRS (_hoops_RCIHP, option->value.option_list, p, pe);
			HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
		}
		else if (!ANYBIT (mask, _hoops_RCIHP->_hoops_GHRAP))
			HI_Return_Chars (list, _hoops_GGCIR, "off", 3);
		else
			HI_Return_Chars (list, _hoops_GGCIR, "on", 2);

		HI_Free_Option_List (_hoops_RIGC, option);
		return;			/* _hoops_GGAR _hoops_AAP _hoops_GIR */
	}

	if (mask == _hoops_GRRAP) {	/* _hoops_SPCAI-_hoops_HCSP */
		if (!ANYBIT (_hoops_RCIHP->_hoops_SCIAA, _hoops_SGICA) ||
			!BIT (_hoops_RCIHP->_hoops_PRSI->mask, _hoops_HRSI)) {
			HE_ERROR (HEC_RENDERING, HES_NO_LOCAL_SETTING, Sprintf_SP (null, "'%s' has no setting in '%p'", _hoops_HSGIH, _hoops_RCIHP->owner));
			HI_Free_Option_List (_hoops_RIGC, option);
			return;
		}

		if (!BIT (_hoops_RCIHP->_hoops_PRSI->value, _hoops_HRSI))
			HI_Return_Chars (list, _hoops_GGCIR, "off", 3);
		else
			HI_Return_Chars (list, _hoops_GGCIR, "on", 2);

		HI_Free_Option_List (_hoops_RIGC, option);
		return;			/* _hoops_GGAR _hoops_AAP _hoops_GIR */
	}

	if ((mask & _hoops_AHGI) == _hoops_ASGAP) {
		if (!ANYBIT (mask, _hoops_RCIHP->_hoops_PSHCA)) {
			HE_ERROR (HEC_RENDERING, HES_NO_LOCAL_SETTING, Sprintf_SP (null, "'%s' has no setting in '%p'", _hoops_HSGIH, _hoops_RCIHP->owner));
			HI_Free_Option_List (_hoops_RIGC, option);
			return;
		}
	}
	else {
		if (!ANYBIT (mask, _hoops_RCIHP->_hoops_SCIAA)) {
			HE_ERROR (HEC_RENDERING, HES_NO_LOCAL_SETTING, Sprintf_SP (null, "'%s' has no setting in '%p'", _hoops_HSGIH, _hoops_RCIHP->owner));
			HI_Free_Option_List (_hoops_RIGC, option);
			return;
		}
	}

	if (mask == _hoops_GSIAA) {
		if (!BIT (_hoops_RCIHP->_hoops_RSIAA, _hoops_GSIAA))
			HI_Return_Chars (list, _hoops_GGCIR, "off", 3);
		else if (ALLBITS (_hoops_RCIHP->locks->normal.mask._hoops_IPPGR &
						  _hoops_RCIHP->locks->normal.value._hoops_IPPGR, _hoops_PIIRS))
			HI_Return_Chars (list, _hoops_GGCIR, "on", 2);
		else {
			p = _hoops_RGCRS (buf, option->value.option_list, &_hoops_RCIHP->locks->normal, true);
			HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
		}
	}
	else if (mask == _hoops_RGRAP) {
		if (!BIT (_hoops_RCIHP->_hoops_RSIAA, _hoops_RGRAP))
			HI_Return_Chars (list, _hoops_GGCIR, "off", 3);
		else if (ALLBITS (_hoops_RCIHP->locks->_hoops_SACRP.mask._hoops_IPPGR &
						  _hoops_RCIHP->locks->_hoops_SACRP.value._hoops_IPPGR, _hoops_PIIRS))
			HI_Return_Chars (list, _hoops_GGCIR, "on", 2);
		else {
			p = _hoops_RGCRS (buf, option->value.option_list, &_hoops_RCIHP->locks->_hoops_SACRP, true);
			HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
		}
	}
	else if (mask == _hoops_PRRAP) {
		long			tmp = _hoops_RCIHP->_hoops_IRARR;

		p = HI_Sprintf1 (p, pe, "%D", &tmp);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_CRRAP) {
		long			tmp = _hoops_RCIHP->_hoops_CHIH;

		p = HI_Sprintf1 (p, pe, "%D", &tmp);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_IPRAP) {
		long			tmp = _hoops_RCIHP->_hoops_IGAAP;

		p = HI_Sprintf1 (p, pe, "%D", &tmp);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_SARAP) {
		long			tmp = _hoops_RCIHP->_hoops_SHIH;

		p = HI_Sprintf1 (p, pe, "%D", &tmp);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_GPRAP) {
		if (_hoops_RCIHP->_hoops_GSAAP == _hoops_RCIHP->_hoops_RSAAP) {
			long			tmp = _hoops_RCIHP->_hoops_GSAAP;

			p = HI_Sprintf1 (p, pe, "%D", &tmp);
		}
		else if (_hoops_RCIHP->_hoops_RSAAP == -1) {
			long			tmp = _hoops_RCIHP->_hoops_GSAAP;

			p = HI_Sprintf1 (p, pe, "line=%D", &tmp);
		}
		else if (_hoops_RCIHP->_hoops_GSAAP == -1) {
			long			tmp = _hoops_RCIHP->_hoops_RSAAP;

			p = HI_Sprintf1 (p, pe, "edge=%D", &tmp);
		}
		else {
			long			tmp = _hoops_RCIHP->_hoops_GSAAP;

			p = HI_Sprintf1 (p, pe, "line=%D,", &tmp);

			tmp = _hoops_RCIHP->_hoops_RSAAP;
			p = HI_Sprintf1 (p, pe, "edge=%D", &tmp);
		}

		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_IRRAP) {
		if (_hoops_RCIHP->_hoops_PSAAP == Display_List_NONE)
			HI_Return_Chars (list, _hoops_GGCIR, "off", 3);
		else if (_hoops_RCIHP->_hoops_PSAAP == Display_List_GEOMETRY)
			HI_Return_Chars (list, _hoops_GGCIR, "on", 2);
		else if (_hoops_RCIHP->_hoops_PSAAP == Display_List_SEGMENT)
			HI_Return_Chars (list, _hoops_GGCIR, "segment", 7);
		else if (_hoops_RCIHP->_hoops_PSAAP == _hoops_ASAAP)
			HI_Return_Chars (list, _hoops_GGCIR, "segment tree", 12);
	}
	else if (mask == _hoops_IARAP) {
		float			tmp = _hoops_RCIHP->_hoops_HHAIR->_hoops_ACSRP;

		p = HI_Sprintf1 (p, pe, "%f", &tmp);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_RPRAP) {
		float			tmp = _hoops_RCIHP->_hoops_HHAIR->_hoops_PCSRP;

		p = HI_Sprintf1 (p, pe, "%f", &tmp);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_PARAP) {
		if (BIT (_hoops_RCIHP->_hoops_SIRAP, Quantization_THRESHOLD))
			HI_Return_Chars (list, _hoops_GGCIR, "threshold", 9);
		else if (BIT (_hoops_RCIHP->_hoops_SIRAP, Quantization_DITHER))
			HI_Return_Chars (list, _hoops_GGCIR, "dither", 6);
		else
			HI_Return_Chars (list, _hoops_GGCIR, "error diffusion", 15);
	}
	else if (mask == _hoops_SRRAP) {
		if (BIT (_hoops_RCIHP->_hoops_SRI, _hoops_SGAAP))
			p = HI_Copy_Chars ("hardware z buffer", p);
		else if (BIT (_hoops_RCIHP->_hoops_SRI, _hoops_GRAAP))
			p = HI_Copy_Chars ("painters", p);
		else if (BIT (_hoops_RCIHP->_hoops_SRI, _hoops_RRAAP))
			p = HI_Copy_Chars ("software z buffer", p);
		else if (BIT (_hoops_RCIHP->_hoops_SRI, _hoops_PRAAP))
			p = HI_Copy_Chars ("hidden line", p);
		else if (BIT (_hoops_RCIHP->_hoops_SRI, _hoops_SICI))
			p = HI_Copy_Chars ("fast hidden line", p);
		else if (BIT (_hoops_RCIHP->_hoops_SRI, _hoops_HSSS))
			p = HI_Copy_Chars ("z sort only", p);
		else if (BIT (_hoops_RCIHP->_hoops_SRI, _hoops_GAI))
			p = HI_Copy_Chars ("priority", p);

		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(p - buf));
	}
	else if (mask == _hoops_GGRAP) {
		p = _hoops_CACRS (_hoops_RCIHP, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(p - buf));
	}
	else if (mask == _hoops_CSHCA) {
		p = _hoops_SACRS (_hoops_RCIHP, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(p - buf));
	}
	else if (mask == _hoops_GGICA) {
		p = _hoops_GACRS (_hoops_RCIHP, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_IGICA) {
		p = _hoops_SGCRS (_hoops_RCIHP, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_AGRAP) {
		p = _hoops_GRCRS (_hoops_RCIHP, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_PRICA) {
		p = _hoops_RRCRS (_hoops_RCIHP, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_SGICA) {
		p = _hoops_RACRS (_hoops_RCIHP, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_IRICA) {
		p = _hoops_HACRS (_hoops_RCIHP, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_CRICA) {
		p = _hoops_IACRS (_hoops_RCIHP, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_SRICA) {
		p = _hoops_GPCRS (_hoops_RCIHP, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_HRICA) {
		p = _hoops_RPCRS (_hoops_RCIHP, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_ARICA) {
		p = _hoops_SRCRS (_hoops_RCIHP, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_RRICA) {
		p = _hoops_HRCRS (_hoops_RCIHP, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_CSGAP) {
		p = _hoops_IRCRS (_hoops_RCIHP, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_SSGAP) {
		p = _hoops_CRCRS (_hoops_RCIHP, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_AGICA) {
		p = _hoops_APCRS (_hoops_RCIHP, option->value.option_list, p, pe);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_HRRAP) {
		p = HI_Sprintf1 (p, pe, "%f,", (void *)&_hoops_RCIHP->_hoops_HHAAP[0]);
		p = HI_Sprintf1 (p, pe, "%f", (void *)&_hoops_RCIHP->_hoops_HHAAP[1]);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_APRAP) {
		p = HI_Sprintf1 (p, pe, "%f,", (void *)&_hoops_RCIHP->_hoops_HCIH.left);
		p = HI_Sprintf1 (p, pe, "%f,", (void *)&_hoops_RCIHP->_hoops_HCIH.right);
		p = HI_Sprintf1 (p, pe, "%f,", (void *)&_hoops_RCIHP->_hoops_HCIH.bottom);
		p = HI_Sprintf1 (p, pe, "%f",  (void *)&_hoops_RCIHP->_hoops_HCIH.top);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_PPRAP) {
		p = HI_Sprintf1 (p, pe, "%f,", (void *)&_hoops_RCIHP->_hoops_HHAIR->_hoops_HRGA.x);
		p = HI_Sprintf1 (p, pe, "%f,", (void *)&_hoops_RCIHP->_hoops_HHAIR->_hoops_HRGA.y);
		p = HI_Sprintf1 (p, pe, "%f",  (void *)&_hoops_RCIHP->_hoops_HHAIR->_hoops_HRGA.z);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_GARAP) {
		p = HI_Sprintf1 (p, pe, "%f,", (void *)&_hoops_RCIHP->_hoops_IHAAP[0]);
		p = HI_Sprintf1 (p, pe, "%f", (void *)&_hoops_RCIHP->_hoops_IHAAP[1]);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_RARAP) {
		p = HI_Sprintf1 (p, pe,"R=%f ", &_hoops_RCIHP->_hoops_CHAAP.red);
		p = HI_Sprintf1 (p, pe,"G=%f ", &_hoops_RCIHP->_hoops_CHAAP.green);
		p = HI_Sprintf1 (p, pe,"B=%f",	&_hoops_RCIHP->_hoops_CHAAP.blue);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_CPRAP) {
		p = HI_Sprintf1 (p, pe,"R=%f ", &_hoops_RCIHP->_hoops_HRA.red);
		p = HI_Sprintf1 (p, pe,"G=%f ", &_hoops_RCIHP->_hoops_HRA.green);
		p = HI_Sprintf1 (p, pe,"B=%f",	&_hoops_RCIHP->_hoops_HRA.blue);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_HPH) {
		p = HI_Sprintf1 (p, pe, "hither=%f,", (void *)&_hoops_RCIHP->_hoops_HHAIR->_hoops_CRIR.hither);
		p = HI_Sprintf1 (p, pe, "yon=%f",	  (void *)&_hoops_RCIHP->_hoops_HHAIR->_hoops_CRIR.yon);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_HPRAP) {
		p = HI_Sprintf1 (p, pe, "%f", (void*)&_hoops_RCIHP->_hoops_CSRS);
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if (mask == _hoops_ISGAP) {
		bool _hoops_HICRS=true;
		if (ALLBITS(_hoops_RCIHP->_hoops_CHP.mask, _hoops_GAAAP)) {
			if (ALLBITS(_hoops_RCIHP->_hoops_CHP.value, _hoops_GAAAP)) {
				HI_Return_Chars (list, _hoops_GGCIR, "on", 2);
				_hoops_HICRS=false;
			}
			else if (!ANYBIT(_hoops_RCIHP->_hoops_CHP.value, _hoops_GAAAP)) {
				HI_Return_Chars (list, _hoops_GGCIR, "off", 3);
				_hoops_HICRS=false;
			}
		}
		if (_hoops_HICRS) {
			if (BIT(_hoops_RCIHP->_hoops_CHP.mask, _hoops_GPSP)) {
				if (!BIT(_hoops_RCIHP->_hoops_CHP.value, _hoops_GPSP))
					p = HI_Copy_Chars ("no ", p);
				p = HI_Copy_Chars ("screen,", p);
			}
			if (BIT(_hoops_RCIHP->_hoops_CHP.mask, _hoops_CRAAP)) {
				if (!BIT(_hoops_RCIHP->_hoops_CHP.value, _hoops_CRAAP))
					p = HI_Copy_Chars ("no ", p);
				p = HI_Copy_Chars ("text,", p);
			}
			if (BIT(_hoops_RCIHP->_hoops_CHP.mask, _hoops_SHP)) {
				if (!BIT(_hoops_RCIHP->_hoops_CHP.value, _hoops_SHP))
					p = HI_Copy_Chars ("no ", p);
				p = HI_Copy_Chars ("lines,", p);
			}
			--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
			HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
		}
	}
	else if (mask == _hoops_CARAP) {
#ifndef DISABLE_AIR_OPTIONS
		if (BIT (_hoops_RCIHP->_hoops_RCRAP, _hoops_PCRAP))
			p = HI_Copy_Chars ("radiosity,", p);
		if (BIT (_hoops_RCIHP->_hoops_RCRAP, _hoops_HCRAP))
			p = HI_Copy_Chars ("ray-trace,", p);
#endif
		if (BIT (_hoops_RCIHP->_hoops_RCRAP, _hoops_ICRAP))
			p = HI_Copy_Chars ("software frame buffer,", p);
		if (BIT (_hoops_RCIHP->_hoops_RCRAP, _hoops_ACRAP) ||
			_hoops_RCIHP->_hoops_RCRAP == false)
			p = HI_Copy_Chars ("standard,", p);
		--p;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
		HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
	}
	else if ((mask & _hoops_AHGI) == _hoops_ASGAP) {
		if (!ANYBIT (mask, _hoops_RCIHP->_hoops_RRRAP))
			HI_Return_Chars (list, _hoops_GGCIR, "off", 3);
		else
			HI_Return_Chars (list, _hoops_GGCIR, "on", 2);
	}
	else {
		if (!ANYBIT (mask, _hoops_RCIHP->_hoops_RSIAA))
			HI_Return_Chars (list, _hoops_GGCIR, "off", 3);
		else
			HI_Return_Chars (list, _hoops_GGCIR, "on", 2);
	}

	HI_Free_Option_List (_hoops_RIGC, option);
}
#endif


HC_INTERFACE void HC_CDECL HC_Show_Rendering_Options (
	char *			list)
{
	_hoops_PAPPR context("Show_Rendering_Options ");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Rendering_Options () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PSRPP)) != null) {

		_hoops_RHAIR	*_hoops_RCIHP;
		if ((_hoops_RCIHP = (_hoops_RHAIR *)HI_Find_Attribute (context, target, HK_RENDERING_OPTIONS)) != null) {
			HI_Show_Rendering_Options (_hoops_RCIHP, list, -1);
			_hoops_HPRH (_hoops_RCIHP);
		}
		_hoops_IRRPR();
	}
#endif
}


#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_Net_Rendering_Options (
	int					count,
	Key const *			keys,
	char *				list)
{
	_hoops_PAPPR context("PShow_Net_Rendering_Options ");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Rendering_Options () */\n");
	);

	_hoops_RHAIR *	_hoops_RCIHP;
	if ((_hoops_RCIHP = (_hoops_RHAIR *) HI_Find_Attribute_And_Lock(context, _hoops_PSRPP, _hoops_HRPCR, count, keys)) != null) {
		HI_Show_Rendering_Options (_hoops_RCIHP, list, -1);
		_hoops_HPRH (_hoops_RCIHP);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(list, -1, "", 0);
#endif
}
#endif



/****/


HC_INTERFACE void HC_CDECL HC_Show_One_Rendering_Option (
	char const *		_hoops_HSGIH,
	char *				list)
{
	_hoops_PAPPR context("Show_One_Rendering_Option ");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_Rendering_Option () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PSRPP)) != null) {

		_hoops_RHAIR	*_hoops_RCIHP;
		if ((_hoops_RCIHP = (_hoops_RHAIR *)HI_Find_Attribute (context, target, HK_RENDERING_OPTIONS)) != null) {
			_hoops_IICRS (context, _hoops_RCIHP, _hoops_HSGIH, list, -1);
			_hoops_HPRH (_hoops_RCIHP);
		}
		_hoops_IRRPR();
	}
#endif
}


#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Rendering_Opti  (
	int					count,
	Key const *			keys,
	char const *		_hoops_HSGIH,
	char *				list)
{
	_hoops_PAPPR context("PShow_One_Net_Rendering_Option ");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_One_Net_Rendering_Option () */\n");
	);

	_hoops_RHAIR *	_hoops_RCIHP;
	if ((_hoops_RCIHP = (_hoops_RHAIR *) HI_Find_Attribute_And_Lock(context, _hoops_PSRPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_IICRS (context, _hoops_RCIHP, _hoops_HSGIH, list, -1);
		_hoops_HPRH (_hoops_RCIHP);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(list, -1, "", 0);
#endif
}
#endif


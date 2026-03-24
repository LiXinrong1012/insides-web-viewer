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
 * $Id: obf_tmp.txt 1.152 2010-12-15 00:55:55 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "please.h"


local const _hoops_IGRCR _hoops_RPGAA[] = {
	{_hoops_GPSA,	_hoops_GRRCR ("left"),							_hoops_RRRCR, 0, false},
	{_hoops_SASA,	_hoops_GRRCR ("right"),							_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_APGAA = {
	_hoops_GGAPR (_hoops_RPGAA),
	_hoops_RPGAA,
};



local const _hoops_IGRCR _hoops_APIIH[] = {
	{_hoops_HGIRP,							_hoops_GRRCR ("off"),							_hoops_RRRCR, 0, false},
	{_hoops_HGIRP,							_hoops_GRRCR ("no"),							_hoops_RRRCR, 0, false},
	{_hoops_HGIRP,							_hoops_GRRCR ("false"),							_hoops_RRRCR, 0, false},
	{_hoops_HPIRP,				_hoops_GRRCR ("on"),							_hoops_RRRCR, 0, false},
	{_hoops_HPIRP,				_hoops_GRRCR ("yes"),							_hoops_RRRCR, 0, false},
	{_hoops_HPIRP,				_hoops_GRRCR ("true"),							_hoops_RRRCR, 0, false},
	{_hoops_IRIRP,				_hoops_GRRCR ("sprite"),						_hoops_RRRCR, 0, false},
	{_hoops_IRIRP,				_hoops_GRRCR ("sprites"),						_hoops_RRRCR, 0, false},
	{_hoops_IRIRP,				_hoops_GRRCR ("spriting"),						_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_PPIIH = {
	_hoops_GGAPR (_hoops_APIIH),
	_hoops_APIIH,
};



local const _hoops_IGRCR _hoops_HPIIH[] = {
	{_hoops_PRCRP,			_hoops_GRRCR ("default"),						_hoops_RRRCR, 0, false},
	{_hoops_HRCRP,				_hoops_GRRCR ("lmv"),							_hoops_RRRCR, 0, false},

};

local const _hoops_HPAGA _hoops_IPIIH = {
	_hoops_GGAPR (_hoops_HPIIH),
	_hoops_HPIIH,
};




#define _hoops_CPIIH	112
#define _hoops_SPIIH	113

/* _hoops_PIP, _hoops_RGAR _hoops_SPR _hoops_HCSP _hoops_HIS _hoops_CRSRR _hoops_PIRA _hoops_HRGR _hoops_PPRAR */
local const _hoops_IGRCR _hoops_GHIIH[] = {
	{_hoops_SIIRP,		_hoops_GRRCR ("pixel threshold"),		_hoops_APRCA, 1, false},
	{_hoops_GCIRP,			_hoops_GRRCR ("use octree"),			_hoops_RRRCR, 0, true},
	{_hoops_CPIIH,						_hoops_GRRCR ("on"),					_hoops_RRRCR, 0, false},
	{_hoops_SPIIH,						_hoops_GRRCR ("off"),					_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_RHIIH = {
	_hoops_GGAPR (_hoops_GHIIH),
	_hoops_GHIIH,
};



local const _hoops_IGRCR	_hoops_AHIIH[] = {
	{Heur_MAX_EXTENT_MODE_DEFER,		_hoops_GRRCR("defer"),			_hoops_RRRCR, 0, false},
	{_hoops_GIIRP,		_hoops_GRRCR("bounding"),		_hoops_RRRCR, 0, false},
	{_hoops_SHIRP,			_hoops_GRRCR("dot"),			_hoops_RRRCR, 0, false},
	{_hoops_CHIRP,			_hoops_GRRCR("none"),			_hoops_RRRCR, 0, false},
};

local const	_hoops_HPAGA _hoops_PHIIH = {
	_hoops_GGAPR (_hoops_AHIIH),
	_hoops_AHIIH,
};



local const _hoops_IGRCR	_hoops_HHIIH[] = {
	{_hoops_AIIRP,		_hoops_GRRCR("segment"),		_hoops_RRRCR, 0, false},
	{_hoops_PIIRP,	_hoops_GRRCR("geometry"),		_hoops_RRRCR, 0, false},
	{_hoops_GIHS,	_hoops_GRRCR("primitive"),		_hoops_RRRCR, 0, false},
	{_hoops_HIIRP,			_hoops_GRRCR("all"),			_hoops_RRRCR, 0, false},
	{_hoops_HIIRP,			_hoops_GRRCR("default"),		_hoops_RRRCR, 0, false},
};

local const	_hoops_HPAGA _hoops_IHIIH = {
	_hoops_GGAPR (_hoops_HHIIH),
	_hoops_HHIIH,
};


local const _hoops_IGRCR _hoops_CHIIH[] = {
	{_hoops_CPIRP,					_hoops_GRRCR ("off"),							_hoops_RRRCR, 0, false},
	{_hoops_CPIRP,					_hoops_GRRCR ("no"),							_hoops_RRRCR, 0, false},
	{_hoops_CPIRP,					_hoops_GRRCR ("none"),							_hoops_RRRCR, 0, false},
	{_hoops_CPIRP,					_hoops_GRRCR ("false"),							_hoops_RRRCR, 0, false},
	{_hoops_IHIRP,					_hoops_GRRCR ("on"),							_hoops_RRRCR, 0, false},
	{_hoops_IHIRP,					_hoops_GRRCR ("yes"),							_hoops_RRRCR, 0, false},
	{_hoops_IHIRP,					_hoops_GRRCR ("true"),							_hoops_RRRCR, 0, false},
	{Heur_Culling_VIEW_FRUSTUM,			_hoops_GRRCR ("view frustum"),					_hoops_RRRCR, 0, true},
	{_hoops_SPIRP,			_hoops_GRRCR ("obscuration"),					_hoops_GHAGA, -999, true, &_hoops_RHIIH},
	{Heur_Culling_EXTENT,				_hoops_GRRCR ("maximum extent"),				_hoops_APRCA, -1, true},
	{Heur_Culling_EXTENT,				_hoops_GRRCR ("max extent"),					_hoops_APRCA, -1, true},
	{_hoops_RIHS,			_hoops_GRRCR ("hard extent"),					_hoops_APRCA, -1, true},
	{_hoops_AHIRP,		_hoops_GRRCR ("vertex threshold"),				_hoops_APRCA, -1, true},
	{_hoops_RHIRP,			_hoops_GRRCR ("maximum extent mode"),			_hoops_GHAGA, 1, true, &_hoops_PHIIH},
	{_hoops_HHIRP,			_hoops_GRRCR ("maximum extent level"),			_hoops_GHAGA, -9, true, &_hoops_IHIIH},

	{_hoops_GHIRP,				_hoops_GRRCR ("vector"),						_hoops_SPPCR, 3, true},
	{_hoops_PHIRP,		_hoops_GRRCR ("vector tolerance"),				_hoops_SPPCR, 1, true},

	/* _hoops_ASSS _hoops_IGRSP _hoops_IIGR _hoops_GIGR _hoops_SRSGR _hoops_RCGRA _hoops_IS "_hoops_CIAS _hoops_CRRPA=1" */
	{Heur_Culling_EXTENT,				_hoops_GRRCR ("subpixel"),						_hoops_RRRCR, 0, true},
	{Heur_Culling_EXTENT,				_hoops_GRRCR ("sub pixel"),						_hoops_RRRCR, 0, true},
	{Heur_Culling_EXTENT,				_hoops_GRRCR ("sub-pixel"),						_hoops_RRRCR, 0, true},
};

local const _hoops_HPAGA _hoops_SHIIH = {
	_hoops_GGAPR (_hoops_CHIIH),
	_hoops_CHIIH,
};

local const _hoops_IGRCR _hoops_GIIIH[] = {
	{_hoops_HGIRP,									_hoops_GRRCR ("off"),					_hoops_RRRCR, 0, false},
	{_hoops_HGIRP,									_hoops_GRRCR ("no"),					_hoops_RRRCR, 0, false},
	{_hoops_HGIRP,									_hoops_GRRCR ("false"),					_hoops_RRRCR, 0, false},
	{_hoops_HAIRP,						_hoops_GRRCR ("on"),					_hoops_RRRCR, 0, false},
	{_hoops_HAIRP,						_hoops_GRRCR ("yes"),					_hoops_RRRCR, 0, false},
	{_hoops_HAIRP,						_hoops_GRRCR ("true"),					_hoops_RRRCR, 0, false},
	{_hoops_IAIRP,							_hoops_GRRCR ("unit"),					_hoops_RRRCR, 0, false},
	{_hoops_SAIRP,					_hoops_GRRCR ("recursive"),				_hoops_RRRCR, 0, false},

};

local const _hoops_HPAGA _hoops_RIIIH = {
	_hoops_GGAPR (_hoops_GIIIH),
	_hoops_GIIIH,
};

local const _hoops_IGRCR _hoops_AIIIH[] = {
	{_hoops_SCIRP,			_hoops_GRRCR ("world volume"),					_hoops_SPPCR, -1, true},
	{_hoops_GSIRP,			_hoops_GRRCR ("screen extent"),					_hoops_SPPCR, -1, true},
	{_hoops_RSIRP,				_hoops_GRRCR ("distance"),						_hoops_SPPCR, -1, true},
	{_hoops_ASIRP,				_hoops_GRRCR ("divergence"),					_hoops_SPPCR, -1, true},
	{_hoops_PSIRP,				_hoops_GRRCR ("density"),						_hoops_SPPCR, -1, true},
	{_hoops_HSIRP,				_hoops_GRRCR ("priority"),						_hoops_SPPCR, -1, true},

	{_hoops_ISIRP,					_hoops_GRRCR ("all"),							_hoops_SPPCR, -1, true},
	{_hoops_ISIRP,					_hoops_GRRCR ("everything"),					_hoops_SPPCR, -1, true},
};

local const _hoops_HPAGA _hoops_PIIIH = {
	_hoops_GGAPR (_hoops_AIIIH),
	_hoops_AIIIH,
};

local const _hoops_IGRCR _hoops_HIIIH[] = {
	{_hoops_HCIRP,					_hoops_GRRCR ("shell"),						_hoops_APRCA, 1, true},
	{_hoops_ICIRP,				_hoops_GRRCR ("polyline"),					_hoops_APRCA, 1, true},
	{_hoops_HCIRP,					_hoops_GRRCR ("shells"),					_hoops_APRCA, 1, true},
	{_hoops_ICIRP,				_hoops_GRRCR ("polylines"),					_hoops_APRCA, 1, true},
};

local const _hoops_HPAGA _hoops_IIIIH = {
	_hoops_GGAPR (_hoops_HIIIH),
	_hoops_HIIIH,
};


local const _hoops_IGRCR _hoops_CIIIH[] = {
	{_hoops_PGCRP,		_hoops_GRRCR ("entity"),		_hoops_RRRCR, 0, false},
	{_hoops_PGCRP,		_hoops_GRRCR ("geometry"),		_hoops_RRRCR, 0, false},
	{_hoops_HGCRP,		_hoops_GRRCR ("segment"),		_hoops_RRRCR, 0, false},
	{_hoops_IGCRP,	_hoops_GRRCR ("segment tree"),	_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_SIIIH = {
	_hoops_GGAPR (_hoops_CIIIH),	_hoops_CIIIH,
};

#define _hoops_GCIIH -9999

local const _hoops_IGRCR _hoops_RCIIH[] = {
	{_hoops_PICAR,						_hoops_GRRCR ("clipping"),						_hoops_RRRCR, 0, true},
	{_hoops_IGIRP,				_hoops_GRRCR ("transformation"),				_hoops_RRRCR, 0, true},
	{_hoops_CGIRP,		_hoops_GRRCR ("intersecting polygon"),			_hoops_RRRCR, 0, true},
	{_hoops_GRIRP,			_hoops_GRRCR ("polygon crossing"),				_hoops_RRRCR, 0, true},
	{_hoops_SGIRP,				_hoops_GRRCR ("backplane cull"),				_hoops_RRRCR, 0, true},
	{_hoops_CGCS,				_hoops_GRRCR ("concave polygon"),				_hoops_RRRCR, 0, true},
	{_hoops_RRIRP,			_hoops_GRRCR ("incremental update"),			_hoops_RRRCR, 0, true},
	{_hoops_GCIIH,			_hoops_GRRCR ("memory purge"),					_hoops_RRRCR, 0, true},
	{_hoops_HPIRP,				_hoops_GRRCR ("quick move"),					_hoops_GHAGA, -1, true, &_hoops_PPIIH},
	{_hoops_PRIRP,				_hoops_GRRCR ("partial erase"),					_hoops_RRRCR, 0, true},
	{_hoops_GPSA|
	 _hoops_SASA,	_hoops_GRRCR ("polygon handedness"),			_hoops_GHAGA, 1, true, &_hoops_APGAA},
	{_hoops_SICIA,		_hoops_GRRCR ("related selection limit"),		_hoops_APRCA, 1, true},
	{_hoops_SRIRP,		_hoops_GRRCR ("internal selection limit"),		_hoops_AASAP, -9, true, &_hoops_IIIIH},
	{_hoops_GAIRP,			_hoops_GRRCR ("selection sorting"),				_hoops_RRRCR, 0, true},
 
	{_hoops_IRI,				_hoops_GRRCR ("hidden surfaces"),				_hoops_RRRCR, 0, true},
	{_hoops_IGIRP,				_hoops_GRRCR ("transformations"),				_hoops_RRRCR, 0, true},
	{_hoops_CGIRP,		_hoops_GRRCR ("intersecting polygons"),			_hoops_RRRCR, 0, true},
	{_hoops_GRIRP,			_hoops_GRRCR ("polygon crossings"),				_hoops_RRRCR, 0, true},
	{_hoops_SGIRP,				_hoops_GRRCR ("backplane culls"),				_hoops_RRRCR, 0, true},
	{_hoops_SGIRP,				_hoops_GRRCR ("backplane culling"),				_hoops_RRRCR, 0, true},
	{_hoops_CGCS,				_hoops_GRRCR ("concave polygons"),				_hoops_RRRCR, 0, true},
	{_hoops_RRIRP,			_hoops_GRRCR ("incremental updates"),			_hoops_RRRCR, 0, true},
	{_hoops_HPIRP,				_hoops_GRRCR ("quick moves"),					_hoops_GHAGA, -1, true, &_hoops_PPIIH},

	{_hoops_RAIRP,						_hoops_GRRCR ("culling"),						_hoops_GHAGA, -99, true, &_hoops_SHIIH},
	{_hoops_RAIRP,						_hoops_GRRCR ("cull"),							_hoops_GHAGA, -99, true, &_hoops_SHIIH},
	{_hoops_RAIRP,						_hoops_GRRCR ("culls"),							_hoops_GHAGA, -99, true, &_hoops_SHIIH},

	{_hoops_AAIRP,				_hoops_GRRCR ("visual selection"),				_hoops_RRRCR, 0, true},
	{_hoops_CCIAA,				_hoops_GRRCR ("exclude bounding"),				_hoops_RRRCR, 0, true},

	{_hoops_PAIRP,				_hoops_GRRCR ("detail selection"),				_hoops_RRRCR, 0, true},
	{_hoops_PAIRP,				_hoops_GRRCR ("detailed selection"),			_hoops_RRRCR, 0, true},

	{_hoops_IPIRP,				_hoops_GRRCR ("ordered drawing"),				_hoops_GHAGA, -1, true, &_hoops_RIIIH},
	{_hoops_CAIRP,				_hoops_GRRCR ("ordered weight"),				_hoops_GHAGA, -99, false, &_hoops_PIIIH},
	{_hoops_CAIRP,				_hoops_GRRCR ("ordered weights"),				_hoops_GHAGA, -99, false, &_hoops_PIIIH},

	{_hoops_GPIRP,					_hoops_GRRCR ("static model"),					_hoops_RRRCR, 0, true},
	{_hoops_GPIRP,					_hoops_GRRCR ("static"),						_hoops_RRRCR, 0, true},

	{_hoops_RPIRP,				_hoops_GRRCR ("selection level"),				_hoops_GHAGA, 1, false, &_hoops_SIIIH},
																				
	{_hoops_APIRP,			_hoops_GRRCR ("force defer batch"),				_hoops_APRCA, 1, true},

	{_hoops_PPIRP,					_hoops_GRRCR ("model type"),					_hoops_GHAGA, -1, false, &_hoops_IPIIH},
	// _hoops_GHSHA _hoops_RGAR
	{-_hoops_CPSHA,							_hoops_GRRCR ("^"),						_hoops_RRRCR, 0, false},
	{-_hoops_HPSHA,							_hoops_GRRCR ("v"),						_hoops_RRRCR, 0, false},
	{-_hoops_SPSHA,						_hoops_GRRCR ("o"),						_hoops_RRRCR, 0, false},
	{-_hoops_IPSHA,					_hoops_GRRCR ("*"),						_hoops_RRRCR, 0, false},

	{-_hoops_SARPH,						_hoops_GRRCR ("selection proximity"),	_hoops_SPPCR, 1, true},
};


local Attribute *_hoops_ACIIH (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR) 
{
	_hoops_GHAIR const *		_hoops_PCIIH = (_hoops_GHAIR const *)_hoops_CPACR;
	_hoops_GHAIR alter *		_hoops_HCIIH = (_hoops_GHAIR alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (item);

	if (_hoops_PCIIH != null &&
		_hoops_PCIIH->mask == _hoops_HCIIH->mask &&
		_hoops_PCIIH->value == _hoops_HCIIH->value &&
		_hoops_PCIIH->_hoops_APH.mask == _hoops_HCIIH->_hoops_APH.mask &&
		_hoops_PCIIH->_hoops_APH.value == _hoops_HCIIH->_hoops_APH.value &&
		(!BIT (_hoops_HCIIH->mask, _hoops_SICIA) ||
		 _hoops_PCIIH->_hoops_GCCIA == _hoops_HCIIH->_hoops_GCCIA) &&
		(!BIT (_hoops_HCIIH->mask, _hoops_SRIRP) ||
		 (_hoops_PCIIH->_hoops_CCIRP.mask == _hoops_HCIIH->_hoops_CCIRP.mask &&
		 _hoops_PCIIH->_hoops_CCIRP.value == _hoops_HCIIH->_hoops_CCIRP.value &&
		 _hoops_PCIIH->_hoops_CCIRP._hoops_SPHPR == _hoops_HCIIH->_hoops_CCIRP._hoops_SPHPR &&
		  _hoops_PCIIH->_hoops_CCIRP.polyline == _hoops_HCIIH->_hoops_CCIRP.polyline)) && 
		(!BIT (_hoops_HCIIH->mask, _hoops_RPIRP) ||
		 _hoops_PCIIH->_hoops_GRCRP == _hoops_HCIIH->_hoops_GRCRP) &&
		(!BIT (_hoops_HCIIH->mask, _hoops_PPIRP) ||
		 _hoops_PCIIH->_hoops_IRCRP == _hoops_HCIIH->_hoops_IRCRP) &&
		(!BIT (_hoops_HCIIH->_hoops_APH.mask, _hoops_SPIRP) ||
		 (_hoops_PCIIH->_hoops_APH._hoops_ACIRP == _hoops_HCIIH->_hoops_APH._hoops_ACIRP && 
		 _hoops_PCIIH->_hoops_APH._hoops_PCIRP == _hoops_HCIIH->_hoops_APH._hoops_PCIRP)) && 
		(!BIT (_hoops_HCIIH->_hoops_APH.mask, Heur_Culling_EXTENT) ||
		 _hoops_PCIIH->_hoops_APH._hoops_GRGC == _hoops_HCIIH->_hoops_APH._hoops_GRGC) &&
		 (!BIT (_hoops_HCIIH->_hoops_APH.mask, _hoops_RIHS) ||
		 _hoops_PCIIH->_hoops_APH._hoops_GCHS == _hoops_HCIIH->_hoops_APH._hoops_GCHS) &&
		(!BIT (_hoops_HCIIH->_hoops_APH.mask, _hoops_AHIRP) ||
		 _hoops_PCIIH->_hoops_APH._hoops_CIIRP == _hoops_HCIIH->_hoops_APH._hoops_CIIRP) &&
		(!BIT (_hoops_HCIIH->mask, _hoops_CAIRP) ||
		 _hoops_PCIIH->_hoops_CSIRP == _hoops_HCIIH->_hoops_CSIRP) &&
		 (!BIT (_hoops_HCIIH->_hoops_APH.mask, _hoops_RHIRP) ||
		 _hoops_PCIIH->_hoops_APH._hoops_PCHS == _hoops_HCIIH->_hoops_APH._hoops_PCHS) &&
		 (!BIT (_hoops_HCIIH->_hoops_APH.mask, _hoops_HHIRP) ||
		 _hoops_PCIIH->_hoops_APH._hoops_SHHS == _hoops_HCIIH->_hoops_APH._hoops_SHHS) &&
		 (!BIT (_hoops_HCIIH->_hoops_APH.mask, _hoops_GHIRP) ||
		 (_hoops_PCIIH->_hoops_APH.vector.x == _hoops_HCIIH->_hoops_APH.vector.x && 
		  _hoops_PCIIH->_hoops_APH.vector.y == _hoops_HCIIH->_hoops_APH.vector.y &&
		  _hoops_PCIIH->_hoops_APH.vector.z == _hoops_HCIIH->_hoops_APH.vector.z)) &&
		(!BIT (_hoops_HCIIH->_hoops_APH.mask, _hoops_PHIRP) ||
		 _hoops_PCIIH->_hoops_APH._hoops_IIIRP == _hoops_HCIIH->_hoops_APH._hoops_IIIRP)  &&
		(!BIT (_hoops_HCIIH->mask, _hoops_APIRP) ||
		 _hoops_PCIIH->_hoops_RRCRP == _hoops_HCIIH->_hoops_RRCRP)) {

		int i;

		for (i=0; i< _hoops_ISIRP; i++) {
			if (BIT (_hoops_PCIIH->_hoops_CSIRP, 1<<i)) {
				if (_hoops_PCIIH->_hoops_SSIRP[i] != _hoops_HCIIH->_hoops_SSIRP[i])
					break;
			}
		}

		if (i == _hoops_ISIRP)
			return null;
	}

	if (_hoops_PCIIH != null) {
		if (!BIT (_hoops_HCIIH->_hoops_APH.mask, _hoops_SPIRP)) {
			_hoops_HCIIH->_hoops_APH._hoops_ACIRP = _hoops_PCIIH->_hoops_APH._hoops_ACIRP;
			_hoops_HCIIH->_hoops_APH._hoops_PCIRP = _hoops_PCIIH->_hoops_APH._hoops_PCIRP;
		}
		if (!BIT (_hoops_HCIIH->_hoops_APH.mask, Heur_Culling_EXTENT))
			_hoops_HCIIH->_hoops_APH._hoops_GRGC = _hoops_PCIIH->_hoops_APH._hoops_GRGC;
		if (!BIT (_hoops_HCIIH->_hoops_APH.mask, _hoops_RIHS))
			_hoops_HCIIH->_hoops_APH._hoops_GCHS = _hoops_PCIIH->_hoops_APH._hoops_GCHS;
		if (!BIT (_hoops_HCIIH->_hoops_APH.mask, _hoops_AHIRP))
			_hoops_HCIIH->_hoops_APH._hoops_CIIRP = _hoops_PCIIH->_hoops_APH._hoops_CIIRP;
		if (!BIT (_hoops_HCIIH->_hoops_APH.mask, _hoops_RHIRP))
			_hoops_HCIIH->_hoops_APH._hoops_PCHS = _hoops_PCIIH->_hoops_APH._hoops_PCHS;
		if (!BIT (_hoops_HCIIH->_hoops_APH.mask, _hoops_HHIRP))
			_hoops_HCIIH->_hoops_APH._hoops_SHHS = _hoops_PCIIH->_hoops_APH._hoops_SHHS;
		if (!BIT (_hoops_HCIIH->_hoops_APH.mask, _hoops_GHIRP))
			_hoops_HCIIH->_hoops_APH.vector = _hoops_PCIIH->_hoops_APH.vector;
		if (!BIT (_hoops_HCIIH->_hoops_APH.mask, _hoops_PHIRP))
			_hoops_HCIIH->_hoops_APH._hoops_IIIRP = _hoops_PCIIH->_hoops_APH._hoops_IIIRP;
		if (!BIT (_hoops_HCIIH->mask, _hoops_APIRP))
			_hoops_HCIIH->_hoops_RRCRP = _hoops_PCIIH->_hoops_RRCRP;

		_hoops_HCIIH->_hoops_APH.value |= (_hoops_PCIIH->_hoops_APH.value & ~_hoops_HCIIH->_hoops_APH.mask);
		_hoops_HCIIH->_hoops_APH.mask |= _hoops_PCIIH->_hoops_APH.mask;


		if (!BIT (_hoops_HCIIH->mask, _hoops_SICIA))
			_hoops_HCIIH->_hoops_GCCIA = _hoops_PCIIH->_hoops_GCCIA;
		if (!BIT (_hoops_HCIIH->mask, _hoops_SRIRP)) {
			_hoops_HCIIH->_hoops_CCIRP.mask = _hoops_PCIIH->_hoops_CCIRP.mask;
			_hoops_HCIIH->_hoops_CCIRP.value = _hoops_PCIIH->_hoops_CCIRP.value;
			_hoops_HCIIH->_hoops_CCIRP._hoops_SPHPR = _hoops_PCIIH->_hoops_CCIRP._hoops_SPHPR;
			_hoops_HCIIH->_hoops_CCIRP.polyline = _hoops_PCIIH->_hoops_CCIRP.polyline;
		}
		else {
			if (!BIT (_hoops_HCIIH->_hoops_CCIRP.mask, _hoops_HCIRP))
				_hoops_HCIIH->_hoops_CCIRP._hoops_SPHPR = _hoops_PCIIH->_hoops_CCIRP._hoops_SPHPR;
			if (!BIT (_hoops_HCIIH->_hoops_CCIRP.mask, _hoops_ICIRP))
				_hoops_HCIIH->_hoops_CCIRP.polyline = _hoops_PCIIH->_hoops_CCIRP.polyline;

			_hoops_HCIIH->_hoops_CCIRP.value |= (_hoops_PCIIH->_hoops_CCIRP.value &
														 ~_hoops_HCIIH->_hoops_CCIRP.mask);
			_hoops_HCIIH->_hoops_CCIRP.mask |= _hoops_PCIIH->_hoops_CCIRP.mask;
		}
		if (!BIT (_hoops_HCIIH->mask, _hoops_RPIRP))
			_hoops_HCIIH->_hoops_GRCRP = _hoops_PCIIH->_hoops_GRCRP;

		for (int i=0; i< _hoops_ISIRP; i++) {
			if (!BIT (_hoops_HCIIH->_hoops_CSIRP, 1<<i)) {
				_hoops_HCIIH->_hoops_SSIRP[i] = _hoops_PCIIH->_hoops_SSIRP[i];
			}
		}
		_hoops_HCIIH->_hoops_CSIRP |= _hoops_PCIIH->_hoops_CSIRP;


		_hoops_HCIIH->value |= (_hoops_PCIIH->value & ~_hoops_HCIIH->mask);
		_hoops_HCIIH->mask |= _hoops_PCIIH->mask;
	}

	return _hoops_HCIIH;
}


local bool _hoops_ICIIH (
	Option_Value *		option,
	_hoops_GHAIR *		_hoops_APHCR) {
 
	if (option->_hoops_GCACR) {
		_hoops_APHCR->_hoops_APH.mask |= _hoops_IHIRP;
		_hoops_APHCR->_hoops_APH.value &= ~_hoops_IHIRP;
		_hoops_APHCR->value &= ~_hoops_RAIRP;
	}
	else if (option->value.option_list == null) {
		_hoops_APHCR->_hoops_APH.mask |= _hoops_IHIRP;
		_hoops_APHCR->_hoops_APH.value |= _hoops_IHIRP;
		_hoops_APHCR->_hoops_APH._hoops_ACIRP = 50;
		_hoops_APHCR->_hoops_APH._hoops_CIIRP = 20;
		_hoops_APHCR->_hoops_APH._hoops_PCIRP = true;
		_hoops_APHCR->value |= _hoops_RAIRP;
	}
	else {
		Option_Value *		_hoops_CHAGA = option->value.option_list;

		do {
			int						_hoops_PHSAA = _hoops_CHAGA->type->id;

			_hoops_APHCR->_hoops_APH.mask |= _hoops_PHSAA;
			_hoops_APHCR->_hoops_APH.value |= _hoops_PHSAA;

			if (_hoops_CHAGA->_hoops_GCACR) {
				if (_hoops_PHSAA == _hoops_RHIRP)
					_hoops_APHCR->_hoops_APH._hoops_PCHS = _hoops_CHIRP;
				else if (_hoops_PHSAA == _hoops_HHIRP)
					_hoops_APHCR->_hoops_APH._hoops_SHHS = _hoops_HIIRP;
				else
					_hoops_APHCR->_hoops_APH.value &= ~_hoops_PHSAA;
			}
			else switch (_hoops_PHSAA) {
				case _hoops_SPIRP: {
					_hoops_APHCR->_hoops_APH._hoops_ACIRP = 50;
					_hoops_APHCR->_hoops_APH._hoops_PCIRP = true;

					if (_hoops_CHAGA->value.option_list != null) {
						Option_Value *		_hoops_CCIIH = _hoops_CHAGA->value.option_list;

						do {
							if (_hoops_CCIIH->type->id == _hoops_SPIIH)
								_hoops_APHCR->_hoops_APH.value &= ~_hoops_SPIRP;
							else if (_hoops_CCIIH->type->id == _hoops_SIIRP)
								_hoops_APHCR->_hoops_APH._hoops_ACIRP = _hoops_CCIIH->value._hoops_RIARA[0];
							else if (_hoops_CCIIH->type->id == _hoops_GCIRP)
								_hoops_APHCR->_hoops_APH._hoops_PCIRP = !_hoops_CCIIH->_hoops_GCACR;
						} while ((_hoops_CCIIH = _hoops_CCIIH->next) != null);
					}
				}	break;

				case Heur_Culling_EXTENT: {
					if (_hoops_CHAGA->value.option_list == null)
						_hoops_APHCR->_hoops_APH._hoops_GRGC = 1;
					else
						_hoops_APHCR->_hoops_APH._hoops_GRGC = _hoops_CHAGA->value._hoops_RIARA[0];
				}	break;
				case _hoops_RIHS: {
					if (_hoops_CHAGA->value.option_list == null)
						_hoops_APHCR->_hoops_APH._hoops_GCHS = 1;
					else
						_hoops_APHCR->_hoops_APH._hoops_GCHS = _hoops_CHAGA->value._hoops_RIARA[0];
				}	break;
				case _hoops_AHIRP: {
					if (_hoops_CHAGA->value.option_list == null)
						_hoops_APHCR->_hoops_APH._hoops_CIIRP = 20;
					else
						_hoops_APHCR->_hoops_APH._hoops_CIIRP = _hoops_CHAGA->value._hoops_RIARA[0];
				}	break;

				case _hoops_HGIRP: {
					_hoops_APHCR->_hoops_APH.mask |= _hoops_IHIRP;
					_hoops_APHCR->_hoops_APH.value &= ~_hoops_IHIRP;
				}	break;

				case _hoops_IHIRP: {
					_hoops_APHCR->_hoops_APH._hoops_ACIRP = 50;
					_hoops_APHCR->_hoops_APH._hoops_CIIRP = 20;
					_hoops_APHCR->_hoops_APH._hoops_PCIRP = true;					
				}	break;

				case _hoops_RHIRP: {
					Option_Value *		_hoops_CCIIH = _hoops_CHAGA->value.option_list;
					_hoops_APHCR->_hoops_APH._hoops_PCHS = _hoops_CCIIH->type->id;
				}	break;

				case _hoops_HHIRP: {
					Option_Value *		_hoops_CCIIH = _hoops_CHAGA->value.option_list;

					_hoops_APHCR->_hoops_APH._hoops_SHHS = _hoops_RIIRP;
					if (_hoops_CCIIH == null)
						_hoops_APHCR->_hoops_APH._hoops_SHHS = _hoops_HIIRP;
					else do {
						_hoops_APHCR->_hoops_APH._hoops_SHHS |= _hoops_CCIIH->type->id;
					} while ((_hoops_CCIIH = _hoops_CCIIH->next) != null);
				}	break;

				case _hoops_GHIRP: {
					if (_hoops_CHAGA->value.option_list == null) {
						_hoops_APHCR->_hoops_APH.vector.x = 0.0f;
						_hoops_APHCR->_hoops_APH.vector.y = 0.0f;
						_hoops_APHCR->_hoops_APH.vector.z = 0.0f;
					}
					else {
						_hoops_AIGA(_hoops_CHAGA->value._hoops_PIPCR, 3, float, &_hoops_APHCR->_hoops_APH.vector);

						if (!HI_Normalize (&_hoops_APHCR->_hoops_APH.vector)) {
							HE_WARNING (HEC_HEURISTIC, HES_ZERO_LENGTH,
										"Specified segment-level culling vector of zero length.");
							_hoops_APHCR->_hoops_APH.value &= ~_hoops_PHSAA;
						}
					}
				}	break;

				case _hoops_PHIRP: {
					if (_hoops_CHAGA->value.option_list == null)
						_hoops_APHCR->_hoops_APH._hoops_IIIRP = 0.0f;
					else {
						_hoops_APHCR->_hoops_APH._hoops_IIIRP = Abs(_hoops_CHAGA->value._hoops_PIPCR[0]);
						
						if (_hoops_APHCR->_hoops_APH._hoops_IIIRP >= 180.0f) {
							HE_WARNING (HEC_HEURISTIC, HES_BAD_ANGLE,
										"Specified tolerance for segment-level culling vector "
										"is at least 180 degrees.");
							_hoops_APHCR->_hoops_APH.value &= ~_hoops_PHSAA;
						}
						else if (_hoops_APHCR->_hoops_APH._hoops_IIIRP >= 90.0f) {
							HE_WARNING (HEC_HEURISTIC, HES_BAD_ANGLE,
										"Specified tolerance for segment-level culling vector "
										"is at least 90 degrees.");
						}
					}
				}	break;

				case Heur_Culling_VIEW_FRUSTUM: 
				default: {
				}	break;
			}
		} while ((_hoops_CHAGA = _hoops_CHAGA->next) != null);
	}

	return true;
}






GLOBAL_FUNCTION bool HI_Process_Heuristic_Options (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			list, 
	_hoops_GHAIR alter *		_hoops_APHCR,
	bool					_hoops_SCIIH) {
	Option_Value *			option_list;
	Option_Value *			option;

	_hoops_HIACR (_hoops_PAPPP, _hoops_RCIIH);

	if (!HI_Parse_Options (_hoops_RIGC, list, _hoops_CIACR (_hoops_PAPPP), &option_list, _hoops_SIACR))
		return false;

	ZERO_STRUCT (_hoops_APHCR, _hoops_GHAIR);
	_hoops_APHCR->type = HK_HEURISTICS;
	_hoops_APHCR->_hoops_SHSHA = -1.0f;

	if ((option = option_list) != null) do {
		_hoops_CGSP		mask = option->type->id;

		if (mask == _hoops_GCIIH) {
			;
		} else if (mask < 0) {			// _hoops_GRH _hoops_GHSHA _hoops_AAP
			if (mask == -_hoops_SARPH) {	// _hoops_GHSHA _hoops_IPCAH
				if (option->_hoops_GCACR)
					_hoops_APHCR->_hoops_SHSHA = 999.0f;
				else {
					_hoops_APHCR->_hoops_SHSHA = option->value._hoops_PIPCR[0];

					if (_hoops_APHCR->_hoops_SHSHA < 0.0f) {
						HE_ERROR (HEC_DRIVER, HES_BAD_SELECTION_PROXIMITY, "'Selection proximity' may not be negative");
						HI_Free_Option_List (_hoops_RIGC, option_list);
						return false;
					}
				}
			}
			else							// _hoops_GHSHA _hoops_ACPH, _hoops_CGHI _hoops_AGGRA
				_hoops_APHCR->_hoops_PPSHA = -mask;
		}
		else if (mask == (_hoops_GPSA | _hoops_SASA)) {
			_hoops_APHCR->mask |= _hoops_GPSA | _hoops_SASA;
			_hoops_APHCR->value &= ~(_hoops_GPSA | _hoops_SASA);

			if (!option->_hoops_GCACR)
				_hoops_APHCR->value |= option->value.option_list[0].type->id;
		}
		else if (mask == _hoops_HPIRP) {
			_hoops_APHCR->mask  |= _hoops_HPIRP;

			if (!option->_hoops_GCACR) {
				if (option->_hoops_AIPCR != 0)
					_hoops_APHCR->value |= option->value.option_list[0].type->id;
				else 
					_hoops_APHCR->value |= _hoops_HPIRP;
			}
			else
				_hoops_APHCR->value &= ~_hoops_HPIRP;
		}
		else if (mask == _hoops_RAIRP) {
			_hoops_APHCR->mask |= _hoops_RAIRP;

			_hoops_ICIIH (option, _hoops_APHCR);
		}
		else if (mask == _hoops_RPIRP) {
			_hoops_APHCR->mask  |= _hoops_RPIRP;
			_hoops_APHCR->_hoops_GRCRP = option->value.option_list[0].type->id;
		}
		else if (mask == _hoops_PPIRP) {
			_hoops_APHCR->mask  |= _hoops_PPIRP;
			_hoops_APHCR->_hoops_IRCRP = option->value.option_list[0].type->id;
		}
		else {
			_hoops_APHCR->mask |= mask;
			if (option->_hoops_GCACR)
				_hoops_APHCR->value &= ~mask;
			else
				_hoops_APHCR->value |= mask;

			if (mask == _hoops_APIRP) {
				if (option->_hoops_GCACR) _hoops_APHCR->_hoops_RRCRP = 0;
				else {
					_hoops_APHCR->_hoops_RRCRP = option->value._hoops_RIARA[0];
					if (_hoops_APHCR->_hoops_RRCRP < 0) {
						HE_ERROR (HEC_HEURISTIC, HES_INVALID_INPUT,
								  "A 'force defer batch' can't be negative");
						HI_Free_Option_List (_hoops_RIGC, option_list);
						return false;
					}
				}
			}
			else if (mask == _hoops_SICIA) {
				if (option->_hoops_GCACR) _hoops_APHCR->_hoops_GCCIA = _hoops_IICIA;
				else {
					_hoops_APHCR->_hoops_GCCIA = option->value._hoops_RIARA[0];
					if (_hoops_APHCR->_hoops_GCCIA < 0) {
						HE_ERROR (HEC_HEURISTIC, HES_INVALID_INPUT,
								  "A 'related selection limit' can't be negative");
						HI_Free_Option_List (_hoops_RIGC, option_list);
						return false;
					}
				}
			}
			else if (mask == _hoops_SRIRP) {
				if (option->_hoops_GCACR) {
					_hoops_APHCR->_hoops_CCIRP.mask = _hoops_HCIRP|_hoops_ICIRP;
					_hoops_APHCR->_hoops_CCIRP.value = 0;
					_hoops_APHCR->_hoops_CCIRP._hoops_SPHPR = _hoops_IICIA;
					_hoops_APHCR->_hoops_CCIRP.polyline = _hoops_IICIA;
				}
				else if (option->_hoops_SGSAP == _hoops_APRCA) {
					_hoops_APHCR->_hoops_CCIRP.mask = _hoops_HCIRP|_hoops_ICIRP;
					_hoops_APHCR->_hoops_CCIRP.value = _hoops_HCIRP|_hoops_ICIRP;
					_hoops_APHCR->_hoops_CCIRP._hoops_SPHPR = option->value._hoops_RIARA[0];
					_hoops_APHCR->_hoops_CCIRP.polyline = option->value._hoops_RIARA[0];
				}
				else {
					Option_Value *		_hoops_CHAGA = option->value.option_list;

					if (_hoops_CHAGA == null) {
						HE_ERROR (HEC_HEURISTIC, HES_INVALID_INPUT, "No 'internal selection limit' options specified");
						HI_Free_Option_List (_hoops_RIGC, option_list);
						return false;
					}
					else do {
						int					id = _hoops_CHAGA->type->id;

						_hoops_APHCR->_hoops_CCIRP.mask |= id;

						if (_hoops_CHAGA->_hoops_GCACR) {
							_hoops_APHCR->_hoops_CCIRP.value &= ~id;
							if (id == _hoops_HCIRP)
								_hoops_APHCR->_hoops_CCIRP._hoops_SPHPR = _hoops_IICIA;
							else
								_hoops_APHCR->_hoops_CCIRP.polyline = _hoops_IICIA;
						}
						else {
							_hoops_APHCR->_hoops_CCIRP.value |= id;
							if (id == _hoops_HCIRP)
								_hoops_APHCR->_hoops_CCIRP._hoops_SPHPR = _hoops_CHAGA->value._hoops_RIARA[0];
							else
								_hoops_APHCR->_hoops_CCIRP.polyline = _hoops_CHAGA->value._hoops_RIARA[0];
						}
					} while ((_hoops_CHAGA = _hoops_CHAGA->next) != null);
				}
			}
			else if (mask == _hoops_IPIRP) {
				_hoops_APHCR->value &= ~_hoops_IPIRP;	/* _hoops_AHPPR _hoops_RGSR _hoops_ARRS _hoops_HAR _hoops_RPHR _hoops_IH _hoops_RGR */
				if (option->_hoops_GCACR) {}
				else if (option->_hoops_AIPCR > 0)
					_hoops_APHCR->value |= option->value.option_list->type->id;
				else
					_hoops_APHCR->value |= _hoops_HAIRP;
			}
			else if (mask == _hoops_CAIRP) {
				Option_Value *		_hoops_CHAGA = option->value.option_list;

				if (_hoops_CHAGA == null) {
					HE_ERROR (HEC_HEURISTIC, HES_INVALID_INPUT, "No 'ordered weight' options specified");
					HI_Free_Option_List (_hoops_RIGC, option_list);
					return false;
				}
				else do {
					int					id = _hoops_CHAGA->type->id;
					float				value = 0.0f;
					int					_hoops_PHSAA = 1 << id;

					if (!_hoops_CHAGA->_hoops_GCACR) {
						if (_hoops_CHAGA->_hoops_AIPCR == 1)
							value = _hoops_CHAGA->value._hoops_PIPCR[0];
						else
							value = 1.0f;
					}

					if (id == _hoops_ISIRP)
						--_hoops_PHSAA;	/* _hoops_HCR _hoops_SIH _hoops_CAPP */

					_hoops_APHCR->_hoops_CSIRP |= _hoops_PHSAA;
					for (int i=0; i<_hoops_ISIRP; i++) {
						if (BIT (_hoops_PHSAA, 1<<i))
							_hoops_APHCR->_hoops_SSIRP[i] = value;
					}
				} while ((_hoops_CHAGA = _hoops_CHAGA->next) != null);
			}
		}
	} while ((option = option->next) != null);

	HI_Free_Option_List (_hoops_RIGC, option_list);

#define	_hoops_GSIIH	(_hoops_SICIA | _hoops_SRIRP | \
								 _hoops_RPIRP | _hoops_PAIRP | \
								 _hoops_AAIRP | _hoops_GAIRP)

	if (_hoops_SCIIH) {
		if (ANYBIT (_hoops_APHCR->mask, ~_hoops_GSIIH)) {
			HE_WARNING (HEC_SELECTION, HES_INVALID_INPUT, "Non-selection Heuristics not allowed.");
			_hoops_APHCR->mask &= _hoops_GSIIH;
		}
	}
	else if (_hoops_APHCR->_hoops_PPSHA != 0 || _hoops_APHCR->_hoops_SHSHA != -1.0f)
		HE_WARNING (HEC_HEURISTIC, HES_INVALID_INPUT, "Selection actions/proximity not allowed.");

	return true;
}


GLOBAL_FUNCTION bool HI_Set_Heuristics (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_GHAIR *			heuristics) 
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_HEURISTICS, _hoops_ACIIH, heuristics);
}


HC_INTERFACE void HC_CDECL HC_Set_Heuristics (
	char const *	list) 
{
	_hoops_PAPPR context("Set_Heuristics");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Heuristics (%S);\n", list));
	);

	bool			used = false;
	_hoops_GHAIR *	heuristics;
	ZALLOC (heuristics, _hoops_GHAIR);

	if (HI_Process_Heuristic_Options(context, list , heuristics, false)) {

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_PPRPP)) != null) {
			used = HI_Set_Heuristics(context, target, heuristics);
			_hoops_IRRPR();
		}
	}

	if (!used)
		FREE (heuristics, _hoops_GHAIR);
}

GLOBAL_FUNCTION bool HI_Unset_Heuristics (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_GHAIR *			heuristics) 
{
	/* _hoops_RRGRA */
	UNREFERENCED(_hoops_RIGC);
	UNREFERENCED(item);
	UNREFERENCED(heuristics);
	return false;
}

HC_INTERFACE void HC_CDECL HC_UnSet_Heuristics (void) 
{
	_hoops_PAPPR context("UnSet_Heuristics");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Heuristics ();\n");
	);

	_hoops_HPAH *	target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PPRPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute(context, target, HK_HEURISTICS);
		_hoops_IRRPR();
	}

}




#ifdef DISABLE_SHOW
#	ifdef DISABLE_METAFILE
#		define _hoops_RSIIH
#	endif
#endif


#ifndef _hoops_RSIIH

local const struct _hoops_ASIIH {
	_hoops_CGSP	mask;
	_hoops_SRHSR			name;
}		_hoops_PSIIH[] = {
			{_hoops_PICAR,					_hoops_GRRCR ("clipping")},
			{_hoops_IGIRP,			_hoops_GRRCR ("transformations")},
			{_hoops_CGIRP,	_hoops_GRRCR ("intersecting polygons")},
			{_hoops_GRIRP,		_hoops_GRRCR ("polygon crossings")},
			{_hoops_SGIRP,			_hoops_GRRCR ("backplane culls")},
			{_hoops_CGCS,			_hoops_GRRCR ("concave polygons")},
			{_hoops_RSA,	_hoops_GRRCR ("polygon handedness")},
			{_hoops_RRIRP,		_hoops_GRRCR ("incremental updates")},
			{_hoops_IRI,			_hoops_GRRCR ("hidden surfaces")},
			{_hoops_PRIRP,			_hoops_GRRCR ("partial erase")},
			{_hoops_HPIRP,			_hoops_GRRCR ("quick moves")},
			{_hoops_SICIA,	_hoops_GRRCR ("related selection limit")},
			{_hoops_SRIRP,	_hoops_GRRCR ("internal selection limit")},
			{_hoops_GAIRP,		_hoops_GRRCR ("selection sorting")},
			{_hoops_AAIRP,			_hoops_GRRCR ("visual selection")},
			{_hoops_CCIAA,			_hoops_GRRCR ("exclude bounding")},
			{_hoops_PAIRP,			_hoops_GRRCR ("detail selection")},
			{_hoops_IGIRP,			_hoops_GRRCR ("transformation")},
			{_hoops_CGIRP,	_hoops_GRRCR ("intersecting polygon")},
			{_hoops_GRIRP,		_hoops_GRRCR ("polygon crossing")},
			{_hoops_SGIRP,			_hoops_GRRCR ("backplane cull")},
			{_hoops_CGCS,			_hoops_GRRCR ("concave polygon")},
			{_hoops_RRIRP,		_hoops_GRRCR ("incremental update")},
			{_hoops_HPIRP,			_hoops_GRRCR ("quick move")},

			{_hoops_RAIRP,					_hoops_GRRCR ("culling")},
			{_hoops_RAIRP,					_hoops_GRRCR ("cull")},
			{_hoops_RAIRP,					_hoops_GRRCR ("culls")},

			{_hoops_IPIRP,			_hoops_GRRCR ("ordered drawing")},
			{_hoops_CAIRP,			_hoops_GRRCR ("ordered weight")},
			{_hoops_CAIRP,			_hoops_GRRCR ("ordered weights")},

			{_hoops_GPIRP,				_hoops_GRRCR ("static model")},
			{_hoops_GPIRP,				_hoops_GRRCR ("static")},

			{_hoops_RPIRP,			_hoops_GRRCR ("selection level")},

			{_hoops_APIRP,		_hoops_GRRCR ("force defer batch")},
			{_hoops_PPIRP,				_hoops_GRRCR ("model type")},
			{false, _hoops_PCGSA}};

local char const *_hoops_HSIIH[] = {
	"world volume",
	"screen extent",
	"distance",	
	"divergence",	
	"density",		
	"priority",	
};

#endif

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

local char *_hoops_SSIIH (
	_hoops_GHAIR const *	heuristics,
	Option_Value const *	option,
	char *					_hoops_ASAPR,
	char const *			_hoops_PSAPR) {
	_hoops_CGSP		mask;

	if (option != null)
		mask = option->type->id;
	else
		mask = ~0U;

	if (option == null && heuristics->_hoops_APH.mask == 0) {
		/* _hoops_RPAPR */
		return _hoops_ASAPR;
	}

	if (option == null && (mask & heuristics->_hoops_APH.mask) == _hoops_IHIRP) {
		if (!ANYBIT (heuristics->_hoops_APH.value, _hoops_IHIRP)) {
			_hoops_ASAPR = HI_Copy_Chars ("off", _hoops_ASAPR);		return _hoops_ASAPR;
		}
		else if (ALLBITS (heuristics->_hoops_APH.value, _hoops_IHIRP) &&
				 heuristics->_hoops_APH._hoops_ACIRP == 0 &&
				 heuristics->_hoops_APH._hoops_GRGC == 1) {
				 /* _hoops_SIGP: _hoops_GGCR _hoops_HSSHH _hoops_IH _hoops_IAPRR _hoops_AAGA? */
			_hoops_ASAPR = HI_Copy_Chars ("on", _hoops_ASAPR);		return _hoops_ASAPR;
		}

		/* _hoops_SHIR: _hoops_GRHP _hoops_CPIC */
	}

	/* _hoops_IGGA _hoops_RGSR(_hoops_GRI) */

	if (BIT (mask & heuristics->_hoops_APH.mask, Heur_Culling_VIEW_FRUSTUM))
		_hoops_ISIIH ("view frustum", BIT (heuristics->_hoops_APH.value, Heur_Culling_VIEW_FRUSTUM), option, _hoops_ASAPR, _hoops_PSAPR);

	if (BIT (mask & heuristics->_hoops_APH.mask, _hoops_GHIRP)) {
		if (BIT (heuristics->_hoops_APH.value, _hoops_GHIRP)) {
			if (option == null)
				_hoops_ASAPR = HI_Copy_Chars ("vector=(", _hoops_ASAPR);			

			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f,", &heuristics->_hoops_APH.vector.x);
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f,", &heuristics->_hoops_APH.vector.y);
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f",  &heuristics->_hoops_APH.vector.z);

			if (option == null)
				_hoops_ASAPR = HI_Copy_Chars(")", _hoops_ASAPR);
			_hoops_ASAPR = HI_Copy_Chars(",", _hoops_ASAPR);
		}
		else {
			if (option == null)
				_hoops_ASAPR = HI_Copy_Chars("no vector,", _hoops_ASAPR);
			else
				_hoops_ASAPR = HI_Copy_Chars("off,", _hoops_ASAPR);
		}
	}
	if (BIT (mask & heuristics->_hoops_APH.mask, _hoops_PHIRP)) {
		if (BIT (heuristics->_hoops_APH.value, _hoops_PHIRP)) {
			if (option == null)
				_hoops_ASAPR = HI_Copy_Chars("vector tolerance=", _hoops_ASAPR);
			
			/* _hoops_SR _hoops_CIGAA _hoops_RH _hoops_RRCIR _hoops_GGR _hoops_RH _hoops_AASA _hoops_CAPP _hoops_RIIA _hoops_IIGR _hoops_HAGC _hoops_PCCP _hoops_GSHRH _hoops_AASA _hoops_IS _hoops_GGCIH */
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f,", &heuristics->_hoops_APH._hoops_IIIRP);
		}
		else {
			if (option == null)
				_hoops_ASAPR = HI_Copy_Chars("no vector tolerance,", _hoops_ASAPR);
			else
				_hoops_ASAPR = HI_Copy_Chars("off,", _hoops_ASAPR);
		}
	}
	if (BIT (mask & heuristics->_hoops_APH.mask, Heur_Culling_EXTENT)) {
		if (BIT (heuristics->_hoops_APH.value, Heur_Culling_EXTENT)) {
			if (option == null)
				_hoops_ASAPR = HI_Copy_Chars ("maximum extent=", _hoops_ASAPR);

			if (heuristics->_hoops_APH._hoops_GRGC > 1)
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%d,",
								 (void *)&heuristics->_hoops_APH._hoops_GRGC);
			else if (option != null)
				_hoops_ASAPR = HI_Copy_Chars ("on,", _hoops_ASAPR);
			else
				_hoops_ASAPR[-1] = ',';
		}
		else {
			if (option == null)
				_hoops_ASAPR = HI_Copy_Chars ("no maximum extent,", _hoops_ASAPR);
			else
				_hoops_ASAPR = HI_Copy_Chars ("off,", _hoops_ASAPR);
		}
	}
	if (BIT (mask & heuristics->_hoops_APH.mask, _hoops_RIHS)) {
		if (BIT (heuristics->_hoops_APH.value, _hoops_RIHS)) {
			if (option == null)
				_hoops_ASAPR = HI_Copy_Chars ("hard extent=", _hoops_ASAPR);

			if (heuristics->_hoops_APH._hoops_GCHS > 1)
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%d,",
								 (void *)&heuristics->_hoops_APH._hoops_GCHS);
			else if (option != null)
				_hoops_ASAPR = HI_Copy_Chars ("on,", _hoops_ASAPR);
			else if (_hoops_ASAPR != null)
				_hoops_ASAPR[-1] = ',';
		}
		else {
			if (option == null)
				_hoops_ASAPR = HI_Copy_Chars ("no hard extent,", _hoops_ASAPR);
			else
				_hoops_ASAPR = HI_Copy_Chars ("off,", _hoops_ASAPR);
		}
	}
	if (BIT (mask & heuristics->_hoops_APH.mask, _hoops_RHIRP)) {
		if (BIT (heuristics->_hoops_APH.value, _hoops_RHIRP)) {
			if (option == null)
				_hoops_ASAPR = HI_Copy_Chars ("maximum extent mode=", _hoops_ASAPR);

			if (heuristics->_hoops_APH._hoops_PCHS == _hoops_GIIRP)
				_hoops_ASAPR = HI_Copy_Chars("bounding,", _hoops_ASAPR);
			else if (heuristics->_hoops_APH._hoops_PCHS == _hoops_SHIRP)
				_hoops_ASAPR = HI_Copy_Chars("dot,", _hoops_ASAPR);
			else if (heuristics->_hoops_APH._hoops_PCHS == Heur_MAX_EXTENT_MODE_DEFER)
				_hoops_ASAPR = HI_Copy_Chars("defer,", _hoops_ASAPR);
			else if (heuristics->_hoops_APH._hoops_PCHS == _hoops_CHIRP)
				_hoops_ASAPR = HI_Copy_Chars("none,", _hoops_ASAPR);
			else if (_hoops_ASAPR != null)
				_hoops_ASAPR[-1] = ',';
		}
		else {
			if (option == null)
				_hoops_ASAPR = HI_Copy_Chars ("no maximum extent mode,", _hoops_ASAPR);
			else
				_hoops_ASAPR = HI_Copy_Chars ("off,", _hoops_ASAPR);
		}
	}
	if (BIT (mask & heuristics->_hoops_APH.mask, _hoops_HHIRP)) {
		if (BIT (heuristics->_hoops_APH.value, _hoops_HHIRP)) {
			if (option == null)
				_hoops_ASAPR = HI_Copy_Chars ("maximum extent level=", _hoops_ASAPR);

			if (heuristics->_hoops_APH._hoops_SHHS == _hoops_HIIRP)
				_hoops_ASAPR = HI_Copy_Chars("default,", _hoops_ASAPR);
			else if (heuristics->_hoops_APH._hoops_SHHS != _hoops_RIIRP) {
				if (_hoops_RIII (heuristics->_hoops_APH._hoops_SHHS) != heuristics->_hoops_APH._hoops_SHHS)
					_hoops_ASAPR = HI_Copy_Chars ("(", _hoops_ASAPR);

				if (BIT (heuristics->_hoops_APH._hoops_SHHS, _hoops_AIIRP))
					_hoops_ASAPR = HI_Copy_Chars("segment,", _hoops_ASAPR);
				if (BIT (heuristics->_hoops_APH._hoops_SHHS, _hoops_PIIRP))
					_hoops_ASAPR = HI_Copy_Chars("geometry,", _hoops_ASAPR);
				if (BIT (heuristics->_hoops_APH._hoops_SHHS, _hoops_GIHS))
					_hoops_ASAPR = HI_Copy_Chars("primitive,", _hoops_ASAPR);

				if (_hoops_ASAPR != null)
					--_hoops_ASAPR;
				if (_hoops_RIII (heuristics->_hoops_APH._hoops_SHHS) != heuristics->_hoops_APH._hoops_SHHS)
					_hoops_ASAPR = HI_Copy_Chars (")", _hoops_ASAPR);
				_hoops_ASAPR = HI_Copy_Chars (",", _hoops_ASAPR);
			}
			else if (_hoops_ASAPR != null)
				_hoops_ASAPR[-1] = ',';
		}
		else {
			if (option == null)
				_hoops_ASAPR = HI_Copy_Chars ("no maximum extent level,", _hoops_ASAPR);
			else
				_hoops_ASAPR = HI_Copy_Chars ("off,", _hoops_ASAPR);
		}
	}
	if (BIT (mask & heuristics->_hoops_APH.mask, _hoops_SPIRP)) {
		if (BIT (heuristics->_hoops_APH.value, _hoops_SPIRP)) {
			bool		_hoops_RGCIH=false, _hoops_HISCA=false;

#ifdef _hoops_AGCIH
			_hoops_RGCIH = (heuristics->_hoops_APH._hoops_ACIRP != 0) || heuristics->_hoops_APH._hoops_PCIRP;
			_hoops_HISCA = (heuristics->_hoops_APH._hoops_ACIRP != 0) && heuristics->_hoops_APH._hoops_PCIRP;
#else
			_hoops_RGCIH = (heuristics->_hoops_APH._hoops_ACIRP != 0);
#endif


			if (option == null) {
				_hoops_ASAPR = HI_Copy_Chars ("obscuration", _hoops_ASAPR);
				if (_hoops_RGCIH) {
					_hoops_ASAPR = HI_Copy_Chars ("=", _hoops_ASAPR);
					if (_hoops_HISCA)
						_hoops_ASAPR = HI_Copy_Chars ("(", _hoops_ASAPR);
				}
			}

			if (heuristics->_hoops_APH._hoops_ACIRP != 0 ||
				option != null && option->value.option_list != null &&
				option->value.option_list->type->id == _hoops_SIIRP) {
				if (option == null || option->value.option_list == null)
					_hoops_ASAPR = HI_Copy_Chars ("pixel threshold=", _hoops_ASAPR);

				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%d,", (void *)&heuristics->_hoops_APH._hoops_ACIRP);
			}
			else if (option != null)
				_hoops_ASAPR = HI_Copy_Chars ("on,", _hoops_ASAPR);

#ifdef _hoops_AGCIH
			if (option != null && option->value.option_list != null &&
				option->value.option_list->type->id == _hoops_GCIRP) {
				if (heuristics->_hoops_APH._hoops_PCIRP)
					_hoops_ASAPR = HI_Copy_Chars ("on,", _hoops_ASAPR);
				else
					_hoops_ASAPR = HI_Copy_Chars ("off", _hoops_ASAPR);
			}
			else if (option == null || option->value.option_list == null)
				if (heuristics->_hoops_APH._hoops_PCIRP)
					_hoops_ASAPR = HI_Copy_Chars ("use octree,", _hoops_ASAPR);
#endif
			--_hoops_ASAPR;

			if (option == null)
				if (_hoops_HISCA)
					_hoops_ASAPR = HI_Copy_Chars (")", _hoops_ASAPR);
			_hoops_ASAPR = HI_Copy_Chars (",", _hoops_ASAPR);
		}
		else {
			if (option == null)
				_hoops_ASAPR = HI_Copy_Chars ("no obscuration,", _hoops_ASAPR);
			else
				_hoops_ASAPR = HI_Copy_Chars ("off,", _hoops_ASAPR);
		}
	}

	--_hoops_ASAPR;  /* (_hoops_HASIR _hoops_GRCIR _hoops_RRCIR) */

	return _hoops_ASAPR;
}

local char const * _hoops_PGCIH[] = {"entity", "segment", "segment tree"};


local char const * _hoops_IRCRP[] = {"default", "lmv"};

local bool _hoops_HGCIH(_hoops_GHAIR const * heuristics)
{
	if (!ALLBITS (heuristics->_hoops_APH.value, _hoops_IHIRP))
		return false;
	else if (heuristics->_hoops_APH._hoops_ACIRP == 50 &&
	  heuristics->_hoops_APH._hoops_PCHS == 0 &&
	  heuristics->_hoops_APH._hoops_SHHS == 0 &&
	  heuristics->_hoops_APH._hoops_GRGC == 0)
		return true;
	else
		return false;
}


GLOBAL_FUNCTION void HI_Show_Heuristics (
	_hoops_GHAIR const *			heuristics,
	char *						list,
	int							_hoops_GGCIR) {
#ifndef _hoops_RSIIH
	char							buf[1000];
	char							*p = buf, *pe = p + _hoops_GGAPR(buf);
	const _hoops_ASIIH			*_hoops_IGCIH = _hoops_PSIIH;
	_hoops_CGSP				mask = heuristics->mask;

	if (mask != false) {
		do if (ANYBIT (mask, _hoops_IGCIH->mask)) {
			mask &= ~_hoops_IGCIH->mask;
			if (_hoops_IGCIH->mask == _hoops_RSA &&
				ANYBIT (heuristics->value, _hoops_RSA)) {
				if (BIT (heuristics->value, _hoops_GPSA))
					p = HI_Copy_Chars ("polygon handedness=left,", p);
				else
					p = HI_Copy_Chars ("polygon handedness=right,", p);
			}
			else if (_hoops_IGCIH->mask == _hoops_HPIRP &&
				     !ALLBITS (heuristics->value, _hoops_HPIRP)&&
					 ANYBIT (heuristics->value, _hoops_HPIRP)) {
				/* _hoops_RH _hoops_CSHHR _hoops_SIGH _hoops_IRS _hoops_CIHCA _hoops_AHCA _hoops_PGAP _hoops_SPAHR _hoops_IS _hoops_SGH */
				if (BIT (heuristics->value, _hoops_IRIRP))
					p = HI_Copy_Chars ("quick moves=spriting,", p);
				else if (BIT (heuristics->value, _hoops_HRIRP))
					p = HI_Copy_Chars ("quick moves=overlay,", p);
				else if (BIT (heuristics->value, _hoops_CRIRP))
					p = HI_Copy_Chars ("quick moves=xor,", p);
			}
			else if (_hoops_IGCIH->mask == _hoops_RAIRP &&
					 (ANYBIT (heuristics->_hoops_APH.value, _hoops_IHIRP) ||
					 !ALLBITS (heuristics->_hoops_APH.mask, _hoops_IHIRP))  &&
					 !_hoops_HGCIH(heuristics)) { 
				_hoops_CGSP		_hoops_CGCIH = heuristics->_hoops_APH.mask & _hoops_IHIRP;
				bool				_hoops_HISCA = _hoops_RIII(_hoops_CGCIH) != _hoops_CGCIH;

				p = HI_Copy_Chars ("culling=", p);
				if (_hoops_HISCA) *p++ = '(';
				p = _hoops_SSIIH (heuristics, null, p, pe);
				if (_hoops_HISCA) *p++ = ')';
				*p++ = ',';
			}
			else if (_hoops_IGCIH->mask == _hoops_PPIRP) {
				p = HI_Sprintf1 (p, pe, "model type=%s,",
								 (void *)_hoops_IRCRP[heuristics->_hoops_IRCRP]);
			}
			else if (_hoops_IGCIH->mask == _hoops_RPIRP &&
					 BIT (heuristics->mask, _hoops_RPIRP)) {
				p = HI_Sprintf1 (p, pe, "selection level=%s,",
								 (void *)_hoops_PGCIH[heuristics->_hoops_GRCRP]);
			}
			else if (_hoops_IGCIH->mask == _hoops_SICIA &&
					 BIT (heuristics->value, _hoops_SICIA)) {
				p = HI_Sprintf1 (p, pe, "related selection limit=%d,",
								 (void *)&heuristics->_hoops_GCCIA);
			}
			else if (_hoops_IGCIH->mask == _hoops_SRIRP &&
					 BIT (heuristics->value, _hoops_SRIRP)) {
				if (ALLBITS (heuristics->_hoops_CCIRP.value,
							 _hoops_HCIRP|_hoops_ICIRP) &&
					heuristics->_hoops_CCIRP._hoops_SPHPR == heuristics->_hoops_CCIRP.polyline)
					p = HI_Sprintf1 (p, pe, "internal selection limit=%d,",
									 (void *)&heuristics->_hoops_CCIRP._hoops_SPHPR);
				else {
					int				_hoops_PHSAA = heuristics->_hoops_CCIRP.mask;
					bool		_hoops_HISCA = _hoops_RIII(_hoops_PHSAA) != _hoops_PHSAA;

					p = HI_Copy_Chars ("internal selection limit=", p);
					if (_hoops_HISCA) *p++ = '(';
					if (BIT (_hoops_PHSAA, _hoops_HCIRP)) {
						if (BIT (heuristics->_hoops_CCIRP.value, _hoops_HCIRP))
							p = HI_Sprintf1 (p, pe, "shell=%d,",
											 (void *)&heuristics->_hoops_CCIRP._hoops_SPHPR);
						else
							p = HI_Copy_Chars ("no shell", p);
					}
					if (BIT (_hoops_PHSAA, _hoops_ICIRP)) {
						if (BIT (heuristics->_hoops_CCIRP.value, _hoops_ICIRP))
							p = HI_Sprintf1 (p, pe, "polyline=%d,",
											 (void *)&heuristics->_hoops_CCIRP.polyline);
						else
							p = HI_Copy_Chars ("no polyline", p);
					}
					p--;	/* _hoops_HASIR _hoops_CGHI ',' */
					if (_hoops_HISCA) *p++ = ')';
					*p++ = ',';
				}
			}
			else if (_hoops_IGCIH->mask == _hoops_IPIRP) {
				if (BIT (heuristics->value, _hoops_IAIRP))
					p = HI_Copy_Chars ("ordered drawing=unit,", p);
				else if (BIT(heuristics->value, _hoops_HAIRP))
					p = HI_Copy_Chars ("ordered drawing,", p);
				else
					p = HI_Copy_Chars ("no ordered drawing,", p);
			}
			else if (_hoops_IGCIH->mask == _hoops_CAIRP) {
				int				_hoops_PHSAA = heuristics->_hoops_CSIRP;
				bool		_hoops_HISCA = _hoops_RIII(_hoops_PHSAA) != _hoops_PHSAA;
				int				i;

				if (heuristics->_hoops_CSIRP == (1<<_hoops_ISIRP)-1) {
					for (i=1; i<_hoops_ISIRP; i++) {
						if (heuristics->_hoops_SSIRP[i] != heuristics->_hoops_SSIRP[0])
							break;
					}
					if (i == _hoops_ISIRP) {
						p = HI_Sprintf1 (p, pe, "ordered weights=everything=%f,",
										 (void *)&heuristics->_hoops_SSIRP[0]);
						continue;
					}
				}
				p = HI_Copy_Chars ("ordered weights=", p);
				if (_hoops_HISCA) *p++ = '(';
				for (i=0; i<_hoops_ISIRP; i++) {
					if (BIT (_hoops_PHSAA, 1<<i)) {
						p = HI_Copy_Chars (_hoops_HSIIH[i], p);
						p = HI_Sprintf1 (p, pe, "=%f,",
											(void *)&heuristics->_hoops_SSIRP[i]);
					}
				}
				p--;	/* _hoops_HASIR _hoops_CGHI ',' */
				if (_hoops_HISCA) *p++ = ')';
				*p++ = ',';
			}
			else if (_hoops_IGCIH->mask == _hoops_APIRP &&
					 BIT (heuristics->mask, _hoops_APIRP)) {
				p = HI_Sprintf1 (p, pe, "force defer batch=%d,", 
											(void *)&heuristics->_hoops_RRCRP);
				if (heuristics->_hoops_ARCRP != 0.0) 
					p = HI_Sprintf1 (p, pe, "force defer bias=%f,", 
											(void *)&heuristics->_hoops_ARCRP);
			}
			else {
				if (!ANYBIT (heuristics->value, _hoops_IGCIH->mask)) {
					*p++ = 'n';
					*p++ = 'o';
					*p++ = ' ';
				}

				p = HI_Copy_Chars (_hoops_IGCIH->name.text, p);
				*p++ = ',';
			}
		}
		_hoops_RGGA ((++_hoops_IGCIH)->mask == false);
		--p;
	}

	HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(p - buf));
#endif
}


#ifndef DISABLE_SHOW

local void _hoops_SGCIH (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GHAIR *			heuristics,
	char const *			_hoops_PSGIH,
	char *					list,
	int						_hoops_GGCIR) 
{
	Option_Value *			option;
	_hoops_CGSP		mask;

	if (!HI_Parse_Options (_hoops_RIGC, _hoops_PSGIH, _hoops_CIACR (_hoops_PAPPP),
		&option, _hoops_CGPCR|_hoops_PAPCA)) return;

	if (option == null) 
		return;

	mask = option->type->id;

	if (!ANYBIT (mask, heuristics->mask)) {
		HE_ERROR (HEC_HEURISTIC, HES_NO_LOCAL_SETTING, 
			Sprintf_SP (null, "'%s' has no setting in '%p'", _hoops_PSGIH, heuristics->owner));
		return;
	}

	if (mask == _hoops_RSA &&
		ANYBIT (heuristics->value, _hoops_RSA)) {
		if (BIT (heuristics->value, _hoops_GPSA))
			HI_Return_Chars (list, _hoops_GGCIR, "left", 4);
		else
			HI_Return_Chars (list, _hoops_GGCIR, "right", 5);
	}
	else if (mask == _hoops_HPIRP &&
			 BIT (heuristics->value, _hoops_IRIRP)) {
		HI_Return_Chars (list, _hoops_GGCIR, "spriting", 8);
	}
	else if (mask == _hoops_RAIRP) {
		char			buf[200], *p = buf, *pe = p+_hoops_GGAPR(buf);

		p = _hoops_SSIIH (heuristics, option->value.option_list, p, pe);

		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(p - buf));
	}
	else if (mask == _hoops_RPIRP) {
		char			buf[200], *p = buf, *pe = p+_hoops_GGAPR(buf);

		p = HI_Sprintf1 (p, pe, "%s", (void *)_hoops_PGCIH[heuristics->_hoops_GRCRP]);

		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(p - buf));
	}
	else if (mask == _hoops_PPIRP) {
		char			buf[200], *p = buf, *pe = p+_hoops_GGAPR(buf);

		p = HI_Sprintf1 (p, pe, "%s", (void *)_hoops_IRCRP[heuristics->_hoops_IRCRP]);

		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(p - buf));
	}
	else if (mask == _hoops_SICIA &&
			 BIT (heuristics->value, _hoops_SICIA)) {
		char			buf[20], *p;

		p = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf)-1, "%d", (void *)&heuristics->_hoops_GCCIA);

		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(p - buf));
	}
	else if (mask == _hoops_SRIRP &&
			 BIT (heuristics->value, _hoops_SRIRP)) {
		char			buf[64], *p = buf, *pe = p + _hoops_GGAPR(buf)-1;

		if (ALLBITS (heuristics->_hoops_CCIRP.value,
					 _hoops_HCIRP|_hoops_ICIRP) &&
			heuristics->_hoops_CCIRP._hoops_SPHPR == heuristics->_hoops_CCIRP.polyline)
			p = HI_Sprintf1 (p, pe, "%d",(void *)&heuristics->_hoops_CCIRP._hoops_SPHPR);
		else {
			int				_hoops_PHSAA = heuristics->_hoops_CCIRP.mask;

			if (BIT (_hoops_PHSAA, _hoops_HCIRP)) {
				if (BIT (heuristics->_hoops_CCIRP.value, _hoops_HCIRP))
					p = HI_Sprintf1 (p, pe, "shell=%d,", (void *)&heuristics->_hoops_CCIRP._hoops_SPHPR);
				else
					p = HI_Copy_Chars ("no shell,", p);
			}
			if (BIT (_hoops_PHSAA, _hoops_ICIRP)) {
				if (BIT (heuristics->_hoops_CCIRP.value, _hoops_ICIRP))
					p = HI_Sprintf1 (p, pe, "polyline=%d,", (void *)&heuristics->_hoops_CCIRP.polyline);
				else
					p = HI_Copy_Chars ("no polyline,", p);
			}
			p--;	/* _hoops_HASIR _hoops_CGHI ',' */
		}

		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(p - buf));
	}
	else if (mask == _hoops_HAIRP) {
		if (BIT (heuristics->value, _hoops_IAIRP))
			HI_Return_Chars (list, _hoops_GGCIR, "unit", 4);
		else if (BIT(heuristics->value, _hoops_HAIRP))
			HI_Return_Chars (list, _hoops_GGCIR, "on", 2);
		else
			HI_Return_Chars (list, _hoops_GGCIR, "off", 3);
	}
	else if (mask == _hoops_CAIRP &&
			 BIT (heuristics->value, _hoops_CAIRP)) {
		char			buf[256], *p;
		int				_hoops_PHSAA = heuristics->_hoops_CSIRP;
		bool		done = false;
		int				i;

		if (heuristics->_hoops_CSIRP == (1<<_hoops_ISIRP)-1) {
			for (i=1; i<_hoops_ISIRP; i++) {
				if (heuristics->_hoops_SSIRP[i] != heuristics->_hoops_SSIRP[0])
					break;
			}
			if (i == _hoops_ISIRP) {
				p = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf)-1, "everything=%f,",
								 (void *)&heuristics->_hoops_SSIRP[0]);
				HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(p - buf));
				done = true;
			}
		}
		if (!done) {
			p = buf;
			for (i=1; i<_hoops_ISIRP; i++) {
				if (BIT (_hoops_PHSAA, 1<<i)) {
					p = HI_Copy_Chars (_hoops_HSIIH[i], p);
					p = HI_Sprintf1 (p, buf+_hoops_GGAPR(buf)-1, "=%f,",
									 (void *)&heuristics->_hoops_SSIRP[0]);
				}
			}
			HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(p - buf));
		}
	}
	else if (mask == _hoops_APIRP &&
			 BIT (heuristics->value, _hoops_APIRP)) {
		char			buf[20], *p;

		p = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf)-1, "%d",
						 (void *)&heuristics->_hoops_RRCRP);

		HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(p - buf));
	}
	else {
		if (!ANYBIT (mask, heuristics->value))
			HI_Return_Chars (list, _hoops_GGCIR, "off", 3);
		else
			HI_Return_Chars (list, _hoops_GGCIR, "on", 2);
	}

	HI_Free_Option_List (_hoops_RIGC, option);
}
#endif



HC_INTERFACE void HC_CDECL HC_Show_Heuristics (
	char *			list) 
{
	_hoops_PAPPR context("Show_Heuristics");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Heuristics () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_RSRPP)) != null) {

		_hoops_GHAIR *	heuristics;
		if ((heuristics = (_hoops_GHAIR *)HI_Find_Attribute (context, target, HK_HEURISTICS)) != null) {

			HI_Show_Heuristics (heuristics, list, -1);
			_hoops_HPRH (heuristics);
		}
		_hoops_IRRPR();
	}
#endif
}




#ifndef _hoops_GRCIH


HC_INTERFACE void HC_CDECL HC_PShow_Net_Heuristics (
	int					count,
	Key const *			keys,
	char *				list) 
{
	_hoops_PAPPR context("PShow_Net_Heuristics");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Heuristics () */\n");
	);

	_hoops_GHAIR *	heuristics;
	if ((heuristics = (_hoops_GHAIR *) HI_Find_Attribute_And_Lock(context, _hoops_RSRPP, _hoops_HRPCR, count, keys)) != null) {
		HI_Show_Heuristics (heuristics, list, -1);
		_hoops_HPRH (heuristics);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(list, -1, "", 0);

#endif
}
#endif



HC_INTERFACE void HC_CDECL HC_Show_One_Heuristic (
	char const *			_hoops_PSGIH,
	char *					list)
{
	_hoops_PAPPR context("Show_One_Heuristic");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_Heuristic () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_RSRPP)) != null) {

		_hoops_GHAIR *	heuristics;
		if ((heuristics = (_hoops_GHAIR *)HI_Find_Attribute (context, target, HK_HEURISTICS)) != null) {

			_hoops_SGCIH (context, heuristics, _hoops_PSGIH, list, -1);
			_hoops_HPRH (heuristics);
		}
		_hoops_IRRPR();
	}
#endif
}


#ifndef _hoops_GRCIH


HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Heuristic (
	int						count,
	Key const *				keys,
	char const *			_hoops_PSGIH,
	char *					list) 
{
	_hoops_PAPPR context("Show_One_Net_Heuristics");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_One_Net_Heuristics () */\n");
	);

	_hoops_GHAIR *	heuristics;
	if ((heuristics = (_hoops_GHAIR *) HI_Find_Attribute_And_Lock(context, _hoops_RSRPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_SGCIH (context, heuristics, _hoops_PSGIH, list, -1);
		_hoops_HPRH (heuristics);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(list, -1, "", 0);
#endif
}
#endif




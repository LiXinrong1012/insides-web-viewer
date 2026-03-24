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
 * $Id: obf_tmp.txt 1.51 2010-08-25 01:14:00 jason Exp $
 */

#include "hoops.h"
#include "adt.h"

#include "hc_proto.h"
#include "hi_proto.h"


/* _hoops_HASIR _hoops_RGR _hoops_GAR _hoops_HAAI _hoops_GAR _hoops_CPHP _hoops_SHS _hoops_RRGPR _hoops_GRP _hoops_AGCR _hoops_PSCH */
#ifndef _hoops_AHSAI

#define BSPX 0x1
#define BSPY 0x2
#define BSPZ 0x4
#define BSP_GARBAGE 0x8 /* _hoops_PPRAR _hoops_HIH _hoops_HPAP */

#define _hoops_PHSAI 10
#define _hoops_HHSAI

#define _hoops_IHSAI (0.60f)
#define _hoops_CHSAI (0.40f)


GLOBAL_FUNCTION bool HI_Compute_Point_To_Line_Distance(
	Point const * point, 
	Point const * _hoops_RSSIH,  
	Point const * _hoops_AHPPA, 
	float alter *_hoops_CGSIR, 
	Point alter * _hoops_HGII)
{
	Vector	_hoops_ISPI = *_hoops_AHPPA - *_hoops_RSSIH;
    float	length = _hoops_ISPI.length();

	// _hoops_PASC
	//_hoops_SHSAI
    float _hoops_PRSHH = (((point->x - _hoops_RSSIH->x) * (_hoops_AHPPA->x - _hoops_RSSIH->x)) +
				((point->y - _hoops_RSSIH->y) * (_hoops_AHPPA->y - _hoops_RSSIH->y)) +
				((point->z - _hoops_RSSIH->z) * (_hoops_AHPPA->z - _hoops_RSSIH->z))) /
				 (length * length);
 
    if (_hoops_PRSHH < 0.0f || _hoops_PRSHH > 1.0f)
        return false;   /* _hoops_PHRHA _hoops_PPSR _hoops_RHAP _hoops_HAR _hoops_HSSC _hoops_GIAA _hoops_RH _hoops_III _hoops_CAGH */
 
	_hoops_ISPI *= _hoops_PRSHH; 

	Point _hoops_RSPSA = *_hoops_RSSIH + _hoops_ISPI;

	if (_hoops_HGII)
		*_hoops_HGII = _hoops_RSPSA;
 
	Vector	_hoops_CSPI = *point - _hoops_RSPSA;
    (*_hoops_CGSIR) = _hoops_CSPI.length();

    return true;
}


/*------------_hoops_SSCAR _hoops_RARIA------------------*/

local _hoops_HHSAR *	_hoops_GISAI(VBSP *tree) {
	_hoops_HHSAR *u;
	if (_hoops_PHSAI == 0)
		return null;
	POOL_ZALLOC(u, _hoops_HHSAR, tree->memory_pool);
	POOL_ALLOC_ARRAY(u->items, _hoops_PHSAI, void *, tree->memory_pool);
	POOL_ALLOC_ARRAY(u->item_bounds, _hoops_PHSAI, _hoops_SASC const *, tree->memory_pool);
	return u;
}


local void _hoops_RISAI(_hoops_HHSAR *u) {

	for (int i = 0; i < u->used; i++) {
		if (u->item_bounds[i] != null)
			FREE(u->item_bounds[i], _hoops_SASC);
	}
	FREE_ARRAY(u->items, _hoops_PHSAI, void *);
	FREE_ARRAY(u->item_bounds, _hoops_PHSAI, _hoops_SASC const *);
	FREE(u, _hoops_HHSAR);
}


local _hoops_IHSAR *_hoops_AISAI(VBSP *tree, int _hoops_CHSAR) {
	_hoops_IHSAR *node;
	POOL_ZALLOC(node, _hoops_IHSAR, tree->memory_pool);
	node->tree = tree;
	node->_hoops_CHSAR = _hoops_CHSAR;
 	node->_hoops_PAIS = _hoops_GISAI(tree);
	return node;
}


local void _hoops_PISAI(_hoops_IHSAR *node) {
	if (node->_hoops_RAGR != null)
		FREE_ARRAY(node->_hoops_RAGR, node->_hoops_PISAR, void *);
	if (node->_hoops_PAIS != null)
		_hoops_RISAI(node->_hoops_PAIS);
	if (node->kids[0] != null) {
		_hoops_PISAI(node->kids[0]);
		node->kids[0] = null;
	}
	if (node->kids[1] != null) {
		_hoops_PISAI(node->kids[1]);
		node->kids[1] = null;
	}
	if (node->kids[2] != null) {
		_hoops_PISAI(node->kids[2]);
		node->kids[2] = null;
	}
	FREE(node, _hoops_IHSAR);
}


GLOBAL_FUNCTION VBSP * HI_New_BSP(
	Memory_Pool *			memory_pool, 
	_hoops_SASC const &	bbox_in, 
	int						max_depth_in) 
{
	VBSP *	_hoops_SGHHA;
	POOL_ZALLOC(_hoops_SGHHA, VBSP, memory_pool);
	_hoops_SGHHA->memory_pool = memory_pool;
	_hoops_SGHHA->_hoops_SCSAR = -1;
	_hoops_SGHHA->bbox = bbox_in;
	_hoops_SGHHA->_hoops_SISAR = max_depth_in;
	_hoops_SGHHA->root = _hoops_AISAI(_hoops_SGHHA, BSPX);
 	return _hoops_SGHHA;
}


GLOBAL_FUNCTION void HI_Delete_BSP(VBSP *tree) {
	_hoops_PISAI(tree->root);
	FREE(tree, VBSP);
}


local int _hoops_HISAI(
	_hoops_IHSAR *		node,
	_hoops_CPSAR	function,
	void *			user_data) 
{
	for (int i = 0; i < node->_hoops_AISAR; i++) {
		if (function (node->_hoops_RAGR[i], user_data) == 0)
			return 0;
	}
	if (node->_hoops_PAIS != null) {
		_hoops_HHSAR *u = node->_hoops_PAIS;
		for (int i = 0; i < u->used; i++) {
			if (function (u->items[i], user_data) == 0)
				return 0;
		}
	}
	if (node->kids[0] != null)
		if (_hoops_HISAI(node->kids[0], function, user_data) == 0)
			return 0;
	if (node->kids[1] != null)
		if (_hoops_HISAI(node->kids[1], function, user_data) == 0)
			return 0;
	if (node->kids[2] != null)
		if (_hoops_HISAI(node->kids[2], function, user_data) == 0)
			return 0;
	return 1;
}


GLOBAL_FUNCTION int HI_BSP_Map_Function(
	VBSP *			tree,
	_hoops_CPSAR	function,
	void *			user_data) 
{
	return _hoops_HISAI(tree->root, function, user_data);
}



local void _hoops_IISAI(_hoops_IHSAR *node, void *data) {
	if (node->_hoops_AISAR == node->_hoops_PISAR) 
	{
		void **temp;
		int _hoops_PAGHH = node->_hoops_PISAR;

		if (node->_hoops_PISAR < 4)
			node->_hoops_PISAR = 4;
		else
			node->_hoops_PISAR *= 2;
		ALLOC_ARRAY(temp, node->_hoops_PISAR, void *);
		if (node->_hoops_RAGR != null) {
			memcpy(temp, node->_hoops_RAGR, node->_hoops_AISAR * sizeof(void *));
			FREE_ARRAY(node->_hoops_RAGR, _hoops_PAGHH, void *);
		}
		node->_hoops_RAGR = temp;
	}
	node->_hoops_RAGR[ node->_hoops_AISAR++ ] = data;
}


local bool _hoops_CISAI(
	VBSP *					tree,
	_hoops_HHSAR *		u, 
	void *					item, 
	_hoops_SASC const *	item_bounds) 
{
	if (u->used >= _hoops_PHSAI)
		return false;

	u->items[ u->used ] = item;

	if (item_bounds != item) {
		_hoops_SASC *	_hoops_SISAI;
		POOL_ZALLOC(_hoops_SISAI, _hoops_SASC, tree->memory_pool);
		*_hoops_SISAI = *item_bounds;
		u->item_bounds[u->used] = _hoops_SISAI;
	}
	else
		u->item_bounds[u->used] = null;

	u->used++;

	return true;
}

local void _hoops_GCSAI (
	VBSP *					tree,
	_hoops_IHSAR *				_hoops_ASCIA, 
	_hoops_SASC const *	_hoops_RCHS, 
	int						_hoops_SISAR,
	void *					item,
	_hoops_SASC const *	item_bounds,
	int						_hoops_RCSAI);

local void _hoops_ACSAI (
	VBSP *					tree,
	_hoops_IHSAR *				_hoops_ASCIA, 
	_hoops_SASC const *	_hoops_RCHS, 
	int						_hoops_SISAR,
	int						_hoops_RCSAI) 
{
	_hoops_HHSAR *		u = _hoops_ASCIA->_hoops_PAIS;
	
	/* _hoops_CCA _hoops_RH _hoops_HSPR _hoops_III, _hoops_SAII _hoops_HHHH _hoops_IS _hoops_IRGH _hoops_PSGR _hoops_IH _hoops_GCGC 
	 * _hoops_IIGR _hoops_GGAS.	_hoops_HHIGR _hoops_CSAP _hoops_HAHH _hoops_GGR _hoops_AGR _hoops_IS _hoops_CRHR _hoops_PGGS _hoops_PAGIR */
	_hoops_ASCIA->_hoops_PAIS = null;

	for (int i = 0; i < u->used; i++) {

		/* _hoops_IARGR->_hoops_RGGPR[_hoops_HAS] == _hoops_IRAP _hoops_HRGR _hoops_IRS _hoops_GRH _hoops_AGIR _hoops_SGS _hoops_SIGH _hoops_SGS _hoops_RH _hoops_IGCI
		 * _hoops_ACAS _hoops_RRGPR _hoops_CCA _hoops_SPSAR _hoops_SGS _hoops_PAH _hoops_SHH _hoops_IGI _hoops_GAR _hoops_IRS _hoops_IASC _hoops_AHCRR */

		_hoops_SASC const *	bbox;
		if (u->item_bounds[i] != null)
			bbox = u->item_bounds[i];
		else
			bbox = (_hoops_SASC const *)u->items[i];

		_hoops_GCSAI(tree, _hoops_ASCIA, _hoops_RCHS, _hoops_SISAR, u->items[i], bbox, _hoops_RCSAI);
	}

	_hoops_RISAI(u);
}










/* _hoops_GIPHR _hoops_IH _hoops_RH _hoops_SPS _hoops_HHPA _hoops_SPIS _hoops_IS _hoops_SHH _hoops_HHGP.	 _hoops_HHIGR _hoops_HRGR _hoops_RH _hoops_CIS'_hoops_GRI
 * _hoops_CSSAR _hoops_IS _hoops_GHSGR _hoops_SGS _hoops_RGR _hoops_IIP _hoops_SAGGR _hoops_PIGS _hoops_CCA _hoops_PCSAI == 0 */
INLINE int _hoops_HCSAI(int _hoops_ICSAI, int _hoops_RCSAI) 
{
	do {
		_hoops_ICSAI = (_hoops_ICSAI<<1);
		if (_hoops_ICSAI > BSPZ)
			_hoops_ICSAI = BSPX;
	} while (!(_hoops_ICSAI & _hoops_RCSAI));
	return _hoops_ICSAI;
}


local void _hoops_GCSAI (
	VBSP *					tree,
	_hoops_IHSAR *				_hoops_ASCIA, 
	_hoops_SASC const *	_hoops_RCHS, 
	int						_hoops_SISAR,
	void *					item,
	_hoops_SASC const *	item_bounds,
	int						_hoops_RCSAI) 
{

	if (_hoops_SISAR <= 0) {
		_hoops_IISAI(_hoops_ASCIA, item);
		return;
	}

	if (_hoops_ASCIA->_hoops_PAIS != null) {
		if (_hoops_CISAI(tree, _hoops_ASCIA->_hoops_PAIS, item, item_bounds))
			return;
		_hoops_ACSAI(tree, _hoops_ASCIA, _hoops_RCHS, _hoops_SISAR, _hoops_RCSAI);
	} 

	switch (_hoops_ASCIA->_hoops_CHSAR) {
		case BSPX: {
			float _hoops_RPIS = _hoops_RCHS->max.x - _hoops_RCHS->min.x;
			float _hoops_CCSAI = _hoops_RCHS->min.x + _hoops_IHSAI * _hoops_RPIS;
			if (item_bounds->max.x < _hoops_CCSAI) {
				/* _hoops_HIAAI _hoops_GPP _hoops_RH _hoops_PRPC */
				if (_hoops_ASCIA->kids[0] == null) 
					_hoops_ASCIA->kids[0] = _hoops_AISAI(_hoops_ASCIA->tree, _hoops_HCSAI(BSPX, _hoops_RCSAI));
				_hoops_SASC _hoops_SCSAI(*_hoops_RCHS);
				_hoops_SCSAI.max.x = _hoops_CCSAI;
				_hoops_GCSAI(tree, _hoops_ASCIA->kids[0], &_hoops_SCSAI, _hoops_SISAR - 1, item, item_bounds, _hoops_RCSAI);
			}
			else {
				float _hoops_GSSAI = _hoops_RCHS->min.x + _hoops_CHSAI * _hoops_RPIS;	
				if (item_bounds->min.x > _hoops_GSSAI) {
					/* _hoops_HIAAI _hoops_GPP _hoops_RH _hoops_SCIA */
					if (_hoops_ASCIA->kids[1] == null)
						_hoops_ASCIA->kids[1] = _hoops_AISAI(_hoops_ASCIA->tree, _hoops_HCSAI(BSPX, _hoops_RCSAI));
					_hoops_SASC _hoops_SCSAI(*_hoops_RCHS);
					_hoops_SCSAI.min.x = _hoops_GSSAI;
					_hoops_GCSAI(tree, _hoops_ASCIA->kids[1], &_hoops_SCSAI, _hoops_SISAR - 1, item, item_bounds, _hoops_RCSAI);
				}
				else {
#ifndef _hoops_HHSAI
					_hoops_IISAI(_hoops_ASCIA, item);
#else
					_hoops_RCSAI &= ~BSPX;
					if (!_hoops_RCSAI) {
						/* _hoops_RGGPR _hoops_ICHIA _hoops_RH _hoops_RSIR _hoops_RSSAI _hoops_ISPH, _hoops_GAR _hoops_PRAR _hoops_GAR _hoops_RH _hoops_RSSAI _hoops_PGHH
						 * _hoops_IIGR _hoops_HCR _hoops_RII _hoops_HAARR.	 _hoops_SCH _hoops_HGPHA _hoops_HPGR _hoops_RGR _hoops_PAPA */
						_hoops_IISAI(_hoops_ASCIA, item);
					}
					else {
						if (_hoops_ASCIA->kids[2] == null)
							_hoops_ASCIA->kids[2] = _hoops_AISAI(_hoops_ASCIA->tree, _hoops_HCSAI(BSPX, _hoops_RCSAI));
						_hoops_GCSAI(tree, _hoops_ASCIA->kids[2], _hoops_RCHS, _hoops_SISAR - 1, item, item_bounds, _hoops_RCSAI);
					}
#endif
				}
			}
		} break;
		case BSPY: {
			float _hoops_RPIS = _hoops_RCHS->max.y - _hoops_RCHS->min.y;
			float _hoops_CCSAI = _hoops_RCHS->min.y + _hoops_IHSAI * _hoops_RPIS;
			if (item_bounds->max.y < _hoops_CCSAI) {
				/* _hoops_HIAAI _hoops_GPP _hoops_RH _hoops_PRPC */
				if (_hoops_ASCIA->kids[0] == null)
					_hoops_ASCIA->kids[0] = _hoops_AISAI(_hoops_ASCIA->tree, _hoops_HCSAI(BSPY, _hoops_RCSAI));
				_hoops_SASC _hoops_SCSAI(*_hoops_RCHS);
				_hoops_SCSAI.max.y = _hoops_CCSAI;
				_hoops_GCSAI(tree, _hoops_ASCIA->kids[0], &_hoops_SCSAI, _hoops_SISAR - 1, item, item_bounds, _hoops_RCSAI);
			}
			else {
				float _hoops_GSSAI = _hoops_RCHS->min.y + _hoops_CHSAI * _hoops_RPIS;	
				if (item_bounds->min.y > _hoops_GSSAI) {
					/* _hoops_HIAAI _hoops_GPP _hoops_RH _hoops_SCIA */
					if (_hoops_ASCIA->kids[1] == null) 
						_hoops_ASCIA->kids[1] = _hoops_AISAI(_hoops_ASCIA->tree, _hoops_HCSAI(BSPY, _hoops_RCSAI));
					_hoops_SASC _hoops_SCSAI(*_hoops_RCHS);
					_hoops_SCSAI.min.y = _hoops_GSSAI;
					_hoops_GCSAI(tree, _hoops_ASCIA->kids[1], &_hoops_SCSAI, _hoops_SISAR - 1, item, item_bounds, _hoops_RCSAI);
				}
				else {
#ifndef _hoops_HHSAI
					_hoops_IISAI(_hoops_ASCIA, item);
#else
					_hoops_RCSAI &= ~BSPY;
					if (!_hoops_RCSAI) {
						/* _hoops_RGGPR _hoops_ICHIA _hoops_RH _hoops_RSIR _hoops_RSSAI _hoops_ISPH, _hoops_GAR _hoops_PRAR _hoops_GAR _hoops_RH _hoops_RSSAI _hoops_PGHH
						 * _hoops_IIGR _hoops_HCR _hoops_RII _hoops_HAARR.	 _hoops_SCH _hoops_HGPHA _hoops_HPGR _hoops_RGR _hoops_PAPA */
						_hoops_IISAI(_hoops_ASCIA, item);
					}
					else {
						if (_hoops_ASCIA->kids[2] == null)
							_hoops_ASCIA->kids[2] = _hoops_AISAI(_hoops_ASCIA->tree, _hoops_HCSAI(BSPY, _hoops_RCSAI));
						_hoops_GCSAI(tree, _hoops_ASCIA->kids[2], _hoops_RCHS, _hoops_SISAR - 1, item, item_bounds, _hoops_RCSAI);
					}
#endif
				}
			}
		} break;
		case BSPZ: {
			float _hoops_RPIS = _hoops_RCHS->max.z - _hoops_RCHS->min.z;
			float _hoops_CCSAI = _hoops_RCHS->min.z + _hoops_IHSAI * _hoops_RPIS;
			if (item_bounds->max.z < _hoops_CCSAI) {
				/* _hoops_HIAAI _hoops_GPP _hoops_RH _hoops_PRPC */
				if (_hoops_ASCIA->kids[0] == null)
					_hoops_ASCIA->kids[0] = _hoops_AISAI(_hoops_ASCIA->tree, _hoops_HCSAI(BSPZ, _hoops_RCSAI));
				_hoops_SASC _hoops_SCSAI(*_hoops_RCHS);
				_hoops_SCSAI.max.z = _hoops_CCSAI;
				_hoops_GCSAI(tree, _hoops_ASCIA->kids[0], &_hoops_SCSAI, _hoops_SISAR - 1, item, item_bounds, _hoops_RCSAI);
			}
			else {
				float _hoops_GSSAI = _hoops_RCHS->min.z + _hoops_CHSAI * _hoops_RPIS;	
				if (item_bounds->min.z > _hoops_GSSAI) {
					/* _hoops_HIAAI _hoops_GPP _hoops_RH _hoops_SCIA */
					if (_hoops_ASCIA->kids[1] == null)
						_hoops_ASCIA->kids[1] = _hoops_AISAI(_hoops_ASCIA->tree, _hoops_HCSAI(BSPZ, _hoops_RCSAI));
					_hoops_SASC _hoops_SCSAI(*_hoops_RCHS);
					_hoops_SCSAI.min.z = _hoops_GSSAI;
					_hoops_GCSAI(tree, _hoops_ASCIA->kids[1], &_hoops_SCSAI, _hoops_SISAR - 1, item, item_bounds, _hoops_RCSAI);
				}
				else {
#ifndef _hoops_HHSAI
					_hoops_IISAI(_hoops_ASCIA, item);
#else
					_hoops_RCSAI &= ~BSPZ;
					if (!_hoops_RCSAI) {
						/* _hoops_RGGPR _hoops_ICHIA _hoops_RH _hoops_RSIR _hoops_RSSAI _hoops_ISPH, _hoops_GAR _hoops_PRAR _hoops_GAR _hoops_RH _hoops_RSSAI _hoops_PGHH
						 * _hoops_IIGR _hoops_HCR _hoops_RII _hoops_HAARR.	 _hoops_SCH _hoops_HGPHA _hoops_HPGR _hoops_RGR _hoops_PAPA */
						_hoops_IISAI(_hoops_ASCIA, item);
					}
					else {
						if (_hoops_ASCIA->kids[2] == null)
							_hoops_ASCIA->kids[2] = _hoops_AISAI(_hoops_ASCIA->tree, _hoops_HCSAI(BSPZ, _hoops_RCSAI));
						_hoops_GCSAI(tree, _hoops_ASCIA->kids[2], _hoops_RCHS, _hoops_SISAR - 1, item, item_bounds, _hoops_RCSAI);
					}
#endif
				}
			}
		} break;
	}

} 



GLOBAL_FUNCTION void HI_BSP_Insert(
	VBSP *					tree, 
	void *					item,
	_hoops_SASC const *	item_bounds) 
{
	int _hoops_RCSAI = BSPX | BSPY | BSPZ;

	/* _hoops_RPP _hoops_RGGPR _hoops_HRGR _hoops_IRAP, _hoops_SR _hoops_HPCAR _hoops_SGS _hoops_RH _hoops_HSPP _hoops_IIGR _hoops_RH _hoops_IGCI 
	 * _hoops_ARSAR _hoops_HRGR _hoops_PCCP _hoops_SPSAR
	 * _hoops_AHIPR _hoops_IHAHP _hoops_HRGR _hoops_PSIGA _hoops_PGGA _hoops_SCH _hoops_AGSR _hoops_SGS _hoops_SR _hoops_PAH _hoops_PSCPR _hoops_SHCAH
	 * _hoops_SIHH _hoops_HAGC _hoops_IRS _hoops_IRGH _hoops_IPS (_hoops_CACH _hoops_ASSAI) */
	if (item_bounds == null)
		item_bounds = (_hoops_SASC const *)item;

	_hoops_GCSAI(tree, tree->root, &tree->bbox, tree->_hoops_SISAR, item, item_bounds, _hoops_RCSAI);
}

 





local bool _hoops_PSSAI(
	_hoops_IHSAR *				_hoops_ASCIA,
	_hoops_SASC const &	_hoops_HSSAI,
	void *					part,
	_hoops_SASC const &	part_bounds) 
{

	for (int i = 0; i < _hoops_ASCIA->_hoops_AISAR; i++) {
		if (!(*_hoops_ASCIA->tree->compare)(_hoops_ASCIA->tree->_hoops_HCSAR, _hoops_ASCIA->_hoops_RAGR[i], part)) {
			return false;
		}
	}

	if (_hoops_ASCIA->_hoops_PAIS != null) {
		_hoops_HHSAR *u = _hoops_ASCIA->_hoops_PAIS;
		for (int i = 0; i < u->used; i++) {
			if (!(*_hoops_ASCIA->tree->compare)(_hoops_ASCIA->tree->_hoops_HCSAR, u->items[i], part)) {
				return false;
			}
		}
	}

	switch (_hoops_ASCIA->_hoops_CHSAR) {
		case BSPX: {
			float _hoops_RPIS = _hoops_HSSAI.max.x - _hoops_HSSAI.min.x;
			float _hoops_GSSAI = _hoops_HSSAI.min.x + _hoops_CHSAI * _hoops_RPIS;
			float _hoops_CCSAI = _hoops_HSSAI.min.x + _hoops_IHSAI * _hoops_RPIS;
 
			float _hoops_GIGCR = HI_Cuboid_To_Cuboid_Distance(
							_hoops_SASC(_hoops_HSSAI.min, Point(_hoops_CCSAI, _hoops_HSSAI.max.y, _hoops_HSSAI.max.z)), 
							part_bounds);

			float _hoops_RIGCR = HI_Cuboid_To_Cuboid_Distance(
							_hoops_SASC(Point(_hoops_GSSAI, _hoops_HSSAI.min.y, _hoops_HSSAI.min.z), _hoops_HSSAI.max),
							part_bounds);
			
			if (_hoops_GIGCR < _hoops_RIGCR) {
				if (_hoops_ASCIA->kids[0] != null) {
					_hoops_SASC _hoops_ISSAI = _hoops_HSSAI;
					_hoops_ISSAI.max.x = _hoops_CCSAI;
					if (!_hoops_PSSAI(_hoops_ASCIA->kids[0], _hoops_ISSAI, part, part_bounds))
						return false;
				}
				if (_hoops_ASCIA->kids[1] != null) {
					_hoops_SASC _hoops_ISSAI = _hoops_HSSAI;
					_hoops_ISSAI.min.x = _hoops_GSSAI;
					if (!_hoops_PSSAI(_hoops_ASCIA->kids[1], _hoops_ISSAI, part, part_bounds))
						return false;
				}
			}
			else {
				if (_hoops_ASCIA->kids[1] != null) {
					_hoops_SASC _hoops_ISSAI = _hoops_HSSAI;
					_hoops_ISSAI.min.x = _hoops_GSSAI;
					if (!_hoops_PSSAI(_hoops_ASCIA->kids[1], _hoops_ISSAI, part, part_bounds))
						return false;
				}
				if (_hoops_ASCIA->kids[0] != null) {
					_hoops_SASC _hoops_ISSAI = _hoops_HSSAI;
					_hoops_ISSAI.max.x = _hoops_CCSAI;
					if (!_hoops_PSSAI(_hoops_ASCIA->kids[0], _hoops_ISSAI, part, part_bounds))
						return false;	
				}
			}
		} break;

		case BSPY: {
			float _hoops_RPIS = _hoops_HSSAI.max.y - _hoops_HSSAI.min.y;
			float _hoops_GSSAI = _hoops_HSSAI.min.y + _hoops_CHSAI * _hoops_RPIS;
			float _hoops_CCSAI = _hoops_HSSAI.min.y + _hoops_IHSAI * _hoops_RPIS;

			float _hoops_GIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(_hoops_HSSAI.min, Point(_hoops_HSSAI.max.x, _hoops_CCSAI, _hoops_HSSAI.max.z)), 
				part_bounds);

			float _hoops_RIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(Point(_hoops_HSSAI.min.x, _hoops_GSSAI, _hoops_HSSAI.min.z), _hoops_HSSAI.max),
				part_bounds);

			if (_hoops_GIGCR < _hoops_RIGCR) {
				if (_hoops_ASCIA->kids[0] != null) {
					_hoops_SASC _hoops_ISSAI = _hoops_HSSAI;
					_hoops_ISSAI.max.y = _hoops_CCSAI;
					if (!_hoops_PSSAI(_hoops_ASCIA->kids[0], _hoops_ISSAI, part, part_bounds))
						return false;
				}
				if (_hoops_ASCIA->kids[1] != null) {
					_hoops_SASC _hoops_ISSAI = _hoops_HSSAI;
					_hoops_ISSAI.min.y = _hoops_GSSAI;
					if (!_hoops_PSSAI(_hoops_ASCIA->kids[1], _hoops_ISSAI, part, part_bounds))
						return false;
				}
			}
			else {
				if (_hoops_ASCIA->kids[1] != null) {
					_hoops_SASC _hoops_ISSAI = _hoops_HSSAI;
					_hoops_ISSAI.min.y = _hoops_GSSAI;
					if (!_hoops_PSSAI(_hoops_ASCIA->kids[1], _hoops_ISSAI, part, part_bounds))
						return false;
				}
				if (_hoops_ASCIA->kids[0] != null) {
					_hoops_SASC _hoops_ISSAI = _hoops_HSSAI;
					_hoops_ISSAI.max.y = _hoops_CCSAI;
					if (!_hoops_PSSAI(_hoops_ASCIA->kids[0], _hoops_ISSAI, part, part_bounds))
						return false;
				}
			}
						
		} break;

		case BSPZ: {
			float _hoops_RPIS = _hoops_HSSAI.max.z - _hoops_HSSAI.min.z;
			float _hoops_GSSAI = _hoops_HSSAI.min.z + _hoops_CHSAI * _hoops_RPIS;
			float _hoops_CCSAI = _hoops_HSSAI.min.z + _hoops_IHSAI * _hoops_RPIS;

			float _hoops_GIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(_hoops_HSSAI.min, Point(_hoops_HSSAI.max.x, _hoops_HSSAI.max.y, _hoops_CCSAI)), 
				part_bounds);

			float _hoops_RIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(Point(_hoops_HSSAI.min.x, _hoops_HSSAI.min.y, _hoops_GSSAI), _hoops_HSSAI.max),
				part_bounds);

			if (_hoops_GIGCR < _hoops_RIGCR) {
				if (_hoops_ASCIA->kids[0] != null) {
					_hoops_SASC _hoops_ISSAI = _hoops_HSSAI;
					_hoops_ISSAI.max.z = _hoops_CCSAI;
					if (!_hoops_PSSAI(_hoops_ASCIA->kids[0], _hoops_ISSAI, part, part_bounds))
						return false;
				}
				if (_hoops_ASCIA->kids[1] != null) {
					_hoops_SASC _hoops_ISSAI = _hoops_HSSAI;
					_hoops_ISSAI.min.z = _hoops_GSSAI;
					if (!_hoops_PSSAI(_hoops_ASCIA->kids[1], _hoops_ISSAI, part, part_bounds))
						return false;
				}
			}
			else {
				if (_hoops_ASCIA->kids[1] != null) {
					_hoops_SASC _hoops_ISSAI = _hoops_HSSAI;
					_hoops_ISSAI.min.z = _hoops_GSSAI;
					if (!_hoops_PSSAI(_hoops_ASCIA->kids[1], _hoops_ISSAI, part, part_bounds))
						return false;
				}
				if (_hoops_ASCIA->kids[0] != null) {
					_hoops_SASC _hoops_ISSAI = _hoops_HSSAI;
					_hoops_ISSAI.max.z = _hoops_CCSAI;
					if (!_hoops_PSSAI(_hoops_ASCIA->kids[0], _hoops_ISSAI, part, part_bounds))
						return false;
				}
			}			
		} break;
	}

	/* _hoops_CSSAI[2] _hoops_HRGR _hoops_RH _hoops_ARP _hoops_IIGR _hoops_APSAR _hoops_SGS _hoops_SHHP _hoops_RH _hoops_RSSAI _hoops_ISPH _hoops_IIGR _hoops_RH _hoops_SCGR _hoops_GIIS, _hoops_HIH
	 * _hoops_HAR _hoops_SSCC _hoops_SGS _hoops_IIGR _hoops_RH _hoops_RII _hoops_HAARR.  _hoops_CPGP _hoops_SSIA _hoops_HS _hoops_RH _hoops_PSHR _hoops_PRCH _hoops_GAR _hoops_RH
	 * _hoops_SCGR _hoops_GIIS, _hoops_SSIA _hoops_CGH _hoops_SHR _hoops_SHH _hoops_RPCSH. */
	if (_hoops_ASCIA->kids[2] != null)
		_hoops_PSSAI(_hoops_ASCIA->kids[2], _hoops_HSSAI, part, part_bounds);

	return true;
}














local bool _hoops_SSSAI(
	_hoops_IHSAR *				_hoops_ASCIA,
	_hoops_SASC const &	_hoops_HSSAI,
	void *					part,
	_hoops_SASC const &	part_bounds) 
{

	for (int i = 0; i < _hoops_ASCIA->_hoops_AISAR; i++) {
		if (!(*_hoops_ASCIA->tree->compare)(_hoops_ASCIA->tree->_hoops_HCSAR, _hoops_ASCIA->_hoops_RAGR[i], part)) {
			return false;
		}
	}

	if (_hoops_ASCIA->_hoops_PAIS != null) {
		_hoops_HHSAR *u = _hoops_ASCIA->_hoops_PAIS;
		for (int i = 0; i < u->used; i++) {
			if (!(*_hoops_ASCIA->tree->compare)(_hoops_ASCIA->tree->_hoops_HCSAR, u->items[i], part)) {
				return false;
			}
		}
	}

	switch (_hoops_ASCIA->_hoops_CHSAR) {
		case BSPX: {
			float _hoops_RPIS = _hoops_HSSAI.max.x - _hoops_HSSAI.min.x;
			if (_hoops_ASCIA->kids[0] != null) {
				float _hoops_CCSAI = _hoops_HSSAI.min.x + _hoops_IHSAI * _hoops_RPIS;
				if (part_bounds.min.x <= _hoops_CCSAI) {
					/* _hoops_GGGPI _hoops_RH _hoops_RAAP */
					_hoops_SASC _hoops_SCSAI = _hoops_HSSAI;
					_hoops_SCSAI.max.x = _hoops_CCSAI;
					if (!_hoops_SSSAI(_hoops_ASCIA->kids[0], _hoops_SCSAI, part, part_bounds))
						return false;
				}
			}
			if (_hoops_ASCIA->kids[1] != null) {
				float _hoops_GSSAI = _hoops_HSSAI.min.x + _hoops_CHSAI * _hoops_RPIS;
				if (part_bounds.max.x >= _hoops_GSSAI) {
					/* _hoops_GGGPI _hoops_RH _hoops_RPHR */
					_hoops_SASC _hoops_SCSAI = _hoops_HSSAI;
					_hoops_SCSAI.min.x = _hoops_GSSAI;
					if (!_hoops_SSSAI(_hoops_ASCIA->kids[1], _hoops_SCSAI, part, part_bounds))
						return false;
				}
			}
		} break;

		case BSPY: {
			float _hoops_RPIS = _hoops_HSSAI.max.y - _hoops_HSSAI.min.y;
			if (_hoops_ASCIA->kids[0] != null) {
				float _hoops_CCSAI = _hoops_HSSAI.min.y + _hoops_IHSAI * _hoops_RPIS;
				if (part_bounds.min.y <= _hoops_CCSAI) {
					/* _hoops_GGGPI _hoops_RH _hoops_RAAP */
					_hoops_SASC _hoops_SCSAI = _hoops_HSSAI;
					_hoops_SCSAI.max.y = _hoops_CCSAI;
					if (!_hoops_SSSAI(_hoops_ASCIA->kids[0], _hoops_SCSAI, part, part_bounds))
						return false;
				}
			}
			if (_hoops_ASCIA->kids[1] != null) {
				float _hoops_GSSAI = _hoops_HSSAI.min.y + _hoops_CHSAI * _hoops_RPIS;
				if (part_bounds.max.y >= _hoops_GSSAI) {
					/* _hoops_GGGPI _hoops_RH _hoops_RPHR */
					_hoops_SASC _hoops_SCSAI = _hoops_HSSAI;
					_hoops_SCSAI.min.y = _hoops_GSSAI;
					if (!_hoops_SSSAI(_hoops_ASCIA->kids[1], _hoops_SCSAI, part, part_bounds))
						return false;
				}
			}
		} break;

		case BSPZ: {
			float _hoops_RPIS = _hoops_HSSAI.max.z - _hoops_HSSAI.min.z;
			if (_hoops_ASCIA->kids[0] != null) {
				float _hoops_CCSAI = _hoops_HSSAI.min.z + _hoops_IHSAI * _hoops_RPIS;
				if (part_bounds.min.z <= _hoops_CCSAI) {
					/* _hoops_GGGPI _hoops_RH _hoops_RAAP */
					_hoops_SASC _hoops_SCSAI = _hoops_HSSAI;
					_hoops_SCSAI.max.z = _hoops_CCSAI;
					if (!_hoops_SSSAI(_hoops_ASCIA->kids[0], _hoops_SCSAI, part, part_bounds))
						return false;
				}
			}
			if (_hoops_ASCIA->kids[1] != null) {
				float _hoops_GSSAI = _hoops_HSSAI.min.z + _hoops_CHSAI * _hoops_RPIS;
				if (part_bounds.max.z >= _hoops_GSSAI) {
					/* _hoops_GGGPI _hoops_RH _hoops_RPHR */
					_hoops_SASC _hoops_SCSAI = _hoops_HSSAI;
					_hoops_SCSAI.min.z = _hoops_GSSAI;
					if (!_hoops_SSSAI(_hoops_ASCIA->kids[1], _hoops_SCSAI, part, part_bounds))
						return false;
				}
			}
		} break;
	}
	/* _hoops_CSSAI[2] _hoops_HRGR _hoops_RH _hoops_ARP _hoops_IIGR _hoops_APSAR _hoops_SGS _hoops_SHHP _hoops_RH _hoops_RSSAI _hoops_ISPH _hoops_IIGR _hoops_RH _hoops_SCGR _hoops_GIIS, _hoops_HIH
	 * _hoops_HAR _hoops_SSCC _hoops_SGS _hoops_IIGR _hoops_RH _hoops_RII _hoops_HAARR.  _hoops_CPGP _hoops_SSIA _hoops_HS _hoops_RH _hoops_PSHR _hoops_PRCH _hoops_GAR _hoops_RH
	 * _hoops_SCGR _hoops_GIIS, _hoops_SSIA _hoops_CGH _hoops_SHR _hoops_SHH _hoops_RPCSH. */
	if (_hoops_ASCIA->kids[2] != null)
		_hoops_SSSAI(_hoops_ASCIA->kids[2], _hoops_HSSAI, part, part_bounds);

	return true;
}






local _hoops_CSCAR _hoops_RGGPI(
	_hoops_IHSAR *_hoops_ASCIA,
	_hoops_SASC const & _hoops_HSSAI,
	void *part,
	_hoops_SASC const & part_bounds) 
{
	_hoops_CSCAR status = VBSP_STATUS_CONTINUE;

 	if (_hoops_ASCIA->_hoops_AISAR > 16)
		status = (*_hoops_ASCIA->tree->compare)(_hoops_ASCIA->tree->_hoops_HCSAR, (void*)&_hoops_HSSAI, 0);
 	
	if (status == VBSP_STATUS_STOP)
		return status;

	switch (_hoops_ASCIA->_hoops_CHSAR) {
		case BSPX: {
			float _hoops_RPIS = _hoops_HSSAI.max.x - _hoops_HSSAI.min.x;
			if (_hoops_ASCIA->kids[0] != null) {
				float _hoops_CCSAI = _hoops_HSSAI.min.x + _hoops_IHSAI * _hoops_RPIS;
				/* _hoops_GGGPI _hoops_RH _hoops_RAAP */
				_hoops_SASC _hoops_SCSAI = _hoops_HSSAI;
				_hoops_SCSAI.max.x = _hoops_CCSAI;
				status = _hoops_RGGPI(_hoops_ASCIA->kids[0], _hoops_SCSAI, part, part_bounds);
				if (status == VBSP_STATUS_STOP)
					return status;
			}
			if (_hoops_ASCIA->kids[1] != null) {
				float _hoops_GSSAI = _hoops_HSSAI.min.x + _hoops_CHSAI * _hoops_RPIS;
				/* _hoops_GGGPI _hoops_RH _hoops_RPHR */
				_hoops_SASC _hoops_SCSAI = _hoops_HSSAI;
				_hoops_SCSAI.min.x = _hoops_GSSAI;
				status = _hoops_RGGPI(_hoops_ASCIA->kids[1], _hoops_SCSAI, part, part_bounds);
				if (status == VBSP_STATUS_STOP)
					return status;
			}
		} break;

		case BSPY: {
			float _hoops_RPIS = _hoops_HSSAI.max.y - _hoops_HSSAI.min.y;
			if (_hoops_ASCIA->kids[0] != null) {
				float _hoops_CCSAI = _hoops_HSSAI.min.y + _hoops_IHSAI * _hoops_RPIS;
				/* _hoops_GGGPI _hoops_RH _hoops_RAAP */
				_hoops_SASC _hoops_SCSAI = _hoops_HSSAI;
				_hoops_SCSAI.max.y = _hoops_CCSAI;
				status = _hoops_RGGPI(_hoops_ASCIA->kids[0], _hoops_SCSAI, part, part_bounds);
				if (status == VBSP_STATUS_STOP)
					return status;
			}
			if (_hoops_ASCIA->kids[1] != null) {
				float _hoops_GSSAI = _hoops_HSSAI.min.y + _hoops_CHSAI * _hoops_RPIS;
				/* _hoops_GGGPI _hoops_RH _hoops_RPHR */
				_hoops_SASC _hoops_SCSAI = _hoops_HSSAI;
				_hoops_SCSAI.min.y = _hoops_GSSAI;
				status = _hoops_RGGPI(_hoops_ASCIA->kids[1], _hoops_SCSAI, part, part_bounds);
				if (status == VBSP_STATUS_STOP)
					return status;
			}
		} break;

		case BSPZ: {
			float _hoops_RPIS = _hoops_HSSAI.max.z - _hoops_HSSAI.min.z;
			if (_hoops_ASCIA->kids[0] != null) {
				float _hoops_CCSAI = _hoops_HSSAI.min.z + _hoops_IHSAI * _hoops_RPIS;
				/* _hoops_GGGPI _hoops_RH _hoops_RAAP */
				_hoops_SASC _hoops_SCSAI = _hoops_HSSAI;
				_hoops_SCSAI.max.z = _hoops_CCSAI;
				status = _hoops_RGGPI(_hoops_ASCIA->kids[0], _hoops_SCSAI, part, part_bounds);
				if (status == VBSP_STATUS_STOP)
					return status;
			}
			if (_hoops_ASCIA->kids[1] != null) {
				float _hoops_GSSAI = _hoops_HSSAI.min.z + _hoops_CHSAI * _hoops_RPIS;
				/* _hoops_GGGPI _hoops_RH _hoops_RPHR */
				_hoops_SASC _hoops_SCSAI = _hoops_HSSAI;
				_hoops_SCSAI.min.z = _hoops_GSSAI;
				status = _hoops_RGGPI(_hoops_ASCIA->kids[1], _hoops_SCSAI, part, part_bounds);
				if (status == VBSP_STATUS_STOP)
					return status;
			}
		} break;
	}

	/* _hoops_CSSAI[2] _hoops_HRGR _hoops_RH _hoops_ARP _hoops_IIGR _hoops_APSAR _hoops_SGS _hoops_SHHP _hoops_RH _hoops_RSSAI _hoops_ISPH _hoops_IIGR _hoops_RH _hoops_SCGR _hoops_GIIS, _hoops_HIH
	 * _hoops_HAR _hoops_SSCC _hoops_SGS _hoops_IIGR _hoops_RH _hoops_RII _hoops_HAARR.  _hoops_CPGP _hoops_SSIA _hoops_HS _hoops_RH _hoops_PSHR _hoops_PRCH _hoops_GAR _hoops_RH
	 * _hoops_SCGR _hoops_GIIS, _hoops_SSIA _hoops_CGH _hoops_SHR _hoops_SHH _hoops_RPCSH. */
	if (_hoops_ASCIA->kids[2] != null)
		status = _hoops_RGGPI(_hoops_ASCIA->kids[2], _hoops_HSSAI, part, part_bounds);

	return status;
}

GLOBAL_FUNCTION  int HI_Test_BSP(
		VBSP *tree, 
		_hoops_PASAR _hoops_CAGPR,
		void *_hoops_HCSAR,
		void *part,
		_hoops_SASC const & part_bounds,
		bool _hoops_SAGPR
		) 
{
	tree->compare = _hoops_CAGPR;
	tree->_hoops_HCSAR = _hoops_HCSAR;

	if (!_hoops_SAGPR) 
		return _hoops_SSSAI(tree->root, tree->bbox, part, part_bounds);
	
	return _hoops_PSSAI(tree->root, tree->bbox, part, part_bounds);
}

GLOBAL_FUNCTION int HI_Test_BSP_Bounding_Reject(
	VBSP *					tree, 
	_hoops_PASAR		_hoops_CAGPR,
	_hoops_SASAR		_hoops_GPGPR,
	void *					_hoops_HCSAR,
	void *					part,
	_hoops_SASC const &	part_bounds) 
{
	tree->compare = _hoops_CAGPR;
	tree->_hoops_PCSAR = _hoops_GPGPR;
	tree->_hoops_HCSAR = _hoops_HCSAR;
	return _hoops_RGGPI(tree->root, tree->bbox, part, part_bounds);
}

 


local bool _hoops_AGGPI(
	_hoops_IHSAR *				_hoops_ASCIA,
	_hoops_SASC const &	_hoops_HSSAI,
	void *					part,
	Point const *			start,
	Vector const *			direction) 
{
	for (int i = 0; i < _hoops_ASCIA->_hoops_AISAR; i++) {
		if (!(*_hoops_ASCIA->tree->compare)(_hoops_ASCIA->tree->_hoops_HCSAR, _hoops_ASCIA->_hoops_RAGR[i], part)) {
			return false;
		}
	}
	if (_hoops_ASCIA->_hoops_PAIS != null) {
		_hoops_HHSAR *u = _hoops_ASCIA->_hoops_PAIS;
		for (int i = 0; i < u->used; i++) {
			if (!(*_hoops_ASCIA->tree->compare)(_hoops_ASCIA->tree->_hoops_HCSAR, u->items[i], part)) {
				return false;
			}
		}
	}

	switch (_hoops_ASCIA->_hoops_CHSAR) {
		case BSPX: {
			float _hoops_RPIS = _hoops_HSSAI.max.x - _hoops_HSSAI.min.x;
		
			if (_hoops_ASCIA->kids[0] != null) {
				/* _hoops_GGGPI _hoops_RH _hoops_RAAP */
				float _hoops_CCSAI = _hoops_HSSAI.min.x + _hoops_IHSAI * _hoops_RPIS;
				_hoops_SASC _hoops_SCSAI = _hoops_HSSAI;
				_hoops_SCSAI.max.x = _hoops_CCSAI;
				if (_hoops_SCSAI._hoops_RPCIR(*start, *direction) &&
					!_hoops_AGGPI(_hoops_ASCIA->kids[0], _hoops_SCSAI, part, start, direction))
					return false;
			}
			if (_hoops_ASCIA->kids[1] != null) {
				/* _hoops_GGGPI _hoops_RH _hoops_RPHR */
				float _hoops_GSSAI = _hoops_HSSAI.min.x + _hoops_CHSAI * _hoops_RPIS;
				_hoops_SASC _hoops_SCSAI = _hoops_HSSAI;
				_hoops_SCSAI.min.x = _hoops_GSSAI;
				if (_hoops_SCSAI._hoops_RPCIR(*start, *direction) &&
					!_hoops_AGGPI(_hoops_ASCIA->kids[1], _hoops_SCSAI, part, start, direction))
					return false;
			}
		} break;

		case BSPY: {
			float _hoops_RPIS = _hoops_HSSAI.max.y - _hoops_HSSAI.min.y;

			if (_hoops_ASCIA->kids[0] != null) {
				/* _hoops_GGGPI _hoops_RH _hoops_RAAP */
				float _hoops_CCSAI = _hoops_HSSAI.min.y + _hoops_IHSAI * _hoops_RPIS;
				_hoops_SASC _hoops_SCSAI = _hoops_HSSAI;
				_hoops_SCSAI.max.y = _hoops_CCSAI;
				if (_hoops_SCSAI._hoops_RPCIR(*start, *direction) &&
					!_hoops_AGGPI(_hoops_ASCIA->kids[0], _hoops_SCSAI, part, start, direction))
					return false;
			}
			if (_hoops_ASCIA->kids[1] != null) {
				/* _hoops_GGGPI _hoops_RH _hoops_RPHR */
				float _hoops_GSSAI = _hoops_HSSAI.min.y + _hoops_CHSAI * _hoops_RPIS;
				_hoops_SASC _hoops_SCSAI = _hoops_HSSAI;
				_hoops_SCSAI.min.y = _hoops_GSSAI;
				if (_hoops_SCSAI._hoops_RPCIR(*start, *direction) &&
					!_hoops_AGGPI(_hoops_ASCIA->kids[1], _hoops_SCSAI, part, start, direction))
					return false;
			}
		} break;

		case BSPZ: {
			float _hoops_RPIS = _hoops_HSSAI.max.z - _hoops_HSSAI.min.z;

			if (_hoops_ASCIA->kids[0] != null) {
				/* _hoops_GGGPI _hoops_RH _hoops_RAAP */
				float _hoops_CCSAI = _hoops_HSSAI.min.z + _hoops_IHSAI * _hoops_RPIS;
				_hoops_SASC _hoops_SCSAI = _hoops_HSSAI;
				_hoops_SCSAI.max.z = _hoops_CCSAI;
				if (_hoops_SCSAI._hoops_RPCIR(*start, *direction) &&
					!_hoops_AGGPI(_hoops_ASCIA->kids[0], _hoops_SCSAI, part, start, direction))
					return false;
			}
			if (_hoops_ASCIA->kids[1] != null) {
				/* _hoops_GGGPI _hoops_RH _hoops_RPHR */
				float _hoops_GSSAI = _hoops_HSSAI.min.z + _hoops_CHSAI * _hoops_RPIS;
				_hoops_SASC _hoops_SCSAI = _hoops_HSSAI;
				_hoops_SCSAI.min.z = _hoops_GSSAI;
				if (_hoops_SCSAI._hoops_RPCIR(*start, *direction) &&
					!_hoops_AGGPI(_hoops_ASCIA->kids[1], _hoops_SCSAI, part, start, direction))
					return false;
			}
		} break;
	}

	if (_hoops_ASCIA->kids[2] != null &&
		!_hoops_AGGPI(_hoops_ASCIA->kids[2], _hoops_HSSAI, part, start, direction))
		return false;

	return true;
}

GLOBAL_FUNCTION bool HI_Test_BSP_Ray(
	VBSP *				tree, 
	_hoops_PASAR	_hoops_CAGPR,
	void *				_hoops_HCSAR,
	void *				part,
	Point const *		start,
	Vector const *		direction) 
{
	if (tree == null)
		return false;

	tree->compare = _hoops_CAGPR;
	tree->_hoops_HCSAR = _hoops_HCSAR;

	return _hoops_AGGPI(tree->root, tree->bbox, part, start, direction);
}




local bool _hoops_PGGPI(
	_hoops_IHSAR *				_hoops_HGGPI,
	_hoops_SASC const &	part_bounds,
	_hoops_IHSAR *				_hoops_IGGPI, 
	_hoops_SASC const &	_hoops_CGGPI)
{
	if (!part_bounds._hoops_RPCIR(_hoops_CGGPI))
		return false;

	switch (_hoops_IGGPI->_hoops_CHSAR) {
		case BSPX: {
			float _hoops_RPIS = _hoops_CGGPI.max.x - _hoops_CGGPI.min.x;
			if (_hoops_IGGPI->kids[0] != null) {
				float _hoops_CCSAI = _hoops_CGGPI.min.x + _hoops_IHSAI * _hoops_RPIS;
				if (part_bounds.min.x <= _hoops_CCSAI) {
					/* _hoops_GGGPI _hoops_RAAP */
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.x = _hoops_CCSAI;
					if (!_hoops_PGGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[0], _hoops_SCSAI))
						return false;
				}
			}
			if (_hoops_IGGPI->kids[1] != null) {
				float _hoops_GSSAI = _hoops_CGGPI.min.x + _hoops_CHSAI * _hoops_RPIS;
				if (part_bounds.max.x >= _hoops_GSSAI) {
					/* _hoops_GGGPI _hoops_RPHR */
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.x = _hoops_GSSAI;
					if (!_hoops_PGGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[1], _hoops_SCSAI))
						return false;
				}
			}
		} break;

		case BSPY: {
			float _hoops_RPIS = _hoops_CGGPI.max.y - _hoops_CGGPI.min.y;
			if (_hoops_IGGPI->kids[0] != null) {
				float _hoops_CCSAI = _hoops_CGGPI.min.y + _hoops_IHSAI * _hoops_RPIS;
				if (part_bounds.min.y <= _hoops_CCSAI) {
					/* _hoops_GGGPI _hoops_RAAP */
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.y = _hoops_CCSAI;
					if (!_hoops_PGGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[0], _hoops_SCSAI))
						return false;
				}
			}
			if (_hoops_IGGPI->kids[1] != null) {
				float _hoops_GSSAI = _hoops_CGGPI.min.y + _hoops_CHSAI * _hoops_RPIS;
				if (part_bounds.max.y >= _hoops_GSSAI) {
					/* _hoops_GGGPI _hoops_RPHR */
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.y = _hoops_GSSAI;
					if (!_hoops_PGGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[1], _hoops_SCSAI))
						return false;
				}
			}
		} break;

		case BSPZ: {
			float _hoops_RPIS = _hoops_CGGPI.max.z - _hoops_CGGPI.min.z;
			if (_hoops_IGGPI->kids[0] != null) {
				float _hoops_CCSAI = _hoops_CGGPI.min.z + _hoops_IHSAI * _hoops_RPIS;
				if (part_bounds.min.z <= _hoops_CCSAI) {
					/* _hoops_GGGPI _hoops_RAAP */
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.z = _hoops_CCSAI;
					if (!_hoops_PGGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[0], _hoops_SCSAI))
						return false;
				}
			}
			if (_hoops_IGGPI->kids[1] != null) {
				float _hoops_GSSAI = _hoops_CGGPI.min.z + _hoops_CHSAI * _hoops_RPIS;
				if (part_bounds.max.z >= _hoops_GSSAI) {
					/* _hoops_GGGPI _hoops_RPHR */
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.z = _hoops_GSSAI;
					if (!_hoops_PGGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[1], _hoops_SCSAI))
						return false;
				}
			}
		} break;
	}

	if (_hoops_IGGPI->kids[2] != null &&
		!_hoops_PGGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[2], _hoops_CGGPI))
			return false;

 	for (int i = 0; i < _hoops_HGGPI->_hoops_AISAR; i++) {
		/* _hoops_ARIP _hoops_SRGR _hoops_ACSRR _hoops_SGGPI _hoops_SRGR */
		for (int j = 0; j < _hoops_IGGPI->_hoops_AISAR; j++) {
			_hoops_IGGPI->_hoops_IISAR = true;
			if (!(*_hoops_HGGPI->tree->compare)(_hoops_HGGPI->tree->_hoops_HCSAR, _hoops_HGGPI->_hoops_RAGR[i], _hoops_IGGPI->_hoops_RAGR[j]))
				return false;
		}
	}

	if (_hoops_HGGPI->_hoops_PAIS != null) {
		_hoops_HHSAR *u = _hoops_HGGPI->_hoops_PAIS;

		/* _hoops_ARIP _hoops_GRGPI _hoops_ACSRR _hoops_SGGPI _hoops_SRGR */
		for (int i = 0; i < u->used; i++) {
			for (int j = 0; j < _hoops_IGGPI->_hoops_AISAR; j++) {
				_hoops_IGGPI->_hoops_IISAR = true;
				if (!(*_hoops_HGGPI->tree->compare)(_hoops_HGGPI->tree->_hoops_HCSAR, u->items[i], _hoops_IGGPI->_hoops_RAGR[j]))
					return false;
			}
		}

		if (_hoops_IGGPI->_hoops_PAIS != null) {
			_hoops_HHSAR *_hoops_PCCRR = _hoops_IGGPI->_hoops_PAIS;
			/* _hoops_ARIP _hoops_GRGPI _hoops_ACSRR _hoops_SGGPI _hoops_GRGPI */
			for (int i = 0; i < u->used; i++) {
				for (int j = 0; j < _hoops_PCCRR->used; j++) {
					_hoops_IGGPI->_hoops_IISAR = true;
					if (!(*_hoops_HGGPI->tree->compare)(_hoops_HGGPI->tree->_hoops_HCSAR, u->items[i], _hoops_PCCRR->items[j]))
						return false;
				}
			}
		}
	}

	if (_hoops_IGGPI->_hoops_PAIS != null) {
		_hoops_HHSAR *_hoops_PCCRR = _hoops_IGGPI->_hoops_PAIS;
		/* _hoops_ARIP _hoops_SRGR _hoops_ACSRR _hoops_SGGPI _hoops_GRGPI */
		for (int i = 0; i < _hoops_HGGPI->_hoops_AISAR; i++) {
			for (int j = 0; j < _hoops_PCCRR->used; j++) {
				if (!(*_hoops_HGGPI->tree->compare)(_hoops_HGGPI->tree->_hoops_HCSAR, _hoops_HGGPI->_hoops_RAGR[i], _hoops_PCCRR->items[j]))
					return false;
			}
		}
	}

	return true;
}


local bool _hoops_RRGPI(
	_hoops_IHSAR *				_hoops_HGGPI,
	_hoops_SASC const &	part_bounds,
	_hoops_IHSAR *				_hoops_IGGPI, 
	_hoops_SASC const &	_hoops_CGGPI)
{

	float _hoops_ARGPI = HI_Cuboid_To_Cuboid_Distance(_hoops_CGGPI, part_bounds);

	if (_hoops_HGGPI->tree->_hoops_SCSAR < _hoops_ARGPI && _hoops_HGGPI->tree->_hoops_GSSAR)
		return true;

	switch (_hoops_IGGPI->_hoops_CHSAR) {
		case BSPX: {
			float _hoops_RPIS = _hoops_CGGPI.max.x - _hoops_CGGPI.min.x;
			float _hoops_GSSAI = _hoops_CGGPI.min.x + _hoops_CHSAI * _hoops_RPIS;
			float _hoops_CCSAI = _hoops_CGGPI.min.x + _hoops_IHSAI * _hoops_RPIS;
 
			float _hoops_GIGCR = HI_Cuboid_To_Cuboid_Distance(
						_hoops_SASC(_hoops_CGGPI.min, Point(_hoops_CCSAI, _hoops_CGGPI.max.y, _hoops_CGGPI.max.z)), 
						part_bounds);

			float _hoops_RIGCR = HI_Cuboid_To_Cuboid_Distance(
						_hoops_SASC(Point(_hoops_GSSAI, _hoops_CGGPI.min.y, _hoops_CGGPI.min.z), _hoops_CGGPI.max),
						part_bounds);
			
			if (_hoops_GIGCR < _hoops_RIGCR) {
				if (_hoops_IGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.x = _hoops_CCSAI;
					if (!_hoops_RRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[0], _hoops_SCSAI))
						return false;
				}
				if (_hoops_IGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.x = _hoops_GSSAI;
					if (!_hoops_RRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[1], _hoops_SCSAI))
						return false;
				}
			}
			else {
				if (_hoops_IGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.x = _hoops_GSSAI;
					if (!_hoops_RRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[1], _hoops_SCSAI))
						return false;
				}
				if (_hoops_IGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.x = _hoops_CCSAI;
					if (!_hoops_RRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[0], _hoops_SCSAI))
						return false;
				}
			}
		} break;

		case BSPY: {
			float _hoops_RPIS = _hoops_CGGPI.max.y - _hoops_CGGPI.min.y;
			float _hoops_GSSAI = _hoops_CGGPI.min.y + _hoops_CHSAI * _hoops_RPIS;
			float _hoops_CCSAI = _hoops_CGGPI.min.y + _hoops_IHSAI * _hoops_RPIS;

			float _hoops_GIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(_hoops_CGGPI.min, Point(_hoops_CGGPI.max.x, _hoops_CCSAI, _hoops_CGGPI.max.z)), 
				part_bounds);

			float _hoops_RIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(Point(_hoops_CGGPI.min.x, _hoops_GSSAI, _hoops_CGGPI.min.z), _hoops_CGGPI.max),
				part_bounds);

			if (_hoops_GIGCR < _hoops_RIGCR) {
				if (_hoops_IGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.y = _hoops_CCSAI;
					if (!_hoops_RRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[0], _hoops_SCSAI))
						return false;
				}
				if (_hoops_IGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.y = _hoops_GSSAI;
					if (!_hoops_RRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[1], _hoops_SCSAI))
						return false;
				}
			}
			else {
				if (_hoops_IGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.y = _hoops_GSSAI;
					if (!_hoops_RRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[1], _hoops_SCSAI))
						return false;
				}
				if (_hoops_IGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.y = _hoops_CCSAI;
					if (!_hoops_RRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[0], _hoops_SCSAI))
						return false;
				}
			}
						
		} break;

		case BSPZ: {
			float _hoops_RPIS = _hoops_CGGPI.max.z - _hoops_CGGPI.min.z;
			float _hoops_GSSAI = _hoops_CGGPI.min.z + _hoops_CHSAI * _hoops_RPIS;
			float _hoops_CCSAI = _hoops_CGGPI.min.z + _hoops_IHSAI * _hoops_RPIS;

			float _hoops_GIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(_hoops_CGGPI.min, Point(_hoops_CGGPI.max.x, _hoops_CGGPI.max.y, _hoops_CCSAI)), 
				part_bounds);

			float _hoops_RIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(Point(_hoops_CGGPI.min.x, _hoops_CGGPI.min.y, _hoops_GSSAI), _hoops_CGGPI.max),
				part_bounds);

			if (_hoops_GIGCR < _hoops_RIGCR) {
				if (_hoops_IGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.z = _hoops_CCSAI;
					if (!_hoops_RRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[0], _hoops_SCSAI))
						return false;
				}
				if (_hoops_IGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.z = _hoops_GSSAI;
					if (!_hoops_RRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[1], _hoops_SCSAI))
						return false;
				}
			}
			else {
				if (_hoops_IGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.z = _hoops_GSSAI;
					if (!_hoops_RRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[1], _hoops_SCSAI))
						return false;
				}
				if (_hoops_IGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.z = _hoops_CCSAI;
					if (!_hoops_RRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[0], _hoops_SCSAI))
						return false;
				}
			}			
		} break;
	}

	if (_hoops_IGGPI->kids[2] != null &&
		!_hoops_RRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[2], _hoops_CGGPI))
			return false;

	for (int i = 0; i < _hoops_HGGPI->_hoops_AISAR; i++) {
		/* _hoops_ARIP _hoops_SRGR _hoops_ACSRR _hoops_SGGPI _hoops_SRGR */
		for (int j = 0; j < _hoops_IGGPI->_hoops_AISAR; j++) {
			if (!(*_hoops_HGGPI->tree->compare)(_hoops_HGGPI->tree->_hoops_HCSAR, _hoops_HGGPI->_hoops_RAGR[i], _hoops_IGGPI->_hoops_RAGR[j]))
				return false;
		}
	}

	if (_hoops_HGGPI->_hoops_PAIS != null) {
		_hoops_HHSAR *u = _hoops_HGGPI->_hoops_PAIS;
		/* _hoops_ARIP _hoops_GRGPI _hoops_ACSRR _hoops_SGGPI _hoops_SRGR */
		for (int i = 0; i < u->used; i++) {
			for (int j = 0; j < _hoops_IGGPI->_hoops_AISAR; j++) {
				if (!(*_hoops_HGGPI->tree->compare)(_hoops_HGGPI->tree->_hoops_HCSAR, u->items[i], _hoops_IGGPI->_hoops_RAGR[j]))
					return false;
			}
		}

		if (_hoops_IGGPI->_hoops_PAIS != null) {
			_hoops_HHSAR *_hoops_PCCRR = _hoops_IGGPI->_hoops_PAIS;
			/* _hoops_ARIP _hoops_GRGPI _hoops_ACSRR _hoops_SGGPI _hoops_GRGPI */
			for (int i = 0; i < u->used; i++) {
				for (int j = 0; j < _hoops_PCCRR->used; j++) {
					if (!(*_hoops_HGGPI->tree->compare)(_hoops_HGGPI->tree->_hoops_HCSAR, u->items[i], _hoops_PCCRR->items[j]))
						return false;
				}
			}
		}
	}

	if (_hoops_IGGPI->_hoops_PAIS != null) {
		_hoops_HHSAR *_hoops_PCCRR = _hoops_IGGPI->_hoops_PAIS;
		/* _hoops_ARIP _hoops_SRGR _hoops_ACSRR _hoops_SGGPI _hoops_GRGPI */
		for (int i = 0; i < _hoops_HGGPI->_hoops_AISAR; i++) {
			for (int j = 0; j < _hoops_PCCRR->used; j++) {
				if (!(*_hoops_HGGPI->tree->compare)(_hoops_HGGPI->tree->_hoops_HCSAR, _hoops_HGGPI->_hoops_RAGR[i], _hoops_PCCRR->items[j]))
					return false;
			}
		}
	}

	return true;
}



local bool _hoops_PRGPI(_hoops_SASC const & _hoops_CRHPA, _hoops_SASC const & _hoops_SRHPA, Vector _hoops_CCSAR, float *dist)
{
	Point _hoops_CCAIA = _hoops_AICIR(_hoops_CRHPA.max, _hoops_CRHPA.min);
	Point _hoops_SCAIA = _hoops_AICIR(_hoops_SRHPA.max, _hoops_SRHPA.min);

	float _hoops_ASAIA = _hoops_CRHPA._hoops_RSAIA().length();
	float _hoops_GSAIA = _hoops_SRHPA._hoops_RSAIA().length();

	_hoops_CCSAR *= 1000.0f;

	Point _hoops_PSAIA(_hoops_CCAIA.x + _hoops_CCSAR.x, _hoops_CCAIA.y + _hoops_CCSAR.y, _hoops_CCAIA.z + _hoops_CCSAR.z);

	float _hoops_IRIIA;
	Point _hoops_HGII;

	if (HI_Compute_Point_To_Line_Distance(&_hoops_SCAIA, &_hoops_CCAIA, &_hoops_PSAIA, &_hoops_IRIIA, &_hoops_HGII)) {
		if (_hoops_IRIIA < (_hoops_GSAIA/2.0f + _hoops_ASAIA/2.0f)) {		
			*dist = _hoops_SRCIR(Point(_hoops_CCAIA.x, _hoops_CCAIA.y, _hoops_CCAIA.z), Point(_hoops_HGII.x, _hoops_HGII.y, _hoops_HGII.z)) - _hoops_GSAIA/2.0f - _hoops_ASAIA/2.0f;
			return true;
		}
	}
	return false;
}

local bool _hoops_HRGPI(
	_hoops_IHSAR *				_hoops_HGGPI,
	_hoops_SASC const &	part_bounds,
	_hoops_IHSAR *				_hoops_IGGPI, 
	_hoops_SASC const &	_hoops_CGGPI)
{
	float dist;

	if (!_hoops_PRGPI(part_bounds, _hoops_CGGPI, _hoops_HGGPI->tree->_hoops_CCSAR, &dist))
	 	return true;

	if (_hoops_HGGPI->tree->_hoops_SCSAR < dist && _hoops_HGGPI->tree->_hoops_GSSAR)
		return true;

	switch (_hoops_IGGPI->_hoops_CHSAR) {
		case BSPX: {
			float _hoops_RPIS = _hoops_CGGPI.max.x - _hoops_CGGPI.min.z;
			float _hoops_GSSAI = _hoops_CGGPI.min.x + _hoops_CHSAI * _hoops_RPIS;
			float _hoops_CCSAI = _hoops_CGGPI.min.x + _hoops_IHSAI * _hoops_RPIS;

			float _hoops_GIGCR = HI_Cuboid_To_Cuboid_Distance(
							_hoops_SASC(_hoops_CGGPI.min, Point(_hoops_CCSAI, _hoops_CGGPI.max.y, _hoops_CGGPI.max.z)), 
							part_bounds);

			float _hoops_RIGCR = HI_Cuboid_To_Cuboid_Distance(
							_hoops_SASC(Point(_hoops_GSSAI, _hoops_CGGPI.min.y, _hoops_CGGPI.min.z), _hoops_CGGPI.max),
							part_bounds);

			if (_hoops_GIGCR < _hoops_RIGCR) {
				if (_hoops_IGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.x = _hoops_CCSAI;
					if (!_hoops_HRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[0], _hoops_SCSAI))
						return false;
				}
				if (_hoops_IGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.x = _hoops_GSSAI;
					if (!_hoops_HRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[1], _hoops_SCSAI))
						return false;
				}
			}
			else {
				if (_hoops_IGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.x = _hoops_GSSAI;
					if (!_hoops_HRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[1], _hoops_SCSAI))
						return false;
				}
				if (_hoops_IGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.x = _hoops_CCSAI;
					if (!_hoops_HRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[0], _hoops_SCSAI))
						return false;
				}
			}

		} break;

		case BSPY: {
			float _hoops_RPIS = _hoops_CGGPI.max.y - _hoops_CGGPI.min.z;
			float _hoops_GSSAI = _hoops_CGGPI.min.y + _hoops_CHSAI * _hoops_RPIS;
			float _hoops_CCSAI = _hoops_CGGPI.min.y + _hoops_IHSAI * _hoops_RPIS;

			float _hoops_GIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(_hoops_CGGPI.min, Point(_hoops_CGGPI.max.x, _hoops_CCSAI, _hoops_CGGPI.max.z)), 
				part_bounds);

			float _hoops_RIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(Point(_hoops_CGGPI.min.x, _hoops_GSSAI, _hoops_CGGPI.min.z), _hoops_CGGPI.max),
				part_bounds);

			if (_hoops_GIGCR < _hoops_RIGCR) {
				if (_hoops_IGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.y = _hoops_CCSAI;
					if (!_hoops_HRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[0], _hoops_SCSAI))
						return false;
				}
				if (_hoops_IGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.y = _hoops_GSSAI;
					if (!_hoops_HRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[1], _hoops_SCSAI))
						return false;
				}
			}
			else {
				if (_hoops_IGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.y = _hoops_GSSAI;
					if (!_hoops_HRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[1], _hoops_SCSAI))
						return false;
				}
				if (_hoops_IGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.y = _hoops_CCSAI;
					if (!_hoops_HRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[0], _hoops_SCSAI))
						return false;
				}
			}
						
		} break;

		case BSPZ: {
			float _hoops_RPIS = _hoops_CGGPI.max.z - _hoops_CGGPI.min.z;
			float _hoops_GSSAI = _hoops_CGGPI.min.z + _hoops_CHSAI * _hoops_RPIS;
			float _hoops_CCSAI = _hoops_CGGPI.min.z + _hoops_IHSAI * _hoops_RPIS;

			float _hoops_GIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(_hoops_CGGPI.min, Point(_hoops_CGGPI.max.x, _hoops_CGGPI.max.y, _hoops_CCSAI)), 
				part_bounds);

			float _hoops_RIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(Point(_hoops_CGGPI.min.x, _hoops_CGGPI.min.y, _hoops_GSSAI), _hoops_CGGPI.max),
				part_bounds);

			if (_hoops_GIGCR < _hoops_RIGCR) {
				if (_hoops_IGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.z = _hoops_CCSAI;
					if (!_hoops_HRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[0], _hoops_SCSAI))
						return false;
				}
				if (_hoops_IGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.z = _hoops_GSSAI;
					if (!_hoops_HRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[1], _hoops_SCSAI))
						return false;
				}
			}
			else {
				if (_hoops_IGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.z = _hoops_GSSAI;
					if (!_hoops_HRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[1], _hoops_SCSAI))
						return false;
				}
				if (_hoops_IGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.z = _hoops_CCSAI;
					if (!_hoops_HRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[0], _hoops_SCSAI))
						return false;
				}
			}
						
		} break;
	}


	if (_hoops_IGGPI->kids[2] != null &&
		!_hoops_HRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI->kids[2], _hoops_CGGPI))
			return false;

	for (int i = 0; i < _hoops_HGGPI->_hoops_AISAR; i++) {
		/* _hoops_ARIP _hoops_SRGR _hoops_ACSRR _hoops_SGGPI _hoops_SRGR */
		for (int j = 0; j < _hoops_IGGPI->_hoops_AISAR; j++) {
			if (!(*_hoops_HGGPI->tree->compare)(_hoops_HGGPI->tree->_hoops_HCSAR, _hoops_HGGPI->_hoops_RAGR[i], _hoops_IGGPI->_hoops_RAGR[j]))
				return false;
		}
	}

	if (_hoops_HGGPI->_hoops_PAIS != null) {
		_hoops_HHSAR *u = _hoops_HGGPI->_hoops_PAIS;
		/* _hoops_ARIP _hoops_GRGPI _hoops_ACSRR _hoops_SGGPI _hoops_SRGR */
		for (int i = 0; i < u->used; i++) {
			for (int j = 0; j < _hoops_IGGPI->_hoops_AISAR; j++) {
				if (!(*_hoops_HGGPI->tree->compare)(_hoops_HGGPI->tree->_hoops_HCSAR, u->items[i], _hoops_IGGPI->_hoops_RAGR[j]))
					return false;
			}
		}

		if (_hoops_IGGPI->_hoops_PAIS != null) {
			_hoops_HHSAR *_hoops_PCCRR = _hoops_IGGPI->_hoops_PAIS;
			/* _hoops_ARIP _hoops_GRGPI _hoops_ACSRR _hoops_SGGPI _hoops_GRGPI */
			for (int i = 0; i < u->used; i++) {
				for (int j = 0; j < _hoops_PCCRR->used; j++) {
					if (!(*_hoops_HGGPI->tree->compare)(_hoops_HGGPI->tree->_hoops_HCSAR, u->items[i], _hoops_PCCRR->items[j]))
						return false;
				}
			}
		}
	}

	if (_hoops_IGGPI->_hoops_PAIS != null) {
		_hoops_HHSAR *_hoops_PCCRR = _hoops_IGGPI->_hoops_PAIS;
		/* _hoops_ARIP _hoops_SRGR _hoops_ACSRR _hoops_SGGPI _hoops_GRGPI */
		for (int i = 0; i < _hoops_HGGPI->_hoops_AISAR; i++) {
			for (int j = 0; j < _hoops_PCCRR->used; j++) {
				if (!(*_hoops_HGGPI->tree->compare)(_hoops_HGGPI->tree->_hoops_HCSAR, _hoops_HGGPI->_hoops_RAGR[i], _hoops_PCCRR->items[j]))
					return false;
			}
		}
	}

	return true;
}


local bool _hoops_IRGPI(
	_hoops_IHSAR *				_hoops_HGGPI,
	_hoops_SASC const &	part_bounds,
	_hoops_IHSAR *				_hoops_IGGPI, 
	_hoops_SASC const &	_hoops_CGGPI)
{
	if (!part_bounds._hoops_RPCIR(_hoops_CGGPI))
		return false;

	if (_hoops_HGGPI->_hoops_AISAR || (_hoops_HGGPI->_hoops_PAIS && _hoops_HGGPI->_hoops_PAIS->used)) {
		if (!_hoops_PGGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI, _hoops_CGGPI))
			return false;
	}

	switch (_hoops_HGGPI->_hoops_CHSAR) {
		case BSPX: {
			float _hoops_RPIS = part_bounds.max.x - part_bounds.min.x;

			if (_hoops_HGGPI->kids[0] != null) {
				float _hoops_CCSAI = part_bounds.min.x + _hoops_IHSAI * _hoops_RPIS;
				if (_hoops_CGGPI.min.x <= _hoops_CCSAI) {
					/* _hoops_GGGPI _hoops_RAAP */
					_hoops_SASC _hoops_SCSAI(part_bounds);
					_hoops_SCSAI.max.x = _hoops_CCSAI;
					if (!_hoops_IRGPI(_hoops_HGGPI->kids[0], _hoops_SCSAI, _hoops_IGGPI, _hoops_CGGPI))
						return false;
				}
			}
			if (_hoops_HGGPI->kids[1] != null) {
				float _hoops_GSSAI = part_bounds.min.x + _hoops_CHSAI * _hoops_RPIS;
				if (_hoops_CGGPI.max.x >= _hoops_GSSAI) {
					/* _hoops_GGGPI _hoops_RPHR */
					_hoops_SASC _hoops_SCSAI(part_bounds);
					_hoops_SCSAI.min.x = _hoops_GSSAI;
					if (!_hoops_IRGPI(_hoops_HGGPI->kids[1], _hoops_SCSAI, _hoops_IGGPI, _hoops_CGGPI))
						return false;
				}
			}
		} break;

		case BSPY: {
			float _hoops_RPIS = part_bounds.max.y - part_bounds.min.y;

			if (_hoops_HGGPI->kids[0] != null) {
				float _hoops_CCSAI = part_bounds.min.y + _hoops_IHSAI * _hoops_RPIS;
				if (_hoops_CGGPI.min.y <= _hoops_CCSAI) {
					/* _hoops_GGGPI _hoops_RAAP */
					_hoops_SASC _hoops_SCSAI(part_bounds);
					_hoops_SCSAI.max.y = _hoops_CCSAI;
					if (!_hoops_IRGPI(_hoops_HGGPI->kids[0], _hoops_SCSAI, _hoops_IGGPI, _hoops_CGGPI))
						return false;
				}
			}
			if (_hoops_HGGPI->kids[1] != null) {
				float _hoops_GSSAI = part_bounds.min.y + _hoops_CHSAI * _hoops_RPIS;
				if (_hoops_CGGPI.max.y >= _hoops_GSSAI) {
					/* _hoops_GGGPI _hoops_RPHR */
					_hoops_SASC _hoops_SCSAI(part_bounds);
					_hoops_SCSAI.min.y = _hoops_GSSAI;
					if (!_hoops_IRGPI(_hoops_HGGPI->kids[1], _hoops_SCSAI, _hoops_IGGPI, _hoops_CGGPI))
						return false;
				}
			}
		} break;

		case BSPZ: {
			float _hoops_RPIS = part_bounds.max.z - part_bounds.min.z;

			if (_hoops_HGGPI->kids[0] != null) {
				float _hoops_CCSAI = part_bounds.min.z + _hoops_IHSAI * _hoops_RPIS;
				if (_hoops_CGGPI.min.z <= _hoops_CCSAI) {
					/* _hoops_GGGPI _hoops_RAAP */
					_hoops_SASC _hoops_SCSAI(part_bounds);
					_hoops_SCSAI.max.z = _hoops_CCSAI;
					if (!_hoops_IRGPI(_hoops_HGGPI->kids[0], _hoops_SCSAI, _hoops_IGGPI, _hoops_CGGPI))
						return false;
				}
			}
			if (_hoops_HGGPI->kids[1] != null) {
				float _hoops_GSSAI = part_bounds.min.z + _hoops_CHSAI * _hoops_RPIS;
				if (_hoops_CGGPI.max.z >= _hoops_GSSAI) {
					/* _hoops_GGGPI _hoops_RPHR */
					_hoops_SASC _hoops_SCSAI(part_bounds);
					_hoops_SCSAI.min.z = _hoops_GSSAI;
					if (!_hoops_IRGPI(_hoops_HGGPI->kids[1], _hoops_SCSAI, _hoops_IGGPI, _hoops_CGGPI))
						return false;
				}
			}
		} break;
	}

	if (_hoops_HGGPI->kids[2] != null &&
		!_hoops_IRGPI(_hoops_HGGPI->kids[2], part_bounds, _hoops_IGGPI, _hoops_CGGPI))
			return false;

	return true;
}

local bool _hoops_CRGPI(
	_hoops_IHSAR *				_hoops_HGGPI,
	_hoops_SASC const &	part_bounds,
	_hoops_IHSAR *				_hoops_IGGPI, 
	_hoops_SASC const &	_hoops_CGGPI)
{

	float _hoops_ARGPI = HI_Cuboid_To_Cuboid_Distance(_hoops_CGGPI, part_bounds);

	if (_hoops_HGGPI->tree->_hoops_SCSAR < _hoops_ARGPI && _hoops_HGGPI->tree->_hoops_GSSAR)
		return true;

	if (_hoops_HGGPI->_hoops_AISAR || _hoops_HGGPI->_hoops_PAIS) {	
		if (!_hoops_RRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI, _hoops_CGGPI))
			return false;
	}

	switch (_hoops_HGGPI->_hoops_CHSAR) {
		case BSPX: {
			float _hoops_RPIS = part_bounds.max.x - part_bounds.min.x;
			float _hoops_GSSAI = part_bounds.min.x + _hoops_CHSAI * _hoops_RPIS;
			float _hoops_CCSAI = part_bounds.min.x + _hoops_IHSAI * _hoops_RPIS;

			float _hoops_GIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(part_bounds.min, Point(_hoops_CCSAI, part_bounds.max.y, part_bounds.max.z)), 
				_hoops_CGGPI);

			float _hoops_RIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(Point(_hoops_GSSAI, part_bounds.min.y, part_bounds.min.z), part_bounds.max),
				_hoops_CGGPI);

			if (_hoops_GIGCR < _hoops_RIGCR) {
				if (_hoops_HGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.x = _hoops_CCSAI;
					if (!_hoops_CRGPI(_hoops_HGGPI->kids[0], part_bounds, _hoops_IGGPI, _hoops_SCSAI))
						return false;
				}
				if (_hoops_HGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.x = _hoops_GSSAI;
					if (!_hoops_CRGPI(_hoops_HGGPI->kids[1], part_bounds, _hoops_IGGPI, _hoops_SCSAI))
						return false;
				}
			}
			else {
				if (_hoops_HGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.x = _hoops_GSSAI;
					if (!_hoops_CRGPI(_hoops_HGGPI->kids[1], part_bounds, _hoops_IGGPI, _hoops_SCSAI))
						return false;
				}
				if (_hoops_HGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.x = _hoops_CCSAI;
					if (!_hoops_CRGPI(_hoops_HGGPI->kids[0], part_bounds, _hoops_IGGPI, _hoops_SCSAI))
						return false;
				}
			}
		} break;

		case BSPY: {
			float _hoops_RPIS = part_bounds.max.y - part_bounds.min.y;
			float _hoops_GSSAI = part_bounds.min.y + _hoops_CHSAI * _hoops_RPIS;
			float _hoops_CCSAI = part_bounds.min.y + _hoops_IHSAI * _hoops_RPIS;

			float _hoops_GIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(part_bounds.min, Point(part_bounds.max.x, _hoops_CCSAI, part_bounds.max.z)), 
				_hoops_CGGPI);

			float _hoops_RIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(Point(part_bounds.min.x, _hoops_GSSAI, part_bounds.min.z), part_bounds.max),
				_hoops_CGGPI);

			if (_hoops_GIGCR < _hoops_RIGCR) {
				if (_hoops_HGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.y = _hoops_CCSAI;
					if (!_hoops_CRGPI(_hoops_HGGPI->kids[0], part_bounds, _hoops_IGGPI, _hoops_SCSAI))
						return false;
				}
				if (_hoops_HGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.y = _hoops_GSSAI;
					if (!_hoops_CRGPI(_hoops_HGGPI->kids[1], part_bounds, _hoops_IGGPI, _hoops_SCSAI))
						return false;
				}
			}
			else {
				if (_hoops_HGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.y = _hoops_GSSAI;
					if (!_hoops_CRGPI(_hoops_HGGPI->kids[1], part_bounds, _hoops_IGGPI, _hoops_SCSAI))
						return false;
				}
				if (_hoops_HGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.y = _hoops_CCSAI;
					if (!_hoops_CRGPI(_hoops_HGGPI->kids[0], part_bounds, _hoops_IGGPI, _hoops_SCSAI))
						return false;
				}
			}
		} break;

		case BSPZ: {
			float _hoops_RPIS = part_bounds.max.z - part_bounds.min.z;
			float _hoops_GSSAI = part_bounds.min.z + _hoops_CHSAI * _hoops_RPIS;
			float _hoops_CCSAI = part_bounds.min.z + _hoops_IHSAI * _hoops_RPIS;

			float _hoops_GIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(part_bounds.min, Point(part_bounds.max.x, part_bounds.max.y, _hoops_CCSAI)), 
				_hoops_CGGPI);

			float _hoops_RIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(Point(part_bounds.min.x, part_bounds.min.y, _hoops_GSSAI), part_bounds.max),
				_hoops_CGGPI);

			if (_hoops_GIGCR < _hoops_RIGCR) {
				if (_hoops_HGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.z = _hoops_CCSAI;
					if (!_hoops_CRGPI(_hoops_HGGPI->kids[0], part_bounds, _hoops_IGGPI, _hoops_SCSAI))
						return false;
				}
				if (_hoops_HGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.z = _hoops_GSSAI;
					if (!_hoops_CRGPI(_hoops_HGGPI->kids[1], part_bounds, _hoops_IGGPI, _hoops_SCSAI))
						return false;
				}
			}
			else {
				if (_hoops_HGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.min.z = _hoops_GSSAI;
					if (!_hoops_CRGPI(_hoops_HGGPI->kids[1], part_bounds, _hoops_IGGPI, _hoops_SCSAI))
						return false;
				}
				if (_hoops_HGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(_hoops_CGGPI);
					_hoops_SCSAI.max.z = _hoops_CCSAI;
					if (!_hoops_CRGPI(_hoops_HGGPI->kids[0], part_bounds, _hoops_IGGPI, _hoops_SCSAI))
						return false;
				}
			}
		} break;
	}

	if (_hoops_HGGPI->kids[2] != null &&
		!_hoops_CRGPI(_hoops_HGGPI->kids[2], part_bounds, _hoops_IGGPI, _hoops_CGGPI))
			return false;

	return true;
}



local bool _hoops_SRGPI(
	_hoops_IHSAR *				_hoops_HGGPI,
	_hoops_SASC const &	part_bounds,
	_hoops_IHSAR *				_hoops_IGGPI, 
	_hoops_SASC const &	_hoops_CGGPI)
{
	float dist;

	if (!_hoops_PRGPI(part_bounds, _hoops_CGGPI, _hoops_HGGPI->tree->_hoops_CCSAR, &dist))
	 	return true;

	if (_hoops_HGGPI->tree->_hoops_SCSAR < dist && _hoops_HGGPI->tree->_hoops_GSSAR)
		return true;

	if (_hoops_HGGPI->_hoops_AISAR || _hoops_HGGPI->_hoops_PAIS) {	
		if (!_hoops_HRGPI(_hoops_HGGPI, part_bounds, _hoops_IGGPI, _hoops_CGGPI))
			return false;
	}

	switch (_hoops_HGGPI->_hoops_CHSAR) {
		case BSPX: {
			float _hoops_RPIS = part_bounds.max.x - part_bounds.min.x;
			float _hoops_GSSAI = part_bounds.min.x + _hoops_CHSAI * _hoops_RPIS;
			float _hoops_CCSAI = part_bounds.min.x + _hoops_IHSAI * _hoops_RPIS;

			float _hoops_GIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(part_bounds.min, Point(_hoops_CCSAI, part_bounds.max.y, part_bounds.max.z)), 
				_hoops_CGGPI);

			float _hoops_RIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(Point(_hoops_GSSAI, part_bounds.min.y, part_bounds.min.z), part_bounds.max),
				_hoops_CGGPI);
			
			if (_hoops_GIGCR < _hoops_RIGCR) {
				if (_hoops_HGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(part_bounds);
					_hoops_SCSAI.max.x = _hoops_CCSAI;
					if (!_hoops_SRGPI(_hoops_HGGPI->kids[0], _hoops_SCSAI, _hoops_IGGPI, _hoops_CGGPI))
						return false;
				}
				if (_hoops_HGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(part_bounds);
					_hoops_SCSAI.min.x = _hoops_GSSAI;
					if (!_hoops_SRGPI(_hoops_HGGPI->kids[1], _hoops_SCSAI, _hoops_IGGPI, _hoops_CGGPI))
						return false;
				}
			}
			else {
				if (_hoops_HGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(part_bounds);
					_hoops_SCSAI.min.x = _hoops_GSSAI;
					if (!_hoops_SRGPI(_hoops_HGGPI->kids[1], _hoops_SCSAI, _hoops_IGGPI, _hoops_CGGPI))
						return false;
				}
				if (_hoops_HGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(part_bounds);
					_hoops_SCSAI.max.x = _hoops_CCSAI;
					if (!_hoops_SRGPI(_hoops_HGGPI->kids[0], _hoops_SCSAI, _hoops_IGGPI, _hoops_CGGPI))
						return false;
				}
			}
		} break;

		case BSPY: {
			float _hoops_RPIS = part_bounds.max.y - part_bounds.min.y;
			float _hoops_GSSAI = part_bounds.min.y + _hoops_CHSAI * _hoops_RPIS;
			float _hoops_CCSAI = part_bounds.min.y + _hoops_IHSAI * _hoops_RPIS;

			float _hoops_GIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(part_bounds.min, Point(part_bounds.max.x, _hoops_CCSAI, part_bounds.max.z)), 
				_hoops_CGGPI);

			float _hoops_RIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(Point(part_bounds.min.x, _hoops_GSSAI, part_bounds.min.z), part_bounds.max),
				_hoops_CGGPI);

			if (_hoops_GIGCR < _hoops_RIGCR) {
				if (_hoops_HGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(part_bounds);
					_hoops_SCSAI.max.y = _hoops_CCSAI;
					if (!_hoops_SRGPI(_hoops_HGGPI->kids[0], _hoops_SCSAI, _hoops_IGGPI, _hoops_CGGPI))
						return false;
				}
				if (_hoops_HGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(part_bounds);
					_hoops_SCSAI.min.y = _hoops_GSSAI;
					if (!_hoops_SRGPI(_hoops_HGGPI->kids[1], _hoops_SCSAI, _hoops_IGGPI, _hoops_CGGPI))
						return false;
				}
			}
			else {

				if (_hoops_HGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(part_bounds);
					_hoops_SCSAI.min.y = _hoops_GSSAI;
					if (!_hoops_SRGPI(_hoops_HGGPI->kids[1], _hoops_SCSAI, _hoops_IGGPI, _hoops_CGGPI))
						return false;
				}
				if (_hoops_HGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(part_bounds);
					_hoops_SCSAI.max.y = _hoops_CCSAI;
					if (!_hoops_SRGPI(_hoops_HGGPI->kids[0], _hoops_SCSAI, _hoops_IGGPI, _hoops_CGGPI))
						return false;
				}
			}
		} break;

		case BSPZ: {
			float _hoops_RPIS = part_bounds.max.z - part_bounds.min.z;
			float _hoops_GSSAI = part_bounds.min.z + _hoops_CHSAI * _hoops_RPIS;
			float _hoops_CCSAI = part_bounds.min.z + _hoops_IHSAI * _hoops_RPIS;

			float _hoops_GIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(part_bounds.min, Point(part_bounds.max.x, part_bounds.max.y, _hoops_CCSAI)), 
				_hoops_CGGPI);

			float _hoops_RIGCR = HI_Cuboid_To_Cuboid_Distance(
				_hoops_SASC(Point(part_bounds.min.x, part_bounds.min.y, _hoops_GSSAI), part_bounds.max),
				_hoops_CGGPI);

			if (_hoops_GIGCR < _hoops_RIGCR) {
				if (_hoops_HGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(part_bounds);
					_hoops_SCSAI.max.z = _hoops_CCSAI;
					if (!_hoops_SRGPI(_hoops_HGGPI->kids[0], _hoops_SCSAI, _hoops_IGGPI, _hoops_CGGPI))
						return false;
				}
				if (_hoops_HGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(part_bounds);
					_hoops_SCSAI.min.z = _hoops_GSSAI;
					if (!_hoops_SRGPI(_hoops_HGGPI->kids[1], _hoops_SCSAI, _hoops_IGGPI, _hoops_CGGPI))
						return false;
				}
			}
			else {
				if (_hoops_HGGPI->kids[1] != null) {
					_hoops_SASC _hoops_SCSAI(part_bounds);
					_hoops_SCSAI.min.z = _hoops_GSSAI;
					if (!_hoops_SRGPI(_hoops_HGGPI->kids[1], _hoops_SCSAI, _hoops_IGGPI, _hoops_CGGPI))
						return false;
				}
				if (_hoops_HGGPI->kids[0] != null) {
					_hoops_SASC _hoops_SCSAI(part_bounds);
					_hoops_SCSAI.max.z = _hoops_CCSAI;
					if (!_hoops_SRGPI(_hoops_HGGPI->kids[0], _hoops_SCSAI, _hoops_IGGPI, _hoops_CGGPI))
						return false;
				}
			}
		} break;
	}

	if (_hoops_HGGPI->kids[2] != null &&
		!_hoops_SRGPI(_hoops_HGGPI->kids[2], part_bounds, _hoops_IGGPI, _hoops_CGGPI))
			return false;

	return true;
}


GLOBAL_FUNCTION int HI_Test_BSP_BSP(
	VBSP *				_hoops_HGGPI, 
	_hoops_PASAR	_hoops_CAGPR, 
	void *				_hoops_HCSAR,
	VBSP *				_hoops_IGGPI,
	bool				_hoops_SAGPR) 
{
	_hoops_HGGPI->compare = _hoops_CAGPR;
	_hoops_HGGPI->_hoops_HCSAR = _hoops_HCSAR;

	if (_hoops_SAGPR)
		if (_hoops_HGGPI->_hoops_ICSAR)
			return _hoops_SRGPI(_hoops_HGGPI->root, _hoops_HGGPI->bbox,_hoops_IGGPI->root, _hoops_IGGPI->bbox);
		else
 			return _hoops_CRGPI(_hoops_HGGPI->root, _hoops_HGGPI->bbox, _hoops_IGGPI->root, _hoops_IGGPI->bbox);
	else
		return _hoops_IRGPI(_hoops_HGGPI->root, _hoops_HGGPI->bbox, _hoops_IGGPI->root, _hoops_IGGPI->bbox);
}


 

/* #_hoops_PPIP _hoops_GAGPI */
#ifdef _hoops_RAGPI
#include "hc_proto.h"
void _hoops_AAGPI(_hoops_IHSAR *_hoops_SGHHA, float *_hoops_RCHS)
{
	float _hoops_PAGPI[2], bounds_save;

	switch (_hoops_SGHHA->_hoops_CHSAR) {
		case BSPX: {
			_hoops_PAGPI[0] = _hoops_RCHS[0] + _hoops_CHSAI * (_hoops_RCHS[3] - _hoops_RCHS[0]);
			_hoops_PAGPI[1] = _hoops_RCHS[0] + _hoops_IHSAI * (_hoops_RCHS[3] - _hoops_RCHS[0]);
			if (_hoops_SGHHA->kids[0] != null) {
				bounds_save = _hoops_RCHS[3];
				_hoops_RCHS[3] = _hoops_PAGPI[1];
				_hoops_AAGPI(_hoops_SGHHA->kids[0], _hoops_RCHS);
				_hoops_RCHS[3] = bounds_save;
			}
			if (_hoops_SGHHA->kids[1] != null) {
				bounds_save = _hoops_RCHS[0];
				_hoops_RCHS[0] = _hoops_PAGPI[0];
				_hoops_AAGPI(_hoops_SGHHA->kids[1], _hoops_RCHS);
				_hoops_RCHS[0] = bounds_save;
			}
		} break;
		case BSPY: {
			_hoops_PAGPI[0] = _hoops_RCHS[1] + _hoops_CHSAI * (_hoops_RCHS[4] - _hoops_RCHS[1]);
			_hoops_PAGPI[1] = _hoops_RCHS[1] + _hoops_IHSAI * (_hoops_RCHS[4] - _hoops_RCHS[1]);

			if (_hoops_SGHHA->kids[0] != null) {
				bounds_save = _hoops_RCHS[4];
				_hoops_RCHS[4] = _hoops_PAGPI[1];
				_hoops_AAGPI(_hoops_SGHHA->kids[0], _hoops_RCHS);
				_hoops_RCHS[4] = bounds_save;
			}
			if (_hoops_SGHHA->kids[1] != null) {
				bounds_save = _hoops_RCHS[1];
				_hoops_RCHS[1] = _hoops_PAGPI[0];
				_hoops_AAGPI(_hoops_SGHHA->kids[1], _hoops_RCHS);
				_hoops_RCHS[1] = bounds_save;
			}
		} break;
		case BSPZ: {
			_hoops_PAGPI[0] = _hoops_RCHS[2] + _hoops_CHSAI * (_hoops_RCHS[5] - _hoops_RCHS[2]);
			_hoops_PAGPI[1] = _hoops_RCHS[2] + _hoops_IHSAI * (_hoops_RCHS[5] - _hoops_RCHS[2]);

			if (_hoops_SGHHA->kids[0] != null) {
				bounds_save = _hoops_RCHS[5];
				_hoops_RCHS[5] = _hoops_PAGPI[1];
				_hoops_AAGPI(_hoops_SGHHA->kids[0], _hoops_RCHS);
				_hoops_RCHS[5] = bounds_save;
			}
			if (_hoops_SGHHA->kids[1] != null) {
				bounds_save = _hoops_RCHS[2];
				_hoops_RCHS[2] = _hoops_PAGPI[0];
				_hoops_AAGPI(_hoops_SGHHA->kids[1], _hoops_RCHS);
				_hoops_RCHS[2] = bounds_save;
			}
		} break;
	}	 
	if (_hoops_SGHHA->kids[2] != null) {
		_hoops_AAGPI(_hoops_SGHHA->kids[2], _hoops_RCHS);
	}
	HC_Insert_Marker(_hoops_RCHS[0], _hoops_RCHS[1], _hoops_RCHS[2]);
	HC_Insert_Marker(_hoops_RCHS[0], _hoops_RCHS[1], _hoops_RCHS[5]);
	HC_Insert_Marker(_hoops_RCHS[0], _hoops_RCHS[4], _hoops_RCHS[2]);
	HC_Insert_Marker(_hoops_RCHS[0], _hoops_RCHS[4], _hoops_RCHS[5]);
	HC_Insert_Marker(_hoops_RCHS[3], _hoops_RCHS[1], _hoops_RCHS[2]);
	HC_Insert_Marker(_hoops_RCHS[3], _hoops_RCHS[1], _hoops_RCHS[5]);
	HC_Insert_Marker(_hoops_RCHS[3], _hoops_RCHS[4], _hoops_RCHS[2]);
	HC_Insert_Marker(_hoops_RCHS[3], _hoops_RCHS[4], _hoops_RCHS[5]);
}
void _hoops_HAGPI(Key _hoops_SRCP, char *color, VBSP *_hoops_SGHHA)
{
	HC_Open_Segment_By_Key(_hoops_SRCP);
		HC_Set_Color(color);
		HC_Set_Visibility("markers = on");
		_hoops_AAGPI(_hoops_SGHHA->root, _hoops_SGHHA->bbox);
	HC_Close_Segment();
}
#endif



#endif /* _hoops_CHS _hoops_IAGPI */


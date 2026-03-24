/*
 * Copyright (c) 1998-2001 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.101 2010-10-16 02:10:20 covey Exp $
 */


#include "hoops.h"
#include "hc_proto.h"

#ifndef _hoops_IGGGC
#include "database.h"
#include "phedron.h"
#include "driver.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "adt.h"
#include "please.h"

#define _hoops_CGGGC	0

#define _hoops_SGGGC			8
#define _hoops_GRGGC			64
#define _hoops_RRIS				0.15f
#define _hoops_RRGGC		1
#define _hoops_ARGGC		24
#define _hoops_PRGGC	24
#define _hoops_HRGGC		false

#define _hoops_IRGGC			0.1
#define _hoops_CRGGC				1000
#define _hoops_SRGGC			150
#define _hoops_GAGGC		4

/* _hoops_IRHP _hoops_RIP _hoops_RHSP _hoops_PSPRH, _hoops_GCGSP _hoops_CGPR _hoops_CPHR, _hoops_HIS _hoops_PAH _hoops_SHH _hoops_PA */
#define _hoops_RAGGC		_hoops_RSHSP


local void _hoops_AAGGC (
	_hoops_HCHSP *			node)
{
	_hoops_PCHSP **		_hoops_ASRGR = &node->items;
	_hoops_PCHSP *		item;
	_hoops_SASC		_hoops_IPIAA;
	Point				_hoops_RPIS;
	_hoops_SASC		limits;

	ZALLOC_ARRAY (node->_hoops_ICHSP, 8, _hoops_HCHSP *);

	_hoops_RPIS.x = node->limits.max.x - node->limits.min.x;
	_hoops_RPIS.y = node->limits.max.y - node->limits.min.y;
	_hoops_RPIS.z = node->limits.max.z - node->limits.min.z;

	_hoops_IPIAA.min.x = node->limits.min.x + (0.5f-_hoops_RRIS) * _hoops_RPIS.x;
	_hoops_IPIAA.min.y = node->limits.min.y + (0.5f-_hoops_RRIS) * _hoops_RPIS.y;
	_hoops_IPIAA.min.z = node->limits.min.z + (0.5f-_hoops_RRIS) * _hoops_RPIS.z;
	_hoops_IPIAA.max.x = node->limits.min.x + (0.5f+_hoops_RRIS) * _hoops_RPIS.x;
	_hoops_IPIAA.max.y = node->limits.min.y + (0.5f+_hoops_RRIS) * _hoops_RPIS.y;
	_hoops_IPIAA.max.z = node->limits.min.z + (0.5f+_hoops_RRIS) * _hoops_RPIS.z;

	while ((item = *_hoops_ASRGR) != null) {
		_hoops_HCHSP *		_hoops_HCPIH = null;

		for (int i=0; i<8; i++) {
			_hoops_SASC alter &	_hoops_PAGGC = limits;

			if ((_hoops_HCPIH = node->_hoops_ICHSP[i]) != null) {
				_hoops_PAGGC = _hoops_HCPIH->limits;
			}
			else {
				if ((i & 1) == 0) {
					limits.min.x = node->limits.min.x;
					limits.max.x = _hoops_IPIAA.max.x;
				}
				else {
					limits.min.x = _hoops_IPIAA.min.x;
					limits.max.x = node->limits.max.x;
				}
				if ((i & 2) == 0) {
					limits.min.y = node->limits.min.y;
					limits.max.y = _hoops_IPIAA.max.y;
				}
				else {
					limits.min.y = _hoops_IPIAA.min.y;
					limits.max.y = node->limits.max.y;
				}
				if ((i & 4) == 0) {
					limits.min.z = node->limits.min.z;
					limits.max.z = _hoops_IPIAA.max.z;
				}
				else {
					limits.min.z = _hoops_IPIAA.min.z;
					limits.max.z = node->limits.max.z;
				}
			}

			if (_hoops_PAGGC._hoops_HPCIR(item->_hoops_RCHS)) {
				/* _hoops_HIAAI _hoops_RH _hoops_CISAR _hoops_IH _hoops_RGR _hoops_RPSI */
				if (_hoops_HCPIH == null) {
					ZALLOC (_hoops_HCPIH, _hoops_HCHSP);
					_hoops_HCPIH->limits = _hoops_PAGGC;
					node->_hoops_ICHSP[i] = _hoops_HCPIH;
					_hoops_HCPIH->_hoops_SCAAR = node;
					_hoops_HCPIH->_hoops_RCHS = item->_hoops_RCHS;
				}
				else
					_hoops_HCPIH->_hoops_RCHS.Merge(item->_hoops_RCHS);

				*_hoops_ASRGR = item->next;
				--node->count;

				item->next = _hoops_HCPIH->items;
				_hoops_HCPIH->items = item;
				++_hoops_HCPIH->count;

				break;
			}
			_hoops_HCPIH = null;
		}

		if (_hoops_HCPIH == null) {
			/* _hoops_IRPSR'_hoops_RA _hoops_SIHRR _hoops_GGR _hoops_IRS _hoops_RPSI, _hoops_GRHP _hoops_SCH _hoops_ARI _hoops_PPR _hoops_IHIS _hoops_IGIAR */
			_hoops_ASRGR = &item->next;
		}
	}
}

local void _hoops_HAGGC (
	_hoops_PGSGP *			_hoops_SHGCR,
	_hoops_HCHSP *				root,
	_hoops_CRCP const *			_hoops_SRCP,
	_hoops_HICS const &	path,
	Bounding &				bounding,
	int						level) {
	_hoops_PCHSP *			item;

	if (level > _hoops_PRGGC)
		return;

	ZALLOC (item, _hoops_PCHSP);
	item->next = null;
	item->segment = _hoops_SRCP;
	item->path = path;
	item->_hoops_RCHS = bounding->cuboid;
	_hoops_PRRH (_hoops_SRCP);

	if (_hoops_SHGCR->_hoops_SSHSP) {
		ZALLOC (root, _hoops_HCHSP);
		root->limits = bounding->cuboid;
		root->_hoops_RCHS = root->limits;
		root->items = item;
		++root->count;
		_hoops_SHGCR->_hoops_SSHSP->AddLast(root);
		return;
	}

	if (root == null) {
		ZALLOC (root, _hoops_HCHSP);
		root->limits = bounding->cuboid;
		root->_hoops_RCHS = root->limits;
		root->flags = _hoops_RAGGC;
		root->items = item;
		++root->count;
		_hoops_SHGCR->root = root;
	}
	else if (BIT (root->flags, _hoops_RAGGC)) {
		/* _hoops_IRCH _hoops_IS _hoops_GCIS _hoops_CCAH _hoops_IGCI */
		root->limits.Merge(bounding->cuboid);
		root->_hoops_RCHS = root->limits;
		item->next = root->items;
		root->items = item;
		if (++root->count > _hoops_GRGGC) {
			root->flags = 0;	/* _hoops_PSP _hoops_RPIP _hoops_IAGGC */
			_hoops_AAGGC (root);
		}
	}
	else if (root->limits._hoops_HPCIR(bounding->cuboid)) {
		/* _hoops_HIAAI _hoops_PCSRR, _hoops_HIH _hoops_PRCH _hoops_GHCA _hoops_RRP _hoops_IS _hoops_ASRHA */
		root->_hoops_RCHS.Merge(bounding->cuboid);

		if (root->_hoops_ICHSP != null) {
			for (int i=0; i<8; i++) {
				_hoops_SASC		_hoops_CAGGC;
				_hoops_HCHSP *			_hoops_HCPIH;

				if ((_hoops_HCPIH = root->_hoops_ICHSP[i]) != null) {
					_hoops_CAGGC = _hoops_HCPIH->limits;
				}
				else {
					if ((i & 1) == 0) {
						_hoops_CAGGC.min.x = root->limits.min.x;
						_hoops_CAGGC.max.x = root->limits.min.x +
							(0.5f+_hoops_RRIS) * (root->limits.max.x - root->limits.min.x);
					}
					else {
						_hoops_CAGGC.min.x = root->limits.min.x +
							(0.5f-_hoops_RRIS) * (root->limits.max.x - root->limits.min.x);
						_hoops_CAGGC.max.x = root->limits.max.x;
					}
					if ((i & 2) == 0) {
						_hoops_CAGGC.min.y = root->limits.min.y;
						_hoops_CAGGC.max.y = root->limits.min.y +
							(0.5f+_hoops_RRIS) * (root->limits.max.y - root->limits.min.y);
					}
					else {
						_hoops_CAGGC.min.y = root->limits.min.y +
							(0.5f-_hoops_RRIS) * (root->limits.max.y - root->limits.min.y);
						_hoops_CAGGC.max.y = root->limits.max.y;
					}
					if ((i & 4) == 0) {
						_hoops_CAGGC.min.z = root->limits.min.z;
						_hoops_CAGGC.max.z = root->limits.min.z +
							(0.5f+_hoops_RRIS) * (root->limits.max.z - root->limits.min.z);
					}
					else {
						_hoops_CAGGC.min.z = root->limits.min.z +
							(0.5f-_hoops_RRIS) * (root->limits.max.z - root->limits.min.z);
						_hoops_CAGGC.max.z = root->limits.max.z;
					}
				}

				if (_hoops_CAGGC._hoops_HPCIR(bounding->cuboid)) {
					/* _hoops_HIAAI _hoops_RH _hoops_CISAR _hoops_IH _hoops_RGR _hoops_RPSI */
					if (level >= _hoops_PRGGC) {
						/* _hoops_PSP _hoops_RRP _hoops_IS _hoops_HGHC _hoops_SCH _hoops_GGR _hoops_HHIS */
						_hoops_HPRH (_hoops_SRCP);
						item->path.release();
						FREE (item, _hoops_PCHSP);
					}
					else if (_hoops_HCPIH == null) {
						ZALLOC (_hoops_HCPIH, _hoops_HCHSP);
						_hoops_HCPIH->limits = _hoops_CAGGC;
						root->_hoops_ICHSP[i] = _hoops_HCPIH;
						_hoops_HCPIH->_hoops_SCAAR = root;
						_hoops_HCPIH->_hoops_RCHS = item->_hoops_RCHS;
						item->next = _hoops_HCPIH->items;
						_hoops_HCPIH->items = item;
						++root->count;
					}
					else {
						/* _hoops_PHRSA _hoops_AASA _hoops_GRS _hoops_IRHH _hoops_RGCI _hoops_HAII "_hoops_IGCI", _hoops_HIS _hoops_RCSH _hoops_RH _hoops_SPR _hoops_SR _hoops_IIAC */
						_hoops_HPRH (_hoops_SRCP);
						item->path.release();
						FREE (item, _hoops_PCHSP);

						_hoops_HAGGC (_hoops_SHGCR, _hoops_HCPIH, _hoops_SRCP, path, bounding, level+1);
					}
					return;
				}
			}

			/* _hoops_SARS'_hoops_RA _hoops_SIHRR _hoops_GII _hoops_RPSI _hoops_CISAR */
			item->next = root->items;
			root->items = item;
			++root->count;
		}
		else {
			item->next = root->items;
			root->items = item;
			if ((++root->count > _hoops_SHGCR->_hoops_GGISP && level < _hoops_PRGGC))
				_hoops_AAGGC (root);
		}
	}
	else {
		if (root->_hoops_SCAAR != null) {
			/* _hoops_CHISR? */
		}

		_hoops_PCCAR {
			float			lower, upper;
			_hoops_HCHSP *		_hoops_SCAAR;
			int				index = 0;

			ZALLOC (_hoops_SCAAR, _hoops_HCHSP);
			ZALLOC_ARRAY (_hoops_SCAAR->_hoops_ICHSP, 8, _hoops_HCHSP *);
			_hoops_SCAAR->_hoops_RCHS = root->_hoops_RCHS;
			/* _hoops_HSPP _hoops_CCA _hoops_RH _hoops_RPSI'_hoops_GRI _hoops_PCSRR */
			_hoops_SCAAR->limits = root->limits;

			/* _hoops_PPR _hoops_IRHI _hoops_GGR _hoops_PGAP _hoops_SGIPR _hoops_HAGA _hoops_SSCP _hoops_SARPA _hoops_RSSAI */
			/* _hoops_PAGA: _hoops_CGPR _hoops_SR _hoops_IRCH _hoops_IS _hoops_GSSC, _hoops_RPSI _hoops_HRGR _hoops_PHPA _hoops_HIS _hoops_PH _hoops_CIHA */
			lower = root->limits.min.x - bounding->cuboid.min.x;
			upper = bounding->cuboid.max.x - root->limits.max.x;
			if (root->limits.min.x == root->limits.max.x) {
				if (bounding->cuboid.min.x < root->limits.min.x)
					_hoops_SCAAR->limits.min.x = bounding->cuboid.min.x;
				if (bounding->cuboid.max.x > root->limits.max.x)
					_hoops_SCAAR->limits.max.x = bounding->cuboid.max.x;
				if (upper < lower)
					index += 1;
			}
			else {
				if (upper > lower) {
					_hoops_SCAAR->limits.max.x = root->limits.min.x +
									 (root->limits.max.x - root->limits.min.x) /
											(0.5f+_hoops_RRIS);
				}
				else {
					_hoops_SCAAR->limits.min.x = root->limits.max.x -
									 (root->limits.max.x - root->limits.min.x) /
											(0.5f+_hoops_RRIS);
					index += 1;
				}
			}

			lower = root->limits.min.y - bounding->cuboid.min.y;
			upper = bounding->cuboid.max.y - root->limits.max.y;
			if (root->limits.min.y == root->limits.max.y) {
				if (bounding->cuboid.min.y < root->limits.min.y)
					_hoops_SCAAR->limits.min.y = bounding->cuboid.min.y;
				if (bounding->cuboid.max.y > root->limits.max.y)
					_hoops_SCAAR->limits.max.y = bounding->cuboid.max.y;
				if (upper < lower)
					index += 2;
			}
			else {
				if (upper > lower) {
					_hoops_SCAAR->limits.max.y = root->limits.min.y +
									 (root->limits.max.y - root->limits.min.y) /
											(0.5f+_hoops_RRIS);
				}
				else {
					_hoops_SCAAR->limits.min.y = root->limits.max.y -
									 (root->limits.max.y - root->limits.min.y) /
											(0.5f+_hoops_RRIS);
					index += 2;
				}
			}

			lower = root->limits.min.z - bounding->cuboid.min.z;
			upper = bounding->cuboid.max.z - root->limits.max.z;
			if (root->limits.min.z == root->limits.max.z) {
				if (bounding->cuboid.min.z < root->limits.min.z)
					_hoops_SCAAR->limits.min.z = bounding->cuboid.min.z;
				if (bounding->cuboid.max.z > root->limits.max.z)
					_hoops_SCAAR->limits.max.z = bounding->cuboid.max.z;
				if (upper < lower)
					index += 4;
			}
			else {
				if (upper > lower) {
					_hoops_SCAAR->limits.max.z = root->limits.min.z +
									 (root->limits.max.z - root->limits.min.z) /
											(0.5f+_hoops_RRIS);
				}
				else {
					_hoops_SCAAR->limits.min.z = root->limits.max.z -
									 (root->limits.max.z - root->limits.min.z) /
											(0.5f+_hoops_RRIS);
					index += 4;
				}
			}

			_hoops_SCAAR->_hoops_ICHSP[index] = root;
			root->_hoops_SCAAR = _hoops_SCAAR;
			_hoops_SHGCR->root = root = _hoops_SCAAR;

			if (root->limits._hoops_HPCIR(bounding->cuboid)) {
				/* _hoops_HIAAI _hoops_HA */
				root->_hoops_RCHS.Merge(bounding->cuboid);
				item->next = root->items;
				root->items = item;
				++root->count;
				break;
			}
		}
	}
}



local bool _hoops_SAGGC (
	_hoops_CRCP const *				_hoops_SRCP) {
	Attribute const *			_hoops_HPHCR;

	if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR))
		return true;

	if ((_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR) != null) do {
		if (_hoops_HPHCR->type > HK_CAMERA)
			break;
		if (_hoops_HPHCR->type == HK_CAMERA)
			return true;
	} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);

	return false;
}

local void _hoops_ARSHP (
	_hoops_AIGPR *		_hoops_RIGC,
	Display_Context const *		dc,
	_hoops_PGSGP alter *			_hoops_SHGCR,
	_hoops_CRCP const *				segment,
	_hoops_HICS const &		path,
	_hoops_ISGI const *	matrix,
	bool						_hoops_ARCAA,
	_hoops_PIGRA *			locks) {
	_hoops_ISGI *			_hoops_PIIAA;
	_hoops_PIGRA				_hoops_RGCAA;
	Subsegment const *			_hoops_SSGPR;

	_hoops_RSAI (locks, _hoops_PIGRA, &_hoops_RGCAA);

	_hoops_PIIAA = (_hoops_ISGI *)matrix;
	if (_hoops_PIIAA != null)
		_hoops_PRRH (_hoops_PIIAA);

	if (segment->_hoops_IPPGR != null) {
		Attribute const *		_hoops_HPHCR = segment->_hoops_IPPGR;
		_hoops_ACHR				_hoops_RGP = 0;

		do {
			if (_hoops_HPHCR->type >= HK_HEURISTICS) {
				if (_hoops_HPHCR->type == HK_HEURISTICS) {
					_hoops_GHAIR const *	_hoops_GIGC = (_hoops_GHAIR const *)_hoops_HPHCR;

					if (ANYBIT (_hoops_GIGC->mask & _hoops_GIGC->value, _hoops_HPIRP)) {
						if (_hoops_PIIAA != null)
							_hoops_HPRH (_hoops_PIIAA);
						return;
					}
				}
				break;
			}
		} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);

		HI_Accumulate_Bounding_Attributes (segment->_hoops_IPPGR,
							   _hoops_ARCAA ? &_hoops_PIIAA : null,
							   &_hoops_RGP, &_hoops_RGCAA, null, 0);
	}

	if (!segment->bounding._hoops_HICAR()) {
		Bounding		bounding = segment->bounding._hoops_SCIS (_hoops_PIIAA->matrix);

		_hoops_HAGGC (_hoops_SHGCR, _hoops_SHGCR->root, segment, path, bounding, 1);
	}

	if ((_hoops_SSGPR = segment->_hoops_RGRPR) != null) do {
		_hoops_CRCP const *		_hoops_SRCP;
		_hoops_HICS		_hoops_HHPIP = path;

		if (_hoops_SSGPR->type == _hoops_AGRPR) {
			_hoops_SRCP = ((_hoops_PGRPR *)_hoops_SSGPR)->_hoops_IGRPR;
			_hoops_HHPIP._hoops_IACHA ((_hoops_PGRPR *)_hoops_SSGPR, dc);
		}
		else
			_hoops_SRCP = (_hoops_CRCP const *)_hoops_SSGPR;


		if (!_hoops_SAGGC (_hoops_SRCP))
			_hoops_ARSHP (_hoops_RIGC, dc, _hoops_SHGCR, _hoops_SRCP, _hoops_HHPIP, _hoops_PIIAA, true, &_hoops_RGCAA);
	} while ((_hoops_SSGPR = _hoops_SSGPR->next) != null);

	if (_hoops_PIIAA != null)
		_hoops_HPRH (_hoops_PIIAA);
}

local void _hoops_GPGGC (
	_hoops_SASC const &	in,
	_hoops_SASC alter &	_hoops_PAGR) {

	Vector d = in.max - in.min;
	_hoops_PAGR = in;

	if (d.x >= d.y && d.x >= d.z) {
		_hoops_PAGR.max.y += (d.x - d.y);
		_hoops_PAGR.max.z += (d.x - d.z);
	}
	else if (d.y >= d.x && d.y >=d.z) {
		_hoops_PAGR.max.x += (d.y - d.x);
		_hoops_PAGR.max.z += (d.y - d.z);
	}
	else {
		_hoops_PAGR.max.x += (d.z - d.x);
		_hoops_PAGR.max.y += (d.z - d.y);
	}
}



local int _hoops_RPGGC (
	_hoops_HCHSP *				node,
	int						_hoops_IPHAP) {

  	if (node) {
		_hoops_IPHAP++;

		if (node->_hoops_ICHSP != null) {
			int				i;

			for (i=0; i<8; i++) {
				_hoops_HCHSP *		_hoops_HCPIH = node->_hoops_ICHSP[i];

				if (_hoops_HCPIH != null)
					_hoops_IPHAP = _hoops_RPGGC (_hoops_HCPIH, _hoops_IPHAP);
			}
		}
	}
	return _hoops_IPHAP;
}





local _hoops_PGSGP * _hoops_APGGC (
	Net_Rendition const &		nr,
	_hoops_CRCP const *				segment,
	_hoops_HICS const &		path,
	int							_hoops_GGISP,
	int							_hoops_RGISP) {
	_hoops_PGSGP *				_hoops_SHGCR = null;
	_hoops_HCHSP *					root  = null;

	ZALLOC (_hoops_SHGCR, _hoops_PGSGP);

	if (!nr->_hoops_IRR->_hoops_PCIRP)
		_hoops_SHGCR->_hoops_SSHSP = POOL_NEW(nr->_hoops_SRA->memory_pool, _hoops_CSHSP)(nr->_hoops_SRA->memory_pool);

	_hoops_SHGCR->_hoops_GGISP = _hoops_GGISP;
	_hoops_SHGCR->_hoops_RGISP = _hoops_RGISP;

	if (nr->_hoops_IRR->_hoops_PCIRP &&
		segment->bounding != null &&
		!segment->bounding._hoops_HICAR()) {

		Bounding	_hoops_PPGGC = segment->bounding;
		_hoops_SHGCR->_hoops_RCHS = _hoops_PPGGC->cuboid;

		ZALLOC (root, _hoops_HCHSP);

		root->limits = _hoops_PPGGC->cuboid;
		root->_hoops_RCHS = _hoops_PPGGC->cuboid;

		_hoops_GPGGC(_hoops_PPGGC->cuboid, root->limits);
		_hoops_GPGGC(_hoops_PPGGC->cuboid, root->_hoops_RCHS);

		_hoops_SHGCR->root = root;
	}
	else {
		_hoops_SHGCR->_hoops_RCHS.min = Point(MAX_FLOAT, MAX_FLOAT, MAX_FLOAT);
		_hoops_SHGCR->_hoops_RCHS.max = Point(-MAX_FLOAT, -MAX_FLOAT, -MAX_FLOAT);
	}

	_hoops_ISGI	matrix;
	matrix._hoops_HIHI = 999;
	HI_Copy_Matrix (&nr->transform_rendition->_hoops_IPH->data, &matrix.matrix);

	_hoops_PIGRA	locks;
	_hoops_RSAI (&nr->_hoops_IRR->locks, _hoops_PIGRA, &locks);

	_hoops_ARSHP (nr->_hoops_SRA->_hoops_RIGC, nr->_hoops_SRA,
					 _hoops_SHGCR, segment, path, &matrix, false, &locks);

	/* _hoops_IRHH _hoops_RCRR _hoops_IRHP _hoops_RIP _hoops_GCGSP */
	if (_hoops_SHGCR->root != null)
		_hoops_SHGCR->root->flags = 0;

	if (_hoops_SHGCR->_hoops_AGISP == 0.0f) {
		/* _hoops_CCIH _hoops_GH _hoops_PRCH */
		if (_hoops_SHGCR->root != null && root != 0) {
			_hoops_SHGCR->_hoops_RCHS = root->_hoops_RCHS;
		}
		else if (!nr->_hoops_IRR->_hoops_PCIRP) {
			_hoops_HCHSP *temp;
			_hoops_SHGCR->_hoops_SSHSP->ResetCursor();
			while ((temp = _hoops_SHGCR->_hoops_SSHSP->PeekCursor()) != null) {
				_hoops_SHGCR->_hoops_RCHS.Merge(temp->_hoops_RCHS);
				_hoops_SHGCR->_hoops_SSHSP->AdvanceCursor();
			}
		}
	}

	Vector	delta = _hoops_SHGCR->_hoops_RCHS.max - _hoops_SHGCR->_hoops_RCHS.min;

	_hoops_SHGCR->_hoops_AGISP = delta.length() * _hoops_IRGGC;

	return _hoops_SHGCR;
}



GLOBAL_FUNCTION _hoops_PGSGP * HD_Generate_Octree (
	Net_Rendition const &		nr,
	_hoops_CRCP const *				segment,
	_hoops_HICS const &		path) {
	_hoops_PGSGP *				_hoops_SHGCR = null;

	if (BIT (nr->_hoops_RCSHR, _hoops_CRSI)) {
		ZALLOC (_hoops_SHGCR, _hoops_PGSGP);	/* _hoops_RHPA _hoops_GGAGA */
	}
	else if (nr->_hoops_IRR->_hoops_PCIRP) {

		int	_hoops_GGISP = 1;
		int	_hoops_RGISP = 0;
		int	_hoops_IPHAP = 0;

		for (int i=0; i<=10; i++) {
			if (_hoops_SHGCR)
				HD_Delete_Octree (nr->_hoops_SRA->_hoops_RIGC, nr, _hoops_SHGCR);

			_hoops_SHGCR = _hoops_APGGC (nr, segment, path, _hoops_GGISP, _hoops_RGISP);

			if (_hoops_SHGCR->root) {
				_hoops_IPHAP = _hoops_RPGGC (_hoops_SHGCR->root,0);

				if (i == 0) {
					if (_hoops_IPHAP / _hoops_SRGGC < _hoops_GAGGC)
						_hoops_RGISP = _hoops_IPHAP/_hoops_SRGGC;
					else
						_hoops_RGISP = _hoops_GAGGC;

					_hoops_SHGCR->_hoops_RGISP = _hoops_RGISP;
				}

				if ((_hoops_IPHAP/(_hoops_RGISP + 1)) < _hoops_CRGGC)
					break;
			}
			else
				break;

			if (i == 0)
				_hoops_GGISP *= 2;
			else if (i == 1)
				_hoops_GGISP *= 4;
			else if (i > 1)
				_hoops_GGISP *= 8;
		}
	}
	else
		_hoops_SHGCR = _hoops_APGGC (nr, segment, path, 1, 10); /* 10 _hoops_HRGR _hoops_HPGGC */

	return _hoops_SHGCR;
}




local void _hoops_IPGGC (
	_hoops_AIGPR *		_hoops_RIGC,
	Net_Rendition const &		nr,
	_hoops_HCHSP *					node) {
	_hoops_PCHSP *				item;

 	if (node->_hoops_ICHSP != null) {
		for (int i=0; i<8; i++)
			if (node->_hoops_ICHSP[i] != null)
				_hoops_IPGGC (_hoops_RIGC, nr, node->_hoops_ICHSP[i]);

		FREE_ARRAY (node->_hoops_ICHSP, 8, _hoops_HCHSP *);
	}

	while ((item = node->items) != null) {
		_hoops_CRCP *				_hoops_SIIS = (_hoops_CRCP alter *)item->segment;
		{	// _hoops_CPSRR _hoops_IHAH _hoops_AAHS _hoops_GAR _hoops_ICPCA() _hoops_CAPP _hoops_GHCA _hoops_IGRC _hoops_HAGGR _hoops_CAGH
			_hoops_SPAGR				_hoops_GHAGR (_hoops_SIIS->_hoops_RHAGR, nr->_hoops_SRA->_hoops_RIGC->thread_id);
			_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (_hoops_SIIS, item->path, false);

			/* _hoops_ICIC _hoops_RPP _hoops_RH _hoops_IGCI _hoops_HRGR _hoops_CPSA _hoops_PCCP _hoops_HAGAR */
			_hoops_SIIS->_hoops_PHSI &= ~(_hoops_PCHGP|_hoops_ACHGP);
			if (_hoops_CSC != null) {
				_hoops_PIHGP			_hoops_CPGGC = _hoops_CSC->_hoops_SRSGP();

				_hoops_CSC->_hoops_CRSGP (_hoops_CPGGC & ~(_hoops_PCHGP|_hoops_ACHGP));
			}
		}

		_hoops_HPRH (_hoops_SIIS);
		item->path.release();

		node->items = item->next;
		FREE (item, _hoops_PCHSP);
	}

	if (node->_hoops_CCHSP != 0) {
		_hoops_GGAGR *				_hoops_SPGGC = (_hoops_GGAGR *)nr->_hoops_SRA->_hoops_GHRI;

		_hoops_HISAA (_hoops_RIGC, _hoops_SPGGC, _hoops_GHGGC, node->_hoops_CCHSP);
	}

	FREE (node, _hoops_HCHSP);
}


GLOBAL_FUNCTION void HD_Delete_Octree (
	_hoops_AIGPR *	_hoops_RIGC,
	Net_Rendition const &	nr,
	_hoops_PGSGP *			_hoops_SHGCR) 
{

	if (_hoops_SHGCR->_hoops_SSHSP) {
		_hoops_SHGCR->_hoops_SSHSP->ResetCursor();
		while (1) {
			_hoops_HCHSP *			temp = _hoops_SHGCR->_hoops_SSHSP->PeekCursor();

			if (!temp)
				break;

			_hoops_IPGGC (_hoops_RIGC, nr, temp);

			_hoops_SHGCR->_hoops_SSHSP->AdvanceCursor();
		}
		delete _hoops_SHGCR->_hoops_SSHSP;
	}
	else if (_hoops_SHGCR->root)
		_hoops_IPGGC(_hoops_RIGC, nr, _hoops_SHGCR->root);

	FREE (_hoops_SHGCR, _hoops_PGSGP);
}


local void _hoops_RHGGC (
	Net_Rendition const &		nr,
	_hoops_HCHSP *					node) {
	_hoops_PCHSP *				item;

	if (node->_hoops_ICHSP != null) {
		int						i;

		for (i=0; i<8; i++)
			if (node->_hoops_ICHSP[i] != null)
				_hoops_RHGGC (nr, node->_hoops_ICHSP[i]);
	}

	if ((item = node->items) != null) do {
		_hoops_CRCP *				_hoops_SIIS = (_hoops_CRCP alter *)item->segment;
		_hoops_SPAGR					_hoops_GHAGR (_hoops_SIIS->_hoops_RHAGR, nr->_hoops_SRA->_hoops_RIGC->thread_id);
		_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (_hoops_SIIS, item->path, false);

		/* _hoops_ICIC _hoops_RPP _hoops_RH _hoops_IGCI _hoops_HRGR _hoops_CPSA _hoops_PCCP _hoops_HAGAR */
		_hoops_SIIS->_hoops_PHSI &= ~(_hoops_PCHGP|_hoops_ACHGP);
		if (_hoops_CSC != null) {
			_hoops_PIHGP			_hoops_CPGGC = _hoops_CSC->_hoops_SRSGP();

			_hoops_CSC->_hoops_CRSGP (_hoops_CPGGC & ~(_hoops_PCHGP|_hoops_ACHGP));
		}
	} while ((item = item->next) != null);

	if (node->_hoops_CCHSP != 0) {
		_hoops_CACGH (nr, node->_hoops_CCHSP);
		node->_hoops_CCHSP = null;
	}
}

GLOBAL_FUNCTION void HD_Flush_Octree_Queries (
	Net_Rendition const &		nr,
	_hoops_CRCP const *				_hoops_SRCP) {

	if (nr == null)
		return;

	{
		_hoops_AIGPR *	_hoops_RIGC = nr->_hoops_SRA->_hoops_RIGC;
		if (_hoops_RIGC == null)
			_hoops_IIRIR(_hoops_RIGC);

		_hoops_SPAGR					_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, _hoops_RIGC->thread_id);
		_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, false);

		if (_hoops_CSC != null) {
			_hoops_PGSGP *		_hoops_AHGGC = _hoops_CSC->_hoops_IGSGP();

			if (_hoops_AHGGC != null && _hoops_AHGGC->root != 0)
				_hoops_RHGGC (nr, _hoops_AHGGC->root);
		}
	}

	Subsegment const *			_hoops_SSGPR;
	if ((_hoops_SSGPR = _hoops_SRCP->_hoops_RGRPR) != null) do {
		_hoops_CRCP const *			_hoops_SRCP = null;

		if (_hoops_SSGPR->type == _hoops_AGRPR)
			_hoops_SRCP = ((_hoops_PGRPR const *)_hoops_SSGPR)->_hoops_IGRPR;
		else
			_hoops_SRCP = (_hoops_CRCP const *)_hoops_SSGPR;

		if (_hoops_SRCP != null) {
			HD_Flush_Octree_Queries (nr, _hoops_SRCP);
		}
	} while ((_hoops_SSGPR = _hoops_SSGPR->next) != null);
}


local void _hoops_PHGGC (
	HThreadID			thread_id,
	_hoops_HCHSP *			node,
	Integer32			flags) {
	_hoops_PCHSP *		item = node->items;
	_hoops_HCHSP *			_hoops_SCAAR = node->_hoops_SCAAR;

	if (ALLBITS (node->flags, flags))
		return;

	node->flags |= flags;

	if (item != null) do {
		_hoops_CRCP *				_hoops_SIIS = (_hoops_CRCP alter *)item->segment;
		_hoops_SPAGR					_hoops_GHAGR (_hoops_SIIS->_hoops_RHAGR, thread_id);
		_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (_hoops_SIIS, item->path);
		_hoops_PIHGP				_hoops_CPGGC = _hoops_CSC->_hoops_SRSGP();

		_hoops_SIIS->_hoops_PHSI |= flags;
		_hoops_CSC->_hoops_CRSGP (_hoops_CPGGC | flags);
	} while ((item = item->next) != null);

	if (node->_hoops_ICHSP != null) {
		int				i;

		node->flags |= _hoops_PSHSP;
		for (i=0; i<8; i++)
			if (node->_hoops_ICHSP[i] != null)
				_hoops_PHGGC (thread_id, node->_hoops_ICHSP[i], flags);
	}

	while (_hoops_SCAAR != null && !BIT (_hoops_SCAAR->flags, _hoops_PSHSP)) {
		_hoops_SCAAR->flags |= _hoops_PSHSP;
		_hoops_SCAAR = _hoops_SCAAR->_hoops_SCAAR;
	}
}

local void _hoops_HHGGC (
	HThreadID			thread_id,
	_hoops_HCHSP *			node) {

	if (!ANYBIT (node->flags,
				 _hoops_ASHSP|_hoops_RSHSP|_hoops_PSHSP))
		return;

	if (node->items != null &&
		ANYBIT (node->flags, _hoops_ASHSP|_hoops_RSHSP)) {
		_hoops_PCHSP *		item = node->items;

		do {
			_hoops_CRCP *				_hoops_SIIS = (_hoops_CRCP alter *)item->segment;
			_hoops_SPAGR					_hoops_GHAGR (_hoops_SIIS->_hoops_RHAGR, thread_id);
			_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (_hoops_SIIS, item->path, false);

			/* _hoops_ICIC _hoops_RPP _hoops_RH _hoops_IGCI _hoops_HRGR _hoops_CPSA _hoops_PCCP _hoops_HAGAR */
			_hoops_SIIS->_hoops_PHSI &= ~(_hoops_PCHGP|_hoops_ACHGP);
			if (_hoops_CSC != null) {
				_hoops_PIHGP			_hoops_CPGGC = _hoops_CSC->_hoops_SRSGP();

				_hoops_CSC->_hoops_CRSGP (_hoops_CPGGC & ~(_hoops_PCHGP|_hoops_ACHGP));
			}
		} while ((item = item->next) != null);
	}

	if (node->_hoops_ICHSP != null &&
		BIT (node->flags, _hoops_PSHSP)) {
		int						i;

		for (i=0; i<8; i++)
			if (node->_hoops_ICHSP[i] != null)
				_hoops_HHGGC (thread_id, node->_hoops_ICHSP[i]);
	}

	node->flags &= ~(_hoops_ASHSP|_hoops_RSHSP|_hoops_PSHSP);
}


local int _hoops_IAIGA[] = { 0, 1, 2, 3, 6, 7, 4, 5,
							2, 6, 0, 4, 1, 5, 3, 7 };
local int _hoops_IHGGC[] = { 8, 8 };


#if _hoops_CGGGC
local int _hoops_CHGGC[] = { 0, 1, 3, 2, 0,
							4, 5, 7, 6, 4,
							0, 4,  1, 5,  2, 6,	 3, 7 };
local int _hoops_SHGGC[]	= { 0, 0, 1, 2, 3,
							0, 4, 5, 6, 7,
							0, 8,  0, 9,  0, 10,  0, 11 };
local int _hoops_GIGGC[] = { 5, 5, 2, 2, 2, 2 };
#endif


local void _hoops_RIGGC (
	Net_Rendition const &		nr,
	_hoops_PGSGP	 *				_hoops_SHGCR,
	_hoops_HCHSP *					node,
	int							level) {

 	if (level > _hoops_ARGGC && !_hoops_SHGCR->_hoops_SSHSP)
		return;

	if (level >= _hoops_RRGGC || _hoops_SHGCR->_hoops_SSHSP) {
		_hoops_HHCR const &		_hoops_IHCR = nr->transform_rendition;
		HThreadID						thread_id = nr->_hoops_SRA->_hoops_RIGC->thread_id;
		Test							result = _hoops_GAAGI;

		if (BIT (_hoops_IHCR->_hoops_APH, Heur_Culling_VIEW_FRUSTUM) &&
			!BIT (_hoops_IHCR->flags, _hoops_AIHS)) {


			// _hoops_PASC ???
#if 0

			/* _hoops_SIGP: _hoops_CR _hoops_SCHSP _hoops_HRGR _hoops_GSSP _hoops_GC, _hoops_SIAS _hoops_SHH _hoops_SHSS _hoops_IS _hoops_AA _hoops_IRS _hoops_RPGS _hoops_RPGP
			** _hoops_HPP _hoops_SCACP _hoops_RHCH _hoops_IIGR _hoops_IRS _hoops_GIIS _hoops_RHIR _hoops_SARA _hoops_RIHCR (_hoops_PAHH
			** _hoops_CCA _hoops_PCCP _hoops_SRPA _hoops_SSH _hoops_HIS _hoops_RHC _hoops_HRGR _hoops_HPGR _hoops_CGRS) _hoops_PPR _hoops_PCR _hoops_GCPPR _hoops_CHHRR
			** _hoops_ACSRR _hoops_RH _hoops_PSCR-_hoops_IHGP _hoops_SARA,
			*/

			int			_hoops_AIGGC;

			if (nr->_hoops_IRR->_hoops_CIIRP != 20)
				_hoops_AIGGC = nr->_hoops_IRR->_hoops_GRGC;
			else
				_hoops_AIGGC = 0;
#endif
			float _hoops_RRIIH = nr->_hoops_SAIR->_hoops_HHCAR.left - nr->transform_rendition->_hoops_AGAA.left;

			HD_Transform_And_Test_Simple_Cuboid (nr, 1, &node->_hoops_RCHS, _hoops_RRIIH, 0.0f, &result, null, null);
		}

		_hoops_HHRA const *	_hoops_SPH = _hoops_IHCR->_hoops_SPH;
		Vector			delta = _hoops_SPH->position - _hoops_AICIR(node->_hoops_RCHS.max, node->_hoops_RCHS.min);
		float			length = delta.length();

		if (result == Test_DISJOINT) {
			/* _hoops_HAR _hoops_GGR _hoops_AHC _hoops_IS _hoops_RACGH */
			if (length <= _hoops_SHGCR->_hoops_AGISP)
				_hoops_PHGGC (thread_id, node, _hoops_PCHGP);
			else
				_hoops_PHGGC (thread_id, node, _hoops_ACHGP);

			node->_hoops_HSHSP = 0;
			node->_hoops_ISHSP = 0;
		}
		else if (BIT (result, Test_EXTENT)) {
 			_hoops_PHGGC (thread_id, node, _hoops_ACHGP);

			node->_hoops_HSHSP =  _hoops_SHGCR->_hoops_RGISP + URANDOM() % (_hoops_SHGCR->_hoops_RGISP + 1);
			node->_hoops_ISHSP =  _hoops_SHGCR->_hoops_RGISP + URANDOM() % (_hoops_SHGCR->_hoops_RGISP + 1);
		}
		else if (node->_hoops_RCHS._hoops_HPCIR(_hoops_SPH->position)) {
			/* _hoops_IAGP _hoops_RPGP _hoops_HAR _hoops_ICPRA _hoops_RPP _hoops_SARA _hoops_ASSA _hoops_AHCRR */
			node->_hoops_HSHSP = 0;
			node->_hoops_ISHSP = 0;
		}
		else if (1 || result == _hoops_GAAGI || length > _hoops_SHGCR->_hoops_AGISP) {
			if (node->_hoops_HSHSP >= 1 && result == _hoops_GAAGI) {
				_hoops_PHGGC (thread_id, node, _hoops_ACHGP);	/* _hoops_HAR _hoops_GGR _hoops_AHC _hoops_IS _hoops_RACGH */
				node->_hoops_HSHSP--;
			}
			else if (node->_hoops_ISHSP >= 1) {
 				node->_hoops_ISHSP--;
			}
			else {
				Point		box[8];
				node->_hoops_RCHS._hoops_GPSC(&box[0]);

				Tristrip *	tristrip;
 				ZALLOC (tristrip, Tristrip);
				_hoops_ICAI (tristrip);

				tristrip->_hoops_SRHA = _hoops_SRHH;

				tristrip->points = box;
				tristrip->point_count = 8;
				tristrip->face_count = 6;

				tristrip->_hoops_PHHA = 2;
				ALLOC_ARRAY(tristrip->lengths, 2, int);
				_hoops_AIGA(_hoops_IHGGC, 2, int, tristrip->lengths);
				tristrip->lengths_allocated = 2;

				ALLOC_ARRAY(tristrip->_hoops_AIHA, 16, int);
				_hoops_AIGA(_hoops_IAIGA, 16, int, tristrip->_hoops_AIHA);
				tristrip->_hoops_IPII = 16;

				tristrip->_hoops_RAHH |= _hoops_AAHH;

 				tristrip->total = 16;


				Polyedge *	polyedge;
				ZALLOC (polyedge, Polyedge);
				_hoops_ICAI (polyedge);

				polyedge->_hoops_SRHA = _hoops_SRHH;

				polyedge->points = box;
				polyedge->point_count = 8;
				polyedge->_hoops_SPHA = 1;

				polyedge->_hoops_PHHA = 1;
				ALLOC_ARRAY(polyedge->lengths, 1, int);
				polyedge->lengths[0] = 2;
				polyedge->lengths_allocated = 1;

				ALLOC_ARRAY(polyedge->_hoops_AIHA, 2, int);
				polyedge->_hoops_AIHA[0] = 0;
				polyedge->_hoops_AIHA[1] = 7;	// _hoops_PIP: _hoops_IRHAP _hoops_GPP _hoops_AGR _hoops_HRCRA _hoops_HII _hoops_PIGGC
				polyedge->_hoops_IPII = 2;

				polyedge->_hoops_RAHH |= _hoops_AAHH;

 				polyedge->total = 2;


				node->_hoops_CCHSP = _hoops_AACGH (nr, true);
				_hoops_HPHCP (nr, tristrip);
				_hoops_RAIGH (nr, polyedge);
				_hoops_PACGH (nr, node->_hoops_CCHSP);

 				if (_hoops_ISAI (tristrip) == 0)
					HI_Free_Tristrip (tristrip);
 				if (_hoops_ISAI (polyedge) == 0)
					HI_Free_Polyedge (polyedge);

#if _hoops_CGGGC
				{
					Polyedge		pe;
					RGB				colors[8];
					int				i;

					ZERO_STRUCT (&pe, Polyedge);
					pe._hoops_SRHA = _hoops_SRHH;

					pe.points = box;
					pe.point_count = 8;
					pe._hoops_SPHA = 12;

					pe._hoops_PHHA = 6;
					pe.lengths = _hoops_GIGGC;
					pe._hoops_AIHA = _hoops_CHGGC;
					pe._hoops_SPII = _hoops_SHGGC;

					ZERO_ARRAY (colors, 8, RGB);
					if (_hoops_ARGGC != _hoops_RRGGC) {
						for (i=0; i<8; i++) {
							colors[i].red = (level-2) * 1.0f/(_hoops_ARGGC-_hoops_RRGGC);
							colors[i].blue = 1.0f - colors[i].red;
						}
					}
					pe._hoops_PCHA = colors;
					/* _hoops_HRRRA->_hoops_PRRRA _hoops_HASGA _hoops_PRCH */
					_hoops_RAIGH (nr, &pe);


					for (i=0; i<8; i++) {
						box[i].x = (i & 1) ? node->limits.max.x : node->limits.min.x;
						box[i].y = (i & 2) ? node->limits.max.y : node->limits.min.y;
						box[i].z = (i & 4) ? node->limits.max.z : node->limits.min.z;
					}
					ZERO_ARRAY (colors, 8, RGB);
					if (_hoops_ARGGC != _hoops_RRGGC) {
						for (i=0; i<8; i++) {
							colors[i].green = (level-2) * 1.0f/(_hoops_ARGGC-_hoops_RRGGC);
						}
					}
					/* _hoops_APRP->_hoops_ASSAA _hoops_GIIS _hoops_PCSRR */
					_hoops_RAIGH (nr, &pe);
				}
#endif
			}
		}
		else {
			node->_hoops_HSHSP = 0;
			node->_hoops_ISHSP = 0;
		}
	}
	if (node->items != null || _hoops_HRGGC)
		++level;

	if (_hoops_SHGCR->_hoops_SSHSP == null) {
		if (node->_hoops_ICHSP != null) {
			for (int i=0; i<8; i++) {
				if (node->_hoops_ICHSP[i])
					_hoops_RIGGC (nr, _hoops_SHGCR, node->_hoops_ICHSP[i], level);
			}
		}
	}
}


GLOBAL_FUNCTION void HD_Process_Deferred_Octrees(Display_Context alter * dc)
{

	while (dc->_hoops_PPSIP != null) {
		_hoops_PGISP *		_hoops_HIGGC = dc->_hoops_PPSIP;

		dc->_hoops_PPSIP = _hoops_HIGGC->next;

		HD_Send_Queries (_hoops_HIGGC->nr, _hoops_HIGGC->_hoops_HGISP);
		_hoops_HIGGC->nr.release();
		FREE (_hoops_HIGGC, _hoops_PGISP);
	}
}


GLOBAL_FUNCTION void HD_Send_Queries (
	Net_Rendition const &		inr,
	_hoops_PGSGP *				_hoops_SHGCR) {
	Net_Rendition				nr = inr;
	_hoops_HCHSP *					root = 0;

	if (_hoops_SHGCR) {
		if (_hoops_SHGCR->_hoops_SSHSP) {
			_hoops_SHGCR->_hoops_SSHSP->ResetCursor();
			root = _hoops_SHGCR->_hoops_SSHSP->PeekCursor();
		}
		else
			root = _hoops_SHGCR->root;
	}
	if (root == null)
		return;
 	/* _hoops_ARP _hoops_GH _hoops_IHGP _hoops_SRGH _hoops_GSSP _hoops_IH _hoops_ASCA/_hoops_HHCPR _hoops_PRCH */
	if (ANYBIT (nr->transform_rendition->flags,
				_hoops_PRIR|_hoops_GRHH|_hoops_IGSP) ||
		ANYBIT (nr->transform_rendition->_hoops_IPH->data._hoops_RAGR,
				_hoops_CICH) || !BIT(nr->transform_rendition->flags, _hoops_ISH)) {
		_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

		_hoops_GGCC->flags &= ~(_hoops_PRIR|_hoops_GRHH|_hoops_IGSP);
		_hoops_GGCC->flags |= _hoops_ISH;

		_hoops_GGCC->_hoops_IPH = _hoops_SGCC::Create (nr->_hoops_SRA);

		HD_Redo_Screen (nr, &((_hoops_HHRA alter *)_hoops_GGCC->_hoops_SPH)->_hoops_GRCC);
	}

	if (_hoops_SHGCR->_hoops_SSHSP) {
		_hoops_SHGCR->_hoops_SSHSP->ResetCursor();
		while (1) {
			_hoops_HCHSP *temp = _hoops_SHGCR->_hoops_SSHSP->PeekCursor();
			if (!temp)
				break;
			_hoops_HHGGC(nr->_hoops_SRA->_hoops_RIGC->thread_id, temp);
			_hoops_RIGGC(nr, _hoops_SHGCR, temp, 1);
			_hoops_SHGCR->_hoops_SSHSP->AdvanceCursor();
		}
		_hoops_SHGCR->_hoops_SSHSP->ResetCursor();
	}
	else {
		_hoops_HHGGC (nr->_hoops_SRA->_hoops_RIGC->thread_id, root);
		_hoops_RIGGC (nr, _hoops_SHGCR, root, 1);
	}
}




local void _hoops_IIGGC (
	Net_Rendition const &		nr,
	_hoops_PGSGP *				_hoops_SHGCR,
	_hoops_HCHSP *					node,
	int							level) {

	if (level > _hoops_ARGGC && !_hoops_SHGCR->_hoops_SSHSP)
		return;

	if (node->_hoops_CCHSP != null) {
		if (_hoops_IACGH (nr, node->_hoops_CCHSP) <= nr->_hoops_IRR->_hoops_ACIRP) {
			_hoops_PHGGC (nr->_hoops_SRA->_hoops_RIGC->thread_id, node, _hoops_ACHGP);
			if (_hoops_SHGCR->_hoops_RGISP)
				node->_hoops_HSHSP = _hoops_SHGCR->_hoops_RGISP + URANDOM() % (_hoops_SHGCR->_hoops_RGISP + 1);
			else
				node->_hoops_HSHSP = 0;
			node->_hoops_ISHSP = 0;
		}
		else {
			node->_hoops_HSHSP = 0;
			if (_hoops_SHGCR->_hoops_RGISP)
				node->_hoops_ISHSP = _hoops_SHGCR->_hoops_RGISP + URANDOM() % (_hoops_SHGCR->_hoops_RGISP + 1);
			else
				node->_hoops_ISHSP = 0;
		}

		node->_hoops_CCHSP = null;
	}

	if (node->items != null || _hoops_HRGGC)
		++level;
	if (_hoops_SHGCR->_hoops_SSHSP) {
		_hoops_HCHSP *		temp;

		_hoops_SHGCR->_hoops_SSHSP->AdvanceCursor();
		temp = _hoops_SHGCR->_hoops_SSHSP->PeekCursor();
		if (temp)
			_hoops_IIGGC (nr, _hoops_SHGCR, temp, level);
	}
	else {
		if (node->_hoops_ICHSP != null) {
			int				i;

			for (i=0; i<8; i++) {
				_hoops_HCHSP *		_hoops_HCPIH = node->_hoops_ICHSP[i];

				if (_hoops_HCPIH != null)
					_hoops_IIGGC (nr, _hoops_SHGCR, _hoops_HCPIH, level);
			}
		}
	}
}

GLOBAL_FUNCTION void HD_Process_Queries (
	Net_Rendition const &		nr,
	_hoops_PGSGP *				_hoops_SHGCR) {
	_hoops_HCHSP *					root = null;

	if (_hoops_SHGCR) {
		if (_hoops_SHGCR->_hoops_SSHSP) {
			_hoops_SHGCR->_hoops_SSHSP->ResetCursor();
			root = _hoops_SHGCR->_hoops_SSHSP->PeekFirst();
		}
		else
			root = _hoops_SHGCR->root;
	}

	if (root == null)
		return;
	_hoops_IIGGC (nr, _hoops_SHGCR, root, 1);
}

#endif

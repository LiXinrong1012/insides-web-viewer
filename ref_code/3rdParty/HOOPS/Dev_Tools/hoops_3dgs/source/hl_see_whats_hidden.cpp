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
 * $Id: obf_tmp.txt 1.166 2010-12-06 22:05:40 jason Exp $
 */

#include "hoops.h"

#ifndef _hoops_IRRHP

#include "database.h"
#include "driver.h"
#include "patterns.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hc_proto.h"
#include "hidden.h"
#include "hpserror.h"
#include "hl.h"

#include <stdio.h>

#define _hoops_RAAHR (0.0001)		/* _hoops_AASC _hoops_SIPSH _hoops_III _hoops_GCPSH _hoops_CGH _hoops_SHH 2/_hoops_RAAA */
#define _hoops_RCPSH (1.0e-15)	// _hoops_CIAS _hoops_AHCR _hoops_IHSR _hoops_HIHHR _hoops_IIGR _hoops_PCCP _hoops_ISHA-_hoops_GPP _hoops_IPPA

#define _hoops_ACPSH 16
#define _hoops_PCPSH 16

local _hoops_AGASH * _hoops_HCPSH (
	_hoops_SGSGP	alter * data,
	float xmin, float xmax,
	float ymin, float ymax,
	unsigned long level) {

	_hoops_AGASH	alter * node;

	ZALLOC (node, _hoops_AGASH);

	node->level=level;

	node->xmin = xmin;
	node->xmax = xmax;
	node->ymin = ymin;
	node->ymax = ymax;

	node->next = data->_hoops_HGASH;
	data->_hoops_HGASH = node;

	return node;
}

#define _hoops_ICPSH 0
#define _hoops_CCPSH 0

#if _hoops_ICPSH
local void _hoops_SCPSH (
	_hoops_AGASH	alter * node) {

	printf ("\n");
	if (!node->_hoops_ICHSP) printf ("leaf node\n");
	printf ("level: %lu\n", node->level);
	printf ("count: %lu\n", node->count);
	printf ("xmin: %f\n", node->xmin);
	printf ("xmax: %f\n", node->xmax);
	printf ("ymin: %f\n", node->ymin);
	printf ("ymax: %f\n", node->ymax);
}
#elif _hoops_CCPSH
local void _hoops_SCPSH (
	_hoops_AGASH	alter * node) {
	static int first=1;

	if (first) {
		float r,g,b;
		printf (";; HMF V1.24 TEXT");
		r=1.0f; g=0.0f; b=0.0f;
		printf ("(Segment \"red\" ((Color_By_Value \"Line\" \"RGB\" %f %f %f)))", r,g,b);
		r=0.0f; g=1.0f; b=0.0f;
		printf ("(Segment \"green\" ((Color_By_Value \"Line\" \"RGB\" %f %f %f)))", r,g,b);
		r=0.0f; g=0.0f; b=1.0f;
		printf ("(Segment \"blue\" ((Color_By_Value \"Line\" \"RGB\" %f %f %f)))", r,g,b);
		first=0;
	}

	if (!node->count) {
		printf ("(Segment \"blue\" (");
	}
	else if (node->count>_hoops_ACPSH) {
		printf ("(Segment \"red\" (");
	}
	else {
		printf ("(Segment \"green\" (");
	}

	printf ("(Polyline ((%f %f %f) (%f %f %f) (%f %f %f) (%f %f %f) (%f %f %f)))))\n",
		node->xmin, node->ymin, (float)node->level*100.0f,
		node->xmin, node->ymax, (float)node->level*100.0f,
		node->xmax, node->ymax, (float)node->level*100.0f,
		node->xmax, node->ymin, (float)node->level*100.0f,
		node->xmin, node->ymin, (float)node->level*100.0f);
}
#else
#define _hoops_SCPSH(x)
#endif

#if 0
local void _hoops_GSPSH(const char *filename, _hoops_CCRSH *list)
{
	FILE *file = fopen(filename,"wb");

	int count = 0;

	_hoops_CCRSH *_hoops_HARIR = list;
	while (_hoops_HARIR != null) {
		_hoops_PCRSH *line = &_hoops_HARIR->_hoops_PICHR[0];

		fprintf(file, "line: %f\n",_hoops_HARIR->_hoops_PICHR[0].points[0].z);
		++count;
		_hoops_HARIR = _hoops_HARIR->next;
	}

	fprintf(file,"printed %i lines",count);

	fclose(file);
}
#endif

template< typename T, bool _hoops_RSPSH(T,T) >
INLINE local T _hoops_ASPSH(T list)
{
	int		_hoops_PSPSH = 1;
	T		p, tail, e, q;
	int		_hoops_HSPSH, _hoops_ISPSH;
	int		_hoops_CSPSH;

	for (;;) {
		_hoops_CSPSH = 0;

		p		= list;
		list	= null;
		tail	= null;

		while (p) {
			++_hoops_CSPSH;
			q = p;
			_hoops_HSPSH = 0;

			while (_hoops_HSPSH < _hoops_PSPSH && q != null)	{
				++_hoops_HSPSH;
				q = q->next;
			}

			_hoops_ISPSH = _hoops_PSPSH;

			while (_hoops_HSPSH > 0 || (_hoops_ISPSH > 0 && q != null)) {
				e = null;

				if (_hoops_HSPSH == 0)	{
					e = q;
					q = q->next;
					--_hoops_ISPSH;
				}
				else if (_hoops_ISPSH == 0 || q == null) {
					e = p;
					p = p->next;
					--_hoops_HSPSH;
				}
				else if (_hoops_RSPSH(q,p)) {
					e = p;
					p = p->next;
					--_hoops_HSPSH;
				}
				else {
					e = q;
					q = q->next;
					--_hoops_ISPSH;
				}


				if (tail)
					tail->next = e;
				else
					list = e;

				tail = e;
			}

			p = q;
		}

		tail->next = null;

		if (_hoops_CSPSH <= 1)
			break;

		_hoops_PSPSH *= 2;
	}

	return list;
}


local void _hoops_SSPSH(_hoops_AGASH	alter *node, _hoops_RGASH const *bounding)
{
	if (node->xmin>bounding->xmin) node->xmin = bounding->xmin;
	if (node->xmax<bounding->xmax) node->xmax = bounding->xmax;
	if (node->ymin>bounding->ymin) node->ymin = bounding->ymin;
	if (node->ymax<bounding->ymax) node->ymax = bounding->ymax;
	node->_hoops_PGASH[node->count].xmin = bounding->xmin;
	node->_hoops_PGASH[node->count].xmax = bounding->xmax;
	node->_hoops_PGASH[node->count].ymin = bounding->ymin;
	node->_hoops_PGASH[node->count].ymax = bounding->ymax;
	node->_hoops_PGASH[node->count]._hoops_RCHHR = bounding->_hoops_RCHHR;
	node->_hoops_PGASH[node->count].offset = bounding->offset;
	node->count++;
}

#ifdef _hoops_GGHSH
// _hoops_SAP _hoops_PSAP _hoops_CHCRA _hoops_IH _hoops_RGR _hoops_SPR _hoops_API.  _hoops_IPCP _hoops_AARRA _hoops_IIGR _hoops_ICSI _hoops_SAPS _hoops_PPSR
// _hoops_PPR _hoops_RISA _hoops_IGIR _hoops_CHCRA _hoops_HRGR _hoops_RIHGH _hoops_RGR _hoops_API _hoops_IS _hoops_SCCHH _hoops_GGR _hoops_PCHC _hoops_RGHSH.
#pragma optimize("", off)
#endif

local void _hoops_AGHSH (
	_hoops_SGSGP				alter * data,
	_hoops_AGASH	alter * node) {

	_hoops_RGASH alter	*_hoops_PGASH;
	_hoops_AGASH	alter	*_hoops_PGHSH,*_hoops_HGHSH,*_hoops_IGHSH,*_hoops_CGHSH,*_hoops_SGHSH;
	unsigned int _hoops_GRHSH, _hoops_RRHSH, _hoops_ARHSH, _hoops_PRHSH, _hoops_HRHSH;
	float _hoops_IRHSH, _hoops_CRHSH, _hoops_SRHSH, _hoops_GAHSH;
	unsigned int i, count;
	float _hoops_RPIS;

	if (node->count < _hoops_ACPSH || node->level >= _hoops_PCPSH) {
		_hoops_SCPSH(node);
		return;
	}

	_hoops_RPIS = node->xmax - node->xmin;
	_hoops_IRHSH = _hoops_RPIS*0.3f + node->xmin;
	_hoops_CRHSH = _hoops_RPIS*0.7f + node->xmin;

	_hoops_RPIS = node->ymax - node->ymin;
	_hoops_SRHSH = _hoops_RPIS*0.3f + node->ymin;
	_hoops_GAHSH = _hoops_RPIS*0.7f + node->ymin;

	_hoops_GRHSH = _hoops_RRHSH = _hoops_ARHSH = _hoops_PRHSH = _hoops_HRHSH = 0;

	_hoops_PGHSH = _hoops_HGHSH = _hoops_IGHSH = _hoops_CGHSH = _hoops_SGHSH = 0;

	_hoops_PGASH = node->_hoops_PGASH;
	count = node->count;

	node->_hoops_PGASH=0;
	node->count=0;

	i = 0;
	while (i < count) {
		if (_hoops_PGASH[i].xmin > _hoops_IRHSH) {
			if (_hoops_PGASH[i].ymin > _hoops_SRHSH)
				_hoops_RRHSH++;
			else if (_hoops_PGASH[i].ymax <= _hoops_GAHSH)
				_hoops_ARHSH++;
			else
				_hoops_GRHSH++;
		}
		else if (_hoops_PGASH[i].xmax <= _hoops_CRHSH) {
			if (_hoops_PGASH[i].ymin > _hoops_SRHSH)
				_hoops_PRHSH++;
			else if (_hoops_PGASH[i].ymax <= _hoops_GAHSH)
				_hoops_HRHSH++;
			else
				_hoops_GRHSH++;
		}
		else
			_hoops_GRHSH++;

		i++;
	}


	if (_hoops_PRHSH) {
		_hoops_IGHSH = _hoops_HCPSH (data, node->xmin, _hoops_CRHSH, _hoops_SRHSH, node->ymax, node->level+1);
		ALLOC_ARRAY_CACHED (_hoops_IGHSH->_hoops_PGASH, _hoops_PRHSH, _hoops_RGASH);

		node->_hoops_ICHSP = _hoops_IGHSH;
		_hoops_IGHSH->_hoops_GHIIP = node->_hoops_GHIIP;
	}

	if (_hoops_HRHSH) {
		_hoops_CGHSH = _hoops_HCPSH (data, node->xmin, _hoops_CRHSH, node->ymin, _hoops_GAHSH, node->level+1);
		ALLOC_ARRAY_CACHED (_hoops_CGHSH->_hoops_PGASH, _hoops_HRHSH, _hoops_RGASH);

		if (!node->_hoops_ICHSP)
			_hoops_CGHSH->_hoops_GHIIP = node->_hoops_GHIIP;
		else
			_hoops_CGHSH->_hoops_GHIIP = node->_hoops_ICHSP;
		node->_hoops_ICHSP = _hoops_CGHSH;
	}

	if (_hoops_ARHSH) {
		_hoops_HGHSH = _hoops_HCPSH (data, _hoops_IRHSH, node->xmax, node->ymin, _hoops_GAHSH, node->level+1);
		ALLOC_ARRAY_CACHED (_hoops_HGHSH->_hoops_PGASH, _hoops_ARHSH, _hoops_RGASH);

		if (!node->_hoops_ICHSP)
			_hoops_HGHSH->_hoops_GHIIP = node->_hoops_GHIIP;
		else
			_hoops_HGHSH->_hoops_GHIIP = node->_hoops_ICHSP;
		node->_hoops_ICHSP = _hoops_HGHSH;
	}

	if (_hoops_RRHSH) {
		_hoops_PGHSH = _hoops_HCPSH (data, _hoops_IRHSH, node->xmax, _hoops_SRHSH, node->ymax, node->level+1);
		ALLOC_ARRAY_CACHED (_hoops_PGHSH->_hoops_PGASH, _hoops_RRHSH, _hoops_RGASH);

		if (!node->_hoops_ICHSP)
			_hoops_PGHSH->_hoops_GHIIP = node->_hoops_GHIIP;
		else
			_hoops_PGHSH->_hoops_GHIIP = node->_hoops_ICHSP;
		node->_hoops_ICHSP = _hoops_PGHSH;
	}

	if (_hoops_GRHSH) {
		_hoops_SGHSH = _hoops_HCPSH (data, MAX_FLOAT, -MAX_FLOAT, MAX_FLOAT, -MAX_FLOAT, node->level+1);

		ALLOC_ARRAY_CACHED (_hoops_SGHSH->_hoops_PGASH, _hoops_GRHSH, _hoops_RGASH);

		if (!node->_hoops_ICHSP)
			_hoops_SGHSH->_hoops_GHIIP = node->_hoops_GHIIP;
		else
			_hoops_SGHSH->_hoops_GHIIP = node->_hoops_ICHSP;

		node->_hoops_ICHSP = _hoops_SGHSH;
	}

	i = 0;
	while (i<count) {
		if (_hoops_PGASH[i].xmin > _hoops_IRHSH) {
			if (_hoops_PGASH[i].ymin > _hoops_SRHSH)
				_hoops_SSPSH(_hoops_PGHSH, &_hoops_PGASH[i]);
			else if (_hoops_PGASH[i].ymax <= _hoops_GAHSH)
				_hoops_SSPSH(_hoops_HGHSH, &_hoops_PGASH[i]);
			else
				_hoops_SSPSH(_hoops_SGHSH, &_hoops_PGASH[i]);
		}
		else if (_hoops_PGASH[i].xmax <= _hoops_CRHSH) {
			if (_hoops_PGASH[i].ymin > _hoops_SRHSH)
				_hoops_SSPSH(_hoops_IGHSH, &_hoops_PGASH[i]);
			else if (_hoops_PGASH[i].ymax <= _hoops_GAHSH)
				_hoops_SSPSH(_hoops_CGHSH, &_hoops_PGASH[i]);
			else
				_hoops_SSPSH(_hoops_SGHSH, &_hoops_PGASH[i]);
		}
		else
			_hoops_SSPSH(_hoops_SGHSH, &_hoops_PGASH[i]);

		i++;
	}

	if (_hoops_SGHSH) {
		_hoops_SCPSH(_hoops_SGHSH);
	}

	FREE_ARRAY(_hoops_PGASH, count, _hoops_RGASH);

	if (_hoops_PGHSH) _hoops_AGHSH(data, _hoops_PGHSH);
	if (_hoops_HGHSH) _hoops_AGHSH(data, _hoops_HGHSH);
	if (_hoops_IGHSH) _hoops_AGHSH(data, _hoops_IGHSH);
	if (_hoops_CGHSH) _hoops_AGHSH(data, _hoops_CGHSH);

	_hoops_SCPSH(node);
}

#ifdef _hoops_GGHSH
#pragma optimize("", on)
#endif

local void _hoops_RAHSH (
	_hoops_SGSGP				alter * data) {

	Int_Rectangle const *		_hoops_CRAIR;

	if (data->_hoops_GPHGA != null)
		_hoops_CRAIR = &data->_hoops_GPHGA->_hoops_APHGA->transform_rendition->_hoops_AGAA;
	else if (data->_hoops_IGASH != null)
		_hoops_CRAIR = &data->_hoops_IGASH->_hoops_APHGA->transform_rendition->_hoops_AGAA;
	else if (data->strings != null)
		_hoops_CRAIR = &data->strings->_hoops_APHGA->transform_rendition->_hoops_AGAA;
	else if (data->_hoops_CPGCP != null)
		_hoops_CRAIR = &data->_hoops_CPGCP->_hoops_APHGA->transform_rendition->_hoops_AGAA;
	else
		return;			/* _hoops_ISAP _hoops_IS _hoops_PGSA? */

	_hoops_AGASH	alter * node = data->root = _hoops_HCPSH (data, _hoops_CRAIR->left, _hoops_CRAIR->right, _hoops_CRAIR->bottom, _hoops_CRAIR->top, 0);

	node->count = data->_hoops_APPH;

	bool				_hoops_AAHSH = false;
#ifdef _hoops_PAHSH
	_hoops_AAHSH = true;
#else
	if (node->count < 2500000) {
		TRY_ALLOC_ARRAY_CACHED (node->_hoops_PGASH, node->count, _hoops_RGASH);

		if (!node->_hoops_PGASH)
			_hoops_AAHSH = true;
	}
	else
		_hoops_AAHSH = true;
#endif // _hoops_HAHSH

	if (!_hoops_AAHSH) {
		_hoops_RCRSH	alter * _hoops_RCHHR;
		int					i = 0;

		while ((_hoops_RCHHR = data->_hoops_CPGCP) != null) {
			int	_hoops_RRC, count = _hoops_RCHHR->count;
			DC_Point const *points = _hoops_RCHHR->points;

			data->_hoops_CPGCP = _hoops_RCHHR->next;

			_hoops_RCHHR->next = node->_hoops_CPGCP;
			node->_hoops_CPGCP = _hoops_RCHHR;

			_hoops_ICHC (count, _hoops_RRC, 3);

			while (count--) {
				node->_hoops_PGASH[i]._hoops_RCHHR = _hoops_RCHHR;
				node->_hoops_PGASH[i].offset = points - _hoops_RCHHR->points;

				node->_hoops_PGASH[i].xmin = _hoops_AHIA (points[0].x, _hoops_AHIA (points[1].x, points[2].x));
				node->_hoops_PGASH[i].xmax = _hoops_IAAA (points[0].x, _hoops_IAAA (points[1].x, points[2].x));
				node->_hoops_PGASH[i].ymin = _hoops_AHIA (points[0].y, _hoops_AHIA (points[1].y, points[2].y));
				node->_hoops_PGASH[i].ymax = _hoops_IAAA (points[0].y, _hoops_IAAA (points[1].y, points[2].y));

				if (node->xmin > node->_hoops_PGASH[i].xmin)
					node->xmin = node->_hoops_PGASH[i].xmin;
				if (node->xmax < node->_hoops_PGASH[i].xmax)
					node->xmax = node->_hoops_PGASH[i].xmax;
				if (node->ymin > node->_hoops_PGASH[i].ymin)
					node->ymin = node->_hoops_PGASH[i].ymin;
				if (node->ymax < node->_hoops_PGASH[i].ymax)
					node->ymax = node->_hoops_PGASH[i].ymax;

				i++;

				points += _hoops_RRC;
			}
		}
	}
	else {
		_hoops_RCRSH	alter * _hoops_RCHHR;
		int					i = 0;

		node->count = data->_hoops_SGASH;
		ALLOC_ARRAY (node->_hoops_PGASH, node->count, _hoops_RGASH);

		while ((_hoops_RCHHR = data->_hoops_CPGCP) != null) {
			int				count = _hoops_RCHHR->count;
			DC_Point const *points = _hoops_RCHHR->points;

			data->_hoops_CPGCP = _hoops_RCHHR->next;

			_hoops_RCHHR->next = node->_hoops_CPGCP;
			node->_hoops_CPGCP = _hoops_RCHHR;

			count = Abs(count);

			node->_hoops_PGASH[i]._hoops_RCHHR = _hoops_RCHHR;
			node->_hoops_PGASH[i].offset = -1;

			node->_hoops_PGASH[i].xmin = MAX_FLOAT;
			node->_hoops_PGASH[i].xmax = -MAX_FLOAT;
			node->_hoops_PGASH[i].ymin = MAX_FLOAT;
			node->_hoops_PGASH[i].ymax = -MAX_FLOAT;

			while (count--) {
				if (node->_hoops_PGASH[i].xmin > points->x)
					node->_hoops_PGASH[i].xmin = points->x;
				if (node->_hoops_PGASH[i].xmax < points->x)
					node->_hoops_PGASH[i].xmax = points->x;
				if (node->_hoops_PGASH[i].ymin > points->y)
					node->_hoops_PGASH[i].ymin = points->y;
				if (node->_hoops_PGASH[i].ymax < points->y)
					node->_hoops_PGASH[i].ymax = points->y;

				points++;
			}

			if (node->xmin > node->_hoops_PGASH[i].xmin)
				node->xmin = node->_hoops_PGASH[i].xmin;
			if (node->xmax < node->_hoops_PGASH[i].xmax)
				node->xmax = node->_hoops_PGASH[i].xmax;
			if (node->ymin > node->_hoops_PGASH[i].ymin)
				node->ymin = node->_hoops_PGASH[i].ymin;
			if (node->ymax < node->_hoops_PGASH[i].ymax)
				node->ymax = node->_hoops_PGASH[i].ymax;

			i++;
		}
	}

	_hoops_AGHSH(data, data->root);
}


#define _hoops_IAHSH(node, xmin, xmax, ymin, ymax) \
		(node->xmax >= xmin && node->ymax >= ymin && \
		 node->xmin <= xmax && node->ymin <= ymax)

#define _hoops_CAHSH(bounding, xmin, xmax, ymin, ymax) \
		((bounding).xmax >= xmin && (bounding).ymax >= ymin && \
		 (bounding).xmin <= xmax && (bounding).ymin <= ymax)

#define _hoops_CAIGP(node,xmin,xmax,ymin,ymax) \
				(node->index++, \
				 _hoops_SAHSH (node, xmin, xmax, ymin, ymax))

#define _hoops_HAIGP(root,xmin,xmax,ymin,ymax) \
				(root->index = 0, root->current = 0,\
				 _hoops_SAHSH (root, xmin, xmax, ymin, ymax))


local _hoops_AGASH * _hoops_SAHSH (
	_hoops_AGASH	alter * node,
	float							xmin,
	float							xmax,
	float							ymin,
	float							ymax) {

	/* _hoops_GIPHR _hoops_GIIS _hoops_PHCRA */
	while (node->index<node->count) {
		if (_hoops_CAHSH(node->_hoops_PGASH[node->index], xmin, xmax, ymin, ymax)) {
			node->current = &node->_hoops_PGASH[node->index];
			return node;
		}
		node->index++;
	}

	/* _hoops_SSS _hoops_SPS _hoops_PHCRA */
	node = (node->_hoops_ICHSP != null ? node->_hoops_ICHSP : node->_hoops_GHIIP);

	while (node != null) {
		if (_hoops_IAHSH (node, xmin, xmax, ymin, ymax)) {
			node->index=0;
			while (node->index<node->count) {
				if (_hoops_CAHSH(node->_hoops_PGASH[node->index], xmin, xmax, ymin, ymax)) {
					node->current = &node->_hoops_PGASH[node->index];
					return node;
				}
				node->index++;
			}
			node = (node->_hoops_ICHSP != null ? node->_hoops_ICHSP : node->_hoops_GHIIP);
		}
		else
			node = node->_hoops_GHIIP;
	}

	return null;
}


local void _hoops_GPHSH (
	_hoops_PCRSH		alter *line) {

	if (line->_hoops_HCRSH != null) {
		_hoops_ACRSH alter * _hoops_RCAI;

		while ((_hoops_RCAI = line->_hoops_HCRSH) != null) {
			line->_hoops_HCRSH = _hoops_RCAI->next;

			FREE (_hoops_RCAI, _hoops_ACRSH);
		}
	}
}


GLOBAL_FUNCTION void HD_Free_HL_Data (
	_hoops_SGSGP		alter *data) {

	if (data->_hoops_HGASH != null) {
		_hoops_AGASH		alter * node;
		_hoops_RCRSH				alter * _hoops_RCHHR;

		while ((node = data->_hoops_HGASH) != null) {
			data->_hoops_HGASH = node->next;

			while ((_hoops_RCHHR = node->_hoops_CPGCP) != null) {
				node->_hoops_CPGCP = _hoops_RCHHR->next;

				_hoops_RCHHR->_hoops_APHGA.release();
				_hoops_RCHHR->path.release();

				if (_hoops_RCHHR->_hoops_CAP) {
					int	_hoops_RRC, count=_hoops_RCHHR->count;
					_hoops_ICHC (count, _hoops_RRC, 3);
					FREE_ARRAY(_hoops_RCHHR->_hoops_CAP, count, DC_Point);
				}
				if (_hoops_RCHHR->planes) {
					int count = _hoops_RCHHR->count<0?Abs(_hoops_RCHHR->count)/3:_hoops_RCHHR->count-2;
					FREE_ARRAY(_hoops_RCHHR->planes, count, _hoops_ARPA);
				}
				FREE_ARRAY(_hoops_RCHHR->points, Abs(_hoops_RCHHR->count), DC_Point);
				FREE (_hoops_RCHHR, _hoops_RCRSH);
			}

			if (node->_hoops_PGASH)
				FREE_ARRAY(node->_hoops_PGASH, node->count, _hoops_RGASH);

			FREE (node, _hoops_AGASH);
		}
	}


	/* _hoops_CASI _hoops_GH _hoops_HIPH (_hoops_RPP _hoops_HAR _hoops_PPSI _hoops_GGR _hoops_RPHSH) */
	if (data->_hoops_CPGCP != null) {
		_hoops_RCRSH		alter * _hoops_RCHHR;

		while ((_hoops_RCHHR = data->_hoops_CPGCP) != null) {
			data->_hoops_CPGCP = _hoops_RCHHR->next;

			_hoops_RCHHR->_hoops_APHGA.release();
			_hoops_RCHHR->path.release();

			if (_hoops_RCHHR->_hoops_CAP) {
				int	_hoops_RRC, count=_hoops_RCHHR->count;
				_hoops_ICHC (count, _hoops_RRC, 3);
				FREE_ARRAY(_hoops_RCHHR->_hoops_CAP, count, DC_Point);
			}
			FREE_ARRAY(_hoops_RCHHR->points, Abs(_hoops_RCHHR->count), DC_Point);
			FREE (_hoops_RCHHR, _hoops_RCRSH);
		}
	}

	if (data->_hoops_GPHGA != null) {
		_hoops_CCRSH		alter * polyline;
		_hoops_PCRSH			alter * line;

		while ((polyline = data->_hoops_GPHGA) != null) {
			data->_hoops_GPHGA = polyline->next;

			while ((line = polyline->_hoops_PICHR) != null) {
				polyline->_hoops_PICHR = line->next;

				_hoops_GPHSH (line);
				FREE (line, _hoops_PCRSH);
			}

			int			count = Abs (polyline->count);

			FREE_ARRAY (polyline->points, count, DC_Point);
			if (polyline->colors != null)
				FREE_ARRAY (polyline->colors, count, RGBAS32);

			polyline->_hoops_APHGA.release();
			polyline->path.release();

			FREE (polyline, _hoops_CCRSH);
		}
	}

	if (data->_hoops_IGASH != null) {
		_hoops_HSRSH		alter * marker;

		while ((marker = data->_hoops_IGASH) != null) {
			data->_hoops_IGASH = marker->next;

			marker->_hoops_APHGA.release();
			marker->path.release();

			FREE (marker, _hoops_HSRSH);
		}
	}

	if (data->_hoops_GGPC != null) {
		_hoops_SSRSH		alter * image;

		while ((image = data->_hoops_GGPC) != null) {
			data->_hoops_GGPC = image->next;

			{
			  _hoops_HHHSA alter				*info;

			  info = image->_hoops_GGASH;
			  if (--info->_hoops_HIHI == 0) { /* _hoops_CGH _hoops_SHH _hoops_CR _hoops_SR _hoops_GA'_hoops_RA _hoops_IRHH _hoops_PCIAR */
				  if (info->db_image)
					  _hoops_HPRH (info->db_image);
				  else {
					  int								height;

					  height = (int)(image->_hoops_GGIAR.y - image->p1.y) + 1;
					  FREE_ARRAY (*info->rasters, info->row_bytes * height, char);
					  FREE_ARRAY (info->rasters, height, void *);
				  }
				  FREE (info, _hoops_HHHSA);
			  }
			}

			image->_hoops_APHGA.release();
			image->path.release();

			FREE (image, _hoops_SSRSH);
		}
	}

	if (data->strings != null) {
		_hoops_ISRSH		alter * string;

		while ((string = data->strings) != null) {
			data->strings = string->next;

			string->_hoops_APHGA.release();
			string->path.release();

			if (string->_hoops_CSRSH->text != null)
				_hoops_HPRH (string->_hoops_CSRSH->text);

			if (string->_hoops_HGCSR != null)
				FREE_ARRAY (string->_hoops_HGCSR, string->_hoops_CSRSH->_hoops_SIHSA.length, _hoops_PGCSR);
			_hoops_PRPIR (string->_hoops_CSRSH->_hoops_SIHSA);
			FREE (string->_hoops_CSRSH, _hoops_HIHSA);
			FREE (string, _hoops_ISRSH);
		}
	}

	FREE (data, _hoops_SGSGP);
}



/* _hoops_GRAS _hoops_SSH _hoops_IIGR _hoops_GSSR _hoops_IS _hoops_IPPA _hoops_PAPR _hoops_HPP 3 _hoops_IGPSH */

#define _hoops_APHSH(_hoops_RPPSH,_hoops_APPSH,_hoops_PPPSH)									\
		(((_hoops_APPSH)->x - (_hoops_RPPSH)->x) * ((_hoops_PPPSH)->y - (_hoops_RPPSH)->y) -		\
		 ((_hoops_PPPSH)->x - (_hoops_RPPSH)->x) * ((_hoops_APPSH)->y - (_hoops_RPPSH)->y))


local bool _hoops_PPHSH (
	DC_Point	const	*point,
	_hoops_RCRSH const	*_hoops_RCHHR,
	int					offset) {

	float	value;

	value = _hoops_APHSH (&_hoops_RCHHR->points[offset+0], &_hoops_RCHHR->points[offset+1], point);

	if (Abs (value) > _hoops_RAAHR*_hoops_RAAHR) {
		if (_hoops_APHSH (&_hoops_RCHHR->points[offset+1], &_hoops_RCHHR->points[offset+2], point) * value <= -_hoops_RAAHR)
			return false;

		if (_hoops_APHSH (&_hoops_RCHHR->points[offset+2], &_hoops_RCHHR->points[offset+0], point) * value <= -_hoops_RAAHR)
			return false;
	}
	else {
		value = _hoops_APHSH (&_hoops_RCHHR->points[offset+1], &_hoops_RCHHR->points[offset+2], point);

		if (_hoops_APHSH (&_hoops_RCHHR->points[offset+2], &_hoops_RCHHR->points[offset+0], point) * value <= -_hoops_RAAHR)
			return false;

		//_hoops_RPP (_hoops_HPHSH (&_hoops_SCPH->_hoops_RSSA[_hoops_SHI+0], &_hoops_SCPH->_hoops_RSSA[_hoops_SHI+1], _hoops_PPSR) * _hoops_PIRA <= -_hoops_IPHSH)
		//	_hoops_ASRC _hoops_RCPP;
	}

	return true;
}


local _hoops_ARPA const * _hoops_CPHSH (_hoops_RCRSH const * _hoops_RCHHR, int offset)
{

	if (_hoops_RCHHR->planes == null) {
		int count = _hoops_RCHHR->count<0?Abs(_hoops_RCHHR->count)/3:_hoops_RCHHR->count-2;
		ZALLOC_ARRAY_CACHED(((_hoops_RCRSH alter *)_hoops_RCHHR)->planes, count, _hoops_ARPA);
	}

	int _hoops_SPHSH = _hoops_RCHHR->count<0?offset/3:offset;
	_hoops_ARPA alter *plane = &_hoops_RCHHR->planes[_hoops_SPHSH];

	if (plane->d == 0.0) {
		double			alter	_hoops_GHHSH, _hoops_RHHSH, _hoops_AHHSH;
		double			alter	_hoops_PHHSH, _hoops_HHHSH, _hoops_IHHSH;

		DC_Point	const	*_hoops_RPPSH = &_hoops_RCHHR->points[offset+0];
		DC_Point	const	*_hoops_APPSH = &_hoops_RCHHR->points[offset+1];
		DC_Point	const	*_hoops_PPPSH = &_hoops_RCHHR->points[offset+2];

		_hoops_GHHSH = _hoops_RPPSH->x - _hoops_APPSH->x;
		_hoops_RHHSH = _hoops_RPPSH->y - _hoops_APPSH->y;
		_hoops_AHHSH = _hoops_RPPSH->z - _hoops_APPSH->z;

		_hoops_PHHSH = _hoops_APPSH->x - _hoops_PPPSH->x;
		_hoops_HHHSH = _hoops_APPSH->y - _hoops_PPPSH->y;
		_hoops_IHHSH = _hoops_APPSH->z - _hoops_PPPSH->z;

		plane->a = (float) (_hoops_RHHSH*_hoops_IHHSH - _hoops_AHHSH*_hoops_HHHSH);
		plane->b = (float) (_hoops_AHHSH*_hoops_PHHSH - _hoops_GHHSH*_hoops_IHHSH);
		plane->c = (float) (_hoops_GHHSH*_hoops_HHHSH - _hoops_RHHSH*_hoops_PHHSH);

		HI_Normalize ((Vector alter *)plane);

		if (plane->c < 0.0f) {
			plane->a = -plane->a;
			plane->b = -plane->b;
			plane->c = -plane->c;
		}

		plane->d = -(plane->a*_hoops_RPPSH->x + plane->b*_hoops_RPPSH->y + plane->c*_hoops_RPPSH->z);
	}

	return plane;
}

/* _hoops_GRAS _hoops_AHC _hoops_GSSR _hoops_IS _hoops_IPPA */
#define _hoops_CHHSH(plane, point) \
		((plane)->a*(point)->x + (plane)->b*(point)->y + (plane)->c*(point)->z + (plane)->d)


/* _hoops_GRAS _hoops_SSCHA _hoops_IH _hoops_SHHSH _hoops_IIGR _hoops_SIGC _hoops_CAGH */

local void _hoops_GIHSH (
	_hoops_ARPA const *		plane,
	_hoops_PCRSH const *		line,
	double alter *		_hoops_RIHSH,
	double alter *		_hoops_AIHSH) {
	double				_hoops_IICPA, _hoops_CICPA;

	_hoops_IICPA = _hoops_CHHSH (plane, &line->points[0]);
	_hoops_CICPA = _hoops_CHHSH (plane, &line->points[1]);

	*_hoops_RIHSH = _hoops_IICPA + line->start * (_hoops_CICPA - _hoops_IICPA);
	*_hoops_AIHSH = _hoops_IICPA + line->end	* (_hoops_CICPA - _hoops_IICPA);
}


local bool _hoops_PIHSH (
	_hoops_RCRSH	const *	_hoops_RCHHR,
	int					offset,
	DC_Point const *	point,
	double				_hoops_HIHSH,
	int					_hoops_IIHSH) {
	_hoops_ARPA const *		plane;

	if (offset == -1) {
		int	_hoops_RRC, count = _hoops_RCHHR->count;
		DC_Point		const * points = _hoops_RCHHR->points;
		_hoops_ICHC (count, _hoops_RRC, 3);

		while (count--) {
			if (points-_hoops_RCHHR->points != _hoops_IIHSH &&
				_hoops_PIHSH (_hoops_RCHHR, points-_hoops_RCHHR->points, point, _hoops_HIHSH, -1))
				return true;

			points += _hoops_RRC;
		}

		return false;
	}

	plane = _hoops_CPHSH(_hoops_RCHHR, offset);

	/* _hoops_HCIC _hoops_SGPSH _hoops_ARRS _hoops_IPPA _hoops_IIGR _hoops_SCPH? */
	if (_hoops_CHHSH (plane, point) < _hoops_HIHSH)
		return false;

	/* _hoops_HCIC _hoops_SGPSH _hoops_GGR _hoops_SCPH */
	return _hoops_PPHSH (point, _hoops_RCHHR, offset);
}


local void _hoops_CIHSH (
	_hoops_PCRSH const *		line,
	float				alpha,
	DC_Point alter *	point) {

	if (alpha == 0.0)
		*point = line->points[0];
	else if (alpha == 1.0)
		*point = line->points[1];
	else
		*point = line->points[0] + alpha * (line->points[1] - line->points[0]);
}

local void _hoops_SIHSH (
	_hoops_PCRSH const *		line,
	float				alpha,
	RGBAS32 alter *		color) {

	if (line->colors == null)
		return;

	if (alpha == 0.0)
		*color = line->colors[0];
	else if (alpha == 1.0)
		*color = line->colors[1];
	else
		_hoops_PCRGA (line->colors[0], line->colors[1], alpha, *color);
}


/* _hoops_GRGGA _hoops_GCHSH _hoops_IIHA _hoops_GPP _hoops_CCAH _hoops_III->_hoops_HSPP */

local void _hoops_RCHSH (
	_hoops_PCRSH alter *				line,
	_hoops_SCRSH alter *	_hoops_ACHSH) {
	DC_Point					_hoops_GGIAR;

	_hoops_CIHSH (line, line->start, &_hoops_GGIAR);

	if (line->points[1].x > line->points[0].x)
		_hoops_ACHSH->xmin = _hoops_GGIAR.x;
	else
		_hoops_ACHSH->xmax = _hoops_GGIAR.x;

	if (line->points[1].y > line->points[0].y)
		_hoops_ACHSH->ymin = _hoops_GGIAR.y;
	else
		_hoops_ACHSH->ymax = _hoops_GGIAR.y;
}


/* _hoops_GRGGA _hoops_GCHSH _hoops_IIHA _hoops_GPP _hoops_CCAH _hoops_III->_hoops_RSGR */

local void _hoops_PCHSH (
	_hoops_PCRSH alter *				line,
	_hoops_SCRSH alter *	_hoops_ACHSH) {
	DC_Point					_hoops_GGIAR;

	_hoops_CIHSH (line, line->end, &_hoops_GGIAR);

	if (line->points[1].x > line->points[0].x)
		_hoops_ACHSH->xmax = _hoops_GGIAR.x;
	else
		_hoops_ACHSH->xmin = _hoops_GGIAR.x;

	if (line->points[1].y > line->points[0].y)
		_hoops_ACHSH->ymax = _hoops_GGIAR.y;
	else
		_hoops_ACHSH->ymin = _hoops_GGIAR.y;
}


local void _hoops_HCHSH (
	_hoops_PCRSH		alter * line) {

	line->start = line->end = 1.0f;

	/* _hoops_CASI _hoops_GH _hoops_GII _hoops_ICHSH */
	_hoops_GPHSH (line);

	line->_hoops_HCRSH = line->_hoops_ICRSH = null;
}


local _hoops_ACRSH *_hoops_CCHSH (
	float					start,
	float					end,
	_hoops_ACRSH		alter * prev,
	_hoops_ACRSH		alter * next) {
	_hoops_ACRSH		alter * _hoops_RCAI;

	ALLOC (_hoops_RCAI, _hoops_ACRSH);

	_hoops_RCAI->start = start;
	_hoops_RCAI->end = end;
	_hoops_RCAI->prev = prev;
	_hoops_RCAI->next = next;

	if (_hoops_RCAI->prev != null)
		_hoops_RCAI->prev->next = _hoops_RCAI;
	if (_hoops_RCAI->next != null)
		_hoops_RCAI->next->prev = _hoops_RCAI;

	return _hoops_RCAI;
}


local void _hoops_SCHSH (
	_hoops_PCRSH		alter * line,
	_hoops_ACRSH		alter * _hoops_RCAI) {

	if (_hoops_RCAI->prev != null)
		_hoops_RCAI->prev->next = _hoops_RCAI->next;
	else
		line->_hoops_HCRSH = _hoops_RCAI->next;

	if (_hoops_RCAI->next != null)
		_hoops_RCAI->next->prev = _hoops_RCAI->prev;
	else
		line->_hoops_ICRSH = _hoops_RCAI->prev;

	/* _hoops_PCCP _hoops_HCSP _hoops_IH _hoops_SPHR: _hoops_GSHSH (_hoops_ASAR)_hoops_GHCS _hoops_RSHSH */

	FREE (_hoops_RCAI, _hoops_ACRSH);
}


local void _hoops_ASHSH (
	_hoops_PCRSH alter *				line,
	_hoops_SCRSH alter *	_hoops_ACHSH,
	float const					a) {

	if (a > line->end - _hoops_RAAHR) {
		_hoops_HCHSH (line);
	}
	else if (line->_hoops_HCRSH == null || line->_hoops_HCRSH->start > a + _hoops_RAAHR) {
		/* _hoops_PSHSH _hoops_AGIR: _hoops_PSP _hoops_ICHSH _hoops_PGCRA */
		line->start = a;
	}
	else if (line->_hoops_ICRSH->start <= a + _hoops_RAAHR) {
		/* _hoops_IHGP _hoops_AGIR: _hoops_HCR _hoops_ICHSH _hoops_PGCRA */
		/* (_hoops_GACC _hoops_ICGI _hoops_SPR _hoops_GCPSH _hoops_AGIR) */

		line->start = _hoops_IAAA (a, line->_hoops_ICRSH->end);
		_hoops_GPHSH (line);
		line->_hoops_HCRSH = line->_hoops_ICRSH = null;
	}
	else if (line->_hoops_HCRSH->next->start > a + _hoops_RAAHR) {
		/* _hoops_RGAR _hoops_SRS _hoops_GCPSH _hoops_PGCRA */
		line->start = _hoops_IAAA (a, line->_hoops_HCRSH->end);
		_hoops_SCHSH (line, line->_hoops_HCRSH);
	}
	else {
		/* _hoops_HAR-_hoops_HIS-_hoops_IHGP _hoops_AGIR: _hoops_SSS _hoops_GCPSH _hoops_GRHCP _hoops_IRS */
		_hoops_ACRSH			alter *_hoops_RCAI;

		_hoops_RCAI = line->_hoops_HCRSH->next;
		while (_hoops_RCAI->start < a + _hoops_RAAHR) {
			FREE (_hoops_RCAI->prev, _hoops_ACRSH);
			_hoops_RCAI = _hoops_RCAI->next;
		}

		line->_hoops_HCRSH = _hoops_RCAI;
		line->start = _hoops_IAAA (a, _hoops_RCAI->prev->end);

		FREE (_hoops_RCAI->prev, _hoops_ACRSH);
		_hoops_RCAI->prev = null;
	}

	/* _hoops_PAAP _hoops_HSHSH */

	_hoops_RCHSH (line, _hoops_ACHSH);
}


local void _hoops_ISHSH (
	_hoops_PCRSH alter *				line,
	_hoops_SCRSH alter *	_hoops_ACHSH,
	float const					a) {

	if (a < line->start + _hoops_RAAHR) {
		_hoops_HCHSH (line);
	}
	else if (line->_hoops_ICRSH == null || line->_hoops_ICRSH->end < a - _hoops_RAAHR) {
		/* _hoops_PSHSH _hoops_AGIR: _hoops_PSP _hoops_ICHSH _hoops_PGCRA */
		line->end = a;
	}
	else if (line->_hoops_HCRSH->end >= a - _hoops_RAAHR) {
		/* _hoops_IHGP _hoops_AGIR: _hoops_HCR _hoops_ICHSH _hoops_PGCRA */
		/* (_hoops_GACC _hoops_ICGI _hoops_SPR _hoops_GCPSH _hoops_AGIR) */

		line->end = _hoops_AHIA (a, line->_hoops_HCRSH->start);
		_hoops_GPHSH (line);
		line->_hoops_HCRSH = line->_hoops_ICRSH = null;
	}
	else if (line->_hoops_ICRSH->prev->end < a - _hoops_RAAHR) {
		/* _hoops_IHGP _hoops_AGIR: _hoops_RGAR _hoops_CGHI _hoops_GCPSH _hoops_PGCRA */

		line->end = _hoops_AHIA (a, line->_hoops_ICRSH->start);
		_hoops_SCHSH (line, line->_hoops_ICRSH);
	}
	else {
		/* _hoops_HAR-_hoops_HIS-_hoops_IHGP _hoops_AGIR: _hoops_SSS _hoops_GCPSH _hoops_ARPP _hoops_IRS */
		_hoops_ACRSH			alter *_hoops_RCAI;

		_hoops_RCAI = line->_hoops_ICRSH->prev;
		while (_hoops_RCAI->end > a - _hoops_RAAHR) {
			FREE (_hoops_RCAI->next, _hoops_ACRSH);
			_hoops_RCAI = _hoops_RCAI->prev;
		}

		line->_hoops_ICRSH = _hoops_RCAI;
		line->end = _hoops_AHIA (a, _hoops_RCAI->next->start);

		FREE (_hoops_RCAI->next, _hoops_ACRSH);
		_hoops_RCAI->next = null;
	}

	/* _hoops_PAAP _hoops_HSHSH */
	_hoops_PCHSH(line, _hoops_ACHSH);
}


local void _hoops_CSHSH (
	_hoops_PCRSH alter *				line,
	_hoops_SCRSH alter *	_hoops_ACHSH,
	float const					start,
	float const					end) {

	if (start == 1.0)
		return;

	if (start < line->start + _hoops_RAAHR) {
		_hoops_ASHSH (line, _hoops_ACHSH, end);
	}
	else if (end > line->end - _hoops_RAAHR) {
		_hoops_ISHSH (line, _hoops_ACHSH, start);
	}
	else if (line->_hoops_HCRSH == null) {
		/* _hoops_PSHSH _hoops_AGIR: _hoops_PSP _hoops_APRS _hoops_ICHSH */
		line->_hoops_HCRSH = line->_hoops_ICRSH = _hoops_CCHSH (start, end, null, null);
	}
	else if (line->_hoops_HCRSH->start > end + _hoops_RAAHR) {
		/* _hoops_IHGP _hoops_AGIR: _hoops_GSRGR _hoops_GCPSH _hoops_IAISR _hoops_IIGR _hoops_SRS _hoops_GCPSH */
		line->_hoops_HCRSH = _hoops_CCHSH (start, end, null, line->_hoops_HCRSH);
	}
	else if (line->_hoops_ICRSH->end < start - _hoops_RAAHR) {
		/* _hoops_IHGP _hoops_AGIR: _hoops_GSRGR _hoops_GCPSH _hoops_GHIPR _hoops_CGHI _hoops_GCPSH */
		line->_hoops_ICRSH = _hoops_CCHSH (start, end, line->_hoops_ICRSH, null);
	}
	else if (line->_hoops_HCRSH->end > end + _hoops_RAAHR) {
		/* _hoops_IHGP _hoops_AGIR: _hoops_SSHSH (_hoops_GCAS) _hoops_SRS _hoops_GCPSH */
		line->_hoops_HCRSH->start = _hoops_AHIA (start, line->_hoops_HCRSH->start);
	}
	else if (line->_hoops_ICRSH->start < start + _hoops_RAAHR) {
		/* _hoops_IHGP _hoops_AGIR: _hoops_SSHSH (_hoops_GCAS) _hoops_CGHI _hoops_GCPSH */
		line->_hoops_ICRSH->end = _hoops_IAAA (end, line->_hoops_ICRSH->end);
	}
	else {
		_hoops_ACRSH		*_hoops_GGISH; /* _hoops_RSSA _hoops_IS _hoops_SRS _hoops_RGISH _hoops_GCPSH */
		_hoops_ACRSH		*_hoops_AGISH; /* _hoops_RSSA _hoops_IS _hoops_CGHI _hoops_RGISH _hoops_GCPSH */

		/* _hoops_GRAA-_hoops_IHGP _hoops_AGIR: _hoops_GHCPR _hoops_ICHSH _hoops_SRSS */

		/* _hoops_SSS _hoops_SRS _hoops_RGISH _hoops_GCPSH */
		_hoops_GGISH = line->_hoops_HCRSH;
		while ((_hoops_GGISH->next != null) &&	 (_hoops_GGISH->end + _hoops_RAAHR < start))
			_hoops_GGISH = _hoops_GGISH->next;

		/* _hoops_SSS _hoops_CGHI _hoops_RGISH _hoops_GCPSH */
		_hoops_AGISH = line->_hoops_ICRSH;
		while ((_hoops_AGISH->prev != null) &&	 (end < _hoops_AGISH->start - _hoops_RAAHR))
			_hoops_AGISH = _hoops_AGISH->prev;

		if (_hoops_GGISH == _hoops_AGISH) {
			/* _hoops_RGAR _hoops_SPR _hoops_GCPSH _hoops_RGISH */
			_hoops_GGISH->start = _hoops_AHIA (start, _hoops_GGISH->start);
			_hoops_GGISH->end = _hoops_IAAA (_hoops_GGISH->end, end);
		}
		else if (_hoops_AGISH->end < _hoops_GGISH->start) {
			/* _hoops_PGISH _hoops_PPR _hoops_HGISH _hoops_HS _hoops_IGISH _hoops_IAPR _hoops_GRR _hoops_RII.  _hoops_PSPC,
			 * (_hoops_HSPP, _hoops_RSGR) _hoops_ASSP'_hoops_RA _hoops_ARCRA _hoops_GII _hoops_APRS _hoops_ICHSH */
			_hoops_CCHSH (start, end, _hoops_AGISH, _hoops_GGISH);
		}
		else {
			/* (_hoops_HSPP, _hoops_RSGR) _hoops_CGISH _hoops_PGCR _hoops_PAR _hoops_RRI _hoops_APRS _hoops_ICHSH */
			while (_hoops_AGISH->prev != _hoops_GGISH)
				_hoops_SCHSH (line, _hoops_AGISH->prev);

			_hoops_GGISH->end = _hoops_IAAA (_hoops_AGISH->end, end);
			_hoops_GGISH->start = _hoops_AHIA (start, _hoops_GGISH->start);

			_hoops_SCHSH (line, _hoops_AGISH);
		}
	}
}


/*
 * _hoops_CGIC _hoops_SGSSR _hoops_IIGR _hoops_ISHA [_hoops_ACCPA,_hoops_PCCPA) _hoops_PPR _hoops_III *_hoops_III
 * _hoops_CACH _hoops_SGISH _hoops_GRISH, _hoops_CCAHR.200
 */

local bool _hoops_RRISH (
	DC_Point	const * _hoops_RPPSH,
	DC_Point	const * _hoops_APPSH,
	_hoops_PCRSH		const * line,
	float			alter * alpha) {

	double const _hoops_ARISH = line->points[1].x - line->points[0].x;
	double const _hoops_PRISH = line->points[1].y - line->points[0].y;

	double const _hoops_HRISH = _hoops_RPPSH->x - _hoops_APPSH->x;
	double const _hoops_IRISH = _hoops_RPPSH->y - _hoops_APPSH->y;

	double const _hoops_CRISH = line->points[0].x - _hoops_RPPSH->x;
	double const _hoops_SRISH = line->points[0].y - _hoops_RPPSH->y;

	double const _hoops_SSHGA = _hoops_PRISH*_hoops_HRISH - _hoops_ARISH*_hoops_IRISH;

	double alter beta;

	/* _hoops_GGAIA _hoops_APGR _hoops_PAPR _hoops_GAR _hoops_GRAA-_hoops_IAGPR */
	if (_hoops_GCRSH (_hoops_SSHGA))
		return false;

	beta = (float)((_hoops_ARISH*_hoops_SRISH - _hoops_PRISH*_hoops_CRISH)/_hoops_SSHGA);	/* _hoops_IH _hoops_HA: _hoops_AA _hoops_GAISH */
	if (beta > 1.0 || beta < 0.0)
		return false;

	*alpha = (float)((_hoops_IRISH*_hoops_CRISH - _hoops_HRISH*_hoops_SRISH)/_hoops_SSHGA);

	return true;
}


/* _hoops_SSS _hoops_RH _hoops_PGCR _hoops_SPPR _hoops_IIGR *_hoops_SCPH _hoops_SGS _hoops_HSRAA _hoops_III *_hoops_III */

local void _hoops_RAISH (
	_hoops_RCRSH const *			_hoops_RCHHR,
	int							offset,
	_hoops_PCRSH const *				line,
	_hoops_SCRSH alter *	_hoops_ACHSH,
	float alter *				_hoops_IRHRA,
	float alter *				_hoops_HRHRA,
	double						_hoops_HIHSH) {
	float						alpha;
	float						b[2];
	int							count = 0;
	DC_Point					_hoops_GGIAR;
	_hoops_ARPA const *				plane = null;

	if (_hoops_RRISH (&_hoops_RCHHR->points[offset+0], &_hoops_RCHHR->points[offset+1], line, &alpha)) {
		if (alpha < line->start || alpha > line->end)
			   b[count++] = alpha;
		else {
			_hoops_CIHSH (line, alpha, &_hoops_GGIAR);

			plane = _hoops_CPHSH(_hoops_RCHHR, offset);

			if (_hoops_CHHSH (plane, &_hoops_GGIAR) >= -1.0 * _hoops_HIHSH)
				b[count++] = alpha;
		}
	}

	if (_hoops_RRISH (&_hoops_RCHHR->points[offset+1], &_hoops_RCHHR->points[offset+2], line, &alpha)) {
		if (count == 1 && Abs (alpha - b[0]) < _hoops_ACHSH->_hoops_GSAHR) {}
		else if (alpha < line->start || alpha > line->end)
			   b[count++] = alpha;
		else {
			_hoops_CIHSH (line, alpha, &_hoops_GGIAR);

			if (!plane)
				plane = _hoops_CPHSH(_hoops_RCHHR, offset);

			if (_hoops_CHHSH (plane, &_hoops_GGIAR) >= -1.0 * _hoops_HIHSH)
				b[count++] = alpha;
		}
	}

	if (count > 0 && count != 2 && _hoops_RRISH (&_hoops_RCHHR->points[offset+2], &_hoops_RCHHR->points[offset+0], line, &alpha)) {
		if (alpha < line->start || alpha > line->end)
			   b[count++] = alpha;
		else {
			_hoops_CIHSH (line, alpha, &_hoops_GGIAR);

			if (!plane)
				plane = _hoops_CPHSH(_hoops_RCHHR, offset);

			if (_hoops_CHHSH (plane, &_hoops_GGIAR) >= -1.0 * _hoops_HIHSH)
				b[count++] = alpha;
		}
	}

	if (count < 2)
		*_hoops_IRHRA = *_hoops_HRHRA = 1.0;
	else {
		*_hoops_IRHRA = _hoops_IAAA (line->start, _hoops_AHIA (b[0], b[1]));
		*_hoops_HRHRA = _hoops_AHIA (line->end, _hoops_IAAA (b[0], b[1]));
		if (*_hoops_IRHRA >= *_hoops_HRHRA)
			*_hoops_IRHRA = *_hoops_HRHRA = 1.0;
	}
}


/*
 * _hoops_SSS _hoops_SRS _hoops_ISHA _hoops_IIGR *_hoops_SCPH _hoops_SGS _hoops_AAISH _hoops_III *_hoops_III
 * _hoops_GGR _hoops_IGS _hoops_SGAHP (_hoops_IRS, _hoops_RCSR)
 */

local float _hoops_PAISH (
	_hoops_RCRSH const * _hoops_RCHHR,
	int					offset,
	_hoops_PCRSH const *		line,
	float const			a,
	float const			b) {
	float					alpha;

	if (_hoops_RRISH (&_hoops_RCHHR->points[offset+0], &_hoops_RCHHR->points[offset+1], line, &alpha) &&
		alpha > a && alpha < b) {
			return alpha;
	}

	if (_hoops_RRISH (&_hoops_RCHHR->points[offset+1], &_hoops_RCHHR->points[offset+2], line, &alpha) &&
		alpha > a && alpha < b) {
			return alpha;
	}

	if (_hoops_RRISH (&_hoops_RCHHR->points[offset+2], &_hoops_RCHHR->points[offset+0], line, &alpha) &&
		alpha > a && alpha < b) {
			return alpha;
	}

	return 1.0; /* _hoops_PSP _hoops_APIP _hoops_SGSSR _hoops_GSGI */
}


/*
 * _hoops_HSPH _hoops_SCPH *_hoops_SCPH _hoops_ACSRR _hoops_III _hoops_CAGH *_hoops_III
 */

local void _hoops_HAISH (
	_hoops_RCRSH alter * 		_hoops_RCHHR,
	int							offset,
	_hoops_PCRSH alter *				line,
	_hoops_SCRSH alter *	_hoops_ACHSH,
	double						_hoops_IICPA,
	double						_hoops_CICPA,
	double						_hoops_HIHSH) {
	DC_Point					_hoops_GGIAR;
	float						t;				// _hoops_IAISH _hoops_SGPSH _hoops_RHPC
	float						start, end;		// _hoops_CAISH _hoops_CAGH _hoops_GSHIA

	// _hoops_HPGR _hoops_CHGC _hoops_SPR _hoops_RIHC _hoops_PIHA _hoops_SHH "_hoops_GHIPR" _hoops_RH _hoops_IPPA _hoops_IIGR _hoops_RH _hoops_SCPH

	if (_hoops_IICPA*_hoops_CICPA < 0.0) {										// _hoops_SPR _hoops_RIHC _hoops_GGR _hoops_RIPS */
		// _hoops_RPGP _hoops_RPP _hoops_III _hoops_CAGH _hoops_SAISH _hoops_SCPH

		t = line->start + (float)(_hoops_IICPA/(_hoops_IICPA - _hoops_CICPA)*(line->end - line->start));
		_hoops_CIHSH (line, t, &_hoops_GGIAR);

		if (_hoops_PPHSH (&_hoops_GGIAR, _hoops_RCHHR, offset)) {
			if (_hoops_IICPA > 0.0) {										// (_hoops_RCSR, _hoops_RSGR) _hoops_SIGC
				_hoops_CIHSH (line, line->start, &_hoops_GGIAR);

				if (_hoops_PPHSH (&_hoops_GGIAR, _hoops_RCHHR, offset))		// (_hoops_HSPP, _hoops_RCSR) _hoops_CAISH
					_hoops_ASHSH (line, _hoops_ACHSH, t);
				else {											// _hoops_RGAR _hoops_ARIP _hoops_IIGR (_hoops_HSPP, _hoops_RCSR) _hoops_CAISH
					start = _hoops_PAISH (_hoops_RCHHR, offset, line, 0.0, t);  // _hoops_III->_hoops_HSPP -> 0.0
					if (start != 1.0)
						_hoops_CSHSH (line, _hoops_ACHSH, start, t);
				}
			}
			else {												// (_hoops_HSPP, _hoops_RCSR) _hoops_SIGC */
				_hoops_CIHSH (line, line->end, &_hoops_GGIAR);

				if (_hoops_PPHSH (&_hoops_GGIAR, _hoops_RCHHR, offset))		// (_hoops_RCSR, _hoops_RSGR) _hoops_CAISH
					_hoops_ISHSH (line, _hoops_ACHSH, t);
				else {											// _hoops_RGAR _hoops_ARIP _hoops_IIGR (_hoops_RCSR, _hoops_RSGR) _hoops_CAISH */
					end = _hoops_PAISH (_hoops_RCHHR, offset, line, t, 1.0); // _hoops_III->_hoops_RSGR -> 1.0
					if (end != 1.0)
						_hoops_CSHSH (line, _hoops_ACHSH, t, end);
				}
			}
		}
		else {
			_hoops_RAISH (_hoops_RCHHR, offset, line, _hoops_ACHSH, &start, &end, _hoops_HIHSH);

			if (start == 1.0) {
				if (line->points[0].x == line->points[1].x && line->points[0].y == line->points[1].y &&
					_hoops_PIHSH (_hoops_RCHHR, offset, &line->points[0], -0.1, -1) &&
					_hoops_PIHSH (_hoops_RCHHR, offset, &line->points[1], -0.1, -1)) {
					// _hoops_CAISH _hoops_ARHAR _hoops_CAGH
					_hoops_HCHSH (line);
				}
				else {
					// _hoops_CACH _hoops_RPP _hoops_PCCP _hoops_ISHA _hoops_IIGR _hoops_RH _hoops_SCPH _hoops_SSPP _hoops_AAISH _hoops_RH _hoops_III?
				}
			}
			else {
				// _hoops_RH _hoops_ICSHR _hoops_GGR _hoops_RIPS _hoops_IIGR _hoops_IPPA _hoops_HRGR _hoops_HAR _hoops_CAISH

				if (_hoops_IICPA > 0.0f) {
					if (t > start)
						_hoops_CSHSH (line, _hoops_ACHSH, start, _hoops_AHIA (t, end));
				}
				else {
					if (t < end)
						_hoops_CSHSH (line, _hoops_ACHSH, _hoops_IAAA (start, t), end);
				}
			}
		}

		return;
	}

	// _hoops_GIPR _hoops_GSHIA _hoops_GHIPR _hoops_IPPA

	_hoops_RAISH (_hoops_RCHHR, offset, line, _hoops_ACHSH, &start, &end, _hoops_HIHSH);
	if (start == 1.0) {
		if (line->points[0].x == line->points[1].x && line->points[0].y == line->points[1].y &&
			_hoops_PIHSH (_hoops_RCHHR, offset, &line->points[0], -0.1, -1) &&
			_hoops_PIHSH (_hoops_RCHHR, offset, &line->points[1], -0.1, -1)) {
			// _hoops_CAISH _hoops_ARHAR _hoops_CAGH
			_hoops_HCHSH (line);
		}
		else {
			// _hoops_CACH _hoops_RPP _hoops_PCCP _hoops_ISHA _hoops_IIGR _hoops_RH _hoops_SCPH _hoops_SSPP _hoops_AAISH _hoops_RH _hoops_III?
		}
	}
	else {
		_hoops_CSHSH (line, _hoops_ACHSH, start, end);
	}
}



local bool _hoops_GPISH (
	_hoops_RCRSH alter *			_hoops_RCHHR,
	int							offset,
	_hoops_PCRSH alter *				line,
	_hoops_SCRSH alter *	_hoops_ACHSH,
	double						_hoops_HIHSH) {
	double						_hoops_IICPA, _hoops_CICPA;
	_hoops_ARPA const *				plane;

	if (offset == -1) {
		int	_hoops_RRC, count = _hoops_RCHHR->count;
		DC_Point		const * points = _hoops_RCHHR->points;
		_hoops_ICHC (count, _hoops_RRC, 3);

		while (count--) {
			if (_hoops_GPISH (_hoops_RCHHR, points-_hoops_RCHHR->points, line, _hoops_ACHSH, _hoops_HIHSH))
				return true;

			points += _hoops_RRC;
		}

		return false;
	}

	plane = _hoops_CPHSH(_hoops_RCHHR, offset);
	if (Abs (plane->c) < _hoops_RCPSH)
		return false;

	/* _hoops_AGSH _hoops_GIPR _hoops_SHHSH _hoops_ARRS _hoops_IPPA _hoops_IIGR _hoops_SCPH? */
	_hoops_GIHSH (plane, line, &_hoops_IICPA, &_hoops_CICPA);
	if (_hoops_IICPA <= _hoops_HIHSH && _hoops_CICPA <= _hoops_HIHSH)
		return false;

	/* _hoops_HSPH _hoops_SCPH _hoops_ACSRR _hoops_III */
	_hoops_HAISH (_hoops_RCHHR, offset, line, _hoops_ACHSH, _hoops_IICPA, _hoops_CICPA, _hoops_HIHSH);

	return (line->start == 1.0);
}

#define QS_RESET
#include "utility/hqsort.h"

#define QS_BUBBLE_SORT				_hoops_RPISH
#define QS_QUICK_SORT_RECURSIVE		_hoops_APISH
#define QS_ISSORTED					_hoops_PPISH
#define QS_TYPE				_hoops_CCRSH **			/* _hoops_RH _hoops_GPRR _hoops_IIGR _hoops_CARA _hoops_PAR _hoops_CRPR _hoops_SGS _hoops_ICGI _hoops_HCR _hoops_HSH */
#define QS_VAL(thing,a)		(thing[a]->points[0].z)		/* _hoops_HRS _hoops_RH _hoops_PIRA _hoops_IIGR _hoops_PCCP _hoops_IGCI _hoops_CCA _hoops_CIHA _hoops_IRS */
#define QS_COMPARE(f1,f2)	(f1<f2)						/* _hoops_SGH ">" _hoops_IS _hoops_GHIS _hoops_GACPR, "<" _hoops_IS _hoops_GHIS _hoops_CPIHR */
#define QS_SWAP(thing,a,b)	{Swap (thing[a], thing[b]);}	/* _hoops_SPIHR _hoops_PGCR _hoops_HSH */
#include "utility/hqsort.h"


INLINE bool _hoops_HPISH(_hoops_CCRSH *a, _hoops_CCRSH *b)
{
	return a->points[0].z < b->points[0].z;
}

local void _hoops_IPISH (
	_hoops_SGSGP				alter * data) {
	_hoops_CCRSH			**_hoops_CPISH = null;
	_hoops_CCRSH			alter * polyline;
	int						count = 0;
	int						i = 0;

	if (data->_hoops_GPHGA == null)
		return;

#ifdef _hoops_SPISH
	data->_hoops_GPHGA = _hoops_ASPSH<_hoops_CCRSH*,_hoops_HPISH>(data->_hoops_GPHGA);
#else

	polyline = data->_hoops_GPHGA;
	do ++count;
	while ((polyline = polyline->next) != null);

	TRY_ALLOC_ARRAY (_hoops_CPISH, count, _hoops_CCRSH *);

	if (_hoops_CPISH) {
		polyline = data->_hoops_GPHGA;
		do _hoops_CPISH[i++] = polyline;
		_hoops_RGGA ((polyline = polyline->next) == null);

		_hoops_APISH (_hoops_CPISH, 0, count - 1, 1024);

		for (i=0; i<count-1; i++) {
			_hoops_CPISH[i]->next = _hoops_CPISH[i+1];
		}
		_hoops_CPISH[count-1]->next = null;
		data->_hoops_GPHGA = _hoops_CPISH[0];

		FREE_ARRAY (_hoops_CPISH, count, _hoops_CCRSH *);
	}
	else {
		data->_hoops_GPHGA = _hoops_ASPSH<_hoops_CCRSH*,_hoops_HPISH>(data->_hoops_GPHGA);
	}

#endif
}


GLOBAL_FUNCTION void HD_HL_Expand_Polyline (
	_hoops_CCRSH alter *			polyline) {

	if (polyline->_hoops_PICHR != null)	// _hoops_AIAH _hoops_GHISH (_hoops_IH _hoops_HAGAR, _hoops_CRRIR _hoops_HII _hoops_ASSIA _hoops_PHSPR)
		return;

	Display_Context const *		dc = polyline->_hoops_APHGA->_hoops_SRA;
	DC_Point const *			points = polyline->points;
	RGBAS32 const *				colors = polyline->colors;
	int							count = polyline->count;
	int							_hoops_RRC;
	_hoops_PCRSH alter *				line;
	_hoops_PCRSH alter **			_hoops_ASRGR;

	_hoops_ASRGR = &polyline->_hoops_PICHR;

	_hoops_ICHC (count, _hoops_RRC, 2);

	while (count-- > 0) {
		POOL_ALLOC (line, _hoops_PCRSH, dc->memory_pool);

		*_hoops_ASRGR = line;
		_hoops_ASRGR = &line->next;

		line->points = points;
		line->colors = colors;

		line->start = 0.0f;
		line->end = 1.0f;

		line->_hoops_HCRSH = line->_hoops_ICRSH = null;

		points += _hoops_RRC;
		if (colors != null)
			colors += _hoops_RRC;
	}
	*_hoops_ASRGR = null;
}

GLOBAL_FUNCTION void HD_HL_Collapse_Polyline (
	_hoops_CCRSH alter *			polyline) {
	bool						_hoops_RHISH = true;		// _hoops_HPCAR _hoops_CCGR _hoops_SR _hoops_CACH _hoops_IAII
	bool						_hoops_AHISH = true;		// "

	_hoops_PCRSH alter *				line;
	// _hoops_RPP _hoops_HCR _hoops_SIGC _hoops_PAR _hoops_CCSHP, _hoops_GHRHA _hoops_IS _hoops_PGHC _hoops_SRSGR _hoops_CCA _hoops_RIP _hoops_IS _hoops_CRGH _hoops_PGAP
	// _hoops_SHS _hoops_SHSP _hoops_GAR-_hoops_HRGR (_hoops_GAAP _hoops_HASIR _hoops_CCSHP _hoops_SGHC _hoops_RPP _hoops_SSIA _hoops_PPPPR'_hoops_RA _hoops_SHH _hoops_CHCC?)
	for (line = polyline->_hoops_PICHR; line != null; line = line->next) {
		if (line->start != 0.0f || line->end != 1.0f || line->_hoops_HCRSH != null)
			_hoops_RHISH = false;
		if (line->start != 1.0f)
			_hoops_AHISH = false;
	}

	if (_hoops_RHISH || _hoops_AHISH) {
		polyline->_hoops_HSIPH = _hoops_RHISH;

		while ((line = polyline->_hoops_PICHR) != null) {
			polyline->_hoops_PICHR = line->next;

			_hoops_GPHSH (line);
			FREE (line, _hoops_PCRSH);
		}
	}
}


/* _hoops_HSPH _hoops_GRR _hoops_III _hoops_ACSRR _hoops_HCR _hoops_ARGPR _hoops_HIPH */

local void _hoops_AHPSH (
	_hoops_SGSGP alter *				data) {
	_hoops_AGASH alter *	node;
	_hoops_CCRSH alter *			polyline;
	_hoops_PCRSH alter *				line;
	double						_hoops_HIHSH;

	for (polyline = data->_hoops_GPHGA; polyline != null; polyline = polyline->next) {
		HD_HL_Expand_Polyline (polyline);

		_hoops_HIHSH = polyline->_hoops_APHGA->_hoops_ASIR->_hoops_GCCI._hoops_CHIH;

		for (line = polyline->_hoops_PICHR; line != null; line = line->next) {
			_hoops_SCRSH	_hoops_ACHSH;

			_hoops_ACHSH.xmin = _hoops_AHIA (line->points[0].x, line->points[1].x);
			_hoops_ACHSH.xmax = _hoops_IAAA (line->points[0].x, line->points[1].x);
			_hoops_ACHSH.ymin = _hoops_AHIA (line->points[0].y, line->points[1].y);
			_hoops_ACHSH.ymax = _hoops_IAAA (line->points[0].y, line->points[1].y);

			Vector				delta = line->points[1] - line->points[0];

			_hoops_ACHSH._hoops_GSAHR = _hoops_SGIHR (delta.x * delta.x + delta.y * delta.y);
			if (_hoops_ACHSH._hoops_GSAHR <= 0.1f)
				_hoops_ACHSH._hoops_GSAHR = 0.1f;
			else
				_hoops_ACHSH._hoops_GSAHR = 0.1f / _hoops_ACHSH._hoops_GSAHR;


			node = _hoops_HAIGP (data->root, _hoops_ACHSH.xmin, _hoops_ACHSH.xmax, _hoops_ACHSH.ymin, _hoops_ACHSH.ymax);

			while (node != null && !_hoops_GPISH (node->current->_hoops_RCHHR, node->current->offset, line, &_hoops_ACHSH, _hoops_HIHSH))
				node = _hoops_CAIGP (node, _hoops_ACHSH.xmin, _hoops_ACHSH.xmax, _hoops_ACHSH.ymin, _hoops_ACHSH.ymax);

			/* _hoops_GIRR _hoops_PSAP _hoops_PICAA _hoops_CSRGA */
			if (line->start < _hoops_SIRSH)
				line->start = 0.0;
			if (line->end > 1.0-_hoops_SIRSH)
				line->end = 1.0;
		}

		HD_HL_Collapse_Polyline (polyline);

		if (_hoops_GGPGR(polyline->_hoops_APHGA))
			break;
	}
}



/* _hoops_HSPH _hoops_GRR _hoops_GPIA _hoops_ACSRR _hoops_HCR _hoops_ARGPR _hoops_HIPH */

local void _hoops_PHISH (
	_hoops_SGSGP				alter * data) {
	_hoops_AGASH		alter * node;
	_hoops_HSRSH			alter * marker;
	double							_hoops_HIHSH;

	for (marker = data->_hoops_IGASH; marker != null; marker = marker->next) {
		_hoops_HIHSH = marker->_hoops_APHGA->_hoops_ASIR->_hoops_GCCI._hoops_CHIH;

		node = _hoops_HAIGP (data->root, marker->_hoops_GGIAR.x, marker->_hoops_GGIAR.x, marker->_hoops_GGIAR.y, marker->_hoops_GGIAR.y);

		while (node != null &&
			   (marker->_hoops_HSIPH = !_hoops_PIHSH (node->current->_hoops_RCHHR, node->current->offset,
														 &marker->_hoops_GGIAR, _hoops_HIHSH, -1)) != false)
			node = _hoops_CAIGP (node, marker->_hoops_GGIAR.x, marker->_hoops_GGIAR.x, marker->_hoops_GGIAR.y, marker->_hoops_GGIAR.y);

		if (_hoops_GGPGR(marker->_hoops_APHGA))
			break;
	}
}



/* "_hoops_HSPH" _hoops_GRR _hoops_HCGR _hoops_GSGR _hoops_ACSRR _hoops_HCR _hoops_ARGPR _hoops_HIPH */

local void _hoops_HHISH (
	_hoops_SGSGP				alter * data) {
	_hoops_AGASH		alter * node;
	_hoops_ISRSH			alter * string;
	double							_hoops_HIHSH;

	for (string = data->strings; string != null; string = string->next) {
		DC_Point				_hoops_IHISH[5];
		DC_Point				_hoops_RPIS[2];
		bool				_hoops_CHISH[5];
		int						_hoops_SHISH = 0;
		int						count = 1;
		int						i;

		if (string->_hoops_HGCSR != null) {
			Vector			_hoops_GIISH[2];

			ZERO_ARRAY (_hoops_GIISH, 2, Vector);
			_hoops_GIISH[0].x = string->_hoops_HGCSR->screen.width;
			_hoops_GIISH[1].y = string->_hoops_HGCSR->screen.height;

			if (string->_hoops_APHGA->_hoops_SISI->rotation != 0.0f) {
				float			rotate[16];

				HI_Compute_Rotation_Matrix (0.0, 0.0, string->_hoops_APHGA->_hoops_SISI->rotation, rotate);
				HI_Compute_Transformed_Vectors (2, _hoops_GIISH, rotate, _hoops_GIISH);
			}

			_hoops_IHISH[0].x = string->_hoops_GGIAR.x;
			_hoops_IHISH[0].y = string->_hoops_GGIAR.y;
			_hoops_IHISH[0].z = string->_hoops_GGIAR.z;
			_hoops_IHISH[1].x = string->_hoops_GGIAR.x + _hoops_GIISH[0].x;
			_hoops_IHISH[1].y = string->_hoops_GGIAR.y + _hoops_GIISH[0].y;
			_hoops_IHISH[1].z = string->_hoops_GGIAR.z;
			_hoops_IHISH[2].x = string->_hoops_GGIAR.x + _hoops_GIISH[1].x;
			_hoops_IHISH[2].y = string->_hoops_GGIAR.y + _hoops_GIISH[1].y;
			_hoops_IHISH[2].z = string->_hoops_GGIAR.z;
			_hoops_IHISH[3].x = string->_hoops_GGIAR.x + _hoops_GIISH[0].x + _hoops_GIISH[1].x;
			_hoops_IHISH[3].y = string->_hoops_GGIAR.y + _hoops_GIISH[0].y + _hoops_GIISH[1].y;
			_hoops_IHISH[3].z = string->_hoops_GGIAR.z;
			_hoops_IHISH[4].x = string->_hoops_GGIAR.x + 0.5f*(_hoops_GIISH[0].x + _hoops_GIISH[1].x);
			_hoops_IHISH[4].y = string->_hoops_GGIAR.y + 0.5f*(_hoops_GIISH[0].y + _hoops_GIISH[1].y);
			_hoops_IHISH[4].z = string->_hoops_GGIAR.z;
			count = 5;
		}
		else
			_hoops_IHISH[0] = string->_hoops_GGIAR;

		_hoops_RPIS[0] = _hoops_IHISH[0];
		_hoops_RPIS[1] = _hoops_IHISH[0];
		for (i=1; i<count; i++) {
			if (_hoops_IHISH[i].x < _hoops_RPIS[0].x)
				_hoops_RPIS[0].x = _hoops_IHISH[i].x;
			else if (_hoops_IHISH[i].x > _hoops_RPIS[1].x)
				_hoops_RPIS[1].x = _hoops_IHISH[i].x;

			if (_hoops_IHISH[i].y < _hoops_RPIS[0].y)
				_hoops_RPIS[0].y = _hoops_IHISH[i].y;
			else if (_hoops_IHISH[i].y > _hoops_RPIS[1].y)
				_hoops_RPIS[1].y = _hoops_IHISH[i].y;
		}

		ZERO_ARRAY (_hoops_CHISH, _hoops_GGAPR(_hoops_CHISH), bool);

		_hoops_HIHSH = string->_hoops_APHGA->_hoops_ASIR->_hoops_GCCI._hoops_CHIH;

		for (i=0; i<count; i++) {
			node = _hoops_HAIGP (data->root, _hoops_IHISH[i].x, _hoops_IHISH[i].x, _hoops_IHISH[i].y, _hoops_IHISH[i].y);

			while (node != null) {
				if (!_hoops_CHISH[i] && _hoops_PIHSH (node->current->_hoops_RCHHR, node->current->offset, &_hoops_IHISH[i], _hoops_HIHSH, -1)) {
					_hoops_CHISH[i] = true;
					_hoops_SHISH++;
					break;
				}
				node = _hoops_CAIGP (node, _hoops_IHISH[i].x, _hoops_IHISH[i].x, _hoops_IHISH[i].y, _hoops_IHISH[i].y);
			}

			if (_hoops_SHISH > count/2) {
				string->_hoops_HSIPH = false;
				break;
			}
		}

		if (_hoops_GGPGR(string->_hoops_APHGA))
			break;
	}
}


/* _hoops_GHIS _hoops_RRRH _hoops_HIS _hoops_RPP _hoops_CCSHP _hoops_RHPSH _hoops_CHR _hoops_SIGC _hoops_SSIA _hoops_PGSA _hoops_RIISH */

struct _hoops_AHCIA {
	float *_hoops_PAGCP;
	_hoops_SSRSH **_hoops_AICHR;
	float _hoops_AIISH;
	_hoops_SSRSH *_hoops_PIISH;
};


#if 0
#define _hoops_HIISH(a,b,t)	((t)=(a),(a)=(b),(b)=(t))
#define QS_TYPE				struct _hoops_AHCIA *
#define QS_VAL(thing,a)		(thing->_hoops_PAGCP[a])
#define QS_COMPARE(f1,f2)	(f1<f2)
#define QS_SWAP(thing,a,b) {		\
	_hoops_HIISH(thing->_hoops_PAGCP[a], thing->_hoops_PAGCP[b], thing->_hoops_AIISH); \
	_hoops_HIISH(thing->_hoops_AICHR[a], thing->_hoops_AICHR[b], thing->_hoops_PIISH); \
}
#include "utility/hqsort.h"
local void _hoops_IIISH (
	_hoops_SGSGP				alter * data) {
	int								count = data->_hoops_PRASH;
	float *_hoops_PAGCP;
	_hoops_SSRSH **_hoops_AICHR;
	_hoops_SSRSH *ptr;
	int i;
	struct _hoops_AHCIA _hoops_RCCIA;

	if (data->_hoops_PRASH < 2)
		return;

	ALLOC_ARRAY (_hoops_AICHR, count, _hoops_SSRSH *);
	ALLOC_ARRAY (_hoops_PAGCP, count, float);
	_hoops_RCCIA._hoops_AICHR = _hoops_AICHR;
	_hoops_RCCIA._hoops_PAGCP = _hoops_PAGCP;
	ptr = data->_hoops_GGPC;
	for (i = 0; i < count; i++) {
		_hoops_AICHR[i] = ptr;
		_hoops_PAGCP[i] = ptr->_hoops_GGIAR.z;
		ptr = ptr->next;
	}

	quick_sort (&_hoops_RCCIA, 0, count-1);

	for (i = 0; i < count-1; i++)
		_hoops_AICHR[i]->next = _hoops_AICHR[i+1];
	_hoops_AICHR[count-1]->next = null;

	data->_hoops_GGPC = _hoops_AICHR[0];
	FREE_ARRAY (_hoops_AICHR, count, _hoops_CASS *);
	FREE_ARRAY (_hoops_PAGCP, count, float);
}
#endif

/* _hoops_AIRI _hoops_SIGC _hoops_SGHC _hoops_IIGR _hoops_GRR _hoops_III */

local bool _hoops_CIISH (
	DC_Point const *		p) {

	return (Abs (p[-2].x - p[-1].x) < 0.5f && Abs (p[-2].y - p[-1].y) < 0.5f);
}

local void _hoops_SIISH (
	_hoops_SGSGP alter *			data) {
	DC_Point				_hoops_PIGAR[256];
	RGBAS32					_hoops_GCISH[256];
	DC_Point alter *		new_points = _hoops_PIGAR;
	RGBAS32 alter *			_hoops_RCISH = _hoops_GCISH;

	if (!data->_hoops_GPHGA ||
		_hoops_GGPGR(data->_hoops_GPHGA->_hoops_APHGA))
		return;

	if (data->_hoops_ARASH > _hoops_GGAPR (_hoops_PIGAR)) {
		ALLOC_ARRAY (new_points, data->_hoops_ARASH, DC_Point);
		ALLOC_ARRAY (_hoops_RCISH, data->_hoops_ARASH, RGBAS32);
	}

	for (_hoops_CCRSH alter * polyline = data->_hoops_GPHGA; polyline != null; polyline = polyline->next) {
		DC_Point alter *			point;
		RGBAS32 alter *				color;
		Line_Rendition_Flags		_hoops_ACISH;
		Line_Rendition				_hoops_AHISA;

		data->dc->_hoops_RAI = polyline->_hoops_RAI;
		data->dc->_hoops_RRCIP = polyline->_hoops_RRCIP;
		data->dc->path = polyline->path;
		_hoops_ACISH = polyline->_hoops_APHGA->_hoops_AHP->flags;

		point = new_points;
		color = _hoops_RCISH;

		if (ANYBIT(polyline->_hoops_APHGA->_hoops_AHP->line_style->flags, _hoops_RHISA) &&
			!ALLBITS(polyline->_hoops_APHGA->_hoops_AHP->flags,
					 _hoops_PHISA|_hoops_HHISA)) {
			_hoops_AHISA = polyline->_hoops_APHGA.Modify()->_hoops_AHP.Modify();
		}


		if (polyline->_hoops_PICHR == null) {
			if (polyline->_hoops_HSIPH) {
				if (polyline->colors == null ||
					polyline->_hoops_APHGA->_hoops_RSGC->action._hoops_ISCHP != nullroutine)
					_hoops_GCIGH (polyline->_hoops_APHGA, polyline->count, polyline->points);
				else
					_hoops_ICGGA (polyline->_hoops_APHGA, polyline->count, polyline->points, polyline->colors);
			}
		}
		else for (_hoops_PCRSH alter * line = polyline->_hoops_PICHR; line != null; line = line->next) {
			if (line->start != 1.0f) {
				float		prev = line->start;

				_hoops_CIHSH (line, line->start, point++);
				if (line->colors != null)
					_hoops_SIHSH (line, line->start, color++);

				for (_hoops_ACRSH alter * _hoops_RCAI = line->_hoops_HCRSH; _hoops_RCAI != null; _hoops_RCAI = _hoops_RCAI->next) {
					_hoops_CIHSH (line, _hoops_RCAI->start, point++);

					if (point - new_points == 2 && _hoops_RCAI->start - prev < 0.5f && _hoops_CIISH (point)) {
						// _hoops_HAR _hoops_GHGC _hoops_ASCA, _hoops_PAISR _hoops_RH _hoops_RSSA _hoops_SR _hoops_SAHR _hoops_IIAC (_hoops_PPR _hoops_HAIR _hoops_RPP _hoops_SIGR)
						point = new_points;
						color = _hoops_RCISH;
					}
					else {
						if (_hoops_AHISA) {
							_hoops_AHISA->flags = _hoops_ACISH;
							_hoops_AHISA->flags |= _hoops_PHISA;
							if (_hoops_RCAI != line->_hoops_HCRSH || line->start != 0.0)
								_hoops_AHISA->flags |= _hoops_HHISA;
						}

						if (line->colors != null)
							_hoops_SIHSH (line, _hoops_RCAI->start, color++);

						if (line->colors == null ||
							polyline->_hoops_APHGA->_hoops_RSGC->action._hoops_ISCHP != nullroutine)
							_hoops_GCIGH (polyline->_hoops_APHGA, point-new_points, new_points);
						else
							_hoops_ICGGA (polyline->_hoops_APHGA, point-new_points, new_points, _hoops_RCISH);
					}

					point = new_points;
					color = _hoops_RCISH;

					prev = _hoops_RCAI->end;
					_hoops_CIHSH (line, _hoops_RCAI->end, point++);
					if (line->colors != null)
						_hoops_SIHSH (line, _hoops_RCAI->end, color++);
				}

				if (line->end != 1.0 ||
					  line->next == null ||
						line->next->start != 0.0f ||
							polyline->count < 0) {
					_hoops_CIHSH (line, line->end, point++);
					if (line->colors != null)
						_hoops_SIHSH (line, line->end, color++);

					if (point - new_points == 2 && line->end - prev < 0.5f && _hoops_CIISH (point)) {
						// _hoops_PAH _hoops_SAHR _hoops_SSPC _hoops_ARI _hoops_HRII _hoops_HSAR "_hoops_PAISR" _hoops_GAR _hoops_SR _hoops_HIAP _hoops_CAPP
					}
					else {
						if (_hoops_AHISA) {
							if (line->end == 1.0f)
								_hoops_AHISA->flags = _hoops_ACISH;
							else
								_hoops_AHISA->flags |= _hoops_PHISA;
							if (line->_hoops_ICRSH)
								_hoops_AHISA->flags |= _hoops_HHISA;
						}

						if (line->colors == null ||
							polyline->_hoops_APHGA->_hoops_RSGC->action._hoops_ISCHP != nullroutine)
							_hoops_GCIGH (polyline->_hoops_APHGA, point-new_points, new_points);
						else
							_hoops_ICGGA (polyline->_hoops_APHGA, point-new_points, new_points, _hoops_RCISH);
					}

					point = new_points;
					color = _hoops_RCISH;
				}
			}
			else if (point != new_points) {
				if (line->colors == null ||
					polyline->_hoops_APHGA->_hoops_RSGC->action._hoops_ISCHP != nullroutine)
					_hoops_GCIGH (polyline->_hoops_APHGA, point-new_points, new_points);
				else
					_hoops_ICGGA (polyline->_hoops_APHGA, point-new_points, new_points, _hoops_RCISH);

				point = new_points;
				color = _hoops_RCISH;
			}
		}

		if (_hoops_GGPGR(polyline->_hoops_APHGA))
			break;
	}

	if (new_points != _hoops_PIGAR) {
		FREE_ARRAY (new_points, data->_hoops_ARASH, DC_Point);
		FREE_ARRAY (_hoops_RCISH, data->_hoops_ARASH, RGBAS32);
	}

	data->dc->_hoops_RAI = null;
	data->dc->_hoops_RRCIP = null;
	data->dc->path = null;
}



/*
 * _hoops_AIRI _hoops_CCSHP _hoops_SGHC _hoops_IIGR _hoops_GRR _hoops_III
 */

local void _hoops_PCISH (
	_hoops_SGSGP alter *				data) {
	_hoops_CCRSH alter *			polyline = data->_hoops_GPHGA;
	_hoops_ACRSH alter *				_hoops_RCAI;
	Net_Rendition				_hoops_CRAI;
	Line_Rendition				_hoops_ASGIP;
	RGB							_hoops_IIHIP;
	int							pattern;
	DC_Point					_hoops_PIGAR[256];
	DC_Point alter *			new_points = _hoops_PIGAR;
	RGBAS32						_hoops_GCISH[256];
	RGBAS32 alter *				_hoops_RCISH = _hoops_GCISH;

	if (!data->_hoops_GPHGA ||
		_hoops_GGPGR(data->_hoops_GPHGA->_hoops_APHGA))
		return;

	_hoops_IIHIP.red   = _hoops_CIHIP(polyline->_hoops_APHGA);
	_hoops_IIHIP.green = _hoops_SIHIP(polyline->_hoops_APHGA);
	_hoops_IIHIP.blue  = _hoops_GCHIP(polyline->_hoops_APHGA);
	pattern = polyline->_hoops_APHGA->_hoops_SAIR->_hoops_CGAIP;
	if (pattern >= FP_WINDOW_FIRST_GRADIENT && pattern <= FP_WINDOW_LAST_GRADIENT) {
		_hoops_IIHIP.red   += _hoops_RCHIP(polyline->_hoops_APHGA);
		_hoops_IIHIP.green += _hoops_ACHIP(polyline->_hoops_APHGA);
		_hoops_IIHIP.blue  += _hoops_PCHIP(polyline->_hoops_APHGA);
		_hoops_IIHIP.red   *= 0.5f;
		_hoops_IIHIP.green *= 0.5f;
		_hoops_IIHIP.blue  *= 0.5f;
	}

	if (data->_hoops_ARASH > _hoops_GGAPR (_hoops_PIGAR)) {
		ALLOC_ARRAY (new_points, data->_hoops_ARASH, DC_Point);
		ALLOC_ARRAY (_hoops_RCISH, data->_hoops_ARASH, RGBAS32);
	}

	for (polyline = data->_hoops_GPHGA; polyline != null; polyline = polyline->next) {
		_hoops_PCRSH alter *		line;
		DC_Point alter *	point;
		RGBAS32 alter *		color;

		data->dc->_hoops_RAI = polyline->_hoops_RAI;
		data->dc->_hoops_RRCIP = polyline->_hoops_RRCIP;
		data->dc->path = polyline->path;

		if (BIT (polyline->_hoops_APHGA->_hoops_ASIR->_hoops_GCCI.options, _hoops_RCCI)) {
			RGB							_hoops_HIHIP;
			float						_hoops_IHCRP;

			_hoops_CRAI = polyline->_hoops_APHGA;
			_hoops_ASGIP = _hoops_CRAI.Modify()->_hoops_AHP.Modify(1000000);

			if (BIT (_hoops_CRAI->_hoops_ASIR->_hoops_GCCI.options, _hoops_RPCRP))
				_hoops_ASGIP->line_style = _hoops_CRAI->_hoops_ASIR->_hoops_GCCI.line_style;

			if (BIT (_hoops_CRAI->_hoops_ASIR->_hoops_GCCI.options, _hoops_GHCRP)) {
				if (_hoops_CRAI->_hoops_ASIR->_hoops_GCCI.weight._hoops_HHP == _hoops_SHGRP)
					_hoops_ASGIP->weight = (int)(_hoops_CRAI->_hoops_ASIR->_hoops_GCCI.weight.value *
										_hoops_CRAI->_hoops_SRA->_hoops_PGCC._hoops_IHHSR);
				else
					_hoops_ASGIP->weight = (int)(HD_Compute_Generic_Size (_hoops_CRAI,
											(int)_hoops_CRAI->_hoops_ASIR->_hoops_GCCI.weight.value,
											_hoops_CRAI->_hoops_ASIR->_hoops_GCCI.weight._hoops_HHP,
											1.0f, false, 0, true) + 0.5f);
			}

			_hoops_IHCRP = polyline->_hoops_APHGA->_hoops_ASIR->_hoops_GCCI._hoops_IHCRP;

			point = new_points;

			if (BIT (_hoops_CRAI->_hoops_ASIR->_hoops_GCCI.options, _hoops_SPCRP)) {
				_hoops_HIHIP.red   = _hoops_CRAI->_hoops_ASIR->_hoops_GCCI.color.red;
				_hoops_HIHIP.green = _hoops_CRAI->_hoops_ASIR->_hoops_GCCI.color.green;
				_hoops_HIHIP.blue  = _hoops_CRAI->_hoops_ASIR->_hoops_GCCI.color.blue;
				color = null;
			}
			else {
				_hoops_HIHIP.red   = (float)_hoops_AHIGH(polyline->_hoops_APHGA);
				_hoops_HIHIP.green = (float)_hoops_PHIGH(polyline->_hoops_APHGA);
				_hoops_HIHIP.blue  = (float)_hoops_HHIGH(polyline->_hoops_APHGA);
				color = _hoops_RCISH;
			}

			_hoops_HIHIP.red   += (_hoops_IIHIP.red	  - _hoops_HIHIP.red) * _hoops_IHCRP;
			_hoops_HIHIP.green += (_hoops_IIHIP.green - _hoops_HIHIP.green) * _hoops_IHCRP;
			_hoops_HIHIP.blue  += (_hoops_IIHIP.blue  - _hoops_HIHIP.blue) * _hoops_IHCRP;

			_hoops_ICHIP (_hoops_CRAI, &_hoops_HIHIP, true);

			if (polyline->_hoops_PICHR == null) {
				if (!polyline->_hoops_HSIPH) {
					if (color == null || polyline->colors == null ||
						polyline->_hoops_APHGA->_hoops_RSGC->action._hoops_SSCHP != nullroutine)
						_hoops_ICIGH (_hoops_CRAI, polyline->count, polyline->points);
					else {
						color = _hoops_RCISH;

						for (int i=0; i < polyline->count; ++i) {
							int			delta;

							*color = polyline->colors[i];
							delta = (int)(_hoops_IIHIP.red * 255.99f) - color->r;
							color->r = (unsigned char)((int)color->r + delta * _hoops_IHCRP);
							delta = (int)(_hoops_IIHIP.green * 255.99f) - color->g;
							color->g = (unsigned char)((int)color->g + delta * _hoops_IHCRP);
							delta = (int)(_hoops_IIHIP.blue * 255.99f) - color->b;
							color->b = (unsigned char)((int)color->b + delta * _hoops_IHCRP);
							color++;
						}

						_hoops_ICGGA (_hoops_CRAI, polyline->count, polyline->points, _hoops_RCISH);
					}
				}
			}
			else for (line = polyline->_hoops_PICHR; line != null; line = line->next) {
				if (line->start != 0.0) {
					*point++ = line->points[0];
					if (color != null && line->colors != null) {
						int			delta;

						*color = line->colors[0];
						delta = (int)(_hoops_IIHIP.red * 255.99f) - color->r;
						color->r = (unsigned char)((int)color->r + delta * _hoops_IHCRP);
						delta = (int)(_hoops_IIHIP.green * 255.99f) - color->g;
						color->g = (unsigned char)((int)color->g + delta * _hoops_IHCRP);
						delta = (int)(_hoops_IIHIP.blue * 255.99f) - color->b;
						color->b = (unsigned char)((int)color->b + delta * _hoops_IHCRP);
						color++;
					}
				}

				if (line->start != 1.0) {
					if (line->start != 0.0) {
						_hoops_CIHSH (line, line->start, point++);
						if (color != null && line->colors != null) {
							int			delta;

							_hoops_SIHSH (line, line->start, color);
							delta = (int)(_hoops_IIHIP.red * 255.99f) - color->r;
							color->r = (unsigned char)((int)color->r + delta * _hoops_IHCRP);
							delta = (int)(_hoops_IIHIP.green * 255.99f) - color->g;
							color->g = (unsigned char)((int)color->g + delta * _hoops_IHCRP);
							delta = (int)(_hoops_IIHIP.blue * 255.99f) - color->b;
							color->b = (unsigned char)((int)color->b + delta * _hoops_IHCRP);
							color++;
						}
					}
					if (point != new_points) {
						if (color == null || line->colors == null ||
							polyline->_hoops_APHGA->_hoops_RSGC->action._hoops_SSCHP != nullroutine)
							_hoops_ICIGH (_hoops_CRAI, point-new_points, new_points);
						else
							_hoops_ICGGA (_hoops_CRAI, point-new_points, new_points, _hoops_RCISH);
					}

					for (_hoops_RCAI = line->_hoops_HCRSH; _hoops_RCAI != null; _hoops_RCAI = _hoops_RCAI->next) {
						_hoops_CIHSH (line, _hoops_RCAI->start, &new_points[0]);
						_hoops_CIHSH (line, _hoops_RCAI->end, &new_points[1]);
						if (color != null && line->colors != null) {
							int			delta;

							_hoops_SIHSH (line, _hoops_RCAI->start, &_hoops_RCISH[0]);
							_hoops_SIHSH (line, _hoops_RCAI->end, &_hoops_RCISH[1]);

							color = _hoops_RCISH;
							delta = (int)(_hoops_IIHIP.red * 255.99f) - color->r;
							color->r = (unsigned char)((int)color->r + delta * _hoops_IHCRP);
							delta = (int)(_hoops_IIHIP.green * 255.99f) - color->g;
							color->g = (unsigned char)((int)color->g + delta * _hoops_IHCRP);
							delta = (int)(_hoops_IIHIP.blue * 255.99f) - color->b;
							color->b = (unsigned char)((int)color->b + delta * _hoops_IHCRP);
							color++;
							delta = (int)(_hoops_IIHIP.red * 255.99f) - color->r;
							color->r = (unsigned char)((int)color->r + delta * _hoops_IHCRP);
							delta = (int)(_hoops_IIHIP.green * 255.99f) - color->g;
							color->g = (unsigned char)((int)color->g + delta * _hoops_IHCRP);
							delta = (int)(_hoops_IIHIP.blue * 255.99f) - color->b;
							color->b = (unsigned char)((int)color->b + delta * _hoops_IHCRP);
							color++;
						}
						if (color == null || line->colors == null ||
							polyline->_hoops_APHGA->_hoops_RSGC->action._hoops_SSCHP != nullroutine)
							_hoops_ICIGH (_hoops_CRAI, 2, new_points);
						else
							_hoops_SCGCP (_hoops_CRAI, new_points, _hoops_RCISH);
					}

					point = new_points;
					if (color != null)
						color = _hoops_RCISH;
					if (line->end != 1.0) {
						_hoops_CIHSH (line, line->end, point++);
						if (color != null && line->colors != null) {
							int			delta;

							_hoops_SIHSH (line, line->end, color);

							delta = (int)(_hoops_IIHIP.red * 255.99f) - color->r;
							color->r = (unsigned char)((int)color->r + delta * _hoops_IHCRP);
							delta = (int)(_hoops_IIHIP.green * 255.99f) - color->g;
							color->g = (unsigned char)((int)color->g + delta * _hoops_IHCRP);
							delta = (int)(_hoops_IIHIP.blue * 255.99f) - color->b;
							color->b = (unsigned char)((int)color->b + delta * _hoops_IHCRP);
							color++;
						}
					}
				}

				if ((line->next == null || line->next->start == 0.0 || polyline->count < 0) && point != new_points) {
					*point++ = line->points[1];
					if (color != null && line->colors != null) {
						int			delta;

						*color = line->colors[1];

						delta = (int)(_hoops_IIHIP.red * 255.99f) - color->r;
						color->r = (unsigned char)((int)color->r + delta * _hoops_IHCRP);
						delta = (int)(_hoops_IIHIP.green * 255.99f) - color->g;
						color->g = (unsigned char)((int)color->g + delta * _hoops_IHCRP);
						delta = (int)(_hoops_IIHIP.blue * 255.99f) - color->b;
						color->b = (unsigned char)((int)color->b + delta * _hoops_IHCRP);
						color++;
					}
					if (color == null || line->colors == null ||
						polyline->_hoops_APHGA->_hoops_RSGC->action._hoops_SSCHP != nullroutine)
						_hoops_ICIGH (_hoops_CRAI, point-new_points, new_points);
					else
						_hoops_ICGGA (_hoops_CRAI, point-new_points, new_points, _hoops_RCISH);

					point = new_points;
					if (color != null)
						color = _hoops_RCISH;
				}
			}
		}

		if (_hoops_GGPGR(polyline->_hoops_APHGA))
			break;
	}

	if (new_points != _hoops_PIGAR) {
		FREE_ARRAY (new_points, data->_hoops_ARASH, DC_Point);
		FREE_ARRAY (_hoops_RCISH, data->_hoops_ARASH, RGBAS32);
	}

	data->dc->_hoops_RAI = null;
	data->dc->_hoops_RRCIP = null;
	data->dc->path = null;
}


/*
 * _hoops_AIRI _hoops_HCR _hoops_SIGC _hoops_SAIA _hoops_GAR _hoops_PRAR _hoops_GAR _hoops_CCSHP _hoops_SAIA _hoops_RPP _hoops_CCSHP _hoops_HPRC
 * _hoops_HRGR _hoops_ARP _hoops_IS _hoops_IHPR
 */

local void _hoops_HCISH (
	_hoops_SGSGP const *				data) {
	_hoops_HSRSH alter *			marker = data->_hoops_IGASH;
	Net_Rendition				_hoops_CRAI;
	_hoops_ICP			_hoops_APIHP;
	RGB							_hoops_IIHIP;
	int							pattern;

	if (!data->_hoops_IGASH ||
		_hoops_GGPGR(data->_hoops_IGASH->_hoops_APHGA))
		return;

	_hoops_IIHIP.red   = (float)_hoops_CIHIP(marker->_hoops_APHGA);
	_hoops_IIHIP.green = (float)_hoops_SIHIP(marker->_hoops_APHGA);
	_hoops_IIHIP.blue  = (float)_hoops_GCHIP(marker->_hoops_APHGA);
	pattern = marker->_hoops_APHGA->_hoops_SAIR->_hoops_CGAIP;
	if (pattern >= FP_WINDOW_FIRST_GRADIENT && pattern <= FP_WINDOW_LAST_GRADIENT) {
		_hoops_IIHIP.red   += (float)_hoops_RCHIP(marker->_hoops_APHGA);
		_hoops_IIHIP.green += (float)_hoops_ACHIP(marker->_hoops_APHGA);
		_hoops_IIHIP.blue  += (float)_hoops_PCHIP(marker->_hoops_APHGA);
		_hoops_IIHIP.red   *= 0.5f;
		_hoops_IIHIP.green *= 0.5f;
		_hoops_IIHIP.blue  *= 0.5f;
	}

	for (marker = data->_hoops_IGASH; marker != null; marker = marker->next) {
		data->dc->_hoops_RAI = marker->_hoops_RAI;
		data->dc->_hoops_RRCIP = marker->_hoops_RRCIP;
		data->dc->path = marker->path;

		if (marker->_hoops_HSIPH) {
			if (marker->type == _hoops_RSRSH)
				_hoops_RCIGH (marker->_hoops_APHGA, &marker->_hoops_GGIAR, &marker->rotation, &marker->_hoops_ACIGH);
			else if (marker->type == _hoops_ASRSH)
				_hoops_PCIGH (marker->_hoops_APHGA, &marker->_hoops_GGIAR);
			else if (marker->type == _hoops_PSRSH)
				_hoops_HCIGH(marker->_hoops_APHGA, &marker->_hoops_GGIAR, &marker->color);
		}
		else if (BIT (marker->_hoops_APHGA->_hoops_ASIR->_hoops_GCCI.options, _hoops_RCCI)) {
			RGB					_hoops_ICISH;
			float				_hoops_IHCRP;

			_hoops_CRAI = marker->_hoops_APHGA;
			_hoops_APIHP = _hoops_CRAI.Modify()->_hoops_GSP.Modify(1000000);

			_hoops_IHCRP = marker->_hoops_APHGA->_hoops_ASIR->_hoops_GCCI._hoops_IHCRP;

			if (marker->type != _hoops_PSRSH) {
				_hoops_ICISH.red   = (float)_hoops_IHIGH(marker->_hoops_APHGA);
				_hoops_ICISH.green = (float)_hoops_CHIGH(marker->_hoops_APHGA);
				_hoops_ICISH.blue  = (float)_hoops_SHIGH(marker->_hoops_APHGA);
			}
			else {
				_hoops_ICISH.red   = (float)marker->color.r;
				_hoops_ICISH.green = (float)marker->color.g;
				_hoops_ICISH.blue  = (float)marker->color.b;
			}

			_hoops_ICISH.red   += (_hoops_IIHIP.red	  - _hoops_ICISH.red) * _hoops_IHCRP;
			_hoops_ICISH.green += (_hoops_IIHIP.green - _hoops_ICISH.green) * _hoops_IHCRP;
			_hoops_ICISH.blue  += (_hoops_IIHIP.blue  - _hoops_ICISH.blue) * _hoops_IHCRP;

			_hoops_GSHIP (_hoops_CRAI, &_hoops_ICISH, true);

			if (marker->type == _hoops_RSRSH)
				_hoops_CCIGH (_hoops_CRAI, &marker->_hoops_GGIAR, &marker->rotation, &marker->_hoops_ACIGH);
			else if (marker->type == _hoops_ASRSH)
				_hoops_SCIGH (_hoops_CRAI, &marker->_hoops_GGIAR);
			else if (marker->type == _hoops_PSRSH)
				_hoops_GSIGH (_hoops_CRAI, &marker->_hoops_GGIAR, &marker->color);
		}

		if (_hoops_GGPGR(marker->_hoops_APHGA))
			break;
	}

	data->dc->_hoops_RAI = null;
	data->dc->_hoops_RRCIP = null;
	data->dc->path = null;
}


typedef struct _hoops_CCISH {
	Net_Rendition	nr;
	DC_Point *		points;
	int				count;
	float			_hoops_SCISH;
} _hoops_GSISH;

typedef struct {
	_hoops_RCRSH	const *	_hoops_RCHHR;
	int					offset;
	float				_hoops_SCISH;
} tri_offset_pair_t;


#define QS_RESET
#include "utility/hqsort.h"
#define QS_BUBBLE_SORT				_hoops_RSISH
#define QS_QUICK_SORT_RECURSIVE		_hoops_ASISH
#define QS_ISSORTED					z_poly_issorted
#define QS_TYPE				_hoops_GSISH **
#define QS_VAL(thing,a)		(thing[a]->_hoops_SCISH)
#define QS_COMPARE(f1,f2)	(f1<f2)
#define QS_SWAP(thing,a,b)	Swap (thing[a], thing[b]);

#include "utility/hqsort.h"


#define QS_RESET
#include "utility/hqsort.h"
#define QS_BUBBLE_SORT				_hoops_PSISH
#define QS_QUICK_SORT_RECURSIVE		_hoops_HSISH
#define QS_ISSORTED					_hoops_ISISH
#define QS_TYPE				tri_offset_pair_t **
#define QS_VAL(thing,a)		(thing[a]->_hoops_SCISH)
#define QS_COMPARE(f1,f2)	(f1<f2)
#define QS_SWAP(thing,a,b)	Swap (thing[a], thing[b]);

#include "utility/hqsort.h"


/*
 * _hoops_AIRI _hoops_HCR _hoops_SIGC _hoops_HIPH _hoops_GAR _hoops_PRAR _hoops_GAR _hoops_CCSHP _hoops_HIPH _hoops_RPP _hoops_CCSHP _hoops_HPRC
 * _hoops_HRGR _hoops_ARP _hoops_IS _hoops_IHPR
 */
#include "adt.h"


typedef VList<tri_offset_pair_t *> _hoops_CSISH;
typedef VList<_hoops_GSISH *> _hoops_SSISH;

typedef VHash<int, _hoops_CSISH *> _hoops_GGCSH;




local void _hoops_RGCSH (
    _hoops_SGSGP const *			data) 
{
    _hoops_RCRSH const *		_hoops_RCHHR;
	tri_offset_pair_t *		pair;

	if (!data->root || !data->root->_hoops_CPGCP ||
		_hoops_GGPGR(data->root->_hoops_CPGCP->_hoops_APHGA))
		return;

	_hoops_CSISH *	_hoops_HSIPH = POOL_NEW(data->dc->memory_pool, _hoops_CSISH)(data->dc->memory_pool);
	_hoops_CSISH *	hidden = POOL_NEW(data->dc->memory_pool, _hoops_CSISH)(data->dc->memory_pool);

	/* "_hoops_HSPH" _hoops_GRR _hoops_HAICP _hoops_SCPH _hoops_ACSRR _hoops_HCR _hoops_RII _hoops_ARGPR _hoops_HIPH */
	for (_hoops_RCHHR = data->root->_hoops_CPGCP; _hoops_RCHHR != null; _hoops_RCHHR = _hoops_RCHHR->next) {
		int					_hoops_RRC, count = _hoops_RCHHR->count;
		DC_Point const *	points = _hoops_RCHHR->points;
		DC_Point const *	_hoops_AGCSH = _hoops_RCHHR->_hoops_CAP;
		double				_hoops_HIHSH;

		if (!_hoops_RCHHR->_hoops_CAP)
			continue;

		_hoops_HIHSH = _hoops_RCHHR->_hoops_APHGA->_hoops_ASIR->_hoops_GCCI._hoops_CHIH;

		_hoops_ICHC (count, _hoops_RRC, 3);

		while (count--) {
			_hoops_AGASH alter	*node;
			bool					_hoops_SRGSP = true;
			int						_hoops_PHGGH = points - _hoops_RCHHR->points;

			node = _hoops_HAIGP (data->root, _hoops_AGCSH->x, _hoops_AGCSH->x, _hoops_AGCSH->y, _hoops_AGCSH->y);

			while (node != null &&
				   (node->current->_hoops_RCHHR == _hoops_RCHHR && _hoops_PHGGH == node->current->offset ||
					(_hoops_SRGSP = !_hoops_PIHSH (node->current->_hoops_RCHHR, node->current->offset,
															_hoops_AGCSH, _hoops_HIHSH, _hoops_PHGGH)) != 0))
				node = _hoops_CAIGP (node, _hoops_AGCSH->x, _hoops_AGCSH->x, _hoops_AGCSH->y, _hoops_AGCSH->y);

			if (_hoops_SRGSP ||
				BIT (_hoops_RCHHR->_hoops_APHGA->_hoops_ASIR->_hoops_GCCI.options, _hoops_RCCI)) {

				ALLOC(pair, tri_offset_pair_t);
				pair->_hoops_RCHHR = _hoops_RCHHR;
				pair->offset = _hoops_PHGGH;
				pair->_hoops_SCISH = _hoops_AGCSH->z;

				if (_hoops_SRGSP)
					_hoops_HSIPH->AddFirst(pair);
				else
					hidden->AddFirst(pair);
			}

			points += _hoops_RRC;
			_hoops_AGCSH++;
		}

		if (_hoops_GGPGR(_hoops_RCHHR->_hoops_APHGA))
			goto _hoops_RCCSR;
	}

	/* _hoops_PGSA _hoops_CCSHP _hoops_SRS */
	if (hidden->Count() > 0) {
		RGB						_hoops_PGCSH;
		float					_hoops_IHCRP;
		RGB						_hoops_IIHIP;
		int						pattern;
		tri_offset_pair_t **	_hoops_HGCSH;
		int	_hoops_ISHAR;
		int i;

		pair = hidden->PeekFirst();

		_hoops_RCHHR = pair->_hoops_RCHHR;

		_hoops_IIHIP.red   = (float)_hoops_CIHIP(_hoops_RCHHR->_hoops_APHGA);
		_hoops_IIHIP.green = (float)_hoops_SIHIP(_hoops_RCHHR->_hoops_APHGA);
		_hoops_IIHIP.blue  = (float)_hoops_GCHIP(_hoops_RCHHR->_hoops_APHGA);
		pattern = _hoops_RCHHR->_hoops_APHGA->_hoops_SAIR->_hoops_CGAIP;
		if (pattern >= FP_WINDOW_FIRST_GRADIENT && pattern <= FP_WINDOW_LAST_GRADIENT) {
			_hoops_IIHIP.red   += (float)_hoops_RCHIP(_hoops_RCHHR->_hoops_APHGA);
			_hoops_IIHIP.green += (float)_hoops_ACHIP(_hoops_RCHHR->_hoops_APHGA);
			_hoops_IIHIP.blue  += (float)_hoops_PCHIP(_hoops_RCHHR->_hoops_APHGA);
			_hoops_IIHIP.red   *= 0.5f;
			_hoops_IIHIP.green *= 0.5f;
			_hoops_IIHIP.blue  *= 0.5f;
		}

		_hoops_ISHAR = hidden->Count();

		ALLOC_ARRAY (_hoops_HGCSH, _hoops_ISHAR, tri_offset_pair_t *);

		for (i=0; i<_hoops_ISHAR; i++) {
			_hoops_HGCSH[i] = hidden->RemoveFirst();
		}

		_hoops_HSISH(_hoops_HGCSH, 0, _hoops_ISHAR - 1, 1024);

		for (i=0; i<_hoops_ISHAR; i++) {
			_hoops_RCHHR = _hoops_HGCSH[i]->_hoops_RCHHR;

			data->dc->_hoops_RAI = _hoops_RCHHR->_hoops_RAI;
			data->dc->_hoops_RRCIP = _hoops_RCHHR->_hoops_RRCIP;
			data->dc->path = _hoops_RCHHR->path;

			Net_Rendition				_hoops_CRAI = _hoops_RCHHR->_hoops_APHGA;
			_hoops_CRAI.Modify()->_hoops_IHA.Modify(1000000); // _hoops_IH _hoops_RH _hoops_IGCSH _hoops_GRPHA

			_hoops_IHCRP = _hoops_RCHHR->_hoops_APHGA->_hoops_ASIR->_hoops_GCCI._hoops_IHCRP;

            _hoops_PGCSH.red   = (float)_hoops_RPIGH(_hoops_RCHHR->_hoops_APHGA);
            _hoops_PGCSH.green = (float)_hoops_APIGH(_hoops_RCHHR->_hoops_APHGA);
            _hoops_PGCSH.blue  = (float)_hoops_PPIGH(_hoops_RCHHR->_hoops_APHGA);

			_hoops_PGCSH.red   += (_hoops_IIHIP.red   - _hoops_PGCSH.red) * _hoops_IHCRP;
			_hoops_PGCSH.green += (_hoops_IIHIP.green - _hoops_PGCSH.green) * _hoops_IHCRP;
			_hoops_PGCSH.blue  += (_hoops_IIHIP.blue  - _hoops_PGCSH.blue) * _hoops_IHCRP;

            _hoops_SCHIP (_hoops_CRAI, &_hoops_PGCSH, true);
			/* _hoops_CGCSH? */
			_hoops_CSIGH (_hoops_CRAI, &_hoops_RCHHR->points[_hoops_HGCSH[i]->offset]);

			if (_hoops_GGPGR(_hoops_RCHHR->_hoops_APHGA))
				break;
		}

		for (i=0; i<_hoops_ISHAR; i++)
			FREE(_hoops_HGCSH[i], tri_offset_pair_t);

		FREE_ARRAY (_hoops_HGCSH, _hoops_ISHAR, tri_offset_pair_t *);
	}

	if (_hoops_HSIPH->Count() > 0) {
		pair = _hoops_HSIPH->PeekFirst();
		_hoops_RCHHR = pair->_hoops_RCHHR;

		if (BIT(_hoops_RCHHR->_hoops_APHGA->_hoops_SRA->_hoops_PGCC.flags, _hoops_IPPGH) &&
			_hoops_RCHHR->_hoops_APHGA->_hoops_SRA->_hoops_IPCI->_hoops_RPCGA != HD_Std_DC_Polygon) {

			_hoops_GGCSH *	_hoops_SGCSH;
			_hoops_CSISH *		_hoops_GRCSH;
			_hoops_SSISH *				_hoops_HARIR;
			_hoops_RGSIH *	_hoops_RRCSH;
			int							_hoops_ISHAR;
			int							i,j,k;

			_hoops_ISHAR = _hoops_HSIPH->Count();

			_hoops_SGCSH = POOL_NEW(data->dc->memory_pool, _hoops_GGCSH)(data->dc->memory_pool, 64);

			for (i=0; i<_hoops_ISHAR; i++) {
				pair = _hoops_HSIPH->RemoveFirst();
				_hoops_RCHHR = pair->_hoops_RCHHR;


				if (!_hoops_SGCSH->LookupItem(_hoops_RCHHR->_hoops_APHGA->_hoops_CPA, &_hoops_GRCSH)) {
					_hoops_GRCSH = POOL_NEW(data->dc->memory_pool, _hoops_CSISH)(data->dc->memory_pool);
					_hoops_SGCSH->InsertItem(_hoops_RCHHR->_hoops_APHGA->_hoops_CPA, _hoops_GRCSH);
				}

				_hoops_GRCSH->AddFirst(pair);
			}

			_hoops_HARIR =POOL_NEW(data->dc->memory_pool, _hoops_SSISH)(data->dc->memory_pool);
			_hoops_RRCSH = POOL_NEW(data->dc->memory_pool, _hoops_RGSIH)(data->dc->memory_pool);

			_hoops_GGCSH::PairList * _hoops_ARCSH = _hoops_SGCSH->GetPairList();
			_hoops_GGCSH::Pair * _hoops_PRCSH;

			while ((_hoops_PRCSH = _hoops_ARCSH->RemoveFirst()) != null) {
				DC_Point *	points;
				int	point_count;
				int _hoops_ISPI, _hoops_CSPI, _hoops_SSPI;
				Net_Rendition	_hoops_HRCSH;

				_hoops_GRCSH = _hoops_PRCSH->Item();

				_hoops_ISHAR = _hoops_GRCSH->Count();

				ALLOC_ARRAY(points, _hoops_ISHAR*3, DC_Point);
				point_count=0;

				while ((pair = _hoops_GRCSH->RemoveFirst()) != null) {
					_hoops_RCHHR = pair->_hoops_RCHHR;
					_hoops_HRCSH = _hoops_RCHHR->_hoops_APHGA;

					_hoops_ISPI = -1;
					_hoops_CSPI = -1;
					_hoops_SSPI = -1;

					for (j=0; j<point_count; j++) {
						if (_hoops_ISPI == -1 && points[j] == _hoops_RCHHR->points[pair->offset+0])
							_hoops_ISPI = j;

						if (_hoops_CSPI == -1 && points[j] == _hoops_RCHHR->points[pair->offset+1])
							_hoops_CSPI = j;

						if (_hoops_SSPI == -1 && points[j] == _hoops_RCHHR->points[pair->offset+2])
							_hoops_SSPI = j;

						if (_hoops_ISPI != -1 && _hoops_CSPI != -1 && _hoops_SSPI != -1)
							break;
					}

					if (_hoops_ISPI == -1) {
						_hoops_ISPI = point_count++;
						points[_hoops_ISPI] = _hoops_RCHHR->points[pair->offset+0];
					}
					if (_hoops_CSPI == -1) {
						_hoops_CSPI = point_count++;
						points[_hoops_CSPI] = _hoops_RCHHR->points[pair->offset+1];
					}
					if (_hoops_SSPI == -1) {
						_hoops_SSPI = point_count++;
						points[_hoops_SSPI] = _hoops_RCHHR->points[pair->offset+2];
					}

					FREE(pair, tri_offset_pair_t);

					HI_Polygon_Triangle_Collector (*_hoops_RRCSH, _hoops_ISPI, _hoops_CSPI, _hoops_SSPI);
				}

				if (_hoops_RRCSH->Count() > 0) {
					_hoops_CPGGH *		_hoops_GSHIR;
					DC_Point *				_hoops_IRCSH;

					HI_Polygon_Merge (data->dc->_hoops_RIGC, _hoops_RRCSH);

					while ((_hoops_GSHIR = _hoops_RRCSH->RemoveFirst()) != null) {
						float	_hoops_CRCSH = MAX_FLOAT;
						float	_hoops_PCHH = -MAX_FLOAT;
						_hoops_GSISH *_hoops_SRCSH;

						ALLOC_ARRAY(_hoops_IRCSH, _hoops_GSHIR->count, DC_Point);

						for (k=0; k<_hoops_GSHIR->count; k++) {
							_hoops_IRCSH[k] = points[_hoops_GSHIR->points[k]];

							if (_hoops_IRCSH[k].z > _hoops_PCHH)
								_hoops_PCHH = _hoops_IRCSH[k].z;
							if (_hoops_IRCSH[k].z < _hoops_CRCSH)
								_hoops_CRCSH = _hoops_IRCSH[k].z;
						}

						ZALLOC(_hoops_SRCSH, _hoops_GSISH);

						_hoops_SRCSH->nr = _hoops_HRCSH;
						_hoops_SRCSH->points = _hoops_IRCSH;
						_hoops_SRCSH->count = _hoops_GSHIR->count;
						_hoops_SRCSH->_hoops_SCISH = (_hoops_PCHH+_hoops_CRCSH) * 0.5f;

						_hoops_HARIR->AddFirst(_hoops_SRCSH);

						FREE_ARRAY(_hoops_GSHIR->points, _hoops_GSHIR->count, int);
						FREE(_hoops_GSHIR, _hoops_CPGGH);
					}
				}

				FREE_ARRAY(points, _hoops_ISHAR*3, Point);
				delete _hoops_GRCSH;
				delete _hoops_PRCSH;
			}


			if (_hoops_HARIR->Count() > 0) {
				_hoops_GSISH **	_hoops_GACSH;
				int				_hoops_RACSH;

				_hoops_RACSH = _hoops_HARIR->Count();

				ALLOC_ARRAY (_hoops_GACSH, _hoops_RACSH, _hoops_GSISH *);

				for (i=0; i<_hoops_RACSH; i++) {
					_hoops_GACSH[i] = _hoops_HARIR->RemoveFirst();
				}

				_hoops_ASISH(_hoops_GACSH, 0, _hoops_RACSH - 1, 1024);

				for (i=0; i<_hoops_RACSH; i++) {
					_hoops_GSISH *_hoops_SRCSH;

					_hoops_SRCSH = _hoops_GACSH[i];

					_hoops_PSGCP(_hoops_SRCSH->nr, _hoops_SRCSH->count, _hoops_SRCSH->points);

					if (_hoops_GGPGR(_hoops_SRCSH->nr)) {
						/* _hoops_GGAS _hoops_SCSRA */
						for (; i<_hoops_RACSH; i++) {
							_hoops_SRCSH = _hoops_GACSH[i];
							FREE_ARRAY(_hoops_SRCSH->points, _hoops_SRCSH->count, DC_Point);
							FREE(_hoops_SRCSH, _hoops_GSISH);
						}
						break;
					}

					FREE_ARRAY(_hoops_SRCSH->points, _hoops_SRCSH->count, DC_Point);
					FREE(_hoops_SRCSH, _hoops_GSISH);
				}

				FREE_ARRAY (_hoops_GACSH, _hoops_RACSH, _hoops_GSISH *);
			}

			delete _hoops_RRCSH;
			delete _hoops_HARIR;
			delete _hoops_ARCSH;
			delete _hoops_SGCSH;
		}
		else {
			/* _hoops_HHGPR _hoops_SCPH _hoops_ASCA */

			if (_hoops_HSIPH->Count() > 0) {
				tri_offset_pair_t **	_hoops_HGCSH;
				int	_hoops_ISHAR;
				int i;

				_hoops_ISHAR = _hoops_HSIPH->Count();

				ALLOC_ARRAY (_hoops_HGCSH, _hoops_ISHAR, tri_offset_pair_t *);

				for (i=0; i<_hoops_ISHAR; i++) {
					_hoops_HGCSH[i] = _hoops_HSIPH->RemoveFirst();
				}

				_hoops_HSISH(_hoops_HGCSH, 0, _hoops_ISHAR - 1, 1024);

				for (i=0; i<_hoops_ISHAR; i++) {
					_hoops_RCHHR = _hoops_HGCSH[i]->_hoops_RCHHR;

					data->dc->_hoops_RAI = _hoops_RCHHR->_hoops_RAI;
					data->dc->_hoops_RRCIP = _hoops_RCHHR->_hoops_RRCIP;
					data->dc->path = _hoops_RCHHR->path;

					/* _hoops_AACSH? */
					_hoops_CSIGH (_hoops_RCHHR->_hoops_APHGA, &_hoops_RCHHR->points[_hoops_HGCSH[i]->offset]);

					if (_hoops_GGPGR(_hoops_RCHHR->_hoops_APHGA))
						break;
				}


				for (i=0; i<_hoops_ISHAR; i++)
					FREE(_hoops_HGCSH[i], tri_offset_pair_t);

				FREE_ARRAY (_hoops_HGCSH, _hoops_ISHAR, tri_offset_pair_t *);
			}
		}
	}

_hoops_RCCSR:
	while ((pair = _hoops_HSIPH->RemoveFirst()) != null)
		FREE(pair, tri_offset_pair_t);

	while ((pair = hidden->RemoveFirst()) != null)
		FREE(pair, tri_offset_pair_t);

	delete _hoops_HSIPH;
	delete hidden;

    data->dc->_hoops_RAI = null;
    data->dc->_hoops_RRCIP = null;
    data->dc->path = null;
}



/*
 * _hoops_AIRI _hoops_HCR _hoops_SIGC _hoops_HCGR _hoops_RHIPP
 */

local void _hoops_PACSH (
	_hoops_SGSGP const *				data) {
	_hoops_ISRSH alter *			string = data->strings;
	_hoops_HIHSA const *	_hoops_CSGCP;
	RGB							_hoops_IIHIP;
	int							pattern;

	if (!data->strings ||
		_hoops_GGPGR(data->strings->_hoops_APHGA))
		return;

	_hoops_IIHIP.red   = (float)_hoops_CIHIP(string->_hoops_APHGA);
	_hoops_IIHIP.green = (float)_hoops_SIHIP(string->_hoops_APHGA);
	_hoops_IIHIP.blue  = (float)_hoops_GCHIP(string->_hoops_APHGA);
	pattern = string->_hoops_APHGA->_hoops_SAIR->_hoops_CGAIP;
	if (pattern >= FP_WINDOW_FIRST_GRADIENT && pattern <= FP_WINDOW_LAST_GRADIENT) {
		_hoops_IIHIP.red   += (float)_hoops_RCHIP(string->_hoops_APHGA);
		_hoops_IIHIP.green += (float)_hoops_ACHIP(string->_hoops_APHGA);
		_hoops_IIHIP.blue  += (float)_hoops_PCHIP(string->_hoops_APHGA);
		_hoops_IIHIP.red   *= 0.5f;
		_hoops_IIHIP.green *= 0.5f;
		_hoops_IIHIP.blue  *= 0.5f;
	}

	for (string = data->strings; string != null; string = string->next) {
		data->dc->_hoops_RAI = string->_hoops_RAI;
		data->dc->_hoops_RRCIP = string->_hoops_RRCIP;
		data->dc->path = string->path;

		_hoops_CSGCP = string->_hoops_CSRSH;

		if (string->_hoops_HSIPH) {
			((Font_Instance *)string->_hoops_APHGA->_hoops_SISI->font)->_hoops_RACSR = _hoops_CSGCP->_hoops_RACSR;
			((Font_Instance *)string->_hoops_APHGA->_hoops_SISI->font)->_hoops_GCHSA = _hoops_CSGCP->_hoops_GCHSA;

			HD_Standard_Draw_Plain_Text (string->_hoops_APHGA, _hoops_CSGCP->text, (Point *)&string->_hoops_GGIAR,
										 _hoops_CSGCP->_hoops_SIHSA.length, _hoops_CSGCP->_hoops_SIHSA._hoops_IPPPP, null);
		}
		else if (BIT (string->_hoops_APHGA->_hoops_ASIR->_hoops_GCCI.options, _hoops_RCCI)) {
			Net_Rendition			_hoops_CRAI = string->_hoops_APHGA;
			_hoops_IGCSR alter &	_hoops_IRRIP = _hoops_CRAI.Modify()->_hoops_SISI.Modify(1000000);
			RGB						_hoops_HACSH;
			float					_hoops_IHCRP;

			_hoops_IHCRP = string->_hoops_APHGA->_hoops_ASIR->_hoops_GCCI._hoops_IHCRP;

			_hoops_HACSH.red   = (float)_hoops_GIIGH(string->_hoops_APHGA);
			_hoops_HACSH.green = (float)_hoops_RIIGH(string->_hoops_APHGA);
			_hoops_HACSH.blue  = (float)_hoops_AIIGH(string->_hoops_APHGA);

			_hoops_HACSH.red   += (_hoops_IIHIP.red	  - _hoops_HACSH.red) * _hoops_IHCRP;
			_hoops_HACSH.green += (_hoops_IIHIP.green - _hoops_HACSH.green) * _hoops_IHCRP;
			_hoops_HACSH.blue  += (_hoops_IIHIP.blue  - _hoops_HACSH.blue) * _hoops_IHCRP;

			_hoops_RSHIP (_hoops_CRAI, &_hoops_HACSH, true);
			if (_hoops_IRRIP->_hoops_RGIHP != null) {		/* _hoops_CGH _hoops_SHH _hoops_RPP _hoops_AHGGR */
				Line_Rendition alter &		_hoops_ASAIP = _hoops_IRRIP->_hoops_RGIHP.Modify();

				_hoops_ASAIP->color = _hoops_IRRIP->color;
				_hoops_ASAIP->_hoops_CHA = _hoops_IRRIP->_hoops_CHA;
				//_hoops_RGISR->_hoops_GGCS = _hoops_IRAP;
			}

			HD_Standard_Draw_Plain_Text (_hoops_CRAI, _hoops_CSGCP->text, (Point *)&string->_hoops_GGIAR,
										 _hoops_CSGCP->_hoops_SIHSA.length, _hoops_CSGCP->_hoops_SIHSA._hoops_IPPPP, null);
		}

		if (_hoops_GGPGR(string->_hoops_APHGA))
			break;
	}

	data->dc->_hoops_RAI = null;
	data->dc->_hoops_RRCIP = null;
	data->dc->path = null;
}


/*
 * _hoops_IACSH _hoops_HIPH _hoops_ACSRR _hoops_APGR, _hoops_SAIA, _hoops_PPR _hoops_HCGR,
 * _hoops_PPR _hoops_AIRI _hoops_PCPA'_hoops_GRI _hoops_RAAP.
 */

GLOBAL_FUNCTION void HD_HL_See_Whats_Hidden (
	Net_Rendition const &		nr) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_SGSGP alter *				data = dc->_hoops_SHSHP;

	if (!_hoops_IACI(dc)) {
		if (!data->_hoops_HHPGR) {
			if (data->_hoops_GISHP)
				_hoops_IPISH (data);

			if (data->_hoops_CPGCP != null) {
				_hoops_RAHSH (data);

				_hoops_AHPSH (data);
				_hoops_PHISH (data);
				_hoops_HHISH (data);
				data->_hoops_HRASH = true;
			}
			if (!_hoops_IACI(dc))
				data->_hoops_HHPGR = true;
		}

		if (data->_hoops_HRASH)
			_hoops_PCISH (data);
		_hoops_RGCSH (data);
		_hoops_SIISH (data);
		_hoops_HCISH (data);
		_hoops_PACSH (data);
	}
	if (!data->_hoops_HHPGR) {
		/* _hoops_ASASA _hoops_PIH */
		HD_Free_HL_Data (data);
		dc->_hoops_SHSHP = null;
	}

	/* _hoops_CIS _hoops_HA _hoops_GIAGR _hoops_GSSR _hoops_GGAS _hoops_PAR _hoops_SRSRR */
}

#endif

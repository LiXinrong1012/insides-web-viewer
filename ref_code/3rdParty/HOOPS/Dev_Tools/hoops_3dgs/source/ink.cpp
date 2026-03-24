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
 * $Id: obf_tmp.txt 1.86 2010-08-25 01:47:58 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


struct _hoops_IHAPI {
	float			x, y, z;

	Polyline *		_hoops_CHAPI;
	int				_hoops_IGSSR;
	int				count;
};



local Polyline * _hoops_SHAPI (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP)
{
	Geometry *				geometry;
	Polyline *				polyline;

	if ((geometry = _hoops_SRCP->geometry) != null) do {
		if (geometry->type >= _hoops_IIIP) {
			if (geometry->type > _hoops_IIIP) {
				if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_AASIR)) break;
			}
			else if (BIT (geometry->_hoops_RRHH, _hoops_HIHCA) &&
					 !BIT (geometry->_hoops_RRHH, _hoops_HGAGR)) {
				polyline = (Polyline *)geometry;
				if (_hoops_SRCP == _hoops_RIGC->open_list->info.segment._hoops_IGRPR) {
					_hoops_RIGC->open_list->info.segment._hoops_ACRIR = polyline;
					_hoops_PRRH (polyline);
				}
				return polyline;
			}
		}
	} while ((geometry = geometry->next) != null);

	Key key = HI_Insert_Polyline (_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP, 0, null);

	polyline = (Polyline *)_hoops_RCSSR (_hoops_RIGC, key);
	polyline->_hoops_RRHH |= _hoops_HIHCA;

	if (_hoops_SRCP == _hoops_RIGC->open_list->info.segment._hoops_IGRPR) {
		_hoops_RIGC->open_list->info.segment._hoops_ACRIR = polyline;
		_hoops_PRRH (polyline);
	}

	if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) {/* _hoops_SIAS _hoops_HS _hoops_RPII _hoops_PCCP _hoops_RHGS _hoops_GIAPI */
		_hoops_CRCP				*_hoops_SAGSA = _hoops_SRCP;

		while (_hoops_SAGSA = _hoops_SAGSA->owner,
			   _hoops_SAGSA->type != _hoops_PRAIR &&
			   BIT (_hoops_SAGSA->_hoops_PHSI, _hoops_PRSIR)) {
			if ((geometry = _hoops_SAGSA->geometry) != null) do {
				if (geometry->type >= _hoops_IIIP) {
					if (geometry->type > _hoops_IIIP) break;

					if (BIT (geometry->_hoops_RRHH, _hoops_HIHCA) &&
						!BIT (geometry->_hoops_RRHH, _hoops_HGAGR)) {
						/* _hoops_SHSP _hoops_RH _hoops_RIP _hoops_IHPPP _hoops_GPP (_hoops_IH _hoops_RIAPI)! */
						Polyline const *	_hoops_AIAPI = (Polyline *)geometry;

						if (_hoops_AIAPI->count != 0) {
							Point			*old,
											*points;

							ZALLOC_ARRAY (points, 4, Point);
							polyline->points = points;
							polyline->allocated = 4;
							polyline->count = 1;

							old = _hoops_AIAPI->points + _hoops_AIAPI->count - 1;
							points->x = old->x;
							points->y = old->y;
							points->z = old->z;
						}
					}
				}
			} while ((geometry = geometry->next) != null);
		}
	}

	return polyline;
}


local void _hoops_PIAPI (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	_hoops_IHAPI *			data)
{
	Point *					points;
	Polyline *				polyline = null;

	if (_hoops_SRCP == _hoops_RIGC->open_list->info.segment._hoops_IGRPR &&
		_hoops_RIGC->open_list->info.segment._hoops_ACRIR != null)
		polyline = _hoops_RIGC->open_list->info.segment._hoops_ACRIR;
	else
		polyline = _hoops_SHAPI (_hoops_RIGC, _hoops_SRCP);

	if ((points = polyline->points) == null) {
		ZALLOC_ARRAY (points, 4, Point);
		polyline->points = points;
		polyline->allocated = 4;
	}
	else if (polyline->count == polyline->allocated) {
		int				count = polyline->allocated;
		Point *			old = points;

		ZALLOC_ARRAY(points, 2*count, Point);
		polyline->points = points;
		polyline->allocated = 2*count;
		_hoops_AIGA (old, count, Point, points);
		FREE_ARRAY (old, count, Point);
	}

	points[polyline->count].x = data->x;
	points[polyline->count].y = data->y;
	points[polyline->count].z = data->z;
	++polyline->count;

	if (data->z != 0.0f && !BIT (polyline->_hoops_RRHH, _hoops_RSPCR)) {
		polyline->_hoops_RRHH |= _hoops_RSPCR;
		if (!BIT (polyline->owner->_hoops_RCGC, _hoops_ASPCR))
			HI_Propagate_Maybes (_hoops_RIGC, polyline->owner, _hoops_ASPCR);
	}


	int						_hoops_HAHC	= polyline->count;
	Point *					_hoops_SPGGA = polyline->points;

	polyline->count	 = 1;
	polyline->points += _hoops_HAHC - 1;

	Bounding				bounding;
	if (HI_Figure_Geometry_Bounding ((Geometry *)polyline, bounding)) {
		HI_Propagate_Bounding (_hoops_RIGC, polyline->owner, bounding, null);
		_hoops_SRCP->_hoops_HSRIR.Merge (bounding);
	}

	polyline->count	 = _hoops_HAHC;
	polyline->points = _hoops_SPGGA;


	if (BIT (polyline->_hoops_CPGPR, _hoops_CASIR))
		polyline->_hoops_CPGPR |= _hoops_GGARA;
	else if (!BIT (polyline->_hoops_CPGPR, _hoops_AHSGA))
		polyline->_hoops_CPGPR |= _hoops_HHSSR;

	HI_Invalidate_Segment_Display_Lists(_hoops_RIGC, _hoops_SRCP, _hoops_IIIP, polyline, 0);

	_hoops_SASIR (_hoops_RIGC, polyline->owner, _hoops_IHSSR|
										   _hoops_PISSR|_hoops_RPSIR);

	data->_hoops_CHAPI = polyline;
	++data->_hoops_IGSSR;
}


local void _hoops_HIAPI (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	_hoops_IHAPI *			data)
{
	Polyline *				polyline;
	int						count = data->count;

	if (_hoops_SRCP == _hoops_RIGC->open_list->info.segment._hoops_IGRPR &&
		_hoops_RIGC->open_list->info.segment._hoops_ACRIR != null)
		polyline = _hoops_RIGC->open_list->info.segment._hoops_ACRIR;
	else
		polyline = _hoops_SHAPI (_hoops_RIGC, _hoops_SRCP);


	if (count < -(polyline->allocated))
		count = -(polyline->allocated);
	if (count > polyline->count)
		polyline->count = 0;
	else
		polyline->count -= count;
	if (polyline->count > polyline->allocated)
		polyline->count = polyline->allocated;

	HI_Invalidate_Segment_Display_Lists(_hoops_RIGC, _hoops_SRCP, _hoops_IIIP, polyline, 0);

	if (polyline->owner)
		HI_Antiquate_Bounding (polyline->owner, true);

	if (!BIT (polyline->_hoops_CPGPR, _hoops_AHSGA))
		polyline->_hoops_CPGPR |= _hoops_HHSSR;

	_hoops_SASIR (_hoops_RIGC, polyline->owner, _hoops_RAGGA|
										   _hoops_PISSR|_hoops_RPSIR);
}


HC_INTERFACE void HC_CDECL HC_Rollback_Ink (
	int						count)
{
	_hoops_PAPPR context("Rollback_Ink");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_D (null, "HC_Rollback_Ink (%d);\n", count));
	);

	_hoops_IHAPI	data;
	data.count = count;

	_hoops_RPPPR();
	if (context->open_list != null && context->open_list->_hoops_GCRIR == _hoops_RCRIR ||
		HI_Find_Our_Open (context)) {
		_hoops_HIAPI (context, context->open_list->info.segment._hoops_IGRPR, &data);
	}
	_hoops_IRRPR();
}

HC_INTERFACE Key HC_CDECL HC_Insert_Ink (
	double					x,
	double					y,
	double					z)
{
	_hoops_PAPPR context("Insert_Ink");

	_hoops_IHAPI			data;
	Key						_hoops_CHSSR = _hoops_SHSSR;

	ZERO_STRUCT(&data, _hoops_IHAPI);
	data.x = (float)x;	  data.y = (float)y;	data.z = (float)z;

	_hoops_RPPPR();
	if (context->open_list != null && context->open_list->_hoops_GCRIR == _hoops_RCRIR ||
		HI_Find_Our_Open (context)) {
		_hoops_PIAPI (context, context->open_list->info.segment._hoops_IGRPR, &data);
	}
	_hoops_IRRPR();

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data._hoops_CHAPI);

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "DEFINE (HC_Insert_Ink (%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F), ", z));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
	);

	return _hoops_CHSSR;
}

local void _hoops_IIAPI (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_CRCP *					_hoops_SRCP)
{
	Polyline *					polyline = null;
	_hoops_SIRIR *					_hoops_AHSCA;

	if (_hoops_SRCP == _hoops_RIGC->open_list->info.segment._hoops_IGRPR)	/* _hoops_ICSI _hoops_ISPR */
		polyline = _hoops_RIGC->open_list->info.segment._hoops_ACRIR;

	if (polyline == null) {						/* _hoops_GIPHR _hoops_IH _hoops_SCH */
		Geometry *				x;

		if ((x = _hoops_SRCP->geometry) != null) do {
			if (x->type >= _hoops_IIIP) {
				if (x->type > _hoops_IIIP) {
					if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_AASIR)) {
						polyline = null;
						break;
					}
				}
				else if (BIT (x->_hoops_RRHH, _hoops_HIHCA) &&
						 !BIT (x->_hoops_RRHH, _hoops_HGAGR)) {
					polyline = (Polyline *)x;
					break;
				}
			}
		} while ((x = x->next) != null);
	}

	if (polyline != null && polyline->count > 0) {	 /* _hoops_IIH _hoops_CSAP _hoops_IIHCA */
		polyline->_hoops_RRHH &= ~_hoops_HIHCA;

		/* _hoops_GGCH _hoops_GII "_hoops_CIAPI"_hoops_GRI _hoops_GPP _hoops_RGR _hoops_CAGH */

		_hoops_AHSCA = _hoops_RIGC->open_list;
		while (_hoops_AHSCA != null) {
			if (_hoops_AHSCA->_hoops_GCRIR == _hoops_RCRIR &&
				_hoops_AHSCA->info.segment._hoops_ACRIR == polyline) {
				_hoops_HPRH (polyline);
				_hoops_AHSCA->info.segment._hoops_ACRIR = null;
			}
			_hoops_AHSCA = _hoops_AHSCA->next;
		}
	}
}

HC_INTERFACE void HC_CDECL HC_Restart_Ink (void)
{
	_hoops_PAPPR context("Restart_Ink");

	CODE_GENERATION (
		HI_Dump_Code ("HC_Restart_Ink ();\n");
	);

	_hoops_RPPPR();
	if (context->open_list != null && context->open_list->_hoops_GCRIR == _hoops_RCRIR ||
		HI_Find_Our_Open (context)) {
		_hoops_IIAPI (context, context->open_list->info.segment._hoops_IGRPR);
	}
	_hoops_IRRPR();
}


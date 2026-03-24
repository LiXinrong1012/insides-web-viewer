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
 * $Id: obf_tmp.txt 1.287 2011-01-07 23:09:39 heppe Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hd_proto.h"
#include "hpserror.h"
#include "adt.h"


#define _hoops_GPHPS 0

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

local const _hoops_IGRCR _hoops_RPHPS[] = {
	{_hoops_ICGAP,						_hoops_GRRCR ("tessellation"),					_hoops_APRCA,			-8, false},
	{_hoops_ACGAP,						_hoops_GRRCR ("cylinder"),						_hoops_APRCA,			-8, false},
	{_hoops_PCGAP,						_hoops_GRRCR ("sphere"),						_hoops_APRCA,			-8, false},
	{_hoops_HCGAP,				_hoops_GRRCR ("nurbs surface"),					_hoops_GHAGA, -999, false,	&_hoops_RIPRS},
};


struct _hoops_APHPS {
	int					point_count;
	Point const *		points;
	int					face_list_length;
	int const *			face_list;

	int					face_count;
	bool				_hoops_ISSIH;
	bool				_hoops_SHCIH;

	Shell *				_hoops_SPHPR;
	int					_hoops_IGSSR;

	Tristrip *			tristrips;
};


local Shell * _hoops_PPHPS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				owner,
	Shell *					_hoops_SPHPR,
	bool					_hoops_SHCIH)
{
	Activity	_hoops_CPGPR = _hoops_SPHPR->_hoops_CPGPR;

	if (!BIT (_hoops_RSPPR(_hoops_RIGC, flags), _hoops_APGHP)) {
		_hoops_SPHPR->_hoops_CPGPR = _hoops_AHSGA;
		HI_Figure_Geometry_Bounding ((Geometry const *)_hoops_SPHPR, _hoops_SPHPR->bounding);
		_hoops_SPHPR->_hoops_CPGPR = _hoops_CPGPR;
	}

	_hoops_CPGPR = (_hoops_SPHPR->point_count > 0 ? _hoops_IHSSR | (_hoops_SPHPR->face_list_length > 0 ? _hoops_SIGPR : 0) : _hoops_CCHPA);

	/* _hoops_PAGA: _hoops_GSRGR _hoops_CRGR _hoops_PCHII 0 _hoops_PAH _hoops_APRI _hoops_RH _hoops_RRCPR _hoops_SR _hoops_GGHP */
	_hoops_SPHPR = (Shell *) HI_Insert_Geometry (_hoops_RIGC, owner, (Geometry *)_hoops_SPHPR, _hoops_SHCIH, _hoops_CPGPR);

	if (_hoops_SPHPR != null && _hoops_SPHPR->owner != null)
		_hoops_SASIR (_hoops_RIGC, _hoops_SPHPR->owner, _hoops_IHSSR);

	return _hoops_SPHPR;
}


local void _hoops_HPHPS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				owner,
	_hoops_APHPS *		data)
{

	Shell *					_hoops_SPHPR;
	ZALLOC (_hoops_SPHPR, Shell);
	_hoops_SPHPR->type = _hoops_SCIP;
	_hoops_SPHPR->_hoops_CPGPR = _hoops_PHSSR;
	_hoops_SPHPR->point_count = data->point_count;
	_hoops_SPHPR->_hoops_SPHA = -1;				/* _hoops_HAR _hoops_AISP _hoops_GAPR */
	_hoops_SPHPR->face_count = data->face_count;

	_hoops_SPHPR->_hoops_GSAPA = true;
	_hoops_SPHPR->face_list_length = data->face_list_length;

	if (data->_hoops_ISSIH) {
		_hoops_SPHPR->polyhedron_flags |= PHF_POINTS_BY_REFERENCE|PHF_SHELL_FACE_LIST_BY_REFERENCE;
		_hoops_SPHPR->points = (Point *)data->points;
		_hoops_SPHPR->face_list = (int *)data->face_list;
	}
	else {
		if (data->point_count > 0) {
			ALLOC_ARRAY_ALIGNED (_hoops_SPHPR->points, data->point_count, Point, 16);
			_hoops_AIGA (data->points, data->point_count, Point, _hoops_SPHPR->points);
		}
		else
			_hoops_SPHPR->points = null;

		if (_hoops_SPHPR->face_list_length > 0)
			_hoops_SPHPR->face_list = (int *)HI_Clone_Anything ((void *)data->face_list, data->face_list_length * (long)sizeof(int));
		else
			_hoops_SPHPR->face_list = null;
	}

	if (data->tristrips != null) {
		if (data->_hoops_IGSSR == 0)
			_hoops_SPHPR->tristrips = data->tristrips;
		else {
			/* _hoops_AIAH _hoops_HCHRC _hoops_RRP _hoops_IS _hoops_ACAHP _hoops_IPS */
			_hoops_SPHPR->tristrips = (Tristrip *)
				HI_Clone_Anything ((void *)data->tristrips, sizeof(Tristrip));

			_hoops_SPHPR->tristrips->lengths = (int *)HI_Clone_Anything ((void *)data->tristrips->lengths,
																  sizeof(int) * data->tristrips->_hoops_PHHA);

			_hoops_SPHPR->tristrips->_hoops_AIHA = (int *)HI_Clone_Anything ((void *)data->tristrips->_hoops_AIHA,
																		 sizeof(int) * data->tristrips->total);

			if (data->tristrips->face_indices)
				_hoops_SPHPR->tristrips->face_indices = (int *)HI_Clone_Anything ((void *)data->tristrips->face_indices,
																		   sizeof(int) * data->tristrips->total);
		}
		_hoops_SPHPR->_hoops_ACRHR = _hoops_SRSCC;
		_hoops_SPHPR->polyhedron_flags |= _hoops_PGAHR;
	}

	_hoops_SPHPR = _hoops_PPHPS (_hoops_RIGC, owner, _hoops_SPHPR, data->_hoops_SHCIH);

	if (_hoops_SPHPR != null) {
		data->_hoops_SPHPR = _hoops_SPHPR;
		++data->_hoops_IGSSR;
	}
}



local bool _hoops_IPHPS (
	int				_hoops_PGRIH,
	int const *		_hoops_ARRI) {
	int const *		_hoops_CPHPS;
	int const *		_hoops_SPHPS;
	int				_hoops_APPH = 0;
	int				length = 0;

	/* _hoops_PPPA _hoops_RHIR _hoops_ARR _hoops_HIS _hoops_SR _hoops_ACPA _hoops_RSH _hoops_GSGS _hoops_IS _hoops_CCPP */
	_hoops_CPHPS = _hoops_ARRI;
	_hoops_SPHPS = _hoops_ARRI + _hoops_PGRIH;
	for (_hoops_CPHPS = _hoops_ARRI; _hoops_CPHPS < _hoops_SPHPS; _hoops_CPHPS += length + 1) {
		length = *_hoops_CPHPS;
		if (length < 0) /* _hoops_HAHCP */
			length = -length;
		/* _hoops_AGHR(_hoops_SPCC > 2) */
		_hoops_APPH += length - 2;
	}
	if (_hoops_CPHPS > _hoops_SPHPS) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_COUNT,
				Sprintf_D (null, "final tristrip runs past declared total length of %d", _hoops_PGRIH));
		return false;
	}
	return true;
}


local bool _hoops_GHHPS (
	_hoops_APHPS *	data) {

	if (data->point_count < 0) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_COUNT, "'point_count' is negative");
		return false;
	}

	if (data->face_list_length > 0) {
		if (!HI_Validate_Face_List (data->point_count, data->face_list_length, data->face_list,
									&data->face_count))
			return false;
	}
	else if (data->tristrips != null) {
		Tristrip const *		ts = data->tristrips;

		if (ts->face_indices) {
			int		_hoops_RPPHR = 0;
			do {
				int				_hoops_PHHA = ts->_hoops_PHHA;
				int *			lengths = ts->lengths;
				int *			fi = ts->face_indices;

				while (_hoops_PHHA-- > 0) {
					int			length = *lengths++;

					if (length < 0)		/* _hoops_HAHCP */
						length = -length;
					length -= 2;

					fi += 2;
					while (length-- > 0) {
						if (_hoops_RPPHR < *fi)
							_hoops_RPPHR = *fi;
						++fi;
					}
				}
			} while ((ts = ts->next) != null);

			data->face_count = _hoops_RPPHR + 1;
		}
		else
			data->face_count = ts->total - 2*ts->_hoops_PHHA;
	}
	else
		data->face_count = 0;

	data->_hoops_SHCIH = true; /* _hoops_CCGR _hoops_GIPCR _hoops_IAII */

	if (data->point_count != 0) {
		Point const	*point = data->points,
										*end = point + data->point_count;

		do if (point->z != 0.0f) {
			data->_hoops_SHCIH = false;
			break;
		} _hoops_RGGA (++point == end);
	}

	return true;
}

struct _hoops_HRHGA {
	int *	indices;
	int		_hoops_SAHI;
	int		_hoops_GPHI;
};


#if _hoops_GPHPS
/* _hoops_IGRIR _hoops_IRS _hoops_SCPH _hoops_IS _hoops_PCCP _hoops_APRS _hoops_HSP.
 * _hoops_HRHII _hoops_SGS _hoops_RH _hoops_SCPH _hoops_ACPAA _hoops_SPR _hoops_ISHA _hoops_CCA _hoops_RH _hoops_HSP */
local void _hoops_RHHPS(_hoops_HRHGA alter *f, int a, int b, int c) {
	int _hoops_HPCSA[3];
	int _hoops_AHHPS[2];
	int *temp;
	int i, j, k;
	int first, _hoops_SSAC;
	bool _hoops_PHHPS;

	if (f->_hoops_GPHI == 0) {
		f->_hoops_GPHI = 3;
		f->indices[0] = a;
		f->indices[1] = b;
		f->indices[2] = c;
		return;
	}

	_hoops_HPCSA[0] = a;
	_hoops_HPCSA[1] = b;
	_hoops_HPCSA[2] = c;
	for (j = 0; j < 3; j++) {
		_hoops_PHHPS = true;
		for (i = 0; i < f->_hoops_GPHI; i++) {
			if (f->indices[i] == _hoops_HPCSA[j]) _hoops_PHHPS = false;
		}
		if (_hoops_PHHPS) {
			if (f->_hoops_GPHI == f->_hoops_SAHI) {
				/* _hoops_IRCH _hoops_RH _hoops_PSPI _hoops_CRPR */
				ALLOC_ARRAY(temp, 2 * f->_hoops_SAHI, int);
				_hoops_AIGA(f->indices, f->_hoops_GPHI, int, temp);
				FREE_ARRAY(f->indices, f->_hoops_SAHI, int);
				f->indices = temp;
				f->_hoops_SAHI *= 2;
			}

			/* _hoops_RH _hoops_CCAH _hoops_GPHA _hoops_HGPHA _hoops_GAPA _hoops_RH _hoops_PGCR _hoops_GIHA _hoops_IIGR _hoops_RH _hoops_GCSP _hoops_ISHA */
			temp = _hoops_AHHPS;
			for (i = 0; i < 3; i++) {
				if (i != j)
				   *temp++ = i;
			}
			first = f->indices[0];
			_hoops_SSAC = f->indices[f->_hoops_GPHI - 1];
			if ((first == _hoops_AHHPS[0] &&
				 _hoops_SSAC  == _hoops_AHHPS[1]) ||
				(_hoops_SSAC  == _hoops_AHHPS[0] &&
				 first == _hoops_AHHPS[1])) {
				f->indices[f->_hoops_GPHI++] = _hoops_HPCSA[j];
				return;
			}
			for (i = 0; i < f->_hoops_GPHI - 1; i++) {
				first = f->indices[i];
				_hoops_SSAC = f->indices[i + 1];
				if (first == _hoops_AHHPS[0] && _hoops_SSAC  == _hoops_AHHPS[1] ||
					_hoops_SSAC  == _hoops_AHHPS[0] && first == _hoops_AHHPS[1]) {
					f->_hoops_GPHI++;
					for (k = f->_hoops_GPHI - 1; k > i + 1; k--)
						f->indices[k + 1] = f->indices[k];
					f->indices[i + 1] = _hoops_HPCSA[j];
					return;
				}
			}
		}
	}
}
#endif


#if _hoops_GPHPS
/* _hoops_HRRGR _hoops_RH _hoops_HSP _hoops_HIGR _hoops_HII _hoops_RH _hoops_CCGI _hoops_HIGR (_hoops_PICAA) */
local bool _hoops_HHHPS (
	int					_hoops_PGRIH,
	int const *			_hoops_ARRI,
	int alter *			_hoops_IHHPS;
	int alter **		_hoops_CHHPS) {
	int const *			_hoops_CPHPS;
	int const *			_hoops_SPHPS;
	int alter *			_hoops_CCPHC;
	int					_hoops_APPH = 0;
	int					length = 0;
	int					i;

	/* _hoops_PPPA _hoops_RHIR _hoops_ARR _hoops_HIS _hoops_SR _hoops_ACPA _hoops_RSH _hoops_GSGS _hoops_IS _hoops_CCPP */
	_hoops_CPHPS = _hoops_ARRI;
	_hoops_SPHPS = _hoops_ARRI + _hoops_PGRIH;
	for (_hoops_CPHPS = _hoops_ARRI; _hoops_CPHPS < _hoops_SPHPS; _hoops_CPHPS += length + 1) {
		length = *_hoops_CPHPS;
		if (length < 0) /* _hoops_HAHCP */
			length = -length;
		/* _hoops_AGHR(*_hoops_SHHPS > 2); */
		_hoops_APPH += length - 2;
	}
	*_hoops_IHHPS = _hoops_APPH * 4;
	ALLOC_ARRAY(*_hoops_CHHPS, *_hoops_IHHPS, int);

	/* _hoops_PPPA _hoops_RHIR _hoops_GICS _hoops_IS _hoops_IGRC _hoops_ARPR _hoops_RH _hoops_HSP _hoops_HIGR */
	_hoops_CPHPS = _hoops_ARRI;
	_hoops_SPHPS = _hoops_ARRI + _hoops_PGRIH;
	_hoops_CCPHC = *_hoops_CHHPS;
	for (_hoops_CPHPS = _hoops_ARRI; _hoops_CPHPS < _hoops_SPHPS; _hoops_CPHPS += length + 1) {
		bool				_hoops_SICPR = false;

		length	= *_hoops_CPHPS;
		if (length < 0) {		/* _hoops_HAHCP */
			length = -length;
			_hoops_SICPR = true;
		}
		/* _hoops_AGHR(*_hoops_SHHPS > 2); */
		for (i = 3; i < (length + 1); i++) {
			_hoops_CCPHC[0] = 3;
			if (_hoops_SICPR) {
				_hoops_CCPHC[1] = _hoops_CPHPS[1];
				_hoops_CCPHC[2] = _hoops_CPHPS[i-1];
				_hoops_CCPHC[3] = _hoops_CPHPS[i];
			}
			else if (i & 0x1) { /* _hoops_RPP _hoops_HAS _hoops_HRGR _hoops_PISC */
				_hoops_CCPHC[1] = _hoops_CPHPS[i-2];
				_hoops_CCPHC[2] = _hoops_CPHPS[i-1];
				_hoops_CCPHC[3] = _hoops_CPHPS[i];
			}
			else {
				_hoops_CCPHC[1] = _hoops_CPHPS[i];
				_hoops_CCPHC[2] = _hoops_CPHPS[i-1];
				_hoops_CCPHC[3] = _hoops_CPHPS[i-2];
			}
			_hoops_CCPHC += 4;
		}
	}

	return true;
}


/* _hoops_HRRGR _hoops_RH _hoops_HSP _hoops_HIGR _hoops_HII _hoops_RH _hoops_AASGR (_hoops_RHRCP) */
local bool _hoops_GIHPS (
	Tristrip const *	ts,
	int alter *			_hoops_IHHPS,
	int alter **		_hoops_CHHPS) {
	int					face_list_length;
	int *				face_list;
	_hoops_HRHGA *			faces;
	int					i, j, fid, _hoops_RIHPS, _hoops_AIHPS, _hoops_PIHPS;
	int *				_hoops_RGCHI;
	int *				_hoops_HIHPS;
	Tristrip const *	_hoops_CPCR;

	/* _hoops_GGI _hoops_AIPH _hoops_SRGR _hoops_GGR _hoops_AGIR _hoops_SR _hoops_RIARR _hoops_PGGPR */
	*_hoops_IHHPS = 0;
	*_hoops_CHHPS = null;

	/* _hoops_CGIC _hoops_CIAS _hoops_HSP _hoops_CIHA */
	_hoops_RIHPS = 0;
	for (_hoops_CPCR = ts; _hoops_CPCR != null; _hoops_CPCR = _hoops_CPCR->next) {
		if (_hoops_CPCR->face_indices) {
			int				_hoops_PHHA = _hoops_CPCR->_hoops_PHHA;
			int *			lengths = _hoops_CPCR->lengths;
			int *			fi = _hoops_CPCR->face_indices;

			while (_hoops_PHHA-- > 0) {
				int				length = *lengths++;

				if (length < 0) /* _hoops_HAHCP */
					length = -length;
				length -= 2;

				fi += 2;

				while (length-- > 0) {
					if ((fid = *fi++) > _hoops_RIHPS)
						_hoops_RIHPS = fid;
				}
			}
		}
		else
			_hoops_RIHPS += _hoops_CPCR->total - 2*_hoops_CPCR->_hoops_PHHA;
	}

	_hoops_AIHPS = _hoops_RIHPS + 1;
	ALLOC_ARRAY(faces, _hoops_AIHPS, _hoops_HRHGA);
	for (i = 0; i < _hoops_AIHPS; i++) {
		ALLOC_ARRAY(faces[i].indices, 4, int);
		faces[i]._hoops_SAHI = 4;
		faces[i]._hoops_GPHI = 0;
	}

	for (_hoops_CPCR = ts; _hoops_CPCR != null; _hoops_CPCR = _hoops_CPCR->next) {
		int				_hoops_PHHA = _hoops_CPCR->_hoops_PHHA;
		int *			lengths = _hoops_CPCR->lengths;
		int *			vi = _hoops_CPCR->_hoops_AIHA;
		int *			fi = _hoops_CPCR->face_indices;
		int				face = -1;

		while (_hoops_PHHA-- > 0) {
			int			length = *lengths++;
			bool	_hoops_SICPR = false;
			int			first = *vi;
			bool	_hoops_CIPAR = false;

			if (length < 0) {	/* _hoops_HAHCP */
				length = -length;
				_hoops_SICPR = true;
			}
			length -= 2;
			if (fi) fi += 2;

			while (length-- > 0) {
				if (fi)
					face = *fi;
				else
					face++;

				if (_hoops_SICPR)
					_hoops_RHHPS (&faces[face], first, vi[1], vi[2]);
				else if (_hoops_CIPAR)
					_hoops_RHHPS (&faces[face], vi[1], vi[0], vi[2]);
				else
					_hoops_RHHPS (&faces[face], vi[0], vi[1], vi[2]);

				_hoops_CIPAR = !_hoops_CIPAR;
				vi++;
				fi++;
			}

			vi += 2;
		}
	}

	_hoops_PIHPS = 0;
	for (i = 0; i < _hoops_AIHPS; i++) {
		if (faces[i]._hoops_GPHI == 0)
			return false;
		_hoops_PIHPS += faces[i]._hoops_GPHI;
	}

	face_list_length = _hoops_PIHPS + _hoops_AIHPS;
	ALLOC_ARRAY(face_list, face_list_length, int);
	_hoops_HIHPS = face_list + face_list_length;
	for (_hoops_RGCHI = face_list, i = 0; _hoops_RGCHI < _hoops_HIHPS; _hoops_RGCHI += *_hoops_RGCHI + 1, i++) {
		_hoops_RGCHI[0] = faces[i]._hoops_GPHI;
		for (j = 0; j < _hoops_RGCHI[0]; j++) {
			_hoops_RGCHI[j + 1] = faces[i].indices[j];
		}
		FREE_ARRAY(faces[i].indices, faces[i]._hoops_SAHI, int);
	}
	FREE_ARRAY(faces, _hoops_AIHPS, _hoops_HRHGA);

	*_hoops_IHHPS = face_list_length;
	*_hoops_CHHPS = face_list;

	return true;
}
#endif


#define _hoops_IIHPS 4096  //_hoops_PIHA _hoops_SHH _hoops_PRGI

local bool _hoops_CIHPS (
	int					_hoops_PGRIH,
	int const *			_hoops_ARRI,
	int					_hoops_HGRIH,
	int const *			_hoops_IGRIH,
	Tristrip alter *	ts)
{
	int					_hoops_APPH;
	const int *			_hoops_CPHPS;
	const int *			_hoops_SPHPS;
	alter int *			_hoops_SIHPS;
	alter int *			_hoops_ACI;
	alter int *			_hoops_IHAHH;
	int					length = 0;
	int					center = 0;

	UNREFERENCED (_hoops_HGRIH);
	_hoops_AAPHR (ts->face_attributes);

	/* _hoops_SRS _hoops_RPR _hoops_RH _hoops_PHI _hoops_IIGR _hoops_CCGI */
	_hoops_SPHPS = _hoops_ARRI + _hoops_PGRIH;

	ts->_hoops_PHHA = 0;
	ts->total = 0;
	_hoops_CPHPS = _hoops_ARRI;
	while (_hoops_CPHPS < _hoops_SPHPS) {
		length = *_hoops_CPHPS;
		if (length < 0) {			/* _hoops_HAHCP */
			length = -length;
			_hoops_CPHPS += length + 1;
			ts->_hoops_PHHA += length-2;
			ts->total += 3*(length-2);
		}
		else {
			_hoops_CPHPS += length + 1;
			while (length > _hoops_IIHPS) {
				ts->_hoops_PHHA++;
				ts->total += _hoops_IIHPS;
				length -= _hoops_IIHPS-2;
			}
			ts->_hoops_PHHA++;
			ts->total += length;
		}
	}

	if (ts->_hoops_PHHA)
		ALLOC_ARRAY (ts->lengths, ts->_hoops_PHHA, int);
	ts->lengths_allocated = ts->_hoops_PHHA;
	if (ts->total)
		ALLOC_ARRAY (ts->_hoops_AIHA, ts->total, int);
	ts->_hoops_IPII = ts->total;
	if (_hoops_IGRIH != null) {
		ALLOC_ARRAY (ts->face_indices, ts->total, int);
		ts->_hoops_SGAHR = ts->total;
	}
	else {
		ts->face_indices = null;
		ts->_hoops_SGAHR = 0;
	}
	ts->_hoops_RAHH |= _hoops_AAHH;

	_hoops_SIHPS = ts->lengths;
	_hoops_ACI = ts->_hoops_AIHA;
	_hoops_IHAHH = ts->face_indices;

	_hoops_APPH = 0;
	for (_hoops_CPHPS = _hoops_ARRI; _hoops_CPHPS < _hoops_SPHPS;) {
		int i;
		length = *_hoops_CPHPS;

		if (length < 0)	{		/* _hoops_HAHCP */
			length = -length;

			_hoops_CPHPS++;
			center = *_hoops_CPHPS++;
			length -= 2;
			for (i=0; i<length; i++) {
				*_hoops_SIHPS++ = 3;

				if (_hoops_IGRIH != null) {
					*_hoops_IHAHH++ = 0;
					*_hoops_IHAHH++ = 0;
					*_hoops_IHAHH++ = _hoops_IGRIH[_hoops_APPH++]; /* _hoops_RCRP _hoops_HSP _hoops_CRSRR _hoops_RPP _hoops_SR _hoops_HS _hoops_SCH... */
				}

				*_hoops_ACI++ = center;
				*_hoops_ACI++ = *_hoops_CPHPS++;
				*_hoops_ACI++ = *_hoops_CPHPS;
			}
			_hoops_CPHPS++;
		}
		else {
			_hoops_CPHPS++;  //_hoops_SRGR _hoops_CHR _hoops_HA _hoops_GCSS _hoops_GGR "_hoops_SPCC"

			while (length > _hoops_IIHPS) {
				*_hoops_SIHPS++ = _hoops_IIHPS;
				*_hoops_ACI++ = *_hoops_CPHPS++;
				if (_hoops_IGRIH != null)
					*_hoops_IHAHH++ = 0;
				*_hoops_ACI++ = *_hoops_CPHPS++;
				if (_hoops_IGRIH != null)
					*_hoops_IHAHH++ = 0;

				for (i = 0; i < _hoops_IIHPS - 2; i++) {
					*_hoops_ACI++ = *_hoops_CPHPS++;
					if (_hoops_IGRIH != null)
						*_hoops_IHAHH++ = _hoops_IGRIH[_hoops_APPH++]; /* _hoops_RCRP _hoops_HSP _hoops_CRSRR _hoops_RPP _hoops_SR _hoops_HS _hoops_SCH... */
				}
				_hoops_CPHPS -= 2;
				length -= _hoops_IIHPS-2;
			}

			*_hoops_SIHPS++ = length;

			*_hoops_ACI++ = *_hoops_CPHPS++;
			if (_hoops_IGRIH != null) *_hoops_IHAHH++ = 0;
			*_hoops_ACI++ = *_hoops_CPHPS++;
			if (_hoops_IGRIH != null) *_hoops_IHAHH++ = 0;

			length -= 2;
			while (length-- > 0) {
				*_hoops_ACI++ = *_hoops_CPHPS++;
				if (_hoops_IGRIH != null)
					*_hoops_IHAHH++ = _hoops_IGRIH[_hoops_APPH++]; /* _hoops_RCRP _hoops_HSP _hoops_CRSRR _hoops_RPP _hoops_SR _hoops_HS _hoops_SCH... */
#if 0
				else
					*_hoops_IHAHH++ = _hoops_APPH++;		/* ..._hoops_IAII _hoops_AGGHA _hoops_SPR _hoops_HII _hoops_CSRRS */
#endif
			}
		}
	}

	ts->next = null;

	return true;
}


GLOBAL_FUNCTION Key HI_Insert_Shell (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	int						point_count,
	Point const *			points,
	int						face_list_length,
	int const *				face_list,
	bool					_hoops_ISSIH)
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_APHPS			data;
	ZERO_STRUCT(&data, _hoops_APHPS);
	data.point_count = point_count;
	data.points = points;
	data.face_list_length = face_list_length;
	data.face_list = face_list;
	data._hoops_ISSIH = _hoops_ISSIH;

	if (_hoops_GHHPS (&data))
		_hoops_HPHPS(_hoops_RIGC, item, &data);

	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data._hoops_SPHPR);

	return _hoops_CHSSR;
}



HC_INTERFACE Key HC_CDECL HC_Insert_Shell (
	int						point_count,
	Point const *			points,
	int						face_list_length,
	int const *				face_list)
{
	_hoops_PAPPR context("Insert_Shell");

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Shell (context, target, point_count, points, face_list_length, face_list, false);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		int		count2 = point_count;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		if (point_count)
			HI_Dump_Code (Sprintf_D (null, "HC_POINT * points = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", point_count));
		else
			HI_Dump_Code ("HC_POINT * points = 0;\n");
		if (face_list_length)
			HI_Dump_Code (Sprintf_D (null, "int * list = (int*) malloc(sizeof(int)*%d);\n", face_list_length));
		else
			HI_Dump_Code ("int * list = 0;\n");
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].x = %.6ff;	 ", count2, points[count2].x));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].y = %.6ff;	 ", count2, points[count2].y));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].z = %.6ff;\n", count2, points[count2].z));
		}
		count2 = face_list_length;
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (Sprintf_DD (null, "list[%d] = %d;\n", count2, face_list[count2]));
		}
		HI_Dump_Code (Sprintf_DD (null, "DEFINE (HC_Insert_Shell (%d, points, %d, list), ", point_count, face_list_length));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
		HI_Dump_Code ("free (points);\n");
		HI_Dump_Code ("free (list);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	return _hoops_CHSSR;
}


HC_INTERFACE Key HC_CDECL HC_Insert_Shell_By_Ref (
	int						point_count,
	Point const	*			points,
	int						face_list_length,
	int const*				face_list)
{
	_hoops_PAPPR context("Insert_Shell_By_Ref");

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Shell (context, target, point_count, points, face_list_length, face_list, true);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		int		count2 = point_count;

		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		if (point_count)
			HI_Dump_Code (Sprintf_D (null, "HC_POINT * points = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", point_count));
		else
			HI_Dump_Code ("HC_POINT * points = 0;\n");
		if (face_list_length)
			HI_Dump_Code (Sprintf_D (null, "int * list = (int*) malloc(sizeof(int)*%d);\n", face_list_length));
		else
			HI_Dump_Code ("int * list = 0;\n");
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].x = %.6ff;	 ", count2, points[count2].x));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].y = %.6ff;	 ", count2, points[count2].y));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].z = %.6ff;\n", count2, points[count2].z));
		}
		count2 = face_list_length;
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (Sprintf_DD (null, "list[%d] = %d;\n", count2, face_list[count2]));
		}
		HI_Dump_Code ("/* HC_Insert_Shell_By_Ref */\n");
		HI_Dump_Code (Sprintf_DD (null, "DEFINE (HC_KInsert_Shell (%d, points, %d, list), ", point_count, face_list_length));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
		HI_Dump_Code ("free (points);\n");
		HI_Dump_Code ("free (list);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	return _hoops_CHSSR;
}


GLOBAL_FUNCTION Key HI_Insert_Shell_By_Tristrips (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	int						point_count,
	Point const	*			points,
	int						_hoops_PGRIH,
	int const *				_hoops_ARRI,
	int						_hoops_HGRIH,
	int const *				_hoops_IGRIH)
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_APHPS			data;
	ZERO_STRUCT(&data, _hoops_APHPS);
	data.point_count = point_count;
	data.points = points;

	if (_hoops_PGRIH) {
		Tristrip *	ts;
		ZALLOC (ts, Tristrip);
		_hoops_ICAI (ts);
		_hoops_CIHPS (_hoops_PGRIH, _hoops_ARRI, _hoops_HGRIH, _hoops_IGRIH, ts);
		data.tristrips = ts;
	}

#if _hoops_GPHPS
	if (_hoops_HGRIH == 0) {
		if (!_hoops_HHHPS (_hoops_PGRIH, _hoops_ARRI,
			&(data.face_list_length), (int **)&(data.face_list))) {
			if (_hoops_ISAI (data.tristrips) == 0)
				HI_Free_Tristrip (data.tristrips);
			_hoops_IRRPR();
			return _hoops_SHSSR;
		}
	}
	else {
		if (!_hoops_GIHPS (ts, &(data.face_list_length), (int **)&(data.face_list))) {
			if (_hoops_ISAI (data.tristrips) == 0)
				HI_Free_Tristrip (data.tristrips);
			_hoops_IRRPR();
			return _hoops_SHSSR;
		}
	}
#endif

	if (_hoops_GHHPS (&data))
		_hoops_HPHPS (_hoops_RIGC, item, &data);

	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR == 0) {
		if (_hoops_ISAI (data.tristrips) == 0)
			HI_Free_Tristrip (data.tristrips);
	}
	else
		_hoops_CHSSR = _hoops_AIRIR (data._hoops_SPHPR);

	return _hoops_CHSSR;
}



HC_INTERFACE Key HC_CDECL HC_Insert_Shell_By_Tristrips (
	int						point_count,
	Point const	*			points,
	int						_hoops_PGRIH,
	int const *				_hoops_ARRI,
	int						_hoops_HGRIH,
	int const *				_hoops_IGRIH)
{
	_hoops_PAPPR context("Insert_Shell_By_Tristrips");

	if (!_hoops_IPHPS(_hoops_PGRIH, _hoops_ARRI))
		return _hoops_SHSSR;

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Shell_By_Tristrips (context, target,
			point_count, points, _hoops_PGRIH, _hoops_ARRI, _hoops_HGRIH, _hoops_IGRIH);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		int		pcount = point_count;
		int		_hoops_GCHPS = _hoops_PGRIH;
		int		fcount = _hoops_HGRIH;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		if (point_count)
			HI_Dump_Code (Sprintf_D (null, "HC_POINT * points = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", point_count));
		else
			HI_Dump_Code ("HC_POINT * points = 0;\n");
		if (_hoops_PGRIH)
			HI_Dump_Code (Sprintf_D (null, "int * list = (int*) malloc(sizeof(int)*%d);\n", _hoops_PGRIH));
		else
			HI_Dump_Code ("int * list = 0;\n");
		if (_hoops_HGRIH)
			HI_Dump_Code (Sprintf_D (null, "int * list2 = (int*) malloc(sizeof(int)*%d);\n", _hoops_HGRIH));
		else
			HI_Dump_Code ("int * list2 = 0;\n");
		while (pcount-- != 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].x = %.6ff;	 ", pcount, points[pcount].x));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].y = %.6ff;	 ", pcount, points[pcount].y));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].z = %.6ff;\n", pcount, points[pcount].z));
		}
		while (_hoops_GCHPS-- != 0) {
			HI_Dump_Code (Sprintf_DD (null, "list[%d] = %d;\n", _hoops_GCHPS, _hoops_ARRI[_hoops_GCHPS]));
		}
		while (fcount-- != 0) {
			HI_Dump_Code (Sprintf_DD (null, "list2[%d] = %d;\n", fcount, _hoops_IGRIH[fcount]));
		}
		HI_Dump_Code (Sprintf_D (null, "DEFINE (HC_Insert_Shell_By_Tristrips (%d, points, ", point_count));
		HI_Dump_Code (Sprintf_DD (null, "%d, list, %d, list2), ", _hoops_PGRIH, _hoops_HGRIH));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
		HI_Dump_Code ("free (points);\n");
		HI_Dump_Code ("free (list);\n");
		HI_Dump_Code ("free (list2);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	return _hoops_CHSSR;
}




local void _hoops_RCHPS (
	_hoops_AIGPR *	_hoops_RIGC,
	Shell alter **			_hoops_CPSIH,
	Shell alter **			victim)
{
	if (*_hoops_CPSIH) {
		/* _hoops_RH _hoops_CPAP _hoops_CSAP _hoops_CGI _hoops_HPP _hoops_SIC */
		switch ((*_hoops_CPSIH)->type) {
			case _hoops_HSIP:
			case _hoops_CSIP:
			case _hoops_ASIP:
			case _hoops_GSIP:
			case _hoops_PRCP: {
				HI_Convert_To_Shell (_hoops_RIGC, null, (Geometry *)*_hoops_CPSIH, _hoops_CPSIH, victim);
			} return;
			default:
				break;
		}
	}

	_hoops_SIRIR const *	_hoops_ACHPS = _hoops_RIGC->open_list;
	if (_hoops_ACHPS == null) {
		; // _hoops_ISAP
	}
	else if (_hoops_ACHPS->_hoops_GCRIR == _hoops_HCRIR) {
		switch (_hoops_ACHPS->info.geometry._hoops_IGRPR->type) {
		/* _hoops_RH _hoops_CPAP _hoops_CSAP _hoops_IGS */
			case _hoops_HSIP:
			case _hoops_CSIP:
			case _hoops_ASIP:
			case _hoops_GSIP:
			case _hoops_PRCP: {
				HI_Convert_To_Shell (_hoops_RIGC, null, _hoops_ACHPS->info.geometry._hoops_IGRPR, _hoops_CPSIH, victim);
			} return;
			default:
				break;
		}
	}
	else if (_hoops_ACHPS->_hoops_GCRIR == _hoops_RSRIR) {
		_hoops_HPAH *	thing = _hoops_ACHPS->info._hoops_PRSI._hoops_IGRPR;
		int			_hoops_PCHPS = _hoops_ACHPS->info._hoops_PRSI.offset;

		switch (thing->type) {
			case _hoops_IRCP: {
				_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)thing;

				if (_hoops_PCHPS == 0) {
					HE_ERROR (HEC_INTERNAL_ERROR, HES_INVALID_KEY, "lod level 0 open for segments is not valid");
					return;
				}

				_hoops_PGAIR *	_hoops_HGAIR = _hoops_SRCP->_hoops_SSRIR();
				if (_hoops_HGAIR != null)
					*_hoops_CPSIH = (Shell *)(_hoops_HGAIR->data[_hoops_PCHPS - 1]);
			} break;

			case _hoops_SCIP:
			case _hoops_GSIP: {
				Polyhedron *	phon = (Polyhedron *)thing;

				if (_hoops_PCHPS == 0)
					*_hoops_CPSIH = (Shell *)phon;
				else if (phon->_hoops_HGAIR == null)
					*_hoops_CPSIH = null;
				else
					*_hoops_CPSIH = (Shell *)(phon->_hoops_HGAIR->data[_hoops_PCHPS - 1]);
			} break;

			default:
				HE_ERROR (HEC_INTERNAL_ERROR, HES_INVALID_KEY,
						"currently open LOD does not refer to a valid shell");
		}
	}
}


local void _hoops_HCHPS (
	_hoops_AIGPR *	_hoops_RIGC,
	Key						key,
	int						_hoops_SSPAR,
	int	alter *				_hoops_RGGCA,
	int	alter *				_hoops_ICHPS)
{
	Shell alter *			_hoops_SPHPR = null;
	Shell alter *			victim = null;
	int						used;
	int *					ptr;
	int *					end;
	int						i, length;
	int						_hoops_ISPI, _hoops_CSPI;
	_hoops_RHHPR *	e;
	_hoops_RHHPR *	_hoops_CCHPS;

	_hoops_SPHPR = (Shell alter *)_hoops_RCSSR (_hoops_RIGC, key);

	if (!_hoops_SPHPR ||
		_hoops_SPHPR->type < _hoops_AHRIR || _hoops_SPHPR->type > _hoops_PHRIR) {
		HE_ERROR (HEC_GEOMETRY, HES_INVALID_KEY, "Provided key does not refer to valid geometry.");
		return;
	}
	_hoops_RCHPS (_hoops_RIGC, &_hoops_SPHPR, &victim);
	if (_hoops_SPHPR == null ||
		_hoops_SPHPR->type != _hoops_SCIP ||
		BIT (_hoops_SPHPR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_GEOMETRY, HES_INVALID_KEY, "Provided key does not refer to a valid shell");
		return;
	}

	if (!_hoops_SPHPR->face_list) {
		if (!_hoops_SPHPR->tristrips) {
			if (_hoops_RGGCA)
				*_hoops_RGGCA = 0;	/* _hoops_RRCPR _hoops_SSCP _hoops_PSP _hoops_RSSI? */
			return;
		}
		HI_Face_List_From_Tristrips (_hoops_RIGC, _hoops_SPHPR);
	}
	else if (!_hoops_SPHPR->_hoops_GSAPA)
		HI_Repair_Shell_Edges (_hoops_RIGC, _hoops_SPHPR);

	if (!_hoops_SPHPR->_hoops_HHHPR || !_hoops_SPHPR->_hoops_SGCPR)
		HI_Create_Shell_Edges (_hoops_SPHPR, true);

	ptr = _hoops_SPHPR->face_list;
	end = ptr + _hoops_SPHPR->face_list_length;
	for (i = 0; i < _hoops_SSPAR && ptr < end; i++) {
		if (ptr[0] > 0)
			length = *ptr;
		else
			length = -(*ptr);
		ptr += length + 1;
	}
	if (i != _hoops_SSPAR) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_FACE_OFFSET,"Provided index exceeds number of faces in shell");
	}

	/* _hoops_HPGR _hoops_RGR _hoops_PPSR, _hoops_ASPR _hoops_RSSA _hoops_IS _hoops_RH _hoops_RSGI _hoops_IIGR _hoops_RH _hoops_HSP _hoops_IH _hoops_PGAP _hoops_SR _hoops_CHR
	 * _hoops_IRCC _hoops_IS _hoops_SSS _hoops_RH _hoops_HRCCP */
	used = 0;
	length = ptr[0];
	for (i = 0; i < length; i++) {
		if (i == 0)
			_hoops_ISPI = ptr[length];
		else
			_hoops_ISPI = ptr[i];
		_hoops_CSPI = ptr[i+1];
		if (_hoops_ISPI > _hoops_CSPI)
			Swap (_hoops_ISPI, _hoops_CSPI);
		e = _hoops_SPHPR->_hoops_HHHPR[_hoops_ISPI];
		_hoops_CCHPS = _hoops_SPHPR->_hoops_HHHPR[_hoops_ISPI + 1];
		while (e < _hoops_CCHPS) {
			if (e->_hoops_GIHPR == _hoops_CSPI) {
				int _hoops_SHPC = e - _hoops_SPHPR->_hoops_GRCPR;
				_hoops_CGCPR *_hoops_SCHPS = &_hoops_SPHPR->_hoops_SGCPR[_hoops_SHPC];

				if (_hoops_SCHPS->_hoops_AIIPR == _hoops_SSPAR) {
					if (_hoops_SCHPS->_hoops_HIIPR >= 0) {
						if (_hoops_ICHPS)
							*_hoops_ICHPS++ = _hoops_SCHPS->_hoops_HIIPR;
						used++;
					}
				}
				else {
					if (_hoops_SCHPS->_hoops_HIIPR != _hoops_SSPAR) {
						HE_ERROR (HEC_TRISTRIP, HES_INVALID_FACE_OFFSET,"invalid case found in internal edge_to_face array");
					}
					if (_hoops_ICHPS)
						*_hoops_ICHPS++ = _hoops_SCHPS->_hoops_AIIPR;
					used++;
				}
				break;
			}
			e++;
		}
	}

	if (_hoops_RGGCA)
		*_hoops_RGGCA = used;

	if (victim)
		HI_Au_Revoir ((_hoops_HPAH *)victim);
}


HC_INTERFACE void HC_CDECL HC_Compute_Face_Neighborhood_Si (
	Key					key,
	int					index,
	int	alter*			count)
{
	_hoops_PAPPR context("HC_Compute_Face_Neighborhood_Si");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Face_Neighborhood_Si() */\n");
	);

	_hoops_RPPPR();
	_hoops_HCHPS (context, key, index, count, null);
	_hoops_IRRPR();
}


HC_INTERFACE void HC_CDECL HC_Compute_Face_Neighborhood (
	Key						key,
	int						index,
	int	alter *				count,
	int	alter *				neighbors)
{
	_hoops_PAPPR context("HC_Compute_Face_Neighborhood");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Face_Neighborhood() */\n");
	);

	_hoops_RPPPR();
	_hoops_HCHPS (context, key, index, count, neighbors);
	_hoops_IRRPR();
}



local void _hoops_GSHPS (_hoops_AIGPR *	_hoops_RIGC, _hoops_AIHPR const * _hoops_PIHPR, Shell alter * _hoops_SPHPR);

HC_INTERFACE Key HC_CDECL HC_Generate_Shell_From_Geometry (
	Key						key,
	char const *			options)
{
	_hoops_PAPPR context("Generate_Shell_From_Geometry");

	_hoops_RPPPR();

	Geometry *	geom = (Geometry *)_hoops_RCSSR (context, key);

	Shell *	_hoops_SPHPR = null;
	Shell *	_hoops_RSHPS = null;
	Key		_hoops_ACHPA = _hoops_SHSSR;

	if (!geom ||
		geom->type < _hoops_AHRIR || geom->type > _hoops_PHRIR) {
		HE_ERROR (HEC_GEOMETRY, HES_INVALID_KEY, "Provided key does not refer to valid geometry.");
		goto Release;
	}

	if (geom->type == _hoops_SCIP) {
		HE_WARNING (HEC_GEOMETRY, HES_INVALID_KEY, "Provided key is already a shell.");
		goto Release;
	}

	HI_Convert_To_Shell (context, options, geom, &_hoops_SPHPR, &_hoops_RSHPS);

	if (!_hoops_RSHPS)
		_hoops_SPHPR = (Shell *)HI_Copy_Geometry (context, (Geometry *)_hoops_SPHPR);
	else
		_hoops_SPHPR = _hoops_RSHPS;

	if (context->open_list != null &&
		(context->open_list->_hoops_GCRIR == _hoops_RCRIR ||
		 context->open_list->_hoops_GCRIR == _hoops_RSRIR) ||
		HI_Find_Our_Open (context)) {
		_hoops_SPHPR = _hoops_PPHPS (context, (_hoops_HPAH *)context->open_list, _hoops_SPHPR, false);
		if (geom->type == _hoops_GSIP)
			_hoops_GSHPS (context, (_hoops_AIHPR const *)geom, _hoops_SPHPR);
		_hoops_ACHPA = _hoops_AIRIR (_hoops_SPHPR);
	}
	else
		HI_Au_Revoir ((_hoops_HPAH *)_hoops_SPHPR);

  Release:
	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Generate_Shell_From_Geometry (LOOKUP (%D),", key));
		HI_Dump_Code (Sprintf_S (null, "%S), ", options));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_ACHPA));
	);

	return _hoops_ACHPA;
}




local void _hoops_ASHPS (int * face, int p, int where)
{
	int	length = face[0];
	for (int i = length; i > where; i--)
		face[i+1] = face[i];
	face[where+1] = p;
	face[0]++;
}

local bool _hoops_PSHPS (int * face, int _hoops_GGIAR, int p1, int p2)
{
	if (face[0] == 0) {
		face[0] = 3;
		face[1] = _hoops_GGIAR;
		face[2] = p1;
		face[3] = p2;
		return true;
	}
	else {
		int length = face[0];
		for (int i = 0; i < length; i++) {
			int		_hoops_AIPCP, f1;
			if (i == 0)
				_hoops_AIPCP = face[length]; /* _hoops_ARGAR _hoops_AARI _hoops_IS _hoops_CGHI _hoops_GPHA _hoops_GGR _hoops_HSP */
			else
				_hoops_AIPCP = face[i];

			f1 = face[i+1];
			if (_hoops_GGIAR == f1 && p1 == _hoops_AIPCP) {
				_hoops_ASHPS(face, p2, i);
				return true;
			}
			else if (p1 == f1 && p2 == _hoops_AIPCP) {
				_hoops_ASHPS(face, _hoops_GGIAR, i);
				return true;
			}
			else if (p2 == f1 && _hoops_GGIAR == _hoops_AIPCP) {
				_hoops_ASHPS(face, p1, i);
				return true;
			}
		}
		return false;
	}
}

struct _hoops_HSHPS{
	int *	face;
	int		_hoops_GGIAR, p1, p2;
};

typedef VList<_hoops_HSHPS const *> _hoops_ISHPS;

local void 	_hoops_CSHPS (
	_hoops_ISHPS *	_hoops_SSHPS,
	int *						face,
	int							_hoops_GGIAR,
	int							p1,
	int							p2) {
	_hoops_HSHPS *		di;

	ALLOC(di, _hoops_HSHPS);
	di->face = face;
	di->_hoops_GGIAR = _hoops_GGIAR;
	di->p1 = p1;
	di->p2 = p2;
	_hoops_SSHPS->AddFirst(di);
}


local bool _hoops_GGIPS (_hoops_ISHPS * _hoops_SSHPS) {
	_hoops_HSHPS const *	di;
	bool				_hoops_IHRPA;

	while (_hoops_SSHPS->Count()) {
		_hoops_IHRPA = false;

		_hoops_SSHPS->ResetCursor();
		/* _hoops_RGHH _hoops_CPS _hoops_RAS _hoops_RH _hoops_SRS _hoops_GGR _hoops_RH _hoops_HIGR */
		do {
			di = _hoops_SSHPS->PeekCursorNext();
			if (di && _hoops_PSHPS (di->face, di->_hoops_GGIAR, di->p1, di->p2)) {
				_hoops_SSHPS->RemoveCursorNext();
				FREE (di, _hoops_HSHPS);
				_hoops_IHRPA = true;
			}
			_hoops_SSHPS->AdvanceCursor();
		} while (di);
		/* _hoops_RGHH _hoops_RH _hoops_SRS _hoops_GGR _hoops_RH _hoops_HIGR */
		di = _hoops_SSHPS->PeekFirst();
		if (_hoops_PSHPS (di->face, di->_hoops_GGIAR, di->p1, di->p2)) {
			_hoops_SSHPS->RemoveFirst();
			FREE (di, _hoops_HSHPS);
			_hoops_IHRPA = true;
		}

		if (!_hoops_IHRPA)
			return false;
	}
	return true;
}


GLOBAL_FUNCTION bool HI_Face_List_From_Tristrips (
	_hoops_AIGPR *	_hoops_RIGC,
	Shell *					_hoops_SPHPR) 
{
	int					i,j,_hoops_RGIPS,_hoops_SAHAR, length;
	Tristrip *			ts;
	int *				faces;
	int *				ptr;

	_hoops_RGIPS = 0;
	for (ts = _hoops_SPHPR->tristrips; ts != null; ts = ts->next) {
		for (i = 0; i < ts->_hoops_PHHA; i++) {
			_hoops_RGIPS += ts->lengths[i] - 2;
		}
	}
	/* _hoops_RH _hoops_HSPR _hoops_RPGP _hoops_IGIPR _hoops_SGS _hoops_RPP _hoops_RH _hoops_SRS _hoops_AASGR _hoops_SSCP
		_hoops_GPSCC, _hoops_SSIA _hoops_HCR _hoops_GRS */
	if (_hoops_SPHPR->tristrips->face_indices) {
		int							face_count = _hoops_SPHPR->face_count;
		int *						_hoops_AGIPS;
		int **						_hoops_PGIPS;
		_hoops_ISHPS *	_hoops_SSHPS = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_ISHPS)(_hoops_RIGC->memory_pool);

		ALLOC_ARRAY_CACHED (_hoops_PGIPS, face_count, int *);
		ZALLOC_ARRAY_CACHED (_hoops_AGIPS, face_count, int);
		_hoops_SPHPR->face_list_length = (face_count * 4) + (_hoops_RGIPS-face_count);
		ZALLOC_ARRAY (_hoops_SPHPR->face_list, _hoops_SPHPR->face_list_length, int);

		for (ts = _hoops_SPHPR->tristrips; ts != null; ts = ts->next) {
			j = 0;
			for (i = 0; i < ts->_hoops_PHHA; i++) {
				if (ts->lengths[i] > 0)
					_hoops_SAHAR = j + ts->lengths[i];
				else
					_hoops_SAHAR = j + -ts->lengths[i];
				j += 2;
				while (j < _hoops_SAHAR) {
					_hoops_AGIPS[ts->face_indices[j]]++;
					j++;
				}
			}
		}
		ptr = _hoops_SPHPR->face_list;
		for (i = 0; i < face_count; i++) {
			length = 2 + _hoops_AGIPS[i];
			_hoops_PGIPS[i] = ptr;
			ptr += length + 1;
		}
		for (ts = _hoops_SPHPR->tristrips; ts != null; ts = ts->next) {
			j = 0;
			for (i = 0; i < ts->_hoops_PHHA; i++) {
				if (ts->lengths[i] > 0)
					_hoops_SAHAR = j + ts->lengths[i];
				else
					_hoops_SAHAR = j + -ts->lengths[i];
				j += 2;
				while (j < _hoops_SAHAR) {
					if (!_hoops_PSHPS(
						_hoops_PGIPS[ts->face_indices[j]],
						ts->_hoops_AIHA[j-2],
						ts->_hoops_AIHA[j-1],
						ts->_hoops_AIHA[j])) {
						_hoops_CSHPS (
							_hoops_SSHPS,
							_hoops_PGIPS[ts->face_indices[j]],
							ts->_hoops_AIHA[j-2],
							ts->_hoops_AIHA[j-1],
							ts->_hoops_AIHA[j]
						);
					}
					j++;
					if (j == _hoops_SAHAR)
						break;
					if (!_hoops_PSHPS(
						_hoops_PGIPS[ts->face_indices[j]],
						ts->_hoops_AIHA[j-1],
						ts->_hoops_AIHA[j-2],
						ts->_hoops_AIHA[j])) {
						_hoops_CSHPS (
							_hoops_SSHPS,
							_hoops_PGIPS[ts->face_indices[j]],
							ts->_hoops_AIHA[j-1],
							ts->_hoops_AIHA[j-2],
							ts->_hoops_AIHA[j]
						);
					}
					j++;
				}
			}
		}
		if (!_hoops_GGIPS(_hoops_SSHPS)) {
			HE_ERROR (HEC_INTERNAL_ERROR, HES_FACE, "unable to reconstruct face list from tristrips");
		}
		delete _hoops_SSHPS;
		FREE_ARRAY (_hoops_AGIPS, _hoops_SPHPR->face_count, int);
		FREE_ARRAY (_hoops_PGIPS, face_count, int *);
	}
	else {
		_hoops_SPHPR->face_list_length = _hoops_RGIPS * 4;
		ALLOC_ARRAY (_hoops_SPHPR->face_list, _hoops_SPHPR->face_list_length, int);
		faces = _hoops_SPHPR->face_list;
		for (ts = _hoops_SPHPR->tristrips; ts != null; ts = ts->next) {
			j = 0;
			for (i = 0; i < ts->_hoops_PHHA; i++) {
				if (ts->lengths[i] > 0)
					_hoops_SAHAR = j + ts->lengths[i];
				else
					_hoops_SAHAR = j + -ts->lengths[i];
				j += 2;
				while (1) {
					faces[0] = 3;
					faces[1] = ts->_hoops_AIHA[j-2];
					faces[2] = ts->_hoops_AIHA[j-1];
					faces[3] = ts->_hoops_AIHA[j];
					faces += 4;
					j++;
					if (j == _hoops_SAHAR) break;
					faces[0] = 3;
					faces[1] = ts->_hoops_AIHA[j-1];
					faces[2] = ts->_hoops_AIHA[j-2];
					faces[3] = ts->_hoops_AIHA[j];
					faces += 4;
					j++;
					if (j == _hoops_SAHAR) break;
				}
			}
		}
	}
	return true;
}

#ifndef DISABLE_GEOMETRY_SHOW

local void _hoops_HGIPS (
	Tristrip *			ts,
	int *				_hoops_IGIPS,
	int *				face_list_lengthp) {
	int					_hoops_CGIPS, _hoops_SGIPS;
	Tristrip *			_hoops_CPCR;

	_hoops_CGIPS = 0;
	_hoops_SGIPS = 0;

	for (_hoops_CPCR = ts; _hoops_CPCR != null; _hoops_CPCR = _hoops_CPCR->next) {
		_hoops_CGIPS += _hoops_CPCR->_hoops_PHHA;
		_hoops_SGIPS += _hoops_CPCR->total - 2*_hoops_CPCR->_hoops_PHHA;
	}

	if (_hoops_IGIPS != null)
		*_hoops_IGIPS = (_hoops_CGIPS * 3) + _hoops_SGIPS;
	if (face_list_lengthp != null)
		*face_list_lengthp = _hoops_SGIPS;
}


/* _hoops_SCHS _hoops_CHR _hoops_SGRIR _hoops_HSAR _hoops_CSHRR, _hoops_HIS _hoops_SR _hoops_HS _hoops_IS _hoops_SIPHA _hoops_PPR _hoops_IPS _hoops_ARGPR _hoops_SIH _hoops_CRGR
 * _hoops_RH _hoops_CCAH _hoops_AHAP.
 * _hoops_HHIGR _hoops_HRGR _hoops_RH _hoops_CIS'_hoops_GRI _hoops_CSSAR _hoops_IS _hoops_PAAP _hoops_HISI _hoops_AHAP(_hoops_GRI) _hoops_AAPR _hoops_PHPC _hoops_IS _hoops_RH _hoops_RHGS _hoops_HSHRR */
local Polyhedron *_hoops_GRIPS (Polyhedron *in) {
	Shell *			_hoops_SPHPR;
	int				i, j, rows, columns;
	int *			ptr;

	ZALLOC (_hoops_SPHPR, Shell);
	_hoops_RSAI (in, Polyhedron, _hoops_SPHPR);
	_hoops_SPHPR->type = _hoops_SCIP;
	_hoops_SPHPR->_hoops_SPHA = -1;				/* _hoops_HAR _hoops_AISP _hoops_GAPR */

	rows = ((_hoops_AIHPR *)in)->rows;
	columns = ((_hoops_AIHPR *)in)->columns;
	_hoops_SPHPR->face_list_length = 5 * (rows-1) * (columns-1);
	ALLOC_ARRAY (_hoops_SPHPR->face_list, _hoops_SPHPR->face_list_length, int);
	ptr = _hoops_SPHPR->face_list;
	for (i = 0; i < rows - 1; i++) {
		for (j = 0; j < columns - 1; j++) {
			/* _hoops_SRSA _hoops_RSSP? */
			ptr[0] = 4;
			ptr[1] = (i * columns) + j;
			ptr[2] = (i * columns) + (j+1);
			ptr[3] = ((i+1) * columns) + (j+1);
			ptr[4] = ((i+1) * columns) + j;
			ptr += 5;
		}
	}

	ZERO_STRUCT (in, _hoops_AIHPR);
	HI_Au_Revoir((_hoops_HPAH *) in);

	return (Polyhedron *)_hoops_SPHPR;
}

/* _hoops_IH _hoops_IRGHC _hoops_CAS _hoops_SR _hoops_CHR _hoops_HAR _hoops_RCRR _hoops_CAS _hoops_SR _hoops_CGH _hoops_SHH _hoops_RRIPS _hoops_RH _hoops_RIHPA _hoops_HPHS _hoops_HII,
 * _hoops_HIS _hoops_SAHR _hoops_IRHH _hoops_CPHP _hoops_GH, _hoops_PPR _hoops_GRHHR _hoops_SCH'_hoops_GRI _hoops_GHAR. _hoops_GCIH _hoops_GGSR _hoops_CCA
 * _hoops_SRSR _hoops_ARIPS _hoops_IS _hoops_RGRIR _hoops_IRS _hoops_CASRR _hoops_RIHH _hoops_RPP _hoops_RH _hoops_SPCC
 * _hoops_IIGR _hoops_RH _hoops_PPARR _hoops_SHPH (_hoops_HIS _hoops_SGS _hoops_SR _hoops_ACPA _hoops_IS _hoops_RCPS _hoops_ISSC _hoops_ARI _hoops_PPR _hoops_GGCR _hoops_CIPH) */
GLOBAL_FUNCTION void HI_Fake_NURBS_Surface_Configs (
	_hoops_AIIAA alter *configs)
{
#ifndef _hoops_GSPIR
	configs->_hoops_GGIRP = 0.005f;
	configs->_hoops_CSHRP = 500;
	configs->_hoops_RGIRP = 10;
	configs->_hoops_AGIRP = 20;
	configs->_hoops_PGIRP = 1.42f;
	configs->_hoops_SSHRP = 10000;
	_hoops_ISHRP(*configs);
#endif
}


#ifndef _hoops_GSPIR
local void _hoops_PRIPS (
	_hoops_AIIAA alter *	configs,
	_hoops_RHAIR const *					_hoops_RCIHP)
{
	_hoops_AIIAA const *	_hoops_HRIPS = &_hoops_RCIHP->geometry->_hoops_PSRIR.configs;

	if (BIT (_hoops_RCIHP->geometry->_hoops_PSRIR.mask, _hoops_PIGAP)) {
		if (BIT (_hoops_RCIHP->geometry->_hoops_PSRIR.value, _hoops_PIGAP))
			configs->_hoops_GGIRP = _hoops_HRIPS->_hoops_GGIRP;
		else
			configs->_hoops_GGIRP = 10000; /* _hoops_PSP _hoops_SAIPR */
	}
	if (BIT (_hoops_RCIHP->geometry->_hoops_PSRIR.mask, _hoops_IIGAP)) {
		if (BIT (_hoops_RCIHP->geometry->_hoops_PSRIR.value, _hoops_IIGAP))
			configs->_hoops_CSHRP = _hoops_HRIPS->_hoops_CSHRP;
		else
			configs->_hoops_CSHRP = 10000; /* _hoops_PSP _hoops_SAIPR */
	}
	if (BIT (_hoops_RCIHP->geometry->_hoops_PSRIR.mask, _hoops_CIGAP)) {
		if (BIT (_hoops_RCIHP->geometry->_hoops_PSRIR.value, _hoops_CIGAP))
			configs->_hoops_RGIRP = _hoops_HRIPS->_hoops_RGIRP;
		else
			configs->_hoops_RGIRP = 10000; /* _hoops_PSP _hoops_SAIPR */
	}
	if (BIT (_hoops_RCIHP->geometry->_hoops_PSRIR.mask, _hoops_SIGAP)) {
		if (BIT (_hoops_RCIHP->geometry->_hoops_PSRIR.value, _hoops_SIGAP))
			configs->_hoops_AGIRP = _hoops_HRIPS->_hoops_AGIRP;
		else
			configs->_hoops_AGIRP = 10000; /* _hoops_PSP _hoops_SAIPR */
	}
	if (BIT (_hoops_RCIHP->geometry->_hoops_PSRIR.mask, _hoops_GCGAP)) {
		if (BIT (_hoops_RCIHP->geometry->_hoops_PSRIR.value, _hoops_GCGAP))
			configs->_hoops_PGIRP = _hoops_HRIPS->_hoops_PGIRP;
		else
			configs->_hoops_PGIRP = 10000; /* _hoops_PSP _hoops_SAIPR */
	}
	if (BIT (_hoops_RCIHP->geometry->_hoops_PSRIR.mask, _hoops_RCGAP)) {
		if (BIT (_hoops_RCIHP->geometry->_hoops_PSRIR.value, _hoops_RCGAP))
			configs->_hoops_SSHRP = _hoops_HRIPS->_hoops_SSHRP;
		else
			configs->_hoops_SSHRP = 10000; /* _hoops_PSP _hoops_SAIPR */
	}
}
#endif		/* #_hoops_CHS _hoops_IRIPS */



local void _hoops_CRIPS (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			list,
	_hoops_APPGR *			surface,
	Shell alter **			_hoops_CPSIH)
{
#ifndef _hoops_GSPIR
	if (surface->_hoops_IPRI == null) {
		_hoops_AIIAA configs;

		/* _hoops_HSPP _hoops_CCA _hoops_SHIR _hoops_HSH */
		HI_Fake_NURBS_Surface_Configs (&configs);
		if (list) {
			Option_Value *options_list = null;

			if (!HI_Parse_Options (_hoops_RIGC, list, _hoops_CIACR (_hoops_HIRGI),
				&options_list, _hoops_SIACR|_hoops_CPSAP)) {
				_hoops_GCIIR * options_hash = null;
				_hoops_PIIIR *		_hoops_RCSGH;
				_hoops_PIIIR **		_hoops_SRIPS;
				_hoops_PIIIR **		_hoops_CASRS;
				int					_hoops_RPSRS;

				_hoops_RPSRS = HOOPS_WORLD->_hoops_GSPGI[_hoops_HIRGI].size;
				if ((_hoops_SRIPS = HOOPS_WORLD->_hoops_GSPGI[_hoops_HIRGI].table) != null) {
					_hoops_CASRS = _hoops_SRIPS + _hoops_RPSRS;
					do {
						_hoops_RCSGH = *_hoops_SRIPS;
						while (_hoops_RCSGH != null) {
							if (_hoops_RCSGH->id == _hoops_HCGAP) {
								options_hash = _hoops_RCSGH->_hoops_CIIIR;
								break;
							}
							_hoops_RCSGH = _hoops_RCSGH->next;
						}
					} while (++_hoops_SRIPS != _hoops_CASRS && options_hash == null);
				}

				if (!HI_Parse_Options (_hoops_RIGC, list, options_hash,
					&options_list, _hoops_SIACR))
					options_list = null;
			}
			while (options_list != null && (options_list->type->id == _hoops_PCGAP || options_list->type->id == _hoops_ACGAP))
				options_list = options_list->next;
			if (options_list) {
				_hoops_RHAIR _hoops_RCIHP;
				_hoops_RIAIR  _hoops_HHAIR;
				_hoops_SCAIR geometry;
				_hoops_PHAIR _hoops_PRSI;
				_hoops_CCAIR locks;
				_hoops_HIAIR _hoops_AIAIR;
				Option_Value *_hoops_GAIPS = options_list;

				if (options_list->type->id == _hoops_HCGAP)
					_hoops_GAIPS = options_list->value.option_list;

				ZERO_STRUCT (&_hoops_RCIHP, _hoops_RHAIR);
				ZERO_STRUCT (&_hoops_HHAIR, _hoops_RIAIR);
				_hoops_RCIHP._hoops_HHAIR = &_hoops_HHAIR;
				ZERO_STRUCT (&geometry, _hoops_SCAIR);
				_hoops_RCIHP.geometry = &geometry;
				ZERO_STRUCT (&_hoops_PRSI, _hoops_PHAIR);
				_hoops_RCIHP._hoops_PRSI = &_hoops_PRSI;
				ZERO_STRUCT (&locks, _hoops_CCAIR);
				_hoops_RCIHP.locks = &locks;
				ZERO_STRUCT (&_hoops_AIAIR, _hoops_HIAIR);
				_hoops_RCIHP._hoops_AIAIR = &_hoops_AIAIR;
				HI_Process_NURBS_Surface_Options(_hoops_GAIPS, &_hoops_RCIHP);
				_hoops_PRIPS (&configs, &_hoops_RCIHP);
				HI_Free_Option_List (_hoops_RIGC, options_list);
			}
		}
		else {
			_hoops_RHAIR const *_hoops_RAIPS = null;
			if (surface->owner)
				_hoops_RAIPS = (_hoops_RHAIR *)HI_Find_Attribute (_hoops_RIGC, (_hoops_HPAH *)surface->owner, -HK_RENDERING_OPTIONS);

			if (_hoops_RAIPS &&
				BIT (_hoops_RAIPS->_hoops_SCIAA, _hoops_CRICA))
				_hoops_PRIPS (&configs, _hoops_RAIPS);
			if (_hoops_RAIPS)
				_hoops_HPRH (_hoops_RAIPS);
		}
		HI_Tessellate_NURBS_Surface (_hoops_RIGC, surface, &configs);
	}
	if (surface->_hoops_IPRI->type == _hoops_GSIP)
		surface->_hoops_IPRI = _hoops_GRIPS (surface->_hoops_IPRI);
	*_hoops_CPSIH = (Shell *)surface->_hoops_IPRI;
#endif
}


local void _hoops_AAIPS (
	int					_hoops_HGII,
	Sphere const *		sphere,
	Shell alter **		_hoops_CPSIH)
{
#ifndef _hoops_RRHIR
	Shell *				_hoops_SPHPR;
	Point *				points;
	Point *				p;
	int *				face_list;
	int					i, j;
	int					point_count, face_count;
	int					face_list_length;
	int *				_hoops_PSRGA;
	int					_hoops_GIIRC, _hoops_RIIRC;
	float				_hoops_RSGPS, _hoops_ASGPS;
	float				_hoops_GPIAA, _hoops_RPIAA;
	float				_hoops_HAIAA, _hoops_IAIAA;
	float				theta, phi, _hoops_GSGPS;

	ZALLOC (_hoops_SPHPR, Shell);
	_hoops_SPHPR->type = _hoops_SCIP;
	_hoops_SPHPR->_hoops_SPHA = -1;				/* _hoops_HAR _hoops_AISP _hoops_GAPR */
	*_hoops_CPSIH = _hoops_SPHPR;

	if (_hoops_HGII < 4) {
		_hoops_SPHPR->point_count = 1;
		ALLOC_ARRAY_ALIGNED (points, 1, Point, 16);
		_hoops_RSAI (&sphere->data.center, Point, points);
		_hoops_SPHPR->points = points;
		return;
	}
	else {
		_hoops_GIIRC = _hoops_HGII;
		_hoops_RIIRC = 1 + _hoops_GIIRC/2;
		point_count = _hoops_GIIRC * _hoops_RIIRC;
		face_count = _hoops_GIIRC * _hoops_RIIRC + 2;
		face_list_length = 5*_hoops_GIIRC*(_hoops_RIIRC-1) + 2*(_hoops_GIIRC+2);
		ALLOC_ARRAY_ALIGNED (points, point_count, Point, 16);
		ALLOC_ARRAY (face_list, face_list_length, int);
		_hoops_SPHPR->face_count = face_count;
		_hoops_SPHPR->points = points;
		_hoops_SPHPR->point_count = point_count;
		_hoops_SPHPR->face_list = face_list;
		_hoops_SPHPR->face_list_length = face_list_length;
	}

	p = points;
	_hoops_RSGPS = 360.0f/_hoops_GIIRC;
	_hoops_ASGPS = 180.0f/(_hoops_RIIRC);
	phi = _hoops_ASGPS/2;
	if (sphere->_hoops_CSPIR) {
		for (j = 0; j < _hoops_RIIRC; phi += _hoops_ASGPS, j++) {
			if (phi > 180.0f)
				phi = 180.0f;
			HI_SinCos(phi, &_hoops_HAIAA, &_hoops_IAIAA);
			for (theta = 0, i = 0; i < _hoops_GIIRC; theta += _hoops_RSGPS, i++) {
				HI_SinCos(theta, &_hoops_GPIAA, &_hoops_RPIAA);
				_hoops_GSGPS = _hoops_HAIAA * _hoops_RPIAA;
				p->x = _hoops_GSGPS * sphere->_hoops_CSPIR[0].x;
				p->y = _hoops_GSGPS * sphere->_hoops_CSPIR[0].y;
				p->z = _hoops_GSGPS * sphere->_hoops_CSPIR[0].z;
				_hoops_GSGPS = _hoops_IAIAA;
				p->x += _hoops_GSGPS * sphere->_hoops_CSPIR[1].x;
				p->y += _hoops_GSGPS * sphere->_hoops_CSPIR[1].y;
				p->z += _hoops_GSGPS * sphere->_hoops_CSPIR[1].z;
				_hoops_GSGPS = _hoops_HAIAA * _hoops_GPIAA;
				p->x += _hoops_GSGPS * sphere->_hoops_CSPIR[2].x;
				p->y += _hoops_GSGPS * sphere->_hoops_CSPIR[2].y;
				p->z += _hoops_GSGPS * sphere->_hoops_CSPIR[2].z;
				p->x += sphere->data.center.x;
				p->y += sphere->data.center.y;
				p->z += sphere->data.center.z;
				p++;
			}
		}
	}
	else {
		for (j = 0; j < _hoops_RIIRC; phi += _hoops_ASGPS, j++) {
			if (phi > 180.0f)
				phi = 180.0f;
			HI_SinCos(phi, &_hoops_HAIAA, &_hoops_IAIAA);
			for (theta = 0, i = 0; i < _hoops_GIIRC; theta += _hoops_RSGPS, i++) {
				HI_SinCos(theta, &_hoops_GPIAA, &_hoops_RPIAA);
				p->x = sphere->data.center.x + sphere->data.radius * _hoops_HAIAA * _hoops_RPIAA;
				p->y = sphere->data.center.y + sphere->data.radius * _hoops_IAIAA;
				p->z = sphere->data.center.z + sphere->data.radius * _hoops_HAIAA * _hoops_GPIAA;
				p++;
			}
		}
		ASSERT (p - points == point_count);
	}
	_hoops_PSRGA = face_list;
	for (j = 0; j < _hoops_RIIRC-1; j++) {
		for (i = 0; i < _hoops_GIIRC-1; i++) {
			*_hoops_PSRGA++ = 4;
			*_hoops_PSRGA++ = j*_hoops_GIIRC + i;
			*_hoops_PSRGA++ = j*_hoops_GIIRC + (i+1);
			*_hoops_PSRGA++ = (j+1)*_hoops_GIIRC + (i+1);
			*_hoops_PSRGA++ = (j+1)*_hoops_GIIRC + i;
		}
		*_hoops_PSRGA++ = 4;
		*_hoops_PSRGA++ = j*_hoops_GIIRC + i;
		*_hoops_PSRGA++ = j*_hoops_GIIRC;
		*_hoops_PSRGA++ = (j+1)*_hoops_GIIRC;
		*_hoops_PSRGA++ = (j+1)*_hoops_GIIRC + i;
	}
	/* _hoops_HA _hoops_IH _hoops_RH _hoops_PCAS */
	*_hoops_PSRGA++ = _hoops_GIIRC+1;
	for (i = 0; i < _hoops_GIIRC; i++) {
		*_hoops_PSRGA++ = j*_hoops_GIIRC + i;
	}
	*_hoops_PSRGA++ = j*_hoops_GIIRC; /* _hoops_SPGCA _hoops_ISSC _hoops_IS _hoops_RH _hoops_HSPP */
	*_hoops_PSRGA++ = _hoops_GIIRC+1;
	*_hoops_PSRGA++ = 0;
	for (i = 0; i < _hoops_GIIRC; i++) {
		*_hoops_PSRGA++ = _hoops_GIIRC - i - 1;
	}

	ASSERT (p - points == point_count);
	ASSERT (_hoops_PSRGA - face_list == face_list_length);
#endif
}



#ifndef _hoops_PSPIR
local void _hoops_PAIPS (
	int								_hoops_HGII,
	PolyCylinder const *			_hoops_HSPIR,
	Shell alter *					_hoops_SPHPR)
{
	_hoops_AGHIR const *	_hoops_PGHIR = _hoops_HSPIR->_hoops_RGHIR;
	Local_Vertex_Attributes alter *	_hoops_HAIPS = &_hoops_SPHPR->local_vertex_attributes;
	int								i, j, _hoops_PAIH, shift, _hoops_SGII, end;
	bool							_hoops_IAIPS;

	_hoops_SGII = 0;
	if (_hoops_PGHIR->ecolors)
		_hoops_SGII |= _hoops_PPHPR;
	if (_hoops_PGHIR->_hoops_HGHIR)
		_hoops_SGII |= _hoops_RPHPR;
	if (_hoops_PGHIR->fcolors)
		_hoops_SGII |= _hoops_AARHR;
	if (_hoops_PGHIR->_hoops_IGHIR)
		_hoops_SGII |= _hoops_HARHR;
	if (_hoops_SGII)
		HI_Initialize_Vertex_Attributes ((Polyhedron *)_hoops_SPHPR, (unsigned short)_hoops_SGII, 0);
	else
		return;
	shift = 0;

	if (_hoops_HGII == 1)
		_hoops_IAIPS = true;
	else
		_hoops_IAIPS = false;

	if (_hoops_IAIPS) {
		if (_hoops_HSPIR->point_count == 2)
			end = 3;
		else
			end = _hoops_HSPIR->point_count;
	}
	else
		end = _hoops_HSPIR->point_count + 2;

	for (i = 0; i < end; i++) {
		if (i < _hoops_HSPIR->point_count)
			_hoops_PAIH = i;
		else if (i == _hoops_HSPIR->point_count) {
			if (_hoops_IAIPS || BIT (_hoops_HSPIR->flags, _hoops_IHHIA))
				_hoops_PAIH = 0;
			else
				continue;
		}
		else {
			if (BIT (_hoops_HSPIR->flags, _hoops_SHHIA))
				_hoops_PAIH = _hoops_HSPIR->point_count - 1;
			else
				continue;
		}
		if (BIT (_hoops_PGHIR->flags[_hoops_PAIH], _hoops_SHRRA)) {
			for (j = 0; j < _hoops_HGII; j++) {
				_hoops_HAIPS->ecolors[shift + j] = _hoops_PGHIR->ecolors[_hoops_PAIH];
				*_hoops_HAIPS->_hoops_CHHPR(shift + j) |= _hoops_PPHPR;
				_hoops_HAIPS->_hoops_SCHPR++;
			}
		}
		if (BIT (_hoops_PGHIR->flags[_hoops_PAIH], _hoops_IHRRA)) {
			for (j = 0; j < _hoops_HGII; j++) {
				_hoops_HAIPS->_hoops_HGHIR[shift + j] = _hoops_PGHIR->_hoops_HGHIR[_hoops_PAIH];
				*_hoops_HAIPS->_hoops_CHHPR(shift + j) |= _hoops_RPHPR;
				_hoops_HAIPS->_hoops_CCHPR++;
			}
		}
		if (BIT (_hoops_PGHIR->flags[_hoops_PAIH], _hoops_GIRRA)) {
			for (j = 0; j < _hoops_HGII; j++) {
				_hoops_HAIPS->fcolors[shift + j] = _hoops_PGHIR->fcolors[_hoops_PAIH];
				*_hoops_HAIPS->_hoops_CHHPR(shift + j) |= _hoops_AARHR;
				_hoops_HAIPS->_hoops_RCRHR++;
			}
		}
		if (BIT (_hoops_PGHIR->flags[_hoops_PAIH], _hoops_CHRRA)) {
			for (j = 0; j < _hoops_HGII; j++) {
				_hoops_HAIPS->_hoops_IGHIR[shift + j] = _hoops_PGHIR->_hoops_IGHIR[_hoops_PAIH];
				*_hoops_HAIPS->_hoops_CHHPR(shift + j) |= _hoops_HARHR;
				_hoops_HAIPS->_hoops_SIRHR++;
			}
		}
		shift += _hoops_HGII;
	}
}
#endif

#ifndef _hoops_PSPIR
local void _hoops_CAIPS (
	PolyCylinder const *		_hoops_HSPIR,
	Shell alter **				_hoops_CPSIH)
{
	Shell *						_hoops_SPHPR;
	Local_Face_Attributes *		_hoops_CPRI;
	_hoops_RPGHR *		lea;
	int							i;

	ZALLOC (_hoops_SPHPR, Shell);
	_hoops_SPHPR->type = _hoops_SCIP;
	_hoops_SPHPR->_hoops_HIHI = 1;
	_hoops_SPHPR->face_count = 1;
	_hoops_SPHPR->_hoops_SPHA = -1;
	*_hoops_CPSIH = _hoops_SPHPR;

	if (_hoops_HSPIR->point_count > 2) {
		_hoops_SPHPR->point_count = _hoops_HSPIR->point_count;
		ALLOC_ARRAY_ALIGNED (_hoops_SPHPR->points, _hoops_SPHPR->point_count, Point, 16);
		_hoops_AIGA (_hoops_HSPIR->points, _hoops_HSPIR->point_count, Point, _hoops_SPHPR->points);
		_hoops_SPHPR->face_list_length = _hoops_HSPIR->point_count + 1;
		ALLOC_ARRAY (_hoops_SPHPR->face_list, _hoops_SPHPR->face_list_length, int);
		_hoops_SPHPR->face_list[0] = _hoops_HSPIR->point_count;
		for (i = 0; i < _hoops_HSPIR->point_count; i++)
			_hoops_SPHPR->face_list[i+1] = i;
	}
	else {
		_hoops_SPHPR->point_count = 3;
		ALLOC_ARRAY_ALIGNED (_hoops_SPHPR->points, 3, Point, 16);
		_hoops_AIGA (_hoops_HSPIR->points, 2, Point, _hoops_SPHPR->points);
		/* _hoops_GGCR _hoops_PCCP _hoops_IHH _hoops_PPSR _hoops_ASPSR _hoops_CCA _hoops_RH _hoops_SRS _hoops_HIS _hoops_SGS _hoops_SR _hoops_PAH _hoops_IRHH _hoops_IRS _hoops_SCPH */
		_hoops_RSAI (&_hoops_HSPIR->points[0], Point, &_hoops_SPHPR->points[2]);
		_hoops_SPHPR->face_list_length = 4;
		ALLOC_ARRAY (_hoops_SPHPR->face_list, 4, int);
		_hoops_SPHPR->face_list[0] = 3;
		_hoops_SPHPR->face_list[1] = 0;
		_hoops_SPHPR->face_list[2] = 1;
		_hoops_SPHPR->face_list[3] = 2;
	}

	HI_Initialize_Face_Attributes ((Polyhedron *)_hoops_SPHPR, _hoops_HSIPR);
	_hoops_CPRI = &_hoops_SPHPR->local_face_attributes;
	*(_hoops_CPRI->_hoops_CHHPR(0)) |= _hoops_HSIPR;
	_hoops_CPRI->_hoops_SIIPR = 1;

	HI_Create_Shell_Edges (_hoops_SPHPR, false);
	HI_Initialize_Edge_Attributes ((Polyhedron *)_hoops_SPHPR, _hoops_AHIAA);
	lea = &_hoops_SPHPR->_hoops_IHHPR;
	lea->flags[1] |= _hoops_AHIAA;
	lea->_hoops_SIIPR = 1;
	if (_hoops_HSPIR->point_count == 2) {
		/* _hoops_RPP _hoops_SR _hoops_RIAGR _hoops_IS _hoops_ARPR _hoops_PCCP _hoops_IHH _hoops_PPSR, _hoops_IIH'_hoops_GRI _hoops_PCCP _hoops_IHH _hoops_ISHA _hoops_IS _hoops_AGSGR _hoops_PSAP _hoops_GAR _hoops_PRAR */
		lea->flags[2] |= _hoops_AHIAA;
		lea->_hoops_SIIPR++;
	}

	if (_hoops_HSPIR->_hoops_RGHIR)
		_hoops_PAIPS (1, _hoops_HSPIR, _hoops_SPHPR);
}
#endif /* #_hoops_CHS _hoops_SAIPS */


local void _hoops_GPIPS (
	int						_hoops_HGII,
	PolyCylinder const *	_hoops_HSPIR,
	Shell alter **			_hoops_CPSIH)
{
#ifndef _hoops_PSPIR
	Shell *					_hoops_SPHPR;
	Point *					points;
	int *					_hoops_AIHA;
	int *					face_indices;
	int *					face_list;
	int *					lengths;
	Tristrip *				tristrip;
	float					_hoops_GGHCR, _hoops_AGHCR, _hoops_RAHCR;
	int						ii, _hoops_ICRHH;
	int						_hoops_HCRGR, _hoops_PGRPS, tristrip_count, _hoops_RPIPS;
	int						_hoops_APIPS, face_list_length;
	int						offset1, offset2, shift, _hoops_PPIPS, index;
	int *					vi;
	int *					fi;
	int *					_hoops_PSRGA;
	int						delta;
	Point const *			center;
	int						_hoops_HGRPS;

	if (_hoops_HGII < 2 ||
		_hoops_HSPIR->_hoops_ISPIR == 1 && _hoops_HSPIR->radii[0] == 0.0f) {
		_hoops_CAIPS (_hoops_HSPIR, _hoops_CPSIH);
		return;
	}

	ZALLOC (_hoops_SPHPR, Shell);
	_hoops_SPHPR->type = _hoops_SCIP;
	_hoops_SPHPR->_hoops_HIHI = 1;
	_hoops_SPHPR->_hoops_SPHA = -1; /* _hoops_HAR _hoops_AISP _hoops_GAPR */
	*_hoops_CPSIH = _hoops_SPHPR;

	ZALLOC (tristrip, Tristrip);
	_hoops_SPHPR->tristrips = tristrip;
	_hoops_ICAI (tristrip);

	_hoops_RPIPS = 0;
	if (!BIT (_hoops_HSPIR->flags, _hoops_GASSA)) {
		if (_hoops_HSPIR->flags & _hoops_IHHIA)
			_hoops_RPIPS++;
		if (_hoops_HSPIR->flags & _hoops_SHHIA)
			_hoops_RPIPS++;
	}
	delta = int (360.0f / _hoops_HGII);
	_hoops_HCRGR = (_hoops_HSPIR->point_count + _hoops_RPIPS) * _hoops_HGII;
	_hoops_PGRPS = (_hoops_HSPIR->point_count-1) * _hoops_HGII + _hoops_RPIPS;
	tristrip_count = (_hoops_HSPIR->point_count-1) + _hoops_RPIPS;
	face_list_length = 5*(_hoops_HSPIR->point_count-1)*_hoops_HGII + _hoops_RPIPS*(_hoops_HGII+1);
	_hoops_APIPS = ((_hoops_HSPIR->point_count-1)*((_hoops_HGII+1)*2)) + _hoops_RPIPS*_hoops_HGII;

	ALLOC_ARRAY_ALIGNED (points, _hoops_HCRGR, Point, 16);
	ALLOC_ARRAY (face_list, face_list_length, int);
	ALLOC_ARRAY (lengths, tristrip_count, int);
	ALLOC_ARRAY (_hoops_AIHA, _hoops_APIPS, int);
	ALLOC_ARRAY (face_indices, _hoops_APIPS, int);
	tristrip->_hoops_RAHH |= _hoops_AAHH;
	tristrip->points = points;
	tristrip->point_count = _hoops_HCRGR;
	tristrip->face_count = _hoops_PGRPS;
	tristrip->lengths = lengths;
	tristrip->_hoops_AIHA = vi = _hoops_AIHA;
	tristrip->face_indices = fi = face_indices;
	tristrip->total = _hoops_APIPS;
	tristrip->_hoops_IPII = _hoops_APIPS;
	tristrip->_hoops_SGAHR = _hoops_APIPS;
	tristrip->lengths_allocated = tristrip_count;
	_hoops_PSRGA = face_list;


	/* _hoops_RPCRC: _hoops_PAHH _hoops_RRP _hoops_IS _hoops_SAHR _hoops_CCPP _hoops_IRS _hoops_IHIR _hoops_HPIPS->_hoops_SGI _hoops_CRPR _hoops_ARI,
			_hoops_CCGR _hoops_SR _hoops_HS _hoops_IRS _hoops_PPRRR _hoops_IIGR _hoops_IPAC _hoops_IGH _hoops_RH _hoops_GIAIA->_hoops_SGI _hoops_CHR _hoops_GHRHR */
	if (!BIT(_hoops_SPHPR->polyhedron_flags, _hoops_CGRHR)) {
		int i = 0;
		ZALLOC_ARRAY(_hoops_SPHPR->local_vertex_attributes.flags, _hoops_HCRGR, Local_Vertex_Flags);
		for (i = 0; i < _hoops_HCRGR; i++)
			_hoops_SPHPR->local_vertex_attributes.flags[i] = _hoops_SPHPR->local_vertex_attributes._hoops_SGRHR;
		_hoops_SPHPR->polyhedron_flags |= _hoops_CGRHR;
	}

	/* _hoops_RHAP _hoops_HAR _hoops_HIHA _hoops_IH _hoops_RSRRA _hoops_AASSA */
	_hoops_HGRPS = 0;
	for (_hoops_ICRHH=0; _hoops_ICRHH<_hoops_HSPIR->point_count; _hoops_ICRHH++) {
		Vector	_hoops_GGHI;
		Vector	_hoops_RGHI;
		float		radius = _hoops_HSPIR->radii[_hoops_HGRPS];

		center = &_hoops_HSPIR->points[_hoops_ICRHH];
		_hoops_GGHI.x = _hoops_HSPIR->_hoops_CSPIR[_hoops_ICRHH].axis[0].x * radius;
		_hoops_GGHI.y = _hoops_HSPIR->_hoops_CSPIR[_hoops_ICRHH].axis[0].y * radius;
		_hoops_GGHI.z = _hoops_HSPIR->_hoops_CSPIR[_hoops_ICRHH].axis[0].z * radius;
		_hoops_RGHI.x = _hoops_HSPIR->_hoops_CSPIR[_hoops_ICRHH].axis[1].x * radius;
		_hoops_RGHI.y = _hoops_HSPIR->_hoops_CSPIR[_hoops_ICRHH].axis[1].y * radius;
		_hoops_RGHI.z = _hoops_HSPIR->_hoops_CSPIR[_hoops_ICRHH].axis[1].z * radius;
		for (ii=0; ii<_hoops_HGII; ++ii) {
			_hoops_RAHCR = ii * delta + _hoops_HSPIR->_hoops_GGHIR[_hoops_ICRHH];
			index = _hoops_ICRHH*_hoops_HGII+ii;

			_hoops_RICH (_hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR);
			points[index].x = center->x + _hoops_AGHCR * _hoops_GGHI.x + _hoops_GGHCR * _hoops_RGHI.x;
			points[index].y = center->y + _hoops_AGHCR * _hoops_GGHI.y + _hoops_GGHCR * _hoops_RGHI.y;
			points[index].z = center->z + _hoops_AGHCR * _hoops_GGHI.z + _hoops_GGHCR * _hoops_RGHI.z;
		}
		if (++_hoops_HGRPS == _hoops_HSPIR->_hoops_ISPIR)
			_hoops_HGRPS = 0;
	}

	offset1 = 0;
	offset2 = _hoops_HGII;
	for (_hoops_ICRHH=0; _hoops_ICRHH<_hoops_HSPIR->point_count-1; _hoops_ICRHH++) {
		shift = _hoops_ICRHH * _hoops_HGII;
		/* _hoops_IIRGR _hoops_CSGPS _hoops_AARI */
		lengths[tristrip->_hoops_PHHA++] = 2*_hoops_HGII+2;
		/* _hoops_HSPP "_hoops_ARPP" _hoops_RH _hoops_GSSR _hoops_ICPPR */
		*vi++ = shift + _hoops_HGII-1 + offset1;
		*vi++ = shift + _hoops_HGII-1 + offset2;
		*fi++ = shift + 0;
		*fi++ = shift + 0;
		for (ii=0; ii<_hoops_HGII; ii++) {
			/* _hoops_CCGI' _hoops_HSP _hoops_PSPI _hoops_PPR _hoops_GPHA _hoops_PSPI _hoops_IRII */
			*vi++ = shift + ii+offset1;
			*fi++ = shift + ii;
			*vi++ = shift + ii+offset2;
			*fi++ = shift + ii;
			/* _hoops_HSP _hoops_HIGR _hoops_CRHPR _hoops_IRS _hoops_HAPR */
			*_hoops_PSRGA++ = 4;
			*_hoops_PSRGA++ = vi[-4];
			*_hoops_PSRGA++ = vi[-2];
			*_hoops_PSRGA++ = vi[-1];
			*_hoops_PSRGA++ = vi[-3];
		}
	}

	if (!BIT (_hoops_HSPIR->flags, _hoops_GASSA)) {
		shift = _hoops_PPIPS = (_hoops_HSPIR->point_count-1) * _hoops_HGII;
		index = (_hoops_HSPIR->point_count-1) * _hoops_HGII;
		if (_hoops_HSPIR->flags & _hoops_IHHIA) {
			shift += _hoops_HGII;
			index++;
			lengths[tristrip->_hoops_PHHA++] = _hoops_HGII;
			*_hoops_PSRGA++ = _hoops_HGII;
			for (ii=0; ii<_hoops_HGII; ii++) {
				/* _hoops_CRHH _hoops_IRII */
				if ((ii & 1) == 0)
					*vi++ = _hoops_HGII-1 - ii/2 + shift;
				else
					*vi++ = ii/2 + shift;
				/* _hoops_GPP _hoops_SPS _hoops_III, _hoops_RPR _hoops_HPIPR _hoops_IS _hoops_RHHSR _hoops_RSSP */
				/* _hoops_HSP _hoops_HIGR _hoops_HAPR */
				*_hoops_PSRGA++ = _hoops_HGII-ii-1 + shift;
				*fi++ = index;
			}
			_hoops_AIGA (points, _hoops_HGII, Point, points + shift);
		}
		if (_hoops_HSPIR->flags & _hoops_SHHIA) {
			shift += _hoops_HGII;
			index++;
			lengths[tristrip->_hoops_PHHA++] = _hoops_HGII;
			*_hoops_PSRGA++ = _hoops_HGII;
			for (ii=0; ii<_hoops_HGII; ii++) {
				/* _hoops_CRHH _hoops_IRII */
				if ((ii & 1) == 0)
					*vi++ = ii/2 + shift;
				else
					*vi++ = _hoops_HGII-1 - ii/2 + shift;
				/* _hoops_HSP _hoops_HIGR _hoops_HAPR */
				*_hoops_PSRGA++ = ii + shift;
				*fi++ = index;
			}
			_hoops_AIGA (points + _hoops_PPIPS, _hoops_HGII, Point, points + shift);
		}
	}

	ASSERT (_hoops_PSRGA - face_list == face_list_length);
	ASSERT (vi - _hoops_AIHA == _hoops_APIPS);
	ASSERT (fi - face_indices == _hoops_APIPS);
	_hoops_SPHPR->face_count = _hoops_PGRPS;
	_hoops_SPHPR->points = points;
	_hoops_SPHPR->point_count = _hoops_HCRGR;
	_hoops_SPHPR->face_list = face_list;
	_hoops_SPHPR->face_list_length = face_list_length;
	if (_hoops_HSPIR->_hoops_RGHIR)
		_hoops_PAIPS (_hoops_HGII, _hoops_HSPIR, _hoops_SPHPR);
#endif /* #_hoops_CHS _hoops_SAIPS */
}


/* _hoops_RGR _hoops_API _hoops_HRGR _hoops_IRS _hoops_HAPR _hoops_AARI _hoops_IPIPS _hoops_PPR
 * _hoops_CPIPS _hoops_SGS _hoops_SIHR _hoops_SPIPS _hoops_PAR _hoops_GRPRA _hoops_RH _hoops_ARGPR
 * _hoops_AAP _hoops_PPR _hoops_GHIPS _hoops_CRGR _hoops_GCIHC */
local void _hoops_RHIPS (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			list,
	Geometry const *		g,
	Shell alter **			_hoops_CPSIH)
{
#if !defined(_hoops_PSPIR) || !defined(_hoops_RRHIR)
	int					i, _hoops_AHIPS, bit;
	int					_hoops_PHIPS[_hoops_IGAIR+1] = {24, -1, -1, -1, -1, -1, -1, -1, -1};
	Shell *				_hoops_HHIPS = null;
	Shell *				_hoops_IHIPS = null;

	if (g->type == _hoops_HSIP)
		bit = _hoops_PCGAP;
	else
		bit = _hoops_ACGAP;

	if (list) {
		Option_Value *option, *options_list;

		if (!HI_Parse_Options (_hoops_RIGC, list, _hoops_CIACR (_hoops_HIRGI),
			&options_list, _hoops_SIACR))
			return;

		if ((option = options_list) != null) do {
			if (BIT(option->type->id, bit)) {
				for (i=0; i<option->_hoops_AIPCR; i++) {
					_hoops_PHIPS[i] = option->value._hoops_RIARA[i];
				}
			}
		} while ((option = option->next) != null);
		if (options_list)
			HI_Free_Option_List (_hoops_RIGC, options_list);
	}
	else {
		_hoops_RHAIR *_hoops_RCIHP = null;

		if (g->owner)
			_hoops_RCIHP = (_hoops_RHAIR *)HI_Find_Attribute (_hoops_RIGC, (_hoops_HPAH *)g->owner, -HK_RENDERING_OPTIONS);

		if (_hoops_RCIHP &&
			BIT (_hoops_RCIHP->_hoops_SCIAA, _hoops_SRICA) &&
			BIT (_hoops_RCIHP->geometry->_hoops_GAICA.mask, bit)) {
			if (g->type == _hoops_HSIP)
				_hoops_AIGA (_hoops_RCIHP->geometry->_hoops_GAICA.sphere, _hoops_IGAIR, int, _hoops_PHIPS);
			else
				_hoops_AIGA (_hoops_RCIHP->geometry->_hoops_GAICA.cylinder, _hoops_IGAIR, int, _hoops_PHIPS);
		}
		if (_hoops_RCIHP)
			_hoops_HPRH (_hoops_RCIHP);
	}

	for (_hoops_AHIPS = 0; _hoops_PHIPS[_hoops_AHIPS] >= 0; _hoops_AHIPS++) {
		if (g->type == _hoops_HSIP)
			_hoops_AAIPS (_hoops_PHIPS[_hoops_AHIPS], (Sphere *)g, &_hoops_IHIPS);
		else
			_hoops_GPIPS(_hoops_PHIPS[_hoops_AHIPS], (PolyCylinder *)g, &_hoops_IHIPS);

		_hoops_IHIPS->_hoops_CPGPR = _hoops_AHSGA;
		HI_Figure_Geometry_Bounding ((Geometry const *)_hoops_IHIPS, _hoops_IHIPS->bounding);
		_hoops_IHIPS->_hoops_CPGPR = _hoops_PHSSR;

		if (_hoops_AHIPS == 0)
			*_hoops_CPSIH = _hoops_HHIPS = _hoops_IHIPS;
		else {
			if (_hoops_AHIPS == 1) {
				ZALLOC (_hoops_HHIPS->_hoops_HGAIR, _hoops_PGAIR);
				_hoops_HHIPS->_hoops_HGAIR->type = _hoops_AGAIR;
				_hoops_HHIPS->_hoops_HGAIR->owner = (_hoops_HPAH *)_hoops_HHIPS;
				_hoops_HHIPS->_hoops_HGAIR->backlink = (_hoops_HPAH **) &(_hoops_HHIPS->_hoops_HGAIR);
				_hoops_HHIPS->_hoops_HGAIR->_hoops_HIHI = 1;
			}
			_hoops_HHIPS->_hoops_HGAIR->data[_hoops_AHIPS-1] = (Geometry *)_hoops_IHIPS;
			_hoops_IHIPS->_hoops_HIHI = 1;
		}
	}
#endif
}

local void _hoops_CHIPS (
	int					count,
	Point const *		points,
	Shell alter **		_hoops_CPSIH) {
	Shell alter *		_hoops_SPHPR;

	ZALLOC (_hoops_SPHPR, Shell);
	_hoops_SPHPR->type = _hoops_SCIP;
	_hoops_SPHPR->_hoops_CPGPR = _hoops_PHSSR;
	_hoops_SPHPR->point_count = count;
	_hoops_SPHPR->_hoops_SPHA = -1;				/* _hoops_HAR _hoops_AISP _hoops_GAPR */
	_hoops_SPHPR->face_count = 1;

	if (count > 0) {
		int alter *		_hoops_PSRGA;
		int				index = 0;

		ALLOC_ARRAY_ALIGNED (_hoops_SPHPR->points, count, Point, 16);
		_hoops_AIGA (points, count, Point, _hoops_SPHPR->points);

		_hoops_SPHPR->face_list_length = count + 1;
		ALLOC_ARRAY (_hoops_PSRGA, _hoops_SPHPR->face_list_length, int);
		_hoops_SPHPR->face_list = _hoops_PSRGA;
		*_hoops_PSRGA++ = count;
		while (count-- > 0)
			*_hoops_PSRGA++ = index++;
	}
	else {
		_hoops_SPHPR->points = null;
		_hoops_SPHPR->face_list_length = 0;
		_hoops_SPHPR->face_list = null;
	}

	_hoops_SPHPR->_hoops_CPGPR = _hoops_AHSGA;
	HI_Figure_Geometry_Bounding ((Geometry const *)_hoops_SPHPR, _hoops_SPHPR->bounding);
	_hoops_SPHPR->_hoops_CPGPR = _hoops_CASIR;

	*_hoops_CPSIH = _hoops_SPHPR;
}

local void _hoops_SHIPS (
	_hoops_AIHPR const *		_hoops_PIHPR,
	Shell alter **		_hoops_CPSIH) {
	Shell alter *		_hoops_SPHPR;
	int alter *			_hoops_PSRGA;
	int					row, col;

	ZALLOC (_hoops_SPHPR, Shell);
	_hoops_SPHPR->type = _hoops_SCIP;
	_hoops_SPHPR->_hoops_CPGPR = _hoops_PHSSR;
	_hoops_SPHPR->point_count = _hoops_PIHPR->point_count;
	_hoops_SPHPR->_hoops_SPHA = -1;
	_hoops_SPHPR->face_count = _hoops_PIHPR->face_count;

	ALLOC_ARRAY_ALIGNED (_hoops_SPHPR->points, _hoops_SPHPR->point_count, Point, 16);
	_hoops_AIGA (_hoops_PIHPR->points, _hoops_SPHPR->point_count, Point, _hoops_SPHPR->points);

	_hoops_SPHPR->face_list_length = 4 * _hoops_SPHPR->face_count;
	ALLOC_ARRAY (_hoops_PSRGA, _hoops_SPHPR->face_list_length, int);
	_hoops_SPHPR->face_list = _hoops_PSRGA;
	for (row=0; row < _hoops_PIHPR->rows-1; row++) {
		for (col=0; col < _hoops_PIHPR->columns-1; col++) {
			*_hoops_PSRGA++ = 3;
			*_hoops_PSRGA++ = row * _hoops_PIHPR->columns + col;
			*_hoops_PSRGA++ = (row+1) * _hoops_PIHPR->columns + col;
			*_hoops_PSRGA++ = row * _hoops_PIHPR->columns + col+1;

			*_hoops_PSRGA++ = 3;
			*_hoops_PSRGA++ = (row+1) * _hoops_PIHPR->columns + col;
			*_hoops_PSRGA++ = (row+1) * _hoops_PIHPR->columns + col+1;
			*_hoops_PSRGA++ = row * _hoops_PIHPR->columns + col+1;
		}
	}

	/* _hoops_AIRC _hoops_GRS _hoops_SHH _hoops_GIIPS _hoops_GGR _hoops_SPHR _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_IS _hoops_RIIPS _hoops_RH _hoops_RRRPR _hoops_HCR _hoops_RH _hoops_PPRRR _hoops_IS _hoops_ARI */
	_hoops_SPHPR->_hoops_CPGPR = _hoops_AHSGA;
	HI_Figure_Geometry_Bounding ((Geometry const *)_hoops_SPHPR, _hoops_SPHPR->bounding);
	_hoops_SPHPR->_hoops_CPGPR = _hoops_CASIR;

	*_hoops_CPSIH = _hoops_SPHPR;
}

local void _hoops_GSHPS (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_AIHPR const *				_hoops_PIHPR,
	Shell alter *				_hoops_SPHPR) {

	_hoops_SPHPR->_hoops_IPPGR = HI_Clone_Attributes (_hoops_RIGC, _hoops_PIHPR->_hoops_IPPGR, _hoops_SPHPR->owner, true, null);

	/* _hoops_GPHA & _hoops_HSP _hoops_RGCPR _hoops_IPS _hoops_GAR _hoops_GGR _hoops_AIIPS, _hoops_SPPR _hoops_RRP _hoops_PIIPS,
	 * _hoops_AHSAR _hoops_RH _hoops_ISIA, _hoops_PGAP _hoops_SR _hoops_RRP _hoops_IS _hoops_IPS _hoops_IHAAR _hoops_CR _hoops_SR _hoops_SPGA'_hoops_RA _hoops_GHGA _hoops_PA _hoops_PII
	 * _hoops_HIIPS()
	 */
	{
		Local_Vertex_Attributes const	*_hoops_HRRSA;
		Local_Vertex_Attributes			*_hoops_IRRSA;
		int									count;

		_hoops_HRRSA = &_hoops_PIHPR->local_vertex_attributes;
		_hoops_IRRSA = &_hoops_SPHPR->local_vertex_attributes;
		count = _hoops_PIHPR->point_count;
		if (count < 0) count = 0;

		if (BIT(_hoops_PIHPR->polyhedron_flags, _hoops_CGRHR)) {
			_hoops_APRGA(_hoops_HRRSA->flags, count, Local_Vertex_Flags, _hoops_IRRSA->flags);
			_hoops_SPHPR->polyhedron_flags |= _hoops_CGRHR;
		}
		else
			_hoops_IRRSA->_hoops_SGRHR = _hoops_HRRSA->_hoops_SGRHR;
		_hoops_IRRSA->_hoops_PAHIR = (RGB *) HI_Clone_Anything (_hoops_HRRSA->_hoops_PAHIR, count * (long)sizeof(RGB));
		_hoops_IRRSA->ecolors = (RGB *) HI_Clone_Anything (_hoops_HRRSA->ecolors, count * (long)sizeof(RGB));
		_hoops_IRRSA->fcolors = (RGB *) HI_Clone_Anything (_hoops_HRRSA->fcolors, count * (long)sizeof(RGB));
		_hoops_IRRSA->_hoops_HAHIR = (_hoops_ACGHR *) HI_Clone_Anything (_hoops_HRRSA->_hoops_HAHIR, count * (long)sizeof(_hoops_ACGHR));
		_hoops_IRRSA->_hoops_HGHIR = (_hoops_ACGHR *) HI_Clone_Anything (_hoops_HRRSA->_hoops_HGHIR, count * (long)sizeof(_hoops_ACGHR));
		_hoops_IRRSA->_hoops_IGHIR = (_hoops_ACGHR *) HI_Clone_Anything (_hoops_HRRSA->_hoops_IGHIR, count * (long)sizeof(_hoops_ACGHR));
		_hoops_IRRSA->_hoops_CAHIR = (float *) HI_Clone_Anything (_hoops_HRRSA->_hoops_CAHIR, count * (long)sizeof(float));
		_hoops_IRRSA->_hoops_SAHIR = (unsigned char *) HI_Clone_Anything (_hoops_HRRSA->_hoops_SAHIR, count * (long)sizeof(unsigned char));

		/* _hoops_ACAHP _hoops_IPS _hoops_SRRSA _hoops_HIGR */
		if (_hoops_HRRSA->_hoops_GPHIR) {
			_hoops_RPHIR *		_hoops_GARSA = _hoops_HRRSA->_hoops_GPHIR;
			_hoops_RPHIR *		_hoops_APHIR;
			_hoops_RPHIR **		_hoops_RARSA = &_hoops_IRRSA->_hoops_GPHIR;

			while (_hoops_GARSA) {
				ALLOC (_hoops_APHIR, _hoops_RPHIR);
				_hoops_APHIR->_hoops_HSAI = _hoops_GARSA->_hoops_HSAI;
				HI_Copy_Name (&_hoops_GARSA->name, &_hoops_APHIR->name);
				_hoops_APHIR->key = _hoops_GARSA->key;
				_hoops_APHIR->id = _hoops_GARSA->id;
				*_hoops_RARSA = _hoops_APHIR;
				_hoops_RARSA = &_hoops_APHIR->next;
				_hoops_GARSA = _hoops_GARSA->next;
			}
			*_hoops_RARSA = null;
		}
		else
			_hoops_IRRSA->_hoops_GPHIR = null;

		if (_hoops_HRRSA->normals != null) {
			if (_hoops_IRRSA->normals == null)
				ALLOC_ARRAY (_hoops_IRRSA->normals, count, Vector);
			_hoops_AIGA (_hoops_HRRSA->normals, count, Vector, _hoops_IRRSA->normals);
		}
		_hoops_IRRSA->params = (_hoops_RSSH *) HI_Clone_Anything (_hoops_HRRSA->params, (long)(count*sizeof(_hoops_RSSH)*_hoops_HRRSA->param_width));
		_hoops_IRRSA->param_width = _hoops_HRRSA->param_width;

		_hoops_IRRSA->_hoops_PPHIR = 0;
		_hoops_IRRSA->_hoops_HPHIR = 0;
		_hoops_IRRSA->_hoops_IPHIR = 0;

		_hoops_IRRSA->_hoops_CPIAA = _hoops_HRRSA->_hoops_CPIAA;
		_hoops_IRRSA->_hoops_SIIPR = _hoops_HRRSA->_hoops_SIIPR;
		_hoops_IRRSA->_hoops_ICRRA = _hoops_HRRSA->_hoops_ICRRA;
		_hoops_IRRSA->_hoops_PCRRA = _hoops_HRRSA->_hoops_PCRRA;
		_hoops_IRRSA->_hoops_HIRRA = _hoops_HRRSA->_hoops_HIRRA;
		_hoops_IRRSA->_hoops_SCHPR = _hoops_HRRSA->_hoops_SCHPR;
		_hoops_IRRSA->_hoops_CCHPR = _hoops_HRRSA->_hoops_CCHPR;
		_hoops_IRRSA->_hoops_RCRHR = _hoops_HRRSA->_hoops_RCRHR;
		_hoops_IRRSA->_hoops_SIRHR = _hoops_HRRSA->_hoops_SIRHR;
		_hoops_IRRSA->_hoops_SCHHC = _hoops_HRRSA->_hoops_SCHHC;
		_hoops_IRRSA->_hoops_AHIIC = _hoops_HRRSA->_hoops_AHIIC;
		_hoops_IRRSA->_hoops_RSAPA = _hoops_HRRSA->_hoops_RSAPA;
		_hoops_IRRSA->explicit_normal_count = _hoops_HRRSA->explicit_normal_count;
		_hoops_IRRSA->_hoops_CACCP = _hoops_HRRSA->_hoops_CACCP;
	}

	{
		Local_Face_Attributes const	*	_hoops_CARSA;
		Local_Face_Attributes		*	_hoops_SARSA;
		int								count;

		_hoops_CARSA	 = &_hoops_PIHPR->local_face_attributes;
		_hoops_SARSA	 = &_hoops_SPHPR->local_face_attributes;
		count = _hoops_PIHPR->face_count;
		if (count < 0) count = 0;


		if (BIT(_hoops_PIHPR->polyhedron_flags, _hoops_APRHR)) {
			_hoops_APRGA(_hoops_CARSA->flags, count, _hoops_GIIPR, _hoops_SARSA->flags);
			_hoops_SPHPR->polyhedron_flags |= _hoops_APRHR;
		}
		else
			_hoops_SARSA->_hoops_SGRHR = _hoops_CARSA->_hoops_SGRHR;
		_hoops_SARSA->colors = (RGB *) HI_Clone_Anything (_hoops_CARSA->colors, count * (long)sizeof(RGB));
		_hoops_SARSA->findices = (_hoops_ACGHR *) HI_Clone_Anything (_hoops_CARSA->findices, count * (long)sizeof(_hoops_ACGHR));
		_hoops_SARSA->_hoops_AHHIR = (unsigned char *) HI_Clone_Anything (_hoops_CARSA->_hoops_AHHIR, count * (long)sizeof(unsigned char));

		if (_hoops_CARSA->normals != null) {
			if (_hoops_SARSA->normals == null)
				ALLOC_ARRAY_ALIGNED (_hoops_SARSA->normals, count, _hoops_ARPA, 16);
			_hoops_AIGA (_hoops_CARSA->normals, count, _hoops_ARPA, _hoops_SARSA->normals);
		}

		_hoops_SARSA->_hoops_CPIAA = _hoops_CARSA->_hoops_CPIAA;
		_hoops_SARSA->_hoops_SIIPR = _hoops_CARSA->_hoops_SIIPR;
		_hoops_SARSA->_hoops_HSRRA = _hoops_CARSA->_hoops_HSRRA;
		_hoops_SARSA->_hoops_PSRRA = _hoops_CARSA->_hoops_PSRRA;
		_hoops_SARSA->_hoops_SRAPA = _hoops_CARSA->_hoops_SRAPA;
		_hoops_SARSA->explicit_normal_count = _hoops_CARSA->explicit_normal_count;
	}

	_hoops_SPHPR->local_face_attributes.regions =
		(int *) HI_Clone_Anything (_hoops_PIHPR->local_face_attributes.regions,
								   _hoops_PIHPR->face_count * (long)sizeof(int)+_hoops_SHHIR);

	{
		_hoops_RPGHR const	*_hoops_AARSA;
		_hoops_RPGHR		*_hoops_PARSA;
		int								count;
		_hoops_GHHPR				which = 0;

		_hoops_AARSA	 = &_hoops_PIHPR->_hoops_IHHPR;
		_hoops_PARSA	 = &_hoops_SPHPR->_hoops_IHHPR;
		count = _hoops_PIHPR->_hoops_SPHA;

		if (_hoops_AARSA->_hoops_CPIAA != 0 || _hoops_AARSA->_hoops_SIIPR)
			which |= _hoops_ICICA;
		if (_hoops_AARSA->_hoops_HSRRA != 0)
			which |= _hoops_SSRRA;
		if (_hoops_AARSA->_hoops_PSRRA != 0)
			which |= _hoops_RPGI;
		if (_hoops_AARSA->_hoops_SRAPA != 0)
			which |= _hoops_GPGI;
		if (_hoops_AARSA->_hoops_CCHHC != 0)
			which |= _hoops_SCICA;
		if (_hoops_AARSA->explicit_normal_count != 0)
			which |= _hoops_CRAHR;

		if (which != 0) {
			int				_hoops_IIIPS = 0;
			int				row, col;

			HI_Initialize_Edge_Attributes ((Polyhedron *)_hoops_SPHPR, which);

			for (row=0; row < _hoops_PIHPR->rows; row++) {
				for (col=0; col < _hoops_PIHPR->columns; col++) {
					int			_hoops_CCAPA = row * _hoops_PIHPR->columns + col;
					int			direction;

					for (direction=0; direction < 3; direction++) {
						int				_hoops_CIIPS = -1;

						if (direction == 0) {
							/* _hoops_HPPR _hoops_ISHA _hoops_SIIPS _hoops_RPHR _hoops_HII "_hoops_PPSR" */
							if (col < _hoops_PIHPR->columns-1)
								_hoops_CIIPS = 3 * _hoops_CCAPA;
						}
						else if (direction == 1) {
							/* _hoops_HPPR _hoops_ISHA _hoops_SIIPS _hoops_GH _hoops_IS _hoops_RAAP */
							if (col > 0 && row < _hoops_PIHPR->rows-1)
								_hoops_CIIPS = 3 * _hoops_CCAPA + 2;
						}
						else if (direction == 2) {
							/* _hoops_HPPR _hoops_ISHA _hoops_SIIPS _hoops_GH */
							if (row < _hoops_PIHPR->rows-1)
								_hoops_CIIPS = 3 * _hoops_CCAPA + 1;
						}

						if (_hoops_CIIPS >= 0) {	/* _hoops_IRS _hoops_HPHR _hoops_ISHA, _hoops_HAR _hoops_SAHR _hoops_SGGGH */
							_hoops_GHHPR		flags;

							flags = _hoops_PARSA->flags[_hoops_IIIPS] = _hoops_AARSA->flags[_hoops_CIIPS];
							if (BIT (flags, _hoops_SSRRA))
								_hoops_PARSA->colors[_hoops_IIIPS] = _hoops_AARSA->colors[_hoops_CIIPS];
							if (BIT (flags, _hoops_RPGI))
								_hoops_PARSA->findices[_hoops_IIIPS] = _hoops_AARSA->findices[_hoops_CIIPS];
							if (BIT (flags, _hoops_GPGI))
								_hoops_PARSA->_hoops_AHHIR[_hoops_IIIPS] = _hoops_AARSA->_hoops_AHHIR[_hoops_CIIPS];
							if (BIT (flags, _hoops_SCICA))
								_hoops_PARSA->weights[_hoops_IIIPS] = _hoops_AARSA->weights[_hoops_CIIPS];
							if (BIT (flags, _hoops_CRAHR))
								_hoops_PARSA->normals[_hoops_IIIPS] = _hoops_AARSA->normals[_hoops_CIIPS];

							_hoops_IIIPS++;
						}
					}
				}
			}
		}

		_hoops_PARSA->_hoops_CPIAA = _hoops_AARSA->_hoops_CPIAA;
		_hoops_PARSA->_hoops_SIIPR = _hoops_AARSA->_hoops_SIIPR;
		_hoops_PARSA->_hoops_HSRRA = _hoops_AARSA->_hoops_HSRRA;
		_hoops_PARSA->_hoops_PSRRA = _hoops_AARSA->_hoops_PSRRA;
		_hoops_PARSA->_hoops_SRAPA = _hoops_AARSA->_hoops_SRAPA;
		_hoops_PARSA->_hoops_CCHHC = _hoops_AARSA->_hoops_CCHHC;
		_hoops_PARSA->explicit_normal_count = _hoops_AARSA->explicit_normal_count;

		/* _hoops_ACAHP _hoops_IPS _hoops_PAIA _hoops_HIGR */
		if (_hoops_AARSA->_hoops_PHHIR) {
			_hoops_HHHIR *_hoops_HARSA = _hoops_AARSA->_hoops_PHHIR;
			_hoops_HHHIR *_hoops_CHHIR;
			_hoops_HHHIR **_hoops_IARSA = &_hoops_PARSA->_hoops_PHHIR;

			while (_hoops_HARSA) {
				ALLOC (_hoops_CHHIR, _hoops_HHHIR);
				_hoops_CHHIR->_hoops_HSAI = _hoops_HARSA->_hoops_HSAI;
				HI_Copy_Name (&_hoops_HARSA->name, &_hoops_CHHIR->name);
				_hoops_CHHIR->key = _hoops_HARSA->key;
				_hoops_CHHIR->id = _hoops_HARSA->id;
				*_hoops_IARSA = _hoops_CHHIR;
				_hoops_IARSA = &_hoops_CHHIR->next;
				_hoops_HARSA = _hoops_HARSA->next;
			}
			*_hoops_IARSA = null;
		}
		else
			_hoops_PARSA->_hoops_PHHIR = null;
	}
}

local void _hoops_GCIPS (
	_hoops_AIGPR *	_hoops_RIGC,
	Grid const *			grid,
	Shell alter **			_hoops_CPSIH) {
	Shell alter *			_hoops_SPHPR;
	int alter *				_hoops_PSRGA;
	Point alter *			points;

	ZALLOC (_hoops_SPHPR, Shell);
	_hoops_SPHPR->type = _hoops_SCIP;
	_hoops_SPHPR->_hoops_CPGPR = _hoops_PHSSR;
	_hoops_SPHPR->_hoops_SPHA = -1;
	*_hoops_CPSIH = _hoops_SPHPR;


	switch (grid->_hoops_APIAA) {
		case _hoops_PPIAA: {
			int	_hoops_RCIPS, _hoops_ACIPS, _hoops_PCIPS, _hoops_PSIGC;

			if (grid->count1 < 0) {
				_hoops_RCIPS =  grid->count1;
				_hoops_ACIPS = -grid->count1;
			}
			else if (grid->count1> 0) {
				_hoops_RCIPS = 0;
				_hoops_ACIPS = grid->count1;
			}
			else {
				_hoops_RCIPS = -64;
				_hoops_ACIPS =  64;
			}
			if (grid->count2 < 0) {
				_hoops_PCIPS =  grid->count2;
				_hoops_PSIGC = -grid->count2;
			}
			else if (grid->count2> 0) {
				_hoops_PCIPS = 0;
				_hoops_PSIGC = grid->count2;
			}
			else {
				_hoops_PCIPS = -64;
				_hoops_PSIGC =  64;
			}

			int	count;
			int _hoops_HCIPS = _hoops_ACIPS - _hoops_RCIPS + 1;
			_hoops_SPHPR->point_count = count = _hoops_HCIPS * (_hoops_PSIGC - _hoops_PCIPS + 1);
			ALLOC_ARRAY_ALIGNED (points, count, Point, 16);
			_hoops_SPHPR->points = points;

			for (int row=_hoops_PCIPS; row<=_hoops_PSIGC; row++) {
				for (int col=_hoops_RCIPS; col<=_hoops_ACIPS; col++) {
					points->x = grid->origin.x + col * grid->_hoops_GGHI.x + row * grid->_hoops_RGHI.x;
					points->y = grid->origin.y + col * grid->_hoops_GGHI.y + row * grid->_hoops_RGHI.y;
					points->z = grid->origin.z + col * grid->_hoops_GGHI.z + row * grid->_hoops_RGHI.z;
					points++;
				}
			}

			_hoops_SPHPR->face_count = count = (_hoops_ACIPS - _hoops_RCIPS) * (_hoops_PSIGC - _hoops_PCIPS);
			_hoops_SPHPR->face_list_length = 5 * _hoops_SPHPR->face_count;
			ALLOC_ARRAY (_hoops_PSRGA, _hoops_SPHPR->face_list_length, int);
			_hoops_SPHPR->face_list = _hoops_PSRGA;

			for (int row=0; row<_hoops_PSIGC-_hoops_PCIPS; row++) {
				for (int col=0; col<_hoops_ACIPS-_hoops_RCIPS; col++) {
					*_hoops_PSRGA++ = 4;
					*_hoops_PSRGA++ = row * _hoops_HCIPS + col;
					*_hoops_PSRGA++ = row * _hoops_HCIPS + col+1;
					*_hoops_PSRGA++ = (row+1) * _hoops_HCIPS + col+1;
					*_hoops_PSRGA++ = (row+1) * _hoops_HCIPS + col;
				}
			}
		}	break;

		case _hoops_SPARP: {
			int		_hoops_ACIPS, _hoops_PCIPS, _hoops_PSIGC;
			float	start, end;
			int		_hoops_ICIPS, _hoops_CCIPS;
			bool	_hoops_SPGPA = false;

			if (grid->count1 < 0)
				_hoops_ACIPS = -grid->count1;
			else if (grid->count1 > 0)
				_hoops_ACIPS = grid->count1;
			else
				_hoops_ACIPS = 64;

			if (grid->count2 < 0) {
				_hoops_PCIPS = grid->count2;
				_hoops_PSIGC = -grid->count2;
				if (-2*grid->count2 >= grid->_hoops_IPIAA) {
					_hoops_PCIPS = 0;
					_hoops_PSIGC = grid->_hoops_IPIAA;
					start = 0.0f;
					end = 360.0f;
					_hoops_SPGPA = true;
				}
				else {
					end = grid->count2 * 360.0f / grid->_hoops_IPIAA;
					start = -end;
				}
			}
			else if (grid->count2 > 0) {
				_hoops_PCIPS = 0;
				_hoops_PSIGC = grid->count2;
				start = 0.0f;
				if (grid->count2 >= grid->_hoops_IPIAA) {
					_hoops_PSIGC = grid->_hoops_IPIAA;
					end = 360.0f;
					_hoops_SPGPA = true;
				}
				else
					end = grid->count2 * 360.0f / grid->_hoops_IPIAA;
			}
			else {
				_hoops_PCIPS = 0;
				_hoops_PSIGC = grid->_hoops_IPIAA;
				start = 0.0f;
				end = 360.0f;
				_hoops_SPGPA = true;
			}

			int	_hoops_SCIPS = 36 / grid->_hoops_IPIAA;

			int	count = _hoops_ACIPS * (_hoops_ACIPS+1) / 2;	/* _hoops_SPR _hoops_CSCS _hoops_GCHPA */
			count *= _hoops_SCIPS;			/* _hoops_ASSS _hoops_IH _hoops_PHPA _hoops_GSGRS */
			if (_hoops_SPGPA)
				count *= grid->_hoops_IPIAA;
			else {
				count *= _hoops_PSIGC - _hoops_PCIPS;
				count += _hoops_ACIPS;				/* _hoops_CSGR _hoops_RSSA */
			}
			count++;						/* _hoops_CGRS */

			_hoops_SPHPR->point_count = count;
			ALLOC_ARRAY_ALIGNED (points, count, Point, 16);
			_hoops_SPHPR->points = points;
			HI_Initialize_Vertex_Attributes ((Polyhedron *)_hoops_SPHPR, _hoops_HHIAA, 0);

			*points = grid->origin;
			points++;
			_hoops_ICIPS = 0;
			_hoops_CCIPS = 1;

			for (int i=1; i<=_hoops_ACIPS; i++) {
				int			_hoops_SRIAA;
				float		delta;
				int			face_list[1000];

				if (_hoops_SPGPA) {
					_hoops_SRIAA = grid->_hoops_IPIAA * i * _hoops_SCIPS;
					delta = (end - start) / (float)_hoops_SRIAA;
				}
				else {
					_hoops_SRIAA = (_hoops_PSIGC-_hoops_PCIPS) * i * _hoops_SCIPS + 1;
					delta = (end - start) / (float)(_hoops_SRIAA - 1);
				}


				for (int j=0; j<_hoops_SRIAA; j++) {
					float		_hoops_RAHCR = start + j*delta;
					float		_hoops_GGHCR, _hoops_AGHCR;

					_hoops_RICH (_hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR);
					points->x = grid->origin.x + i * (_hoops_AGHCR * grid->_hoops_GGHI.x + _hoops_GGHCR * grid->_hoops_RGHI.x);
					points->y = grid->origin.y + i * (_hoops_AGHCR * grid->_hoops_GGHI.y + _hoops_GGHCR * grid->_hoops_RGHI.y);
					points->z = grid->origin.z + i * (_hoops_AGHCR * grid->_hoops_GGHI.z + _hoops_GGHCR * grid->_hoops_RGHI.z);

					if (j % (i*_hoops_SCIPS) != 0) {
						if (!BIT(_hoops_SPHPR->polyhedron_flags, _hoops_CGRHR)) {
							ZALLOC_ARRAY(_hoops_SPHPR->local_vertex_attributes.flags, _hoops_SPHPR->point_count, Local_Vertex_Flags);
							for (int k = 0; k < _hoops_SPHPR->point_count; k++)
								_hoops_SPHPR->local_vertex_attributes.flags[k] = _hoops_SPHPR->local_vertex_attributes._hoops_SGRHR;
							_hoops_SPHPR->polyhedron_flags |= _hoops_CGRHR;
						}
						*_hoops_SPHPR->local_vertex_attributes._hoops_CHHPR(points-_hoops_SPHPR->points) = _hoops_HHIAA;
						++_hoops_SPHPR->local_vertex_attributes._hoops_SIIPR;
					}
					points++;
				}

				for (int j=0; j<(_hoops_PSIGC-_hoops_PCIPS); j++) {
					_hoops_PSRGA = face_list;
					*_hoops_PSRGA++ = (i-1)*_hoops_SCIPS+1 + i*_hoops_SCIPS+1;
					for (int k=(i-1)*_hoops_SCIPS; k>=0; k--) {
						int	offset = j*(i-1)*_hoops_SCIPS + k;

						if (i > 1)
							offset %= grid->_hoops_IPIAA*(i-1)*_hoops_SCIPS;
						*_hoops_PSRGA++ = _hoops_ICIPS + offset;
					}
					for (int k=0; k<=i*_hoops_SCIPS; k++) {
						int	offset = j*i*_hoops_SCIPS + k;

						offset %= grid->_hoops_IPIAA*i*_hoops_SCIPS;
						*_hoops_PSRGA++ = _hoops_ICIPS + _hoops_CCIPS + offset;
					}

					/* _hoops_GGCR _hoops_HSP */
					PUSHNAME(_hoops_RIGC);
					HC_Edit_Shell_Faces (_hoops_AIRIR(_hoops_SPHPR), -1, 0, _hoops_PSRGA-face_list, face_list);
					POPNAME(_hoops_RIGC);
				}

				_hoops_ICIPS += _hoops_CCIPS;
				_hoops_CCIPS = _hoops_SRIAA;
			}
		}	break;
	}

	_hoops_SPHPR->_hoops_CPGPR = _hoops_AHSGA;
	HI_Figure_Geometry_Bounding ((Geometry const *)_hoops_SPHPR, _hoops_SPHPR->bounding);
	_hoops_SPHPR->_hoops_CPGPR = _hoops_PHSSR;
}

GLOBAL_FUNCTION void HI_Convert_To_Shell (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			options,
	Geometry const *		geom,
	Shell alter **			_hoops_CPSIH,
	Shell alter **			_hoops_SPSIH)
{
	Geometry *				_hoops_GSIPS = null;

	_hoops_HIACR (_hoops_HIRGI, _hoops_RPHPS);

	*_hoops_SPSIH = null;

	switch (geom->type) {
		case _hoops_PRCP: {
			_hoops_CRIPS (_hoops_RIGC, options, (_hoops_APPGR *)geom, _hoops_CPSIH);
		}	break;

		case _hoops_ASIP: {
			geom = _hoops_GSIPS = (Geometry *)HI_Cylinder_To_PolyCylinder ((Cylinder *)geom);
		}	_hoops_HHHI;
		case _hoops_CSIP:
		case _hoops_HSIP: {
			_hoops_RHIPS (_hoops_RIGC, options, geom, _hoops_SPSIH);
		}	break;

		case _hoops_RCIP: {
			Polygon const *	_hoops_RPIGA = (Polygon const *)geom;
			_hoops_CHIPS (_hoops_RPIGA->count, _hoops_RPIGA->points, _hoops_SPSIH);
		}	break;

		case _hoops_SGCP:
		case _hoops_GRCP:
		case _hoops_RRCP:
		case _hoops_CGCP: {
			Point *		points;
			int				count;
			int				use_count;

			PUSHNAME(_hoops_RIGC);
			HC_Compute_Polyline_From_Curve (_hoops_AIRIR(geom), options, &count, null);
			ALLOC_ARRAY (points, count, Point);
			HC_Compute_Polyline_From_Curve (_hoops_AIRIR(geom), options, &count, points);
			POPNAME(_hoops_RIGC);

			use_count = count;
			if (geom->type == _hoops_SGCP || geom->type == _hoops_CGCP)
				--use_count;	/* _hoops_GA'_hoops_RA _hoops_RRP _hoops_HHHA _hoops_GGGR */

			_hoops_CHIPS (use_count, points, _hoops_SPSIH);

			FREE_ARRAY (points, count, Point);
		}	break;

		case _hoops_GSIP: {
			_hoops_SHIPS ((_hoops_AIHPR const *)geom, _hoops_SPSIH);
		}	break;

		case _hoops_GGCP: {
			_hoops_GCIPS (_hoops_RIGC, (Grid const *)geom, _hoops_SPSIH);
		}	break;

		default:
			HE_ERROR (HEC_GEOMETRY, HES_INVALID_KEY,
				"Provided key does not refer to a valid surface-based geometry");
	}

	if (*_hoops_SPSIH != null) {
		*_hoops_CPSIH = *_hoops_SPSIH;
		(*_hoops_SPSIH)->_hoops_CPGPR |= _hoops_CASIR;
	}
	if (_hoops_GSIPS != null)
		_hoops_HPRH (_hoops_GSIPS);
}

#endif /* _hoops_IHS _hoops_CPAP _hoops_CRGH */


HC_INTERFACE void HC_CDECL HC_Show_Shell_By_Tristrips_Size (
	Key				key,
	int *			point_countp,
	int *			_hoops_IGIPS,
	int *			face_list_lengthp)
{
	_hoops_PAPPR context("Show_Shell_By_Tristrips_Size");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Shell_Size () */\n");
	);

	Shell *			victim	= null;

	_hoops_CSPPR();

	Shell *	_hoops_SPHPR = (Shell *)_hoops_RCSSR (context, key);
	_hoops_RCHPS (context, &_hoops_SPHPR, &victim);

	if (_hoops_SPHPR == null ||
		_hoops_SPHPR->type != _hoops_SCIP ||
		BIT (_hoops_SPHPR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_KEY,
				"Provided key does not refer to a valid shell");
	}
	else {
		if (point_countp != null)
			*point_countp = _hoops_SPHPR->point_count;

		if (_hoops_IGIPS || face_list_lengthp) {
			if ((_hoops_SPHPR->face_list != null) &&
				(_hoops_SPHPR->tristrips == null))
				HI_Assemble_3D_Tristrips ((Polyhedron *)_hoops_SPHPR, 0xff, true);

			_hoops_HGIPS (_hoops_SPHPR->tristrips,
								 _hoops_IGIPS, face_list_lengthp);
		}
	}
	if (victim)
		HI_Au_Revoir ((_hoops_HPAH *)victim);
	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Shell_By_Tristrips (
	Key				key,
	int				*point_countp,
	Point			*points,
	int *			_hoops_IGIPS,
	int *			_hoops_RSIPS,
	int *			face_list_lengthp,
	int *			face_list)
{
	_hoops_PAPPR context("Show_Shell_By_Tristrips");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Shell_By_Tristrips () */\n");
	);

	_hoops_CSPPR();

	Shell *			victim	= null;
	alter int *		_hoops_ASIPS = _hoops_RSIPS;
	alter int *		_hoops_RRPHC = face_list;
	Tristrip *		_hoops_CPCR;

	Shell *	_hoops_SPHPR = (Shell *)_hoops_RCSSR (context, key);
	_hoops_RCHPS (context, &_hoops_SPHPR, &victim);

	if (_hoops_SPHPR == null ||
		_hoops_SPHPR->type != _hoops_SCIP ||
		BIT (_hoops_SPHPR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_KEY, "Provided key does not refer to a valid shell");
	}
	else {
		if (point_countp != null)
			*point_countp = _hoops_SPHPR->point_count;

		if (points != null)
			_hoops_AIGA (_hoops_SPHPR->points, _hoops_SPHPR->point_count, Point, points);

		if (_hoops_IGIPS || face_list_lengthp || _hoops_RSIPS || face_list) {
			if (_hoops_SPHPR->face_list != null && _hoops_SPHPR->tristrips == null)
				HI_Assemble_3D_Tristrips ((Polyhedron *)_hoops_SPHPR, 0xff, true);

			_hoops_HGIPS (_hoops_SPHPR->tristrips, _hoops_IGIPS, face_list_lengthp);
		}

		if (_hoops_RSIPS != null) {
			for (_hoops_CPCR = _hoops_SPHPR->tristrips; _hoops_CPCR != null; _hoops_CPCR = _hoops_CPCR->next) {
				int				_hoops_PHHA = _hoops_CPCR->_hoops_PHHA;
				int *			lengths = _hoops_CPCR->lengths;
				int *			vi = _hoops_CPCR->_hoops_AIHA;

				while (_hoops_PHHA-- > 0) {
					int			length = *lengths++;

					*_hoops_ASIPS++ = length;
					if (length < 0)
						length = -length;
					_hoops_AIGA (vi, length, int, _hoops_ASIPS);
					_hoops_ASIPS += length;
					vi += length;
				}
			}
		}
		if (face_list != null) {
			int				face = 0;

			for (_hoops_CPCR = _hoops_SPHPR->tristrips; _hoops_CPCR != null; _hoops_CPCR = _hoops_CPCR->next) {
				int				_hoops_PHHA = _hoops_CPCR->_hoops_PHHA;
				int *			lengths = _hoops_CPCR->lengths;
				int *			fi = _hoops_CPCR->face_indices;

				while (_hoops_PHHA-- > 0) {
					int			length = *lengths++;

					if (length < 0)
						length = -length;
					if (fi) {
						_hoops_AIGA (fi + 2, length-2, int, _hoops_RRPHC);
						fi += length;
						_hoops_RRPHC += length - 2;
					}
					else {
						length -= 2;
						while (length-- > 0)
							*_hoops_RRPHC++ = face++;
					}
				}
			}
		}
	}
	if (victim)
		HI_Au_Revoir ((_hoops_HPAH *)victim);
	_hoops_IRRPR();
#endif
}


GLOBAL_FUNCTION void HI_Show_Shell (
	_hoops_AIGPR *	_hoops_RIGC,
	Key						key,
	int *					point_countp,
	Point *					points,
	int *					face_list_lengthp,
	int *					face_list)
{
	Shell *					_hoops_SPHPR	= null;
	Shell *					victim	= null;

	_hoops_SPHPR = (Shell *)_hoops_RCSSR (_hoops_RIGC, key);
	_hoops_RCHPS (_hoops_RIGC, &_hoops_SPHPR, &victim);

	if (_hoops_SPHPR == null ||
		_hoops_SPHPR->type != _hoops_SCIP ||
		BIT (_hoops_SPHPR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_KEY, "Provided key does not refer to a valid shell");
	}
	else {
		if (point_countp != null)
			*point_countp = _hoops_SPHPR->point_count;

		if (points != null)
			_hoops_AIGA (_hoops_SPHPR->points, _hoops_SPHPR->point_count, Point, points);

		if (_hoops_SPHPR->tristrips != null &&
			_hoops_SPHPR->face_list == null &&
			face_list != null)
			HI_Face_List_From_Tristrips (_hoops_RIGC, _hoops_SPHPR);

		if (face_list != null) {
			_hoops_AIGA (_hoops_SPHPR->face_list, _hoops_SPHPR->face_list_length, int, face_list);
		}

		if (face_list_lengthp != null)
			*face_list_lengthp = _hoops_SPHPR->face_list_length;
	}
	if (victim)
		HI_Au_Revoir ((_hoops_HPAH *)victim);
}




HC_INTERFACE void HC_CDECL HC_Show_Shell (
	Key				key,
	int *			point_countp,
	Point *			points,
	int *			face_list_lengthp,
	int *			face_list)
{
	_hoops_PAPPR context("Show_Shell");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Shell () */\n");
	);

	_hoops_CSPPR();
	HI_Show_Shell (context, key, point_countp, points, face_list_lengthp, face_list);
	_hoops_IRRPR();

#endif
}



GLOBAL_FUNCTION void HI_Show_Shell_Size (
	_hoops_AIGPR *	_hoops_RIGC,
	Key						key,
	int *					point_countp,
	int *					face_list_lengthp)
{
	Shell *					_hoops_SPHPR	= null;
	Shell *					victim	= null;

	_hoops_SPHPR = (Shell *)_hoops_RCSSR (_hoops_RIGC, key);
	_hoops_RCHPS (_hoops_RIGC, &_hoops_SPHPR, &victim);

	if (_hoops_SPHPR == null ||
		_hoops_SPHPR->type != _hoops_SCIP ||
		BIT (_hoops_SPHPR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_KEY,
				"Provided key does not refer to a valid shell");
	}
	else {
		if (_hoops_SPHPR->tristrips != null &&
			_hoops_SPHPR->face_list == null &&
			face_list_lengthp != null)
			HI_Face_List_From_Tristrips (_hoops_RIGC, _hoops_SPHPR);

		if (point_countp != null)
			*point_countp = _hoops_SPHPR->point_count;

		if (face_list_lengthp != null)
			*face_list_lengthp = _hoops_SPHPR->face_list_length;
	}
	if (victim)
		HI_Au_Revoir ((_hoops_HPAH *)victim);
}



HC_INTERFACE void HC_CDECL HC_Show_Shell_Size (
	Key				key,
	int *			point_countp,
	int *			face_list_lengthp)
{
	_hoops_PAPPR context("Show_Shell_Size");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Shell_Size () */\n");
	);

	_hoops_CSPPR();
	HI_Show_Shell_Size (context, key, point_countp, face_list_lengthp);
	_hoops_IRRPR();

#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Shell_Face_Count (
	Key				key,
	int *			_hoops_AGSIH)
{
	_hoops_PAPPR context("Show_Shell_Face_Count");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Shell_Face_Count () */\n");
	);

	if (_hoops_AGSIH == null)
		return;

	_hoops_CSPPR();
	Shell *	_hoops_SPHPR = (Shell *)_hoops_RCSSR (context, key);

	Shell *	victim	= null;
	_hoops_RCHPS (context, &_hoops_SPHPR, &victim);

	if (_hoops_SPHPR == null ||
		_hoops_SPHPR->type != _hoops_SCIP ||
		BIT (_hoops_SPHPR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_KEY, "Provided key does not refer to a valid shell");
	}
	else {
		*_hoops_AGSIH = _hoops_SPHPR->face_count;
	}
	if (victim)
		HI_Au_Revoir ((_hoops_HPAH *)victim);
	_hoops_IRRPR();
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Shell_Tristrip_Count (
	Key				key,
	int *			_hoops_PSIPS)
{
	_hoops_PAPPR context("HC_Show_Shell_Tristrip_Count");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Shell_Tristrip_Count () */\n");
	);

	if (_hoops_PSIPS == null)
		return;

	_hoops_CSPPR();
	Shell *	_hoops_SPHPR = (Shell *)_hoops_RCSSR (context, key);

	Shell *	victim	= null;
	_hoops_RCHPS (context, &_hoops_SPHPR, &victim);

	if (_hoops_SPHPR == null ||
		_hoops_SPHPR->type != _hoops_SCIP ||
		BIT (_hoops_SPHPR->_hoops_RRHH, _hoops_HGAGR)) {
			HE_ERROR (HEC_TRISTRIP, HES_INVALID_KEY, "Provided key does not refer to a valid shell");
	}
	else {
		if ((_hoops_SPHPR->face_list != null) &&
			(_hoops_SPHPR->tristrips == null))
			HI_Assemble_3D_Tristrips ((Polyhedron *)_hoops_SPHPR, 0xff, true);

		if (_hoops_SPHPR->tristrips != null)
			*_hoops_PSIPS = _hoops_SPHPR->tristrips->_hoops_PHHA;
		else
			*_hoops_PSIPS = 0;
	}
	if (victim)
		HI_Au_Revoir ((_hoops_HPAH *)victim);
	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Partial_Shell (
	Key				key,
	int				_hoops_HSIPS,
	int				pcount,
	Point *			points,
	int				foffset,
	int				fcount,
	int *			face_list_lengthp,
	int *			face_list)
{
	_hoops_PAPPR context("Show_Partial_Shell");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Partial_Shell */\n");
	);

	if (_hoops_HSIPS < 0) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_OFFSET, "Unreasonable (negative) point offset");
		return;
	}
	if (pcount < 0) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_COUNT, "Unreasonable (negative) point count");
		return;
	}
	if (foffset < 0) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_FACE_OFFSET, "Unreasonable (negative) face offset");
		return;
	}
	if (fcount < 0) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_FACE_COUNT, "Unreasonable (negative) face count");
		return;
	}

	_hoops_CSPPR();
	Shell *	_hoops_SPHPR = (Shell *)_hoops_RCSSR (context, key);

	Shell *	victim	= null;
	_hoops_RCHPS (context, &_hoops_SPHPR, &victim);

	if (_hoops_SPHPR == null ||
		_hoops_SPHPR->type != _hoops_SCIP ||
		BIT (_hoops_SPHPR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_KEY, "Provided key does not refer to a valid shell");
	}
	else if (pcount > 0 && _hoops_HSIPS >= _hoops_SPHPR->point_count) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_OFFSET, "Provided offset exceeds number of vertices in shell");
	}
	else if (_hoops_HSIPS + pcount > _hoops_SPHPR->point_count) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_RANGE, "Provided range extends past last vertex of shell");
	}
	else if (fcount > 0 && foffset >= _hoops_SPHPR->face_count) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_FACE_OFFSET, "Provided offset exceeds number of faces in shell");
	}
	else if (foffset + fcount > _hoops_SPHPR->face_count) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_FACE_RANGE, "Provided range extends past last face of shell");
	}
	else {
		if (pcount > 0)
			_hoops_AIGA (_hoops_SPHPR->points + _hoops_HSIPS, pcount, Point, points);

		if (fcount != 0) {
			int *			_hoops_AIGRA;
			int				_hoops_RRC;
			int				count;
			int *			start;
			int 			length;

			if (_hoops_SPHPR->tristrips != null && _hoops_SPHPR->face_list == null)
				HI_Face_List_From_Tristrips (context, _hoops_SPHPR);
			_hoops_AIGRA = _hoops_SPHPR->face_list;

			/* _hoops_SICR _hoops_HSP _hoops_SHI _hoops_IS _hoops_HSP-_hoops_HIGR _hoops_SHI */

			if ((count = foffset) != 0) do {	/* _hoops_IH _hoops_GRR _hoops_HSP */
				_hoops_RRC = *_hoops_AIGRA++;
				_hoops_AIGRA += _hoops_RRC;				/* _hoops_PH _hoops_IGIAR */

				/* _hoops_PSSSR _hoops_IH _hoops_PCCPR */
				while ((_hoops_RRC = *_hoops_AIGRA) < 0)
					_hoops_AIGRA += 1 - _hoops_RRC;
			} _hoops_RGGA (--count == 0);

			start = _hoops_AIGRA;


			/* _hoops_SICR _hoops_HSP _hoops_RPR _hoops_IS _hoops_SPCC */

			if ((count = fcount) != 0) do {		/* _hoops_IH _hoops_GRR _hoops_HSP */
				_hoops_RRC = *_hoops_AIGRA++;
				_hoops_AIGRA += _hoops_RRC;				/* _hoops_PH _hoops_IGIAR */

				/* _hoops_RGAR _hoops_ISPR _hoops_IH _hoops_PCCPR _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_ISGR _hoops_RSGR _hoops_IIGR _hoops_CRPR */
				if (_hoops_AIGRA < _hoops_SPHPR->face_list + _hoops_SPHPR->face_list_length) {
					/* _hoops_PSSSR _hoops_IH _hoops_PCCPR */
					while ((_hoops_RRC = *_hoops_AIGRA) < 0 && (_hoops_AIGRA < _hoops_SPHPR->face_list + _hoops_SPHPR->face_list_length))
						_hoops_AIGRA += 1 - _hoops_RRC;
				}
			} _hoops_RGGA (--count == 0);

			length = _hoops_AIGRA - start;


			*face_list_lengthp = length;
			_hoops_AIGA (start, length, int, face_list);
		}
	}
	if (victim)
		HI_Au_Revoir ((_hoops_HPAH *)victim);
	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Partial_Shell_Size (
	Key				key,
	int				foffset,
	int				fcount,
	int *			face_list_lengthp)
{
	_hoops_PAPPR context("Show_Partial_Shell_Size");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Partial_Shell_Size () */\n");
	);

	if (foffset < 0) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_FACE_OFFSET, "Unreasonable (negative) face offset");
		return;
	}
	if (fcount < 0) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_FACE_COUNT, "Unreasonable (negative) face count");
		return;
	}

	_hoops_CSPPR();
	Shell *	_hoops_SPHPR = (Shell *)_hoops_RCSSR (context, key);

	Shell *	victim	= null;
	_hoops_RCHPS (context, &_hoops_SPHPR, &victim);

	if (_hoops_SPHPR == null ||
		_hoops_SPHPR->type != _hoops_SCIP ||
		BIT (_hoops_SPHPR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_KEY, "Provided key does not refer to a valid shell");
	}
	else if (foffset >= _hoops_SPHPR->face_count) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_FACE_OFFSET, "Provided offset exceeds number of faces in shell");
	}
	else if (foffset + fcount > _hoops_SPHPR->face_count) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_FACE_RANGE, "Provided range extends past last face of shell");
	}
	else {
		int *			_hoops_AIGRA = _hoops_SPHPR->face_list;
		int				_hoops_RRC;
		int				count;
		int *			start;
		int 			length;

		/* _hoops_SICR _hoops_HSP _hoops_SHI _hoops_IS _hoops_HSP-_hoops_HIGR _hoops_SHI */

		if ((count = foffset) != 0) do {		/* _hoops_IH _hoops_GRR _hoops_HSP */
			_hoops_RRC = *_hoops_AIGRA++;
			_hoops_AIGRA += _hoops_RRC;			/* _hoops_PH _hoops_IGIAR */

			/* _hoops_PSSSR _hoops_IH _hoops_PCCPR */
			while ((_hoops_RRC = *_hoops_AIGRA) < 0)
				_hoops_AIGRA += 1 - _hoops_RRC;
		} _hoops_RGGA (--count == 0);

		start = _hoops_AIGRA;


		/* _hoops_SICR _hoops_HSP _hoops_RPR _hoops_IS _hoops_SPCC */

		if ((count = fcount) != 0) do { /* _hoops_IH _hoops_GRR _hoops_HSP */
			_hoops_RRC = *_hoops_AIGRA++;
			_hoops_AIGRA += _hoops_RRC;			/* _hoops_PH _hoops_IGIAR */

			/* _hoops_RGAR _hoops_ISPR _hoops_IH _hoops_PCCPR _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_ISGR _hoops_RSGR _hoops_IIGR _hoops_CRPR */
			if (_hoops_AIGRA < _hoops_SPHPR->face_list + _hoops_SPHPR->face_list_length) {
				/* _hoops_PSSSR _hoops_IH _hoops_PCCPR */
				while ((_hoops_RRC = *_hoops_AIGRA) < 0 && (_hoops_AIGRA < _hoops_SPHPR->face_list + _hoops_SPHPR->face_list_length))
					_hoops_AIGRA += 1 - _hoops_RRC;
			}
		} _hoops_RGGA (--count == 0);

		length = _hoops_AIGRA - start;

		*face_list_lengthp = length;
	}

	_hoops_IRRPR();
#endif
}

GLOBAL_FUNCTION void HI_Edit_Shell_Faces (
	_hoops_AIGPR *	_hoops_RIGC,
	Shell *					_hoops_SPHPR,
	int						ioffset,
	int						ndelete,
	int						_hoops_CSSIH,
	int	const *				insert_list)
{
	_hoops_ICIIR(_hoops_RIGC);

	bool	_hoops_HAHRI = (_hoops_RIGC->_hoops_CACAA == _hoops_RIGC->_hoops_SACAA);

HOOPS_WORLD->_hoops_RCHGI=1;	// _hoops_PGHGR _hoops_ACPC _hoops_APSA
	if (_hoops_HAHRI)
		_hoops_RPPPR();
HOOPS_WORLD->_hoops_RCHGI=0;

	int						offset = ioffset;
	int						insert;
	int						count;

	/*
	 * _hoops_GCAAI _hoops_IPAC
	 */

	if (offset == -1)
		offset = _hoops_SPHPR->face_count;

	if (offset < 0 || ndelete < 0 || _hoops_CSSIH < 0) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_NUMBER, "The offset, delete count, or insertion count is negative");
		goto Release;
	}

	if (offset + ndelete > _hoops_SPHPR->face_count) {
		char			buf[MAX_ERRMSG];

		if (ioffset == -1)
			HE_ERROR (HEC_TRISTRIP, HES_INVALID_OFFSET, "Can't delete faces after the end of the list (offset is -1)");
		else
			HE_ERROR2 (HEC_TRISTRIP, HES_INVALID_OFFSET,
					Sprintf_DD (null,"Can't delete or replace as many as %d faces at offset %d -",ndelete, ioffset),
					   Sprintf_D (buf, "the shell only has %d", _hoops_SPHPR->face_count));
		goto Release;
	}

	if (_hoops_CSSIH == 0)
		insert = 0;
	else if (!HI_Validate_Face_List (_hoops_SPHPR->point_count,
									 _hoops_CSSIH,
									 insert_list,
									 &insert))
		goto Release;


	if (ndelete == 0 && insert == 0)
		goto Release; /* _hoops_CPRSH */

	if (_hoops_SPHPR->face_list == null && _hoops_SPHPR->tristrips != null) {
		HE_ERROR (HEC_MEMORY, HES_REBUILDING_TRISTRIP, "Face list data has been discarded, can not Edit");
		goto Release;
	}

	/*
	 * _hoops_HCR _hoops_GPRS, _hoops_AA _hoops_SCH
	 */

	if (_hoops_SPHPR->face_count + insert - ndelete == 0) {
		if (_hoops_SPHPR->face_list != null) {
			FREE_ARRAY (_hoops_SPHPR->face_list, _hoops_SPHPR->face_list_length, int);
			_hoops_SPHPR->face_list = null;
			_hoops_SPHPR->face_list_length = 0;
		}
	}
	else {
		int				_hoops_ISIPS;
		int				_hoops_ASCRA;

		/*
		 * _hoops_HIGAA _hoops_RH _hoops_CCAH _hoops_HSP _hoops_HIGR _hoops_GGR
		 */

		{
			int *			_hoops_AIGRA = _hoops_SPHPR->face_list;
			int				_hoops_RRC;
			int *			_hoops_CASRS = _hoops_AIGRA + _hoops_SPHPR->face_list_length;

			/* _hoops_SICR _hoops_HSP _hoops_SHI _hoops_IS _hoops_HSP-_hoops_HIGR _hoops_SHI */

			if ((count = offset) != 0) do {		/* _hoops_IH _hoops_GRR _hoops_HSP */
				_hoops_RRC = *_hoops_AIGRA++;
				_hoops_AIGRA += _hoops_RRC;				/* _hoops_PH _hoops_IGIAR */

				/* _hoops_PSSSR _hoops_IH _hoops_PCCPR */
				while (_hoops_AIGRA != _hoops_CASRS && (_hoops_RRC = *_hoops_AIGRA) < 0)
					_hoops_AIGRA += 1 - _hoops_RRC;
			} while (--count > 0);

			_hoops_ASCRA = _hoops_AIGRA - _hoops_SPHPR->face_list;

			/* _hoops_SSS _hoops_RSH _hoops_GSGS _hoops_HIGR _hoops_HRGR _hoops_IHGS _hoops_PGHPR */

			if ((count = ndelete) != 0) do {
				_hoops_RRC = *_hoops_AIGRA++;
				_hoops_AIGRA += _hoops_RRC;				/* _hoops_PH _hoops_IGIAR */

				/* _hoops_PSSSR _hoops_IH _hoops_PCCPR */
				while (_hoops_AIGRA != _hoops_CASRS && (_hoops_RRC = *_hoops_AIGRA) < 0)
					_hoops_AIGRA += 1 - _hoops_RRC;
			} while (--count > 0);

			_hoops_ISIPS = _hoops_AIGRA - _hoops_SPHPR->face_list - _hoops_ASCRA;
		}

		if (_hoops_ISIPS == _hoops_CSSIH) {
			/* _hoops_RH _hoops_PIHGR _hoops_AGIR */
			_hoops_AIGA (insert_list, _hoops_CSSIH, int, _hoops_SPHPR->face_list + _hoops_ASCRA);
		}
		else {
			int *			_hoops_AARGA;
			int *			_hoops_AIGRA;
			int				_hoops_CSIPS;
			int *			_hoops_SSIPS;

			/* _hoops_PIHA _hoops_SIPHA _hoops_RH _hoops_CRPR */

			_hoops_CSIPS = _hoops_SPHPR->face_list_length;
			_hoops_SPHPR->face_list_length += _hoops_CSSIH - _hoops_ISIPS;

			if (_hoops_SPHPR->face_list_length > 0)
				ALLOC_ARRAY (_hoops_AARGA, _hoops_SPHPR->face_list_length, int);
			else _hoops_AARGA = null;

			_hoops_AIGRA = _hoops_SSIPS = _hoops_SPHPR->face_list;
			_hoops_SPHPR->face_list = _hoops_AARGA;

			if (_hoops_ASCRA > 0) {
				_hoops_AIGA (_hoops_AIGRA, _hoops_ASCRA, int, _hoops_AARGA);
				_hoops_AIGRA += _hoops_ASCRA;
				_hoops_AARGA += _hoops_ASCRA;
			}

			if (_hoops_CSSIH > 0) {
				_hoops_AIGA (insert_list,
								 _hoops_CSSIH, int, _hoops_AARGA);
				_hoops_AARGA += _hoops_CSSIH;
			}

			if (_hoops_CSIPS - _hoops_ASCRA - _hoops_ISIPS > 0) {
				_hoops_AIGA (_hoops_AIGRA + _hoops_ISIPS,
							_hoops_CSIPS - _hoops_ASCRA - _hoops_ISIPS,
							int, _hoops_AARGA);
			}

			if (_hoops_SSIPS != null)
				FREE_ARRAY (_hoops_SSIPS, _hoops_CSIPS, int);
		}
	}


	/*
	 * _hoops_AISA _hoops_HSP _hoops_AIRC & _hoops_PIAGR _hoops_SPPR _hoops_GAR _hoops_SIGR
	 */
	HI_Adjust_Face_Attributes (_hoops_SPHPR, offset, ndelete, insert);

	_hoops_SPHPR->face_count += insert - ndelete;

	_hoops_SPHPR->_hoops_GSAPA = false;

	if (_hoops_SPHPR->tristrips)
		HI_Free_Tristrip_List (_hoops_SPHPR->tristrips);
	_hoops_SPHPR->tristrips = null;
	_hoops_SPHPR->_hoops_ACRHR = 0;

	if (_hoops_SPHPR->_hoops_SHGPR)
		HI_Free_Polyedge_List (_hoops_SPHPR->_hoops_SHGPR);
	_hoops_SPHPR->_hoops_SHGPR = null;
	_hoops_SPHPR->_hoops_RSHPR = 0;

	if (_hoops_SPHPR->_hoops_CHGPR)
		HI_Free_Polyedge_List (_hoops_SPHPR->_hoops_CHGPR);
	_hoops_SPHPR->_hoops_CHGPR = null;
	_hoops_SPHPR->polyhedron_flags &= ~_hoops_SCRRA;

	HI_Repair_Shell_Edges (_hoops_RIGC, _hoops_SPHPR);
    HI_Invalidate_Display_Lists (_hoops_RIGC, _hoops_SPHPR);

	_hoops_SPHPR->polyhedron_flags &= ~PHF_VERTEX_NORMALS_VALID;
	if (insert > 0) {
		_hoops_SPHPR->polyhedron_flags &= ~PHF_FACE_NORMALS_VALID;
		_hoops_SPHPR->polyhedron_flags &= ~_hoops_ASAHR;
		_hoops_SPHPR->_hoops_ACRHR &= ~_hoops_PPRHR;
	}

	if (ndelete > 0)
		_hoops_SASIR (_hoops_RIGC, (Geometry *)_hoops_SPHPR, _hoops_AISSR|_hoops_CSCCA|_hoops_RPSIR);
	else /* _hoops_RPP (_hoops_GSRGR > 0) */
		_hoops_SASIR (_hoops_RIGC, (Geometry *)_hoops_SPHPR, _hoops_GPSIR|_hoops_CSCCA|_hoops_RPSIR);

  Release:
	if (_hoops_HAHRI)
		_hoops_IRRPR();
}

HC_INTERFACE void HC_CDECL HC_Edit_Shell_Faces (
	Key						key,
	int						ioffset,
	int						ndelete,
	int						_hoops_CSSIH,
	int	const *				insert_list)
{
	_hoops_PAPPR context("Edit_Shell_Faces");

#ifdef DISABLE_GEOMETRY_EDIT
	_hoops_IRPPR ("Geometry Edit");
#else
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, key, _hoops_RSGPP)) != null) {
		HI_Edit_Shell_Faces(context, (Shell *)target, ioffset, ndelete, _hoops_CSSIH, insert_list);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		int		count2 = _hoops_CSSIH;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "int * list = (int*) malloc(sizeof(int)*%d);\n", count2));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (Sprintf_DD (null, "list[%d] = %d;	 ", count2, insert_list[count2]));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Shell_Faces (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, ", ioffset, ndelete));
		HI_Dump_Code (Sprintf_D (null, "%d, list);\n", _hoops_CSSIH));
		HI_Dump_Code ("free (list);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);
#endif
}

GLOBAL_FUNCTION void HI_Delete_Specific_Shell_Faces (
	_hoops_AIGPR *	_hoops_RIGC,
	Shell alter *			_hoops_SPHPR,
	int						count,
	int const *				indices)
{
#ifdef DISABLE_GEOMETRY_EDIT
	_hoops_IRPPR ("Geometry Edit");
#else

	if (_hoops_SPHPR == null ||
		_hoops_SPHPR->type != _hoops_SCIP || BIT (_hoops_SPHPR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_KEY, "Key does not refer to a valid shell");
		return;
	}

	if (count < 0) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_NUMBER, "The count is negative");
		return;
	}

	if (count == 0)
		return; /* _hoops_CPRSH */

	if (_hoops_SPHPR->face_list == null && _hoops_SPHPR->tristrips != null) {
		HE_ERROR (HEC_MEMORY, HES_REBUILDING_TRISTRIP, "Face list data has been discarded, can not Delete");
		return;
	}

	int	*			mapping = null;
	int				_hoops_GGCPS = 0;

	/* _hoops_RIP _hoops_RSSA _hoops_PGAP _hoops_CHR _hoops_IS _hoops_SHH _hoops_PGHPR */
	_hoops_GGCPS = _hoops_SPHPR->face_count;
	ZALLOC_ARRAY (mapping, _hoops_GGCPS, int);

	for (int i=0; i<count; i++) {
		int			index = indices[i];

		if (index < 0) {
			HE_ERROR (HEC_TRISTRIP, HES_INVALID_OFFSET,
					   Sprintf_DD (null, "Invalid negative face offset %d at entry %d", index, i));
			goto Release;
		}
		else if (index >= _hoops_GGCPS) {
			char			buf[MAX_ERRMSG];

			HE_ERROR2 (HEC_TRISTRIP, HES_INVALID_OFFSET,
					   Sprintf_DD (null, "Invalid face offset %d at entry %d -", index, i),
					   Sprintf_D (buf, "the shell only has %d points", _hoops_SPHPR->face_count));
			goto Release;
		}

		mapping[index] = -1;
	}

	/* _hoops_ARP _hoops_SIA _hoops_IH _hoops_HHRPA _hoops_RSSA _hoops_PPR _hoops_HGCR _hoops_HACH _hoops_HSP _hoops_RPR */
	count = 0;
	for (int i=0; i<_hoops_GGCPS; i++) {
		if (mapping[i] == 0)
			mapping[i] = count++;
	}

	/*
	 * _hoops_HCR _hoops_GPRS, _hoops_AA _hoops_SCH
	 */

	_hoops_SPHPR->face_count = count;

	if (_hoops_SPHPR->face_count == 0) {
		if (_hoops_SPHPR->face_list != null) {
			FREE_ARRAY (_hoops_SPHPR->face_list, _hoops_SPHPR->face_list_length, int);
			_hoops_SPHPR->face_list = null;
			_hoops_SPHPR->face_list_length = 0;
		}
	}
	else {
		int				_hoops_RGCPS = 0;

		/*
		 * _hoops_HIGAA _hoops_RH _hoops_CCAH _hoops_HSP _hoops_HIGR _hoops_GGR
		 */

		{
			int *				_hoops_AIGRA = _hoops_SPHPR->face_list;
			int *				_hoops_CASRS = _hoops_AIGRA + _hoops_SPHPR->face_list_length;

			for (int i=0; i<_hoops_GGCPS; i++) {
				int const *		_hoops_AGCPS = _hoops_AIGRA;
				int				_hoops_RRC;

				_hoops_RRC = *_hoops_AIGRA++;
				_hoops_AIGRA += _hoops_RRC;				/* _hoops_PH _hoops_IGIAR */

				/* _hoops_PSSSR _hoops_IH _hoops_PCCPR */
				while (_hoops_AIGRA != _hoops_CASRS && (_hoops_RRC = *_hoops_AIGRA) < 0)
					_hoops_AIGRA += 1 - _hoops_RRC;

				if (mapping[i] >= 0)
					_hoops_RGCPS += _hoops_AIGRA - _hoops_AGCPS;
			}
		}

		{
			int				_hoops_CSIPS = _hoops_SPHPR->face_list_length;
			int *			_hoops_SSIPS = _hoops_SPHPR->face_list;

			/* _hoops_SIPHA _hoops_RH _hoops_CRPR */
			_hoops_SPHPR->face_list_length = _hoops_RGCPS;

			if (_hoops_SPHPR->face_list_length > 0) {
				int *			_hoops_AIGRA = _hoops_SSIPS;
				int *			_hoops_AARGA;
				int *			_hoops_CASRS = _hoops_AIGRA + _hoops_CSIPS;

				ALLOC_ARRAY (_hoops_AARGA, _hoops_SPHPR->face_list_length, int);
				_hoops_SPHPR->face_list = _hoops_AARGA;

				for (int i=0; i<_hoops_GGCPS; i++) {
					int const *	_hoops_AGCPS = _hoops_AIGRA;
					int			_hoops_RRC;

					_hoops_RRC = *_hoops_AIGRA++;
					_hoops_AIGRA += _hoops_RRC;				/* _hoops_PH _hoops_IGIAR */

					/* _hoops_PSSSR _hoops_IH _hoops_PCCPR */
					while (_hoops_AIGRA != _hoops_CASRS && (_hoops_RRC = *_hoops_AIGRA) < 0)
						_hoops_AIGRA += 1 - _hoops_RRC;

					if (mapping[i] >= 0) {
						int		_hoops_HHHHR = _hoops_AIGRA - _hoops_AGCPS;

						_hoops_AIGA (_hoops_AGCPS, _hoops_HHHHR, int, _hoops_AARGA);
						_hoops_AARGA += _hoops_HHHHR;
					}
				}
			}
			else
				_hoops_SPHPR->face_list = null;

			if (_hoops_SSIPS != null)
				FREE_ARRAY (_hoops_SSIPS, _hoops_CSIPS, int);
		}
	}


	/*
	 * _hoops_AISA _hoops_HSP _hoops_AIRC
	 */
	if (_hoops_SPHPR->face_count == 0) {
		if (BIT(_hoops_SPHPR->polyhedron_flags, _hoops_APRHR)) {
			if (_hoops_SPHPR->local_face_attributes.flags != null) {
				FREE_ARRAY (_hoops_SPHPR->local_face_attributes.flags,
							_hoops_GGCPS, _hoops_GIIPR);
				_hoops_SPHPR->local_face_attributes.flags = null;
			}
		}
		else
			_hoops_SPHPR->local_face_attributes._hoops_SGRHR = 0;

		if (_hoops_SPHPR->local_face_attributes.colors != null) {
			FREE_ARRAY (_hoops_SPHPR->local_face_attributes.colors,
						_hoops_GGCPS, RGB);
			_hoops_SPHPR->local_face_attributes.colors = null;
		}

		if (_hoops_SPHPR->local_face_attributes.findices != null) {
			FREE_ARRAY (_hoops_SPHPR->local_face_attributes.findices,
						_hoops_GGCPS, _hoops_ACGHR);
			_hoops_SPHPR->local_face_attributes.findices = null;
		}

		if (_hoops_SPHPR->local_face_attributes._hoops_AHHIR != null) {
			FREE_ARRAY (_hoops_SPHPR->local_face_attributes._hoops_AHHIR,
						_hoops_GGCPS, unsigned char);
			_hoops_SPHPR->local_face_attributes._hoops_AHHIR = null;
		}

		if (_hoops_SPHPR->local_face_attributes.normals != null) {
			FREE_ARRAY_ALIGNED (_hoops_SPHPR->local_face_attributes.normals,
								_hoops_GGCPS, _hoops_ARPA, 16);
			_hoops_SPHPR->local_face_attributes.normals = null;
		}

		if (_hoops_SPHPR->local_face_attributes.regions != null) {
			FREE_ARRAY (_hoops_SPHPR->local_face_attributes.regions,
						_hoops_GGCPS + _hoops_SHHIR, int);
			_hoops_SPHPR->local_face_attributes.regions = null;
		}

		_hoops_SPHPR->local_face_attributes._hoops_CPIAA			= 0;
		_hoops_SPHPR->local_face_attributes._hoops_SIIPR		= 0;
		_hoops_SPHPR->local_face_attributes._hoops_HSRRA	= 0;
		_hoops_SPHPR->local_face_attributes._hoops_PSRRA	= 0;
		_hoops_SPHPR->local_face_attributes._hoops_SRAPA			= 0;
		_hoops_SPHPR->local_face_attributes.explicit_normal_count			= 0;
	}
	else {
		_hoops_GIIPR *		_hoops_CICHH = _hoops_SPHPR->local_face_attributes.flags;
		_hoops_GIIPR *		_hoops_ICRRH = null;
		RGB *					_hoops_PGICP = _hoops_SPHPR->local_face_attributes.colors;
		RGB *					_hoops_RCISH = null;
		_hoops_ACGHR*		_hoops_PGCPS = _hoops_SPHPR->local_face_attributes.findices;
		_hoops_ACGHR *		_hoops_HGCPS = null;
		unsigned char *			_hoops_IGCPS = _hoops_SPHPR->local_face_attributes._hoops_AHHIR;
		unsigned char *			_hoops_CGCPS = null;
		_hoops_ARPA *					_hoops_CIRSH = _hoops_SPHPR->local_face_attributes.normals;
		_hoops_ARPA *					_hoops_RSCRA = null;
		int *					_hoops_SGCPS = _hoops_SPHPR->local_face_attributes.regions;
		int *					_hoops_GRCPS = null;

		if (_hoops_CICHH != null)
			ALLOC_ARRAY (_hoops_ICRRH,	_hoops_SPHPR->face_count, _hoops_GIIPR);
		if (_hoops_PGICP != null)
			ALLOC_ARRAY (_hoops_RCISH,	_hoops_SPHPR->face_count, RGB);
		if (_hoops_PGCPS != null)
			ALLOC_ARRAY (_hoops_HGCPS, _hoops_SPHPR->face_count, _hoops_ACGHR);
		if (_hoops_IGCPS != null)
			ALLOC_ARRAY (_hoops_CGCPS, _hoops_SPHPR->face_count, unsigned char);
		if (_hoops_CIRSH != null)
			ALLOC_ARRAY_ALIGNED (_hoops_RSCRA,	_hoops_SPHPR->face_count, _hoops_ARPA, 16);
		if (_hoops_SGCPS != null) {
			ALLOC_ARRAY (_hoops_GRCPS,	_hoops_SPHPR->face_count +_hoops_SHHIR, int);
			_hoops_GRCPS[_hoops_SPHPR->face_count + _hoops_GISCC] = 0;
		}

		if (BIT(_hoops_SPHPR->polyhedron_flags, _hoops_APRHR)) {
			for (int i=0; i<_hoops_GGCPS; i++) {
				int					_hoops_HGAHC = mapping[i];
				_hoops_GIIPR *	_hoops_RRCPS = _hoops_SPHPR->local_face_attributes._hoops_CHHPR(i);

				if (_hoops_HGAHC >= 0) {
					if (_hoops_CICHH != null)
						_hoops_AIGA (_hoops_RRCPS, 1, _hoops_GIIPR, &_hoops_ICRRH[_hoops_HGAHC]);
					if (_hoops_PGICP != null)
						_hoops_AIGA (&_hoops_PGICP[i], 1, RGB, &_hoops_RCISH[_hoops_HGAHC]);
					if (_hoops_PGCPS != null)
						_hoops_AIGA (&_hoops_PGCPS[i], 1, _hoops_ACGHR, &_hoops_HGCPS[_hoops_HGAHC]);
					if (_hoops_IGCPS != null)
						_hoops_AIGA (&_hoops_IGCPS[i], 1, unsigned char, &_hoops_CGCPS[_hoops_HGAHC]);
					if (_hoops_CIRSH != null)
						_hoops_AIGA (&_hoops_CIRSH[i], 1, _hoops_ARPA, &_hoops_RSCRA[_hoops_HGAHC]);
					if (_hoops_SGCPS != null)
						_hoops_AIGA (&_hoops_SGCPS[i], 1, int, &_hoops_GRCPS[_hoops_HGAHC]);
				}
				else if (_hoops_CICHH != null) {
					if (BIT (*_hoops_RRCPS, _hoops_IAGI))
						--_hoops_SPHPR->local_face_attributes._hoops_CPIAA;
					if (BIT (*_hoops_RRCPS, _hoops_HSIPR))
						--_hoops_SPHPR->local_face_attributes._hoops_SIIPR;
					if (BIT (*_hoops_RRCPS, LFA_EXPLICIT_COLOR_BY_VALUE))
						--_hoops_SPHPR->local_face_attributes._hoops_HSRRA;
					if (BIT (*_hoops_RRCPS, LFA_EXPLICIT_COLOR_BY_FINDEX))
						--_hoops_SPHPR->local_face_attributes._hoops_PSRRA;
					if (BIT (*_hoops_RRCPS, _hoops_HAGI))
						--_hoops_SPHPR->local_face_attributes._hoops_SRAPA;
					if (BIT (*_hoops_RRCPS, LFA_EXPLICIT_NORMAL))
						--_hoops_SPHPR->local_face_attributes.explicit_normal_count;
				}
			}
		}
		else {
			for (int i = 0; i < _hoops_GGCPS; i++) {
				int			_hoops_HGAHC = mapping[i];
				if (_hoops_HGAHC >= 0) {
					if (_hoops_PGICP != null)
						_hoops_AIGA (&_hoops_PGICP[i], 1, RGB, &_hoops_RCISH[_hoops_HGAHC]);
					if (_hoops_PGCPS != null)
						_hoops_AIGA (&_hoops_PGCPS[i], 1, _hoops_ACGHR, &_hoops_HGCPS[_hoops_HGAHC]);
					if (_hoops_IGCPS != null)
						_hoops_AIGA (&_hoops_IGCPS[i], 1, unsigned char, &_hoops_CGCPS[_hoops_HGAHC]);
					if (_hoops_CIRSH != null)
						_hoops_AIGA (&_hoops_CIRSH[i], 1, _hoops_ARPA, &_hoops_RSCRA[_hoops_HGAHC]);
					if (_hoops_SGCPS != null)
						_hoops_AIGA (&_hoops_SGCPS[i], 1, int, &_hoops_GRCPS[_hoops_HGAHC]);
				}
			}
			if (_hoops_CICHH != null) {
				if (BIT (_hoops_SPHPR->local_face_attributes._hoops_SGRHR, _hoops_IAGI))
					_hoops_SPHPR->local_face_attributes._hoops_CPIAA -= count;
				if (BIT (_hoops_SPHPR->local_face_attributes._hoops_SGRHR, _hoops_HSIPR))
					_hoops_SPHPR->local_face_attributes._hoops_SIIPR -= count;
				if (BIT (_hoops_SPHPR->local_face_attributes._hoops_SGRHR, LFA_EXPLICIT_COLOR_BY_VALUE))
					_hoops_SPHPR->local_face_attributes._hoops_HSRRA -= count;
				if (BIT (_hoops_SPHPR->local_face_attributes._hoops_SGRHR, LFA_EXPLICIT_COLOR_BY_FINDEX))
					_hoops_SPHPR->local_face_attributes._hoops_PSRRA -= count;
				if (BIT (_hoops_SPHPR->local_face_attributes._hoops_SGRHR, _hoops_HAGI))
					_hoops_SPHPR->local_face_attributes._hoops_SRAPA -= count;
				if (BIT (_hoops_SPHPR->local_face_attributes._hoops_SGRHR, LFA_EXPLICIT_NORMAL))
					_hoops_SPHPR->local_face_attributes.explicit_normal_count -= count;
			}
		}

		if (_hoops_CICHH != null && BIT(_hoops_SPHPR->polyhedron_flags, _hoops_APRHR))
			FREE_ARRAY (_hoops_SPHPR->local_face_attributes.flags, _hoops_GGCPS, _hoops_GIIPR);
		if (_hoops_PGICP != null)
			FREE_ARRAY (_hoops_SPHPR->local_face_attributes.colors, _hoops_GGCPS, RGB);
		if (_hoops_PGCPS != null)
			FREE_ARRAY (_hoops_SPHPR->local_face_attributes.findices, _hoops_GGCPS, _hoops_ACGHR);
		if (_hoops_IGCPS != null)
			FREE_ARRAY (_hoops_SPHPR->local_face_attributes._hoops_AHHIR, _hoops_GGCPS, unsigned char);
		if (_hoops_CIRSH != null)
			FREE_ARRAY_ALIGNED (_hoops_SPHPR->local_face_attributes.normals, _hoops_GGCPS, _hoops_ARPA, 16);
		if (_hoops_SGCPS != null)
			FREE_ARRAY (_hoops_SPHPR->local_face_attributes.regions, _hoops_GGCPS +_hoops_SHHIR, int);

		if (_hoops_ICRRH) {
			_hoops_SPHPR->local_face_attributes.flags	 = _hoops_ICRRH;
			_hoops_SPHPR->polyhedron_flags |= _hoops_APRHR;
		}
		else {
			/* _hoops_RRCPR->_hoops_HPSSI._hoops_IIGCI _hoops_CGH _hoops_CCHRC _hoops_PSHR */
		}
		_hoops_SPHPR->local_face_attributes.colors		= _hoops_RCISH;
		_hoops_SPHPR->local_face_attributes.findices	= _hoops_HGCPS;
		_hoops_SPHPR->local_face_attributes._hoops_AHHIR	= _hoops_CGCPS;
		_hoops_SPHPR->local_face_attributes.normals	= _hoops_RSCRA;
		_hoops_SPHPR->local_face_attributes.regions	= _hoops_GRCPS;
	}


	HI_Repair_Shell_Edges (_hoops_RIGC, _hoops_SPHPR);


	if (_hoops_SPHPR->tristrips)
		HI_Free_Tristrip_List (_hoops_SPHPR->tristrips);
	_hoops_SPHPR->tristrips = null;
	_hoops_SPHPR->_hoops_ACRHR = false;

	if (_hoops_SPHPR->_hoops_SHGPR)
		HI_Free_Polyedge_List (_hoops_SPHPR->_hoops_SHGPR);
	_hoops_SPHPR->_hoops_SHGPR = null;
	_hoops_SPHPR->_hoops_RSHPR = false;

	if (_hoops_SPHPR->_hoops_CHGPR)
		HI_Free_Polyedge_List (_hoops_SPHPR->_hoops_CHGPR);
	_hoops_SPHPR->_hoops_CHGPR = null;
	_hoops_SPHPR->polyhedron_flags &= ~_hoops_SCRRA;

	_hoops_SPHPR->polyhedron_flags &= ~PHF_VERTEX_NORMALS_VALID;

	_hoops_SASIR (_hoops_RIGC, (Geometry *)_hoops_SPHPR, _hoops_AISSR|
														  _hoops_CSCCA|
														  _hoops_RPSIR);

  Release:
	if (mapping != null)
		FREE_ARRAY (mapping, _hoops_GGCPS, int);
#endif
}



HC_INTERFACE void HC_CDECL HC_Delete_Specific_Shell_Faces (
	Key				key,
	int				count,
	int const *		indices)
{
	_hoops_PAPPR context("Delete_Specific_Shell_Faces");

#ifdef DISABLE_GEOMETRY_EDIT
	_hoops_IRPPR ("Geometry Edit");
#else
	CODE_GENERATION (
		int		count2 = count;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "int * indices = (int*) malloc(sizeof(int)*%d);\n", count2));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (Sprintf_DD (null, "indices[%d] = %d;\n", count2, indices[count2]));
		}
		HI_Dump_Code (Sprintf_LD (null, "Delete_Specific_Shell_Faces (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_D (null, "%d, indices);\n", count));
		HI_Dump_Code ("free (indices);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	_hoops_RPPPR();
	Shell *	_hoops_SPHPR = (Shell *)_hoops_RCSSR (context, key);
	HI_Delete_Specific_Shell_Faces (context, _hoops_SPHPR, count, indices);
	_hoops_IRRPR();
#endif
}


#ifndef DISABLE_GEOMETRY_EDIT

local void _hoops_ARCPS (
	_hoops_AIGPR *	_hoops_RIGC,
	Shell *					_hoops_SPHPR,
	int						offset,
	int						ndelete) {
	int						_hoops_GGCPS = _hoops_SPHPR->face_count;
	int *					_hoops_PRCPS = null;
	int						_hoops_HRCPS = 0;
	int *					_hoops_ASPH = _hoops_SPHPR->face_list;
	int *					_hoops_HICPR = _hoops_ASPH + _hoops_SPHPR->face_list_length;
	int						_hoops_IRCPS = offset + ndelete;
	int						_hoops_PHHHR = -1;

	/* _hoops_RRP _hoops_IS _hoops_ISPR _hoops_IH _hoops_RSSI _hoops_IS _hoops_RSRHR _hoops_SGGR, _hoops_CRCPS  */

	ALLOC_ARRAY_CACHED (_hoops_PRCPS, _hoops_GGCPS, int);

	while (_hoops_ASPH != _hoops_HICPR) {
		int		*_hoops_CRRHR;

		if (*_hoops_ASPH >= 0) {
			_hoops_CRRHR = _hoops_ASPH + *_hoops_ASPH + 1;
			++_hoops_PHHHR;
		}
		else {
			_hoops_CRRHR = _hoops_ASPH - *_hoops_ASPH + 1;
		}

		/* _hoops_RHAP _hoops_RGR _hoops_HSP _hoops_SCIR _hoops_IRS _hoops_AHCI _hoops_SPR? */

		_hoops_RGGA (++_hoops_ASPH == _hoops_CRRHR) {
			if (offset <= *_hoops_ASPH && *_hoops_ASPH < _hoops_IRCPS) { /* _hoops_CHCAR */
				_hoops_ASPH = _hoops_CRRHR;	/* _hoops_HSGR _hoops_IS _hoops_RH _hoops_RSGR */

				/* _hoops_PIHA _hoops_HSGR _hoops_GII _hoops_HHRPA _hoops_PCCPR _hoops_GGR _hoops_RGR _hoops_HSP _hoops_HA */
				while (_hoops_ASPH != _hoops_HICPR && *_hoops_ASPH < 0)
					_hoops_ASPH += 1 - *_hoops_ASPH;

				/* _hoops_PCSA _hoops_RGR _hoops_SPR _hoops_IH _hoops_SRCPS */
				_hoops_PRCPS[_hoops_HRCPS++] = _hoops_PHHHR;
				break;
			}
		}
	}

	if (_hoops_HRCPS > 0) {
		HI_Delete_Specific_Shell_Faces (_hoops_RIGC, _hoops_SPHPR, _hoops_HRCPS, _hoops_PRCPS);
	}

	FREE_ARRAY (_hoops_PRCPS, _hoops_GGCPS, int);
}

local void _hoops_GACPS (
	_hoops_AIGPR *	_hoops_RIGC,
	Shell *					_hoops_SPHPR,
	int *					mapping) {
	int						_hoops_GGCPS = _hoops_SPHPR->face_count;
	int *					_hoops_PRCPS = null;
	int						_hoops_HRCPS = 0;
	int *					_hoops_ASPH = _hoops_SPHPR->face_list;
	int *					_hoops_HICPR = _hoops_ASPH + _hoops_SPHPR->face_list_length;
	int						_hoops_PHHHR = -1;

	/* _hoops_RRP _hoops_IS _hoops_ISPR _hoops_IH _hoops_RSSI _hoops_IS _hoops_RSRHR _hoops_SGGR, _hoops_CRCPS  */

	ALLOC_ARRAY_CACHED (_hoops_PRCPS, _hoops_GGCPS, int);

	while (_hoops_ASPH != _hoops_HICPR) {
		int		*_hoops_CRRHR;

		if (*_hoops_ASPH >= 0) {
			_hoops_CRRHR = _hoops_ASPH + *_hoops_ASPH + 1;
			++_hoops_PHHHR;
		}
		else {
			_hoops_CRRHR = _hoops_ASPH - *_hoops_ASPH + 1;
		}

		/* _hoops_RHAP _hoops_RGR _hoops_HSP _hoops_SCIR _hoops_IRS _hoops_AHCI _hoops_SPR? */

		_hoops_RGGA (++_hoops_ASPH == _hoops_CRRHR) {
			if (mapping[*_hoops_ASPH] < 0) { /* _hoops_CHCAR */
				_hoops_ASPH = _hoops_CRRHR;	/* _hoops_HSGR _hoops_IS _hoops_RH _hoops_RSGR */

				/* _hoops_PIHA _hoops_HSGR _hoops_GII _hoops_HHRPA _hoops_PCCPR _hoops_GGR _hoops_RGR _hoops_HSP _hoops_HA */
				while (_hoops_ASPH != _hoops_HICPR && *_hoops_ASPH < 0)
					_hoops_ASPH += 1 - *_hoops_ASPH;

				/* _hoops_PCSA _hoops_RGR _hoops_SPR _hoops_IH _hoops_SRCPS */
				_hoops_PRCPS[_hoops_HRCPS++] = _hoops_PHHHR;
				break;
			}
		}
	}

	if (_hoops_HRCPS > 0) {
		HI_Delete_Specific_Shell_Faces (_hoops_RIGC, _hoops_SPHPR, _hoops_HRCPS, _hoops_PRCPS);
	}

	FREE_ARRAY (_hoops_PRCPS, _hoops_GGCPS, int);
}

#endif

/* _hoops_PAGA: _hoops_RRCPR'_hoops_GRI _hoops_PPSR _hoops_RPR _hoops_CGH _hoops_SHH _hoops_RH _hoops_GIGR _hoops_PIRA _hoops_CGPR _hoops_RGR _hoops_HRGR _hoops_PIGS */
GLOBAL_FUNCTION void HI_Adjust_Vertex_To_Edge (
	Shell *					_hoops_SPHPR,
	int						offset,
	int						ndelete,
	int						insert)
{
	_hoops_RHHPR **	_hoops_RACPS;
	_hoops_RHHPR **	_hoops_AACPS;

	/* _hoops_SGPR _hoops_SRHAS _hoops_HHSA: _hoops_SIPHA _hoops_HII _hoops_SI _hoops_SHR. */

	/* ("+ 1" _hoops_IH _hoops_RH _hoops_IHH _hoops_PACPS _hoops_PIRA) */
	ALLOC_ARRAY (_hoops_RACPS, _hoops_SPHPR->point_count - ndelete + insert + 1,
				 _hoops_RHHPR *);

	{	_hoops_RHHPR	**_hoops_HACPS;

		_hoops_HACPS = _hoops_AACPS = _hoops_SPHPR->_hoops_HHHPR;
		_hoops_SPHPR->_hoops_HHHPR = _hoops_RACPS;

		if (offset > 0) {
			_hoops_AIGA (_hoops_HACPS, offset, _hoops_RHHPR *, _hoops_RACPS);
			_hoops_HACPS += offset;
			_hoops_RACPS += offset;
		}

		_hoops_HACPS += ndelete;

		if (insert > 0) {
			do *_hoops_RACPS++ = *_hoops_HACPS;
			_hoops_RGGA (--insert == 0);
		}
		/** '_hoops_GSRGR' _hoops_HRGR _hoops_HA _hoops_AIPH **/

		/* (_hoops_SHR _hoops_HHH _hoops_IS _hoops_AA _hoops_GPP _hoops_RH _hoops_RSGR, _hoops_PGGA _hoops_IIGR _hoops_RH "+ 1") */
		_hoops_AIGA (_hoops_HACPS, _hoops_SPHPR->point_count - offset - ndelete + 1,
					 _hoops_RHHPR *, _hoops_RACPS);
	}

	FREE_ARRAY (_hoops_AACPS, _hoops_SPHPR->point_count + 1, _hoops_RHHPR*);
}

#ifndef DISABLE_GEOMETRY_EDIT
local void _hoops_IACPS (
	Shell *					_hoops_SPHPR,
	int *					mapping,
	int						_hoops_AAAHA) {
	int						_hoops_CACPS = _hoops_SPHPR->point_count;
	_hoops_RHHPR **	_hoops_HACPS = _hoops_SPHPR->_hoops_HHHPR;
	_hoops_RHHPR **	_hoops_RACPS;
	int						i;

	/* "+ 1" _hoops_IH _hoops_RH _hoops_IHH _hoops_PACPS _hoops_PIRA */
	ALLOC_ARRAY (_hoops_RACPS, _hoops_AAAHA + 1, _hoops_RHHPR *);
	_hoops_SPHPR->_hoops_HHHPR = _hoops_RACPS;

	for (i=0; i<_hoops_CACPS; i++) {
		if (mapping[i] >= 0)
			_hoops_RACPS[mapping[i]] = _hoops_HACPS[i];
	}
	/* _hoops_PPR _hoops_PGGA _hoops_IIGR _hoops_RH "+ 1" */
	_hoops_RACPS[_hoops_AAAHA] = _hoops_HACPS[_hoops_CACPS];

	FREE_ARRAY (_hoops_HACPS, _hoops_CACPS + 1, _hoops_RHHPR*);
}
#endif

/* _hoops_PAGA: _hoops_RRCPR'_hoops_GRI _hoops_PPSR _hoops_RPR _hoops_CGH _hoops_SHH _hoops_RH _hoops_GIGR _hoops_PIRA _hoops_CGPR _hoops_RGR _hoops_HRGR _hoops_PIGS */
GLOBAL_FUNCTION void HI_Adjust_Vertex_Attributes (
	Shell *							_hoops_SPHPR,
	int								offset,
	int								ndelete,
	int								insert)
{
	Local_Vertex_Attributes *		_hoops_SPRI = &_hoops_SPHPR->local_vertex_attributes;
	int								count;
	int								_hoops_CACPS;
	int								_hoops_AAAHA;

	_hoops_CACPS = _hoops_SPHPR->point_count;
	_hoops_AAAHA = _hoops_CACPS - ndelete + insert;

	if (insert == ndelete) {
		Local_Vertex_Flags *	_hoops_SAHPR;
		Local_Vertex_Flags *	_hoops_SACPS;

		if (BIT(_hoops_SPHPR->polyhedron_flags, _hoops_CGRHR)) {
			/* _hoops_CIPAA _hoops_GGR _hoops_HGHC */
			_hoops_SAHPR = _hoops_SPRI->_hoops_CHHPR(offset);
			_hoops_SACPS = _hoops_SAHPR + insert;
			do {
				if (BIT (*_hoops_SAHPR, _hoops_PHIAA))
					--_hoops_SPRI->_hoops_CPIAA;
				if (BIT (*_hoops_SAHPR, _hoops_HHIAA))
					--_hoops_SPRI->_hoops_SIIPR;

				if (BIT (*_hoops_SAHPR, _hoops_HCRRA))
					--_hoops_SPRI->_hoops_ICRRA;
				if (BIT (*_hoops_SAHPR, _hoops_SIRRA))
					--_hoops_SPRI->_hoops_PCRRA;
				if (BIT (*_hoops_SAHPR, _hoops_CCRRA))
					--_hoops_SPRI->_hoops_HIRRA;

				if (BIT (*_hoops_SAHPR, _hoops_PPHPR))
					--_hoops_SPRI->_hoops_SCHPR;
				if (BIT (*_hoops_SAHPR, _hoops_RPHPR))
					--_hoops_SPRI->_hoops_CCHPR;

				if (BIT (*_hoops_SAHPR, _hoops_AARHR))
					--_hoops_SPRI->_hoops_RCRHR;
				if (BIT (*_hoops_SAHPR, _hoops_HARHR))
					--_hoops_SPRI->_hoops_SIRHR;

				if (BIT (*_hoops_SAHPR, _hoops_GCICA))
					--_hoops_SPRI->_hoops_SCHHC;

				if (BIT (*_hoops_SAHPR, _hoops_SIICA)) {
					Polyhedron *		_hoops_HPGPR = (Polyhedron *)_hoops_SPHPR;
					_hoops_RPHIR *		_hoops_GARSA;
					unsigned char		symbol;

					symbol = _hoops_SPRI->_hoops_SAHIR[_hoops_SAHPR - _hoops_SPRI->flags];
					_hoops_GARSA = HI_LVA_Symbol_Lookup (_hoops_HPGPR, symbol);
					if (_hoops_ISAI(_hoops_GARSA) == 0)
						HI_LVA_Symbol_Delete (_hoops_HPGPR, _hoops_GARSA);

					--_hoops_SPRI->_hoops_AHIIC;
				}

				if (BIT (*_hoops_SAHPR, LVA_EXPLICIT_NORMAL))
					--_hoops_SPRI->explicit_normal_count;

				if (BIT (*_hoops_SAHPR, _hoops_ASAPA))
					--_hoops_SPRI->_hoops_RSAPA;

				*_hoops_SAHPR = 0;
			} _hoops_RGGA (++_hoops_SAHPR == _hoops_SACPS);
		}
		else {
			_hoops_SAHPR = _hoops_SPRI->_hoops_CHHPR(offset); //_hoops_HIGCI _hoops_CGH _hoops_ASRC _hoops_IIGCI _hoops_GGR _hoops_RGR _hoops_AGIR

			if (BIT (*_hoops_SAHPR, _hoops_PHIAA))
				_hoops_SPRI->_hoops_CPIAA -= (insert-offset);
			if (BIT (*_hoops_SAHPR, _hoops_HHIAA))
				_hoops_SPRI->_hoops_SIIPR -= (insert-offset);

			if (BIT (*_hoops_SAHPR, _hoops_HCRRA))
				_hoops_SPRI->_hoops_ICRRA -= (insert-offset);
			if (BIT (*_hoops_SAHPR, _hoops_SIRRA))
				_hoops_SPRI->_hoops_PCRRA -= (insert-offset);
			if (BIT (*_hoops_SAHPR, _hoops_CCRRA))
				_hoops_SPRI->_hoops_HIRRA -= (insert-offset);

			if (BIT (*_hoops_SAHPR, _hoops_PPHPR))
				_hoops_SPRI->_hoops_SCHPR -= (insert-offset);
			if (BIT (*_hoops_SAHPR, _hoops_RPHPR))
				_hoops_SPRI->_hoops_CCHPR -= (insert-offset);

			if (BIT (*_hoops_SAHPR, _hoops_AARHR))
				_hoops_SPRI->_hoops_RCRHR -= (insert-offset);
			if (BIT (*_hoops_SAHPR, _hoops_HARHR))
				_hoops_SPRI->_hoops_SIRHR -= (insert-offset);

			if (BIT (*_hoops_SAHPR, _hoops_GCICA))
				_hoops_SPRI->_hoops_SCHHC -= (insert-offset);

			if (BIT (*_hoops_SAHPR, _hoops_SIICA)) {
				Polyhedron *		_hoops_HPGPR = (Polyhedron *)_hoops_SPHPR;
				_hoops_RPHIR *		_hoops_GARSA;
				unsigned char		symbol;

				symbol = _hoops_SPRI->_hoops_SAHIR[offset];
				_hoops_GARSA = HI_LVA_Symbol_Lookup (_hoops_HPGPR, symbol);
				if (_hoops_ISAI(_hoops_GARSA) == 0)
					HI_LVA_Symbol_Delete (_hoops_HPGPR, _hoops_GARSA);

				_hoops_SPRI->_hoops_AHIIC -= (insert-offset);
			}

			if (BIT (*_hoops_SAHPR, LVA_EXPLICIT_NORMAL))
				_hoops_SPRI->explicit_normal_count -= (insert-offset);

			if (BIT (*_hoops_SAHPR, _hoops_ASAPA))
				_hoops_SPRI->_hoops_RSAPA -= (insert-offset);

			*_hoops_SAHPR = 0;
		}
	}
	else if (_hoops_AAAHA == 0) {
		if (_hoops_SPRI->_hoops_GPHIR != null) {
			_hoops_RPHIR *		sl = _hoops_SPRI->_hoops_GPHIR;
			_hoops_RPHIR *		_hoops_APHIR;

			do {
				_hoops_APHIR = sl->next;

				_hoops_RGAIR (sl->name);
				FREE (sl, _hoops_RPHIR);
			} while ((sl = _hoops_APHIR) != null);
		}

		if (_hoops_SPRI->flags && BIT(_hoops_SPHPR->polyhedron_flags, _hoops_CGRHR)) {
			FREE_ARRAY (_hoops_SPRI->flags, _hoops_CACPS, Local_Vertex_Flags);
			_hoops_SPHPR->polyhedron_flags &= ~_hoops_CGRHR;
			_hoops_SPRI->flags = null;
			_hoops_SPRI->_hoops_SGRHR = 0;
		}
		else
			_hoops_SPRI->_hoops_SGRHR = 0;
		if (_hoops_SPRI->_hoops_PAHIR)
			FREE_ARRAY (_hoops_SPRI->_hoops_PAHIR, _hoops_CACPS, RGB);
		if (_hoops_SPRI->ecolors)
			FREE_ARRAY (_hoops_SPRI->ecolors, _hoops_CACPS, RGB);
		if (_hoops_SPRI->fcolors)
			FREE_ARRAY (_hoops_SPRI->fcolors, _hoops_CACPS, RGB);
		if (_hoops_SPRI->_hoops_HAHIR)
			FREE_ARRAY (_hoops_SPRI->_hoops_HAHIR, _hoops_CACPS, _hoops_ACGHR);
		if (_hoops_SPRI->_hoops_HGHIR)
			FREE_ARRAY (_hoops_SPRI->_hoops_HGHIR, _hoops_CACPS, _hoops_ACGHR);
		if (_hoops_SPRI->_hoops_IGHIR)
			FREE_ARRAY (_hoops_SPRI->_hoops_IGHIR, _hoops_CACPS, _hoops_ACGHR);
		if (_hoops_SPRI->_hoops_CAHIR)
			FREE_ARRAY (_hoops_SPRI->_hoops_CAHIR, _hoops_CACPS, float);
		if (_hoops_SPRI->_hoops_SAHIR)
			FREE_ARRAY (_hoops_SPRI->_hoops_SAHIR, _hoops_CACPS, unsigned char);
		if (_hoops_SPRI->normals)
			FREE_ARRAY (_hoops_SPRI->normals, _hoops_CACPS, Vector);
		if (_hoops_SPRI->params)
			FREE_ARRAY (_hoops_SPRI->params, _hoops_CACPS*_hoops_SPRI->param_width, _hoops_RSSH);

		ZERO_STRUCT (_hoops_SPRI, Local_Vertex_Attributes);
	}
	else {
		Local_Vertex_Flags *		_hoops_CICHH = _hoops_SPRI->_hoops_CHHPR();
		Local_Vertex_Flags *		_hoops_GPCPS = null;
		Local_Vertex_Flags *		_hoops_ICRRH;
		RGBAS32 *					_hoops_RPCPS = _hoops_SPRI->_hoops_IAHIR;
		RGBAS32 *					_hoops_APCPS = null;
		RGBAS32 *					_hoops_PPCPS;
		RGB *						_hoops_HPCPS = _hoops_SPRI->_hoops_PAHIR;
		RGB *						_hoops_IPCPS = null;
		RGB *						_hoops_CPCPS;
		RGB *						_hoops_SPCPS = _hoops_SPRI->ecolors;
		RGB *						_hoops_GHCPS = null;
		RGB *						_hoops_RHCPS;
		RGB *						_hoops_AHCPS = _hoops_SPRI->fcolors;
		RGB *						_hoops_PHCPS = null;
		RGB *						_hoops_HHCPS;
		_hoops_ACGHR *			_hoops_IHCPS = _hoops_SPRI->_hoops_HAHIR;
		_hoops_ACGHR *			_hoops_CHCPS = null;
		_hoops_ACGHR *			_hoops_SHCPS;
		_hoops_ACGHR *			_hoops_GICPS = _hoops_SPRI->_hoops_HGHIR;
		_hoops_ACGHR *			_hoops_RICPS = null;
		_hoops_ACGHR *			_hoops_AICPS;
		_hoops_ACGHR *			_hoops_PICPS = _hoops_SPRI->_hoops_IGHIR;
		_hoops_ACGHR *			_hoops_HICPS = null;
		_hoops_ACGHR *			_hoops_IICPS;
		float *						_hoops_CICPS = _hoops_SPRI->_hoops_CAHIR;
		float *						_hoops_SICPS = null;
		float *						_hoops_GCCPS;
		unsigned char *				_hoops_RCCPS = _hoops_SPRI->_hoops_SAHIR;
		unsigned char *				_hoops_ACCPS = null;
		unsigned char *				_hoops_PCCPS;
		Vector *					_hoops_CIRSH = _hoops_SPRI->normals;
		Vector *					_hoops_HCCPS = null;
		Vector *					_hoops_RSCRA;
		_hoops_RSSH *					_hoops_ICCPS = _hoops_SPRI->params;
		_hoops_RSSH *					_hoops_CCCPS = null;
		_hoops_RSSH *					_hoops_RPHCP;
		int							param_width = _hoops_SPRI->param_width;
		bool						_hoops_SCCPS = BIT(_hoops_SPHPR->polyhedron_flags, _hoops_CGRHR);

		if (_hoops_SCCPS || _hoops_SPRI->_hoops_SGRHR != 0 && ndelete - insert != 0) {
			ZALLOC_ARRAY (_hoops_GPCPS,	_hoops_AAAHA, Local_Vertex_Flags);
			_hoops_SPHPR->polyhedron_flags |= _hoops_CGRHR;
		}
		if (_hoops_SPRI->_hoops_IAHIR != null)
			ALLOC_ARRAY (_hoops_APCPS,	  _hoops_AAAHA, RGBAS32);
		if (_hoops_SPRI->_hoops_PAHIR != null)
			ALLOC_ARRAY (_hoops_IPCPS,	  _hoops_AAAHA, RGB);
		if (_hoops_SPRI->ecolors != null) {
			if (_hoops_SPRI->ecolors == _hoops_SPRI->_hoops_PAHIR)
				_hoops_GHCPS = _hoops_IPCPS;
			else
				ALLOC_ARRAY (_hoops_GHCPS,	  _hoops_AAAHA, RGB);
		}
		if (_hoops_SPRI->fcolors != null) {
			if (_hoops_SPRI->fcolors == _hoops_SPRI->_hoops_PAHIR)
				_hoops_PHCPS = _hoops_IPCPS;
			else if (_hoops_SPRI->fcolors == _hoops_SPRI->ecolors)
				_hoops_PHCPS = _hoops_GHCPS;
			else
				ALLOC_ARRAY (_hoops_PHCPS,	  _hoops_AAAHA, RGB);
		}
		if (_hoops_SPRI->_hoops_HAHIR != null)
			ALLOC_ARRAY (_hoops_CHCPS,  _hoops_AAAHA, _hoops_ACGHR);
		if (_hoops_SPRI->_hoops_HGHIR != null) {
			if (_hoops_SPRI->_hoops_HGHIR == _hoops_SPRI->_hoops_HAHIR)
				_hoops_RICPS = _hoops_CHCPS;
			else
				ALLOC_ARRAY (_hoops_RICPS,  _hoops_AAAHA, _hoops_ACGHR);
		}
		if (_hoops_SPRI->_hoops_IGHIR != null) {
			if (_hoops_SPRI->_hoops_IGHIR == _hoops_SPRI->_hoops_HAHIR)
				_hoops_HICPS = _hoops_CHCPS;
			else if (_hoops_SPRI->_hoops_IGHIR == _hoops_SPRI->_hoops_HGHIR)
				_hoops_HICPS = _hoops_RICPS;
			else
				ALLOC_ARRAY (_hoops_HICPS,  _hoops_AAAHA, _hoops_ACGHR);
		}
		if (_hoops_SPRI->_hoops_CAHIR != null)
			ALLOC_ARRAY (_hoops_SICPS,	_hoops_AAAHA, float);
		if (_hoops_SPRI->_hoops_SAHIR != null)
			ALLOC_ARRAY (_hoops_ACCPS,	_hoops_AAAHA, unsigned char);
		if (_hoops_SPRI->normals != null)
			ALLOC_ARRAY (_hoops_HCCPS,	_hoops_AAAHA, Vector);
		if (_hoops_SPRI->params != null)
			ALLOC_ARRAY (_hoops_CCCPS,	_hoops_AAAHA*param_width, _hoops_RSSH);

		_hoops_ICRRH	   = _hoops_GPCPS;
		_hoops_PPCPS	   = _hoops_APCPS;
		_hoops_CPCPS	   = _hoops_IPCPS;
		_hoops_RHCPS	   = _hoops_GHCPS;
		_hoops_HHCPS	   = _hoops_PHCPS;
		_hoops_SHCPS  = _hoops_CHCPS;
		_hoops_AICPS  = _hoops_RICPS;
		_hoops_IICPS  = _hoops_HICPS;
		_hoops_GCCPS	   = _hoops_SICPS;
		_hoops_PCCPS	   = _hoops_ACCPS;
		_hoops_RSCRA	   = _hoops_HCCPS;
		_hoops_RPHCP	   = _hoops_CCCPS;


		if (offset > 0) {
			if (_hoops_SCCPS) {
				_hoops_AIGA (_hoops_CICHH, offset, Local_Vertex_Flags, _hoops_ICRRH);
				_hoops_CICHH += offset;
				_hoops_ICRRH += offset;
			}
			else if (_hoops_SPRI->_hoops_SGRHR != 0 && _hoops_ICRRH != null) {
				for (int i = 0; i < offset; i++)
					*_hoops_ICRRH++ = _hoops_SPRI->_hoops_SGRHR;
			}
			if (_hoops_RPCPS != null) {
				_hoops_AIGA (_hoops_RPCPS, offset, RGBAS32, _hoops_PPCPS);
				_hoops_RPCPS += offset;
				_hoops_PPCPS += offset;
			}
			if (_hoops_HPCPS != null) {
				_hoops_AIGA (_hoops_HPCPS, offset, RGB, _hoops_CPCPS);
				_hoops_HPCPS += offset;
				_hoops_CPCPS += offset;
			}
			if (_hoops_SPCPS != null) {
				_hoops_AIGA (_hoops_SPCPS, offset, RGB, _hoops_RHCPS);
				_hoops_SPCPS += offset;
				_hoops_RHCPS += offset;
			}
			if (_hoops_AHCPS != null) {
				_hoops_AIGA (_hoops_AHCPS, offset, RGB, _hoops_HHCPS);
				_hoops_AHCPS += offset;
				_hoops_HHCPS += offset;
			}
			if (_hoops_IHCPS != null) {
				_hoops_AIGA (_hoops_IHCPS, offset, _hoops_ACGHR, _hoops_SHCPS);
				_hoops_IHCPS += offset;
				_hoops_SHCPS += offset;
			}
			if (_hoops_GICPS != null) {
				_hoops_AIGA (_hoops_GICPS, offset, _hoops_ACGHR, _hoops_AICPS);
				_hoops_GICPS += offset;
				_hoops_AICPS += offset;
			}
			if (_hoops_PICPS != null) {
				_hoops_AIGA (_hoops_PICPS, offset, _hoops_ACGHR, _hoops_IICPS);
				_hoops_PICPS += offset;
				_hoops_IICPS += offset;
			}
			if (_hoops_CICPS != null) {
				_hoops_AIGA (_hoops_CICPS, offset, float, _hoops_GCCPS);
				_hoops_CICPS += offset;
				_hoops_GCCPS += offset;
			}
			if (_hoops_RCCPS != null) {
				_hoops_AIGA (_hoops_RCCPS, offset, unsigned char, _hoops_PCCPS);
				_hoops_RCCPS += offset;
				_hoops_PCCPS += offset;
			}
			if (_hoops_CIRSH != null) {
				_hoops_AIGA (_hoops_CIRSH, offset, Vector, _hoops_RSCRA);
				_hoops_CIRSH += offset;
				_hoops_RSCRA += offset;
			}
			if (_hoops_ICCPS != null) {
				_hoops_AIGA (_hoops_ICCPS, offset * param_width, _hoops_RSSH, _hoops_RPHCP);
				_hoops_ICCPS += offset * param_width;
				_hoops_RPHCP += offset * param_width;
			}
		}

		if (ndelete > 0) {
			Local_Vertex_Flags *	_hoops_GSCPS;

			_hoops_GSCPS = _hoops_CICHH + ndelete;

			if (BIT(_hoops_SPHPR->polyhedron_flags, _hoops_CGRHR)) {
				_hoops_GSCPS = _hoops_CICHH + ndelete;
				if (_hoops_CICHH != null) do {
					if (BIT (*_hoops_CICHH, _hoops_PHIAA))
						--_hoops_SPRI->_hoops_CPIAA;
					if (BIT (*_hoops_CICHH, _hoops_HHIAA))
						--_hoops_SPRI->_hoops_SIIPR;
					if (BIT (*_hoops_CICHH, _hoops_HCRRA))
						--_hoops_SPRI->_hoops_ICRRA;
					if (BIT (*_hoops_CICHH, _hoops_SIRRA))
						--_hoops_SPRI->_hoops_PCRRA;
					if (BIT (*_hoops_CICHH, _hoops_CCRRA))
						--_hoops_SPRI->_hoops_HIRRA;
					if (BIT (*_hoops_CICHH, _hoops_PPHPR))
						--_hoops_SPRI->_hoops_SCHPR;
					if (BIT (*_hoops_CICHH, _hoops_RPHPR))
						--_hoops_SPRI->_hoops_CCHPR;
					if (BIT (*_hoops_CICHH, _hoops_AARHR))
						--_hoops_SPRI->_hoops_RCRHR;
					if (BIT (*_hoops_CICHH, _hoops_HARHR))
						--_hoops_SPRI->_hoops_SIRHR;
					if (BIT (*_hoops_CICHH, _hoops_GCICA))
						--_hoops_SPRI->_hoops_SCHHC;
					if (BIT (*_hoops_CICHH, _hoops_SIICA)) {
						Polyhedron *		_hoops_HPGPR = (Polyhedron *)_hoops_SPHPR;
						_hoops_RPHIR *		_hoops_GARSA;
						unsigned char		symbol;

						symbol = _hoops_SPRI->_hoops_SAHIR[_hoops_CICHH - _hoops_SPRI->flags];
						_hoops_GARSA = HI_LVA_Symbol_Lookup (_hoops_HPGPR, symbol);
						if (_hoops_ISAI(_hoops_GARSA) == 0)
							HI_LVA_Symbol_Delete (_hoops_HPGPR, _hoops_GARSA);

						--_hoops_SPRI->_hoops_AHIIC;
					}
					if (BIT (*_hoops_CICHH, LVA_EXPLICIT_NORMAL))
						--_hoops_SPRI->explicit_normal_count;
					if (BIT (*_hoops_CICHH, _hoops_ASAPA))
						--_hoops_SPRI->_hoops_RSAPA;
				} _hoops_RGGA (++_hoops_CICHH == _hoops_GSCPS);
			}
			else {
				if (_hoops_SPRI->_hoops_SGRHR != 0) {
					if (BIT (*_hoops_CICHH, _hoops_PHIAA))
						_hoops_SPRI->_hoops_CPIAA -= ndelete;
					if (BIT (*_hoops_CICHH, _hoops_HHIAA))
						_hoops_SPRI->_hoops_SIIPR -= ndelete;
					if (BIT (*_hoops_CICHH, _hoops_HCRRA))
						_hoops_SPRI->_hoops_ICRRA -= ndelete;
					if (BIT (*_hoops_CICHH, _hoops_SIRRA))
						_hoops_SPRI->_hoops_PCRRA -= ndelete;
					if (BIT (*_hoops_CICHH, _hoops_CCRRA))
						_hoops_SPRI->_hoops_HIRRA -= ndelete;
					if (BIT (*_hoops_CICHH, _hoops_PPHPR))
						_hoops_SPRI->_hoops_SCHPR -= ndelete;
					if (BIT (*_hoops_CICHH, _hoops_RPHPR))
						_hoops_SPRI->_hoops_CCHPR -= ndelete;
					if (BIT (*_hoops_CICHH, _hoops_AARHR))
						_hoops_SPRI->_hoops_RCRHR -= ndelete;
					if (BIT (*_hoops_CICHH, _hoops_HARHR))
						_hoops_SPRI->_hoops_SIRHR -= ndelete;
					if (BIT (*_hoops_CICHH, _hoops_GCICA))
						_hoops_SPRI->_hoops_SCHHC -= ndelete;
					if (BIT (*_hoops_CICHH, _hoops_SIICA)) {
						Polyhedron *		_hoops_HPGPR = (Polyhedron *)_hoops_SPHPR;
						_hoops_RPHIR *		_hoops_GARSA;
						unsigned char		symbol;

						symbol = _hoops_SPRI->_hoops_SAHIR[offset];
						_hoops_GARSA = HI_LVA_Symbol_Lookup (_hoops_HPGPR, symbol);
						if (_hoops_ISAI(_hoops_GARSA) == 0)
							HI_LVA_Symbol_Delete (_hoops_HPGPR, _hoops_GARSA);

						_hoops_SPRI->_hoops_AHIIC -= ndelete;
					}
					if (BIT (*_hoops_CICHH, LVA_EXPLICIT_NORMAL))
						_hoops_SPRI->explicit_normal_count -= ndelete;
					if (BIT (*_hoops_CICHH, _hoops_ASAPA))
						_hoops_SPRI->_hoops_RSAPA -= ndelete;
				}
			}

			if (_hoops_RPCPS	   != null) _hoops_RPCPS	   += ndelete;
			if (_hoops_HPCPS	   != null) _hoops_HPCPS	   += ndelete;
			if (_hoops_SPCPS	   != null) _hoops_SPCPS	   += ndelete;
			if (_hoops_AHCPS	   != null) _hoops_AHCPS	   += ndelete;
			if (_hoops_IHCPS  != null) _hoops_IHCPS  += ndelete;
			if (_hoops_GICPS  != null) _hoops_GICPS  += ndelete;
			if (_hoops_PICPS  != null) _hoops_PICPS  += ndelete;
			if (_hoops_CICPS	   != null) _hoops_CICPS	   += ndelete;
			if (_hoops_RCCPS	   != null) _hoops_RCCPS	   += ndelete;
			if (_hoops_CIRSH	   != null) _hoops_CIRSH	   += ndelete;
			if (_hoops_ICCPS	   != null) _hoops_ICCPS	   += ndelete * param_width;
		}

		if (insert > 0) {
			count = insert;		/* _hoops_CRGR _hoops_IRS _hoops_GCPR */
			do {
				if (_hoops_ICRRH	!= null)	*_hoops_ICRRH++ = 0;
				if (_hoops_PPCPS != null)		*_hoops_PPCPS++ = _hoops_CAHSR::_hoops_RPSR;
				if (_hoops_CPCPS != null)	*_hoops_CPCPS++ = _hoops_GPSR::_hoops_RPSR;
				if (_hoops_RHCPS != null)	*_hoops_RHCPS++ = _hoops_GPSR::_hoops_RPSR;
				if (_hoops_HHCPS != null)	*_hoops_HHCPS++ = _hoops_GPSR::_hoops_RPSR;
				if (_hoops_SHCPS != null)	*_hoops_SHCPS++ = 0.0f;
				if (_hoops_AICPS != null)	*_hoops_AICPS++ = 0.0f;
				if (_hoops_IICPS != null)	*_hoops_IICPS++ = 0.0f;
				if (_hoops_GCCPS	!= null)	*_hoops_GCCPS++ = 0.0f;
				if (_hoops_PCCPS != null)	*_hoops_PCCPS++ = 0;
				if (_hoops_RSCRA != null)	*_hoops_RSCRA++ = _hoops_IRGA::_hoops_CRGA;
				if (_hoops_RPHCP	!= null)	{
					_hoops_CRAGI(_hoops_RPHCP, param_width);
					_hoops_RPHCP += param_width;
				}
			} _hoops_RGGA (--count == 0);
		}

		count = _hoops_CACPS - offset - ndelete;
		if (count > 0) {
			if (_hoops_SCCPS)
				_hoops_AIGA (_hoops_CICHH, count, Local_Vertex_Flags, _hoops_ICRRH);
			else if (_hoops_SPRI->_hoops_SGRHR != 0 && _hoops_ICRRH != null) {
				for (int i = 0; i < offset; i++)
					*_hoops_ICRRH++ = _hoops_SPRI->_hoops_SGRHR;
			}
			if (_hoops_RPCPS != null)
				_hoops_AIGA (_hoops_RPCPS, count, RGBAS32, _hoops_PPCPS);
			if (_hoops_HPCPS != null)
				_hoops_AIGA (_hoops_HPCPS, count, RGB, _hoops_CPCPS);
			if (_hoops_SPCPS != null)
				_hoops_AIGA (_hoops_SPCPS, count, RGB, _hoops_RHCPS);
			if (_hoops_AHCPS != null)
				_hoops_AIGA (_hoops_AHCPS, count, RGB, _hoops_HHCPS);
			if (_hoops_IHCPS != null)
				_hoops_AIGA (_hoops_IHCPS, count, _hoops_ACGHR, _hoops_SHCPS);
			if (_hoops_GICPS != null)
				_hoops_AIGA (_hoops_GICPS, count, _hoops_ACGHR, _hoops_AICPS);
			if (_hoops_PICPS != null)
				_hoops_AIGA (_hoops_PICPS, count, _hoops_ACGHR, _hoops_IICPS);
			if (_hoops_CICPS != null)
				_hoops_AIGA (_hoops_CICPS, count, float, _hoops_GCCPS);
			if (_hoops_RCCPS != null)
				_hoops_AIGA (_hoops_RCCPS, count, unsigned char, _hoops_PCCPS);
			if (_hoops_CIRSH != null)
				_hoops_AIGA (_hoops_CIRSH, count, Vector, _hoops_RSCRA);
			if (_hoops_ICCPS != null)
				_hoops_AIGA (_hoops_ICCPS, count * param_width, _hoops_RSSH, _hoops_RPHCP);
		}

		if (_hoops_SPRI->flags != null && BIT(_hoops_SPHPR->polyhedron_flags, _hoops_CGRHR))
			FREE_ARRAY (_hoops_SPRI->flags, _hoops_CACPS, Local_Vertex_Flags);
		if (_hoops_SPRI->_hoops_IAHIR != null)
			FREE_ARRAY (_hoops_SPRI->_hoops_IAHIR, _hoops_CACPS, RGBAS32);
		if (_hoops_SPRI->_hoops_PAHIR != null)
			FREE_ARRAY (_hoops_SPRI->_hoops_PAHIR, _hoops_CACPS, RGB);
		if (_hoops_SPRI->ecolors != null && _hoops_SPRI->ecolors != _hoops_SPRI->_hoops_PAHIR)
			FREE_ARRAY (_hoops_SPRI->ecolors, _hoops_CACPS, RGB);
		if (_hoops_SPRI->fcolors != null && _hoops_SPRI->fcolors != _hoops_SPRI->_hoops_PAHIR && _hoops_SPRI->fcolors != _hoops_SPRI->ecolors)
			FREE_ARRAY (_hoops_SPRI->fcolors, _hoops_CACPS, RGB);
		if (_hoops_SPRI->_hoops_HAHIR != null)
			FREE_ARRAY (_hoops_SPRI->_hoops_HAHIR, _hoops_CACPS, _hoops_ACGHR);
		if (_hoops_SPRI->_hoops_HGHIR != null && _hoops_SPRI->_hoops_HGHIR != _hoops_SPRI->_hoops_HAHIR)
			FREE_ARRAY (_hoops_SPRI->_hoops_HGHIR, _hoops_CACPS, _hoops_ACGHR);
		if (_hoops_SPRI->_hoops_IGHIR != null && _hoops_SPRI->_hoops_IGHIR != _hoops_SPRI->_hoops_HAHIR && _hoops_SPRI->_hoops_IGHIR != _hoops_SPRI->_hoops_HGHIR)
			FREE_ARRAY (_hoops_SPRI->_hoops_IGHIR, _hoops_CACPS, _hoops_ACGHR);
		if (_hoops_SPRI->_hoops_CAHIR != null)
			FREE_ARRAY (_hoops_SPRI->_hoops_CAHIR, _hoops_CACPS, float);
		if (_hoops_SPRI->_hoops_SAHIR != null)
			FREE_ARRAY (_hoops_SPRI->_hoops_SAHIR, _hoops_CACPS, unsigned char);
		if (_hoops_SPRI->normals != null)
			FREE_ARRAY (_hoops_SPRI->normals, _hoops_CACPS, Vector);
		if (_hoops_SPRI->params != null)
			FREE_ARRAY (_hoops_SPRI->params, _hoops_CACPS*param_width, _hoops_RSSH);

		_hoops_SPRI->flags		 = _hoops_GPCPS;
		_hoops_SPRI->_hoops_PAHIR	= _hoops_IPCPS;
		_hoops_SPRI->ecolors	= _hoops_GHCPS;
		_hoops_SPRI->fcolors	= _hoops_PHCPS;
		_hoops_SPRI->_hoops_HAHIR	= _hoops_CHCPS;
		_hoops_SPRI->_hoops_HGHIR	= _hoops_RICPS;
		_hoops_SPRI->_hoops_IGHIR	= _hoops_HICPS;
		_hoops_SPRI->_hoops_CAHIR		= _hoops_SICPS;
		_hoops_SPRI->_hoops_SAHIR	= _hoops_ACCPS;
		_hoops_SPRI->normals	= _hoops_HCCPS;
		_hoops_SPRI->params		= _hoops_CCCPS;
	}
}

/* _hoops_PAGA: _hoops_RRCPR'_hoops_GRI _hoops_HSP _hoops_RPR _hoops_CGH _hoops_SHH _hoops_RH _hoops_GIGR _hoops_PIRA _hoops_CGPR _hoops_RGR _hoops_HRGR _hoops_PIGS */
GLOBAL_FUNCTION void HI_Adjust_Face_Attributes (
	Shell *				_hoops_SPHPR,
	int					offset,
	int					ndelete,
	int					insert)
{
	int					count;
	int					_hoops_GGCPS;
	int					_hoops_CIIIC;

	_hoops_GGCPS = _hoops_SPHPR->face_count;
	_hoops_CIIIC = _hoops_GGCPS - ndelete + insert;

	if (_hoops_SPHPR->local_face_attributes.regions != null) {
		if (insert == ndelete) {
			/* _hoops_PGHH _hoops_HAR _hoops_RGISH */
		}
		else if (_hoops_CIIIC == 0) {
			FREE_ARRAY (_hoops_SPHPR->local_face_attributes.regions, _hoops_GGCPS +_hoops_SHHIR, int);
			_hoops_SPHPR->local_face_attributes.regions = null;
		}
		else {
			int *		_hoops_SGCPS;
			int *		_hoops_GRCPS;
			int *		_hoops_RSCPS = null;

			_hoops_SGCPS = _hoops_SPHPR->local_face_attributes.regions;

			ALLOC_ARRAY (_hoops_RSCPS, _hoops_CIIIC +_hoops_SHHIR, int);

			_hoops_GRCPS = _hoops_RSCPS;

			if (offset > 0) {
				_hoops_AIGA (_hoops_SGCPS, offset, int, _hoops_GRCPS);
				_hoops_SGCPS += offset;
				_hoops_GRCPS += offset;
			}

			_hoops_SGCPS += ndelete;

			if (insert > 0) {
				ZERO_ARRAY (_hoops_GRCPS, insert, int);
				_hoops_GRCPS += insert;
			}

			count = _hoops_GGCPS - offset - ndelete;
			if (count)
				_hoops_AIGA (_hoops_SGCPS, count, int, _hoops_GRCPS);

			FREE_ARRAY (_hoops_SPHPR->local_face_attributes.regions, _hoops_GGCPS +_hoops_SHHIR, int);

			/* _hoops_PRGSI _hoops_RH _hoops_ISPH _hoops_CCIR (_hoops_HPGR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_PGHH _hoops_CRPR). */
			_hoops_RSCPS[_hoops_CIIIC + _hoops_GISCC] = 0;

			_hoops_SPHPR->local_face_attributes.regions = _hoops_RSCPS;
		}
	}

	if (_hoops_SPHPR->local_face_attributes.flags != null || _hoops_SPHPR->local_face_attributes._hoops_SGRHR != 0 ||
		_hoops_SPHPR->local_face_attributes.normals != null) {
		bool _hoops_ASCPS = false;
		if (insert == ndelete) {
			_hoops_GIIPR *		_hoops_RIIPR;
			_hoops_GIIPR *		_hoops_PSCPS;

			if (BIT(_hoops_SPHPR->polyhedron_flags, _hoops_APRHR)) {
				/* _hoops_CIPAA _hoops_GGR _hoops_HGHC */
				_hoops_RIIPR = _hoops_SPHPR->local_face_attributes._hoops_CHHPR(offset);
				_hoops_PSCPS = _hoops_RIIPR + insert;
				do {
					if (BIT (*_hoops_RIIPR, _hoops_IAGI))
						--_hoops_SPHPR->local_face_attributes._hoops_CPIAA;
					if (BIT (*_hoops_RIIPR, _hoops_HSIPR))
						--_hoops_SPHPR->local_face_attributes._hoops_SIIPR;
					if (BIT (*_hoops_RIIPR, LFA_EXPLICIT_COLOR_BY_VALUE))
						--_hoops_SPHPR->local_face_attributes._hoops_HSRRA;
					if (BIT (*_hoops_RIIPR, LFA_EXPLICIT_COLOR_BY_FINDEX))
						--_hoops_SPHPR->local_face_attributes._hoops_PSRRA;
					if (BIT (*_hoops_RIIPR, _hoops_HAGI))
						--_hoops_SPHPR->local_face_attributes._hoops_SRAPA;
					if (BIT (*_hoops_RIIPR, LFA_EXPLICIT_NORMAL))
						--_hoops_SPHPR->local_face_attributes.explicit_normal_count;
					*_hoops_RIIPR = 0;
				} _hoops_RGGA (++_hoops_RIIPR == _hoops_PSCPS);
			}
			else {
				_hoops_RIIPR = _hoops_SPHPR->local_face_attributes._hoops_CHHPR(offset);
				if (BIT (*_hoops_RIIPR, _hoops_IAGI))
					_hoops_SPHPR->local_face_attributes._hoops_CPIAA -= insert;
				if (BIT (*_hoops_RIIPR, _hoops_HSIPR))
					_hoops_SPHPR->local_face_attributes._hoops_SIIPR -= insert;
				if (BIT (*_hoops_RIIPR, LFA_EXPLICIT_COLOR_BY_VALUE))
					_hoops_SPHPR->local_face_attributes._hoops_HSRRA -= insert;
				if (BIT (*_hoops_RIIPR, LFA_EXPLICIT_COLOR_BY_FINDEX))
					_hoops_SPHPR->local_face_attributes._hoops_PSRRA -= insert;
				if (BIT (*_hoops_RIIPR, _hoops_HAGI))
					_hoops_SPHPR->local_face_attributes._hoops_SRAPA -= insert;
				if (BIT (*_hoops_RIIPR, LFA_EXPLICIT_NORMAL))
					_hoops_SPHPR->local_face_attributes.explicit_normal_count -= insert;
				*_hoops_RIIPR = 0;
			}
		}
		else if (_hoops_CIIIC == 0) {
			if (_hoops_SPHPR->local_face_attributes.flags != null) {
				FREE_ARRAY (_hoops_SPHPR->local_face_attributes.flags,
							_hoops_GGCPS, _hoops_GIIPR);
				_hoops_SPHPR->local_face_attributes.flags = null;
				_hoops_SPHPR->local_face_attributes._hoops_SGRHR = 0;
				_hoops_SPHPR->polyhedron_flags &= ~ _hoops_APRHR;
			}

			if (_hoops_SPHPR->local_face_attributes.colors != null) {
				FREE_ARRAY (_hoops_SPHPR->local_face_attributes.colors,
							_hoops_GGCPS, RGB);
				_hoops_SPHPR->local_face_attributes.colors = null;
			}

			if (_hoops_SPHPR->local_face_attributes.findices != null) {
				FREE_ARRAY (_hoops_SPHPR->local_face_attributes.findices,
							_hoops_GGCPS, _hoops_ACGHR);
				_hoops_SPHPR->local_face_attributes.findices = null;
			}

			if (_hoops_SPHPR->local_face_attributes._hoops_AHHIR != null) {
				FREE_ARRAY (_hoops_SPHPR->local_face_attributes._hoops_AHHIR,
							_hoops_GGCPS, unsigned char);
				_hoops_SPHPR->local_face_attributes._hoops_AHHIR = null;
			}

			if (_hoops_SPHPR->local_face_attributes.normals != null) {
				FREE_ARRAY_ALIGNED (_hoops_SPHPR->local_face_attributes.normals,
									_hoops_GGCPS, _hoops_ARPA, 16);
				_hoops_SPHPR->local_face_attributes.normals = null;
			}

			_hoops_SPHPR->local_face_attributes._hoops_CPIAA			= 0;
			_hoops_SPHPR->local_face_attributes._hoops_SIIPR		= 0;
			_hoops_SPHPR->local_face_attributes._hoops_HSRRA	= 0;
			_hoops_SPHPR->local_face_attributes._hoops_PSRRA	= 0;
			_hoops_SPHPR->local_face_attributes._hoops_SRAPA			= 0;
			_hoops_SPHPR->local_face_attributes.explicit_normal_count			= 0;
		}
		else {
			_hoops_GIIPR *			_hoops_CICHH;
			_hoops_GIIPR *			_hoops_ICRRH;
			_hoops_GIIPR *			_hoops_GPCPS = null;
			RGB *						_hoops_PGICP;
			RGB *						_hoops_RCISH;
			RGB *						_hoops_HSCPS = null;
			_hoops_ACGHR *			_hoops_PGCPS;
			_hoops_ACGHR *			_hoops_HGCPS;
			_hoops_ACGHR *			_hoops_ISCPS = null;
			unsigned char *				_hoops_IGCPS;
			unsigned char *				_hoops_CGCPS;
			unsigned char *				_hoops_CSCPS = null;
			_hoops_ARPA *						_hoops_CIRSH;
			_hoops_ARPA *						_hoops_RSCRA;
			_hoops_ARPA *						_hoops_HCCPS = null;

			_hoops_CICHH	 = _hoops_SPHPR->local_face_attributes.flags;
			_hoops_PGICP	 = _hoops_SPHPR->local_face_attributes.colors;
			_hoops_PGCPS = _hoops_SPHPR->local_face_attributes.findices;
			_hoops_IGCPS = _hoops_SPHPR->local_face_attributes._hoops_AHHIR;
			_hoops_CIRSH	 = _hoops_SPHPR->local_face_attributes.normals;

			if ((_hoops_CICHH != null && BIT(_hoops_SPHPR->polyhedron_flags, _hoops_APRHR)) ||
				ndelete - insert != 0) {
				ZALLOC_ARRAY (_hoops_GPCPS,	_hoops_CIIIC, _hoops_GIIPR);
				if (!BIT(_hoops_SPHPR->polyhedron_flags, _hoops_APRHR)) {
					for (int i = 0; i < _hoops_CIIIC; i++) {
						_hoops_GPCPS[i] = _hoops_SPHPR->local_face_attributes._hoops_SGRHR;
					}
				}
				_hoops_ASCPS = true;
			}
			if (_hoops_PGICP != null)
				ALLOC_ARRAY (_hoops_HSCPS,	_hoops_CIIIC, RGB);
			if (_hoops_PGCPS != null)
				ALLOC_ARRAY (_hoops_ISCPS, _hoops_CIIIC, _hoops_ACGHR);
			if (_hoops_IGCPS != null)
				ALLOC_ARRAY (_hoops_CSCPS, _hoops_CIIIC, unsigned char);
			if (_hoops_CIRSH != null)
				ALLOC_ARRAY_ALIGNED (_hoops_HCCPS,	_hoops_CIIIC, _hoops_ARPA, 16);

			_hoops_ICRRH	 = _hoops_GPCPS;
			_hoops_RCISH	 = _hoops_HSCPS;
			_hoops_HGCPS = _hoops_ISCPS;
			_hoops_CGCPS = _hoops_CSCPS;
			_hoops_RSCRA	 = _hoops_HCCPS;

			if (offset > 0) {
				if (_hoops_CICHH != null && BIT(_hoops_SPHPR->polyhedron_flags, _hoops_APRHR)) {
					_hoops_AIGA (_hoops_CICHH, offset, _hoops_GIIPR, _hoops_ICRRH);
					_hoops_CICHH += offset;
					_hoops_ICRRH += offset;
				}
				else if (!BIT(_hoops_SPHPR->polyhedron_flags, _hoops_APRHR) && _hoops_SPHPR->local_face_attributes._hoops_SGRHR != 0) {
					if (_hoops_ICRRH) {
						for (int i =0; i < offset; i++) {
							_hoops_ICRRH[i] = _hoops_SPHPR->local_face_attributes._hoops_SGRHR;
						}
						_hoops_ICRRH += offset;
					}
				}
				if (_hoops_PGICP != null) {
					_hoops_AIGA (_hoops_PGICP, offset, RGB, _hoops_RCISH);
					_hoops_PGICP += offset;
					_hoops_RCISH += offset;
				}
				if (_hoops_PGCPS != null) {
					_hoops_AIGA (_hoops_PGCPS, offset, _hoops_ACGHR, _hoops_HGCPS);
					_hoops_PGCPS += offset;
					_hoops_HGCPS += offset;
				}
				if (_hoops_IGCPS != null) {
					_hoops_AIGA (_hoops_IGCPS, offset, unsigned char, _hoops_CGCPS);
					_hoops_IGCPS += offset;
					_hoops_CGCPS += offset;
				}
				if (_hoops_CIRSH != null) {
					_hoops_AIGA (_hoops_CIRSH, offset, _hoops_ARPA, _hoops_RSCRA);
					_hoops_CIRSH += offset;
					_hoops_RSCRA += offset;
				}
			}

			if (ndelete > 0) {
				_hoops_GIIPR *		_hoops_GSCPS;

				if (BIT(_hoops_SPHPR->polyhedron_flags, _hoops_APRHR)) {
					_hoops_GSCPS = _hoops_CICHH + ndelete;
					if (_hoops_CICHH != null) do {
						if (BIT (*_hoops_CICHH, _hoops_IAGI))
							--_hoops_SPHPR->local_face_attributes._hoops_CPIAA;
						if (BIT (*_hoops_CICHH, _hoops_HSIPR))
							--_hoops_SPHPR->local_face_attributes._hoops_SIIPR;
						if (BIT (*_hoops_CICHH, LFA_EXPLICIT_COLOR_BY_VALUE))
							--_hoops_SPHPR->local_face_attributes._hoops_HSRRA;
						if (BIT (*_hoops_CICHH, LFA_EXPLICIT_COLOR_BY_FINDEX))
							--_hoops_SPHPR->local_face_attributes._hoops_PSRRA;
						if (BIT (*_hoops_CICHH, _hoops_HAGI))
							--_hoops_SPHPR->local_face_attributes._hoops_SRAPA;
						if (BIT (*_hoops_CICHH, LFA_EXPLICIT_NORMAL))
							--_hoops_SPHPR->local_face_attributes.explicit_normal_count;
					} _hoops_RGGA (++_hoops_CICHH == _hoops_GSCPS);
				}
				else {
					if (_hoops_SPHPR->local_face_attributes._hoops_SGRHR != 0) {
						if (BIT (_hoops_SPHPR->local_face_attributes._hoops_SGRHR, _hoops_IAGI))
							_hoops_SPHPR->local_face_attributes._hoops_CPIAA -= ndelete;
						if (BIT (_hoops_SPHPR->local_face_attributes._hoops_SGRHR, _hoops_HSIPR))
							_hoops_SPHPR->local_face_attributes._hoops_SIIPR -= ndelete;
						if (BIT (_hoops_SPHPR->local_face_attributes._hoops_SGRHR, LFA_EXPLICIT_COLOR_BY_VALUE))
							_hoops_SPHPR->local_face_attributes._hoops_HSRRA -= ndelete;
						if (BIT (_hoops_SPHPR->local_face_attributes._hoops_SGRHR, LFA_EXPLICIT_COLOR_BY_FINDEX))
							_hoops_SPHPR->local_face_attributes._hoops_PSRRA -= ndelete;
						if (BIT (_hoops_SPHPR->local_face_attributes._hoops_SGRHR, _hoops_HAGI))
							_hoops_SPHPR->local_face_attributes._hoops_SRAPA -= ndelete;
						if (BIT (_hoops_SPHPR->local_face_attributes._hoops_SGRHR, LFA_EXPLICIT_NORMAL))
							_hoops_SPHPR->local_face_attributes.explicit_normal_count -= ndelete;
					}
				}

				if (_hoops_PGICP	 != null) _hoops_PGICP   += ndelete;
				if (_hoops_PGCPS != null) _hoops_PGCPS += ndelete;
				if (_hoops_IGCPS != null) _hoops_IGCPS += ndelete;
				if (_hoops_CIRSH	 != null) _hoops_CIRSH  += ndelete;
			}

			if (insert > 0) {
				count = insert; /* _hoops_CRGR _hoops_IRS _hoops_GCPR */
				do {
					if (_hoops_ICRRH != null) *_hoops_ICRRH = 0;
					if (_hoops_RCISH != null) *_hoops_RCISH = _hoops_GPSR::_hoops_RPSR;
					if (_hoops_HGCPS != null) *_hoops_HGCPS = 0.0f;
					if (_hoops_CGCPS != null) *_hoops_CGCPS = 0;
					if (_hoops_RSCRA != null)
						_hoops_RSCRA->a = _hoops_RSCRA->b = _hoops_RSCRA->c = _hoops_RSCRA->d = 0.0f;

					if (_hoops_ICRRH != null) ++_hoops_ICRRH;
					if (_hoops_RCISH != null) ++_hoops_RCISH;
					if (_hoops_HGCPS != null) ++_hoops_HGCPS;
					if (_hoops_CGCPS != null) ++_hoops_CGCPS;
					if (_hoops_RSCRA != null) ++_hoops_RSCRA;
				} _hoops_RGGA (--count == 0);
			}

			count = _hoops_GGCPS - offset - ndelete;
			if (count > 0) {
				if (_hoops_CICHH != null && BIT(_hoops_SPHPR->polyhedron_flags, _hoops_APRHR))
					_hoops_AIGA (_hoops_CICHH, count, _hoops_GIIPR, _hoops_ICRRH);
				if (_hoops_PGICP != null)
					_hoops_AIGA (_hoops_PGICP, count, RGB, _hoops_RCISH);
				if (_hoops_PGCPS != null)
					_hoops_AIGA (_hoops_PGCPS, count, _hoops_ACGHR, _hoops_HGCPS);
				if (_hoops_IGCPS != null)
					_hoops_AIGA (_hoops_IGCPS, count, unsigned char, _hoops_CGCPS);
				if (_hoops_CIRSH != null)
					_hoops_AIGA (_hoops_CIRSH, count, _hoops_ARPA, _hoops_RSCRA);
			}

			if (_hoops_CICHH != null && BIT(_hoops_SPHPR->polyhedron_flags, _hoops_APRHR))
				FREE_ARRAY (_hoops_SPHPR->local_face_attributes._hoops_CHHPR(), _hoops_GGCPS, _hoops_GIIPR);
			if (_hoops_PGICP != null)
				FREE_ARRAY (_hoops_SPHPR->local_face_attributes.colors, _hoops_GGCPS, RGB);
			if (_hoops_PGCPS != null)
				FREE_ARRAY (_hoops_SPHPR->local_face_attributes.findices, _hoops_GGCPS, _hoops_ACGHR);
			if (_hoops_IGCPS != null)
				FREE_ARRAY (_hoops_SPHPR->local_face_attributes._hoops_AHHIR, _hoops_GGCPS, unsigned char);
			if (_hoops_CIRSH != null)
				FREE_ARRAY_ALIGNED (_hoops_SPHPR->local_face_attributes.normals, _hoops_GGCPS, _hoops_ARPA, 16);

			_hoops_SPHPR->local_face_attributes.flags	 = _hoops_GPCPS;
			if (_hoops_ASCPS && _hoops_SPHPR->local_face_attributes.flags != null)
				_hoops_SPHPR->polyhedron_flags |= _hoops_APRHR;
			_hoops_SPHPR->local_face_attributes.colors	 = _hoops_HSCPS;
			_hoops_SPHPR->local_face_attributes.findices = _hoops_ISCPS;
			_hoops_SPHPR->local_face_attributes._hoops_AHHIR = _hoops_CSCPS;
			_hoops_SPHPR->local_face_attributes.normals	 = _hoops_HCCPS;
		}
	}
}

/* _hoops_PAGA: _hoops_RH _hoops_CCAH _hoops_SCAPA _hoops_CGH _hoops_SHH _hoops_GGR _hoops_HGHC _hoops_CGPR _hoops_RGR _hoops_HRGR _hoops_PIGS */
GLOBAL_FUNCTION void HI_Repair_Shell_Edges (
	_hoops_AIGPR *	_hoops_RIGC,
	Shell *					_hoops_SPHPR)
{
	
	_hoops_CRCP *	_hoops_ARPGR;
	if ((_hoops_ARPGR = _hoops_SPHPR->owner) != null)
		_hoops_ARPGR->_hoops_RHAGR._hoops_PRPGR(_hoops_RIGC->thread_id);

	/*
	 * _hoops_AISA _hoops_SPPR & _hoops_PAII _hoops_AIRC
	 */
	bool					_hoops_SSCPS;

	if (_hoops_SPHPR->_hoops_SGCPR == null)
		_hoops_SSCPS = false;
	else {
		FREE_ARRAY (_hoops_SPHPR->_hoops_SGCPR, _hoops_SPHPR->_hoops_SPHA, _hoops_CGCPR);
		_hoops_SPHPR->_hoops_SGCPR = null;
		_hoops_SSCPS = true;
		/* (_hoops_SAHR _hoops_PIAGR _hoops_CAPR _hoops_HII _hoops_SI) */
	}

	if (_hoops_SPHPR->_hoops_GRCPR == null) {
		/* _hoops_CAIP'_hoops_RA _hoops_RRP _hoops_IS _hoops_GGSPS _hoops_AARI _hoops_CCA _hoops_PGI _hoops_SPPR _hoops_PAR _hoops_ISHA _hoops_AIRC */
	}
	else if (_hoops_SPHPR->_hoops_IHHPR.flags == null) {
		/* _hoops_PIHA _hoops_PIAGR _hoops_RH _hoops_ISHA _hoops_HIGR _hoops_HIH _hoops_HAR _hoops_RH _hoops_ISHA _hoops_AIRC (?) */

		/* _hoops_RSRHR _hoops_SGGR _hoops_RH _hoops_RHGS _hoops_ARIPR */

		FREE_ARRAY (_hoops_SPHPR->_hoops_GRCPR, _hoops_SPHPR->_hoops_SPHA, _hoops_RHHPR);
		_hoops_SPHPR->_hoops_GRCPR = null;
		_hoops_SPHPR->_hoops_SPHA = -1;

		FREE_ARRAY (_hoops_SPHPR->_hoops_HHHPR, _hoops_SPHPR->point_count + 1, _hoops_RHHPR *);
		_hoops_SPHPR->_hoops_HHHPR = null;

		/* _hoops_RPP _hoops_HRCC _hoops_IGRC _hoops_IRHS _hoops_CAPR, _hoops_SSIA _hoops_PAH _hoops_PIAGR _hoops_CAPR... */
	}
	else {
		_hoops_RHHPR **			_hoops_RGSPS;
		_hoops_RHHPR **			_hoops_AGSPS;
		_hoops_RPGHR			_hoops_PGSPS;
		_hoops_RHHPR *			_hoops_HGSPS;
		_hoops_RHHPR *			_hoops_IGSPS;
		int								_hoops_CGSPS;
		_hoops_RHHPR **			_hoops_SGSPS;
		_hoops_RHHPR **			_hoops_GRSPS;
		_hoops_RHHPR *			_hoops_IIRPA;
		int								_hoops_RRSPS;
		int								_hoops_ARSPS;

		_hoops_HGSPS = _hoops_IGSPS = _hoops_SPHPR->_hoops_GRCPR;
		_hoops_CGSPS = _hoops_SPHPR->_hoops_SPHA;
		_hoops_RGSPS = _hoops_AGSPS = _hoops_SPHPR->_hoops_HHHPR;


		/* _hoops_RIPHR _hoops_CCAH _hoops_ISHA _hoops_PAIGR */
		HI_Create_Shell_Edges (_hoops_SPHPR, _hoops_SSCPS);


		/* _hoops_HGCR _hoops_IRS _hoops_IPS _hoops_IIGR _hoops_RH _hoops_RHGS _hoops_IGRI _hoops_CICRR, _hoops_HSGAS _hoops_PRSPS */
		_hoops_RSAI (&_hoops_SPHPR->_hoops_IHHPR, _hoops_RPGHR, &_hoops_PGSPS);

		/* _hoops_CCPP & _hoops_SCAC _hoops_CCAH _hoops_AIRC */
		{
			_hoops_GHHPR		_hoops_HRSPS = 0;

			if (_hoops_PGSPS.colors != null)	  _hoops_HRSPS |= _hoops_SSRRA;
			if (_hoops_PGSPS.findices != null) _hoops_HRSPS |= _hoops_RPGI;
			if (_hoops_PGSPS._hoops_AHHIR != null) _hoops_HRSPS |= _hoops_GPGI;
			if (_hoops_PGSPS.weights != null)  _hoops_HRSPS |= _hoops_SCICA;
			if (_hoops_PGSPS.normals != null)  _hoops_HRSPS |= _hoops_CRAHR;

			ZERO_STRUCT (&_hoops_SPHPR->_hoops_IHHPR, _hoops_RPGHR);
			HI_Initialize_Edge_Attributes ((Polyhedron *)_hoops_SPHPR, _hoops_HRSPS);

			/* _hoops_SAHR _hoops_SRAI _hoops_RH _hoops_HSGP _hoops_HIGR */
			_hoops_SPHPR->_hoops_IHHPR._hoops_PHHIR = _hoops_PGSPS._hoops_PHHIR;
			_hoops_PGSPS._hoops_PHHIR = null;
		}


		/*
		 * 3 _hoops_SSRR _hoops_IRGHC:
		 *
		 * _hoops_PCCP _hoops_ISHA _hoops_HRGR _hoops_GGR _hoops_RH _hoops_CCAH _hoops_HIGR _hoops_RGAR - _hoops_HSPC _hoops_RGCI _hoops_AIRC
		 * _hoops_PCCP _hoops_ISHA _hoops_HRGR _hoops_GGR _hoops_RH _hoops_RHGS _hoops_HIGR _hoops_RGAR - _hoops_HSGR _hoops_RH _hoops_RHGS _hoops_AIRC
		 * _hoops_PCCP _hoops_ISHA _hoops_HRGR _hoops_GGR _hoops_GIPR _hoops_CPCI - _hoops_IPS _hoops_RGCI _hoops_AIRC
		 *
		 * _hoops_SR _hoops_HPCAR _hoops_RH _hoops_ISHA _hoops_HIGR _hoops_HRGR _hoops_GSHHR _hoops_HPP _hoops_GIPR _hoops_HCGP _hoops_PPR _hoops_PASPR
		 */

		_hoops_SGSPS = _hoops_SPHPR->_hoops_HHHPR;
		_hoops_GRSPS = _hoops_SGSPS + _hoops_SPHPR->point_count;

		_hoops_IIRPA = *_hoops_SGSPS;
		_hoops_HGSPS = *_hoops_RGSPS;

		_hoops_RRSPS = 0;
		_hoops_ARSPS = 0;

		do {
			_hoops_RHHPR *	_hoops_IRSPS = *++_hoops_SGSPS;
			_hoops_RHHPR *	_hoops_CRSPS = *++_hoops_RGSPS;

			_hoops_RGGA (_hoops_IIRPA == _hoops_IRSPS && _hoops_HGSPS == _hoops_CRSPS) {
				/* _hoops_RH _hoops_HCGP _hoops_HRGR _hoops_APIP _hoops_IH _hoops_HPGR _hoops_CHGC _hoops_SPR */

				if (_hoops_HGSPS == _hoops_CRSPS ||
					(_hoops_IIRPA != _hoops_IRSPS &&
					 _hoops_IIRPA->_hoops_GIHPR < _hoops_HGSPS->_hoops_GIHPR)) {
					/* _hoops_RH _hoops_CCAH _hoops_SPR _hoops_ASSP'_hoops_RA _hoops_GGCA _hoops_GGR _hoops_RH _hoops_RHGS _hoops_HIGR */
					++_hoops_ARSPS;
					++_hoops_IIRPA;
				}
				else if (_hoops_IIRPA == _hoops_IRSPS ||
						 (_hoops_HGSPS != _hoops_CRSPS &&
						  _hoops_IIRPA->_hoops_GIHPR > _hoops_HGSPS->_hoops_GIHPR)) {
					/* _hoops_RH _hoops_RHGS _hoops_SPR _hoops_ASSP'_hoops_RA _hoops_GGCA _hoops_GGR _hoops_RH _hoops_CCAH _hoops_HIGR */
					_hoops_GHHPR		flags;

					/* _hoops_HIH _hoops_SRS _hoops_CACH _hoops_RPP _hoops_IIH _hoops_CHR _hoops_GII _hoops_SASI _hoops_SRSPS _hoops_IS _hoops_CASI */
					flags = _hoops_PGSPS.flags[_hoops_RRSPS];

					if (BIT (flags, _hoops_GPGI)) {
						Polyhedron *		_hoops_HPGPR = (Polyhedron *)_hoops_SPHPR;
						_hoops_HHHIR *		_hoops_HARSA;

						_hoops_HARSA = HI_LEA_Pattern_Lookup (_hoops_HPGPR, _hoops_PGSPS._hoops_AHHIR[_hoops_RRSPS]);
						if (_hoops_ISAI(_hoops_HARSA) == 0)
							HI_LEA_Pattern_Delete (_hoops_HPGPR, _hoops_HARSA);
					}

					++_hoops_RRSPS;
					++_hoops_HGSPS;
				}
				else {
					_hoops_GHHPR		flags;

					/*
					 * _hoops_RH _hoops_GHSPR _hoops_CHR _hoops_SASPR; _hoops_RH _hoops_ISHA _hoops_PHRPA _hoops_IS _hoops_GGCA
					 */
					flags = _hoops_SPHPR->_hoops_IHHPR.flags[_hoops_ARSPS] = _hoops_PGSPS.flags[_hoops_RRSPS];

					if (BIT (flags, _hoops_APGI))
						++_hoops_SPHPR->_hoops_IHHPR._hoops_CPIAA;
					if (BIT (flags, _hoops_AHIAA))
						++_hoops_SPHPR->_hoops_IHHPR._hoops_SIIPR;
					if (BIT (flags, _hoops_RPGI)) {
						++_hoops_SPHPR->_hoops_IHHPR._hoops_PSRRA;
						_hoops_SPHPR->_hoops_IHHPR.findices[_hoops_ARSPS] = _hoops_PGSPS.findices[_hoops_RRSPS];
					}
					if (BIT (flags, _hoops_SSRRA)) {
						++_hoops_SPHPR->_hoops_IHHPR._hoops_HSRRA;
						_hoops_SPHPR->_hoops_IHHPR.colors[_hoops_ARSPS] = _hoops_PGSPS.colors[_hoops_RRSPS];
					}
					if (BIT (flags, _hoops_GPGI)) {
						++_hoops_SPHPR->_hoops_IHHPR._hoops_SRAPA;
						_hoops_SPHPR->_hoops_IHHPR._hoops_AHHIR[_hoops_ARSPS] = _hoops_PGSPS._hoops_AHHIR[_hoops_RRSPS];
					}
					if (BIT (flags, _hoops_SCICA)) {
						_hoops_SPHPR->_hoops_IHHPR.weights[_hoops_ARSPS] = _hoops_PGSPS.weights[_hoops_RRSPS];
						++_hoops_SPHPR->_hoops_IHHPR._hoops_CCHHC;
					}
					if (BIT (flags, _hoops_CRAHR)) {
						_hoops_SPHPR->_hoops_IHHPR.normals[_hoops_ARSPS] = _hoops_PGSPS.normals[_hoops_RRSPS];
						++_hoops_SPHPR->_hoops_IHHPR.explicit_normal_count;
					}

					++_hoops_ARSPS;
					++_hoops_IIRPA;

					++_hoops_RRSPS;
					++_hoops_HGSPS;
				}
			}
		} _hoops_RGGA (_hoops_SGSPS == _hoops_GRSPS);

		/* _hoops_RSRHR _hoops_SGGR _hoops_RH _hoops_RHGS _hoops_CIPH */
		FREE_ARRAY (_hoops_IGSPS, _hoops_CGSPS, _hoops_RHHPR);
		FREE_ARRAY (_hoops_AGSPS, _hoops_SPHPR->point_count + 1, _hoops_RHHPR *);

		if (_hoops_PGSPS.flags != null)
			FREE_ARRAY (_hoops_PGSPS.flags, _hoops_CGSPS, _hoops_GHHPR);
		if (_hoops_PGSPS.colors != null)
			FREE_ARRAY (_hoops_PGSPS.colors, _hoops_CGSPS, RGB);
		if (_hoops_PGSPS.findices != null)
			FREE_ARRAY (_hoops_PGSPS.findices, _hoops_CGSPS, _hoops_ACGHR);
		if (_hoops_PGSPS._hoops_AHHIR != null)
			FREE_ARRAY (_hoops_PGSPS._hoops_AHHIR, _hoops_CGSPS, unsigned char);
		if (_hoops_PGSPS.weights != null)
			FREE_ARRAY (_hoops_PGSPS.weights, _hoops_CGSPS, float);
		if (_hoops_PGSPS.normals != null)
			FREE_ARRAY (_hoops_PGSPS.normals, _hoops_CGSPS, Vector);
	}

	_hoops_SPHPR->_hoops_GSAPA = true;

	if (_hoops_ARPGR != null)
		_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
}


#ifndef DISABLE_GEOMETRY_EDIT

local void _hoops_GASPS (
	Shell *							_hoops_SPHPR,
	int *							mapping,
	int								_hoops_AAAHA) {
	Local_Vertex_Attributes *		_hoops_SPRI = &_hoops_SPHPR->local_vertex_attributes;
	int								_hoops_CACPS = _hoops_SPHPR->point_count;
	Local_Vertex_Flags *			_hoops_ICRRH = null;
	RGB *							_hoops_CPCPS = null;
	RGB *							_hoops_RHCPS = null;
	RGB *							_hoops_HHCPS = null;
	_hoops_ACGHR *				_hoops_SHCPS = null;
	_hoops_ACGHR *				_hoops_AICPS = null;
	_hoops_ACGHR *				_hoops_IICPS = null;
	float *							_hoops_GCCPS = null;
	unsigned char *					_hoops_PCCPS = null;
	Vector *						_hoops_RSCRA = null;
	_hoops_RSSH *						_hoops_RPHCP = null;
	int								param_width = _hoops_SPRI->param_width;
	int								i;

	if (_hoops_SPRI->flags != null)
		ALLOC_ARRAY (_hoops_ICRRH,		_hoops_AAAHA, Local_Vertex_Flags);
	if (_hoops_SPRI->_hoops_PAHIR != null)
		ALLOC_ARRAY (_hoops_CPCPS,	_hoops_AAAHA, RGB);
	if (_hoops_SPRI->ecolors != null)
		ALLOC_ARRAY (_hoops_RHCPS,	_hoops_AAAHA, RGB);
	if (_hoops_SPRI->fcolors != null)
		ALLOC_ARRAY (_hoops_HHCPS,	_hoops_AAAHA, RGB);
	if (_hoops_SPRI->_hoops_HAHIR != null)
		ALLOC_ARRAY (_hoops_SHCPS, _hoops_AAAHA, _hoops_ACGHR);
	if (_hoops_SPRI->_hoops_HGHIR != null)
		ALLOC_ARRAY (_hoops_AICPS, _hoops_AAAHA, _hoops_ACGHR);
	if (_hoops_SPRI->_hoops_IGHIR != null)
		ALLOC_ARRAY (_hoops_IICPS, _hoops_AAAHA, _hoops_ACGHR);
	if (_hoops_SPRI->_hoops_CAHIR != null)
		ALLOC_ARRAY (_hoops_GCCPS,		_hoops_AAAHA, float);
	if (_hoops_SPRI->_hoops_SAHIR != null)
		ALLOC_ARRAY (_hoops_PCCPS,	_hoops_AAAHA, unsigned char);
	if (_hoops_SPRI->normals != null)
		ALLOC_ARRAY (_hoops_RSCRA,	_hoops_AAAHA, Vector);
	if (_hoops_SPRI->params != null)
		ALLOC_ARRAY (_hoops_RPHCP,	_hoops_AAAHA*param_width, _hoops_RSSH);

	for (i=0; i<_hoops_CACPS; i++) {
		int			_hoops_HGAHC = mapping[i];

		if (_hoops_HGAHC >= 0) {
			if (_hoops_SPRI->flags != null)
				_hoops_AIGA (&_hoops_SPRI->flags[i], 1, Local_Vertex_Flags, &_hoops_ICRRH[_hoops_HGAHC]);

			if (_hoops_SPRI->_hoops_PAHIR != null)
				_hoops_AIGA (&_hoops_SPRI->_hoops_PAHIR[i], 1, RGB, &_hoops_CPCPS[_hoops_HGAHC]);
			if (_hoops_SPRI->ecolors != null)
				_hoops_AIGA (&_hoops_SPRI->ecolors[i], 1, RGB, &_hoops_RHCPS[_hoops_HGAHC]);
			if (_hoops_SPRI->fcolors != null)
				_hoops_AIGA (&_hoops_SPRI->fcolors[i], 1, RGB, &_hoops_HHCPS[_hoops_HGAHC]);

			if (_hoops_SPRI->_hoops_HAHIR != null)
				_hoops_AIGA (&_hoops_SPRI->_hoops_HAHIR[i], 1, _hoops_ACGHR, &_hoops_SHCPS[_hoops_HGAHC]);
			if (_hoops_SPRI->_hoops_HGHIR != null)
				_hoops_AIGA (&_hoops_SPRI->_hoops_HGHIR[i], 1, _hoops_ACGHR, &_hoops_AICPS[_hoops_HGAHC]);
			if (_hoops_SPRI->_hoops_IGHIR != null)
				_hoops_AIGA (&_hoops_SPRI->_hoops_IGHIR[i], 1, _hoops_ACGHR, &_hoops_IICPS[_hoops_HGAHC]);

			if (_hoops_SPRI->_hoops_CAHIR != null)
				_hoops_AIGA (&_hoops_SPRI->_hoops_CAHIR[i], 1, float, &_hoops_GCCPS[_hoops_HGAHC]);
			if (_hoops_SPRI->_hoops_SAHIR != null)
				_hoops_AIGA (&_hoops_SPRI->_hoops_SAHIR[i], 1, unsigned char, &_hoops_PCCPS[_hoops_HGAHC]);

			if (_hoops_SPRI->normals != null)
				_hoops_AIGA (&_hoops_SPRI->normals[i], 1, Vector, &_hoops_RSCRA[_hoops_HGAHC]);

			if (_hoops_SPRI->params != null)
				_hoops_AIGA (&_hoops_SPRI->params[i*param_width], param_width, _hoops_RSSH, &_hoops_RPHCP[_hoops_HGAHC*param_width]);
		}
		else if (_hoops_SPRI->flags != null) {
			if (BIT (_hoops_SPRI->flags[i], _hoops_PHIAA))
				--_hoops_SPRI->_hoops_CPIAA;
			if (BIT (_hoops_SPRI->flags[i], _hoops_HHIAA))
				--_hoops_SPRI->_hoops_SIIPR;

			if (BIT (_hoops_SPRI->flags[i], _hoops_HCRRA))
				--_hoops_SPRI->_hoops_ICRRA;
			if (BIT (_hoops_SPRI->flags[i], _hoops_SIRRA))
				--_hoops_SPRI->_hoops_PCRRA;
			if (BIT (_hoops_SPRI->flags[i], _hoops_CCRRA))
				--_hoops_SPRI->_hoops_HIRRA;

			if (BIT (_hoops_SPRI->flags[i], _hoops_PPHPR))
				--_hoops_SPRI->_hoops_SCHPR;
			if (BIT (_hoops_SPRI->flags[i], _hoops_RPHPR))
				--_hoops_SPRI->_hoops_CCHPR;

			if (BIT (_hoops_SPRI->flags[i], _hoops_AARHR))
				--_hoops_SPRI->_hoops_RCRHR;
			if (BIT (_hoops_SPRI->flags[i], _hoops_HARHR))
				--_hoops_SPRI->_hoops_SIRHR;

			if (BIT (_hoops_SPRI->flags[i], _hoops_GCICA))
				--_hoops_SPRI->_hoops_SCHHC;

			if (BIT (_hoops_SPRI->flags[i], _hoops_SIICA)) {
				Polyhedron *		_hoops_HPGPR = (Polyhedron *)_hoops_SPHPR;
				_hoops_RPHIR *		_hoops_GARSA;
				unsigned char		symbol;

				symbol = _hoops_SPRI->_hoops_SAHIR[i];
				_hoops_GARSA = HI_LVA_Symbol_Lookup (_hoops_HPGPR, symbol);
				if (_hoops_ISAI(_hoops_GARSA) == 0)
					HI_LVA_Symbol_Delete (_hoops_HPGPR, _hoops_GARSA);

				--_hoops_SPRI->_hoops_AHIIC;
			}

			if (BIT (_hoops_SPRI->flags[i], LVA_EXPLICIT_NORMAL))
				--_hoops_SPRI->explicit_normal_count;

			if (BIT (_hoops_SPRI->flags[i], _hoops_ASAPA))
				--_hoops_SPRI->_hoops_RSAPA;
		}
	}


	if (_hoops_SPRI->flags != null)
		FREE_ARRAY (_hoops_SPRI->flags, _hoops_CACPS, Local_Vertex_Flags);
	if (_hoops_SPRI->_hoops_PAHIR != null)
		FREE_ARRAY (_hoops_SPRI->_hoops_PAHIR, _hoops_CACPS, RGB);
	if (_hoops_SPRI->ecolors != null)
		FREE_ARRAY (_hoops_SPRI->ecolors, _hoops_CACPS, RGB);
	if (_hoops_SPRI->fcolors != null)
		FREE_ARRAY (_hoops_SPRI->fcolors, _hoops_CACPS, RGB);
	if (_hoops_SPRI->_hoops_HAHIR != null)
		FREE_ARRAY (_hoops_SPRI->_hoops_HAHIR, _hoops_CACPS, _hoops_ACGHR);
	if (_hoops_SPRI->_hoops_HGHIR != null)
		FREE_ARRAY (_hoops_SPRI->_hoops_HGHIR, _hoops_CACPS, _hoops_ACGHR);
	if (_hoops_SPRI->_hoops_IGHIR != null)
		FREE_ARRAY (_hoops_SPRI->_hoops_IGHIR, _hoops_CACPS, _hoops_ACGHR);
	if (_hoops_SPRI->_hoops_IAHIR != null) {
		FREE_ARRAY (_hoops_SPRI->_hoops_IAHIR, _hoops_CACPS, RGBAS32);
	}
	if (_hoops_SPRI->_hoops_CAHIR != null) {
		FREE_ARRAY (_hoops_SPRI->_hoops_CAHIR, _hoops_CACPS, float);
		_hoops_SPRI->_hoops_CAHIR = _hoops_GCCPS;
		_hoops_SPRI->_hoops_SCHHC = _hoops_AAAHA;
	}
	if (_hoops_SPRI->_hoops_SAHIR != null) {
		FREE_ARRAY (_hoops_SPRI->_hoops_SAHIR, _hoops_CACPS, unsigned char);
		_hoops_SPRI->_hoops_SAHIR = _hoops_PCCPS;
		_hoops_SPRI->_hoops_AHIIC = _hoops_AAAHA;
	}
	if (_hoops_SPRI->normals != null) {
		FREE_ARRAY (_hoops_SPRI->normals, _hoops_CACPS, Vector);
		_hoops_SPRI->normals = _hoops_RSCRA;
		_hoops_SPRI->explicit_normal_count = _hoops_AAAHA;
	}
	if (_hoops_SPRI->params != null) {
		FREE_ARRAY (_hoops_SPRI->params, _hoops_CACPS*param_width, _hoops_RSSH);
		_hoops_SPRI->params = _hoops_RPHCP;
		_hoops_SPRI->_hoops_RSAPA = _hoops_AAAHA;
	}

	// _hoops_GIGHR: _hoops_PS _hoops_GHCA _hoops_RRP _hoops_IS _hoops_IHGC _hoops_ISIA _hoops_IH _hoops_AGCR _hoops_CSSC _hoops_GAR _hoops_PRAR.
	// _hoops_HHIGR _hoops_CSAP _hoops_HAR _hoops_SRAA _hoops_HPGR _hoops_RH _hoops_GHIR _hoops_IIGR _hoops_RGR _hoops_GIAR _hoops_PCPA _hoops_RH _hoops_AAH _hoops_PPRRR _hoops_IS _hoops_AA _hoops_SGS _hoops_CSAP.
	_hoops_SPRI->flags		 = _hoops_ICRRH;
	_hoops_SPRI->_hoops_PAHIR	 = _hoops_CPCPS;
	_hoops_SPRI->ecolors	 = _hoops_RHCPS;
	_hoops_SPRI->fcolors	 = _hoops_HHCPS;
	_hoops_SPRI->_hoops_HAHIR	 = _hoops_SHCPS;
	_hoops_SPRI->_hoops_HGHIR	 = _hoops_AICPS;
	_hoops_SPRI->_hoops_IGHIR	 = _hoops_IICPS;
}
#endif


GLOBAL_FUNCTION void HI_Edit_Shell_Points (
	_hoops_AIGPR *	_hoops_RIGC,
	Shell *					_hoops_SPHPR,
	int						ioffset,
	int						ndelete,
	int						insert,
	Point const *			points)
{
	_hoops_ICIIR(_hoops_RIGC);

HOOPS_WORLD->_hoops_RCHGI=1;	// _hoops_PGHGR _hoops_ACPC _hoops_APSA
	_hoops_RPPPR();
HOOPS_WORLD->_hoops_RCHGI=0;

	int	offset = ioffset;
	int	_hoops_CACPS;

	if (offset == -1)
		offset = _hoops_SPHPR->point_count;

	if (offset < 0 || ndelete < 0 || insert < 0) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_NUMBER,"The offset, delete count, or insertion count is negative");
		goto Release;
	}

	if (offset + ndelete > _hoops_SPHPR->point_count) {
		char			buf[MAX_ERRMSG];

		if (ioffset == -1)
			HE_ERROR (HEC_TRISTRIP, HES_INVALID_OFFSET,"Can't delete points after the end of the list (offset is -1)");
		else
			HE_ERROR2 (HEC_TRISTRIP, HES_INVALID_OFFSET,
					Sprintf_DD (null,"Can't delete/replace as many as %d points at offset %d -",ndelete, ioffset),
					   Sprintf_D (buf, "the shell only has %d", _hoops_SPHPR->point_count));
		goto Release;
	}

	if (ndelete == 0 && insert == 0)
		goto Release; /* _hoops_CPRSH */

	_hoops_CACPS = _hoops_SPHPR->point_count; /* _hoops_ASAC _hoops_RGR */

	if (ndelete == insert) {
		/* _hoops_CSASA, _hoops_RH _hoops_PIHGR _hoops_AGIR */
		_hoops_AIGA (points, insert, Point, &_hoops_SPHPR->points[offset]);
		/* _hoops_HCR _hoops_CPHR */
	}
	else {
		Point *				new_points;

		/* _hoops_SRS, _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_GII _hoops_RSSI _hoops_SGS _hoops_CGRPR _hoops_RSSA _hoops_IHGS _hoops_PGHPR */
		if (ndelete > 0 && _hoops_SPHPR->face_list_length > 0)
			_hoops_ARCPS (_hoops_RIGC, _hoops_SPHPR, offset, ndelete);

		/* _hoops_RPP (_hoops_IRRC(_hoops_RRCPR->_hoops_PHRHR, _hoops_CPSSI) ||
			 (!_hoops_IRRC(_hoops_RRCPR->_hoops_PHRHR, _hoops_CPSSI) && _hoops_RRCPR->_hoops_SPSSI._hoops_IIGCI != 0)) */
			HI_Adjust_Vertex_Attributes (_hoops_SPHPR, offset, ndelete, insert);

		if (_hoops_SPHPR->_hoops_HHHPR != null)
			HI_Adjust_Vertex_To_Edge (_hoops_SPHPR, offset, ndelete, insert);

		/* _hoops_RRP _hoops_IS _hoops_IPS _hoops_SCH _hoops_IS _hoops_CCAH _hoops_GC */

		if (_hoops_SPHPR->point_count - ndelete + insert > 0)
			ALLOC_ARRAY_ALIGNED (new_points, _hoops_SPHPR->point_count - ndelete + insert, Point, 16);
		else
			new_points = null;

		if (offset > 0)
			_hoops_AIGA (_hoops_SPHPR->points, offset, Point, new_points);

		if (insert > 0)
			_hoops_AIGA (points, insert, Point, new_points + offset);

		if (_hoops_SPHPR->point_count > offset + ndelete)
			_hoops_AIGA (_hoops_SPHPR->points + (offset + ndelete),
						 _hoops_SPHPR->point_count - (offset + ndelete),
						 Point,
						 new_points + (offset + insert));

		if (BIT (_hoops_SPHPR->polyhedron_flags, PHF_POINTS_BY_REFERENCE))
			_hoops_SPHPR->polyhedron_flags &= ~PHF_POINTS_BY_REFERENCE;
		else if (_hoops_SPHPR->points != null)
			FREE_ARRAY_ALIGNED (_hoops_SPHPR->points, _hoops_SPHPR->point_count, Point, 16);

		_hoops_SPHPR->points = new_points;
		_hoops_SPHPR->point_count += insert - ndelete;

		if (offset < _hoops_CACPS) {
			if (_hoops_SPHPR->face_list_length > 0) {
				/* _hoops_GHCA _hoops_RRP _hoops_IS _hoops_RCCGS _hoops_HHH _hoops_IIGR _hoops_RH _hoops_HHRPA _hoops_RSSI */

				int	*	item = _hoops_SPHPR->face_list;
				int *	end = item + _hoops_SPHPR->face_list_length;
				int		delta = insert - ndelete;

				do {
					int		*_hoops_CRRHR;

					if (*item++ >= 0)
						_hoops_CRRHR = item + item[-1];
					else
						_hoops_CRRHR = item - item[-1];

					if (item != _hoops_CRRHR) {
						do if (*item >= offset) *item += delta;
						_hoops_RGGA (++item == _hoops_CRRHR);
					}
				} _hoops_RGGA (item == end);
				_hoops_SPHPR->_hoops_ACRHR = 0; //_hoops_HHSA _hoops_RASPS (_hoops_PRGI _hoops_RPP _hoops_PSP _hoops_RASPS _hoops_GPP _hoops_IHCGP) _hoops_PGGA _hoops_PSPI _hoops_AGRP.
			}

			if (_hoops_SPHPR->_hoops_SPHA > 0) {
				/* _hoops_GHCA _hoops_RRP _hoops_IS _hoops_RCCGS _hoops_HHH _hoops_IIGR _hoops_RH _hoops_SPPR */

				_hoops_RHHPR*		_hoops_SRCPR = _hoops_SPHPR->_hoops_GRCPR;
				_hoops_RHHPR*		end = _hoops_SRCPR + _hoops_SPHPR->_hoops_SPHA;
				int						delta = insert - ndelete;

				do if (_hoops_SRCPR->_hoops_GIHPR >= offset) _hoops_SRCPR->_hoops_GIHPR += delta;
				_hoops_RGGA (++_hoops_SRCPR == end);
			}
		}

		/* _hoops_HHSA _hoops_IPGGR _hoops_IIGR _hoops_PSSI */
		_hoops_SPHPR->_hoops_AGRHR = false;
		_hoops_SPHPR->_hoops_RSHPR = false;
	}

	if (ndelete > 0) {
		_hoops_SPHPR->bounding = Bounding::Create(_hoops_SPHPR->point_count, _hoops_SPHPR->points);

		if (_hoops_SPHPR->owner)
			HI_Antiquate_Bounding (_hoops_SPHPR->owner, true);
	}
	else /* _hoops_RPP (_hoops_GSRGR > 0) */{
		if (_hoops_SPHPR->bounding == null)
			_hoops_SPHPR->bounding = Bounding::Create(insert, points);
		else
			_hoops_SPHPR->bounding.Merge (insert, points);

		if (_hoops_SPHPR->owner)
			HI_Propagate_Bounding (_hoops_RIGC, _hoops_SPHPR->owner, _hoops_SPHPR->bounding, null);
	}

	/*
	 * _hoops_AGIIP _hoops_RH _hoops_HHPH _hoops_IIGR _hoops_RSSI _hoops_SSCP _hoops_HGAS
	 */
	if (!_hoops_SPHPR->_hoops_ACRHR ||
		offset == _hoops_CACPS) {
		/* _hoops_IRAHR */
	}
	else if (BIT (HOOPS_WORLD->system_flags, _hoops_AGSPP)) {
		int *	item = _hoops_SPHPR->face_list;
		int *	end = item + _hoops_SPHPR->face_list_length;
		int		_hoops_AASPS = offset - ndelete + insert;

		/*
		 * _hoops_ISPR _hoops_GRR _hoops_HSP _hoops_IS _hoops_CACH _hoops_RPP _hoops_GII _hoops_IIGR _hoops_RGCI _hoops_RSSA _hoops_AAPR _hoops_PASPS;
		 * _hoops_GPGS _hoops_IRS _hoops_GPHA _hoops_GPP _hoops_CPHP _hoops_APPR _hoops_SGS _hoops_IRS _hoops_SPPSH _hoops_HSP
		 * _hoops_HGIIC _hoops_ASAR-_hoops_SGPHR.
		 */
		if (item == null) {
			HE_ERROR (HEC_MEMORY, HES_REBUILDING_TRISTRIP, "Tristrips require rebuilding but face list data has been discarded");
			goto Release;
		}
		else do {
			int *	_hoops_CRRHR;

			if (*item++ >= 0)
				_hoops_CRRHR = item + item[-1];
			else
				_hoops_CRRHR = item - item[-1];

			if (_hoops_CRRHR <= item + 3) {
				/* _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_SCPH (_hoops_PAR _hoops_HRHC) - _hoops_PSP _hoops_AGRP _hoops_SSRR */
				item = _hoops_CRRHR;
			}
			else {
				do if (*item >= offset && *item < _hoops_AASPS) {
					_hoops_SPHPR->_hoops_ACRHR = false;
					break;
				} _hoops_RGGA (++item == _hoops_CRRHR);
			}
		} _hoops_RGGA (item == end ||
				 !_hoops_SPHPR->_hoops_ACRHR);
	}


	if (!BIT (_hoops_SPHPR->_hoops_RRHH, _hoops_RSPCR) && insert > 0) {
		Point const *				pp = points;
		Point const *				pe = pp + insert;
		do if (pp->z != 0.0f) {
			_hoops_SPHPR->_hoops_RRHH |= _hoops_RSPCR;
			if (_hoops_SPHPR->owner && !BIT (_hoops_SPHPR->owner->_hoops_RCGC, _hoops_ASPCR))
				HI_Propagate_Maybes (_hoops_RIGC, _hoops_SPHPR->owner, _hoops_ASPCR);
			break;
		} _hoops_RGGA (++pp == pe);
	}

	/*
	 * _hoops_RHSGP _hoops_PIHA _hoops_SHH _hoops_HASPS _hoops_HCCPR _hoops_SSIA'_hoops_ASAR _hoops_HCR _hoops_GRGA _hoops_ARP
	 */
	if (_hoops_SPHPR->local_vertex_attributes.explicit_normal_count != _hoops_SPHPR->point_count)
		_hoops_SPHPR->polyhedron_flags &= ~PHF_VERTEX_NORMALS_VALID;

	if (_hoops_SPHPR->local_face_attributes.explicit_normal_count != _hoops_SPHPR->face_count)
		_hoops_SPHPR->polyhedron_flags &= ~PHF_FACE_NORMALS_VALID;

	_hoops_SPHPR->polyhedron_flags &= ~_hoops_ASAHR;

    HI_Invalidate_Display_Lists (_hoops_RIGC, _hoops_SPHPR);

	if (ndelete > 0)
		_hoops_SASIR (_hoops_RIGC, (Geometry *)_hoops_SPHPR,
			_hoops_AISSR|_hoops_CSCCA|_hoops_PISSR|_hoops_RPSIR);
	else /* _hoops_RPP (_hoops_GSRGR > 0) */
		_hoops_SASIR (_hoops_RIGC, (Geometry *)_hoops_SPHPR,
			_hoops_GPSIR|_hoops_CSCCA|_hoops_PISSR|_hoops_RPSIR);

Release:
	_hoops_IRRPR();
}

HC_INTERFACE void HC_CDECL HC_Edit_Shell_Points (
	Key					key,
	int					ioffset,
	int					ndelete,
	int					insert,
	Point const *		points)
{
	_hoops_PAPPR context("Edit_Shell_Points");

#ifdef DISABLE_GEOMETRY_EDIT
	_hoops_IRPPR ("Geometry Edit");
#else
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, key, _hoops_RSGPP)) != null) {
		HI_Edit_Shell_Points(context, (Shell *)target, ioffset, ndelete, insert, points);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		int		count2 = insert;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "HC_POINT * points = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", count2));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].x = %.6ff;	 ", count2, points[count2].x));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].y = %.6ff;	 ", count2, points[count2].y));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].z = %.6ff;\n", count2, points[count2].z));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Shell_Points (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, ", ioffset, ndelete));
		HI_Dump_Code (Sprintf_D (null, "%d, points);\n", insert));
		HI_Dump_Code ("free (points);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);
#endif
}


HC_INTERFACE void HC_CDECL HC_Delete_Specific_Shell_Points (
	Key					key,
	int					count,
	int const *			indices)
{
	_hoops_PAPPR context("Delete_Specific_Shell_Points");

#ifdef DISABLE_GEOMETRY_EDIT
	_hoops_IRPPR ("Geometry Edit");
#else
	CODE_GENERATION (
		int		count2 = count;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "int * indices = (int*) malloc(sizeof(int)*%d);\n", count2));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (Sprintf_DD (null, "indices[%d] = %d;\n", count2, indices[count2]));
		}
		HI_Dump_Code (Sprintf_LD (null, "Delete_Specific_Shell_Points (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_D (null, "%d, indices);\n", count));
		HI_Dump_Code ("free (indices);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);


	int	*	mapping = null;
	int		_hoops_CACPS = 0;

	_hoops_RPPPR();

	Shell *	_hoops_SPHPR = (Shell *)_hoops_RCSSR (context, key);

	if (_hoops_SPHPR == null || _hoops_SPHPR->type != _hoops_SCIP ||
		BIT (_hoops_SPHPR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_KEY,"Key does not refer to a valid shell");
		goto Release;
	}

	if (count < 0) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_NUMBER,"The count is negative");
		goto Release;
	}

	if (count == 0)
		goto Release; /* _hoops_CPRSH */

	/* _hoops_RIP _hoops_RSSA _hoops_PGAP _hoops_CHR _hoops_IS _hoops_SHH _hoops_PGHPR */
	_hoops_CACPS = _hoops_SPHPR->point_count;
	ZALLOC_ARRAY (mapping, _hoops_CACPS, int);

	for (int i=0; i<count; i++) {
		int			index = indices[i];

		if (index < 0) {
			HE_ERROR (HEC_TRISTRIP, HES_INVALID_OFFSET,
					   Sprintf_DD (null, "Invalid negative point offset %d at entry %d", index, i));
			goto Release;
		}
		else if (index >= _hoops_CACPS) {
			char			buf[MAX_ERRMSG];

			HE_ERROR2 (HEC_TRISTRIP, HES_INVALID_OFFSET,
					   Sprintf_DD (null, "Invalid point offset %d at entry %d -", index, i),
					   Sprintf_D (buf, "the shell only has %d points", _hoops_SPHPR->point_count));
			goto Release;
		}

		mapping[index] = -1;
	}

	/* _hoops_ARP _hoops_SIA _hoops_IH _hoops_HHRPA _hoops_RSSA _hoops_PPR _hoops_HGCR _hoops_HACH _hoops_PPSR _hoops_RPR */
	count = 0;
	for (int i=0; i<_hoops_CACPS; i++) {
		if (mapping[i] == 0)
			mapping[i] = count++;
	}

	{
		Point *				new_points;

		/* _hoops_SRS, _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_GII _hoops_RSSI _hoops_SGS _hoops_CGRPR _hoops_RSSA _hoops_IHGS _hoops_PGHPR */
		if (_hoops_SPHPR->face_list_length > 0)
			_hoops_GACPS (context, _hoops_SPHPR, mapping);

		if (_hoops_SPHPR->local_vertex_attributes.flags != null &&
			BIT(_hoops_SPHPR->polyhedron_flags, _hoops_CGRHR) ||
			!BIT(_hoops_SPHPR->polyhedron_flags, _hoops_CGRHR) &&
			_hoops_SPHPR->local_vertex_attributes._hoops_SGRHR != 0 ||
			_hoops_SPHPR->local_vertex_attributes.normals != null)
			_hoops_GASPS (_hoops_SPHPR, mapping, count);

		if (_hoops_SPHPR->_hoops_HHHPR != null)
			_hoops_IACPS (_hoops_SPHPR, mapping, count);

		/* _hoops_RRP _hoops_IS _hoops_IPS _hoops_SCH _hoops_IS _hoops_CCAH _hoops_GC */

		if (count > 0)
			ALLOC_ARRAY_ALIGNED (new_points, count, Point, 16);
		else
			new_points = null;

		for (int i=0; i<_hoops_CACPS; i++) {
			if (mapping[i] >= 0)
				new_points[mapping[i]] = _hoops_SPHPR->points[i];
		}

		if (BIT (_hoops_SPHPR->polyhedron_flags, PHF_POINTS_BY_REFERENCE))
			_hoops_SPHPR->polyhedron_flags &= ~PHF_POINTS_BY_REFERENCE;
		else if (_hoops_SPHPR->points != null)
			FREE_ARRAY_ALIGNED (_hoops_SPHPR->points, _hoops_SPHPR->point_count, Point, 16);

		_hoops_SPHPR->points = new_points;
		_hoops_SPHPR->point_count = count;

		if (_hoops_SPHPR->face_list_length > 0) {
			/* _hoops_GHCA _hoops_RRP _hoops_IS _hoops_RCCGS _hoops_HHH _hoops_IIGR _hoops_RH _hoops_HHRPA _hoops_RSSI */

			int *			item = _hoops_SPHPR->face_list;
			int *			end = item + _hoops_SPHPR->face_list_length;

			do {
				int		*_hoops_CRRHR;

				if (*item++ >= 0)
					_hoops_CRRHR = item + item[-1];
				else
					_hoops_CRRHR = item - item[-1];

				if (item != _hoops_CRRHR) {
					do *item = mapping[*item];
					_hoops_RGGA (++item == _hoops_CRRHR);
				}
			} _hoops_RGGA (item == end);
		}

		if (_hoops_SPHPR->_hoops_SPHA > 0) {
			/* _hoops_GHCA _hoops_RRP _hoops_IS _hoops_RCCGS _hoops_HHH _hoops_IIGR _hoops_RH _hoops_SPPR */

			_hoops_RHHPR	*_hoops_SRCPR = _hoops_SPHPR->_hoops_GRCPR,
												*end = _hoops_SRCPR + _hoops_SPHPR->_hoops_SPHA;

			do _hoops_SRCPR->_hoops_GIHPR = mapping[_hoops_SRCPR->_hoops_GIHPR];
			_hoops_RGGA (++_hoops_SRCPR == end);
		}

		/* _hoops_HHSA _hoops_IPGGR _hoops_IIGR _hoops_PSSI */
		_hoops_SPHPR->_hoops_AGRHR = false;
		_hoops_SPHPR->_hoops_RSHPR = false;
	}

	_hoops_SPHPR->bounding = Bounding::Create(_hoops_SPHPR->point_count, _hoops_SPHPR->points);

	/*
	 * _hoops_RHSGP _hoops_PIHA _hoops_SHH _hoops_HASPS _hoops_HCCPR _hoops_SSIA'_hoops_ASAR _hoops_HCR _hoops_GRGA _hoops_ARP
	 */
	if (_hoops_SPHPR->local_vertex_attributes.explicit_normal_count !=
		_hoops_SPHPR->point_count)
		_hoops_SPHPR->polyhedron_flags &= ~PHF_VERTEX_NORMALS_VALID;

	if (_hoops_SPHPR->local_face_attributes.explicit_normal_count !=
		_hoops_SPHPR->face_count)
		_hoops_SPHPR->polyhedron_flags &= ~PHF_FACE_NORMALS_VALID;

	HI_Invalidate_Display_Lists (context, _hoops_SPHPR);

	_hoops_SASIR (context, (Geometry *)_hoops_SPHPR,
		_hoops_AISSR|_hoops_CSCCA|_hoops_PISSR|_hoops_RPSIR);

  Release:
	if (mapping != null)
		FREE_ARRAY (mapping, _hoops_CACPS, int);

	_hoops_IRRPR();
#endif
}


struct _hoops_AAGPA {
	_hoops_AAGPA *		next;
	int					_hoops_GIHPR;
	_hoops_CGCPR		_hoops_SGCPR;
};


local int _hoops_PAGPA (
	int							point1,
	int							point2,
	int							face,
	_hoops_AAGPA **			_hoops_HHHPR)
{
	int							source;
	int							_hoops_GIHPR;
	_hoops_AAGPA *				_hoops_HAGPA;
	_hoops_AAGPA **			_hoops_ASRGR;

	if (point1 == point2)
		return 0;

	if (point1 < point2) {
		/* _hoops_GACPR _hoops_ISHA _hoops_IAGA _hoops_HII 1 _hoops_IS 2 */
		source		= point1;
		_hoops_GIHPR = point2;
	}
	else {
		/* _hoops_CPIHR _hoops_ISHA _hoops_IAGA _hoops_HII 2 _hoops_IS 1 */
		source		= point2;
		_hoops_GIHPR = point1;
	}

	_hoops_ASRGR = &_hoops_HHHPR[source];

	while (!((_hoops_HAGPA = *_hoops_ASRGR) == null || _hoops_HAGPA->_hoops_GIHPR >= _hoops_GIHPR))
		_hoops_ASRGR = &_hoops_HAGPA->next;

	if (_hoops_HAGPA != null && _hoops_HAGPA->_hoops_GIHPR == _hoops_GIHPR) {
		/* _hoops_GSGI _hoops_PCCP _hoops_APRS _hoops_SPR */
		if (_hoops_HAGPA->_hoops_SGCPR._hoops_AIIPR == face || _hoops_HAGPA->_hoops_SGCPR._hoops_HIIPR == face) {
			// _hoops_SSRS _hoops_ISHA _hoops_HII _hoops_PSHR _hoops_HSP?  _hoops_PAHH _hoops_IRS _hoops_ARHAR
		}
		else if (_hoops_HAGPA->_hoops_SGCPR._hoops_HIIPR == _hoops_PIIPR)
			_hoops_HAGPA->_hoops_SGCPR._hoops_HIIPR = face;
		else {
			_hoops_HAGPA->_hoops_SGCPR._hoops_HIIPR = _hoops_IAGPA;
		}
	}
	else {
		/* _hoops_HAR _hoops_GSGI - _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_ISHA */
		ALLOC (_hoops_HAGPA, _hoops_AAGPA);
		_hoops_HAGPA->next = *_hoops_ASRGR;
		*_hoops_ASRGR = _hoops_HAGPA;
		_hoops_HAGPA->_hoops_GIHPR = _hoops_GIHPR;
		_hoops_HAGPA->_hoops_SGCPR._hoops_AIIPR = face;
		_hoops_HAGPA->_hoops_SGCPR._hoops_HIIPR = _hoops_PIIPR;
		return 1;
	}

	return 0;
}

GLOBAL_FUNCTION void HI_Create_Shell_Edges (
	Shell *				_hoops_SPHPR,
	bool				_hoops_APCIH)
{
	_hoops_AAGPA **	_hoops_HHHPR;


	/*
	 * _hoops_SR'_hoops_ASAR _hoops_CPIC _hoops_IS _hoops_ARPR _hoops_IRS _hoops_CCHHR _hoops_HIGR _hoops_IIGR _hoops_PASPR _hoops_GIHA _hoops_IH
	 * _hoops_GRR _hoops_HCGP _hoops_GPHA, _hoops_PPR _hoops_PSCR _hoops_HPGR _hoops_RH _hoops_RSGR _hoops_SAGR _hoops_HCR _hoops_RH _hoops_CCHHR
	 * _hoops_CPCI _hoops_CRGR _hoops_IRS _hoops_RSRA _hoops_IPGPA-_hoops_RCPGR _hoops_CRPR.
	 */
	{
		_hoops_AAGPA **	_hoops_PPGPA;

		/*
		 * "+1" _hoops_PGGA _hoops_SR'_hoops_ASAR _hoops_CPIC _hoops_IS _hoops_SICR _hoops_RGR _hoops_CRPR _hoops_CRGR
		 * _hoops_RH _hoops_RRCPR->_hoops_RPGPA _hoops_CRPR _hoops_SPHR
		 */
		ZALLOC_ARRAY_CACHED (_hoops_PPGPA, _hoops_SPHPR->point_count + 1, _hoops_AAGPA *);
		_hoops_HHHPR = _hoops_PPGPA;
	}

	_hoops_SPHPR->_hoops_SPHA = 0;

	if (_hoops_SPHPR->face_list == null) {
		/* _hoops_HPCAR _hoops_RRCPR _hoops_CSAP _hoops_HCR _hoops_HIPH _hoops_PPR _hoops_ARPR _hoops_IASPS & _hoops_CASPS _hoops_HII _hoops_CCGI */
		Tristrip const *		ts;

		if ((ts = _hoops_SPHPR->tristrips) != null) do {
			int						_hoops_PHHA = ts->_hoops_PHHA;
			int *					lengths = ts->lengths;
			int *					vi = ts->_hoops_AIHA;
			int *					fi = ts->face_indices;
			int						face = -1;

			while (_hoops_PHHA-- > 0) {
				int						length = *lengths++;
				int						p1 = *vi++;
				int						p2 = *vi++;
				int						_hoops_IAPH;
				bool					_hoops_SICPR = false;

				if (length < 0) {		/* _hoops_HAHCP */
					length = -length;
					_hoops_SICPR = true;
				}
				length -= 2;

				if (fi) fi += 2;

				while (length-- > 0) {
					_hoops_IAPH = *vi++;
					if (fi)
						face = *fi++;
					else
						face++;

					if (p1 != p2 && p2 != _hoops_IAPH && _hoops_IAPH != p1) {
						_hoops_SPHPR->_hoops_SPHA += _hoops_PAGPA (p1, p2, face, _hoops_HHHPR);
						_hoops_SPHPR->_hoops_SPHA += _hoops_PAGPA (p1, _hoops_IAPH, face, _hoops_HHHPR);
						_hoops_SPHPR->_hoops_SPHA += _hoops_PAGPA (p2, _hoops_IAPH, face, _hoops_HHHPR);
					}

					if (!_hoops_SICPR)
						p1 = p2;
					p2 = _hoops_IAPH;
				}
			}
		} _hoops_RGGA ((ts = ts->next) == null);
	}
	else {
		int *		_hoops_ASPH = _hoops_SPHPR->face_list;
		int *		_hoops_HICPR = _hoops_ASPH + _hoops_SPHPR->face_list_length;
		int			face = -1;

		_hoops_RGGA (_hoops_ASPH == _hoops_HICPR) {
			int *	_hoops_CICPR;

			if (*_hoops_ASPH++ < 0)			/* (_hoops_RCCPR _hoops_GGR _hoops_RH _hoops_PGHC _hoops_HSP) */
				_hoops_CICPR = _hoops_ASPH - _hoops_ASPH[-1];
			else {						/* (_hoops_GSSR _hoops_CCAH _hoops_HSP) */
				_hoops_CICPR = _hoops_ASPH + _hoops_ASPH[-1];
				++face;
			}

			if (_hoops_ASPH != _hoops_CICPR) {
				int				_hoops_PICPR;
				int				_hoops_IICPR;
				int				_hoops_AICPR = 0;

				_hoops_PICPR = _hoops_IICPR = *_hoops_ASPH++;

				_hoops_PCCAR {
					if (_hoops_ASPH != _hoops_CICPR) {
						/* _hoops_GSSR _hoops_AGIR; _hoops_HGCR _hoops_SPS _hoops_GPHA */
						_hoops_AICPR = *_hoops_ASPH++;
					}
					else {
						/*
						 * _hoops_ARGAR _hoops_SCH _hoops_AARI _hoops_IS _hoops_RH _hoops_RSGI (_hoops_HCCPR
						 * _hoops_SR _hoops_PAR _hoops_RH _hoops_IPSP _hoops_AIAH _hoops_HS!)
						 */
						if (_hoops_AICPR == _hoops_IICPR) break;
						_hoops_AICPR = _hoops_IICPR;
					}

					_hoops_SPHPR->_hoops_SPHA += _hoops_PAGPA (_hoops_AICPR, _hoops_PICPR, face, _hoops_HHHPR);

					_hoops_PICPR = _hoops_AICPR;
				}
			}
		}
	}

	if (_hoops_APCIH && _hoops_SPHPR->_hoops_SPHA > 0) {
		_hoops_CGCPR *			_hoops_APGPA;
		_hoops_AAGPA *			_hoops_HAGPA;
		_hoops_AAGPA **		_hoops_PPGPA = _hoops_HHHPR;
		_hoops_AAGPA **		_hoops_HPGPA = _hoops_PPGPA + _hoops_SPHPR->point_count;

		ALLOC_ARRAY (_hoops_APGPA, _hoops_SPHPR->_hoops_SPHA, _hoops_CGCPR);
		_hoops_SPHPR->_hoops_SGCPR = _hoops_APGPA;

		do {
			/* _hoops_IH _hoops_GRR _hoops_AH _hoops_ISHA, _hoops_IPGPA _hoops_PRIA _hoops_RH _hoops_RSSI */
			if ((_hoops_HAGPA = *_hoops_PPGPA) != null) do {
				_hoops_APGPA->_hoops_AIIPR = _hoops_HAGPA->_hoops_SGCPR._hoops_AIIPR;
				_hoops_APGPA->_hoops_HIIPR = _hoops_HAGPA->_hoops_SGCPR._hoops_HIIPR;
				++_hoops_APGPA;
			} _hoops_RGGA ((_hoops_HAGPA = _hoops_HAGPA->next) == null);
		} _hoops_RGGA (++_hoops_PPGPA == _hoops_HPGPA);
	}

	/* _hoops_SASPS' _hoops_IS _hoops_SCH. */

	/*
	 * _hoops_IPCP _hoops_RPGPA _hoops_CRPR, _hoops_PHPC _hoops_IS _hoops_CCHHR _hoops_CPCI, _hoops_SAGGR
	 * _hoops_RPSGA _hoops_CRGR _hoops_RH _hoops_CACHR _hoops_SPR, _hoops_PHPC _hoops_IS _hoops_CRPR _hoops_AIRP.
	 *
	 * _hoops_HGI _hoops_HRGR, _hoops_IIGR _hoops_IPGAA, _hoops_PRGIR.
	 *
	 * _hoops_HGI _hoops_CRS _hoops_GACC _hoops_GPSPS _hoops_GAR _hoops_IRS _hoops_RIP _hoops_SGS _hoops_GISA-_hoops_PRCPR _hoops_SSCP _hoops_RPII
	 * _hoops_PIGS. (_hoops_GPGP _hoops_HASHR _hoops_ARAR _hoops_ASHS _hoops_GRS _hoops_SHH _hoops_AHHR; _hoops_HPPC-_hoops_IS-_hoops_IAS
	 * _hoops_PCIC _hoops_SGS _hoops_HPP _hoops_RGCI "_hoops_RPR+1".)
	 */

	if (sizeof(_hoops_AAGPA *) != sizeof(_hoops_RHHPR *))
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Oh drat");

	_hoops_SPHPR->_hoops_HHHPR = (_hoops_RHHPR **)_hoops_HHHPR;

	{
		_hoops_RHHPR *	_hoops_SRCPR; /* _hoops_RH _hoops_CPGPA _hoops_PIH */
		bool					_hoops_SPGPA	 = true;
		bool					_hoops_GHGPA = true;
		_hoops_AAGPA *			_hoops_HAGPA;
		_hoops_AAGPA **		_hoops_PPGPA = _hoops_HHHPR;
		_hoops_AAGPA **		_hoops_HPGPA = _hoops_PPGPA + _hoops_SPHPR->point_count;

		/* _hoops_AGGA _hoops_SAGR _hoops_RH _hoops_CCHHR _hoops_CPCI _hoops_CRGR _hoops_IRS _hoops_RSRA _hoops_CRPR */

		if (_hoops_SPHPR->_hoops_SPHA > 0) {
			ALLOC_ARRAY (_hoops_SRCPR, _hoops_SPHPR->_hoops_SPHA, _hoops_RHHPR);
			_hoops_SPHPR->_hoops_GRCPR = _hoops_SRCPR;
		}
		else
			_hoops_SPHPR->_hoops_GRCPR = _hoops_SRCPR = null;

		do {
			/* _hoops_HGCR _hoops_RH _hoops_CCHHR _hoops_HIGR _hoops_IIGR _hoops_AH _hoops_ISHA _hoops_SIHC */
			_hoops_HAGPA = *_hoops_PPGPA;

			/*
			 * _hoops_RHGPA _hoops_RIR-_hoops_HCGP-_hoops_GPHA _hoops_CRS _hoops_IS _hoops_PPSR _hoops_HPGR _hoops_RH _hoops_CACHR
			 * _hoops_PIH
			 */
			*(_hoops_RHHPR **)_hoops_PPGPA = _hoops_SRCPR;

			/*_hoops_IH _hoops_GRR _hoops_AH _hoops_ISHA, _hoops_IPGPA _hoops_PRIA _hoops_RH _hoops_GHSPR*/
			_hoops_RGGA (_hoops_HAGPA == null) {
				_hoops_AAGPA *	victim;

				/*
				 * _hoops_IPCP _hoops_RRCPR _hoops_HRGR _hoops_CAHC _hoops_CHGRR _hoops_HCR _hoops_SPPR _hoops_HS _hoops_HPGR _hoops_CHGC _hoops_PGCR _hoops_RSSI.
				 * _hoops_HHIGR _hoops_HRGR _hoops_AHGPA _hoops_CHGRR _hoops_GRR _hoops_ISHA _hoops_SSCP _hoops_PSP _hoops_RRI _hoops_HSAR _hoops_PGCR _hoops_RSSI.
				 */
				if (_hoops_HAGPA->_hoops_SGCPR._hoops_HIIPR == _hoops_PIIPR) _hoops_SPGPA = false;
				if (_hoops_HAGPA->_hoops_SGCPR._hoops_HIIPR == _hoops_IAGPA) _hoops_GHGPA = false;

				/* _hoops_IPS _hoops_RH _hoops_PHGPA */
				_hoops_SRCPR->_hoops_GIHPR = _hoops_HAGPA->_hoops_GIHPR;
				++_hoops_SRCPR;

				/* _hoops_IHSH _hoops_HPGR _hoops_RH _hoops_SPS _hoops_AH _hoops_PASPR _hoops_SIHC */
				victim = _hoops_HAGPA;
				_hoops_HAGPA = _hoops_HAGPA->next;
				FREE (victim, _hoops_AAGPA);
			}

			/* _hoops_CCGR _hoops_IIH _hoops_CHR _hoops_PSP _hoops_RRI _hoops_HCGP _hoops_GIHA */
		} _hoops_RGGA (++_hoops_PPGPA == _hoops_HPGPA);

		/* _hoops_CISA _hoops_GGR _hoops_RH _hoops_HACH (_hoops_SHCAR, _hoops_RSHS + 1) _hoops_RARP */
		*(_hoops_RHHPR **)_hoops_PPGPA = _hoops_SRCPR;


		_hoops_SPHPR->polyhedron_flags |= _hoops_PACPR | _hoops_HACPR;
		if (!_hoops_SPGPA) _hoops_SPHPR->polyhedron_flags &= ~_hoops_HACPR;

		_hoops_SPHPR->polyhedron_flags |= _hoops_IPSCC | _hoops_HPSCC;
		if (!_hoops_GHGPA) _hoops_SPHPR->polyhedron_flags &= ~_hoops_HPSCC;
	}
}




GLOBAL_FUNCTION bool HI_Validate_Face_List (
	int					point_count,
	int					face_list_length,
	int const *			face_list,
	int *				_hoops_AGSIH)
{
	int const *			item;
	int const *			_hoops_CRRHR;
	int const *			end;
	char				buf[MAX_ERRMSG];

	*_hoops_AGSIH = 0; /* _hoops_HIS _hoops_SGIP */

	if (face_list_length == 0)
		return true;

	if (face_list_length < 0) {
		HE_ERROR (HEC_FACE, HES_INVALID_LIST_LENGTH,"'face_list_length' is negative");
		return false;
	}

	item = face_list;
	end = item + face_list_length;

	/* _hoops_SRS _hoops_HSP _hoops_PIHA _hoops_SHH '_hoops_RPRHR' */
	if (*item < 0) {
		HE_ERROR (HEC_FACE, HES_INVALID_NUMBER,"Face list must not begin with a negative number");
		return false;
	}

	do {
		if (*item++ >= 0) {		/* _hoops_GSSR _hoops_RPRHR _hoops_HSP */
			_hoops_CRRHR = item + item[-1];
		}
		else {			/* '_hoops_HHHR' _hoops_HSP == _hoops_IRS _hoops_RCCPR _hoops_GGR _hoops_RH _hoops_CGHI _hoops_HSP */
			_hoops_CRRHR = item - item[-1];
			--*_hoops_AGSIH;
		}

		if (_hoops_CRRHR > end) {
			HE_ERROR2 (HEC_FACE, HES_INVALID_OFFSET,
					Sprintf_DD (null,"Face length %d found at offset %d in 'face_list'",item[-1], item - face_list - 1),
					   Sprintf_D (buf,"runs past total list length of %d",face_list_length));
			return false;
		}

		_hoops_RGGA (item == _hoops_CRRHR) {
			if (*item < 0) {
				HE_ERROR (HEC_FACE, HES_INVALID_INDEX,
						Sprintf_DD (null, "Negative index '%d' found at offset %d in 'face_list'", *item, item - face_list));
				return false;
			}

			if (*item++ >= point_count) {
				HE_ERROR2 (HEC_FACE, HES_INVALID_INDEX,
						Sprintf_DD (null, "Vertex index %d found at offset %d in 'face_list'", item[-1], item - face_list - 1),
						   Sprintf_D (buf, "runs past total point count of %d", point_count));
				return false;
			}
		}
		++*_hoops_AGSIH;
	}
	_hoops_RGGA (item == end);

	return true;
}




GLOBAL_FUNCTION _hoops_HHHIR * HI_LEA_Pattern_Lookup (
	Polyhedron const *	_hoops_IPRI,
	unsigned char		id)
{
#ifndef _hoops_RGIPR
	_hoops_RPGHR const *lea;
	_hoops_HHHIR *_hoops_IHHIR;

	lea = &_hoops_IPRI->_hoops_IHHPR;
	_hoops_IHHIR = lea->_hoops_PHHIR;

	while (_hoops_IHHIR) {
		if (_hoops_IHHIR->id == id)
			return _hoops_IHHIR;
		_hoops_IHHIR = _hoops_IHHIR->next;
	}
#endif
	return 0;
}

GLOBAL_FUNCTION _hoops_HHHIR * HI_LEA_Pattern_Init (
	Polyhedron *			_hoops_IPRI,
	_hoops_HCRPR const *			name)
{
#ifndef _hoops_RGIPR
	_hoops_RPGHR *	lea;
	_hoops_HHHIR *			_hoops_IHHIR;
	Integer32				key;
	char					_hoops_RPSPS;

	lea = &_hoops_IPRI->_hoops_IHHPR;

	_hoops_HCARA(*name,key);

	/* _hoops_HGCR _hoops_CCAH _hoops_CRSRR */
	if (lea->_hoops_PHHIR) {
		/* _hoops_ISPR _hoops_IH _hoops_PPGCI */
		_hoops_IHHIR = lea->_hoops_PHHIR;
		while (_hoops_IHHIR) {
			if (_hoops_IHHIR->key == key)
				if (_hoops_RAHSR (*name, _hoops_IHHIR->name))
					return _hoops_IHHIR;
			_hoops_IHHIR = _hoops_IHHIR->next;
		}

		_hoops_RPSPS = 0;
		for (int i=1; i<255; i++) {
			_hoops_IHHIR = lea->_hoops_PHHIR;
			while (_hoops_IHHIR) {
				if (_hoops_IHHIR->id == i)
					break;
				_hoops_IHHIR = _hoops_IHHIR->next;
			}
			if (_hoops_IHHIR == null || _hoops_IHHIR->id != i) {
				_hoops_RPSPS = i;
				break;
			}
		}

		if (_hoops_RPSPS == 0)
			return null;
	}
	else
		_hoops_RPSPS = 1;

	ALLOC (_hoops_IHHIR, _hoops_HHHIR);

	_hoops_IHHIR->_hoops_HSAI = 0;
	HI_Copy_Name(name, &_hoops_IHHIR->name);
	_hoops_IHHIR->key = key;
	_hoops_IHHIR->id = (char)_hoops_RPSPS;

	_hoops_IHHIR->next = lea->_hoops_PHHIR;
	lea->_hoops_PHHIR = _hoops_IHHIR;

	return _hoops_IHHIR;
#else
	return null;
#endif
}

GLOBAL_FUNCTION void HI_LEA_Pattern_Delete (
	Polyhedron	*_hoops_IPRI,
	_hoops_HHHIR	*pattern) {
#ifndef _hoops_RGIPR
	_hoops_RPGHR *lea;
	_hoops_HHHIR *_hoops_IHHIR;
	_hoops_HHHIR **_hoops_APSPS;

	lea = &_hoops_IPRI->_hoops_IHHPR;
	_hoops_IHHIR = lea->_hoops_PHHIR;
	_hoops_APSPS = &lea->_hoops_PHHIR;

	while (_hoops_IHHIR) {
		if (_hoops_IHHIR == pattern) {
			*_hoops_APSPS = _hoops_IHHIR->next;
			_hoops_RGAIR (_hoops_IHHIR->name);
			FREE (_hoops_IHHIR, _hoops_HHHIR);
			return;
		}
		_hoops_APSPS = &_hoops_IHHIR->next;
		_hoops_IHHIR = _hoops_IHHIR->next;
	}
#endif
}


GLOBAL_FUNCTION void HI_Initialize_Edge_Attributes (
	Polyhedron *			_hoops_IPRI,
	_hoops_GHHPR		which)
{
	int						count;

	switch (_hoops_IPRI->type) {
	  case _hoops_GSIP: {
	  }	  break;

	  case _hoops_SCIP: {
		  if (_hoops_IPRI->_hoops_SPHA < 0)
			  HI_Create_Shell_Edges ((Shell *)_hoops_IPRI, false);
	  }	  break;

	  default: {
		  _hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Doesn't have edges");
		  return;
	  } /* _hoops_IHSA; */
	}

	if ((count = _hoops_IPRI->_hoops_SPHA) == 0)
		return;

	if (_hoops_IPRI->_hoops_IHHPR.flags == null) {
		_hoops_GHHPR		*flags;
		_hoops_GHHPR		*_hoops_RSCPR;

		ALLOC_ARRAY (flags, count, _hoops_GHHPR);
		_hoops_IPRI->_hoops_IHHPR.flags = flags;
		_hoops_RSCPR = flags + count;

		do *flags = 0;
		while (++flags < _hoops_RSCPR);
	}
	else {
		_hoops_GHHPR		*flags;
		_hoops_GHHPR		*_hoops_RSCPR;
		_hoops_GHHPR		_hoops_PPSPS = ~which;

		flags = _hoops_IPRI->_hoops_IHHPR.flags;
		_hoops_RSCPR = flags + count;

		do *flags &= _hoops_PPSPS;
		while (++flags < _hoops_RSCPR);
	}

#ifndef _hoops_GCGHR
	if (BIT (which, _hoops_SSRRA)) {
		RGB					*color;
		RGB					*_hoops_HPSPS;

		ALLOC_ARRAY (color, count, RGB);
		_hoops_IPRI->_hoops_IHHPR.colors = color;
		_hoops_HPSPS = color + count;

		do *color = _hoops_GPSR::_hoops_RPSR;
		while (++color < _hoops_HPSPS);

		_hoops_IPRI->_hoops_IHHPR._hoops_HSRRA = 0;
	}

	if (BIT (which, _hoops_RPGI)) {
		_hoops_ACGHR	*findex;
		_hoops_ACGHR	*_hoops_IPSPS;

		ALLOC_ARRAY (findex, count, _hoops_ACGHR);
		_hoops_IPRI->_hoops_IHHPR.findices = findex;
		_hoops_IPSPS = findex + count;

		do *findex = 0.0f;
		while (++findex < _hoops_IPSPS);

		_hoops_IPRI->_hoops_IHHPR._hoops_PSRRA = 0;
	}
#endif

#ifndef _hoops_RGIPR
	if (BIT (which, _hoops_GPGI)) {
		unsigned char			*pattern;
		unsigned char			*_hoops_CPSPS;

		ALLOC_ARRAY (pattern, count, unsigned char);
		_hoops_IPRI->_hoops_IHHPR._hoops_AHHIR = pattern;
		_hoops_CPSPS = pattern + count;

		do *pattern = 0;
		while (++pattern < _hoops_CPSPS);

		_hoops_IPRI->_hoops_IHHPR._hoops_SRAPA = 0;
	}

	if (BIT (which, _hoops_SCICA)) {
		float					*weight;
		float					*_hoops_SPSPS;

		ALLOC_ARRAY (weight, count, float);
		_hoops_IPRI->_hoops_IHHPR.weights = weight;
		_hoops_SPSPS = weight + count;

		do *weight = 0.0f;
		while (++weight < _hoops_SPSPS);

		_hoops_IPRI->_hoops_IHHPR._hoops_CCHHC = 0;
	}
#endif

#ifndef _hoops_HCGHR
	if (BIT (which, _hoops_CRAHR)) {
		Vector				*normal;
		Vector				*_hoops_GHSPS;

		ALLOC_ARRAY (normal, count, Vector);
		_hoops_IPRI->_hoops_IHHPR.normals = normal;
		_hoops_GHSPS = normal + count;

		do normal->x = normal->y = normal->z = 0.0f;
		while (++normal < _hoops_GHSPS);

		_hoops_IPRI->_hoops_IHHPR.explicit_normal_count = 0;
	}
#endif
}



//_hoops_RAS _hoops_IRS _hoops_PPGAR _hoops_HCGI _hoops_CASRR, _hoops_SR _hoops_PAH _hoops_CHRI _hoops_PHPHA _hoops_GSSR _hoops_PIH, _hoops_CR _hoops_SCH'_hoops_GRI _hoops_GPP _hoops_RH _hoops_PGPRH _hoops_PPR _hoops_PAH _hoops_PHGCA
//_hoops_SHH _hoops_PCIRH _hoops_CGH _hoops_SR _hoops_SGIPR _hoops_HGAP _hoops_SCH _hoops_GICS.  _hoops_HHIGR _hoops_PAH'_hoops_RA _hoops_SHH _hoops_GGPS, _hoops_PHRI, _hoops_CCGR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_PCCP _hoops_PAAP, _hoops_CGPR
//_hoops_SR'_hoops_ASAR _hoops_RCRR _hoops_SGS _hoops_AGGCI _hoops_HRGR _hoops_CIGHR _hoops_GPP _hoops_IS _hoops_IRS _hoops_IPS.
GLOBAL_FUNCTION void HI_Flush_Derived_Normals (
	_hoops_AIGPR *	_hoops_RIGC,
	Polyhedron	alter *		_hoops_IPRI)
{
	_hoops_CRCP *	_hoops_ARPGR;
	if ((_hoops_ARPGR = _hoops_IPRI->owner) != null)
		_hoops_ARPGR->_hoops_RHAGR._hoops_PRPGR(_hoops_RIGC->thread_id);

	Local_Face_Attributes alter *_hoops_CPRI = (Local_Face_Attributes alter *) &_hoops_IPRI->local_face_attributes;
	Local_Vertex_Attributes alter *_hoops_SPRI = (Local_Vertex_Attributes alter *) &_hoops_IPRI->local_vertex_attributes;

	if (_hoops_CPRI->normals != null &&
		_hoops_CPRI->explicit_normal_count == 0) {
		FREE_ARRAY_ALIGNED (_hoops_CPRI->normals, _hoops_IPRI->face_count, _hoops_ARPA, 16);
		_hoops_CPRI->normals = null;
		_hoops_IPRI->polyhedron_flags &= ~(PHF_FACE_NORMALS_VALID|_hoops_ASAHR);
	}
	if (_hoops_SPRI->normals != null &&
		_hoops_SPRI->explicit_normal_count == 0) {
		int point_count = _hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR;
		FREE_ARRAY (_hoops_SPRI->normals, point_count, Vector);
		_hoops_SPRI->normals = null;
		_hoops_IPRI->polyhedron_flags &= ~(PHF_VERTEX_NORMALS_VALID|PHF_IMPLICIT_NORMALS_REVERSED);
	}

	if (_hoops_ARPGR != null)
		_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
}



GLOBAL_FUNCTION void HI_Initialize_Face_Attributes (
	Polyhedron *			_hoops_IPRI,
	_hoops_GIIPR		which)
{
	int						count;

	if ((count = _hoops_IPRI->face_count) == 0)
		return;

	if (_hoops_IPRI->local_face_attributes.flags == null) {
		_hoops_IPRI->local_face_attributes._hoops_SGRHR &= ~which;
	}
	else {
		_hoops_GIIPR		*flags;
		_hoops_GIIPR		*_hoops_RSCPR;
		_hoops_GIIPR		_hoops_PPSPS = ~which;

		flags = _hoops_IPRI->local_face_attributes._hoops_CHHPR();
		_hoops_RSCPR = flags + count;

		do *flags &= _hoops_PPSPS;
		_hoops_RGGA (++flags == _hoops_RSCPR);
	}

	if (BIT (which, LFA_EXPLICIT_COLOR_BY_VALUE)) {
		RGB					*color;

		ZALLOC_ARRAY (color, count, RGB);
		_hoops_IPRI->local_face_attributes.colors = color;
		_hoops_IPRI->local_face_attributes._hoops_HSRRA = 0;
	}

	if (BIT (which, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
		_hoops_ACGHR	*findex;

		ZALLOC_ARRAY (findex, count, _hoops_ACGHR);
		_hoops_IPRI->local_face_attributes.findices = findex;
		_hoops_IPRI->local_face_attributes._hoops_PSRRA = 0;
	}

	if (BIT (which, _hoops_HAGI)) {
		unsigned char			*pattern;

		ZALLOC_ARRAY (pattern, count, unsigned char);
		_hoops_IPRI->local_face_attributes._hoops_AHHIR = pattern;
		_hoops_IPRI->local_face_attributes._hoops_SRAPA = 0;
	}

	if (BIT (which, LFA_EXPLICIT_NORMAL)) {
		_hoops_ARPA						*normal;

		ALLOC_ARRAY_ALIGNED (normal, count, _hoops_ARPA, 16);
		SET_MEMORY (normal, count*sizeof(_hoops_ARPA), 0);
		_hoops_IPRI->local_face_attributes.normals = normal;
		_hoops_IPRI->local_face_attributes.explicit_normal_count = 0;
	}
}


GLOBAL_FUNCTION _hoops_RPHIR * HI_LVA_Symbol_Lookup (
	Polyhedron const *	_hoops_IPRI,
	unsigned char		id)
{
#ifndef _hoops_CSGHR
	Local_Vertex_Attributes const *_hoops_SPRI;
	_hoops_RPHIR *sl;

	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
	sl = _hoops_SPRI->_hoops_GPHIR;

	while (sl) {
		if (sl->id == id)
			return sl;
		sl = sl->next;
	}
#endif
	return 0;
}

GLOBAL_FUNCTION _hoops_RPHIR * HI_LVA_Symbol_Init (
	Polyhedron *				_hoops_IPRI,
	_hoops_HCRPR const *				name)
{
#ifndef _hoops_CSGHR
	Local_Vertex_Attributes *	_hoops_SPRI;
	_hoops_RPHIR *				sl;
	Integer32					key;
	char						_hoops_RPSPS;
	int							i;

	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

	_hoops_HCARA(*name,key);

	/* _hoops_HGCR _hoops_CCAH _hoops_CRSRR */
	if (_hoops_SPRI->_hoops_GPHIR) {
		/*_hoops_ISPR _hoops_IH _hoops_PPGCI*/
		sl = _hoops_SPRI->_hoops_GPHIR;
		while (sl) {
			if (sl->key == key)
				if (_hoops_RAHSR (*name, sl->name))
					return sl;
			sl = sl->next;
		}

		_hoops_RPSPS = 0;
		for (i=1; i<255; i++) {
			sl = _hoops_SPRI->_hoops_GPHIR;
			while (sl) {
				if (sl->id == i)
					break;
				sl = sl->next;
			}
			if (sl == null || sl->id != i) {
				_hoops_RPSPS=i;
				break;
			}
		}

		if (_hoops_RPSPS == 0)
			return null;
	}
	else
		_hoops_RPSPS = 1;

	ALLOC(sl, _hoops_RPHIR);

	sl->_hoops_HSAI = 0;
	HI_Copy_Name(name, &sl->name);
	sl->key = key;
	sl->id = (char)_hoops_RPSPS;

	sl->next = _hoops_SPRI->_hoops_GPHIR;
	_hoops_SPRI->_hoops_GPHIR = sl;

	return sl;
#else
	return null;
#endif
}

GLOBAL_FUNCTION void HI_LVA_Symbol_Delete (
	Polyhedron	*	_hoops_IPRI,
	_hoops_RPHIR	*	symbol)
{
#ifndef _hoops_CSGHR
	Local_Vertex_Attributes *_hoops_SPRI;
	_hoops_RPHIR *sl;
	_hoops_RPHIR **_hoops_SICRS;

	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
	sl = _hoops_SPRI->_hoops_GPHIR;
	_hoops_SICRS = &_hoops_SPRI->_hoops_GPHIR;

	while (sl) {
		if (sl == symbol) {
			*_hoops_SICRS = sl->next;
			_hoops_RGAIR(sl->name);
			FREE(sl, _hoops_RPHIR);
			return;
		}
		_hoops_SICRS = &sl->next;
		sl = sl->next;
	}
#endif
}



GLOBAL_FUNCTION void HI_Initialize_Vertex_Attributes (
	Polyhedron *		_hoops_IPRI,
	Local_Vertex_Flags	which,
	Integer32			data) {
	int					count;

	if ((count = _hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR) == 0)
		return;
#ifndef DISABLE_GEOMETRY_ATTRIBUTES
#ifndef _hoops_GCGHR
	/*_hoops_RPP (_hoops_CPHAR->_hoops_SPSSI._hoops_SGI == _hoops_IRAP) {
		_hoops_RHSPS	*_hoops_SGI;

		_hoops_AHSPS (_hoops_SGI, _hoops_RPR, _hoops_RHSPS);
		_hoops_CPHAR->_hoops_SPSSI._hoops_SGI = _hoops_SGI;
	}*/

	if (BIT (which, _hoops_HCRRA)) {
		RGB					*color;

		ZALLOC_ARRAY (color, count, RGB);
		_hoops_IPRI->local_vertex_attributes._hoops_PAHIR = color;

		_hoops_IPRI->local_vertex_attributes._hoops_ICRRA = 0;
	}

	if (BIT (which, _hoops_SIRRA)) {
		_hoops_ACGHR	*findex;

		ZALLOC_ARRAY (findex, count, _hoops_ACGHR);
		_hoops_IPRI->local_vertex_attributes._hoops_HAHIR = findex;

		_hoops_IPRI->local_vertex_attributes._hoops_PCRRA = 0;
	}

	if (BIT (which, _hoops_CCRRA)) {
		RGBAS32				*_hoops_PIHR;

		ZALLOC_ARRAY (_hoops_PIHR, count, RGBAS32);
		_hoops_IPRI->local_vertex_attributes._hoops_IAHIR = _hoops_PIHR;

		_hoops_IPRI->local_vertex_attributes._hoops_HIRRA = 0;
	}

	if (BIT (which, _hoops_PPHPR)) {
		RGB					*color;

		ZALLOC_ARRAY (color, count, RGB);
		_hoops_IPRI->local_vertex_attributes.ecolors = color;

		_hoops_IPRI->local_vertex_attributes._hoops_SCHPR = 0;
	}

	if (BIT (which, _hoops_RPHPR)) {
		_hoops_ACGHR	*findex;

		ZALLOC_ARRAY (findex, count, _hoops_ACGHR);
		_hoops_IPRI->local_vertex_attributes._hoops_HGHIR = findex;

		_hoops_IPRI->local_vertex_attributes._hoops_CCHPR = 0;
	}

	if (BIT (which, _hoops_AARHR)) {
		RGB					*color;

		ZALLOC_ARRAY (color, count, RGB);
		_hoops_IPRI->local_vertex_attributes.fcolors = color;

		_hoops_IPRI->local_vertex_attributes._hoops_RCRHR = 0;
	}

	if (BIT (which, _hoops_HARHR)) {
		_hoops_ACGHR	*findex;

		ZALLOC_ARRAY (findex, count, _hoops_ACGHR);
		_hoops_IPRI->local_vertex_attributes._hoops_IGHIR = findex;

		_hoops_IPRI->local_vertex_attributes._hoops_SIRHR = 0;
	}
#endif

	if (BIT (which, _hoops_GCICA)) {
		float					*size;

		ZALLOC_ARRAY (size, count, float);
		_hoops_IPRI->local_vertex_attributes._hoops_CAHIR = size;

		_hoops_IPRI->local_vertex_attributes._hoops_SCHHC = 0;
	}
#ifndef _hoops_CSGHR
	if (BIT (which, _hoops_SIICA)) {
		unsigned char			*symbol;

		ZALLOC_ARRAY (symbol, count, unsigned char);
		_hoops_IPRI->local_vertex_attributes._hoops_SAHIR = symbol;

		_hoops_IPRI->local_vertex_attributes._hoops_AHIIC = 0;
	}
#endif
#ifndef _hoops_HCGHR
	if (BIT (which, LVA_EXPLICIT_NORMAL)) {
		Vector						*normal;

		ZALLOC_ARRAY (normal, count, Vector);
		_hoops_IPRI->local_vertex_attributes.normals = normal;

		_hoops_IPRI->local_vertex_attributes.explicit_normal_count = 0;
	}
#endif
#ifndef DISABLE_TEXTURING
	if (BIT (which, _hoops_ASAPA)) {
		_hoops_RSSH	*params;
		_hoops_RSSH	*_hoops_ICCPS;
		Integer32	_hoops_PHSPS;
		Integer32	param_width = data;

		_hoops_ICCPS=_hoops_IPRI->local_vertex_attributes.params;
		_hoops_PHSPS=_hoops_IPRI->local_vertex_attributes.param_width;

		if (param_width <= _hoops_PHSPS)
			return;

		ALLOC_ARRAY (params, count*param_width, _hoops_RSSH);

		if (!_hoops_ICCPS) {
			_hoops_SRAGI(params, count, param_width);
			_hoops_IPRI->local_vertex_attributes._hoops_RSAPA=0;
		}
		else {
			int i,j;

			for (i=0; i<count; i++) {
				COPY_PARAMETER (&_hoops_ICCPS[i*_hoops_PHSPS], &params[i*param_width], _hoops_PHSPS);
				for (j=_hoops_PHSPS; j<param_width; j++) {
					params[i*param_width+j] = 0.0f;
				}
			}
			FREE_ARRAY (_hoops_ICCPS, count*_hoops_PHSPS, _hoops_RSSH);
		}

		_hoops_IPRI->local_vertex_attributes.params = params;
		_hoops_IPRI->local_vertex_attributes.param_width = param_width;
	}

	if (BIT (which, _hoops_CCCCC)) {
		_hoops_RSSH	*params;
		_hoops_RSSH	*_hoops_ICCPS;
		Integer32	_hoops_PHSPS;
		Integer32	param_width = data;

		_hoops_IPRI->local_vertex_attributes._hoops_SSCCC = 0;

		_hoops_ICCPS = _hoops_IPRI->local_vertex_attributes._hoops_PPHIR;
		_hoops_PHSPS = _hoops_IPRI->local_vertex_attributes._hoops_HPHIR;

		if (param_width == _hoops_PHSPS)
			return;

		if (_hoops_ICCPS)
			FREE_ARRAY (_hoops_ICCPS, count*_hoops_PHSPS, _hoops_RSSH);

		ALLOC_ARRAY (params, count*param_width, _hoops_RSSH);

		_hoops_SRAGI(params, count, param_width);

		_hoops_IPRI->local_vertex_attributes._hoops_PPHIR = params;
		_hoops_IPRI->local_vertex_attributes._hoops_HPHIR = param_width;
	}
#endif
#endif
}


GLOBAL_FUNCTION _hoops_AGHIR * HI_Initialize_PCA_Vertex_Attributes (
	PolyCylinder alter *			_hoops_HSPIR,
	_hoops_CGHIR				which) {
	_hoops_AGHIR *	_hoops_PGHIR;
	int								count;

	if ((count = _hoops_HSPIR->point_count) == 0)
		return null;

	if ((_hoops_PGHIR = _hoops_HSPIR->_hoops_RGHIR) == null) {
		ZALLOC (_hoops_PGHIR, _hoops_AGHIR);
		_hoops_HSPIR->_hoops_RGHIR = _hoops_PGHIR;
	}

	if (_hoops_PGHIR->flags == null) {
		_hoops_CGHIR		*flags;

		ZALLOC_ARRAY (flags, count, _hoops_CGHIR);
		_hoops_PGHIR->flags = flags;
	}

	if (BIT (which, _hoops_SHRRA)) {
		RGB					*color;

		ZALLOC_ARRAY (color, count, RGB);
		_hoops_PGHIR->ecolors = color;

		_hoops_PGHIR->_hoops_SCHPR = 0;
	}

	if (BIT (which, _hoops_IHRRA)) {
		_hoops_ACGHR	*findex;

		ZALLOC_ARRAY (findex, count, _hoops_ACGHR);
		_hoops_PGHIR->_hoops_HGHIR = findex;

		_hoops_PGHIR->_hoops_CCHPR = 0;
	}

	if (BIT (which, _hoops_GIRRA)) {
		RGB					*color;

		ZALLOC_ARRAY (color, count, RGB);
		_hoops_PGHIR->fcolors = color;

		_hoops_PGHIR->_hoops_RCRHR = 0;
	}

	if (BIT (which, _hoops_CHRRA)) {
		_hoops_ACGHR	*findex;

		ZALLOC_ARRAY (findex, count, _hoops_ACGHR);
		_hoops_PGHIR->_hoops_IGHIR = findex;

		_hoops_PGHIR->_hoops_SIRHR = 0;
	}

	return _hoops_PGHIR;
}




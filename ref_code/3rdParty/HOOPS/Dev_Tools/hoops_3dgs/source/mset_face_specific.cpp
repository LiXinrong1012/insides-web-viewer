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
 * $Id: obf_tmp.txt 1.16 2010-10-06 19:16:36 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


/* _hoops_PISGA _hoops_CRPR _hoops_CGH _hoops_PAHH _hoops_SHH _hoops_IRS _hoops_SCAH _hoops_GASR (_hoops_AHCII _hoops_GPP _hoops_RH _hoops_GPHA)*/

GLOBAL_FUNCTION int HI_Split_Point_Lookup (
	Polyhedron const *		_hoops_IPRI,
	int						vertex,
	int						face) {
	_hoops_CPHIR **		_hoops_HGIIR;
	_hoops_CPHIR *		vl;
	int						vcount;
	int						i;

	if (_hoops_IPRI == null)
		return vertex;

	if ((_hoops_HGIIR = _hoops_IPRI->local_vertex_attributes._hoops_RCIHR) == null)
		return vertex;	/* _hoops_PIRC _hoops_HHGP */
	if ((vl = _hoops_HGIIR[vertex]) == null)
		return vertex;	/* _hoops_RGR _hoops_SPR _hoops_HAR _hoops_HHGP */

	vcount = vl[0].face;
	for (i=1; i<=vcount; i++) {
		if (vl[i].face == face)
			return vl[i].vertex;
	}
	return -1;
}

GLOBAL_FUNCTION int HI_Split_Point_Original (
	Polyhedron const *		_hoops_IPRI,
	int						vertex) {
	int *					_hoops_HGIIR;

	if (_hoops_IPRI == null)
		return vertex;

	if (vertex < _hoops_IPRI->point_count)
		return vertex;

	_hoops_HGIIR = _hoops_IPRI->local_vertex_attributes._hoops_RHHIR;
	return _hoops_HGIIR[vertex - _hoops_IPRI->point_count];
}



local void _hoops_PHCII (
	_hoops_CPHIR **	_hoops_HGIIR,
	int					vertex,
	int					face) {
	_hoops_CPHIR *	vl;

	if ((vl = _hoops_HGIIR[vertex]) == null) {
		ZALLOC_ARRAY (vl, 2, _hoops_CPHIR);
		_hoops_HGIIR[vertex] = vl;
		vl[0].face = 1;	/* _hoops_RPR _hoops_IIGR _hoops_HISS _hoops_RSSI */
		vl[0].vertex = 1; /* _hoops_RPR _hoops_IIGR _hoops_PCIAR _hoops_HAR _hoops_GRGA _hoops_HHGP */
		vl[1].face = face; /* _hoops_SRS _hoops_HSP _hoops_HHCII */
		vl[1].vertex = vertex; /* _hoops_PPSR _hoops_ACAR _hoops_ISSC _hoops_IS _hoops_GIGR _hoops_CCGR _hoops_SCH _hoops_CPSA _hoops_ASIRA _hoops_PSAP*/
	}
	else {
		int		_hoops_IRCSA = vl[0].face;
		int		i;

		for (i=1; i<=_hoops_IRCSA; i++) {
			if (vl[i].face == face)
				return;	/* _hoops_AIAH _hoops_ACPA _hoops_IIGR _hoops_RGR _hoops_HSP */
		}
		/* _hoops_GGCR _hoops_HPIH */
		ZALLOC_ARRAY (vl, _hoops_IRCSA+2, _hoops_CPHIR);
		_hoops_AIGA (_hoops_HGIIR[vertex], _hoops_IRCSA+1, _hoops_CPHIR, vl);
		FREE_ARRAY (_hoops_HGIIR[vertex], _hoops_IRCSA+1, _hoops_CPHIR);
		_hoops_HGIIR[vertex] = vl;

		++vl[0].face;
		++vl[0].vertex;
		/* _hoops_HAS = _hoops_IHCII+1; */
		vl[i].face = face;
		vl[i].vertex = vertex;
		/* _hoops_CHCII _hoops_ISHP _hoops_IH _hoops_SHCAH */
		while (i > 1 && vl[i].face < vl[i-1].face) {
			int			tmp;

			tmp = vl[i].face;	vl[i].face = vl[i-1].face; vl[i-1].face = tmp;
			tmp = vl[i].vertex;	vl[i].vertex = vl[i-1].face; vl[i-1].vertex = tmp;
			--i;
		}
	}
}

local bool _hoops_SHCII (
	Polyhedron *				_hoops_IPRI,
	int							count,
	int const *					vertices,
	int const *					faces,
	Local_Vertex_Flags			_hoops_GICII) {
	Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
	Local_Vertex_Flags *		flags = _hoops_SPRI->_hoops_CHHPR();
	int							_hoops_RICII = _hoops_IPRI->point_count +
																_hoops_IPRI->_hoops_GCRHR;
	_hoops_CPHIR **			_hoops_HGIIR;
	bool *						_hoops_GHIAA;
	int *						mapping;
	int							_hoops_AICII;
	bool						_hoops_GAPCA = false;
	int							_hoops_RGCCA = 0;
	int							i;

	if (_hoops_IPRI->face_count <= 0) {
		/*_hoops_RIHH*/;
		return false;
	}

	ZALLOC_ARRAY (_hoops_GHIAA, _hoops_IPRI->point_count, bool);

	/* _hoops_CGIC _hoops_PGAP _hoops_RSSA _hoops_GHCA _hoops_RRP _hoops_HRHAR */
	for (i=0; i<count; i++) {
		int					index = vertices[i];

		if (index < 0 || index > _hoops_IPRI->point_count) {
			/*_hoops_RIHH*/;
			break;
		}
		if (faces[i] < 0 || faces[i] > _hoops_IPRI->face_count) {
			/*_hoops_RIHH*/;
			break;
		}

		_hoops_GHIAA[vertices[i]] = true;
	}
	if (_hoops_GAPCA) {
		FREE_ARRAY (_hoops_GHIAA, _hoops_IPRI->point_count, bool);
		return false;
	}

	if ((_hoops_HGIIR = _hoops_IPRI->local_vertex_attributes._hoops_RCIHR) == null) {
		ZALLOC_ARRAY (_hoops_HGIIR, _hoops_IPRI->point_count, _hoops_CPHIR *);
		_hoops_IPRI->local_vertex_attributes._hoops_RCIHR = _hoops_HGIIR;
	}

	/* _hoops_ARAS _hoops_RH _hoops_SCAPA _hoops_PAR _hoops_CCGI _hoops_IS _hoops_CGIC _hoops_PGAP _hoops_RSSI _hoops_PICII _hoops_IS _hoops_RSSA _hoops_SGS _hoops_RRP _hoops_HRHAR */

	if (_hoops_IPRI->type == _hoops_GSIP) {}
	else if (((Shell *)_hoops_IPRI)->face_list != null) {
		Shell *			_hoops_SPHPR = (Shell *)_hoops_IPRI;
		int const		*item,
						*_hoops_CRRHR,
						*end;
		int				face = 0;

		item = _hoops_SPHPR->face_list;
		end = item + _hoops_SPHPR->face_list_length;

		do {
			int				length = *item++;

			if (length < 0) {
				length = -length;
				--face;		/* _hoops_PAISR _hoops_RH _hoops_PGHC _hoops_GPISR */
			}
			_hoops_CRRHR = item + length;

			while (item != _hoops_CRRHR) {
				int			index = *item++;

				if (_hoops_GHIAA[index])
					_hoops_PHCII (_hoops_HGIIR, index, face);
			}

			++face;
		} while (item < end);
	}
	else if (_hoops_IPRI->tristrips != null) {
		Tristrip const *		ts = _hoops_IPRI->tristrips;
		int						face = -1;

		do {
			int						_hoops_PHHA = ts->_hoops_PHHA;
			int const *				lengths = ts->lengths;
			int const *				vi = ts->_hoops_AIHA;
			int const *				fi = ts->face_indices;

			while (_hoops_PHHA-- > 0) {
				int					length = *lengths++;
				int					_hoops_SICPR = false;
				bool			_hoops_AGRCA = false;
				int					_hoops_HSPI, _hoops_ISPI, _hoops_CSPI;

				if (length < 0) {
					length = -length;
					_hoops_SICPR = true;
				}

				_hoops_HSPI = *vi++;
				_hoops_ISPI = *vi++;

				if (fi != null)
					fi += 2;
				length -= 2;
				while (length-- > 0) {
					_hoops_CSPI = *vi++;
					if (fi != null)
						face = *fi++;
					else
						face++;

					if (_hoops_GHIAA[_hoops_HSPI])
						_hoops_PHCII (_hoops_HGIIR, _hoops_HSPI, face);
					if (_hoops_GHIAA[_hoops_ISPI])
						_hoops_PHCII (_hoops_HGIIR, _hoops_ISPI, face);
					if (_hoops_GHIAA[_hoops_CSPI])
						_hoops_PHCII (_hoops_HGIIR, _hoops_CSPI, face);


					if (!_hoops_SICPR) {
						_hoops_HSPI = _hoops_ISPI;
						_hoops_AGRCA = !_hoops_AGRCA;
					}
					_hoops_ISPI = _hoops_CSPI;
				}
			}
		} while ((ts = ts->next) != null);
	}

	FREE_ARRAY (_hoops_GHIAA, _hoops_IPRI->point_count, bool);

	/* _hoops_HA _hoops_ARAS _hoops_RH _hoops_SASI _hoops_RRGP _hoops_IS _hoops_CACH _hoops_PGAP _hoops_CPSA _hoops_HHGP _hoops_PPR _hoops_IPASR _hoops_CCAH _hoops_PSPI */
	_hoops_AICII = 1024;
	ALLOC_ARRAY (mapping, _hoops_AICII, int);
	while (count-- > 0) {
		int						vertex = *vertices++;
		int						face = *faces++;
		_hoops_CPHIR *		vl;
		int						vcount;

		vl = _hoops_HGIIR[vertex];
		vcount = vl[0].face;
		for (i=1; i<=vcount; i++) {
			if (vl[i].face == face) {
				/* _hoops_RGR _hoops_HRGR _hoops_RH _hoops_AGIR _hoops_SR _hoops_HHGC */
				if (vl[i].vertex == vertex) {
					/* _hoops_HAR _hoops_RRHSA _hoops_HHGP */
					if (--vl[0].vertex > 0) {	/* _hoops_GA'_hoops_RA _hoops_RRP _hoops_IRS _hoops_CIGGR _hoops_PPSR _hoops_RPP _hoops_RGR _hoops_HRGR _hoops_RH _hoops_CGHI _hoops_CGRPR */
						vl[i].vertex = _hoops_RICII + _hoops_RGCCA;
						if (_hoops_RGCCA == _hoops_AICII) {
							int *	_hoops_IPGSA = mapping;

							ALLOC_ARRAY (mapping, _hoops_AICII+1024, int);
							_hoops_AIGA (_hoops_IPGSA, _hoops_AICII, int, mapping);
							FREE_ARRAY (_hoops_IPGSA, _hoops_AICII, int);
							_hoops_AICII += 1024;
						}
						mapping[_hoops_RGCCA] = vertex;
						++_hoops_RGCCA;
					}
				}
				break;
			}
		}
		if (i > vcount) {
			/*_hoops_ASRHR?*/
		}
	}

	/* _hoops_SIPHA _hoops_GII _hoops_GPHA-_hoops_PCPP _hoops_SIRGR _hoops_IHIA _hoops_CCA _hoops_RSSI, _hoops_IPS _hoops_PIH _hoops_CRGR _hoops_CCAH _hoops_GIHA */
	{
		Point *					points;

		ALLOC_ARRAY_ALIGNED (points, _hoops_RICII + _hoops_RGCCA, Point, 16);
		_hoops_AIGA (_hoops_IPRI->points, _hoops_RICII, Point, points);
		FREE_ARRAY_ALIGNED (_hoops_IPRI->points, _hoops_RICII, Point, 16);
		_hoops_IPRI->points = points;

		for (i=0; i<_hoops_RGCCA; i++)
			points[_hoops_RICII+i] = points[mapping[i]];
	}

	if(BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)){
		ALLOC_ARRAY (flags, _hoops_RICII + _hoops_RGCCA, Local_Vertex_Flags);
		_hoops_AIGA (_hoops_SPRI->flags, _hoops_RICII, Local_Vertex_Flags, flags);
		FREE_ARRAY (_hoops_SPRI->flags, _hoops_RICII, Local_Vertex_Flags);
		_hoops_SPRI->flags = flags;
		for (i=0; i<_hoops_RGCCA; i++)
			flags[_hoops_RICII+i] = flags[mapping[i]] |= _hoops_GICII;
	}
	else
		_hoops_SPRI->_hoops_SGRHR |= _hoops_GICII;


	if (_hoops_SPRI->normals != null) {
		Vector *					normals;

		ALLOC_ARRAY (normals, _hoops_RICII + _hoops_RGCCA, Vector);
		_hoops_AIGA (_hoops_SPRI->normals, _hoops_RICII, Vector, normals);
		FREE_ARRAY (_hoops_SPRI->normals, _hoops_RICII, Vector);
		_hoops_SPRI->normals = normals;

		for (i=0; i<_hoops_RGCCA; i++)
			normals[_hoops_RICII+i] = normals[mapping[i]];
	}

	if (_hoops_SPRI->fcolors != null) {
		RGB *					fcolors;

		ALLOC_ARRAY (fcolors, _hoops_RICII + _hoops_RGCCA, RGB);
		_hoops_AIGA (_hoops_SPRI->fcolors, _hoops_RICII, RGB, fcolors);
		FREE_ARRAY (_hoops_SPRI->fcolors, _hoops_RICII, RGB);
		_hoops_SPRI->fcolors = fcolors;

		for (i=0; i<_hoops_RGCCA; i++)
			fcolors[_hoops_RICII+i] = fcolors[mapping[i]];
	}

	if (_hoops_SPRI->_hoops_IGHIR != null) {
		_hoops_ACGHR *		_hoops_IGHIR;

		ALLOC_ARRAY (_hoops_IGHIR, _hoops_RICII + _hoops_RGCCA, _hoops_ACGHR);
		_hoops_AIGA (_hoops_SPRI->_hoops_IGHIR, _hoops_RICII, _hoops_ACGHR, _hoops_IGHIR);
		FREE_ARRAY (_hoops_SPRI->_hoops_IGHIR, _hoops_RICII, _hoops_ACGHR);
		_hoops_SPRI->_hoops_IGHIR = _hoops_IGHIR;

		for (i=0; i<_hoops_RGCCA; i++)
			_hoops_IGHIR[_hoops_RICII+i] = _hoops_IGHIR[mapping[i]];
	}

	if (_hoops_SPRI->params != null) {
		_hoops_RSSH *				params;
		int							param_width = _hoops_SPRI->param_width;

		ALLOC_ARRAY (params, (_hoops_RICII + _hoops_RGCCA) * param_width, _hoops_RSSH);
		_hoops_AIGA (_hoops_SPRI->params, _hoops_RICII * param_width, _hoops_RSSH, params);
		FREE_ARRAY (_hoops_SPRI->params, _hoops_RICII * param_width, _hoops_RSSH);
		_hoops_SPRI->params = params;

		for (i=0; i<_hoops_RGCCA; i++)
			_hoops_AIGA (&params[mapping[i] * param_width], param_width, int,
						&params[(_hoops_RICII+i) * param_width]);
	}

	FREE_ARRAY (mapping, _hoops_AICII, int);
	{
		int			_hoops_ACSAP = _hoops_IPRI->_hoops_GCRHR;
		int *		_hoops_HICII;

		ALLOC_ARRAY (_hoops_HICII, _hoops_ACSAP + _hoops_RGCCA, int);
		if (_hoops_IPRI->_hoops_GCRHR != 0) {
			_hoops_AIGA (_hoops_IPRI->local_vertex_attributes._hoops_RHHIR,
						_hoops_ACSAP, int, _hoops_HICII);
			FREE_ARRAY (_hoops_IPRI->local_vertex_attributes._hoops_RHHIR,
						_hoops_ACSAP, int);
		}
		_hoops_AIGA (mapping, _hoops_ACSAP, int, &_hoops_HICII[_hoops_ACSAP]);
		_hoops_IPRI->local_vertex_attributes._hoops_RHHIR = _hoops_HICII;
		
	}

	_hoops_IPRI->_hoops_GCRHR += _hoops_RGCCA;


	return true;
}


HC_INTERFACE void HC_MSet_Face_Spec_Vert_Normals (
	Key						key,
	int						count,
	int const *				vertices,
	int const *				faces,
	Point const *			_hoops_IICII) 
{
	_hoops_PAPPR context("MSet_Face_Specific_Vertex_Normals");

#ifdef _hoops_HCGHR
	_hoops_IRPPR ("Geometry Normals");
#else
	CODE_GENERATION (
		int		count2 = count;
		if (count == 0) {
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Face_Specific_Vertex_Normals (LOOKUP (%D), 0, 0, 0, 0);\n", key));
		}
		else {
			HI_Dump_Code (Sprintf_D (null, "{int* vertices = (int*) malloc(sizeof(int)*%d);\n", count2));
			HI_Dump_Code (Sprintf_D (null, "int* faces = (int*) malloc(sizeof(int)*%d);\n", count2));
			HI_Dump_Code (Sprintf_D (null, "HC_POINT* normals = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", count2));
			++HOOPS_WORLD->_hoops_ISPPR;
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (Sprintf_DD (null, "vertices[%d].x = %d;\n", count2, vertices[count2]));
				HI_Dump_Code (Sprintf_DD (null, "faces[%d].x = %d;\n", count2, faces[count2]));
				HI_Dump_Code (_hoops_CHCHR (null, "normals[%d].x = %f;  ", count2, _hoops_IICII[count2].x));
				HI_Dump_Code (_hoops_CHCHR (null, "normals[%d].y = %f;  ", count2, _hoops_IICII[count2].y));
				HI_Dump_Code (_hoops_CHCHR (null, "normals[%d].z = %f;\n", count2, _hoops_IICII[count2].z));
			}
			HI_Dump_Code (Sprintf_LD (null, "HC_MSet_Face_Specific_Vertex_Normals (LOOKUP (%D), ", key));
			HI_Dump_Code (Sprintf_D (null, "%d, vertices, faces, normals);\n", count));
			HI_Dump_Code ("free (vertices);\n");
			HI_Dump_Code ("free (faces);\n");
			HI_Dump_Code ("free (normals);\n");
			--HOOPS_WORLD->_hoops_ISPPR;
			HI_Dump_Code ("}\n");
		}
	);

	if (count < 0) {
		HE_ERROR (HEC_MSET_VERTEX, HES_INVALID_COUNT, "Count is negative");
		return;
	}

	Polyhedron *	_hoops_IPRI;

	if ((_hoops_IPRI = (Polyhedron *)HI_Find_Target_And_Lock(context, key, _hoops_HCGPP)) == null)
		return;

	Vector const *	normals = (Vector const *)_hoops_IICII;

	if (_hoops_IPRI->local_vertex_attributes.normals == null)
		HI_Initialize_Vertex_Attributes (_hoops_IPRI, LVA_EXPLICIT_NORMAL, 0);

	_hoops_SHCII (_hoops_IPRI, count, vertices, faces, _hoops_CICII);
	Local_Vertex_Flags *	flags = _hoops_IPRI->local_vertex_attributes.flags;

	while (count-- > 0) {
		int	vertex = *vertices++;
		int	face = *faces++;
		
		if ((vertex = HI_Split_Point_Lookup (_hoops_IPRI, vertex, face)) >= 0) {

			if (!BIT (flags[vertex], LVA_EXPLICIT_NORMAL)) {
				flags[vertex] |= LVA_EXPLICIT_NORMAL;
				++_hoops_IPRI->local_vertex_attributes.explicit_normal_count;
			}

			Vector *	_hoops_AHAHR = &_hoops_IPRI->local_vertex_attributes.normals[vertex];
			*_hoops_AHAHR = *normals;

			if (!HI_Normalize (_hoops_AHAHR))
				HE_WARNING (HEC_NORMAL, HES_ZERO_LENGTH, "Normal vector is of zero or nearly zero length");
		}
		else {
			/*_hoops_ASRHR?*/
			ASSERT(0);
		}
	}

	_hoops_IRRPR();

#endif
}






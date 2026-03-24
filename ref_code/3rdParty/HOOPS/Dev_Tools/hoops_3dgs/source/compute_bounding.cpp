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
 * $Id: obf_tmp.txt 1.172 2010-10-06 19:15:52 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "searchh.h"
#include "please.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


struct _hoops_AGIAA {
	_hoops_AGIAA *		next;

	Geometry const *		geometry;
	_hoops_ISGI *		matrix;
	_hoops_PIGRA			locks;
	_hoops_ACHR				_hoops_RGP;
	bool					single;
};


struct _hoops_PGIAA {
	Bounding *				bounding;
	_hoops_AGIAA *		_hoops_ARGC;
	_hoops_ACHR				_hoops_RGP;
	_hoops_HGIAA				flags;
};

local int _hoops_IGIAA (
	Point const *		center,
	Vector const *		_hoops_GGHI,
	Vector const *		_hoops_RGHI,
	int					count,
	Point alter *		pl) {
	int					ii;

	if (count % 4 == 0) {
		int						count2 = count / 2;
		float					theta = 90.0f;
		float					delta = 360.0f / (float)count;

		ii = count2 / 2;
		do {
			float			s, t;
			float			_hoops_CGIAA;
			float			_hoops_SGIAA;
			Point alter	*_hoops_GGIAR = &pl[ii];
			Point alter	*p1 = &pl[count2-ii];
			Point alter	*p2 = &pl[count2+ii];
			Point alter	*_hoops_IAPH = &pl[count-ii];

			_hoops_RICH (theta, t, s);
			theta -= delta;

			_hoops_CGIAA = s * _hoops_GGHI->x;
			_hoops_SGIAA = t * _hoops_RGHI->x;
			_hoops_GGIAR->x = center->x + _hoops_CGIAA + _hoops_SGIAA;
			p1->x = center->x - _hoops_CGIAA + _hoops_SGIAA;
			p2->x = center->x - _hoops_CGIAA - _hoops_SGIAA;
			_hoops_IAPH->x = center->x + _hoops_CGIAA - _hoops_SGIAA;

			_hoops_CGIAA = s * _hoops_GGHI->y;
			_hoops_SGIAA = t * _hoops_RGHI->y;
			_hoops_GGIAR->y = center->y + _hoops_CGIAA + _hoops_SGIAA;
			p1->y = center->y - _hoops_CGIAA + _hoops_SGIAA;
			p2->y = center->y - _hoops_CGIAA - _hoops_SGIAA;
			_hoops_IAPH->y = center->y + _hoops_CGIAA - _hoops_SGIAA;

			_hoops_CGIAA = s * _hoops_GGHI->z;
			_hoops_SGIAA = t * _hoops_RGHI->z;
			_hoops_GGIAR->z = center->z + _hoops_CGIAA + _hoops_SGIAA;
			p1->z = center->z - _hoops_CGIAA + _hoops_SGIAA;
			p2->z = center->z - _hoops_CGIAA - _hoops_SGIAA;
			_hoops_IAPH->z = center->z + _hoops_CGIAA - _hoops_SGIAA;
		} while (ii-- != 0);
	}
	else {
		for (ii=0; ii<count; ii++) {
			float			s, t;

			_hoops_RICH (360.0f / (float)count, t, s);
			pl[ii].x = center->x + s * _hoops_GGHI->x + t * _hoops_RGHI->x;
			pl[ii].y = center->y + s * _hoops_GGHI->y + t * _hoops_RGHI->y;
			pl[ii].z = center->z + s * _hoops_GGHI->z + t * _hoops_RGHI->z;
		}
		pl[count].x = pl[0].x;
		pl[count].y = pl[0].y;
		pl[count].z = pl[0].z;
	}

	return count + 1;
}

GLOBAL_FUNCTION int HI_Generate_Elliptical_Points (
	_hoops_GHHI const *		curve,
	int						count,
	Point alter *			_hoops_IAIRA) {
	Point alter *			pl = _hoops_IAIRA;

	switch (curve->type) {
		case _hoops_SGCP:
		case _hoops_CGCP: {
			if (BIT(curve->_hoops_RRHH, _hoops_SHHI)) {
				Point				center;
				Vector				_hoops_GGHI, _hoops_RGHI;
				_hoops_AIHI const *	c;

				c = (_hoops_AIHI const *)curve;
				center.x = c->center.x;
				center.y = c->center.y;
				center.z = 0.0f;
				_hoops_GGHI.x = c->radius;
				_hoops_GGHI.y = 0.0f;
				_hoops_GGHI.z = 0.0f;
				_hoops_RGHI.x = 0.0f;
				_hoops_RGHI.y = c->radius;
				_hoops_RGHI.z = 0.0f;

				return _hoops_IGIAA (&center, &_hoops_GGHI, &_hoops_RGHI,
												 count, pl);
			}

			return _hoops_IGIAA (&curve->center,
											 &curve->_hoops_GGHI,
											 &curve->_hoops_RGHI,
											 count, pl);
		}	_hoops_HHHI;

		case _hoops_RIIP: {
			if (BIT (curve->_hoops_RRHH, _hoops_RGGGA)) {
				_hoops_SSSSR const *	a;

				a = (_hoops_SSSSR const *)curve;

				_hoops_AIGA (a->points, 3, Point, pl);
				return 3;
			}
			/* _hoops_IAII _hoops_HSSC _hoops_RHIR _hoops_IS _hoops_PHIGR _hoops_PGIS _hoops_AGIR */
		}	_hoops_HHHI;

		case _hoops_GRCP:
		case _hoops_RRCP:
		case _hoops_GIIP: {
			Elliptical_Arc const *	arc = (Elliptical_Arc const *)curve;
			Point const *			center;
			Vector const			*_hoops_GGHI, *_hoops_RGHI;
			Point					_hoops_GRIAA;
			Vector					_hoops_RRIAA, _hoops_ARIAA;
			float					start, end;
			float					s, t;

			if (BIT (arc->_hoops_RRHH, _hoops_SHHI)) {
				Circular_Arc_Lite const *	a;

				a = (Circular_Arc_Lite const *)arc;
				_hoops_GRIAA.x = a->center.x;
				_hoops_GRIAA.y = a->center.y;
				_hoops_GRIAA.z = 0.0f;
				_hoops_RRIAA.x = a->radius;
				_hoops_RRIAA.y = 0.0f;
				_hoops_RRIAA.z = 0.0f;
				_hoops_ARIAA.x = 0.0f;
				_hoops_ARIAA.y = a->radius;
				_hoops_ARIAA.z = 0.0f;
				center = &_hoops_GRIAA;
				_hoops_GGHI = &_hoops_RRIAA;
				_hoops_RGHI = &_hoops_ARIAA;
				start = a->arc_start;
				end = a->_hoops_PHHI;
			}
			else {
				center = &arc->center;
				_hoops_GGHI = &arc->_hoops_GGHI;
				_hoops_RGHI = &arc->_hoops_RGHI;
				start = arc->arc_start;
				end = arc->_hoops_PHHI;
				if (end < start)
					end += 1.0f;
			}

			if (start == 0.0f && end == 1.0f)
				return _hoops_IGIAA (center, _hoops_GGHI, _hoops_RGHI, count, pl);
			else {
				int				ii;
				float			theta;
				float			delta;

				if (curve->type == _hoops_RRCP) {
					pl->x = center->x;
					pl->y = center->y;
					pl->z = center->z;
					++pl;
				}

				theta = 360.0f * start;
				delta = 360.0f / (float)count;
				ii = (int)((float)count * Abs(end - start));

				if (arc->type != _hoops_GIIP &&
					!BIT (arc->_hoops_RRHH, _hoops_SHHI)) {
					Circular_Arc *		_hoops_PRIAA = (Circular_Arc *)curve;

					pl->x = _hoops_PRIAA->start.x;
					pl->y = _hoops_PRIAA->start.y;
					pl->z = _hoops_PRIAA->start.z;
					++pl;
					--ii; /* _hoops_ARR _hoops_IH _hoops_RGR _hoops_PPSR */
					--ii; /* _hoops_PPR _hoops_ARR _hoops_IS _hoops_HRIAA _hoops_IH _hoops_RH _hoops_RSGR _hoops_PPSR - _hoops_SPHR */
					theta += delta;
				}

				_hoops_RGGA (ii-- < 0) {
					_hoops_RICH (theta, t, s);
					pl->x = center->x + s * _hoops_GGHI->x + t * _hoops_RGHI->x;
					pl->y = center->y + s * _hoops_GGHI->y + t * _hoops_RGHI->y;
					pl->z = center->z + s * _hoops_GGHI->z + t * _hoops_RGHI->z;
					++pl;
					theta += delta;
				}

				if (curve->type != _hoops_GIIP &&
					!BIT (arc->_hoops_RRHH, _hoops_SHHI)) {
					Circular_Arc *		_hoops_PRIAA = (Circular_Arc *)curve;

					pl->x = _hoops_PRIAA->end.x;
					pl->y = _hoops_PRIAA->end.y;
					pl->z = _hoops_PRIAA->end.z;
					++pl;
				}
				else {
					_hoops_RICH (360.0f*end, t, s);
					pl->x = center->x + s * _hoops_GGHI->x + t * _hoops_RGHI->x;
					pl->y = center->y + s * _hoops_GGHI->y + t * _hoops_RGHI->y;
					pl->z = center->z + s * _hoops_GGHI->z + t * _hoops_RGHI->z;
					++pl;
				}

				return (pl - _hoops_IAIRA);
			}
		}	_hoops_HHHI;	/* _hoops_HCR _hoops_ARAR _hoops_ASRC */

		default:		/* _hoops_CGH _hoops_IIP _hoops_HGCR _hoops_ARI */
			break;
	}

	return 0;
}

GLOBAL_FUNCTION bool HI_Add_Geometry_Bounding (
	_hoops_AIGPR *		_hoops_RIGC,
	Geometry const *			geometry,
	_hoops_ISGI const *	matrix,
	_hoops_ACHR					_hoops_RGP,
	_hoops_PIGRA *			locks,
	_hoops_HGIAA					flags,
	Bounding alter &			bounding) {
	int							count;
	Point *						points = null;
	int							allocated = 0;
	int							_hoops_IRIAA = 0;

	switch (geometry->type) {
		case HK_STRING_CURSOR:
		case _hoops_GHPGR: {
			return false;
		}	_hoops_HHHI;

		case _hoops_HGPGR: {
			return true;
		}	_hoops_HHHI;

		case _hoops_RIIP:
		case _hoops_GIIP: {
			if (!BIT (_hoops_RGP, T_LINES))
				return true;

			if (BIT(flags, _hoops_CRIAA))
				allocated = 17;
			else
				allocated = 105;
			ALLOC_ARRAY_ALIGNED_CACHED (points, allocated, Point, 16);

			count = HI_Generate_Elliptical_Points ((_hoops_GHHI const *)geometry, allocated-5, points);
		}	break;

		case _hoops_SGCP:
		case _hoops_GRCP:
		case _hoops_RRCP:
		case _hoops_CGCP: {
			if (!ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE))
				return true;

			if (BIT(flags, _hoops_CRIAA))
				allocated = 17;
			else
				allocated = 105;
			ALLOC_ARRAY_ALIGNED_CACHED (points, allocated, Point, 16);

			count = HI_Generate_Elliptical_Points ((_hoops_GHHI const *)geometry, allocated-5, points);
		}		break;

		case _hoops_ASIP: {
			Cylinder const *		cylinder = (Cylinder const *)geometry;
			int						_hoops_SRIAA = 24;
			Vector					axis[2];

			if (!ANYBIT (_hoops_RGP, T_FACES|T_ANY_SHELL_EDGE))
				return true;

			if (BIT(flags, _hoops_CRIAA))
				_hoops_SRIAA = 12;

			allocated = count = _hoops_SRIAA * 2 + 1;

			ALLOC_ARRAY_ALIGNED_CACHED (points, allocated, Point, 16);

			axis[0].x = cylinder->_hoops_CSPIR.axis[0].x * cylinder->radius;
			axis[0].y = cylinder->_hoops_CSPIR.axis[0].y * cylinder->radius;
			axis[0].z = cylinder->_hoops_CSPIR.axis[0].z * cylinder->radius;
			axis[1].x = cylinder->_hoops_CSPIR.axis[1].x * cylinder->radius;
			axis[1].y = cylinder->_hoops_CSPIR.axis[1].y * cylinder->radius;
			axis[1].z = cylinder->_hoops_CSPIR.axis[1].z * cylinder->radius;


			_hoops_IGIAA (&cylinder->axis[0], &axis[0], &axis[1], _hoops_SRIAA, &points[0]);
			_hoops_IGIAA (&cylinder->axis[1], &axis[0], &axis[1], _hoops_SRIAA, &points[_hoops_SRIAA]);
		}	break;

		case _hoops_CSIP: {
			PolyCylinder const *	polycylinder= (PolyCylinder const *)geometry;
			int						_hoops_SRIAA = 24;

			if (!ANYBIT (_hoops_RGP, T_FACES|T_ANY_SHELL_EDGE))
				return true;

			if (BIT(flags, _hoops_CRIAA))
				_hoops_SRIAA = 12;

			allocated = count = _hoops_SRIAA * polycylinder->point_count + 1;

			ALLOC_ARRAY_ALIGNED_CACHED (points, count, Point, 16);

			for (int ii=0; ii<polycylinder->point_count; ii++) {
				Vector		axis[2];
				float			radius;

				radius = polycylinder->radii[ii % polycylinder->_hoops_ISPIR];

				axis[0].x = polycylinder->_hoops_CSPIR[ii].axis[0].x * radius;
				axis[0].y = polycylinder->_hoops_CSPIR[ii].axis[0].y * radius;
				axis[0].z = polycylinder->_hoops_CSPIR[ii].axis[0].z * radius;
				axis[1].x = polycylinder->_hoops_CSPIR[ii].axis[1].x * radius;
				axis[1].y = polycylinder->_hoops_CSPIR[ii].axis[1].y * radius;
				axis[1].z = polycylinder->_hoops_CSPIR[ii].axis[1].z * radius;

				_hoops_IGIAA (&polycylinder->points[ii], &axis[0], &axis[1], _hoops_SRIAA, &points[_hoops_SRIAA*ii]);
			}
		}	break;

		case _hoops_HSIP: {
			Sphere const *			sphere = (Sphere const *)geometry;
			Point *					p;
			float					radius = sphere->data.radius;

			if (!ANYBIT (_hoops_RGP, T_FACES|T_ANY_SHELL_EDGE))
				return true;

			allocated = count = 156;
			ALLOC_ARRAY_ALIGNED_CACHED (points, allocated, Point, 16);

			p = points;

			float const *			_hoops_GAIAA = HI_Get_Sin72_Lookup();
			float const *			_hoops_RAIAA = HI_Get_Cos72_Lookup();

			float const *			_hoops_AAIAA = _hoops_GAIAA;
			float const *			_hoops_PAIAA = _hoops_RAIAA;

			for (int j = 0; j <= 12; j++) {
				float				_hoops_HAIAA = *_hoops_AAIAA;
				float				_hoops_IAIAA = *_hoops_PAIAA;

				float const *		_hoops_CAIAA = _hoops_GAIAA;
				float const *		_hoops_SAIAA = _hoops_RAIAA;

				for (int i = 0; i < 12; i++) {
					float			_hoops_GPIAA = *_hoops_CAIAA;
					float			_hoops_RPIAA = *_hoops_SAIAA;

					p->x = sphere->data.center.x + radius * _hoops_HAIAA * _hoops_RPIAA;
					p->y = sphere->data.center.y + radius * _hoops_IAIAA;
					p->z = sphere->data.center.z + radius * _hoops_HAIAA * _hoops_GPIAA;

					p++;
					_hoops_CAIAA += 6;
					_hoops_SAIAA += 6;
				}
				_hoops_AAIAA += 6;
				_hoops_PAIAA += 6;
			}
		}	break;


		case _hoops_SIIP: {
			_hoops_IRIAA |= Bounding_TRANSFORM_DEPENDENT;
			return true;
		} break;

		case _hoops_GGCP: {
			Grid const *			grid = (Grid const *)geometry;

			if (!ANYBIT (_hoops_RGP, T_FACES|T_ANY_GRID_EDGE|T_VERTICES))
				return true;

			if (grid->_hoops_APIAA == _hoops_PPIAA) {
				int					_hoops_AIGCR = Abs (grid->count1);
				int					_hoops_PIGCR = Abs (grid->count2);
				Vector				_hoops_ISPI, _hoops_CSPI;

				ALLOC_ARRAY_ALIGNED_CACHED (points, 4, Point, 16);
				count = allocated = 4;

				_hoops_ISPI.x = _hoops_AIGCR * grid->_hoops_GGHI.x;
				_hoops_ISPI.y = _hoops_AIGCR * grid->_hoops_GGHI.y;
				_hoops_ISPI.z = _hoops_AIGCR * grid->_hoops_GGHI.z;

				_hoops_CSPI.x = _hoops_PIGCR * grid->_hoops_RGHI.x;
				_hoops_CSPI.y = _hoops_PIGCR * grid->_hoops_RGHI.y;
				_hoops_CSPI.z = _hoops_PIGCR * grid->_hoops_RGHI.z;

				/* _hoops_SRS _hoops_ARP _hoops_GH _hoops_RSSA _hoops_HPIAA _hoops_RPRHR _hoops_ISIA */
				points[0].x = grid->origin.x;
				points[0].y = grid->origin.y;
				points[0].z = grid->origin.z;

				points[1].x = grid->origin.x + _hoops_ISPI.x;
				points[1].y = grid->origin.y + _hoops_ISPI.y;
				points[1].z = grid->origin.z + _hoops_ISPI.z;

				points[2].x = grid->origin.x + _hoops_CSPI.x;
				points[2].y = grid->origin.y + _hoops_CSPI.y;
				points[2].z = grid->origin.z + _hoops_CSPI.z;

				points[3].x = grid->origin.x + _hoops_ISPI.x + _hoops_CSPI.x;
				points[3].y = grid->origin.y + _hoops_ISPI.y + _hoops_CSPI.y;
				points[3].z = grid->origin.z + _hoops_ISPI.z + _hoops_CSPI.z;

				/* _hoops_HHHR _hoops_ISIA _hoops_GRS _hoops_SRPA 2 _hoops_IIGR _hoops_RH _hoops_RSSA */
				if (grid->count1 < 0) {
					points[0].x -= _hoops_ISPI.x;
					points[0].y -= _hoops_ISPI.y;
					points[0].z -= _hoops_ISPI.z;

					points[2].x -= _hoops_ISPI.x;
					points[2].y -= _hoops_ISPI.y;
					points[2].z -= _hoops_ISPI.z;
				}

				if (grid->count2 < 0) {
					points[0].x -= _hoops_CSPI.x;
					points[0].y -= _hoops_CSPI.y;
					points[0].z -= _hoops_CSPI.z;

					points[1].x -= _hoops_CSPI.x;
					points[1].y -= _hoops_CSPI.y;
					points[1].z -= _hoops_CSPI.z;
				}

				if (grid->count1 == 0 || grid->count2 == 0)
					_hoops_IRIAA |= Bounding_TRANSFORM_DEPENDENT;
			}
			else {
				int						_hoops_AIGCR = grid->count1,
										_hoops_PIGCR = grid->count2;
				float					start, end, _hoops_RAHCR, increment;
				float					_hoops_GGHCR, _hoops_AGHCR;
				Point *					pl;

				if (_hoops_PIGCR == 0) {
					start = 0.0f;
					end = 360.0f;
					_hoops_PIGCR = grid->_hoops_IPIAA - 1;
				}
				else if (_hoops_PIGCR > 0) {
					start = 0.0f;
					if (_hoops_PIGCR >= grid->_hoops_IPIAA) {
						end = 360.0f;
						_hoops_PIGCR = grid->_hoops_IPIAA - 1;
					}
					else
						end = _hoops_PIGCR * 360.0f / grid->_hoops_IPIAA;
				}
				else {
					_hoops_PIGCR *= -2;
					if (_hoops_PIGCR >= grid->_hoops_IPIAA) {
						start = 0.0f;
						end = 360.0f;
						_hoops_PIGCR = grid->_hoops_IPIAA - 1;
					}
					else {
						end = _hoops_PIGCR * 180.0f / grid->_hoops_IPIAA;
						start = -end;
					}
				}

				ALLOC_ARRAY_ALIGNED_CACHED (points, 64, Point, 16);
				allocated = 64;
				count = 0;

				pl = points;

				/* _hoops_SR _hoops_PAH _hoops_SHR _hoops_GCIS _hoops_RHCH */
				pl->x = grid->origin.x;
				pl->y = grid->origin.y;
				pl->z = grid->origin.z;
				++pl;

				_hoops_RAHCR = start;
				increment = 6.0f;
				do {
					_hoops_RICH (_hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR);
					pl->x = grid->origin.x +
							 _hoops_AIGCR * (_hoops_AGHCR * grid->_hoops_GGHI.x + _hoops_GGHCR * grid->_hoops_RGHI.x);
					pl->y = grid->origin.y +
							 _hoops_AIGCR * (_hoops_AGHCR * grid->_hoops_GGHI.y + _hoops_GGHCR * grid->_hoops_RGHI.y);
					pl->z = grid->origin.z +
							 _hoops_AIGCR * (_hoops_AGHCR * grid->_hoops_GGHI.z + _hoops_GGHCR * grid->_hoops_RGHI.z);
					++pl;
				} _hoops_RGGA ((_hoops_RAHCR += increment) >= end);

				_hoops_RICH (end, _hoops_GGHCR, _hoops_AGHCR);
				pl->x = grid->origin.x +
							_hoops_AIGCR * (_hoops_AGHCR * grid->_hoops_GGHI.x + _hoops_GGHCR * grid->_hoops_RGHI.x);
				pl->y = grid->origin.y +
							_hoops_AIGCR * (_hoops_AGHCR * grid->_hoops_GGHI.y + _hoops_GGHCR * grid->_hoops_RGHI.y);
				pl->z = grid->origin.z +
							_hoops_AIGCR * (_hoops_AGHCR * grid->_hoops_GGHI.z + _hoops_GGHCR * grid->_hoops_RGHI.z);
				++pl;

				count = pl - points;

				if (grid->count1 == 0)
					_hoops_IRIAA |= Bounding_TRANSFORM_DEPENDENT;
			}
		}	break;


		case _hoops_HGCP: {
			if (!BIT (_hoops_RGP, T_IMAGES))
				return true;

			count = 1;
			points = (Point alter *)&((Image *)geometry)->_hoops_CSAI;
			_hoops_IRIAA |= _hoops_IGCIR;
		}	break;

		case _hoops_ICIP: {
			_hoops_SHPIR const			*light = (_hoops_SHPIR *)geometry;	// _hoops_RGAR _hoops_RRP _hoops_RCAHR _hoops_IH _hoops_CCAC _hoops_SS

			if (!ANYBIT (_hoops_RGP, T_ANY_LIGHTS))
				return true;

			if (light->_hoops_PRR != _hoops_S)
				return true;

			count = light->count;
			points = (Point alter *)light->points;
		}	break;

		case _hoops_PCIP: {
			if (!BIT (_hoops_RGP, T_MARKERS))
				return true;

			count = 1;
			points = (Point alter *)&((Marker *)geometry)->_hoops_CSAI;
		}	break;

		case _hoops_PIRS: {
			_hoops_GRPGR const *		_hoops_CPAI = (_hoops_GRPGR *)geometry;

			if (!BIT (_hoops_RGP, T_MARKERS))
				return true;

			if (_hoops_CPAI->count == 0)
				return true;

			count = _hoops_CPAI->count;
			points = (Point alter *)_hoops_CPAI->points;
		}	break;

		case _hoops_GSIP:
		case _hoops_SCIP: {
			Polyhedron const		*_hoops_IPRI = (Polyhedron *)geometry;

			if (!ANYBIT (_hoops_RGP, T_FACES|T_ANY_MESH_EDGE|T_VERTICES) &&
				_hoops_IPRI->local_face_attributes._hoops_CPIAA == 0 &&
				_hoops_IPRI->_hoops_IHHPR._hoops_CPIAA == 0 &&
				_hoops_IPRI->local_vertex_attributes._hoops_CPIAA == 0)
				return true;

			if (_hoops_IPRI->_hoops_HGAIR != null) {
				int i;
				Geometry *g;
				for (i = 0; i < _hoops_IGAIR; i++) {
					g = _hoops_IPRI->_hoops_HGAIR->data[i];
					while (g != null) {
						HI_Add_Geometry_Bounding (_hoops_RIGC, g, matrix, _hoops_RGP, locks, flags, bounding);
						g = g->next;
					}
				}
			}

			if (BIT(flags, _hoops_SPIAA)) {
				/* _hoops_HPPR _hoops_IS _hoops_CAHA _hoops_GGSR _hoops_PCPA _hoops_GRS _hoops_SHH _hoops_CHCC */
				if (BIT (_hoops_RGP, T_VERTICES) &&
					_hoops_IPRI->local_vertex_attributes._hoops_SIIPR == 0 ||
					_hoops_IPRI->local_vertex_attributes._hoops_CPIAA ==
																_hoops_IPRI->point_count) {
					/* _hoops_HCR _hoops_RSSA _hoops_CHR _hoops_GGR _hoops_SGH _hoops_GAR _hoops_GPHA _hoops_SAIA, _hoops_HIS _hoops_SR _hoops_PAH _hoops_HPRAR _hoops_IS _hoops_RH _hoops_GRAA-_hoops_AHSIR _hoops_AGIR */
				}
				else {
					bool		*_hoops_GHIAA;
					int				i;

					/* _hoops_RRP _hoops_IS _hoops_IHSH _hoops_RHIR _hoops_RH _hoops_IIRGR _hoops_IS _hoops_CACH _hoops_PGAP _hoops_RSSA _hoops_CHR _hoops_RHIAA */
					ZALLOC_ARRAY (_hoops_GHIAA, _hoops_IPRI->point_count, bool);

					count = 0;
					if (BIT (_hoops_RGP, T_FACES) ||
						_hoops_IPRI->local_face_attributes._hoops_CPIAA != 0) {
						if (_hoops_IPRI->tristrips != null) {
							Tristrip const *		ts;

							ts = _hoops_IPRI->tristrips;
							do if (BIT (ts->face_attributes.flags, _hoops_IAGI) ||
								   BIT (_hoops_RGP, T_FACES) &&
								   !BIT (ts->face_attributes.flags, _hoops_HSIPR)) {
								int					total = ts->total;
								int const *			vi = ts->_hoops_AIHA;

								for (i=0; i<total; i++) {
									int				index = *vi++;

									index = HI_Split_Point_Original (_hoops_IPRI, index);
									if (!_hoops_GHIAA[index]) {
										_hoops_GHIAA[index] = true;
										++count;
									}
								}
							} while ((ts = ts->next) != null);
						}
						else if (_hoops_IPRI->type == _hoops_SCIP) {
							Shell *					_hoops_SPHPR = (Shell *)_hoops_IPRI;
							int const *				face_list;
							int const *				_hoops_CRRHR;
							int const *				global_end;
							int						index;
							int						face = -1;

							Local_Face_Attributes const * _hoops_CPRI = &_hoops_SPHPR->local_face_attributes;

							face_list = _hoops_SPHPR->face_list;
							global_end = face_list + _hoops_SPHPR->face_list_length;

							while (face_list != global_end) {
								index = *face_list++;
								if (index < 0)
									index = -index;
								else
									++face;
								_hoops_CRRHR = face_list + index;

								if (BIT (_hoops_RGP, T_FACES) && !BIT (*_hoops_CPRI->_hoops_CHHPR(face), _hoops_HSIPR) ||
									!BIT (_hoops_RGP, T_FACES) && BIT (*_hoops_CPRI->_hoops_CHHPR(face), _hoops_IAGI)) {
									while (face_list != _hoops_CRRHR) {
										index = *face_list++;

										if (!_hoops_GHIAA[index]) {
											_hoops_GHIAA[index] = true;
											++count;
										}
									}
								}
								else
									face_list = _hoops_CRRHR;
							}
						}
						else {
							_hoops_AIHPR *					_hoops_PIHPR = (_hoops_AIHPR *)_hoops_IPRI;
							int						rows = _hoops_PIHPR->rows;
							int						columns = _hoops_PIHPR->columns;
							int						face = 0;
							int						vertex = 0;

							Local_Face_Attributes const *_hoops_CPRI = &_hoops_PIHPR->local_face_attributes;

							--rows;	/* _hoops_HPPP _hoops_HPP _hoops_RPCPR _hoops_HAPHR _hoops_RRGI _hoops_RH _hoops_HSP _hoops_RRGP */
							while (rows-- > 0) {
								int				_hoops_HIHPR = columns-1;

								while (_hoops_HIHPR-- > 0) {	/* _hoops_PPR _hoops_IAPHR _hoops_IS _hoops_RH _hoops_RAAP */
									if (BIT (_hoops_RGP, T_FACES) && !BIT (*_hoops_CPRI->_hoops_CHHPR(face), _hoops_HSIPR) ||
										!BIT (_hoops_RGP, T_FACES) && BIT (*_hoops_CPRI->_hoops_CHHPR(face), _hoops_IAGI)) {
										if (!_hoops_GHIAA[vertex]) {			/* _hoops_GSSC _hoops_RAAP */
											_hoops_GHIAA[vertex] = true;
											++count;
										}
										if (!_hoops_GHIAA[vertex+1]) {		/* _hoops_GSSC _hoops_RPHR */
											_hoops_GHIAA[vertex+1] = true;
											++count;
										}
										if (!_hoops_GHIAA[vertex+columns]) {	/* _hoops_AAPA _hoops_RAAP */
											_hoops_GHIAA[vertex+columns] = true;
											++count;
										}
									}
									++face;

									if (BIT (_hoops_RGP, T_FACES) && !BIT (*_hoops_CPRI->_hoops_CHHPR(face), _hoops_HSIPR) ||
										!BIT (_hoops_RGP, T_FACES) && BIT (*_hoops_CPRI->_hoops_CHHPR(face), _hoops_IAGI)) {
										if (!_hoops_GHIAA[vertex+1]) {		/* _hoops_GSSC _hoops_RPHR */
											_hoops_GHIAA[vertex+1] = true;
											++count;
										}
										if (!_hoops_GHIAA[vertex+columns]) {	/* _hoops_AAPA _hoops_RAAP */
											_hoops_GHIAA[vertex+columns] = true;
											++count;
										}
										if (!_hoops_GHIAA[vertex+columns+1]) {			/* _hoops_AAPA _hoops_RPHR */
											_hoops_GHIAA[vertex+columns+1] = true;
											++count;
										}
									}
									++face;

									++vertex;	/* _hoops_CPHR _hoops_CCA _hoops_RGR _hoops_GPHA _hoops_PPR _hoops_RH _hoops_HSP _hoops_PSAI _hoops_ARRS & _hoops_RPHR _hoops_HII _hoops_SCH */
								}

								++vertex;	/* _hoops_HSGR _hoops_CGHI _hoops_GPHA _hoops_GPP _hoops_RGR _hoops_GAGHR */
							}
						}
					}
					if (count < _hoops_IPRI->point_count &&
						(ANYBIT (_hoops_RGP, T_EDGES) ||
						 _hoops_IPRI->_hoops_IHHPR._hoops_CPIAA != 0)) {
						if (_hoops_IPRI->_hoops_SHGPR != null) {
							Polyedge const *		pe;

							pe = _hoops_IPRI->_hoops_SHGPR;
							do if (BIT (pe->_hoops_PPGI.flags, _hoops_APGI) ||
								   BIT (_hoops_RGP, T_EDGES) &&
								   !BIT (pe->_hoops_PPGI.flags, _hoops_AHIAA)) {
								int					total = pe->total;
								int const *			vi = pe->_hoops_AIHA;

								for (i=0; i<total; i++) {
									int				index = *vi++;

									if (!_hoops_GHIAA[index]) {
										_hoops_GHIAA[index] = true;
										++count;
									}
								}
							} while ((pe = pe->next) != null);
						}
					}
					if (count < _hoops_IPRI->point_count &&
						BIT (_hoops_RGP, T_VERTICES)) {
						if (_hoops_IPRI->_hoops_GIGPR != null) {
							Polymarker const *		pm;

							pm = _hoops_IPRI->_hoops_GIGPR;
							do if (BIT (pm->_hoops_SACI.flags, _hoops_PHIAA) ||
								   BIT (_hoops_RGP, T_VERTICES) &&
								   !BIT (pm->_hoops_SACI.flags, _hoops_HHIAA)) {
								int					total = pm->length;
								int const *			vi = pm->_hoops_AIHA;

								for (i=0; i<total; i++) {
									int				index = *vi++;

									if (!_hoops_GHIAA[index]) {
										_hoops_GHIAA[index] = true;
										++count;
									}
								}
							} while ((pm = pm->next) != null);
						}
					}

					if (count < _hoops_IPRI->point_count) {	/* _hoops_HPGR _hoops_CHGC _hoops_SPR _hoops_PPRAR */
						allocated = _hoops_IPRI->point_count;
						ALLOC_ARRAY_ALIGNED_CACHED (points, allocated, Point, 16);

						count = 0;
						for (i=0; i<_hoops_IPRI->point_count; i++) {
							if (_hoops_GHIAA[i]) {
								points[count] = _hoops_IPRI->points[i];
								++count;
							}
						}
					}
					FREE_ARRAY (_hoops_GHIAA, _hoops_IPRI->point_count, bool);

					if (count < _hoops_IPRI->point_count)
						break;
					/* _hoops_SHS _hoops_HCR _hoops_RSSA _hoops_GGR _hoops_SGH _hoops_PPR _hoops_SR _hoops_PAH _hoops_HPRAR _hoops_RHIR _hoops_IS _hoops_RH _hoops_SHISR _hoops_CRAA */
					/* (_hoops_HIH _hoops_CASI _hoops_GH _hoops_ISCP _hoops_AH _hoops_CRPR) */
					if (allocated > 0)
						FREE_ARRAY_ALIGNED (points, allocated, Point, 16);
					allocated = 0;
					points = null;
				}
			}
			if (!bounding._hoops_HICAR() && !BIT(flags, _hoops_IHIAA) &&
				 (matrix == null ||
				  !ANYBIT (matrix->matrix._hoops_RAGR, ~(_hoops_CHCP|_hoops_PRICR)))) {

				/* _hoops_SR _hoops_PAH _hoops_PAIHR, _hoops_RH _hoops_CPHAR'_hoops_GRI _hoops_IASC _hoops_GRPC _hoops_CGH _hoops_AA */
				if (_hoops_IPRI->bounding._hoops_HICAR())
					return true;		/* _hoops_HIH _hoops_HSGR _hoops_PCCP _hoops_RHPA _hoops_IASC */

				points = (Point *)&_hoops_IPRI->bounding->cuboid.min;
				count = 2;
			}
			else {
				count = _hoops_IPRI->point_count;
				points = (Point alter *)_hoops_IPRI->points;
			}
		}  break;

		case _hoops_RCIP: {
			Polygon const *		polygon = (Polygon const *)geometry;

			if (!ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE))
				return true;

			count = polygon->count;
			points = (Point alter *)polygon->points;
		}	break;

		case _hoops_HIIP:
		case _hoops_IIIP: {
			Polyline const *		polyline = (Polyline *)geometry;

			if (!BIT (_hoops_RGP, T_LINES))
				return true;

			if (polyline->count == 0)
				return true;

			count = Abs(polyline->count);
			points = (Point alter *)polyline->points;
		}	break;

		case _hoops_PIIP: {
			Line const *		line = (Line *)geometry;

			if (!BIT (_hoops_RGP, T_LINES))
				return true;

			count = 2;
			points = (Point alter *)line->points;
		}	break;

		case _hoops_CHIP: {
#ifndef _hoops_CCPIR
			_hoops_PIRGR alter *		curve = (_hoops_PIRGR alter *) geometry;

			if (!BIT (_hoops_RGP, T_LINES))
				return true;

			if (BIT(flags, _hoops_SPIAA) ||
				curve->_hoops_RRHH & _hoops_CHIAA) {
				if (curve->polyline.points == null) {
					Polyline polyline;
					_hoops_PARC control;

					/* _hoops_ARP _hoops_GH _hoops_SHIR _hoops_HSH. */
					control._hoops_PPPI = 32;
					control._hoops_HPPI = 0;
					control._hoops_IPPI = 0;
					control._hoops_CPPI = 20;
					control._hoops_SPPI = 1;
					control._hoops_SAR = false;

					HI_Generate_NURBS_Polyline (curve, &control, null, &polyline, 0);

					if (polyline.points == null)
						return false;
					curve->polyline.points = polyline.points;
					curve->polyline.allocated = polyline.allocated;
					curve->polyline.count = polyline.count;
				}
				count = curve->polyline.count;
				points = (Point alter *)curve->polyline.points;
			}
			else {
				count = curve->control_point_count;
				points = (Point alter *)curve->control_points;
			}
#endif
		}	break;

		case _hoops_PRCP: {
#ifndef _hoops_GSPIR
			_hoops_APPGR alter *	surface = (_hoops_APPGR alter *) geometry;

			if (!ANYBIT (_hoops_RGP, T_FACES|T_ANY_SHELL_EDGE))
				return true;

			if (BIT(flags, _hoops_SPIAA) ||
				surface->_hoops_SHIAA & _hoops_GIIAA) {
				_hoops_SPAGR				_hoops_RIIAA (surface->_hoops_RHAGR, _hoops_RIGC->thread_id);

				if (surface->_hoops_IPRI == null) {
					_hoops_AIIAA configs = { 0, 0, 0, 0, 0, 0 };
					HI_Fake_NURBS_Surface_Configs (&configs);
					HI_Tessellate_NURBS_Surface (_hoops_RIGC, surface, &configs);
				}

				if (!bounding._hoops_HICAR() &&
					 (matrix == null ||
					  !ANYBIT (matrix->matrix._hoops_RAGR,
							   ~(_hoops_CHCP|_hoops_PRICR)))) {
					/* _hoops_SR _hoops_PAH _hoops_PAIHR, _hoops_RH _hoops_CPHAR'_hoops_GRI _hoops_IASC _hoops_GRPC _hoops_CGH _hoops_AA */
					if (surface->_hoops_IPRI->bounding._hoops_HICAR())
						return true;		/* _hoops_HIH _hoops_HSGR _hoops_PCCP _hoops_RHPA _hoops_IASC */

					points = (Point *)&surface->_hoops_IPRI->bounding->cuboid.min;
					count = 2;
				}
				else {
					count = surface->_hoops_IPRI->point_count;
					points = (Point alter *)surface->_hoops_IPRI->points;
				}
			}
			else {
				count = surface->n_u_vertices * surface->n_v_vertices;
				points = (Point alter *)surface->control_points;
			}
#endif
		}	break;

		case _hoops_AGCP: {
			if (!BIT (_hoops_RGP, T_TEXT))
				return true;

			count = 1;
			points = (Point alter *)&((_hoops_HACC const *)geometry)->_hoops_CSAI;
			_hoops_IRIAA |= _hoops_HGCIR;
		}	break;

		case _hoops_AHIP: {
			_hoops_PHIP const *	_hoops_RRA = (_hoops_PHIP const *)geometry;
			_hoops_ISGI *			_hoops_PIIAA = (_hoops_ISGI *)matrix;

			if (_hoops_PIIAA != null)
				_hoops_PRRH (_hoops_PIIAA);

			if (_hoops_RRA->_hoops_IPPGR != null) {
				if (!HI_Accumulate_Bounding_Attributes (_hoops_RRA->_hoops_IPPGR,
														&_hoops_PIIAA,
														&_hoops_RGP, locks, null, flags)) {
					/* _hoops_IASC->_hoops_SGI |= _hoops_HIIAA; */
					if (_hoops_PIIAA != null)
						_hoops_HPRH (_hoops_PIIAA);
					return true;
				}
				matrix = _hoops_PIIAA;
			}

			if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
				_hoops_CRCP const *				_hoops_SRCP = (_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0];

				if ((geometry = _hoops_SRCP->geometry) != null) do {
					HI_Add_Geometry_Bounding (_hoops_RIGC, geometry, matrix, _hoops_RGP, locks, flags, bounding);
				} while ((geometry = geometry->next) != null);
			}
			else {
				for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++) {
					geometry = (Geometry const *)_hoops_RRA->_hoops_IHIP[i];

					HI_Add_Geometry_Bounding (_hoops_RIGC, geometry, matrix, _hoops_RGP, locks, flags, bounding);
				}
			}

			if (_hoops_PIIAA != null)
				_hoops_HPRH (_hoops_PIIAA);

			/* _hoops_RGR _hoops_PAH _hoops_IHPS _hoops_RPP _hoops_RH _hoops_CGRPR _hoops_RSSA _hoops_RGAR _hoops_IS _hoops_CGSI _hoops_SIHH _hoops_IASC _hoops_SHHRR
			 * (_hoops_IH _hoops_PCAI, _hoops_IRS _hoops_CAGH _hoops_IIAAR _hoops_RGAR _hoops_SS _hoops_PAR _hoops_HPPA _hoops_GHC) */
			if (bounding._hoops_HICAR())
				return false;
			return true;
		}	_hoops_HHHI;

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unknown geometry type");
			return false;
		}	_hoops_HHHI;
	}

	if (bounding == null)
		bounding = Bounding::Create();

	if (count > 0) {
		if (matrix != null &&
			ANYBIT (matrix->matrix._hoops_RAGR, _hoops_CICH)) {
			Point const			*_hoops_HRRGA = points;

			if (allocated == 0) {		/* _hoops_PAH'_hoops_RA _hoops_IIIAA, _hoops_HGCR _hoops_IRHP _hoops_IIPR */
				ALLOC_ARRAY_ALIGNED_CACHED (points, count, Point, 16);
				allocated = count;
			}

			HI_Compute_Transformed_Points (count, _hoops_HRRGA,
											&matrix->matrix.elements[0][0],
											points);
		}

		bounding.Merge (count, points);
	}
	bounding->flags |= _hoops_IRIAA;

	if (allocated != 0)
		FREE_ARRAY_ALIGNED (points, allocated, Point, 16);

	return true;
}


GLOBAL_FUNCTION bool HI_Accumulate_Bounding_Attributes (
	Attribute *				_hoops_ASGPR,
	_hoops_ISGI **		_hoops_PSACR,
	_hoops_ACHR *			_hoops_RGP,
	_hoops_PIGRA *		locks,
	unsigned int alter *	conditions,
	_hoops_HGIAA				flags) {
	_hoops_PIGRA			_hoops_PCGS, _hoops_CIIAA;
	Attribute *				_hoops_SIIAA = _hoops_ASGPR;

	/* _hoops_HSPP _hoops_CCA _hoops_SGHS _hoops_GCIAA _hoops_HII _hoops_ARRS */
	_hoops_PCGS = *locks;
	ZERO_STRUCT (&_hoops_CIIAA, _hoops_PIGRA);

	/* _hoops_RRP _hoops_IS _hoops_ISPR _hoops_IH _hoops_RCIAA _hoops_ACIAA _hoops_RSIH, _hoops_IS _hoops_CGIC
	** _hoops_IGH _hoops_PAR _hoops_HAR _hoops_PA _hoops_ARPP _hoops_SCH (_hoops_SHCAR, _hoops_PCIAA) _hoops_GHCA _hoops_SHH _hoops_IGI _hoops_HCIAA */

	do {
		if (_hoops_ASGPR->type > _hoops_IAAA (HK_HEURISTICS, HK_RENDERING_OPTIONS))
			break;

		if (_hoops_ASGPR->type == HK_HEURISTICS) {
			_hoops_GHAIR const *		_hoops_GIGC = (_hoops_GHAIR const *)_hoops_ASGPR;

			if (BIT(flags, _hoops_ICIAA) &&
				BIT (_hoops_GIGC->mask & _hoops_GIGC->value, _hoops_CCIAA))
				return false;
		}
		else if (_hoops_ASGPR->type == HK_RENDERING_OPTIONS) {
			_hoops_RHAIR *		_hoops_AHAIR = (_hoops_RHAIR *)_hoops_ASGPR;

			if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_GSIAA)) {
				if (BIT (_hoops_AHAIR->_hoops_RSIAA, _hoops_GSIAA)) {
					/* _hoops_PA _hoops_HSGRA _hoops_HRGR _hoops_HCAGR _hoops_ASIAA _hoops_HCIAA */
					_hoops_CIIAA = _hoops_AHAIR->locks->normal.mask;
					if (0 /* _hoops_PCIRA _hoops_AAHS _hoops_PSIAA _hoops_RPSI _hoops_AAHS */)
						_hoops_HSIAA (&_hoops_CIIAA, &_hoops_PCGS, sizeof (_hoops_PIGRA));

					/* _hoops_HASC _hoops_CCAH _hoops_AAHS _hoops_HRP */
					_hoops_HSIAA (&_hoops_PCGS, &_hoops_CIIAA, sizeof (_hoops_PIGRA));
					_hoops_ISIAA (&_hoops_PCGS, &_hoops_AHAIR->locks->normal.value, sizeof (_hoops_PIGRA));

					/* _hoops_PRIA _hoops_IS _hoops_HACH */
					*locks = _hoops_PCGS;

					/* _hoops_IH _hoops_IRGH _hoops_HCGC _hoops_ARP _hoops_RGR _hoops_IS _hoops_SRCH _hoops_CSIAA '_hoops_PCPAR _hoops_HIH _hoops_HCIAA _hoops_ASIAA' */
					_hoops_HSIAA (&_hoops_PCGS, &_hoops_CIIAA, sizeof (_hoops_PIGRA));
				}
				else {
					/* _hoops_SSIAA _hoops_CPS */
					ZERO_STRUCT (locks, _hoops_PIGRA);
					ZERO_STRUCT (&_hoops_PCGS, _hoops_PIGRA);
				}
			}
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	_hoops_ASGPR = _hoops_SIIAA;


	do {
#ifndef DISABLE_STYLE_SEGMENT
		if (_hoops_ASGPR->type == HK_STYLE) {
			if (!BIT (_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_STYLE))) {
				Style *					style = (Style *)_hoops_ASGPR;
				_hoops_PIGRA			_hoops_RGCAA;

				_hoops_RGCAA = *locks;

				if (style->_hoops_IGRPR && style->_hoops_IGRPR->_hoops_IPPGR &&
					(style->condition.count == 0 ||
						HI_Condition_Passed (HOOPS_WORLD->_hoops_AGCAA, conditions, &style->condition))) {

					if (!HI_Accumulate_Bounding_Attributes (style->_hoops_IGRPR->_hoops_IPPGR, _hoops_PSACR, _hoops_RGP, locks, conditions, flags))
						return false;

					/* _hoops_HGCR _hoops_RH _hoops_PGCAA */
					_hoops_PCGS = *locks;

					if (1 /* _hoops_RPSI _hoops_PSIAA _hoops_PCIRA */) {
						/* _hoops_SRS, _hoops_PA _hoops_HCIAA _hoops_ASIAA _hoops_IGICR _hoops_ASIAA */
						_hoops_HSIAA (&_hoops_PCGS, &_hoops_CIIAA, sizeof (_hoops_PIGRA));

						/* _hoops_HGCAA _hoops_PA _hoops_SR _hoops_PCPAR _hoops_SGS _hoops_RH _hoops_IAHA _hoops_GHCA _hoops_HS _hoops_ASIAA */
						_hoops_IGCAA (&_hoops_RGCAA, &_hoops_CIIAA, sizeof (_hoops_PIGRA));
						_hoops_ISIAA (&_hoops_RGCAA, &_hoops_PCGS, sizeof (_hoops_PIGRA));

						/* _hoops_HACH _hoops_PAAP */
						*locks = _hoops_RGCAA;
					}
				}
			}
		}
		else
#endif
		if (_hoops_ASGPR->type > _hoops_IAAA(_hoops_IAAA(_hoops_IAAA(HK_MODELLING_MATRIX,HK_VISIBILITY),_hoops_CPPIR),HK_CAMERA))
			return true;
		else if (_hoops_ASGPR->type == HK_VISIBILITY) {
			if (!BIT (_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_VISIBILITY))) {
				_hoops_RSAIR const *		vis = (_hoops_RSAIR const *)_hoops_ASGPR;

				*_hoops_RGP &= ~(vis->mask & ~_hoops_PCGS._hoops_RGP);
				*_hoops_RGP |= vis->mask & vis->value &
								~_hoops_PCGS._hoops_RGP;
			}
		}
		else if (_hoops_ASGPR->type == HK_MODELLING_MATRIX) {
			if (_hoops_PSACR != null && !BIT (_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_MODELLING_MATRIX))) {
				_hoops_ISGI *		matrix = (_hoops_ISGI *)_hoops_ASGPR;

				if (*_hoops_PSACR == null) {
					*_hoops_PSACR = matrix;
					_hoops_PRRH (*_hoops_PSACR);
				}
				else {
					_hoops_ISGI		*_hoops_CPAI;

					ZALLOC (_hoops_CPAI, _hoops_ISGI);
					_hoops_CPAI->type = HK_MODELLING_MATRIX;
					_hoops_CPAI->_hoops_HIHI = 1;

					HI_Multiply_Matrices (&matrix->matrix, &(*_hoops_PSACR)->matrix, &_hoops_CPAI->matrix);
					_hoops_HPRH (*_hoops_PSACR);
					*_hoops_PSACR = _hoops_CPAI;
				}
			}
		}
		else if (_hoops_ASGPR->type == _hoops_CPPIR) {
			if (conditions != null && HOOPS_WORLD->_hoops_PCIIR != 0) {
				_hoops_SPPIR const *		_hoops_CGCAA = (_hoops_SPPIR const *)_hoops_ASGPR;

				_hoops_HSIAA (conditions, _hoops_CGCAA->_hoops_SGCAA, _hoops_CGCAA->count*sizeof(unsigned int));
				_hoops_ISIAA (conditions, _hoops_CGCAA->values, _hoops_CGCAA->count*sizeof(unsigned int));
			}
		}
		else if (_hoops_ASGPR->type == HK_CAMERA) {
			if (BIT(flags, _hoops_GRCAA))
				return false;
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	return true;
}

local void _hoops_RRCAA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP const *			segment,
	_hoops_ISGI *		matrix,
	bool					_hoops_ARCAA,
	_hoops_PIGRA *		locks,
	unsigned int const *	conditions,
	_hoops_ACHR				_hoops_PRCAA,
	_hoops_HGIAA				flags,
	Bounding alter &		bounding,
	_hoops_AGIAA **	_hoops_ARGC) {
	_hoops_ISGI *		_hoops_PIIAA = matrix;
	_hoops_ACHR				_hoops_RGP = _hoops_PRCAA;
	Geometry const *		geometry;
	Subsegment const *		_hoops_SSGPR;
	unsigned int alter *	_hoops_HRCAA;
	int						_hoops_IRCAA = HOOPS_WORLD->_hoops_AGCAA / 32;

	if (_hoops_PIIAA != null)
		_hoops_PRRH (_hoops_PIIAA);


	if (_hoops_IRCAA == 0)
		++_hoops_IRCAA;
	ZALLOC_ARRAY (_hoops_HRCAA, _hoops_IRCAA, unsigned int);

	if (conditions != null)
		_hoops_AIGA (conditions, _hoops_IRCAA, unsigned int, _hoops_HRCAA);

	if (segment->_hoops_IPPGR != null) {
		if (!HI_Accumulate_Bounding_Attributes (segment->_hoops_IPPGR,
												_hoops_ARCAA ? &_hoops_PIIAA : null,
												&_hoops_RGP, locks, _hoops_HRCAA, flags)) {
			bounding->flags |= _hoops_CRCAA;
			goto _hoops_HPAGR;
		}
	}

	if (BIT(flags, _hoops_SRCAA) &&
		!segment->bounding._hoops_HICAR() &&
		BIT(segment->bounding->flags, _hoops_CCIIR)) {

		if (_hoops_PIIAA == null)
			bounding->Merge(segment->bounding);
		else
			bounding->Merge(segment->bounding._hoops_SCIS(_hoops_PIIAA->matrix));

		goto _hoops_HPAGR;
	}

	if (BIT(flags, _hoops_GACAA))
		_hoops_RGP = ~0;

	if ((geometry = segment->geometry) != null) {
		if (BIT(flags, _hoops_IHIAA)) {
			_hoops_AGIAA *		sc;

			ZALLOC (sc, _hoops_AGIAA);
			sc->next = *_hoops_ARGC;
			*_hoops_ARGC = sc;

			sc->geometry = geometry;
			if ((sc->matrix = matrix) != null)
				_hoops_PRRH (matrix);
			sc->locks = *locks;
			sc->_hoops_RGP = _hoops_RGP;
		}
		else {
			do if (!HI_Add_Geometry_Bounding (_hoops_RIGC, geometry, _hoops_PIIAA, _hoops_RGP, locks, flags, bounding))
				goto _hoops_HPAGR;
			while ((geometry = geometry->next) != null);
		}
	}


	if (BIT(flags, _hoops_RACAA))
		flags |= _hoops_ICIAA;

	if ((_hoops_SSGPR = segment->_hoops_RGRPR) != null) do {
		_hoops_CRCP const *			_hoops_SRCP;

		if (_hoops_SSGPR->type == _hoops_AGRPR)
			_hoops_SRCP = (_hoops_CRCP const *)((_hoops_PGRPR const *)_hoops_SSGPR)->_hoops_IGRPR;
		else
			_hoops_SRCP = (_hoops_CRCP const *)_hoops_SSGPR;


		if (_hoops_SRCP != null &&
			(!BIT(flags, _hoops_AACAA) || !BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PACAA))) {
			_hoops_PIGRA		_hoops_HACAA;

			_hoops_HACAA = *locks;

			_hoops_RRCAA (_hoops_RIGC, _hoops_SRCP, _hoops_PIIAA, true, locks, _hoops_HRCAA,
									 _hoops_RGP, flags|_hoops_GRCAA, bounding, _hoops_ARGC);

			*locks = _hoops_HACAA;
		}
	} while ((_hoops_SSGPR = _hoops_SSGPR->next) != null);

  _hoops_HPAGR:
	if (_hoops_PIIAA != null)
		_hoops_HPRH (_hoops_PIIAA);
	FREE_ARRAY (_hoops_HRCAA, _hoops_IRCAA, unsigned int);

	return;
}


local bool _hoops_IACAA (
	_hoops_AIGPR *	_hoops_RIGC,
	Key						key,
	_hoops_ACHR				_hoops_RGP,
	_hoops_HGIAA				flags,
	Bounding alter &		bounding,
	_hoops_AGIAA **	_hoops_ARGC)
{
	_hoops_HPAH *				thing;
	bool					result = true;

	if (_hoops_RIGC->_hoops_CACAA == _hoops_RIGC->_hoops_SACAA)
		_hoops_CSPPR();

	thing = (_hoops_HPAH *)_hoops_RCSSR (_hoops_RIGC, key);

	if (thing == null || BIT (thing->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_KEY, "Key does not refer to anything valid");
		result = false;
	}
	else if (thing->type == _hoops_IRCP) {
		_hoops_PIGRA		locks;

		ZERO_STRUCT (&locks, _hoops_PIGRA);

		_hoops_RRCAA (_hoops_RIGC, (_hoops_CRCP *)thing, null, false, &locks, null,
								 _hoops_RGP, flags, bounding, _hoops_ARGC);
	}
	else if (thing->type >= _hoops_AHRIR && thing->type <= _hoops_PHRIR) {
		if (BIT(flags, _hoops_IHIAA)) {
			_hoops_AGIAA *		sc;

			ZALLOC (sc, _hoops_AGIAA);
			sc->next = *_hoops_ARGC;
			*_hoops_ARGC = sc;

			sc->geometry = (Geometry *)thing;
			sc->_hoops_RGP = _hoops_RGP;
			sc->single = true;
		}
		else
			HI_Add_Geometry_Bounding (_hoops_RIGC, (Geometry *)thing, null,
									  BIT(flags, _hoops_GACAA) ? ~0 : _hoops_RGP,
									  null, flags, bounding);
	}
	else {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_KEY,"Key must refer to a segment or geometry");
		result = false;
	}

	if (_hoops_RIGC->_hoops_CACAA == _hoops_RIGC->_hoops_SACAA)
		_hoops_IRRPR();

	return result && !bounding._hoops_HICAR();
}



HC_INTERFACE bool HC_CDECL HC_Compute_Circumsphere_By_Key (
	Key						key,
	Point *					center,
	float *					radius)
{
	_hoops_PAPPR context("Compute_Circumsphere_By_Key");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Circumsphere_By_Key () */\n");
	);

	Bounding			bounding;
	bounding = Bounding::Create();
	if (_hoops_IACAA (
			context, key,
			T_ANY_DRAWABLE_GEOMETRY, _hoops_GACAA | _hoops_ICIAA,
			bounding, null)) {

		*center = bounding->sphere.center;
		*radius = bounding->sphere.radius;

		return true;
	}

	center->x = center->y = center->z = 0.0f;
	*radius = -1.0f;

	return false;
}


HC_INTERFACE bool HC_CDECL HC_Compute_Circumcuboid_By_Key (
	Key						key,
	Point *					min,
	Point *					max)
{
	_hoops_PAPPR context("Compute_Circumcuboid_By_Key");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Circumcuboid_By_Key () */\n");
	);

	Bounding	bounding;
	bounding = Bounding::Create();
	if (_hoops_IACAA (
			context, key,
			T_ANY_DRAWABLE_GEOMETRY, _hoops_GACAA | _hoops_ICIAA,
			 bounding, null)) {

		*min = bounding->cuboid.min;
		*max = bounding->cuboid.max;

		return true;
	}

	min->x = min->y = min->z = 1.0f;
	max->x = max->y = max->z = -1.0f;

	return false;
}



local void _hoops_GPCAA (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_CRCP *					_hoops_SRCP,
	void *						info) {
	_hoops_PGIAA *	pt = (_hoops_PGIAA *)info;
	_hoops_PIGRA				locks;

	ZERO_STRUCT (&locks, _hoops_PIGRA);

	_hoops_RRCAA (_hoops_RIGC, _hoops_SRCP, null, false, &locks, null,
							 pt->_hoops_RGP, pt->flags, *pt->bounding, &pt->_hoops_ARGC);
}


/* _hoops_SGSS _hoops_IGI _hoops_HPP _hoops_RCAR _hoops_RGAP */
GLOBAL_FUNCTION void HI_Accumulate_Segment_Bounding (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_CRCP const *				_hoops_SRCP,
	Bounding alter &			bounding,
	_hoops_HRPA const *			matrix,
	_hoops_ACHR					_hoops_PRCAA,
	_hoops_HGIAA					flags) {
	_hoops_PIGRA				locks;
	_hoops_ISGI			_hoops_RPCAA;

	ZERO_STRUCT (&locks, _hoops_PIGRA);
	ZERO_STRUCT (&_hoops_RPCAA, _hoops_ISGI);

	if (matrix != null) {
		_hoops_RPCAA.matrix = *matrix;

#if 0
		_hoops_RPCAA.type = HK_MODELLING_MATRIX;
#endif
		_hoops_RPCAA._hoops_HIHI = 1;
	}

	_hoops_RRCAA (_hoops_RIGC, _hoops_SRCP, (matrix ? &_hoops_RPCAA : null), false, &locks, null,
							 _hoops_PRCAA, flags, bounding, null);

	if (matrix != null && _hoops_RPCAA._hoops_HIHI != 1)
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Utility error while processing bounding matrices");
}



HC_INTERFACE bool HC_CDECL HC_Compute_Circumsphere (
	char const *				segname,
	Point *						center,
	float *						radius)
{
	_hoops_PAPPR context("Compute_Circumsphere");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Circumsphere () */\n");
	);

	Bounding	bounding = Bounding::Create();

	_hoops_PGIAA	pt;
	ZERO_STRUCT(&pt, _hoops_PGIAA);
	pt.bounding = &bounding;
	pt._hoops_RGP = T_ANY_DRAWABLE_GEOMETRY;
	pt.flags = _hoops_GACAA | _hoops_ICIAA;

	_hoops_CSPPR();
	HI_For_Each (context, segname, true, _hoops_GPCAA, (void *)&pt);
	_hoops_IRRPR();

	if (bounding._hoops_HICAR()) {
		center->x = center->y = center->z = 0.0f;
		*radius = -1.0f;

		return false;
	}

	*center = bounding->sphere.center;
	*radius = bounding->sphere.radius;

	return true;
}

HC_INTERFACE bool HC_CDECL HC_Compute_Circumcuboid (
	char const *				segname,
	Point *						min,
	Point *						max) {

	_hoops_PAPPR context("Compute_Circumcuboid");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Circumcuboid () */\n");
	);


	Bounding	bounding = Bounding::Create();

	_hoops_PGIAA	pt;
	ZERO_STRUCT(&pt, _hoops_PGIAA);
	pt.bounding = &bounding;
	pt._hoops_RGP = T_ANY_DRAWABLE_GEOMETRY;
	pt.flags = _hoops_GACAA | _hoops_ICIAA;

	_hoops_CSPPR();
	HI_For_Each (context, segname, true, _hoops_GPCAA, (void *)&pt);
	_hoops_IRRPR();

	if (bounding._hoops_HICAR()) {
		min->x = min->y = min->z = 1.0f;
		max->x = max->y = max->z = -1.0f;

		return false;
	}

	*min = bounding->cuboid.min;
	*max = bounding->cuboid.max;

	return true;
}


local float _hoops_APCAA (float _hoops_PPCAA, float _hoops_HPCAA, float _hoops_IPCAA,
					float _hoops_CPCAA, float _hoops_SPCAA, float _hoops_GHCAA,
					float _hoops_RHCAA, float _hoops_AHCAA, float _hoops_PHCAA) {
	return _hoops_PPCAA * (_hoops_SPCAA * _hoops_PHCAA - _hoops_AHCAA * _hoops_GHCAA) -
	       _hoops_CPCAA * (_hoops_HPCAA * _hoops_PHCAA - _hoops_AHCAA * _hoops_IPCAA) +
	       _hoops_RHCAA * (_hoops_HPCAA * _hoops_GHCAA - _hoops_SPCAA * _hoops_IPCAA);
}

struct _hoops_HHCAA {
	Point	a0, a1, a2, a3;
	Point	center;
	int		_hoops_IHCAA;
	float	_hoops_CHCAA;
	//_hoops_AIIC	_hoops_PSAA;

	_hoops_HHCAA ()
		: _hoops_IHCAA (0) {
		center = _hoops_HPCH::_hoops_IPCH;
		_hoops_CHCAA = MAX_FLOAT;
	}
	_hoops_HHCAA (Point const & _hoops_GGIAR)
		: a0 (_hoops_GGIAR), _hoops_IHCAA (1) {
		center = a0;
		_hoops_CHCAA = 0.0f;
	}
	_hoops_HHCAA (Point const & _hoops_GGIAR, Point const & p1)
		: a0 (_hoops_GGIAR), a1 (p1), _hoops_IHCAA (2) {
		Vector		_hoops_SHCAA = 0.5f * (a1 - a0);

		center = _hoops_GGIAR + _hoops_SHCAA;
		_hoops_CHCAA = _hoops_SHCAA._hoops_SSRP (_hoops_SHCAA);
	}
	_hoops_HHCAA (Point const & _hoops_GGIAR, Point const & p1, Point const & p2)
		: a0 (_hoops_GGIAR), a1 (p1), a2 (p2), _hoops_IHCAA (3) {
		Vector			_hoops_ISPI = p1 - _hoops_GGIAR;
		Vector			_hoops_CSPI = p2 - _hoops_GGIAR;
		Vector			c = _hoops_ISPI._hoops_SAIAR(_hoops_CSPI);
		float			d = 2.0f * c._hoops_SSRP(c);

		if (Abs (d) > 1.0e-10f) {
			Vector		_hoops_GICAA = (_hoops_CSPI._hoops_SSRP(_hoops_CSPI) * (_hoops_ISPI._hoops_SAIAR(_hoops_CSPI))._hoops_SAIAR(_hoops_ISPI) +
							  _hoops_ISPI._hoops_SSRP(_hoops_ISPI) * _hoops_CSPI._hoops_SAIAR(_hoops_ISPI._hoops_SAIAR(_hoops_CSPI))) / d;
			center = _hoops_GGIAR + _hoops_GICAA;
			_hoops_CHCAA = _hoops_GICAA._hoops_SSRP(_hoops_GICAA);
		}
		else {
			center = _hoops_HPCH::_hoops_IPCH;
			_hoops_CHCAA = MAX_FLOAT;
		}
	}
	_hoops_HHCAA (Point const & _hoops_GGIAR, Point const & p1, Point const & p2, Point const & _hoops_IAPH)
		: a0 (_hoops_GGIAR), a1 (p1), a2 (p2), a3 (_hoops_IAPH), _hoops_IHCAA (4) {
		Vector 			_hoops_ISPI = p1 - _hoops_GGIAR;
		Vector 			_hoops_CSPI = p2 - _hoops_GGIAR;
		Vector 			_hoops_SSPI = _hoops_IAPH - _hoops_GGIAR;
		float			d = 2.0f * _hoops_APCAA (_hoops_ISPI.x, _hoops_ISPI.y, _hoops_ISPI.z,  _hoops_CSPI.x, _hoops_CSPI.y, _hoops_CSPI.z,  _hoops_SSPI.x, _hoops_SSPI.y, _hoops_SSPI.z);

		if (Abs (d) > 1.0e-10f) {
			Vector		_hoops_GICAA = (_hoops_SSPI._hoops_SSRP(_hoops_SSPI) * _hoops_ISPI._hoops_SAIAR(_hoops_CSPI) +
							  _hoops_CSPI._hoops_SSRP(_hoops_CSPI) * _hoops_SSPI._hoops_SAIAR(_hoops_ISPI) +
							  _hoops_ISPI._hoops_SSRP(_hoops_ISPI) * _hoops_CSPI._hoops_SAIAR(_hoops_SSPI)) / d;

			center = _hoops_GGIAR + _hoops_GICAA;
			_hoops_CHCAA = _hoops_GICAA._hoops_SSRP(_hoops_GICAA);
		}
		else {
			center = _hoops_HPCH::_hoops_IPCH;
			_hoops_CHCAA = MAX_FLOAT;
		}
	}

	bool _hoops_RICAA (Point const & p) {
		Vector		v = p - center;
		return  v._hoops_SSRP (v) <= 1.00001f * _hoops_CHCAA;
	}
};



local void _hoops_AICAA (
	_hoops_HHCAA alter &		ts,
	Point const &				p) {

	switch (ts._hoops_IHCAA) {
		// _hoops_SRS _hoops_PGCR _hoops_ARAR _hoops_PICAA, (_hoops_PHRI _hoops_CGH _hoops_HSPP _hoops_CCA _hoops_IRS _hoops_CHHRR _hoops_IIHA _hoops_GPP 2 _hoops_HICAA _hoops_RSSA)
		case 0: {
			ts = _hoops_HHCAA (p);
		}	break;
		case 1: {
			ts = _hoops_HHCAA (ts.a0, p);
		}	break;

		// _hoops_PSSP _hoops_GGGRR _hoops_IIGR _hoops_CCAH _hoops_CCA _hoops_PGI _hoops_IICAA, _hoops_RPP _hoops_RSIPR _hoops_CICAA _hoops_IRS _hoops_CHHRR _hoops_IIAAR _hoops_RH _hoops_RII _hoops_PPSR
		// _hoops_PSCR _hoops_SR _hoops_PIHA _hoops_SICAA _hoops_IS _hoops_IRS 3-_hoops_PPSR _hoops_CHHRR
		case 2: {
			_hoops_HHCAA		_hoops_GCCAA (ts.a0, p);
			_hoops_HHCAA		_hoops_RCCAA (ts.a1, p);
			_hoops_HHCAA		_hoops_ACCAA;

			if (/* _hoops_PCCAA._hoops_HCCAA < _hoops_AAH._hoops_HCCAA && */ _hoops_GCCAA._hoops_RICAA (ts.a1))
				_hoops_ACCAA = _hoops_GCCAA;
			if (_hoops_RCCAA._hoops_CHCAA < _hoops_ACCAA._hoops_CHCAA && _hoops_RCCAA._hoops_RICAA (ts.a0))
				_hoops_ACCAA = _hoops_RCCAA;

			if (_hoops_ACCAA._hoops_IHCAA == 0)
				ts = _hoops_HHCAA (ts.a0, ts.a1, p);
			else
				ts = _hoops_ACCAA;
		}	break;

		// _hoops_PSHR, _hoops_HIH _hoops_ISPR _hoops_CCAH _hoops_PPSR _hoops_CCA 1 _hoops_PAR 2 _hoops_PGHC _hoops_RSSA, _hoops_ARPP _hoops_HHIC _hoops_SR _hoops_RRP _hoops_IS _hoops_SICAA _hoops_IS 4
		case 3: {
			_hoops_HHCAA		_hoops_GCCAA (ts.a0, p);
			_hoops_HHCAA		_hoops_RCCAA (ts.a1, p);
			_hoops_HHCAA		_hoops_ICCAA (ts.a2, p);
			_hoops_HHCAA		_hoops_CCCAA (ts.a0, ts.a1, p);
			_hoops_HHCAA		_hoops_SCCAA (ts.a0, ts.a2, p);
			_hoops_HHCAA		_hoops_GSCAA (ts.a1, ts.a2, p);
			_hoops_HHCAA		_hoops_ACCAA;

			if (/* _hoops_PCCAA._hoops_HCCAA < _hoops_AAH._hoops_HCCAA && */ _hoops_GCCAA._hoops_RICAA (ts.a1) && _hoops_GCCAA._hoops_RICAA (ts.a2))
				_hoops_ACCAA = _hoops_GCCAA;
			if (_hoops_RCCAA._hoops_CHCAA < _hoops_ACCAA._hoops_CHCAA && _hoops_RCCAA._hoops_RICAA (ts.a0) && _hoops_GCCAA._hoops_RICAA (ts.a2))
				_hoops_ACCAA = _hoops_RCCAA;
			if (_hoops_ICCAA._hoops_CHCAA < _hoops_ACCAA._hoops_CHCAA && _hoops_ICCAA._hoops_RICAA (ts.a0) && _hoops_GCCAA._hoops_RICAA (ts.a1))
				_hoops_ACCAA = _hoops_ICCAA;
			if (_hoops_CCCAA._hoops_CHCAA < _hoops_ACCAA._hoops_CHCAA && _hoops_CCCAA._hoops_RICAA (ts.a2))
				_hoops_ACCAA = _hoops_CCCAA;
			if (_hoops_SCCAA._hoops_CHCAA < _hoops_ACCAA._hoops_CHCAA && _hoops_SCCAA._hoops_RICAA (ts.a1))
				_hoops_ACCAA = _hoops_SCCAA;
			if (_hoops_GSCAA._hoops_CHCAA < _hoops_ACCAA._hoops_CHCAA && _hoops_GSCAA._hoops_RICAA (ts.a0))
				_hoops_ACCAA = _hoops_GSCAA;

			if (_hoops_ACCAA._hoops_IHCAA == 0)
				ts = _hoops_HHCAA (ts.a0, ts.a1, ts.a2, p);
			else
				ts = _hoops_ACCAA;
		}	break;

		// _hoops_HHH _hoops_AARRA _hoops_IIGR 1, 2 _hoops_PAR 3 _hoops_PGHC _hoops_RSSA _hoops_CGH _hoops_SHR _hoops_IPHR, _hoops_HAGC _hoops_IRS 2, 3, _hoops_PAR 4-_hoops_PPSR _hoops_CHHRR
		case 4: {
			_hoops_HHCAA		_hoops_GCCAA (ts.a0, p);
			_hoops_HHCAA		_hoops_RCCAA (ts.a1, p);
			_hoops_HHCAA		_hoops_ICCAA (ts.a2, p);
			_hoops_HHCAA		_hoops_RSCAA (ts.a3, p);
			_hoops_HHCAA		_hoops_CCCAA (ts.a0, ts.a1, p);
			_hoops_HHCAA		_hoops_SCCAA (ts.a0, ts.a2, p);
			_hoops_HHCAA		_hoops_ASCAA (ts.a0, ts.a3, p);
			_hoops_HHCAA		_hoops_GSCAA (ts.a1, ts.a2, p);
			_hoops_HHCAA		_hoops_PSCAA (ts.a1, ts.a3, p);
			_hoops_HHCAA		_hoops_HSCAA (ts.a2, ts.a3, p);
			_hoops_HHCAA		_hoops_ISCAA (ts.a0, ts.a1, ts.a2, p);
			_hoops_HHCAA		_hoops_CSCAA (ts.a0, ts.a1, ts.a3, p);
			_hoops_HHCAA		_hoops_SSCAA (ts.a0, ts.a2, ts.a3, p);
			_hoops_HHCAA		_hoops_GGSAA (ts.a1, ts.a2, ts.a3, p);
			_hoops_HHCAA		_hoops_ACCAA;

			if (/* _hoops_PCCAA._hoops_HCCAA < _hoops_AAH._hoops_HCCAA && */ _hoops_GCCAA._hoops_RICAA (ts.a1) && _hoops_GCCAA._hoops_RICAA (ts.a2) && _hoops_GCCAA._hoops_RICAA (ts.a3))
				_hoops_ACCAA = _hoops_GCCAA;
			if (_hoops_RCCAA._hoops_CHCAA < _hoops_ACCAA._hoops_CHCAA && _hoops_RCCAA._hoops_RICAA (ts.a0) && _hoops_RCCAA._hoops_RICAA (ts.a2) && _hoops_RCCAA._hoops_RICAA (ts.a3))
				_hoops_ACCAA = _hoops_RCCAA;
			if (_hoops_ICCAA._hoops_CHCAA < _hoops_ACCAA._hoops_CHCAA && _hoops_ICCAA._hoops_RICAA (ts.a0) && _hoops_ICCAA._hoops_RICAA (ts.a1) && _hoops_ICCAA._hoops_RICAA (ts.a3))
				_hoops_ACCAA = _hoops_ICCAA;
			if (_hoops_RSCAA._hoops_CHCAA < _hoops_ACCAA._hoops_CHCAA && _hoops_RSCAA._hoops_RICAA (ts.a0) && _hoops_RSCAA._hoops_RICAA (ts.a1) && _hoops_RSCAA._hoops_RICAA (ts.a2))
				_hoops_ACCAA = _hoops_RSCAA;
			if (_hoops_CCCAA._hoops_CHCAA < _hoops_ACCAA._hoops_CHCAA && _hoops_CCCAA._hoops_RICAA (ts.a2) && _hoops_CCCAA._hoops_RICAA (ts.a3))
				_hoops_ACCAA = _hoops_CCCAA;
			if (_hoops_SCCAA._hoops_CHCAA < _hoops_ACCAA._hoops_CHCAA && _hoops_SCCAA._hoops_RICAA (ts.a1) && _hoops_SCCAA._hoops_RICAA (ts.a3))
				_hoops_ACCAA = _hoops_SCCAA;
			if (_hoops_ASCAA._hoops_CHCAA < _hoops_ACCAA._hoops_CHCAA && _hoops_ASCAA._hoops_RICAA (ts.a1) && _hoops_ASCAA._hoops_RICAA (ts.a2))
				_hoops_ACCAA = _hoops_ASCAA;
			if (_hoops_GSCAA._hoops_CHCAA < _hoops_ACCAA._hoops_CHCAA && _hoops_GSCAA._hoops_RICAA (ts.a0) && _hoops_GSCAA._hoops_RICAA (ts.a3))
				_hoops_ACCAA = _hoops_GSCAA;
			if (_hoops_PSCAA._hoops_CHCAA < _hoops_ACCAA._hoops_CHCAA && _hoops_PSCAA._hoops_RICAA (ts.a0) && _hoops_PSCAA._hoops_RICAA (ts.a2))
				_hoops_ACCAA = _hoops_GSCAA;
			if (_hoops_HSCAA._hoops_CHCAA < _hoops_ACCAA._hoops_CHCAA && _hoops_HSCAA._hoops_RICAA (ts.a0) && _hoops_HSCAA._hoops_RICAA (ts.a1))
				_hoops_ACCAA = _hoops_HSCAA;
			if (_hoops_ISCAA._hoops_CHCAA < _hoops_ACCAA._hoops_CHCAA && _hoops_ISCAA._hoops_RICAA (ts.a3))
				_hoops_ACCAA = _hoops_ISCAA;
			if (_hoops_CSCAA._hoops_CHCAA < _hoops_ACCAA._hoops_CHCAA && _hoops_CSCAA._hoops_RICAA (ts.a2))
				_hoops_ACCAA = _hoops_CSCAA;
			if (_hoops_SSCAA._hoops_CHCAA < _hoops_ACCAA._hoops_CHCAA && _hoops_SSCAA._hoops_RICAA (ts.a1))
				_hoops_ACCAA = _hoops_SSCAA;
			if (_hoops_GGSAA._hoops_CHCAA < _hoops_ACCAA._hoops_CHCAA && _hoops_GGSAA._hoops_RICAA (ts.a0))
				_hoops_ACCAA = _hoops_GGSAA;

			ts = _hoops_ACCAA;
		}	break;
	}
}


class _hoops_RGSAA : public _hoops_CHCIR {
	friend class Counted_Pointer<_hoops_RGSAA>;
	private:
		HOOPS_API _hoops_RGSAA () : _hoops_CHCIR () {}

	public:
		Point		_hoops_AGSAA, _hoops_PGSAA, _hoops_HGSAA, _hoops_IGSAA, _hoops_RPSC, _hoops_CGSAA;


		bool		Merge (int count, Point const * points) alter {
						_hoops_SASC	sc (count, points);

						if (BIT (flags, Bounding_EMPTY)) {
							_hoops_AGSAA = _hoops_PGSAA = _hoops_HGSAA = _hoops_IGSAA = _hoops_RPSC = _hoops_CGSAA = *points++;
							--count;
							flags &= ~Bounding_EMPTY;
						}
						while (count-- > 0) {
							if (points->x < _hoops_AGSAA.x)
								_hoops_AGSAA = *points;
							else if (points->x > _hoops_PGSAA.x)
								_hoops_PGSAA = *points;

							if (points->y < _hoops_HGSAA.y)
								_hoops_HGSAA = *points;
							else if (points->y > _hoops_IGSAA.y)
								_hoops_IGSAA = *points;

							if (points->z < _hoops_RPSC.z)
								_hoops_RPSC = *points;
							else if (points->z > _hoops_CGSAA.z)
								_hoops_CGSAA = *points;

							++points;
						}
						return false;
					}
};
typedef Counted_Pointer<_hoops_RGSAA>		_hoops_SGSAA;


class _hoops_GRSAA : public _hoops_CHCIR {
	friend class Counted_Pointer<_hoops_GRSAA>;
	private:
		HOOPS_API _hoops_GRSAA () : _hoops_CHCIR () {}

	public:
		Point *		points;
		int			count;

		~_hoops_GRSAA() {
			if (count > 0)
				FREE_ARRAY (points, count, Point);
		}

		bool		Merge (int c, Point const * p) alter {
						if (count == 0) {
							count = c;
							_hoops_GGIPR (p, count, Point, points);
						}
						else {
							Point *		_hoops_RRSAA = points;
							int			_hoops_ARSAA = count;

							count += c;
							ALLOC_ARRAY_CACHED (points, count, Point);
							_hoops_AIGA (_hoops_RRSAA, _hoops_ARSAA, Point, points);
							_hoops_AIGA (p, c, Point, &points[_hoops_ARSAA]);
							FREE_ARRAY (_hoops_RRSAA, _hoops_ARSAA, Point);
						}
						return false;
					}
};
typedef Counted_Pointer<_hoops_GRSAA>		_hoops_PRSAA;


local void _hoops_HRSAA (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HGIAA					flags,
	Bounding alter &			bounding,
	_hoops_AGIAA alter *	_hoops_ARGC) {
	_hoops_AGIAA alter *	_hoops_RPPA;

	if (_hoops_ARGC == null)
		return;		// _hoops_PSP _hoops_PIH

	// _hoops_HSPAR _hoops_PPSR _hoops_PIH _hoops_IS _hoops_CGIC 2 _hoops_HICAA _hoops_RSSA _hoops_IS _hoops_IRHH _hoops_CIGS _hoops_CHHRR
	_hoops_SGSAA				_hoops_IRSAA = _hoops_SGSAA::Create();

	_hoops_RPPA = _hoops_ARGC;
	do {
		Geometry const *		geometry = _hoops_RPPA->geometry;

		do {
			HI_Add_Geometry_Bounding (_hoops_RIGC, geometry, _hoops_RPPA->matrix, _hoops_RPPA->_hoops_RGP, &_hoops_RPPA->locks, flags, (Bounding &)_hoops_IRSAA);
		} while (!_hoops_RPPA->single && (geometry = geometry->next) != null);
	} while ((_hoops_RPPA = _hoops_RPPA->next) != null);

	_hoops_HHCAA				as;

	if (_hoops_IRSAA->_hoops_PGSAA.x - _hoops_IRSAA->_hoops_AGSAA.x >= _hoops_IRSAA->_hoops_CGSAA.z - _hoops_IRSAA->_hoops_RPSC.z) {
		if (_hoops_IRSAA->_hoops_PGSAA.x - _hoops_IRSAA->_hoops_AGSAA.x >= _hoops_IRSAA->_hoops_IGSAA.y - _hoops_IRSAA->_hoops_HGSAA.y)
			as = _hoops_HHCAA (_hoops_IRSAA->_hoops_AGSAA, _hoops_IRSAA->_hoops_PGSAA);
		else
			as = _hoops_HHCAA (_hoops_IRSAA->_hoops_HGSAA, _hoops_IRSAA->_hoops_IGSAA);
	}
	else {
		if (_hoops_IRSAA->_hoops_IGSAA.y - _hoops_IRSAA->_hoops_HGSAA.y >= _hoops_IRSAA->_hoops_CGSAA.z - _hoops_IRSAA->_hoops_RPSC.z)
			as = _hoops_HHCAA (_hoops_IRSAA->_hoops_HGSAA, _hoops_IRSAA->_hoops_IGSAA);
		else
			as = _hoops_HHCAA (_hoops_IRSAA->_hoops_RPSC, _hoops_IRSAA->_hoops_CGSAA);
	}

	_hoops_RPPA = _hoops_ARGC;
	while (_hoops_RPPA != null) {
		Geometry const *		geometry = _hoops_RPPA->geometry;
		bool					_hoops_CCCIR = false;

		do {
			_hoops_PRSAA		_hoops_CRSAA = _hoops_PRSAA::Create();
			bool						_hoops_SRSAA = false;

			HI_Add_Geometry_Bounding (_hoops_RIGC, geometry, _hoops_RPPA->matrix, _hoops_RPPA->_hoops_RGP, &_hoops_RPPA->locks, flags, (Bounding &)_hoops_CRSAA);

			do {
				Point const *		points = _hoops_CRSAA->points;
				int					count = _hoops_CRSAA->count;

				_hoops_SRSAA = false;

				while (count-- > 0) {
					if (!as._hoops_RICAA (*points)) {
						_hoops_AICAA (as, *points);
						_hoops_CCCIR = _hoops_SRSAA = true;
						break;
					}
					++points;
				}
			} while (_hoops_SRSAA);
		} while (!_hoops_CCCIR && !_hoops_RPPA->single && (geometry = geometry->next) != null);

		if (_hoops_CCCIR)
			_hoops_RPPA = _hoops_ARGC;
		else
			_hoops_RPPA = _hoops_RPPA->next;
	}

	while ((_hoops_RPPA = _hoops_ARGC) != null) {
		_hoops_ARGC = _hoops_ARGC->next;

		if (_hoops_RPPA->matrix != null)
			_hoops_HPRH (_hoops_RPPA->matrix);
		FREE (_hoops_RPPA, _hoops_AGIAA);
	}

	bounding->sphere.center = as.center;
	bounding->sphere.radius = _hoops_SGIHR (as._hoops_CHCAA);
	bounding->cuboid = bounding->sphere;
	bounding->flags &= ~Bounding_EMPTY;
}




#define _hoops_GASAA			0
#define _hoops_RASAA				1
#define _hoops_AASAA				2
#define _hoops_PASAA		3
#define _hoops_HASAA		4
#define _hoops_IASAA	5
#define _hoops_CASAA		6

#define _hoops_SASAA		_hoops_ASPCR	/* _hoops_CACH _hoops_PIP _hoops_GGR _hoops_GPSAA _hoops_GASR */


local const _hoops_IGRCR _hoops_RPSAA[] = {
	{_hoops_GASAA,			_hoops_GRRCR ("visibility"),			_hoops_GHAGA, -999, false, null},
	{_hoops_RASAA,			_hoops_GRRCR ("detailed"),				_hoops_RRRCR, 0, true, null},
	{_hoops_HASAA,	_hoops_GRRCR ("respect locking"),		_hoops_RRRCR, 0, true, null},
	{_hoops_IASAA,	_hoops_GRRCR ("ignore clip region"),	_hoops_RRRCR, 0, true, null},
	{_hoops_IASAA,	_hoops_GRRCR ("ignore clip regions"),	_hoops_RRRCR, 0, true, null},
	{_hoops_CASAA,		_hoops_GRRCR ("minimal"),				_hoops_RRRCR, 0, true, null},
#if 0
	{_hoops_AASAA,			_hoops_GRRCR ("inherit"),			_hoops_RRRCR, 0, true, null},
	{_hoops_PASAA,	_hoops_GRRCR ("exclude segment"),	_hoops_PRRCR, -999, true},
#endif
};


local bool _hoops_APSAA (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			filter,
	bool *					_hoops_PPSAA,
	_hoops_ACHR *			_hoops_RGP,
	_hoops_HGIAA *			flags) {
	Option_Value *			option_list;
	Option_Value *			option;

	if (_hoops_CIACR (_hoops_HPSAA)->table == null) {
		int				count = _hoops_GGAPR (_hoops_RPSAA);
		int				_hoops_IPSAA = count;
		_hoops_PIIIR	**table;

		while (_hoops_IPSAA != _hoops_RIII (_hoops_IPSAA))
			_hoops_IPSAA &= ~_hoops_RIII (_hoops_IPSAA);

		ZALLOC_ARRAY (table, _hoops_IPSAA, _hoops_PIIIR *);

		_hoops_CIACR (_hoops_HPSAA)->table = table;
		_hoops_CIACR (_hoops_HPSAA)->size = _hoops_IPSAA;


		while (count-- > 0) {
			_hoops_GCIIR *	_hoops_CIIIR = null;

			/* _hoops_GRH _hoops_PRCA _hoops_IS _hoops_GGGRA _hoops_GGR _hoops_HPRC _hoops_GASR */
			switch (_hoops_RPSAA[count].id) {
				case _hoops_GASAA:			_hoops_CIIIR = _hoops_CIACR (_hoops_CPSAA);		break;
			}

			if (_hoops_CIIIR != null) {
				_hoops_PIIIR *		_hoops_SPSAA;

				_hoops_SPSAA = HI_Define_Nice_Option (_hoops_CIACR (_hoops_HPSAA),
													_hoops_RPSAA[count].id,
													(_hoops_HCRPR *)&_hoops_RPSAA[count].name,
													_hoops_GHAGA, -999,
													_hoops_RPSAA[count]._hoops_GHSAA,
													_hoops_CIIIR);
				_hoops_SPSAA->_hoops_RRHH |= _hoops_SIIIR;
			}
			else
				HI_Define_Nice_Option (_hoops_CIACR (_hoops_HPSAA),
									   _hoops_RPSAA[count].id,
									   (_hoops_HCRPR *)&_hoops_RPSAA[count].name,
									   _hoops_RPSAA[count]._hoops_RCIIR,
									   _hoops_RPSAA[count]._hoops_RHSAA,
									   _hoops_RPSAA[count]._hoops_GHSAA,
									   null);
		}
	}


	if (!HI_Parse_Options (_hoops_RIGC, filter, _hoops_CIACR (_hoops_HPSAA),
						   &option_list, _hoops_SIACR))
		return false;

	if (_hoops_PPSAA != null)
		*_hoops_PPSAA = false;
	*_hoops_RGP = T_ANY_DRAWABLE_GEOMETRY;
	if (flags != null)
		*flags = 0;

	if ((option = option_list) != null) do {
		if (option->type->id == _hoops_GASAA) {
			Option_Value *_hoops_AHSAA = option->value.option_list;

			if (_hoops_PPSAA != null)
				*_hoops_PPSAA = true;

			if (_hoops_AHSAA != null) do {
				_hoops_ACHR	_hoops_PHSAA = (_hoops_ACHR)_hoops_AHSAA->type->id;

				if (BIT (_hoops_PHSAA, _hoops_HHSAA)) {
					/* "_hoops_IHSAA" _hoops_AGSR "_hoops_HHSA _hoops_RH _hoops_SHSC _hoops_PAIP _hoops_IS
					 * _hoops_RGR _hoops_PIRA" _hoops_HRII _hoops_HSAR "_hoops_HIGAA _hoops_RGR _hoops_SPR _hoops_IGRH."
					 *
					 * _hoops_IPCP "_hoops_SHSC _hoops_PAIP" _hoops_HRGR _hoops_RH _hoops_CRIPR _hoops_PISH _hoops_HPGR _hoops_RGR _hoops_PSSPR _hoops_PAPA.
					 */
					*_hoops_RGP = 0;
					if (!_hoops_AHSAA->_hoops_GCACR)
						*_hoops_RGP |= (_hoops_PHSAA & ~_hoops_HHSAA);
				}
				else if (_hoops_PHSAA == _hoops_SASAA ||
						 _hoops_PHSAA == T_CUT_GEOMETRY ||
						 _hoops_PHSAA == T_ANY_SHADOW) {
					/* _hoops_PAH _hoops_IGIRR _hoops_SSPC _hoops_AGCR */
				}
				else if (_hoops_AHSAA->type->_hoops_RCIIR == _hoops_GHAGA &&
						 _hoops_AHSAA->value.option_list != null) {
					/* _hoops_ARAS _hoops_RHIR _hoops_IRS _hoops_ARAH-_hoops_HIGR */

					Option_Value *_hoops_CHSAA = _hoops_AHSAA->value.option_list;

					do {
						_hoops_ACHR	_hoops_SHSAA = (_hoops_ACHR)_hoops_CHSAA->type->id;

						if (BIT (_hoops_SHSAA, _hoops_HHSAA)) {
							/* "_hoops_IHSAA" _hoops_AGSR "_hoops_HHSA _hoops_RH _hoops_SHSC _hoops_PAIP _hoops_IS
							 * _hoops_RGR _hoops_PIRA" _hoops_HRII _hoops_HSAR "_hoops_HIGAA _hoops_RGR _hoops_SPR _hoops_IGRH."
							 *
							 * _hoops_IPCP "_hoops_SHSC _hoops_PAIP" _hoops_HRGR _hoops_RH _hoops_CRIPR _hoops_PISH _hoops_HPGR _hoops_RGR _hoops_PSSPR _hoops_PAPA.
							 */
							*_hoops_RGP &= ~_hoops_PHSAA;
							if (!_hoops_CHSAA->_hoops_GCACR)
								*_hoops_RGP |= (_hoops_SHSAA & ~_hoops_HHSAA);
						}
						else {
							/* _hoops_HIGAA _hoops_RGR _hoops_SPR _hoops_IGRH. */
							if (_hoops_CHSAA->_hoops_GCACR)
								*_hoops_RGP &= ~_hoops_SHSAA;
							else
								*_hoops_RGP |= _hoops_SHSAA;
						}
					} while ((_hoops_CHSAA = _hoops_CHSAA->next) != null);
				}
				else {
					/* _hoops_HIGAA _hoops_RGR _hoops_SPR _hoops_IGRH. */
					if (_hoops_AHSAA->_hoops_GCACR)
						*_hoops_RGP &= ~_hoops_PHSAA;
					else
						*_hoops_RGP |= _hoops_PHSAA;
				}
			} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
		}
		else if (option->type->id == _hoops_RASAA) {
			if (flags && !option->_hoops_GCACR)
				*flags |= _hoops_SPIAA;
		}
		else if (option->type->id == _hoops_IASAA) {
			if (flags && !option->_hoops_GCACR)
				*flags |= _hoops_GISAA;
		}
		else if (option->type->id == _hoops_HASAA) {
			if (flags && !option->_hoops_GCACR)
				*flags |= _hoops_SRCAA;
		}
		else if (option->type->id == _hoops_CASAA) {
			if (flags && !option->_hoops_GCACR)
				*flags |= _hoops_IHIAA;
		}
	} while ((option = option->next) != null);


	HI_Free_Option_List (_hoops_RIGC, option_list);

	return true;
}


HC_INTERFACE bool HC_CDECL HC_Filter_Circumsphere (
	char const *				segname,
	char const *				filter,
	Point *						center,
	float *						radius) {

	_hoops_PAPPR context("Filter_Circumsphere");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Filter_Circumsphere () */\n");
	);

	Bounding					bounding = Bounding::Create();
	_hoops_PGIAA	pt;

	pt.bounding = &bounding;
	pt._hoops_ARGC = null;

	if (!_hoops_APSAA (context, filter, null, &pt._hoops_RGP, &pt.flags))
		return false;

	pt.flags |= _hoops_RACAA;

	_hoops_CSPPR();
	HI_For_Each (context, segname, true, _hoops_GPCAA, (void *)&pt);
	_hoops_IRRPR();

	if (BIT (pt.flags, _hoops_IHIAA)) {
		_hoops_HRSAA (context, pt.flags, bounding, pt._hoops_ARGC);
	}

	if (bounding._hoops_HICAR()) {
		center->x = center->y = center->z = 0.0f;
		*radius = -1.0f;
		return false;
	}

	*center = bounding->sphere.center;
	*radius = bounding->sphere.radius;
	return true;
}

HC_INTERFACE bool HC_CDECL HC_Filter_Circumcuboid (
	char const *				segname,
	char const *				filter,
	Point *						min,
	Point *						max) {

	_hoops_PAPPR context("Filter_Circumcuboid");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Filter_Circumcuboid () */\n");
	);

	Bounding					bounding = Bounding::Create();
	_hoops_PGIAA	pt;

	pt.bounding = &bounding;
	pt._hoops_ARGC = null;

	if (!_hoops_APSAA (context, filter, null, &pt._hoops_RGP, &pt.flags))
		return false;

	pt.flags |= _hoops_RACAA;

	_hoops_CSPPR();
	HI_For_Each (context, segname, true, _hoops_GPCAA, (void *)&pt);
	_hoops_IRRPR();

	if (bounding._hoops_HICAR()) {
		min->x = min->y = min->z = 1.0f;
		max->x = max->y = max->z = -1.0f;
		return false;
	}

	*min = bounding->cuboid.min;
	*max = bounding->cuboid.max;
	return true;
}


HC_INTERFACE bool HC_CDECL HC_Filter_Circumsphere_By_Key (
	Key						key,
	char const *			filter,
	Point *					center,
	float *					radius)
{
	_hoops_PAPPR context("Filter_Circumsphere_By_Key");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Filter_Circumsphere_By_Key () */\n");
	);

	_hoops_ACHR				_hoops_RGP;
	_hoops_HGIAA				flags;
	_hoops_AGIAA *		_hoops_ARGC = null;

	if (!_hoops_APSAA (context, filter, null, &_hoops_RGP, &flags))
		return false;

	flags |= _hoops_RACAA;

	Bounding	bounding;

	if (_hoops_IACAA (context, key, _hoops_RGP, flags, bounding, &_hoops_ARGC)) {
		if (BIT (flags, _hoops_IHIAA)) {
			_hoops_HRSAA (context, flags, bounding, _hoops_ARGC);
		}

		*center = bounding->sphere.center;
		*radius = bounding->sphere.radius;
		return true;
	}

	center->x = center->y = center->z = 0.0f;
	*radius = -1.0f;
	return false;
}


HC_INTERFACE bool HC_CDECL HC_Filter_Circumcuboid_By_Key (
	Key						key,
	char const *			filter,
	Point *					min,
	Point *					max)
{
	_hoops_PAPPR context("Filter_Circumcuboid_By_Key");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Filter_Circumcuboid_By_Key () */\n");
	);

	_hoops_ACHR				_hoops_RGP;
	_hoops_HGIAA				flags;

	if (!_hoops_APSAA (context, filter, null, &_hoops_RGP, &flags))
		return false;

	flags |= _hoops_RACAA;

	Bounding	bounding;

	if (_hoops_IACAA (context, key, _hoops_RGP, flags, bounding, null)) {
		*min = bounding->cuboid.min;
		*max = bounding->cuboid.max;
		return true;
	}

	min->x = min->y = min->z = 1.0f;
	max->x = max->y = max->z = -1.0f;
	return false;
}






HC_INTERFACE void HC_CDECL HC_Compute_Screen_Extent (
	char const *			segname,
	char const *			filter,
	float *					left,
	float *					right,
	float *					bottom,
	float *					top)
{
	_hoops_PAPPR context("Compute_Screen_Extent");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Screen_Extent () */\n");
	);


	_hoops_CSPPR();
	_hoops_GGAGR *	_hoops_GHRI;
	_hoops_RISAA	_hoops_AISAA;
	if ((_hoops_GHRI = HI_Force_Find_Owner_Actor (context, segname, &_hoops_AISAA.context)) != null) {
		if (_hoops_APSAA (context, filter, &_hoops_AISAA._hoops_PPSAA, &_hoops_AISAA._hoops_RGP, &_hoops_AISAA._hoops_PISAA)) {
			if (_hoops_HISAA (context, _hoops_GHRI, _hoops_IISAA, &_hoops_AISAA)) {
				*left = _hoops_AISAA.left;
				*right = _hoops_AISAA.right;
				*bottom = _hoops_AISAA.bottom;
				*top = _hoops_AISAA.top;
			}
			else {
				*left = *bottom = -1.0f;
				*right = *top = 1.0f;
			}
		}
	}
	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Compute_Screen_Extent_By_Pat (
	int						count,
	Key const *				keys,
	char const *			filter,
	float *					left,
	float *					right,
	float *					bottom,
	float *					top)
{
	_hoops_PAPPR context("Compute_Screen_Extent_By_Path");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Screen_Extent_By_Path () */\n");
	);


	_hoops_CSPPR();

	int	_hoops_CISAA = 0;
	_hoops_CRCP const **	_hoops_SISAA;

	if ((_hoops_CISAA = HI_Convert_Keys_To_Path (context, count, keys, _hoops_SISAA)) == 0) {
		HE_ERROR (HEC_SEGMENT, HES_INVALID_KEY, "Provided key does not refer to a valid Segment");
	}
	else {
		_hoops_RISAA	_hoops_AISAA;
		_hoops_GGAGR *	_hoops_GHRI;
		if ((_hoops_GHRI = HI_Force_Find_Path_Actor (context, _hoops_CISAA, _hoops_SISAA, &_hoops_AISAA.context)) != null) {
			_hoops_AISAA.context = null;
			_hoops_AISAA._hoops_CISAA = _hoops_CISAA;
			_hoops_AISAA.path = _hoops_SISAA;

			if (_hoops_APSAA (context, filter, &_hoops_AISAA._hoops_PPSAA, &_hoops_AISAA._hoops_RGP, &_hoops_AISAA._hoops_PISAA)) {
				if (_hoops_HISAA (context, _hoops_GHRI, _hoops_IISAA, &_hoops_AISAA)) {
					*left = _hoops_AISAA.left;
					*right = _hoops_AISAA.right;
					*bottom = _hoops_AISAA.bottom;
					*top = _hoops_AISAA.top;
				}
				else {
					*left = *bottom = -1.0f;
					*right = *top = 1.0f;
				}
			}
		}
	}

	_hoops_IRRPR();

	if (_hoops_CISAA > 0)
		FREE_ARRAY (_hoops_SISAA, _hoops_CISAA, _hoops_CRCP const *);
#endif
}

/* _hoops_GCSAA _hoops_CRGPR */

HC_INTERFACE void HC_CDECL HC_Compute_Screen_Extent_By_Key (
	Key						key,
	char const *			filter,
	float *					left,
	float *					right,
	float *					bottom,
	float *					top)
{
	_hoops_PAPPR context("Compute_Screen_Extent_By_Key");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Screen_Extent_By_Key () */\n");
	);

	_hoops_CSPPR();
	_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP*)_hoops_RCSSR (context, key);
	if (_hoops_SRCP == null || _hoops_SRCP->type != _hoops_IRCP ||
		BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_KEY, "Provided key does not refer to valid segment");
		_hoops_IRRPR();
		return;
	}

	_hoops_GGAGR *	_hoops_GHRI;
	_hoops_RISAA	_hoops_AISAA;
	if ((_hoops_GHRI = HI_Force_Find_Owner_Actor (context, _hoops_GRSPR (null, "%k", &key), &_hoops_AISAA.context)) != null) {
		if (_hoops_APSAA (context, filter, &_hoops_AISAA._hoops_PPSAA, &_hoops_AISAA._hoops_RGP, &_hoops_AISAA._hoops_PISAA)) {
			if (_hoops_HISAA (context, _hoops_GHRI, _hoops_IISAA, &_hoops_AISAA)) {
				*left = _hoops_AISAA.left;
				*right = _hoops_AISAA.right;
				*bottom = _hoops_AISAA.bottom;
				*top = _hoops_AISAA.top;
			}
			else {
				*left = *bottom = -1.0f;
				*right = *top = 1.0f;
			}
		}
	}
	_hoops_IRRPR();
#endif
}

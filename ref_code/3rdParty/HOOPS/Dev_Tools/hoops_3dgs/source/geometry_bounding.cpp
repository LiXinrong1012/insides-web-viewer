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
 * $Id: obf_tmp.txt 1.142 2010-10-08 06:34:27 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


local int _hoops_SHCHH (
	Elliptical_Arc const *arc,
	int						count,
	Point alter			*_hoops_IAIRA) {
	Point alter			*pl = _hoops_IAIRA;
	int						ii;
	float					theta;
	float					delta;
	Point const			*center;
	Vector const			*_hoops_GGHI, *_hoops_RGHI;
	Point				_hoops_GRIAA;
	Vector				_hoops_RRIAA, _hoops_ARIAA;
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

	theta = 360.0f * start;
	delta = 360.0f / (float)count;
	ii = (int)((float)count * (end - start));

	_hoops_RGGA (ii-- < 0) {
		_hoops_RICH (theta, t, s);
		pl->x = center->x + s * _hoops_GGHI->x + t * _hoops_RGHI->x;
		pl->y = center->y + s * _hoops_GGHI->y + t * _hoops_RGHI->y;
		pl->z = center->z + s * _hoops_GGHI->z + t * _hoops_RGHI->z;
		++pl;
		theta += delta;
	}

	{
		_hoops_RICH (360.0f*end , t, s);
		pl->x = center->x + s * _hoops_GGHI->x + t * _hoops_RGHI->x;
		pl->y = center->y + s * _hoops_GGHI->y + t * _hoops_RGHI->y;
		pl->z = center->z + s * _hoops_GGHI->z + t * _hoops_RGHI->z;
		++pl;
	}


	return (pl - _hoops_IAIRA);
}


local void _hoops_GICHH (
	PolyCylinder *			polycylinder) {
	Bounding alter &		_hoops_RCHS = polycylinder->bounding;
	Vector const			size = _hoops_RCHS->cuboid.max - _hoops_RCHS->cuboid.min;
	float					_hoops_RICHH = 2 * (size.x * size.y + (size.x + size.y) * size.z);
	Point const *			points = polycylinder->points;
	float const *			radii = polycylinder->radii;
	float					_hoops_AICHH = 0.0f;
	float					_hoops_CPHA = 0.0f;
	int						count;

	count = polycylinder->point_count-1;
	while (count-- > 0) {
		Vector				axis = points[1] - points[0];

		_hoops_CPHA += axis.length();
	}

	count = polycylinder->_hoops_ISPIR;
	while (count-- > 0)
		_hoops_AICHH += *radii++;
	_hoops_AICHH /= (float)polycylinder->_hoops_ISPIR;

	float	area = 2 * HK_Pi * _hoops_AICHH * _hoops_CPHA;

	if (_hoops_RICHH > 0.0f)
		_hoops_RCHS->_hoops_CGCIR = _hoops_AHIA (area / _hoops_RICHH, 1.0f);
	else
		_hoops_RCHS->_hoops_CGCIR = 0.0f;

	if (_hoops_RCHS->_hoops_CGCIR == 0.0f)
		_hoops_RCHS->_hoops_CGCIR = 0.01f * polycylinder->point_count; // _hoops_GAHPR _hoops_PII _hoops_ISII
}

local void _hoops_PICHH (
	Polyhedron *			_hoops_IPRI) 
{
	Bounding alter &		_hoops_RCHS = _hoops_IPRI->bounding;
	Vector const			size = _hoops_RCHS->cuboid.max - _hoops_RCHS->cuboid.min;

	// _hoops_HPPR _hoops_IS _hoops_HGCR _hoops_HICHH _hoops_PPR _hoops_SSGRH _hoops_GHC _hoops_IS _hoops_SHH _hoops_GCRHA
	int	c = 0;

	if (size.x == 0.0f)
		c++;
	if (size.y == 0.0f)
		c++;
	if (size.z == 0.0f)
		c++;

	if (c == 1) {
		_hoops_RCHS->_hoops_CGCIR = 1.0f;
		return;
	}

#if 0
	_hoops_RCHS->_hoops_CGCIR = 0.5f;
#else

	Point const *			points = _hoops_IPRI->points;
	float					area = 0.0f;
	_hoops_IICHH		_hoops_CICHH = _hoops_IPRI->polyhedron_flags;
	bool					_hoops_SICHH = false;
	

	if (_hoops_IPRI->tristrips == null) {
		int	_hoops_APPHA = HOOPS_WORLD->_hoops_HGGHR;
		HOOPS_WORLD->_hoops_HGGHR &= ~_hoops_SRRIR;
		HI_Assemble_3D_Tristrips (_hoops_IPRI, (_hoops_SARHR)~0, false);
		HOOPS_WORLD->_hoops_HGGHR = _hoops_APPHA;
		_hoops_SICHH = true;
	}

	if (_hoops_IPRI->tristrips) {
		Tristrip const *		ts = _hoops_IPRI->tristrips;

		do {
			int					_hoops_PHHA = ts->_hoops_PHHA;
			int const *			lengths = ts->lengths;
			int const *			vi = ts->_hoops_AIHA;

			while (_hoops_PHHA-- > 0) {
				int				length = *lengths++;
				int				_hoops_HSPI = *vi++;
				int				_hoops_ISPI = *vi++;
				Vector			s1 = points[_hoops_ISPI] - points[_hoops_HSPI];

				length -= 2;
				while (length-- > 0) {
					int			_hoops_CSPI = *vi++;
					Vector		s2 = points[_hoops_CSPI] - points[_hoops_ISPI];
					Vector		_hoops_SAIAR = s1._hoops_SAIAR (s2);

					area += 0.5f * Abs (_hoops_SAIAR.length());

					_hoops_HSPI = _hoops_ISPI;
					_hoops_ISPI = _hoops_CSPI;
					s1 = s2;
				}
			}
		} while ((ts = ts->next) != null);


		float	_hoops_RICHH = 2 * (size.x * size.y + (size.x + size.y) * size.z);

		_hoops_RCHS->_hoops_CGCIR = _hoops_AHIA (area / _hoops_RICHH, 1.0f);
	}
	else
		_hoops_RCHS->_hoops_CGCIR = _hoops_AHIA (_hoops_IPRI->point_count/10000.0f, 1.0f);

	if (_hoops_SICHH) {
		if (_hoops_IPRI->tristrips) {
			HI_Free_Tristrip_List (_hoops_IPRI->tristrips);
			_hoops_IPRI->tristrips = null;
		}
		_hoops_IPRI->_hoops_ACRHR = 0;
		_hoops_IPRI->polyhedron_flags &= (_hoops_APRHR | _hoops_CGRHR);
		_hoops_IPRI->polyhedron_flags |= (_hoops_CICHH & ~(_hoops_APRHR | _hoops_CGRHR));
	}
#endif
}




GLOBAL_FUNCTION bool HI_Figure_Geometry_Bounding (
	Geometry const *			geom,
	Bounding alter &			bounding) {

	switch (geom->type) {
		case _hoops_SGCP: {
			_hoops_PHPIR const *		_hoops_HGSSR = (_hoops_PHPIR const *)geom;

			_hoops_CAIS	sphere;
			sphere.center = _hoops_HGSSR->center;
			sphere.radius = _hoops_HGSSR->radius;

			bounding = Bounding::Create(sphere);
			bounding->_hoops_CGCIR = 0.1f;

			HOOPS_WORLD->_hoops_HSRGH++;
		}	break;

		case _hoops_RIIP: {
			if (BIT (geom->_hoops_RRHH, _hoops_RGGGA)) {
				_hoops_SSSSR const *		_hoops_GCCHH = (_hoops_SSSSR *) geom;

				bounding = Bounding::Create(3, _hoops_GCCHH->points);
				bounding->_hoops_CGCIR = 0.05f;

				HOOPS_WORLD->_hoops_HSRGH++;
				break;
			}
			/* _hoops_HSSC _hoops_RHIR _hoops_IS _hoops_PHIGR _hoops_AGIR */
		}	_hoops_HHHI;

		case _hoops_GRCP:
		case _hoops_RRCP: {
			if (BIT (geom->_hoops_RRHH, _hoops_SHHI)) {
				Circular_Arc_Lite const *	_hoops_RCCHH = (Circular_Arc_Lite *) geom;

				_hoops_SASC				cuboid;

				cuboid.min.z = cuboid.max.z = 0.0f;

				if ((_hoops_RCCHH->_hoops_PHHI - _hoops_RCCHH->arc_start) >= 0.5f) {
					cuboid.min.x = _hoops_RCCHH->center.x - _hoops_RCCHH->radius;
					cuboid.max.x = _hoops_RCCHH->center.x + _hoops_RCCHH->radius;
					cuboid.min.y = _hoops_RCCHH->center.y - _hoops_RCCHH->radius;
					cuboid.max.y = _hoops_RCCHH->center.y + _hoops_RCCHH->radius;
				}
				else {
					Point			start, end;
					float			_hoops_GGHCR, _hoops_AGHCR;
					Point			center;
					float			_hoops_ARGCR, radius;

					_hoops_RICH (_hoops_RCCHH->arc_start * 360.0f, _hoops_GGHCR, _hoops_AGHCR);
					start.x = _hoops_RCCHH->center.x + _hoops_AGHCR * _hoops_RCCHH->radius;
					start.y = _hoops_RCCHH->center.y + _hoops_GGHCR   * _hoops_RCCHH->radius;

					_hoops_RICH (_hoops_RCCHH->_hoops_PHHI * 360.0f, _hoops_GGHCR, _hoops_AGHCR);
					end.x = _hoops_RCCHH->center.x + _hoops_AGHCR * _hoops_RCCHH->radius;
					end.y = _hoops_RCCHH->center.y + _hoops_GGHCR   * _hoops_RCCHH->radius;

					center.x = (start.x + end.x) * 0.5f;
					center.y = (start.y + end.y) * 0.5f;

					_hoops_ARGCR = start.x - center.x;
					radius = _hoops_ARGCR * _hoops_ARGCR;
					_hoops_ARGCR = start.y - center.y;
					radius += _hoops_ARGCR * _hoops_ARGCR;
					radius = _hoops_SGIHR (radius);

					cuboid.min.x	= center.x - radius;
					cuboid.max.x = center.x + radius;
					cuboid.min.y = center.y - radius;
					cuboid.max.y = center.y + radius;

					if (geom->type == _hoops_RRCP) {
						center.x = _hoops_RCCHH->center.x;
						center.y = _hoops_RCCHH->center.y;
						center.z = 0.0f;
						cuboid.Merge (1, &center);
					}
				}

				bounding = Bounding::Create(cuboid);
				bounding->_hoops_CGCIR = 0.8f;
			}
			else {
				Circular_Arc const	*arc = (Circular_Arc const *)geom;

				if ((arc->_hoops_PHHI - arc->arc_start) >= 0.5f) {
					_hoops_CAIS	sphere;
					sphere.center = arc->center;
					sphere.radius = arc->radius;

					bounding = Bounding::Create(sphere);
					bounding->_hoops_CGCIR = 0.1f;
				}
				else {
					_hoops_CAIS	sphere;

					sphere.center.x = (arc->start.x + arc->end.x) * 0.5f;
					sphere.center.y = (arc->start.y + arc->end.y) * 0.5f;
					sphere.center.z = (arc->start.z + arc->end.z) * 0.5f;

					float	_hoops_ARGCR, radius;

					_hoops_ARGCR = arc->start.x - sphere.center.x;
					radius = _hoops_ARGCR * _hoops_ARGCR;
					_hoops_ARGCR = arc->start.y - sphere.center.y;
					radius += _hoops_ARGCR * _hoops_ARGCR;
					_hoops_ARGCR = arc->start.z - sphere.center.z;
					radius += _hoops_ARGCR * _hoops_ARGCR;

					sphere.radius = _hoops_SGIHR (radius);

					if (geom->type == _hoops_RRCP)
						sphere.Merge (1, &arc->center);

					bounding = Bounding::Create(sphere);
					bounding->_hoops_CGCIR = 0.1f;
				}
			}

			HOOPS_WORLD->_hoops_HSRGH++;
		}	break;


		case _hoops_HGPGR: {
			return false;
		}	_hoops_HHHI;


		case _hoops_ASIP: {
			Cylinder const *		cylinder = (Cylinder const *)geom;

			_hoops_CAIS			sphere;
			sphere.center.x = 0.5f * (cylinder->axis[0].x + cylinder->axis[1].x);
			sphere.center.y = 0.5f * (cylinder->axis[0].y + cylinder->axis[1].y);
			sphere.center.z = 0.5f * (cylinder->axis[0].z + cylinder->axis[1].z);

			float					length, tmp;
			tmp = cylinder->axis[1].x - cylinder->axis[0].x;
			length = tmp * tmp;
			tmp = cylinder->axis[1].y - cylinder->axis[0].y;
			length += tmp * tmp;
			tmp = cylinder->axis[1].z - cylinder->axis[0].z;
			length += tmp * tmp;		/* _hoops_RRAA _hoops_IIGR _hoops_SPCC */
			length *= 0.25f;			/* _hoops_RRAA _hoops_IIGR _hoops_HHAA _hoops_SPCC */

			length += cylinder->radius * cylinder->radius;

			sphere.radius = _hoops_SGIHR (length);

			bounding = Bounding::Create(sphere);
			bounding->_hoops_CGCIR = 0.5f;

			HOOPS_WORLD->_hoops_HSRGH++;
		}	break;


		case _hoops_CSIP: {
			PolyCylinder const *	polycylinder = (PolyCylinder const *)geom;

			if (BIT(polycylinder->_hoops_CPGPR, _hoops_AHSGA)) {
				Bounding alter & b = (Bounding alter &)polycylinder->bounding;

				b = Bounding::Create(polycylinder->point_count, polycylinder->points);

				if (!polycylinder->bounding._hoops_HICAR()) {
					float const & displacement = polycylinder->_hoops_PCCSA;
					Vector _hoops_ACCHH(displacement, displacement, displacement);

					b->cuboid.min -= _hoops_ACCHH;
					b->cuboid.max += _hoops_ACCHH;
					b->sphere.radius += displacement;

					_hoops_GICHH ((PolyCylinder alter *)polycylinder);
				}
				HOOPS_WORLD->_hoops_HSRGH++;
			}

			bounding = polycylinder->bounding;
		}	break;


		case _hoops_HSIP: {
			Sphere const *			sphere = (Sphere const *)geom;

			bounding = Bounding::Create(sphere->data);
			bounding->_hoops_CGCIR = 1.0f;

			HOOPS_WORLD->_hoops_HSRGH++;
		}	break;


		case _hoops_CGCP: {
			Ellipse const *			ellipse = (Ellipse const *)geom;

			float	_hoops_PCCHH = Vector(ellipse->major - ellipse->center).length();
			float	_hoops_HCCHH = Vector(ellipse->minor - ellipse->center).length();

			_hoops_CAIS	sphere;
			sphere.center = ellipse->center;
			sphere.radius = _hoops_IAAA (_hoops_PCCHH, _hoops_HCCHH);

			bounding = Bounding::Create(sphere);
			bounding->_hoops_CGCIR = 0.1f;

			HOOPS_WORLD->_hoops_HSRGH++;
		}	break;

		case _hoops_GIIP: {
			Elliptical_Arc const *	_hoops_ICCHH = (Elliptical_Arc const *)geom;
			Point					points[128];
			int						count;

			count = _hoops_SHCHH (_hoops_ICCHH, 100, points);

			bounding = Bounding::Create(count, points);

			bounding->_hoops_CGCIR = 0.05f;
			HOOPS_WORLD->_hoops_HSRGH++;
		}	break;


		case _hoops_GGCP: {
			Grid const *			grid = (Grid const *)geom;
			Point					points[64];
			int						count;

			if (grid->_hoops_APIAA == _hoops_PPIAA) {
				int					_hoops_AIGCR = Abs (grid->count1);
				int					_hoops_PIGCR = Abs (grid->count2);
				Vector				_hoops_ISPI, _hoops_CSPI;

				count = 4;

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
			}
			else {
				int					_hoops_AIGCR = grid->count1,
									_hoops_PIGCR = grid->count2;
				float				start, end, _hoops_RAHCR, increment;
				float				_hoops_GGHCR, _hoops_AGHCR;
				Point *				pl;

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
			}

			bounding = Bounding::Create(count, points);
			bounding->_hoops_CGCIR = 0.1f;

			/* _hoops_RGR _hoops_IRHS _hoops_IS _hoops_SHH _hoops_CGHI _hoops_PGGA _hoops_CCCHH::_hoops_GISA() _hoops_HRSCA _hoops_RH _hoops_RIP */
			/* _hoops_PPR _hoops_RGR _hoops_HRGR _hoops_HAHH _hoops_IS _hoops_CRHR _hoops_IRS _hoops_SCCHH _hoops_GGR _hoops_RH _hoops_HCHSR _hoops_SRHR _hoops_RRGR */
			if (grid->count1 == 0 ||
				grid->_hoops_APIAA == _hoops_PPIAA && grid->count2 == 0)
				bounding->flags |= Bounding_TRANSFORM_DEPENDENT;

			HOOPS_WORLD->_hoops_HSRGH++;
		}	break;

		case _hoops_HGCP: {
			Image const *		image = (Image const *)geom;

			bounding = Bounding::Create(1, &image->_hoops_CSAI);
			bounding->flags = _hoops_IGCIR;
			bounding->_hoops_CGCIR = 0.1f;

			HOOPS_WORLD->_hoops_HSRGH++;
		}	break;


		case _hoops_ICIP: {
			_hoops_SHPIR const *	light = (_hoops_SHPIR const *)geom;	// _hoops_RGAR _hoops_AHSIR _hoops_CCAC _hoops_SS

			if (light->_hoops_PRR != _hoops_S)
				return false;

			bounding = Bounding::Create(light->count, light->points);
			bounding->_hoops_CGCIR = 0.1f;

			HOOPS_WORLD->_hoops_HSRGH++;
		}	break;


		case _hoops_PCIP: {
			Marker const *	marker = (Marker const *)geom;

			bounding = Bounding::Create(1, &marker->_hoops_CSAI);
			bounding->_hoops_CGCIR = 0.01f;

			HOOPS_WORLD->_hoops_HSRGH++;
		}	break;

		case _hoops_PIRS: {
			_hoops_GRPGR const *		_hoops_CPAI = (_hoops_GRPGR const *)geom;

			if (_hoops_CPAI->count == 0)
				return false;

			int count = _hoops_CPAI->count;

			bounding = Bounding::Create(_hoops_CPAI->count, _hoops_CPAI->points);

			bounding->_hoops_CGCIR = _hoops_AHIA (0.01f * count, 0.10f);

			HOOPS_WORLD->_hoops_HSRGH++;
		}	break;


		case _hoops_GSIP:
		case _hoops_SCIP: {
			Polyhedron const *		_hoops_IPRI = (Polyhedron alter *)geom;

			if (BIT(_hoops_IPRI->_hoops_CPGPR, _hoops_AHSGA)) {
				/* _hoops_PAGA: _hoops_ICIC _hoops_IS _hoops_HIIC _hoops_IASC _hoops_IS "_hoops_IHAH" _hoops_SCH _hoops_GPP _hoops_CPHAR */
				Bounding alter &		_hoops_CPAIA = (Bounding alter &)_hoops_IPRI->bounding;

				_hoops_CPAIA = Bounding::Create(_hoops_IPRI->point_count, _hoops_IPRI->points);

				if (!_hoops_IPRI->bounding._hoops_HICAR())
					_hoops_PICHH ((Polyhedron alter *)_hoops_IPRI);

				if (_hoops_IPRI->_hoops_HGAIR != null) {
					for (int i = 0; i < _hoops_IGAIR; i++) {
						Geometry const *	geometry;

						if ((geometry = _hoops_IPRI->_hoops_HGAIR->data[i]) != null) do {
							Bounding		_hoops_HSIGA;

							if (HI_Figure_Geometry_Bounding (geometry, _hoops_HSIGA))
								_hoops_CPAIA.Merge (_hoops_HSIGA);
						} while ((geometry = geometry->next) != null);
					}
				}
				HOOPS_WORLD->_hoops_HSRGH++;
			}

			bounding = _hoops_IPRI->bounding;
		}  break;


		case _hoops_RCIP: {
			Polygon const *			polygon = (Polygon const *)geom;

			if (polygon->count == 0)
				return false;

			bounding = Bounding::Create(polygon->count, polygon->points);
			bounding->_hoops_CGCIR = 0.5f;

			HOOPS_WORLD->_hoops_HSRGH++;
		}	break;


		case _hoops_SIIP:
		case _hoops_HIIP:
		case _hoops_IIIP: {
			Polyline const *		polyline = (Polyline const *)geom;

			if (polyline->count == 0)
				return false;

			int count = Abs(polyline->count);

			bounding = Bounding::Create(polyline->count, polyline->points);

			if (polyline->type == _hoops_SIIP)
				bounding->flags = Bounding_TRANSFORM_DEPENDENT;

			bounding->_hoops_CGCIR = _hoops_AHIA (0.01f * count, 0.25f);

			HOOPS_WORLD->_hoops_HSRGH++;
		}	break;


		case _hoops_PIIP: {
			Line const *			line = (Line const *)geom;

			bounding = Bounding::Create(2, line->points);
			bounding->_hoops_CGCIR = 0.02f;

			HOOPS_WORLD->_hoops_HSRGH++;
		}	break;


		case _hoops_CHIP: {
#ifndef _hoops_CCPIR
			_hoops_PIRGR const *		curve = (_hoops_PIRGR *)geom;
			Polyline				polyline;
			_hoops_PARC		control;

			/* _hoops_ARP _hoops_GH _hoops_SHIR _hoops_HSH. */
			control._hoops_PPPI = 32;
			control._hoops_HPPI = 0;
			control._hoops_IPPI = 0;
			control._hoops_CPPI = 20;
			control._hoops_SPPI = 1;
			control._hoops_SAR = false;

			if (curve->control_point_count == 0)
				return false;

			if (curve->_hoops_RRHH & _hoops_CHIAA) {
				HI_Generate_NURBS_Polyline (curve, &control, null, &polyline, 0);
				bounding = Bounding::Create(curve->polyline.count, curve->polyline.points);
				FREE_ARRAY (polyline.points, polyline.allocated, Point);
			}
			else {
				bounding = Bounding::Create(curve->control_point_count, curve->control_points);
			}

			if (!bounding._hoops_HICAR())
				bounding->_hoops_CGCIR = 0.1f;

			HOOPS_WORLD->_hoops_HSRGH++;
#endif
		}	break;


		case HK_STRING_CURSOR: {
			return false;
		}	_hoops_HHHI;


		case _hoops_PRCP: {
#ifndef _hoops_GSPIR
			_hoops_APPGR alter *surface = (_hoops_APPGR *)geom;

			if (surface->_hoops_SHIAA & _hoops_GIIAA) {
				_hoops_IPR (HEC_SURFACE, HES_PROCEDURAL_ERROR,
							"Figure_Geometry_Bounding: negative weights for NURBS Surface not handled");
				return false;
			}

			if (surface->n_u_vertices * surface->n_v_vertices == 0)
				return false;

			bounding =  Bounding::Create (surface->n_u_vertices * surface->n_v_vertices, surface->control_points);

			HOOPS_WORLD->_hoops_HSRGH++;
#endif
		}	break;

		case _hoops_AGCP: {
			_hoops_HACC const *			text = (_hoops_HACC const *)geom;

			bounding = Bounding::Create(1, &text->_hoops_CSAI);
			bounding->flags = _hoops_HGCIR;
			bounding->_hoops_CGCIR = 0.05f;

			HOOPS_WORLD->_hoops_HSRGH++;
		}	break;


		case _hoops_AHIP: {
			_hoops_PHIP alter *	_hoops_RRA = (_hoops_PHIP alter *)geom;

			if (_hoops_RRA->bounding == null) {
				Bounding		_hoops_GAIHA;

				if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
					_hoops_CRCP const *			_hoops_SRCP = (_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0];
					Geometry const *		geometry;

					if (_hoops_SRCP->_hoops_HSRIR && _hoops_RRA->_hoops_RGPGR == ~0)
						_hoops_GAIHA = _hoops_SRCP->_hoops_HSRIR;
					else {
						if ((geometry = _hoops_SRCP->geometry) != null) do {
							if (!BIT (_hoops_RRA->_hoops_RGPGR, _hoops_AGPGR(geometry->type))) {
								_hoops_PGPGR (geometry, geometry->type);
								if (geometry == null)
									break;
							}
							else {
								Bounding		_hoops_HSIGA;

								if (HI_Figure_Geometry_Bounding (geometry, _hoops_HSIGA))
									_hoops_GAIHA.Merge (_hoops_HSIGA);
							}
						} while ((geometry = geometry->next) != null);
					}
				}
				else {
					for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++) {
						Bounding			_hoops_HSIGA;
						Geometry const *	g = (Geometry const *)_hoops_RRA->_hoops_IHIP[i];

						if (_hoops_AGPGR(g->type) & _hoops_RRA->_hoops_RGPGR &&
							HI_Figure_Geometry_Bounding (g, _hoops_HSIGA))
								_hoops_GAIHA.Merge (_hoops_HSIGA);
					}
				}

				_hoops_RRA->bounding = _hoops_GAIHA;
				HOOPS_WORLD->_hoops_HSRGH++;
			}


			bounding = _hoops_RRA->bounding;

			if (!_hoops_RRA->bounding._hoops_HICAR()) {
				if (_hoops_RRA->_hoops_IPPGR != null) {
					Attribute *		_hoops_PSACR = null;

					HI_Gather_Modelling (_hoops_RRA->_hoops_IPPGR, &_hoops_PSACR);

					if (_hoops_PSACR != null) {
						bounding = _hoops_RRA->bounding._hoops_SCIS (&((_hoops_ISGI *)_hoops_PSACR)->matrix.elements[0][0]);
						_hoops_HPRH (_hoops_PSACR);
					}
				}
			}
			/* _hoops_RGR _hoops_PAH _hoops_IHPS _hoops_RPP _hoops_RH _hoops_CGRPR _hoops_RSSA _hoops_RGAR _hoops_IS _hoops_CGSI _hoops_SIHH _hoops_IASC _hoops_SHHRR
			 * (_hoops_IH _hoops_PCAI, _hoops_IRS _hoops_CAGH _hoops_IIAAR _hoops_RGAR _hoops_SS _hoops_PAR _hoops_HPPA _hoops_GHC) */
			if (bounding._hoops_HICAR())
				return false;
		}	break;


		case _hoops_HCIIR: //_hoops_RHGC _hoops_IASC
		case _hoops_GHPGR: {
			return false;
		}	_hoops_HHHI;


		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Unknown geometry type");
			return false;
		}	_hoops_HHHI;
	}

	return true;
}

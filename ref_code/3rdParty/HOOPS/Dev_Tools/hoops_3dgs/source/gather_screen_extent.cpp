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
 * $Id: obf_tmp.txt 1.65 2010-10-06 19:16:28 jason Exp $
 */


#include "hoops.h"
#include "driver.h"
#include "database.h"
#include "phedron.h"
#include "patterns.h"
#include "please.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

#ifndef DISABLE_COMPUTE

local void _hoops_HIRHH (
	Net_Rendition const & 		nr,
	Text_Info const *			_hoops_IIRHH) {
	Text_Info alter *			ti = (Text_Info alter *)_hoops_IIRHH;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	float						_hoops_CIRHH = _hoops_HRCIR->font->_hoops_ISISR;
	_hoops_SASC alter &		cuboid = *dc->_hoops_HAHGH;

	float	_hoops_GGHCR, _hoops_AGHCR;
	_hoops_RICH (_hoops_HRCIR->_hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR);
	float	slant_extra = _hoops_CIRHH * _hoops_GGHCR / _hoops_AGHCR;

	if (BIT (_hoops_HRCIR->transform, FT_POSITION_ONLY)) {
		Vector		_hoops_CHPSP;

		_hoops_CHPSP.x = _hoops_CIRHH * ti->_hoops_CHPSP.x + slant_extra * ti->_hoops_CHPSP.y;
		_hoops_CHPSP.y = _hoops_CIRHH * ti->_hoops_CHPSP.y + slant_extra * ti->_hoops_CHPSP.x;
		_hoops_CHPSP.z = 0.0f;

		for (int i=0; i<ti->_hoops_SIHSA.length; i++) {
			float			width = HD_Compute_Character_Width (nr, ti, i);

			Vector			_hoops_GAGCR;
			_hoops_GAGCR.x = ti->_hoops_GHPSP.x * width;
			_hoops_GAGCR.y = ti->_hoops_GHPSP.y * width;
			_hoops_GAGCR.z = 0;

			Point const *	p;
			p = HD_Compute_Character_Position (nr, ti, i);
			p = HD_Compute_Transformed_Text_Position (nr, ti, p);

			if (p != null) {
				Point	box[4];
				box[0].x = p->x;
				box[0].y = p->y;
				box[0].z = p->z;
				box[1].x = box[0].x + _hoops_GAGCR.x;
				box[1].y = box[0].y + _hoops_GAGCR.y;
				box[1].z = box[0].z + _hoops_GAGCR.z;
				box[2].x = box[0].x + _hoops_GAGCR.x + _hoops_CHPSP.x;
				box[2].y = box[0].y + _hoops_GAGCR.y + _hoops_CHPSP.y;
				box[2].z = box[0].z + _hoops_GAGCR.z + _hoops_CHPSP.z;
				box[3].x = box[0].x + _hoops_CHPSP.x;
				box[3].y = box[0].y + _hoops_CHPSP.y;
				box[3].z = box[0].z + _hoops_CHPSP.z;
				cuboid.Merge(4, box);
			}
		}
	}
	else {
		Point	box[4];
		box[0].x = ti->position.x;
		box[0].y = ti->position.y;
		box[0].z = ti->position.z;
		box[1].x = ti->position.x + ti->_hoops_HHPSP.x;
		box[1].y = ti->position.y + ti->_hoops_HHPSP.y;
		box[1].z = ti->position.z + ti->_hoops_HHPSP.z;
		box[2].x = ti->position.x + ti->_hoops_HHPSP.x + _hoops_CIRHH * ti->_hoops_CHPSP.x;
		box[2].y = ti->position.y + ti->_hoops_HHPSP.y + _hoops_CIRHH * ti->_hoops_CHPSP.y;
		box[2].z = ti->position.z + ti->_hoops_HHPSP.z + _hoops_CIRHH * ti->_hoops_CHPSP.z;
		box[3].x = ti->position.x + _hoops_CIRHH * ti->_hoops_CHPSP.x;
		box[3].y = ti->position.y + _hoops_CIRHH * ti->_hoops_CHPSP.y;
		box[3].z = ti->position.z + _hoops_CIRHH * ti->_hoops_CHPSP.z;

		if (_hoops_HRCIR->transform == FT_FULL) {
			for (int i=0; i<4; ++i) {
				Point const * p = HD_Compute_Transformed_Text_Position (nr, ti, &box[i]);

				if (p != null) {
					box[i].x = p->x;
					box[i].y = p->y;
					box[i].z = p->z;
					cuboid.Merge(1, &box[i]);
				}
			}
		}
		else
			cuboid.Merge(4, box);
	}
}

local void _hoops_SIRHH (
	Net_Rendition const & 		nr,
	_hoops_HACC const *				text,
	_hoops_SASC alter &		cuboid) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_SSCGA		_hoops_GCRHH = dc->_hoops_IPCI->_hoops_CSCGA;

	dc->_hoops_IPCI->_hoops_CSCGA = _hoops_HIRHH;
	dc->_hoops_HAHGH = &cuboid;
	/* _hoops_CGH _hoops_SHH _hoops_ICIC _hoops_IS _hoops_GRPHA _hoops_SSPP _hoops_GPP _hoops_RGR _hoops_IPP */
	((_hoops_IGCSR alter &)nr->_hoops_SISI)->_hoops_HCPAP = 0.0f;
	((_hoops_IGCSR alter &)nr->_hoops_SISI)->_hoops_CRPSP = true;

	HD_Std_3D_Text (nr, text);

	dc->_hoops_IPCI->_hoops_CSCGA = _hoops_GCRHH;
	dc->_hoops_HAHGH = null;
}




local void _hoops_IGARH (
	Net_Rendition alter &	nr,
	_hoops_CRCP const *			_hoops_SRCP,
	bool					_hoops_RCRHH) {
	Display_Context const *	dc = nr->_hoops_SRA;
	Attribute const *		_hoops_HPHCR;

	if (_hoops_SRCP != HOOPS_WORLD->root && _hoops_RCRHH) {
		while (_hoops_SRCP->_hoops_IPPGR == null) {
			_hoops_SRCP = (_hoops_CRCP const *)_hoops_SRCP->owner;
			if ((_hoops_CRCP const *)_hoops_SRCP == HOOPS_WORLD->root) break;
		}

		if (_hoops_SRCP != HOOPS_WORLD->root)
			_hoops_IGARH (nr, (_hoops_CRCP const *)_hoops_SRCP->owner, true);
	}

	if (_hoops_SRCP == dc->_hoops_AAHSR) {
		_hoops_HRPA			_hoops_RHSPR;

		HD_Undo_Screen (nr, &_hoops_RHSPR);
		HD_Calculate_Outer_Window (nr);
		nr->transform_rendition->flags |= _hoops_PRAIP;
		HD_Redo_Screen (nr, &_hoops_RHSPR);
	}

	if ((_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR) != null)
		HD_Downwind_Rendition (nr, _hoops_SRCP->_hoops_IPPGR, (_hoops_SRCP == HOOPS_WORLD->root) ? _hoops_CAHGP : _hoops_SRCP->_hoops_RCGC, true);
}



local int _hoops_IGIAA (
	Point const *			center,
	Vector const *			_hoops_GGHI,
	Vector const *			_hoops_RGHI,
	int						count,
	Point alter *			pl) {
	int						ii;
	int						count2 = count / 2;
	float					theta = 90.0f;
	float					delta = 360.0f / (float)count;

	ii = count2 / 2;
	do {
		float			s, t;
		float			_hoops_CGIAA;
		float			_hoops_SGIAA;
		Point alter	*	_hoops_GGIAR = &pl[ii];
		Point alter	*	p1 = &pl[count2-ii];
		Point alter	*	p2 = &pl[count2+ii];
		Point alter	*	_hoops_IAPH = &pl[count-ii];

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

	return count + 1;
}


local bool _hoops_ACRHH (
	Net_Rendition const &		nr,
	Geometry const *			geometry,
	bool						_hoops_PISAA,
	bool						_hoops_PCRHH,
	Bounding alter &			bounding) {
	int							mask = nr->_hoops_RGPGR;
	int							count = 0;
	Point *						points = null;
	int							allocated = 0;
	float const *				matrix;
	_hoops_ACHR					_hoops_RGP;

	if (geometry->type == _hoops_AHIP) {
		_hoops_PHIP const *	_hoops_RRA = (_hoops_PHIP const *)geometry;
		Net_Rendition				_hoops_SSGS = nr;

		if (_hoops_RRA->condition.count > 0 &&
			!HI_Condition_Passed (nr->_hoops_ASIR->conditions.count,
								  nr->_hoops_ASIR->conditions._hoops_RCHA,
								  &_hoops_RRA->condition)) {
			/* _hoops_HAR _hoops_SPR _hoops_SR _hoops_HHGC */
			return true;
		}

		if (_hoops_RRA->_hoops_IPPGR != null)
			HD_Downwind_Rendition (_hoops_SSGS, _hoops_RRA->_hoops_IPPGR, _hoops_CAHGP, true);

		if (_hoops_RRA->_hoops_RGPGR != ~0 && _hoops_RRA->_hoops_RGPGR != mask)
			_hoops_SSGS.Modify()->_hoops_RGPGR &= _hoops_RRA->_hoops_RGPGR|_hoops_AGPGR(_hoops_AHIP);


		if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
			_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0];

			if ((geometry = _hoops_SRCP->geometry) != null) do {
				if (!_hoops_ACRHH (_hoops_SSGS, geometry, _hoops_PISAA, _hoops_PCRHH, bounding))
					return false;
			} while ((geometry = geometry->next) != null);
			return true;
		}
		else {
			for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++)
				if (!_hoops_ACRHH (_hoops_SSGS, (Geometry const *)_hoops_RRA->_hoops_IHIP[i], _hoops_PISAA, _hoops_PCRHH, bounding))
					return false;
			return true;
		}
	}

	matrix = &nr->transform_rendition->matrix->data.elements[0][0];
	_hoops_RGP = nr->_hoops_RGP;

	if (BIT (mask, _hoops_AGPGR (geometry->type))) switch (geometry->type) {
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

			ALLOC_ARRAY (points, 105, Point);
			allocated = 105;
			count = HI_Generate_Elliptical_Points ((_hoops_GHHI const *)geometry,
												   100, points);
		}	break;

		case _hoops_SGCP:
		case _hoops_GRCP:
		case _hoops_RRCP:
		case _hoops_CGCP: {
			if (!ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE))
				return true;

			ALLOC_ARRAY (points, 105, Point);
			allocated = 105;
			count = HI_Generate_Elliptical_Points ((_hoops_GHHI const *)geometry,
												   100, points);
		}		break;

		case _hoops_ASIP: {
			Cylinder const *	cylinder = (Cylinder const *)geometry;
			Vector				axis[2];

			if (!ANYBIT (_hoops_RGP, T_FACES|T_ANY_SHELL_EDGE))
				return true;

			ALLOC_ARRAY (points, 84, Point);
			allocated = 84;

			axis[0].x = cylinder->_hoops_CSPIR.axis[0].x * cylinder->radius;
			axis[0].y = cylinder->_hoops_CSPIR.axis[0].y * cylinder->radius;
			axis[0].z = cylinder->_hoops_CSPIR.axis[0].z * cylinder->radius;
			axis[1].x = cylinder->_hoops_CSPIR.axis[1].x * cylinder->radius;
			axis[1].y = cylinder->_hoops_CSPIR.axis[1].y * cylinder->radius;
			axis[1].z = cylinder->_hoops_CSPIR.axis[1].z * cylinder->radius;

			_hoops_IGIAA (&cylinder->axis[0],
									  &axis[0],
									  &axis[1],
									  40, &points[0]);
			_hoops_IGIAA (&cylinder->axis[1],
									  &axis[0],
									  &axis[1],
									  40, &points[40]);
			count = 80;
		}	break;

		case _hoops_CSIP: {
			PolyCylinder const *	polycylinder = (PolyCylinder const *)geometry;
			int						ii;

			if (!ANYBIT (_hoops_RGP, T_FACES|T_ANY_SHELL_EDGE))
				return true;

			allocated = count = 24 * polycylinder->point_count + 1;
			ALLOC_ARRAY (points, count, Point);

			for (ii=0; ii<polycylinder->point_count; ii++) {
				Vector			axis[2];
				float			radius;

				radius = polycylinder->radii[ii % polycylinder->_hoops_ISPIR];

				axis[0].x = polycylinder->_hoops_CSPIR[ii].axis[0].x * radius;
				axis[0].y = polycylinder->_hoops_CSPIR[ii].axis[0].y * radius;
				axis[0].z = polycylinder->_hoops_CSPIR[ii].axis[0].z * radius;
				axis[1].x = polycylinder->_hoops_CSPIR[ii].axis[1].x * radius;
				axis[1].y = polycylinder->_hoops_CSPIR[ii].axis[1].y * radius;
				axis[1].z = polycylinder->_hoops_CSPIR[ii].axis[1].z * radius;

				_hoops_IGIAA (&polycylinder->points[ii],
										  &axis[0],
										  &axis[1],
										  24, &points[24*ii]);
			}
		}	break;

#define _hoops_HCRHH 10
		case _hoops_HSIP: {
			Sphere const *		sphere = (Sphere const *)geometry;
			int					ii, _hoops_ICRHH;
			float				theta, phi, _hoops_IGHCP, _hoops_CCRHH;

			if (!ANYBIT (_hoops_RGP, T_FACES|T_ANY_SHELL_EDGE))
				return true;

			allocated = count = _hoops_HCRHH*_hoops_HCRHH;
			ALLOC_ARRAY (points, count, Point);
			_hoops_IGHCP = (2 * 3.14159f) / _hoops_HCRHH;
			_hoops_CCRHH = _hoops_IGHCP / 2;
			for (theta = 0, ii = 0; ii < _hoops_HCRHH; theta += _hoops_IGHCP, ii++) {
				for (phi = 0, _hoops_ICRHH = 0; _hoops_ICRHH < _hoops_HCRHH; phi += _hoops_CCRHH, _hoops_ICRHH++) {
					points[ii*_hoops_HCRHH + _hoops_ICRHH].x = (float) ((sin(phi) * cos(theta)) * sphere->data.radius) + sphere->data.center.x;
					points[ii*_hoops_HCRHH + _hoops_ICRHH].y = (float) ((sin(phi) * sin(theta)) * sphere->data.radius) + sphere->data.center.y;
					points[ii*_hoops_HCRHH + _hoops_ICRHH].z = (float) ((cos(phi)) * sphere->data.radius) + sphere->data.center.z;
				}
			}
		}	break;

		case _hoops_GGCP: {
			Grid const *		grid = (Grid const *)geometry;

			if (!ANYBIT (_hoops_RGP, T_FACES|T_ANY_GRID_EDGE|T_VERTICES))
				return true;

			if (grid->_hoops_APIAA == _hoops_PPIAA) {
				int				_hoops_AIGCR = Abs (grid->count1);
				int				_hoops_PIGCR = Abs (grid->count2);
				Vector			_hoops_ISPI, _hoops_CSPI;

				ALLOC_ARRAY (points, 4, Point);
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
					bounding->flags |= Bounding_TRANSFORM_DEPENDENT;
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

				ALLOC_ARRAY (points, 64, Point);
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
					bounding->flags |= Bounding_TRANSFORM_DEPENDENT;
			}
		}	break;


		case _hoops_HGCP: {
			if (!BIT (_hoops_RGP, T_IMAGES))
				return true;

			Image const *		image = (Image const *)geometry;
			Point				tmp[2];

			HI_Compute_Transformed_Points (1, &image->_hoops_CSAI,
										   matrix, &tmp[1]);

			tmp[0].x = tmp[1].x - image->width / 2;
			tmp[0].y = tmp[1].y - image->height / 2;
			tmp[0].z = tmp[1].z;
			tmp[1].x += image->width / 2;
			tmp[1].y += image->height / 2;

			bounding.Merge (2, tmp);

			count = 0;
		}	break;

		case _hoops_ICIP: {
			_hoops_SHPIR const *		light = (_hoops_SHPIR const *)geometry;	// _hoops_RGAR _hoops_AHSIR _hoops_CCAC _hoops_SS

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

			Marker const *		marker = (Marker const *)geometry;

			count = 1;
			points = (Point alter *)&marker->_hoops_CSAI;
		}	break;

		case _hoops_PIRS: {
			_hoops_GRPGR const *		_hoops_CPAI = (_hoops_GRPGR const *)geometry;

			if (!BIT (_hoops_RGP, T_MARKERS))
				return true;

			if (_hoops_CPAI->count == 0)
				return false;

			count = _hoops_CPAI->count;
			points = (Point alter *)_hoops_CPAI->points;
		}	break;

		case _hoops_GSIP:
		case _hoops_SCIP: {
			Polyhedron const *		_hoops_IPRI = (Polyhedron *)geometry;

			if (!ANYBIT (_hoops_RGP, T_FACES|T_ANY_MESH_EDGE|T_VERTICES))
				return true;

			if (_hoops_IPRI->_hoops_HGAIR != null) {
				for (int i = 0; i < _hoops_IGAIR; i++) {
					Geometry *		g = _hoops_IPRI->_hoops_HGAIR->data[i];

					while (g != null) {
						_hoops_ACRHH (nr, g, _hoops_PISAA, _hoops_PCRHH, bounding);
						g = g->next;
					}
				}
			}

			if (_hoops_PISAA) {
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
					ALLOC_ARRAY (_hoops_GHIAA, _hoops_IPRI->point_count, bool);
					ZERO_ARRAY (_hoops_GHIAA, _hoops_IPRI->point_count, bool);

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

/* _hoops_SIGP: _hoops_AHAA _hoops_CIHA _hoops_IS _hoops_HPHR _hoops_PPSR _hoops_CIHA */
									if (!_hoops_GHIAA[index]) {
										_hoops_GHIAA[index] = true;
										++count;
									}
								}
							} while ((ts = ts->next) != null);
						}
						else if (_hoops_IPRI->type == _hoops_SCIP) {
							Shell const *					_hoops_SPHPR = (Shell const *)_hoops_IPRI;
							Local_Face_Attributes const *	_hoops_CPRI = &_hoops_SPHPR->local_face_attributes;
							int const *						face_list;
							int const *						_hoops_CRRHR;
							int const *						global_end;
							int								index;
							int								face = -1;

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
					}
					if (count < _hoops_IPRI->point_count &&
						(ANYBIT (_hoops_RGP, T_EDGES) ||
						 _hoops_IPRI->_hoops_IHHPR._hoops_CPIAA != 0)) {
						if (_hoops_IPRI->_hoops_SHGPR != null) {
							Polyedge const *		pe;

							pe = _hoops_IPRI->_hoops_SHGPR;
							do {
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
							do {
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
						ALLOC_ARRAY (points, allocated, Point);

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
				}
			}

			count = _hoops_IPRI->point_count;
			points = (Point alter *)_hoops_IPRI->points;
		}  break;

		case _hoops_RCIP: {
			Polygon const *			polygon = (Polygon const *)geometry;

			if (!ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE))
				return true;

			count = polygon->count;
			points = (Point alter *)polygon->points;
		}	break;

		case _hoops_HIIP:
		case _hoops_IIIP: {
			Polyline const *		polyline = (Polyline const *)geometry;

			if (!BIT (_hoops_RGP, T_LINES))
				return true;

			if (polyline->count == 0)
				return false;

			count = Abs (polyline->count);
			points = (Point alter *)polyline->points;
		}	break;

		case _hoops_PIIP: {
			Line const *		line = (Line const *)geometry;

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

			if (curve->_hoops_RRHH & _hoops_CHIAA) {
				if (curve->polyline.points == null) {
					Polyline polyline;

					HI_Generate_NURBS_Polyline (curve, null, null, &polyline, 0);

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

			if (surface->_hoops_SHIAA & _hoops_GIIAA) {
				_hoops_IPR (HEC_SURFACE, HES_PROCEDURAL_ERROR,
							"Figure_Geometry_Bounding: negative weights for NURBS Surface not handled");
				return false;
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

			_hoops_SASC	cuboid;

			_hoops_SIRHH (nr, (_hoops_HACC *)geometry, cuboid);

			count = 0;

			if (_hoops_PCRHH && nr->transform_rendition->_hoops_HCHH != null) {
				_hoops_ASHH const *	_hoops_CRAIR = nr->transform_rendition->_hoops_HCHH->_hoops_PSHH;

				do if (!BIT (_hoops_CRAIR->flags, _hoops_RHIH)) {
					if (_hoops_CRAIR->_hoops_RCHS.left > cuboid.min.x)
						cuboid.min.x = _hoops_CRAIR->_hoops_RCHS.left;
					if (_hoops_CRAIR->_hoops_RCHS.right < cuboid.max.x)
						cuboid.max.x = _hoops_CRAIR->_hoops_RCHS.right;
					if (_hoops_CRAIR->_hoops_RCHS.bottom > cuboid.min.y)
						cuboid.min.y = _hoops_CRAIR->_hoops_RCHS.bottom;
					if (_hoops_CRAIR->_hoops_RCHS.top < cuboid.max.y)
						cuboid.max.y = _hoops_CRAIR->_hoops_RCHS.top;
				} while ((_hoops_CRAIR = _hoops_CRAIR->next) != null);

				if (cuboid.min.x < cuboid.max.x &&
					cuboid.min.y < cuboid.max.y)
					bounding.Merge (cuboid);
			}
			else
				bounding.Merge (cuboid);
		}	break;

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unknown geometry type");
			return false;
		}	_hoops_HHHI;
	}

	if (count > 0) {
		Point const			*_hoops_HRRGA = points;

		if (allocated == 0) {	/* _hoops_PAH'_hoops_RA _hoops_IIIAA, _hoops_HGCR _hoops_IRHP _hoops_IIPR */
			ALLOC_ARRAY (points, count, Point);
			allocated = count;
		}

		HI_Compute_Transformed_Points (count, _hoops_HRRGA,
									   &nr->transform_rendition->matrix->data.elements[0][0],
									   points);

		if (_hoops_PCRHH && nr->transform_rendition->_hoops_HCHH != null) {
			_hoops_ASHH const *		_hoops_CRAIR = nr->transform_rendition->_hoops_HCHH->_hoops_PSHH;

			_hoops_SASC	cuboid(count, points);

			do if (!BIT (_hoops_CRAIR->flags, _hoops_RHIH)) {
				if (_hoops_CRAIR->_hoops_RCHS.left > cuboid.min.x)
					cuboid.min.x = _hoops_CRAIR->_hoops_RCHS.left;
				if (_hoops_CRAIR->_hoops_RCHS.right < cuboid.max.x)
					cuboid.max.x = _hoops_CRAIR->_hoops_RCHS.right;
				if (_hoops_CRAIR->_hoops_RCHS.bottom > cuboid.min.y)
					cuboid.min.y = _hoops_CRAIR->_hoops_RCHS.bottom;
				if (_hoops_CRAIR->_hoops_RCHS.top < cuboid.max.y)
					cuboid.max.y = _hoops_CRAIR->_hoops_RCHS.top;
			} while ((_hoops_CRAIR = _hoops_CRAIR->next) != null);

			if (cuboid.min.x < cuboid.max.x && cuboid.min.y < cuboid.max.y)
				bounding.Merge (cuboid);
		}
		else
			bounding.Merge (count, points);

		if (allocated != 0)
			FREE_ARRAY (points, allocated, Point);
	}

	return true;
}


local bool _hoops_RRCAA (
	Net_Rendition const &		nr,
	_hoops_CRCP const *				segment,
	bool						_hoops_PISAA,
	bool						_hoops_PCRHH,
	Bounding alter &			bounding) {
	Geometry const *			geometry;
	Subsegment const *			_hoops_SSGPR;

	if ((geometry = segment->geometry) != null) do {
		if (!_hoops_ACRHH (nr, geometry, _hoops_PISAA, _hoops_PCRHH, bounding))
			return false;
	} while ((geometry = geometry->next) != null);


	if ((_hoops_SSGPR = segment->_hoops_RGRPR) != null) do {
		_hoops_CRCP const *			_hoops_SRCP = _hoops_SSIGP (_hoops_SSGPR);
		bool					process = true;

		if (_hoops_SRCP->_hoops_IPPGR != null) {
			Attribute const *	_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR;

			do {
				if (_hoops_HPHCR->type > HK_HEURISTICS)
					break;

				if (_hoops_HPHCR->type == HK_HEURISTICS) {
					_hoops_GHAIR const *	_hoops_GIGC = (_hoops_GHAIR const *)_hoops_HPHCR;

					if (BIT (_hoops_GIGC->mask & _hoops_GIGC->value, _hoops_CCIAA)) {
						process = false;
						break;
					}
				}
			} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
		}

		if (process) {
			Net_Rendition		_hoops_PPHIP = nr;

			if (_hoops_SRCP->_hoops_IPPGR != null)
				HD_Downwind_Rendition (_hoops_PPHIP, _hoops_SRCP->_hoops_IPPGR, _hoops_SRCP->_hoops_RCGC, true);

			_hoops_RRCAA (_hoops_PPHIP, _hoops_SRCP, _hoops_PISAA, _hoops_PCRHH, bounding);
		}
	} while ((_hoops_SSGPR = _hoops_SSGPR->next) != null);

	return true;
}
#endif


GLOBAL_FUNCTION bool HD_Gather_Screen_Extent (
	Display_Context alter *			dc,
	_hoops_RISAA alter *	_hoops_AISAA) {
	bool							_hoops_IA = false;
#ifndef DISABLE_COMPUTE
	_hoops_CRCP const *					_hoops_SRCP = _hoops_AISAA->context;
	Net_Rendition					nr;
	float							_hoops_SCRHH,
									_hoops_GSRHH;
	_hoops_CGRA				_hoops_SGRA;
	Bounding						bounding = Bounding::Create();
	bool							_hoops_PISAA = BIT (_hoops_AISAA->_hoops_PISAA, _hoops_SPIAA);
	bool							_hoops_PCRHH = !BIT (_hoops_AISAA->_hoops_PISAA, _hoops_GISAA);

	nr = Net_Rendition::Create(dc);

	if (_hoops_SRCP != null) {
		/* _hoops_RSRA _hoops_CAGH _hoops_RAGA */
		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) {		/* _hoops_ARARH */
			Subsegment const *_hoops_GIPIA;

			while ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) {
				while (_hoops_GIPIA->next != null)
					_hoops_GIPIA = _hoops_GIPIA->next;
				if (_hoops_GIPIA->type != _hoops_IRCP) break;
				_hoops_SRCP = (_hoops_CRCP const *)_hoops_GIPIA;
			}
		}

		_hoops_IGARH (nr, _hoops_SRCP, true);
	}
	else {
		/* _hoops_CAGH _hoops_CRAA _hoops_CHIA */
		_hoops_CRCP const **	_hoops_RSRHH = _hoops_AISAA->path;
		int					count = _hoops_AISAA->_hoops_CISAA;
		bool				_hoops_RCRHH = true;

		while (count-- != 0) {
			_hoops_SRCP = *_hoops_RSRHH++;

			if (_hoops_SRCP->type != _hoops_IRCP)	/* _hoops_CPAP _hoops_HPGR _hoops_RSGR _hoops_IIGR _hoops_HIGR */
				break;

			_hoops_IGARH (nr, _hoops_SRCP, _hoops_RCRHH);
			_hoops_RCRHH = false;
		}
	}

	if (_hoops_AISAA->_hoops_PPSAA) {
		nr->_hoops_RGP = nr->_hoops_IRR->_hoops_AARIP = _hoops_AISAA->_hoops_RGP;
	}

	if (_hoops_SRCP->type == _hoops_IRCP)
		_hoops_RRCAA (nr, _hoops_SRCP, _hoops_PISAA, _hoops_PCRHH, bounding);
	else
		_hoops_ACRHH (nr, (Geometry *)_hoops_SRCP, _hoops_PISAA, _hoops_PCRHH, bounding);

	_hoops_SGRA = nr->_hoops_SAIR;

	_hoops_SCRHH =	  (float)(_hoops_SGRA->_hoops_PHRA.right - _hoops_SGRA->_hoops_PHRA.left);
	_hoops_GSRHH =  (float)(_hoops_SGRA->_hoops_PHRA.top - _hoops_SGRA->_hoops_PHRA.bottom);

	if (_hoops_SCRHH == 0 || _hoops_GSRHH == 0) {
		_hoops_AISAA->left = _hoops_AISAA->bottom = -1.0f;
		_hoops_AISAA->right = _hoops_AISAA->top = 1.0f;
		_hoops_IA = true;
		goto _hoops_HPAGR;
	}


	/* _hoops_SICR _hoops_ASCR _hoops_IS _hoops_RPPS _hoops_PHGSP */

	_hoops_AISAA->left   = 2.0f * (bounding->cuboid.min.x - _hoops_SGRA->_hoops_PHRA.left) / _hoops_SCRHH - 1.0f;
	_hoops_AISAA->right  = 2.0f * (bounding->cuboid.max.x - _hoops_SGRA->_hoops_PHRA.left) / _hoops_SCRHH - 1.0f;
	_hoops_AISAA->bottom = 2.0f * (bounding->cuboid.min.y - _hoops_SGRA->_hoops_PHRA.bottom) / _hoops_GSRHH - 1.0f;
	_hoops_AISAA->top    = 2.0f * (bounding->cuboid.max.y - _hoops_SGRA->_hoops_PHRA.bottom) / _hoops_GSRHH - 1.0f;


	if (_hoops_AISAA->left < 1.0f && _hoops_AISAA->right > -1.0f &&
		_hoops_AISAA->bottom < 1.0f && _hoops_AISAA->top > -1.0f)
		_hoops_IA = true;

 _hoops_HPAGR:

	return _hoops_IA;
#else
	return false;
#endif
}

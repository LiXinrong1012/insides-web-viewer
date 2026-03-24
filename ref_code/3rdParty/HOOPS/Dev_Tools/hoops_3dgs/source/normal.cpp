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
 * $Id: obf_tmp.txt 1.72 2011-01-22 06:11:26 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


HC_INTERFACE void HC_CDECL HC_Set_Normal (
	double			dx,
	double			_hoops_CRRAR,
	double			_hoops_AAAC)
{
	_hoops_PAPPR context("Set_Normal");

#ifdef _hoops_HCGHR
	_hoops_IRPPR ("Geometry Normals");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "HC_Set_Normal (%F, %F, ", dx, _hoops_CRRAR));
		HI_Dump_Code (Sprintf_F (null, "%F);\n", _hoops_AAAC));
	);

	Vector			normal;
	Vector *		_hoops_AHAHR = null;
	bool			_hoops_SASSI = false;

	Polyhedron *	_hoops_IPRI = context->open_list->info._hoops_IPRI._hoops_IGRPR;
	int offset = context->open_list->info._hoops_IPRI.offset;

	if (_hoops_IPRI->type != _hoops_CSIP) {
		if (context->open_list != null && context->open_list->_hoops_GCRIR == _hoops_ICRIR &&
			!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
			/* _hoops_SR _hoops_CHR _hoops_AHCA _hoops_IS _hoops_ARP _hoops_IRS _hoops_GSSR _hoops_GPP _hoops_IRS _hoops_RSRA _hoops_HSP, _hoops_HIH _hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_IRS _hoops_HSP _hoops_RIP
			_hoops_CRPR _hoops_HPP _hoops_HA, _hoops_SR _hoops_RRP _hoops_SPR! */
			int i = 0;
			ZALLOC_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
			for (i = 0; i <  _hoops_IPRI->face_count; i++)
				_hoops_IPRI->local_face_attributes.flags[i] = _hoops_IPRI->local_face_attributes._hoops_SGRHR;
			_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
		}
		else if (context->open_list != null && context->open_list->_hoops_GCRIR == _hoops_SCRIR &&
			!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
			/* _hoops_SR _hoops_CHR _hoops_AHCA _hoops_IS _hoops_ARP _hoops_IRS _hoops_GSSR _hoops_GPP _hoops_IRS _hoops_RSRA _hoops_GPHA, _hoops_HIH _hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_IRS _hoops_GPHA _hoops_RIP
			_hoops_CRPR _hoops_HPP _hoops_HA, _hoops_SR _hoops_RRP _hoops_SPR! */
			int i = 0;
			ZALLOC_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
			for (i = 0; i <  _hoops_IPRI->point_count; i++)
				_hoops_IPRI->local_vertex_attributes.flags[i] = _hoops_IPRI->local_vertex_attributes._hoops_SGRHR;
			_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
		}
	}

	normal.x = (float)dx;
	normal.y = (float)_hoops_CRRAR;
	normal.z = (float)_hoops_AAAC;

	if (!HI_Normalize (&normal))
		HE_WARNING (HEC_NORMAL, HES_ZERO_LENGTH, "Normal vector is of zero or nearly zero length");

	if (context->open_list == null) {
		HE_ERROR (HEC_NORMAL, HES_OPEN_FACE_OR_VERTEX_ONLY, "Can 'set normal' only on an open face, region, or vertex");
		return;
	}
	switch (context->open_list->_hoops_GCRIR) {
		default: {
			HE_ERROR (HEC_NORMAL, HES_OPEN_FACE_OR_VERTEX_ONLY, "Can 'set normal' only on an open face, region, or vertex");
			return;
		}	_hoops_HHHI;

		case _hoops_GSRIR: {
			_hoops_GIIPR		*flags;
			_hoops_ARPA					*_hoops_HICSA;
			int const				*regions = _hoops_IPRI->local_face_attributes.regions;
			int						region = offset;
			bool					_hoops_SACRH = false;

			if (regions == null && region != 0)
				return;	/* _hoops_RSSI _hoops_GGR _hoops_SHIR _hoops_ISPH, _hoops_IAGC _hoops_HRGR _hoops_HAR */

			if (_hoops_IPRI->local_face_attributes.normals == null)
				HI_Initialize_Face_Attributes (_hoops_IPRI, LFA_EXPLICIT_NORMAL);

			for (offset=0; offset<_hoops_IPRI->face_count; offset++) {
				if (regions == null || regions[offset] == region) {
					_hoops_HICSA = &_hoops_IPRI->local_face_attributes.normals[offset];
					_hoops_AHAHR = (Vector *)_hoops_HICSA;
					flags = ((Polyhedron*)_hoops_IPRI)->local_face_attributes._hoops_CHHPR(offset);

					if (_hoops_AHAHR->x != normal.x ||
						_hoops_AHAHR->y != normal.y ||
						_hoops_AHAHR->z != normal.z) {
						_hoops_AHAHR->x = normal.x;
						_hoops_AHAHR->y = normal.y;
						_hoops_AHAHR->z = normal.z;
						_hoops_SASSI = true;
					}

					if (!BIT (*flags, LFA_EXPLICIT_NORMAL)) {
						++_hoops_IPRI->local_face_attributes.explicit_normal_count;
						*flags |= LFA_EXPLICIT_NORMAL;
						_hoops_SACRH = true;
					}
				}
			}

			if (_hoops_IPRI->local_face_attributes.lff_uniform(_hoops_IPRI->face_count)) {
				/* _hoops_SR _hoops_CHR _hoops_ISSC _hoops_IS _hoops_IRS _hoops_PIAP _hoops_CAS _hoops_RH _hoops_SGI _hoops_CHR _hoops_GHRHR, _hoops_IIS'_hoops_GRI _hoops_CIH _hoops_RH _hoops_SGI _hoops_CRPR */
				_hoops_IPRI->local_face_attributes._hoops_SGRHR = _hoops_IPRI->local_face_attributes.flags[0];
				FREE_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
				_hoops_IPRI->polyhedron_flags &= ~_hoops_APRHR;
				_hoops_IPRI->local_face_attributes.flags = 0;
			}

			if (_hoops_SACRH)
				_hoops_SASIR (context, _hoops_IPRI, _hoops_CAHRA);
		}	break;

		case _hoops_ICRIR: {
			_hoops_GIIPR		*flags;
			_hoops_ARPA					*_hoops_HICSA;

			if (_hoops_IPRI->type == _hoops_CSIP) {
				PolyCylinder		*_hoops_HSPIR = (PolyCylinder *)_hoops_IPRI;
				_hoops_SSPIR			*_hoops_CSPIR;
				Vector				axis;
				bool				_hoops_SACRH = false;
				float				matrix[16];
				Vector const *		old_normal = null;
				Vector alter *		new_normal = null;
				Vector				_hoops_GPSSI;
				float				_hoops_RAHCR;
				float				_hoops_RPSSI;

				if (offset == 0) {
					Point const *	start = &_hoops_HSPIR->points[0];
					Point const *	next = start+1;

					while (next->x == start->x &&
						   next->y == start->y &&
						   next->z == start->z) {
						++next;
					}

					axis.x = start->x - next->x;
					axis.y = start->y - next->y;
					axis.z = start->z - next->z;

					if (normal.x*axis.x + normal.y*axis.y + normal.z*axis.z < 0.0f) {
						normal.x = -normal.x;
						normal.y = -normal.y;
						normal.z = -normal.z;
					}

					if (BIT (_hoops_HSPIR->flags, _hoops_RSICA))
						old_normal = &_hoops_HSPIR->_hoops_ACCSA[0];

					_hoops_HSPIR->flags |= _hoops_RSICA;
					new_normal = &_hoops_HSPIR->_hoops_ACCSA[0];
					_hoops_CSPIR = &_hoops_HSPIR->_hoops_CSPIR[0];
				}
				else {
					Point const *		end = &_hoops_HSPIR->points[_hoops_HSPIR->point_count-1];
					Point const *		prev = end-1;

					while (prev->x == end->x &&
						   prev->y == end->y &&
						   prev->z == end->z) {
						--prev;
					}

					axis.x = end->x - prev->x;
					axis.y = end->y - prev->y;
					axis.z = end->z - prev->z;

					if (normal.x*axis.x + normal.y*axis.y + normal.z*axis.z < 0.0f) {
						normal.x = -normal.x;
						normal.y = -normal.y;
						normal.z = -normal.z;
					}

					if (BIT (_hoops_HSPIR->flags, _hoops_ASICA))
						old_normal = &_hoops_HSPIR->_hoops_ACCSA[1];

					_hoops_HSPIR->flags |= _hoops_ASICA;
					new_normal = &_hoops_HSPIR->_hoops_ACCSA[1];
					_hoops_CSPIR = &_hoops_HSPIR->_hoops_CSPIR[_hoops_HSPIR->point_count-1];
				}

				HI_Normalize (&axis);

				if (old_normal != null) {
					/* _hoops_PAISR _hoops_GII _hoops_RHGS _hoops_RGSR _hoops_RPP _hoops_HACH _hoops_GRS _hoops_SHH _hoops_HAGH */

					if (normal.x != old_normal->x ||
						normal.y != old_normal->y ||
						normal.z != old_normal->z) {
						_hoops_SACRH = true;

						HI_Compute_Cross_Product (old_normal, &axis, &_hoops_GPSSI);
						_hoops_RPSSI = (float)HI_Compute_Vector_Length (&_hoops_GPSSI);
						_hoops_RPSSI = _hoops_RPSSI*_hoops_RPSSI;
						if (_hoops_RPSSI < 1.0f)
							_hoops_RAHCR = _hoops_ISSSR (_hoops_SGIHR (1.0f - _hoops_RPSSI));
						else
							_hoops_RAHCR = 90.0f;
						if (_hoops_RAHCR != 0.0f) {
							HI_Compute_Offaxis_Rotation (_hoops_GPSSI.x, _hoops_GPSSI.y, _hoops_GPSSI.z,
														 _hoops_RAHCR, matrix);
							HI_Compute_Transformed_Points (2, (Point *)_hoops_CSPIR->axis,
														   matrix, (Point *)_hoops_CSPIR->axis);
						}
					}
				}
				else {
					if (normal.x != axis.x ||
						normal.y != axis.y ||
						normal.z != axis.z)
						_hoops_SACRH = true;
				}
				new_normal->x = normal.x;
				new_normal->y = normal.y;
				new_normal->z = normal.z;

				if (_hoops_SACRH) {
					/* _hoops_GHAA _hoops_CCAH _hoops_RGSR _hoops_CIAA "_hoops_SHIR" _hoops_AGIR */

					HI_Compute_Cross_Product (&axis, &normal, &_hoops_GPSSI);
					_hoops_RPSSI = (float)HI_Compute_Vector_Length (&_hoops_GPSSI);
					_hoops_RPSSI = _hoops_RPSSI*_hoops_RPSSI;
					if (_hoops_RPSSI < 1.0f)
						_hoops_RAHCR = _hoops_ISSSR (_hoops_SGIHR (1.0f - _hoops_RPSSI));
					else
						_hoops_RAHCR = 90.0f;
					if (_hoops_RAHCR != 0.0f) {
						HI_Compute_Offaxis_Rotation (_hoops_GPSSI.x, _hoops_GPSSI.y, _hoops_GPSSI.z, _hoops_RAHCR,
													 matrix);
						HI_Compute_Transformed_Points (2, (Point *)_hoops_CSPIR->axis,
													   matrix, (Point *)_hoops_CSPIR->axis);
					}

					_hoops_SASIR (context, _hoops_HSPIR, _hoops_AISSR | _hoops_RPSIR);
				}
				else
					_hoops_SASIR (context, _hoops_HSPIR, _hoops_CAHRA);
				break;
			}

			if (_hoops_IPRI->local_face_attributes.normals == null)
				HI_Initialize_Face_Attributes (_hoops_IPRI, LFA_EXPLICIT_NORMAL);

			_hoops_HICSA = &_hoops_IPRI->local_face_attributes.normals[offset];
			_hoops_AHAHR = (Vector *)_hoops_HICSA;
			flags = ((Polyhedron*)_hoops_IPRI)->local_face_attributes._hoops_CHHPR(offset);

			if (!BIT (*flags, LFA_EXPLICIT_NORMAL)) {
				if (++_hoops_IPRI->local_face_attributes.explicit_normal_count == _hoops_IPRI->face_count) {
					//_hoops_RPP (_hoops_APSSI(_hoops_CPHAR)) {
					//	_hoops_PPSSI _hoops_SGI _hoops_CRPR
					//  ((_hoops_IHRCP*)_hoops_CPHAR)->_hoops_PHRHR &= ~_hoops_HHRHR;
					//  _hoops_SGI = ((_hoops_IHRCP*)_hoops_CPHAR)->_hoops_HPSSI._hoops_HIGCI(_hoops_SHI);
					//}
				}
				*flags |= LFA_EXPLICIT_NORMAL;
				if (_hoops_IPRI->local_face_attributes.lff_uniform(_hoops_IPRI->face_count)) {
					/* _hoops_SR _hoops_CHR _hoops_ISSC _hoops_IS _hoops_IRS _hoops_PIAP _hoops_CAS _hoops_RH _hoops_SGI _hoops_CHR _hoops_GHRHR, _hoops_IIS'_hoops_GRI _hoops_CIH _hoops_RH _hoops_SGI _hoops_CRPR */
					_hoops_IPRI->local_face_attributes._hoops_SGRHR = _hoops_IPRI->local_face_attributes.flags[0];
					FREE_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
					_hoops_IPRI->polyhedron_flags &= ~_hoops_APRHR;
					_hoops_IPRI->local_face_attributes.flags = 0;
				}
				_hoops_SASIR (context, _hoops_IPRI, _hoops_CAHRA);
			}
		}	break;

		case _hoops_SCRIR: {
			Local_Vertex_Flags	*flags;

			if (_hoops_IPRI->local_vertex_attributes.normals == null)
				HI_Initialize_Vertex_Attributes (_hoops_IPRI, LVA_EXPLICIT_NORMAL, 0);

			_hoops_AHAHR = &_hoops_IPRI->local_vertex_attributes.normals[offset];
			flags = _hoops_IPRI->local_vertex_attributes._hoops_CHHPR(offset);

			if (!BIT (*flags, LVA_EXPLICIT_NORMAL)) {
				if (++_hoops_IPRI->local_vertex_attributes.explicit_normal_count == _hoops_IPRI->point_count) {
					//_hoops_RPP (_hoops_IPSSI(_hoops_CPHAR)) {
					//	_hoops_PPSSI _hoops_SGI _hoops_CRPR
					//  ((_hoops_IHRCP*)_hoops_CPHAR)->_hoops_PHRHR &= ~_hoops_CPSSI;
					//  _hoops_SGI = ((_hoops_IHRCP*)_hoops_CPHAR)->_hoops_SPSSI._hoops_HIGCI(_hoops_SHI);
					//}
				}
				*flags |= LVA_EXPLICIT_NORMAL;

				if (_hoops_IPRI->local_vertex_attributes.lvf_uniform(_hoops_IPRI->point_count)) {
					_hoops_IPRI->local_vertex_attributes._hoops_SGRHR = _hoops_IPRI->local_vertex_attributes.flags[0];
					FREE_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
					_hoops_IPRI->polyhedron_flags &= ~_hoops_CGRHR;
					_hoops_IPRI->local_vertex_attributes.flags = 0;
				}
				_hoops_SASIR (context, _hoops_IPRI, _hoops_CAHRA);
			}
		}	break;
	}


	/* _hoops_RPGP _hoops_IS _hoops_CACH _hoops_RPP (_hoops_RRI) _hoops_IGSIP _hoops_HRGR _hoops_SIGR */
	if (_hoops_AHAHR != null && (_hoops_SASSI || *_hoops_AHAHR != normal)) {
		*_hoops_AHAHR = normal;

		if (context->open_list != null &&
			(context->open_list->_hoops_GCRIR == _hoops_ICRIR ||
			 context->open_list->_hoops_GCRIR == _hoops_GSRIR && _hoops_SASSI)) {
			_hoops_IPRI->polyhedron_flags &= ~_hoops_ASAHR;

			if (BIT (_hoops_IPRI->polyhedron_flags, PHF_FACE_NORMALS_VALID)) {
				if (_hoops_IPRI->local_vertex_attributes.explicit_normal_count != _hoops_IPRI->point_count) {
					/* _hoops_SPR _hoops_PAR _hoops_RRI _hoops_GPHA _hoops_ASGA _hoops_GHSSI _hoops_GPP _hoops_IRS _hoops_HSP _hoops_GSSR */
					_hoops_IPRI->polyhedron_flags &= ~PHF_VERTEX_NORMALS_VALID;
				}

				/* _hoops_HSP _hoops_ASGA _hoops_AAPR _hoops_PGCPR _hoops_IS _hoops_IHGSR */
				_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR | _hoops_RPSIR);
			}
			else if (BIT (_hoops_IPRI->polyhedron_flags, PHF_VERTEX_NORMALS_VALID) &&
					 _hoops_IPRI->local_vertex_attributes.explicit_normal_count != _hoops_IPRI->point_count) {
				/*
				 *	_hoops_GPHA _hoops_ASGA _hoops_AAPR _hoops_PGCPR _hoops_IS _hoops_IHGSR _hoops_PPR _hoops_HPGR
				 *	_hoops_CHGC _hoops_SPR _hoops_GHSSI _hoops_GPP _hoops_IRS _hoops_HSP _hoops_GSSR.
				 */
				_hoops_IPRI->polyhedron_flags &= ~PHF_VERTEX_NORMALS_VALID;

				_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR | _hoops_RPSIR);
			}
		}
		else /* _hoops_RHSSI */ {
			if (BIT (_hoops_IPRI->polyhedron_flags, PHF_VERTEX_NORMALS_VALID)) {
				/* _hoops_GPHA _hoops_ASGA _hoops_AAPR _hoops_PGCPR _hoops_IS _hoops_IHGSR */
				_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR | _hoops_RPSIR);
			}
		}
	}
#endif
}



HC_INTERFACE void HC_CDECL HC_UnSet_Normal (void)
{
	_hoops_PAPPR context("UnSet_Normal");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Normal ();\n");
	);

	if (context->open_list == null) {
		HE_ERROR (HEC_NORMAL, HES_FACE_OR_VERTEX_ONLY, "Can only 'unset normal' on an open face or vertex");
		return;
	}
	switch (context->open_list->_hoops_GCRIR) {
		default: {
			HE_ERROR (HEC_NORMAL, HES_FACE_OR_VERTEX_ONLY, "Can only 'unset normal' on an open face or vertex");
			return;
		}	_hoops_HHHI;

#ifndef _hoops_HCGHR
		case _hoops_ICRIR: {
			Local_Face_Attributes *	_hoops_CPRI;
			_hoops_GIIPR * flags;

			Polyhedron *	_hoops_IPRI = context->open_list->info._hoops_IPRI._hoops_IGRPR;
			int				offset  = context->open_list->info._hoops_IPRI.offset;

			if (_hoops_IPRI->type == _hoops_CSIP) {
				PolyCylinder *_hoops_HSPIR = (PolyCylinder *)_hoops_IPRI;
				_hoops_SSPIR	*_hoops_CSPIR;
				Vector		axis;
				float			matrix[16];
				Vector alter *		normal = null;
				Vector				_hoops_GPSSI;
				float			_hoops_RAHCR;

				if (offset == 0) {
					Point const *	start = &_hoops_HSPIR->points[0];
					Point const *	next = start+1;

					if (!BIT (_hoops_HSPIR->flags, _hoops_RSICA)) {
						HE_ERROR (HEC_FACE, HES_NORMAL, "No normal set on this face");
						return;
					}

					while (*next == *start)
						++next;

					axis = *start - *next;

					_hoops_HSPIR->flags &= ~_hoops_RSICA;
					normal = &_hoops_HSPIR->_hoops_ACCSA[0];
					_hoops_CSPIR = &_hoops_HSPIR->_hoops_CSPIR[0];
				}
				else {
					Point const *	end = &_hoops_HSPIR->points[_hoops_HSPIR->point_count-1];
					Point const *	prev = end-1;

					if (!BIT (_hoops_HSPIR->flags, _hoops_ASICA)) {
						HE_ERROR (HEC_FACE, HES_NORMAL, "No normal set on this face");
						return;
					}

					while (*prev == *end)
						--prev;

					axis = *end - *prev;

					_hoops_HSPIR->flags &= ~_hoops_ASICA;
					normal = &_hoops_HSPIR->_hoops_ACCSA[1];
					_hoops_CSPIR = &_hoops_HSPIR->_hoops_CSPIR[_hoops_HSPIR->point_count-1];
				}

				HI_Normalize (&axis);

				_hoops_RPPPR();
				if (*normal != axis) {
					HI_Compute_Cross_Product (normal, &axis, &_hoops_GPSSI);
					_hoops_RAHCR = (float)HI_Compute_Vector_Length (&_hoops_GPSSI);
					_hoops_RAHCR = _hoops_ISSSR (_hoops_SGIHR (1.0f - _hoops_RAHCR*_hoops_RAHCR));
					HI_Compute_Offaxis_Rotation (_hoops_GPSSI.x, _hoops_GPSSI.y, _hoops_GPSSI.z,
												 _hoops_RAHCR, matrix);
					HI_Compute_Transformed_Points (2, (Point *)_hoops_CSPIR->axis,
												   matrix, (Point *)_hoops_CSPIR->axis);

					normal->x = axis.x;
					normal->y = axis.y;
					normal->z = axis.z;

					_hoops_SASIR (context, _hoops_HSPIR, _hoops_AISSR|_hoops_CSCCA|_hoops_RPSIR);
				}
				else
					_hoops_SASIR (context, _hoops_HSPIR, _hoops_CAHRA);
				_hoops_IRRPR();
				break;
			}

			_hoops_CPRI = &_hoops_IPRI->local_face_attributes;

			flags = _hoops_CPRI->_hoops_CHHPR(offset);

			if (!BIT (*flags, LFA_EXPLICIT_NORMAL)) {
				HE_ERROR (HEC_FACE, HES_NORMAL, "No normal set on this face");
				return;
			}

			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
				/* _hoops_SR _hoops_HS _hoops_SAHR _hoops_IPPRA _hoops_IRS _hoops_RHPC _hoops_GPP _hoops_IRS _hoops_RSRA _hoops_GPHA.  _hoops_CGP _hoops_RIAGR _hoops_RPII _hoops_GRP _hoops_RH
				_hoops_GHRHR _hoops_RIP, _hoops_SR _hoops_PAH'_hoops_RA _hoops_CPRIR _hoops_PPR _hoops_SR _hoops_HS _hoops_IS _hoops_CCPP _hoops_RH _hoops_IIRRA->_hoops_SGI _hoops_CRPR (_hoops_PPR _hoops_HSPC _hoops_SCH _hoops_IS _hoops_RH _hoops_GHRHR _hoops_RIP)*/
				ZALLOC_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
				for (int i = 0; i < _hoops_IPRI->face_count; i++)
					_hoops_IPRI->local_face_attributes.flags[i] = _hoops_IPRI->local_face_attributes._hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
				flags = _hoops_CPRI->_hoops_CHHPR(offset);
			}



			_hoops_RPPPR();
			*flags &= ~LFA_EXPLICIT_NORMAL;
			if (--_hoops_CPRI->explicit_normal_count == 0) {
				FREE_ARRAY_ALIGNED (_hoops_CPRI->normals, _hoops_IPRI->face_count, _hoops_ARPA, 16);
				_hoops_CPRI->normals = null;
			}
			else {
				_hoops_CPRI->normals[offset].a =
				_hoops_CPRI->normals[offset].b =
				_hoops_CPRI->normals[offset].c =
				_hoops_CPRI->normals[offset].d = 0.0f;
			}

			/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_ISSC _hoops_IS _hoops_IRS _hoops_PIAP _hoops_CAS _hoops_RH _hoops_SGI _hoops_CHR _hoops_GHRHR, _hoops_SR _hoops_GHCA _hoops_RRP _hoops_IS _hoops_CIH _hoops_RH _hoops_SGI _hoops_CRPR */
			if (!BIT (_hoops_IPRI->polyhedron_flags, _hoops_CCRHR) &&
				_hoops_CPRI->lff_uniform(_hoops_IPRI->face_count)) {
				_hoops_CPRI->_hoops_SGRHR = _hoops_CPRI->flags[0];
				FREE_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
				_hoops_IPRI->polyhedron_flags &= ~_hoops_APRHR;
				_hoops_CPRI->flags = 0;
			}

			_hoops_IPRI->polyhedron_flags &= ~_hoops_ASAHR;
			if (BIT (_hoops_IPRI->polyhedron_flags,
					 PHF_VERTEX_NORMALS_VALID|PHF_FACE_NORMALS_VALID)) {
				_hoops_IPRI->polyhedron_flags &=
					~(PHF_VERTEX_NORMALS_VALID|PHF_FACE_NORMALS_VALID);
				_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR|_hoops_RPSIR);
			}
			else
				_hoops_SASIR (context, _hoops_IPRI, _hoops_CAHRA);
			_hoops_IRRPR();
		}	break;

		case _hoops_GSRIR: {
			_hoops_GIIPR *		flags;
			int						offset;
			bool					_hoops_SACRH = false;

			Polyhedron *			_hoops_IPRI = context->open_list->info._hoops_IPRI._hoops_IGRPR;
			int						region = context->open_list->info._hoops_IPRI.offset;
			Local_Face_Attributes *	_hoops_CPRI		 = &_hoops_IPRI->local_face_attributes;
			int const *				regions	 = _hoops_CPRI->regions;

			if ((flags = _hoops_CPRI->flags) == null ||
				regions == null && region != 0) {
				HE_ERROR (HEC_FACE, HES_NORMAL, "No normals set in this region");
				return;
			}

			_hoops_RPPPR();

			for (offset=0; offset<_hoops_IPRI->face_count; offset++) {
				if (regions == null || regions[offset] == region) {
					if (BIT (flags[offset], LFA_EXPLICIT_NORMAL)) {
						flags[offset] &= ~LFA_EXPLICIT_NORMAL;
						if (--_hoops_CPRI->explicit_normal_count == 0) {
							FREE_ARRAY_ALIGNED (_hoops_CPRI->normals, _hoops_IPRI->face_count, _hoops_ARPA, 16);
							_hoops_CPRI->normals = null;
						}
						else {
							_hoops_CPRI->normals[offset].a =
							_hoops_CPRI->normals[offset].b =
							_hoops_CPRI->normals[offset].c =
							_hoops_CPRI->normals[offset].d = 0.0f;
						}
						_hoops_SACRH = true;
					}
				}
			}

			if (_hoops_SACRH) {
				_hoops_IPRI->polyhedron_flags &= ~_hoops_ASAHR;
				if (BIT (_hoops_IPRI->polyhedron_flags,
						 PHF_VERTEX_NORMALS_VALID|PHF_FACE_NORMALS_VALID)) {
					_hoops_IPRI->polyhedron_flags &=
						~(PHF_VERTEX_NORMALS_VALID|PHF_FACE_NORMALS_VALID);
					_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR|_hoops_RPSIR);
				}
				else
					_hoops_SASIR (context, _hoops_IPRI, _hoops_CAHRA);
			}
			else
				HE_ERROR (HEC_REGION, HES_NORMAL, "No normals set in this region");

			_hoops_IRRPR();
		}	break;

		case _hoops_SCRIR: {
			Polyhedron *				_hoops_IPRI = context->open_list->info._hoops_IPRI._hoops_IGRPR;
			int							offset = context->open_list->info._hoops_IPRI.offset;
			Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
			Local_Vertex_Flags *		flags = _hoops_SPRI->_hoops_CHHPR(offset);

			if (!BIT (*flags, LVA_EXPLICIT_NORMAL)) {
				HE_ERROR (HEC_VERTEX, HES_NORMAL, "No normal set on this vertex");
				return;
			}

			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
				/* _hoops_SR _hoops_HS _hoops_SAHR _hoops_IPPRA _hoops_IRS _hoops_RHPC _hoops_GPP _hoops_IRS _hoops_RSRA _hoops_GPHA.  _hoops_CGP _hoops_RIAGR _hoops_RPII _hoops_GRP _hoops_RH
				_hoops_GHRHR _hoops_RIP, _hoops_SR _hoops_PAH'_hoops_RA _hoops_CPRIR _hoops_PPR _hoops_SR _hoops_HS _hoops_IS _hoops_CCPP _hoops_RH _hoops_IIRRA->_hoops_SGI _hoops_CRPR (_hoops_PPR _hoops_HSPC _hoops_SCH _hoops_IS _hoops_RH _hoops_GHRHR _hoops_RIP)*/
				ZALLOC_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
				for (int i = 0; i < _hoops_IPRI->point_count; i++)
					_hoops_IPRI->local_vertex_attributes.flags[i] = _hoops_IPRI->local_vertex_attributes._hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
				flags = _hoops_SPRI->_hoops_CHHPR(offset);
			}


			_hoops_RPPPR();
			*flags &= ~LVA_EXPLICIT_NORMAL;
			if (--_hoops_SPRI->explicit_normal_count == 0) {
				FREE_ARRAY (_hoops_SPRI->normals, _hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR, Vector);
				_hoops_SPRI->normals = null;
			}
			else {
				_hoops_SPRI->normals[offset].x =
				_hoops_SPRI->normals[offset].y =
				_hoops_SPRI->normals[offset].z = 0.0f;
			}

			if (_hoops_SPRI->lvf_uniform(_hoops_IPRI->point_count)) {
				_hoops_SPRI->_hoops_SGRHR = _hoops_SPRI->flags[0];
				FREE_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
				_hoops_IPRI->polyhedron_flags &= ~_hoops_CGRHR;
				_hoops_SPRI->flags = 0;
			}


			if (BIT (_hoops_IPRI->polyhedron_flags, PHF_VERTEX_NORMALS_VALID)) {
				_hoops_IPRI->polyhedron_flags &= ~PHF_VERTEX_NORMALS_VALID;
				_hoops_SASIR (context, _hoops_IPRI, _hoops_GPSIR|_hoops_RPSIR);
			}
			else
				_hoops_SASIR (context, _hoops_IPRI, _hoops_CAHRA);
			_hoops_IRRPR();
		}	break;
#endif
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Normal (
	float *			x,
	float *			y,
	float *			z)
{
	_hoops_PAPPR context("Show_Normal");

#ifdef _hoops_HCGHR
	_hoops_IRPPR ("Geometry Normals");
#else
#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Normal () */\n");
	);

	Vector const *	normal = null;

	_hoops_CSPPR();

	if (context->open_list == null) {
		HE_ERROR (HEC_NORMAL, HES_OPEN_FACE_OR_VERTEX_ONLY, "Can only 'show normal' on an open face or vertex");
		goto Release;
	}
	switch (context->open_list->_hoops_GCRIR) {
		default: {
			HE_ERROR (HEC_NORMAL, HES_OPEN_FACE_OR_VERTEX_ONLY, "Can only 'show normal' on an open face or vertex");
			goto Release;
		}	_hoops_HHHI;

		case _hoops_ICRIR: {
			Polyhedron			*_hoops_IPRI;
			_hoops_GIIPR		*flags;
			_hoops_ARPA				*plane;

			_hoops_IPRI = context->open_list->info._hoops_IPRI._hoops_IGRPR;

			if (_hoops_IPRI->type == _hoops_CSIP) {
				PolyCylinder const * _hoops_HSPIR = (PolyCylinder const *)_hoops_IPRI;

				if (context->open_list->info.geometry.offset == 0) {
					if (BIT (_hoops_HSPIR->flags, _hoops_RSICA))
						normal = &_hoops_HSPIR->_hoops_ACCSA[0];
				}
				else {
					if (BIT (_hoops_HSPIR->flags, _hoops_ASICA))
						normal = &_hoops_HSPIR->_hoops_ACCSA[1];
				}

				if (normal == null) {
					HE_ERROR (HEC_NORMAL, HES_NO_LOCAL_SETTING, "No normal is explicitly set here");
					goto Release;
				}
				break;
			}

			plane = _hoops_IPRI->local_face_attributes.normals;
			flags = ((Polyhedron*)_hoops_IPRI)->local_face_attributes._hoops_CHHPR(context->open_list->info._hoops_IPRI.offset);

			if (plane == null || !BIT (*flags, LFA_EXPLICIT_NORMAL)) {
				HE_ERROR (HEC_NORMAL, HES_NO_LOCAL_SETTING, "No normal is explicitly set here");
				goto Release;
			}
			normal = (Vector *)(plane +
			context->open_list->info._hoops_IPRI.offset);
		}	break;

		case _hoops_SCRIR: {
			Polyhedron			*_hoops_IPRI;
			Local_Vertex_Flags	*flags;

			_hoops_IPRI = context->open_list->info._hoops_IPRI._hoops_IGRPR;
			normal = _hoops_IPRI->local_vertex_attributes.normals;
			flags = _hoops_IPRI->local_vertex_attributes._hoops_CHHPR(context->open_list->info._hoops_IPRI.offset);

			if (normal == null || !BIT (*flags, LVA_EXPLICIT_NORMAL)) {
				HE_ERROR (HEC_NORMAL, HES_NO_LOCAL_SETTING, "No normal is explicitly set here");
				goto Release;
			}
			normal += context->open_list->info._hoops_IPRI.offset;
		}	break;
	}

	*x = normal->x;
	*y = normal->y;
	*z = normal->z;

  Release:
	_hoops_IRRPR();
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Net_Normal (
	float *			x,
	float *			y,
	float *			z)
{
	_hoops_PAPPR context("Show_Net_Normal");

#ifdef _hoops_HCGHR
	_hoops_IRPPR ("Geometry Normals");
#else
#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else

	Vector const *	normal;

	_hoops_CSPPR();

	if (context->open_list == null) {
		HE_ERROR (HEC_NORMAL, HES_OPEN_FACE_OR_VERTEX_ONLY, "Can only 'show normal' on an open face or vertex");
		goto Release;
	}
	switch (context->open_list->_hoops_GCRIR) {
		default: {
			HE_ERROR (HEC_NORMAL, HES_OPEN_FACE_OR_VERTEX_ONLY, "Can only 'show normal' on an open face or vertex");
			goto Release;
		}	_hoops_HHHI;

		case _hoops_ICRIR: {
			Polyhedron *	_hoops_IPRI = context->open_list->info._hoops_IPRI._hoops_IGRPR;
			int				offset = context->open_list->info._hoops_IPRI.offset;

			if (_hoops_IPRI->type == _hoops_CSIP) {
				PolyCylinder const * _hoops_HSPIR = (PolyCylinder const *)_hoops_IPRI;

				normal = &_hoops_HSPIR->_hoops_ACCSA[offset];
				break;
			}

			_hoops_GIIPR	flag = *_hoops_IPRI->local_face_attributes._hoops_CHHPR(offset);

			if (!BIT (flag, LFA_EXPLICIT_NORMAL) && !BIT (_hoops_IPRI->polyhedron_flags, PHF_FACE_NORMALS_VALID))
				HI_Assemble_Face_Normals (_hoops_IPRI);

			normal = (Vector *) &_hoops_IPRI->local_face_attributes.normals[offset];
		}	break;

		case _hoops_SCRIR: {
			Polyhedron *		_hoops_IPRI = context->open_list->info._hoops_IPRI._hoops_IGRPR;
			int					offset = context->open_list->info._hoops_IPRI.offset;
			Local_Vertex_Flags	flag = *_hoops_IPRI->local_vertex_attributes._hoops_CHHPR(offset);

			if (!BIT (flag, LVA_EXPLICIT_NORMAL) && !BIT (_hoops_IPRI->polyhedron_flags, PHF_VERTEX_NORMALS_VALID))
				HI_Assemble_3D_Tristrips (_hoops_IPRI, false, true);

			normal = &_hoops_IPRI->local_vertex_attributes.normals[offset];
		}	break;
	}

	*x = normal->x;
	*y = normal->y;
	*z = normal->z;

Release:
	_hoops_IRRPR();
#endif
#endif
}



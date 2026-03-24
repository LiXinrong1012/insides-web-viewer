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
 * $Id: obf_tmp.txt 1.78 2010-12-17 22:17:21 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hi_proto.h"

#undef _hoops_RAAHR
#ifdef _hoops_AAAHR
#define _hoops_RAAHR 1.0e-20f
#else
#define _hoops_RAAHR 1.0e-10f
#endif

GLOBAL_FUNCTION void HI_Assemble_Face_Normals (
	Polyhedron	*_hoops_IPRI) 
{
	if (_hoops_IPRI->local_face_attributes.normals == null)
		HI_Initialize_Face_Attributes (_hoops_IPRI, LFA_EXPLICIT_NORMAL);

	if (_hoops_IPRI->type == _hoops_GSIP) {
		_hoops_AIHPR *				_hoops_PIHPR = (_hoops_AIHPR *)_hoops_IPRI;
		int					_hoops_IHRHR;
		_hoops_ARPA				*normal;
		_hoops_GIIPR	*flags;
		Point				*_hoops_PAAHR;
		Point				*_hoops_HAAHR;
		Point				*_hoops_IAAHR;
		Point				*_hoops_CAAHR;
		Vector				_hoops_SAAHR;
		Vector				_hoops_GPAHR;
		bool				_hoops_RPAHR;

		_hoops_RPAHR = BIT (_hoops_IPRI->polyhedron_flags,
								 PHF_IMPLICIT_NORMALS_REVERSED);

		normal = _hoops_PIHPR->local_face_attributes.normals;
		flags  = _hoops_PIHPR->local_face_attributes._hoops_CHHPR();

		_hoops_IHRHR = _hoops_PIHPR->rows - 1;

		_hoops_PAAHR = _hoops_PIHPR->points;
		_hoops_HAAHR = _hoops_PAAHR + 1;
		_hoops_IAAHR = _hoops_PIHPR->points + _hoops_PIHPR->columns;
		_hoops_CAAHR = _hoops_IAAHR + 1;

		do {
			int		_hoops_APAHR = _hoops_PIHPR->columns - 1;

			_hoops_SAAHR.x = _hoops_IAAHR->x - _hoops_PAAHR->x;
			_hoops_SAAHR.y = _hoops_IAAHR->y - _hoops_PAAHR->y;
			_hoops_SAAHR.z = _hoops_IAAHR->z - _hoops_PAAHR->z;

			do {
				/*
				 * _hoops_SSSA _hoops_RH _hoops_GSSR _hoops_HPP _hoops_RH _hoops_PPAHR _hoops_SHHP-
				 * _hoops_HPAHR, _hoops_HRII _hoops_HSAR _hoops_RH _hoops_IPAHR-_hoops_CPAHR _hoops_CCAC _hoops_SPAHR,
				 * _hoops_CR _hoops_RH _hoops_PGCR _hoops_PISRR _hoops_CGH _hoops_SHH _hoops_GHAHR _hoops_PRAR-_hoops_RHAHR
				 * _hoops_IH _hoops_IRS _hoops_SCPH.
				 */
				_hoops_GPAHR.x = _hoops_HAAHR->x - _hoops_IAAHR->x;
				_hoops_GPAHR.y = _hoops_HAAHR->y - _hoops_IAAHR->y;
				_hoops_GPAHR.z = _hoops_HAAHR->z - _hoops_IAAHR->z;

				if (!BIT (*flags, LFA_EXPLICIT_NORMAL)) {
					normal->a = -(_hoops_SAAHR.y * _hoops_GPAHR.z - _hoops_SAAHR.z * _hoops_GPAHR.y);
					normal->b = -(_hoops_SAAHR.z * _hoops_GPAHR.x - _hoops_SAAHR.x * _hoops_GPAHR.z);
					normal->c = -(_hoops_SAAHR.x * _hoops_GPAHR.y - _hoops_SAAHR.y * _hoops_GPAHR.x);
					if (_hoops_RPAHR) {
						normal->a = normal->a;
						normal->b = normal->b;
						normal->c = normal->c;
					}
					(void)HI_Normalize ((Vector *)normal);
				}

				normal->d = -(_hoops_PAAHR->x * normal->a +
							  _hoops_PAAHR->y * normal->b +
							  _hoops_PAAHR->z * normal->c);

				++normal;
				if(BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR))
					++flags;


				_hoops_SAAHR.x = _hoops_CAAHR->x - _hoops_HAAHR->x;
				_hoops_SAAHR.y = _hoops_CAAHR->y - _hoops_HAAHR->y;
				_hoops_SAAHR.z = _hoops_CAAHR->z - _hoops_HAAHR->z;

				if (!BIT (*flags, LFA_EXPLICIT_NORMAL)) {
					normal->a = -(_hoops_SAAHR.y * _hoops_GPAHR.z - _hoops_SAAHR.z * _hoops_GPAHR.y);
					normal->b = -(_hoops_SAAHR.z * _hoops_GPAHR.x - _hoops_SAAHR.x * _hoops_GPAHR.z);
					normal->c = -(_hoops_SAAHR.x * _hoops_GPAHR.y - _hoops_SAAHR.y * _hoops_GPAHR.x);
					(void)HI_Normalize ((Vector *)normal);
					if (_hoops_RPAHR) {
						normal->a = normal->a;
						normal->b = normal->b;
						normal->c = normal->c;
					}
				}

				normal->d = -(_hoops_PAAHR->x * normal->a +
							  _hoops_PAAHR->y * normal->b +
							  _hoops_PAAHR->z * normal->c);

				++normal;
				if(BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR))
					++flags;

				_hoops_PAAHR = _hoops_HAAHR++;
				_hoops_IAAHR = _hoops_CAAHR++;
			} _hoops_RGGA (--_hoops_APAHR == 0);

			_hoops_PAAHR = _hoops_HAAHR++;
			_hoops_IAAHR = _hoops_CAAHR++;
		} _hoops_RGGA (--_hoops_IHRHR == 0);
	}

	else /* _hoops_RPP (_hoops_CPHAR->_hoops_GPRR == _hoops_HGCPR) */ {
		Shell *					_hoops_SPHPR = (Shell *)_hoops_IPRI;
		Point *					points = _hoops_IPRI->points;
		_hoops_ARPA *					_hoops_AHAHR = _hoops_SPHPR->local_face_attributes.normals;
		_hoops_GIIPR *		flags = _hoops_SPHPR->local_face_attributes._hoops_CHHPR();
		bool					_hoops_RPAHR = BIT (_hoops_IPRI->polyhedron_flags, PHF_IMPLICIT_NORMALS_REVERSED);

		float	a, b, c;

		if (_hoops_SPHPR->face_list == null) {
			Tristrip const *		ts;
			_hoops_ARPA *				_hoops_PHAHR;
			int					i = 0;

			_hoops_PHAHR = _hoops_AHAHR + _hoops_IPRI->face_count;

			do {
				if (!BIT (*(_hoops_SPHPR->local_face_attributes._hoops_CHHPR(i)), LFA_EXPLICIT_NORMAL)) {
					_hoops_AHAHR->a = 0.0f;
					_hoops_AHAHR->b = 0.0f;
					_hoops_AHAHR->c = 0.0f;
				}
				_hoops_AHAHR->d = 0.0f;
				i++;
			} _hoops_RGGA (++_hoops_AHAHR == _hoops_PHAHR);

			/* _hoops_HAPR _hoops_HGAS _hoops_AGCR, _hoops_PPSI _hoops_CAPR _hoops_ISSC */
			_hoops_AHAHR = _hoops_SPHPR->local_face_attributes.normals;
			flags		 = _hoops_SPHPR->local_face_attributes._hoops_CHHPR();

			if ((ts = _hoops_IPRI->tristrips) != null) do {
				int						_hoops_PHHA = ts->_hoops_PHHA;
				int const *				lengths = ts->lengths;
				int const *				vi = ts->_hoops_AIHA;
				int const *				fi = ts->face_indices;
				int						face = -1;

				while (_hoops_PHHA-- > 0) {
					bool		_hoops_SICPR = false;
					int				length = *lengths++;
					int				p1 = *vi++;
					int				p2 = *vi++;
					int				_hoops_IAPH;
					Vector		_hoops_ISPI;
					Vector		_hoops_CSPI;
					bool		_hoops_HHAHR = !_hoops_RPAHR;

					if (length < 0) {
						length = -length;
						_hoops_SICPR = true;
					}
					length -= 2;

					if (fi) fi += 2;

					_hoops_ISPI.x = points[p2].x - points[p1].x;
					_hoops_ISPI.y = points[p2].y - points[p1].y;
					_hoops_ISPI.z = points[p2].z - points[p1].z;

					while (length-- > 0) {
						_hoops_IAPH = *vi++;
						if (fi)
							face = *fi++;
						else
							face++;

						_hoops_CSPI.x = points[_hoops_IAPH].x - points[p2].x;
						_hoops_CSPI.y = points[_hoops_IAPH].y - points[p2].y;
						_hoops_CSPI.z = points[_hoops_IAPH].z - points[p2].z;

						if (!BIT (*(_hoops_SPHPR->local_face_attributes._hoops_CHHPR(face)), LFA_EXPLICIT_NORMAL)) {
							a = _hoops_ISPI.y * _hoops_CSPI.z	 -	_hoops_ISPI.z * _hoops_CSPI.y;
							b = _hoops_ISPI.z * _hoops_CSPI.x	 -	_hoops_ISPI.x * _hoops_CSPI.z;
							c = _hoops_ISPI.x * _hoops_CSPI.y	 -	_hoops_ISPI.y * _hoops_CSPI.x;

							if (_hoops_HHAHR) {
								a = -a;	  b = -b;	c = -c;
							}

							_hoops_AHAHR[face].a += a;
							_hoops_AHAHR[face].b += b;
							_hoops_AHAHR[face].c += c;
						}

						if (!_hoops_SICPR) {
							p1 = p2;
							_hoops_HHAHR = !_hoops_HHAHR;
							_hoops_ISPI.x = _hoops_CSPI.x;
							_hoops_ISPI.y = _hoops_CSPI.y;
							_hoops_ISPI.z = _hoops_CSPI.z;
						}
						else {
							_hoops_ISPI.x = points[_hoops_IAPH].x - points[p1].x;
							_hoops_ISPI.y = points[_hoops_IAPH].y - points[p1].y;
							_hoops_ISPI.z = points[_hoops_IAPH].z - points[p1].z;
						}
						p2 = _hoops_IAPH;
					}
				}
			} _hoops_RGGA ((ts = ts->next) == null);

			i = 0;
			do {
				if (!BIT (*(_hoops_SPHPR->local_face_attributes._hoops_CHHPR(i)), LFA_EXPLICIT_NORMAL))
					if (!HI_Normalize ((Vector *)_hoops_AHAHR))
						 _hoops_SPHPR->local_face_attributes._hoops_IHAHR++;
				i++;
			} _hoops_RGGA (++_hoops_AHAHR == _hoops_PHAHR);

			/* _hoops_HAPR _hoops_HGAS _hoops_AGCR, _hoops_PPSI _hoops_CAPR _hoops_ISSC */
			_hoops_AHAHR = _hoops_SPHPR->local_face_attributes.normals;
			flags		 = _hoops_SPHPR->local_face_attributes._hoops_CHHPR();

			if ((ts = _hoops_IPRI->tristrips) != null) do {
				int						_hoops_PHHA = ts->_hoops_PHHA;
				int const *				lengths = ts->lengths;
				int const *				vi = ts->_hoops_AIHA;
				int const *				fi = ts->face_indices;
				int						face = -1;

				while (_hoops_PHHA-- > 0) {
					bool		_hoops_SICPR = false;
					int				length = *lengths++;
					int				p1 = *vi++;
					int				p2 = *vi++;
					int				_hoops_IAPH;
					_hoops_ARPA		*plane;

					if (length < 0) {
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

						plane = &_hoops_AHAHR[face];
						plane->d = -(points[p1].x * plane->a +
									 points[p1].y * plane->b +
									 points[p1].z * plane->c);

						if (!_hoops_SICPR)
							p1 = p2;
						p2 = _hoops_IAPH;
					}
				}
			} _hoops_RGGA ((ts = ts->next) == null);
		}
		else { 
			int		*face_list;
			int		*_hoops_CHAHR;
			int		*_hoops_SHAHR;

			face_list = _hoops_SPHPR->face_list;
			_hoops_SHAHR = face_list + _hoops_SPHPR->face_list_length;
		
			_hoops_PCCAR {
				Point *	_hoops_GIAHR;
				int *	_hoops_RIAHR = face_list++;
				int		length = *_hoops_RIAHR;

				if (length < 0)
					length = -length;
				_hoops_CHAHR = face_list + length;

				if (BIT (*flags, LFA_EXPLICIT_NORMAL)) {
					if (face_list == _hoops_CHAHR)
						_hoops_GIAHR = points;
					else
						_hoops_GIAHR = points + *face_list;

					face_list = _hoops_CHAHR;
				}
				else {
					/* _hoops_IPCP 3 _hoops_AIAHR _hoops_RAIGR, _hoops_IHAC, _hoops_PPR _hoops_IHRPR _hoops_CHR _hoops_PIAHR _hoops_IS _hoops_RH
					 * _hoops_HIAHR _hoops_IIGR _hoops_RH _hoops_IIAHR _hoops_IIGR _hoops_RH _hoops_HSSP _hoops_CIAA _hoops_RH _hoops_CIAHR, _hoops_SIAHR, _hoops_PPR
					 * _hoops_HSHC _hoops_GHC, _hoops_GCAHR.
					 *
					 * _hoops_HSRR _hoops_APRAR _hoops_RCAHR, _hoops_ACAHR _hoops_IS _hoops_PCAHR & _hoops_HCAHR (1_hoops_ICPC _hoops_ICAHR) _hoops_CCAHR. 513
					 */

					/* _hoops_ARAS _hoops_AARI _hoops_RH _hoops_HSP, _hoops_IGGC _hoops_SCAHR _hoops_HIAHR */

					a = b = c = 0.0f;

					if (face_list == _hoops_CHAHR) {
						_hoops_AHAHR->a = _hoops_AHAHR->b = _hoops_AHAHR->c = 0.0f;
						_hoops_GIAHR = points;
					}
					else {
						Point				*_hoops_GGIAR;
						Point				*p1;
						_hoops_SASC 		sc;

						_hoops_GIAHR = _hoops_GGIAR = points + *face_list;

						_hoops_RGGA (++face_list == _hoops_CHAHR) {
							p1 = points + *face_list;
							sc.Merge (*p1);
							a += (_hoops_GGIAR->y + p1->y) * (p1->z - _hoops_GGIAR->z);
							b += (_hoops_GGIAR->z + p1->z) * (p1->x - _hoops_GGIAR->x);
							c += (_hoops_GGIAR->x + p1->x) * (p1->y - _hoops_GGIAR->y);
							_hoops_GGIAR = p1;
						}

						/* _hoops_GGGR _hoops_SCH _hoops_GH, _hoops_PPR _hoops_IPS _hoops_IRS/_hoops_RCSR/_hoops_GSGGR _hoops_CRGR '_hoops_GSSR' */
						p1 = _hoops_GIAHR;
						sc.Merge (*p1);
						_hoops_AHAHR->a = -(a + (_hoops_GGIAR->y + p1->y) * (p1->z - _hoops_GGIAR->z));
						_hoops_AHAHR->b = -(b + (_hoops_GGIAR->z + p1->z) * (p1->x - _hoops_GGIAR->x));
						_hoops_AHAHR->c = -(c + (_hoops_GGIAR->x + p1->x) * (p1->y - _hoops_GGIAR->y));

						if (_hoops_RPAHR) {
							_hoops_AHAHR->a = -_hoops_AHAHR->a;
							_hoops_AHAHR->b = -_hoops_AHAHR->b;
							_hoops_AHAHR->c = -_hoops_AHAHR->c;
						}

						float	_hoops_RPIS = _hoops_IAAA(Abs(sc.max.x), Abs(sc.min.x), 
											Abs(sc.max.y), Abs(sc.min.y), 
											Abs(sc.max.z), Abs(sc.min.z));
						float	size = _hoops_IAAA (sc.max.x - sc.min.x, 
											sc.max.y - sc.min.y, 
											sc.max.z - sc.min.z);
						float	_hoops_GSAHR = size * size * _hoops_RAAHR;


						if (size < 2.5e-7f * _hoops_RPIS ||
							Abs(_hoops_AHAHR->a) < _hoops_GSAHR &&
							Abs(_hoops_AHAHR->b) < _hoops_GSAHR &&
							Abs(_hoops_AHAHR->c) < _hoops_GSAHR) {
							_hoops_AHAHR->a =
								_hoops_AHAHR->b = 
									_hoops_AHAHR->c = 0.0f;
							_hoops_SPHPR->local_face_attributes._hoops_IHAHR++;
						}
						else
							(void)HI_Normalize ((Vector *)_hoops_AHAHR);
					}
				}

				_hoops_AHAHR->d = -(_hoops_GIAHR->x * _hoops_AHAHR->a +
									_hoops_GIAHR->y * _hoops_AHAHR->b +
									_hoops_GIAHR->z * _hoops_AHAHR->c);

				_hoops_PCCAR {
					/* _hoops_RPGP _hoops_RPP _hoops_HCR _hoops_CPHR */
					if (face_list == _hoops_SHAHR) goto _hoops_PCPPR;

					if (*face_list >= 0) {
						/* _hoops_IHIS _hoops_GPP _hoops_IS _hoops_RH _hoops_SPS _hoops_HSP */
						++_hoops_AHAHR;
						if(BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR))
							++flags;
						break;
					}

					if (_hoops_AHAHR->a == 0.0f &&
						_hoops_AHAHR->b == 0.0f &&
						_hoops_AHAHR->c == 0.0f) {
						/* _hoops_HPPR _hoops_IS _hoops_SGH _hoops_RH "_hoops_RCCPR" _hoops_IS _hoops_RCPS _hoops_GH _hoops_CCA _hoops_IRS _hoops_GSSR,
						 * _hoops_CR _hoops_RH "_hoops_HSP" _hoops_RSAHR _hoops_IS _hoops_SHH _hoops_ARHAR
						 */
						break;
					}

					/* _hoops_SAHR _hoops_HSGR _hoops_RH _hoops_RCCPR */
					face_list += 1 - *face_list;
				}
			}
		}
		_hoops_PCPPR:;
	}

	_hoops_IPRI->polyhedron_flags |= PHF_FACE_NORMALS_VALID |
										   _hoops_ASAHR;
}

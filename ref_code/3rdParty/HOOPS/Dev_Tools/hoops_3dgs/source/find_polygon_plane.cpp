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
 * $Id: obf_tmp.txt 1.42 2010-06-04 21:37:17 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"


GLOBAL_FUNCTION bool HI_Figure_Plane_From_Points (
	int				count,
	Point const	*	_hoops_IAIRA,
	_hoops_ARPA alter	*	plane) {
	Point const	*	pl = _hoops_IAIRA;
	Vector			normal;
	Point const	*	_hoops_RPIRA;
	float			a, b, c;
	float			_hoops_SPGHH, _hoops_GHGHH, _hoops_RHGHH;

	/*
	 * _hoops_IPCP 3 _hoops_AIAHR _hoops_RAIGR, _hoops_IHAC, _hoops_PPR _hoops_IHRPR _hoops_CHR _hoops_PIAHR _hoops_IS _hoops_RH
	 * _hoops_HIAHR _hoops_IIGR _hoops_RH _hoops_IIAHR _hoops_IIGR _hoops_RH _hoops_HSSP _hoops_CIAA _hoops_RH _hoops_CIAHR, _hoops_SIAHR, _hoops_PPR
	 * _hoops_HSHC _hoops_GHC, _hoops_GCAHR.
	 * _hoops_HSRR _hoops_APRAR _hoops_RCAHR, _hoops_ACAHR _hoops_IS _hoops_PCAHR & _hoops_HCAHR (1_hoops_ICPC _hoops_ICAHR) _hoops_CCAHR. 513
	 */

	if (count < 3) 
		return false;

	/* _hoops_ARAS _hoops_AARI _hoops_RH _hoops_HSSP, _hoops_IGGC _hoops_SCAHR _hoops_HIAHR */

	/*
	 * _hoops_IRS "_hoops_RHCH" _hoops_PPSR _hoops_HRGR _hoops_GACC _hoops_HPISR, _hoops_IS _hoops_IRHH _hoops_RH _hoops_IPPA '_hoops_GHGP' _hoops_RPPR
	 * _hoops_RRI "_hoops_APIP" _hoops_CGPR _hoops_RH _hoops_HSSP _hoops_HRGR _hoops_GRAA-_hoops_HPSS.
	 */

	a = b = c = 0.0f;
	_hoops_SPGHH = _hoops_GHGHH = _hoops_RHGHH = 0.0f;

	_hoops_RPIRA = pl + count - 1;
	do {
		a += (pl[0].y + pl[1].y) * (pl[1].z - pl[0].z);
		b += (pl[0].z + pl[1].z) * (pl[1].x - pl[0].x);
		c += (pl[0].x + pl[1].x) * (pl[1].y - pl[0].y);

		_hoops_SPGHH += pl[0].x;
		_hoops_GHGHH += pl[0].y;
		_hoops_RHGHH += pl[0].z;
	}
	_hoops_RGGA (++pl == _hoops_RPIRA);

	/* _hoops_IRAA _hoops_PICP _hoops_IIGR _hoops_RH _hoops_APIRA _hoops_PPSR, _hoops_PPR _hoops_IPS _hoops_IRS/_hoops_RCSR/_hoops_GSGGR _hoops_CRGR '_hoops_GSSR' */
	{	Point const	*close = _hoops_IAIRA;

		normal.x = a + (pl->y + close->y) * (close->z - pl->z);
		normal.y = b + (pl->z + close->z) * (close->x - pl->x);
		normal.z = c + (pl->x + close->x) * (close->y - pl->y);
	}

	/* _hoops_HPIRA _hoops_SPAAR _hoops_RH _hoops_AASHR */
	{	float	_hoops_AHGHH = 1.0f / (float)count;

		_hoops_SPGHH = (_hoops_SPGHH + pl->x) * _hoops_AHGHH;
		_hoops_GHGHH = (_hoops_GHGHH + pl->y) * _hoops_AHGHH;
		_hoops_RHGHH = (_hoops_RHGHH + pl->z) * _hoops_AHGHH;
	}

	if (HI_Normalize (&normal)) {  /* ("_hoops_CGH" _hoops_SHR _hoops_SHH != 0) */
		plane->a = normal.x;
		plane->b = normal.y;
		plane->c = normal.z;
		plane->d = -(_hoops_SPGHH*normal.x + _hoops_GHGHH*normal.y + _hoops_RHGHH*normal.z);
		return true;
	}

	plane->a = plane->b = plane->c = plane->d = 0.0f;
	return false;
}


GLOBAL_FUNCTION void HI_Find_Polygon_Plane (
	Polygon alter		*polygon) {

	polygon->_hoops_RRHH |= _hoops_ARHH;

	/*
	 * _hoops_IPCP 3 _hoops_AIAHR _hoops_RAIGR, _hoops_IHAC, _hoops_PPR _hoops_IHRPR _hoops_CHR _hoops_PIAHR _hoops_IS _hoops_RH
	 * _hoops_HIAHR _hoops_IIGR _hoops_RH _hoops_IIAHR _hoops_IIGR _hoops_RH _hoops_HSSP _hoops_CIAA _hoops_RH _hoops_CIAHR, _hoops_SIAHR, _hoops_PPR
	 * _hoops_HSHC _hoops_GHC, _hoops_GCAHR.
	 * _hoops_HSRR _hoops_APRAR _hoops_RCAHR, _hoops_ACAHR _hoops_IS _hoops_PCAHR & _hoops_HCAHR (1_hoops_ICPC _hoops_ICAHR) _hoops_CCAHR. 513
	 */

	if (polygon->count < 3) return;

	if (HI_Figure_Plane_From_Points (polygon->count, polygon->points,
									 &polygon->plane))
		polygon->_hoops_RRHH |= _hoops_IASGP;
}

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
 * $Id: obf_tmp.txt 1.76 2010-01-13 00:37:00 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "tandt.h"
#include "hpserror.h"


local void _hoops_HSHPH (
	Net_Rendition const &		nr,
	Geometry const *			geometry,
	Point alter *				_hoops_ISHPH,
	_hoops_ARPA alter *				_hoops_SHPA) {
	_hoops_SGCC const &	_hoops_HSGA = nr->transform_rendition->_hoops_IPH;
	Point const *				_hoops_CSHPH;
	Point						_hoops_SSHPH;
	_hoops_ARPA const *				_hoops_GGIPH;

	/* _hoops_SSCR _hoops_IRS _hoops_GSSP _hoops_GC (_hoops_HAR _hoops_SHPR _hoops_GC) _hoops_GSSR _hoops_PPR _hoops_AHC */

	switch (geometry->type) {
		case _hoops_RCIP: {
			if (!BIT (geometry->_hoops_RRHH, _hoops_ARHH))
				HI_Find_Polygon_Plane ((Polygon alter *)geometry);/*_hoops_HGPSA*/

			if (!BIT (geometry->_hoops_RRHH, _hoops_IASGP)) {
				/* _hoops_GRHP _hoops_SCH _hoops_HII _hoops_RGIPH */
				_hoops_SHPA->a = 0.0f;
				_hoops_SHPA->b = 0.0f;
				_hoops_SHPA->c = -1.0f;
				_hoops_SHPA->d = 0.0f;
				if (_hoops_ISHPH != null) {
					_hoops_ISHPH->x = 0.0f;
					_hoops_ISHPH->y = 0.0f;
					_hoops_ISHPH->z = 0.0f;
				}
				return;
			}
			else {
				Polygon const *	polygon = (Polygon const *)geometry;
				int				count = polygon->count;
				Point const	*	_hoops_AGIPH = polygon->points;
				Point const	*	_hoops_PGIPH = _hoops_AGIPH + count;

				_hoops_GGIPH = &polygon->plane;
				_hoops_CSHPH = &_hoops_SSHPH;

				/* _hoops_SSS _hoops_RH _hoops_HGIPH _hoops_IIGR _hoops_RH _hoops_HSSP */
				_hoops_SSHPH.x = 0.0f;
				_hoops_SSHPH.y = 0.0f;
				_hoops_SSHPH.z = 0.0f;
				_hoops_RGGA (_hoops_AGIPH == _hoops_PGIPH) {
					_hoops_SSHPH.x += _hoops_AGIPH->x;
					_hoops_SSHPH.y += _hoops_AGIPH->y;
					_hoops_SSHPH.z += _hoops_AGIPH->z;
					_hoops_AGIPH++;
				}
				_hoops_SSHPH.x /= count;
				_hoops_SSHPH.y /= count;
				_hoops_SSHPH.z /= count;
			}
		}	break;

		case _hoops_SGCP:
		case _hoops_CGCP: {
			_hoops_GSPI const *	_hoops_IHHIR = (_hoops_GSPI const *)geometry;
			_hoops_GGIPH = &_hoops_IHHIR->plane;
			_hoops_CSHPH = &_hoops_IHHIR->center;
		}	break;

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Figlight confusion");
			return;
		}		/* _hoops_IHSA; */
	}

	if (!ANYBIT (_hoops_HSGA->data._hoops_RAGR, _hoops_CICH)) {
		/* _hoops_RSH _hoops_AGAPR. */
		_hoops_SHPA->a = _hoops_GGIPH->a;
		_hoops_SHPA->b = _hoops_GGIPH->b;
		_hoops_SHPA->c = _hoops_GGIPH->c;
		_hoops_SHPA->d = _hoops_GGIPH->d;

		if (_hoops_ISHPH != null) {
			_hoops_ISHPH->x = _hoops_CSHPH->x;
			_hoops_ISHPH->y = _hoops_CSHPH->y;
			_hoops_ISHPH->z = _hoops_CSHPH->z;
		}
	}
	else {
		_hoops_RPRA const *		_hoops_CRIPA = _hoops_HSGA->_hoops_PPRA()->data.elements;

		/* _hoops_IGPP _hoops_CARA _hoops_IPPA _hoops_IS _hoops_IRS */

		/* "_hoops_IRSIR _hoops_HIHP _hoops_GAR _hoops_GPRRH . _hoops_HAICR" - _hoops_RPRRH & _hoops_APRRH */
		/* _hoops_RH _hoops_IAPGR-_hoops_GGSR _hoops_AIRP _hoops_CHR _hoops_HSSPR _hoops_IS _hoops_SHH _hoops_AHHR _hoops_GGR _hoops_IRS _hoops_IRISR 4x3 */

		_hoops_SHPA->a = _hoops_CRIPA[0][0] * _hoops_GGIPH->a +
						 _hoops_CRIPA[0][1] * _hoops_GGIPH->b +
						 _hoops_CRIPA[0][2] * _hoops_GGIPH->c /* +
						 _hoops_PPRRH[0][3] * _hoops_IGIPH->_hoops_GHGP */;

		_hoops_SHPA->b = _hoops_CRIPA[1][0] * _hoops_GGIPH->a +
						 _hoops_CRIPA[1][1] * _hoops_GGIPH->b +
						 _hoops_CRIPA[1][2] * _hoops_GGIPH->c /* +
						 _hoops_PPRRH[1][3] * _hoops_IGIPH->_hoops_GHGP */;

		_hoops_SHPA->c = _hoops_CRIPA[2][0] * _hoops_GGIPH->a +
						 _hoops_CRIPA[2][1] * _hoops_GGIPH->b +
						 _hoops_CRIPA[2][2] * _hoops_GGIPH->c /* +
						 _hoops_PPRRH[2][3] * _hoops_IGIPH->_hoops_GHGP */;

		_hoops_SHPA->d = _hoops_CRIPA[3][0] * _hoops_GGIPH->a +
						 _hoops_CRIPA[3][1] * _hoops_GGIPH->b +
						 _hoops_CRIPA[3][2] * _hoops_GGIPH->c +
						 _hoops_CRIPA[3][3] * _hoops_GGIPH->d;

		(void)HI_Normalize_Plane (_hoops_SHPA);


		if (_hoops_ISHPH != null) {
			/* _hoops_IGPP _hoops_CARA _hoops_ACAGR _hoops_IS _hoops_IRS _hoops_GCPR */
			_hoops_RPRA const *		mat = _hoops_HSGA->data.elements;

			_hoops_ISHPH->x = _hoops_HPRA (mat, *_hoops_CSHPH);
			_hoops_ISHPH->y = _hoops_IPRA (mat, *_hoops_CSHPH);
			_hoops_ISHPH->z = _hoops_CPRA (mat, *_hoops_CSHPH);
		}
	}
}


GLOBAL_FUNCTION void HD_Figure_Light (
	Net_Rendition const &		nr,
	Geometry const *			geometry,
	RGBA alter *				total) {
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	_hoops_ARPA						plane;

	/*
	 * _hoops_RPP _hoops_CGIPH || _hoops_SGIPH || _hoops_GRIPH
	 * _hoops_HRGR _hoops_IHPR _hoops_PSCR _hoops_GRAS _hoops_RH _hoops_PPSR _hoops_PPR _hoops_RIH _hoops_RH _hoops_PPSR _hoops_IS _hoops_SSSA _hoops_RRIPH _hoops_SHS
	 * _hoops_RIH _hoops_GGR _hoops_IRAP.
	 */
	if (_hoops_SIGA->_hoops_AGP != null &&
		_hoops_SIGA->_hoops_AGP->_hoops_ISPHP ||
		(BIT (nr->_hoops_IRR->_hoops_PPH, Rendo_LOCAL_VIEWER)) ||
		(BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HPH))) {
		Point				_hoops_ICAGA;

		_hoops_HSHPH (nr, geometry, &_hoops_ICAGA, &plane);
		_hoops_ISACP (nr, _hoops_SIGA->_hoops_AGP, _hoops_SIGA->_hoops_CHA,
							 &_hoops_ICAGA, null, &plane, null, null, 0, 0, total, null);
	}
	else {
		_hoops_HSHPH (nr, geometry, null, &plane);
		_hoops_ISACP (nr, _hoops_SIGA->_hoops_AGP, _hoops_SIGA->_hoops_CHA,
							 null, null, &plane, null, null, 0, 0, total, null);
	}
}

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
 * $Id: obf_tmp.txt 1.100 2010-10-27 03:37:13 covey Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


GLOBAL_FUNCTION Test HD_Transform_And_Test_Bounding (
	Net_Rendition const &		nr,
	Bounding const *			_hoops_RCGRGR,
	_hoops_PACIR const *	_hoops_HCSR,
	Int_Rectangle const *		_hoops_ACSR,
	float						_hoops_ARIIH,
	float *						_hoops_IRIIH)
{
	Bounding const &	bounding = *_hoops_RCGRGR;
	bounding._hoops_SSAGR();

	if (bounding._hoops_HICAR())
		return Test_DISJOINT;

	if (!ANYBIT (bounding->flags, _hoops_IGCIR|Bounding_TRANSFORM_DEPENDENT)) {
		if (!ANYBIT(bounding->flags, _hoops_RGCIR|_hoops_AGCIR))
			bounding->_hoops_PGCIR();

		Test	result = 0;
		int		_hoops_PIHS = 0;

		float	_hoops_RRIIH = _hoops_IAAA(_hoops_ACSR->left - _hoops_HCSR->left, 0.0f);

		if (BIT (bounding->flags, _hoops_RGCIR))
			_hoops_PIHS = HD_Transform_And_Test_Simple_Sphere (nr, 1, &bounding->sphere, null,
				_hoops_RRIIH, _hoops_ARIIH, &result, _hoops_IRIIH, null);
		else
			_hoops_PIHS = HD_Transform_And_Test_Simple_Cuboid (nr, 1, &bounding->cuboid,
				_hoops_RRIIH, _hoops_ARIIH, &result, _hoops_IRIIH, null);

		return result;
	}

	return _hoops_RAAGI;
}




GLOBAL_FUNCTION int HD_Transform_And_Test_Simple_Cuboid (
	Net_Rendition const &		nr,
	int							count,
	_hoops_SASC const * 		_hoops_HRIIH,
	float						_hoops_RRIIH,
	float						_hoops_ARIIH,
	Test alter *				results,
	float alter *				_hoops_PRIIH,
	float alter *				_hoops_CIHS)
{
	ASSERT(_hoops_HRIIH);
	ASSERT(results);

	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;

	_hoops_PACIR const &	_hoops_HCSR = nr->transform_rendition->_hoops_AGAA;

	_hoops_PACIR	_hoops_ACSR = _hoops_HCSR;
	if (_hoops_RRIIH != 0.0f)
		_hoops_ACSR._hoops_IACHA(_hoops_RRIIH);

	int		_hoops_PIHS = 0;
	float	_hoops_ACGRGR = -MAX_FLOAT;

	for (int i = 0; i < count; i++) {
		Point			in[8];

		_hoops_HRIIH[i]._hoops_GPSC(&in[0]);

		DC_Point		_hoops_PAGR[8];
		float			ws[8];
		_hoops_GRCAR		_hoops_ARCAR[8];

		int	_hoops_PCGRGR = (*HOOPS_WORLD->_hoops_PHCAR[_hoops_IHCR->_hoops_HGSC])
			(_hoops_IHCR, 8, in, &_hoops_IHCR->matrix->data.elements[0][0], &_hoops_HCSR, _hoops_PAGR, ws, _hoops_ARCAR);

		bool _hoops_HCGRGR = (_hoops_PCGRGR == 8);

		if (!_hoops_HCGRGR) {
			int			_hoops_HAHPP;

			if (_hoops_PCGRGR == 0) {
				/* _hoops_PGII _hoops_CHR _hoops_SIPP. _hoops_GCRR _hoops_RCRR _hoops_SSIA'_hoops_ASAR _hoops_HCR _hoops_SIPP _hoops_GPP _hoops_RH _hoops_PSHR _hoops_PPAP.*/

				_hoops_HAHPP  = (int)_hoops_ARCAR[0];
				_hoops_HAHPP &= (int)_hoops_ARCAR[1];
				_hoops_HAHPP &= (int)_hoops_ARCAR[2];
				_hoops_HAHPP &= (int)_hoops_ARCAR[3];
				_hoops_HAHPP &= (int)_hoops_ARCAR[4];
				_hoops_HAHPP &= (int)_hoops_ARCAR[5];
				_hoops_HAHPP &= (int)_hoops_ARCAR[6];
				_hoops_HAHPP &= (int)_hoops_ARCAR[7];

				if (_hoops_HAHPP != 0) {
					results[i] = Test_DISJOINT;
					continue;
				}
			}

			_hoops_HAHPP  = (int)_hoops_ARCAR[0];
			_hoops_HAHPP |= (int)_hoops_ARCAR[1];
			_hoops_HAHPP |= (int)_hoops_ARCAR[2];
			_hoops_HAHPP |= (int)_hoops_ARCAR[3];
			_hoops_HAHPP |= (int)_hoops_ARCAR[4];
			_hoops_HAHPP |= (int)_hoops_ARCAR[5];
			_hoops_HAHPP |= (int)_hoops_ARCAR[6];
			_hoops_HAHPP |= (int)_hoops_ARCAR[7];

			results[i] = _hoops_RAAGI;

			if (BIT (_hoops_HAHPP, _hoops_IPCAR)) {
				_hoops_ACGRGR = MAX_FLOAT;
				continue;
			}
		}

		bool _hoops_ICGRGR = (_hoops_CIHS != null || _hoops_PRIIH != null || _hoops_ARIIH != 0.0f);

		if (_hoops_HCGRGR || _hoops_ICGRGR) {
			_hoops_PACIR	rect = _hoops_PACIR(8, _hoops_PAGR);

			if (_hoops_HCGRGR) {
				if (_hoops_ACSR._hoops_HPCIR(rect))
					results[i] = _hoops_GAAGI;
				else
					results[i] = _hoops_RAAGI;	/* _hoops_GIAA '_hoops_CRIPR' _hoops_HIH _hoops_HAR '_hoops_PSSPR' */
			}

			if (_hoops_ICGRGR) {
				float _hoops_CCGRGR =  (rect.right - rect.left);
				float _hoops_SCGRGR =  (rect.top - rect.bottom);

				float _hoops_GSGRGR = _hoops_IAAA(_hoops_CCGRGR, _hoops_SCGRGR);

				if (_hoops_PRIIH)
					_hoops_PRIIH[i] = _hoops_GSGRGR;

				if (_hoops_ARIIH > 0.0f) {
					if (_hoops_GSGRGR <= _hoops_ARIIH) {
						results[i] |=  Test_EXTENT;
						if (_hoops_GSGRGR > _hoops_ACGRGR)
							_hoops_ACGRGR = _hoops_GSGRGR;
						continue;
					}
				}
				else if (_hoops_ARIIH < 0.0f) {
					if (_hoops_GSGRGR > -_hoops_ARIIH) {
						results[i] |=  Test_EXTENT;
						if (_hoops_GSGRGR > _hoops_ACGRGR)
							_hoops_ACGRGR = _hoops_GSGRGR;
						continue;
					}
				}
			}
		}

		_hoops_PIHS++;
	}

	if (_hoops_CIHS)
		*_hoops_CIHS = _hoops_ACGRGR;

	return _hoops_PIHS;
}



GLOBAL_FUNCTION int HD_Transform_And_Test_Simple_Sphere (
	Net_Rendition const &		nr,
	int							count,
	_hoops_CAIS const * 		_hoops_GRIIH,
	int const *					_hoops_ACHS,
	float						_hoops_RRIIH,
	float						_hoops_ARIIH,
	Test alter *				results,
	float alter *				_hoops_PRIIH,
	float alter *				_hoops_CIHS)
{

	ASSERT(_hoops_GRIIH);
	ASSERT(results);

	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_IHCR._hoops_SSAGR();

	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	_hoops_SGRA._hoops_SSAGR();

	if (!BIT (_hoops_IHCR->flags, _hoops_ICPHP))
		HD_Validate_Object_To_View (nr);

	_hoops_HHRA const *				_hoops_SPH = _hoops_IHCR->_hoops_SPH;
	_hoops_RPRA const *			matrix = (_hoops_RPRA const *)&_hoops_IHCR->_hoops_GGPSP->data.elements[0][0];
	_hoops_SSAGR(_hoops_SPH);
	_hoops_SSAGR(matrix);
	_hoops_SSAGR(_hoops_GRIIH);

	bool	_hoops_RSGRGR = BIT (_hoops_IHCR->_hoops_APH, Heur_Culling_VIEW_FRUSTUM) && !BIT (_hoops_IHCR->flags, _hoops_AIHS);
	float	_hoops_ISPA = 0.0f, _hoops_SSPA = 0.0f;
	float	_hoops_GHRGR = 0.0f;
	bool	_hoops_ASGRGR = false;

	float	_hoops_HIPHP = 1.0f;
	if (_hoops_PRIIH != null || _hoops_CIHS != null) {
		_hoops_HIPHP = _hoops_IHCR->_hoops_HIPHP;
#ifdef HOOPS_DEBUG_BUILD
		float	width = nr->_hoops_SAIR->_hoops_PHRA.right - nr->_hoops_SAIR->_hoops_PHRA.left;
		ASSERT(fabs(_hoops_IHCR->_hoops_HIPHP - width / _hoops_IHCR->_hoops_SPH->_hoops_ISPA) <= 0.000001f * _hoops_IHCR->_hoops_HIPHP);
#endif
	}

	//_hoops_PIP: _hoops_HHHR _hoops_CRRPA _hoops_SAIPR _hoops_AGSR "_hoops_PIIA _hoops_RH _hoops_RPGP" -- _hoops_IGI _hoops_IH _hoops_PSGRGR _hoops_HGISR
	if (ANYBIT (_hoops_IHCR->_hoops_APH, Heur_Culling_EXTENT|_hoops_RIHS)) {
		_hoops_GHRGR = _hoops_ARIIH * _hoops_IHCR->_hoops_IIPHP;
#ifdef HOOPS_DEBUG_BUILD
		float	width = nr->_hoops_SAIR->_hoops_PHRA.right - nr->_hoops_SAIR->_hoops_PHRA.left;
		ASSERT(width == 0.0f ||
				fabs(_hoops_IHCR->_hoops_IIPHP - _hoops_IHCR->_hoops_SPH->_hoops_ISPA / width) < 0.000001f * _hoops_IHCR->_hoops_IIPHP);
#endif
		if (_hoops_GHRGR != 0.0f)
			_hoops_ASGRGR = true;
	}

	if (_hoops_RSGRGR) {
		float	width = _hoops_SGRA->_hoops_PHRA.right - _hoops_SGRA->_hoops_PHRA.left;
		float	height = _hoops_SGRA->_hoops_PHRA.top - _hoops_SGRA->_hoops_PHRA.bottom;

		_hoops_ISPA = _hoops_SPH->_hoops_ISPA * 0.5;
		_hoops_SSPA = _hoops_SPH->_hoops_SSPA * 0.5;

		if (_hoops_SPH->projection != _hoops_SSIH) {
			float _hoops_ISIH = _hoops_SGRA->_hoops_CSIH *
									(_hoops_IHCR->_hoops_HCIH.top - _hoops_IHCR->_hoops_HCIH.bottom) /
									(_hoops_IHCR->_hoops_HCIH.right - _hoops_IHCR->_hoops_HCIH.left);

			if (_hoops_ISIH <= _hoops_SPH->_hoops_CSIH)
				_hoops_ISPA *= _hoops_SPH->_hoops_CSIH / _hoops_ISIH;
			else
				_hoops_SSPA *= _hoops_ISIH / _hoops_SPH->_hoops_CSIH;
		}

		if (_hoops_RRIIH > 0.0f)
			_hoops_RRIIH /= _hoops_AHIA(width, height) * 0.5f;

		_hoops_RRIIH += 1.0f;
	}

	bool	_hoops_HSGRGR = (_hoops_SPH->projection == _hoops_GHH);
	float	_hoops_ISGRGR = _hoops_SPH->_hoops_SRIR;

	float	_hoops_CSGRGR = 1.0f;
	bool	_hoops_SSGRGR = false;

	if (BIT (_hoops_IHCR->_hoops_GGPSP->data._hoops_RAGR, _hoops_CHCP)) {
		float length = matrix[0][0] * matrix[0][0] +
				 matrix[0][1] * matrix[0][1] +
				 matrix[0][2] * matrix[0][2];
		float tmp = matrix[1][0] * matrix[1][0] +
				 matrix[1][1] * matrix[1][1] +
				 matrix[1][2] * matrix[1][2];
		if (tmp > length)
			length = tmp;
		tmp	   = matrix[2][0] * matrix[2][0] +
				 matrix[2][1] * matrix[2][1] +
				 matrix[2][2] * matrix[2][2];
		if (tmp > length)
			length = tmp;

		_hoops_CSGRGR = _hoops_SGIHR(length);

		if (_hoops_CSGRGR != 1.0f)
			_hoops_SSGRGR = true;
	}

	float	_hoops_GGRRGR = -MAX_FLOAT;
	int		_hoops_PIHS = 0;
	bool	_hoops_RGRRGR = BIT (_hoops_IHCR->_hoops_GGPSP->data._hoops_RAGR, _hoops_CICH);

	for (int i = 0; i < count; i++) {
		if (_hoops_GRIIH[i].radius == -1.0f) {
			results[i] = _hoops_RAAGI;

			if (_hoops_PRIIH)
				_hoops_PRIIH[i] = -1.0f;

			_hoops_PIHS++;
			continue;
		}

		float	z;

		if (_hoops_RGRRGR)
			z = _hoops_CPRA (matrix, _hoops_GRIIH[i].center);
		else
			z = _hoops_GRIIH[i].center.z;

		float	radius = _hoops_GRIIH[i].radius;

		if (_hoops_SSGRGR)
			radius *= _hoops_CSGRGR;

		bool	_hoops_AGRRGR = false;
		float	_hoops_PGRRGR = radius;
		float	_hoops_RGRA = 1.0f;

		if (z >= -_hoops_ISGRGR + radius) {
			_hoops_RGRA =  _hoops_ISGRGR / (z + _hoops_ISGRGR);
			radius *= _hoops_RGRA;
		}
		else if (_hoops_HSGRGR) {
			if (z < -_hoops_ISGRGR - radius) {
				results[i] = Test_DISJOINT; /* _hoops_AGPC _hoops_GHIPR _hoops_RH _hoops_RHC */
				continue;
			}
			else
				_hoops_AGRRGR = true;
		}


		if (_hoops_PRIIH)
			_hoops_PRIIH[i] = radius * _hoops_HIPHP;

		if (_hoops_RSGRGR) {
			if (_hoops_HSGRGR)
				_hoops_PGRRGR = radius;
			else
				_hoops_RGRA = 1.0f;

			_hoops_PGRRGR *= _hoops_RRIIH;

			float y = _hoops_IPRA (matrix, _hoops_GRIIH[i].center);
			y *= _hoops_RGRA;
			if (y - _hoops_PGRRGR > _hoops_SSPA ||
				y + _hoops_PGRRGR < -_hoops_SSPA) {
				results[i] = Test_DISJOINT; /* _hoops_PSAP _hoops_IS _hoops_SCIA _hoops_PAR _hoops_PRPC */
				if (_hoops_ACHS && _hoops_ACHS[i] > 0) {
					SET_MEMORY (&results[i+1], _hoops_ACHS[i]*sizeof(Test), results[i]);
					i += _hoops_ACHS[i];
				}
				continue;
			}

			float x = _hoops_HPRA (matrix, _hoops_GRIIH[i].center);
			x *= _hoops_RGRA;
			if (x - _hoops_PGRRGR > _hoops_ISPA ||
				x + _hoops_PGRRGR < -_hoops_ISPA) {
				if (_hoops_ACHS && _hoops_ACHS[i] > 0) {
					SET_MEMORY (&results[i+1], _hoops_ACHS[i]*sizeof(Test), results[i]);
					i += _hoops_ACHS[i];
				}
				results[i] = Test_DISJOINT; /* _hoops_PSAP _hoops_IS _hoops_RPHR _hoops_PAR _hoops_RAAP */
				continue;
			}

			if (y + _hoops_PGRRGR > _hoops_SSPA ||
				y - _hoops_PGRRGR < -_hoops_SSPA) {
					results[i] = _hoops_RAAGI; /* _hoops_PSAP _hoops_IS _hoops_SCIA _hoops_PAR _hoops_PRPC */
			}
			else if (x + _hoops_PGRRGR > _hoops_ISPA ||
					 x - _hoops_PGRRGR < -_hoops_ISPA) {
					results[i] = _hoops_RAAGI; /* _hoops_PSAP _hoops_IS _hoops_RPHR _hoops_PAR _hoops_RAAP */
			}
			else
				results[i] = _hoops_GAAGI;
		}
		else
			results[i] = _hoops_RAAGI;

		if (_hoops_ASGRGR) {
			if (radius < _hoops_GHRGR) {
				results[i] |= Test_EXTENT;

				if (_hoops_CIHS &&
					radius > _hoops_GGRRGR)
					_hoops_GGRRGR = radius;

				if (_hoops_ACHS && _hoops_ACHS[i] > 0) {
					SET_MEMORY (&results[i+1], _hoops_ACHS[i]*sizeof(Test), results[i]);
					i += _hoops_ACHS[i];
				}
				continue;
			}
			else if (_hoops_GHRGR < 0 && radius >= -_hoops_GHRGR) {
				//_hoops_SR'_hoops_ASAR _hoops_HCHAR _hoops_IH _hoops_SAHR _hoops_RH _hoops_CIPH _hoops_SR _hoops_SARS'_hoops_RA _hoops_HGCR _hoops_AARI _hoops_IS _hoops_ARPP,
				//_hoops_HIS _hoops_SHRGS _hoops_RH _hoops_AHSC _hoops_CIPH _hoops_SR'_hoops_RISP _hoops_AIAH _hoops_CHCC
				if (!_hoops_ACHS || _hoops_ACHS[i] == 0)
					results[i] |= Test_EXTENT;

				if (_hoops_CIHS &&
					radius > _hoops_GGRRGR)
					_hoops_GGRRGR = radius;

				continue;
			}
		}

		_hoops_PIHS++;
		if (_hoops_AGRRGR)
			_hoops_GGRRGR = MAX_FLOAT;
	}

	if (_hoops_CIHS) {
		if (_hoops_GHRGR > 0)
			*_hoops_CIHS = _hoops_GGRRGR * _hoops_HIPHP;
		else
			*_hoops_CIHS = -_hoops_GGRRGR * _hoops_HIPHP;
	}

	return _hoops_PIHS;
}



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
 * $Id: obf_tmp.txt 1.96 2010-11-18 00:59:01 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

#ifndef DISABLE_COMPUTE

#ifdef _hoops_SIRCA
#	undef _hoops_SIRCA
#endif
#define _hoops_SIRCA					0
#define _hoops_GCRCA				1
#define _hoops_RCRCA				2
#define _hoops_ACRCA			3
#define _hoops_PCRCA			4
#define _hoops_HCRCA			5
#define _hoops_ICRCA			6
#define _hoops_CCRCA			7
#define _hoops_SCRCA			8
#define _hoops_GSRCA			9

#define _hoops_RSRCA		_hoops_RCRCA


local int _hoops_ASRCA (
	char const *		in_system) {
	char const *		_hoops_RPPA = in_system;
	int					result = _hoops_SIRCA;

	while (_hoops_RPPA[0] == ' ' || _hoops_RPPA[0] == '\t') _hoops_RPPA++;

	switch (_hoops_SHPCR (_hoops_RPPA[0])) {
		case 'c': {
			if (_hoops_SHPCR (_hoops_RPPA[1]) == 'a'  &&
				_hoops_SHPCR (_hoops_RPPA[2]) == 'm'  &&
				_hoops_SHPCR (_hoops_RPPA[3]) == 'e'  &&
				_hoops_SHPCR (_hoops_RPPA[4]) == 'r'  &&
				_hoops_SHPCR (_hoops_RPPA[5]) == 'a') {
				result = _hoops_RSRCA;
				_hoops_RPPA += 6;
			}
		}	break;

		case 'w': {
			if (_hoops_SHPCR (_hoops_RPPA[1]) == 'o'  &&
				_hoops_SHPCR (_hoops_RPPA[2]) == 'r'  &&
				_hoops_SHPCR (_hoops_RPPA[3]) == 'l'  &&
				_hoops_SHPCR (_hoops_RPPA[4]) == 'd') {
				result = _hoops_RCRCA;
				_hoops_RPPA += 5;
			}
		}	break;

		case 'v': {
			if (_hoops_SHPCR (_hoops_RPPA[1]) == 'i'  &&
				_hoops_SHPCR (_hoops_RPPA[2]) == 'e'  &&
				_hoops_SHPCR (_hoops_RPPA[3]) == 'w'  &&
				_hoops_SHPCR (_hoops_RPPA[4]) == 'p'  &&
				_hoops_SHPCR (_hoops_RPPA[5]) == 'o'  &&
				_hoops_SHPCR (_hoops_RPPA[6]) == 'i'  &&
				_hoops_SHPCR (_hoops_RPPA[7]) == 'n'  &&
				_hoops_SHPCR (_hoops_RPPA[8]) == 't') {
				result = _hoops_ACRCA;
				_hoops_RPPA += 9;
			}
		}	break;

		case 'p': {
			if (_hoops_SHPCR (_hoops_RPPA[1]) == 'r'  &&
				_hoops_SHPCR (_hoops_RPPA[2]) == 'o'  &&
				_hoops_SHPCR (_hoops_RPPA[3]) == 'j'  &&
				_hoops_SHPCR (_hoops_RPPA[4]) == 'e'  &&
				_hoops_SHPCR (_hoops_RPPA[5]) == 'c'  &&
				_hoops_SHPCR (_hoops_RPPA[6]) == 't'  &&
				_hoops_SHPCR (_hoops_RPPA[7]) == 'i'  &&
				_hoops_SHPCR (_hoops_RPPA[8]) == 'o'  &&
				_hoops_SHPCR (_hoops_RPPA[9]) == 'n') {
				result = _hoops_PCRCA;
				_hoops_RPPA += 10;
			}
		}	break;

		case 's': {
			if (_hoops_SHPCR (_hoops_RPPA[1]) == 'c'  &&
				_hoops_SHPCR (_hoops_RPPA[2]) == 'r'  &&
				_hoops_SHPCR (_hoops_RPPA[3]) == 'e'  &&
				_hoops_SHPCR (_hoops_RPPA[4]) == 'e'  &&
				_hoops_SHPCR (_hoops_RPPA[5]) == 'n'  &&
				_hoops_SHPCR (_hoops_RPPA[6]) == ' '  &&
				_hoops_SHPCR (_hoops_RPPA[7]) == 'r'  &&
				_hoops_SHPCR (_hoops_RPPA[8]) == 'a'  &&
				_hoops_SHPCR (_hoops_RPPA[9]) == 'n'  &&
				_hoops_SHPCR (_hoops_RPPA[10]) == 'g'  &&
				_hoops_SHPCR (_hoops_RPPA[11]) == 'e') {
				result = _hoops_HCRCA;
				_hoops_RPPA += 12;
			}
		}	break;

		case 'l': {
			if (_hoops_SHPCR (_hoops_RPPA[1]) == 'o'  &&
				_hoops_SHPCR (_hoops_RPPA[2]) == 'c'  &&
				_hoops_SHPCR (_hoops_RPPA[3]) == 'a'  &&
				_hoops_SHPCR (_hoops_RPPA[4]) == 'l'  &&
				_hoops_SHPCR (_hoops_RPPA[5]) == ' ') {
				if (_hoops_SHPCR (_hoops_RPPA[6])	  == 'w') {
					if (_hoops_SHPCR (_hoops_RPPA[7]) == 'i'  &&
						_hoops_SHPCR (_hoops_RPPA[8]) == 'n'  &&
						_hoops_SHPCR (_hoops_RPPA[9]) == 'd'  &&
						_hoops_SHPCR (_hoops_RPPA[10]) == 'o'	&&
						_hoops_SHPCR (_hoops_RPPA[11]) == 'w') {
						result = _hoops_ICRCA;
						_hoops_RPPA += 12;
					}
				}
				else if (_hoops_SHPCR (_hoops_RPPA[6]) == 'p') {
					if (_hoops_SHPCR (_hoops_RPPA[7]) == 'i'  &&
						_hoops_SHPCR (_hoops_RPPA[8]) == 'x'  &&
						_hoops_SHPCR (_hoops_RPPA[9]) == 'e'  &&
						_hoops_SHPCR (_hoops_RPPA[10]) == 'l'	&&
						_hoops_SHPCR (_hoops_RPPA[11]) == 's') {
						result = _hoops_CCRCA;
						_hoops_RPPA += 12;
					}
				}
			}
		}	break;

		case 'o': {
			if (_hoops_SHPCR (_hoops_RPPA[1]) == 'b') {
				if (_hoops_SHPCR (_hoops_RPPA[2]) == 'j'  &&
					_hoops_SHPCR (_hoops_RPPA[3]) == 'e'  &&
					_hoops_SHPCR (_hoops_RPPA[4]) == 'c'  &&
					_hoops_SHPCR (_hoops_RPPA[5]) == 't') {
					result = _hoops_GCRCA;
					_hoops_RPPA += 6;
				}
			}
			else if (_hoops_SHPCR (_hoops_RPPA[1]) == 'u') {
				if (_hoops_SHPCR (_hoops_RPPA[2]) == 't'  &&
					 _hoops_SHPCR (_hoops_RPPA[3]) == 'e'	&&
					 _hoops_SHPCR (_hoops_RPPA[4]) == 'r'	&&
					 _hoops_SHPCR (_hoops_RPPA[5]) == ' ') {
					if (_hoops_SHPCR (_hoops_RPPA[6])	   == 'w') {
						if (_hoops_SHPCR (_hoops_RPPA[7])	== 'i'	&&
							_hoops_SHPCR (_hoops_RPPA[8])	== 'n'	&&
							_hoops_SHPCR (_hoops_RPPA[9])	== 'd'	&&
							_hoops_SHPCR (_hoops_RPPA[10]) == 'o'	&&
							_hoops_SHPCR (_hoops_RPPA[11]) == 'w') {
							result = _hoops_SCRCA;
							_hoops_RPPA += 12;
						}
					}
					else if (_hoops_SHPCR (_hoops_RPPA[6])	 == 'p') {
						if (_hoops_SHPCR (_hoops_RPPA[7])	== 'i'	&&
							 _hoops_SHPCR (_hoops_RPPA[8])	 == 'x'	 &&
							 _hoops_SHPCR (_hoops_RPPA[9])	 == 'e'	 &&
							 _hoops_SHPCR (_hoops_RPPA[10]) == 'l'	 &&
							 _hoops_SHPCR (_hoops_RPPA[11]) == 's') {
							result = _hoops_GSRCA;
							_hoops_RPPA += 12;
						}
					}
				}
			}
		}	break;
	}

	if (_hoops_RPPA[0] != '\0') {		/* _hoops_RSH _hoops_SSHRR */
		while (_hoops_RPPA[0] == ' ' || _hoops_RPPA[0] == '\t') _hoops_RPPA++;		/* _hoops_PSRCA _hoops_RGR */
		if (_hoops_RPPA[0] != '\0') result = _hoops_SIRCA;			/* _hoops_HAR _hoops_IRS _hoops_PSSP */
	}

	return result;
}

#endif


GLOBAL_FUNCTION bool HI_Compute_Transform_By_Path (
	_hoops_AIGPR *	_hoops_RIGC,
	int						count,
	Key const *				keys,
	char const *			in_system,
	char const *			out_system,
	float alter *			resultp) {

#ifndef DISABLE_COMPUTE
	_hoops_RPRA alter *		result = (_hoops_RPRA alter *)resultp;
	float					_hoops_HSRCA, _hoops_ISRCA;
	int						_hoops_CSRCA, _hoops_SSRCA;
	_hoops_RPRA				matrix[4];
	_hoops_RPRA				_hoops_GGACA[4];
	_hoops_RPRA				_hoops_RGACA[4];
	float					left, right, bottom, top;
	float					_hoops_AGACA, _hoops_PGACA;
	int						_hoops_HGACA, _hoops_IGACA;
	int						_hoops_CGACA, _hoops_SGACA, _hoops_GRACA, _hoops_RRACA;
	int						_hoops_ARACA, _hoops_PRACA;
	float					_hoops_ISIH;
	_hoops_HHRA *				_hoops_SPH = null;
	_hoops_RHAIR *		_hoops_AHAIR = null;
	Attribute *				_hoops_ASGPR;
	int						_hoops_HRACA;
	_hoops_CRCP const **		_hoops_SISAA;
	int						_hoops_CISAA;
	
	_hoops_RRACA = _hoops_CGACA = _hoops_IGACA = _hoops_HGACA = 0;
	_hoops_PGACA = _hoops_AGACA = 0.0f;

	if ((_hoops_CSRCA = _hoops_ASRCA (in_system)) == _hoops_SIRCA) {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_COORDINATE_SPACE,
				Sprintf_S (null,  "Unrecognized input coordinate space '%s'", in_system));
		return false;
	}

	if ((_hoops_SSRCA = _hoops_ASRCA (out_system)) == _hoops_SIRCA) {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_COORDINATE_SPACE,
				Sprintf_S (null,  "Unrecognized output coordinate space '%s'", out_system));
		return false;
	}

	HI_Compute_Identity_Matrix (&result[0][0]);

	if (_hoops_SSRCA == _hoops_CSRCA)  
		return  true;			/* _hoops_RPAPR */

	if ((_hoops_CISAA = HI_Convert_Keys_To_Path (_hoops_RIGC, count, keys, _hoops_SISAA)) == 0) {
		HE_ERROR (HEC_SEGMENT, HES_INVALID_KEY, "Provided key does not refer to a valid Segment");
		goto _hoops_IRACA;
	}

	_hoops_CRACA	control;
	ZERO_STRUCT (&control, _hoops_CRACA);

	if ((_hoops_AHAIR = (_hoops_RHAIR *)HI_Find_Net_Attribute_By_Path (_hoops_RIGC, _hoops_CISAA, (_hoops_CRCP const **)_hoops_SISAA, HK_RENDERING_OPTIONS)) == null)
		goto _hoops_IRACA;

	/* _hoops_PA _hoops_PGAP _hoops_CRRPR _hoops_PRGIA _hoops_PAR _hoops_SARA _hoops_SGS _hoops_SIAS _hoops_SHH _hoops_CISH -- _hoops_HHSH _hoops_CPS _hoops_SHS */
	if (_hoops_CSRCA >= _hoops_PCRCA || _hoops_SSRCA >= _hoops_PCRCA) {
		float			scale;

		if (!HI_Compute_Window_Extent_By_Pth (_hoops_RIGC, _hoops_CISAA, _hoops_SISAA, &_hoops_AGACA, &_hoops_PGACA, &_hoops_HGACA, &_hoops_IGACA,
												&_hoops_CGACA, &_hoops_SGACA, &_hoops_GRACA, &_hoops_RRACA))
			goto _hoops_IRACA;

		_hoops_ARACA = _hoops_SGACA - _hoops_CGACA + 1;
		_hoops_PRACA = _hoops_RRACA - _hoops_GRACA + 1;

		if (_hoops_HGACA < 2 || _hoops_IGACA < 2)
			goto _hoops_IRACA;

		scale = 2.0f / (float)(_hoops_HGACA-1);
		left   = (float)_hoops_CGACA	* scale - 1.0f;
		right  = (float)_hoops_SGACA	* scale - 1.0f;
		scale = 2.0f / (float)(_hoops_IGACA-1);
		bottom = (float)_hoops_GRACA * scale - 1.0f;
		top	   = (float)_hoops_RRACA	* scale - 1.0f;

		control._hoops_ISIH = (float)(_hoops_RRACA - _hoops_GRACA) / (float)(_hoops_SGACA - _hoops_CGACA) *
								_hoops_PGACA / _hoops_AGACA *
								(_hoops_AHAIR->_hoops_HCIH.top - _hoops_AHAIR->_hoops_HCIH.bottom) /
								(_hoops_AHAIR->_hoops_HCIH.right - _hoops_AHAIR->_hoops_HCIH.left);
	}
	else {
		_hoops_ARACA = _hoops_PRACA = 1;
		left = right = bottom = top = 0.0f;
		control._hoops_ISIH = 1.0f;
	}


	if ((_hoops_SPH = (_hoops_HHRA *)HI_Find_Net_Attribute_By_Path (_hoops_RIGC, _hoops_CISAA, (_hoops_CRCP const **)_hoops_SISAA, HK_CAMERA)) == null)
		goto _hoops_IRACA;

	if (!HI_Camera_To_Transform (_hoops_SPH, 0.0))
		goto _hoops_IRACA;

	HI_Copy_44 (&_hoops_SPH->_hoops_PRPA.elements[0][0], &_hoops_GGACA[0][0]);
	HI_Copy_44 (&_hoops_SPH->_hoops_AIIH.elements[0][0], &_hoops_RGACA[0][0]);
	control._hoops_SPH = _hoops_SPH;

	if ((_hoops_ASGPR = HI_Find_Net_Attribute_By_Path (_hoops_RIGC, _hoops_CISAA, (_hoops_CRCP const **)_hoops_SISAA, HK_HANDEDNESS)) == null)
		goto _hoops_IRACA;
	_hoops_HRACA = ((_hoops_ARAIR *)_hoops_ASGPR)->which;
	_hoops_HPRH (_hoops_ASGPR);


	if (_hoops_CSRCA < _hoops_SSRCA)	 switch (_hoops_CSRCA) {
		case _hoops_GCRCA: {
			/* _hoops_CARA -> _hoops_GSSP */
			_hoops_ISGI		*modelling_matrix;

			if ((modelling_matrix = (_hoops_ISGI *)HI_Find_Net_Attribute_By_Path (_hoops_RIGC, _hoops_CISAA, (_hoops_CRCP const **)_hoops_SISAA, 
																						HK_MODELLING_MATRIX, _hoops_SRACA, &control)) == null)
				goto _hoops_IRACA;

			HI_Copy_43 (&modelling_matrix->matrix.elements[0][0], &result[0][0]);
			result[0][3] = result[1][3] = result[2][3] = 0.0f;
			result[3][3] = 1.0f;

			_hoops_HPRH (modelling_matrix);

			if (_hoops_SSRCA == _hoops_RCRCA)	 break;
		} _hoops_HHHI;

		case _hoops_RCRCA: {
			/* _hoops_GSSP * _hoops_SARA -> _hoops_GAACA */

			if (_hoops_CSRCA == _hoops_RCRCA)
				HI_Copy_44 (&_hoops_GGACA[0][0], &result[0][0]);
			else {
				HI_Compute_Matrix_Product (&result[0][0], &_hoops_GGACA[0][0], &result[0][0]);
			}
			result[3][2] += _hoops_SPH->_hoops_SRIR;				/* _hoops_PHCH _hoops_GGR _hoops_AHCR */

			if (_hoops_SSRCA == _hoops_ACRCA)	 break;
		} _hoops_HHHI;

		case _hoops_ACRCA: {
			/* _hoops_GAACA * _hoops_AIHP -> _hoops_PHCR */

			result[3][2] -= _hoops_SPH->_hoops_SRIR;				/* _hoops_PHCH _hoops_GGR _hoops_AHCR */
			HI_Compute_Matrix_Product (&result[0][0], &_hoops_RGACA[0][0], &result[0][0]);

			if (_hoops_SSRCA == _hoops_PCRCA)  break;
		}

		case _hoops_PCRCA: {
			/* _hoops_PHCR -> _hoops_SHPR _hoops_CCIR */

			_hoops_ISIH = (float)_hoops_PRACA / (float)_hoops_ARACA	 *	_hoops_AGACA / _hoops_PGACA;
			_hoops_ISIH *= (_hoops_AHAIR->_hoops_HCIH.top - _hoops_AHAIR->_hoops_HCIH.bottom) /
							 (_hoops_AHAIR->_hoops_HCIH.right - _hoops_AHAIR->_hoops_HCIH.left);

			_hoops_HSRCA = _hoops_ISRCA = 1.0f;

			if (_hoops_SPH->projection != _hoops_SSIH) {
				if (_hoops_SPH->_hoops_CSIH < _hoops_ISIH)
					_hoops_ISRCA *= _hoops_SPH->_hoops_CSIH / _hoops_ISIH;
				else
					_hoops_HSRCA *= _hoops_ISIH / _hoops_SPH->_hoops_CSIH;
			}

			if (_hoops_HRACA == _hoops_RAACA) _hoops_HSRCA = -_hoops_HSRCA;

			/* _hoops_CSRA */
			result[0][0] *= _hoops_HSRCA;
			result[1][0] *= _hoops_HSRCA;
			result[2][0] *= _hoops_HSRCA;
			result[3][0] *= _hoops_HSRCA;

			result[0][1] *= _hoops_ISRCA;
			result[1][1] *= _hoops_ISRCA;
			result[2][1] *= _hoops_ISRCA;
			result[3][1] *= _hoops_ISRCA;

			if (_hoops_SSRCA == _hoops_HCRCA)  break;
		}

		case _hoops_HCRCA: {
			/* _hoops_SHPR _hoops_CCIR -> _hoops_IRGH _hoops_RPPS */

			_hoops_HSRCA = 0.5f * (_hoops_AHAIR->_hoops_HCIH.right - _hoops_AHAIR->_hoops_HCIH.left);
			_hoops_ISRCA = 0.5f * (_hoops_AHAIR->_hoops_HCIH.top - _hoops_AHAIR->_hoops_HCIH.bottom);

			result[0][0] *= _hoops_HSRCA;
			result[1][0] *= _hoops_HSRCA;
			result[2][0] *= _hoops_HSRCA;
			result[3][0] *= _hoops_HSRCA;

			result[0][1] *= _hoops_ISRCA;
			result[1][1] *= _hoops_ISRCA;
			result[2][1] *= _hoops_ISRCA;
			result[3][1] *= _hoops_ISRCA;

			_hoops_HSRCA = 0.5f * (_hoops_AHAIR->_hoops_HCIH.left + _hoops_AHAIR->_hoops_HCIH.right);
			_hoops_ISRCA = 0.5f * (_hoops_AHAIR->_hoops_HCIH.bottom + _hoops_AHAIR->_hoops_HCIH.top);

			result[0][0] += _hoops_HSRCA * result[0][3];
			result[0][1] += _hoops_ISRCA * result[0][3];
			result[1][0] += _hoops_HSRCA * result[1][3];
			result[1][1] += _hoops_ISRCA * result[1][3];
			result[2][0] += _hoops_HSRCA * result[2][3];
			result[2][1] += _hoops_ISRCA * result[2][3];
			result[3][0] += _hoops_HSRCA * result[3][3];
			result[3][1] += _hoops_ISRCA * result[3][3];

			if (_hoops_SSRCA == _hoops_ICRCA)	break;
		} _hoops_HHHI;

		case _hoops_ICRCA: {
			if (_hoops_SSRCA == _hoops_CCRCA) {
				/* _hoops_CSRA */
				_hoops_HSRCA = (_hoops_ARACA-1) * 0.5f;
				_hoops_ISRCA = (_hoops_PRACA-1) * -0.5f;

				result[0][0] *= _hoops_HSRCA;
				result[1][0] *= _hoops_HSRCA;
				result[2][0] *= _hoops_HSRCA;
				result[3][0] *= _hoops_HSRCA;

				result[0][1] *= _hoops_ISRCA;
				result[1][1] *= _hoops_ISRCA;
				result[2][1] *= _hoops_ISRCA;
				result[3][1] *= _hoops_ISRCA;


				/* _hoops_PHCH */
				_hoops_ISRCA = -_hoops_ISRCA;

				result[0][0] += _hoops_HSRCA * result[0][3];
				result[0][1] += _hoops_ISRCA * result[0][3];
				result[1][0] += _hoops_HSRCA * result[1][3];
				result[1][1] += _hoops_ISRCA * result[1][3];
				result[2][0] += _hoops_HSRCA * result[2][3];
				result[2][1] += _hoops_ISRCA * result[2][3];
				result[3][0] += _hoops_HSRCA * result[3][3];
				result[3][1] += _hoops_ISRCA * result[3][3];
				break;
			}
		} _hoops_HHHI;

		case _hoops_CCRCA: {
			if (_hoops_CSRCA == _hoops_CCRCA) {
				if (_hoops_SSRCA == _hoops_GSRCA) {		/* _hoops_PICAA! */
					/* _hoops_PHCH */
					_hoops_HSRCA = (float)_hoops_CGACA;
					_hoops_ISRCA = (float)(_hoops_IGACA-1 - _hoops_RRACA);

					result[0][0] += _hoops_HSRCA * result[0][3];
					result[0][1] += _hoops_ISRCA * result[0][3];
					result[1][0] += _hoops_HSRCA * result[1][3];
					result[1][1] += _hoops_ISRCA * result[1][3];
					result[2][0] += _hoops_HSRCA * result[2][3];
					result[2][1] += _hoops_ISRCA * result[2][3];
					result[3][0] += _hoops_HSRCA * result[3][3];
					result[3][1] += _hoops_ISRCA * result[3][3];

					break;
				}

				/* _hoops_IRGH _hoops_ASPA -> _hoops_IRGH _hoops_RPPS */

				/* _hoops_CSRA */
				if (_hoops_ARACA < 2 || _hoops_PRACA < 2)
					goto _hoops_IRACA;
				_hoops_HSRCA = 2.0f / (_hoops_ARACA-1);
				_hoops_ISRCA = -2.0f / (_hoops_PRACA-1);

				result[0][0] *= _hoops_HSRCA;
				result[1][0] *= _hoops_HSRCA;
				result[2][0] *= _hoops_HSRCA;
				result[3][0] *= _hoops_HSRCA;

				result[0][1] *= _hoops_ISRCA;
				result[1][1] *= _hoops_ISRCA;
				result[2][1] *= _hoops_ISRCA;
				result[3][1] *= _hoops_ISRCA;

				/* _hoops_PHCH (_hoops_AAACA _hoops_CHR +/- 1.0) */
				result[0][0] -= result[0][3];
				result[0][1] += result[0][3];
				result[1][0] -= result[1][3];
				result[1][1] += result[1][3];
				result[2][0] -= result[2][3];
				result[2][1] += result[2][3];
				result[3][0] -= result[3][3];
				result[3][1] += result[3][3];
			}

			/* _hoops_IRGH -> _hoops_CRIPR */

			/* _hoops_CSRA */
			_hoops_HSRCA = 0.5f * (right - left);
			_hoops_ISRCA = 0.5f * (top - bottom);

			result[0][0] *= _hoops_HSRCA;
			result[1][0] *= _hoops_HSRCA;
			result[2][0] *= _hoops_HSRCA;
			result[3][0] *= _hoops_HSRCA;

			result[0][1] *= _hoops_ISRCA;
			result[1][1] *= _hoops_ISRCA;
			result[2][1] *= _hoops_ISRCA;
			result[3][1] *= _hoops_ISRCA;

			/* _hoops_PHCH */
			_hoops_HSRCA = 0.5f * (left+right);
			_hoops_ISRCA = 0.5f * (bottom+top);

			result[0][0] += _hoops_HSRCA * result[0][3];
			result[0][1] += _hoops_ISRCA * result[0][3];
			result[1][0] += _hoops_HSRCA * result[1][3];
			result[1][1] += _hoops_ISRCA * result[1][3];
			result[2][0] += _hoops_HSRCA * result[2][3];
			result[2][1] += _hoops_ISRCA * result[2][3];
			result[3][0] += _hoops_HSRCA * result[3][3];
			result[3][1] += _hoops_ISRCA * result[3][3];

			if (_hoops_SSRCA == _hoops_SCRCA)	break;
		} _hoops_HHHI;

		case _hoops_SCRCA: {
			/* _hoops_SSS _hoops_PPR _hoops_GHAA _hoops_AIR _hoops_HSH _hoops_IS _hoops_CRIPR _hoops_AISIR _hoops_CPHH */

			/* _hoops_CRIPR _hoops_RPPS -> _hoops_CRIPR _hoops_ASPA */

			/* _hoops_CSRA */
			_hoops_HSRCA = (_hoops_HGACA-1) * 0.5f;
			_hoops_ISRCA = (_hoops_IGACA-1) * -0.5f;

			result[0][0] *= _hoops_HSRCA;
			result[1][0] *= _hoops_HSRCA;
			result[2][0] *= _hoops_HSRCA;
			result[3][0] *= _hoops_HSRCA;

			result[0][1] *= _hoops_ISRCA;
			result[1][1] *= _hoops_ISRCA;
			result[2][1] *= _hoops_ISRCA;
			result[3][1] *= _hoops_ISRCA;

			/* _hoops_PHCH */
			_hoops_ISRCA = -_hoops_ISRCA;

			result[0][0] += _hoops_HSRCA * result[0][3];
			result[0][1] += _hoops_ISRCA * result[0][3];
			result[1][0] += _hoops_HSRCA * result[1][3];
			result[1][1] += _hoops_ISRCA * result[1][3];
			result[2][0] += _hoops_HSRCA * result[2][3];
			result[2][1] += _hoops_ISRCA * result[2][3];
			result[3][0] += _hoops_HSRCA * result[3][3];
			result[3][1] += _hoops_ISRCA * result[3][3];

			if (_hoops_SSRCA == _hoops_GSRCA)	break;
		} _hoops_HHHI;

		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "Unrecognized coordinate space value");
			goto _hoops_IRACA;
	}
	else  switch (_hoops_CSRCA) {
		case _hoops_GSRCA: {
			if (_hoops_SSRCA == _hoops_CCRCA) {	/* _hoops_PICAA! */
				/* _hoops_PHCH */
				_hoops_HSRCA = (float)(-_hoops_CGACA);
				_hoops_ISRCA = (float)(-(_hoops_IGACA-1 - _hoops_RRACA));

				result[0][0] += _hoops_HSRCA * result[0][3];
				result[0][1] += _hoops_ISRCA * result[0][3];
				result[1][0] += _hoops_HSRCA * result[1][3];
				result[1][1] += _hoops_ISRCA * result[1][3];
				result[2][0] += _hoops_HSRCA * result[2][3];
				result[2][1] += _hoops_ISRCA * result[2][3];
				result[3][0] += _hoops_HSRCA * result[3][3];
				result[3][1] += _hoops_ISRCA * result[3][3];

				break;
			}


			/* _hoops_CRIPR _hoops_ASPA -> _hoops_CRIPR _hoops_RPPS */

			/* _hoops_PHCH */
			_hoops_HSRCA = -0.5f * (_hoops_HGACA-1);
			_hoops_ISRCA = -0.5f * (_hoops_IGACA-1);

			result[0][0] += _hoops_HSRCA * result[0][3];
			result[0][1] += _hoops_ISRCA * result[0][3];
			result[1][0] += _hoops_HSRCA * result[1][3];
			result[1][1] += _hoops_ISRCA * result[1][3];
			result[2][0] += _hoops_HSRCA * result[2][3];
			result[2][1] += _hoops_ISRCA * result[2][3];
			result[3][0] += _hoops_HSRCA * result[3][3];
			result[3][1] += _hoops_ISRCA * result[3][3];

			/* _hoops_CSRA */
			/* _hoops_PAACA & _hoops_HAACA _hoops_RAICR _hoops_ARRS */
			_hoops_HSRCA = 2.0f / (_hoops_HGACA-1);
			_hoops_ISRCA = -2.0f / (_hoops_IGACA-1);

			result[0][0] *= _hoops_HSRCA;
			result[1][0] *= _hoops_HSRCA;
			result[2][0] *= _hoops_HSRCA;
			result[3][0] *= _hoops_HSRCA;

			result[0][1] *= _hoops_ISRCA;
			result[1][1] *= _hoops_ISRCA;
			result[2][1] *= _hoops_ISRCA;
			result[3][1] *= _hoops_ISRCA;

			if (_hoops_SSRCA == _hoops_SCRCA)	break;
		} _hoops_HHHI;

		case _hoops_SCRCA: {
			/* _hoops_CRIPR -> _hoops_IRGH */

			/* _hoops_PHCH */
			_hoops_HSRCA = -0.5f * (left + right);
			_hoops_ISRCA = -0.5f * (bottom + top);

			result[0][0] += _hoops_HSRCA * result[0][3];
			result[0][1] += _hoops_ISRCA * result[0][3];
			result[1][0] += _hoops_HSRCA * result[1][3];
			result[1][1] += _hoops_ISRCA * result[1][3];
			result[2][0] += _hoops_HSRCA * result[2][3];
			result[2][1] += _hoops_ISRCA * result[2][3];
			result[3][0] += _hoops_HSRCA * result[3][3];
			result[3][1] += _hoops_ISRCA * result[3][3];

			/* _hoops_CSRA */
			if (left == right || bottom == top)
				goto _hoops_IRACA;
			_hoops_HSRCA = 2.0f / (right - left);
			_hoops_ISRCA = 2.0f / (top - bottom);

			result[0][0] *= _hoops_HSRCA;
			result[1][0] *= _hoops_HSRCA;
			result[2][0] *= _hoops_HSRCA;
			result[3][0] *= _hoops_HSRCA;

			result[0][1] *= _hoops_ISRCA;
			result[1][1] *= _hoops_ISRCA;
			result[2][1] *= _hoops_ISRCA;
			result[3][1] *= _hoops_ISRCA;

			if (_hoops_SSRCA == _hoops_CCRCA) {
				_hoops_HSRCA = (_hoops_ARACA-1) * 0.5f;
				_hoops_ISRCA = (_hoops_PRACA-1) * -0.5f;

				/* _hoops_IRGH -> _hoops_IRGH _hoops_ASPA */
				/* _hoops_CSRA */
				result[0][0] *= _hoops_HSRCA;
				result[1][0] *= _hoops_HSRCA;
				result[2][0] *= _hoops_HSRCA;
				result[3][0] *= _hoops_HSRCA;

				result[0][1] *= _hoops_ISRCA;
				result[1][1] *= _hoops_ISRCA;
				result[2][1] *= _hoops_ISRCA;
				result[3][1] *= _hoops_ISRCA;

				/* _hoops_PHCH */
				_hoops_ISRCA = -_hoops_ISRCA;

				result[0][0] += _hoops_HSRCA * result[0][3];
				result[0][1] += _hoops_ISRCA * result[0][3];
				result[1][0] += _hoops_HSRCA * result[1][3];
				result[1][1] += _hoops_ISRCA * result[1][3];
				result[2][0] += _hoops_HSRCA * result[2][3];
				result[2][1] += _hoops_ISRCA * result[2][3];
				result[3][0] += _hoops_HSRCA * result[3][3];
				result[3][1] += _hoops_ISRCA * result[3][3];
				break;
			}
		} _hoops_HHHI;

		case _hoops_CCRCA: {
			if (_hoops_CSRCA == _hoops_CCRCA) {
				/* _hoops_IRGH _hoops_ASPA -> _hoops_IRGH _hoops_RPPS */

				/* _hoops_CSRA */
				if (_hoops_ARACA < 2 || _hoops_PRACA < 2)
					goto _hoops_IRACA;
				_hoops_HSRCA = 2.0f / (_hoops_ARACA-1);
				_hoops_ISRCA = -2.0f / (_hoops_PRACA-1);

				result[0][0] *= _hoops_HSRCA;
				result[1][0] *= _hoops_HSRCA;
				result[2][0] *= _hoops_HSRCA;
				result[3][0] *= _hoops_HSRCA;

				result[0][1] *= _hoops_ISRCA;
				result[1][1] *= _hoops_ISRCA;
				result[2][1] *= _hoops_ISRCA;
				result[3][1] *= _hoops_ISRCA;

				/* _hoops_PHCH (_hoops_AAACA _hoops_CHR +/1 1.0) */

				result[0][0] -= result[0][3];
				result[0][1] += result[0][3];
				result[1][0] -= result[1][3];
				result[1][1] += result[1][3];
				result[2][0] -= result[2][3];
				result[2][1] += result[2][3];
				result[3][0] -= result[3][3];
				result[3][1] += result[3][3];
			}

			if (_hoops_SSRCA == _hoops_ICRCA)	break;
		} _hoops_HHHI;

		case _hoops_ICRCA: {
			/* _hoops_IRGH _hoops_RPPS -> _hoops_GSCHA */
			_hoops_HSRCA = -0.5f * (_hoops_AHAIR->_hoops_HCIH.left + _hoops_AHAIR->_hoops_HCIH.right);
			_hoops_ISRCA = -0.5f * (_hoops_AHAIR->_hoops_HCIH.bottom + _hoops_AHAIR->_hoops_HCIH.top);

			result[0][0] += _hoops_HSRCA * result[0][3];
			result[0][1] += _hoops_ISRCA * result[0][3];
			result[1][0] += _hoops_HSRCA * result[1][3];
			result[1][1] += _hoops_ISRCA * result[1][3];
			result[2][0] += _hoops_HSRCA * result[2][3];
			result[2][1] += _hoops_ISRCA * result[2][3];
			result[3][0] += _hoops_HSRCA * result[3][3];
			result[3][1] += _hoops_ISRCA * result[3][3];

			_hoops_HSRCA = 2.0f / (_hoops_AHAIR->_hoops_HCIH.right - _hoops_AHAIR->_hoops_HCIH.left);
			_hoops_ISRCA = 2.0f / (_hoops_AHAIR->_hoops_HCIH.top - _hoops_AHAIR->_hoops_HCIH.bottom);

			result[0][0] *= _hoops_HSRCA;
			result[1][0] *= _hoops_HSRCA;
			result[2][0] *= _hoops_HSRCA;
			result[3][0] *= _hoops_HSRCA;

			result[0][1] *= _hoops_ISRCA;
			result[1][1] *= _hoops_ISRCA;
			result[2][1] *= _hoops_ISRCA;
			result[3][1] *= _hoops_ISRCA;

			if (_hoops_SSRCA == _hoops_HCRCA)	break;
		} _hoops_HHHI;

		case _hoops_HCRCA: {
			/* _hoops_SHPR _hoops_CCIR -> _hoops_PHCR (_hoops_PAISR _hoops_SHPR _hoops_SAAA) */

			/* _hoops_IAACA */
			_hoops_ISIH = (float)_hoops_PRACA / (float)_hoops_ARACA	 *	_hoops_AGACA / _hoops_PGACA;
			_hoops_ISIH *= (_hoops_AHAIR->_hoops_HCIH.top - _hoops_AHAIR->_hoops_HCIH.bottom) /
							 (_hoops_AHAIR->_hoops_HCIH.right - _hoops_AHAIR->_hoops_HCIH.left);

			_hoops_HSRCA = _hoops_ISRCA = 1.0f;

			if (_hoops_SPH->projection != _hoops_SSIH) {
				if (_hoops_SPH->_hoops_CSIH < _hoops_ISIH)
					_hoops_ISRCA *= _hoops_SPH->_hoops_CSIH / _hoops_ISIH;
				else
					_hoops_HSRCA *= _hoops_ISIH / _hoops_SPH->_hoops_CSIH;
			}

			if (_hoops_HRACA == _hoops_RAACA) _hoops_HSRCA = -_hoops_HSRCA;

			_hoops_HSRCA = 1.0f / _hoops_HSRCA;
			_hoops_ISRCA = 1.0f / _hoops_ISRCA;

			/* _hoops_CSRA */
			result[0][0] *= _hoops_HSRCA;
			result[1][0] *= _hoops_HSRCA;
			result[2][0] *= _hoops_HSRCA;
			result[3][0] *= _hoops_HSRCA;

			result[0][1] *= _hoops_ISRCA;
			result[1][1] *= _hoops_ISRCA;
			result[2][1] *= _hoops_ISRCA;
			result[3][1] *= _hoops_ISRCA;

			if (_hoops_SSRCA == _hoops_PCRCA)  break;
		} _hoops_HHHI;

		case _hoops_PCRCA: {
			/* _hoops_PHCR / _hoops_AIHP -> _hoops_GAACA */

			if (_hoops_CSRCA == _hoops_PCRCA) {
				if (!HI_Compute_Matrix_Inverse (&_hoops_RGACA[0][0], &result[0][0])) {
					goto _hoops_IRACA;
				}
			}
			else {
				if (!HI_Compute_Matrix_Inverse (&_hoops_RGACA[0][0], &matrix[0][0])) {
					goto _hoops_IRACA;
				}

				HI_Compute_Matrix_Product (&result[0][0], &matrix[0][0], &result[0][0]);
			}

			/* _hoops_PHCH _hoops_GGR _hoops_AHCR */
			result[2][2] += _hoops_SPH->_hoops_SRIR * result[2][3];
			result[3][2] += _hoops_SPH->_hoops_SRIR;

			if (_hoops_SSRCA == _hoops_ACRCA)	 break;
		} _hoops_HHHI;

		case _hoops_ACRCA: {
			/* _hoops_GAACA / _hoops_RIHCR -> _hoops_GSSP */

			/* _hoops_PHCH _hoops_GGR _hoops_AHCR */
			result[2][2] -= _hoops_SPH->_hoops_SRIR * result[2][3];
			result[3][2] -= _hoops_SPH->_hoops_SRIR;

			if (!HI_Compute_Matrix_Inverse (&_hoops_GGACA[0][0], &matrix[0][0])) {
				goto _hoops_IRACA;
			}

			HI_Compute_Matrix_Product (&result[0][0], &matrix[0][0], &result[0][0]);

			if (_hoops_SSRCA == _hoops_RCRCA)	 break;
		} _hoops_HHHI;

		case _hoops_RCRCA: {
			/* _hoops_GSSP / _hoops_PRGIA -> _hoops_CARA */
			_hoops_ISGI		*modelling_matrix;

			if ((modelling_matrix = (_hoops_ISGI *)HI_Find_Net_Attribute_By_Path (_hoops_RIGC, _hoops_CISAA, (_hoops_CRCP const **)_hoops_SISAA, 
																						HK_MODELLING_MATRIX, _hoops_SRACA, &control)) == null)
				goto _hoops_IRACA;

			HI_Copy_43 (&modelling_matrix->matrix.elements[0][0], &matrix[0][0]);
			matrix[0][3] = matrix[1][3] = matrix[2][3] = 0.0f;
			matrix[3][3] = 1.0f;

			_hoops_HPRH (modelling_matrix);

			if (_hoops_CSRCA == _hoops_RCRCA) {
				if (!HI_Compute_Matrix_Inverse (&matrix[0][0], &result[0][0])) {
					goto _hoops_IRACA;
				}
			}
			else {
				if (!HI_Compute_Matrix_Inverse (&matrix[0][0], &matrix[0][0])) {
					goto _hoops_IRACA;
				}

				HI_Compute_Matrix_Product (&result[0][0], &matrix[0][0], &result[0][0]);
			}

			if (_hoops_SSRCA == _hoops_GCRCA) 
				break;
		} _hoops_HHHI;

		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unrecognized coordinate space value");
			goto _hoops_IRACA;
	}

	if (_hoops_CISAA > 0)
		FREE_ARRAY (_hoops_SISAA, _hoops_CISAA, _hoops_CRCP *);


	_hoops_HPRH (_hoops_SPH);
	if (_hoops_AHAIR != null)
		_hoops_HPRH (_hoops_AHAIR);

	return	true;

_hoops_IRACA:
	if (_hoops_SPH != null)
		_hoops_HPRH (_hoops_SPH);
	if (_hoops_AHAIR != null)
		_hoops_HPRH (_hoops_AHAIR);

	if (_hoops_CISAA > 0)
		FREE_ARRAY (_hoops_SISAA, _hoops_CISAA, _hoops_CRCP *);

#endif
	return false;
}



HC_INTERFACE bool HC_CDECL HC_Compute_Transform_By_Path (
	int						count,
	Key const *				keys,
	char const *			in_system,
	char const *			out_system,
	float alter *			matrix) 
{
	_hoops_PAPPR context("Compute_Transform_By_Path");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
	return false;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Transform_By_Path () */\n");
	);

	_hoops_CSPPR();
	bool result = HI_Compute_Transform_By_Path (context, count, keys, in_system, out_system, matrix);
	_hoops_IRRPR();

	return result;
#endif
}
	

HC_INTERFACE bool HC_CDECL HC_Compute_Transform (
	char const *			segment,
	char const *			in_system,
	char const *			out_system,
	float alter *			matrix) 
{
	_hoops_PAPPR context("Compute_Transform");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
	return false;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Transform () */\n");
	);

	bool result = false;

	_hoops_CSPPR();

	_hoops_CRCP * _hoops_SRCP = HI_One_Segment_Search(context, segment, true);

	if (_hoops_SRCP != null) {

		Key key = _hoops_AIRIR(_hoops_SRCP);

		PUSHNAME(context);
		result = HC_Compute_Transform_By_Path (1, &key, in_system, out_system, matrix);
		POPNAME(context);
	}
	_hoops_IRRPR();

	return result;
#endif	
}


HC_INTERFACE bool HC_CDECL HC_Compute_Coordinates (
	char const *		segment,
	char const *		in_system,
	Point const	*		_hoops_CAACA,
	char const *		out_system,
	Point *				_hoops_SAACA) 
{
	_hoops_PAPPR context("Compute_Coordinates");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
	return false;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Coordinates () */\n");
	);

	_hoops_RPRA			m[4];
	Point const	*		in = _hoops_CAACA;

	PUSHNAME(context);
	if (!HC_Compute_Transform (segment, in_system, out_system, &m[0][0])) {
		POPNAME(context);
		return	false;
	}
	POPNAME(context);

	float x =	 in->x * m[0][0]  +	 in->y * m[1][0]  +	 in->z * m[2][0]  +	 m[3][0];
	float y =	 in->x * m[0][1]  +	 in->y * m[1][1]  +	 in->z * m[2][1]  +	 m[3][1];
	float z =	 in->x * m[0][2]  +	 in->y * m[1][2]  +	 in->z * m[2][2]  +	 m[3][2];
	float w =	 in->x * m[0][3]  +	 in->y * m[1][3]  +	 in->z * m[2][3]  +	 m[3][3];

	if (w <= 0.0f)	
		return false;		/* _hoops_HPGR/_hoops_GHIPR _hoops_RHC */

	if (w != 1.0f) {
		float	_hoops_PIIPA = 1.0f / w;

		x *= _hoops_PIIPA;
		y *= _hoops_PIIPA;
		z *= _hoops_PIIPA;
	}

	_hoops_SAACA->x = x;
	_hoops_SAACA->y = y;
	_hoops_SAACA->z = z;

	return	true;
#endif
}

HC_INTERFACE bool HC_CDECL HC_Compute_Coordinates_By_Path (
	int					count,
	Key const *			keys,
	char const *		in_system,
	Point const	*		_hoops_CAACA,
	char const *		out_system,
	Point *				_hoops_SAACA) 
{
	_hoops_PAPPR context("Compute_Coordinates_By_Path");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
	return false;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Coordinates_By_Path () */\n");
	);

	_hoops_RPRA	m[4];

	PUSHNAME(context);
	if (!HC_Compute_Transform_By_Path (count, keys, in_system, out_system, &m[0][0])) {
		POPNAME(context);
		return	false;
	}
	POPNAME(context);

	Point const	*	in = _hoops_CAACA;

	float x =	 in->x * m[0][0]  +	 in->y * m[1][0]  +	 in->z * m[2][0]  +	 m[3][0];
	float y =	 in->x * m[0][1]  +	 in->y * m[1][1]  +	 in->z * m[2][1]  +	 m[3][1];
	float z =	 in->x * m[0][2]  +	 in->y * m[1][2]  +	 in->z * m[2][2]  +	 m[3][2];
	float w =	 in->x * m[0][3]  +	 in->y * m[1][3]  +	 in->z * m[2][3]  +	 m[3][3];

	if (w <= 0.0f)	
		return false;		/* _hoops_HPGR/_hoops_GHIPR _hoops_RHC */

	if (w != 1.0f) {
		float	_hoops_PIIPA = 1.0f / w;

		x *= _hoops_PIIPA;
		y *= _hoops_PIIPA;
		z *= _hoops_PIIPA;
	}

	_hoops_SAACA->x = x;
	_hoops_SAACA->y = y;
	_hoops_SAACA->z = z;

	return	true;
#endif
}




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
 * $Id: obf_tmp.txt 1.50 2010-09-22 02:29:38 trask Exp $
 */

#include "hoops.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"



GLOBAL_FUNCTION void HI_Compute_Identity_Matrix (
	float alter				*matp) {
	_hoops_RPRA alter		*m = (_hoops_RPRA alter *)matp;

	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}


HC_INTERFACE void HC_CDECL HC_Compute_Identity_Matrix (
	float alter *		matp) 
{
	_hoops_PAPPR context("Compute_Identity_Matrix");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Identity_Matrix () */\n");
	);

	HI_Compute_Identity_Matrix (matp);
}





GLOBAL_FUNCTION void HI_Compute_Scale_Matrix (
	double					x,
	double					y,
	double					z,
	float alter				*matp) {
	_hoops_RPRA alter		*m = (_hoops_RPRA alter *)matp;

	m[0][0] = (float)x; m[0][1] = 0.0f;		m[0][2] = 0.0f;		m[0][3] = 0.0f;
	m[1][0] = 0.0f;		m[1][1] = (float)y; m[1][2] = 0.0f;		m[1][3] = 0.0f;
	m[2][0] = 0.0f;		m[2][1] = 0.0f;		m[2][2] = (float)z; m[2][3] = 0.0f;
	m[3][0] = 0.0f;		m[3][1] = 0.0f;		m[3][2] = 0.0f;		m[3][3] = 1.0f;
}

HC_INTERFACE void HC_CDECL HC_Compute_Scale_Matrix (
	double				x,
	double				y,
	double				z,
	float alter *		matp) 
{
	_hoops_PAPPR context("Compute_Scale_Matrix");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Scale_Matrix () */\n");
	);

	HI_Compute_Scale_Matrix(x,y,z,matp);
}

GLOBAL_FUNCTION void HI_Compute_Translation_Matrix (
	double					x,
	double					y,
	double					z,
	float alter *			matp) 
{
	_hoops_RPRA alter		*m = (_hoops_RPRA alter *)matp;

	m[0][0] = 1.0f;		m[0][1] = 0.0f;		m[0][2] = 0.0f;		m[0][3] = 0.0f;
	m[1][0] = 0.0f;		m[1][1] = 1.0f;		m[1][2] = 0.0f;		m[1][3] = 0.0f;
	m[2][0] = 0.0f;		m[2][1] = 0.0f;		m[2][2] = 1.0f;		m[2][3] = 0.0f;
	m[3][0] = (float)x; m[3][1] = (float)y; m[3][2] = (float)z; m[3][3] = 1.0f;
}

HC_INTERFACE void HC_CDECL HC_Compute_Translation_Matrix (
	double					x,
	double					y,
	double					z,
	float alter *			matp) 
{
	_hoops_PAPPR context("Compute_Translation_Matrix");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Translation_Matrix () */\n");
	);

	HI_Compute_Translation_Matrix (x, y, z, matp);
}



GLOBAL_FUNCTION void HI_Compute_Rotation_Matrix (
	double					x,
	double					y,
	double					z,
	float alter				*matp) {
	_hoops_RPRA alter		*m = (_hoops_RPRA alter *)matp;

	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;

	if (x == 0.0f) {
		if (y == 0.0f) {
			float	_hoops_GPACA, _hoops_RPACA;

			if (z == 0.0f) {/* _hoops_RPAPR */}
			else {
				/* _hoops_APACA _hoops_SSH _hoops_ICSA */

				_hoops_RICH ((float)z, _hoops_GPACA, _hoops_RPACA);

				m[0][1] = _hoops_GPACA;
				m[1][1] = _hoops_RPACA;
				m[0][0] =  m[1][1];
				m[1][0] = -m[0][1];
			}
		}
		else if (z == 0.0f) {
			/* _hoops_APACA _hoops_HAPC _hoops_ICSA */

			float	_hoops_PPACA, _hoops_HPACA;

			_hoops_RICH ((float)y, _hoops_PPACA, _hoops_HPACA);
			m[2][0] = _hoops_PPACA;
			m[2][2] = _hoops_HPACA;
			m[0][0] =  m[2][2];
			m[0][2] = -m[2][0];
		}
		else {
			/* _hoops_CIAHR _hoops_AARRA */

			float	_hoops_PPACA, _hoops_HPACA, _hoops_GPACA, _hoops_RPACA;

			_hoops_RICH ((float)y, _hoops_PPACA, _hoops_HPACA);
			_hoops_RICH ((float)z, _hoops_GPACA, _hoops_RPACA);

			m[0][0] = _hoops_HPACA * _hoops_RPACA;
			m[0][1] = _hoops_HPACA * _hoops_GPACA;
			m[0][2] = -_hoops_PPACA;
			m[1][0] = -_hoops_GPACA;
			m[1][1] = _hoops_RPACA;
			m[1][2] = 0.0f;
			m[2][0] = _hoops_PPACA * _hoops_RPACA;
			m[2][1] = _hoops_PPACA * _hoops_GPACA;
			m[2][2] = _hoops_HPACA;
		}
	}
	else if (y == 0.0f) {
		if (z == 0.0f) {
			/* _hoops_APACA _hoops_SISR */
			float	_hoops_IPACA, _hoops_CPACA;

			_hoops_RICH ((float)x, _hoops_IPACA, _hoops_CPACA);

			m[1][2] = _hoops_IPACA;
			m[2][2] = _hoops_CPACA;

			m[1][1] =  m[2][2];
			m[2][1] = -m[1][2];
		}
		else {
			/* _hoops_SISR _hoops_SSH _hoops_SPACA */

			float	_hoops_IPACA, _hoops_CPACA, _hoops_GPACA, _hoops_RPACA;

			_hoops_RICH ((float)x, _hoops_IPACA, _hoops_CPACA);
			_hoops_RICH ((float)z, _hoops_GPACA, _hoops_RPACA);

			m[0][0] = _hoops_RPACA;
			m[0][1] = _hoops_GPACA;
			m[0][2] = 0.0f;
			m[1][0] = -_hoops_CPACA * _hoops_GPACA;
			m[1][1] = _hoops_CPACA * _hoops_RPACA;
			m[1][2] = _hoops_IPACA;
			m[2][0] = _hoops_IPACA * _hoops_GPACA;
			m[2][1] = -_hoops_IPACA * _hoops_RPACA;
			m[2][2] = _hoops_CPACA;
		}
	}
	else {
		if (z == 0.0f) {
			/* _hoops_SISR _hoops_HAPC _hoops_SPACA */

			float	_hoops_IPACA, _hoops_CPACA, _hoops_PPACA, _hoops_HPACA;

			_hoops_RICH ((float)x, _hoops_IPACA, _hoops_CPACA);
			_hoops_RICH ((float)y, _hoops_PPACA, _hoops_HPACA);

			m[0][0] = _hoops_HPACA;
			m[0][1] = 0.0f;
			m[0][2] = -_hoops_PPACA;
			m[1][0] = _hoops_IPACA * _hoops_PPACA;
			m[1][1] = _hoops_CPACA;
			m[1][2] = _hoops_IPACA * _hoops_HPACA;
			m[2][0] = _hoops_CPACA * _hoops_PPACA;
			m[2][1] = -_hoops_IPACA;
			m[2][2] = _hoops_CPACA * _hoops_HPACA;
		}
		else {
			/* _hoops_SISR _hoops_HAPC _hoops_SSH _hoops_SPACA */

			float	_hoops_IPACA, _hoops_CPACA, _hoops_PPACA, _hoops_HPACA, _hoops_GPACA, _hoops_RPACA;

			_hoops_RICH ((float)x, _hoops_IPACA, _hoops_CPACA);
			_hoops_RICH ((float)y, _hoops_PPACA, _hoops_HPACA);
			_hoops_RICH ((float)z, _hoops_GPACA, _hoops_RPACA);

			m[0][0] = _hoops_HPACA * _hoops_RPACA;
			m[0][1] = _hoops_HPACA * _hoops_GPACA;
			m[0][2] = -_hoops_PPACA;
			m[1][0] = _hoops_IPACA * _hoops_PPACA * _hoops_RPACA - _hoops_CPACA * _hoops_GPACA;
			m[1][1] = _hoops_IPACA * _hoops_PPACA * _hoops_GPACA + _hoops_CPACA * _hoops_RPACA;
			m[1][2] = _hoops_IPACA * _hoops_HPACA;
			m[2][0] = _hoops_IPACA * _hoops_GPACA + _hoops_CPACA * _hoops_PPACA * _hoops_RPACA;
			m[2][1] = _hoops_CPACA * _hoops_PPACA * _hoops_GPACA - _hoops_IPACA * _hoops_RPACA;
			m[2][2] = _hoops_CPACA * _hoops_HPACA;
		}
	}
}


HC_INTERFACE void HC_CDECL HC_Compute_Rotation_Matrix (
	double					x,
	double					y,
	double					z,
	float alter *			matp) 
{
	_hoops_PAPPR context("Compute_Rotation_Matrix");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Rotation_Matrix () */\n");
	);

	HI_Compute_Rotation_Matrix (x, y, z, matp);
}



GLOBAL_FUNCTION void HI_Compute_Offaxis_Rotation (
	double					x,
	double					y,
	double					z,
	double					_hoops_RAHCR,
	float alter				*matp) {
	_hoops_RPRA alter		*m = (_hoops_RPRA alter *)matp;
	Vector					axis;
	float					_hoops_GGHCR, _hoops_AGHCR;
	float					_hoops_PPSPA,
							_hoops_HPSPA,
							_hoops_IPSPA,
							_hoops_CPSPA;

	_hoops_RICH ((float)_hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR);

	axis.x = (float)x;
	axis.y = (float)y;
	axis.z = (float)z;

	if (!HI_Normalize (&axis)) {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_ROTATION_AXIS,
			"Specified rotation axis is all zeroes");
		/* _hoops_CISA _hoops_GGR _hoops_SRGH _hoops_HIS _hoops_PA _hoops_HSPR _hoops_SSCP _hoops_IRS _hoops_GHACA _hoops_RSGA */
		HI_Compute_Identity_Matrix(matp);
		return;
	}

	_hoops_PPSPA = 1.0f - _hoops_AGHCR;
	_hoops_HPSPA = _hoops_PPSPA * axis.x * axis.y;
	_hoops_IPSPA = _hoops_PPSPA * axis.x * axis.z;
	_hoops_CPSPA = _hoops_PPSPA * axis.y * axis.z;

	m[0][0] = _hoops_PPSPA * axis.x * axis.x + _hoops_AGHCR;
	m[0][1] = _hoops_GGHCR * axis.z + _hoops_HPSPA;
	m[0][2] = _hoops_IPSPA - _hoops_GGHCR * axis.y;
	m[0][3] = 0.0f;
	m[1][0] = _hoops_HPSPA - _hoops_GGHCR * axis.z;
	m[1][1] = _hoops_PPSPA * axis.y * axis.y + _hoops_AGHCR;
	m[1][2] = _hoops_GGHCR * axis.x + _hoops_CPSPA;
	m[1][3] = 0.0f;
	m[2][0] = _hoops_GGHCR * axis.y + _hoops_IPSPA;
	m[2][1] = _hoops_CPSPA - _hoops_GGHCR * axis.x;
	m[2][2] = _hoops_PPSPA * axis.z * axis.z + _hoops_AGHCR;
	m[2][3] = 0.0f;
	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

HC_INTERFACE void HC_CDECL HC_Compute_Offaxis_Rotation (
	double					x,
	double					y,
	double					z,
	double					_hoops_RAHCR,
	float alter *			matp) 
{
	_hoops_PAPPR context("Compute_Offaxis_Rotation");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Offaxis_Rotation () */\n");
	);

	HI_Compute_Offaxis_Rotation (x,y,z,_hoops_RAHCR,matp);
}


HC_INTERFACE void HC_CDECL HC_Compute_Offcenter_Rotation (
	double					ax,
	double					_hoops_RHACA,
	double					_hoops_AHACA,
	double					tx,
	double					ty,
	double					tz,
	float alter *			matp) 
{
	_hoops_PAPPR context("Compute_Offcenter_Rotation");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Offcenter_Rotation () */\n");
	);

	_hoops_RPRA alter		*_hoops_PAGR = (_hoops_RPRA alter *)matp;
	_hoops_RPRA			_hoops_PHACA[4];
	_hoops_RPRA			_hoops_HHACA[4];

	HI_Compute_Translation_Matrix (-tx, -ty, -tz, &_hoops_PHACA[0][0]);
	HI_Compute_Rotation_Matrix (ax, _hoops_RHACA, _hoops_AHACA, &_hoops_HHACA[0][0]);
	HI_Compute_Matrix_Product (&_hoops_PHACA[0][0], &_hoops_HHACA[0][0], &_hoops_PAGR[0][0]);

	_hoops_PAGR[3][0] += (float)tx;
	_hoops_PAGR[3][1] += (float)ty;
	_hoops_PAGR[3][2] += (float)tz;
}





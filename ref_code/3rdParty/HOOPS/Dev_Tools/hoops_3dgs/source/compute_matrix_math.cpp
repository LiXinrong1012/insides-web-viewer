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
 * $Id: obf_tmp.txt 1.79 2010-10-06 19:16:21 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hpspsf.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

#define _hoops_RAAHR 1e-32f


GLOBAL_FUNCTION void HI_Compute_Matrix_Product (
	float const *			leftp,
	float const *			rightp,
	float alter *			resultp) {
	_hoops_RPRA const *		_hoops_GSHPA = (_hoops_RPRA const *)leftp;
	_hoops_RPRA const *		_hoops_RSHPA = (_hoops_RPRA const *)rightp;
	_hoops_RPRA alter *		result = (_hoops_RPRA alter *)resultp;
	_hoops_RPRA				tmp[4];

	tmp[0][0] = _hoops_GSHPA[0][0] * _hoops_RSHPA[0][0] + _hoops_GSHPA[0][1] * _hoops_RSHPA[1][0] +
				_hoops_GSHPA[0][2] * _hoops_RSHPA[2][0] + _hoops_GSHPA[0][3] * _hoops_RSHPA[3][0];
	tmp[0][1] = _hoops_GSHPA[0][0] * _hoops_RSHPA[0][1] + _hoops_GSHPA[0][1] * _hoops_RSHPA[1][1] +
				_hoops_GSHPA[0][2] * _hoops_RSHPA[2][1] + _hoops_GSHPA[0][3] * _hoops_RSHPA[3][1];
	tmp[0][2] = _hoops_GSHPA[0][0] * _hoops_RSHPA[0][2] + _hoops_GSHPA[0][1] * _hoops_RSHPA[1][2] +
				_hoops_GSHPA[0][2] * _hoops_RSHPA[2][2] + _hoops_GSHPA[0][3] * _hoops_RSHPA[3][2];
	tmp[0][3] = _hoops_GSHPA[0][0] * _hoops_RSHPA[0][3] + _hoops_GSHPA[0][1] * _hoops_RSHPA[1][3] +
				_hoops_GSHPA[0][2] * _hoops_RSHPA[2][3] + _hoops_GSHPA[0][3] * _hoops_RSHPA[3][3];

	tmp[1][0] = _hoops_GSHPA[1][0] * _hoops_RSHPA[0][0] + _hoops_GSHPA[1][1] * _hoops_RSHPA[1][0] +
				_hoops_GSHPA[1][2] * _hoops_RSHPA[2][0] + _hoops_GSHPA[1][3] * _hoops_RSHPA[3][0];
	tmp[1][1] = _hoops_GSHPA[1][0] * _hoops_RSHPA[0][1] + _hoops_GSHPA[1][1] * _hoops_RSHPA[1][1] +
				_hoops_GSHPA[1][2] * _hoops_RSHPA[2][1] + _hoops_GSHPA[1][3] * _hoops_RSHPA[3][1];
	tmp[1][2] = _hoops_GSHPA[1][0] * _hoops_RSHPA[0][2] + _hoops_GSHPA[1][1] * _hoops_RSHPA[1][2] +
				_hoops_GSHPA[1][2] * _hoops_RSHPA[2][2] + _hoops_GSHPA[1][3] * _hoops_RSHPA[3][2];
	tmp[1][3] = _hoops_GSHPA[1][0] * _hoops_RSHPA[0][3] + _hoops_GSHPA[1][1] * _hoops_RSHPA[1][3] +
				_hoops_GSHPA[1][2] * _hoops_RSHPA[2][3] + _hoops_GSHPA[1][3] * _hoops_RSHPA[3][3];

	tmp[2][0] = _hoops_GSHPA[2][0] * _hoops_RSHPA[0][0] + _hoops_GSHPA[2][1] * _hoops_RSHPA[1][0] +
				_hoops_GSHPA[2][2] * _hoops_RSHPA[2][0] + _hoops_GSHPA[2][3] * _hoops_RSHPA[3][0];
	tmp[2][1] = _hoops_GSHPA[2][0] * _hoops_RSHPA[0][1] + _hoops_GSHPA[2][1] * _hoops_RSHPA[1][1] +
				_hoops_GSHPA[2][2] * _hoops_RSHPA[2][1] + _hoops_GSHPA[2][3] * _hoops_RSHPA[3][1];
	tmp[2][2] = _hoops_GSHPA[2][0] * _hoops_RSHPA[0][2] + _hoops_GSHPA[2][1] * _hoops_RSHPA[1][2] +
				_hoops_GSHPA[2][2] * _hoops_RSHPA[2][2] + _hoops_GSHPA[2][3] * _hoops_RSHPA[3][2];
	tmp[2][3] = _hoops_GSHPA[2][0] * _hoops_RSHPA[0][3] + _hoops_GSHPA[2][1] * _hoops_RSHPA[1][3] +
				_hoops_GSHPA[2][2] * _hoops_RSHPA[2][3] + _hoops_GSHPA[2][3] * _hoops_RSHPA[3][3];

	tmp[3][0] = _hoops_GSHPA[3][0] * _hoops_RSHPA[0][0] + _hoops_GSHPA[3][1] * _hoops_RSHPA[1][0] +
				_hoops_GSHPA[3][2] * _hoops_RSHPA[2][0] + _hoops_GSHPA[3][3] * _hoops_RSHPA[3][0];
	tmp[3][1] = _hoops_GSHPA[3][0] * _hoops_RSHPA[0][1] + _hoops_GSHPA[3][1] * _hoops_RSHPA[1][1] +
				_hoops_GSHPA[3][2] * _hoops_RSHPA[2][1] + _hoops_GSHPA[3][3] * _hoops_RSHPA[3][1];
	tmp[3][2] = _hoops_GSHPA[3][0] * _hoops_RSHPA[0][2] + _hoops_GSHPA[3][1] * _hoops_RSHPA[1][2] +
				_hoops_GSHPA[3][2] * _hoops_RSHPA[2][2] + _hoops_GSHPA[3][3] * _hoops_RSHPA[3][2];
	tmp[3][3] = _hoops_GSHPA[3][0] * _hoops_RSHPA[0][3] + _hoops_GSHPA[3][1] * _hoops_RSHPA[1][3] +
				_hoops_GSHPA[3][2] * _hoops_RSHPA[2][3] + _hoops_GSHPA[3][3] * _hoops_RSHPA[3][3];

	HI_Copy_44 (&tmp[0][0], &result[0][0]);
}


HC_INTERFACE void HC_CDECL HC_Compute_Matrix_Product (
	float const *			leftp,
	float const *			rightp,
	float alter *			resultp) 
{
	_hoops_PAPPR context("Compute_Matrix_Product");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Matrix_Product () */\n");
	);

	HI_Compute_Matrix_Product (leftp, rightp, resultp);
#endif
}



/*
_hoops_ASHPA:
							[ _hoops_PSHPA  _hoops_HSHPA	_hoops_ISHPA	 _hoops_CSHPA ]
							[ _hoops_SSHPA  _hoops_GGIPA	_hoops_RGIPA	 _hoops_AGIPA ]
							[ _hoops_PGIPA  _hoops_HGIPA	_hoops_IGIPA	 _hoops_CGIPA ]
							[ _hoops_SGIPA  _hoops_GRIPA	_hoops_RRIPA	 _hoops_ARIPA ]

_hoops_PRIPA:
	[  _hoops_GGIPA (_hoops_IGIPA _hoops_ARIPA - _hoops_CGIPA _hoops_RRIPA) - _hoops_RGIPA (_hoops_HGIPA _hoops_ARIPA - _hoops_CGIPA _hoops_GRIPA) + _hoops_AGIPA (_hoops_HGIPA _hoops_RRIPA - _hoops_IGIPA _hoops_GRIPA),
		- _hoops_HSHPA (_hoops_IGIPA _hoops_ARIPA - _hoops_CGIPA _hoops_RRIPA) + _hoops_ISHPA (_hoops_HGIPA _hoops_ARIPA - _hoops_CGIPA _hoops_GRIPA) - _hoops_CSHPA (_hoops_HGIPA _hoops_RRIPA - _hoops_IGIPA _hoops_GRIPA),
			 _hoops_HSHPA (_hoops_RGIPA _hoops_ARIPA - _hoops_AGIPA _hoops_RRIPA) - _hoops_ISHPA (_hoops_GGIPA _hoops_ARIPA - _hoops_AGIPA _hoops_GRIPA) + _hoops_CSHPA (_hoops_GGIPA _hoops_RRIPA - _hoops_RGIPA _hoops_GRIPA),
			  - _hoops_HSHPA (_hoops_RGIPA _hoops_CGIPA - _hoops_AGIPA _hoops_IGIPA) + _hoops_ISHPA (_hoops_GGIPA _hoops_CGIPA - _hoops_AGIPA _hoops_HGIPA) - _hoops_CSHPA (_hoops_GGIPA _hoops_IGIPA - _hoops_RGIPA _hoops_HGIPA)]
	[- _hoops_SSHPA (_hoops_IGIPA _hoops_ARIPA - _hoops_CGIPA _hoops_RRIPA) + _hoops_RGIPA (_hoops_PGIPA _hoops_ARIPA - _hoops_CGIPA _hoops_SGIPA) - _hoops_AGIPA (_hoops_PGIPA _hoops_RRIPA - _hoops_IGIPA _hoops_SGIPA),
		  _hoops_PSHPA (_hoops_IGIPA _hoops_ARIPA - _hoops_CGIPA _hoops_RRIPA) - _hoops_ISHPA (_hoops_PGIPA _hoops_ARIPA - _hoops_CGIPA _hoops_SGIPA) + _hoops_CSHPA (_hoops_PGIPA _hoops_RRIPA - _hoops_IGIPA _hoops_SGIPA),
		   - _hoops_PSHPA (_hoops_RGIPA _hoops_ARIPA - _hoops_AGIPA _hoops_RRIPA) + _hoops_ISHPA (_hoops_SSHPA _hoops_ARIPA - _hoops_AGIPA _hoops_SGIPA) - _hoops_CSHPA (_hoops_SSHPA _hoops_RRIPA - _hoops_RGIPA _hoops_SGIPA),
				_hoops_PSHPA (_hoops_RGIPA _hoops_CGIPA - _hoops_AGIPA _hoops_IGIPA) - _hoops_ISHPA (_hoops_SSHPA _hoops_CGIPA - _hoops_AGIPA _hoops_PGIPA) + _hoops_CSHPA (_hoops_SSHPA _hoops_IGIPA - _hoops_RGIPA _hoops_PGIPA)]
	[  _hoops_SSHPA (_hoops_HGIPA _hoops_ARIPA - _hoops_CGIPA _hoops_GRIPA) - _hoops_GGIPA (_hoops_PGIPA _hoops_ARIPA - _hoops_CGIPA _hoops_SGIPA) + _hoops_AGIPA (_hoops_PGIPA _hoops_GRIPA - _hoops_HGIPA _hoops_SGIPA),
		- _hoops_PSHPA (_hoops_HGIPA _hoops_ARIPA - _hoops_CGIPA _hoops_GRIPA) + _hoops_HSHPA (_hoops_PGIPA _hoops_ARIPA - _hoops_CGIPA _hoops_SGIPA) - _hoops_CSHPA (_hoops_PGIPA _hoops_GRIPA - _hoops_HGIPA _hoops_SGIPA),
			 _hoops_PSHPA (_hoops_GGIPA _hoops_ARIPA - _hoops_AGIPA _hoops_GRIPA) - _hoops_HSHPA (_hoops_SSHPA _hoops_ARIPA - _hoops_AGIPA _hoops_SGIPA) + _hoops_CSHPA (_hoops_SSHPA _hoops_GRIPA - _hoops_GGIPA _hoops_SGIPA),
			  - _hoops_PSHPA (_hoops_GGIPA _hoops_CGIPA - _hoops_AGIPA _hoops_HGIPA) + _hoops_HSHPA (_hoops_SSHPA _hoops_CGIPA - _hoops_AGIPA _hoops_PGIPA) - _hoops_CSHPA (_hoops_SSHPA _hoops_HGIPA - _hoops_GGIPA _hoops_PGIPA)]
	[- _hoops_SSHPA (_hoops_HGIPA _hoops_RRIPA - _hoops_IGIPA _hoops_GRIPA) + _hoops_GGIPA (_hoops_PGIPA _hoops_RRIPA - _hoops_IGIPA _hoops_SGIPA) - _hoops_RGIPA (_hoops_PGIPA _hoops_GRIPA - _hoops_HGIPA _hoops_SGIPA),
		  _hoops_PSHPA (_hoops_HGIPA _hoops_RRIPA - _hoops_IGIPA _hoops_GRIPA) - _hoops_HSHPA (_hoops_PGIPA _hoops_RRIPA - _hoops_IGIPA _hoops_SGIPA) + _hoops_ISHPA (_hoops_PGIPA _hoops_GRIPA - _hoops_HGIPA _hoops_SGIPA),
		   - _hoops_PSHPA (_hoops_GGIPA _hoops_RRIPA - _hoops_RGIPA _hoops_GRIPA) + _hoops_HSHPA (_hoops_SSHPA _hoops_RRIPA - _hoops_RGIPA _hoops_SGIPA) - _hoops_ISHPA (_hoops_SSHPA _hoops_GRIPA - _hoops_GGIPA _hoops_SGIPA),
				_hoops_PSHPA (_hoops_GGIPA _hoops_IGIPA - _hoops_RGIPA _hoops_HGIPA) - _hoops_HSHPA (_hoops_SSHPA _hoops_IGIPA - _hoops_RGIPA _hoops_PGIPA) + _hoops_ISHPA (_hoops_SSHPA _hoops_HGIPA - _hoops_GGIPA _hoops_PGIPA)]

_hoops_HRIPA:
		 _hoops_PSHPA (_hoops_GGIPA (_hoops_IGIPA _hoops_ARIPA - _hoops_CGIPA _hoops_RRIPA) - _hoops_RGIPA (_hoops_HGIPA _hoops_ARIPA - _hoops_CGIPA _hoops_GRIPA) + _hoops_AGIPA (_hoops_HGIPA _hoops_RRIPA - _hoops_IGIPA _hoops_GRIPA))
	   - _hoops_HSHPA (_hoops_SSHPA (_hoops_IGIPA _hoops_ARIPA - _hoops_CGIPA _hoops_RRIPA) - _hoops_RGIPA (_hoops_PGIPA _hoops_ARIPA - _hoops_CGIPA _hoops_SGIPA) + _hoops_AGIPA (_hoops_PGIPA _hoops_RRIPA - _hoops_IGIPA _hoops_SGIPA))
	   + _hoops_ISHPA (_hoops_SSHPA (_hoops_HGIPA _hoops_ARIPA - _hoops_CGIPA _hoops_GRIPA) - _hoops_GGIPA (_hoops_PGIPA _hoops_ARIPA - _hoops_CGIPA _hoops_SGIPA) + _hoops_AGIPA (_hoops_PGIPA _hoops_GRIPA - _hoops_HGIPA _hoops_SGIPA))
	   - _hoops_CSHPA (_hoops_SSHPA (_hoops_HGIPA _hoops_RRIPA - _hoops_IGIPA _hoops_GRIPA) - _hoops_GGIPA (_hoops_PGIPA _hoops_RRIPA - _hoops_IGIPA _hoops_SGIPA) + _hoops_RGIPA (_hoops_PGIPA _hoops_GRIPA - _hoops_HGIPA _hoops_SGIPA))
*/


GLOBAL_FUNCTION void HI_Compute_Matrix_Adjoint (
	float const *			matp,
	float alter *			_hoops_IRIPA) {
	_hoops_RPRA const *		a = (_hoops_RPRA const *)matp;
	_hoops_RPRA alter *		_hoops_CRIPA = (_hoops_RPRA alter *)_hoops_IRIPA;
	_hoops_RPRA				tmp[4];

	/* (_hoops_SRIPA _hoops_IIGR _hoops_GAIPA _hoops_PPR _hoops_IRS _hoops_RSCA _hoops_RAIPA..). */

	float	_hoops_AAIPA = a[1][0]*a[2][1] - a[1][1]*a[2][0],
			_hoops_PAIPA = a[1][0]*a[2][2] - a[1][2]*a[2][0],
			_hoops_HAIPA = a[1][0]*a[2][3] - a[1][3]*a[2][0],
			_hoops_IAIPA = a[1][0]*a[3][1] - a[1][1]*a[3][0],
			_hoops_CAIPA = a[1][0]*a[3][2] - a[1][2]*a[3][0],
			_hoops_SAIPA = a[1][0]*a[3][3] - a[1][3]*a[3][0],
			_hoops_GPIPA = a[1][1]*a[2][2] - a[1][2]*a[2][1],
			_hoops_RPIPA = a[1][1]*a[2][3] - a[1][3]*a[2][1],
			_hoops_APIPA = a[1][1]*a[3][2] - a[1][2]*a[3][1],
			_hoops_PPIPA = a[1][1]*a[3][3] - a[1][3]*a[3][1],
			_hoops_HPIPA = a[1][2]*a[2][3] - a[1][3]*a[2][2],
			_hoops_IPIPA = a[1][2]*a[3][3] - a[1][3]*a[3][2],
			_hoops_CPIPA = a[2][0]*a[3][1] - a[2][1]*a[3][0],
			_hoops_SPIPA = a[2][0]*a[3][2] - a[2][2]*a[3][0],
			_hoops_GHIPA = a[2][0]*a[3][3] - a[2][3]*a[3][0],
			_hoops_RHIPA = a[2][1]*a[3][2] - a[2][2]*a[3][1],
			_hoops_AHIPA = a[2][1]*a[3][3] - a[2][3]*a[3][1],
			_hoops_PHIPA = a[2][2]*a[3][3] - a[2][3]*a[3][2];


	tmp[0][0] = a[1][1]*_hoops_PHIPA - a[1][2]*_hoops_AHIPA + a[1][3]*_hoops_RHIPA;
	tmp[0][1] = a[0][2]*_hoops_AHIPA - a[0][3]*_hoops_RHIPA - a[0][1]*_hoops_PHIPA;
	tmp[0][2] = a[0][1]*_hoops_IPIPA - a[0][2]*_hoops_PPIPA + a[0][3]*_hoops_APIPA;
	tmp[0][3] = a[0][2]*_hoops_RPIPA - a[0][3]*_hoops_GPIPA - a[0][1]*_hoops_HPIPA;
	tmp[1][0] = a[1][2]*_hoops_GHIPA - a[1][3]*_hoops_SPIPA - a[1][0]*_hoops_PHIPA;
	tmp[1][1] = a[0][0]*_hoops_PHIPA - a[0][2]*_hoops_GHIPA + a[0][3]*_hoops_SPIPA;
	tmp[1][2] = a[0][2]*_hoops_SAIPA - a[0][3]*_hoops_CAIPA - a[0][0]*_hoops_IPIPA;
	tmp[1][3] = a[0][0]*_hoops_HPIPA - a[0][2]*_hoops_HAIPA + a[0][3]*_hoops_PAIPA;
	tmp[2][0] = a[1][0]*_hoops_AHIPA - a[1][1]*_hoops_GHIPA + a[1][3]*_hoops_CPIPA;
	tmp[2][1] = a[0][1]*_hoops_GHIPA - a[0][3]*_hoops_CPIPA - a[0][0]*_hoops_AHIPA;
	tmp[2][2] = a[0][0]*_hoops_PPIPA - a[0][1]*_hoops_SAIPA + a[0][3]*_hoops_IAIPA;
	tmp[2][3] = a[0][1]*_hoops_HAIPA - a[0][3]*_hoops_AAIPA - a[0][0]*_hoops_RPIPA;
	tmp[3][0] = a[1][1]*_hoops_SPIPA - a[1][2]*_hoops_CPIPA - a[1][0]*_hoops_RHIPA;
	tmp[3][1] = a[0][0]*_hoops_RHIPA - a[0][1]*_hoops_SPIPA + a[0][2]*_hoops_CPIPA;
	tmp[3][2] = a[0][1]*_hoops_CAIPA - a[0][2]*_hoops_IAIPA - a[0][0]*_hoops_APIPA;
	tmp[3][3] = a[0][0]*_hoops_GPIPA - a[0][1]*_hoops_PAIPA + a[0][2]*_hoops_AAIPA;

	_hoops_CRIPA[0][0] = tmp[0][0];
	_hoops_CRIPA[0][1] = tmp[0][1];
	_hoops_CRIPA[0][2] = tmp[0][2];
	_hoops_CRIPA[0][3] = tmp[0][3];
	_hoops_CRIPA[1][0] = tmp[1][0];
	_hoops_CRIPA[1][1] = tmp[1][1];
	_hoops_CRIPA[1][2] = tmp[1][2];
	_hoops_CRIPA[1][3] = tmp[1][3];
	_hoops_CRIPA[2][0] = tmp[2][0];
	_hoops_CRIPA[2][1] = tmp[2][1];
	_hoops_CRIPA[2][2] = tmp[2][2];
	_hoops_CRIPA[2][3] = tmp[2][3];
	_hoops_CRIPA[3][0] = tmp[3][0];
	_hoops_CRIPA[3][1] = tmp[3][1];
	_hoops_CRIPA[3][2] = tmp[3][2];
	_hoops_CRIPA[3][3] = tmp[3][3];
}


HC_INTERFACE void HC_CDECL HC_Compute_Matrix_Adjoint (
	float const *			matp,
	float alter *			_hoops_IRIPA) 
{
	_hoops_PAPPR context("Compute_Matrix_Adjoint");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Matrix_Adjoint () */\n");
	);

	HI_Compute_Matrix_Adjoint (matp,_hoops_IRIPA);
#endif
}


GLOBAL_FUNCTION double HI_Compute_Matrix_Determinant (
	float const	 *			matp) {
	_hoops_RPRA const *		a = (_hoops_RPRA const *)matp;

	float			_hoops_CPIPA = a[2][0]*a[3][1] - a[2][1]*a[3][0],
					_hoops_SPIPA = a[2][0]*a[3][2] - a[2][2]*a[3][0],
					_hoops_GHIPA = a[2][0]*a[3][3] - a[2][3]*a[3][0],
					_hoops_RHIPA = a[2][1]*a[3][2] - a[2][2]*a[3][1],
					_hoops_AHIPA = a[2][1]*a[3][3] - a[2][3]*a[3][1],
					_hoops_PHIPA = a[2][2]*a[3][3] - a[2][3]*a[3][2];
	float			_hoops_GGIAR = a[1][1]*_hoops_PHIPA -
						 a[1][2]*_hoops_AHIPA +
						 a[1][3]*_hoops_RHIPA,
					p1 = a[1][0]*_hoops_PHIPA -
						 a[1][2]*_hoops_GHIPA +
						 a[1][3]*_hoops_SPIPA,
					p2 = a[1][0]*_hoops_AHIPA -
						 a[1][1]*_hoops_GHIPA +
						 a[1][3]*_hoops_CPIPA,
					_hoops_IAPH = a[1][0]*_hoops_RHIPA -
						 a[1][1]*_hoops_SPIPA +
						 a[1][2]*_hoops_CPIPA;

	return	a[0][0]*_hoops_GGIAR - a[0][1]*p1 + a[0][2]*p2 - a[0][3]*_hoops_IAPH;
}

HC_INTERFACE double HC_CDECL HC_Compute_Matrix_Determinant (
	float const *		matp) 
{
	_hoops_PAPPR context("Compute_Matrix_Determinant");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
	return 0.0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Matrix_Determinant () */\n");
	);

	return HI_Compute_Matrix_Determinant(matp);

#endif
}


GLOBAL_FUNCTION bool HI_Compute_Matrix_Inverse (
	float const *			matp,
	float alter *			invp) {
	_hoops_RPRA const *		a = (_hoops_RPRA const *)matp;
	_hoops_RPRA alter *		_hoops_CRPA = (_hoops_RPRA alter *)invp;
	_hoops_RPRA				tmp[4];

	// _hoops_SRIPA _hoops_IIGR _hoops_GAIPA _hoops_PPR _hoops_IRS _hoops_RSCA _hoops_RAIPA...
	float			_hoops_AAIPA = a[1][0]*a[2][1] - a[1][1]*a[2][0],
					_hoops_PAIPA = a[1][0]*a[2][2] - a[1][2]*a[2][0],
					_hoops_HAIPA = a[1][0]*a[2][3] - a[1][3]*a[2][0],
					_hoops_IAIPA = a[1][0]*a[3][1] - a[1][1]*a[3][0],
					_hoops_CAIPA = a[1][0]*a[3][2] - a[1][2]*a[3][0],
					_hoops_SAIPA = a[1][0]*a[3][3] - a[1][3]*a[3][0],
					_hoops_GPIPA = a[1][1]*a[2][2] - a[1][2]*a[2][1],
					_hoops_RPIPA = a[1][1]*a[2][3] - a[1][3]*a[2][1],
					_hoops_APIPA = a[1][1]*a[3][2] - a[1][2]*a[3][1],
					_hoops_PPIPA = a[1][1]*a[3][3] - a[1][3]*a[3][1],
					_hoops_HPIPA = a[1][2]*a[2][3] - a[1][3]*a[2][2],
					_hoops_IPIPA = a[1][2]*a[3][3] - a[1][3]*a[3][2],
					_hoops_CPIPA = a[2][0]*a[3][1] - a[2][1]*a[3][0],
					_hoops_SPIPA = a[2][0]*a[3][2] - a[2][2]*a[3][0],
					_hoops_GHIPA = a[2][0]*a[3][3] - a[2][3]*a[3][0],
					_hoops_RHIPA = a[2][1]*a[3][2] - a[2][2]*a[3][1],
					_hoops_AHIPA = a[2][1]*a[3][3] - a[2][3]*a[3][1],
					_hoops_PHIPA = a[2][2]*a[3][3] - a[2][3]*a[3][2];
	float			_hoops_GGIAR, p1, p2, _hoops_IAPH;
	float			_hoops_HHIPA, _hoops_IHIPA;

	tmp[0][0] = a[1][1]*_hoops_PHIPA - a[1][2]*_hoops_AHIPA + a[1][3]*_hoops_RHIPA;
	tmp[0][1] = a[0][2]*_hoops_AHIPA - a[0][3]*_hoops_RHIPA - a[0][1]*_hoops_PHIPA;
	tmp[0][2] = a[0][1]*_hoops_IPIPA - a[0][2]*_hoops_PPIPA + a[0][3]*_hoops_APIPA;
	tmp[0][3] = a[0][2]*_hoops_RPIPA - a[0][3]*_hoops_GPIPA - a[0][1]*_hoops_HPIPA;
	tmp[1][0] = a[1][2]*_hoops_GHIPA - a[1][3]*_hoops_SPIPA - a[1][0]*_hoops_PHIPA;
	tmp[1][1] = a[0][0]*_hoops_PHIPA - a[0][2]*_hoops_GHIPA + a[0][3]*_hoops_SPIPA;
	tmp[1][2] = a[0][2]*_hoops_SAIPA - a[0][3]*_hoops_CAIPA - a[0][0]*_hoops_IPIPA;
	tmp[1][3] = a[0][0]*_hoops_HPIPA - a[0][2]*_hoops_HAIPA + a[0][3]*_hoops_PAIPA;
	tmp[2][0] = a[1][0]*_hoops_AHIPA - a[1][1]*_hoops_GHIPA + a[1][3]*_hoops_CPIPA;
	tmp[2][1] = a[0][1]*_hoops_GHIPA - a[0][3]*_hoops_CPIPA - a[0][0]*_hoops_AHIPA;
	tmp[2][2] = a[0][0]*_hoops_PPIPA - a[0][1]*_hoops_SAIPA + a[0][3]*_hoops_IAIPA;
	tmp[2][3] = a[0][1]*_hoops_HAIPA - a[0][3]*_hoops_AAIPA - a[0][0]*_hoops_RPIPA;
	tmp[3][0] = a[1][1]*_hoops_SPIPA - a[1][2]*_hoops_CPIPA - a[1][0]*_hoops_RHIPA;
	tmp[3][1] = a[0][0]*_hoops_RHIPA - a[0][1]*_hoops_SPIPA + a[0][2]*_hoops_CPIPA;
	tmp[3][2] = a[0][1]*_hoops_CAIPA - a[0][2]*_hoops_IAIPA - a[0][0]*_hoops_APIPA;
	tmp[3][3] = a[0][0]*_hoops_GPIPA - a[0][1]*_hoops_PAIPA + a[0][2]*_hoops_AAIPA;

	_hoops_GGIAR =  tmp[0][0];
	p1 = -tmp[1][0];
	p2 =  tmp[2][0];
	_hoops_IAPH = -tmp[3][0];

	_hoops_HHIPA = a[0][0]*_hoops_GGIAR - a[0][1]*p1 + a[0][2]*p2 - a[0][3]*_hoops_IAPH;
	if (_hoops_HHIPA <= _hoops_RAAHR && _hoops_HHIPA >= -_hoops_RAAHR)
		return false;

	_hoops_IHIPA = 1.0f / _hoops_HHIPA;

	_hoops_CRPA[0][0] = tmp[0][0] * _hoops_IHIPA;
	_hoops_CRPA[0][1] = tmp[0][1] * _hoops_IHIPA;
	_hoops_CRPA[0][2] = tmp[0][2] * _hoops_IHIPA;
	_hoops_CRPA[0][3] = tmp[0][3] * _hoops_IHIPA;
	_hoops_CRPA[1][0] = tmp[1][0] * _hoops_IHIPA;
	_hoops_CRPA[1][1] = tmp[1][1] * _hoops_IHIPA;
	_hoops_CRPA[1][2] = tmp[1][2] * _hoops_IHIPA;
	_hoops_CRPA[1][3] = tmp[1][3] * _hoops_IHIPA;
	_hoops_CRPA[2][0] = tmp[2][0] * _hoops_IHIPA;
	_hoops_CRPA[2][1] = tmp[2][1] * _hoops_IHIPA;
	_hoops_CRPA[2][2] = tmp[2][2] * _hoops_IHIPA;
	_hoops_CRPA[2][3] = tmp[2][3] * _hoops_IHIPA;
	_hoops_CRPA[3][0] = tmp[3][0] * _hoops_IHIPA;
	_hoops_CRPA[3][1] = tmp[3][1] * _hoops_IHIPA;
	_hoops_CRPA[3][2] = tmp[3][2] * _hoops_IHIPA;
	_hoops_CRPA[3][3] = tmp[3][3] * _hoops_IHIPA;

	return	true;
}


HC_INTERFACE bool HC_CDECL HC_Compute_Matrix_Inverse (
	float const *			matp,
	float alter *			invp) 
{
	_hoops_PAPPR context("Compute_Matrix_Inverse");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Matrix_Inverse () */\n");
	);

	return HI_Compute_Matrix_Inverse (matp, invp);
}


GLOBAL_FUNCTION bool HC_CDECL HI_Compute_Normalized_Matrix (
	float const *			matp,
	float alter *			_hoops_CHIPA) 
{

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
	return false;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Normalized_Matrix () */\n");
	);

	_hoops_RPRA const *		a = (_hoops_RPRA const *)matp;
	_hoops_RPRA alter *		_hoops_IRPA = (_hoops_RPRA alter *)_hoops_CHIPA;
	float					_hoops_IHIPA;

	float	_hoops_HHIPA = (float)HI_Compute_Matrix_Determinant (&a[0][0]);

	if (_hoops_HHIPA == 0.0f)
		return  false;

	_hoops_IHIPA = 1.0f / _hoops_HHIPA;

	_hoops_IRPA[0][0] = a[0][0] * _hoops_IHIPA;
	_hoops_IRPA[0][1] = a[0][1] * _hoops_IHIPA;
	_hoops_IRPA[0][2] = a[0][2] * _hoops_IHIPA;
	_hoops_IRPA[0][3] = a[0][3] * _hoops_IHIPA;
	_hoops_IRPA[1][0] = a[1][0] * _hoops_IHIPA;
	_hoops_IRPA[1][1] = a[1][1] * _hoops_IHIPA;
	_hoops_IRPA[1][2] = a[1][2] * _hoops_IHIPA;
	_hoops_IRPA[1][3] = a[1][3] * _hoops_IHIPA;
	_hoops_IRPA[2][0] = a[2][0] * _hoops_IHIPA;
	_hoops_IRPA[2][1] = a[2][1] * _hoops_IHIPA;
	_hoops_IRPA[2][2] = a[2][2] * _hoops_IHIPA;
	_hoops_IRPA[2][3] = a[2][3] * _hoops_IHIPA;
	_hoops_IRPA[3][0] = a[3][0] * _hoops_IHIPA;
	_hoops_IRPA[3][1] = a[3][1] * _hoops_IHIPA;
	_hoops_IRPA[3][2] = a[3][2] * _hoops_IHIPA;
	_hoops_IRPA[3][3] = a[3][3] * _hoops_IHIPA;

	return	true;
#endif
}

HC_INTERFACE bool HC_CDECL HC_Compute_Normalized_Matrix (
	float const *			matp,
	float alter *			_hoops_CHIPA) 
{
	_hoops_PAPPR context("Compute_Normalized_Matrix");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Normalized_Matrix () */\n");
	);

	return HI_Compute_Normalized_Matrix (matp, _hoops_CHIPA);
}


HC_INTERFACE bool HC_CDECL HC_Compute_Transformed_Plane (
	_hoops_ARPA const *			in,
	float const *			matp,
	_hoops_ARPA *					_hoops_PAGR) 
{
	_hoops_PAPPR context("Compute_Transformed_Plane");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
	return false;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Transformed_Plane () */\n");
	);

	_hoops_RPRA const *		m = (_hoops_RPRA const *)matp;
	_hoops_ARPA					_hoops_IRPA;
	_hoops_RPRA				_hoops_CRPA[4];

	HI_Compute_Matrix_Adjoint (&m[0][0], &_hoops_CRPA[0][0]);

	_hoops_IRPA.a = in->a*_hoops_CRPA[0][0] + in->b*_hoops_CRPA[0][1] + in->c*_hoops_CRPA[0][2] + in->d*_hoops_CRPA[0][3];
	_hoops_IRPA.b = in->a*_hoops_CRPA[1][0] + in->b*_hoops_CRPA[1][1] + in->c*_hoops_CRPA[1][2] + in->d*_hoops_CRPA[1][3];
	_hoops_IRPA.c = in->a*_hoops_CRPA[2][0] + in->b*_hoops_CRPA[2][1] + in->c*_hoops_CRPA[2][2] + in->d*_hoops_CRPA[2][3];
	_hoops_IRPA.d = in->a*_hoops_CRPA[3][0] + in->b*_hoops_CRPA[3][1] + in->c*_hoops_CRPA[3][2] + in->d*_hoops_CRPA[3][3];

	HI_Normalize_Plane (&_hoops_IRPA);

	_hoops_PAGR->a = _hoops_IRPA.a;
	_hoops_PAGR->b = _hoops_IRPA.b;
	_hoops_PAGR->c = _hoops_IRPA.c;
	_hoops_PAGR->d = _hoops_IRPA.d;

	return	true;
#endif
}

GLOBAL_FUNCTION void HI_Compute_Transformed_Planes (
	int						count,
	_hoops_ARPA const *			in,
	_hoops_HRPA const *		mat,
	_hoops_ARPA *					_hoops_PAGR) {
	_hoops_RPRA const *		_hoops_CRIPA;
	_hoops_ARPA					temp;

	if (mat->_hoops_APRA == null)
		HI_Validate_Matrix_Adjoint (mat);
	_hoops_CRIPA = (_hoops_RPRA const *)mat->_hoops_APRA->data.elements;

	while (--count >= 0) {
		temp.a = in->a*_hoops_CRIPA[0][0] + in->b*_hoops_CRIPA[0][1] + in->c*_hoops_CRIPA[0][2] + in->d*_hoops_CRIPA[0][3];
		temp.b = in->a*_hoops_CRIPA[1][0] + in->b*_hoops_CRIPA[1][1] + in->c*_hoops_CRIPA[1][2] + in->d*_hoops_CRIPA[1][3];
		temp.c = in->a*_hoops_CRIPA[2][0] + in->b*_hoops_CRIPA[2][1] + in->c*_hoops_CRIPA[2][2] + in->d*_hoops_CRIPA[2][3];
		temp.d = in->a*_hoops_CRIPA[3][0] + in->b*_hoops_CRIPA[3][1] + in->c*_hoops_CRIPA[3][2] + in->d*_hoops_CRIPA[3][3];

		HI_Normalize_Plane(&temp);

		_hoops_PAGR->a = temp.a;
		_hoops_PAGR->b = temp.b;
		_hoops_PAGR->c = temp.c;
		_hoops_PAGR->d = temp.d;

		in++;
		_hoops_PAGR++;
	}
}


GLOBAL_FUNCTION bool HI_Compute_Transformed_Planes2 (
	int						count,
	_hoops_ARPA const *			in,
	float const *			matp,
	_hoops_ARPA *					_hoops_PAGR) {
	_hoops_RPRA const *		m = (_hoops_RPRA const *)matp;
	_hoops_ARPA					_hoops_IRPA;
	_hoops_RPRA				_hoops_CRPA[4];
	bool					_hoops_SHIPA = false;

	HI_Compute_Matrix_Adjoint (&m[0][0], &_hoops_CRPA[0][0]);

	while (--count >= 0) {
		_hoops_IRPA.a = in->a*_hoops_CRPA[0][0] + in->b*_hoops_CRPA[0][1] + in->c*_hoops_CRPA[0][2] + in->d*_hoops_CRPA[0][3];
		_hoops_IRPA.b = in->a*_hoops_CRPA[1][0] + in->b*_hoops_CRPA[1][1] + in->c*_hoops_CRPA[1][2] + in->d*_hoops_CRPA[1][3];
		_hoops_IRPA.c = in->a*_hoops_CRPA[2][0] + in->b*_hoops_CRPA[2][1] + in->c*_hoops_CRPA[2][2] + in->d*_hoops_CRPA[2][3];
		_hoops_IRPA.d = in->a*_hoops_CRPA[3][0] + in->b*_hoops_CRPA[3][1] + in->c*_hoops_CRPA[3][2] + in->d*_hoops_CRPA[3][3];

		HI_Normalize_Plane(&_hoops_IRPA);

		_hoops_PAGR->a = _hoops_IRPA.a;
		_hoops_PAGR->b = _hoops_IRPA.b;
		_hoops_PAGR->c = _hoops_IRPA.c;
		_hoops_PAGR->d = _hoops_IRPA.d;

		in++;
		_hoops_PAGR++;
	}

	return !_hoops_SHIPA;
}

HC_INTERFACE bool HC_CDECL HC_Compute_Transformed_Planes (
	int						count,
	_hoops_ARPA const *			in,
	float const *			matp,
	_hoops_ARPA *					_hoops_PAGR) 
{
	_hoops_PAPPR context("Compute_Transformed_Planes");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
	return false;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Transformed_Planes () */\n");
	);

	return HI_Compute_Transformed_Planes2 (count, in, matp, _hoops_PAGR);
#endif
}


/* _hoops_GASA: _hoops_CRICR _hoops_IS _hoops_GIIPA, _hoops_HIH _hoops_SCH _hoops_RIIPA _hoops_AIIPA
 * _hoops_RGAR _hoops_IS _hoops_RH _hoops_AAPA 3x3 _hoops_ICSA _hoops_IHSR */
GLOBAL_FUNCTION void HI_Compute_Transformed_Vectors (
	int						count,
	Vector const *			_hoops_CIIRR,
	float const *			matp,
	Vector *				result) {
	_hoops_RPRA const *		m = (_hoops_RPRA const *)matp;
	float					x, y, z;
	Vector const *			in = _hoops_CIIRR;
	Vector *				_hoops_PAGR = result;

	while (--count >= 0) {
		x = in->x*m[0][0]; x += in->y*m[1][0]; x += in->z*m[2][0];
		y = in->x*m[0][1]; y += in->y*m[1][1]; y += in->z*m[2][1];
		z = in->x*m[0][2]; z += in->y*m[1][2]; z += in->z*m[2][2];
		_hoops_PAGR->x = x;
		_hoops_PAGR->y = y;
		_hoops_PAGR->z = z;

		in++;
		_hoops_PAGR++;
	}
}


GLOBAL_FUNCTION void HI_Compute_Transformed_Points (
	int					count,
	Point const *		points,
	float const *		matp,
	Point *				result) {
#if 0
	_hoops_RPRA const *	m = (_hoops_RPRA const *)matp;
	float				x, y, z, w, _hoops_PIIPA;
	Point const *		in = points;
	Point *				_hoops_PAGR = result;

	while (--count >= 0) {
		x = in->x*m[0][0] + in->y*m[1][0] + in->z*m[2][0] + m[3][0];
		y = in->x*m[0][1] + in->y*m[1][1] + in->z*m[2][1] + m[3][1];
		z = in->x*m[0][2] + in->y*m[1][2] + in->z*m[2][2] + m[3][2];
		w = in->x*m[0][3] + in->y*m[1][3] + in->z*m[2][3] + m[3][3];

		if (w != 1.0f) {
			if (w != 0.0f) {
				_hoops_PIIPA = 1.0f / w;
				x *= _hoops_PIIPA;
				y *= _hoops_PIIPA;
				z *= _hoops_PIIPA;
			}
			else {
				/* _hoops_HIIPA ? */
			}
		}

		_hoops_PAGR->x = x;
		_hoops_PAGR->y = y;
		_hoops_PAGR->z = z;

		in++;
		_hoops_PAGR++;
	}
#else
	if (matp[3] == 0.0f && matp[7] == 0.0f && matp[11] == 0.0f && matp[15] == 1.0f)
		HI_Transform_Points_43 (count, points, matp, result);
	else
		HI_Transform_Points_44 (count, points, matp, 0.001f, result, null);
#endif
}


HC_INTERFACE void HC_CDECL HC_Compute_Transformed_Points (
	int						count,
	Point const *			points,
	float const *			matp,
	Point *					result) 
{
	_hoops_PAPPR context("Compute_Transformed_Points");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Transformed_Points () */\n");
	);

#if 0
	HI_Compute_Transformed_Points (count, points, matp, result);
#else
	if (matp[3] == 0.0f && matp[7] == 0.0f && matp[11] == 0.0f && matp[15] == 1.0f)
		HI_Transform_Points_43 (count, points, matp, result);
	else
		HI_Transform_Points_44 (count, points, matp, 0.001f, result, null);
#endif
}



GLOBAL_FUNCTION void HI_Transform_Points_43 (
	int						count,
	Point const *			input,
	float const *			transform,
	Point alter *			output) {
	_hoops_RPRA const *		tm = (_hoops_RPRA const *)transform;

#ifdef _hoops_IIIPA
	if (BIT (HOOPS_WORLD->_hoops_CIIPA, _hoops_SIIPA) && count >= 80 &&
		((POINTER_SIZED_INT)input & 0x0F) == 0 &&
		((POINTER_SIZED_INT)output & 0x0F) == 0) {
		float							_hoops_GCIPA[100];
		float *							matrix_plus;
		unsigned int					mxcsr;

		if (HOOPS_WORLD->_hoops_RCIPA != 0) {
			unsigned int			temp;

			__asm	lea			eax, temp
			STMXCSR (EAX)

			mxcsr = temp;
			temp |= HOOPS_WORLD->_hoops_RCIPA;	/* _hoops_ACIPA _hoops_GHPA & _hoops_PCIPA-_hoops_RAHP-_hoops_GHPA _hoops_RPP _hoops_APP */

			__asm	lea			eax, temp		/* _hoops_GGR _hoops_AGIR _hoops_IHRPR _hoops_APGR _hoops_HCIPA _hoops_GPP _hoops_ICIPA */
			LDMXCSR	(EAX)
		}

		matrix_plus = (float *)ALIGNED_16(_hoops_GCIPA);

		{
			float *					_hoops_CCIPA = matrix_plus;
			int						row, col;

			for (col=0; col<3; col++) {			/* _hoops_CGHI _hoops_PIHP _hoops_PPRAR */
				for (row=0; row<4; row++) {
					*_hoops_CCIPA++ = tm[row][col];
					*_hoops_CCIPA++ = tm[row][col];
					*_hoops_CCIPA++ = tm[row][col];
					*_hoops_CCIPA++ = tm[row][col];
				}
			}
		}

		/* _hoops_PAGA: _hoops_SR _hoops_HHGC _hoops_IS:
				_hoops_AA {} _hoops_HPGP ((_hoops_RPR -= 4) >= 4);
		   _hoops_HIH _hoops_RH _hoops_RPGP _hoops_HRGR _hoops_SCIPA.  _hoops_RIIA _hoops_SR _hoops_PAH:
				_hoops_RPR -= 4;
				_hoops_AA {} _hoops_HPGP ((_hoops_RPR -= 4) >= 0);
				_hoops_RPR += 4;
		   _hoops_RGR _hoops_IGRIR 2 _hoops_GSRH, _hoops_HIH _hoops_GSIPA _hoops_PCCP _hoops_IHH _hoops_RPGP _hoops_ASSA _hoops_RH _hoops_HAPR
		*/

		__asm {
			mov				eax, dword ptr input
			mov				ecx, dword ptr count
			mov				edx, dword ptr output

			sub				ecx, 4							; _hoops_RSIPA count for 0-_hoops_ASIPA test
		  _hoops_PSIPA:
			mov				ebx, dword ptr matrix_plus		; _hoops_HSIPA to reset _hoops_ISIPA _hoops_GIPC

			; _hoops_CSIPA 4 points
			MOVAPS			(XMM4, EAX)						; 4: x1,_hoops_AGSIR,_hoops_HGSIR,x2
			add				eax, 16
			MOVAPS			(XMM5, EAX)						; 5: _hoops_PGSIR,_hoops_IGSIR,_hoops_SSIPA,_hoops_GGCPA
			add				eax, 16
			MOVAPS			(XMM6, EAX)						; 6: _hoops_RGCPA,_hoops_AGCPA,_hoops_PGCPA,_hoops_HGCPA
			add				eax, 16

			; _hoops_IGCPA by _hoops_CGCPA
			MOVAPS			(XMM0, XMM4)					; 0: x1,_hoops_AGSIR,_hoops_HGSIR,x2
			MOVAPS			(XMM2, XMM5)					; 2: _hoops_PGSIR,_hoops_IGSIR,_hoops_SSIPA,_hoops_GGCPA

			SHUFPS			(XMM0, XMM5, SHUFSEL (0,1,2,3))	; 0: x1,_hoops_AGSIR,_hoops_SSIPA,_hoops_GGCPA
			MOVAPS			(XMM1, XMM0)					; 1: x1,_hoops_AGSIR,_hoops_SSIPA,_hoops_GGCPA
			SHUFPS			(XMM2, XMM6, SHUFSEL (0,1,2,3))	; 2: _hoops_PGSIR,_hoops_IGSIR,_hoops_PGCPA,_hoops_HGCPA

			MOVHLPS			(XMM5, XMM4)					; 5: _hoops_HGSIR,x2,_hoops_SSIPA,_hoops_GGCPA
			MOVLHPS			(XMM5, XMM6)					; 5: _hoops_HGSIR,x2,_hoops_RGCPA,_hoops_AGCPA


			SHUFPS			(XMM0, XMM5, SHUFSEL (0,2,1,3))	; 0: x1,_hoops_SSIPA,x2,_hoops_AGCPA	!	_hoops_SGCPA _hoops_HGA
			SHUFPS			(XMM1, XMM2, SHUFSEL (1,3,0,2))	; 1: _hoops_AGSIR,_hoops_GGCPA,_hoops_PGSIR,_hoops_PGCPA	!	is not 1,2,3,4
			SHUFPS			(XMM2, XMM5, SHUFSEL (1,3,0,2))	; 2: _hoops_IGSIR,_hoops_HGCPA,_hoops_HGSIR,_hoops_RGCPA
			SHUFPS			(XMM2, XMM2, SHUFSEL (2,3,0,1))	; 2: _hoops_HGSIR,_hoops_RGCPA,_hoops_IGSIR,_hoops_HGCPA	!	_hoops_GRCPA is _hoops_RRCPA


			; _hoops_ARCPA by matrix
			; X
			MOVAPS			(XMM4, EBX)						; 4: _hoops_PRCPA
			add				ebx, 16
			MULPS			(XMM4, XMM0)					; 4: x*_hoops_PRCPA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_HRCPA
			add				ebx, 16
			MULPS			(XMM7, XMM1)					; 7: y*_hoops_HRCPA
			ADDPS			(XMM4, XMM7)					; 4: x*_hoops_PRCPA + y*_hoops_HRCPA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_IRCPA
			add				ebx, 16
			MULPS			(XMM7, XMM2)					; 7: z*_hoops_IRCPA
			ADDPS			(XMM4, XMM7)					; 4: x*_hoops_PRCPA + y*_hoops_HRCPA + z*_hoops_IRCPA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_CRCPA
			add				ebx, 16
			ADDPS			(XMM4, XMM7)					; 4: X = x*_hoops_PRCPA + y*_hoops_HRCPA + z*_hoops_IRCPA + _hoops_CRCPA

			; Y
			MOVAPS			(XMM5, EBX)						; 5: _hoops_SRCPA
			add				ebx, 16
			MULPS			(XMM5, XMM0)					; 5: x*_hoops_SRCPA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_PPCAA
			add				ebx, 16
			MULPS			(XMM7, XMM1)					; 7: y*_hoops_PPCAA
			ADDPS			(XMM5, XMM7)					; 5: x*_hoops_SRCPA + y*_hoops_PPCAA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_CPCAA
			add				ebx, 16
			MULPS			(XMM7, XMM2)					; 7: z*_hoops_CPCAA
			ADDPS			(XMM5, XMM7)					; 5: x*_hoops_SRCPA + y*_hoops_PPCAA + z*_hoops_CPCAA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_RHCAA
			add				ebx, 16
			ADDPS			(XMM5, XMM7)					; 5: Y = x*_hoops_SRCPA + y*_hoops_PPCAA + z*_hoops_CPCAA + _hoops_RHCAA

			; _hoops_GACPA
			MOVAPS			(XMM6, EBX)						; 6: _hoops_RACPA
			add				ebx, 16
			MULPS			(XMM6, XMM0)					; 6: x*_hoops_RACPA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_HPCAA
			add				ebx, 16
			MULPS			(XMM7, XMM1)					; 7: y*_hoops_HPCAA
			ADDPS			(XMM6, XMM7)					; 6: x*_hoops_RACPA + y*_hoops_HPCAA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_SPCAA
			add				ebx, 16
			MULPS			(XMM7, XMM2)					; 7: z*_hoops_SPCAA
			ADDPS			(XMM6, XMM7)					; 6: x*_hoops_RACPA + y*_hoops_HPCAA + z*_hoops_SPCAA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_AHCAA
			add				ebx, 16
			ADDPS			(XMM6, XMM7)					; 6: _hoops_GACPA = x*_hoops_RACPA + y*_hoops_HPCAA + z*_hoops_SPCAA + _hoops_AHCAA

			; _hoops_SIPI to _hoops_AACPA
			SHUFPS			(XMM4, XMM4, SHUFSEL (0,2,1,3))	; 4: x1,x2,_hoops_SSIPA,_hoops_AGCPA
			SHUFPS			(XMM5, XMM5, SHUFSEL (2,1,0,3))	; 5: _hoops_PGSIR,_hoops_GGCPA,_hoops_AGSIR,_hoops_PGCPA
			SHUFPS			(XMM6, XMM6, SHUFSEL (1,3,0,2))	; 6: _hoops_RGCPA,_hoops_HGCPA,_hoops_HGSIR,_hoops_IGSIR

			MOVAPS			(XMM0, XMM5)					; 0: _hoops_PGSIR,_hoops_GGCPA,_hoops_AGSIR,_hoops_PGCPA
			MOVAPS			(XMM1, XMM4)					; 1: x1,x2,_hoops_SSIPA,_hoops_AGCPA
			MOVAPS			(XMM2, XMM4)					; 2: x1,x2,_hoops_SSIPA,_hoops_AGCPA
			UNPCKHPS		(XMM0, XMM6)					; 0: _hoops_AGSIR,_hoops_HGSIR,_hoops_PGCPA,_hoops_IGSIR
			UNPCKHPS		(XMM1, XMM6)					; 1: _hoops_SSIPA,_hoops_HGSIR,_hoops_AGCPA,_hoops_IGSIR
			UNPCKHPS		(XMM2, XMM5)					; 2: _hoops_SSIPA,_hoops_AGSIR,_hoops_AGCPA,_hoops_PGCPA
			UNPCKLPS		(XMM0, XMM4)					; 0: _hoops_AGSIR,x1,_hoops_HGSIR,x2
			SHUFPS			(XMM1, XMM5, SHUFSEL (0,3,0,1))	; 1: _hoops_SSIPA,_hoops_IGSIR,_hoops_PGSIR,_hoops_GGCPA
			SHUFPS			(XMM2, XMM6, SHUFSEL (2,3,0,1))	; 2: _hoops_AGCPA,_hoops_PGCPA,_hoops_RGCPA,_hoops_HGCPA
			SHUFPS			(XMM0, XMM0, SHUFSEL (1,0,2,3))	; 0: _hoops_AGSIR,_hoops_HGSIR,x1,x2	!
			SHUFPS			(XMM1, XMM1, SHUFSEL (2,1,0,3))	; 1: _hoops_PGSIR,_hoops_IGSIR,_hoops_SSIPA,_hoops_GGCPA	!
			SHUFPS			(XMM2, XMM2, SHUFSEL (2,0,1,3))	; 2: _hoops_RGCPA,_hoops_AGCPA,_hoops_PGCPA,_hoops_HGCPA	!


			; _hoops_PACPA
			MOVAPS			(EDX, XMM0)
			add				edx, 16
			MOVAPS			(EDX, XMM1)
			add				edx, 16
			MOVAPS			(EDX, XMM2)
			add				edx, 16

			; _hoops_HACPA if _hoops_IHIIR _hoops_IACPA 4 _hoops_CACPA to do
			sub				ecx, 4
			jge				_hoops_PSIPA

			; _hoops_SACPA count & _hoops_AICHR in case _hoops_IHIIR _hoops_IACPA _hoops_CACPA to process _hoops_GPCPA
			add				ecx, 4							; _hoops_SACPA count
			mov				dword ptr input, eax
			mov				count, ecx
			mov				dword ptr output, edx
		}

		if (HOOPS_WORLD->_hoops_RCIPA != 0) {
			__asm	lea			eax, mxcsr
			LDMXCSR	(EAX)
		}
	}
#endif

	while (count-- > 0) {
		float			x, y, z;

		x = input->x * tm[0][0] + input->y * tm[1][0] + input->z * tm[2][0] + tm[3][0];
		y = input->x * tm[0][1] + input->y * tm[1][1] + input->z * tm[2][1] + tm[3][1];
		z = input->x * tm[0][2] + input->y * tm[1][2] + input->z * tm[2][2] + tm[3][2];
		++input;

		output->x = x;
		output->y = y;
		output->z = z;
		++output;
	}
}

#define	_hoops_RPCPA	1024

GLOBAL_FUNCTION void HI_Transform_Points_44 (
	int						count,
	Point const *			input,
	float const *			transform,
	float					_hoops_CHCR,
	Point alter *			output,
	float alter *			_hoops_APCPA) {
	_hoops_RPRA const *		tm = (_hoops_RPRA const *)transform;
	float alter *			ws = _hoops_APCPA;

#ifdef _hoops_IIIPA
	if (count >= 24 &&
		BIT (HOOPS_WORLD->_hoops_CIIPA, _hoops_SIIPA) &&
		((POINTER_SIZED_INT)input & 0x0F) == 0 &&
		((POINTER_SIZED_INT)output & 0x0F) == 0 &&
		((POINTER_SIZED_INT)ws & 0x0F) == 0) {

		int					_hoops_PPCPA = 0;

		float				_hoops_HPCPA[_hoops_RPCPA+16];
		float alter *		_hoops_IPCPA = null;

		if (ws == null) {
			if (count > _hoops_RPCPA) {
				ALLOC_ARRAY_ALIGNED (_hoops_IPCPA, count, float, 16);
				ws = _hoops_IPCPA;
				_hoops_PPCPA = count;
			}
			else
				ws = (float *)ALIGNED_16(_hoops_HPCPA);
		}


		float				_hoops_GCIPA[100];
		float *				matrix_plus;
		unsigned int		mxcsr;

		if (HOOPS_WORLD->_hoops_RCIPA != 0) {
			unsigned int	temp;

			__asm	lea			eax, temp
			STMXCSR (EAX)

			mxcsr = temp;
			temp |= HOOPS_WORLD->_hoops_RCIPA;	/* _hoops_ACIPA _hoops_GHPA & _hoops_PCIPA-_hoops_RAHP-_hoops_GHPA _hoops_RPP _hoops_APP */

			__asm	lea			eax, temp		/* _hoops_GGR _hoops_AGIR _hoops_IHRPR _hoops_APGR _hoops_HCIPA _hoops_GPP _hoops_ICIPA */
			LDMXCSR	(EAX)
		}

		/* _hoops_SR _hoops_HHGC _hoops_RGR _hoops_IS _hoops_SHH 16-_hoops_RAPSR _hoops_RGCGA */
		matrix_plus = (float *)ALIGNED_16(_hoops_GCIPA);

		{
			float *			_hoops_CCIPA = matrix_plus;
			int				row, col;

			for (col=0; col<4; col++) {
				for (row=0; row<4; row++) {
					*_hoops_CCIPA++ = tm[row][col];
					*_hoops_CCIPA++ = tm[row][col];
					*_hoops_CCIPA++ = tm[row][col];
					*_hoops_CCIPA++ = tm[row][col];
				}
			}

			*_hoops_CCIPA++ = _hoops_CHCR;
			*_hoops_CCIPA++ = _hoops_CHCR;
			*_hoops_CCIPA++ = _hoops_CHCR;
			*_hoops_CCIPA++ = _hoops_CHCR;

			*_hoops_CCIPA++ = 1.0f;
			*_hoops_CCIPA++ = 1.0f;
			*_hoops_CCIPA++ = 1.0f;
			*_hoops_CCIPA++ = 1.0f;
		}

		/* _hoops_PAGA: _hoops_SR _hoops_HHGC _hoops_IS:
				_hoops_AA {} _hoops_HPGP ((_hoops_RPR -= 4) >= 4);
		   _hoops_HIH _hoops_RH _hoops_RPGP _hoops_HRGR _hoops_SCIPA.  _hoops_RIIA _hoops_SR _hoops_PAH:
				_hoops_RPR -= 4;
				_hoops_AA {} _hoops_HPGP ((_hoops_RPR -= 4) >= 0);
				_hoops_RPR += 4;
		   _hoops_RGR _hoops_IGRIR 2 _hoops_GSRH, _hoops_HIH _hoops_GSIPA _hoops_PCCP _hoops_IHH _hoops_RPGP _hoops_ASSA _hoops_RH _hoops_HAPR
		*/

		__asm {
			push			edi
			mov				eax, dword ptr input
			mov				ecx, dword ptr count
			mov				edx, dword ptr output
			mov				edi, dword ptr ws

			sub				ecx, 4							; _hoops_RSIPA count for 0-_hoops_ASIPA test
		  _hoops_PSIPA:
			mov				ebx, dword ptr matrix_plus		; _hoops_HSIPA to reset _hoops_ISIPA _hoops_GIPC

			; _hoops_CSIPA 4 points
			MOVAPS			(XMM4, EAX)						; 4: x1,_hoops_AGSIR,_hoops_HGSIR,x2
			add				eax, 16
			MOVAPS			(XMM5, EAX)						; 5: _hoops_PGSIR,_hoops_IGSIR,_hoops_SSIPA,_hoops_GGCPA
			add				eax, 16
			MOVAPS			(XMM6, EAX)						; 6: _hoops_RGCPA,_hoops_AGCPA,_hoops_PGCPA,_hoops_HGCPA
			add				eax, 16

			; _hoops_IGCPA by _hoops_CGCPA
			MOVAPS			(XMM0, XMM4)					; 0: x1,_hoops_AGSIR,_hoops_HGSIR,x2
			MOVAPS			(XMM2, XMM5)					; 2: _hoops_PGSIR,_hoops_IGSIR,_hoops_SSIPA,_hoops_GGCPA

			SHUFPS			(XMM0, XMM5, SHUFSEL (0,1,2,3))	; 0: x1,_hoops_AGSIR,_hoops_SSIPA,_hoops_GGCPA
			MOVAPS			(XMM1, XMM0)					; 1: x1,_hoops_AGSIR,_hoops_SSIPA,_hoops_GGCPA
			SHUFPS			(XMM2, XMM6, SHUFSEL (0,1,2,3))	; 2: _hoops_PGSIR,_hoops_IGSIR,_hoops_PGCPA,_hoops_HGCPA

			MOVHLPS			(XMM5, XMM4)					; 5: _hoops_HGSIR,x2,_hoops_SSIPA,_hoops_GGCPA
			MOVLHPS			(XMM5, XMM6)					; 5: _hoops_HGSIR,x2,_hoops_RGCPA,_hoops_AGCPA


			SHUFPS			(XMM0, XMM5, SHUFSEL (0,2,1,3))	; 0: x1,_hoops_SSIPA,x2,_hoops_AGCPA	!	_hoops_SGCPA _hoops_HGA
			SHUFPS			(XMM1, XMM2, SHUFSEL (1,3,0,2))	; 1: _hoops_AGSIR,_hoops_GGCPA,_hoops_PGSIR,_hoops_PGCPA	!	is not 1,2,3,4
			SHUFPS			(XMM2, XMM5, SHUFSEL (1,3,0,2))	; 2: _hoops_IGSIR,_hoops_HGCPA,_hoops_HGSIR,_hoops_RGCPA
			SHUFPS			(XMM2, XMM2, SHUFSEL (2,3,0,1))	; 2: _hoops_HGSIR,_hoops_RGCPA,_hoops_IGSIR,_hoops_HGCPA	!	_hoops_GRCPA is _hoops_RRCPA


			; _hoops_ARCPA by matrix
			; X
			MOVAPS			(XMM4, EBX)						; 4: _hoops_PRCPA
			add				ebx, 16
			MULPS			(XMM4, XMM0)					; 4: x*_hoops_PRCPA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_HRCPA
			add				ebx, 16
			MULPS			(XMM7, XMM1)					; 7: y*_hoops_HRCPA
			ADDPS			(XMM4, XMM7)					; 4: x*_hoops_PRCPA + y*_hoops_HRCPA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_IRCPA
			add				ebx, 16
			MULPS			(XMM7, XMM2)					; 7: z*_hoops_IRCPA
			ADDPS			(XMM4, XMM7)					; 4: x*_hoops_PRCPA + y*_hoops_HRCPA + z*_hoops_IRCPA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_CRCPA
			add				ebx, 16
			ADDPS			(XMM4, XMM7)					; 4: X = x*_hoops_PRCPA + y*_hoops_HRCPA + z*_hoops_IRCPA + _hoops_CRCPA

			; Y
			MOVAPS			(XMM5, EBX)						; 5: _hoops_SRCPA
			add				ebx, 16
			MULPS			(XMM5, XMM0)					; 5: x*_hoops_SRCPA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_PPCAA
			add				ebx, 16
			MULPS			(XMM7, XMM1)					; 7: y*_hoops_PPCAA
			ADDPS			(XMM5, XMM7)					; 5: x*_hoops_SRCPA + y*_hoops_PPCAA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_CPCAA
			add				ebx, 16
			MULPS			(XMM7, XMM2)					; 7: z*_hoops_CPCAA
			ADDPS			(XMM5, XMM7)					; 5: x*_hoops_SRCPA + y*_hoops_PPCAA + z*_hoops_CPCAA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_RHCAA
			add				ebx, 16
			ADDPS			(XMM5, XMM7)					; 5: Y = x*_hoops_SRCPA + y*_hoops_PPCAA + z*_hoops_CPCAA + _hoops_RHCAA

			; _hoops_GACPA
			MOVAPS			(XMM6, EBX)						; 6: _hoops_RACPA
			add				ebx, 16
			MULPS			(XMM6, XMM0)					; 6: x*_hoops_RACPA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_HPCAA
			add				ebx, 16
			MULPS			(XMM7, XMM1)					; 7: y*_hoops_HPCAA
			ADDPS			(XMM6, XMM7)					; 6: x*_hoops_RACPA + y*_hoops_HPCAA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_SPCAA
			add				ebx, 16
			MULPS			(XMM7, XMM2)					; 7: z*_hoops_SPCAA
			ADDPS			(XMM6, XMM7)					; 6: x*_hoops_RACPA + y*_hoops_HPCAA + z*_hoops_SPCAA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_AHCAA
			add				ebx, 16
			ADDPS			(XMM6, XMM7)					; 6: _hoops_GACPA = x*_hoops_RACPA + y*_hoops_HPCAA + z*_hoops_SPCAA + _hoops_AHCAA

			; _hoops_CPCPA
			MOVAPS			(XMM3, EBX)						; 3: _hoops_SPCPA
			add				ebx, 16
			MULPS			(XMM3, XMM0)					; 3: x*_hoops_SPCPA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_IPCAA
			add				ebx, 16
			MULPS			(XMM7, XMM1)					; 7: y*_hoops_IPCAA
			ADDPS			(XMM3, XMM7)					; 3: x*_hoops_SPCPA + y*_hoops_IPCAA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_GHCAA
			add				ebx, 16
			MULPS			(XMM7, XMM2)					; 7: z*_hoops_GHCAA
			ADDPS			(XMM3, XMM7)					; 3: x*_hoops_SPCPA + y*_hoops_IPCAA + z*_hoops_GHCAA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_PHCAA
			add				ebx, 16
			ADDPS			(XMM3, XMM7)					; 3: _hoops_CPCPA = x*_hoops_SPCPA + y*_hoops_IPCAA + z*_hoops_GHCAA + _hoops_PHCAA

			; _hoops_GHCPA
			MOVAPS			(XMM7, EBX)						; 7: _hoops_CHCR
			add				ebx, 16
			_hoops_RHCPA			(XMM7, XMM3)					; 7: true if _hoops_CHCR < _hoops_CPCPA (_hoops_CPCPA _hoops_RRCI _hoops_AHCPA _hoops_CHCR)
			MOVAPS			(XMM1, XMM7)					; 1: true mask

			MOVAPS			(XMM0, EBX)						; 0: 1.0

			_hoops_PHCPA			(XMM7, XMM3)					; 7: _hoops_HHCPA where _hoops_CPCPA >= _hoops_CHCR
			_hoops_IHCPA			(XMM1, XMM0)					; 1: 1s where _hoops_CPCPA <  _hoops_CHCR
			_hoops_CHCPA			(XMM1, XMM7)					; 1: _hoops_HHCPA (1s where _hoops_CPCPA < _hoops_CHCR -- _hoops_SHCPA for _hoops_GICPA)

			_hoops_RICPA			(XMM0, XMM1)					; 0: 1/_hoops_CPCPA

			MULPS			(XMM4, XMM0)					; 4: Xr (x1,_hoops_SSIPA,x2,_hoops_AGCPA)
			MULPS			(XMM5, XMM0)					; 5: _hoops_AICPA (_hoops_AGSIR,_hoops_GGCPA,_hoops_PGSIR,_hoops_PGCPA)
			MULPS			(XMM6, XMM0)					; 6: _hoops_PICPA (_hoops_HGSIR,_hoops_RGCPA,_hoops_IGSIR,_hoops_HGCPA)


			; _hoops_SIPI to _hoops_AACPA
			SHUFPS			(XMM4, XMM4, SHUFSEL (0,2,1,3))	; 4: x1,x2,_hoops_SSIPA,_hoops_AGCPA
			SHUFPS			(XMM5, XMM5, SHUFSEL (2,1,0,3))	; 5: _hoops_PGSIR,_hoops_GGCPA,_hoops_AGSIR,_hoops_PGCPA
			SHUFPS			(XMM6, XMM6, SHUFSEL (1,3,0,2))	; 6: _hoops_RGCPA,_hoops_HGCPA,_hoops_HGSIR,_hoops_IGSIR

			MOVAPS			(XMM0, XMM5)					; 0: _hoops_PGSIR,_hoops_GGCPA,_hoops_AGSIR,_hoops_PGCPA
			MOVAPS			(XMM1, XMM4)					; 1: x1,x2,_hoops_SSIPA,_hoops_AGCPA
			MOVAPS			(XMM2, XMM4)					; 2: x1,x2,_hoops_SSIPA,_hoops_AGCPA
			UNPCKHPS		(XMM0, XMM6)					; 0: _hoops_AGSIR,_hoops_HGSIR,_hoops_PGCPA,_hoops_IGSIR
			UNPCKHPS		(XMM1, XMM6)					; 1: _hoops_SSIPA,_hoops_HGSIR,_hoops_AGCPA,_hoops_IGSIR
			UNPCKHPS		(XMM2, XMM5)					; 2: _hoops_SSIPA,_hoops_AGSIR,_hoops_AGCPA,_hoops_PGCPA
			UNPCKLPS		(XMM0, XMM4)					; 0: _hoops_AGSIR,x1,_hoops_HGSIR,x2
			SHUFPS			(XMM1, XMM5, SHUFSEL (0,3,0,1))	; 1: _hoops_SSIPA,_hoops_IGSIR,_hoops_PGSIR,_hoops_GGCPA
			SHUFPS			(XMM2, XMM6, SHUFSEL (2,3,0,1))	; 2: _hoops_AGCPA,_hoops_PGCPA,_hoops_RGCPA,_hoops_HGCPA
			SHUFPS			(XMM0, XMM0, SHUFSEL (1,0,2,3))	; 0: _hoops_AGSIR,_hoops_HGSIR,x1,x2	!
			SHUFPS			(XMM1, XMM1, SHUFSEL (2,1,0,3))	; 1: _hoops_PGSIR,_hoops_IGSIR,_hoops_SSIPA,_hoops_GGCPA	!
			SHUFPS			(XMM2, XMM2, SHUFSEL (2,0,1,3))	; 2: _hoops_RGCPA,_hoops_AGCPA,_hoops_PGCPA,_hoops_HGCPA	!


			; _hoops_HICPA w _hoops_HGA
			SHUFPS			(XMM3, XMM3, SHUFSEL (0,2,1,3))	; 3: _hoops_IICPA,_hoops_CICPA,_hoops_SICPA,_hoops_GCCPA


			; _hoops_PACPA
			MOVAPS			(EDX, XMM0)
			add				edx, 16
			MOVAPS			(EDX, XMM1)
			add				edx, 16
			MOVAPS			(EDX, XMM2)
			add				edx, 16

			MOVAPS			(_hoops_RCCPA, XMM3)
			add				edi, 16

			; _hoops_HACPA if _hoops_IHIIR _hoops_IACPA 4 _hoops_CACPA to do
			sub				ecx, 4
			jge				_hoops_PSIPA

			; _hoops_SACPA count & _hoops_AICHR in case _hoops_IHIIR _hoops_IACPA _hoops_CACPA to process _hoops_GPCPA
			add				ecx, 4							; _hoops_SACPA count
			mov				dword ptr input, eax
			mov				count, ecx
			mov				dword ptr output, edx
			mov				dword ptr ws, edi
			pop edi
		}

		if (HOOPS_WORLD->_hoops_RCIPA != 0) {
			__asm	lea			eax, mxcsr
			LDMXCSR	(EAX)
		}

		if (_hoops_IPCPA != null)
			FREE_ARRAY_ALIGNED (_hoops_IPCPA, _hoops_PPCPA, float, 16);
	}
#endif

	_hoops_SSAGR(input);
	_hoops_SSAGR(ws);
	_hoops_SSAGR(output);

	if (_hoops_APCPA) {

//#_hoops_PPIP _hoops_ACCPA
//#_hoops_PPIP _hoops_PCCPA
#define _hoops_HCCPA

#if defined(_hoops_ICCPA) || defined(_hoops_HCCPA)
		double _hoops_CCCPA = _hoops_CHCR;
#endif
		while (count-- > 0) {
#ifdef _hoops_SCCPA
			float			x, y, z, w;

			x = input->x * tm[0][0] + input->y * tm[1][0] + input->z * tm[2][0] + tm[3][0];
			y = input->x * tm[0][1] + input->y * tm[1][1] + input->z * tm[2][1] + tm[3][1];
			z = input->x * tm[0][2] + input->y * tm[1][2] + input->z * tm[2][2] + tm[3][2];
			w = input->x * tm[0][3] + input->y * tm[1][3] + input->z * tm[2][3] + tm[3][3];
			++input;

			*ws++ = w;

			if (w >= _hoops_CHCR) {
				w = 1.0f / w;
				output->x = x * w;
				output->y = y * w;
				output->z = z * w;
			}
			else {
				output->x = x;
				output->y = y;
				output->z = z;
			}
			++output;
#endif
#ifdef _hoops_ICCPA
			double	w;

			w = input->x * tm[0][3] + input->y * tm[1][3] + input->z * tm[2][3] + tm[3][3];

			*ws++ = w;

			if (w >= _hoops_CCCPA)
				w = 1.0 / w;
			else
				w = 1.0;

			output->x = (input->x * tm[0][0] + input->y * tm[1][0] + input->z * tm[2][0] + tm[3][0]) * w;
			output->y = (input->x * tm[0][1] + input->y * tm[1][1] + input->z * tm[2][1] + tm[3][1]) * w;
			output->z = (input->x * tm[0][2] + input->y * tm[1][2] + input->z * tm[2][2] + tm[3][2]) * w;

			++input;
			++output;
#endif
#ifdef _hoops_HCCPA
			double			x, y, z, w;

			w = input->x * tm[0][3] + input->y * tm[1][3] + input->z * tm[2][3] + tm[3][3];
			z = input->x * tm[0][2] + input->y * tm[1][2] + input->z * tm[2][2] + tm[3][2];
			y = input->x * tm[0][1] + input->y * tm[1][1] + input->z * tm[2][1] + tm[3][1];
			x = input->x * tm[0][0] + input->y * tm[1][0] + input->z * tm[2][0] + tm[3][0];

			if (w >= _hoops_CCCPA) {
				double _hoops_APCP = 1.0 / w;
				output->x = x * _hoops_APCP;
				output->y = y * _hoops_APCP;
				output->z = z * _hoops_APCP;
			}
			else {
				output->x = x;
				output->y = y;
				output->z = z;
			}

			*ws++ = w;
			++input;
			++output;
#endif
		}

	}
	else {
		while (count-- > 0) {
			float			x, y, z, w;

			x = input->x * tm[0][0] + input->y * tm[1][0] + input->z * tm[2][0] + tm[3][0];
			y = input->x * tm[0][1] + input->y * tm[1][1] + input->z * tm[2][1] + tm[3][1];
			z = input->x * tm[0][2] + input->y * tm[1][2] + input->z * tm[2][2] + tm[3][2];
			w = input->x * tm[0][3] + input->y * tm[1][3] + input->z * tm[2][3] + tm[3][3];
			++input;

			if (w >= _hoops_CHCR) {
				w = 1.0f / w;
				output->x = x * w;
				output->y = y * w;
				output->z = z * w;
			}
			else {
				output->x = x;
				output->y = y;
				output->z = z;
			}
			++output;
		}
	}
}





local void _hoops_GSCPA (
	float const *			matp,
	float alter *			_hoops_IRIPA) {
	_hoops_RPRA const *		mat = (_hoops_RPRA const *)matp;
	_hoops_RPRA alter *		_hoops_CRIPA = (_hoops_RPRA alter *)_hoops_IRIPA;

	// _hoops_SRIPA _hoops_IIGR _hoops_GAIPA _hoops_PPR _hoops_IRS _hoops_RSCA _hoops_RAIPA...
	float			_hoops_RSCPA = mat[1][0]*mat[2][1] - mat[1][1]*mat[2][0],
					_hoops_ASCPA = mat[1][0]*mat[2][2] - mat[1][2]*mat[2][0],
					_hoops_PSCPA = mat[1][0]*mat[2][3] - mat[1][3]*mat[2][0],
					_hoops_HSCPA = mat[1][0]*mat[3][1] - mat[1][1]*mat[3][0],
					_hoops_ISCPA = mat[1][0]*mat[3][2] - mat[1][2]*mat[3][0],
					_hoops_CSCPA = mat[1][0]*mat[3][3] - mat[1][3]*mat[3][0],
					_hoops_SSCPA = mat[1][1]*mat[2][2] - mat[1][2]*mat[2][1],
					_hoops_GGSPA = mat[1][1]*mat[2][3] - mat[1][3]*mat[2][1],
					_hoops_RGSPA = mat[1][1]*mat[3][2] - mat[1][2]*mat[3][1],
					_hoops_AGSPA = mat[1][1]*mat[3][3] - mat[1][3]*mat[3][1],
					_hoops_PGSPA = mat[1][2]*mat[2][3] - mat[1][3]*mat[2][2],
					_hoops_HGSPA = mat[1][2]*mat[3][3] - mat[1][3]*mat[3][2],
					_hoops_IGSPA = mat[2][0]*mat[3][1] - mat[2][1]*mat[3][0],
					_hoops_CGSPA = mat[2][0]*mat[3][2] - mat[2][2]*mat[3][0],
					_hoops_SGSPA = mat[2][0]*mat[3][3] - mat[2][3]*mat[3][0],
					_hoops_GRSPA = mat[2][1]*mat[3][2] - mat[2][2]*mat[3][1],
					_hoops_RRSPA = mat[2][1]*mat[3][3] - mat[2][3]*mat[3][1],
					_hoops_ARSPA = mat[2][2]*mat[3][3] - mat[2][3]*mat[3][2];


	_hoops_CRIPA[0][0] = mat[1][1]*_hoops_ARSPA -
				mat[1][2]*_hoops_RRSPA +
				mat[1][3]*_hoops_GRSPA;
	_hoops_CRIPA[0][1] = mat[0][2]*_hoops_RRSPA -
				mat[0][3]*_hoops_GRSPA -
				mat[0][1]*_hoops_ARSPA;
	_hoops_CRIPA[0][2] = mat[0][1]*_hoops_HGSPA -
				mat[0][2]*_hoops_AGSPA +
				mat[0][3]*_hoops_RGSPA;
	_hoops_CRIPA[0][3] = mat[0][2]*_hoops_GGSPA -
				mat[0][3]*_hoops_SSCPA -
				mat[0][1]*_hoops_PGSPA;
	_hoops_CRIPA[1][0] = mat[1][2]*_hoops_SGSPA -
				mat[1][3]*_hoops_CGSPA -
				mat[1][0]*_hoops_ARSPA;
	_hoops_CRIPA[1][1] = mat[0][0]*_hoops_ARSPA -
				mat[0][2]*_hoops_SGSPA +
				mat[0][3]*_hoops_CGSPA;
	_hoops_CRIPA[1][2] = mat[0][2]*_hoops_CSCPA -
				mat[0][3]*_hoops_ISCPA -
				mat[0][0]*_hoops_HGSPA;
	_hoops_CRIPA[1][3] = mat[0][0]*_hoops_PGSPA -
				mat[0][2]*_hoops_PSCPA +
				mat[0][3]*_hoops_ASCPA;
	_hoops_CRIPA[2][0] = mat[1][0]*_hoops_RRSPA -
				mat[1][1]*_hoops_SGSPA +
				mat[1][3]*_hoops_IGSPA;
	_hoops_CRIPA[2][1] = mat[0][1]*_hoops_SGSPA -
				mat[0][3]*_hoops_IGSPA -
				mat[0][0]*_hoops_RRSPA;
	_hoops_CRIPA[2][2] = mat[0][0]*_hoops_AGSPA -
				mat[0][1]*_hoops_CSCPA +
				mat[0][3]*_hoops_HSCPA;
	_hoops_CRIPA[2][3] = mat[0][1]*_hoops_PSCPA -
				mat[0][3]*_hoops_RSCPA -
				mat[0][0]*_hoops_GGSPA;
	_hoops_CRIPA[3][0] = mat[1][1]*_hoops_CGSPA -
				mat[1][2]*_hoops_IGSPA -
				mat[1][0]*_hoops_GRSPA;
	_hoops_CRIPA[3][1] = mat[0][0]*_hoops_GRSPA -
				mat[0][1]*_hoops_CGSPA +
				mat[0][2]*_hoops_IGSPA;
	_hoops_CRIPA[3][2] = mat[0][1]*_hoops_ISCPA -
				mat[0][2]*_hoops_HSCPA -
				mat[0][0]*_hoops_RGSPA;
	_hoops_CRIPA[3][3] = mat[0][0]*_hoops_SSCPA -
				mat[0][1]*_hoops_ASCPA +
				mat[0][2]*_hoops_RSCPA;

	// _hoops_RPP _hoops_SR _hoops_IRHH _hoops_RH [3][3] _hoops_PRSPA _hoops_RPRHR, _hoops_SR _hoops_HRSPA _hoops_RH _hoops_IRSPA _hoops_IIGR _hoops_IPPA _hoops_GHSSR

	if (_hoops_CRIPA[3][3] < 0.0f) {
		_hoops_CRIPA[0][0] = -_hoops_CRIPA[0][0];
		_hoops_CRIPA[0][1] = -_hoops_CRIPA[0][1];
		_hoops_CRIPA[0][2] = -_hoops_CRIPA[0][2];
		_hoops_CRIPA[0][3] = -_hoops_CRIPA[0][3];
		_hoops_CRIPA[1][0] = -_hoops_CRIPA[1][0];
		_hoops_CRIPA[1][1] = -_hoops_CRIPA[1][1];
		_hoops_CRIPA[1][2] = -_hoops_CRIPA[1][2];
		_hoops_CRIPA[1][3] = -_hoops_CRIPA[1][3];
		_hoops_CRIPA[2][0] = -_hoops_CRIPA[2][0];
		_hoops_CRIPA[2][1] = -_hoops_CRIPA[2][1];
		_hoops_CRIPA[2][2] = -_hoops_CRIPA[2][2];
		_hoops_CRIPA[2][3] = -_hoops_CRIPA[2][3];
		_hoops_CRIPA[3][0] = -_hoops_CRIPA[3][0];
		_hoops_CRIPA[3][1] = -_hoops_CRIPA[3][1];
		_hoops_CRIPA[3][2] = -_hoops_CRIPA[3][2];
		_hoops_CRIPA[3][3] = -_hoops_CRIPA[3][3];
	}
}


GLOBAL_FUNCTION void HI_Adjoint_44_Z (
	float const *			matp,
	float alter *			_hoops_CRIPA) {
	_hoops_RPRA const *		mat = (_hoops_RPRA const *)matp;
	float					w;

	// _hoops_SRIPA _hoops_IIGR _hoops_GAIPA _hoops_PPR _hoops_IRS _hoops_RSCA _hoops_RAIPA...
	float			_hoops_RSCPA = mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0],
					_hoops_ASCPA = mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0],
					_hoops_PSCPA = mat[1][0] * mat[2][3] - mat[1][3] * mat[2][0],
					_hoops_HSCPA = mat[1][0] * mat[3][1] - mat[1][1] * mat[3][0],
					_hoops_CSCPA = mat[1][0] * mat[3][3] - mat[1][3] * mat[3][0],
					_hoops_SSCPA = mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1],
					_hoops_GGSPA = mat[1][1] * mat[2][3] - mat[1][3] * mat[2][1],
					_hoops_AGSPA = mat[1][1] * mat[3][3] - mat[1][3] * mat[3][1],
					_hoops_IGSPA = mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0],
					_hoops_SGSPA = mat[2][0] * mat[3][3] - mat[2][3] * mat[3][0],
					_hoops_RRSPA = mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1];


	_hoops_CRIPA[0] = mat[1][0] * _hoops_RRSPA -
			 mat[1][1] * _hoops_SGSPA +
			 mat[1][3] * _hoops_IGSPA;
	_hoops_CRIPA[1] = mat[0][1] * _hoops_SGSPA -
			 mat[0][3] * _hoops_IGSPA -
			 mat[0][0] * _hoops_RRSPA;
	_hoops_CRIPA[2] = mat[0][0] * _hoops_AGSPA -
			 mat[0][1] * _hoops_CSCPA +
			 mat[0][3] * _hoops_HSCPA;
	_hoops_CRIPA[3] = mat[0][1] * _hoops_PSCPA -
			 mat[0][3] * _hoops_RSCPA -
			 mat[0][0] * _hoops_GGSPA;
	w = mat[0][0] * _hoops_SSCPA -
		mat[0][1] * _hoops_ASCPA +
		mat[0][2] * _hoops_RSCPA;

	if (w < 0.0f) {
		_hoops_CRIPA[0] = -_hoops_CRIPA[0];
		_hoops_CRIPA[1] = -_hoops_CRIPA[1];
		_hoops_CRIPA[2] = -_hoops_CRIPA[2];
		_hoops_CRIPA[3] = -_hoops_CRIPA[3];
	}
}



GLOBAL_FUNCTION void HI_Adjoint_44 (
	float const *			matp,
	float alter *			_hoops_IRIPA) {
	_hoops_RPRA alter *		_hoops_CRIPA = (_hoops_RPRA alter *)_hoops_IRIPA;

	_hoops_GSCPA (matp, _hoops_IRIPA);

	if (_hoops_CRIPA[3][3] != 1.0f && _hoops_CRIPA[3][3] != 0.0f) {
		float					scale;
		_hoops_RPRA alter *		_hoops_IHHIR;

		_hoops_IHHIR = (_hoops_RPRA alter *)_hoops_CRIPA;
		scale = 1.0f / _hoops_IHHIR[3][3];

		_hoops_IHHIR[0][0] *= scale;
		_hoops_IHHIR[0][1] *= scale;
		_hoops_IHHIR[0][2] *= scale;
		_hoops_IHHIR[0][3] *= scale;
		_hoops_IHHIR[1][0] *= scale;
		_hoops_IHHIR[1][1] *= scale;
		_hoops_IHHIR[1][2] *= scale;
		_hoops_IHHIR[1][3] *= scale;
		_hoops_IHHIR[2][0] *= scale;
		_hoops_IHHIR[2][1] *= scale;
		_hoops_IHHIR[2][2] *= scale;
		_hoops_IHHIR[2][3] *= scale;
		_hoops_IHHIR[3][0] *= scale;
		_hoops_IHHIR[3][1] *= scale;
		_hoops_IHHIR[3][2] *= scale;
		_hoops_IHHIR[3][3] = 1.0f;
	}
}



GLOBAL_FUNCTION void HI_Validate_Matrix_Adjoint (
	_hoops_HRPA const *		matrix) {

	if (matrix->_hoops_APRA == null)
		matrix->_hoops_APRA = _hoops_CRSPA::Create (HOOPS_WORLD->memory_pool);

	if (matrix->_hoops_RAGR != _hoops_SGICR) {
		HI_Adjoint_44 (&matrix->elements[0][0], &matrix->_hoops_APRA->data.elements[0][0]);
		matrix->_hoops_APRA->data._hoops_CPH = 0.0f;
		matrix->_hoops_APRA->data._hoops_RAGR = matrix->_hoops_RAGR;
	}
}


local float _hoops_SRSPA (_hoops_RPRA const *m) {
	return (m[0][0] * (m[1][1]*m[2][2] - m[2][1]*m[1][2]) -
			m[1][0] * (m[0][1]*m[2][2] - m[2][1]*m[0][2]) +
			m[2][0] * (m[0][1]*m[1][2] - m[1][1]*m[0][2]));
}

GLOBAL_FUNCTION void HI_Validate_Matrix_NEG3X3 (
	_hoops_HRPA alter *		matrix) {
	float					_hoops_HHIPA = _hoops_SRSPA ((_hoops_RPRA const *)matrix->elements);

	matrix->flags |= _hoops_HASA;

	if (_hoops_HHIPA < 0)
		matrix->_hoops_RAGR |= _hoops_CASA;
	else
		matrix->_hoops_RAGR &= ~_hoops_CASA;
}


GLOBAL_FUNCTION void HI_Matmul_44_by_44 (
	float const *			leftp,
	float const *			rightp,
	float alter *			resultp) {
	_hoops_RPRA const *		_hoops_GSHPA = (_hoops_RPRA const *)leftp;
	_hoops_RPRA const *		_hoops_RSHPA = (_hoops_RPRA const *)rightp;
	_hoops_RPRA alter *		_hoops_GASPA = (_hoops_RPRA alter *)resultp;

	_hoops_GASPA[0][0] = _hoops_GSHPA[0][0] * _hoops_RSHPA[0][0] + _hoops_GSHPA[0][1] * _hoops_RSHPA[1][0] +
			   _hoops_GSHPA[0][2] * _hoops_RSHPA[2][0] + _hoops_GSHPA[0][3] * _hoops_RSHPA[3][0];
	_hoops_GASPA[0][1] = _hoops_GSHPA[0][0] * _hoops_RSHPA[0][1] + _hoops_GSHPA[0][1] * _hoops_RSHPA[1][1] +
			   _hoops_GSHPA[0][2] * _hoops_RSHPA[2][1] + _hoops_GSHPA[0][3] * _hoops_RSHPA[3][1];
	_hoops_GASPA[0][2] = _hoops_GSHPA[0][0] * _hoops_RSHPA[0][2] + _hoops_GSHPA[0][1] * _hoops_RSHPA[1][2] +
			   _hoops_GSHPA[0][2] * _hoops_RSHPA[2][2] + _hoops_GSHPA[0][3] * _hoops_RSHPA[3][2];
	_hoops_GASPA[0][3] = _hoops_GSHPA[0][0] * _hoops_RSHPA[0][3] + _hoops_GSHPA[0][1] * _hoops_RSHPA[1][3] +
			   _hoops_GSHPA[0][2] * _hoops_RSHPA[2][3] + _hoops_GSHPA[0][3] * _hoops_RSHPA[3][3];

	_hoops_GASPA[1][0] = _hoops_GSHPA[1][0] * _hoops_RSHPA[0][0] + _hoops_GSHPA[1][1] * _hoops_RSHPA[1][0] +
			   _hoops_GSHPA[1][2] * _hoops_RSHPA[2][0] + _hoops_GSHPA[1][3] * _hoops_RSHPA[3][0];
	_hoops_GASPA[1][1] = _hoops_GSHPA[1][0] * _hoops_RSHPA[0][1] + _hoops_GSHPA[1][1] * _hoops_RSHPA[1][1] +
			   _hoops_GSHPA[1][2] * _hoops_RSHPA[2][1] + _hoops_GSHPA[1][3] * _hoops_RSHPA[3][1];
	_hoops_GASPA[1][2] = _hoops_GSHPA[1][0] * _hoops_RSHPA[0][2] + _hoops_GSHPA[1][1] * _hoops_RSHPA[1][2] +
			   _hoops_GSHPA[1][2] * _hoops_RSHPA[2][2] + _hoops_GSHPA[1][3] * _hoops_RSHPA[3][2];
	_hoops_GASPA[1][3] = _hoops_GSHPA[1][0] * _hoops_RSHPA[0][3] + _hoops_GSHPA[1][1] * _hoops_RSHPA[1][3] +
			   _hoops_GSHPA[1][2] * _hoops_RSHPA[2][3] + _hoops_GSHPA[1][3] * _hoops_RSHPA[3][3];

	_hoops_GASPA[2][0] = _hoops_GSHPA[2][0] * _hoops_RSHPA[0][0] + _hoops_GSHPA[2][1] * _hoops_RSHPA[1][0] +
			   _hoops_GSHPA[2][2] * _hoops_RSHPA[2][0] + _hoops_GSHPA[2][3] * _hoops_RSHPA[3][0];
	_hoops_GASPA[2][1] = _hoops_GSHPA[2][0] * _hoops_RSHPA[0][1] + _hoops_GSHPA[2][1] * _hoops_RSHPA[1][1] +
			   _hoops_GSHPA[2][2] * _hoops_RSHPA[2][1] + _hoops_GSHPA[2][3] * _hoops_RSHPA[3][1];
	_hoops_GASPA[2][2] = _hoops_GSHPA[2][0] * _hoops_RSHPA[0][2] + _hoops_GSHPA[2][1] * _hoops_RSHPA[1][2] +
			   _hoops_GSHPA[2][2] * _hoops_RSHPA[2][2] + _hoops_GSHPA[2][3] * _hoops_RSHPA[3][2];
	_hoops_GASPA[2][3] = _hoops_GSHPA[2][0] * _hoops_RSHPA[0][3] + _hoops_GSHPA[2][1] * _hoops_RSHPA[1][3] +
			   _hoops_GSHPA[2][2] * _hoops_RSHPA[2][3] + _hoops_GSHPA[2][3] * _hoops_RSHPA[3][3];

	_hoops_GASPA[3][0] = _hoops_GSHPA[3][0] * _hoops_RSHPA[0][0] + _hoops_GSHPA[3][1] * _hoops_RSHPA[1][0] +
			   _hoops_GSHPA[3][2] * _hoops_RSHPA[2][0] + _hoops_GSHPA[3][3] * _hoops_RSHPA[3][0];
	_hoops_GASPA[3][1] = _hoops_GSHPA[3][0] * _hoops_RSHPA[0][1] + _hoops_GSHPA[3][1] * _hoops_RSHPA[1][1] +
			   _hoops_GSHPA[3][2] * _hoops_RSHPA[2][1] + _hoops_GSHPA[3][3] * _hoops_RSHPA[3][1];
	_hoops_GASPA[3][2] = _hoops_GSHPA[3][0] * _hoops_RSHPA[0][2] + _hoops_GSHPA[3][1] * _hoops_RSHPA[1][2] +
			   _hoops_GSHPA[3][2] * _hoops_RSHPA[2][2] + _hoops_GSHPA[3][3] * _hoops_RSHPA[3][2];
	_hoops_GASPA[3][3] = _hoops_GSHPA[3][0] * _hoops_RSHPA[0][3] + _hoops_GSHPA[3][1] * _hoops_RSHPA[1][3] +
			   _hoops_GSHPA[3][2] * _hoops_RSHPA[2][3] + _hoops_GSHPA[3][3] * _hoops_RSHPA[3][3];
}


GLOBAL_FUNCTION void HI_Matmul_43_by_43 (
	float const *			leftp,
	float const *			rightp,
	float alter *			resultp) {
	_hoops_RPRA const *		_hoops_GSHPA = (_hoops_RPRA const *)leftp;
	_hoops_RPRA const *		_hoops_RSHPA = (_hoops_RPRA const *)rightp;
	_hoops_RPRA alter *		_hoops_GASPA = (_hoops_RPRA alter *)resultp;

	_hoops_GASPA[0][0] = _hoops_GSHPA[0][0] * _hoops_RSHPA[0][0] + _hoops_GSHPA[0][1] * _hoops_RSHPA[1][0] + _hoops_GSHPA[0][2] * _hoops_RSHPA[2][0];
	_hoops_GASPA[0][1] = _hoops_GSHPA[0][0] * _hoops_RSHPA[0][1] + _hoops_GSHPA[0][1] * _hoops_RSHPA[1][1] + _hoops_GSHPA[0][2] * _hoops_RSHPA[2][1];
	_hoops_GASPA[0][2] = _hoops_GSHPA[0][0] * _hoops_RSHPA[0][2] + _hoops_GSHPA[0][1] * _hoops_RSHPA[1][2] + _hoops_GSHPA[0][2] * _hoops_RSHPA[2][2];
	_hoops_GASPA[0][3] = 0.0f;

	_hoops_GASPA[1][0] = _hoops_GSHPA[1][0] * _hoops_RSHPA[0][0] + _hoops_GSHPA[1][1] * _hoops_RSHPA[1][0] + _hoops_GSHPA[1][2] * _hoops_RSHPA[2][0];
	_hoops_GASPA[1][1] = _hoops_GSHPA[1][0] * _hoops_RSHPA[0][1] + _hoops_GSHPA[1][1] * _hoops_RSHPA[1][1] + _hoops_GSHPA[1][2] * _hoops_RSHPA[2][1];
	_hoops_GASPA[1][2] = _hoops_GSHPA[1][0] * _hoops_RSHPA[0][2] + _hoops_GSHPA[1][1] * _hoops_RSHPA[1][2] + _hoops_GSHPA[1][2] * _hoops_RSHPA[2][2];
	_hoops_GASPA[1][3] = 0.0f;

	_hoops_GASPA[2][0] = _hoops_GSHPA[2][0] * _hoops_RSHPA[0][0] + _hoops_GSHPA[2][1] * _hoops_RSHPA[1][0] + _hoops_GSHPA[2][2] * _hoops_RSHPA[2][0];
	_hoops_GASPA[2][1] = _hoops_GSHPA[2][0] * _hoops_RSHPA[0][1] + _hoops_GSHPA[2][1] * _hoops_RSHPA[1][1] + _hoops_GSHPA[2][2] * _hoops_RSHPA[2][1];
	_hoops_GASPA[2][2] = _hoops_GSHPA[2][0] * _hoops_RSHPA[0][2] + _hoops_GSHPA[2][1] * _hoops_RSHPA[1][2] + _hoops_GSHPA[2][2] * _hoops_RSHPA[2][2];
	_hoops_GASPA[2][3] = 0.0f;

	_hoops_GASPA[3][0] = _hoops_GSHPA[3][0] * _hoops_RSHPA[0][0] + _hoops_GSHPA[3][1] * _hoops_RSHPA[1][0] + _hoops_GSHPA[3][2] * _hoops_RSHPA[2][0] +
			   _hoops_GSHPA[3][3] * _hoops_RSHPA[3][0];
	_hoops_GASPA[3][1] = _hoops_GSHPA[3][0] * _hoops_RSHPA[0][1] + _hoops_GSHPA[3][1] * _hoops_RSHPA[1][1] + _hoops_GSHPA[3][2] * _hoops_RSHPA[2][1] +
			   _hoops_GSHPA[3][3] * _hoops_RSHPA[3][1];
	_hoops_GASPA[3][2] = _hoops_GSHPA[3][0] * _hoops_RSHPA[0][2] + _hoops_GSHPA[3][1] * _hoops_RSHPA[1][2] + _hoops_GSHPA[3][2] * _hoops_RSHPA[2][2] +
			   _hoops_GSHPA[3][3] * _hoops_RSHPA[3][2];
	_hoops_GASPA[3][3] = 1.0f;
}


GLOBAL_FUNCTION void HI_Multiply_Matrices (
	_hoops_HRPA const *		left,
	_hoops_HRPA const *		right,
	_hoops_HRPA alter *		result) {

	if (!ANYBIT (left->_hoops_RAGR, _hoops_CICH)) {
		HI_Copy_Matrix (right, result);
	}
	else if (!ANYBIT (right->_hoops_RAGR, _hoops_CICH)) {
		HI_Copy_Matrix (left, result);
	}
	else {
		_hoops_HRPA		_hoops_HCIS;

		if (left == result) {
			HI_Copy_Matrix (left, &_hoops_HCIS);
			left = &_hoops_HCIS;
		}
		else if (right == result) {
			HI_Copy_Matrix (right, &_hoops_HCIS);
			right = &_hoops_HCIS;
		}

		result->_hoops_CPH = left->_hoops_CPH *
								  right->_hoops_CPH;
		result->_hoops_RAGR = left->_hoops_RAGR | right->_hoops_RAGR;
		result->flags = 0;
		result->_hoops_APRA = null;

		if (!BIT (result->_hoops_RAGR, _hoops_HRICR))
			HI_Matmul_43_by_43 (&left->elements[0][0],
								&right->elements[0][0],
								&result->elements[0][0]);
		else
			HI_Matmul_44_by_44 (&left->elements[0][0],
								&right->elements[0][0],
								&result->elements[0][0]);

		HI_Orthogonalize_Matrix (result);
	}
}


GLOBAL_FUNCTION void HI_Scale_And_Translate_Matrix (
	_hoops_HRPA const *		in,
	float					_hoops_GPCH,
	float					_hoops_RPCH,
	float					sz,
	float					tx,
	float					ty,
	float					tz,
	_hoops_HRPA alter *		_hoops_PAGR) {
	_hoops_RPRA alter *		_hoops_RASPA;
	_hoops_RPRA alter *		_hoops_AASPA;

	_hoops_PAGR->_hoops_CPH = 0.0f;
	_hoops_PAGR->_hoops_RAGR = _hoops_CICH;
	_hoops_PAGR->flags = 0;
	_hoops_PAGR->_hoops_APRA = null;

	_hoops_RASPA = (_hoops_RPRA alter *)in->elements;
	_hoops_AASPA = (_hoops_RPRA alter *)_hoops_PAGR->elements;

	_hoops_AASPA[0][0] = _hoops_RASPA[0][0] * _hoops_GPCH + _hoops_RASPA[0][3] * tx;
	_hoops_AASPA[0][1] = _hoops_RASPA[0][1] * _hoops_RPCH + _hoops_RASPA[0][3] * ty;
	_hoops_AASPA[0][2] = _hoops_RASPA[0][2] * sz + _hoops_RASPA[0][3] * tz;
	_hoops_AASPA[0][3] = _hoops_RASPA[0][3];

	_hoops_AASPA[1][0] = _hoops_RASPA[1][0] * _hoops_GPCH + _hoops_RASPA[1][3] * tx;
	_hoops_AASPA[1][1] = _hoops_RASPA[1][1] * _hoops_RPCH + _hoops_RASPA[1][3] * ty;
	_hoops_AASPA[1][2] = _hoops_RASPA[1][2] * sz + _hoops_RASPA[1][3] * tz;
	_hoops_AASPA[1][3] = _hoops_RASPA[1][3];

	_hoops_AASPA[2][0] = _hoops_RASPA[2][0] * _hoops_GPCH + _hoops_RASPA[2][3] * tx;
	_hoops_AASPA[2][1] = _hoops_RASPA[2][1] * _hoops_RPCH + _hoops_RASPA[2][3] * ty;
	_hoops_AASPA[2][2] = _hoops_RASPA[2][2] * sz + _hoops_RASPA[2][3] * tz;
	_hoops_AASPA[2][3] = _hoops_RASPA[2][3];

	_hoops_AASPA[3][0] = _hoops_RASPA[3][0] * _hoops_GPCH + _hoops_RASPA[3][3] * tx;
	_hoops_AASPA[3][1] = _hoops_RASPA[3][1] * _hoops_RPCH + _hoops_RASPA[3][3] * ty;
	_hoops_AASPA[3][2] = _hoops_RASPA[3][2] * sz + _hoops_RASPA[3][3] * tz;
	_hoops_AASPA[3][3] = _hoops_RASPA[3][3];
}



GLOBAL_FUNCTION void HI_Ident_44 (
	float alter *			outp) {
	_hoops_RPRA alter *		_hoops_PAGR = (_hoops_RPRA alter *)outp;

	_hoops_PAGR[0][0] = 1.0f;
	_hoops_PAGR[0][1] = 0.0f;
	_hoops_PAGR[0][2] = 0.0f;
	_hoops_PAGR[0][3] = 0.0f;
	_hoops_PAGR[1][0] = 0.0f;
	_hoops_PAGR[1][1] = 1.0f;
	_hoops_PAGR[1][2] = 0.0f;
	_hoops_PAGR[1][3] = 0.0f;
	_hoops_PAGR[2][0] = 0.0f;
	_hoops_PAGR[2][1] = 0.0f;
	_hoops_PAGR[2][2] = 1.0f;
	_hoops_PAGR[2][3] = 0.0f;
	_hoops_PAGR[3][0] = 0.0f;
	_hoops_PAGR[3][1] = 0.0f;
	_hoops_PAGR[3][2] = 0.0f;
	_hoops_PAGR[3][3] = 1.0f;
}



GLOBAL_FUNCTION void HI_Ident_Matrix (
	_hoops_HRPA alter *		matrix) {
	_hoops_RPRA alter *		_hoops_IHHIR;

	_hoops_IHHIR = (_hoops_RPRA alter *)matrix->elements;

	_hoops_IHHIR[0][0] = 1.0f;
	_hoops_IHHIR[0][1] = 0.0f;
	_hoops_IHHIR[0][2] = 0.0f;
	_hoops_IHHIR[0][3] = 0.0f;
	_hoops_IHHIR[1][0] = 0.0f;
	_hoops_IHHIR[1][1] = 1.0f;
	_hoops_IHHIR[1][2] = 0.0f;
	_hoops_IHHIR[1][3] = 0.0f;
	_hoops_IHHIR[2][0] = 0.0f;
	_hoops_IHHIR[2][1] = 0.0f;
	_hoops_IHHIR[2][2] = 1.0f;
	_hoops_IHHIR[2][3] = 0.0f;
	_hoops_IHHIR[3][0] = 0.0f;
	_hoops_IHHIR[3][1] = 0.0f;
	_hoops_IHHIR[3][2] = 0.0f;
	_hoops_IHHIR[3][3] = 1.0f;

	matrix->_hoops_CPH = 1.0f;
	matrix->_hoops_RAGR = _hoops_SGICR;
	matrix->flags = 0;
	matrix->_hoops_APRA = null;
}



GLOBAL_FUNCTION void HI_Copy_43 (
	float const *			_hoops_PASPA,
	float alter *			outp) {
	_hoops_RPRA alter *		_hoops_PAGR = (_hoops_RPRA alter *)outp;

	_hoops_AIGA(_hoops_PASPA, 16, float, outp);
	_hoops_PAGR[0][3] = 0.0f;
	_hoops_PAGR[1][3] = 0.0f;
	_hoops_PAGR[2][3] = 0.0f;
	_hoops_PAGR[3][3] = 1.0f;
}

GLOBAL_FUNCTION void HI_Copy_44 (
	float const *			_hoops_PASPA,
	float alter *			outp) {

	_hoops_AIGA(_hoops_PASPA, 16, float, outp);
}



GLOBAL_FUNCTION void HI_Copy_Matrix (
	_hoops_HRPA const *		in,
	_hoops_HRPA alter *		_hoops_PAGR) {

	_hoops_AIGA(in->elements, 16, float, _hoops_PAGR->elements);
	_hoops_PAGR->_hoops_CPH = in->_hoops_CPH;
	_hoops_PAGR->_hoops_RAGR = in->_hoops_RAGR;
	_hoops_PAGR->flags = in->flags;
	_hoops_PAGR->_hoops_APRA = null;
}



GLOBAL_FUNCTION void HI_Orthogonalize_Matrix (
	_hoops_HRPA alter *		matrix) {
	_hoops_RPRA alter *		_hoops_IHHIR;
	float					_hoops_IRPA;

	/*
	 * _hoops_GCCS-_hoops_HPGIR _hoops_GRR _hoops_GAGHR _hoops_AAGA _hoops_GGR _hoops_RH 3x3
	 */

	if (matrix->_hoops_CPH == 0.0f)
		return; /* _hoops_PAH'_hoops_RA _hoops_AA _hoops_SCH */

	_hoops_IHHIR = (_hoops_RPRA alter *)matrix->elements;

	_hoops_IRPA = _hoops_IHHIR[0][0] * _hoops_IHHIR[0][0] +
		   _hoops_IHHIR[0][1] * _hoops_IHHIR[0][1] +
		   _hoops_IHHIR[0][2] * _hoops_IHHIR[0][2];
	_hoops_IRPA = matrix->_hoops_CPH / _hoops_SGIHR (_hoops_IRPA);
	_hoops_IHHIR[0][0] *= _hoops_IRPA;
	_hoops_IHHIR[0][1] *= _hoops_IRPA;
	_hoops_IHHIR[0][2] *= _hoops_IRPA;

	_hoops_IRPA = _hoops_IHHIR[1][0] * _hoops_IHHIR[1][0] +
		   _hoops_IHHIR[1][1] * _hoops_IHHIR[1][1] +
		   _hoops_IHHIR[1][2] * _hoops_IHHIR[1][2];
	_hoops_IRPA = matrix->_hoops_CPH / _hoops_SGIHR (_hoops_IRPA);
	_hoops_IHHIR[1][0] *= _hoops_IRPA;
	_hoops_IHHIR[1][1] *= _hoops_IRPA;
	_hoops_IHHIR[1][2] *= _hoops_IRPA;

	_hoops_IRPA = _hoops_IHHIR[2][0] * _hoops_IHHIR[2][0] +
		   _hoops_IHHIR[2][1] * _hoops_IHHIR[2][1] +
		   _hoops_IHHIR[2][2] * _hoops_IHHIR[2][2];
	_hoops_IRPA = matrix->_hoops_CPH / _hoops_SGIHR (_hoops_IRPA);
	_hoops_IHHIR[2][0] *= _hoops_IRPA;
	_hoops_IHHIR[2][1] *= _hoops_IRPA;
	_hoops_IHHIR[2][2] *= _hoops_IRPA;

	matrix->_hoops_APRA = null;
}




GLOBAL_FUNCTION void HI_Figure_Translation_Matrix (
	float					x,
	float					y,
	float					z,
	_hoops_HRPA alter *		mat) {

	mat->_hoops_CPH = 1.0f;
	if (z == 0.0f && x == 0.0f && y == 0.0f)
		mat->_hoops_RAGR = false;
	else {
		mat->_hoops_RAGR = _hoops_PRICR;
		if (z != 0.0f)
			mat->_hoops_RAGR |= _hoops_RRICR;
	}
	mat->flags = 0;
	mat->_hoops_APRA = null;

	ZERO_ARRAY (mat->elements, 16, float);
	mat->elements[0][0] = 1.0f;
	mat->elements[1][1] = 1.0f;
	mat->elements[2][2] = 1.0f;
	mat->elements[3][0] = x;
	mat->elements[3][1] = y;
	mat->elements[3][2] = z;
	mat->elements[3][3] = 1.0f;
}




GLOBAL_FUNCTION void HI_Figure_Scale_Matrix (
	float					x,
	float					y,
	float					z,
	_hoops_HRPA alter *		mat) {

	mat->_hoops_CPH = 0.0f;
	mat->_hoops_RAGR = _hoops_SGICR;
	if ((z == y || -z == y) && (z == x || -z == x)) {
		if (z < 0)
			mat->_hoops_CPH = -z;
		else
			mat->_hoops_CPH = z;

		if (z != 1.0f)
			mat->_hoops_RAGR = _hoops_CHCP | _hoops_RRICR;
		else if (x != 1.0f || y != 1.0f)
			mat->_hoops_RAGR = _hoops_CHCP;
		else
			mat->_hoops_RAGR = false;
	}
	else {
		mat->_hoops_RAGR = _hoops_CHCP;
		if (z != 1.0f)
			mat->_hoops_RAGR |= _hoops_RRICR;
	}
	mat->flags = 0;
	mat->_hoops_APRA = null;

	ZERO_ARRAY (mat->elements, 16, float);
	mat->elements[0][0] = x;
	mat->elements[1][1] = y;
	mat->elements[2][2] = z;
	mat->elements[3][3] = 1.0f;
}




GLOBAL_FUNCTION void HI_Figure_Offaxis_Rotation_Mtx (
	float					x,
	float					y,
	float					z,
	float					_hoops_RAHCR,
	_hoops_HRPA alter *		mat) {
	_hoops_RPRA alter *		m = mat->elements;

	mat->_hoops_CPH = 1.0f;
	mat->flags = false;
	mat->_hoops_APRA = null;

	HI_Compute_Offaxis_Rotation (x, y, z, _hoops_RAHCR, &m[0][0]);

	if (m[0][2] != 0.0f || m[1][2] != 0.0f ||
		m[2][0] != 0.0f || m[2][1] != 0.0f ||
		m[2][2] != 1.0f)
		mat->_hoops_RAGR = _hoops_GRICR | _hoops_RRICR;
	else if (m[0][0] != 1.0f || m[0][1] != 0.0f ||
			 m[1][0] != 0.0f || m[1][1] != 0.0f)
		mat->_hoops_RAGR = _hoops_GRICR;
	else
		mat->_hoops_RAGR = false;

	/*
	 * _hoops_HASPA _hoops_HRGR _hoops_AIAH _hoops_HAHH _hoops_PGGA
	 * _hoops_SR _hoops_RGAR _hoops_SCCGR _hoops_RH _hoops_IASPA _hoops_PSCH.
	 */
	HI_Orthogonalize_Matrix (mat);
}




GLOBAL_FUNCTION void HI_Figure_Rotation_Matrix (
	float					x,
	float					y,
	float					z,
	_hoops_HRPA alter *		mat) {
	_hoops_RPRA alter *		m = mat->elements;

	mat->_hoops_CPH = 1.0f;
	mat->flags = false;
	mat->_hoops_APRA = null;

	HI_Compute_Rotation_Matrix (x, y, z, &m[0][0]);

	if (m[0][2] != 0.0f || m[1][2] != 0.0f ||
		m[2][0] != 0.0f || m[2][1] != 0.0f ||
		m[2][2] != 1.0f)
		mat->_hoops_RAGR = _hoops_GRICR | _hoops_RRICR;
	else if (m[0][0] != 1.0f || m[0][1] != 0.0f ||
			 m[1][0] != 0.0f || m[1][1] != 0.0f)
		mat->_hoops_RAGR = _hoops_GRICR;
	else
		mat->_hoops_RAGR = false;

	/*
	 * _hoops_HASPA _hoops_HRGR _hoops_AIAH _hoops_HAHH _hoops_PGGA
	 * _hoops_SR _hoops_RGAR _hoops_SCCGR _hoops_RH _hoops_IASPA _hoops_PSCH.
	 */
	HI_Orthogonalize_Matrix (mat);
}



GLOBAL_FUNCTION bool HI_Figure_General_Modelling_Mtx (
	float const *			_hoops_CASPA,
	_hoops_HRPA alter *		mat) 
{
	_hoops_RPRA const *		_hoops_SASPA = (_hoops_RPRA const *)_hoops_CASPA;
	_hoops_RPRA alter *		m = mat->elements;
	float					scale, tmp;

	if (_hoops_SASPA[0][3] != 0.0f || _hoops_SASPA[1][3] != 0.0f || _hoops_SASPA[2][3] != 0.0f) {
		HE_ERROR (HEC_MODELLING_MATRIX, HES_BAD_PERSPECTIVE, "Modelling matrices must have no perspective component");
		return false;
	}

	if (_hoops_SASPA[3][3] == 0.0f) {
		HE_ERROR (HEC_MODELLING_MATRIX, HES_SINGULAR_MATRIX, "Requested modelling matrix is singular");
		return false;
	}

	ZERO_ARRAY (mat->elements, 16, float);
	mat->_hoops_RAGR = _hoops_SGICR;
	mat->flags = 0;

	m[3][3] = 1.0f;

	if (_hoops_SASPA[3][3] == 1.0f) {
		m[0][0] = _hoops_SASPA[0][0];
		m[0][1] = _hoops_SASPA[0][1];
		m[0][2] = _hoops_SASPA[0][2];
		m[1][0] = _hoops_SASPA[1][0];
		m[1][1] = _hoops_SASPA[1][1];
		m[1][2] = _hoops_SASPA[1][2];
		m[2][0] = _hoops_SASPA[2][0];
		m[2][1] = _hoops_SASPA[2][1];
		m[2][2] = _hoops_SASPA[2][2];
		m[3][0] = _hoops_SASPA[3][0];
		m[3][1] = _hoops_SASPA[3][1];
		m[3][2] = _hoops_SASPA[3][2];
	}
	else {
		float				_hoops_GPSPA = 1.0f/_hoops_SASPA[3][3];

		m[0][0] = _hoops_SASPA[0][0] * _hoops_GPSPA;
		m[0][1] = _hoops_SASPA[0][1] * _hoops_GPSPA;
		m[0][2] = _hoops_SASPA[0][2] * _hoops_GPSPA;
		m[1][0] = _hoops_SASPA[1][0] * _hoops_GPSPA;
		m[1][1] = _hoops_SASPA[1][1] * _hoops_GPSPA;
		m[1][2] = _hoops_SASPA[1][2] * _hoops_GPSPA;
		m[2][0] = _hoops_SASPA[2][0] * _hoops_GPSPA;
		m[2][1] = _hoops_SASPA[2][1] * _hoops_GPSPA;
		m[2][2] = _hoops_SASPA[2][2] * _hoops_GPSPA;
		m[3][0] = _hoops_SASPA[3][0] * _hoops_GPSPA;
		m[3][1] = _hoops_SASPA[3][1] * _hoops_GPSPA;
		m[3][2] = _hoops_SASPA[3][2] * _hoops_GPSPA;
	}


	if (m[0][2] != 0.0f || m[1][2] != 0.0f || m[3][2] != 0.0f)
		mat->_hoops_RAGR |= _hoops_RRICR;

	scale = m[0][0] * m[0][0]  +  m[1][0] * m[1][0]	 +	m[2][0] * m[2][0];
	if (scale != 1.0f || m[0][0] == -1.0f)
		mat->_hoops_RAGR |= _hoops_CHCP;
	mat->_hoops_CPH = _hoops_SGIHR (scale);
	tmp = m[0][1] * m[0][1]	 +	m[1][1] * m[1][1]  +  m[2][1] * m[2][1];
	if (tmp != 1.0f || m[1][1] == -1.0f)
		mat->_hoops_RAGR |= _hoops_CHCP;
	if (tmp != scale) mat->_hoops_CPH = 0.0f;
	tmp = m[0][2] * m[0][2]	 +	m[1][2] * m[1][2]  +  m[2][2] * m[2][2];
	if (tmp != 1.0f || m[2][2] == -1.0f)
		mat->_hoops_RAGR |= _hoops_CHCP;
	if (tmp != scale) mat->_hoops_CPH = 0.0f;

	if (m[3][0] != 0.0f || m[3][1] != 0.0f || m[3][2] != 0.0f)
		mat->_hoops_RAGR |= _hoops_PRICR;

	if (m[0][1] != 0.0f || m[0][2] != 0.0f ||
		m[1][0] != 0.0f || m[1][2] != 0.0f ||
		m[2][0] != 0.0f || m[2][1] != 0.0f)
		mat->_hoops_RAGR |= _hoops_GRICR;

	return true;
}



/* _hoops_IGIPR "_hoops_IRSS" _hoops_HRGR _hoops_SCGA */
GLOBAL_FUNCTION void HI_Arbitrary_Rotate (
	Vector const *			axis,
	Point const	*			_hoops_RPSPA,
	float					_hoops_RAHCR,
	Point *					_hoops_APSPA) {
	float					_hoops_GGHCR,
							_hoops_AGHCR;
	float					_hoops_PPSPA,
							_hoops_HPSPA,
							_hoops_IPSPA,
							_hoops_CPSPA,
							_hoops_SPSPA,
							_hoops_GHSPA;

	_hoops_RICH (_hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR);

	_hoops_PPSPA = 1.0f - _hoops_AGHCR;
	_hoops_HPSPA = _hoops_PPSPA * axis->x * axis->y;
	_hoops_IPSPA = _hoops_PPSPA * axis->x * axis->z;
	_hoops_CPSPA = _hoops_PPSPA * axis->y * axis->z;

	_hoops_SPSPA =	 _hoops_GGHCR * _hoops_RPSPA->z * axis->y - _hoops_GGHCR * _hoops_RPSPA->y * axis->z +
			 _hoops_PPSPA * _hoops_RPSPA->x * axis->x * axis->x + _hoops_IPSPA * _hoops_RPSPA->z +
			 _hoops_HPSPA * _hoops_RPSPA->y + _hoops_AGHCR * _hoops_RPSPA->x;

	_hoops_GHSPA =	 _hoops_GGHCR * _hoops_RPSPA->x * axis->z + _hoops_PPSPA * _hoops_RPSPA->y * axis->y * axis->y -
			 _hoops_GGHCR * _hoops_RPSPA->z * axis->x + _hoops_CPSPA * _hoops_RPSPA->z + _hoops_AGHCR * _hoops_RPSPA->y +
			 _hoops_HPSPA * _hoops_RPSPA->x;

	_hoops_APSPA->z = _hoops_PPSPA * _hoops_RPSPA->z * axis->z * axis->z - _hoops_GGHCR * _hoops_RPSPA->x * axis->y +
			 _hoops_GGHCR * _hoops_RPSPA->y * axis->x + _hoops_AGHCR * _hoops_RPSPA->z + _hoops_CPSPA * _hoops_RPSPA->y +
			 _hoops_IPSPA * _hoops_RPSPA->x;
	_hoops_APSPA->y = _hoops_GHSPA;
	_hoops_APSPA->x = _hoops_SPSPA;

/* _hoops_RHSPA _hoops_SPPPR _hoops_IS _hoops_CAHP _hoops_RH _hoops_HPSIR */
/*	_hoops_AHSPA(_hoops_PHSPA):=_hoops_RSGA([_hoops_HHSPA(_hoops_PHSPA),0,-_hoops_IHSPA(_hoops_PHSPA)],[0,1,0],[_hoops_IHSPA(_hoops_PHSPA),0,_hoops_HHSPA(_hoops_PHSPA)])_hoops_CHSPA
	_hoops_SHSPA(_hoops_PHSPA):=_hoops_RSGA([_hoops_HHSPA(_hoops_PHSPA),_hoops_IHSPA(_hoops_PHSPA),0],[-_hoops_IHSPA(_hoops_PHSPA),_hoops_HHSPA(_hoops_PHSPA),0],[0,0,1])_hoops_CHSPA

	_hoops_SHSPA(_hoops_IRS)._hoops_AHSPA(_hoops_RCSR)._hoops_SHSPA(_hoops_GSGGR)._hoops_AHSPA(-_hoops_RCSR)._hoops_SHSPA(-_hoops_IRS)_hoops_CHSPA
	%,_hoops_IRS=-_hoops_GISPA(_hoops_HAPC,_hoops_SISR),_hoops_RCSR=-_hoops_GISPA(_hoops_AGGIR(_hoops_SISR^2+_hoops_HAPC^2),_hoops_SSH),_hoops_GSGGR=_hoops_RISPA
	_hoops_AISPA(1,_hoops_SISR^2+_hoops_HAPC^2+_hoops_SSH^2,%)_hoops_CHSPA
	_hoops_AISPA(_hoops_SISR^2+_hoops_HAPC^2,1-_hoops_SSH^2,%)_hoops_CHSPA
	_hoops_PISPA(_hoops_HISPA,1-_hoops_HHSPA(_hoops_RCSA),%)_hoops_CHSPA
	_hoops_PISPA(-_hoops_HISPA,_hoops_HHSPA(_hoops_RCSA)-1,%)_hoops_CHSPA
	_hoops_PISPA(_hoops_HISPA*_hoops_SSH^2+_hoops_HHSPA(_hoops_RCSA),-_hoops_HISPA*_hoops_HAPC^2-_hoops_HISPA*_hoops_SISR^2+1,%)_hoops_CHSPA
	_hoops_AISPA(_hoops_IISPA,_hoops_HISPA*_hoops_SISR*_hoops_HAPC,%)_hoops_CHSPA
	_hoops_AISPA(_hoops_CISPA,_hoops_HISPA*_hoops_SISR*_hoops_SSH,%)_hoops_CHSPA
	_hoops_PISPA(_hoops_RGHCR,_hoops_IHSPA(_hoops_RCSA),%)_hoops_CHSPA
	_hoops_PISPA(_hoops_SRGPA,_hoops_HHSPA(_hoops_RCSA),%)_hoops_CHSPA
	_hoops_HGPI:_hoops_AISPA(_hoops_SISPA,_hoops_HISPA*_hoops_HAPC*_hoops_SSH,%);
	_hoops_GCSPA:_hoops_RCSPA([_hoops_ACSPA,_hoops_PCSPA,_hoops_HCSPA].%);
	_hoops_ICSPA:_hoops_CCSPA
	_hoops_SCSPA(_hoops_HGPI,_hoops_HGPI)_hoops_CHSPA
*//*
_hoops_RSGA([_hoops_HISPA*_hoops_SISR^2+_hoops_SRGPA,_hoops_RGHCR*_hoops_SSH+_hoops_IISPA,_hoops_CISPA-_hoops_RGHCR*_hoops_HAPC],
	   [_hoops_IISPA-_hoops_RGHCR*_hoops_SSH,_hoops_HISPA*_hoops_HAPC^2+_hoops_SRGPA,_hoops_RGHCR*_hoops_SISR+_hoops_SISPA],
	   [_hoops_RGHCR*_hoops_HAPC+_hoops_CISPA,_hoops_SISPA-_hoops_RGHCR*_hoops_SISR,_hoops_HISPA*_hoops_SSH^2+_hoops_SRGPA]);
*//*
_hoops_SCSPA(_hoops_GCSPA,_hoops_GCSPA)_hoops_CHSPA
*//*
_hoops_RSGA([-_hoops_RGHCR*_hoops_PCSPA*_hoops_SSH+_hoops_RGHCR*_hoops_HCSPA*_hoops_HAPC+_hoops_HISPA*_hoops_ACSPA*_hoops_SISR^2+_hoops_CISPA*_hoops_HCSPA+_hoops_IISPA*_hoops_PCSPA+_hoops_SRGPA*_hoops_ACSPA,
		_hoops_RGHCR*_hoops_ACSPA*_hoops_SSH+_hoops_HISPA*_hoops_PCSPA*_hoops_HAPC^2-_hoops_RGHCR*_hoops_HCSPA*_hoops_SISR+_hoops_SISPA*_hoops_HCSPA+_hoops_SRGPA*_hoops_PCSPA+_hoops_IISPA*_hoops_ACSPA,
		_hoops_HISPA*_hoops_HCSPA*_hoops_SSH^2-_hoops_RGHCR*_hoops_ACSPA*_hoops_HAPC+_hoops_RGHCR*_hoops_PCSPA*_hoops_SISR+_hoops_SRGPA*_hoops_HCSPA+_hoops_SISPA*_hoops_PCSPA+_hoops_CISPA*_hoops_ACSPA])
*//*
*/
}


GLOBAL_FUNCTION void HI_Arbitrary_Rotate_SC (
	Vector const *		axis,
	Point const	*		_hoops_RPSPA,
	float				_hoops_GGHCR,
	float				_hoops_AGHCR,
	Point *				_hoops_APSPA) {
	float				_hoops_PPSPA = 1.0f - _hoops_AGHCR,
						_hoops_HPSPA = _hoops_PPSPA * axis->x * axis->y,
						_hoops_IPSPA = _hoops_PPSPA * axis->x * axis->z,
						_hoops_CPSPA = _hoops_PPSPA * axis->y * axis->z,
						_hoops_SPSPA,
						_hoops_GHSPA;

	_hoops_SPSPA =	 _hoops_GGHCR * _hoops_RPSPA->z * axis->y - _hoops_GGHCR * _hoops_RPSPA->y * axis->z +
			 _hoops_PPSPA * _hoops_RPSPA->x * axis->x * axis->x + _hoops_IPSPA * _hoops_RPSPA->z +
			 _hoops_HPSPA * _hoops_RPSPA->y + _hoops_AGHCR * _hoops_RPSPA->x;

	_hoops_GHSPA =	 _hoops_GGHCR * _hoops_RPSPA->x * axis->z + _hoops_PPSPA * _hoops_RPSPA->y * axis->y * axis->y -
			 _hoops_GGHCR * _hoops_RPSPA->z * axis->x + _hoops_CPSPA * _hoops_RPSPA->z + _hoops_AGHCR * _hoops_RPSPA->y +
			 _hoops_HPSPA * _hoops_RPSPA->x;

	_hoops_APSPA->z = _hoops_PPSPA * _hoops_RPSPA->z * axis->z * axis->z - _hoops_GGHCR * _hoops_RPSPA->x * axis->y +
			 _hoops_GGHCR * _hoops_RPSPA->y * axis->x + _hoops_AGHCR * _hoops_RPSPA->z + _hoops_CPSPA * _hoops_RPSPA->y +
			 _hoops_IPSPA * _hoops_RPSPA->x;
	_hoops_APSPA->y = _hoops_GHSPA;
	_hoops_APSPA->x = _hoops_SPSPA;
}



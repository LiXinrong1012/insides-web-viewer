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
 * $Id: obf_tmp.txt 1.59 2010-03-25 22:35:21 heppe Exp $
 */

#include "hoops.h"
#include "hi_proto.h"

#ifdef DISABLE_TABLE_LOOKUPS
#	include		<math.h>
#	define		_hoops_AHSSI		1.0e10f
#else

/* _hoops_IRS _hoops_GASR _hoops_IIGR _hoops_GHSGP _hoops_GGICR _hoops_RRAA _hoops_PHSSI */
local float const _hoops_HHSSI[] = {
		/* 1.00000 */	1.00000f, 0.99612f, 0.99228f, 0.98848f,
		/* 1.03125 */	0.98474f, 0.98103f, 0.97735f, 0.97373f,
		/* 1.06250 */	0.97014f, 0.96659f, 0.96308f, 0.95962f,
		/* 1.09375 */	0.95618f, 0.95279f, 0.94942f, 0.94610f,
		/* 1.12500 */	0.94281f, 0.93955f, 0.93633f, 0.93314f,
		/* 1.15625 */	0.92998f, 0.92685f, 0.92376f, 0.92070f,
		/* 1.18750 */	0.91767f, 0.91466f, 0.91169f, 0.90874f,
		/* 1.21875 */	0.90582f, 0.90293f, 0.90007f, 0.89724f,
		/* 1.25000 */	0.89443f, 0.89165f, 0.88889f, 0.88616f,
		/* 1.28125 */	0.88345f, 0.88077f, 0.87812f, 0.87548f,
		/* 1.31250 */	0.87287f, 0.87028f, 0.86772f, 0.86518f,
		/* 1.34375 */	0.86266f, 0.86016f, 0.85769f, 0.85523f,
		/* 1.37500 */	0.85281f, 0.85039f, 0.84800f, 0.84562f,
		/* 1.40625 */	0.84328f, 0.84094f, 0.83863f, 0.83633f,
		/* 1.43750 */	0.83406f, 0.83180f, 0.82956f, 0.82734f,
		/* 1.46875 */	0.82514f, 0.82295f, 0.82078f, 0.81863f,
		/* 1.50000 */	0.81650f, 0.81438f, 0.81228f, 0.81019f,
		/* 1.53125 */	0.80812f, 0.80607f, 0.80403f, 0.80201f,
		/* 1.56250 */	0.80000f, 0.79801f, 0.79603f, 0.79407f,
		/* 1.59375 */	0.79212f, 0.79018f, 0.78826f, 0.78636f,
		/* 1.62500 */	0.78447f, 0.78258f, 0.78072f, 0.77887f,
		/* 1.65625 */	0.77703f, 0.77520f, 0.77339f, 0.77159f,
		/* 1.68750 */	0.76980f, 0.76803f, 0.76626f, 0.76451f,
		/* 1.71875 */	0.76277f, 0.76104f, 0.75932f, 0.75762f,
		/* 1.75000 */	0.75593f, 0.75424f, 0.75258f, 0.75092f,
		/* 1.78125 */	0.74927f, 0.74763f, 0.74600f, 0.74439f,
		/* 1.81250 */	0.74278f, 0.74119f, 0.73960f, 0.73802f,
		/* 1.84375 */	0.73646f, 0.73491f, 0.73336f, 0.73182f,
		/* 1.87500 */	0.73029f, 0.72878f, 0.72727f, 0.72577f,
		/* 1.90625 */	0.72429f, 0.72280f, 0.72133f, 0.71988f,
		/* 1.93750 */	0.71842f, 0.71698f, 0.71554f, 0.71412f,
		/* 1.96875 */	0.71270f, 0.71129f, 0.70988f, 0.70849f,
		/* 2.00000 */	0.70711f, 0.70573f, 0.70436f, 0.70300f,
		/* 2.03125 */	0.70165f, 0.70030f, 0.69896f, 0.69763f,
		/* 2.06250 */	0.69631f, 0.69499f, 0.69369f, 0.69239f,
		/* 2.09375 */	0.69109f, 0.68981f, 0.68853f, 0.68726f,
		/* 2.12500 */	0.68599f, 0.68473f, 0.68348f, 0.68224f,
		/* 2.15625 */	0.68100f, 0.67977f, 0.67855f, 0.67733f,
		/* 2.18750 */	0.67612f, 0.67492f, 0.67372f, 0.67253f,
		/* 2.21875 */	0.67134f, 0.67016f, 0.66899f, 0.66783f,
		/* 2.25000 */	0.66667f, 0.66551f, 0.66436f, 0.66322f,
		/* 2.28125 */	0.66208f, 0.66096f, 0.65983f, 0.65871f,
		/* 2.31250 */	0.65760f, 0.65649f, 0.65539f, 0.65429f,
		/* 2.34375 */	0.65320f, 0.65211f, 0.65103f, 0.64995f,
		/* 2.37500 */	0.64889f, 0.64782f, 0.64676f, 0.64571f,
		/* 2.40625 */	0.64466f, 0.64361f, 0.64257f, 0.64154f,
		/* 2.43750 */	0.64051f, 0.63949f, 0.63847f, 0.63745f,
		/* 2.46875 */	0.63644f, 0.63544f, 0.63444f, 0.63344f,
		/* 2.50000 */	0.63246f, 0.63147f, 0.63049f, 0.62951f,
		/* 2.53125 */	0.62854f, 0.62757f, 0.62661f, 0.62565f,
		/* 2.56250 */	0.62470f, 0.62374f, 0.62280f, 0.62186f,
		/* 2.59375 */	0.62092f, 0.61999f, 0.61906f, 0.61813f,
		/* 2.62500 */	0.61721f, 0.61630f, 0.61538f, 0.61448f,
		/* 2.65625 */	0.61357f, 0.61267f, 0.61177f, 0.61088f,
		/* 2.68750 */	0.60999f, 0.60911f, 0.60823f, 0.60735f,
		/* 2.71875 */	0.60648f, 0.60561f, 0.60474f, 0.60388f,
		/* 2.75000 */	0.60302f, 0.60217f, 0.60132f, 0.60047f,
		/* 2.78125 */	0.59962f, 0.59878f, 0.59795f, 0.59711f,
		/* 2.81250 */	0.59629f, 0.59546f, 0.59464f, 0.59382f,
		/* 2.84375 */	0.59300f, 0.59219f, 0.59138f, 0.59057f,
		/* 2.87500 */	0.58977f, 0.58897f, 0.58817f, 0.58738f,
		/* 2.90625 */	0.58659f, 0.58580f, 0.58502f, 0.58424f,
		/* 2.93750 */	0.58346f, 0.58269f, 0.58191f, 0.58115f,
		/* 2.96875 */	0.58038f, 0.57962f, 0.57886f, 0.57810f,
		/* 3.00000 */	0.57735f};

/* _hoops_IRS _hoops_GASR _hoops_IIGR _hoops_GHSGP _hoops_IAHP _hoops_IIGR _hoops_GGICR _hoops_RRAA _hoops_PHSSI */
/* _hoops_RGR _hoops_HRGR _hoops_RH _hoops_AIAII _hoops_IIGR _hoops_RH _hoops_GASR _hoops_ARRS */
local float const _hoops_IHSSI[] = {
		/* 1.00000 */	-0.00388f, -0.00383f, -0.00380f, -0.00375f,
		/* 1.03125 */	-0.00371f, -0.00367f, -0.00363f, -0.00359f,
		/* 1.06250 */	-0.00354f, -0.00351f, -0.00347f, -0.00344f,
		/* 1.09375 */	-0.00339f, -0.00337f, -0.00332f, -0.00329f,
		/* 1.12500 */	-0.00326f, -0.00322f, -0.00319f, -0.00316f,
		/* 1.15625 */	-0.00313f, -0.00309f, -0.00306f, -0.00303f,
		/* 1.18750 */	-0.00300f, -0.00298f, -0.00295f, -0.00291f,
		/* 1.21875 */	-0.00289f, -0.00286f, -0.00283f, -0.00281f,
		/* 1.25000 */	-0.00278f, -0.00276f, -0.00273f, -0.00270f,
		/* 1.28125 */	-0.00268f, -0.00265f, -0.00264f, -0.00261f,
		/* 1.31250 */	-0.00259f, -0.00256f, -0.00255f, -0.00252f,
		/* 1.34375 */	-0.00250f, -0.00247f, -0.00246f, -0.00243f,
		/* 1.37500 */	-0.00242f, -0.00239f, -0.00237f, -0.00235f,
		/* 1.40625 */	-0.00233f, -0.00231f, -0.00230f, -0.00227f,
		/* 1.43750 */	-0.00225f, -0.00224f, -0.00222f, -0.00221f,
		/* 1.46875 */	-0.00219f, -0.00217f, -0.00215f, -0.00213f,
		/* 1.50000 */	-0.00212f, -0.00210f, -0.00209f, -0.00207f,
		/* 1.53125 */	-0.00205f, -0.00204f, -0.00202f, -0.00201f,
		/* 1.56250 */	-0.00199f, -0.00198f, -0.00197f, -0.00195f,
		/* 1.59375 */	-0.00193f, -0.00192f, -0.00191f, -0.00189f,
		/* 1.62500 */	-0.00188f, -0.00186f, -0.00185f, -0.00184f,
		/* 1.65625 */	-0.00183f, -0.00181f, -0.00180f, -0.00179f,
		/* 1.68750 */	-0.00177f, -0.00177f, -0.00175f, -0.00174f,
		/* 1.71875 */	-0.00173f, -0.00172f, -0.00170f, -0.00170f,
		/* 1.75000 */	-0.00168f, -0.00167f, -0.00166f, -0.00165f,
		/* 1.78125 */	-0.00164f, -0.00163f, -0.00162f, -0.00160f,
		/* 1.81250 */	-0.00160f, -0.00158f, -0.00158f, -0.00157f,
		/* 1.84375 */	-0.00155f, -0.00155f, -0.00153f, -0.00153f,
		/* 1.87500 */	-0.00152f, -0.00151f, -0.00150f, -0.00149f,
		/* 1.90625 */	-0.00148f, -0.00147f, -0.00146f, -0.00145f,
		/* 1.93750 */	-0.00144f, -0.00144f, -0.00143f, -0.00142f,
		/* 1.96875 */	-0.00141f, -0.00140f, -0.00139f, -0.00138f,
		/* 2.00000 */	-0.00138f, -0.00137f, -0.00136f, -0.00135f,
		/* 2.03125 */	-0.00135f, -0.00134f, -0.00133f, -0.00132f,
		/* 2.06250 */	-0.00132f, -0.00131f, -0.00130f, -0.00129f,
		/* 2.09375 */	-0.00129f, -0.00128f, -0.00127f, -0.00126f,
		/* 2.12500 */	-0.00126f, -0.00125f, -0.00124f, -0.00124f,
		/* 2.15625 */	-0.00123f, -0.00122f, -0.00122f, -0.00121f,
		/* 2.18750 */	-0.00120f, -0.00120f, -0.00119f, -0.00119f,
		/* 2.21875 */	-0.00118f, -0.00117f, -0.00117f, -0.00116f,
		/* 2.25000 */	-0.00115f, -0.00115f, -0.00114f, -0.00114f,
		/* 2.28125 */	-0.00113f, -0.00113f, -0.00112f, -0.00111f,
		/* 2.31250 */	-0.00111f, -0.00110f, -0.00110f, -0.00109f,
		/* 2.34375 */	-0.00109f, -0.00108f, -0.00107f, -0.00107f,
		/* 2.37500 */	-0.00107f, -0.00106f, -0.00106f, -0.00105f,
		/* 2.40625 */	-0.00105f, -0.00104f, -0.00103f, -0.00103f,
		/* 2.43750 */	-0.00102f, -0.00102f, -0.00101f, -0.00101f,
		/* 2.46875 */	-0.00100f, -0.00100f, -0.00100f, -0.00099f,
		/* 2.50000 */	-0.00099f, -0.00098f, -0.00098f, -0.00097f,
		/* 2.53125 */	-0.00097f, -0.00096f, -0.00096f, -0.00095f,
		/* 2.56250 */	-0.00095f, -0.00094f, -0.00095f, -0.00093f,
		/* 2.59375 */	-0.00094f, -0.00093f, -0.00092f, -0.00092f,
		/* 2.62500 */	-0.00091f, -0.00091f, -0.00091f, -0.00090f,
		/* 2.65625 */	-0.00090f, -0.00090f, -0.00089f, -0.00089f,
		/* 2.68750 */	-0.00088f, -0.00088f, -0.00088f, -0.00087f,
		/* 2.71875 */	-0.00087f, -0.00086f, -0.00087f, -0.00086f,
		/* 2.75000 */	-0.00086f, -0.00085f, -0.00084f, -0.00085f,
		/* 2.78125 */	-0.00084f, -0.00084f, -0.00083f, -0.00083f,
		/* 2.81250 */	-0.00083f, -0.00082f, -0.00082f, -0.00082f,
		/* 2.84375 */	-0.00081f, -0.00081f, -0.00081f, -0.00080f,
		/* 2.87500 */	-0.00080f, -0.00080f, -0.00079f, -0.00079f,
		/* 2.90625 */	-0.00079f, -0.00078f, -0.00078f, -0.00078f,
		/* 2.93750 */	-0.00078f, -0.00077f, -0.00077f, -0.00077f,
		/* 2.96875 */	-0.00076f, -0.00076f, -0.00076f, -0.00075f,
		/* 3.00000 */	-0.00075f};


#define _hoops_CHSSI		1.0f	/* _hoops_RH _hoops_SRS _hoops_SRRPR _hoops_GGR _hoops_RH _hoops_GASR */
#define _hoops_SHSSI		3.0f	/* _hoops_RH _hoops_CGHI _hoops_SRRPR _hoops_IIH, _hoops_CIGHR _hoops_PSAP _hoops_RH _hoops_RSGR */
#define _hoops_GISSI		(sizeof (_hoops_HHSSI) / sizeof (float))
#define _hoops_RISSI 128.0f /* ((_hoops_AISSI - 1) / (_hoops_PISSI - _hoops_HISSI)) */

#endif

local INLINE bool _hoops_IISSI (
	Vector alter *_hoops_GIHI) {
	float			_hoops_GRAGI, _hoops_RRAGI, _hoops_ARAGI;
	float			length;
	int				_hoops_CISSI;

	/*
	 * _hoops_RAP
	 *	  _hoops_SISSI = |_hoops_GCSPA->_hoops_SISR|
	 *	  _hoops_GCSSI = |_hoops_GCSPA->_hoops_HAPC|
	 *	  _hoops_RCSSI = |_hoops_GCSPA->_hoops_SSH|
	 */
	if (_hoops_GIHI->x >= 0.0f) _hoops_GRAGI = _hoops_GIHI->x;
	else _hoops_GRAGI = -_hoops_GIHI->x;
	if (_hoops_GIHI->y >= 0.0f) _hoops_RRAGI = _hoops_GIHI->y;
	else _hoops_RRAGI = -_hoops_GIHI->y;
	if (_hoops_GIHI->z >= 0.0f) _hoops_ARAGI = _hoops_GIHI->z;
	else _hoops_ARAGI = -_hoops_GIHI->z;

#ifdef DISABLE_TABLE_LOOKUPS
	/* _hoops_HGGC _hoops_RRP _hoops_IS _hoops_PSSSR _hoops_GGSR _hoops_IH _hoops_PGSAH */
	if (_hoops_GRAGI > _hoops_AHSSI) {
		length = _hoops_AHSSI / _hoops_GRAGI;
		_hoops_GRAGI *= length;
		_hoops_RRAGI *= length;
		_hoops_ARAGI *= length;
		_hoops_GIHI->x *= length;
		_hoops_GIHI->y *= length;
		_hoops_GIHI->z *= length;
	}
	if (_hoops_RRAGI > _hoops_AHSSI) {
		length = _hoops_AHSSI / _hoops_RRAGI;
		_hoops_GRAGI *= length;
		_hoops_RRAGI *= length;
		_hoops_ARAGI *= length;
		_hoops_GIHI->x *= length;
		_hoops_GIHI->y *= length;
		_hoops_GIHI->z *= length;
	}
	if (_hoops_ARAGI > _hoops_AHSSI) {
		length = _hoops_AHSSI / _hoops_ARAGI;
		_hoops_GRAGI *= length;
		_hoops_RRAGI *= length;
		_hoops_ARAGI *= length;
		_hoops_GIHI->x *= length;
		_hoops_GIHI->y *= length;
		_hoops_GIHI->z *= length;
	}

	length = _hoops_GRAGI * _hoops_GRAGI  +	 _hoops_RRAGI * _hoops_RRAGI  +	 _hoops_ARAGI * _hoops_ARAGI;

	if (length == 0.0f)
		return false;

	length = 1.0f / sqrt (length);

	_hoops_GIHI->x *= length;
	_hoops_GIHI->y *= length;
	_hoops_GIHI->z *= length;
#else

	if (_hoops_ARAGI < _hoops_RRAGI) {
		if (_hoops_RRAGI < _hoops_GRAGI) {
			/* _hoops_RCSSI < _hoops_GCSSI < _hoops_SISSI */
			if (_hoops_GRAGI <= 1.0e-30) return false;

			_hoops_GRAGI = 1.0f / _hoops_GRAGI;
			_hoops_RRAGI = _hoops_GIHI->y * _hoops_GRAGI;
			_hoops_ARAGI = _hoops_GIHI->z * _hoops_GRAGI;
			_hoops_GRAGI = _hoops_GIHI->x * _hoops_GRAGI; /* _hoops_SPAC _hoops_HSAR _hoops_HHCPR _hoops_HRASR */

			length = (_hoops_RRAGI * _hoops_RRAGI + _hoops_ARAGI * _hoops_ARAGI) * _hoops_RISSI;
		}
		else {
			/* _hoops_RCSSI < _hoops_SISSI < _hoops_GCSSI	 -_hoops_PAR-  _hoops_SISSI < _hoops_RCSSI < _hoops_GCSSI */
			if (_hoops_RRAGI <= 1.0e-30) return false;

			_hoops_RRAGI = 1.0f / _hoops_RRAGI;
			_hoops_GRAGI = _hoops_GIHI->x * _hoops_RRAGI;
			_hoops_ARAGI = _hoops_GIHI->z * _hoops_RRAGI;
			_hoops_RRAGI = _hoops_GIHI->y * _hoops_RRAGI; /* _hoops_SPAC _hoops_HSAR _hoops_HHCPR _hoops_HRASR */

			length = (_hoops_GRAGI * _hoops_GRAGI  + _hoops_ARAGI * _hoops_ARAGI) * _hoops_RISSI;
		}
	}
	else /* _hoops_GCSSI < _hoops_RCSSI */ {
		if (_hoops_ARAGI < _hoops_GRAGI) {
			/* _hoops_GCSSI < _hoops_RCSSI < _hoops_SISSI */
			if (_hoops_GRAGI <= 1.0e-30) return false;

			_hoops_GRAGI = 1.0f / _hoops_GRAGI;
			_hoops_RRAGI = _hoops_GIHI->y * _hoops_GRAGI;
			_hoops_ARAGI = _hoops_GIHI->z * _hoops_GRAGI;
			_hoops_GRAGI = _hoops_GIHI->x * _hoops_GRAGI; /* _hoops_SPAC _hoops_HSAR _hoops_HHCPR _hoops_HRASR */

			length = (_hoops_RRAGI * _hoops_RRAGI + _hoops_ARAGI * _hoops_ARAGI) * _hoops_RISSI;
		}
		else {
			/* _hoops_GCSSI < _hoops_SISSI < _hoops_RCSSI	 -_hoops_PAR-  _hoops_SISSI < _hoops_GCSSI < _hoops_RCSSI */
			if (_hoops_ARAGI <= 1.0e-30) return false;

			_hoops_ARAGI = 1.0f / _hoops_ARAGI;
			_hoops_GRAGI = _hoops_GIHI->x * _hoops_ARAGI;
			_hoops_RRAGI = _hoops_GIHI->y * _hoops_ARAGI;
			_hoops_ARAGI = _hoops_GIHI->z * _hoops_ARAGI; /* _hoops_SPAC _hoops_HSAR _hoops_HHCPR _hoops_HRASR */

			length = (_hoops_GRAGI * _hoops_GRAGI + _hoops_RRAGI * _hoops_RRAGI) * _hoops_RISSI;
		}
	}

	_hoops_CISSI = (int)length;
	length = (length - _hoops_CISSI) * _hoops_IHSSI[_hoops_CISSI] +
		_hoops_HHSSI[_hoops_CISSI];

	_hoops_GIHI->x = _hoops_GRAGI * length;
	_hoops_GIHI->y = _hoops_RRAGI * length;
	_hoops_GIHI->z = _hoops_ARAGI * length;

#endif
	return true;
}

GLOBAL_FUNCTION bool HI_Normalize (
	Vector alter *_hoops_GIHI) {
	return _hoops_IISSI(_hoops_GIHI);
}

GLOBAL_FUNCTION bool HI_Normalize_Vectors (
	int count,
	Vector alter *_hoops_GIHI) {
	bool _hoops_IA = true;

	do {
		_hoops_IA &= _hoops_IISSI(_hoops_GIHI++);
	} while (--count > 0);

	return _hoops_IA;
}


GLOBAL_FUNCTION bool HI_Normalize_Plane (
	_hoops_ARPA alter	*plane) {
	float			_hoops_GRAGI, _hoops_RRAGI, _hoops_ARAGI;
	float			length;
	int				_hoops_CISSI;

	/*
	 * _hoops_RAP
	 *	  _hoops_SISSI = |_hoops_IPPA->_hoops_IRS|
	 *	  _hoops_GCSSI = |_hoops_IPPA->_hoops_RCSR|
	 *	  _hoops_RCSSI = |_hoops_IPPA->_hoops_GSGGR|
	 */
	if (plane->a >= 0.0f) _hoops_GRAGI = plane->a;
	else _hoops_GRAGI = -plane->a;
	if (plane->b >= 0.0f) _hoops_RRAGI = plane->b;
	else _hoops_RRAGI = -plane->b;
	if (plane->c >= 0.0f) _hoops_ARAGI = plane->c;
	else _hoops_ARAGI = -plane->c;


#ifdef DISABLE_TABLE_LOOKUPS
	/* _hoops_HGGC _hoops_RRP _hoops_IS _hoops_PSSSR _hoops_GGSR _hoops_IH _hoops_PGSAH */
	if (_hoops_GRAGI > _hoops_AHSSI) {
		length = _hoops_AHSSI / _hoops_GRAGI;
		_hoops_GRAGI *= length;
		_hoops_RRAGI *= length;
		_hoops_ARAGI *= length;
		plane->a *= length;
		plane->b *= length;
		plane->c *= length;
		plane->d *= length;
	}
	if (_hoops_RRAGI > _hoops_AHSSI) {
		length = _hoops_AHSSI / _hoops_RRAGI;
		_hoops_GRAGI *= length;
		_hoops_RRAGI *= length;
		_hoops_ARAGI *= length;
		plane->a *= length;
		plane->b *= length;
		plane->c *= length;
		plane->d *= length;
	}
	if (_hoops_ARAGI > _hoops_AHSSI) {
		length = _hoops_AHSSI / _hoops_ARAGI;
		_hoops_GRAGI *= length;
		_hoops_RRAGI *= length;
		_hoops_ARAGI *= length;
		plane->a *= length;
		plane->b *= length;
		plane->c *= length;
		plane->d *= length;
	}

	length = _hoops_GRAGI * _hoops_GRAGI  +	 _hoops_RRAGI * _hoops_RRAGI  +	 _hoops_ARAGI * _hoops_ARAGI;

	if (length == 0.0f)
		return false;

	length = 1.0f / sqrt (length);

	plane->a *= length;
	plane->b *= length;
	plane->c *= length;
	plane->d *= length;
#else
	if (_hoops_ARAGI < _hoops_RRAGI) {
		if (_hoops_RRAGI < _hoops_GRAGI) {
			/* _hoops_RCSSI < _hoops_GCSSI < _hoops_SISSI */
			if (_hoops_GRAGI <= 1.0e-30) return false;

			_hoops_GRAGI = 1.0f / _hoops_GRAGI;
			_hoops_RRAGI = plane->b * _hoops_GRAGI;
			_hoops_ARAGI = plane->c * _hoops_GRAGI;
			plane->d *= _hoops_GRAGI;
			_hoops_GRAGI = plane->a * _hoops_GRAGI; /* _hoops_SPAC _hoops_HSAR _hoops_HHCPR _hoops_HRASR */

			length = (_hoops_RRAGI * _hoops_RRAGI + _hoops_ARAGI * _hoops_ARAGI) * _hoops_RISSI;
		}
		else {
			/* _hoops_RCSSI < _hoops_SISSI < _hoops_GCSSI	 -_hoops_PAR-  _hoops_SISSI < _hoops_RCSSI < _hoops_GCSSI */
			if (_hoops_RRAGI <= 1.0e-30) return false;

			_hoops_RRAGI = 1.0f / _hoops_RRAGI;
			_hoops_GRAGI = plane->a * _hoops_RRAGI;
			_hoops_ARAGI = plane->c * _hoops_RRAGI;
			plane->d *= _hoops_RRAGI;
			_hoops_RRAGI = plane->b * _hoops_RRAGI; /* _hoops_SPAC _hoops_HSAR _hoops_HHCPR _hoops_HRASR */

			length = (_hoops_GRAGI * _hoops_GRAGI  + _hoops_ARAGI * _hoops_ARAGI) * _hoops_RISSI;
		}
	}
	else /* _hoops_GCSSI < _hoops_RCSSI */ {
		if (_hoops_ARAGI < _hoops_GRAGI) {
			/* _hoops_GCSSI < _hoops_RCSSI < _hoops_SISSI */
			if (_hoops_GRAGI <= 1.0e-30) return false;

			_hoops_GRAGI = 1.0f / _hoops_GRAGI;
			_hoops_RRAGI = plane->b * _hoops_GRAGI;
			_hoops_ARAGI = plane->c * _hoops_GRAGI;
			plane->d *= _hoops_GRAGI;
			_hoops_GRAGI = plane->a * _hoops_GRAGI; /* _hoops_SPAC _hoops_HSAR _hoops_HHCPR _hoops_HRASR */

			length = (_hoops_RRAGI * _hoops_RRAGI + _hoops_ARAGI * _hoops_ARAGI) * _hoops_RISSI;
		}
		else {
			/* _hoops_GCSSI < _hoops_SISSI < _hoops_RCSSI	 -_hoops_PAR-  _hoops_SISSI < _hoops_GCSSI < _hoops_RCSSI */
			if (_hoops_ARAGI <= 1.0e-30) return false;

			_hoops_ARAGI = 1.0f / _hoops_ARAGI;
			_hoops_GRAGI = plane->a * _hoops_ARAGI;
			_hoops_RRAGI = plane->b * _hoops_ARAGI;
			plane->d *= _hoops_ARAGI;
			_hoops_ARAGI = plane->c * _hoops_ARAGI; /* _hoops_SPAC _hoops_HSAR _hoops_HHCPR _hoops_HRASR */

			length = (_hoops_GRAGI * _hoops_GRAGI + _hoops_RRAGI * _hoops_RRAGI) * _hoops_RISSI;
		}
	}

	_hoops_CISSI = (int)length;
	length = (length - _hoops_CISSI) * _hoops_IHSSI[_hoops_CISSI] +
		_hoops_HHSSI[_hoops_CISSI];

	plane->a = _hoops_GRAGI * length;
	plane->b = _hoops_RRAGI * length;
	plane->c = _hoops_ARAGI * length;
	plane->d *= length;

#endif
	return true;
}

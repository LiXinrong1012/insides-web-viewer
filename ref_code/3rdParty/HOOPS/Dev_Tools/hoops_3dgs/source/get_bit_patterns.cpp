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
 * $Id: obf_tmp.txt 1.46 2010-10-06 19:16:14 jason Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "patterns.h"
#include "hd_proto.h"
#include "hi_proto.h"

#define _hoops_PRSHH(x)			((unsigned short)(x))

local const		unsigned short	_hoops_HRSHH[16] =
									{_hoops_PRSHH(0x0003), _hoops_PRSHH(0x0006), _hoops_PRSHH(0x000C), _hoops_PRSHH(0x0018),
									 _hoops_PRSHH(0x0030), _hoops_PRSHH(0x0060), _hoops_PRSHH(0x00C0), _hoops_PRSHH(0x0180),
									 _hoops_PRSHH(0x0300), _hoops_PRSHH(0x0600), _hoops_PRSHH(0x0C00), _hoops_PRSHH(0x1800),
									 _hoops_PRSHH(0x3000), _hoops_PRSHH(0x6000), _hoops_PRSHH(0xC000), _hoops_PRSHH(0x8001)},
						_hoops_IRSHH[16] =
									{_hoops_PRSHH(0x8001), _hoops_PRSHH(0xC000), _hoops_PRSHH(0x6000), _hoops_PRSHH(0x3000),
									 _hoops_PRSHH(0x1800), _hoops_PRSHH(0x0C00), _hoops_PRSHH(0x0600), _hoops_PRSHH(0x0300),
									 _hoops_PRSHH(0x0180), _hoops_PRSHH(0x00C0), _hoops_PRSHH(0x0060), _hoops_PRSHH(0x0030),
									 _hoops_PRSHH(0x0018), _hoops_PRSHH(0x000C), _hoops_PRSHH(0x0006), _hoops_PRSHH(0x0003)},
						_hoops_CRSHH [16] =
									{_hoops_PRSHH(0x0303), _hoops_PRSHH(0x0303), _hoops_PRSHH(0x0303), _hoops_PRSHH(0x0303),
									 _hoops_PRSHH(0x0303), _hoops_PRSHH(0x0303), _hoops_PRSHH(0x0303), _hoops_PRSHH(0x0303),
									 _hoops_PRSHH(0x0303), _hoops_PRSHH(0x0303), _hoops_PRSHH(0x0303), _hoops_PRSHH(0x0303),
									 _hoops_PRSHH(0x0303), _hoops_PRSHH(0x0303), _hoops_PRSHH(0x0303), _hoops_PRSHH(0x0303)},
						_hoops_SRSHH[16] =
									{_hoops_PRSHH(0xFFFF), _hoops_PRSHH(0xFFFF), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000),
									 _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000),
									 _hoops_PRSHH(0xFFFF), _hoops_PRSHH(0xFFFF), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000),
									 _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000)},
						_hoops_GASHH[16] =
									{_hoops_PRSHH(0xFFFF), _hoops_PRSHH(0x0101), _hoops_PRSHH(0x0101), _hoops_PRSHH(0x0101),
									 _hoops_PRSHH(0x0101), _hoops_PRSHH(0x0101), _hoops_PRSHH(0x0101), _hoops_PRSHH(0x0101),
									 _hoops_PRSHH(0xFFFF), _hoops_PRSHH(0x0101), _hoops_PRSHH(0x0101), _hoops_PRSHH(0x0101),
									 _hoops_PRSHH(0x0101), _hoops_PRSHH(0x0101), _hoops_PRSHH(0x0101), _hoops_PRSHH(0x0101)},
						_hoops_RASHH[16] =
									{_hoops_PRSHH(0x8001), _hoops_PRSHH(0x4002), _hoops_PRSHH(0x2004), _hoops_PRSHH(0x1008),
									 _hoops_PRSHH(0x0810), _hoops_PRSHH(0x0420), _hoops_PRSHH(0x0240), _hoops_PRSHH(0x0180),
									 _hoops_PRSHH(0x0180), _hoops_PRSHH(0x0240), _hoops_PRSHH(0x0420), _hoops_PRSHH(0x0810),
									 _hoops_PRSHH(0x1008), _hoops_PRSHH(0x2004), _hoops_PRSHH(0x4002), _hoops_PRSHH(0x8001)},
						_hoops_AASHH[16] =
									{_hoops_PRSHH(0x0303), _hoops_PRSHH(0x0303), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000),
									 _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000),
									 _hoops_PRSHH(0x0303), _hoops_PRSHH(0x0303), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000),
									 _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000)},
						_hoops_PASHH[16] =
									{_hoops_PRSHH(0x00FF), _hoops_PRSHH(0x0081), _hoops_PRSHH(0x0081), _hoops_PRSHH(0x0081),
									 _hoops_PRSHH(0x0081), _hoops_PRSHH(0x0081), _hoops_PRSHH(0x0081), _hoops_PRSHH(0x00FF),
									 _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000),
									 _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000)},
						_hoops_HASHH[16] =
									{_hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000),
									 _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000),
									 _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000),
									 _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000)},
						_hoops_IASHH[16] =
									{_hoops_PRSHH(0x0101), _hoops_PRSHH(0x0202), _hoops_PRSHH(0x0404), _hoops_PRSHH(0x0808),
									 _hoops_PRSHH(0x1010), _hoops_PRSHH(0x2020), _hoops_PRSHH(0x4040), _hoops_PRSHH(0x8080),
									 _hoops_PRSHH(0x0101), _hoops_PRSHH(0x0202), _hoops_PRSHH(0x0404), _hoops_PRSHH(0x0808),
									 _hoops_PRSHH(0x1010), _hoops_PRSHH(0x2020), _hoops_PRSHH(0x4040), _hoops_PRSHH(0x8080)},
						_hoops_CASHH[16] =
									{_hoops_PRSHH(0x8080), _hoops_PRSHH(0x4040), _hoops_PRSHH(0x2020), _hoops_PRSHH(0x1010),
									 _hoops_PRSHH(0x0808), _hoops_PRSHH(0x0404), _hoops_PRSHH(0x0202), _hoops_PRSHH(0x0101),
									 _hoops_PRSHH(0x8080), _hoops_PRSHH(0x4040), _hoops_PRSHH(0x2020), _hoops_PRSHH(0x1010),
									 _hoops_PRSHH(0x0808), _hoops_PRSHH(0x0404), _hoops_PRSHH(0x0202), _hoops_PRSHH(0x0101)},
						_hoops_SASHH[16] =
									{_hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111),
									 _hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111),
									 _hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111),
									 _hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111)},
						_hoops_GPSHH[16] =
									{_hoops_PRSHH(0xFFFF), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000),
									 _hoops_PRSHH(0xFFFF), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000),
									 _hoops_PRSHH(0xFFFF), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000),
									 _hoops_PRSHH(0xFFFF), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000)},
						_hoops_RPSHH[16] =
									{_hoops_PRSHH(0xFFFF), _hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111),
									 _hoops_PRSHH(0xFFFF), _hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111),
									 _hoops_PRSHH(0xFFFF), _hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111),
									 _hoops_PRSHH(0xFFFF), _hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111), _hoops_PRSHH(0x1111)},
						_hoops_APSHH[16] =
									{_hoops_PRSHH(0x8181), _hoops_PRSHH(0x4242), _hoops_PRSHH(0x2424), _hoops_PRSHH(0x1818),
									 _hoops_PRSHH(0x1818), _hoops_PRSHH(0x2424), _hoops_PRSHH(0x4242), _hoops_PRSHH(0x8181),
									 _hoops_PRSHH(0x8181), _hoops_PRSHH(0x4242), _hoops_PRSHH(0x2424), _hoops_PRSHH(0x1818),
									 _hoops_PRSHH(0x1818), _hoops_PRSHH(0x2424), _hoops_PRSHH(0x4242), _hoops_PRSHH(0x8181)},
						_hoops_PPSHH[16] =
									{_hoops_PRSHH(0x1111), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000),
									 _hoops_PRSHH(0x1111), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000),
									 _hoops_PRSHH(0x1111), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000),
									 _hoops_PRSHH(0x1111), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000)},
						_hoops_HPSHH[16] =
									{_hoops_PRSHH(0x0F0F), _hoops_PRSHH(0x0909), _hoops_PRSHH(0x0909), _hoops_PRSHH(0x0F0F),
									 _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000),
									 _hoops_PRSHH(0x0F0F), _hoops_PRSHH(0x0909), _hoops_PRSHH(0x0909), _hoops_PRSHH(0x0F0F),
									 _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000), _hoops_PRSHH(0x0000)};


GLOBAL_FUNCTION void HD_Get_Bit_Patterns (
	Display_Context alter	*dc,
	bool					_hoops_CIPAR) {
	int							_hoops_CGCIR;

	dc->_hoops_GRPH[FP_SOLID] = _hoops_HASHH;
	dc->_hoops_GRPH[FP_CHECKERBOARD] = _hoops_PASHH;
	dc->_hoops_GRPH[FP_CROSSHATCH] = _hoops_GASHH;
	dc->_hoops_GRPH[FP_DIAMONDS] = _hoops_RASHH;
	dc->_hoops_GRPH[FP_HORIZONTAL_BARS] = _hoops_SRSHH;
	dc->_hoops_GRPH[FP_SQUARE_DOTS] = _hoops_AASHH;
	dc->_hoops_GRPH[FP_VERTICAL_BARS] = _hoops_CRSHH;
	dc->_hoops_GRPH[FP_WINDOW_CHECKERBOARD] = _hoops_HPSHH;
	dc->_hoops_GRPH[FP_WINDOW_CROSSHATCH] = _hoops_RPSHH;
	dc->_hoops_GRPH[FP_WINDOW_DIAMONDS] = _hoops_APSHH;
	dc->_hoops_GRPH[FP_WINDOW_HORIZONTAL_BARS] = _hoops_GPSHH;
	dc->_hoops_GRPH[FP_WINDOW_SQUARE_DOTS] = _hoops_PPSHH;
	dc->_hoops_GRPH[FP_WINDOW_VERTICAL_BARS] = _hoops_SASHH;
	dc->_hoops_GRPH[FP_WINDOW_TRANSPARENT] = _hoops_APSHH;

	if (!_hoops_CIPAR) {
		/* _hoops_GSSR _hoops_AGIR _hoops_HRGR _hoops_RAAP-_hoops_IS-_hoops_RPHR, _hoops_SCIA-_hoops_IS-_hoops_PRPC... */

		dc->_hoops_GRPH[FP_SLANT_LEFT] = _hoops_IRSHH;
		dc->_hoops_GRPH[FP_SLANT_RIGHT] = _hoops_HRSHH;
		dc->_hoops_GRPH[FP_WINDOW_SLANT_LEFT] = _hoops_CASHH;
		dc->_hoops_GRPH[FP_WINDOW_SLANT_RIGHT] = _hoops_IASHH;
	}
	else {
		dc->_hoops_GRPH[FP_SLANT_LEFT] = _hoops_HRSHH;
		dc->_hoops_GRPH[FP_SLANT_RIGHT] = _hoops_IRSHH;
		dc->_hoops_GRPH[FP_WINDOW_SLANT_LEFT] = _hoops_IASHH;
		dc->_hoops_GRPH[FP_WINDOW_SLANT_RIGHT] = _hoops_CASHH;
	}


	if (HOOPS_WORLD->_hoops_IPSHH == null) {
		unsigned short alter	*_hoops_CPSHH;
		int						_hoops_AISRP[8][8];
		int						row, col;

		/*
		 *	_hoops_IPCP _hoops_SPS _hoops_HAPR _hoops_GPISP _hoops_RH _hoops_SPSHH _hoops_PISRP _hoops_GASR, _hoops_GAR _hoops_SPCP:
		 *	 _hoops_IRGH _hoops_RCIC		_hoops_SCSH		_hoops_PISRP[8][8] = {
		 *		  { 0,	48,	 12,  60,	3,	51,	 15,  63},
		 *		  {32,	16,	 44,  28,  35,	19,	 47,  31},
		 *		  { 8,	56,	  4,  52,  11,	59,	  7,  55},
		 *		  {40,	24,	 36,  20,  43,	27,	 39,  23},
		 *		  { 2,	50,	 14,  62,	1,	49,	 13,  61},
		 *		  {34,	18,	 46,  30,  33,	17,	 45,  29},
		 *		  {10,	58,	  6,  54,	9,	57,	  5,  53},
		 *		  {42,	26,	 38,  22,  41,	25,	 37,  21}
		 *	 };
		 */
		for (row = 0; row < 8; ++row)
			for (col = 0; col < 8; ++col) {
				int		x = col, y = row, _hoops_CPGCR;

				_hoops_CPGCR = (				(x & 1 ^ y & 1)) << 1 | y & 1; x >>= 1; y >>= 1;
				_hoops_CPGCR = (_hoops_CPGCR << 1 | (x & 1 ^ y & 1)) << 1 | y & 1; x >>= 1; y >>= 1;
				_hoops_CPGCR = (_hoops_CPGCR << 1 | (x & 1 ^ y & 1)) << 1 | y & 1;

				_hoops_AISRP[row][col] = _hoops_CPGCR;
		}

		/* _hoops_CCPP _hoops_RH _hoops_CCAH _hoops_SPSHH _hoops_PAIA */
		ALLOC_ARRAY (_hoops_CPSHH, 16L * _hoops_SPRSP, unsigned short);
		HOOPS_WORLD->_hoops_IPSHH = _hoops_CPSHH;

		/* _hoops_GRAS _hoops_RH _hoops_PAIA _hoops_IIHA _hoops_GPP _hoops_RH _hoops_GHSHH */
		_hoops_CGCIR = 0;
		do {
			for (row = 0; row < 16; ++row) {
				unsigned short _hoops_RHSHH = 0;
				for (col = 0; col < 16; ++col) {
					_hoops_RHSHH <<= 1;
					if (_hoops_CGCIR > _hoops_AISRP[row & 7][col & 7])
						_hoops_RHSHH |= 1;
				}
				*_hoops_CPSHH++ = _hoops_RHSHH;
			}
		} _hoops_RGGA (++_hoops_CGCIR > _hoops_SPRSP-1);
	}

	_hoops_CGCIR = _hoops_SPRSP - 1;
	do dc->_hoops_GRPH[_hoops_CGCIR + _hoops_CPRSP] =
		&(HOOPS_WORLD->_hoops_IPSHH[_hoops_CGCIR*16]);
	_hoops_RGGA (--_hoops_CGCIR < 0);

	dc->_hoops_ASPGH = 16;
	dc->_hoops_CCAGH = _hoops_CIPAR;
}


/*
 * _hoops_IPCP '1' _hoops_SIH _hoops_ISPCA _hoops_IS _hoops_PGS _hoops_ASPA, '0' _hoops_IS _hoops_APRP. _hoops_IPCP _hoops_PPSCP
 * _hoops_SAGGR _hoops_AHSHH _hoops_ISHP _hoops_GAR _hoops_HPS, _hoops_PHAP _hoops_CCA _hoops_RH _hoops_PHSHH _hoops_IGRH _hoops_GGR _hoops_RH
 * _hoops_HISAR-_hoops_AGR _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_RAPSR.
 *
 * _hoops_HHIGR _hoops_CHH _hoops_SHH _hoops_AGAPR _hoops_IS _hoops_HHSHH _hoops_RGCPR _hoops_APRP-_hoops_PPR-_hoops_PGS _hoops_RRRH _hoops_GGR
 * _hoops_RRGR _hoops_SGS _hoops_ASSP'_hoops_RA _hoops_SHAC _hoops_CCA _hoops_RH _hoops_CSGRH. (_hoops_IHSHH)
 */

local const unsigned char
		_hoops_CHSHH[8] =
				{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80},
		_hoops_SHSHH[8] =
				{0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01},
		_hoops_GISHH[8] =
				{0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10},
		_hoops_RISHH[8]=
				{0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00},
		_hoops_AISHH[8] =
				{0x10, 0x10, 0x10, 0x10, 0xFF, 0x10, 0x10, 0x10},
		_hoops_PISHH[8] =
				{0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81},
		_hoops_HISHH[8] =
				{0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00},
		_hoops_IISHH[8] =
				{0x0F, 0x09, 0x09, 0x0F, 0x00, 0x00, 0x00, 0x00},
		_hoops_CISHH[8] =
				{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		_hoops_SISHH[8] =
				{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80},
		_hoops_GCSHH[8] =
				{0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01},
		_hoops_RCSHH[8] =
				{0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11},
		_hoops_ACSHH[8] =
				{0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00},
		_hoops_PCSHH[8] =
				{0xFF, 0x11, 0x11, 0x11, 0xFF, 0x11, 0x11, 0x11},
		_hoops_HCSHH[8] =
				{0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81},
		_hoops_ICSHH[8] =
				{0x11, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00},
		_hoops_CCSHH[8] =
				{0x0F, 0x09, 0x09, 0x0F, 0x00, 0x00, 0x00, 0x00};


GLOBAL_FUNCTION void HD_Get_Bit_Patterns_8 (
	Display_Context alter	*dc,
	bool					_hoops_CIPAR) {
	int							_hoops_CGCIR;

	dc->_hoops_GRPH[FP_SOLID] = (unsigned short const *)_hoops_CISHH;
	dc->_hoops_GRPH[FP_CHECKERBOARD] = (unsigned short const *)_hoops_IISHH;
	dc->_hoops_GRPH[FP_CROSSHATCH] = (unsigned short const *)_hoops_AISHH;
	dc->_hoops_GRPH[FP_DIAMONDS] = (unsigned short const *)_hoops_PISHH;
	dc->_hoops_GRPH[FP_HORIZONTAL_BARS] = (unsigned short const *)_hoops_RISHH;
	dc->_hoops_GRPH[FP_SQUARE_DOTS] = (unsigned short const *)_hoops_HISHH;
	dc->_hoops_GRPH[FP_VERTICAL_BARS] = (unsigned short const *)_hoops_GISHH;
	dc->_hoops_GRPH[FP_WINDOW_CHECKERBOARD] = (unsigned short const *)_hoops_CCSHH;
	dc->_hoops_GRPH[FP_WINDOW_CROSSHATCH] = (unsigned short const *)_hoops_PCSHH;
	dc->_hoops_GRPH[FP_WINDOW_DIAMONDS] = (unsigned short const *)_hoops_HCSHH;
	dc->_hoops_GRPH[FP_WINDOW_HORIZONTAL_BARS] = (unsigned short const *)_hoops_ACSHH;
	dc->_hoops_GRPH[FP_WINDOW_SQUARE_DOTS] = (unsigned short const *)_hoops_ICSHH;
	dc->_hoops_GRPH[FP_WINDOW_VERTICAL_BARS] = (unsigned short const *)_hoops_RCSHH;
	dc->_hoops_GRPH[FP_WINDOW_TRANSPARENT] = (unsigned short const *)_hoops_HCSHH;

	if (!_hoops_CIPAR) {
		/* _hoops_GSSR _hoops_AGIR _hoops_HRGR _hoops_RAAP-_hoops_IS-_hoops_RPHR, _hoops_SCIA-_hoops_IS-_hoops_PRPC... */

		dc->_hoops_GRPH[FP_SLANT_LEFT] = (unsigned short const *)_hoops_SHSHH;
		dc->_hoops_GRPH[FP_SLANT_RIGHT] = (unsigned short const *)_hoops_CHSHH;
		dc->_hoops_GRPH[FP_WINDOW_SLANT_LEFT] = (unsigned short const *)_hoops_GCSHH;
		dc->_hoops_GRPH[FP_WINDOW_SLANT_RIGHT] = (unsigned short const *)_hoops_SISHH;
	}
	else {
		dc->_hoops_GRPH[FP_SLANT_LEFT] = (unsigned short const *)_hoops_CHSHH;
		dc->_hoops_GRPH[FP_SLANT_RIGHT] = (unsigned short const *)_hoops_SHSHH;
		dc->_hoops_GRPH[FP_WINDOW_SLANT_LEFT] = (unsigned short const *)_hoops_SISHH;
		dc->_hoops_GRPH[FP_WINDOW_SLANT_RIGHT] = (unsigned short const *)_hoops_GCSHH;
	}

	if (HOOPS_WORLD->_hoops_SCSHH == null) {
		unsigned char alter *_hoops_CPSHH;
		int					_hoops_AISRP[8][8];
		int					row, col;

		/*
		 *	_hoops_IPCP _hoops_SPS _hoops_HAPR _hoops_GPISP _hoops_RH _hoops_SPSHH _hoops_PISRP _hoops_GASR, _hoops_GAR _hoops_SPCP:
		 *	 _hoops_IRGH _hoops_RCIC		_hoops_SCSH		_hoops_PISRP[8][8] = {
		 *		  { 0,	48,	 12,  60,	3,	51,	 15,  63},
		 *		  {32,	16,	 44,  28,  35,	19,	 47,  31},
		 *		  { 8,	56,	  4,  52,  11,	59,	  7,  55},
		 *		  {40,	24,	 36,  20,  43,	27,	 39,  23},
		 *		  { 2,	50,	 14,  62,	1,	49,	 13,  61},
		 *		  {34,	18,	 46,  30,  33,	17,	 45,  29},
		 *		  {10,	58,	  6,  54,	9,	57,	  5,  53},
		 *		  {42,	26,	 38,  22,  41,	25,	 37,  21}
		 *	 };
		 */
		for (row = 0; row < 8; ++row)
			for (col = 0; col < 8; ++col) {
				int		x = col, y = row, _hoops_CPGCR;

				_hoops_CPGCR = (				(x & 1 ^ y & 1)) << 1 | y & 1; x >>= 1; y >>= 1;
				_hoops_CPGCR = (_hoops_CPGCR << 1 | (x & 1 ^ y & 1)) << 1 | y & 1; x >>= 1; y >>= 1;
				_hoops_CPGCR = (_hoops_CPGCR << 1 | (x & 1 ^ y & 1)) << 1 | y & 1;

				_hoops_AISRP[row][col] = _hoops_CPGCR;
		}

		/* _hoops_CCPP _hoops_RH _hoops_CCAH _hoops_SPSHH _hoops_PAIA */
		ALLOC_ARRAY (_hoops_CPSHH, 8L * _hoops_SPRSP, unsigned char);
		HOOPS_WORLD->_hoops_SCSHH = _hoops_CPSHH;

		/* _hoops_GRAS _hoops_RH _hoops_PAIA _hoops_IIHA _hoops_GPP _hoops_RH _hoops_GHSHH */
		_hoops_CGCIR = 0;
		do {
			for (row = 0; row < 8; ++row) {
				unsigned char _hoops_RHSHH = 0;
				for (col = 0; col < 8; ++col) {
					_hoops_RHSHH <<= 1;
					if (_hoops_CGCIR > _hoops_AISRP[row][col])
						_hoops_RHSHH |= 1;
				}
				*_hoops_CPSHH++ = _hoops_RHSHH;
			}
		} _hoops_RGGA (++_hoops_CGCIR > _hoops_SPRSP-1);
	}

	_hoops_CGCIR = _hoops_SPRSP - 1;
	do dc->_hoops_GRPH[_hoops_CGCIR + _hoops_CPRSP] =
		(unsigned short const *)&(HOOPS_WORLD->_hoops_SCSHH[_hoops_CGCIR*8]);
	_hoops_RGGA (--_hoops_CGCIR < 0);

	dc->_hoops_ASPGH = 8;
	dc->_hoops_CCAGH = _hoops_CIPAR;
}

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
 * $Id: obf_tmp.txt 1.32 2009-10-23 23:04:24 trask Exp $
 */

#include "hoops.h"
#include "hi_proto.h"
#include <math.h>
#include <stdlib.h>


#define _hoops_ICHPH _hoops_GGAPR (_hoops_CCHPH)

static char const *_hoops_CCHPH[] = {
	   /* 000 */  "",
	   /* 001 */  "",
	   /* 002 */  "\1\1 ",
	   /* 003 */  "\1\1 \1\2 ",
	   /* 004 */  "\1\1 \2\2 ",
	   /* 005 */  "\1\1 \1\2 \2\3 ",
	   /* 006 */  "\1\1 \1\2 \3\3 ",
	   /* 007 */  "\1\1 \1\2 \2\3 \2\4 ",
	   /* 008 */  "\1\1 \2\2 \3\3 ",
	   /* 009 */  "\1\1 \2\2 \3\3 \4\1 ",
	   /* 010 */  "\1\1 \1\2 \2\3 \4\4 ",
	   /* 011 */  "\1\1 \1\2 \2\3 \4\4 \5\1 ",
	   /* 012 */  "\1\1 \1\2 \3\3 \4\4 ",
	   /* 013 */  "\1\1 \2\2 \3\3 \4\1 \5\3 ",
	   /* 014 */  "\1\1 \1\2 \2\3 \2\4 \5\5 ",
	   /* 015 */  "\1\1 \1\2 \3\3 \4\4 \5\3 ",
	   /* 016 */  "\1\1 \2\2 \3\3 \4\4 ",
	   /* 017 */  "\1\1 \2\2 \3\3 \4\1 \5\1 ",
	   /* 018 */  "\1\1 \2\2 \3\3 \4\4 \5\2 ",
	   /* 019 */  "\1\1 \2\1 \3\2 \4\2 \5\5 \6\4 ",
	   /* 020 */  "\1\1 \2\1 \3\2 \4\4 \5\5 ",
	   /* 021 */  "\1\1 \2\1 \3\2 \4\4 \5\1 \6\5 ",
	   /* 022 */  "\1\1 \2\1 \3\2 \4\4 \5\1 \6\6 ",
	   /* 023 */  "\1\1 \2\1 \3\2 \4\4 \5\5 \6\3 ",
	   /* 024 */  "\1\1 \2\1 \3\3 \4\4 \5\5 ",
	   /* 025 */  "\1\1 \2\1 \3\3 \4\4 \5\5 \6\1 ",
	   /* 026 */  "\1\1 \2\2 \3\3 \4\1 \5\3 \6\6 ",
	   /* 027 */  "\1\1 \2\1 \3\3 \4\4 \5\3 \6\5 ",
	   /* 028 */  "\1\1 \2\1 \3\2 \4\2 \5\5 \6\6 ",
	   /* 029 */  "\1\1 \2\1 \3\2 \4\2 \5\5 \6\6 \7\1 ",
	   /* 030 */  "\1\1 \2\1 \3\3 \4\4 \5\3 \6\6 ",
};



GLOBAL_FUNCTION float HI_Exponentiate (
	float			_hoops_SHGCR,
	float			_hoops_SCHPH) {
	int				_hoops_GSHPH;

	if (_hoops_SCHPH == 0.0f) return 1.0f;
	if (_hoops_SCHPH == 1.0f) return _hoops_SHGCR;
	if (_hoops_SHGCR == 0.0f) {
		if (_hoops_SCHPH < 0.0f)
			return MAX_FLOAT;
		else
			return 0.0f;
	}

	_hoops_GSHPH = (int)_hoops_SCHPH;
	if (_hoops_SCHPH == (float)_hoops_GSHPH &&
		_hoops_GSHPH > 0 &&
		_hoops_GSHPH < _hoops_ICHPH) {
		float			_hoops_CGHCA[10];
		char const		*_hoops_CIPPH;
		float			*_hoops_RSHPH = &_hoops_CGHCA[1];

		_hoops_CIPPH = _hoops_CCHPH[_hoops_GSHPH];

		*_hoops_RSHPH = _hoops_SHGCR;
		while (*_hoops_CIPPH) {
			*++_hoops_RSHPH = _hoops_CGHCA[(int)_hoops_CIPPH[0]] * _hoops_CGHCA[(int)_hoops_CIPPH[1]];
			_hoops_CIPPH += 3; /* _hoops_IRIIP _hoops_SGGP _hoops_PSPI, _hoops_PPR _hoops_ASHPH _hoops_PSHPH */
		}
		return *_hoops_RSHPH;
	}
	else
		return (float)pow (_hoops_SHGCR, _hoops_SCHPH);
}

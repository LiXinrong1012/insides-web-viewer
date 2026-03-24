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
 * $Id: obf_tmp.txt 1.47 2010-10-06 19:16:43 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "path.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


#ifndef DISABLE_SHOW

local const char	_hoops_GSGHS[] = "Return string won't fit in provided space; truncated";


local char * _hoops_RSGHS (
	_hoops_AIGPR *	_hoops_RIGC,
	char *					_hoops_ASAPR,
	char *					_hoops_PSAPR) 
{
	_hoops_CRCP *	_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_PCRIR;
	_hoops_ASAPR = HI_Sprintf1 ((_hoops_ASAPR), (_hoops_PSAPR), "%p", (void *)_hoops_SRCP);
	if (_hoops_ASAPR == null) {
		HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_GSGHS);
		return null;
	}
	else
		return _hoops_ASAPR;
}


local char * _hoops_CCAPR (
	char const		*in,
	char			*_hoops_PAGR,
	int				len) 
{
	while (len-- > 0) 
		*_hoops_PAGR++ = *in++;
	return _hoops_PAGR;
}


local char *_hoops_HRIGP (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_RSAPR *			_hoops_CIPPR,
	char *					_hoops_ASAPR,
	char *					_hoops_PSAPR,
	bool					_hoops_ASGHS) {
	char *					start = _hoops_ASAPR;

	while (_hoops_CIPPR != null) {
		switch (_hoops_CIPPR->type) {
			case _hoops_ISAPR:
				if (_hoops_ASGHS) {
					HE_ERROR (HEC_SEGMENT, HES_INVALID_REFERENCE,
							"Cannot reference current segment in this context");
					return null;
				}
				_hoops_ASGHS = true;
				_hoops_ASAPR = _hoops_RSGHS (_hoops_RIGC, _hoops_ASAPR, _hoops_PSAPR);
				break;
			case _hoops_HSAPR:
				if (!_hoops_ASGHS)
					_hoops_ASAPR = _hoops_RSGHS (_hoops_RIGC, _hoops_ASAPR, _hoops_PSAPR);
				if (_hoops_PSAPR - _hoops_ASAPR < 3) {
					HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_GSGHS);
					return null;
				}
				_hoops_ASAPR = _hoops_CCAPR ("...", _hoops_ASAPR, 3);
				break;
			case _hoops_PGRHH:
				if (!_hoops_ASGHS)
					_hoops_ASAPR = _hoops_RSGHS (_hoops_RIGC, _hoops_ASAPR, _hoops_PSAPR);
				if (_hoops_PSAPR - _hoops_ASAPR < 4) {
					HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_GSGHS);
					return null;
				}
				_hoops_ASAPR = _hoops_CCAPR ("....", _hoops_ASAPR, 4);
				break;
			case _hoops_SSAPR:
				if (!_hoops_ASGHS) 
					_hoops_ASAPR = _hoops_RSGHS (_hoops_RIGC, _hoops_ASAPR, _hoops_PSAPR);
				if (_hoops_ASAPR == _hoops_PSAPR) {
					HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_GSGHS);
					return null;
				}
				*_hoops_ASAPR++ = '%';
				break;
			case _hoops_CSAPR:
				_hoops_ASGHS = true;
				if (_hoops_ASAPR == _hoops_PSAPR) {
					HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_GSGHS);
					return null;
				}
				if (_hoops_ASAPR == start || *(_hoops_ASAPR - 1) != '/')	/* _hoops_PSGHS // */
					*_hoops_ASAPR++ = '/';
				break;
			case _hoops_GGPPR:
				if (! _hoops_ASGHS)
					_hoops_ASAPR = _hoops_RSGHS (_hoops_RIGC, _hoops_ASAPR, _hoops_PSAPR);
				if (_hoops_ASAPR != start + 1) --_hoops_ASAPR;
				do --_hoops_ASAPR;
				_hoops_RGGA (_hoops_ASAPR == start || *_hoops_ASAPR == '/');
				if (_hoops_ASAPR == start) *_hoops_ASAPR++ = '/';
				break;
			case _hoops_RGPPR:
				_hoops_ASAPR = _hoops_HRIGP (_hoops_RIGC, _hoops_CIPPR->expansion, _hoops_ASAPR, _hoops_PSAPR, _hoops_ASGHS);
				break;
			case _hoops_SGPPR:
				if (!_hoops_ASGHS) 
					_hoops_ASAPR = _hoops_RSGHS (_hoops_RIGC, _hoops_ASAPR, _hoops_PSAPR);
				if (_hoops_ASAPR == _hoops_PSAPR) {
					HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_GSGHS);
					return null;
				}
				*_hoops_ASAPR++ = ',';
				break;
			case _hoops_GRPPR:
				if (!_hoops_ASGHS) 
					_hoops_ASAPR = _hoops_RSGHS (_hoops_RIGC, _hoops_ASAPR, _hoops_PSAPR);
				if (_hoops_ASAPR == _hoops_PSAPR) {
					HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_GSGHS);
					return null;
				}
				*_hoops_ASAPR++ = '(';
				break;
			case _hoops_RRPPR:
				if (!_hoops_ASGHS) 
					_hoops_ASAPR = _hoops_RSGHS (_hoops_RIGC, _hoops_ASAPR, _hoops_PSAPR);
				if (_hoops_ASAPR == _hoops_PSAPR) {
					HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_GSGHS);
					return null;
				}
				*_hoops_ASAPR++ = ')';
				break;
			case _hoops_ARPPR:
				if (! _hoops_ASGHS) {
					_hoops_ASAPR = _hoops_RSGHS (_hoops_RIGC, _hoops_ASAPR, _hoops_PSAPR);
					if (_hoops_ASAPR == _hoops_PSAPR) {
						HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_GSGHS);
						return null;
					}
					else *_hoops_ASAPR++ = '/';
				}
				if (_hoops_PSAPR - _hoops_ASAPR < _hoops_CIPPR->_hoops_AGPPR.length) {
					HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_GSGHS);
					return null;
				}
				_hoops_ASAPR = _hoops_CCAPR (_hoops_CIPPR->_hoops_AGPPR.text, _hoops_ASAPR, _hoops_CIPPR->_hoops_AGPPR.length);
				break;
			case _hoops_PRPPR:
				if (!_hoops_ASGHS) 
					_hoops_ASAPR = _hoops_RSGHS (_hoops_RIGC, _hoops_ASAPR, _hoops_PSAPR);
				if (_hoops_ASAPR == _hoops_PSAPR) {
					HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_GSGHS);
					return null;
				}
				*_hoops_ASAPR++ = '*';
				break;
			case _hoops_HRPPR:
				if (! _hoops_ASGHS) {
					_hoops_ASAPR = _hoops_RSGHS (_hoops_RIGC, _hoops_ASAPR, _hoops_PSAPR);
					if (_hoops_ASAPR == _hoops_PSAPR) {
						HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_GSGHS);
						return null;
					}
					else *_hoops_ASAPR++ = '/';
				}
				if (_hoops_PSAPR - _hoops_ASAPR < 9) {
					HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_GSGHS);
					return null;
				}
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%k", (void *)&_hoops_CIPPR->key);
				break;
			default:
				HE_ERROR (HEC_SEGMENT, HES_INVALID_PATH_TOKEN,
						"Undefined path token type");
				return null;
		}
		_hoops_CIPPR = _hoops_CIPPR->next;
	}
	return _hoops_ASAPR;
}
#endif


HC_INTERFACE void HC_CDECL HC_Show_Pathname_Expansion (
	char const *	_hoops_HSGHS,
	char *			expansion)
{
	_hoops_PAPPR context("Show_Pathname_Expansion");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Pathname_Expansion () */\n");
	);

	char			*_hoops_ASAPR, *_hoops_PSAPR;

	_hoops_RSAPR * _hoops_CIPPR = HI_Parse_Path (context, _hoops_HSGHS, _hoops_RPPSA);
	if (_hoops_CIPPR == null) return;

		_hoops_PSAPR = expansion + HOOPS_WORLD->_hoops_RAPPR - 1;

		if ((_hoops_ASAPR = _hoops_HRIGP (context,_hoops_CIPPR, expansion, _hoops_PSAPR, false)) == null)
			_hoops_ASAPR = expansion; /* _hoops_ISGHS */

		*_hoops_ASAPR = '\0';
	
	HI_Free_Path (_hoops_CIPPR);
#endif
}



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
 * $Id: obf_tmp.txt 1.81 2010-11-18 00:59:02 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


/* _hoops_HGI _hoops_PIRA _hoops_HRGR _hoops_SHHA _hoops_IS _hoops_SHH _hoops_HAGH _hoops_HSAR _hoops_HCR _hoops_RH _hoops_APRPS _hoops_HSH! */
#define _hoops_PPRPS				-1

/* (_hoops_HRPAI _hoops_GGR _hoops_AGR _hoops_IIGR _hoops_SISRP) */
local const _hoops_IGRCR _hoops_HPRPS[] = {
	{_hoops_IAHGP, _hoops_GRRCR("on"),				_hoops_RRRCR, 0, false},
	{_hoops_PPRPS,					_hoops_GRRCR("off"),			_hoops_RRRCR, 0, false},
	{_hoops_PPRPS,					_hoops_GRRCR("nothing"),		_hoops_RRRCR, 0, false},

	{_hoops_IAHGP, _hoops_GRRCR("everything"),		_hoops_ARSAP, 1, true},
	{_hoops_RAHGP, _hoops_GRRCR("geometry"),		_hoops_ARSAP, 1, true},
	{T_ANY_EDGE,				_hoops_GRRCR("edge"),			_hoops_ARSAP, 1, true},
	{T_FACES,					_hoops_GRRCR("face"),			_hoops_ARSAP, 1, true},
	{T_ANY_LIGHTS,				_hoops_GRRCR("light"),			_hoops_ARSAP, 1, true},
	{T_LINES,					_hoops_GRRCR("line"),			_hoops_ARSAP, 1, true},
	{T_LINES,					_hoops_GRRCR("polyline"),		_hoops_ARSAP, 1, true},
	{T_MARKERS,					_hoops_GRRCR("marker only"),	_hoops_ARSAP, 1, true},
	{T_VERTICES,				_hoops_GRRCR("vertex"),			_hoops_ARSAP, 1, true},
	{T_MARKERS|T_VERTICES,		_hoops_GRRCR("marker"),			_hoops_ARSAP, 1, true},
	{T_IMAGES,					_hoops_GRRCR("image"),			_hoops_ARSAP, 1, true},
	{T_IMAGES,					_hoops_GRRCR("pixel array"),	_hoops_ARSAP, 1, true},
	{T_FACES|T_ANY_EDGE,		_hoops_GRRCR("polygon"),		_hoops_ARSAP, 1, true},
	{T_STRING_CURSORS,			_hoops_GRRCR("string cursor"),	_hoops_ARSAP, 1, true},
	{T_TEXT,					_hoops_GRRCR("text"),			_hoops_ARSAP, 1, true},
	{T_WINDOWS,					_hoops_GRRCR("window"),			_hoops_ARSAP, 1, true},
	{_hoops_GPA,				_hoops_GRRCR("isoline"),		_hoops_ARSAP, 1, true},

	{T_ANY_EDGE,				_hoops_GRRCR("edges"),			_hoops_ARSAP, 1, true},
	{T_FACES,					_hoops_GRRCR("faces"),			_hoops_ARSAP, 1, true},
	{T_ANY_LIGHTS,				_hoops_GRRCR("lights"),			_hoops_ARSAP, 1, true},
	{T_LINES,					_hoops_GRRCR("lines"),			_hoops_ARSAP, 1, true},
	{T_LINES,					_hoops_GRRCR("polylines"),		_hoops_ARSAP, 1, true},
	{T_MARKERS,					_hoops_GRRCR("markers only"),	_hoops_ARSAP, 1, true},
	{T_VERTICES,				_hoops_GRRCR("vertices"),		_hoops_ARSAP, 1, true},
	{T_MARKERS|T_VERTICES,		_hoops_GRRCR("markers"),		_hoops_ARSAP, 1, true},
	{T_IMAGES,					_hoops_GRRCR("images"),			_hoops_ARSAP, 1, true},
	{T_IMAGES,					_hoops_GRRCR("pixel arrays"),	_hoops_ARSAP, 1, true},
	{T_FACES|T_ANY_EDGE,		_hoops_GRRCR("polygons"),		_hoops_ARSAP, 1, true},
	{T_STRING_CURSORS,			_hoops_GRRCR("string cursors"), _hoops_ARSAP, 1, true},
	{T_WINDOWS,					_hoops_GRRCR("windows"),		_hoops_ARSAP, 1, true},
	{_hoops_GPA,				_hoops_GRRCR("isolines"),		_hoops_ARSAP, 1, true},
};


local bool _hoops_IPRPS (
	_hoops_AIGPR *	_hoops_RIGC,
	Option_Value *			_hoops_CPRPS,
	Option_Value *			option) 
{

	HE_ERROR2 (HEC_SELECTION, HES_INVALID_INPUT,
			   Sprintf_NN (null, "'%n' is not a legal selectability (type was '%n')", &option->value._name[0], &option->type->name),
			   "(Choices are 'on/off/^/v/*/O/!' or combinations)");

	if (_hoops_CPRPS != null) 
		HI_Free_Option_List (_hoops_RIGC, _hoops_CPRPS);
	return false;
}


local bool _hoops_SPRPS (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			list,
	_hoops_ASAIR *			_hoops_APHCR) 
{
	_hoops_HIACR (_hoops_IAPPP, _hoops_HPRPS);

	char	buf[MAX_ERRMSG];

	/* _hoops_AGSIP! _hoops_SIHHH!!!! */
	if (*list == '^' || *list == '*' ||
		((*list == 'v' || *list == 'V') &&
		 (list[1] != 'e' && list[1] != 'E')) ||
		((*list == 'O' || *list == 'o') &&
		 (list[1] == '^' || list[1] == 'v' || list[1] == '*' ||
		  list[1] == '!' || list[1] == '\0'))) {
		Sprintf_S (buf, "window=%s", list);
		list = buf;
	}

	Option_Value *	_hoops_CPRPS;
	Option_Value *	option;
	
	if (!HI_Parse_Options (_hoops_RIGC, list, _hoops_CIACR (_hoops_IAPPP), &_hoops_CPRPS, _hoops_SIACR))
		return false;

	if ((option = _hoops_CPRPS) == null) 
		return false;

	_hoops_APHCR->mask = 0;
	_hoops_APHCR->up = 0;
	_hoops_APHCR->down = 0;
	_hoops_APHCR->_hoops_RHARP = 0;
	_hoops_APHCR->_hoops_AHARP = 0;
	_hoops_APHCR->_hoops_PHARP = 0;

	do {
		if (option->type->_hoops_RCIIR == _hoops_RRRCR) {
			_hoops_APHCR->mask = _hoops_IAHGP;
			_hoops_APHCR->up = 0;
			_hoops_APHCR->down = 0;	/* _hoops_HPCAR "_hoops_PSAP" */
			_hoops_APHCR->_hoops_AHARP = 0;
			_hoops_APHCR->_hoops_RHARP = 0;
			_hoops_APHCR->_hoops_PHARP = 0;

			if (option->type->id != _hoops_PPRPS)
				_hoops_APHCR->down = _hoops_IAHGP;		/* "_hoops_GPP" */
		}
		else {
			_hoops_ACHR	mask = option->type->id;

			_hoops_APHCR->mask |= mask;
			_hoops_APHCR->down &= ~mask;
			_hoops_APHCR->up &= ~mask;
			_hoops_APHCR->_hoops_AHARP &= ~mask;
			_hoops_APHCR->_hoops_RHARP &= ~mask;
			_hoops_APHCR->_hoops_PHARP &= ~mask;

			if (option->_hoops_GCACR) {}
			else {
				char	*_hoops_RPPA = option->value._name[0].text,
								*_hoops_SSRPR = _hoops_RPPA + option->value._name[0].length;
				bool	_hoops_GHRPS = false;
				bool	_hoops_RHRPS = false;

				if (_hoops_RPPA == _hoops_SSRPR) {
					_hoops_APHCR->down |= mask;		/* _hoops_ISAP - "_hoops_GPP" */
				}
				else do switch (*_hoops_RPPA++) {
					case '!': {
						/* _hoops_RHAP _hoops_HAR _hoops_RPR _hoops_GAR, _hoops_PAR _hoops_AGPP _hoops_CCA, _hoops_PGI
						 * _hoops_AHRPS _hoops_PAR _hoops_SRRSA */
						_hoops_APHCR->_hoops_PHARP |= mask;
					}	break;

					case '^': {
						if (_hoops_GHRPS)
							return _hoops_IPRPS (_hoops_RIGC, _hoops_CPRPS, option);
						_hoops_APHCR->up |= mask;
						_hoops_RHRPS = true;
					}	break;

					case 'V':
					case 'v': {
						if (_hoops_GHRPS)
							return _hoops_IPRPS (_hoops_RIGC, _hoops_CPRPS, option);
						_hoops_APHCR->down |= mask;
						_hoops_RHRPS = true;
					}	break;

					case '*': {
						if (_hoops_GHRPS)
							return _hoops_IPRPS (_hoops_RIGC, _hoops_CPRPS, option);
						_hoops_APHCR->_hoops_AHARP |= mask;
						_hoops_RHRPS = true;
					}	break;

					case 'o':
					case 'O': {
						if (_hoops_RPPA == _hoops_SSRPR) {		/* _hoops_CGHI _hoops_GSPR */
							if (_hoops_GHRPS)
								return _hoops_IPRPS (_hoops_RIGC, _hoops_CPRPS, option);
							_hoops_APHCR->_hoops_RHARP |= mask;
							_hoops_RHRPS = true;
						}
						else switch (*_hoops_RPPA) {
							case 'n':
							case 'N': {
								if (_hoops_GHRPS || _hoops_RHRPS)
									return _hoops_IPRPS (_hoops_RIGC, _hoops_CPRPS, option);
								++_hoops_RPPA;
								_hoops_APHCR->down |= mask;
								_hoops_GHRPS = true;
							}	break;

							case 'f':
							case 'F': {
								if (_hoops_GHRPS || _hoops_RHRPS)
									return _hoops_IPRPS (_hoops_RIGC, _hoops_CPRPS, option);
								++_hoops_RPPA;
								if (_hoops_RPPA == _hoops_SSRPR || (*_hoops_RPPA != 'f' && *_hoops_RPPA != 'F'))
									return _hoops_IPRPS (_hoops_RIGC, _hoops_CPRPS, option);
								++_hoops_RPPA;
								/* _hoops_PSP _hoops_RRP _hoops_IS _hoops_ARHSA _hoops_SGI */
								_hoops_GHRPS = true;
							}	break;

							default: {
								if (_hoops_GHRPS)
									return _hoops_IPRPS (_hoops_RIGC, _hoops_CPRPS, option);
								_hoops_APHCR->_hoops_RHARP |= mask;
								_hoops_RHRPS = true;
							}	break;
						}
					}	break;

					case ' ':
					case '\t': {
						/* _hoops_PSRCA */
					}	break;

					default: {
						return _hoops_IPRPS (_hoops_RIGC, _hoops_CPRPS, option);
					}	/* _hoops_IHSA; */
				} while (_hoops_RPPA != _hoops_SSRPR);

				if (ANYBIT (_hoops_APHCR->_hoops_PHARP, mask)) {
					/* _hoops_PSH '!' _hoops_RH _hoops_PSHR _hoops_GAR '_hoops_HPPC!' */
					if (!ANYBIT (_hoops_APHCR->up | _hoops_APHCR->_hoops_RHARP |
								 _hoops_APHCR->down | _hoops_APHCR->_hoops_AHARP, mask))
						_hoops_APHCR->down |= mask;

					/* "_hoops_PRGI _hoops_RPP _hoops_PSIPR" _hoops_HRGR _hoops_HAR _hoops_CPSA _hoops_APIP _hoops_IH _hoops_SPHGR */
					/* _hoops_HIH _hoops_SR _hoops_IIS _hoops_SCH _hoops_PHRPS _hoops_RPP _hoops_SSIA _hoops_ASGPH "_hoops_CPS" */
					if (mask == T_WINDOWS)
						HE_WARNING (HEC_SELECTION, HES_NOT_VALID_FOR_WINDOWS,
									"Selectability of '!' is not valid for 'windows'");

					_hoops_APHCR->_hoops_PHARP &= ~T_WINDOWS;
				}
			}
		}
	} while ((option = option->next) != null);

	if (_hoops_CPRPS != null) HI_Free_Option_List (_hoops_RIGC, _hoops_CPRPS);

	_hoops_APHCR->_hoops_HHARP = _hoops_APHCR->up | _hoops_APHCR->down | _hoops_APHCR->_hoops_RHARP | _hoops_APHCR->_hoops_AHARP;

	return true;
}


local Attribute * _hoops_HHRPS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR) 
{
	_hoops_ASAIR const *	_hoops_IHRPS = (_hoops_ASAIR const *)_hoops_CPACR;
	_hoops_ASAIR alter *	_hoops_CHRPS = (_hoops_ASAIR alter *)_hoops_SPACR;

	if (_hoops_IHRPS != null &&
		_hoops_IHRPS->mask == _hoops_CHRPS->mask &&
		_hoops_IHRPS->up == _hoops_CHRPS->up &&
		_hoops_IHRPS->down == _hoops_CHRPS->down &&
		_hoops_IHRPS->_hoops_RHARP == _hoops_CHRPS->_hoops_RHARP &&
		_hoops_IHRPS->_hoops_AHARP == _hoops_CHRPS->_hoops_AHARP &&
		_hoops_IHRPS->_hoops_PHARP == _hoops_CHRPS->_hoops_PHARP)
		return null;

	if (_hoops_IHRPS != null) {
		_hoops_CHRPS->up |= (_hoops_IHRPS->up & ~_hoops_CHRPS->mask);
		_hoops_CHRPS->down |= (_hoops_IHRPS->down & ~_hoops_CHRPS->mask);
		_hoops_CHRPS->_hoops_RHARP |= (_hoops_IHRPS->_hoops_RHARP & ~_hoops_CHRPS->mask);
		_hoops_CHRPS->_hoops_AHARP |= (_hoops_IHRPS->_hoops_AHARP & ~_hoops_CHRPS->mask);
		_hoops_CHRPS->_hoops_PHARP |= (_hoops_IHRPS->_hoops_PHARP & ~_hoops_CHRPS->mask);
		_hoops_CHRPS->mask |= _hoops_IHRPS->mask;
		_hoops_CHRPS->_hoops_HHARP = _hoops_CHRPS->up|_hoops_CHRPS->down|_hoops_CHRPS->_hoops_RHARP|_hoops_CHRPS->_hoops_AHARP;
	}

	_hoops_ACHR	_hoops_RCGC = 0;

	if (ANYBIT (_hoops_CHRPS->_hoops_HHARP, _hoops_RAHGP))
		_hoops_RCGC = _hoops_RPHGP;

	if (BIT (_hoops_CHRPS->_hoops_HHARP, T_WINDOWS))
		_hoops_RCGC |= _hoops_PPHGP;

	_hoops_CRCP * _hoops_SRCP = (_hoops_CRCP *)item;
	ASSERT(_hoops_SRCP->type == _hoops_IRCP);

	if (!ALLBITS (_hoops_SRCP->_hoops_RCGC, _hoops_RCGC))
		HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_RCGC);

	return _hoops_CHRPS;
}


GLOBAL_FUNCTION bool HI_Set_Selectability(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_ASAIR *			_hoops_AAICA) 
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_SELECTABILITY, _hoops_HHRPS, _hoops_AAICA);
}

GLOBAL_FUNCTION bool HI_Unset_Selectability(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_ASAIR *			_hoops_AAICA) 
{
	/* _hoops_RRGRA */
	UNREFERENCED(_hoops_RIGC);
	UNREFERENCED(item);
	UNREFERENCED(_hoops_AAICA);
	return false;
}

HC_INTERFACE void HC_CDECL HC_Set_Selectability (
	char const *		list) 
{
	_hoops_PAPPR context("Set_Selectability");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Selectability (%S);\n", list));
	);

	bool			used = false;
	_hoops_ASAIR *	_hoops_AAICA;
	ZALLOC (_hoops_AAICA, _hoops_ASAIR);
	if (_hoops_SPRPS (context, list, _hoops_AAICA)) {

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_CPRPP)) != null) {
			used = HI_Set_Selectability(context, target, _hoops_AAICA);
			_hoops_IRRPR();
		}
	}
	if (!used)
		FREE (_hoops_AAICA, _hoops_ASAIR);

}


HC_INTERFACE void HC_CDECL HC_UnSet_Selectability (void) 
{
	_hoops_PAPPR context("UnSet_Selectability");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Selectability ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_CPRPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute (context,  target, HK_SELECTABILITY);
		_hoops_IRRPR();
	}
}




#ifdef DISABLE_SHOW
#	ifdef DISABLE_METAFILE
#		define	_hoops_SHRPS
#	endif
#endif

#ifndef _hoops_SHRPS

local char *_hoops_GIRPS (
	char					*_hoops_ASAPR,
	_hoops_ASAIR		*_hoops_GSCSP,
	_hoops_ACHR			type,
	char const				*_hoops_RHSRR) {

	do
		*_hoops_ASAPR++ = *_hoops_RHSRR++;
	_hoops_RGGA (*_hoops_RHSRR == '\0');

	*_hoops_ASAPR++ = '=';

	if (ANYBIT (_hoops_GSCSP->down, type))	   *_hoops_ASAPR++ = 'v';
	if (ANYBIT (_hoops_GSCSP->up, type))		   *_hoops_ASAPR++ = '^';
	if (ANYBIT (_hoops_GSCSP->_hoops_AHARP, type)) *_hoops_ASAPR++ = '*';
	if (ANYBIT (_hoops_GSCSP->_hoops_RHARP, type))   *_hoops_ASAPR++ = 'O';

	if (_hoops_ASAPR[-1] == '=') {
		*_hoops_ASAPR++ = 'o';
		*_hoops_ASAPR++ = 'f';
		*_hoops_ASAPR++ = 'f';
	}
	else {
		if (_hoops_ASAPR[-1] == 'v') {
			_hoops_ASAPR[-1] = 'o';
			*_hoops_ASAPR++ = 'n';
		}

		if (ANYBIT (_hoops_GSCSP->_hoops_PHARP, type)) 
			*_hoops_ASAPR++ = '!';
	}

	*_hoops_ASAPR++ = ',';

	return _hoops_ASAPR;
}
#endif


GLOBAL_FUNCTION void HI_Show_Selectability (
	_hoops_ASAIR *		_hoops_GSCSP,
	char *				spec,
	int					_hoops_CSACR) 
{
#ifndef _hoops_SHRPS
	char				buf[300];
	char				*_hoops_ASAPR = buf;

	if (_hoops_GSCSP->mask == _hoops_IAHGP &&
		(_hoops_GSCSP->down == _hoops_IAHGP || _hoops_GSCSP->down == false) &&
		(_hoops_GSCSP->up == _hoops_IAHGP || _hoops_GSCSP->up == false) &&
		(_hoops_GSCSP->_hoops_AHARP == _hoops_IAHGP ||
		 _hoops_GSCSP->_hoops_AHARP == false) &&
		(_hoops_GSCSP->_hoops_RHARP == _hoops_IAHGP ||
		 _hoops_GSCSP->_hoops_RHARP == false) &&
		(_hoops_GSCSP->_hoops_PHARP == _hoops_IAHGP ||
		 _hoops_GSCSP->_hoops_PHARP == false)) {
		_hoops_ASAPR = _hoops_GIRPS (_hoops_ASAPR, _hoops_GSCSP, _hoops_IAHGP, "everything");
	}
	else {
		if (BIT (_hoops_GSCSP->mask, T_WINDOWS))
			_hoops_ASAPR = _hoops_GIRPS (_hoops_ASAPR, _hoops_GSCSP, T_WINDOWS, "windows");

		if (ALLBITS (_hoops_GSCSP->mask, _hoops_RAHGP) &&
			(ALLBITS (_hoops_GSCSP->down, _hoops_RAHGP) ||
			 !ANYBIT (_hoops_GSCSP->down, _hoops_RAHGP)) &&
			(ALLBITS (_hoops_GSCSP->up, _hoops_RAHGP) ||
			 !ANYBIT (_hoops_GSCSP->up, _hoops_RAHGP)) &&
			(ALLBITS (_hoops_GSCSP->_hoops_AHARP, _hoops_RAHGP) ||
			 !ANYBIT (_hoops_GSCSP->_hoops_AHARP, _hoops_RAHGP)) &&
			(ALLBITS (_hoops_GSCSP->_hoops_RHARP, _hoops_RAHGP) ||
			 !ANYBIT (_hoops_GSCSP->_hoops_RHARP, _hoops_RAHGP)) &&
			(ALLBITS (_hoops_GSCSP->_hoops_PHARP, _hoops_RAHGP) ||
			 !ANYBIT (_hoops_GSCSP->_hoops_PHARP, _hoops_RAHGP))) {
			_hoops_ASAPR = _hoops_GIRPS (_hoops_ASAPR, _hoops_GSCSP, _hoops_RAHGP, "geometry");
		}
		else {
			if (ALLBITS (_hoops_GSCSP->mask, T_FACES|T_ANY_EDGE) &&
				(ALLBITS (_hoops_GSCSP->down, T_FACES|T_ANY_EDGE) ||
				 !ANYBIT (_hoops_GSCSP->down, T_FACES|T_ANY_EDGE)) &&
				(ALLBITS (_hoops_GSCSP->up, T_FACES|T_ANY_EDGE) ||
				 !ANYBIT (_hoops_GSCSP->up, T_FACES|T_ANY_EDGE)) &&
				(ALLBITS (_hoops_GSCSP->_hoops_AHARP, T_FACES|T_ANY_EDGE) ||
				 !ANYBIT (_hoops_GSCSP->_hoops_AHARP, T_FACES|T_ANY_EDGE)) &&
				(ALLBITS (_hoops_GSCSP->_hoops_RHARP, T_FACES|T_ANY_EDGE) ||
				 !ANYBIT (_hoops_GSCSP->_hoops_RHARP, T_FACES|T_ANY_EDGE)) &&
				(ALLBITS (_hoops_GSCSP->_hoops_PHARP, T_FACES|T_ANY_EDGE) ||
				 !ANYBIT (_hoops_GSCSP->_hoops_PHARP, T_FACES|T_ANY_EDGE))) {
				_hoops_ASAPR = _hoops_GIRPS (_hoops_ASAPR, _hoops_GSCSP, T_FACES|T_ANY_EDGE, "polygons");
			}
			else {
				if (ANYBIT (_hoops_GSCSP->mask, T_ANY_EDGE))
					_hoops_ASAPR = _hoops_GIRPS (_hoops_ASAPR, _hoops_GSCSP, T_ANY_EDGE, "edges");

				if (BIT (_hoops_GSCSP->mask, T_FACES))
					_hoops_ASAPR = _hoops_GIRPS (_hoops_ASAPR, _hoops_GSCSP, T_FACES, "faces");
			}

			if (ALLBITS (_hoops_GSCSP->mask, T_MARKERS|T_VERTICES) &&
				(ALLBITS (_hoops_GSCSP->down, T_MARKERS|T_VERTICES) ||
				 !ANYBIT (_hoops_GSCSP->down, T_MARKERS|T_VERTICES)) &&
				(ALLBITS (_hoops_GSCSP->up, T_MARKERS|T_VERTICES) ||
				 !ANYBIT (_hoops_GSCSP->up, T_MARKERS|T_VERTICES)) &&
				(ALLBITS (_hoops_GSCSP->_hoops_AHARP, T_MARKERS|T_VERTICES) ||
				 !ANYBIT (_hoops_GSCSP->_hoops_AHARP, T_MARKERS|T_VERTICES)) &&
				(ALLBITS (_hoops_GSCSP->_hoops_RHARP, T_MARKERS|T_VERTICES) ||
				 !ANYBIT (_hoops_GSCSP->_hoops_RHARP, T_MARKERS|T_VERTICES)) &&
				(ALLBITS (_hoops_GSCSP->_hoops_PHARP, T_MARKERS|T_VERTICES) ||
				 !ANYBIT (_hoops_GSCSP->_hoops_PHARP, T_MARKERS|T_VERTICES))) {
				_hoops_ASAPR = _hoops_GIRPS (_hoops_ASAPR, _hoops_GSCSP, T_MARKERS|T_VERTICES, "markers");
			}
			else {
				if (BIT (_hoops_GSCSP->mask, T_MARKERS))
					_hoops_ASAPR = _hoops_GIRPS (_hoops_ASAPR, _hoops_GSCSP, T_MARKERS, "markers only");

				if (ANYBIT (_hoops_GSCSP->mask, T_VERTICES))
					_hoops_ASAPR = _hoops_GIRPS (_hoops_ASAPR, _hoops_GSCSP, T_VERTICES, "vertices");
			}

			if (BIT (_hoops_GSCSP->mask, T_ANY_LIGHTS))
				_hoops_ASAPR = _hoops_GIRPS (_hoops_ASAPR, _hoops_GSCSP, T_ANY_LIGHTS, "lights");

			if (BIT (_hoops_GSCSP->mask, T_LINES))
				_hoops_ASAPR = _hoops_GIRPS (_hoops_ASAPR, _hoops_GSCSP, T_LINES, "lines");

			if (BIT (_hoops_GSCSP->mask, T_IMAGES))
				_hoops_ASAPR = _hoops_GIRPS (_hoops_ASAPR, _hoops_GSCSP, T_IMAGES, "images");

			if (BIT (_hoops_GSCSP->mask, T_TEXT))
				_hoops_ASAPR = _hoops_GIRPS (_hoops_ASAPR, _hoops_GSCSP, T_TEXT, "text");

			if (BIT (_hoops_GSCSP->mask, T_STRING_CURSORS))
				_hoops_ASAPR = _hoops_GIRPS (_hoops_ASAPR, _hoops_GSCSP, T_STRING_CURSORS, "string cursors");
		}

		if (BIT (_hoops_GSCSP->mask, _hoops_GPA))
			_hoops_ASAPR = _hoops_GIRPS (_hoops_ASAPR, _hoops_GSCSP, _hoops_GPA, "isolines");
	}

	if (_hoops_ASAPR > buf) --_hoops_ASAPR; /* _hoops_HASIR _hoops_GRCIR _hoops_RRCIR */

	HI_Return_Chars (spec, _hoops_CSACR, buf, (int)(_hoops_ASAPR - buf));
#endif
}


#ifndef DISABLE_SHOW

local void _hoops_RIRPS (
	_hoops_ASAIR *	_hoops_RIRIP,
	char const *	_hoops_AIRPS) 
{
	HE_ERROR (HEC_SELECTION, HES_NO_LOCAL_SETTING, Sprintf_SP (null, "'%s' has no setting in '%p'", _hoops_AIRPS, _hoops_RIRIP->owner));
}



INLINE char const * _hoops_PIRPS (
	char const				*string,
	char const				*_hoops_CSIAC) {

	while (*_hoops_CSIAC) 
		if (*string++ != *_hoops_CSIAC++) 
			return null;
	return string;
}

local _hoops_ACHR _hoops_HIRPS (
	char const		*_hoops_IIRPS) {
	char const		*_hoops_RPPA = _hoops_IIRPS;
	char			*_hoops_ASAPR;
	_hoops_ACHR	type = 0;
	char			buf[50];

	while (*_hoops_RPPA == ' ') ++_hoops_RPPA;
	_hoops_ASAPR = buf;
	_hoops_RGGA (*_hoops_RPPA == '\0') {
		*_hoops_ASAPR = _hoops_SHPCR (*_hoops_RPPA);
		if (++_hoops_ASAPR == buf+_hoops_GGAPR(buf)-1) {
			_hoops_ASAPR = buf;
			break;
		}
		++_hoops_RPPA;
	}
	*_hoops_ASAPR = '\0';
	while (*--_hoops_ASAPR == ' ')
		*_hoops_ASAPR = '\0';

	switch (buf[0]) {
		case 'w': {
			_hoops_RPPA = _hoops_PIRPS (&buf[1], "indow");
			type = T_WINDOWS;
			if (_hoops_RPPA != null && *_hoops_RPPA == 's') ++_hoops_RPPA;
		}	break;
		case 'c': {
			if ((_hoops_RPPA = _hoops_PIRPS (&buf[1], "utting plane")) != null)
				type = T_CUTTING_PLANES;
			else if ((_hoops_RPPA = _hoops_PIRPS (&buf[1], "ut geometry")) != null)
				type = T_CUT_GEOMETRY;
			else if ((_hoops_RPPA = _hoops_PIRPS (&buf[1], "ut edge")) != null)
				type = T_CUT_GEOMETRY;
			else {
				_hoops_RPPA = _hoops_PIRPS (&buf[1], "ut face");
				type = T_CUT_GEOMETRY;
			}
			if (_hoops_RPPA != null && *_hoops_RPPA == 's') ++_hoops_RPPA;
		}	break;
		case 'e': {
			if ((_hoops_RPPA = _hoops_PIRPS (&buf[1], "dge")) != null) {
				type = T_ANY_EDGE;
				if (_hoops_RPPA != null && *_hoops_RPPA == 's') ++_hoops_RPPA;
			}
			else {
				_hoops_RPPA = _hoops_PIRPS (&buf[1], "verything");
				type = _hoops_IAHGP;
			}
		}	break;
		case 'f': {
			_hoops_RPPA = _hoops_PIRPS (&buf[1], "ace");
			type = T_FACES;
			if (_hoops_RPPA != null && *_hoops_RPPA == 's') ++_hoops_RPPA;
		}	break;
		case 'g': {
			_hoops_RPPA = _hoops_PIRPS (&buf[1], "eometry");
			type = _hoops_RAHGP;
		}	break;
		case 'l': {
			if ((_hoops_RPPA = _hoops_PIRPS (&buf[1], "ine")) != null)
				type = T_LINES;
			else {
				_hoops_RPPA = _hoops_PIRPS (&buf[1], "ight");
				type = T_ANY_LIGHTS;
			}
			if (_hoops_RPPA != null && *_hoops_RPPA == 's') ++_hoops_RPPA;
		}	break;
		case 'm': {
			if ((_hoops_RPPA = _hoops_PIRPS (&buf[1], "arker")) != null) {
				char const		*tmp;

				if (*_hoops_RPPA == 's')
					++_hoops_RPPA;

				if ((tmp = _hoops_PIRPS (_hoops_RPPA, " only")) != null) {
					_hoops_RPPA = tmp;
					type = T_MARKERS;
				}
				else
					type = T_MARKERS | T_VERTICES;
			}
		}	break;
		case 'v': {
			if ((_hoops_RPPA = _hoops_PIRPS (&buf[1], "ertex")) != null)
				type = T_VERTICES;
			else {
				_hoops_RPPA = _hoops_PIRPS (&buf[1], "ertices");
				type = T_VERTICES;
			}
		}	break;

		case 'i': {
			_hoops_RPPA = _hoops_PIRPS (&buf[1], "mage");
			type = T_IMAGES;
			if (_hoops_RPPA != null && *_hoops_RPPA == 's') ++_hoops_RPPA;
		}	break;
		case 'p': {
			if ((_hoops_RPPA = _hoops_PIRPS (&buf[1], "olygon")) != null)
				type = T_FACES|T_ANY_EDGE;
			else if ((_hoops_RPPA = _hoops_PIRPS (&buf[1], "olyline")) != null)
				type = T_LINES;
			else {
				_hoops_RPPA = _hoops_PIRPS (&buf[1], "ixel array");
				type = T_IMAGES;
			}
			if (_hoops_RPPA != null && *_hoops_RPPA == 's') ++_hoops_RPPA;
		}	break;
		case 't': {
			_hoops_RPPA = _hoops_PIRPS (&buf[1], "ext");
			type = T_TEXT;
		}	break;
		case 's': {
			if ((_hoops_RPPA = _hoops_PIRPS (&buf[1], "tring cursor")) != null)
				type = T_STRING_CURSORS;
			else {
				_hoops_RPPA = _hoops_PIRPS (&buf[1], "hadow");
				type = T_ANY_SHADOW;
			}
			if (_hoops_RPPA != null && *_hoops_RPPA == 's') ++_hoops_RPPA;
		}	break;
		default: {
			_hoops_RPPA = null;
			type = 0;
		}	break;
	}

	if (_hoops_RPPA == null || *_hoops_RPPA != '\0') {
		HE_ERROR (HEC_GEOMETRY, HES_INVALID_TYPE, Sprintf_S (null, "'%s' is not a recognized type", _hoops_IIRPS));
		return false;
	}

	return type;
}


local void _hoops_CIRPS (
	_hoops_ASAIR		*_hoops_RIRIP,
	char const				*_hoops_AIRPS,
	char					*result,
	int						_hoops_RIAGA) {
	_hoops_ACHR			type;

	while (*_hoops_AIRPS == ' ') ++_hoops_AIRPS;

	if ((type = _hoops_HIRPS (_hoops_AIRPS)) != false) {
		char					buf[8];
		char					*_hoops_ASAPR;

		if (!ANYBIT (_hoops_RIRIP->mask, type)) {
			_hoops_RIRPS (_hoops_RIRIP, _hoops_AIRPS);
			return;
		}

		if (type != _hoops_RIII(type)) {
			if (!ALLBITS (_hoops_RIRIP->mask, type) ||
				(ANYBIT (_hoops_RIRIP->up, type) &&
				 !ALLBITS (_hoops_RIRIP->up, type)) ||
				(ANYBIT (_hoops_RIRIP->_hoops_RHARP, type) &&
				 !ALLBITS (_hoops_RIRIP->_hoops_RHARP, type)) ||
				(ANYBIT (_hoops_RIRIP->down, type) &&
				 !ALLBITS (_hoops_RIRIP->down, type)) ||
				(ANYBIT (_hoops_RIRIP->_hoops_AHARP, type) &&
				 !ALLBITS (_hoops_RIRIP->_hoops_AHARP, type))) {
				HE_ERROR2 (HEC_GEOMETRY, HES_INVALID_TYPE,
						   Sprintf_S (null, "Can't show '%s' selectability -", _hoops_AIRPS),
						   "individual components don't all agree");

				return;
			}
			type = _hoops_RIII(type);
		}

		_hoops_ASAPR = buf;
		if (BIT (_hoops_RIRIP->up, type)) *_hoops_ASAPR++ = '^';
		if (BIT (_hoops_RIRIP->down, type)) *_hoops_ASAPR++ = 'v';
		if (BIT (_hoops_RIRIP->_hoops_RHARP, type)) *_hoops_ASAPR++ = 'O';
		if (BIT (_hoops_RIRIP->_hoops_AHARP, type)) *_hoops_ASAPR++ = '*';
		if (_hoops_ASAPR == buf)
			HI_Return_Chars (result, _hoops_RIAGA, "off", 3);
		else {
			if (BIT (_hoops_RIRIP->_hoops_PHARP, type)) *_hoops_ASAPR++ = '!';
			HI_Return_Chars (result, _hoops_RIAGA, buf, (int)(_hoops_ASAPR - buf));
		}
	}
}
#endif


HC_INTERFACE void HC_CDECL HC_Show_Selectability (
	char *			list) 
{
	_hoops_PAPPR context("Show_Selectability");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Selectability () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HSRPP)) != null) {

		_hoops_ASAIR *	_hoops_AAICA;
		if ((_hoops_AAICA = (_hoops_ASAIR *)HI_Find_Attribute (context, target, HK_SELECTABILITY)) != null) {

			HI_Show_Selectability (_hoops_AAICA, list, -1);
			_hoops_HPRH (_hoops_AAICA);
		}
		_hoops_IRRPR();
	}
#endif
}


#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_Net_Selectability (
	int				count,
	Key const *		keys,
	char *			list) 
{
	_hoops_PAPPR context("PShow_Net_Selectability");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Selectability () */\n");
	);

	_hoops_ASAIR *	_hoops_AAICA;
	if ((_hoops_AAICA = (_hoops_ASAIR *) HI_Find_Attribute_And_Lock(context, _hoops_HSRPP, _hoops_HRPCR, count, keys)) != null) {
		HI_Show_Selectability (_hoops_AAICA, list, -1);
		_hoops_HPRH (_hoops_AAICA);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(list, -1, "", 0);
#endif
}
#endif



HC_INTERFACE void HC_CDECL HC_Show_One_Selectability (
	char const *		_hoops_ISGIH,
	char *				list) 
{
	_hoops_PAPPR context("Show_One_Selectability");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_Selectability () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HSRPP)) != null) {

		_hoops_ASAIR *	_hoops_AAICA;
		if ((_hoops_AAICA = (_hoops_ASAIR *)HI_Find_Attribute (context, target, HK_SELECTABILITY)) != null) {
		
			_hoops_CIRPS (_hoops_AAICA, _hoops_ISGIH, list, -1);
			_hoops_HPRH (_hoops_AAICA);
		}
		_hoops_IRRPR();
	}
#endif
}




#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Selectability (
	int				count,
	Key const *		keys,
	char const *	_hoops_ISGIH,
	char *			list) 
{
	_hoops_PAPPR context("PShow_One_Net_Selectability");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_One_Net_Selectability () */\n");
	);

	_hoops_ASAIR *	_hoops_AAICA;
	if ((_hoops_AAICA = (_hoops_ASAIR *) HI_Find_Attribute_And_Lock(context, _hoops_HSRPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_CIRPS (_hoops_AAICA, _hoops_ISGIH, list, -1);
		_hoops_HPRH (_hoops_AAICA);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(list, -1, "", 0);

#endif
}
#endif



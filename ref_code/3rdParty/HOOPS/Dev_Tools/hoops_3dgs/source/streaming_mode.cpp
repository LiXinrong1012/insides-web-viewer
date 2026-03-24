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
 * $Id: obf_tmp.txt 1.62 2010-10-26 20:48:20 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


local bool _hoops_AIGGGR (
	char const		*spec,
	bool		*_hoops_PIGGGR) {

	/*** _hoops_IGIPR _hoops_AHHR-_hoops_CCGAI _hoops_GSGR! ***/

	switch (spec[0]) {
		case 'T': case 't': case 'Y': case 'y': {
			*_hoops_PIGGGR = true;
			return true;
		}		/*_hoops_IHSA;*/

		case 'F': case 'f': case 'N': case 'n': {
			*_hoops_PIGGGR = false;
			return true;
		}		/*_hoops_IHSA;*/

		case 'O': case 'o': {
			switch (spec[1]) {
				case 'N': case 'n': {
					*_hoops_PIGGGR = true;
					return true;
				}		/*_hoops_IHSA;*/

				case 'F': case 'f': {
					*_hoops_PIGGGR = false;
					return true;
				}		/*_hoops_IHSA;*/
			}
		}	break;
	}

	HE_ERROR2 (HEC_ATTRIBUTE, HES_BAD_VALUE,
			   Sprintf_S (null, "'%s' is a bad attribute value -", spec),
			   "Should be one of On/Off/True/False/Yes/No (or an abbreviation)");

	return false;
}


local Attribute *_hoops_HIGGGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR)
{
	_hoops_RRAIR const *	_hoops_IIGGGR = (_hoops_RRAIR const *)_hoops_CPACR;
	_hoops_RRAIR alter *	_hoops_CIGGGR = (_hoops_RRAIR alter *)_hoops_SPACR;

	_hoops_CRCP * _hoops_SRCP = (_hoops_CRCP *)item;
	ASSERT(_hoops_SRCP->type == _hoops_IRCP);

	UNREFERENCED (_hoops_RIGC);

	if (_hoops_IIGGGR != null && _hoops_IIGGGR->flag == _hoops_CIGGGR->flag)
		return null;

	if (_hoops_CIGGGR->flag == true && BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) /* _hoops_SIGGGR */
		return null;

	if (_hoops_CIGGGR->flag == false) {

		/* _hoops_RGSR _hoops_ARCGC */
		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) { /* _hoops_CSAP _hoops_RRCGC */
			HE_ERROR2 (HEC_INVALID_INPUT, HES_AUTO_STREAMING_MODE,
					   Sprintf_P (null,"Can't turn off Streaming Mode in '%p' -", _hoops_SRCP),
					   "Once it's on, it has to stay on - try deleting the segment.");
			return null;
		}
	}
	else {	

		/* _hoops_RGSR _hoops_HII (_hoops_RRSSH _hoops_PAR _hoops_ARCGC) _hoops_IS _hoops_RRCGC */
		Subsegment *x;
		if ((x = _hoops_SRCP->_hoops_RGRPR) != null) {
			do if (x->type == _hoops_IRCP) {
				HE_ERROR (HEC_INVALID_INPUT, HES_AUTO_STREAMING_MODE,
						  Sprintf_P (null,"'%p' has subsegments - can't turn on streaming mode",_hoops_SRCP));
				return null;
			} while ((x = x->next) != null);
		}

		_hoops_SRCP->_hoops_PHSI |= _hoops_PRSIR;
		_hoops_CIGGGR->_hoops_PHSCA = _hoops_SRCP;
	}

	return _hoops_CIGGGR;
}



GLOBAL_FUNCTION bool HI_Set_Streaming_Mode(
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH *					item,
	_hoops_RRAIR *			_hoops_SSGCR) 
{
	return HI_Set_Attribute (_hoops_RIGC, item, _hoops_GRAIR, _hoops_HIGGGR, _hoops_SSGCR);
}

HC_INTERFACE void HC_CDECL HC_Set_Streaming_Mode (
	char const *		spec)
{
	_hoops_PAPPR context("Set_Streaming_Mode");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Streaming_Mode (%S);\n", spec));
	);

	bool				used = false;
	_hoops_RRAIR *	_hoops_SSGCR;
	ZALLOC (_hoops_SSGCR, _hoops_RRAIR);

	if (_hoops_AIGGGR (spec, &_hoops_SSGCR->flag)) {

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_SPRPP)) != null) {
			used = HI_Set_Streaming_Mode(context, target, _hoops_SSGCR);
			_hoops_IRRPR();
		}
	}

	if (!used)
		FREE (_hoops_SSGCR, _hoops_RRAIR);

}



HC_INTERFACE void HC_CDECL HC_UnSet_Streaming_Mode (void) {
	_hoops_PAPPR context("UnSet_Streaming_Mode");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Streaming_Mode ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_SPRPP/*|_hoops_GCGGGR*/)) != null) {
		HI_UnSet_Attribute (context,  target, _hoops_GRAIR);
		_hoops_IRRPR();
	}
}


HC_INTERFACE void HC_CDECL HC_Show_Streaming_Mode (
	char alter *			spec)
{
	_hoops_PAPPR context("Show_Streaming_Mode");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Streaming_Mode () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_ISRPP)) != null) {

		_hoops_RRAIR const *	_hoops_CGAPS;
		if ((_hoops_CGAPS = (_hoops_RRAIR *)HI_Find_Attribute (context, target, _hoops_GRAIR)) != null) {
			if (_hoops_CGAPS->flag)
				HI_Return_Chars (spec, -1, "on", 2);
			else
				HI_Return_Chars (spec, -1, "off", 3);
			_hoops_HPRH (_hoops_CGAPS);
		}
		_hoops_IRRPR();
	}
#endif
}


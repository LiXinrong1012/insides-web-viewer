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
 * $Id: obf_tmp.txt 1.101 2010-11-18 00:59:02 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


/* _hoops_HPGHR _hoops_CAPCR _hoops_SAPCR, _hoops_GRAA-_hoops_GPPCR _hoops_PHCR _hoops_RPPCR _hoops_PAH _hoops_SHH _hoops_APPCR.
 * _hoops_PHGP _hoops_RGAR _hoops_RH _hoops_CPAC _hoops_IIAHR _hoops_PHHR _hoops_CRGR _hoops_RH _hoops_GSSR-_hoops_IAHA _hoops_PPPCR _hoops_GASR _hoops_ARI
 * _hoops_IH _hoops_IRS _hoops_GIAP-_hoops_HPPCR _hoops_PPPCR.
 */
local const _hoops_IGRCR _hoops_IPPCR[] = {
	{_hoops_CPPCR, _hoops_GRRCR ("oblique orthographic"), _hoops_SPPCR, -2, false},
	{_hoops_GHH, _hoops_GRRCR ("oblique perspective"), _hoops_SPPCR, -2, false},
	{_hoops_SSIH, _hoops_GRRCR ("oblique stretched"), _hoops_SPPCR, -2, false},
};


local bool _hoops_GHPCR (
	_hoops_AIGPR *	_hoops_RIGC,
	double					_hoops_RHPCR,	/* _hoops_ASAI '_hoops_AIIC' */
	Option_Value *			option_list)
{

	if (_hoops_RHPCR <= -90.0f || _hoops_RHPCR >= 90.0f) {
		HE_ERROR2 (HEC_CAMERA, HES_BAD_OBLIQUE_PROJECTION,
				   Sprintf_F (null,"A projection obliquity of %f is not reasonable -", _hoops_RHPCR),
				   "Should be in the range of -90 to +90 degrees.");

		HI_Free_Option_List (_hoops_RIGC, option_list); /* _hoops_IRS _hoops_AHPCR _hoops_IS _hoops_RH _hoops_CIS */
		return false;
	}

	return true;
}


local bool _hoops_PHPCR (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			_hoops_HHPCR,
	_hoops_HHRA *				_hoops_SPH)
{
	char const *		projection = _hoops_HHPCR;
	char const *		_hoops_IHPCR;
	char				c;

	/* _hoops_RH _hoops_HSPR _hoops_HRGR _hoops_CHPCR! */

	switch (_hoops_SHPCR (*projection)) {
		case 'p': {
			_hoops_IHPCR = "erspective";
			_hoops_SPH->projection = _hoops_GHH;
		}	break;
		case 'o': {
			_hoops_IHPCR = "rthographic";
			_hoops_SPH->projection = _hoops_CPPCR;
		}	break;
		case 's': {
			_hoops_IHPCR = "tretched";
			_hoops_SPH->projection = _hoops_SSIH;
		}	break;
		default: {
			_hoops_IHPCR = "forget it";
		}	break;
	}

	_hoops_SPH->_hoops_HHCH = 0.0f; /* _hoops_CCGR _hoops_GIPCR _hoops_IAII */
	_hoops_SPH->_hoops_IHCH = 0.0f; /*	 "		"	   "	 */

	_hoops_RGGA ((c = *++projection) == '\0') if (_hoops_SHPCR(c) != *_hoops_IHPCR++) {
		Option_Value *option_list;
		Option_Value *option;

		/* _hoops_PSP _hoops_RRI _hoops_HPS - _hoops_AA _hoops_IRS _hoops_GIAP _hoops_PPPCR _hoops_IH _hoops_GPPCR _hoops_IIAHR */

		_hoops_HIACR (_hoops_RIPCR, _hoops_IPPCR);

		if (!HI_Parse_Options (_hoops_RIGC, _hoops_HHPCR, _hoops_CIACR (_hoops_RIPCR),
							   &option_list, _hoops_SIACR))
			return false;

		if ((option = option_list) == null) {
			HE_ERROR (HEC_CAMERA, HES_INVALID_PROJECTION, "No camera projection specified");
			return false;
		}

		_hoops_RGGA (option->next == null) option = option->next;/*_hoops_SGH _hoops_RH _hoops_CGHI _hoops_SPR*/

		_hoops_SPH->projection = (int)option->type->id;

		if (option->_hoops_AIPCR == 0) {
			HE_ERROR (HEC_CAMERA, HES_INVALID_INPUT,"Oblique camera projections require 1 or 2 floats");
			HI_Free_Option_List (_hoops_RIGC, option_list);
			return false;
		}
		else {
			_hoops_SPH->_hoops_HHCH = option->value._hoops_PIPCR[0];
			if (!_hoops_GHPCR (_hoops_RIGC, _hoops_SPH->_hoops_HHCH, option_list))
				return false;

			if (option->_hoops_AIPCR > 1) {
				_hoops_SPH->_hoops_IHCH = option->value._hoops_PIPCR[1];
				if (!_hoops_GHPCR (_hoops_RIGC, _hoops_SPH->_hoops_IHCH, option_list))
					return false;
			}
		}

		HI_Free_Option_List (_hoops_RIGC, option_list);
		break;
	}

	return true;
}



GLOBAL_FUNCTION void HI_Default_Camera(
	_hoops_HHRA *		_hoops_SPH,
	_hoops_HHRA const *	_hoops_HIPCR)
{

	ZERO_STRUCT (_hoops_SPH, _hoops_HHRA);
	_hoops_SPH->type = HK_CAMERA;

	if (_hoops_HIPCR != null) {
		_hoops_SPH->position = _hoops_HIPCR->position;
		_hoops_SPH->target = _hoops_HIPCR->target;
		_hoops_SPH->up_vector = _hoops_HIPCR->up_vector;
		_hoops_SPH->_hoops_ISPA = _hoops_HIPCR->_hoops_ISPA;
		_hoops_SPH->_hoops_SSPA = _hoops_HIPCR->_hoops_SSPA;
		_hoops_SPH->projection = _hoops_HIPCR->projection;
		_hoops_SPH->_hoops_IIPCR = _hoops_HIPCR->_hoops_IIPCR;
		_hoops_SPH->_hoops_CRSS = _hoops_HIPCR->_hoops_CRSS;
		_hoops_SPH->_hoops_SRIR = _hoops_HIPCR->_hoops_SRIR;			
		_hoops_SPH->_hoops_ARSS = _hoops_HIPCR->_hoops_ARSS;	
		_hoops_SPH->_hoops_PRSS = _hoops_HIPCR->_hoops_PRSS;
		_hoops_SPH->_hoops_CSIH = _hoops_HIPCR->_hoops_CSIH;

		_hoops_SPH->_hoops_CIPCR = _hoops_HIPCR->_hoops_CIPCR;
		_hoops_SPH->_hoops_SIPCR = _hoops_HIPCR->_hoops_SIPCR;
		if (_hoops_HIPCR->_hoops_SIPCR != &HOOPS_WORLD->_hoops_GCPCR)
			_hoops_SPH->_hoops_SIPCR = &_hoops_SPH->_hoops_CIPCR;
	}
	else {
		_hoops_SPH->position.z = -5.0f;
		_hoops_SPH->up_vector = _hoops_IRGA::_hoops_RCPCR;
		_hoops_SPH->_hoops_ISPA = 2.0f;
		_hoops_SPH->_hoops_SSPA = 2.0f;
		_hoops_SPH->projection = _hoops_GHH;
		_hoops_SPH->_hoops_IIPCR = _hoops_IRGA::_hoops_IGHH;
		_hoops_SPH->_hoops_CRSS = _hoops_IRGA::X_Axis;
		_hoops_SPH->_hoops_SRIR = 5.0f;			/* _hoops_SAAP._hoops_SSH - _hoops_AHC._hoops_SSH */
		_hoops_SPH->_hoops_ARSS = 0.4f;		/* _hoops_ACPCR / _hoops_RHC _hoops_GIRA */
		_hoops_SPH->_hoops_PRSS = 0.4f;	/* _hoops_PCPCR / _hoops_RHC _hoops_GIRA */
		_hoops_SPH->_hoops_CSIH = 1.0f;

		_hoops_SPH->_hoops_SIPCR = &HOOPS_WORLD->_hoops_GCPCR;
	}
}


local void _hoops_HCPCR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HHRA *				_hoops_SPH,
	_hoops_CRCP *				_hoops_SRCP)
{
	_hoops_ACHR			_hoops_ICPCR;

	/* _hoops_RAIGR "2-_hoops_APCAR" _hoops_SARA _hoops_PIHA _hoops_PPSR _hoops_RGCPR _hoops_ISHP _hoops_RH +/-_hoops_AHCR _hoops_IRSS, _hoops_PPR _hoops_RH
	 * _hoops_AHCR=0 _hoops_IPPA _hoops_PIHA _hoops_SHH "_hoops_HPGR" _hoops_RH _hoops_SAAP.
	 *
	 * ("_hoops_PCPCR" _hoops_HRGR _hoops_SAHR _hoops_IGI _hoops_GAR _hoops_IRS _hoops_CCPCR-_hoops_SIPIR _hoops_CSRA _hoops_SIPIR.)
	 */

	if (Abs (_hoops_SPH->_hoops_IIPCR.z) > 0.999f &&
		(_hoops_SPH->projection != _hoops_GHH ||
		 Abs (_hoops_SPH->target.z) < 0.001f * _hoops_SPH->_hoops_SSPA)) {
		/* _hoops_HHIGR _hoops_HRGR 2-_hoops_APCAR - _hoops_SHSP _hoops_SCH _hoops_SCPCR */
	}
	else {
		/* _hoops_HHIGR _hoops_HRGR 3-_hoops_APCAR - _hoops_CRGS _hoops_GSPCR */

		_hoops_SPH->_hoops_RRHH |= _hoops_RSPCR;
		if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_ASPCR))
			HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_ASPCR);
	}

	_hoops_ICPCR = _hoops_SRCP->_hoops_RCGC;
	HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_PSPCR);
	_hoops_SRCP->_hoops_RCGC = _hoops_ICPCR;
}



local void _hoops_HSPCR (
	_hoops_HHRA *			_hoops_ISPCR,
	Vector *			_hoops_CSPCR)
{
	Vector	_hoops_SSPCR = _hoops_ISPCR->_hoops_IIPCR._hoops_SAIAR(*_hoops_CSPCR);

	float _hoops_GGHCR = _hoops_SSPCR.length();

	if (_hoops_GGHCR > 0.0f) {

		_hoops_SSPCR /= _hoops_GGHCR; // _hoops_RGHCR _hoops_HRGR _hoops_AAGA _hoops_SPCC

		if (_hoops_GGHCR > 0.0001f) {
			float _hoops_AGHCR = _hoops_ISPCR->_hoops_IIPCR._hoops_SSRP(*_hoops_CSPCR);
			HI_Arbitrary_Rotate_SC (&_hoops_SSPCR, (Point *)&_hoops_ISPCR->up_vector, _hoops_GGHCR, _hoops_AGHCR, (Point *)&_hoops_ISPCR->up_vector);
		}
	}

	_hoops_ISPCR->_hoops_CRSS = _hoops_ISPCR->up_vector._hoops_SAIAR(*_hoops_CSPCR);
}


local Attribute *_hoops_PGHCR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR)
{
	_hoops_HHRA const *			_hoops_HGHCR = (_hoops_HHRA const *)_hoops_CPACR;
	_hoops_HHRA alter *			_hoops_IGHCR = (_hoops_HHRA alter *)_hoops_SPACR;

	_hoops_CRCP * _hoops_SRCP = (_hoops_CRCP *)item;
	ASSERT(_hoops_SRCP->type == _hoops_IRCP);

	int action = _hoops_IGHCR->_hoops_RRHH;
	_hoops_IGHCR->_hoops_RRHH = 0;

	switch (action) {

		case _hoops_CGHCR:  {

			if (_hoops_HGHCR != null) {
				if (_hoops_IGHCR->position == _hoops_HGHCR->position &&
					_hoops_IGHCR->target == _hoops_HGHCR->target &&
					_hoops_IGHCR->up_vector == _hoops_HGHCR->up_vector &&
					_hoops_IGHCR->_hoops_ISPA == _hoops_HGHCR->_hoops_ISPA &&
					_hoops_IGHCR->_hoops_SSPA == _hoops_HGHCR->_hoops_SSPA &&
					_hoops_IGHCR->projection == _hoops_HGHCR->projection &&
					_hoops_IGHCR->_hoops_CIPCR == _hoops_HGHCR->_hoops_CIPCR &&
					_hoops_IGHCR->_hoops_SIPCR == _hoops_HGHCR->_hoops_SIPCR &&
					_hoops_IGHCR->_hoops_HHCH == _hoops_HGHCR->_hoops_HHCH &&
					_hoops_IGHCR->_hoops_IHCH == _hoops_HGHCR->_hoops_IHCH)
					return null;

				if (_hoops_HGHCR->_hoops_SIPCR == &_hoops_HGHCR->_hoops_CIPCR) {
					_hoops_IGHCR->_hoops_CIPCR = _hoops_HGHCR->_hoops_CIPCR;
					_hoops_IGHCR->_hoops_SIPCR = &_hoops_IGHCR->_hoops_CIPCR;
				}
			}
		} break;

		case _hoops_SGHCR: {

			Point position = _hoops_IGHCR->position;

			if (_hoops_HGHCR != null && _hoops_HGHCR->position == position)
				return null;

			HI_Default_Camera(_hoops_IGHCR, _hoops_HGHCR);

			_hoops_IGHCR->position = position;

			Vector _hoops_GRHCR = _hoops_IGHCR->target - _hoops_IGHCR->position;

			_hoops_IGHCR->_hoops_SRIR = _hoops_GRHCR.length();

			if (_hoops_IGHCR->_hoops_SRIR > 1.0E-20f) {
				_hoops_GRHCR._hoops_AAIAR();
				_hoops_HSPCR (_hoops_IGHCR, &_hoops_GRHCR);
				_hoops_IGHCR->_hoops_IIPCR = _hoops_GRHCR;
			}

			if (_hoops_IGHCR->projection == _hoops_GHH) {
				_hoops_IGHCR->_hoops_ISPA = _hoops_IGHCR->_hoops_ARSS * _hoops_IGHCR->_hoops_SRIR;
				_hoops_IGHCR->_hoops_SSPA = _hoops_IGHCR->_hoops_PRSS * _hoops_IGHCR->_hoops_SRIR;
			}
			else {
				/* _hoops_GA'_hoops_RA _hoops_AGRP _hoops_PAIP _hoops_RPP _hoops_HAR _hoops_RRHCR, _hoops_HIS _hoops_ARHCR _hoops_ARIA */
				_hoops_IGHCR->_hoops_ARSS = _hoops_IGHCR->_hoops_ISPA / _hoops_IGHCR->_hoops_SRIR;
				_hoops_IGHCR->_hoops_PRSS = _hoops_IGHCR->_hoops_SSPA / _hoops_IGHCR->_hoops_SRIR;
			}	

		} break;

		case _hoops_PRHCR: {

			Point target = _hoops_IGHCR->target;

			if (_hoops_HGHCR != null && _hoops_HGHCR->target == target)
				return null;

			HI_Default_Camera(_hoops_IGHCR, _hoops_HGHCR);

			_hoops_IGHCR->target = target;

			Vector _hoops_GRHCR = _hoops_IGHCR->target - _hoops_IGHCR->position;

			_hoops_IGHCR->_hoops_SRIR = _hoops_GRHCR.length();

			if (_hoops_IGHCR->_hoops_SRIR > 1.0E-20f) {
				_hoops_GRHCR._hoops_AAIAR();
				_hoops_HSPCR (_hoops_IGHCR, &_hoops_GRHCR);
				_hoops_IGHCR->_hoops_IIPCR = _hoops_GRHCR;
			}

			if (_hoops_IGHCR->projection == _hoops_GHH) {
				_hoops_IGHCR->_hoops_ISPA = _hoops_IGHCR->_hoops_ARSS * _hoops_IGHCR->_hoops_SRIR;
				_hoops_IGHCR->_hoops_SSPA = _hoops_IGHCR->_hoops_PRSS * _hoops_IGHCR->_hoops_SRIR;
			}
			else {
				/* _hoops_GA'_hoops_RA _hoops_AGRP _hoops_PAIP _hoops_RPP _hoops_HAR _hoops_RRHCR, _hoops_HIS _hoops_ARHCR _hoops_ARIA */
				_hoops_IGHCR->_hoops_ARSS = _hoops_IGHCR->_hoops_ISPA / _hoops_IGHCR->_hoops_SRIR;
				_hoops_IGHCR->_hoops_PRSS = _hoops_IGHCR->_hoops_SSPA / _hoops_IGHCR->_hoops_SRIR;
			}	

		} break;

		case _hoops_HRHCR: {

			Vector up_vector = _hoops_IGHCR->up_vector;

			if (_hoops_HGHCR != null && _hoops_HGHCR->up_vector == up_vector)
				return null;

			HI_Default_Camera(_hoops_IGHCR, _hoops_HGHCR);

			/* _hoops_HHGC _hoops_RHC _hoops_SISR (_hoops_GH _hoops_SISR _hoops_RHC) */
			_hoops_IGHCR->up_vector = up_vector._hoops_SAIAR(_hoops_IGHCR->_hoops_IIPCR);
			_hoops_IGHCR->up_vector = _hoops_IGHCR->_hoops_IIPCR._hoops_SAIAR(_hoops_IGHCR->up_vector);

			float length = _hoops_IGHCR->up_vector.length();

			if (length > 1.0E-20f) {
				_hoops_IGHCR->up_vector._hoops_AAIAR();
			}
			else {
				HE_ERROR2 (HEC_CAMERA, HES_BAD_UP_VECTOR,
					Sprintf_P (null, "Can't set up-vector in '%p' -", _hoops_SRCP),
					"Requested up-vector is co-linear with current line of sight");
				return null;
			}

			_hoops_IGHCR->_hoops_CRSS = _hoops_IGHCR->up_vector._hoops_SAIAR(_hoops_IGHCR->_hoops_IIPCR);

		} break;

		case _hoops_IRHCR: {

			float _hoops_ISPA = _hoops_IGHCR->_hoops_ISPA;
			float _hoops_SSPA = _hoops_IGHCR->_hoops_SSPA;

			if (_hoops_HGHCR != null && 
				_hoops_HGHCR->_hoops_ISPA == _hoops_ISPA &&
				_hoops_HGHCR->_hoops_SSPA == _hoops_SSPA)
				return null;

			if (_hoops_HGHCR != null && _hoops_HGHCR->_hoops_SRIR == 0.0f) {
				HE_ERROR2 (HEC_CAMERA, HES_BAD_POSITION,
					Sprintf_P (null,"Can't set up camera field in '%p' -", _hoops_SRCP), 
					"Camera position is on top of camera target");
				return null;
			}

			HI_Default_Camera(_hoops_IGHCR, _hoops_HGHCR);

			_hoops_IGHCR->_hoops_ISPA = _hoops_ISPA;
			_hoops_IGHCR->_hoops_SSPA = _hoops_SSPA;
			_hoops_IGHCR->_hoops_ARSS = _hoops_ISPA / _hoops_IGHCR->_hoops_SRIR;
			_hoops_IGHCR->_hoops_PRSS = _hoops_SSPA / _hoops_IGHCR->_hoops_SRIR;
			_hoops_IGHCR->_hoops_CSIH = _hoops_SSPA / _hoops_ISPA;

		} break;

		case _hoops_CRHCR: {

			int projection = _hoops_IGHCR->projection;
			float _hoops_HHCH = _hoops_IGHCR->_hoops_HHCH;
			float _hoops_IHCH = _hoops_IGHCR->_hoops_IHCH;

			if (_hoops_HGHCR != null && 
				_hoops_HGHCR->projection == projection &&
				_hoops_HGHCR->_hoops_HHCH == _hoops_HHCH &&
				_hoops_HGHCR->_hoops_IHCH == _hoops_IHCH)
				return null;

			HI_Default_Camera(_hoops_IGHCR, _hoops_HGHCR);

			_hoops_IGHCR->projection = projection;
			_hoops_IGHCR->_hoops_HHCH = _hoops_HHCH;
			_hoops_IGHCR->_hoops_IHCH = _hoops_IHCH;

		} break;

		case _hoops_SRHCR: {

			float limit = _hoops_IGHCR->_hoops_CIPCR;

			if (_hoops_HGHCR != null &&
				_hoops_HGHCR->_hoops_SIPCR != &HOOPS_WORLD->_hoops_GCPCR &&
				limit == _hoops_HGHCR->_hoops_CIPCR)
				return null;

			HI_Default_Camera(_hoops_IGHCR, _hoops_HGHCR);

			_hoops_IGHCR->_hoops_CIPCR = limit;
			_hoops_IGHCR->_hoops_SIPCR = &_hoops_IGHCR->_hoops_CIPCR;

		} break;

		case _hoops_GAHCR: {

			float	_hoops_RAHCR = _hoops_IGHCR->position.x;

			if (_hoops_HGHCR != null && _hoops_RAHCR == 0.0f)
				return null;

			HI_Default_Camera(_hoops_IGHCR, _hoops_HGHCR);
			
			if (_hoops_RAHCR != 0.0f) {
				HI_Arbitrary_Rotate (&_hoops_IGHCR->_hoops_IIPCR, (Point *)&_hoops_IGHCR->up_vector, _hoops_RAHCR, (Point *)&_hoops_IGHCR->up_vector);
				_hoops_IGHCR->up_vector._hoops_AAIAR();
				_hoops_IGHCR->_hoops_CRSS = _hoops_IGHCR->up_vector._hoops_SAIAR(_hoops_IGHCR->_hoops_IIPCR);
			}

		} break;

		case _hoops_AAHCR: {

			float	_hoops_PAHCR = _hoops_IGHCR->position.x;
			float	_hoops_HAHCR = _hoops_IGHCR->position.y;

			if (_hoops_HGHCR != null && _hoops_PAHCR == 0.0f && _hoops_HAHCR == 0.0f)
				return null;

			HI_Default_Camera(_hoops_IGHCR, _hoops_HGHCR);

			if (_hoops_PAHCR != 0.0f) {
				HI_Arbitrary_Rotate (&_hoops_IGHCR->up_vector,(Point *)&_hoops_IGHCR->_hoops_IIPCR, -_hoops_PAHCR, (Point *)&_hoops_IGHCR->_hoops_IIPCR);
				_hoops_IGHCR->_hoops_IIPCR._hoops_AAIAR();
				_hoops_IGHCR->_hoops_CRSS = _hoops_IGHCR->up_vector._hoops_SAIAR(_hoops_IGHCR->_hoops_IIPCR);
			}

			if (_hoops_HAHCR != 0.0f) {
				HI_Arbitrary_Rotate (&_hoops_IGHCR->_hoops_CRSS, (Point *)&_hoops_IGHCR->_hoops_IIPCR, _hoops_HAHCR,(Point *)&_hoops_IGHCR->_hoops_IIPCR);
				_hoops_IGHCR->_hoops_IIPCR._hoops_AAIAR();
				_hoops_IGHCR->up_vector = _hoops_IGHCR->_hoops_IIPCR._hoops_SAIAR(_hoops_IGHCR->_hoops_CRSS);
			}

			_hoops_IGHCR->position = _hoops_IGHCR->target - _hoops_IGHCR->_hoops_SRIR * _hoops_IGHCR->_hoops_IIPCR;

		} break;

		case _hoops_IAHCR: {

			float	_hoops_PAHCR = _hoops_IGHCR->position.x;
			float	_hoops_HAHCR = _hoops_IGHCR->position.y;

			if (_hoops_HGHCR != null && _hoops_PAHCR == 0.0f && _hoops_HAHCR == 0.0f)
				return null;

			HI_Default_Camera(_hoops_IGHCR, _hoops_HGHCR);

			if (_hoops_PAHCR != 0.0f) {
				HI_Arbitrary_Rotate (&_hoops_IGHCR->up_vector,(Point *)&_hoops_IGHCR->_hoops_IIPCR, _hoops_PAHCR,(Point *)&_hoops_IGHCR->_hoops_IIPCR);
				_hoops_IGHCR->_hoops_IIPCR._hoops_AAIAR();
				_hoops_IGHCR->_hoops_CRSS = _hoops_IGHCR->up_vector._hoops_SAIAR(_hoops_IGHCR->_hoops_IIPCR);
			}

			if (_hoops_HAHCR != 0.0f) {
				HI_Arbitrary_Rotate (&_hoops_IGHCR->_hoops_CRSS, (Point *)&_hoops_IGHCR->_hoops_IIPCR, -_hoops_HAHCR,(Point *)&_hoops_IGHCR->_hoops_IIPCR);
				_hoops_IGHCR->_hoops_IIPCR._hoops_AAIAR();
				_hoops_IGHCR->up_vector = _hoops_IGHCR->_hoops_IIPCR._hoops_SAIAR(_hoops_IGHCR->_hoops_CRSS);
			}

			_hoops_IGHCR->target = _hoops_IGHCR->position + _hoops_IGHCR->_hoops_SRIR * _hoops_IGHCR->_hoops_IIPCR;

		} break;

		case _hoops_CAHCR: {

			float	_hoops_APCH = 1.0f/_hoops_IGHCR->position.x;

			HI_Default_Camera(_hoops_IGHCR, _hoops_HGHCR);

			_hoops_IGHCR->_hoops_ARSS *= _hoops_APCH;
			_hoops_IGHCR->_hoops_PRSS *= _hoops_APCH;
			_hoops_IGHCR->_hoops_ISPA  *= _hoops_APCH;
			_hoops_IGHCR->_hoops_SSPA *= _hoops_APCH;

		} break;

		case _hoops_SAHCR: {

			Point	delta = _hoops_IGHCR->position;

			if (_hoops_HGHCR != null && delta.x == 0.0f && delta.y == 0.0f && delta.z == 0.0f)
				return null;

			HI_Default_Camera(_hoops_IGHCR, _hoops_HGHCR);

			// _hoops_SSH _hoops_AGRP _hoops_CGH _hoops_GPHCR _hoops_IGIAR _hoops_RHC, _hoops_HAPC _hoops_AGRP _hoops_IGIAR _hoops_GH _hoops_AAGA, _hoops_PPR _hoops_SISR _hoops_AGRP _hoops_IGIAR (_hoops_GH _hoops_SISR _hoops_RHC). 

			Vector d(0,0,0);

			if (delta.z != 0.0f) {
				d.x += delta.z * _hoops_IGHCR->_hoops_IIPCR.x;
				d.y += delta.z * _hoops_IGHCR->_hoops_IIPCR.y;
				d.z += delta.z * _hoops_IGHCR->_hoops_IIPCR.z;
			}

			if (delta.y != 0.0f) {
				d.x += delta.y * _hoops_IGHCR->up_vector.x;
				d.y += delta.y * _hoops_IGHCR->up_vector.y;
				d.z += delta.y * _hoops_IGHCR->up_vector.z;
			}

			if (delta.x != 0.0f) {
				d.x += delta.x * _hoops_IGHCR->_hoops_CRSS.x;
				d.y += delta.x * _hoops_IGHCR->_hoops_CRSS.y;
				d.z += delta.x * _hoops_IGHCR->_hoops_CRSS.z;
			}

			_hoops_IGHCR->position += d;
			_hoops_IGHCR->target += d;

		} break;

		default: ASSERT(0); break;
	}

	_hoops_HCPCR (_hoops_RIGC, _hoops_IGHCR, _hoops_SRCP);

	return _hoops_IGHCR;
}

local bool _hoops_RPHCR(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HHRA &				_hoops_APHCR,
	Point const *			position,
	Point const *			target,
	Vector const *			up_vector,
	float					width,
	float					height,
	char const *			proj)
{

	ZERO_STRUCT (&_hoops_APHCR, _hoops_HHRA);
	_hoops_APHCR.position = *position;
	_hoops_APHCR.target = *target;
	_hoops_APHCR.up_vector = *up_vector;
	_hoops_APHCR._hoops_ISPA = width;
	_hoops_APHCR._hoops_SSPA = height;
	_hoops_APHCR._hoops_CIPCR = 0.0f;
	_hoops_APHCR._hoops_SIPCR = &HOOPS_WORLD->_hoops_GCPCR;
	_hoops_APHCR._hoops_CSIH = height / width;
	_hoops_APHCR._hoops_IIPCR = _hoops_APHCR.target - _hoops_APHCR.position;
	_hoops_APHCR._hoops_SRIR = _hoops_APHCR._hoops_IIPCR.length();

	if (!HI_Normalize (&_hoops_APHCR._hoops_IIPCR)) {
		HE_ERROR (HEC_CAMERA, HES_BAD_POSITION,"Requested camera position is on top of camera target");
		return false;
	}

	/* _hoops_HHGC _hoops_RHC _hoops_SISR (_hoops_GH _hoops_SISR _hoops_RHC) */

	_hoops_APHCR.up_vector = _hoops_APHCR.up_vector._hoops_SAIAR(_hoops_APHCR._hoops_IIPCR);
	_hoops_APHCR.up_vector = _hoops_APHCR._hoops_IIPCR._hoops_SAIAR(_hoops_APHCR.up_vector);

	if (!HI_Normalize (&_hoops_APHCR.up_vector)) {
		if (up_vector->x == 0.0f && up_vector->y == 0.0f && up_vector->z == 0.0f)
			HE_ERROR (HEC_CAMERA, HES_BAD_UP_VECTOR, "Requested camera up vector all zeroes");
		else
			HE_ERROR (HEC_CAMERA, HES_BAD_UP_VECTOR, "Requested up vector is co-linear with line of sight");
		return false;
	}

	_hoops_APHCR._hoops_CRSS = _hoops_APHCR.up_vector._hoops_SAIAR(_hoops_APHCR._hoops_IIPCR);

	if (_hoops_APHCR._hoops_ISPA <= 0.0f) {
		HE_ERROR (HEC_CAMERA, HES_BAD_FIELD_WIDTH, "Field width is zero or negative");
		return false;
	}
	_hoops_APHCR._hoops_ARSS = _hoops_APHCR._hoops_ISPA / _hoops_APHCR._hoops_SRIR;

	if (_hoops_APHCR._hoops_SSPA <= 0.0f) {
		HE_ERROR (HEC_CAMERA, HES_BAD_FIELD_HEIGHT, "Field height is zero or negative");
		return false;
	}
	_hoops_APHCR._hoops_PRSS = _hoops_APHCR._hoops_SSPA / _hoops_APHCR._hoops_SRIR;

	if (!_hoops_PHPCR (_hoops_RIGC, proj, &_hoops_APHCR))
		return false;

	return true;
}

GLOBAL_FUNCTION bool HI_Set_Camera (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	_hoops_HHRA *				_hoops_SPH)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_CAMERA, _hoops_PGHCR, _hoops_SPH);
}



HC_INTERFACE void HC_CDECL HC_Set_Camera (
	Point const	*	position,
	Point const	*	target,
	Vector const *	up_vector,
	double			width,
	double			height,
	char const *	proj) {

	_hoops_PAPPR context("Set_Camera");

	CODE_GENERATION (
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("HC_POINT position, target, up_vector;\n");
		HI_Dump_Code (Sprintf_FF (null, "position.x = %.6ff;  position.y = %.6ff;	 ", position->x, position->y));
		HI_Dump_Code (Sprintf_F (null, "position.z = %.6ff;\n", position->z));
		HI_Dump_Code (Sprintf_FF (null, "target.x = %.6ff;	 target.y = %.6ff;	 ", target->x, target->y));
		HI_Dump_Code (Sprintf_F (null, "target.z = %.6ff;\n", target->z));
		HI_Dump_Code (Sprintf_FF (null, "up_vector.x = %.6ff;	up_vector.y = %.6ff;  ", up_vector->x, up_vector->y));
		HI_Dump_Code (Sprintf_F (null, "up_vector.z = %.6ff;\n", up_vector->z));
		HI_Dump_Code (Sprintf_FF (null, "HC_Set_Camera (&position, &target, &up_vector, %.6Ff, %.6Ff, ", width, height));
		HI_Dump_Code (Sprintf_S (null, "%S);\n", proj));
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("\n}");
	);

	bool		used = false;
	_hoops_HHRA *	_hoops_SPH;
	ZALLOC (_hoops_SPH, _hoops_HHRA);

	if (_hoops_RPHCR(context, *_hoops_SPH, position, target, up_vector, (float)width, (float)height, proj)) {

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_PPHCR)) != null) {
			used = HI_Set_Camera(context, target, _hoops_SPH);
			_hoops_IRRPR();
		}
	}

	if (!used)
		FREE (_hoops_SPH, _hoops_HHRA);

}

HC_INTERFACE void HC_CDECL HC_UnSet_Camera (void) 
{
	_hoops_PAPPR context("UnSet_Camera");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Camera ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PPHCR|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute (context, target, HK_CAMERA);
		_hoops_IRRPR();
	}
	
}


GLOBAL_FUNCTION void HI_Set_Camera_Near_Limit (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	float					limit)
{
	_hoops_HHRA *	_hoops_SPH;
	ZALLOC (_hoops_SPH, _hoops_HHRA);

	_hoops_SPH->_hoops_RRHH = _hoops_SRHCR;
	_hoops_SPH->_hoops_CIPCR = limit;

	if (!HI_Set_Camera (_hoops_RIGC, item, _hoops_SPH))
		FREE (_hoops_SPH, _hoops_HHRA);
}


HC_INTERFACE void HC_CDECL HC_Set_Camera_Near_Limit (
	double			ilimit)
{
	_hoops_PAPPR context("Set_Camera_Near_Limit");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_F (null, "HC_Set_Camera_Near_Limit (%.6Ff);\n", ilimit));
	);

	float	limit = (float)ilimit;

	if (limit < -1.0f || limit > 1.0f) {
		HE_ERROR (HEC_CAMERA, HES_INVALID_RANGE, "Invalid camera near limit, should be from -1 to 1");
		return;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PPHCR)) != null) {
		HI_Set_Camera_Near_Limit(context, target, limit);
		_hoops_IRRPR();
	}

}




GLOBAL_FUNCTION void HI_UnSet_Camera_Near_Limit (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH * 				item) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_CRCP * _hoops_SRCP = (_hoops_CRCP *)item;

	ASSERT(!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR));
	ASSERT(_hoops_SRCP->type == _hoops_IRCP);

	Attribute *	_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR;

	if (_hoops_HPHCR != null) {
		do if (_hoops_HPHCR->type >= HK_CAMERA) {
			if (_hoops_HPHCR->type == HK_CAMERA)
				((_hoops_HHRA alter *)_hoops_HPHCR)->_hoops_SIPCR = &HOOPS_WORLD->_hoops_GCPCR;
			break;
		} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
	}
}


HC_INTERFACE void HC_CDECL HC_UnSet_Camera_Near_Limit ()
{
	_hoops_PAPPR context("UnSet_Camera_Near_Limit");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Camera_Near_Limit ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PPHCR|_hoops_GSIIR)) != null) {
		HI_UnSet_Camera_Near_Limit (context, target);
		_hoops_IRRPR();
	}
#endif
}


GLOBAL_FUNCTION void HI_Set_Camera_By_Volume (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	char const *			proj,
	float					xmin,
	float					xmax,
	float					ymin,
	float					ymax)
{
	bool		used = false;
	_hoops_HHRA *	_hoops_SPH;
	ZALLOC (_hoops_SPH, _hoops_HHRA);

	if (_hoops_PHPCR (_hoops_RIGC, proj, _hoops_SPH)) {

		_hoops_SPH->_hoops_ISPA = xmax - xmin;
		_hoops_SPH->_hoops_SSPA = ymax - ymin;
		_hoops_SPH->target.x = (xmin + xmax) * 0.5f;
		_hoops_SPH->target.y = (ymin + ymax) * 0.5f;
		_hoops_SPH->target.z = 0.0f;
		_hoops_SPH->position.x = _hoops_SPH->target.x;
		_hoops_SPH->position.y = _hoops_SPH->target.y;
		_hoops_SPH->position.z = -2.5f * _hoops_IAAA (_hoops_SPH->_hoops_ISPA, _hoops_SPH->_hoops_SSPA);
		_hoops_SPH->up_vector.x = 0.0f;
		_hoops_SPH->up_vector.y = 1.0f;
		_hoops_SPH->up_vector.z = 0.0f;
		_hoops_SPH->_hoops_IIPCR.x = 0.0f;
		_hoops_SPH->_hoops_IIPCR.y = 0.0f;
		_hoops_SPH->_hoops_IIPCR.z = 1.0f;
		_hoops_SPH->_hoops_CRSS.x = 1.0f;
		_hoops_SPH->_hoops_CRSS.y = 0.0f;
		_hoops_SPH->_hoops_CRSS.z = 0.0f;
		_hoops_SPH->_hoops_CIPCR = 0.0f;
		_hoops_SPH->_hoops_SIPCR = &HOOPS_WORLD->_hoops_GCPCR;
		_hoops_SPH->_hoops_SRIR = -_hoops_SPH->position.z;
		_hoops_SPH->_hoops_ARSS = _hoops_SPH->_hoops_ISPA / _hoops_SPH->_hoops_SRIR;
		_hoops_SPH->_hoops_PRSS = _hoops_SPH->_hoops_SSPA / _hoops_SPH->_hoops_SRIR;
		_hoops_SPH->_hoops_CSIH = _hoops_SPH->_hoops_SSPA / _hoops_SPH->_hoops_ISPA;

		used = HI_Set_Camera (_hoops_RIGC, item, _hoops_SPH);
	}

	if (!used)
		FREE (_hoops_SPH, _hoops_HHRA);
}


HC_INTERFACE void HC_CDECL HC_Set_Camera_By_Volume (
	char const *	proj,
	double			xmin,
	double			xmax,
	double			ymin,
	double			ymax)
{
	_hoops_PAPPR context("Set_Camera_By_Volume");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Camera_By_Volume (%S, ", proj));
		HI_Dump_Code (Sprintf_FF (null, "%.6Ff, %.6Ff, ", xmin, xmax));
		HI_Dump_Code (Sprintf_FF (null, "%.6Ff, %.6Ff);\n", ymin, ymax));
	);

	if (xmin >= xmax) {
		HE_ERROR (HEC_CAMERA, HES_BAD_XMIN, "Xmin is equal to or greater than Xmax");
		return;
	}

	if (ymin >= ymax) {
		HE_ERROR (HEC_CAMERA, HES_BAD_YMIN, "Ymin is equal to or greater than Ymax");
		return;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PPHCR)) != null) {
		HI_Set_Camera_By_Volume (context, target, proj, (float)xmin, (float)xmax, (float)ymin, (float)ymax);
		_hoops_IRRPR();
	}

}


GLOBAL_FUNCTION void HI_Set_Camera_Field (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	float					width,
	float					height)
{
	_hoops_HHRA *	_hoops_SPH;
	ZALLOC (_hoops_SPH, _hoops_HHRA);

	_hoops_SPH->_hoops_RRHH = _hoops_IRHCR;
	_hoops_SPH->_hoops_ISPA = width;
	_hoops_SPH->_hoops_SSPA = height;

	if (!HI_Set_Camera (_hoops_RIGC, item, _hoops_SPH))
		FREE (_hoops_SPH, _hoops_HHRA);
}


HC_INTERFACE void HC_CDECL HC_Set_Camera_Field (
	double			width,
	double			height)
{
	_hoops_PAPPR context("Set_Camera_Field");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "HC_Set_Camera_Field (%.6Ff, %.6Ff);\n", width, height));
	);

	if (width <= 0.0) {
		HE_ERROR (HEC_CAMERA, HES_BAD_FIELD_WIDTH, "Field width is zero or negative");
		return;
	}

	if (height <= 0.0) {
		HE_ERROR (HEC_CAMERA, HES_BAD_FIELD_HEIGHT, "Field height is zero or negative");
		return;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PPHCR)) != null) {
		HI_Set_Camera_Field (context, target, (float)width, (float)height);
		_hoops_IRRPR();
	}

}



GLOBAL_FUNCTION void HI_Set_Camera_Position (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	Point const *			point)
{
	_hoops_HHRA * _hoops_SPH;
	ZALLOC (_hoops_SPH, _hoops_HHRA);
	_hoops_SPH->_hoops_RRHH = _hoops_SGHCR;
	_hoops_SPH->position = *point;

	if (!HI_Set_Camera (_hoops_RIGC, item, _hoops_SPH))
		FREE (_hoops_SPH, _hoops_HHRA);
}



HC_INTERFACE void HC_CDECL HC_Set_Camera_Position (
	double			x,
	double			y,
	double			z)
{
	_hoops_PAPPR context("Set_Camera_Position");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "HC_Set_Camera_Position (%.6Ff, %.6Ff, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%.6Ff);\n", z));
	);

	Point	position(x,y,z);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PPHCR)) != null) {
		HI_Set_Camera_Position (context, target, &position);
		_hoops_IRRPR();
	}
}


GLOBAL_FUNCTION void HI_Set_Camera_Projection (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	char const *			proj)
{
	bool		used = false;
	_hoops_HHRA *	_hoops_SPH;
	ZALLOC (_hoops_SPH, _hoops_HHRA);

	if (_hoops_PHPCR (_hoops_RIGC, proj, _hoops_SPH)) {
		_hoops_SPH->_hoops_RRHH = _hoops_CRHCR;
		used = HI_Set_Camera (_hoops_RIGC, item, _hoops_SPH);
	}

	if (!used)
		FREE (_hoops_SPH, _hoops_HHRA);
}


HC_INTERFACE void HC_CDECL HC_Set_Camera_Projection (
	char const *	proj)
{
	_hoops_PAPPR context("Set_Camera_Projection");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Camera_Projection (%S);\n", proj));
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PPHCR)) != null) {
		HI_Set_Camera_Projection (context, target, proj);
		_hoops_IRRPR();
	}
}


GLOBAL_FUNCTION void HI_Set_Camera_Target (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	Point const *			target)
{
	_hoops_HHRA * _hoops_SPH;
	ZALLOC (_hoops_SPH, _hoops_HHRA);

	_hoops_SPH->_hoops_RRHH = _hoops_PRHCR;
	_hoops_SPH->target = *target;

	if (!HI_Set_Camera (_hoops_RIGC, item, _hoops_SPH))
		FREE (_hoops_SPH, _hoops_HHRA);
}


HC_INTERFACE void HC_CDECL HC_Set_Camera_Target (
	double			x,
	double			y,
	double			z)
{
	_hoops_PAPPR context("Set_Camera_Target");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "HC_Set_Camera_Target (%.6Ff, %.6Ff, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%.6Ff);\n", z));
	);

	Point	point(x,y,z);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PPHCR)) != null) {
		HI_Set_Camera_Target (context, target, &point);
		_hoops_IRRPR();
	}

}


GLOBAL_FUNCTION void HI_Set_Camera_Up_Vector (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	Vector const *			up_vector)
{
	_hoops_HHRA * _hoops_SPH;
	ZALLOC (_hoops_SPH, _hoops_HHRA);

	_hoops_SPH->_hoops_RRHH = _hoops_HRHCR;
	_hoops_SPH->up_vector = *up_vector;

	if (!HI_Set_Camera (_hoops_RIGC, item, _hoops_SPH))
		FREE (_hoops_SPH, _hoops_HHRA);
}


HC_INTERFACE void HC_CDECL HC_Set_Camera_Up_Vector (
	double			x,
	double			y,
	double			z)
{
	_hoops_PAPPR context("Set_Camera_Up_Vector");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "HC_Set_Camera_Up_Vector (%.6Ff, %.6Ff, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%.6Ff);\n", z));
	);

	Vector up_vector(x,y,z);

	if (up_vector.x == 0.0f && up_vector.y == 0.0f && up_vector.z == 0.0f) {
		HE_ERROR (HEC_CAMERA, HES_BAD_UP_VECTOR, "Specified Up vector is all zeroes");
		return;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PPHCR)) != null) {
		HI_Set_Camera_Up_Vector (context, target, &up_vector);
		_hoops_IRRPR();
	}

}

GLOBAL_FUNCTION void HI_Zoom_Camera (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	float					_hoops_APCH)
{
	_hoops_HHRA * _hoops_SPH;
	ZALLOC (_hoops_SPH, _hoops_HHRA);

	_hoops_SPH->_hoops_RRHH = _hoops_CAHCR;
	_hoops_SPH->position.x = _hoops_APCH;

	if (!HI_Set_Camera (_hoops_RIGC, item, _hoops_SPH))
		FREE (_hoops_SPH, _hoops_HHRA);
}



HC_INTERFACE void HC_CDECL HC_Zoom_Camera (
	double			izoom)
{
	_hoops_PAPPR context("Zoom_Camera");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_F (null, "HC_Zoom_Camera (%.6Ff);\n", izoom));
	);

	float	_hoops_APCH = (float)izoom;

	if (_hoops_APCH <= 0.0f) {
		HE_ERROR2 (HEC_CAMERA, HES_INVALID_ZOOM_FACTOR,
			_hoops_APCH == 0.0f ?
			"Unreasonable (zero!) zoom factor -" :
			"Unreasonable (negative!) zoom factor -",
			"(less than 1 ==> smaller, greater than 1 ==> larger)");
		return;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PPHCR)) != null) {
		HI_Zoom_Camera (context, target, _hoops_APCH);
		_hoops_IRRPR();
	}

}


GLOBAL_FUNCTION void HI_Roll_Camera (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	float					_hoops_RAHCR)
{
	_hoops_HHRA *	_hoops_SPH;
	ZALLOC (_hoops_SPH, _hoops_HHRA);

	_hoops_SPH->_hoops_RRHH = _hoops_GAHCR;
	_hoops_SPH->position.x = _hoops_RAHCR;

	if (!HI_Set_Camera (_hoops_RIGC, item, _hoops_SPH))
		FREE (_hoops_SPH, _hoops_HHRA);
}


HC_INTERFACE void HC_CDECL HC_Roll_Camera (
	double			_hoops_RAHCR)
{
	_hoops_PAPPR context("Roll_Camera");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_F (null, "HC_Roll_Camera (%.6Ff);\n", _hoops_RAHCR));
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PPHCR)) != null) {
		HI_Roll_Camera (context, target, (float)_hoops_RAHCR);
		_hoops_IRRPR();
	}
}

GLOBAL_FUNCTION void HI_Pan_Camera (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	float					_hoops_PAHCR,
	float					_hoops_HAHCR)
{
	_hoops_HHRA * _hoops_SPH;
	ZALLOC (_hoops_SPH, _hoops_HHRA);

	_hoops_SPH->_hoops_RRHH = _hoops_IAHCR;
	_hoops_SPH->position.x = _hoops_PAHCR;
	_hoops_SPH->position.y = _hoops_HAHCR;

	if (!HI_Set_Camera (_hoops_RIGC, item, _hoops_SPH))
		FREE (_hoops_SPH, _hoops_HHRA);
}


HC_INTERFACE void HC_CDECL HC_Pan_Camera (
	double			_hoops_PAHCR,
	double			_hoops_HAHCR)
{
	_hoops_PAPPR context("Pan_Camera");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "HC_Pan_Camera (%.6Ff, %.6Ff);\n", _hoops_PAHCR, _hoops_HAHCR));
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PPHCR)) != null) {
		HI_Pan_Camera (context, target, (float)_hoops_PAHCR, (float)_hoops_HAHCR);
		_hoops_IRRPR();
	}

}

GLOBAL_FUNCTION void HI_Orbit_Camera (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	float					_hoops_PAHCR,
	float					_hoops_HAHCR)
{
	_hoops_HHRA * _hoops_SPH;
	ZALLOC (_hoops_SPH, _hoops_HHRA);

	_hoops_SPH->_hoops_RRHH = _hoops_AAHCR;
	_hoops_SPH->position.x = _hoops_PAHCR;
	_hoops_SPH->position.y = _hoops_HAHCR;

	if (!HI_Set_Camera (_hoops_RIGC, item, _hoops_SPH))
		FREE (_hoops_SPH, _hoops_HHRA);
}



HC_INTERFACE void HC_CDECL HC_Orbit_Camera (
	double			_hoops_PAHCR,
	double			_hoops_HAHCR)
{
	_hoops_PAPPR context("Orbit_Camera");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "HC_Orbit_Camera (%.6Ff, %.6Ff);\n", _hoops_PAHCR, _hoops_HAHCR));
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PPHCR)) != null) {
		HI_Orbit_Camera (context, target, (float)_hoops_PAHCR, (float)_hoops_HAHCR);
		_hoops_IRRPR();
	}
}


GLOBAL_FUNCTION void HI_Dolly_Camera (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	Point const *			point)
{
	_hoops_HHRA * _hoops_SPH;
	ZALLOC (_hoops_SPH, _hoops_HHRA);

	_hoops_SPH->_hoops_RRHH = _hoops_SAHCR;
	_hoops_SPH->position = *point;

	if (!HI_Set_Camera (_hoops_RIGC, item, _hoops_SPH))
		FREE (_hoops_SPH, _hoops_HHRA);
}

HC_INTERFACE void HC_CDECL HC_Dolly_Camera (
	double			x,
	double			y,
	double			z)
{
	_hoops_PAPPR context("Dolly_Camera");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "HC_Dolly_Camera (%.6Ff, %.6Ff, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%.6Ff);\n", z));
	);

	Point		_hoops_IPHCR(x,y,z);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PPHCR)) != null) {
		HI_Dolly_Camera (context, target, &_hoops_IPHCR);
		_hoops_IRRPR();
	}

}





#ifndef DISABLE_SHOW

local void _hoops_CPHCR (
	_hoops_HHRA *				_hoops_SPH,
	char *					proj,
	int						_hoops_SPHCR) {
	local const char		ortho[] = "orthographic",
							_hoops_GHHCR[] = "perspective",
							_hoops_RHHCR[] = "stretched";

	if (_hoops_SPH->_hoops_HHCH == 0.0f &&
		_hoops_SPH->_hoops_IHCH == 0.0f) {
		if (_hoops_SPH->projection == _hoops_CPPCR)
			HI_Return_Chars (proj, _hoops_SPHCR, ortho, 12);
		else if (_hoops_SPH->projection == _hoops_GHH)
			HI_Return_Chars (proj, _hoops_SPHCR, _hoops_GHHCR, 11);
		else
			HI_Return_Chars (proj, _hoops_SPHCR, _hoops_RHHCR, 9);
	}
	else {
		char					buf[100];
		char					*_hoops_ASAPR = buf;

		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, buf+_hoops_GGAPR(buf), "oblique %s=",
						  (void *)((_hoops_SPH->projection == _hoops_CPPCR) ? ortho :
								   (_hoops_SPH->projection == _hoops_GHH) ?	 _hoops_GHHCR :
								   _hoops_RHHCR));

		if (_hoops_SPH->_hoops_IHCH == 0.0f) {
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, buf+_hoops_GGAPR(buf), "%f",
							  (void *)&_hoops_SPH->_hoops_HHCH);
		}
		else {
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, buf+_hoops_GGAPR(buf), "(%f,",
							  (void *)&_hoops_SPH->_hoops_HHCH);
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, buf+_hoops_GGAPR(buf), "%f)",
							  (void *)&_hoops_SPH->_hoops_IHCH);
		}

		HI_Return_Chars (proj, _hoops_SPHCR, buf, _hoops_ASAPR - buf);
	}
}

local void _hoops_AHHCR (
	_hoops_HHRA		* _hoops_SPH,
	Point		* position,
	Point		* target,
	Vector		* up_vector,
	float		* width,
	float		* height,
	char		* proj,
	int			_hoops_SPHCR) {

	if (position)
		*position = _hoops_SPH->position;
	if (target)
		*target = _hoops_SPH->target;
	if (up_vector)
		*up_vector = _hoops_SPH->up_vector;
	if (width)
		*width = _hoops_SPH->_hoops_ISPA;
	if (height)
		*height = _hoops_SPH->_hoops_SSPA;
	if (proj)
		_hoops_CPHCR (_hoops_SPH, proj, _hoops_SPHCR);
}

#endif

HC_INTERFACE void HC_CDECL HC_Show_Camera (
	Point *		position,
	Point *		_hoops_PHHCR,
	Vector *	up_vector,
	float *		width,
	float *		height,
	char *		proj)
{
	_hoops_PAPPR context("Show_Camera");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Camera () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HHHCR)) != null) {
		_hoops_HHRA *	_hoops_SPH;
		if ((_hoops_SPH = (_hoops_HHRA *)HI_Find_Attribute (context, target, HK_CAMERA)) != null) {
			_hoops_AHHCR (_hoops_SPH, position, _hoops_PHHCR, up_vector, width, height, proj, -1);
			_hoops_HPRH (_hoops_SPH);
		}
		_hoops_IRRPR();
	}
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Camera_Field (
	float *			width,
	float *			height)
{
	_hoops_PAPPR context("Show_Camera_Field");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Camera_Field () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HHHCR)) != null) {

		_hoops_HHRA *	_hoops_SPH;
		if ((_hoops_SPH = (_hoops_HHRA *)HI_Find_Attribute (context, target, HK_CAMERA)) != null) {
			*width = _hoops_SPH->_hoops_ISPA;
			*height = _hoops_SPH->_hoops_SSPA;
			_hoops_HPRH (_hoops_SPH);
		}
		_hoops_IRRPR();
	}
#endif
}


HC_INTERFACE bool HC_CDECL HC_Show_Camera_Near_Limit (
	float *			limit)
{
	_hoops_PAPPR context("Show_Camera_Near_Limit");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return false;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Camera_Near_Limit () */\n");
	);

	bool	_hoops_IHHCR = false;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HHHCR)) != null) {

		_hoops_HHRA *	_hoops_SPH;
		if ((_hoops_SPH = (_hoops_HHRA *)HI_Find_Attribute (context, target, HK_CAMERA)) != null) {
			*limit = *_hoops_SPH->_hoops_SIPCR;
			_hoops_IHHCR = (_hoops_SPH->_hoops_SIPCR != &HOOPS_WORLD->_hoops_GCPCR);
			_hoops_HPRH (_hoops_SPH);
		}
		_hoops_IRRPR();
	}

	return _hoops_IHHCR;
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Camera_Position (
	float *			x,
	float *			y,
	float *			z)
{
	_hoops_PAPPR context("Show_Camera_Position");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Camera_Position () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HHHCR)) != null) {
		_hoops_HHRA *	_hoops_SPH;
		if ((_hoops_SPH = (_hoops_HHRA *)HI_Find_Attribute (context, target, HK_CAMERA)) != null) {
			*x = _hoops_SPH->position.x;
			*y = _hoops_SPH->position.y;
			*z = _hoops_SPH->position.z;
			_hoops_HPRH (_hoops_SPH);
		}
		_hoops_IRRPR();
	}
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Camera_Projection (
	char *		proj)
{
	_hoops_PAPPR context("Show_Camera_Projection");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Camera_Projection () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HHHCR)) != null) {
		_hoops_HHRA *	_hoops_SPH;
		if ((_hoops_SPH = (_hoops_HHRA *)HI_Find_Attribute (context, target, HK_CAMERA)) != null) {
			_hoops_CPHCR (_hoops_SPH, proj, -1);
			_hoops_HPRH (_hoops_SPH);
		}
		_hoops_IRRPR();
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Camera_Target (
	float *			x,
	float *			y,
	float *			z)
{
	_hoops_PAPPR context("Show_Camera_Target");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Camera_Target () */\n");
	);


	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HHHCR)) != null) {
		_hoops_HHRA *	_hoops_SPH;
		if ((_hoops_SPH = (_hoops_HHRA *)HI_Find_Attribute (context, target, HK_CAMERA)) != null) {
			*x = _hoops_SPH->target.x;
			*y = _hoops_SPH->target.y;
			*z = _hoops_SPH->target.z;
			_hoops_HPRH (_hoops_SPH);
		}
		_hoops_IRRPR();
	}
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Camera_Up_Vector (
	float *			x,
	float *			y,
	float *			z)
{
	_hoops_PAPPR context("Show_Camera_Up_Vector");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Camera_Up_Vector () */\n");
	);


	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HHHCR)) != null) {
		_hoops_HHRA *	_hoops_SPH;
		if ((_hoops_SPH = (_hoops_HHRA *)HI_Find_Attribute (context, target, HK_CAMERA)) != null) {
			*x = _hoops_SPH->up_vector.x;
			*y = _hoops_SPH->up_vector.y;
			*z = _hoops_SPH->up_vector.z;
			_hoops_HPRH (_hoops_SPH);
		}
		_hoops_IRRPR();
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Camera_By_Volume (
	char *				proj,
	float *				xmin,
	float *				xmax,
	float *				ymin,
	float *				ymax)
{
	_hoops_PAPPR context("Show_Camera_By_Volume");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Camera_By_Volume () */\n");
	);


	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HHHCR)) != null) {

		_hoops_HHRA *	_hoops_SPH;
		if ((_hoops_SPH = (_hoops_HHRA *)HI_Find_Attribute (context, target, HK_CAMERA)) != null) {
			if (_hoops_SPH->target.x != _hoops_SPH->position.x ||
				_hoops_SPH->target.y != _hoops_SPH->position.y ||
				_hoops_SPH->target.z <= _hoops_SPH->position.z ||
				_hoops_SPH->up_vector.y < 0.999f) {

					HE_ERROR (HEC_CAMERA, HES_NOT_A_CAMERA_VOLUME,
						Sprintf_P (null, "The Camera for '%p' is not a Camera Volume", _hoops_SPH->owner));
			}
			else {
				*xmin = _hoops_SPH->target.x - _hoops_SPH->_hoops_ISPA * 0.5f;
				*xmax = _hoops_SPH->target.x + _hoops_SPH->_hoops_ISPA * 0.5f;
				*ymin = _hoops_SPH->target.y - _hoops_SPH->_hoops_SSPA * 0.5f;
				*ymax = _hoops_SPH->target.y + _hoops_SPH->_hoops_SSPA * 0.5f;

				_hoops_CPHCR (_hoops_SPH, proj, -1);
			}

			_hoops_HPRH (_hoops_SPH);
		}
		_hoops_IRRPR();
	}
#endif
}



#ifndef _hoops_ARPCR


HC_INTERFACE void HC_CDECL HC_PShow_Net_Camera (
	int				count,
	Key const *		keys,
	Point *			position,
	Point *			target,
	Vector *		up_vector,
	float *			width,
	float *			height,
	char *			proj)
{
	_hoops_PAPPR context("PShow_Net_Camera");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Camera () */\n");
	);

	_hoops_HHRA *	_hoops_SPH;
	if ((_hoops_SPH = (_hoops_HHRA *) HI_Find_Attribute_And_Lock(context, _hoops_HHHCR, _hoops_HRPCR, count, keys)) != null) {
		*position = _hoops_SPH->position;
		*target = _hoops_SPH->target;
		*up_vector = _hoops_SPH->up_vector;
		*width = _hoops_SPH->_hoops_ISPA;
		*height = _hoops_SPH->_hoops_SSPA;
		_hoops_CPHCR (_hoops_SPH, proj, -1);
		_hoops_HPRH (_hoops_SPH);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(proj, -1, "", 0);
#endif
}

#endif


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Camera_Field (
	int				count,
	Key const *		keys,
	float *			width,
	float *			height)
{
	_hoops_PAPPR context("PShow_Net_Camera_Field");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Camera_Field () */\n");
	);

	_hoops_HHRA *	_hoops_SPH;
	if ((_hoops_SPH = (_hoops_HHRA *) HI_Find_Attribute_And_Lock(context, _hoops_HHHCR, _hoops_HRPCR, count, keys)) != null) {
		*width = _hoops_SPH->_hoops_ISPA;
		*height = _hoops_SPH->_hoops_SSPA;
		_hoops_HPRH (_hoops_SPH);
		_hoops_IRRPR();
	}
#endif
}
#endif


#ifndef _hoops_ARPCR
HC_INTERFACE bool HC_CDECL HC_PShow_Net_Camera_Near_Limit (
	int				count,
	Key const *		keys,
	float *			limit)
{
	_hoops_PAPPR context("PShow_Net_Camera_Near_Limit");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
	return false;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Camera_Near_Limit () */\n");
	);

	bool		_hoops_IHHCR = false;
	_hoops_HHRA *	_hoops_SPH;
	if ((_hoops_SPH = (_hoops_HHRA *) HI_Find_Attribute_And_Lock(context, _hoops_HHHCR, _hoops_HRPCR, count, keys)) != null) {
		*limit = *_hoops_SPH->_hoops_SIPCR;
		_hoops_IHHCR = (_hoops_SPH->_hoops_SIPCR != &HOOPS_WORLD->_hoops_GCPCR);
		_hoops_HPRH (_hoops_SPH);
		_hoops_IRRPR();
	}
	
	return _hoops_IHHCR;
#endif
}
#endif


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Camera_Position (
	int				count,
	Key const *		keys,
	float *			x,
	float *			y,
	float *			z)
{
	_hoops_PAPPR context("PShow_Net_Camera_Position");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Camera_Position () */\n");
	);

	_hoops_HHRA *	_hoops_SPH;
	if ((_hoops_SPH = (_hoops_HHRA *) HI_Find_Attribute_And_Lock(context, _hoops_HHHCR, _hoops_HRPCR, count, keys)) != null) {
		*x = _hoops_SPH->position.x;
		*y = _hoops_SPH->position.y;
		*z = _hoops_SPH->position.z;
		_hoops_HPRH (_hoops_SPH);
		_hoops_IRRPR();
	}
#endif
}
#endif


#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_Net_Camera_Projection (
	int				count,
	Key const *		keys,
	char *			proj)
{
	_hoops_PAPPR context("PShow_Net_Camera_Projection");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Camera_Projection () */\n");
	);

	_hoops_HHRA *	_hoops_SPH;
	if ((_hoops_SPH = (_hoops_HHRA *) HI_Find_Attribute_And_Lock(context, _hoops_HHHCR, _hoops_HRPCR, count, keys)) != null) {
		_hoops_CPHCR (_hoops_SPH, proj, -1);
		_hoops_HPRH (_hoops_SPH);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(proj, -1, "", 0);
#endif
}

#endif


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Camera_Target (
	int				count,
	Key const *		keys,
	float *			x,
	float *			y,
	float *			z)
{
	_hoops_PAPPR context("PShow_Net_Camera_Target");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Camera_Target () */\n");
	);

	_hoops_HHRA *	_hoops_SPH;
	if ((_hoops_SPH = (_hoops_HHRA *) HI_Find_Attribute_And_Lock(context, _hoops_HHHCR, _hoops_HRPCR, count, keys)) != null) {
		*x = _hoops_SPH->target.x;
		*y = _hoops_SPH->target.y;
		*z = _hoops_SPH->target.z;
		_hoops_HPRH (_hoops_SPH);
		_hoops_IRRPR();
	}
#endif
}
#endif


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Camera_Up_Vector (
	int				count,
	Key const *		keys,
	float *			x,
	float *			y,
	float *			z)
{
	_hoops_PAPPR context("PShow_Net_Camera_Up_Vector");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Camera_Up_Vector () */\n");
	);

	_hoops_HHRA *	_hoops_SPH;
	if ((_hoops_SPH = (_hoops_HHRA *) HI_Find_Attribute_And_Lock(context, _hoops_HHHCR, _hoops_HRPCR, count, keys)) != null) {
		*x = _hoops_SPH->up_vector.x;
		*y = _hoops_SPH->up_vector.y;
		*z = _hoops_SPH->up_vector.z;
		_hoops_HPRH (_hoops_SPH);
		_hoops_IRRPR();
	}
#endif
}
#endif



#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_Net_Camera_By_Volume (
	int					count,
	Key const *			keys,
	char *				proj,
	float *				xmin,
	float *				xmax,
	float *				ymin,
	float *				ymax)
{
	_hoops_PAPPR context("PShow_Net_Camera_By_Volume");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Camera_By_Volume () */\n");
	);

	_hoops_HHRA *	_hoops_SPH;
	if ((_hoops_SPH = (_hoops_HHRA *) HI_Find_Attribute_And_Lock(context, _hoops_HHHCR, _hoops_HRPCR, count, keys)) != null) {
		if (_hoops_SPH->target.x != _hoops_SPH->position.x ||
			_hoops_SPH->target.y != _hoops_SPH->position.y ||
			_hoops_SPH->target.z <= _hoops_SPH->position.z ||
			_hoops_SPH->up_vector.y < 0.999f) {
			HE_ERROR (HEC_CAMERA, HES_NOT_A_CAMERA_VOLUME, Sprintf_P (null, "The Camera for '%p' is not a Camera Volume", _hoops_SPH->owner));
		}
		else {
			*xmin = _hoops_SPH->target.x - _hoops_SPH->_hoops_ISPA * 0.5f;
			*xmax = _hoops_SPH->target.x + _hoops_SPH->_hoops_ISPA * 0.5f;
			*ymin = _hoops_SPH->target.y - _hoops_SPH->_hoops_SSPA * 0.5f;
			*ymax = _hoops_SPH->target.y + _hoops_SPH->_hoops_SSPA * 0.5f;
			_hoops_CPHCR (_hoops_SPH, proj, -1);
		}
		_hoops_HPRH (_hoops_SPH);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(proj, -1, "", 0);
#endif
}

#endif






GLOBAL_FUNCTION bool HI_Camera_To_Transform (
	_hoops_HHRA alter *			_hoops_SPH,
	double					_hoops_CHHCR)
{
	_hoops_RPRA alter *		_hoops_SHHCR;

	if (_hoops_CHHCR == 0.0 && BIT (_hoops_SPH->_hoops_RRHH, _hoops_GIHCR))
		return (_hoops_SPH->_hoops_SRIR != 0.0f);

	_hoops_SPH->_hoops_RRHH |= _hoops_GIHCR;

	/*
	 * _hoops_SSSA _hoops_RH _hoops_RIHCR _hoops_PRGGR _hoops_IIGR _hoops_RH _hoops_SARA
	 */

	if (_hoops_SPH->_hoops_SRIR == 0.0f) {
		HE_ERROR (HEC_CAMERA, HES_BAD_POSITION,
				Sprintf_P (null, "Camera position in segment '%p' is right on top of camera target",
				_hoops_SPH->owner));

		/* _hoops_CISA _hoops_GGR, _hoops_SAHR _hoops_GGR _hoops_AGIR */
		HI_Ident_Matrix (&_hoops_SPH->_hoops_PRPA);
		HI_Ident_Matrix (&_hoops_SPH->_hoops_AIIH);
		HI_Ident_Matrix (&_hoops_SPH->_hoops_GRCC);

		return false;
	}

	/*
	 * _hoops_IPCP _hoops_RIHCR _hoops_RSGA _hoops_PAH _hoops_SHH _hoops_AIHCR _hoops_GAR _hoops_IRS _hoops_AGRP _hoops_IIGR
	 * _hoops_HARGR.  _hoops_PAGAR, _hoops_SR'_hoops_GHGP _hoops_ACRR _hoops_IS _hoops_GHPHR _hoops_RH _hoops_RSGA
	 * _hoops_SSPP _hoops_HII _hoops_RH _hoops_SARA _hoops_PSPAR, _hoops_GRP _hoops_CAPR _hoops_GAR _hoops_GAGHR-_hoops_PSPAR:
	 *
	 *	  | _hoops_PIHCR _hoops_HIHCR _hoops_IIHCR 0 |	 <-- _hoops_GH _hoops_SHHP _hoops_RHC
	 *	  | _hoops_CIHCR _hoops_SIHCR _hoops_GCHCR 0 |	 <-- _hoops_GH
	 *	  | _hoops_RCHCR _hoops_ACHCR _hoops_PCHCR 0 |	 <-- _hoops_RHC
	 *	  | _hoops_HCHCR _hoops_ICHCR _hoops_CCHCR 1 |	 <-- _hoops_SAAP
	 *
	 * [_hoops_PAGA _hoops_SGS _hoops_RH _hoops_SCHCR _hoops_PIHP _hoops_SSCP _hoops_GSHCR _hoops_RSHCR _hoops_IS
	 *	_hoops_RH _hoops_SARA _hoops_PSPAR, _hoops_ASHCR _hoops_IRS _hoops_IISGR _hoops_HAPRR,
	 *	_hoops_PPR _hoops_IRS _hoops_SPR _hoops_RSHCR _hoops_IS _hoops_RH _hoops_SARA _hoops_SAAP, _hoops_IRS _hoops_PPSR,
	 *	_hoops_ASHCR _hoops_PCCP _hoops_PSHCR _hoops_HAPRR]
	 *
	 * _hoops_HSHCR _hoops_RH _hoops_RSGA _hoops_RPRAR _hoops_ISHCR _hoops_SARA _hoops_GC _hoops_GGR _hoops_CSHCR _hoops_IIGR _hoops_RH _hoops_GSSP
	 * _hoops_GC.  _hoops_HIGAR _hoops_SR'_hoops_GHGP _hoops_PII _hoops_HRGR _hoops_RH _hoops_GSSP _hoops_GC _hoops_AIHCR
	 * _hoops_GGR _hoops_CSHCR _hoops_IIGR _hoops_RH _hoops_SARA _hoops_GC.  _hoops_IPCP 3x3 _hoops_IISGR _hoops_PRGGR _hoops_IIGR _hoops_RH
	 * _hoops_RSGA _hoops_HRGR _hoops_SSHCR _hoops_GGICR; _hoops_SCH'_hoops_GRI _hoops_RGICR, _hoops_HIS _hoops_RH _hoops_AGICR
	 * _hoops_HRGR _hoops_PGICR _hoops_RH _hoops_HGICR:
	 *
	 *	  | _hoops_PIHCR _hoops_CIHCR _hoops_RCHCR 0 |
	 *	  | _hoops_HIHCR _hoops_SIHCR _hoops_ACHCR 0 |
	 *	  | _hoops_IIHCR _hoops_GCHCR _hoops_PCHCR 0 |
	 *	  | .  .  .	 1 |
	 *
	 * _hoops_PGII _hoops_SGS _hoops_IGICR _hoops_HRGR _hoops_IS _hoops_CGICR _hoops_RH _hoops_SARA _hoops_SAAP _hoops_GGR _hoops_CSHCR
	 * _hoops_IIGR _hoops_RH _hoops_CCAH _hoops_HARGR.
	 */

	_hoops_SPH->_hoops_PRPA.flags = 0;

	_hoops_SHHCR = (_hoops_RPRA alter *)_hoops_SPH->_hoops_PRPA.elements;

	_hoops_SHHCR[0][0] = _hoops_SPH->_hoops_CRSS.x;
	_hoops_SHHCR[1][0] = _hoops_SPH->_hoops_CRSS.y;
	_hoops_SHHCR[2][0] = _hoops_SPH->_hoops_CRSS.z;

	_hoops_SHHCR[0][1] = _hoops_SPH->up_vector.x;
	_hoops_SHHCR[1][1] = _hoops_SPH->up_vector.y;
	_hoops_SHHCR[2][1] = _hoops_SPH->up_vector.z;

	_hoops_SHHCR[0][2] = _hoops_SPH->_hoops_IIPCR.x;
	_hoops_SHHCR[1][2] = _hoops_SPH->_hoops_IIPCR.y;
	_hoops_SHHCR[2][2] = _hoops_SPH->_hoops_IIPCR.z;

	_hoops_SHHCR[0][3] = 0.0f;
	_hoops_SHHCR[1][3] = 0.0f;
	_hoops_SHHCR[2][3] = 0.0f;
	_hoops_SHHCR[3][3] = 1.0f;

	_hoops_SPH->_hoops_PRPA._hoops_CPH = 1.0f;
	_hoops_SPH->_hoops_PRPA._hoops_RAGR = _hoops_SGICR;

	if (_hoops_SHHCR[0][0] != 1.0f || _hoops_SHHCR[0][1] != 0.0f ||
		_hoops_SHHCR[1][0] != 0.0f || _hoops_SHHCR[1][1] != 1.0f) {

		_hoops_SPH->_hoops_PRPA._hoops_RAGR = _hoops_GRICR;

		if (_hoops_SHHCR[2][0] != 0.0f || _hoops_SHHCR[2][1] != 0.0f ||
			_hoops_SHHCR[0][2] != 0.0f || _hoops_SHHCR[1][2] != 0.0f || _hoops_SHHCR[2][2] != 1.0f)
			_hoops_SPH->_hoops_PRPA._hoops_RAGR |= _hoops_RRICR;
	}


	/*
	 * _hoops_GGAH _hoops_RH _hoops_SAAP _hoops_IS _hoops_RH _hoops_CGRS, _hoops_RPP _hoops_SIGR.
	 * _hoops_PAGA _hoops_SGS _hoops_RGR _hoops_GRS _hoops_HAGGR _hoops_ARICR.
	 */

	if (_hoops_SPH->target.x == 0.0f &&
		_hoops_SPH->target.y == 0.0f &&
		_hoops_SPH->target.z == 0.0f) {
		_hoops_SHHCR[3][0] = 0.0f;
		_hoops_SHHCR[3][1] = 0.0f;
		_hoops_SHHCR[3][2] = 0.0f;
	}
	else {
		_hoops_SHHCR[3][0] = -(_hoops_SHHCR[0][0] * _hoops_SPH->target.x +
					  _hoops_SHHCR[1][0] * _hoops_SPH->target.y +
					  _hoops_SHHCR[2][0] * _hoops_SPH->target.z);
		_hoops_SHHCR[3][1] = -(_hoops_SHHCR[0][1] * _hoops_SPH->target.x +
					  _hoops_SHHCR[1][1] * _hoops_SPH->target.y +
					  _hoops_SHHCR[2][1] * _hoops_SPH->target.z);
		_hoops_SHHCR[3][2] = -(_hoops_SHHCR[0][2] * _hoops_SPH->target.x +
					  _hoops_SHHCR[1][2] * _hoops_SPH->target.y +
					  _hoops_SHHCR[2][2] * _hoops_SPH->target.z);

		_hoops_SPH->_hoops_PRPA._hoops_RAGR |= _hoops_PRICR;
	}


	/*
	 * _hoops_SSSA _hoops_RH _hoops_PHCR _hoops_PRGGR _hoops_IIGR _hoops_RH _hoops_SARA
	 */
	HI_Figure_Scale_Matrix (2.0f / _hoops_SPH->_hoops_ISPA,
							2.0f / _hoops_SPH->_hoops_SSPA,
							1.0f / _hoops_SPH->_hoops_SRIR,
							&_hoops_SPH->_hoops_AIIH);

	if (_hoops_SPH->projection == _hoops_GHH) {
		_hoops_SPH->_hoops_AIIH.elements[2][3] =
			_hoops_SPH->_hoops_AIIH.elements[2][2];
		_hoops_SPH->_hoops_AIIH._hoops_CPH = 0.0f;
		_hoops_SPH->_hoops_AIIH._hoops_RAGR |= _hoops_HRICR;
	}

	/* _hoops_GRCH _hoops_IRICR _hoops_HRGR _hoops_CRICR _hoops_IS _hoops_GPPCR _hoops_AARI _hoops_GHCR _hoops_IRSS */
	if (_hoops_CHHCR != 0.0f) {
		float			_hoops_SHCH, _hoops_GICH;
		_hoops_RPRA alter		*proj;

		_hoops_RICH ((float)_hoops_CHHCR, _hoops_SHCH, _hoops_GICH);
		proj = (_hoops_RPRA alter *)_hoops_SPH->_hoops_AIIH.elements;

		if (_hoops_GICH != 0.0f) { /* (_hoops_SRICR-_hoops_GAICR _hoops_CGH _hoops_AIAH _hoops_HS _hoops_RAICR) */
			/*
			 * _hoops_IPCP _hoops_HSPR _hoops_HRGR _hoops_APGP _hoops_IRS _hoops_AAICR _hoops_IIGR _hoops_IRS _hoops_IASI 4-_hoops_HPP-4
			 * (_hoops_RH _hoops_PHCR _hoops_RSGA) _hoops_HPP _hoops_RH _hoops_IRICR _hoops_RSGA:
			 *
			 *	  1		0	  0		0		   _hoops_SPCR	 0	   0	 0
			 *	  0		1	  0		0	 \/	   0	 _hoops_GHCR	   0	 0
			 *	  _hoops_PAICR 0	  1		0	 /\	   0	 0	   _hoops_AHCR	 _hoops_HAICR
			 *	  0		0	  0		1		   0	 0	   0	 1
			 */
			proj[2][0] = proj[0][0] * _hoops_SHCH/_hoops_GICH;

			_hoops_SPH->_hoops_AIIH._hoops_RAGR |= _hoops_GRICR;
			_hoops_SPH->_hoops_AIIH._hoops_CPH = 0.0f;
		}
	}

	/*
	 * _hoops_IAICR _hoops_SPCR _hoops_PPR _hoops_GHCR _hoops_IH _hoops_GPPCR _hoops_CAICR.
	 * _hoops_PAGA _hoops_SGS _hoops_RGR _hoops_GRS _hoops_HAGGR _hoops_ARICR.
	 */

	if (_hoops_SPH->_hoops_HHCH != 0.0f || _hoops_SPH->_hoops_IHCH != 0.0f) {
		_hoops_HRPA		_hoops_CHCH;
		_hoops_HRPA		proj;
		float			_hoops_SHCH, _hoops_GICH;

		HI_Copy_Matrix (&_hoops_SPH->_hoops_AIIH, &proj);
		HI_Ident_Matrix (&_hoops_CHCH);

		_hoops_RICH (_hoops_SPH->_hoops_HHCH, _hoops_SHCH, _hoops_GICH);
		if (_hoops_GICH != 0.0f) {
			/*
			 * _hoops_IPCP _hoops_HSPR _hoops_HRGR _hoops_APGP _hoops_IRS _hoops_SAICR _hoops_IIGR _hoops_IRS 4-_hoops_HPP-3 _hoops_HPP
			 *
			 *	  1		0	  0		0
			 *	  0		1	  0		0
			 *	  _hoops_PAICR 0	  1		0
			 *	  0		0	  0		1
			 *
			 * _hoops_GPICR _hoops_IIHA _hoops_GPP _hoops_PCPA _hoops_SR _hoops_ACPA _hoops_AHCA _hoops_RH _hoops_CIIA
			 */
			_hoops_CHCH.elements[2][0] = _hoops_SHCH/_hoops_GICH;
		}

		_hoops_RICH (_hoops_SPH->_hoops_IHCH, _hoops_SHCH, _hoops_GICH);
		if (_hoops_GICH != 0.0f) {
			/*
			 * _hoops_RPICR _hoops_GAR _hoops_ARRS, _hoops_GRP
			 *
			 *	  1		0	  0		0
			 *	  0		1	  0		0
			 *	  0		_hoops_PAICR 1		0
			 *	  0		0	  0		1
			 */
			_hoops_CHCH.elements[2][1] = _hoops_SHCH/_hoops_GICH;
		}

		_hoops_CHCH._hoops_RAGR |= _hoops_GRICR;
		_hoops_CHCH._hoops_CPH = 0.0f;

		HI_Multiply_Matrices (&_hoops_CHCH, &proj, &_hoops_SPH->_hoops_AIIH);
	}


	/*
	 * _hoops_PISPR _hoops_SCH _hoops_HCR _hoops_GIRP
	 */
	HI_Multiply_Matrices (&_hoops_SPH->_hoops_PRPA,
						  &_hoops_SPH->_hoops_AIIH,
						  &_hoops_SPH->_hoops_GRCC);

	return true;
}



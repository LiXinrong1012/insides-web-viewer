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
 * $Id: obf_tmp.txt 1.95 2010-10-06 19:15:59 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "please.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


HC_INTERFACE int HC_CDECL HC_Compute_Selection (
	char const *			_hoops_SASHA,
	char const *			_hoops_GPSHA,
	char const *			_hoops_RPSHA,
	double					xw,
	double					yw) 
{
	_hoops_PAPPR context("Compute_Selection");

#ifdef DISABLE_SELECTION
	_hoops_IRPPR ("Selection");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Compute_Selection (%S, %S, ", _hoops_SASHA, _hoops_GPSHA));
		HI_Dump_Code (Sprintf_S (null, "%S, ", _hoops_RPSHA));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F);\n", xw, yw));
	);

	_hoops_CSPPR();
	_hoops_GGAGR *	_hoops_GHRI;
	if (!_hoops_SASHA || (_hoops_GHRI = HI_Force_Find_Driver (context, _hoops_SASHA)) == null) {
		HE_ERROR (HEC_COMPUTE, HES_DRIVER, "Unable to locate display driver");
		_hoops_IRRPR();
		return 0;
	}
	
	_hoops_CRCP *				_hoops_GHIIR;
	_hoops_APSHA			action;
	_hoops_GHAIR				_hoops_APHCR;

	if (_hoops_GPSHA == null)
		_hoops_GPSHA = "";
	while (*_hoops_GPSHA == ' ') ++_hoops_GPSHA;
	if (*_hoops_GPSHA == '\0')
		_hoops_GHIIR = null;
	else {

		_hoops_CRCP *			owner;

		_hoops_GHIIR = HI_One_Segment_Search (context, _hoops_GPSHA, true);
		if (_hoops_GHIIR == null) {
			_hoops_IRRPR();
			return 0;
		}

		owner = _hoops_GHIIR;
		_hoops_RGGA (owner == _hoops_GHRI->owner) {
			owner = owner->owner;
			if (owner->type == _hoops_PRAIR) {
				HE_ERROR (HEC_COMPUTE, HES_NOT_A_DIRECT_DESCENDANT,
						Sprintf_PP (null,"'%p' is not a direct descendant of '%p'", _hoops_GHIIR, _hoops_GHRI->owner));
				_hoops_IRRPR();
				return 0;
			}
		}
	}

	if (!HI_Process_Heuristic_Options (context, _hoops_RPSHA, &_hoops_APHCR, true)) {
		_hoops_IRRPR();
		return 0;
	}

	// _hoops_HPPC _hoops_RPP _hoops_HAR _hoops_CHIA
	if ((action = _hoops_APHCR._hoops_PPSHA) == 0)
		action = _hoops_HPSHA;

	if (xw < -1.0001f || xw > 1.0001f || yw < -1.0001f || yw > 1.0001f) {
		HE_ERROR (HEC_COMPUTE, HES_OUT_OF_RANGE_WINDOW, "Window x or y is not in the range of -1 to +1");
		_hoops_IRRPR();
		return 0;
	}

	if (action == _hoops_HPSHA)
		action |= _hoops_IPSHA;
	else if (action == _hoops_CPSHA)
		action |= _hoops_SPSHA;

	/* _hoops_RRP _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_RH _hoops_RHPP _hoops_HRGR _hoops_AGPC _hoops_CISI -- _hoops_HRHI _hoops_IGISR _hoops_GGR _hoops_GSGS _hoops_IIGR
	 * _hoops_RH _hoops_PIH _hoops_SIGR _hoops_IH _hoops_IRS _hoops_GHSHA */
	if (BIT (_hoops_GHRI->_hoops_CPGPR, _hoops_CASIR)) {		/* _hoops_PSP _hoops_PAAP _hoops_GAPR */
		_hoops_CSPPR();
		/* _hoops_RHSHA, _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_GPGR _hoops_AHSHA */
		if (BIT (_hoops_GHRI->_hoops_CPGPR, _hoops_CASIR)) 
			HI_Queue_Actor_Update(_hoops_GHRI, true);
		_hoops_IRRPR();
	}


	Selection_Event				*_hoops_GPIIR;

	ZALLOC (_hoops_GPIIR, Selection_Event);
	_hoops_GPIIR->owner = HOOPS_WORLD;
	_hoops_GPIIR->_hoops_HIHI = 1;
	_hoops_GPIIR->type = _hoops_SAIIR;
	_hoops_GPIIR->_hoops_PHSHA = HI_What_Time();
	_hoops_GPIIR->flags = _hoops_HHSHA;
	_hoops_GPIIR->_hoops_IHSHA.left	  = (float)xw;
	_hoops_GPIIR->_hoops_IHSHA.right  = (float)xw;
	_hoops_GPIIR->_hoops_IHSHA.bottom = (float)yw;
	_hoops_GPIIR->_hoops_IHSHA.top	  = (float)yw;
	_hoops_GPIIR->_hoops_IHSHA.hither = -MAX_FLOAT;
	_hoops_GPIIR->_hoops_IHSHA.yon	  = MAX_FLOAT;
	_hoops_GPIIR->_hoops_CHSHA = action;
	_hoops_GPIIR->status = ANYBIT(action, _hoops_CPSHA|_hoops_SPSHA) ? 0 : 1;
	_hoops_GPIIR->target = _hoops_GHRI;
	_hoops_PRRH (_hoops_GHRI);
	if ((_hoops_GPIIR->_hoops_GHIIR = _hoops_GHIIR) != null)
		_hoops_PRRH (_hoops_GHIIR);

	if (_hoops_APHCR.mask != 0 || _hoops_APHCR._hoops_SHSHA != -1.0f)
		_hoops_GPIIR->heuristics = &_hoops_APHCR;

	bool _hoops_GISHA = _hoops_HISAA (context, _hoops_GHRI, _hoops_RISHA, _hoops_GPIIR);
	
	_hoops_IRRPR();

	if (!_hoops_GISHA)
		_hoops_HPRH (_hoops_GPIIR);
	else if (_hoops_GPIIR->_hoops_APIIR == null)
		_hoops_HPRH (_hoops_GPIIR);
	else {
		_hoops_RPIIR				*si;
		int						count = 0;

		/* _hoops_GCRR _hoops_SCH _hoops_RH _hoops_AISHA _hoops_PGRRR! */

		if (context->_hoops_PISHA != null)
			_hoops_HPRH (context->_hoops_PISHA);
		context->_hoops_PISHA = (_hoops_HISHA *)_hoops_GPIIR;
		_hoops_GPIIR->heuristics = null;

		/* _hoops_RPR _hoops_GH */

		si = _hoops_GPIIR->_hoops_APIIR;
		do ++count;
		while ((si = si->next) != null);

		/* _hoops_HPHR _hoops_GHSHA: _hoops_ASRC _hoops_RH _hoops_HPHR _hoops_RPR */
		return count;
	}

	/* _hoops_PSP _hoops_GHSHA: _hoops_ASRC _hoops_IRS _hoops_RPR _hoops_IIGR _hoops_AHHR */
#endif
	return 0;
}

#ifndef DISABLE_SELECTION

local _hoops_GGAGR * _hoops_IISHA (void) {
	_hoops_GGAGR				*_hoops_GHRI;

	if ((_hoops_GHRI = HOOPS_WORLD->_hoops_CISHA) != null) {
		do if (!BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_SISHA) &&
				ALLBITS (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA|_hoops_RCSHA))
			return _hoops_GHRI;
		while ((_hoops_GHRI = _hoops_GHRI->_hoops_CISHA) != null);
	}

	return null;
}
#endif


HC_INTERFACE int HC_CDECL HC_Compute_Selection_By_Volume (
	char const *			_hoops_SASHA,
	char const *			_hoops_GPSHA,
	char const *			_hoops_RPSHA,
	double					left,
	double					right,
	double					bottom,
	double					top,
	double					hither,
	double					yon) 
{
	_hoops_PAPPR context("Compute_Selection_By_Volume");

#ifdef DISABLE_SELECTION
	_hoops_IRPPR ("Selection");
	return 0;
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Compute_Selection_By_Volume (%S, %S, ", _hoops_SASHA, _hoops_GPSHA));
		HI_Dump_Code (Sprintf_S (null, "%S, ", _hoops_RPSHA));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", left, right));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", bottom, top));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F);\n", hither, yon));
	);

	_hoops_GGAGR *					_hoops_GHRI;
	_hoops_CRCP *				_hoops_GHIIR;
	_hoops_APSHA			action;
	bool					_hoops_ACSHA;
	_hoops_GHAIR				_hoops_APHCR;
	bool 					_hoops_GISHA;

	if (_hoops_SASHA == null)
		_hoops_SASHA = "";
	while (*_hoops_SASHA == ' ') 
		++_hoops_SASHA;
	if (_hoops_GPSHA == null)
		_hoops_GPSHA = "";
	while (*_hoops_GPSHA == ' ')
		++_hoops_GPSHA;

	_hoops_CSPPR();

	if (*_hoops_SASHA != '\0') {
		if ((_hoops_GHRI = HI_Force_Find_Driver (context, _hoops_SASHA)) == null)
			goto Failed;
		_hoops_ACSHA = false;
	}
	else {
		/* _hoops_HPPR _hoops_IS _hoops_SSS *_hoops_GII* _hoops_PCSHA */
		if ((_hoops_GHRI = _hoops_IISHA()) == null) {
			PUSHNAME(context);
			HI_Do_Update (context, -1.0, false);
			POPNAME(context);
			if ((_hoops_GHRI = _hoops_IISHA()) == null) {
				if ((_hoops_GHRI = HI_Force_Find_Driver (context, "/driver/printf/null")) == null)
					goto Failed;
			}
		}

		_hoops_ACSHA = true;
	}

	if (*_hoops_GPSHA == '\0') {
		if (_hoops_ACSHA) {
			HE_ERROR (HEC_COMPUTE, HES_NULL_INPUT, "'display' and 'start-seg' shouldn't both be empty strings");
			goto Failed;
		}

		_hoops_GHIIR = null;
	}
	else {

		_hoops_GHIIR = HI_One_Segment_Search (context, _hoops_GPSHA, true);
		if (_hoops_GHIIR == null)
			goto Failed;

		if (!_hoops_ACSHA) {
			_hoops_CRCP *	owner = _hoops_GHIIR;
			_hoops_RGGA (owner == _hoops_GHRI->owner) {
				owner = owner->owner;
				if (owner->type == _hoops_PRAIR) {
					HE_ERROR (HEC_COMPUTE, HES_NOT_A_DIRECT_DESCENDANT,
							Sprintf_PP (null,"'%p' is not a direct descendant of '%p'", _hoops_GHIIR, _hoops_GHRI->owner));
					goto Failed;
				}
			}
		}
	}

	if (!HI_Process_Heuristic_Options (context, _hoops_RPSHA, &_hoops_APHCR, true))
		goto Failed;

	// _hoops_HPPC _hoops_RPP _hoops_HAR _hoops_CHIA
	if ((action = _hoops_APHCR._hoops_PPSHA) == 0)
		action = _hoops_HPSHA;

	if (!_hoops_ACSHA) {
		if (left < (double)-1.0001 || right > (double)1.0001 ||
			bottom < (double)-1.0001 || top > (double)1.0001) {
			HE_ERROR (HEC_COMPUTE, HES_OUT_OF_RANGE_WINDOW, "Specified window coordinates not in the range of -1 to +1");
			goto Failed;
		}
	}

	if (left > right) {
		if (left > right + (double)0.001) {
			HE_ERROR (HEC_COMPUTE, HES_INVALID_OUTPUT, "Left > right coordinate");
			goto Failed;
		}
		left = right;
	}

	if (bottom > top) {
		if (bottom > top + (double)0.001) {
			HE_ERROR (HEC_COMPUTE, HES_INVALID_OUTPUT, "Bottom > top coordinate");
			goto Failed;
		}
		bottom = top;
	}

	if (hither > yon) {
		if (hither > yon + (double)0.001) {
			HE_ERROR (HEC_COMPUTE, HES_INVALID_OUTPUT, "Hither > yon coordinate");
			goto Failed;
		}
		hither = yon;
	}

	if (action == _hoops_HPSHA)
		action |= _hoops_IPSHA;
	else if (action == _hoops_CPSHA)
		action |= _hoops_SPSHA;

	/* _hoops_RRP _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_RH _hoops_RHPP _hoops_HRGR _hoops_AGPC _hoops_CISI -- _hoops_HRHI _hoops_IGISR _hoops_GGR _hoops_GSGS _hoops_IIGR
	 * _hoops_RH _hoops_PIH _hoops_SIGR _hoops_IH _hoops_IRS _hoops_GHSHA */
	if (BIT (_hoops_GHRI->_hoops_CPGPR, _hoops_CASIR)) {		/* _hoops_PSP _hoops_PAAP _hoops_GAPR */
		/* _hoops_RHSHA, _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_GPGR _hoops_AHSHA */
		if (BIT (_hoops_GHRI->_hoops_CPGPR, _hoops_CASIR)) 
			HI_Queue_Actor_Update(_hoops_GHRI, true);
	}


	Selection_Event				*_hoops_GPIIR;
	ZALLOC (_hoops_GPIIR, Selection_Event);
	_hoops_GPIIR->owner = HOOPS_WORLD;
	_hoops_GPIIR->_hoops_HIHI = 1;
	_hoops_GPIIR->type = _hoops_SAIIR;
	_hoops_GPIIR->_hoops_PHSHA = HI_What_Time();
	_hoops_GPIIR->flags = _hoops_HCSHA;
	if (_hoops_ACSHA)
		_hoops_GPIIR->flags |= _hoops_ICSHA;
	_hoops_GPIIR->_hoops_IHSHA.left	  = (float)left;
	_hoops_GPIIR->_hoops_IHSHA.right  = (float)right;
	_hoops_GPIIR->_hoops_IHSHA.bottom = (float)bottom;
	_hoops_GPIIR->_hoops_IHSHA.top	  = (float)top;
	_hoops_GPIIR->_hoops_IHSHA.hither = (float)hither;
	_hoops_GPIIR->_hoops_IHSHA.yon	  = (float)yon;
	_hoops_GPIIR->_hoops_CHSHA = action;
	_hoops_GPIIR->status = ANYBIT(action, _hoops_CPSHA|_hoops_SPSHA) ? 0 : 1;
	if (*_hoops_SASHA != '\0') {
		_hoops_GPIIR->target = _hoops_GHRI;
		_hoops_PRRH (_hoops_GPIIR->target);
	}
	if ((_hoops_GPIIR->_hoops_GHIIR = _hoops_GHIIR) != null)
		_hoops_PRRH (_hoops_GHIIR);

	if (_hoops_APHCR.mask != 0 || _hoops_APHCR._hoops_SHSHA != -1.0f)
		_hoops_GPIIR->heuristics = &_hoops_APHCR;

	_hoops_GISHA = _hoops_HISAA (context, _hoops_GHRI, _hoops_RISHA, _hoops_GPIIR);

	if (!_hoops_GISHA)
		_hoops_HPRH (_hoops_GPIIR);
	else if (_hoops_GPIIR->_hoops_APIIR == null)
		_hoops_HPRH (_hoops_GPIIR);
	else {
		_hoops_RPIIR *		si;
		int						count = 0;

		/* _hoops_GCRR _hoops_SCH _hoops_RH _hoops_AISHA _hoops_PGRRR! */

		if (context->_hoops_PISHA != null)
			_hoops_HPRH (context->_hoops_PISHA);
		context->_hoops_PISHA = (_hoops_HISHA *)_hoops_GPIIR;
		_hoops_GPIIR->heuristics = null;

		/* _hoops_RPR _hoops_GH */
		si = _hoops_GPIIR->_hoops_APIIR;
		do ++count;
		while ((si = si->next) != null);

		/* _hoops_HPHR _hoops_GHSHA: _hoops_ASRC _hoops_RH _hoops_HPHR _hoops_RPR */
		_hoops_IRRPR();
		return count;
	}

Failed:
	_hoops_IRRPR();
	/* _hoops_PSP _hoops_GHSHA: _hoops_ASRC _hoops_IRS _hoops_RPR _hoops_IIGR _hoops_AHHR */
	return 0;
#endif
	
}


HC_INTERFACE int HC_CDECL HC_Compute_Selection_By_Area (
	char const *			_hoops_SASHA,
	char const *			_hoops_GPSHA,
	char const *			_hoops_RPSHA,
	double					left,
	double					right,
	double					bottom,
	double					top) 
{
	_hoops_PAPPR context("Compute_Selection_By_Area");

#ifdef DISABLE_SELECTION
	_hoops_IRPPR ("Selection");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Compute_Selection_By_Area (%S, %S, ", _hoops_SASHA, _hoops_GPSHA));
		HI_Dump_Code (Sprintf_S (null, "%S, ", _hoops_RPSHA));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", left, right));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F);\n", bottom, top));
	);

	PUSHNAME(context);
	int count = HC_Compute_Selection_By_Volume (_hoops_SASHA, _hoops_GPSHA, _hoops_RPSHA,
											left, right, bottom, top, -MAX_FLOAT, MAX_FLOAT);
	POPNAME(context);
#endif
	return count;
}


HC_INTERFACE int HC_CDECL HC_Compute_Selection_By_Polylin (
	char const *			_hoops_SASHA,
	char const *			_hoops_GPSHA,
	char const *			_hoops_RPSHA,
	int						count,
	Point const *			points) 
{
	_hoops_PAPPR context("Compute_Selection_By_Polyline");

#ifdef DISABLE_SELECTION
	_hoops_IRPPR ("Selection");
#else
#ifdef DISABLE_POLY_SELECTION
	_hoops_IRPPR ("Polyline/Polygon Based Selection");
#else
	CODE_GENERATION (
		int		count2 = count;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "HC_POINT * points = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", count));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].x = %f;	 ", count2, points[count2].x));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].y = %f;	 ", count2, points[count2].y));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].z = %f;\n", count2, points[count2].z));
		}
		HI_Dump_Code (Sprintf_SS (null, "HC_Compute_Selection_By_Polylin (%S, %S, ", _hoops_SASHA, _hoops_GPSHA));
		HI_Dump_Code (Sprintf_SD (null, "%S, %d, points);\n", _hoops_RPSHA, count));
		HI_Dump_Code ("free (points);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	
	_hoops_CSPPR();
	_hoops_GGAGR *	_hoops_GHRI;
	if ((_hoops_GHRI = HI_Force_Find_Driver (context, _hoops_SASHA)) == null) {
		_hoops_IRRPR();
		return 0;
	}

	if (_hoops_GPSHA == null)
		_hoops_GPSHA = "";
	while (*_hoops_GPSHA == ' ') 
		++_hoops_GPSHA;

	_hoops_CRCP *	_hoops_GHIIR;

	if (*_hoops_GPSHA == '\0')
		_hoops_GHIIR = null;
	else {
		_hoops_CRCP				*owner;

		_hoops_GHIIR = HI_One_Segment_Search (context, _hoops_GPSHA, true);
		if (_hoops_GHIIR == null) {
			_hoops_IRRPR();
			return 0;
		}

		owner = _hoops_GHIIR;
		_hoops_RGGA (owner == _hoops_GHRI->owner) {
			owner = owner->owner;
			if (owner->type == _hoops_PRAIR) {
				HE_ERROR (HEC_COMPUTE, HES_NOT_A_DIRECT_DESCENDANT,
						Sprintf_PP (null,"'%p' is not a direct descendant of '%p'", _hoops_GHIIR, _hoops_GHRI->owner));
				_hoops_IRRPR();
				return 0;
			}
		}
	}

	_hoops_GHAIR	_hoops_APHCR;
	if (!HI_Process_Heuristic_Options (context, _hoops_RPSHA, &_hoops_APHCR, true)) {
		_hoops_IRRPR();
		return 0;
	}

	_hoops_APSHA	action;
	// _hoops_HPPC _hoops_RPP _hoops_HAR _hoops_CHIA
	if ((action = _hoops_APHCR._hoops_PPSHA) == 0)
		action = _hoops_HPSHA;

	if (action == _hoops_HPSHA)
		action |= _hoops_IPSHA;
	else if (action == _hoops_CPSHA)
		action |= _hoops_SPSHA;

	/* _hoops_RRP _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_RH _hoops_RHPP _hoops_HRGR _hoops_AGPC _hoops_CISI -- _hoops_HRHI _hoops_IGISR _hoops_GGR _hoops_GSGS _hoops_IIGR
	 * _hoops_RH _hoops_PIH _hoops_SIGR _hoops_IH _hoops_IRS _hoops_GHSHA */
	if (BIT (_hoops_GHRI->_hoops_CPGPR, _hoops_CASIR)) {		/* _hoops_PSP _hoops_PAAP _hoops_GAPR */
		/* _hoops_RHSHA, _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_GPGR _hoops_AHSHA */
		if (BIT (_hoops_GHRI->_hoops_CPGPR, _hoops_CASIR)) 
			HI_Queue_Actor_Update(_hoops_GHRI, true);
	}

	if (count < 2) {
		HE_ERROR2 (HEC_SELECTION, HES_INVALID_NUMBER,
				   "The supplied polyline must have at least 2 points",
				   "to process a compute selection by polyline");
		_hoops_IRRPR();
		return 0;
	}

	Selection_Event *	_hoops_GPIIR;
	ZALLOC (_hoops_GPIIR, Selection_Event);
	_hoops_GPIIR->owner = HOOPS_WORLD;
	_hoops_GPIIR->_hoops_HIHI = 1;
	_hoops_GPIIR->type = _hoops_SAIIR;
	_hoops_GPIIR->_hoops_PHSHA = HI_What_Time();
	_hoops_GPIIR->flags = _hoops_HCSHA;
	_hoops_GPIIR->_hoops_CHSHA = action;
	_hoops_GPIIR->status = ANYBIT(action, _hoops_CPSHA|_hoops_SPSHA) ? 0 : 1;
	_hoops_GPIIR->target = _hoops_GHRI;
	_hoops_PRRH (_hoops_GHRI);
	if ((_hoops_GPIIR->_hoops_GHIIR = _hoops_GHIIR) != null)
		_hoops_PRRH (_hoops_GHIIR);
	_hoops_GPIIR->count = count;
	_hoops_GPIIR->_hoops_HARIR = (Point *)HI_Clone_Anything (points, count * (long)sizeof (Point));

	_hoops_GPIIR->_hoops_IHSHA.left	  = points->x;
	_hoops_GPIIR->_hoops_IHSHA.right  = points->x;
	_hoops_GPIIR->_hoops_IHSHA.bottom = points->y;
	_hoops_GPIIR->_hoops_IHSHA.top	  = points->y;
	_hoops_RGGA (--count == 0) {
		++points;
		if (points->x < _hoops_GPIIR->_hoops_IHSHA.left)
			_hoops_GPIIR->_hoops_IHSHA.left = points->x;
		else if (points->x > _hoops_GPIIR->_hoops_IHSHA.right)
			_hoops_GPIIR->_hoops_IHSHA.right = points->x;
		if (points->y < _hoops_GPIIR->_hoops_IHSHA.bottom)
			_hoops_GPIIR->_hoops_IHSHA.bottom = points->y;
		else if (points->y > _hoops_GPIIR->_hoops_IHSHA.top)
			_hoops_GPIIR->_hoops_IHSHA.top = points->y;
	}
	_hoops_GPIIR->_hoops_IHSHA.hither = -MAX_FLOAT;
	_hoops_GPIIR->_hoops_IHSHA.yon	  = MAX_FLOAT;

	if (_hoops_APHCR.mask != 0 || _hoops_APHCR._hoops_SHSHA != -1.0f)
		_hoops_GPIIR->heuristics = &_hoops_APHCR;

	bool _hoops_GISHA = _hoops_HISAA (context, _hoops_GHRI, _hoops_RISHA, _hoops_GPIIR);
	_hoops_IRRPR();

	if (!_hoops_GISHA)
		_hoops_HPRH (_hoops_GPIIR);
	else if (_hoops_GPIIR->_hoops_APIIR == null)
		_hoops_HPRH (_hoops_GPIIR);
	else {
		_hoops_RPIIR *		si;
		int						total = 0;

		/* _hoops_GCRR _hoops_SCH _hoops_RH _hoops_AISHA _hoops_PGRRR! */

		if (context->_hoops_PISHA != null)
			_hoops_HPRH (context->_hoops_PISHA);
		context->_hoops_PISHA = (_hoops_HISHA *)_hoops_GPIIR;
		_hoops_GPIIR->heuristics = null;

		/* _hoops_RPR _hoops_GH */

		si = _hoops_GPIIR->_hoops_APIIR;
		do ++total;
		while ((si = si->next) != null);

		/* _hoops_HPHR _hoops_GHSHA: _hoops_ASRC _hoops_RH _hoops_HPHR _hoops_RPR */
		return total;
	}

	/* _hoops_PSP _hoops_GHSHA: _hoops_ASRC _hoops_IRS _hoops_RPR _hoops_IIGR _hoops_AHHR */
#endif
#endif
	return 0;
}



HC_INTERFACE int HC_CDECL HC_Compute_Selection_By_Polygon (
	char const *			_hoops_SASHA,
	char const *			_hoops_GPSHA,
	char const *			_hoops_RPSHA,
	int						count,
	Point const *			points) 
{
	_hoops_PAPPR context("Compute_Selection_By_Polygon");

#ifdef DISABLE_SELECTION
	_hoops_IRPPR ("Selection");
#else
#ifdef DISABLE_POLY_SELECTION
	_hoops_IRPPR ("Polyline/Polygon Based Selection");
#else
	CODE_GENERATION (
		int		count2 = count;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "HC_POINT * points = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", count));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].x = %f;	 ", count2, points[count2].x));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].y = %f;	 ", count2, points[count2].y));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].z = %f;\n", count2, points[count2].z));
		}
		HI_Dump_Code (Sprintf_SS (null, "HC_Compute_Selection_By_Polygon (%S, %S, ", _hoops_SASHA, _hoops_GPSHA));
		HI_Dump_Code (Sprintf_SD (null, "%S, %d, points);}\n", _hoops_RPSHA, count));
		HI_Dump_Code ("free (points);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	_hoops_CSPPR();
	_hoops_GGAGR *	_hoops_GHRI;
	if ((_hoops_GHRI = HI_Force_Find_Driver (context, _hoops_SASHA)) == null) {
		_hoops_IRRPR();
		return 0;
	}

	if (_hoops_GPSHA == null)
		_hoops_GPSHA = "";
	while (*_hoops_GPSHA == ' ') 
		++_hoops_GPSHA;

	_hoops_CRCP *	_hoops_GHIIR;
	if (*_hoops_GPSHA == '\0')
		_hoops_GHIIR = null;
	else {

		_hoops_CRCP *	owner;

		_hoops_GHIIR = HI_One_Segment_Search (context, _hoops_GPSHA, true);

		if (_hoops_GHIIR == null) {
			_hoops_IRRPR();
			return 0;
		}

		owner = _hoops_GHIIR;
		_hoops_RGGA (owner == _hoops_GHRI->owner) {
			owner = owner->owner;
			if (owner->type == _hoops_PRAIR) {
				HE_ERROR (HEC_COMPUTE, HES_NOT_A_DIRECT_DESCENDANT,
						Sprintf_PP (null,"'%p' is not a direct descendant of '%p'", _hoops_GHIIR, _hoops_GHRI->owner));
				_hoops_IRRPR();
				return 0;
			}
		}
	}

	_hoops_GHAIR	_hoops_APHCR;
	if (!HI_Process_Heuristic_Options (context, _hoops_RPSHA, &_hoops_APHCR, true)) {
		_hoops_IRRPR();
		return 0;
	}

	_hoops_APSHA	action;

	// _hoops_HPPC _hoops_RPP _hoops_HAR _hoops_CHIA
	if ((action = _hoops_APHCR._hoops_PPSHA) == 0)
		action = _hoops_HPSHA;

	if (action == _hoops_HPSHA)
		action |= _hoops_IPSHA;
	else if (action == _hoops_CPSHA)
		action |= _hoops_SPSHA;

	/* _hoops_RRP _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_RH _hoops_RHPP _hoops_HRGR _hoops_AGPC _hoops_CISI -- _hoops_HRHI _hoops_IGISR _hoops_GGR _hoops_GSGS _hoops_IIGR
	 * _hoops_RH _hoops_PIH _hoops_SIGR _hoops_IH _hoops_IRS _hoops_GHSHA */
	if (BIT (_hoops_GHRI->_hoops_CPGPR, _hoops_CASIR)) {		/* _hoops_PSP _hoops_PAAP _hoops_GAPR */
		/* _hoops_RHSHA, _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_GPGR _hoops_AHSHA */
		if (BIT (_hoops_GHRI->_hoops_CPGPR, _hoops_CASIR)) 
			HI_Queue_Actor_Update(_hoops_GHRI, true);
	}

	if (count < 3) {
		HE_ERROR2 (HEC_SELECTION, HES_INVALID_NUMBER,
				   "The supplied polygon must have at least 3 points",
				   "to process a compute selection by polygon");
		_hoops_IRRPR();
		return 0;
	}

	Selection_Event *	_hoops_GPIIR;

	ZALLOC (_hoops_GPIIR, Selection_Event);
	_hoops_GPIIR->owner = HOOPS_WORLD;
	_hoops_GPIIR->_hoops_HIHI = 1;
	_hoops_GPIIR->type = _hoops_SAIIR;
	_hoops_GPIIR->_hoops_PHSHA = HI_What_Time();
	_hoops_GPIIR->flags = _hoops_HCSHA | _hoops_CCSHA;
	_hoops_GPIIR->_hoops_CHSHA = action;
	_hoops_GPIIR->status = ANYBIT(action, _hoops_CPSHA|_hoops_SPSHA) ? 0 : 1;
	_hoops_GPIIR->target = _hoops_GHRI;
	_hoops_PRRH (_hoops_GHRI);
	if ((_hoops_GPIIR->_hoops_GHIIR = _hoops_GHIIR) != null)
		_hoops_PRRH (_hoops_GHIIR);

	/*
	 * _hoops_IGPP _hoops_RH _hoops_PPSR _hoops_HIGR _hoops_IAPR, _hoops_SCSHA _hoops_SGS _hoops_SCH'_hoops_GRI _hoops_CAHC
	 */
	{
		Point const	*_hoops_SSAC = &points[count - 1];

		if (points[0].x == _hoops_SSAC->x && points[0].y == _hoops_SSAC->y && points[0].z == _hoops_SSAC->z) {
			_hoops_GPIIR->_hoops_HARIR = (Point *)HI_Clone_Anything (points, count * (long)sizeof (Point));
			_hoops_GPIIR->count = count;
		}
		else {
			_hoops_GPIIR->count = count + 1;
			ALLOC_ARRAY (_hoops_GPIIR->_hoops_HARIR, _hoops_GPIIR->count, Point);
			_hoops_AIGA (points, count, Point, _hoops_GPIIR->_hoops_HARIR);
			_hoops_GPIIR->_hoops_HARIR[count] = _hoops_GPIIR->_hoops_HARIR[0];
		}
	}

	_hoops_GPIIR->_hoops_IHSHA.left	  = points->x;
	_hoops_GPIIR->_hoops_IHSHA.right  = points->x;
	_hoops_GPIIR->_hoops_IHSHA.bottom = points->y;
	_hoops_GPIIR->_hoops_IHSHA.top	  = points->y;
	_hoops_RGGA (--count == 0) {
		++points;

		if (points->x < _hoops_GPIIR->_hoops_IHSHA.left)
			_hoops_GPIIR->_hoops_IHSHA.left = points->x;
		else if (points->x > _hoops_GPIIR->_hoops_IHSHA.right)
			_hoops_GPIIR->_hoops_IHSHA.right = points->x;

		if (points->y < _hoops_GPIIR->_hoops_IHSHA.bottom)
			_hoops_GPIIR->_hoops_IHSHA.bottom = points->y;
		else if (points->y > _hoops_GPIIR->_hoops_IHSHA.top)
			_hoops_GPIIR->_hoops_IHSHA.top = points->y;
	}
	_hoops_GPIIR->_hoops_IHSHA.hither = -MAX_FLOAT;
	_hoops_GPIIR->_hoops_IHSHA.yon	  =	 MAX_FLOAT;

	if (_hoops_APHCR.mask != 0 || _hoops_APHCR._hoops_SHSHA != -1.0f)
		_hoops_GPIIR->heuristics = &_hoops_APHCR;

	bool _hoops_GISHA = _hoops_HISAA (context, _hoops_GHRI, _hoops_RISHA, _hoops_GPIIR);
	_hoops_IRRPR();

	if (!_hoops_GISHA)
		_hoops_HPRH (_hoops_GPIIR);
	else if (_hoops_GPIIR->_hoops_APIIR == null)
		_hoops_HPRH (_hoops_GPIIR);
	else {
		_hoops_RPIIR *		si;
		int						total = 0;

		/* _hoops_GCRR _hoops_SCH _hoops_RH _hoops_AISHA _hoops_PGRRR! */

		if (context->_hoops_PISHA != null)
			_hoops_HPRH (context->_hoops_PISHA);
		context->_hoops_PISHA = (_hoops_HISHA *)_hoops_GPIIR;
		_hoops_GPIIR->heuristics = null;

		/* _hoops_RPR _hoops_GH */

		si = _hoops_GPIIR->_hoops_APIIR;
		do ++total;
		while ((si = si->next) != null);

		/* _hoops_HPHR _hoops_GHSHA: _hoops_ASRC _hoops_RH _hoops_HPHR _hoops_RPR */
		return total;
	}

	/* _hoops_PSP _hoops_GHSHA: _hoops_ASRC _hoops_IRS _hoops_RPR _hoops_IIGR _hoops_AHHR */
#endif
#endif
	return 0;
}

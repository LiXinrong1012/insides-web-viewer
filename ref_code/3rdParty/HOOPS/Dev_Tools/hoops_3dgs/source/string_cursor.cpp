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
 * $Id: obf_tmp.txt 1.51 2010-07-29 22:00:46 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


HC_INTERFACE Key HC_CDECL HC_Insert_String_Cursor (
	Key					_hoops_RCGGGR,
	int					row,
	int					column) 
{
	_hoops_PAPPR context("Insert_String_Cursor");

	_hoops_CSPPR();
	_hoops_HACC *	text = (_hoops_HACC *)_hoops_RCSSR (context, _hoops_RCGGGR);

	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (text == null || text->type != _hoops_AGCP ||
		BIT (text->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_STRING_CURSOR, HES_INVALID_KEY,"Provided key does not refer to a valid Text item");
	}
	else if (row < 0) {
		HE_ERROR (HEC_STRING_CURSOR, HES_INVALID_ROW, Sprintf_D (null,"Row #%d not valid - must not be negative", row));
	}
	else if (column < 0) {
		HE_ERROR (HEC_STRING_CURSOR, HES_INVALID_COLUMN, Sprintf_D (null,"Column #%d not valid - must not be negative", column));
	}
	else {

		Geometry **	_hoops_ASRGR = null;

		if (row == 0 && column > text->count) {
			HE_ERROR (HEC_STRING_CURSOR, HES_INVALID_CHARACTER_NUMBER,
					Sprintf_DD (null,"'%d' is not a valid character number - you only have %d",column, text->count));
		}
		else if (row != 0 && column > text->_hoops_ICI[row]) {
			HE_ERROR (HEC_STRING_CURSOR, HES_INVALID_CHARACTER_NUMBER,
					Sprintf_DD (null, "'%d' is not a valid character number - you only have %d on that line",column, text->_hoops_ICI[row]));
		}
		else
			_hoops_ASRGR = (Geometry **)&text->_hoops_AAPGR;

		if (_hoops_ASRGR == null) { 
			/* _hoops_ACGGGR _hoops_HRGR _hoops_ICGSA */ 
		}
		else {

			if (text->_hoops_ICI != null) {

				while (column > text->_hoops_ICI[row]) {
					column -= text->_hoops_ICI[row] + 1;		/* _hoops_GCIS _hoops_RH \_hoops_ACHP */
					++row;
				}
			}

			_hoops_PIGPR *	cursor;
			ZALLOC (cursor, _hoops_PIGPR);

			cursor->_hoops_HIHI = 1;
			cursor->type = HK_STRING_CURSOR;
			cursor->_hoops_CPGPR = _hoops_PHSSR;
			cursor->row = row;
			cursor->column = column;
			cursor->owner = (_hoops_CRCP *)text;		/** _hoops_HAR _hoops_CPSA _hoops_IRS _hoops_CAGH **/
			cursor->key = _hoops_AIRIR (cursor);

			_hoops_RPPPR();
			if ((cursor->next = *_hoops_ASRGR) != null)
				(*_hoops_ASRGR)->backlink = &cursor->next;
			*_hoops_ASRGR = (Geometry *)cursor;
			cursor->backlink = _hoops_ASRGR;

			if (!BIT (text->owner->_hoops_RCGC, T_STRING_CURSORS))
				HI_Propagate_Maybes (context, text->owner, T_STRING_CURSORS);

			/* _hoops_CGH _hoops_CPSA _hoops_SHH _hoops_GPRGS */
			_hoops_SASIR (context, text, _hoops_GGARA);
			_hoops_CHSSR = _hoops_AIRIR (cursor);
			_hoops_IRRPR(); // _hoops_PHCHH
		}
	}
	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Insert_String_Cursor (LOOKUP(%D), ", _hoops_RCGGGR));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d), ", row, column));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
	);

	return _hoops_CHSSR;
}



HC_INTERFACE void HC_CDECL HC_Show_String_Cursor (
	Key					key,
	Key *				owner,
	int *				row,
	int *				col) 
{
	_hoops_PAPPR context("Show_String_Cursor");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_String_Cursor () */\n");
	);

	_hoops_CSPPR();
	_hoops_PIGPR *	cursor = (_hoops_PIGPR *)_hoops_RCSSR (context, key);

	if (cursor == null ||
		cursor->type != HK_STRING_CURSOR ||
		BIT (cursor->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_STRING_CURSOR, HES_INVALID_KEY, "Provided key does not refer to a valid \"String Cursor\"");
	}
	else {
		*owner = cursor->owner->key;
		*row = cursor->row;
		*col = cursor->column;
	}

	_hoops_IRRPR();
#endif
}



HC_INTERFACE void HC_CDECL HC_Move_String_Cursor (
	Key					key,
	int					row,
	int					column) 
{
	_hoops_PAPPR context("Move_String_Cursor");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Move_String_Cursor (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d);\n", row, column));
	);

	if (row < 0) {
		HE_ERROR (HEC_STRING_CURSOR, HES_INVALID_ROW,
			Sprintf_D (null,"Row #%d not valid - must not be negative", row));
		return;
	}

	if (column < 0) {
		HE_ERROR (HEC_STRING_CURSOR, HES_INVALID_COLUMN,
			Sprintf_D (null,"Column #%d not valid - must not be negative", column));
		return;
	}

	_hoops_CSPPR();

	_hoops_PIGPR *	cursor = (_hoops_PIGPR *)_hoops_RCSSR (context, key);
	_hoops_HACC const *	text = (_hoops_HACC const *)cursor->owner;

	if (cursor == null || cursor->type != HK_STRING_CURSOR || BIT (cursor->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_STRING_CURSOR, HES_INVALID_KEY,"Provided key does not refer to a valid String Cursor");
	}
	else if (row >= text->_hoops_PICHR && row != 0) {
		HE_ERROR (HEC_STRING_CURSOR, HES_INVALID_ROW,
				Sprintf_DD (null,"'%d' is not a valid row number - you only have %d", row,text->_hoops_PICHR));
	}
	else if (row == 0 && column > text->count) {
		HE_ERROR (HEC_STRING_CURSOR, HES_INVALID_CHARACTER_NUMBER,
				Sprintf_DD (null,"'%d' is not a valid character number - you only have %d", column, text->count));
	}
	else if (row != 0 && column > text->_hoops_ICI[row]) {
		HE_ERROR (HEC_STRING_CURSOR, HES_INVALID_CHARACTER_NUMBER,
				Sprintf_DD (null,"'%d' is not a valid character number - you only have %d on that line", column, text->_hoops_ICI[row]));
	}
	else {

		if (text->_hoops_ICI != null) {

			while (column > text->_hoops_ICI[row]) {
				column -= text->_hoops_ICI[row] + 1;		/* _hoops_GCIS _hoops_RH \_hoops_ACHP */
				++row;
			}
		}

		if (row != cursor->row || column != cursor->column) {

			_hoops_RPPPR();
			cursor->row = row;
			cursor->column = column;

			if (!ANYBIT (cursor->_hoops_CPGPR, _hoops_CASIR|_hoops_AHSGA)) {
				cursor->_hoops_CPGPR |= _hoops_HHSSR;

				/* _hoops_CGH _hoops_CPSA _hoops_SHH _hoops_GPRGS */
				_hoops_SASIR (context, text, _hoops_RAGGA);
			}
			_hoops_IRRPR();
		}

	}

	_hoops_IRRPR();
}



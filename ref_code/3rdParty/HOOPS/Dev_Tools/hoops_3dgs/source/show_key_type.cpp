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
 * $Id: obf_tmp.txt 1.119 2010-10-14 01:06:40 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "phedron.h"


#ifdef DISABLE_SHOW
#	ifdef DISABLE_SEARCH
#		define	_hoops_PHGHS
#	endif
#endif

#ifndef _hoops_PHGHS

local _hoops_SRHSR	_hoops_HHGHS[] = {
	_hoops_GRRCR ("style"),

	_hoops_GRRCR ("conditions"),
	_hoops_GRRCR ("texture definitions"),
	_hoops_GRRCR ("glyph definitions"),
	_hoops_GRRCR ("line pattern definitions"),
	_hoops_GRRCR ("named style definitions"),
	_hoops_GRRCR ("rendering options"),
	_hoops_GRRCR ("selectability"),
	_hoops_GRRCR ("visibility"),
	_hoops_GRRCR ("color map"),
	_hoops_GRRCR ("color"),

	_hoops_GRRCR ("window frame"),
	_hoops_GRRCR ("window pattern"),
	_hoops_GRRCR ("window"),
	_hoops_GRRCR ("camera"),
	_hoops_GRRCR ("heuristics"),
	_hoops_GRRCR ("modelling matrix"),
	_hoops_GRRCR ("callback"),
	_hoops_GRRCR ("clip region"),
	_hoops_GRRCR ("driver"),
	_hoops_GRRCR ("driver options"),

	_hoops_GRRCR ("edge pattern"),
	_hoops_GRRCR ("edge weight"),
	_hoops_GRRCR ("face pattern"),
	_hoops_GRRCR ("handedness"),
	_hoops_GRRCR ("line pattern"),
	_hoops_GRRCR ("line weight"),
	_hoops_GRRCR ("marker size"),
	_hoops_GRRCR ("marker symbol"),
	_hoops_GRRCR ("text alignment"),
	_hoops_GRRCR ("text font"),

	_hoops_GRRCR ("text path"),
	_hoops_GRRCR ("text spacing"),
	_hoops_GRRCR ("user options"),
	_hoops_GRRCR ("user value"),
	_hoops_GRRCR ("texture matrix"),
	_hoops_GRRCR ("streaming mode"),
	_hoops_GRRCR ("cutting plane"),
	_hoops_GRRCR ("light"),				/* _hoops_GRH _hoops_IHGHS _hoops_CAPP */
	_hoops_GRRCR ("shell"),
	_hoops_GRRCR ("mesh"),

	_hoops_GRRCR ("grid"),
	_hoops_GRRCR ("nurbs surface"),
	_hoops_GRRCR ("cylinder"),
	_hoops_GRRCR ("polycylinder"),
	_hoops_GRRCR ("sphere"),
	_hoops_GRRCR ("polygon"),
	_hoops_GRRCR ("circle"),
	_hoops_GRRCR ("circular chord"),
	_hoops_GRRCR ("circular wedge"),
	_hoops_GRRCR ("ellipse"),

	_hoops_GRRCR ("line"),
	_hoops_GRRCR ("-multiline-"),
	_hoops_GRRCR ("polyline"),
	_hoops_GRRCR ("nurbs curve"),
	_hoops_GRRCR ("circular arc"),
	_hoops_GRRCR ("elliptical arc"),
	_hoops_GRRCR ("infinite line"),
	_hoops_GRRCR ("image"),
	_hoops_GRRCR ("marker"),
	_hoops_GRRCR ("-multimarker-"),

	_hoops_GRRCR ("text"),
	_hoops_GRRCR ("string cursor"),
	_hoops_GRRCR ("reference"),
	_hoops_GRRCR ("missing geometry"),
	_hoops_GRRCR ("include"),
	_hoops_GRRCR ("segment"),
	_hoops_GRRCR ("lods"),
	_hoops_GRRCR ("open list"),
	_hoops_GRRCR ("world"),
	_hoops_GRRCR ("alias"),

	_hoops_GRRCR ("callback name"),
	_hoops_GRRCR ("color def"),
	_hoops_GRRCR ("error handler"),
	_hoops_GRRCR ("exit handler"),
	_hoops_GRRCR ("font"),
	_hoops_GRRCR ("texture"),
	_hoops_GRRCR ("wakeup"),
	_hoops_GRRCR ("option type"),
	_hoops_GRRCR ("trim polyline"),
	_hoops_GRRCR ("trim nurbs curve"),

	_hoops_GRRCR ("trim collection"),
	_hoops_GRRCR ("display list"),
	_hoops_GRRCR ("contour"),
	_hoops_GRRCR ("static model"),
	_hoops_GRRCR ("button event"),
	_hoops_GRRCR ("location event"),
	_hoops_GRRCR ("selection event"),
	_hoops_GRRCR ("special event"),
	_hoops_GRRCR ("string event"),
	_hoops_GRRCR ("wakeup event"),

	/* _hoops_GRH _hoops_CSSC _hoops_PGAP _hoops_GHCA _hoops_SHH _hoops_GIIA _hoops_HPP _hoops_GIPHR */
	_hoops_GRRCR ("normal"),
	_hoops_GRRCR ("parameter"),
	_hoops_GRRCR ("face"),
	_hoops_GRRCR ("edge"),
	_hoops_GRRCR ("vertex"),
};

#endif

GLOBAL_FUNCTION void HI_Show_Type_Name (
	int				_hoops_GGSIH,
	char *			type,
	int				length) {
#ifndef _hoops_PHGHS

	if (_hoops_GGAPR(_hoops_HHGHS) != _hoops_GHAGP+1 + 5/* _hoops_GRH _hoops_CSSC */) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Key/type lookup mismatch.");
	}

	HI_Return_Chars (type, length, _hoops_HHGHS[_hoops_GGSIH].text, _hoops_HHGHS[_hoops_GGSIH].length);
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Key_Type (
	Key			key,
	char *		type) 
{
	_hoops_PAPPR context("Show_Key_Type");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Key_Type () */\n");
	);

	bool		_hoops_PPIHA = false;
	_hoops_CSPPR();

	_hoops_HPAH *	thing = (_hoops_HPAH *)_hoops_RCSSR (context, key);
	if (thing == null || BIT (thing->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_INVALID_KEY, HES_INVALID_TYPE, "Provided key does not refer to a valid 3dgs database item");
		_hoops_IRRPR();
		return;
	}

	if (thing != null) {
		int		_hoops_GGSIH = thing->type;

		if (BIT (thing->_hoops_RRHH, _hoops_HGAGR)) {}
		else if ((_hoops_GGSIH >= _hoops_AHRIR && _hoops_GGSIH <= _hoops_PHRIR) ||
				 (_hoops_GGSIH >= _hoops_IISIR && _hoops_GGSIH <= _hoops_IHRIR) ||
				 _hoops_GGSIH == HK_STYLE ||
				 _hoops_GGSIH == _hoops_PIRIR) {
			if (_hoops_GGSIH == _hoops_ICIP) {
				Light const *		light = (Light const *)thing;

				switch (light->_hoops_PRR) {
					case _hoops_H: {
						HI_Return_Chars (type, -1, "distant light", 13);
					}	break;
					case _hoops_C: {
						HI_Return_Chars (type, -1, "local light", 11);
					}	break;
					case _hoops_I: {
						HI_Return_Chars (type, -1, "spot light", 10);
					}	break;
					case _hoops_S: {
						HI_Return_Chars (type, -1, "area light", 10);
					}	break;
				}
			}
			else if (_hoops_GGSIH == _hoops_SIIP) {
				if (BIT(thing->_hoops_RRHH, _hoops_IHHCA))
					HI_Return_Chars (type, -1, "infinite ray", 12);
				else
					HI_Return_Chars (type, -1, "infinite line", 13);
			}
			else if (_hoops_GGSIH == _hoops_HGPGR && ((_hoops_HHPIR const *)thing)->count > 1)
				HI_Return_Chars (type, -1, "cutting section", 15);
			else if (_hoops_GGSIH == _hoops_HIIP)
				HI_Return_Chars (type, -1, "line", 4);
			else if (_hoops_GGSIH == _hoops_PIRS)
				HI_Return_Chars (type, -1, "marker", 6);
			else if (_hoops_GGSIH == HK_STYLE) {
				Style const *		style = (Style const *)thing;

				if (style->_hoops_IGRPR == null)
					HI_Return_Chars (type, -1, "named style", 11);
				else
					HI_Return_Chars (type, -1, "style", 5);
			}
			else
				HI_Show_Type_Name (_hoops_GGSIH, type, -1);

			_hoops_PPIHA = true;
		}
	}

	_hoops_IRRPR();

	if (!_hoops_PPIHA)
		HE_ERROR (HEC_INVALID_KEY, HES_INVALID_TYPE, "Invalid key type");
#endif
}




HC_INTERFACE void HC_CDECL HC_Show_LOD_Type (
	Key			key,
	int			level,
	char *		type) 
{
	_hoops_PAPPR context("Show_LOD_Type");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_LOD_Type () */\n");
	);

	_hoops_CSPPR();

	_hoops_HPAH const	*thing = (_hoops_HPAH *)_hoops_RCSSR (context, key);

	if (thing == null || BIT (thing->_hoops_RRHH, _hoops_HGAGR)) {
		HI_Return_Chars (type, -1, "invalid", 7);
	}
	else if (level == 0) {
		HI_Show_Type_Name (thing->type, type, -1);
	}
	else {
		_hoops_PGAIR const *	_hoops_HGAIR = null;

		switch (thing->type) {
			case _hoops_SCIP:
			case _hoops_GSIP:
				_hoops_HGAIR = ((Polyhedron *)thing)->_hoops_HGAIR;
				break;
			case _hoops_IRCP:
				_hoops_HGAIR = ((_hoops_CRCP *)thing)->_hoops_SSRIR();
				break;
		}

		level -= 1;		/* _hoops_PRCCA 0 _hoops_HRGR _hoops_RH _hoops_AHAP _hoops_ACAS */
		if (_hoops_HGAIR != null &&
			_hoops_HGAIR->data[level] != null) {
			if (_hoops_HGAIR->data[level]->next != null) {
				HI_Return_Chars (type, -1, "collection", 10);
			}
			else {
				int	_hoops_GGSIH = _hoops_HGAIR->data[level]->type;
				HI_Show_Type_Name (_hoops_GGSIH, type, -1);
			}
		}
		else {
			HI_Return_Chars (type, -1, "invalid", 7);
		}
	}

	_hoops_IRRPR();
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Key_Status (
	Key			key,
	char *		status) 
{
	_hoops_PAPPR context("Show_Key_Status");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Key_Status () */\n");
	);

	_hoops_CSPPR();

	_hoops_HPAH *	thing  = (_hoops_HPAH *)_hoops_RCSSR (context, key);

	if (((POINTER_SIZED_INT)thing & ((1<<ALIGNMENT) - 1)) != 0)
		HI_Return_Chars (status, -1, "invalid", 7);

	else if (thing == null ||
		BIT (thing->_hoops_RRHH, _hoops_HGAGR) ||
		((thing->type < _hoops_AHRIR ||
		  thing->type > _hoops_PHRIR) &&
		 thing->type != _hoops_AGRPR && thing->type != _hoops_IRCP &&
		 thing->type != HK_STYLE))
		HI_Return_Chars (status, -1, "invalid", 7);
	else if (thing->type == _hoops_IRCP &&
			BIT(((_hoops_CRCP *)thing)->_hoops_PHSI, _hoops_ISHGP))
		HI_Return_Chars (status, -1, "invalid", 7);
	else if (key > _hoops_SHSSR) {
		if (HI_Has_Local_Key ((_hoops_CRCP *)thing->owner, thing->key))
			HI_Return_Chars (status, -1, "local", 5);
		else
			HI_Return_Chars (status, -1, "global", 6);
	}
	else
		HI_Return_Chars (status, -1, "valid", 5);

	_hoops_IRRPR();
#endif
}



HC_INTERFACE Key HC_CDECL HC_Show_Original_Key (
	Key						key) 
{
	_hoops_PAPPR context("Show_Original_Key");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Original_Key () */\n");
	);

	int		offset;

	_hoops_CSPPR();

	_hoops_HPAH *	thing = (_hoops_HPAH *)_hoops_SISIR (context, key, &offset);

	if (((POINTER_SIZED_INT)thing & ((1<<ALIGNMENT) - 1)) != 0)
		key = _hoops_SHSSR;

	else if (thing == null ||
		BIT (thing->_hoops_RRHH, _hoops_HGAGR) ||
		((thing->type < _hoops_AHRIR ||
		  thing->type > _hoops_PHRIR) &&
		 thing->type != _hoops_AGRPR && thing->type != _hoops_IRCP &&
		 thing->type != HK_STYLE && thing->type != _hoops_PIRIR))
		 key = _hoops_SHSSR;
	else if (BIT (thing->_hoops_RRHH, _hoops_CHRIR)) {
		int *				mapping = null;

		if (thing->type == _hoops_HIIP)
			mapping = ((_hoops_SHRIR *)thing)->mapping;
		else if (thing->type == _hoops_PIRS)
			mapping = ((_hoops_GRPGR *)thing)->mapping;

		key = ~(POINTER_SIZED_INT)(mapping[offset] & ~_hoops_RIRIR);
	}
	else
		key = _hoops_AIRIR (thing);

	_hoops_IRRPR();

	return key;
#endif
}

HC_INTERFACE Key HC_CDECL HC_Show_Renumbered_Key (
	Key			key,
	char *		status) 
{
	_hoops_PAPPR context("Show_Renumbered_Key");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Renumbered_Key () */\n");
	);

	_hoops_CSPPR();

	_hoops_HPAH *	thing = (_hoops_HPAH *)_hoops_RCSSR (context, key);

	if (((POINTER_SIZED_INT)thing & ((1<<ALIGNMENT) - 1)) != 0)
		key = _hoops_SHSSR;

	else if (thing == null ||
		BIT (thing->_hoops_RRHH, _hoops_HGAGR) ||
		((thing->type < _hoops_AHRIR ||
		  thing->type > _hoops_PHRIR) &&
		 thing->type != _hoops_AGRPR && thing->type != _hoops_IRCP &&
		 thing->type != HK_STYLE))
		key = _hoops_SHSSR;
	else
		key = thing->key;

	if (status != null) {
		if (key == _hoops_SHSSR)
			HI_Return_Chars (status, -1, "invalid", 5);
		else if (key < 0)
			HI_Return_Chars (status, -1, "original", 5);
		else if (HI_Has_Local_Key ((_hoops_CRCP *)thing->owner, thing->key))
			HI_Return_Chars (status, -1, "local", 5);
		else
			HI_Return_Chars (status, -1, "global", 6);
	}

	_hoops_IRRPR();

	return key;
#endif
}





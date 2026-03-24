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
 * $Id: obf_tmp.txt 1.66 2011-01-11 19:20:05 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "searchh.h"
#include "hpserror.h"
#include "patterns.h"
#include "driver.h"
#include "hd_proto.h"

/* _hoops_PIHA _hoops_PSSP _hoops_AGR _hoops_GGR _hoops_HSGP._hoops_GGHR */
local const char * _hoops_AGGIH[] = {
"()", "(.)", "(+)", "(x)", "(())", "(*)", ".", "+", "*", "x", "[]", "[.]", "[x]", "[*]", "<>", "<.>", "<+>", "<*>", 
"/\\", "^/\\", "/.\\", "/*\\", "^/*\\", "\\/", "v\\/", "\\./", "\\*/", "v\\*/", "|>", ">|>", "|.>", "|*>", ">|*>", 
"<|", "<<|", "<.|", "<*|", "<<*|", "#", "++", "/ \\", "/_\\", "|", "/", "\\", "/__\\", "/_^_\\", "y", "z"};


GLOBAL_FUNCTION _hoops_GASC HD_Find_Glyph_Legacy (
	Net_Rendition const &	nr,
	char					symbol) {

	if (symbol > MK_LETTER_Z) return null;
	if (symbol < MK_CIRCLE) return null;
	return HD_Find_Glyph (nr->glyph_rendition, _hoops_AGGIH[(int)symbol], 0, 0, false);
}

GLOBAL_FUNCTION _hoops_GASC HD_Find_Glyph (
	_hoops_GHRIP const &		_hoops_RRA,
	const char *				_hoops_HSIHH,
	_hoops_HCRPR const *				_hoops_PACSR,
	Integer32					key,
	bool						error) {
	_hoops_GASC						glyph;
	_hoops_HCRPR						_hoops_PGGIH;
	_hoops_HCRPR const *				name;
	int							i;

	_hoops_HGGIH(_hoops_PGGIH);

	if (!_hoops_PACSR) {
		name = &_hoops_PGGIH;
		HI_Canonize_Chars(_hoops_HSIHH, &_hoops_PGGIH);
	}
	else
		name = _hoops_PACSR;

	if (!key)
		_hoops_HCARA(*name, key);

	for (i=0; i<_hoops_RRA->count; ++i) {
		if (_hoops_RRA->keys[i] == key && _hoops_RAHSR(*name, _hoops_RRA->glyphs[i]->name)) {
			glyph = _hoops_RRA->glyphs[i];
			break;
		}
	}
	if (!glyph && error) {
		HE_WARNING (HEC_MARKER, HES_NOT_AVAILABLE,
			Sprintf_N (null, "Requested glyph '%n' not found", name));
	}

	if (!_hoops_PACSR)
		_hoops_RGAIR(_hoops_PGGIH);

	return glyph;
}

GLOBAL_FUNCTION char HD_Find_Glyph_Legacy_Symbol (_hoops_GASC const & glyph)
{
	for (int i=MK_CIRCLE; i<MK_LETTER_Z; ++i) 
		if (_hoops_AGGR(_hoops_AGGIH[i], glyph->name.text))
			return i;
	return MK_DOT;
}




/* _hoops_GIGHR: _hoops_CGH _hoops_GGCR _hoops_RRI _hoops_ARRPA _hoops_IPAC _hoops_GPP _hoops_RRPIP */

GLOBAL_FUNCTION bool HI_Validate_Glyph (_hoops_GASC alter & glyph) {
	char const *		_hoops_RPPA = glyph->data;
	char const *		end = _hoops_RPPA + glyph->length;
	int					_hoops_SIAIP;
	bool				_hoops_CIAIP = false;
	float				radius, _hoops_IGGIH, _hoops_CGGIH, _hoops_SGGIH, _hoops_GRGIH;
	int					i;

	if (glyph->length < 4) {
		HE_ERROR (HEC_GLYPH, HES_DATA_LENGTH_MISMATCH,
			"Specified glyph data undersized");
		return false;
	}
	
	radius = (float)*_hoops_RPPA++;
	if (radius == 0.0f) {
		HE_ERROR (HEC_GLYPH, HES_DEGENERATE_DEFINITION,
			"Specified glyph has radius zero");
		return false;
	}

	_hoops_IGGIH = (float)*_hoops_RPPA++;
	_hoops_CGGIH = (float)*_hoops_RPPA++;

	_hoops_GRGIH = 0.0f;
	
	glyph->flags = _hoops_ICIAP;

	while (_hoops_RPPA < end) {
		switch ((_hoops_SIAIP = _hoops_SAAIP (*_hoops_RPPA))) {
			case _hoops_PSIAP: {
				++_hoops_RPPA;
				if (_hoops_RPPA == end) { /* _hoops_RRGIH */
					glyph->scale = _hoops_SGIHR(_hoops_GRGIH)/radius;
					return true;				
				}
				HE_ERROR (HEC_GLYPH, HES_DATA_LENGTH_MISMATCH,
						"Specified data length is inconsistent with data");
				goto FAILED;
			}	break;

			case _hoops_HSIAP: {
				++_hoops_RPPA;
				glyph->flags |= _hoops_CCIAP;
				_hoops_CIAIP=true;
			}	break;

			case _hoops_ISIAP: {
				++_hoops_RPPA;
				if (!_hoops_CIAIP) {
					HE_ERROR (HEC_GLYPH, HES_DEGENERATE_DEFINITION,
							"Restarting fill when none has started, definition is degenerate");
					goto FAILED;
				}
			}	break;

			case _hoops_CSIAP: {
				++_hoops_RPPA;
				if (!_hoops_CIAIP) {
					HE_ERROR (HEC_GLYPH, HES_DEGENERATE_DEFINITION,
							"Ending fill when none has started, definition is degenerate");
					goto FAILED;
				}
				_hoops_CIAIP=false;
			}	break;

			case _hoops_SSIAP: {
				++_hoops_RPPA;
				if (_hoops_RPPA+4>end) break;
				/* _hoops_HCPI: 2 _hoops_ARGIH _hoops_RRGP */
				if (_hoops_RPPA[0] == _hoops_RPPA[2] || _hoops_RPPA[1] == _hoops_RPPA[3]) {
					HE_ERROR (HEC_GLYPH, HES_DEGENERATE_DEFINITION,
							"Ellipse definition is degenerate");
					goto FAILED;
				}
				
				for (i=0;i<2;i++) {
					float dx = (float)*_hoops_RPPA++ - _hoops_IGGIH;
					float _hoops_CRRAR = (float)*_hoops_RPPA++ - _hoops_CGGIH;

					_hoops_SGGIH = dx*dx+_hoops_CRRAR*_hoops_CRRAR;

					if (_hoops_SGGIH > glyph->scale) 
						_hoops_GRGIH = _hoops_SGGIH;
				}		

			}	break;

			case _hoops_GGCAP: {
				++_hoops_RPPA;
				if (_hoops_RPPA+6>end) break;
				/* _hoops_PGIS: 3 _hoops_ARGIH _hoops_RRGP */
				if ((_hoops_RPPA[0] == _hoops_RPPA[2] && _hoops_RPPA[1] == _hoops_RPPA[3]) ||
					(_hoops_RPPA[0] == _hoops_RPPA[4] && _hoops_RPPA[1] == _hoops_RPPA[5]) ||
					(_hoops_RPPA[2] == _hoops_RPPA[4] && _hoops_RPPA[3] == _hoops_RPPA[5])) {
					HE_ERROR (HEC_GLYPH, HES_COINCIDENT_POINT,
							"Arc definition includes coincident points");
					goto FAILED;
				}

				for (i=0;i<3;i++) {
					float dx = (float)*_hoops_RPPA++ - _hoops_IGGIH;
					float _hoops_CRRAR = (float)*_hoops_RPPA++ - _hoops_CGGIH;

					_hoops_SGGIH = dx*dx+_hoops_CRRAR*_hoops_CRRAR;

					if (_hoops_SGGIH > glyph->scale) 
						_hoops_GRGIH = _hoops_SGGIH;
				}		

			}	break;

			case _hoops_RGCAP:
			case _hoops_AGCAP: {
				++_hoops_RPPA;
				if (_hoops_RPPA+4>end) break;
				/* _hoops_HGGS: 2 _hoops_ARGIH _hoops_RRGP */
				if (_hoops_RPPA[0] == _hoops_RPPA[2] && _hoops_RPPA[1] == _hoops_RPPA[3]) {
					HE_ERROR (HEC_GLYPH, HES_DEGENERATE_DEFINITION,
							"Infinite ray or line definition is degenerate");
					goto FAILED;
				}
				if (_hoops_CIAIP) {
					HE_ERROR (HEC_GLYPH, HES_DEGENERATE_DEFINITION,
							"Defining infinite ray or line well filling, definition is degenerate ");
					goto FAILED;
				}
									
				for (i=0;i<2;i++) {
					float dx = (float)*_hoops_RPPA++ - _hoops_IGGIH;
					float _hoops_CRRAR = (float)*_hoops_RPPA++ - _hoops_CGGIH;

					_hoops_SGGIH = dx*dx+_hoops_CRRAR*_hoops_CRRAR;

					if (_hoops_SGGIH > glyph->scale) 
						_hoops_GRGIH = _hoops_SGGIH;
				}		
				glyph->flags |= _hoops_IGGS;
			}	break;

			case _hoops_PGCAP:
			case _hoops_HGCAP: {
				++_hoops_RPPA;
				glyph->flags |= _hoops_PAGS;
			}	break;

			case _hoops_IGCAP: {
				++_hoops_RPPA;
				_hoops_RPPA+=3;
				glyph->flags |= _hoops_HAGS;
			}	break;

			case _hoops_CGCAP: {
				++_hoops_RPPA;
				_hoops_RPPA+=1;
				glyph->flags |= _hoops_SCIAP;
			}	break;
			
			case _hoops_SGCAP: {
				++_hoops_RPPA;
				glyph->flags |= _hoops_RSIAP;
			}	break;

			case _hoops_ASIAP: 
			default: {
				++_hoops_RPPA;
				if (_hoops_SIAIP > 0) {
					/* _hoops_ISII: <_hoops_PRGIH> _hoops_ARGIH _hoops_RRGP */
					for (i=0;i<_hoops_SIAIP;i++) {
						float dx = (float)*_hoops_RPPA++ - _hoops_IGGIH;
						float _hoops_CRRAR = (float)*_hoops_RPPA++ - _hoops_CGGIH;

						_hoops_SGGIH = dx*dx+_hoops_CRRAR*_hoops_CRRAR;

						if (_hoops_SGGIH > glyph->scale) 
							_hoops_GRGIH = _hoops_SGGIH;
					}			   
				}
				else {
					char _hoops_HHCHR[MAX_ERRMSG]; 
					HE_ERROR (HEC_GLYPH, HES_INVALID_INPUT,
						   Sprintf_DD (_hoops_HHCHR, "Drawing code '%d' at offset %d is not valid", _hoops_SIAIP, _hoops_RPPA - glyph->data - 1));
					goto FAILED;
				}
			}	break;
		}
	}

	HE_ERROR (HEC_GLYPH, HES_DATA_LENGTH_MISMATCH,
			"Specified glyph data unterminated");

FAILED:
	return false;
}

#ifndef _hoops_HRGIH
local Attribute * _hoops_IRGIH (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR) 
{
	_hoops_AAAIR const *	_hoops_CRGIH = (_hoops_AAAIR const *)_hoops_CPACR;
	_hoops_AAAIR alter *	_hoops_SRGIH = (_hoops_AAAIR alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (item);

	ASSERT(_hoops_SRGIH->count == 1);

	if (_hoops_CRGIH) {

		for (int i=0; i<_hoops_CRGIH->count; i++) {
			if (_hoops_CRGIH->keys[i] == _hoops_SRGIH->keys[0] &&
				_hoops_RAHSR(_hoops_SRGIH->glyphs[0]->name, _hoops_CRGIH->glyphs[i]->name)) {

				/* _hoops_IIIAA _hoops_PPR _hoops_SRAI */
				_hoops_PGRCA(_hoops_CRGIH)->glyphs[i] = _hoops_SRGIH->glyphs[0];

				_hoops_SRGIH->glyphs[0] = null;
				FREE_ARRAY(_hoops_SRGIH->glyphs, 1, _hoops_GASC);
				FREE_ARRAY(_hoops_SRGIH->keys, 1, Integer32);

				_hoops_SRGIH->glyphs = _hoops_CRGIH->glyphs;
				_hoops_SRGIH->keys = _hoops_CRGIH->keys;
				_hoops_SRGIH->count = _hoops_CRGIH->count;

				_hoops_PGRCA(_hoops_CRGIH)->glyphs =null;
				_hoops_PGRCA(_hoops_CRGIH)->keys = null;
				_hoops_PGRCA(_hoops_CRGIH)->count = 0;

				return _hoops_SRGIH;
			}
		}

		// _hoops_HASC
		if (_hoops_CRGIH->count > 0) {
			int	count = _hoops_CRGIH->count+1;

			_hoops_GASC *	glyphs;
			ZALLOC_ARRAY(glyphs, count, _hoops_GASC);

			Integer32 *	keys;
			ALLOC_ARRAY(keys, count, Integer32);

			_hoops_AIGA(_hoops_SRGIH->glyphs, 1, _hoops_GASC, glyphs);
			_hoops_AIGA(_hoops_SRGIH->keys, 1, Integer32, keys);
			FREE_ARRAY(_hoops_SRGIH->glyphs, 1, _hoops_GASC);
			FREE_ARRAY(_hoops_SRGIH->keys, 1, Integer32);

			// _hoops_RGR _hoops_HRGR _hoops_HIGIP
			_hoops_AIGA(_hoops_CRGIH->keys, _hoops_CRGIH->count, Integer32, &keys[1]);
			_hoops_AIGA(_hoops_CRGIH->glyphs, _hoops_CRGIH->count, _hoops_GASC, &glyphs[1]);
			FREE_ARRAY(_hoops_CRGIH->glyphs, _hoops_CRGIH->count, _hoops_GASC);
			FREE_ARRAY(_hoops_CRGIH->keys, _hoops_CRGIH->count, Integer32);
			_hoops_PGRCA(_hoops_CRGIH)->glyphs =null;
			_hoops_PGRCA(_hoops_CRGIH)->keys = null;
			_hoops_PGRCA(_hoops_CRGIH)->count = 0;

			_hoops_SRGIH->glyphs = glyphs;
			_hoops_SRGIH->keys = keys;
			_hoops_SRGIH->count = count;
		}
	}

	return _hoops_SRGIH;
}


local _hoops_GASC _hoops_GAGIH (
	_hoops_HCRPR *			name,
	int				length,
	char const *	definition) {
	_hoops_GASC			glyph;

	/* _hoops_RARIR _hoops_RPHH */
	if (!definition) { 
		HE_WARNING (HEC_GLYPH, HES_INVALID_INPUT, 
				Sprintf_N (null, "Glyph '%n' has null definition ", &name));
		return null;
	}

	glyph = _hoops_GASC::Create();
	glyph->length = length;
	ALLOC_ARRAY(glyph->data, glyph->length, char);	
	_hoops_AIGA(definition, glyph->length, char, glyph->data);

	/*_hoops_SRAI _hoops_RSIRR*/
	glyph->name.text = name->text;
	glyph->name.length = name->length;
	name->text = null;
	name->length = 0;

	/* _hoops_GISA _hoops_IRS _hoops_CCAH _hoops_RPHH _hoops_IPPHR */
	if (!HI_Validate_Glyph(glyph)) {
		HE_WARNING (HEC_GLYPH, HES_INVALID_INPUT, 
				Sprintf_N (null, "Glyph '%n' has bad definition ", &glyph->name));
		return null;
	}

	_hoops_HCARA(glyph->name,glyph->key);

	return glyph;
}
#endif


GLOBAL_FUNCTION bool HI_Set_Glyph_Defs(
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_HPAH *				item, 
	_hoops_AAAIR *			glyph_defs)
{
	return HI_Set_Attribute (_hoops_RIGC, item, _hoops_RAAIR, _hoops_IRGIH, glyph_defs);
}


HC_INTERFACE void HC_CDECL HC_Define_Glyph (
	char const *			name,
	int						_hoops_RAGIH,
	char const *			definition) 
{
	_hoops_PAPPR context("Define_Glyph");

#ifdef _hoops_HRGIH
	_hoops_IRPPR ("Glyph");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_D (null, "{char definition[%d];\n", _hoops_RAGIH));
		++HOOPS_WORLD->_hoops_ISPPR;
		for (int i=0;i<_hoops_RAGIH;i++)
				HI_Dump_Code (Sprintf_DD (null, "definition[%d] = (char)%d;\n", i, (int)definition[i]));
		HI_Dump_Code (Sprintf_SD (null, "HC_Define_Glyph (%S, %d, definition);}\n", name, _hoops_RAGIH));
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_HCRPR	_hoops_CRPCR;

	HI_Canonize_Chars (name, &_hoops_CRPCR);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_GLYPH, HES_NULL_INPUT, "Glyph name is blank or null");
		return;
	}

	_hoops_GASC	glyph = _hoops_GAGIH(&_hoops_CRPCR, _hoops_RAGIH, definition);

	if (glyph != null) {

		bool			used = false;
		_hoops_AAAIR *	glyph_defs;
		ZALLOC (glyph_defs, _hoops_AAAIR);
		glyph_defs->count = 1;
		ZALLOC_ARRAY(glyph_defs->glyphs, 1, _hoops_GASC);
		ALLOC_ARRAY(glyph_defs->keys, 1, Integer32);

		glyph_defs->glyphs[0] = glyph;
		glyph_defs->keys[0] = glyph->key;

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_IARPP)) != null) {
			used = HI_Set_Glyph_Defs(context, target, glyph_defs);
			_hoops_IRRPR();
		}

		if (!used) {
			FREE_ARRAY(glyph_defs->glyphs, 1, _hoops_GASC);
			FREE_ARRAY(glyph_defs->keys, 1, Integer32);
			FREE (glyph_defs, _hoops_AAAIR);
		}
	}

	_hoops_RGAIR(_hoops_CRPCR);
#endif
}


GLOBAL_FUNCTION void HI_UnSet_Defined_Glyph(
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_HPAH *				item, 
	_hoops_HCRPR const &			_hoops_CRPCR) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_AAAIR * _hoops_AAGIH = (_hoops_AAAIR*) HI_Find_Attribute(_hoops_RIGC, item, -_hoops_RAAIR);

	if (!_hoops_AAGIH) {
		HE_ERROR (HEC_GLYPH, HES_INVALID_INPUT, "No Glyph definitions found");
		goto Release;
	}

	Integer32	key;

	_hoops_HCARA(_hoops_CRPCR,key); 

	for (int i=0; i<_hoops_AAGIH->count; ++i) {
		if (_hoops_AAGIH->keys[i] == key && _hoops_RAHSR(_hoops_CRPCR, _hoops_AAGIH->glyphs[i]->name)) {
			_hoops_AAGIH->glyphs[i] = null;

			if (_hoops_AAGIH->count == 1) {
				FREE_ARRAY(_hoops_AAGIH->glyphs, 1, _hoops_GASC);
				FREE_ARRAY(_hoops_AAGIH->keys, 1, Integer32);
				_hoops_AAGIH->glyphs = null;
				_hoops_AAGIH->keys = null;
				_hoops_AAGIH->count = 0;
			}
			else {
				_hoops_GASC *			_hoops_SPRIP;
				Integer32 *		new_keys;
				int				_hoops_RGCCA;

				_hoops_RGCCA = _hoops_AAGIH->count-1;

				ZALLOC_ARRAY(_hoops_SPRIP, _hoops_RGCCA, _hoops_GASC);
				ALLOC_ARRAY(new_keys, _hoops_RGCCA, Integer32);

				if (i > 0) {
					_hoops_AIGA(_hoops_AAGIH->glyphs, i, _hoops_GASC, _hoops_SPRIP);
					_hoops_AIGA(_hoops_AAGIH->keys, i, Integer32, new_keys);
				}

				if (i < _hoops_RGCCA) {
					_hoops_AIGA(&_hoops_AAGIH->glyphs[i+1], _hoops_RGCCA-i, _hoops_GASC, &_hoops_SPRIP[i]);
					_hoops_AIGA(&_hoops_AAGIH->keys[i+1], _hoops_RGCCA-i, Integer32, &new_keys[i]);
				}

				FREE_ARRAY(_hoops_AAGIH->glyphs, _hoops_AAGIH->count, _hoops_GASC);
				FREE_ARRAY(_hoops_AAGIH->keys, _hoops_AAGIH->count, Integer32);

				_hoops_AAGIH->glyphs = _hoops_SPRIP;
				_hoops_AAGIH->keys = new_keys;
				_hoops_AAGIH->count = _hoops_RGCCA;
			}

			goto Release;
		}
	}

	HE_WARNING (HEC_GLYPH, HES_INVALID_INPUT, Sprintf_N (null, "Glyph '%n' not found ",&_hoops_CRPCR));

Release:
	if (_hoops_AAGIH)
		_hoops_HPRH(_hoops_AAGIH);
}

HC_INTERFACE void HC_CDECL HC_UnDefine_Glyph (
	char const *			name) 
{

	_hoops_PAPPR context("UnDefine_Glyph");

#ifdef _hoops_PAGIH
	_hoops_IRPPR ("Glyph");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnDefine_Glyph (%S);\n", name));
	);

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars (name, &_hoops_CRPCR);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_GLYPH, HES_NULL_INPUT, "Glyph name is blank or null");
		return;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_IARPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Defined_Glyph(context, target, _hoops_CRPCR);
		_hoops_IRRPR();
	}

	_hoops_RGAIR(_hoops_CRPCR);
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Glyph (
	char const *		name,
	char *				definition) 
{
	_hoops_PAPPR context("Show_Glyph");

#ifdef _hoops_HRGIH
	_hoops_IRPPR ("Glyph");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Glyph () */\n");
	);

	definition[0] = '\0';

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars (name, &_hoops_CRPCR);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_GLYPH, HES_NULL_INPUT, "Glyph name is blank or null");
		return;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PCRPP)) != null) {

		_hoops_AAAIR *	_hoops_AAGIH;
		
		if ((_hoops_AAGIH = (_hoops_AAAIR *) HI_Find_Attribute(context, target, _hoops_RAAIR)) != null) {

			Integer32	key;
			_hoops_HCARA(_hoops_CRPCR,key); 

			for (int i=0; i<_hoops_AAGIH->count; i++) {
				if (_hoops_AAGIH->keys[i] == key&& _hoops_RAHSR(_hoops_CRPCR, _hoops_AAGIH->glyphs[i]->name)) {
					_hoops_GASC	glyph = _hoops_AAGIH->glyphs[i];
					HI_Return_Chars (definition, -1, glyph->data, (int)glyph->length-1);
					break;
				}
			}

			_hoops_HPRH(_hoops_AAGIH);
		}
		_hoops_IRRPR();
	}

	_hoops_RGAIR (_hoops_CRPCR);
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Glyph_Size (
	char const *			name,
	int *					size) 
{
	_hoops_PAPPR context("Show_Glyph_Size");

#ifdef _hoops_HRGIH
	_hoops_IRPPR ("Glyph");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Glyph_Size () */\n");
	);

	*size = 0;

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars (name, &_hoops_CRPCR);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_GLYPH, HES_NULL_INPUT, "Glyph name is blank or null");
		return;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PCRPP)) != null) {

		_hoops_AAAIR *	_hoops_AAGIH;

		if ((_hoops_AAGIH = (_hoops_AAAIR *) HI_Find_Attribute(context, target, _hoops_RAAIR)) != null) {

			Integer32	key;
			_hoops_HCARA(_hoops_CRPCR,key); 

			for (int i=0; i<_hoops_AAGIH->count; i++) {
				if (_hoops_AAGIH->keys[i] == key&& _hoops_RAHSR(_hoops_CRPCR, _hoops_AAGIH->glyphs[i]->name)) {
					_hoops_GASC	glyph = _hoops_AAGIH->glyphs[i];
					*size = (int)glyph->length;
					break;
				}
			}

			_hoops_HPRH(_hoops_AAGIH);
		}
		_hoops_IRRPR();
	}

	_hoops_RGAIR (_hoops_CRPCR);
#endif
}


HC_INTERFACE void HC_CDECL HC_PShow_Net_Glyph (
	int						count,
	Key const *				keys,
	char const *			name,
	char *					definition) 
{
	_hoops_PAPPR context("PShow_Net_Glyph");

#ifdef _hoops_HRGIH
	_hoops_IRPPR ("Glyph");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Glyph () */\n");
	);

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars (name, &_hoops_CRPCR);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_GLYPH, HES_NULL_INPUT, "Glyph name is blank or null");
		return;
	}

	*definition = '\0';

	_hoops_AAAIR * _hoops_AAGIH;
	if ((_hoops_AAGIH = (_hoops_AAAIR *) HI_Find_Attribute_And_Lock(context, _hoops_PCRPP, _hoops_HRPCR, count, keys)) != null) {

		_hoops_GASC		glyph;
		Integer32	key;

		_hoops_HCARA(_hoops_CRPCR,key); 

		for (int i=0; i<_hoops_AAGIH->count; i++) {
			if (_hoops_AAGIH->keys[i] == key&& _hoops_RAHSR(_hoops_CRPCR, _hoops_AAGIH->glyphs[i]->name)) {
				glyph = _hoops_AAGIH->glyphs[i];
				break;
			}
		}

		_hoops_HPRH(_hoops_AAGIH);

		if (!glyph) {
			HE_ERROR (HEC_GLYPH, HES_DEFINITION_NOT_FOUND,
				Sprintf_N (null, "Glyph '%n' not found", &_hoops_CRPCR));
		}
		else 
			HI_Return_Chars (definition, -1, glyph->data, (int)glyph->length-1);

		_hoops_IRRPR();
	}
	else
		HE_ERROR (HEC_GLYPH, HES_INVALID_INPUT, "No Glyph definitions found");

	_hoops_RGAIR (_hoops_CRPCR);
#endif
}



HC_INTERFACE void HC_CDECL HC_PShow_Net_Glyph_Size (
	int						count,
	Key const *				keys,
	char const *			name,
	int *					size) {
	_hoops_PAPPR context("PShow_Net_Glyph_Size");

#ifdef _hoops_HRGIH
	_hoops_IRPPR ("Glyph");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Glyph_Size () */\n");
	);

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars (name, &_hoops_CRPCR);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_GLYPH, HES_NULL_INPUT, "Glyph name is blank or null");
		return;
	}

	*size = 0;

	_hoops_AAAIR * _hoops_AAGIH;
	if ((_hoops_AAGIH = (_hoops_AAAIR *) HI_Find_Attribute_And_Lock(context, _hoops_PCRPP, _hoops_HRPCR, count, keys)) != null) {

		_hoops_GASC		glyph;
		Integer32	key;

		_hoops_HCARA(_hoops_CRPCR,key); 

		for (int i=0; i<_hoops_AAGIH->count; i++) {
			if (_hoops_AAGIH->keys[i] == key&& _hoops_RAHSR(_hoops_CRPCR, _hoops_AAGIH->glyphs[i]->name)) {
				glyph = _hoops_AAGIH->glyphs[i];
				break;
			}
		}

		_hoops_HPRH(_hoops_AAGIH);

		if (!glyph) {
			HE_ERROR (HEC_GLYPH, HES_DEFINITION_NOT_FOUND,
				Sprintf_N (null, "Glyph '%n' not found", &_hoops_CRPCR));
		}
		else 
			*size = (int) glyph->length;

		_hoops_IRRPR();
	}
	else
		HE_ERROR (HEC_GLYPH, HES_INVALID_INPUT, "No Glyph definitions found");

	_hoops_RGAIR (_hoops_CRPCR);
#endif
}




#ifndef DISABLE_SEARCH
#ifndef _hoops_HRGIH
local void _hoops_HAGIH(_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP * _hoops_SRCP)
{
	_hoops_SSPPR *		_hoops_GGHPR;
	_hoops_AGHPR *		node;

	ZALLOC (_hoops_GGHPR, _hoops_SSPPR);
	_hoops_GGHPR->prev = _hoops_RIGC->glyph_search_stack;
	_hoops_RIGC->glyph_search_stack = _hoops_GGHPR;

	if (_hoops_SRCP == null) {
		if (_hoops_RIGC->open_list != null && _hoops_RIGC->open_list->_hoops_GCRIR == _hoops_RCRIR ||
			HI_Find_Our_Open (_hoops_RIGC)) {

			if (_hoops_RIGC->open_list->_hoops_GCRIR == _hoops_RCRIR)
				_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_IGRPR;
			else {
				HE_ERROR (HEC_GLYPH, HES_NO_OPEN_SEGMENT, "Glyphs require open segment");
				return;
			}
		}
		else {
			HE_ERROR (HEC_GLYPH, HES_NO_OPEN_SEGMENT, "Glyph require open segment, none can be found");
			return;
		}
	}

	_hoops_AAAIR * _hoops_AAGIH = (_hoops_AAAIR *) HI_Find_Attribute(_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP, -_hoops_RAAIR);

	if (_hoops_AAGIH) {
		for (int i=0; i<_hoops_AAGIH->count; ++i) {
			_hoops_GASC *		glyph;

			ZALLOC (glyph, _hoops_GASC);
			*glyph = _hoops_AAGIH->glyphs[i];

			ZALLOC (node, _hoops_AGHPR);
			node->next = _hoops_GGHPR->list;
			_hoops_GGHPR->list = node;
			node->item = (_hoops_HPAH *)glyph;
			++_hoops_GGHPR->count;
		}

		_hoops_HPRH(_hoops_AAGIH);
	}

}
#endif
#endif


HC_INTERFACE void HC_CDECL HC_Begin_Glyph_Search (void) 
{
	_hoops_PAPPR context("Begin_Glyph_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef _hoops_HRGIH
	_hoops_IRPPR ("Glyph");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Begin_Glyph_Search () */\n");
		++HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_CSPPR();
	_hoops_HAGIH(context, null);
	_hoops_IRRPR();

#endif
#endif
}


HC_INTERFACE bool HC_CDECL HC_Find_Glyph (
	char *				_hoops_IAGIH) 
{	
	_hoops_PAPPR context("Find_Glyph");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef _hoops_HRGIH
	_hoops_IRPPR ("Glyph");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Find_Glyph () */\n");
	);

	_hoops_AGHPR	*			list;

	if (context->glyph_search_stack == null) {
		HE_ERROR (HEC_GLYPH, HES_INACTIVE_SEARCH,
				"No glyph search is active");
		return false;
	}

	if ((list = context->glyph_search_stack->list) != null) {
		_hoops_GASC *		item = (_hoops_GASC *)list->item;

		context->glyph_search_stack->list = list->next;
		FREE (list, _hoops_AGHPR);
		list = context->glyph_search_stack->list;

		HI_Return_Sprintf1 (_hoops_IAGIH, -1, "%n", (void *)&(*item)->name);

		*item = null;
		FREE (item, _hoops_GASC);

		return true;
	}
#endif
#endif

	return false;
}




HC_INTERFACE void HC_CDECL HC_Show_Glyph_Count (
	int *					count) {
	_hoops_SSPPR *			_hoops_GGHPR;
	_hoops_PAPPR context("Show_Glyph_Count");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef _hoops_HRGIH
	_hoops_IRPPR ("Glyph");
	*count = 0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Glyph_Count () */\n");
	);

	_hoops_GGHPR = context->glyph_search_stack;
	if (_hoops_GGHPR == null) {
		*count = 0;
		HE_ERROR (HEC_GLYPH, HES_INACTIVE_SEARCH, "No glyph search is active");
	}
	else
		*count = _hoops_GGHPR->count;
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_End_Glyph_Search (void) {
	_hoops_SSPPR *			_hoops_GGHPR;
	_hoops_AGHPR				*node, *_hoops_CAGIH;
	_hoops_PAPPR context("End_Glyph_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef _hoops_SAGIH
	_hoops_IRPPR ("Glyph");
#else
	CODE_GENERATION (
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("/* HC_End_Glyph_Search () */\n");
	);

	_hoops_GGHPR = context->glyph_search_stack;
	if (_hoops_GGHPR == null) {
		HE_ERROR (HEC_GLYPH, HES_END_WITHOUT_BEGIN_SEARCH, "End without Begin");
		return;
	}
	node = _hoops_GGHPR->list;

	while (node != null) {
		_hoops_CAGIH = node->next;

		_hoops_GASC *		item = (_hoops_GASC *) node->item;
		*item = null;
		FREE (item, _hoops_GASC);

		FREE (node, _hoops_AGHPR);
		node = _hoops_CAGIH;
	}
	context->glyph_search_stack = _hoops_GGHPR->prev;
	FREE (_hoops_GGHPR, _hoops_SSPPR);
#endif
#endif
}


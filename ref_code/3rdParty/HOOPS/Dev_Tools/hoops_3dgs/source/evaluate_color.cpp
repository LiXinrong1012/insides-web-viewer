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
 * $Id: obf_tmp.txt 1.150 2010-12-06 22:05:40 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "adt.h"

#define			_hoops_AHSAH				0.2f
#define			_hoops_PHSAH				0.35f
#define			_hoops_HHSAH				0.5f

#define			GLOSS_FLAG		-1.0f
#define			_hoops_IHSAH		-2.0f

struct token {
	struct token		*prev,
						*next;
	char				*start,			/* _hoops_SRS _hoops_GSPR */
						*end;			/* _hoops_CGHI _hoops_GSPR; _hoops_HAR _hoops_RHGGP _hoops_GRCIR _hoops_RPGR */
	int					_hoops_ARAHR;			/* _hoops_RRAS _hoops_IIGR _hoops_CHSAH */
	bool				_hoops_SHSAH;		/* _hoops_IHPR _hoops_RPP _hoops_RIAGR _hoops_GRCIR _hoops_RPGR */
};

struct _hoops_GISAH {
	_hoops_RCR *				texture;
	_hoops_HCRPR					name;
	RGB						color;
	float					_hoops_IRIR;
	float					gloss;
	float					_hoops_PAGRA;
	Material_Channel_Flags	flags;
	_hoops_ARGRA		_hoops_PRGRA;
};

local token		_hoops_RISAH;

local token * _hoops_AISAH (
	token const	*	_hoops_RIASA,
	token const	*	_hoops_PISAH,
	bool			errors) {

	if (errors) {
		token const	*		_hoops_CIPPR = _hoops_RIASA;
		char				buf[MAX_ERRMSG];
		char				*outp = buf,
							*_hoops_HISAH = null;

		_hoops_RGGA (_hoops_CIPPR->prev == null) _hoops_CIPPR = _hoops_CIPPR->prev;

		do {
			char	*_hoops_PASPA = _hoops_CIPPR->start;

			if (_hoops_CIPPR->end - _hoops_PASPA + 2 > buf+_hoops_GGAPR(buf) - outp) break;

			if (_hoops_CIPPR == _hoops_PISAH) _hoops_HISAH = outp;

			do *outp++ = *_hoops_PASPA++;
			_hoops_RGGA (_hoops_PASPA > _hoops_CIPPR->end);

			if (_hoops_CIPPR->_hoops_SHSAH) *outp++ = ' ';
		} _hoops_RGGA ((_hoops_CIPPR = _hoops_CIPPR->next) == null);

		if (outp[-1] == ' ') --outp;

		*outp = '\0';

		if (_hoops_HISAH == null)
			HE_ERROR2 (HEC_COLOR, HES_SYNTAX_ERROR,
						"Color syntax error or undefined color",
						Sprintf_S (null, "Color passed was '%s'", buf));
		else {
			char	_hoops_IISAH[MAX_ERRMSG];

			outp = _hoops_IISAH;
			_hoops_RGGA (outp - _hoops_IISAH == _hoops_HISAH - buf) *outp++ = '-';
			*outp++ = '^';
			*outp++ = '\0';

				HE_ERROR3 (HEC_COLOR, HES_SYNTAX_ERROR,
						"Color syntax error or undefined color",
							Sprintf_S (null,  "Color passed was '%s'", buf),
							Sprintf_S (_hoops_IISAH, "Error was near ---%s", _hoops_IISAH));
		}
	}

	return &_hoops_RISAH;
}

#ifndef DISABLE_COLOR_NAMES
local _hoops_RSHIR * _hoops_CISAH (
	_hoops_AIGPR *	_hoops_RIGC,
	token const *			_hoops_CIPPR,
	token alter **			_hoops_SISAH,
	bool					_hoops_GCSAH) {
	token const *			_hoops_RCSAH = _hoops_CIPPR;
	int						_hoops_ARAHR = _hoops_CIPPR->_hoops_ARAHR;
	int						id;
	
	id = _hoops_RIGC->_hoops_IAPCR;

	if (_hoops_RSPPR(_hoops_RIGC, _hoops_SCHPP) == null) 
		return null;

	_hoops_RGGA (_hoops_RCSAH->prev == null) {
		_hoops_RCSAH = _hoops_RCSAH->prev;
		_hoops_ARAHR += _hoops_RCSAH->_hoops_ARAHR;
		if (_hoops_RCSAH->_hoops_SHSAH) _hoops_ARAHR += ' ';
	}

	_hoops_PCCAR {
		_hoops_RSHIR	*_hoops_ICHIR;

		/*** _hoops_PGCR'_hoops_GRI _hoops_HSPPR _hoops_RGAR! ***/
		_hoops_ICHIR = _hoops_RSPPR(_hoops_RIGC, _hoops_SCHPP)[_hoops_ARAHR & (_hoops_GSHPP - 1)];

		_hoops_RGGA (_hoops_ICHIR == null) {
			int				_hoops_SCPPR = _hoops_CIPPR->end - _hoops_RCSAH->start + 1;

			if (_hoops_ICHIR->name.length == _hoops_SCPPR &&
				(_hoops_GCSAH || _hoops_ICHIR->degree == _hoops_RGGPP)) {
				char	*_hoops_RPPA = _hoops_RCSAH->start,
										*_hoops_GSPPR = _hoops_ICHIR->name.text;

				while (*_hoops_RPPA++ == *_hoops_GSPPR++) if (--_hoops_SCPPR == 0) {
					*_hoops_SISAH = _hoops_RCSAH->prev;
					return _hoops_ICHIR;
				}
			}

			_hoops_ICHIR = _hoops_ICHIR->_hoops_SSCAP;
		}

		if (_hoops_RCSAH->next == null) return null;

		_hoops_ARAHR -= _hoops_RCSAH->_hoops_ARAHR;
		if (_hoops_RCSAH->_hoops_SHSAH) _hoops_ARAHR -= ' ';
		_hoops_RCSAH = _hoops_RCSAH->next;
	}
}
#endif

#ifndef DISABLE_TEXTURING
local token const * _hoops_ACSAH (
	token const *			_hoops_CIPPR,
	_hoops_CPAIR const *	_hoops_CICSR,
	_hoops_RCR	 **				_hoops_PCSAH) {
	token const *			_hoops_RCSAH = _hoops_CIPPR;
	token const *			_hoops_HPIS = _hoops_CIPPR;
	
	if (!_hoops_CICSR) {
#define _hoops_HCSAH 1024
		_hoops_RCR *	_hoops_ICSAH;
		_hoops_HCRPR		name;
		char *		_hoops_RPPA;

		_hoops_RGGA (_hoops_RCSAH->prev == null)
			_hoops_RCSAH = _hoops_RCSAH->prev;

		_hoops_RPPA = _hoops_RCSAH->start;
		name.length = _hoops_CIPPR->end - _hoops_RCSAH->start + 1;

		if (_hoops_RCSAH == _hoops_CIPPR &&	_hoops_CIPPR->start != _hoops_CIPPR->end && *_hoops_CIPPR->start == *_hoops_CIPPR->end &&
			(*_hoops_CIPPR->start == '"' || *_hoops_CIPPR->start == '\'' || *_hoops_CIPPR->start == '`')) {
			_hoops_RPPA++;
			name.length -= 2;
		}

		ALLOC_ARRAY (name.text, name.length+1, char);
		_hoops_AIGA (_hoops_RPPA, name.length, char, name.text);
		name.text[name.length] = '\0';

		_hoops_ICSAH = HI_Clone_Texture(0);

		/* _hoops_SRAI _hoops_RSIRR */
		ZALLOC(_hoops_ICSAH->_hoops_PAPIR, _hoops_AAPIR);
		_hoops_ICSAH->_hoops_PAPIR->name.text = name.text;
		_hoops_ICSAH->_hoops_PAPIR->name.length = name.length;
		_hoops_HCARA (_hoops_ICSAH->_hoops_PAPIR->name,_hoops_ICSAH->_hoops_PAPIR->key);
		_hoops_ICSAH->flags|=TF_UNEVALUATED;

		/* _hoops_CSICP _hoops_RGR _hoops_GGR _hoops_GIPR _hoops_CCSAH _hoops_PPR _hoops_RSIRR _hoops_IRHH _hoops_RII _hoops_RRGR _hoops_SCSAH */
		HI_Copy_Name (&_hoops_ICSAH->_hoops_PAPIR->name, &_hoops_ICSAH->name); 
		_hoops_ICSAH->key = _hoops_ICSAH->_hoops_PAPIR->key;

		*_hoops_PCSAH =  _hoops_ICSAH;

		/* _hoops_RGR _hoops_HRGR _hoops_HAR _hoops_SSRR _hoops_HCCPR _hoops_GSSAH _hoops_APIGP _hoops_GPP _hoops_HHH _hoops_HPS */
		return _hoops_RCSAH->prev;
#undef _hoops_HCSAH
	}

	_hoops_RGGA (_hoops_RCSAH->prev == null) {
		_hoops_RCSAH = _hoops_RCSAH->prev;
	}

	_hoops_PCCAR {
		int				length = _hoops_CIPPR->end - _hoops_RCSAH->start + 1;
		bool			_hoops_RSSAH = false;

		if (_hoops_RCSAH == _hoops_CIPPR &&	_hoops_CIPPR->start != _hoops_CIPPR->end && *_hoops_CIPPR->start == *_hoops_CIPPR->end &&
			(*_hoops_CIPPR->start == '"' || *_hoops_CIPPR->start == '\'' || *_hoops_CIPPR->start == '`')) {
			_hoops_RSSAH = true;
			length -= 2;
		}

		/* _hoops_PSSP _hoops_ASSAH _hoops_PIRA */
		_hoops_HCRPR name;
		name.length = length;
		name.text = _hoops_RCSAH->start;
		if (_hoops_RSSAH)
			name.text++;

		Integer32 key;
		_hoops_HCARA (name,key);

		for (int i=0; i<_hoops_CICSR->count; i++) {
			if (key == _hoops_CICSR->keys[i]) {
				Integer32		n = length;
				_hoops_RCR *		texture = _hoops_CICSR->textures[i];

				if (texture->name.length == n) {
					char *		_hoops_RPPA = _hoops_RCSAH->start;
					char *		_hoops_GSPPR = texture->name.text;

					if (_hoops_RSSAH)
						++_hoops_RPPA;

					while (*_hoops_RPPA++ == *_hoops_GSPPR++) if (--n == 0) {
						*_hoops_PCSAH = HI_Activate_Texture (texture, _hoops_CICSR, true);
						return _hoops_RCSAH->prev;
					}
				}
			}
		}

		if (_hoops_RCSAH->next == null) 
			return _hoops_HPIS;

		/* _hoops_CGGR _hoops_RH _hoops_RIPS _hoops_ICRP _hoops_AAS _hoops_PSAP _hoops_PPR _hoops_CACH _hoops_RPP _hoops_SGS _hoops_HRGR _hoops_IRS _hoops_HH */
		/* _hoops_RGR _hoops_CRHPR _hoops_CGSI _hoops_PII _hoops_HSP=_hoops_PRRRA _hoops_PSSAH _hoops_IPHR */

		_hoops_RCSAH = _hoops_RCSAH->next;
	}

	return _hoops_HPIS;
}
#endif


local void _hoops_HSSAH (
	_hoops_PACHR alter *			_hoops_SHGCR,
	_hoops_PACHR const *			_hoops_ISSAH,
	double				_hoops_CSSAH) {
	float				_hoops_CGSIR = (float)_hoops_CSSAH;

	/* _hoops_GHAA _hoops_SSSAH _hoops_IS _hoops_AIRA */
	float				_hoops_CASSR;
	float				_hoops_GGGPH;


	if (_hoops_SHGCR->_hoops_ISPHR == 0.0f)
		_hoops_SHGCR->_hoops_SCPHR = _hoops_ISSAH->_hoops_SCPHR;
	else if (_hoops_ISSAH->_hoops_ISPHR == 0.0f) {
		/* _hoops_ISAP _hoops_IS _hoops_AA */
	}
	else {
		float	_hoops_RGGPH = _hoops_ISSAH->_hoops_SCPHR - _hoops_SHGCR->_hoops_SCPHR;

		if (_hoops_RGGPH > 180.0f)
			_hoops_RGGPH -= 360.0f;
		else if (_hoops_RGGPH < -180.0f)
			_hoops_RGGPH += 360.0f;

		_hoops_SHGCR->_hoops_SCPHR += _hoops_RGGPH * _hoops_CGSIR * _hoops_ISSAH->_hoops_ISPHR;

		if (_hoops_SHGCR->_hoops_SCPHR >= 360.0f)
			_hoops_SHGCR->_hoops_SCPHR -= 360.0f;
		else if (_hoops_SHGCR->_hoops_SCPHR < 0.0f)
			_hoops_SHGCR->_hoops_SCPHR += 360.0f;
	}

/* _hoops_SCRI _hoops_HCSAA _hoops_SHRRR _hoops_GGR _hoops_HRAGP _hoops_GC _hoops_RPP _hoops_SIGR -- _hoops_AAAIA */

	if (_hoops_SHGCR->_hoops_HSPHR > 0.999	 ||	 _hoops_SHGCR->_hoops_HSPHR  < 0.001) {
		if (_hoops_ISSAH->_hoops_HSPHR > 0.999	||	_hoops_ISSAH->_hoops_HSPHR	< 0.001)
			_hoops_GGGPH = 0.0f;			/* _hoops_SSSAH _hoops_HRGR _hoops_APRP _hoops_PAR _hoops_PGS */
		else {
			/* _hoops_GRAS _hoops_SSSAH _hoops_AGGPH */
			if (_hoops_ISSAH->_hoops_HSPHR <= 0.5)
				_hoops_GGGPH = _hoops_ISSAH->_hoops_ISPHR / (2.0f * _hoops_ISSAH->_hoops_HSPHR);
			else
				_hoops_GGGPH = _hoops_ISSAH->_hoops_ISPHR / (2.0f - 2.0f * _hoops_ISSAH->_hoops_HSPHR);
		}
		/* _hoops_AIRA _hoops_HRGR _hoops_APRP _hoops_PAR _hoops_PGS, _hoops_ARP _hoops_AIRA _hoops_AGGPH _hoops_IS _hoops_PSSP _hoops_SSSAH */
		_hoops_CASSR = _hoops_GGGPH;
	}
	else  {
		/* _hoops_GRAS _hoops_AIRA _hoops_AGGPH */
		if (_hoops_SHGCR->_hoops_HSPHR <= 0.5)
			_hoops_CASSR = _hoops_SHGCR->_hoops_ISPHR / (2.0f * _hoops_SHGCR->_hoops_HSPHR);
		else
			_hoops_CASSR = _hoops_SHGCR->_hoops_ISPHR / (2.0f - 2.0f * _hoops_SHGCR->_hoops_HSPHR);

		if (_hoops_ISSAH->_hoops_HSPHR > 0.999	||	_hoops_ISSAH->_hoops_HSPHR	< 0.001) {
			/* _hoops_SSSAH _hoops_HRGR _hoops_APRP _hoops_PAR _hoops_PGS, _hoops_ARP _hoops_SSSAH _hoops_AGGPH _hoops_IS _hoops_PSSP _hoops_AIRA */
			_hoops_GGGPH = _hoops_CASSR;
		}
		else  {
			/* _hoops_GRAS _hoops_SSSAH _hoops_AGGPH */
			if (_hoops_ISSAH->_hoops_HSPHR <= 0.5)
				_hoops_GGGPH = _hoops_ISSAH->_hoops_ISPHR / (2.0f * _hoops_ISSAH->_hoops_HSPHR);
			else
				_hoops_GGGPH = _hoops_ISSAH->_hoops_ISPHR / (2.0f - 2.0f * _hoops_ISSAH->_hoops_HSPHR);
		}
	}
	_hoops_CASSR += (_hoops_GGGPH - _hoops_CASSR) * _hoops_CGSIR;

	_hoops_SHGCR->_hoops_HSPHR += (_hoops_ISSAH->_hoops_HSPHR - _hoops_SHGCR->_hoops_HSPHR) * _hoops_CGSIR;


/* _hoops_SICR _hoops_AGGPH _hoops_ISSC _hoops_IS _hoops_HCSAA */

	if (_hoops_SHGCR->_hoops_HSPHR <= 0.5f)
		_hoops_SHGCR->_hoops_ISPHR = _hoops_CASSR * 2.0f * _hoops_SHGCR->_hoops_HSPHR;
	else
		_hoops_SHGCR->_hoops_ISPHR = _hoops_CASSR * (2.0f - 2.0f * _hoops_SHGCR->_hoops_HSPHR);
}


/* _hoops_GASA: _hoops_PCHIA _hoops_RGR _hoops_API _hoops_GAR _hoops_HAAI _hoops_GAR _hoops_HAIR _hoops_PAIGR _hoops_CHR _hoops_ISAIA _hoops_IS _hoops_PGGPH'_hoops_GRI _hoops_RIIA _hoops_IIGR 
 * _hoops_ACGIP _hoops_GCHR */
local bool _hoops_HGGPH (
	_hoops_GISAH *			_hoops_SHGCR,
	Named_Material *			_hoops_ISSAH,
	int							degree,
	bool						errors) {
	float						_hoops_CGSIR;

	/* _hoops_HGI _hoops_PCPH _hoops_APPP _hoops_IRS _hoops_HAIR: *_hoops_AIRA _hoops_PPR _hoops_HPIH _hoops_HAIR *_hoops_SSSAH _hoops_PPR
	** _hoops_SHPH *_hoops_AIRA _hoops_GGR _hoops_HGHC _hoops_HPP _hoops_CGGRA _hoops_GGR *_hoops_SSSAH.
	*/

	/* _hoops_IGGPH _hoops_PSHA _hoops_SGS _hoops_RCPS _hoops_GGR _hoops_RHIR _hoops_ARI _hoops_CHR "_hoops_CGGPH" _hoops_PAR "_hoops_SGGPH" _hoops_PSHA _hoops_PPR
	** _hoops_CIPAA _hoops_RH *_hoops_AIRA _hoops_HAIR.
	** _hoops_CGP _hoops_SR _hoops_HGCR _hoops_IRS "_hoops_AIRA" _hoops_HAIR _hoops_PII "_hoops_PRRRA", _hoops_SR _hoops_HS _hoops_RH "_hoops_GC" _hoops_PCGR
	** _hoops_GRGPH.
	*/
	if (degree == _hoops_RGGPP) {
		/* "_hoops_GC _hoops_GRGPH" -- _hoops_SRS _hoops_SPR (_hoops_RRGPH) _hoops_AGGRA */
		/* _hoops_PAAS _hoops_GHGA _hoops_PSHA _hoops_PII "_hoops_SCAC _hoops_ARGPH" */

		if (ALLBITS (_hoops_ISSAH->_hoops_PRGRA, _hoops_SHGCR->_hoops_PRGRA)) {
			if (errors)
				HE_WARNING (HEC_COLOR, HES_BASE_COLOR_OVERRIDE,
						"Modifier color completely overrides the base color");
		}

		if (BIT (_hoops_ISSAH->_hoops_PRGRA, M_DIFFUSE)) {
			_hoops_SHGCR->color = _hoops_ISSAH->_hoops_CSHR;				 
			_hoops_RGAIR (_hoops_SHGCR->name);
			HI_Copy_Name (&_hoops_ISSAH->_hoops_IRGRA, &_hoops_SHGCR->name);
		}
		if (BIT (_hoops_ISSAH->_hoops_PRGRA, _hoops_RHGRA)) {
			if (_hoops_SHGCR->texture)
				_hoops_HPRH (_hoops_SHGCR->texture);
			_hoops_SHGCR->texture = _hoops_ISSAH->_hoops_SCA->texture;
			_hoops_PRRH (_hoops_SHGCR->texture);
		}
		if (BIT (_hoops_ISSAH->_hoops_PRGRA, M_TRANSMISSION))
			_hoops_SHGCR->_hoops_IRIR = _hoops_ISSAH->_hoops_IRIR;

		if (BIT (_hoops_ISSAH->_hoops_PRGRA, _hoops_RAGRA))
			_hoops_SHGCR->gloss = _hoops_ISSAH->gloss;

		if (BIT (_hoops_ISSAH->_hoops_PRGRA, _hoops_AAGRA))
			_hoops_SHGCR->_hoops_PAGRA = _hoops_ISSAH->_hoops_PAGRA;

		_hoops_SHGCR->_hoops_PRGRA |= _hoops_ISSAH->_hoops_PRGRA;
	}
	else {
		/* _hoops_IAR _hoops_CPRP _hoops_IGGA _hoops_IGPC */
		/* _hoops_PGGA _hoops_SR _hoops_HS _hoops_PCCP "_hoops_CGGPH", "_hoops_SGGPH", _hoops_PAR "-" _hoops_GAR _hoops_IRS _hoops_RRGPH _hoops_IIGR *_hoops_AIRA */
		if (degree == _hoops_HGGPP) {
			/* _hoops_PAAS _hoops_GRP _hoops_RH "-" _hoops_GRGPH, _hoops_RSIPR _hoops_SSSAH _hoops_GHCRH _hoops_AIRA _hoops_PAH _hoops_HS _hoops_GII
			** _hoops_AI.
			*/
			if (ANYBIT (_hoops_ISSAH->_hoops_PRGRA | _hoops_SHGCR->_hoops_PRGRA, _hoops_PSARA)) {
				if (errors)
					HE_ERROR (HEC_TEXTURE, HES_MAY_NOT_HAVE_TEXTURES,
							"Components of modifier and base color may not have textures");
				return false;
			}
			if (_hoops_ISSAH->_hoops_PRGRA != _hoops_SHGCR->_hoops_PRGRA) {
				if (errors)
					HE_ERROR (HEC_COLOR, HES_COLOR_COMPONENTS_MISMATCH,
							"Components of modifier and base color do not match");
				return false;
			}
		}
		else {
			/* _hoops_PS _hoops_CHR _hoops_GGR _hoops_RH "-_hoops_SGGPH" _hoops_PAR "-_hoops_CGGPH" _hoops_AGIR */

			/* _hoops_PAAS _hoops_GRP _hoops_RH "-_hoops_SGGPH/_hoops_CGGPH" _hoops_GAHIR, _hoops_SSSAH _hoops_GHCA _hoops_HAR _hoops_HS _hoops_GII _hoops_AI,
			** _hoops_PPR _hoops_GII _hoops_AI _hoops_SGS *_hoops_AIRA _hoops_SSCP _hoops_GRS _hoops_SHH _hoops_IAIH _hoops_GAR _hoops_SGIP _hoops_GAR
			** _hoops_CGGRA _hoops_IAGA.	 (_hoops_IPCP _hoops_IPSP _hoops_CGH _hoops_ASRS _hoops_AI _hoops_GRP _hoops_PRGPH)
			*/
			if (ANYBIT (_hoops_ISSAH->_hoops_PRGRA, _hoops_PSARA)) {
				if (errors)
					HE_ERROR (HEC_TEXTURE, HES_MAY_NOT_HAVE_TEXTURES,
							"Modifier color may not have textures");
				return false;
			}
			if (ANYBIT (_hoops_ISSAH->_hoops_PRGRA, ~_hoops_SHGCR->_hoops_PRGRA)) {
				if (errors)
					HE_ERROR (HEC_COLOR, HES_BASE_COLOR_OVERRIDE,
							"Modifier color contains components not present in base color");
				return false;
			}
		}

		switch (degree) {
			case _hoops_HGGPP:			_hoops_CGSIR = _hoops_HHSAH; break;
			case _hoops_AGGPP:	_hoops_CGSIR = _hoops_PHSAH;	break;
			case _hoops_PGGPP:	_hoops_CGSIR = _hoops_AHSAH;	break;

			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unknown color modification level");
				return false;
			}
		}

		_hoops_HSSAH ((_hoops_PACHR alter *)&_hoops_SHGCR->color, (_hoops_PACHR const *)&_hoops_ISSAH->_hoops_CSHR, _hoops_CGSIR);
		_hoops_RGAIR (_hoops_SHGCR->name);

		if (BIT (_hoops_ISSAH->_hoops_PRGRA, M_TRANSMISSION)) 
			_hoops_ISSAH->_hoops_IRIR = 1.0f - ((_hoops_PACHR const &)_hoops_ISSAH->color[_hoops_PCA])._hoops_HSPHR;

		if (BIT (_hoops_ISSAH->_hoops_PRGRA, _hoops_RAGRA))
			_hoops_SHGCR->gloss += (_hoops_ISSAH->gloss - _hoops_SHGCR->gloss) * _hoops_CGSIR;

		if (BIT (_hoops_ISSAH->_hoops_PRGRA, _hoops_AAGRA))
			_hoops_SHGCR->_hoops_PAGRA +=
				(_hoops_ISSAH->_hoops_PAGRA - _hoops_SHGCR->_hoops_PAGRA) * _hoops_CGSIR;
	}

	return true;
}



local bool _hoops_HRGPH (
	_hoops_GISAH *		_hoops_SHGCR,
	_hoops_GISAH *		_hoops_ISSAH,
	int						degree,
	bool					errors) {
	float					_hoops_CGSIR;

	/* _hoops_HGI _hoops_PCPH _hoops_APPP _hoops_IRS _hoops_HAIR: *_hoops_AIRA _hoops_PPR _hoops_HPIH _hoops_HAIR *_hoops_SSSAH _hoops_PPR
	** _hoops_SHPH *_hoops_AIRA _hoops_GGR _hoops_HGHC _hoops_HPP _hoops_CGGRA _hoops_GGR *_hoops_SSSAH.
	*/

	/* _hoops_IGGPH _hoops_PSHA _hoops_SGS _hoops_RCPS _hoops_GGR _hoops_RHIR _hoops_ARI _hoops_CHR "_hoops_CGGPH" _hoops_PAR "_hoops_SGGPH" _hoops_PSHA _hoops_PPR
	** _hoops_CIPAA _hoops_RH *_hoops_AIRA _hoops_HAIR.
	** _hoops_CGP _hoops_SR _hoops_HGCR _hoops_IRS "_hoops_AIRA" _hoops_HAIR _hoops_PII "_hoops_PRRRA", _hoops_SR _hoops_HS _hoops_RH "_hoops_GC" _hoops_PCGR
	** _hoops_GRGPH.
	*/
	if (degree == _hoops_RGGPP) {
		/* "_hoops_GC _hoops_GRGPH" -- _hoops_SRS _hoops_SPR (_hoops_RRGPH) _hoops_AGGRA */
		/* _hoops_PAAS _hoops_GHGA _hoops_PSHA _hoops_PII "_hoops_SCAC _hoops_ARGPH" */

		if (ALLBITS (_hoops_ISSAH->_hoops_PRGRA, _hoops_SHGCR->_hoops_PRGRA)) {
			if (errors)
				HE_WARNING (HEC_COLOR, HES_BASE_COLOR_OVERRIDE,
						"Modifier color completely overrides the base color");
		}

		if (BIT (_hoops_ISSAH->_hoops_PRGRA, M_DIFFUSE)) {
			_hoops_SHGCR->color = _hoops_ISSAH->color;				 
			_hoops_RGAIR (_hoops_SHGCR->name);
			HI_Copy_Name (&_hoops_ISSAH->name, &_hoops_SHGCR->name);
		}
		if (BIT (_hoops_ISSAH->_hoops_PRGRA, _hoops_RHGRA)) {
			if (_hoops_SHGCR->texture)
				_hoops_HPRH (_hoops_SHGCR->texture);
			_hoops_SHGCR->texture = _hoops_ISSAH->texture;
			_hoops_PRRH (_hoops_SHGCR->texture);
		}
		if (BIT (_hoops_ISSAH->_hoops_PRGRA, M_TRANSMISSION))
			_hoops_SHGCR->_hoops_IRIR = _hoops_ISSAH->_hoops_IRIR;

		if (BIT (_hoops_ISSAH->_hoops_PRGRA, _hoops_RAGRA))
			_hoops_SHGCR->gloss = _hoops_ISSAH->gloss;

		if (BIT (_hoops_ISSAH->_hoops_PRGRA, _hoops_AAGRA))
			_hoops_SHGCR->_hoops_PAGRA = _hoops_ISSAH->_hoops_PAGRA;

		_hoops_SHGCR->_hoops_PRGRA |= _hoops_ISSAH->_hoops_PRGRA;
	}
	else {
		/* _hoops_IAR _hoops_CPRP _hoops_IGGA _hoops_IGPC */
		/* _hoops_PGGA _hoops_SR _hoops_HS _hoops_PCCP "_hoops_CGGPH", "_hoops_SGGPH", _hoops_PAR "-" _hoops_GAR _hoops_IRS _hoops_RRGPH _hoops_IIGR *_hoops_AIRA */
		if (degree == _hoops_HGGPP) {
			/* _hoops_PAAS _hoops_GRP _hoops_RH "-" _hoops_GRGPH, _hoops_IRGPH _hoops_SSSAH _hoops_GHCRH _hoops_AIRA _hoops_PAH _hoops_HS _hoops_GII
			** _hoops_AI.
			*/
			if (ANYBIT (_hoops_ISSAH->_hoops_PRGRA | _hoops_SHGCR->_hoops_PRGRA, _hoops_PSARA)) {
				if (errors)
					HE_ERROR (HEC_TEXTURE, HES_MAY_NOT_HAVE_TEXTURES,
							"Components of modifier and base color may not have textures");
				return false;
			}
			if (_hoops_ISSAH->_hoops_PRGRA != _hoops_SHGCR->_hoops_PRGRA) {
				if (errors)
					HE_ERROR (HEC_COLOR, HES_COLOR_COMPONENTS_MISMATCH,
							"Components of modifier and base color do not match");
				return false;
			}
		}
		else {
			/* _hoops_PS _hoops_CHR _hoops_GGR _hoops_RH "-_hoops_SGGPH" _hoops_PAR "-_hoops_CGGPH" _hoops_AGIR */

			/* _hoops_PAAS _hoops_GRP _hoops_RH "-_hoops_SGGPH/_hoops_CGGPH" _hoops_GAHIR, _hoops_SSSAH _hoops_GHCA _hoops_HAR _hoops_HS _hoops_GII _hoops_AI,
			** _hoops_PPR _hoops_GII _hoops_AI _hoops_SGS *_hoops_AIRA _hoops_SSCP _hoops_GRS _hoops_SHH _hoops_IAIH _hoops_GAR _hoops_SGIP _hoops_GAR
			** _hoops_CGGRA _hoops_IAGA.	 (_hoops_IPCP _hoops_IPSP _hoops_CGH _hoops_ASRS _hoops_AI _hoops_GRP _hoops_PRGPH)
			*/
			if (ANYBIT (_hoops_ISSAH->_hoops_PRGRA, _hoops_PSARA)) {
				if (errors)
					HE_ERROR (HEC_TEXTURE, HES_MAY_NOT_HAVE_TEXTURES,
							"Modifier color may not have textures");
				return false;
			}
			if (ANYBIT (_hoops_ISSAH->_hoops_PRGRA, ~_hoops_SHGCR->_hoops_PRGRA)) {
				if (errors)
					HE_ERROR (HEC_COLOR, HES_BASE_COLOR_OVERRIDE,
							"Modifier color contains components not present in base color");
				return false;
			}
		}

		switch (degree) {
			case _hoops_HGGPP:			_hoops_CGSIR = _hoops_HHSAH; break;
			case _hoops_AGGPP:	_hoops_CGSIR = _hoops_PHSAH;	break;
			case _hoops_PGGPP:	_hoops_CGSIR = _hoops_AHSAH;	break;

			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unknown color modification level");
				return false;
			}
		}

		_hoops_HSSAH ((_hoops_PACHR alter *)&_hoops_SHGCR->color, (_hoops_PACHR const *)&_hoops_ISSAH->color, _hoops_CGSIR);
		_hoops_RGAIR (_hoops_SHGCR->name);

		if (BIT (_hoops_ISSAH->_hoops_PRGRA, M_TRANSMISSION)) 
			_hoops_ISSAH->_hoops_IRIR = _hoops_ISSAH->_hoops_IRIR;

		if (BIT (_hoops_ISSAH->_hoops_PRGRA, _hoops_RAGRA))
			_hoops_SHGCR->gloss += (_hoops_ISSAH->gloss - _hoops_SHGCR->gloss) * _hoops_CGSIR;

		if (BIT (_hoops_ISSAH->_hoops_PRGRA, _hoops_AAGRA))
			_hoops_SHGCR->_hoops_PAGRA +=
				(_hoops_ISSAH->_hoops_PAGRA - _hoops_SHGCR->_hoops_PAGRA) * _hoops_CGSIR;
	}

	return true;
}



local token * _hoops_CRGPH (
	_hoops_HCRPR const *	_hoops_SRGPH) {
	char			*ref = _hoops_SRGPH->text,
					*_hoops_GAGPH = ref + _hoops_SRGPH->length;
	token *			_hoops_CIPPR;

	ALLOC (_hoops_CIPPR, token);
	_hoops_CIPPR->prev = null;

	_hoops_PCCAR {
		int				_hoops_ARAHR = 0;
		char			_hoops_PPARA = '\0';

		_hoops_CIPPR->start = ref;

		do switch (_hoops_IRGCR(*ref)) {
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
			case '.': if (ref == _hoops_CIPPR->start && !_hoops_PPARA) {
				/* _hoops_HPPR _hoops_IS _hoops_PPPCR _hoops_GGSR _hoops_IRS _hoops_HHGPR _hoops_PHI */
				while (ref < _hoops_GAGPH && '0' <= *ref	&&	*ref <= '9')
					_hoops_ARAHR += *ref++;
				if (ref < _hoops_GAGPH && *ref == '.')  _hoops_ARAHR+= *ref++;
				while (ref < _hoops_GAGPH && '0' <= *ref	&&	*ref <= '9')
					_hoops_ARAHR += *ref++;
				if (ref < _hoops_GAGPH && *ref == 'e') {
					_hoops_ARAHR += *ref++;
					if (*ref == '+' || *ref == '-')	 _hoops_ARAHR += *ref++;
					while (ref < _hoops_GAGPH && '0' <= *ref	&&	*ref <= '9')
						_hoops_ARAHR += *ref++;
				}
				if (ref == _hoops_GAGPH ||
					 *ref == ' ' || *ref == '\0' || *ref == ')')
					/* _hoops_CRPRA _hoops_GGSR _hoops_IS _hoops_IRS _hoops_HHGPR _hoops_PHI */
					goto _hoops_PCPPR;
				break;
			}	/**** _hoops_HSSC _hoops_RHIR _hoops_RPP "_hoops_PHI" _hoops_CPSA _hoops_ARIP _hoops_IIGR _hoops_GSGR ****/

			case 'a': case 'b': case 'c': case 'd': case 'e':
			case 'f': case 'g': case 'h': case 'i': case 'j':
			case 'k': case 'l': case 'm': case 'n': case 'o':
			case 'p': case 'q': case 'r': case 's': case 't':
			case 'u': case 'v': case 'w': case 'x': case 'y':
			case 'z': case '+': case '_': {
				_hoops_ARAHR += *ref++;
			}	break;

			case '"': case '\'': case '`': {
				if (*ref == _hoops_PPARA || !_hoops_PPARA) {
					if (*ref == _hoops_PPARA && ref[1] == _hoops_PPARA) {
						/* _hoops_RGR _hoops_API _hoops_PAH'_hoops_RA _hoops_RGHH _hoops_IPARA _hoops_CPARA.  _hoops_HCHGA _hoops_PPR _hoops_HPPR _hoops_GICS */
						token *		_hoops_RAGPH;
						do {
							_hoops_RAGPH = _hoops_CIPPR->prev;
							FREE (_hoops_CIPPR, token);
						} _hoops_RGGA ((_hoops_CIPPR = _hoops_RAGPH) == null);
						return null;
					}
					_hoops_PPARA ^= *ref;
				}
				_hoops_ARAHR += *ref++;
			}	break;

			default: {
				if (_hoops_PPARA) {
					_hoops_ARAHR += *ref++;
					break;
				}
				/* _hoops_RPP _hoops_IIH _hoops_CHR _hoops_PSP _hoops_AAGPH, _hoops_PSCR _hoops_RH _hoops_AAS _hoops_HRGR _hoops_SPS _hoops_GAS */
				if (ref == _hoops_CIPPR->start && ref != _hoops_GAGPH) _hoops_ARAHR = *ref++;
			}	goto _hoops_PCPPR;
		} _hoops_RGGA (ref == _hoops_GAGPH);

		_hoops_PCPPR:;

		_hoops_CIPPR->_hoops_ARAHR = _hoops_ARAHR;
		_hoops_CIPPR->end = ref - 1;

		if (ref == _hoops_GAGPH) {
			_hoops_CIPPR->_hoops_SHSAH = false;
			_hoops_CIPPR->next = null;
			break;		/* _hoops_HCR _hoops_CPHR! */
		}
		else if (*ref == ' ') {
			_hoops_CIPPR->_hoops_SHSAH = true;
			++ref;
		}
		else {
			_hoops_CIPPR->_hoops_SHSAH = false;
		}

		{	token *		_hoops_PAGPH = _hoops_CIPPR;
			ALLOC (_hoops_CIPPR, token);
			_hoops_CIPPR->prev = _hoops_PAGPH;
			_hoops_PAGPH->next = _hoops_CIPPR;
		}
	}

	return _hoops_CIPPR;
}


local token const * _hoops_HAGPH (
	_hoops_AIGPR *	_hoops_RIGC,
	token const	*			_hoops_RIASA,
	token const *			_hoops_CIPPR,
	bool					errors,
	char alter *			_hoops_IAGPH,
	float alter *			_hoops_CAGPH) 
{

	/* _hoops_PPPCR _hoops_IHHPP (_hoops_PAR _hoops_PGGRA) '=' _hoops_AIIC _hoops_CIAAR */

	if (_hoops_CIPPR == null) 
		return _hoops_AISAH (_hoops_RIASA, null, errors);
	if (_hoops_CIPPR->prev == null) 
		return _hoops_AISAH (_hoops_RIASA, _hoops_CIPPR, errors);
	if (_hoops_CIPPR->prev->prev == null) 
		return _hoops_AISAH (_hoops_RIASA, _hoops_CIPPR->prev, errors);

	char const *	_hoops_RPPA = _hoops_CIPPR->start;
	if (HI_Scan_Float (_hoops_RIGC, &_hoops_RPPA, _hoops_CIPPR->end+1, _hoops_CAGPH) != null)
		return _hoops_AISAH (_hoops_RIASA, _hoops_CIPPR, errors);

	_hoops_CIPPR = _hoops_CIPPR->prev;
	if (*_hoops_CIPPR->start == '-') {
		*_hoops_CAGPH = -*_hoops_CAGPH;
		_hoops_CIPPR = _hoops_CIPPR->prev;
		if (_hoops_CIPPR->prev == null) return _hoops_AISAH (_hoops_RIASA, _hoops_CIPPR, errors);
	}
	if (*_hoops_CIPPR->start != '=') return _hoops_AISAH (_hoops_RIASA, _hoops_CIPPR, errors);
	_hoops_CIPPR = _hoops_CIPPR->prev;

	if (_hoops_CIPPR->start != _hoops_CIPPR->end) {
		/* _hoops_ISPR _hoops_IH _hoops_GRH _hoops_ARAR: _hoops_IGPRA & _hoops_CIHA */
		int				length;

		_hoops_RPPA = _hoops_CIPPR->start;
		length = _hoops_CIPPR->end - _hoops_CIPPR->start + 1;

		if (length == 5 &&
			_hoops_RPPA[0] == 'g' &&
			_hoops_RPPA[1] == 'l' &&
			_hoops_RPPA[2] == 'o' &&
			_hoops_RPPA[3] == 's' &&
			_hoops_RPPA[4] == 's') *_hoops_IAGPH = 'g';

		else if (length == 5 &&
				 _hoops_RPPA[0] == 'i' &&
				 _hoops_RPPA[1] == 'n' &&
				 _hoops_RPPA[2] == 'd' &&
				 _hoops_RPPA[3] == 'e' &&
				 _hoops_RPPA[4] == 'x') *_hoops_IAGPH = 'n';

		else
			return _hoops_AISAH (_hoops_RIASA, _hoops_CIPPR, errors);
	}
	else
		*_hoops_IAGPH = *_hoops_CIPPR->start;


	_hoops_CIPPR = _hoops_CIPPR->prev;

	return _hoops_CIPPR;
}


local token const * _hoops_SAGPH (
	_hoops_AIGPR *	_hoops_RIGC,
	token const	*			_hoops_RIASA,
	token const *			_hoops_CIPPR,
	bool					errors,
	_hoops_PACHR alter *				color,
	_hoops_HCRPR alter *			name) 
{
	float				_hoops_HAGR[3];
	char				spec[3];

	name->length = 0;

	_hoops_CIPPR = _hoops_HAGPH (_hoops_RIGC, _hoops_RIASA, _hoops_CIPPR, errors, &spec[2], &_hoops_HAGR[2]);
	if (_hoops_CIPPR == &_hoops_RISAH) 
		return _hoops_CIPPR;

	if (spec[2] == 'g') {
		if (_hoops_HAGR[2] > 1e3f || _hoops_HAGR[2] < 1e-3f) {
			if (errors)
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE,"Gloss is unreasonable");
			return &_hoops_RISAH;
		}

		color->_hoops_SCPHR = GLOSS_FLAG;
		color->_hoops_HSPHR = _hoops_HAGR[2];
		return _hoops_CIPPR;
	}
	else if (spec[2] == 'n') {
		if (_hoops_HAGR[2] > 1e2f || _hoops_HAGR[2] < 1e-2f) {
			if (errors)
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE,"Index (of refraction) is unreasonable");
			return &_hoops_RISAH;
		}

		color->_hoops_SCPHR = _hoops_IHSAH;
		color->_hoops_HSPHR = _hoops_HAGR[2];
		return _hoops_CIPPR;
	}

	_hoops_CIPPR = _hoops_HAGPH (_hoops_RIGC, _hoops_RIASA, _hoops_CIPPR, errors, &spec[1], &_hoops_HAGR[1]);
	if (_hoops_CIPPR == &_hoops_RISAH) return _hoops_CIPPR;
	_hoops_CIPPR = _hoops_HAGPH (_hoops_RIGC, _hoops_RIASA, _hoops_CIPPR, errors, &spec[0], &_hoops_HAGR[0]);
	if (_hoops_CIPPR == &_hoops_RISAH) return _hoops_CIPPR;

	if (spec[0] == 'h' && (spec[1] == 'l' || spec[1] == 'i') &&
		spec[2] == 's') {
		if (_hoops_HAGR[0] > 1e5f || _hoops_HAGR[0] < -1e5f) {
			if (errors)
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_HUE,"Hue is unreasonable");
			return &_hoops_RISAH;
		}

		while (_hoops_HAGR[0] >= 360.0f) _hoops_HAGR[0] -= 360.0f;
		while (_hoops_HAGR[0] < 0.0f) _hoops_HAGR[0] += 360.0f;

		if (_hoops_HAGR[1] > 1.0f || _hoops_HAGR[1] < 0.0f) {
			if (errors)
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_LIGHTNESS,"Lightness out of range (must be 0 to 1)");
			return &_hoops_RISAH;
		}

		if ((_hoops_HAGR[1] > 0.5f && _hoops_HAGR[2] > 2.0f - 2.0f*_hoops_HAGR[1]) ||
			(_hoops_HAGR[1] <= 0.5f && _hoops_HAGR[2] > 2.0f*_hoops_HAGR[1]) || _hoops_HAGR[2] < 0.0f) {
			if (errors)
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_SATURATION,"Saturation out of range (range is a function of lightness)");
			return &_hoops_RISAH;
		}

		color->_hoops_SCPHR = _hoops_HAGR[0];
		color->_hoops_HSPHR = _hoops_HAGR[1];
		color->_hoops_ISPHR = _hoops_HAGR[2];
	}
	else if (spec[0] == 'h' && spec[1] == 'i' && spec[2] == 'c') {
		if (_hoops_HAGR[0] > 1e5f || _hoops_HAGR[0] < -1e5f) {
			if (errors)
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_HUE,"Hue is unreasonable");
			return &_hoops_RISAH;
		}

		while (_hoops_HAGR[0] >= 360.0f) _hoops_HAGR[0] -= 360.0f;
		while (_hoops_HAGR[0] < 0.0f) _hoops_HAGR[0] += 360.0f;

		if (_hoops_HAGR[2] > 1.0f || _hoops_HAGR[2] < 0.0f) {
			if (errors)
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_CHROMACITY,"Chromaticity (saturation) out of range (must be 0 to 1)");
			return &_hoops_RISAH;
		}

		if (_hoops_HAGR[1] > 1.0f || _hoops_HAGR[1] < 0.0f) {
			if (errors)
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_LIGHTNESS,"Intensity (lightness) out of range (must be 0 to 1)");
			return &_hoops_RISAH;
		}

		color->_hoops_SCPHR = _hoops_HAGR[0];
		if (_hoops_HAGR[1] <= 0.5f)
			color->_hoops_ISPHR = _hoops_HAGR[2] * 2.0f*_hoops_HAGR[1];
		else
			color->_hoops_ISPHR = _hoops_HAGR[2] * (2.0f - 2.0f*_hoops_HAGR[1]);

		color->_hoops_HSPHR = _hoops_HAGR[1];
	}
	else if (spec[0] == 'h' && spec[1] == 's' && spec[2] == 'v') {
		if (_hoops_HAGR[0] > 1e5f || _hoops_HAGR[0] < -1e5f) {
			if (errors)
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_HUE,"Hue is unreasonable");
			return &_hoops_RISAH;
		}

		while (_hoops_HAGR[0] >= 360.0f) _hoops_HAGR[0] -= 360.0f;
		while (_hoops_HAGR[0] < 0.0f) _hoops_HAGR[0] += 360.0f;

		if (_hoops_HAGR[2] > 1.0f || _hoops_HAGR[2] < 0.0f) {
			if (errors)
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_LIGHTNESS,"'Value' (lightness) out of range (must be 0 to 1)");
			return &_hoops_RISAH;
		}

		if (_hoops_HAGR[1] > _hoops_HAGR[2] || _hoops_HAGR[1] < 0.0f) {
			if (errors)
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_SATURATION,"Saturation out of range (must be between 0 and 'Value')");
			return &_hoops_RISAH;
		}

		color->_hoops_SCPHR = _hoops_HAGR[0];
		color->_hoops_ISPHR = _hoops_HAGR[1];
		color->_hoops_HSPHR = _hoops_HAGR[2] - 0.5f * _hoops_HAGR[1];
	}
	else if (spec[0] == 'r' && spec[1] == 'g' && spec[2] == 'b') {
		RGB			rgb;

		if (_hoops_HAGR[0] < 0.0f || _hoops_HAGR[0] > 1.0f) {
			if (errors)
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_RED,"Value for Red out of range (must be 0 to 1)");
			return &_hoops_RISAH;
		}
		if (_hoops_HAGR[1] < 0.0f || _hoops_HAGR[1] > 1.0f) {
			if (errors)
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_GREEN,"Value for Green out of range (must be 0 to 1)");
			return &_hoops_RISAH;
		}
		if (_hoops_HAGR[2] < 0.0f || _hoops_HAGR[2] > 1.0f) {
			if (errors)
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_BLUE,"Value for Blue out of range (must be 0 to 1)");
			return &_hoops_RISAH;
		}

		rgb.red = _hoops_HAGR[0];
		rgb.green = _hoops_HAGR[1];
		rgb.blue = _hoops_HAGR[2];

		HI_RGB_To_HLS (&rgb, color);
	}
	else
		return _hoops_AISAH (_hoops_RIASA, _hoops_CIPPR, errors);

	return _hoops_CIPPR;
}


local token const * _hoops_GPGPH (
	_hoops_AIGPR *		_hoops_RIGC,
	token const *				_hoops_RIASA,	/* _hoops_RPGPH _hoops_IIGR _hoops_APGPH */
	token const *				_hoops_CIPPR,		/* _hoops_PPGPH */
	_hoops_CPAIR const *		_hoops_CICSR,		/* _hoops_HPGPH */
	bool						errors,
	_hoops_GISAH *			_hoops_IPGPH) {
	_hoops_RSHIR *				_hoops_ICHIR;
	_hoops_SCHIR *					_hoops_GSHIR;
	token const *				_hoops_CPGPH = _hoops_CIPPR;
	_hoops_RCR *					texture = null;

	/* _hoops_GRAS _hoops_SPR _hoops_APRAR _hoops_HAIR, _hoops_APHR _hoops_HPGR _hoops_SPGPH */

	/* _hoops_SIAS _hoops_SHH _hoops_CHCA _hoops_PAR _hoops_PAPR _hoops_HAIR */

#ifndef DISABLE_TEXTURING
	if (_hoops_AGGR (_hoops_CIPPR->start, "off")) {
		_hoops_IPGPH->texture = null;
		_hoops_IPGPH->_hoops_PRGRA = _hoops_GHGPH;
		return _hoops_CIPPR->prev;
	}

	if (_hoops_CICSR)
		_hoops_CPGPH = _hoops_ACSAH (_hoops_CIPPR, _hoops_CICSR, &texture);
	if (texture) {
		_hoops_CIPPR = _hoops_CPGPH;
		_hoops_IPGPH->texture = texture;
		_hoops_IPGPH->_hoops_PRGRA = _hoops_GHGPH;
	}
	else 
#endif
#ifndef DISABLE_COLOR_NAMES
	if ((_hoops_ICHIR = _hoops_CISAH (_hoops_RIGC, _hoops_CIPPR, (token **)&_hoops_CPGPH, false)) != null) {
		_hoops_RIASA = _hoops_CIPPR = _hoops_CPGPH;
		_hoops_GSHIR = _hoops_ICHIR->_hoops_AAPPR;
		_hoops_RSAI (&_hoops_GSHIR->_hoops_ISHIR._hoops_CSHR, _hoops_PACHR, &_hoops_IPGPH->color);
		_hoops_RGAIR (_hoops_IPGPH->name);
		HI_Copy_Name (&_hoops_ICHIR->name, &_hoops_IPGPH->name);
		_hoops_IPGPH->_hoops_PRGRA = _hoops_RHGPH;
	}
	else
#endif
	{
		/* _hoops_IPCP _hoops_RSIRR _hoops_CSAP _hoops_HAR _hoops_IRS _hoops_HSSPR _hoops_HH _hoops_RSIRR, _hoops_GHCRH _hoops_IRS _hoops_HSSPR _hoops_HAIR _hoops_PHPPR,
		** _hoops_IIS'_hoops_GRI _hoops_CACH _hoops_RPP _hoops_SCH _hoops_HRGR _hoops_PCCP _hoops_AHGPH= _hoops_PHGPH= _hoops_IHAC= _hoops_PAR _hoops_HHGPH ...
		*/
		_hoops_PACHR					color;
		_hoops_HCRPR					name;

		do {
			/* _hoops_IHGPH _hoops_GACC _hoops_APPP _hoops_PICP _hoops_IIGR _hoops_RH _hoops_GRH _hoops_AGIR _hoops_IH
			** _hoops_IGPRA _hoops_PPR _hoops_CHGPH.
			*/
			bool _hoops_SHGPH = errors && (_hoops_CICSR != null);

			_hoops_CPGPH = _hoops_CIPPR;
			if (_hoops_CIPPR->start != _hoops_CIPPR->end && *_hoops_CIPPR->start == *_hoops_CIPPR->end &&
				(*_hoops_CIPPR->start == '"' || *_hoops_CIPPR->start == '\'' || *_hoops_CIPPR->start == '`')) {
				_hoops_HCRPR					_hoops_GIGPH;
				token const *			_hoops_RIGPH;
				token const *			_hoops_RAGPH;
				token alter *			victim;

				_hoops_GIGPH.length = _hoops_CIPPR->end - _hoops_CIPPR->start - 1;
				ALLOC_ARRAY (_hoops_GIGPH.text, _hoops_GIGPH.length+1, char);
				_hoops_AIGA (_hoops_CIPPR->start+1, _hoops_GIGPH.length, char, _hoops_GIGPH.text);
				_hoops_GIGPH.text[_hoops_GIGPH.length] = '\0';
				_hoops_RAGPH = _hoops_RIGPH = _hoops_CRGPH (&_hoops_GIGPH);
				if (!_hoops_RAGPH) {
					_hoops_RGAIR (_hoops_GIGPH);
					HI_Canonize_Chars_Quoted (_hoops_CIPPR->start, &_hoops_GIGPH, false);
					_hoops_RAGPH = _hoops_RIGPH = _hoops_CRGPH (&_hoops_GIGPH);
				}

				_hoops_RAGPH = _hoops_SAGPH (_hoops_RIGC, _hoops_RIGPH, _hoops_RAGPH, _hoops_SHGPH, &color, &name);
				if (_hoops_RAGPH == &_hoops_RISAH)
					_hoops_CIPPR = &_hoops_RISAH;
				else
					_hoops_CIPPR = _hoops_CIPPR->prev;
				/* _hoops_CIH _hoops_IRHP _hoops_AAS _hoops_HIGR */
				victim = (token alter *)_hoops_RIGPH;
				do {
					_hoops_RAGPH = victim->prev;
					FREE (victim, token);
				} _hoops_RGGA ((victim = (token alter *)_hoops_RAGPH) == null);
				_hoops_RGAIR (_hoops_GIGPH);
			}
			else
				_hoops_CIPPR = _hoops_SAGPH (_hoops_RIGC, _hoops_RIASA, _hoops_CIPPR, _hoops_SHGPH, &color, &name);

#ifndef DISABLE_TEXTURING
			if (_hoops_CIPPR == &_hoops_RISAH) {

				/* _hoops_SPIC _hoops_ISSC _hoops_IS _hoops_AIGPH _hoops_IIGR _hoops_HAIR _hoops_RSIRR */
				while (_hoops_CPGPH->next) 
					_hoops_CPGPH = _hoops_CPGPH->next;
				
				_hoops_CIPPR = _hoops_CPGPH;
				/* _hoops_ARI _hoops_SR _hoops_RRP _hoops_IS _hoops_IGGRA _hoops_PII _hoops_SR _hoops_SAHR _hoops_GGHP _hoops_IRS _hoops_HH _hoops_RSIRR */
				/* _hoops_RGR _hoops_GRS _hoops_ARPR _hoops_IRS _hoops_PIGPH _hoops_HH _hoops_CCA _hoops_IRS _hoops_RSIRR */
				_hoops_CPGPH = _hoops_ACSAH (_hoops_CIPPR, 0, &texture);

				_hoops_CIPPR = _hoops_CPGPH;

				_hoops_IPGPH->_hoops_PRGRA |= _hoops_GHGPH;
				HI_Copy_Name (&texture->name, &_hoops_IPGPH->name);

				/* _hoops_PSSRH _hoops_GGR _hoops_ARI */
				/* _hoops_SGSS _hoops_HRGR 1 _hoops_AIAH */
				if (_hoops_CICSR) {
					_hoops_IPGPH->texture = HI_Activate_Texture (texture, _hoops_CICSR, true);
					_hoops_HPRH(texture);
				}
				else
					_hoops_IPGPH->texture = texture;

			}
			else 
#endif
			if ((_hoops_CIPPR == &_hoops_RISAH)) {
				return _hoops_CIPPR;
			}
			else if (color._hoops_SCPHR == GLOSS_FLAG) {
				_hoops_IPGPH->_hoops_PRGRA |= _hoops_RAGRA;
				_hoops_IPGPH->gloss = color._hoops_HSPHR;
			}
			else if (color._hoops_SCPHR == _hoops_IHSAH) {
				_hoops_IPGPH->_hoops_PRGRA |= _hoops_AAGRA;
				_hoops_IPGPH->_hoops_PAGRA = color._hoops_HSPHR;
			}
			else {
				_hoops_PACHR alter &		_hoops_HACHR = (_hoops_PACHR alter &)_hoops_IPGPH->color;

				_hoops_HACHR._hoops_SCPHR			= color._hoops_SCPHR;
				_hoops_HACHR._hoops_HSPHR	= color._hoops_HSPHR;
				_hoops_HACHR._hoops_ISPHR	= color._hoops_ISPHR;
				HI_Copy_Name (&name, &_hoops_IPGPH->name);
				_hoops_IPGPH->_hoops_PRGRA |= _hoops_RHGPH;
			}
		} _hoops_RGGA (_hoops_CIPPR == null || *_hoops_CIPPR->start == ',' ||
				 *_hoops_CIPPR->start == '(' || *_hoops_CIPPR->start == '=');
	}

	/* _hoops_SIAS _hoops_HS '-' _hoops_PAR _hoops_HIGPH _hoops_HA (_hoops_CRSH _hoops_HPIPR) */

	_hoops_RGGA (_hoops_CIPPR == null) {
		/* _hoops_RRGPH: _hoops_RRHSA _hoops_PAPR, _hoops_HAIR -_hoops_CGGPH, _hoops_PAR _hoops_HAIR -_hoops_SGGPH */
		/* _hoops_IRAA _hoops_GAR _hoops_AHPH _hoops_GAR _hoops_SR _hoops_PAH _hoops_SSS */

#ifndef DISABLE_COLOR_NAMES
		if ((_hoops_ICHIR = _hoops_CISAH (_hoops_RIGC, _hoops_CIPPR, (token **)&_hoops_CPGPH, true)) != null) {
			_hoops_CIPPR = _hoops_CPGPH;
			/* _hoops_SRSA _hoops_GASA: _hoops_SICR _hoops_RGR _hoops_IS _hoops_IRS _hoops_IIGPH _hoops_GAR _hoops_HAAI _hoops_GAR _hoops_HAIR _hoops_PAIGR
			 * _hoops_PAH _hoops_SHH _hoops_ISAIA _hoops_HII _hoops_CIGPH _hoops_IAPR _hoops_IS _hoops_PHIGR _hoops_GRIP */
			if (!_hoops_HGGPH (_hoops_IPGPH, &_hoops_ICHIR->_hoops_AAPPR->_hoops_ISHIR, _hoops_ICHIR->degree, errors))
				return &_hoops_RISAH;
		}
		else
#endif
		if (_hoops_CIPPR->prev != null && _hoops_CIPPR->prev->prev != null &&
			(*_hoops_CIPPR->prev->start == '-' ||
			 *_hoops_CIPPR->prev->start == ')') &&
			((_hoops_CIPPR->end - _hoops_CIPPR->start == 1 &&
			  _hoops_CIPPR->start[0] == 'e' &&
			  _hoops_CIPPR->start[1] == 'r') ||
			 (_hoops_CIPPR->end - _hoops_CIPPR->start == 2 &&
			  _hoops_CIPPR->start[0] == 'i' &&
			  _hoops_CIPPR->start[1] == 's' &&
			  _hoops_CIPPR->start[2] == 'h'))) {
			if (_hoops_CIPPR->end - _hoops_CIPPR->start == 1) {
				/* "_hoops_SGGPH" */
				_hoops_GISAH				_hoops_SIGPH;

				_hoops_CIPPR = _hoops_CIPPR->prev;
				if (*_hoops_CIPPR->start == '-') _hoops_CIPPR = _hoops_CIPPR->prev;

				_hoops_SIGPH._hoops_PRGRA = false;

				_hoops_CIPPR = _hoops_GPGPH (_hoops_RIGC, _hoops_RIASA, _hoops_CIPPR, _hoops_CICSR, errors, &_hoops_SIGPH);
				if (_hoops_CIPPR == &_hoops_RISAH) return _hoops_CIPPR;

				if (!_hoops_HRGPH (_hoops_IPGPH, &_hoops_SIGPH, _hoops_AGGPP, errors))
					return &_hoops_RISAH;
			}
			else {
				/* "_hoops_CGGPH" */
				_hoops_GISAH				_hoops_GCGPH;

				_hoops_CIPPR = _hoops_CIPPR->prev;
				if (*_hoops_CIPPR->start == '-') _hoops_CIPPR = _hoops_CIPPR->prev;

				_hoops_GCGPH._hoops_PRGRA = false;

				_hoops_CIPPR = _hoops_GPGPH (_hoops_RIGC, _hoops_RIASA, _hoops_CIPPR, _hoops_CICSR, errors, &_hoops_GCGPH);
				if (_hoops_CIPPR == &_hoops_RISAH) return _hoops_CIPPR;

				if (!_hoops_HRGPH (_hoops_IPGPH, &_hoops_GCGPH, _hoops_PGGPP, errors))
					return &_hoops_RISAH;
			}
		}
		else if (*_hoops_CIPPR->start != '-' &&
				 *_hoops_CIPPR->start != '(' &&
				 *_hoops_CIPPR->start != '=' &&
				 *_hoops_CIPPR->start != ',') {
			_hoops_GISAH					_hoops_RCGPH;
			token const *					start = _hoops_CIPPR;

			ZERO_STRUCT (&_hoops_RCGPH, _hoops_GISAH);
			_hoops_CIPPR = _hoops_GPGPH (_hoops_RIGC, _hoops_RIASA, _hoops_CIPPR, _hoops_CICSR, errors, &_hoops_RCGPH);
			if (_hoops_CIPPR == &_hoops_RISAH) return _hoops_CIPPR;

			if (_hoops_CIPPR != start) {
				if (!_hoops_CICSR && _hoops_RCGPH._hoops_PRGRA == _hoops_GHGPH) {
					if (_hoops_RCGPH.texture)
						_hoops_HPRH (_hoops_RCGPH.texture);
					_hoops_RGAIR (_hoops_RCGPH.name);
				}
				else if (!_hoops_HRGPH (_hoops_IPGPH, &_hoops_RCGPH, _hoops_RGGPP, errors)) {
					if (_hoops_RCGPH.texture)
						_hoops_HPRH (_hoops_RCGPH.texture);
					_hoops_RGAIR (_hoops_RCGPH.name);
					return &_hoops_RISAH;
				}
			}
			else {
				if (_hoops_RCGPH.texture)
					_hoops_HPRH (_hoops_RCGPH.texture);
				_hoops_RGAIR (_hoops_RCGPH.name);
				break;	/* _hoops_HAR _hoops_IRS _hoops_RRGPH; _hoops_HGCR _hoops_GGSR _hoops_IIGR _hoops_ARI */
			}
		}
		else break;		/* _hoops_HAR _hoops_IRS _hoops_RRGPH; _hoops_HGCR _hoops_GGSR _hoops_IIGR _hoops_ARI */
	}

	if (_hoops_CIPPR != null && *_hoops_CIPPR->start == '-') {	/* _hoops_AASHR _hoops_IIGR _hoops_PGCR */
		_hoops_GISAH						_hoops_RCGPH;

		if ((_hoops_CIPPR = _hoops_CIPPR->prev) == null)
			return _hoops_AISAH (_hoops_RIASA, null, errors);

		ZERO_STRUCT (&_hoops_RCGPH, _hoops_GISAH);
		_hoops_CIPPR = _hoops_GPGPH (_hoops_RIGC, _hoops_RIASA, _hoops_CIPPR, _hoops_CICSR, errors, &_hoops_RCGPH);
		if (_hoops_CIPPR == &_hoops_RISAH) 
			return _hoops_CIPPR;
		if (_hoops_CIPPR != null && *_hoops_CIPPR->start == '-') { /* _hoops_PAH'_hoops_RA _hoops_HS _hoops_RSIRR-_hoops_RSIRR-_hoops_RSIRR */
			if (_hoops_RCGPH.texture != null)
				_hoops_HPRH (_hoops_RCGPH.texture);
			_hoops_RGAIR (_hoops_RCGPH.name);
			return _hoops_AISAH (_hoops_RIASA, _hoops_CIPPR, errors);
		}

		if (!_hoops_HRGPH (_hoops_IPGPH, &_hoops_RCGPH, _hoops_HGGPP, errors)) {
			if (_hoops_RCGPH.texture != null)
				_hoops_HPRH (_hoops_RCGPH.texture);
			_hoops_RGAIR (_hoops_RCGPH.name);
			return &_hoops_RISAH;
		}

		if (_hoops_RCGPH.texture != null)
			_hoops_HPRH (_hoops_RCGPH.texture);
		_hoops_RGAIR (_hoops_RCGPH.name);
	}

	return _hoops_CIPPR;
} /* _hoops_RSGR _hoops_API '_hoops_HGCR _hoops_HAIR' */


local void _hoops_ACGPH (token * _hoops_RIASA) {
	token *		_hoops_CIPPR;

	do {
		_hoops_CIPPR = _hoops_RIASA->prev;
		FREE (_hoops_RIASA, token);
	} _hoops_RGGA ((_hoops_RIASA = _hoops_CIPPR) == null);
}


local bool _hoops_PCGPH (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HCRPR const *			name,
	_hoops_CPAIR const *	_hoops_CICSR,
	int						_hoops_HGA,
	bool					errors,
	_hoops_ARGRA		_hoops_PRGRA,
	Named_Material *		_hoops_ISHIR) {
	token const *			_hoops_RIASA;
	token const *			_hoops_CIPPR;
	int						i;
	_hoops_HCRPR					_hoops_HCGPH = { null, 0 };
	bool					status = false;
	_hoops_GISAH			_hoops_ICGPH;

	/* _hoops_SRSGR _hoops_PIIA-_hoops_AGR _hoops_AAS _hoops_HIGR */
	_hoops_CIPPR = _hoops_RIASA = _hoops_CRGPH (name);
	if (!_hoops_CIPPR) {
		/* _hoops_RPP _hoops_RH _hoops_HAIR _hoops_GIHRR _hoops_IPARA _hoops_HPARA _hoops_HPS (_hoops_IAS._hoops_ISHI. '_hoops_CCGPH''_hoops_GRI _hoops_HH'),
		 * _hoops_SCH _hoops_HRGR _hoops_HAR _hoops_SSRR _hoops_IS _hoops_SCGPH _hoops_CCA _hoops_CICRR _hoops_CRGR _hoops_RH _hoops_RSIRR.  _hoops_PS _hoops_RRP _hoops_IS 
		 * _hoops_IRHH _hoops_IRS _hoops_IHIR _hoops_IPS */
		HI_Canonize_Chars_Quoted (name->text, &_hoops_HCGPH, false);
		name = &_hoops_HCGPH;
		_hoops_CIPPR = _hoops_RIASA = _hoops_CRGPH (name);
	}

	/* _hoops_GRAS _hoops_SPR _hoops_APRAR _hoops_HAIR, _hoops_APHR _hoops_HPGR _hoops_SPGPH */

	/* _hoops_SIAS _hoops_SHH _hoops_CHCA _hoops_PAR _hoops_PAPR _hoops_HAIR */
	ZERO_STRUCT (&_hoops_ICGPH, _hoops_GISAH);
	_hoops_ICGPH._hoops_PRGRA = _hoops_GSGPH;
	_hoops_CIPPR = _hoops_GPGPH (_hoops_RIGC, _hoops_RIASA, _hoops_CIPPR, _hoops_CICSR, errors, &_hoops_ICGPH);
	if (_hoops_CIPPR == &_hoops_RISAH) {
		_hoops_ACGPH ((token alter *)_hoops_RIASA);
		goto _hoops_HPAGR;
	}

	/* _hoops_PIHA _hoops_HS _hoops_PIRC _hoops_RAAP */
	if (_hoops_CIPPR != null) {
		_hoops_AISAH (_hoops_RIASA, _hoops_CIPPR, errors); /* (_hoops_ASRC _hoops_PIRA _hoops_HAR _hoops_IGI) */
		_hoops_ACGPH ((token alter *)_hoops_RIASA);
		goto _hoops_HPAGR;
	}
	_hoops_ACGPH ((token alter *)_hoops_RIASA);

	if (ANYBIT (_hoops_PRGRA, _hoops_RAGRA | _hoops_AAGRA) &&
		ANYBIT (_hoops_ICGPH._hoops_PRGRA, _hoops_RHGPH | _hoops_GHGPH)) {
		/* _hoops_RSGPH _hoops_ASGPH _hoops_CPHP _hoops_AHCI _hoops_PII "_hoops_SPI=_hoops_ARGPH"*/
		HE_ERROR (HEC_COLOR, HES_PURE_COLOR_OR_TEXTURE_ONLY,
				"Gloss/Index components may only be assigned a numerical value");
		goto _hoops_HPAGR;
	}
	if (ANYBIT (_hoops_PRGRA, _hoops_ASARA | _hoops_PSARA) &&
		ANYBIT (_hoops_ICGPH._hoops_PRGRA,~(_hoops_RHGPH|_hoops_GHGPH))) {
		/* _hoops_RSGPH _hoops_ASGPH _hoops_CPHP _hoops_AHCI _hoops_PII "_hoops_SPI=_hoops_ARGPH"*/
		HE_ERROR (HEC_TEXTURE, HES_PURE_COLOR_OR_TEXTURE_ONLY,
				"Color components may only be assigned a \"pure\" color/texture");
		goto _hoops_HPAGR;
	}
	if (ANYBIT (_hoops_PRGRA, _hoops_SIARA | _hoops_GCARA) &&
		_hoops_ICGPH._hoops_PRGRA != _hoops_GHGPH) {
		HE_ERROR (HEC_TEXTURE, HES_PLAIN_TEXTURE_ONLY, 
			"Bump/Environment may not be given a plain color");
		goto _hoops_HPAGR;
	}
	if (BIT (_hoops_PRGRA, _hoops_RHGRA) && 
		!BIT (_hoops_PRGRA, M_DIFFUSE) &&
		_hoops_ICGPH._hoops_PRGRA != _hoops_GHGPH) {
		HE_ERROR (HEC_TEXTURE, HES_PLAIN_TEXTURE_ONLY, 
			"diffuse texture may not be given a plain color");
		goto _hoops_HPAGR;
	}
	if (BIT (_hoops_PRGRA, M_DIFFUSE) && 
		!BIT (_hoops_PRGRA, _hoops_RHGRA) &&
		_hoops_ICGPH._hoops_PRGRA != _hoops_RHGPH) {
		HE_ERROR (HEC_COLOR, HES_COLOR, 
			"diffuse color may only be assigned a plain color");
	}
	if (_hoops_HGA > 0 && 
		ANYBIT (_hoops_PRGRA, M_DIFFUSE|_hoops_RHGRA) && 
		!BIT (_hoops_ICGPH._hoops_PRGRA, _hoops_GHGPH)) {
		HE_ERROR (HEC_COLOR, HES_COLOR, 
			"diffuse channels >0 may not be assigned a plain color");
		/* _hoops_IH _hoops_RGR _hoops_SAGHR _hoops_RIHH, _hoops_CR _hoops_SCH _hoops_IGI _hoops_IS _hoops_SHH _hoops_RPRI, _hoops_HSGR _hoops_RH 
		   "_hoops_HHIIA _hoops_GGAS" _hoops_PPR _hoops_IIS _hoops_RH _hoops_ACSP _hoops_IIGR _hoops_RH _hoops_HAIR _hoops_PHHR _hoops_RHIR */
	}


	if (ANYBIT (_hoops_PRGRA, _hoops_ASARA)) {
		if (BIT (_hoops_PRGRA, M_DIFFUSE)) {
			if (BIT (_hoops_ICGPH._hoops_PRGRA, _hoops_RHGPH) && (_hoops_HGA == 0)) {
				_hoops_ISHIR->_hoops_CSHR = _hoops_ICGPH.color;
				_hoops_RGAIR (_hoops_ISHIR->_hoops_IRGRA);
				HI_Copy_Name (name, &_hoops_ISHIR->_hoops_IRGRA);
				_hoops_ISHIR->_hoops_PRGRA |= M_DIFFUSE;
			}
		}
		for (i=0; i<_hoops_CRGRA; i++) {		
			if (BIT (_hoops_PRGRA, HOOPS_READ_ONLY._hoops_SRGRA[i])) {
				if (BIT (_hoops_ICGPH._hoops_PRGRA, _hoops_RHGPH)) {
					_hoops_ISHIR->color[i] = _hoops_ICGPH.color;
					_hoops_RGAIR (_hoops_ISHIR->name[i]);
					HI_Copy_Name (name, &_hoops_ISHIR->name[i]);
					_hoops_ISHIR->_hoops_PRGRA |= HOOPS_READ_ONLY._hoops_SRGRA[i];
				}
			}
		}
	}

	if (ANYBIT (_hoops_PRGRA, _hoops_PSARA)) {
		if (BIT (_hoops_PRGRA, _hoops_RHGRA)) {
			if (_hoops_ICGPH.texture) {
				_hoops_HIR *_hoops_PGC, *_hoops_CSSGA;

				_hoops_PGC = HI_New_Diffuse_Channel (_hoops_ICGPH.texture);
				HI_Copy_Name (&_hoops_ICGPH.name, &_hoops_PGC->name);
				_hoops_PGC->_hoops_HGA = _hoops_HGA;
				if (_hoops_ISHIR->_hoops_SCA) {
					_hoops_CSSGA = HI_Mix_Diffuse_Channels (_hoops_ISHIR->_hoops_SCA, _hoops_PGC);
					HI_Free_Diffuse_Channel_List (_hoops_PGC);
					HI_Free_Diffuse_Channel_List (_hoops_ISHIR->_hoops_SCA);
					_hoops_ISHIR->_hoops_SCA = _hoops_CSSGA;
				}
				else
					_hoops_ISHIR->_hoops_SCA = _hoops_PGC;
			}
			_hoops_ISHIR->_hoops_PRGRA |= _hoops_RHGRA;
		}
		for (i=0; i<_hoops_GAGRA; i++) {		
			if (BIT (_hoops_PRGRA, HOOPS_READ_ONLY._hoops_APGRA[i])) {
				if (_hoops_ICGPH.texture) {
					if (_hoops_ISHIR->texture[i] != null)
						_hoops_HPRH (_hoops_ISHIR->texture[i]);
					_hoops_ISHIR->texture[i] = _hoops_ICGPH.texture;
					_hoops_PRRH(_hoops_ISHIR->texture[i]);
					_hoops_ISHIR->_hoops_PRGRA |= HOOPS_READ_ONLY._hoops_APGRA[i];
				}
				else if (i < _hoops_CRGRA && 
						 BIT (_hoops_PRGRA, HOOPS_READ_ONLY._hoops_SRGRA[i])) {
					_hoops_ISHIR->_hoops_PRGRA |= HOOPS_READ_ONLY._hoops_APGRA[i];
				}
				else
					_hoops_ISHIR->_hoops_PRGRA |= HOOPS_READ_ONLY._hoops_APGRA[i];
			}
		}
	}

	if (BIT (_hoops_PRGRA, M_TRANSMISSION)) {
		_hoops_ISHIR->_hoops_IRIR = 1.0f - ((_hoops_PACHR const &)_hoops_ICGPH.color)._hoops_HSPHR;
	}

	if (BIT (_hoops_ICGPH._hoops_PRGRA, _hoops_RAGRA)) {
		_hoops_ISHIR->gloss = _hoops_ICGPH.gloss;
		_hoops_ISHIR->_hoops_PRGRA |= _hoops_RAGRA;
	}

	if (BIT (_hoops_ICGPH._hoops_PRGRA, _hoops_AAGRA)) {
		_hoops_ISHIR->_hoops_PAGRA = _hoops_ICGPH._hoops_PAGRA;
		_hoops_ISHIR->_hoops_PRGRA |= _hoops_AAGRA;
	}
	status = true;

_hoops_HPAGR:
	if (_hoops_HCGPH.length)
		_hoops_RGAIR (_hoops_HCGPH);
	_hoops_RGAIR (_hoops_ICGPH.name);
	if (_hoops_ICGPH.texture)
		_hoops_HPRH (_hoops_ICGPH.texture);
	return status;
} /* _hoops_RSGR _hoops_API '_hoops_HGCR _hoops_IHIR _hoops_HAIR' */



local void _hoops_PSGPH(Named_Material* _hoops_HSGPH, const char *_hoops_AAPPR, void const * const _hoops_SHSCA) {
	UNREFERENCED(_hoops_AAPPR);
	UNREFERENCED(_hoops_SHSCA);

	HI_Free_Material_Names(_hoops_HSGPH, 1);
	FREE(_hoops_HSGPH, Named_Material);
}

GLOBAL_FUNCTION void HI_Flush_Color_Material_Lookup(_hoops_ISGPH **_hoops_HIHPP)
{
	if (*_hoops_HIHPP == null) 
		return;

	(*_hoops_HIHPP)->MapFunction(_hoops_PSGPH, 0);

	delete *_hoops_HIHPP;

	*_hoops_HIHPP = null;
}

GLOBAL_FUNCTION bool HI_Evaluate_Color (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HCRPR const *			_hoops_SRGPH,
	Named_Material *		_hoops_ISHIR,
	_hoops_CPAIR *			_hoops_CICSR,
	bool					errors) {
	_hoops_ARGRA		_hoops_PRGRA;
	_hoops_HCRPR					_hoops_CSGPH;
	char *					_hoops_RPPA, *_hoops_SSGPH;
	char const *			_hoops_SSRPR, *_hoops_GGRPH;
	int						_hoops_HGA;
	char 					_hoops_RGRPH = 0;
	_hoops_SRHSR				_hoops_PGHHP = _hoops_GRRCR("-");

	if (_hoops_SRGPH->length == 0) {
		if (errors)
			HE_ERROR (HEC_COLOR, HES_NULL_INPUT, "Color specification is blank");
		return false;
	}

	if (!_hoops_CICSR && _hoops_RSPPR(_hoops_RIGC, _hoops_HIHPP) != null) {
		Named_Material *	_hoops_HSGPH;
		vhash_status_t		result;

		_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);

		result = _hoops_RSPPR(_hoops_RIGC, _hoops_HIHPP)->LookupItem(_hoops_SRGPH->text, &_hoops_HSGPH);

		_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);

		if (result == VHASH_STATUS_SUCCESS) {
			HI_Copy_Named_Material (_hoops_HSGPH, _hoops_ISHIR);
			return true;
		}
	}

	_hoops_RPPA = _hoops_SRGPH->text;
	_hoops_SSRPR = _hoops_RPPA + _hoops_SRGPH->length;

	/* _hoops_IRHH _hoops_RCRR _hoops_PIRC _hoops_HISIR _hoops_GGR */
	_hoops_ISHIR->_hoops_PRGRA = _hoops_GSGPH;

	while (*_hoops_RPPA == ' ') _hoops_RPPA++;
	while (*(_hoops_SSRPR-1) == ' ') _hoops_SSRPR--;

	while (*_hoops_RPPA == '(' && *(_hoops_SSRPR-1) == ')') {
		_hoops_RPPA++;
		_hoops_SSRPR--;
	}

	_hoops_HGA = 0;
	while (_hoops_RPPA != _hoops_SSRPR) {
		bool		_hoops_AGRPH;
		int				_hoops_RGPRA;
		char			_hoops_PPARA;

		_hoops_PRGRA = _hoops_GSGPH;

		while (1) {
			_hoops_ARGRA		_hoops_PGRPH;

			while (*_hoops_RPPA == ' ') _hoops_RPPA++;

			_hoops_PGRPH = _hoops_GSGPH;

			_hoops_SSGPH = _hoops_RPPA;

			switch (*_hoops_RPPA) {
				case 'g': {
					if (_hoops_GPPSA (_hoops_RPPA, 5, "gloss")) {
						_hoops_RPPA += 5;
						while (*_hoops_RPPA == ' ') _hoops_RPPA++;
						if (*_hoops_RPPA != '=') break;
						_hoops_RPPA = _hoops_SSGPH;
						_hoops_PGRPH |= _hoops_RAGRA;
					}
				}	break; 

				case 'i': {
					if (_hoops_GPPSA (_hoops_RPPA, 5, "index")) {
						_hoops_RPPA += 5;
						while (*_hoops_RPPA == ' ') _hoops_RPPA++;
						if (*_hoops_RPPA != '=') break;
						_hoops_RPPA = _hoops_SSGPH;
						_hoops_PGRPH |= _hoops_AAGRA;
					}
				}	break;	 
		
				case 'b': {
					if (_hoops_GPPSA (_hoops_RPPA, 4, "bump")) {
						_hoops_RPPA += 4;
						while (*_hoops_RPPA == ' ') _hoops_RPPA++;
						if (*_hoops_RPPA != '=') break;
						_hoops_RPPA++;
						_hoops_PGRPH |= _hoops_SIARA;
					}
				}	break;

				case 'd': {
					if (_hoops_GPPSA (_hoops_RPPA, 15, "diffuse texture")) {
						_hoops_RPPA += 15;
						while (*_hoops_RPPA == ' ') _hoops_RPPA++;
						if (*_hoops_RPPA != '=') break;
						_hoops_RPPA++;
						_hoops_PGRPH |= _hoops_RHGRA;
					}
					else if (_hoops_GPPSA (_hoops_RPPA, 13, "diffuse color")) {
						_hoops_RPPA += 13;
						while (*_hoops_RPPA == ' ') _hoops_RPPA++;
						if (*_hoops_RPPA != '=') break;
						_hoops_RPPA++;
						_hoops_PGRPH |= M_DIFFUSE;
					}
					else if (_hoops_GPPSA (_hoops_RPPA, 7, "diffuse")) {
						_hoops_RPPA += 7;
						while (*_hoops_RPPA == ' ') _hoops_RPPA++;
						if (*_hoops_RPPA != '=') break;
						_hoops_RPPA++;
						_hoops_PGRPH |= M_DIFFUSE|_hoops_RHGRA;
						_hoops_ISHIR->_hoops_HRGRA |= M_DIFFUSE;
					}
				}	break;

				case 's': {
					if (_hoops_GPPSA (_hoops_RPPA, 8, "specular")) {
						_hoops_RPPA += 8;
						while (*_hoops_RPPA == ' ') _hoops_RPPA++;
						if (*_hoops_RPPA != '=') break;
						_hoops_RPPA++;
						_hoops_PGRPH |= M_SPECULAR|_hoops_PIARA;
						_hoops_ISHIR->_hoops_HRGRA |= M_SPECULAR;
					}
				}	break;
								
				case 't': {
					if (_hoops_GPPSA (_hoops_RPPA, 12, "transmission")) {
						_hoops_RPPA += 12;
						while (*_hoops_RPPA == ' ') _hoops_RPPA++;
						if (*_hoops_RPPA != '=') break;
						_hoops_RPPA++;
						_hoops_PGRPH |= M_TRANSMISSION|_hoops_IIARA;
						_hoops_ISHIR->_hoops_HRGRA |= M_TRANSMISSION;
					}
				}	break;

				case 'm': {
					if (_hoops_GPPSA (_hoops_RPPA, 6, "mirror")) {
						_hoops_RPPA += 6;
						while (*_hoops_RPPA == ' ') _hoops_RPPA++;
						if (*_hoops_RPPA != '=') break;
						_hoops_RPPA++;
						_hoops_PGRPH |= M_MIRROR|_hoops_HIARA;
						_hoops_ISHIR->_hoops_HRGRA |= M_MIRROR;
					}
				}	break;

				case 'e': {
					if (_hoops_GPPSA (_hoops_RPPA, 11, "environment")) {
						_hoops_RPPA += 11;
						while (*_hoops_RPPA == ' ') _hoops_RPPA++;
						if (*_hoops_RPPA != '=') break;
						_hoops_RPPA++;
						_hoops_PGRPH |= _hoops_GCARA;
					}
					else if (_hoops_GPPSA (_hoops_RPPA, 8, "emission")) {
						_hoops_RPPA += 8;
						while (*_hoops_RPPA == ' ') _hoops_RPPA++;
						if (*_hoops_RPPA != '=') break;
						_hoops_RPPA++;
						_hoops_PGRPH |= M_EMISSION|_hoops_CIARA;
						_hoops_ISHIR->_hoops_HRGRA |= M_EMISSION;
					}
				}	break;

				default: break;
			}

			if (_hoops_PGRPH != _hoops_GSGPH) {
				_hoops_PRGRA |= _hoops_PGRPH;
				if (ANYBIT (_hoops_PGRPH, _hoops_RAGRA|_hoops_AAGRA))
					break;
			}
			else {
				_hoops_RPPA = _hoops_SSGPH;
				break;
			}
		}

		if (BIT (_hoops_PRGRA, _hoops_RHGRA)) {
			HI_Free_Diffuse_Channel_List (_hoops_ISHIR->_hoops_SCA);
			_hoops_ISHIR->_hoops_SCA = null;
			_hoops_HGA = 0;
		}
		/* _hoops_GASA: _hoops_RGR _hoops_RRGR _hoops_IS _hoops_ARP _hoops_RH _hoops_SHIR _hoops_IGPC _hoops_PIHA _hoops_RCPS _hoops_RAS _hoops_RH _hoops_ARRS _hoops_AASA _hoops_IS 
		   _hoops_HGRPH.  _hoops_PS _hoops_HHGC "_hoops_RSSI=(_hoops_SPI=_hoops_PCPCP, _hoops_SPI=_hoops_IGRPH)" _hoops_IS _hoops_HS
		   _hoops_IGRPH _hoops_GCGRA _hoops_PCPCP, _hoops_HIH "_hoops_RSSI = (_hoops_PCPCP,_hoops_IGRPH)" _hoops_CGH _hoops_ASAH _hoops_IGRPH _hoops_CIAA _hoops_PCPCP _hoops_GAR _hoops_GPGR _hoops_SPI _hoops_GRIP */
		if (_hoops_PRGRA == _hoops_GSGPH) {
			_hoops_PRGRA = M_DIFFUSE|_hoops_RHGRA;
			_hoops_ISHIR->_hoops_HRGRA |= M_DIFFUSE;
		}

		while (*_hoops_RPPA == ' ') _hoops_RPPA++;

		_hoops_RGPRA = 0;
		_hoops_GGRPH = _hoops_RPPA;
		_hoops_PPARA = '\0';
		while (_hoops_GGRPH != _hoops_SSRPR) {
			if (*_hoops_GGRPH == '"' || *_hoops_GGRPH == '\'' || *_hoops_GGRPH == '`') {
				if (*_hoops_GGRPH == _hoops_PPARA || !_hoops_PPARA)
					_hoops_PPARA ^= *_hoops_GGRPH;
			}
			else if (!_hoops_PPARA) {
				if (*_hoops_GGRPH == '(')
					++_hoops_RGPRA;
				else if (*_hoops_GGRPH == ')')
					--_hoops_RGPRA;
				else if (*_hoops_GGRPH == ',' && _hoops_RGPRA <= 0)
					break;
			}

			++_hoops_GGRPH;
		}

		_hoops_AGRPH = false;
		if (*_hoops_RPPA == '(' && *(_hoops_GGRPH-1) == ')') {
			_hoops_RPPA++;
			_hoops_AGRPH = true;
		}

		while (_hoops_RPPA != _hoops_GGRPH) {
			_hoops_HCRPR		item;
			int			_hoops_CGRPH;
			int			_hoops_SGRPH;
			char		*start = null, *end = null;

			while (*_hoops_RPPA == ' ') _hoops_RPPA++;

			_hoops_SSGPH = _hoops_RPPA;

			_hoops_PPARA = '\0';
			while (_hoops_RPPA != _hoops_GGRPH) {
				if (*_hoops_RPPA == '"' || *_hoops_RPPA == '\'' || *_hoops_RPPA == '`') {
					if (*_hoops_RPPA == _hoops_PPARA || !_hoops_PPARA)
						_hoops_PPARA ^= *_hoops_RPPA;
				}
				else if (!_hoops_PPARA) {
					if (*_hoops_RPPA == '(')
						++_hoops_RGPRA;
					else if (*_hoops_RPPA == ')') {
						if (_hoops_RGPRA == 0 && _hoops_AGRPH)
							break;
						--_hoops_RGPRA;
					}
					else if (*_hoops_RPPA == ',' && _hoops_RGPRA <= 0)
						break;
				}

				++_hoops_RPPA;
			}
 
			item.length = _hoops_RPPA - _hoops_SSGPH;

			while (_hoops_SSGPH[item.length-1] == ' ' && item.length>0) item.length--;

			if (*_hoops_SSGPH == '(' && _hoops_SSGPH[item.length-1] == ')') {
				_hoops_SSGPH++;
				item.length = _hoops_RPPA-_hoops_SSGPH-1;
			}

			ALLOC_ARRAY (item.text, item.length+1, char); 

			_hoops_AIGA (_hoops_SSGPH, item.length, char, item.text);
			item.text[item.length] = 0;

			_hoops_SSGPH = item.text;
			_hoops_CGRPH = 0;
			_hoops_PPARA = '\0';
			while (*_hoops_SSGPH) {
				if (*_hoops_SSGPH == '"' || *_hoops_SSGPH == '\'' || *_hoops_SSGPH == '`') {
					if (*_hoops_SSGPH == _hoops_PPARA || !_hoops_PPARA)
						_hoops_PPARA ^= *_hoops_SSGPH;
				}
				else if (!_hoops_PPARA) {
					if ('A' <= *_hoops_SSGPH && *_hoops_SSGPH <= 'Z')
						*_hoops_SSGPH += 'a' - 'A';
					if (*_hoops_SSGPH == '(' && _hoops_SSGPH != item.text) {
						start = _hoops_SSGPH;
						_hoops_CGRPH++;
					}
					if (*_hoops_SSGPH == ')' && _hoops_CGRPH > 0) {
						end = _hoops_SSGPH + 1;	/* +1 _hoops_HIS _hoops_HAPR _hoops_GRS _hoops_IPS ')' _hoops_GACC */
						_hoops_CGRPH++;
					}
				}
				++_hoops_SSGPH;
			}

			/* _hoops_PSSPR _hoops_PSSPR _hoops_CCIH _hoops_RSAIP */
			if (_hoops_CGRPH == 2) {
				char	*new_text, *_hoops_GRRPH;

				ALLOC_ARRAY (new_text, item.length+1, char); 
				_hoops_GRRPH = new_text;

				_hoops_SSGPH = start;
				do *_hoops_GRRPH++ = *_hoops_SSGPH++;
				while (_hoops_SSGPH != end);

				if (start != item.text) {		
					if (*--start == ' ')
						*_hoops_GRRPH++ = ' ';
					else
						++start;
				}
				_hoops_SSGPH = item.text;
				while (_hoops_SSGPH != start)
					*_hoops_GRRPH++ = *_hoops_SSGPH++;
				*_hoops_GRRPH = '\0';

				FREE_ARRAY (item.text, item.length+1, char); 
				item.text = new_text;
			}

			_hoops_SSGPH = item.text;
			_hoops_SGRPH = 0;
			_hoops_PPARA = '\0';
			while (*_hoops_SSGPH) {
				if (*_hoops_SSGPH == '"' || *_hoops_SSGPH == '\'' || *_hoops_SSGPH == '`') {
					if (*_hoops_SSGPH == _hoops_PPARA || !_hoops_PPARA)
						_hoops_PPARA ^= *_hoops_SSGPH;
				}
				else if (!_hoops_PPARA && (*_hoops_SSGPH == '(' || *_hoops_SSGPH == ')')) 
					_hoops_SGRPH++;
				++_hoops_SSGPH;
			}
			if (_hoops_SGRPH > 0) {
				char	*new_text, *_hoops_GRRPH;

				ALLOC_ARRAY (new_text, item.length+1-_hoops_SGRPH, char); 
				_hoops_SSGPH = item.text;
				_hoops_GRRPH = new_text;
				_hoops_PPARA = '\0';
				while (*_hoops_SSGPH) {
					if (*_hoops_SSGPH == '"' || *_hoops_SSGPH == '\'' || *_hoops_SSGPH == '`') {
						if (*_hoops_SSGPH == _hoops_PPARA || _hoops_PPARA == '\0')
							_hoops_PPARA ^= *_hoops_SSGPH;
						*_hoops_GRRPH++ = *_hoops_SSGPH++;
					}
					else if (_hoops_PPARA || *_hoops_SSGPH != '(' && *_hoops_SSGPH != ')') 
						*_hoops_GRRPH++ = *_hoops_SSGPH++;
					else
						_hoops_SSGPH++;
				}
				*_hoops_GRRPH = '\0';
				FREE_ARRAY (item.text, item.length+1, char); 
				item.text = new_text;
				item.length -= _hoops_SGRPH;

				if (item.text[item.length-1] == ' ') {
					int		_hoops_RRRPH = item.length-1;

					while (item.text[_hoops_RRRPH-1] == ' ' && _hoops_RRRPH>0) _hoops_RRRPH--;
					
					ALLOC_ARRAY (new_text, _hoops_RRRPH+1, char); 
					_hoops_AIGA (item.text, _hoops_RRRPH, char, new_text);
					new_text[_hoops_RRRPH] = '\0';
					FREE_ARRAY (item.text, item.length+1, char);
					item.text = new_text;
					item.length = _hoops_RRRPH;
				}
			}

			if (!_hoops_PCGPH (_hoops_RIGC, &item, _hoops_CICSR, _hoops_HGA, errors, _hoops_PRGRA, _hoops_ISHIR)) {
				HI_Free_Material_Names (_hoops_ISHIR, 1);
				_hoops_RGAIR (item); 
				if (_hoops_SRGPH == &_hoops_CSGPH)
					_hoops_RGAIR (_hoops_CSGPH);
				return false;
			}

			if (BIT (_hoops_PRGRA, _hoops_RHGRA)&&
				_hoops_RAHSR (item, _hoops_PGHHP))
				_hoops_RGRPH = '-';
			_hoops_HGA++;
			_hoops_RGAIR (item); 

			if (_hoops_RPPA == _hoops_GGRPH) break;

			if (!_hoops_AGRPH)
				break; /* , _hoops_PAR _hoops_CRIPR _hoops_ARRPH */
			else
				_hoops_RPPA++;

		} /* _hoops_SPI=(_hoops_PCPCP,_hoops_IGRPH) */

		if (_hoops_RPPA++ == _hoops_SSRPR)
			break;
	} /* _hoops_SPI=_hoops_PRRRA,_hoops_HPIHP=_hoops_HRRRA */

	if (_hoops_ISHIR->_hoops_SCA) {
		_hoops_HIR *ptr = _hoops_ISHIR->_hoops_SCA;
		/* _hoops_SSS _hoops_RH _hoops_CGHI _hoops_SPI _hoops_RCAP */
		while (ptr->next != null) {
			ptr = ptr->next;
		}
		ptr->flags |= _hoops_SGGRA;
	}

	if (!_hoops_CICSR && !HOOPS_WORLD->_hoops_PRRPH ) {
		Named_Material	*_hoops_HSGPH;

		ZALLOC(_hoops_HSGPH, Named_Material);
		HI_Copy_Named_Material (_hoops_ISHIR, _hoops_HSGPH);

		_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);
		if (_hoops_RSPPR(_hoops_RIGC, _hoops_HIHPP) == null)
			_hoops_RSPPR(_hoops_RIGC, _hoops_HIHPP) = 
				POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_ISGPH)(HOOPS_WORLD->memory_pool, 128);
	
		_hoops_RSPPR(_hoops_RIGC, _hoops_HIHPP)->InsertItem(_hoops_SRGPH->text, _hoops_HSGPH);

		_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);
	}

	return true;
}

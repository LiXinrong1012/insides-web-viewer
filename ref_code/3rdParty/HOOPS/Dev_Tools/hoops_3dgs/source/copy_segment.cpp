/*
 * Copyright (c) 1998-2001 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.435 2011-01-10 23:42:57 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "adt.h"

#ifdef DISABLE_DATABASE_EDIT
#	ifdef DISABLE_PARTIAL_ERASE
#		ifdef _hoops_PASCA
#			define	_hoops_HASCA
#		endif
#	endif
#endif

#define XALLOC(p, _hoops_IASCA, type) do {				\
			type *			_hoops_CASCA;				\
			ZALLOC (_hoops_CASCA, type);				\
			p = (_hoops_IASCA *)_hoops_CASCA;					\
		} while (0)

#define _hoops_SASCA(p, type)	 XALLOC (p, Attribute,  type)
#define _hoops_GPSCA(p, type)	 XALLOC (p, Geometry,   type)
#define _hoops_RPSCA(p, type) XALLOC (p, Subsegment, type)


#define _hoops_APSCA(_hoops_PPSCA,_hoops_HPSCA,_hoops_IPSCA)							\
	if ((_hoops_PPSCA) != null && (_hoops_PPSCA)->count > 0) {					\
		int			_i_;										\
		for (_i_=0; _i_<(_hoops_PPSCA)->count; _i_++) {					\
			Key		_hoops_CPSCA = (_hoops_PPSCA)->old_keys[_i_];			\
			if (_hoops_CPSCA == (_hoops_HPSCA)->key ||					\
				_hoops_CPSCA == _hoops_AIRIR(_hoops_HPSCA))				\
				(_hoops_PPSCA)->new_keys[_i_] = _hoops_AIRIR(_hoops_IPSCA);	\
		}														\
	}

#define _hoops_SPSCA(_hoops_PPSCA,_hoops_HPSCA,_hoops_IPSCA)						\
	if ((_hoops_PPSCA) != null && (_hoops_PPSCA)->count > 0) {					\
		int			_i_;										\
		for (_i_=0; _i_<(_hoops_PPSCA)->count; _i_++) {					\
			Key		_hoops_CPSCA = (_hoops_PPSCA)->old_keys[_i_];			\
			if (_hoops_CPSCA == _hoops_HPSCA)								\
				(_hoops_PPSCA)->new_keys[_i_] = _hoops_IPSCA;					\
		}														\
	}


#ifndef _hoops_HASCA
local _hoops_PGAIR * _hoops_GHSCA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_PGAIR *				in) {
	_hoops_PGAIR *				_hoops_PAGR;

	ZALLOC (_hoops_PAGR, _hoops_PGAIR);
	_hoops_PAGR->type = _hoops_AGAIR;
	_hoops_PAGR->_hoops_HIHI = 1;
	for (int i = 0; i < _hoops_IGAIR; i++)
		if (in->data[i] != null)
			_hoops_PAGR->data[i] = HI_Copy_Geometry	 (_hoops_RIGC, (Geometry *) in->data[i]);

	return _hoops_PAGR;
}
#endif

#ifndef DISABLE_DATABASE_EDIT

local void _hoops_RHSCA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				tail) {
	_hoops_CRCP *				head = tail;
	_hoops_SIRIR *				_hoops_AHSCA;
	Attribute *				_hoops_HPHCR;

	while (BIT (head->owner->_hoops_PHSI, _hoops_PRSIR))
		head = head->owner;

	if ((_hoops_HPHCR = head->_hoops_IPPGR) != null) do {
		if (_hoops_HPHCR->type == _hoops_GRAIR)
			break;
	} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
	if (_hoops_HPHCR == null) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Streaming attribute missing");
		return;
	}
	((_hoops_RRAIR *)_hoops_HPHCR)->_hoops_PHSCA = tail;

	_hoops_AHSCA = _hoops_RIGC->open_list;
	while (_hoops_AHSCA != null) {
		if (_hoops_AHSCA->_hoops_GCRIR == _hoops_RCRIR &&
			_hoops_AHSCA->info.segment._hoops_PCRIR == head) {
			_hoops_AHSCA->info.segment._hoops_IGRPR = tail;
			_hoops_PRRH (tail);
		}
		_hoops_AHSCA = _hoops_AHSCA->next;
	}
}

local void _hoops_HHSCA(_hoops_IHSCA * _hoops_CHSCA, POINTER_SIZED_INT index, void const * const _hoops_SHSCA)
{
	_hoops_GISCA * _hoops_RISCA = (_hoops_GISCA *)_hoops_SHSCA;
	_hoops_IHSCA * _hoops_AISCA = NEW(_hoops_IHSCA)(_hoops_CHSCA->data, _hoops_CHSCA->data_length);
	_hoops_RISCA->InsertItem(index, _hoops_AISCA);
}

/* _hoops_PAGA: _hoops_CIS _hoops_HRGR _hoops_HGSAR _hoops_IH _hoops_RGSR _hoops_IPSIR _hoops_IIGR _hoops_SRS _hoops_IGCI _hoops_RIRRR (_hoops_RPP _hoops_GII) */
GLOBAL_FUNCTION Attribute * HI_Clone_Attributes (
	_hoops_AIGPR *		_hoops_RIGC,
	Attribute const *			_hoops_PISCA,
	_hoops_CRCP const *				new_owner,
	bool						_hoops_HISCA,
	void *						pt) {
	_hoops_IISCA *		_hoops_HASAR = (_hoops_IISCA *)pt;
	Attribute *					first = null;
	Attribute **				_hoops_CISCA = &first;
	Attribute *					_hoops_SISCA;

	if (_hoops_PISCA != null) do {
		switch (_hoops_PISCA->type) {
			case HK_STYLE: {
#ifndef DISABLE_STYLE_SEGMENT
				Style const *		_hoops_GCSCA = (Style const *)_hoops_PISCA;
				Style alter * &		_hoops_RCSCA = (Style alter * &)_hoops_SISCA;

				_hoops_SASCA (_hoops_SISCA, Style);

				if (_hoops_GCSCA->_hoops_IGRPR) {
					_hoops_RCSCA->_hoops_IGRPR = _hoops_GCSCA->_hoops_IGRPR;
					_hoops_PRRH (_hoops_RCSCA->_hoops_IGRPR);
					_hoops_ACSCA(_hoops_RIGC, _hoops_RCSCA, _hoops_GCSCA->_hoops_IGRPR);
				}
				else {
					HI_Copy_Name(&_hoops_GCSCA->_hoops_SGAIR, &_hoops_RCSCA->_hoops_SGAIR);
					_hoops_RCSCA->_hoops_PCSCA = _hoops_GCSCA->_hoops_PCSCA;
				}

				if (_hoops_PISCA->key > 0 && HI_Has_Local_Key (_hoops_PISCA->owner, _hoops_PISCA->key))
					HI_Set_User_Key (_hoops_RIGC, (_hoops_HPAH *)_hoops_SISCA, 0, _hoops_PISCA->key, true);
				else
					_hoops_SISCA->key = _hoops_AIRIR (_hoops_SISCA);

				HI_Copy_Conditional (&_hoops_GCSCA->condition, &_hoops_RCSCA->condition);

				_hoops_APSCA (_hoops_HASAR, _hoops_PISCA, _hoops_SISCA);
#endif
			}	break;

			case HK_DRIVER: {
				_hoops_GGAGR const *		_hoops_HCSCA = (_hoops_GGAGR const *)_hoops_PISCA;
				_hoops_GGAGR alter * &		_hoops_ICSCA = (_hoops_GGAGR alter * &)_hoops_SISCA;

				_hoops_SASCA (_hoops_SISCA, _hoops_GGAGR);
				_hoops_ICSCA->action = _hoops_ICSCA->connected_action = _hoops_HCSCA->action;

				// _hoops_ASIGA _hoops_GAAP _hoops_HIASR?
				_hoops_ICSCA->_hoops_GRPIR = null;
				_hoops_ICSCA->_hoops_RGAGR = null;
				_hoops_ICSCA->_hoops_ACARR = null;
			}	break;

			case HK_MODELLING_MATRIX: {
				_hoops_SASCA (_hoops_SISCA, _hoops_ISGI);
				HI_Copy_Matrix (&((_hoops_ISGI const *)_hoops_PISCA)->matrix, &((_hoops_ISGI alter *)_hoops_SISCA)->matrix);
			}	break;

			case HK_TEXTURE_MATRIX: {
#ifndef DISABLE_TEXTURING
				_hoops_SASCA (_hoops_SISCA, _hoops_GAAIR);
				HI_Copy_Matrix (&((_hoops_GAAIR const *)_hoops_PISCA)->matrix, &((_hoops_GAAIR alter *)_hoops_SISCA)->matrix);
#endif
			}	break;

			case _hoops_IPAIR: {
#ifndef DISABLE_TEXTURING
				_hoops_CPAIR const *		_hoops_CCSCA = (_hoops_CPAIR const *)_hoops_PISCA;
				_hoops_CPAIR alter * &		_hoops_SCSCA = (_hoops_CPAIR alter * &)_hoops_SISCA;

				_hoops_SASCA (_hoops_SISCA, _hoops_CPAIR);
				_hoops_SCSCA->count = _hoops_CCSCA->count;
				if (_hoops_SCSCA->count > 0) {
					int i;

					ALLOC_ARRAY (_hoops_SCSCA->textures, _hoops_SCSCA->count, _hoops_RCR *);
					ALLOC_ARRAY (_hoops_SCSCA->keys, _hoops_SCSCA->count, Integer32);

					_hoops_AIGA (_hoops_CCSCA->keys,
								_hoops_SCSCA->count, Integer32,
								_hoops_SCSCA->keys);

					for (i=0; i<_hoops_SCSCA->count; i++) {
						_hoops_SCSCA->textures[i] = HI_Clone_Texture (_hoops_CCSCA->textures[i]);
						_hoops_SCSCA->textures[i]->owner = (_hoops_HPAH *)new_owner;
					}
				}
				else {
					_hoops_SCSCA->textures = null;
					_hoops_SCSCA->keys = null;
				}
#endif
			}	break;

			case _hoops_RAAIR: {
				_hoops_AAAIR const *	_hoops_GSSCA = (_hoops_AAAIR const *)_hoops_PISCA;
				_hoops_AAAIR alter * &	_hoops_RSSCA = (_hoops_AAAIR alter * &)_hoops_SISCA;

				_hoops_SASCA (_hoops_SISCA, _hoops_AAAIR);

				if ((_hoops_RSSCA->count = _hoops_GSSCA->count) > 0) {
					ZALLOC_ARRAY (_hoops_RSSCA->glyphs, _hoops_RSSCA->count, _hoops_GASC);
					ALLOC_ARRAY (_hoops_RSSCA->keys, _hoops_RSSCA->count, Integer32);

					for (int i=0; i<_hoops_RSSCA->count; i++)
						_hoops_RSSCA->glyphs[i] = _hoops_GSSCA->glyphs[i];
					_hoops_AIGA (_hoops_GSSCA->keys, _hoops_RSSCA->count, Integer32, _hoops_RSSCA->keys);
				}
				else {
					_hoops_RSSCA->glyphs = null;
					_hoops_RSSCA->keys = null;
				}
			}	break;

			case _hoops_HAAIR: {
				_hoops_IAAIR const *	_hoops_ASSCA = (_hoops_IAAIR const *)_hoops_PISCA;
				_hoops_IAAIR alter * &	_hoops_PSSCA = (_hoops_IAAIR alter * &)_hoops_SISCA;

				_hoops_SASCA (_hoops_SISCA, _hoops_IAAIR);

				_hoops_PSSCA->count=_hoops_ASSCA->count;
				if (_hoops_PSSCA->count > 0) {
					ZALLOC_ARRAY (_hoops_PSSCA->_hoops_SAAIR, _hoops_PSSCA->count, _hoops_GPAIR);
					ALLOC_ARRAY (_hoops_PSSCA->keys, _hoops_PSSCA->count, Integer32);

					for (int i=0; i<_hoops_PSSCA->count; i++)
						_hoops_PSSCA->_hoops_SAAIR[i] = _hoops_ASSCA->_hoops_SAAIR[i];
					_hoops_AIGA (_hoops_ASSCA->keys, _hoops_PSSCA->count, Integer32, _hoops_PSSCA->keys);
				}
				else {
					_hoops_PSSCA->_hoops_SAAIR = null;
					_hoops_PSSCA->keys = null;
				}
			}	break;

			case _hoops_RPAIR: {
				_hoops_APAIR const *		_hoops_HSSCA = (_hoops_APAIR const *)_hoops_PISCA;
				_hoops_APAIR alter * &	_hoops_ISSCA = (_hoops_APAIR alter * &)_hoops_SISCA;

				_hoops_SASCA (_hoops_SISCA, _hoops_APAIR);

				_hoops_ISSCA->count=_hoops_HSSCA->count;
				if (_hoops_ISSCA->count > 0) {
					ZALLOC_ARRAY (_hoops_ISSCA->_hoops_HPAIR, _hoops_ISSCA->count, Line_Style);
					ALLOC_ARRAY (_hoops_ISSCA->keys, _hoops_ISSCA->count, Integer32);

					for (int i=0; i<_hoops_ISSCA->count; i++)
						_hoops_ISSCA->_hoops_HPAIR[i] = _hoops_HSSCA->_hoops_HPAIR[i];
					_hoops_AIGA (_hoops_HSSCA->keys, _hoops_ISSCA->count, Integer32, _hoops_ISSCA->keys);
				}
				else {
					_hoops_ISSCA->_hoops_HPAIR = null;
					_hoops_ISSCA->keys = null;
				}
			}	break;

			case HK_DRIVER_OPTIONS: {
				_hoops_GAPIR const *		_hoops_CSSCA = (_hoops_GAPIR const *)_hoops_PISCA;
				_hoops_GAPIR alter * &	_hoops_SSSCA = (_hoops_GAPIR alter * &)_hoops_SISCA;

				_hoops_SASCA (_hoops_SISCA, _hoops_GAPIR);
				_hoops_RSAI (_hoops_PISCA, _hoops_GAPIR, _hoops_SISCA);

				_hoops_APRGA(_hoops_CSSCA->_hoops_RPPIR, _hoops_SSSCA->_hoops_APPIR, int, _hoops_SSSCA->_hoops_RPPIR);


				HI_Copy_Name (&_hoops_CSSCA->_hoops_IAPIR, &_hoops_SSSCA->_hoops_IAPIR);
				_hoops_SSSCA->_hoops_HAPIR = HI_Copy_Name_List (_hoops_CSSCA->_hoops_HAPIR);

				_hoops_SSSCA->_hoops_SAPIR = HI_Copy_Font_Names(_hoops_CSSCA->_hoops_SAPIR);

				if (_hoops_SSSCA->_hoops_PPPIR)
					_hoops_PRRH(_hoops_SSSCA->_hoops_PPPIR);
			}	break;

			case HK_USER_OPTIONS: {
				_hoops_HPPIR const * 			_hoops_GGGSA = (_hoops_HPPIR const *)_hoops_PISCA;
				_hoops_HPPIR alter * &			_hoops_RGGSA = (_hoops_HPPIR alter * &)_hoops_SISCA;

				_hoops_SASCA (_hoops_SISCA, _hoops_HPPIR);

				if (_hoops_GGGSA->option_list)
				_hoops_RGGSA->option_list =	HI_Copy_Option_List (_hoops_GGGSA->option_list);

				if (_hoops_GGGSA->_hoops_APICA)
				_hoops_RGGSA->_hoops_APICA = HI_Copy_Option_List (_hoops_GGGSA->_hoops_APICA);

				if (_hoops_GGGSA->_hoops_AGGSA && _hoops_GGGSA->_hoops_AGGSA->Count() > 0)
					_hoops_RGGSA->_hoops_AGGSA = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_PGGSA)(_hoops_GGGSA->_hoops_AGGSA);

				if (_hoops_GGGSA->_hoops_HGGSA && _hoops_GGGSA->_hoops_HGGSA->Count() > 0) {
					_hoops_RGGSA->_hoops_HGGSA = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_GISCA)(HOOPS_WORLD->memory_pool, _hoops_GGGSA->_hoops_HGGSA->TableSize());
					_hoops_GGGSA->_hoops_HGGSA->MapFunction(_hoops_HHSCA, (void*)_hoops_RGGSA->_hoops_HGGSA);
				}

				if (_hoops_GGGSA->_hoops_IGGSA) {
					_hoops_RGGSA->_hoops_IGGSA = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_CGGSA)(_hoops_GGGSA->_hoops_IGGSA);
					_hoops_HPPIR const * _hoops_IPPIR;
					_hoops_CGGSA::UniqueCursor *	uc = _hoops_RGGSA->_hoops_IGGSA->GetUniqueCursor();
					while ((_hoops_IPPIR = uc->Peek()) != null) {
						ASSERT(_hoops_IPPIR->_hoops_IGGSA == null);
						_hoops_PRRH(_hoops_IPPIR);
						uc->Advance();
					}
					delete uc;
				}
			}	break;

			case _hoops_CPPIR: {
				_hoops_SPPIR const *		_hoops_GCACA = (_hoops_SPPIR const *)_hoops_PISCA;
				_hoops_SPPIR alter * &	_hoops_RCACA = (_hoops_SPPIR alter * &)_hoops_SISCA;

				_hoops_SASCA (_hoops_SISCA, _hoops_SPPIR);
				_hoops_RSAI(_hoops_PISCA, _hoops_SPPIR, _hoops_SISCA);
				_hoops_APRGA(_hoops_GCACA->_hoops_SGCAA, _hoops_GCACA->count, unsigned int, _hoops_RCACA->_hoops_SGCAA);
				_hoops_APRGA(_hoops_GCACA->values, _hoops_GCACA->count, unsigned int, _hoops_RCACA->values);
				for (int i=0; i<_hoops_RCACA->count; i++) {
					unsigned int	_hoops_RCHA = _hoops_RCACA->_hoops_SGCAA[i];
					int				index = i * 32;

					while (_hoops_RCHA != 0) {
						if ((_hoops_RCHA & 1) != 0) {
							_hoops_PRRH (HOOPS_WORLD->_hoops_PCIIR[index]);
						}
						_hoops_RCHA >>= 1;
						++index;
					}
				}

				_hoops_RCACA->_hoops_ACPGR = HI_Copy_Conditional_Actions(_hoops_GCACA->_hoops_ACPGR);
			}	break;

			case HK_WINDOW: {
				_hoops_SASCA (_hoops_SISCA, Window);
				_hoops_RSAI(_hoops_PISCA, Window, _hoops_SISCA);
			}	break;

			case HK_VISIBILITY: {
				_hoops_SASCA (_hoops_SISCA, _hoops_RSAIR);
				_hoops_RSAI(_hoops_PISCA, _hoops_RSAIR, _hoops_SISCA);
			}	break;

			case HK_HEURISTICS: {
				_hoops_SASCA (_hoops_SISCA, _hoops_GHAIR);
				_hoops_RSAI(_hoops_PISCA, _hoops_GHAIR, _hoops_SISCA);
			}	break;

			case HK_RENDERING_OPTIONS: {
				_hoops_RHAIR const *			_hoops_SGGSA = (_hoops_RHAIR const *)_hoops_PISCA;
				_hoops_RHAIR alter * &			_hoops_GRGSA = (_hoops_RHAIR alter * &)_hoops_SISCA;

				_hoops_SASCA (_hoops_SISCA, _hoops_RHAIR);
				_hoops_RSAI(_hoops_PISCA, _hoops_RHAIR, _hoops_SISCA);

				if (_hoops_GRGSA->_hoops_AIAIR) {
					ALLOC(_hoops_GRGSA->_hoops_AIAIR, _hoops_HIAIR);
					_hoops_RSAI(_hoops_SGGSA->_hoops_AIAIR, _hoops_HIAIR, _hoops_GRGSA->_hoops_AIAIR);
					HI_Copy_Name (&_hoops_SGGSA->_hoops_AIAIR->_hoops_PIAIR,
						&_hoops_GRGSA->_hoops_AIAIR->_hoops_PIAIR);
				}

				if (_hoops_GRGSA->_hoops_PRSI) {
					ALLOC(_hoops_GRGSA->_hoops_PRSI, _hoops_PHAIR);
					_hoops_RSAI(_hoops_SGGSA->_hoops_PRSI, _hoops_PHAIR, _hoops_GRGSA->_hoops_PRSI);
					_hoops_GRGSA->_hoops_PRSI->bounding.retain();
				}

				if (_hoops_GRGSA->locks) {
					ALLOC(_hoops_GRGSA->locks, _hoops_CCAIR);
					_hoops_RSAI(_hoops_SGGSA->locks, _hoops_CCAIR, _hoops_GRGSA->locks);
				}

				if (_hoops_GRGSA->_hoops_HHAIR) {
					ALLOC(_hoops_GRGSA->_hoops_HHAIR, _hoops_RIAIR);
					_hoops_RSAI(_hoops_SGGSA->_hoops_HHAIR, _hoops_RIAIR, _hoops_GRGSA->_hoops_HHAIR);
					HI_Copy_Name (&_hoops_SGGSA->_hoops_HHAIR->_hoops_GHSS.color.name,
						&_hoops_GRGSA->_hoops_HHAIR->_hoops_GHSS.color.name);
					HI_Copy_Name (&_hoops_SGGSA->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR,
						&_hoops_GRGSA->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR);
					_hoops_GRGSA->_hoops_HHAIR->_hoops_IHAIR._hoops_CHAIR = null;
				}

				if (_hoops_GRGSA->geometry) {
					ALLOC(_hoops_GRGSA->geometry, _hoops_SCAIR);
					_hoops_RSAI(_hoops_SGGSA->geometry, _hoops_SCAIR, _hoops_GRGSA->geometry);
				}

				if (_hoops_GRGSA->_hoops_IIAIR) {
					ALLOC (_hoops_GRGSA->_hoops_IIAIR, _hoops_ICAIR);
					_hoops_RSAI (_hoops_SGGSA->_hoops_IIAIR, _hoops_ICAIR, _hoops_GRGSA->_hoops_IIAIR);
					if (_hoops_GRGSA->_hoops_IIAIR->_hoops_CIAIR != 0) {
						_hoops_APRGA (_hoops_SGGSA->_hoops_IIAIR->_hoops_SIAIR,
							_hoops_GRGSA->_hoops_IIAIR->_hoops_CIAIR, float,
							_hoops_GRGSA->_hoops_IIAIR->_hoops_SIAIR);
					}
					if (_hoops_GRGSA->_hoops_IIAIR->_hoops_GCAIR != 0) {
						_hoops_APRGA (_hoops_SGGSA->_hoops_IIAIR->colors,
							_hoops_GRGSA->_hoops_IIAIR->_hoops_GCAIR, RGB,
							_hoops_GRGSA->_hoops_IIAIR->colors);
					}
					if (_hoops_GRGSA->_hoops_IIAIR->_hoops_RCAIR != 0) {
						ALLOC_ARRAY (_hoops_GRGSA->_hoops_IIAIR->_hoops_ACAIR,
							_hoops_GRGSA->_hoops_IIAIR->_hoops_RCAIR, _hoops_HCRPR);
						for (int i=0; i<_hoops_GRGSA->_hoops_IIAIR->_hoops_RCAIR; i++)
							HI_Copy_Name (&_hoops_SGGSA->_hoops_IIAIR->_hoops_ACAIR[i],
							&_hoops_GRGSA->_hoops_IIAIR->_hoops_ACAIR[i]);

						_hoops_APRGA (_hoops_SGGSA->_hoops_IIAIR->_hoops_PCAIR,
							_hoops_GRGSA->_hoops_IIAIR->_hoops_RCAIR, Integer32,
							_hoops_GRGSA->_hoops_IIAIR->_hoops_PCAIR);
					}
					if (_hoops_GRGSA->_hoops_IIAIR->weight_count != 0) {
						_hoops_APRGA (_hoops_SGGSA->_hoops_IIAIR->weights,
							_hoops_GRGSA->_hoops_IIAIR->weight_count, _hoops_HCAIR,
							_hoops_GRGSA->_hoops_IIAIR->weights);
					}
				}
			}	break;

			case HK_SELECTABILITY: {
				_hoops_SASCA (_hoops_SISCA, _hoops_ASAIR);
				_hoops_RSAI(_hoops_PISCA, _hoops_ASAIR, _hoops_SISCA);
			}	break;

			case HK_WINDOW_FRAME: {
				_hoops_SASCA (_hoops_SISCA, _hoops_GSAIR);
				_hoops_RSAI(_hoops_PISCA, _hoops_GSAIR, _hoops_SISCA);
			}	break;

			case HK_COLOR: {
				_hoops_SSGI const *			_hoops_RPRRA = (_hoops_SSGI const *)_hoops_PISCA;
				_hoops_SSGI alter * &			_hoops_APRRA = (_hoops_SSGI alter * &)_hoops_SISCA;
				_hoops_ACSGA *			list;

				_hoops_SASCA (_hoops_SISCA, _hoops_SSGI);

				_hoops_APRRA->_hoops_GHA = _hoops_RPRRA->_hoops_GHA;
				_hoops_APRRA->_hoops_CCCIR = Color_NONE;
				_hoops_APRRA->colors = HI_Copy_Colors (_hoops_RPRRA->colors, null);

				if (new_owner->type == _hoops_IRCP && (list = _hoops_APRRA->colors) != null) do {
					if (list->type == _hoops_GIGRA) {
						_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;

						if ((BIT (_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA, _hoops_IIARA) &&
							 _hoops_ICSGA->_hoops_ISHIR.texture[_hoops_PCA] != null ||
							 BIT (_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA, M_TRANSMISSION) &&
							 (_hoops_ICSGA->_hoops_ISHIR.color[_hoops_PCA].red   != 0.0f ||
							  _hoops_ICSGA->_hoops_ISHIR.color[_hoops_PCA].green != 0.0f ||
							  _hoops_ICSGA->_hoops_ISHIR.color[_hoops_PCA].blue  != 0.0f))) {
							HI_More_Transparencies (_hoops_RIGC, (_hoops_CRCP *)new_owner, 1);
							break;
						}
					}
				} while ((list = list->next) != null);
			}	break;

			case HK_CALLBACK: {
#ifndef DISABLE_CALLBACKS
				_hoops_SASCA (_hoops_SISCA, _hoops_GCHIR);
				((_hoops_GCHIR alter *)_hoops_SISCA)->_hoops_ACHIR = HI_Copy_Callback_List (((_hoops_GCHIR const *)_hoops_PISCA)->_hoops_ACHIR);
#endif
			}	break;

			case HK_HANDEDNESS: {
				_hoops_SASCA (_hoops_SISCA, _hoops_ARAIR);
				_hoops_RSAI(_hoops_PISCA, _hoops_ARAIR, _hoops_SISCA);
			}	break;

			case HK_LINE_WEIGHT:
			case HK_EDGE_WEIGHT:
			case HK_TEXT_SPACING:
			case HK_MARKER_SIZE: {
				_hoops_SASCA (_hoops_SISCA, _hoops_AHPIR);
				_hoops_RSAI(_hoops_PISCA, _hoops_AHPIR, _hoops_SISCA);
			}	break;

			case HK_FACE_PATTERN:
			case HK_WINDOW_PATTERN:
			case HK_TEXT_ALIGNMENT: {
				_hoops_SASCA (_hoops_SISCA, _hoops_GGPIR);
				_hoops_RSAI(_hoops_PISCA, _hoops_GGPIR, _hoops_SISCA);
			}	break;

			case HK_EDGE_PATTERN: {
				_hoops_ISAIR const *		_hoops_RRGSA = (_hoops_ISAIR const *)_hoops_PISCA;
				_hoops_ISAIR alter * &	_hoops_ARGSA = (_hoops_ISAIR alter * &)_hoops_SISCA;

				_hoops_SASCA (_hoops_SISCA, _hoops_ISAIR);
				_hoops_RSAI(_hoops_PISCA, _hoops_ISAIR, _hoops_SISCA);
				HI_Copy_Name(&_hoops_RRGSA->line_style, &_hoops_ARGSA->line_style);
			}	break;

			case HK_LINE_PATTERN: {
				_hoops_PSAIR const *		_hoops_RRGSA = (_hoops_PSAIR const *)_hoops_PISCA;
				_hoops_PSAIR alter * &	_hoops_ARGSA = (_hoops_PSAIR alter * &)_hoops_SISCA;

				_hoops_SASCA (_hoops_SISCA, _hoops_PSAIR);
				_hoops_RSAI(_hoops_PISCA, _hoops_PSAIR, _hoops_SISCA);
				HI_Copy_Name(&_hoops_RRGSA->line_style, &_hoops_ARGSA->line_style);
				HI_Copy_Name(&_hoops_RRGSA->start_glyph, &_hoops_ARGSA->start_glyph);
				HI_Copy_Name(&_hoops_RRGSA->middle_glyph, &_hoops_ARGSA->middle_glyph);
				HI_Copy_Name(&_hoops_RRGSA->end_glyph, &_hoops_ARGSA->end_glyph);
			}	break;

			case HK_MARKER_SYMBOL: {
				_hoops_SSAIR const *			_hoops_RRGSA = (_hoops_SSAIR const *)_hoops_PISCA;
				_hoops_SSAIR alter * &		_hoops_ARGSA = (_hoops_SSAIR alter * &)_hoops_SISCA;

				_hoops_SASCA (_hoops_SISCA, _hoops_SSAIR);
				_hoops_RSAI(_hoops_PISCA, _hoops_SSAIR, _hoops_SISCA);
				HI_Copy_Name(&_hoops_RRGSA->name, &_hoops_ARGSA->name);
			}	break;

			case HK_USER_VALUE: {
				_hoops_SASCA (_hoops_SISCA, _hoops_RHPIR);
				_hoops_RSAI(_hoops_PISCA, _hoops_RHPIR, _hoops_SISCA);
			}	break;

			case HK_TEXT_FONT: {
				_hoops_AGPIR	*_hoops_GSGRA, *_hoops_HIGRA;

				_hoops_SASCA (_hoops_SISCA, _hoops_AGPIR);
				_hoops_RSAI(_hoops_PISCA, _hoops_AGPIR, _hoops_SISCA);

				_hoops_GSGRA = (_hoops_AGPIR *)_hoops_SISCA;
				_hoops_HIGRA = (_hoops_AGPIR *)_hoops_PISCA;

				if (_hoops_HIGRA->_hoops_HGPIR != null) {
					_hoops_GSGRA->_hoops_HGPIR = HI_Copy_Font_Names (_hoops_HIGRA->_hoops_HGPIR);
				}
			}	break;

			case HK_COLOR_MAP: {
				_hoops_RHAH const *			_hoops_SSPRA = (_hoops_RHAH const *)_hoops_PISCA;
				_hoops_RHAH alter * &			_hoops_GGHRA = (_hoops_RHAH alter * &)_hoops_SISCA;

				int i;

				_hoops_SASCA (_hoops_SISCA, _hoops_RHAH);
				_hoops_RSAI(_hoops_PISCA, _hoops_RHAH, _hoops_SISCA);

				ALLOC_ARRAY(_hoops_GGHRA->_hoops_HAA, _hoops_GGHRA->length, Named_Material);

				for (i=0; i<_hoops_GGHRA->length; i++)
					HI_Copy_Named_Material (&_hoops_SSPRA->_hoops_HAA[i],
											&_hoops_GGHRA->_hoops_HAA[i]);

				_hoops_GGHRA->_hoops_PPRPR = null;
			}	break;

			case HK_CAMERA: {
				_hoops_SASCA (_hoops_SISCA, _hoops_HHRA);
				_hoops_RSAI(_hoops_PISCA, _hoops_HHRA, _hoops_SISCA);

				_hoops_HHRA const *	_hoops_PRGSA = (_hoops_HHRA const *)_hoops_PISCA;
				_hoops_HHRA alter *	_hoops_HRGSA = (_hoops_HHRA alter *)_hoops_SISCA;

				_hoops_HRGSA->_hoops_PRPA._hoops_APRA.retain();
				_hoops_HRGSA->_hoops_AIIH._hoops_APRA.retain();
				_hoops_HRGSA->_hoops_GRCC._hoops_APRA.retain();

				if (_hoops_PRGSA->_hoops_SIPCR != &HOOPS_WORLD->_hoops_GCPCR)
					_hoops_HRGSA->_hoops_SIPCR = &_hoops_HRGSA->_hoops_CIPCR;
			}	break;

			case HK_CLIP_REGION: {
				_hoops_IRAIR const *			_hoops_IRGSA = (_hoops_IRAIR const *)_hoops_PISCA;
				_hoops_IRAIR alter * &		_hoops_CRGSA = (_hoops_IRAIR alter * &)_hoops_SISCA;

				_hoops_SASCA (_hoops_SISCA, _hoops_IRAIR);
				_hoops_RSAI(_hoops_PISCA, _hoops_IRAIR, _hoops_SISCA);
				_hoops_APRGA(_hoops_IRGSA->points, _hoops_IRGSA->count, Point, _hoops_CRGSA->points);
			}	break;

			case HK_TEXT_PATH: {
				_hoops_SASCA (_hoops_SISCA, _hoops_RGPIR);
				_hoops_RSAI(_hoops_PISCA, _hoops_RGPIR, _hoops_SISCA);
			}	break;

			case _hoops_GRAIR: {
				_hoops_SASCA (_hoops_SISCA, _hoops_RRAIR);
				_hoops_RSAI(_hoops_PISCA, _hoops_RRAIR, _hoops_SISCA);
			}	break;

			default: {
				_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, Sprintf_D (null,
					"Unexpected segment attributes (#%d)", _hoops_PISCA->type));
				*_hoops_CISCA = null;
				return first;
			}		/*_hoops_IHSA;*/
		}

		_hoops_SISCA->_hoops_HIHI = 1;
		_hoops_SISCA->type = _hoops_PISCA->type;
		_hoops_SISCA->_hoops_RRHH = _hoops_PISCA->_hoops_RRHH;
		_hoops_SISCA->owner = (_hoops_CRCP *)new_owner;
		_hoops_SISCA->_hoops_CPGPR = _hoops_HCHPA;
		_hoops_SISCA->_hoops_SPGPR = false;
		_hoops_SISCA->next = null;
		*_hoops_CISCA = _hoops_SISCA;
		_hoops_SISCA->backlink = _hoops_CISCA;
		_hoops_CISCA = &_hoops_SISCA->next;

		switch (_hoops_SISCA->type) {
			case HK_DRIVER: {
				HI_Init_Driver (_hoops_RIGC, (_hoops_GGAGR *)_hoops_SISCA, false);

				/* _hoops_IRHH _hoops_RCRR _hoops_RHPP _hoops_SAGGR _hoops_AIS _hoops_PRGI _hoops_RPP _hoops_PSP _hoops_SRGSA */
				_hoops_SASIR (_hoops_RIGC, new_owner, _hoops_GAGSA);
			}	break;
		}
	} while (_hoops_HISCA && (_hoops_PISCA = _hoops_PISCA->next) != null);

	*_hoops_CISCA = null;

	return first;
}

local void _hoops_RAGSA (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_CRCP alter *				_hoops_SRCP,
	Geometry const *			geom,
	int							_hoops_RGPGR = ~0) {

	switch (geom->type) {
		case _hoops_ICIP: {
			if (BIT (_hoops_RGPGR, _hoops_AGPGR (_hoops_ICIP)))
				HI_More_Light (_hoops_RIGC, _hoops_SRCP, 1);
		}	break;

		case _hoops_HGPGR: {
			if (BIT (_hoops_RGPGR, _hoops_AGPGR (_hoops_HGPGR)))
				HI_More_Cutting_Planes (_hoops_RIGC, _hoops_SRCP, 1);
		}	break;

		case _hoops_AHIP: {
			_hoops_PHIP const *		_hoops_RRA = (_hoops_PHIP const *)geom;

			if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
				_hoops_CRCP const *		_hoops_HGRPR = (_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0];

				HI_More_Light (_hoops_RIGC, _hoops_SRCP, _hoops_HGRPR->_hoops_AAGSA());
				HI_More_Cutting_Planes (_hoops_RIGC, _hoops_SRCP, _hoops_HGRPR->_hoops_PAGSA());
			}
			else {
				for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++) {
					_hoops_RAGSA (_hoops_RIGC, _hoops_SRCP, (Geometry const *)_hoops_RRA->_hoops_IHIP[i], _hoops_RRA->_hoops_RGPGR);
				}
			}
		}	break;
	}
}


local void _hoops_HAGSA (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_CRCP *					_hoops_IAGSA, // _hoops_HISRA
	_hoops_CRCP *					_hoops_CAGSA,
	_hoops_CRCP *					_hoops_SAGSA,
	_hoops_IISCA *		_hoops_HASAR) {

  top:;

	_hoops_SAGSA->bounding = _hoops_CAGSA->bounding;
	_hoops_SAGSA->_hoops_HSRIR = _hoops_CAGSA->_hoops_HSRIR;

	if ((_hoops_SAGSA->_hoops_IPPGR = HI_Clone_Attributes (_hoops_RIGC, _hoops_CAGSA->_hoops_IPPGR, _hoops_SAGSA, true, _hoops_HASAR)) != null) {
		Attribute *				_hoops_HPHCR = _hoops_SAGSA->_hoops_IPPGR;

		_hoops_HPHCR->backlink = &_hoops_SAGSA->_hoops_IPPGR;

		do HI_Redraw_Attribute (_hoops_RIGC, _hoops_SAGSA, _hoops_HPHCR->type, null, _hoops_HPHCR);
		while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
	}

	if (BIT (_hoops_SAGSA->_hoops_PHSI, _hoops_PRSIR) && _hoops_CAGSA->_hoops_RGRPR == null)
		_hoops_RHSCA (_hoops_RIGC, _hoops_SAGSA);

#if 1
		/*_hoops_RH _hoops_PPRRR _hoops_RGR _hoops_CAGH _hoops_HRGR _hoops_IHGS _hoops_SPIP _hoops_CPSA _hoops_CGH*/
		/*_hoops_SHH _hoops_HGAS _hoops_HIS _hoops_IRS _hoops_PPCAR _hoops_PPII _hoops_HRGR _hoops_IGI _hoops_IH _hoops_CCAH*/
		/*_hoops_PPR _hoops_IPS _hoops_SGHC _hoops_HIH _hoops_RGR _hoops_GPGSA _hoops_HRGR _hoops_RPGSA _hoops_IRS _hoops_RSCA*/
		/*_hoops_SPAC _hoops_GAAP _hoops_HIH _hoops_IRS _hoops_SHSC _hoops_AHCPR _hoops_APGSA*/
		_hoops_SAGSA->_hoops_GACP = null;
		_hoops_SAGSA->geometry = null;
#endif

	if (_hoops_CAGSA->geometry == null) _hoops_SAGSA->geometry = null;
	else {
#if 1
		Geometry *				_hoops_PPGSA = _hoops_CAGSA->geometry;

		do {
			Geometry *			_hoops_HPGSA = HI_Copy_Geometry (_hoops_RIGC, _hoops_PPGSA);

			if (BIT (_hoops_PPGSA->_hoops_RRHH, _hoops_CHRIR)) {
				int				count;
				int const *		_hoops_IPGSA;
				int const *		_hoops_CPGSA;

				if (_hoops_PPGSA->type == _hoops_HIIP) {
					_hoops_SHRIR const *	_hoops_GIRIR = (_hoops_SHRIR const *)_hoops_PPGSA;
					count = -_hoops_GIRIR->count / 2;
					_hoops_IPGSA = _hoops_GIRIR->mapping;
					_hoops_CPGSA = ((_hoops_SHRIR const *)_hoops_HPGSA)->mapping;
				}
				else {
					_hoops_GRPGR const *	_hoops_CPAI = (_hoops_GRPGR const *)_hoops_PPGSA;
					count = _hoops_CPAI->count;
					_hoops_IPGSA = _hoops_CPAI->mapping;
					_hoops_CPGSA = ((_hoops_GRPGR const *)_hoops_HPGSA)->mapping;
				}

				for (int i=0; i<count; ++i) {
					_hoops_SPSCA (_hoops_HASAR, HOOPS_WORLD->_hoops_GCHCA.table[_hoops_IPGSA[i] & ~_hoops_RIRIR].key,
												HOOPS_WORLD->_hoops_GCHCA.table[_hoops_CPGSA[i] & ~_hoops_RIRIR].key);
				}
			}
			else
				_hoops_APSCA (_hoops_HASAR, _hoops_PPGSA, _hoops_HPGSA);

			_hoops_RAGSA (_hoops_RIGC, _hoops_SAGSA, _hoops_HPGSA);

			switch (_hoops_HPGSA->type) {
				case _hoops_HGCP: {
					Image *_hoops_SPGSA = (Image *)_hoops_PPGSA;
					if (BIT (_hoops_SPGSA->flags, _hoops_SHCC))
						HOOPS_WORLD->_hoops_ACPIR++;
					if (_hoops_SPGSA->texture != null) {
						Image *		_hoops_GHGSA = (Image *)_hoops_HPGSA;
						_hoops_RCR *	texture;

						if ((texture = HI_Look_Up_Texture (_hoops_RIGC, _hoops_SAGSA, &_hoops_GHGSA->name)) != null) {
							_hoops_GHGSA->texture = texture;
							_hoops_PRRH (texture);
						}
					}
				}	break;
			}

			_hoops_HPGSA->owner = _hoops_SAGSA;

			if (BIT (_hoops_HPGSA->_hoops_RRHH, _hoops_PASIR))
				HI_Table_Insert_OO_Geometry(_hoops_SAGSA, _hoops_HPGSA);
			else
				HI_Table_Insert_Geometry(_hoops_SAGSA, _hoops_HPGSA);

			if (_hoops_PPGSA->key > 0 &&
				HI_Has_Local_Key (_hoops_PPGSA->owner, _hoops_PPGSA->key))
					HI_Set_User_Key (_hoops_RIGC, (_hoops_HPAH *)_hoops_HPGSA, 0, _hoops_PPGSA->key, true);
		} while ((_hoops_PPGSA = _hoops_PPGSA->next) != null);
#else
		Geometry		*_hoops_PPGSA = _hoops_CAGSA->geometry;
		Geometry		**_hoops_CISCA = &_hoops_SAGSA->geometry;
		Geometry		*_hoops_HPGSA;

		do {
			_hoops_HPGSA = HI_Copy_Geometry (_hoops_RIGC, _hoops_PPGSA);

			switch (_hoops_HPGSA->type) {
				case _hoops_ICIP: {
					HI_More_Light (_hoops_RIGC,_hoops_SAGSA, 1);
					break;
				}

				case _hoops_HGPGR: {
					HI_More_Cutting_Planes (_hoops_RIGC,_hoops_SAGSA, 1);
					break;
				}

				default:		break;
			}

			_hoops_HPGSA->owner = _hoops_SAGSA;
			*_hoops_CISCA = _hoops_HPGSA;
			_hoops_HPGSA->backlink = _hoops_CISCA;
			_hoops_CISCA = &_hoops_HPGSA->next;

			if (_hoops_PPGSA->key > 0 && HI_Has_Local_Key (_hoops_PPGSA->owner, _hoops_PPGSA->key))
				HI_Set_User_Key (_hoops_RIGC, (_hoops_HPAH *)_hoops_HPGSA, 0, _hoops_PPGSA->key, true);
		} while ((_hoops_PPGSA = _hoops_PPGSA->next) != null);
		*_hoops_CISCA = null;
#endif
	}

	if (_hoops_CAGSA->_hoops_RGRPR == null) _hoops_SAGSA->_hoops_RGRPR = null;
	else {
		Subsegment *		_hoops_RHGSA = _hoops_CAGSA->_hoops_RGRPR;
		Subsegment **		_hoops_CISCA = &_hoops_SAGSA->_hoops_RGRPR;
		Subsegment *		_hoops_AHGSA;

		do {
			switch (_hoops_RHGSA->type) {
				case _hoops_IRCP: {
					_hoops_CRCP const *			_hoops_PHGSA = (_hoops_CRCP const *)_hoops_RHGSA;
					_hoops_CRCP alter * &		_hoops_HHGSA = (_hoops_CRCP alter * &)_hoops_AHGSA;

					ASSERT(_hoops_RHGSA != _hoops_IAGSA);
					if (_hoops_RHGSA == _hoops_IAGSA)
						continue;

					_hoops_RPSCA (_hoops_AHGSA, _hoops_CRCP);
					_hoops_HHGSA->_hoops_PHSI = _hoops_PHGSA->_hoops_PHSI & ~_hoops_SHSIR;
					_hoops_HHGSA->_hoops_RCGC = _hoops_PHGSA->_hoops_RCGC;
					HI_Copy_Name (&_hoops_PHGSA->name, &_hoops_HHGSA->name);
					if (_hoops_PHGSA->_hoops_SSRIR() != null) {
						_hoops_PGAIR *		_hoops_HGAIR = _hoops_GHSCA (_hoops_RIGC, _hoops_PHGSA->_hoops_SSRIR());

						_hoops_HHGSA->_hoops_GGAIR (_hoops_HGAIR);
						_hoops_HGAIR->owner = (_hoops_HPAH *)_hoops_AHGSA;
					}
				}	break;

				case _hoops_AGRPR: {
					_hoops_PGRPR const *			_hoops_IHGSA = (_hoops_PGRPR const *)_hoops_RHGSA;
					_hoops_PGRPR alter * &		_hoops_CHGSA = (_hoops_PGRPR alter * &)_hoops_AHGSA;

					_hoops_CRCP *				ref;

					_hoops_RPSCA (_hoops_AHGSA, _hoops_PGRPR);

					_hoops_CHGSA->priority = _hoops_IHGSA->priority;

					ref = (_hoops_CRCP alter *)_hoops_IHGSA->_hoops_IGRPR;

					_hoops_CHGSA->_hoops_IGRPR = ref;
					_hoops_PRRH (ref);
					_hoops_SPAPA(_hoops_RIGC, _hoops_CHGSA, ref);

					HI_Copy_Conditional (&_hoops_IHGSA->condition, &_hoops_CHGSA->condition);

					if (!BIT (ref->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR)) {
						if (ref->_hoops_AAGSA() > 0)
							HI_More_Light (_hoops_RIGC, _hoops_SAGSA, ref->_hoops_AAGSA());

						if (ref->_hoops_PAGSA() > 0)
							HI_More_Cutting_Planes (_hoops_RIGC, _hoops_SAGSA, ref->_hoops_PAGSA());

						if (ref->_hoops_SHGSA() > 0)
							HI_More_Shadows (_hoops_RIGC, _hoops_SAGSA, ref->_hoops_SHGSA());

						if (!BIT (ref->_hoops_PHSI, _hoops_GIGSA|_hoops_RIGSA))
							if (ref->_hoops_IGCCA > 0)
								HI_More_Transparencies (_hoops_RIGC, _hoops_SAGSA, ref->_hoops_IGCCA);
					}
				}	break;

				default: {
					_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, Sprintf_D (null,
						"Unexpected subsegment data types (#%d)", _hoops_RHGSA->type));
					return;
				}		/* _hoops_IHSA; */
			}

			_hoops_AHGSA->_hoops_HIHI = 1;
			_hoops_AHGSA->type = _hoops_RHGSA->type;
			_hoops_AHGSA->_hoops_RRHH = _hoops_RHGSA->_hoops_RRHH;
			_hoops_AHGSA->owner = _hoops_SAGSA;
			_hoops_AHGSA->key = _hoops_AIRIR (_hoops_AHGSA);
			_hoops_AHGSA->_hoops_CPGPR = _hoops_HCHPA;
			_hoops_AHGSA->priority = _hoops_RHGSA->priority;

			*_hoops_CISCA = _hoops_AHGSA;
			_hoops_AHGSA->backlink = _hoops_CISCA;
			_hoops_CISCA = &_hoops_AHGSA->next;

			_hoops_APSCA (_hoops_HASAR, _hoops_RHGSA, _hoops_AHGSA);

			if (_hoops_RHGSA->key > 0 && HI_Has_Local_Key (_hoops_RHGSA->owner, _hoops_RHGSA->key))
				HI_Set_User_Key (_hoops_RIGC, (_hoops_HPAH *)_hoops_AHGSA, 0, _hoops_RHGSA->key, true);

			switch (_hoops_AHGSA->type) {
				case _hoops_IRCP: {
					if (_hoops_RHGSA->next == null) {	/* _hoops_SRCH _hoops_PAGIR! */
						_hoops_CAGSA = (_hoops_CRCP *)_hoops_RHGSA;
						_hoops_SAGSA = (_hoops_CRCP *)_hoops_AHGSA;
						goto top;
					}
					else {
						_hoops_HAGSA (_hoops_RIGC, _hoops_IAGSA, (_hoops_CRCP *)_hoops_RHGSA, (_hoops_CRCP *)_hoops_AHGSA, _hoops_HASAR);
					}
				}	break;

				case _hoops_AGRPR: {
				}	break;
			}
		} while ((_hoops_RHGSA = _hoops_RHGSA->next) != null);
		*_hoops_CISCA = null;
	}
}


GLOBAL_FUNCTION Key HI_Copy_Segment (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_CRCP *					_hoops_CAGSA,
	_hoops_CRCP *					newowner,
	Subsegment **				_hoops_ASRGR,
	Subsegment *				_hoops_AIGSA,
	_hoops_HCRPR *						newname,
	bool						_hoops_PIGSA,
	void *						info)
{
	_hoops_IISCA *		_hoops_HASAR = (_hoops_IISCA *)info;
	_hoops_CRCP *					_hoops_SAGSA;

	/* _hoops_IHGP _hoops_RIHH _hoops_HCGC _hoops_SRS */

	if (BIT (newowner->_hoops_PHSI, _hoops_PRSIR)) {
		HI_Not_When_Streamed (newowner, "copy a segment under it");
		return _hoops_SHSSR;
	}

	if (newname == null && _hoops_CAGSA->owner == newowner)
		return _hoops_CAGSA->key;	/* _hoops_PSHR _hoops_SPR! */

	if (_hoops_PIGSA) {
		_hoops_SAGSA = (_hoops_CRCP *)*_hoops_ASRGR;
		if (_hoops_SAGSA->_hoops_IPPGR != null ||
			_hoops_SAGSA->geometry != null ||
			_hoops_SAGSA->_hoops_RGRPR != null) {
			HE_ERROR2 (HEC_SEGMENT, HES_OUTPUT_SEGMENT_EXISTS,
					Sprintf_PP (null, "Can't copy '%p' to '%p' -", _hoops_CAGSA, _hoops_SAGSA),
					   "Output segment exists and already has things in it");
			return _hoops_SHSSR;
		}
	}
	else {
		/* _hoops_ISPR _hoops_IH _hoops_IRGH _hoops_IPSP-_hoops_SIC _hoops_HIGSA */
		bool			renumber = true;

		if (_hoops_HASAR != null)
			renumber = !_hoops_HASAR->_hoops_IIGSA;

		if (renumber && _hoops_CAGSA->key > 0 &&
			HI_Has_Local_Key (_hoops_CAGSA->owner, _hoops_CAGSA->key) &&
			HI_Has_Local_Key (newowner, _hoops_CAGSA->key)) {
			HE_ERROR2 (HEC_SEGMENT, HES_NUMBER_ALREADY_IN_USE,
					Sprintf_PP (null, "Can't copy '%p' into '%p' -",_hoops_CAGSA, newowner),
					   "The locally renumbered keys would overlap");
			return _hoops_SHSSR;
		}

		_hoops_SAGSA = HI_Create_One_Segment (_hoops_RIGC,(newname == null) ? &_hoops_CAGSA->name : newname,_hoops_ASRGR, _hoops_AIGSA, newowner, false);

		if (renumber && _hoops_CAGSA->key > 0 && HI_Has_Local_Key (_hoops_CAGSA->owner, _hoops_CAGSA->key))
			HI_Set_User_Key (_hoops_RIGC, (_hoops_HPAH *)_hoops_SAGSA, 0, _hoops_CAGSA->key, true);
	}

	_hoops_APSCA (_hoops_HASAR, _hoops_CAGSA, _hoops_SAGSA);

	_hoops_HAGSA (_hoops_RIGC, _hoops_SAGSA, _hoops_CAGSA, _hoops_SAGSA, _hoops_HASAR);

	_hoops_SAGSA->_hoops_PHSI = _hoops_CAGSA->_hoops_PHSI;

	/* _hoops_RPP _hoops_SR _hoops_IIAC _hoops_RRI _hoops_IAIA _hoops_IIGR _hoops_CGSI, _hoops_CRGS _hoops_RH _hoops_PHPA _hoops_CIGSA */
	if (!ALLBITS (_hoops_SAGSA->_hoops_RCGC, _hoops_CAGSA->_hoops_RCGC))
		HI_Propagate_Maybes (_hoops_RIGC, _hoops_SAGSA, _hoops_CAGSA->_hoops_RCGC & ~_hoops_SAGSA->_hoops_RCGC);

	if (_hoops_SAGSA->bounding != null)
		HI_Propagate_Bounding (_hoops_RIGC, newowner, _hoops_SAGSA->bounding, _hoops_SAGSA);

	/* _hoops_RPP _hoops_SR _hoops_HS _hoops_IRS _hoops_RPPS _hoops_HA, _hoops_CIHPA _hoops_IHHH _hoops_CPCHR & _hoops_CRGS _hoops_RH _hoops_PHPA _hoops_CIGSA */
	if (BIT (_hoops_SAGSA->_hoops_PHSI, _hoops_SHSIR)) {
		if (!BIT (newowner->_hoops_RCGC, T_WINDOWS))
			HI_Propagate_Maybes (_hoops_RIGC, newowner, T_WINDOWS);

		HI_Bring_To_Front (_hoops_RIGC, (_hoops_HPAH *)_hoops_SAGSA);
	}

	/* _hoops_IRHH _hoops_RCRR _hoops_SR'_hoops_ASAR _hoops_SIGSA */
	if (BIT (_hoops_SAGSA->_hoops_RCGC, T_FACES))
		_hoops_SASIR (_hoops_RIGC, _hoops_SAGSA, _hoops_GCGSA|
									_hoops_CSCCA|
									_hoops_PISSR|
									_hoops_RPSIR);
	else
		_hoops_SASIR (_hoops_RIGC, _hoops_SAGSA, _hoops_RCGSA|
									_hoops_PISSR|
									_hoops_RPSIR);

	/* _hoops_IRHH _hoops_RCRR _hoops_IAHA _hoops_PRCHR _hoops_IS _hoops_IHHH _hoops_CHR _hoops_ASAR-_hoops_CPHR */
#ifndef DISABLE_STYLE_SEGMENT
	Xref *		_hoops_AHICA;

	if ((_hoops_AHICA = _hoops_SAGSA->_hoops_SGRPR()) != null) do {
		if (_hoops_AHICA->type == HK_STYLE)
			HI_Redraw_Style (_hoops_RIGC, (Style *)_hoops_AHICA);
	} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);
#endif

	return _hoops_SAGSA->key;
}



local _hoops_SRHSR	_hoops_ACGSA = _hoops_PCGSA;

local void _hoops_HCGSA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	void *					info)
{
	Key						_hoops_ACHPA;

	_hoops_CRCP *	newowner = _hoops_RIGC->open_list->info.segment._hoops_PCRIR;

	if (newowner->_hoops_RGRPR == null ||
		newowner->_hoops_RGRPR->type == _hoops_IRCP ||
		BIT (newowner->_hoops_RGRPR->_hoops_RRHH, _hoops_PASIR)) {
		/* _hoops_PPSI _hoops_SCH _hoops_GPP _hoops_RH _hoops_RIPS */
		_hoops_ACHPA = HI_Copy_Segment (_hoops_RIGC, _hoops_SRCP, newowner, &newowner->_hoops_RGRPR,
								  null, (_hoops_HCRPR *)&_hoops_ACGSA, false, info);
	}
	else {
		Subsegment *		_hoops_AIGSA = newowner->_hoops_RGRPR;
		Subsegment *		_hoops_GIPIA = _hoops_AIGSA->next;

		while (_hoops_GIPIA != null) {
			if (_hoops_GIPIA->type == _hoops_IRCP) break;
			if (BIT (_hoops_GIPIA->_hoops_RRHH, _hoops_PASIR)) break;
			_hoops_AIGSA = _hoops_GIPIA;
			_hoops_GIPIA = _hoops_GIPIA->next;
		}

		_hoops_ACHPA = HI_Copy_Segment (_hoops_RIGC, _hoops_SRCP, newowner, &_hoops_AIGSA->next,
								  _hoops_AIGSA, (_hoops_HCRPR *)&_hoops_ACGSA, false, info);
	}

	/* _hoops_ASRC _hoops_SIC _hoops_RPP _hoops_SPR, 0 _hoops_RPP _hoops_PIRC, _hoops_ICGSA _hoops_RPP _hoops_AHPH */
	if (_hoops_ACHPA != 0) {
		_hoops_IISCA *		_hoops_HASAR = (_hoops_IISCA *)info;

		if (_hoops_HASAR->key == 0)
			_hoops_HASAR->key = _hoops_ACHPA;
		else
			_hoops_HASAR->key = _hoops_SHSSR;
	}
}


local Key _hoops_CCGSA (
	_hoops_AIGPR *		_hoops_RIGC,
	char const *				oldname,
	char const *				newname,
	_hoops_IISCA *		_hoops_HASAR) {
	_hoops_IISCA		_hoops_SCGSA;

	if (_hoops_HASAR == null) {
		ZERO_STRUCT (&_hoops_SCGSA, _hoops_IISCA);
		_hoops_HASAR = &_hoops_SCGSA;
	}
	else
		SET_MEMORY (_hoops_HASAR->new_keys, _hoops_HASAR->count*sizeof(Key), ~0);

	if (*newname == '\0') {
		/* _hoops_SGCH _hoops_IH _hoops_PCCP _hoops_IGS _hoops_CAGH, _hoops_HIH _hoops_SRCH _hoops_GSGSA _hoops_HIS _hoops_SR _hoops_PAH
		 * _hoops_RCRP _hoops_IRS _hoops_RRI _hoops_CICAR _hoops_RIHH _hoops_GPSRR _hoops_IIGR _hoops_ISCP _hoops_HAII.
		 */
		if (_hoops_RIGC->open_list == null || _hoops_RIGC->open_list->_hoops_GCRIR != _hoops_RCRIR) {
			HE_ERROR2 (HEC_SEGMENT, HES_NO_OPEN_SEGMENT,
					   "Can't copy to a new unnamed segment within the open segment -", "No segment is open.");
			return _hoops_SHSSR;
		}

		if (BIT (_hoops_RIGC->open_list->info.segment._hoops_PCRIR->_hoops_PHSI, _hoops_PRSIR)) {
			HI_Not_When_Streamed (_hoops_RIGC->open_list->info.segment._hoops_PCRIR, "create sub-segment");
			return _hoops_SHSSR;
		}

		HI_For_Each (_hoops_RIGC, oldname, true, _hoops_HCGSA, (void *)_hoops_HASAR);
		return _hoops_HASAR->key;
	}
	else {
		return HI_Output_Parse (_hoops_RIGC, oldname, newname, HI_Copy_Segment, (void *)_hoops_HASAR);
	}
}

#endif

#ifndef _hoops_HASCA

local void _hoops_RSGSA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_PIGPR *			_hoops_ASGSA,
	_hoops_PIGPR **		_hoops_CISCA,
	Geometry *				owner) {
	_hoops_PIGPR *			_hoops_PSGSA;
	_hoops_CRCP *				_hoops_SRCP = owner->owner;

	do if (!BIT (_hoops_ASGSA->_hoops_RRHH, _hoops_HGAGR)) {
		ALLOC (_hoops_PSGSA, _hoops_PIGPR);
		_hoops_PSGSA->row = _hoops_ASGSA->row;
		_hoops_PSGSA->column = _hoops_ASGSA->column;
		_hoops_PSGSA->_hoops_HIHI = 1;
		_hoops_PSGSA->type = _hoops_ASGSA->type;
		_hoops_PSGSA->_hoops_RRHH = _hoops_ASGSA->_hoops_RRHH;
		_hoops_PSGSA->owner = (_hoops_CRCP *)owner;
		_hoops_PSGSA->key = _hoops_AIRIR (_hoops_PSGSA);
		_hoops_PSGSA->_hoops_CPGPR = _hoops_HCHPA;
		_hoops_PSGSA->_hoops_SPGPR = false;
		_hoops_PSGSA->next = null;
		_hoops_PSGSA->_hoops_IPPGR = null;
		*_hoops_CISCA = (_hoops_PIGPR *)_hoops_PSGSA;
		_hoops_PSGSA->backlink = (Geometry **)_hoops_CISCA;
		_hoops_CISCA = (_hoops_PIGPR **)&_hoops_PSGSA->next;

		if (_hoops_ASGSA->key > 0 && HI_Has_Local_Key (_hoops_SRCP, _hoops_ASGSA->key))
			HI_Set_User_Key (_hoops_RIGC, (_hoops_HPAH *)_hoops_PSGSA, 0, _hoops_ASGSA->key, true);
	} while ((_hoops_ASGSA = (_hoops_PIGPR *)_hoops_ASGSA->next) != null);
}


local Polymarker * _hoops_HSGSA (
	Polymarker *		in,
	Geometry *			new_owner) {
	Polymarker *		_hoops_PAGR;
	Polymarker *		_hoops_ISGSA = null;

	do {
		ZALLOC (_hoops_PAGR, Polymarker);
		_hoops_PAGR->_hoops_GSCP = new_owner;
		_hoops_PAGR->bounding = in->bounding;
		_hoops_PAGR->next = _hoops_ISGSA;
		_hoops_ISGSA = _hoops_PAGR;
		_hoops_RSAI (&in->_hoops_SACI, _hoops_PSGHR, &_hoops_PAGR->_hoops_SACI);
		_hoops_PAGR->length = in->length;
		if (in->_hoops_IPII > 0 && in->length > 0) {
			int len;

			if (in->_hoops_IPII > in->length)
				len = in->length;
			else
				len = in->_hoops_IPII;
			_hoops_APRGA(in->_hoops_AIHA, len, int, _hoops_PAGR->_hoops_AIHA);
			_hoops_PAGR->_hoops_IPII = len;
			_hoops_PAGR->_hoops_RAHH |= _hoops_AAHH;
		}
		_hoops_ICAI (_hoops_PAGR);
	} while ((in = in->next) != null);

	return _hoops_PAGR;
}


local Polyedge * _hoops_CSGSA (
	Polyedge *			in) {
	Polyedge *			_hoops_PAGR;
	Polyedge *			_hoops_ISGSA = null;

	do {
		ZALLOC (_hoops_PAGR, Polyedge);
		_hoops_PAGR->next = _hoops_ISGSA;
		_hoops_ISGSA = _hoops_PAGR;

		_hoops_RSAI (&in->_hoops_PPGI, _hoops_IAHPR, &_hoops_PAGR->_hoops_PPGI);

		_hoops_APRGA(in->lengths, in->_hoops_PHHA, int, _hoops_PAGR->lengths);
		_hoops_PAGR->lengths_allocated = in->_hoops_PHHA;
		_hoops_APRGA(in->_hoops_AIHA, in->total, int, _hoops_PAGR->_hoops_AIHA);
		_hoops_APRGA(in->_hoops_SPII, in->total, int, _hoops_PAGR->_hoops_SPII);
		_hoops_PAGR->_hoops_IPII = _hoops_PAGR->_hoops_CPII = in->total;

		_hoops_PAGR->_hoops_RAHH |= _hoops_AAHH;

		_hoops_PAGR->total = in->total;
		_hoops_PAGR->_hoops_PHHA = in->_hoops_PHHA;
		_hoops_ICAI (_hoops_PAGR);
	} while ((in = in->next) != null);

	return _hoops_PAGR;
}


local Tristrip  * _hoops_SSGSA (
	Tristrip *			in) {
	Tristrip *			_hoops_PAGR;
	Tristrip *			_hoops_ISGSA = null;

	do {
		ZALLOC (_hoops_PAGR, Tristrip);
		_hoops_ICAI (_hoops_PAGR);
		_hoops_PAGR->next = _hoops_ISGSA;
		_hoops_ISGSA = _hoops_PAGR;

		_hoops_RSAI (&in->face_attributes, One_Face_Attributes, &_hoops_PAGR->face_attributes);

		_hoops_APRGA(in->lengths, in->_hoops_PHHA, int, _hoops_PAGR->lengths);
		_hoops_PAGR->lengths_allocated = in->_hoops_PHHA;
		_hoops_APRGA(in->_hoops_AIHA, in->total, int, _hoops_PAGR->_hoops_AIHA);
		_hoops_APRGA(in->face_indices, in->total, int, _hoops_PAGR->face_indices);
		_hoops_PAGR->_hoops_IPII = _hoops_PAGR->_hoops_SGAHR = in->total;

		_hoops_PAGR->_hoops_RAHH |= _hoops_AAHH;

		_hoops_PAGR->total = in->total;
		_hoops_PAGR->_hoops_PHHA = in->_hoops_PHHA;
		_hoops_ICAI (_hoops_PAGR);
	} while ((in = in->next) != null);

	return _hoops_PAGR;
}


local UV_Trim * _hoops_GGRSA (
	UV_Trim *				in) {
	UV_Trim *				_hoops_PAGR = null;
	UV_Trim					*head, *prev;
	UV_Trim_Poly *			_hoops_HARIR;
	UV_Trim_Curve *			curve;
	UV_Trim_Collection *	_hoops_RGRSA;

	if (in == null)
		return null;

	head = null;
	prev = null;
	if (in != null) do {
		switch (in->type) {
			case _hoops_PARIR: {
				UV_Trim_Poly const *		_hoops_AGRSA = (UV_Trim_Poly const *)in;

				ALLOC (_hoops_HARIR, UV_Trim_Poly);
				_hoops_PAGR = (UV_Trim *)_hoops_HARIR;
				_hoops_HARIR->type = _hoops_PARIR;
				_hoops_HARIR->count = _hoops_AGRSA->count;
				_hoops_APRGA(_hoops_AGRSA->points, _hoops_AGRSA->count, UV_Point, _hoops_HARIR->points);
			}	break;

			case _hoops_IARIR: {
				UV_Trim_Curve const *		_hoops_PGRSA = (UV_Trim_Curve const *)in;

				ALLOC (curve, UV_Trim_Curve);
				_hoops_PAGR = (UV_Trim *)curve;
				_hoops_PAGR->type = _hoops_IARIR;
				curve->degree = _hoops_PGRSA->degree;
				curve->control_point_count = _hoops_PGRSA->control_point_count;
				_hoops_APRGA(_hoops_PGRSA->control_points, _hoops_PGRSA->control_point_count, UV_Point, curve->control_points);
				_hoops_APRGA(_hoops_PGRSA->weights, _hoops_PGRSA->control_point_count*sizeof(UV_Point), float, curve->weights);
				_hoops_APRGA(_hoops_PGRSA->knots, (_hoops_PGRSA->control_point_count + _hoops_PGRSA->degree + 1), float, curve->knots);
			}	break;

			case _hoops_CARIR: {
				UV_Trim_Collection const * _hoops_HGRSA = (UV_Trim_Collection const *)in;

				ALLOC (_hoops_RGRSA, UV_Trim_Collection);
				_hoops_PAGR = (UV_Trim *)_hoops_RGRSA;
				_hoops_RGRSA->type = _hoops_CARIR;
				_hoops_RGRSA->_hoops_GPRIR = _hoops_GGRSA (_hoops_HGRSA->_hoops_GPRIR);
			}	break;

			default:
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "unrecognized trim type in copyseg.c:clone_trimlist");
				return null;
		}
		_hoops_PAGR->flags = in->flags;

		if (head == null)
			head = _hoops_PAGR;			/* _hoops_GRHP _hoops_IHGC _hoops_IIGR _hoops_RH _hoops_SRS _hoops_AHAP _hoops_PSPP */
		if (prev != null)
			prev->next = _hoops_PAGR; /* _hoops_AGGAR _hoops_RH _hoops_PGHC _hoops_CARRA _hoops_IS _hoops_RH _hoops_SPR _hoops_SAHR _hoops_SPIP */
		prev = _hoops_PAGR;
	} while ((in = in->next) != null);
	_hoops_PAGR->next = null; /* _hoops_IRAP-_hoops_GHHR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_HIGR */

	return head;
}

#endif


GLOBAL_FUNCTION Polyhedron * HI_Clone_Polyhedron (
	_hoops_AIGPR *		_hoops_RIGC,
	Polyhedron *				_hoops_IGRSA) {
#ifndef _hoops_HASCA
	Geometry *					_hoops_HPGSA;
	Polyhedron *				_hoops_CGRSA;

	if (_hoops_IGRSA->type == _hoops_SCIP) {
		_hoops_GPSCA (_hoops_HPGSA, Shell);
		_hoops_CGRSA = (Polyhedron *)_hoops_HPGSA;
		Shell alter *		_hoops_SPHPR = (Shell alter *)_hoops_HPGSA;
		Shell const *		_hoops_SGRSA = (Shell const *)_hoops_IGRSA;

		if (BIT (_hoops_IGRSA->polyhedron_flags, PHF_SHELL_FACE_LIST_BY_REFERENCE))
			_hoops_SPHPR->face_list = _hoops_SGRSA->face_list;
		else
			_hoops_APRGA(_hoops_SGRSA->face_list, _hoops_SGRSA->face_list_length, int, _hoops_SPHPR->face_list);

		_hoops_SPHPR->face_list_length = _hoops_SGRSA->face_list_length;
		_hoops_SPHPR->_hoops_GSAPA = _hoops_SGRSA->_hoops_GSAPA;

		_hoops_APRGA(_hoops_SGRSA->_hoops_GRCPR, _hoops_SGRSA->_hoops_SPHA, _hoops_RHHPR, _hoops_SPHPR->_hoops_GRCPR);

		/* _hoops_PAH'_hoops_RA _hoops_SAHR _hoops_GRRSA _hoops_RPGPA _hoops_GAR _hoops_SCH _hoops_HRGR _hoops_IRGH _hoops_CICRR */
		if (_hoops_SGRSA->_hoops_HHHPR != null) {
			int						count;
			int						index;
			_hoops_RHHPR	**_hoops_RRRSA,
												**_hoops_ARRSA;

			count = _hoops_SGRSA->point_count + 1;
			ALLOC_ARRAY (_hoops_ARRSA, count, _hoops_RHHPR *);
			_hoops_SPHPR->_hoops_HHHPR = _hoops_ARRSA;

			_hoops_RRRSA = _hoops_SGRSA->_hoops_HHHPR;
			do {
				index = *_hoops_RRRSA++ - _hoops_SGRSA->_hoops_GRCPR;
				*_hoops_ARRSA++ = _hoops_SPHPR->_hoops_GRCPR + index;
			} _hoops_RGGA (--count == 0);
		}
		else
			_hoops_SPHPR->_hoops_HHHPR = null;

		_hoops_APRGA(_hoops_SGRSA->_hoops_SGCPR, _hoops_IGRSA->_hoops_SPHA, _hoops_CGCPR, _hoops_SPHPR->_hoops_SGCPR);
	}
	else { /* _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_HSHRR */
		_hoops_GPSCA (_hoops_HPGSA, _hoops_AIHPR);
		_hoops_CGRSA = (Polyhedron *)_hoops_HPGSA;
		_hoops_AIHPR alter *		_hoops_PIHPR = (_hoops_AIHPR alter *)_hoops_HPGSA;
		_hoops_AIHPR const *		_hoops_PRRSA = (_hoops_AIHPR const *)_hoops_IGRSA;

		_hoops_PIHPR->rows = _hoops_PRRSA->rows;
		_hoops_PIHPR->columns = _hoops_PRRSA->columns;
	}

	_hoops_RSAI (_hoops_IGRSA, Polyhedron, _hoops_CGRSA);

	_hoops_CGRSA->bounding.retain();

	if (BIT (_hoops_IGRSA->polyhedron_flags, PHF_POINTS_BY_REFERENCE))
		_hoops_CGRSA->points = _hoops_IGRSA->points;
	else {
		ALLOC_ARRAY_ALIGNED (_hoops_CGRSA->points, _hoops_IGRSA->point_count +
													_hoops_IGRSA->_hoops_GCRHR, Point, 16);
		_hoops_AIGA (_hoops_IGRSA->points, _hoops_IGRSA->point_count +
											_hoops_IGRSA->_hoops_GCRHR, Point, _hoops_CGRSA->points);
	}

	{
		Local_Vertex_Attributes *		_hoops_HRRSA;
		Local_Vertex_Attributes *		_hoops_IRRSA;
		int								count;

		_hoops_HRRSA = &_hoops_IGRSA->local_vertex_attributes;
		_hoops_IRRSA = &_hoops_CGRSA->local_vertex_attributes;
		count = _hoops_IGRSA->point_count + _hoops_IGRSA->_hoops_GCRHR;
		if (count < 0) count = 0;

		_hoops_IRRSA->flags = (Local_Vertex_Flags *) HI_Clone_Anything (_hoops_HRRSA->flags, count * (long)sizeof(Local_Vertex_Flags));
		_hoops_IRRSA->_hoops_PAHIR = (RGB *) HI_Clone_Anything (_hoops_HRRSA->_hoops_PAHIR, count * (long)sizeof(RGB));
		_hoops_IRRSA->ecolors = (RGB *) HI_Clone_Anything (_hoops_HRRSA->ecolors, count * (long)sizeof(RGB));
		_hoops_IRRSA->fcolors = (RGB *) HI_Clone_Anything (_hoops_HRRSA->fcolors, count * (long)sizeof(RGB));
		_hoops_IRRSA->_hoops_HAHIR = (_hoops_ACGHR *) HI_Clone_Anything (_hoops_HRRSA->_hoops_HAHIR, count * (long)sizeof(_hoops_ACGHR));
		_hoops_IRRSA->_hoops_HGHIR = (_hoops_ACGHR *) HI_Clone_Anything (_hoops_HRRSA->_hoops_HGHIR, count * (long)sizeof(_hoops_ACGHR));
		_hoops_IRRSA->_hoops_IGHIR = (_hoops_ACGHR *) HI_Clone_Anything (_hoops_HRRSA->_hoops_IGHIR, count * (long)sizeof(_hoops_ACGHR));
		_hoops_IRRSA->_hoops_IAHIR = (RGBAS32 *) HI_Clone_Anything (_hoops_HRRSA->_hoops_IAHIR, count * (long)sizeof(RGBAS32));
		_hoops_IRRSA->_hoops_CAHIR = (float *) HI_Clone_Anything (_hoops_HRRSA->_hoops_CAHIR, count * (long)sizeof(float));
		_hoops_IRRSA->_hoops_SAHIR = (unsigned char *) HI_Clone_Anything (_hoops_HRRSA->_hoops_SAHIR, count * (long)sizeof(unsigned char));

		/*_hoops_CRRSA _hoops_IPS _hoops_SRRSA _hoops_HIGR*/
		if (_hoops_HRRSA->_hoops_GPHIR) {
			_hoops_RPHIR *		_hoops_GARSA = _hoops_HRRSA->_hoops_GPHIR;
			_hoops_RPHIR *		_hoops_APHIR;
			_hoops_RPHIR **		_hoops_RARSA = &_hoops_IRRSA->_hoops_GPHIR;

			while (_hoops_GARSA) {
				ALLOC (_hoops_APHIR, _hoops_RPHIR);
				_hoops_APHIR->_hoops_HSAI = _hoops_GARSA->_hoops_HSAI;
				HI_Copy_Name (&_hoops_GARSA->name, &_hoops_APHIR->name);
				_hoops_APHIR->key = _hoops_GARSA->key;
				_hoops_APHIR->id = _hoops_GARSA->id;
				*_hoops_RARSA = _hoops_APHIR;
				_hoops_RARSA = &_hoops_APHIR->next;
				_hoops_GARSA = _hoops_GARSA->next;
			}
			*_hoops_RARSA = null;
		}
		else
			_hoops_IRRSA->_hoops_GPHIR = null;

		_hoops_IRRSA->normals = (Vector *) HI_Clone_Anything (_hoops_HRRSA->normals, count * (long)sizeof(Vector));
		_hoops_IRRSA->params = (_hoops_RSSH *) HI_Clone_Anything (_hoops_HRRSA->params, (long)(count*sizeof(_hoops_RSSH)*_hoops_HRRSA->param_width));
		_hoops_IRRSA->param_width = _hoops_HRRSA->param_width;

		_hoops_IRRSA->_hoops_PPHIR = 0;
		_hoops_IRRSA->_hoops_HPHIR = 0;
		_hoops_IRRSA->_hoops_IPHIR = 0;
	}

	{
		_hoops_RPGHR *			_hoops_AARSA;
		_hoops_RPGHR *			_hoops_PARSA;
		int								count;

		_hoops_AARSA	 = &_hoops_IGRSA->_hoops_IHHPR;
		_hoops_PARSA	 = &_hoops_CGRSA->_hoops_IHHPR;
		count = _hoops_IGRSA->_hoops_SPHA;
		if (count < 0) count = 0;

		_hoops_PARSA->flags = (_hoops_GHHPR *) HI_Clone_Anything (_hoops_AARSA->flags, count * (long)sizeof(_hoops_GHHPR));
		_hoops_PARSA->colors = (RGB *) HI_Clone_Anything (_hoops_AARSA->colors, count * (long)sizeof(RGB));
		_hoops_PARSA->findices = (_hoops_ACGHR *) HI_Clone_Anything (_hoops_AARSA->findices, count * (long)sizeof(_hoops_ACGHR));
		_hoops_PARSA->_hoops_AHHIR = (unsigned char *) HI_Clone_Anything (_hoops_AARSA->_hoops_AHHIR, count * (long)sizeof(unsigned char));
		_hoops_PARSA->weights = (float *) HI_Clone_Anything (_hoops_AARSA->weights, count * (long)sizeof(float));
		_hoops_PARSA->normals = (Vector *) HI_Clone_Anything (_hoops_AARSA->normals, count * (long)sizeof(Vector));

		/*_hoops_CRRSA _hoops_IPS _hoops_PAIA _hoops_HIGR*/
		if (_hoops_AARSA->_hoops_PHHIR) {
			_hoops_HHHIR *		_hoops_HARSA = _hoops_AARSA->_hoops_PHHIR;
			_hoops_HHHIR *		_hoops_CHHIR;
			_hoops_HHHIR **		_hoops_IARSA = &_hoops_PARSA->_hoops_PHHIR;

			while (_hoops_HARSA) {
				ALLOC (_hoops_CHHIR, _hoops_HHHIR);
				_hoops_CHHIR->_hoops_HSAI = _hoops_HARSA->_hoops_HSAI;
				HI_Copy_Name (&_hoops_HARSA->name, &_hoops_CHHIR->name);
				_hoops_CHHIR->key = _hoops_HARSA->key;
				_hoops_CHHIR->id = _hoops_HARSA->id;
				*_hoops_IARSA = _hoops_CHHIR;
				_hoops_IARSA = &_hoops_CHHIR->next;
				_hoops_HARSA = _hoops_HARSA->next;
			}
			*_hoops_IARSA = null;
		}
		else
			_hoops_PARSA->_hoops_PHHIR = null;
	}

	{
		Local_Face_Attributes *			_hoops_CARSA;
		Local_Face_Attributes *			_hoops_SARSA;
		int								count;

		_hoops_CARSA	 = &_hoops_IGRSA->local_face_attributes;
		_hoops_SARSA	 = &_hoops_CGRSA->local_face_attributes;
		count = _hoops_IGRSA->face_count;
		if (count < 0) count = 0;

		_hoops_APRGA(_hoops_CARSA->flags, count, _hoops_GIIPR, _hoops_SARSA->flags);
		_hoops_SARSA->colors = (RGB *) HI_Clone_Anything (_hoops_CARSA->colors, count * (long)sizeof(RGB));
		_hoops_SARSA->findices = (_hoops_ACGHR *) HI_Clone_Anything (_hoops_CARSA->findices, count * (long)sizeof(_hoops_ACGHR));
		_hoops_SARSA->_hoops_AHHIR = (unsigned char *) HI_Clone_Anything (_hoops_CARSA->_hoops_AHHIR, count * (long)sizeof(unsigned char));
		_hoops_APRGA(_hoops_CARSA->_hoops_GARHR, _hoops_CARSA->_hoops_HCRHR, _hoops_SRRHR, _hoops_SARSA->_hoops_GARHR);

		if (_hoops_CARSA->normals != null) {
			ALLOC_ARRAY_ALIGNED (_hoops_SARSA->normals, count, _hoops_ARPA, 16);
			_hoops_AIGA (_hoops_CARSA->normals, count, _hoops_ARPA, _hoops_SARSA->normals);
		}
		else
			_hoops_SARSA->normals = null;
	}

	_hoops_CGRSA->local_face_attributes.regions = (int *) HI_Clone_Anything (_hoops_IGRSA->local_face_attributes.regions,
																		     (_hoops_IGRSA->face_count + _hoops_SHHIR) * (long)sizeof(int));

	if (_hoops_IGRSA->_hoops_GIGPR != null)
		_hoops_CGRSA->_hoops_GIGPR = _hoops_HSGSA (_hoops_IGRSA->_hoops_GIGPR, (Geometry *)_hoops_CGRSA);

	if (_hoops_IGRSA->_hoops_SHGPR != null)
		_hoops_CGRSA->_hoops_SHGPR = _hoops_CSGSA (_hoops_IGRSA->_hoops_SHGPR);

	if (_hoops_IGRSA->tristrips != null)
		_hoops_CGRSA->tristrips = _hoops_SSGSA (_hoops_IGRSA->tristrips);

	if (_hoops_IGRSA->_hoops_CHGPR != null)
		_hoops_CGRSA->_hoops_CHGPR = _hoops_CSGSA (_hoops_IGRSA->_hoops_CHGPR);

	if (_hoops_IGRSA->_hoops_HGAIR != null)
		_hoops_CGRSA->_hoops_HGAIR = _hoops_GHSCA (_hoops_RIGC, _hoops_IGRSA->_hoops_HGAIR);

	_hoops_APRGA (_hoops_IGRSA->_hoops_GIHIR._hoops_SIAIR, _hoops_IGRSA->_hoops_GIHIR._hoops_CIAIR, float,
				 _hoops_CGRSA->_hoops_GIHIR._hoops_SIAIR);


	return _hoops_CGRSA;
#else
	return null;
#endif
}

GLOBAL_FUNCTION Geometry * HI_Copy_Geometry (
	_hoops_AIGPR *		_hoops_RIGC,
	Geometry const *			_hoops_PPGSA) {
#ifndef _hoops_HASCA
	Geometry *				_hoops_HPGSA = null;

	switch (_hoops_PPGSA->type) {
		case _hoops_SGCP: {
			if (BIT (_hoops_PPGSA->_hoops_RRHH, _hoops_SHHI)) {
				_hoops_GPSCA (_hoops_HPGSA, _hoops_AIHI);
				_hoops_RSAI(_hoops_PPGSA, _hoops_AIHI, _hoops_HPGSA);
			}
			else {
				_hoops_GPSCA (_hoops_HPGSA, _hoops_PHPIR);
				_hoops_RSAI(_hoops_PPGSA, _hoops_PHPIR, _hoops_HPGSA);
			}
		}	break;

		case _hoops_HGPGR: {
			_hoops_GPSCA (_hoops_HPGSA, _hoops_HHPIR);
			_hoops_RSAI(_hoops_PPGSA, _hoops_HHPIR, _hoops_HPGSA);

			_hoops_HHPIR const *	_hoops_GPRSA = (_hoops_HHPIR const *)_hoops_PPGSA;

			_hoops_APRGA(_hoops_GPRSA->planes, _hoops_GPRSA->count, _hoops_ARPA, ((_hoops_HHPIR *)_hoops_HPGSA)->planes);
		}	break;

		case _hoops_RIIP:
		case _hoops_GRCP:
		case _hoops_RRCP: {
			if (BIT (_hoops_PPGSA->_hoops_RRHH, _hoops_SHHI)) {
				_hoops_GPSCA (_hoops_HPGSA, Circular_Arc_Lite);
				_hoops_RSAI(_hoops_PPGSA, Circular_Arc_Lite, _hoops_HPGSA);
			}
			else {
				_hoops_GPSCA (_hoops_HPGSA, Circular_Arc);
				_hoops_RSAI(_hoops_PPGSA, Circular_Arc, _hoops_HPGSA);
			}
		}	break;

		case _hoops_CGCP: {
			_hoops_GPSCA (_hoops_HPGSA, Ellipse);
			_hoops_RSAI(_hoops_PPGSA, Ellipse, _hoops_HPGSA);
		}	break;

		case _hoops_GIIP: {
			_hoops_GPSCA (_hoops_HPGSA, Elliptical_Arc);
			_hoops_RSAI(_hoops_PPGSA, Elliptical_Arc, _hoops_HPGSA);
		}	break;

		case _hoops_GGCP: {
			_hoops_GPSCA (_hoops_HPGSA, Grid);
			_hoops_RSAI(_hoops_PPGSA, Grid, _hoops_HPGSA);
			/* _hoops_PSP _hoops_PCIAR _hoops_IIGR _hoops_AIRI _hoops_CPCI _hoops_CHR _hoops_PHRH, _hoops_HIS _hoops_RH _hoops_CCAH _hoops_SPR _hoops_GRS
			* _hoops_SHH _hoops_AHHR'_hoops_GHGP... _hoops_IS _hoops_SHH _hoops_PIISR _hoops_HPGR _hoops_SPS _hoops_PAAP */
#if 0
			SET_MEMORY(&_hoops_HPGSA->grid.dl, sizeof(_hoops_GACR), 0);
#endif
		}	break;

		case _hoops_RCIP: {
			_hoops_GPSCA (_hoops_HPGSA, Polygon);
			_hoops_RSAI(_hoops_PPGSA, Polygon, _hoops_HPGSA);
			Polygon const *		_hoops_RPRSA = (Polygon const *)_hoops_PPGSA;
			Polygon alter *		_hoops_APRSA = (Polygon alter *)_hoops_HPGSA;

			_hoops_APRGA(_hoops_RPRSA->points, _hoops_RPRSA->count, Point, _hoops_APRSA->points);
			_hoops_APRSA->allocated = _hoops_RPRSA->count;
		}	break;

		case _hoops_SCIP:
		case _hoops_GSIP: {
			_hoops_HPGSA = (Geometry *) HI_Clone_Polyhedron (_hoops_RIGC, (Polyhedron *) _hoops_PPGSA);
		}	break;

		case _hoops_SIIP:
		case _hoops_IIIP: {
			_hoops_GPSCA (_hoops_HPGSA, Polyline);
			_hoops_RSAI(_hoops_PPGSA, Polyline, _hoops_HPGSA);
			Polyline const *		_hoops_PPRSA = (Polyline const *)_hoops_PPGSA;
			Polyline alter *		_hoops_HPRSA = (Polyline alter *)_hoops_HPGSA;

			_hoops_HPRSA->allocated = Abs(_hoops_PPRSA->count);
			_hoops_APRGA(_hoops_PPRSA->points, _hoops_HPRSA->allocated, Point, _hoops_HPRSA->points);
			if (_hoops_PPRSA->orientation != null)
				if (BIT(_hoops_PPGSA->_hoops_RRHH, _hoops_HCPIR))
					_hoops_APRGA(_hoops_PPRSA->orientation, 2, Vector, _hoops_HPRSA->orientation);
				else
					_hoops_APRGA(_hoops_PPRSA->orientation, 1, Vector, _hoops_HPRSA->orientation);
		}	break;

		case _hoops_HIIP: {
			_hoops_GPSCA (_hoops_HPGSA, _hoops_SHRIR);
			_hoops_RSAI(_hoops_PPGSA, _hoops_SHRIR, _hoops_HPGSA);
			_hoops_SHRIR const *		_hoops_IPRSA = (_hoops_SHRIR const *)_hoops_PPGSA;
			_hoops_SHRIR alter *		_hoops_CPRSA = (_hoops_SHRIR alter *)_hoops_HPGSA;

			_hoops_CPRSA->allocated = -_hoops_IPRSA->count;
			_hoops_APRGA(_hoops_IPRSA->points, _hoops_CPRSA->allocated, Point, _hoops_CPRSA->points);
			if (_hoops_IPRSA->mapping != null) {
				int		count = _hoops_CPRSA->allocated/2;

				ALLOC_ARRAY(_hoops_CPRSA->mapping, count, int);
				for (int offset = 0; offset < count; ++offset)
					_hoops_CPRSA->mapping[offset] = HI_Record_Lightweight_Key ((_hoops_HPAH *)_hoops_CPRSA, offset) |
												_hoops_IPRSA->mapping[offset] & _hoops_RIRIR;
			}
		}	break;

		case _hoops_PIIP: {
			_hoops_GPSCA (_hoops_HPGSA, Line);
			_hoops_RSAI(_hoops_PPGSA, Line, _hoops_HPGSA);
		}	break;

		case _hoops_CHIP: {
#ifndef _hoops_CCPIR
			_hoops_PIRGR *_hoops_SPRSA = (_hoops_PIRGR *)_hoops_PPGSA;
			_hoops_PIRGR *_hoops_GHRSA;
			int knot_count = _hoops_SPRSA->control_point_count + _hoops_SPRSA->degree + 1;

			_hoops_GPSCA (_hoops_HPGSA, _hoops_PIRGR);
			_hoops_RSAI(_hoops_PPGSA, _hoops_PIRGR, _hoops_HPGSA);

			_hoops_GHRSA = (_hoops_PIRGR *)_hoops_HPGSA;

			_hoops_APRGA(_hoops_SPRSA->control_points, _hoops_SPRSA->control_point_count, Point, _hoops_GHRSA->control_points);
			_hoops_APRGA(_hoops_SPRSA->knots, knot_count, float, _hoops_GHRSA->knots);
			_hoops_APRGA(_hoops_SPRSA->weights, _hoops_SPRSA->control_point_count, float, _hoops_GHRSA->weights);

			_hoops_GHRSA->polyline.allocated = 0;
			_hoops_GHRSA->polyline.count = 0;
			_hoops_GHRSA->polyline.points = null;
#endif
		}	break;

		case _hoops_PRCP: {
#ifndef _hoops_GSPIR
			_hoops_APPGR *_hoops_SPRSA = (_hoops_APPGR *)_hoops_PPGSA;
			_hoops_APPGR *_hoops_GHRSA;
			int _hoops_RSPIR = _hoops_SPRSA->u_degree + _hoops_SPRSA->n_u_vertices + 1;
			int _hoops_ASPIR = _hoops_SPRSA->v_degree + _hoops_SPRSA->n_v_vertices + 1;

			_hoops_GPSCA (_hoops_HPGSA, _hoops_APPGR);
			_hoops_RSAI(_hoops_PPGSA, _hoops_APPGR, _hoops_HPGSA);
			_hoops_GHRSA = (_hoops_APPGR *)_hoops_HPGSA;

			_hoops_APRGA(_hoops_SPRSA->control_points, _hoops_SPRSA->n_u_vertices * _hoops_SPRSA->n_v_vertices, Point, _hoops_GHRSA->control_points);
			_hoops_APRGA(_hoops_SPRSA->weights, _hoops_SPRSA->n_u_vertices * _hoops_SPRSA->n_v_vertices, float, _hoops_GHRSA->weights);
			_hoops_APRGA(_hoops_SPRSA->u_knots, _hoops_RSPIR, float, _hoops_GHRSA->u_knots);
			_hoops_APRGA(_hoops_SPRSA->v_knots, _hoops_ASPIR, float, _hoops_GHRSA->v_knots);

			_hoops_GHRSA->_hoops_GPRIR = _hoops_GGRSA (_hoops_SPRSA->_hoops_GPRIR);

			/* _hoops_RGR _hoops_HRGR _hoops_GAHPR _hoops_RHRSA, _hoops_CR _hoops_SCH _hoops_GRS _hoops_HGAP _hoops_SGS _hoops_SR _hoops_AHRSA
			* _hoops_GPP _hoops_RH _hoops_SPS _hoops_PAAP.  _hoops_PS _hoops_HHS _hoops_AGRP _hoops_IS _hoops_IRS _hoops_PHRSA _hoops_AASA _hoops_HPGR _hoops_HHH _hoops_PPSR,
			* _hoops_HIH _hoops_HAR _hoops_RPHR _hoops_HA */
			_hoops_GHRSA->_hoops_IPRI = null;
#endif
		}	break;

		case _hoops_ASIP: {
#ifndef _hoops_PSPIR
			_hoops_GPSCA (_hoops_HPGSA, Cylinder);
			_hoops_RSAI(_hoops_PPGSA, Cylinder, _hoops_HPGSA);
#endif
		}	break;

		case _hoops_CSIP: {
#ifndef _hoops_PSPIR
			_hoops_GPSCA (_hoops_HPGSA, PolyCylinder);
			_hoops_RSAI(_hoops_PPGSA, PolyCylinder, _hoops_HPGSA);
			PolyCylinder const *		_hoops_HHRSA = (PolyCylinder const *)_hoops_PPGSA;
			PolyCylinder alter *		_hoops_IHRSA = (PolyCylinder alter *)_hoops_HPGSA;

			_hoops_IHRSA->bounding.retain();

			_hoops_IHRSA->_hoops_SGHIR = null;
			_hoops_IHRSA->_hoops_GRHIR = null;

			_hoops_APRGA(_hoops_HHRSA->points, _hoops_HHRSA->point_count, Point, _hoops_IHRSA->points);
			_hoops_APRGA(_hoops_HHRSA->radii, _hoops_HHRSA->_hoops_ISPIR, float, _hoops_IHRSA->radii);

			if (_hoops_HHRSA->_hoops_RGHIR != null) {
				_hoops_AGHIR const *		_hoops_CHRSA = _hoops_HHRSA->_hoops_RGHIR;
				_hoops_AGHIR alter *		_hoops_SHRSA;
				int count = _hoops_HHRSA->point_count;

				_hoops_APRGA(_hoops_CHRSA, 1, _hoops_AGHIR, _hoops_SHRSA); _hoops_IHRSA->_hoops_RGHIR = _hoops_SHRSA;

				_hoops_APRGA(_hoops_CHRSA->fcolors, count, RGB, _hoops_SHRSA->fcolors);
				_hoops_APRGA(_hoops_CHRSA->ecolors, count, RGB, _hoops_SHRSA->ecolors);
				_hoops_APRGA(_hoops_CHRSA->_hoops_IGHIR, count, _hoops_ACGHR, _hoops_SHRSA->_hoops_IGHIR);
				_hoops_APRGA(_hoops_CHRSA->_hoops_HGHIR, count, _hoops_ACGHR, _hoops_SHRSA->_hoops_HGHIR);
				_hoops_APRGA(_hoops_CHRSA->flags, count, _hoops_CGHIR, _hoops_SHRSA->flags);
			}

			_hoops_APRGA(_hoops_HHRSA->_hoops_CSPIR, _hoops_HHRSA->point_count, _hoops_SSPIR, _hoops_IHRSA->_hoops_CSPIR);
			_hoops_APRGA(_hoops_HHRSA->_hoops_GGHIR, _hoops_HHRSA->point_count, float, _hoops_IHRSA->_hoops_GGHIR);
#endif
		}	break;

		case _hoops_HSIP: {
#ifndef _hoops_RRHIR
			_hoops_GPSCA (_hoops_HPGSA, Sphere);
			_hoops_RSAI(_hoops_PPGSA, Sphere, _hoops_HPGSA);
#endif
		}	break;

		case _hoops_PCIP: {
			_hoops_GPSCA (_hoops_HPGSA, Marker);
			_hoops_RSAI (_hoops_PPGSA, Marker, _hoops_HPGSA);
			Marker const *		_hoops_GIRSA = (Marker const *)_hoops_PPGSA;
			Marker alter *		_hoops_RIRSA = (Marker alter *)_hoops_HPGSA;

			if (_hoops_GIRSA->orientation != null)
			if (BIT(_hoops_PPGSA->_hoops_RRHH, _hoops_IHPIR))
				_hoops_APRGA(_hoops_GIRSA->orientation, 2, Vector, _hoops_RIRSA->orientation);
			else
				_hoops_APRGA(_hoops_GIRSA->orientation, 1, Vector, _hoops_RIRSA->orientation);
		}	break;

		case _hoops_PIRS: {
			_hoops_GPSCA (_hoops_HPGSA, _hoops_GRPGR);
			_hoops_RSAI(_hoops_PPGSA, _hoops_GRPGR, _hoops_HPGSA);
			_hoops_GRPGR const *		_hoops_AIRSA = (_hoops_GRPGR const *)_hoops_PPGSA;
			_hoops_GRPGR alter *		_hoops_PIRSA = (_hoops_GRPGR alter *)_hoops_HPGSA;

			_hoops_PIRSA->allocated = _hoops_AIRSA->count;
			_hoops_APRGA(_hoops_AIRSA->points, _hoops_PIRSA->allocated, Point, _hoops_PIRSA->points);
			if (_hoops_AIRSA->mapping != null) {
				int		count = _hoops_PIRSA->allocated;

				ALLOC_ARRAY(_hoops_PIRSA->mapping, count, int);
				for (int offset = 0; offset < count; ++offset)
					_hoops_PIRSA->mapping[offset] = HI_Record_Lightweight_Key ((_hoops_HPAH *)_hoops_PIRSA, offset) |
												_hoops_AIRSA->mapping[offset] & _hoops_RIRIR;
			}
		}	break;

		case _hoops_ICIP: {
			Light const *		_hoops_HIRSA = (Light const *)_hoops_PPGSA;

			switch (_hoops_HIRSA->_hoops_PRR) {
				case _hoops_H: {
					_hoops_GPSCA (_hoops_HPGSA, _hoops_HIPIR);
					_hoops_RSAI(_hoops_PPGSA, _hoops_HIPIR, _hoops_HPGSA);
				}	break;

				case _hoops_C: {
					_hoops_GPSCA (_hoops_HPGSA, _hoops_AIPIR);
					_hoops_RSAI(_hoops_PPGSA, _hoops_AIPIR, _hoops_HPGSA);
				}	break;

				case _hoops_I: {
					_hoops_GPSCA (_hoops_HPGSA, _hoops_PIPIR);
					_hoops_RSAI(_hoops_PPGSA, _hoops_PIPIR, _hoops_HPGSA);
				}	break;

				case _hoops_S: {
					_hoops_GPSCA (_hoops_HPGSA, _hoops_SHPIR);
					_hoops_RSAI(_hoops_PPGSA, _hoops_SHPIR, _hoops_HPGSA);

					_hoops_SHPIR const *		_hoops_IIRSA = (_hoops_SHPIR const *)_hoops_PPGSA;
					_hoops_SHPIR alter *		_hoops_CIRSA = (_hoops_SHPIR alter *)_hoops_HPGSA;

					_hoops_APRGA(_hoops_IIRSA->points, _hoops_IIRSA->count, Point, _hoops_CIRSA->points);
				}	break;
			}
		}	break;

		case _hoops_GHPGR: {
			_hoops_GPSCA (_hoops_HPGSA, _hoops_RHPGR);
			_hoops_RSAI(_hoops_PPGSA, _hoops_RHPGR, _hoops_HPGSA);
		}	break;

		case HK_STRING_CURSOR: {
			_hoops_GPSCA (_hoops_HPGSA, _hoops_PIGPR);
			_hoops_RSAI(_hoops_PPGSA, _hoops_PIGPR, _hoops_HPGSA);
		}	break;

		case _hoops_AGCP: {
			_hoops_GPSCA (_hoops_HPGSA, _hoops_HACC);
			_hoops_RSAI (_hoops_PPGSA, _hoops_HACC, _hoops_HPGSA);
			_hoops_HACC const *		_hoops_SIRSA = (_hoops_HACC const *)_hoops_PPGSA;
			_hoops_HACC alter *		_hoops_GCRSA = (_hoops_HACC alter *)_hoops_HPGSA;

			_hoops_GCRSA->bounding.retain();

			if (_hoops_GCRSA->_hoops_AAPGR != null)
				_hoops_RSGSA (_hoops_RIGC, _hoops_SIRSA->_hoops_AAPGR, &_hoops_GCRSA->_hoops_AAPGR, _hoops_HPGSA);

			_hoops_GCRSA->karacters = (Karacter *)HI_Clone_Anything (_hoops_SIRSA->karacters,
			(_hoops_SIRSA->count+1) * (long)sizeof (Karacter));

			if (_hoops_SIRSA->_hoops_RIHIR != null) {
				_hoops_GCRSA->_hoops_ICI = (int *)HI_Clone_Anything (_hoops_SIRSA->_hoops_ICI, _hoops_SIRSA->_hoops_PICHR * (long)sizeof (int));

				/* "_hoops_RRGPR" _hoops_IRHS _hoops_IS _hoops_PPSR _hoops_CRGR _hoops_RH _hoops_CCAH _hoops_RCRSA _hoops_CRPR, _hoops_HIS _hoops_GRAS
				* _hoops_CCAH _hoops_CICRR _hoops_IIHA _hoops_GPP _hoops_AII _hoops_GGHAA _hoops_HPP _hoops_RHGS _hoops_CICRR */
				ALLOC_ARRAY (_hoops_GCRSA->_hoops_RIHIR, _hoops_GCRSA->_hoops_PICHR, Karacter *);

				for (int i = 0; i < _hoops_GCRSA->_hoops_PICHR; ++i)
					_hoops_GCRSA->_hoops_RIHIR[i] = _hoops_GCRSA->karacters + (_hoops_SIRSA->_hoops_RIHIR[i] - _hoops_SIRSA->karacters);
			}

			if (_hoops_SIRSA->region != null) {
				ALLOC (_hoops_GCRSA->region, _hoops_AIHIR);
				_hoops_RSAI (_hoops_SIRSA->region, _hoops_AIHIR, _hoops_GCRSA->region);
			}

			if (_hoops_SIRSA->_hoops_PIHIR != null) {
				ALLOC_ARRAY (_hoops_GCRSA->_hoops_PIHIR, _hoops_SIRSA->count, _hoops_HIHIR);
				_hoops_AIGA (_hoops_SIRSA->_hoops_PIHIR, _hoops_SIRSA->count, _hoops_HIHIR,
							 _hoops_GCRSA->_hoops_PIHIR);

				for (int i = 0; i < _hoops_SIRSA->count; i++) {
					if (_hoops_SIRSA->_hoops_PIHIR[i]._hoops_HGPIR != null)
						_hoops_SIRSA->_hoops_PIHIR[i]._hoops_HGPIR = HI_Copy_Font_Names (_hoops_SIRSA->_hoops_PIHIR[i]._hoops_HGPIR);
				}
			}
		}	break;

		case _hoops_HGCP: {
			void const **			_hoops_ACRSA;
			void const * const *	_hoops_PCRSA;
			int						count;

			_hoops_GPSCA (_hoops_HPGSA, Image);
			_hoops_RSAI(_hoops_PPGSA, Image, _hoops_HPGSA);
			Image const *		_hoops_HCRSA = (Image const *)_hoops_PPGSA;
			Image alter *		_hoops_ICRSA = (Image alter *)_hoops_HPGSA;

			_hoops_ICRSA->_hoops_GAHA = null;
			_hoops_ICRSA->_hoops_PHGH = null;
			_hoops_ICRSA->_hoops_RCPIR = null;
			HI_Copy_Name (&_hoops_HCRSA->name, &_hoops_ICRSA->name);

			if (BIT (_hoops_HCRSA->flags, _hoops_SSGH)) {
				_hoops_ICRSA->_hoops_IARH = _hoops_HCRSA->_hoops_IARH;
				ASSERT (_hoops_HCRSA->rasters == null); //_hoops_IAII 2 _hoops_RRRH _hoops_HAII _hoops_PSHR _hoops_PPGS
				//_hoops_PIP: _hoops_CCRSA, _hoops_HAR _hoops_SCRSA _hoops_ARI, _hoops_CR _hoops_GSRSA _hoops_CHR _hoops_RGHP _hoops_IH _hoops_SGRH _hoops_RRRH
				ALLOC_ARRAY (_hoops_ICRSA->_hoops_PHGH, _hoops_HCRSA->_hoops_IARH, char);
				COPY_MEMORY ((void alter *)_hoops_HCRSA->_hoops_PHGH,
					(long)_hoops_HCRSA->_hoops_IARH,
					(void alter *)_hoops_ICRSA->_hoops_PHGH);
			}
			else if (BIT (_hoops_PPGSA->_hoops_RRHH, _hoops_IIPIR)) {
				void** _hoops_RSRSA;
				_hoops_APRGA(((void  *)_hoops_HCRSA->rasters), _hoops_HCRSA->height, void*, _hoops_RSRSA);
				_hoops_ICRSA->rasters = _hoops_RSRSA;
			}
			else {
				ALLOC_ARRAY (_hoops_ACRSA, _hoops_HCRSA->height, void const *);
				_hoops_ICRSA->rasters = _hoops_ACRSA;

				TRY_ALLOC_ARRAY (_hoops_ICRSA->_hoops_PHGH, (long)_hoops_ICRSA->row_bytes * (long)_hoops_ICRSA->height, char);

				count = _hoops_HCRSA->height;

				if (_hoops_ICRSA->_hoops_PHGH != null) {
					unsigned char	*_hoops_PHGH;

					_hoops_PHGH = (unsigned char *)_hoops_ICRSA->_hoops_PHGH;
					if (count > 0) do {
						*_hoops_ACRSA++ = (void *)_hoops_PHGH;
						_hoops_PHGH += _hoops_ICRSA->row_bytes;
					} _hoops_RGGA (--count == 0);
				}
				else {
					if (count > 0) do {
						ALLOC_ARRAY (*_hoops_ACRSA, _hoops_ICRSA->width * _hoops_ICRSA->_hoops_GCPIR, unsigned char);
						++_hoops_ACRSA;
					} _hoops_RGGA (--count == 0);
				}

				if (_hoops_ICRSA->_hoops_PHGH != null && _hoops_HCRSA->_hoops_PHGH != null) {
					COPY_MEMORY ((void alter *)_hoops_HCRSA->_hoops_PHGH,
						(long)_hoops_ICRSA->height * (long)_hoops_ICRSA->row_bytes,
						(void alter *)_hoops_ICRSA->_hoops_PHGH);
				}
				else {
					_hoops_PCRSA = _hoops_HCRSA->rasters;
					count = _hoops_HCRSA->height;
					_hoops_ACRSA = (void const * alter *)_hoops_ICRSA->rasters;

					do
						COPY_MEMORY ((void alter *)*_hoops_PCRSA++,
							(long)_hoops_HCRSA->width * (long)_hoops_HCRSA->_hoops_GCPIR,
							(void alter *)*_hoops_ACRSA++);
					_hoops_RGGA (--count == 0);
				}
			}

			/* _hoops_HHS _hoops_IPS _hoops_RH _hoops_PIAH _hoops_ASRSA, _hoops_HIH _hoops_PAH _hoops_GACC _hoops_SCRHR _hoops_CAPR _hoops_GPP _hoops_HRGGR */
			_hoops_ICRSA->next = null;
			/* _hoops_CIS (_hoops_GGR _hoops_GSSR _hoops_IPS, _hoops_APIC) _hoops_GRS _hoops_CCIH _hoops_GH _hoops_IRGH _hoops_HH _hoops_AGGAR */
			_hoops_ICRSA->texture = null;
		}	break;

		case _hoops_AHIP: {

			_hoops_GPSCA (_hoops_HPGSA, _hoops_PHIP);
			_hoops_RSAI(_hoops_PPGSA, _hoops_PHIP, _hoops_HPGSA);
			_hoops_PHIP const *		_hoops_PSRSA = (_hoops_PHIP const *)_hoops_PPGSA;
			_hoops_PHIP alter *		_hoops_HSRSA = (_hoops_PHIP alter *)_hoops_HPGSA;

			_hoops_HSRSA->bounding.retain();

			ALLOC_ARRAY (_hoops_HSRSA->_hoops_IHIP, _hoops_HSRSA->_hoops_HHIP, _hoops_SIHIR const *);
			_hoops_AIGA (_hoops_PSRSA->_hoops_IHIP, _hoops_PSRSA->_hoops_HHIP, _hoops_SIHIR const *, _hoops_HSRSA->_hoops_IHIP);

			for (int i = 0; i<_hoops_HSRSA->_hoops_HHIP; i++)
				_hoops_PRRH (_hoops_HSRSA->_hoops_IHIP[i]);

			_hoops_ISRSA(_hoops_RIGC, _hoops_HSRSA);

			HI_Copy_Conditional (&_hoops_PSRSA->condition, &_hoops_HSRSA->condition);
		}	break;

		default: {
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, Sprintf_D (null,
											 "Unexpected segment geometry type (#%d)", _hoops_PPGSA->type));
			return 0;
		}		/* _hoops_IHSA; */
	}

	_hoops_HPGSA->_hoops_HIHI = 1;
	_hoops_HPGSA->key = _hoops_AIRIR (_hoops_HPGSA);
	_hoops_HPGSA->_hoops_CPGPR = _hoops_HCHPA;
	_hoops_HPGSA->_hoops_SPGPR = false;
	_hoops_HPGSA->next = null;
	_hoops_HPGSA->backlink = &_hoops_HPGSA->next;

	if ((_hoops_HPGSA->_hoops_IPPGR =
			HI_Clone_Attributes (_hoops_RIGC, _hoops_PPGSA->_hoops_IPPGR, (_hoops_CRCP const *)_hoops_HPGSA, true, null)) != null)
		_hoops_HPGSA->_hoops_IPPGR->backlink = &_hoops_HPGSA->_hoops_IPPGR;

	return _hoops_HPGSA;
#else
	return null;
#endif
}

HC_INTERFACE Key HC_CDECL HC_Copy_Segment (
	char const *		oldname,
	char const *		newname)
{
	_hoops_PAPPR context("Copy_Segment");

#ifdef DISABLE_DATABASE_EDIT
	_hoops_IRPPR ("Database Edit");
	return _hoops_SHSSR;
#else

	_hoops_RPPPR();
	Key	key = _hoops_CCGSA (context, oldname, newname, null);
	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "DEFINE (HC_Copy_Segment (%S, %S), ", oldname, newname));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", key));
	);

	return key;
#endif
}


HC_INTERFACE Key HC_CDECL HC_Copy_Segment_With_Mapping (
	char const *				oldname,
	char const *				newname,
	int							count,
	Key const *					old_keys,
	Key alter *					new_keys)
{
	_hoops_PAPPR context("Copy_Segment_With_Mapping");

#ifdef DISABLE_DATABASE_EDIT
	_hoops_IRPPR ("Database Edit");
	return _hoops_SHSSR;
#else

	Key alter *	_hoops_CSRSA = new_keys;

	if (count > 0 && new_keys == old_keys)
		ALLOC_ARRAY (_hoops_CSRSA, count, Key);

	_hoops_IISCA		_hoops_HASAR;
	ZERO_STRUCT (&_hoops_HASAR, _hoops_IISCA);
	_hoops_HASAR.count = count;
	_hoops_HASAR.old_keys = old_keys;
	_hoops_HASAR.new_keys = _hoops_CSRSA;

	_hoops_RPPPR();
	Key key = _hoops_CCGSA (context, oldname, newname, &_hoops_HASAR);
	_hoops_IRRPR();

	if (_hoops_CSRSA != new_keys) {
		_hoops_AIGA (_hoops_CSRSA, count, Key, new_keys);
		FREE_ARRAY (_hoops_CSRSA, count, Key);
	}

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "DEFINE (HC_Copy_Segment/*_With_Mapping*/	(%S, %S), ", oldname, newname));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", key));
	);

	return key;
#endif
}


#ifndef _hoops_PASCA
local void _hoops_SSRSA (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_CRCP	*					_hoops_SRCP,
	void *						info) {
	_hoops_IISCA *		data = (_hoops_IISCA *)info;
	Geometry const *			_hoops_PPGSA = data->geometry;
	Geometry *					_hoops_HPGSA = 0;

	if (_hoops_PPGSA->type == HK_STRING_CURSOR) {
		/*_hoops_ASIGA _hoops_RIHH*/
		return;
	}

	_hoops_HPGSA = HI_Copy_Geometry (_hoops_RIGC, _hoops_PPGSA);

	if (_hoops_HPGSA == 0)
		return;

	HI_Insert_Geometry (_hoops_RIGC, (_hoops_HPAH*)_hoops_SRCP, _hoops_HPGSA, !BIT (_hoops_PPGSA->_hoops_RRHH, _hoops_RSPCR),
						_hoops_IHSSR);

	_hoops_RAGSA (_hoops_RIGC, _hoops_SRCP, _hoops_HPGSA);

	data->count++;
	data->key = _hoops_AIRIR(_hoops_HPGSA);
}

local bool HC_CDECL _hoops_GGASA (
	_hoops_AIGPR *		_hoops_RIGC,
	Key							in_key,
	char const *				_hoops_SRCP,
	Key *						out_key)
{
	if (out_key)
		*out_key = _hoops_SHSSR;

	Geometry *	geom = (Geometry *)_hoops_RCSSR (_hoops_RIGC, in_key);

	if (geom == null || BIT (geom->_hoops_RRHH, _hoops_HGAGR) ||
		geom->type < _hoops_AHRIR ||
		geom->type > _hoops_GHPGR) {

		HE_ERROR (HEC_GEOMETRY, HES_INVALID_KEY, "Provided key does not refer to valid geometry");
			return false;
	}

	_hoops_IISCA	data;
	ZERO_STRUCT (&data, _hoops_IISCA);
	data.geometry = geom;
	data.key = _hoops_SHSSR;

	HI_For_Each (_hoops_RIGC, _hoops_SRCP, true, _hoops_SSRSA, (void *)&data);

	if (data.count == 0)
		return false;
	else if (data.count == 1 && out_key)
		*out_key = data.key;

	return true;
}
#endif


HC_INTERFACE Key HC_CDECL HC_Copy_Geometry (
	Key						in_key,
	char const *			_hoops_SRCP)
{
	_hoops_PAPPR context("Copy_Geometry");

#ifdef _hoops_PASCA
	_hoops_IRPPR ("Copy Geometry");
	return _hoops_SHSSR;
#else

	Key		key = _hoops_SHSSR;

	_hoops_RPPPR();
	bool	_hoops_IA = _hoops_GGASA(context, in_key, _hoops_SRCP, &key);
	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Copy_Geometry (LOOKUP(%D),", in_key));
		HI_Dump_Code (Sprintf_S (null, "%S), ", _hoops_SRCP));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", key));
	);

	if (_hoops_IA && key == _hoops_SHSSR) {
		HE_WARNING(HEC_INVALID_KEY, HES_BAD_RETURN_KEY, "Can't return the key - more than one segment was copied");
	}

	return key;
#endif
}


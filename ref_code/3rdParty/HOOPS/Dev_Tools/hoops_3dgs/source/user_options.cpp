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
 * $Id: obf_tmp.txt 1.141 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hpserror.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "adt.h"





/* _hoops_PAGA: _hoops_AGCR _hoops_PIRRR _hoops_CHR _hoops_IIAC _hoops_CGPR _hoops_SRS _hoops_SIGR, _hoops_IGIR _hoops_HRGR _hoops_RHGC, _hoops_HIS _hoops_ICPRGR _hoops_IRS _hoops_PIRA.  _hoops_GHAC _hoops_AAHAR _hoops_SPHR... */
#define _hoops_CCPRGR			 64
#define _hoops_SCPRGR			 64

struct _hoops_GSPRGR {
	Option_Value *		option_list;
	bool				_hoops_RSPRGR;

	long				index;
	void *				value;
	void const *		data;
	long				data_length;
};



#include "utility/huffman.h"

Begin_HOOPS_Namespace

class User_Option_Compressor : public CMO {

public:

	User_Option_Compressor() {

		_hoops_ASPRGR = false;
		_hoops_PSPRGR = false;

		_hoops_HSPRGR = new_huffman_encoder_8();
		_hoops_ISPRGR = new_huffman_encoder_16();
	};

	~User_Option_Compressor() {
		delete_huffman_encoder_8(_hoops_HSPRGR);
		delete_huffman_encoder_16(_hoops_ISPRGR);
	};


	void _hoops_AHSH(_hoops_HCRPR const &name) {
		if (_hoops_PSPRGR == false)
			huffman_add_data_8(_hoops_HSPRGR, name.length, name.text);
	};
	
	void _hoops_AHSH(KName const &name) {
		if (_hoops_ASPRGR == false)
			huffman_add_data_16(_hoops_ISPRGR, name.length, name._hoops_IPPPP);
	};

	void Decode(_hoops_HCRPR const &_hoops_PACSR, _hoops_HCRPR &_hoops_CSPRGR) {
		
		if (_hoops_PACSR.length < 0) {
			int out_n;
			char *out_data;
			ALLOC_ARRAY(out_data, -_hoops_PACSR.length, char);
			huffman_decode_8(_hoops_HSPRGR, -_hoops_PACSR.length, _hoops_PACSR.text, &out_n, out_data); 

			ALLOC_ARRAY(_hoops_CSPRGR.text, out_n+1, char);
			_hoops_CSPRGR.length = out_n;
			_hoops_AIGA(out_data, out_n, char, _hoops_CSPRGR.text);
			_hoops_CSPRGR.text[_hoops_CSPRGR.length] = '\0';

			FREE_ARRAY(out_data, -_hoops_PACSR.length, char);
		}
		else
			HI_Copy_Name(&_hoops_PACSR, &_hoops_CSPRGR);

	};

	void Decode(KName const &_hoops_PACSR, KName &_hoops_CSPRGR) {

		if (_hoops_PACSR.length < 0) {
			int out_n;
			Karacter *out_data;
			ALLOC_ARRAY(out_data, -_hoops_PACSR.length, Karacter);
			huffman_decode_16(_hoops_ISPRGR, -_hoops_PACSR.length, _hoops_PACSR._hoops_IPPPP, &out_n, out_data); 

			ALLOC_ARRAY(_hoops_CSPRGR._hoops_IPPPP, out_n+1, Karacter);
			_hoops_CSPRGR.length = out_n;
			_hoops_AIGA(out_data, out_n, Karacter, _hoops_CSPRGR._hoops_IPPPP);
			_hoops_CSPRGR._hoops_IPPPP[_hoops_CSPRGR.length] = 0x0000;

			FREE_ARRAY(out_data, -_hoops_PACSR.length, Karacter);
		}
		else
			HI_Copy_KName(&_hoops_PACSR, &_hoops_CSPRGR);

	};

	void _hoops_SSPRGR(_hoops_HCRPR &name) {

		if (_hoops_PSPRGR == false) {
			huffman_create_tables_8(_hoops_HSPRGR);
			_hoops_PSPRGR = true;
		}
		
		int out_data_bits;
		char *out_data;
		int _hoops_GGHRGR = name.length;
		ALLOC_ARRAY(out_data, _hoops_GGHRGR, char);

		if (huffman_encode_8(_hoops_HSPRGR, name.length, name.text, &out_data_bits, out_data)) {

			_hoops_RGAIR(name);
			int len = (out_data_bits+7)/8;
			ALLOC_ARRAY(name.text, len, char);
			_hoops_AIGA(out_data, len, char, name.text);
			name.length = -out_data_bits;
		}
	
		FREE_ARRAY(out_data, _hoops_GGHRGR, char);
	}

	void _hoops_SSPRGR(KName &name) {

		if (_hoops_ASPRGR == false) {
			huffman_create_tables_16(_hoops_ISPRGR);
			_hoops_ASPRGR = true;
		}
		
		int out_data_bits;
		Karacter *out_data;
		int _hoops_GGHRGR = name.length;
		ALLOC_ARRAY(out_data, _hoops_GGHRGR, Karacter);

		if (huffman_encode_16(_hoops_ISPRGR, name.length, name._hoops_IPPPP, &out_data_bits, out_data)) {

			_hoops_PRPIR(name);
			int len = (out_data_bits+15)/16;
			ALLOC_ARRAY(name._hoops_IPPPP, len, Karacter);
			_hoops_AIGA(out_data, len, Karacter, name._hoops_IPPPP);
			name.length = -out_data_bits;
		}

		FREE_ARRAY(out_data, _hoops_GGHRGR, Karacter);
	}
	
	void _hoops_RGHRGR(_hoops_HCRPR &name) {

		if (name.length < 0) {
			int out_n;
			char *out_data;
			int _hoops_GGHRGR = -name.length;
			ALLOC_ARRAY(out_data, _hoops_GGHRGR, char);
			huffman_decode_8(_hoops_HSPRGR, -name.length, name.text, &out_n, out_data); 

			_hoops_RGAIR(name);

			ALLOC_ARRAY(name.text, out_n+1, char);
			name.length = out_n;
			_hoops_AIGA(out_data, out_n, char, name.text);
			name.text[name.length] = '\0';

			FREE_ARRAY(out_data, _hoops_GGHRGR, char);
		}
	}

	void _hoops_RGHRGR(KName &name) {

		if (name.length < 0) {
			int out_n;
			Karacter *out_data;
			int _hoops_GGHRGR = -name.length;
			ALLOC_ARRAY(out_data, _hoops_GGHRGR, Karacter);
			huffman_decode_16(_hoops_ISPRGR, -name.length, name._hoops_IPPPP, &out_n, out_data); 

			_hoops_PRPIR(name);

			ALLOC_ARRAY(name._hoops_IPPPP, out_n+1, Karacter);
			name.length = out_n;
			_hoops_AIGA(out_data, out_n, Karacter, name._hoops_IPPPP);
			name._hoops_IPPPP[name.length] = 0x0000;

			FREE_ARRAY(out_data, _hoops_GGHRGR, Karacter);
		}
	}

private:

	huffman_encoder_8_t * _hoops_HSPRGR;
	huffman_encoder_16_t * _hoops_ISPRGR;

	bool _hoops_ASPRGR;
	bool _hoops_PSPRGR;
};
End_HOOPS_Namespace;





#define _hoops_AGHRGR	0
#define _hoops_PGHRGR	1

struct _hoops_HGHRGR {
	User_Option_Compressor * _hoops_IGHRGR;
	User_Option_Compressor * _hoops_CGHRGR;
	int mode;
};


local void _hoops_SGHRGR(
	_hoops_HPPIR * _hoops_IPPIR, 
	_hoops_HGHRGR *pt)
{
	User_Option_Compressor * _hoops_CGRRS = pt->_hoops_IGHRGR;
	User_Option_Compressor * _hoops_SGRRS = pt->_hoops_CGHRGR;
	int mode = pt->mode;

	Option_Value			*option;

	if ((option = _hoops_IPPIR->option_list) != null) do {

		if (!option->_hoops_GCACR && 
			option->_hoops_AIPCR > 0) {

			int	count = 0;
		
			do {

				if (mode == _hoops_AGHRGR) {
					if (_hoops_CGRRS != null) 
						_hoops_CGRRS->_hoops_RGHRGR(option->value._name[count]);
					_hoops_SGRRS->_hoops_AHSH(option->value._name[count]);
				}
				else {
// 					_hoops_RSPHR _hoops_SCSH _hoops_ARHHI=0;
// 					_hoops_ARHHI++;
					_hoops_SGRRS->_hoops_SSPRGR(option->value._name[count]);
// 					_hoops_GRHRGR->_hoops_PGISA(_hoops_HCSP->_hoops_PIRA._hoops_RRHRGR[_hoops_RPR]);
// 					_hoops_GRHRGR->_hoops_GSRA(_hoops_HCSP->_hoops_PIRA._hoops_RRHRGR[_hoops_RPR]);
				}

			} _hoops_RGGA (++count == option->_hoops_AIPCR);
		}

	} _hoops_RGGA ((option = option->next) == null);

	if ((option = _hoops_IPPIR->_hoops_APICA) != null) do {

		if (!option->_hoops_GCACR && 
			option->_hoops_AIPCR > 0) {

			int	count = 0;
		
			do {

				if (mode == _hoops_AGHRGR) {
					if (_hoops_CGRRS != null) 
						_hoops_CGRRS->_hoops_RGHRGR(option->value._hoops_HGSAP[count]);
					_hoops_SGRRS->_hoops_AHSH(option->value._hoops_HGSAP[count]);
				}
				else {
					_hoops_SGRRS->_hoops_SSPRGR(option->value._hoops_HGSAP[count]);
				}

			} _hoops_RGGA (++count == option->_hoops_AIPCR);
		}

	} _hoops_RGGA ((option = option->next) == null);

}

local void HC_CDECL _hoops_ARHRGR (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_CRCP *					_hoops_SRCP,
	void *						info)
{
	_hoops_HGHRGR *pt = (_hoops_HGHRGR*)info;

	_hoops_HPPIR alter	*_hoops_IPPIR = (_hoops_HPPIR*) HI_Find_Attribute(_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP, -HK_USER_OPTIONS);

	UNREFERENCED(_hoops_RIGC);

	if (_hoops_IPPIR != null) {
		_hoops_SGHRGR(_hoops_IPPIR, pt);
		_hoops_HPRH(_hoops_IPPIR);
	}

	if (_hoops_SRCP->geometry != null) {
		Geometry const * geom = _hoops_SRCP->geometry;

		do if (!BIT (geom->_hoops_RRHH, _hoops_HGAGR) && geom->_hoops_IPPGR != null) {

			Attribute *	_hoops_HPHCR = geom->_hoops_IPPGR;

			do {

				if (_hoops_HPHCR->type == HK_USER_OPTIONS) {
					_hoops_SGHRGR((_hoops_HPPIR alter *)_hoops_HPHCR, pt);
					break;
				}

			} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
			
		} while ((geom = geom->next) != null);
	}

}


GLOBAL_FUNCTION void HI_Compress_User_Options(_hoops_AIGPR * _hoops_RIGC)
{
	_hoops_HGHRGR pt;

	_hoops_RPPPR();

	pt._hoops_IGHRGR = HOOPS_WORLD->_hoops_GCHGI;
	pt._hoops_CGHRGR = NEW(User_Option_Compressor)();
	
	pt.mode = _hoops_AGHRGR;
	HI_For_Each (_hoops_RIGC, "/...", true, _hoops_ARHRGR, (void *)&pt);

	pt.mode = _hoops_PGHRGR;
	HI_For_Each (_hoops_RIGC, "/...", true, _hoops_ARHRGR, (void *)&pt);

	if (HOOPS_WORLD->_hoops_GCHGI != null)
		delete HOOPS_WORLD->_hoops_GCHGI;

	HOOPS_WORLD->_hoops_GCHGI = pt._hoops_CGHRGR;

	_hoops_IRRPR();
}


GLOBAL_FUNCTION void HI_Free_User_Options_Compressor()
{
	if (HOOPS_WORLD->_hoops_GCHGI != null)
		delete HOOPS_WORLD->_hoops_GCHGI;
}

GLOBAL_FUNCTION void HI_Decode_User_Option(_hoops_HCRPR const &in, _hoops_HCRPR &_hoops_PAGR)
{

	if (HOOPS_WORLD->_hoops_GCHGI) 
		HOOPS_WORLD->_hoops_GCHGI->Decode(in,_hoops_PAGR);
	else
		HI_Copy_Name(&in, &_hoops_PAGR);

}

GLOBAL_FUNCTION void HI_Decode_Unicode_User_Option(KName const &in, KName &_hoops_PAGR)
{

	if (HOOPS_WORLD->_hoops_GCHGI) 
		HOOPS_WORLD->_hoops_GCHGI->Decode(in,_hoops_PAGR);
	else
		HI_Copy_KName(&in, &_hoops_PAGR);

}

local void _hoops_HHSCA(_hoops_IHSCA * _hoops_CHSCA, POINTER_SIZED_INT index, void const * const _hoops_SHSCA)
{
	_hoops_GISCA * _hoops_RISCA = (_hoops_GISCA *)_hoops_SHSCA;
	_hoops_IHSCA * _hoops_AISCA = NEW(_hoops_IHSCA)(_hoops_CHSCA->data, _hoops_CHSCA->data_length);
	_hoops_RISCA->InsertItem(index, _hoops_AISCA);
}

local Attribute *	_hoops_PRHRGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR) 
{
	_hoops_HPPIR const *	_hoops_GASGH = (_hoops_HPPIR const *)_hoops_CPACR;
	_hoops_HPPIR alter *	_hoops_RASGH = (_hoops_HPPIR alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (item);

	if (HOOPS_WORLD->_hoops_GCHGI) {
		
		if (_hoops_RASGH->option_list != null && 
			_hoops_RASGH->option_list->_hoops_AIPCR > 0) {

			for (int i=0; i<_hoops_RASGH->option_list->_hoops_AIPCR; i++) {
				if (_hoops_RASGH->option_list->value._name)
					HOOPS_WORLD->_hoops_GCHGI->_hoops_SSPRGR(_hoops_RASGH->option_list->value._name[i]);
			}
		}

		if (_hoops_RASGH->_hoops_APICA != null && 
			_hoops_RASGH->_hoops_APICA->_hoops_AIPCR > 0) {

			for (int i=0; i<_hoops_RASGH->_hoops_APICA->_hoops_AIPCR; i++) {
				if (_hoops_RASGH->_hoops_APICA->value._name)
					HOOPS_WORLD->_hoops_GCHGI->_hoops_SSPRGR(_hoops_RASGH->_hoops_APICA->value._hoops_HGSAP[i]);
			}
		}
	}

	if (_hoops_GASGH != null) {

		Option_Value *			option_list = _hoops_RASGH->option_list;
		Option_Value *			_hoops_APICA = _hoops_RASGH->_hoops_APICA;
		_hoops_PGGSA *			_hoops_AGGSA = _hoops_RASGH->_hoops_AGGSA;
		_hoops_GISCA *	_hoops_HGGSA = _hoops_RASGH->_hoops_HGGSA;

		_hoops_RASGH->option_list = null;
		_hoops_RASGH->_hoops_APICA = null;
		_hoops_RASGH->_hoops_AGGSA = null;
		_hoops_RASGH->_hoops_HGGSA = null;

		if (_hoops_GASGH->_hoops_HIHI > 1) {
			// _hoops_IPS
			if (_hoops_GASGH->option_list != null)
				_hoops_RASGH->option_list = HI_Copy_Option_List (_hoops_GASGH->option_list);

			if (_hoops_GASGH->_hoops_APICA != null)
				_hoops_RASGH->_hoops_APICA = HI_Copy_Option_List (_hoops_GASGH->_hoops_APICA);

			if (_hoops_GASGH->_hoops_AGGSA != null && _hoops_GASGH->_hoops_AGGSA->Count() > 0)
				_hoops_RASGH->_hoops_AGGSA = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_PGGSA)(_hoops_GASGH->_hoops_AGGSA);

			if (_hoops_GASGH->_hoops_HGGSA != null && _hoops_GASGH->_hoops_HGGSA->Count() > 0) {
				_hoops_RASGH->_hoops_HGGSA = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_GISCA)(HOOPS_WORLD->memory_pool, _hoops_GASGH->_hoops_HGGSA->TableSize());
				_hoops_GASGH->_hoops_HGGSA->MapFunction(_hoops_HHSCA, (void*)_hoops_RASGH->_hoops_HGGSA);
			}
		}
		else {
			// _hoops_SRAI
			_hoops_RASGH->option_list = _hoops_GASGH->option_list;
			_hoops_RASGH->_hoops_APICA = _hoops_GASGH->_hoops_APICA;
			_hoops_RASGH->_hoops_AGGSA = _hoops_GASGH->_hoops_AGGSA;
			_hoops_RASGH->_hoops_HGGSA = _hoops_GASGH->_hoops_HGGSA;

			_hoops_PGRCA(_hoops_GASGH)->option_list = null;
			_hoops_PGRCA(_hoops_GASGH)->_hoops_APICA = null;
			_hoops_PGRCA(_hoops_GASGH)->_hoops_AGGSA = null;
			_hoops_PGRCA(_hoops_GASGH)->_hoops_HGGSA = null;
		}

		if (_hoops_RASGH->option_list == null)
			_hoops_RASGH->option_list = option_list;
		else if (option_list) {

			Option_Value **	_hoops_CIGHH = &_hoops_RASGH->option_list, *_hoops_GCGHH, *_hoops_HRHRGR;
			
			_hoops_GCGHH = option_list;

			do {
				Option_Value *	_hoops_IRHRGR = _hoops_GCGHH->next;
				_hoops_GCGHH->next = null;	/* _hoops_GHHR _hoops_SCH */

				_hoops_RGGA ((_hoops_HRHRGR = *_hoops_CIGHH) == null ||
					_hoops_HRHRGR->type->id >= _hoops_GCGHH->type->id)
					_hoops_CIGHH = &_hoops_HRHRGR->next;

				/*_hoops_SGH _hoops_RGR */
				*_hoops_CIGHH = _hoops_GCGHH;

				if (_hoops_HRHRGR == null ||
					_hoops_HRHRGR->type->id > _hoops_GCGHH->type->id) {
						(*_hoops_CIGHH)->next = _hoops_HRHRGR;
				}
				else {	/* _hoops_PIHA _hoops_SHH _hoops_SASPR, _hoops_HASIR _hoops_GIGR */
					(*_hoops_CIGHH)->next = _hoops_HRHRGR->next;
					_hoops_HRHRGR->next = null;
					HI_Free_Option_List (_hoops_RIGC, _hoops_HRHRGR);
				}

				_hoops_GCGHH = _hoops_IRHRGR;

			} while (_hoops_GCGHH != null);
		}

		if (_hoops_RASGH->_hoops_APICA == null)
			_hoops_RASGH->_hoops_APICA = _hoops_APICA;
		else if (_hoops_APICA) {

			Option_Value **	_hoops_CIGHH = &_hoops_RASGH->_hoops_APICA, *_hoops_GCGHH, *_hoops_HRHRGR;
			
			_hoops_GCGHH = _hoops_APICA;

			do {
				Option_Value *	_hoops_IRHRGR = _hoops_GCGHH->next;
				_hoops_GCGHH->next = null;	/* _hoops_GHHR _hoops_SCH */

				_hoops_RGGA ((_hoops_HRHRGR = *_hoops_CIGHH) == null ||
					_hoops_HRHRGR->type->id >= _hoops_GCGHH->type->id)
					_hoops_CIGHH = &_hoops_HRHRGR->next;

				/*_hoops_SGH _hoops_RGR */
				*_hoops_CIGHH = _hoops_GCGHH;

				if (_hoops_HRHRGR == null ||
					_hoops_HRHRGR->type->id > _hoops_GCGHH->type->id) {
					(*_hoops_CIGHH)->next = _hoops_HRHRGR;
				}
				else {	/* _hoops_PIHA _hoops_SHH _hoops_SASPR, _hoops_HASIR _hoops_GIGR */
					(*_hoops_CIGHH)->next = _hoops_HRHRGR->next;
					_hoops_HRHRGR->next = null;
					HI_Free_Option_List (_hoops_RIGC, _hoops_HRHRGR);
				}

				_hoops_GCGHH = _hoops_IRHRGR;

			} while (_hoops_GCGHH != null);
		}

		if (_hoops_RASGH->_hoops_AGGSA == null)
			_hoops_RASGH->_hoops_AGGSA = _hoops_AGGSA;
		else if (_hoops_AGGSA && _hoops_AGGSA->Count() > 0) {
			_hoops_RASGH->_hoops_AGGSA->Merge(_hoops_AGGSA, VHASH_MERGE_REPLACE_DUPLICATES);
			delete _hoops_AGGSA;
		}

		if (_hoops_RASGH->_hoops_HGGSA == null)
			_hoops_RASGH->_hoops_HGGSA = _hoops_HGGSA;
		else {
			if (_hoops_HGGSA && _hoops_HGGSA->Count() > 0) {
				_hoops_GISCA::PairList * _hoops_ARIRI = _hoops_HGGSA->GetPairList();
				_hoops_ARIRI->ResetCursor();
				_hoops_GISCA::Pair * p;
				while((p = _hoops_ARIRI->PeekCursor()) != 0){
					_hoops_IHSCA * _hoops_CRHRGR = null;
					_hoops_IHSCA * _hoops_CHSCA = null;
					_hoops_HGGSA->RemoveItem(p->Key(), &_hoops_CRHRGR);
					_hoops_RASGH->_hoops_HGGSA->ReplaceItem(p->Key(), _hoops_CRHRGR, &_hoops_CHSCA);
					if (_hoops_CHSCA)
						delete _hoops_CHSCA;
					_hoops_ARIRI->AdvanceCursor();
				}
				delete _hoops_ARIRI;
			}
			delete _hoops_HGGSA;
		}
		
	}

	return _hoops_RASGH;
}


GLOBAL_FUNCTION bool HI_Set_User_Options (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_HPPIR *			user_options)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_USER_OPTIONS, _hoops_PRHRGR, user_options);
}

local void _hoops_SRHRGR(_hoops_IHSCA * _hoops_CHSCA, POINTER_SIZED_INT index, void const * const _hoops_SHSCA)
{
	UNREFERENCED(index);
	UNREFERENCED(_hoops_SHSCA);
	delete _hoops_CHSCA;
}

GLOBAL_FUNCTION void HI_Free_User_Option (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPPIR *			user_options)
{
	if (user_options->option_list)
		HI_Free_Option_List (_hoops_RIGC, user_options->option_list);

	if (user_options->_hoops_APICA)
		HI_Free_Option_List (_hoops_RIGC, user_options->_hoops_APICA);

	if (user_options->_hoops_AGGSA)
		delete user_options->_hoops_AGGSA;

	if (user_options->_hoops_HGGSA) {
		user_options->_hoops_HGGSA->MapFunction(_hoops_SRHRGR);
		delete user_options->_hoops_HGGSA;
	}

	if (user_options->_hoops_IGGSA) {
		_hoops_HPPIR const * _hoops_HGSGP;
		while ((_hoops_HGSGP = user_options->_hoops_IGGSA->RemoveFirst()) != null)
			_hoops_HPRH(_hoops_HGSGP);
		delete user_options->_hoops_IGGSA;
	}

	FREE (user_options, _hoops_HPPIR);
}


local void _hoops_CSACA (void) {
	_hoops_PIIIR	**_hoops_SSACA;

	ZALLOC_ARRAY (_hoops_SSACA, _hoops_CCPRGR, _hoops_PIIIR *);
	_hoops_CIACR (_hoops_SAPPP)->table = _hoops_SSACA;
	_hoops_CIACR (_hoops_SAPPP)->size = _hoops_CCPRGR;
}

local void _hoops_GAHRGR (void) {
	_hoops_RPSAP **_hoops_SSACA;

	ZALLOC_ARRAY (_hoops_SSACA, _hoops_SCPRGR, _hoops_RPSAP *);
	_hoops_CIACR (_hoops_CPPPP)->table = (_hoops_PIIIR **)_hoops_SSACA;
	_hoops_CIACR (_hoops_CPPPP)->size = _hoops_SCPRGR;
}


local void _hoops_RAHRGR (
	_hoops_AIGPR *	_hoops_RIGC,
	Option_Value **			_hoops_PPRHA) 
{
	Option_Value **	_hoops_AAHRGR;
	Option_Value *	_hoops_RSGHR;
	Option_Value *	_hoops_ACCAA;
	Option_Value **	_hoops_PAHRGR;
	Option_Value *	_hoops_RASGH = null;

	/* _hoops_SAHR _hoops_AA _hoops_IRS _hoops_CHCII-_hoops_GHIS: _hoops_SSS _hoops_RH _hoops_SARPA _hoops_IIGR _hoops_RH _hoops_HHRPA,
	 * _hoops_PPR _hoops_IHIS _hoops_SCH _hoops_IAPR _hoops_IS _hoops_RH _hoops_RIPS _hoops_IIGR _hoops_IRS _hoops_HASGH _hoops_HIGR.
	 * (_hoops_GSCHI _hoops_IGAPA _hoops_GAR _hoops_SR _hoops_AA _hoops_SCH)
	 */

	while (_hoops_PAHRGR = _hoops_PPRHA, (_hoops_ACCAA = *_hoops_PAHRGR) != null) {
		_hoops_AAHRGR = &_hoops_ACCAA->next;
		_hoops_RGGA ((_hoops_RSGHR = *_hoops_AAHRGR) == null) {
			/* ("<=" _hoops_HRII _hoops_HSAR "<" _hoops_IS _hoops_IGHAR _hoops_IGAPA _hoops_RH _hoops_RPHR _hoops_PPRRR) */
			if (_hoops_ACCAA->type->id <= _hoops_RSGHR->type->id) {
				_hoops_PAHRGR = _hoops_AAHRGR;
				_hoops_ACCAA = _hoops_RSGHR;
			}
			_hoops_AAHRGR = &_hoops_RSGHR->next;
		}

		*_hoops_PAHRGR = _hoops_ACCAA->next;	/* _hoops_CAHHH _hoops_SCH _hoops_GGSR _hoops_IIGR _hoops_RH _hoops_RHGS _hoops_HIGR */

		if (_hoops_RASGH != null && _hoops_ACCAA->type->id == _hoops_RASGH->type->id) {
			_hoops_ACCAA->next = null;					/* _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_SSRS */
			HI_Free_Option_List (_hoops_RIGC, _hoops_ACCAA);			/* _hoops_PCHIA! _hoops_PCHIA! */
		}
		else {					/* _hoops_PPSI _hoops_SCH _hoops_GPP _hoops_RH _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_HASGH _hoops_HIGR */
			_hoops_ACCAA->next = _hoops_RASGH;
			_hoops_RASGH = _hoops_ACCAA;
		}
	}
	*_hoops_PPRHA = _hoops_RASGH;
}





HC_INTERFACE void HC_CDECL HC_Set_User_Options (
	char const *				options) 
{
	_hoops_PAPPR context("Set_User_Options");

	CODE_GENERATION (
		int count = _hoops_SSGR(options) + 1;
		if (count) {
			HI_Dump_Code (H_FORMAT_TEXT("/* %s */\n", H_UTF8(options).encodedText()));
			HI_Dump_Code ("{\n");
			++HOOPS_WORLD->_hoops_ISPPR;
			HI_Dump_Code (Sprintf_LD (null, "char * data = (char*) malloc(sizeof(char)*%D);\n", count));
			while (count-- != 0)
				HI_Dump_Code (H_FORMAT_TEXT("data[%d] = 0x%x;\n", count, options[count]));
			HI_Dump_Code ("HC_Set_User_Options (data);\n");
			HI_Dump_Code ("free (data);\n");
			--HOOPS_WORLD->_hoops_ISPPR;
			HI_Dump_Code ("}\n");
		} else {
			HI_Dump_Code ("/*  */\nHC_Set_User_Options (\"\");\n");
		}
	);

	if (_hoops_CIACR (_hoops_SAPPP)->table == null) 
		_hoops_CSACA();

	bool			used = false;
	_hoops_HPPIR *	user_options;
	ZALLOC (user_options, _hoops_HPPIR);

	Option_Value *	option_list;

	if (HI_Parse_Options (context, options,_hoops_CIACR (_hoops_SAPPP), &option_list, _hoops_SIACR)) {

		user_options->option_list = HI_Copy_Option_List (option_list);
		HI_Free_Option_List (context, option_list);

		_hoops_RAHRGR (context, &user_options->option_list);

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_IHRPP)) != null) {
			used = HI_Set_User_Options (context, target, user_options);
			_hoops_IRRPR();
		}
	}

	if (!used) 
		HI_Free_User_Option(context, user_options);

}


HC_INTERFACE void HC_CDECL HC_UnSet_User_Options (void) 
{
	_hoops_PAPPR context("UnSet_User_Options");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_User_Options ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_IHRPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute (context, target, HK_USER_OPTIONS);
		_hoops_IRRPR();
	}
}




HC_INTERFACE void HC_CDECL HC_Set_Unicode_Options (
	Karacter const *			options) 
{
	_hoops_PAPPR context("Set_Unicode_Options");

#ifdef DISABLE_UNICODE_OPTIONS
	_hoops_IRPPR ("Unicode_Options");
#else
	CODE_GENERATION (
        H_UTF16 _hoops_RSPPH;
        _hoops_RSPPH.encodedText((utf16_char const*)options);
		int count = (int)_hoops_RSPPH.length() + 1;
		unsigned short * _hoops_HAHRGR = (unsigned short *)options;
		HI_Dump_Code (H_FORMAT_TEXT("/* %s */", H_UTF8(_hoops_RSPPH).encodedText()));
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (H_FORMAT_TEXT("unsigned short * data = (unsigned short*) malloc(sizeof(unsigned short)*%d);\n", count));
		while (count-- != 0)
			HI_Dump_Code (H_FORMAT_TEXT("data[%d] = 0x%x;\n", count, _hoops_HAHRGR[count]));
		HI_Dump_Code ("HC_Set_Unicode_Options (data);\n");
		HI_Dump_Code ("free (data);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	if (_hoops_CIACR (_hoops_CPPPP)->table == null) 
		_hoops_GAHRGR();

	bool			used = false;
	_hoops_HPPIR *	user_options;
	ZALLOC (user_options, _hoops_HPPIR);
	Option_Value *	_hoops_APICA;

	if (HI_Parse_KOptions (context, options, _hoops_CIACR (_hoops_CPPPP), &_hoops_APICA, _hoops_SIACR)) {

		user_options->_hoops_APICA = HI_Copy_Option_List (_hoops_APICA);
		HI_Free_Option_List (context, _hoops_APICA);

		_hoops_RAHRGR (context, &user_options->_hoops_APICA);

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_IHRPP)) != null) {
			used = HI_Set_User_Options (context, target, user_options);
			_hoops_IRRPR();
		}
	}

	if (!used) 
		HI_Free_User_Option(context, user_options);

#endif
}


HC_INTERFACE void HC_CDECL HC_UnSet_Unicode_Options (void) 
{
	_hoops_PAPPR context("UnSet_Unicode_Options");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Unicode_Options ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_IHRPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute (context, target, HK_USER_OPTIONS);
		_hoops_IRRPR();
	}
}


HC_INTERFACE void HC_CDECL HC_Set_User_Index (
	long						index,
	void const *				value) 
{
	_hoops_PAPPR context("Set_User_Index");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Set_User_Index (%D, ", index));
		HI_Dump_Code (Sprintf_LD (null, "(void *)(HC_POINTER_SIZED_INT)(%D));\n", value));
	);

	bool			used = false;
	_hoops_HPPIR *	user_options;
	ZALLOC (user_options, _hoops_HPPIR);

	user_options->_hoops_AGGSA = POOL_NEW(context->memory_pool, _hoops_PGGSA)(context->memory_pool, 2);
	user_options->_hoops_AGGSA->InsertItem(index, (void *) value);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_IHRPP)) != null) {
		used = HI_Set_User_Options (context, target, user_options);
		_hoops_IRRPR();
	}

	if (!used) 
		HI_Free_User_Option(context, user_options);

}



/* _hoops_PAGA _hoops_RSIRR _hoops_IAHRGR _hoops_GPP _hoops_AGRR _hoops_CAHRGR _hoops_ASRSA:
 *	_hoops_CRPGH[_hoops_GRI]  _hoops_IS  _hoops_SAHRGR	 _hoops_GPP _hoops_HCR _hoops_GPHRGR
 *	_hoops_GISHR	   _hoops_IS  _hoops_RPHRGR	 _hoops_GPP _hoops_HCR _hoops_APHRGR
 *	_hoops_CPAGI	   _hoops_IS  _hoops_PPHRGR	 _hoops_GPP _hoops_HCR _hoops_HPHRGR[_hoops_RHRRS]_hoops_CPAGI
 */



#ifndef DISABLE_SHOW


local char * _hoops_IPHRGR (
	char		*_hoops_ASAPR,
	char		*_hoops_PSAPR,
	char const	*string) {

	if (_hoops_ASAPR == null || _hoops_ASAPR == _hoops_PSAPR)
		return null;

	while (*string) {
		*_hoops_ASAPR++ = *string++;

		if (_hoops_ASAPR == _hoops_PSAPR)
			return null;
	}

	return _hoops_ASAPR;
}


local Karacter * _hoops_CPHRGR (
	Karacter		*_hoops_ASAPR,
	Karacter		*_hoops_PSAPR,
	char const		*string) {

	if (_hoops_ASAPR == null || _hoops_ASAPR == _hoops_PSAPR)
		return null;

	while (*string) {
		*_hoops_ASAPR++ = (Karacter)*string++;

		if (_hoops_ASAPR == _hoops_PSAPR)
			return null;
	}

	return _hoops_ASAPR;
}



local char * _hoops_CSCGS (
	char		*_hoops_ASAPR,
	char		*_hoops_PSAPR,
	_hoops_HCRPR const	*name) {
	int				length = name->length;
	char const *_hoops_RPPA = name->text;

	if (_hoops_ASAPR == null || _hoops_ASAPR == _hoops_PSAPR)
		return null;

	while (length-- > 0) {
		*_hoops_ASAPR++ = *_hoops_RPPA++;

		if (_hoops_ASAPR == _hoops_PSAPR)
			return null;
	}

	return _hoops_ASAPR;
}


local Karacter * _hoops_SPHRGR (
	Karacter		*_hoops_ASAPR,
	Karacter		*_hoops_PSAPR,
	KName const	*_hoops_SIHSA) {
	int				length = _hoops_SIHSA->length;
	Karacter const *_hoops_IHSCP = _hoops_SIHSA->_hoops_IPPPP;

	if (_hoops_ASAPR == null || _hoops_ASAPR == _hoops_PSAPR)
		return null;

	while (length-- > 0) {
		*_hoops_ASAPR++ = *_hoops_IHSCP++;

		if (_hoops_ASAPR == _hoops_PSAPR)
			return null;
	}

	return _hoops_ASAPR;
}

/* _hoops_SGSS _hoops_RIRRR _hoops_HII _hoops_GHHRGR */
/* _hoops_CGIC _hoops_RPP _hoops_IRS _hoops_RSIRR _hoops_SSCP _hoops_GII _hoops_GRH _hoops_HPS _hoops_PAR _hoops_GHGPR _hoops_HGS _hoops_SGS _hoops_CHH _hoops_SHH 
 * _hoops_CISS _hoops_RPP _hoops_SR _hoops_SARS'_hoops_RA _hoops_GGCR _hoops_CPARA.  (_hoops_SAIHS _hoops_HII _hoops_CPRAA _hoops_CPARA _hoops_IS _hoops_AIAH _hoops_RSIGI _hoops_RHIPP, _hoops_PHRI */
local bool _hoops_GPIHS (
	_hoops_HCRPR const	*name,
	bool		_hoops_RPIHS) 
{
	char			*string = name->text;
	int				count = name->length;
	char			_hoops_PPARA = 0;

	if (count != 0) do {
		if ('a' <= *string && *string <= 'z') {}
		else if ('0' <= *string && *string <= '9') {}
		else switch (*string) {
			case ' ':
				if (string[1] == ' ' && !_hoops_PPARA)
					return true;
			
			case '#':	 case '+':	  case '-':
			case '$':	 case '_':	  case '.':
				break;

			/* _hoops_HPS _hoops_SGS _hoops_CHR _hoops_PHRH _hoops_GGR _hoops_CRAA _hoops_RPPCR, _hoops_HIH _hoops_HAR _hoops_GGGGR */
			case ':':
				if (_hoops_RPIHS)
					break;

			case '\'': case '"': case '`':
				if (_hoops_PPARA) {
					if (*string == _hoops_PPARA)
						if (string[1] == _hoops_PPARA)
							/* _hoops_SRIII _hoops_RH _hoops_CISI _hoops_HPARA _hoops_IAHA _hoops_RIRPR _hoops_GAR _hoops_PCCP _hoops_PGPCR 
							 * _hoops_ICPPR _hoops_IS _hoops_SHH _hoops_PPIHS _hoops_GAR _hoops_IRS _hoops_RSRA _hoops_HAGAR. (_hoops_IAS._hoops_ISHI.
							 * "_hoops_HPIHS'_hoops_GRI _hoops_GSSP" _hoops_PAH _hoops_GACC _hoops_SHH _hoops_AIHCR _hoops_GAR '_hoops_HPIHS''_hoops_GRI _hoops_GSSP') */
							++string;
						else
							_hoops_PPARA = 0;
				}
				else
					_hoops_PPARA = *string;
				break;
			default:
				/* _hoops_AHGHS _hoops_IPIHS _hoops_HIRCC _hoops_AAGPH, _hoops_PGAP _hoops_RRP _hoops_CPIHS _hoops_HPP _hoops_CPARA _hoops_PPR
				 * _hoops_CGH _hoops_PRGPR _hoops_SHH _hoops_GHSAR "_hoops_GRH" */
				if (!_hoops_PPARA)
					return true;
		}

		++string;
	} _hoops_RGGA (--count == 0);

	if (_hoops_PPARA)
		return true; /* _hoops_PARRA _hoops_CPARA (_hoops_IAS._hoops_ISHI. _hoops_HPIHS'_hoops_GRI _hoops_GSSP) */

	return	false;
}


local void _hoops_RHHRGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPPIR const *	_hoops_AHHRGR,
	char *					options,
	int						_hoops_HGPCA) 
{
	local const char		_hoops_SSACR[] = "Return string won't fit in provided space";
	_hoops_HPPIR const *	user_options;
	Option_Value *			_hoops_CSCIR;

	if (_hoops_AHHRGR->_hoops_IGGSA)
		user_options = HI_Distill_User_Options(_hoops_RIGC, _hoops_AHHRGR, _hoops_CIIAP);
	else
		user_options = _hoops_AHHRGR;

	if ((_hoops_CSCIR = user_options->option_list) == null)
		HI_Return_Chars (options, _hoops_HGPCA, "", 0);
	else {
		char			*_hoops_ASAPR = options;
		char			*_hoops_PSAPR;

		if (_hoops_HGPCA == -1)
			_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR;	/* _hoops_IHRPR _hoops_IAHA */
		else
			_hoops_PSAPR = _hoops_ASAPR + _hoops_HGPCA;				/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */

		_hoops_PCCAR {
			int				_hoops_RHSAA;

			if (_hoops_CSCIR->type->_hoops_RCIIR != _hoops_HRSAP)
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected option type");
			else if (_hoops_CSCIR->_hoops_GCACR) {
				_hoops_ASAPR = _hoops_IPHRGR (_hoops_ASAPR, _hoops_PSAPR, "no ");
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn", &_hoops_CSCIR->type->name);
			}
			else if ((_hoops_RHSAA = _hoops_CSCIR->_hoops_AIPCR) == 0) {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn", &_hoops_CSCIR->type->name);
			}
			else if (_hoops_RHSAA == 1) {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn", &_hoops_CSCIR->type->name);
				_hoops_ASAPR = _hoops_IPHRGR (_hoops_ASAPR, _hoops_PSAPR, "=");
				_hoops_HCRPR _hoops_CPSGI;
				HI_Decode_User_Option(_hoops_CSCIR->value._name[0],_hoops_CPSGI);
				_hoops_ASAPR = _hoops_CSCGS (_hoops_ASAPR, _hoops_PSAPR, &_hoops_CPSGI);
				_hoops_RGAIR(_hoops_CPSGI);
			}
			else {
				int		count = 0;

				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn", &_hoops_CSCIR->type->name);
				_hoops_ASAPR = _hoops_IPHRGR (_hoops_ASAPR, _hoops_PSAPR, "=(");

				do {
					_hoops_HCRPR _hoops_CPSGI;
					HI_Decode_User_Option(_hoops_CSCIR->value._name[count],_hoops_CPSGI);
					_hoops_ASAPR = _hoops_CSCGS (_hoops_ASAPR, _hoops_PSAPR, &_hoops_CSCIR->value._name[count]);
					_hoops_RGAIR(_hoops_CPSGI);
					_hoops_ASAPR = _hoops_IPHRGR (_hoops_ASAPR, _hoops_PSAPR, ",");
					if (_hoops_ASAPR == null) break;
				} _hoops_RGGA (++count == _hoops_RHSAA);

				if (_hoops_ASAPR != null)
					_hoops_ASAPR[-1] = ')';		/* _hoops_AGRP _hoops_CGHI _hoops_RRCIR _hoops_IS ')' */
			}


			if ((_hoops_CSCIR = _hoops_CSCIR->next) == null) break;

			if (_hoops_ASAPR == _hoops_PSAPR) _hoops_ASAPR = null; /* _hoops_PGPCR _hoops_RPP _hoops_PSP _hoops_RSIAR _hoops_IH ',' */
			if (_hoops_ASAPR == null) break;	  /* _hoops_PAR _hoops_RPP _hoops_AIAH _hoops_GGSR _hoops_IIGR _hoops_RSIAR */
			*_hoops_ASAPR++ = ',';		/* _hoops_GGCR ',' _hoops_GAPA _hoops_APSAR */
		}

		if (_hoops_ASAPR == null) {
			HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_SSACR);
			goto _hoops_RCCSR;
		}

		/* _hoops_GHHR _hoops_PRRP */
		if (_hoops_HGPCA == -1) {
			if (_hoops_ASAPR == _hoops_PSAPR) {
				HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_SSACR);
				goto _hoops_RCCSR;
			}
			*_hoops_ASAPR = '\0';							/* _hoops_IHRPR _hoops_IAHA */
		}
		else {
			_hoops_RGGA (_hoops_ASAPR == _hoops_PSAPR) *_hoops_ASAPR++ = ' ';		/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */
		}
	}

_hoops_RCCSR:

	if (_hoops_AHHRGR != user_options)
		_hoops_HPRH(user_options);

}

local int _hoops_PHHRGR (
	_hoops_HCRPR const *			name) {
	char const *			_hoops_RPPA = name->text;
	int						count = 0;

	if (name->length > 0 && _hoops_GPIHS (name, false)) {
		count = 2;			/* _hoops_HSPP & _hoops_RSGR */

		do if (*_hoops_RPPA == '`')
			++count;		/* _hoops_SRIII _hoops_GH _hoops_GRR _hoops_SGCRP _hoops_HHHRGR */
		while (*++_hoops_RPPA != '\0');
	}

	return count;
}

local void _hoops_IHHRGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPPIR const *		_hoops_AHHRGR,
	int *						length) 
{
	_hoops_HPPIR const *		user_options;
	Option_Value *				_hoops_CSCIR;

	*length = 0;

	if (_hoops_AHHRGR->_hoops_IGGSA)
		user_options = HI_Distill_User_Options(_hoops_RIGC, _hoops_AHHRGR, _hoops_CIIAP);
	else
		user_options = _hoops_AHHRGR;

	if ((_hoops_CSCIR = user_options->option_list) != null) _hoops_PCCAR {
		int				_hoops_RHSAA;

		if (_hoops_CSCIR->type->_hoops_RCIIR != _hoops_HRSAP)
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected option type");
		else if (_hoops_CSCIR->_hoops_GCACR) {
			*length += 3 + _hoops_CSCIR->type->name.length;		/* "_hoops_PSP %_hoops_ACHP" */
			*length += _hoops_PHHRGR (&_hoops_CSCIR->type->name);
		}
		else if ((_hoops_RHSAA = _hoops_CSCIR->_hoops_AIPCR) == 0) {
			*length += _hoops_CSCIR->type->name.length;			/* "%_hoops_ACHP" */
			*length += _hoops_PHHRGR (&_hoops_CSCIR->type->name);
		}
		else if (_hoops_RHSAA == 1) {					/* "%_hoops_ACHP=%_hoops_ACHP" */
			_hoops_HCRPR _hoops_CPSGI;
			HI_Decode_User_Option(_hoops_CSCIR->value._name[0], _hoops_CPSGI);
			*length += _hoops_CSCIR->type->name.length + 1 + _hoops_CPSGI.length;
			*length += _hoops_PHHRGR (&_hoops_CSCIR->type->name);
			*length += _hoops_PHHRGR (&_hoops_CPSGI);
			_hoops_RGAIR(_hoops_CPSGI);
		}
		else {
			int		count = 0;

			*length += _hoops_CSCIR->type->name.length + 2;		/* "%_hoops_ACHP=" */
			*length += _hoops_PHHRGR (&_hoops_CSCIR->type->name);

			do {
				_hoops_HCRPR _hoops_CPSGI;
				HI_Decode_User_Option(_hoops_CSCIR->value._name[count], _hoops_CPSGI);
				*length += _hoops_CPSGI.length + 1;	/* "%_hoops_ACHP," */
				*length += _hoops_PHHRGR (&_hoops_CPSGI);
				_hoops_RGAIR(_hoops_CPSGI);
			} _hoops_RGGA (++count == _hoops_RHSAA);
			/* _hoops_AGRP _hoops_HACH ',' _hoops_IS ')' -- _hoops_PSP _hoops_SPCC _hoops_AGRP */
		}

		if ((_hoops_CSCIR = _hoops_CSCIR->next) == null) break;

		*length += 1;			/* "," _hoops_GAPA _hoops_APSAR */
	}

//_hoops_IIARR:

	if (_hoops_AHHRGR != user_options)
		_hoops_HPRH(user_options);

}


local bool _hoops_CHHRGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPPIR const *	_hoops_AHHRGR,
	bool					_hoops_PSACR,
	_hoops_CRCP const *			owner,
	char const *			uoname,
	char *					list,
	int						_hoops_GGCIR) 
{
	char const *			_hoops_SHHRGR = uoname;
	_hoops_HCRPR					_hoops_IPPIR;
	_hoops_HPPIR const *	user_options;
	Option_Value *			option = null;
	bool					result = true;
	
	if (_hoops_AHHRGR->_hoops_IGGSA)
		user_options = HI_Distill_User_Options(_hoops_RIGC, _hoops_AHHRGR, _hoops_CIIAP);
	else
		user_options = _hoops_AHHRGR;

	char const *	_hoops_SSACR;
	if ((_hoops_SSACR = HI_Scan_Name (_hoops_RIGC, &_hoops_SHHRGR, null, &_hoops_IPPIR)) != null) {
		HE_ERROR (HEC_USER_OPTIONS, HES_PARSE_STRING,
			Sprintf_SS (null, "Can't scan '%s' - %s", _hoops_SHHRGR, _hoops_SSACR));
		HI_Return_Chars (list, _hoops_GGCIR, "", 0);
		result = false;
		goto _hoops_RCCSR;
	}

	if ((option = user_options->option_list) != null) do {
		if (_hoops_RAHSR (_hoops_IPPIR, option->type->name)) {
			if (option->_hoops_GCACR)
				HI_Return_Chars (list, _hoops_GGCIR, "off", 3);
			else if (option->_hoops_AIPCR == 0)
				HI_Return_Chars (list, _hoops_GGCIR, "on", 2);
			else if (option->_hoops_AIPCR == 1) {
				_hoops_HCRPR tmp;
				HI_Decode_User_Option(option->value._name[0], tmp);
				HI_Return_Chars (list, _hoops_GGCIR, tmp.text, tmp.length);
				_hoops_RGAIR(tmp);
			}
			else {
				char	*_hoops_ASAPR = list;
				char	*_hoops_PSAPR;
				int		count = 0;

				if (_hoops_GGCIR == -1)
					_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR;	/* _hoops_IHRPR _hoops_IAHA */
				else
					_hoops_PSAPR = _hoops_ASAPR + _hoops_GGCIR;			/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */

				do {
					_hoops_HCRPR _hoops_CPSGI;
					HI_Decode_User_Option(option->value._name[count], _hoops_CPSGI);
					_hoops_ASAPR = _hoops_CSCGS (_hoops_ASAPR, _hoops_PSAPR, &_hoops_CPSGI);
					_hoops_RGAIR(_hoops_CPSGI);
				} _hoops_RGGA (++count == option->_hoops_AIPCR);

				if (_hoops_ASAPR == null) 
					break;

				_hoops_ASAPR[-1] = ')';	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
			}
			_hoops_RGAIR (_hoops_IPPIR);
			goto _hoops_RCCSR;
		}
	} _hoops_RGGA ((option = option->next) == null);

	if (option == null)
		result = false;

	if (!_hoops_PSACR) {
		HE_ERROR (HEC_USER_OPTIONS, HES_NO_LOCAL_SETTING, 
			Sprintf_SP (null, "'%s' has no local setting in '%p'", uoname, owner));
	}

	_hoops_RGAIR (_hoops_IPPIR);

	HI_Return_Chars (list, _hoops_GGCIR, "", 0);

_hoops_RCCSR:

	if (_hoops_AHHRGR != user_options)
		_hoops_HPRH(user_options);
	
	return result;
}
#endif



HC_INTERFACE void HC_CDECL HC_Show_User_Options (
	char *					options) 
{
	_hoops_PAPPR context("Show_User_Options");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_User_Options () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PGAPP)) != null) {

		_hoops_HPPIR *	user_options;
		if ((user_options = (_hoops_HPPIR *)HI_Find_Attribute (context, target, HK_USER_OPTIONS)) != null) {
			_hoops_RHHRGR (context, user_options, options, -1);
			_hoops_HPRH (user_options);
		}
		_hoops_IRRPR();
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_User_Options_Length (
	int *					length) 
{
	_hoops_PAPPR context("Show_User_Options_Length");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_User_Options_Length () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PGAPP)) != null) {

		_hoops_HPPIR *	user_options;
		if ((user_options = (_hoops_HPPIR *)HI_Find_Attribute (context, target, HK_USER_OPTIONS)) != null) {
			_hoops_IHHRGR (context, user_options, length);
			_hoops_HPRH (user_options);
		}
		_hoops_IRRPR();
	}
#endif
}


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_User_Options (
	int					count,
	Key const *			keys,
	char *				options) 
{
	_hoops_PAPPR context("PShow_Net_User_Options");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_User_Options () */\n");
	);

	_hoops_HPPIR *	user_options;
	if ((user_options = (_hoops_HPPIR *) HI_Find_Attribute_And_Lock(context, _hoops_PGAPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_RHHRGR (context, user_options, options, -1);
		_hoops_HPRH (user_options);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(options, -1, "", 0);

#endif
}
#endif


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_User_Opt_Length (
	int					count,
	Key const *			keys,
	int *				length)
{
	_hoops_PAPPR context("PShow_Net_User_Opt_Length");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_User_Opt_Length () */\n");
	);

	*length = 0;

	_hoops_HPPIR *	user_options;
	if ((user_options = (_hoops_HPPIR *) HI_Find_Attribute_And_Lock(context, _hoops_PGAPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_IHHRGR (context, user_options, length);
		_hoops_HPRH (user_options);
		_hoops_IRRPR();
	}
	
#endif
}
#endif


HC_INTERFACE void HC_CDECL HC_Show_One_User_Option (
	char const *			uoname,
	char *					options) 
{
	_hoops_PAPPR context("Show_One_User_Option");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_User_Option () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PGAPP)) != null) {

		_hoops_HPPIR *	user_options;
		if ((user_options = (_hoops_HPPIR *)HI_Find_Attribute (context, target, HK_USER_OPTIONS)) != null) {
			_hoops_CHHRGR (context, user_options, false, user_options->owner, uoname, options, -1);
			_hoops_HPRH (user_options);
		}
		_hoops_IRRPR();
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_One_User_Option_Length (
	char const *		uoname,
	int *				length) 
{
	_hoops_PAPPR context("Show_One_User_Option_Length");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_User_Option_Length () */\n");
	);

	*length = 0;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PGAPP)) != null) {

		_hoops_HPPIR *	user_options;
		if ((user_options = (_hoops_HPPIR *)HI_Find_Attribute (context, target, HK_USER_OPTIONS)) != null) {
			char * options;
			ZALLOC_ARRAY_CACHED(options, HOOPS_WORLD->_hoops_RAPPR, char);
			if (_hoops_CHHRGR (context, user_options, false, user_options->owner, uoname, options, -1)) {
				*length = _hoops_SSGR(options);
			}
			FREE_ARRAY(options, HOOPS_WORLD->_hoops_RAPPR, char);
			_hoops_HPRH (user_options);
		}
		_hoops_IRRPR();
	}
#endif
}



#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_User_Option (
	int					count,
	Key const *			keys,
	char const *		uoname,
	char *				options) 
{
	_hoops_PAPPR context("PShow_One_Net_User_Option");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_One_Net_User_Option () */\n");
	);

	_hoops_HPPIR *	user_options;
	if ((user_options = (_hoops_HPPIR *) HI_Find_Attribute_And_Lock(context, _hoops_PGAPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_CHHRGR (context, user_options, true, null, uoname, options, -1);
		_hoops_HPRH (user_options);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(options, -1, "", 0);

#endif
}
#endif


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_User_Opt_Len (
	int					count,
	Key const *			keys,
	char const *		uoname,
	int *				length) 
{
	_hoops_PAPPR context("PShow_One_Net_User_Opt_Len");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_One_Net_User_Opt_Len () */\n");
	);

	*length = 0;

	_hoops_HPPIR *	user_options;
	if ((user_options = (_hoops_HPPIR *) HI_Find_Attribute_And_Lock(context, _hoops_PGAPP, _hoops_HRPCR, count, keys)) != null) {
		char * options;
		ZALLOC_ARRAY_CACHED(options, HOOPS_WORLD->_hoops_RAPPR, char);
		if (_hoops_CHHRGR (context, user_options, true, null, uoname, options, -1)) {
			*length = _hoops_SSGR(options);
		}
		FREE_ARRAY(options, HOOPS_WORLD->_hoops_RAPPR, char);
		_hoops_HPRH (user_options);
		_hoops_IRRPR();
	}
	
#endif
}
#endif



/*--------------------------------------------------------------------*/

#ifndef DISABLE_SHOW
#ifndef DISABLE_UNICODE_OPTIONS

local Karacter _hoops_GIHRGR[] = {0};

local void _hoops_RIHRGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPPIR const *	_hoops_AIHRGR,
	Karacter *				options,
	int						_hoops_HGPCA) 
{
	_hoops_HPPIR const *	_hoops_PIHRGR;
	Option_Value *			_hoops_CSCIR;
	local const char		_hoops_SSACR[] = "Return string won't fit in provided space";

	if (_hoops_AIHRGR->_hoops_IGGSA)
		_hoops_PIHRGR = HI_Distill_User_Options(_hoops_RIGC, _hoops_AIHRGR, _hoops_SIIAP);
	else
		_hoops_PIHRGR = _hoops_AIHRGR;
		
	if ((_hoops_CSCIR = _hoops_PIHRGR->_hoops_APICA) == null)
		HI_Return_Karacters (options, _hoops_HGPCA, _hoops_GIHRGR, 0);
	else {
		Karacter		*_hoops_ASAPR = options;
		Karacter		*_hoops_PSAPR;

		if (_hoops_HGPCA == -1)
			_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR;	/* _hoops_IHRPR _hoops_IAHA */
		else
			_hoops_PSAPR = _hoops_ASAPR + _hoops_HGPCA;				/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */

		_hoops_PCCAR {
			_hoops_RPSAP *_hoops_HCGCC = (_hoops_RPSAP *)_hoops_CSCIR->type;
			int				_hoops_RHSAA;

			if (_hoops_CSCIR->type->_hoops_RCIIR != _hoops_CRSAP)
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected option type");
			else if (_hoops_CSCIR->_hoops_GCACR) {
				_hoops_ASAPR = _hoops_CPHRGR (_hoops_ASAPR, _hoops_PSAPR, "no ");
				_hoops_ASAPR = _hoops_SPHRGR (_hoops_ASAPR, _hoops_PSAPR, &_hoops_HCGCC->_hoops_SIHSA);
			}
			else if ((_hoops_RHSAA = _hoops_CSCIR->_hoops_AIPCR) == 0) {
				_hoops_ASAPR = _hoops_SPHRGR (_hoops_ASAPR, _hoops_PSAPR, &_hoops_HCGCC->_hoops_SIHSA);
			}
			else if (_hoops_RHSAA == 1) {
				_hoops_ASAPR = _hoops_SPHRGR (_hoops_ASAPR, _hoops_PSAPR, &_hoops_HCGCC->_hoops_SIHSA);
				_hoops_ASAPR = _hoops_CPHRGR (_hoops_ASAPR, _hoops_PSAPR, "=");
				KName _hoops_CPSGI;
				HI_Decode_Unicode_User_Option(_hoops_CSCIR->value._hoops_HGSAP[0],_hoops_CPSGI);
				_hoops_ASAPR = _hoops_SPHRGR (_hoops_ASAPR, _hoops_PSAPR, &_hoops_CPSGI);
				_hoops_PRPIR(_hoops_CPSGI);
			}
			else {
				int		count = 0;

				_hoops_ASAPR = _hoops_SPHRGR (_hoops_ASAPR, _hoops_PSAPR, &_hoops_HCGCC->_hoops_SIHSA);
				_hoops_ASAPR = _hoops_CPHRGR (_hoops_ASAPR, _hoops_PSAPR, "=(");

				do {
					KName _hoops_CPSGI;
					HI_Decode_Unicode_User_Option(_hoops_CSCIR->value._hoops_HGSAP[count],_hoops_CPSGI);
					_hoops_ASAPR = _hoops_SPHRGR (_hoops_ASAPR, _hoops_PSAPR, &_hoops_CSCIR->value._hoops_HGSAP[count]);
					_hoops_PRPIR(_hoops_CPSGI);
					_hoops_ASAPR = _hoops_CPHRGR (_hoops_ASAPR, _hoops_PSAPR, ",");
					if (_hoops_ASAPR == null) break;
				} _hoops_RGGA (++count == _hoops_RHSAA);

				if (_hoops_ASAPR != null)
					_hoops_ASAPR[-1] = ')';		/* _hoops_AGRP _hoops_CGHI _hoops_RRCIR _hoops_IS ')' */
			}

			if ((_hoops_CSCIR = _hoops_CSCIR->next) == null) break;

			if (_hoops_ASAPR == _hoops_PSAPR) _hoops_ASAPR = null; /* _hoops_PGPCR _hoops_RPP _hoops_PSP _hoops_RSIAR _hoops_IH ',' */
			if (_hoops_ASAPR == null) break;	  /* _hoops_PAR _hoops_RPP _hoops_AIAH _hoops_GGSR _hoops_IIGR _hoops_RSIAR */
			*_hoops_ASAPR++ = ',';		/* _hoops_GGCR ',' _hoops_GAPA _hoops_APSAR */
		}

		if (_hoops_ASAPR == null) {
			HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_SSACR);
			goto _hoops_RCCSR;
		}

		/* _hoops_GHHR _hoops_PRRP */
		if (_hoops_HGPCA == -1) {
			if (_hoops_ASAPR == _hoops_PSAPR) {
				HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_SSACR);
				goto _hoops_RCCSR;
			}
			*_hoops_ASAPR = '\0';							/* _hoops_IHRPR _hoops_IAHA */
		}
		else {
			_hoops_RGGA (_hoops_ASAPR == _hoops_PSAPR) *_hoops_ASAPR++ = ' ';		/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */
		}
	}

_hoops_RCCSR:

	if (_hoops_AIHRGR != _hoops_PIHRGR)
		_hoops_HPRH(_hoops_PIHRGR);

}

local void _hoops_HIHRGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPPIR const *	_hoops_AIHRGR,
	int *					length) 
{
	_hoops_HPPIR const *	_hoops_PIHRGR;
	Option_Value *			_hoops_CSCIR;

	if (_hoops_AIHRGR->_hoops_IGGSA)
		_hoops_PIHRGR = HI_Distill_User_Options(_hoops_RIGC, _hoops_AIHRGR, _hoops_SIIAP);
	else
		_hoops_PIHRGR = _hoops_AIHRGR;

	*length = 0;
	if ((_hoops_CSCIR = _hoops_PIHRGR->_hoops_APICA) != null) _hoops_PCCAR {
		_hoops_RPSAP *_hoops_HCGCC = (_hoops_RPSAP *)_hoops_CSCIR->type;
		int				_hoops_RHSAA;

		if (_hoops_CSCIR->type->_hoops_RCIIR != _hoops_CRSAP)
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected option type");
		else if (_hoops_CSCIR->_hoops_GCACR)
			*length += 3 + _hoops_HCGCC->_hoops_SIHSA.length;
		else if ((_hoops_RHSAA = _hoops_CSCIR->_hoops_AIPCR) == 0)
			*length += _hoops_HCGCC->_hoops_SIHSA.length;
		else if (_hoops_RHSAA == 1) {
			KName _hoops_CPSGI;
			HI_Decode_Unicode_User_Option(_hoops_CSCIR->value._hoops_HGSAP[0] ,_hoops_CPSGI);
			*length += _hoops_HCGCC->_hoops_SIHSA.length + 1 + _hoops_CPSGI.length;
			_hoops_PRPIR(_hoops_CPSGI);
		}
		else {
			int		count = 0;

			*length += _hoops_HCGCC->_hoops_SIHSA.length + 2;
			do {
				KName _hoops_CPSGI;
				HI_Decode_Unicode_User_Option(_hoops_CSCIR->value._hoops_HGSAP[count] ,_hoops_CPSGI);		
				*length += _hoops_CPSGI.length + 1;
				_hoops_PRPIR(_hoops_CPSGI);
			} _hoops_RGGA (++count == _hoops_RHSAA);
		}

		if ((_hoops_CSCIR = _hoops_CSCIR->next) == null) break;

		*length += 1;
	}

//_hoops_IIARR:

	if (_hoops_AIHRGR != _hoops_PIHRGR)
		_hoops_HPRH(_hoops_PIHRGR);
}

local Karacter _hoops_IIHRGR[] = {'o','f','f'}, _hoops_CIHRGR[] = {'o','n'};

local void _hoops_SIHRGR (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPPIR const *		_hoops_AIHRGR,
	bool						_hoops_PSACR,
	_hoops_CRCP const *				owner,
	Karacter const *			uoname,
	Karacter *					list,
	int							_hoops_GGCIR) 
{
	KName						_hoops_IPPIR;
	_hoops_HPPIR const *		_hoops_PIHRGR;
	Option_Value *				option;

	if (_hoops_AIHRGR->_hoops_IGGSA)
		_hoops_PIHRGR = HI_Distill_User_Options(_hoops_RIGC, _hoops_AIHRGR, _hoops_SIIAP);
	else
		_hoops_PIHRGR = _hoops_AIHRGR;

	HI_Canonize_Kars (uoname, &_hoops_IPPIR);

	if ((option = _hoops_PIHRGR->_hoops_APICA) != null) do {
		_hoops_RPSAP			*_hoops_HCGCC = (_hoops_RPSAP *)option->type;

		if (_hoops_RARPH (_hoops_IPPIR, _hoops_HCGCC->_hoops_SIHSA)) {
			if (option->_hoops_GCACR)
				HI_Return_Karacters (list, _hoops_GGCIR, _hoops_IIHRGR, 3);
			else if (option->_hoops_AIPCR == 0)
				HI_Return_Karacters (list, _hoops_GGCIR, _hoops_CIHRGR, 2);
			else if (option->_hoops_AIPCR == 1) {
				KName _hoops_CPSGI;
				HI_Decode_Unicode_User_Option(option->value._hoops_HGSAP[0], _hoops_CPSGI);
				HI_Return_Karacters (list, _hoops_GGCIR, _hoops_CPSGI._hoops_IPPPP, _hoops_CPSGI.length);
				_hoops_PRPIR(_hoops_CPSGI);
			} 
			else {
				Karacter		*_hoops_ASAPR = list;
				Karacter		*_hoops_PSAPR;
				int		count = 0;

				if (_hoops_GGCIR == -1)
					_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR;	/* _hoops_IHRPR _hoops_IAHA */
				else
					_hoops_PSAPR = _hoops_ASAPR + _hoops_GGCIR;			/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */

				do {
					KName _hoops_CPSGI;
					HI_Decode_Unicode_User_Option(option->value._hoops_HGSAP[count], _hoops_CPSGI);
					_hoops_ASAPR = _hoops_SPHRGR (_hoops_ASAPR, _hoops_PSAPR, &_hoops_CPSGI);
					_hoops_PRPIR(_hoops_CPSGI);

					_hoops_ASAPR = _hoops_CPHRGR (_hoops_ASAPR, _hoops_PSAPR, ",");
					if (_hoops_ASAPR == null) break;
				} _hoops_RGGA (++count == option->_hoops_AIPCR);

				if (_hoops_ASAPR != null)
					_hoops_ASAPR[-1] = '\0';		/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
			}
			_hoops_PRPIR (_hoops_IPPIR);
			goto _hoops_RCCSR;
		}
	} _hoops_RGGA ((option = option->next) == null);

	if (!_hoops_PSACR) {
		HE_ERROR (HEC_USER_OPTIONS, HES_NO_LOCAL_SETTING,
				  Sprintf_P (null, "Unicode User_Option	 has no local setting in '%p'", owner));
	}

	_hoops_PRPIR (_hoops_IPPIR);

	HI_Return_Karacters (list, _hoops_GGCIR, _hoops_GIHRGR, 0);

_hoops_RCCSR:

	if (_hoops_AIHRGR != _hoops_PIHRGR)
		_hoops_HPRH(_hoops_PIHRGR);

}

local void _hoops_GCHRGR (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPPIR const *		_hoops_AIHRGR,
	bool						_hoops_PSACR,
	_hoops_CRCP const *				owner,
	Karacter const *			uoname,
	int *						length) 
{
	KName						_hoops_IPPIR;
	_hoops_HPPIR const *		_hoops_PIHRGR;
	Option_Value *				option;

	if (_hoops_AIHRGR->_hoops_IGGSA)
		_hoops_PIHRGR = HI_Distill_User_Options(_hoops_RIGC, _hoops_AIHRGR, _hoops_SIIAP);
	else
		_hoops_PIHRGR = _hoops_AIHRGR;

	HI_Canonize_Kars (uoname, &_hoops_IPPIR);

	*length = 0;

	if ((option = _hoops_PIHRGR->_hoops_APICA) != null) do {
		_hoops_RPSAP			*_hoops_HCGCC = (_hoops_RPSAP *)option->type;

		if (_hoops_RARPH (_hoops_IPPIR, _hoops_HCGCC->_hoops_SIHSA)) {
			if (option->_hoops_GCACR)
				*length = 3;	/* '_hoops_PSAP' */
			else if (option->_hoops_AIPCR == 0)
				*length = 2;	/* '_hoops_GPP' */
			else if (option->_hoops_AIPCR == 1) {
				KName _hoops_CPSGI;
				HI_Decode_Unicode_User_Option(option->value._hoops_HGSAP[0] ,_hoops_CPSGI);
				*length = _hoops_CPSGI.length;
				_hoops_PRPIR(_hoops_CPSGI);
			}
			else {
				int				count = 0;

				do {
					KName _hoops_CPSGI;
					HI_Decode_Unicode_User_Option(option->value._hoops_HGSAP[count] ,_hoops_CPSGI);
					*length += _hoops_CPSGI.length + 1;	/* '_hoops_PIRA,' */
					_hoops_PRPIR(_hoops_CPSGI);
				} _hoops_RGGA (++count == option->_hoops_AIPCR);

				*length -= 1;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
			}
			_hoops_PRPIR (_hoops_IPPIR);
			goto _hoops_RCCSR;
		}
	} _hoops_RGGA ((option = option->next) == null);

	if (!_hoops_PSACR) {
		HE_ERROR (HEC_USER_OPTIONS, HES_NO_LOCAL_SETTING,
				  Sprintf_P (null, "Unicode User_Option	 has no local setting in '%p'", owner));
	}

	_hoops_PRPIR (_hoops_IPPIR);

	*length = 0;

_hoops_RCCSR:

	if (_hoops_AIHRGR != _hoops_PIHRGR)
		_hoops_HPRH(_hoops_PIHRGR);
	
}
#endif
#endif



HC_INTERFACE void HC_CDECL HC_Show_Unicode_Options (
	Karacter *			options) 
{
	_hoops_PAPPR context("Show_Unicode_Options");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef DISABLE_UNICODE_OPTIONS
	_hoops_IRPPR ("Unicode_Options");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Unicode_Options () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PGAPP)) != null) {

		_hoops_HPPIR *	_hoops_PIHRGR;
		if ((_hoops_PIHRGR = (_hoops_HPPIR *)HI_Find_Attribute (context, target, HK_USER_OPTIONS)) != null) {
			_hoops_RIHRGR (context, _hoops_PIHRGR, options, -1);
			_hoops_HPRH (_hoops_PIHRGR);
		}
		_hoops_IRRPR();
	}
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Unicode_Options_Length (
	int *					length) 
{
	_hoops_PAPPR context("Show_Unicode_Options_Length");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef DISABLE_UNICODE_OPTIONS
	_hoops_IRPPR ("Unicode_Options");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Unicode_Options_Length () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PGAPP)) != null) {

		_hoops_HPPIR *	_hoops_PIHRGR;
		if ((_hoops_PIHRGR = (_hoops_HPPIR *)HI_Find_Attribute (context, target, HK_USER_OPTIONS)) != null) {
			_hoops_HIHRGR (context, _hoops_PIHRGR, length);
			_hoops_HPRH (_hoops_PIHRGR);
		}
		_hoops_IRRPR();
	}
#endif
#endif
}



#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Unicode_Options (
	int						count,
	Key const *				keys,
	Karacter *				options) 
{
	_hoops_PAPPR context("PShow_Net_Unicode_Options");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
#ifdef DISABLE_UNICODE_OPTIONS
	_hoops_IRPPR ("Unicode_Options");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Unicode_Options () */\n");
	);

	_hoops_HPPIR *	_hoops_PIHRGR;
	if ((_hoops_PIHRGR = (_hoops_HPPIR *) HI_Find_Attribute_And_Lock(context, _hoops_PGAPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_RIHRGR (context, _hoops_PIHRGR, options, -1);
		_hoops_HPRH (_hoops_PIHRGR);
		_hoops_IRRPR();
	}
	else
		HI_Return_Karacters(options, -1, null, 0);
	
#endif
#endif
}
#endif


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Unicode_Opt_Length (
	int						count,
	Key const *				keys,
	int *					length) 
{
	_hoops_PAPPR context("PShow_Net_Unicode_Opt_Length");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
#ifdef DISABLE_UNICODE_OPTIONS
	_hoops_IRPPR ("Unicode_Options");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Unicode_Opt_Length () */\n");
	);

	*length=0;

	_hoops_HPPIR *	_hoops_PIHRGR;
	if ((_hoops_PIHRGR = (_hoops_HPPIR *) HI_Find_Attribute_And_Lock(context, _hoops_PGAPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_HIHRGR (context, _hoops_PIHRGR, length);
		_hoops_HPRH (_hoops_PIHRGR);
		_hoops_IRRPR();
	}
	
#endif
#endif
}
#endif


HC_INTERFACE void HC_CDECL HC_Show_One_Unicode_Option (
	Karacter const *		uoname,
	Karacter *				options) 
{
	_hoops_PAPPR context("Show_One_Unicode_Option");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef DISABLE_UNICODE_OPTIONS
	_hoops_IRPPR ("Unicode_Options");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_Unicode_Option () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PGAPP)) != null) {

		_hoops_HPPIR *	_hoops_PIHRGR;
		if ((_hoops_PIHRGR = (_hoops_HPPIR *)HI_Find_Attribute (context, target, HK_USER_OPTIONS)) != null) {
			_hoops_SIHRGR (context, _hoops_PIHRGR, false, _hoops_PIHRGR->owner, uoname, options, -1);
			_hoops_HPRH (_hoops_PIHRGR);
		}
		_hoops_IRRPR();
	}
#endif
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_One_Uni_Option_Length (
	Karacter const *		uoname,
	int *					length) 
{
	_hoops_PAPPR context("Show_One_Uni_Option_Length");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef DISABLE_UNICODE_OPTIONS
	_hoops_IRPPR ("Unicode_Options");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_Uni_Option_Length () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PGAPP)) != null) {

		_hoops_HPPIR *	_hoops_PIHRGR;
		if ((_hoops_PIHRGR = (_hoops_HPPIR *)HI_Find_Attribute (context, target, HK_USER_OPTIONS)) != null) {
			_hoops_GCHRGR (context, _hoops_PIHRGR, false, _hoops_PIHRGR->owner, uoname, length);
			_hoops_HPRH (_hoops_PIHRGR);
		}
		_hoops_IRRPR();
	}
#endif
#endif
}



#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Unicode_Opt (
	int						count,
	Key const *				keys,
	Karacter const *		uoname,
	Karacter *				options) 
{
	_hoops_PAPPR context("PShow_One_Net_Unicode_Option");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
#ifdef DISABLE_UNICODE_OPTIONS
	_hoops_IRPPR ("Unicode_Options");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_One_Net_Unicode_Option () */\n");
	);

	_hoops_HPPIR *	_hoops_PIHRGR;
	if ((_hoops_PIHRGR = (_hoops_HPPIR *) HI_Find_Attribute_And_Lock(context, _hoops_PGAPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_SIHRGR (context, _hoops_PIHRGR, true, null, uoname, options, -1);
		_hoops_HPRH (_hoops_PIHRGR);
		_hoops_IRRPR();
	}
	else
		HI_Return_Karacters(options, -1, null, 0);

#endif
#endif
}
#endif

#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Uni_Opt_Len (
	int						count,
	Key const *				keys,
	Karacter const *		uoname,
	int *					length) 
{
	_hoops_PAPPR context("PShow_One_Net_Uni_Opt_Len");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
#ifdef DISABLE_UNICODE_OPTIONS
	_hoops_IRPPR ("Unicode_Options");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_One_Net_Uni_Opt_Len () */\n");
	);

	*length = 0;

	_hoops_HPPIR *	_hoops_PIHRGR;
	if ((_hoops_PIHRGR = (_hoops_HPPIR *) HI_Find_Attribute_And_Lock(context, _hoops_PGAPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_GCHRGR (context, _hoops_PIHRGR, true, null, uoname, length);
		_hoops_HPRH (_hoops_PIHRGR);
		_hoops_IRRPR();
	}
	
#endif
#endif
}
#endif




/**********************************************************************/

local void _hoops_RCHRGR(
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPPIR const *		_hoops_AHHRGR,
	int *						_hoops_CSGIH) 
{
	_hoops_HPPIR const *		user_options;

	if (_hoops_AHHRGR->_hoops_IGGSA)
		user_options = HI_Distill_User_Options(_hoops_RIGC, _hoops_AHHRGR, _hoops_GCIAP);
	else 
		user_options = _hoops_AHHRGR;

	if(user_options->_hoops_AGGSA)
		*_hoops_CSGIH = user_options->_hoops_AGGSA->Count();
	else
		*_hoops_CSGIH = 0;

	if (user_options != _hoops_AHHRGR)
		_hoops_HPRH(user_options);
}

local void _hoops_ACHRGR(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPPIR *			_hoops_AHHRGR,
	int *					_hoops_CSGIH,
	long *					indices,
	void **					values) {
	_hoops_HPPIR const *	user_options;

	if (_hoops_AHHRGR->_hoops_IGGSA)
		user_options = HI_Distill_User_Options(_hoops_RIGC, _hoops_AHHRGR, _hoops_GCIAP);
	else 
		user_options = _hoops_AHHRGR;

	if(user_options->_hoops_AGGSA){
		*_hoops_CSGIH = user_options->_hoops_AGGSA->Count();
		_hoops_PGGSA::PairList * _hoops_ARIRI = user_options->_hoops_AGGSA->GetPairList();
		_hoops_ARIRI->ResetCursor();
		_hoops_PGGSA::Pair * p;
		while((p = _hoops_ARIRI->PeekCursor()) != 0){
			*indices++ = p->Key();
			*values++ = p->Item();
			_hoops_ARIRI->AdvanceCursor();
		}
		delete _hoops_ARIRI;
	}	

	if (user_options != _hoops_AHHRGR)
		_hoops_HPRH(user_options);
}

local bool _hoops_PCHRGR (
	_hoops_HPPIR *		user_options, 
	long				index,
	void **				value)
{

	_hoops_HPPIR const * _hoops_IPPIR;

	// _hoops_PSHS
	if (user_options->_hoops_IGGSA) {
		_hoops_CGGSA::UniqueCursor *	uc = user_options->_hoops_IGGSA->GetUniqueCursor();
		while((_hoops_IPPIR = uc->Peek()) != null) {	

			ASSERT(_hoops_IPPIR->_hoops_IGGSA == null);

			if (_hoops_IPPIR->_hoops_AGGSA && _hoops_IPPIR->_hoops_AGGSA->Count() != 0) {
				void * item;
				_hoops_PGGSA::status status = _hoops_IPPIR->_hoops_AGGSA->LookupItem(index, &item);
				if(status == VHASH_STATUS_SUCCESS){
					if (value != null)
						*value = item;
					delete uc;
					return true;
				}
			}

			uc->Advance();
		}
		delete uc;
	}

	// _hoops_IRGH
	_hoops_IPPIR = user_options;
	if (_hoops_IPPIR->_hoops_AGGSA && _hoops_IPPIR->_hoops_AGGSA->Count() != 0) {
		void * item;
		_hoops_PGGSA::status status = _hoops_IPPIR->_hoops_AGGSA->LookupItem(index, &item);
		if(status == VHASH_STATUS_SUCCESS){
			if (value != null)
				*value = item;
			return true;
		}
	}

	return false;
}

HC_INTERFACE void HC_CDECL HC_Show_User_Index_Count (
	int *					_hoops_CSGIH) 
{
	_hoops_PAPPR context("Show_User_Index_Count");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* Show_User_Index_Count () */\n");
	);

	*_hoops_CSGIH = 0;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PGAPP)) != null) {

		_hoops_HPPIR *	user_options;
		if ((user_options = (_hoops_HPPIR *)HI_Find_Attribute (context, target, -HK_USER_OPTIONS)) != null) {
			_hoops_RCHRGR(context, user_options, _hoops_CSGIH);
			_hoops_HPRH (user_options);
		}
		_hoops_IRRPR();
	}
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_User_Indices (
	int *				_hoops_CSGIH,
	long *				indices,
	void **				values) 
{
	_hoops_PAPPR context("Show_User_Indices");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* Show_User_Indices () */\n");
	);

	*_hoops_CSGIH = 0;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PGAPP)) != null) {

		_hoops_HPPIR *	user_options;
		if ((user_options = (_hoops_HPPIR *)HI_Find_Attribute (context, target, HK_USER_OPTIONS)) != null) {
			_hoops_ACHRGR(context, user_options, _hoops_CSGIH, indices, values);	
			_hoops_HPRH (user_options);
		}
		_hoops_IRRPR();
	}
#endif
}

HC_INTERFACE bool HC_CDECL HC_Show_One_User_Index (
	long					index,
	void **					value) 
{
	_hoops_PAPPR context("Show_One_User_Index");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* Show_One_User_Index () */\n");
	);

	if (value != null)
		*value = null;

	bool	_hoops_PPIHA = false;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PGAPP)) != null) {

		_hoops_HPPIR *	user_options;
		if ((user_options = (_hoops_HPPIR *)HI_Find_Attribute (context, target, -HK_USER_OPTIONS)) != null) {
			_hoops_PPIHA = _hoops_PCHRGR(user_options, index, value);
			_hoops_HPRH (user_options);
		}
		_hoops_IRRPR();
	}

	return _hoops_PPIHA;
#endif
	
}


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_User_Index_Count (
	int					count,
	Key const *			keys,
	int	*				_hoops_CSGIH) 
{
	_hoops_PAPPR context("PShow_Net_User_Index_Count");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* PShow_Net_User_Index_Count () */\n");
	);

	*_hoops_CSGIH = 0;

	_hoops_HPPIR *	user_options;
	if ((user_options = (_hoops_HPPIR *) HI_Find_Attribute_And_Lock(context, _hoops_PGAPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_RCHRGR(context, user_options, _hoops_CSGIH);
		_hoops_HPRH (user_options);
		_hoops_IRRPR();
	}
	
#endif
}
#endif


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_User_Indices (
	int					count,
	Key const *			keys,
	int *				_hoops_CSGIH,
	long *				indices,
	void **				values) 
{
	_hoops_PAPPR context("PShow_Net_User_Indices");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* PShow_Net_User_Indices () */\n");
	);

	*_hoops_CSGIH = 0;

	_hoops_HPPIR *	user_options;
	if ((user_options = (_hoops_HPPIR *) HI_Find_Attribute_And_Lock(context, _hoops_PGAPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_ACHRGR(context, user_options, _hoops_CSGIH, indices, values); 
		_hoops_HPRH (user_options);
		_hoops_IRRPR();
	}
	
#endif
}
#endif




#ifndef _hoops_ARPCR
HC_INTERFACE bool HC_CDECL HC_PShow_One_Net_User_Index (
	int					count,
	Key const *			keys,
	long				index,
	void **				value) 
{
	_hoops_PAPPR context("PShow_One_Net_User_Index");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* PShow_One_Net_User_Index () */\n");
	);

	if (value != null)
		*value = null;

	bool	_hoops_PPIHA = false;

	_hoops_HPPIR *	user_options;
	if ((user_options = (_hoops_HPPIR *) HI_Find_Attribute_And_Lock(context, _hoops_PGAPP, _hoops_HRPCR|_hoops_CSCAP, count, keys)) != null) {
		_hoops_PPIHA = _hoops_PCHRGR(user_options, index, value);
		_hoops_HPRH (user_options);
		_hoops_IRRPR();
	}
	
	return _hoops_PPIHA;
#endif
}
#endif



HC_INTERFACE void HC_CDECL HC_Set_User_Data (
	POINTER_SIZED_INT			index,
	void const *				data,
	long						data_length) 
{
	_hoops_PAPPR context("Set_User_Data");

	CODE_GENERATION (
		int count = data_length;
		char* _hoops_HAHRGR = (char *)data;
		HI_Dump_Code (H_FORMAT_TEXT("/* %s */\n", H_UTF8((char const *)data).encodedText()));
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_LD (null, "char * data = (char*) malloc(sizeof(char)*%D);\n", data_length));
		while (count-- != 0)
			HI_Dump_Code (H_FORMAT_TEXT("data[%d] = 0x%x;\n", count, _hoops_HAHRGR[count]));
		HI_Dump_Code (H_FORMAT_TEXT("HC_Set_User_Data (%ld, (void *)&data[0], %ld);\n", index, data_length));
		HI_Dump_Code ("free (data);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	bool			used = false;
	_hoops_HPPIR *	user_options;
	ZALLOC (user_options, _hoops_HPPIR);

	_hoops_IHSCA * _hoops_CRHRGR = NEW(_hoops_IHSCA)(data, data_length);

	user_options->_hoops_HGGSA = POOL_NEW(context->memory_pool, _hoops_GISCA)(context->memory_pool, 2);
	user_options->_hoops_HGGSA->InsertItem(index, _hoops_CRHRGR);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_IHRPP)) != null) {
		used = HI_Set_User_Options (context, target, user_options);
		_hoops_IRRPR();
	}

	if (!used) 
		HI_Free_User_Option(context, user_options);

}

local long _hoops_HCHRGR(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPPIR const *	user_options,	
	POINTER_SIZED_INT		index,
	void *					data,
	long 					data_size)
{
	UNREFERENCED(_hoops_RIGC);

	long	_hoops_ICHRGR = 0;
	_hoops_HPPIR const * _hoops_IPPIR;

	// _hoops_PSHS
	if (user_options->_hoops_IGGSA) {
		_hoops_CGGSA::UniqueCursor *	uc = user_options->_hoops_IGGSA->GetUniqueCursor();
		while((_hoops_IPPIR = uc->Peek()) != null) {	

			ASSERT(_hoops_IPPIR->_hoops_IGGSA == null);

			if (_hoops_IPPIR->_hoops_HGGSA && _hoops_IPPIR->_hoops_HGGSA->Count() != 0) {
				_hoops_IHSCA * item;
				_hoops_GISCA::status status = _hoops_IPPIR->_hoops_HGGSA->LookupItem(index, &item);
				if(status == VHASH_STATUS_SUCCESS){
					if (data_size >= item->data_length) {
						_hoops_ICHRGR = item->data_length;
						if (data != null)
							COPY_MEMORY(item->data, item->data_length, data);
					}
					else 
						_hoops_ICHRGR = -item->data_length;

					delete uc;
					return _hoops_ICHRGR;
				}
			}
			uc->Advance();
		}
		delete uc;
	}

	// _hoops_HCIAA _hoops_ARP
	_hoops_IPPIR = user_options;	

	if (_hoops_IPPIR->_hoops_HGGSA && _hoops_IPPIR->_hoops_HGGSA->Count() != 0) {
		_hoops_IHSCA * item;
		_hoops_GISCA::status status = _hoops_IPPIR->_hoops_HGGSA->LookupItem(index, &item);
		if(status == VHASH_STATUS_SUCCESS){
			if (data_size >= item->data_length) {
				_hoops_ICHRGR = item->data_length;
				if (data != null)
					COPY_MEMORY(item->data, item->data_length, data);
			}
			else 
				_hoops_ICHRGR = -item->data_length;

			return _hoops_ICHRGR;
		}
	}

	return _hoops_ICHRGR;
}


local long _hoops_CCHRGR(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPPIR const *	_hoops_AHHRGR, 
	POINTER_SIZED_INT *		data_indices, 
	long					data_indices_count) {
	_hoops_HPPIR const *	user_options; 
	long					_hoops_ICHRGR = 0;

	if (_hoops_AHHRGR->_hoops_IGGSA)
		user_options = HI_Distill_User_Options(_hoops_RIGC, _hoops_AHHRGR, _hoops_RCIAP);
	else
		user_options = _hoops_AHHRGR; 

	if(user_options->_hoops_HGGSA) {

		long count = (long)user_options->_hoops_HGGSA->Count();

		if (data_indices_count >= count) {

			_hoops_ICHRGR = user_options->_hoops_HGGSA->Count();
			_hoops_GISCA::PairList * _hoops_ARIRI = user_options->_hoops_HGGSA->GetPairList();
			_hoops_ARIRI->ResetCursor();
			_hoops_GISCA::Pair * p;
			while((p = _hoops_ARIRI->PeekCursor()) != 0){
				*data_indices++ = p->Key();
				_hoops_ARIRI->AdvanceCursor();
			}
			delete _hoops_ARIRI;
		}
		else
			_hoops_ICHRGR = -count;
	}

//_hoops_IIARR:

	if (_hoops_AHHRGR != user_options)
		_hoops_HPRH(user_options);

	return _hoops_ICHRGR;
}



HC_INTERFACE long HC_CDECL HC_Show_One_User_Data (
	POINTER_SIZED_INT		index,
	void *					data,
	long 					data_size) 
{
	_hoops_PAPPR context("Show_One_User_Data");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* Show_One_User_Data () */\n");
	);

	long	_hoops_ICHRGR = 0;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PGAPP)) != null) {

		_hoops_HPPIR *	user_options;
		if ((user_options = (_hoops_HPPIR *)HI_Find_Attribute (context, target, -HK_USER_OPTIONS)) != null) {
			_hoops_ICHRGR = _hoops_HCHRGR(context, user_options, index, data, data_size);
			_hoops_HPRH (user_options);
		}
		_hoops_IRRPR();
	}
	return _hoops_ICHRGR;
#endif
}

HC_INTERFACE long HC_CDECL HC_Show_User_Data_Indices (
	POINTER_SIZED_INT *		data_indices, 
	long					data_indices_count) 
{
	_hoops_PAPPR context("Show_User_Data_Indices");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return 0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* Show_User_Data_Indices () */\n");
	);

	long	_hoops_ICHRGR = 0;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PGAPP)) != null) {

		_hoops_HPPIR *	user_options;
		if ((user_options = (_hoops_HPPIR *)HI_Find_Attribute (context, target, -HK_USER_OPTIONS)) != null) {
			_hoops_ICHRGR = _hoops_CCHRGR(context, user_options, data_indices, data_indices_count);
			_hoops_HPRH (user_options);
		}
		_hoops_IRRPR();
	}
	return _hoops_ICHRGR;
#endif
}



HC_INTERFACE long HC_CDECL HC_PShow_One_Net_User_Data (
	int						count,
	Key const *				keys,	
	POINTER_SIZED_INT		index, 
	void *					data, 
	long					data_length) 
{
	_hoops_PAPPR context("PShow_One_Net_User_Data");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return 0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_One_Net_User_Data () */\n");
	);

	long	_hoops_ICHRGR = 0;

	_hoops_HPPIR *	user_options;
	if ((user_options = (_hoops_HPPIR *) HI_Find_Attribute_And_Lock(context, _hoops_PGAPP, _hoops_HRPCR|_hoops_CSCAP, count, keys)) != null) {
		_hoops_ICHRGR = _hoops_HCHRGR(context, user_options, index, data, data_length);
		_hoops_HPRH (user_options);
		_hoops_IRRPR();
	}

	return _hoops_ICHRGR;
#endif	
}





GLOBAL_FUNCTION int HI_User_Option_Hash_Key(
	_hoops_HPPIR const *	_hoops_ACSIH)
{
	_hoops_HPPIR const *				_hoops_SHSGI = _hoops_ACSIH;
	_hoops_CGGSA::UniqueCursor *	uc = null;
	int									key = 1;

	if (_hoops_SHSGI->_hoops_IGGSA && 
		_hoops_SHSGI->_hoops_IGGSA->Count() > 0) 
		uc = _hoops_ACSIH->_hoops_IGGSA->GetUniqueCursor();
	
	do {

		if (_hoops_SHSGI->_hoops_AGGSA)
			key += _hoops_SHSGI->_hoops_AGGSA->Count();

		if (_hoops_SHSGI->_hoops_HGGSA)
			key ^= _hoops_SHSGI->_hoops_HGGSA->Count() << 8;

		if (_hoops_SHSGI->option_list != null)
			key += 57;

		if (_hoops_SHSGI->_hoops_APICA != null)
			key += 111;

		if (_hoops_SHSGI->_hoops_AGGSA && _hoops_SHSGI->_hoops_AGGSA->Count() > 0) {

			int count = _hoops_SHSGI->_hoops_AGGSA->Count();

			_hoops_PGGSA::PairList * list = _hoops_SHSGI->_hoops_AGGSA->GetPairList();

			list->ResetCursor();

			while (count--) {
				_hoops_PGGSA::Pair *	pair = list->PeekCursor();

				key ^= pair->Key();
				key ^= (int)(POINTER_SIZED_INT)pair->Item();

				list->AdvanceCursor();
			}

			delete list;
		}

		if (uc) {
			_hoops_SHSGI = uc->Peek();
			uc->Advance();
		}
		else
			break;

	} while (_hoops_SHSGI != null);

	delete uc;

	return key;
}

GLOBAL_FUNCTION _hoops_HPPIR * HI_Distill_User_Options(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPPIR const *	_hoops_ACSIH, 
	int						flags)
{
	_hoops_HPPIR *			_hoops_SPSAA;

	ZALLOC (_hoops_SPSAA, _hoops_HPPIR);
	_hoops_SPSAA->type = HK_USER_OPTIONS;
	_hoops_SPSAA->_hoops_HIHI = 1;

	bool _hoops_SCHRGR = false;
	bool _hoops_GSHRGR = false;
	bool _hoops_RSHRGR = false;
	bool _hoops_ASHRGR = false;

	if (_hoops_ACSIH->_hoops_IGGSA != null) {

		if (_hoops_ACSIH->_hoops_IGGSA->Count() > 1)
			_hoops_ACSIH->_hoops_IGGSA->Reverse();

		_hoops_CGGSA::UniqueCursor *	uc = _hoops_ACSIH->_hoops_IGGSA->GetUniqueCursor();
		_hoops_HPPIR const * _hoops_IPPIR;

		while((_hoops_IPPIR = uc->Peek()) != null) {	

			if (_hoops_IPPIR->option_list != null)
				_hoops_SCHRGR = true;

			if (_hoops_IPPIR->_hoops_APICA != null)
				_hoops_GSHRGR = true;

			if (_hoops_IPPIR->_hoops_AGGSA != null)
				_hoops_RSHRGR = true;

			if (_hoops_IPPIR->_hoops_HGGSA != null)
				_hoops_ASHRGR = true;

			uc->Advance();
		}
		delete uc;
	}

	if (BIT(flags, _hoops_CIIAP)) {

		_hoops_HPPIR const * _hoops_IPPIR;

		// _hoops_PSHS
		if (_hoops_SCHRGR) {

			_hoops_CGGSA::UniqueCursor *	uc = _hoops_ACSIH->_hoops_IGGSA->GetUniqueCursor();

			while((_hoops_IPPIR = uc->Peek()) != null) {	

				ASSERT(_hoops_IPPIR->_hoops_IGGSA == null);

				Option_Value **	_hoops_CIGHH = &_hoops_SPSAA->option_list, *_hoops_GCGHH, *_hoops_HRHRGR;

				if ((_hoops_GCGHH = _hoops_IPPIR->option_list) != null) do {
					Option_Value *_hoops_IRHRGR;

					_hoops_RGGA ((_hoops_HRHRGR = *_hoops_CIGHH) == null ||
							_hoops_HRHRGR->type->id >= _hoops_GCGHH->type->id)
						_hoops_CIGHH = &_hoops_HRHRGR->next;

					_hoops_IRHRGR = _hoops_GCGHH->next;
					_hoops_GCGHH->next = null;	/* _hoops_HCPRA _hoops_GHHR _hoops_SCH */

					/* _hoops_IPS _hoops_RGR _hoops_PIRA _hoops_GGR */
					*_hoops_CIGHH = HI_Copy_Option_List (_hoops_GCGHH);

					if (_hoops_HRHRGR == null ||
						_hoops_HRHRGR->type->id > _hoops_GCGHH->type->id) {
						(*_hoops_CIGHH)->next = _hoops_HRHRGR;
					}
					else {	/* _hoops_PIHA _hoops_SHH _hoops_SASPR, _hoops_HASIR _hoops_GIGR */
						(*_hoops_CIGHH)->next = _hoops_HRHRGR->next;

						_hoops_HRHRGR->next = null;
						HI_Free_Option_List (_hoops_RIGC, _hoops_HRHRGR);
					}
					_hoops_GCGHH->next = _hoops_IRHRGR; /* _hoops_PPSI _hoops_SCH _hoops_ISSC */
				}
				_hoops_RGGA ((_hoops_GCGHH = _hoops_GCGHH->next) == null);

				uc->Advance();
			}
			delete uc;

		}

		if (_hoops_ACSIH->option_list != null) {

			// _hoops_HCIAA _hoops_ARP
			_hoops_IPPIR = _hoops_ACSIH;	

			Option_Value **	_hoops_CIGHH = &_hoops_SPSAA->option_list, *_hoops_GCGHH, *_hoops_HRHRGR;

			if ((_hoops_GCGHH = _hoops_IPPIR->option_list) != null) do {
				Option_Value *_hoops_IRHRGR;

				_hoops_RGGA ((_hoops_HRHRGR = *_hoops_CIGHH) == null ||
						_hoops_HRHRGR->type->id >= _hoops_GCGHH->type->id)
					_hoops_CIGHH = &_hoops_HRHRGR->next;

				_hoops_IRHRGR = _hoops_GCGHH->next;
				_hoops_GCGHH->next = null;	/* _hoops_HCPRA _hoops_GHHR _hoops_SCH */

				/* _hoops_IPS _hoops_RGR _hoops_PIRA _hoops_GGR */
				*_hoops_CIGHH = HI_Copy_Option_List (_hoops_GCGHH);

				if (_hoops_HRHRGR == null ||
					_hoops_HRHRGR->type->id > _hoops_GCGHH->type->id) {
					(*_hoops_CIGHH)->next = _hoops_HRHRGR;
				}
				else {	/* _hoops_PIHA _hoops_SHH _hoops_SASPR, _hoops_HASIR _hoops_GIGR */
					(*_hoops_CIGHH)->next = _hoops_HRHRGR->next;

					_hoops_HRHRGR->next = null;
					HI_Free_Option_List (_hoops_RIGC, _hoops_HRHRGR);
				}
				_hoops_GCGHH->next = _hoops_IRHRGR; /* _hoops_PPSI _hoops_SCH _hoops_ISSC */
			}
			_hoops_RGGA ((_hoops_GCGHH = _hoops_GCGHH->next) == null);
		}
	}

#ifndef DISABLE_UNICODE_OPTIONS
	if (BIT(flags, _hoops_SIIAP)) {

		_hoops_HPPIR const * _hoops_IPPIR;

		// _hoops_PSHS
		if (_hoops_GSHRGR) {
			
			_hoops_CGGSA::UniqueCursor *	uc = _hoops_ACSIH->_hoops_IGGSA->GetUniqueCursor();

			while((_hoops_IPPIR = uc->Peek()) != null) {	

				ASSERT(_hoops_IPPIR->_hoops_IGGSA == null);

				Option_Value **	_hoops_CIGHH = &_hoops_SPSAA->_hoops_APICA, *_hoops_GCGHH, *_hoops_HRHRGR;

				if ((_hoops_GCGHH = _hoops_IPPIR->_hoops_APICA) != null) do {
					Option_Value *_hoops_IRHRGR;

					_hoops_RGGA ((_hoops_HRHRGR = *_hoops_CIGHH) == null ||
							_hoops_HRHRGR->type->id >= _hoops_GCGHH->type->id)
						_hoops_CIGHH = &_hoops_HRHRGR->next;

					_hoops_IRHRGR = _hoops_GCGHH->next;
					_hoops_GCGHH->next = null;	/* _hoops_HCPRA _hoops_GHHR _hoops_SCH */

					/* _hoops_IPS _hoops_RGR _hoops_PIRA _hoops_GGR */
					*_hoops_CIGHH = HI_Copy_Option_List (_hoops_GCGHH);

					if (_hoops_HRHRGR == null ||
						_hoops_HRHRGR->type->id > _hoops_GCGHH->type->id) {
						(*_hoops_CIGHH)->next = _hoops_HRHRGR;
					}
					else {	/* _hoops_PIHA _hoops_SHH _hoops_SASPR, _hoops_HASIR _hoops_GIGR */
						(*_hoops_CIGHH)->next = _hoops_HRHRGR->next;

						_hoops_HRHRGR->next = null;
						HI_Free_Option_List (_hoops_RIGC, _hoops_HRHRGR);
					}
					_hoops_GCGHH->next = _hoops_IRHRGR; /* _hoops_PPSI _hoops_SCH _hoops_ISSC */
				}
				_hoops_RGGA ((_hoops_GCGHH = _hoops_GCGHH->next) == null);

				uc->Advance();
			}
			delete uc;
		}

		if (_hoops_ACSIH->_hoops_APICA != null) {

			// _hoops_HCIAA _hoops_ARP
			_hoops_IPPIR = _hoops_ACSIH;	

			Option_Value **	_hoops_CIGHH = &_hoops_SPSAA->_hoops_APICA, *_hoops_GCGHH, *_hoops_HRHRGR;

			if ((_hoops_GCGHH = _hoops_IPPIR->_hoops_APICA) != null) do {
				Option_Value *_hoops_IRHRGR;

				_hoops_RGGA ((_hoops_HRHRGR = *_hoops_CIGHH) == null ||
						_hoops_HRHRGR->type->id >= _hoops_GCGHH->type->id)
					_hoops_CIGHH = &_hoops_HRHRGR->next;

				_hoops_IRHRGR = _hoops_GCGHH->next;
				_hoops_GCGHH->next = null;	/* _hoops_HCPRA _hoops_GHHR _hoops_SCH */

				/* _hoops_IPS _hoops_RGR _hoops_PIRA _hoops_GGR */
				*_hoops_CIGHH = HI_Copy_Option_List (_hoops_GCGHH);

				if (_hoops_HRHRGR == null ||
					_hoops_HRHRGR->type->id > _hoops_GCGHH->type->id) {
					(*_hoops_CIGHH)->next = _hoops_HRHRGR;
				}
				else {	/* _hoops_PIHA _hoops_SHH _hoops_SASPR, _hoops_HASIR _hoops_GIGR */
					(*_hoops_CIGHH)->next = _hoops_HRHRGR->next;

					_hoops_HRHRGR->next = null;
					HI_Free_Option_List (_hoops_RIGC, _hoops_HRHRGR);
				}
				_hoops_GCGHH->next = _hoops_IRHRGR; /* _hoops_PPSI _hoops_SCH _hoops_ISSC */
			}
			_hoops_RGGA ((_hoops_GCGHH = _hoops_GCGHH->next) == null);
		}
	}
#endif

	if (BIT(flags, _hoops_GCIAP)) {

		_hoops_HPPIR const * _hoops_IPPIR;

		// _hoops_PSHS
		if (_hoops_RSHRGR) {
			
			_hoops_CGGSA::UniqueCursor *	uc = _hoops_ACSIH->_hoops_IGGSA->GetUniqueCursor();

			while((_hoops_IPPIR = uc->Peek()) != null) {

				ASSERT(_hoops_IPPIR->_hoops_IGGSA == null);

				if (_hoops_IPPIR->_hoops_AGGSA && _hoops_IPPIR->_hoops_AGGSA->Count() > 0) {
					if (!_hoops_SPSAA->_hoops_AGGSA) {
						_hoops_SPSAA->_hoops_AGGSA = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_PGGSA)(_hoops_IPPIR->_hoops_AGGSA);
					}
					else 
						_hoops_SPSAA->_hoops_AGGSA->Merge(_hoops_IPPIR->_hoops_AGGSA, VHASH_MERGE_REPLACE_DUPLICATES);
				}
				uc->Advance();
			}

			delete uc;
		}

		if (_hoops_ACSIH->_hoops_AGGSA != null) {

			// _hoops_HCIAA _hoops_ARP
			_hoops_IPPIR = _hoops_ACSIH;	

			if (_hoops_IPPIR->_hoops_AGGSA && _hoops_IPPIR->_hoops_AGGSA->Count() > 0) {
				if (!_hoops_SPSAA->_hoops_AGGSA)
					_hoops_SPSAA->_hoops_AGGSA = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_PGGSA)(_hoops_IPPIR->_hoops_AGGSA);
				else 
					_hoops_SPSAA->_hoops_AGGSA->Merge(_hoops_IPPIR->_hoops_AGGSA, VHASH_MERGE_REPLACE_DUPLICATES);
			}
		}
	}

	if (BIT(flags, _hoops_RCIAP)) {

		_hoops_HPPIR const * _hoops_IPPIR;

		// _hoops_PSHS
		if (_hoops_ASHRGR) {
			
			_hoops_CGGSA::UniqueCursor *	uc = _hoops_ACSIH->_hoops_IGGSA->GetUniqueCursor();

			while((_hoops_IPPIR = uc->Peek()) != null) {

				ASSERT(_hoops_IPPIR->_hoops_IGGSA == null);

				if (_hoops_IPPIR->_hoops_HGGSA && _hoops_IPPIR->_hoops_HGGSA->Count() > 0) {

					_hoops_GISCA::PairList * _hoops_ARIRI = _hoops_IPPIR->_hoops_HGGSA->GetPairList();
					_hoops_ARIRI->ResetCursor();
					_hoops_GISCA::Pair * p;
					while((p = _hoops_ARIRI->PeekCursor()) != 0){
						_hoops_IHSCA * _hoops_CRHRGR = NEW(_hoops_IHSCA)(p->Item()->data, p->Item()->data_length);
						_hoops_IHSCA * _hoops_CHSCA = null;
						if (!_hoops_SPSAA->_hoops_HGGSA) 
							_hoops_SPSAA->_hoops_HGGSA = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_GISCA)(HOOPS_WORLD->memory_pool);
						_hoops_SPSAA->_hoops_HGGSA->ReplaceItem(p->Key(), _hoops_CRHRGR, &_hoops_CHSCA);
						if (_hoops_CHSCA)
							delete _hoops_CHSCA;
						_hoops_ARIRI->AdvanceCursor();
					}
					delete _hoops_ARIRI;
				}

				uc->Advance();
			}
			delete uc;
		}

		if (_hoops_ACSIH->_hoops_HGGSA != null) {

			// _hoops_HCIAA _hoops_ARP
			_hoops_IPPIR = _hoops_ACSIH;	

			if (_hoops_IPPIR->_hoops_HGGSA && _hoops_IPPIR->_hoops_HGGSA->Count() > 0) {

				_hoops_GISCA::PairList * _hoops_ARIRI = _hoops_IPPIR->_hoops_HGGSA->GetPairList();
				_hoops_ARIRI->ResetCursor();
				_hoops_GISCA::Pair * p;
				while((p = _hoops_ARIRI->PeekCursor()) != 0){
					_hoops_IHSCA * _hoops_CRHRGR = NEW(_hoops_IHSCA)(p->Item()->data, p->Item()->data_length);
					_hoops_IHSCA * _hoops_CHSCA = null;
					if (!_hoops_SPSAA->_hoops_HGGSA)
						_hoops_SPSAA->_hoops_HGGSA = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_GISCA)(HOOPS_WORLD->memory_pool);
					_hoops_SPSAA->_hoops_HGGSA->ReplaceItem(p->Key(), _hoops_CRHRGR, &_hoops_CHSCA);
					if (_hoops_CHSCA)
						delete _hoops_CHSCA;
					_hoops_ARIRI->AdvanceCursor();
				}
				delete _hoops_ARIRI;
			}
		}
	}


	if (BIT(flags, _hoops_PCIAP)) {

		_hoops_HPPIR tmp;

		ZERO_STRUCT(&tmp, _hoops_HPPIR);

		tmp.option_list = _hoops_ACSIH->option_list;
		tmp._hoops_APICA = _hoops_ACSIH->_hoops_APICA;
		tmp._hoops_AGGSA = _hoops_ACSIH->_hoops_AGGSA;
		tmp._hoops_HGGSA = _hoops_ACSIH->_hoops_HGGSA;
		tmp._hoops_IGGSA = _hoops_ACSIH->_hoops_IGGSA;

		_hoops_HPPIR * _hoops_PSHRGR = (_hoops_HPPIR *)_hoops_ACSIH;

		_hoops_PSHRGR->option_list = _hoops_SPSAA->option_list;
		_hoops_PSHRGR->_hoops_APICA = _hoops_SPSAA->_hoops_APICA;
		_hoops_PSHRGR->_hoops_AGGSA = _hoops_SPSAA->_hoops_AGGSA;
		_hoops_PSHRGR->_hoops_HGGSA = _hoops_SPSAA->_hoops_HGGSA;
		_hoops_PSHRGR->_hoops_IGGSA = _hoops_SPSAA->_hoops_IGGSA;

		_hoops_SPSAA->option_list = tmp.option_list;
		_hoops_SPSAA->_hoops_APICA = tmp._hoops_APICA;
		_hoops_SPSAA->_hoops_AGGSA = tmp._hoops_AGGSA;
		_hoops_SPSAA->_hoops_HGGSA = tmp._hoops_HGGSA;
		_hoops_SPSAA->_hoops_IGGSA = tmp._hoops_IGGSA;

		_hoops_HPRH(_hoops_SPSAA);
		return null;
	}
	else if (_hoops_ACSIH->_hoops_IGGSA)
		_hoops_ACSIH->_hoops_IGGSA->Reverse();

	return _hoops_SPSAA;
}



local int _hoops_HSHRGR (
	_hoops_PGGSA::Pair *	a,
	_hoops_PGGSA::Pair *	b,
	void const * const		data) {
	UNREFERENCED(data);

	if (a->Key() < b->Key())
		return -1;
	else if (a->Key() > b->Key())
		return 1;
	else if (a->Item() < b->Item())
		return -1;
	else if (a->Item() > b->Item())
		return 1;
	return 0;
}


local int _hoops_ISHRGR (
	_hoops_GISCA::Pair *	a,
	_hoops_GISCA::Pair *	b,
	void const * const		data) {
	UNREFERENCED(data);

	if (a->Key() < b->Key())
		return -1;
	else if (a->Key() > b->Key())
		return 1;
	return 0;
}

GLOBAL_FUNCTION bool HI_User_Option_Equal(
	_hoops_HPPIR const *		_hoops_PCSIH, 
	_hoops_HPPIR const *		_hoops_HCSIH) {

	Option_Value const *		_hoops_CSHRGR;
	Option_Value const *		_hoops_SSHRGR;
	int							_hoops_PPAIC, _hoops_HPAIC;

	if (_hoops_PCSIH->_hoops_IGGSA && 
		_hoops_PCSIH->_hoops_IGGSA->Count() == 1) {

		ASSERT(_hoops_PCSIH->option_list == null);
		ASSERT(_hoops_PCSIH->_hoops_APICA == null);
		ASSERT(_hoops_PCSIH->_hoops_AGGSA == null);
		ASSERT(_hoops_PCSIH->_hoops_HGGSA == null);

		_hoops_PCSIH = _hoops_PCSIH->_hoops_IGGSA->PeekFirst();
	}

	if (_hoops_HCSIH->_hoops_IGGSA && 
		_hoops_HCSIH->_hoops_IGGSA->Count() == 1) {

		ASSERT(_hoops_HCSIH->option_list == null);
		ASSERT(_hoops_HCSIH->_hoops_APICA == null);
		ASSERT(_hoops_HCSIH->_hoops_AGGSA == null);
		ASSERT(_hoops_HCSIH->_hoops_HGGSA == null);

		_hoops_HCSIH = _hoops_HCSIH->_hoops_IGGSA->PeekFirst();
	}

	// _hoops_PCR _hoops_PIHGR _hoops_IHHA _hoops_SRS
	
	if (_hoops_PCSIH->_hoops_IGGSA && !_hoops_HCSIH->_hoops_IGGSA ||
		!_hoops_PCSIH->_hoops_IGGSA && _hoops_HCSIH->_hoops_IGGSA ||
		(_hoops_PCSIH->_hoops_IGGSA && _hoops_HCSIH->_hoops_IGGSA &&
		 _hoops_PCSIH->_hoops_IGGSA->Count() != _hoops_HCSIH->_hoops_IGGSA->Count()))
		return false;

	if (_hoops_PCSIH->_hoops_AGGSA && !_hoops_HCSIH->_hoops_AGGSA ||
		!_hoops_PCSIH->_hoops_AGGSA && _hoops_HCSIH->_hoops_AGGSA ||
		(_hoops_PCSIH->_hoops_AGGSA && _hoops_HCSIH->_hoops_AGGSA &&
		 _hoops_PCSIH->_hoops_AGGSA->Count() != _hoops_HCSIH->_hoops_AGGSA->Count()))
		return false;
	
	if (_hoops_PCSIH->_hoops_HGGSA && !_hoops_HCSIH->_hoops_HGGSA ||
		!_hoops_PCSIH->_hoops_HGGSA && _hoops_HCSIH->_hoops_HGGSA ||
		(_hoops_PCSIH->_hoops_HGGSA && _hoops_HCSIH->_hoops_HGGSA &&
		 _hoops_PCSIH->_hoops_HGGSA->Count() != _hoops_HCSIH->_hoops_HGGSA->Count()))
		return false;

	/* _hoops_ISPR _hoops_IHHA _hoops_IIGR _hoops_AAP _hoops_CPCI */
	_hoops_PPAIC = _hoops_HPAIC = 0;
	if ((_hoops_CSHRGR = _hoops_PCSIH->option_list) != null) do
		++_hoops_PPAIC;
	while ((_hoops_CSHRGR = _hoops_CSHRGR->next) != null);
	if ((_hoops_SSHRGR = _hoops_HCSIH->option_list) != null) do
		++_hoops_HPAIC;
	while ((_hoops_SSHRGR = _hoops_SSHRGR->next) != null);
	if (_hoops_PPAIC != _hoops_HPAIC)
		return false;

	/* _hoops_PPR _hoops_PSHR _hoops_IH _hoops_GGIRGR (_hoops_CSPGA) _hoops_CPCI*/
	_hoops_PPAIC = _hoops_HPAIC = 0;
	if ((_hoops_CSHRGR = _hoops_PCSIH->_hoops_APICA) != null) do
		++_hoops_PPAIC;
	while ((_hoops_CSHRGR = _hoops_CSHRGR->next) != null);
	if ((_hoops_SSHRGR = _hoops_HCSIH->_hoops_APICA) != null) do
		++_hoops_HPAIC;
	while ((_hoops_SSHRGR = _hoops_SSHRGR->next) != null);
	if (_hoops_PPAIC != _hoops_HPAIC)
		return false;

	// _hoops_ACAHP _hoops_PCR _hoops_RH _hoops_ACIPR _hoops_ARIP

	if (_hoops_PCSIH->_hoops_IGGSA && _hoops_PCSIH->_hoops_IGGSA->Count() > 0) {

		int count = _hoops_PCSIH->_hoops_IGGSA->Count();

		bool _hoops_RGIRGR = true;

		_hoops_CGGSA::UniqueCursor *	_hoops_AGIRGR = _hoops_PCSIH->_hoops_IGGSA->GetUniqueCursor();
		_hoops_CGGSA::UniqueCursor *	_hoops_PGIRGR = _hoops_HCSIH->_hoops_IGGSA->GetUniqueCursor();

		while (count--) {
			_hoops_HPPIR const *	_hoops_ARIAS = _hoops_AGIRGR->Peek();
			_hoops_HPPIR const *	_hoops_PRIAS = _hoops_PGIRGR->Peek();

			ASSERT(_hoops_ARIAS->_hoops_IGGSA == null);
			ASSERT(_hoops_PRIAS->_hoops_IGGSA == null);

			if (!HI_User_Option_Equal(_hoops_ARIAS, _hoops_PRIAS)) {
				_hoops_RGIRGR = false;
				break;
			}
			_hoops_AGIRGR->Advance();
			_hoops_PGIRGR->Advance();
		}

		delete _hoops_AGIRGR;
		delete _hoops_PGIRGR;

		if (!_hoops_RGIRGR)
			return false;
	}

	if (_hoops_PCSIH->_hoops_AGGSA && _hoops_PCSIH->_hoops_AGGSA->Count() > 0) {

		int count = _hoops_PCSIH->_hoops_AGGSA->Count();

		_hoops_PGGSA::PairList * _hoops_AIAIC = _hoops_PCSIH->_hoops_AGGSA->GetPairList();
		_hoops_AIAIC->Sort(_hoops_HSHRGR);

		_hoops_PGGSA::PairList * _hoops_PIAIC = _hoops_HCSIH->_hoops_AGGSA->GetPairList();
		_hoops_PIAIC->Sort(_hoops_HSHRGR);

		bool _hoops_RGIRGR = true;

		_hoops_PIAIC->ResetCursor();
		_hoops_AIAIC->ResetCursor();
		while (count--) {
			_hoops_PGGSA::Pair *	_hoops_HGIRGR = _hoops_PIAIC->PeekCursor();
			_hoops_PGGSA::Pair *	_hoops_IGIRGR = _hoops_AIAIC->PeekCursor();

			if (_hoops_HGIRGR->Key() != _hoops_IGIRGR->Key() ||
				_hoops_HGIRGR->Item() != _hoops_IGIRGR->Item()) {
				_hoops_RGIRGR = false;
				break;
			}
			_hoops_PIAIC->AdvanceCursor();
			_hoops_AIAIC->AdvanceCursor();
		}
		delete _hoops_PIAIC;
		delete _hoops_AIAIC;

		if (!_hoops_RGIRGR)
			return false;
	}

	if (_hoops_PCSIH->_hoops_HGGSA && _hoops_PCSIH->_hoops_HGGSA->Count() > 0) {

		int count = _hoops_PCSIH->_hoops_HGGSA->Count();

		_hoops_GISCA::PairList * _hoops_AIAIC = _hoops_PCSIH->_hoops_HGGSA->GetPairList();
		_hoops_AIAIC->Sort(_hoops_ISHRGR);

		_hoops_GISCA::PairList * _hoops_PIAIC = _hoops_HCSIH->_hoops_HGGSA->GetPairList();
		_hoops_PIAIC->Sort(_hoops_ISHRGR);

		bool _hoops_RGIRGR = true;
		
		_hoops_PIAIC->ResetCursor();
		_hoops_AIAIC->ResetCursor();
		while (count--) {
			_hoops_GISCA::Pair *	_hoops_HGIRGR = _hoops_PIAIC->PeekCursor();
			_hoops_GISCA::Pair *	_hoops_IGIRGR = _hoops_AIAIC->PeekCursor();

			if (_hoops_HGIRGR->Key() != _hoops_IGIRGR->Key() ||
				_hoops_HGIRGR->Item()->data_length != _hoops_IGIRGR->Item()->data_length ||
				_hoops_PAGH(_hoops_HGIRGR->Item()->data, _hoops_HGIRGR->Item()->data_length, _hoops_IGIRGR->Item()->data) != 0) {
				_hoops_RGIRGR = false;
				break;
			}
			_hoops_PIAIC->AdvanceCursor();
			_hoops_AIAIC->AdvanceCursor();
		}
		delete _hoops_PIAIC;
		delete _hoops_AIAIC;

		if (!_hoops_RGIRGR)
			return false;
	}

	/* _hoops_CICAR _hoops_PPS _hoops_IIGR _hoops_AAP */
	if ((_hoops_CSHRGR = _hoops_PCSIH->option_list) != null) do {
		if ((_hoops_SSHRGR = _hoops_HCSIH->option_list) != null) do {
			if (_hoops_CSHRGR->type->id == _hoops_SSHRGR->type->id &&
				_hoops_CSHRGR->_hoops_GCACR == _hoops_SSHRGR->_hoops_GCACR &&
				(_hoops_CSHRGR->value._name == null && _hoops_SSHRGR->value._name == null ||
				 _hoops_CSHRGR->value._name != null && _hoops_SSHRGR->value._name != null &&
				 _hoops_RAHSR(*_hoops_CSHRGR->value._name, *_hoops_SSHRGR->value._name)))
				break;
		} while ((_hoops_SSHRGR = _hoops_SSHRGR->next) != null);
		
		if (_hoops_SSHRGR == null)	/* _hoops_PSP _hoops_PSSP */
			return false;
	} while ((_hoops_CSHRGR = _hoops_CSHRGR->next) != null);

	/* _hoops_PPR _hoops_GGIRGR */
	if ((_hoops_CSHRGR = _hoops_PCSIH->_hoops_APICA) != null) do {
		if ((_hoops_SSHRGR = _hoops_HCSIH->_hoops_APICA) != null) do {
			if (_hoops_CSHRGR->type->id == _hoops_SSHRGR->type->id &&
				_hoops_CSHRGR->_hoops_GCACR == _hoops_SSHRGR->_hoops_GCACR &&
				(_hoops_CSHRGR->value._hoops_HGSAP == null && _hoops_SSHRGR->value._hoops_HGSAP == null ||
				 _hoops_CSHRGR->value._hoops_HGSAP != null && _hoops_SSHRGR->value._hoops_HGSAP != null &&
				 _hoops_RARPH(*_hoops_CSHRGR->value._hoops_HGSAP, *_hoops_SSHRGR->value._hoops_HGSAP)))
				break;
		} while ((_hoops_SSHRGR = _hoops_SSHRGR->next) != null);
		
		if (_hoops_SSHRGR == null)	/* _hoops_PSP _hoops_PSSP */
			return false;
	} while ((_hoops_CSHRGR = _hoops_CSHRGR->next) != null);

	return true;
}




local Attribute *_hoops_CGIRGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR) 
{
	_hoops_RHPIR const *		_hoops_GIAGP = (_hoops_RHPIR const *)_hoops_CPACR;
	_hoops_RHPIR alter *		_hoops_PIAGP = (_hoops_RHPIR alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (item);

	if (_hoops_GIAGP != null &&
		_hoops_GIAGP->data == _hoops_PIAGP->data)
		return null;
	
	return _hoops_PIAGP;
}

GLOBAL_FUNCTION bool HI_Set_User_Value (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_RHPIR *			_hoops_CGGCH)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_USER_VALUE, _hoops_CGIRGR, _hoops_CGGCH);
}


HC_INTERFACE void HC_CDECL HC_Set_User_Value (
	POINTER_SIZED_INT		data) {

	_hoops_PAPPR context("Set_User_Value");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Set_User_Value (0x%X);\n", data));
	);

	bool			used = false;
	_hoops_RHPIR *	_hoops_CGGCH;
	ZALLOC (_hoops_CGGCH, _hoops_RHPIR);

	_hoops_CGGCH->data = data;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_CHRPP|_hoops_GSIIR)) != null) {
		used = HI_Set_User_Value (context, target, _hoops_CGGCH);
		_hoops_IRRPR();
	}

	if (!used)
		FREE (_hoops_CGGCH, _hoops_RHPIR);
}



HC_INTERFACE void HC_CDECL HC_UnSet_User_Value (void) 
{
	_hoops_PAPPR context("UnSet_User_Value");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_User_Value ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_CHRPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute (context, target, HK_USER_VALUE);
		_hoops_IRRPR();
	}
}




HC_INTERFACE void HC_CDECL HC_Show_User_Value (
	POINTER_SIZED_INT *	data)
{
	_hoops_PAPPR context("Show_User_Value");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_User_Value () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HGAPP)) != null) {

		_hoops_RHPIR *	_hoops_CGGCH;
		if ((_hoops_CGGCH = (_hoops_RHPIR *)HI_Find_Attribute (context, target, HK_USER_VALUE)) != null) {
			*data = _hoops_CGGCH->data;
			_hoops_HPRH (_hoops_CGGCH);
		}
		_hoops_IRRPR();
	}
#endif
}



#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_User_Value (
	int						count,
	Key const *				keys,
	POINTER_SIZED_INT *		data) 
{
	_hoops_PAPPR context("PShow_User_Value");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_User_Value () */\n");
	);

	_hoops_RHPIR *	_hoops_CGGCH;
	if ((_hoops_CGGCH = (_hoops_RHPIR *) HI_Find_Attribute_And_Lock(context, _hoops_HGAPP, _hoops_HRPCR, count, keys)) != null) {
		*data = _hoops_CGGCH->data;
		_hoops_HPRH (_hoops_CGGCH);
		_hoops_IRRPR();
	}
	else
		*data = 0;

#endif
}
#endif


GLOBAL_FUNCTION bool HI_Show_One_User_Option_By_Key(_hoops_AIGPR * _hoops_RIGC, Key key, char const * uoname, char * options)
{
	_hoops_RSIIR(_hoops_RIGC);

	_hoops_HPAH *	thing = (_hoops_HPAH *)_hoops_RCSSR (_hoops_RIGC, key);

	_hoops_HPPIR *	user_options;
	if ((user_options = (_hoops_HPPIR *)HI_Find_Attribute(_hoops_RIGC, thing, HK_USER_OPTIONS)) != null) {
		bool result = _hoops_CHHRGR (_hoops_RIGC, user_options, true, null, uoname, options, -1);
		_hoops_HPRH (user_options);
		return result;
	}

	HI_Return_Chars(options, -1, "", 0);
	return false;
}

GLOBAL_FUNCTION bool HI_PShow_One_Net_User_Option(_hoops_AIGPR * _hoops_RIGC, int count, Key const * keys, char const * uoname, char * options)
{
	_hoops_RSIIR(_hoops_RIGC);
	_hoops_HPPIR *	user_options;
	if ((user_options = (_hoops_HPPIR *)HI_Find_Attribute_And_Lock(_hoops_RIGC, _hoops_PGAPP, _hoops_HRPCR|_hoops_SRGPP, count, keys)) != null) {
		bool result = _hoops_CHHRGR (_hoops_RIGC, user_options, true, null, uoname, options, -1);
		_hoops_HPRH (user_options);
		return result;
	}

	HI_Return_Chars(options, -1, "", 0);
	return false;
}


GLOBAL_FUNCTION void HI_Show_One_User_Data_By_Key(
	_hoops_AIGPR *	_hoops_RIGC, 
	Key						key, 										  
	POINTER_SIZED_INT		index, 
	void *					data, 
	long					data_length, 
	long *					data_length_out)
{
	_hoops_RSIIR(_hoops_RIGC);

	*data_length_out = 0;

	_hoops_HPAH *	thing = (_hoops_HPAH *)_hoops_RCSSR (_hoops_RIGC, key);

	_hoops_HPPIR *	user_options;

	if ((user_options = (_hoops_HPPIR *)HI_Find_Attribute(_hoops_RIGC, thing, -HK_USER_OPTIONS)) != null) {
		*data_length_out = _hoops_HCHRGR (_hoops_RIGC, user_options, index, data, data_length);
		_hoops_HPRH (user_options);
	}
}

GLOBAL_FUNCTION void HI_PShow_One_Net_User_Data(
	_hoops_AIGPR *	_hoops_RIGC, 
	int						count, 
	Key const *				keys, 										
	POINTER_SIZED_INT		index, 
	void *					data, 
	long					data_length, 
	long *					data_length_out)
{
	_hoops_RSIIR(_hoops_RIGC);

	*data_length_out = 0;

	_hoops_HPPIR *	user_options;
	if ((user_options = (_hoops_HPPIR *)HI_Find_Attribute_And_Lock(_hoops_RIGC, _hoops_PGAPP|_hoops_SRGPP, _hoops_HRPCR|_hoops_CSCAP, count, keys)) != null) {
		*data_length_out = _hoops_HCHRGR (_hoops_RIGC, user_options, index, data, data_length);
		_hoops_HPRH (user_options);
	}
}

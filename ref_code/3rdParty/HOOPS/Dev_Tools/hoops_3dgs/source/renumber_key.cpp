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
 * $Id: obf_tmp.txt 1.95 2010-10-22 22:17:11 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


INLINE int	_hoops_RSCRS (POINTER_SIZED_INT value)	{ return (int)(value | (value >> 16)) & 0x0000FFFF;	}

INLINE int	_hoops_RSCRS (Key * value)				{ return _hoops_RSCRS ((POINTER_SIZED_INT)value);	}

INLINE int	_hoops_RSCRS (void const * owner, Key value)
													{ return _hoops_RSCRS ((POINTER_SIZED_INT)owner) +
															 _hoops_RSCRS ((POINTER_SIZED_INT)value);	}




GLOBAL_FUNCTION Key HI_Key_To_Internal (
	_hoops_AIGPR *		_hoops_RIGC,
	Key							key,
	_hoops_CRCP const *				_hoops_SRCP) 
{

	// _hoops_AGSAH _hoops_GGR _hoops_AGIR _hoops_AICRR _hoops_RAIA _hoops_SSPP
	if (key <= _hoops_SHSSR)
		return key;

	if (HOOPS_WORLD->_hoops_CCPGI.table != null) {
		_hoops_GPPGI *			_hoops_CCPGI = &HOOPS_WORLD->_hoops_CCPGI;

		if (_hoops_SRCP == null && _hoops_RIGC->open_list != null && _hoops_RIGC->open_list->_hoops_GCRIR == _hoops_RCRIR)
			_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_PCRIR;

		int	_hoops_GCAH = _hoops_RSCRS (_hoops_SRCP, key);
		_hoops_GCAH &= _hoops_CCPGI->size - 1;

		_hoops_PSSAP *	node = _hoops_CCPGI->table[_hoops_GCAH];

		if (node != null) do {
			if (node->_hoops_HSSAP == key  &&
				node->owner == (_hoops_HPAH *)_hoops_SRCP)
				return	node->original;
		} while ((node = node->next) != null);
	}


	_hoops_GPPGI *	global_keys = &_hoops_RSPPR(_hoops_RIGC, global_keys);

	if (global_keys->table != null) {

		int	_hoops_GCAH = _hoops_RSCRS (key);
		_hoops_GCAH &= global_keys->size - 1;

		_hoops_PSSAP *	node = global_keys->table[_hoops_GCAH];

		if (node != null) do {
			if (node->_hoops_HSSAP == key)
				return	node->original;
		} while ((node = node->next) != null);
	}

	// _hoops_PSP _hoops_PSSP -- _hoops_RIHH _hoops_CGH _hoops_SHH _hoops_CRPPR _hoops_HPP _hoops_CIS
	return	_hoops_SHSSR;
}


GLOBAL_FUNCTION bool HI_Has_Local_Key (
	_hoops_CRCP const *				owner,
	Key							_hoops_HSICA) {
	int							_hoops_GCAH;
	_hoops_PSSAP *					node;
	_hoops_GPPGI *					_hoops_CCPGI = &HOOPS_WORLD->_hoops_CCPGI;

	if (owner->type == _hoops_PRAIR || _hoops_CCPGI->table == null)
		return false;


	_hoops_GCAH = _hoops_RSCRS (owner, _hoops_HSICA);
	_hoops_GCAH &= _hoops_CCPGI->size - 1;

	node = _hoops_CCPGI->table[_hoops_GCAH];

	if (node != null) do {
		if (node->_hoops_HSSAP == _hoops_HSICA &&
			node->owner == (_hoops_HPAH *)owner)
			return	true;
	} while ((node = node->next) != null);


	return	false;
}


#define _hoops_ASCRS	2


HC_INTERFACE Key HC_CDECL HC_Renumber_Key (
	Key						old_key,
	Key						new_key,
	char const *			scope) 
{
	_hoops_PAPPR context("Renumber_Key");

	Key	_hoops_CHSSR = _hoops_SHSSR;

	int	offset;

	_hoops_CSPPR();

	/* _hoops_ISPR _hoops_PSCRS */
	_hoops_HPAH *	item = _hoops_SISIR (context, old_key, &offset);

	if (item == null || BIT (item->_hoops_RRHH, _hoops_HGAGR) ||
		(item->type < _hoops_AHRIR || item->type > _hoops_PHRIR) &&
		item->type != _hoops_AGRPR && item->type != _hoops_IRCP &&
		item->type != HK_STYLE) {
		HE_ERROR2 (HEC_RENUMBER_KEY, HES_INVALID_INPUT,
				Sprintf_LD (null,"Old key (%D) does not refer to a valid item", old_key),
						"	 (segment, style, include, or geometry)");
	}
	else if (item->owner == null) {
		HI_Not_When_LOD ();
	}
	else {

		int						_hoops_GCAH;
		_hoops_PSSAP *				node;
		int *					mapping = null;
		int						index = 0;

		Key _hoops_RACII = _hoops_AIRIR (item);
		Key _hoops_HSCRS = item->key;

		if (BIT (item->_hoops_RRHH, _hoops_CHRIR)) {
			if (item->type == _hoops_HIIP)
				mapping = ((_hoops_SHRIR *)item)->mapping;
			else if (item->type == _hoops_PIRS)
				mapping = ((_hoops_GRPGR *)item)->mapping;

			index = mapping[offset] & ~_hoops_RIRIR;
			_hoops_RACII = ~(POINTER_SIZED_INT)index;
			_hoops_HSCRS = HOOPS_WORLD->_hoops_GCHCA.table[index].key;
		}

		/* _hoops_GRH _hoops_AGIR _hoops_IS _hoops_PHIH _hoops_GIGR _hoops_SIC */
		if (new_key == _hoops_SHSSR || new_key == _hoops_RACII) {
			if (_hoops_HSCRS > _hoops_SHSSR)
				HI_Delete_User_Key (context, item, _hoops_HSCRS);			/* _hoops_HSCI _hoops_RH _hoops_RHGS _hoops_IPSP-_hoops_SIC */

			if (BIT (item->_hoops_RRHH, _hoops_CHRIR))
				HOOPS_WORLD->_hoops_GCHCA.table[index].key = _hoops_RACII;
			else
				item->key = _hoops_RACII;

			_hoops_CHSSR = _hoops_RACII;
		}
		/* _hoops_ISPR _hoops_SICGS */
		else if (new_key < 0) {
			HE_ERROR (HEC_RENUMBER_KEY, HES_INVALID_INPUT,
					  Sprintf_LD (null, "'%D' is not a valid user key (cannot be a negative value)", new_key));
			_hoops_CHSSR = _hoops_HSCRS;
		}
		/* _hoops_GSRGR _hoops_SICGS _hoops_SIC _hoops_GGR _hoops_IRPR _hoops_GASR */
		else if (*scope == 'l'	||	*scope == 'L') {
			if (item->owner->type == _hoops_PRAIR) {
				HE_ERROR (HEC_RENUMBER_KEY, HES_ORPHAN_SEGMENT, "The segment '/' has no owner, so may not have a local key.");
				_hoops_CHSSR = _hoops_HSCRS;
			}
			else {
				/* _hoops_IRHH _hoops_RCRR _hoops_IIH _hoops_HRGR _hoops_PSP _hoops_RAGS */
				_hoops_GPPGI *			_hoops_CCPGI = &HOOPS_WORLD->_hoops_CCPGI;

				if (_hoops_CCPGI->table != null) {
					_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);
					_hoops_GCAH = _hoops_RSCRS (item->owner, new_key);
					_hoops_GCAH &= _hoops_CCPGI->size - 1;
					node = _hoops_CCPGI->table[_hoops_GCAH];

					if (node != null) do {
						if (node->_hoops_HSSAP == new_key &&
							node->owner == item->owner &&
							_hoops_RCSSR (context, node->original) != item) {
							HE_ERROR (HEC_RENUMBER_KEY, HES_NUMBER_ALREADY_IN_USE,
									  Sprintf_LD (null, "There is already an object locally numbered %D with the same parent", new_key));
							_hoops_CHSSR = _hoops_HSCRS;
							break;
						}
					} while ((node = node->next) != null);
					_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);
				}
			}

			if (_hoops_CHSSR == _hoops_SHSSR) {	// _hoops_SARS'_hoops_RA _hoops_RHHR _hoops_HIGSA _hoops_AGIR
				HI_Set_User_Key (context, item, offset, new_key, true);
				_hoops_CHSSR = new_key;
			}
		}
		else {		/* _hoops_HRSAR */
			/* _hoops_IRHH _hoops_RCRR _hoops_IIH _hoops_HRGR _hoops_PSP _hoops_RAGS */
			_hoops_GPPGI *			global_keys;

			global_keys = &_hoops_RSPPR(context, global_keys);

			if (global_keys->table != null) {
				_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);
				_hoops_GCAH = _hoops_RSCRS (new_key);
				_hoops_GCAH &= global_keys->size - 1;
				node = global_keys->table[_hoops_GCAH];

				if (node != null) do {
					if (node->_hoops_HSSAP == new_key &&
						_hoops_RCSSR (context, node->original) != item) {
						HE_ERROR (HEC_RENUMBER_KEY, HES_NUMBER_ALREADY_IN_USE,
								  Sprintf_LD (null, "There is already an object globally numbered %D", new_key));
						_hoops_CHSSR = _hoops_HSCRS;
					}
				} while ((node = node->next) != null);
				_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);
			}

			if (_hoops_CHSSR == _hoops_SHSSR) {	// _hoops_SARS'_hoops_RA _hoops_RHHR _hoops_HIGSA _hoops_AGIR
				HI_Set_User_Key (context, item, offset, new_key, false);
				_hoops_CHSSR = new_key;
			}
		}
	}

	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Renumber_Key (LOOKUP (%D), ", old_key));
		HI_Dump_Code (Sprintf_LD (null, "%D, ", new_key));
		HI_Dump_Code (Sprintf_S (null, "%S, ", scope));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
	);

	return _hoops_CHSSR;
}


local _hoops_PSSAP ** _hoops_PIIGS (
	Integer32					count) {
	_hoops_PSSAP **					table;

	ZALLOC_ARRAY (table, count, _hoops_PSSAP *);

	return table;
}


GLOBAL_FUNCTION void HI_Set_User_Key (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH *					item,
	int							offset,
	Key							new_key,
	bool						_hoops_HSCIH) 
{
	Key							_hoops_RACII = _hoops_AIRIR (item);
	int							_hoops_GCAH;
	_hoops_PSSAP *					node;
	_hoops_PSSAP **					table;

	if (BIT (item->_hoops_RRHH, _hoops_CHRIR)) {
		int *					mapping = null;

		if (item->type == _hoops_HIIP)
			mapping = ((_hoops_SHRIR *)item)->mapping;
		else if (item->type == _hoops_PIRS)
			mapping = ((_hoops_GRPGR *)item)->mapping;

		int						index = mapping[offset] & ~_hoops_RIRIR;
		_hoops_RACII = HOOPS_WORLD->_hoops_GCHCA.table[index].key;

		if (item->key > _hoops_SHSSR)
			HI_Delete_User_Key (_hoops_RIGC, item);				/* _hoops_HSCI _hoops_GII _hoops_RHGS _hoops_IPSP-_hoops_SIC */
		HOOPS_WORLD->_hoops_GCHCA.table[index].key = new_key;
	}
	else {
		if (item->key > _hoops_SHSSR)
			HI_Delete_User_Key (_hoops_RIGC, item);				/* _hoops_HSCI _hoops_GII _hoops_RHGS _hoops_IPSP-_hoops_SIC */
		item->key = new_key;
	}

	_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);

	if (_hoops_HSCIH) {
		_hoops_GPPGI *				_hoops_CCPGI = &HOOPS_WORLD->_hoops_CCPGI;

		if ((table = _hoops_CCPGI->table) == null) {
			_hoops_CCPGI->table = table = _hoops_PIIGS (_hoops_APRGI);
			_hoops_CCPGI->size = _hoops_APRGI;
		}
		else if (_hoops_CCPGI->_hoops_SAPGI >	8 * _hoops_CCPGI->size) {
			_hoops_PSSAP **			current;
			_hoops_PSSAP **			_hoops_GCGCC = table;
			Integer32			tmp;
			Integer32			_hoops_CIGRR = _hoops_CCPGI->size;

			_hoops_CCPGI->size = _hoops_ASCRS * _hoops_CIGRR;
			_hoops_CCPGI->table = table = _hoops_PIIGS (_hoops_CCPGI->size);

			current = _hoops_GCGCC;
			tmp = _hoops_CIGRR;
			do {
				while ((node = *current) != null) {
					_hoops_GCAH = _hoops_RSCRS (node->owner, node->_hoops_HSSAP);
					_hoops_GCAH &= _hoops_CCPGI->size - 1;

					*current = node->next;
					node->next = _hoops_CCPGI->table[_hoops_GCAH];
					_hoops_CCPGI->table[_hoops_GCAH] = node;
				}
				++current;
			} while (--tmp > 0);
			FREE_ARRAY (_hoops_GCGCC, _hoops_CIGRR, _hoops_PSSAP *);
		}

		_hoops_GCAH = _hoops_RSCRS (item->owner, new_key);
		_hoops_GCAH &= _hoops_CCPGI->size - 1;

		ALLOC (node, _hoops_PSSAP);
		node->owner = item->owner;
		node->_hoops_HSSAP = new_key;
		node->original = _hoops_RACII;

		node->next = table[_hoops_GCAH];
		table[_hoops_GCAH] = node;

		++_hoops_CCPGI->_hoops_SAPGI;
	}
	else {
		_hoops_GPPGI *				global_keys;
		
		global_keys = &_hoops_RSPPR(_hoops_RIGC, global_keys);

		if ((table = global_keys->table) == null) {
			global_keys->table = table = _hoops_PIIGS (_hoops_APRGI);
			global_keys->size = _hoops_APRGI;
		}
		else if (global_keys->_hoops_SAPGI >	8 * global_keys->size) {

			_hoops_PSSAP **			current;
			_hoops_PSSAP **			_hoops_GCGCC = table;
			Integer32			tmp;
			Integer32			_hoops_CIGRR = global_keys->size;

			global_keys->size = _hoops_ASCRS * _hoops_CIGRR;
			global_keys->table = table = _hoops_PIIGS (global_keys->size);

			current = _hoops_GCGCC;
			tmp = _hoops_CIGRR;
			do {
				while ((node = *current) != null) {
					_hoops_GCAH = _hoops_RSCRS (node->_hoops_HSSAP);
					_hoops_GCAH &= global_keys->size - 1;

					*current = node->next;
					node->next = global_keys->table[_hoops_GCAH];
					global_keys->table[_hoops_GCAH] = node;
				}
				++current;
			} while (--tmp > 0);
			FREE_ARRAY (_hoops_GCGCC, _hoops_CIGRR, _hoops_PSSAP *);
		}

		_hoops_GCAH = _hoops_RSCRS (new_key);
		_hoops_GCAH &= global_keys->size - 1;

		ALLOC (node, _hoops_PSSAP);
		node->owner = item->owner;
		node->_hoops_HSSAP = new_key;
		node->original = _hoops_RACII;

		node->next = table[_hoops_GCAH];
		table[_hoops_GCAH] = node;

		++global_keys->_hoops_SAPGI;
	}

	_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);
}


GLOBAL_FUNCTION void HI_Delete_User_Key (
	_hoops_AIGPR *		_hoops_RIGC, 
	_hoops_HPAH *					item,
	Key							_hoops_HSICA) {
	int							_hoops_GCAH;
	_hoops_PSSAP **					node;
	bool						_hoops_ISCRS = true;

	if (_hoops_HSICA == _hoops_SHSSR)
		_hoops_HSICA = item->key;

	_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);

	if (item->owner->type != _hoops_PRAIR && HOOPS_WORLD->_hoops_CCPGI.table != null) {
		_hoops_GPPGI *			_hoops_CCPGI = &HOOPS_WORLD->_hoops_CCPGI;

		_hoops_GCAH = _hoops_RSCRS (item->owner, _hoops_HSICA);
		_hoops_GCAH &= _hoops_CCPGI->size - 1;

		node = &_hoops_CCPGI->table[_hoops_GCAH];

		if (*node != null) do {
			if ((*node)->owner == item->owner &&
				((*node)->original == _hoops_HSICA ||
				 (*node)->_hoops_HSSAP == _hoops_HSICA)) {
				_hoops_PSSAP *		tmp;

				tmp = *node;
				*node = tmp->next;
				FREE (tmp, _hoops_PSSAP);

				--_hoops_CCPGI->_hoops_SAPGI;
				_hoops_ISCRS = false;
				break;
			}
		} while (*(node = &(*node)->next) != null);
	}

	if (_hoops_ISCRS) {
		_hoops_GPPGI *				global_keys;

		global_keys = &_hoops_RSPPR(_hoops_RIGC, global_keys);

		if (global_keys->table != null) {
			_hoops_GCAH = _hoops_RSCRS (_hoops_HSICA);
			_hoops_GCAH &= global_keys->size - 1;

			node = &global_keys->table[_hoops_GCAH];

			if (*node != null) do {
				if ((*node)->original == _hoops_HSICA ||
					(*node)->_hoops_HSSAP == _hoops_HSICA) {
					_hoops_PSSAP		*tmp;

					tmp = *node;
					*node = tmp->next;
					FREE (tmp, _hoops_PSSAP);

					--global_keys->_hoops_SAPGI;
					break;
				}
			} while (*(node = &(*node)->next) != null);
		}
	}

	_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);
}

// _hoops_AAAHH _hoops_SIC -> _hoops_IGCI/_hoops_SHI _hoops_GASR _hoops_PSCH
// _hoops_AAAHH _hoops_RSHIC _hoops_GRS _hoops_RRP _hoops_IS _hoops_ASH _hoops_PCCP _hoops_CRPR _hoops_IIGR _hoops_CRGIA _hoops_RSHCR _hoops_IS _hoops_RH _hoops_SCSHR (_hoops_IGCI/_hoops_SHI -> _hoops_AAAHH _hoops_SIC)

GLOBAL_FUNCTION int HI_Record_Lightweight_Key (
	_hoops_HPAH *					item,
	int							offset,
	int							index) {

	if (index == -1) {
		if (HOOPS_WORLD->_hoops_GCHCA._hoops_CRIGP != null) {
			index = HOOPS_WORLD->_hoops_GCHCA._hoops_CRIGP - HOOPS_WORLD->_hoops_GCHCA.table;
			HOOPS_WORLD->_hoops_GCHCA._hoops_CRIGP = HOOPS_WORLD->_hoops_GCHCA._hoops_CRIGP->_hoops_HPPGI;
		}
		else {
			if (HOOPS_WORLD->_hoops_GCHCA.count == HOOPS_WORLD->_hoops_GCHCA.allocated) {
				_hoops_PPPGI *				_hoops_GCGCC = HOOPS_WORLD->_hoops_GCHCA.table;
				int						_hoops_CIGRR = HOOPS_WORLD->_hoops_GCHCA.allocated;

				if (HOOPS_WORLD->_hoops_GCHCA.allocated == 0)
					HOOPS_WORLD->_hoops_GCHCA.allocated = 1024;
				else
					HOOPS_WORLD->_hoops_GCHCA.allocated = (int)((float)HOOPS_WORLD->_hoops_GCHCA.allocated * 1.6180339887f);

				ZALLOC_ARRAY (HOOPS_WORLD->_hoops_GCHCA.table, HOOPS_WORLD->_hoops_GCHCA.allocated, _hoops_PPPGI);

				if (_hoops_GCGCC != null) {
					_hoops_AIGA (_hoops_GCGCC, _hoops_CIGRR, _hoops_PPPGI, HOOPS_WORLD->_hoops_GCHCA.table);
					FREE_ARRAY (_hoops_GCGCC, _hoops_CIGRR, _hoops_PPPGI);
				}
				else {
					// _hoops_HRIAA 0 _hoops_RARP _hoops_PGAP _hoops_CHH _hoops_ARCR _hoops_IS _hoops_HPAP _hoops_ICGSA _hoops_PIRA _hoops_IIGR -1
					HOOPS_WORLD->_hoops_GCHCA.table[0].item = null;
					HOOPS_WORLD->_hoops_GCHCA.table[0].key = _hoops_SHSSR;
					HOOPS_WORLD->_hoops_GCHCA.table[0].offset = -666;
					++HOOPS_WORLD->_hoops_GCHCA.count;
				}
			}

			index = HOOPS_WORLD->_hoops_GCHCA.count++;
		}
	}

	HOOPS_WORLD->_hoops_GCHCA.table[index].item = item;
	HOOPS_WORLD->_hoops_GCHCA.table[index].key = ~(POINTER_SIZED_INT)index;
	HOOPS_WORLD->_hoops_GCHCA.table[index].offset = offset;

	return index;
}

GLOBAL_FUNCTION void HI_Replace_Lightweight_Key (
	int							index,
	_hoops_HPAH *					item,
	int							offset) {

	if (index <= 0 || index >= HOOPS_WORLD->_hoops_GCHCA.count ||
		HOOPS_WORLD->_hoops_GCHCA.table[index].offset < 0)
		return;		// _hoops_IAIGH _hoops_SASRR?

	HOOPS_WORLD->_hoops_GCHCA.table[index].item = item;
	HOOPS_WORLD->_hoops_GCHCA.table[index].offset = offset;
}

GLOBAL_FUNCTION void HI_Remove_Lightweight_Key (
	int							index) {

	if (index <= 0 || index >= HOOPS_WORLD->_hoops_GCHCA.count ||
		HOOPS_WORLD->_hoops_GCHCA.table[index].offset < 0)
		return;		// _hoops_AIPH _hoops_CIHA _hoops_PAR _hoops_RARP _hoops_AIAH _hoops_HGGPR

	if (index == HOOPS_WORLD->_hoops_GCHCA.count - 1)
		--HOOPS_WORLD->_hoops_GCHCA.count;		// _hoops_PIHGR, _hoops_PHRI _hoops_PAHH _hoops_IIIHC
	else {
		HOOPS_WORLD->_hoops_GCHCA.table[index]._hoops_HPPGI = HOOPS_WORLD->_hoops_GCHCA._hoops_CRIGP;
		HOOPS_WORLD->_hoops_GCHCA.table[index].key = _hoops_SHSSR;	// _hoops_RIP _hoops_AIPH
		HOOPS_WORLD->_hoops_GCHCA.table[index].offset = -1;		// _hoops_RIP _hoops_AIPH

		HOOPS_WORLD->_hoops_GCHCA._hoops_CRIGP = &HOOPS_WORLD->_hoops_GCHCA.table[index];
	}
}

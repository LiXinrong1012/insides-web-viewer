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
 * $Id: obf_tmp.txt 1.141 2010-12-09 00:20:04 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "path.h"
#include "hi_proto.h"
#include "hc_proto.h"
#include "hpserror.h"
#include "adt.h"


const int	_hoops_HRASA	= 0;
const int	_hoops_IRASA	= 1;
const int	_hoops_CRASA	= -1;
#define	_hoops_SRASA(x)	(1-x)

struct _hoops_GAASA {
	_hoops_GAASA *		_hoops_RAASA[2];
	Subsegment *		item;
	int					priority;
	int					bias;
};

Begin_HOOPS_Namespace
	struct _hoops_AAASA {
		_hoops_GAASA *	_hoops_PAASA;
		_hoops_GAASA *	_hoops_HAASA;
		bool			_hoops_IAASA;
		bool			_hoops_CAASA;
	};
End_HOOPS_Namespace;

local int _hoops_HGA (int bias, int priority, char const * name, Subsegment * _hoops_GIPIA, _hoops_GAASA * tree) {
	if (bias < tree->bias)
		return _hoops_HRASA;
	else if (bias > tree->bias)
		return _hoops_IRASA;

	if (priority < tree->priority)
		return _hoops_HRASA;
	else if (priority > tree->priority)
		return _hoops_IRASA;

	Type		_hoops_SAASA = _hoops_GIPIA != null ? _hoops_GIPIA->type : _hoops_IRCP;

	if (_hoops_SAASA < tree->item->type)
		return _hoops_HRASA;
	else if (_hoops_SAASA > tree->item->type)
		return _hoops_IRASA;

	_hoops_CRCP const *	_hoops_SRCP = null;

	if (tree->item->type == _hoops_IRCP)
		_hoops_SRCP = (_hoops_CRCP const *)tree->item;

	if (name != null) {
		if (_hoops_SRCP != null && _hoops_SRCP->name.length > 0) {
			int		cmp = _hoops_GPASA (name, _hoops_SRCP->name.text);

			if (cmp < 0)
				return _hoops_HRASA;
			else if (cmp > 0)
				return _hoops_IRASA;
		}
		else
			return _hoops_IRASA;
	}
	else if (_hoops_SRCP != null && _hoops_SRCP->name.length > 0)
		return _hoops_HRASA;
	else {
		if (_hoops_GIPIA < tree->item)
			return _hoops_HRASA;
		else if (_hoops_GIPIA > tree->item)
			return _hoops_IRASA;
	}

	return _hoops_CRASA;
}




/*---------------------------------------------------------------------------*/

local _hoops_GAASA * _hoops_RPASA (int bias, int priority, Subsegment * item) {
	_hoops_GAASA *			node;

	ALLOC (node, _hoops_GAASA);
	ZERO_STRUCT (node, _hoops_GAASA);

	node->item = item;
	node->priority = priority;
	node->bias = bias;

	return node;
}

local void _hoops_APASA (_hoops_GAASA *node) {
	FREE (node, _hoops_GAASA);
}

/*---------------------------------------------------------------------------*/

local _hoops_GAASA * _hoops_PPASA (_hoops_GAASA *tree, int direction) {
	_hoops_GAASA *save = tree->_hoops_RAASA[direction];

	tree->_hoops_RAASA[direction] = save->_hoops_RAASA[_hoops_SRASA(direction)];
	save->_hoops_RAASA[_hoops_SRASA(direction)] = tree;

	return save;
}

/*---------------------------------------------------------------------------*/

local _hoops_GAASA * _hoops_HPASA (_hoops_GAASA *tree, int bias, int priority, char const * name, Subsegment * item) {
	_hoops_GAASA		_hoops_HCIS;
	_hoops_GAASA *	temps[2];
	int				direction;

	if (tree == null)
		return tree;

	ZERO_STRUCT (&_hoops_HCIS, _hoops_GAASA);
	temps[_hoops_HRASA] = temps[_hoops_IRASA] = &_hoops_HCIS;

	while (item != tree->item && (direction = _hoops_HGA (bias, priority, name, item, tree)) != _hoops_CRASA) {
		if (tree->_hoops_RAASA[direction] == null)
			break;

		if (_hoops_HGA (bias, priority, name, item, tree->_hoops_RAASA[direction]) == direction) {
			tree = _hoops_PPASA (tree, direction);

			if (tree->_hoops_RAASA[direction] == null)
				break;
		}

		temps[_hoops_SRASA(direction)]->_hoops_RAASA[direction] = tree;
		temps[_hoops_SRASA(direction)] = tree;
		tree = tree->_hoops_RAASA[direction];
	}

	/* _hoops_IPASA */
	temps[_hoops_HRASA]->_hoops_RAASA[_hoops_IRASA] = tree->_hoops_RAASA[_hoops_HRASA];
	temps[_hoops_IRASA]->_hoops_RAASA[_hoops_HRASA] = tree->_hoops_RAASA[_hoops_IRASA];
	tree->_hoops_RAASA[_hoops_HRASA] = _hoops_HCIS._hoops_RAASA[_hoops_IRASA];
	tree->_hoops_RAASA[_hoops_IRASA] = _hoops_HCIS._hoops_RAASA[_hoops_HRASA];

	return tree;
}

/*---------------------------------------------------------------------------*/

local _hoops_GAASA * _hoops_CPASA (_hoops_GAASA *tree, int bias, int priority, char const * name, Subsegment * item) {
	_hoops_GAASA *	node = _hoops_RPASA (bias, priority, item);
	char const *	_hoops_SPASA;

	if (tree == null)
		return node;

	tree = _hoops_HPASA (tree, bias, priority, name, item);

	_hoops_SPASA = null;
	if (tree->item->type == _hoops_IRCP) {
		_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *)tree->item;

		if (_hoops_SRCP->name.length != 0)
			_hoops_SPASA = _hoops_SRCP->name.text;
	}

	if (bias == tree->bias &&
		priority == tree->priority &&
		(item == tree->item || item == null && _hoops_AGGR (name, _hoops_SPASA))) {
		_hoops_APASA (node);

		return tree;
	}
	else {
		int direction = _hoops_HGA (bias, priority, name, item, tree);

		node->_hoops_RAASA[direction] = tree->_hoops_RAASA[direction];
		node->_hoops_RAASA[_hoops_SRASA(direction)] = tree;
		tree->_hoops_RAASA[direction] = null;

		return node;
	}
}

local _hoops_GAASA * _hoops_GHASA (_hoops_GAASA *tree, int bias, int priority, Subsegment * item) {
	char const *	name = null;

	if (tree == null)
		return null;

	if (item != null && item->type == _hoops_IRCP) {
		_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *)item;

		if (_hoops_SRCP->name.length != 0)
			name = _hoops_SRCP->name.text;
	}

	tree = _hoops_HPASA (tree, bias, priority, name, item);

	if (bias == tree->bias && priority == tree->priority && item == tree->item) {
		_hoops_GAASA *	tmp;

		if (tree->_hoops_RAASA[_hoops_HRASA] == null)
			tmp = tree->_hoops_RAASA[_hoops_IRASA];
		else {
			tmp = _hoops_HPASA (tree->_hoops_RAASA[_hoops_HRASA], bias, priority+1, name, item);
			tmp->_hoops_RAASA[_hoops_IRASA] = tree->_hoops_RAASA[_hoops_IRASA];
		}

		_hoops_APASA (tree);
		tree = tmp;
	}

	return tree;
}

GLOBAL_FUNCTION bool HI_Fast_Lookup_Available (
	_hoops_CRCP const *		owner,
	bool				_hoops_HAASA) {
	_hoops_AAASA *		_hoops_HGIIR = owner->_hoops_RHASA();

	if (_hoops_HGIIR == null)
		return false;

	if (_hoops_HAASA)
		return _hoops_HGIIR->_hoops_HAASA != null;
	else
		return _hoops_HGIIR->_hoops_PAASA != null;
}

GLOBAL_FUNCTION _hoops_CRCP * HI_Find_Fast_Lookup_Segment (
	_hoops_CRCP alter *			owner,
	char const *			name) {
	_hoops_AAASA *			_hoops_HGIIR = owner->_hoops_RHASA();
	_hoops_GAASA *			tree = _hoops_HGIIR->_hoops_PAASA;

	if (tree == null)
		return null;

	_hoops_HGIIR->_hoops_PAASA = tree = _hoops_HPASA (tree, 0, 0, name, null);

	if (tree->item != null && tree->item->type == _hoops_IRCP) {
		_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *)tree->item;

		if (_hoops_SRCP->name.length != 0 && _hoops_AGGR (name, _hoops_SRCP->name.text))
			return (_hoops_CRCP *)_hoops_HGIIR->_hoops_PAASA->item;
	}

	return null;
}

GLOBAL_FUNCTION void HI_Add_Fast_Lookup_Item (
	_hoops_CRCP alter *			owner,
	bool					_hoops_HAASA,
	Subsegment *			item) {
	_hoops_AAASA *			_hoops_HGIIR = owner->_hoops_RHASA();
	_hoops_GAASA **			root;
	char const *			name = null;
	int						priority = 0;
	int						bias = 0;

	if (_hoops_HGIIR == null)
		return;

	if (_hoops_HAASA) {
		if (!_hoops_HGIIR->_hoops_CAASA)
			return;
		root = &_hoops_HGIIR->_hoops_HAASA;
		priority = item->priority;
	}
	else {
		if (!_hoops_HGIIR->_hoops_IAASA)
			return;
		root = &_hoops_HGIIR->_hoops_PAASA;
	}


	if (item->type == _hoops_IRCP) {
		_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *)item;

		if (_hoops_SRCP->name.length != 0)
			name = _hoops_SRCP->name.text;
		else if (!_hoops_HAASA)
			return;

		if (_hoops_HAASA && BIT (_hoops_SRCP->_hoops_RCGC, _hoops_AHASA) && !ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GISIR | _hoops_SHSIR))
			bias = -1;
	}

	*root = _hoops_CPASA (*root, bias, priority, name, item);
}

GLOBAL_FUNCTION void HI_Remove_Fast_Lookup_Item (
	_hoops_CRCP alter *			owner,
	bool					_hoops_HAASA,
	Subsegment *			item) {
	_hoops_AAASA *			_hoops_HGIIR = owner->_hoops_RHASA();
	_hoops_GAASA **			root;
	int						priority = 0;
	int						bias = 0;

	if (_hoops_HGIIR == null)
		return;

	if (_hoops_HAASA) {
		root = &_hoops_HGIIR->_hoops_HAASA;
		priority = item->priority;
	}
	else
		root = &_hoops_HGIIR->_hoops_PAASA;

	if (*root == null)
		return;		/* _hoops_SASRR? */


	if (item->type == _hoops_IRCP) {
		_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *)item;

		if (_hoops_SRCP->name.length == 0 && !_hoops_HAASA)
			return;

		if (_hoops_HAASA && BIT (_hoops_SRCP->_hoops_RCGC, _hoops_AHASA) && !ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GISIR | _hoops_SHSIR))
			bias = -1;
	}

	*root = _hoops_GHASA (*root, bias, priority, item);
}

GLOBAL_FUNCTION Subsegment * HI_Find_Fast_Lookup_Predecessor (
	_hoops_CRCP alter *			owner,
	bool					_hoops_HAASA,
	Subsegment *			item,
	char const *			name) {
	_hoops_AAASA *			_hoops_HGIIR = owner->_hoops_RHASA();
	_hoops_GAASA **			root;
	int						priority = 0;
	int						bias = 0;


	if (_hoops_HAASA) {
		root = &_hoops_HGIIR->_hoops_HAASA;
		priority = item->priority;
	}
	else
		root = &_hoops_HGIIR->_hoops_PAASA;

	if (*root == null)
		return null;		/* _hoops_SASRR? */


	if (item != null && item->type == _hoops_IRCP) {
		_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *)item;

		if (_hoops_SRCP->name.length == 0 && !_hoops_HAASA)
			return null;

		if (_hoops_HAASA && BIT (_hoops_SRCP->_hoops_RCGC, _hoops_AHASA) && !ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GISIR | _hoops_SHSIR))
			bias = -1;
	}

	*root = _hoops_HPASA (*root, bias, priority, name, item);

	{
		_hoops_GAASA *	node = (*root)->_hoops_RAASA[_hoops_HRASA];

		if (node != null) {
			while (node->_hoops_RAASA[_hoops_IRASA] != null)
				node = node->_hoops_RAASA[_hoops_IRASA];

			return node->item;
		}
	}

	return null;
}

/*---------------------------------------------------------------------------*/

GLOBAL_FUNCTION void HI_Create_Fast_Lookup (
	_hoops_CRCP alter *			owner,
	bool					_hoops_HAASA)
{
	Subsegment *			_hoops_GIPIA;
	_hoops_AAASA *			_hoops_HGIIR = owner->_hoops_RHASA();

	if (_hoops_HGIIR == null) {
		ZALLOC (_hoops_HGIIR, _hoops_AAASA);
		owner->_hoops_PHASA (_hoops_HGIIR);
	}

	if (!_hoops_HAASA && _hoops_HGIIR->_hoops_PAASA == null) {
		if ((_hoops_GIPIA = owner->_hoops_RGRPR) != null) do {
			char const *	name = null;

			if (_hoops_GIPIA->type == _hoops_IRCP) {
				_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *)_hoops_GIPIA;

				if (_hoops_SRCP->name.length != 0)
					name = _hoops_SRCP->name.text;
			}

			if (name != null)
				_hoops_HGIIR->_hoops_PAASA = _hoops_CPASA (_hoops_HGIIR->_hoops_PAASA, 0, 0, name, _hoops_GIPIA);
		} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);

		_hoops_HGIIR->_hoops_IAASA = true;
	}

	if (_hoops_HAASA && _hoops_HGIIR->_hoops_HAASA == null) {
		if ((_hoops_GIPIA = owner->_hoops_RGRPR) != null) do {
			char const *	name = null;

			if (_hoops_GIPIA->type == _hoops_IRCP) {
				_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *)_hoops_GIPIA;

				if (_hoops_SRCP->name.length != 0)
					name = _hoops_SRCP->name.text;
			}
			else /* _hoops_RPP (_hoops_HHASA->_hoops_GPRR == _hoops_IHASA) */
				((_hoops_PGRPR *)_hoops_GIPIA)->priority = 0;	/* _hoops_CHASA _hoops_SHIR _hoops_SPIP _hoops_IH _hoops_GHCP _hoops_SHASA */

			_hoops_HGIIR->_hoops_HAASA = _hoops_CPASA (_hoops_HGIIR->_hoops_HAASA, 0, _hoops_GIPIA->priority, name, _hoops_GIPIA);
		} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);

		_hoops_HGIIR->_hoops_CAASA = true;
	}
}

/*---------------------------------------------------------------------------*/

local void _hoops_GIASA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GAASA *			tree) {
	VList<_hoops_GAASA *>		stack(_hoops_RIGC->memory_pool);

	stack.AddFirst(tree);
	while (stack.Count() > 0)	{
		tree = stack.RemoveFirst();

		while (tree)	{
			if (tree->_hoops_RAASA[_hoops_IRASA])
				stack.AddFirst(tree->_hoops_RAASA[_hoops_IRASA]);

			_hoops_GAASA *	temp = tree->_hoops_RAASA[_hoops_HRASA];
			FREE (tree, _hoops_GAASA);
			tree = temp;
		}
	}
}

GLOBAL_FUNCTION void HI_Destroy_Fast_Lookups (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP alter *			owner) {
	_hoops_AAASA *			_hoops_HGIIR = owner->_hoops_RHASA();

	if (_hoops_HGIIR != null) {
		if (_hoops_HGIIR->_hoops_PAASA != null)
			_hoops_GIASA (_hoops_RIGC, _hoops_HGIIR->_hoops_PAASA);
		if (_hoops_HGIIR->_hoops_HAASA != null)
			_hoops_GIASA (_hoops_RIGC, _hoops_HGIIR->_hoops_HAASA);

		FREE (_hoops_HGIIR, _hoops_AAASA);
		owner->_hoops_PHASA (null);
	}
}

/*---------------------------------------------------------------------------*/

GLOBAL_FUNCTION void HI_Show_Fast_Lookup_Priority_Range (
	_hoops_CRCP *				_hoops_SRCP,
	long *					low,
	long *					high) {
	_hoops_AAASA *			_hoops_HGIIR = _hoops_SRCP->_hoops_RHASA();

	if (_hoops_HGIIR->_hoops_HAASA != null) {
		_hoops_GAASA const *	node;

		if (low != null) {
			node = _hoops_HGIIR->_hoops_HAASA;
			while (node->_hoops_RAASA[_hoops_HRASA] != null)
				node = node->_hoops_RAASA[_hoops_HRASA];
			*low = node->priority;
		}
		if (high != null) {
			node = _hoops_HGIIR->_hoops_HAASA;
			while (node->_hoops_RAASA[_hoops_IRASA] != null)
				node = node->_hoops_RAASA[_hoops_IRASA];
			*high = node->priority;
		}
	}
	else {
		if (low != null)
			*low = 0;
		if (high != null)
			*high = 0;
	}
}

/*---------------------------------------------------------------------------*/


struct _hoops_RIASA {
	_hoops_RIASA *		prev;
	_hoops_RSAPR *	_hoops_CIPPR;
};


local _hoops_CRCP * _hoops_AIASA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_RSAPR *			_hoops_PIASA,
	_hoops_RIASA *				_hoops_HIASA,
	_hoops_CRCP *				start_seg,
	bool					_hoops_IIASA) {
	_hoops_RSAPR *			_hoops_CIPPR;
	_hoops_RIASA *				_hoops_RCSHR;
	_hoops_CRCP *				_hoops_SRCP;
	_hoops_CRCP *				_hoops_CIASA = null;
	bool					_hoops_ACGPR = false;
	_hoops_RSAPR				_hoops_SIASA;


_hoops_GCASA:
	_hoops_CIPPR = _hoops_PIASA;
	_hoops_RCSHR = _hoops_HIASA;
	_hoops_SRCP = start_seg;


	_hoops_PCCAR {
		switch (_hoops_CIPPR->type) {
			case _hoops_PGPPR:
			case _hoops_HGPPR:
			case _hoops_IGPPR:
			case _hoops_CGPPR: {
				/*** _hoops_RCASA: _hoops_SAHR _hoops_ACASA _hoops_RH _hoops_AAS _hoops_HIGR ***/

				_hoops_SIASA.next = null;
				_hoops_CIPPR = &_hoops_SIASA;
			}	break;

			case _hoops_ISAPR: {
				if (_hoops_SRCP == null)
					_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_PCRIR;
			}	break;

			case _hoops_RGPPR: {
				if (_hoops_CIPPR->next == null) {
					/* _hoops_SAHR _hoops_AASH _hoops_GIRP */

					_hoops_SIASA.next = _hoops_CIPPR->expansion;
					_hoops_CIPPR = &_hoops_SIASA;
				}
				else {
					/* _hoops_SCH'_hoops_GRI _hoops_ACIPR _hoops_IS _hoops_CRGS _hoops_CGPR _hoops_RGR _hoops_CCAH _hoops_CCHHR _hoops_HIGR _hoops_RARP
					 * _hoops_CGH _hoops_SHH _hoops_PGHPR. _hoops_PHGP _hoops_PAIHR: _hoops_CCPP _hoops_SCH _hoops_GPP _hoops_RH _hoops_SPRS,
					 * _hoops_GHHA, _hoops_PPR _hoops_PGICR _hoops_ASRC. _hoops_PCASA _hoops_HCASA!
					 */
					_hoops_RIASA			_hoops_ICASA;

					_hoops_ICASA.prev = _hoops_RCSHR;
					_hoops_ICASA._hoops_CIPPR = _hoops_CIPPR->next;

					_hoops_SRCP = _hoops_AIASA (_hoops_RIGC, _hoops_CIPPR->expansion, &_hoops_ICASA, _hoops_SRCP, _hoops_IIASA);
					goto _hoops_PRSPR;
				}
			}	break;

			case _hoops_CSAPR: {
				if (_hoops_SRCP == null) {
					if ((_hoops_SRCP = HOOPS_WORLD->root) == null) {
						_hoops_RPPPR();
						_hoops_SRCP = HI_Create_One_Segment (_hoops_RIGC, null, (Subsegment **)&HOOPS_WORLD->root, null, (_hoops_CRCP *)HOOPS_WORLD, true);
						_hoops_IRRPR();
					}
				}
			}	break;

			case _hoops_GGPPR: {
				if (_hoops_SRCP == null)
					_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_PCRIR;

				_hoops_SRCP = _hoops_SRCP->owner;
			}	break;

			case _hoops_HRPPR: {
				_hoops_SRCP = (_hoops_CRCP *)_hoops_SISIR (_hoops_RIGC, _hoops_CIPPR->key, _hoops_SRCP);

				if (_hoops_SRCP == null || _hoops_SRCP->type != _hoops_IRCP ||
					BIT (_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR)) {		/* _hoops_AIPH _hoops_CGRPR */
					if (_hoops_CIASA != null) {			/* _hoops_CCASA */
						_hoops_RPPPR();
						HI_Delete_Segment (_hoops_RIGC, _hoops_CIASA, (void *)null);
						_hoops_IRRPR();
					}
					HE_ERROR (HEC_SEGMENT, HES_INVALID_KEY,
							  "'@key' reference does not point to a valid segment");
					_hoops_SRCP = null;
					goto _hoops_PRSPR;
				}
			}	break;

			case _hoops_ARPPR: {
				_hoops_CRCP *		current = _hoops_SRCP;
				Subsegment *	_hoops_SSGPR;
				Subsegment **	_hoops_ASRGR = null;
				int				cmp;
				Subsegment *	_hoops_AIGSA = null;
				int				_hoops_SCASA = 0;

				if (current == null)
					current = _hoops_RIGC->open_list->info.segment._hoops_PCRIR;

				if (BIT (current->_hoops_PHSI, _hoops_PRSIR)) {
					HI_Not_When_Streamed (current, "create sub-segment");
					_hoops_SRCP = null;
					goto _hoops_PRSPR;
				}

				/* _hoops_HAPR _hoops_GH _hoops_IS _hoops_CAS _hoops_SCH _hoops_GSASA _hoops_IS _hoops_PHHR */

				_hoops_SRCP = null;
				if ((_hoops_SSGPR = current->_hoops_RGRPR) == null)
					_hoops_ASRGR = &current->_hoops_RGRPR;
				else {
					LOCK_MUTEX (HOOPS_WORLD->_hoops_RSASA);
					_hoops_AAASA *	_hoops_HGIIR = current->_hoops_RHASA();

					if (_hoops_HGIIR != null && _hoops_HGIIR->_hoops_PAASA != null) {
						_hoops_HGIIR->_hoops_PAASA = _hoops_CPASA (_hoops_HGIIR->_hoops_PAASA, 0, 0, _hoops_CIPPR->_hoops_AGPPR.text, null);
						if (_hoops_HGIIR->_hoops_PAASA->item != null)
							_hoops_SRCP = (_hoops_CRCP *)_hoops_HGIIR->_hoops_PAASA->item;
						else {
							_hoops_GAASA *	node = _hoops_HGIIR->_hoops_PAASA->_hoops_RAASA[_hoops_HRASA];

							if (node != null) {
								while (node->_hoops_RAASA[_hoops_IRASA] != null)
									node = node->_hoops_RAASA[_hoops_IRASA];

								_hoops_AIGSA = node->item;
								_hoops_ASRGR = &_hoops_AIGSA->next;
							}

							// _hoops_GA'_hoops_RA _hoops_SHSP _hoops_ASASA _hoops_RARP, _hoops_GRS _hoops_PSASA _hoops_SCH _hoops_IH _hoops_HSASA
							_hoops_HGIIR->_hoops_PAASA = _hoops_GHASA (_hoops_HGIIR->_hoops_PAASA, 0, 0, null);
						}
					}
					UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RSASA);

					if (_hoops_SRCP == null && _hoops_ASRGR == null) {
						_hoops_ASRGR = &current->_hoops_RGRPR;

						_hoops_PCCAR {
							if (BIT (_hoops_SSGPR->_hoops_RRHH, _hoops_PASIR) &&
								_hoops_SSGPR->priority > 0) {
								_hoops_ASRGR = _hoops_SSGPR->backlink;
								break;
							}

							/* _hoops_HPCAR _hoops_IHASA < _hoops_ISASA < _hoops_ISAP */

							_hoops_AIGSA = _hoops_SSGPR;

							if (_hoops_SSGPR->type == _hoops_IRCP) {
								if ((cmp = HI_Compare_Names (&_hoops_CIPPR->_hoops_AGPPR, &((_hoops_CRCP *)_hoops_SSGPR)->name)) == 0) {
									/* _hoops_CSASA-_hoops_SSASA! _hoops_GSGI _hoops_SCH! */
									_hoops_SRCP = (_hoops_CRCP *)_hoops_SSGPR;
									break;
								}
								else if (cmp < 0) {
									/* _hoops_SCH _hoops_IAGA _hoops_ARPP _hoops_ARI */
									_hoops_ASRGR = _hoops_SSGPR->backlink;
									break;
								}
								++_hoops_SCASA;
							}

							if (_hoops_SSGPR->next == null) {
								_hoops_ASRGR = &_hoops_SSGPR->next;
								break;
							}

							_hoops_SSGPR = _hoops_SSGPR->next;
						}

						if (BIT (current->_hoops_PHSI, _hoops_GGPSA) &&
							_hoops_ASRGR != null) {
							/* _hoops_ACIPR _hoops_AGIR: _hoops_CGSI _hoops_GHCA _hoops_SHH _hoops_GGSR _hoops_IIGR _hoops_RGPSA _hoops_AGR
							 * _hoops_RCIPR _hoops_PHHR _hoops_HCR _hoops_RH _hoops_PPRRR _hoops_IS _hoops_RH _hoops_RSGR _hoops_IS _hoops_CACH _hoops_RPP _hoops_SCH'_hoops_GRI
							 * _hoops_IIH _hoops_GGR _hoops_PCCP _hoops_GGSR-_hoops_IIGR-_hoops_AGR _hoops_PPRRR.
							 */

							if ((_hoops_SSGPR = *_hoops_ASRGR) != null) do {
								if (_hoops_SSGPR->type == _hoops_IRCP &&
									_hoops_RAHSR (_hoops_CIPPR->_hoops_AGPPR, ((_hoops_CRCP const *)_hoops_SSGPR)->name)) {
									_hoops_SRCP = (_hoops_CRCP *)_hoops_SSGPR;
									break;
								}
							} while ((_hoops_SSGPR = _hoops_SSGPR->next) != null);
						}
					}
				}

				if (_hoops_SRCP == null) {
					if (!_hoops_IIASA)
						goto _hoops_PRSPR;

					if (BIT (current->_hoops_PHSI, _hoops_AGPSA))
						_hoops_RIGC->flags |= _hoops_PGPSA;

					if (!_hoops_ACGPR &&
						!BIT(_hoops_RIGC->flags, _hoops_PGPSA)) {

						_hoops_ACGPR = true;		// _hoops_GRS _hoops_HGCR

						if (!_hoops_RPPPR()) {	// _hoops_HIH _hoops_GHCA _hoops_SHH _hoops_HGPSA
							// _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_RGRIR _hoops_HHSIR _hoops_GAR _hoops_SR _hoops_CHR _hoops_GIAA _hoops_IRS _hoops_IHSIR
							_hoops_AAASA *	_hoops_HGIIR = current->_hoops_RHASA();

							if (_hoops_HGIIR == null && _hoops_SCASA > 128 &&
								!BIT (HOOPS_WORLD->_hoops_IRARR, _hoops_IGPSA)) {
								HI_Create_Fast_Lookup (current, false);
								_hoops_HGIIR = current->_hoops_RHASA();
								_hoops_SCASA = 0;
							}

							goto _hoops_GCASA;
						}
					}


					LOCK_MUTEX (HOOPS_WORLD->_hoops_RSASA);
					_hoops_AAASA *	_hoops_HGIIR = current->_hoops_RHASA();

					if (_hoops_HGIIR != null && _hoops_HGIIR->_hoops_PAASA != null)
						_hoops_HGIIR->_hoops_PAASA = _hoops_CPASA (_hoops_HGIIR->_hoops_PAASA, 0, 0, _hoops_CIPPR->_hoops_AGPPR.text, null);
					UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RSASA);



					_hoops_SRCP = HI_Create_One_Segment (_hoops_RIGC, &_hoops_CIPPR->_hoops_AGPPR, _hoops_ASRGR, _hoops_AIGSA, current, true);

					if (_hoops_CIASA == null)
						_hoops_CIASA = _hoops_SRCP;

					if (_hoops_AIGSA != null && _hoops_AIGSA->priority != 0 &&
						(_hoops_AIGSA->type == _hoops_IRCP ||
						 !BIT(_hoops_AIGSA->_hoops_RRHH, _hoops_HPAPA)))
						HI_Set_Priority (_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP, 0);


					if (BIT (_hoops_SRCP->owner->_hoops_PHSI, _hoops_CGPSA))
						HI_Attach_Automatic_Driver (_hoops_RIGC, _hoops_SRCP);
				}

				if (_hoops_SCASA > 128 && !BIT (HOOPS_WORLD->_hoops_IRARR, _hoops_IGPSA)) {
					LOCK_MUTEX (HOOPS_WORLD->_hoops_RSASA);
					HI_Create_Fast_Lookup (current, false);
					UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RSASA);
					_hoops_SCASA = 0;
				}
			}	break;

			case _hoops_GRPPR:
			case _hoops_RRPPR: {
			}	break;

			default: {
				_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Somethin' bad in 'descend'");
			}	break;
		}

		if ((_hoops_CIPPR = _hoops_CIPPR->next) == null) {
			if (_hoops_RCSHR == null) break;
			_hoops_CIPPR = _hoops_RCSHR->_hoops_CIPPR;
			_hoops_RCSHR = _hoops_RCSHR->prev;
		}
	}

	/* _hoops_SGPSA _hoops_GGSR _hoops_IIGR _hoops_GRPSA - _hoops_PIHA _hoops_SHH _hoops_CPHR! */
_hoops_PRSPR:
	if (_hoops_ACGPR)
		_hoops_IRRPR();

	return _hoops_SRCP;
}



template <typename T, int size>
class _hoops_RRPSA : public CMO {
	private:
		T		table[size+1];	// _hoops_GCIS _hoops_IRS _hoops_GRCIR _hoops_IRAP

	public:
		_hoops_RRPSA () {
			ZERO_ARRAY (table, size+1, T);
		}

		bool	_hoops_ARPSA (T item, T * _hoops_PRPSA = null) {
			if (_hoops_PRPSA != null)
				*_hoops_PRPSA = null;
			int		i;
			for (i = 0; i < size && table[i] != null; ++i) {
				if (table[i] == item) {
					while (i-- > 0)
						table[i+1] = table[i];
					table[0] = item;
					return true;
				}
			}
			if (i == size && _hoops_PRPSA != null)
				*_hoops_PRPSA = table[--i];
			while (i-- > 0)
				table[i+1] = table[i];
			table[0] = item;
			return false;
		}

		void Flush (void (*_hoops_HRPSA)(T, void *) = nullroutine, void * v = null) {
			if (_hoops_HRPSA != nullroutine) {
				for (int i = 0; i < size && table[i] != null; ++i) {
					_hoops_HRPSA (table[i], v);
				}
			}
			ZERO_ARRAY (table, size, T);
		}

		void Remove (T item, void (*_hoops_HRPSA)(T, void *) = nullroutine, void * v = null) {
			bool		shift = false;
			for (int i = 0; i < size && table[i] != null; ++i) {
				if (table[i] == item) {
					if (_hoops_HRPSA != nullroutine)
						_hoops_HRPSA (table[i], v);
					shift = true;
				}
				if (shift)
					table[i] = table[i+1];
			}
		}
};




local void _hoops_IRPSA (_hoops_CRCP const * _hoops_SRCP, void * _hoops_SPAIR) {
	_hoops_AIGPR *	_hoops_RIGC = (_hoops_AIGPR *)_hoops_SPAIR;
	_hoops_SPAGR					_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, _hoops_RIGC->thread_id);
	_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP);
	_hoops_CRPSA *	_hoops_HGIIR = _hoops_CSC->_hoops_SRPSA();
	delete _hoops_HGIIR;
	_hoops_CSC->_hoops_GAPSA (null);
	_hoops_HPRH (_hoops_SRCP);
}


GLOBAL_FUNCTION void HI_Record_Recent_Seg_Path (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP const * _hoops_SRCP) {
	_hoops_CAAI (HOOPS_WORLD->_hoops_RAPSA);

	if (HOOPS_WORLD->_hoops_AAPSA == null)
		HOOPS_WORLD->_hoops_AAPSA = NEW(_hoops_PAPSA);

	_hoops_CRCP const *	_hoops_PRPSA;
	if (!HOOPS_WORLD->_hoops_AAPSA->_hoops_ARPSA (_hoops_SRCP, &_hoops_PRPSA))
		_hoops_PRRH (_hoops_SRCP);

	_hoops_APAI (HOOPS_WORLD->_hoops_RAPSA);

	if (_hoops_PRPSA != null)
		_hoops_IRPSA (_hoops_PRPSA, _hoops_RIGC);
}

GLOBAL_FUNCTION void HI_Flush_Seg_Path_Lookup (_hoops_AIGPR * _hoops_RIGC)
{
	_hoops_CAAI (HOOPS_WORLD->_hoops_RAPSA);

	if (HOOPS_WORLD->_hoops_AAPSA != null) {
		HOOPS_WORLD->_hoops_AAPSA->Flush (_hoops_IRPSA, _hoops_RIGC);
		delete HOOPS_WORLD->_hoops_AAPSA;
		HOOPS_WORLD->_hoops_AAPSA = null;
	}

	_hoops_APAI (HOOPS_WORLD->_hoops_RAPSA);
}

GLOBAL_FUNCTION void HI_Remove_Seg_Path_Lookup_Item (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP const * _hoops_SRCP)
{
	UNREFERENCED (_hoops_RIGC);

	_hoops_CAAI (HOOPS_WORLD->_hoops_RAPSA);

	if (HOOPS_WORLD->_hoops_AAPSA != null) {
		HOOPS_WORLD->_hoops_AAPSA->Remove (_hoops_SRCP);
	}

	_hoops_APAI (HOOPS_WORLD->_hoops_RAPSA);
}





HC_INTERFACE Key HC_CDECL HC_Create_Segment (
	char const *			name)
{
	_hoops_PAPPR context("Create_Segment");

	CODE_GENERATION (
		char	_hoops_RICIA[256];
		if (name[0] == '\0') {
			Sprintf_D (_hoops_RICIA, "unnamed %d", HOOPS_WORLD->_hoops_CGHGA);
			name = _hoops_RICIA;
		}
	);

	_hoops_CRCP *	_hoops_SRCP = HI_Create_Segment (context, null, name, true);

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "DEFINE (HC_Create_Segment (%S), ", name));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_SRCP->key));
	);

	return	_hoops_SRCP != null ? _hoops_SRCP->key : _hoops_SHSSR;
}

HC_INTERFACE Key HC_CDECL HC_Create_Segment_Key_By_Key (
	Key						parent_segment,
	char const *			child_segment_name)
{
	_hoops_PAPPR context("Create_Segment_Key_By_Key");

	CODE_GENERATION (
		char	_hoops_RICIA[256];
		if (child_segment_name[0] == '\0') {
			Sprintf_D (_hoops_RICIA, "unnamed %d", HOOPS_WORLD->_hoops_CGHGA);
			child_segment_name = _hoops_RICIA;
		}
	);

	_hoops_CSPPR();
	_hoops_CRCP *	_hoops_HAPSA = (_hoops_CRCP *)_hoops_RCSSR (context, parent_segment);

	if (_hoops_HAPSA == null || (_hoops_HAPSA->type != _hoops_IRCP &&
		_hoops_HAPSA->type != _hoops_PIRIR) || BIT(_hoops_HAPSA->_hoops_RRHH, _hoops_HGAGR)) {
			HE_ERROR (HEC_SEGMENT, HES_INVALID_KEY, "Provided key does not refer to a valid Segment");
			_hoops_IRRPR();
			return _hoops_SHSSR;
	}

	if (_hoops_HAPSA->type == _hoops_PIRIR)
		_hoops_HAPSA = (_hoops_CRCP *)((_hoops_PGRPR *)_hoops_HAPSA)->_hoops_IGRPR;

	_hoops_CRCP *	_hoops_SRCP = HI_Create_Segment (context, _hoops_HAPSA, child_segment_name, true);

	Key _hoops_IAPSA = _hoops_SRCP != null ? _hoops_SRCP->key : _hoops_SHSSR;

	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Create_Segment_Key_By_Key (LOOKUP (%D), ", parent_segment));
		HI_Dump_Code (Sprintf_S (null, "%S), ", child_segment_name));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_IAPSA));
	);

	return _hoops_IAPSA;
}


GLOBAL_FUNCTION _hoops_CRCP * HI_Create_Segment (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				owner,
	char const *			name,
	bool					_hoops_IIASA) {
	Subsegment **			_hoops_ASRGR, *_hoops_SSGPR;
	_hoops_CRCP *				_hoops_SRCP = null;

	while (*name == ' ')
		name++;

	_hoops_CSPPR();

	if (*name == '\0') {
		if (owner == null) {
			/* _hoops_SGCH _hoops_IH _hoops_PCCP _hoops_IGS _hoops_CAGH, _hoops_HIH _hoops_SRCH _hoops_GSGSA _hoops_HIS _hoops_SR _hoops_PAH
			 * _hoops_RCRP _hoops_IRS _hoops_RRI _hoops_CICAR _hoops_RIHH _hoops_GPSRR _hoops_IIGR _hoops_ISCP _hoops_HAII.
			 */
			if (_hoops_RIGC->open_list == null || _hoops_RIGC->open_list->_hoops_GCRIR != _hoops_RCRIR) {
				HE_ERROR3 (HEC_SEGMENT, HES_CANNOT_OPEN_UNNAMED_SEGMENT,
						   "Can't create unnamed segment -",
						   "unnamed segments require that a containing segment",
						   "already be open, but none is.");
				goto Release;
			}

			owner = _hoops_RIGC->open_list->info.segment._hoops_PCRIR;
		}

		if (BIT (owner->_hoops_PHSI, _hoops_PRSIR)) {
			HI_Not_When_Streamed (owner, "create sub-segment");
			goto Release;
		}

		_hoops_ASRGR = &owner->_hoops_RGRPR;

		if (BIT (owner->_hoops_PHSI, _hoops_GGPSA))
			_hoops_RGGA ((_hoops_SSGPR = *_hoops_ASRGR) == null ||
				   _hoops_SSGPR->type >= _hoops_IRCP ||
				   BIT (_hoops_SSGPR->_hoops_RRHH, _hoops_PASIR))
				_hoops_ASRGR = &_hoops_SSGPR->next;
		else
			_hoops_RGGA ((_hoops_SSGPR = *_hoops_ASRGR) == null || _hoops_SSGPR->type >= _hoops_IRCP)
				_hoops_ASRGR = &_hoops_SSGPR->next;

		if (!_hoops_RPPPR()) {		// _hoops_PSSSR _hoops_IH _hoops_CPHP _hoops_SHS _hoops_HAGC _hoops_SHPH _hoops_CGPR _hoops_SR _hoops_HPPR _hoops_IS _hoops_SICAA
			_hoops_ASRGR = &owner->_hoops_RGRPR;

			if (BIT (owner->_hoops_PHSI, _hoops_GGPSA))
				_hoops_RGGA ((_hoops_SSGPR = *_hoops_ASRGR) == null ||
					   _hoops_SSGPR->type >= _hoops_IRCP ||
					   BIT (_hoops_SSGPR->_hoops_RRHH, _hoops_PASIR))
					_hoops_ASRGR = &_hoops_SSGPR->next;
			else
				_hoops_RGGA ((_hoops_SSGPR = *_hoops_ASRGR) == null || _hoops_SSGPR->type >= _hoops_IRCP)
					_hoops_ASRGR = &_hoops_SSGPR->next;
		}

		_hoops_SRCP = HI_Create_One_Segment (_hoops_RIGC, null, _hoops_ASRGR, null, owner, true);

		_hoops_IRRPR();
	}
	else {
		_hoops_CRCP *			_hoops_CAPSA = owner;
		char const *		_hoops_SAPSA = name;

		if (_hoops_CAPSA == null &&
			_hoops_RIGC->open_list != null && _hoops_RIGC->open_list->_hoops_GCRIR == _hoops_RCRIR)
			_hoops_CAPSA = _hoops_RIGC->open_list->info.segment._hoops_PCRIR;

		if (_hoops_CAPSA != null) {
			if (_hoops_AGGR (_hoops_SAPSA, "."))
				_hoops_SRCP = _hoops_CAPSA;
			else if (!BIT (_hoops_CAPSA->_hoops_PHSI, _hoops_AGPSA)) {
				while (_hoops_GPPSA(_hoops_SAPSA, 3, "../")) {
					_hoops_SAPSA += 3;
					_hoops_CAPSA = _hoops_CAPSA->owner;
					if (_hoops_CAPSA == HOOPS_WORLD->root)
						break;
				}

				_hoops_SPAGR					_hoops_GHAGR (_hoops_CAPSA->_hoops_RHAGR, _hoops_RIGC->thread_id);
				_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (_hoops_CAPSA);
				_hoops_CRPSA *	_hoops_HGIIR = _hoops_CSC->_hoops_SRPSA();

				if (_hoops_HGIIR != null) {
					int					result = _hoops_HGIIR->LookupItem(_hoops_SAPSA, &_hoops_SRCP);

					if (result == VHASH_STATUS_SUCCESS) {
						HI_Record_Recent_Seg_Path (_hoops_RIGC, _hoops_CAPSA);
#if 0
						if (BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR)) {
							_hoops_HPRH(_hoops_SRCP);
							_hoops_HGIIR->RemoveItem(_hoops_SAPSA, 0);
							_hoops_SRCP = null;
						}
#endif
					}
				}
			}
		}

		if (_hoops_SRCP == null) {
			_hoops_RSAPR *	path = HI_Parse_Path (_hoops_RIGC, name, _hoops_RPPSA);

			if (path == null)	// _hoops_RIHH (_hoops_AIAH _hoops_CRPPR) - _hoops_AHCI _hoops_CRAA
				goto Release;

			_hoops_SRCP = _hoops_AIASA (_hoops_RIGC, path, null, owner, _hoops_IIASA);
			HI_Free_Path (path);

			if (owner == null &&
				_hoops_RIGC->open_list != null && _hoops_RIGC->open_list->_hoops_GCRIR == _hoops_RCRIR)
				owner =  _hoops_RIGC->open_list->info.segment._hoops_PCRIR;

			if (owner && _hoops_SRCP && !BIT (owner->_hoops_PHSI, _hoops_AGPSA)) {
				_hoops_SPAGR					_hoops_GHAGR (owner->_hoops_RHAGR, _hoops_RIGC->thread_id);
				_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (owner);
				_hoops_CRPSA *	_hoops_HGIIR = _hoops_CSC->_hoops_SRPSA();

				if (_hoops_HGIIR == null) {
					_hoops_HGIIR = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_CRPSA)(HOOPS_WORLD->memory_pool,1);
					_hoops_CSC->_hoops_GAPSA(_hoops_HGIIR);
				}
				_hoops_HGIIR->InsertItem(_hoops_SAPSA, _hoops_SRCP);

				HI_Record_Recent_Seg_Path (_hoops_RIGC, owner);
			}
		}
	}

	HOOPS_WORLD->_hoops_APPSA = true;

  Release:
	_hoops_IRRPR();

	return _hoops_SRCP;
}


GLOBAL_FUNCTION _hoops_CRCP * HI_Create_One_Segment (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HCRPR const *			name,
	Subsegment **			_hoops_ASRGR,
	Subsegment *			_hoops_AIGSA,
	_hoops_CRCP *				owner,
	bool					_hoops_PPPSA)
{
	_hoops_ICIIR(_hoops_RIGC);
	ASSERT(owner);

UNREFERENCED(_hoops_AIGSA);
UNREFERENCED(_hoops_PPPSA);

	_hoops_CRCP *	_hoops_SRCP;
	ZALLOC (_hoops_SRCP, _hoops_CRCP);

	_hoops_SRCP->_hoops_HIHI = 1;
	_hoops_SRCP->type = _hoops_IRCP;
	_hoops_SRCP->_hoops_RRHH = _hoops_GGSCA;
	_hoops_SRCP->owner = owner;
	if (BIT (owner->_hoops_PHSI, _hoops_AGPSA))
		_hoops_SRCP->_hoops_PHSI = _hoops_AGPSA;
	_hoops_SRCP->key = _hoops_AIRIR (_hoops_SRCP);
	_hoops_SRCP->_hoops_CPGPR = _hoops_HCHPA;
	if (name != null)
		HI_Copy_Name (name, &_hoops_SRCP->name);

	_hoops_SRCP->backlink = _hoops_ASRGR;
	if ((_hoops_SRCP->next = *_hoops_ASRGR) != null)
		(*_hoops_ASRGR)->backlink = &_hoops_SRCP->next;
	*_hoops_ASRGR = (Subsegment *)_hoops_SRCP;

	if (owner->type == _hoops_IRCP) {
		//_hoops_HPPSA (_hoops_IPPSA->_hoops_HHSIR);
		_hoops_AAASA *	_hoops_HGIIR = owner->_hoops_RHASA();

		if (_hoops_HGIIR != null) {
			if (_hoops_HGIIR->_hoops_PAASA != null) {
				if (_hoops_HGIIR->_hoops_PAASA->item == null)	/* _hoops_RCAPR _hoops_SGP _hoops_GGR _hoops_CPPSA() _hoops_ARRS */
					_hoops_HGIIR->_hoops_PAASA->item = (Subsegment *)_hoops_SRCP;
				else if (name != null)
					HI_Add_Fast_Lookup_Item (owner, false, (Subsegment *)_hoops_SRCP);
			}

			if (_hoops_HGIIR->_hoops_HAASA != null)
				HI_Add_Fast_Lookup_Item (owner, true, (Subsegment *)_hoops_SRCP);
		}
		//_hoops_SPPSA (_hoops_IPPSA->_hoops_HHSIR);
	}

	if (owner->type != _hoops_PRAIR) {
		int	_hoops_CGSCA = _hoops_RSPPR(_hoops_RIGC, flags);
		int	_hoops_SGSCA = _hoops_RIGC->flags;

		/* _hoops_IRHH _hoops_RCRR _hoops_SR _hoops_PRSCA _hoops_RGR _hoops_GHPSA */
		_hoops_RSPPR(_hoops_RIGC, flags) &= ~_hoops_GRSCA;
		_hoops_RIGC->flags &= ~_hoops_RRSCA;
		_hoops_SASIR (_hoops_RIGC, owner, _hoops_CCHPA);
		_hoops_RSPPR(_hoops_RIGC, flags) = _hoops_CGSCA;
		_hoops_RIGC->flags = _hoops_SGSCA;
	}

	return _hoops_SRCP;
}


GLOBAL_FUNCTION _hoops_CRCP * HI_Create_Proxy (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP const *			_hoops_SRCP)
{
	if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_CGPSA) ||
		BIT (_hoops_SRCP->owner->_hoops_PHSI, _hoops_CGPSA)) {
		HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Can't create proxy for driver segments.");
		return null;
	}

	_hoops_SPAGR				_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, _hoops_RIGC->thread_id);
	_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP);

	_hoops_RHPSA *		_hoops_HSPIR;

	if ((_hoops_HSPIR = _hoops_CSC->_hoops_AHPSA()) == null) {
		ZALLOC (_hoops_HSPIR, _hoops_RHPSA);
		_hoops_HSPIR->_hoops_PHPSA = -1;
		_hoops_CSC->_hoops_HHPSA (_hoops_HSPIR);
	}

	if (_hoops_HSPIR->_hoops_IHPSA != null) {
		ASSERT(0);
		HE_WARNING (HEC_GEOMETRY_OR_SEGMENT, HES_OUTPUT_SEGMENT_EXISTS, "Can't create new proxy using existing one");
		return _hoops_HSPIR->_hoops_IHPSA;
	}

	int _hoops_CHPSA = _hoops_RIGC->flags;
	_hoops_RIGC->flags |= _hoops_PGPSA;
	_hoops_CRCP *	_hoops_IHPSA = HI_Create_One_Segment (_hoops_RIGC, null, (Subsegment alter **)&_hoops_HSPIR->_hoops_IHPSA, null, (_hoops_CRCP alter*)HOOPS_WORLD, false);
	_hoops_RIGC->flags &= _hoops_CHPSA;

	_hoops_IHPSA->_hoops_RRHH &= ~_hoops_GGSCA;
	_hoops_IHPSA->_hoops_PHSI |= _hoops_AGPSA;

	_hoops_IHPSA->owner = _hoops_PGRCA(_hoops_SRCP);

	_hoops_PRRH(_hoops_SRCP);

	HOOPS_WORLD->_hoops_SHPSA++;

	return _hoops_IHPSA;
}


HC_INTERFACE Key HC_CDECL HC_Create_Proxy (
	Key					key)
{
	_hoops_PAPPR context("Create_Proxy");

	Key	_hoops_IAPSA = _hoops_SHSSR;

	_hoops_CSPPR();

	_hoops_HPAH *	item = _hoops_RCSSR (context, key);

	if (item != null && item->type == _hoops_IRCP) {
		_hoops_CRCP * _hoops_SRCP = (_hoops_CRCP *)item;

		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIPSA)) {
			HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Can't create proxy for proxy or populator.");
		}
		else {
			_hoops_CRCP *	_hoops_IHPSA = HI_Create_Proxy (context, (_hoops_CRCP *)item);

			if (_hoops_IHPSA != null)
				_hoops_IAPSA = _hoops_IHPSA->key;
			else
				HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Unable to create proxy segment");
		}
	}
	else
		HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Provided key does not point to a valid segment");

	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Create_Proxy (LOOKUP (%D))", key));
		HI_Dump_Code (Sprintf_LD (null, ", %D);\n", _hoops_IAPSA));
	);

	return _hoops_IAPSA;
}

HC_INTERFACE void HC_CDECL HC_Commit_Proxy (
	Key				key,
	const char *	options)
{
	_hoops_PAPPR context("Commit_Proxy");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Commit_Proxy (LOOKUP (%D))", key));
	);

	UNREFERENCED(options);

	_hoops_CSPPR();

	_hoops_CRCP * _hoops_SRCP = (_hoops_CRCP *)_hoops_RCSSR (context, key);

	if (_hoops_SRCP == null || _hoops_SRCP->type != _hoops_IRCP) {
		HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Provided key does not point to a valid segment");
	}
	else if (!BIT(_hoops_SRCP->_hoops_PHSI, _hoops_AGPSA)) {
		HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Provided key does not point to a proxy segment");
	}
	else {
		_hoops_CAAI (HOOPS_WORLD->_hoops_RIPSA);
		bool _hoops_AIPSA = HI_Is_Segment_Open(context, _hoops_SRCP, false);
		_hoops_APAI (HOOPS_WORLD->_hoops_RIPSA);

		if (_hoops_AIPSA)
			HE_ERROR (HEC_SEGMENT, HES_OPEN_SEGMENT, "Can't commit an open proxy");
		else {
			_hoops_SRCP->_hoops_PHSI &= ~_hoops_AGPSA;

			_hoops_CAAI (HOOPS_WORLD->_hoops_PIPSA);
			if (!HOOPS_WORLD->_hoops_HIPSA)
				HOOPS_WORLD->_hoops_HIPSA = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_IIPSA)(HOOPS_WORLD->memory_pool);

			HOOPS_WORLD->_hoops_HIPSA->AddLast(_hoops_SRCP);
			_hoops_APAI (HOOPS_WORLD->_hoops_PIPSA);

			HOOPS_WORLD->_hoops_CIPSA++;
		}
	}

	_hoops_IRRPR();
}
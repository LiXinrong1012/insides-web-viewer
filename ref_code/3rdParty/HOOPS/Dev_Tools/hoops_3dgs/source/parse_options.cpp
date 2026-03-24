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
 * $Id: obf_tmp.txt 1.98 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"
#include "hpserror.h"

/*
 * (_hoops_RAIGR _hoops_HHHR _hoops_RPR _hoops_GGR _hoops_RH _hoops_HCSP _hoops_GPRR _hoops_AGSR _hoops_RH _hoops_HCSP _hoops_PAH _hoops_HS _hoops_AHHR
 *	_hoops_GRPAR _hoops_RHIR _hoops_RIGCC(_hoops_RPR) _hoops_GRPAR.)
 */

struct _hoops_AIGCC {
	char const **			_hoops_PIGCC;
	Karacter const **		_hoops_HIGCC;
	_hoops_GCIIR *		_hoops_CIIIR;
	bool					_hoops_IIGCC;
};



local _hoops_PIIIR * _hoops_CIGCC (
	_hoops_HCRPR const *			name,
	int						_hoops_ACIPP) {
	_hoops_PIIIR	*			type;
	_hoops_PIIIR	**			_hoops_SIGCC;
	_hoops_GCIIR *		_hoops_SPHHR = _hoops_CIACR (_hoops_SAPPP);

	_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);

	if (_hoops_SPHHR->count++ >= 2*_hoops_SPHHR->size) {
		_hoops_PIIIR **		_hoops_GCGCC = _hoops_SPHHR->table;
		int					_hoops_CIGRR = _hoops_SPHHR->size;

		_hoops_SPHHR->size *= 4;
		ZALLOC_ARRAY (_hoops_SPHHR->table, _hoops_SPHHR->size, _hoops_PIIIR *);

		for (int i=0; i<_hoops_CIGRR; i++) {
			while ((type = _hoops_GCGCC[i]) != null) {
				int		_hoops_RCGCC;

				_hoops_GCGCC[i] = type->next;

				_hoops_PCIPP (type->name, _hoops_RCGCC);

				_hoops_SIGCC = &_hoops_SPHHR->table[_hoops_RCGCC & (_hoops_SPHHR->size - 1)];
				if ((type->next = *_hoops_SIGCC) != null)
					type->next->backlink = &type->next;
				*_hoops_SIGCC = type;
				type->backlink = _hoops_SIGCC;
			}
		}

		FREE_ARRAY (_hoops_GCGCC, _hoops_CIGRR, _hoops_PIIIR *);
	}

	_hoops_SIGCC = &_hoops_SPHHR->table[_hoops_ACIPP & (_hoops_SPHHR->size - 1)];
	ZALLOC (type, _hoops_PIIIR);
	if ((type->next = *_hoops_SIGCC) != null)
		type->next->backlink = &type->next;
	*_hoops_SIGCC = type;
	type->backlink = _hoops_SIGCC;
	type->type = _hoops_AIIIR;
	type->_hoops_HIHI = 1;
	type->owner = (_hoops_HPAH *)HOOPS_WORLD;
	//_hoops_GPRR->_hoops_CPGC = _hoops_RCPP;	 (_hoops_SHCAR, _hoops_HAR _hoops_ACGCC) 

	HI_Copy_Name (name, &type->name);
	type->id = ++HOOPS_WORLD->_hoops_RSPGI;
	type->_hoops_RCIIR = _hoops_HRSAP;
	type->_hoops_RHSAA = -1;
	type->_hoops_GHSAA = true;

	_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);

	return type;
}

#ifndef DISABLE_UNICODE_OPTIONS
local _hoops_RPSAP * _hoops_PCGCC (
	KName const	*			_hoops_SIHSA,
	int						_hoops_ACIPP) {
	_hoops_RPSAP *			_hoops_HCGCC;
	_hoops_RPSAP **			_hoops_SIGCC;
	_hoops_GCIIR *		_hoops_SPHHR = _hoops_CIACR (_hoops_CPPPP);

	_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);

	if (_hoops_SPHHR->count++ >= 2*_hoops_SPHHR->size) {
		_hoops_RPSAP **		_hoops_GCGCC = (_hoops_RPSAP **)_hoops_SPHHR->table;
		int					_hoops_CIGRR = _hoops_SPHHR->size;

		_hoops_SPHHR->size *= 4;
		ZALLOC_ARRAY (_hoops_SPHHR->table, _hoops_SPHHR->size, _hoops_PIIIR *);

		for (int i=0; i<_hoops_CIGRR; i++) {
			while ((_hoops_HCGCC = _hoops_GCGCC[i]) != null) {
				int		_hoops_RCGCC;

				_hoops_GCGCC[i] = _hoops_HCGCC->next;

				_hoops_HCIPP (_hoops_HCGCC->_hoops_SIHSA, _hoops_RCGCC);

				_hoops_SIGCC = (_hoops_RPSAP **)&_hoops_SPHHR->table[_hoops_RCGCC & (_hoops_SPHHR->size - 1)];
				if ((_hoops_HCGCC->next = *_hoops_SIGCC) != null)
					_hoops_HCGCC->next->backlink = &_hoops_HCGCC->next;
				*_hoops_SIGCC = _hoops_HCGCC;
				_hoops_HCGCC->backlink = _hoops_SIGCC;
			}
		}

		FREE_ARRAY (_hoops_GCGCC, _hoops_CIGRR, _hoops_PIIIR *);
	}

	_hoops_SIGCC = (_hoops_RPSAP **)&_hoops_SPHHR->table[_hoops_ACIPP & (_hoops_SPHHR->size - 1)];
	ZALLOC (_hoops_HCGCC, _hoops_RPSAP);
	if ((_hoops_HCGCC->next = *_hoops_SIGCC) != null)
		_hoops_HCGCC->next->backlink = &_hoops_HCGCC->next;
	*_hoops_SIGCC = _hoops_HCGCC;
	_hoops_HCGCC->backlink = _hoops_SIGCC;
	_hoops_HCGCC->type = _hoops_AIIIR;
	_hoops_HCGCC->_hoops_HIHI = 1;
	_hoops_HCGCC->owner = (_hoops_HPAH *)HOOPS_WORLD;
	//_hoops_ICGCC->_hoops_CPGC = _hoops_RCPP;	(_hoops_SHCAR, _hoops_HAR _hoops_ACGCC)

	HI_Copy_KName (_hoops_SIHSA, &_hoops_HCGCC->_hoops_SIHSA);
	_hoops_HCGCC->id = ++HOOPS_WORLD->_hoops_RSPGI;
	_hoops_HCGCC->_hoops_RCIIR = _hoops_CRSAP;
	_hoops_HCGCC->_hoops_RHSAA = -1;
	_hoops_HCGCC->_hoops_GHSAA = true;

	_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);

	return _hoops_HCGCC;
}
#endif



local int _hoops_CCGCC () {
	_hoops_PIIIR **		table = HOOPS_WORLD->_hoops_PCIIR;
	int					count = HOOPS_WORLD->_hoops_AGCAA;
	int					index = 0;

	_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);

	while (index < count) {
		if (*table++ == null)
			break;
		index++;
	}

	if (index == count) {
		/* _hoops_HCR _hoops_IGI _hoops_GH, _hoops_HGCR _hoops_HPIH _hoops_SSAI */
		ZALLOC_ARRAY (table, count+32, _hoops_PIIIR *);  /* _hoops_CIGCR _hoops_IIGR 32 _hoops_IH _hoops_SCGCC _hoops_IIGR _hoops_PSSCI _hoops_GSGCC */
		if (count > 0) {
			_hoops_AIGA (HOOPS_WORLD->_hoops_PCIIR, count, _hoops_PIIIR *, table);
			FREE_ARRAY (HOOPS_WORLD->_hoops_PCIIR, count, _hoops_PIIIR *);
		}
		HOOPS_WORLD->_hoops_PCIIR = table;
		HOOPS_WORLD->_hoops_AGCAA += 32;

		if (index == 0) {	/* _hoops_SPCS _hoops_GGR _hoops_HGHC 0 */
			_hoops_PIIIR	*type;

			ZALLOC (type, _hoops_PIIIR);
			type->backlink = &type->next;
			type->type = _hoops_AIIIR;
			type->_hoops_HIHI = 1;
			type->owner = (_hoops_HPAH *)HOOPS_WORLD;

			HOOPS_WORLD->_hoops_PCIIR[0] = type;
			type->_hoops_RCIIR = _hoops_ACIIR;
			type->_hoops_GHSAA = true;

			++index;
		}
	}

	_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);

	return index;
}

local _hoops_PIIIR * _hoops_RSGCC (
	_hoops_HCRPR const *			name,
	int						_hoops_ACIPP) {
	_hoops_PIIIR	*			type;
	_hoops_PIIIR	**			_hoops_SIGCC;
	_hoops_GCIIR *		_hoops_SPHHR = _hoops_CIACR (_hoops_GGPCA);

	_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);

	_hoops_SIGCC = &_hoops_SPHHR->table[_hoops_ACIPP & (_hoops_SPHHR->size - 1)];
	ZALLOC (type, _hoops_PIIIR);
	if ((type->next = *_hoops_SIGCC) != null)
		type->next->backlink = &type->next;
	*_hoops_SIGCC = type;
	type->backlink = _hoops_SIGCC;
	type->type = _hoops_AIIIR;
	type->_hoops_HIHI = 1;
	type->owner = (_hoops_HPAH *)HOOPS_WORLD;
	//_hoops_GPRR->_hoops_CPGC = _hoops_RCPP;	(_hoops_SHCAR, _hoops_HAR _hoops_ACGCC) 

	HI_Copy_Name (name, &type->name);
	type->id = _hoops_CCGCC();
	HOOPS_WORLD->_hoops_PCIIR[type->id] = type;
	type->_hoops_RCIIR = _hoops_ACIIR;
	type->_hoops_GHSAA = true;

	++_hoops_SPHHR->count;

	_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);

	return type;
}



local void _hoops_ASGCC (
	_hoops_AIGPR *	_hoops_RIGC,
	Option_Value *			list) {

	if (list != null) {
		if (list->value._hoops_RIARA == null) { /* _hoops_SIAS _hoops_HAR _hoops_HS _hoops_IRS _hoops_GASR _hoops_GAPR! */
			HI_Free_Option_List (_hoops_RIGC, list->next);
			if (list->type->_hoops_HIHI == 1)
				_hoops_CIGPR (_hoops_RIGC,list->type);
			_hoops_HPRH (list->type);
			FREE (list, Option_Value);
		}
		else
			HI_Free_Option_List (_hoops_RIGC, list); /* (_hoops_GSSR _hoops_AGIR) */
	}
}


local bool _hoops_HAARA (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			options,
	Option_Value **			list,
	char const *			_hoops_SSACR,
	int						flags) 
{
	char					_hoops_SSSSI [_hoops_CGHHP];

	if (!BIT(flags, _hoops_CPSAP)) {
		HE_ERROR3 (HEC_SYNTAX, HES_PARSE_STRING,
				Sprintf_S (_hoops_SSSSI, "Error parsing option string '%s' -", options),
				   _hoops_SSACR, "(If you have unquoted string parameters, quote marks may fix the problem.)");
	}

	_hoops_ASGCC (_hoops_RIGC, *list);
	*list=null;
	return false;
}

local bool _hoops_PSGCC (
	_hoops_AIGPR *	_hoops_RIGC,
	Karacter const *		options,
	Option_Value **			list,
	char const *			_hoops_SSACR) {

	UNREFERENCED(_hoops_SSACR);
	UNREFERENCED(options);

	HE_ERROR (HEC_SYNTAX, HES_PARSE_STRING,
				"Parse error");

	_hoops_ASGCC (_hoops_RIGC, *list);
	*list=null;
	return false;
}


local char * _hoops_HSGCC (
	Option_Value const *	value) {

	return Sprintf_ND (null, "Too few values for '%n' - %d are needed",
					   &value->type->name, value->_hoops_AIPCR);
}


local char const * _hoops_ISGCC (
	Option_Value const	*value,
	char const				*_hoops_SSACR) {

	return Sprintf_NS (null, "Can't scan '%n' - %s", &value->type->name, _hoops_SSACR);
}


local char const * _hoops_CSGCC (
	_hoops_AIGPR *	_hoops_RIGC,
	Option_Value *			value,
	char const **			_hoops_SSGCC) {
	bool *					table;
	int						count;
	char const *			_hoops_SSACR;

	/* _hoops_IRS _hoops_SSRR _hoops_HIGR _hoops_IIGR _hoops_CAPR */
	if (value->type->_hoops_RHSAA < 0 && value->_hoops_AIPCR > 1) {
		int					_hoops_GGRCC = 1;
		char const *		_hoops_RPPA = *_hoops_SSGCC;

		_hoops_RGGA (*_hoops_RPPA == '\0' || *_hoops_RPPA == ')')
			if (*_hoops_RPPA++ == ',')			/* _hoops_HPIH _hoops_SPR */
				if (++_hoops_GGRCC == value->_hoops_AIPCR)
					break;

		value->_hoops_AIPCR = _hoops_GGRCC;
	}

	count = value->_hoops_AIPCR;
	POOL_ALLOC_ARRAY (table, count, bool, _hoops_RIGC->memory_pool);
	value->value._hoops_PGSAP = table;

	_hoops_PCCAR {
		if ((_hoops_SSACR = HI_Scan_Boolean (_hoops_RIGC, _hoops_SSGCC, null, table++)) != null)
			return _hoops_ISGCC (value, _hoops_SSACR);

		if (--count == 0)
			break;
		if (*(*_hoops_SSGCC)++ != ',')
			return _hoops_HSGCC (value);
		while (**_hoops_SSGCC == ' ')
			++*_hoops_SSGCC;
	}
	return null;
}


local char const * _hoops_RGRCC (
	_hoops_AIGPR *	_hoops_RIGC,
	Option_Value *			value,
	char const **			_hoops_SSGCC) {
	int *					table;
	int						count;
	char const *			_hoops_SSACR;

	/* _hoops_IRS _hoops_SSRR _hoops_HIGR _hoops_IIGR _hoops_CAPR */
	if (value->type->_hoops_RHSAA < 0 && value->_hoops_AIPCR > 1) {
		int					_hoops_GGRCC = 1;
		char const *		_hoops_RPPA = *_hoops_SSGCC;

		_hoops_RGGA (*_hoops_RPPA == '\0' || *_hoops_RPPA == ')')
			if (*_hoops_RPPA++ == ',')			/* _hoops_HPIH _hoops_SPR */
				if (++_hoops_GGRCC == value->_hoops_AIPCR)
					break;

		value->_hoops_AIPCR = _hoops_GGRCC;
	}

	count = value->_hoops_AIPCR;
	POOL_ALLOC_ARRAY (table, count, int, _hoops_RIGC->memory_pool);
	value->value._hoops_RIARA = table;

	_hoops_PCCAR {
		if ((_hoops_SSACR = HI_Scan_Integer (_hoops_RIGC, _hoops_SSGCC, null, table++)) != null)
			return _hoops_ISGCC (value, _hoops_SSACR);

		if (--count == 0)
			break;
		if (*(*_hoops_SSGCC)++ != ',')
			return _hoops_HSGCC (value);
		while (**_hoops_SSGCC == ' ')
			++*_hoops_SSGCC;
	}
	return null;
}


local char const * _hoops_AGRCC (
	_hoops_AIGPR *	_hoops_RIGC,
	Option_Value *			value,
	char const **			_hoops_SSGCC) {
	long *					table;
	int						count;
	char const *			_hoops_SSACR;

	/* _hoops_IRS _hoops_SSRR _hoops_HIGR _hoops_IIGR _hoops_CAPR */
	if (value->type->_hoops_RHSAA < 0 && value->_hoops_AIPCR > 1) {
		int				_hoops_GGRCC = 1;
		char const		*_hoops_RPPA = *_hoops_SSGCC;

		_hoops_RGGA (*_hoops_RPPA == '\0' || *_hoops_RPPA == ')')
			if (*_hoops_RPPA++ == ',')			/* _hoops_HPIH _hoops_SPR */
				if (++_hoops_GGRCC == value->_hoops_AIPCR)
					break;

		value->_hoops_AIPCR = _hoops_GGRCC;
	}

	count = value->_hoops_AIPCR;
	POOL_ALLOC_ARRAY (table, count, long, _hoops_RIGC->memory_pool);
	value->value._hoops_RARHA = table;

	_hoops_PCCAR {
		if ((_hoops_SSACR = HI_Scan_Long (_hoops_RIGC, _hoops_SSGCC, null, table++)) != null)
			return _hoops_ISGCC (value, _hoops_SSACR);

		if (--count == 0)
			break;
		if (*(*_hoops_SSGCC)++ != ',')
			return _hoops_HSGCC (value);
		while (**_hoops_SSGCC == ' ')
			++*_hoops_SSGCC;
	}
	return null;
}

local char const * _hoops_PGRCC (
	_hoops_AIGPR *	_hoops_RIGC,
	Option_Value *			value,
	char const **			_hoops_SSGCC) {
	POINTER_SIZED_INT *		table;
	int						count;
	char const *			_hoops_SSACR;

	/* _hoops_IRS _hoops_SSRR _hoops_HIGR _hoops_IIGR _hoops_CAPR */
	if (value->type->_hoops_RHSAA < 0 && value->_hoops_AIPCR > 1) {
		int				_hoops_GGRCC = 1;
		char const		*_hoops_RPPA = *_hoops_SSGCC;

		_hoops_RGGA (*_hoops_RPPA == '\0' || *_hoops_RPPA == ')')
			if (*_hoops_RPPA++ == ',')			/* _hoops_HPIH _hoops_SPR */
				if (++_hoops_GGRCC == value->_hoops_AIPCR)
					break;

		value->_hoops_AIPCR = _hoops_GGRCC;
	}

	count = value->_hoops_AIPCR;
	POOL_ALLOC_ARRAY (table, count, POINTER_SIZED_INT, _hoops_RIGC->memory_pool);
	value->value._hoops_CGSAP = table;

	_hoops_PCCAR {
		if ((_hoops_SSACR = HI_Scan_Ptr (_hoops_RIGC, _hoops_SSGCC, null, table++)) != null)
			return _hoops_ISGCC (value, _hoops_SSACR);

		if (--count == 0)
			break;
		if (*(*_hoops_SSGCC)++ != ',')
			return _hoops_HSGCC (value);
		while (**_hoops_SSGCC == ' ')
			++*_hoops_SSGCC;
	}
	return null;
}




local char const * _hoops_HGRCC (
	_hoops_AIGPR *	_hoops_RIGC,
	Option_Value *			value,
	char const **			_hoops_SSGCC) {
	float *					table;
	int						count;
	char const *			_hoops_SSACR;

	/* _hoops_IRS _hoops_SSRR _hoops_HIGR _hoops_IIGR _hoops_CAPR */
	if (value->type->_hoops_RHSAA < 0 && value->_hoops_AIPCR > 1) {
		int				_hoops_GGRCC = 1;
		char const		*_hoops_RPPA = *_hoops_SSGCC;

		_hoops_RGGA (*_hoops_RPPA == '\0' || *_hoops_RPPA == ')')
			if (*_hoops_RPPA++ == ',')			/* _hoops_HPIH _hoops_SPR */
				if (++_hoops_GGRCC == value->_hoops_AIPCR)
					break;

		value->_hoops_AIPCR = _hoops_GGRCC;
	}

	count = value->_hoops_AIPCR;
	POOL_ALLOC_ARRAY (table, count, float, _hoops_RIGC->memory_pool);
	value->value._hoops_PIPCR = table;

	_hoops_PCCAR {
		if ((_hoops_SSACR = HI_Scan_Float (_hoops_RIGC, _hoops_SSGCC, null, table++)) != null)
			return _hoops_ISGCC (value, _hoops_SSACR);

		if (--count == 0)
			break;
		if (*(*_hoops_SSGCC)++ != ',')
			return _hoops_HSGCC (value);
		while (**_hoops_SSGCC == ' ')
			++*_hoops_SSGCC;
	}
	return null;
}


local char const *_hoops_IGRCC (
	_hoops_AIGPR *	_hoops_RIGC,
	Option_Value *			value,
	char const **			_hoops_SSGCC) {
	_hoops_AGSAP *		table;
	int						count;
	char const *			_hoops_SSACR;

	/* _hoops_IRS _hoops_SSRR _hoops_HIGR _hoops_IIGR _hoops_CAPR */
	if (value->type->_hoops_RHSAA < 0 && value->_hoops_AIPCR > 1) {
		int				_hoops_GGRCC = 1;
		char const		*_hoops_RPPA = *_hoops_SSGCC;

		_hoops_RGGA (*_hoops_RPPA == '\0' || *_hoops_RPPA == ')')
			if (*_hoops_RPPA++ == ',')			/* _hoops_HPIH _hoops_SPR */
				if (++_hoops_GGRCC == value->_hoops_AIPCR)
					break;

		value->_hoops_AIPCR = _hoops_GGRCC;
	}

	count = value->_hoops_AIPCR;
	POOL_ALLOC_ARRAY (table, count, _hoops_AGSAP, _hoops_RIGC->memory_pool);
	value->value._hoops_RRRHA = table;

	_hoops_PCCAR {
		int						_hoops_ACIPP;
		_hoops_HCRPR					name;
		_hoops_GCIIR *		_hoops_SPHHR;
		_hoops_PIIIR *			type;
		bool					_hoops_CGRCC = false;

		if ((_hoops_SSACR = HI_Scan_Float (_hoops_RIGC, _hoops_SSGCC, null, &table->value)) != null) {
			table->value = 0.0f;
			_hoops_CGRCC = true;
		}

		while (**_hoops_SSGCC == ' ') ++*_hoops_SSGCC;
		if (**_hoops_SSGCC != '\0' && **_hoops_SSGCC != ',' && **_hoops_SSGCC != ')') {
			if ((_hoops_SSACR = HI_Scan_Name (_hoops_RIGC, _hoops_SSGCC, null, &name)) != null)
				return _hoops_ISGCC (value, _hoops_SSACR);
		}
		else {							/* _hoops_PSP _hoops_RSIRR -- _hoops_GHCA _hoops_SHH _hoops_RPRI */
			name.length = 0;
			name.text = null;		/* _hoops_SAHR _hoops_CPHP */
		}

		_hoops_SPHHR = value->type->_hoops_CIIIR;

		_hoops_PCIPP (name, _hoops_ACIPP);
		type = _hoops_SPHHR->table[_hoops_ACIPP & (_hoops_SPHHR->size - 1)];

		if (type != null) {
			do if (_hoops_RAHSR (type->name, name))
				break;
			while ((type = type->next) != null);
		}

		if (type == null) {
			_hoops_SSACR = Sprintf_NN (null,
							  "'%n' is not a reasonable units specifier for '%n'",
							  &name, &value->type->name);
			_hoops_RGAIR (name);
			return _hoops_SSACR;
		}
		_hoops_RGAIR (name);

		if (_hoops_CGRCC && !type->_hoops_GHSAA)
			return _hoops_ISGCC (value, _hoops_SSACR);

		table->_hoops_HHP = type->id;
		++table;

		if (--count == 0)
			break;
		if (*(*_hoops_SSGCC)++ != ',')
			return _hoops_HSGCC (value);
		while (**_hoops_SSGCC == ' ')
			++*_hoops_SSGCC;
	}
	return null;
}


local char const * _hoops_SGRCC (
	_hoops_AIGPR *	_hoops_RIGC,
	Option_Value *			value,
	char const **			_hoops_SSGCC) {
	_hoops_HCRPR *					table;
	int						count;
	char const *			_hoops_SSACR;

	/* _hoops_IRS _hoops_SSRR _hoops_HIGR _hoops_IIGR _hoops_CAPR */
	if (value->type->_hoops_RHSAA < 0 && value->_hoops_AIPCR > 1) {
		int					_hoops_GGRCC = 1;
		char const *		_hoops_RPPA = *_hoops_SSGCC;

		_hoops_RGGA (*_hoops_RPPA == '\0' || *_hoops_RPPA == ')') {
			if (*_hoops_RPPA == '\'') {
				_hoops_PCCAR {
					if (*++_hoops_RPPA == '\'') {
						if (*++_hoops_RPPA == '\'')
							++_hoops_RPPA;
						else
							break;
					}
					if (*_hoops_RPPA == '\0')
						goto _hoops_PCPPR;
				}
			}
			else if (*_hoops_RPPA == '"') {
				_hoops_PCCAR {
					if (*++_hoops_RPPA == '"') {
						if (*++_hoops_RPPA == '"')
							++_hoops_RPPA;
						else
							break;
					}
					if (*_hoops_RPPA == '\0')
						goto _hoops_PCPPR;
				}
			}
			else if (*_hoops_RPPA == '`') {
				_hoops_PCCAR {
					if (*++_hoops_RPPA == '`') {
						if (*++_hoops_RPPA == '`')
							++_hoops_RPPA;
						else break;
					}
					if (*_hoops_RPPA == '\0')
						goto _hoops_PCPPR;
				}
			}
			else if (*_hoops_RPPA++ == ',')				/* _hoops_HPIH _hoops_SPR */
				if (++_hoops_GGRCC == value->_hoops_AIPCR)
					break;
		}
		_hoops_PCPPR:;
		value->_hoops_AIPCR = _hoops_GGRCC;
	}

	count = value->_hoops_AIPCR;
	POOL_ALLOC_ARRAY (table, count, _hoops_HCRPR, _hoops_RIGC->memory_pool);
	value->value._name = table;

	_hoops_PCCAR {
		if ((_hoops_SSACR = HI_Scan_Name (_hoops_RIGC, _hoops_SSGCC, null, table)) != null) {
			_hoops_RGGA (--count < 0) table->length = 0, ++table;
			return _hoops_ISGCC (value, _hoops_SSACR);
		}

		++table;

		if (--count == 0)
			break;

		if (*(*_hoops_SSGCC)++ != ',') {
			_hoops_RGGA (--count < 0) table->length = 0, ++table;
			return _hoops_HSGCC (value);
		}

		while (**_hoops_SSGCC == ' ') ++*_hoops_SSGCC;
	}
	return null;
}


local char const * _hoops_GRRCC (
	_hoops_AIGPR *	_hoops_RIGC,
	Option_Value *			value,
	char const **			_hoops_SSGCC) {
	_hoops_HCRPR *					table;
	int						count;
	char const *			_hoops_SSACR;

	/* _hoops_IRS _hoops_SSRR _hoops_HIGR _hoops_IIGR _hoops_CAPR */
	if (value->type->_hoops_RHSAA < 0 && value->_hoops_AIPCR > 1) {
		int				_hoops_GGRCC = 1;
		char const		*_hoops_RPPA = *_hoops_SSGCC;

		_hoops_RGGA (*_hoops_RPPA == '\0' || *_hoops_RPPA == ')')
			if (*_hoops_RPPA++ == ',')			/* _hoops_HPIH _hoops_SPR */
				if (++_hoops_GGRCC == value->_hoops_AIPCR)
					break;

		value->_hoops_AIPCR = _hoops_GGRCC;
	}

	count = value->_hoops_AIPCR;
	POOL_ALLOC_ARRAY (table, count, _hoops_HCRPR, _hoops_RIGC->memory_pool);
	value->value._name = table;

	_hoops_PCCAR {
		if ((_hoops_SSACR = HI_Scan_String (_hoops_RIGC, _hoops_SSGCC, null, table)) != null) {
			_hoops_RGGA (--count < 0) table->length = 0, ++table;
			return _hoops_ISGCC (value, _hoops_SSACR);
		}

		++table;

		if (--count == 0)
			break;

		if (*(*_hoops_SSGCC)++ != ',') {
			_hoops_RGGA (--count < 0) table->length = 0, ++table;
			return _hoops_HSGCC (value);
		}

		while (**_hoops_SSGCC == ' ') ++*_hoops_SSGCC;
	}

	return null;
}


local char const * _hoops_RRRCC (
	_hoops_AIGPR *	_hoops_RIGC,
	Option_Value *			value,
	char const **			_hoops_SSGCC) 
{
	char const *			_hoops_RPPA = *_hoops_SSGCC;

	if (*_hoops_RPPA != '=')
		value->_hoops_AIPCR = 0;
	else {
		char const		*_hoops_SSRPR;
		int				_hoops_CCS = 0;

		/* _hoops_RHPC _hoops_GPRI */

		do {} while (*++_hoops_RPPA == ' ');		/* _hoops_ISGR _hoops_RH = _hoops_PPR _hoops_GII _hoops_ARRCC */

		_hoops_SSRPR = _hoops_RPPA;		/* _hoops_SSS _hoops_RH _hoops_RSGR */
		_hoops_PCCAR switch (*_hoops_SSRPR++) {
			case '\'': case '"': case '`': {
				char			_hoops_PRRCC = _hoops_SSRPR[-1];

				_hoops_PCCAR {
					if (*_hoops_SSRPR == '\0')
						return "Mismatched quote marks";
					if (*_hoops_SSRPR++ == _hoops_PRRCC) {
						if (*_hoops_SSRPR == _hoops_PRRCC)
							++_hoops_SSRPR;
						else break;
					}
				}
			}	break;

			case '(': {
				++_hoops_CCS;
			}	break;

			case ')': {
				if (--_hoops_CCS < 0)
					return "Too many )'s";
			}	break;

			case '\0': case ',': {
				if (_hoops_CCS == 0)
					goto _hoops_PCPPR;
				if (_hoops_SSRPR[-1] == '\0')
					return "Too many ('s";
			}	break;
		}
		_hoops_PCPPR:;

		*_hoops_SSGCC = --_hoops_SSRPR;

		while (_hoops_SSRPR > _hoops_RPPA && _hoops_SSRPR[-1] == ' ') --_hoops_SSRPR;

		POOL_ALLOC_ARRAY (value->value._name, 1, _hoops_HCRPR, _hoops_RIGC->memory_pool);
		value->_hoops_AIPCR = 1;

		if (_hoops_RPPA == _hoops_SSRPR)
			value->value._name->length = 0;
		else {
			int				size = _hoops_SSRPR - _hoops_RPPA;
			char			*ptr;
			POOL_ALLOC_ARRAY (ptr, size+1, char, _hoops_RIGC->memory_pool);
			value->value._name->length = size;
			value->value._name->text = ptr;
			_hoops_RGGA (--size < 0) *ptr++ = *_hoops_RPPA++;
			*ptr = '\0';
		}
	}

	return null;
}

#ifndef DISABLE_UNICODE_OPTIONS
local char const * _hoops_HRRCC (
	_hoops_AIGPR *	_hoops_RIGC,
	Option_Value *			value,
	Karacter const **		_hoops_IRRCC) 
{
	Karacter const *		_hoops_IHSCP = *_hoops_IRRCC;

	if (*_hoops_IHSCP != '=')
		value->_hoops_AIPCR = 0;
	else {
		Karacter const		*_hoops_CRRCC;
		int						_hoops_CCS = 0;

		/* _hoops_RHPC _hoops_GPRI */

		do {} while (*++_hoops_IHSCP == ' ');		/* _hoops_ISGR _hoops_RH = _hoops_PPR _hoops_GII _hoops_ARRCC */

		_hoops_CRRCC = _hoops_IHSCP;		/* _hoops_SSS _hoops_RH _hoops_RSGR */
		_hoops_PCCAR switch (*_hoops_CRRCC++) {
			case '\'': case '"': case '`': {
				char			_hoops_PRRCC = (char)_hoops_CRRCC[-1];

				_hoops_PCCAR {
					if (*_hoops_CRRCC == '\0')
						return "Mismatched quote marks";
					if (*_hoops_CRRCC++ == _hoops_PRRCC) {
						if (*_hoops_CRRCC == _hoops_PRRCC)
							++_hoops_CRRCC;
						else break;
					}
				}
			}	break;

			case '(': {
				++_hoops_CCS;
			}	break;

			case ')': {
				if (--_hoops_CCS < 0)
					return "Too many )'s";
			}	break;

			case '\0': case ',': {
				if (_hoops_CCS == 0)
					goto _hoops_PCPPR;
				if (_hoops_CRRCC[-1] == '\0')
					return "Too many ('s";
			}	break;
		}
		_hoops_PCPPR:;

		*_hoops_IRRCC = --_hoops_CRRCC;

		while (_hoops_CRRCC > _hoops_IHSCP && _hoops_CRRCC[-1] == ' ') --_hoops_CRRCC;

		POOL_ALLOC_ARRAY (value->value._hoops_HGSAP, 1, KName, _hoops_RIGC->memory_pool);
		value->_hoops_AIPCR = 1;

		if (_hoops_IHSCP == _hoops_CRRCC)
			value->value._hoops_HGSAP->length = 0;
		else {
			int				size = _hoops_CRRCC - _hoops_IHSCP;
			Karacter		*ptr;
			POOL_ALLOC_ARRAY (ptr, size+1, Karacter, _hoops_RIGC->memory_pool);
			value->value._hoops_HGSAP->length = size;
			value->value._hoops_HGSAP->_hoops_IPPPP = ptr;
			_hoops_RGGA (--size < 0) *ptr++ = *_hoops_IHSCP++;
			*ptr = 0;
		}
	}

	return null;
}
#endif

/* _hoops_GRH _hoops_RSIRR _hoops_HII _hoops_SRRCC */
local _hoops_SRHSR		_hoops_GARCC = _hoops_GRRCR ("unknown request");


GLOBAL_FUNCTION bool HI_Parse_Options (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			_hoops_SICIH,
	_hoops_GCIIR *		_hoops_SPHHR,
	Option_Value **			_hoops_GCCIH,
	int						flags) 
{
	char const *			_hoops_RARCC = _hoops_SICIH;
	Option_Value **			_hoops_SRRGI = _hoops_GCCIH;
	_hoops_AIGCC *				_hoops_AARCC = null;

	*_hoops_GCCIH = null;

	while (*_hoops_RARCC == ' ') 
		++_hoops_RARCC;

	if (BIT (flags, _hoops_IPSAP)) {
		/* _hoops_AGSIP _hoops_IS _hoops_HGCR _hoops_PAGIR _hoops_SIHC _hoops_CGI _hoops_RHIR */
		if (sizeof (_hoops_AIGCC *) != sizeof (_hoops_PIIIR **))
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Whatzit size");

		_hoops_AARCC = (_hoops_AIGCC *)_hoops_SPHHR;
		_hoops_SPHHR = _hoops_AARCC->_hoops_CIIIR;

		if (*_hoops_RARCC == ')' || *_hoops_RARCC == '\0') { /* _hoops_CPHR */
			*_hoops_AARCC->_hoops_PIGCC = _hoops_RARCC;
			return true;
		}
	}
	else {		/* _hoops_GSSR _hoops_AGIR */
		if (*_hoops_RARCC == '\0')
			return true; /* _hoops_CPHR _hoops_AIAH */
	}

	if (_hoops_SPHHR->table == null) {
		_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Options table is empty");
		return false;
	}


	_hoops_PCCAR {
		_hoops_HCRPR				name;
		_hoops_PIIIR	*		type;
		char const *		_hoops_SSACR;
		Option_Value *		value;
		bool				_hoops_GCACR = false;
		int					_hoops_ACIPP;
		bool				_hoops_IIGCC;

		if ((_hoops_SSACR = HI_Scan_Name (_hoops_RIGC, &_hoops_RARCC, null, &name)) != null) {
			_hoops_HAARA (_hoops_RIGC, _hoops_SICIH, _hoops_GCCIH, _hoops_SSACR, flags);
			break;
		}

		_hoops_PCIPP (name, _hoops_ACIPP);
		_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);
		type = _hoops_SPHHR->table[_hoops_ACIPP & (_hoops_SPHHR->size - 1)];

		if (type != null) {
			do if (_hoops_RAHSR (type->name, name))
				break;
			while ((type = type->next) != null);
		}

		if (type == null && _hoops_SPHHR == _hoops_CIACR (_hoops_AIRGI)) {
			_hoops_PCIPP (_hoops_GARCC, _hoops_ACIPP);
			type = _hoops_SPHHR->table[_hoops_ACIPP & (_hoops_SPHHR->size - 1)];
			if (type != null) {
				do if (_hoops_RAHSR (type->name, _hoops_GARCC))
					break;
				while ((type = type->next) != null);
			}
		}
		_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);

		if (type == null) {
			if (name.length > 3 &&
				name.text[0] == 'n' &&
				name.text[1] == 'o' &&
				name.text[2] == ' ') {

				_hoops_HCRPR			_hoops_PARCC;

				_hoops_PARCC.length = name.length - 3;
				_hoops_PARCC.text = name.text + 3;
				while (*_hoops_PARCC.text == ' ') { /* (_hoops_PAH'_hoops_RA _hoops_SHH _hoops_HCR _hoops_ARRCC) */
					--_hoops_PARCC.length;
					++_hoops_PARCC.text;
				}

				_hoops_PCIPP (_hoops_PARCC, _hoops_ACIPP);
				_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);
				type = _hoops_SPHHR->table[_hoops_ACIPP & (_hoops_SPHHR->size - 1)];

				if (type != null) {
					do if (_hoops_RAHSR (type->name, _hoops_PARCC))
						break;
					while ((type = type->next) != null);
				}
				_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);

				if (type == null) {
					if (_hoops_SPHHR == _hoops_CIACR (_hoops_SAPPP))
						type = _hoops_CIGCC (&_hoops_PARCC, _hoops_ACIPP);
					else if (_hoops_SPHHR == _hoops_CIACR (_hoops_GGPCA))
						type = _hoops_RSGCC (&_hoops_PARCC, _hoops_ACIPP);
					else {
						_hoops_SSACR = Sprintf_NN (null,"Neither '%n' nor '%n' was found in the current tables", &_hoops_PARCC, &name);
						_hoops_RGAIR (name);
						return _hoops_HAARA (_hoops_RIGC, _hoops_SICIH, _hoops_GCCIH, _hoops_SSACR, flags);
					}
				}

				if (!type->_hoops_GHSAA && !BIT (flags, _hoops_CGPCR)) {
					_hoops_SSACR = Sprintf_NN (null,"Option '%n' is not negatable and '%n' was not found",&_hoops_PARCC, &name);
					_hoops_RGAIR (name);
					return _hoops_HAARA (_hoops_RIGC, _hoops_SICIH, _hoops_GCCIH, _hoops_SSACR, flags);
				}

				if (*_hoops_RARCC == '=') {
					_hoops_SSACR = Sprintf_N (null,"A negated option ('%n') doesn't take any parameters",&name);
					_hoops_RGAIR (name);
					return _hoops_HAARA (_hoops_RIGC, _hoops_SICIH, _hoops_GCCIH, _hoops_SSACR, flags);
				}

				_hoops_GCACR = true;
			}
			else {		/* _hoops_HAR _hoops_GSGI, _hoops_PPR _hoops_HAR "_hoops_PSP _hoops_HARCC" */
				if (_hoops_SPHHR == _hoops_CIACR (_hoops_SAPPP))
					type = _hoops_CIGCC (&name, _hoops_ACIPP);
				else if (_hoops_SPHHR == _hoops_CIACR (_hoops_GGPCA))
					type = _hoops_RSGCC (&name, _hoops_ACIPP);
				else {
					_hoops_SSACR = Sprintf_N (null,"Option '%n' was not found in the current tables",&name);
					_hoops_RGAIR (name);
					return _hoops_HAARA (_hoops_RIGC, _hoops_SICIH, _hoops_GCCIH, _hoops_SSACR, flags);
				}
			}
		}

		_hoops_RGAIR (name);


		/* _hoops_ARPR _hoops_RH _hoops_CCAH _hoops_PIRA */
		POOL_ZALLOC (value, Option_Value, _hoops_RIGC->memory_pool);

		value->type = type;
		_hoops_PRRH (type);
		value->_hoops_SGSAP = type->_hoops_RCIIR;	/* _hoops_CCGR _hoops_GIPCR _hoops_IAII */
		value->_hoops_GCACR = _hoops_GCACR;
		value->_hoops_AIPCR = type->_hoops_RHSAA;
		if (value->_hoops_AIPCR < 0)
			value->_hoops_AIPCR = -value->_hoops_AIPCR;

		*_hoops_SRRGI = value;
		_hoops_SRRGI = &value->next;

		/* _hoops_CISA _hoops_GGR _hoops_RH _hoops_HSH, _hoops_RPP _hoops_GII */
		if (_hoops_GCACR) {}
		else if (type->_hoops_RHSAA == 0) {		/* _hoops_IARCC _hoops_PSP _hoops_GRPAR */
			value->value._hoops_RIARA = null;
			if (*_hoops_RARCC == '=') {
				do {} while (*++_hoops_RARCC == ' ');

				_hoops_IIGCC = false;
				if (*_hoops_RARCC == '(') {
					_hoops_IIGCC = true;
					do {} while (*++_hoops_RARCC == ' ');
				}

				if (HI_Scan_Boolean (_hoops_RIGC, &_hoops_RARCC, null, &value->_hoops_GCACR) != null)
					return _hoops_HAARA (_hoops_RIGC, _hoops_SICIH, _hoops_GCCIH,
					 "Expected either no parameter, or one on/off-style parameter", flags);

				value->_hoops_GCACR = !value->_hoops_GCACR;

				if (value->_hoops_GCACR && !type->_hoops_GHSAA) {
					_hoops_SSACR = Sprintf_N (null, "Option '%n' is not negatable", &type->name);
					_hoops_RGAIR (name);
					return _hoops_HAARA (_hoops_RIGC, _hoops_SICIH, _hoops_GCCIH, _hoops_SSACR, flags);
				}

				if (_hoops_IIGCC) {
					if (*_hoops_RARCC != ')')
						return _hoops_HAARA (_hoops_RIGC, _hoops_SICIH, _hoops_GCCIH,
							*_hoops_RARCC == ',' ?
							  Sprintf_ND (null,"Too many values for '%n' - only %d are needed",&type->name, type->_hoops_RHSAA) :
							  Sprintf_N (null,"Mismatched ()'s or illegal character after '%n ='",&type->name), flags);

					do {} while (*++_hoops_RARCC == ' ');
				}
			}
		}
		else if (type->_hoops_RCIIR == _hoops_HRSAP) {
			/* _hoops_GRH _hoops_PHSPR */
			if ((_hoops_SSACR = _hoops_RRRCC (_hoops_RIGC, value, &_hoops_RARCC)) != null)
				return _hoops_HAARA (_hoops_RIGC, _hoops_SICIH, _hoops_GCCIH,Sprintf_SN (null, "%s in option '%n'",_hoops_SSACR, &type->name), flags);
		}
		else if (*_hoops_RARCC == '=' &&		/* _hoops_GRPAR _hoops_ICPAA */
				 (!BIT (flags, _hoops_CGPCR) || type->_hoops_RCIIR >= _hoops_GHAGA)) {
			do {} while (*++_hoops_RARCC == ' ');

			_hoops_IIGCC = false;
			if (*_hoops_RARCC == '(') {
				_hoops_IIGCC = true;
				do {} while (*++_hoops_RARCC == ' ');
			}
			else if (type->_hoops_RHSAA > 1)
				return _hoops_HAARA (_hoops_RIGC, _hoops_SICIH, _hoops_GCCIH,
					Sprintf_N (null,"Expected parenthesized list of values for '%n'",&type->name), flags);
			else if (type->_hoops_RHSAA < -1)
				value->_hoops_AIPCR = 1; /* _hoops_SAIPR _hoops_RH _hoops_CARCC */

			switch (type->_hoops_RCIIR) {
				case _hoops_RRSAP: {
					_hoops_SSACR = _hoops_CSGCC (_hoops_RIGC, value, &_hoops_RARCC);
				}	break;
				case _hoops_SPPCR: {
					_hoops_SSACR = _hoops_HGRCC (_hoops_RIGC, value, &_hoops_RARCC);
				}	break;
				case _hoops_CIGHA: {
					_hoops_SSACR = _hoops_IGRCC (_hoops_RIGC, value, &_hoops_RARCC);
				}	break;
				case _hoops_APRCA:
				case _hoops_CASAP: {
					_hoops_SSACR = _hoops_RGRCC (_hoops_RIGC, value, &_hoops_RARCC);
				}	break;
				case _hoops_PRRCR: {
					_hoops_SSACR = _hoops_SGRCC (_hoops_RIGC, value, &_hoops_RARCC);
				}	break;
				case _hoops_ARSAP: {
					_hoops_SSACR = _hoops_GRRCC (_hoops_RIGC, value, &_hoops_RARCC);
				}	break;
				case _hoops_SIGHA: {
					_hoops_SSACR = _hoops_AGRCC (_hoops_RIGC, value, &_hoops_RARCC);
				}	break;
				case _hoops_IRSAP: {
					_hoops_SSACR = _hoops_PGRCC (_hoops_RIGC, value, &_hoops_RARCC);
				}	break;

				case _hoops_AASAP:
				case _hoops_HASAP:
				case _hoops_IASAP: {
					if (type->_hoops_RCIIR == _hoops_AASAP) {
						int				*table;

						/* _hoops_HPPR _hoops_IH _hoops_IRS _hoops_RSRA _hoops_SCSH _hoops_PIRA */
						value->_hoops_AIPCR = 1;
						POOL_ALLOC_ARRAY (table, 1, int, _hoops_RIGC->memory_pool);
						value->value._hoops_RIARA = table;

						value->_hoops_SGSAP = _hoops_APRCA;
						if ((_hoops_SSACR = HI_Scan_Integer (_hoops_RIGC, &_hoops_RARCC, null, table)) == null)
							break;

						/* _hoops_SARS'_hoops_RA _hoops_HGCR _hoops_PCCP _hoops_SCSH, _hoops_CASI _hoops_GH & _hoops_SAS _hoops_CCA _hoops_PASAP */
						FREE_ARRAY (table, 1, int);
					}
					else if (type->_hoops_RCIIR == _hoops_HASAP) {
						POINTER_SIZED_INT	*table;

						/* _hoops_HPPR _hoops_IH _hoops_IRS _hoops_RSRA _hoops_CRS _hoops_PIRA */
						value->_hoops_AIPCR = 1;
						POOL_ALLOC_ARRAY (table, 1, POINTER_SIZED_INT, _hoops_RIGC->memory_pool);
						value->value._hoops_CGSAP = table;

						value->_hoops_SGSAP = _hoops_IRSAP;
						if ((_hoops_SSACR = HI_Scan_Ptr (_hoops_RIGC, &_hoops_RARCC, null, table)) == null)
							break;

						/* _hoops_SARS'_hoops_RA _hoops_HGCR _hoops_PCCP _hoops_SCSH, _hoops_CASI _hoops_GH & _hoops_SAS _hoops_CCA _hoops_PASAP */
						FREE_ARRAY (table, 1, POINTER_SIZED_INT);
					}
					else {
						float			*table;

						/* _hoops_HPPR _hoops_IH _hoops_IRS _hoops_RSRA _hoops_AIIC _hoops_PIRA */
						value->_hoops_AIPCR = 1;
						POOL_ALLOC_ARRAY (table, 1, float, _hoops_RIGC->memory_pool);
						value->value._hoops_PIPCR = table;

						value->_hoops_SGSAP = _hoops_SPPCR;
						if ((_hoops_SSACR = HI_Scan_Float (_hoops_RIGC, &_hoops_RARCC, null, table)) == null)
							break;

						/* _hoops_SARS'_hoops_RA _hoops_HGCR _hoops_IRS _hoops_AIIC, _hoops_CASI _hoops_GH & _hoops_SAS _hoops_CCA _hoops_PASAP */
						FREE_ARRAY (table, 1, float);
					}
					value->value._hoops_IGSAP = null;
					value->_hoops_AIPCR = type->_hoops_RHSAA;
					if (value->_hoops_AIPCR < 0)
						value->_hoops_AIPCR = -value->_hoops_AIPCR;
					value->_hoops_SGSAP = _hoops_GHAGA;
				}	_hoops_HHHI;

				case _hoops_GHAGA: {
					_hoops_AIGCC			_hoops_SARCC;

					_hoops_SARCC._hoops_PIGCC = &_hoops_RARCC;
					_hoops_SARCC._hoops_HIGCC = null;
					_hoops_SARCC._hoops_IIGCC = _hoops_IIGCC;
					_hoops_SARCC._hoops_CIIIR = type->_hoops_CIIIR;

					if (!HI_Parse_Options (_hoops_RIGC, _hoops_RARCC,
										   (_hoops_GCIIR *)&_hoops_SARCC,
										   &value->value.option_list,
										   flags | _hoops_IPSAP)) {
						value->value.option_list = null;

						_hoops_ASGCC (_hoops_RIGC, *_hoops_GCCIH);
						*_hoops_GCCIH=null;
						return false;
					}

					if (value->value.option_list == null) {
						value->_hoops_AIPCR = 0;

						if (type->_hoops_RHSAA > 0)
							return _hoops_HAARA (_hoops_RIGC, _hoops_SICIH, _hoops_GCCIH,
									Sprintf_N (null, "Can't find parameter list for '%n'",
									&type->name), flags);
					}
					else {
						value->_hoops_AIPCR = 1;

						/* _hoops_SHH _hoops_AGAPR - _hoops_RPP _hoops_RGAR _hoops_PGIIP _hoops_SPR, _hoops_RCRP _hoops_RH _hoops_CGHI _hoops_SPR */
						if (type->_hoops_RHSAA == 1 || type->_hoops_RHSAA == -1) {
							Option_Value *_hoops_AHSAA;

							_hoops_AHSAA = value->value.option_list;

							if (_hoops_AHSAA->next != null) {
								Option_Value *prev;
								do prev = _hoops_AHSAA, _hoops_AHSAA = _hoops_AHSAA->next;
								_hoops_RGGA (_hoops_AHSAA->next == null);
								prev->next = null;
								HI_Free_Option_List (_hoops_RIGC, value->value.option_list);
								value->value.option_list = _hoops_AHSAA;
							}
						}
					}

					_hoops_SSACR = null;
				}	break;

				default: {
					_hoops_SSACR = "Internal parse error";
				}	break;
			}

			if (_hoops_SSACR != null)
				return _hoops_HAARA (_hoops_RIGC, _hoops_SICIH, _hoops_GCCIH, _hoops_SSACR, flags);

			if (_hoops_IIGCC) {
				if (*_hoops_RARCC != ')')
					return _hoops_HAARA (_hoops_RIGC, _hoops_SICIH, _hoops_GCCIH,
						(*_hoops_RARCC == ',') ?
						  Sprintf_ND (null, "Too many values for '%n' - only %d are needed", &type->name, value->_hoops_AIPCR) :
						  Sprintf_N (null, "Mismatched ()'s or illegal character after '%n ='", &type->name), flags);

				do {} while (*++_hoops_RARCC == ' ');
			}
		}
		else {	/* _hoops_PSP "=". (_hoops_PSP _hoops_GRPAR.) */
			if (type->_hoops_RHSAA < 0 || BIT (flags, _hoops_CGPCR)) {
				/* _hoops_AHHR _hoops_HRGR _hoops_IRS _hoops_RPRI _hoops_PHI _hoops_IIGR _hoops_PRSAR */
				value->_hoops_AIPCR = 0;
				value->value._hoops_IGSAP = null;
			}
			else if (type->_hoops_RCIIR == _hoops_ARSAP &&
					 value->_hoops_AIPCR == 1) {
				_hoops_SSACR = "";
				(void)_hoops_GRRCC (_hoops_RIGC, value, (char const **)&_hoops_SSACR);
			}
			else if (type->_hoops_RCIIR == _hoops_PRRCR &&
					 value->_hoops_AIPCR == 1) {
				_hoops_SSACR = "''";
				(void)_hoops_SGRCC (_hoops_RIGC, value, (char const **)&_hoops_SSACR);
			}
			else if (type->_hoops_RCIIR == _hoops_RRSAP &&
					 value->_hoops_AIPCR == 1) {
				_hoops_SSACR = "on";
				(void)_hoops_CSGCC (_hoops_RIGC, value, (char const **)&_hoops_SSACR);
			}
			else {
				return _hoops_HAARA (_hoops_RIGC, _hoops_SICIH, _hoops_GCCIH,Sprintf_N (null, "Can't find parameter list for '%n'",&type->name), flags);
			}
		}

		if (*_hoops_RARCC == ',' && BIT (flags, _hoops_PAPCA))
			return _hoops_HAARA (_hoops_RIGC, _hoops_SICIH, _hoops_GCCIH,"Multiple options not allowed", flags);

		if (_hoops_AARCC == null) {	/* _hoops_GSSR _hoops_SCIA-_hoops_PAPA _hoops_RSGR _hoops_IIGR _hoops_HCSP */
			if (*_hoops_RARCC != ',') {
				if (*_hoops_RARCC == '\0')
					return true;
				else
					return _hoops_HAARA (_hoops_RIGC, _hoops_SICIH, _hoops_GCCIH,"Unexpected character found", flags);
			}
		}
		else {			/* _hoops_IRS _hoops_RSRA _hoops_RGSAP _hoops_PAR _hoops_IRS _hoops_RGSAP _hoops_HIGR */
			if (!(_hoops_AARCC->_hoops_IIGCC && *_hoops_RARCC == ',')) {
				*_hoops_AARCC->_hoops_PIGCC = _hoops_RARCC;
				return true;
			}
		}


		do {} while (*++_hoops_RARCC == ' ');

		if (*_hoops_RARCC == '\0')
			return _hoops_HAARA (_hoops_RIGC, _hoops_SICIH, _hoops_GCCIH,"Trailing comma found", flags);
	}

	return false;
}


#ifndef DISABLE_UNICODE_OPTIONS
local char const * _hoops_GPRCC (
	_hoops_AIGPR *	_hoops_RIGC,
	Karacter const **		_hoops_RPRCC,		/* _hoops_ASPR _hoops_IS _hoops_ASPR _hoops_IS _hoops_GSGR (_hoops_SRSS) */
	Karacter const *		_hoops_CRRCC,		/* _hoops_ASPR _hoops_IS _hoops_RSGR _hoops_IIGR _hoops_GSGR (_hoops_IRIGR) */
	KName *					_hoops_SIHSA)		/* _hoops_ASPR _hoops_IS _hoops_GHPP (_hoops_PHPH) */
{
	Karacter const *		_hoops_IHSCP = *_hoops_RPRCC;
	Karacter *				_hoops_APRCC;
	int						length = 0;
	Karacter const *		_hoops_PPRCC;
	Karacter const *		_hoops_HPRCC;
	local char const		_hoops_AIHGC[] = "Illegal character found, or expected name/string not found";

	/* _hoops_IGHHH: _hoops_IPRCC _hoops_RHIPP _hoops_GHCA _hoops_SHH _hoops_PGI 0-_hoops_CCGAI (_hoops_CPRCC _hoops_GRS
	 * _hoops_SHH _hoops_IRAP) _hoops_PAR _hoops_SPCC-_hoops_CCGAI (_hoops_CPRCC _hoops_GRS _hoops_SHH _hoops_GRAA-_hoops_IRAP). _hoops_SPRCC
	 * _hoops_IH _hoops_GHRCC _hoops_IS _hoops_CPRCC _hoops_GRS _hoops_IPHR _hoops_GGSR _hoops_GPRS _hoops_GGR _hoops_PGI _hoops_AGIR; _hoops_PCGC _hoops_IH
	 * _hoops_PACAR _hoops_IS _hoops_CPRCC _hoops_GRS _hoops_RRP _hoops_IS _hoops_SRS _hoops_ISPR _hoops_IH _hoops_CPRCC _hoops_IHGS _hoops_GRAA-_hoops_IRAP.
	 */

	if (_hoops_CRRCC != null && _hoops_IHSCP >= _hoops_CRRCC) return _hoops_AIHGC;

	while (*_hoops_IHSCP == ' ') if (++_hoops_IHSCP == _hoops_CRRCC) return _hoops_AIHGC;

	_hoops_PPRCC = _hoops_IHSCP;

	/* ('%' _hoops_HRGR _hoops_HAR _hoops_IRS _hoops_HAIHH _hoops_RGAR _hoops_IH _hoops_RH _hoops_SSCPR _hoops_IIGR
	 *	_hoops_RH '_hoops_IGIR _hoops_AAHP' _hoops_HCGR _hoops_HRCSR _hoops_HCSP.)
	 */

	_hoops_RGGA (_hoops_IHSCP == _hoops_CRRCC) switch (*_hoops_IHSCP++) {
		default: {
			++length;
		}	break;

		case '/': case '?': case '*': case '^': case ',':
		case '{': case '}': case '<': case '>': case '!': case '(':
		case ')': case '\0': case '\n': case '=': case '@': { /* _hoops_RHRCC! */
		}		goto _hoops_PCPPR;

		case '.': {		/* '...' _hoops_HRGR _hoops_IRS _hoops_HAIHH _hoops_HAH! */
			if (length >= 2 && _hoops_IHSCP[-2] == '.' && _hoops_IHSCP[-3] == '.') {
				_hoops_IHSCP -= 2;
				length -= 2;
				goto _hoops_PCPPR;
			}
			else
				++length;
		}	break;

		case '"': case '`': case '\'': {
			Karacter		_hoops_AHRCC = _hoops_IHSCP[-1];

			_hoops_PCCAR {
				if (_hoops_IHSCP == _hoops_CRRCC || *_hoops_IHSCP == '\0') return "Unbalanced quote marks";

				if (*_hoops_IHSCP++ != _hoops_AHRCC) ++length;
				else if (_hoops_IHSCP != _hoops_CRRCC && *_hoops_IHSCP == _hoops_AHRCC) ++length, ++_hoops_IHSCP;
				else break;
			}
		}	break;
	}
	_hoops_IHSCP++;		/* _hoops_CR _hoops_SR _hoops_PHRCC _hoops_HPP _hoops_HHRCC _hoops_RH _hoops_RSGR, _hoops_SHI _hoops_RH --_hoops_IHRCC _hoops_CAPP */

  _hoops_PCPPR:;

	/* _hoops_GASA: _hoops_RH _hoops_HSPR _hoops_PGCR _hoops_APGR _hoops_RSRHR _hoops_CHRCC _hoops_AHGSR _hoops_SGS _hoops_CHR _hoops_ICIC _hoops_IS _hoops_SSPC */
	_hoops_HPRCC = --_hoops_IHSCP;
	while (length > 0 && *--_hoops_IHSCP == ' ') --length;

	if (length == 0) {	/* _hoops_PIHA _hoops_HS _hoops_RPII _hoops_CGIGI _hoops_IRAP _hoops_GSGR */
		_hoops_SIHSA->length = 0;
		_hoops_SIHSA->_hoops_IPPPP = null;
	}
	else {
		POOL_ALLOC_ARRAY (_hoops_APRCC, length+1, Karacter, _hoops_RIGC->memory_pool);
		_hoops_SIHSA->length = length;
		_hoops_SIHSA->_hoops_IPPPP = _hoops_APRCC;

		_hoops_IHSCP = _hoops_PPRCC;

		do switch (*_hoops_IHSCP) {
			default:

			case 0337/*_hoops_SHRCC-_hoops_GIRCC*/:		case 0340/*_hoops_IRS`*/:
			case 0341/*_hoops_IRS'*/:		case 0342/*_hoops_IRS^*/:
			case 0343/*_hoops_IRS~*/:		case 0344/*_hoops_IRS"*/:
			case 0345/*_hoops_IRS.*/:		case 0346/*_hoops_RIRCC*/:
			case 0347/*_hoops_GSGGR,*/:		case 0350/*_hoops_IAS`*/:
			case 0351/*_hoops_IAS'*/:		case 0352/*_hoops_IAS^*/:
			case 0353/*_hoops_IAS"*/:		case 0354/*_hoops_HAS`*/:
			case 0355/*_hoops_HAS'*/:		case 0356/*_hoops_HAS^*/:
			case 0357/*_hoops_HAS"*/:		case 0360/*_hoops_AIRCC*/:
			case 0361/*_hoops_ACHP~*/:		case 0362/*_hoops_GCSR`*/:
			case 0363/*_hoops_GCSR'*/:		case 0364/*_hoops_GCSR^*/:
			case 0365/*_hoops_GCSR~*/:		case 0366/*_hoops_GCSR"*/:
			case 0370/*_hoops_GCSR/ */:		case 0371/*_hoops_IARGR`*/:
			case 0372/*_hoops_IARGR'*/:		case 0373/*_hoops_IARGR^*/:
			case 0374/*_hoops_IARGR"*/:		case 0375/*_hoops_HAPC'*/:
			case 0376/*_hoops_PIRCC*/:		case 0377/*_hoops_HAPC"*/:

			case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
			case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
			case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
			case 's': case 't': case 'u': case 'v': case 'w': case 'x':
			case 'y': case 'z': case '$': case '_': case '-': case '+':
			case '#': case ' ': case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7': case '8': case '9':
			case ':': case '&': case '.': case '%': case '[': case ']': {
				*_hoops_APRCC++ = *_hoops_IHSCP++;
			}	break;

			case 0300/*_hoops_RAIGR`*/:		case 0301/*_hoops_RAIGR'*/:
			case 0302/*_hoops_RAIGR^*/:		case 0303/*_hoops_RAIGR~*/:
			case 0304/*_hoops_RAIGR"*/:		case 0305/*_hoops_RAIGR.*/:
			case 0306/*_hoops_PAAIA*/:		case 0307/*_hoops_IHRPR,*/:
			case 0310/*_hoops_HRAIA`*/:		case 0311/*_hoops_HRAIA'*/:
			case 0312/*_hoops_HRAIA^*/:		case 0313/*_hoops_HRAIA"*/:
			case 0314/*_hoops_GHAP`*/:		case 0315/*_hoops_GHAP'*/:
			case 0316/*_hoops_GHAP^*/:		case 0317/*_hoops_GHAP"*/:
			case 0320/*_hoops_HIRCC-_hoops_AIRCC*/:		case 0321/*_hoops_PGGIR~*/:
			case 0322/*_hoops_RGGIR`*/:		case 0323/*_hoops_RGGIR'*/:
			case 0324/*_hoops_RGGIR^*/:		case 0325/*_hoops_RGGIR~*/:
			case 0326/*_hoops_RGGIR"*/:		case 0330/*_hoops_RGGIR/ */:
			case 0331/*_hoops_GRGGR`*/:		case 0332/*_hoops_GRGGR'*/:
			case 0333/*_hoops_GRGGR^*/:		case 0334/*_hoops_GRGGR"*/:
			case 0335/*_hoops_GHCR'*/:		case 0336/*_hoops_HIRCC-_hoops_PIRCC*/:

			case 'A': case 'B': case 'C': case 'D':
			case 'E': case 'F': case 'G': case 'H': case 'I': case 'J':
			case 'K': case 'L': case 'M': case 'N': case 'O': case 'P':
			case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V':
			case 'W': case 'X': case 'Y': case 'Z': {
				*_hoops_APRCC++ = _hoops_SHPCR (*_hoops_IHSCP), ++_hoops_IHSCP;
			}	break;


			case '"': case '`': case '\'': {
				Karacter		_hoops_AHRCC = *_hoops_IHSCP++;

				_hoops_PCCAR {
					if (*_hoops_IHSCP == _hoops_AHRCC) {
						if (*++_hoops_IHSCP == _hoops_AHRCC) {
							*_hoops_APRCC++ = *_hoops_IHSCP++;
							--length;
						}
						else break;
					}
					else {
						*_hoops_APRCC++ = *_hoops_IHSCP++;
						--length;
					}
				}
				++length;		/* (_hoops_GGSP _hoops_IHH --_hoops_SPCC _hoops_HPGR _hoops_RH _hoops_PRPC) */
			}	break;

#if 0
			default: {
				_hoops_RGAIR (*name);
				return "Illegal character found - try more quote marks?";
			}	/*_hoops_IHSA;*/
#endif
		}
		_hoops_RGGA (--length <= 0);
		*_hoops_APRCC = 0;
	}

	*_hoops_RPRCC = _hoops_HPRCC;
	return null;
}
#endif

GLOBAL_FUNCTION bool HI_Parse_KOptions (
	_hoops_AIGPR *	_hoops_RIGC,
	Karacter const *		_hoops_IIRCC,
	_hoops_GCIIR *		_hoops_SPHHR,
	Option_Value **			_hoops_GCCIH,
	int						flags) {
#ifndef DISABLE_UNICODE_OPTIONS
	Karacter const *		_hoops_CIRCC = _hoops_IIRCC;
	Option_Value **			_hoops_SRRGI;
	_hoops_AIGCC *				_hoops_AARCC = null;

	*_hoops_GCCIH = null;

	while (*_hoops_CIRCC == ' ') ++_hoops_CIRCC;

	if (BIT (flags, _hoops_IPSAP)) {
		/* _hoops_AGSIP _hoops_IS _hoops_HGCR _hoops_PAGIR _hoops_SIHC _hoops_CGI _hoops_RHIR */
		if (sizeof (_hoops_AIGCC *) != sizeof (_hoops_PIIIR **))
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Whatzit size");

		_hoops_AARCC = (_hoops_AIGCC *)_hoops_SPHHR;
		_hoops_SPHHR = _hoops_AARCC->_hoops_CIIIR;

		if (*_hoops_CIRCC == ')' || *_hoops_CIRCC == '\0') { /* _hoops_CPHR */
			*_hoops_AARCC->_hoops_HIGCC = _hoops_CIRCC;
			return true;
		}
	}
	else {		/* _hoops_GSSR _hoops_AGIR */
		if (*_hoops_CIRCC == '\0')
			return true; /* _hoops_CPHR _hoops_AIAH */
	}

	if (_hoops_SPHHR->table == null) {
		_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Options table is empty");
		return false;
	}


	_hoops_PCCAR {
		KName				_hoops_SIHSA;
		_hoops_RPSAP *		_hoops_HCGCC;
		char const *		_hoops_SSACR;
		Option_Value *		value;
		bool				_hoops_GCACR = false;
		int					_hoops_ACIPP;
		bool				_hoops_IIGCC;

		if ((_hoops_SSACR = _hoops_GPRCC (_hoops_RIGC, &_hoops_CIRCC, null, &_hoops_SIHSA)) != null) {
			_hoops_PSGCC (_hoops_RIGC, _hoops_IIRCC, _hoops_GCCIH, _hoops_SSACR);
			break;
		}

		_hoops_HCIPP (_hoops_SIHSA, _hoops_ACIPP);
		_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);
		_hoops_HCGCC = (_hoops_RPSAP *)_hoops_SPHHR->table[_hoops_ACIPP & (_hoops_SPHHR->size - 1)];

		if (_hoops_HCGCC != null) {
			do if (_hoops_RARPH (_hoops_HCGCC->_hoops_SIHSA, _hoops_SIHSA))
				break;
			while ((_hoops_HCGCC = _hoops_HCGCC->next) != null);
		}
		_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);


		if (_hoops_HCGCC == null) {
			if (_hoops_SIHSA.length > 3 &&
				_hoops_SIHSA._hoops_IPPPP[0] == 'n' &&
				_hoops_SIHSA._hoops_IPPPP[1] == 'o' &&
				_hoops_SIHSA._hoops_IPPPP[2] == ' ') {

				KName				_hoops_PARCC;

				_hoops_PARCC.length = _hoops_SIHSA.length - 3;
				_hoops_PARCC._hoops_IPPPP = _hoops_SIHSA._hoops_IPPPP + 3;
				while (*_hoops_PARCC._hoops_IPPPP == ' ') { /* (_hoops_PAH'_hoops_RA _hoops_SHH _hoops_HCR _hoops_ARRCC) */
					--_hoops_PARCC.length;
					++_hoops_PARCC._hoops_IPPPP;
				}

				_hoops_HCIPP (_hoops_PARCC, _hoops_ACIPP);
				_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);
				_hoops_HCGCC = (_hoops_RPSAP *)_hoops_SPHHR->table[_hoops_ACIPP & (_hoops_SPHHR->size - 1)];

				if (_hoops_HCGCC != null) {
					do if (_hoops_RARPH (_hoops_HCGCC->_hoops_SIHSA, _hoops_PARCC))
						break;
					while ((_hoops_HCGCC = _hoops_HCGCC->next) != null);
				}
				_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);

				if (_hoops_HCGCC == null)
					_hoops_HCGCC = _hoops_PCGCC (&_hoops_PARCC, _hoops_ACIPP);


				if (*_hoops_CIRCC == '=') {
					_hoops_PRPIR (_hoops_SIHSA);
					return _hoops_PSGCC (_hoops_RIGC, _hoops_IIRCC, _hoops_GCCIH, null);
				}

				_hoops_GCACR = true;
			}
			else		/* _hoops_HAR _hoops_GSGI, _hoops_PPR _hoops_HAR "_hoops_PSP _hoops_HARCC" */
				_hoops_HCGCC = _hoops_PCGCC (&_hoops_SIHSA, _hoops_ACIPP);
		}

		_hoops_PRPIR (_hoops_SIHSA);

		/* _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_GII _hoops_APRS _hoops_SPR _hoops_IIGR _hoops_RH _hoops_PSHR _hoops_GPRR */
		_hoops_SRRGI = _hoops_GCCIH;
		_hoops_RGGA ((value = *_hoops_SRRGI) == null) {
			if (value->type->id == _hoops_HCGCC->id) {
				*_hoops_SRRGI = value->next;
				value->next = null;

				HE_WARNING (HEC_OPTION_TYPE, HES_REDUNDANT,
							"Redundant setting of option discarded.");

				HI_Free_Option_List (_hoops_RIGC, value);

				if ((value = *_hoops_SRRGI) != null) {
					/* _hoops_PPSI _hoops_RH _hoops_CCAH _hoops_SPR _hoops_GPP _hoops_RH _hoops_RSGR - _hoops_RHHSR _hoops_RH _hoops_IPPHR
					 * _hoops_AGR. _hoops_CSH _hoops_GRH _hoops_SCPC.
					 */
					_hoops_RGGA (value->next == null) value = value->next;
					_hoops_SRRGI = &value->next;
				}
				break;
			}
			_hoops_SRRGI = &value->next;
		}

		/* _hoops_ARPR _hoops_RH _hoops_CCAH _hoops_PIRA */
		POOL_ALLOC (value, Option_Value, _hoops_RIGC->memory_pool);

		value->type = (_hoops_PIIIR *)_hoops_HCGCC;
		_hoops_PRRH (_hoops_HCGCC);
		value->_hoops_GCACR = _hoops_GCACR;
		value->value._hoops_IGSAP = null;
		value->_hoops_AIPCR = _hoops_HCGCC->_hoops_RHSAA;
		if (value->_hoops_AIPCR < 0)
			value->_hoops_AIPCR = -value->_hoops_AIPCR;

		value->next = *_hoops_SRRGI;
		*_hoops_SRRGI = value;

		/* _hoops_CISA _hoops_GGR _hoops_RH _hoops_HSH, _hoops_RPP _hoops_GII */
		if (_hoops_GCACR) {}
		else if (_hoops_HCGCC->_hoops_RCIIR == _hoops_CRSAP) {
			/* _hoops_GRH _hoops_PHSPR */
			if ((_hoops_SSACR = _hoops_HRRCC (_hoops_RIGC, value, &_hoops_CIRCC)) != null)
				return _hoops_PSGCC (_hoops_RIGC, _hoops_IIRCC, _hoops_GCCIH, null);
		}
		else if (*_hoops_CIRCC == '=' &&		/* _hoops_GRPAR _hoops_ICPAA */
				 (!BIT (flags, _hoops_CGPCR) || _hoops_HCGCC->_hoops_RCIIR == _hoops_GHAGA)) {
			do {} while (*++_hoops_CIRCC == ' ');

			_hoops_IIGCC = false;
			if (*_hoops_CIRCC == '(') {
				_hoops_IIGCC = true;
				do {} while (*++_hoops_CIRCC == ' ');
			}
			else if (_hoops_HCGCC->_hoops_RHSAA > 1)
				return _hoops_PSGCC (_hoops_RIGC, _hoops_IIRCC, _hoops_GCCIH,"Expected parenthesized list of values for Unicode Option");
			else if (_hoops_HCGCC->_hoops_RHSAA < -1)
				value->_hoops_AIPCR = 1; /* _hoops_SAIPR _hoops_RH _hoops_CARCC */

			switch (_hoops_HCGCC->_hoops_RCIIR) {
				case _hoops_GHAGA: {
					_hoops_AIGCC			_hoops_SARCC;

					_hoops_SARCC._hoops_PIGCC = null;
					_hoops_SARCC._hoops_HIGCC = &_hoops_CIRCC;
					_hoops_SARCC._hoops_IIGCC = _hoops_IIGCC;
					_hoops_SARCC._hoops_CIIIR = _hoops_HCGCC->_hoops_CIIIR;

					if (!HI_Parse_KOptions (_hoops_RIGC, _hoops_CIRCC,
										   (_hoops_GCIIR *)&_hoops_SARCC,
										   &value->value.option_list,
										   flags | _hoops_IPSAP)) {
						value->value.option_list = null;

						_hoops_ASGCC (_hoops_RIGC, *_hoops_GCCIH);
						*_hoops_GCCIH=null;
						return false;
					}

					if (value->value.option_list == null) {
						value->_hoops_AIPCR = 0;

						if (_hoops_HCGCC->_hoops_RHSAA > 0)
							return _hoops_PSGCC (_hoops_RIGC, _hoops_IIRCC, _hoops_GCCIH,
													"Can't find parameter list for Unicode Option");
					}
					else {
						value->_hoops_AIPCR = 1;

						/* _hoops_SHH _hoops_AGAPR - _hoops_RPP _hoops_RGAR _hoops_PGIIP _hoops_SPR, _hoops_RCRP _hoops_RH _hoops_CGHI _hoops_SPR */
						if (_hoops_HCGCC->_hoops_RHSAA == 1 || _hoops_HCGCC->_hoops_RHSAA == -1) {
							Option_Value *_hoops_AHSAA;

							_hoops_AHSAA = value->value.option_list;

							if (_hoops_AHSAA->next != null) {
								Option_Value *prev;
								do prev = _hoops_AHSAA, _hoops_AHSAA = _hoops_AHSAA->next;
								_hoops_RGGA (_hoops_AHSAA->next == null);
								prev->next = null;
								HI_Free_Option_List (_hoops_RIGC, value->value.option_list);
								value->value.option_list = _hoops_AHSAA;
							}
						}
					}

					_hoops_SSACR = null;
				}	break;

				default: {
					_hoops_SSACR = "Internal parse error";
				}	break;
			}

			if (_hoops_SSACR != null)
				return _hoops_PSGCC (_hoops_RIGC, _hoops_IIRCC, _hoops_GCCIH, _hoops_SSACR);

			if (_hoops_IIGCC) {
				if (*_hoops_CIRCC != ')')
					return _hoops_PSGCC (_hoops_RIGC, _hoops_IIRCC, _hoops_GCCIH,
						(*_hoops_CIRCC == ',') ?
						  Sprintf_D (null,"Too many values for Unicode Option - only %d are needed",value->_hoops_AIPCR) :
						  "Mismatched ()'s or illegal character after 'Unicode Option ='");

				do {} while (*++_hoops_CIRCC == ' ');
			}
		}

		if (*_hoops_CIRCC == ',' && BIT (flags, _hoops_PAPCA))
			return _hoops_PSGCC (_hoops_RIGC, _hoops_IIRCC, _hoops_GCCIH, "Multiple options not allowed");

		if (_hoops_AARCC == null) {	/* _hoops_GSSR _hoops_SCIA-_hoops_PAPA _hoops_RSGR _hoops_IIGR _hoops_HCSP */
			if (*_hoops_CIRCC != ',') {
				if (*_hoops_CIRCC == '\0')
					return true;
				else
					return _hoops_PSGCC (_hoops_RIGC, _hoops_IIRCC, _hoops_GCCIH,"Unexpected character found");
			}
		}
		else {			/* _hoops_IRS _hoops_RSRA _hoops_RGSAP _hoops_PAR _hoops_IRS _hoops_RGSAP _hoops_HIGR */
			if (!(_hoops_AARCC->_hoops_IIGCC && *_hoops_CIRCC == ',')) {
				*_hoops_AARCC->_hoops_HIGCC = _hoops_CIRCC;
				return true;
			}
		}


		do {} while (*++_hoops_CIRCC == ' ');

		if (*_hoops_CIRCC == '\0')
			return _hoops_PSGCC (_hoops_RIGC, _hoops_IIRCC, _hoops_GCCIH, "Trailing comma found");
	}
#endif

	return false;
}


// _hoops_AGCR _hoops_CHR _hoops_HAR _hoops_GPP _hoops_RH _hoops_ISSSH _hoops_ICGAR
GLOBAL_FUNCTION Option_Value * HI_Copy_Option_List (
	Option_Value const *	_hoops_GASGH) {
	Option_Value *			first;
	Option_Value **			_hoops_ASRGR = &first;

	if (_hoops_GASGH != null) do {
		Option_Value			*_hoops_RASGH;
		int						count;

		ZALLOC (_hoops_RASGH, Option_Value);
		*_hoops_ASRGR = _hoops_RASGH;
		_hoops_ASRGR = &_hoops_RASGH->next;
		_hoops_RASGH->type = _hoops_GASGH->type;
		_hoops_PRRH (_hoops_RASGH->type);
		_hoops_RASGH->_hoops_GCACR = _hoops_GASGH->_hoops_GCACR;
		_hoops_RASGH->_hoops_AIPCR = _hoops_GASGH->_hoops_AIPCR;

		if (_hoops_RASGH->_hoops_GCACR || (count = _hoops_RASGH->_hoops_AIPCR) == 0)
			_hoops_RASGH->value._hoops_IGSAP = null; /* (_hoops_IH _hoops_SIRCC) */
		else switch (_hoops_RASGH->type->_hoops_RCIIR) {
			case _hoops_RRSAP: {
				ALLOC_ARRAY (_hoops_RASGH->value._hoops_PGSAP, count, bool);
				count = _hoops_RASGH->_hoops_AIPCR - 1;
				do _hoops_RASGH->value._hoops_PGSAP[count] = _hoops_GASGH->value._hoops_PGSAP[count];
				_hoops_RGGA (--count < 0);
			}	break;

			case _hoops_SPPCR: {
				ALLOC_ARRAY (_hoops_RASGH->value._hoops_PIPCR, count, float);
				count = _hoops_RASGH->_hoops_AIPCR - 1;
				do _hoops_RASGH->value._hoops_PIPCR[count] = _hoops_GASGH->value._hoops_PIPCR[count];
				_hoops_RGGA (--count < 0);
			}	break;

			case _hoops_APRCA:	{
				ALLOC_ARRAY (_hoops_RASGH->value._hoops_RIARA, count, int);
				count = _hoops_RASGH->_hoops_AIPCR - 1;
				do _hoops_RASGH->value._hoops_RIARA[count] = _hoops_GASGH->value._hoops_RIARA[count];
				_hoops_RGGA (--count < 0);
			}	break;

			case _hoops_SIGHA:	{
				ALLOC_ARRAY (_hoops_RASGH->value._hoops_RARHA, count, long);
				count = _hoops_RASGH->_hoops_AIPCR - 1;
				do _hoops_RASGH->value._hoops_RARHA[count] = _hoops_GASGH->value._hoops_RARHA[count];
				_hoops_RGGA (--count < 0);
			}	break;

			case _hoops_HRSAP:
			case _hoops_ARSAP:
			case _hoops_PRRCR: {
				ALLOC_ARRAY (_hoops_RASGH->value._name, count, _hoops_HCRPR);
				count = _hoops_RASGH->_hoops_AIPCR - 1;
				do HI_Copy_Name (&_hoops_GASGH->value._name[count],
								 &_hoops_RASGH->value._name[count]);
				_hoops_RGGA (--count < 0);
			}	break;

			case _hoops_CRSAP:
			case _hoops_GASAP:
			case _hoops_SRSAP: {
				ALLOC_ARRAY (_hoops_RASGH->value._hoops_HGSAP, count, KName);
				count = _hoops_RASGH->_hoops_AIPCR - 1;
				do HI_Copy_KName (&_hoops_GASGH->value._hoops_HGSAP[count],
								  &_hoops_RASGH->value._hoops_HGSAP[count]);
				_hoops_RGGA (--count < 0);
			}	break;

			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Can't copy unknown option type");
			}	break;
		}
	} while ((_hoops_GASGH = _hoops_GASGH->next) != null);

	*_hoops_ASRGR = null;
	return first;
}




GLOBAL_FUNCTION void HI_Free_Option_List (
	_hoops_AIGPR *		_hoops_RIGC,
	Option_Value *				list) 
{
	Option_Value *				next;

	if (list != null) do {
		int						count;

		next = list->next;

		if ((count = list->_hoops_AIPCR) != 0 && list->value._hoops_IGSAP != null) {
			switch (list->type->_hoops_RCIIR) {
				case _hoops_RRSAP: {
					FREE_ARRAY (list->value._hoops_PGSAP, count, bool);
				}	break;

				case _hoops_SPPCR: {
					FREE_ARRAY (list->value._hoops_PIPCR, count, float);
				}	break;

				case _hoops_CIGHA: {
					FREE_ARRAY (list->value._hoops_RRRHA,
								count, _hoops_AGSAP);
				}	break;

				case _hoops_APRCA:
				case _hoops_CASAP: {
					FREE_ARRAY (list->value._hoops_RIARA, count, int);
				}	break;

				case _hoops_SIGHA: {
					FREE_ARRAY (list->value._hoops_RARHA, count, long);
				}	break;

				case _hoops_IRSAP: {
					FREE_ARRAY (list->value._hoops_CGSAP, count, POINTER_SIZED_INT);
				}	break;

				case _hoops_HRSAP:
				case _hoops_ARSAP:
				case _hoops_PRRCR: {
					_hoops_HCRPR *			_hoops_HGPIR = list->value._name;

					do {
						_hoops_RGAIR (*_hoops_HGPIR);
						_hoops_HGPIR++;
					} while (--count > 0);

					FREE_ARRAY (list->value._name,
						   list->_hoops_AIPCR, _hoops_HCRPR);
				}	break;

				case _hoops_CRSAP:
				case _hoops_GASAP:
				case _hoops_SRSAP: {
					KName *			_hoops_GCRCC = list->value._hoops_HGSAP;

					do {
						_hoops_PRPIR (*_hoops_GCRCC);
						_hoops_GCRCC++;
					} while (--count > 0);

					FREE_ARRAY (list->value._hoops_HGSAP,
						   list->_hoops_AIPCR, KName);
				}	break;

				case _hoops_GHAGA: {
					HI_Free_Option_List (_hoops_RIGC, list->value.option_list);
				}	break;

				case _hoops_AASAP: {
					if (list->_hoops_SGSAP == _hoops_APRCA)
						FREE_ARRAY (list->value._hoops_RIARA, count, int);
					else
						HI_Free_Option_List (_hoops_RIGC, list->value.option_list);
				}	break;

				case _hoops_HASAP: {
					if (list->_hoops_SGSAP == _hoops_IRSAP)
						FREE_ARRAY (list->value._hoops_CGSAP, count, POINTER_SIZED_INT);
					else
						HI_Free_Option_List (_hoops_RIGC, list->value.option_list);
				}	break;

				case _hoops_IASAP: {
					if (list->_hoops_SGSAP == _hoops_SPPCR)
						FREE_ARRAY (list->value._hoops_PIPCR, count, float);
					else
						HI_Free_Option_List (_hoops_RIGC, list->value.option_list);
				}	break;

				default: {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unrecognized option value");
				}	break;
			}
		}

		if (list->type->_hoops_HIHI == 1)
			_hoops_CIGPR (_hoops_RIGC,list->type);
		_hoops_HPRH (list->type);

		FREE (list, Option_Value);
	} while ((list = next) != null);
}




GLOBAL_FUNCTION void HI_Define_Constant_Options (
	_hoops_IGRCR const *	_hoops_PPCIH,
	int								_hoops_HPCIH,
	_hoops_GCIIR *				_hoops_SPHHR) 
{
	int								_hoops_IPSAA;

	if (_hoops_SPHHR->table == null) {
		_hoops_IPSAA = _hoops_HPCIH;
		while (_hoops_IPSAA != _hoops_RIII (_hoops_IPSAA))
			_hoops_IPSAA &= ~_hoops_RIII (_hoops_IPSAA);

		ZALLOC_ARRAY (_hoops_SPHHR->table, _hoops_IPSAA, _hoops_PIIIR *);
		_hoops_SPHHR->size = _hoops_IPSAA;
		_hoops_SPHHR->count = 0;
	}

	_hoops_RGGA (--_hoops_HPCIH < 0) {
		_hoops_GCIIR *			_hoops_CIIIR = null;

		if (_hoops_PPCIH->_hoops_RCIIR == _hoops_GHAGA ||
			_hoops_PPCIH->_hoops_RCIIR == _hoops_CIGHA ||
			_hoops_PPCIH->_hoops_RCIIR == _hoops_AASAP ||
			_hoops_PPCIH->_hoops_RCIIR == _hoops_HASAP ||
			_hoops_PPCIH->_hoops_RCIIR == _hoops_IASAP) {

			ZALLOC (_hoops_CIIIR, _hoops_GCIIR);

			HI_Define_Constant_Options (_hoops_PPCIH->_hoops_SASAP->options,
										_hoops_PPCIH->_hoops_SASAP->count,
										_hoops_CIIIR);
		}

		HI_Define_Nice_Option (_hoops_SPHHR,
							   _hoops_PPCIH->id,
							   (_hoops_HCRPR *)&_hoops_PPCIH->name,
							   _hoops_PPCIH->_hoops_RCIIR,
							   _hoops_PPCIH->_hoops_RHSAA,
							   _hoops_PPCIH->_hoops_GHSAA,
							   _hoops_CIIIR);

		++_hoops_PPCIH;
	}
}


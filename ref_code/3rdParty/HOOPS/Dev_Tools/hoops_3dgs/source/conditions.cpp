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
 * $Id: obf_tmp.txt 1.66 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hpserror.h"
#include "hc_proto.h"
#include "hi_proto.h"


#define _hoops_CIACA			 64

local	char const 						overflow[] = "Return string won't fit in provided space";



local Attribute * _hoops_SIACA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR)
{
	_hoops_SPPIR const *		_hoops_GCACA = (_hoops_SPPIR const *)_hoops_CPACR;
	_hoops_SPPIR alter *		_hoops_RCACA = (_hoops_SPPIR alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (item);

	if (_hoops_GCACA != null) {
		if (_hoops_GCACA->count > 0) {
			if (_hoops_RCACA->_hoops_SGCAA != null) {
				// _hoops_HASC, _hoops_SRPA _hoops_SGSS _hoops_IH _hoops_RHGS _hoops_SSSC _hoops_RH _hoops_CCAH _hoops_RGSR _hoops_SARS'_hoops_RA _hoops_ACPA _hoops_AHCA

				for (int i=0; i<_hoops_GCACA->count; i++) {
					unsigned int	mask = _hoops_GCACA->_hoops_SGCAA[i] & ~_hoops_RCACA->_hoops_SGCAA[i];
					int				index = i * 32;

					while (mask != 0) {
						if ((mask & 1) != 0)
							_hoops_PRRH (HOOPS_WORLD->_hoops_PCIIR[index]);

						mask >>= 1;
						++index;
					}
				}

				int					_hoops_CIGRR = _hoops_GCACA->count * sizeof (unsigned int);
				unsigned int *		scratch;


				_hoops_GGIPR (_hoops_GCACA->values, _hoops_GCACA->count, unsigned int, scratch);
				_hoops_HSIAA (scratch, _hoops_RCACA->_hoops_SGCAA, _hoops_CIGRR);

				_hoops_ISIAA (_hoops_RCACA->_hoops_SGCAA, _hoops_GCACA->_hoops_SGCAA, _hoops_CIGRR);
				_hoops_ISIAA (_hoops_RCACA->values, scratch, _hoops_CIGRR);

				FREE_ARRAY (scratch, _hoops_GCACA->count, unsigned int);
			}
			else {
				// _hoops_IPS

				_hoops_APRGA(_hoops_GCACA->_hoops_SGCAA, _hoops_GCACA->count, unsigned int, _hoops_RCACA->_hoops_SGCAA);
				_hoops_APRGA(_hoops_GCACA->values, _hoops_GCACA->count, unsigned int, _hoops_RCACA->values);

				_hoops_RCACA->count = _hoops_GCACA->count;

				for (int i=0; i<_hoops_RCACA->count; i++) {
					unsigned int	_hoops_RCHA = _hoops_RCACA->_hoops_SGCAA[i];
					int				index = i * 32;

					while (_hoops_RCHA != 0) {
						if ((_hoops_RCHA & 1) != 0)
							_hoops_PRRH (HOOPS_WORLD->_hoops_PCIIR[index]);

						_hoops_RCHA >>= 1;
						++index;
					}
				}
			}
		}

		bool					_hoops_ACACA = (_hoops_RCACA->_hoops_ACPGR != null);
		_hoops_PCACA *	_hoops_HCACA = _hoops_GCACA->_hoops_ACPGR;

#define _hoops_ICACA		0
#define _hoops_CCACA		1
#define _hoops_SCACA	2

		while (_hoops_HCACA != null) {
			_hoops_PCACA *	_hoops_GSACA = _hoops_RCACA->_hoops_ACPGR;
			int						what = _hoops_CCACA;

			if (_hoops_ACACA) {
				while (_hoops_GSACA != null) {
					if (_hoops_GSACA->type == _hoops_HCACA->type) {
						if (BIT (_hoops_GSACA->flags, _hoops_RSACA) &&
							(_hoops_GSACA->condition.count != _hoops_HCACA->condition.count ||
							 !EQUAL_MEMORY (_hoops_GSACA->condition._hoops_ASACA, _hoops_GSACA->condition.count*sizeof(int),
											_hoops_HCACA->condition._hoops_ASACA)))
							what = _hoops_SCACA;
						else
							what = _hoops_ICACA;

						break;
					}
					_hoops_GSACA = _hoops_GSACA->next;
				}
			}

			if (what == _hoops_CCACA) {
				ZALLOC(_hoops_GSACA, _hoops_PCACA);
				HI_Copy_Conditional (&_hoops_HCACA->condition, &_hoops_GSACA->condition);
				_hoops_GSACA->flags = _hoops_HCACA->flags;
				_hoops_GSACA->type = _hoops_HCACA->type;

				_hoops_GSACA->next = _hoops_RCACA->_hoops_ACPGR;
				_hoops_RCACA->_hoops_ACPGR = _hoops_GSACA;
			}
			else if (what == _hoops_SCACA) {
				if (_hoops_HCACA->condition.count > 0) {
					int			_hoops_CGCGR = _hoops_GSACA->condition.count;
					int const *	_hoops_PSACA = _hoops_GSACA->condition._hoops_ASACA;

					ALLOC_ARRAY (_hoops_GSACA->condition._hoops_ASACA, _hoops_CGCGR + _hoops_HCACA->condition.count + 1, int);
					_hoops_AIGA (_hoops_HCACA->condition._hoops_ASACA, _hoops_HCACA->condition.count, int,
								_hoops_GSACA->condition._hoops_ASACA);
					// _hoops_CCCH, _hoops_HIS _hoops_SRPA _hoops_ISIA
					for (int i = 0; i  <_hoops_HCACA->condition.count; i++)
						if (_hoops_HCACA->condition._hoops_ASACA[i] >= 0)
							_hoops_PRRH (HOOPS_WORLD->_hoops_PCIIR[_hoops_HCACA->condition._hoops_ASACA[i]]);
					// _hoops_HSACA _hoops_AGCR, _hoops_HIS _hoops_ISIA _hoops_IHRI
					_hoops_AIGA (_hoops_PSACA, _hoops_CGCGR, int, _hoops_GSACA->condition._hoops_ASACA + _hoops_HCACA->condition.count);
					FREE_ARRAY (_hoops_PSACA, _hoops_CGCGR, int);

					_hoops_GSACA->condition._hoops_ASACA[_hoops_CGCGR + _hoops_HCACA->condition.count] = _hoops_ISACA;
					_hoops_GSACA->condition.count += _hoops_HCACA->condition.count + 1;
				}
			}

			_hoops_HCACA = _hoops_HCACA->next;
		}
	}

	return _hoops_RCACA;
}


local void _hoops_CSACA (void) {
	_hoops_PIIIR	**_hoops_SSACA;

	ZALLOC_ARRAY (_hoops_SSACA, _hoops_CIACA, _hoops_PIIIR *);
	_hoops_CIACR (_hoops_GGPCA)->table = _hoops_SSACA;
	_hoops_CIACR (_hoops_GGPCA)->size = _hoops_CIACA;
}


local void _hoops_RGPCA (
	_hoops_SPPIR *			conditions,
	Option_Value *			option)
{
	conditions->count = HOOPS_WORLD->_hoops_AGCAA / 32;
	if (conditions->count == 0)
		conditions->count = 1;

	ZALLOC_ARRAY (conditions->_hoops_SGCAA, conditions->count, unsigned int);
	ZALLOC_ARRAY (conditions->values, conditions->count, unsigned int);

	if (option != null) do {
		int				index = option->type->id / 32;
		int				offset = option->type->id % 32;
		unsigned int	bit = 1UL << offset;

		conditions->_hoops_SGCAA[index] |= bit;
		_hoops_PRRH (HOOPS_WORLD->_hoops_PCIIR[option->type->id]);

		if (option->_hoops_GCACR)
			conditions->values[index] &= ~bit;
		else
			conditions->values[index] |= bit;
	} while ((option = option->next) != null);
}

GLOBAL_FUNCTION bool HI_Set_Conditions (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_SPPIR *			conditions)
{
	return HI_Set_Attribute (_hoops_RIGC, item, _hoops_CPPIR, _hoops_SIACA, conditions);
}


GLOBAL_FUNCTION _hoops_PCACA * HI_Copy_Conditional_Actions(_hoops_PCACA * _hoops_ACPGR)
{
	_hoops_PCACA *	_hoops_AGPCA = null;
	_hoops_PCACA **	_hoops_ASRGR = &_hoops_AGPCA;

	while (_hoops_ACPGR != null) {
		_hoops_PCACA * action;
		ZALLOC (action, _hoops_PCACA);

		HI_Copy_Conditional(&_hoops_ACPGR->condition, &action->condition);
		action->flags = _hoops_ACPGR->flags;
		action->type = _hoops_ACPGR->type;

		*_hoops_ASRGR = action;
		_hoops_ASRGR = &action->next;

		_hoops_ACPGR = _hoops_ACPGR->next;
	}

	return _hoops_AGPCA;
}

GLOBAL_FUNCTION void HI_Free_Conditional_Actions(_hoops_PCACA * action)
{
	while (action != null) {
		_hoops_PCACA *	next = action->next;
		HI_Free_Conditional(&action->condition);
		FREE (action, _hoops_PCACA);
		action = next;
	}
}

GLOBAL_FUNCTION void HI_Free_Condition(_hoops_SPPIR * _hoops_GHPIR)
{

	if (_hoops_GHPIR->count > 0) {
		for (int i=0; i<_hoops_GHPIR->count; i++) {
			unsigned int	_hoops_RCHA = _hoops_GHPIR->_hoops_SGCAA[i];
			int				index = i * 32;

			while (_hoops_RCHA != 0) {
				if ((_hoops_RCHA & 1) != 0) {
					_hoops_HPRH (HOOPS_WORLD->_hoops_PCIIR[index]);
				}
				_hoops_RCHA >>= 1;
				++index;
			}
		}
		FREE_ARRAY (_hoops_GHPIR->_hoops_SGCAA, _hoops_GHPIR->count, unsigned int);
		FREE_ARRAY (_hoops_GHPIR->values, _hoops_GHPIR->count, unsigned int);
	}

	HI_Free_Conditional_Actions(_hoops_GHPIR->_hoops_ACPGR);

	FREE (_hoops_GHPIR, _hoops_SPPIR);
}

HC_INTERFACE void HC_CDECL HC_Set_Conditions (
	char const *		options)
{
	_hoops_PAPPR context("Set_Conditions");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Conditions (%S);\n", options));
	);

	Option_Value *		option_list;

	if (_hoops_CIACR (_hoops_GGPCA)->table == null)
		_hoops_CSACA();

	if (HI_Parse_Options (context, options, _hoops_CIACR (_hoops_GGPCA), &option_list, _hoops_SIACR)) {
		bool			used = false;
		_hoops_SPPIR *	conditions;
		ZALLOC (conditions, _hoops_SPPIR);

		_hoops_RGPCA (conditions, option_list);

		HI_Free_Option_List (context, option_list);

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_PGPCA)) != null) {
			used = HI_Set_Conditions (context, target, conditions);
			_hoops_IRRPR();
		}

		if (!used)
			HI_Free_Condition (conditions);
	}
}



/************************************************************************************************************/


HC_INTERFACE void HC_CDECL HC_UnSet_Conditions (void)
{
	_hoops_PAPPR context("UnSet_Conditions");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Conditions ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PGPCA|_hoops_GSIIR)) != null) {
		_hoops_SPPIR *	conditions;
		if ((conditions = (_hoops_SPPIR *)HI_Find_Attribute (context, target, _hoops_CPPIR)) != null) {
			if (conditions->_hoops_ACPGR != null) {
				// _hoops_SAHR _hoops_CASI _hoops_GGSR _hoops_RH _hoops_SSSC, _hoops_SHSP _hoops_RH _hoops_PGSI
				if (conditions->count > 0) {
					for (int i = 0; i < conditions->count; i++) {
						unsigned int	_hoops_RCHA = conditions->_hoops_SGCAA[i];
						int				index = i * 32;

						while (_hoops_RCHA != 0) {
							if ((_hoops_RCHA & 1) != 0) {
								_hoops_HPRH (HOOPS_WORLD->_hoops_PCIIR[index]);
							}
							_hoops_RCHA >>= 1;
							++index;
						}
					}
					FREE_ARRAY (conditions->_hoops_SGCAA, conditions->count, unsigned int);
					FREE_ARRAY (conditions->values, conditions->count, unsigned int);
				}

				HI_Redraw_Attribute (context, conditions->owner, _hoops_CPPIR, conditions, null);

				_hoops_HPRH (conditions);
			}
			else {
				_hoops_HPRH (conditions);
				HI_UnSet_Attribute (context, target, _hoops_CPPIR);
			}
		}
		_hoops_IRRPR();
	}
}


/************************************************************************************************************/


GLOBAL_FUNCTION void HI_Show_Conditions (
	_hoops_SPPIR const *		conditions,
	char *					options,
	int						_hoops_HGPCA) {
	char *					_hoops_ASAPR = options;
	char const *			_hoops_PSAPR;

	if (_hoops_HGPCA == -1)
		_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR;		/* _hoops_IHRPR _hoops_IAHA */
	else
		_hoops_PSAPR = _hoops_ASAPR + _hoops_HGPCA;			/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */

	for (int i=0; i<conditions->count; i++) {
		unsigned int	mask = conditions->_hoops_SGCAA[i];
		unsigned int	value = conditions->values[i];
		int				index = i * 32;

		while (mask != 0) {
			if (BIT (mask, 1)) {
				_hoops_PIIIR const		*_hoops_HIIIR = HOOPS_WORLD->_hoops_PCIIR[index];

				if (_hoops_ASAPR != options) {
					if (_hoops_ASAPR == _hoops_PSAPR) {
						_hoops_ASAPR = null; /* _hoops_PGPCR _hoops_RPP _hoops_PSP _hoops_RSIAR _hoops_IH ',' */
						break;
					}
					*_hoops_ASAPR++ = ',';
				}

				if (!BIT (value, 1)) {
					if ((_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "no ", null)) == null)
						break;
				}
				if ((_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%n", (void *)&_hoops_HIIIR->name)) == null)
					break;

				if (_hoops_ASAPR == null)
					break;
			}

			mask >>= 1;
			value >>= 1;
			++index;
		}
		if (_hoops_ASAPR == null)
			break;
	}

	if (_hoops_ASAPR == null) {
		HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, overflow);
		return;
	}

	/* _hoops_GHHR _hoops_PRRP */
	if (_hoops_HGPCA == -1) {
		if (_hoops_ASAPR == _hoops_PSAPR) {
			HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, overflow);
			return;
		}
		*_hoops_ASAPR = '\0';								/* _hoops_IHRPR _hoops_IAHA */
	}
	else {
		_hoops_RGGA (_hoops_ASAPR == _hoops_PSAPR) *_hoops_ASAPR++ = ' ';	/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */
	}
}


#ifndef DISABLE_SHOW

local void _hoops_IGPCA (
	_hoops_SPPIR const *		conditions,
	int *					length) {

	*length = 0;

	for (int i=0; i<conditions->count; i++) {
		unsigned int	mask = conditions->_hoops_SGCAA[i];
		unsigned int	value = conditions->values[i];
		int				index = i * 32;

		while (mask != 0) {
			if (BIT (mask, 1)) {
				_hoops_PIIIR const		*_hoops_HIIIR = HOOPS_WORLD->_hoops_PCIIR[index];

				if (*length > 0)
					++*length;	/* ',' */

				if (!BIT (value, 1))
					*length += 3;	/* '_hoops_PSP ' */
				*length += _hoops_HIIIR->name.length;
			}

			mask >>= 1;
			value >>= 1;
			++index;
		}
	}
}


local void _hoops_CGPCA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_SPPIR const *		conditions,
	bool					_hoops_PSACR,
	char const *			condition,
	char *					list,
	int						_hoops_GGCIR)
{
	_hoops_HCRPR					cname;
	char const *			_hoops_RPPA = condition;

	HI_Scan_Name (_hoops_RIGC, &_hoops_RPPA, null, &cname);

	for (int i=0; i<conditions->count; i++) {
		unsigned int	mask = conditions->_hoops_SGCAA[i];
		unsigned int	value = conditions->values[i];
		int				index = i * 32;

		while (mask != 0) {
			if (BIT (mask, 1)) {
				_hoops_PIIIR const		*_hoops_HIIIR = HOOPS_WORLD->_hoops_PCIIR[index];

				if (_hoops_RAHSR (cname, _hoops_HIIIR->name)) {
					if (BIT (value, 1))
						HI_Return_Chars (list, _hoops_GGCIR, "on", 2);
					else
						HI_Return_Chars (list, _hoops_GGCIR, "off", 3);

					_hoops_RGAIR (cname);
					return;
				}
			}

			mask >>= 1;
			value >>= 1;
			++index;
		}
	}

	if (!_hoops_PSACR) {
		HE_ERROR (HEC_CONDITIONS, HES_NO_LOCAL_SETTING,
				  Sprintf_SP (null, "'%s' has no local setting in '%p'", &cname, conditions->owner));
	}

	_hoops_RGAIR (cname);

	HI_Return_Chars (list, _hoops_GGCIR, "", 0);
	return;
}

#endif


HC_INTERFACE void HC_CDECL HC_Show_Conditions (
	char *				options)
{
	_hoops_PAPPR context("Show_Conditions");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Conditions () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_SGPCA)) != null) {
		_hoops_SPPIR const *	conditions;
		if ((conditions = (_hoops_SPPIR const *)HI_Find_Attribute (context, target, _hoops_CPPIR)) != null) {
			HI_Show_Conditions (conditions, options, -1);
			_hoops_HPRH (conditions);
		}
		_hoops_IRRPR();
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Conditions_Length (
	int *			length)
{
	_hoops_PAPPR context("Show_Conditions_Length");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Conditions_Length () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_SGPCA)) != null) {
		_hoops_SPPIR const *	conditions;
		if ((conditions = (_hoops_SPPIR const *)HI_Find_Attribute (context, target, _hoops_CPPIR)) != null) {
			_hoops_IGPCA (conditions, length);
			_hoops_HPRH (conditions);
		}
		_hoops_IRRPR();
	}
#endif
}



#ifndef _hoops_ARPCR


HC_INTERFACE void HC_CDECL HC_PShow_Net_Conditions (
	int					count,
	Key const *			keys,
	char *				options)
{
	_hoops_PAPPR context("PShow_Net_Conditions");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Conditions () */\n");
	);

	_hoops_SPPIR const *	conditions;
	if ((conditions = (_hoops_SPPIR const *) HI_Find_Attribute_And_Lock(context, _hoops_SGPCA, _hoops_HRPCR, count, keys)) != null) {
		HI_Show_Conditions (conditions, options, -1);
		_hoops_HPRH (conditions);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(options, -1, "", 0);
#endif
}

HC_INTERFACE void HC_CDECL HC_PShow_Net_Conditions_Length (
	int					count,
	Key const *			keys,
	int *				length)
{
	_hoops_PAPPR context("PShow_Net_Conditions_Length");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Conditions_Length () */\n");
	);

	_hoops_SPPIR const *	conditions;
	if ((conditions = (_hoops_SPPIR const *) HI_Find_Attribute_And_Lock(context, _hoops_SGPCA, _hoops_HRPCR, count, keys)) != null) {
		_hoops_IGPCA (conditions, length);
		_hoops_HPRH (conditions);
		_hoops_IRRPR();
	}
	else
		*length = 0;

#endif
}
#endif


HC_INTERFACE void HC_CDECL HC_Show_One_Condition (
	char const *			cname,
	char *					options)
{
	_hoops_PAPPR context("Show_One_Condition");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_Condition () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_SGPCA)) != null) {
		_hoops_SPPIR const *	conditions;
		if ((conditions = (_hoops_SPPIR const *)HI_Find_Attribute (context, target, _hoops_CPPIR)) != null) {
			_hoops_CGPCA (context, conditions, false, cname, options, -1);
			_hoops_HPRH (conditions);
		}
		_hoops_IRRPR();
	}
#endif
}



#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Condition (
	int						count,
	Key const *				keys,
	char const *			cname,
	char *					options)
{
	_hoops_PAPPR context("PShow_One_Net_Condition");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_One_Net_Condition () */\n");
	);

	_hoops_SPPIR const *	conditions;
	if ((conditions = (_hoops_SPPIR const *) HI_Find_Attribute_And_Lock(context, _hoops_SGPCA, _hoops_HRPCR, count, keys)) != null) {
		_hoops_CGPCA (context, conditions, true, cname, options, -1);
		_hoops_HPRH (conditions);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(options, -1, "", 0);

#endif
}

#endif



/************************************************************************************************************/

#define _hoops_GRPCA		-1
#define _hoops_RRPCA		-2

local const _hoops_IGRCR _hoops_ARPCA[] = {
	{_hoops_PRPCA,				_hoops_GRRCR ("segment tree"),		_hoops_RRRCR, 0, false},
	{_hoops_GRPCA,	_hoops_GRRCR ("segment"),			_hoops_RRRCR, 0, false},

	{_hoops_RRPCA,	_hoops_GRRCR ("replace"),			_hoops_RRRCR, 0, false},
	{_hoops_RSACA,						_hoops_GRRCR ("merge"),				_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_HRPCA = {
	_hoops_GGAPR (_hoops_ARPCA),	_hoops_ARPCA,
};

local const _hoops_IGRCR _hoops_IRPCA[] = {
	{_hoops_CRPCA,		_hoops_GRRCR ("prune segment"),		_hoops_GHAGA, -9, false, &_hoops_HRPCA},
};



HC_INTERFACE void HC_CDECL HC_Set_Conditional_Action (
	char const *	options,
	char const *	condition)
{
	_hoops_PAPPR			context("Set_Conditional_Action");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Set_Conditional_Action (%S, %S);\n", options, condition));
	);

	Option_Value *	option_list;
	Option_Value *	option;

	_hoops_HIACR (_hoops_SRPCA, _hoops_IRPCA);

	int				_hoops_IHAGA = HI_Parse_Options (context, options, _hoops_CIACR (_hoops_SRPCA),
													 &option_list, _hoops_SIACR);

	if (_hoops_IHAGA) {
		_hoops_SPPIR *			conditions;
		ZALLOC (conditions, _hoops_SPPIR);
		_hoops_PCACA **	_hoops_ASRGR = &conditions->_hoops_ACPGR;
		bool					used = false;
		bool					_hoops_GAPCA = false;

		if ((option = option_list) != null) do {
			switch (option->type->id) {
				case _hoops_CRPCA: {
					_hoops_PCACA *	action;

					ZALLOC (action, _hoops_PCACA);
					*_hoops_ASRGR = action;
					_hoops_ASRGR = &action->next;

					action->type = option->type->id;

					Option_Value *	_hoops_CHAGA;

					if ((_hoops_CHAGA = option->value.option_list) != null) do {
						switch (_hoops_CHAGA->type->id) {
							case _hoops_PRPCA: {
								action->flags |= _hoops_PRPCA;
							}	break;

							case _hoops_GRPCA: {
								action->flags &= ~_hoops_PRPCA;
							}	break;

							case _hoops_RSACA: {
								action->flags |= _hoops_RSACA;
							}	break;

							case _hoops_RRPCA: {
								action->flags &= ~_hoops_RSACA;
							}	break;

							default: {
								_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
													"Unrecognized conditional action option type");
								_hoops_GAPCA = true;
								break;
							}
						}
					} while ((_hoops_CHAGA = _hoops_CHAGA->next) != null);
				}	break;

				default: {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unrecognized conditional action option type");
					_hoops_GAPCA = true;
					break;
				}
			}
		} while ((option = option->next) != null);

		HI_Free_Option_List (context, option_list);

		if (_hoops_GAPCA)
			; // _hoops_ISAP
		else if (!HI_Parse_Condition (context, condition, &conditions->_hoops_ACPGR->condition)) {
			HE_ERROR2 (HEC_STYLE, HES_CONDITIONAL,
						"Unable to process the conditional expression:", Sprintf_S (null, "'%s'", condition));
		}
		else {
			if (conditions->_hoops_ACPGR->next != null) {
				// _hoops_RAPCA _hoops_RGAR _hoops_PIISR _hoops_GGR _hoops_HPAC _hoops_GPP _hoops_SRS _hoops_ACPH, _hoops_HIS _hoops_AAPCA _hoops_IS _hoops_HIASR
				_hoops_PCACA *	action = conditions->_hoops_ACPGR->next;
				do {
					HI_Copy_Conditional (&conditions->_hoops_ACPGR->condition, &action->condition);
				} while ((action = action->next) != null);
			}

			_hoops_HPAH * target;
			if ((target = HI_Find_Target_And_Lock(context, _hoops_PGPCA)) != null) {
				used = HI_Set_Conditions (context, target, conditions);
				_hoops_IRRPR();
			}
		}

		if (!used)
			HI_Free_Condition (conditions);
	}
}

//

GLOBAL_FUNCTION void HI_Show_Conditional_Action_Types (
	_hoops_SPPIR const *			conditions,
	char *						action_types) {
	char *						_hoops_ASAPR = action_types;
	char const *				_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR;
	_hoops_PCACA const *	action = conditions->_hoops_ACPGR;

	if (action != null) do {
		switch (action->type) {
			case _hoops_CRPCA: {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "prune segment", null);
			}	break;
		}
		if ((action = action->next) != null)
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ",", null);
	} while (action != null);

	if (_hoops_ASAPR == null)
		HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, overflow);
	else
		*_hoops_ASAPR = '\0';
}

GLOBAL_FUNCTION void HI_Show_One_Conditional_Action (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_SPPIR const *			conditions,
	char const *				action_type,
	char *						options,
	char *						condition) {
	_hoops_PCACA const *	action = conditions->_hoops_ACPGR;

	if (action != null) {
		Option_Value *			option;

		_hoops_HIACR (_hoops_SRPCA, _hoops_IRPCA);

		if (!HI_Parse_Options (_hoops_RIGC, action_type, _hoops_CIACR (_hoops_SRPCA),
								&option, _hoops_CGPCR|_hoops_PAPCA))
			return;

		do {
			if (action->type == option->type->id) {
				char *				_hoops_ASAPR = options;
				char *				_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR;

				if (BIT (action->flags, _hoops_PRPCA))
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "segment tree", null);
				else
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "segment", null);

				if (_hoops_ASAPR == null)
					HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, overflow);
				else
					*_hoops_ASAPR = '\0';

				HI_Show_Conditional (&action->condition, condition, -1);

				break;
			}
		} while ((action = action->next) != null);

		HI_Free_Option_List (_hoops_RIGC, option);
	}

	if (action == null)
		HE_ERROR (HEC_CONDITIONS, HES_NO_LOCAL_SETTING,
				  Sprintf_SP (null, "'%s' has no setting in '%p'", action_type, conditions->owner));
}

//

HC_INTERFACE void HC_CDECL HC_Show_Cond_Action_Types (
	char *					action_types) {
	_hoops_PAPPR					context("Show_Conditional_Action_Types");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Conditional_Action_Types (); */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_SGPCA)) != null) {
		_hoops_SPPIR const *		conditions;
		if ((conditions = (_hoops_SPPIR const *)HI_Find_Attribute (context, target, _hoops_CPPIR)) != null) {
			HI_Show_Conditional_Action_Types (conditions, action_types);
			_hoops_HPRH (conditions);
		}
		_hoops_IRRPR();
	}
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_One_Conditional_Action (
	char const *			action_type,
	char *					options,
	char *					condition)  {
	_hoops_PAPPR					context("Show_One_Conditional_Action");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_Conditional_Action (); */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_SGPCA)) != null) {
		_hoops_SPPIR const *		conditions;
		if ((conditions = (_hoops_SPPIR const *)HI_Find_Attribute (context, target, _hoops_CPPIR)) != null) {
			HI_Show_One_Conditional_Action (context, conditions, action_type, options, condition);
			_hoops_HPRH (conditions);
		}
		_hoops_IRRPR();
	}
#endif
}



HC_INTERFACE void HC_CDECL HC_UnSet_Conditional_Actions (void)
{
	_hoops_PAPPR context("UnSet_Conditional_Actions");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Conditional_Actions ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PGPCA|_hoops_GSIIR)) != null) {
		_hoops_SPPIR *	conditions;
		if ((conditions = (_hoops_SPPIR *)HI_Find_Attribute (context, target, _hoops_CPPIR)) != null) {
			if (conditions->count > 0) {
				// _hoops_SAHR _hoops_CASI _hoops_GGSR _hoops_RH _hoops_PGSI, _hoops_SHSP _hoops_RH _hoops_SSSC
				HI_Free_Conditional_Actions(conditions->_hoops_ACPGR);
				conditions->_hoops_ACPGR = null;

				HI_Redraw_Attribute (context, conditions->owner, _hoops_CPPIR, conditions, null);

				_hoops_HPRH (conditions);
			}
			else {
				_hoops_HPRH (conditions);
				HI_UnSet_Attribute (context, target, _hoops_CPPIR);
			}
		}
		_hoops_IRRPR();
	}
}


/************************************************************************************************************/


/* _hoops_RCPPR
		_hoops_PIHHR
		_hoops_HAPCA
		_hoops_GCPAR
		_hoops_IAPCA, _hoops_CAPCA
		_hoops_ASAI
		()
	_hoops_PAGA: _hoops_PIHHR & _hoops_CAPCA _hoops_CHR _hoops_SAPCA _hoops_HSHPR _hoops_HIH _hoops_HSCR _hoops_RRAR
*/

struct _hoops_GPPCA {
	struct _hoops_GPPCA	*left;
	struct _hoops_GPPCA	*right;
	int					code;
};

local void _hoops_RPPCA (
	struct _hoops_GPPCA *		node) {

	if (node->left != null)
		_hoops_RPPCA (node->left);
	if (node->right != null)
		_hoops_RPPCA (node->right);

	if (node->code >= 0)
		_hoops_HPRH (HOOPS_WORLD->_hoops_PCIIR[node->code]);

	FREE (node, struct _hoops_GPPCA);
}

local struct _hoops_GPPCA * _hoops_APPCA (_hoops_AIGPR *	_hoops_RIGC, char const **_hoops_RAARA);


#define _hoops_PPPCA(_x_) (_x_ == ' ' || _x_  == '!' || _x_ == '(')

local bool _hoops_HPPCA (
	char const *			_hoops_RPPA) {

	if (_hoops_RPPA[0] == '!' && _hoops_RPPA[1] != '=')
		return true;
	if ((_hoops_RPPA[0] == 'N' || _hoops_RPPA[0] == 'n') && (_hoops_RPPA[1] == 'O' || _hoops_RPPA[1] == 'o') &&
		(_hoops_RPPA[2] == 'T' || _hoops_RPPA[2] == 't') && _hoops_PPPCA (_hoops_RPPA[3]))
		return true;
	return false;
}
local bool _hoops_IPPCA (
	char const *			_hoops_RPPA) {

	if (_hoops_RPPA[0] == '=' && _hoops_RPPA[1] == '='  ||
		_hoops_RPPA[0] == '!' && _hoops_RPPA[1] == '=')
		return true;
	if ((_hoops_RPPA[0] == 'E' || _hoops_RPPA[0] == 'e') &&
		(_hoops_RPPA[1] == 'Q' || _hoops_RPPA[1] == 'q') &&
		_hoops_PPPCA (_hoops_RPPA[2]))
		return true;
	if ((_hoops_RPPA[0] == 'N' || _hoops_RPPA[0] == 'n') &&
		(_hoops_RPPA[1] == 'E' || _hoops_RPPA[1] == 'e') &&
		(_hoops_RPPA[2] == 'Q' || _hoops_RPPA[2] == 'q') &&
		_hoops_PPPCA (_hoops_RPPA[3]))
		return true;
	return false;
}
local bool _hoops_CPPCA (
	char const *			_hoops_RPPA) {

	if (_hoops_RPPA[0] == '&')
		return true;
	if ((_hoops_RPPA[0] == 'A' || _hoops_RPPA[0] == 'a') &&
		(_hoops_RPPA[1] == 'N' || _hoops_RPPA[1] == 'n') &&
		(_hoops_RPPA[2] == 'D' || _hoops_RPPA[2] == 'd') &&
		_hoops_PPPCA (_hoops_RPPA[3]))
		return true;
	return false;
}
local bool _hoops_SPPCA (
	char const *			_hoops_RPPA) {

	if (_hoops_RPPA[0] == '|')
		return true;
	if ((_hoops_RPPA[0] == 'O' || _hoops_RPPA[0] == 'o') &&
		(_hoops_RPPA[1] == 'R' || _hoops_RPPA[1] == 'r') &&
		_hoops_PPPCA (_hoops_RPPA[2]))
		return true;
	return false;
}

local bool _hoops_GHPCA (
	char const *			_hoops_RPPA) {

	if (_hoops_RPPA[0] == '^')
		return true;
	if ((_hoops_RPPA[0] == 'X' || _hoops_RPPA[0] == 'x') &&
		(_hoops_RPPA[1] == 'O' || _hoops_RPPA[1] == 'o') &&
		(_hoops_RPPA[2] == 'R' || _hoops_RPPA[2] == 'r') &&
		_hoops_PPPCA (_hoops_RPPA[3]))
		return true;
	return false;
}

local bool _hoops_RHPCA (
	char const *			_hoops_RPPA) {

	return *_hoops_RPPA == '\0' ||
		   *_hoops_RPPA == ')' ||
		   _hoops_HPPCA (_hoops_RPPA) ||
		   _hoops_IPPCA (_hoops_RPPA) ||
		   _hoops_CPPCA (_hoops_RPPA) ||
		   _hoops_SPPCA (_hoops_RPPA) ||
		   _hoops_GHPCA (_hoops_RPPA);
}


local struct _hoops_GPPCA * _hoops_AHPCA (
	_hoops_AIGPR *	_hoops_RIGC,
	char const **			_hoops_RAARA)
{
	struct _hoops_GPPCA *		node;

	if (**_hoops_RAARA == '(') {
		++*_hoops_RAARA;
		while (**_hoops_RAARA == ' ') ++*_hoops_RAARA;
		node = _hoops_APPCA (_hoops_RIGC, _hoops_RAARA);
		if (node == null)
			return null;

		if (**_hoops_RAARA != ')') {
			/* _hoops_RIHH */
			_hoops_RPPCA (node);
			return null;
		}
		++*_hoops_RAARA;
		while (**_hoops_RAARA == ' ') ++*_hoops_RAARA;
	}
	else {
		char			tmp[1024];
		char *			_hoops_ISSPA = tmp;
		Option_Value *option;
		int				_hoops_RGPRA = 0;
		char			_hoops_PPARA = '\0';

		while (_hoops_PPARA || !_hoops_RHPCA (*_hoops_RAARA)) {
			char			_hoops_PHPCA = *(*_hoops_RAARA)++;

			if (_hoops_PHPCA == '"' || _hoops_PHPCA == '\'' || _hoops_PHPCA == '`') {
				if (_hoops_PHPCA == _hoops_PPARA || !_hoops_PPARA)
					_hoops_PPARA ^= _hoops_PHPCA;
				*_hoops_ISSPA++ = _hoops_PHPCA;
			}
			else if (_hoops_PPARA) {
				*_hoops_ISSPA++ = _hoops_PHPCA;
			}
			else {
				if (_hoops_PHPCA == '(')
					++_hoops_RGPRA;
				else if (_hoops_PHPCA == ')')
					--_hoops_RGPRA;
				else if (_hoops_PHPCA== ',' && _hoops_RGPRA <= 0)
					break;
				*_hoops_ISSPA++ = _hoops_SHPCR (_hoops_PHPCA);
			}
		}
		while (_hoops_ISSPA != tmp && _hoops_ISSPA[-1] == ' ')
			--_hoops_ISSPA;
		*_hoops_ISSPA = '\0';
		if (_hoops_ISSPA == tmp)
			return null;	/* _hoops_ISAP _hoops_ARI _hoops_CGPR _hoops_SR _hoops_RRP _hoops_CPHP? */
		while (**_hoops_RAARA == ' ')
			++*_hoops_RAARA;

		if (!HI_Parse_Options (_hoops_RIGC, tmp, _hoops_CIACR (_hoops_GGPCA),
							   &option, _hoops_SIACR))
			return null;


		ALLOC (node, struct _hoops_GPPCA);
		node->code = option->type->id;
		_hoops_PRRH (option->type);
		node->left = null;
		node->right = null;

		HI_Free_Option_List (_hoops_RIGC, option);
	}

	return node;
}
local struct _hoops_GPPCA * _hoops_HHPCA (
	_hoops_AIGPR *	_hoops_RIGC,
	char const **			_hoops_RAARA)
{
	struct _hoops_GPPCA *		node = null;

	if (_hoops_HPPCA (*_hoops_RAARA)) {
		char const *			_hoops_RPPA = *_hoops_RAARA;
		struct _hoops_GPPCA *		right;

		if (*_hoops_RPPA == '!')
			++*_hoops_RAARA;		/* '!' */
		else
			*_hoops_RAARA += 3;	/* '_hoops_HAR' */
		while (**_hoops_RAARA == ' ') ++*_hoops_RAARA;

		right = _hoops_HHPCA (_hoops_RIGC, _hoops_RAARA);
		if (right == null)
			return null;

		ALLOC (node, struct _hoops_GPPCA);
		node->code = _hoops_IHPCA;
		node->left = null;
		node->right = right;
	}
	else
		node = _hoops_AHPCA (_hoops_RIGC, _hoops_RAARA);

	return node;
}
local struct _hoops_GPPCA * _hoops_CHPCA (
	_hoops_AIGPR *	_hoops_RIGC,
	char const **			_hoops_RAARA)
{
	struct _hoops_GPPCA *		node;

	node = _hoops_HHPCA (_hoops_RIGC, _hoops_RAARA);
	if (node == null)
		return null;

	while (_hoops_IPPCA (*_hoops_RAARA)) {
		char const *			_hoops_RPPA = *_hoops_RAARA;
		struct _hoops_GPPCA *		left = node;
		struct _hoops_GPPCA *		right;

		if (_hoops_RPPA[1] == '=')
			*_hoops_RAARA += 2;	/* '==' _hoops_PAR '!=' */
		else if (_hoops_RPPA[0] == 'E' || _hoops_RPPA[0] == 'e')
			*_hoops_RAARA += 2;	/* '_hoops_SHPCA' */
		else
			*_hoops_RAARA += 3;	/* '_hoops_GIPCA' */
		while (**_hoops_RAARA == ' ') ++*_hoops_RAARA;

		right = _hoops_HHPCA (_hoops_RIGC, _hoops_RAARA);
		if (right == null) {
			_hoops_RPPCA (left);
			return null;
		}

		ALLOC (node, struct _hoops_GPPCA);
		switch (*_hoops_RPPA) {
			case 'N':	case 'n':	case '!':		node->code = _hoops_RIPCA;		break;
			case 'E':	case 'e':	case '=':		node->code = _hoops_AIPCA;		break;
		}
		node->left = left;
		node->right = right;
	}

	return node;
}
local struct _hoops_GPPCA * _hoops_PIPCA (
	_hoops_AIGPR *	_hoops_RIGC,
	char const **			_hoops_RAARA)
{
	struct _hoops_GPPCA *		node;

	node = _hoops_CHPCA (_hoops_RIGC, _hoops_RAARA);
	if (node == null)
		return null;

	while (_hoops_CPPCA (*_hoops_RAARA)) {
		char const *			_hoops_RPPA = *_hoops_RAARA;
		struct _hoops_GPPCA *		left = node;
		struct _hoops_GPPCA *		right;

		if (*_hoops_RPPA == '&') {
			++*_hoops_RAARA;			/* '&' */
			if (**_hoops_RAARA == '&')
				++*_hoops_RAARA;		/* '&&' */
		}
		else
			*_hoops_RAARA += 3;	/* '_hoops_PPR' */
		while (**_hoops_RAARA == ' ') ++*_hoops_RAARA;

		right = _hoops_CHPCA (_hoops_RIGC, _hoops_RAARA);
		if (right == null) {
			_hoops_RPPCA (left);
			return null;
		}

		ALLOC (node, struct _hoops_GPPCA);
		node->code = _hoops_HIPCA;
		node->left = left;
		node->right = right;
	}

	return node;
}
local struct _hoops_GPPCA * _hoops_IIPCA (
	_hoops_AIGPR *	_hoops_RIGC,
	char const **			_hoops_RAARA)
{
	struct _hoops_GPPCA *		node;

	node = _hoops_PIPCA (_hoops_RIGC, _hoops_RAARA);
	if (node == null)
		return null;

	while (_hoops_SPPCA (*_hoops_RAARA)) {
		char const *			_hoops_RPPA = *_hoops_RAARA;
		struct _hoops_GPPCA *		left = node;
		struct _hoops_GPPCA *		right;

		if (*_hoops_RPPA == '|') {
			++*_hoops_RAARA;			/* '|' */
			if (**_hoops_RAARA == '|')
				++*_hoops_RAARA;		/* '||' */
		}
		else
			*_hoops_RAARA += 2;		/* '_hoops_PAR' */
		while (**_hoops_RAARA == ' ') ++*_hoops_RAARA;

		right = _hoops_PIPCA (_hoops_RIGC, _hoops_RAARA);
		if (right == null) {
			_hoops_RPPCA (left);
			return null;
		}

		ALLOC (node, struct _hoops_GPPCA);
		node->code = _hoops_ISACA;
		node->left = left;
		node->right = right;
	}

	return node;
}
local struct _hoops_GPPCA * _hoops_APPCA (
	_hoops_AIGPR *	_hoops_RIGC,
	char const **			_hoops_RAARA)
{
	struct _hoops_GPPCA *		node;

	node = _hoops_IIPCA (_hoops_RIGC, _hoops_RAARA);
	if (node == null)
		return null;

	while (_hoops_GHPCA (*_hoops_RAARA)) {
		char const *			_hoops_RPPA = *_hoops_RAARA;
		struct _hoops_GPPCA *		left = node;
		struct _hoops_GPPCA *		right;

		if (*_hoops_RPPA == '^')
			++*_hoops_RAARA;			/* '^' */
		else
			*_hoops_RAARA += 3;		/* '_hoops_CIPCA' */
		while (**_hoops_RAARA == ' ') ++*_hoops_RAARA;

		right = _hoops_IIPCA (_hoops_RIGC, _hoops_RAARA);
		if (right == null) {
			_hoops_RPPCA (left);
			return null;
		}

		ALLOC (node, struct _hoops_GPPCA);
		node->code = _hoops_SIPCA;
		node->left = left;
		node->right = right;
	}

	return node;
}


local int _hoops_GCPCA (
	struct _hoops_GPPCA *		node) {
	int						count = 1;

	if (node->left != null)
		count += _hoops_GCPCA (node->left);
	if (node->right != null)
		count += _hoops_GCPCA (node->right);

	return count;
}

local void _hoops_RCPCA (
	struct _hoops_GPPCA *		node,
	int **					_hoops_ACPCA) {

	if (node->left != null)
		_hoops_RCPCA (node->left, _hoops_ACPCA);
	if (node->right != null)
		_hoops_RCPCA (node->right, _hoops_ACPCA);

	*(*_hoops_ACPCA)++ = node->code;
	/* _hoops_CPRAA _hoops_IRS _hoops_HPAC _hoops_RRGR _hoops_CHH _hoops_PCPCA, _hoops_HCPCA _hoops_GIIS _hoops_CHH _hoops_ICPCA, _hoops_HIS _hoops_PSP _hoops_GCHRR _hoops_AGRP */
	FREE (node, struct _hoops_GPPCA);
}


GLOBAL_FUNCTION bool HI_Parse_Condition (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			string,
	_hoops_CCPCA alter *		_hoops_SCPCA)
{
	struct _hoops_GPPCA *		node;
	char const *			sp;
	int *					_hoops_ASACA;

	if (_hoops_CIACR (_hoops_GGPCA)->table == null) _hoops_CSACA();

	while (*string == ' ')
		++string;
	if (*(sp = string) == '\0') /* _hoops_RPGR _hoops_GSGR _hoops_HRGR _hoops_IHRI */
		return true;

	node = _hoops_APPCA (_hoops_RIGC, &sp);

	if (node == null)
		return false;	/* _hoops_HPCS _hoops_GSPCA */

	if (*sp != '\0') {
		_hoops_RPPCA (node);
		return false;
	}

	_hoops_SCPCA->count = _hoops_GCPCA (node);

	ALLOC_ARRAY (_hoops_ASACA, _hoops_SCPCA->count, int);
	_hoops_SCPCA->_hoops_ASACA = _hoops_ASACA;

	_hoops_RCPCA (node, &_hoops_ASACA);		/* _hoops_GACC _hoops_RSPCA _hoops_RH _hoops_HHIS */

	return true;
}



local struct _hoops_GPPCA * _hoops_ASPCA (
	int const **					_hoops_PSPCA,
	int alter *						count) {
	struct _hoops_GPPCA *				node;

	ALLOC (node, struct _hoops_GPPCA);
	node->left = node->right = null;	/* _hoops_CCGR _hoops_SR _hoops_CGIC _hoops_RRAR */
	node->code = *(*_hoops_PSPCA)--;
	--*count;

	if (node->code >= 0) {
		_hoops_PRRH (HOOPS_WORLD->_hoops_PCIIR[node->code]);
	}
	else {
		node->right = _hoops_ASPCA (_hoops_PSPCA, count);
		if (node->code != _hoops_IHPCA)	/* _hoops_ASAI _hoops_HRGR _hoops_IRS _hoops_HSPCA _hoops_SIRRR */
			node->left = _hoops_ASPCA (_hoops_PSPCA, count);
	}

	return node;
}

/* _hoops_PAGA: _hoops_AGCR _hoops_SIRGR _hoops_PIHA _hoops_ISPCA _hoops_IS _hoops_RH _hoops_RRGR _hoops_CSPCA _hoops_GGR _hoops_AARPR._hoops_GGHR */
local	char const *_hoops_SSPCA[]	 = {"?",  "not ", " eq ", " neq ", " and ", " or ", " xor "};
local	int			_hoops_GGHCA[] = { 0,		1,		2,		 2,		  3,	  4,	   5   };

local void _hoops_RGHCA (
	char alter **			bpp,
	char const *			_hoops_PSAPR,
	struct _hoops_GPPCA *		node,
	int						_hoops_AGHCA) {

	if (node->code >= 0) {
		*bpp = HI_Sprintf1 (*bpp, _hoops_PSAPR, "%n", (void *)&HOOPS_WORLD->_hoops_PCIIR[node->code]->name);
	}
	else {
		int	_hoops_PGHCA = -node->code;

		if (_hoops_GGHCA[_hoops_PGHCA] > _hoops_AGHCA) {
			if ((*bpp = HI_Sprintf1 (*bpp, _hoops_PSAPR, "(", null)) == null)
				return;
		}

		if (node->left != null) {
			_hoops_RGHCA (bpp, _hoops_PSAPR, node->left, _hoops_GGHCA[_hoops_PGHCA]);
			if (!*bpp)
				return;
		}

		if ((*bpp = HI_Sprintf1 (*bpp, _hoops_PSAPR, "%s", _hoops_SSPCA[_hoops_PGHCA])) == null)
			return;
		if (!*bpp)
			return;

		_hoops_RGHCA (bpp, _hoops_PSAPR, node->right, _hoops_GGHCA[_hoops_PGHCA]);
		if (!*bpp)
			return;

		if (_hoops_GGHCA[-node->code] > _hoops_AGHCA) {
			if ((*bpp = HI_Sprintf1 (*bpp, _hoops_PSAPR, ")", null)) == null)
				return;
		}
	}
}

GLOBAL_FUNCTION void HI_Show_Conditional (
	_hoops_CCPCA const *		_hoops_SCPCA,
	char alter *			list,
	int						_hoops_GGCIR)
{
	int const *				_hoops_ACPCA;
	int						count;
	struct _hoops_GPPCA *		node;
	char					*_hoops_ASAPR = list;
	char					*_hoops_PSAPR;

	if ((count = _hoops_SCPCA->count) == 0) {
		HI_Return_Chars (list, _hoops_GGCIR, "", 0);
		return;
	}

	if (_hoops_GGCIR == -1)
		_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR;		/* _hoops_IHRPR _hoops_IAHA */
	else
		_hoops_PSAPR = _hoops_ASAPR + _hoops_GGCIR;				/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */

	_hoops_ACPCA = &_hoops_SCPCA->_hoops_ASACA[count - 1];
	node = _hoops_ASPCA (&_hoops_ACPCA, &count);
	_hoops_RGHCA (&_hoops_ASAPR, _hoops_PSAPR, node, 666);
	_hoops_RPPCA (node);

	if (_hoops_ASAPR == null) {
		HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, overflow);
		return;
	}

	/* _hoops_GHHR _hoops_PRRP */
	if (_hoops_GGCIR == -1) {
		if (_hoops_ASAPR == _hoops_PSAPR) {
			HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, overflow);
			return;
		}
		*_hoops_ASAPR = '\0';								/* _hoops_IHRPR _hoops_IAHA */
	}
	else {
		_hoops_RGGA (_hoops_ASAPR == _hoops_PSAPR) *_hoops_ASAPR++ = ' ';	/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */
	}
}


GLOBAL_FUNCTION void HI_Copy_Conditional (
	_hoops_CCPCA const *	in,
	_hoops_CCPCA alter *	_hoops_PAGR)
{
	_hoops_PAGR->_hoops_ASACA = (int *)HI_Clone_Aligned (in->_hoops_ASACA, in->count * sizeof (int));
	_hoops_PAGR->count = in->count;

	for (int i=0; i<_hoops_PAGR->count; i++)
		if (_hoops_PAGR->_hoops_ASACA[i] >= 0)
			_hoops_PRRH (HOOPS_WORLD->_hoops_PCIIR[_hoops_PAGR->_hoops_ASACA[i]]);
}

GLOBAL_FUNCTION void HI_Free_Conditional (
	_hoops_CCPCA alter *	_hoops_GHPIR)
{
	if (_hoops_GHPIR->count > 0) {
		for (int i=0; i<_hoops_GHPIR->count; i++)
			if (_hoops_GHPIR->_hoops_ASACA[i] >= 0)
				_hoops_HPRH (HOOPS_WORLD->_hoops_PCIIR[_hoops_GHPIR->_hoops_ASACA[i]]);

		FREE_ARRAY (_hoops_GHPIR->_hoops_ASACA, _hoops_GHPIR->count, int);
	}
}

GLOBAL_FUNCTION bool HI_Condition_Passed (
	int							_hoops_HGHCA,
	unsigned int const *		_hoops_IGHCA,
	_hoops_CCPCA const *			condition) {
	int const *					_hoops_ASACA = condition->_hoops_ASACA;
	int							count = condition->count;
	unsigned int				_hoops_CGHCA = 0;

	if (count == 0)
		return true;

	/* _hoops_ASRHR, _hoops_RGAR _hoops_IIAH _hoops_IH _hoops_RAGPR _hoops_SGHCA _hoops_SGS _hoops_GA'_hoops_RA _hoops_AISI _hoops_RRI _hoops_HSAR 32 _hoops_AAIP */
	while (count--) {
		int				code = *_hoops_ASACA++;

		switch (code) {
			case _hoops_IHPCA: {
				_hoops_CGHCA ^= 1;
			}	break;
			case _hoops_HIPCA: {
				_hoops_CGHCA = (_hoops_CGHCA >> 1) & (_hoops_CGHCA & 1);
			}	break;
			case _hoops_ISACA: {
				_hoops_CGHCA = (_hoops_CGHCA >> 1) | (_hoops_CGHCA & 1);
			}	break;
			case _hoops_RIPCA:
			case _hoops_SIPCA: {
				_hoops_CGHCA = (_hoops_CGHCA >> 1) ^ (_hoops_CGHCA & 1);
			}	break;
			case _hoops_AIPCA: {
				_hoops_CGHCA = (_hoops_CGHCA >> 1) ^ (_hoops_CGHCA & 1) ^ 1;
			}	break;

			default: {
				unsigned int	bit = 0;

				if (_hoops_IGHCA != null) {
					int				index = code / 32;
					int				offset = code % 32;

					if (index < _hoops_HGHCA)
						bit = (_hoops_IGHCA[index] >> offset) & 1;
				}

				_hoops_CGHCA = (_hoops_CGHCA << 1) | bit;
			}	break;
		}
	}

	return _hoops_CGHCA != 0;
}





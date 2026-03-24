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
 * $Id: obf_tmp.txt 1.39 2009-10-23 23:30:22 trask Exp $
 */

#include "hoops.h"
#include "hi_proto.h"


/* _hoops_PIP: _hoops_RH "*_hoops_CCAHR++" _hoops_PIPPR _hoops_HRGR _hoops_IGI _hoops_IRS _hoops_AHCPR; _hoops_RGR _hoops_SIAS _hoops_HAR _hoops_SHH _hoops_RIRA _hoops_GPP
 * _hoops_PCGGGR _hoops_IACAR _hoops_HIH _hoops_SCH _hoops_RCGPA _hoops_GGSR _hoops_SGS _hoops_RH _hoops_HCGGGR _hoops_HICA, _hoops_HPGR _hoops_CHGC,
 * _hoops_HRGR _hoops_SHSS _hoops_IS _hoops_HGCR _hoops_SCH _hoops_HHSH _hoops_HCR _hoops_RH _hoops_PPRRR _hoops_ISSC _hoops_IS _hoops_RRHAR.
 */




GLOBAL_FUNCTION int HI_String_Length (
	char const		*start) {
	char const		*in = start;

	do {} _hoops_RGGA (*in++ == '\0');
	return in - start - 1;
}


GLOBAL_FUNCTION bool HI_Equal_Strings (
	char const		*a,
	char const		*b) {

	while (*a++ == *b) if (*b++ == '\0') return true;
	return false;
}


GLOBAL_FUNCTION bool HI_CI_Equal_Strings (
	char const		*a,
	char const		*b) {

	while (_hoops_SHPCR (*a) == _hoops_SHPCR (*b)) {
		if (*b++ == '\0') return true;
		++a;
	}
	return false;
}


GLOBAL_FUNCTION bool HI_Equal_Strings_To_Max (
	char const		*a,
	int				max,
	char const		*b) {

	do {
		if (--max < 0) return true;
		if (*a++ != *b) return false;
	}
	_hoops_RGGA (*b++ == '\0');

	return true;
}


GLOBAL_FUNCTION bool HI_CI_Equal_Strings_To_Max (
	char const		*a,
	int				max,
	char const		*b) {

	do {
		if (--max < 0) return true;
		if (_hoops_SHPCR (*a) != _hoops_SHPCR (*b)) return false;
		++a;
	}
	_hoops_RGGA (*b++ == '\0');

	return true;
}


GLOBAL_FUNCTION int HI_Compare_Strings (
	char const		*a,
	char const		*b) {

	while (*a++ == *b) if (*b++ == '\0') return 0;

	if (_hoops_IRGCR(a[-1]) < _hoops_IRGCR(*b))
		return -1;
	else
		return 1;
}



GLOBAL_FUNCTION int HI_Compare_Strings_To_Max (
	char const		*a,
	int				max,
	char const		*b) {

	do {
		if (--max < 0) return 0;
		if (*a++ != *b) {
			if (_hoops_IRGCR(a[-1]) < _hoops_IRGCR(*b))
				return -1;
			else
				return 1;
		}
	}
	_hoops_RGGA (*b++ == '\0');

	return 0;
}



GLOBAL_FUNCTION void HI_Copy_String (
	char const		*in,
	char			*_hoops_PAGR) {

	do {} _hoops_RGGA ((*_hoops_PAGR++ = *in++) == '\0');
}


GLOBAL_FUNCTION void HI_Copy_String_To_Max (
	char const		*in,
	int				max,
	char			*_hoops_PAGR) {

	do if (--max < 0) {
		*_hoops_PAGR = '\0';
		break;
	}
	_hoops_RGGA ((*_hoops_PAGR++ = *in++) == '\0');
}


GLOBAL_FUNCTION void HI_Append_String (
	char const		*in,
	char			*_hoops_PAGR) {

	do {} _hoops_RGGA (*_hoops_PAGR++ == '\0');
	--_hoops_PAGR;
	do {} _hoops_RGGA ((*_hoops_PAGR++ = *in++) == '\0');
}


GLOBAL_FUNCTION void HI_Append_String_To_Max (
	char const		*in,
	int				max,
	char			*_hoops_PAGR) {

	do {} _hoops_RGGA (*_hoops_PAGR++ == '\0');
	--_hoops_PAGR;

	do if (--max < 0) {
		*_hoops_PAGR = '\0';
		break;
	}
	_hoops_RGGA ((*_hoops_PAGR++ = *in++) == '\0');
}


GLOBAL_FUNCTION bool HI_Wild_Equal_Strings (
	char const		*a,
	char const		*p) {
	char			test, _hoops_RSGHR;
	char const		*sp;
	char const		*sa;

	sp = null;
	sa = null;
	_hoops_PCCAR {
		if ((_hoops_RSGHR = *p++) == '*') {
			if (*p == '\0')	 return	 true;
			sp = p;
			sa = a;
		}
		else if (_hoops_RSGHR == '\0') {
			if (*a == '\0')	 return	 true;
			if ((p = sp) == null)  return  false;
			a = ++sa;
		}
		else if ((test = *a++) == '\0')	 return	 false;
		else if (test != _hoops_RSGHR  &&  _hoops_RSGHR != '%'	&&	_hoops_RSGHR != '?') {
			if ((p = sp) == null)  return  false;
			a = ++sa;
		}
	}
}


GLOBAL_FUNCTION bool HI_CI_Wild_Equal_Strings (
	char const		*a,
	char const		*p) {
	char			test, _hoops_RSGHR;
	char const		*sp;
	char const		*sa;

	sp = null;
	sa = null;
	_hoops_PCCAR {
		if ((_hoops_RSGHR = *p++) == '*') {
			if (*p == '\0')	 return	 true;
			sp = p;
			sa = a;
		}
		else if (_hoops_RSGHR == '\0') {
			if (*a == '\0')	 return	 true;
			if ((p = sp) == null)  return  false;
			a = ++sa;
		}
		else if ((test = *a++) == '\0')	 return	 false;
		else if (_hoops_SHPCR(test) != _hoops_SHPCR(_hoops_RSGHR)  &&
				  _hoops_RSGHR != '%'  &&  _hoops_RSGHR != '?') {
			if ((p = sp) == null)  return  false;
			a = ++sa;
		}
	}
}

GLOBAL_FUNCTION bool HI_CI_Wild_Equal_Strings_To_Max (
	char const		*a,
	int				max,
	char const		*p) {
	char			test, _hoops_RSGHR;
	char const		*sp;
	char const		*sa;
	char const		*end = a+max;

	sp = null;
	sa = null;
	_hoops_PCCAR {
		if ((_hoops_RSGHR = *p++) == '*') {
			if (*p == '\0')	 return	 true;
			sp = p;
			sa = a;
		}
		else if (_hoops_RSGHR == '\0') {
			if (*a == '\0'	||	a == end)  return  true;
			if ((p = sp) == null)  return  false;
			a = ++sa;
		}
		else if ((test = *a++) == '\0')	 return	 false;
		else if (_hoops_SHPCR(test) != _hoops_SHPCR(_hoops_RSGHR)  &&
				  _hoops_RSGHR != '%'  &&  _hoops_RSGHR != '?') {
			if ((p = sp) == null)  return  false;
			a = ++sa;
		}
	}
}


GLOBAL_FUNCTION char const * HI_First_Substring_In_String (
	char const		*_hoops_RHCIH,
	char const		*string) {
	char			_hoops_RSGHR;
	char const		*_hoops_ICGGGR = _hoops_RHCIH;
	char const		*_hoops_CCGGGR;

	_hoops_RGGA ((_hoops_RSGHR = *string) == '\0') {
		if (_hoops_RSGHR == *_hoops_RHCIH) {
			_hoops_CCGGGR = string++;
			do {
				if (*++_hoops_RHCIH == '\0') return  _hoops_CCGGGR;
				else if (*_hoops_RHCIH != *string) break;
				++string;
			} _hoops_PCCAR;
			_hoops_RHCIH = _hoops_ICGGGR;
			string = ++_hoops_CCGGGR;
		}
		else
			++string;
	}
	return	null;
}



GLOBAL_FUNCTION char const * HI_Last_Substring_In_String (
	char const		*_hoops_RHCIH,
	char const		*string) {
	char			_hoops_RSGHR;
	char const		*_hoops_ICGGGR = _hoops_RHCIH;
	char const		*_hoops_CCGGGR;
	char const		*_hoops_ACCAA = null;

	_hoops_RGGA ((_hoops_RSGHR = *string) == '\0') {
		if (_hoops_RSGHR == *_hoops_RHCIH) {
			_hoops_CCGGGR = string++;
			do {
				if (*++_hoops_RHCIH == '\0') {
					_hoops_ACCAA = _hoops_CCGGGR;
					break;
				}
				else if (*_hoops_RHCIH != *string) break;
				++string;
			} _hoops_PCCAR;
			_hoops_RHCIH = _hoops_ICGGGR;
			string = ++_hoops_CCGGGR;
		}
		else
			++string;
	}
	return	_hoops_ACCAA;
}

GLOBAL_FUNCTION char const * HI_CI_First_Substring_In_String (
	char const		*_hoops_RHCIH,
	char const		*string) {
	char			_hoops_RSGHR;
	char const		*_hoops_ICGGGR = _hoops_RHCIH;
	char const		*_hoops_CCGGGR;

	_hoops_RGGA ((_hoops_RSGHR = *string) == '\0') {
		if (_hoops_SHPCR(_hoops_RSGHR) == _hoops_SHPCR(*_hoops_RHCIH)) {
			_hoops_CCGGGR = string++;
			do {
				if (*++_hoops_RHCIH == '\0') return  _hoops_CCGGGR;
				else if (_hoops_SHPCR(*_hoops_RHCIH) != _hoops_SHPCR(*string)) break;
				++string;
			} _hoops_PCCAR;
			_hoops_RHCIH = _hoops_ICGGGR;
			string = ++_hoops_CCGGGR;
		}
		else
			++string;
	}
	return	null;
}



GLOBAL_FUNCTION char const * HI_CI_Last_Substring_In_String (
	char const		*_hoops_RHCIH,
	char const		*string) {
	char			_hoops_RSGHR;
	char const		*_hoops_ICGGGR = _hoops_RHCIH;
	char const		*_hoops_CCGGGR;
	char const		*_hoops_ACCAA = null;

	_hoops_RGGA ((_hoops_RSGHR = *string) == '\0') {
		if (_hoops_SHPCR(_hoops_RSGHR) == _hoops_SHPCR(*_hoops_RHCIH)) {
			_hoops_CCGGGR = string++;
			do {
				if (*++_hoops_RHCIH == '\0') {
					_hoops_ACCAA = _hoops_CCGGGR;
					break;
				}
				else if (_hoops_SHPCR(*_hoops_RHCIH) != _hoops_SHPCR(*string)) break;
				++string;
			} _hoops_PCCAR;
			_hoops_RHCIH = _hoops_ICGGGR;
			string = ++_hoops_CCGGGR;
		}
		else
			++string;
	}
	return	_hoops_ACCAA;
}



GLOBAL_FUNCTION char * HI_Copy_Chars (
	char const		*in,
	char			*_hoops_PAGR) {

	do {} _hoops_RGGA ((*_hoops_PAGR++ = *in++) == '\0');

	return _hoops_PAGR - 1;
}

GLOBAL_FUNCTION void HI_Copy_Name_To_Chars (
	_hoops_HCRPR const *	in,
	char alter *	_hoops_PAGR) {

	if (in->length != 0)
		_hoops_AIGA (in->text, in->length+1, char, _hoops_PAGR);
	else
		*_hoops_PAGR = '\0';
}

GLOBAL_FUNCTION void HI_Copy_Chars_To_Name (
	char const *	in,
	_hoops_HCRPR alter *	_hoops_IACIH) {

	if ((_hoops_IACIH->length = _hoops_SSGR (in)) > 0) {
		ALLOC_ARRAY (_hoops_IACIH->text, _hoops_IACIH->length+1, char);
		_hoops_AIGA (in, _hoops_IACIH->length+1, char, _hoops_IACIH->text);
	}
	else
		_hoops_IACIH->text = null;
}


GLOBAL_FUNCTION void HI_Copy_KName (
	KName const          *in,
	KName                *_hoops_PAGR) {

	if (in->length == 0) {
		_hoops_PAGR->length = 0;
		_hoops_PAGR->_hoops_IPPPP = null;
	}
	else
	if (in->length > 0) {
		_hoops_PAGR->length = in->length;
		ALLOC_ARRAY (_hoops_PAGR->_hoops_IPPPP, _hoops_PAGR->length+1, Karacter);
		_hoops_AIGA (in->_hoops_IPPPP, _hoops_PAGR->length+1, Karacter, _hoops_PAGR->_hoops_IPPPP);
	}
	else {
		_hoops_PAGR->length = in->length;
		int len = (-in->length+15)/16;
		ALLOC_ARRAY(_hoops_PAGR->_hoops_IPPPP, len, Karacter);
		_hoops_AIGA(in->_hoops_IPPPP, len, Karacter, _hoops_PAGR->_hoops_IPPPP);
	}
}



GLOBAL_FUNCTION void HI_Copy_Name (
	_hoops_HCRPR const *	in,
	_hoops_HCRPR alter *	_hoops_PAGR) {

	if (in->length == 0) {
		_hoops_PAGR->length = 0;
		_hoops_PAGR->text = null;
	}
	else
	if (in->length > 0) {
		_hoops_PAGR->length = in->length;
		ALLOC_ARRAY(_hoops_PAGR->text, _hoops_PAGR->length+1, char);
		_hoops_AIGA(in->text, _hoops_PAGR->length+1, char, _hoops_PAGR->text);
	}
	else {
		_hoops_PAGR->length = in->length;
		int len = (-in->length+7)/8;
		ALLOC_ARRAY(_hoops_PAGR->text, len, char);
		_hoops_AIGA(in->text, len, char, _hoops_PAGR->text);
	}
}

GLOBAL_FUNCTION _hoops_AAPIR * HI_Copy_Name_List (
	_hoops_AAPIR const      *in) {
	_hoops_AAPIR            *_hoops_SCGGGR;
	_hoops_AAPIR            **_hoops_PISGH = &_hoops_SCGGGR;

	_hoops_RGGA (in == null) {
		_hoops_AAPIR    *_hoops_PAGR;

		ZALLOC (_hoops_PAGR, _hoops_AAPIR);
		*_hoops_PISGH = _hoops_PAGR;
		_hoops_PISGH = &_hoops_PAGR->next;
		
		HI_Copy_Name (&in->name, &_hoops_PAGR->name);
		
		_hoops_PAGR->key = in->key;

		in = in->next;
	}

	*_hoops_PISGH = null;
	return _hoops_SCGGGR;
}

GLOBAL_FUNCTION void HI_Free_Name_List (_hoops_AAPIR * old)
{
	while (old != null) {
		_hoops_AAPIR *_hoops_PAGR = old->next;
		_hoops_RGAIR(old->name);
		FREE (old, _hoops_AAPIR);
		old = _hoops_PAGR;
	}
}



GLOBAL_FUNCTION void * HI_Clone_Anything (
	void const		*in,
	unsigned int	size) 
{
	char			*_hoops_GSGGGR;
	void			*_hoops_PAGR;

	if (size <= 0 || in == null) return null;

	ALLOC_ARRAY (_hoops_GSGGGR, (long)size, char);
	_hoops_PAGR = (void *)_hoops_GSGGGR;
	COPY_MEMORY(in, size, _hoops_PAGR);

	return _hoops_PAGR;
}


GLOBAL_FUNCTION void * HI_Clone_Aligned (
	void const		*in,
	unsigned int	size) 
{
	void			*_hoops_PAGR;
	char			*_hoops_RSGGGR;

	if (size <= 0 || in == null) return null;
	ALLOC_ARRAY (_hoops_RSGGGR, (long)size, char);
	_hoops_PAGR = (void *)_hoops_RSGGGR;
	COPY_MEMORY(in, size, _hoops_PAGR);

	return _hoops_PAGR;
}



GLOBAL_FUNCTION void HI_Canonize_Chars (
	char const		*string,
	_hoops_HCRPR			*name) {
	int				_hoops_ICHPP;
	char const		*_hoops_RPPA;
	char			*_hoops_GSGGGR;

	/* _hoops_HASIR _hoops_GHAAI _hoops_GC */
	while (*string == ' ' || *string == '\t') ++string;

	/* _hoops_RPR _hoops_IGCIS, _hoops_ISRHA _hoops_GPGR _hoops_HGS */
	_hoops_ICHPP = 0;
	_hoops_RPPA = string;

	if (*_hoops_RPPA == '\0') {
		name->length = 0;
		name->text = null;
		return;
	}

	do if (*_hoops_RPPA == ' ' || *_hoops_RPPA == '\t') {
		while (_hoops_RPPA[1] == ' ' || _hoops_RPPA[1] == '\t') ++_hoops_RPPA, --_hoops_ICHPP;
	}
	_hoops_RGGA (*++_hoops_RPPA == '\0');

	_hoops_ICHPP += _hoops_RPPA - string;

	/* _hoops_PSPHC _hoops_GRCIR _hoops_GC(_hoops_GRI) */

	if (_hoops_RPPA[-1] == ' ' || _hoops_RPPA[-1] == '\t') --_hoops_ICHPP;

	ALLOC_ARRAY (_hoops_GSGGGR, _hoops_ICHPP+1, char);
	name->text = _hoops_GSGGGR;
	name->length = _hoops_ICHPP;

	do {
		char	c = *string++;

		if (c == ' ' || c == '\t') {
			while (*string == ' ' || *string == '\t') ++string;
			*_hoops_GSGGGR++ = ' ';
		}
		else
			*_hoops_GSGGGR++ = _hoops_SHPCR (c);
	}
	_hoops_RGGA (--_hoops_ICHPP == 0);
	*_hoops_GSGGGR = '\0';
}

GLOBAL_FUNCTION void HI_Canonize_Chars_Quoted (
	char const		*string,
	_hoops_HCRPR			*name,
	bool		_hoops_CRCIH) {
	int				_hoops_ICHPP;
	char const		*_hoops_RPPA;
	char const		*_hoops_ASGGGR;
	char			*_hoops_GSGGGR;
	char			_hoops_PPARA;

	/* _hoops_HASIR _hoops_GHAAI _hoops_GC */
	while (*string == ' ' || *string == '\t') ++string;

	/* _hoops_RPR _hoops_IGCIS, _hoops_ISRHA _hoops_GPGR _hoops_HGS */
	_hoops_ICHPP = 0;
	_hoops_RPPA = string;

	if (*_hoops_RPPA == '\0') {
		name->length = 0;
		name->text = null;
		return;
	}

	_hoops_PPARA = '\0';
	do {
		char	c = *_hoops_RPPA++;

		if (c == '"' || c == '\'' || c == '`') {
			if (c == _hoops_PPARA || !_hoops_PPARA) {
				_hoops_PPARA ^= c;
				if (!_hoops_CRCIH && *_hoops_RPPA != c)
					--_hoops_ICHPP;
			}
		}
		else if (!_hoops_PPARA && (c == ' ' || c == '\t'))
			while (*_hoops_RPPA == ' ' || *_hoops_RPPA == '\t')
				++_hoops_RPPA, --_hoops_ICHPP;
	} _hoops_RGGA (*_hoops_RPPA == '\0');

	_hoops_ICHPP += _hoops_RPPA - string;

	/* _hoops_PSPHC _hoops_GRCIR _hoops_GC(_hoops_GRI) */

	while (_hoops_ICHPP > 0 && (_hoops_RPPA[-1] == ' ' || _hoops_RPPA[-1] == '\t')) {
		_hoops_ICHPP--;
		_hoops_RPPA--;
	}
	_hoops_ASGGGR = _hoops_RPPA;

	ALLOC_ARRAY (_hoops_GSGGGR, _hoops_ICHPP+1, char);
	name->text = _hoops_GSGGGR;
	name->length = _hoops_ICHPP;

	
	_hoops_RPPA = string;
	_hoops_PPARA = '\0';
	while (_hoops_RPPA != _hoops_ASGGGR) {
		char	c = *_hoops_RPPA++;

		if (c == '"' || c == '\'' || c == '`') {
			if (c == _hoops_PPARA || !_hoops_PPARA) {
				_hoops_PPARA ^= c;
				if (_hoops_CRCIH)
					*_hoops_GSGGGR++ = c;
				else if (*_hoops_RPPA == c) {
					*_hoops_GSGGGR++ = *_hoops_RPPA++;
					_hoops_PPARA ^= c;
				}
			}
			else
				/* _hoops_CPARA _hoops_IIGR _hoops_IRS _hoops_HAGH _hoops_IAHA, _hoops_IAS._hoops_ISHI. _hoops_RH _hoops_PSGGGR _hoops_GGR "_hoops_CCGPH'_hoops_GRI _hoops_HH" */
				*_hoops_GSGGGR++ = c; 
		}
		else if (_hoops_PPARA)
			*_hoops_GSGGGR++ = c;
		else if (c == ' ' || c == '\t') {
			while (*_hoops_RPPA == ' ' || *_hoops_RPPA == '\t') ++_hoops_RPPA;
			*_hoops_GSGGGR++ = ' ';
		}
		else
			*_hoops_GSGGGR++ = _hoops_SHPCR (c);

	}
	*_hoops_GSGGGR = '\0';
}


GLOBAL_FUNCTION void HI_Canonize_Kars (
	Karacter const		*string,
	KName				*_hoops_SIHSA) {
	int						_hoops_ICHPP;
	Karacter const		*_hoops_IHSCP;
	Karacter				*_hoops_HSGGGR;

	/* _hoops_HASIR _hoops_GHAAI _hoops_GC */
	while (*string == ' ' || *string == '\t') ++string;

	/* _hoops_RPR _hoops_IGCIS, _hoops_ISRHA _hoops_GPGR _hoops_HGS */
	_hoops_ICHPP = 0;
	_hoops_IHSCP = string;

	if (*_hoops_IHSCP == '\0') {
		_hoops_SIHSA->length = 0;
		_hoops_SIHSA->_hoops_IPPPP = null;
		return;
	}

	do if (*_hoops_IHSCP == ' ' || *_hoops_IHSCP == '\t') {
		while (_hoops_IHSCP[1] == ' ' || _hoops_IHSCP[1] == '\t') ++_hoops_IHSCP, --_hoops_ICHPP;
	}
	_hoops_RGGA (*++_hoops_IHSCP == '\0');

	_hoops_ICHPP += _hoops_IHSCP - string;

	/* _hoops_PSPHC _hoops_GRCIR _hoops_GC(_hoops_GRI) */

	if (_hoops_IHSCP[-1] == ' ' || _hoops_IHSCP[-1] == '\t') --_hoops_ICHPP;

	ALLOC_ARRAY (_hoops_HSGGGR, _hoops_ICHPP+1, Karacter);
	_hoops_SIHSA->_hoops_IPPPP = _hoops_HSGGGR;
	_hoops_SIHSA->length = _hoops_ICHPP;

	do {
		Karacter		c = *string++;

		if (c == ' ' || c == '\t') {
			while (*string == ' ' || *string == '\t') ++string;
			*_hoops_HSGGGR++ = ' ';
		}
		else if ((c & 0xFF00) != 0)
			*_hoops_HSGGGR++ = c;
		else
			*_hoops_HSGGGR++ = _hoops_SHPCR ((unsigned char)c);
	}
	_hoops_RGGA (--_hoops_ICHPP == 0);
	*_hoops_HSGGGR = 0;
}



GLOBAL_FUNCTION int HI_Compare_Names (
	_hoops_HCRPR const	*a,
	_hoops_HCRPR const	*b) {
	int				cmp;

	if (a->length < b->length) {
		if (a->length == 0)
			return -1;
		if ((cmp = _hoops_CIGGI (a->text, a->length, b->text)) != 0)
			return cmp;

		return -1;
	}
	else if (a->length > b->length) {
		if (b->length == 0)
			return 1;
		if ((cmp = _hoops_CIGGI (a->text, b->length, b->text)) != 0)
			return cmp;

		return 1;
	}
	else
		return _hoops_CIGGI (a->text, a->length, b->text);
}


/*
* _hoops_PAGA: _hoops_RGR _hoops_API _hoops_SSSCP _hoops_SHH _hoops_AHAAR _hoops_IS _hoops_IRS _hoops_GCGGI() _hoops_PAR _hoops_SIGGI() _hoops_GGR _hoops_RH _hoops_PSHR
* _hoops_SHIGR _hoops_SGS _hoops_ISGGGR() _hoops_HHS, _hoops_GAR _hoops_CACSH _hoops_PAH _hoops_HAHA _hoops_RH _hoops_CPCP
* _hoops_IIGR "_hoops_ICHRR" _hoops_HSH _hoops_CGPR _hoops_RGAR _hoops_HCHAR _hoops_HPGR _hoops_RH _hoops_IGGA "_hoops_GCSRR".
*
* _hoops_SAGAR, _hoops_RGR _hoops_API _hoops_HRGR _hoops_IPIH _hoops_PPRAR -- _hoops_HCR _hoops_PGHC _hoops_RAIA _hoops_AAPR _hoops_RGAR
* _hoops_IPAC _hoops_IH [_hoops_GGR]_hoops_GHRCC, _hoops_HAR _hoops_AGR, _hoops_PPR _hoops_HS _hoops_RPII _hoops_RASA _hoops_CCA _hoops_RH _hoops_CCAH
* _hoops_CSGGGR() _hoops_RIGR, _hoops_PGAP *_hoops_PAH* _hoops_SGH _hoops_SIGGI().
*/

GLOBAL_FUNCTION int HI_Compare_KNames (
	KName const          *a,
	KName const          *b) {
	Karacter const       *_hoops_CAARA = a->_hoops_IPPPP,
	*_hoops_ASAPR = b->_hoops_IPPPP;
	int                     _hoops_SCPPR;

	if (a->length < b->length) {
		if ((_hoops_SCPPR = a->length) > 0) do {
			if (*_hoops_CAARA++ != *_hoops_ASAPR++) {
				if (_hoops_CAARA[-1] < _hoops_ASAPR[-1])
					return -1;
				else
					return 1;
			}
		}
		_hoops_RGGA (--_hoops_SCPPR == 0);

		return -1;
	}
	else {
		if ((_hoops_SCPPR = b->length) > 0) do {
			if (*_hoops_CAARA++ != *_hoops_ASAPR++) {
				if (_hoops_CAARA[-1] < _hoops_ASAPR[-1])
					return -1;
				else
					return 1;
			}
		}
		_hoops_RGGA (--_hoops_SCPPR == 0);

		if (a->length == b->length)
			return 0;
		else
			return 1;
	}
}








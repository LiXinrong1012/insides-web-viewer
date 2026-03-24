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
 * $Id: obf_tmp.txt 1.23 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "database.h"
#include "adt.h"


#define _hoops_GRIPP		-1				
#define _hoops_RRIPP		-2				
#define _hoops_ARIPP		-3				
#define _hoops_PRIPP		-4				
#define _hoops_HRIPP		-5
#define _hoops_IRIPP	-6
#define _hoops_CRIPP		-7
#define _hoops_SRIPP	-8
#define _hoops_GAIPP	-9

local const _hoops_IGRCR _hoops_RAIPP[] = {
	{_hoops_GRIPP,		_hoops_GRRCR ("config"),	_hoops_ARSAP,  -999, false},
	{_hoops_ARIPP,		_hoops_GRRCR ("reset"),		_hoops_RRRCR,    0, false},
	{_hoops_PRIPP,		_hoops_GRRCR ("flush"),		_hoops_RRRCR,    0, false},
	{_hoops_RRIPP,	_hoops_GRRCR ("software"),	_hoops_RRRCR,    0, false},

	{_hoops_HRIPP,		_hoops_GRRCR ("tristrip minimum"),					_hoops_APRCA,    1, false},
	{_hoops_IRIPP,	_hoops_GRRCR ("display list tristrip minimum"),	_hoops_APRCA,    1, false},
	{_hoops_CRIPP,	_hoops_GRRCR ("flat tristrip minimum"),				_hoops_APRCA,    1, false},
	{_hoops_SRIPP,	_hoops_GRRCR ("flat display list tristrip minimum"),_hoops_APRCA,    1, false},
	{_hoops_GAIPP,	_hoops_GRRCR ("general tristrip minimum"),			_hoops_APRCA,    1, false},

};


GLOBAL_FUNCTION void HI_Free_Driver_Config(
		_hoops_ARARR *_hoops_GPPHA) 
{
	_hoops_AAPIR    *victim;

	_hoops_RGAIR(_hoops_GPPHA->driver);
	_hoops_RGAIR(_hoops_GPPHA->id);
	_hoops_RGAIR(_hoops_GPPHA->version);
	_hoops_RGAIR(_hoops_GPPHA->_hoops_AAIPP);

	_hoops_RGGA ((victim = _hoops_GPPHA->config) == null) {
		_hoops_GPPHA->config = victim->next;
		_hoops_RGAIR (victim->name);
		FREE (victim, _hoops_AAPIR);
	}

	FREE(_hoops_GPPHA, _hoops_ARARR);
}

GLOBAL_FUNCTION _hoops_ARARR * HI_Clone_Driver_Config(
		_hoops_ARARR *_hoops_GPPHA) 
{
	_hoops_ARARR *_hoops_PAIPP;

	ZALLOC(_hoops_PAIPP, _hoops_ARARR);

	if (_hoops_GPPHA) {
		_hoops_AAPIR    *item;

		_hoops_RSAI(_hoops_GPPHA, _hoops_ARARR, _hoops_PAIPP);
		HI_Copy_Name(&_hoops_GPPHA->driver, &_hoops_PAIPP->driver); 
		HI_Copy_Name(&_hoops_GPPHA->id, &_hoops_PAIPP->id); 
		HI_Copy_Name(&_hoops_GPPHA->version, &_hoops_PAIPP->version); 
		HI_Copy_Name(&_hoops_GPPHA->_hoops_AAIPP, &_hoops_PAIPP->_hoops_AAIPP); 
		
		_hoops_PAIPP->config = 0;
		item = _hoops_GPPHA->config;
		while (item) {
			_hoops_AAPIR	*new_item;

			ALLOC (new_item, _hoops_AAPIR);
			HI_Copy_Name (&item->name, &new_item->name);
			new_item->next = _hoops_PAIPP->config;
			_hoops_PAIPP->config = new_item;
			item = item->next;
		}

		_hoops_PAIPP->next=0;
	}

	return _hoops_PAIPP;
}

#define _hoops_HAIPP	0x001
#define _hoops_IAIPP	0x010
#define _hoops_CAIPP 0x100
#define _hoops_SAIPP  0x110
#define _hoops_GPIPP  0x101
#define _hoops_RPIPP  0x011

local bool _hoops_APIPP (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			required,
	char const *			_hoops_PPIPP) 
{
	char const		*_hoops_AIPPA = required;
	char const		*_hoops_PIPPA = _hoops_PPIPP;
	char const		*_hoops_HPIPP = _hoops_AIPPA + 2048;
	char const		*_hoops_IPIPP = _hoops_PIPPA + 2048;
	int _hoops_CPIPP = 0, _hoops_SPIPP = 0;
	int _hoops_GHIPP = _hoops_SAIPP;
	int result = _hoops_IAIPP;

	if (required[0] == '<' && required[1] == '=') {
		_hoops_GHIPP = _hoops_RPIPP;
		_hoops_AIPPA += 2;
	}
	else if (required[0] == '>' && required[1] == '=') {
		_hoops_GHIPP = _hoops_SAIPP;
		_hoops_AIPPA += 2;
	}
	else if (required[0] == '!' && required[1] == '=') {
		_hoops_GHIPP = _hoops_GPIPP;
		_hoops_AIPPA += 2;
	}
	if (required[0] == '<') {
		_hoops_GHIPP = _hoops_HAIPP;
		_hoops_AIPPA += 1;
	}
	else if (required[0] == '>') {
		_hoops_GHIPP = _hoops_CAIPP;
		_hoops_AIPPA += 1;
	}

	for (;;) {
		if (*_hoops_AIPPA == '*' || *_hoops_AIPPA == '*') {
			result = _hoops_IAIPP;
			break;
		}
		HI_Scan_Integer (_hoops_RIGC, &_hoops_AIPPA, _hoops_HPIPP, &_hoops_CPIPP);
		HI_Scan_Integer (_hoops_RIGC, &_hoops_PIPPA, _hoops_IPIPP, &_hoops_SPIPP);
		if (_hoops_SPIPP > _hoops_CPIPP) {
			result = _hoops_CAIPP;
			break;
		}
		else if (_hoops_SPIPP < _hoops_CPIPP) {
			result = _hoops_HAIPP;
			break;
		}
		if (*_hoops_AIPPA != '.' || *_hoops_PIPPA != '.') {
			/* _hoops_RGAR _hoops_RPP _hoops_GIPR _hoops_RHIPP _hoops_HS _hoops_HPIH _hoops_AHIPP _hoops_IS _hoops_PCR _hoops_AA
			 * _hoops_SR _hoops_SAS _hoops_GPP _hoops_IS _hoops_RH _hoops_SPS _hoops_HHIPR */
			result = _hoops_IAIPP;
			break;
		}
		else {
			_hoops_AIPPA++;
			_hoops_PIPPA++;
		}
	}

	if (BIT (result, _hoops_GHIPP))
		return true;
	else
		return false;
}


GLOBAL_FUNCTION _hoops_ARARR * HI_Lookup_Driver_Config(
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			driver,
	char const *			id,
	char const *			version,
	bool					_hoops_PHIPP,
	XBits const	*			_hoops_HHIPP) 
{
	_hoops_ARARR *	_hoops_GPPHA = HOOPS_WORLD->_hoops_IHIPP;

	while (_hoops_GPPHA) {

		_hoops_ARARR *_hoops_CHIPP = _hoops_GPPHA->next;

		if ((_hoops_IGGPA(_hoops_GPPHA->driver.text, driver) || 
					HI_CI_Wild_Equal_Strings(_hoops_GPPHA->driver.text, driver) ||
					HI_CI_Wild_Equal_Strings(driver, _hoops_GPPHA->driver.text)) &&
			(_hoops_IGGPA(_hoops_GPPHA->id.text, id) || 
					HI_CI_Wild_Equal_Strings(_hoops_GPPHA->id.text, id) ||
					HI_CI_Wild_Equal_Strings(id, _hoops_GPPHA->id.text)) &&
				_hoops_APIPP (_hoops_RIGC, _hoops_GPPHA->version.text, version)) {

			_hoops_ARARR *_hoops_SHIPP;

			_hoops_SHIPP = HI_Clone_Driver_Config(_hoops_GPPHA);

			if (_hoops_HHIPP) {
				_hoops_AAPIR    *item;

				item = _hoops_SHIPP->config;
				while (item) {
					int i=0;
					const char *ptr = item->name.text;

					if (_hoops_GIIPP(ptr, "XBIT_", 5))
						ptr += 5;

					while (_hoops_HHIPP[i].options[0] != '\0') {

						if (_hoops_IGGPA(ptr, _hoops_HHIPP[i].options)) {

							int offset = XBIT_OFFSET(_hoops_HHIPP[i].bit);
							int bit = XBIT_BIT(_hoops_HHIPP[i].bit);

							_hoops_SHIPP->_hoops_HHIPP[offset] |= (1<<bit);
							break;
						}

						i++;
					}

					if (_hoops_HHIPP[i].options[0] == '\0') {
						HE_WARNING (HEC_SYSTEM, HES_INVALID_INPUT,
									 Sprintf_N (null,
									   "Driver config '%n' unknown -- ignoring",
										&item->name));					
					}
					item = item->next;
				}


			}

			return _hoops_SHIPP;
		}

		_hoops_GPPHA=_hoops_CHIPP;
	}

	if (_hoops_PHIPP) {
		return HI_Clone_Driver_Config(0);
	}

	return 0;
}

GLOBAL_FUNCTION void HI_Read_Driver_Config_File()
{
	//_hoops_IRIGR _hoops_GGR _hoops_RIIPP _hoops_PPR _hoops_IRHH _hoops_HCPH _hoops_IS _hoops_AIIPP();
	unsigned int i;

	vconf_t* v = new_vconf( HOOPS_WORLD->memory_pool );
	vconf_set_delimiter(v, ':');
	vconf_set_file_style(v, VCONF_FILE_STYLE_CHUNKED);
	if (!vconf_read_file(v, HOOPS_WORLD->_hoops_PARPR.text)) {
		HE_ERROR (HEC_FILE_IO, HES_FILE_OPEN,
			"Could not open driver config file specified in environment variable HOOPS_DRIVER_CONFIG_FILE.");
		delete_vconf(v);
		return;
	}

	for (i=0; i<vconf_chunk_count(v); i++) {
		const char * driver = null;
		const char * id = null;
		const char * version = null;
		const char * config = null;

		vconf_set_chunk(v, i);
		if (vconf_option_count(v) > 4) {
			HE_WARNING (HEC_FILE_IO, HES_INVALID_INPUT,
				"Malformed driver config file: Too many options; check for illegal multi-line options.");
			continue;
		}

		driver	= vconf_get_option(v, "DRIVER");
		id		= vconf_get_option(v, "ID");
		version	= vconf_get_option(v, "VERSION");
		config	= vconf_get_option(v, "CONFIG");

		if (driver == null)
			HE_WARNING (HEC_FILE_IO, HES_INVALID_INPUT,
				"Malformed driver config file: missing DRIVER information.");

		if (id == null)
			HE_WARNING (HEC_FILE_IO, HES_INVALID_INPUT,
				"Malformed driver config file: missing ID information.");

		if (version == null)
			HE_WARNING (HEC_FILE_IO, HES_INVALID_INPUT,
				"Malformed driver config file: missing VERSION information.");

		if (config == null)
			HE_WARNING (HEC_FILE_IO, HES_INVALID_INPUT,
				"Malformed driver config file: missing CONFIG information.");

		if (driver == null || id == null || version == null || config == null)
			continue;

		HC_Define_Driver_Config(driver, id, version, config);
	}

	delete_vconf(v);
}

GLOBAL_FUNCTION void HI_Flush_Driver_Config(
	char const *	driver,
	char const *	id,
	char const *	version) 
{
	_hoops_ARARR *_hoops_GPPHA;
	_hoops_ARARR *_hoops_PIIPP=0;

	_hoops_GPPHA = HOOPS_WORLD->_hoops_IHIPP;

	while (_hoops_GPPHA) {

		_hoops_ARARR *_hoops_CHIPP = _hoops_GPPHA->next;

		if ((_hoops_IGGPA(_hoops_GPPHA->driver.text, driver) || 
					HI_CI_Wild_Equal_Strings(_hoops_GPPHA->driver.text, driver)) &&
			(_hoops_IGGPA(_hoops_GPPHA->id.text, id) || 
					HI_CI_Wild_Equal_Strings(_hoops_GPPHA->id.text, id)) &&
			(_hoops_IGGPA(_hoops_GPPHA->version.text, version) || 
					HI_CI_Wild_Equal_Strings(_hoops_GPPHA->version.text, version))) {

			HI_Free_Driver_Config(_hoops_GPPHA);
		}
		else {

			_hoops_GPPHA->next = _hoops_PIIPP;
			_hoops_PIIPP = _hoops_GPPHA->next;
		}

		_hoops_GPPHA=_hoops_CHIPP;
	}

	HOOPS_WORLD->_hoops_IHIPP = _hoops_PIIPP;
}

HC_INTERFACE void HC_CDECL HC_Define_Driver_Config(
	char const *	driver,
	char const *	id,
	char const *	version,
	char const *	config) 
{
	_hoops_PAPPR context("Define_Driver_Config");

	if (!driver || !id || !version || !config) {
		HE_ERROR (HEC_HOOPS_SYSTEM, HES_INVALID_INPUT, "Define_Driver_Config requires four non null values");
		return;
	}

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Define_Driver_Config (%S, %S, ", driver, id));
		HI_Dump_Code (Sprintf_SS (null, "%S, %S);\n", version, config));
	);

	_hoops_HIACR (_hoops_HIIPP, _hoops_RAIPP);

	Option_Value	*option_list;
	Option_Value	*option;

	if (HI_Parse_Options (context, config, _hoops_CIACR (_hoops_HIIPP), &option_list, _hoops_SIACR)) {

		_hoops_ARARR *_hoops_GPPHA;

		_hoops_GPPHA = HI_Clone_Driver_Config(0);

		HI_Canonize_Chars(driver, &_hoops_GPPHA->driver);
		HI_Canonize_Chars(id, &_hoops_GPPHA->id);
		HI_Canonize_Chars(version, &_hoops_GPPHA->version);
		HI_Copy_Chars_To_Name(config, &_hoops_GPPHA->_hoops_AAIPP);

		if ((option = option_list) != null) do {

			switch (option->type->id) {

				case _hoops_GRIPP: {

					_hoops_AAPIR    *victim;
					int				count;
					_hoops_HCRPR			*_hoops_HGPIR;
					_hoops_AAPIR	**item;

					/* _hoops_CASI _hoops_GH */
					_hoops_RGGA ((victim = _hoops_GPPHA->config) == null) {
						_hoops_GPPHA->config = victim->next;
						_hoops_RGAIR (victim->name);
						FREE (victim, _hoops_AAPIR);
					}

					count = option->_hoops_AIPCR;
					item	= &_hoops_GPPHA->config;
					_hoops_HGPIR = option->value._name;

					_hoops_RGGA (count-- == 0) {
						if (_hoops_HGPIR->length > 0) {
							ALLOC (*item, _hoops_AAPIR);
							HI_Copy_Name (_hoops_HGPIR, &(*item)->name);
							item = &(*item)->next;
							*item = null;
						}
						++_hoops_HGPIR;
					}
			
				}break;

				case _hoops_ARIPP: {
					HI_Flush_Driver_Config(driver, id, version);
					HI_Reset_Driver_Config_SS();
					HI_Free_Driver_Config(_hoops_GPPHA);
					goto _hoops_PRSPR;
				}break;

				case _hoops_PRIPP: {
					HI_Flush_Driver_Config(driver, id, version);
					HI_Free_Driver_Config(_hoops_GPPHA);
					goto _hoops_PRSPR;
				}break;

				case _hoops_RRIPP: {
					_hoops_GPPHA->flags |= _hoops_IIIPP;
				}break;

				case _hoops_HRIPP: {
					_hoops_GPPHA->_hoops_CIIPP = option->value._hoops_RIARA[0];
				}break;

				case _hoops_IRIPP: {
					_hoops_GPPHA->_hoops_SIIPP = option->value._hoops_RIARA[0];
				}break;

				case _hoops_CRIPP: {
					_hoops_GPPHA->_hoops_GCIPP = option->value._hoops_RIARA[0];
				}break;

				case _hoops_SRIPP: {
					_hoops_GPPHA->_hoops_RCIPP = option->value._hoops_RIARA[0];
				}break;

				case _hoops_GAIPP: {
					_hoops_GPPHA->_hoops_CIIPP = option->value._hoops_RIARA[0];
					_hoops_GPPHA->_hoops_SIIPP = option->value._hoops_RIARA[0];
					_hoops_GPPHA->_hoops_GCIPP = option->value._hoops_RIARA[0];
					_hoops_GPPHA->_hoops_RCIPP = option->value._hoops_RIARA[0];
				}break;

			}

		} _hoops_RGGA ((option = option->next) == null);

		_hoops_GPPHA->next = HOOPS_WORLD->_hoops_IHIPP;
		HOOPS_WORLD->_hoops_IHIPP = _hoops_GPPHA;

_hoops_PRSPR:
		HI_Free_Option_List (context, option_list);
	}

}


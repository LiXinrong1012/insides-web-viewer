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
 * $Id: obf_tmp.txt 1.19 2011-01-08 00:54:14 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "tandt.h"
#include "hpserror.h"
#include "hd_proto.h"
#include "hi_proto.h"


GLOBAL_FUNCTION float HD_Compute_Generic_Size (
	Net_Rendition const & 		nr,
	double						value,
	_hoops_GIGRP			_hoops_HHP,
	float						_hoops_HGPAR,
	bool						_hoops_HPIHH,
	bool alter *				_hoops_IA,
	bool						errors) {
	float						size = 1.0f;
#ifndef DISABLE_DRAW_3D
	Display_Context const *		dc = nr->_hoops_SRA;

	if (_hoops_IA)
		*_hoops_IA = true;

	switch (_hoops_HHP) {
		case _hoops_SPSC: {
			_hoops_SGCC const &		_hoops_HSGA = nr->transform_rendition->_hoops_IPH;

			if (_hoops_HSGA->data._hoops_CPH != 0.0f)
				size = _hoops_HSGA->data._hoops_CPH;
			else {
				float	tmp;

				size = ((Vector const *)&_hoops_HSGA->data.elements[0][0])->length();
				if ((tmp = ((Vector const *)&_hoops_HSGA->data.elements[1][0])->length()) > size)
					size = tmp;
				if ((tmp = ((Vector const *)&_hoops_HSGA->data.elements[2][0])->length()) > size)
					size = tmp;
			}
		}	_hoops_HHHI;

		case GSU_ORU: {
			_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
			_hoops_HHRA const *				_hoops_SPH = nr->transform_rendition->_hoops_SPH;
			float						width, height;

			width  = (float)(_hoops_SGRA->_hoops_CIIH.right -
							 _hoops_SGRA->_hoops_CIIH.left + 1);
			height = (float)(_hoops_SGRA->_hoops_CIIH.top -
							 _hoops_SGRA->_hoops_CIIH.bottom + 1);

			if (_hoops_HPIHH) {
				if (_hoops_SPH->_hoops_CSIH < _hoops_SGRA->_hoops_CSIH)
					size *= (float)value * 0.5f * (float)width;
				else
					size *= (float)value * 0.5f * (float)height;
			}
			else if (_hoops_SPH->projection == _hoops_SSIH ||
				_hoops_SPH->_hoops_CSIH >= _hoops_SGRA->_hoops_CSIH)
				size *= (float)value * height / _hoops_SPH->_hoops_SSPA;
			else
				size *= (float)value * width / _hoops_SPH->_hoops_ISPA;
		}	break;

		case GSU_SRU: {
			size = (float)value * (float)dc->current._hoops_PRPSR.y;
		}	break;

		case GSU_WRU: {
			_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;

			size = (float)value *
				   (float)(_hoops_SGRA->_hoops_CIIH.top - _hoops_SGRA->_hoops_CIIH.bottom + 1);
		}	break;

		case GSU_POINTS: {
			size = (float)value *				/* _hoops_RSSA */
				   (float)(1.0/72 *					/* _hoops_IPIHH _hoops_RIR _hoops_PPSR */
						 2.54 *						/* _hoops_SAPSR _hoops_RIR _hoops_CPIHH */
						 1.0001) *					/* (_hoops_GIRR _hoops_GH _hoops_IRS _hoops_RSCA) */
				   dc->current._hoops_HAP.y;	/* _hoops_ASPA _hoops_RIR _hoops_SPIHH */

			if (!BIT(dc->flags, _hoops_CSHSR))
				size *= HOOPS_WORLD->_hoops_IRGHP;

		}	break;

		case GSU_PIXELS: {
			size = (float)value;
		}	break;

		case GSU_PERCENT: {
			size = _hoops_HGPAR * ((float)value/100.0f);
		}	break;

		case GSU_SCALE: {
			size = _hoops_HGPAR * (float)value;
		}	break;

		default: {
			if (_hoops_IA)
				*_hoops_IA = false;

			if (errors) {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "'size units' ?");
			}
			size = 10.0f;
		}	break;
	}
#endif

	return size;
}



char const *_hoops_GHIHH[] = {
	"???",				/* (_hoops_RHIHH) */
	"oru",
	"sru",
	"wru",
	"pixels",	
	"points",
	"%",
	"",
	"wsu"
};

GLOBAL_FUNCTION void HI_Format_Generic_Size_String (
	_hoops_HCAIR const *	size,
	char alter *			list,
	int						_hoops_GGCIR) 
{
	char alter *			_hoops_ASAPR = list;
	char alter *			_hoops_PSAPR;
	local const char		_hoops_SSACR[] = "Return string won't fit in provided space";

	float					value = size->value;
	_hoops_GIGRP		_hoops_HHP = size->_hoops_HHP;

	if (_hoops_GGCIR == -1)
		_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR;	/* _hoops_IHRPR _hoops_IAHA */
	else
		_hoops_PSAPR = _hoops_ASAPR + _hoops_GGCIR;	/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */

	_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f", &value);
	if (_hoops_HHP != 0)
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s", _hoops_GHIHH[(int)_hoops_HHP]);

	if (_hoops_ASAPR == null) {
		HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_SSACR);
		return;
	}

	/* _hoops_GHHR _hoops_PRRP */
	if (_hoops_GGCIR == -1) {
		if (_hoops_ASAPR == _hoops_PSAPR) {
			HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_SSACR);
			return;
		}
		*_hoops_ASAPR = '\0';								/* _hoops_IHRPR _hoops_IAHA */
	}
	else {
		_hoops_RGGA (_hoops_ASAPR == _hoops_PSAPR) *_hoops_ASAPR++ = ' ';	/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */
	}
}
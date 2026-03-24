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
 * $Id: obf_tmp.txt 1.69 2010-09-22 02:29:38 trask Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"

static void _hoops_IHIHP(_hoops_RHAH const * &_hoops_CSIR, 
						   Driver_Color const * &_hoops_AHHHP,
						   _hoops_GARSR	& _hoops_CHIHP,
						   _hoops_GARSR	& _hoops_RHHHP,
						   _hoops_RHAH const * _hoops_SPRAR,
						   Display_Context const *		dc)
{
	int							_hoops_SHIHP;
	Named_Material const *		_hoops_ISHIR;
	Driver_Color alter *		_hoops_GIIHP;

	/* _hoops_CRCH _hoops_GII _hoops_RHGS _hoops_ARCR */
	if (_hoops_AHHHP != null && _hoops_CHIHP > 0)
		FREE_ARRAY (_hoops_AHHHP, _hoops_CHIHP, Driver_Color);
	_hoops_AHHHP = null;

	_hoops_CSIR = _hoops_SPRAR;

	if ((_hoops_CHIHP = _hoops_SHIHP = _hoops_SPRAR->length) == 0)
		return;

	if (dc->options._hoops_RAHHP) {
		RGB const *				rgb;

		POOL_ALLOC_ARRAY_CACHED (_hoops_GIIHP, _hoops_SHIHP, Driver_Color, dc->memory_pool);
		_hoops_SHIHP = _hoops_CHIHP;
		_hoops_AHHHP = _hoops_GIIHP;
		_hoops_ISHIR = _hoops_SPRAR->_hoops_HAA;

		do {
			rgb = &_hoops_ISHIR->_hoops_CSHR;
			if (rgb && rgb->_hoops_CPIR() > 0.5f) {
				*_hoops_GIIHP = dc->_hoops_SPHHP;
			}
			else
				*_hoops_GIIHP = dc->_hoops_GHHHP;

			++_hoops_GIIHP;
			++_hoops_ISHIR;
		}
		_hoops_RGGA (--_hoops_SHIHP == 0);
	}
	else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) {
		float					_hoops_PHHHP;

		POOL_ALLOC_ARRAY_CACHED (_hoops_GIIHP, _hoops_SHIHP, Driver_Color, dc->memory_pool);
		_hoops_SHIHP = _hoops_CHIHP;
		_hoops_AHHHP = _hoops_GIIHP;
		_hoops_ISHIR = _hoops_SPRAR->_hoops_HAA;

		_hoops_PHHHP = (float)dc->_hoops_PGCC._hoops_PCHSR - 0.01f;

		do {
			_hoops_GIIHP->_hoops_HRIR.r =
				dc->_hoops_PGCC._hoops_HHHHP[(int)(_hoops_ISHIR->_hoops_CSHR.red * _hoops_PHHHP)];
			_hoops_GIIHP->_hoops_HRIR.g =
				dc->_hoops_PGCC._hoops_HHHHP[(int)(_hoops_ISHIR->_hoops_CSHR.green * _hoops_PHHHP)];
			_hoops_GIIHP->_hoops_HRIR.b =
				dc->_hoops_PGCC._hoops_HHHHP[(int)(_hoops_ISHIR->_hoops_CSHR.blue * _hoops_PHHHP)];
			_hoops_GIIHP->_hoops_HRIR.a = _hoops_GPGCR;


			++_hoops_GIIHP;
			++_hoops_ISHIR;
		}
		_hoops_RGGA (--_hoops_SHIHP == 0);
	}
	else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_RIIHP) {
		float					_hoops_PHHHP;

		POOL_ALLOC_ARRAY_CACHED (_hoops_GIIHP, _hoops_SHIHP, Driver_Color, dc->memory_pool);
		_hoops_SHIHP = _hoops_CHIHP;
		_hoops_AHHHP = _hoops_GIIHP;
		_hoops_ISHIR = _hoops_SPRAR->_hoops_HAA;

		_hoops_PHHHP = (float)dc->_hoops_PGCC._hoops_PCHSR - 0.001f;

		do {
			_hoops_GIIHP->_hoops_PIHHP = (_hoops_HIHHP)(_hoops_ISHIR->_hoops_CSHR._hoops_CPIR() * _hoops_PHHHP);
			++_hoops_GIIHP;
			++_hoops_ISHIR;
		}
		_hoops_RGGA (--_hoops_SHIHP == 0);
	}
	else /* _hoops_AIIHP */ {	 /* _hoops_IPHR'_hoops_GRI _hoops_AIAH _hoops_RPII _hoops_CPHR _hoops_HPP _hoops_PIIHP */
		_hoops_HIIHP const *	_hoops_IIIHP;

		_hoops_IIIHP = (_hoops_HIIHP const *)_hoops_SPRAR->_hoops_PPRPR;

		if (_hoops_IIIHP != null) {		/* _hoops_SPR _hoops_PIIHP _hoops_CIIHP _hoops_SR _hoops_RRP */
			if (_hoops_IIIHP->_hoops_SIIHP == _hoops_GIHHP)
				_hoops_RHHHP = dc->_hoops_RIHHP;/* _hoops_SCSAA */
			else
				_hoops_RHHHP = _hoops_IIIHP->_hoops_SIIHP;
		}
	}
}


GLOBAL_FUNCTION void HD_Downwind_Color_Map (
	Net_Rendition alter &		nr,
	Attribute const *			_hoops_ASGPR) {
#ifndef DISABLE_COLOR_MAPS
	_hoops_RHAH const *			_hoops_SPRAR=null;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_CAHHP			_hoops_SAHHP;

	_hoops_SAHHP = nr.Modify()->_hoops_ASIR.Modify()->_hoops_PSIR.Modify();

	if (_hoops_ASGPR->type == HK_COLOR_MAP) {
		_hoops_SPRAR = (_hoops_RHAH const *)_hoops_ASGPR;
		
		_hoops_IHIHP (_hoops_SAHHP->_hoops_CSIR, _hoops_SAHHP->_hoops_AHHHP, 
						_hoops_SAHHP->length, _hoops_SAHHP->_hoops_RHHHP, _hoops_SPRAR, dc);

		if (nr->_hoops_ARA->_hoops_CICP._hoops_CCCRP == _hoops_HCCRP) {
			_hoops_GRA alter &		_hoops_GCIHP = nr->_hoops_ARA.Modify();

			if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_HIRC)) {
				_hoops_GCIHP->_hoops_CICP.scale = _hoops_SAHHP->_hoops_CSIR->length - 1;
				_hoops_GCIHP->_hoops_CICP.translate = 0.0f;
			}
			else {
				_hoops_GCIHP->_hoops_CICP.scale = _hoops_SAHHP->_hoops_CSIR->length;
				_hoops_GCIHP->_hoops_CICP.translate = -0.5f;
			}
		}
	}
	else if(_hoops_ASGPR->type == HK_RENDERING_OPTIONS) {
		_hoops_RHAIR * _hoops_RCIHP = (_hoops_RHAIR *) _hoops_ASGPR;

		if (_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_CHAIR) {
			if (BIT(_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_CHAIR->_hoops_IGRPR->_hoops_RRHH, _hoops_HGAGR))	{
				Style *		style = _hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_CHAIR;

				if ((*style->_hoops_SHAIR = style->_hoops_GRRPR) != null)
					style->_hoops_GRRPR->_hoops_SHAIR = style->_hoops_SHAIR;
				_hoops_HPRH(style);
				_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_CHAIR = null;
			}
		}

		if (_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_CHAIR == null) {			
			_hoops_HCRPR			name;

			HI_Canonize_Chars_Quoted (_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR.text, &name, false);
			HI_Open_Segment(dc->_hoops_RIGC, _hoops_RCIHP->owner);

			_hoops_CRCP *		_hoops_SRCP = HI_One_Segment_Search (dc->_hoops_RIGC, name.text, false);

			HI_Close_Segment (dc->_hoops_RIGC);

			if (_hoops_SRCP != null) {
				Style *		style;

				ZALLOC (style, Style);
				style->type = HK_STYLE;
				style->_hoops_HIHI = 1;
				style->owner = (_hoops_CRCP*)_hoops_RCIHP;
				style->_hoops_CPGPR = _hoops_HCHPA;
				style->key = _hoops_AIRIR (style);
				
				_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_CHAIR=style;
				style->backlink = (Attribute**)&_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_CHAIR;

				style->_hoops_IGRPR = _hoops_SRCP;
				_hoops_PRRH (_hoops_SRCP);
				_hoops_ACSCA(dc->_hoops_RIGC, style, _hoops_SRCP);
			}
			_hoops_RGAIR (name);
		}

		if (_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_CHAIR == null) {
			if (!_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_RGAHA) {
				HE_WARNING (HEC_RENDERING, HES_INVALID_SEG_NAME_PARAMETER,
							Sprintf_N (null, "Gooch color map segment '%n' does not exist",
										&_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR));
				_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_RGAHA=true;
			}
		}
		else {
			Attribute *		_hoops_HPHCR = _hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_CHAIR->_hoops_IGRPR->_hoops_IPPGR;

			if (_hoops_HPHCR != null) do {	
				if(_hoops_HPHCR->type == HK_COLOR_MAP){
					break;
				}
			} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
			if (_hoops_HPHCR == null && !_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_RGAHA) {
				HE_WARNING (HEC_RENDERING, HES_REQUIRES_COLOR_MAP,
							Sprintf_N (null, "No color map exists in segment '%n'.",
										&_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR));
				_hoops_RCIHP->_hoops_HHAIR->_hoops_IHAIR._hoops_RGAHA=true;
			}
			else
				_hoops_SPRAR=(_hoops_RHAH *) _hoops_HPHCR;
		}

		if (_hoops_SPRAR == null) {	//_hoops_RGHH _hoops_IRAP _hoops_HAIR _hoops_ARCR _hoops_SGHC
			_hoops_SAHHP->_hoops_ISIR = null;
			_hoops_SAHHP->_hoops_ACIHP = null;
			_hoops_SAHHP->_hoops_HSIR = 0;
			return;
		}

		_hoops_IHIHP (_hoops_SAHHP->_hoops_ISIR, _hoops_SAHHP->_hoops_ACIHP, 
						_hoops_SAHHP->_hoops_HSIR, _hoops_SAHHP->_hoops_RHHHP, _hoops_SPRAR, dc);
	}
	
#endif
}

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
 * $Id: obf_tmp.txt 1.202 2010-10-25 23:13:00 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "patterns.h"
#include "hi_proto.h"
#include "hd_proto.h"
#include "hpserror.h"


GLOBAL_FUNCTION RGB HD_Apply_Color_Effects (
	RGB const &					_hoops_SHGCR,
	_hoops_AHAH const &				_hoops_CSPHP) {
	RGB							result = _hoops_SHGCR;
	float						_hoops_HHGA = 0.0f;

	if (BIT (_hoops_CSPHP._hoops_ACGRP, _hoops_AIGRP)) {
		result = _hoops_SHGCR * _hoops_CSPHP.scale + _hoops_CSPHP.translate;

		result.red   = _hoops_IAAA (0.0f, _hoops_AHIA (result.red,   1.0f));
		result.green = _hoops_IAAA (0.0f, _hoops_AHIA (result.green, 1.0f));
		result.blue  = _hoops_IAAA (0.0f, _hoops_AHIA (result.blue,  1.0f));
	}

	if (BIT (_hoops_CSPHP._hoops_ACGRP, _hoops_CIGRP)) {
		_hoops_HHGA = result._hoops_CPIR();
		result = RGB (_hoops_HHGA);
	}

	if (BIT (_hoops_CSPHP._hoops_ACGRP, _hoops_SIGRP)) {
		result *= _hoops_CSPHP.color;
	}
	else if (ALLBITS (_hoops_CSPHP._hoops_ACGRP, _hoops_RCGRP)) {
		RGB const &				color = _hoops_CSPHP.color;

		_hoops_HHGA *= 2.0f;
		_hoops_HHGA -= 1.0f;

		if (_hoops_HHGA <= 0.0f)
			result = color + _hoops_HHGA * color;
		else
			result = color + _hoops_HHGA * (1.0f - color);
	}

	return result;
}

local void _hoops_SSPHP (
	Net_Rendition const &		nr,
	_hoops_HHA alter &	_hoops_GGHHP,
	Named_Material const *		_hoops_RGHHP,
	_hoops_ARGRA			_hoops_PCGS) {

	Named_Material				_hoops_GGPRA;
	_hoops_RCR *					_hoops_AGHHP = null;
	_hoops_SRHSR					_hoops_PGHHP = _hoops_GRRCR ("-");
	_hoops_SRHSR					_hoops_HGSH = _hoops_GRRCR ("*");
	bool						_hoops_CCCIR = false;

	_hoops_CPAIR				_hoops_CICSR;
	_hoops_CICSR.textures = nr->_hoops_GCCSR->textures;
	_hoops_CICSR.keys = nr->_hoops_GCCSR->keys;
	_hoops_CICSR.count = nr->_hoops_GCCSR->count;

	Integer32	_hoops_PSSGA = nr->_hoops_GCCSR->_hoops_CPA;

	if (BIT (_hoops_RGHHP->_hoops_PRGRA, _hoops_RHGRA) &&
		!BIT (_hoops_PCGS, M_DIFFUSE) &&
		((_hoops_GGHHP->_hoops_ARIR && 
		  nr->_hoops_GCCSR->_hoops_CPA != _hoops_GGHHP->_hoops_HGHHP) ||
		 !HI_Diffuse_Channels_Match (_hoops_GGHHP->_hoops_SCA, _hoops_RGHHP->_hoops_SCA, _hoops_PSSGA))) {
		_hoops_HIR *	head=null;
		_hoops_HIR *	_hoops_PGC=null;
		_hoops_HIR *	_hoops_IGHHP;
		_hoops_HIR **	_hoops_ASRGR;

		if (BIT (_hoops_RGHHP->_hoops_PRGRA, _hoops_RHGRA) && 
			_hoops_RGHHP->_hoops_SCA != null)
			head = _hoops_PGC = HI_Mix_Diffuse_Channels (_hoops_GGHHP->_hoops_SCA, _hoops_RGHHP->_hoops_SCA);

		_hoops_GGHHP.Modify();
		_hoops_GGHHP->_hoops_HGHHP = nr->_hoops_GCCSR->_hoops_CPA;
		_hoops_CCCIR = true;

		if (_hoops_GGHHP->_hoops_SCA != null) {
			HI_Free_Diffuse_Channel_List (_hoops_GGHHP->_hoops_SCA);
			_hoops_GGHHP->_hoops_SCA = null;
		}
		_hoops_ASRGR = &_hoops_GGHHP->_hoops_SCA;

		while (_hoops_PGC) {
			_hoops_IGHHP = null;
			if (_hoops_RAHSR (_hoops_PGC->texture->name, _hoops_PGHHP) ||
				_hoops_RAHSR (_hoops_PGC->texture->name, _hoops_HGSH)) { 
				/* _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_IRS "-" _hoops_PAR _hoops_IRS "*", _hoops_SAHR _hoops_HSGR _hoops_SCH */
				_hoops_PGC = _hoops_PGC->next;
				continue;
			}
			/* _hoops_HPPR _hoops_IS _hoops_HGCR _hoops_RH _hoops_HH _hoops_RH _hoops_PIHGR _hoops_PPRRR _hoops_SCH _hoops_SSCP _hoops_SGSS 1 _hoops_AIAH */
			else if ((_hoops_AGHHP = HI_Activate_Texture(_hoops_PGC->texture, &_hoops_CICSR, false, _hoops_PSSGA)) == null) {
				if (BIT (_hoops_PGC->flags, _hoops_CCARA)) {
					HE_WARNING (HEC_COLOR, HES_DEFINITION_NOT_FOUND,
						Sprintf_N (null, "Found explicit but undefined texture specification: '%n'", &_hoops_PGC->texture->_hoops_PAPIR->name));
					_hoops_AGHHP = HI_Activate_Texture(_hoops_PGC->texture, &_hoops_CICSR, true, _hoops_PSSGA);
				}
				else { 
					char		_hoops_APARA[_hoops_CGHHP];
					_hoops_HCRPR		texture_name;

					/* _hoops_HA _hoops_SR _hoops_PIHA _hoops_HPPR _hoops_HPHR _hoops_ACIPR _hoops_IS _hoops_HGCR _hoops_RH _hoops_HAIR */
					ZERO_STRUCT(&_hoops_GGPRA, Named_Material);
					Sprintf_N (_hoops_APARA, "%n", &_hoops_PGC->texture->name);
					texture_name.text = _hoops_APARA;
					texture_name.length = _hoops_PGC->texture->name.length;

					if (HI_Evaluate_Color (nr->_hoops_SRA->_hoops_RIGC, &texture_name, &_hoops_GGPRA, &_hoops_CICSR, true)) {
						if (_hoops_GGPRA._hoops_SCA) {
							_hoops_IGHHP = _hoops_GGPRA._hoops_SCA;
							_hoops_GGPRA._hoops_SCA = null;
							if (BIT (_hoops_GGPRA._hoops_PRGRA, M_DIFFUSE)) {
								HI_HLS_To_RGB ((_hoops_PACHR const *)&_hoops_GGPRA._hoops_CSHR, &_hoops_IGHHP->texture->_hoops_HPIR._hoops_IPIR);
								_hoops_IGHHP->flags |= _hoops_PRA;
							}
						}
					}
					else {
						HE_ERROR (HEC_COLOR, HES_NULL_INPUT, "Color specification is blank");
						if (_hoops_AGHHP)
							_hoops_HPRH (_hoops_AGHHP);
						_hoops_AGHHP=null;
					}
					HI_Free_Material_Names (&_hoops_GGPRA, 1);
				}
			}
			if (_hoops_AGHHP || _hoops_IGHHP) {
				if (!_hoops_IGHHP) {
					_hoops_IGHHP = HI_New_Diffuse_Channel (_hoops_AGHHP);
					_hoops_HPRH (_hoops_AGHHP); /* _hoops_SAII _hoops_IIGR _hoops_SGHHP _hoops_CGI _hoops_IS _hoops_GRHHP */
					_hoops_IGHHP->flags = _hoops_PGC->flags;
				}
				_hoops_IGHHP->_hoops_HGA = _hoops_PGC->_hoops_HGA;
				*_hoops_ASRGR = _hoops_IGHHP;
				_hoops_ASRGR = &_hoops_IGHHP->next;
				if (BIT (_hoops_PGC->flags, _hoops_PRA))
					_hoops_AGHHP->_hoops_HPIR._hoops_IPIR = _hoops_PGC->texture->_hoops_HPIR._hoops_IPIR;
			}
			_hoops_PGC = _hoops_PGC->next;
		}
		/* _hoops_RPP _hoops_RH _hoops_HSPR _hoops_AASA _hoops_IS _hoops_CIH _hoops_SPI _hoops_RCAP _hoops_HIGR _hoops_SGIPR _hoops_IGRC _hoops_CRRHP _hoops_AI, _hoops_SCH _hoops_HRGR _hoops_RRHHP
		 * _hoops_PCCP _hoops_SGCRP _hoops_RIHH.  _hoops_IPCP _hoops_ARHHP _hoops_HPGR _hoops_RH _hoops_HSPP _hoops_HRGR _hoops_AGIA _hoops_IS _hoops_IGGRA _hoops_PII _hoops_IRS _hoops_IPS */
		/*_hoops_RPP (_hoops_HARS->_hoops_HH->_hoops_SGSS == 1)
			_hoops_PRHHP (_hoops_HRHHP, _hoops_IRHHP, "_hoops_GSGI _hoops_AIPH _hoops_CGRPR _hoops_RPR");*/
		HI_Free_Diffuse_Channel_List (head);
	}


	for (int i=0; i<_hoops_GAGRA; i++) {
		if (!BIT (_hoops_PCGS, HOOPS_READ_ONLY._hoops_AHGRA[i]) &&
			BIT (_hoops_RGHHP->_hoops_PRGRA, HOOPS_READ_ONLY._hoops_APGRA[i]) &&
			_hoops_GGHHP->texture[i] != _hoops_RGHHP->texture[i]) {

			if (!_hoops_CCCIR) {
				_hoops_GGHHP.Modify();
				_hoops_GGHHP->_hoops_HGHHP = nr->_hoops_GCCSR->_hoops_CPA;
				_hoops_CCCIR = true;
			}

			if (_hoops_GGHHP->texture[i] != null) {
				_hoops_HPRH (_hoops_GGHHP->texture[i]);
				_hoops_GGHHP->texture[i] = null;
			}

			if (_hoops_RGHHP->texture[i]) {
				/* _hoops_HPPR _hoops_IS _hoops_HGCR _hoops_RH _hoops_HH _hoops_RH _hoops_PIHGR _hoops_PPRRR _hoops_SCH _hoops_SSCP _hoops_SGSS 1 _hoops_AIAH */
				if ((_hoops_GGHHP->texture[i] = HI_Activate_Texture(_hoops_RGHHP->texture[i], &_hoops_CICSR, false, _hoops_PSSGA)) != null) {
					if (BIT (_hoops_RGHHP->flags[i], _hoops_PRA)) {
						_hoops_GGHHP->texture[i]->_hoops_SCR |= _hoops_ICARA;
						_hoops_GGHHP->color[i] = _hoops_RGHHP->texture[i]->_hoops_HPIR._hoops_IPIR;
					}
				}
				else {
					if (BIT (_hoops_RGHHP->flags[i], _hoops_CCARA)) {
						HE_WARNING (HEC_COLOR, HES_DEFINITION_NOT_FOUND,
							Sprintf_N (null, "Found explicit but undefined texture specification: '%n'", _hoops_RGHHP->texture[i]->_hoops_PAPIR));
						_hoops_GGHHP->texture[i] = HI_Activate_Texture(_hoops_RGHHP->texture[i], &_hoops_CICSR, true, _hoops_PSSGA);
						if (BIT (_hoops_RGHHP->flags[i], _hoops_PRA)) {
							_hoops_GGHHP->texture[i]->_hoops_SCR |= _hoops_ICARA;
							_hoops_GGHHP->color[i] = _hoops_RGHHP->texture[i]->_hoops_HPIR._hoops_IPIR;
						}
					}
					else { 
						char		_hoops_APARA[_hoops_CGHHP];
						_hoops_HCRPR		texture_name;

						/* _hoops_HA _hoops_SR _hoops_PIHA _hoops_HPPR _hoops_HPHR _hoops_ACIPR _hoops_IS _hoops_HGCR _hoops_RH _hoops_HAIR */
						ZERO_STRUCT(&_hoops_GGPRA, Named_Material);
						Sprintf_N (_hoops_APARA, "%n", &_hoops_RGHHP->texture[i]->name);
						texture_name.text = _hoops_APARA;
						texture_name.length = _hoops_SSGR (_hoops_APARA);

						if (HI_Evaluate_Color (nr->_hoops_SRA->_hoops_RIGC, &texture_name, &_hoops_GGPRA, &_hoops_CICSR, true)) {
							if (_hoops_GGPRA._hoops_SCA) {
								_hoops_PRRH(_hoops_GGPRA._hoops_SCA->texture);
								_hoops_GGHHP->texture[i] = _hoops_GGPRA._hoops_SCA->texture;
								if (BIT (_hoops_GGPRA._hoops_PRGRA, M_DIFFUSE)) {
									HI_HLS_To_RGB ((_hoops_PACHR const *)&_hoops_GGPRA._hoops_CSHR, &_hoops_GGHHP->color[i]);
									_hoops_GGHHP->texture[i]->_hoops_SCR |= _hoops_IGA;
								}
							}
						}
						else {
							HE_ERROR (HEC_COLOR, HES_NULL_INPUT, "Color specification is blank");
						}
						HI_Free_Material_Names (&_hoops_GGPRA, 1);
					}
				}
			}
		}
	}

	if (_hoops_CCCIR) {
		/* _hoops_ARP _hoops_RH _hoops_PIRA _hoops_IIGR _hoops_RH _hoops_AIHGR, "_hoops_HSHAR" */
		_hoops_GGHHP->_hoops_ARIR = false;
		if (_hoops_GGHHP->_hoops_SCA)
			_hoops_GGHHP->_hoops_ARIR = true;
		else for (int i=0; i<_hoops_GAGRA; i++) {
			if (_hoops_GGHHP->texture[i]) {
				_hoops_GGHHP->_hoops_ARIR = true;
				break;
			}
		}
	}
}

local _hoops_HHA _hoops_CRHHP (
	Net_Rendition const &		nr,
	_hoops_HHA const &	mat,
	_hoops_ACSGA const *			list,
	_hoops_ARGRA			_hoops_PCGS,
	bool						_hoops_SRHHP) {
	Display_Context const *		dc = nr->_hoops_SRA;
	Named_Material const *		_hoops_RGHHP = null;
	_hoops_HHA			_hoops_GGHHP = mat;
	RGB const *					rgb = null;
	_hoops_AHAH const &				_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;
	bool						_hoops_GAHHP = BIT (_hoops_PHAH.options, _hoops_CHRH);

	if (list->type == _hoops_PPCA) {
		_hoops_APCA const *	normal = (_hoops_APCA const *)list;

		rgb = &normal->rgb;

		if (dc->options._hoops_RAHHP) {
			/* _hoops_PAGA: _hoops_AAHHP _hoops_HGRH _hoops_CR _hoops_RGSR _hoops_IIGR '_hoops_IHPR' _hoops_RAACR _hoops_GHCA _hoops_PAHHP */
			if (!_hoops_SRHHP == !dc->_hoops_HAHHP)
				rgb = &_hoops_GPSR::_hoops_IAHHP;
			else
				rgb = &_hoops_GPSR::_hoops_RPSR;
		}

		if (!BIT (_hoops_PCGS, M_DIFFUSE) && mat->_hoops_CSHR != *rgb) {
			_hoops_GGHHP.Modify();

			if (_hoops_GAHHP)
				_hoops_GGHHP->_hoops_CSHR = HD_Apply_Color_Effects (*rgb, _hoops_PHAH);
			else
				_hoops_GGHHP->_hoops_CSHR = *rgb;

			HI_Free_Diffuse_Channel_List (_hoops_GGHHP->_hoops_SCA);
			_hoops_GGHHP->_hoops_SCA = null;
			_hoops_GGHHP->_hoops_ARIR = false;
			for (int i=0; i<_hoops_GAGRA; i++) {
				if (_hoops_GGHHP->texture[i]) {
					_hoops_GGHHP->_hoops_ARIR = true;
					break;
				}
			}
			return _hoops_GGHHP;
		}

		return mat;
	}


	if (list->type != _hoops_SHGRA) {
		_hoops_HCSGA const *			_hoops_ICSGA = (_hoops_HCSGA const *)list;

		_hoops_RGHHP = &_hoops_ICSGA->_hoops_ISHIR;
	}
#ifndef DISABLE_COLOR_MAPS
	else {
		_hoops_PCSGA const *			findex = (_hoops_PCSGA const *)list;
		_hoops_CAHHP const &		_hoops_SAHHP = nr->_hoops_ASIR->_hoops_PSIR;
		int								index = (int)(findex->value + 0.5f);

		if (index >= (int)_hoops_SAHHP->length) index = 0;

		_hoops_RGHHP = &_hoops_SAHHP->_hoops_CSIR->_hoops_HAA[index];
	}
#endif

	if (_hoops_RGHHP != null) {
		if (ANYBIT (_hoops_RGHHP->_hoops_PRGRA, _hoops_ASARA)) {
			if (!BIT (_hoops_PCGS, M_DIFFUSE) && BIT (_hoops_RGHHP->_hoops_PRGRA, M_DIFFUSE)) {
				rgb = &_hoops_RGHHP->_hoops_CSHR;
				if (dc->options._hoops_RAHHP) {
					if (!_hoops_SRHHP == !dc->_hoops_HAHHP)
						rgb = &_hoops_GPSR::_hoops_IAHHP;
					else
						rgb = &_hoops_GPSR::_hoops_RPSR;
				}
				if (mat->_hoops_CSHR != *rgb) {
					_hoops_GGHHP.Modify();
					if (_hoops_GAHHP)
						_hoops_GGHHP->_hoops_CSHR = HD_Apply_Color_Effects (*rgb, _hoops_PHAH);
					else
						_hoops_GGHHP->_hoops_CSHR = *rgb;
				}
			}
			for (int i=0; i<_hoops_CRGRA; i++) {

				if (!BIT (_hoops_PCGS, HOOPS_READ_ONLY._hoops_AHGRA[i]) &&
					BIT (_hoops_RGHHP->_hoops_PRGRA, HOOPS_READ_ONLY._hoops_SRGRA[i]) &&
					mat->color[i] != _hoops_RGHHP->color[i]) {
					
					_hoops_GGHHP.Modify();

					if (_hoops_GAHHP)
						_hoops_GGHHP->color[i] = HD_Apply_Color_Effects (_hoops_RGHHP->color[i], _hoops_PHAH);
					else
						_hoops_GGHHP->color[i] = _hoops_RGHHP->color[i];
				}
			}
		}


		if (!BIT (_hoops_PCGS, M_TRANSMISSION) &&
			BIT (_hoops_RGHHP->_hoops_PRGRA, M_TRANSMISSION) &&
			mat->_hoops_IRIR != _hoops_RGHHP->_hoops_IRIR &&
			(!BIT(dc->flags, _hoops_GPHHP) || 
			 !nr->_hoops_CPP->_hoops_GHSS._hoops_RPHHP)) {
			_hoops_GGHHP.Modify()->_hoops_IRIR = _hoops_RGHHP->_hoops_IRIR;
		}

		if (dc->_hoops_APHHP == null) {

#ifndef DISABLE_TEXTURING
			if (ANYBIT (_hoops_RGHHP->_hoops_PRGRA, _hoops_PSARA) &&
				(BIT(_hoops_RGHHP->_hoops_PRGRA, _hoops_CHGRA) || _hoops_GGHHP->_hoops_ARIR)) {
				_hoops_SSPHP(nr, _hoops_GGHHP, _hoops_RGHHP, _hoops_PCGS);
			}
#endif

			if (!BIT (_hoops_PCGS, _hoops_RAGRA) &&
				BIT (_hoops_RGHHP->_hoops_PRGRA, _hoops_RAGRA) && 
				mat->gloss != _hoops_RGHHP->gloss) {
				_hoops_GGHHP.Modify()->gloss = _hoops_RGHHP->gloss;
			}

			if (!BIT (_hoops_PCGS, _hoops_AAGRA) &&
				BIT (_hoops_RGHHP->_hoops_PRGRA, _hoops_AAGRA) &&
				mat->_hoops_PAGRA != _hoops_RGHHP->_hoops_PAGRA) {
				_hoops_GGHHP.Modify()->_hoops_PAGRA = _hoops_RGHHP->_hoops_PAGRA;
			}

		}
	}

	return _hoops_GGHHP;
}

#define _hoops_PPHHP(src, _hoops_PCAP) ((_hoops_PCAP)._hoops_HRIR.a = (src)._hoops_HRIR.a)


local bool _hoops_HPHHP (
	Net_Rendition const &		nr,
	_hoops_ACSGA const *			list,
	_hoops_CRCP const *				_hoops_SRCP,
	Driver_Color alter *		_hoops_IPHHP,
	Driver_Color alter *		_hoops_SIPI,
	Driver_Color alter *		face,
	Driver_Color alter *		edge,
	RGB alter *					_hoops_PGC) {
	Display_Context const *		dc = nr->_hoops_SRA;
	Driver_Color				_hoops_CPHHP;

	/*
	 * _hoops_SSCR _hoops_RH _hoops_SPI _hoops_IHSR _hoops_RGAR
	 */
	switch (list->type) {
		case _hoops_SHGRA: {
#ifndef DISABLE_COLOR_MAPS
			if (BIT(dc->flags, _hoops_CPPHP) && dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR)
				*_hoops_PGC = _hoops_GPSR::_hoops_RPSR;
			else {
				_hoops_PCSGA const *			findex = (_hoops_PCSGA const *)list;
				_hoops_CAHHP const &		_hoops_SAHHP = nr->_hoops_ASIR->_hoops_PSIR;
				int								index = (int)(findex->value + 0.5f);

				if (index < (int)_hoops_SAHHP->length) {
					Named_Material const *		_hoops_ISHIR = _hoops_SAHHP->_hoops_CSIR->_hoops_HAA;

					*_hoops_PGC = _hoops_ISHIR[index]._hoops_CSHR;
				}
				else
					*_hoops_PGC = _hoops_GPSR::_hoops_RPSR;
			}
#else
			*_hoops_PGC = _hoops_GPSR::_hoops_RPSR;
#endif
		}	break;

		case _hoops_PPCA: {
			_hoops_APCA const *		normal = (_hoops_APCA const *)list;

			*_hoops_PGC = normal->rgb;
		}	break;

		case _hoops_GIGRA: {
			_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;

			*_hoops_PGC = _hoops_ICSGA->_hoops_ISHIR._hoops_CSHR;
		}	break;
	}

	/*
	 * _hoops_AGGA _hoops_CAHA _hoops_RH _hoops_ACSP _hoops_IIGR _hoops_RH _hoops_PSHA
	 */
	if (dc->options._hoops_RAHHP) {
		*_hoops_IPHHP = dc->_hoops_SPHHP;
		*_hoops_SIPI = dc->_hoops_GHHHP;

		if (ANYBIT (nr->_hoops_RGP, T_ANY_EDGE)) {
			*face = dc->_hoops_GHHHP;
			*edge = dc->_hoops_SPHHP;
		}
		else {
			*face = dc->_hoops_SPHHP;
			*edge = dc->_hoops_GHHHP;
		}
		/* _hoops_HSP _hoops_CGARA _hoops_SSCP _hoops_PSHR _hoops_CSSP _hoops_GAR _hoops_SPPR (_hoops_PRGI _hoops_RPP _hoops_SPPR _hoops_PSIPR) */
	}
	else if (list->type == _hoops_SHGRA) {
#ifndef DISABLE_COLOR_MAPS
		if (BIT(dc->flags, _hoops_CPPHP) && dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR)
			*_hoops_IPHHP = *_hoops_SIPI = *face = *edge = _hoops_CAHSR::_hoops_SAHSR;		/* _hoops_IPIHR _hoops_SCH */
		else {
			_hoops_PCSGA const *			findex = (_hoops_PCSGA const *)list;
			_hoops_CAHHP const &		_hoops_SAHHP = nr->_hoops_ASIR->_hoops_PSIR;
			int								index = (int)(findex->value + 0.5f);

			if (index >= (int)_hoops_SAHHP->length) {
				char			buf[MAX_ERRMSG];

				Sprintf_DD (buf, "The current color map has only %d entries; offset %d was requested.",
							 (int)_hoops_SAHHP->length, index);

				if (_hoops_SRCP->type == _hoops_IRCP)
					_hoops_PHPGR (HEC_COLOR, HES_OUT_OF_RANGE_COLOR_INDEX,
							Sprintf_P (null, "A color-by-index in '%p' is out of range -", _hoops_SRCP),
							buf);
				else
					_hoops_PHPGR (HEC_COLOR, HES_OUT_OF_RANGE_COLOR_INDEX,
							_hoops_GRSPR (null, "A color-by-index in shell or mesh %k is out of range -", _hoops_SRCP),
							buf);
				return false;
			}

			if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
				_hoops_CPHHP = _hoops_CAHSR::_hoops_SAHSR;	/* _hoops_CASI _hoops_SCH _hoops_GGSR */
				_hoops_CPHHP._hoops_PGGCR = _hoops_SAHHP->_hoops_RHHHP + index;
				*_hoops_IPHHP = *_hoops_SIPI = *face = *edge = _hoops_CPHHP;
			}
			else
				*_hoops_IPHHP = *_hoops_SIPI = *face = *edge = _hoops_SAHHP->_hoops_AHHHP[index];
		}
#else
		*_hoops_IPHHP = *_hoops_SIPI = *face = *edge = _hoops_CAHSR::_hoops_SAHSR;	/* _hoops_IPIHR _hoops_SCH */
#endif
	}
	else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) {
		_hoops_AHAH const &				_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;
		float						_hoops_PHHHP;

		_hoops_PHHHP = (float)dc->_hoops_PGCC._hoops_PCHSR - 0.01f;

		if (BIT (_hoops_PHAH.options, _hoops_CHRH)) {
			RGB						tmp = HD_Apply_Color_Effects (*_hoops_PGC, _hoops_PHAH);

			_hoops_CPHHP._hoops_HRIR.r = dc->_hoops_PGCC._hoops_HHHHP[(int)(tmp.red	 * _hoops_PHHHP)];
			_hoops_CPHHP._hoops_HRIR.g = dc->_hoops_PGCC._hoops_HHHHP[(int)(tmp.green * _hoops_PHHHP)];
			_hoops_CPHHP._hoops_HRIR.b = dc->_hoops_PGCC._hoops_HHHHP[(int)(tmp.blue  * _hoops_PHHHP)];
		}
		else {		
			_hoops_CPHHP._hoops_HRIR.r = dc->_hoops_PGCC._hoops_HHHHP[(int)(_hoops_PGC->red	  * _hoops_PHHHP)];
			_hoops_CPHHP._hoops_HRIR.g = dc->_hoops_PGCC._hoops_HHHHP[(int)(_hoops_PGC->green * _hoops_PHHHP)];
			_hoops_CPHHP._hoops_HRIR.b = dc->_hoops_PGCC._hoops_HHHHP[(int)(_hoops_PGC->blue  * _hoops_PHHHP)];
		}

		if (list->type == _hoops_GIGRA &&
			BIT (((_hoops_HCSGA const *)list)->_hoops_ISHIR._hoops_PRGRA, M_TRANSMISSION) &&
			(!BIT(dc->flags, _hoops_GPHHP) || !nr->_hoops_CPP->_hoops_GHSS._hoops_RPHHP))
			_hoops_CPHHP._hoops_HRIR.a = (int)(((_hoops_HCSGA const *)list)->_hoops_ISHIR._hoops_IRIR * _hoops_PHHHP);
		else
			_hoops_CPHHP._hoops_HRIR.a = _hoops_GPGCR;

		*_hoops_IPHHP = *_hoops_SIPI = *face = *edge = _hoops_CPHHP;
	}
	else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
		_hoops_CPHHP = _hoops_CAHSR::_hoops_SAHSR;	/* (_hoops_IRHH _hoops_RCRR _hoops_SCH'_hoops_GRI _hoops_CASI _hoops_PPR _hoops_IHHHP) */

		if (!BIT(dc->flags, _hoops_CPPHP)) {
			if (list->_hoops_PPRPR != null) {	/* _hoops_IRHH _hoops_RCRR _hoops_SR _hoops_HS _hoops_IRS _hoops_HCAGR _hoops_CHHHP _hoops_HAIR */
				_hoops_CPHHP._hoops_PGGCR = ((_hoops_SHHHP const *)list->_hoops_PPRPR)->index;
				if (_hoops_CPHHP._hoops_PGGCR == _hoops_GIHHP)
					_hoops_CPHHP._hoops_PGGCR = dc->_hoops_RIHHP;
			}
		}

		*_hoops_IPHHP = *_hoops_SIPI = *face = *edge = _hoops_CPHHP;
	}
	else /* _hoops_AIHHP */ {
		_hoops_CPHHP = _hoops_CAHSR::_hoops_SAHSR;	/* (_hoops_IRHH _hoops_RCRR _hoops_SCH'_hoops_GRI _hoops_CASI _hoops_PPR _hoops_IHHHP) */
		_hoops_CPHHP._hoops_PIHHP = (_hoops_HIHHP)(_hoops_PGC->_hoops_CPIR() * ((float)dc->_hoops_PGCC._hoops_PCHSR - 0.001f));
		*_hoops_IPHHP = *_hoops_SIPI = *face = *edge = _hoops_CPHHP;
	}

	return true;
}


//_hoops_IIHHP _hoops_SHPR _hoops_CIHHP _hoops_PPRGR _hoops_CRGR _hoops_IRS _hoops_HSP _hoops_HSGP
GLOBAL_FUNCTION void HD_Setup_Screen_Door (
	Net_Rendition alter &		nr)
{
	_hoops_CIGA alter &		_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HHA alter &	mat = _hoops_SIGA->_hoops_CHA;
	_hoops_SIHHP alter *	up;

	if ((up = (_hoops_SIHHP alter *)_hoops_SIGA->_hoops_PGPH) != null) {
		if (_hoops_ISAI (up) == 0) {
			if (up->pattern != null)
				FREE_ARRAY (up->pattern, up->width * up->height,
							unsigned char);

			FREE (up, _hoops_SIHHP);
		}
		_hoops_SIGA->_hoops_PGPH = null;
		_hoops_SIGA->pattern = FP_SOLID;
	}

	if (_hoops_SIGA->_hoops_CHA->_hoops_IRIR != 1.0f) {
		unsigned short					value;
		unsigned short const *			_hoops_HAPAR;
		unsigned char alter *			_hoops_SCGCR;
		int								i;


		ALLOC (up, _hoops_SIHHP);
		_hoops_ICAI (up);
		up->_hoops_CPA = nr->_hoops_SRA->_hoops_GCHHP();
		up->width = up->height = 8;
		up->_hoops_RCHHP = true;
		up->_hoops_ACHHP = UPAT_NO_CONTRAST;
		ALLOC_ARRAY (_hoops_SCGCR, 64, unsigned char);
		up->pattern = _hoops_SCGCR;

		value = (unsigned short)(mat->_hoops_IRIR * 0x0000FFFF);
		_hoops_HAPAR = &HOOPS_READ_ONLY._hoops_CHGCR[0][0];
		for (i=0; i<64; i++) {
			*_hoops_SCGCR++ = (value < *_hoops_HAPAR++) ? 1 : 0;	/* 1 _hoops_HRGR _hoops_ASPA _hoops_IS _hoops_HSGR */
		}
		up->stipple = 64 - (int)(mat->_hoops_IRIR * 64);

		_hoops_SIGA->_hoops_PGPH = up;
		_hoops_SIGA->pattern = FP_USER_DEFINED;

		mat->_hoops_IRIR = 1.0f;
		mat->color[_hoops_PCA] = _hoops_GPSR::_hoops_RPSR;

		if (nr->_hoops_SRA->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) {
			_hoops_SIGA->color._hoops_HRIR.a = _hoops_GPGCR;
			_hoops_SIGA->_hoops_RGIR._hoops_HRIR.a = _hoops_GPGCR;
		}
		else {
			/* _hoops_PA _hoops_SR *_hoops_PAH* _hoops_AA? */
		}
	}

	//_hoops_SR _hoops_PAH'_hoops_RA _hoops_IPIH _hoops_RGHH _hoops_HSP _hoops_PAIA _hoops_SGS _hoops_CHR _hoops_HAGH _hoops_IH _hoops_RIPS _hoops_PPR 
	//_hoops_ISSC _hoops_RSSI, _hoops_HIS _hoops_SAHR _hoops_IPS _hoops_IAPR _hoops_RH _hoops_HSGP _hoops_PPR _hoops_CAHAR _hoops_RH _hoops_PCHHP _hoops_AAPR _hoops_RH _hoops_PSHR
	if (_hoops_SIGA->_hoops_GIA->_hoops_IRIR != 1.0f) {
		_hoops_SIGA->_hoops_GIA->_hoops_IRIR = _hoops_SIGA->_hoops_CHA->_hoops_IRIR;
		_hoops_SIGA->_hoops_GIA->color[_hoops_PCA] = _hoops_SIGA->_hoops_CHA->color[_hoops_PCA];
	}

	nr->_hoops_PSGI &= ~T_FACES;
}


GLOBAL_FUNCTION int HD_Downwind_Color (
	Net_Rendition alter &		nr,
	_hoops_SSGI const *				color,
	_hoops_ACHR					_hoops_RCGC,
	_hoops_PIGRA const *		locks) {
	_hoops_ACSGA const *			list = color->colors;
	_hoops_SSAGR(list);
	Display_Context const *		dc = nr->_hoops_SRA;
	int							_hoops_HCHHP = _hoops_ICHHP;
	float						_hoops_CCHHP = 0.0f;

	if (BIT (_hoops_RCGC, T_FACES))
		_hoops_CCHHP = nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR;


	do {
		Driver_Color			_hoops_IPHHP = _hoops_CAHSR::_hoops_SAHSR,
								_hoops_SIPI = _hoops_CAHSR::_hoops_SAHSR,
								face = _hoops_CAHSR::_hoops_SAHSR,
								edge = _hoops_CAHSR::_hoops_SAHSR;
		RGB						_hoops_PGC = _hoops_GPSR::_hoops_RPSR;
		Color_Object			target = list->_hoops_GHA;

		// _hoops_PAGA: _hoops_RGR _hoops_ICSHR _hoops_RGAR _hoops_SIHR _hoops_RHPP _hoops_PSHA, _hoops_APIR _hoops_SPI _hoops_HRGR _hoops_GIR _hoops_PPGA _hoops_CAPP

		if (list->type != _hoops_GIGRA ||
			ANYBIT (((_hoops_HCSGA const *)list)->_hoops_ISHIR._hoops_PRGRA, M_DIFFUSE)) {
			if (ANYBIT (target, ~(_hoops_IRARA | Color_LIGHTING))) {
				if (!_hoops_HPHHP (nr, list, color->owner,
									  &_hoops_IPHHP, &_hoops_SIPI, &face, &edge,
									  &_hoops_PGC))
					continue;
			}

			if (BIT (target, Color_FRONT) &&
				BIT (_hoops_RCGC, T_FACES)) {
				if (!ANYBIT (locks->_hoops_HAA[_hoops_IAA], M_DIFFUSE|M_TRANSMISSION)) {
					if (nr->_hoops_IHA->color != face) {
						_hoops_CIGA alter &	_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();

						_hoops_SIGA->_hoops_SCHHP = face;
						_hoops_SIGA->color = face;
					}
				}
				else if (!BIT (locks->_hoops_HAA[_hoops_IAA], M_DIFFUSE)) {
					Driver_Color				tmp = face;

					tmp._hoops_HRIR.a = nr->_hoops_IHA->color._hoops_HRIR.a;
					if (nr->_hoops_IHA->color != face) {
						_hoops_CIGA alter &	_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();

						_hoops_SIGA->_hoops_SCHHP = face;
						_hoops_SIGA->color = face;
						_hoops_SIGA->_hoops_GSHHP = face;
						_hoops_SIGA->_hoops_RGIR = face;
					}
				}
				else if (!BIT (locks->_hoops_HAA[_hoops_IAA], M_TRANSMISSION)) {
					Driver_Color				tmp = face;

					if (nr->_hoops_IHA->color._hoops_HRIR.a != tmp._hoops_HRIR.a) {
						_hoops_CIGA alter &	_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();

						_hoops_SIGA->_hoops_SCHHP._hoops_HRIR.a = tmp._hoops_HRIR.a;
						_hoops_SIGA->color._hoops_HRIR.a = tmp._hoops_HRIR.a;
						_hoops_SIGA->_hoops_GSHHP._hoops_HRIR.a = tmp._hoops_HRIR.a;
						_hoops_SIGA->_hoops_RGIR._hoops_HRIR.a = tmp._hoops_HRIR.a;
					}
				}
			}
			if (BIT (target, Color_BACK) &&
				BIT (_hoops_RCGC, T_FACES)) {
				if (!ANYBIT (locks->_hoops_HAA[_hoops_RSHHP], M_DIFFUSE|M_TRANSMISSION)) {
					if (nr->_hoops_IHA->_hoops_RGIR != face) {
						_hoops_CIGA alter &	_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();

						_hoops_SIGA->_hoops_GSHHP = face;
						_hoops_SIGA->_hoops_RGIR = face;
					}
				}
				else if (!BIT (locks->_hoops_HAA[_hoops_RSHHP], M_DIFFUSE)) {
					Driver_Color				tmp = face;

					tmp._hoops_HRIR.a = nr->_hoops_IHA->_hoops_RGIR._hoops_HRIR.a;
					if (nr->_hoops_IHA->_hoops_RGIR != face) {
						_hoops_CIGA alter &	_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();

						_hoops_SIGA->_hoops_GSHHP = face;
						_hoops_SIGA->_hoops_RGIR = face;
					}
				}
				else if (!BIT (locks->_hoops_HAA[_hoops_RSHHP], M_TRANSMISSION)) {
					Driver_Color				tmp = face;

					if (nr->_hoops_IHA->_hoops_RGIR._hoops_HRIR.a != tmp._hoops_HRIR.a) {
						_hoops_CIGA alter &	_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();

						_hoops_SIGA->_hoops_GSHHP._hoops_HRIR.a = tmp._hoops_HRIR.a;
						_hoops_SIGA->_hoops_RGIR._hoops_HRIR.a = tmp._hoops_HRIR.a;
					}
				}
			}


			if (ANYBIT (target, Color_WINDOW|Color_LINE|Color_MARKER|Color_VERTEX|Color_TEXT|Color_EDGE)) {
				if (BIT (target, Color_WINDOW) &&
					// _hoops_PAGA: _hoops_ASHHP _hoops_HAR _hoops_RAICR, _hoops_SCH _hoops_RGAR _hoops_SGI _hoops_PSHHP _hoops_SPHGR, _hoops_HAR _hoops_RH _hoops_IRGH _hoops_SPR
					!BIT (locks->_hoops_HAA[_hoops_HSHHP], M_DIFFUSE)) {
					if (nr->_hoops_ASIR->window.color != _hoops_SIPI) {
						_hoops_ISHHP alter &	_hoops_CSHHP = nr.Modify()->_hoops_ASIR.Modify();

						_hoops_CSHHP->window._hoops_SCHHP = _hoops_SIPI;
						_hoops_CSHHP->window.color = _hoops_SIPI;
						_hoops_CSHHP->window._hoops_PGC = _hoops_PGC;
					}
				}
				if (BIT (target, Color_LINE) &&
					BIT (_hoops_RCGC, T_LINES) &&
					!BIT (locks->_hoops_HAA[_hoops_RPA], M_DIFFUSE)) {
					if (nr->_hoops_AHP->color != _hoops_IPHHP) {
						Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_AHP.Modify();

						_hoops_HC->_hoops_SCHHP = _hoops_IPHHP;
						_hoops_HC->color = _hoops_IPHHP;

						_hoops_HC->_hoops_IHA = null;
						_hoops_HC->_hoops_SSHHP = null;
					}
				}
				if (BIT (target, Color_MARKER) &&
					BIT (_hoops_RCGC, T_MARKERS) &&
					!BIT (locks->_hoops_HAA[_hoops_APA], M_DIFFUSE)) {
					if (nr->_hoops_GSP->color != _hoops_IPHHP) {
						_hoops_ICP alter &	_hoops_CCP = nr.Modify()->_hoops_GSP.Modify();

						_hoops_CCP->_hoops_SCHHP = _hoops_IPHHP;
						_hoops_CCP->color = _hoops_IPHHP;

						_hoops_CCP->_hoops_SSHHP = null;
					}
				}
				if (BIT (target, Color_VERTEX) &&
					BIT (_hoops_RCGC, T_VERTICES) &&
					!BIT (locks->_hoops_HAA[_hoops_PPA], M_DIFFUSE)) {
					if (nr->_hoops_SCP->color != _hoops_IPHHP) {
						_hoops_ICP alter &	_hoops_CCP = nr.Modify()->_hoops_SCP.Modify();

						_hoops_CCP->_hoops_SCHHP = _hoops_IPHHP;
						_hoops_CCP->color = _hoops_IPHHP;

						_hoops_CCP->_hoops_SSHHP = null;
					}
				}
				if (BIT (target, Color_TEXT) &&
					ANYBIT (_hoops_RCGC, T_TEXT|T_STRING_CURSORS) &&
					!BIT (locks->_hoops_HAA[_hoops_GGIHP], M_DIFFUSE)) {
					if (nr->_hoops_SISI->color != _hoops_IPHHP) {
						_hoops_IGCSR alter &		_hoops_HRCIR = nr.Modify()->_hoops_SISI.Modify();

						_hoops_HRCIR->_hoops_SCHHP = _hoops_IPHHP;
						_hoops_HRCIR->color = _hoops_IPHHP;

						_hoops_HRCIR->_hoops_RGIHP = null;
					}
				}

				if (BIT (target, Color_EDGE) &&
					BIT (_hoops_RCGC, T_EDGES) &&
					!BIT (locks->_hoops_HAA[_hoops_SAA], M_DIFFUSE)) {
					if (nr->_hoops_RHP->color != edge) {
						Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_RHP.Modify();

						_hoops_HC->_hoops_SCHHP = edge;
						_hoops_HC->color = edge;

						_hoops_HC->_hoops_IHA = null;
						_hoops_HC->_hoops_SSHHP = null;
					}
				}
			}


			if (ANYBIT(target, _hoops_AGIHP)) {
				if (BIT (target, Color_WINDOW_CONTRAST) &&
					// _hoops_PAGA: _hoops_ASHHP _hoops_HAR _hoops_RAICR, _hoops_SCH _hoops_RGAR _hoops_SGI _hoops_PSHHP _hoops_SPHGR, _hoops_HAR _hoops_RH _hoops_IRGH _hoops_SPR
					!BIT (locks->_hoops_HAA[_hoops_PGIHP], M_DIFFUSE)) {
					if (nr->_hoops_ASIR->window._hoops_HGIHP != _hoops_IPHHP) {
						_hoops_ISHHP alter &	_hoops_CSHHP = nr.Modify()->_hoops_ASIR.Modify();

						_hoops_CSHHP->window._hoops_IGIHP = _hoops_IPHHP;
						_hoops_CSHHP->window._hoops_HGIHP = _hoops_IPHHP;
						_hoops_CSHHP->window._hoops_CGIHP = _hoops_PGC;
					}
				}
				if (BIT (target, _hoops_RRARA) &&
					BIT (_hoops_RCGC, T_FACES) &&
					!BIT (locks->_hoops_HAA[_hoops_SGIHP], M_DIFFUSE)) {
					if (nr->_hoops_IHA->contrast_color != edge) {
						_hoops_CIGA alter &	_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();

						_hoops_SIGA->_hoops_GRIHP = edge;
						_hoops_SIGA->contrast_color = edge;
					}
				}
				if (BIT (target, _hoops_GRARA) &&
					BIT (_hoops_RCGC, T_FACES) &&
					!BIT (locks->_hoops_HAA[_hoops_RRIHP], M_DIFFUSE)) {
					if (nr->_hoops_IHA->_hoops_ARIHP != edge) {
						_hoops_CIGA alter &	_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();

						_hoops_SIGA->_hoops_PRIHP = edge;
						_hoops_SIGA->_hoops_ARIHP = edge;
					}
				}
				if (BIT (target, Color_EDGE_CONTRAST) &&
					BIT (_hoops_RCGC, T_EDGES) &&
					!BIT (locks->_hoops_HAA[_hoops_HRIHP], M_DIFFUSE)) {
					if (nr->_hoops_RHP->contrast_color != edge) {
						Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_RHP.Modify();

						_hoops_HC->_hoops_GRIHP = edge;
						_hoops_HC->contrast_color = edge;

						_hoops_HC->contrast_rendition = null;
					}
				}
				if (BIT (target, Color_LINE_CONTRAST) &&
					BIT (_hoops_RCGC, T_LINES) &&
					!BIT (locks->_hoops_HAA[_hoops_IRIHP], M_DIFFUSE)) {
					if (nr->_hoops_AHP->contrast_color != _hoops_SIPI) {
						Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_AHP.Modify();

						_hoops_HC->_hoops_GRIHP = _hoops_SIPI;
						_hoops_HC->contrast_color = _hoops_SIPI;

						_hoops_HC->contrast_rendition = null;
					}
				}
				if (BIT (target, Color_MARKER_CONTRAST) &&
					BIT (_hoops_RCGC, T_MARKERS) &&
					!BIT (locks->_hoops_HAA[_hoops_CRIHP], M_DIFFUSE)) {
					if (nr->_hoops_GSP->contrast_color != _hoops_SIPI) {
						_hoops_ICP alter &	_hoops_CCP = nr.Modify()->_hoops_GSP.Modify();

						_hoops_CCP->_hoops_GRIHP = _hoops_SIPI;
						_hoops_CCP->contrast_color = _hoops_SIPI;

						_hoops_CCP->contrast_rendition = null;
					}
				}
				if (BIT (target, Color_VERTEX_CONTRAST) &&
					BIT (_hoops_RCGC, T_VERTICES) &&
					!BIT (locks->_hoops_HAA[_hoops_SRIHP], M_DIFFUSE)) {
					if (nr->_hoops_SCP->contrast_color != _hoops_SIPI) {
						_hoops_ICP alter &	_hoops_CCP = nr.Modify()->_hoops_SCP.Modify();

						_hoops_CCP->_hoops_GRIHP = _hoops_SIPI;
						_hoops_CCP->contrast_color = _hoops_SIPI;

						_hoops_CCP->contrast_rendition = null;
					}
				}
				if (BIT (target, Color_TEXT_CONTRAST) &&
					ANYBIT (_hoops_RCGC, T_TEXT|T_STRING_CURSORS) &&
					!BIT (locks->_hoops_HAA[_hoops_GAIHP], M_DIFFUSE)) {
					if (nr->_hoops_SISI->contrast_color != _hoops_SIPI) {
						_hoops_IGCSR alter &		_hoops_HRCIR = nr.Modify()->_hoops_SISI.Modify();

						_hoops_HRCIR->_hoops_GRIHP = _hoops_SIPI;
						_hoops_HRCIR->contrast_color = _hoops_SIPI;

						_hoops_HRCIR->_hoops_RGIHP = null;
					}
				}
			}

			if (ANYBIT(target, _hoops_SGARA|Color_CUT_FACE|Color_CUT_EDGE|_hoops_IRARA|Color_LIGHTING)) {
				if (BIT (target, _hoops_SGARA) && !BIT (locks->_hoops_HAA[_hoops_RAIHP], M_DIFFUSE)) {
					if (nr->_hoops_AAIHP->color != _hoops_IPHHP) {
						_hoops_CIGA alter &	_hoops_SIGA = nr.Modify()->_hoops_AAIHP.Modify();

						_hoops_SIGA->_hoops_SCHHP = _hoops_IPHHP;
						_hoops_SIGA->color = _hoops_IPHHP;
					}
				}

				if (BIT (target, Color_CUT_FACE) && !BIT (locks->_hoops_HAA[_hoops_PAIHP], M_DIFFUSE)) {
					if (nr->_hoops_HAIHP->color != _hoops_IPHHP) {
						_hoops_CIGA alter &	_hoops_SIGA = nr.Modify()->_hoops_HAIHP.Modify();

						_hoops_SIGA->_hoops_SCHHP = _hoops_IPHHP;
						_hoops_SIGA->color = _hoops_IPHHP;
					}
				}
				if (BIT (target, Color_CUT_EDGE) && !BIT (locks->_hoops_HAA[_hoops_IAIHP], M_DIFFUSE)) {
					if (nr->_hoops_CAIHP->color != _hoops_IPHHP) {
						Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_CAIHP.Modify();

						_hoops_HC->_hoops_SCHHP = _hoops_IPHHP;
						_hoops_HC->color = _hoops_IPHHP;

						_hoops_HC->_hoops_SSHHP = null;
						_hoops_HC->_hoops_IHA = null;
					}
				}

				if (BIT (target, _hoops_PRARA) && !BIT (locks->color, _hoops_PRARA)) {
					_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
					RGB							_hoops_HASR;

					if (list->type == _hoops_PPCA) {
						_hoops_APCA const *		normal = (_hoops_APCA const *)list;

						_hoops_HASR  = normal->rgb;
					}
					else if (list->type == _hoops_GIGRA) {
						_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;

						_hoops_HASR = _hoops_ICSGA->_hoops_ISHIR._hoops_CSHR;
					}
#ifndef DISABLE_COLOR_MAPS
					else if (!BIT(dc->flags, _hoops_CPPHP) /* && _hoops_HIGR->_hoops_GPRR == _hoops_SAIHP */) {
						_hoops_PCSGA const *		findex = (_hoops_PCSGA const *)list;
						_hoops_RHAH const	*			_hoops_GPIHP = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;

						if ((int)findex->value >= _hoops_GPIHP->length) {
							HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_COLOR_INDEX,
									  "Ambient color index is out of range");
							_hoops_HASR = _hoops_GPSR::_hoops_RPSR;
						}
						else {
							Named_Material const *	_hoops_ISHIR = _hoops_GPIHP->_hoops_HAA + (int)findex->value;

							_hoops_HASR  = _hoops_ISHIR->_hoops_CSHR ;
						}
					}
#endif
					else
						_hoops_HASR = _hoops_GPSR::_hoops_RPSR;

					if (_hoops_HASR != _hoops_RRGH->_hoops_RPIHP) {
						_hoops_GRGH alter &		_hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();

						_hoops_APIHP->_hoops_HASR = _hoops_APIHP->_hoops_RPIHP = _hoops_HASR;
					}
				}
				if (BIT (target, _hoops_HRARA) && !BIT (locks->color, _hoops_HRARA)) {
					_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
					RGB							_hoops_CASR;

					if (list->type == _hoops_PPCA) {
						_hoops_APCA const *		normal = (_hoops_APCA const *)list;

						_hoops_CASR = normal->rgb;
					}
					else if (list->type == _hoops_GIGRA) {
						_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;

						_hoops_CASR = _hoops_ICSGA->_hoops_ISHIR._hoops_CSHR;
					}
#ifndef DISABLE_COLOR_MAPS
					else if (!BIT(dc->flags, _hoops_CPPHP) /* && _hoops_HIGR->_hoops_GPRR == _hoops_SAIHP */) {
						_hoops_PCSGA const *		findex = (_hoops_PCSGA const *)list;
						_hoops_RHAH const	*_hoops_GPIHP = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;

						if ((int)findex->value >= _hoops_GPIHP->length) {
							HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_COLOR_INDEX,
									  "Ambient color index is out of range");
							_hoops_CASR = _hoops_GPSR::_hoops_RPSR;
						}
						else {
							Named_Material const *	_hoops_ISHIR = _hoops_GPIHP->_hoops_HAA + (int)findex->value;

							_hoops_CASR  = _hoops_ISHIR->_hoops_CSHR;
						}
					}
#endif
					else
						_hoops_CASR = _hoops_GPSR::_hoops_RPSR;

					if (_hoops_CASR != _hoops_RRGH->_hoops_CASR) {
						_hoops_GRGH alter &		_hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();

						_hoops_APIHP->_hoops_CASR = _hoops_APIHP->_hoops_PPIHP = _hoops_CASR;
					}
				}

				if (BIT (target, Color_LIGHTING) && !BIT (locks->color, Color_LIGHTING)) {
					_hoops_GRGH const &	_hoops_RRGH = nr->_hoops_IRR;
					RGB						_hoops_PCP;

					if (list->type == _hoops_PPCA) {
						_hoops_APCA const *		normal = (_hoops_APCA const *)list;

						_hoops_PCP = normal->rgb;
					}
					else if (list->type == _hoops_GIGRA) {
						_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;

						_hoops_PCP = _hoops_ICSGA->_hoops_ISHIR._hoops_CSHR;
					}
	#ifndef DISABLE_COLOR_MAPS
					else if (!BIT(dc->flags, _hoops_CPPHP) /* && _hoops_HIGR->_hoops_GPRR == _hoops_SAIHP */) {
						_hoops_PCSGA const *		findex = (_hoops_PCSGA const *)list;
						_hoops_RHAH const	*	_hoops_GPIHP = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;

						if ((int)findex->value >= _hoops_GPIHP->length) {
							HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_COLOR_INDEX,
									  "Lighting color index is out of range");
							_hoops_PCP = _hoops_GPSR::_hoops_RPSR;
						}
						else {
							Named_Material const *	_hoops_ISHIR = _hoops_GPIHP->_hoops_HAA + (int)findex->value;

							_hoops_PCP = _hoops_ISHIR->_hoops_CSHR;
						}
					}
	#endif
					else
						_hoops_PCP = _hoops_GPSR::_hoops_RPSR;

					if (_hoops_PCP != _hoops_RRGH->_hoops_PCP) {
						_hoops_GRGH alter &		_hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();

						_hoops_APIHP->_hoops_PCP = _hoops_PCP;
					}
				}

			}
		}
		else if (BIT (((_hoops_HCSGA const *)list)->_hoops_ISHIR._hoops_PRGRA, M_TRANSMISSION) &&
				 dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) {
			// _hoops_PCCP _hoops_APPCR _hoops_CSPP _hoops_RPP _hoops_RH _hoops_RRGR _hoops_ARRS _hoops_SGS _hoops_SIHR _hoops_SAHR _hoops_HPIHP

			if (ANYBIT (target, ~(_hoops_IRARA | Color_LIGHTING))) {
				if (!_hoops_HPHHP (nr, list, color->owner,
									  &_hoops_IPHHP, &_hoops_SIPI, &face, &edge,
									  &_hoops_PGC))
					continue;
			}

			if (BIT (target, Color_FRONT) &&
				BIT (_hoops_RCGC, T_FACES)) {
				if (!BIT (locks->_hoops_HAA[_hoops_IAA], M_TRANSMISSION)) {
					if (nr->_hoops_IHA->color._hoops_HRIR.a != face._hoops_HRIR.a) {
						_hoops_CIGA alter &	_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();
						_hoops_PPHHP (face, _hoops_SIGA->_hoops_SCHHP);
						_hoops_PPHHP (face, _hoops_SIGA->color);
					}
				}
			}
			if (BIT (target, Color_BACK) &&
				BIT (_hoops_RCGC, T_FACES)) {
				if (!BIT (locks->_hoops_HAA[_hoops_RSHHP], M_TRANSMISSION)) {
					if (nr->_hoops_IHA->_hoops_RGIR._hoops_HRIR.a != face._hoops_HRIR.a) {
						_hoops_CIGA alter &	_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();
						_hoops_PPHHP (face, _hoops_SIGA->_hoops_GSHHP);
						_hoops_PPHHP (face, _hoops_SIGA->_hoops_RGIR);
					}
				}
			}

			if (ANYBIT (target, Color_LINE|Color_MARKER|Color_VERTEX|Color_TEXT|Color_EDGE)) {
				if (BIT (target, Color_LINE) &&
					BIT (_hoops_RCGC, T_LINES) &&
					!BIT (locks->_hoops_HAA[_hoops_RPA], M_TRANSMISSION)) {
					if (nr->_hoops_AHP->color._hoops_HRIR.a != _hoops_IPHHP._hoops_HRIR.a) {
						Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_AHP.Modify();
						_hoops_PPHHP (_hoops_IPHHP, _hoops_HC->_hoops_SCHHP);
						_hoops_PPHHP (_hoops_IPHHP, _hoops_HC->color);

						_hoops_HC->_hoops_IHA = null;
						_hoops_HC->_hoops_SSHHP = null;
					}
				}
				if (BIT (target, Color_MARKER) &&
					BIT (_hoops_RCGC, T_MARKERS) &&
					!BIT (locks->_hoops_HAA[_hoops_APA], M_TRANSMISSION)) {
					if (nr->_hoops_GSP->color._hoops_HRIR.a != _hoops_IPHHP._hoops_HRIR.a) {
						_hoops_ICP alter &	_hoops_CCP = nr.Modify()->_hoops_GSP.Modify();
						_hoops_PPHHP (_hoops_IPHHP, _hoops_CCP->_hoops_SCHHP);
						_hoops_PPHHP (_hoops_IPHHP, _hoops_CCP->color);

						_hoops_CCP->_hoops_SSHHP = null;
					}
				}
				if (BIT (target, Color_VERTEX) &&
					BIT (_hoops_RCGC, T_VERTICES) &&
					!BIT (locks->_hoops_HAA[_hoops_PPA], M_TRANSMISSION)) {
					if (nr->_hoops_SCP->color._hoops_HRIR.a != _hoops_IPHHP._hoops_HRIR.a) {
						_hoops_ICP alter &	_hoops_CCP = nr.Modify()->_hoops_SCP.Modify();
						_hoops_PPHHP (_hoops_IPHHP, _hoops_CCP->_hoops_SCHHP);
						_hoops_PPHHP (_hoops_IPHHP, _hoops_CCP->color);

						_hoops_CCP->_hoops_SSHHP = null;
					}
				}
				if (BIT (target, Color_TEXT) &&
					ANYBIT (_hoops_RCGC, T_TEXT|T_STRING_CURSORS) &&
					!BIT (locks->_hoops_HAA[_hoops_GGIHP], M_TRANSMISSION)) {
					if (nr->_hoops_SISI->color._hoops_HRIR.a != _hoops_IPHHP._hoops_HRIR.a) {
						_hoops_IGCSR alter &		_hoops_HRCIR = nr.Modify()->_hoops_SISI.Modify();
						_hoops_PPHHP (_hoops_IPHHP, _hoops_HRCIR->_hoops_SCHHP);
						_hoops_PPHHP (_hoops_IPHHP, _hoops_HRCIR->color);

						_hoops_HRCIR->_hoops_RGIHP = null;
					}
				}

				if (BIT (target, Color_EDGE) &&
					BIT (_hoops_RCGC, T_EDGES) &&
					!BIT (locks->_hoops_HAA[_hoops_SAA], M_TRANSMISSION)) {
					if (nr->_hoops_RHP->color._hoops_HRIR.a != edge._hoops_HRIR.a) {
						Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_RHP.Modify();
						_hoops_PPHHP (edge, _hoops_HC->_hoops_SCHHP);
						_hoops_PPHHP (edge, _hoops_HC->color);

						_hoops_HC->_hoops_IHA = null;
						_hoops_HC->_hoops_SSHHP = null;
					}
				}
			}

			if (ANYBIT(target, _hoops_AGIHP)) {
				if (BIT (target, Color_FACE_CONTRAST) &&
					BIT (_hoops_RCGC, T_FACES) &&
					!BIT (locks->_hoops_HAA[_hoops_SGIHP], M_TRANSMISSION)) {
					if (nr->_hoops_IHA->contrast_color._hoops_HRIR.a != edge._hoops_HRIR.a) {
						_hoops_CIGA alter &	_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();
						_hoops_PPHHP (edge, _hoops_SIGA->_hoops_GRIHP);
						_hoops_PPHHP (edge, _hoops_SIGA->contrast_color);
					}
				}
				if (BIT (target, Color_EDGE_CONTRAST) &&
					BIT (_hoops_RCGC, T_EDGES) &&
					!BIT (locks->_hoops_HAA[_hoops_HRIHP], M_TRANSMISSION)) {
					if (nr->_hoops_RHP->contrast_color._hoops_HRIR.a != edge._hoops_HRIR.a) {
						Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_RHP.Modify();
						_hoops_PPHHP (edge, _hoops_HC->_hoops_GRIHP);
						_hoops_PPHHP (edge, _hoops_HC->contrast_color);

						_hoops_HC->contrast_rendition = null;
					}
				}
				if (BIT (target, Color_LINE_CONTRAST) &&
					BIT (_hoops_RCGC, T_LINES) &&
					!BIT (locks->_hoops_HAA[_hoops_IRIHP], M_TRANSMISSION)) {
					if (nr->_hoops_AHP->contrast_color._hoops_HRIR.a != _hoops_SIPI._hoops_HRIR.a) {
						Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_AHP.Modify();
						_hoops_PPHHP (_hoops_SIPI, _hoops_HC->_hoops_GRIHP);
						_hoops_PPHHP (_hoops_SIPI, _hoops_HC->contrast_color);

						_hoops_HC->contrast_rendition = null;
					}
				}
				if (BIT (target, Color_MARKER_CONTRAST) &&
					BIT (_hoops_RCGC, T_MARKERS) &&
					!BIT (locks->_hoops_HAA[_hoops_CRIHP], M_TRANSMISSION)) {
					if (nr->_hoops_GSP->contrast_color._hoops_HRIR.a != _hoops_SIPI._hoops_HRIR.a) {
						_hoops_ICP alter &	_hoops_CCP = nr.Modify()->_hoops_GSP.Modify();
						_hoops_PPHHP (_hoops_SIPI, _hoops_CCP->_hoops_GRIHP);
						_hoops_PPHHP (_hoops_SIPI, _hoops_CCP->contrast_color);

						_hoops_CCP->contrast_rendition = null;
					}
				}
				if (BIT (target, Color_VERTEX_CONTRAST) &&
					BIT (_hoops_RCGC, T_VERTICES) &&
					!BIT (locks->_hoops_HAA[_hoops_SRIHP], M_TRANSMISSION)) {
					if (nr->_hoops_SCP->contrast_color._hoops_HRIR.a != _hoops_SIPI._hoops_HRIR.a) {
						_hoops_ICP alter &	_hoops_CCP = nr.Modify()->_hoops_SCP.Modify();
						_hoops_PPHHP (_hoops_SIPI, _hoops_CCP->_hoops_GRIHP);
						_hoops_PPHHP (_hoops_SIPI, _hoops_CCP->contrast_color);

						_hoops_CCP->contrast_rendition = null;
					}
				}
				if (BIT (target, Color_TEXT_CONTRAST) &&
					ANYBIT (_hoops_RCGC, T_TEXT|T_STRING_CURSORS) &&
					!BIT (locks->_hoops_HAA[_hoops_GAIHP], M_TRANSMISSION)) {
					if (nr->_hoops_SISI->contrast_color._hoops_HRIR.a != _hoops_SIPI._hoops_HRIR.a) {
						_hoops_IGCSR alter &		_hoops_HRCIR = nr.Modify()->_hoops_SISI.Modify();
						_hoops_PPHHP (_hoops_SIPI, _hoops_HRCIR->_hoops_GRIHP);
						_hoops_PPHHP (_hoops_SIPI, _hoops_HRCIR->contrast_color);

						_hoops_HRCIR->_hoops_RGIHP = null;
					}
				}
			}

			if (ANYBIT(target, _hoops_SGARA|Color_CUT_FACE|Color_CUT_EDGE)) {
				if (BIT (target, _hoops_SGARA) && !BIT (locks->_hoops_HAA[_hoops_RAIHP], M_TRANSMISSION)) {
					if (nr->_hoops_AAIHP->color._hoops_HRIR.a != _hoops_IPHHP._hoops_HRIR.a) {
						_hoops_CIGA alter &	_hoops_SIGA = nr.Modify()->_hoops_AAIHP.Modify();
						_hoops_PPHHP (_hoops_IPHHP, _hoops_SIGA->_hoops_SCHHP);
						_hoops_PPHHP (_hoops_IPHHP, _hoops_SIGA->color);
					}
				}

				if (BIT (target, Color_CUT_FACE) && !BIT (locks->_hoops_HAA[_hoops_PAIHP], M_TRANSMISSION)) {
					if (nr->_hoops_HAIHP->color._hoops_HRIR.a != _hoops_IPHHP._hoops_HRIR.a) {
						_hoops_CIGA alter &	_hoops_SIGA = nr.Modify()->_hoops_HAIHP.Modify();
						_hoops_PPHHP (_hoops_IPHHP, _hoops_SIGA->_hoops_SCHHP);
						_hoops_PPHHP (_hoops_IPHHP, _hoops_SIGA->color);
					}
				}
				if (BIT (target, Color_CUT_EDGE) && !BIT (locks->_hoops_HAA[_hoops_IAIHP], M_TRANSMISSION)) {
					if (nr->_hoops_CAIHP->color._hoops_HRIR.a != _hoops_IPHHP._hoops_HRIR.a) {
						Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_CAIHP.Modify();
						_hoops_PPHHP (_hoops_IPHHP, _hoops_HC->_hoops_SCHHP);
						_hoops_PPHHP (_hoops_IPHHP, _hoops_HC->color);

						_hoops_HC->_hoops_IHA = null;
						_hoops_HC->_hoops_SSHHP = null;
					}
				}
			}
		}

		// _hoops_PPR _hoops_HA _hoops_RH _hoops_IHIR _hoops_GCHR
		_hoops_SSAGR(&_hoops_RCGC);
		_hoops_SSAGR(list->next);

		_hoops_CIGA const &			_hoops_SIGA = nr->_hoops_IHA;
		_hoops_HHA				mat;

		if (ANYBIT (target, Color_FACE) && ANYBIT (_hoops_RCGC, T_FACES | T_IMAGES)) {
			// _hoops_GRHP _hoops_RIPS & _hoops_ISSC _hoops_GIRP _hoops_RPP _hoops_SSRR
			if (ALLBITS (target, Color_FACE) &&
				_hoops_SIGA->_hoops_CHA == _hoops_SIGA->_hoops_GIA &&
				locks->_hoops_HAA[_hoops_IAA] == locks->_hoops_HAA[_hoops_RSHHP]) {
				mat = _hoops_CRHHP (nr, _hoops_SIGA->_hoops_CHA,
										 list, locks->_hoops_HAA[_hoops_IAA],
										 ANYBIT (nr->_hoops_RGP, T_ANY_EDGE));

				if (mat != _hoops_SIGA->_hoops_CHA) {
					if (mat->_hoops_IRIR != _hoops_SIGA->_hoops_CHA->_hoops_IRIR)
						_hoops_HCHHP |= _hoops_IPIHP;

					_hoops_CIGA alter &	_hoops_CPIHP = nr.Modify()->_hoops_IHA.Modify();

					_hoops_CPIHP->_hoops_CHA = mat;
					_hoops_CPIHP->_hoops_GIA = mat;

					if (_hoops_RIRGR(mat))
						nr->_hoops_PSGI |= (T_FACES|T_IMAGES);
					else
						nr->_hoops_PSGI &= ~(T_FACES|T_IMAGES);
				}
			}
			else {
				bool					_hoops_CCCIR = false;

				if (BIT (target, Color_FRONT)) {
					mat = _hoops_CRHHP (nr, _hoops_SIGA->_hoops_CHA,
											 list, locks->_hoops_HAA[_hoops_IAA],
											 ANYBIT (nr->_hoops_RGP, T_ANY_EDGE));

					if (mat != _hoops_SIGA->_hoops_CHA) {
						if (mat->_hoops_IRIR != _hoops_SIGA->_hoops_CHA->_hoops_IRIR)
							_hoops_HCHHP |= _hoops_IPIHP;

						nr.Modify()->_hoops_IHA.Modify()->_hoops_CHA = mat;
						_hoops_CCCIR = true;
					}
				}

				if (BIT (target, Color_BACK)) {
					mat = _hoops_CRHHP (nr, _hoops_SIGA->_hoops_GIA,
											 list, locks->_hoops_HAA[_hoops_RSHHP],
											 ANYBIT (nr->_hoops_RGP, T_ANY_EDGE));

					if (mat != _hoops_SIGA->_hoops_GIA) {
						if (mat->_hoops_IRIR != _hoops_SIGA->_hoops_GIA->_hoops_IRIR)
							_hoops_HCHHP |= _hoops_IPIHP;

						nr.Modify()->_hoops_IHA.Modify()->_hoops_GIA = mat;
						_hoops_CCCIR = true;
					}
				}

				if (_hoops_CCCIR) {
					if (_hoops_RIRGR(nr->_hoops_IHA->_hoops_CHA) ||
						_hoops_RIRGR(nr->_hoops_IHA->_hoops_GIA))
						nr->_hoops_PSGI |= (T_FACES|T_IMAGES);
					else
						nr->_hoops_PSGI &= ~(T_FACES|T_IMAGES);
				}
			}
		}

		if (ANYBIT (target, Color_LINE|Color_EDGE|Color_MARKER|Color_VERTEX|Color_TEXT)) {
			if (BIT (target, Color_LINE) && BIT (_hoops_RCGC, T_LINES)) {
				Line_Rendition const &			_hoops_HC = nr->_hoops_AHP;

				mat = _hoops_CRHHP (nr, _hoops_HC->_hoops_CHA,
										 list, locks->_hoops_HAA[_hoops_RPA], false);

				if (mat != _hoops_HC->_hoops_CHA) {
					nr.Modify()->_hoops_AHP.Modify()->_hoops_CHA = mat;

					if (mat->_hoops_IRIR != 1.0f)
						nr->_hoops_PSGI |= T_LINES;
					else
						nr->_hoops_PSGI &= ~T_LINES;
				}
			}

			if (BIT (target, Color_EDGE) && BIT (_hoops_RCGC, T_EDGES)) {
				Line_Rendition const &			_hoops_GHP = nr->_hoops_RHP;

				mat = _hoops_CRHHP (nr, _hoops_GHP->_hoops_CHA,
										 list, locks->_hoops_HAA[_hoops_SAA], false);

				if (mat != _hoops_GHP->_hoops_CHA) {
					nr.Modify()->_hoops_RHP.Modify()->_hoops_CHA = mat;

					if (mat->_hoops_IRIR != 1.0f)
						nr->_hoops_PSGI |= T_EDGES;
					else
						nr->_hoops_PSGI &= ~T_EDGES;
				}
			}

			if (BIT (target, Color_MARKER) && BIT (_hoops_RCGC, T_MARKERS)) {
				_hoops_ICP const &		_hoops_CCP = nr->_hoops_GSP;

				mat = _hoops_CRHHP (nr, _hoops_CCP->_hoops_CHA,
										 list, locks->_hoops_HAA[_hoops_APA], false);

				if (mat != _hoops_CCP->_hoops_CHA) {
					nr.Modify()->_hoops_GSP.Modify()->_hoops_CHA = mat;

					if (mat->_hoops_IRIR != 1.0f)
						nr->_hoops_PSGI |= T_MARKERS;
					else
						nr->_hoops_PSGI &= ~T_MARKERS;
				}
			}

			if (BIT (target, Color_VERTEX) && BIT (_hoops_RCGC, T_VERTICES)) {
				_hoops_ICP const &		_hoops_CCP = nr->_hoops_SCP;

				mat = _hoops_CRHHP (nr, _hoops_CCP->_hoops_CHA,
										 list, locks->_hoops_HAA[_hoops_PPA], false);

				if (mat != _hoops_CCP->_hoops_CHA) {
					nr.Modify()->_hoops_SCP.Modify()->_hoops_CHA = mat;

					if (mat->_hoops_IRIR != 1.0f)
						nr->_hoops_PSGI |= T_VERTICES;
					else
						nr->_hoops_PSGI &= ~T_VERTICES;
				}
			}

			if (BIT (target, Color_TEXT) && ANYBIT (_hoops_RCGC, T_TEXT|T_STRING_CURSORS)) {
				_hoops_IGCSR const &			_hoops_HRCIR = nr->_hoops_SISI;

				mat = _hoops_CRHHP (nr, _hoops_HRCIR->_hoops_CHA,
										 list, locks->_hoops_HAA[_hoops_GGIHP], false);

				if (mat != _hoops_HRCIR->_hoops_CHA) {
					nr.Modify()->_hoops_SISI.Modify()->_hoops_CHA = mat;

					if (mat->_hoops_IRIR != 1.0f)
						nr->_hoops_PSGI |= (T_TEXT|T_STRING_CURSORS);
					else
						nr->_hoops_PSGI &= ~(T_TEXT|T_STRING_CURSORS);
				}
			}
		}


		if (ANYBIT (target, Color_CUT_EDGE|Color_CUT_FACE)) {
			bool _hoops_CCCIR = false;
			if (BIT (target, Color_CUT_EDGE)) {
				Line_Rendition const &			_hoops_GHP = nr->_hoops_CAIHP;

				mat = _hoops_CRHHP (nr, _hoops_GHP->_hoops_CHA,
										 list, locks->_hoops_HAA[_hoops_IAIHP], false);

				if (mat != _hoops_GHP->_hoops_CHA) {
					nr.Modify()->_hoops_CAIHP.Modify()->_hoops_CHA = mat;
					_hoops_CCCIR = true;
				}
			}
			if (BIT (target, Color_CUT_FACE)) {
				_hoops_CIGA const &			_hoops_SPIHP = nr->_hoops_HAIHP;

				mat = _hoops_CRHHP (nr, _hoops_SPIHP->_hoops_CHA,
										 list, locks->_hoops_HAA[_hoops_PAIHP],
										 ANYBIT (nr->_hoops_IRR->_hoops_GHIHP, T_ANY_EDGE));

				if (mat != _hoops_SPIHP->_hoops_CHA) {
					nr.Modify()->_hoops_HAIHP.Modify()->_hoops_CHA = mat;
					_hoops_CCCIR = true;
				}
			}

			if (_hoops_CCCIR) {
				if (nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR != 1.0f ||
					nr->_hoops_IHA->_hoops_GIA->_hoops_IRIR != 1.0f)
					nr->_hoops_PSGI |= T_CUT_GEOMETRY;
				else
					nr->_hoops_PSGI &= ~T_CUT_GEOMETRY;
			}
		}


		if (BIT (target, Color_WINDOW)) {	// _hoops_PAGA: _hoops_ASHHP _hoops_HAR _hoops_RAICR
			Named_Material const *			_hoops_RGHHP = null;

			if (list->type != _hoops_PPCA) {
				if (list->type != _hoops_SHGRA) {
					_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;

					_hoops_RGHHP = &_hoops_ICSGA->_hoops_ISHIR;
				}
#ifndef DISABLE_COLOR_MAPS
				else {
					_hoops_PCSGA const *			findex = (_hoops_PCSGA const *)list;
					_hoops_CAHHP const &		_hoops_SAHHP = nr->_hoops_ASIR->_hoops_PSIR;
					int								index = (int)(findex->value + 0.5f);

					if (index >= (int)_hoops_SAHHP->length) index = 0;

					_hoops_RGHHP = &_hoops_SAHHP->_hoops_CSIR->_hoops_HAA[index];
					if (_hoops_RGHHP == null)
						/*
						 * _hoops_HGI _hoops_AGSR _hoops_SGS _hoops_AICRR _hoops_ARP _hoops_IRS _hoops_HAIR _hoops_HPP _hoops_CIHA
						 * _hoops_HIH _hoops_SSAS _hoops_HAR _hoops_HGSR _hoops_IRS _hoops_HAIR _hoops_ARCR
						 */
						 HE_WARNING (HEC_COLOR_MAP, HES_REQUIRES_COLOR_MAP,
									 "Set Color by Index with No Color Map Set");
				}
#endif

#ifndef DISABLE_TEXTURING
				_hoops_ISHHP alter &	_hoops_RHIHP = nr.Modify()->_hoops_ASIR.Modify();

				if (_hoops_RHIHP->window.texture != null)
					_hoops_HPRH (_hoops_RHIHP->window.texture);
				_hoops_RHIHP->window.texture = null;

				if (_hoops_RGHHP != null &&
					_hoops_RGHHP->_hoops_SCA != null) {
					_hoops_RHIHP->window.texture = _hoops_RGHHP->_hoops_SCA->texture;
					_hoops_PRRH (_hoops_RHIHP->window.texture);
				}
#endif
			}
			else if (nr->_hoops_ASIR->window.texture != null) {
				_hoops_ISHHP alter &	_hoops_RHIHP = nr.Modify()->_hoops_ASIR.Modify();

				_hoops_HPRH (_hoops_RHIHP->window.texture);
				_hoops_RHIHP->window.texture = null;
			}
		}
	} while ((list = list->next) != null);

	if (dc->_hoops_APHHP == null) {
		if (ANYBIT (_hoops_RCGC, nr->_hoops_PSGI)) {
			switch (nr->_hoops_CPP->_hoops_PRH.style) {
				case _hoops_GCPI: {
					if (!BIT(nr->current, _hoops_AHIHP))
						nr.Modify()->current |= _hoops_AHIHP;
				}	_hoops_HHHI;

				case Transparency_STYLE_BLENDING: {
					if (!BIT(nr->_hoops_RCSHR, _hoops_AHIHP))
						nr.Modify()->_hoops_RCSHR |= _hoops_AHIHP;
				}	_hoops_HHHI;

				case _hoops_AIII: {
				}	break;
			}
		}
		else {
			switch (nr->_hoops_CPP->_hoops_PRH.style) {
				case _hoops_GCPI: {
					if (BIT(nr->current, _hoops_AHIHP))
						nr.Modify()->current &= ~_hoops_AHIHP;
				}	_hoops_HHHI;

				case Transparency_STYLE_BLENDING: {
					if (BIT(nr->_hoops_RCSHR, _hoops_AHIHP))
						nr.Modify()->_hoops_RCSHR &= ~_hoops_AHIHP;
				}	_hoops_HHHI;

				case _hoops_AIII: {
				}	break;
			}
		}

		if (BIT (_hoops_RCGC, T_FACES) &&
			nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR != _hoops_CCHHP &&
			nr->_hoops_CPP->_hoops_PRH.style == _hoops_GCPI) {
			nr.Modify();
			HD_Setup_Screen_Door (nr);
		}
	}

	if (nr->_hoops_IRR->_hoops_SRI == _hoops_SICI) {
		_hoops_HCHHP |= _hoops_PHIHP;

		/* _hoops_IHSP _hoops_RGAR _hoops_SIGR _hoops_RHSP _hoops_HSCH _hoops_HSP _hoops_RIH */
		if (dc->_hoops_SHCI() != _hoops_GICI) {
			if (BIT (nr->_hoops_RCSHR, _hoops_AHIHP))
				nr.Modify()->_hoops_RCSHR &= ~_hoops_AHIHP;
		}
	}
	else if (BIT(nr->_hoops_ARA->_hoops_IHRH.options, _hoops_CHRH))
		_hoops_HCHHP |= _hoops_HHIHP;	

	if (ANYBIT(nr->flags, _hoops_HCHHP))
		nr.Modify()->flags &= ~_hoops_HCHHP;

	return _hoops_HCHHP;
}

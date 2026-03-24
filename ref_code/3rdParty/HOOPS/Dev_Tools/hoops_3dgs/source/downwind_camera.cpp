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
 * $Id: obf_tmp.txt 1.102 2010-10-27 00:51:29 covey Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"

local void _hoops_GPPHP (
	Display_Context const *		dc,
	_hoops_HHRA const *				_hoops_SPH,
	_hoops_PC alter &		_hoops_RPPHP,
	_hoops_AS const *		_hoops_APPHP) {
	_hoops_AS alter *		light;

	do {
		POOL_ALLOC (light, _hoops_AS, dc->memory_pool);
		_hoops_RSAI (_hoops_APPHP, _hoops_AS, light);

		if (light->count != 0) {	/* _hoops_ACAHP _hoops_IPS _hoops_RSSA */
			Point* _hoops_PPPHP = (Point*)(light->points);
			_hoops_HAHSA(_hoops_APPHP->points, light->count, Point, _hoops_PPPHP, dc->memory_pool);
			light->points = _hoops_PPPHP;
		}

		light->next = _hoops_RPPHP->_hoops_CGR;
		_hoops_RPPHP->_hoops_CGR = light;

		light->_hoops_ARSR.x = light->direction.x - _hoops_SPH->_hoops_IIPCR.x;
		light->_hoops_ARSR.y = light->direction.y - _hoops_SPH->_hoops_IIPCR.y;
		light->_hoops_ARSR.z = light->direction.z - _hoops_SPH->_hoops_IIPCR.z;
		HI_Normalize (&light->_hoops_ARSR);
	} while ((_hoops_APPHP = _hoops_APPHP->next) != null);
}

GLOBAL_FUNCTION void HD_Downwind_Camera (
	Net_Rendition alter &		nr,
	Attribute const *			_hoops_ASGPR) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_HHRA const *				_hoops_SPH = (_hoops_HHRA const *)_hoops_ASGPR;
	_hoops_HHCR			_hoops_IHCR;
	_hoops_HHRA const *				_hoops_PRGSA;
	float						_hoops_CHHCR = 0.0f;
	float						_hoops_HPPHP;

	if (_hoops_SPH->projection == _hoops_GHH &&
		(BIT(dc->_hoops_PGCC.flags, _hoops_IPPHP) ||
		 BIT(dc->flags, _hoops_CPPHP))) {
		/* _hoops_GA'_hoops_RA _hoops_SHAC _hoops_SPPHP _hoops_SARA _hoops_RPP _hoops_SR _hoops_PAH'_hoops_RA _hoops_AA _hoops_SCH, _hoops_HIH _hoops_PHHR _hoops_IAISR
		   _hoops_RPP _hoops_GHPHP _hoops_GGHC _hoops_SR _hoops_PAHH _hoops_GA'_hoops_RA _hoops_ACPA _hoops_GAPR... */
		switch (nr->transform_rendition->_hoops_RHPHP) {
			case _hoops_AHPHP:
					_hoops_CHHCR = 0.0f;
					break;
			case _hoops_PHPHP:
					_hoops_CHHCR = -nr->transform_rendition->_hoops_ACSRP;
					break;
			case _hoops_HHPHP:
					_hoops_CHHCR =  nr->transform_rendition->_hoops_ACSRP;
					break;
		}
	}

	/* _hoops_SR'_hoops_GCPP _hoops_SHR _hoops_RRP _hoops_RH _hoops_RSGA */
	if (_hoops_SPH->_hoops_SRIR == 0.0f ||		/* _hoops_AHCI _hoops_SARA? */
		!HI_Camera_To_Transform ((_hoops_HHRA alter *)_hoops_ASGPR, _hoops_CHHCR)) /*_hoops_HGPSA _hoops_HIIC*/
		return;

	_hoops_IHCR = nr.Modify()->transform_rendition.Modify();

	/* _hoops_RHRIR _hoops_ARI, _hoops_GHCA _hoops_SHH _hoops_RH _hoops_PSHR _hoops_SARA _hoops_PPR _hoops_SR _hoops_CHR _hoops_SAHR _hoops_IHPHP _hoops_IRICR */
	if ((_hoops_PRGSA = _hoops_IHCR->_hoops_SPH) != _hoops_SPH) {
		_hoops_IHCR->_hoops_SPH = _hoops_SPH;
		_hoops_PRRH (_hoops_IHCR->_hoops_SPH);
		// _hoops_GII _hoops_CHPHP _hoops_GRS _hoops_SHH _hoops_SHPHP _hoops_SPHR, _hoops_GAR _hoops_SR _hoops_HHGC _hoops_IS _hoops_PCR _hoops_SCH _hoops_ACSRR _hoops_RH _hoops_CCAH
	}

	_hoops_HPPHP = *_hoops_IHCR->_hoops_SPH->_hoops_SIPCR;

	if (_hoops_HPPHP > 0.0f)
		_hoops_IHCR->_hoops_CHCR = _hoops_HPPHP;
	else if (_hoops_HPPHP < 0.0f)
		_hoops_IHCR->_hoops_CHCR = -_hoops_HPPHP;
	else
		_hoops_IHCR->_hoops_CHCR = Abs(_hoops_GIPHP);

	if (_hoops_IHCR->_hoops_CHCR < 1.0e-5f)
		_hoops_IHCR->_hoops_CHCR = 1.0e-5f;

	_hoops_IHCR->_hoops_RIPHP = 1.0f;

	if (!BIT (nr->transform_rendition->flags, _hoops_AIPHP)) {
		/* _hoops_PSP _hoops_PRGIA; _hoops_SAHR _hoops_RH _hoops_SARA _hoops_PPR _hoops_SHPR */
		HD_Redo_Screen (nr, &((_hoops_HHRA alter *)_hoops_IHCR->_hoops_SPH)->_hoops_GRCC);
	}
	else {
		_hoops_HRPA						_hoops_PIPHP;

		HI_Multiply_Matrices (&_hoops_IHCR->_hoops_IPH->data,
							  &_hoops_IHCR->_hoops_SPH->_hoops_GRCC,
							  &_hoops_PIPHP);

		HD_Redo_Screen (nr, &_hoops_PIPHP);
	}

	float	width = nr->_hoops_SAIR->_hoops_PHRA.right - nr->_hoops_SAIR->_hoops_PHRA.left;
	_hoops_IHCR->_hoops_HIPHP = width / _hoops_IHCR->_hoops_SPH->_hoops_ISPA;
	if (width > 0.0f)
		_hoops_IHCR->_hoops_IIPHP = _hoops_IHCR->_hoops_SPH->_hoops_ISPA / width;
	else
		_hoops_IHCR->_hoops_IIPHP = 1.0e9f;

	if (_hoops_IHCR->_hoops_HGSC == _hoops_CIPHP ||
		_hoops_IHCR->_hoops_HGSC == _hoops_SIPHP /* (_hoops_PAHA'_hoops_RA _hoops_IHPS) */) {
		/* _hoops_SHSP _hoops_SCH _hoops_SHH */
	}
	else if (_hoops_SPH->projection == _hoops_GHH) {
		if (_hoops_PGSC (_hoops_IHCR->_hoops_HGSC))
			_hoops_IHCR->_hoops_HGSC = _hoops_GCPHP;
		else
			_hoops_IHCR->_hoops_HGSC = _hoops_RCPHP;
	}
	else {		/* _hoops_RRP 3x2 _hoops_HAH!! */
		if (_hoops_PGSC (_hoops_IHCR->_hoops_HGSC))
			_hoops_IHCR->_hoops_HGSC = _hoops_ACPHP;
		else
			_hoops_IHCR->_hoops_HGSC = _hoops_PCPHP;
	}

	((_hoops_SGCC alter &)_hoops_IHCR->matrix)->data.flags &= ~_hoops_HASA;

	_hoops_IHCR->flags &= ~(_hoops_IGCC |
				   _hoops_HCPHP  |
				   _hoops_ICPHP);

	if (nr->_hoops_CPP->_hoops_PRIGA._hoops_CCPHP &&
		(_hoops_PRGSA == null ||
		 _hoops_IHCR->_hoops_SPH->_hoops_ISPA  != _hoops_PRGSA->_hoops_ISPA ||
		 _hoops_IHCR->_hoops_SPH->_hoops_SSPA != _hoops_PRGSA->_hoops_SSPA)) {
		_hoops_GCIR alter & 	_hoops_SCPHP = nr->_hoops_CPP.Modify();

		_hoops_SCPHP->_hoops_PRIGA.tolerance = _hoops_SCPHP->_hoops_PRIGA._hoops_GSPHP *
				_hoops_IAAA (_hoops_IHCR->_hoops_SPH->_hoops_ISPA, _hoops_IHCR->_hoops_SPH->_hoops_SSPA);
	}

	if (BIT (_hoops_IHCR->flags, _hoops_HHGGA))
		HD_Set_DC_Cutting_Planes (nr);

	if (_hoops_PRGSA != null) {
		if (_hoops_IHCR->_hoops_SPH->_hoops_IIPCR.x != _hoops_PRGSA->_hoops_IIPCR.x ||
			_hoops_IHCR->_hoops_SPH->_hoops_IIPCR.y != _hoops_PRGSA->_hoops_IIPCR.y ||
			_hoops_IHCR->_hoops_SPH->_hoops_IIPCR.z != _hoops_PRGSA->_hoops_IIPCR.z) {
			// _hoops_RRP _hoops_IS _hoops_CCIH-_hoops_GH _hoops_GII _hoops_RRR _hoops_RSPHP _hoops_PSPAR
			_hoops_PC 			_hoops_ASPHP;
			_hoops_PC 			_hoops_PSPHP;
			_hoops_PC 			_hoops_HSPHP;

			if ((_hoops_ASPHP = nr->_hoops_IHA->_hoops_AGP) != null) {
				_hoops_CIGA alter &		_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();
				_hoops_PC				_hoops_RPPHP = _hoops_PC::Create(nr->_hoops_SRA);

				_hoops_SIGA->_hoops_AGP = _hoops_RPPHP;

				_hoops_RPPHP->scale = _hoops_ASPHP->scale;
				_hoops_RPPHP->count = _hoops_ASPHP->count;
				_hoops_RPPHP->_hoops_ISPHP =
							 _hoops_ASPHP->_hoops_ISPHP;

				_hoops_GPPHP (dc, _hoops_IHCR->_hoops_SPH, _hoops_RPPHP, _hoops_ASPHP->_hoops_CGR);
			}

			if ((_hoops_PSPHP = nr->_hoops_RHP->_hoops_AGP) != null) {
				Line_Rendition alter &		_hoops_GHP = nr.Modify()->_hoops_RHP.Modify();

				if (_hoops_PSPHP == _hoops_ASPHP)	// _hoops_CCAH _hoops_ISHA _hoops_SS _hoops_PAH _hoops_SHH _hoops_PSHR _hoops_GAR _hoops_CCAH _hoops_HSP _hoops_SS
					_hoops_GHP->_hoops_AGP = nr->_hoops_IHA->_hoops_AGP;
				else {
					_hoops_PC				_hoops_RPPHP = _hoops_PC::Create(nr->_hoops_SRA);

					_hoops_GHP->_hoops_AGP = _hoops_RPPHP;

					_hoops_RPPHP->scale = _hoops_PSPHP->scale;
					_hoops_RPPHP->count = _hoops_PSPHP->count;
					_hoops_RPPHP->_hoops_ISPHP =
								 _hoops_PSPHP->_hoops_ISPHP;

					_hoops_GPPHP (dc, _hoops_IHCR->_hoops_SPH, _hoops_RPPHP, _hoops_PSPHP->_hoops_CGR);
				}
			}

			if ((_hoops_HSPHP = nr->_hoops_SCP->_hoops_AGP) != null) {
				_hoops_ICP alter &	_hoops_CCP = nr.Modify()->_hoops_SCP.Modify();

				if (_hoops_HSPHP == _hoops_ASPHP)		// _hoops_CCAH _hoops_GPIA _hoops_SS _hoops_PAH _hoops_SHH _hoops_PSHR _hoops_GAR _hoops_CCAH _hoops_HSP _hoops_SS
					_hoops_CCP->_hoops_AGP = nr->_hoops_IHA->_hoops_AGP;
				else if (_hoops_HSPHP == _hoops_PSPHP)	// _hoops_CCAH _hoops_GPIA _hoops_SS _hoops_PAH _hoops_SHH _hoops_PSHR _hoops_GAR _hoops_CCAH _hoops_ISHA _hoops_SS
					_hoops_CCP->_hoops_AGP = nr->_hoops_RHP->_hoops_AGP;
				else {
					_hoops_PC				_hoops_RPPHP = _hoops_PC::Create(nr->_hoops_SRA);

					_hoops_CCP->_hoops_AGP = _hoops_RPPHP;

					_hoops_RPPHP->scale = _hoops_HSPHP->scale;
					_hoops_RPPHP->count = _hoops_HSPHP->count;
					_hoops_RPPHP->_hoops_ISPHP =
								 _hoops_HSPHP->_hoops_ISPHP;

					_hoops_GPPHP (dc, _hoops_IHCR->_hoops_SPH, _hoops_RPPHP, _hoops_HSPHP->_hoops_CGR);
				}
			}
		}

		if (_hoops_PRGSA != _hoops_SPH)
			_hoops_HPRH (_hoops_PRGSA);
	}
}

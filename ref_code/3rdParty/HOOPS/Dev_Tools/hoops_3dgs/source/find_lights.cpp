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
 * $Id: obf_tmp.txt 1.168 2010-07-02 21:35:17 covey Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "tandt.h"
#include "hpserror.h"


local void _hoops_RRSPH (
	Display_Context const *		dc,
	Attribute const *			_hoops_ASGPR,
	_hoops_HHAGP alter *		_hoops_CIIPH,
	Color_Object alter *		_hoops_ARSPH,
	_hoops_ACHR alter *			_hoops_SIIPH,
	RGB const * alter *			_hoops_PRSPH,
	RGB alter *					_hoops_HRSPH,
	_hoops_ACHR alter *			_hoops_IIIPH,
	_hoops_ACHR alter *			_hoops_IRSPH,
	bool *						_hoops_CRSPH,
	_hoops_HHRA const * alter *		_hoops_SRSPH,
	_hoops_RHAH const * alter *	_hoops_GASPH,
	_hoops_HRPA const * alter *	_hoops_PIIPH,
	_hoops_HRPA alter *			_hoops_HIIPH) {

	_hoops_SSAGR(_hoops_ASGPR);

	_hoops_HHAGP				_hoops_RCIPH, _hoops_ACIPH;
	Color_Object				_hoops_RASPH, _hoops_AASPH;
	_hoops_ACHR					_hoops_PCIPH, _hoops_HCIPH;

	/* _hoops_HSPP _hoops_CCA _hoops_SGHS _hoops_GCIAA _hoops_HII _hoops_ARRS */
	_hoops_RCIPH = *_hoops_CIIPH;
	_hoops_RASPH = *_hoops_ARSPH;
	_hoops_PCIPH = *_hoops_SIIPH;
	_hoops_ACIPH = false;
	_hoops_AASPH = false;
	_hoops_HCIPH = false;

	/* _hoops_ISPR _hoops_IH _hoops_GGRRA _hoops_SRS */
	Attribute const				*_hoops_SIIAA = _hoops_ASGPR;

	do {
		_hoops_SSAGR(_hoops_ASGPR->next);

		/* _hoops_SR'_hoops_ASAR _hoops_RGAR _hoops_GPIHR _hoops_GGR _hoops_RH _hoops_GCAC _hoops_AAP & _hoops_AIRC _hoops_CHR _hoops_GSHHR */
		if (_hoops_ASGPR->type > HK_RENDERING_OPTIONS)
			break;

		if (_hoops_ASGPR->type == HK_RENDERING_OPTIONS) {
			_hoops_RHAIR const	*_hoops_AHAIR = (_hoops_RHAIR const *)_hoops_ASGPR;

			if (BIT(_hoops_AHAIR->_hoops_SCIAA, _hoops_GSIAA)) {
				if (BIT(_hoops_AHAIR->_hoops_RSIAA, _hoops_GSIAA)) {
					/* _hoops_SSIAA _hoops_GII _hoops_AIRC _hoops_HSGRA _hoops_ARI */
					/* _hoops_PPR _hoops_PRIA _hoops_GII _hoops_SHPH */
					_hoops_ACIPH = _hoops_AHAIR->locks->normal.mask._hoops_IPPGR;
					_hoops_RCIPH &= ~_hoops_ACIPH;
					*_hoops_CIIPH &= ~_hoops_ACIPH;
					*_hoops_CIIPH |= _hoops_ACIPH &
									_hoops_AHAIR->locks->normal.value._hoops_IPPGR;

					/* _hoops_HA _hoops_IH _hoops_HAIR _hoops_ARAH-_hoops_SGHS */
					if (BIT (_hoops_AHAIR->locks->normal.mask._hoops_IPPGR, _hoops_GGCAA(HK_COLOR))) {
						if (BIT(_hoops_AHAIR->locks->normal.value._hoops_IPPGR, _hoops_GGCAA(HK_COLOR))) {
							_hoops_AASPH = _hoops_AHAIR->locks->normal.mask.color;
							_hoops_RASPH = ~_hoops_AASPH;
							*_hoops_ARSPH &= ~_hoops_AASPH;
							*_hoops_ARSPH |= _hoops_AASPH &
											_hoops_AHAIR->locks->normal.value.color;
						}
						else {
							*_hoops_ARSPH = 0;
							_hoops_RASPH = 0;
							_hoops_AASPH = ~0;
						}
					}

					/* _hoops_PPR _hoops_HPRC _hoops_ARAH-_hoops_SGHS */
					if (BIT (_hoops_AHAIR->locks->normal.mask._hoops_IPPGR, _hoops_GGCAA(HK_VISIBILITY))) {
						if (BIT(_hoops_AHAIR->locks->normal.value._hoops_IPPGR, _hoops_GGCAA(HK_VISIBILITY))) {
							_hoops_HCIPH = _hoops_AHAIR->locks->normal.mask._hoops_RGP;
							_hoops_PCIPH &= ~_hoops_HCIPH;
							*_hoops_SIIPH &= ~_hoops_HCIPH;
							*_hoops_SIIPH |= _hoops_HCIPH &
											_hoops_AHAIR->locks->normal.value._hoops_RGP;
						}
						else {
							*_hoops_SIIPH = 0;
							_hoops_PCIPH = 0;
							_hoops_HCIPH = ~0;
						}
					}
				}
				else {
					/* _hoops_SSIAA _hoops_CPS */
					*_hoops_CIIPH = _hoops_RCIPH = false;
					*_hoops_ARSPH = _hoops_RASPH = 0;
					*_hoops_SIIPH = _hoops_PCIPH = 0;
					_hoops_ACIPH = (_hoops_HHAGP)~0;
					_hoops_AASPH = ~0;
					_hoops_HCIPH = ~0;
				}
			}

			if (!dc->options._hoops_SIAH &&
				BIT(_hoops_AHAIR->_hoops_PSHCA, _hoops_HAI) &&
				!BIT (_hoops_RASPH, Color_LIGHTING)) {

				*_hoops_CRSPH = BIT(_hoops_AHAIR->_hoops_RRRAP, _hoops_HAI);
			}

			break;
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	_hoops_ASGPR = _hoops_SIIAA;
	_hoops_SSAGR(_hoops_ASGPR);

	do {
		_hoops_SSAGR(_hoops_ASGPR->next);

		if (_hoops_ASGPR->type > _hoops_IAAA (HK_VISIBILITY, HK_COLOR, HK_COLOR_MAP, HK_CAMERA, HK_MODELLING_MATRIX, HK_STYLE))
			break;

		switch (_hoops_ASGPR->type) {
		case HK_VISIBILITY: {
			_hoops_RSAIR const *		vis = (_hoops_RSAIR const *)_hoops_ASGPR;

			*_hoops_IIIPH &= ~(vis->mask & ~_hoops_PCIPH);
			*_hoops_IIIPH |= vis->value & ~_hoops_PCIPH &
					   vis->mask;
			if (!BIT(_hoops_PCIPH, T_ANY_SHADOW)) {
				*_hoops_IRSPH &= ~vis->_hoops_SPSS.mask;
				*_hoops_IRSPH |= vis->_hoops_SPSS.value &
									vis->_hoops_SPSS.mask;
			}
		}	break;

		case HK_COLOR: if (!BIT (_hoops_RASPH, Color_LIGHTING)) {
			_hoops_SSGI const *			color = (_hoops_SSGI const *)_hoops_ASGPR;

			if (BIT (color->_hoops_GHA, Color_LIGHTING)) {
				_hoops_ACSGA const *	list = color->colors;

				do {
					if (BIT (list->_hoops_GHA, Color_LIGHTING)) {
						switch (list->type) {
							case _hoops_SHGRA: {
								_hoops_PCSGA const *		findex = (_hoops_PCSGA const *)list;

								if ((int)findex->value >= (*_hoops_GASPH)->length) {
									HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_COLOR_INDEX,
											"Lighting color index is out of range");
									_hoops_HRSPH->red   = 1.0f;
									_hoops_HRSPH->green = 1.0f;
									_hoops_HRSPH->blue  = 1.0f;
								}
								else {
									Named_Material const	  *_hoops_ISHIR;

									_hoops_ISHIR = (*_hoops_GASPH)->_hoops_HAA + (int)findex->value;
									*_hoops_HRSPH = _hoops_ISHIR->_hoops_CSHR;
								}
							}	break;

							case _hoops_PPCA: {
								_hoops_APCA const *		normal = (_hoops_APCA const *)list;

								*_hoops_HRSPH = normal->rgb;
							}	break;

							case _hoops_GIGRA: {
								_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;

								*_hoops_HRSPH = _hoops_ICSGA->_hoops_ISHIR._hoops_CSHR;
							}	break;
						}
						if (*_hoops_CRSPH)
							*_hoops_HRSPH = RGB(_hoops_HRSPH->_hoops_CPIR());

						*_hoops_PRSPH = _hoops_HRSPH;
						break;
					}
				} while ((list = list->next) != null);
			}
		}	break;

		case HK_COLOR_MAP: if (!BIT (_hoops_RCIPH, 1L<<HK_COLOR_MAP)) {
			*_hoops_GASPH = (_hoops_RHAH const *)_hoops_ASGPR;
		}	break;

		case HK_CAMERA: if (!BIT (_hoops_RCIPH, 1L<<HK_CAMERA)) {
			*_hoops_SRSPH = (_hoops_HHRA const *)_hoops_ASGPR;
		}	break;

		case HK_MODELLING_MATRIX: if (!BIT (_hoops_RCIPH, 1L<<HK_MODELLING_MATRIX)) {
			_hoops_ISGI const *	matrix = (_hoops_ISGI const *)_hoops_ASGPR;

			if (*_hoops_PIIPH == null)
				HI_Copy_Matrix (&matrix->matrix, _hoops_HIIPH);
			else
				HI_Multiply_Matrices (&matrix->matrix, *_hoops_PIIPH, _hoops_HIIPH);

			*_hoops_PIIPH = _hoops_HIIPH;
		}	break;


		case HK_STYLE: if (!BIT (_hoops_RCIPH, 1L<<HK_STYLE)) {
#ifndef DISABLE_STYLE_SEGMENT
			Style *		style = (Style *)_hoops_ASGPR;

			if (style->_hoops_IGRPR && style->_hoops_IGRPR->_hoops_IPPGR) {
				_hoops_RRSPH (dc, style->_hoops_IGRPR->_hoops_IPPGR,
										_hoops_CIIPH, _hoops_ARSPH, _hoops_SIIPH,
										_hoops_PRSPH, _hoops_HRSPH,
										_hoops_IIIPH, _hoops_IRSPH, _hoops_CRSPH,
										_hoops_SRSPH, _hoops_GASPH, _hoops_PIIPH, _hoops_HIIPH);


				/* _hoops_IRHH _hoops_RCRR _hoops_SGHS _hoops_CHR _hoops_GH-_hoops_IS-_hoops_ICGIP */
				_hoops_RCIPH = *_hoops_CIIPH & ~_hoops_ACIPH;
				_hoops_RASPH = *_hoops_ARSPH & ~_hoops_AASPH;
				_hoops_PCIPH = *_hoops_SIIPH & ~_hoops_HCIPH;
			}
#endif
		}	break;
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
}


/*
 * _hoops_PAGA: _hoops_RH 4_hoops_CRISR _hoops_PIHP _hoops_IIGR _hoops_RH _hoops_GCHRR _hoops_PASPH, _hoops_GAR _hoops_IGI _hoops_PPR _hoops_SPIP _hoops_GGR
 *		 _hoops_RGR _hoops_PCPH, _hoops_SHR _hoops_IIAH _hoops_GGSR _hoops_IS _hoops_SHH (0 0 0 1). _hoops_IPCP *_hoops_HPHR* _hoops_GCHRR
 *		 _hoops_PASPH _hoops_HS _hoops_ICPRA 4_hoops_CRISR _hoops_IAPHR (_hoops_HASPH _hoops_IASPH[3][3]).
 */

local void _hoops_CASPH (
	Display_Context const *			dc,
	Light const *					gl,
	_hoops_ACHR						_hoops_RGP,
	_hoops_ACHR						_hoops_CRR,
	bool							_hoops_CRSPH,
	RGB const *						color,
	_hoops_RHAH const *				_hoops_GPIHP,
	Color_Object					_hoops_RASPH,
	_hoops_HRPA const *				_hoops_HSGA,
	_hoops_HHRA const *					_hoops_SPH,
	_hoops_AS alter * alter *	_hoops_SASPH) {
	_hoops_RPRA const *				mat = _hoops_HSGA->elements;
	_hoops_AS alter *			light;

	POOL_ZALLOC (light, _hoops_AS, dc->memory_pool);
	light->next = *_hoops_SASPH;
	*_hoops_SASPH = light;
	light->_hoops_PCASP = _hoops_AIRIR (gl);

	light->color = *color;
	//_hoops_RRR->_hoops_GPSPH = _hoops_RPSPH::_hoops_APSPH;
	//_hoops_RRR->_hoops_ARARA = _hoops_RPSPH::_hoops_APSPH;

	if (gl->_hoops_IPPGR != null) {
		Attribute const *		_hoops_ASGPR = gl->_hoops_IPPGR;

		do {
			if (_hoops_ASGPR->type > HK_COLOR) break;

			if (_hoops_ASGPR->type == HK_COLOR &&
				!BIT (_hoops_RASPH, Color_LIGHTING) &&
				ANYBIT (((_hoops_SSGI const *)_hoops_ASGPR)->_hoops_GHA, Color_LIGHTING|_hoops_IRARA)) {
				_hoops_SSGI const *		color = (_hoops_SSGI const *)_hoops_ASGPR;
				_hoops_ACSGA const *	list = color->colors;

				do {
					switch (list->type) {
						case _hoops_SHGRA: {
							_hoops_PCSGA const *		findex = (_hoops_PCSGA const *)list;

							if ((int)findex->value >= _hoops_GPIHP->length) {
								HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_COLOR_INDEX,
										  "Lighting color index is out of range");
								if (BIT (list->_hoops_GHA, Color_LIGHTING))
									light->color.red = light->color.green = light->color.blue = 1.0f;
								if (BIT (list->_hoops_GHA, _hoops_PRARA))
									light->_hoops_HASR.red = light->_hoops_HASR.green = light->_hoops_HASR.blue = 0.3f;
								if (BIT (list->_hoops_GHA, _hoops_HRARA))
									light->_hoops_CASR.red = light->_hoops_CASR.green = light->_hoops_CASR.blue = 0.3f;
							}
							else {
								Named_Material const	  *_hoops_ISHIR;

								_hoops_ISHIR = _hoops_GPIHP->_hoops_HAA + (int)findex->value;
								if (BIT (list->_hoops_GHA, Color_LIGHTING))
									light->color = _hoops_ISHIR->_hoops_CSHR;
								if (BIT (list->_hoops_GHA, _hoops_PRARA))
									light->_hoops_HASR = _hoops_ISHIR->_hoops_CSHR;
								if (BIT (list->_hoops_GHA, _hoops_PRARA))
									light->_hoops_CASR = _hoops_ISHIR->_hoops_CSHR;
							}
						}	break;

						case _hoops_PPCA: {
							_hoops_APCA const *		normal = (_hoops_APCA const *)list;

							if (BIT (list->_hoops_GHA, Color_LIGHTING))
								light->color = normal->rgb;
							if (BIT (list->_hoops_GHA, _hoops_PRARA))
								light->_hoops_HASR = normal->rgb;
							if (BIT (list->_hoops_GHA, _hoops_HRARA))
								light->_hoops_CASR = normal->rgb;
						}	break;

						case _hoops_GIGRA: {
							_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;

							if (BIT (list->_hoops_GHA, Color_LIGHTING))
								light->color = _hoops_ICSGA->_hoops_ISHIR._hoops_CSHR;
							if (BIT (list->_hoops_GHA, _hoops_PRARA))
								light->_hoops_HASR = _hoops_ICSGA->_hoops_ISHIR._hoops_CSHR;
							if (BIT (list->_hoops_GHA, _hoops_HRARA))
								light->_hoops_CASR = _hoops_ICSGA->_hoops_ISHIR._hoops_CSHR;
						}	break;
					}
				} while ((list = list->next) != null);

				if (_hoops_CRSPH) {
					light->color = RGB(light->color._hoops_CPIR());
					light->_hoops_HASR = RGB(light->_hoops_HASR._hoops_CPIR());
					light->_hoops_CASR = RGB(light->_hoops_CASR._hoops_CPIR());
				}
			}
		} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
	}


	light->_hoops_PRR = gl->_hoops_PRR;
	light->_hoops_RGP = _hoops_RGP & T_ANY_LIGHTS;
	light->_hoops_CRR = _hoops_CRR;
	light->time_stamp = gl->time_stamp;

	switch (light->_hoops_PRR) {
	  case _hoops_H: {
		  _hoops_HIPIR const *		dl = (_hoops_HIPIR const *)gl;
		  Vector temp;

		  light->direction.x = dl->direction.x;
		  light->direction.y = dl->direction.y;
		  light->direction.z = dl->direction.z;
		  if (BIT (gl->flags, _hoops_RISGP)) {
			  _hoops_HRPA const *	_hoops_PPSPH = &_hoops_SPH->_hoops_PRPA;

			  /* _hoops_HHSA _hoops_RH _hoops_SARA _hoops_IS _hoops_CISA _hoops_GGR _hoops_RGCI _hoops_RIHCR _hoops_RSGA _hoops_RPP _hoops_SCH _hoops_CCACR'_hoops_RA _hoops_CPHR _hoops_HIS _hoops_AIAH */
			  if (!_hoops_SPH->_hoops_PRPA._hoops_RAGR &&
				   _hoops_SPH->_hoops_PRPA.elements[0][0] == 0)
				  HI_Camera_To_Transform ((_hoops_HHRA alter *)_hoops_SPH, 0);
			  if (_hoops_PPSPH->_hoops_APRA == null)
				  HI_Validate_Matrix_Adjoint ((_hoops_HRPA alter *)_hoops_PPSPH);
			  temp.x = _hoops_HPSPH (_hoops_PPSPH->_hoops_APRA->data.elements, light->direction);
			  temp.y = _hoops_IPSPH (_hoops_PPSPH->_hoops_APRA->data.elements, light->direction);
			  temp.z = _hoops_CPSPH (_hoops_PPSPH->_hoops_APRA->data.elements, light->direction);
			  light->direction.x = temp.x;
			  light->direction.y = temp.y;
			  light->direction.z = temp.z;
		  }

		  if (ANYBIT (_hoops_HSGA->_hoops_RAGR, _hoops_CICH)) {
			  temp.x = _hoops_HPSPH (mat, light->direction);
			  temp.y = _hoops_IPSPH (mat, light->direction);
			  temp.z = _hoops_CPSPH (mat, light->direction);
			  light->direction.x = temp.x;
			  light->direction.y = temp.y;
			  light->direction.z = temp.z;
		  }

		  if (!HI_Normalize (&light->direction))
			  HE_WARNING (HEC_DISTANT_LIGHT, HES_DIRECTION_IS_SINGULAR,
					  "Light direction was made singular by the modelling matrix");

		  light->position.x = light->position.y = light->position.z = 0.0f;
		  light->target.x = light->target.y = light->target.z = 0.0f;
		  light->_hoops_ACSR = light->_hoops_HCSR = light->_hoops_CCSGP = 0.0f;
		  light->inner_cos = light->_hoops_HCASP = 0.0f;
		  light->count = 0;
		  light->points = null;
		  light->_hoops_HSSGP = 0;
	  }	  break;

	  case _hoops_C: {
		  _hoops_AIPIR const *		pl = (_hoops_AIPIR const *)gl;

		  if (BIT (gl->flags, _hoops_RISGP)) {
			  Vector const *		_hoops_SPSPH = &_hoops_SPH->_hoops_CRSS;
			  Vector const *		_hoops_GHSPH = &_hoops_SPH->up_vector;
			  Vector const *		_hoops_RHSPH = &_hoops_SPH->_hoops_IIPCR;

			  light->position.x = _hoops_SPH->position.x +
								  _hoops_SPSPH->x * pl->position.x +
								  _hoops_GHSPH->x * pl->position.x +
								  _hoops_RHSPH->x * pl->position.x;
			  light->position.y = _hoops_SPH->position.y +
								  _hoops_SPSPH->y * pl->position.y +
								  _hoops_GHSPH->y * pl->position.y +
								  _hoops_RHSPH->y * pl->position.y;
			  light->position.z = _hoops_SPH->position.z +
								  _hoops_SPSPH->z * pl->position.z +
								  _hoops_GHSPH->z * pl->position.z +
								  _hoops_RHSPH->z * pl->position.z;
		  }
		  else {
			  light->position.x = pl->position.x;
			  light->position.y = pl->position.y;
			  light->position.z = pl->position.z;
		  }
		  if (ANYBIT (_hoops_HSGA->_hoops_RAGR, _hoops_CICH)) {
			  Point					temp;

			  temp.x = _hoops_HPRA (mat, light->position);
			  temp.y = _hoops_IPRA (mat, light->position);
			  temp.z = _hoops_CPRA (mat, light->position);
			  light->position.x = temp.x;
			  light->position.y = temp.y;
			  light->position.z = temp.z;
		  }
		  light->direction.x = light->direction.y = light->direction.z = 0.0f;
		  light->target.x = light->target.y = light->target.z = 0.0f;
		  light->_hoops_ACSR = light->_hoops_HCSR = light->_hoops_CCSGP = 0.0f;
		  light->inner_cos = light->_hoops_HCASP = 0.0f;
		  light->count = 0;
		  light->points = null;
		  light->_hoops_HSSGP = 0;
	  }	  break;

	  case _hoops_I: {
		  _hoops_PIPIR const *		sl = (_hoops_PIPIR const *)gl;
		  float						length;
		  float						tmp;

		  if (BIT (gl->flags, _hoops_RISGP)) {
			  Vector const *		_hoops_SPSPH = &_hoops_SPH->_hoops_CRSS;
			  Vector const *		_hoops_GHSPH = &_hoops_SPH->up_vector;
			  Vector const *		_hoops_RHSPH = &_hoops_SPH->_hoops_IIPCR;

			  light->position.x = _hoops_SPH->position.x +
								  _hoops_SPSPH->x * sl->position.x +
								  _hoops_GHSPH->x * sl->position.x +
								  _hoops_RHSPH->x * sl->position.x;
			  light->position.y = _hoops_SPH->position.y +
								  _hoops_SPSPH->y * sl->position.y +
								  _hoops_GHSPH->y * sl->position.y +
								  _hoops_RHSPH->y * sl->position.y;
			  light->position.z = _hoops_SPH->position.z +
								  _hoops_SPSPH->z * sl->position.z +
								  _hoops_GHSPH->z * sl->position.z +
								  _hoops_RHSPH->z * sl->position.z;

			  light->target.x = _hoops_SPH->target.x +
								_hoops_SPSPH->x * sl->target.x +
								_hoops_GHSPH->x * sl->target.x +
								_hoops_RHSPH->x * sl->target.x;
			  light->target.y = _hoops_SPH->target.y +
								_hoops_SPSPH->y * sl->target.y +
								_hoops_GHSPH->y * sl->target.y +
								_hoops_RHSPH->y * sl->target.y;
			  light->target.z = _hoops_SPH->target.z +
								_hoops_SPSPH->z * sl->target.z +
								_hoops_GHSPH->z * sl->target.z +
								_hoops_RHSPH->z * sl->target.z;
		  }
		  else {
			  light->position.x = sl->position.x;
			  light->position.y = sl->position.y;
			  light->position.z = sl->position.z;
			  light->target.x = sl->target.x;
			  light->target.y = sl->target.y;
			  light->target.z = sl->target.z;
		  }

		  if (ANYBIT (_hoops_HSGA->_hoops_RAGR, _hoops_CICH)) {
			  Point					temp;

			  temp.x = _hoops_HPRA (mat, light->position);
			  temp.y = _hoops_IPRA (mat, light->position);
			  temp.z = _hoops_CPRA (mat, light->position);
			  light->position.x = temp.x;
			  light->position.y = temp.y;
			  light->position.z = temp.z;

			  temp.x = _hoops_HPRA (mat, light->target);
			  temp.y = _hoops_IPRA (mat, light->target);
			  temp.z = _hoops_CPRA (mat, light->target);
			  light->target.x = temp.x;
			  light->target.y = temp.y;
			  light->target.z = temp.z;
		  }

		  light->direction.x = light->target.x - light->position.x;
		  light->direction.y = light->target.y - light->position.y;
		  light->direction.z = light->target.z - light->position.z;

		  length = _hoops_SGIHR (light->direction.x * light->direction.x +
						 light->direction.y * light->direction.y +
						 light->direction.z * light->direction.z);

		  if (!HI_Normalize (&light->direction))
			  HE_WARNING (HEC_SPOT_LIGHT, HES_DIRECTION_IS_SINGULAR,
					  "Light direction was made singular by the modelling matrix");

		  light->_hoops_HCSR = sl->_hoops_ASSGP;
		  light->_hoops_ACSR = sl->_hoops_RSSGP;
		  light->_hoops_CCSGP = sl->_hoops_CCSGP;

		  /*
		   * _hoops_GHCA _hoops_RRP _hoops_IS _hoops_GRAS _hoops_RCSA _hoops_HA _hoops_SGS _hoops_SR _hoops_ACPA _hoops_RH
		   * _hoops_GSSP _hoops_PCRR _hoops_IIGR _hoops_IRS _hoops_SARA-_hoops_CSCHR _hoops_RRR
		   */
		  if (BIT (gl->flags, _hoops_RISGP)) {
			  if (sl->_hoops_SCSGP == _hoops_PCSGP) {
				  tmp = sl->_hoops_ASSGP * 0.5f;
				  tmp *= tmp;
				  tmp += length * length;
				  if ((tmp = _hoops_SGIHR (tmp)) == 0.0f) tmp = 1.0f;
				  tmp = length / tmp;
				  light->_hoops_HCASP = tmp;
				  light->_hoops_HCSR = _hoops_ISSSR (tmp);

				  if (sl->_hoops_GSSGP == _hoops_ICSGP) {
					  light->_hoops_ACSR = light->_hoops_HCSR * sl->_hoops_RSSGP;
					  light->inner_cos = COS (light->_hoops_ACSR);
				  }
			  }
			  if (sl->_hoops_GSSGP == _hoops_PCSGP) {
				  tmp = sl->_hoops_RSSGP * 0.5f;
				  tmp *= tmp;
				  tmp += length * length;
				  if ((tmp = _hoops_SGIHR (tmp)) == 0.0f) tmp = 1.0f;
				  tmp = length / tmp;
				  light->inner_cos = tmp;
				  light->_hoops_ACSR = _hoops_ISSSR (tmp);
			  }
		  }
		  else {
			  light->inner_cos = COS (light->_hoops_ACSR);
			  light->_hoops_HCASP = COS (light->_hoops_HCSR);
		  }

		  light->count = 0;
		  light->points = null;
		  light->_hoops_HSSGP = 0;
	  }	  break;

	  case _hoops_S: {
		  _hoops_SHPIR const *		al = (_hoops_SHPIR const *)gl;

		  light->_hoops_HSSGP = al->_hoops_HSSGP;
		  light->count = al->count;
		  light->_hoops_ACSR = 0.0f;
		  light->_hoops_HCSR = 90.0f;
		  light->_hoops_CCSGP = 1.0f;
		  light->inner_cos = 1.0f;
		  light->_hoops_HCASP = 0.0f;
		  light->position.x = light->position.y = light->position.z = 0.0f;
		  if ((light->count = al->count) > 0) {
			  Point alter *			to;
			  Point const *			from;
			  int					_hoops_AHSPH = light->count;

			  ALLOC_ARRAY (to, _hoops_AHSPH, Point);
			  light->points = to;
			  from = al->points;

			  if (!ANYBIT (_hoops_HSGA->_hoops_RAGR, _hoops_CICH)) {
				  while (_hoops_AHSPH-- > 0) {
					  light->position.x += (to->x = from->x);
					  light->position.y += (to->y = from->y);
					  light->position.z += (to->z = from->z);

					  ++from; ++to;
				  }
			  }
			  else {
				  while (_hoops_AHSPH-- > 0) {
					  to->x = _hoops_HPRA (mat, *from);
					  to->y = _hoops_IPRA (mat, *from);
					  to->x = _hoops_CPRA (mat, *from);

					  light->position.x += to->x;
					  light->position.y += to->y;
					  light->position.z += to->z;

					  ++from; ++to;
				  }
			  }

			  light->position.x /= (float)light->count;
			  light->position.y /= (float)light->count;
			  light->position.z /= (float)light->count;
		  }
		  else
			  light->points = null;

		  _hoops_ARPA						plane;

		  (void)HI_Figure_Plane_From_Points (light->count,
							(Point alter *)light->points, &plane);

		  if (light->_hoops_HSSGP == _hoops_SISGP) {
			  light->direction.x = -plane.a;
			  light->direction.y = -plane.b;
			  light->direction.z = -plane.c;
		  }
		  else {
			  light->direction.x = plane.a;
			  light->direction.y = plane.b;
			  light->direction.z = plane.c;
		  }

		  light->target.x = light->position.x + light->direction.x;
		  light->target.y = light->position.y + light->direction.y;
		  light->target.z = light->position.z + light->direction.z;
	  }	  break;
	}

	light->_hoops_ICASP = BIT (gl->flags, _hoops_RISGP);

	light->_hoops_ARSR.x = light->direction.x - _hoops_SPH->_hoops_IIPCR.x;
	light->_hoops_ARSR.y = light->direction.y - _hoops_SPH->_hoops_IIPCR.y;
	light->_hoops_ARSR.z = light->direction.z - _hoops_SPH->_hoops_IIPCR.z;
	HI_Normalize (&light->_hoops_ARSR);
}


local void _hoops_PSIPH (
	Display_Context const *			dc,
	Geometry const *				geometry,
	_hoops_HHAGP					_hoops_RCIPH,
	Color_Object					_hoops_RASPH,
	_hoops_ACHR						_hoops_PCIPH,
	RGB const *						color,
	_hoops_ACHR						_hoops_RGP,
	_hoops_ACHR						_hoops_CRR,
	bool							_hoops_CRSPH,
	_hoops_RHAH const *				_hoops_GPIHP,
	_hoops_HRPA const *				_hoops_HSGA,
	_hoops_HHRA const *					_hoops_SPH,
	_hoops_AS alter * alter *	_hoops_SASPH,
	_hoops_ACHR alter *				_hoops_PHSPH,
	_hoops_ACHR alter *				_hoops_HHSPH,
	int								mask = ~0,
	bool							single = false) {
	_hoops_HRPA const *				_hoops_IHSPH = _hoops_HSGA;

	if (geometry == null || !ANYBIT (mask, _hoops_AGPGR (_hoops_ICIP)))
		return;

	do {
		_hoops_HSGA = _hoops_IHSPH;
		if (geometry->type == _hoops_ICIP) {
			*_hoops_PHSPH		 |= (_hoops_RGP & T_ANY_LIGHTS);
			*_hoops_HHSPH &= (_hoops_RGP & T_ANY_LIGHTS);
			_hoops_CASPH (dc, (Light const *)geometry, _hoops_RGP, _hoops_CRR, _hoops_CRSPH,
					   color, _hoops_GPIHP, _hoops_RASPH, _hoops_HSGA, _hoops_SPH, _hoops_SASPH);
		}
		else if (geometry->type == _hoops_AHIP) {
			_hoops_PHIP const *		_hoops_RRA = (_hoops_PHIP const *)geometry;
			_hoops_HRPA						_hoops_HIIPH;
			RGB								_hoops_HRSPH;

			if (_hoops_RRA->_hoops_IPPGR != null) {
				_hoops_RRSPH (dc, _hoops_RRA->_hoops_IPPGR,
										  &_hoops_RCIPH, &_hoops_RASPH, &_hoops_PCIPH,
										  &color, &_hoops_HRSPH,
										  &_hoops_RGP, &_hoops_CRR, &_hoops_CRSPH,
										  &_hoops_SPH, &_hoops_GPIHP, &_hoops_HSGA, &_hoops_HIIPH);
			}

			if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
				_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0];

				_hoops_PSIPH (dc, _hoops_SRCP->geometry,
								  _hoops_RCIPH, _hoops_RASPH, _hoops_PCIPH,
								  color, _hoops_RGP, _hoops_CRR, _hoops_CRSPH,
								  _hoops_GPIHP, _hoops_HSGA, _hoops_SPH, _hoops_SASPH, _hoops_PHSPH, _hoops_HHSPH,
								  mask & _hoops_RRA->_hoops_RGPGR);
			}
			else {
				for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++)
					_hoops_PSIPH (dc, (Geometry const *)_hoops_RRA->_hoops_IHIP[i],
									  _hoops_RCIPH, _hoops_RASPH, _hoops_PCIPH,
									  color, _hoops_RGP, _hoops_CRR, _hoops_CRSPH,
									  _hoops_GPIHP, _hoops_HSGA, _hoops_SPH, _hoops_SASPH, _hoops_PHSPH, _hoops_HHSPH,
									  mask & _hoops_RRA->_hoops_RGPGR, true);
			}
		}

		if (single)
			break;
	} while ((geometry = geometry->next) != null);
}

local void _hoops_CHSPH (
	Display_Context const *			dc,
	_hoops_CRCP const *					_hoops_SRCP,
	_hoops_HHAGP					_hoops_RCIPH,
	Color_Object					_hoops_RASPH,
	_hoops_ACHR						_hoops_PCIPH,
	RGB const *						color,
	_hoops_ACHR						_hoops_RGP,
	_hoops_ACHR						_hoops_CRR,
	bool							_hoops_CRSPH,
	_hoops_RHAH const *				_hoops_GPIHP,
	_hoops_HRPA const *				_hoops_HSGA,
	_hoops_HHRA const *					_hoops_SPH,
	bool							_hoops_SSIPH,
	_hoops_AS alter * alter *	_hoops_SASPH,
	_hoops_ACHR alter *				_hoops_PHSPH,
	_hoops_ACHR alter *				_hoops_HHSPH) {
	_hoops_HRPA						_hoops_HIIPH;
	RGB								_hoops_HRSPH;

  top:;

	if (_hoops_SRCP->_hoops_IPPGR != null && _hoops_SSIPH)
		_hoops_RRSPH (dc, _hoops_SRCP->_hoops_IPPGR,
								  &_hoops_RCIPH, &_hoops_RASPH, &_hoops_PCIPH,
								  &color, &_hoops_HRSPH,
								  &_hoops_RGP, &_hoops_CRR, &_hoops_CRSPH,
								  &_hoops_SPH, &_hoops_GPIHP, &_hoops_HSGA, &_hoops_HIIPH);


	if (_hoops_SRCP->geometry != null && BIT (_hoops_RGP, T_ANY_LIGHTS))
		_hoops_PSIPH (dc, _hoops_SRCP->geometry,
						  _hoops_RCIPH, _hoops_RASPH, _hoops_PCIPH,
						  color, _hoops_RGP, _hoops_CRR, _hoops_CRSPH,
						  _hoops_GPIHP, _hoops_HSGA, _hoops_SPH, _hoops_SASPH, _hoops_PHSPH, _hoops_HHSPH);


	{
		Subsegment const *			_hoops_GIPIA;

		if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
			_hoops_CRCP const *		_hoops_GGCPH = _hoops_SSIGP (_hoops_GIPIA);

			if (_hoops_GGCPH->_hoops_AAGSA() > 0 &&
				!BIT (_hoops_GGCPH->_hoops_PHSI, _hoops_SHSIR)) {
				if (1 || _hoops_GGCPH->next != null) {
					_hoops_CHSPH (dc, _hoops_GGCPH,
										_hoops_RCIPH, _hoops_RASPH, _hoops_PCIPH,
										color, _hoops_RGP, _hoops_CRR, _hoops_CRSPH,
										_hoops_GPIHP, _hoops_HSGA, _hoops_SPH,
										true,
										_hoops_SASPH, _hoops_PHSPH, _hoops_HHSPH);
				}
				else {
					_hoops_SRCP = _hoops_GGCPH;
					_hoops_SSIPH = true;
					goto top;
				}
			}
		} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);
	}
}


local void _hoops_SHSPH (
	Display_Context const *		dc,
	_hoops_PC alter &		_hoops_RPPHP,
	_hoops_AS const *		_hoops_APPHP,
	_hoops_ACHR					geom) {
	_hoops_AS alter *		light;
	Point*						_hoops_HRRGA = (Point*)(_hoops_APPHP->points);
	Point*						new_points;

	do if (BIT (_hoops_APPHP->_hoops_RGP, geom)) {
		_hoops_HAHSA(_hoops_APPHP, 1, _hoops_AS, light, dc->memory_pool);
		_hoops_APRGA(_hoops_HRRGA, light->count, Point, new_points);

		light->next = _hoops_RPPHP->_hoops_CGR;
		_hoops_RPPHP->_hoops_CGR = light;
	} while ((_hoops_APPHP = _hoops_APPHP->next) != null);
}


local void _hoops_GISPH (
	Net_Rendition alter &		nr,
	_hoops_PC alter &		_hoops_RPPHP) {
	_hoops_AS alter *		light;

	_hoops_RPPHP->count = 0;
	_hoops_RPPHP->_hoops_ISPHP = false;

	light = _hoops_RPPHP->_hoops_CGR;
	do {
		++_hoops_RPPHP->count;

		switch (light->_hoops_PRR) {
		  case _hoops_H: {
			  /* _hoops_RPAPR */
		  }	  break;

		  case _hoops_C:
		  case _hoops_I:
		  case _hoops_S: {
			  _hoops_RPPHP->_hoops_ISPHP = true;
		  }	  break;

		  default: {
			  _hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Light? What light?");
		  }	  break;
		}
	} while ((light = light->next) != null);

	/* _hoops_CSGA _hoops_IRS _hoops_SAAA */
	if (nr->_hoops_SRA->options._hoops_RCPRP > 0.0f)
		_hoops_RPPHP->scale = 1.0f / nr->_hoops_SRA->options._hoops_RCPRP;
	else {
		RGB		total, _hoops_RISPH;

		/* _hoops_SSCR _hoops_IRS _hoops_APSR _hoops_AISPH */

		total = 0.5f * (nr->_hoops_IRR->_hoops_HASR + nr->_hoops_IRR->_hoops_CASR);
		_hoops_RISPH = _hoops_GPSR::_hoops_RPSR;

		light = _hoops_RPPHP->_hoops_CGR;
		do {
			if (light->_hoops_PRR == _hoops_I) {
				if (light->color.red > _hoops_RISPH.red)
					_hoops_RISPH.red = light->color.red;
				if (light->color.green > _hoops_RISPH.green)
					_hoops_RISPH.green = light->color.green;
				if (light->color.blue > _hoops_RISPH.blue)
					_hoops_RISPH.blue = light->color.blue;
			}
			else {
				total += light->color;
			}
			total += 0.5f * (light->_hoops_HASR + light->_hoops_CASR);
		} while ((light = light->next) != null);
		total += _hoops_RISPH;

		_hoops_RPPHP->scale = _hoops_IAAA (total.red, total.green, total.blue);

		if (_hoops_RPPHP->scale < 1.0f)
			_hoops_RPPHP->scale = 1.0f;
		else
			_hoops_RPPHP->scale = 1.0f / _hoops_RPPHP->scale;
	}

	/* _hoops_GHAA _hoops_RH _hoops_SAAA */
	light = _hoops_RPPHP->_hoops_CGR;
	do {
		light->color *= _hoops_RPPHP->scale;
		light->_hoops_HASR  *= _hoops_RPPHP->scale;
		light->_hoops_CASR *= _hoops_RPPHP->scale;
	} while ((light = light->next) != null);

	/*
	 * _hoops_HGI _hoops_GPSPR _hoops_IIGR _hoops_RRGR _hoops_HRGR _hoops_GHIS _hoops_IIGR _hoops_PISPH, _hoops_PGGA _hoops_SCH _hoops_HISPH _hoops_RH
	 * _hoops_SCGR _hoops_IPP, _hoops_HPGP _hoops_RH _hoops_IISPH _hoops_CRS _hoops_GIAA _hoops_RH _hoops_CIS'_hoops_GRI _hoops_SCII
	 * _hoops_CHH _hoops_SGAGA _hoops_CISPH.	_hoops_SISPH, _hoops_SR'_hoops_ASAR _hoops_GPGS _hoops_RGAR _hoops_RH
	 * _hoops_AASR _hoops_PAIP, _hoops_PPR _hoops_SR _hoops_ACPA _hoops_SGS _hoops_RGAR _hoops_RH _hoops_GCAC _hoops_RRGR/_hoops_SPSIR
	 * _hoops_CHH _hoops_CACH _hoops_SCH _hoops_SPS.
	 */
	{
		_hoops_GRGH alter & 		_hoops_RRGH = nr.Modify()->_hoops_IRR.Modify();

		_hoops_RRGH->_hoops_HASR *= _hoops_RPPHP->scale;
		_hoops_RRGH->_hoops_CASR *= _hoops_RPPHP->scale;
	}
}


local void _hoops_GCSPH (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP) {
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	_hoops_ISHHP const &	_hoops_CSHHP = nr->_hoops_ASIR;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_AS alter *		_hoops_CGR = null;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_RHAH const *			_hoops_GPIHP;
	_hoops_ACHR					_hoops_PHSPH = false;
	_hoops_ACHR					_hoops_HHSPH = T_ANY_LIGHTS;
	bool						_hoops_CRSPH = BIT(_hoops_RRGH->_hoops_PPH, _hoops_HAI);;

	if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR && dc->_hoops_GCPRP <= 0) {
		HE_ERROR2 (HEC_DISTANT_LIGHT, HES_SMALL_FIXED_COLORS,
				Sprintf_P (null, "Can't turn on lights in '%p' -", _hoops_SRCP),
				   "'Fixed colors' came out too small");
		return;
	}

	_hoops_GPIHP = _hoops_CSHHP->_hoops_PSIR->_hoops_CSIR;

	_hoops_CHSPH (dc, _hoops_SRCP, _hoops_RRGH->locks._hoops_IPPGR, _hoops_RRGH->locks.color, _hoops_RRGH->locks._hoops_RGP,
						&_hoops_RRGH->_hoops_PCP, nr->_hoops_RGP, _hoops_RRGH->_hoops_CRR, _hoops_CRSPH, _hoops_GPIHP,
						&_hoops_IHCR->_hoops_IPH->data, _hoops_IHCR->_hoops_SPH,
						false, &_hoops_CGR, &_hoops_PHSPH, &_hoops_HHSPH);

	if (_hoops_PHSPH) {
		_hoops_PC					_hoops_RCSPH = _hoops_PC::Create(dc);

		if (BIT (_hoops_HHSPH, T_LIGHTS_FOR_FACES))
			nr->_hoops_IHA->_hoops_AGP = _hoops_RCSPH;
		else if (BIT (_hoops_PHSPH, T_LIGHTS_FOR_FACES)) {
			_hoops_PC				_hoops_ACSPH = _hoops_PC::Create(dc);

			nr->_hoops_IHA->_hoops_AGP = _hoops_ACSPH;

			_hoops_SHSPH (dc, _hoops_ACSPH, _hoops_CGR, T_LIGHTS_FOR_FACES);
			_hoops_GISPH (nr, _hoops_ACSPH);
		}

		if (BIT (_hoops_HHSPH, T_LIGHTS_FOR_EDGES))
			nr->_hoops_RHP->_hoops_AGP = _hoops_RCSPH;
		else if (BIT (_hoops_PHSPH, T_LIGHTS_FOR_EDGES)) {
			_hoops_PC				_hoops_ACSPH = _hoops_PC::Create(dc);

			nr->_hoops_RHP->_hoops_AGP = _hoops_ACSPH;

			_hoops_SHSPH (dc, _hoops_ACSPH, _hoops_CGR, T_LIGHTS_FOR_EDGES);
			_hoops_GISPH (nr, _hoops_ACSPH);
		}

		if (BIT (_hoops_HHSPH, T_LIGHTS_FOR_MARKERS))
			nr->_hoops_SCP->_hoops_AGP = _hoops_RCSPH;
		else if (BIT (_hoops_PHSPH, T_LIGHTS_FOR_MARKERS)) {
			_hoops_PC				_hoops_ACSPH = _hoops_PC::Create(dc);

			nr->_hoops_SCP->_hoops_AGP = _hoops_ACSPH;

			_hoops_SHSPH (dc, _hoops_ACSPH, _hoops_CGR, T_LIGHTS_FOR_MARKERS);
			_hoops_GISPH (nr, _hoops_ACSPH);
		}

		_hoops_RCSPH->_hoops_CGR = _hoops_CGR;	// _hoops_SGH _hoops_CAPR, _hoops_PAR _hoops_APRI _hoops_RPP _hoops_SR _hoops_SARS'_hoops_RA _hoops_CGRPR _hoops_GII

		if (_hoops_RCSPH->shared())
			_hoops_GISPH (nr, _hoops_RCSPH);
	}
}


GLOBAL_FUNCTION void HD_Find_Lights (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP) {

	nr.Modify();
	nr->_hoops_IHA.Modify()->_hoops_AGP = null;
	nr->_hoops_RHP.Modify()->_hoops_AGP = null;
	nr->_hoops_SCP.Modify()->_hoops_AGP = null;

	if (_hoops_SRCP->_hoops_AAGSA() > 0)
		_hoops_GCSPH (nr, _hoops_SRCP);
}

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
 * $Id: obf_tmp.txt 1.284 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "patterns.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "adt.h"





/* _hoops_RARHR _hoops_HRGR _hoops_PCSPH _hoops_CRICR _hoops_IS _hoops_ISPAA _hoops_IIGR _hoops_HCSPH */

local void _hoops_PIIS (
	_hoops_AIGPR *			_hoops_RIGC,
	Attribute *						_hoops_ASGPR,
	Attribute **					_hoops_PSACR,
	Type							type,
	_hoops_PIGRA *				locks,
	_hoops_PIGRA *				_hoops_SACRP,
	unsigned int *					_hoops_ICSPH,
	int								_hoops_CCSPH,
	_hoops_CRACA const *	control)
{
	_hoops_SSAGR(_hoops_ASGPR);
	_hoops_PIGRA			_hoops_PCGS;
	_hoops_PIGRA *		_hoops_SCSPH = locks;
	Attribute *				_hoops_SIIAA = _hoops_ASGPR;
	bool					_hoops_RPGIP = false;
	unsigned int *			conditions = _hoops_ICSPH;
	int						_hoops_IRCAA = 0;
	_hoops_PIGRA			_hoops_CIIAA;

	ZERO_STRUCT (&_hoops_CIIAA, _hoops_PIGRA);

	/* _hoops_RRP _hoops_IS _hoops_ISPR _hoops_IH _hoops_RCIAA _hoops_ACIAA _hoops_RSIH, _hoops_IS _hoops_CGIC
	** _hoops_IGH _hoops_PAR _hoops_HAR _hoops_PA _hoops_ARPP _hoops_SCH (_hoops_SHCAR, _hoops_PCIAA) _hoops_GHCA _hoops_SHH _hoops_IGI _hoops_HCIAA */

	do {
		_hoops_SSAGR(_hoops_ASGPR->next);

		if (_hoops_ASGPR->type > _hoops_IAAA (HK_RENDERING_OPTIONS, _hoops_CPPIR))
			break;

		if (_hoops_ASGPR->type == HK_RENDERING_OPTIONS) {
			_hoops_RHAIR	*_hoops_AHAIR = (_hoops_RHAIR *)_hoops_ASGPR;

			if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_GSIAA)) {
				_hoops_PIGRA			_hoops_PHGIP;

				/* _hoops_HSPP _hoops_CCA _hoops_SGHS _hoops_GCIAA _hoops_HII _hoops_ARRS */
				_hoops_RSAI (locks, _hoops_PIGRA, &_hoops_PCGS);
				_hoops_SCSPH = &_hoops_PCGS;

				if (BIT (_hoops_AHAIR->_hoops_RSIAA, _hoops_GSIAA)) {
					/* _hoops_PA _hoops_HSGRA _hoops_HRGR _hoops_HCAGR _hoops_ASIAA _hoops_HCIAA */
					_hoops_RSAI (&_hoops_AHAIR->locks->normal.mask, _hoops_PIGRA, &_hoops_CIIAA);
					// _hoops_HIH _hoops_HAR _hoops_PA _hoops_GRGA _hoops_ARP _hoops_IS _hoops_SSPC
					_hoops_HSIAA (&_hoops_CIIAA, _hoops_SACRP, sizeof (_hoops_PIGRA));

					/* _hoops_HASC _hoops_CCAH _hoops_AAHS _hoops_HRP */
					_hoops_HSIAA (&_hoops_PCGS, &_hoops_CIIAA, sizeof (_hoops_PIGRA));
					/* _hoops_PIASR _hoops_HRGR _hoops_PA _hoops_SR _hoops_HHGC _hoops_IS _hoops_AAHS, _hoops_ACCHA _hoops_GII _hoops_SR _hoops_SPGA'_hoops_RA _hoops_PHRH _hoops_IS _hoops_AGRP */
					_hoops_RSAI (&_hoops_AHAIR->locks->normal.value, _hoops_PIGRA, &_hoops_PHGIP);
					_hoops_HSIAA (&_hoops_PHGIP, _hoops_SACRP, sizeof (_hoops_PIGRA));

					_hoops_ISIAA (&_hoops_PCGS, &_hoops_PHGIP, sizeof (_hoops_PIGRA));

					/* _hoops_IH _hoops_IRGH _hoops_HCGC _hoops_ARP _hoops_RGR _hoops_IS _hoops_SRCH _hoops_CSIAA '_hoops_PCPAR _hoops_HIH _hoops_HCIAA _hoops_ASIAA' */
					_hoops_RSAI (&_hoops_PCGS, _hoops_PIGRA, locks);
					_hoops_HSIAA (&_hoops_PCGS, &_hoops_CIIAA, sizeof (_hoops_PIGRA));
				}
			}
			if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_RGRAP)) {
				// _hoops_AGCR _hoops_SAHR _hoops_RARHR -- _hoops_RPSI _hoops_PAH _hoops_HAR _hoops_HHSP
				_hoops_ISIAA (_hoops_SACRP, &_hoops_AHAIR->locks->_hoops_SACRP.value, sizeof (_hoops_PIGRA));
			}


			/* _hoops_GCAC _hoops_AAP _hoops_CGH _hoops_SHH _hoops_SRS, _hoops_HIH _hoops_AA _hoops_RGR _hoops_ARI _hoops_GGR _hoops_AGIR _hoops_SCH _hoops_SHPH */
			if (type == HK_MODELLING_MATRIX &&
				control != null && BIT (_hoops_CCSPH, _hoops_SRACA) &&
				!BIT (_hoops_SCSPH->_hoops_IPPGR, _hoops_GGCAA(HK_RENDERING_OPTIONS)) &&
				BIT (_hoops_AHAIR->_hoops_SCIAA & _hoops_AHAIR->_hoops_RSIAA, _hoops_AGICA) &&
				_hoops_AHAIR->_hoops_PGICA != _hoops_GCAAP) {
				_hoops_ISGI alter *		_hoops_HSGA = (_hoops_ISGI alter *)*_hoops_PSACR;
				_hoops_HRPA						temp;
				_hoops_HRPA						_hoops_RHSPR;

				if (ANYBIT (_hoops_AHAIR->_hoops_PGICA, _hoops_ACAAP) &&
					_hoops_HSGA != null) {	/* _hoops_PAHH _hoops_SPR, _hoops_HIH _hoops_ISAP _hoops_IS _hoops_AA _hoops_RPP _hoops_PIRC */
					if (BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_CIAAP)) {
						HI_Copy_Matrix (&_hoops_HSGA->matrix, &temp);
						if (!BIT (_hoops_AHAIR->_hoops_PGICA,
								  _hoops_IIAAP)) {
							HI_Normalize ((Vector *)&temp.elements[0][0]);
							HI_Normalize ((Vector *)&temp.elements[1][0]);
							HI_Normalize ((Vector *)&temp.elements[2][0]);
						}
						temp.elements[3][0] =
							temp.elements[3][1] =
								temp.elements[3][2] = 0.0f;
						HI_Validate_Matrix_Adjoint (&temp);
						_hoops_AIGA (&temp._hoops_APRA->data.elements[0][0], 16, float,
									 &temp.elements[0][0]);
						/* _hoops_RSGA _hoops_IHGIP _hoops_CHGIP, _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_ASSP'_hoops_RA _hoops_IHSH _hoops_PRAR _hoops_GIR */
						//_hoops_IRHP._hoops_SGI &= _hoops_GSSPH;
						temp._hoops_CPH = 0.0f;

						HI_Copy_Matrix (&_hoops_HSGA->matrix, &_hoops_RHSPR);
						HI_Multiply_Matrices (&temp, &_hoops_RHSPR, &_hoops_HSGA->matrix);
					}
					else if (BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_IIAAP)) {
						float			_hoops_PIIH, _hoops_HIIH, _hoops_SHGIP;

						_hoops_PIIH = (float)HI_Compute_Vector_Length ((Vector const *)&_hoops_HSGA->matrix.elements[0][0]);
						_hoops_HIIH = (float)HI_Compute_Vector_Length ((Vector const *)&_hoops_HSGA->matrix.elements[1][0]);
						_hoops_SHGIP = (float)HI_Compute_Vector_Length ((Vector const *)&_hoops_HSGA->matrix.elements[2][0]);

						if (_hoops_PIIH == 0.0f)
							_hoops_PIIH = 1.0f;
						if (_hoops_HIIH == 0.0f)
							_hoops_HIIH = 1.0f;
						if (_hoops_SHGIP == 0.0f)
							_hoops_SHGIP = 1.0f;

						HI_Figure_Scale_Matrix (1.0f / _hoops_PIIH, 1.0f / _hoops_HIIH, 1.0f / _hoops_SHGIP, &temp);
						HI_Copy_Matrix (&_hoops_HSGA->matrix, &_hoops_RHSPR);
						HI_Multiply_Matrices (&temp, &_hoops_RHSPR, &_hoops_HSGA->matrix);
					}
					if (BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_SIAAP)) {
						HI_Ident_Matrix (&temp);
						temp.elements[3][0] = -_hoops_HSGA->matrix.elements[3][0];
						temp.elements[3][1] = -_hoops_HSGA->matrix.elements[3][1];
						temp.elements[3][2] = -_hoops_HSGA->matrix.elements[3][2];
						temp._hoops_RAGR = _hoops_PRICR;
						if (temp.elements[3][2] != 0.0f)
							temp._hoops_RAGR |= _hoops_RRICR;
						HI_Copy_Matrix (&_hoops_HSGA->matrix, &_hoops_RHSPR);
						HI_Multiply_Matrices (&temp, &_hoops_RHSPR, &_hoops_HSGA->matrix);
					}
				}

				if (ANYBIT (_hoops_AHAIR->_hoops_PGICA, _hoops_RCAAP)) {
					_hoops_HHRA const *		_hoops_SPH = control->_hoops_SPH;

					if (_hoops_HSGA == null) {	/* _hoops_PAHH _hoops_SPR, _hoops_HIH _hoops_SAHR _hoops_GGR _hoops_AGIR */
						ZALLOC (_hoops_HSGA, _hoops_ISGI);
						_hoops_HSGA->type = HK_MODELLING_MATRIX;
						_hoops_HSGA->_hoops_HIHI = 1;
						HI_Ident_Matrix (&_hoops_HSGA->matrix);
						*_hoops_PSACR = (Attribute *)_hoops_HSGA;
					}

					if (BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_HIAAP) &&
						_hoops_SPH->projection == _hoops_GHH) {
						/* _hoops_RRP _hoops_IS _hoops_RGHH _hoops_RGR _hoops_SPHR _hoops_PGGA _hoops_SR _hoops_HHGC _hoops_SCH _hoops_IS *_hoops_GCIS* _hoops_GII _hoops_IRGH _hoops_PRGIA */
						_hoops_RPGIP = true;
					}
					if (BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_PIAAP)) {
						HI_Ident_Matrix (&temp);
						temp.elements[3][0] = _hoops_SPH->target.x;
						temp.elements[3][1] = _hoops_SPH->target.y;
						temp.elements[3][2] = _hoops_SPH->target.z;
						temp._hoops_RAGR = _hoops_PRICR;
						if (temp.elements[3][2] != 0.0f)
							temp._hoops_RAGR |= _hoops_RRICR;
						HI_Copy_Matrix (&_hoops_HSGA->matrix, &_hoops_RHSPR);
						HI_Multiply_Matrices (&temp, &_hoops_RHSPR, &_hoops_HSGA->matrix);
					}
					if (BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_AIAAP)) {
						HI_Ident_Matrix (&temp);
						temp.elements[0][0] = _hoops_SPH->_hoops_CRSS.x;
						temp.elements[0][1] = _hoops_SPH->_hoops_CRSS.y;
						temp.elements[0][2] = _hoops_SPH->_hoops_CRSS.z;
						temp.elements[1][0] = _hoops_SPH->up_vector.x;
						temp.elements[1][1] = _hoops_SPH->up_vector.y;
						temp.elements[1][2] = _hoops_SPH->up_vector.z;
						temp.elements[2][0] = _hoops_SPH->_hoops_IIPCR.x;
						temp.elements[2][1] = _hoops_SPH->_hoops_IIPCR.y;
						temp.elements[2][2] = _hoops_SPH->_hoops_IIPCR.z;
						temp._hoops_CPH = 1.0f;
						temp._hoops_RAGR = _hoops_GRICR |
										_hoops_RRICR;

						HI_Copy_Matrix (&_hoops_HSGA->matrix, &_hoops_RHSPR);
						HI_Multiply_Matrices (&temp, &_hoops_RHSPR, &_hoops_HSGA->matrix);
					}
					if (BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_RIAAP)) {
						float			scale;

						if (_hoops_SPH->projection != _hoops_SSIH) {
							if (_hoops_SPH->_hoops_CSIH >= control->_hoops_ISIH)
								scale = _hoops_SPH->_hoops_SSPA;
							else
								scale = _hoops_SPH->_hoops_ISPA;
						}
						else
							scale = _hoops_IAAA (_hoops_SPH->_hoops_SSPA, _hoops_SPH->_hoops_ISPA);

						scale = scale / 2.0f;

						HI_Figure_Scale_Matrix (scale, scale, scale, &temp);
						HI_Copy_Matrix (&_hoops_HSGA->matrix, &_hoops_RHSPR);
						HI_Multiply_Matrices (&temp, &_hoops_RHSPR, &_hoops_HSGA->matrix);
					}
				}
			}
		}
		else if (_hoops_ASGPR->type == _hoops_CPPIR) {
			_hoops_SPPIR const *		_hoops_RSSPH = (_hoops_SPPIR const *)_hoops_ASGPR;
			int						size = _hoops_RSSPH->count * sizeof (unsigned int);

			if (conditions == null) {
				if ((_hoops_IRCAA = HOOPS_WORLD->_hoops_AGCAA / 32) == 0)
					_hoops_IRCAA = 1;
				ZALLOC_ARRAY (conditions, _hoops_IRCAA, unsigned int);
			}

			_hoops_HSIAA (conditions, _hoops_RSSPH->_hoops_SGCAA, size);
			_hoops_ISIAA (conditions, _hoops_RSSPH->values, size);
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	_hoops_ASGPR = _hoops_SIIAA;
	_hoops_SSAGR(_hoops_ASGPR);

	do {
		_hoops_SSAGR(_hoops_ASGPR->next);

#ifndef DISABLE_STYLE_SEGMENT
		if (_hoops_ASGPR->type == HK_STYLE) {
			if (!BIT (_hoops_SCSPH->_hoops_IPPGR, _hoops_GGCAA(HK_STYLE))) {
				Style *			style = (Style *)_hoops_ASGPR;

				if (_hoops_SCSPH != &_hoops_PCGS) {
					_hoops_RSAI (locks, _hoops_PIGRA, &_hoops_PCGS);
					_hoops_SCSPH = &_hoops_PCGS;
				}

				if (style->_hoops_IGRPR && style->_hoops_IGRPR->_hoops_IPPGR &&
					(style->condition.count == 0 ||
						HI_Condition_Passed (HOOPS_WORLD->_hoops_AGCAA, conditions, &style->condition))) {

					_hoops_PIIS (_hoops_RIGC, style->_hoops_IGRPR->_hoops_IPPGR, _hoops_PSACR, type, locks, _hoops_SACRP, conditions, _hoops_CCSPH, control);
					_hoops_RSAI (locks, _hoops_PIGRA, &_hoops_PCGS);
					/* _hoops_IH _hoops_IRGH _hoops_HCGC _hoops_ARP _hoops_RGR _hoops_IS _hoops_SRCH _hoops_CSIAA '_hoops_PCPAR _hoops_HIH _hoops_HCIAA _hoops_ASIAA' */
					_hoops_HSIAA (&_hoops_PCGS, &_hoops_CIIAA, sizeof (_hoops_PIGRA));
				}
			}
		}
		else
#endif
		if (_hoops_ASGPR->type > type)
			break;

		if (_hoops_ASGPR->type == HK_COLOR_MAP && control != null) {
			if (BIT (_hoops_CCSPH, _hoops_ISCAP))
				_hoops_PGRCA(control)->_hoops_CSIR = (_hoops_RHAH const *)_hoops_ASGPR;
		}

		if (_hoops_ASGPR->type == type) switch (type) {
			/* _hoops_HHH _hoops_AIRC _hoops_PIHA _hoops_SHH _hoops_RPHGA _hoops_GPSPR-_hoops_HPP-_hoops_GPSPR */
			case HK_COLOR: {
				_hoops_SSGI const *			_hoops_ASSPH = (_hoops_SSGI const *)_hoops_ASGPR;
				_hoops_SSGI alter *			color;
				_hoops_RHAH const *		_hoops_CSIR = null;

				if (control != null) {
					if (BIT (_hoops_CCSPH, _hoops_ISCAP))
						_hoops_CSIR = control->_hoops_CSIR;
				}

				if ((color = (_hoops_SSGI *)*_hoops_PSACR) == null) {
					_hoops_ACSGA *		list = HI_Copy_Colors (_hoops_ASSPH->colors, _hoops_CSIR, _hoops_SCSPH);

					if (list != null) {
						ZALLOC (color, _hoops_SSGI);
						color->type = HK_COLOR;
						color->_hoops_HIHI = 1;
						*_hoops_PSACR = (Attribute *)color;
						color->colors = list;
						while (list != null) {
							color->_hoops_GHA |= list->_hoops_GHA;
							list = list->next;
						}
					}
				}
				else
					HI_Merge_Colors (color, _hoops_ASSPH->colors, _hoops_SCSPH, _hoops_CSIR);
			}	break;

			case HK_CALLBACK: if (!BIT (_hoops_SCSPH->_hoops_IPPGR, _hoops_GGCAA(HK_CALLBACK))) {
#ifndef DISABLE_CALLBACKS
				_hoops_GCHIR const *	_hoops_PSSPH = (_hoops_GCHIR const *)_hoops_ASGPR;
				_hoops_GCHIR alter *	callback;

				if ((callback = (_hoops_GCHIR *)*_hoops_PSACR) == null) {
					*_hoops_PSACR = HI_Clone_Attributes (_hoops_RIGC, _hoops_ASGPR, null, false, null);
				}
				else {
					_hoops_IHACR *	old = callback->_hoops_ACHIR;
					callback->_hoops_ACHIR = HI_Merge_Callback_Lists (old, _hoops_PSSPH->_hoops_ACHIR);
					HI_Free_Callback_List (old);
				}
#endif
			}	break;


			case _hoops_CPPIR: {
				_hoops_SPPIR const *		_hoops_RSSPH = (_hoops_SPPIR const *)_hoops_ASGPR;
				_hoops_SPPIR alter *		c;
				int						size = _hoops_RSSPH->count * sizeof (unsigned int);

				if ((c = (_hoops_SPPIR *)*_hoops_PSACR) == null) {
					*_hoops_PSACR = HI_Clone_Attributes (_hoops_RIGC, _hoops_ASGPR, null, false, null);
				}
				else {
					// _hoops_SRPA _hoops_SGSS _hoops_IH _hoops_CCAH _hoops_SSSC _hoops_RH _hoops_PGHC _hoops_RGSR _hoops_SARS'_hoops_RA _hoops_ACPA _hoops_AHCA

					for (int i=0; i<_hoops_RSSPH->count; i++) {
						unsigned int	mask = _hoops_RSSPH->_hoops_SGCAA[i] & ~c->_hoops_SGCAA[i];
						int				index = i * 32;

						while (mask != 0) {
							if ((mask & 1) != 0)
								_hoops_PRRH (HOOPS_WORLD->_hoops_PCIIR[index]);

							mask >>= 1;
							++index;
						}
					}

					_hoops_ISIAA (c->_hoops_SGCAA, _hoops_RSSPH->_hoops_SGCAA, size);
					_hoops_HSIAA (c->values, _hoops_RSSPH->_hoops_SGCAA, size);
					_hoops_ISIAA (c->values, _hoops_RSSPH->values, size);
				}
			}	break;


			case HK_WINDOW: if (!BIT (_hoops_SCSPH->_hoops_IPPGR, _hoops_GGCAA(HK_WINDOW))) {
				Window const *		_hoops_HSSPH = (Window const *)_hoops_ASGPR;
				Window alter *		w;

				if ((w = (Window *)*_hoops_PSACR) == null) {
					*_hoops_PSACR = HI_Clone_Attributes (_hoops_RIGC, _hoops_ASGPR, null, false, null);
				}
				else {
					float	scale = (w->_hoops_RCHS.right - w->_hoops_RCHS.left) * 0.5f;
					float	translate = (w->_hoops_RCHS.right + w->_hoops_RCHS.left) * 0.5f;

					w->_hoops_RCHS.left = _hoops_HSSPH->_hoops_RCHS.left * scale + translate;
					w->_hoops_RCHS.right = _hoops_HSSPH->_hoops_RCHS.right * scale + translate;

					scale = (w->_hoops_RCHS.top - w->_hoops_RCHS.bottom) * 0.5f;
					translate = (w->_hoops_RCHS.top + w->_hoops_RCHS.bottom) * 0.5f;

					w->_hoops_RCHS.bottom = _hoops_HSSPH->_hoops_RCHS.bottom * scale + translate;
					w->_hoops_RCHS.top = _hoops_HSSPH->_hoops_RCHS.top * scale + translate;
				}
			}	break;

			case HK_TEXT_FONT: if (!BIT (_hoops_SCSPH->_hoops_IPPGR, _hoops_GGCAA(HK_TEXT_FONT))) {
				_hoops_AGPIR const *		_hoops_ISSPH = (_hoops_AGPIR const *)_hoops_ASGPR;
				_hoops_AGPIR *				_hoops_PGPIR;

				if ((_hoops_PGPIR = (_hoops_AGPIR *)*_hoops_PSACR) == null) {
					*_hoops_PSACR = HI_Clone_Attributes (_hoops_RIGC, _hoops_ASGPR, null, false, null);
				}
				else {
					if (_hoops_ISSPH->_hoops_HGPIR != null) {
						if (_hoops_PGPIR->_hoops_HGPIR != null) {
							_hoops_IGPIR *	name = _hoops_PGPIR->_hoops_HGPIR;
							_hoops_IGPIR *	next;
							do {
								next = name->next;
								if (name->_hoops_SSSGP == GFN_SPECIFIED)
									_hoops_RGAIR (name->specified);
								FREE (name, _hoops_IGPIR);
							} while ((name = next) != null);
						}
						_hoops_PGPIR->_hoops_HGPIR = HI_Copy_Font_Names (_hoops_ISSPH->_hoops_HGPIR);
					}

					if (BIT(_hoops_ISSPH->_hoops_HAICA, _hoops_RPPAP)) {
						_hoops_PGPIR->_hoops_GHGRP = _hoops_ISSPH->_hoops_GHGRP;
						_hoops_PGPIR->size = _hoops_ISSPH->size;
					}

					if (BIT(_hoops_ISSPH->_hoops_HAICA, _hoops_APPAP)) {
						_hoops_PGPIR->_hoops_SSPAP = _hoops_ISSPH->_hoops_SSPAP;
						_hoops_PGPIR->_hoops_ACPAP = _hoops_ISSPH->_hoops_ACPAP;
					}

					if (BIT(_hoops_ISSPH->_hoops_HAICA, _hoops_CPPAP)) {
						_hoops_PGPIR->_hoops_PCPAP = _hoops_ISSPH->_hoops_PCPAP;
						_hoops_PGPIR->_hoops_GGHAP = _hoops_ISSPH->_hoops_GGHAP;
					}

					if (BIT(_hoops_ISSPH->_hoops_HAICA, _hoops_GHPAP)) {
						_hoops_PGPIR->_hoops_HCPAP = _hoops_ISSPH->_hoops_HCPAP;
						_hoops_PGPIR->_hoops_RGHAP = _hoops_ISSPH->_hoops_RGHAP;
					}

					if (BIT(_hoops_ISSPH->_hoops_HAICA, _hoops_IIPAP))
						_hoops_PGPIR->_hoops_SGHAP = _hoops_ISSPH->_hoops_SGHAP;

					if (BIT(_hoops_ISSPH->_hoops_HAICA, _hoops_HPPAP))
						_hoops_PGPIR->rotation = _hoops_ISSPH->rotation;

					if (BIT(_hoops_ISSPH->_hoops_HAICA, _hoops_IPPAP))
						_hoops_PGPIR->width_scale = _hoops_ISSPH->width_scale;

					if (BIT(_hoops_ISSPH->_hoops_HAICA, _hoops_RHPAP))
						_hoops_PGPIR->_hoops_ICPAP = _hoops_ISSPH->_hoops_ICPAP;

					if (BIT(_hoops_ISSPH->_hoops_HAICA, _hoops_SPPAP))
						_hoops_PGPIR->_hoops_IPGRP = _hoops_ISSPH->_hoops_IPGRP;

					if (BIT(_hoops_ISSPH->_hoops_HAICA, _hoops_PPPAP))
						_hoops_PGPIR->transform = _hoops_ISSPH->transform;

					if (BIT(_hoops_ISSPH->_hoops_HAICA, _hoops_HIPAP)) {
						if (_hoops_ISSPH->_hoops_ISPAP[0] != -1)
							_hoops_PGPIR->_hoops_ISPAP[0] = _hoops_ISSPH->_hoops_ISPAP[0];
						if (_hoops_ISSPH->_hoops_ISPAP[1] != -1)
							_hoops_PGPIR->_hoops_ISPAP[1] = _hoops_ISSPH->_hoops_ISPAP[1];
						if (_hoops_ISSPH->_hoops_AGHAP != _hoops_SHGRP) {
							_hoops_PGPIR->_hoops_CCPAP = _hoops_ISSPH->_hoops_CCPAP;
							_hoops_PGPIR->_hoops_AGHAP = _hoops_ISSPH->_hoops_AGHAP;
						}
					}

					if (BIT(_hoops_ISSPH->_hoops_HAICA, _hoops_CIPAP)) {
						if (_hoops_ISSPH->_hoops_CSPAP[0] != -1)
							_hoops_PGPIR->_hoops_CSPAP[0] = _hoops_ISSPH->_hoops_CSPAP[0];
						if (_hoops_ISSPH->_hoops_CSPAP[1] != -1)
							_hoops_PGPIR->_hoops_CSPAP[1] = _hoops_ISSPH->_hoops_CSPAP[1];
						if (_hoops_ISSPH->_hoops_PGHAP != _hoops_SHGRP) {
							_hoops_PGPIR->_hoops_SCPAP = _hoops_ISSPH->_hoops_SCPAP;
							_hoops_PGPIR->_hoops_PGHAP = _hoops_ISSPH->_hoops_PGHAP;
						}
					}

					_hoops_PGPIR->_hoops_HAICA |= _hoops_ISSPH->_hoops_HAICA;
					_hoops_PGPIR->_hoops_CPGRP &= ~_hoops_ISSPH->_hoops_HAICA;
					_hoops_PGPIR->_hoops_CPGRP |= _hoops_ISSPH->_hoops_HAICA &
										_hoops_ISSPH->_hoops_CPGRP;
				}
			}	break;

			case HK_DRIVER_OPTIONS: if (!BIT (_hoops_SCSPH->_hoops_IPPGR, _hoops_GGCAA(HK_DRIVER_OPTIONS))) {
				_hoops_GAPIR const *		options = (_hoops_GAPIR const *)_hoops_ASGPR;
				_hoops_GAPIR alter *		d;
				int							count;

				if ((d = (_hoops_GAPIR *)*_hoops_PSACR) == null) {
					*_hoops_PSACR = HI_Clone_Attributes (_hoops_RIGC, _hoops_ASGPR, null, false, null);
				}
				else {
					if (BIT (options->_hoops_HCARP, _hoops_ICARP)) {
						d->_hoops_IRARR = options->_hoops_IRARR;

						if (d->_hoops_APPIR != options->_hoops_APPIR &&
							d->_hoops_APPIR != 0)
							FREE_ARRAY (d->_hoops_RPPIR, d->_hoops_APPIR, int);

						d->_hoops_APPIR = options->_hoops_APPIR;
						if ((count = d->_hoops_APPIR) > 0) {
							ALLOC_ARRAY (d->_hoops_RPPIR, count, int);
							_hoops_AIGA (options->_hoops_RPPIR, count, int, d->_hoops_RPPIR);
						}
						else
							d->_hoops_RPPIR = null;
					}

					if (BIT (options->_hoops_HCARP, _hoops_SCARP))
						d->_hoops_APASR = options->_hoops_APASR;

					if (BIT (options->_hoops_HCARP, _hoops_GSARP)) {
						d->_hoops_GCPRP[0] = options->_hoops_GCPRP[0];
						d->_hoops_GCPRP[1] = options->_hoops_GCPRP[1];
						d->_hoops_GCPRP[2] = options->_hoops_GCPRP[2];
					}

					if (BIT (options->_hoops_HCARP, _hoops_CCARP))
						d->_hoops_CRHRP = options->_hoops_CRHRP;

					if (BIT (options->_hoops_HCARP, _hoops_RSARP))
						d->_hoops_IGHRP = options->_hoops_IGHRP;

					if (BIT (options->_hoops_HCARP, _hoops_ARPRP))
						d->_hoops_ARHRP = options->_hoops_ARHRP;

					if (BIT (options->_hoops_HCARP, _hoops_HRPRP))
						_hoops_AIGA (options->_hoops_IAHRP, _hoops_HAHRP, int, d->_hoops_IAHRP);

					if (BIT (options->_hoops_HCARP, _hoops_IRPRP))
						d->_hoops_PPHRP = options->_hoops_PPHRP;

					if (BIT (options->_hoops_HCARP, _hoops_ASARP))
						d->_hoops_RCPRP = options->_hoops_RCPRP;

					if (BIT (options->_hoops_HCARP, _hoops_PSARP))
						d->_hoops_ACPRP = options->_hoops_ACPRP;

					if (BIT (options->_hoops_HCARP, _hoops_HSARP)) {
						d->_hoops_PCPRP[0][0] = options->_hoops_PCPRP[0][0];
						d->_hoops_PCPRP[0][1] = options->_hoops_PCPRP[0][1];
						d->_hoops_PCPRP[1][0] = options->_hoops_PCPRP[1][0];
						d->_hoops_PCPRP[1][1] = options->_hoops_PCPRP[1][1];
						d->_hoops_PCPRP[2][0] = options->_hoops_PCPRP[2][0];
						d->_hoops_PCPRP[2][1] = options->_hoops_PCPRP[2][1];
					}

					if (BIT (options->_hoops_HCARP, _hoops_ISARP))
						d->_hoops_AAPSR = options->_hoops_AAPSR;

					if (BIT (options->_hoops_HCARP, _hoops_CSARP))
						d->_hoops_GSHSR = options->_hoops_GSHSR;

					if (BIT (options->_hoops_HCARP, _hoops_SSARP)) {
						d->_hoops_SPHSR.x = options->_hoops_SPHSR.x;
						d->_hoops_SPHSR.y = options->_hoops_SPHSR.y;
					}

					if (BIT (options->_hoops_HCARP, _hoops_GGPRP))
						d->_hoops_SHSHA = options->_hoops_SHSHA;

					if (BIT (options->_hoops_HCARP, _hoops_RGPRP)) {
						d->_hoops_HCPRP.left = options->_hoops_HCPRP.left;
						d->_hoops_HCPRP.right = options->_hoops_HCPRP.right;
						d->_hoops_HCPRP.bottom = options->_hoops_HCPRP.bottom;
						d->_hoops_HCPRP.top = options->_hoops_HCPRP.top;
					}

					if (BIT (options->_hoops_HCARP, _hoops_PGPRP))
						d->_hoops_GSPRP = options->_hoops_GSPRP;

					if (BIT (options->_hoops_HCARP, _hoops_IGPRP))
						d->_hoops_GCHSR = options->_hoops_GCHSR;

					if (BIT (options->_hoops_HCARP, _hoops_CGPRP))
						d->_hoops_ISPRP = options->_hoops_ISPRP;

					if (BIT (options->_hoops_HCARP, _hoops_HGPRP))
						d->_hoops_RCHSR = options->_hoops_RCHSR;

					if (BIT (options->_hoops_HCARP, _hoops_PRPRP))
						d->_hoops_CSPRP = options->_hoops_CSPRP;

					if (BIT (options->_hoops_HCARP, _hoops_SGPRP))
						d->_hoops_AGHRP = options->_hoops_AGHRP;

					if (BIT (options->_hoops_HCARP, _hoops_RRPRP))
						d->_hoops_GHHSR = options->_hoops_GHHSR;

					if (BIT (options->_hoops_HCARP, _hoops_AGPRP)) {
						_hoops_RGAIR (d->_hoops_IAPIR);
						HI_Copy_Name (&options->_hoops_IAPIR, &d->_hoops_IAPIR);
					}

					if (BIT (options->_hoops_HCARP, _hoops_SRPRP)) {
						d->_hoops_AIPGA = options->_hoops_AIPGA;
					}

					if (BIT (options->_hoops_HCARP, _hoops_GRPRP)) {
						HI_Free_Name_List(d->_hoops_HAPIR);
						d->_hoops_HAPIR = HI_Copy_Name_List (options->_hoops_HAPIR);
					}

					if (BIT (options->_hoops_HCARP, _hoops_RAPRP))
						d->_hoops_HSPRP = options->_hoops_HSPRP;

					if (BIT (options->_hoops_HCARP, _hoops_GAPRP)) {
						if (d->_hoops_PPPIR)
							_hoops_HPRH (d->_hoops_PPPIR);
						d->_hoops_PPPIR = options->_hoops_PPPIR;
						if (options->_hoops_PPPIR)
							_hoops_PRRH (options->_hoops_PPPIR);
					}

					if (BIT (options->_hoops_HCARP, _hoops_PAPRP)) {
						d->_hoops_HSHRP = options->_hoops_HSHRP;
					}

					if (BIT (options->_hoops_HCARP, _hoops_CRPRP)) {
						if (d->_hoops_SAPIR) {
							HI_Free_Font_Names (d->_hoops_SAPIR);
							d->_hoops_SAPIR = null;
						}

						if (BIT (options->_hoops_HCARP, _hoops_CRPRP))
							d->_hoops_SAPIR = HI_Copy_Font_Names(options->_hoops_SAPIR);
					}


					if (BIT (options->_hoops_HCARP, _hoops_AAPRP)) {
						if (d->_hoops_GPPIR) {
							HI_Free_Font_Names (d->_hoops_GPPIR);
							d->_hoops_GPPIR = null;
						}

						if (BIT (options->_hoops_HCARP, _hoops_AAPRP))
							d->_hoops_GPPIR = HI_Copy_Font_Names(options->_hoops_GPPIR);
					}

					if (BIT (options->_hoops_IAPRP, _hoops_AIPRP)) {
						if (BIT (options->_hoops_AHHRP.mask, _hoops_CPHRP))
							d->_hoops_AHHRP._hoops_GAHP = options->_hoops_AHHRP._hoops_GAHP;
						d->_hoops_AHHRP.mask |= options->_hoops_AHHRP.mask;
						d->_hoops_AHHRP.value &= ~options->_hoops_AHHRP.mask;
						d->_hoops_AHHRP.value |= options->_hoops_AHHRP.value & options->_hoops_AHHRP.mask;
					}

					if (BIT (options->_hoops_IAPRP, _hoops_PIPRP)) {
						if (BIT (options->_hoops_AIHRP.mask, _hoops_HHHRP))
							d->_hoops_AIHRP._hoops_GIGP = options->_hoops_AIHRP._hoops_GIGP;
						d->_hoops_AIHRP.mask |= options->_hoops_AIHRP.mask;
						d->_hoops_AIHRP.value &= ~options->_hoops_AIHRP.mask;
						d->_hoops_AIHRP.value |= options->_hoops_AIHRP.value & options->_hoops_AIHRP.mask;
					}

					if (BIT (options->_hoops_IAPRP, _hoops_HIPRP)) {
						if (BIT (options->_hoops_RGSH.mask, _hoops_HIHRP))
							d->_hoops_RGSH._hoops_SHGP = options->_hoops_RGSH._hoops_SHGP;
						if (BIT (options->_hoops_RGSH.mask, _hoops_IIHRP))
							d->_hoops_RGSH._hoops_HGGGR = options->_hoops_RGSH._hoops_HGGGR;
						d->_hoops_RGSH.mask |= options->_hoops_RGSH.mask;
						d->_hoops_RGSH.value &= ~options->_hoops_RGSH.mask;
						d->_hoops_RGSH.value |= options->_hoops_RGSH.value & options->_hoops_RGSH.mask;
					}

					if (BIT (options->_hoops_IAPRP, _hoops_IIPRP)) {
						if (BIT (options->_hoops_ASHRP.mask, _hoops_PCHRP))
							d->_hoops_ASHRP._hoops_GSHRP = options->_hoops_ASHRP._hoops_GSHRP;
						if (BIT (options->_hoops_ASHRP.mask, _hoops_HCHRP))
							d->_hoops_ASHRP._hoops_RSHRP = options->_hoops_ASHRP._hoops_RSHRP;
						if (BIT (options->_hoops_ASHRP.mask, _hoops_ICHRP))
							d->_hoops_ASHRP._hoops_SHGP = options->_hoops_ASHRP._hoops_SHGP;
						d->_hoops_ASHRP.mask |= options->_hoops_ASHRP.mask;
						d->_hoops_ASHRP.value &= ~options->_hoops_ASHRP.mask;
						d->_hoops_ASHRP.value |= options->_hoops_ASHRP.value & options->_hoops_ASHRP.mask;
					}

					d->_hoops_IAICA |= options->_hoops_IAICA;
					d->_hoops_HCARP &= ~options->_hoops_IAICA;
					d->_hoops_HCARP |= options->_hoops_HCARP & options->_hoops_IAICA;

					d->_hoops_HAICA |= options->_hoops_HAICA;
					d->_hoops_IAPRP &= ~options->_hoops_HAICA;
					d->_hoops_IAPRP |= options->_hoops_IAPRP & options->_hoops_HAICA;
				}
			}	break;

			case HK_USER_OPTIONS: if (!BIT (_hoops_SCSPH->_hoops_IPPGR, _hoops_GGCAA(HK_USER_OPTIONS))) {
				_hoops_HPPIR const *		_hoops_RCGIP = (_hoops_HPPIR const *)_hoops_ASGPR;
				_hoops_HPPIR alter *		_hoops_SPSAA;

				// _hoops_GRH _hoops_CHCRA _hoops_RRI _hoops_PII _hoops_ISHP _hoops_CRARH
				if ((_hoops_SPSAA = (_hoops_HPPIR *)*_hoops_PSACR) == null) {
					ZALLOC (_hoops_SPSAA, _hoops_HPPIR);
					_hoops_SPSAA->type = HK_USER_OPTIONS;
					_hoops_SPSAA->_hoops_HIHI = 1;
					*_hoops_PSACR = (Attribute *)_hoops_SPSAA;

					_hoops_SPSAA->_hoops_IGGSA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_CGGSA)(_hoops_RIGC->memory_pool);

					if (_hoops_RCGIP->_hoops_IGGSA == null) {
						_hoops_PRRH(_hoops_RCGIP);
						_hoops_SPSAA->_hoops_IGGSA->AddFirst(_hoops_RCGIP);
					}
					else {
						ASSERT(_hoops_RCGIP->option_list == null);
						ASSERT(_hoops_RCGIP->_hoops_APICA == null);
						ASSERT(_hoops_RCGIP->_hoops_AGGSA == null);
						ASSERT(_hoops_RCGIP->_hoops_HGGSA == null);

						_hoops_HPPIR const * _hoops_HGSGP;
						_hoops_CGGSA::UniqueCursor *	uc = _hoops_RCGIP->_hoops_IGGSA->GetUniqueCursor();
						while ((_hoops_HGSGP = uc->Peek()) != null) {
							ASSERT(_hoops_HGSGP->_hoops_IGGSA == null);
							_hoops_PRRH(_hoops_HGSGP);
							_hoops_SPSAA->_hoops_IGGSA->AddFirst(_hoops_HGSGP);
							uc->Advance();
						}
						delete uc;
					}
				}
				else {
					if (!_hoops_SPSAA->_hoops_IGGSA)
						_hoops_SPSAA->_hoops_IGGSA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_CGGSA)(_hoops_RIGC->memory_pool);

					if (_hoops_RCGIP->_hoops_IGGSA == null) {
						_hoops_HPPIR const *	_hoops_CSSPH = _hoops_SPSAA->_hoops_IGGSA->PeekFirst();

						if (!_hoops_CSSPH ||
							!HI_User_Option_Equal(_hoops_CSSPH, _hoops_RCGIP)) {

							_hoops_PRRH(_hoops_RCGIP);
							_hoops_SPSAA->_hoops_IGGSA->AddFirst(_hoops_RCGIP);
						}
					}
					else {
						ASSERT(_hoops_RCGIP->option_list == null);
						ASSERT(_hoops_RCGIP->_hoops_APICA == null);
						ASSERT(_hoops_RCGIP->_hoops_AGGSA == null);
						ASSERT(_hoops_RCGIP->_hoops_HGGSA == null);

						_hoops_HPPIR const * _hoops_HGSGP;
						_hoops_CGGSA::UniqueCursor *	uc = _hoops_RCGIP->_hoops_IGGSA->GetUniqueCursor();
						while ((_hoops_HGSGP = uc->Peek()) != null) {
							ASSERT(_hoops_HGSGP->_hoops_IGGSA == null);
							_hoops_PRRH(_hoops_HGSGP);
							_hoops_SPSAA->_hoops_IGGSA->AddFirst(_hoops_HGSGP);
							uc->Advance();
						}
						delete uc;
					}
				}
			}	break;

			case HK_MODELLING_MATRIX: if (!BIT (_hoops_SCSPH->_hoops_IPPGR, _hoops_GGCAA(HK_MODELLING_MATRIX))) {
				_hoops_ISGI const *		_hoops_SSSPH = (_hoops_ISGI const *)_hoops_ASGPR;
				_hoops_ISGI alter *		_hoops_CPAI;

				if ((_hoops_CPAI = (_hoops_ISGI *)*_hoops_PSACR) == null) {
					*_hoops_PSACR = HI_Clone_Attributes (_hoops_RIGC, _hoops_ASGPR, null, false, null);
				}
				else {
					_hoops_HRPA	_hoops_RHSPR;
					HI_Copy_Matrix (&_hoops_CPAI->matrix, &_hoops_RHSPR);
					HI_Multiply_Matrices (&_hoops_SSSPH->matrix, &_hoops_RHSPR, &_hoops_CPAI->matrix);
				}
			}	break;

			case HK_HEURISTICS: if (!BIT (_hoops_SCSPH->_hoops_IPPGR, _hoops_GGCAA(HK_HEURISTICS))) {
				_hoops_GHAIR const *		_hoops_GGGHH = (_hoops_GHAIR const *)_hoops_ASGPR;
				_hoops_GHAIR alter *		h;

				if ((h = (_hoops_GHAIR *)*_hoops_PSACR) == null) {
					*_hoops_PSACR = HI_Clone_Attributes (_hoops_RIGC, _hoops_ASGPR, null, false, null);
				}
				else {
					if (BIT (_hoops_GGGHH->value, _hoops_SICIA))
						h->_hoops_GCCIA = _hoops_GGGHH->_hoops_GCCIA;
					if (BIT (_hoops_GGGHH->value, _hoops_SRIRP)) {
						if (BIT (_hoops_GGGHH->_hoops_CCIRP.value, _hoops_HCIRP))
							h->_hoops_CCIRP._hoops_SPHPR = _hoops_GGGHH->_hoops_CCIRP._hoops_SPHPR;
						if (BIT (_hoops_GGGHH->_hoops_CCIRP.value, _hoops_ICIRP))
							h->_hoops_CCIRP.polyline = _hoops_GGGHH->_hoops_CCIRP.polyline;
					}
					if (BIT (_hoops_GGGHH->mask, _hoops_RPIRP))
						h->_hoops_GRCRP = _hoops_GGGHH->_hoops_GRCRP;
					if (BIT (_hoops_GGGHH->mask, _hoops_APIRP))
						h->_hoops_RRCRP = _hoops_GGGHH->_hoops_RRCRP;
					if (BIT (_hoops_GGGHH->mask, _hoops_PPIRP))
						h->_hoops_IRCRP = _hoops_GGGHH->_hoops_IRCRP;
					if (BIT (_hoops_GGGHH->_hoops_APH.value, _hoops_SPIRP)) {
						h->_hoops_APH._hoops_ACIRP = _hoops_GGGHH->_hoops_APH._hoops_ACIRP;
						h->_hoops_APH._hoops_PCIRP = _hoops_GGGHH->_hoops_APH._hoops_PCIRP;
					}
					if (BIT (_hoops_GGGHH->mask, _hoops_RAIRP)) {
						if (BIT (_hoops_GGGHH->_hoops_APH.value, Heur_Culling_EXTENT))
							h->_hoops_APH._hoops_GRGC = _hoops_GGGHH->_hoops_APH._hoops_GRGC;
						if (BIT (_hoops_GGGHH->_hoops_APH.value, _hoops_RIHS))
							h->_hoops_APH._hoops_GCHS = _hoops_GGGHH->_hoops_APH._hoops_GCHS;
						if (BIT (_hoops_GGGHH->_hoops_APH.value, _hoops_AHIRP))
							h->_hoops_APH._hoops_CIIRP = _hoops_GGGHH->_hoops_APH._hoops_CIIRP;
						if (BIT (_hoops_GGGHH->_hoops_APH.value, _hoops_RHIRP))
							h->_hoops_APH._hoops_PCHS = _hoops_GGGHH->_hoops_APH._hoops_PCHS;
						if (BIT (_hoops_GGGHH->_hoops_APH.value, _hoops_HHIRP))
							h->_hoops_APH._hoops_SHHS = _hoops_GGGHH->_hoops_APH._hoops_SHHS;
						if (BIT (_hoops_GGGHH->_hoops_APH.value, _hoops_GHIRP))
							h->_hoops_APH.vector = _hoops_GGGHH->_hoops_APH.vector;
						if (BIT (_hoops_GGGHH->_hoops_APH.value, _hoops_PHIRP))
							h->_hoops_APH._hoops_IIIRP = _hoops_GGGHH->_hoops_APH._hoops_IIIRP;
					}
					if (BIT (_hoops_GGGHH->mask, _hoops_CAIRP)) {
						for (unsigned int i=0; i<_hoops_ISIRP; i++)
							if (BIT (_hoops_GGGHH->_hoops_CSIRP, 1<<i))
								h->_hoops_SSIRP[i] = _hoops_GGGHH->_hoops_SSIRP[i];
						h->_hoops_CSIRP |= _hoops_GGGHH->_hoops_CSIRP;
					}

					h->mask |= _hoops_GGGHH->mask;
					h->value &= ~_hoops_GGGHH->mask;
					h->value |= _hoops_GGGHH->mask &
								_hoops_GGGHH->value;
					h->_hoops_APH.mask |= _hoops_GGGHH->_hoops_APH.mask;
					h->_hoops_APH.value &= ~_hoops_GGGHH->_hoops_APH.mask;
					h->_hoops_APH.value |= _hoops_GGGHH->_hoops_APH.mask &
									 _hoops_GGGHH->_hoops_APH.value;
					h->_hoops_CCIRP.mask |= _hoops_GGGHH->_hoops_CCIRP.mask;
					h->_hoops_CCIRP.value &= ~_hoops_GGGHH->_hoops_CCIRP.mask;
					h->_hoops_CCIRP.value |= _hoops_GGGHH->_hoops_CCIRP.mask &
									 _hoops_GGGHH->_hoops_CCIRP.value;
				}
			}	break;

			case HK_RENDERING_OPTIONS: if (!BIT (_hoops_SCSPH->_hoops_IPPGR, _hoops_GGCAA(HK_RENDERING_OPTIONS))) {
				_hoops_RHAIR const *	_hoops_AHAIR = (_hoops_RHAIR *)_hoops_ASGPR;
				_hoops_RHAIR alter *	_hoops_RGGHH;

				if ((_hoops_RGGHH = (_hoops_RHAIR *)*_hoops_PSACR) == null) {
					*_hoops_PSACR = HI_Clone_Attributes (_hoops_RIGC, _hoops_ASGPR, null, false, null);
				}
				else {
					if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_PARAP))
						_hoops_RGGHH->_hoops_SIRAP = _hoops_AHAIR->_hoops_SIRAP;
					if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_CARAP))
						_hoops_RGGHH->_hoops_RCRAP = _hoops_AHAIR->_hoops_RCRAP;
					if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_PRRAP))
						_hoops_RGGHH->_hoops_IRARR = _hoops_AHAIR->_hoops_IRARR;
					if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_CRRAP))
						_hoops_RGGHH->_hoops_CHIH = _hoops_AHAIR->_hoops_CHIH;
					if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_IPRAP))
						_hoops_RGGHH->_hoops_IGAAP = _hoops_AHAIR->_hoops_IGAAP;
					if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_SARAP))
						_hoops_RGGHH->_hoops_SHIH = _hoops_AHAIR->_hoops_SHIH;
					if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_GPRAP)) {
						if (_hoops_AHAIR->_hoops_GSAAP != -1)
							_hoops_RGGHH->_hoops_GSAAP = _hoops_AHAIR->_hoops_GSAAP;
						if (_hoops_AHAIR->_hoops_RSAAP != -1)
							_hoops_RGGHH->_hoops_RSAAP = _hoops_AHAIR->_hoops_RSAAP;
					}

					if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_IRRAP))
						_hoops_RGGHH->_hoops_PSAAP = _hoops_AHAIR->_hoops_PSAAP;

					if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_GSIAA)) {
						if (_hoops_RGGHH->locks == null)
							ZALLOC (_hoops_RGGHH->locks, _hoops_CCAIR);

						if (BIT (_hoops_AHAIR->_hoops_RSIAA, _hoops_GSIAA)) {
							/* _hoops_HASC _hoops_CCAH _hoops_AAHS _hoops_HRP */
							_hoops_ISIAA (&_hoops_RGGHH->locks->normal.mask, &_hoops_AHAIR->locks->normal.mask, sizeof (_hoops_PIGRA));
							_hoops_HSIAA (&_hoops_RGGHH->locks->normal.value, &_hoops_AHAIR->locks->normal.mask, sizeof (_hoops_PIGRA));
							_hoops_ISIAA (&_hoops_RGGHH->locks->normal.value, &_hoops_AHAIR->locks->normal.value, sizeof (_hoops_PIGRA));
						}
						else {
							/* _hoops_SSIAA _hoops_CPS */
							ZERO_STRUCT (&_hoops_RGGHH->locks->normal.mask, _hoops_PIGRA);
							ZERO_STRUCT (&_hoops_RGGHH->locks->normal.value, _hoops_PIGRA);
						}
					}
					if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_RGRAP)) {
						if (_hoops_RGGHH->locks == null)
							ZALLOC (_hoops_RGGHH->locks, _hoops_CCAIR);

						_hoops_ISIAA (&_hoops_RGGHH->locks->_hoops_SACRP.mask, &_hoops_AHAIR->locks->_hoops_SACRP.mask, sizeof (_hoops_PIGRA));
						_hoops_ISIAA (&_hoops_RGGHH->locks->_hoops_SACRP.value, &_hoops_AHAIR->locks->_hoops_SACRP.value, sizeof (_hoops_PIGRA));
					}

					if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_SRRAP))
						_hoops_RGGHH->_hoops_SRI = _hoops_AHAIR->_hoops_SRI;

					_hoops_RGGHH->_hoops_HGICA |= _hoops_AHAIR->_hoops_HGICA;
					_hoops_RGGHH->_hoops_PGICA &= ~_hoops_AHAIR->_hoops_HGICA;
					_hoops_RGGHH->_hoops_PGICA |= _hoops_AHAIR->_hoops_HGICA &
											   _hoops_AHAIR->_hoops_PGICA;

					if (_hoops_AHAIR->_hoops_HHAIR != null) {
						if (_hoops_RGGHH->_hoops_HHAIR == null)
							ZALLOC(_hoops_RGGHH->_hoops_HHAIR, _hoops_RIAIR);

						_hoops_RGGHH->_hoops_HHAIR->_hoops_IHAIR.mask |= _hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR.mask;
						_hoops_RGGHH->_hoops_HHAIR->_hoops_IHAIR.value &= ~_hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR.mask;
						_hoops_RGGHH->_hoops_HHAIR->_hoops_IHAIR.value |= _hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR.mask &
												   _hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR.value;

						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR.mask, _hoops_SCSRP))
							_hoops_RGGHH->_hoops_HHAIR->_hoops_IHAIR._hoops_GRCR = _hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR._hoops_GRCR;
						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR.mask, _hoops_ICSRP)) {
							_hoops_RGGHH->_hoops_HHAIR->_hoops_IHAIR._hoops_HCIR[0] = _hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR._hoops_HCIR[0];
							_hoops_RGGHH->_hoops_HHAIR->_hoops_IHAIR._hoops_HCIR[1] = _hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR._hoops_HCIR[1];
						}
						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR.mask, _hoops_GSSRP)) {
							_hoops_RGAIR (_hoops_RGGHH->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR);
							HI_Copy_Name(&_hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR,
										 &_hoops_RGGHH->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR);
						}

						if (BIT (_hoops_AHAIR->_hoops_RRRAP, _hoops_HPH)) {
							_hoops_RGGHH->_hoops_HHAIR->_hoops_CRIR.hither = _hoops_AHAIR->_hoops_HHAIR->_hoops_CRIR.hither;
							_hoops_RGGHH->_hoops_HHAIR->_hoops_CRIR.yon = _hoops_AHAIR->_hoops_HHAIR->_hoops_CRIR.yon;
						}

						_hoops_RGGHH->_hoops_HHAIR->_hoops_PRIGA.mask |= _hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.mask;
						_hoops_RGGHH->_hoops_HHAIR->_hoops_PRIGA.value &= ~_hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.mask;
						_hoops_RGGHH->_hoops_HHAIR->_hoops_PRIGA.value |= _hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.mask &
							_hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.value;
						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.mask, _hoops_RSSRP))
							_hoops_RGGHH->_hoops_HHAIR->_hoops_PRIGA.level = _hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.level;
						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.mask, _hoops_HSSRP))
							_hoops_RGGHH->_hoops_HHAIR->_hoops_PRIGA._hoops_SRIGA = _hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA._hoops_SRIGA;
						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.mask, _hoops_PSSRP))
							_hoops_RGGHH->_hoops_HHAIR->_hoops_PRIGA.tolerance = _hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.tolerance;

						_hoops_RGGHH->_hoops_HHAIR->_hoops_GHSS.mask |= _hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask;
						_hoops_RGGHH->_hoops_HHAIR->_hoops_GHSS.value &= ~_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask;
						_hoops_RGGHH->_hoops_HHAIR->_hoops_GHSS.value |= _hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask &
							_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.value;

						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_PGGAP))
							_hoops_RGGHH->_hoops_HHAIR->_hoops_GHSS._hoops_RGP = _hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS._hoops_RGP;
						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_IGGAP))
							_hoops_RGGHH->_hoops_HHAIR->_hoops_GHSS.plane = _hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.plane;
						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_CGGAP))
							_hoops_RGGHH->_hoops_HHAIR->_hoops_GHSS.light = _hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.light;
						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_SGGAP)) {
							_hoops_RGAIR (_hoops_RGGHH->_hoops_HHAIR->_hoops_GHSS.color.name);
							HI_Copy_Name (&_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.color.name,
								&_hoops_RGGHH->_hoops_HHAIR->_hoops_GHSS.color.name);
							_hoops_RGGHH->_hoops_HHAIR->_hoops_GHSS.color.rgb = _hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.color.rgb;
						}
						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_GRGAP))
							_hoops_RGGHH->_hoops_HHAIR->_hoops_GHSS._hoops_IRIR = _hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS._hoops_IRIR;
						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_RRGAP))
							_hoops_RGGHH->_hoops_HHAIR->_hoops_GHSS._hoops_HAP = _hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS._hoops_HAP;
						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_ARGAP))
							_hoops_RGGHH->_hoops_HHAIR->_hoops_GHSS._hoops_IGGGR = _hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS._hoops_IGGGR;

						_hoops_RGGHH->_hoops_HHAIR->_hoops_HRR.mask |= _hoops_AHAIR->_hoops_HHAIR->_hoops_HRR.mask;
						_hoops_RGGHH->_hoops_HHAIR->_hoops_HRR.value &= ~_hoops_AHAIR->_hoops_HHAIR->_hoops_HRR.mask;
						_hoops_RGGHH->_hoops_HHAIR->_hoops_HRR.value |= _hoops_AHAIR->_hoops_HHAIR->_hoops_HRR.mask &
							_hoops_AHAIR->_hoops_HHAIR->_hoops_HRR.value;

						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_HRR.mask, _hoops_PAGAP))
							_hoops_RGGHH->_hoops_HHAIR->_hoops_HRR._hoops_HAP = _hoops_AHAIR->_hoops_HHAIR->_hoops_HRR._hoops_HAP;
						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_HRR.mask, _hoops_HAGAP))
							_hoops_RGGHH->_hoops_HHAIR->_hoops_HRR._hoops_CAP = _hoops_AHAIR->_hoops_HHAIR->_hoops_HRR._hoops_CAP;

						_hoops_RGGHH->_hoops_HHAIR->_hoops_RHGGR.mask |= _hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.mask;
						_hoops_RGGHH->_hoops_HHAIR->_hoops_RHGGR.value &= ~_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.mask;
						_hoops_RGGHH->_hoops_HHAIR->_hoops_RHGGR.value |= _hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.mask &
							_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.value;

						_hoops_RGGHH->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.mask |= _hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.mask;
						_hoops_RGGHH->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.value &= ~_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.mask;
						_hoops_RGGHH->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.value |= _hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.mask &
							_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.value;

						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_GPGAP))
							_hoops_RGGHH->_hoops_HHAIR->_hoops_RHGGR.plane = _hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.plane;
						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_RPGAP))
							_hoops_RGGHH->_hoops_HHAIR->_hoops_RHGGR._hoops_IRIR = _hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR._hoops_IRIR;
						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_HPGAP))
							_hoops_RGGHH->_hoops_HHAIR->_hoops_RHGGR._hoops_IGGGR = _hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR._hoops_IGGGR;
						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_PPGAP)) {
							_hoops_RGGHH->_hoops_HHAIR->_hoops_RHGGR.hither = _hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.hither;
							_hoops_RGGHH->_hoops_HHAIR->_hoops_RHGGR.yon = _hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.yon;
						}

						if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_PPRAP)) {
							_hoops_RGGHH->_hoops_HHAIR->_hoops_HRGA = _hoops_AHAIR->_hoops_HHAIR->_hoops_HRGA;
							_hoops_RSAI (&_hoops_AHAIR->_hoops_HHAIR->_hoops_HRGA, Vector, &_hoops_RGGHH->_hoops_HHAIR->_hoops_HRGA);
						}
					}

					_hoops_RGGHH->_hoops_SSHCA.mask |= _hoops_AHAIR->_hoops_SSHCA.mask;
					_hoops_RGGHH->_hoops_SSHCA.value &= ~_hoops_AHAIR->_hoops_SSHCA.mask;
					_hoops_RGGHH->_hoops_SSHCA.value |= _hoops_AHAIR->_hoops_SSHCA.mask &
												_hoops_AHAIR->_hoops_SSHCA.value;
					if (BIT (_hoops_AHAIR->_hoops_SSHCA.mask, _hoops_RAAAP))
						_hoops_RGGHH->_hoops_SSHCA.style = _hoops_AHAIR->_hoops_SSHCA.style;
					if (BIT (_hoops_AHAIR->_hoops_SSHCA.mask, _hoops_AAAAP))
						_hoops_RGGHH->_hoops_SSHCA._hoops_SRI = _hoops_AHAIR->_hoops_SSHCA._hoops_SRI;

					_hoops_RGGHH->_hoops_RGICA.mask |= _hoops_AHAIR->_hoops_RGICA.mask;
					_hoops_RGGHH->_hoops_RGICA.value &= ~_hoops_AHAIR->_hoops_RGICA.mask;
					_hoops_RGGHH->_hoops_RGICA.value |= _hoops_AHAIR->_hoops_RGICA.mask &
												_hoops_AHAIR->_hoops_RGICA.value;
					if (BIT (_hoops_AHAIR->_hoops_RGICA.mask, _hoops_CPAAP))
						_hoops_RGGHH->_hoops_RGICA._hoops_GHAAP = _hoops_AHAIR->_hoops_RGICA._hoops_GHAAP;
					if (BIT (_hoops_AHAIR->_hoops_RGICA.mask, _hoops_HPAAP))
						_hoops_RGGHH->_hoops_RGICA._hoops_SPAAP = _hoops_AHAIR->_hoops_RGICA._hoops_SPAAP;


					_hoops_RGGHH->_hoops_CHP.mask |= _hoops_AHAIR->_hoops_CHP.mask;
					_hoops_RGGHH->_hoops_CHP.value &= ~_hoops_AHAIR->_hoops_CHP.mask;
					_hoops_RGGHH->_hoops_CHP.value |= _hoops_AHAIR->_hoops_CHP.mask &
												   _hoops_AHAIR->_hoops_CHP.value;

					if (_hoops_AHAIR->_hoops_AIAIR != null) {
						if (_hoops_RGGHH->_hoops_AIAIR == null)
							ZALLOC(_hoops_RGGHH->_hoops_AIAIR, _hoops_HIAIR);

						if (BIT (_hoops_AHAIR->_hoops_AIAIR->mask, _hoops_RPCRP)) {
							_hoops_RGAIR(_hoops_RGGHH->_hoops_AIAIR->_hoops_PIAIR);
							HI_Copy_Name(&_hoops_AHAIR->_hoops_AIAIR->_hoops_PIAIR, &_hoops_RGGHH->_hoops_AIAIR->_hoops_PIAIR);
							_hoops_RGGHH->_hoops_AIAIR->_hoops_HHCRP = _hoops_AHAIR->_hoops_AIAIR->_hoops_HHCRP;
						}
						if (BIT (_hoops_AHAIR->_hoops_AIAIR->mask, _hoops_GHCRP)) {
							_hoops_RGGHH->_hoops_AIAIR->weight.value = _hoops_AHAIR->_hoops_AIAIR->weight.value;
							_hoops_RGGHH->_hoops_AIAIR->weight._hoops_HHP = _hoops_AHAIR->_hoops_AIAIR->weight._hoops_HHP;
						}
						if (BIT (_hoops_AHAIR->_hoops_AIAIR->mask, _hoops_SPCRP)) {
							_hoops_RGGHH->_hoops_AIAIR->color.red = _hoops_AHAIR->_hoops_AIAIR->color.red;
							_hoops_RGGHH->_hoops_AIAIR->color.green = _hoops_AHAIR->_hoops_AIAIR->color.green;
							_hoops_RGGHH->_hoops_AIAIR->color.blue = _hoops_AHAIR->_hoops_AIAIR->color.blue;
						}
						if (BIT (_hoops_AHAIR->_hoops_AIAIR->mask, _hoops_APCRP))
							_hoops_RGGHH->_hoops_AIAIR->_hoops_IHCRP = _hoops_AHAIR->_hoops_AIAIR->_hoops_IHCRP;
						if (BIT (_hoops_AHAIR->_hoops_AIAIR->mask, _hoops_PPCRP))
							_hoops_RGGHH->_hoops_AIAIR->_hoops_CHIH = _hoops_AHAIR->_hoops_AIAIR->_hoops_CHIH;
						if (BIT (_hoops_AHAIR->_hoops_AIAIR->mask, _hoops_PHCRP))
							_hoops_RGGHH->_hoops_AIAIR->_hoops_CHCRP = _hoops_AHAIR->_hoops_AIAIR->_hoops_CHCRP;

						_hoops_RGGHH->_hoops_AIAIR->mask |= _hoops_AHAIR->_hoops_AIAIR->mask;
						_hoops_RGGHH->_hoops_AIAIR->value &= ~_hoops_AHAIR->_hoops_AIAIR->mask;
						_hoops_RGGHH->_hoops_AIAIR->value |= _hoops_AHAIR->_hoops_AIAIR->mask & _hoops_AHAIR->_hoops_AIAIR->value;
					}

					if (_hoops_AHAIR->_hoops_IIAIR != null) {
						if (_hoops_RGGHH->_hoops_IIAIR == null)
							ZALLOC(_hoops_RGGHH->_hoops_IIAIR, _hoops_ICAIR);

						if (ANYBIT (_hoops_AHAIR->_hoops_IIAIR->mask, _hoops_RICRP|_hoops_HICRP)) {
							_hoops_RGGHH->_hoops_IIAIR->_hoops_RGP.mask |= _hoops_AHAIR->_hoops_IIAIR->_hoops_RGP.mask;
							_hoops_RGGHH->_hoops_IIAIR->_hoops_RGP.value &= ~_hoops_AHAIR->_hoops_IIAIR->_hoops_RGP.mask;
							_hoops_RGGHH->_hoops_IIAIR->_hoops_RGP.value |= _hoops_AHAIR->_hoops_IIAIR->_hoops_RGP.mask &
																		_hoops_AHAIR->_hoops_IIAIR->_hoops_RGP.value;
						}
						if (BIT (_hoops_AHAIR->_hoops_IIAIR->mask, _hoops_AICRP)) {
							_hoops_RGGHH->_hoops_IIAIR->_hoops_CCCRP = _hoops_AHAIR->_hoops_IIAIR->_hoops_CCCRP;
							_hoops_RGGHH->_hoops_IIAIR->scale = _hoops_AHAIR->_hoops_IIAIR->scale;
							_hoops_RGGHH->_hoops_IIAIR->translate = _hoops_AHAIR->_hoops_IIAIR->translate;
						}

						if (BIT (_hoops_AHAIR->_hoops_IIAIR->mask, _hoops_IICRP)) {
							if (_hoops_RGGHH->_hoops_IIAIR->_hoops_CIAIR != 0)
								FREE_ARRAY (_hoops_RGGHH->_hoops_IIAIR->_hoops_SIAIR, _hoops_RGGHH->_hoops_IIAIR->_hoops_CIAIR, float);

							if ((_hoops_RGGHH->_hoops_IIAIR->_hoops_CIAIR = _hoops_AHAIR->_hoops_IIAIR->_hoops_CIAIR) != 0) {
								_hoops_APRGA (_hoops_AHAIR->_hoops_IIAIR->_hoops_SIAIR,
											 _hoops_RGGHH->_hoops_IIAIR->_hoops_CIAIR, float,
											 _hoops_RGGHH->_hoops_IIAIR->_hoops_SIAIR);
							}
						}
						if (BIT (_hoops_AHAIR->_hoops_IIAIR->mask, _hoops_CICRP)) {
							if (_hoops_RGGHH->_hoops_IIAIR->_hoops_GCAIR != 0)
								FREE_ARRAY (_hoops_RGGHH->_hoops_IIAIR->colors, _hoops_RGGHH->_hoops_IIAIR->_hoops_GCAIR, RGB);
							if ((_hoops_RGGHH->_hoops_IIAIR->_hoops_GCAIR = _hoops_AHAIR->_hoops_IIAIR->_hoops_GCAIR) != 0) {
								_hoops_APRGA (_hoops_AHAIR->_hoops_IIAIR->colors,
											 _hoops_RGGHH->_hoops_IIAIR->_hoops_GCAIR, RGB,
											 _hoops_RGGHH->_hoops_IIAIR->colors);
							}
						}
						if (BIT (_hoops_AHAIR->_hoops_IIAIR->mask, _hoops_SICRP)) {
							if (_hoops_RGGHH->_hoops_IIAIR->_hoops_RCAIR != 0) {
								for (int i=0; i<_hoops_RGGHH->_hoops_IIAIR->_hoops_RCAIR; i++)
									_hoops_RGAIR (_hoops_RGGHH->_hoops_IIAIR->_hoops_ACAIR[i]);
								FREE_ARRAY (_hoops_RGGHH->_hoops_IIAIR->_hoops_ACAIR, _hoops_RGGHH->_hoops_IIAIR->_hoops_RCAIR, _hoops_HCRPR);
								FREE_ARRAY (_hoops_RGGHH->_hoops_IIAIR->_hoops_PCAIR, _hoops_RGGHH->_hoops_IIAIR->_hoops_RCAIR, Integer32);
							}

							if ((_hoops_RGGHH->_hoops_IIAIR->_hoops_RCAIR = _hoops_AHAIR->_hoops_IIAIR->_hoops_RCAIR) != 0) {
								ALLOC_ARRAY (_hoops_RGGHH->_hoops_IIAIR->_hoops_ACAIR,
											 _hoops_RGGHH->_hoops_IIAIR->_hoops_RCAIR, _hoops_HCRPR);
								for (int i=0; i<_hoops_RGGHH->_hoops_IIAIR->_hoops_RCAIR; i++)
									HI_Copy_Name (&_hoops_AHAIR->_hoops_IIAIR->_hoops_ACAIR[i],
												  &_hoops_RGGHH->_hoops_IIAIR->_hoops_ACAIR[i]);

								_hoops_APRGA (_hoops_AHAIR->_hoops_IIAIR->_hoops_PCAIR,
											 _hoops_RGGHH->_hoops_IIAIR->_hoops_RCAIR, Integer32,
											 _hoops_RGGHH->_hoops_IIAIR->_hoops_PCAIR);
							}
						}
						if (BIT (_hoops_AHAIR->_hoops_IIAIR->mask, _hoops_GCCRP)) {
							if (_hoops_RGGHH->_hoops_IIAIR->weight_count != 0)
								FREE_ARRAY (_hoops_RGGHH->_hoops_IIAIR->weights, _hoops_RGGHH->_hoops_IIAIR->weight_count, _hoops_HCAIR);

							if ((_hoops_RGGHH->_hoops_IIAIR->weight_count = _hoops_AHAIR->_hoops_IIAIR->weight_count) != 0) {
								_hoops_APRGA (_hoops_AHAIR->_hoops_IIAIR->weights,
											 _hoops_RGGHH->_hoops_IIAIR->weight_count, _hoops_HCAIR,
											 _hoops_RGGHH->_hoops_IIAIR->weights);
							}
						}

						_hoops_RGGHH->_hoops_IIAIR->mask |= _hoops_AHAIR->_hoops_IIAIR->mask;
						_hoops_RGGHH->_hoops_IIAIR->value &= ~_hoops_AHAIR->_hoops_IIAIR->mask;
						_hoops_RGGHH->_hoops_IIAIR->value |= _hoops_AHAIR->_hoops_IIAIR->mask & _hoops_AHAIR->_hoops_IIAIR->value;
					}


					if (BIT (_hoops_AHAIR->_hoops_SHAAP, _hoops_HIGRP))
						_hoops_RGGHH->_hoops_IHRH._hoops_ACGRP = _hoops_AHAIR->_hoops_IHRH._hoops_ACGRP;
					if (BIT (_hoops_AHAIR->_hoops_SHAAP, _hoops_AIGRP)) {
						_hoops_RGGHH->_hoops_IHRH.scale = _hoops_AHAIR->_hoops_IHRH.scale;
						_hoops_RGGHH->_hoops_IHRH.translate = _hoops_AHAIR->_hoops_IHRH.translate;
					}
					if (BIT (_hoops_AHAIR->_hoops_SHAAP, _hoops_PIGRP))
						_hoops_RGGHH->_hoops_IHRH.color = _hoops_AHAIR->_hoops_IHRH.color;

					_hoops_RGGHH->_hoops_SHAAP |= _hoops_AHAIR->_hoops_SHAAP;
					_hoops_RGGHH->_hoops_GIAAP &= ~_hoops_AHAIR->_hoops_SHAAP;
					_hoops_RGGHH->_hoops_GIAAP |= _hoops_AHAIR->_hoops_SHAAP & _hoops_AHAIR->_hoops_GIAAP;

					if (_hoops_AHAIR->_hoops_PRSI != null) {
						if (_hoops_RGGHH->_hoops_PRSI == null)
							ZALLOC(_hoops_RGGHH->_hoops_PRSI, _hoops_PHAIR);

						if (BIT (_hoops_AHAIR->_hoops_PRSI->mask, _hoops_SSCRP))
							_hoops_RGGHH->_hoops_PRSI->_hoops_IRSH = _hoops_AHAIR->_hoops_PRSI->_hoops_IRSH;
						if (BIT (_hoops_AHAIR->_hoops_PRSI->mask, _hoops_IGSRP))
							_hoops_RGGHH->_hoops_PRSI->_hoops_ARPHA = _hoops_AHAIR->_hoops_PRSI->_hoops_ARPHA;
						for (int i = 0; i < _hoops_IGAIR; i++) {
							if (BIT (_hoops_AHAIR->_hoops_PRSI->mask, _hoops_ISCRP))
								_hoops_RGGHH->_hoops_PRSI->_hoops_PRPHA[i] = _hoops_AHAIR->_hoops_PRSI->_hoops_PRPHA[i];
							if (BIT (_hoops_AHAIR->_hoops_PRSI->mask, _hoops_IASRP))
								_hoops_RGGHH->_hoops_PRSI->_hoops_AISRP[i] = _hoops_AHAIR->_hoops_PRSI->_hoops_AISRP[i];
							if (BIT (_hoops_AHAIR->_hoops_PRSI->mask, _hoops_IRSRP))
								_hoops_RGGHH->_hoops_PRSI->_hoops_GHRGR[i] = _hoops_AHAIR->_hoops_PRSI->_hoops_GHRGR[i];
						}
						if (BIT (_hoops_AHAIR->_hoops_PRSI->mask, _hoops_RRSRP))
							_hoops_AHAIR->_hoops_PRSI->bounding = _hoops_RGGHH->_hoops_PRSI->bounding;
						if (BIT (_hoops_AHAIR->_hoops_PRSI->mask, _hoops_CSCRP))
							_hoops_RGGHH->_hoops_PRSI->_hoops_HISRP = _hoops_AHAIR->_hoops_PRSI->_hoops_HISRP;
						if (BIT (_hoops_AHAIR->_hoops_PRSI->mask, _hoops_HASRP))
							_hoops_RGGHH->_hoops_PRSI->_hoops_IISRP = _hoops_AHAIR->_hoops_PRSI->_hoops_IISRP;
						if (BIT (_hoops_AHAIR->_hoops_PRSI->mask, _hoops_GGSRP))
							_hoops_RGGHH->_hoops_PRSI->_hoops_RHPHA = _hoops_AHAIR->_hoops_PRSI->_hoops_RHPHA;
						if (BIT (_hoops_AHAIR->_hoops_PRSI->mask, _hoops_AGSRP))
							_hoops_RGGHH->_hoops_PRSI->tolerance = _hoops_AHAIR->_hoops_PRSI->tolerance;
						if (BIT (_hoops_AHAIR->_hoops_PRSI->mask, _hoops_GRSRP))
							_hoops_RGGHH->_hoops_PRSI->_hoops_SRHHR = _hoops_AHAIR->_hoops_PRSI->_hoops_SRHHR;
						if (BIT (_hoops_AHAIR->_hoops_PRSI->mask, _hoops_PASRP))
							_hoops_RGGHH->_hoops_PRSI->_hoops_RCSRP = _hoops_AHAIR->_hoops_PRSI->_hoops_RCSRP;

						_hoops_RGGHH->_hoops_PRSI->mask |= _hoops_AHAIR->_hoops_PRSI->mask;
						_hoops_RGGHH->_hoops_PRSI->value &= ~_hoops_AHAIR->_hoops_PRSI->mask;
						_hoops_RGGHH->_hoops_PRSI->value |= _hoops_AHAIR->_hoops_PRSI->mask &
													   _hoops_AHAIR->_hoops_PRSI->value;
					}

					if (_hoops_AHAIR->geometry != null) {
						if (_hoops_RGGHH->geometry == null)
							ZALLOC(_hoops_RGGHH->geometry, _hoops_SCAIR);

						_hoops_RGGHH->geometry->_hoops_APPI.mask |= _hoops_AHAIR->geometry->_hoops_APPI.mask;
						_hoops_RGGHH->geometry->_hoops_APPI.value &= ~_hoops_AHAIR->geometry->_hoops_APPI.mask;
						_hoops_RGGHH->geometry->_hoops_APPI.value |= _hoops_AHAIR->geometry->_hoops_APPI.mask &
													_hoops_AHAIR->geometry->_hoops_APPI.value;
						if (BIT (_hoops_AHAIR->geometry->_hoops_APPI.mask, _hoops_CHGAP))
							_hoops_RGGHH->geometry->_hoops_APPI._hoops_PPPI = _hoops_AHAIR->geometry->_hoops_APPI._hoops_PPPI;
						if (BIT (_hoops_AHAIR->geometry->_hoops_APPI.mask, _hoops_SHGAP))
							_hoops_RGGHH->geometry->_hoops_APPI._hoops_HPPI = _hoops_AHAIR->geometry->_hoops_APPI._hoops_HPPI;
						if (BIT (_hoops_AHAIR->geometry->_hoops_APPI.mask, _hoops_GIGAP))
							_hoops_RGGHH->geometry->_hoops_APPI._hoops_IPPI = _hoops_AHAIR->geometry->_hoops_APPI._hoops_IPPI;
						if (BIT (_hoops_AHAIR->geometry->_hoops_APPI.mask, _hoops_RIGAP))
							_hoops_RGGHH->geometry->_hoops_APPI._hoops_CPPI = _hoops_AHAIR->geometry->_hoops_APPI._hoops_CPPI;
						if (BIT (_hoops_AHAIR->geometry->_hoops_APPI.mask, _hoops_AIGAP))
							_hoops_RGGHH->geometry->_hoops_APPI._hoops_SPPI = _hoops_AHAIR->geometry->_hoops_APPI._hoops_SPPI;

						_hoops_RGGHH->geometry->_hoops_PSRIR.mask |= _hoops_AHAIR->geometry->_hoops_PSRIR.mask;
						_hoops_RGGHH->geometry->_hoops_PSRIR.value &= ~_hoops_AHAIR->geometry->_hoops_PSRIR.mask;
						_hoops_RGGHH->geometry->_hoops_PSRIR.value |= _hoops_AHAIR->geometry->_hoops_PSRIR.mask &
													_hoops_AHAIR->geometry->_hoops_PSRIR.value;
						if (BIT (_hoops_AHAIR->geometry->_hoops_PSRIR.mask, _hoops_PIGAP))
							_hoops_RGGHH->geometry->_hoops_PSRIR.configs._hoops_GGIRP = _hoops_AHAIR->geometry->_hoops_PSRIR.configs._hoops_GGIRP;
						if (BIT (_hoops_AHAIR->geometry->_hoops_PSRIR.mask, _hoops_IIGAP))
							_hoops_RGGHH->geometry->_hoops_PSRIR.configs._hoops_CSHRP = _hoops_AHAIR->geometry->_hoops_PSRIR.configs._hoops_CSHRP;
						if (BIT (_hoops_AHAIR->geometry->_hoops_PSRIR.mask, _hoops_CIGAP))
							_hoops_RGGHH->geometry->_hoops_PSRIR.configs._hoops_RGIRP = _hoops_AHAIR->geometry->_hoops_PSRIR.configs._hoops_RGIRP;
						if (BIT (_hoops_AHAIR->geometry->_hoops_PSRIR.mask, _hoops_SIGAP))
							_hoops_RGGHH->geometry->_hoops_PSRIR.configs._hoops_AGIRP = _hoops_AHAIR->geometry->_hoops_PSRIR.configs._hoops_AGIRP;
						if (BIT (_hoops_AHAIR->geometry->_hoops_PSRIR.mask, _hoops_GCGAP))
							_hoops_RGGHH->geometry->_hoops_PSRIR.configs._hoops_PGIRP = _hoops_AHAIR->geometry->_hoops_PSRIR.configs._hoops_PGIRP;
						if (BIT (_hoops_AHAIR->geometry->_hoops_PSRIR.mask, _hoops_RCGAP))
							_hoops_RGGHH->geometry->_hoops_PSRIR.configs._hoops_SSHRP = _hoops_AHAIR->geometry->_hoops_PSRIR.configs._hoops_SSHRP;

						_hoops_ISHRP(_hoops_RGGHH->geometry->_hoops_PSRIR.configs);
					}



					if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_HRRAP)) {
						_hoops_RGGHH->_hoops_HHAAP[0] = _hoops_AHAIR->_hoops_HHAAP[0];
						_hoops_RGGHH->_hoops_HHAAP[1] = _hoops_AHAIR->_hoops_HHAAP[1];
					}
					if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_APRAP))
						_hoops_RGGHH->_hoops_HCIH = _hoops_AHAIR->_hoops_HCIH;

					_hoops_RGGHH->_hoops_ISHCA |= _hoops_AHAIR->_hoops_ISHCA;
					_hoops_RGGHH->_hoops_GHRAP &= ~_hoops_AHAIR->_hoops_ISHCA;
					_hoops_RGGHH->_hoops_GHRAP |= _hoops_AHAIR->_hoops_ISHCA &
												_hoops_AHAIR->_hoops_GHRAP;

					_hoops_RGGHH->_hoops_PSHCA |= _hoops_AHAIR->_hoops_PSHCA;
					_hoops_RGGHH->_hoops_RRRAP &= ~_hoops_AHAIR->_hoops_PSHCA;
					_hoops_RGGHH->_hoops_RRRAP |= _hoops_AHAIR->_hoops_PSHCA & _hoops_AHAIR->_hoops_RRRAP;

					_hoops_RGGHH->_hoops_SCIAA |= _hoops_AHAIR->_hoops_SCIAA;
					_hoops_RGGHH->_hoops_RSIAA &= ~_hoops_AHAIR->_hoops_SCIAA;
					_hoops_RGGHH->_hoops_RSIAA |= _hoops_AHAIR->_hoops_SCIAA & _hoops_AHAIR->_hoops_RSIAA;
				}
			}	break;

			case HK_VISIBILITY: /* _hoops_SGH _hoops_IGGA _hoops_SGHS */ {
				_hoops_RSAIR const *		_hoops_AGGHH = (_hoops_RSAIR const *)_hoops_ASGPR;
				_hoops_RSAIR alter *		vis;

				if ((vis = (_hoops_RSAIR *)*_hoops_PSACR) == null) {
					if ((_hoops_AGGHH->mask & ~_hoops_SCSPH->_hoops_RGP) != 0) {
						ZALLOC (vis, _hoops_RSAIR);
						vis->type = HK_VISIBILITY;
						vis->_hoops_HIHI = 1;
						*_hoops_PSACR = (Attribute *)vis;
						vis->mask = _hoops_AGGHH->mask & ~_hoops_SCSPH->_hoops_RGP;
						vis->value = _hoops_AGGHH->value & ~_hoops_SCSPH->_hoops_RGP;
						vis->_hoops_SPSS.mask = _hoops_AGGHH->_hoops_SPSS.mask;
						vis->_hoops_SPSS.value = _hoops_AGGHH->_hoops_SPSS.value;
						vis->_hoops_PRIGA.mask = _hoops_AGGHH->_hoops_PRIGA.mask;
						vis->_hoops_PRIGA.value = _hoops_AGGHH->_hoops_PRIGA.value;
					}
				}
				else {
					vis->mask |= _hoops_AGGHH->mask & ~_hoops_SCSPH->_hoops_RGP;
					vis->value &= ~_hoops_AGGHH->mask | _hoops_SCSPH->_hoops_RGP;
					vis->value |= _hoops_AGGHH->mask & ~_hoops_SCSPH->_hoops_RGP &
								  _hoops_AGGHH->value;

					vis->_hoops_SPSS.mask |= _hoops_AGGHH->_hoops_SPSS.mask;
					vis->_hoops_SPSS.value &= ~_hoops_AGGHH->_hoops_SPSS.mask;
					vis->_hoops_SPSS.value |= _hoops_AGGHH->_hoops_SPSS.mask &
										 _hoops_AGGHH->_hoops_SPSS.value;
					vis->_hoops_PRIGA.mask |= _hoops_AGGHH->_hoops_PRIGA.mask;
					vis->_hoops_PRIGA.value &= ~_hoops_AGGHH->_hoops_PRIGA.value;
					vis->_hoops_PRIGA.value |= _hoops_AGGHH->_hoops_PRIGA.mask &
											   _hoops_AGGHH->_hoops_PRIGA.value;
				}
			}	break;

			case HK_SELECTABILITY: if (!BIT (_hoops_SCSPH->_hoops_IPPGR, _hoops_GGCAA(HK_SELECTABILITY))) {
				_hoops_ASAIR const *		_hoops_PGGHH = (_hoops_ASAIR const *)_hoops_ASGPR;
				_hoops_ASAIR alter *		_hoops_RIRIP;

				if ((_hoops_RIRIP = (_hoops_ASAIR *)*_hoops_PSACR) == null) {
					*_hoops_PSACR = HI_Clone_Attributes (_hoops_RIGC, _hoops_ASGPR, null, false, null);
				}
				else {
					_hoops_RIRIP->mask |= _hoops_PGGHH->mask;

					_hoops_RIRIP->up &= ~_hoops_PGGHH->mask;
					_hoops_RIRIP->down &= ~_hoops_PGGHH->mask;
					_hoops_RIRIP->_hoops_RHARP &= ~_hoops_PGGHH->mask;
					_hoops_RIRIP->_hoops_AHARP &= ~_hoops_PGGHH->mask;
					_hoops_RIRIP->_hoops_PHARP &= ~_hoops_PGGHH->mask;

					_hoops_RIRIP->up |= _hoops_PGGHH->up;
					_hoops_RIRIP->down |= _hoops_PGGHH->down;
					_hoops_RIRIP->_hoops_RHARP |= _hoops_PGGHH->_hoops_RHARP;
					_hoops_RIRIP->_hoops_AHARP |= _hoops_PGGHH->_hoops_AHARP;
					_hoops_RIRIP->_hoops_PHARP |= _hoops_PGGHH->_hoops_PHARP;
				}
			}	break;

			case _hoops_IPAIR: {
				_hoops_CPAIR const *	_hoops_HGGHH = (_hoops_CPAIR const *)_hoops_ASGPR;
				_hoops_CPAIR alter *	_hoops_IGGHH;

				if (_hoops_HGGHH->count == 0)
					break;

				// _hoops_RRI _hoops_PII _hoops_IRS _hoops_RRSS

				if ((_hoops_IGGHH = (_hoops_CPAIR *)*_hoops_PSACR) == null) {
					ZALLOC (_hoops_IGGHH, _hoops_CPAIR);
					_hoops_IGGHH->type = _hoops_IPAIR;
					_hoops_IGGHH->_hoops_HIHI = 1;
					*_hoops_PSACR = (Attribute *)_hoops_IGGHH;
				}

				int			_hoops_RGCCA = _hoops_IGGHH->count + _hoops_HGGHH->count;
				_hoops_RCR **	_hoops_HPRIP;
				int *		new_keys;

				ALLOC_ARRAY (_hoops_HPRIP, _hoops_RGCCA, _hoops_RCR *);
				ALLOC_ARRAY (new_keys, _hoops_RGCCA, Integer32);

				for (int i=0; i<_hoops_HGGHH->count; i++) {
					_hoops_HPRIP[i] = HI_Clone_Texture (_hoops_HGGHH->textures[i]);
					_hoops_HPRIP[i]->owner = null;
				}
				_hoops_AIGA (_hoops_HGGHH->keys, _hoops_HGGHH->count, Integer32, new_keys);

				if (_hoops_IGGHH->count) {
					_hoops_AIGA (_hoops_IGGHH->textures, _hoops_IGGHH->count, _hoops_RCR *, &_hoops_HPRIP[_hoops_HGGHH->count]);
					_hoops_AIGA (_hoops_IGGHH->keys, _hoops_IGGHH->count, Integer32, &new_keys[_hoops_HGGHH->count]);
					FREE_ARRAY (_hoops_IGGHH->textures, _hoops_IGGHH->count, _hoops_RCR *);
					FREE_ARRAY (_hoops_IGGHH->keys, _hoops_IGGHH->count, Integer32);
				}

				_hoops_IGGHH->textures = _hoops_HPRIP;
				_hoops_IGGHH->keys = new_keys;
				_hoops_IGGHH->count = _hoops_RGCCA;
			}	break;

			case _hoops_RAAIR: {
				_hoops_AAAIR const *		_hoops_CGGHH = (_hoops_AAAIR const *)_hoops_ASGPR;
				_hoops_AAAIR alter *		_hoops_SGGHH;

				// _hoops_RRI _hoops_PII _hoops_IRS _hoops_RRSS

				if ((_hoops_SGGHH = (_hoops_AAAIR *)*_hoops_PSACR) == null) {
					ZALLOC (_hoops_SGGHH, _hoops_AAAIR);
					_hoops_SGGHH->type = _hoops_RAAIR;
					_hoops_SGGHH->_hoops_HIHI = 1;
					*_hoops_PSACR = (Attribute *)_hoops_SGGHH;
				}

				int			_hoops_RGCCA = _hoops_SGGHH->count + _hoops_CGGHH->count;
				_hoops_GASC *		_hoops_SPRIP;
				int *		new_keys;
				ZALLOC_ARRAY (_hoops_SPRIP, _hoops_RGCCA, _hoops_GASC);
				ALLOC_ARRAY (new_keys, _hoops_RGCCA, Integer32);

				for (int i=0; i<_hoops_CGGHH->count; i++)
					_hoops_SPRIP[i] = _hoops_CGGHH->glyphs[i];
				_hoops_AIGA (_hoops_CGGHH->keys, _hoops_CGGHH->count, Integer32, new_keys);

				if (_hoops_SGGHH->count) {
					// _hoops_PIP, _hoops_HIGIP _hoops_AGCR
					_hoops_AIGA (_hoops_SGGHH->glyphs, _hoops_SGGHH->count, _hoops_GASC, &_hoops_SPRIP[_hoops_CGGHH->count]);
					FREE_ARRAY (_hoops_SGGHH->glyphs, _hoops_SGGHH->count, _hoops_GASC);

					_hoops_AIGA (_hoops_SGGHH->keys, _hoops_SGGHH->count, Integer32, &new_keys[_hoops_CGGHH->count]);
					FREE_ARRAY (_hoops_SGGHH->keys, _hoops_SGGHH->count, Integer32);
				}

				_hoops_SGGHH->glyphs = _hoops_SPRIP;
				_hoops_SGGHH->keys = new_keys;
				_hoops_SGGHH->count = _hoops_RGCCA;
			}	break;

			case _hoops_HAAIR: {
				_hoops_IAAIR const *	_hoops_GRGHH = (_hoops_IAAIR const *)_hoops_ASGPR;
				_hoops_IAAIR alter *	_hoops_RRGHH;

				if ((_hoops_RRGHH = (_hoops_IAAIR *)*_hoops_PSACR) == null) {
					ZALLOC (_hoops_RRGHH, _hoops_IAAIR);
					_hoops_RRGHH->type = _hoops_HAAIR;
					_hoops_RRGHH->_hoops_HIHI = 1;
					*_hoops_PSACR = (Attribute *)_hoops_RRGHH;
				}

				int				_hoops_RGCCA = _hoops_RRGHH->count + _hoops_GRGHH->count;
				_hoops_GPAIR *	_hoops_GIGIP;
				int *			new_keys;

				ZALLOC_ARRAY (_hoops_GIGIP, _hoops_RGCCA, _hoops_GPAIR);
				ALLOC_ARRAY (new_keys, _hoops_RGCCA, Integer32);

				for (int i=0; i<_hoops_GRGHH->count; i++)
					_hoops_GIGIP[i] = _hoops_GRGHH->_hoops_SAAIR[i];
				_hoops_AIGA (_hoops_GRGHH->keys, _hoops_GRGHH->count, Integer32, new_keys);

				if (_hoops_RRGHH->count) {
					// _hoops_PIP, _hoops_HIGIP _hoops_AGCR
					_hoops_AIGA (_hoops_RRGHH->_hoops_SAAIR, _hoops_RRGHH->count, _hoops_GPAIR, &_hoops_GIGIP[_hoops_GRGHH->count]);
					FREE_ARRAY (_hoops_RRGHH->_hoops_SAAIR, _hoops_RRGHH->count, _hoops_GPAIR);
					_hoops_AIGA (_hoops_RRGHH->keys, _hoops_RRGHH->count, Integer32, &new_keys[_hoops_GRGHH->count]);
					FREE_ARRAY (_hoops_RRGHH->keys, _hoops_RRGHH->count, Integer32);
				}

				_hoops_RRGHH->_hoops_SAAIR = _hoops_GIGIP;
				_hoops_RRGHH->keys = new_keys;
				_hoops_RRGHH->count = _hoops_RGCCA;
			}	break;

			case _hoops_RPAIR: {
				_hoops_APAIR const *		_hoops_ARGHH = (_hoops_APAIR const *)_hoops_ASGPR;
				_hoops_APAIR alter *		_hoops_PRGHH;

				if ((_hoops_PRGHH = (_hoops_APAIR *)*_hoops_PSACR) == null) {
					ZALLOC (_hoops_PRGHH, _hoops_APAIR);
					_hoops_PRGHH->type = _hoops_RPAIR;
					_hoops_PRGHH->_hoops_HIHI = 1;
					*_hoops_PSACR = (Attribute *)_hoops_PRGHH;
				}

				int				_hoops_RGCCA = _hoops_PRGHH->count + _hoops_ARGHH->count;
				Line_Style *	_hoops_HRGHH;
				int *			new_keys;

				ZALLOC_ARRAY (_hoops_HRGHH, _hoops_RGCCA, Line_Style);
				ALLOC_ARRAY (new_keys, _hoops_RGCCA, Integer32);

				for (int i=0; i<_hoops_ARGHH->count; i++)
					_hoops_HRGHH[i] = _hoops_ARGHH->_hoops_HPAIR[i];
				_hoops_AIGA (_hoops_ARGHH->keys, _hoops_ARGHH->count, Integer32, new_keys);

				if (_hoops_PRGHH->count) {
					// _hoops_PIP, _hoops_HIGIP _hoops_AGCR
					_hoops_AIGA (_hoops_PRGHH->_hoops_HPAIR, _hoops_PRGHH->count, Line_Style, &_hoops_HRGHH[_hoops_ARGHH->count]);
					FREE_ARRAY (_hoops_PRGHH->_hoops_HPAIR, _hoops_PRGHH->count, Line_Style);
					_hoops_AIGA (_hoops_PRGHH->keys, _hoops_PRGHH->count, Integer32, &new_keys[_hoops_ARGHH->count]);
					FREE_ARRAY (_hoops_PRGHH->keys, _hoops_PRGHH->count, Integer32);
				}

				_hoops_PRGHH->_hoops_HPAIR = _hoops_HRGHH;
				_hoops_PRGHH->keys = new_keys;
				_hoops_PRGHH->count = _hoops_RGCCA;
			}	break;

			case HK_EDGE_PATTERN: if (!BIT (_hoops_SCSPH->_hoops_IPPGR, _hoops_GGCAA(HK_EDGE_PATTERN))) {
				_hoops_ISAIR const *		_hoops_IRGHH = (_hoops_ISAIR const *)_hoops_ASGPR;
				_hoops_ISAIR alter *		_hoops_CSAIR;

				if ((_hoops_CSAIR = (_hoops_ISAIR *)*_hoops_PSACR) == null) {
					*_hoops_PSACR = HI_Clone_Attributes (_hoops_RIGC, _hoops_ASGPR, null, false, null);
				}
				else {
					if (_hoops_IRGHH->mask == 0) {
						//_hoops_IRRIR
						_hoops_RGAIR (_hoops_CSAIR->line_style);
						HI_Copy_Name (&_hoops_IRGHH->line_style, &_hoops_CSAIR->line_style);
						_hoops_CSAIR->_hoops_SCCAP = _hoops_IRGHH->_hoops_SCCAP;
						_hoops_CSAIR->value = _hoops_IRGHH->value;
						_hoops_CSAIR->mask = _hoops_IRGHH->mask;
					}
					else {
						if (ANYBIT(_hoops_IRGHH->mask, _hoops_AICAP|_hoops_CCCAP)) {
							_hoops_RGAIR (_hoops_CSAIR->line_style);
							HI_Copy_Name (&_hoops_IRGHH->line_style, &_hoops_CSAIR->line_style);
							_hoops_CSAIR->_hoops_SCCAP = _hoops_IRGHH->_hoops_SCCAP;
						}
						//_hoops_HASC _hoops_PISH
						_hoops_CSAIR->mask |= _hoops_IRGHH->mask;
						//_hoops_HASC _hoops_PIRA
						if (BIT(_hoops_IRGHH->mask, _hoops_PICAP)) {
							_hoops_CSAIR->value &= ~LCAP_MASK;
							_hoops_CSAIR->value |= _hoops_IRGHH->value & LCAP_MASK;
						}
						if (BIT(_hoops_IRGHH->mask, _hoops_HICAP)) {
							_hoops_CSAIR->value &= ~LCAP_END_MASK;
							_hoops_CSAIR->value |= _hoops_IRGHH->value & LCAP_END_MASK;
						}
						if (BIT(_hoops_IRGHH->mask, _hoops_IICAP)) {
							_hoops_CSAIR->value &= ~LPAT_MASK;
							_hoops_CSAIR->value |= _hoops_IRGHH->value & LPAT_MASK;
						}
						if (BIT(_hoops_IRGHH->mask, _hoops_CICAP)) {
							_hoops_CSAIR->value &= ~LJOIN_MASK;
							_hoops_CSAIR->value |= _hoops_IRGHH->value & LJOIN_MASK;
						}
					}
				}
			}	break;

			case HK_LINE_PATTERN: if (!BIT (_hoops_SCSPH->_hoops_IPPGR, _hoops_GGCAA(HK_LINE_PATTERN))) {
				_hoops_PSAIR const *		_hoops_CRGHH = (_hoops_PSAIR const *)_hoops_ASGPR;
				_hoops_PSAIR alter *		_hoops_HSAIR;

				if ((_hoops_HSAIR = (_hoops_PSAIR *)*_hoops_PSACR) == null) {
					*_hoops_PSACR = HI_Clone_Attributes (_hoops_RIGC, _hoops_ASGPR, null, false, null);
				}
				else {
					if (_hoops_CRGHH->mask == 0) {
						//_hoops_IRRIR
						_hoops_RGAIR (_hoops_HSAIR->line_style);
						HI_Copy_Name (&_hoops_CRGHH->line_style, &_hoops_HSAIR->line_style);
						_hoops_HSAIR->_hoops_SCCAP = _hoops_CRGHH->_hoops_SCCAP;
						_hoops_HSAIR->value = _hoops_CRGHH->value;
						_hoops_HSAIR->mask = _hoops_CRGHH->mask;
					}
					else {
						if (ANYBIT(_hoops_CRGHH->mask, _hoops_AICAP|_hoops_CCCAP)) {
							_hoops_RGAIR (_hoops_HSAIR->line_style);
							HI_Copy_Name (&_hoops_CRGHH->line_style, &_hoops_HSAIR->line_style);
							_hoops_HSAIR->_hoops_SCCAP = _hoops_CRGHH->_hoops_SCCAP;
						}
						if (BIT(_hoops_CRGHH->mask, _hoops_SICAP)) {
							_hoops_RGAIR (_hoops_HSAIR->start_glyph);
							HI_Copy_Name (&_hoops_CRGHH->start_glyph, &_hoops_HSAIR->start_glyph);
							_hoops_HSAIR->_hoops_GSCAP = _hoops_CRGHH->_hoops_GSCAP;
						}
						if (BIT(_hoops_CRGHH->mask, _hoops_RCCAP)) {
							_hoops_RGAIR (_hoops_HSAIR->middle_glyph);
							HI_Copy_Name (&_hoops_CRGHH->middle_glyph, &_hoops_HSAIR->middle_glyph);
							_hoops_HSAIR->_hoops_RSCAP = _hoops_CRGHH->_hoops_RSCAP;
						}
						if (BIT(_hoops_CRGHH->mask, _hoops_GCCAP)) {
							_hoops_RGAIR (_hoops_HSAIR->end_glyph);
							HI_Copy_Name (&_hoops_CRGHH->end_glyph, &_hoops_HSAIR->end_glyph);
							_hoops_HSAIR->_hoops_ASCAP = _hoops_CRGHH->_hoops_ASCAP;
						}
						//_hoops_HASC _hoops_PISH
						_hoops_HSAIR->mask |= _hoops_CRGHH->mask;
						//_hoops_HASC _hoops_PIRA
						if (BIT(_hoops_CRGHH->mask, _hoops_PICAP)) {
							_hoops_HSAIR->value &= ~LCAP_MASK;
							_hoops_HSAIR->value |= _hoops_CRGHH->value & LCAP_MASK;
						}
						if (BIT(_hoops_CRGHH->mask, _hoops_HICAP)) {
							_hoops_HSAIR->value &= ~LCAP_END_MASK;
							_hoops_HSAIR->value |= _hoops_CRGHH->value & LCAP_END_MASK;
						}
						if (BIT(_hoops_CRGHH->mask, _hoops_IICAP)) {
							_hoops_HSAIR->value &= ~LPAT_MASK;
							_hoops_HSAIR->value |= _hoops_CRGHH->value & LPAT_MASK;
						}
						if (BIT(_hoops_CRGHH->mask, _hoops_CICAP)) {
							_hoops_HSAIR->value &= ~LJOIN_MASK;
							_hoops_HSAIR->value |= _hoops_CRGHH->value & LJOIN_MASK;
						}
					}
				}
			}	break;

			/* _hoops_HCR _hoops_RII _hoops_AIRC _hoops_SAHR _hoops_CHASA (_hoops_RPP _hoops_HAR _hoops_PCPAR) */
			default: {
				if (_hoops_ASGPR->type == type && !BIT (_hoops_SCSPH->_hoops_IPPGR, _hoops_GGCAA(type))) {
					if (*_hoops_PSACR != null)
						_hoops_HPRH (*_hoops_PSACR);
					*_hoops_PSACR = _hoops_ASGPR;
					_hoops_PRRH (_hoops_ASGPR);
				}
			}	break;
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	if (_hoops_RPGIP) {
		/* _hoops_SR _hoops_HHGC _hoops_RH _hoops_ARGR _hoops_GSSP _hoops_AHC _hoops_IIGR _hoops_RH _hoops_CARA _hoops_CGRS (_hoops_PGAP _hoops_SRIPR _hoops_IS _hoops_SHH _hoops_RH
		 * _hoops_HCHIA _hoops_ARIP _hoops_IIGR _hoops_RH _hoops_GCHRR _hoops_PRGIA _hoops_RSGA), _hoops_PPR _hoops_CACH _hoops_RSH _hoops_SGS _hoops_IIRIP _hoops_GPP _hoops_RH _hoops_RAR
		 * _hoops_AAGA.	_hoops_RH _hoops_AHHSR _hoops_IIGR _hoops_SGS _hoops_CCA _hoops_RH _hoops_SAAP _hoops_GIRA _hoops_CGH _hoops_PPGR _hoops_IH
		 * _hoops_RH _hoops_IGIR _hoops_AGRP _hoops_SAPGP _hoops_IS _hoops_AIHP
		 */
		_hoops_ISGI alter *		_hoops_HSGA = (_hoops_ISGI alter *)*_hoops_PSACR;
		_hoops_HHRA const *					_hoops_SPH = control->_hoops_SPH;
		Point const *					origin = (Point const *)&_hoops_HSGA->matrix.elements[3][0];
		float							scale;
		_hoops_HRPA						temp;
		_hoops_HRPA						_hoops_RHSPR;
		float							_hoops_CHCR;

		/* '_hoops_GHGP' _hoops_IIGR _hoops_IPPA _hoops_PHGSR _hoops_RHIR _hoops_SARA _hoops_AHC */
		scale = -(_hoops_SPH->position.x * _hoops_SPH->_hoops_IIPCR.x +
				  _hoops_SPH->position.y * _hoops_SPH->_hoops_IIPCR.y +
				  _hoops_SPH->position.z * _hoops_SPH->_hoops_IIPCR.z);
		/* _hoops_PRRGR _hoops_CGRS _hoops_CIAA _hoops_SARA _hoops_AAGA _hoops_CSCHR _hoops_IS _hoops_SARA _hoops_AHC */
		scale += origin->x * _hoops_SPH->_hoops_IIPCR.x + origin->y * _hoops_SPH->_hoops_IIPCR.y + origin->z * _hoops_SPH->_hoops_IIPCR.z;
		/* _hoops_CSRA _hoops_RRPS _hoops_IS _hoops_SARA _hoops_GIRA */
		scale /= _hoops_SPH->_hoops_SRIR;

		/* _hoops_PSSSR _hoops_IH _hoops_AHCI _hoops_ARAR */
		if ((_hoops_CHCR = *_hoops_SPH->_hoops_SIPCR) <= 0.0f)
			_hoops_CHCR = 0.05f;
		if (scale > _hoops_CHCR) {
			HI_Figure_Scale_Matrix (scale, scale, scale, &temp);
			HI_Copy_Matrix (&_hoops_HSGA->matrix, &_hoops_RHSPR);
			HI_Multiply_Matrices (&temp, &_hoops_RHSPR, &_hoops_HSGA->matrix);
		}
	}

	if (conditions != _hoops_ICSPH)
		FREE_ARRAY (conditions, _hoops_IRCAA, unsigned int);
}


local void _hoops_IGARH (
	_hoops_AIGPR *			_hoops_RIGC,
	_hoops_CRCP const *					_hoops_SRCP,
	Attribute **					_hoops_PSACR,
	Type							type,
	_hoops_PIGRA *				locks,
	_hoops_PIGRA *				_hoops_SRGHH,
	unsigned int *					conditions,
	int								_hoops_CCSPH,
	_hoops_CRACA const *	control)
{
	_hoops_CRCP *	owner = _hoops_SRCP->owner;

	while (owner->type != _hoops_PRAIR) {
		if (owner->type == _hoops_IRCP) {
			if (owner->_hoops_IPPGR != null) {
				_hoops_IGARH (_hoops_RIGC, owner, _hoops_PSACR, type, locks, _hoops_SRGHH, conditions, _hoops_CCSPH, control);
				break;
			}
			owner = owner->owner;
		}
		else if (owner->type == _hoops_PIRIR) {
			// _hoops_IPCA _hoops_GH
			owner = owner->owner;
		}
		else
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected type found while upwinding");
	}

	if (_hoops_SRCP->type == _hoops_IRCP) {
		if (_hoops_SRCP->_hoops_IPPGR != null)
			_hoops_PIIS (_hoops_RIGC, _hoops_SRCP->_hoops_IPPGR, _hoops_PSACR, type, locks, _hoops_SRGHH, conditions, _hoops_CCSPH, control);
	}
	else {
		Geometry const *	geo = (Geometry const *)_hoops_SRCP;
		if (geo->_hoops_IPPGR != null)
			_hoops_PIIS (_hoops_RIGC, geo->_hoops_IPPGR, _hoops_PSACR, type, locks, _hoops_SRGHH, conditions, _hoops_CCSPH, control);
	}
}


GLOBAL_FUNCTION Attribute * HI_Find_Net_Attribute (
	_hoops_AIGPR *			_hoops_RIGC,
	_hoops_HPAH const *				item,
	Type							type,
	int								_hoops_CCSPH,
	_hoops_CRACA const *	control)
{
	_hoops_RSIIR(_hoops_RIGC);
	ASSERT(item != null);

	ASSERT(!ANYBIT(_hoops_CCSPH, _hoops_ISCAP|_hoops_HSCAP|_hoops_SRACA) || control!=null);

	_hoops_CRCP const *			_hoops_SRCP = null;
	Attribute *				internal = null;
	Attribute *				_hoops_GAGHH = null;
	Attribute *				_hoops_PSACR = null;
	_hoops_PIGRA			locks;
	_hoops_PIGRA			_hoops_SRGHH;
	Type					_hoops_RHIPH = Abs(type);

	if (type == _hoops_RHAGP)
		return null;	/* (_hoops_IH _hoops_RAGHH) */

	if (item->type == _hoops_IRCP)
		_hoops_SRCP = (_hoops_CRCP const *)item;
	else if (item->type >= _hoops_AHRIR && item->type <= _hoops_PHRIR) {
		internal = HI_Find_Attribute (_hoops_RIGC, item, -_hoops_RHIPH);
		_hoops_SRCP = (_hoops_CRCP const *)item->owner;
	}
	else if (item->type == _hoops_CIRIR) {
		_hoops_SIRIR const * _hoops_ASIIR = (_hoops_SIRIR const *)item;

		switch (_hoops_ASIIR->_hoops_GCRIR) {
			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected open");
				return null;
			}	/*_hoops_IHSA;*/

			case _hoops_RCRIR: {
				_hoops_SRCP = _hoops_ASIIR->info.segment._hoops_IGRPR;
			}	break;

	#ifndef DISABLE_GEOMETRY_ATTRIBUTES
			case _hoops_HCRIR: {
				internal = HI_Find_Attribute (_hoops_RIGC, (_hoops_HPAH const*)_hoops_ASIIR->info.geometry._hoops_IGRPR, -_hoops_RHIPH);
				_hoops_SRCP = _hoops_ASIIR->info.geometry._hoops_IGRPR->owner;
			}	break;

			case _hoops_SCRIR:
			case _hoops_CCRIR:
			case _hoops_ICRIR: {
				internal = HI_Find_Local_Attribute (_hoops_RIGC, _hoops_ASIIR, _hoops_RHIPH);
				_hoops_GAGHH = HI_Find_Attribute (_hoops_RIGC, (_hoops_HPAH const*)_hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR, -_hoops_RHIPH);
				_hoops_SRCP = _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR->owner;
			}	break;
	#endif
		}
	}

	ZERO_STRUCT (&locks, _hoops_PIGRA);
	ZERO_STRUCT (&_hoops_SRGHH, _hoops_PIGRA);

	if (_hoops_SRCP) {
		unsigned int *			conditions;
		int						_hoops_IRCAA;

		if ((_hoops_IRCAA = HOOPS_WORLD->_hoops_AGCAA / 32) == 0)
			_hoops_IRCAA = 1;
		ZALLOC_ARRAY (conditions, _hoops_IRCAA, unsigned int);

		_hoops_IGARH (_hoops_RIGC, _hoops_SRCP, &_hoops_PSACR, _hoops_RHIPH, &locks, &_hoops_SRGHH, conditions, _hoops_CCSPH, control);

		FREE_ARRAY (conditions, _hoops_IRCAA, unsigned int);
	}
	if (_hoops_GAGHH != null) {
		_hoops_PIIS (_hoops_RIGC, _hoops_GAGHH, &_hoops_PSACR, _hoops_RHIPH, &locks, &_hoops_SRGHH, null, _hoops_CCSPH, control);
		_hoops_HPRH (_hoops_GAGHH);
	}
	if (internal != null) {
		_hoops_PIIS (_hoops_RIGC, internal, &_hoops_PSACR, _hoops_RHIPH, &locks, &_hoops_SRGHH, null, _hoops_CCSPH, control);
		_hoops_HPRH (internal);
	}

	if (_hoops_PSACR == null) {
		if (type > 0)
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, Sprintf_D (null, "No net attribute, type %d", type));
	}
	else if (_hoops_PSACR->_hoops_HIHI == 1)	/* _hoops_PIHA _hoops_SHH _hoops_PCCP _hoops_IGRI _hoops_PGAP _hoops_PIHAA	 */
		_hoops_PSACR->owner = _hoops_PGRCA(_hoops_SRCP);			/* _hoops_CAHAR _hoops_SR _hoops_CHR _hoops_HHRI _hoops_HPP _hoops_RH _hoops_HSPP _hoops_PHHIP */

	return	_hoops_PSACR;
}

local void _hoops_AAGHH (
	int						_hoops_PAGHH,
	int						_hoops_HAGHH,
	_hoops_CRCP const ** &		_hoops_SISAA) {
	_hoops_CRCP const **		_hoops_IAGHH = _hoops_SISAA;

	ALLOC_ARRAY (_hoops_SISAA, _hoops_HAGHH, _hoops_CRCP const *);
	_hoops_AIGA (_hoops_IAGHH, _hoops_AHIA (_hoops_PAGHH, _hoops_HAGHH), _hoops_CRCP *, _hoops_SISAA);
	FREE_ARRAY (_hoops_IAGHH, _hoops_PAGHH, _hoops_CRCP const *);
}

local bool _hoops_CAGHH (
	_hoops_CRCP const *			_hoops_SRCP,
	_hoops_CRCP const *			limit,
	int &					allocated,
	_hoops_CRCP const ** &		_hoops_SISAA,
	int &					count) {
	int						_hoops_HAHC = count;

	if (_hoops_SRCP == limit)
		return true;

	if (_hoops_SRCP == HOOPS_WORLD->root || _hoops_SRCP == null)
		return false;

	if (!_hoops_CAGHH (_hoops_SRCP->owner, limit, allocated, _hoops_SISAA, count)) {
		count = _hoops_HAHC;
		return false;
	}

	if (count == allocated)
		_hoops_AAGHH (count, allocated *= 2, _hoops_SISAA);

	if (_hoops_SRCP->type != _hoops_PIRIR)
		_hoops_SISAA[count++] = _hoops_SRCP;

	return true;
}

GLOBAL_FUNCTION int HI_Convert_Keys_To_Path (
	_hoops_AIGPR *	_hoops_RIGC,
	int						in_count,
	Key const *				keys,
	_hoops_CRCP const ** &		_hoops_SISAA) {
	_hoops_CRCP const *			prev = null;
	_hoops_CRCP const *			includee = null;
	int						_hoops_PSSPA = 0;
	int						allocated = 32;
	bool					_hoops_SAGHH = false;

	ALLOC_ARRAY (_hoops_SISAA, allocated, _hoops_CRCP const*);

	while (in_count-- > 0) {
		_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *)_hoops_SISIR (_hoops_RIGC, keys[in_count], prev);

		if (_hoops_SRCP == null)
			_hoops_SRCP = includee;

		if (prev && _hoops_SRCP->owner != prev)
			_hoops_CAGHH (_hoops_SRCP->owner, prev, allocated, _hoops_SISAA, _hoops_PSSPA);

		if (_hoops_SRCP == null || BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR) ||
			_hoops_SRCP->type != _hoops_IRCP && _hoops_SRCP->type != _hoops_AGRPR) {
			if (_hoops_SRCP != null &&
				_hoops_SRCP->type >= _hoops_AHRIR &&
				_hoops_SRCP->type <= _hoops_PHRIR) {
				++in_count;
				break;
			}
			else {
				if (_hoops_SAGHH) {
					HE_ERROR (HEC_SEGMENT, HES_INVALID_KEY,
							  "Provided key does not refer to a valid Segment, Include, or Geometry");
					FREE_ARRAY (_hoops_SISAA, allocated, _hoops_CRCP *);
					return 0;
				}
				else
					_hoops_SAGHH = true;
			}
		}

		if (_hoops_SRCP == null || _hoops_SRCP->type == _hoops_IRCP) {
			if (_hoops_SRCP != prev) {
				if (_hoops_PSSPA == allocated)
					_hoops_AAGHH (_hoops_PSSPA, allocated *= 2, _hoops_SISAA);
				_hoops_SISAA[_hoops_PSSPA++] = _hoops_SRCP;
			}
			prev = _hoops_SRCP;
		}
		else {
			if (prev == null)
				_hoops_CAGHH (_hoops_SRCP->owner, HOOPS_WORLD->root, allocated, _hoops_SISAA, _hoops_PSSPA);
			includee = _hoops_SSIGP ((Subsegment *)_hoops_SRCP);	// _hoops_PHHIP _hoops_CPSA _hoops_PCCP _hoops_GPAPA
			if (_hoops_PSSPA == allocated)
				_hoops_AAGHH (_hoops_PSSPA, allocated *= 2, _hoops_SISAA);
			_hoops_SISAA[_hoops_PSSPA++] = includee;
			prev = includee;
		}
	}

	/* _hoops_GII _hoops_HHRPA _hoops_CRGIA (_hoops_CGHI _hoops_CHHHP) _hoops_GHCA _hoops_SHH _hoops_CPAP _hoops_PRCHR _hoops_PPR _hoops_IRS _hoops_CPAP _hoops_SIC */
	while (in_count-- > 0) {
		Geometry const *		geo = (Geometry const *)_hoops_SISIR (_hoops_RIGC, keys[in_count], prev);

		if (geo == null ||
			geo->type < _hoops_AHRIR || geo->type > _hoops_PHRIR) {
			HE_ERROR (HEC_SEGMENT, HES_INVALID_KEY,
					  "Provided key does not refer to a valid Segment, Include, or Geometry");
			FREE_ARRAY (_hoops_SISAA, allocated, _hoops_CRCP *);
			return 0;
		}

		if (geo->type == _hoops_AHIP) {
			_hoops_PHIP *		_hoops_RRA = (_hoops_PHIP *)geo;

			// _hoops_RCPS _hoops_GH _hoops_CCA _hoops_HHH _hoops_CAGH _hoops_GAR '_hoops_GCPC' _hoops_IH _hoops_SPS _hoops_SIC
			if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP)
				prev = (_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0];
			else
				prev = (_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0]->owner;
		}
		else if (in_count != 0) {
			HE_ERROR (HEC_SEGMENT, HES_INVALID_KEY,
					  "Only one non-reference Geometry may be specified");
			FREE_ARRAY (_hoops_SISAA, allocated, _hoops_CRCP *);
			return 0;
		}


		if (_hoops_PSSPA == allocated)
			_hoops_AAGHH (_hoops_PSSPA, allocated *= 2, _hoops_SISAA);
		_hoops_SISAA[_hoops_PSSPA++] = (_hoops_CRCP const *)geo;
	}

	_hoops_AAGHH (allocated, _hoops_PSSPA, _hoops_SISAA);
	return	_hoops_PSSPA;
}


GLOBAL_FUNCTION Attribute * HI_Find_Net_Attribute_By_Path (
	_hoops_AIGPR *			_hoops_RIGC,
	int								count,
	_hoops_CRCP const **				_hoops_SISAA,
	Type							type,
	int								_hoops_CCSPH,
	_hoops_CRACA const *	control)
{
	bool					_hoops_GPGHH = false;
	_hoops_CRCP const *			_hoops_SRCP = null;
	Attribute *				_hoops_PSACR = null;
	_hoops_PIGRA			locks, _hoops_SACRP;
	unsigned int *			conditions;
	int						_hoops_IRCAA;
	Type					_hoops_RHIPH = Abs(type);

	_hoops_RSIIR(_hoops_RIGC);

	ASSERT(!ANYBIT(_hoops_CCSPH, _hoops_ISCAP|_hoops_HSCAP|_hoops_SRACA) || control!=null);

	if (type == _hoops_RHAGP)
		return null;	/* (_hoops_IH _hoops_RAGHH) */

	ZERO_STRUCT (&locks, _hoops_PIGRA);
	ZERO_STRUCT (&_hoops_SACRP, _hoops_PIGRA);

	if ((_hoops_IRCAA = HOOPS_WORLD->_hoops_AGCAA / 32) == 0)
		_hoops_IRCAA = 1;
	ZALLOC_ARRAY (conditions, _hoops_IRCAA, unsigned int);
	if (control != null && control->conditions != null)
		_hoops_ISIAA (conditions, control->conditions, _hoops_IRCAA * sizeof (unsigned int));


	if (control != null) {
		if (control->locks != null)
			_hoops_RSAI (control->locks, _hoops_PIGRA, &locks);
		if (control->_hoops_SACRP != null)
			_hoops_RSAI (control->_hoops_SACRP, _hoops_PIGRA, &_hoops_SACRP);

		_hoops_GPGHH = BIT (_hoops_CCSPH, _hoops_HSCAP);	// _hoops_PSP _hoops_RPIP _hoops_ARP _hoops_RPGHH
	}

	if (*_hoops_SISAA == null) {
		_hoops_GPGHH = true;
		_hoops_SISAA++;
		count--;
	}

	if (!_hoops_GPGHH) {
		/* _hoops_SGARH _hoops_SRS _hoops_CAGH _hoops_IH _hoops_CIH */
		_hoops_SRCP = *_hoops_SISAA++;
		--count;
		_hoops_IGARH (_hoops_RIGC, _hoops_SRCP, &_hoops_PSACR, _hoops_RHIPH, &locks, &_hoops_SACRP, conditions, _hoops_CCSPH, control);
	}

	/* _hoops_ACSP _hoops_SAHR _hoops_RARHR */
	while (count-- > 0) {
		_hoops_SRCP = *_hoops_SISAA++;

		if (_hoops_SRCP->type == _hoops_IRCP) {
			if (_hoops_SRCP->_hoops_IPPGR != null)
				_hoops_PIIS (_hoops_RIGC, _hoops_SRCP->_hoops_IPPGR, &_hoops_PSACR, _hoops_RHIPH, &locks, &_hoops_SACRP, conditions, _hoops_CCSPH, control);
		}
		else {	/* _hoops_CPAP */
			Geometry const *	geo = (Geometry const *)_hoops_SRCP;
			if (geo->_hoops_IPPGR != null)
				_hoops_PIIS (_hoops_RIGC, geo->_hoops_IPPGR, &_hoops_PSACR, _hoops_RHIPH, &locks, &_hoops_SACRP, null, _hoops_CCSPH, control);
		}
	}

	FREE_ARRAY (conditions, _hoops_IRCAA, unsigned int);

	if (_hoops_PSACR != null) {
		if (_hoops_PSACR->_hoops_HIHI == 1)	/* _hoops_PIHA _hoops_SHH _hoops_PCCP _hoops_IGRI _hoops_PGAP _hoops_PIHAA */
			_hoops_PSACR->owner = (_hoops_CRCP *)_hoops_SRCP;		/* _hoops_HIIC _hoops_CGH _hoops_SHH _hoops_ICIC */
	}
#if 0 /* _hoops_APGHH */
	else if (!_hoops_GPGHH) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							Sprintf_D (null, "No net attribute, type %d", type));
	}
#endif

	if (_hoops_PSACR != null && type == HK_MODELLING_MATRIX) {
		/* _hoops_GCHRR _hoops_RSGA _hoops_GHCA _hoops_SHH _hoops_CRGP _hoops_HSAR _hoops_RH _hoops_AARRA (_hoops_AAHRP _hoops_IIGR _hoops_PPGHH) */
		_hoops_HRPA alter *		mat = &((_hoops_ISGI *)_hoops_PSACR)->matrix;
		_hoops_RPRA alter *		m = mat->elements;
		float					scale, tmp;

		mat->_hoops_RAGR = _hoops_SGICR;

		if (m[0][2] != 0.0f || m[1][2] != 0.0f || m[3][2] != 0.0f)
			mat->_hoops_RAGR |= _hoops_RRICR;

		scale = m[0][0] * m[0][0]  +  m[1][0] * m[1][0]	 +	m[2][0] * m[2][0];
		if (scale != 1.0f || m[0][0] == -1.0f)
			mat->_hoops_RAGR |= _hoops_CHCP;
		mat->_hoops_CPH = _hoops_SGIHR (scale);
		tmp = m[0][1] * m[0][1]	 +	m[1][1] * m[1][1]  +  m[2][1] * m[2][1];
		if (tmp != 1.0f || m[1][1] == -1.0f)
			mat->_hoops_RAGR |= _hoops_CHCP;
		if (tmp != scale) mat->_hoops_CPH = 0.0f;
		tmp = m[0][2] * m[0][2]	 +	m[1][2] * m[1][2]  +  m[2][2] * m[2][2];
		if (tmp != 1.0f || m[2][2] == -1.0f)
			mat->_hoops_RAGR |= _hoops_CHCP;
		if (tmp != scale) mat->_hoops_CPH = 0.0f;

		if (m[3][0] != 0.0f || m[3][1] != 0.0f || m[3][2] != 0.0f)
			mat->_hoops_RAGR |= _hoops_PRICR;

		if (m[0][1] != 0.0f || m[0][2] != 0.0f ||
			m[1][0] != 0.0f || m[1][2] != 0.0f ||
			m[2][0] != 0.0f || m[2][1] != 0.0f)
			mat->_hoops_RAGR |= _hoops_GRICR;
	}

	return	_hoops_PSACR;
}


GLOBAL_FUNCTION Attribute * HI_Find_Attribute_And_Lock (
	_hoops_AIGPR *			_hoops_RIGC,
	_hoops_IPRRA						_hoops_HPGHH,
	int								_hoops_CCSPH,
	int								count,
	Key const *						keys,
	_hoops_HPAH **						_hoops_IPGHH,
	_hoops_CRACA const *	control)
{
	ASSERT(BIT(_hoops_HPGHH, _hoops_ARGPP));
	ASSERT(!ANYBIT(_hoops_CCSPH, _hoops_ISCAP|_hoops_HSCAP|_hoops_SRACA) || control!=null);

	_hoops_HPAH *	target = null;
	Attribute * _hoops_HPHCR = null;

	if (BIT(_hoops_CCSPH, _hoops_HRPCR)) {
		Type	_hoops_CPGHH = _hoops_RAGPP(_hoops_HPGHH);
		ASSERT(_hoops_CPGHH > 0);

		if (BIT(_hoops_CCSPH, _hoops_CSCAP))
			_hoops_CPGHH = -_hoops_CPGHH;

		if (count == 0) {
			target = HI_Find_Target_And_Lock(_hoops_RIGC, _hoops_HPGHH);
			if (target != null) {
				_hoops_HPHCR = HI_Find_Net_Attribute (_hoops_RIGC, target, _hoops_CPGHH, _hoops_CCSPH, control);
				if (_hoops_HPHCR == null)
					_hoops_IRRPR();
			}
		}
		else {
			if (!BIT(_hoops_HPGHH, _hoops_SRGPP))
				_hoops_CSPPR();
			else
				_hoops_RSIIR(_hoops_RIGC);

			_hoops_CRCP const **		_hoops_SISAA;
			int						_hoops_CISAA;

			if (_hoops_CPGHH == _hoops_RHAGP)
				return null;	/* (_hoops_IH _hoops_RAGHH) */

			if ((_hoops_CISAA = HI_Convert_Keys_To_Path (_hoops_RIGC, count, keys, _hoops_SISAA)) > 0)
				_hoops_HPHCR = HI_Find_Net_Attribute_By_Path (_hoops_RIGC, _hoops_CISAA, (_hoops_CRCP const **)_hoops_SISAA, _hoops_CPGHH, _hoops_CCSPH, control);
			else
				HE_ERROR (HEC_SEGMENT, HES_INVALID_KEY, "Provided key does not refer to a valid Segment");

			if (_hoops_CISAA > 0)
				FREE_ARRAY (_hoops_SISAA, _hoops_CISAA, _hoops_CRCP const *);

			if (_hoops_HPHCR == null &&
				!BIT(_hoops_HPGHH, _hoops_SRGPP))
				_hoops_IRRPR();
		}
	}
	else {
		ASSERT(0);
	}

	if (_hoops_IPGHH != null)
		*_hoops_IPGHH = target;

	return _hoops_HPHCR;
}

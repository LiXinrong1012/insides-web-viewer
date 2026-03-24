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
 * $Id: obf_tmp.txt 1.178 2010-12-15 02:58:36 covey Exp $
 */


#include "hoops.h"
#include "database.h"
#include "patterns.h"
#include "driver.h"
#include "please.h"
#include "select.h"
#include "tandt.h"		/* _hoops_IH _hoops_SIRPS _hoops_AGIR */
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "adt.h"


/* _hoops_PHPHA _hoops_HII _hoops_RIPIP; _hoops_AHIHR _hoops_AIRC _hoops_RHSI;
 * _hoops_IPHIA._hoops_GGHR _hoops_PPR '_hoops_AGIR _hoops_GCRPS' _hoops_RRAI.
 */

GLOBAL_FUNCTION void HD_Selection_Downwind (
	Net_Rendition alter &		nr,
	Attribute const *			_hoops_HPPGR) {
#ifndef DISABLE_SELECTION
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP const	*	sc = dc->_hoops_APHHP;
	_hoops_PIGRA				_hoops_PCGS, _hoops_CIIAA;
	bool						_hoops_RPGIP = false;

	/*** _hoops_ISAP _hoops_HCGC _hoops_IS _hoops_CACH _hoops_RPP _hoops_HSAGA _hoops_HRGR _hoops_IGRC _hoops_IHGS _hoops_HGAS! ***/

	/* _hoops_HSPP _hoops_CCA _hoops_SGHS _hoops_GCIAA _hoops_HII _hoops_ARRS */
	_hoops_RSAI (&nr->_hoops_IRR->locks, _hoops_PIGRA, &_hoops_PCGS);
	ZERO_STRUCT (&_hoops_CIIAA, _hoops_PIGRA);

	/* _hoops_RRP _hoops_IS _hoops_ISPR _hoops_IH _hoops_RCIAA _hoops_ACIAA _hoops_RSIH, _hoops_IS _hoops_CGIC
	** _hoops_IGH _hoops_PAR _hoops_HAR _hoops_PA _hoops_ARPP _hoops_SCH (_hoops_SHCAR, _hoops_PCIAA) _hoops_GHCA _hoops_SHH _hoops_IGI _hoops_HCIAA */
	Attribute const	*_hoops_HPGIP = _hoops_HPPGR;

	do {
		if (_hoops_HPPGR->type > _hoops_IAAA (_hoops_CPPIR, HK_RENDERING_OPTIONS, HK_COLOR_MAP, _hoops_HAAIR))
			break;

		switch (_hoops_HPPGR->type) {
			case _hoops_CPPIR: {
				_hoops_SPPIR const *			_hoops_GHPIR = (_hoops_SPPIR const *)_hoops_HPPGR;
				_hoops_ISHHP alter	&	_hoops_RHIHP = nr.Modify()->_hoops_ASIR.Modify();

				if (HOOPS_WORLD->_hoops_PCIIR > 0) {

					if (_hoops_GHPIR->count > 0) {
						int	count = HOOPS_WORLD->_hoops_AGCAA / 32;

						if (_hoops_RHIHP->conditions._hoops_RCHA == null) {
							POOL_ZALLOC_ARRAY (_hoops_RHIHP->conditions._hoops_RCHA, count, unsigned int, dc->memory_pool);
							_hoops_RHIHP->conditions.count = count;
						}
						else if (_hoops_RHIHP->conditions.count < count) {
							unsigned int *	_hoops_IPGIP = _hoops_RHIHP->conditions._hoops_RCHA;
							int				_hoops_IRCSA = _hoops_RHIHP->conditions.count;

							POOL_ZALLOC_ARRAY (_hoops_RHIHP->conditions._hoops_RCHA, count, unsigned int, dc->memory_pool);
							_hoops_AIGA (_hoops_IPGIP, _hoops_IRCSA, unsigned int, _hoops_RHIHP->conditions._hoops_RCHA);
							FREE_ARRAY (_hoops_IPGIP, _hoops_IRCSA, unsigned int);
							_hoops_RHIHP->conditions.count = count;
						}

						_hoops_HSIAA (_hoops_RHIHP->conditions._hoops_RCHA, _hoops_GHPIR->_hoops_SGCAA, _hoops_GHPIR->count*sizeof(unsigned int));
						_hoops_ISIAA (_hoops_RHIHP->conditions._hoops_RCHA, _hoops_GHPIR->values, _hoops_GHPIR->count*sizeof(unsigned int));

						if (!_hoops_RHIHP->conditions._hoops_CPGIP)
							_hoops_RHIHP->conditions._hoops_CPGIP = POOL_NEW(dc->memory_pool, _hoops_SPGIP)(dc->memory_pool);

						_hoops_PRRH(_hoops_GHPIR);
						_hoops_RHIHP->conditions._hoops_CPGIP->AddFirst(_hoops_GHPIR);
	#if 0
						for (int i=0; i<_hoops_GHPIR->count; i++) {
							unsigned int	mask = _hoops_GHPIR->_hoops_SGCAA[i];
							unsigned int	value = _hoops_GHPIR->values[i];
							unsigned int	_hoops_IPGIP = _hoops_RHIHP->conditions._hoops_RCHA[i];
							int				index = i * 32;

							while (mask != 0) {

								if ((mask & 1) != 0 && ((value^_hoops_IPGIP) & 1) != 0) {

									if ((value & 1) != 0)
										_hoops_PRRH (HOOPS_WORLD->_hoops_PCIIR[index]);
									else 
										_hoops_HPRH (HOOPS_WORLD->_hoops_PCIIR[index]);
								}

								mask >>= 1;
								value >>= 1;
								_hoops_IPGIP >>= 1;
								++index;
							}
						}
	#endif
						// _hoops_ASIGA _hoops_SIGR _hoops_IHSHH _hoops_RPP (_hoops_RCRPS->_hoops_PGSI != _hoops_IRAP) {
					}
				}
			}	break;

			case HK_RENDERING_OPTIONS: {
				_hoops_RHAIR const	*_hoops_AHAIR = (_hoops_RHAIR const *)_hoops_HPPGR;

				if (_hoops_AHAIR->locks != null) {

					if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_GSIAA)) {
						_hoops_GRGH const &	_hoops_RRGH = nr->_hoops_IRR;
						_hoops_PIGRA			_hoops_PHGIP;

						/* _hoops_PA _hoops_HSGRA _hoops_HRGR _hoops_HCAGR _hoops_ASIAA _hoops_HCIAA */
						_hoops_RSAI (&_hoops_AHAIR->locks->normal.mask, _hoops_PIGRA, &_hoops_CIIAA);
						// _hoops_HIH _hoops_HAR _hoops_PA _hoops_GRGA _hoops_ARP _hoops_IS _hoops_SSPC
						_hoops_HSIAA (&_hoops_CIIAA, &_hoops_RRGH->_hoops_HHGIP, sizeof (_hoops_PIGRA));

						/* _hoops_HASC _hoops_CCAH _hoops_AAHS _hoops_HRP */
						_hoops_HSIAA (&_hoops_PCGS, &_hoops_CIIAA, sizeof (_hoops_PIGRA));
						/* _hoops_PIASR _hoops_HRGR _hoops_PA _hoops_SR _hoops_HHGC _hoops_IS _hoops_AAHS, _hoops_ACCHA _hoops_GII _hoops_SR _hoops_SPGA'_hoops_RA _hoops_PHRH _hoops_IS _hoops_AGRP */
						_hoops_RSAI (&_hoops_AHAIR->locks->normal.value, _hoops_PIGRA, &_hoops_PHGIP);
						_hoops_HSIAA (&_hoops_PHGIP, &_hoops_RRGH->_hoops_HHGIP, sizeof (_hoops_PIGRA));

						_hoops_ISIAA (&_hoops_PCGS, &_hoops_PHGIP, sizeof (_hoops_PIGRA));

						/* _hoops_PPR _hoops_ARP _hoops_GPP _hoops_IPP */
						if (!EQUAL_MEMORY (&_hoops_PCGS, sizeof (_hoops_PIGRA), &_hoops_RRGH->locks)) {
							_hoops_GRGH alter &	_hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();

							_hoops_RSAI (&_hoops_PCGS, _hoops_PIGRA, &_hoops_APIHP->locks);
						}

						/* _hoops_IH _hoops_IRGH _hoops_HCGC _hoops_ARP _hoops_RGR _hoops_IS _hoops_SRCH _hoops_CSIAA '_hoops_PCPAR _hoops_HIH _hoops_HCIAA _hoops_ASIAA' */
						_hoops_HSIAA (&_hoops_PCGS, &_hoops_CIIAA, sizeof (_hoops_PIGRA));
					}
					if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_RGRAP)) {
						_hoops_GRGH alter &	_hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();

						// _hoops_AGCR _hoops_SAHR _hoops_RARHR -- _hoops_RPSI _hoops_PAH _hoops_HAR _hoops_HHSP
						_hoops_ISIAA (&_hoops_APIHP->_hoops_HHGIP, &_hoops_AHAIR->locks->_hoops_SACRP.value, sizeof (_hoops_PIGRA));
					}
				}

				/* _hoops_GCAC _hoops_AAP _hoops_CGH _hoops_SHH _hoops_SRS, _hoops_HIH _hoops_AA _hoops_RGR _hoops_ARI _hoops_GGR _hoops_AGIR _hoops_SCH _hoops_SHPH */
				if (!BIT (_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_RENDERING_OPTIONS)) &&
					BIT (_hoops_AHAIR->_hoops_SCIAA & _hoops_AHAIR->_hoops_RSIAA, _hoops_AGICA) &&
					_hoops_AHAIR->_hoops_PGICA != _hoops_GCAAP) {
					_hoops_ISGI		temp;

					temp._hoops_RRHH = _hoops_RSPCR;

					if (ANYBIT (_hoops_AHAIR->_hoops_PGICA, _hoops_ACAAP)) {
						_hoops_SGCC const &	_hoops_HSGA = nr->transform_rendition->_hoops_IPH;

						if (BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_CIAAP)) {
							HI_Copy_Matrix (&_hoops_HSGA->data, &temp.matrix);
							if (!BIT (_hoops_AHAIR->_hoops_PGICA,
									  _hoops_IIAAP)) {
								HI_Normalize ((Vector *)&temp.matrix.elements[0][0]);
								HI_Normalize ((Vector *)&temp.matrix.elements[1][0]);
								HI_Normalize ((Vector *)&temp.matrix.elements[2][0]);
							}
							temp.matrix.elements[3][0] =
								temp.matrix.elements[3][1] =
									temp.matrix.elements[3][2] = 0.0f;
							HI_Validate_Matrix_Adjoint (&temp.matrix);
							_hoops_AIGA (&temp.matrix._hoops_APRA->data.elements[0][0],
										 16, float,
										 &temp.matrix.elements[0][0]);
							/* _hoops_RSGA _hoops_IHGIP _hoops_CHGIP, _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_ASSP'_hoops_RA _hoops_IHSH _hoops_PRAR _hoops_GIR */
							//_hoops_IRHP._hoops_RSGA._hoops_SGI &= _hoops_GSSPH;
							temp.matrix._hoops_APRA = null;
							temp.matrix._hoops_CPH = 0.0f;

							HD_Downwind_Modelling_Matrix (nr, (Attribute const *)&temp);
						}
						else if (BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_IIAAP)) {
							float			_hoops_PIIH, _hoops_HIIH, _hoops_SHGIP;

							_hoops_PIIH = (float)HI_Compute_Vector_Length ((Vector const *)&_hoops_HSGA->data.elements[0][0]);
							_hoops_HIIH = (float)HI_Compute_Vector_Length ((Vector const *)&_hoops_HSGA->data.elements[1][0]);
							_hoops_SHGIP = (float)HI_Compute_Vector_Length ((Vector const *)&_hoops_HSGA->data.elements[2][0]);

							if (_hoops_PIIH == 0.0f)
								_hoops_PIIH = 1.0f;
							if (_hoops_HIIH == 0.0f)
								_hoops_HIIH = 1.0f;
							if (_hoops_SHGIP == 0.0f)
								_hoops_SHGIP = 1.0f;

							HI_Figure_Scale_Matrix (1.0f / _hoops_PIIH, 1.0f / _hoops_HIIH, 1.0f / _hoops_SHGIP, &temp.matrix);
							HD_Downwind_Modelling_Matrix (nr, (Attribute const *)&temp);
						}
						if (BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_SIAAP)) {
							HI_Ident_Matrix (&temp.matrix);
							temp.matrix.elements[3][0] = -_hoops_HSGA->data.elements[3][0];
							temp.matrix.elements[3][1] = -_hoops_HSGA->data.elements[3][1];
							temp.matrix.elements[3][2] = -_hoops_HSGA->data.elements[3][2];
							temp.matrix._hoops_RAGR = _hoops_PRICR;
							if (temp.matrix.elements[3][2] != 0.0f)
								temp.matrix._hoops_RAGR |= _hoops_RRICR;
							HD_Downwind_Modelling_Matrix (nr, (Attribute const *)&temp);
						}
					}

					if (ANYBIT (_hoops_AHAIR->_hoops_PGICA, _hoops_RCAAP)) {
						_hoops_HHRA const *		_hoops_SPH = nr->transform_rendition->_hoops_SPH;

						if (BIT (_hoops_AHAIR->_hoops_PGICA,
								 _hoops_HIAAP)) {
							/* _hoops_RRP _hoops_IS _hoops_RGHH _hoops_RGR _hoops_SPHR _hoops_PGGA _hoops_SR _hoops_HHGC _hoops_SCH _hoops_IS *_hoops_GCIS* _hoops_GII _hoops_IRGH _hoops_PRGIA */
							_hoops_RPGIP = true;
						}
						if (BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_PIAAP)) {
							HI_Ident_Matrix (&temp.matrix);
							temp.matrix.elements[3][0] = _hoops_SPH->target.x;
							temp.matrix.elements[3][1] = _hoops_SPH->target.y;
							temp.matrix.elements[3][2] = _hoops_SPH->target.z;
							temp.matrix._hoops_RAGR = _hoops_PRICR;
							if (temp.matrix.elements[3][2] != 0.0f)
								temp.matrix._hoops_RAGR |= _hoops_RRICR;
							HD_Downwind_Modelling_Matrix (nr, (Attribute const *)&temp);
						}
						if (BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_AIAAP)) {
							HI_Ident_Matrix (&temp.matrix);
							temp.matrix.elements[0][0] = _hoops_SPH->_hoops_CRSS.x;
							temp.matrix.elements[0][1] = _hoops_SPH->_hoops_CRSS.y;
							temp.matrix.elements[0][2] = _hoops_SPH->_hoops_CRSS.z;
							temp.matrix.elements[1][0] = _hoops_SPH->up_vector.x;
							temp.matrix.elements[1][1] = _hoops_SPH->up_vector.y;
							temp.matrix.elements[1][2] = _hoops_SPH->up_vector.z;
							temp.matrix.elements[2][0] = _hoops_SPH->_hoops_IIPCR.x;
							temp.matrix.elements[2][1] = _hoops_SPH->_hoops_IIPCR.y;
							temp.matrix.elements[2][2] = _hoops_SPH->_hoops_IIPCR.z;
							temp.matrix._hoops_CPH = 1.0f;
							temp.matrix._hoops_RAGR = _hoops_GRICR |
											_hoops_RRICR;

							HD_Downwind_Modelling_Matrix (nr, (Attribute const *)&temp);
						}
						if (BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_RIAAP)) {
							float			scale;

							scale = _hoops_SPH->_hoops_SSPA / 2.0f;

							HI_Figure_Scale_Matrix (scale, scale, scale, &temp.matrix);
							HD_Downwind_Modelling_Matrix (nr, (Attribute const *)&temp);
						}
					}
				}
			} break;

			case _hoops_HAAIR: {
				_hoops_IAAIR const *			_hoops_CAAIR = (_hoops_IAAIR const *)_hoops_HPPGR;

				if (_hoops_CAAIR->count > 0) {
					_hoops_RIGIP alter &	_hoops_AIGIP = nr.Modify()->_hoops_PIGIP.Modify();
					_hoops_GPAIR *					_hoops_GIGIP;
					int *							new_keys;
					int								_hoops_RGCCA;

					_hoops_RGCCA = _hoops_AIGIP->count + _hoops_CAAIR->count;

					POOL_ZALLOC_ARRAY (_hoops_GIGIP, _hoops_RGCCA, _hoops_GPAIR, dc->memory_pool);
					POOL_ALLOC_ARRAY (new_keys, _hoops_RGCCA, Integer32, dc->memory_pool);

					for (int i=0; i<_hoops_CAAIR->count; ++i)
						_hoops_GIGIP[i] = _hoops_CAAIR->_hoops_SAAIR[i];
					_hoops_AIGA (_hoops_CAAIR->keys, _hoops_CAAIR->count, Integer32, new_keys);

					if (_hoops_AIGIP->count) {
						// _hoops_PIP, _hoops_HIGIP _hoops_AGCR
						_hoops_AIGA (_hoops_AIGIP->_hoops_SAAIR, _hoops_AIGIP->count, _hoops_GPAIR, &_hoops_GIGIP[_hoops_CAAIR->count]);
						FREE_ARRAY (_hoops_AIGIP->_hoops_SAAIR, _hoops_AIGIP->count, _hoops_GPAIR);

						_hoops_AIGA (_hoops_AIGIP->keys, _hoops_AIGIP->count, Integer32, &new_keys[_hoops_CAAIR->count]);
						FREE_ARRAY (_hoops_AIGIP->keys, _hoops_AIGIP->count, Integer32);
					}

					_hoops_AIGIP->_hoops_SAAIR = _hoops_GIGIP;
					_hoops_AIGIP->keys = new_keys;
					_hoops_AIGIP->count = _hoops_RGCCA;
				}
			} break;

			default:
				break;
		}
	} while ((_hoops_HPPGR = _hoops_HPPGR->next) != null);

	_hoops_HPPGR = _hoops_HPGIP;

	do switch (_hoops_HPPGR->type) {
		/* (_hoops_SRCH _hoops_RIHH _hoops_RPGP _hoops_HPGR _hoops_PRPC) */
		case HK_COLOR:
		case HK_DRIVER_OPTIONS:
		case HK_FACE_PATTERN:
		case _hoops_GRAIR:
		case HK_USER_VALUE:
		case HK_TEXTURE_MATRIX:
		case _hoops_IPAIR:
		case HK_WINDOW_PATTERN: {
		}	break;

		case HK_DRIVER: {
			nr.Modify()->_hoops_SAIR.Modify()->_hoops_ASIHP &= ~(_hoops_GCARP | _hoops_RCARP);
		}	break;


		case _hoops_RAAIR: {
			_hoops_AAAIR const *		_hoops_CGGHH = (_hoops_AAAIR const *)_hoops_HPPGR;

			if (_hoops_CGGHH->count > 0) {
				_hoops_GHRIP alter &		_hoops_RHRIP = nr.Modify()->glyph_rendition.Modify();
				_hoops_GASC *						_hoops_SPRIP;
				int *						new_keys;
				int							_hoops_RGCCA;

				_hoops_RGCCA = _hoops_RHRIP->count + _hoops_CGGHH->count;

				POOL_ZALLOC_ARRAY (_hoops_SPRIP, _hoops_RGCCA, _hoops_GASC, dc->memory_pool);
				POOL_ALLOC_ARRAY (new_keys, _hoops_RGCCA, Integer32, dc->memory_pool);

				for (int i=0; i<_hoops_CGGHH->count; ++i)
					_hoops_SPRIP[i] = _hoops_CGGHH->glyphs[i];
				_hoops_AIGA (_hoops_CGGHH->keys, _hoops_CGGHH->count, Integer32, new_keys);

				if (_hoops_RHRIP->count) {
					// _hoops_PIP, _hoops_HIGIP _hoops_AGCR
					_hoops_AIGA (_hoops_RHRIP->glyphs, _hoops_RHRIP->count, _hoops_GASC, &_hoops_SPRIP[_hoops_CGGHH->count]);
					FREE_ARRAY (_hoops_RHRIP->glyphs, _hoops_RHRIP->count, _hoops_GASC);

					_hoops_AIGA (_hoops_RHRIP->keys, _hoops_RHRIP->count, Integer32, &new_keys[_hoops_CGGHH->count]);
					FREE_ARRAY (_hoops_RHRIP->keys, _hoops_RHRIP->count, Integer32);
				}

				_hoops_RHRIP->glyphs = _hoops_SPRIP;
				_hoops_RHRIP->keys = new_keys;
				_hoops_RHRIP->count = _hoops_RGCCA;
			}
		} break;

		case _hoops_HAAIR: {
			// _hoops_RSGIP _hoops_RSIH
		} break;

		case _hoops_RPAIR: {
			_hoops_APAIR const *		_hoops_ACRPS = (_hoops_APAIR const *)_hoops_HPPGR;

			if (_hoops_ACRPS->count > 0) {
				_hoops_PHRIP alter &	_hoops_HHRIP = nr.Modify()->_hoops_GCSHP.Modify();
				Line_Style *					_hoops_AHRIP;
				int *							new_keys;
				int								_hoops_RGCCA;

				_hoops_RGCCA = _hoops_HHRIP->count + _hoops_ACRPS->count;

				POOL_ZALLOC_ARRAY (_hoops_AHRIP, _hoops_RGCCA, Line_Style, dc->memory_pool);
				POOL_ALLOC_ARRAY (new_keys, _hoops_RGCCA, Integer32, dc->memory_pool);

				for (int i=0; i<_hoops_ACRPS->count; ++i)
					_hoops_AHRIP[i] = _hoops_ACRPS->_hoops_HPAIR[i];
				_hoops_AIGA (_hoops_ACRPS->keys, _hoops_ACRPS->count, Integer32, new_keys);

				if (_hoops_HHRIP->count) {
					// _hoops_PIP, _hoops_HIGIP _hoops_AGCR
					_hoops_AIGA (_hoops_HHRIP->_hoops_HPAIR, _hoops_HHRIP->count, Line_Style, &_hoops_AHRIP[_hoops_ACRPS->count]);
					FREE_ARRAY (_hoops_HHRIP->_hoops_HPAIR, _hoops_HHRIP->count, Line_Style);

					_hoops_AIGA (_hoops_HHRIP->keys, _hoops_HHRIP->count, Integer32, &new_keys[_hoops_ACRPS->count]);
					FREE_ARRAY (_hoops_HHRIP->keys, _hoops_HHRIP->count, Integer32);
				}

				_hoops_HHRIP->_hoops_HPAIR = _hoops_AHRIP;
				_hoops_HHRIP->keys = new_keys;
				_hoops_HHRIP->count = _hoops_RGCCA;

				if (!_hoops_HHRIP->_hoops_IHRIP)		// _hoops_RGAR _hoops_GPP _hoops_RH _hoops_SRRPR _hoops_CAGH
					_hoops_HHRIP->_hoops_IHRIP = HD_Find_Line_Style(nr, "-");
			}
		} break;

		case HK_EDGE_PATTERN:	if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_EDGE_PATTERN))) {
			_hoops_ISAIR const *	_hoops_CSAIR = (_hoops_ISAIR const *)_hoops_HPPGR;
			Line_Style					line_style;
			int							i;

			if (_hoops_CSAIR->mask == 0 ||
				BIT(_hoops_CSAIR->mask, _hoops_AICAP) ) {
				for (i=0; i<nr->_hoops_GCSHP->count; i++) {
					if (nr->_hoops_GCSHP->keys[i] == _hoops_CSAIR->_hoops_SCCAP &&
						_hoops_RAHSR(_hoops_CSAIR->line_style, nr->_hoops_GCSHP->_hoops_HPAIR[i]->name)) {
						line_style = nr->_hoops_GCSHP->_hoops_HPAIR[i];
						break;
					}
				}
				if (!line_style) {
					HE_WARNING (HEC_LINE_STYLE, HES_NOT_AVAILABLE,
						Sprintf_N (null, "Requested line style '%n' not found", &_hoops_CSAIR->line_style));
				}
			}

			if (_hoops_CSAIR->mask == 0) {
				if (line_style &&
					(nr->_hoops_RHP->line_style != line_style ||
						 nr->_hoops_RHP->style != _hoops_CSAIR->value)) {
					bool					_hoops_GRHPR = (nr->_hoops_RHP == nr->_hoops_CAIHP);
					Line_Rendition			_hoops_ASGIP = nr.Modify()->_hoops_RHP.Modify();

					_hoops_ASGIP->style = _hoops_CSAIR->value;
					_hoops_ASGIP->line_style = line_style;

					if (_hoops_GRHPR)
						nr->_hoops_CAIHP = nr->_hoops_RHP;
					else {
						_hoops_ASGIP = nr->_hoops_CAIHP.Modify();

						_hoops_ASGIP->style = _hoops_CSAIR->value;
						_hoops_ASGIP->line_style = line_style;
					}
				}
			}
			else {
				Line_Rendition alter &	_hoops_ASGIP = nr.Modify()->_hoops_RHP.Modify();

				if (BIT(_hoops_CSAIR->mask, _hoops_CICAP)) {
					_hoops_ASGIP->style &= ~LJOIN_MASK;
					_hoops_ASGIP->style |= _hoops_CSAIR->value & LJOIN_MASK;
				}
				if (BIT(_hoops_CSAIR->mask, _hoops_IICAP)) {
					_hoops_ASGIP->style &= ~LPAT_MASK;
					_hoops_ASGIP->style |= _hoops_CSAIR->value & LPAT_MASK;
				}

				if (BIT(_hoops_CSAIR->mask, _hoops_AICAP) && line_style)
					_hoops_ASGIP->line_style = line_style;
			}
		}	break;

		case HK_EDGE_WEIGHT:	if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_EDGE_WEIGHT))) {
			_hoops_RHCAP const *		_hoops_PSGIP = (_hoops_RHCAP const *)_hoops_HPPGR;

			if (nr->_hoops_RHP->_hoops_PHP != _hoops_PSGIP->data.value ||
				nr->_hoops_RHP->_hoops_HHP != _hoops_PSGIP->data._hoops_HHP) {
				bool						_hoops_GRHPR = (nr->_hoops_RHP == nr->_hoops_CAIHP);
				Line_Rendition alter &		_hoops_ASGIP = nr.Modify()->_hoops_RHP.Modify();

				_hoops_ASGIP->_hoops_PHP = _hoops_PSGIP->data.value;
				_hoops_ASGIP->_hoops_HHP = _hoops_PSGIP->data._hoops_HHP;

				if (_hoops_ASGIP->_hoops_HHP == _hoops_SHGRP)
					_hoops_ASGIP->weight = (int)(_hoops_ASGIP->_hoops_PHP *
										dc->_hoops_PGCC._hoops_IHHSR);
				else if (_hoops_ASGIP->_hoops_HHP == GSU_PIXELS)
					_hoops_ASGIP->weight = (int)(_hoops_ASGIP->_hoops_PHP + 0.5f);
				else
					_hoops_ASGIP->weight = -1;

				if (_hoops_ASGIP->weight != -1 && 
					(_hoops_ASGIP->weight < 0 || _hoops_ASGIP->weight > _hoops_CSGIP)) {
					_hoops_ASGIP->weight = (float)_hoops_CSGIP;
				}

				if (_hoops_GRHPR)
					nr->_hoops_CAIHP = nr->_hoops_RHP;
				else
					nr.Modify()->_hoops_CAIHP.Modify()->weight = nr->_hoops_RHP->weight;
			}
		}	break;

		case HK_LINE_PATTERN:	if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_LINE_PATTERN))) {
			_hoops_PSAIR const *	_hoops_HSAIR = (_hoops_PSAIR const *)_hoops_HPPGR;
			Line_Style					line_style;
			int							i;

			if (_hoops_HSAIR->mask == 0 ||
				BIT(_hoops_HSAIR->mask, _hoops_AICAP) ) {
				for (i=0; i<nr->_hoops_GCSHP->count; i++) {
					if (nr->_hoops_GCSHP->keys[i] == _hoops_HSAIR->_hoops_SCCAP &&
						_hoops_RAHSR(_hoops_HSAIR->line_style, nr->_hoops_GCSHP->_hoops_HPAIR[i]->name)) {
						line_style = nr->_hoops_GCSHP->_hoops_HPAIR[i];
						break;
					}
				}
				if (!line_style) {
					HE_WARNING (HEC_LINE_STYLE, HES_NOT_AVAILABLE,
								Sprintf_N (null, "Requested line style '%n' not found", &_hoops_HSAIR->line_style));
				}
			}

			if (_hoops_HSAIR->mask == 0) {
				if (line_style &&
					(nr->_hoops_AHP->line_style != line_style ||
						 nr->_hoops_AHP->style != _hoops_HSAIR->value)) {
					Line_Rendition alter & _hoops_ASGIP = nr.Modify()->_hoops_AHP.Modify();

					_hoops_ASGIP->start_glyph = null;
					_hoops_ASGIP->middle_glyph = null;
					_hoops_ASGIP->end_glyph = null;

					_hoops_ASGIP->flags &= ~(_hoops_RGRIP|_hoops_SRPI|_hoops_AGRIP);

					_hoops_ASGIP->style = _hoops_HSAIR->value;
					_hoops_ASGIP->line_style = line_style;
				}
			}
			else {
				int		glyph_count = 0;

				if (_hoops_HSAIR->start_glyph.length != 0)
					glyph_count++;
				if (_hoops_HSAIR->middle_glyph.length != 0)
					glyph_count++;
				if (_hoops_HSAIR->end_glyph.length != 0)
					glyph_count++;

				Line_Rendition alter & _hoops_ASGIP = nr.Modify()->_hoops_AHP.Modify();

				/* _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RPP _hoops_SR _hoops_HS _hoops_HHPA _hoops_HCR _hoops_RH _hoops_GPPC _hoops_ACGIP _hoops_GGR _hoops_RH _hoops_PGRIP */
				if (glyph_count > 0) {
					for (int i=0; i<nr->glyph_rendition->count; i++) {
						if (_hoops_HSAIR->start_glyph.length != 0 &&
							nr->glyph_rendition->glyphs[i]->key == _hoops_HSAIR->_hoops_GSCAP &&
							_hoops_RAHSR(_hoops_HSAIR->start_glyph, nr->glyph_rendition->glyphs[i]->name)) {
							_hoops_ASGIP->start_glyph = nr->glyph_rendition->glyphs[i];
							glyph_count--;
							_hoops_ASGIP->flags &= ~_hoops_HHISA;
						}
						if (_hoops_HSAIR->middle_glyph.length != 0 &&
							nr->glyph_rendition->glyphs[i]->key == _hoops_HSAIR->_hoops_RSCAP &&
							_hoops_RAHSR(_hoops_HSAIR->middle_glyph, nr->glyph_rendition->glyphs[i]->name)) {
							_hoops_ASGIP->middle_glyph = nr->glyph_rendition->glyphs[i];
							glyph_count--;
							_hoops_ASGIP->flags &= ~_hoops_HGRIP;
						}
						if (_hoops_HSAIR->end_glyph.length != 0 &&
							nr->glyph_rendition->glyphs[i]->key == _hoops_HSAIR->_hoops_ASCAP &&
							_hoops_RAHSR(_hoops_HSAIR->end_glyph, nr->glyph_rendition->glyphs[i]->name)) {
							_hoops_ASGIP->end_glyph = nr->glyph_rendition->glyphs[i];
							if (BIT(_hoops_HSAIR->mask, _hoops_PCCAP))
								_hoops_ASGIP->flags |= _hoops_RGRIP;
							else
								_hoops_ASGIP->flags &= ~_hoops_RGRIP;
							glyph_count--;
							_hoops_ASGIP->flags &= ~_hoops_PHISA;
						}

						if (glyph_count == 0)
							break;
					}

					if (glyph_count > 0) {
						/* _hoops_AHGSR _hoops_IH _hoops_IGRIP _hoops_RPHH _hoops_PAIGR */
						if (_hoops_HSAIR->start_glyph.length != 0 && !_hoops_ASGIP->start_glyph) {
							HE_WARNING (HEC_MARKER, HES_NOT_AVAILABLE,
								Sprintf_N (null, "Requested glyph '%n' not found", &_hoops_HSAIR->start_glyph));
						}
						if (_hoops_HSAIR->middle_glyph.length != 0 && !_hoops_ASGIP->middle_glyph) {
							HE_WARNING (HEC_MARKER, HES_NOT_AVAILABLE,
								Sprintf_N (null, "Requested glyph '%n' not found", &_hoops_HSAIR->middle_glyph));
						}
						if (_hoops_HSAIR->end_glyph.length != 0 && !_hoops_ASGIP->end_glyph) {
							HE_WARNING (HEC_MARKER, HES_NOT_AVAILABLE,
								Sprintf_N (null, "Requested glyph '%n' not found", &_hoops_HSAIR->end_glyph));
						}
					}
				}

				if (BIT(_hoops_HSAIR->mask, _hoops_SICAP) &&
					_hoops_HSAIR->start_glyph.length == 0) {
					_hoops_ASGIP->start_glyph = null;
					_hoops_ASGIP->flags |= _hoops_HHISA;
				}
				if (BIT(_hoops_HSAIR->mask, _hoops_RCCAP) &&
					_hoops_HSAIR->middle_glyph.length == 0) {
					_hoops_ASGIP->middle_glyph = null;
					_hoops_ASGIP->flags |= _hoops_HGRIP;
				}
				if (BIT(_hoops_HSAIR->mask, _hoops_GCCAP) &&
					_hoops_HSAIR->end_glyph.length == 0) {
					_hoops_ASGIP->end_glyph = null;
					_hoops_ASGIP->flags &= ~_hoops_RGRIP;
					_hoops_ASGIP->flags |= _hoops_PHISA;
				}

				if (_hoops_ASGIP->start_glyph || _hoops_ASGIP->middle_glyph || _hoops_ASGIP->end_glyph)
					_hoops_ASGIP->flags |= _hoops_SRPI;
				else
					_hoops_ASGIP->flags &= ~_hoops_SRPI;

				if (BIT(_hoops_HSAIR->mask, _hoops_PICAP)) {
					_hoops_ASGIP->style &= ~LCAP_START_MASK;
					_hoops_ASGIP->style |= _hoops_HSAIR->value & LCAP_START_MASK;
				}
				if (BIT(_hoops_HSAIR->mask, _hoops_HICAP)) {
					_hoops_ASGIP->style &= ~LCAP_END_MASK;
					_hoops_ASGIP->style |= _hoops_HSAIR->value & LCAP_END_MASK;
				}
				if (BIT(_hoops_HSAIR->mask, _hoops_CICAP)) {
					_hoops_ASGIP->style &= ~LJOIN_MASK;
					_hoops_ASGIP->style |= _hoops_HSAIR->value & LJOIN_MASK;
				}
				if (BIT(_hoops_HSAIR->mask, _hoops_IICAP)) {
					_hoops_ASGIP->style &= ~LPAT_MASK;
					_hoops_ASGIP->style |= _hoops_HSAIR->value & LPAT_MASK;
				}

				if (BIT(_hoops_HSAIR->mask, _hoops_AICAP) && line_style)
					_hoops_ASGIP->line_style = line_style;
			}
		}	break;

		case HK_LINE_WEIGHT:	if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_LINE_WEIGHT))) {
			_hoops_GHCAP const *		_hoops_CGRIP = (_hoops_GHCAP const *)_hoops_HPPGR;

			if (nr->_hoops_AHP->_hoops_PHP != _hoops_CGRIP->data.value ||
				nr->_hoops_AHP->_hoops_HHP != _hoops_CGRIP->data._hoops_HHP) {
				Line_Rendition alter &	_hoops_ASGIP = nr.Modify()->_hoops_AHP.Modify();

				_hoops_ASGIP->_hoops_PHP = _hoops_CGRIP->data.value;
				_hoops_ASGIP->_hoops_HHP = _hoops_CGRIP->data._hoops_HHP;

				if (_hoops_ASGIP->_hoops_HHP == _hoops_SHGRP)
					_hoops_ASGIP->weight = (int)(_hoops_ASGIP->_hoops_PHP *
										dc->_hoops_PGCC._hoops_IHHSR);
				else if (_hoops_ASGIP->_hoops_HHP == GSU_PIXELS)
					_hoops_ASGIP->weight = (int)(_hoops_ASGIP->_hoops_PHP + 0.5f);
				else
					_hoops_ASGIP->weight = -1;

				if (_hoops_ASGIP->weight != -1 && 
					(_hoops_ASGIP->weight < 0 || _hoops_ASGIP->weight > _hoops_CSGIP)) {
					_hoops_ASGIP->weight = (float)_hoops_CSGIP;
				}
			}
		}	break;

		case HK_MARKER_SYMBOL:	if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_MARKER_SYMBOL))) {
			_hoops_GICAP const *		_hoops_IRPP = (_hoops_GICAP const *)_hoops_HPPGR;
			_hoops_GASC						glyph;

			for (int i=0; i<nr->glyph_rendition->count; i++) {
				if (nr->glyph_rendition->keys[i] == _hoops_IRPP->key &&
					_hoops_RAHSR(_hoops_IRPP->name, nr->glyph_rendition->glyphs[i]->name)) {
					glyph = nr->glyph_rendition->glyphs[i];
					break;
				}
			}

			if (!glyph) {
				HE_WARNING (HEC_MARKER, HES_NOT_AVAILABLE,
					Sprintf_N (null, "Requested marker '%n' not found", &_hoops_IRPP->name));
			}
			else if (nr->_hoops_GSP->glyph != glyph) {
				bool						shared = (nr->_hoops_GSP == nr->_hoops_SCP);
				_hoops_ICP alter &	_hoops_HCSHP = nr.Modify()->_hoops_GSP.Modify();

				_hoops_HCSHP->glyph = glyph;

				if (shared)
					nr->_hoops_SCP = _hoops_HCSHP;
				else {
					_hoops_ICP alter &	_hoops_SCPHP = nr->_hoops_SCP.Modify();

					_hoops_SCPHP->glyph = glyph;
				}
			}
		}	break;

		case HK_MARKER_SIZE:	if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_MARKER_SIZE))) {
			/* _hoops_HAIC'_hoops_RA _hoops_RRSS _hoops_GPIA _hoops_IGIR _hoops_CCGR _hoops_RGGIH _hoops_SSCP
			 * _hoops_ARAS _hoops_RGCI _hoops_IPGAA, _hoops_PGGA _hoops_SCH _hoops_RAIA _hoops_SCGR._hoops_PCRPS -
			 * _hoops_IIS _hoops_PIIHP _hoops_CCIH _hoops_SCH _hoops_GH.
			 */
			if (!BIT(dc->flags, _hoops_CPPHP)) {
				_hoops_AHCAP const *		_hoops_IRPP = (_hoops_AHCAP const *)_hoops_HPPGR;

				if (nr->_hoops_GSP->_hoops_PHP != _hoops_IRPP->data.value ||
					nr->_hoops_GSP->_hoops_HHP != _hoops_IRPP->data._hoops_HHP) {
					bool						shared = (nr->_hoops_GSP == nr->_hoops_SCP);
					_hoops_ICP alter &	_hoops_HCSHP = nr.Modify()->_hoops_GSP.Modify();

					_hoops_HCSHP->_hoops_PHP = _hoops_IRPP->data.value;
					_hoops_HCSHP->_hoops_HHP = _hoops_IRPP->data._hoops_HHP;

					if (_hoops_HCSHP->_hoops_HHP == _hoops_SHGRP) {
						float					size;

						size = _hoops_HCSHP->_hoops_PHP * _hoops_RRRIP * dc->current._hoops_PRPSR.y;
						_hoops_HCSHP->ysize = size;
						_hoops_HCSHP->_hoops_RGRS = size*dc->current._hoops_AGRS;
					}
					else if (_hoops_HCSHP->_hoops_HHP == GSU_PIXELS) {
						_hoops_HCSHP->ysize = _hoops_HCSHP->_hoops_PHP*0.5f;
						_hoops_HCSHP->_hoops_RGRS = _hoops_HCSHP->_hoops_PHP*0.5f*dc->current._hoops_AGRS;
					}
					else
						_hoops_HCSHP->ysize = _hoops_HCSHP->_hoops_RGRS = -1.0f;

					if (shared)
						nr->_hoops_SCP = _hoops_HCSHP;
					else {
						_hoops_ICP alter &	_hoops_SCPHP = nr->_hoops_SCP.Modify();

						_hoops_SCPHP->_hoops_RGRS = nr->_hoops_GSP->_hoops_RGRS;
						_hoops_SCPHP->ysize = nr->_hoops_GSP->ysize;
						_hoops_SCPHP->_hoops_PHP = _hoops_IRPP->data.value;
						_hoops_SCPHP->_hoops_HHP = _hoops_IRPP->data._hoops_HHP;
					}
				}
			}
		}	break;

		case HK_STYLE:	if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_STYLE))) {
#ifndef DISABLE_STYLE_SEGMENT
			Style *				style = (Style *)_hoops_HPPGR;
			_hoops_CRCP const *		_hoops_ACSR = style->_hoops_IGRPR;

			if (_hoops_ACSR == null) {
				// _hoops_ACGIP _hoops_IAHA
				_hoops_GPAIR _hoops_PCGIP;

				for (int i=0; i<nr->_hoops_PIGIP->count; i++) {
					if (nr->_hoops_PIGIP->keys[i] == style->_hoops_PCSCA) {
						if (!_hoops_RAHSR(style->_hoops_SGAIR,  nr->_hoops_PIGIP->_hoops_SAAIR[i]->name))
							continue;
						_hoops_PCGIP = nr->_hoops_PIGIP->_hoops_SAAIR[i];
						break;
					}
				}
				if (!_hoops_PCGIP) {
					HE_WARNING (HEC_STYLE, HES_NOT_AVAILABLE,
						Sprintf_N (null, "Requested named style '%n' not found", &style->_hoops_SGAIR));
				}
				else 
					_hoops_ACSR = _hoops_PCGIP->segment;
			}

			if (_hoops_ACSR && _hoops_ACSR->_hoops_IPPGR  &&
				(style->condition.count == 0 || 
					HI_Condition_Passed (nr->_hoops_ASIR->conditions.count,
										 nr->_hoops_ASIR->conditions._hoops_RCHA,
										&style->condition))) {

				_hoops_GRGH			_hoops_RRGH = nr->_hoops_IRR;
				_hoops_PIGRA			_hoops_RGCAA;

				_hoops_RSAI (&_hoops_RRGH->locks, _hoops_PIGRA, &_hoops_RGCAA);

				HD_Selection_Downwind (nr, _hoops_ACSR->_hoops_IPPGR);

				/* _hoops_IRHH _hoops_RCRR _hoops_SGHS _hoops_CHR _hoops_GH-_hoops_IS-_hoops_ICGIP*/

				if (BIT (_hoops_ACSR->_hoops_RCGC, _hoops_RHHGP))
					_hoops_RSAI (&_hoops_RRGH->locks, _hoops_PIGRA, &_hoops_PCGS);

				if (1 /* _hoops_RPSI _hoops_PSIAA _hoops_PCIRA */) {
					if (BIT (_hoops_ACSR->_hoops_RCGC, _hoops_RHHGP)) {
						/* _hoops_SRS, _hoops_PA _hoops_HCIAA _hoops_ASIAA _hoops_IGICR _hoops_ASIAA */
						_hoops_HSIAA (&_hoops_PCGS, &_hoops_CIIAA, sizeof (_hoops_PIGRA));

						/* _hoops_HGCAA _hoops_PA _hoops_SR _hoops_PCPAR _hoops_SGS _hoops_RH _hoops_IAHA _hoops_GHCA _hoops_HS _hoops_ASIAA */
						_hoops_IGCAA (&_hoops_RGCAA, &_hoops_CIIAA, sizeof (_hoops_PIGRA));
						_hoops_ISIAA (&_hoops_RGCAA, &_hoops_PCGS, sizeof (_hoops_PIGRA));
					}

					if (!EQUAL_MEMORY (&_hoops_RGCAA, sizeof (_hoops_PIGRA), &_hoops_RRGH->locks)) {
						_hoops_GRGH alter &	_hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();

						_hoops_RSAI (&_hoops_RGCAA, _hoops_PIGRA, &_hoops_APIHP->locks);
					}
				}
			}
#endif
		}	break;

		case _hoops_CPPIR: {
			// _hoops_GIR _hoops_RSIH
		}	break;

		case HK_RENDERING_OPTIONS: if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_RENDERING_OPTIONS))) {
			_hoops_RHAIR const	*	_hoops_AHAIR = (_hoops_RHAIR const *) _hoops_HPPGR;
			_hoops_GHGI					_hoops_CCCIR;

			if ((_hoops_CCCIR = _hoops_AHAIR->_hoops_PSHCA &
						   (nr->_hoops_IRR->_hoops_PPH ^ _hoops_AHAIR->_hoops_RRRAP)) != 0)
				nr.Modify()->_hoops_IRR.Modify()->_hoops_PPH ^= _hoops_CCCIR;

			if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_HRRAP) &&
				(_hoops_AHAIR->_hoops_HHAAP[0] != nr->transform_rendition->_hoops_GSCH[0] ||
				 _hoops_AHAIR->_hoops_HHAAP[1] != nr->transform_rendition->_hoops_GSCH[1])) {
				_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();
				_hoops_HRPA						_hoops_RHSPR;

				HD_Undo_Screen (nr, &_hoops_RHSPR);
				_hoops_GGCC->_hoops_GSCH[0] = _hoops_AHAIR->_hoops_HHAAP[0];
				_hoops_GGCC->_hoops_GSCH[1] = _hoops_AHAIR->_hoops_HHAAP[1];
				if (_hoops_GGCC->_hoops_GSCH[0] == _hoops_GGCC->_hoops_GSCH[1]) {
					if (_hoops_GGCC->_hoops_GSCH[1] == 1.0f)
						_hoops_GGCC->_hoops_GSCH[0] -= 0.0001f;
					else
						_hoops_GGCC->_hoops_GSCH[1] += 0.0001f;
				}
				HD_Redo_Screen (nr, &_hoops_RHSPR);

				if (BIT (_hoops_GGCC->flags, _hoops_HHGGA))
					HD_Set_DC_Cutting_Planes (nr);
			}
			if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_APRAP) &&
				(_hoops_AHAIR->_hoops_HCIH.left != nr->transform_rendition->_hoops_HCIH.left ||
				 _hoops_AHAIR->_hoops_HCIH.right != nr->transform_rendition->_hoops_HCIH.right ||
				 _hoops_AHAIR->_hoops_HCIH.bottom != nr->transform_rendition->_hoops_HCIH.bottom ||
				 _hoops_AHAIR->_hoops_HCIH.top != nr->transform_rendition->_hoops_HCIH.top)) {
				_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
				_hoops_HRPA					_hoops_RHSPR;
				Int_Rectangle				_hoops_GPHH;
				float						_hoops_RISHP, _hoops_AISHP,
											_hoops_PISHP, _hoops_HISHP;

				_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

				HD_Undo_Screen (nr, &_hoops_RHSPR);
				_hoops_GGCC->_hoops_HCIH = _hoops_AHAIR->_hoops_HCIH;
				HD_Redo_Screen (nr, &_hoops_RHSPR);

				// _hoops_PASC
				_hoops_PISHP = (_hoops_SGRA->_hoops_CIIH.right - _hoops_SGRA->_hoops_CIIH.left) * 0.5f;
				_hoops_HISHP = (_hoops_SGRA->_hoops_CIIH.top - _hoops_SGRA->_hoops_CIIH.bottom) * 0.5f;
				_hoops_RISHP = (_hoops_SGRA->_hoops_CIIH.left +	_hoops_SGRA->_hoops_CIIH.right) * 0.5f;
				_hoops_AISHP = (_hoops_SGRA->_hoops_CIIH.top + _hoops_SGRA->_hoops_CIIH.bottom) * 0.5f;

				_hoops_GPHH.left   = int (_hoops_RISHP + _hoops_AHAIR->_hoops_HCIH.left   * _hoops_PISHP);
				_hoops_GPHH.right  = int (_hoops_RISHP + _hoops_AHAIR->_hoops_HCIH.right  * _hoops_PISHP);
				_hoops_GPHH.bottom = int (_hoops_AISHP + _hoops_AHAIR->_hoops_HCIH.bottom * _hoops_HISHP);
				_hoops_GPHH.top    = int (_hoops_AISHP + _hoops_AHAIR->_hoops_HCIH.top    * _hoops_HISHP);

				_hoops_GGCC->_hoops_AGAA._hoops_PGPGP(_hoops_GPHH);
			}
			if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_CRRAP) &&
				_hoops_AHAIR->_hoops_CHIH != nr->transform_rendition->_hoops_CHIH) {
				_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

				_hoops_GGCC->_hoops_CHIH = (float)_hoops_AHAIR->_hoops_CHIH;
				if (!BIT(dc->flags, _hoops_AASHP))
					_hoops_GGCC->_hoops_CHIH *= dc->_hoops_PGCC._hoops_PASHP /
										(float)(1L << dc->_hoops_PGCC._hoops_HASHP);
			}
			if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_IPRAP) &&
				_hoops_AHAIR->_hoops_IGAAP != nr->transform_rendition->_hoops_IGAAP) {
				_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

				_hoops_GGCC->_hoops_IGAAP = (float)_hoops_AHAIR->_hoops_IGAAP;
				if (!BIT(dc->flags, _hoops_AASHP))
					_hoops_GGCC->_hoops_IGAAP *= dc->_hoops_PGCC._hoops_PASHP /
										(float)(1L << dc->_hoops_PGCC._hoops_HASHP);
			}
			if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_SARAP) &&
				_hoops_AHAIR->_hoops_SHIH != nr->transform_rendition->_hoops_SHIH) {
				_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

				_hoops_GGCC->_hoops_SHIH = (float)_hoops_AHAIR->_hoops_SHIH;
				if (!BIT(dc->flags, _hoops_AASHP))
					_hoops_GGCC->_hoops_SHIH *= dc->_hoops_PGCC._hoops_PASHP /
					(float)(1L << dc->_hoops_PGCC._hoops_HASHP);
			}
			if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_GPRAP)) {
				if (_hoops_AHAIR->_hoops_GSAAP != nr->_hoops_AHP->_hoops_HCAA)
					nr.Modify()->_hoops_AHP.Modify()->_hoops_HCAA = (float)_hoops_AHAIR->_hoops_GSAAP;
				if (_hoops_AHAIR->_hoops_RSAAP != nr->_hoops_RHP->_hoops_HCAA)
					nr.Modify()->_hoops_AHP.Modify()->_hoops_HCAA = (float)_hoops_AHAIR->_hoops_RSAAP;
			}

#ifndef _hoops_CCPIR
			if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_IRICA)) {
				_hoops_GRA alter &		_hoops_GCIHP = nr.Modify()->_hoops_ARA.Modify();

				if (BIT (_hoops_AHAIR->geometry->_hoops_APPI.mask, _hoops_HHGAP))
					_hoops_GCIHP->_hoops_APPI._hoops_SAR =
						BIT (_hoops_AHAIR->geometry->_hoops_APPI.value, _hoops_HHGAP);
				if (BIT (_hoops_AHAIR->geometry->_hoops_APPI.mask, _hoops_CHGAP))
					_hoops_GCIHP->_hoops_APPI._hoops_PPPI = _hoops_AHAIR->geometry->_hoops_APPI._hoops_PPPI;
				if (BIT (_hoops_AHAIR->geometry->_hoops_APPI.mask, _hoops_SHGAP))
					_hoops_GCIHP->_hoops_APPI._hoops_HPPI = _hoops_AHAIR->geometry->_hoops_APPI._hoops_HPPI;
				if (BIT (_hoops_AHAIR->geometry->_hoops_APPI.mask, _hoops_GIGAP))
					_hoops_GCIHP->_hoops_APPI._hoops_IPPI = _hoops_AHAIR->geometry->_hoops_APPI._hoops_IPPI;
				if (BIT (_hoops_AHAIR->geometry->_hoops_APPI.mask, _hoops_RIGAP))
					_hoops_GCIHP->_hoops_APPI._hoops_CPPI = _hoops_AHAIR->geometry->_hoops_APPI._hoops_CPPI;
				if (BIT (_hoops_AHAIR->geometry->_hoops_APPI.mask, _hoops_AIGAP))
					_hoops_GCIHP->_hoops_APPI._hoops_SPPI = _hoops_AHAIR->geometry->_hoops_APPI._hoops_SPPI;
			}
#endif

			if (ANYBIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_AGRAP | _hoops_PRICA)) {
				_hoops_GRA alter &		_hoops_GCIHP = nr.Modify()->_hoops_ARA.Modify();

				if (ANYBIT (_hoops_AHAIR->_hoops_IIAIR->value, _hoops_RICRP|_hoops_HICRP)) {
					_hoops_GCIHP->_hoops_CICP._hoops_RGP &= ~_hoops_AHAIR->_hoops_IIAIR->_hoops_RGP.mask;
					_hoops_GCIHP->_hoops_CICP._hoops_RGP |= _hoops_AHAIR->_hoops_IIAIR->_hoops_RGP.value;
				}

				if (BIT (_hoops_AHAIR->_hoops_IIAIR->mask, _hoops_AICRP)) {
					if (BIT (_hoops_AHAIR->_hoops_IIAIR->value, _hoops_AICRP)) {
						_hoops_GCIHP->_hoops_CICP._hoops_CCCRP = _hoops_AHAIR->_hoops_IIAIR->_hoops_CCCRP;

						if (_hoops_GCIHP->_hoops_CICP._hoops_CCCRP == _hoops_HCCRP) {
							_hoops_CAHHP const &		_hoops_SAHHP = nr->_hoops_ASIR->_hoops_PSIR;

							if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_HIRC)) {
								_hoops_GCIHP->_hoops_CICP.scale = _hoops_SAHHP->_hoops_CSIR->length - 1;
								_hoops_GCIHP->_hoops_CICP.translate = 0.0f;
							}
							else {
								_hoops_GCIHP->_hoops_CICP.scale = _hoops_SAHHP->_hoops_CSIR->length;
								_hoops_GCIHP->_hoops_CICP.translate = -0.5f;
							}
						}
						else {
							_hoops_GCIHP->_hoops_CICP.scale = _hoops_AHAIR->_hoops_IIAIR->scale;
							_hoops_GCIHP->_hoops_CICP.translate = _hoops_AHAIR->_hoops_IIAIR->translate;
						}
					}
					else {
						_hoops_GCIHP->_hoops_CICP._hoops_CCCRP = _hoops_PCCRP;
						_hoops_GCIHP->_hoops_CICP.scale = 1.0f;
						_hoops_GCIHP->_hoops_CICP.translate = 0.0f;
					}
				}

				if (BIT (_hoops_AHAIR->_hoops_IIAIR->mask, _hoops_IICRP)) {
					if (_hoops_GCIHP->_hoops_ACP._hoops_CIAIR != 0)
						FREE_ARRAY (_hoops_GCIHP->_hoops_ACP._hoops_SIAIR, _hoops_GCIHP->_hoops_ACP._hoops_CIAIR, float);
					_hoops_GCIHP->_hoops_ACP._hoops_SIAIR = null;

					_hoops_GCIHP->_hoops_ACP._hoops_RSCRP = _hoops_AHAIR->_hoops_IIAIR->_hoops_RSCRP;
					if ((_hoops_GCIHP->_hoops_ACP._hoops_CIAIR = _hoops_AHAIR->_hoops_IIAIR->_hoops_CIAIR) != 0) {
						POOL_ALLOC_ARRAY (_hoops_GCIHP->_hoops_ACP._hoops_SIAIR, _hoops_GCIHP->_hoops_ACP._hoops_CIAIR, float, dc->memory_pool);
						_hoops_AIGA (_hoops_AHAIR->_hoops_IIAIR->_hoops_SIAIR, _hoops_GCIHP->_hoops_ACP._hoops_CIAIR, float, _hoops_GCIHP->_hoops_ACP._hoops_SIAIR);
					}
				}
				if (BIT (_hoops_AHAIR->_hoops_IIAIR->mask, _hoops_SICRP)) {
					if (_hoops_GCIHP->_hoops_ACP._hoops_RCAIR != 0) {
						for (int i=0; i<_hoops_GCIHP->_hoops_ACP._hoops_RCAIR; i++)
							_hoops_RGAIR (_hoops_GCIHP->_hoops_ACP._hoops_ACAIR[i]);
						FREE_ARRAY (_hoops_GCIHP->_hoops_ACP._hoops_ACAIR, _hoops_GCIHP->_hoops_ACP._hoops_RCAIR, _hoops_HCRPR);

						FREE_ARRAY (_hoops_GCIHP->_hoops_ACP._hoops_PCAIR, _hoops_GCIHP->_hoops_ACP._hoops_RCAIR, Integer32);
					}
					_hoops_GCIHP->_hoops_ACP._hoops_ACAIR = null;
					_hoops_GCIHP->_hoops_ACP._hoops_PCAIR = null;

					if ((_hoops_GCIHP->_hoops_ACP._hoops_RCAIR = _hoops_AHAIR->_hoops_IIAIR->_hoops_RCAIR) != 0) {
						POOL_ALLOC_ARRAY (_hoops_GCIHP->_hoops_ACP._hoops_ACAIR, _hoops_GCIHP->_hoops_ACP._hoops_RCAIR, _hoops_HCRPR, dc->memory_pool);
						for (int i=0; i<_hoops_GCIHP->_hoops_ACP._hoops_RCAIR; i++)
							HI_Copy_Name (&_hoops_AHAIR->_hoops_IIAIR->_hoops_ACAIR[i], &_hoops_GCIHP->_hoops_ACP._hoops_ACAIR[i]);
						POOL_ALLOC_ARRAY (_hoops_GCIHP->_hoops_ACP._hoops_PCAIR, _hoops_GCIHP->_hoops_ACP._hoops_RCAIR, Integer32, dc->memory_pool);
						_hoops_AIGA (_hoops_AHAIR->_hoops_IIAIR->_hoops_PCAIR, _hoops_GCIHP->_hoops_ACP._hoops_RCAIR, Integer32, _hoops_GCIHP->_hoops_ACP._hoops_PCAIR);
					}
				}
				if (BIT (_hoops_AHAIR->_hoops_IIAIR->mask, _hoops_GCCRP)) {
					if (_hoops_GCIHP->_hoops_ACP.weight_count != 0)
						FREE_ARRAY (_hoops_GCIHP->_hoops_ACP.weights, _hoops_GCIHP->_hoops_ACP.weight_count, _hoops_HCAIR);
					_hoops_GCIHP->_hoops_ACP.weights = null;

					if ((_hoops_GCIHP->_hoops_ACP.weight_count = _hoops_AHAIR->_hoops_IIAIR->weight_count) != 0) {
						POOL_ALLOC_ARRAY (_hoops_GCIHP->_hoops_ACP.weights, _hoops_GCIHP->_hoops_ACP.weight_count, _hoops_HCAIR, dc->memory_pool);
						_hoops_AIGA (_hoops_AHAIR->_hoops_IIAIR->weights, _hoops_GCIHP->_hoops_ACP.weight_count, _hoops_HCAIR, _hoops_GCIHP->_hoops_ACP.weights);
					}
				}
			}

			if (BIT (_hoops_AHAIR->_hoops_ISHCA, _hoops_HIRC) &&
				nr->_hoops_ARA->_hoops_CICP._hoops_CCCRP == _hoops_HCCRP) {
				_hoops_CAHHP const &		_hoops_SAHHP = nr->_hoops_ASIR->_hoops_PSIR;
				_hoops_GRA alter &		_hoops_GCIHP = nr.Modify()->_hoops_ARA.Modify();

				if (BIT (_hoops_AHAIR->_hoops_GHRAP, _hoops_HIRC)) {
					_hoops_GCIHP->_hoops_CICP.scale = _hoops_SAHHP->_hoops_CSIR->length - 1;
					_hoops_GCIHP->_hoops_CICP.translate = 0.0f;
				}
				else {
					_hoops_GCIHP->_hoops_CICP.scale = _hoops_SAHHP->_hoops_CSIR->length;
					_hoops_GCIHP->_hoops_CICP.translate = -0.5f;
				}
			}
		}	break;

		// _hoops_RRP _hoops_HAIR _hoops_ARCR _hoops_RGAR _hoops_IH _hoops_SSRR _hoops_CPRC _hoops_CIAAI
		case HK_COLOR_MAP: {
			_hoops_RHAH const *			_hoops_SPRAR = (_hoops_RHAH const *)_hoops_HPPGR;

			nr.Modify()->_hoops_ASIR.Modify()->_hoops_PSIR.Modify()->_hoops_CSIR = _hoops_SPRAR;

			if (nr->_hoops_ARA->_hoops_CICP._hoops_CCCRP == _hoops_HCCRP) {
				_hoops_GRA alter &		_hoops_GCIHP = nr->_hoops_ARA.Modify();

				if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_HIRC)) {
					_hoops_GCIHP->_hoops_CICP.scale = _hoops_SPRAR->length - 1;
					_hoops_GCIHP->_hoops_CICP.translate = 0.0f;
				}
				else {
					_hoops_GCIHP->_hoops_CICP.scale = _hoops_SPRAR->length;
					_hoops_GCIHP->_hoops_CICP.translate = -0.5f;
				}
			}
		}	break;

		case HK_CAMERA: if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_CAMERA))) {
			if (BIT (sc->options, _hoops_IICAH)) {
				if (BIT (sc->options, _hoops_IRPAS)) {
					HE_WARNING (HEC_CAMERA, HES_CAMERA_IGNORED,
							Sprintf_P (null,
						"Camera ignored in '%p' during world-space Select",
						_hoops_HPPGR->owner));
				}
			}
			else
				HD_Downwind_Camera (nr, _hoops_HPPGR);
		}	break;

		case HK_CLIP_REGION:	if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_CLIP_REGION))) {
			_hoops_IRAIR const *			_hoops_CRAIR = (_hoops_IRAIR const *)_hoops_HPPGR;
			_hoops_HHCR alter &	_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

			if (_hoops_CRAIR->count > 0) {
				DC_Point				buffer[32];
				DC_Point				*points = buffer;
				int						count = _hoops_CRAIR->count;
				float const				*mat;
				float					_hoops_IHPIA[4][4];
				_hoops_ASHH alter *_hoops_PPGGA;

				if (count > _hoops_GGAPR(buffer))
					POOL_ALLOC_ARRAY_CACHED (points, count, DC_Point, dc->memory_pool);

				if (BIT (_hoops_CRAIR->flags, _hoops_SPAGA)) {
					if (!BIT (_hoops_GGCC->flags, _hoops_IGCC))
						HD_Validate_World_To_Screen (nr);
					mat = &_hoops_GGCC->_hoops_CGCC->data.elements[0][0];
				}
				else {
					_hoops_CGRA const &		_hoops_SGRA = nr->_hoops_SAIR;

					HI_Compute_Identity_Matrix (&_hoops_IHPIA[0][0]);

					_hoops_IHPIA[0][0] = 0.5f * (_hoops_SGRA->_hoops_PHRA.right - _hoops_SGRA->_hoops_PHRA.left);
					_hoops_IHPIA[1][1] = 0.5f * (_hoops_SGRA->_hoops_PHRA.top  - _hoops_SGRA->_hoops_PHRA.bottom);
					_hoops_IHPIA[3][0] = 0.5f * (_hoops_SGRA->_hoops_PHRA.left + _hoops_SGRA->_hoops_PHRA.right);
					_hoops_IHPIA[3][1] = 0.5f * (_hoops_SGRA->_hoops_PHRA.bottom + _hoops_SGRA->_hoops_PHRA.top);
					mat = &_hoops_IHPIA[0][0];
				}

				HI_Compute_Transformed_Points (count, _hoops_CRAIR->points,
												mat, (Point *)points);

				_hoops_PPGGA = HD_New_Convex_Clip_Region (nr, count, points);
				_hoops_PPGGA->flags = _hoops_CRAIR->flags;


				if (_hoops_GGCC->_hoops_HCHH != null)
					_hoops_GGCC->_hoops_HCHH.Modify();
				else
					_hoops_GGCC->_hoops_HCHH = _hoops_HSRGA::Create (dc);

				_hoops_ASHH **	_hoops_ASRGR = (_hoops_ASHH **)&_hoops_GGCC->_hoops_HCHH->_hoops_PSHH;

				if (BIT (_hoops_PPGGA->flags, _hoops_RHIH)) {
					_hoops_GGCC->_hoops_HCHH->_hoops_ISRGA = true;

					while (*_hoops_ASRGR && !BIT ((*_hoops_ASRGR)->flags, _hoops_RHIH))
						_hoops_ASRGR = &(*_hoops_ASRGR)->next;
				}

				_hoops_PPGGA->next = *_hoops_ASRGR;
				*_hoops_ASRGR = _hoops_PPGGA;

				if (count > _hoops_GGAPR(buffer))
					FREE_ARRAY (points, count, DC_Point);
			}
		}	break;

		case HK_TEXT_SPACING:	if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_TEXT_SPACING))) {
			_hoops_PHCAP const *		ts = (_hoops_PHCAP const *)_hoops_HPPGR;

			if (nr->_hoops_SISI->spacing != ts->data.value)
				nr.Modify()->_hoops_SISI.Modify()->spacing = ts->data.value;
		}	break;

		case HK_TEXT_ALIGNMENT: if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_TEXT_ALIGNMENT))) {
			_hoops_SHCAP const *		_hoops_ARRIP = (_hoops_SHCAP const *)_hoops_HPPGR;

			if (nr->_hoops_SISI->_hoops_PRRIP != _hoops_ARRIP->value ||
				nr->_hoops_SISI->_hoops_HRRIP != _hoops_ARRIP->_hoops_HHCAP) {
				_hoops_IGCSR alter &		_hoops_IRRIP = nr.Modify()->_hoops_SISI.Modify();

				_hoops_IRRIP->_hoops_PRRIP = _hoops_ARRIP->value;
				_hoops_IRRIP->_hoops_HRRIP = _hoops_ARRIP->_hoops_HHCAP;
			}
		}	break;

		case HK_TEXT_FONT:		if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_TEXT_FONT))) {
			HD_Downwind_Text_Font (nr, (_hoops_AGPIR alter *)_hoops_HPPGR);
		}	break;

		case HK_TEXT_PATH:		if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_TEXT_PATH))) {
			_hoops_RGPIR const *			_hoops_HAPAR = (_hoops_RGPIR const *)_hoops_HPPGR;
			_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;

			if (_hoops_HAPAR->value.x == _hoops_HRCIR->path.x &&
				_hoops_HAPAR->value.y == _hoops_HRCIR->path.y &&
				_hoops_HAPAR->value.z == _hoops_HRCIR->path.z) break;

			_hoops_IGCSR alter &		_hoops_IRRIP = nr.Modify()->_hoops_SISI.Modify();

			_hoops_IRRIP->path.x = _hoops_HAPAR->value.x;
			_hoops_IRRIP->path.y = _hoops_HAPAR->value.y;
			_hoops_IRRIP->path.z = _hoops_HAPAR->value.z;
			if (_hoops_IRRIP->_hoops_CRRIP) {
				if (_hoops_IRRIP->path.x != 0.0f || _hoops_IRRIP->path.y != 0.0f)
					_hoops_IRRIP->rotation = _hoops_AGGGA (_hoops_IRRIP->path.y, _hoops_IRRIP->path.x);
			}
		}	break;

		case HK_VISIBILITY:		/* _hoops_IGGA _hoops_SGHS */ {
			_hoops_RSAIR const *		vis = (_hoops_RSAIR const *)_hoops_HPPGR;
			_hoops_ACHR				_hoops_CCCIR;

			if ((_hoops_CCCIR = vis->mask & ~_hoops_PCGS._hoops_RGP & (nr->_hoops_RGP ^ vis->value)) != 0) {
				nr.Modify()->_hoops_IRR.Modify();

				nr->_hoops_IRR->_hoops_AARIP ^= _hoops_CCCIR;
				nr->_hoops_RGP ^= _hoops_CCCIR;

				if (BIT (_hoops_CCCIR, T_CUTTING_PLANES) &&
					nr->transform_rendition-> _hoops_RGH != null)
					nr.Modify()->transform_rendition.Modify()->flags ^= _hoops_CSP;
			}
		}	break;

		case HK_HEURISTICS:		if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_HEURISTICS))) {
			_hoops_GHAIR const *		_hoops_GIGC = (_hoops_GHAIR const *)_hoops_HPPGR;
			_hoops_CGSP		_hoops_CCCIR;
			short					_hoops_IGGIP;

			// _hoops_GRH _hoops_HCSP _hoops_SSPP _hoops_RHIR _hoops_HAIHR _hoops_AASA
			if (_hoops_GIGC->_hoops_SHSHA != -1.0f)
				dc->options._hoops_SHSHA = _hoops_GIGC->_hoops_SHSHA;

			if (BIT (_hoops_GIGC->mask, _hoops_SICIA)) {
				int			_hoops_HCRPS;

				if (BIT (_hoops_GIGC->value, _hoops_SICIA))
					_hoops_HCRPS = _hoops_GIGC->_hoops_GCCIA;
				else
					_hoops_HCRPS = _hoops_IICIA;

				if (nr->_hoops_IRR->_hoops_GCCIA != _hoops_HCRPS)
					nr.Modify()->_hoops_IRR.Modify()->_hoops_GCCIA = _hoops_HCRPS;
			}
			if (BIT (_hoops_GIGC->mask, _hoops_SRIRP)) {
				int			_hoops_HCRPS;

				if (BIT (_hoops_GIGC->_hoops_CCIRP.value, _hoops_HCIRP))
					_hoops_HCRPS = _hoops_GIGC->_hoops_CCIRP._hoops_SPHPR;
				else
					_hoops_HCRPS = _hoops_IICIA;

				if (nr->_hoops_IRR->_hoops_CCIRP._hoops_SPHPR != _hoops_HCRPS)
					nr.Modify()->_hoops_IRR.Modify()->_hoops_CCIRP._hoops_SPHPR = _hoops_HCRPS;

				if (BIT (_hoops_GIGC->_hoops_CCIRP.value, _hoops_ICIRP))
					_hoops_HCRPS = _hoops_GIGC->_hoops_CCIRP.polyline;
				else
					_hoops_HCRPS = _hoops_IICIA;

				if (nr->_hoops_IRR->_hoops_CCIRP.polyline != _hoops_HCRPS)
					nr.Modify()->_hoops_IRR.Modify()->_hoops_CCIRP.polyline = _hoops_HCRPS;
			}

			if (BIT (_hoops_GIGC->mask, _hoops_RPIRP))
				if (nr->_hoops_IRR->_hoops_GRCRP != _hoops_GIGC->_hoops_GRCRP)
					nr.Modify()->_hoops_IRR.Modify()->_hoops_GRCRP = _hoops_GIGC->_hoops_GRCRP;


			_hoops_CCCIR = (nr->transform_rendition->heuristics ^ _hoops_GIGC->value) &
					  _hoops_GIGC->mask;
			_hoops_IGGIP = (nr->transform_rendition->_hoops_APH ^ _hoops_GIGC->_hoops_APH.value) &
							  _hoops_GIGC->_hoops_APH.mask;

			if (_hoops_CCCIR == (_hoops_GHGI)0 && _hoops_IGGIP == 0)
				break;

			_hoops_HHCR alter &		_hoops_ICRPS = nr.Modify()->transform_rendition.Modify();
			_hoops_ICRPS->heuristics ^= _hoops_CCCIR;
			_hoops_ICRPS->_hoops_APH ^= _hoops_IGGIP;

			if (BIT (_hoops_ICRPS->heuristics, _hoops_SGIRP) &&
				ANYBIT (_hoops_ICRPS->heuristics, _hoops_GPSA|
										 _hoops_SASA))
				_hoops_ICRPS->flags |= _hoops_IGSP;
			else
				_hoops_ICRPS->flags &= ~_hoops_IGSP;

			/* _hoops_GA'_hoops_RA _hoops_SHAC _hoops_CCA _hoops_HRHAC _hoops_PAR _hoops_CCRPS */
		}	break;

		case HK_MODELLING_MATRIX:		if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_MODELLING_MATRIX))) {
			if (!BIT (sc->options, _hoops_HRPAS) &&
				ANYBIT (((_hoops_ISGI const *)_hoops_HPPGR)->matrix._hoops_RAGR,
						_hoops_CICH)) {
				HD_Downwind_Modelling_Matrix (nr, _hoops_HPPGR);

				if (nr->transform_rendition->_hoops_HGSC == _hoops_SIPHP)
					nr.Modify()->transform_rendition.Modify()->_hoops_HGSC = _hoops_ACPHP;
			}
		}	break;

		case HK_WINDOW: if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_WINDOW))) {
			if (!BIT (sc->options, _hoops_IICAH))
				HD_Downwind_Window (nr, _hoops_HPPGR);
		}	break;

		case HK_HANDEDNESS:		if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_HANDEDNESS))) {
			if (!BIT (sc->options, _hoops_IICAH))
				HD_Downwind_Handedness (nr, _hoops_HPPGR);
		}	break;

		case HK_SELECTABILITY:	if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_SELECTABILITY))) {
			_hoops_ASAIR const *		_hoops_RIRIP = (_hoops_ASAIR const *)_hoops_HPPGR;
			_hoops_GRGH				_hoops_RRGH = nr->_hoops_IRR;
			_hoops_ACHR					_hoops_CCCIR = 0;
			_hoops_ACHR					_hoops_AIRIP = 0;


			if (BIT(sc->event->_hoops_CHSHA, _hoops_HPSHA)) {
				_hoops_CCCIR |= ((_hoops_RIRIP->down | _hoops_RIRIP->_hoops_AHARP) ^ _hoops_RRGH->_hoops_AAICA) & _hoops_RIRIP->mask;
				_hoops_AIRIP |= (_hoops_RIRIP->down ^ _hoops_RRGH->_hoops_AAICA) & _hoops_RIRIP->mask;
			}
			else if (BIT(sc->event->_hoops_CHSHA, _hoops_IPSHA)) {
				_hoops_CCCIR |= (_hoops_RIRIP->_hoops_AHARP ^ _hoops_RRGH->_hoops_AAICA) & _hoops_RIRIP->mask;
				_hoops_AIRIP |= _hoops_CCCIR;
			}

			if (BIT(sc->event->_hoops_CHSHA, _hoops_CPSHA)) {
				_hoops_CCCIR |= ((_hoops_RIRIP->up | _hoops_RIRIP->_hoops_RHARP) ^ _hoops_RRGH->_hoops_AAICA) & _hoops_RIRIP->mask;
				_hoops_AIRIP |= (_hoops_RIRIP->up ^ _hoops_RRGH->_hoops_AAICA) & _hoops_RIRIP->mask;
			}
			else if (BIT(sc->event->_hoops_CHSHA, _hoops_SPSHA)) {
				_hoops_CCCIR |= (_hoops_RIRIP->_hoops_RHARP ^ _hoops_RRGH->_hoops_AAICA) & _hoops_RIRIP->mask;
				_hoops_AIRIP |= _hoops_CCCIR;
			}

			_hoops_ACHR	_hoops_PIRIP = (_hoops_RIRIP->_hoops_PHARP ^ _hoops_RRGH->_hoops_PHARP) & _hoops_RIRIP->mask;

			if (_hoops_CCCIR != 0 || _hoops_AIRIP != 0 || _hoops_PIRIP != 0) {
				_hoops_RRGH = nr.Modify()->_hoops_IRR.Modify();
				_hoops_RRGH->_hoops_AAICA ^= _hoops_CCCIR;
				_hoops_RRGH->restricted_selectability ^= _hoops_AIRIP;
				_hoops_RRGH->_hoops_PHARP ^= _hoops_PIRIP;
			}

		}	break;

		case HK_WINDOW_FRAME:	if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_WINDOW_FRAME))) {
			if (!BIT (sc->options, _hoops_IICAH))
				HD_Downwind_Window_Frame (nr, _hoops_HPPGR);
		}	break;

		case HK_CALLBACK:		if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_CALLBACK))) {
#ifndef DISABLE_CALLBACKS
			_hoops_GCHIR const *			_hoops_RCHIR = (_hoops_GCHIR const *)_hoops_HPPGR;
			_hoops_IHACR const			*_hoops_RCACR = _hoops_RCHIR->_hoops_ACHIR;
			_hoops_PSIHP			_hoops_HSIHP = nr->_hoops_RSGC;
			bool						_hoops_ISIHP = false;
			_hoops_CRCP const				*owner = _hoops_HPPGR->owner;

#			define		_hoops_CSIHP(index, _hoops_RCACR, element, type) do {	\
				if (_hoops_HSIHP->action.element != (type)_hoops_RCACR->name->address) {	\
					if (!_hoops_ISIHP) {								\
						_hoops_HSIHP = nr.Modify()->_hoops_RSGC.Modify();	\
						_hoops_ISIHP = true;							\
					}											\
					_hoops_HSIHP->action.element = (type)_hoops_RCACR->name->address;		\
					_hoops_HSIHP->_hoops_RGCHP[index] = owner;					\
					_hoops_HSIHP->_hoops_AIACR[index] = _hoops_RCACR->_hoops_AIACR;	\
				}												\
			} while (0)

			if (_hoops_RCACR != null) do switch (_hoops_RCACR->type) {
				case _hoops_SHRCR: {
					_hoops_CSIHP (_hoops_SHRCR, _hoops_RCACR,
								   draw_window_frame, _hoops_ICCHP);
				}	break;

				case _hoops_GGACR: {
					_hoops_CSIHP (_hoops_GGACR, _hoops_RCACR,
								   draw_3d_marker, _hoops_IHCHP);
				}	break;

				case _hoops_RGACR: {
					_hoops_CSIHP (_hoops_RGACR, _hoops_RCACR,
								   draw_3d_polyline, _hoops_CHCHP);
				}	break;

				case _hoops_AGACR: {
					_hoops_CSIHP (_hoops_AGACR, _hoops_RCACR,
								   draw_3d_polygon, _hoops_HCIGA);
				}	break;

				case _hoops_PGACR: {
					_hoops_CSIHP (_hoops_PGACR, _hoops_RCACR,
								   draw_3d_text, _hoops_HICHP);
				}	break;

				case _hoops_HGACR: {
					_hoops_CSIHP (_hoops_HGACR, _hoops_RCACR,
								   draw_3d_geometry, _hoops_CICHP);
				}	break;

				case _hoops_IGACR: {
					_hoops_CSIHP (_hoops_IGACR, _hoops_RCACR,
								   draw_text, _hoops_PHCHP);
				}	break;

				case _hoops_CGACR: {
					_hoops_CSIHP (_hoops_CGACR, _hoops_RCACR,
								   draw_window, _hoops_HCCHP);
				}	break;

				case _hoops_SGACR: {
					_hoops_CSIHP (_hoops_SGACR, _hoops_RCACR,
								   draw_segment, _hoops_CCCHP);
				}	break;

				case _hoops_GRACR: {
					_hoops_CSIHP (_hoops_GRACR, _hoops_RCACR,
								   draw_segment_tree, _hoops_CCCHP);
				}	break;

			} while ((_hoops_RCACR = _hoops_RCACR->next) != null);
#endif
		}	break;

		case HK_USER_OPTIONS: {
			if (!BIT(_hoops_PCGS._hoops_IPPGR, _hoops_GGCAA(HK_USER_OPTIONS))) {
				_hoops_HPPIR const *	_hoops_IPPIR = (_hoops_HPPIR const *)_hoops_HPPGR;

				if (_hoops_IPPIR->_hoops_AGGSA && _hoops_IPPIR->_hoops_AGGSA->Count() > 0 ||
					_hoops_IPPIR->_hoops_IGGSA && _hoops_IPPIR->_hoops_IGGSA->Count() > 0) {
					_hoops_CIGIP _hoops_SIGIP = nr.Modify()->_hoops_GCGIP.Modify();
					if(!_hoops_SIGIP->_hoops_IGGSA)
						_hoops_SIGIP->_hoops_IGGSA = POOL_NEW(dc->memory_pool, _hoops_CGGSA)(dc->memory_pool);

					if (_hoops_IPPIR->_hoops_IGGSA && _hoops_IPPIR->_hoops_IGGSA->Count() > 0) {
						_hoops_HPPIR const *	_hoops_RCGIP;
						_hoops_CGGSA::UniqueCursor *	uc = _hoops_IPPIR->_hoops_IGGSA->GetUniqueCursor();
						while((_hoops_RCGIP = uc->Peek()) != null) {
							ASSERT(_hoops_RCGIP->_hoops_IGGSA == null);
							_hoops_PRRH(_hoops_RCGIP);
							_hoops_SIGIP->_hoops_IGGSA->AddFirst(_hoops_RCGIP);
							uc->Advance();
						}
						delete uc;
					}

					if (_hoops_IPPIR->_hoops_AGGSA && _hoops_IPPIR->_hoops_AGGSA->Count() > 0) {
						_hoops_PRRH(_hoops_IPPIR);
						_hoops_SIGIP->_hoops_IGGSA->AddFirst(_hoops_IPPIR);
					}
				}
			}
		}	break;

		default: {
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, Sprintf_D (null,
				"'Selection Downwind' - unknown type '%d'", _hoops_HPPGR->type));
			return;
		}		/* _hoops_IHSA; */
	} while ((_hoops_HPPGR = _hoops_HPPGR->next) != null);

	if (_hoops_RPGIP &&
		nr->transform_rendition->_hoops_SPH->projection == _hoops_GHH) {
		/* _hoops_SR _hoops_HHGC _hoops_RH _hoops_ARGR _hoops_GSSP _hoops_AHC _hoops_IIGR _hoops_RH _hoops_CARA _hoops_CGRS (_hoops_PGAP _hoops_SRIPR _hoops_IS _hoops_SHH _hoops_RH
		 * _hoops_HCHIA _hoops_ARIP _hoops_IIGR _hoops_RH _hoops_GCHRR _hoops_PRGIA _hoops_RSGA), _hoops_PPR _hoops_CACH _hoops_RSH _hoops_SGS _hoops_IIRIP _hoops_GPP _hoops_RH _hoops_RAR
		 * _hoops_AAGA.	_hoops_RH _hoops_AHHSR _hoops_IIGR _hoops_SGS _hoops_CCA _hoops_RH _hoops_SAAP _hoops_GIRA _hoops_CGH _hoops_PPGR _hoops_IH
		 * _hoops_RH _hoops_IGIR _hoops_AGRP _hoops_SAPGP _hoops_IS _hoops_AIHP
		 */
		_hoops_HHRA const *				_hoops_SPH = nr->transform_rendition->_hoops_SPH;
		_hoops_SGCC const &	_hoops_HSGA = nr->transform_rendition->_hoops_IPH;
		Point const *				origin = (Point const *)&_hoops_HSGA->data.elements[3][0];
		float						scale;
		_hoops_ISGI			temp;

		/* '_hoops_GHGP' _hoops_IIGR _hoops_IPPA _hoops_PHGSR _hoops_RHIR _hoops_SARA _hoops_AHC */
		scale = -(_hoops_SPH->position.x * _hoops_SPH->_hoops_IIPCR.x +
				  _hoops_SPH->position.y * _hoops_SPH->_hoops_IIPCR.y +
				  _hoops_SPH->position.z * _hoops_SPH->_hoops_IIPCR.z);
		/* _hoops_PRRGR _hoops_CGRS _hoops_CIAA _hoops_SARA _hoops_AAGA _hoops_CSCHR _hoops_IS _hoops_SARA _hoops_AHC */
		scale += origin->x * _hoops_SPH->_hoops_IIPCR.x + origin->y * _hoops_SPH->_hoops_IIPCR.y + origin->z * _hoops_SPH->_hoops_IIPCR.z;
		/* _hoops_CSRA _hoops_RRPS _hoops_IS _hoops_SARA _hoops_GIRA */
		scale /= _hoops_SPH->_hoops_SRIR;

		/* _hoops_PSSSR _hoops_IH _hoops_AHCI _hoops_ARAR */
		if (scale > nr->transform_rendition->_hoops_CHCR) {
			HI_Figure_Scale_Matrix (scale, scale, scale, &temp.matrix);
			HD_Downwind_Modelling_Matrix (nr, (Attribute const *)&temp);
		}
	}
#endif
}

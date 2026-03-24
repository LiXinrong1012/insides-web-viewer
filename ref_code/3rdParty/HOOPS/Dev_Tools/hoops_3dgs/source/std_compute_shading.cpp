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
 * $Id: obf_tmp.txt 1.121 2010-06-04 21:37:19 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

/*
 * _hoops_AHGHR:
 *	1  _hoops_PCCP _hoops_CARA _hoops_APIR,
 *	2  _hoops_AGIIP _hoops_RH _hoops_GSSP-_hoops_GC _hoops_ACAGR _hoops_IIGR _hoops_RH _hoops_CARA
 *		 (_hoops_RPP _hoops_SICHS->_hoops_CGIPH),
 *	3  _hoops_RH _hoops_CAHA'_hoops_GRI _hoops_IPPA (_hoops_GCCHS _hoops_IIGR _hoops_IRS _hoops_GSSP _hoops_GC _hoops_GSSR _hoops_PPR _hoops_GHGP),
 * _hoops_CSGA _hoops_RH _hoops_SRAA _hoops_HAIR _hoops_IIGR _hoops_RGR _hoops_CIP _hoops_CARA.
 */
GLOBAL_FUNCTION void HD_Standard_Compute_Shading (
	Net_Rendition const &		nr,
	_hoops_PC const &		_hoops_RPPHP,
	_hoops_HHA const &	_hoops_ISHIR,
	Point const *				_hoops_ICAGA,
	RGB const *					color,
	_hoops_ARPA const *				plane,
	Vector const *				_hoops_ASACP,
	_hoops_RSSH const *			params,
	Integer32					param_width,
	_hoops_SSIC				param_flags,
	RGBA alter *				result,
	RGBA alter *				_hoops_RPCSP) 
{
	_hoops_AS const *		light;
	RGBA						_hoops_CSHR;
	RGBA						_hoops_RCCHS;
	Vector const *				normal;
	Vector						_hoops_ACCHS = _hoops_IRGA::_hoops_CRGA;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_HHRA const *				_hoops_SPH = _hoops_IHCR->_hoops_SPH;
	float						_hoops_PCCHS;
	Vector						_hoops_SGRRC;
	Vector const *				_hoops_IHPGA;
	RGB							_hoops_HCCHS;
	RGBA						_hoops_AGCSH;

	UNREFERENCED(_hoops_ASACP);

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_SSRAP)) return;
#endif

	if (color == null)
		color = &_hoops_ISHIR->_hoops_CSHR;
	_hoops_CSHR.red	= color->red;
	_hoops_CSHR.green = color->green;
	_hoops_CSHR.blue	= color->blue;
	_hoops_CSHR.alpha = 1.0f;

#if 0
	if (BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI) || 
		nr->_hoops_SRA->options._hoops_SIAH) {
		_hoops_CSHR = RGB(_hoops_CSHR._hoops_CPIR());
	}
#endif

	_hoops_RCCHS.red	 = _hoops_ISHIR->color[_hoops_HIA].red;
	_hoops_RCCHS.green = _hoops_ISHIR->color[_hoops_HIA].green;
	_hoops_RCCHS.blue	 = _hoops_ISHIR->color[_hoops_HIA].blue;
	_hoops_RCCHS.alpha = 1.0f;

	normal = (Vector const *)plane;


#ifndef DISABLE_TEXTURING
	if (params != null && param_width>0 && _hoops_ISHIR->_hoops_ARIR) {
		_hoops_HIR const *	_hoops_PGC = _hoops_ISHIR->_hoops_SCA;

		if (_hoops_PGC) {
			if (ANYBIT (_hoops_PGC->texture->_hoops_SCR, _hoops_PGA|_hoops_IGA|_hoops_GSR) || 
				_hoops_PGC->_hoops_HGA>0)
				_hoops_CSHR.alpha = 1;
			else
				_hoops_CSHR.alpha = 0;

			do {
				if (BIT (_hoops_PGC->texture->_hoops_SCR, _hoops_GSR))
					continue;  //_hoops_PAH'_hoops_RA _hoops_ICCHS _hoops_AIRRR _hoops_GGR _hoops_ICCGR

				HD_Standard_Compute_Texture (nr, 
							_hoops_PGC->texture,
							_hoops_ICAGA, plane, 
							params, param_width, param_flags,
							_hoops_RHGRA,
							&_hoops_AGCSH);

				if (BIT (_hoops_PGC->flags, _hoops_PRA)) {
					_hoops_AHAH const &				_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;

					if (BIT (_hoops_PGC->flags, _hoops_PPIR)) {
						_hoops_AGCSH.red *= _hoops_CSHR.red;
						_hoops_AGCSH.green *= _hoops_CSHR.green;
						_hoops_AGCSH.blue *= _hoops_CSHR.blue;
					}
					else {
						_hoops_AGCSH.red *= _hoops_PGC->texture->_hoops_HPIR._hoops_IPIR.red;
						_hoops_AGCSH.green *= _hoops_PGC->texture->_hoops_HPIR._hoops_IPIR.green;
						_hoops_AGCSH.blue *= _hoops_PGC->texture->_hoops_HPIR._hoops_IPIR.blue;
					}

					if (BIT (_hoops_PHAH.options, _hoops_CHRH)) {
						float		_hoops_CCCHS = _hoops_AGCSH.alpha;
						_hoops_AGCSH = HD_Apply_Color_Effects (_hoops_AGCSH, _hoops_PHAH);
						_hoops_AGCSH.alpha = _hoops_CCCHS;
					}
				}
				if (BIT (_hoops_PGC->texture->_hoops_SCR, _hoops_IGA)) {
					_hoops_AGCSH.red *= _hoops_CSHR.red;
					_hoops_AGCSH.green *= _hoops_CSHR.green;
					_hoops_AGCSH.blue *= _hoops_CSHR.blue;
				}

				_hoops_GRA const &	_hoops_RRA = nr->_hoops_ARA;
				_hoops_AGCSH.red   *= _hoops_RRA->image._hoops_HRA.red;
				_hoops_AGCSH.green *= _hoops_RRA->image._hoops_HRA.green;
				_hoops_AGCSH.blue	 *= _hoops_RRA->image._hoops_HRA.blue;

				if (BIT (_hoops_PGC->texture->_hoops_SCR, _hoops_PGA) || _hoops_PGC->_hoops_HGA > 0) {
					_hoops_CSHR.red	= _hoops_AGCSH.red*_hoops_AGCSH.alpha + _hoops_CSHR.red*(1.0f-_hoops_AGCSH.alpha);
					_hoops_CSHR.green = _hoops_AGCSH.green*_hoops_AGCSH.alpha + _hoops_CSHR.green*(1.0f-_hoops_AGCSH.alpha);
					_hoops_CSHR.blue	= _hoops_AGCSH.blue*_hoops_AGCSH.alpha + _hoops_CSHR.blue*(1.0f-_hoops_AGCSH.alpha);
					_hoops_CSHR.alpha	= _hoops_AGCSH.alpha*_hoops_AGCSH.alpha + _hoops_CSHR.alpha*(1.0f-_hoops_AGCSH.alpha);
				}
				else {
					_hoops_CSHR.red	= _hoops_AGCSH.red;
					_hoops_CSHR.green = _hoops_AGCSH.green;
					_hoops_CSHR.blue	= _hoops_AGCSH.blue;
					_hoops_CSHR.alpha = _hoops_AGCSH.alpha;
				}
			} while ((_hoops_PGC = _hoops_PGC->next) != null);
		}

		if (_hoops_ISHIR->texture[_hoops_HIA] != null) {
			HD_Standard_Compute_Texture (nr, 
									_hoops_ISHIR->texture[_hoops_HIA],
									_hoops_ICAGA, plane, 
									params, param_width, param_flags,
									_hoops_PIARA,
									&_hoops_RCCHS);
			if (BIT (_hoops_ISHIR->texture[_hoops_HIA]->_hoops_SCR, _hoops_IGA)) {
				_hoops_RCCHS.red *= _hoops_ISHIR->color[_hoops_HIA].red;
				_hoops_RCCHS.green *= _hoops_ISHIR->color[_hoops_HIA].green;
				_hoops_RCCHS.blue *= _hoops_ISHIR->color[_hoops_HIA].blue;
			}			
		}
	}
#endif

	/*_hoops_GHI _hoops_APSR*/
	_hoops_HCCHS.red = _hoops_HCCHS.green = _hoops_HCCHS.blue = 0.0f;

	if (_hoops_RPPHP == null || plane == null || !BIT (_hoops_IHCR->flags, _hoops_GRHH))
		*result = _hoops_CSHR;
	else {
		/*
		 * _hoops_PS *_hoops_AA* _hoops_HS _hoops_SS _hoops_GGR _hoops_RH _hoops_HIRA
		 */
		_hoops_GRGH const &_hoops_RRGH = nr->_hoops_IRR;
		float _hoops_SCCHS;

		/*
		 * _hoops_CGP _hoops_SR _hoops_HS _hoops_IRS _hoops_IRGH _hoops_GSCHS/_hoops_SARA _hoops_GGR _hoops_IRS _hoops_HIRA
		 */
		if (BIT (nr->_hoops_IRR->_hoops_PPH, Rendo_LOCAL_VIEWER) ||
			_hoops_SPH->_hoops_IHCH != 0.0f || _hoops_SPH->_hoops_HHCH != 0.0f) {
			if (BIT (nr->_hoops_IRR->_hoops_PPH, Rendo_LOCAL_VIEWER)) {
				_hoops_SGRRC.x = _hoops_ICAGA->x - _hoops_SPH->position.x;
				_hoops_SGRRC.y = _hoops_ICAGA->y - _hoops_SPH->position.y;
				_hoops_SGRRC.z = _hoops_ICAGA->z - _hoops_SPH->position.z;
			}
			else {
				_hoops_SGRRC.x = _hoops_SPH->target.x - _hoops_SPH->position.x;
				_hoops_SGRRC.y = _hoops_SPH->target.y - _hoops_SPH->position.y;
				_hoops_SGRRC.z = _hoops_SPH->target.z - _hoops_SPH->position.z;
			}

			if (_hoops_SPH->_hoops_IHCH != 0.0f) {
				float			_hoops_SHCH, _hoops_GICH;
				float			_hoops_RSIPA;

				_hoops_RICH (_hoops_SPH->_hoops_IHCH, _hoops_SHCH, _hoops_GICH);
				_hoops_RSIPA = _hoops_SPH->_hoops_SRIR * _hoops_SHCH / _hoops_GICH;

				_hoops_SGRRC.x -= _hoops_RSIPA * _hoops_SPH->up_vector.x;
				_hoops_SGRRC.y -= _hoops_RSIPA * _hoops_SPH->up_vector.y;
				_hoops_SGRRC.z -= _hoops_RSIPA * _hoops_SPH->up_vector.z;
			}

			if (_hoops_SPH->_hoops_HHCH != 0.0f) {
				float			_hoops_SHCH, _hoops_GICH;
				float			_hoops_RSIPA;

				_hoops_RICH (_hoops_SPH->_hoops_HHCH, _hoops_SHCH, _hoops_GICH);
				_hoops_RSIPA = _hoops_SPH->_hoops_SRIR * _hoops_SHCH / _hoops_GICH;

				_hoops_SGRRC.x -= _hoops_RSIPA * _hoops_SPH->_hoops_CRSS.x;
				_hoops_SGRRC.y -= _hoops_RSIPA * _hoops_SPH->_hoops_CRSS.y;
				_hoops_SGRRC.z -= _hoops_RSIPA * _hoops_SPH->_hoops_CRSS.z;
			}

			(void)HI_Normalize (&_hoops_SGRRC);
			_hoops_IHPGA = &_hoops_SGRRC;
		}
		else
			_hoops_IHPGA = &_hoops_SPH->_hoops_IIPCR;

		/* _hoops_RSCHS _hoops_IHSR */
		if (_hoops_ISHIR->texture[_hoops_HCA] != null) {
			RGBA		_hoops_ASCHS;
			HD_Standard_Compute_Texture (nr, 
									_hoops_ISHIR->texture[_hoops_HCA],
									_hoops_ICAGA, plane, 
									params, param_width, param_flags,
									_hoops_CIARA,
									&_hoops_ASCHS);
			if (BIT (_hoops_ISHIR->texture[_hoops_HCA]->_hoops_SCR, _hoops_IGA)) {
				_hoops_ASCHS.red *= _hoops_ISHIR->color[_hoops_HCA].red;
				_hoops_ASCHS.green *= _hoops_ISHIR->color[_hoops_HCA].green;
				_hoops_ASCHS.blue *= _hoops_ISHIR->color[_hoops_HCA].blue;
			}
			*result = _hoops_ASCHS;
		}
		else
			*result = _hoops_ISHIR->color[_hoops_HCA];

		if (_hoops_ISHIR->texture[_hoops_PCA] != null) {
			RGBA		_hoops_PSCHS;
			HD_Standard_Compute_Texture (nr, 
									_hoops_ISHIR->texture[_hoops_PCA],
									_hoops_ICAGA, plane, 
									params, param_width, param_flags,
									_hoops_IIARA,
									&_hoops_PSCHS);
			if (BIT (_hoops_ISHIR->texture[_hoops_PCA]->_hoops_SCR, _hoops_IGA)) {
				_hoops_PSCHS.red *= _hoops_ISHIR->color[_hoops_PCA].red;
				_hoops_PSCHS.green *= _hoops_ISHIR->color[_hoops_PCA].green;
				_hoops_PSCHS.blue *= _hoops_ISHIR->color[_hoops_PCA].blue;
			}
			_hoops_CSHR.alpha *= 1.0f - _hoops_PSCHS._hoops_CPIR();
		}

		if (_hoops_SPH->projection == _hoops_GHH)
			_hoops_PCCHS = plane->a * _hoops_SPH->position.x +
							  plane->b * _hoops_SPH->position.y +
							  plane->c * _hoops_SPH->position.z +
							  plane->d;
		else
			_hoops_PCCHS = -(plane->a * _hoops_SPH->_hoops_IIPCR.x +
								plane->b * _hoops_SPH->_hoops_IIPCR.y +
								plane->c * _hoops_SPH->_hoops_IIPCR.z);

		if (nr->_hoops_IRR->_hoops_HRGA == _hoops_IRGA::_hoops_CRGA)
			_hoops_SCCHS = normal->_hoops_SSRP (_hoops_SPH->up_vector);
		else
			_hoops_SCCHS = normal->_hoops_SSRP (nr->_hoops_IRR->_hoops_HRGA);
		_hoops_SCCHS = _hoops_SCCHS/2 + 0.5f;
		if ((light = _hoops_RPPHP->_hoops_CGR) != null) do {
			/* "_hoops_GHAP" = _hoops_IGAHS, "_hoops_PGGIR" = _hoops_GSSR, "_hoops_AHGPH" = _hoops_HSCHS */
			float					_hoops_ISCHS;
			float					_hoops_CSCHS;
			bool					_hoops_SSCHS = false;
			float					_hoops_GGSHS;
			RGB						_hoops_RGSHS;
			Vector					_hoops_AGSHS;
			float					_hoops_SIRH;
			float					_hoops_SGC;

			/* _hoops_RIR-_hoops_RRR _hoops_AASR (_hoops_PGSHS) */
			result->red	  += _hoops_CSHR.red   * light->_hoops_HASR.red * _hoops_SCCHS;
			result->green += _hoops_CSHR.green * light->_hoops_HASR.green * _hoops_SCCHS;
			result->blue  += _hoops_CSHR.blue  * light->_hoops_HASR.blue * _hoops_SCCHS;
			result->red	  += _hoops_CSHR.red   * light->_hoops_CASR.red * (1-_hoops_SCCHS);
			result->green += _hoops_CSHR.green * light->_hoops_CASR.green * (1-_hoops_SCCHS);
			result->blue  += _hoops_CSHR.blue  * light->_hoops_CASR.blue * (1-_hoops_SCCHS);

			/*
			 * _hoops_PS'_hoops_ASAR _hoops_GPIHR _hoops_GGR _hoops_RGR _hoops_RRR _hoops_RGAR _hoops_RPP _hoops_SCH _hoops_HRGR _hoops_GPP
			 * _hoops_RH _hoops_PSHR _hoops_PPAP _hoops_IIGR _hoops_RH _hoops_HSSP _hoops_GAR _hoops_RH _hoops_GSCHS _hoops_HRGR -
			 * "_hoops_HGSHS" _hoops_SIGH _hoops_GPP _hoops_PGAP _hoops_PPAP _hoops_IIGR _hoops_RH
			 * _hoops_IPPA _hoops_RH _hoops_SARA _hoops_ISSCI; "_hoops_IGSHS" _hoops_SRIPR _hoops_IS _hoops_RCRP _hoops_RH
			 * _hoops_PSHR _hoops_PIRA _hoops_IH _hoops_PCCP _hoops_GCRS _hoops_SGIP _hoops_SGGR _hoops_RRR.
			 */
			switch (light->_hoops_PRR) {
			  case _hoops_H: {
				  /*
				   * _hoops_IGAHS (=_hoops_RRR->_hoops_HAGA) _hoops_GICPR _hoops_IS _hoops_SHH _hoops_PPRAR
				   * _hoops_GGR _hoops_RH _hoops_IISRR _hoops_CAPP _hoops_IH _hoops_RGR _hoops_GPRR _hoops_IIGR _hoops_RRR
				   */

				  if ((_hoops_ISCHS = light->direction.x * normal->x +
							   light->direction.y * normal->y +
							   light->direction.z * normal->z) < 0.0f) {
					  if (_hoops_PCCHS >= 0.0f)
						  _hoops_SSCHS = true;
					  _hoops_CSCHS = -_hoops_ISCHS;
				  }
				  else {
					  if (_hoops_PCCHS <= 0.0f)
						  _hoops_SSCHS = true;
					  _hoops_CSCHS = _hoops_ISCHS;
				  }
			  }	  break;

			  case _hoops_S:
			  case _hoops_C:
			  case _hoops_I: {
				  _hoops_ACCHS.x = light->position.x - _hoops_ICAGA->x;
				  _hoops_ACCHS.y = light->position.y - _hoops_ICAGA->y;
				  _hoops_ACCHS.z = light->position.z - _hoops_ICAGA->z;
				  (void)HI_Normalize (&_hoops_ACCHS);

				  if ((_hoops_ISCHS = _hoops_ACCHS.x * normal->x +
							   _hoops_ACCHS.y * normal->y +
							   _hoops_ACCHS.z * normal->z) < 0.0f) {
					  if (_hoops_PCCHS >= 0.0f)
						  _hoops_SSCHS = true;
					  _hoops_CSCHS = -_hoops_ISCHS;
				  }
				  else {
					  if (_hoops_PCCHS <= 0.0f)
						  _hoops_SSCHS = true;
					  _hoops_CSCHS = _hoops_ISCHS;
				  }
			  }	  break;

			  default: {
				  _hoops_ISCHS = _hoops_CSCHS = 0.0f;
			  }	  break;
			}


			/*
			 * _hoops_CGSHS, _hoops_SAGH _hoops_RGAR _hoops_IH _hoops_CCAC _hoops_PPR _hoops_GISR _hoops_SS
			 */
			switch (light->_hoops_PRR) {
			  case _hoops_H:
			  case _hoops_C: {
				  _hoops_GGSHS = 0.0f;
				  _hoops_SIRH = 1.0f;
				  /* _hoops_SGSHS *= _hoops_HCGGR; */
			  }	  break;

			  case _hoops_S: {
				  _hoops_GGSHS = -(_hoops_ACCHS.x * light->direction.x +
							   _hoops_ACCHS.y * light->direction.y +
							   _hoops_ACCHS.z * light->direction.z);

				  /* _hoops_RSRA-_hoops_RPSA _hoops_GRSHS _hoops_RH _hoops_RHPH _hoops_PPRRR? */
				  if (light->_hoops_HSSGP != _hoops_GCSGP && _hoops_GGSHS < 0.0f) continue;

				  if (_hoops_GGSHS < 0.0f) /* _hoops_CCIH _hoops_CCIR */
					  _hoops_GGSHS = -_hoops_GGSHS;

				  _hoops_SIRH = _hoops_GGSHS;
				  _hoops_CSCHS *= _hoops_SIRH;
			  }	  break;

			  case _hoops_I: {
				  if ((_hoops_GGSHS = -(_hoops_ACCHS.x * light->direction.x +
									_hoops_ACCHS.y * light->direction.y +
									_hoops_ACCHS.z * light->direction.z)) <
					  light->_hoops_HCASP) continue;
				  else {
					  float			_hoops_RAHCR = _hoops_ISSSR (_hoops_GGSHS);

					  if (_hoops_RAHCR <= light->_hoops_ACSR)
						  /* _hoops_GIAA _hoops_PSSPR _hoops_AAHIA */
						  _hoops_SIRH = 1.0f;
					  else if (_hoops_RAHCR < light->_hoops_HCSR)
						  /* _hoops_GAPA _hoops_RRSHS - _hoops_PSRHA _hoops_ACIAR */
						  _hoops_SIRH = (light->_hoops_HCSR - _hoops_RAHCR) /
										(light->_hoops_HCSR - light->_hoops_ACSR);
					  else
						  /* _hoops_SIPP */
						  continue;

					  if (light->_hoops_CCSGP > 0.0f)
						  _hoops_SIRH *= HI_Exponentiate (_hoops_GGSHS, light->_hoops_CCSGP);

					  _hoops_CSCHS *= _hoops_SIRH;
				  }
			  }	  break;

			  default: {
				  _hoops_SIRH = 0.0f;
			  }	  break;
			}

			/*
			 * _hoops_ARSHS
			 */
			if (!_hoops_SSCHS) {
				_hoops_RGSHS.red	 = _hoops_CSHR.red   * _hoops_CSCHS;
				_hoops_RGSHS.green = _hoops_CSHR.green * _hoops_CSCHS;
				_hoops_RGSHS.blue	 = _hoops_CSHR.blue  * _hoops_CSCHS;
			}
			else
				_hoops_RGSHS.red = _hoops_RGSHS.green = _hoops_RGSHS.blue = 0;

			/*
			 * _hoops_PRSHS
			 *
			 * _hoops_IPCP _hoops_HRSHS _hoops_HRGR _hoops_IAIAR _hoops_HPIAA _hoops_SR _hoops_HHGC _hoops_IS
			 * _hoops_HRSPA 64 _hoops_HHASH _hoops_HARH _hoops_GGSR _hoops_IIGR 256 _hoops_HPGR _hoops_RH _hoops_IRSHS _hoops_PIRA.
			 * _hoops_HGI _hoops_AGSR _hoops_SR _hoops_PAH _hoops_CRSHS _hoops_PCCP _hoops_RIHH _hoops_IIGR _hoops_SPR _hoops_ARIP _hoops_GGR _hoops_SRSHS-_hoops_AIAA.
			 *	  _hoops_GASHS _hoops_SARR:
			 *		_hoops_SAIPR^_hoops_ACHP = 1/64
			 *		_hoops_SAIPR = (1/64)^(1/_hoops_ACHP)
			 *	  _hoops_RASHS _hoops_SARR:
			 *		_hoops_SAIPR / (_hoops_ACHP - _hoops_ACHP * _hoops_SAIPR + _hoops_SAIPR) = 1/64
			 *		_hoops_SAIPR = _hoops_ACHP / (_hoops_ACHP + 63)
			 */
#			define _hoops_AASHS	  0.30f
#			define _hoops_PASHS	  0.81f
#			define _hoops_HASHS 0.50f		/* 0.76f */

			/*
			 * _hoops_IASHS _hoops_HSH _hoops_CHR _hoops_SSPP _hoops_SGASP _hoops_CIAA _hoops_IGPRA _hoops_PIRA
			 * _hoops_IS _hoops_ASRHA _hoops_IRSHS, _hoops_CRSHA _hoops_CASHS _hoops_RH _hoops_GPCCP
			 * _hoops_IIGR _hoops_RH _hoops_GHI _hoops_SASHS _hoops_PICSI _hoops_HPP _hoops_RH _hoops_GPSHS.
			 */
#			define _hoops_RPSHS		  4.0f	/* _hoops_CACH _hoops_GCHRA _hoops_GICHI _hoops_APSHS */
#			define _hoops_PPSHS	  10.0f /* _hoops_HPSHS * ? */

			switch (light->_hoops_PRR) {
				case _hoops_H: {
				  /*
				   * _hoops_IPSHS _hoops_SARR
				   * _hoops_GRI = |_hoops_CIPII._hoops_PGGIR|
				   */
					if ((_hoops_SGC = light->_hoops_ARSR.x * normal->x +
								  light->_hoops_ARSR.y * normal->y +
								  light->_hoops_ARSR.z * normal->z) < 0)
						_hoops_SGC = -_hoops_SGC;

					/* _hoops_GGCR _hoops_SCH _hoops_GGR
					 * _hoops_PIP: _hoops_GHI _hoops_ASSP'_hoops_RA _hoops_GARIR _hoops_GPP _hoops_SPI _hoops_CARA _hoops_HAIR,
					 *	   _hoops_HIH _hoops_RHAP _hoops_GARIR _hoops_GPP _hoops_RH _hoops_GHI _hoops_CPSHS _hoops_IIGR _hoops_RH _hoops_CARA
					 * _hoops_CGSHS _hoops_HRGR _hoops_GICPR _hoops_IS _hoops_SHH 1.0 _hoops_IH _hoops_RSSR _hoops_SS
					 */
#if 1
					float _hoops_SPSHS;
					if (_hoops_ISHIR->gloss >= 2.0f)
						_hoops_SPSHS = _hoops_HASHS;
					else
						_hoops_SPSHS = 0;

					if (_hoops_SGC > 0) {
						_hoops_SGC /= (_hoops_ISHIR->gloss * _hoops_PPSHS) *
								  (1.0f - _hoops_SGC) + _hoops_SGC;
						_hoops_HCCHS.red   += _hoops_SGC * _hoops_RCCHS.red	* light->color.red;
						_hoops_HCCHS.green += _hoops_SGC * _hoops_RCCHS.green * light->color.green;
						_hoops_HCCHS.blue  += _hoops_SGC * _hoops_RCCHS.blue  * light->color.blue;
					}
#else
					if (_hoops_SGC > _hoops_PASHS) {
						_hoops_SGC = HI_Exponentiate (_hoops_SGC,
												  _hoops_ISHIR->gloss * _hoops_RPSHS);
						_hoops_HCCHS.red   += _hoops_SGC * _hoops_RCCHS.red	* light->color.red;
						_hoops_HCCHS.green += _hoops_SGC * _hoops_RCCHS.green * light->color.green;
						_hoops_HCCHS.blue  += _hoops_SGC * _hoops_RCCHS.blue  * light->color.blue;
					}
#endif
			  }	  break;

			  case _hoops_S:
			  case _hoops_C:
			  case _hoops_I: {
				  /*
				   * _hoops_GHSHS _hoops_ASGAH
				   * _hoops_PHAA, _hoops_CAHA _hoops_HSCHS _hoops_AAGA _hoops_AHGPH
				   * (_hoops_GHAP _hoops_SISR _hoops_PGGIR = _hoops_PGGIR _hoops_SISR _hoops_AHGPH, _hoops_GHAP . _hoops_PGGIR = _hoops_PGGIR . _hoops_AHGPH, _hoops_PGGIR . _hoops_PGGIR = 1, _hoops_IPSH _hoops_GAIPA)
				   */
				  _hoops_ISCHS *= 2.0f;
				  _hoops_AGSHS.x = _hoops_ACCHS.x - _hoops_ISCHS * normal->x;
				  _hoops_AGSHS.y = _hoops_ACCHS.y - _hoops_ISCHS * normal->y;
				  _hoops_AGSHS.z = _hoops_ACCHS.z - _hoops_ISCHS * normal->z;

				  _hoops_SGC = _hoops_AGSHS.x * _hoops_IHPGA->x +
							 _hoops_AGSHS.y * _hoops_IHPGA->y +
							 _hoops_AGSHS.z * _hoops_IHPGA->z;

				  if (_hoops_SGC > _hoops_AASHS) {
					  _hoops_SGC = HI_Exponentiate (_hoops_SGC, _hoops_ISHIR->gloss);
					  /*
					   * _hoops_GGCR _hoops_SCH _hoops_GGR
					   * _hoops_PIP: _hoops_GHI _hoops_ASSP'_hoops_RA _hoops_GARIR _hoops_GPP _hoops_SPI _hoops_CARA _hoops_HAIR,
					   *	   _hoops_HIH _hoops_RHAP _hoops_GARIR _hoops_GPP _hoops_RH _hoops_GHI _hoops_CPSHS _hoops_IIGR _hoops_RH _hoops_CARA
					   */
					  _hoops_SGC *= _hoops_SIRH;
					  _hoops_HCCHS.red   += _hoops_SGC * _hoops_RCCHS.red	  * light->color.red;
					  _hoops_HCCHS.green += _hoops_SGC * _hoops_RCCHS.green * light->color.green;
					  _hoops_HCCHS.blue  += _hoops_SGC * _hoops_RCCHS.blue  * light->color.blue;
				  }
			  }	  break;
			}

			/*
			 * _hoops_IRHH _hoops_RCRR _hoops_HAR _hoops_RRI _hoops_HSAR 100% _hoops_IIGR _hoops_RH _hoops_RRR _hoops_HRGR _hoops_HSCHS
			 * _hoops_PIP: _hoops_IRS _hoops_GIH _hoops_PPRRR _hoops_SIAS _hoops_SHH _hoops_IS _hoops_HRSPA _hoops_RH _hoops_RHSHS _hoops_IIGR _hoops_RH
			 *		 _hoops_HAIR _hoops_RPP _hoops_SR _hoops_CHR _hoops_GGSR _hoops_IIGR _hoops_CCIR.
			 */
			if (_hoops_RGSHS.red	 > 1.0f) _hoops_RGSHS.red	  = 1.0f;
			if (_hoops_RGSHS.green > 1.0f) _hoops_RGSHS.green = 1.0f;
			if (_hoops_RGSHS.blue	 > 1.0f) _hoops_RGSHS.blue  = 1.0f;

			/* _hoops_PHHSR _hoops_HPP _hoops_RH _hoops_RRR _hoops_HAIR _hoops_PPR _hoops_GGCR _hoops_SCH _hoops_GGR */
			result->red	  += _hoops_RGSHS.red	  * light->color.red;
			result->green += _hoops_RGSHS.green * light->color.green;
			result->blue  += _hoops_RGSHS.blue  * light->color.blue;
		} _hoops_RGGA ((light = light->next) == null);

		result->red	  += _hoops_CSHR.red   * _hoops_RRGH->_hoops_HASR.red * _hoops_SCCHS;
		result->green += _hoops_CSHR.green * _hoops_RRGH->_hoops_HASR.green * _hoops_SCCHS;
		result->blue  += _hoops_CSHR.blue  * _hoops_RRGH->_hoops_HASR.blue * _hoops_SCCHS;
		result->red	  += _hoops_CSHR.red   * _hoops_RRGH->_hoops_CASR.red * (1-_hoops_SCCHS);
		result->green += _hoops_CSHR.green * _hoops_RRGH->_hoops_CASR.green * (1-_hoops_SCCHS);
		result->blue  += _hoops_CSHR.blue  * _hoops_RRGH->_hoops_CASR.blue * (1-_hoops_SCCHS);
	}

#ifndef DISABLE_TEXTURING
	/* _hoops_GGCR _hoops_GGR _hoops_RHI _hoops_SIA */
	if (_hoops_ISHIR->texture[_hoops_RIA] != null) {
		RGBA					_hoops_RAC;

		_hoops_RAC.red	 = _hoops_ISHIR->color[_hoops_ACA].red;
		_hoops_RAC.green = _hoops_ISHIR->color[_hoops_ACA].green;
		_hoops_RAC.blue	 = _hoops_ISHIR->color[_hoops_ACA].blue;
		_hoops_RAC.alpha = 1.0f;

		if (params != null) {
			if (_hoops_ISHIR->texture[_hoops_ACA] != null) {
				if (BIT (_hoops_ISHIR->texture[_hoops_ACA]->_hoops_SCR, _hoops_IGA)) {
					HD_Standard_Compute_Texture (nr, 
										_hoops_ISHIR->texture[_hoops_ACA],
										_hoops_ICAGA, plane, 
										params, param_width, param_flags,
										_hoops_HIARA,
										&_hoops_AGCSH);

					_hoops_RAC.red	 *= _hoops_AGCSH.red;
					_hoops_RAC.green *= _hoops_AGCSH.green;
					_hoops_RAC.blue	 *= _hoops_AGCSH.blue;
					_hoops_RAC.alpha *= _hoops_AGCSH.alpha;
				}
				else
					HD_Standard_Compute_Texture (nr, 
										_hoops_ISHIR->texture[_hoops_ACA],
										_hoops_ICAGA, plane, 
										params, param_width, param_flags,
										_hoops_HIARA,
										&_hoops_RAC);
			}
		}


		HD_Standard_Compute_Texture (nr, 
						_hoops_ISHIR->texture[_hoops_RIA],
						_hoops_ICAGA, plane, 
						null, 0, 0,
						_hoops_GCARA,
						&_hoops_AGCSH);

#if 1
		_hoops_AGCSH.red *= _hoops_RAC.red;
		_hoops_AGCSH.green *= _hoops_RAC.green;
		_hoops_AGCSH.blue *= _hoops_RAC.blue;
	
#if 1
		float _hoops_HHGA = _hoops_RAC._hoops_CPIR();
		result->red *= 1-_hoops_HHGA;
		result->green *= 1-_hoops_HHGA;
		result->blue *= 1-_hoops_HHGA;
#else
		result->red *= 1-_hoops_RAC.red;
		result->green *= 1-_hoops_RAC.green;
		result->blue *= 1-_hoops_RAC.blue;
#endif

		result->red	  += _hoops_AGCSH.red;
		result->green += _hoops_AGCSH.green;
		result->blue  += _hoops_AGCSH.blue;
#else
		result->red	  = _hoops_AGCSH.red;
		result->green = _hoops_AGCSH.green;
		result->blue  = _hoops_AGCSH.blue;
#endif
	}
#endif

	if (_hoops_RPCSP) {
		_hoops_RPCSP->red = _hoops_HCCHS.red;
		_hoops_RPCSP->green = _hoops_HCCHS.green;
		_hoops_RPCSP->blue = _hoops_HCCHS.blue;
	}
	else {
		result->red += _hoops_HCCHS.red;
		result->green += _hoops_HCCHS.green;
		result->blue += _hoops_HCCHS.blue;
	}

	/*
	 * _hoops_IRHH _hoops_RCRR _hoops_RH _hoops_RCA _hoops_CSRA _hoops_GPGH'_hoops_RA _hoops_GHGA _hoops_AHSHS _hoops_PHSHS
	 * _hoops_PIP: _hoops_PS _hoops_HHS _hoops_RASHR _hoops_RGR _hoops_IS _hoops_RHHSR _hoops_RH _hoops_RHSHS _hoops_IIGR _hoops_RH _hoops_HAIR _hoops_RPP
	 *		 _hoops_SCH _hoops_ISSCI _hoops_GGSR _hoops_IIGR _hoops_CCIR.
	 */
	if (result->red > 1.0f) result->red = 1.0f;
	if (result->green > 1.0f) result->green = 1.0f;
	if (result->blue  > 1.0f) result->blue		= 1.0f;


	/*
	 * _hoops_CGP _hoops_RH _hoops_HIRA _hoops_HRGR _hoops_IS _hoops_SHH _hoops_HCH _hoops_HHSHS
	 *
	 * "_hoops_IHSHS _hoops_CHSHS" _hoops_AIH _hoops_SAAHS _hoops_SHSHS.
	 *
	 * _hoops_HRSHA = 0 _hoops_PAR _hoops_IPSP _hoops_PIRA
	 * _hoops_GISHS = 10 * |_hoops_SARA->_hoops_SAAP - _hoops_SARA->_hoops_AHC| _hoops_PAR _hoops_IPSP _hoops_PIRA
	 * _hoops_RISHS = |_hoops_ACAGR - _hoops_SARA->_hoops_AHC|
	 * _hoops_PAIR = (_hoops_RISHS - _hoops_GISHS) / (_hoops_HRSHA - _hoops_GISHS);
	 * _hoops_HACH _hoops_HAIR = _hoops_PAIR * _hoops_CIIA _hoops_HAIR + (1 - _hoops_PAIR) * _hoops_IGHP _hoops_HAIR
	 */
	if (BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HPH)) {
		_hoops_GCIR const &		_hoops_RCIR = nr->_hoops_CPP;
		Point								_hoops_AISHS;
		RGB const *							_hoops_PRHAC;
		float								hither, yon, _hoops_CRIR, _hoops_SIRH, _hoops_PISHS;

		_hoops_PRHAC = &nr->_hoops_SAIR->_hoops_GRAIP;
		hither = _hoops_RCIR->_hoops_CRIR.hither;
		yon	   = _hoops_RCIR->_hoops_CRIR.yon;

		_hoops_AISHS.x = _hoops_ICAGA->x - _hoops_SPH->position.x;
		_hoops_AISHS.y = _hoops_ICAGA->y - _hoops_SPH->position.y;
		_hoops_AISHS.z = _hoops_ICAGA->z - _hoops_SPH->position.z;
		_hoops_PISHS = _hoops_AISHS.x * _hoops_AISHS.x +
				_hoops_AISHS.y * _hoops_AISHS.y +
				_hoops_AISHS.z * _hoops_AISHS.z;

		if (_hoops_PISHS <= hither * hither)
			_hoops_SIRH = 1.0f;
		else if (_hoops_PISHS >= yon * yon)
			_hoops_SIRH = 0.0f;
		else
			_hoops_SIRH = (_hoops_SGIHR (_hoops_PISHS) - yon) / (hither - yon);

		_hoops_CRIR = 1.0f - _hoops_SIRH;
		result->red	  = _hoops_SIRH * result->red	+ _hoops_CRIR * _hoops_PRHAC->red;
		result->green = _hoops_SIRH * result->green + _hoops_CRIR * _hoops_PRHAC->green;
		result->blue  = _hoops_SIRH * result->blue	+ _hoops_CRIR * _hoops_PRHAC->blue;
	}

	result->alpha = _hoops_CSHR.alpha;
}




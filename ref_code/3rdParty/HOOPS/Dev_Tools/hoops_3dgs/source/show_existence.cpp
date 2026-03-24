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
 * $Id: obf_tmp.txt 1.120 2010-10-28 21:32:32 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "searchh.h"
#include "phedron.h"	/* _hoops_IH _hoops_ISHA, _hoops_HSP, _hoops_GPHA _hoops_SIHC */
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "adt.h"


#ifndef DISABLE_GEOMETRY_ATTRIBUTES

local bool _hoops_SCHCA (
	_hoops_RRHCA *	_hoops_ARHCA,
	Attribute const *		_hoops_ASGPR) {
	int						type = _hoops_ASGPR->type;

	switch (type) {
		case HK_COLOR: {
			_hoops_SSGI const *	color = (_hoops_SSGI const *)_hoops_ASGPR;

			if (ANYBIT (_hoops_ARHCA->_hoops_GAHCA.color.mask, color->_hoops_GHA))
				return true;
			else {
				_hoops_ACSGA const *	list = color->colors;

				do {
					int			i;

					for (i=0; i<_hoops_IIGRA; i++) {
						if (BIT (list->_hoops_GHA, 1<<i)) {
							if (list->type == _hoops_GIGRA) {
								_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;

								if (ANYBIT (_hoops_ARHCA->_hoops_GAHCA.color._hoops_HAA[i],
											_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA))
									break;
							}
							else {
								if (BIT (_hoops_ARHCA->_hoops_GAHCA.color._hoops_HAA[i], M_DIFFUSE))
									break;
							}
						}
					}
					if (i < _hoops_IIGRA) {
						return true;
						break;
					}
				} while ((list = list->next) != null);
			}
		}   break;

		case HK_RENDERING_OPTIONS: {
			_hoops_RHAIR const *	_hoops_AHAIR = (_hoops_RHAIR const *)_hoops_ASGPR;

			if (_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_ASHCA  & _hoops_AHAIR->_hoops_SCIAA ||
				_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA.simple & _hoops_AHAIR->_hoops_PSHCA ||
				_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_HSHCA & _hoops_AHAIR->_hoops_ISHCA ||
				_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_SSHCA & _hoops_AHAIR->_hoops_SSHCA.mask ||
				_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_RGICA & _hoops_AHAIR->_hoops_RGICA.mask ||
				_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_CGICA & _hoops_AHAIR->_hoops_AIAIR->mask ||
				_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_GRICA & _hoops_AHAIR->_hoops_PRSI->mask ||
				_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_APPI & _hoops_AHAIR->geometry->_hoops_APPI.mask ||
				_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_PSRIR & _hoops_AHAIR->geometry->_hoops_PSRIR.mask ||
				_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_GAICA & _hoops_AHAIR->geometry->_hoops_GAICA.mask ||
				_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_PRIGA & _hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.mask ||
				_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_GHSS & _hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask ||
				_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_PGICA & _hoops_AHAIR->_hoops_HGICA ||
				_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA.locks._hoops_IPPGR & _hoops_AHAIR->locks->normal.mask._hoops_IPPGR ||
				_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA.locks.color & _hoops_AHAIR->locks->normal.mask.color ||
				_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA.locks._hoops_RGP & _hoops_AHAIR->locks->normal.mask._hoops_RGP) {
				/* _hoops_RAICA */
				return true;
			}
		}   break;

		case HK_SELECTABILITY: {
			if (_hoops_ARHCA->_hoops_GAHCA._hoops_AAICA & ((_hoops_ASAIR const *)_hoops_ASGPR)->mask)
				return true;
		}	break;

		case HK_VISIBILITY: {
			if (_hoops_ARHCA->_hoops_GAHCA._hoops_RGP & ((_hoops_RSAIR const *)_hoops_ASGPR)->mask)
				return true;
		}	break;

		case HK_DRIVER_OPTIONS: {
			_hoops_GAPIR const *		_hoops_RAPIR = (_hoops_GAPIR const *)_hoops_ASGPR;

			if (_hoops_ARHCA->_hoops_GAHCA._hoops_PAICA.flags & _hoops_RAPIR->_hoops_HAICA ||
				_hoops_ARHCA->_hoops_GAHCA._hoops_PAICA.values & _hoops_RAPIR->_hoops_IAICA)
				return true;
		}	break;

		case HK_HEURISTICS: {
			_hoops_GHAIR const *			_hoops_GIGC = (_hoops_GHAIR const *)_hoops_ASGPR;

			if (_hoops_ARHCA->_hoops_GAHCA.heuristics.mask & _hoops_GIGC->mask ||
				_hoops_ARHCA->_hoops_GAHCA.heuristics._hoops_APH & _hoops_GIGC->_hoops_APH.mask)
				return true;
		}	break;

		case HK_TEXT_FONT: {
			if (_hoops_ARHCA->_hoops_GAHCA._hoops_CAICA & ((_hoops_AGPIR const *)_hoops_ASGPR)->_hoops_HAICA)
				return true;
		}	break;

		case HK_USER_OPTIONS: {
			if (_hoops_ARHCA->_hoops_GAHCA.user_options.count > 0) {
				_hoops_HPPIR const *		_hoops_IPPIR = (_hoops_HPPIR const *)_hoops_ASGPR;
				Option_Value const *		opt;
				int							_hoops_SAICA = _hoops_ARHCA->_hoops_GAHCA.user_options.count;
				int const *					_hoops_GPICA = _hoops_ARHCA->_hoops_GAHCA.user_options._hoops_GPICA;

				if ((opt = _hoops_IPPIR->option_list) != null) do {
					int						_hoops_RPICA = opt->type->id;

					for (int i=0; i<_hoops_SAICA; i++)
						if (_hoops_RPICA == _hoops_GPICA[i])
							return true;
				} while ((opt = opt->next) != null);

				if ((opt = _hoops_IPPIR->_hoops_APICA) != null) do {
					int						_hoops_RPICA = opt->type->id;

					for (int i=0; i<_hoops_SAICA; i++)
						if (_hoops_RPICA == _hoops_GPICA[i])
							return true;
				} while ((opt = opt->next) != null);
			}
		}	break;

		case _hoops_CPPIR: {
			_hoops_SPPIR const *			conditions = (_hoops_SPPIR const *)_hoops_ASGPR;

			if (BIT (_hoops_ARHCA->_hoops_GAHCA._hoops_APHCA, _hoops_PPHCA) &&
				conditions->count > 0)
				return true;

			if (BIT (_hoops_ARHCA->_hoops_GAHCA._hoops_APHCA, _hoops_HPHCA) &&
				conditions->_hoops_ACPGR != null)
				return true;

			if (_hoops_ARHCA->_hoops_GAHCA.conditions.count > 0) {
				int const *					_hoops_GPICA = _hoops_ARHCA->_hoops_GAHCA.conditions._hoops_GPICA;

				for (int i=0; i<_hoops_ARHCA->_hoops_GAHCA.conditions.count; i++) {
					int			index = _hoops_GPICA[i] / 32;
					int			offset = _hoops_GPICA[i] % 32;

					if (index < conditions->count &&
						BIT (conditions->_hoops_SGCAA[index],  1UL << offset))
						return true;
				}
			}
			if (_hoops_ARHCA->_hoops_GAHCA._hoops_PPICA.count > 0) {
				_hoops_PCACA const *	_hoops_ACPGR = conditions->_hoops_ACPGR;
				int const *					_hoops_GPICA = _hoops_ARHCA->_hoops_GAHCA._hoops_PPICA._hoops_GPICA;

				if (_hoops_ACPGR != null) do {
					for (int i=0; i<_hoops_ARHCA->_hoops_GAHCA._hoops_PPICA.count; i++) {
						if (_hoops_GPICA[i] == _hoops_ACPGR->type)
							return true;
					}
				} while ((_hoops_ACPGR = _hoops_ACPGR->next) != null);
			}
		}	break;

		case HK_CALLBACK: {
			if (_hoops_ARHCA->_hoops_GAHCA.callbacks.count > 0) {
				_hoops_GCHIR const *			_hoops_RCHIR = (_hoops_GCHIR const *)_hoops_ASGPR;
				_hoops_IHACR const *		_hoops_RCACR;
				int							_hoops_SAICA = _hoops_ARHCA->_hoops_GAHCA.callbacks.count;
				int const *					_hoops_GPICA = _hoops_ARHCA->_hoops_GAHCA.callbacks._hoops_GPICA;

				if ((_hoops_RCACR = _hoops_RCHIR->_hoops_ACHIR) != null) do {
					int						_hoops_RPICA = _hoops_RCACR->type;

					for (int i=0; i<_hoops_SAICA; i++)
						if (_hoops_RPICA == _hoops_GPICA[i])
							return true;
				} while ((_hoops_RCACR = _hoops_RCACR->next) != null);
			}
		}	break;

		case HK_STYLE: {
			Style const *			style = (Style const *)_hoops_ASGPR;

			if (BIT (_hoops_ARHCA->_hoops_GAHCA._hoops_IPHCA, _hoops_CPHCA) &&
				style->_hoops_IGRPR != null)
				return true;
			if (BIT (_hoops_ARHCA->_hoops_GAHCA._hoops_IPHCA, _hoops_SPHCA) &&
				style->_hoops_IGRPR == null)
				return true;
		}	break;

		case _hoops_IPAIR: {
			_hoops_CPAIR const *			_hoops_SPAIR = (_hoops_CPAIR const *)_hoops_ASGPR;

			for (int i = 0; i < _hoops_SPAIR->count; i++) {
				bool	_hoops_RSR = BIT (_hoops_SPAIR->textures[i]->_hoops_SCR, _hoops_GSR);

				if (BIT (_hoops_ARHCA->_hoops_GAHCA._hoops_RAHCA, _hoops_GPHCA) && _hoops_RSR)
					return true;
				if (BIT (_hoops_ARHCA->_hoops_GAHCA._hoops_RAHCA, _hoops_HPICA) && !_hoops_RSR)
					return true;
			}
		}	break;
	}

	return false;
}


local int _hoops_GHGHS (
	Geometry const *		geo,	/* _hoops_GHCA _hoops_SHH _hoops_GII _hoops_CPAP */
	_hoops_RRHCA *	_hoops_ARHCA) {
	int						count = 0;

	if ((_hoops_ARHCA->_hoops_AHHCA || _hoops_ARHCA->_hoops_CPICA) && geo->_hoops_IPPGR != null) {
		Attribute	*_hoops_ASGPR;

		_hoops_ASGPR = geo->_hoops_IPPGR;
		do {
			if (_hoops_ARHCA->_hoops_AHHCA || _hoops_ARHCA->_hoops_CHHCA[(int)_hoops_ASGPR->type] ||
				_hoops_SCHCA (_hoops_ARHCA, _hoops_ASGPR)) {
				++count;
				if (_hoops_ARHCA->_hoops_RCHCA)
					return count;
			}
		} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
	}

	if (_hoops_ARHCA->_hoops_PHICA) {
		_hoops_RPAPA * _hoops_APAPA = HOOPS_WORLD->_hoops_PPAPA->Lookup(geo);

		if (_hoops_APAPA != null) 
			count += _hoops_APAPA->Count();
	}

	if (_hoops_ARHCA->bounding) {
		switch (geo->type) {
			case _hoops_SCIP:
			case _hoops_GSIP: {
				Polyhedron const *			phon = (Polyhedron const *)geo;

				if (!phon->bounding._hoops_HICAR())
					++count;
			}	break;
			case _hoops_CSIP: {
				PolyCylinder const *		_hoops_HSPIR = (PolyCylinder const *)geo;

				if (!_hoops_HSPIR->bounding._hoops_HICAR())
					++count;
			}	break;
			case _hoops_AGCP: {
				_hoops_HACC const *				text = (_hoops_HACC const *)geo;

				if (!text->bounding._hoops_HICAR())
					++count;
			}	break;
			case _hoops_AHIP: {
				_hoops_PHIP const *	_hoops_RRA = (_hoops_PHIP const *)geo;

				if (!_hoops_RRA->bounding._hoops_HICAR())
					++count;
			}	break;
		}
	}

	if (_hoops_ARHCA->_hoops_AHHCA || _hoops_ARHCA->geometry_options) {
		if (geo->type == _hoops_IIIP) {
			Polyline const * pl = (Polyline const *)geo;
			if (pl->orientation)
				count++;
		}

		if (geo->type == _hoops_PCIP) {
			Marker const * _hoops_GPIIH = (Marker const *)geo;
			if (_hoops_GPIIH->orientation)
				count++;
		}

		if (geo->type == _hoops_ICIP) {
			if (BIT(((Light const *)geo)->flags, _hoops_RISGP))
				count++;
		}
	}

	if (geo->type == _hoops_CSIP) {
		PolyCylinder const *				_hoops_HSPIR = (PolyCylinder const *)geo;
		_hoops_AGHIR const *		_hoops_PGHIR;

		if ((_hoops_PGHIR = _hoops_HSPIR->_hoops_RGHIR) != null) {
			if (_hoops_ARHCA->_hoops_RGHIR._hoops_GCPPP)
				count += _hoops_PGHIR->_hoops_RCRHR +
				_hoops_PGHIR->_hoops_SIRHR;
			if (_hoops_ARHCA->_hoops_RGHIR._hoops_RCPPP)
				count += _hoops_PGHIR->_hoops_SCHPR +
				_hoops_PGHIR->_hoops_CCHPR;
		}

		if (_hoops_ARHCA->_hoops_RGHIR._hoops_PRHH) {
			if (BIT (_hoops_HSPIR->flags, _hoops_RSICA))
				++count;
			if (BIT (_hoops_HSPIR->flags, _hoops_ASICA))
				++count;
		}
	}
	else if (geo->type == _hoops_SCIP || geo->type == _hoops_GSIP) {
		Polyhedron const *		phon = (Polyhedron const *)geo;

		if (_hoops_ARHCA->_hoops_RIPPP ||
			_hoops_ARHCA->_hoops_CHHCA[(int)HK_FACE_PATTERN]) {
			Local_Face_Attributes const *		_hoops_CPRI =
							&phon->local_face_attributes;

			if (_hoops_ARHCA->_hoops_RGHIR._hoops_PAGI)
				count += _hoops_CPRI->_hoops_HSRRA +
						 _hoops_CPRI->_hoops_PSRRA;
			if (_hoops_ARHCA->_hoops_RGHIR._hoops_PRHH)
				count += _hoops_CPRI->explicit_normal_count;
			if (_hoops_ARHCA->_hoops_RGHIR.face_patterns || _hoops_ARHCA->_hoops_CHHCA[(int)HK_FACE_PATTERN])
				count += _hoops_CPRI->_hoops_SRAPA;
			if (_hoops_ARHCA->_hoops_RGHIR._hoops_AIPPP)
				count += _hoops_CPRI->_hoops_CPIAA +
						 _hoops_CPRI->_hoops_SIIPR;
		}
		if (_hoops_ARHCA->_hoops_PIPPP ||
			_hoops_ARHCA->_hoops_CHHCA[(int)HK_EDGE_PATTERN] ||
			_hoops_ARHCA->_hoops_CHHCA[(int)HK_EDGE_WEIGHT]) {
			_hoops_RPGHR const *		lea =
							&phon->_hoops_IHHPR;

			if (_hoops_ARHCA->_hoops_RGHIR._hoops_ASHA)
				count += lea->_hoops_HSRRA +
						 lea->_hoops_PSRRA;
			if (_hoops_ARHCA->_hoops_RGHIR._hoops_RSHA)
				count += lea->explicit_normal_count;
			if (_hoops_ARHCA->_hoops_RGHIR._hoops_HIPPP || _hoops_ARHCA->_hoops_CHHCA[(int)HK_EDGE_PATTERN])
				count += lea->_hoops_SRAPA;
			if (_hoops_ARHCA->_hoops_RGHIR._hoops_IIPPP || _hoops_ARHCA->_hoops_CHHCA[(int)HK_EDGE_WEIGHT])
				count += lea->_hoops_CCHHC;
			if (_hoops_ARHCA->_hoops_RGHIR._hoops_CIPPP)
				count += lea->_hoops_CPIAA +
						 lea->_hoops_SIIPR;
		}
		if (_hoops_ARHCA->any_vertex_attributes ||
			_hoops_ARHCA->_hoops_CHHCA[(int)HK_MARKER_SYMBOL] ||
			_hoops_ARHCA->_hoops_CHHCA[(int)HK_MARKER_SIZE]) {
			Local_Vertex_Attributes const *		_hoops_SPRI =
							&phon->local_vertex_attributes;

			if (_hoops_ARHCA->_hoops_SIPPP) {
				if (_hoops_ARHCA->_hoops_RGHIR._hoops_GCPPP)
					count += _hoops_SPRI->_hoops_RCRHR +
							 _hoops_SPRI->_hoops_SIRHR;

				if (_hoops_ARHCA->_hoops_RGHIR._hoops_RCPPP)
					count += _hoops_SPRI->_hoops_SCHPR +
							 _hoops_SPRI->_hoops_CCHPR;

				if (_hoops_ARHCA->_hoops_RGHIR._hoops_ACPPP)
					count += _hoops_SPRI->_hoops_ICRRA +
							 _hoops_SPRI->_hoops_PCRRA +
							 _hoops_SPRI->_hoops_HIRRA;
				else if (_hoops_ARHCA->_hoops_RGHIR._hoops_PCPPP)
					count += _hoops_SPRI->_hoops_HIRRA;
			}
			if (_hoops_ARHCA->_hoops_RGHIR._hoops_ICHA)
				count += _hoops_SPRI->explicit_normal_count;
			if (_hoops_ARHCA->_hoops_RGHIR._hoops_ACICA)
				count += _hoops_SPRI->_hoops_RSAPA;
			if (_hoops_ARHCA->_hoops_RGHIR._hoops_HCPPP || _hoops_ARHCA->_hoops_CHHCA[(int)HK_MARKER_SYMBOL])
				count += _hoops_SPRI->_hoops_AHIIC;
			if (_hoops_ARHCA->_hoops_RGHIR._hoops_ICPPP || _hoops_ARHCA->_hoops_CHHCA[(int)HK_MARKER_SIZE])
				count += _hoops_SPRI->_hoops_SCHHC;
			if (_hoops_ARHCA->_hoops_RGHIR._hoops_CCPPP)
				count += _hoops_SPRI->_hoops_CPIAA +
						 _hoops_SPRI->_hoops_SIIPR;
		}

		if (_hoops_ARHCA->_hoops_AHHCA || _hoops_ARHCA->_hoops_CHHCA[(int)_hoops_AGAIR]) {
			_hoops_PGAIR const *		_hoops_HGAIR;

			if ((_hoops_HGAIR = phon->_hoops_HGAIR) != null) {
				int				i;

				for (i=0; i<_hoops_IGAIR; i++)
					if (_hoops_HGAIR->data[i] != null)
						++count;
			}
		}
		if (_hoops_ARHCA->_hoops_AHHCA || _hoops_ARHCA->_hoops_CHHCA[(int)_hoops_HCIIR]) {
			Tristrip *ts = phon->tristrips;
			Polyedge *pe = phon->_hoops_SHGPR;
			Polymarker *pm = phon->_hoops_GIGPR;

			while (ts) {
				if (ts->_hoops_GAHA)
					++count;
				ts = ts->next;
			}
			while (pe) {
				if (pe->_hoops_GAHA)
					++count;
				pe = pe->next;
			}
			while (pm) {
				if (pm->_hoops_GAHA)
					++count;
				pm = pm->next;
			}
			pe = phon->_hoops_CHGPR;
			while (pe) {
				if (pe->_hoops_GAHA)
					++count;
				pe = pe->next;
			}
		}
	}

	return count;
}
#endif





HC_INTERFACE int HC_CDECL HC_Show_Existence_By_Key (
	Key						key,
	char const *			types)
{
	_hoops_PAPPR context("Show_Existence_By_Key");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
	return 0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Existence_By_Key () */\n");
	);

	char const *			_hoops_RPPA = types;
	_hoops_RRHCA		_hoops_ARHCA;
	int						result = 0;

	_hoops_CSPPR();
	_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)_hoops_RCSSR (context, key);

	if (_hoops_SRCP == null || BIT (_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR)) {
		while (*_hoops_RPPA == ' ')
			_hoops_RPPA++;
		if (_hoops_SHPCR(_hoops_RPPA[0]) == 's' &&
			_hoops_SHPCR(_hoops_RPPA[1]) == 'e' &&
			_hoops_SHPCR(_hoops_RPPA[2]) == 'l' &&
			_hoops_SHPCR(_hoops_RPPA[3]) == 'f') {
			/* '_hoops_HAHI' _hoops_HRGR _hoops_IRS _hoops_GHAR _hoops_RHGHS _hoops_RPP _hoops_SIC _hoops_SIAS _hoops_SHH _hoops_AIPH */
		}
		else {
			/* _hoops_PA _hoops_SHS _hoops_CGH _hoops_HS _hoops_RAICR _hoops_RH _hoops_SIC _hoops_SRS... */
			HE_ERROR (HEC_EXISTENCE, HES_INVALID_KEY, "Key does not refer to a valid entity");
		}
	}
	else if (_hoops_SRCP->type != _hoops_IRCP) {
		_hoops_HPAH *	thing = (_hoops_HPAH *)_hoops_SRCP;

		while (*_hoops_RPPA == ' ')
			_hoops_RPPA++;
		if (_hoops_SHPCR(_hoops_RPPA[0]) == 's' &&
			_hoops_SHPCR(_hoops_RPPA[1]) == 'e' &&
			_hoops_SHPCR(_hoops_RPPA[2]) == 'l' &&
			_hoops_SHPCR(_hoops_RPPA[3]) == 'f') {
			result = 1;
		}
		else if (_hoops_SHPCR(_hoops_RPPA[0]) == 'i' &&
				 _hoops_SHPCR(_hoops_RPPA[1]) == 'n' &&
				 _hoops_SHPCR(_hoops_RPPA[2]) == 't' &&
				 _hoops_SHPCR(_hoops_RPPA[3]) == 'e' &&
				 _hoops_SHPCR(_hoops_RPPA[4]) == 'r' &&
				 _hoops_SHPCR(_hoops_RPPA[5]) == 'e' &&
				 _hoops_SHPCR(_hoops_RPPA[6]) == 's' &&
				 _hoops_SHPCR(_hoops_RPPA[7]) == 't' &&
				 _hoops_SHPCR(_hoops_RPPA[8]) == 'i' &&
				 _hoops_SHPCR(_hoops_RPPA[9]) == 'n' &&
				 _hoops_SHPCR(_hoops_RPPA[10]) == 'g' &&
				 BIT (thing->_hoops_RRHH, _hoops_GGCCA)) {
				 result = 1;
		}
#if 0
		else if (_hoops_SHPCR(_hoops_RPPA[0]) == 'b' &&
				 _hoops_SHPCR(_hoops_RPPA[1]) == 'o' &&
				 _hoops_SHPCR(_hoops_RPPA[2]) == 'u' &&
				 _hoops_SHPCR(_hoops_RPPA[3]) == 'n' &&
				 _hoops_SHPCR(_hoops_RPPA[4]) == 'd' &&
				 _hoops_SHPCR(_hoops_RPPA[5]) == 'i' &&
				 _hoops_SHPCR(_hoops_RPPA[6]) == 'n' &&
				 _hoops_SHPCR(_hoops_RPPA[7]) == 'g' &&
				 BIT (thing->_hoops_RRHH, _hoops_GGSCA)) {
					result = 1;
		}
#endif
		else if (_hoops_AHRIR <= thing->type && thing->type <= _hoops_PHRIR &&
				 HI_Decipher_Type_Names (context, types, &_hoops_ARHCA)) {

			result = _hoops_GHGHS ((Geometry *)thing, &_hoops_ARHCA);

			HI_Clean_FCD (&_hoops_ARHCA);
		}
	}
	else {
		if (HI_Decipher_Type_Names (context, types, &_hoops_ARHCA)) {
			HI_Count_Contents (context, _hoops_SRCP, (void *)&_hoops_ARHCA);

			result = _hoops_ARHCA.item.count;

			HI_Clean_FCD (&_hoops_ARHCA);
		}
	}

	_hoops_IRRPR();
	return result;
#endif
}


HC_INTERFACE int HC_CDECL HC_QShow_Existence (
	char const *			segspec,
	char const *			types)
{
	_hoops_PAPPR context("QShow_Existence");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
	return 0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_QShow_Existence () */\n");
	);

	_hoops_RRHCA		_hoops_ARHCA;
	char const *			_hoops_SIIS = segspec;

	while (*_hoops_SIIS == ' ') ++_hoops_SIIS;
	if (*_hoops_SIIS == '.') {
		++_hoops_SIIS;
		while (*_hoops_SIIS == ' ') ++_hoops_SIIS;
	}
	if (*_hoops_SIIS == '\0') {
		int						tmp;

		/* _hoops_SGGC '.' - _hoops_RGR _hoops_GACC _hoops_AHGHS _hoops_IIGSH _hoops_CGSI _hoops_IHGS _hoops_IGS */

		PUSHNAME(context);
		tmp = HC_Show_Existence (types);
		POPNAME(context);
		return tmp;
	}

	if (!HI_Decipher_Type_Names (context, types, &_hoops_ARHCA))
		return 0;

	_hoops_CSPPR();
	/* _hoops_PIP: _hoops_CAGH _hoops_HRGR _hoops_HAR _hoops_RGHP _hoops_IS _hoops_GGCA _hoops_RPP _hoops_SR _hoops_CHR _hoops_ASAAI _hoops_RPP _hoops_SCH _hoops_HICP! */
	HI_For_Each (context, segspec, !_hoops_ARHCA._hoops_IPICA, HI_Count_Contents, (void *)&_hoops_ARHCA);
	_hoops_IRRPR();

	HI_Clean_FCD (&_hoops_ARHCA);

	return _hoops_ARHCA.item.count;
#endif
}

HC_INTERFACE int HC_CDECL HC_Show_Existence (
	char const *			types)
{
	_hoops_PAPPR context("Show_Existence");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Existence () */\n");
	);

	int	count = 0;

	if (context->open_list == null) {}
	else if (context->open_list->_hoops_GCRIR == _hoops_RCRIR) {
		_hoops_CRCP * _hoops_SRCP = context->open_list->info.segment._hoops_PCRIR;

		PUSHNAME(context);
		count = HC_Show_Existence_By_Key (_hoops_AIRIR (_hoops_SRCP), types);
		POPNAME(context);
	}
	else {
		_hoops_RRHCA	_hoops_ARHCA;

		if (!HI_Decipher_Type_Names (context, types, &_hoops_ARHCA))
			return 0;

		count = 0;

		if (_hoops_ARHCA._hoops_IPICA && context->open_list != null)
			++count;

		switch (context->open_list->_hoops_GCRIR) {
			/* _hoops_RGAR _hoops_GPIHR _hoops_GGR _hoops_SAGHR _hoops_CGSI */

		  case _hoops_RSRIR: {
			Polyhedron *	_hoops_IPRI = context->open_list->info._hoops_IPRI._hoops_IGRPR;
			int				offset = context->open_list->info._hoops_IPRI.offset;
			Geometry *		geo = null;

			if (offset == 0)
			   geo = (Geometry *)_hoops_IPRI;
			else if (offset > 0 && offset < _hoops_IGAIR)
			   geo = _hoops_IPRI->_hoops_HGAIR->data[offset-1];

#ifndef DISABLE_GEOMETRY_ATTRIBUTES
			if (geo != null)
				count += _hoops_GHGHS (geo, &_hoops_ARHCA);
#endif
		  }	  break;

		  case _hoops_HCRIR:	{
			Geometry *	geo = context->open_list->info.geometry._hoops_IGRPR;

			if (_hoops_ARHCA._hoops_SSICA && BIT (geo->_hoops_RRHH, _hoops_GGCCA))
				++count;

#ifndef DISABLE_GEOMETRY_ATTRIBUTES
			count += _hoops_GHGHS (geo, &_hoops_ARHCA);
#endif
		  }	  break;

#ifndef DISABLE_GEOMETRY_ATTRIBUTES
		  case _hoops_SCRIR: {
			  Polyhedron *		_hoops_IPRI;
			  int				offset;

			  _hoops_IPRI = context->open_list->info._hoops_IPRI._hoops_IGRPR;
			  offset = context->open_list->info._hoops_IPRI.offset;

			  if (_hoops_IPRI->type == _hoops_CSIP) {
				  PolyCylinder *		_hoops_HSPIR = (PolyCylinder *)_hoops_IPRI;
				  _hoops_AGHIR *_hoops_PGHIR;

#  ifndef _hoops_GCGHR
				  if ((_hoops_PGHIR = _hoops_HSPIR->_hoops_RGHIR) != null) {
					  _hoops_CGHIR		flags = _hoops_PGHIR->flags[offset];

					  if (_hoops_ARHCA._hoops_CHHCA[(int)HK_COLOR] &&
						  ANYBIT (flags, _hoops_GPPRA|
										 _hoops_RPPRA))
						  ++count;
					  else if (_hoops_ARHCA._hoops_SIPPP) {
						  if (_hoops_ARHCA._hoops_RGHIR._hoops_GCPPP &&
							  BIT (flags, _hoops_RPPRA))
							  ++count;
						  if (_hoops_ARHCA._hoops_RGHIR._hoops_RCPPP &&
							  BIT (flags, _hoops_GPPRA))
							  ++count;
					  }
				  }
#  endif
			  }
			  else {
				  Local_Vertex_Flags	flags;

				  flags = *(_hoops_IPRI->local_vertex_attributes._hoops_CHHPR(offset));

				  if (flags != 0) {
#  ifndef _hoops_IIICA
					  if ((_hoops_ARHCA._hoops_RGHIR._hoops_CCPPP ||
						   _hoops_ARHCA._hoops_CHHCA[(int)HK_VISIBILITY]) &&
						  ANYBIT (flags, _hoops_CIICA))
						  ++count;
#  endif

#  ifndef _hoops_GCGHR
					  if (_hoops_ARHCA._hoops_CHHCA[(int)HK_COLOR] &&
						  ANYBIT (flags, _hoops_APPRA|
										 _hoops_PPPRA|
										 _hoops_HPPRA))
						  ++count;
					  else if (_hoops_ARHCA._hoops_SIPPP) {
						  if (_hoops_ARHCA._hoops_RGHIR._hoops_GCPPP &&
							  BIT (flags, _hoops_HPPRA))
							  ++count;

						  if (_hoops_ARHCA._hoops_RGHIR._hoops_RCPPP &&
							  BIT (flags, _hoops_PPPRA))
							  ++count;

						  if (_hoops_ARHCA._hoops_RGHIR._hoops_ACPPP &&
							  BIT (flags, _hoops_APPRA))
							  ++count;
						  else if (_hoops_ARHCA._hoops_RGHIR._hoops_PCPPP &&
							  BIT (flags, _hoops_CCRRA))
							  ++count;
					  }
#  endif

#  ifndef _hoops_CSGHR
					  if ((_hoops_ARHCA._hoops_RGHIR._hoops_HCPPP ||
						   _hoops_ARHCA._hoops_CHHCA[(int)HK_MARKER_SYMBOL]) &&
						  BIT (flags, _hoops_SIICA))
						  ++count;
					  if ((_hoops_ARHCA._hoops_RGHIR._hoops_ICPPP ||
						   _hoops_ARHCA._hoops_CHHCA[(int)HK_MARKER_SIZE]) &&
						  BIT (flags, _hoops_GCICA))
						  ++count;
#  endif

#  ifndef _hoops_HCGHR
					  if ((_hoops_ARHCA._hoops_RGHIR._hoops_ICHA) &&
						  BIT (flags, LVA_EXPLICIT_NORMAL))
						  ++count;
#  endif

#  ifndef DISABLE_TEXTURING
					  if ((_hoops_ARHCA._hoops_RGHIR._hoops_ACICA) &&
						  BIT (flags, _hoops_ASAPA))
						  ++count;
#  endif
				  }
			  }
		  }	  break;

		  case _hoops_CCRIR: {
			  _hoops_GHHPR		flags;
			  Polyhedron			*_hoops_IPRI;
			  _hoops_GHHPR		*_hoops_HIICA;

			  _hoops_IPRI = context->open_list->info._hoops_IPRI._hoops_IGRPR;

			  if ((_hoops_HIICA = _hoops_IPRI->_hoops_IHHPR.flags) != null) {
				  flags = _hoops_HIICA[context->open_list->info._hoops_IPRI.offset];

#  ifndef _hoops_IIICA
				  if ((_hoops_ARHCA._hoops_RGHIR._hoops_CIPPP ||
					   _hoops_ARHCA._hoops_CHHCA[(int)HK_VISIBILITY]) &&
					  ANYBIT (flags, _hoops_ICICA))
					  ++count;
#  endif

#  ifndef _hoops_GCGHR
				  if ((_hoops_ARHCA._hoops_RGHIR._hoops_ASHA ||
					   _hoops_ARHCA._hoops_CHHCA[(int)HK_COLOR]) &&
					  ANYBIT (flags, _hoops_CCICA))
					  ++count;
#  endif

#  ifndef _hoops_RGIPR
				  if ((_hoops_ARHCA._hoops_RGHIR._hoops_HIPPP ||
					   _hoops_ARHCA._hoops_CHHCA[(int)HK_EDGE_PATTERN]) &&
					  BIT (flags, _hoops_GPGI))
					  ++count;

				  if ((_hoops_ARHCA._hoops_RGHIR._hoops_IIPPP ||
					   _hoops_ARHCA._hoops_CHHCA[(int)HK_EDGE_WEIGHT]) &&
					  BIT (flags, _hoops_SCICA))
					  ++count;
#  endif
			  }
		  }	  break;

			case _hoops_GSRIR: {
				_hoops_GIIPR		flags;
				Polyhedron			*_hoops_IPRI;
				int const				*regions;
				int						region;
				int						offset;

				_hoops_IPRI = context->open_list->info._hoops_IPRI._hoops_IGRPR;
				region	   = context->open_list->info._hoops_IPRI.offset;
				regions	   = _hoops_IPRI->local_face_attributes.regions;

				if (regions == null && region != 0)
					break;			/* _hoops_HCR _hoops_RSSI _hoops_GGR _hoops_SHIR _hoops_ISPH, _hoops_IAGC _hoops_GPGH'_hoops_RA */

				for (offset=0; offset<_hoops_IPRI->face_count; offset++) {
					if (_hoops_IPRI->local_face_attributes._hoops_CHHPR() != null &&
						(regions == null || regions[offset] == region)) {
						flags = *((Polyhedron*)_hoops_IPRI)->local_face_attributes._hoops_CHHPR(offset);

#  ifndef _hoops_IIICA
						if ((_hoops_ARHCA._hoops_RGHIR._hoops_AIPPP ||
							_hoops_ARHCA._hoops_CHHCA[(int)HK_VISIBILITY]) &&
							ANYBIT (flags, _hoops_HRAPA))
								++count;
#  endif

#  ifndef _hoops_GCGHR
						if ((_hoops_ARHCA._hoops_RGHIR._hoops_PAGI ||
							_hoops_ARHCA._hoops_CHHCA[(int)HK_COLOR]) &&
							ANYBIT (flags, _hoops_IACHR))
								++count;
#  endif

#  ifndef _hoops_PGPHR
						if ((_hoops_ARHCA._hoops_RGHIR.face_patterns ||
							_hoops_ARHCA._hoops_CHHCA[(int)HK_FACE_PATTERN]) &&
							BIT (flags, _hoops_HAGI))
								++count;
#  endif

#  ifndef _hoops_HCGHR
						if ((_hoops_ARHCA._hoops_RGHIR._hoops_PRHH) &&
							BIT (flags, LFA_EXPLICIT_NORMAL))
								++count;
#  endif
					}
				}
			}	break;

		  case _hoops_ICRIR: {
			  _hoops_GIIPR		flags;
			  Polyhedron			*_hoops_IPRI;

			  _hoops_IPRI = context->open_list->info._hoops_IPRI._hoops_IGRPR;

			  if (_hoops_IPRI->type == _hoops_CSIP) {
				  PolyCylinder *		_hoops_HSPIR = (PolyCylinder *)_hoops_IPRI;

#  ifndef _hoops_HCGHR
				  if (_hoops_ARHCA._hoops_RGHIR._hoops_ICHA) {
					int offset = context->open_list->info._hoops_IPRI.offset;

					if (offset == 0 && BIT (_hoops_HSPIR->flags, _hoops_RSICA))
						++count;
					else if (offset == 1 && BIT (_hoops_HSPIR->flags, _hoops_ASICA))
						++count;
				  }
#  endif
			  }
			  else {
				  _hoops_GIIPR		*_hoops_HIICA;

				  if ((_hoops_HIICA = _hoops_IPRI->local_face_attributes._hoops_CHHPR()) != null) {
					  flags = *(_hoops_IPRI->local_face_attributes._hoops_CHHPR(context->open_list->info._hoops_IPRI.offset));

#  ifndef _hoops_IIICA
					  if ((_hoops_ARHCA._hoops_RGHIR._hoops_AIPPP ||
						   _hoops_ARHCA._hoops_CHHCA[(int)HK_VISIBILITY]) &&
						  ANYBIT (flags, _hoops_HRAPA))
						  ++count;
#  endif

#  ifndef _hoops_GCGHR
					  if ((_hoops_ARHCA._hoops_RGHIR._hoops_PAGI ||
						   _hoops_ARHCA._hoops_CHHCA[(int)HK_COLOR]) &&
						  ANYBIT (flags, _hoops_IACHR))
						  ++count;
#  endif

#  ifndef _hoops_PGPHR
					  if ((_hoops_ARHCA._hoops_RGHIR.face_patterns ||
						   _hoops_ARHCA._hoops_CHHCA[(int)HK_FACE_PATTERN]) &&
						  BIT (flags, _hoops_HAGI))
						  ++count;
#  endif

#  ifndef _hoops_HCGHR
					  if ((_hoops_ARHCA._hoops_RGHIR._hoops_PRHH) &&
						  BIT (flags, LFA_EXPLICIT_NORMAL))
						  ++count;
#  endif
				}
			  }
		  }	  break;
#endif
		}

		if (_hoops_ARHCA._hoops_RCHCA && count != 0) count = 1; /* _hoops_PAIHR */

		HI_Clean_FCD (&_hoops_ARHCA);
	}

#endif

	return count;
}




HC_INTERFACE int HC_CDECL HC_Show_Existence_Unicode_By_K (
	Key						key,
	Karacter const *		types)
{
	_hoops_PAPPR context("Show_Existence_Unicode_By_Key");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
	return 0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Existence_Unicode_By_K () */\n");
	);

	int	count = 0;

	_hoops_CSPPR();
	_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)_hoops_RCSSR (context, key);

	if (_hoops_SRCP == null || BIT (_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR)) {
		/* _hoops_PA _hoops_SHS _hoops_CGH _hoops_HS _hoops_RAICR _hoops_RH _hoops_SIC _hoops_SRS... */
		HE_ERROR (HEC_EXISTENCE, HES_INVALID_KEY, "Key does not refer to a valid entity");
	}
	else if (_hoops_SRCP->type != _hoops_IRCP) {
		_hoops_HPAH *	thing = (_hoops_HPAH *)_hoops_SRCP;

		if (_hoops_AHRIR <= thing->type && thing->type <= _hoops_PHRIR) {
			_hoops_RRHCA	_hoops_ARHCA;

			if (HI_Decipher_Unicode_Type_Names (context, types, &_hoops_ARHCA)) {
				count = _hoops_GHGHS ((Geometry *)thing, &_hoops_ARHCA);
				HI_Clean_FCD (&_hoops_ARHCA);
			}
		}
	}
	else {
		_hoops_RRHCA		_hoops_ARHCA;
		if (HI_Decipher_Unicode_Type_Names (context, types, &_hoops_ARHCA)) {
			HI_Count_Contents (context, _hoops_SRCP, (void *)&_hoops_ARHCA);
			HI_Clean_FCD (&_hoops_ARHCA);
			count = _hoops_ARHCA.item.count;
		}
	}
	_hoops_IRRPR();

	return count;
#endif
}


HC_INTERFACE int HC_CDECL HC_QShow_Existence_Unicode (
	char const *			segspec,
	Karacter const *		types)
{
	_hoops_PAPPR context("QShow_Existence_Unicode");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
	return 0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_QShow_Existence_Unicode () */\n");
	);

	_hoops_RRHCA		_hoops_ARHCA;
	char const *			_hoops_SIIS = segspec;

	while (*_hoops_SIIS == ' ') ++_hoops_SIIS;
	if (*_hoops_SIIS == '.') {
		++_hoops_SIIS;
		while (*_hoops_SIIS == ' ') ++_hoops_SIIS;
	}
	if (*_hoops_SIIS == '\0') {
		int						tmp;

		/* _hoops_SGGC '.' - _hoops_RGR _hoops_GACC _hoops_AHGHS _hoops_IIGSH _hoops_CGSI _hoops_IHGS _hoops_IGS */

		PUSHNAME(context);
		tmp = HC_Show_Existence_Unicode (types);
		POPNAME(context);
		return tmp;
	}

	if (!HI_Decipher_Unicode_Type_Names (context, types, &_hoops_ARHCA))
		return 0;

	_hoops_CSPPR();
	/* _hoops_PIP: _hoops_CAGH _hoops_HRGR _hoops_HAR _hoops_RGHP _hoops_IS _hoops_GGCA _hoops_RPP _hoops_SR _hoops_CHR _hoops_ASAAI _hoops_RPP _hoops_SCH _hoops_HICP! */
	HI_For_Each (context, segspec, !_hoops_ARHCA._hoops_IPICA, HI_Count_Contents, (void *)&_hoops_ARHCA);
	_hoops_IRRPR();

	HI_Clean_FCD (&_hoops_ARHCA);

	return _hoops_ARHCA.item.count;
#endif
}

HC_INTERFACE int HC_CDECL HC_Show_Existence_Unicode (
	Karacter const *			types)
{
	_hoops_PAPPR context("Show_Existence_Unicode");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
	return 0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Existence_Unicode () */\n");
	);

	_hoops_CSPPR();

	int		count = 0;

	if (context->open_list == null) {}
	else if (context->open_list->_hoops_GCRIR == _hoops_RCRIR) {
		_hoops_CRCP *	_hoops_SRCP = context->open_list->info.segment._hoops_PCRIR;
		PUSHNAME(context);
		count = HC_Show_Existence_Unicode_By_K (_hoops_AIRIR (_hoops_SRCP), types);
		POPNAME(context);
	}
	else {
		_hoops_RRHCA	_hoops_ARHCA;

		if (HI_Decipher_Unicode_Type_Names (context, types, &_hoops_ARHCA)) {
			switch (context->open_list->_hoops_GCRIR) {
				/* _hoops_RGAR _hoops_GPIHR _hoops_GGR _hoops_SAGHR _hoops_CGSI */

				case _hoops_RSRIR: {
					Polyhedron *	_hoops_IPRI = context->open_list->info._hoops_IPRI._hoops_IGRPR;
					int				offset = context->open_list->info._hoops_IPRI.offset;
					Geometry *		geo = null;

					if (offset == 0)
					   geo = (Geometry *)_hoops_IPRI;
					else if (offset > 0 && offset < _hoops_IGAIR)
					   geo = _hoops_IPRI->_hoops_HGAIR->data[offset-1];

#ifndef DISABLE_GEOMETRY_ATTRIBUTES
					if (geo != null)
						count += _hoops_GHGHS (geo, &_hoops_ARHCA);
#endif
				}	break;

				case _hoops_HCRIR:	{
					Geometry *	geo = context->open_list->info.geometry._hoops_IGRPR;

#ifndef DISABLE_GEOMETRY_ATTRIBUTES
				count += _hoops_GHGHS (geo, &_hoops_ARHCA);
#endif
				}	break;
			}

			if (_hoops_ARHCA._hoops_RCHCA && count != 0) count = 1; /* _hoops_PAIHR */

			HI_Clean_FCD (&_hoops_ARHCA);
		}
	}
	_hoops_IRRPR();

	return count;
#endif
}

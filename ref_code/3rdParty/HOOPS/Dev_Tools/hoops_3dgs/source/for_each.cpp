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
 * $Id: obf_tmp.txt 1.86 2010-12-06 22:05:40 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "path.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "adt.h"


struct _hoops_ISGHH {
	_hoops_ISGHH *	next;
	_hoops_CRCP *		_hoops_SRCP;
};

struct _hoops_CSGHH {
	_hoops_CSGHH *	prev;
	_hoops_RSAPR *	_hoops_CIPPR;
};


local void _hoops_SSGHH (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_AAPHP *		_hoops_GGRHH,
	_hoops_RSAPR const *		_hoops_CIPPR,
	_hoops_CSGHH *			_hoops_RCSHR,
	_hoops_CRCP *				_hoops_SRCP,
	_hoops_ISGHH **			_hoops_AAIIA);


local void _hoops_RGRHH (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_AAPHP *		_hoops_GGRHH,
	_hoops_RSAPR const *		_hoops_CIPPR,
	_hoops_CSGHH *			_hoops_RCSHR,
	_hoops_CRCP *				_hoops_SRCP,
	int						offset,
	bool					_hoops_AGRHH,
	_hoops_ISGHH **			_hoops_AAIIA) 
{
	_hoops_RSAPR				_hoops_SIASA;

	/* _hoops_PSSP _hoops_AAGPH _hoops_GIAA _hoops_RH _hoops_RAGA _hoops_CAGH'_hoops_GRI _hoops_RSIRR */

	_hoops_PCCAR {
		switch (_hoops_CIPPR->type) {
			case _hoops_PGPPR:
			case _hoops_HGPPR:
			case _hoops_IGPPR:
			case _hoops_CGPPR: {
				/*** _hoops_RCASA: _hoops_SAHR _hoops_ACASA _hoops_RH _hoops_AAS _hoops_HIGR ***/

				_hoops_SIASA.next = null;
				_hoops_CIPPR = &_hoops_SIASA;
			}	break;

			case _hoops_CSAPR:
			case _hoops_HSAPR:
			case _hoops_PGRHH: {
				if (_hoops_AGRHH || offset == _hoops_SRCP->name.length)
					_hoops_SSGHH (_hoops_RIGC, _hoops_GGRHH, _hoops_CIPPR, _hoops_RCSHR, _hoops_SRCP, _hoops_AAIIA);

				return;
			}	/*_hoops_IHSA;*/

			case _hoops_PRPPR: {
				_hoops_AGRHH = true;
			}	break;

			case _hoops_SSAPR: {
				if (_hoops_SRCP->name.length == offset)
					return;
				else
					++offset;
			}	break;

			case _hoops_ARPPR: {
				if (_hoops_CIPPR->_hoops_AGPPR.length + offset > _hoops_SRCP->name.length)
					return;
				else {
					char			*a, *b;
					int				length;

					if (!_hoops_AGRHH) {
						a = _hoops_SRCP->name.text + offset;
						b = _hoops_CIPPR->_hoops_AGPPR.text;
						length = _hoops_CIPPR->_hoops_AGPPR.length;

						do
							if (*a++ != *b++)
								return;
						_hoops_RGGA (--length == 0);

						offset += _hoops_CIPPR->_hoops_AGPPR.length;
					}
					else if (_hoops_CIPPR->next == null) {
						offset = _hoops_SRCP->name.length - _hoops_CIPPR->_hoops_AGPPR.length;

						a = _hoops_SRCP->name.text + offset;
						b = _hoops_CIPPR->_hoops_AGPPR.text;
						length = _hoops_CIPPR->_hoops_AGPPR.length;

						do
							if (*a++ != *b++)
								return;
						_hoops_RGGA (--length == 0);

						/* _hoops_HGRHH = _hoops_RCPP; */
						/* _hoops_SHI += _hoops_SPGPH->_hoops_AAGPH._hoops_SPCC; */
					}
					else {
						do {
							a = _hoops_SRCP->name.text + offset;
							b = _hoops_CIPPR->_hoops_AGPPR.text;
							length = _hoops_CIPPR->_hoops_AGPPR.length;

							while (*a++ == *b++) if (--length == 0) {
								_hoops_RGRHH (_hoops_RIGC, _hoops_GGRHH, _hoops_CIPPR->next, _hoops_RCSHR, _hoops_SRCP, offset + _hoops_CIPPR->_hoops_AGPPR.length, false, _hoops_AAIIA);
								break;
							}
						} _hoops_RGGA (++offset > _hoops_SRCP->name.length - _hoops_CIPPR->_hoops_AGPPR.length);

						return;
					}
				}
			}	break;

			case _hoops_SGPPR: {
				int						_hoops_SIPPR = 0;
				_hoops_RSAPR const		*_hoops_IGRHH = _hoops_CIPPR;

				/* _hoops_SSS _hoops_PIS _hoops_RPHR _hoops_RGGR (_hoops_RPP _hoops_GII) */

				_hoops_PCCAR {
					if ((_hoops_CIPPR = _hoops_CIPPR->next) == null) {
						/* _hoops_SR _hoops_CHR _hoops_HPGR _hoops_CGRHH _hoops_PAPA, _hoops_PPR _hoops_IHGRH _hoops_IHCS
						 * _hoops_PSAP _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_HIGR _hoops_SIHH _hoops_IRS _hoops_PIS ')'. */

						local const		_hoops_RSAPR	_hoops_SGRHH = {null, _hoops_RRPPR};

						/* _hoops_GRRHH _hoops_RH _hoops_SCGR _hoops_PHHIP _hoops_CIAA _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_HIGR */

						_hoops_RGRHH (_hoops_RIGC, _hoops_GGRHH, &_hoops_SGRHH, _hoops_RCSHR, _hoops_SRCP, offset, _hoops_AGRHH, _hoops_AAIIA);

						if (_hoops_IGRHH->next == null) /* _hoops_SRPC _hoops_IGRSP */
							return;

						/* _hoops_HSPP _hoops_IAPR */
						_hoops_SSGHH (_hoops_RIGC, _hoops_GGRHH, _hoops_IGRHH->next, _hoops_RCSHR, null, _hoops_AAIIA);
						return;
					}

					if (_hoops_CIPPR->type == _hoops_GRPPR)
						++_hoops_SIPPR;
					else if (_hoops_CIPPR->type == _hoops_RRPPR)
						if (--_hoops_SIPPR < 0)
							break;
				}
			}	break;

			case _hoops_RRPPR: {
			}	break;

			case _hoops_GRPPR: {
				_hoops_PCCAR {
					int				_hoops_SIPPR = 0;

					_hoops_CIPPR = _hoops_CIPPR->next;
					_hoops_RGRHH (_hoops_RIGC, _hoops_GGRHH, _hoops_CIPPR, _hoops_RCSHR, _hoops_SRCP, offset, _hoops_AGRHH, _hoops_AAIIA);

					_hoops_RGGA (_hoops_CIPPR->type == _hoops_SGPPR && _hoops_SIPPR == 0) {
						if (_hoops_CIPPR->type == _hoops_GRPPR)
							++_hoops_SIPPR;
						else if (_hoops_CIPPR->type == _hoops_RRPPR)
							if (--_hoops_SIPPR < 0)
								return;

						_hoops_CIPPR = _hoops_CIPPR->next;
					}
				}
			}	/*_hoops_IHSA;*/

			default: {
				_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Somethin' bad in 'do_letters'");
				return;
			}	/* _hoops_IHSA; */
		}

		if ((_hoops_CIPPR = _hoops_CIPPR->next) == null) {
			if (_hoops_RCSHR == null)
				break;
			_hoops_CIPPR = _hoops_RCSHR->_hoops_CIPPR;
			_hoops_RCSHR = _hoops_RCSHR->prev;
		}
	}

	/* _hoops_SGPSA _hoops_GGSR _hoops_IIGR _hoops_GRPSA - _hoops_PIHA _hoops_SHH _hoops_IIH! */

	if (_hoops_AGRHH || _hoops_SRCP->name.length == offset) {
		if (_hoops_GGRHH->LookupItem(_hoops_SRCP) != VHASH_STATUS_SUCCESS) {
			_hoops_ISGHH	*_hoops_RRRHH;

			ALLOC (_hoops_RRRHH, _hoops_ISGHH);
			_hoops_RRRHH->_hoops_SRCP = _hoops_SRCP;
			_hoops_PRRH (_hoops_SRCP);
			_hoops_GGRHH->InsertItem(_hoops_SRCP);
			(*_hoops_AAIIA)->next = _hoops_RRRHH;
			*_hoops_AAIIA = _hoops_RRRHH;
		}
	}
}


local void _hoops_SSGHH (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_AAPHP *		_hoops_GGRHH,
	_hoops_RSAPR const *		_hoops_CIPPR,
	_hoops_CSGHH *			_hoops_RCSHR,
	_hoops_CRCP *				_hoops_SRCP,
	_hoops_ISGHH **			_hoops_AAIIA) {
	_hoops_RSAPR				_hoops_SIASA;

	/* _hoops_PSSP _hoops_SGHC _hoops_GIAA _hoops_RH _hoops_RAGA _hoops_CAGH */

	_hoops_PCCAR {	/* _hoops_GAR _hoops_RGRRR _hoops_GAR _hoops_SR _hoops_HS _hoops_GRPSA (_hoops_CACH _hoops_PRPC _hoops_IIGR _hoops_HAPR) */
		switch (_hoops_CIPPR->type) {
			case _hoops_PGPPR:
			case _hoops_HGPPR:
			case _hoops_IGPPR:
			case _hoops_CGPPR: {
				/*** _hoops_RCASA: _hoops_SAHR _hoops_ACASA _hoops_RH _hoops_AAS _hoops_HIGR ***/

				_hoops_SIASA.next = null;
				_hoops_CIPPR = &_hoops_SIASA;
			}	break;

			case _hoops_ISAPR: {
				_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_PCRIR;
			}	break;

			case _hoops_RGPPR: {
				if (_hoops_CIPPR->next == null) {
					/* _hoops_SAHR _hoops_AASH _hoops_GIRP */

					_hoops_SIASA.next = _hoops_CIPPR->expansion;
					_hoops_CIPPR = &_hoops_SIASA;
				}
				else {
					/* _hoops_SCH'_hoops_GRI _hoops_ACIPR _hoops_IS _hoops_CRGS _hoops_CGPR _hoops_RGR _hoops_CCAH _hoops_CCHHR _hoops_HIGR _hoops_RARP
					 * _hoops_CGH _hoops_SHH _hoops_PGHPR. _hoops_PHGP _hoops_PAIHR: _hoops_CCPP _hoops_SCH _hoops_GPP _hoops_RH _hoops_SPRS,
					 * _hoops_GHHA, _hoops_PPR _hoops_PGICR _hoops_ASRC. _hoops_PCASA _hoops_HCASA!
					 */

					_hoops_CSGHH			_hoops_ICASA;

					_hoops_ICASA.prev = _hoops_RCSHR;
					_hoops_ICASA._hoops_CIPPR = _hoops_CIPPR->next;
					_hoops_SSGHH(_hoops_RIGC, _hoops_GGRHH, _hoops_CIPPR->expansion, &_hoops_ICASA, _hoops_SRCP, _hoops_AAIIA);
					return;
				}
			}	break;

			case _hoops_CSAPR: {
				if (_hoops_SRCP == null) {
					if ((_hoops_SRCP = HOOPS_WORLD->root) == null) /* _hoops_PSP _hoops_PSSP (_hoops_PSP _hoops_SRRPR!) */
						return;
				}
			}	break;

			case _hoops_GGPPR: {
				if (_hoops_SRCP == null)
					_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_PCRIR;

				_hoops_SRCP = _hoops_SRCP->owner;
			}	break;

			case _hoops_HRPPR: {
				_hoops_SRCP = (_hoops_CRCP *)_hoops_SISIR (_hoops_RIGC, _hoops_CIPPR->key, _hoops_SRCP);

				if (_hoops_SRCP == null || _hoops_SRCP->type != _hoops_IRCP ||
					BIT (_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR)) return;	/* _hoops_ARRHH */
			}	break;

			case _hoops_SGPPR: {
				int						_hoops_SIPPR = 0;
				_hoops_RSAPR const		*_hoops_IGRHH = _hoops_CIPPR;

				/* _hoops_SSS _hoops_PIS _hoops_RPHR _hoops_RGGR, _hoops_RPP _hoops_GII */

				_hoops_PCCAR {
					if ((_hoops_CIPPR = _hoops_CIPPR->next) == null) {
						/* _hoops_SR _hoops_CHR _hoops_HPGR _hoops_CGRHH _hoops_PAPA, _hoops_PPR _hoops_IHGRH _hoops_IHCS
						 * _hoops_PSAP _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_HIGR _hoops_SIHH _hoops_IRS _hoops_PIS ')'.
						 */

						local const		_hoops_RSAPR	_hoops_SGRHH = {null, _hoops_RRPPR};

						/* _hoops_GRRHH _hoops_RH _hoops_SCGR _hoops_PHHIP _hoops_CIAA _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_HIGR */

						_hoops_SSGHH (_hoops_RIGC, _hoops_GGRHH, &_hoops_SGRHH, _hoops_RCSHR, _hoops_SRCP, _hoops_AAIIA);

						/* _hoops_PRRHH _hoops_IS _hoops_HSPP _hoops_IAPR */

						_hoops_SRCP = null;
						_hoops_CIPPR = _hoops_IGRHH;
						break;
					}

					if (_hoops_CIPPR->type == _hoops_GRPPR)
						++_hoops_SIPPR;
					else if (_hoops_CIPPR->type == _hoops_RRPPR)
						if (--_hoops_SIPPR < 0)
							break;
				}
			}	break;

			case _hoops_RRPPR: {
			}	break;

			case _hoops_GRPPR: {
				_hoops_PCCAR {
					int				_hoops_SIPPR = 0;

					_hoops_CIPPR = _hoops_CIPPR->next;
					_hoops_SSGHH (_hoops_RIGC, _hoops_GGRHH, _hoops_CIPPR, _hoops_RCSHR, _hoops_SRCP, _hoops_AAIIA);

					_hoops_RGGA (_hoops_CIPPR->type == _hoops_SGPPR && _hoops_SIPPR == 0) {
						if (_hoops_CIPPR->type == _hoops_GRPPR)
							++_hoops_SIPPR;
						else if (_hoops_CIPPR->type == _hoops_RRPPR)
							if (--_hoops_SIPPR < 0)
								return;

						_hoops_CIPPR = _hoops_CIPPR->next;
					}
				}
			}	_hoops_HHHI;

			case _hoops_ARPPR: if (_hoops_CIPPR->type == _hoops_ARPPR) {	/* _hoops_ISPR _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_HRRHH _hoops_HII _hoops_ARRS */
				if (_hoops_CIPPR->next == null ||				/* _hoops_AAGPH _hoops_CCA _hoops_PSP _hoops_IRRHH? */
					(_hoops_CIPPR->next->type != _hoops_PRPPR &&
					 _hoops_CIPPR->next->type != _hoops_SSAPR &&
					 _hoops_CIPPR->next->type != _hoops_HSAPR &&
					 _hoops_CIPPR->next->type != _hoops_PGRHH)) {
					 /*  _hoops_SR _hoops_PAH _hoops_AA _hoops_IRS _hoops_ICSI _hoops_HIIA (_hoops_PAR _hoops_ASGGR _hoops_SPR _hoops_RPP _hoops_HIGR _hoops_HRGR _hoops_RGRRR) */
					if (_hoops_SRCP == null)
						_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_PCRIR;

					if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) {}
					else if (HI_Fast_Lookup_Available (_hoops_SRCP, false)) {
						_hoops_CRCP *		_hoops_GIPIA;

						LOCK_MUTEX (HOOPS_WORLD->_hoops_RSASA);
						_hoops_GIPIA = HI_Find_Fast_Lookup_Segment (_hoops_SRCP, _hoops_CIPPR->_hoops_AGPPR.text);
						UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RSASA);

						if (_hoops_GIPIA != null)
							_hoops_RGRHH (_hoops_RIGC, _hoops_GGRHH, _hoops_CIPPR, _hoops_RCSHR, _hoops_GIPIA, 0, false, _hoops_AAIIA);
					}
					else {
						Subsegment *	_hoops_SSGPR;
						int				_hoops_SCASA = 0;

						if ((_hoops_SSGPR = _hoops_SRCP->_hoops_RGRPR) != null) do {
							if (_hoops_SSGPR->type >= _hoops_IRCP) {
								if (_hoops_SSGPR->type > _hoops_IRCP) {
									if (!BIT(_hoops_SRCP->_hoops_PHSI, _hoops_GGPSA))
										break;
								}
								else {
									_hoops_CRCP *		test = (_hoops_CRCP *)_hoops_SSGPR;

									if (_hoops_RAHSR (test->name, _hoops_CIPPR->_hoops_AGPPR)) {
										_hoops_RGRHH (_hoops_RIGC, _hoops_GGRHH, _hoops_CIPPR, _hoops_RCSHR, test, 0, false, _hoops_AAIIA);
										break;
									}
								}
							}
							++_hoops_SCASA;
						} while ((_hoops_SSGPR = _hoops_SSGPR->next) != null);

						if (_hoops_SCASA > 128 && !BIT (HOOPS_WORLD->_hoops_IRARR, _hoops_IGPSA)) {
							LOCK_MUTEX (HOOPS_WORLD->_hoops_RSASA);
							HI_Create_Fast_Lookup (_hoops_SRCP, false);
							UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RSASA);
						}
					}

					return;
				}
			}	_hoops_HHHI;

			case _hoops_PRPPR:
			case _hoops_SSAPR:
			case _hoops_HSAPR:
			case _hoops_PGRHH: {
				Subsegment	*_hoops_SSGPR;

				if (_hoops_SRCP == null)
					_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_PCRIR;

				if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR) &&
					(_hoops_SSGPR = _hoops_SRCP->_hoops_RGRPR) != null) {
					do if (!BIT (_hoops_SSGPR->_hoops_RRHH, _hoops_HGAGR)) {
						if (_hoops_SSGPR->type == _hoops_AGRPR) {
							if (_hoops_CIPPR->type == _hoops_PGRHH) {
								_hoops_PGRPR *		include = (_hoops_PGRPR *)_hoops_SSGPR;

								_hoops_SSGHH (_hoops_RIGC, _hoops_GGRHH, _hoops_CIPPR, _hoops_RCSHR, (_hoops_CRCP alter *)include->_hoops_IGRPR, _hoops_AAIIA);
							}
						}
						else if (_hoops_CIPPR->type == _hoops_HSAPR || _hoops_CIPPR->type == _hoops_PGRHH)
							_hoops_SSGHH (_hoops_RIGC, _hoops_GGRHH, _hoops_CIPPR, _hoops_RCSHR, (_hoops_CRCP *)_hoops_SSGPR, _hoops_AAIIA);
						else
							_hoops_RGRHH (_hoops_RIGC, _hoops_GGRHH, _hoops_CIPPR, _hoops_RCSHR, (_hoops_CRCP *)_hoops_SSGPR, 0, false, _hoops_AAIIA);
					} while ((_hoops_SSGPR = _hoops_SSGPR->next) != null);
				}

				if (_hoops_CIPPR->type != _hoops_HSAPR && _hoops_CIPPR->type != _hoops_PGRHH)
					return;
			}	break;

			default: {
				_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Somethin' bad in 'do_segments'");
			}	break;
		}

		if ((_hoops_CIPPR = _hoops_CIPPR->next) == null) {
			if (_hoops_RCSHR == null)
				break;
			_hoops_CIPPR = _hoops_RCSHR->_hoops_CIPPR;
			_hoops_RCSHR = _hoops_RCSHR->prev;
		}
	}

	/* _hoops_SGPSA _hoops_GGSR _hoops_IIGR _hoops_GRPSA - _hoops_PIHA _hoops_SHH _hoops_IIH! */

	if (_hoops_GGRHH->LookupItem(_hoops_SRCP) != VHASH_STATUS_SUCCESS) {
		_hoops_ISGHH *	_hoops_RRRHH;

		ALLOC (_hoops_RRRHH, _hoops_ISGHH);
		_hoops_RRRHH->_hoops_SRCP = _hoops_SRCP;
		_hoops_PRRH (_hoops_SRCP);
		_hoops_GGRHH->InsertItem(_hoops_SRCP);
		(*_hoops_AAIIA)->next = _hoops_RRRHH;
		*_hoops_AAIIA = _hoops_RRRHH;
	}
}



GLOBAL_FUNCTION void HI_For_Each (
	_hoops_AIGPR *		_hoops_RIGC,
	char const *				spec,
	bool						required,
	_hoops_CRRHH		action,
	void *						param) 
{
	_hoops_RSAPR *				path;
	_hoops_ISGHH				_hoops_GGHPR;
	_hoops_ISGHH *				_hoops_SSAC;
	char const *				_hoops_SAPSA = spec;
	_hoops_CRCP *					_hoops_SRRHH = null;


	/* _hoops_GRH _hoops_AGIR "." && "^"	(_hoops_ASSP'_hoops_RA _hoops_HIISR _hoops_CCA _hoops_GRCIR _hoops_HGS) */
	if (_hoops_RIGC->open_list != null && _hoops_RIGC->open_list->_hoops_GCRIR == _hoops_RCRIR) {
		_hoops_CRCP *	_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_PCRIR;

		if (spec[0] == '.'	&&	spec[1] == '\0') {
			(*action)(_hoops_RIGC, _hoops_SRCP, param);
			return;
		}
		if (_hoops_SRCP->owner->type != _hoops_PRAIR  &&
			((spec[0] == '^'  &&  spec[1] == '\0') ||
			 (spec[0] == '.'  &&  spec[1] == '.'  &&  spec[2] == '\0'))) {
			(*action)(_hoops_RIGC, _hoops_SRCP->owner, param);
			return;
		}

		if (!_hoops_GPPSA(_hoops_SAPSA, 3, "...")) {
			_hoops_SRRHH = _hoops_RIGC->open_list->info.segment._hoops_IGRPR;

			while (_hoops_GPPSA(_hoops_SAPSA, 3, "../")) {
				_hoops_SAPSA += 3;
				_hoops_SRRHH = _hoops_SRRHH->owner;
				if (_hoops_SRRHH == HOOPS_WORLD->root)
					break;
			}

			_hoops_SPAGR					_hoops_GHAGR (_hoops_SRRHH->_hoops_RHAGR, _hoops_RIGC->thread_id);
			_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRRHH);
			_hoops_CRPSA *	_hoops_HGIIR = _hoops_CSC->_hoops_SRPSA();

			if (_hoops_HGIIR != null) {
				vhash_status_t		result = _hoops_HGIIR->LookupItem(_hoops_SAPSA, &_hoops_SRCP);

				if (result == VHASH_STATUS_SUCCESS) {
#if 0
					if (BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR)) {
						_hoops_HPRH(_hoops_SRCP);
						_hoops_HGIIR->RemoveItem(_hoops_SAPSA, &_hoops_SRCP);
					}
					else
#endif
					{
						(*action)(_hoops_RIGC, _hoops_SRCP, param);
						HI_Record_Recent_Seg_Path (_hoops_RIGC, _hoops_SRRHH);
						return;
					}
				}
			}
		}
	}

	/* _hoops_GRH _hoops_AGIR _hoops_IHGP "@_hoops_SIC" _hoops_CAGH */
	if (spec[0] == '@') {
		Key				key = 0;
		char const		*_hoops_RPPA = spec;

		if (_hoops_RPPA[1] != '\0') _hoops_PCCAR {
			int				inc;

			switch (*++_hoops_RPPA) {
				case '0':				inc = 0x0;		break;
				case '1':				inc = 0x1;		break;
				case '2':				inc = 0x2;		break;
				case '3':				inc = 0x3;		break;
				case '4':				inc = 0x4;		break;
				case '5':				inc = 0x5;		break;
				case '6':				inc = 0x6;		break;
				case '7':				inc = 0x7;		break;
				case '8':				inc = 0x8;		break;
				case '9':				inc = 0x9;		break;
				case 'A': case 'a':		inc = 0xA;		break;
				case 'B': case 'b':		inc = 0xB;		break;
				case 'C': case 'c':		inc = 0xC;		break;
				case 'D': case 'd':		inc = 0xD;		break;
				case 'E': case 'e':		inc = 0xE;		break;
				case 'F': case 'f':		inc = 0xF;		break;
				default:				inc = -1;		break;

				case '\0': {
					_hoops_CRCP *		_hoops_SRCP;

					_hoops_SRCP = (_hoops_CRCP *)_hoops_RCSSR (_hoops_RIGC, key);
					if (_hoops_SRCP == null || _hoops_SRCP->type != _hoops_IRCP ||
						BIT (_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR)) {
						if (required)
							HE_ERROR (HEC_SEGMENT, HES_INVALID_REFERENCE,
									  Sprintf_S (null,"'%s' reference does not point to a valid segment", spec));
					}
					else
						(*action)(_hoops_RIGC, _hoops_SRCP, param);
				}	return;
			}

			if (inc < 0)
				break;

			key <<= 4;
			key += inc;
		}
	}


	if ((path = HI_Parse_Path (_hoops_RIGC, spec, _hoops_RPPSA|_hoops_AIPPR|QUALIFIERS)) == null) {
		/* _hoops_RIHH (_hoops_AIAH _hoops_CRPPR) - _hoops_AHCI _hoops_RSIRR */
		return;
	}


	_hoops_AAPHP *	_hoops_GGRHH = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_AAPHP)(_hoops_RIGC->memory_pool, _hoops_PAPHP);

	_hoops_SSAC = &_hoops_GGHPR;
	_hoops_SSGHH (_hoops_RIGC, _hoops_GGRHH, path, null, null, &_hoops_SSAC);
	_hoops_SSAC->next = null;

	delete _hoops_GGRHH;

	if (_hoops_SRRHH && !path->_hoops_GARHH && _hoops_GGHPR.next != null && _hoops_GGHPR.next->next == null) {
		_hoops_SPAGR					_hoops_GHAGR (_hoops_SRRHH->_hoops_RHAGR, _hoops_RIGC->thread_id);
		_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRRHH);
		_hoops_CRPSA *	_hoops_HGIIR = _hoops_CSC->_hoops_SRPSA();

		if (_hoops_HGIIR == null) {
			_hoops_HGIIR = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_CRPSA)(HOOPS_WORLD->memory_pool, 1);
			_hoops_CSC->_hoops_GAPSA (_hoops_HGIIR);
		}
		_hoops_HGIIR->InsertItem(_hoops_SAPSA, _hoops_GGHPR.next->_hoops_SRCP);

		HI_Record_Recent_Seg_Path (_hoops_RIGC, _hoops_SRRHH);
	}

	if (_hoops_GGHPR.next == null) {
		if (required) {
			HE_ERROR (HEC_SEGMENT, HES_NONE_FOUND,
					  Sprintf_S (null, "No segments named '%s' were found", spec));
		}
	}
	else {
		_hoops_ISGHH *	_hoops_RRRHH;
		_hoops_ISGHH *	_hoops_RARHH;

		_hoops_RRRHH = _hoops_GGHPR.next;

		do {
			_hoops_CRCP *		_hoops_SRCP = _hoops_RRRHH->_hoops_SRCP;

			(*action)(_hoops_RIGC, _hoops_SRCP, param);

			_hoops_HPRH (_hoops_SRCP);
			_hoops_RARHH = _hoops_RRRHH->next;
			FREE (_hoops_RRRHH, _hoops_ISGHH);
		} while ((_hoops_RRRHH = _hoops_RARHH) != null);
	}

	HI_Free_Path (path);
}

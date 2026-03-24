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
 * $Id: obf_tmp.txt 1.102 2010-12-06 22:05:40 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "adt.h"



typedef VHash<_hoops_CRCP const *, int> _hoops_CSGHP;

GLOBAL_FUNCTION void HI_Delete_By_Keys (
	_hoops_AIGPR *	_hoops_RIGC,
	int						count,
	Key const *				keys) 
{
	_hoops_CSGHP *		_hoops_SSGHP = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_CSGHP)(_hoops_RIGC->memory_pool);

	for (int i = 0; i < count; i++) {
		int				offset;
		_hoops_HPAH *		_hoops_CISIR = (_hoops_HPAH *)_hoops_SISIR (_hoops_RIGC, keys[i], &offset);

		if (BIT (_hoops_CISIR->_hoops_RRHH, _hoops_HGAGR)) {}
		else if (_hoops_CISIR->type == _hoops_IRCP) {
			HI_Delete_Segment (_hoops_RIGC, (_hoops_CRCP *)_hoops_CISIR, null);
		}
		else if (_hoops_CISIR->type == _hoops_HCIIR) {
			_hoops_GACR * dl = (_hoops_GACR *)_hoops_CISIR;
			_hoops_CIGPR (_hoops_RIGC,dl);
			_hoops_HPRH(dl);
		}
		else if (_hoops_CISIR->owner == null) {
			HI_Not_When_LOD ();
		}
		else {
			_hoops_CRCP				*owner = (_hoops_CRCP *)_hoops_CISIR->owner;
			int					_hoops_GGRHP = 0;
			int					_hoops_HPPS;

			while (owner->type != _hoops_IRCP)
				owner = owner->owner;

			if (_hoops_CISIR->type >= _hoops_AHRIR && _hoops_CISIR->type <= _hoops_PHRIR) {
				if (BIT (_hoops_CISIR->_hoops_RRHH, _hoops_CHRIR) &&
					keys[i] != _hoops_AIRIR(_hoops_CISIR)) {		// _hoops_SRSIR _hoops_PPR _hoops_GASIR _hoops_GPP _hoops_RH _hoops_CCAH _hoops_RASIR
					if (_hoops_CISIR->type == _hoops_HIIP)
						_hoops_CISIR = (_hoops_HPAH *)HI_Isolate_Line_From_Multiline (_hoops_RIGC, (_hoops_SHRIR *)_hoops_CISIR, offset);
					else if (_hoops_CISIR->type == _hoops_PIRS)
						_hoops_CISIR = (_hoops_HPAH *)HI_Isolate_Marker_From_Multimarker (_hoops_RIGC, (_hoops_GRPGR *)_hoops_CISIR, offset);
				}

				_hoops_SSGHP->LookupItem (owner, &_hoops_GGRHP);
				_hoops_HPPS = _hoops_AGPGR (_hoops_CISIR->type);
			}
			else {
				_hoops_HPPS = _hoops_AGPGR (_hoops_PHRIR+1);	// _hoops_GII _hoops_GRAA-_hoops_AHHR, _hoops_PPR _hoops_SHSP _hoops_PISH _hoops_HPGR _hoops_AHHR _hoops_HIS _hoops_RPGP _hoops_HHHH
			}

			if (!BIT (_hoops_GGRHP, _hoops_HPPS)) {
				if (_hoops_HPPS != _hoops_AGPGR (_hoops_PHRIR+1)) {	// _hoops_GA'_hoops_RA _hoops_SHAC _hoops_HHACR _hoops_PISH _hoops_GPP _hoops_IAHA/_hoops_GCIS
					_hoops_GGRHP |= _hoops_HPPS;
					_hoops_SSGHP->ReplaceItem (owner, _hoops_GGRHP);
				}

				/* _hoops_HPGGR _hoops_RH _hoops_CAGH'_hoops_GRI _hoops_ARGPR _hoops_AIRI _hoops_CPCI _hoops_GAR _hoops_AIPH */
				if (_hoops_CISIR->type >= _hoops_AHRIR && _hoops_CISIR->type <= _hoops_PHRIR)
					HI_Invalidate_Segment_Display_Lists (_hoops_RIGC, owner, _hoops_CISIR->type, (Geometry *)_hoops_CISIR, 0);

				if (_hoops_CISIR->type >= _hoops_AHRIR && _hoops_CISIR->type <= _hoops_PHRIR ||
					_hoops_CISIR->type == _hoops_AGRPR) {
					HI_Antiquate_Bounding (owner, true);

					if (_hoops_CISIR->type != _hoops_AGRPR)
						if (owner->_hoops_HSRIR != null)
							owner->_hoops_HSRIR.Modify()->flags |= _hoops_AAPGP;
				}

				if (!BIT (_hoops_CISIR->_hoops_CPGPR, _hoops_CASIR)) {
					if (_hoops_CISIR->type == _hoops_AGRPR) {
						_hoops_PGRPR				*include = (_hoops_PGRPR *) _hoops_CISIR;
						_hoops_CRCP				*_hoops_SRCP;

						_hoops_SRCP = (_hoops_CRCP alter *)include->_hoops_IGRPR;

						/* _hoops_RH _hoops_HSPR _hoops_HRGR _hoops_RIRRR _hoops_HII _hoops_RGRHP... */
						if (owner->type == _hoops_PRAIR) {/* _hoops_SAHR _hoops_ASSS _hoops_SPSIR _hoops_IS _hoops_CIPGA */}
						else if (BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR)) {/* _hoops_SCACR. */}
						else if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA) &&
								 (ANYBIT (_hoops_SRCP->_hoops_RCGC, _hoops_HAHGP) ||
								  BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR))) {
							/* _hoops_RGRIR _hoops_PCCP _hoops_PAAP */
							_hoops_SASIR (_hoops_RIGC, owner, _hoops_HGSCA |
														_hoops_IHPGP);
						}
						else if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) {
							Window				*window = HI_Find_Scoping_Window (_hoops_SRCP);

							_hoops_SRCP->_hoops_PHSI &= ~_hoops_SHSIR;
							_hoops_SRCP->_hoops_CPGPR &= ~_hoops_AHPGP; /* _hoops_HIAP */
							HI_Propagate_Scoped_Activity (_hoops_RIGC, (_hoops_SIHIR *)_hoops_SRCP,
														  _hoops_GSCCA,
														  &window->_hoops_RCHS);
							_hoops_SRCP->_hoops_PHSI |= _hoops_SHSIR;
						}
						else if (ANYBIT (_hoops_SRCP->_hoops_RCGC, T_FACES))
							_hoops_SASIR (_hoops_RIGC, owner, _hoops_PCPGP |
														_hoops_CSCCA |
														_hoops_PISSR|
														_hoops_RPSIR|
														_hoops_SSCCA);
						else if (ANYBIT (_hoops_SRCP->_hoops_RCGC, _hoops_HAHGP))
							_hoops_SASIR (_hoops_RIGC, owner, _hoops_HRCCA |
														_hoops_PISSR|
														_hoops_RPSIR|
														_hoops_SSCCA);
						else
							_hoops_SASIR (_hoops_RIGC, owner, _hoops_CCHPA);
					}
#ifndef DISABLE_STYLE_SEGMENT
					else if (_hoops_CISIR->type == HK_STYLE)
						HI_Delete_Style_Attributes (_hoops_RIGC, owner, (Style *)_hoops_CISIR);
#endif
					else {
						/* _hoops_SCH'_hoops_GRI _hoops_CPAP */

						/* _hoops_PAGA: _hoops_IPAC _hoops_HCR _hoops_AHSHA, _hoops_HAR _hoops_SAHR _hoops_CARS */
						_hoops_CAAI (HOOPS_WORLD->_hoops_RIPSA);
						_hoops_AIGPR *	_hoops_AGRHP = HOOPS_WORLD->_hoops_PGSCA;
						do {
							_hoops_SIRIR *	_hoops_AHSCA = _hoops_AGRHP->open_list;
							while (_hoops_AHSCA != null) {
								if (_hoops_AHSCA->_hoops_GCRIR == _hoops_HCRIR &&
									_hoops_AHSCA->info.geometry._hoops_IGRPR == (Geometry *)_hoops_CISIR) {
									_hoops_APAI (HOOPS_WORLD->_hoops_RIPSA);
									HE_ERROR (HEC_GEOMETRY, HES_OPEN_GEOMETRY, "Can't delete geometry - still open");
									// _hoops_ASRC _hoops_GA'_hoops_RA _hoops_ASRC _hoops_PGGA _hoops_RII _hoops_APSAR _hoops_SIAS 
									continue;
								}
								_hoops_AHSCA = _hoops_AHSCA->next;
							}
						} while ((_hoops_AGRHP = _hoops_AGRHP->next) != null);
						_hoops_APAI (HOOPS_WORLD->_hoops_RIPSA);

						switch (_hoops_CISIR->type) {
							case _hoops_RCIP:
							case _hoops_SGCP:
							case _hoops_CGCP:
							case _hoops_GGCP:
							case _hoops_PRCP:
							case _hoops_ASIP:
							case _hoops_CSIP:
							case _hoops_HSIP:
							case _hoops_SCIP:
							case _hoops_GSIP:
							case _hoops_AHIP: {
								_hoops_SASIR (_hoops_RIGC, owner, _hoops_PCPGP|
														   _hoops_CSCCA|
														   _hoops_PISSR|
														   _hoops_RPSIR|
														   _hoops_SSCCA);
							}	break;

							case _hoops_HGPGR: {
								_hoops_SASIR (_hoops_RIGC, owner, _hoops_PCPGP|
														   _hoops_CSCCA|
														   _hoops_RPSIR|
														   _hoops_SSCCA);
							}	break;

							default: {
								_hoops_SASIR (_hoops_RIGC, owner, _hoops_HRCCA|
														   _hoops_PISSR|
														   _hoops_RPSIR|
														   _hoops_SSCCA);
							}	break;
						}
					}
				}
			}

			HI_Generic_Delete (_hoops_RIGC,_hoops_CISIR);
		}
	}

	delete _hoops_SSGHP;
}


HC_INTERFACE void HC_CDECL HC_Delete_By_Key (
	Key			key)
{
	_hoops_PAPPR context("Delete_By_Key");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Delete_By_Key (LOOKUP (%D));\n", key));
	);

	_hoops_RPPPR();

	_hoops_HPAH *	_hoops_CISIR = (_hoops_HPAH *)_hoops_RCSSR (context, key);

	if (_hoops_CISIR == null ||
		BIT (_hoops_CISIR->_hoops_RRHH, _hoops_HGAGR) ||
		(_hoops_CISIR->type < _hoops_AHRIR || _hoops_CISIR->type > _hoops_PHRIR) &&
		 _hoops_CISIR->type != _hoops_AGRPR && _hoops_CISIR->type != _hoops_IRCP &&
		 _hoops_CISIR->type != HK_STYLE && _hoops_CISIR->type != _hoops_HCIIR) {
		HE_ERROR (HEC_MISC, HES_INVALID_KEY,
				"Key does not refer to a valid segment, style, include, or geometry");
	}
	else
		HI_Delete_By_Keys (context, 1, &key);

	_hoops_IRRPR();
}



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
 * $Id: obf_tmp.txt 1.76 2010-10-06 19:16:21 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


HC_INTERFACE void HC_CDECL HC_Delete_Segment (
	char const *	name)
{
	_hoops_PAPPR context("Delete_Segment");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Delete_Segment (%S);\n", name));
	);

	/*** (_hoops_HHGC _hoops_SCIA-_hoops_ISHP _hoops_GIPHR!) ***/
	_hoops_RPPPR();
	HI_For_Each (context, name, true, HI_Delete_Segment, (void *)null);
	_hoops_IRRPR();
}

GLOBAL_FUNCTION bool HI_Is_Segment_Open(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	bool					_hoops_AARHP)
{
	bool result = false;

	UNREFERENCED(_hoops_RIGC);
	// _hoops_CIS _hoops_PIHA _hoops_AAHS _hoops_IPPSA->_hoops_PARHP;

	/* _hoops_PAGA: _hoops_SR'_hoops_ASAR _hoops_IPAC _hoops_HCR _hoops_AHSHA, _hoops_HAR _hoops_SAHR _hoops_CARS */
	_hoops_AIGPR *	_hoops_AGRHP = HOOPS_WORLD->_hoops_PGSCA;

	do {
		_hoops_SIRIR *			_hoops_AHSCA = _hoops_AGRHP->open_list;

		while (_hoops_AHSCA  != null) {
			switch (_hoops_AHSCA->_hoops_GCRIR) {
				case _hoops_HCRIR: {
					_hoops_CRCP *	owner;
					if ((owner = _hoops_AHSCA->info.geometry._hoops_IGRPR->owner) != null)
						_hoops_RGGA (owner->type == _hoops_PRAIR) {
							if (owner == _hoops_SRCP) {
								if (_hoops_AARHP)
									HE_ERROR2 (HEC_GEOMETRY, HES_OPEN_GEOMETRY,
										Sprintf_P (null, "Segment '%p' -", _hoops_SRCP),"Geometry is still open somewhere within it");
								result = true;
								goto _hoops_PRSPR;
							}
							owner = owner->owner;
						}
					else {
						/* _hoops_HAIC'_hoops_RA _hoops_CPSA _hoops_ISPR! */
					}
				}	break;

				case _hoops_RCRIR: {
					if (_hoops_AHSCA->info.segment._hoops_PCRIR == _hoops_SRCP) {
						if (_hoops_AARHP)
							HE_ERROR (HEC_SEGMENT, HES_OPEN_SEGMENT,
								Sprintf_P (null, "Segment '%p' - still Open", _hoops_SRCP));
						result = true;
						goto _hoops_PRSPR;
					}
					else {
						_hoops_CRCP *	owner = _hoops_AHSCA->info.segment._hoops_PCRIR->owner;

						_hoops_RGGA (owner->type == _hoops_PRAIR) {
							if (owner == _hoops_SRCP) {
								if (_hoops_AARHP) {
									char	buf[MAX_ERRMSG];
									HE_ERROR2 (HEC_SEGMENT, HES_OPEN_SEGMENT,
										Sprintf_P (null, "Segment '%p' -", _hoops_SRCP),
										Sprintf_P (buf, "subsegment '%p' is still open", _hoops_AHSCA->info.segment._hoops_PCRIR));
								}
								result = true;
								goto _hoops_PRSPR;
							}
							owner = owner->owner;
						}
					}
				}	break;

				case _hoops_CCRIR:
				case _hoops_SCRIR:
				case _hoops_ICRIR:
				case _hoops_RSRIR:
				case _hoops_ASRIR:
				case _hoops_GSRIR:
					/* _hoops_AGCR _hoops_GA'_hoops_RA _hoops_RRP _hoops_HHHA _hoops_HCGC _hoops_GAR _hoops_SSIA _hoops_CGH _hoops_SHR
					 * _hoops_SHH _hoops_HARHP _hoops_CCA _hoops_PCCP _hoops_IHIA _hoops_IARHP
					 */
					break;

				default: {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Corrupt open list");
					result = true;
					goto _hoops_PRSPR;
				}	break;
			}
			_hoops_AHSCA = _hoops_AHSCA->next;
		}
	} while ((_hoops_AGRHP = _hoops_AGRHP->next) != null);

_hoops_PRSPR:
	return result;
}

GLOBAL_FUNCTION void HI_Delete_Segment (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	void *					info)
{
	UNREFERENCED (info);

	_hoops_CAAI (HOOPS_WORLD->_hoops_RIPSA);

	if (HI_Is_Segment_Open(_hoops_RIGC, _hoops_SRCP, true)) {
		_hoops_APAI (HOOPS_WORLD->_hoops_RIPSA);
		return;
	}

	if (_hoops_SRCP != HOOPS_WORLD->root) {
		for (int i=0; i<HOOPS_WORLD->_hoops_CARHP; i++) {
			if (_hoops_SRCP == HOOPS_WORLD->_hoops_SARHP[i]._hoops_RPGHP) {
				char	buf[MAX_ERRMSG];
				_hoops_PHPGR (HEC_SEGMENT, HES_NOT_AVAILABLE,
						Sprintf_P (null, "Deleting segment '%p' -", _hoops_SRCP),
						Sprintf_D (buf, "removes 'texture root' for definition set '%d'", i));
				HOOPS_WORLD->_hoops_SARHP[i]._hoops_RPGHP = HOOPS_WORLD->root;
			}
		}
	}

	_hoops_APAI (HOOPS_WORLD->_hoops_RIPSA);

	HI_Flush_Seg_Path_Lookup(_hoops_RIGC);

	_hoops_CRCP *	owner = _hoops_SRCP->owner;
	if (owner->type == _hoops_PRAIR) {/* _hoops_SAHR _hoops_ASSS _hoops_SPSIR _hoops_IS _hoops_CIPGA */}
	else if (BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR)) {/* _hoops_SCACR. */}
	else if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA) &&
			 (ANYBIT (_hoops_SRCP->_hoops_RCGC, _hoops_PAHGP) ||
			  BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR))) {
		/* _hoops_RGRIR _hoops_PCCP _hoops_PAAP */
		_hoops_SASIR (_hoops_RIGC, owner, _hoops_HGSCA | _hoops_IHPGP);
	}
	else if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) {
		Window		*window = HI_Find_Scoping_Window (_hoops_SRCP);

		/*
		 * _hoops_GPRHP _hoops_IPIHR _hoops_RH _hoops_RPPS, _hoops_HIS _hoops_SGS _hoops_RH
		 * _hoops_RPRHP _hoops_CPGGR _hoops_ASSP'_hoops_RA _hoops_HGCR _hoops_APRHP _hoops_ISHP,
		 * _hoops_HCCPR _hoops_RPPS _hoops_HRGR _hoops_PSIPR -- _hoops_IIS _hoops_SCH _hoops_HGCR _hoops_ARGS
		 * _hoops_PPRHP _hoops_SGGR
		 */
		if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GCHGP))
			_hoops_SRCP->_hoops_PHSI &= ~_hoops_SHSIR;
		_hoops_SRCP->_hoops_CPGPR &= ~_hoops_AHPGP; /* _hoops_HIAP */
		HI_Propagate_Scoped_Activity (_hoops_RIGC, (_hoops_SIHIR *)_hoops_SRCP,
									  _hoops_SCCCA,
									  &window->_hoops_RCHS);
		_hoops_SRCP->_hoops_PHSI |= _hoops_SHSIR;
	}
	else if (ANYBIT (_hoops_SRCP->_hoops_RCGC, T_FACES))
		_hoops_SASIR (_hoops_RIGC, owner,
								   _hoops_PCPGP|
								   _hoops_CSCCA|
								   _hoops_PISSR|
								   _hoops_RPSIR|
								   _hoops_SSCCA);
	else if (ANYBIT (_hoops_SRCP->_hoops_RCGC, _hoops_HAHGP))
		_hoops_SASIR (_hoops_RIGC, owner,
								   _hoops_HRCCA|
								   _hoops_PISSR|
								   _hoops_RPSIR|
								   _hoops_SSCCA);
	else
		_hoops_SASIR (_hoops_RIGC, owner, _hoops_CCHPA);

	HI_Antiquate_Bounding (_hoops_SRCP, false);
	HI_Generic_Delete (_hoops_RIGC,(_hoops_HPAH *)_hoops_SRCP);
}

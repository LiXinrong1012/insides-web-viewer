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
 * $Id: obf_tmp.txt 1.45 2010-10-06 19:16:28 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "adt.h"



GLOBAL_FUNCTION void HI_More_Transparencies (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	int						count) 
{
	_hoops_ICIIR(_hoops_RIGC);

	if (count == 0 || ANYBIT (_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR|_hoops_HIRIR))
		return;

	_hoops_PCCAR {
		int			_hoops_IRCSA = _hoops_SRCP->_hoops_IGCCA;
		int			_hoops_RGCCA = _hoops_IRCSA + count;

		_hoops_SRCP->_hoops_IGCCA = _hoops_RGCCA;

		if (_hoops_RGCCA < 0) {
			if (_hoops_IRCSA >= 0) /* _hoops_SHCAR, _hoops_RPP _hoops_SCH _hoops_SAHR _hoops_HA _hoops_CCIHH _hoops_AHCI */
				_hoops_PHPGR (HEC_HOOPS_SYSTEM, HES_HOOPS_IS_CONFUSED,
						"Transparency counting mismatch",
							 Sprintf_P (null, "(Segment was '%p'.)", _hoops_SRCP));
		}

		if (_hoops_SRCP == HOOPS_WORLD->root) break;

		_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_AISSR);

		if (ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GISIR|_hoops_GIGSA|_hoops_RIGSA) ||
			BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR) && !BIT (_hoops_SRCP->_hoops_PHSI, _hoops_RCHGP))
			break;

		Xref *		_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR();

		if (_hoops_AHICA != null) do {
			if (_hoops_AHICA->type == _hoops_AGRPR &&
				!BIT (_hoops_AHICA->_hoops_RRHH, _hoops_HGAGR))
				HI_More_Transparencies (_hoops_RIGC, _hoops_AHICA->owner, count);
		} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);

		_hoops_SRCP = _hoops_SRCP->owner;

		if (_hoops_SRCP == null || _hoops_SRCP->type != _hoops_IRCP)
			return;
	}
}


GLOBAL_FUNCTION void HI_Less_Transparencies (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	int						count) {

	HI_More_Transparencies (_hoops_RIGC, _hoops_SRCP, -count);
}




GLOBAL_FUNCTION void HI_More_Shadows (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	int						count) 
{
	_hoops_ICIIR(_hoops_RIGC);

	if (count == 0 || ANYBIT (_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR|_hoops_HIRIR))
		return;

	_hoops_PCCAR {
		int			_hoops_IRCSA = _hoops_SRCP->_hoops_SHGSA();
		int			_hoops_RGCCA = _hoops_IRCSA + count;

		_hoops_SRCP->_hoops_ASIGP (_hoops_RGCCA);

		if (_hoops_RGCCA < 0) {
			if (_hoops_IRCSA >= 0) /* _hoops_SHCAR, _hoops_RPP _hoops_SCH _hoops_SAHR _hoops_HA _hoops_CCIHH _hoops_AHCI */
				_hoops_ARGIP (HEC_HOOPS_SYSTEM, HES_HOOPS_IS_CONFUSED,
						"Either you have more than 32767 shadows in a",
							 "scene or Hoops is very confused. The picture may not be right.",
							 Sprintf_P (null, "(Segment was '%p'.)", _hoops_SRCP));
		}

		if (_hoops_SRCP == HOOPS_WORLD->root) break;

		_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_AISSR);

		if (ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR)) break;

		Xref *		_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR();

		if (_hoops_AHICA != null) do {
			if (_hoops_AHICA->type == _hoops_AGRPR &&
				!BIT (_hoops_AHICA->_hoops_RRHH, _hoops_HGAGR))
				HI_More_Shadows (_hoops_RIGC,_hoops_AHICA->owner, count);
		} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);

		_hoops_SRCP = _hoops_SRCP->owner;

		if (_hoops_SRCP == null || _hoops_SRCP->type != _hoops_IRCP)
			return;
	}
}


GLOBAL_FUNCTION void HI_Less_Shadows (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	int						count) {

	HI_More_Shadows (_hoops_RIGC, _hoops_SRCP, -count);
}



/*
	_hoops_GRCII _hoops_RRCII _hoops_ARCII._hoops_IHRPR!
	"_hoops_PRCII" _hoops_HGAS _hoops_IS "_hoops_HRCII".
	_hoops_IPCP _hoops_AIIAP _hoops_HGAS _hoops_IS _hoops_HAR _hoops_GCIS _hoops_IRCII.

*/

GLOBAL_FUNCTION void HI_More_Cutting_Planes (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	int						count) 
{
	_hoops_ICIIR(_hoops_RIGC);

	if (count == 0 || ANYBIT (_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR|_hoops_HIRIR))
		return;

	_hoops_PCCAR {
		int			_hoops_IRCSA = _hoops_SRCP->_hoops_PAGSA();
		int			_hoops_RGCCA = _hoops_IRCSA + count;

		if (_hoops_RGCCA >= 0)
			_hoops_SRCP->_hoops_RSIGP (_hoops_RGCCA);

		if (_hoops_SRCP == HOOPS_WORLD->root) break;

		_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_GGARA | _hoops_RPSIR |
								 _hoops_ISCCA | _hoops_AICSA);

		if (ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR)) break;

		Xref *	_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR();

		if (_hoops_AHICA != null) do {
			if (_hoops_AHICA->type == _hoops_AGRPR &&
				!BIT (_hoops_AHICA->_hoops_RRHH, _hoops_HGAGR))
				HI_More_Cutting_Planes (_hoops_RIGC,_hoops_AHICA->owner, count);
		} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);


		_hoops_RPAPA * _hoops_APAPA = HOOPS_WORLD->_hoops_PPAPA->Lookup(_hoops_SRCP);

		if (_hoops_APAPA != null) {
			_hoops_APAPA->ResetCursor();
			_hoops_PHIP *	_hoops_RRA;
			while((_hoops_RRA = _hoops_APAPA->PeekCursor()) != null) {
				if (BIT (_hoops_RRA->_hoops_RGPGR, _hoops_AGPGR (_hoops_HGPGR)))
					HI_More_Cutting_Planes (_hoops_RIGC,_hoops_RRA->owner, count);
				_hoops_APAPA->AdvanceCursor();
			}
		}

		_hoops_SRCP = _hoops_SRCP->owner;

		if (_hoops_SRCP == null || _hoops_SRCP->type != _hoops_IRCP)
			return;
	}
}


GLOBAL_FUNCTION void HI_Less_Cutting_Planes (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	int						count) {

	HI_More_Cutting_Planes (_hoops_RIGC, _hoops_SRCP, -count);
}



GLOBAL_FUNCTION void HI_More_Light (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	int						count) 
{
	_hoops_ICIIR(_hoops_RIGC);

	if (count == 0 || ANYBIT (_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR|_hoops_HIRIR))
		return;

	_hoops_PCCAR {
		int			_hoops_IRCSA = _hoops_SRCP->_hoops_AAGSA();
		int			_hoops_RGCCA = _hoops_IRCSA + count;

		_hoops_SRCP->_hoops_GSIGP (_hoops_RGCCA);

		if (_hoops_RGCCA < 0) {
			if (_hoops_IRCSA >= 0) /* _hoops_SHCAR, _hoops_RPP _hoops_SCH _hoops_SAHR _hoops_HA _hoops_CCIHH _hoops_AHCI */
				_hoops_ARGIP (HEC_HOOPS_SYSTEM, HES_HOOPS_IS_CONFUSED,
						"Either you have more than 32767 lights in a scene or",
							 "Hoops is very confused. The picture may not be right.",
							 Sprintf_P (null, "(Segment was '%p'.)", _hoops_SRCP));
		}

		if (_hoops_SRCP == HOOPS_WORLD->root) break;

		_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_GPSIR|_hoops_RPSIR|_hoops_IISSR);

		if (ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR)) break;

		Xref *	_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR();

		if (_hoops_AHICA != null) do {
			if (_hoops_AHICA->type == _hoops_AGRPR &&
				!BIT (_hoops_AHICA->_hoops_RRHH, _hoops_HGAGR))
				HI_More_Light (_hoops_RIGC, _hoops_AHICA->owner, count);
		} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);

		_hoops_RPAPA * _hoops_APAPA = HOOPS_WORLD->_hoops_PPAPA->Lookup(_hoops_SRCP);

		if (_hoops_APAPA != null) {
			_hoops_APAPA->ResetCursor();
			_hoops_PHIP *	_hoops_RRA;
			while((_hoops_RRA = _hoops_APAPA->PeekCursor()) != null) {
				if (BIT (_hoops_RRA->_hoops_RGPGR, _hoops_AGPGR (_hoops_ICIP)))
					HI_More_Light (_hoops_RIGC, _hoops_RRA->owner, count);
				_hoops_APAPA->AdvanceCursor();
			}
		}

		_hoops_SRCP = _hoops_SRCP->owner;

		if (_hoops_SRCP == null || _hoops_SRCP->type != _hoops_IRCP)
			return;
	}
}


GLOBAL_FUNCTION void HI_Less_Light (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	int						count) {

	HI_More_Light (_hoops_RIGC, _hoops_SRCP, -count);
}



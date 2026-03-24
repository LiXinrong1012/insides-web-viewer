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
 * $Id: obf_tmp.txt 1.126 2010-10-28 18:04:55 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"
#include "hpserror.h"





GLOBAL_FUNCTION bool HI_Set_Attribute (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH *					node,
	Type						type,
	_hoops_RSCIH	_hoops_ASCIH,
	Attribute *					_hoops_ASGPR)
{
	_hoops_ICIIR(_hoops_RIGC);

	bool _hoops_RGAPS = false;

	_hoops_HPAH *		_hoops_AGAPS = node;
	_hoops_CRCP *		_hoops_SRCP = (_hoops_CRCP*)node;
	Geometry *		geo = null;
	_hoops_CRCP *		owner = _hoops_SRCP;
	Attribute **	_hoops_ASRGR = null;

	if (node->type == _hoops_IRCP) {
		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR) &&
			/*	  _hoops_CPSA _hoops_ARP _hoops_RPPS/_hoops_RHPP _hoops_CIPH _hoops_GPP _hoops_SCIA _hoops_PAPA _hoops_RPP _hoops_PIGHH	 */
			(type != HK_WINDOW				&& type != HK_WINDOW_FRAME &&
			 /*
			 _hoops_GPRR != _hoops_PGAPS	&& _hoops_GPRR != _hoops_HGAPS &&
			 _hoops_HGGSP[_hoops_IGAPS] _hoops_HAIR _hoops_HA _hoops_GIR _hoops_CAPP _hoops_GAR _hoops_GSHRH _hoops_GRH _hoops_AGIR
			 */
			 type != HK_WINDOW_PATTERN		&&
			 type != HK_DRIVER				&& type != HK_DRIVER_OPTIONS)) {

			_hoops_CRCP *			_hoops_GGARH = _hoops_SRCP;
			Attribute *			_hoops_HPHCR;
			_hoops_RRAIR *	_hoops_CGAPS;

			if ((_hoops_HPHCR = _hoops_GGARH->_hoops_IPPGR) != null) do {
				if (_hoops_HPHCR->type == _hoops_GRAIR)
					break;
			} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);

			if (_hoops_HPHCR == null) {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Streaming attribute missing");
				goto _hoops_PRSPR;
			}

			_hoops_CGAPS = (_hoops_RRAIR *)_hoops_HPHCR;

			_hoops_SRCP = _hoops_CGAPS->_hoops_PHSCA;

			if (_hoops_SRCP->geometry != null || _hoops_SRCP->_hoops_RGRPR != null) {
				_hoops_CRCP *	_hoops_SGAPS = _hoops_SRCP;

				/* _hoops_GHGA _hoops_IGRI _hoops_RAS _hoops_CPAP _hoops_PAR _hoops_GCIS _hoops_PIHA _hoops_ARPR _hoops_CCAH _hoops_HHASA */

				if (_hoops_SRCP->_hoops_RGRPR == null) {
					_hoops_SRCP = HI_Create_One_Segment (_hoops_RIGC, null, &_hoops_SRCP->_hoops_RGRPR, null, _hoops_SRCP, true);
				}
				else {
					Subsegment	*_hoops_SRRGI = _hoops_SRCP->_hoops_RGRPR;

					_hoops_RGGA (_hoops_SRRGI->next == null) _hoops_SRRGI = _hoops_SRRGI->next;
					_hoops_SRCP = HI_Create_One_Segment (_hoops_RIGC, null, &_hoops_SRRGI->next, _hoops_SRRGI, _hoops_SRCP, true);
				}

				_hoops_SRCP->_hoops_PHSI |= _hoops_PRSIR;

				_hoops_CGAPS->_hoops_PHSCA = _hoops_SRCP;

				_hoops_SIRIR *	_hoops_AHSCA = _hoops_RIGC->open_list;

				while (_hoops_AHSCA != null) {
					if (_hoops_AHSCA->_hoops_GCRIR == _hoops_RCRIR &&
						_hoops_AHSCA->info.segment._hoops_IGRPR == _hoops_SGAPS) {
						_hoops_PRRH (_hoops_SRCP);
						_hoops_HPRH (_hoops_SGAPS);
						_hoops_AHSCA->info.segment._hoops_IGRPR = _hoops_SRCP;
						if (_hoops_AHSCA->info.segment._hoops_ACRIR != null) {
							_hoops_HPRH (_hoops_AHSCA->info.segment._hoops_ACRIR);
							_hoops_AHSCA->info.segment._hoops_ACRIR = null;
						}
					}
					_hoops_AHSCA = _hoops_AHSCA->next;
				}
			}

			_hoops_AGAPS = (_hoops_HPAH *)_hoops_SRCP;
			owner = _hoops_SRCP;
		}

		_hoops_ASRGR = &_hoops_SRCP->_hoops_IPPGR;
	}
	else {
		/* _hoops_CPSA _hoops_CPAP! */
		_hoops_SRCP = (_hoops_CRCP *)node->owner;
		geo = (Geometry *)node;
		_hoops_ASRGR = &geo->_hoops_IPPGR;

		ASSERT (node->type >= _hoops_AHRIR && node->type <= _hoops_PHRIR);
		ASSERT (HI_Check_Geometry_Attribute_Type(_hoops_RIGC,geo,type));
	}


	Attribute *		_hoops_PISCA;

	while ((_hoops_PISCA = *_hoops_ASRGR) != null) {
		if (_hoops_PISCA->type >= type) {
			if (_hoops_PISCA->type > type)
				_hoops_PISCA = null;
			break;
		}
		_hoops_ASRGR = &_hoops_PISCA->next;
	}

	Attribute *		_hoops_SISCA;

	if ((_hoops_SISCA = (*_hoops_ASCIH)(_hoops_RIGC, _hoops_AGAPS, _hoops_PISCA, _hoops_ASGPR)) != null) {
		_hoops_RGAPS = true;

		_hoops_SISCA->type = type;
		_hoops_SISCA->_hoops_HIHI = 1;
		_hoops_SISCA->owner = owner;

		_hoops_SISCA->backlink = _hoops_ASRGR;
		if ((_hoops_SISCA->next = *_hoops_ASRGR) != null)
			(*_hoops_ASRGR)->backlink = &_hoops_SISCA->next;
		*_hoops_ASRGR = _hoops_SISCA;

		_hoops_SISCA->_hoops_CPGPR = _hoops_HCHPA;
		_hoops_SISCA->_hoops_SPGPR = 0;
		/* _hoops_RHSGS->_hoops_CPGC = 0; */

		if (_hoops_PISCA != null)
			_hoops_CIGPR (_hoops_RIGC,_hoops_PISCA);

		if (_hoops_SRCP != null) {	/* _hoops_PSSSR _hoops_PGCCA */
			HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, type, _hoops_PISCA, _hoops_SISCA);
			_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_CCHPA);
		}

		if (_hoops_PISCA != null)
			HI_Generic_Delete (_hoops_RIGC, (_hoops_HPAH *)_hoops_PISCA);
	}


	if (type == HK_DRIVER_OPTIONS || type == HK_COLOR &&
		node->type == _hoops_IRCP) {

		/* _hoops_PHIH _hoops_PHHIP _hoops_IH _hoops_GRH _hoops_ARAR,_hoops_CR _hoops_PIGHH _hoops_RRGR _hoops_ARRS _hoops_GHCA _hoops_AGRP _hoops_SCH */
		_hoops_SRCP = (_hoops_CRCP *)node;

		/* _hoops_GRH _hoops_PRCA _hoops_IH "_hoops_GRAPS" _hoops_IRS _hoops_RHPP */
		if (type == HK_DRIVER_OPTIONS && _hoops_SISCA != null &&
			BIT (((_hoops_GAPIR *)_hoops_ASGPR)->_hoops_HAICA, _hoops_SIPRP)) {

			_hoops_GAPIR const *		_hoops_RAPIR = (_hoops_GAPIR const *)_hoops_ASGPR;

			if (BIT (_hoops_RAPIR->_hoops_IAPRP, _hoops_SIPRP))
				_hoops_SRCP->_hoops_PHSI |= _hoops_ARRPR;
			else
				_hoops_SRCP->_hoops_PHSI &= ~_hoops_ARRPR;
		}
		/* _hoops_RGHH _hoops_RPPS [_hoops_CGARA] _hoops_HAIR _hoops_GPP _hoops_PIGHH _hoops_CAGH */
		else if (type == HK_COLOR  && BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR) &&
			ANYBIT (((_hoops_SSGI const *)_hoops_ASGPR)->_hoops_GHA, Color_WINDOW|Color_WINDOW_CONTRAST)) {

			_hoops_SSGI *	_hoops_RRAPS;
			ZALLOC (_hoops_RRAPS, _hoops_SSGI);

			_hoops_ACSGA *	list = ((_hoops_SSGI *)_hoops_ASGPR)->colors;
			do {
				if (ANYBIT (list->_hoops_GHA, Color_WINDOW|Color_WINDOW_CONTRAST)) {
					_hoops_ACSGA *		_hoops_IIHHH = list->next;
					_hoops_ACSGA *		tmp;

					list->next = null;
					tmp = HI_Copy_Colors (list, null);
					list->next = _hoops_IIHHH;

					tmp->next = _hoops_RRAPS->colors;
					_hoops_RRAPS->colors = tmp;
					tmp->_hoops_GHA &= Color_WINDOW|Color_WINDOW_CONTRAST;
					_hoops_RRAPS->_hoops_GHA |= tmp->_hoops_GHA;
				}
			} while ((list = list->next) != null);

			_hoops_ASRGR = &_hoops_SRCP->_hoops_IPPGR;
			while ((_hoops_PISCA = *_hoops_ASRGR) != null) {
				if (_hoops_PISCA->type >= type) {
					if (_hoops_PISCA->type > type)
						_hoops_PISCA = null;
					break;
				}
				_hoops_ASRGR = &_hoops_PISCA->next;
			}

			if ((_hoops_SISCA = (*_hoops_ASCIH)(_hoops_RIGC, node, _hoops_PISCA, _hoops_RRAPS)) != null) {
				_hoops_SISCA->type = type;
				_hoops_SISCA->_hoops_HIHI = 1;
				_hoops_SISCA->owner = _hoops_SRCP;

				_hoops_SISCA->backlink = _hoops_ASRGR;
				if ((_hoops_SISCA->next = *_hoops_ASRGR) != null)
					(*_hoops_ASRGR)->backlink = &_hoops_SISCA->next;
				*_hoops_ASRGR = _hoops_SISCA;

				_hoops_SISCA->_hoops_CPGPR = _hoops_HCHPA;
				_hoops_SISCA->_hoops_SPGPR = 0;
				/* _hoops_RHSGS->_hoops_CPGC = 0; */

				HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, type, _hoops_PISCA, _hoops_SISCA);

				_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_CCHPA);

				if (_hoops_PISCA != null)
					HI_Generic_Delete (_hoops_RIGC,(_hoops_HPAH *)_hoops_PISCA);
			}
			else {
				_hoops_RRAPS->type = HK_COLOR;
				_hoops_RRAPS->_hoops_HIHI = 1;
				_hoops_HPRH (_hoops_RRAPS);
			}
		}
	}
	else if (type == HK_MODELLING_MATRIX && geo != null) {
		ASSERT(geo->type >= _hoops_AHRIR && geo->type <= _hoops_PHRIR);

		Bounding	_hoops_RCHS;

		if (HI_Figure_Geometry_Bounding (geo, _hoops_RCHS)) {
			_hoops_CRCP *	_hoops_SRCP = geo->owner;

			HI_Propagate_Bounding (_hoops_RIGC, _hoops_SRCP, _hoops_RCHS, null);
			HI_Antiquate_Bounding (_hoops_SRCP, true);

			if (_hoops_SRCP->_hoops_HSRIR != null) {
				_hoops_SRCP->_hoops_HSRIR.Modify()->flags |= _hoops_AAPGP;
				_hoops_SRCP->_hoops_HSRIR->Merge (_hoops_RCHS);	// _hoops_GGSR-_hoops_IIGR-_hoops_ICGIP _hoops_HIH _hoops_GHACA
			}
		}
	}

_hoops_PRSPR:

	return _hoops_RGAPS;
}



GLOBAL_FUNCTION void HI_UnSet_Attribute (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	int						type)
{
	_hoops_ICIIR(_hoops_RIGC);

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else

	Attribute *	_hoops_HPHCR = null;
	_hoops_HPAH *	original = item;
	_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)item;

	if (item->type == _hoops_IRCP) {
		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) {
			HI_Not_When_Streamed (_hoops_SRCP, "'UnSet' things");
			goto _hoops_PRSPR;
		}

		if (_hoops_SRCP->owner->type == _hoops_PRAIR) {
			_hoops_PHPGR (HEC_ATTRIBUTE, HES_DEFAULT_WORLD_ATTRIBUTE,
				"Not good to 'UnSet' the attribute settings in '/' -",
				"They are the defaults for the world");
			goto _hoops_PRSPR;
		}
		_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR;
	}
	else {
		/* _hoops_CPSA _hoops_CPAP! */
		Geometry * geo = (Geometry *)item;
		_hoops_HPHCR = geo->_hoops_IPPGR;
		_hoops_SRCP = _hoops_SRCP->owner;
	}

	if (_hoops_HPHCR != null) {
		do if (_hoops_HPHCR->type >= type) {
			if (_hoops_HPHCR->type == type) {
				HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, type, _hoops_HPHCR, null);
				if (original->type != _hoops_IRCP)
					_hoops_SASIR (_hoops_RIGC, original, _hoops_GGARA|_hoops_RPSIR);
				HI_Generic_Delete (_hoops_RIGC, (_hoops_HPAH *)_hoops_HPHCR);
			}
			break;
		} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
	}

	/* _hoops_HAR _hoops_ARI, _hoops_ICCAR _hoops_PRAR... */
_hoops_PRSPR:
;
#endif
}





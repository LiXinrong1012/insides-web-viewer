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
 * $Id: obf_tmp.txt 1.70 2010-10-06 19:16:28 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hi_proto.h"


GLOBAL_FUNCTION void HI_Age_Seg_Flags	(
	_hoops_CRCP				*root) {

	UNREFERENCED (root);
}


local void _hoops_PPGPR (
	Polyhedron *			_hoops_HPGPR) {

	if (_hoops_HPGPR->tristrips != null) {
		Tristrip *		ts = _hoops_HPGPR->tristrips;
		int				_hoops_IPGPR = 0;


		do {
			if (ts->_hoops_CPGPR != 0 || ts->_hoops_SPGPR != 0) {
				_hoops_IPGPR = 0;	/* _hoops_GHCA _hoops_RRP _hoops_IH _hoops_HPIH _hoops_GIRR _hoops_RPP _hoops_GHGPR-_hoops_RHGPR */
				_hoops_HPGPR->_hoops_CPGPR |= _hoops_AHGPR;

				break;
			}
			else if ((ts->face_attributes.flags & _hoops_PHGPR) == 0) {
				++_hoops_IPGPR;
			}
		} while ((ts = ts->next) != null);

		if (_hoops_IPGPR > 1)	/* _hoops_ISAP _hoops_IS _hoops_HASC _hoops_RPP _hoops_HPGR _hoops_ICRP _hoops_SPR "_hoops_HHGPR" _hoops_CGGR */
			HI_Resort_Tristrips (_hoops_HPGPR, -2);
		else {
			ts = _hoops_HPGPR->tristrips;
			do {
				ts->_hoops_SPGPR = ts->_hoops_CPGPR;
				ts->_hoops_CPGPR = _hoops_IHGPR;
			} while ((ts = ts->next) != null);
		}
	}
	if (_hoops_HPGPR->_hoops_CHGPR != null) {
		Polyedge *		pe = _hoops_HPGPR->_hoops_CHGPR;

		do {
			pe->_hoops_SPGPR = pe->_hoops_CPGPR;
			pe->_hoops_CPGPR = _hoops_IHGPR;
		} while ((pe = pe->next) != null);
	}
	if (_hoops_HPGPR->_hoops_SHGPR != null) {
		Polyedge *		pe = _hoops_HPGPR->_hoops_SHGPR;

		do {
			pe->_hoops_SPGPR = pe->_hoops_CPGPR;
			pe->_hoops_CPGPR = _hoops_IHGPR;
		} while ((pe = pe->next) != null);
	}
	if (_hoops_HPGPR->_hoops_GIGPR != null) {
		Polymarker *		pm = _hoops_HPGPR->_hoops_GIGPR;

		do {
			pm->_hoops_SPGPR = pm->_hoops_CPGPR;
			pm->_hoops_CPGPR = _hoops_IHGPR;
		} while ((pm = pm->next) != null);
	}
}


local void _hoops_RIGPR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_PIGPR *			cursor) {
	_hoops_PIGPR *			_hoops_HIGPR;

	do {
		_hoops_HIGPR = (_hoops_PIGPR *)cursor->next;

		if (cursor->_hoops_CPGPR || cursor->_hoops_SPGPR) {
			if (BIT (cursor->_hoops_RRHH, _hoops_HGAGR)) {
				/* _hoops_PSHR _hoops_GAR _hoops_GGR _hoops_IIGPR */

				HI_Disentangle (_hoops_RIGC, (_hoops_HPAH *)cursor);
				_hoops_CIGPR (_hoops_RIGC,cursor);
				_hoops_HPRH (cursor);
				continue;
			}

			cursor->_hoops_SPGPR = cursor->_hoops_CPGPR & ~_hoops_SIGPR;
			cursor->_hoops_CPGPR = _hoops_IHGPR;
		}
	} while ((cursor = _hoops_HIGPR) != null);
}


local bool _hoops_GCGPR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	bool					_hoops_RCGPR,
	bool					_hoops_ACGPR) {

  top:;

	_hoops_SRCP->_hoops_SPGPR = _hoops_SRCP->_hoops_CPGPR & ~_hoops_SIGPR;
	_hoops_SRCP->_hoops_CPGPR = 0;
	_hoops_SRCP->_hoops_PCGPR = 0;

	_hoops_SRCP->_hoops_PHSI &= ~(_hoops_HCGPR|_hoops_ICGPR);

	{	Geometry		*geometry,
										*_hoops_CCGPR;

		if ((geometry = _hoops_SRCP->geometry) != null) do {
			_hoops_CCGPR = geometry->next;

			if (geometry->_hoops_CPGPR || geometry->_hoops_SPGPR) {
				switch (geometry->type) {
					case _hoops_GSIP:
					case _hoops_SCIP: {
						_hoops_PPGPR ((Polyhedron *)geometry);
					}	break;
					case _hoops_AGCP: {
						_hoops_HACC *		text = (_hoops_HACC *)geometry;

						if (text->_hoops_AAPGR != null)
							_hoops_RIGPR (_hoops_RIGC, text->_hoops_AAPGR);
					}	break;
				}

				geometry->_hoops_SPGPR = geometry->_hoops_CPGPR & ~_hoops_SIGPR;
				geometry->_hoops_CPGPR = _hoops_IHGPR;
			}
		} while ((geometry = _hoops_CCGPR) != null);


		if ((geometry = _hoops_SRCP->_hoops_SCGPR()) != null) {
			do {
				_hoops_CCGPR = geometry->next;

				/* _hoops_PSHR _hoops_GAR _hoops_GGR _hoops_IIGPR */
				if (!_hoops_ACGPR)
					_hoops_ACGPR = _hoops_GSGPR();
				if (_hoops_ACGPR) {
					HI_Disentangle (_hoops_RIGC, (_hoops_HPAH *)geometry);
					_hoops_CIGPR (_hoops_RIGC,geometry);
					_hoops_HPRH (geometry);
				}
			} while ((geometry = _hoops_CCGPR) != null);
			_hoops_SRCP->_hoops_RSGPR (null);
		}
	}

	{	Attribute	*_hoops_ASGPR,
										*_hoops_PSGPR;

		if ((_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR) != null) do {
			_hoops_PSGPR = _hoops_ASGPR->next;

			if (_hoops_ASGPR->_hoops_CPGPR || _hoops_ASGPR->_hoops_SPGPR) {
				switch (_hoops_ASGPR->type) {
					case HK_WINDOW: {
						Window *		window = (Window *)_hoops_ASGPR;

						window->_hoops_HSGPR.left		= window->_hoops_ISGPR.left;
						window->_hoops_HSGPR.right	= window->_hoops_ISGPR.right;
						window->_hoops_HSGPR.bottom	= window->_hoops_ISGPR.bottom;
						window->_hoops_HSGPR.top		= window->_hoops_ISGPR.top;

						window->_hoops_ISGPR.left		=  1;
						window->_hoops_ISGPR.right	= -1;
						window->_hoops_ISGPR.bottom	=  1;
						window->_hoops_ISGPR.top		= -1;
					}	break;

					case HK_DRIVER: {
						_hoops_GGAGR *		_hoops_GHRI = (_hoops_GGAGR *)_hoops_ASGPR;

						_hoops_GHRI->_hoops_CSGPR._hoops_HSGPR.left		= _hoops_GHRI->_hoops_CSGPR._hoops_ISGPR.left;
						_hoops_GHRI->_hoops_CSGPR._hoops_HSGPR.right		= _hoops_GHRI->_hoops_CSGPR._hoops_ISGPR.right;
						_hoops_GHRI->_hoops_CSGPR._hoops_HSGPR.bottom	= _hoops_GHRI->_hoops_CSGPR._hoops_ISGPR.bottom;
						_hoops_GHRI->_hoops_CSGPR._hoops_HSGPR.top		= _hoops_GHRI->_hoops_CSGPR._hoops_ISGPR.top;

						_hoops_GHRI->_hoops_CSGPR._hoops_ISGPR.left		=  1;
						_hoops_GHRI->_hoops_CSGPR._hoops_ISGPR.right		= -1;
						_hoops_GHRI->_hoops_CSGPR._hoops_ISGPR.bottom	=  1;
						_hoops_GHRI->_hoops_CSGPR._hoops_ISGPR.top		= -1;
					}	break;
				}

				_hoops_ASGPR->_hoops_SPGPR = _hoops_ASGPR->_hoops_CPGPR & ~_hoops_SIGPR;
				_hoops_ASGPR->_hoops_CPGPR = _hoops_IHGPR;
			}
		} while ((_hoops_ASGPR = _hoops_PSGPR) != null);
	}

	{	Subsegment	*_hoops_SSGPR,
										*_hoops_GGRPR;

		if ((_hoops_SSGPR = _hoops_SRCP->_hoops_RGRPR) != null) do {
			_hoops_GGRPR = _hoops_SSGPR->next;

			if (_hoops_SSGPR->_hoops_CPGPR || _hoops_SSGPR->_hoops_SPGPR) {
				if (_hoops_SSGPR->type == _hoops_AGRPR) {
					_hoops_PGRPR			*include = (_hoops_PGRPR *)_hoops_SSGPR;

					include->_hoops_SPGPR = _hoops_SSGPR->_hoops_CPGPR & ~_hoops_SIGPR;
					include->_hoops_CPGPR = _hoops_IHGPR;

					if (_hoops_RCGPR) {
						_hoops_CRCP *	_hoops_HGRPR = (_hoops_CRCP alter *)include->_hoops_IGRPR;

						/* _hoops_PSP _hoops_RII _hoops_GCIS _hoops_IS _hoops_IHHH (_hoops_SR _hoops_CHR _hoops_RH _hoops_RGAR _hoops_CGRPR _hoops_GGR _hoops_RH _hoops_HIGR)? */
						if (_hoops_HGRPR->_hoops_SGRPR()->_hoops_GRRPR == null) {
							_hoops_CRCP			*owner = _hoops_HGRPR->owner;

							while (owner != HOOPS_WORLD->root) {
								/* _hoops_HRCC _hoops_ICAS _hoops_PCCP _hoops_RRRPR? */
								if (owner->_hoops_SGRPR() != null)
									break;
								owner = owner->owner;
							}

							/* _hoops_RPP _hoops_PIRC, _hoops_ICIC _hoops_IS _hoops_SCAC _hoops_SGI _hoops_APHR _hoops_ARI */
							if (owner == HOOPS_WORLD->root)
								_hoops_ACGPR = _hoops_GCGPR (_hoops_RIGC, _hoops_HGRPR, _hoops_RCGPR, _hoops_ACGPR);
						}
					}
				}
				else if (!BIT (((_hoops_CRCP const *)_hoops_SSGPR)->_hoops_PHSI, _hoops_ARRPR)) {
					if (_hoops_GGRPR == null) {
						_hoops_SRCP = (_hoops_CRCP *)_hoops_SSGPR;
						goto top;
					}

					_hoops_ACGPR = _hoops_GCGPR (_hoops_RIGC, (_hoops_CRCP *)_hoops_SSGPR, _hoops_RCGPR, _hoops_ACGPR);
				}
			}
		} while ((_hoops_SSGPR = _hoops_GGRPR) != null);

		if ((_hoops_SSGPR = _hoops_SRCP->_hoops_PRRPR()) != null) {
			do {
				_hoops_GGRPR = _hoops_SSGPR->next;

				/* _hoops_PSHR _hoops_GAR _hoops_GGR _hoops_IIGPR */
				if (!_hoops_ACGPR)
					_hoops_ACGPR = _hoops_GSGPR();
				if (_hoops_ACGPR) {
					HI_Disentangle (_hoops_RIGC, (_hoops_HPAH *)_hoops_SSGPR);
					_hoops_CIGPR (_hoops_RIGC,_hoops_SSGPR);
					_hoops_HPRH (_hoops_SSGPR);
				}
			} while ((_hoops_SSGPR = _hoops_GGRPR) != null);
			_hoops_SRCP->_hoops_HRRPR (null);
		}
	}

	return _hoops_ACGPR;
}


GLOBAL_FUNCTION void HI_Age_Activity (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				root) {

	if (BIT (root->_hoops_RRHH, _hoops_HGAGR)) {
		/* _hoops_PSHR _hoops_GAR _hoops_GGR _hoops_IIGPR */

		if (_hoops_GSGPR()) {
			HI_Disentangle (_hoops_RIGC, (_hoops_HPAH *)root);
			_hoops_CIGPR (_hoops_RIGC,root);
			_hoops_HPRH (root);
			_hoops_IRRPR();
		}
	}
	else {/* _hoops_PAGA: _hoops_HPPR _hoops_IS _hoops_RGHH _hoops_PASS _hoops_PSHS _hoops_CRRPR _hoops_RPP _hoops_SR _hoops_CHR _hoops_APHR _hoops_PSAP-_hoops_SRRPR (_hoops_GARPR _hoops_RHPP) */
		/* _hoops_API _hoops_HRS _hoops_IHPR _hoops_RPP _hoops_SCH _hoops_RARPR _hoops_IRS _hoops_GGI _hoops_AAHS _hoops_GPP _hoops_RH _hoops_AARPR _hoops_IGIAR _hoops_RH _hoops_PPRRR */
		if (_hoops_GCGPR (_hoops_RIGC, root, root != HOOPS_WORLD->root, false))
			_hoops_IRRPR();
	}
}

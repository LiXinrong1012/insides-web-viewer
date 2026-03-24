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
 * $Id: obf_tmp.txt 1.98 2010-10-06 19:16:14 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

#ifndef DISABLE_DATABASE_EDIT

local void _hoops_SHGHH (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP) 
{

	/* _hoops_CCIH _hoops_GII _hoops_IGS _hoops_PRCHR _hoops_IS _hoops_RH _hoops_CSRIR _hoops_CAGH */

	_hoops_SIRIR *			_hoops_AHSCA = _hoops_RIGC->open_list;

	while (_hoops_AHSCA != null) {
		if (_hoops_AHSCA->_hoops_GCRIR == _hoops_RCRIR &&
			_hoops_AHSCA->info.segment._hoops_PCRIR == _hoops_SRCP) {
			if (_hoops_AHSCA->info.segment._hoops_IGRPR != _hoops_SRCP) {
				_hoops_HPRH (_hoops_AHSCA->info.segment._hoops_IGRPR);
				_hoops_AHSCA->info.segment._hoops_IGRPR = _hoops_SRCP;
				_hoops_PRRH (_hoops_SRCP);
			}
		}
		_hoops_AHSCA = _hoops_AHSCA->next;
	}

	Attribute *	_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR;	/* _hoops_IIP _hoops_IRAP */

	_hoops_CRCP *	_hoops_GIPIA;
	while ((_hoops_GIPIA = (_hoops_CRCP *)_hoops_SRCP->_hoops_RGRPR) != null) {
		/* _hoops_GIGHH _hoops_AIRC */
		_hoops_RGGA (_hoops_ASGPR->next == null) _hoops_ASGPR = _hoops_ASGPR->next;
		if ((_hoops_ASGPR->next = _hoops_GIPIA->_hoops_IPPGR) != null)
			_hoops_ASGPR->next->backlink = &_hoops_ASGPR->next;
		_hoops_GIPIA->_hoops_IPPGR = null;

		/* _hoops_PPR _hoops_GSSC _hoops_CHAPA */
		_hoops_SRCP->_hoops_RGRPR = _hoops_GIPIA->_hoops_RGRPR;
		_hoops_GIPIA->_hoops_RGRPR = null;

		/* _hoops_RIGHH _hoops_PSHHP _hoops_HRPR */
		_hoops_HPRH (_hoops_GIPIA);
	}

	/* _hoops_GGSP _hoops_CCAH _hoops_SAII _hoops_IIGR _hoops_AIRC */
	_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR;
	do	_hoops_ASGPR->owner = _hoops_SRCP;
	_hoops_RGGA ((_hoops_ASGPR = _hoops_ASGPR->next) == null);

	Attribute *	prev[_hoops_CRCCA+1];

	int	ii = _hoops_CRCCA;
	do prev[ii] = null;
	_hoops_RGGA (--ii < 0);

	/* _hoops_CGH _hoops_AASA _hoops_SGSS _hoops_PCPH _hoops_IS _hoops_HASC _hoops_HCSP (_hoops_PPR _hoops_RII?) _hoops_AIRC */

	_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR;
	do if (_hoops_ASGPR->type >= _hoops_RAAGP) {	/* _hoops_PSP _hoops_AIGHH _hoops_PAR _hoops_IAHA */
		int				type;

		/* _hoops_AAAI _hoops_HA (_hoops_SR _hoops_GRS _hoops_ASAC & _hoops_PHIH _hoops_HII "_hoops_GCPC" _hoops_HIGR */
		if ((*_hoops_ASGPR->backlink = _hoops_ASGPR->next) != null)
			_hoops_ASGPR->next->backlink = _hoops_ASGPR->backlink;

		if (prev[type = _hoops_ASGPR->type] != null) {
			/* _hoops_PAGA: _hoops_IIH _hoops_HRGR _hoops_RGAR _hoops_SGIPR _hoops_SPR _hoops_RPPS _hoops_GGR _hoops_PIGHH _hoops_CCH _hoops_HASC _hoops_HHH _hoops_CSSC */
			switch (type) {
				case HK_DRIVER_OPTIONS: {
					_hoops_GAPIR *	_hoops_RAPIR = (_hoops_GAPIR *)_hoops_ASGPR;
					_hoops_GAPIR *	_hoops_HIGHH = (_hoops_GAPIR *)prev[type];

					_hoops_RAPIR->_hoops_IAPRP |= _hoops_HIGHH->_hoops_IAPRP & ~_hoops_RAPIR->_hoops_HAICA;
					_hoops_RAPIR->_hoops_HAICA |= _hoops_HIGHH->_hoops_HAICA;

					_hoops_RAPIR->_hoops_HCARP |= _hoops_HIGHH->_hoops_HCARP & ~_hoops_RAPIR->_hoops_IAICA;
					_hoops_RAPIR->_hoops_IAICA |= _hoops_HIGHH->_hoops_IAICA;
				}	break;


				case HK_USER_OPTIONS: {
					_hoops_HPPIR *	_hoops_IPPIR = (_hoops_HPPIR *)_hoops_ASGPR;
					_hoops_HPPIR *	_hoops_IIGHH = (_hoops_HPPIR *)prev[type];

					Option_Value **	_hoops_CIGHH = &_hoops_IPPIR->option_list;
					Option_Value *	_hoops_SIGHH;
					Option_Value *	_hoops_GCGHH;

					// _hoops_ASIGA
					if ((_hoops_SIGHH = _hoops_IIGHH->option_list)!=null) do {
						_hoops_RGGA ((_hoops_GCGHH = *_hoops_CIGHH) == null ||
								_hoops_GCGHH->type->id >= _hoops_SIGHH->type->id)
							_hoops_CIGHH = &_hoops_GCGHH->next;

						if (_hoops_GCGHH == null ||
							_hoops_GCGHH->type->id > _hoops_SIGHH->type->id) {
							Option_Value *_hoops_RCGHH = _hoops_SIGHH->next;

							/* _hoops_IPS _hoops_RGR _hoops_PIRA _hoops_GGR */

							_hoops_SIGHH->next = null;  /* _hoops_HCPRA _hoops_GHHR _hoops_SCH */

							*_hoops_CIGHH = HI_Copy_Option_List (_hoops_SIGHH);
							(*_hoops_CIGHH)->next = _hoops_GCGHH;

							_hoops_SIGHH->next = _hoops_RCGHH; /* _hoops_PPSI _hoops_SCH _hoops_ISSC */
						}
					} while ((_hoops_SIGHH = _hoops_SIGHH->next) != null);
				}	break;

				case HK_MODELLING_MATRIX: {
					_hoops_ISGI *	_hoops_CPAI = (_hoops_ISGI *)_hoops_ASGPR;
					_hoops_ISGI *	_hoops_ACGHH = (_hoops_ISGI *)prev[type];

					_hoops_HRPA	_hoops_RHSPR;
					HI_Copy_Matrix (&_hoops_CPAI->matrix, &_hoops_RHSPR);
					HI_Multiply_Matrices (&_hoops_RHSPR, &_hoops_ACGHH->matrix, &_hoops_CPAI->matrix);
				}	break;

				case HK_VISIBILITY: {
					_hoops_RSAIR *	vis = (_hoops_RSAIR *)_hoops_ASGPR;
					_hoops_RSAIR *	_hoops_PCGHH = (_hoops_RSAIR *)prev[type];

					vis->value |= _hoops_PCGHH->value & ~vis->mask;
					vis->mask |= _hoops_PCGHH->mask;
				}	break;

				case HK_SELECTABILITY: {
					_hoops_ASAIR *	_hoops_RIRIP = (_hoops_ASAIR *)_hoops_ASGPR;
					_hoops_ASAIR *	_hoops_HCGHH = (_hoops_ASAIR *)prev[type];

					_hoops_RIRIP->_hoops_HHARP |= _hoops_HCGHH->_hoops_HHARP & ~_hoops_RIRIP->mask;
					_hoops_RIRIP->up |= _hoops_HCGHH->up & ~_hoops_RIRIP->mask;
					_hoops_RIRIP->down |= _hoops_HCGHH->down & ~_hoops_RIRIP->mask;
					_hoops_RIRIP->_hoops_RHARP |= _hoops_HCGHH->_hoops_RHARP & ~_hoops_RIRIP->mask;
					_hoops_RIRIP->_hoops_AHARP |= _hoops_HCGHH->_hoops_AHARP & ~_hoops_RIRIP->mask;
					_hoops_RIRIP->mask |= _hoops_HCGHH->mask;
				}	break;

				case HK_HEURISTICS: {
					_hoops_GHAIR *	h = (_hoops_GHAIR *)_hoops_ASGPR;
					_hoops_GHAIR *	_hoops_HPGPR = (_hoops_GHAIR *)prev[type];

					h->value |= _hoops_HPGPR->value & ~h->mask;
					h->mask |= _hoops_HPGPR->mask;
				}	break;

				case HK_RENDERING_OPTIONS: {
					_hoops_RHAIR *	r = (_hoops_RHAIR *)_hoops_ASGPR;
					_hoops_RHAIR *	_hoops_ICGHH = (_hoops_RHAIR *)prev[type];

					r->_hoops_RSIAA |= _hoops_ICGHH->_hoops_RSIAA & ~r->_hoops_SCIAA;
					r->_hoops_SCIAA |= _hoops_ICGHH->_hoops_SCIAA;

					r->_hoops_RRRAP |= _hoops_ICGHH->_hoops_RRRAP & ~r->_hoops_PSHCA;
					r->_hoops_PSHCA |= _hoops_ICGHH->_hoops_PSHCA;

					r->_hoops_GHRAP |= _hoops_ICGHH->_hoops_GHRAP & ~r->_hoops_ISHCA;
					r->_hoops_ISHCA |= _hoops_ICGHH->_hoops_ISHCA;
				}	break;
			}

			_hoops_HPRH (prev[type]);
		}
		prev[type] = _hoops_ASGPR;
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	/* _hoops_PHIH _hoops_HHRPA _hoops_AIRC _hoops_HPP _hoops_GPRR */
	if ((_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR) != null) {
		Attribute **	_hoops_ASRGR = &_hoops_SRCP->_hoops_IPPGR;
		Attribute *		_hoops_HPHCR;

		/* _hoops_CCIH _hoops_PIGHH _hoops_CCH _hoops_RSGR-_hoops_IIGR-_hoops_AIGHH */
		if ((_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR) != null) do {
			if (_hoops_HPHCR->type == _hoops_GRAIR)
				break;
		} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
		if (_hoops_HPHCR == null) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Streaming attribute missing");
			return;
		}
		((_hoops_RRAIR *)_hoops_HPHCR)->_hoops_PHSCA = _hoops_SRCP;

		while (*_hoops_ASRGR != null) _hoops_ASRGR = &(*_hoops_ASRGR)->next;

		ii = _hoops_RAAGP;
		do if (prev[ii] != null) {
			prev[ii]->backlink = _hoops_ASRGR;
			*_hoops_ASRGR = prev[ii];
			_hoops_ASRGR = &(*_hoops_ASRGR)->next;
		} _hoops_RGGA (++ii >= _hoops_CRCCA);
		*_hoops_ASRGR = null;
	}
}


GLOBAL_FUNCTION void HI_Really_Flush_Geometry (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	Integer32				flags)
{
	_hoops_CRCP *				save = _hoops_SRCP;
	Subsegment *			_hoops_SSGPR;
	Integer32				_hoops_CCGHH = 0;

	if (!BIT(flags, _hoops_SGGPP))
		_hoops_CCGHH |= _hoops_SPHGP;

	if (BIT(flags, _hoops_CGGPP))
		_hoops_CCGHH |= _hoops_GPHGP;

	top:;

	_hoops_SRCP->_hoops_RCGC &= ~(_hoops_IRHGP & _hoops_AAHGP | _hoops_CCGHH);

	if (BIT(_hoops_SRCP->_hoops_PHSI, _hoops_GIPSA)) {
		_hoops_SPAGR				_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, _hoops_RIGC->thread_id);
		_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, false);

		if (_hoops_CSC != null) {
			_hoops_RHPSA *	_hoops_HSPIR = _hoops_CSC->_hoops_AHPSA();

			if (_hoops_HSPIR != null) {
				if (BIT(flags, _hoops_CGGPP) &&
					_hoops_HSPIR->_hoops_IHPSA != null)
					_hoops_HSPIR->_hoops_IHPSA->_hoops_PHSI |= _hoops_ISHGP;

				if (BIT(_hoops_SRCP->_hoops_PHSI, _hoops_HSHGP)) {
					_hoops_HSPIR->_hoops_PHPSA = HOOPS_WORLD->_hoops_GPPI;
					HOOPS_WORLD->_hoops_ISRGH++;
				}
			}
		}

		_hoops_SRCP->_hoops_PHSI &= ~_hoops_HSHGP;
	}

	Geometry		*geometry, *_hoops_CCGPR;

	if (BIT(flags, _hoops_CGGPP)) {
		if ((geometry = _hoops_SRCP->geometry) != null) do {
			_hoops_CCGPR = geometry->next;
			/* _hoops_PSHR _hoops_GAR _hoops_GGR _hoops_IIGPR */
			HI_Disentangle (_hoops_RIGC, (_hoops_HPAH *)geometry);
			_hoops_CIGPR (_hoops_RIGC,geometry);
			_hoops_HPRH (geometry);
		} while ((geometry = _hoops_CCGPR) != null);
	}
	else {
		if ((geometry = _hoops_SRCP->geometry) != null) do {
			_hoops_CCGPR = geometry->next;
			if (!BIT (geometry->_hoops_RRHH, _hoops_HGAGR))
				HI_Generic_Delete (_hoops_RIGC, (_hoops_HPAH *)geometry);
		} while ((geometry = _hoops_CCGPR) != null);
	}

	Subsegment	*_hoops_GGRPR;

	if ((_hoops_SSGPR = _hoops_SRCP->_hoops_RGRPR) != null) do {
		_hoops_GGRPR = _hoops_SSGPR->next;

		if (_hoops_SSGPR->type == _hoops_AGRPR) {
			if (!BIT(flags, _hoops_SGGPP))
				HI_Generic_Delete (_hoops_RIGC, (_hoops_HPAH *)_hoops_SSGPR);
			else
				_hoops_SRCP->_hoops_RCGC |= _hoops_SSIGP(_hoops_SSGPR)->_hoops_RCGC;
		}
		else {
			_hoops_CRCP * _hoops_SCGHH = (_hoops_CRCP *)_hoops_SSGPR;

			if (BIT(flags, _hoops_GRGPP) ||
				 (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR) &&
				  (_hoops_SCGHH->geometry != null ||
				   (_hoops_SCGHH->_hoops_RGRPR != null &&
				    ANYBIT (_hoops_SCGHH->_hoops_RCGC, (_hoops_IRHGP & _hoops_AAHGP) | _hoops_CCGHH))))) {

				/* _hoops_SR _hoops_GHHA _hoops_HIH _hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_CPSA _hoops_RRP _hoops_IS, _hoops_SR _hoops_PAIHR. */

				if (_hoops_GGRPR != null)
					HI_Really_Flush_Geometry (_hoops_RIGC, _hoops_SCGHH, flags);
				else {
					_hoops_SRCP = _hoops_SCGHH;
					goto top;
				}
			}
		}
	} while ((_hoops_SSGPR = _hoops_GGRPR) != null);


	/*** _hoops_GHRHA _hoops_CSRIR _hoops_AIRC ***/

	if (BIT (save->_hoops_PHSI, _hoops_PRSIR) && save->_hoops_RGRPR != null)
		_hoops_SHGHH (_hoops_RIGC, save);
}


local void _hoops_GSGHH (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP) {
	Subsegment *			_hoops_SSGPR;

	top:;

	/* _hoops_SRPA _hoops_SGI */

	if (_hoops_SRCP->_hoops_SGRPR() != null || BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GISIR))
		_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_PCPGP|_hoops_RPSIR);

	_hoops_SRCP->_hoops_RCGC &= ~_hoops_HPRRA;	/* _hoops_SSASA! */
	if ((_hoops_SSGPR = _hoops_SRCP->_hoops_RGRPR) != null) do {	/* _hoops_HIH _hoops_GAAP _hoops_ISHP _hoops_CAPP */
		_hoops_CRCP *		ref = _hoops_SSIGP (_hoops_SSGPR);

		_hoops_SRCP->_hoops_RCGC |= ref->_hoops_RCGC;
		if (BIT (_hoops_SRCP->_hoops_RCGC, _hoops_HPRRA))
			break;		/* _hoops_GGHP _hoops_SCH _hoops_ISSC! */
	} while ((_hoops_SSGPR = _hoops_SSGPR->next) != null);


	{	Attribute	*_hoops_HPHCR,
					*_hoops_RSGHH;

		if ((_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR) != null) do {
			Type			type = _hoops_HPHCR->type;

			_hoops_RSGHH = _hoops_HPHCR->next;

			if (type != _hoops_GRAIR) {
				HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, type, _hoops_HPHCR, null);
				HI_Generic_Delete (_hoops_RIGC,(_hoops_HPAH *)_hoops_HPHCR);
			}
		} while ((_hoops_HPHCR = _hoops_RSGHH) != null);
	}

	/* _hoops_GHHA _hoops_APCS _hoops_RGAR _hoops_RPP _hoops_PIGHH */
	if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) {
		if ((_hoops_SSGPR = _hoops_SRCP->_hoops_RGRPR) != null) {
			_hoops_CRCP *		_hoops_ASGHH = (_hoops_CRCP *)_hoops_SSGPR;	// _hoops_PSP _hoops_PSGHH _hoops_SSRR

			if (_hoops_ASGHH->_hoops_IPPGR != null ||
				_hoops_ASGHH->_hoops_RGRPR != null && ANYBIT (_hoops_ASGHH->_hoops_RCGC, _hoops_HPRRA)) {
				/* _hoops_SR _hoops_CHH _hoops_GHHA, _hoops_HIH _hoops_SR _hoops_RGAR _hoops_HS _hoops_SPR _hoops_PSHHP*/

				_hoops_SRCP = _hoops_ASGHH;
				goto top;
			}
		}
	}

	/* _hoops_CGH _hoops_IHIS _hoops_HCR _hoops_CPAP _hoops_CRGR _hoops_HGSI _hoops_CAGH */
}

local void _hoops_HSGHH (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	void *					info) {

	UNREFERENCED (info);

	if (_hoops_SRCP->_hoops_IPPGR != null || ANYBIT (_hoops_SRCP->_hoops_RCGC, _hoops_HPRRA))
		_hoops_GSGHH (_hoops_RIGC, _hoops_SRCP);
}

#endif



HC_INTERFACE void HC_CDECL HC_Flush_Attributes (
	char const *	name)
{
	_hoops_PAPPR context("Flush_Attributes");

#ifdef DISABLE_DATABASE_EDIT
	_hoops_IRPPR ("Database Edit");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Flush_Attributes (%S);\n", name));
	);

	/*** (_hoops_HHGC _hoops_SCIA-_hoops_ISHP _hoops_GIPHR!) ***/
	_hoops_RPPPR();
	HI_For_Each (context, name, true, _hoops_HSGHH, null);
	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Flush_Geometry (
	char const				*name) {

	_hoops_PAPPR context("Flush_Geometry");

#ifdef DISABLE_DATABASE_EDIT
	_hoops_IRPPR ("Database Edit");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Flush_Geometry (%S);\n", name));
	);

	/*** (_hoops_HHGC _hoops_SCIA-_hoops_ISHP _hoops_GIPHR!) ***/
	_hoops_RPPPR();
	HI_For_Each (context, name, true, HI_Flush_Geometry, null);
	_hoops_IRRPR();
#endif
}




GLOBAL_FUNCTION void HI_Flush_Geometry (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	void *					info) {

#ifndef DISABLE_DATABASE_EDIT

	UNREFERENCED (info);

	if (_hoops_SRCP->geometry != null ||
		(_hoops_SRCP->_hoops_RGRPR != null &&
		 ANYBIT (_hoops_SRCP->_hoops_RCGC, (_hoops_IRHGP & _hoops_AAHGP) | _hoops_SPHGP))) {

		_hoops_SIRIR *			_hoops_AHSCA = _hoops_RIGC->open_list;

		if (_hoops_AHSCA  != null) {
			do {
				if (_hoops_AHSCA->_hoops_GCRIR == _hoops_HCRIR) {
					_hoops_CRCP				*owner;

					owner = _hoops_AHSCA->info.geometry._hoops_IGRPR->owner;
					if (owner->type == _hoops_AGCP) owner = owner->owner; /* _hoops_ARSIR */

					do {
						if (owner == _hoops_SRCP) {
							HE_ERROR (HEC_GEOMETRY, HES_OPEN_GEOMETRY,
									Sprintf_P (null, "Can't flush - geometry is still open in '%p'", _hoops_SRCP));
							return;
						}
						owner = owner->owner;
					} while (BIT (owner->_hoops_PHSI, _hoops_PRSIR) && owner->type != _hoops_PRAIR);
				}
			} while ((_hoops_AHSCA = _hoops_AHSCA->next) != null);

			if (BIT (_hoops_SRCP->_hoops_RCGC, T_LINES)) {
				_hoops_AHSCA = _hoops_RIGC->open_list;
				do {
					if (_hoops_AHSCA->_hoops_GCRIR == _hoops_RCRIR &&
						_hoops_AHSCA->info.segment._hoops_ACRIR != null) {
						if (_hoops_AHSCA->info.segment._hoops_IGRPR == _hoops_SRCP) {
							_hoops_HPRH (_hoops_AHSCA->info.segment._hoops_ACRIR);
							_hoops_AHSCA->info.segment._hoops_ACRIR = null;
						}
					}
				} while ((_hoops_AHSCA = _hoops_AHSCA->next) != null);
			}
		}

		/* _hoops_SRPA _hoops_SGI */

		if (BIT (_hoops_SRCP->_hoops_RCGC, T_FACES))
			_hoops_SASIR (_hoops_RIGC, _hoops_SRCP,
									 _hoops_PCPGP|
									 _hoops_CSCCA|
									 _hoops_PISSR|
									 _hoops_RPSIR);
		else
			_hoops_SASIR (_hoops_RIGC, _hoops_SRCP,
									 _hoops_HRCCA|
									 _hoops_PISSR|
									 _hoops_RPSIR);

		HI_Really_Flush_Geometry (_hoops_RIGC, _hoops_SRCP, _hoops_IGGPP);
	}
#endif
}




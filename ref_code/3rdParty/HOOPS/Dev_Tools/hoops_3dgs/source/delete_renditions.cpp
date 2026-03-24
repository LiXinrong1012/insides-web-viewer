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
 * $Id: obf_tmp.txt 1.104 2010-12-06 22:05:40 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "please.h"
#include "hi_proto.h"
#include "hd_proto.h"
#include "adt.h"


local void _hoops_PGRHP (_hoops_AICGP * _hoops_HSPIR, _hoops_AHAGR * _hoops_CSC)
{
	_hoops_AHAGR *			sc;
	_hoops_HICS const &	path = _hoops_CSC->path;

	int i = 0;
	while (_hoops_HSPIR->LookupNthItem(path->key, i, &sc) == VHASH_STATUS_SUCCESS) {
		if (path->count == sc->path->count) {
			int		j;

			for (j=0; j<path->count; ++j)
				if (path->_hoops_PGCGP[j] != sc->path->_hoops_PGCGP[j])
					break;

			if (j == path->count) {	// _hoops_APRAR _hoops_PSSP
				_hoops_HSPIR->RemoveNthItem(path->key, i);
				return;
			}
		}
		i++;
	}
}

GLOBAL_FUNCTION void HI_Delete_Renditions (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	_hoops_PGRPR const *			include,
	Display_Context *		dc,
	bool					_hoops_HGRHP) {

	if (_hoops_SRCP->_hoops_CSC != null) {
		_hoops_SPAGR				_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, _hoops_RIGC->thread_id);
		_hoops_AHAGR *		_hoops_CSC = _hoops_SRCP->_hoops_CSC;
		// _hoops_SRS _hoops_IHSH _hoops_HPGR _hoops_GII _hoops_IGRHP (_hoops_CRAA-_hoops_IIHA) _hoops_RIAH
		_hoops_AICGP *		_hoops_HSPIR = _hoops_CSC->_hoops_IRSGP();
		_hoops_AHAGR **	_hoops_ASRGR = &_hoops_CSC->next;

		while ((_hoops_CSC = *_hoops_ASRGR) != null) {
			_hoops_PGRPR *		st = _hoops_CSC->_hoops_CHICA();
			bool			kill = true;

			if (st != null)
				HI_Delete_Renditions (_hoops_RIGC, (_hoops_CRCP *)st->_hoops_IGRPR, include, dc);

			if ((_hoops_HGRHP || dc != null) && _hoops_CSC->_hoops_APHGA != null) {
				// _hoops_RGAR _hoops_PCHIA _hoops_RPP _hoops_RH _hoops_IHAH _hoops_HRGR _hoops_RIHA _hoops_IS _hoops_RH _hoops_CHIA _hoops_GHCSR
				if (_hoops_HGRHP || _hoops_CSC->_hoops_APHGA->_hoops_SRA == dc) {
					_hoops_GGAGR alter *	_hoops_GHRI = _hoops_PGRCA(_hoops_CSC->_hoops_APHGA->_hoops_SRA->_hoops_GHRI);
					++_hoops_GHRI->_hoops_GAIAP;	// _hoops_RIS _hoops_CGRHP _hoops_ACPH _hoops_ISPR
					_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_SGRHP, _hoops_CSC);
					--_hoops_GHRI->_hoops_GAIAP;
					_hoops_CSC->_hoops_APHGA = null;
				}
				else
					kill = false;
			}

			if (!_hoops_HGRHP && kill && include != null) {
				// _hoops_RGAR _hoops_PCHIA _hoops_RPP _hoops_RH _hoops_IHAH _hoops_HRGR _hoops_RIHA _hoops_IS _hoops_RH _hoops_CHIA _hoops_GCIS
				_hoops_HICS const &	path = _hoops_CSC->path;
				int						j;

				for (j=0; j<path->count; ++j)
					if (path->_hoops_PGCGP[j] == include)
						break;

				if (j == _hoops_CSC->path->count)	// _hoops_PSP _hoops_PSSP
					kill = false;
			}

			if (kill) {
				*_hoops_ASRGR = _hoops_CSC->next;
				_hoops_PGRHP(_hoops_HSPIR, _hoops_CSC);
				delete _hoops_CSC;
			}
			else
				_hoops_ASRGR = &_hoops_CSC->next;
		}

		// _hoops_HA _hoops_CASI _hoops_HGSI _hoops_IHAH
		_hoops_CSC = _hoops_SRCP->_hoops_CSC;

		_hoops_PGRPR *	st = _hoops_CSC->_hoops_CHICA();
		bool		kill = true;

		if (st != null)
			HI_Delete_Renditions (_hoops_RIGC, _hoops_PGRCA(st->_hoops_IGRPR), include, dc, _hoops_HGRHP);

		if ((_hoops_HGRHP || dc != null) && _hoops_CSC->_hoops_APHGA != null) {
			// _hoops_RGAR _hoops_PCHIA _hoops_RPP _hoops_RH _hoops_IHAH _hoops_HRGR _hoops_RIHA _hoops_IS _hoops_RH _hoops_CHIA _hoops_GHCSR
			if (_hoops_HGRHP || _hoops_CSC->_hoops_APHGA->_hoops_SRA == dc) {
				_hoops_HISAA (_hoops_RIGC, _hoops_CSC->_hoops_APHGA->_hoops_SRA->_hoops_GHRI, _hoops_SGRHP, _hoops_CSC);
				_hoops_CSC->_hoops_APHGA = null;
			}
			else
				kill = false;
		}

		if (!_hoops_HGRHP && include != null)
			kill = false;						// _hoops_HGSI _hoops_IHAH _hoops_IIP _hoops_SPASR _hoops_IRS _hoops_SASI _hoops_GCIS _hoops_CRAA _hoops_CARRA

		if (kill && _hoops_CSC->next == null) {		// _hoops_PAH'_hoops_RA _hoops_PCHIA _hoops_RPP _hoops_IIH _hoops_CHR _hoops_HGGC _hoops_IGRHP _hoops_RIAH
			_hoops_SRCP->_hoops_CSC = null;
			delete _hoops_CSC;
		}
	}


	// _hoops_HA _hoops_GPP _hoops_IS _hoops_GII _hoops_CHAPA
	Subsegment *		_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR;
	if (_hoops_GIPIA != null) do {
		if (_hoops_GIPIA->type == _hoops_AGRPR) {
			_hoops_PGRPR *		_hoops_GRRHP = (_hoops_PGRPR *)_hoops_GIPIA;

			HI_Delete_Renditions (_hoops_RIGC, _hoops_PGRCA(_hoops_GRRHP->_hoops_IGRPR), include, dc, _hoops_HGRHP);
		}
		else
			HI_Delete_Renditions (_hoops_RIGC, (_hoops_CRCP *)_hoops_GIPIA, include, dc, _hoops_HGRHP);
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);

	// _hoops_GACC _hoops_HSPAR _hoops_CHAPA _hoops_RCAPR _hoops_PSSAR
	_hoops_GIPIA = _hoops_SRCP->_hoops_PRRPR();
	if (_hoops_GIPIA != null) do {
		if (_hoops_GIPIA->type == _hoops_AGRPR) {
			_hoops_PGRPR *		_hoops_GRRHP = (_hoops_PGRPR *)_hoops_GIPIA;

			HI_Delete_Renditions (_hoops_RIGC, _hoops_PGRCA(_hoops_GRRHP->_hoops_IGRPR), include, dc, _hoops_HGRHP);
		}
		else
			HI_Delete_Renditions (_hoops_RIGC, (_hoops_CRCP *)_hoops_GIPIA, include, dc, _hoops_HGRHP);
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);
}



//_hoops_PSCGP::_hoops_PSCGP () {}
_hoops_AHAGR::_hoops_AHAGR (_hoops_CRCP const * s, _hoops_HICS const & p) : segment (s), path (p) {}


_hoops_AHAGR::~_hoops_AHAGR () {
	_hoops_AIGPR *	_hoops_RIGC;
	_hoops_IIRIR(_hoops_RIGC);

	if (_hoops_APHGA != null) {
		_hoops_HISAA (_hoops_RIGC, _hoops_APHGA->_hoops_SRA->_hoops_GHRI, _hoops_SGRHP, this);
		_hoops_APHGA = null;
	}

#ifndef DISABLE_CUT_GEOMETRY
	_hoops_PHSGA *		_hoops_HHSGA = _hoops_GHSGA();
	if (_hoops_HHSGA != null) {
		_hoops_RRSGA *			_hoops_RRRHP;

		while ((_hoops_RRRHP = _hoops_HHSGA->_hoops_RHSGA) != null) {
			Geometry *	geometry;

			while ((geometry = _hoops_RRRHP->geometry) != null) {
				_hoops_RRRHP->geometry = geometry->next;
				HI_Au_Revoir ((_hoops_HPAH *)geometry);
			}

			_hoops_HHSGA->_hoops_RHSGA = _hoops_RRRHP->next;
			FREE (_hoops_RRRHP, _hoops_RRSGA);
		}

		FREE (_hoops_HHSGA, _hoops_PHSGA);
		_hoops_RGSGP(null);
	}
#endif

#ifndef DISABLE_SIMPLE_SHADOW
	_hoops_CPSS *		_hoops_SPSS = _hoops_CSCGP();
	if (_hoops_SPSS != null) {
		if (_hoops_SPSS->master_rendition != null)
			_hoops_SPSS->master_rendition.release();

		if (_hoops_SPSS->texture != null)
			_hoops_HPRH (_hoops_SPSS->texture);

		if (_hoops_SPSS->image != null) {
			_hoops_HPRH (_hoops_SPSS->image);
			if (_hoops_SPSS->texture) {
				//_hoops_CGPR _hoops_RGCH _hoops_CHR _hoops_CPIC _hoops_SGGR, _hoops_RPP _hoops_RH _hoops_CAGH _hoops_IHAH _hoops_GPGH'_hoops_RA _hoops_RH _hoops_CGHI
				//_hoops_AHAP _hoops_ARRHP _hoops_GPP _hoops_IS _hoops_SCH, _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_AGCGR
				ASSERT (_hoops_SPSS->texture->image->_hoops_HIHI == 1 && _hoops_SPSS->texture->_hoops_HIHI == 1);

				//_hoops_PRRHP _hoops_PCPA _hoops_CHH _hoops_IAII _hoops_SHH _hoops_IRS _hoops_AGCGR _hoops_HPP _hoops_GRII _hoops_CGRPR
				_hoops_HPRH (_hoops_SPSS->texture);
			}
		}

		FREE (_hoops_SPSS, _hoops_CPSS);
		_hoops_ISCGP(null);
	}


	_hoops_GSAR const *	_hoops_HRR = _hoops_GGSGP();
	if (_hoops_HRR != null) {
		_hoops_GSAR const *	_hoops_HRRHP;

		do {
			_hoops_HRRHP = _hoops_HRR->next;
			if (_hoops_HRR->_hoops_PACR)
				_hoops_HPRH (_hoops_HRR->_hoops_PACR);
			FREE (_hoops_HRR, _hoops_GSAR);
		} while ((_hoops_HRR = _hoops_HRRHP) != null);

		_hoops_SSCGP(null);
	}
#endif

#ifndef _hoops_IRRHP
	_hoops_SGSGP *		hl = _hoops_GRSGP();
	if (hl != null) {
		HD_Free_HL_Data (hl);
		_hoops_CGSGP(null);
	}
#endif

	_hoops_PGRPR *		st = _hoops_CHICA();
	if (st != null) {
		HI_Disentangle (_hoops_RIGC, (_hoops_HPAH*)st->_hoops_IGRPR);
		_hoops_HPRH (st);

		_hoops_RASGP (null);	// _hoops_GACC _hoops_CRRHP _hoops_SRRHP
	}

	_hoops_RHPSA *		_hoops_HSPIR = _hoops_AHPSA();
	if (_hoops_HSPIR != null) {
		if (_hoops_HSPIR->_hoops_IHPSA) {
			// _hoops_CIH _hoops_GARHP
			if (HOOPS_WORLD->_hoops_HIPSA->Count() > 0)
				HOOPS_WORLD->_hoops_HIPSA->Remove(_hoops_HSPIR->_hoops_IHPSA);

			_hoops_CRCP alter *_hoops_RARHP = (_hoops_CRCP alter *)_hoops_HSPIR->_hoops_IHPSA->owner;
			_hoops_HPRH(_hoops_RARHP);

			_hoops_HSPIR->_hoops_IHPSA->owner = (_hoops_CRCP alter*)HOOPS_WORLD;
			_hoops_HPRH(_hoops_HSPIR->_hoops_IHPSA);
		}

		FREE (_hoops_HSPIR, _hoops_RHPSA);
		_hoops_HHPSA(null);
	}


	_hoops_HRPA *	_hoops_CPAI = _hoops_ARSGP();
	if (_hoops_CPAI != null) {
		_hoops_CPAI->_hoops_APRA.release();
		FREE (_hoops_CPAI, _hoops_HRPA);
		_hoops_RRSGP(null);
	}


	_hoops_AICGP *		_hoops_HPGPR = _hoops_IRSGP();
	if (_hoops_HPGPR != null) {
		_hoops_AICGP::PairList *	pl = _hoops_HPGPR->GetPairList();
		_hoops_AICGP::Pair *		p;

		while ((p = pl->RemoveFirst()) != null) {
			_hoops_AHAGR *	sc = p->Item();
			delete p;
			delete sc;
		}

		delete pl;
		delete _hoops_HPGPR;
		_hoops_PRSGP (null);
	}

	_hoops_CRPSA *	_hoops_HGIIR = _hoops_SRPSA();
	if (_hoops_HGIIR != null) {
		HI_Remove_Seg_Path_Lookup_Item (_hoops_RIGC, segment);

		delete _hoops_HGIIR;
		_hoops_GAPSA (null);
		_hoops_HPRH (segment);
	}


	_hoops_CRSGP (0);

	if (_hoops_PRIGP != 0)
		_hoops_PRIGP |= 666;
}


_hoops_PHIGP::~_hoops_PHIGP () {
	_hoops_SPIGP *	_hoops_ICI = (_hoops_SPIGP *)_hoops_AACP (_hoops_HHIGP);
	delete _hoops_ICI;
	set (_hoops_HHIGP, null);

	_hoops_IIIGP *	_hoops_SIIGP = (_hoops_IIIGP *)_hoops_AACP (_hoops_RIIGP);
	delete _hoops_SIIGP;
	set (_hoops_RIIGP, null);

	_hoops_HIIGP *	dc = (_hoops_HIIGP *)_hoops_AACP (_hoops_IHIGP);
	delete dc;
	set (_hoops_IHIGP, null);

	if (_hoops_PRIGP != 0)
		_hoops_PRIGP |= 666;
}

GLOBAL_FUNCTION _hoops_AHAGR * HI_Find_Segment_Cache (
	_hoops_CRCP const *			_hoops_SRCP,
	_hoops_HICS const &	path,
	bool					_hoops_IIASA) 
{
	_hoops_AHAGR *			_hoops_CSC = _hoops_SRCP->_hoops_CSC;
	_hoops_AICGP *			_hoops_HSPIR = null;

	if (path) {
		if (_hoops_CSC != null) {
			_hoops_HSPIR = _hoops_CSC->_hoops_IRSGP();

			if (_hoops_HSPIR) {
				_hoops_AHAGR *		sc;
				int					i = 0;

				while (_hoops_HSPIR->LookupNthItem(path->key, i, &sc) == VHASH_STATUS_SUCCESS) {
					if (path->count == sc->path->count) {
						int			j;

						for (j=0; j<path->count; ++j)
							if (path->_hoops_PGCGP[j] != sc->path->_hoops_PGCGP[j])
								break;

						if (j == path->count)	// _hoops_APRAR _hoops_PSSP
							return sc;
					}
					i++;
				}
			}
		}

		if (!_hoops_IIASA)
			return null;
	}

	// _hoops_PSP _hoops_PSSP
	if (_hoops_IIASA) {
		if (_hoops_CSC == null) {
			_hoops_CSC = NEW(_hoops_AHAGR)(_hoops_SRCP, null);
			_hoops_PGRCA(_hoops_SRCP)->_hoops_CSC = _hoops_CSC;
		}

		if (path) {
			if (_hoops_HSPIR == null) {
				_hoops_HSPIR = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_AICGP)(HOOPS_WORLD->memory_pool, 2);
				_hoops_CSC->_hoops_PRSGP(_hoops_HSPIR);
			}

			_hoops_AHAGR *	sc = NEW(_hoops_AHAGR)(_hoops_SRCP, path);

			_hoops_HSPIR->InsertItem(path->key, sc);

			sc->next = _hoops_CSC->next;
			_hoops_CSC->next = sc;

			return sc;
		}
	}

	return _hoops_CSC;
}

GLOBAL_FUNCTION _hoops_AHAGR * HI_Find_Segment_Cache (
	_hoops_CRCP const *			_hoops_SRCP,
	bool					_hoops_IIASA) {

	return HI_Find_Segment_Cache (_hoops_SRCP, _hoops_HICS(), _hoops_IIASA);
}

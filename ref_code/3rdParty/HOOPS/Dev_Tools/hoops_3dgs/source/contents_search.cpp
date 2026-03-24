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
 * $Id: obf_tmp.txt 1.186 2010-10-28 21:32:32 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "searchh.h"
#include "phedron.h"	/* _hoops_IH _hoops_ISHA, _hoops_HSP, _hoops_GPHA _hoops_SIHC */
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "adt.h"


local bool _hoops_GRHCA (
	_hoops_AIGPR *	_hoops_RIGC,
	Attribute *				_hoops_ASGPR,
	_hoops_RRHCA *	_hoops_ARHCA) {
	_hoops_AGHPR *			node;
	bool					_hoops_PRHCA = false;
	bool					_hoops_HRHCA = false;

	//_hoops_IRHCA _hoops_RRP _hoops_GRH _hoops_PRCA _hoops_ARI _hoops_PGGA _hoops_SSIA _hoops_CHR _hoops_IGRC _hoops_PGCR _hoops_CSSC
	// ("_hoops_AIRRR" _hoops_PPR "_hoops_HH _hoops_PAIGR") _hoops_SGS _hoops_HSSRR _hoops_IRS _hoops_RSRA _hoops_CRHCA* _hoops_SRSR
	if (_hoops_ASGPR->type == _hoops_IPAIR) {
		int						_hoops_SRHCA = _hoops_ARHCA->_hoops_GAHCA._hoops_RAHCA;
		bool 					_hoops_PPIHA = false;
		bool 					_hoops_AAHCA, _hoops_PAHCA;

		if (_hoops_RIII(_hoops_SRHCA) != _hoops_SRHCA) {
			// _hoops_RPP _hoops_SR _hoops_CHR _hoops_PHSPR _hoops_IRS _hoops_IAGC _hoops_IH _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_HAHCA, _hoops_CIHPA _hoops_PSAP _hoops_SIH _hoops_SPR _hoops_HPGR _hoops_IRS _hoops_GHIR _hoops_PPR _hoops_GHHA
			int 	_hoops_IAHCA = _hoops_SRHCA;
			int 	_hoops_CAHCA = 0;
			do {
				_hoops_ARHCA->_hoops_GAHCA._hoops_RAHCA = _hoops_RIII(_hoops_SRHCA);
				_hoops_PRHCA |= _hoops_GRHCA (_hoops_RIGC, _hoops_ASGPR, _hoops_ARHCA); //_hoops_GHHA!!
				_hoops_CAHCA |= _hoops_RIII(_hoops_SRHCA);
				_hoops_SRHCA = _hoops_IAHCA & ~_hoops_CAHCA;
			} while (_hoops_SRHCA != 0);
			_hoops_ARHCA->_hoops_GAHCA._hoops_RAHCA = _hoops_IAHCA;
			return _hoops_PRHCA;
		}

		_hoops_CPAIR const *	_hoops_SAHCA = (_hoops_CPAIR const *)_hoops_ASGPR;

		_hoops_PAHCA = BIT (_hoops_ARHCA->_hoops_GAHCA._hoops_RAHCA, _hoops_GPHCA);
		for (int i = 0; i < _hoops_SAHCA->count; i++) {
			_hoops_AAHCA = BIT (_hoops_SAHCA->textures[i]->_hoops_SCR, _hoops_GSR);
			if (_hoops_AAHCA == _hoops_PAHCA) {
				if (_hoops_AAHCA)
					_hoops_HRHCA = true;
				_hoops_PPIHA = true;
				break;
			}
		}
		if (!_hoops_PPIHA)
			return false; //_hoops_HCR _hoops_AIRRR _hoops_CGPR _hoops_SR _hoops_AAPR _hoops_HCHAR _hoops_IH _hoops_AI, _hoops_PAR _hoops_GPHP _hoops_RPHP
	}
	//  _hoops_CRICR _hoops_IS _hoops_GRPR _hoops_RPHCA _hoops_HII _hoops_SSSC
	else if (_hoops_ASGPR->type == _hoops_CPPIR) {
		int						_hoops_SRHCA = _hoops_ARHCA->_hoops_GAHCA._hoops_APHCA;

		if (_hoops_RIII(_hoops_SRHCA) != _hoops_SRHCA) {
			// _hoops_RPP _hoops_SR _hoops_CHR _hoops_PHSPR _hoops_IRS _hoops_IAGC _hoops_IH _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_HAHCA, _hoops_CIHPA _hoops_PSAP _hoops_SIH _hoops_SPR _hoops_HPGR _hoops_IRS _hoops_GHIR _hoops_PPR _hoops_GHHA
			int 	_hoops_IAHCA = _hoops_SRHCA;
			int 	_hoops_CAHCA = 0;
			do {
				_hoops_ARHCA->_hoops_GAHCA._hoops_APHCA = _hoops_RIII(_hoops_SRHCA);
				_hoops_PRHCA |= _hoops_GRHCA (_hoops_RIGC, _hoops_ASGPR, _hoops_ARHCA); //_hoops_GHHA!!
				_hoops_CAHCA |= _hoops_RIII(_hoops_SRHCA);
				_hoops_SRHCA = _hoops_IAHCA & ~_hoops_CAHCA;
			} while (_hoops_SRHCA != 0);
			_hoops_ARHCA->_hoops_GAHCA._hoops_APHCA = _hoops_IAHCA;
			return _hoops_PRHCA;
		}

		_hoops_SPPIR const *		conditions = (_hoops_SPPIR const *)_hoops_ASGPR;

		if (BIT (_hoops_SRHCA, _hoops_PPHCA)) {
			if (conditions->count == 0)
				return false;
		}
		else if (BIT (_hoops_SRHCA, _hoops_HPHCA)) {
			if (conditions->_hoops_ACPGR == null)
				return false;
			_hoops_HRHCA = true;
		}
	}
	else if (_hoops_ASGPR->type == HK_STYLE) {
		int						_hoops_SRHCA = _hoops_ARHCA->_hoops_GAHCA._hoops_IPHCA;

		if (_hoops_RIII(_hoops_SRHCA) != _hoops_SRHCA) {
			// _hoops_RPP _hoops_SR _hoops_CHR _hoops_PHSPR _hoops_IRS _hoops_IAGC _hoops_IH _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_HAHCA, _hoops_CIHPA _hoops_PSAP _hoops_SIH _hoops_SPR _hoops_HPGR _hoops_IRS _hoops_GHIR _hoops_PPR _hoops_GHHA
			int 	_hoops_IAHCA = _hoops_SRHCA;
			int 	_hoops_CAHCA = 0;
			do {
				_hoops_ARHCA->_hoops_GAHCA._hoops_IPHCA = _hoops_RIII(_hoops_SRHCA);
				_hoops_PRHCA |= _hoops_GRHCA (_hoops_RIGC, _hoops_ASGPR, _hoops_ARHCA); //_hoops_GHHA!!
				_hoops_CAHCA |= _hoops_RIII(_hoops_SRHCA);
				_hoops_SRHCA = _hoops_IAHCA & ~_hoops_CAHCA;
			} while (_hoops_SRHCA != 0);
			_hoops_ARHCA->_hoops_GAHCA._hoops_IPHCA = _hoops_IAHCA;
			return _hoops_PRHCA;
		}

		Style const *			style = (Style const *)_hoops_ASGPR;

		if (BIT (_hoops_SRHCA, _hoops_CPHCA)) {
			if (style->_hoops_IGRPR == null)
				return false;
		}
		else if (BIT (_hoops_SRHCA, _hoops_SPHCA)) {
			if (style->_hoops_IGRPR != null)
				return false;
			_hoops_HRHCA = true;
		}
	}

	ZALLOC (node, _hoops_AGHPR);
	node->item = (_hoops_HPAH *)_hoops_ASGPR;
	_hoops_PRRH (_hoops_ASGPR);
	if (_hoops_ASGPR->type == HK_STYLE)
		node->key = _hoops_ASGPR->key;
	else
		node->key = _hoops_AIRIR(_hoops_ASGPR->owner);
	node->type = _hoops_ASGPR->type;
	node->_hoops_AGRI = _hoops_HRHCA;

	*_hoops_ARHCA->item._hoops_ASRGR = node;
	_hoops_ARHCA->item._hoops_ASRGR = &node->next;
	++_hoops_RIGC->_hoops_GHHCA->count;

	return true;
}


local bool _hoops_RHHCA (
	_hoops_AIGPR *	_hoops_RIGC,
	Geometry *				geometry,
	_hoops_RRHCA *	_hoops_ARHCA) {
	_hoops_AGHPR *			node;
	int						type;
	bool					_hoops_PRHCA = false;

	do {
		type = geometry->type;

		if (_hoops_ARHCA->_hoops_AHHCA ||
			(type == _hoops_ICIP &&
			 (((Light const *)geometry)->_hoops_PRR == _hoops_H && _hoops_ARHCA->_hoops_CGR._hoops_PHHCA ||
			  ((Light const *)geometry)->_hoops_PRR == _hoops_C && _hoops_ARHCA->_hoops_CGR.point ||
			  ((Light const *)geometry)->_hoops_PRR == _hoops_I && _hoops_ARHCA->_hoops_CGR._hoops_HHHCA ||
			  ((Light const *)geometry)->_hoops_PRR == _hoops_S && _hoops_ARHCA->_hoops_CGR.area)) ||
			(type == _hoops_SIIP &&
			 (!BIT(geometry->_hoops_RRHH, _hoops_IHHCA) && _hoops_ARHCA->_hoops_CHHCA[_hoops_SIIP] ||
			  BIT(geometry->_hoops_RRHH, _hoops_IHHCA) && _hoops_ARHCA->_hoops_SHHCA)) ||
			(type == _hoops_HIIP && _hoops_ARHCA->_hoops_CHHCA[_hoops_PIIP]) ||
			(type == _hoops_PIRS && _hoops_ARHCA->_hoops_CHHCA[_hoops_PCIP]) ||
			type != _hoops_ICIP && type != _hoops_SIIP && _hoops_ARHCA->_hoops_CHHCA[type]) {
			// _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_GPRR _hoops_SR _hoops_HHGC
			if (_hoops_ARHCA->_hoops_RAIHR == _hoops_GIHCA ||
				BIT (geometry->_hoops_RRHH, _hoops_PASIR) && _hoops_ARHCA->_hoops_RAIHR == _hoops_RIHCA ||
				!BIT (geometry->_hoops_RRHH, _hoops_PASIR) && _hoops_ARHCA->_hoops_RAIHR == _hoops_AIHCA) {
				// _hoops_CPCP _hoops_SPASR _hoops_IAGC
				if (type != _hoops_IIIP || _hoops_ARHCA->_hoops_PIHCA == _hoops_GIHCA ||
					(BIT (geometry->_hoops_RRHH, _hoops_HIHCA) && _hoops_ARHCA->_hoops_PIHCA == _hoops_RIHCA) ||
					(!BIT (geometry->_hoops_RRHH, _hoops_HIHCA) && _hoops_ARHCA->_hoops_PIHCA == _hoops_AIHCA)) {
					// _hoops_HAR _hoops_IIHCA _hoops_PAR _hoops_IIHCA _hoops_CIHCA _hoops_SPASR
					if (BIT (geometry->_hoops_RRHH, _hoops_CHRIR) && !_hoops_ARHCA->_hoops_SIHCA) {
						if (type == _hoops_HIIP) {
							_hoops_SHRIR const *	_hoops_GIRIR = (_hoops_SHRIR const *)geometry;
							int					count = -_hoops_GIRIR->count / 2;

							for (int i=0; i<count; ++i) {
								ZALLOC (node, _hoops_AGHPR);
								node->item = (_hoops_HPAH *)geometry;
								_hoops_PRRH (geometry);
								node->key = HOOPS_WORLD->_hoops_GCHCA.table[_hoops_GIRIR->mapping[i] & ~_hoops_RIRIR].key;
								node->type = _hoops_PIIP;

								*_hoops_ARHCA->item._hoops_ASRGR = node;
								_hoops_ARHCA->item._hoops_ASRGR = &node->next;
								++_hoops_RIGC->_hoops_GHHCA->count;
								_hoops_PRHCA = true;

								if (_hoops_ARHCA->_hoops_RCHCA)
									return true;
							}
						}
						else if (type == _hoops_PIRS) {
							_hoops_GRPGR const *	_hoops_CPAI = (_hoops_GRPGR const *)geometry;
							int					count = _hoops_CPAI->count;

							for (int i=0; i<count; ++i) {
								ZALLOC (node, _hoops_AGHPR);
								node->item = (_hoops_HPAH *)geometry;
								_hoops_PRRH (geometry);
								node->key = HOOPS_WORLD->_hoops_GCHCA.table[_hoops_CPAI->mapping[i] & ~_hoops_RIRIR].key;
								node->type = _hoops_PCIP;

								*_hoops_ARHCA->item._hoops_ASRGR = node;
								_hoops_ARHCA->item._hoops_ASRGR = &node->next;
								++_hoops_RIGC->_hoops_GHHCA->count;
								_hoops_PRHCA = true;

								if (_hoops_ARHCA->_hoops_RCHCA)
									return true;
							}
						}
					}
					else {
						ZALLOC (node, _hoops_AGHPR);
						node->item = (_hoops_HPAH *)geometry;
						_hoops_PRRH (geometry);
						node->key = geometry->key;
						node->type = geometry->type;

						*_hoops_ARHCA->item._hoops_ASRGR = node;
						_hoops_ARHCA->item._hoops_ASRGR = &node->next;
						++_hoops_RIGC->_hoops_GHHCA->count;
						_hoops_PRHCA = true;

						if (_hoops_ARHCA->_hoops_RCHCA)
							return true;
					}
				}
			}
		}
		if ((_hoops_ARHCA->_hoops_AHHCA || _hoops_ARHCA->_hoops_CHHCA[(int)HK_STRING_CURSOR]) && type == _hoops_AGCP) {
			_hoops_PIGPR *		cursor;

			if ((cursor = ((_hoops_HACC *)geometry)->_hoops_AAPGR) != null) do {
				ZALLOC (node, _hoops_AGHPR);
				node->item = (_hoops_HPAH *)cursor;
				_hoops_PRRH (cursor);
				node->key = cursor->key;
				node->type = cursor->type;

				*_hoops_ARHCA->item._hoops_ASRGR = node;
				_hoops_ARHCA->item._hoops_ASRGR = &node->next;
				++_hoops_RIGC->_hoops_GHHCA->count;
				_hoops_PRHCA = true;

				if (_hoops_ARHCA->_hoops_RCHCA)
					return true;
			} while ((cursor = (_hoops_PIGPR *) cursor->next) != null);
		}
	} while ((geometry = geometry->next) != null);

	return _hoops_PRHCA;
}


local void _hoops_ACHCA (
	_hoops_GACR alter *	dl,
	_hoops_RRHCA *	_hoops_ARHCA) {
	_hoops_AGHPR *			node;

	ZALLOC (node, _hoops_AGHPR);
	node->item = (_hoops_HPAH *)dl;
	_hoops_PRRH (dl);
	node->key = -1;
	node->type = dl->type;

	*_hoops_ARHCA->item._hoops_ASRGR = node;
	_hoops_ARHCA->item._hoops_ASRGR = &node->next;
}


local void _hoops_PCHCA (
	_hoops_PGAIR alter *		_hoops_HGAIR,
	_hoops_RRHCA *	_hoops_ARHCA) {
	_hoops_AGHPR *			node;

	ZALLOC (node, _hoops_AGHPR);
	node->item = (_hoops_HPAH *)_hoops_HGAIR;
	_hoops_PRRH (_hoops_HGAIR);
	node->key = _hoops_AIRIR(_hoops_HGAIR->owner);
	node->type = _hoops_HGAIR->type;

	*_hoops_ARHCA->item._hoops_ASRGR = node;
	_hoops_ARHCA->item._hoops_ASRGR = &node->next;
}


/* _hoops_HCHCA _hoops_PPR _hoops_GPHHR _hoops_HCR _hoops_RH _hoops_AIRI _hoops_CPCI _hoops_SGS _hoops_SGHPA _hoops_PSAP _hoops_SPR _hoops_SAGHR _hoops_GPSPR _hoops_IIGR _hoops_CPAP */
local int _hoops_ICHCA (
	Geometry const *		geom,
	_hoops_RRHCA *	_hoops_ARHCA) {
	_hoops_GACR *			dl;
	int						count = 0;

	switch (geom->type) {
		case _hoops_SCIP:
		case _hoops_GSIP: {
			Polyhedron const *	phon = (Polyhedron const *)geom;
			Tristrip const *	ts = phon->tristrips;
			Polyedge const *	pe = phon->_hoops_SHGPR;
			Polymarker const *	pm = phon->_hoops_GIGPR;

			while (ts) {
				if (ts->_hoops_GAHA) {
					dl = ts->_hoops_GAHA;
					while (dl) {
						_hoops_ACHCA (dl, _hoops_ARHCA);
						count++;
						dl = dl->next;
					}
				}
				ts = ts->next;
			}
			while (pe) {
				if (pe->_hoops_GAHA) {
					dl = pe->_hoops_GAHA;
					while (dl) {
						_hoops_ACHCA (dl, _hoops_ARHCA);
						count++;
						dl = dl->next;
					}
				}
				pe = pe->next;
			}
			while (pm) {
				if (pm->_hoops_GAHA) {
					dl = pm->_hoops_GAHA;
					while (dl) {
						_hoops_ACHCA (dl, _hoops_ARHCA);
						count++;
						dl = dl->next;
					}
				}
				pm = pm->next;
			}
			pe = phon->_hoops_CHGPR;
			while (pe) {
				if (pe->_hoops_GAHA) {
					dl = pe->_hoops_GAHA;
					while (dl) {
						_hoops_ACHCA (dl, _hoops_ARHCA);
						count++;
						dl = dl->next;
					}
				}
				pe = pe->next;
			}
			if (phon->_hoops_HGAIR != null) {
				Geometry const *g;

				for (int i = 0; i < _hoops_IGAIR; i++) {
					g = phon->_hoops_HGAIR->data[i];
					while (g) {
						_hoops_ICHCA (g, _hoops_ARHCA);
						count++;
						g = g->next;
					}
				}
			}
			break;
		}
		case _hoops_CSIP: {
			PolyCylinder const *_hoops_HSPIR = (PolyCylinder const *)geom;

			for (dl = _hoops_HSPIR->_hoops_SGHIR; dl != null; dl = dl->next) {
				_hoops_ACHCA (dl, _hoops_ARHCA);
				count++;
			}
			for (dl = _hoops_HSPIR->_hoops_GRHIR; dl != null; dl = dl->next) {
				_hoops_ACHCA (dl, _hoops_ARHCA);
				count++;
			}
			break;
		}
		case _hoops_HGCP: {
			Image const *image = (Image const *)geom;

			for (dl = image->_hoops_GAHA; dl != null; dl = dl->next) {
				_hoops_ACHCA (dl, _hoops_ARHCA);
				count++;
			}
			break;
		}
		case _hoops_PRCP: {
			_hoops_APPGR const *surface = (_hoops_APPGR const *)geom;
			if (surface->_hoops_IPRI)
				count += _hoops_ICHCA ((Geometry const *)surface->_hoops_IPRI, _hoops_ARHCA);
			break;
		}
		/* _hoops_SHIR: */
			/* _hoops_AA _hoops_ISAP */
	}
	return count;
}

local bool _hoops_CCHCA(_hoops_HIR * list, int index)
{
	while (list) {
		if (list->_hoops_HGA == index)
			return true;
		list=list->next;
	}
	return false;
}

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
								int index = _hoops_ARHCA->_hoops_GAHCA.color._hoops_GSHCA[i];

								if (ANYBIT (_hoops_ARHCA->_hoops_GAHCA.color._hoops_HAA[i], _hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA) &&
									(index == -1 || _hoops_CCHCA(_hoops_ICSGA->_hoops_ISHIR._hoops_SCA, index)))
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

			if (_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_ASHCA & _hoops_AHAIR->_hoops_SCIAA ||
				_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA.simple & _hoops_AHAIR->_hoops_PSHCA ||
				_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_HSHCA & _hoops_AHAIR->_hoops_ISHCA ||
				BIT(_hoops_AHAIR->_hoops_SCIAA, _hoops_CSHCA) &&
				(_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_SSHCA & _hoops_AHAIR->_hoops_SSHCA.mask) ||
				BIT(_hoops_AHAIR->_hoops_SCIAA, _hoops_GGICA) &&
				(_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_RGICA & _hoops_AHAIR->_hoops_RGICA.mask) ||
				BIT(_hoops_AHAIR->_hoops_SCIAA, _hoops_AGICA) &&
				(_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_PGICA & _hoops_AHAIR->_hoops_HGICA) ||

				(_hoops_AHAIR->_hoops_AIAIR != null &&
				 BIT(_hoops_AHAIR->_hoops_SCIAA, _hoops_IGICA) &&
				 (_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_CGICA & _hoops_AHAIR->_hoops_AIAIR->mask)) ||

				(_hoops_AHAIR->_hoops_PRSI != null &&
				 BIT(_hoops_AHAIR->_hoops_SCIAA, _hoops_SGICA) &&
				 (_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_GRICA & _hoops_AHAIR->_hoops_PRSI->mask)) ||

				(_hoops_AHAIR->_hoops_HHAIR != null &&
				 (BIT(_hoops_AHAIR->_hoops_SCIAA, _hoops_RRICA) &&
				  (_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_GHSS & _hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask) ||
				  BIT(_hoops_AHAIR->_hoops_SCIAA, _hoops_ARICA) &&
				  (_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_PRIGA & _hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.mask))) ||

				(_hoops_AHAIR->_hoops_IIAIR != null &&
				 BIT(_hoops_AHAIR->_hoops_SCIAA, _hoops_PRICA) &&
				 (_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_IIAIR & _hoops_AHAIR->_hoops_IIAIR->mask)) ||

				(_hoops_AHAIR->geometry != null &&
				 (BIT(_hoops_AHAIR->_hoops_SCIAA, _hoops_HRICA) &&
				  (_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA.geometry & _hoops_AHAIR->geometry->mask) ||
				  BIT(_hoops_AHAIR->_hoops_SCIAA, _hoops_IRICA) &&
				  (_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_APPI & _hoops_AHAIR->geometry->_hoops_APPI.mask) ||
				  BIT(_hoops_AHAIR->_hoops_SCIAA, _hoops_CRICA) &&
				  (_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_PSRIR & _hoops_AHAIR->geometry->_hoops_PSRIR.mask) ||
				  BIT(_hoops_AHAIR->_hoops_SCIAA, _hoops_SRICA) &&
				  (_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA._hoops_GAICA & _hoops_AHAIR->geometry->_hoops_GAICA.mask))) ||

				(_hoops_AHAIR->locks != null &&
				 (_hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA.locks._hoops_IPPGR & _hoops_AHAIR->locks->normal.mask._hoops_IPPGR ||
				  _hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA.locks.color & _hoops_AHAIR->locks->normal.mask.color ||
				  _hoops_ARHCA->_hoops_GAHCA._hoops_RSHCA.locks._hoops_RGP & _hoops_AHAIR->locks->normal.mask._hoops_RGP))

				) {
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

				// _hoops_ASIGA
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


GLOBAL_FUNCTION void HI_Link_Contents (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	void *					info) {
	_hoops_RRHCA *	_hoops_ARHCA = (_hoops_RRHCA *)info;
	_hoops_AGHPR *			node;
	int						type;

	if (_hoops_ARHCA->_hoops_RCHCA &&
		_hoops_RIGC->_hoops_GHHCA->count > 0)
		return;

	if (_hoops_ARHCA->_hoops_IPICA) {
		ZALLOC (node, _hoops_AGHPR);
		node->item = (_hoops_HPAH *)_hoops_SRCP;
		_hoops_PRRH(_hoops_SRCP);
		node->key = _hoops_SRCP->key;
		node->type = _hoops_SRCP->type;

		*_hoops_ARHCA->item._hoops_ASRGR = node;
		_hoops_ARHCA->item._hoops_ASRGR = &node->next;
		++_hoops_RIGC->_hoops_GHHCA->count;

		if (_hoops_ARHCA->_hoops_RCHCA)
			return;
	}


	top:;

	if ((_hoops_ARHCA->_hoops_AHHCA || _hoops_ARHCA->_hoops_CPICA) && _hoops_SRCP->_hoops_IPPGR != null) {
		Attribute	*_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR;

		do {
			type = _hoops_ASGPR->type;

			if (_hoops_ARHCA->_hoops_AHHCA && type != HK_DRIVER || 
				_hoops_ARHCA->_hoops_CHHCA[type] ||
				_hoops_SCHCA (_hoops_ARHCA, _hoops_ASGPR)) {
				if (_hoops_GRHCA (_hoops_RIGC, _hoops_ASGPR, _hoops_ARHCA) && _hoops_ARHCA->_hoops_RCHCA)
					return;
			}
		} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
	}

	if ((_hoops_ARHCA->_hoops_AHHCA || _hoops_ARHCA->_hoops_SPICA) && _hoops_SRCP->geometry != null) {
		if (_hoops_RHHCA (_hoops_RIGC, _hoops_SRCP->geometry, _hoops_ARHCA) && _hoops_ARHCA->_hoops_RCHCA)
			return;
	}

	if ((_hoops_ARHCA->_hoops_AHHCA ||
		 _hoops_ARHCA->_hoops_CHHCA[(int)_hoops_AGRPR] || _hoops_ARHCA->_hoops_CHHCA[(int)_hoops_IRCP]) &&
		_hoops_SRCP->_hoops_RGRPR != null) {
		Subsegment	*_hoops_SSGPR = _hoops_SRCP->_hoops_RGRPR;

		do {
			type = _hoops_SSGPR->type;

			if (type == _hoops_IRCP && BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) {
				_hoops_SRCP = (_hoops_CRCP *)_hoops_SSGPR;
				goto top;
			}

			if (_hoops_ARHCA->_hoops_AHHCA || _hoops_ARHCA->_hoops_CHHCA[type]) {
				if (_hoops_ARHCA->_hoops_RAIHR == _hoops_GIHCA ||
					BIT (_hoops_SSGPR->_hoops_RRHH, _hoops_PASIR) && _hoops_ARHCA->_hoops_RAIHR == _hoops_RIHCA ||
					!BIT (_hoops_SSGPR->_hoops_RRHH, _hoops_PASIR) && _hoops_ARHCA->_hoops_RAIHR == _hoops_AIHCA) {
					ZALLOC (node, _hoops_AGHPR);
					node->item = (_hoops_HPAH *)_hoops_SSGPR;
					_hoops_PRRH (_hoops_SSGPR);
					node->key = _hoops_SSGPR->key;
					node->type = _hoops_SSGPR->type;

					*_hoops_ARHCA->item._hoops_ASRGR = node;
					_hoops_ARHCA->item._hoops_ASRGR = &node->next;
					++_hoops_RIGC->_hoops_GHHCA->count;

					if (_hoops_ARHCA->_hoops_RCHCA)
						return;
				}
			}
		} while ((_hoops_SSGPR = _hoops_SSGPR->next) != null);
	}

	if ((_hoops_ARHCA->_hoops_GHICA || _hoops_ARHCA->_hoops_RHICA) && _hoops_SRCP->_hoops_SGRPR() != null) {
		Xref *		_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR();

		do if (!BIT (_hoops_AHICA->owner->_hoops_RRHH, _hoops_HIRIR)) {
			type = _hoops_AHICA->type;

			if (type == _hoops_AGRPR && _hoops_ARHCA->_hoops_GHICA ||
				type == HK_STYLE && _hoops_ARHCA->_hoops_RHICA) {
				ZALLOC (node, _hoops_AGHPR);
				node->item = (_hoops_HPAH *)_hoops_AHICA;
				_hoops_PRRH (_hoops_AHICA);
				node->key = _hoops_AHICA->key;
				node->type = _hoops_AHICA->type;

				*_hoops_ARHCA->item._hoops_ASRGR = node;
				_hoops_ARHCA->item._hoops_ASRGR = &node->next;
				++_hoops_RIGC->_hoops_GHHCA->count;

				if (_hoops_ARHCA->_hoops_RCHCA)
					return;
			}
		} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);
	}

	if (_hoops_ARHCA->_hoops_PHICA) {

		_hoops_RPAPA * _hoops_APAPA = HOOPS_WORLD->_hoops_PPAPA->Lookup(_hoops_SRCP);

		if (_hoops_APAPA != null) {
			_hoops_RPAPA::UniqueCursor *	uc = _hoops_APAPA->GetUniqueCursor();
			_hoops_PHIP const *	_hoops_RRA;
			while((_hoops_RRA = uc->Peek()) != null) {
				ZALLOC (node, _hoops_AGHPR);
				node->item = (_hoops_HPAH *)_hoops_RRA;
				_hoops_PRRH (_hoops_RRA);
				node->key = _hoops_RRA->key;
				node->type = _hoops_RRA->type;

				*_hoops_ARHCA->item._hoops_ASRGR = node;
				_hoops_ARHCA->item._hoops_ASRGR = &node->next;
				++_hoops_RIGC->_hoops_GHHCA->count;

				if (_hoops_ARHCA->_hoops_RCHCA)
					break;
				uc->Advance();
			}
			delete uc;

			if (_hoops_ARHCA->_hoops_RCHCA && _hoops_RIGC->_hoops_GHHCA->count > 0)
				return;
		}
	}
		
	if ((_hoops_ARHCA->_hoops_AHHCA || _hoops_ARHCA->_hoops_CHHCA[(int)_hoops_AGAIR]) && _hoops_SRCP->_hoops_SSRIR() != null) {
		if (!BIT (_hoops_SRCP->_hoops_SSRIR()->_hoops_RRHH, _hoops_HGAGR)) {
			_hoops_PCHCA (_hoops_SRCP->_hoops_SSRIR(), _hoops_ARHCA);
			++_hoops_RIGC->_hoops_GHHCA->count;

			if (_hoops_ARHCA->_hoops_RCHCA)
				return;
		}
	}
	if (_hoops_ARHCA->_hoops_AHHCA || _hoops_ARHCA->_hoops_CHHCA[(int)_hoops_HCIIR]) {
		{
			_hoops_SPAGR					_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, _hoops_RIGC->thread_id);
			_hoops_GACR alter *	dl;
			_hoops_AHAGR *			_hoops_CSC = _hoops_SRCP->_hoops_CSC;

			if (_hoops_SRCP->_hoops_CSC != null) do {
				_hoops_GPAGR	_hoops_RPAGR = _hoops_SRCP->_hoops_CSC->_hoops_PHAGR();

				if (_hoops_RPAGR != null) {
					if ((dl = _hoops_RPAGR->_hoops_GAHA) != null) do {
						_hoops_ACHCA (dl, _hoops_ARHCA);
						++_hoops_RIGC->_hoops_GHHCA->count;

						if (_hoops_ARHCA->_hoops_RCHCA)
							return;
					} while ((dl = dl->next) != null);
					if ((dl = _hoops_RPAGR->_hoops_HHICA) != null) do {
						_hoops_ACHCA (dl, _hoops_ARHCA);
						++_hoops_RIGC->_hoops_GHHCA->count;

						if (_hoops_ARHCA->_hoops_RCHCA)
							return;
					} while ((dl = dl->next) != null);
					if ((dl = _hoops_RPAGR->_hoops_IHAGR) != null) do {
						_hoops_ACHCA (dl, _hoops_ARHCA);
						++_hoops_RIGC->_hoops_GHHCA->count;

						if (_hoops_ARHCA->_hoops_RCHCA)
							return;
					} while ((dl = dl->next) != null);
				}
			} while ((_hoops_CSC = _hoops_CSC->next) != null);
		}
		if (_hoops_SRCP->geometry != null) {
			Geometry const *	g = _hoops_SRCP->geometry;
			while (g) {
				_hoops_RIGC->_hoops_GHHCA->count += _hoops_ICHCA (g, _hoops_ARHCA);
				g = g->next;
			}
		}
	}

	if (_hoops_ARHCA->_hoops_IHICA) {
		_hoops_SPAGR					_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, _hoops_RIGC->thread_id);
		_hoops_AHAGR const *	_hoops_CSC = _hoops_SRCP->_hoops_CSC;

		if (_hoops_CSC != null) do {
			_hoops_PGRPR const *			st;

			if ((st = _hoops_CSC->_hoops_CHICA()) != null) {
				ZALLOC (node, _hoops_AGHPR);
				node->item = (_hoops_HPAH *)st;
				_hoops_PRRH (st);
				node->key = st->key;
				node->type = st->type;

				*_hoops_ARHCA->item._hoops_ASRGR = node;
				_hoops_ARHCA->item._hoops_ASRGR = &node->next;
				++_hoops_RIGC->_hoops_GHHCA->count;

				if (_hoops_ARHCA->_hoops_RCHCA)
					return;
			}
		} while ((_hoops_CSC = _hoops_CSC->next) != null);
	}
}


GLOBAL_FUNCTION void HI_Free_Search_List (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_AGHPR *				node) {
	_hoops_AGHPR *				next;
	UNREFERENCED (_hoops_RIGC);

	if (node != null) do {
		next = node->next;
		_hoops_HPRH (node->item);
		FREE (node, _hoops_AGHPR);
	} while ((node = next) != null);
}


#ifndef DISABLE_SEARCH

local void _hoops_SHICA (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_RRHCA *		_hoops_ARHCA) {
	_hoops_AGHPR					head;
	_hoops_AGHPR *				node = &head;
	int							count = 0;

#	define		_hoops_GIICA(_hoops_RIICA, _hoops_AIICA) do {				\
					ZALLOC (node->next, _hoops_AGHPR);	\
					node = node->next;					\
					node->item = (_hoops_HPAH *)_hoops_RIICA;	\
					_hoops_PRRH (_hoops_RIICA);						\
					node->key = -1;						\
					node->type = _hoops_AIICA;				\
					++count;							\
				} while (0)

	if (_hoops_RIGC->open_list != null) switch (_hoops_RIGC->open_list->_hoops_GCRIR) {
		/* _hoops_RGAR _hoops_GPIHR _hoops_GGR _hoops_SAGHR _hoops_CGSI */

		case _hoops_HCRIR:		{
			Geometry *	geometry = _hoops_RIGC->open_list->info.geometry._hoops_IGRPR;

			if (_hoops_ARHCA->_hoops_IPICA) {
				ZALLOC (node->next, _hoops_AGHPR);
				node = node->next;
				node->item = (_hoops_HPAH *)geometry;
				_hoops_PRRH (node->item);
				node->key = geometry->key;
				node->type = geometry->type;
				++count;
			}

			if ((_hoops_ARHCA->_hoops_AHHCA || _hoops_ARHCA->_hoops_CPICA) &&
				geometry->_hoops_IPPGR != null) {

				Attribute *	_hoops_ASGPR = geometry->_hoops_IPPGR;
				do {
					int	type = _hoops_ASGPR->type;

					if (_hoops_ARHCA->_hoops_AHHCA || _hoops_ARHCA->_hoops_CHHCA[type] ||
						_hoops_SCHCA (_hoops_ARHCA, _hoops_ASGPR)) {
						ZALLOC (node, _hoops_AGHPR);
						node->item = (_hoops_HPAH *)_hoops_ASGPR;
						node->key = _hoops_AIRIR(geometry);
						node->type = _hoops_ASGPR->type;
						_hoops_PRRH (_hoops_ASGPR);

						*_hoops_ARHCA->item._hoops_ASRGR = node;
						_hoops_ARHCA->item._hoops_ASRGR = &node->next;
						++_hoops_RIGC->_hoops_GHHCA->count;
					}
				} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
			}

			if (_hoops_ARHCA->_hoops_PHICA) {

				_hoops_RPAPA * _hoops_APAPA = HOOPS_WORLD->_hoops_PPAPA->Lookup(geometry);

				if (_hoops_APAPA != null) {
					_hoops_RPAPA::UniqueCursor *	uc = _hoops_APAPA->GetUniqueCursor();
					_hoops_PHIP const *	_hoops_RRA;
					while((_hoops_RRA = uc->Peek()) != null) {
						ZALLOC (node, _hoops_AGHPR);
						node->item = (_hoops_HPAH *)_hoops_RRA;
						_hoops_PRRH (_hoops_RRA);
						node->key = _hoops_RRA->key;
						node->type = _hoops_RRA->type;

						*_hoops_ARHCA->item._hoops_ASRGR = node;
						_hoops_ARHCA->item._hoops_ASRGR = &node->next;
						++_hoops_RIGC->_hoops_GHHCA->count;

						uc->Advance();
					}
					delete uc;
				}
			}

		}	break;

		case _hoops_RSRIR: {
				_hoops_HPAH *	thing = _hoops_RIGC->open_list->info._hoops_PRSI._hoops_IGRPR;
				int			level = _hoops_RIGC->open_list->info._hoops_PRSI.offset;

				if (level == 0) {
					if (_hoops_ARHCA->_hoops_IPICA) {
					  ZALLOC (node->next, _hoops_AGHPR);
					  node = node->next;
					  node->item = thing;
					  _hoops_PRRH (thing);
					  node->key = _hoops_AIRIR(thing->owner);
					  node->type = thing->type;
					  ++count;
					}
				}
				else {
					_hoops_PGAIR *	_hoops_HGAIR = null;

					switch (thing->type) {
						case _hoops_SCIP:
						case _hoops_GSIP:
							_hoops_HGAIR = ((Polyhedron *)thing)->_hoops_HGAIR;
							break;
						case _hoops_IRCP:
							_hoops_HGAIR = ((_hoops_CRCP *)thing)->_hoops_SSRIR();
							break;
						default:
							HE_ERROR (HEC_INTERNAL_ERROR, HES_MOST_RECENT_OPEN,
									"unrecognized LOD owner");
					}
					if (_hoops_HGAIR != null) {
						Geometry *	geometry;

						level -= 1;
						if ((geometry = _hoops_HGAIR->data[level]) != null)
							_hoops_RHHCA (_hoops_RIGC, geometry, _hoops_ARHCA);
					}
				}
		}	break;

#ifndef DISABLE_GEOMETRY_ATTRIBUTES
		case _hoops_SCRIR: {
			Polyhedron *					_hoops_IPRI = _hoops_RIGC->open_list->info._hoops_IPRI._hoops_IGRPR;
			int								offset = _hoops_RIGC->open_list->info._hoops_IPRI.offset;

			if (_hoops_ARHCA->_hoops_IPICA)
				_hoops_GIICA (_hoops_IPRI, _hoops_PIICA);

			if (_hoops_IPRI->type == _hoops_CSIP) {
				PolyCylinder *				_hoops_HSPIR = (PolyCylinder *) _hoops_IPRI;
				_hoops_AGHIR *	_hoops_PGHIR = _hoops_HSPIR->_hoops_RGHIR;

#  ifndef _hoops_GCGHR
			if (_hoops_PGHIR != null) {
				_hoops_CGHIR			flags = _hoops_PGHIR->flags[offset];

				if (_hoops_ARHCA->_hoops_CHHCA[(int)HK_COLOR] && ANYBIT (flags, _hoops_GPPRA|_hoops_RPPRA))
					_hoops_GIICA (_hoops_HSPIR, HK_COLOR);
			}
#  endif
			}
			else {
				Local_Vertex_Flags *		_hoops_HIICA = _hoops_IPRI->local_vertex_attributes.flags;

				if (_hoops_HIICA != null) {
					Local_Vertex_Flags		flags = _hoops_HIICA[offset];

#  ifndef _hoops_IIICA
					if (_hoops_ARHCA->_hoops_CHHCA[(int)HK_VISIBILITY] && ANYBIT (flags, _hoops_CIICA))
						_hoops_GIICA (_hoops_IPRI, HK_VISIBILITY);
#  endif

#  ifndef _hoops_GCGHR
					if (_hoops_ARHCA->_hoops_CHHCA[(int)HK_COLOR] && ANYBIT (flags, _hoops_CPPRA))
						_hoops_GIICA (_hoops_IPRI, HK_COLOR);
#  endif

#  ifndef _hoops_CSGHR
					if (_hoops_ARHCA->_hoops_CHHCA[(int)HK_MARKER_SYMBOL] && BIT (flags, _hoops_SIICA))
						_hoops_GIICA (_hoops_IPRI, HK_MARKER_SYMBOL);

					if (_hoops_ARHCA->_hoops_CHHCA[(int)HK_MARKER_SIZE] && BIT (flags, _hoops_GCICA))
						_hoops_GIICA (_hoops_IPRI, HK_MARKER_SIZE);
#  endif

#  ifndef _hoops_HCGHR
					if (_hoops_ARHCA->_hoops_RGHIR._hoops_ICHA && BIT (flags, LVA_EXPLICIT_NORMAL))
						_hoops_GIICA (_hoops_IPRI, _hoops_RCICA);
#  endif

#  ifndef DISABLE_TEXTURING
					if (_hoops_ARHCA->_hoops_RGHIR._hoops_ACICA && BIT (flags, _hoops_ASAPA))
						_hoops_GIICA (_hoops_IPRI, _hoops_PCICA);
#  endif
				}
			}
		}	break;

		case _hoops_CCRIR: {
			Polyhedron *				_hoops_IPRI = _hoops_RIGC->open_list->info._hoops_IPRI._hoops_IGRPR;
			int							offset = _hoops_RIGC->open_list->info._hoops_IPRI.offset;
			_hoops_GHHPR *			_hoops_HIICA = _hoops_IPRI->_hoops_IHHPR.flags;

			if (_hoops_ARHCA->_hoops_IPICA)
				_hoops_GIICA (_hoops_IPRI, _hoops_HCICA);

			if (_hoops_HIICA != null) {
				_hoops_GHHPR		flags = _hoops_HIICA[offset];

#  ifndef _hoops_IIICA
				if (_hoops_ARHCA->_hoops_CHHCA[(int)HK_VISIBILITY] && ANYBIT (flags, _hoops_ICICA))
					_hoops_GIICA (_hoops_IPRI, HK_VISIBILITY);
#  endif

#  ifndef _hoops_GCGHR
				if (_hoops_ARHCA->_hoops_CHHCA[(int)HK_COLOR] && ANYBIT (flags, _hoops_CCICA))
					_hoops_GIICA (_hoops_IPRI, HK_COLOR);
#  endif

#  ifndef _hoops_RGIPR
				if (_hoops_ARHCA->_hoops_CHHCA[(int)HK_EDGE_WEIGHT] && BIT (flags, _hoops_SCICA))
					_hoops_GIICA (_hoops_IPRI, HK_EDGE_WEIGHT);

				if (_hoops_ARHCA->_hoops_CHHCA[(int)HK_EDGE_PATTERN] && BIT (flags, _hoops_GPGI))
					_hoops_GIICA (_hoops_IPRI, HK_EDGE_PATTERN);
#  endif
			}
		}	break;

		case _hoops_ICRIR: {
			Polyhedron *				_hoops_IPRI = _hoops_RIGC->open_list->info._hoops_IPRI._hoops_IGRPR;
			int							offset = _hoops_RIGC->open_list->info._hoops_IPRI.offset;

			if (_hoops_ARHCA->_hoops_IPICA)
				_hoops_GIICA (_hoops_IPRI, _hoops_GSICA);

			if (_hoops_IPRI->type == _hoops_CSIP) {
				PolyCylinder *			_hoops_HSPIR = (PolyCylinder *) _hoops_IPRI;

#  ifndef _hoops_HCGHR
				if (_hoops_ARHCA->_hoops_RGHIR._hoops_ICHA) {
					if (offset == 0 && BIT (_hoops_HSPIR->flags, _hoops_RSICA) ||
						offset == 1 && BIT (_hoops_HSPIR->flags, _hoops_ASICA))
						_hoops_GIICA (_hoops_HSPIR, _hoops_RCICA);
				}
#  endif
			}
			else {
				_hoops_GIIPR *		_hoops_HIICA = _hoops_IPRI->local_face_attributes._hoops_CHHPR();

				if (_hoops_HIICA != null) {
					_hoops_GIIPR	flags = _hoops_HIICA[offset];

#  ifndef _hoops_IIICA
					if (_hoops_ARHCA->_hoops_CHHCA[(int)HK_VISIBILITY] && ANYBIT (flags, _hoops_HRAPA))
						_hoops_GIICA (_hoops_IPRI, HK_VISIBILITY);
#  endif

#  ifndef _hoops_GCGHR
					if (_hoops_ARHCA->_hoops_CHHCA[(int)HK_COLOR] && ANYBIT (flags, _hoops_IACHR))
						_hoops_GIICA (_hoops_IPRI, HK_COLOR);
#  endif

#  ifndef _hoops_PGPHR
					if (_hoops_ARHCA->_hoops_CHHCA[(int)HK_FACE_PATTERN] && BIT (flags, _hoops_HAGI))
						_hoops_GIICA (_hoops_IPRI, HK_FACE_PATTERN);
#  endif

#  ifndef _hoops_HCGHR
					if (_hoops_ARHCA->_hoops_RGHIR._hoops_PRHH && BIT (flags, LFA_EXPLICIT_NORMAL))
						_hoops_GIICA (_hoops_IPRI, _hoops_RCICA);
#  endif
				}
			}
		}	break;
#endif
	}

	if (count > 0) {
		node->next = null;
		*_hoops_ARHCA->item._hoops_ASRGR = head.next;
		_hoops_ARHCA->item._hoops_ASRGR = &node->next;
		_hoops_RIGC->_hoops_GHHCA->count += count;
	}
}

local bool _hoops_PSICA (Geometry const *geom)
{
	switch (geom->type) {
		case _hoops_SCIP:
		case _hoops_GSIP: {
			Polyhedron const *phon = (Polyhedron const *)geom;
			Tristrip const *ts = phon->tristrips;

			if (ts != null && ts->_hoops_GAHA != null)
				return true;
			if (phon->_hoops_HGAIR != null) {
				int i;
				Geometry const *g;

				for (i = 0; i < _hoops_IGAIR; i++) {
					g = phon->_hoops_HGAIR->data[i];
					while (g) {
						if (_hoops_PSICA(g))
							return true;
						g = g->next;
					}
				}
			}
			return false;
		}
		case _hoops_CSIP: {
			PolyCylinder const *_hoops_HSPIR = (PolyCylinder const *)geom;
			if (_hoops_HSPIR->_hoops_SGHIR ||
				_hoops_HSPIR->_hoops_GRHIR)
				return true;
			return false;
		}
		case _hoops_HGCP: {
			Image const *image = (Image const *)geom;
			if (image->_hoops_GAHA)
				return true;
		}
		/* _hoops_SHIR: */
			/* _hoops_AA _hoops_ISAP */
	}
	return false;
}

#endif


HC_INTERFACE void HC_CDECL HC_Begin_Contents_Search (
	char const *			segspec,
	char const *			types) {
	_hoops_SSPPR *			_hoops_GGHPR;
	_hoops_RRHCA		_hoops_ARHCA;
	_hoops_PAPPR context("Begin_Contents_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Begin_Contents_Search () */\n");
		++HOOPS_WORLD->_hoops_ISPPR;
	);


	/* _hoops_GGCR _hoops_GIPHR _hoops_RGSPR _hoops_SRS _hoops_HIS _hoops_ACGR/_hoops_HCSH _hoops_HRGR _hoops_IHRI _hoops_PRGI _hoops_CCA _hoops_AHCI _hoops_CIIA */
	ZALLOC (_hoops_GGHPR, _hoops_SSPPR);
	_hoops_GGHPR->prev = context->_hoops_GHHCA;
	context->_hoops_GHHCA = _hoops_GGHPR;

	if (!HI_Decipher_Type_Names (context, types, &_hoops_ARHCA))
		return;

	_hoops_CSPPR();

	_hoops_ARHCA.item._hoops_ASRGR = &_hoops_GGHPR->list;

	if (context->open_list != null &&
		context->open_list->_hoops_GCRIR != _hoops_RCRIR) {
		char const				*_hoops_SIIS = segspec;

		/* _hoops_ASSS "." _hoops_PAR "" _hoops_IS _hoops_ACAHR _hoops_IS _hoops_PA _hoops_SGS'_hoops_GRI _hoops_IGS */
		while (*_hoops_SIIS == ' ') ++_hoops_SIIS;
		if (*_hoops_SIIS == '.') {
			++_hoops_SIIS;
			while (*_hoops_SIIS == ' ') ++_hoops_SIIS;
		}
		if (*_hoops_SIIS == '\0') {
			_hoops_SHICA (context, &_hoops_ARHCA);
			goto done;
		}
	}

	HI_For_Each (context, segspec, true, HI_Link_Contents, (_hoops_HPAH *)&_hoops_ARHCA);

  done:
	_hoops_IRRPR();

	HI_Clean_FCD (&_hoops_ARHCA);
#endif
}


HC_INTERFACE bool HC_CDECL HC_Find_Contents (
	char *					type,
	Key *					key) {
	_hoops_PAPPR context("Find_Contents");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Find_Contents () */\n");
	);

	if (context->_hoops_GHHCA == null) {
		HE_ERROR (HEC_CONTENT, HES_INACTIVE_SEARCH, "No contents search is active");
		return false;
	}

	bool result = false;

	_hoops_CSPPR();
	_hoops_AGHPR	*	list;
	while ((list = context->_hoops_GHHCA->list) != null) {
		_hoops_HPAH *	item = list->item;
		Key			_hoops_HSICA = list->key;
		Type		_hoops_ISICA = list->type;
		bool		_hoops_AGRI = list->_hoops_AGRI;

		context->_hoops_GHHCA->list = list->next;
		FREE (list, _hoops_AGHPR);

		if (item != null && BIT (item->_hoops_RRHH, _hoops_HGAGR))
			_hoops_HPRH (item);
		else {
			if (key)
				*key = _hoops_HSICA;

			if (type != null) {
				if (_hoops_ISICA == _hoops_SIIP && BIT(item->_hoops_RRHH, _hoops_IHHCA))
					HI_Return_Chars(type, -1, "infinite ray", 12);
				else if (_hoops_ISICA == _hoops_IPAIR && _hoops_AGRI)
					HI_Return_Chars (type, -1, "shaders", 7);
				else if (_hoops_ISICA == _hoops_CPPIR && _hoops_AGRI)
					HI_Return_Chars (type, -1, "conditional action", 18);
				else if (_hoops_ISICA == HK_STYLE && _hoops_AGRI)
					HI_Return_Chars (type, -1, "named style", 11);
				else
					HI_Show_Type_Name (_hoops_ISICA, type, -1);
			}

			if (item != null)
				_hoops_HPRH (item);

			result = true;
			break;
		}
	}
	_hoops_IRRPR();
#endif
	return result;
}



HC_INTERFACE void HC_CDECL HC_Reverse_Contents_Search ()
{
	_hoops_PAPPR context("Reverse_Contents_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/*HC_Reverse_Contents_Search();*/\n");
	);

	if (context->_hoops_GHHCA == null) {
		HE_ERROR (HEC_CONTENT, HES_INACTIVE_SEARCH, "No contents search is active");
		return;
	}

	_hoops_AGHPR	*	list = context->_hoops_GHHCA->list;

	_hoops_AGHPR	*	_hoops_IRRS = null;
	while (list != null) {
		_hoops_AGHPR	*	current = list;
		list = list->next;
		current->next = _hoops_IRRS;
		_hoops_IRRS = current;
	}
	context->_hoops_GHHCA->list = _hoops_IRRS;

#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Contents_Count (
	int *				count)
{
	_hoops_PAPPR context("Show_Contents_Count");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Contents_Count () */\n");
	);

	_hoops_SSPPR *	_hoops_GGHPR = context->_hoops_GHHCA;

	if (_hoops_GGHPR == null) {
		HE_ERROR (HEC_CONTENT, HES_INACTIVE_SEARCH, "No contents search is active");
		*count = 0;
	}
	else
		*count = _hoops_GGHPR->count;
#endif
}


HC_INTERFACE void HC_CDECL HC_End_Contents_Search (void)
{
	_hoops_PAPPR context("End_Contents_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("/* HC_End_Contents_Search () */\n");
	);

	_hoops_SSPPR *	_hoops_GGHPR;

	if ((_hoops_GGHPR = context->_hoops_GHHCA) == null) {
		HE_ERROR (HEC_CONTENT, HES_END_WITHOUT_BEGIN_SEARCH, "End without Begin");
		return;
	}

	HI_Free_Search_List (context, _hoops_GGHPR->list);

	context->_hoops_GHHCA = _hoops_GGHPR->prev;
	FREE (_hoops_GGHPR, _hoops_SSPPR);
#endif
}

#ifndef DISABLE_SEARCH
void _hoops_CSICA (
	_hoops_AIGPR *	_hoops_RIGC,
	 _hoops_CRCP *				_hoops_SRCP,
	 _hoops_RRHCA *	_hoops_ARHCA) {
	_hoops_SPAGR					_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, _hoops_RIGC->thread_id);
	_hoops_AHAGR *			_hoops_CSC = _hoops_SRCP->_hoops_CSC;

	if (_hoops_CSC != null) do {
		_hoops_GPAGR		_hoops_RPAGR = _hoops_CSC->_hoops_PHAGR();

		if (_hoops_RPAGR != null) {
			if (_hoops_RPAGR->_hoops_GAHA != null)
				++_hoops_ARHCA->item.count;
			if (_hoops_RPAGR->_hoops_HHICA != null)
				++_hoops_ARHCA->item.count;
			if (_hoops_RPAGR->_hoops_IHAGR != null)
				++_hoops_ARHCA->item.count;
		}
	} while ((_hoops_CSC = _hoops_CSC->next) != null);
}
#endif


GLOBAL_FUNCTION void HI_Count_Contents (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	void *					info) {
#ifndef DISABLE_SEARCH
	_hoops_RRHCA *	_hoops_ARHCA = (_hoops_RRHCA *)info;
	int						type;

	UNREFERENCED(_hoops_RIGC);

	if (_hoops_ARHCA->_hoops_IPICA) {
		++_hoops_ARHCA->item.count;
		if (_hoops_ARHCA->_hoops_RCHCA)
			return;
	}

	if (_hoops_ARHCA->_hoops_SSICA && BIT (_hoops_SRCP->_hoops_RRHH, _hoops_GGCCA)) {
		++_hoops_ARHCA->item.count;
		if (_hoops_ARHCA->_hoops_RCHCA)
			return;
	}

	top:;

	if (_hoops_ARHCA->bounding && !_hoops_SRCP->bounding._hoops_HICAR()) {
		++_hoops_ARHCA->item.count;
		if (_hoops_ARHCA->_hoops_RCHCA)
			return;
	}

	if ((_hoops_ARHCA->_hoops_AHHCA || _hoops_ARHCA->_hoops_CPICA) && _hoops_SRCP->_hoops_IPPGR != null) {
		Attribute const *		_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR;

		do {
			type = _hoops_ASGPR->type;

			if (_hoops_ARHCA->_hoops_AHHCA && type != HK_DRIVER || 
				_hoops_ARHCA->_hoops_CHHCA[type] ||
				_hoops_SCHCA (_hoops_ARHCA, _hoops_ASGPR)) {
				++_hoops_ARHCA->item.count;
				if (_hoops_ARHCA->_hoops_RCHCA)
					return;
			}
		} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
	}

	if ((_hoops_ARHCA->_hoops_AHHCA || _hoops_ARHCA->_hoops_SPICA) && _hoops_SRCP->geometry != null) {
		Geometry const *		geometry = _hoops_SRCP->geometry;

		do {
			type = geometry->type;

			if (_hoops_ARHCA->_hoops_AHHCA ||
				(type == _hoops_ICIP &&
				 (((Light const *)geometry)->_hoops_PRR == _hoops_H && _hoops_ARHCA->_hoops_CGR._hoops_PHHCA ||
				  ((Light const *)geometry)->_hoops_PRR == _hoops_C && _hoops_ARHCA->_hoops_CGR.point ||
				  ((Light const *)geometry)->_hoops_PRR == _hoops_I && _hoops_ARHCA->_hoops_CGR._hoops_HHHCA ||
				  ((Light const *)geometry)->_hoops_PRR == _hoops_S && _hoops_ARHCA->_hoops_CGR.area)) ||
				(type == _hoops_SIIP &&
				 (!BIT(geometry->_hoops_RRHH, _hoops_IHHCA) && _hoops_ARHCA->_hoops_CHHCA[_hoops_SIIP] ||
				  BIT(geometry->_hoops_RRHH, _hoops_IHHCA) && _hoops_ARHCA->_hoops_SHHCA)) ||
				(type == _hoops_HIIP && _hoops_ARHCA->_hoops_CHHCA[_hoops_PIIP]) ||
				(type == _hoops_PIRS && _hoops_ARHCA->_hoops_CHHCA[_hoops_PCIP]) ||
				type != _hoops_ICIP && type != _hoops_SIIP && _hoops_ARHCA->_hoops_CHHCA[type]) {
				// _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_GPRR _hoops_SR _hoops_HHGC
				if (_hoops_ARHCA->_hoops_RAIHR == _hoops_GIHCA ||
					BIT (geometry->_hoops_RRHH, _hoops_PASIR) && _hoops_ARHCA->_hoops_RAIHR == _hoops_RIHCA ||
					!BIT (geometry->_hoops_RRHH, _hoops_PASIR) && _hoops_ARHCA->_hoops_RAIHR == _hoops_AIHCA) {
					// _hoops_CPCP _hoops_SPASR _hoops_IAGC
					if (type != _hoops_IIIP || _hoops_ARHCA->_hoops_PIHCA == _hoops_GIHCA ||
						(BIT (geometry->_hoops_RRHH, _hoops_HIHCA) && _hoops_ARHCA->_hoops_PIHCA == _hoops_RIHCA) ||
						(!BIT (geometry->_hoops_RRHH, _hoops_HIHCA) && _hoops_ARHCA->_hoops_PIHCA == _hoops_AIHCA)) {
						// _hoops_HAR _hoops_IIHCA _hoops_PAR _hoops_IIHCA _hoops_CIHCA _hoops_SPASR
						if (BIT (geometry->_hoops_RRHH, _hoops_CHRIR)) {
							// _hoops_RGGAR _hoops_AGSAR _hoops_GHCA _hoops_SHH _hoops_IPIH _hoops_RHPA
							int		_hoops_RGCCA = 0;

							if (type == _hoops_HIIP)
								_hoops_RGCCA = -((_hoops_SHRIR *)geometry)->count / 2;
							else if (type == _hoops_PIRS)
								_hoops_RGCCA = ((_hoops_GRPGR *)geometry)->count;

							if (_hoops_RGCCA > 0) {
								_hoops_ARHCA->item.count += _hoops_RGCCA;

								if (_hoops_ARHCA->_hoops_RCHCA)
									return;
							}
						}
						else {
							++_hoops_ARHCA->item.count;

							if (_hoops_ARHCA->_hoops_RCHCA)
								return;
						}
					}
				}
			}
			if ((_hoops_ARHCA->_hoops_AHHCA || _hoops_ARHCA->_hoops_CHHCA[(int)HK_STRING_CURSOR]) &&
				type == _hoops_AGCP) {
				_hoops_PIGPR				*cursor;

				if ((cursor = ((_hoops_HACC const *)geometry)->_hoops_AAPGR) != null) do {
					++_hoops_ARHCA->item.count;
					if (_hoops_ARHCA->_hoops_RCHCA)
						return;
				} while ((cursor = (_hoops_PIGPR *) cursor->next) != null);
			}
		} while ((geometry = geometry->next) != null);
	}

	if ((_hoops_ARHCA->_hoops_AHHCA ||
		 _hoops_ARHCA->_hoops_CHHCA[(int)_hoops_AGRPR] || _hoops_ARHCA->_hoops_CHHCA[(int)_hoops_IRCP]) &&
		_hoops_SRCP->_hoops_RGRPR != null) {
		Subsegment	*_hoops_SSGPR = _hoops_SRCP->_hoops_RGRPR;

		do {
			type = _hoops_SSGPR->type;

			if (type == _hoops_IRCP && BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) {
				_hoops_SRCP = (_hoops_CRCP *)_hoops_SSGPR;
				goto top;
			}

			if (_hoops_ARHCA->_hoops_AHHCA || _hoops_ARHCA->_hoops_CHHCA[type]) {
				if (_hoops_ARHCA->_hoops_RAIHR == _hoops_GIHCA ||
					(BIT (_hoops_SSGPR->_hoops_RRHH, _hoops_PASIR) &&
					 _hoops_ARHCA->_hoops_RAIHR == _hoops_RIHCA) ||
					(!BIT (_hoops_SSGPR->_hoops_RRHH, _hoops_PASIR) &&
					 _hoops_ARHCA->_hoops_RAIHR == _hoops_AIHCA)) {
					++_hoops_ARHCA->item.count;
					if (_hoops_ARHCA->_hoops_RCHCA)
						return;
				}
			}
		} while ((_hoops_SSGPR = _hoops_SSGPR->next) != null);
	}

	if ((_hoops_ARHCA->_hoops_GHICA || _hoops_ARHCA->_hoops_RHICA) && _hoops_SRCP->_hoops_SGRPR() != null) {
		Xref *		_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR();

		do {
			type = _hoops_AHICA->type;

			if (type == _hoops_AGRPR && _hoops_ARHCA->_hoops_GHICA ||
				type == HK_STYLE && _hoops_ARHCA->_hoops_RHICA)
				++_hoops_ARHCA->item.count;
		} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);
	}

	if (_hoops_ARHCA->_hoops_PHICA) {
		_hoops_RPAPA * _hoops_APAPA = HOOPS_WORLD->_hoops_PPAPA->Lookup(_hoops_SRCP);

		if (_hoops_APAPA != null) 
			_hoops_ARHCA->item.count += _hoops_APAPA->Count();
	}

	if (_hoops_ARHCA->_hoops_AHHCA ||
		_hoops_ARHCA->_hoops_CHHCA[(int)_hoops_AGAIR] ||
		_hoops_ARHCA->_hoops_CHHCA[(int)_hoops_HCIIR]) {
		if (_hoops_ARHCA->_hoops_CHHCA[(int)_hoops_AGAIR]) {
			/* _hoops_AGCCA _hoops_IS _hoops_CAGH-_hoops_PAPA _hoops_PGCCA _hoops_RGAR */
			_hoops_PGAIR const *		_hoops_HGAIR;

			if ((_hoops_HGAIR = _hoops_SRCP->_hoops_SSRIR()) != null) {
				int				i;

				for (i=0; i<_hoops_IGAIR; i++)
					if (_hoops_HGAIR->data[i] != null)
						++_hoops_ARHCA->item.count;
			}
		}
		if (_hoops_ARHCA->_hoops_CHHCA[(int)_hoops_HCIIR]) {
			Geometry		*geometry = _hoops_SRCP->geometry;

			while (geometry) {
				if (_hoops_PSICA (geometry))
					++_hoops_ARHCA->item.count;
				geometry = geometry->next;
			}

			/* _hoops_RPR _hoops_CAGH-_hoops_PAPA _hoops_AIRI _hoops_CPCI */
			_hoops_CSICA (_hoops_RIGC, _hoops_SRCP, _hoops_ARHCA);
		}
	}


	if (_hoops_ARHCA->_hoops_IHICA) {
		_hoops_SPAGR						_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, _hoops_RIGC->thread_id);
		_hoops_AHAGR const	*		_hoops_CSC = _hoops_SRCP->_hoops_CSC;

		if (_hoops_CSC != null) do {
			if (_hoops_CSC->_hoops_CHICA() != null)
				++_hoops_ARHCA->item.count;
		} while ((_hoops_CSC = _hoops_CSC->next) != null);
	}

	if (_hoops_ARHCA->_hoops_HGCCA)
		_hoops_ARHCA->item.count += _hoops_SRCP->_hoops_IGCCA;
#endif
}


#define _hoops_CGCCA 4096

HC_INTERFACE void HC_CDECL HC_Flush_Contents (
	char const *			segspec,
	char const *			types)
{
	_hoops_PAPPR context("Flush_Contents");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Flush_Contents (%S, %S);\n", segspec, types));
	);

	_hoops_RRHCA		_hoops_ARHCA;
	_hoops_AGHPR *			list;
	int						pass = 0;
	_hoops_AGHPR *			_hoops_SGCCA = null;

	/* _hoops_PRGI _hoops_RPP _hoops_AHCI _hoops_GPRR, _hoops_CCPP _hoops_PIH _hoops_HRPR _hoops_HIS _hoops_GRCCA _hoops_PPPPR'_hoops_RA _hoops_CIPGA */
	_hoops_SSPPR *	_hoops_GGHPR;
	ZALLOC (_hoops_GGHPR, _hoops_SSPPR);
	_hoops_GGHPR->prev = context->_hoops_GHHCA;
	context->_hoops_GHHCA = _hoops_GGHPR;

	if (HI_Decipher_Type_Names (context, types, &_hoops_ARHCA)) {
		_hoops_ARHCA.item._hoops_ASRGR = &_hoops_GGHPR->list;
		_hoops_ARHCA._hoops_SIHCA = true;	// _hoops_PAH _hoops_AGGAR _hoops_RGGAR _hoops_AGSAR _hoops_SSPP

		if (context->open_list != null && context->open_list->_hoops_GCRIR == _hoops_RSRIR) {
			char const *	_hoops_SIIS = segspec;
			_hoops_HPAH *		thing = context->open_list->info._hoops_PRSI._hoops_IGRPR;
			int				level = context->open_list->info._hoops_PRSI.offset;
			_hoops_PGAIR *		_hoops_HGAIR = null;

			/* _hoops_ASSS "." _hoops_PAR "" _hoops_IS _hoops_ACAHR _hoops_IS _hoops_PA _hoops_SGS'_hoops_GRI _hoops_IGS */
			while (*_hoops_SIIS == ' ') ++_hoops_SIIS;
			if (*_hoops_SIIS == '.') {
				++_hoops_SIIS;
				while (*_hoops_SIIS == ' ') ++_hoops_SIIS;
			}
			switch (thing->type) {
				case _hoops_SCIP:
				case _hoops_GSIP:
					_hoops_HGAIR = ((Polyhedron *)thing)->_hoops_HGAIR;
					break;
				case _hoops_IRCP:
					_hoops_HGAIR = ((_hoops_CRCP *)thing)->_hoops_SSRIR();
					break;
				default:
					HE_ERROR (HEC_INTERNAL_ERROR, HES_MOST_RECENT_OPEN, "unrecognized LOD owner (2)");
			}
			if (*_hoops_SIIS == '\0' && _hoops_HGAIR != null && level > 0) {
				Geometry *	geom;
				bool		_hoops_RRCCA = false;

				level -= 1;	 /* 0 _hoops_HRGR _hoops_RH _hoops_AIRA _hoops_RAAA, _hoops_ARCCA->_hoops_PIH _hoops_PSPI _hoops_HSPP _hoops_CCA _hoops_PRCCA 1 */
				if ((geom = _hoops_HGAIR->data[level]) != null) do {
					Geometry *			victim = geom;

					geom = geom->next;

					if (_hoops_ARHCA._hoops_AHHCA || _hoops_ARHCA._hoops_CHHCA[(int)victim->type]) {
						_hoops_RRCCA = true;
						if ((*victim->backlink = victim->next) != null)
							victim->next->backlink = victim->backlink;

						HI_Au_Revoir ((_hoops_HPAH *)victim);
					}
				} while (geom != null);

				if (_hoops_RRCCA)
					_hoops_SASIR (context, thing, _hoops_HRCCA);
			}
		}
		else if (context->open_list != null && context->open_list->_hoops_GCRIR == _hoops_HCRIR) {
			Geometry const *g = context->open_list->info.geometry._hoops_IGRPR;

			if (_hoops_ARHCA._hoops_AHHCA || _hoops_ARHCA._hoops_CHHCA[(int)_hoops_HCIIR]) {
				context->_hoops_GHHCA->count += _hoops_ICHCA (g, &_hoops_ARHCA);
			}
			if (_hoops_ARHCA._hoops_AHHCA || _hoops_ARHCA._hoops_CHHCA[(int)_hoops_AGAIR]) {
				if (g->type == _hoops_SCIP || g->type == _hoops_GSIP) {
					Polyhedron const *phon = (Polyhedron const *) g;
					if (phon->_hoops_HGAIR) {
						_hoops_PCHCA (phon->_hoops_HGAIR, &_hoops_ARHCA);
						++context->_hoops_GHHCA->count;
					}
				}
				else if (g->type == _hoops_PRCP) {
					_hoops_APPGR const *surface = (_hoops_APPGR const *)g;
					if (surface->_hoops_IPRI && surface->_hoops_IPRI->_hoops_HGAIR) {
						_hoops_PCHCA (surface->_hoops_IPRI->_hoops_HGAIR, &_hoops_ARHCA);
						++context->_hoops_GHHCA->count;
					}
				}
			}
		}
		else {
			HI_For_Each (context, segspec, true, HI_Link_Contents, (_hoops_HPAH *)&_hoops_ARHCA);
		}

		/* _hoops_HA _hoops_SGS _hoops_CIPH _hoops_HRGR _hoops_CCHHR, _hoops_CASI _hoops_SCH _hoops_GH */
		for (;;) {
			Key				_hoops_IGIC[_hoops_CGCCA];
			int				_hoops_IRCCA = 0;

			while ((list = _hoops_GGHPR->list) != null) {
				_hoops_HPAH		*item = list->item;

				_hoops_GGHPR->list = list->next;
				if (list->item->type == HK_DRIVER && pass == 0) {
					/* _hoops_GASA: _hoops_SPSIR _hoops_HS _hoops_GRH _hoops_CIPP (_hoops_IAS._hoops_ISHI. _hoops_AIRI _hoops_CPCI)
					 * _hoops_SGS _hoops_PHHR _hoops_ISHP _hoops_CCA _hoops_CAPR.  _hoops_CGP _hoops_GII _hoops_IIGR _hoops_AGAP _hoops_CGSI _hoops_IHPS _hoops_IS
					 * _hoops_GACC _hoops_SHH _hoops_GGR _hoops_RH _hoops_HIGR, _hoops_SR _hoops_HHS _hoops_HS _hoops_SPGC _hoops_RPP
					 * _hoops_RH _hoops_RHPP _hoops_SAGGR _hoops_PGHPR _hoops_SRS. */
					list->next = _hoops_SGCCA;
					_hoops_SGCCA = list;
				}
				else {
					if (!BIT (item->_hoops_RRHH, _hoops_HGAGR) || item->type == _hoops_HCIIR) {
						Type			type = item->type;
						_hoops_HPAH		*owner = item->owner;

						if (type <= _hoops_CRCCA && type != HK_STYLE) {
							_hoops_CRCP				*_hoops_SRCP = (_hoops_CRCP *) owner;

							_hoops_RPPPR();
							HI_Redraw_Attribute (context, _hoops_SRCP, type, (Attribute *)item, null);
							if (type == _hoops_IPAIR)
								HI_Flush_Textures (context, (_hoops_CPAIR *)item, list->_hoops_AGRI);
							else
								HI_Generic_Delete (context, item);
							_hoops_HPRH (item);
							_hoops_IRRPR();
						}
						else {
							_hoops_IGIC[_hoops_IRCCA++] = _hoops_AIRIR (item);
							if (_hoops_IRCCA == _hoops_CGCCA) {
								_hoops_RPPPR();
								HI_Delete_By_Keys (context, _hoops_IRCCA, _hoops_IGIC);
								for (int i = 0; i < _hoops_IRCCA; i++)
									_hoops_HPRH (_hoops_RCSSR (context, _hoops_IGIC[i]));
								_hoops_IRRPR();
								_hoops_IRCCA = 0;
							}
						}
					}
					FREE (list, _hoops_AGHPR);
				}
			}
			if (_hoops_IRCCA != 0) {
				_hoops_RPPPR();
				HI_Delete_By_Keys (context, _hoops_IRCCA, _hoops_IGIC);
				for (int i = 0; i < _hoops_IRCCA; i++)
					_hoops_HPRH (_hoops_RCSSR (context, _hoops_IGIC[i]));
				_hoops_IRRPR();
				_hoops_IRCCA = 0;
			}
			if (_hoops_SGCCA) {
				_hoops_GGHPR->list = _hoops_SGCCA;
				_hoops_SGCCA = null;
				pass++;
			}
			else
				break;
		}

		HI_Clean_FCD (&_hoops_ARHCA);
	}

	context->_hoops_GHHCA = _hoops_GGHPR->prev;
	FREE (_hoops_GGHPR, _hoops_SSPPR);
}

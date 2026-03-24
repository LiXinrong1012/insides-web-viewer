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
 * $Id: obf_tmp.txt 1.184 2010-12-06 22:05:40 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "please.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hd_proto.h"
#include "task_queue.h"
#include "adt.h"



local void _hoops_HPHHH (
	Attribute *		_hoops_ASGPR,
	_hoops_RSAIR **	_hoops_RGP,
	Window **		window,
	_hoops_GHAIR **	heuristics) {

	do {
		if (_hoops_ASGPR->type > _hoops_IAAA (HK_STYLE, HK_VISIBILITY, HK_HEURISTICS, HK_WINDOW))
			break;
		else switch (_hoops_ASGPR->type) {
			case HK_STYLE: {
#ifndef DISABLE_STYLE_SEGMENT
				Style const *		style = (Style const *)_hoops_ASGPR;

				if (style->_hoops_IGRPR &&
					!BIT (style->_hoops_IGRPR->_hoops_RRHH, _hoops_HGAGR) &&
					style->_hoops_IGRPR->_hoops_IPPGR != null)
					_hoops_HPHHH (style->_hoops_IGRPR->_hoops_IPPGR,
											 _hoops_RGP, window, heuristics);
#endif
			}	break;

			case HK_VISIBILITY: {
				*_hoops_RGP = (_hoops_RSAIR *)_hoops_ASGPR;
			}	break;

			case HK_WINDOW: {
				*window = (Window *)_hoops_ASGPR;
			}	break;

			case HK_HEURISTICS: {
				*heuristics = (_hoops_GHAIR *)_hoops_ASGPR;
			}	break;
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
}


local void _hoops_IPHHH (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP) {
	_hoops_RSAIR *			_hoops_RGP = null;
	_hoops_GHAIR *			heuristics = null;
	Window *				window = null;

	if (_hoops_SRCP->_hoops_IPPGR != null)
		_hoops_HPHHH (_hoops_SRCP->_hoops_IPPGR, &_hoops_RGP, &window, &heuristics);

	if (_hoops_RGP == null || BIT (_hoops_RGP->value, T_WINDOWS)) {
		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GCHGP))
			HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, HK_VISIBILITY, null, (Attribute *)_hoops_RGP);
	}
	else if (BIT (_hoops_RGP->mask, T_WINDOWS) &&
			 !BIT (_hoops_RGP->value, T_WINDOWS)) {
		if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GCHGP))
			HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, HK_VISIBILITY, null, (Attribute *)_hoops_RGP);
	}

	if (heuristics == null || !BIT (heuristics->value, T_WINDOWS)) {
		if (ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA|_hoops_RIGSA))
			HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, HK_HEURISTICS, null, (Attribute *)heuristics);
	}
	else {
		if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA|_hoops_RIGSA))
			HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, HK_HEURISTICS, null, (Attribute *)heuristics);
	}

	if (window == null) {
		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR))
			HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, HK_WINDOW, null, null);
	}
	else {
		if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR))
			HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, HK_WINDOW, null, (Attribute *)window);
	}
}


#	if FALSE
	if (driver == null) {
		if (ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_CPHHH|_hoops_SPHHH))
			HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, HK_DRIVER, null, null);
	}
#	if FALSE
	else if (driver->value == _hoops_GHHHH) {
		if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SPHHH))
			HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, HK_DRIVER, null, (Attribute *)driver);
	}
#	endif
	else {
		if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_CPHHH))
			HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, HK_DRIVER, null, (Attribute *)driver);
	}
#	endif



local void _hoops_RHHHH (
	_hoops_AIGPR *	_hoops_RIGC,
	Geometry *				geometry)
{
	do {
		geometry->_hoops_RRHH |= _hoops_HGAGR;

		HI_Delete_User_Key (_hoops_RIGC, (_hoops_HPAH *)geometry);
		if (BIT (geometry->_hoops_RRHH, _hoops_CHRIR)) {
			int *			mapping = null;
			int				count = 0;

			if (geometry->type == _hoops_HIIP) {
				_hoops_SHRIR *			_hoops_GIRIR = (_hoops_SHRIR *)geometry;

				mapping = _hoops_GIRIR->mapping;
				count = -_hoops_GIRIR->count / 2;
			}
			else if (geometry->type == _hoops_PIRS) {
				_hoops_GRPGR *		_hoops_CPAI = (_hoops_GRPGR *)geometry;

				mapping = _hoops_CPAI->mapping;
				count = _hoops_CPAI->count;
			}

			for (int i = 0; i < count; ++i) {
				int					index = mapping[i] & ~_hoops_RIRIR;

				if (HOOPS_WORLD->_hoops_GCHCA.table[index].key > _hoops_SHSSR)
					HI_Delete_User_Key (_hoops_RIGC, (_hoops_HPAH *)geometry,
										HOOPS_WORLD->_hoops_GCHCA.table[index].key);
			}
		}

		Attribute *			_hoops_HPHCR = geometry->_hoops_IPPGR;

		if (_hoops_HPHCR != null) do {
			Attribute *		next = _hoops_HPHCR->next;

			if (_hoops_HPHCR->type == HK_COLOR) {
				_hoops_ACSGA			*list;

				if ((list = ((_hoops_SSGI *)_hoops_HPHCR)->colors) != null) do {
					if (list->type == _hoops_GIGRA) {
						_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;

						if ((BIT (_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA, _hoops_IIARA) &&
							 _hoops_ICSGA->_hoops_ISHIR.texture[_hoops_PCA] != null ||
							 BIT (_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA, M_TRANSMISSION) &&
							 (_hoops_ICSGA->_hoops_ISHIR.color[_hoops_PCA].red   != 0.0f ||
							  _hoops_ICSGA->_hoops_ISHIR.color[_hoops_PCA].green != 0.0f ||
							  _hoops_ICSGA->_hoops_ISHIR.color[_hoops_PCA].blue  != 0.0f))) {
							HI_Less_Transparencies (_hoops_RIGC, geometry->owner, 1);
							break;
						}
					}
				} while ((list = list->next) != null);

				HI_Generic_Delete (_hoops_RIGC,(_hoops_HPAH *)_hoops_HPHCR);
			}

			_hoops_HPHCR = next;
		} while (_hoops_HPHCR != null);

		_hoops_RPAPA * _hoops_APAPA = HOOPS_WORLD->_hoops_PPAPA->Remove(geometry);

		if (_hoops_APAPA != null) {

			_hoops_PHIP const *	_hoops_RRA;

			while((_hoops_RRA = _hoops_APAPA->RemoveFirst()) != null) {
	
				for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++) {
					if (_hoops_RRA->_hoops_IHIP[i] == (_hoops_SIHIR *)geometry) {
						if (_hoops_RRA->_hoops_HHIP == 1) {
							HI_Delete_By_Keys (_hoops_RIGC, 1, &_hoops_RRA->key);
						}
						else {
							_hoops_SIHIR const * alter *	_hoops_GHAPA = _hoops_PGRCA(_hoops_RRA)->_hoops_IHIP;
							_hoops_HPRH(geometry);
							ALLOC_ARRAY (_hoops_PGRCA(_hoops_RRA)->_hoops_IHIP, _hoops_RRA->_hoops_HHIP-1, _hoops_SIHIR const *);
							if (i > 0)
								_hoops_AIGA (_hoops_GHAPA, i, _hoops_SIHIR const *, _hoops_PGRCA(_hoops_RRA)->_hoops_IHIP);
							if (i < _hoops_RRA->_hoops_HHIP-1)
								_hoops_AIGA (&_hoops_GHAPA[i+1], _hoops_RRA->_hoops_HHIP-1-i, _hoops_SIHIR const *, &_hoops_PGRCA(_hoops_RRA)->_hoops_IHIP[i]);
							FREE_ARRAY (_hoops_GHAPA, _hoops_RRA->_hoops_HHIP, _hoops_SIHIR const *);
							--_hoops_PGRCA(_hoops_RRA)->_hoops_HHIP;
						}
						break;
					}
				}
			}

			delete _hoops_APAPA;
		}

		switch (geometry->type) {
			case _hoops_GSIP:
			case _hoops_SCIP: {
				HI_Clean_Geometry_Display_Lists  (geometry, false, true);
			}	break;

			case _hoops_AGCP: {
				_hoops_PIGPR		*sc, *next;

				if ((sc = ((_hoops_HACC *)geometry)->_hoops_AAPGR) != null) {
					do {
						next = (_hoops_PIGPR *)sc->next;
						HI_Generic_Delete (_hoops_RIGC,(_hoops_HPAH *)sc);
					} while ((sc = next) != null);
				}
			}	break;

			case _hoops_IIIP: {
				if (BIT (geometry->_hoops_RRHH, _hoops_HIHCA)) {

					/* _hoops_PAGA: _hoops_IPAC _hoops_HCR _hoops_AHSHA, _hoops_HAR _hoops_SAHR _hoops_CARS */
					_hoops_CAAI (HOOPS_WORLD->_hoops_RIPSA);
					_hoops_AIGPR *	_hoops_AGRHP = HOOPS_WORLD->_hoops_PGSCA;
					do {
						_hoops_SIRIR *	_hoops_AHSCA = _hoops_AGRHP->open_list;
						while (_hoops_AHSCA != null) {
							if (_hoops_AHSCA->_hoops_GCRIR == _hoops_RCRIR &&
								_hoops_AHSCA->info.segment._hoops_ACRIR == (Polyline *)geometry) {
									_hoops_HPRH (geometry);
									_hoops_AHSCA->info.segment._hoops_ACRIR = null;
							}
							_hoops_AHSCA = _hoops_AHSCA->next;
						}
					} while ((_hoops_AGRHP = _hoops_AGRHP->next) != null);
					_hoops_APAI (HOOPS_WORLD->_hoops_RIPSA);
				}
			}	break;

			case _hoops_CHIP: {
				/* _hoops_AA _hoops_SR _hoops_RRP _hoops_IS _hoops_AA _hoops_CPHP _hoops_ARI? */
			}	break;

			case HK_STRING_CURSOR: {
				_hoops_GGAGR *		driver = HOOPS_WORLD->_hoops_CISHA;

				do if (driver->_hoops_CPCR._hoops_SRPIR == (_hoops_PIGPR *)geometry ||
					   driver->_hoops_RCSHR._hoops_SRPIR == (_hoops_PIGPR *)geometry) {
					driver->_hoops_CGPIR |= _hoops_PARPH;
					HOOPS_WORLD->_hoops_AARPH = true;
				} while ((driver = driver->_hoops_CISHA) != null);
			}	break;

			case _hoops_HGPGR: {
				HI_Less_Cutting_Planes (_hoops_RIGC, geometry->owner, 1);
			}	break;

			case _hoops_HGCP: {
#ifndef DISABLE_TEXTURING
			   Image *		image =	(Image *) geometry;

			   /* _hoops_RPP _hoops_RGR _hoops_CSCR _hoops_SSCP _hoops_IRS _hoops_CHHA _hoops_HH _hoops_HSCI _hoops_SCH */
			   if (image->texture) {
				   HI_UnDefine_Texture(_hoops_RIGC, image->texture);
				   /* _hoops_AHHHH, _hoops_SR _hoops_CPSA _hoops_AA _hoops_RRP _hoops_RGR _hoops_ISPR */
				   if (image->texture) {
					   _hoops_HPRH (image->texture);
					   image->texture = null;
				   }
			   }
#endif
			}	break;

			case _hoops_ICIP: {
				HI_Less_Light (_hoops_RIGC, geometry->owner, 1);
			}	break;

			case _hoops_AHIP: {
				_hoops_PHIP *		_hoops_RRA = (_hoops_PHIP *)geometry;

				if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
					_hoops_CRCP const *			_hoops_HGRPR = (_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0];

					HI_Less_Light (_hoops_RIGC, geometry->owner, _hoops_HGRPR->_hoops_AAGSA());
					HI_Less_Cutting_Planes (_hoops_RIGC, geometry->owner, _hoops_HGRPR->_hoops_PAGSA());
				}
				else {
					for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++) {
						if (_hoops_RRA->_hoops_IHIP[i]->type == _hoops_ICIP)
							HI_Less_Light (_hoops_RIGC, geometry->owner, 1);
						else if (_hoops_RRA->_hoops_IHIP[i]->type == _hoops_HGPGR)
							HI_Less_Cutting_Planes (_hoops_RIGC, geometry->owner, 1);
					}
				}
				HI_Disentangle (_hoops_RIGC, (_hoops_HPAH *)geometry);
// _hoops_SIGP: _hoops_PHHHH _hoops_PRCHR
			}	break;
		}

		Geometry *		next = geometry->next;

		if (BIT (geometry->_hoops_CPGPR, _hoops_CASIR) ||
			geometry->type == HK_STRING_CURSOR) {

			HI_Disentangle (_hoops_RIGC, (_hoops_HPAH *)geometry);
			_hoops_CIGPR (_hoops_RIGC,geometry);
			geometry->owner = null;
			_hoops_HPRH (geometry);
		}
		else {
			_hoops_CIGPR (_hoops_RIGC,geometry);
			if ((geometry->next = geometry->owner->_hoops_SCGPR()) != null)
				geometry->next->backlink = &geometry->next;
			geometry->owner->_hoops_RSGPR (geometry);
		}

		geometry = next;
	} while (geometry != null);
}


local void _hoops_HHHHH (
	_hoops_AIGPR *	_hoops_RIGC,
	Attribute *				_hoops_ASGPR,
	bool					_hoops_IHHHH) {

	/* _hoops_GIGHR: _hoops_RGAR _hoops_AIARR _hoops_HA _hoops_RPP _hoops_CHHHH,
			 _hoops_PAR _hoops_RPP _hoops_RGAR _hoops_RH _hoops_IGRI _hoops_PPR _hoops_HAR _hoops_RH _hoops_RRRPR _hoops_HRGR _hoops_IHGS _hoops_PGHPR.
	 */

	do if (!BIT (_hoops_ASGPR->_hoops_RRHH, _hoops_HGAGR)) {
		if (_hoops_ASGPR->type != HK_WINDOW || !_hoops_IHHHH)
			_hoops_ASGPR->_hoops_RRHH |= _hoops_HGAGR;

		switch (_hoops_ASGPR->type) {
			case HK_STYLE: {
#ifndef DISABLE_STYLE_SEGMENT
				Style *		style = (Style *)_hoops_ASGPR;
				_hoops_CRCP	*	owner = _hoops_ASGPR->owner;

				HI_Delete_Style_Attributes (_hoops_RIGC, owner, style);

				HI_Delete_User_Key (_hoops_RIGC, (_hoops_HPAH *)_hoops_ASGPR);

				if (!BIT (owner->_hoops_RRHH, _hoops_HGAGR))
					if (ANYBIT (owner->_hoops_PHSI,_hoops_SHSIR|_hoops_GIGSA))
						_hoops_IPHHH (_hoops_RIGC, owner);
#endif
			}	break;

			case HK_DRIVER: {
				_hoops_GGAGR *		_hoops_GHRI = (_hoops_GGAGR *)_hoops_ASGPR;

				if (BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA)) {
					/* _hoops_GHHR _hoops_RH _hoops_SISS */
					_hoops_GGAGR				*dl = HOOPS_WORLD->_hoops_CISHA;

					do if (dl->_hoops_CPCR.target == _hoops_GHRI ||
						   dl->_hoops_RCSHR.target == _hoops_GHRI)
						dl->_hoops_CGPIR |= _hoops_PARPH;
					while ((dl = dl->_hoops_CISHA) != null);

					HI_Queue_Actor_Shutdown(_hoops_GHRI, true);
				}

				if (_hoops_GHRI->_hoops_GRPIR) {
					delete _hoops_GHRI->_hoops_GRPIR;
					_hoops_GHRI->_hoops_GRPIR = null;
				}

				if (_hoops_GHRI->_hoops_ACARR) {
					delete _hoops_GHRI->_hoops_ACARR;
					_hoops_GHRI->_hoops_ACARR = null;
				}

				HOOPS_WORLD->_hoops_AARPH = true;
				_hoops_GHRI->_hoops_CGPIR |= _hoops_PARPH;
				_hoops_ASGPR->owner->_hoops_PHSI &= ~(_hoops_GISIR|_hoops_HIHGP);
			}	break;

			case HK_COLOR: {
			}	break;
		}

		Attribute *		next = _hoops_ASGPR->next;
		_hoops_CRCP *		owner = _hoops_ASGPR->owner;

		if (owner != null && owner->type == _hoops_IRCP &&
			BIT (owner->_hoops_PHSI, _hoops_GISIR)) {
			Attribute *		driver = owner->_hoops_IPPGR;

			do if (driver->type == HK_DRIVER) {
				driver->_hoops_CPGPR |= _hoops_AHSGA;
				break;
			} while ((driver = driver->next) != null);
		}

		HI_Disentangle (_hoops_RIGC, (_hoops_HPAH *)_hoops_ASGPR);
		_hoops_CIGPR (_hoops_RIGC,_hoops_ASGPR);
		_hoops_HPRH (_hoops_ASGPR);

		_hoops_ASGPR = next;
	}
	else {
		_hoops_ASGPR = _hoops_ASGPR->next;
	} while (_hoops_ASGPR != null);
}

local void _hoops_SHHHH (
	_hoops_AIGPR *	_hoops_RIGC,
	Subsegment *			_hoops_GIPIA) {

	do if (!BIT (_hoops_GIPIA->_hoops_RRHH, _hoops_HGAGR)) {
		_hoops_GIPIA->_hoops_RRHH |= _hoops_HGAGR;

		HI_Delete_User_Key (_hoops_RIGC, (_hoops_HPAH *)_hoops_GIPIA);

		// _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_RGRIR _hoops_HHSIR _hoops_GAR _hoops_SR _hoops_CHR(?) _hoops_GIAA _hoops_IRS _hoops_IHSIR
		HI_Remove_Fast_Lookup_Item (_hoops_GIPIA->owner, false, _hoops_GIPIA);
		HI_Remove_Fast_Lookup_Item (_hoops_GIPIA->owner, true, _hoops_GIPIA);

		switch (_hoops_GIPIA->type) {
			case _hoops_IRCP: {
				_hoops_CRCP *		_hoops_SRCP = (_hoops_CRCP *)_hoops_GIPIA;
				Xref *			_hoops_AHICA;
				_hoops_PIHGP		_hoops_AICIP;

				// _hoops_GA'_hoops_RA _hoops_GIHHH _hoops_GHIR _hoops_CCA _hoops_AGCR _hoops_GAR _hoops_SR _hoops_PCHIA _hoops_PSAP _hoops_RH _hoops_CHAPA
				HI_Destroy_Fast_Lookups (_hoops_RIGC, _hoops_SRCP);

				_hoops_AICIP = _hoops_SRCP->_hoops_PHSI & (_hoops_SHSIR | _hoops_GISIR);

				if (_hoops_SRCP->geometry != null)
					_hoops_RHHHH (_hoops_RIGC, _hoops_SRCP->geometry);

				if (_hoops_SRCP->_hoops_IPPGR != null) {
#ifndef DISABLE_STYLE_SEGMENT
					if ((_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR()) != null) do {
						if (_hoops_AHICA->type == HK_STYLE &&
							!BIT (_hoops_AHICA->_hoops_RRHH, _hoops_HGAGR) &&
							!BIT (_hoops_AHICA->owner->_hoops_RRHH, _hoops_HGAGR))
							HI_Delete_Style_Attributes (_hoops_RIGC,  _hoops_AHICA->owner, (Style *)_hoops_AHICA);
					} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);
#endif

					/* _hoops_RPPS _hoops_ISPR _hoops_ARPP "_hoops_SPIC" _hoops_IS _hoops_HGCR _hoops_SCH _hoops_ARPP _hoops_PSSAR */
					if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) {
						Window				*window;

						window = HI_Find_Scoping_Window (_hoops_SRCP);

						if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GCHGP))
							_hoops_SRCP->_hoops_PHSI &= ~_hoops_SHSIR;
						_hoops_SRCP->_hoops_CPGPR &= ~_hoops_AHPGP; /* _hoops_HIAP */
						HI_Propagate_Scoped_Activity (_hoops_RIGC, (_hoops_SIHIR *)_hoops_SRCP,
													  _hoops_GSCCA,
													  &window->_hoops_RCHS);
						_hoops_SRCP->_hoops_PHSI |= _hoops_SHSIR;
					}

					if (ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GISIR) ||
								_hoops_SRCP->_hoops_IPPGR->type == HK_STYLE)
						_hoops_HHHHH (_hoops_RIGC, _hoops_SRCP->_hoops_IPPGR, true);
				}

				if ((_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR()) != null) do if (!BIT (_hoops_AHICA->_hoops_RRHH, _hoops_HGAGR)) {
					/* _hoops_SHHH _hoops_SHH _hoops_IIGPR(_hoops_HSIGP), _hoops_HIH _hoops_IH _hoops_HICIP... */
					_hoops_AHICA->_hoops_RRHH |= _hoops_HGAGR;
					_hoops_AHICA->_hoops_CPGPR |= _hoops_CCHPA;

					if (BIT (_hoops_AHICA->owner->_hoops_RRHH, _hoops_HGAGR)) {}
					else {
						if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR)) {
							if (_hoops_SRCP->_hoops_SHGSA() > 0 && _hoops_AHICA->type == _hoops_AGRPR)
								HI_Less_Shadows (_hoops_RIGC, _hoops_AHICA->owner, _hoops_SRCP->_hoops_SHGSA());

							if (_hoops_AHICA->type == _hoops_AGRPR &&
								!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA|_hoops_RIGSA)) {
								if (_hoops_SRCP->_hoops_IGCCA > 0)
									HI_Less_Transparencies (_hoops_RIGC, _hoops_AHICA->owner, _hoops_SRCP->_hoops_IGCCA);
							}
						}

						if (_hoops_AHICA->type == _hoops_AGRPR) {
							_hoops_PGRPR *		include = (_hoops_PGRPR *)_hoops_AHICA;
							_hoops_CRCP *		_hoops_RIHHH;

							HI_Delete_User_Key (_hoops_RIGC, (_hoops_HPAH *)_hoops_AHICA);

							/* _hoops_CRRPR _hoops_GA'_hoops_RA _hoops_RSGR _hoops_GH _hoops_GGR _hoops_RH _hoops_ACGIP _hoops_HIIA, _hoops_HIS _hoops_RGAR _hoops_CASI _hoops_GHCP */
							// _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_RGRIR _hoops_HHSIR _hoops_GAR _hoops_SR _hoops_CHR(?) _hoops_GIAA _hoops_IRS _hoops_IHSIR
							HI_Remove_Fast_Lookup_Item (_hoops_AHICA->owner, true, (Subsegment *)_hoops_AHICA);

							_hoops_RIHHH = (_hoops_CRCP alter *)include->_hoops_IGRPR;

							if ((BIT (_hoops_RIHHH->_hoops_RCGC, T_WINDOWS) ||
									  BIT (_hoops_RIHHH->_hoops_PHSI, _hoops_SHSIR)) &&
									 !ANYBIT (_hoops_RIHHH->_hoops_PHSI, _hoops_GIGSA)) {
								if (BIT (_hoops_RIHHH->_hoops_RCGC, T_FACES) &&
									!ANYBIT (_hoops_RIHHH->_hoops_PHSI, _hoops_SHSIR|
															_hoops_GIGSA))
									_hoops_SASIR (_hoops_RIGC, _hoops_AHICA->owner,
										_hoops_GCGSA|_hoops_RPSIR|_hoops_SSCCA);
								else
									_hoops_SASIR (_hoops_RIGC, _hoops_AHICA->owner,
										_hoops_RCGSA|_hoops_RPSIR|_hoops_SSCCA);
							}
							else if (ANYBIT (_hoops_RIHHH->_hoops_RCGC, _hoops_HAHGP) &&
									 !BIT (_hoops_RIHHH->_hoops_PHSI, _hoops_GIGSA)) {
								if (BIT (_hoops_RIHHH->_hoops_RCGC, T_FACES) &&
									!ANYBIT (_hoops_RIHHH->_hoops_PHSI, _hoops_SHSIR|
															_hoops_GIGSA))
									_hoops_SASIR (_hoops_RIGC, _hoops_AHICA->owner,
										_hoops_PCPGP|_hoops_RPSIR|_hoops_SSCCA);
								else
									_hoops_SASIR (_hoops_RIGC, _hoops_AHICA->owner,
										_hoops_HRCCA|_hoops_RPSIR|_hoops_SSCCA);
							}
							else
								_hoops_SASIR (_hoops_RIGC, _hoops_AHICA->owner,
													_hoops_CCHPA);

							_hoops_CIGPR (_hoops_RIGC,_hoops_AHICA);
							if ((_hoops_AHICA->next = _hoops_AHICA->owner->_hoops_PRRPR()) != null)
								_hoops_AHICA->next->backlink = &_hoops_AHICA->next;
							_hoops_AHICA->owner->_hoops_HRRPR (_hoops_AHICA);
							_hoops_AHICA->owner = null;
						}
#ifndef DISABLE_STYLE_SEGMENT
						else {	/* _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_AIHHH */
							HI_Delete_User_Key (_hoops_RIGC, (_hoops_HPAH *)_hoops_AHICA);

							if (ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_GIGSA))
								_hoops_IPHHH (_hoops_RIGC, _hoops_AHICA->owner);
						}
#endif
					}
				} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);

				/* _hoops_CAHAR _hoops_SR _hoops_HGGC _hoops_HS _hoops_GII _hoops_RPPS/_hoops_RHPP _hoops_HPGP _hoops_GHGA
				** _hoops_CHAPA _hoops_IS _hoops_RRS _hoops_PCHC _hoops_PIHHH */

				_hoops_SRCP->_hoops_PHSI |= _hoops_AICIP;

				if (_hoops_SRCP->_hoops_RGRPR != null)
					_hoops_SHHHH (_hoops_RIGC, _hoops_SRCP->_hoops_RGRPR);

				if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR)) {
					if (_hoops_SRCP->_hoops_SHGSA() > 0)
						HI_Less_Shadows (_hoops_RIGC, _hoops_SRCP->owner, _hoops_SRCP->_hoops_SHGSA());

					if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA|_hoops_RIGSA)) {
						if (_hoops_SRCP->_hoops_IGCCA > 0)
							HI_Less_Transparencies (_hoops_RIGC, _hoops_SRCP->owner, _hoops_SRCP->_hoops_IGCCA);
					}
				}

				_hoops_SRCP->_hoops_PHSI &= ~_hoops_AICIP;
			}	break;

			case _hoops_AGRPR: {
				_hoops_PGRPR *		include = (_hoops_PGRPR *)_hoops_GIPIA;
				_hoops_CRCP	*		_hoops_SRCP = (_hoops_CRCP alter *)include->_hoops_IGRPR;

				if (!BIT (_hoops_GIPIA->owner->_hoops_RRHH, _hoops_HGAGR)) {
					if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR)) {
						if (_hoops_SRCP->_hoops_AAGSA() > 0)
							HI_Less_Light (_hoops_RIGC, _hoops_GIPIA->owner, _hoops_SRCP->_hoops_AAGSA());
						if (_hoops_SRCP->_hoops_PAGSA() > 0)
							HI_Less_Cutting_Planes (_hoops_RIGC, _hoops_GIPIA->owner, _hoops_SRCP->_hoops_PAGSA());
						if (_hoops_SRCP->_hoops_SHGSA() > 0)
							HI_Less_Shadows (_hoops_RIGC, _hoops_GIPIA->owner, _hoops_SRCP->_hoops_SHGSA());

						if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA|_hoops_RIGSA)) {
							if (_hoops_SRCP->_hoops_IGCCA > 0)
								HI_Less_Transparencies (_hoops_RIGC, _hoops_GIPIA->owner, _hoops_SRCP->_hoops_IGCCA);
						}
					}

					/* _hoops_RIRRR _hoops_HII _hoops_ARRS, "_hoops_HSIGP" -> "_hoops_HHASA" */
					if ((BIT (_hoops_SRCP->_hoops_RCGC, T_WINDOWS) ||
							  BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) &&
							 !BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA)) {
						if (BIT (_hoops_SRCP->_hoops_RCGC, T_FACES) &&
							!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|
													_hoops_GIGSA))
							_hoops_SASIR (_hoops_RIGC, _hoops_GIPIA->owner,
								_hoops_GCGSA|_hoops_RPSIR|_hoops_SSCCA);
						else
							_hoops_SASIR (_hoops_RIGC, _hoops_GIPIA->owner,
								_hoops_RCGSA|_hoops_RPSIR|_hoops_SSCCA);
					}
					else if (ANYBIT (_hoops_SRCP->_hoops_RCGC, _hoops_HAHGP) &&
							 !BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA)) {
						if (BIT (_hoops_SRCP->_hoops_RCGC, T_FACES) &&
							!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|
													_hoops_GIGSA))
							_hoops_SASIR (_hoops_RIGC, _hoops_GIPIA->owner,
								_hoops_PCPGP|_hoops_RPSIR|_hoops_SSCCA);
						else
							_hoops_SASIR (_hoops_RIGC, _hoops_GIPIA->owner,
								_hoops_HRCCA|_hoops_RPSIR|_hoops_SSCCA);
					}
					else
						_hoops_SASIR (_hoops_RIGC, _hoops_GIPIA->owner,
											_hoops_CCHPA);
				}
			}	break;
		}

		Subsegment *			next = _hoops_GIPIA->next;
		bool					_hoops_HIHHH = true;
		_hoops_CRCP const *			_hoops_SRCP = _hoops_SSIGP(_hoops_GIPIA);
		{
			_hoops_SPAGR					_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, _hoops_RIGC->thread_id);
			_hoops_AHAGR const *	_hoops_CSC = _hoops_SRCP->_hoops_CSC;

			if (_hoops_CSC != null) do {
				if (_hoops_CSC->_hoops_APHGA != null &&
					BIT (_hoops_CSC->_hoops_APHGA->transform_rendition->heuristics, _hoops_PRIRP)) {
					_hoops_HIHHH = false;
					break;
				}
			} while ((_hoops_CSC = _hoops_CSC->next) != null);
		}

		if (_hoops_HIHHH) {
			HI_Disentangle (_hoops_RIGC, (_hoops_HPAH *)_hoops_GIPIA);

			_hoops_CIGPR (_hoops_RIGC,_hoops_GIPIA);
			_hoops_GIPIA->owner = null;
			_hoops_HPRH (_hoops_GIPIA);
		}
		else {
			_hoops_CIGPR (_hoops_RIGC,_hoops_GIPIA);
			if ((_hoops_GIPIA->next = _hoops_GIPIA->owner->_hoops_PRRPR()) != null)
				_hoops_GIPIA->next->backlink = &_hoops_GIPIA->next;
			_hoops_GIPIA->owner->_hoops_HRRPR (_hoops_GIPIA);
			_hoops_GIPIA->owner = null;
		}

		_hoops_GIPIA = next;
	}
	else {
		_hoops_GIPIA = _hoops_GIPIA->next;
	} while (_hoops_GIPIA != null);
}


GLOBAL_FUNCTION void HI_Generic_Delete (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				_hoops_CISIR)
{
	_hoops_ICIIR(_hoops_RIGC);

	if (_hoops_CISIR->type < _hoops_HPAGP) {
		_hoops_HPAH *		_hoops_IIHHH;
		_hoops_HPAH **		_hoops_CIHHH;
		_hoops_HPAH *		_hoops_GGHPR;

		/*_hoops_ARI _hoops_SR _hoops_SAHR _hoops_HASIR _hoops_SCH _hoops_HII _hoops_GASR
		 *_hoops_IIS _hoops_RH _hoops_RHGS _hoops_RRGR _hoops_AA _hoops_RH _hoops_RII _hoops_IPHR*/
		/*_hoops_SR _hoops_RRP _hoops_IS _hoops_HSGR _hoops_GSGR _hoops_ARSIR _hoops_PGGA _hoops_SSIA _hoops_CHR _hoops_IIP _hoops_RRAI*/
		if (_hoops_CISIR->type >= _hoops_AHRIR &&
				_hoops_CISIR->type <= _hoops_PHRIR&&
				_hoops_CISIR->type != HK_STRING_CURSOR)
			HI_Table_Remove_Geometry((Geometry *)_hoops_CISIR);

		/*** _hoops_SIHHH!! ***/

		_hoops_IIHHH = _hoops_CISIR->next;
		_hoops_CIHHH = _hoops_CISIR->backlink;

		/* _hoops_RRP _hoops_IS _hoops_CCIH _hoops_GSSR _hoops_GPHHR, _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_CGSI _hoops_PII _hoops_GCHHH */
		if ((*_hoops_CIHHH = _hoops_IIHHH) != null)
			_hoops_IIHHH->backlink = _hoops_CIHHH;

		_hoops_CISIR->next = null;	/* _hoops_SRCH _hoops_RH _hoops_HAPR _hoops_GGR _hoops_RCHHH */
		_hoops_CISIR->backlink = &_hoops_GGHPR;
		_hoops_GGHPR = _hoops_CISIR;

		/* _hoops_RRP _hoops_IS _hoops_AA _hoops_RH _hoops_CPGGR _hoops_ARPP _hoops_SR _hoops_RSRHR _hoops_SCH _hoops_SGGR! */
		_hoops_CISIR->_hoops_CPGPR |= _hoops_CCHPA; /* _hoops_IH _hoops_ACHHH */
		_hoops_SASIR (_hoops_RIGC, _hoops_CISIR->owner, _hoops_CCHPA);

		if (_hoops_CISIR->type <= _hoops_CRCCA)
			_hoops_HHHHH (_hoops_RIGC, (Attribute *)_hoops_CISIR, false);
		else if (_hoops_CISIR->type <= _hoops_PHRIR)
			_hoops_RHHHH (_hoops_RIGC, (Geometry *)_hoops_CISIR);
		else
			_hoops_SHHHH (_hoops_RIGC, (Subsegment *)_hoops_CISIR);

		if (_hoops_GGHPR == null) { /* _hoops_SCH _hoops_CSAP _hoops_HGGPR */
			//_hoops_RPP ((*_hoops_PCHHH = _hoops_HCHHH) != _hoops_IRAP)
			//	_hoops_HCHHH->_hoops_IPSIR = _hoops_PCHHH;
		}
		else {
			_hoops_CISIR->backlink = _hoops_CIHHH;
			*_hoops_CIHHH = _hoops_CISIR;
			if ((_hoops_CISIR->next = _hoops_IIHHH) != null)
				_hoops_IIHHH->backlink = &_hoops_CISIR->next;
		}
	}
	else {
		_hoops_CISIR->_hoops_RRHH |= _hoops_HGAGR;
		HI_Disentangle (_hoops_RIGC, _hoops_CISIR);
		_hoops_CIGPR (_hoops_RIGC,_hoops_CISIR);
		_hoops_HPRH (_hoops_CISIR);
	}
}


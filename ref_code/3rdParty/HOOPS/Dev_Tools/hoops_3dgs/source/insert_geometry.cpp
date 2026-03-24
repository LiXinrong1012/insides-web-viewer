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
 * $Id: obf_tmp.txt 1.148 2010-11-02 03:15:27 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "phedron.h"




GLOBAL_FUNCTION void HI_Table_Remove_Geometry (
	Geometry *		geometry) {
	_hoops_CRCP *		_hoops_SRCP = geometry->owner;
	long			_hoops_CPIGP = _hoops_IIAGR(geometry->type);

	if (_hoops_SRCP->_hoops_GACP == null) {
		if (!BIT (_hoops_SRCP->_hoops_RRHH, _hoops_HIRIR))
			HE_ERROR (HEC_INVALID_KEY, HES_INVALID_GEOMETY_OR_SEGMENT,
					  "Segment doesn't have a valid geometry table.");
		return;
	}

	/* _hoops_HRGR _hoops_SCH _hoops_GGR _hoops_RH _hoops_IASIR _hoops_ICSHR */
	if (BIT (geometry->_hoops_RRHH, _hoops_PASIR))
		_hoops_CPIGP = _hoops_RACP;

	/* _hoops_HRGR _hoops_SCH _hoops_RH _hoops_SRS _hoops_IIGR _hoops_SCH'_hoops_GRI _hoops_GPRR */
	if (_hoops_SRCP->_hoops_GACP->_hoops_AACP (_hoops_CPIGP) == geometry) {
		if (geometry->next != null && (_hoops_CPIGP == _hoops_RACP || geometry->type == geometry->next->type))
			_hoops_SRCP->_hoops_GACP->set (_hoops_CPIGP, geometry->next);
		else
			_hoops_SRCP->_hoops_GACP->set (_hoops_CPIGP, null);
	}
}

GLOBAL_FUNCTION void HI_Table_Insert_OO_Geometry (
	_hoops_CRCP *		_hoops_SRCP,
	Geometry *		geometry) {

	if (_hoops_SRCP->_hoops_GACP == null)
		_hoops_SRCP->_hoops_GACP = NEW(_hoops_AAIGP);

	if (_hoops_SRCP->geometry == null) {
		geometry->next = null;
		geometry->backlink = &_hoops_SRCP->geometry;
		_hoops_SRCP->geometry = geometry;

		_hoops_SRCP->_hoops_GACP->set (_hoops_RACP, geometry);
	}
	else {	/*_hoops_ARI _hoops_SR _hoops_RRP _hoops_IS _hoops_GGCR _hoops_HPGR _hoops_RH _hoops_CGHI _hoops_GISR _hoops_GGR _hoops_HIGR*/
		Geometry *		_hoops_GHHPH;

		if (_hoops_SRCP->_hoops_GACP->_hoops_AACP (_hoops_RACP) == null)
			_hoops_SRCP->_hoops_GACP->set (_hoops_RACP, geometry);

		_hoops_GHHPH = _hoops_SRCP->_hoops_GACP->_hoops_IAIGP ();
		while (_hoops_GHHPH->next != null) _hoops_GHHPH = _hoops_GHHPH->next;

		geometry->next = null;
		geometry->backlink = &_hoops_GHHPH->next;
		_hoops_GHHPH->next = geometry;
	}
}


GLOBAL_FUNCTION void HI_Table_Insert_Geometry (
	_hoops_CRCP *		_hoops_SRCP,
	Geometry *		geometry) {
	long			_hoops_CPIGP = _hoops_IIAGR(geometry->type);

	if (_hoops_SRCP->_hoops_GACP == null)
		_hoops_SRCP->_hoops_GACP = NEW(_hoops_AAIGP);

	if (_hoops_SRCP->geometry == null) {
		geometry->next = null;
		geometry->backlink = &_hoops_SRCP->geometry;
		_hoops_SRCP->geometry = geometry;
	}
	else if (_hoops_SRCP->_hoops_GACP->_hoops_AACP (_hoops_CPIGP) != null) {
		Geometry *			g = _hoops_SRCP->_hoops_GACP->_hoops_AACP (_hoops_CPIGP);

		geometry->next = g;
		geometry->backlink = g->backlink;
		*g->backlink = geometry;
		g->backlink = &geometry->next;
	}

/*_hoops_RHRRA*/
	/*_hoops_AGIR 3 _hoops_SRS _hoops_IIGR _hoops_IRS _hoops_GPRR _hoops_GGR _hoops_GRAA _hoops_RHPA _hoops_HIGR*/
	/*_hoops_GHAP'_hoops_SPHAI _hoops_SAHR _hoops_GRP _hoops_RH _hoops_RHGS _hoops_HSPAR _hoops_ARI _hoops_HIH _hoops_RIGRP _hoops_RH _hoops_GASR*/
	/*_hoops_IGHS _hoops_IRS _hoops_GASR _hoops_HIIA _hoops_PPR _hoops_HSPAR _hoops_HRGR _hoops_RH _hoops_GPRCP _hoops_HIH _hoops_IH _hoops_HA _hoops_SAHR _hoops_HGCR _hoops_SCH _hoops_CRSH*/
	else {
		Geometry		*_hoops_GHHPH = _hoops_SRCP->geometry;
		Type			type = geometry->type;

		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_AASIR))
			_hoops_RGGA (_hoops_GHHPH->type >= type || _hoops_GHHPH->next == null ||
				   BIT (_hoops_GHHPH->_hoops_RRHH, _hoops_PASIR))
				_hoops_GHHPH = _hoops_GHHPH->next;
		else
			_hoops_RGGA (_hoops_GHHPH->type >= type || _hoops_GHHPH->next == null)
				_hoops_GHHPH = _hoops_GHHPH->next;

		if (_hoops_GHHPH->type < type && !BIT (_hoops_GHHPH->_hoops_RRHH, _hoops_PASIR)) {
			/* _hoops_PPSI _hoops_SCH _hoops_RAS _hoops_RGR _hoops_SPR */
			geometry->next = null;
			geometry->backlink = &_hoops_GHHPH->next;
			_hoops_GHHPH->next = geometry;
		}
		else {
			/* _hoops_PPSI _hoops_SCH _hoops_ARPP _hoops_RGR _hoops_SPR */
			*_hoops_GHHPH->backlink = geometry;
			geometry->backlink = _hoops_GHHPH->backlink;
			geometry->next = _hoops_GHHPH;
			_hoops_GHHPH->backlink = &geometry->next;
		}
	}

	_hoops_SRCP->_hoops_GACP->set (_hoops_CPIGP, geometry);
}



GLOBAL_FUNCTION _hoops_ACHR HI_Determine_Geometry_Maybes (
	Geometry const *	geometry) {
	_hoops_ACHR			_hoops_SIAPI = 0;

	switch (geometry->type) {
		case _hoops_GRCP:
		case _hoops_RRCP:
		case _hoops_SGCP:
		case _hoops_CGCP: {
			_hoops_SIAPI = T_FACES|T_EDGES;
		}	break;

		case _hoops_SIIP:
		case _hoops_RIIP:
		case _hoops_GIIP:
		case _hoops_PIIP:
		case _hoops_HIIP:
		case _hoops_IIIP: {
			_hoops_SIAPI = T_LINES;
		}	break;

		case _hoops_PCIP:
		case _hoops_PIRS: {
			_hoops_SIAPI = T_MARKERS;
		}	break;

		case _hoops_HGPGR: {
			_hoops_SIAPI = T_CUTTING_PLANES;
		}	break;

		case _hoops_ICIP: {
			_hoops_SIAPI = T_ANY_LIGHTS | _hoops_ASRRA;
		}	break;


		case _hoops_CHIP: {
			_hoops_SIAPI = T_LINES|T_MARKERS;
		}	break;

		case _hoops_HGCP: {
			_hoops_SIAPI = T_IMAGES;

			switch (((Image const *)geometry)->_hoops_ISRRP) {
				case _hoops_HHGH:
				case Image_RGBA32:
				case _hoops_HRSRH:      _hoops_SIAPI |= _hoops_ASRRA;
			}
		}	break;

		case _hoops_RCIP: {
			_hoops_SIAPI = T_FACES|T_EDGES;
		}	break;

		case _hoops_GGCP:
		case _hoops_GSIP:
		case _hoops_PRCP:
		case _hoops_ASIP:
		case _hoops_CSIP:
		case _hoops_HSIP:
		case _hoops_SCIP: {
			_hoops_SIAPI = T_FACES|T_EDGES|T_VERTICES;
		}	break;

		case _hoops_AGCP: {
			_hoops_SIAPI = T_TEXT;
		}	break;

		case HK_STRING_CURSOR: {
			_hoops_SIAPI = T_STRING_CURSORS;
		}	break;

		case _hoops_AHIP: {
			_hoops_PHIP const *	_hoops_RRA = (_hoops_PHIP const *)geometry;

			if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
				_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0];

				_hoops_SIAPI |= _hoops_SRCP->_hoops_RCGC;
			}
			else {
				for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++)
					_hoops_SIAPI |= HI_Determine_Geometry_Maybes ((Geometry const *)_hoops_RRA->_hoops_IHIP[i]);
			}
		}	break;

		default: {
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, Sprintf_D (null,
									"Unexpected segment geometry type (#%d)", geometry->type));
			/*_hoops_ASIGA _hoops_GGAS*/
			return T_FACES|T_EDGES|T_VERTICES|T_LINES;
		}
	}

	return _hoops_SIAPI;
}


GLOBAL_FUNCTION Geometry * HI_Insert_Geometry (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				thing,
	Geometry *				geometry,
	bool					_hoops_SHCIH,
	Activity				_hoops_CPGPR,
	bool					_hoops_CCHAH) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_SIRIR const *		open_list = null;
	_hoops_CRCP *				_hoops_SRCP = null;
	_hoops_ACHR				_hoops_SIAPI;
	Bounding				bounding;
	Activity				_hoops_GCAPI = 0;

	/* _hoops_HPIRA _hoops_SHRAA _hoops_GGR */
	if (_hoops_CCHAH)
		geometry->_hoops_HIHI = 1;
	geometry->_hoops_SPGPR = false;
	geometry->key = _hoops_AIRIR (geometry);
	geometry->priority = (HOOPS_WORLD->_hoops_IPAPA)++;

	_hoops_SIAPI = HI_Determine_Geometry_Maybes (geometry);
	if (!_hoops_SHCIH) {
		geometry->_hoops_RRHH |= _hoops_RSPCR;
		_hoops_SIAPI |= _hoops_ASPCR;
	}

	if (thing->type == _hoops_CIRIR)
		open_list = (_hoops_SIRIR const *)thing;

	if (open_list && open_list->_hoops_GCRIR == _hoops_RSRIR) {
		_hoops_HPAH *		owner = open_list->info._hoops_PRSI._hoops_IGRPR;
		int				level = open_list->info._hoops_PRSI.offset;

		owner->_hoops_CPGPR |= _hoops_ICHPA;
		/* _hoops_GRH _hoops_PRCA _hoops_IH _hoops_PCGR _hoops_IIGR _hoops_AIRA _hoops_CSPP (_hoops_APIP _hoops_IH _hoops_CRHIR _hoops_RGAR) */
		if (level == 0) {
			/* _hoops_HGI _hoops_HRGR _hoops_IRS _hoops_IGRH _hoops_CAAPH.	 _hoops_PS _hoops_HHGC _hoops_IS _hoops_RCAPI _hoops_PGGC _hoops_RH _hoops_AIRP
			 * _hoops_IIGR _hoops_RH _hoops_RHGS _hoops_CPAP, _hoops_AHSAR _hoops_SGS _hoops_SR _hoops_HHGC _hoops_RH _hoops_CCAH _hoops_RRCPR _hoops_IS _hoops_HS
			 * _hoops_RH _hoops_PSHR _hoops_ARCCA _hoops_PPR _hoops_RGSPR _hoops_GAR _hoops_ACAPI.  _hoops_PSPC _hoops_SR _hoops_IPS
			 * _hoops_ARCCA _hoops_PPR _hoops_RGSPR, _hoops_GGSHR _hoops_RH _hoops_SRGR _hoops_IIGR _hoops_RH _hoops_PGCR _hoops_SCHS _hoops_PCAPI,
			 * _hoops_PSCR _hoops_RCAPI _hoops_PGGC.
			 */
			Polyhedron *_hoops_HCAPI, *_hoops_ICAPI;

			if (owner->type == _hoops_IRCP) {
				HE_ERROR (HEC_LOD, HES_INVALID_TARGET,
					"Replacement of LOD level 0 invalid for segments.");
				return null;
			}
			if (owner->type != _hoops_SCIP && owner->type != _hoops_GSIP) {
				HE_ERROR (HEC_LOD, HES_INVALID_TARGET,
					"Replacement of LOD level 0 only valid for shells and meshes.");
				return null;
			}
			if (owner->type != geometry->type) {
				HE_ERROR (HEC_LOD, HES_INVALID_TARGET,
					"Replacement of LOD level 0 may not change type.");
				return null;
			}
			_hoops_HCAPI = (Polyhedron *)owner;
			_hoops_ICAPI = (Polyhedron *) geometry;

			_hoops_HCAPI->_hoops_CPGPR |= _hoops_ICAPI->_hoops_CPGPR;

			_hoops_SRCP = _hoops_HCAPI->owner;

			ASSERT (_hoops_ICAPI->_hoops_HIHI == 1);
			_hoops_RSAI (_hoops_HCAPI, Geometry, _hoops_ICAPI);

			if (!BIT (_hoops_RSPPR(_hoops_RIGC, flags), _hoops_APGHP)) {
				HI_Figure_Geometry_Bounding (geometry, bounding);
				_hoops_ICAPI->bounding = _hoops_HCAPI->bounding;
			}

			if (_hoops_HCAPI->type == _hoops_SCIP)
				Swap (*(Shell *)_hoops_HCAPI, *(Shell *)_hoops_ICAPI);
			else if (_hoops_HCAPI->type == _hoops_GSIP)
				Swap (*(_hoops_AIHPR *)_hoops_HCAPI, *(_hoops_AIHPR *)_hoops_ICAPI);

			_hoops_HCAPI->_hoops_HGAIR = _hoops_ICAPI->_hoops_HGAIR;

			_hoops_ICAPI->_hoops_HGAIR = null;
			_hoops_ICAPI->_hoops_IPPGR =  null;
			_hoops_ICAPI->_hoops_HIHI = 1;
			HI_Au_Revoir ((_hoops_HPAH *) _hoops_ICAPI);
			geometry = (Geometry *) _hoops_HCAPI;

			if (!_hoops_SHCIH)
				geometry->_hoops_RRHH |= _hoops_RSPCR;

			_hoops_HCAPI->bounding.Merge (bounding);
			if (_hoops_SRCP != null) {
				HI_Propagate_Bounding (_hoops_RIGC, _hoops_HCAPI->owner, bounding, null);
				_hoops_SRCP->_hoops_HSRIR.Merge (bounding);
			}
		}
		else {
			_hoops_PGAIR *		_hoops_HGAIR = null;

			switch (owner->type) {
				case _hoops_SCIP:
				case _hoops_GSIP: {
					Polyhedron *	_hoops_HCAPI = (Polyhedron *)owner;

					if ((_hoops_HGAIR = _hoops_HCAPI->_hoops_HGAIR) == null) {
						ZALLOC (_hoops_HGAIR, _hoops_PGAIR);
						_hoops_HCAPI->_hoops_HGAIR = _hoops_HGAIR;
						_hoops_HGAIR->type = _hoops_AGAIR;
						_hoops_HGAIR->owner = (_hoops_HPAH *)_hoops_HCAPI;
						_hoops_HGAIR->backlink = (_hoops_HPAH **) &_hoops_HCAPI->_hoops_HGAIR;
						_hoops_HGAIR->_hoops_HIHI = 1;
					}

					_hoops_SRCP = _hoops_HCAPI->owner;
	
					if (!BIT (_hoops_RSPPR(_hoops_RIGC, flags), _hoops_APGHP)) {
						HI_Figure_Geometry_Bounding (geometry, bounding);
						_hoops_HCAPI->bounding.Merge (bounding);
						if (_hoops_SRCP != null) {
							HI_Propagate_Bounding (_hoops_RIGC, _hoops_HCAPI->owner, bounding, null);
							_hoops_SRCP->_hoops_HSRIR.Merge (bounding);
						}
					}
				} break;

				case _hoops_IRCP: {
					_hoops_CRCP *	_hoops_CCAPI = (_hoops_CRCP *)owner;

					if ((_hoops_HGAIR = _hoops_CCAPI->_hoops_SSRIR()) == null) {
						ZALLOC (_hoops_HGAIR, _hoops_PGAIR);
						_hoops_HGAIR->type = _hoops_AGAIR;
						_hoops_HGAIR->owner = (_hoops_HPAH *)_hoops_CCAPI;
						_hoops_HGAIR->_hoops_HIHI = 1;
						_hoops_CCAPI->_hoops_GGAIR (_hoops_HGAIR);
					}

					if (!BIT (_hoops_RSPPR(_hoops_RIGC, flags), _hoops_APGHP)) {
						HI_Figure_Geometry_Bounding (geometry, bounding);
						HI_Propagate_Bounding (_hoops_RIGC, _hoops_CCAPI, bounding, null);
					}

					_hoops_SRCP = _hoops_CCAPI;
				} break;

				default: {
					HE_ERROR (HEC_INTERNAL_ERROR, HES_MOST_RECENT_OPEN,
							  "unrecognized LOD owner encountered in HI_Insert_Geometry");
					return null;
				}
			}

			level -= 1;
			if ((geometry->next = _hoops_HGAIR->data[level]) != null)
				geometry->next->backlink = &geometry->next;
			geometry->backlink = &_hoops_HGAIR->data[level];
			_hoops_HGAIR->data[level] = geometry;
			geometry->owner = null;
		}
	}
	else {
		if (thing->type == _hoops_CIRIR) {
			open_list = (_hoops_SIRIR const *)thing;
			if (open_list->_hoops_GCRIR == _hoops_RCRIR) {
				_hoops_SRCP = open_list->info.segment._hoops_IGRPR;
			}
		}
		else if (thing->type == _hoops_IRCP)
			_hoops_SRCP = (_hoops_CRCP *)thing;

		geometry->owner = _hoops_SRCP;

		HI_Invalidate_Segment_Display_Lists(_hoops_RIGC, _hoops_SRCP, geometry->type, geometry, 0);

		if (_hoops_SRCP->geometry == null)
			_hoops_GCAPI = _hoops_SSCCA;

		/*_hoops_CPS _hoops_SHS _hoops_ARI _hoops_CPSA _hoops_HRGR _hoops_PHHIP _hoops_PPR _hoops_RIP */
		/*_hoops_IPPAR _hoops_HIS _hoops_HA _hoops_CPSA _hoops_GGCR _hoops_RH _hoops_CPAP*/
		HI_Table_Insert_Geometry  (_hoops_SRCP, geometry);

		if (geometry->type == _hoops_AHIP) {
			_hoops_PHIP const *		_hoops_RRA = (_hoops_PHIP const *)geometry;

			if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
				_hoops_CRCP const *		ref = (_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0];

				if (BIT (ref->_hoops_PHSI, _hoops_HHSI))
					_hoops_SRCP->_hoops_PHSI |= _hoops_HHSI;
			}
			else {
				for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++) {
					if (_hoops_RRA->_hoops_IHIP[i]->type == _hoops_SCIP || _hoops_RRA->_hoops_IHIP[i]->type == _hoops_GSIP) {
						Polyhedron const *_hoops_IPRI = (Polyhedron const *)_hoops_RRA->_hoops_IHIP[i];

						if (_hoops_IPRI->local_face_attributes._hoops_CPIAA ||
							_hoops_IPRI->_hoops_IHHPR._hoops_CPIAA ||
							_hoops_IPRI->local_vertex_attributes._hoops_CPIAA)
							_hoops_SRCP->_hoops_PHSI |= _hoops_HHSI;
					}
				}
			}
		}

		if (!BIT (_hoops_RSPPR(_hoops_RIGC, flags), _hoops_APGHP) &&
			HI_Figure_Geometry_Bounding (geometry, bounding)) {

			if (_hoops_SRCP->_hoops_HSRIR == null)
				_hoops_SRCP->_hoops_HSRIR = bounding;
			else /* _hoops_GSSR _hoops_HASC */
				_hoops_SRCP->_hoops_HSRIR.Merge (bounding);

			HI_Propagate_Bounding (_hoops_RIGC, _hoops_SRCP, bounding, null);
		}
	}

	if (_hoops_SRCP != null) {
		if (!ALLBITS (_hoops_SRCP->_hoops_RCGC, _hoops_SIAPI))
			HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_SIAPI);

		if (BIT (_hoops_SIAPI, T_FACES))
			_hoops_CPGPR |= _hoops_CSCCA;
		if (BIT (_hoops_SIAPI, T_LIGHTS_FOR_FACES))
			_hoops_CPGPR |= _hoops_IISSR;
		_hoops_CPGPR |= _hoops_PISSR|_hoops_RPSIR | _hoops_GCAPI;
		_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_CPGPR);
	}

	return geometry;
}

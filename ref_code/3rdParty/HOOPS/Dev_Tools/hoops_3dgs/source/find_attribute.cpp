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
 * $Id: obf_tmp.txt 1.55 2010-09-17 19:42:09 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "phedron.h"

GLOBAL_FUNCTION Attribute * HI_Find_Attribute (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH const *		item,
	Type					type)
{
	_hoops_RSIIR(_hoops_RIGC);
	ASSERT(item != null);

	Attribute *	result = null;
	Type		_hoops_RHIPH = Abs(type);

_hoops_AHIPH:

	if (item->type == _hoops_IRCP ||
		(item->type >= _hoops_AHRIR && item->type <= _hoops_PHRIR)) {

		Attribute *	_hoops_ASGPR = null;

		if (item->type == _hoops_IRCP) {
			_hoops_CRCP * _hoops_SRCP = (_hoops_CRCP *)item;
			if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) {
				ASSERT(0);
				// _hoops_AA _hoops_GCHRR _hoops_ARI
				return result;
			}
			_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR;
		}
		else {
			Geometry const * geo = (Geometry const *)item;
			_hoops_ASGPR = geo->_hoops_IPPGR;
		}

		if (_hoops_ASGPR != null) do {
			if (_hoops_ASGPR->type >= _hoops_RHIPH) {
				if (_hoops_ASGPR->type == _hoops_RHIPH) {
					_hoops_PRRH(_hoops_ASGPR);
					result = _hoops_ASGPR;
				}
				break;
			}
		} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	}
	else if (item->type == _hoops_CIRIR) {
		_hoops_SIRIR const * _hoops_ASIIR = (_hoops_SIRIR const *)item; 
		if (_hoops_ASIIR->_hoops_GCRIR == _hoops_RCRIR) {
			item = (_hoops_HPAH const *)_hoops_ASIIR->info.segment._hoops_IGRPR;
			goto _hoops_AHIPH;
		}
		else if (_hoops_ASIIR->_hoops_GCRIR == _hoops_HCRIR) {
			item = (_hoops_HPAH const *)_hoops_ASIIR->info.geometry._hoops_IGRPR;
			goto _hoops_AHIPH;
		}
		else {
			result = HI_Find_Local_Attribute (_hoops_RIGC, _hoops_ASIIR, _hoops_RHIPH);
		}
	}

	if (result == null && type > 0)
		HE_ERROR (HEC_ATTRIBUTE, HES_NO_LOCAL_SETTING, "Attribute is not set.");

	return result;
}


local void _hoops_PHIPH (
	Attribute **	_hoops_HPHCR,
	int				type,
	float			index) {
	_hoops_SSGI *			color;
	_hoops_PCSGA *	findex;

	if (*_hoops_HPHCR == null) {
		ZALLOC (color, _hoops_SSGI);
		color->type = HK_COLOR;
		color->_hoops_HIHI = 1;
		color->_hoops_GHA = type;
		*_hoops_HPHCR = (Attribute *)color;
	}
	else
		color = (_hoops_SSGI *)*_hoops_HPHCR;

	ZALLOC (findex, _hoops_PCSGA);
	findex->next = color->colors;
	color->colors = findex;

	findex->type = _hoops_SHGRA;
	findex->_hoops_GHA = type;
	findex->value = index;
}


local void _hoops_HHIPH (
	Attribute	**_hoops_HPHCR,
	int				type,
	RGB			*rgb) {
	_hoops_SSGI		*color;
	_hoops_APCA *normal;

	if (*_hoops_HPHCR == null) {
		ZALLOC (color, _hoops_SSGI);
		color->type = HK_COLOR;
		color->_hoops_HIHI = 1;
		color->_hoops_GHA = type;
		*_hoops_HPHCR = (Attribute *)color;
	}
	else
		color = (_hoops_SSGI *)*_hoops_HPHCR;

	ZALLOC (normal, _hoops_APCA);
	normal->next = color->colors;
	color->colors = normal;

	normal->type = _hoops_PPCA;
	normal->_hoops_GHA = type;
	normal->rgb = *rgb;
}


local void _hoops_IHIPH (
	Attribute **	_hoops_HPHCR,
	int				type,
	RGBAS32 *		_hoops_PIHR) {
	_hoops_SSGI *			color;
	_hoops_APCA *	normal;

	if (*_hoops_HPHCR == null) {
		ZALLOC (color, _hoops_SSGI);
		color->type = HK_COLOR;
		color->_hoops_HIHI = 1;
		color->_hoops_GHA = type;
		*_hoops_HPHCR = (Attribute *)color;
	}
	else
		color = (_hoops_SSGI *)*_hoops_HPHCR;

	// _hoops_ACAC: _hoops_RHAR _hoops_HAIR _hoops_CCA _hoops_HPIHP?
	ZALLOC (normal, _hoops_APCA);
	normal->next = color->colors;
	color->colors = normal;

	normal->type = _hoops_PPCA;
	normal->_hoops_GHA = type;

	normal->rgb = *_hoops_PIHR;
}


GLOBAL_FUNCTION Attribute * HI_Find_Local_Attribute (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_SIRIR const *		_hoops_ASIIR,
	Type					type)
{
	_hoops_RSIIR(_hoops_RIGC);

	Attribute *	result = null;

	if (_hoops_ASIIR == null) {
		ASSERT(0);
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected open type");
	}
	else switch (_hoops_ASIIR->_hoops_GCRIR) {

		default: {
			ASSERT(0);
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected open type");
		}	break;

#ifndef DISABLE_GEOMETRY_ATTRIBUTES
		case _hoops_SCRIR: {

			Local_Vertex_Attributes *	_hoops_GIPGA;
			Polyhedron *	_hoops_IPRI	= _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR;
			int				offset		= _hoops_ASIIR->info._hoops_IPRI.offset;

#ifndef _hoops_GCGHR
			if (_hoops_IPRI->type == _hoops_CSIP) {
				PolyCylinder const *		_hoops_HSPIR = (PolyCylinder const *)_hoops_IPRI;
				_hoops_AGHIR *	_hoops_PGHIR;
				_hoops_CGHIR			flags;

				if (type == HK_COLOR && (_hoops_PGHIR = _hoops_HSPIR->_hoops_RGHIR) != null) {
					Attribute *	_hoops_CHIPH = null;

					flags = _hoops_PGHIR->flags[offset];

					if (BIT (flags, _hoops_GIRRA))
						_hoops_HHIPH (&_hoops_CHIPH,
						Color_FACE,
						&_hoops_PGHIR->fcolors[offset]);
					else if (BIT (flags, _hoops_CHRRA))
						_hoops_PHIPH (&_hoops_CHIPH,
						Color_FACE,
						_hoops_PGHIR->_hoops_IGHIR[offset]);

					if (BIT (flags, _hoops_SHRRA))
						_hoops_HHIPH (&_hoops_CHIPH,
						Color_EDGE,
						&_hoops_PGHIR->ecolors[offset]);
					else if (BIT (flags, _hoops_IHRRA))
						_hoops_PHIPH (&_hoops_CHIPH,
						Color_EDGE,
						_hoops_PGHIR->_hoops_HGHIR[offset]);

					if (_hoops_CHIPH != null)
						result = _hoops_CHIPH;
				}

				break;
			}
#endif
			_hoops_GIPGA = &_hoops_IPRI->local_vertex_attributes;

			if (*_hoops_GIPGA->_hoops_CHHPR(offset) != 0) {
				Local_Vertex_Flags	flags;

				flags = *_hoops_GIPGA->_hoops_CHHPR(offset);

				switch (type) {
					case HK_VISIBILITY: {
#  ifndef _hoops_IIICA
						if (ANYBIT (flags, _hoops_CIICA)) {
							_hoops_RSAIR	*vis;

							ZALLOC (vis, _hoops_RSAIR);
							vis->type = HK_VISIBILITY;
							vis->_hoops_HIHI = 1;
							vis->mask = T_MARKERS;
							if (BIT (flags, _hoops_PHIAA))
								vis->value = T_MARKERS;
							result = (Attribute *)vis;
						}
#  endif
					}	break;

					case HK_COLOR: {
#  ifndef _hoops_GCGHR
						Attribute	*_hoops_CHIPH = null;

						if (BIT (flags, _hoops_HCRRA))
							_hoops_HHIPH (&_hoops_CHIPH,
							Color_VERTEX,
							&_hoops_GIPGA->_hoops_PAHIR[offset]);
						else if (BIT (flags, _hoops_SIRRA))
							_hoops_PHIPH (&_hoops_CHIPH,
							Color_VERTEX,
							_hoops_GIPGA->_hoops_HAHIR[offset]);
						else if (BIT (flags, _hoops_CCRRA))
							_hoops_IHIPH (&_hoops_CHIPH,
							Color_VERTEX,
							&_hoops_GIPGA->_hoops_IAHIR[offset]);

						if (BIT (flags, _hoops_PPHPR))
							_hoops_HHIPH (&_hoops_CHIPH,
							Color_EDGE,
							&_hoops_GIPGA->ecolors[offset]);
						else if (BIT (flags, _hoops_RPHPR))
							_hoops_PHIPH (&_hoops_CHIPH,
							Color_EDGE,
							_hoops_GIPGA->_hoops_HGHIR[offset]);

						if (BIT (flags, _hoops_AARHR))
							_hoops_HHIPH (&_hoops_CHIPH,
							Color_FACE,
							&_hoops_GIPGA->fcolors[offset]);
						else if (BIT (flags, _hoops_HARHR))
							_hoops_PHIPH (&_hoops_CHIPH,
							Color_FACE,
							_hoops_GIPGA->_hoops_IGHIR[offset]);

						if (_hoops_CHIPH != null)
							result = _hoops_CHIPH;
#  endif
					}	break;

					case HK_MARKER_SYMBOL: {
#  ifndef _hoops_CSGHR
						if (BIT (flags, _hoops_SIICA)) {
							_hoops_GICAP		*_hoops_IRPP;
							_hoops_RPHIR			*sl;

							ZALLOC (_hoops_IRPP, _hoops_GICAP);
							_hoops_IRPP->type = HK_MARKER_SYMBOL;
							_hoops_IRPP->_hoops_HIHI = 1;
							sl = HI_LVA_Symbol_Lookup(_hoops_IPRI, _hoops_GIPGA->_hoops_SAHIR[offset]);
							HI_Copy_Name(&sl->name, &_hoops_IRPP->name);
							result = (Attribute *)_hoops_IRPP;
						}
#  endif
					}	break;

					case HK_MARKER_SIZE: {
#  ifndef _hoops_CSGHR
						if (BIT (flags, _hoops_GCICA)) {
							_hoops_AHCAP	*_hoops_IRPP;

							ZALLOC (_hoops_IRPP, _hoops_AHCAP);
							_hoops_IRPP->type = HK_MARKER_SIZE;
							_hoops_IRPP->_hoops_HIHI = 1;
							_hoops_IRPP->data.value = _hoops_GIPGA->_hoops_CAHIR[offset];
							_hoops_IRPP->data._hoops_HHP = _hoops_SHGRP;
							result = (Attribute *)_hoops_IRPP;
						}
#  endif
					}	  break;
				}
			}
		}	break;

		case _hoops_CCRIR: {
			
			Polyhedron *	_hoops_IPRI = _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR;
			int				offset = _hoops_ASIIR->info._hoops_IPRI.offset;
			_hoops_RPGHR *	_hoops_GIPGA = &_hoops_IPRI->_hoops_IHHPR;

			_hoops_GHHPR	flags;

			if (_hoops_GIPGA->flags != null) {
				flags = _hoops_GIPGA->flags[offset];

				switch (type) {
					case HK_COLOR: {
#  ifndef _hoops_GCGHR
						Attribute	*_hoops_CHIPH = null;

						if (BIT (flags, _hoops_SSRRA)) {
							_hoops_HHIPH (&_hoops_CHIPH,
								Color_EDGE,
								&_hoops_GIPGA->colors[offset]);
							result = _hoops_CHIPH;
						}
						else if (BIT (flags, _hoops_RPGI)) {
							_hoops_PHIPH (&_hoops_CHIPH,
								Color_EDGE,
								_hoops_GIPGA->findices[offset]);
							result = _hoops_CHIPH;
						}
#  endif
				}	break;

				case HK_VISIBILITY: {
#  ifndef _hoops_IIICA
					if (ANYBIT (flags, _hoops_ICICA)) {
						_hoops_RSAIR	*vis;

						ZALLOC (vis, _hoops_RSAIR);
						vis->type = HK_VISIBILITY;
						vis->_hoops_HIHI = 1;
						vis->mask = T_ANY_EDGE;
						if (BIT (flags, _hoops_APGI))
							vis->value = T_ANY_EDGE;
						result = (Attribute *)vis;
					}
#  endif
				}	break;

				case HK_EDGE_PATTERN: {
					if (BIT (flags, _hoops_GPGI)) {
#  ifndef _hoops_RGIPR
						_hoops_ISAIR *	_hoops_CSAIR;
						_hoops_HHHIR *			_hoops_IHHIR;

						ZALLOC (_hoops_CSAIR, _hoops_ISAIR);
						_hoops_CSAIR->type = HK_EDGE_PATTERN;
						_hoops_CSAIR->_hoops_HIHI = 1;
						_hoops_IHHIR = HI_LEA_Pattern_Lookup(_hoops_IPRI, _hoops_GIPGA->_hoops_AHHIR[offset]);
						HI_Copy_Name(&_hoops_IHHIR->name, &_hoops_CSAIR->line_style);
						result = (Attribute *)_hoops_CSAIR;
						/* _hoops_PSP _hoops_CCAH _hoops_SHIPH _hoops_RRGR? */
					}
#  endif
				}	break;

				case HK_EDGE_WEIGHT: {
#  ifndef _hoops_RGIPR
					if (BIT (flags, _hoops_SCICA)) {
						_hoops_RHCAP *	_hoops_PSGIP;

						ZALLOC (_hoops_PSGIP, _hoops_RHCAP);
						_hoops_PSGIP->type = HK_EDGE_WEIGHT;
						_hoops_PSGIP->_hoops_HIHI = 1;
						_hoops_PSGIP->data.value = _hoops_GIPGA->weights[offset];
						result = (Attribute *)_hoops_PSGIP;
					}
#  endif
				}	break;
			}
		}
	}	break;

	case _hoops_ICRIR: {

		Polyhedron *			_hoops_IPRI	= _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR;
		int						offset		= _hoops_ASIIR->info._hoops_IPRI.offset;
		Local_Face_Attributes *	_hoops_GIPGA		= &_hoops_IPRI->local_face_attributes;
		_hoops_GIIPR		flags = *(_hoops_GIPGA->_hoops_CHHPR(offset));

		switch (type) {
			case HK_COLOR: {
#  ifndef _hoops_GCGHR
				Attribute	*_hoops_CHIPH = null;

				if (BIT (flags, LFA_EXPLICIT_COLOR_BY_VALUE)) {
					_hoops_HHIPH (&_hoops_CHIPH,
						Color_FACE,
						&_hoops_GIPGA->colors[offset]);
					result = _hoops_CHIPH;
				}
				else if (BIT (flags, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
					_hoops_PHIPH (&_hoops_CHIPH,
						Color_FACE,
						_hoops_GIPGA->findices[offset]);
					result = _hoops_CHIPH;
				}
#  endif
			}	break;

			case HK_VISIBILITY: {
#  ifndef _hoops_IIICA
				if (ANYBIT (flags, _hoops_HRAPA)) {
					_hoops_RSAIR	*vis;

					ZALLOC (vis, _hoops_RSAIR);
					vis->type = HK_VISIBILITY;
					vis->_hoops_HIHI = 1;
					vis->mask = T_FACES;
					if (BIT (flags, _hoops_IAGI))
						vis->value = T_FACES;
					result = (Attribute *)vis;
				}
#  endif
			}	  break;

			case HK_FACE_PATTERN: {
#  ifndef _hoops_PGPHR
				if (BIT (flags, _hoops_HAGI)) {
					_hoops_IHCAP *_hoops_HCHPR;

					ZALLOC (_hoops_HCHPR, _hoops_IHCAP);
					_hoops_HCHPR->type = HK_FACE_PATTERN;
					_hoops_HCHPR->_hoops_HIHI = 1;
					_hoops_HCHPR->value = _hoops_IRGCR (_hoops_GIPGA->_hoops_AHHIR[offset]);
					result = (Attribute *)_hoops_HCHPR;
				}
#  endif
			}	break;
		}
	}	break;
#endif
}
	return result;
}





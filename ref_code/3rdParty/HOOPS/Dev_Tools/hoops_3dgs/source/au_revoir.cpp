/*
 * Copyright (c) 1998-2001 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.350 2010-12-03 00:42:47 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "please.h"
#include "path.h"
#include "phedron.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "task_queue.h"
#include "adt.h"




local void _hoops_AARIR (UV_Trim *node) {
	if (node->next != null)
		_hoops_AARIR (node->next); /* _hoops_GHHA */
	HI_Delete_Trim (node);
}


GLOBAL_FUNCTION void HI_Delete_Trim (UV_Trim *node) {
	int knot_count;

	switch (node->type) {
		case _hoops_PARIR: {
			UV_Trim_Poly *		_hoops_HARIR = (UV_Trim_Poly *)node;

			FREE_ARRAY (_hoops_HARIR->points, _hoops_HARIR->count, UV_Point);
			FREE (_hoops_HARIR, UV_Trim_Poly);
		}	break;

		case _hoops_IARIR: {
			UV_Trim_Curve *		curve = (UV_Trim_Curve *)node;

			knot_count = curve->control_point_count + curve->degree + 1;
			FREE_ARRAY (curve->control_points, curve->control_point_count, UV_Point);
			if (curve->weights != null)
				FREE_ARRAY (curve->weights, curve->control_point_count, float);
			if (curve->knots != null)
				FREE_ARRAY (curve->knots, knot_count, float);
			FREE (curve, UV_Trim_Curve);
		}	break;

		case _hoops_CARIR: {
			UV_Trim_Collection *		_hoops_SARIR = (UV_Trim_Collection *)node;

			if (_hoops_SARIR->_hoops_GPRIR != null)
				_hoops_AARIR (_hoops_SARIR->_hoops_GPRIR);
			FREE (_hoops_SARIR, UV_Trim_Collection);
		}	break;

		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "Unexpected trim type in nurbs surface trim list");
			break;
	}
}

local void _hoops_RPRIR (
	_hoops_HPAH		*thing) {
	_hoops_HPAH		*_hoops_APRIR;

	do {
		_hoops_APRIR = thing->next;
#if 0
		if (HOOPS_WORLD->_hoops_PPRIR && thing->_hoops_HIHI > 1)
			printf("L: %p\n", (void*)thing);
#endif
		/* _hoops_RPP _hoops_SCH _hoops_HPRIR _hoops_IPRIR _hoops_SCH _hoops_PSCR _hoops_SCH _hoops_ASSP'_hoops_RA _hoops_HAII _hoops_SCH _hoops_CPRIR */
		thing->owner = null;
		thing->next = null;
		thing->backlink = null;
		_hoops_HPRH (thing);
	} while ((thing = _hoops_APRIR) != null);
}


GLOBAL_FUNCTION void HI_Au_Revoir (
	_hoops_HPAH *	thing) 
{
	_hoops_HPAH *	next;

#		define	Q_INUTILE(ref)	  do {												\
					if (_hoops_SPRIR ((_hoops_GHRIR alter *)&(ref)->_hoops_HIHI) == 0)	\
						next = (_hoops_HPAH *)ref;										\
					else next = null;												\
				} while (0)


	/* _hoops_GASA: _hoops_SHH _hoops_RHRIR! _hoops_RGR _hoops_APSH _hoops_PII _hoops_SCH'_hoops_GRI _hoops_CPIC _hoops_IS _hoops_HAPR, _hoops_HIH _hoops_SCH _hoops_ASSP'_hoops_RA _hoops_AHSAR _hoops_GGR _hoops_GRH _hoops_ARAR. */
	do {
		if (thing->type >= _hoops_AHRIR && thing->type <= _hoops_PHRIR) {
			Attribute *		_hoops_IPPGR;

			if ((_hoops_IPPGR = ((Geometry *)thing)->_hoops_IPPGR) != null)
				_hoops_RPRIR ((_hoops_HPAH *)_hoops_IPPGR);
		}

		if (HOOPS_WORLD->_hoops_HHRIR &&
			thing->type >= _hoops_AHRIR && thing->type <= _hoops_IHRIR) {
			if (BIT (thing->_hoops_RRHH, _hoops_CHRIR)) {
				int const *			mapping = null;
				int					count = 0;

				if (thing->type == _hoops_HIIP) {
					_hoops_SHRIR const *	_hoops_GIRIR = (_hoops_SHRIR const *)thing;

					mapping = _hoops_GIRIR->mapping;
					count = -_hoops_GIRIR->count / 2;
				}
				else if (thing->type == _hoops_PIRS) {
					_hoops_GRPGR const *	_hoops_CPAI = (_hoops_GRPGR const *)thing;

					mapping = _hoops_CPAI->mapping;
					count = _hoops_CPAI->count;
				}

				while (count-- > 0)
					HOOPS_WORLD->_hoops_HHRIR(~(POINTER_SIZED_INT)(*mapping++ & ~_hoops_RIRIR));
			}
			else
				HOOPS_WORLD->_hoops_HHRIR(_hoops_AIRIR(thing));
		}

		next = null;

		switch (thing->type) {
		case _hoops_PIRIR:	/* _hoops_RAIA _hoops_RH _hoops_GCIS _hoops_HRPR */
		case _hoops_AGRPR: {
			_hoops_PGRPR *		include = (_hoops_PGRPR *)thing;

			if (include->_hoops_IGRPR != null) {
				if (include->owner != null &&
					BIT(include->owner->_hoops_RRHH, _hoops_HIRIR))  {
					_hoops_AIGPR *	_hoops_RIGC;
					_hoops_IIRIR(_hoops_RIGC);
					HI_Clean_Static_Tree(_hoops_RIGC, (_hoops_CRCP *)include->_hoops_IGRPR);
				}

				Q_INUTILE (include->_hoops_IGRPR);
			}

			HI_Free_Conditional (&include->condition);
			FREE (include, _hoops_PGRPR);
		}	break;

		case _hoops_CIRIR: {
			_hoops_SIRIR *		open_list = (_hoops_SIRIR *)thing;

			switch (open_list->_hoops_GCRIR) {
				case _hoops_RCRIR: {
					if (open_list->info.segment._hoops_ACRIR != null)
						_hoops_HPRH (open_list->info.segment._hoops_ACRIR);

					_hoops_HPRH (open_list->info.segment._hoops_PCRIR);
					Q_INUTILE (open_list->info.segment._hoops_IGRPR);
				}	break;

#ifndef DISABLE_GEOMETRY_ATTRIBUTES
				case _hoops_HCRIR: {
					Q_INUTILE (open_list->info.geometry._hoops_IGRPR);
				}	break;

				case _hoops_ICRIR:
				case _hoops_CCRIR:
				case _hoops_SCRIR:
				case _hoops_GSRIR:
#endif
				case _hoops_RSRIR: {
					Q_INUTILE (open_list->info._hoops_IPRI._hoops_IGRPR);
				}	break;

				case _hoops_ASRIR: {
					Q_INUTILE (open_list->info._hoops_PSRIR._hoops_IGRPR);
				}	break;

				default: {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									   "Unexpected Open type");
				}	break;
			}

			FREE (thing, _hoops_SIRIR);
		}	break;

		case _hoops_IRCP: {
			_hoops_CRCP	*		segment = (_hoops_CRCP *)thing;

			segment->bounding.release();
			segment->_hoops_HSRIR.release();

			if (segment->geometry != null)
				_hoops_RPRIR ((_hoops_HPAH *)segment->geometry);

			if (segment->_hoops_GACP)
				delete segment->_hoops_GACP;

			if (segment->_hoops_SCGPR() != null) {
				_hoops_RPRIR ((_hoops_HPAH *)segment->_hoops_SCGPR());
				segment->_hoops_RSGPR (null);
			}

			if (segment->_hoops_PRRPR() != null) {
				_hoops_RPRIR ((_hoops_HPAH *)segment->_hoops_PRRPR());
				segment->_hoops_HRRPR (null);
			}

			segment->_hoops_ISRIR (null);

			if (segment->_hoops_IPPGR != null)
				_hoops_RPRIR ((_hoops_HPAH *)segment->_hoops_IPPGR);

			/* _hoops_AA _hoops_RGR _hoops_HRGHR _hoops_IS _hoops_HHSA _hoops_IPGR _hoops_GPP _hoops_RH _hoops_CGHI _hoops_SPR
			 * (_hoops_RGR _hoops_HRGR _hoops_IH _hoops_CSRIR _hoops_SGHC)
			 */

			if ((next = (_hoops_HPAH *)segment->_hoops_RGRPR) != null) {
				_hoops_HPAH		*save;
				_hoops_RGGA ((save = next->next) == null) {
					_hoops_HPRH (next);
					next = save;
				}
				next->owner = null;
				Q_INUTILE (next);
			}

			if (segment->_hoops_SSRIR() != null)
				HI_Au_Revoir ((_hoops_HPAH *)segment->_hoops_SSRIR());
			segment->_hoops_GGAIR (null);	// _hoops_SCAC _hoops_IHAH _hoops_HRPR _hoops_RPP _hoops_CISI _hoops_CCA _hoops_IRAP _hoops_RARP

			delete segment->extended;

			_hoops_RGAIR (segment->name);
			FREE (segment, _hoops_CRCP);
		}	break;

		case _hoops_AGAIR: {
			_hoops_PGAIR *		_hoops_HGAIR = (_hoops_PGAIR *)thing;

			if (_hoops_HGAIR->backlink != null)
				*_hoops_HGAIR->backlink = _hoops_HGAIR->next;	 /* _hoops_IPIH _hoops_SHR _hoops_IRAP */
			for (int i = 0; i < _hoops_IGAIR; i++) {
				if (_hoops_HGAIR->data[i] != null) {
					_hoops_HPAH	*ptr, *_hoops_CGAIR;

					ptr = (_hoops_HPAH *)_hoops_HGAIR->data[i];
					do {
						_hoops_CGAIR = ptr->next;
						HI_Au_Revoir ((_hoops_HPAH *)ptr);
					} while ((ptr = _hoops_CGAIR) != null);
				}
			}
			FREE (_hoops_HGAIR, _hoops_PGAIR);
		}	break;

#ifndef DISABLE_STYLE_SEGMENT
		case HK_STYLE: {
			Style alter *			style = (Style *)thing;

			if (style->_hoops_IGRPR)
				Q_INUTILE (style->_hoops_IGRPR);
			HI_Free_Conditional (&style->condition);
			_hoops_RGAIR(style->_hoops_SGAIR);
			FREE (style, Style);
		}	break;
#endif

		case _hoops_GRAIR: {
			FREE (thing, _hoops_RRAIR);
		}	break;

		case HK_HANDEDNESS: {
			FREE (thing, _hoops_ARAIR);
		}	break;

		case _hoops_PRAIR: {
			_hoops_HRAIR (HEC_FATAL_ERROR, HES_CANNOT_DESTROY_WORLD,
					"Haven't learned to Delete the world");
		}	break;

		case HK_CAMERA: {
			_hoops_HHRA *		_hoops_SPH = (_hoops_HHRA *)thing;
			_hoops_SPH->_hoops_PRPA._hoops_APRA.release();
			_hoops_SPH->_hoops_AIIH._hoops_APRA.release();
			_hoops_SPH->_hoops_GRCC._hoops_APRA.release();
			FREE (thing, _hoops_HHRA);
		}	break;

		case HK_CLIP_REGION: {
			_hoops_IRAIR alter *		_hoops_CRAIR = (_hoops_IRAIR *)thing;

			if (_hoops_CRAIR->count > 0)
				FREE_ARRAY (_hoops_CRAIR->points, _hoops_CRAIR->count, Point);
			FREE (_hoops_CRAIR, _hoops_IRAIR);
		}	break;

#ifndef DISABLE_COLOR_MAPS
		case HK_COLOR_MAP: {
			_hoops_RHAH alter *		_hoops_SRAIR = (_hoops_RHAH *)thing;

			if (_hoops_SRAIR->length > 0) {
				HI_Free_Material_Names (_hoops_SRAIR->_hoops_HAA, _hoops_SRAIR->length);
				FREE_ARRAY (_hoops_SRAIR->_hoops_HAA, _hoops_SRAIR->length, Named_Material);
			}
			FREE (_hoops_SRAIR, _hoops_RHAH);
		}	break;
#endif

		case HK_MODELLING_MATRIX: {
			((_hoops_ISGI *)thing)->matrix._hoops_APRA.release();
			FREE (thing, _hoops_ISGI);
		}	break;

		case HK_TEXTURE_MATRIX: {
			((_hoops_GAAIR *)thing)->matrix._hoops_APRA.release();
			FREE (thing, _hoops_GAAIR);
		}	break;

		case _hoops_RAAIR: {
			_hoops_AAAIR *			_hoops_PAAIR = (_hoops_AAAIR *)thing;

			if (_hoops_PAAIR->count > 0) {
				for (int i=0; i<_hoops_PAAIR->count; i++)
					_hoops_PAAIR->glyphs[i] = null;

				FREE_ARRAY (_hoops_PAAIR->glyphs, _hoops_PAAIR->count, _hoops_GASC);
				FREE_ARRAY (_hoops_PAAIR->keys, _hoops_PAAIR->count, Integer32);
			}
			FREE (_hoops_PAAIR, _hoops_AAAIR);
		}	break;

		case _hoops_HAAIR: {
			_hoops_IAAIR *		_hoops_CAAIR = (_hoops_IAAIR *)thing;

			if (_hoops_CAAIR->count > 0) {
				for (int i=0; i<_hoops_CAAIR->count; i++)
					_hoops_CAAIR->_hoops_SAAIR[i] = null;

				FREE_ARRAY (_hoops_CAAIR->_hoops_SAAIR, _hoops_CAAIR->count, _hoops_GPAIR);
				FREE_ARRAY (_hoops_CAAIR->keys, _hoops_CAAIR->count, Integer32);
			}
			FREE (_hoops_CAAIR, _hoops_IAAIR);
		}	break;

		case _hoops_RPAIR: {
			_hoops_APAIR *		_hoops_PPAIR = (_hoops_APAIR *)thing;

			if (_hoops_PPAIR->count > 0) {
				for (int i=0; i<_hoops_PPAIR->count; i++)
					_hoops_PPAIR->_hoops_HPAIR[i] = null;

				FREE_ARRAY (_hoops_PPAIR->_hoops_HPAIR, _hoops_PPAIR->count, Line_Style);
				FREE_ARRAY (_hoops_PPAIR->keys, _hoops_PPAIR->count, Integer32);
			}

			FREE (_hoops_PPAIR, _hoops_APAIR);
		}	break;

		case _hoops_IPAIR: {
			_hoops_CPAIR *			_hoops_SPAIR = (_hoops_CPAIR *)thing;

			if (_hoops_SPAIR->count > 0) {
				for (int i=0; i<_hoops_SPAIR->count; i++) {
					_hoops_RCR *		texture = _hoops_SPAIR->textures[i];

					if (texture->image != null && texture->_hoops_HIHI == 2) {
						if (texture->image->texture == texture)
							texture->image->texture = null;
						texture->owner = null;
						_hoops_HPRH (texture->image);
						_hoops_HPRH (texture);
						texture->image = null;
					}

					_hoops_RPRIR ((_hoops_HPAH *)texture);
				}

				FREE_ARRAY (_hoops_SPAIR->textures, _hoops_SPAIR->count, _hoops_RCR *);
				FREE_ARRAY (_hoops_SPAIR->keys, _hoops_SPAIR->count, Integer32);
			}
			FREE (_hoops_SPAIR, _hoops_CPAIR);
		}	break;

		case HK_WINDOW: {
			FREE (thing, Window);
		}	break;

		case HK_HEURISTICS: {
			FREE (thing, _hoops_GHAIR);
		}	break;

		case HK_RENDERING_OPTIONS: {
			_hoops_RHAIR *		_hoops_AHAIR = (_hoops_RHAIR *)thing;

			if (_hoops_AHAIR->_hoops_PRSI != null) {
				_hoops_AHAIR->_hoops_PRSI->bounding.release();
				FREE (_hoops_AHAIR->_hoops_PRSI, _hoops_PHAIR);
			}

			if (_hoops_AHAIR->_hoops_HHAIR != null) {
				_hoops_RGAIR (_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.color.name);

				if (_hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR._hoops_CHAIR) {
					Style *	style = _hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR._hoops_CHAIR;

					if ((*style->_hoops_SHAIR = style->_hoops_GRRPR) != null)
						style->_hoops_GRRPR->_hoops_SHAIR=style->_hoops_SHAIR;
					_hoops_HPRH (style);
				}
				_hoops_RGAIR (_hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR);
				FREE (_hoops_AHAIR->_hoops_HHAIR, _hoops_RIAIR);
			}

			if (_hoops_AHAIR->_hoops_AIAIR) {
				_hoops_RGAIR (_hoops_AHAIR->_hoops_AIAIR->_hoops_PIAIR);
				FREE (_hoops_AHAIR->_hoops_AIAIR, _hoops_HIAIR);
			}

			if (_hoops_AHAIR->_hoops_IIAIR != null) {

				if (_hoops_AHAIR->_hoops_IIAIR->_hoops_CIAIR != 0) {
					FREE_ARRAY (_hoops_AHAIR->_hoops_IIAIR->_hoops_SIAIR, _hoops_AHAIR->_hoops_IIAIR->_hoops_CIAIR, float);
				}

				if (_hoops_AHAIR->_hoops_IIAIR->_hoops_GCAIR != 0) {
					FREE_ARRAY (_hoops_AHAIR->_hoops_IIAIR->colors, _hoops_AHAIR->_hoops_IIAIR->_hoops_GCAIR, RGB);
				}

				if (_hoops_AHAIR->_hoops_IIAIR->_hoops_RCAIR != 0) {
					for (int i=0; i<_hoops_AHAIR->_hoops_IIAIR->_hoops_RCAIR; i++)
						_hoops_RGAIR (_hoops_AHAIR->_hoops_IIAIR->_hoops_ACAIR[i]);
					FREE_ARRAY (_hoops_AHAIR->_hoops_IIAIR->_hoops_ACAIR, _hoops_AHAIR->_hoops_IIAIR->_hoops_RCAIR, _hoops_HCRPR);

					FREE_ARRAY (_hoops_AHAIR->_hoops_IIAIR->_hoops_PCAIR, _hoops_AHAIR->_hoops_IIAIR->_hoops_RCAIR, Integer32);
				}

				if (_hoops_AHAIR->_hoops_IIAIR->weight_count != 0) {
					FREE_ARRAY (_hoops_AHAIR->_hoops_IIAIR->weights, _hoops_AHAIR->_hoops_IIAIR->weight_count, _hoops_HCAIR);
				}
				FREE (_hoops_AHAIR->_hoops_IIAIR, _hoops_ICAIR);
			}

			if (_hoops_AHAIR->locks != null)
				FREE (_hoops_AHAIR->locks, _hoops_CCAIR);
			
			if (_hoops_AHAIR->geometry != null)
				FREE (_hoops_AHAIR->geometry, _hoops_SCAIR);
			
			FREE (thing, _hoops_RHAIR);
		}	break;

		case HK_WINDOW_FRAME: {
			FREE (thing, _hoops_GSAIR);
		}	break;

		case HK_VISIBILITY: {
			FREE (thing, _hoops_RSAIR);
		}	break;

		case HK_SELECTABILITY: {
			FREE (thing, _hoops_ASAIR);
		}	break;

		case HK_COLOR: {
			_hoops_SSGI *				color = (_hoops_SSGI *)thing;

			HI_Free_Colors (color->colors);

			FREE (thing, _hoops_SSGI);
		}	break;

		case HK_LINE_PATTERN: {
			_hoops_PSAIR *	_hoops_HSAIR = (_hoops_PSAIR *)thing;
			_hoops_RGAIR(_hoops_HSAIR->line_style);
			_hoops_RGAIR(_hoops_HSAIR->start_glyph);
			_hoops_RGAIR(_hoops_HSAIR->middle_glyph);
			_hoops_RGAIR(_hoops_HSAIR->end_glyph);
			FREE (_hoops_HSAIR, _hoops_PSAIR);
		}	break;

		case HK_EDGE_PATTERN: {
			_hoops_ISAIR *	_hoops_CSAIR = (_hoops_ISAIR *)thing;
			_hoops_RGAIR(_hoops_CSAIR->line_style);
			FREE (_hoops_CSAIR, _hoops_ISAIR);
		}	break;

		case HK_MARKER_SYMBOL: {
			_hoops_SSAIR *		_hoops_IRPP = (_hoops_SSAIR *)thing;
			_hoops_RGAIR(_hoops_IRPP->name);
			FREE (_hoops_IRPP, _hoops_SSAIR);
		}	break;

		case HK_FACE_PATTERN:
		case HK_WINDOW_PATTERN:
		case HK_TEXT_ALIGNMENT: {
			FREE (thing, _hoops_GGPIR);
		}	break;

		case HK_TEXT_PATH: {
			FREE (thing, _hoops_RGPIR);
		}	break;

		case HK_TEXT_FONT: {
			_hoops_AGPIR *		_hoops_PGPIR = (_hoops_AGPIR *)thing;

			if (_hoops_PGPIR->_hoops_HGPIR != null) {
				_hoops_IGPIR	*name;

				if ((name = _hoops_PGPIR->_hoops_HGPIR) != null)
					HI_Free_Font_Names(name);
			}

			FREE (_hoops_PGPIR, _hoops_AGPIR);
		}	break;

		case HK_DRIVER: {
			_hoops_GGAGR *			_hoops_GHRI = (_hoops_GGAGR *)thing;

			if (!BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_SGPIR) &&
				_hoops_GHRI->_hoops_PPRPR != null)
				HI_Queue_Actor_Shutdown(_hoops_GHRI, true);
			else
				ASSERT(_hoops_GHRI->_hoops_PPRPR == null);

			if (_hoops_GHRI->_hoops_GRPIR) {
				delete _hoops_GHRI->_hoops_GRPIR;
				_hoops_GHRI->_hoops_GRPIR = null;
			}

			if (_hoops_GHRI->_hoops_ACARR) {
				delete _hoops_GHRI->_hoops_ACARR;
				_hoops_GHRI->_hoops_ACARR = null;
			}

			_hoops_RRPIR	*	sl;

			while ((sl = _hoops_GHRI->_hoops_ARPIR) != null) {
				_hoops_GHRI->_hoops_ARPIR = sl->prev;

				_hoops_PRPIR (sl->string);
				FREE (sl, _hoops_RRPIR);
			}

			_hoops_PRPIR (_hoops_GHRI->_hoops_HRPIR);

			if (_hoops_GHRI->_hoops_CPCR._hoops_IRPIR != null)
				FREE_ARRAY (_hoops_GHRI->_hoops_CPCR._hoops_IRPIR, _hoops_CRPIR + 1, int);

			if (_hoops_GHRI->_hoops_RCSHR._hoops_IRPIR != null)
				FREE_ARRAY (_hoops_GHRI->_hoops_RCSHR._hoops_IRPIR, _hoops_CRPIR + 1, int);

			if (_hoops_GHRI->_hoops_RCSHR.target != _hoops_GHRI && _hoops_GHRI->_hoops_RCSHR.target != null)
				_hoops_HPRH (_hoops_GHRI->_hoops_RCSHR.target);

			if (_hoops_GHRI->_hoops_RCSHR._hoops_SRPIR != null)
				_hoops_HPRH (_hoops_GHRI->_hoops_RCSHR._hoops_SRPIR);

			if (_hoops_GHRI->_hoops_CPCR.target != _hoops_GHRI && _hoops_GHRI->_hoops_CPCR.target != null)
				_hoops_HPRH (_hoops_GHRI->_hoops_CPCR.target);

			if (_hoops_GHRI->_hoops_CPCR._hoops_SRPIR != null)
				Q_INUTILE (_hoops_GHRI->_hoops_CPCR._hoops_SRPIR);

			FREE (_hoops_GHRI, _hoops_GGAGR);
		}	break;

		case HK_DRIVER_OPTIONS: {
			_hoops_GAPIR *	_hoops_RAPIR = (_hoops_GAPIR *)thing;
			_hoops_IGPIR *			name;
			_hoops_AAPIR *			_hoops_PAPIR = _hoops_RAPIR->_hoops_HAPIR;

			_hoops_RGAIR (_hoops_RAPIR->_hoops_IAPIR);

			while (_hoops_PAPIR != null) {
				_hoops_AAPIR *		_hoops_CAPIR = _hoops_PAPIR->next;

				_hoops_RGAIR(_hoops_PAPIR->name);
				FREE (_hoops_PAPIR, _hoops_AAPIR);
				_hoops_PAPIR = _hoops_CAPIR;
			}

			if ((name = _hoops_RAPIR->_hoops_SAPIR) != null)
				HI_Free_Font_Names(name);

			if ((name = _hoops_RAPIR->_hoops_GPPIR) != null)
				HI_Free_Font_Names(name);

			if (_hoops_RAPIR->_hoops_RPPIR != null)
				FREE_ARRAY (_hoops_RAPIR->_hoops_RPPIR, _hoops_RAPIR->_hoops_APPIR, int);

			if (_hoops_RAPIR->_hoops_PPPIR != null)
				_hoops_HPRH (_hoops_RAPIR->_hoops_PPPIR);

			FREE (_hoops_RAPIR, _hoops_GAPIR);
		}	break;

		case HK_USER_OPTIONS: {
			_hoops_HPPIR *		_hoops_IPPIR = (_hoops_HPPIR *)thing;

			_hoops_AIGPR *	_hoops_RIGC;
			_hoops_IIRIR(_hoops_RIGC);

			HI_Free_User_Option(_hoops_RIGC, _hoops_IPPIR);
		}	break;

		case _hoops_CPPIR: {
			_hoops_SPPIR *		_hoops_GHPIR = (_hoops_SPPIR *)thing;

			HI_Free_Condition(_hoops_GHPIR);

		}	break;

		case HK_USER_VALUE: {
			FREE (thing, _hoops_RHPIR);
		}	break;

		case HK_LINE_WEIGHT:
		case HK_EDGE_WEIGHT:
		case HK_TEXT_SPACING:
		case HK_MARKER_SIZE: {
			FREE (thing, _hoops_AHPIR);
		}	break;

		case _hoops_SGCP: {
			if (BIT (thing->_hoops_RRHH, _hoops_SHHI))
				FREE (thing, _hoops_AIHI);
			else
				FREE (thing, _hoops_PHPIR);
		}	break;

		case _hoops_RIIP:
		case _hoops_GRCP:
		case _hoops_RRCP: {
			if (BIT (thing->_hoops_RRHH, _hoops_SHHI))
				FREE (thing, Circular_Arc_Lite);
			else
				FREE (thing, Circular_Arc);
		}	break;

		case _hoops_HGPGR: {
			_hoops_HHPIR *		_hoops_RPPA = (_hoops_HHPIR *)thing;

			if (_hoops_RPPA->count > 0)
				FREE_ARRAY (_hoops_RPPA->planes, _hoops_RPPA->count, _hoops_ARPA);
			FREE (_hoops_RPPA, _hoops_HHPIR);
		}	break;

		case _hoops_CGCP: {
			FREE (thing, Ellipse);
		}	break;

		case _hoops_GIIP: {
			FREE (thing, Elliptical_Arc);
		}	break;

		case _hoops_GGCP: {
			FREE (thing, Grid);
		}	break;

		case _hoops_PCIP: {
			Marker *			marker = (Marker *) thing;

			if (marker->orientation != null)
				if (BIT(marker->_hoops_RRHH, _hoops_IHPIR))
					FREE_ARRAY (marker->orientation, 2, Vector);
				else
					FREE_ARRAY (marker->orientation, 1, Vector);
			FREE (marker, Marker);
		}	break;

		case _hoops_PIRS: {
			_hoops_GRPGR *		_hoops_CHPIR = (_hoops_GRPGR *)thing;

			if (_hoops_CHPIR->allocated > 0)
				FREE_ARRAY (_hoops_CHPIR->points, _hoops_CHPIR->allocated, Point);
			if (_hoops_CHPIR->mapping != null) {
				for (int i = 0; i < _hoops_CHPIR->count; ++i)
					HI_Remove_Lightweight_Key (_hoops_CHPIR->mapping[i]);

				FREE_ARRAY (_hoops_CHPIR->mapping, _hoops_CHPIR->allocated, int);
			}
			FREE (thing, _hoops_GRPGR);
		}	break;

		case _hoops_ICIP: {
			_hoops_SHPIR *		light = (_hoops_SHPIR *) thing;	// _hoops_GIPIR _hoops_HRGR _hoops_RH _hoops_RGAR _hoops_SPR _hoops_SR _hoops_RRP _hoops_IS _hoops_RIPIR _hoops_CRGR

			switch (light->_hoops_PRR) {
				case _hoops_S: {
					if (light->count != 0)
						FREE_ARRAY (light->points, light->count, Point);
					FREE (light, _hoops_SHPIR);
				} break;
				case _hoops_C: {
					FREE (light, _hoops_AIPIR);
				} break;
				case _hoops_I: {
					FREE (light, _hoops_PIPIR);
				} break;
				case _hoops_H: {
					FREE (light, _hoops_HIPIR);
				} break;
			}
		}	break;

		case _hoops_GHPGR: {
			FREE (thing, _hoops_RHPGR);
		}	break;

		case _hoops_HGCP: {
			Image alter *		image = (Image *)thing;
			void const * const *_hoops_GAAC;
			_hoops_GACR *		dl;

			_hoops_GAAC = image->rasters;

			if (BIT (image->_hoops_RRHH, _hoops_IIPIR)) {}
			else if (image->_hoops_PHGH != null) {
				if (BIT (image->flags, _hoops_SSGH))
					FREE_ARRAY (image->_hoops_PHGH, image->_hoops_IARH, char);
				else
					if (image->row_bytes * image->height > 0)
						FREE_ARRAY (image->_hoops_PHGH, image->row_bytes * image->height, char);
			}
			else if (!ANYBIT (image->flags,_hoops_APAH|_hoops_GRRH)) {
				/* _hoops_RH _hoops_CIPIR _hoops_SIPIR _hoops_HRGR _hoops_IRS _hoops_IGRH _hoops_PRGIR, _hoops_HIH
				 * _hoops_HACAR _hoops_GPP _hoops_SISPR _hoops_IS _hoops_CICA _hoops_GGSR _hoops_IIHA _hoops_GPP _hoops_RH _hoops_GPRR */
				int row_bytes = image->width * image->_hoops_GCPIR;

				_hoops_GAAC += image->height;
				do {
					--_hoops_GAAC;
					FREE_ARRAY (*_hoops_GAAC, row_bytes, char);
				} _hoops_RGGA (_hoops_GAAC == image->rasters);
			}

			if (image->rasters != null)
				FREE_ARRAY (_hoops_GAAC, image->height, void *);
			if (image->_hoops_RCPIR != null)
				FREE_ARRAY (image->_hoops_RCPIR, image->height, void *);
			_hoops_RGAIR (image->name);

			if (image->next)
				_hoops_HPRH (image->next);

			while ((dl = image->_hoops_GAHA) != null) {
				image->owner = null;
				image->_hoops_GAHA = dl->next;
				_hoops_HPRH(dl);
			}

			if (BIT (image->flags, _hoops_SHCC)) {
				if (HOOPS_WORLD->_hoops_ACPIR == 0)
					_hoops_PHPGR (HEC_HOOPS_SYSTEM, HES_HOOPS_IS_CONFUSED,
								"Hoops is very confused concerning transparent image counting.",
								"The picture may not be right.");
				else
					HOOPS_WORLD->_hoops_ACPIR--;
			}

			FREE (thing, Image);
		}	break;

		case _hoops_SIIP:
		case _hoops_IIIP: {
			Polyline *		polyline = (Polyline *)thing;

			if (!BIT(polyline->_hoops_RRHH, _hoops_PCPIR)) {
				if (polyline->allocated > 0)
					FREE_ARRAY (polyline->points,
								polyline->allocated, Point);
				if (polyline->orientation != null)
					if (BIT(polyline->_hoops_RRHH, _hoops_HCPIR))
						FREE_ARRAY (polyline->orientation, 2, Vector);
					else
						FREE_ARRAY (polyline->orientation, 1, Vector);
			}
			FREE (thing, Polyline);
		}	break;

		case _hoops_HIIP: {
			_hoops_SHRIR *		_hoops_ICPIR = (_hoops_SHRIR *)thing;

			if (_hoops_ICPIR->allocated > 0)
				FREE_ARRAY (_hoops_ICPIR->points, _hoops_ICPIR->allocated, Point);
			if (_hoops_ICPIR->mapping != null) {
				int			count = -_hoops_ICPIR->count / 2;

				for (int i = 0; i < count; ++i)
					HI_Remove_Lightweight_Key (_hoops_ICPIR->mapping[i]);

				FREE_ARRAY (_hoops_ICPIR->mapping, _hoops_ICPIR->allocated/2, int);
			}
			FREE (thing, _hoops_SHRIR);
		}	break;

		case _hoops_PIIP: {
			FREE (thing, Line);
		}	break;

		case _hoops_CHIP: {
#ifndef _hoops_CCPIR
			_hoops_PIRGR *		_hoops_SCPIR = (_hoops_PIRGR *)thing;
			int					knot_count = _hoops_SCPIR->control_point_count + _hoops_SCPIR->degree + 1;

			if (_hoops_SCPIR->control_points != null)
				FREE_ARRAY	(_hoops_SCPIR->control_points,
							 _hoops_SCPIR->control_point_count, Point);
			if (_hoops_SCPIR->knots != null)
				FREE_ARRAY	(_hoops_SCPIR->knots, knot_count, float);
			if (_hoops_SCPIR->weights != null)
				FREE_ARRAY	(_hoops_SCPIR->weights, _hoops_SCPIR->control_point_count, float);
			if (_hoops_SCPIR->polyline.points != null)
				FREE_ARRAY	(_hoops_SCPIR->polyline.points, _hoops_SCPIR->polyline.allocated, Point);
			FREE  (thing, _hoops_PIRGR);
#endif
		}	break;

		case _hoops_PRCP: {
#ifndef _hoops_GSPIR
			_hoops_APPGR *		_hoops_SCPIR = (_hoops_APPGR *)thing;
			int 				_hoops_RSPIR = _hoops_SCPIR->n_u_vertices + _hoops_SCPIR->u_degree + 1;
			int 				_hoops_ASPIR = _hoops_SCPIR->n_v_vertices + _hoops_SCPIR->v_degree + 1;

			if (_hoops_SCPIR->control_points != null)
				FREE_ARRAY (_hoops_SCPIR->control_points, _hoops_SCPIR->n_u_vertices*_hoops_SCPIR->n_v_vertices, Point);
			if (_hoops_SCPIR->weights != null)
				FREE_ARRAY (_hoops_SCPIR->weights, _hoops_SCPIR->n_u_vertices*_hoops_SCPIR->n_v_vertices, float);
			if (_hoops_SCPIR->u_knots != null)
				FREE_ARRAY (_hoops_SCPIR->u_knots, _hoops_RSPIR, float);
			if (_hoops_SCPIR->v_knots != null)
				FREE_ARRAY (_hoops_SCPIR->v_knots, _hoops_ASPIR, float);

			if (_hoops_SCPIR->_hoops_GPRIR != null)
				_hoops_AARIR (_hoops_SCPIR->_hoops_GPRIR);
			if (_hoops_SCPIR->_hoops_IPRI != null)
				HI_Au_Revoir  ((_hoops_HPAH *)_hoops_SCPIR->_hoops_IPRI);

			FREE (thing, _hoops_APPGR);
#endif
		}	break;

		case _hoops_ASIP: {
#ifndef _hoops_PSPIR
			FREE (thing, Cylinder);
#endif
		}	break;

		case _hoops_CSIP: {
#ifndef _hoops_PSPIR
			PolyCylinder *		_hoops_HSPIR = (PolyCylinder *)thing;
			_hoops_GACR *		dl;

			_hoops_HSPIR->bounding.release();

			if (_hoops_HSPIR->points)
				FREE_ARRAY (_hoops_HSPIR->points, _hoops_HSPIR->point_count, Point);
			if (_hoops_HSPIR->radii)
				FREE_ARRAY (_hoops_HSPIR->radii, _hoops_HSPIR->_hoops_ISPIR, float);
			if (_hoops_HSPIR->_hoops_CSPIR)
				FREE_ARRAY (_hoops_HSPIR->_hoops_CSPIR, _hoops_HSPIR->point_count, _hoops_SSPIR);
			if (_hoops_HSPIR->_hoops_GGHIR)
				FREE_ARRAY (_hoops_HSPIR->_hoops_GGHIR, _hoops_HSPIR->point_count, float);

			if (_hoops_HSPIR->_hoops_RGHIR != null) {
				_hoops_AGHIR *	_hoops_PGHIR = _hoops_HSPIR->_hoops_RGHIR;

				if (_hoops_PGHIR->ecolors != null && _hoops_PGHIR->ecolors != _hoops_PGHIR->fcolors)
					FREE_ARRAY (_hoops_PGHIR->ecolors, _hoops_HSPIR->point_count, RGB);
				if (_hoops_PGHIR->fcolors != null)
					FREE_ARRAY (_hoops_PGHIR->fcolors, _hoops_HSPIR->point_count, RGB);
				if (_hoops_PGHIR->_hoops_HGHIR != null && _hoops_PGHIR->_hoops_HGHIR != _hoops_PGHIR->_hoops_IGHIR)
					FREE_ARRAY (_hoops_PGHIR->_hoops_HGHIR, _hoops_HSPIR->point_count, _hoops_ACGHR);
				if (_hoops_PGHIR->_hoops_IGHIR != null)
					FREE_ARRAY (_hoops_PGHIR->_hoops_IGHIR, _hoops_HSPIR->point_count, _hoops_ACGHR);
				if (_hoops_PGHIR->flags != null)
					FREE_ARRAY (_hoops_PGHIR->flags, _hoops_HSPIR->point_count, _hoops_CGHIR);
				FREE (_hoops_PGHIR, _hoops_AGHIR);
			}
			while ((dl = _hoops_HSPIR->_hoops_SGHIR) != null) {
				_hoops_HSPIR->_hoops_SGHIR = dl->next;
				_hoops_HPRH(dl);
			}
			while ((dl = _hoops_HSPIR->_hoops_GRHIR) != null) {
				_hoops_HSPIR->_hoops_GRHIR = dl->next;
				_hoops_HPRH(dl);
			}
			FREE (thing, PolyCylinder);
#endif
		}	break;

		case _hoops_HSIP: {
#ifndef _hoops_RRHIR
			Sphere *			sphere = (Sphere *)thing;

			if (sphere->_hoops_CSPIR != null)
				FREE_ARRAY (sphere->_hoops_CSPIR, 3, Vector);
			FREE (thing, Sphere);
#endif
		}	break;

		case _hoops_ARHIR: {
			_hoops_PRHIR *			_hoops_HRHIR = (_hoops_PRHIR *)thing;

			if (_hoops_HRHIR->allocated > 0)
				FREE_ARRAY (_hoops_HRHIR->points, _hoops_HRHIR->allocated, Point);

			if (_hoops_HRHIR->_hoops_IRHIR > 0)
				FREE_ARRAY (_hoops_HRHIR->lengths, _hoops_HRHIR->_hoops_IRHIR, int);

			FREE (thing, _hoops_PRHIR);
		}	break;

		case _hoops_RCIP: {
			Polygon *			_hoops_HARIR = (Polygon *)thing;

			if (_hoops_HARIR->allocated > 0)
				FREE_ARRAY (_hoops_HARIR->points, _hoops_HARIR->allocated, Point);

			FREE (thing, Polygon);
		}	break;

		case _hoops_SCIP:
		case _hoops_GSIP: {
			/* _hoops_PAGA: _hoops_PAH'_hoops_RA _hoops_SGH _hoops_RH _hoops_ASGH "_hoops_AHAP->_hoops_CPAP._hoops_CPHAR",
			 * _hoops_PGGA _hoops_CRHIR _hoops_GA'_hoops_RA _hoops_SRHIR _hoops_RH _hoops_GAHIR - _hoops_SSIA _hoops_SPGA'_hoops_RA
			 * _hoops_PRRP _hoops_RGIRR _hoops_GIAA "->_hoops_CPAP". _hoops_PHGP _hoops_SICR "_hoops_AHAP"
			 * _hoops_IS _hoops_PCPA _hoops_SR _hoops_RRP _hoops_HPGR _hoops_RH _hoops_SCIA (_hoops_HRII _hoops_HSAR _hoops_RAHIR _hoops_SCH _hoops_GPP
			 * _hoops_GRR _hoops_SGH, _hoops_PGAP _hoops_SAGGR _hoops_AAHIR.)
			 */

			{	Polyhedron *	_hoops_IPRI = (Polyhedron *)thing;

				_hoops_IPRI->bounding.release();

				if (_hoops_IPRI->_hoops_HGAIR != null)
					HI_Au_Revoir ((_hoops_HPAH *)_hoops_IPRI->_hoops_HGAIR);

				{
					Tristrip *			ts;

					if ((ts = _hoops_IPRI->tristrips) != null) do {
						_hoops_GACR *		dl;

						while ((dl = ts->_hoops_GAHA) != null) {
							ts->_hoops_GAHA = dl->next;
							_hoops_HPRH(dl);
						}
					} while ((ts = ts->next) != null);
				}
				{
					Polyedge *			pe;

					if ((pe = _hoops_IPRI->_hoops_SHGPR) != null) do {
						_hoops_GACR *		dl;

						while ((dl = pe->_hoops_GAHA) != null) {
							pe->_hoops_GAHA = dl->next;
							_hoops_HPRH(dl);
						}
					} while ((pe = pe->next) != null);

					if ((pe = _hoops_IPRI->_hoops_CHGPR) != null) do {
						_hoops_GACR *		dl;

						while ((dl = pe->_hoops_GAHA) != null) {
							pe->_hoops_GAHA = dl->next;
							_hoops_HPRH(dl);
						}
					} while ((pe = pe->next) != null);
				}
				{
					Polymarker *			pm;

					if ((pm = _hoops_IPRI->_hoops_GIGPR) != null) do {
						_hoops_GACR *		dl;

						while ((dl = pm->_hoops_GAHA) != null) {
							pm->_hoops_GAHA = dl->next;
							_hoops_HPRH(dl);
						}
					} while ((pm = pm->next) != null);
				}

				if (!BIT(_hoops_IPRI->polyhedron_flags, PHF_POINTS_BY_REFERENCE))
					if (_hoops_IPRI->points != null)
						FREE_ARRAY_ALIGNED (_hoops_IPRI->points,
									_hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR,
									Point, 16);

#ifndef DISABLE_GEOMETRY_ATTRIBUTES
				if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR) && _hoops_IPRI->local_vertex_attributes.flags != null)
					FREE_ARRAY (_hoops_IPRI->local_vertex_attributes.flags,
								_hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR,
								Local_Vertex_Flags);
#ifndef _hoops_GCGHR
				if (_hoops_IPRI->local_vertex_attributes._hoops_PAHIR != null &&
					_hoops_IPRI->local_vertex_attributes._hoops_PAHIR !=
						_hoops_IPRI->local_vertex_attributes.ecolors &&
					_hoops_IPRI->local_vertex_attributes._hoops_PAHIR !=
						_hoops_IPRI->local_vertex_attributes.fcolors)
					FREE_ARRAY (_hoops_IPRI->local_vertex_attributes._hoops_PAHIR,
								_hoops_IPRI->point_count,
								RGB);
				if (_hoops_IPRI->local_vertex_attributes.ecolors != null &&
					_hoops_IPRI->local_vertex_attributes.ecolors !=
						_hoops_IPRI->local_vertex_attributes.fcolors)
					FREE_ARRAY (_hoops_IPRI->local_vertex_attributes.ecolors,
								_hoops_IPRI->point_count,
								RGB);
				if (_hoops_IPRI->local_vertex_attributes.fcolors != null)
					FREE_ARRAY (_hoops_IPRI->local_vertex_attributes.fcolors,
								_hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR,
								RGB);

				if (_hoops_IPRI->local_vertex_attributes._hoops_HAHIR != null &&
					_hoops_IPRI->local_vertex_attributes._hoops_HAHIR !=
						_hoops_IPRI->local_vertex_attributes._hoops_HGHIR &&
					_hoops_IPRI->local_vertex_attributes._hoops_HAHIR !=
						_hoops_IPRI->local_vertex_attributes._hoops_IGHIR)
					FREE_ARRAY (_hoops_IPRI->local_vertex_attributes._hoops_HAHIR,
								_hoops_IPRI->point_count,
								_hoops_ACGHR);
				if (_hoops_IPRI->local_vertex_attributes._hoops_HGHIR != null &&
					_hoops_IPRI->local_vertex_attributes._hoops_HGHIR !=
						_hoops_IPRI->local_vertex_attributes._hoops_IGHIR)
					FREE_ARRAY (_hoops_IPRI->local_vertex_attributes._hoops_HGHIR,
								_hoops_IPRI->point_count,
								_hoops_ACGHR);
				if (_hoops_IPRI->local_vertex_attributes._hoops_IGHIR != null)
					FREE_ARRAY (_hoops_IPRI->local_vertex_attributes._hoops_IGHIR,
								_hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR,
								_hoops_ACGHR);

				if (_hoops_IPRI->local_vertex_attributes._hoops_IAHIR != null)
					FREE_ARRAY (_hoops_IPRI->local_vertex_attributes._hoops_IAHIR,
								_hoops_IPRI->point_count,
								RGBAS32);
#endif
#ifndef _hoops_CSGHR
				if (_hoops_IPRI->local_vertex_attributes._hoops_CAHIR != null)
					FREE_ARRAY (_hoops_IPRI->local_vertex_attributes._hoops_CAHIR,
								_hoops_IPRI->point_count,
								float);
				if (_hoops_IPRI->local_vertex_attributes._hoops_SAHIR != null)
					FREE_ARRAY (_hoops_IPRI->local_vertex_attributes._hoops_SAHIR,
								_hoops_IPRI->point_count,
								unsigned char);

				if (_hoops_IPRI->local_vertex_attributes._hoops_GPHIR) {
					_hoops_RPHIR *sl = _hoops_IPRI->local_vertex_attributes._hoops_GPHIR;
					_hoops_RPHIR *_hoops_APHIR;

					while (sl) {
						_hoops_RGAIR (sl->name);
						_hoops_APHIR = sl->next;
						FREE (sl, _hoops_RPHIR);
						sl = _hoops_APHIR;
					}
				}
#endif
#ifndef _hoops_HCGHR
				if (_hoops_IPRI->local_vertex_attributes.normals != null)
				  if (!BIT(_hoops_IPRI->polyhedron_flags, PHF_VERTEX_NORMALS_BY_REFERENCE))
					FREE_ARRAY (_hoops_IPRI->local_vertex_attributes.normals,
								_hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR,
								Vector);
#endif
#ifndef DISABLE_TEXTURING
				if (_hoops_IPRI->local_vertex_attributes.params != null)
					FREE_ARRAY (_hoops_IPRI->local_vertex_attributes.params,
								(_hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR) *
								_hoops_IPRI->local_vertex_attributes.param_width,
								_hoops_RSSH);

				if (_hoops_IPRI->local_vertex_attributes._hoops_PPHIR != null)
					FREE_ARRAY (_hoops_IPRI->local_vertex_attributes._hoops_PPHIR,
								(_hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR) *
								_hoops_IPRI->local_vertex_attributes._hoops_HPHIR,
								_hoops_RSSH);

				if (_hoops_IPRI->local_vertex_attributes._hoops_IPHIR != null)
					FREE_ARRAY (_hoops_IPRI->local_vertex_attributes._hoops_IPHIR,
								(_hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR) * 2,
								_hoops_RSSH);
#endif
				if (_hoops_IPRI->local_vertex_attributes._hoops_RCIHR != null) {
					int						point_count = _hoops_IPRI->point_count;
					_hoops_CPHIR **		_hoops_SPHIR = _hoops_IPRI->local_vertex_attributes._hoops_RCIHR;

					while (point_count-- > 0) {
						_hoops_CPHIR *	_hoops_GHHIR;

						if ((_hoops_GHHIR = *_hoops_SPHIR++) != null) {
							int		count = _hoops_GHHIR[0].face + 1;

							FREE_ARRAY (_hoops_GHHIR, count, _hoops_CPHIR);
						}
					}
					FREE_ARRAY (_hoops_IPRI->local_vertex_attributes._hoops_RCIHR,
								_hoops_IPRI->point_count, _hoops_CPHIR *);
				}
				if (_hoops_IPRI->_hoops_GCRHR > 0)
					FREE_ARRAY (_hoops_IPRI->local_vertex_attributes._hoops_RHHIR,
								_hoops_IPRI->_hoops_GCRHR, int);




				if (_hoops_IPRI->_hoops_IHHPR.flags != null)
					FREE_ARRAY (_hoops_IPRI->_hoops_IHHPR.flags,
								_hoops_IPRI->_hoops_SPHA,
								_hoops_GHHPR);
#ifndef _hoops_GCGHR
				if (_hoops_IPRI->_hoops_IHHPR.colors != null)
					FREE_ARRAY (_hoops_IPRI->_hoops_IHHPR.colors,
								_hoops_IPRI->_hoops_SPHA,
								RGB);
				if (_hoops_IPRI->_hoops_IHHPR.findices != null)
					FREE_ARRAY (_hoops_IPRI->_hoops_IHHPR.findices,
								_hoops_IPRI->_hoops_SPHA,
								_hoops_ACGHR);
#endif
#ifndef _hoops_RGIPR
				if (_hoops_IPRI->_hoops_IHHPR._hoops_AHHIR != null)
					FREE_ARRAY (_hoops_IPRI->_hoops_IHHPR._hoops_AHHIR,
								_hoops_IPRI->_hoops_SPHA,
								unsigned char);
				if (_hoops_IPRI->_hoops_IHHPR.weights != null)
					FREE_ARRAY (_hoops_IPRI->_hoops_IHHPR.weights,
								_hoops_IPRI->_hoops_SPHA,
								float);

				if (_hoops_IPRI->_hoops_IHHPR._hoops_PHHIR) {
					_hoops_HHHIR *_hoops_IHHIR = _hoops_IPRI->_hoops_IHHPR._hoops_PHHIR;
					_hoops_HHHIR *_hoops_CHHIR;

					while (_hoops_IHHIR) {
						_hoops_RGAIR (_hoops_IHHIR->name);
						_hoops_CHHIR = _hoops_IHHIR->next;
						FREE (_hoops_IHHIR, _hoops_HHHIR);
						_hoops_IHHIR = _hoops_CHHIR;
					}
				}
#endif
				if (_hoops_IPRI->_hoops_IHHPR.normals != null)
					FREE_ARRAY (_hoops_IPRI->_hoops_IHHPR.normals,
								_hoops_IPRI->_hoops_SPHA,
								Vector);

				if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR) && _hoops_IPRI->local_face_attributes.flags != null)
					FREE_ARRAY (_hoops_IPRI->local_face_attributes.flags,
								_hoops_IPRI->face_count,
								_hoops_GIIPR);

				if (_hoops_IPRI->local_face_attributes._hoops_GARHR != null) {
					FREE_ARRAY (_hoops_IPRI->local_face_attributes._hoops_GARHR,
								_hoops_IPRI->local_face_attributes._hoops_HCRHR,
								_hoops_SRRHR);
					_hoops_IPRI->local_face_attributes._hoops_HCRHR = 0;
				}
#ifndef _hoops_GCGHR
				if (_hoops_IPRI->local_face_attributes.colors != null)
					FREE_ARRAY (_hoops_IPRI->local_face_attributes.colors,
								_hoops_IPRI->face_count,
								RGB);
				if (_hoops_IPRI->local_face_attributes.findices != null)
					FREE_ARRAY (_hoops_IPRI->local_face_attributes.findices,
								_hoops_IPRI->face_count,
								_hoops_ACGHR);
#endif
#ifndef _hoops_PGPHR
				if (_hoops_IPRI->local_face_attributes._hoops_AHHIR != null)
					FREE_ARRAY (_hoops_IPRI->local_face_attributes._hoops_AHHIR,
								_hoops_IPRI->face_count,
								unsigned char);
#endif
				if (_hoops_IPRI->local_face_attributes.normals != null)
					FREE_ARRAY_ALIGNED (_hoops_IPRI->local_face_attributes.normals,
										_hoops_IPRI->face_count,
										_hoops_ARPA, 16);
#endif

				if (_hoops_IPRI->local_face_attributes.regions != null)
					FREE_ARRAY (_hoops_IPRI->local_face_attributes.regions,
								_hoops_IPRI->face_count+_hoops_SHHIR,
								int);

				if (_hoops_IPRI->_hoops_GIGPR != null)
					HI_Free_Polymarker_List (_hoops_IPRI->_hoops_GIGPR);

				if (_hoops_IPRI->_hoops_SHGPR != null)
					HI_Free_Polyedge_List (_hoops_IPRI->_hoops_SHGPR);
				if (_hoops_IPRI->_hoops_CHGPR != null)
					HI_Free_Polyedge_List (_hoops_IPRI->_hoops_CHGPR);

				if (_hoops_IPRI->tristrips != null)
					HI_Free_Tristrip_List (_hoops_IPRI->tristrips);

				if (_hoops_IPRI->_hoops_GIHIR._hoops_CIAIR > 0)
					FREE_ARRAY (_hoops_IPRI->_hoops_GIHIR._hoops_SIAIR, _hoops_IPRI->_hoops_GIHIR._hoops_CIAIR, float);
			}

			switch (thing->type) {
				default: {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									   "Unexpected polyhedron");
				}	break;

				case _hoops_GSIP: {
					_hoops_AIHPR *_hoops_PIHPR = (_hoops_AIHPR *)thing;
					FREE (_hoops_PIHPR, _hoops_AIHPR);
				}	break;

				case _hoops_SCIP: {
					Shell		*_hoops_SPHPR = (Shell *)thing;

					if (!BIT (_hoops_SPHPR->polyhedron_flags, PHF_SHELL_FACE_LIST_BY_REFERENCE)) {
						if (_hoops_SPHPR->face_list_length != 0)
							FREE_ARRAY (_hoops_SPHPR->face_list, _hoops_SPHPR->face_list_length, int);
					}


					if (_hoops_SPHPR->_hoops_GRCPR != null)
						FREE_ARRAY (_hoops_SPHPR->_hoops_GRCPR, _hoops_SPHPR->_hoops_SPHA, _hoops_RHHPR);

					if (_hoops_SPHPR->_hoops_HHHPR != null)
						FREE_ARRAY (_hoops_SPHPR->_hoops_HHHPR, _hoops_SPHPR->point_count + 1, _hoops_RHHPR *);

					if (_hoops_SPHPR->_hoops_SGCPR != null)
						FREE_ARRAY (_hoops_SPHPR->_hoops_SGCPR, _hoops_SPHPR->_hoops_SPHA, _hoops_CGCPR);

					FREE (_hoops_SPHPR, Shell);
				}	break;
			}
		}	break;

		case _hoops_AGCP: {
			_hoops_HACC *			text = (_hoops_HACC *)thing;

			text->bounding.release();

			if (text->karacters != null)
				FREE_ARRAY (text->karacters, text->count+1, Karacter);

			if (text->_hoops_PICHR != 0) {
				if (text->_hoops_ICI != null)
					FREE_ARRAY (text->_hoops_ICI, text->_hoops_PICHR, int);
				if (text->_hoops_RIHIR != null)
					FREE_ARRAY (text->_hoops_RIHIR, text->_hoops_PICHR, Karacter *);
			}

			if (text->_hoops_AAPGR != null)
				_hoops_RPRIR ((_hoops_HPAH *)text->_hoops_AAPGR);

			if (text->region != null)
				FREE (text->region, _hoops_AIHIR);

			if (text->_hoops_PIHIR != null) {
				for (int i=0; i<text->count; i++) {
					_hoops_IGPIR	*name;

					if ((name = text->_hoops_PIHIR[i]._hoops_HGPIR) != null)
						HI_Free_Font_Names (name);
				}

				FREE_ARRAY (text->_hoops_PIHIR, text->count, _hoops_HIHIR);
			}

			FREE (thing, _hoops_HACC);
		}	break;

		case HK_STRING_CURSOR: {
			FREE (thing, _hoops_PIGPR);
		}	break;

		case _hoops_AHIP: {
			_hoops_PHIP *	_hoops_RRA = (_hoops_PHIP *)thing;

			if (!BIT(_hoops_RRA->_hoops_RRHH, _hoops_IIHIR)) {
				_hoops_AIGPR *	_hoops_RIGC;
				_hoops_IIRIR (_hoops_RIGC);
				_hoops_CIHIR(_hoops_RIGC, _hoops_RRA, true);
			}

			_hoops_RRA->bounding.release();

			for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++)
				Q_INUTILE (_hoops_RRA->_hoops_IHIP[i]);
			FREE_ARRAY (_hoops_RRA->_hoops_IHIP, _hoops_RRA->_hoops_HHIP, _hoops_SIHIR *);
			HI_Free_Conditional (&_hoops_RRA->condition);
			FREE (thing, _hoops_PHIP);
		}	break;

#ifndef DISABLE_CALLBACKS
		case HK_CALLBACK: {
			_hoops_GCHIR *		_hoops_RCHIR = (_hoops_GCHIR *)thing;

			if (_hoops_RCHIR->_hoops_ACHIR != null)
				HI_Free_Callback_List (_hoops_RCHIR->_hoops_ACHIR);

			FREE (_hoops_RCHIR, _hoops_GCHIR);
		}	break;
#endif

		case _hoops_IIPPR: {
			_hoops_SRPPR *		alias = (_hoops_SRPPR *)thing;

			_hoops_RGAIR (alias->name);
			HI_Free_Path (alias->_hoops_AAPPR);
			FREE (alias, _hoops_SRPPR);
		}	break;

#ifndef DISABLE_CALLBACKS
		case _hoops_PCHIR: {
			_hoops_HCHIR *		_hoops_ICHIR = (_hoops_HCHIR *)thing;

			_hoops_RGAIR (_hoops_ICHIR->name);
			FREE (_hoops_ICHIR, _hoops_HCHIR);
		}	break;
#endif

#ifndef DISABLE_COLOR_NAMES
		case _hoops_CCHIR: {
			_hoops_SCHIR *			_hoops_GSHIR = (_hoops_SCHIR *)thing;
			_hoops_RSHIR			*_hoops_ASHIR, *_hoops_PSHIR;

			if ((_hoops_ASHIR = _hoops_GSHIR->_hoops_HSHIR) != null) do {
				_hoops_PSHIR = _hoops_ASHIR->next;
				_hoops_RGAIR (_hoops_ASHIR->name);
				FREE (_hoops_ASHIR, _hoops_RSHIR);
			} while ((_hoops_ASHIR = _hoops_PSHIR) != null);

			HI_Free_Material_Names (&_hoops_GSHIR->_hoops_ISHIR, 1);

			_hoops_RGAIR (_hoops_GSHIR->definition);
			FREE (_hoops_GSHIR, _hoops_SCHIR);
		}	break;
#endif

		case _hoops_CSHIR: {
			FREE (thing, _hoops_SSHIR);
		}	break;

		case _hoops_GGIIR: {
			FREE (thing, _hoops_RGIIR);
		}	break;

		case _hoops_AGIIR: {
			_hoops_PGIIR *		font = (_hoops_PGIIR *)thing;

			_hoops_RGAIR (font->name);
			if (font->_hoops_HGIIR != null)
				_hoops_HPRH (font->_hoops_HGIIR);
			if (font->_hoops_IGIIR != 0)
				FREE_ARRAY (font->_hoops_CGIIR,
							font->_hoops_IGIIR, char *);
			if (!BIT (font->_hoops_RRHH, _hoops_SGIIR))
				FREE_ARRAY (font->data, font->data_length, char);
			FREE (thing, _hoops_PGIIR);
		}	break;

#ifndef DISABLE_TEXTURING
		case _hoops_GRIIR: {
			_hoops_RCR *		tx = (_hoops_RCR *)thing;

			if (tx->owner != null) {
				_hoops_AIGPR *	_hoops_RIGC;
				_hoops_IIRIR (_hoops_RIGC);
				HI_UnDefine_Texture (_hoops_RIGC, tx);
			}

			if (tx->_hoops_HGIIR != null)
				_hoops_HPRH (tx->_hoops_HGIIR);

			if (tx->_hoops_RHGH != null)
				_hoops_HPRH (tx->_hoops_RHGH);

			if (tx->image != null) {
				if (tx->image->texture == (_hoops_RCR const *)thing)
					tx->image->texture = null;
				_hoops_HPRH (tx->image);
			}

			if (tx->_hoops_GAGH != null)
				_hoops_HPRH (tx->_hoops_GAGH);

			if (tx->_hoops_RRIIR != null)
				_hoops_HPRH (tx->_hoops_RRIIR);

			_hoops_RGAIR (tx->name);

			if (tx->_hoops_PAPIR) {
				_hoops_AAPIR	*_hoops_CAPIR, *_hoops_PAPIR = tx->_hoops_PAPIR;

				while (_hoops_PAPIR != null) {
					_hoops_CAPIR = _hoops_PAPIR->next;
					_hoops_RGAIR(_hoops_PAPIR->name);
					FREE (_hoops_PAPIR, _hoops_AAPIR);
					_hoops_PAPIR = _hoops_CAPIR;
				}
			}

			if (tx->_hoops_PRAH) {
				int _hoops_ARIIR;

				if (BIT (tx->flags, _hoops_AIA))
					_hoops_ARIIR = 6;
				else
					_hoops_ARIIR = tx->_hoops_ICR[0] *
									tx->_hoops_ICR[1] *
									tx->_hoops_ICR[2];

				for (int i=0; i<_hoops_ARIIR; i++)
					_hoops_HPRH(tx->_hoops_PRAH[i]);
				FREE_ARRAY(tx->_hoops_PRAH, _hoops_ARIIR, _hoops_RCR*);
			}

			if (tx->_hoops_RSR) {
				_hoops_RGAIR (tx->_hoops_RSR->shader_source);
				FREE (tx->_hoops_RSR, _hoops_AGSA);
			}

			FREE (tx, _hoops_RCR);
		}	break;
#endif

		case _hoops_PRIIR: {
			FREE (thing, _hoops_HRIIR);
		}	break;

/* _hoops_HHSH, _hoops_HIH _hoops_GRAS _hoops_PAH _hoops_CAHP _hoops_SSHGR */
/* #_hoops_CHS _hoops_IRIIR */
		case _hoops_CRIIR: {
			_hoops_SRIIR *		be = (_hoops_SRIIR *)thing;

			/* _hoops_ISPR _hoops_IH _hoops_IHIA _hoops_GAIIR */
			if (be->_hoops_RAIIR != null)
				_hoops_HPRH (be->_hoops_RAIIR);

			Q_INUTILE (be->source);
			FREE (be, _hoops_SRIIR);
		}	break;

		case _hoops_AAIIR: {
			_hoops_PAIIR *	_hoops_HAIIR = (_hoops_PAIIR *)thing;

			/* _hoops_ISPR _hoops_IH _hoops_IHIA _hoops_IAIIR */
			if (_hoops_HAIIR->_hoops_CAIIR != null)
				_hoops_HPRH (_hoops_HAIIR->_hoops_CAIIR);

			Q_INUTILE (_hoops_HAIIR->source);
			FREE (_hoops_HAIIR, _hoops_PAIIR);
		}	break;

		case _hoops_SAIIR: {
			Selection_Event *	_hoops_GPIIR = (Selection_Event *)thing;
			_hoops_RPIIR *	si;

			if ((si = _hoops_GPIIR->_hoops_APIIR) != null) {
				_hoops_RPIIR				*_hoops_PPIIR;
				do {
					_hoops_PPIIR = si->next;
					HI_Free_Selection_Item (si);
				} while ((si = _hoops_PPIIR) != null);
			}

			if (_hoops_GPIIR->_hoops_HPIIR != null) {
				_hoops_IPIIR *_hoops_CPIIR = _hoops_GPIIR->_hoops_HPIIR;
				if (_hoops_CPIIR->_hoops_SPIIR != null)
					FREE_ARRAY (_hoops_CPIIR->_hoops_SPIIR, _hoops_CPIIR->allocated, _hoops_RPIIR *);
				FREE (_hoops_CPIIR, _hoops_IPIIR);
			}

			if (_hoops_GPIIR->_hoops_HARIR != null)
				FREE_ARRAY (_hoops_GPIIR->_hoops_HARIR, _hoops_GPIIR->count, Point);

			if (_hoops_GPIIR->source != null)
				_hoops_HPRH (_hoops_GPIIR->source);

			if (_hoops_GPIIR->_hoops_GHIIR != null)
				_hoops_HPRH (_hoops_GPIIR->_hoops_GHIIR);

			if (_hoops_GPIIR->target != null)
				Q_INUTILE (_hoops_GPIIR->target);

			FREE (_hoops_GPIIR, Selection_Event);
		}	break;

		case _hoops_RHIIR: {
			_hoops_AHIIR *		_hoops_GPIIR = (_hoops_AHIIR *)thing;

			_hoops_PRPIR (_hoops_GPIIR->string);

			Q_INUTILE (_hoops_GPIIR->source);
			FREE (_hoops_GPIIR, _hoops_AHIIR);
		}	break;

		case _hoops_PHIIR: {
			_hoops_HHIIR *		_hoops_IHIIR = (_hoops_HHIIR *)thing;

			Q_INUTILE (_hoops_IHIIR->_hoops_CHIIR);
			FREE (_hoops_IHIIR, _hoops_HHIIR);
		}	break;
/* #_hoops_SHIIR */

		case _hoops_GIIIR: {
			_hoops_RIIIR *		_hoops_GPIIR = (_hoops_RIIIR *)thing;

			_hoops_RGAIR (_hoops_GPIIR->name);
			_hoops_RGAIR (_hoops_GPIIR->value);
			FREE (_hoops_GPIIR, _hoops_RIIIR);
		}	break;

		case _hoops_AIIIR: {
			_hoops_PIIIR *		_hoops_HIIIR = (_hoops_PIIIR *)thing;

			if (!BIT (_hoops_HIIIR->_hoops_RRHH, _hoops_IIIIR))
				_hoops_RGAIR (_hoops_HIIIR->name);

			if (_hoops_HIIIR->_hoops_CIIIR != null &&
				!BIT (_hoops_HIIIR->_hoops_RRHH, _hoops_SIIIR)) {
				_hoops_GCIIR *		_hoops_SPHHR = _hoops_HIIIR->_hoops_CIIIR;
				int						size = _hoops_SPHHR->size;

				while (size-- > 0) {
					_hoops_AIGPR *	_hoops_RIGC;
					_hoops_IIRIR(_hoops_RIGC);

					_hoops_PIIIR			**list = &_hoops_SPHHR->table[size];
					_hoops_PIIIR			*victim;

					while ((victim = *list) != null) {
						_hoops_CIGPR (_hoops_RIGC, victim);
						_hoops_HPRH (victim);
					}
				}
				FREE_ARRAY (_hoops_SPHHR->table, _hoops_SPHHR->size, _hoops_PIIIR *);
				FREE (_hoops_SPHHR, _hoops_GCIIR);
			}
			if (_hoops_HIIIR->_hoops_RCIIR == _hoops_ACIIR) {
				int		index = _hoops_HIIIR->id;

				HOOPS_WORLD->_hoops_PCIIR[index] = null;
			}
			FREE (thing, _hoops_PIIIR);
		}	break;

		case _hoops_HCIIR: {
			_hoops_GACR *dl = (_hoops_GACR *)thing;

			if (dl->_hoops_GGCI >= 0) {
				_hoops_AIGPR *	_hoops_RIGC;
				_hoops_IIRIR(_hoops_RIGC);
				HI_Extract_Display_List (_hoops_RIGC, dl->_hoops_GGCI, dl);
			}

			if (dl->list)
				HI_Clean_Display_List(&dl, false, true);

			if (dl->_hoops_GASI)
				dl->_hoops_GASI->_hoops_GASI = null;

			FREE (dl, _hoops_GACR);
		}  break;

		default: {
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
									"Unknown datatype in 'Au_Revoir'");
			return;
		}		/* _hoops_IHSA; */
		}
	} while ((thing = next) != null);

#	undef		Q_INUTILE
}
